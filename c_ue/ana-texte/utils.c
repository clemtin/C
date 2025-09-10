#include "utils.h"

// Fonction pour vérifier si un caractère peut faire partie d'un mot
int caractereDunMot(unsigned char c) {
    if ((c >= 'a' && c <= 'z') || // lettre minuscule
        (c >= 'A' && c <= 'Z') || // lettre majuscule
        (c >= 192 && c <= 255) || // lettre accentuée ISO 8859-1
        (c >= '0' && c <= '9') || // chiffre
        (c == '\'' )||              // apostrophe
        (c == '-')) {               // tiret
        return 1;
    } else {
        return 0;
    }
}

// Fonction pour vérifier si un caractère est un point, un point d'exclamation ou un point d'interrogation ou point de suspentions
int caractereFinDePhrase(unsigned char c) {
    if (c == '.' || c == '!' || c == '?'){
        return 1;
    }else {
        return 0;
        }
}
