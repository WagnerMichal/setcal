#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Funkce na porovnani dvou retezcu. Prochazi retezce a pokud jsou rozdilne vrati false
bool my_strcmp(char *str_1, char *str_2)
{
    for (int i = 0; str_1[i] != '\0' || str_2[i] != '\0'; i++)
    {
        if (str_1[i] != str_2[i])
        {
            return false;
        }
    }
    return true;
}
//Funkce pouze pro vypis statistik
void stats(int minimum, int unique_chars, float avg)
{
    printf("Statistika:\n");
    printf("Ruznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", unique_chars, minimum, avg);
}
bool level_1(char *arr)
{
    int count_low = 0;
    int count_caps = 0;
    //Prochazeni hesla po znaku aĹž do '\0'
    for (int i = 0; arr[i] != '\0'; i++)
    {
        //Pokud je znak z intervalu 'a' az 'z' pricte se jednicka do count_low
        if (arr[i] >= 'a' && arr[i] <= 'z')
        {
            count_low++;
        }
        //Pokud je znak z intervalu 'A' az 'Z' pricte se jednicka do count_caps
        else if (arr[i] >= 'A' && arr[i] <= 'Z')
        {
            count_caps++;
        }
    }
    //Pokud jsou promenne count_caps a count_low vetsi nez nula, tak heslo projde levelem jedna
    if (count_caps > 0 && count_low > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool level_2(char *arr, long param)
{
    int count_caps = 0;
    int count_low = 0;
    int count_numbers = 0;
    int count_others = 0;
    //Cyklus, ktery prochazi heslo po znaku a pricita jednicku k count_low, count_caps, count_numbers a count_others pokud se znak nachazi v dane skupine
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] >= 'a' && arr[i] <= 'z')
        {
            count_low++;
        }
        else if (arr[i] >= 'A' && arr[i] <= 'Z')
        {
            count_caps++;
        }
        else if (arr[i] >= '0' && arr[i] <= '9')
        {
            count_numbers++;
        }
        else if ((arr[i] >= ' ' && arr[i] <= '/') || (arr[i] >= ':' && arr[i] <= '@') || (arr[i] >= '[' && arr[i] <= '`') || (arr[i] >= '{' && arr[i] <= '~'))
        {
            count_others++;
        }
    }
    //Pokud je zadan parametr jedna, tak se kontroluje zda je jedna z promenne vetsi jak nula. Pokud ano tak heslo proslo.
    if (param == 1)
    {
        if (count_low > 0 || count_caps > 0 || count_numbers > 0 || count_others > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //Pokud je zadan parametr dva, tak se kontroluje zda jsou dve promenne vetsi jak nula. Pokud ano tak heslo proslo.
    else if (param == 2)
    {
        if ((count_low > 0 && count_caps > 0) || (count_low > 0 && count_numbers > 0) || (count_low > 0 && count_others > 0) ||
            (count_caps > 0 && count_numbers > 0) || (count_caps > 0 && count_others > 0) || (count_numbers > 0 && count_others > 0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //Pokud je zadan parametr tri, tak se kontroluje zda jsou tri promenne vetsi jak nula. Pokud ano tak heslo proslo.
    else if (param == 3)
    {
        if ((count_low > 0 && count_numbers > 0 && count_caps > 0) || (count_low > 0 && count_numbers > 0 && count_others > 0) ||
            (count_low > 0 && count_caps > 0 && count_others > 0) || (count_caps > 0 && count_numbers > 0 && count_others > 0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //Pokud je zadan parametr ctyri a vice, tak se kontroluje zda jsou ctyri promenne vetsi jak nula. Pokud ano tak heslo proslo.
    else if (param >= 4)
    {
        if (count_low > 0 && count_caps > 0 && count_numbers > 0 && count_others > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
bool level_3(char *arr, long param)
{
    //Pokud je parametr jedna, tak level_3 bere kazdy znak jako chybu
    if (param == 1)
    {
        return false;
    }
    //Promenna pro pocitani zda se znak opakuje. Je nastavena na hodnotu jedna, protoze prvni stejny znak, ktery porovnava nezapocita do sekvence stejnych znaku
    int same_chars = 1;
    //Prochazime heslo od indexu i = 0 do znaku '\0'
    for (int i = 0; arr[i] != '\0'; i++)
    {
        //Prochazime heslo od indexu y = i + 1 tudiz o jedno vetsi jak index i do znaku '\0'
        for (int y = i + 1; arr[y] != '\0'; y++)
        {
            //Pokud se znaky rovnaji, tak se do promenne same_chars pricte jednicka
            if (arr[i] == arr[y])
            {
                same_chars++;
                //Pokud je hodnota same_chars stejna jak parametr znamena to, ze se v hesle nachazi sekvence stejnych znaku a vrati false
                if (same_chars == param)
                {
                    return false;
                }
                break;
            }
            //Pokud se znaky nerovnaji, tak podminka posle break a cyklus pokracuje
            else if (arr[i] != arr[y])
            {
                break;
            }
        }
    }
    return true;
}

bool level_4(char *arr, long param)
{
    //Pole pro ulozeni substringu o delce parametru
    char compare_first[param];
    char compare_second[param];
    //pomocne promenne
    int second_index = 0, first_index = 0, bump = 0;
    //Prochazime heslo a ukladame do compare_first od indexu i pocet znaku podle poctu parametru do '\0'
    for (int i = 0; first_index < param && arr[i] != '\0'; i++)
    {
        //ulozime znak na first_index a zvedneme first_index o hodnotu jedna
        compare_first[first_index] = arr[i];
        first_index++;
        //pokud je v poli stejny pocet znaku jako velikost parametru zacne druhy cyklus
        if (first_index == param)
        {
            //prochazime heslo a ukladame do compare_second od indexu y = bump + 1 pocet znaku podle poctu parametru do '\0'
            for (int y = bump + 1; second_index < param && arr[y] != '\0'; y++)
            {
                //ulozime znak na second_index a zvedneme second_index o hodnotu jedna
                compare_second[second_index] = arr[y];
                second_index++;
                //pokud je v poli stejny pocet znaku jako velikost parametru zacne dalsi cyklus
                if (second_index == param)
                {
                    //promenna pro urceni poctu stejnych znaku
                    int flag = 0;
                    //prochazime compare_first a compare_second
                    for (int j = 0; compare_first[j] != '\0' && compare_second[j] != '\0'; j++)
                    {
                        //pokud se znak na indexu j v poli compare_first a compare_second rovna, tak se pricte jednicka do promenne flag
                        if (compare_first[j] == compare_second[j])
                        {
                            flag++;
                            //pokud je hodnota promenne flag vetsi nebo rovna hodnote parametru znamena to, ze v hesle se nachazi podretezec a funkce vrati false
                            if (flag >= param)
                            {
                                return false;
                            }
                        }
                    }
                    //cyklus, ktery prochazi pole compare_second a vymaze znaky, ktere se zde nachazi
                    for (int delete = 0; compare_second[delete] != '\0'; delete ++)
                    {
                        compare_second[delete] = 0;
                    }
                    //vratime index na hodnotu nula
                    second_index = 0;
                    //potreba pocitat s vnorenou dvojici, tudiz musime index vratit na pozici vnorenou do compare_first
                    //(pĹ.: parametr = 3, compare_first bude obsahovat znaky na indexu [O],[1],[2] a compare_second znaky na indexu [1],[2],[3])
                    //cyklus skonci na hodnote y = 3 a zacal by na hodnote 4, tudiz 3 = 3 - (2) => 1 a cyklus zacne na indexu 2
                    y = y - (param - 1);
                }
            }
        }
        //az dojdeme v cyklu pro pole compare_second k znaku '\0' zacne tato podminka
        if (first_index == param)
        {
            //cyklus, ktery prochazi pole compare_first a vymaze znaky, ktere se zde nachazi
            for (int delete = 0; compare_first[delete] != '\0'; delete ++)
            {
                compare_first[delete] = 0;
            }
            //cyklus pro compare_second musi zacit na hodnote o jedna vetsi nez pro compare_first
            //bez teto promenne by mohlo dojit k porovnavani stejnych indexu
            bump++;
            //potreba pocitat s vnorenou dvojici i u pole compare_first
            i = i - (param - 1);
            //vratime oba indexy na hodnotu nula pro pripad, kdy by se cyklus pro pole compare_second ukoncil drive skrz nedostatek znaku
            first_index = 0;
            second_index = 0;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    (void)argc; //counter argumentĹŻ
    (void)argv; //argument

    int level;          //level
    long param;         //parametr
    char password[102]; //string pro uloĹženĂ­ hesla

    //PromÄnnĂŠ pro statistiku
    int unique_char = 0, minimum = 120, position = 0;
    float avg, length_all = 0.0, password_count = 0.0;
    bool statistics = false;
    char unique_chars[101] = {};

    //Pokud je argc jedna nebo dva znamena to, ze chybi zadany level nebo i parametr -> vyhodi se error
    if (argc == 1 || argc == 2)
    {
        fprintf(stderr, "Nedostatek parametru");
        return 1;
    }
    //Pokud je argc vetsi jak dva znamena to, ze obsahuje minimĂĄlne nazev, level a parametr
    if (argc > 2)
    {
        //Cyklus, ktery pricita jednicku do promenne i az do velikosti argc
        for (int i = 1; i < argc; i++)
        {
            //na prvni pozici argv je level, tudiz se pomoci funkce my_strcmp porovnaji stringy a pokud jsou stejne tak se hodnota nahraje do promenne level
            if (i == 1)
            {
                if (my_strcmp(argv[i], "1") == true)
                {
                    level = 1;
                }
                else if (my_strcmp(argv[i], "2") == true)
                {
                    level = 2;
                }
                else if (my_strcmp(argv[i], "3") == true)
                {
                    level = 3;
                }
                else if (my_strcmp(argv[i], "4") == true)
                {
                    level = 4;
                }
                else
                {
                    //pokud je v argv[1] zadana hodnota jina nez z intervalu <1;4> -> error
                    fprintf(stderr, "Spatne zadany level - pouzij <1,4>\n");
                    return 1;
                }
            }
            //na druhe pozici argv je parametr, tudiz se pomoci funkce atoi vezme pouze ciselna hodnota a nahraje se do promenne param,
            //pokud je hodnota promenne param mensi nebo rovna nule, tak se vyhodĂ­ error
            if (i == 2)
            {
                param = atoi(argv[2]);
                if (param <= 0)
                {
                    fprintf(stderr, "Parametr musi byt kladne cele cislo\n");
                    return 1;
                }
            }
            //na treti pozici se nachazi --stats, do stringu stats je nahrana podoba v jake ma byt zapsana. Pomoci funkce my_strcmp zjistim zda se sring
            //na vstupu rovna stringu stats pokud ano tak se bool statistics zmeni na true a pozdÄji se vytisknou. Pokud ne tak se hodi error - chybne zapsano
            if (i == 3)
            {
                char *stats = "--stats";
                if (my_strcmp(stats, argv[i]) == true)
                {
                    statistics = true;
                }
                else
                {
                    fprintf(stderr, "chybne zapsana statistika");
                    return 1;
                }
            }
            if (i >= 4) //Pokud je na vstupu vice parametru nez muĹže byt vyhodi se error
            {
                fprintf(stderr, "Prekrocen maximalni pocet argumentu\n");
                return 1;
            }
        }
    }
    //nacitani z textoveho souboru
    while (fgets(password, 102, stdin) != NULL)
    {
        //dalsi promenne pro statistiky
        float length = 0.0;
        char compare;

        //cyklus pro prochazeni kazdeho hesla po znaku, ktery po kazdem projiti pricte jednicku do promenne length
        for (int i = 0; password[i] != '\0' && password[i] != '\n'; i++)
        {
            length++;
        }
        //pokud je delka hesla vetsi, jak povolena hodnota 100, tak se vyhodi error
        if (length > 100.0)
        {
            fprintf(stderr, "Prekrocena velikost hesla");
            return 1;
        }
        //delku kazdeho hesla porovnam s nejmensim heslem a pokud je mensi, tak se do promenne minimum nahraje nova nejmensi delka
        if ((int)length < minimum)
        {
            minimum = (int)length;
        }
        //prictu delku hesla do promenne pro delku vsech hesel
        length_all += length;

        //cyklus, ktery prochazi kazde heslo a hleda unikatni znaky
        for (int i = 0; password[i] != '\0' && password[i] != '\n'; i++)
        {
            //do promenne compare si nahraju znak z hesla na indexu i
            compare = password[i];
            //pomocnĂĄ promenna pro urceni zda se znak nachazi v poli unique_chars
            int flag = 1;
            //prochazim pole unique_chars az do '\0'
            for (int y = 0; unique_chars[y] != '\0'; y++)
            {
                //pokud se znak na indexu y rovna znaku compare, tak se zmeni flag na 0
                if (unique_chars[y] == compare)
                {
                    flag = 0;
                    break;
                }
            }
            //pokud flag zustane na hodnote 1 znamena to, ze znak se v poli unique_chars nenachazi
            if (flag == 1)
            {
                //znak se do unique_chars zapise a zvedne se pocet unikatnich znaku a index pozice pro pole unique_chars
                unique_chars[position] = compare;
                unique_char++;
                position++;
            }
        }
        //zvedne se pocet projitych hesel
        password_count++;

        //Pokud je na vstupu level 1, tak se kontroluje zda funkce level_1 prosla a vyhodila true, pokud ano vytiskne se heslo
        if (level == 1)
        {
            if (level_1(password) == true)
            {
                printf("%s", password);
            }
        }
        //Pokud je na vstupu level 2, tak se zkontroluje zda heslo proslo funkci level_1, pokud ano, tak se provede funkce level_2 a popripade se vytiskne heslo
        else if (level == 2)
        {
            if (level_1(password) == true)
            {
                if (level_2(password, param) == true)
                {
                    printf("%s", password);
                }
            }
        }
        //Pokud je na vstupu level 3, tak se zkontroluje zda heslo proslo funkci level_1 a level_2, pokud ano, tak se provede funkce level_3 a popripade se vytiskne heslo
        else if (level == 3)
        {
            if (level_1(password) == true)
            {
                if (level_2(password, param) == true)
                {
                    if (level_3(password, param) == true)
                    {
                        printf("%s", password);
                    }
                }
            }
        }
        //Pokud je na vstupu level 4, tak se zkontroluje zda heslo proslo funkci level_1, level_2 a level_3, pokud ano, tak se provede funkce level_4 a popripade se vytiskne heslo
        else if (level == 4)
        {
            if (level_1(password) == true)
            {
                if (level_2(password, param) == true)
                {
                    if (level_3(password, param) == true)
                    {
                        if (level_4(password, param) == true)
                        {
                            printf("%s", password);
                        }
                    }
                }
            }
        }
    }
    //Pokud je statistics true vypocita se avg pomoci celkove delky vsech hesel a poctu hesel. Pote se pomoce funkce stats vytisknou statistiky
    if (statistics == true)
    {
        avg = length_all / password_count;
        stats(minimum, unique_char, avg);
    }
    return 0;
}