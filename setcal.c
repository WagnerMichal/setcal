#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

struct tElement{ //STRUKTURA PRVKU
    char element[31]; //pole s prvkem (maximalni velikost prvku je 30 znaku)
};
struct tElementRelation{ //STRUKTURA ELEMENTU V RELACI
    struct tElement *elementPtr[2]; //v relaci jsou vzdy 2 prvky
};
struct tRelation{ //STRUKTURA RELACE
    struct tElementRelation **elementRelationPtr;
    int elementRelationCount;
    int capacity;
};
struct tUniversum{ //STRUKTURA UNIVERZA
    struct tElement **elementPtr;
    int elementCount;
    int capacity;
};
struct tSet{ //STRUKTURA MNOZINY
    struct tElement **elementPtr;
    int elementCount;
    int capacity;
};
struct tLine{ //STRUKTURA RADKU
    struct tUniversum *universumPtr;
    struct tSet *setPtr;
    struct tRelation *relationPtr;
};
struct tData{ //STRUKTURA DAT (cely vstupni soubor)
    struct tLine **linePtr;
    int lineCount; //pocet radku
    int capacity;
};
bool empty(const struct tData aData, int par1){ // A - tiskne 0 nebo 1 podle toho, jestli je množina definovaná na řádku A prázdná nebo neprázdná.
    if (aData.linePtr[par1]->setPtr == NULL && aData.linePtr[par1]->universumPtr == NULL){
        return false;
    }
    if (aData.linePtr[par1]->universumPtr == NULL && aData.linePtr[par1]->setPtr->elementCount == 0){ //pokud univerzum i mnozina prazdne -> true
        printf("true\n");
    }
    else if (aData.linePtr[par1]->universumPtr == NULL){ //pokud pouze univerzum prazdne -> false
        printf("false\n");
    }
    if (aData.linePtr[par1]->setPtr == NULL && aData.linePtr[par1]->universumPtr->elementCount == 0){
        printf("true\n");
    }
    else if (aData.linePtr[par1]->setPtr == NULL){ //pokud pouze mnozina prazdna -> false
        printf("false\n");
    }
    return true;
}
bool card(const struct tData aData, int par1){ // A - tiskne počet prvků v množině A (definované na řádku A).
    if (aData.linePtr[par1]->setPtr == NULL && aData.linePtr[par1]->universumPtr == NULL){  //pokud prazdne -> false
        return false;
    }
    if (aData.linePtr[par1]->universumPtr == NULL){ //univerzum prazdne -> tiskne pocet prvku v mnozine
        printf("%d\n", aData.linePtr[par1]->setPtr->elementCount);
    }
    else{
        printf("%d\n", aData.linePtr[par1]->universumPtr->elementCount);    //tiskne pocet prvku v univerzu
    }
    return true;
}
bool complement(const struct tData aData, int par1){ // A - tiskne doplněk množiny A. 1 2 3 4 5 6
    printf("S");
    if (par1 == 1){     //radek ukazuje na univerzum
        return true;
    }
    if (aData.linePtr[par1]->relationPtr){ //radek ukazuje na relace
        return false;
    }
    for (int i = 0; i < aData.linePtr[1]->universumPtr->elementCount; i++){ // projizdi univerzum
        int flag = 0;
        for (int j = 0; j < aData.linePtr[par1]->setPtr->elementCount; j++){ // projizdi mnozinu na radku par1
            if (strcmp(aData.linePtr[1]->universumPtr->elementPtr[i]->element, aData.linePtr[par1]->setPtr->elementPtr[j]->element) == 0){ // pokud se prvek v univerzu rovna s prvkem v mnozine
                flag++;
                break;
            }
        }
        if (flag == 0){     //pokud se zadny nerovna tak se vytiskne
            printf(" %s", aData.linePtr[1]->universumPtr->elementPtr[i]->element);
        }
    }
    printf("\n");
    return true;
}
bool unio(const struct tData aData, int par1, int par2){ // A B - tiskne sjednocení množin A a B
    if (aData.linePtr[par1]->relationPtr || aData.linePtr[par2]->relationPtr){      //pokud jeden z radku ukazuje na relace
        return false;
    }
    if (aData.linePtr[par1]->setPtr->elementCount == 0 && aData.linePtr[par2]->setPtr->elementCount == 0){    //pokud jsou prazdne mnoziny
        printf("S");
        return true;
    }
    printf("S");
    if (aData.linePtr[par1]->setPtr->elementCount == 0){       //radek par1 je prazdny -> vytiskne se radek par2
        for (int i = 0; i < aData.linePtr[par2]->setPtr->elementCount; i++){
            printf(" %s", aData.linePtr[par2]->setPtr->elementPtr[i]->element);
        }
    }
    else if (aData.linePtr[par2]->setPtr->elementCount == 0){   //radek par2 je prazdny -> vytiskne se radek par1
        for (int i = 0; i < aData.linePtr[par1]->setPtr->elementCount; i++){
            printf(" %s", aData.linePtr[par1]->setPtr->elementPtr[i]->element);
        }
    }
    if (aData.linePtr[par1]->setPtr->elementCount != 0 && aData.linePtr[par2]->setPtr->elementCount != 0){  //oba radky nejsou prazdne
        for (int i = 0; i < aData.linePtr[par1]->setPtr->elementCount; i++){    //prochazi se radek par1
            printf(" %s", aData.linePtr[par1]->setPtr->elementPtr[i]->element); // vytiskne se element na indexu 'i' a radku par1
        }
        for (int i = 0; i < aData.linePtr[par2]->setPtr->elementCount; i++){    //prochazi se radek par2
            int flag = 0;
            for (int j = 0; j < aData.linePtr[par1]->setPtr->elementCount; j++){    //prochazi se radek par1
                if ((strcmp(aData.linePtr[par1]->setPtr->elementPtr[j]->element, aData.linePtr[par2]->setPtr->elementPtr[i]->element)) == 0){   //pokud se elementy na indexu 'i' (par2) a 'j' (par1) rovnaji
                    flag++;
                    break;
                }
            }
            if (flag == 0){ //pokud se zadny z par1 nerovna s par2 'i'
                printf(" %s", aData.linePtr[par2]->setPtr->elementPtr[i]->element);
            }
        }
    }
    printf("\n");
    return true;
}
bool intersect(const struct tData aData, int par1, int par2){ // tiskne prunik mnozin A B
    printf("S");
    if (aData.linePtr[par1]->relationPtr || aData.linePtr[par2]->relationPtr){  //pokud jeden z radku ukazuje na relace
        return false;
    }
    for (int i = 0; i < aData.linePtr[par1]->setPtr->elementCount; i++){    //prochazi se radek par1
        for (int j = 0; j < aData.linePtr[par2]->setPtr->elementCount; j++){    //prochazi se radek par2
            if (strcmp(aData.linePtr[par1]->setPtr->elementPtr[i]->element, aData.linePtr[par2]->setPtr->elementPtr[j]->element) == 0){ //pokud se elementy na indexu 'i' (par1) a 'j' (par2) rovnaji
                printf(" %s", aData.linePtr[par1]->setPtr->elementPtr[i]->element); //vytiskne se element na radku par1 a indexu 'i'
                break;
            }
        }
    }
    printf("\n");
    return true;
}
bool minus(const struct tData aData, int par1, int par2){ // A B - tiskne rozdíl množin A \ B.
    printf("S");
    if (aData.linePtr[par1]->relationPtr || aData.linePtr[par2]->relationPtr){  //pokud jeden z radku ukazuje na relace
        return false;
    }
    if (aData.linePtr[par1]->setPtr->elementCount == 0){    //pokud je prazdna mnozina na radku par1
        return true;
    }
    if (aData.linePtr[par2]->setPtr->elementCount == 0){    //pokud je prazdna mnozina na radku par2
        for (int i = 0; i < aData.linePtr[par1]->setPtr->elementCount; i++){    //prochazi se radek par1
            printf(" %s", aData.linePtr[par1]->setPtr->elementPtr[i]->element);     //tiskne prvek na indexu 'i' a radku par1
        }
        return true;
    }
    for (int i = 0; i < aData.linePtr[par1]->setPtr->elementCount; i++){    //prochazi se radek par1
        int flag = 0;
        for (int j = 0; j < aData.linePtr[par2]->setPtr->elementCount; j++){    //prochazi se radek par2
            if (strcmp(aData.linePtr[par1]->setPtr->elementPtr[i]->element, aData.linePtr[par2]->setPtr->elementPtr[j]->element) == 0){     //pokud se elementy na indexu 'i' (par1) a 'j' (par2) rovnaji
                flag++;
                break;
            }
        }
        if (flag == 0){ //pokud se zadny z par2 nerovna s par1 'i'
            printf(" %s", aData.linePtr[par1]->setPtr->elementPtr[i]->element);
        }
    }
    printf("\n");
    return true;
}
bool subseteq(const struct tData aData, int par1, int par2){ // A B - tiskne 0 nebo 1 podle toho, jestli je množina A podmnožinou množiny B.
    if (aData.linePtr[par1]->relationPtr || aData.linePtr[par2]->relationPtr){  //pokud jeden z radku ukazuje na relace
        return false;
    }
    if (aData.linePtr[par1]->setPtr->elementCount == 0){    //pokud je prazdna mnozina na radku par1
        printf("true\n");
        return true;
    }
    int flag = 0;
    for (int i = 0; i < aData.linePtr[par1]->setPtr->elementCount; i++){    //prochazi se radek par1
        for (int j = 0; j < aData.linePtr[par2]->setPtr->elementCount; j++){    //prochazi se radek par2
            if (strcmp(aData.linePtr[par1]->setPtr->elementPtr[i]->element, aData.linePtr[par2]->setPtr->elementPtr[j]->element) == 0){   //pokud se elementy na indexu 'i' (par1) a 'j' (par2) rovnaji
                flag++;
                break;
            }
        }
    }
    if (flag < aData.linePtr[par1]->setPtr->elementCount){  //pokud je flag(pocet spolecnych elementu) mensi jak pocet elementu v radku par1
        printf("false\n");
        return true;
    }
    printf("true\n");
    return true;
}
bool subset(const struct tData aData, int par1, int par2){ // A B - tiskne 0 nebo 1, jestli je množina A vlastní podmnožina množiny B.
    if (aData.linePtr[par1]->relationPtr || aData.linePtr[par2]->relationPtr){    //pokud jeden z radku ukazuje na relace
        return false;
    }
    if ((aData.linePtr[par1]->setPtr->elementCount == 0) && (aData.linePtr[par2]->setPtr->elementCount == 0)){  //pokud je prazdna mnozina na radku par1 a par2
        printf("false\n");
        return true;
    }
    if ((aData.linePtr[par1]->setPtr->elementCount == 0) && (aData.linePtr[par2]->setPtr->elementCount != 0)){  //pokud je prazdna mnozina jen na radku par1
        printf("true\n");
        return true;
    }
    int flag = 0;
    for (int i = 0; i < aData.linePtr[par1]->setPtr->elementCount; i++){    //prochazi se radek par1
        for (int j = 0; j < aData.linePtr[par2]->setPtr->elementCount; j++){    //prochazi se radek par2
            if (strcmp(aData.linePtr[par1]->setPtr->elementPtr[i]->element, aData.linePtr[par2]->setPtr->elementPtr[j]->element) == 0){ //pokud se elementy na indexu 'i' (par1) a 'j' (par2) rovnaji
                flag++;
                break;
            }
        }
    }   //pokud je flag(pocet spolecnych elementu) a mene elementu na radku par1 nez na radku par2
    if ((flag == aData.linePtr[par1]->setPtr->elementCount) && (aData.linePtr[par1]->setPtr->elementCount < aData.linePtr[par2]->setPtr->elementCount)){ 
        printf("true\n");
        return true;
    }
    printf("false\n");
    return true;
}
bool equals(const struct tData aData, int par1, int par2){ // A B - tiskne 0 nebo 1, jestli jsou množiny rovny.
    if (aData.linePtr[par1]->relationPtr || aData.linePtr[par2]->relationPtr){  //pokud jeden z radku ukazuje na relace
        return false;
    }
    if ((aData.linePtr[par1]->setPtr->elementCount == 0) && (aData.linePtr[par2]->setPtr->elementCount == 0)){  //pokud je prazdna mnozina na radku par1 a par2
        printf("true\n");
        return true;
    }
    if (aData.linePtr[par1]->setPtr->elementCount == 0 || aData.linePtr[par2]->setPtr->elementCount == 0){  //pokud je prazdna mnozina na radku par1 nebo par2
        printf("false\n");
        return true;
    }
    for (int i = 0; i < aData.linePtr[par1]->setPtr->elementCount; i++){    //prochazi se radek par1
        int flag = 0;
        for (int j = 0; j < aData.linePtr[par2]->setPtr->elementCount; j++){    //prochazi se radek par2
            if (strcmp(aData.linePtr[par1]->setPtr->elementPtr[i]->element, aData.linePtr[par2]->setPtr->elementPtr[j]->element) == 0){    //pokud se elementy na indexu 'i' (par1) a 'j' (par2) rovnaji
                flag++;
                break;
            }
        }
        if (flag == 0){     //pokud se zadny z par2 nerovna s par1 'i'
            printf("false\n");
            return true;
        }
    }
    printf("true\n");
    return true;
}
bool reflexive(const struct tData aData, int par1){ // (a, a) (b, b) (a, c) pro vsechny prvky
    if (aData.linePtr[par1]->setPtr || aData.linePtr[par1]->universumPtr){  //pokud jeden z radku ukazuje na mnozinu nebo univerzum
        return false;
    }
    if (aData.linePtr[par1]->relationPtr->elementRelationCount == 0 && aData.linePtr[1]->universumPtr->elementCount == 0){  //pokud je prazdna relace na radku par1 a prazdne univerzum
        printf("true\n");
        return true;
    }
    bool reflex = false;
    for (int i = 0; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        int flag = 0;   
        if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element) == 0){
            reflex = true;  //pokud se elementy v relaci na prvnim a druhem miste rovnaji
        }
        else if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element) == 1){    //pokud se elementy v relaci na prvnim a druhem miste nerovnaji
            for (int j = 0; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1
                if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element, aData.linePtr[1]->universumPtr->elementPtr[j]->element) == 0){  //pokud se prvek na prvnim miste v relaci na indexu 'i' rovna s prvkem univerza
                    flag++;
                    break;
                }
            }
            if (flag == 0){ //pokud se zadny prvek z univerza nerovna s prvkem na prvnim miste relace 'i'
                printf("false\n");
                return true;
            }
            for (int j = 0; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1
                if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element, aData.linePtr[1]->universumPtr->elementPtr[j]->element) == 0){  //pokud se prvek na druhem miste v relaci na indexu 'i' rovna s prvkem univerza
                    flag++;
                    break;
                }
            }
            if (flag == 0){ //pokud se zadny prvek z univerza nerovna s prvkem na druhem miste relace 'i'
                printf("false\n");
                return true;
            }
            reflex = false;
        }
    }
    if (reflex == true){
        printf("true\n");
        return true;
    }
    printf("false\n");
    return true;
}
bool symmetric(const struct tData aData, int par1){ // pro (a, b) musi byt (b, a)
    if (par1 == 1){
        return false;
    }
    if (aData.linePtr[par1]->setPtr){   //pokud radek ukazuje na mnoziny
        return false;
    }
    if (aData.linePtr[par1]->relationPtr->elementRelationCount == 0 && aData.linePtr[1]->universumPtr->elementCount){   //pokud je prazdna relace na radku par1 a prazdne univerzum
        printf("true\n");
        return true;
    }
    if (aData.linePtr[par1]->relationPtr->elementRelationCount == 0){   //pokud je prazdna pouze relace
        printf("true\n");
        return true;
    }
    int flag = 0;
    for (int i = 0; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        for (int j = i + 1; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1 o jedna vetsi nez index 'i'
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[1]->element) == 0){     //pokud se prvek na prvnim miste z relace na indexu 'i' rovna s prvkem na druhem miste z relace na indexu 'j'
                if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element) == 0){ //pokud se prvek na prvnim miste z relace na indexu 'j' rovna s prvkem na druhem miste z relace na indexu 'i'
                    flag++;
                }
            }
        }
    }
    if (flag == aData.linePtr[par1]->relationPtr->elementRelationCount){    //pokud se flag(pocet symetrickych prvku) rovna poctu relaci
        printf("true\n");
        return true;
    }
    printf("true\n");
    return true;
}
bool antisymmetric(const struct tData aData, int par1){ // pro (a, b) nesmi byt ani jedno (b, a)
    if (par1 == 1){
        return false;
    }
    if (aData.linePtr[par1]->setPtr){   //pokud radek ukazuje na mnoziny
        return false;
    }
    for (int i = 0; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        for (int j = i + 1; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1 o jedna vetsi nez index 'i'
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[1]->element) == 0){     //pokud se prvek na prvnim miste z relace na indexu 'i' rovna s prvkem na druhem miste z relace na indexu 'j'
                if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element) == 0){ //pokud se prvek na prvnim miste z relace na indexu 'j' rovna s prvkem na druhem miste z relace na indexu 'i'
                    printf("false\n");
                    return true;
                }
            }
        }
    }
    printf("true\n");
    return true;
}
bool transitive(const struct tData aData, int par1){ // (a, b)(b, c)(d, a)(a, a)
    if (par1 == 1 || aData.linePtr[par1]->setPtr){  //pokud radek ukazuje na mnoziny
        return false;
    }
    if (aData.linePtr[par1]->relationPtr->elementRelationCount == 0 || aData.linePtr[1]->universumPtr->elementCount == 0){  //pokud je prazdna relace na radku par1 a prazdne univerzum
        printf("true\n");
        return true;
    }
    bool transitive = false;
    for (int i = 0; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        transitive = false;
        for (int j = 0; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[0]->element) == 0){ //pokud se prvek na prvnim miste z relace na indexu 'j' rovna s prvkem na druhem miste z relace na indexu 'i'
                for (int y = 0; y < aData.linePtr[par1]->relationPtr->elementRelationCount; y++){   //prochazi se radek par1
                    if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[y]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element) == 0){ //pokud se prvek na prvnim miste z relace na indexu 'y' rovna s prvkem na druhem miste z relace na indexu 'i'
                        if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[y]->elementPtr[1]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[1]->element) == 0){ //pokud se prvek na prvnim miste z relace na indexu 'y' rovna s prvkem na prvnim miste z relace na indexu 'j'
                            transitive = true;
                        }
                    }
                }
            }
        }
    }
    if (transitive == true){
        printf("true\n");
        return true;
    }
    printf("false\n");
    return true;
}
bool function(const struct tData aData, int par1){ // tiskne jestli je funkce opravdu funkce (nemohou byt 2 stejne x)
    if (par1 == 1 || aData.linePtr[par1]->setPtr){  //pokud radek ukazuje na mnoziny nebo univerzum
        return false;
    }
    for (int i = 0; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        for (int j = i + 1; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1 o jedna vetsi nez index 'i'
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[0]->element) == 0){ //pokud se prvek na prvnim miste z relace na indexu 'i' rovna s prvkem na prvnim miste z relace na indexu 'j'
                printf("false\n");
                return true;
            }
        }
    }
    printf("true\n");
    return true;
}
bool domain(const struct tData aData, int par1){ //tisken definicni obor funkce - vsechny prvky x (x, y)(y, c)(x, a)(z, c)
    if (par1 == 1 || aData.linePtr[par1]->setPtr || aData.linePtr[par1]->universumPtr){ //pokud radek ukazuje na mnoziny nebo univerzum
        return false;
    }
    printf("S");
    if (aData.linePtr[par1]->relationPtr->elementRelationCount == 0){   //pokud je prazdna relace
        return true;
    }
    printf(" %s", aData.linePtr[par1]->relationPtr->elementRelationPtr[0]->elementPtr[0]->element); // tiskne se prvni prvek z prvni relace
    for (int i = 1; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        int flag = 0;
        for (int j = i - 1; j >= 0; j--){   //prochazi se predchazejici prvky
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[0]->element) == 0){ //pokud se prvni prvek z relace na indexu 'i' rovna s prvnim prvkem na indexu 'j'
                flag++;
                break;
            }
        }
        if (flag == 0){ //pokud se nenasel stejny prvek jako na prvnim miste relace na indexu 'i'
            printf(" %s", aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element);
        }
    }
    printf("\n");
    return true;
}
bool codomain(const struct tData aData, int par1){ //tiskne obor hodnot funkce - vsechny prvky y (x, y)(y, c)(x, a)(z, c)
    if (par1 == 1 || aData.linePtr[par1]->setPtr || aData.linePtr[par1]->universumPtr){  //pokud radek ukazuje na mnoziny nebo univerzum
        return false;
    }
    printf("S");
    if (aData.linePtr[par1]->relationPtr->elementRelationCount == 0){   //pokud je prazdna relace
        return true;
    }
    printf(" %s", aData.linePtr[par1]->relationPtr->elementRelationPtr[0]->elementPtr[1]->element); // tiskne se druhy prvek z prvni relace
    for (int i = 1; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        int flag = 0;
        for (int j = i - 1; j >= 0; j--){   //prochazi se predchazejici prvky
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[1]->element) == 0){ //pokud se druhy prvek z relace na indexu 'i' rovna s druhym prvkem na indexu 'j'
                flag++;
                break;
            }
        }
        if (flag == 0){ //pokud se nenasel stejny prvek jako na druhem miste relace na indexu 'i'
            printf(" %s", aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element);
        }
    }
    printf("\n");
    return true;
}
bool injective(const struct tData aData, int par1){ //0 nebo 1 jestli je relace injektivni
    for (int i = 0; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        for (int j = i + 1; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1 o jedna vetsi nez index 'i'
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[0]->element) == 0){ //pokud se prvni prvek z relace na indexu 'i' rovna s prvnim prvkem na indexu 'j'
                return false;
            }
        }
    }
    for (int i = 0; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        for (int j = i + 1; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1 o jedna vetsi nez index 'i'
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[1]->element) == 0){ //pokud se druhy prvek z relace na indexu 'i' rovna s druhym prvkem na indexu 'j'
                return false;
            }
        }
    }
    return true;
}
bool surjective(const struct tData aData, int par1){
    for (int i = 0; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        for (int j = i + 1; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1 o jedna vetsi nez index 'i'
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[1]->element) == 0){ //pokud se druhy prvek z relace na indexu 'i' rovna s druhym prvkem na indexu 'j'
                return false;
            }
        }
    }
    return true;
}
bool bijective(const struct tData aData, int par1){ //0 nebo 1 jestli je relace bijektivni (1 a)(2 b)(3 c)(4 d)
    for (int i = 0; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        for (int j = i + 1; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1 o jedna vetsi nez index 'i'
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[0]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[0]->element) == 0){ //pokud se prvni prvek z relace na indexu 'i' rovna s prvnim prvkem na indexu 'j'
                return false;
            }
        }
    }
    for (int i = 0; i < aData.linePtr[par1]->relationPtr->elementRelationCount; i++){   //prochazi se radek par1
        for (int j = i + 1; j < aData.linePtr[par1]->relationPtr->elementRelationCount; j++){   //prochazi se radek par1 o jedna vetsi nez index 'i'
            if (strcmp(aData.linePtr[par1]->relationPtr->elementRelationPtr[i]->elementPtr[1]->element, aData.linePtr[par1]->relationPtr->elementRelationPtr[j]->elementPtr[1]->element) == 0){ //pokud se druhy prvek z relace na indexu 'i' rovna s druhym prvkem na indexu 'j'
                return false;
            }
        }
    }
    return true;
}
void freeData(struct tData* aDataPtr) { //FUNKCE PRO ODALOKOVANI DAT
    for (int i = 1; i < aDataPtr->lineCount; i++) {
        if (i == 1) {
            for (int u = 0; u < aDataPtr->linePtr[1]->universumPtr->elementCount; ++u) { //ODALOKACE UNIVERZA
                free(aDataPtr->linePtr[1]->universumPtr->elementPtr[u]);
            }
            free(aDataPtr->linePtr[1]->universumPtr);
            free(aDataPtr->linePtr[1]);
        }
        else
        {
            if (aDataPtr->linePtr[i]->setPtr) { //ODALOKACE MNOZINY
                for (int s = 0; s < aDataPtr->linePtr[i]->setPtr->elementCount; ++s) {
                    free(aDataPtr->linePtr[i]->setPtr->elementPtr[s]);
                }
                free(aDataPtr->linePtr[i]->setPtr);
                free(aDataPtr->linePtr[i]);
            }
            else if (aDataPtr->linePtr[i]->relationPtr) { //ODALOKACE RELACE
                for (int r = 0; r < aDataPtr->linePtr[i]->relationPtr->elementRelationCount; ++r) {
                    free(aDataPtr->linePtr[i]->relationPtr->elementRelationPtr[r]->elementPtr[0]);
                    free(aDataPtr->linePtr[i]->relationPtr->elementRelationPtr[r]->elementPtr[1]);
                    free(aDataPtr->linePtr[i]->relationPtr->elementRelationPtr[r]);
                }
                free(aDataPtr->linePtr[i]->relationPtr);
                free(aDataPtr->linePtr[i]);
            }
        }
    }
    free(aDataPtr->linePtr);
}
void printData(struct tData *aDataPtr){ //FUNKCE PRO TISK DAT
    for (int i = 1; i < aDataPtr->lineCount; i++){
        if (i == 1){
            printf("U"); //tisteni U
            for (int u = 0; u < aDataPtr->linePtr[1]->universumPtr->elementCount; ++u)
            {
                printf(" %s", aDataPtr->linePtr[1]->universumPtr->elementPtr[u]->element);
            }
            printf("\n");
        }
        else{
            if (aDataPtr->linePtr[i]->setPtr){
                printf("S"); //tisteni S
                for (int s = 0; s < aDataPtr->linePtr[i]->setPtr->elementCount; ++s){
                    printf(" %s", aDataPtr->linePtr[i]->setPtr->elementPtr[s]->element);
                }
                printf("\n");
            }
            if (aDataPtr->linePtr[i]->relationPtr){
                printf("R"); //tisteni R
                for (int r = 0; r < aDataPtr->linePtr[i]->relationPtr->elementRelationCount; ++r){
                    printf(" (%s ", aDataPtr->linePtr[i]->relationPtr->elementRelationPtr[r]->elementPtr[0]->element);
                    printf("%s)", aDataPtr->linePtr[i]->relationPtr->elementRelationPtr[r]->elementPtr[1]->element);
                }
                printf("\n");
            }
        }
    }
}
bool readData(FILE *aFsrc, struct tData *aDataPtr){ //FUNKCE PRO CTENI DAT
    if (!aFsrc || !aDataPtr){ //kontrola pradanych parametru
        return false;
    }
    char firstChar;
    fscanf(aFsrc, "%c", &firstChar);
    if (firstChar != 'U'){
        fprintf(stderr, "Zadne univerzum.\n");
        return false;
    }
    int lineCount = 1;
    struct tLine **linePtrAlloc = calloc(1, sizeof(struct tLine));
    aDataPtr->capacity = 1;
    struct tUniversum *universum = calloc(1, sizeof(struct tUniversum));
    universum->capacity = 1;
    while (firstChar != 'C' && firstChar != ' ' && firstChar != '\n'){
        struct tLine *line = calloc(1, sizeof(struct tLine));
        if (lineCount + 1 >= aDataPtr->capacity){   //pokud se pocet radku + 1 rovna kapacite, tak zdvojnasobime kapacitu
            linePtrAlloc = realloc(linePtrAlloc, 2 * aDataPtr->capacity * sizeof(struct tLine));    //a realokujeme data
            aDataPtr->capacity = 2 * aDataPtr->capacity;
        }
        if (firstChar == 'U'){  //cteni radku s universem
            if (EOF == (fscanf(aFsrc, "%c", &firstChar)))
                fprintf(stderr, "Chyba.\n");

            if (firstChar != ' ' && firstChar != '\n'){
                fprintf(stderr, "Za U nenasleduje mezera!");
                return false;
            }
            int elementCount = 0;
            while (firstChar == ' '){
                if (elementCount + 1 >= universum->capacity){
                    universum->elementPtr = realloc(universum->elementPtr, 2 * universum->capacity * sizeof(struct tElement));
                    universum->capacity = 2 * universum->capacity;
                }
                struct tElement *dataCalloc = calloc(1, sizeof(struct tElement));
                fscanf(aFsrc, "%s", (dataCalloc->element));
                for (int i = 0; dataCalloc->element[i] != '\0'; i++){
                    if (i >= 30){
                        fprintf(stderr, "Moc dlouhy element.\n");
                        return false;
                    }
                }
                for (int i = 0; dataCalloc->element[i] != '\0'; i++){
                    if (!((dataCalloc->element[i] >= 'A' && dataCalloc->element[i] <= 'Z') || (dataCalloc->element[i] >= 'a' && dataCalloc->element[i] <= 'z') || (dataCalloc->element[i] == 32))){
                        fprintf(stderr, "Chyba v zadani univerza.\n");
                        return false;
                    }
                }
                if (!strcmp(dataCalloc->element, "true") || !strcmp(dataCalloc->element, "false") || !strcmp(dataCalloc->element, "empty") || !strcmp(dataCalloc->element, "card") || !strcmp(dataCalloc->element, "complement") || !strcmp(dataCalloc->element, "unio") || !strcmp(dataCalloc->element, "intersect") || !strcmp(dataCalloc->element, "minus") || !strcmp(dataCalloc->element, "subseteq") || !strcmp(dataCalloc->element, "subset") || !strcmp(dataCalloc->element, "equals") || !strcmp(dataCalloc->element, "reflexive") || !strcmp(dataCalloc->element, "symmetric") || !strcmp(dataCalloc->element, "antisymmetric") || !strcmp(dataCalloc->element, "transitive") || !strcmp(dataCalloc->element, "function") || !strcmp(dataCalloc->element, "domain") || !strcmp(dataCalloc->element, "codomain") || !strcmp(dataCalloc->element, "injective") || !strcmp(dataCalloc->element, "surjective") || !strcmp(dataCalloc->element, "bijective")){
                    fprintf(stderr, "Chyba univerza.\n");
                    return false;
                }
                universum->elementPtr[elementCount] = dataCalloc;
                elementCount += 1;
                universum->elementCount = elementCount;
                if (EOF == (fscanf(aFsrc, "%c", &firstChar)))
                    return false;
            }
            line->universumPtr = universum;
            linePtrAlloc[lineCount] = line;
            aDataPtr->linePtr = linePtrAlloc;
            lineCount += 1;
        }
        if (firstChar == 'S'){  //cteni radku s mnozinami
            struct tSet *set = calloc(1, sizeof(struct tSet));
            set->capacity = 1;  //prvotni nastaveni kapacity mnoziny
            fscanf(aFsrc, "%c", &firstChar);
            if (firstChar != ' ' && firstChar != '\n'){
                fprintf(stderr, "Za S nenasleduje mezera!");
                return false;
            }
            int elementCount = 0;
            if (firstChar == '\n'){
                set->elementCount = 0;
            }
            while (firstChar == ' '){
                if (elementCount + 1 >= set->capacity) {
                    set->elementPtr = realloc(set->elementPtr, 2 * set->capacity * sizeof(struct tElement));
                    set->capacity = 2 * set->capacity;
                }
                struct tElement *dataCalloc = calloc(1, sizeof(struct tElement));
                fscanf(aFsrc, "%s", (dataCalloc->element));
                set->elementPtr[elementCount] = dataCalloc;
                elementCount += 1;
                set->elementCount = elementCount;
                fscanf(aFsrc, "%c", &firstChar);
            }
            line->setPtr = set;
            line->relationPtr = NULL; //pro jistotu, pri naslednem tisteni
            linePtrAlloc[lineCount] = line;
            aDataPtr->linePtr = linePtrAlloc;
            lineCount += 1;
        }
        if (firstChar == 'R'){  //cteni radku s relacemi
            struct tRelation *relation = calloc(1, sizeof(struct tUniversum));
            relation->capacity = 1; //prvotni nastaveni kapacity relace
            fscanf(aFsrc, "%c", &firstChar);
            if (firstChar != ' ' && firstChar != '\n'){
                fprintf(stderr, "Za R nenasleduje mezera!");
                return false;
            }
            int elementRelationCount = 0;
            if (elementRelationCount + 1 >= relation->capacity){
                relation->elementRelationPtr = realloc(relation->elementRelationPtr, 2 * relation->capacity * sizeof(struct tElementRelation));
                relation->capacity = 2 * relation->capacity;
            }
            if (firstChar == '\n'){
                relation->elementRelationCount = 0;
            }
            while (firstChar == ' '){
                struct tElement *dataCalloc1 = calloc(1, sizeof(struct tElement));
                struct tElement *dataCalloc2 = calloc(1, sizeof(struct tElement));
                struct tElementRelation *elementRelationPtr = calloc(1, sizeof(struct tElementRelation));
                fscanf(aFsrc, "(%s", (dataCalloc1->element));
                fscanf(aFsrc, " %s)", (dataCalloc2->element));
                for (size_t i = 0; i < 31; ++i){
                    if (dataCalloc2->element[i] == ')'){
                        dataCalloc2->element[i] = '\0';
                        break;
                    }
                }
                elementRelationPtr->elementPtr[0] = dataCalloc1;
                elementRelationPtr->elementPtr[1] = dataCalloc2;
                relation->elementRelationPtr[elementRelationCount] = elementRelationPtr;
                elementRelationCount += 1;
                relation->elementRelationCount = elementRelationCount;
                fscanf(aFsrc, "%c", &firstChar);
            }
            line->relationPtr = relation;
            line->setPtr = NULL; //pro jistotu, pri naslednem tisteni
            linePtrAlloc[lineCount] = line;
            aDataPtr->linePtr = linePtrAlloc;
            lineCount += 1;
        }
        firstChar = fgetc(aFsrc);
        if (firstChar == EOF){
            printData(aDataPtr);
            fprintf(stderr, "Pouze univerzum.");
            return false;
        }
    }
    aDataPtr->lineCount = lineCount;
    if (lineCount > 1000){
        fprintf(stderr, "Moc radku.\n");
        return false;
    }
    printData(aDataPtr); //TISTENI VSTUPNICH DAT
    while (firstChar == 'C'){   //cteni radku s commandy
        firstChar = fgetc(aFsrc);
        if (firstChar != ' '){
            fprintf(stderr, "Za prikazem nenasleduje mezera!");
            return false;
        }
        char command[20];
        int par1 = 0, par2 = 0, par3 = 0;
        fscanf(aFsrc, "%s", command);
        fscanf(aFsrc, "%d", &par1);
        fscanf(aFsrc, "%d", &par2);
        fscanf(aFsrc, "%d", &par3);
        if ((strcmp(command, "bijective") != 0) && par3){   //CTENI COMMANDU
            fprintf(stderr, "Chyba, moc parametru.\n");
            return false;
        }
        if (par1 > (aDataPtr->lineCount)){
            fprintf(stderr, "Parametr na nexistujici radek");
            return false;
        }
        if (par2 > (aDataPtr->lineCount)){
            fprintf(stderr, "Parametr na nexistujici radek");
            return false;
        }
        if (par3 > (aDataPtr->lineCount)){
            fprintf(stderr, "Parametr na nexistujici radek");
            return false;
        }
        if (strcmp(command, "empty") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!empty(*aDataPtr, par1)){
                    fprintf(stderr, "Prikaz empty na relaci.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "card") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru\n");
                return false;
            }
            else{
                if (!card(*aDataPtr, par1)){
                    fprintf(stderr, "Prikaz card na relaci.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "complement") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru\n");
                return false;
            }
            else{
                if (!complement(*aDataPtr, par1)){
                    fprintf(stderr, "Complement nemuze ukazovat na relace.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "union") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru\n");
                return false;
            }
            else if (!par2){
                fprintf(stderr, "Chybny pocet parametru\n");
                return false;
            }
            else{
                if (!unio(*aDataPtr, par1, par2)){
                    fprintf(stderr, "Nemuze ukazovat na relaci.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "intersect") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else if (!par2){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!intersect(*aDataPtr, par1, par2)){
                    fprintf(stderr, "Nemuze ukazovat na relaci.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "minus") == 0){
            if (!par1 || !par2){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!minus(*aDataPtr, par1, par2)){
                    fprintf(stderr, "Nemuze ukazovat na relace.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "subseteq") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else if (!par2){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!subseteq(*aDataPtr, par1, par2)){
                    fprintf(stderr, "Nemuze ukazovat na relace.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "subset") == 0){
            if (!par1 || !par2){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!subset(*aDataPtr, par1, par2)){
                    fprintf(stderr, "Nemuze ukazovat na relace.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "equals") == 0){
            if (!par1 || !par2){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!equals(*aDataPtr, par1, par2)){
                    fprintf(stderr, "Nemuze ukazovat na relace.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "reflexive") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!reflexive(*aDataPtr, par1)){
                    fprintf(stderr, "Error.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "symmetric") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!symmetric(*aDataPtr, par1)){
                    fprintf(stderr, "Error.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "antisymmetric") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!antisymmetric(*aDataPtr, par1)){
                    fprintf(stderr, "Error.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "transitive") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!transitive(*aDataPtr, par1)){
                    fprintf(stderr, "Error.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "function") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!function(*aDataPtr, par1)){
                    fprintf(stderr, "Error.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "domain") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!domain(*aDataPtr, par1)){
                    fprintf(stderr, "Error.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "codomain") == 0){
            if (!par1){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (!codomain(*aDataPtr, par1)){
                    fprintf(stderr, "Error.\n");
                    return false;
                }
            }
        }
        else if (strcmp(command, "injective") == 0){
            if (!par1 || !par2 || !par3){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (injective(*aDataPtr, par1))
                    printf("true\n");
                else
                    printf("false\n");
            }
        }
        else if (strcmp(command, "surjective") == 0){
            if (!par1 || !par2 || !par3){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (surjective(*aDataPtr, par1))
                    printf("true\n");
                else
                    printf("false\n");
            }
        }
        else if (strcmp(command, "bijective") == 0){
            if (!par1 || !par2 || !par3){
                fprintf(stderr, "Chybny pocet parametru");
                return false;
            }
            else{
                if (bijective(*aDataPtr, par1))
                    printf("true\n");
                else
                    printf("false\n");
            }
        }
        if (EOF == (fscanf(aFsrc, "%c", &firstChar)))
            return true;

        if (firstChar == 'S' || firstChar == 'U' || firstChar == 'R'){
            fprintf(stderr, "po prikazu nasleduje definice mnoziny");
            return false;
        }
    }
    return true;
}
int main(int argc, char *argv[]){   //MAIN FUNKCE
    if (argc != 2){
        fprintf(stderr, "Nebyl zadan nazev suboru.");
        return 1;
    }
    FILE *fsrc = fopen(argv[1], "r");
    if (!fsrc){
        fprintf(stderr, "Nelze otevrit soubor: %s\n", argv[1]);
        return 2;
    }
    struct tData data = {.linePtr = NULL, .lineCount = 0};
    if (!readData(fsrc, &data)){
        freeData(&data);    //odalokovani dat po chybnem cteni
        fprintf(stderr, "Chyba dat.\n");
        return 3;
    }
    freeData(&data);    //odalokovani dat
    fclose(fsrc);   //uzavreni vstupniho souboru
    return 0;
}
