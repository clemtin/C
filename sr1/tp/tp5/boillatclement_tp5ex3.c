#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATH 1024
#define MAGIC_SIZE 8
#define N 4 // nombre de fils traiterFichier

typedef struct {
    char path[MAX_PATH];
    ino_t inode;
    off_t size;
} Resultat;

// Convertit une chaîne hexadécimale ("FF D8 FF E0") en tableau d'octets
size_t parse_hex(const char *hexstr, unsigned char *out, size_t maxlen) {
    size_t count = 0;
    const char *p = hexstr;
    while (*p && count < maxlen) {
        while (isspace((unsigned char)*p)) p++; // ignore espaces
        if (!isxdigit((unsigned char)p[0]) || !isxdigit((unsigned char)p[1]))
            break;
        char byte_str[3] = { p[0], p[1], '\0' };
        out[count++] = (unsigned char)strtol(byte_str, NULL, 16);
        p += 2;
        while (isspace((unsigned char)*p)) p++;
    }
    return count;
}

// Compare les premiers octets du fichier avec un motif binaire
int compare_magic(const char *fichier, const unsigned char *magic, size_t magic_len) {
    int fd = open(fichier, O_RDONLY);
    if (fd < 0) return 0;
    unsigned char buffer[MAGIC_SIZE] = {0};
    ssize_t n = read(fd, buffer, magic_len);
    close(fd);
    if (n < (ssize_t)magic_len) return 0;
    return memcmp(buffer, magic, magic_len) == 0;
}

int main(int argc, char *argv[]) {
    int visualiser = 0;
    int binaire = 0;
    char *cmd = NULL;
    const char *magic_str = NULL;
    const char *repertoire = NULL;

    // --- Analyse des arguments ---
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-v cmd] [-b] <magic> <repertoire>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-v") == 0) {
            visualiser = 1;
            cmd = argv[++i];
        } else if (strcmp(argv[i], "-b") == 0) {
            binaire = 1;
        } else {
            break;
        }
        i++;
    }

    if (argc - i < 2) {
        fprintf(stderr, "Usage: %s [-v cmd] [-b] <magic> <repertoire>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    magic_str = argv[i];
    repertoire = argv[i + 1];

    unsigned char magic[MAGIC_SIZE];
    size_t magic_len;

    if (binaire) {
        magic_len = parse_hex(magic_str, magic, MAGIC_SIZE);
        if (magic_len == 0) {
            fprintf(stderr, "Erreur : format hex invalide\n");
            exit(EXIT_FAILURE);
        }
    } else {
        magic_len = strlen(magic_str);
        memcpy(magic, magic_str, magic_len);
    }

    int pipes_fichiers[N][2];
    int pipe_reponse[2];

    for (int j = 0; j < N; j++)
        if (pipe(pipes_fichiers[j]) == -1) { perror("pipe"); exit(1); }

    if (pipe(pipe_reponse) == -1) { perror("pipe"); exit(1); }

    // --- Fils traiterRéponse ---
    pid_t pid_reponse = fork();
    if (pid_reponse == 0) {
        close(pipe_reponse[1]);
        Resultat res;

        while (read(pipe_reponse[0], &res, sizeof(res)) > 0) {
            printf("MATCH: %s | inode=%lu | taille=%ld octets\n",
                   res.path, (unsigned long)res.inode, (long)res.size);

            if (visualiser && cmd != NULL) {
                pid_t pid_visu = fork();
                if (pid_visu == 0) {
                    execlp(cmd, cmd, res.path, NULL);
                    perror("execlp visu");
                    exit(1);
                }
            }
        }

        while (wait(NULL) > 0);
        close(pipe_reponse[0]);
        exit(0);
    }

    // --- Fils traiterFichier ---
    for (int j = 0; j < N; j++) {
        pid_t pid = fork();
        if (pid == 0) {
            close(pipes_fichiers[j][1]);
            close(pipe_reponse[0]);
            char chemin[MAX_PATH];
            while (read(pipes_fichiers[j][0], chemin, sizeof(chemin)) > 0) {
                if (compare_magic(chemin, magic, magic_len)) {
                    struct stat st;
                    if (stat(chemin, &st) == 0) {
                        Resultat res;
                        strncpy(res.path, chemin, MAX_PATH);
                        res.inode = st.st_ino;
                        res.size = st.st_size;
                        write(pipe_reponse[1], &res, sizeof(res));
                    }
                }
            }
            close(pipes_fichiers[j][0]);
            close(pipe_reponse[1]);
            exit(0);
        }
        close(pipes_fichiers[j][0]);
    }

    // --- Père : parcourt le répertoire ---
    DIR *dir = opendir(repertoire);
    if (!dir) { perror("opendir"); exit(1); }

    struct dirent *ent;
    int index = 0;

    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;

        char chemin[MAX_PATH];
        snprintf(chemin, MAX_PATH, "%s/%s", repertoire, ent->d_name);

        struct stat st;
        if (stat(chemin, &st) == 0 && S_ISREG(st.st_mode)) {
            write(pipes_fichiers[index][1], chemin, sizeof(chemin));
            index = (index + 1) % N;
        }
    }
    closedir(dir);

    for (int j = 0; j < N; j++)
        close(pipes_fichiers[j][1]);

    close(pipe_reponse[1]);

    for (int j = 0; j < N + 1; j++)
        wait(NULL);

    return 0;
}