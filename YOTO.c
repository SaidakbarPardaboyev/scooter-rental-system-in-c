#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <dirent.h>

#define BST (+5)

const float priceOfUseSkuter = 1699.99;

typedef struct{
    char username[100];
    char password[100];
}User;

typedef struct{
    char username[100];
    char password[100];
    char name[100];
    char surname[100];
    char phoneNumber[100];
    char ID_NUMBER[100];
    double balance;
}FillDataBase;

typedef struct{
    char username[100];
    char password[100];
    char name[100];
    char surname[100];
    char phoneNumber[100];
    char ID_NUMBER[100];
}ForAdmin;

void LoginOrRegister(User* odam, char UserAppID[], FillDataBase* New, char* exist);
bool UserTrue(User* odam, char temPass[], char UserAppID[]);
void NewUser(FillDataBase* New, char NewUserIDNumber[]);
void AddUserToDataBase(FillDataBase* New, char NewUserIDNumber[]);
void CreateNewUserDir(FillDataBase* New, char NewUserIDChar[]);
int FindNewUserId();
void AddUserInfoIntoUserDir(FillDataBase* New);
void putDepositeWhileRegister(FillDataBase* New);
bool IsCardNumberTrue(char cardNumber[]);
void mainMenyu(FillDataBase* curUser, char* UserAppID, char* exist, char* ScooterID);
void FillCurrentUserInfoToStructure(FillDataBase* curUser);
void frontInfoMainMenyu(FillDataBase* curUser);
void chooseSkuter(FillDataBase* curUser, char* UserAppID, char* ScooterID);
bool IsTrueSkuterId(char* skuterId, char* UserAppID);
void UseSkuter(FillDataBase* curUser, char* choose, char* UserAppID);
void TimerAndSummaCounter(int UseSkuterTime, float* summa);
void FillTravelsHistory(FillDataBase* curUser, float summa, int UseSkuterTime, char* choose, char* UserAppID);
void frontInfoAditionMayus(FillDataBase* curUser);
void profile(FillDataBase* curUser);
void PrintTrevelSheet();
void mainForAdmin(ForAdmin* Admin, char* UserAppID, char* exist);
void FillAdminInfoToStructure(ForAdmin* Admin, char* UserAppID);
void frontInfoAdminMenyu(ForAdmin* Admin);
void profileAdmin(ForAdmin* Admin);
void Addscooter();
void LastUsageOfScooter();

int main (){
    system("cls");

    User odam;
    FillDataBase curUser;
    ForAdmin Admin;

    curUser.balance = 0;
    char UserAppID[100] = {};
    char exist[100] = {};
    char ScooterID[100] = {};
    LoginOrRegister(&odam, UserAppID, &curUser, exist);
    if(strcmp(exist, "ha") == 0 || strcmp(exist, "yo'q") == 0){
        if(strcmp(UserAppID, "Admin1") != 0){
            chdir(UserAppID);
            mainMenyu(&curUser,UserAppID, exist, ScooterID);
        }else{
            mainForAdmin(&Admin, UserAppID, exist);
        }
    }

    return 0;
}

void FillAdminInfoToStructure(ForAdmin* Admin, char* UserAppID){
    char def[100] = {};
    chdir(UserAppID);

    FILE* AdminInfo = fopen("AdminInfo.txt", "r+");
    
    if (AdminInfo == NULL) {
        perror("Error opening UserInfo.txt");
        exit(EXIT_FAILURE);
    }

     while (fscanf(AdminInfo, " %s", def) == 1) {
        if (strcmp(def, "Ism:") == 0) {
            fscanf(AdminInfo, " %[^\n]s", Admin->name);
            // printf("Ism = %s\n", curUser->name);
        } else if (strcmp(def, "Familiya:") == 0) {
            fscanf(AdminInfo, " %[^\n]s", Admin->surname);
            // printf("Familiya = %s\n", curUser->surname);
        } else if (strcmp(def, "Username:") == 0) {
            fscanf(AdminInfo, " %[^\n]s", Admin->username);
            // printf("Username = %s\n", curUser->username);
        } else if (strcmp(def, "Telefon_raqam:") == 0) {
            fscanf(AdminInfo, " %[^\n]s", Admin->phoneNumber);
            // printf("Telefon raqam = %s\n", curUser->phoneNumber);
        } else if (strcmp(def, "ID_raqam:") == 0) {
            fscanf(AdminInfo, " %[^\n]s", Admin->ID_NUMBER);
            // printf("Id number = %s\n", curUser->ID_NUMBER);
        }
    }
    fclose(AdminInfo);
    if (chdir("..") != 0) {
        puts("chdinr() error");
    }
}

void frontInfoAdminMenyu(ForAdmin* Admin){
    system("cls");
    printf("    - - - - - - - - - - - - - - - -\n");
    printf("   | \033[1mAdmin\033[0m %s\n", Admin->username);
    printf("    - - - - - - - - - - - - - - - -\n\n");
    printf("    - - - - -    - - - - - - -  \n");
    printf("   | profile |  | Add scooter |\n");
    printf("    - - - - -    - - - - - - -  \n");
    printf("    - - - - - - - - - - - -    ---- \n");
    printf("   | Last usage of scooter |  | << | \n");
    printf("    - - - - - - - - - - - -    ---- \n\n");
}

void profileAdmin(ForAdmin* Admin){
    system("cls");
    printf("   Ism: %s\n", Admin->name);
    printf("   -----------------------------------------\n");
    printf("   Familiya: %s\n", Admin->surname);
    printf("   -----------------------------------------\n");
    printf("   Username: %s\n", Admin->username);
    printf("   -----------------------------------------\n");
    printf("   Telefon raqam: %s\n", Admin->phoneNumber);
    printf("   -----------------------------------------\n");
    printf("   ID raqam: %s\n", Admin->ID_NUMBER);
    printf("   -----------------------------------------\n\n");
}

void Addscooter(){
    system("cls");
    char new[100] = "";
    printf("   Write new scooter name: ");
    scanf(" %s", new);

    FILE* Vehicle = fopen("VehiclesIDNumbers.txt", "a");
    
    if(Vehicle == NULL){
        puts("   Vehicle file cannot open.\n");
        return;
    }

    int check;
    check = mkdir(new);
    if (check != 0) {
        perror("   mkdir() error");
        exit(EXIT_FAILURE);
    }

    fprintf(Vehicle, "\nVehicle ID Number: %s", new);

    fclose(Vehicle);
}

void LastUsageOfScooter(){
    system("cls");

    printf("   Enter scooter name: ");
    char name[100] = {};
    scanf(" %s", name);
    chdir(name);

    FILE* History = fopen("History.txt", "r");

    if(History == NULL){
        puts("   Error: History opening");
        return;
    }

    while(1){
        FILE* LastUsage = fopen("LastUsage.txt", "w");
        for(int i = 0; i < 9; i++){
            char tem[100] = {};
            fscanf(History, " %[^\n]s", tem);
            fprintf(LastUsage, "%s\n", tem);
            // printf("%s\n", tem);
        }
        // printf("\n");
        fclose(LastUsage);
        if(feof(History)){
            break;
        }
    }
    fclose(History);

    FILE* PrintLastUser = fopen("LastUsage.txt", "r");
    
    if(PrintLastUser == NULL){
        puts("Error: History opening");
        return;
    }
    fseek(PrintLastUser, 0, SEEK_SET);
    printf("   ");
    while(1){
        char belgi = fgetc(PrintLastUser);
        if(feof(PrintLastUser)){
            break;
        }
        if(belgi == '\n'){
            printf("%c", belgi);
            printf("   ");
        }else{
            printf("%c", belgi);
        }
    }
    printf("\n");

    if (chdir("..") != 0) {
        puts("chdinr() error");
    }
    printf("   ");
}

void mainForAdmin(ForAdmin* Admin, char* UserAppID, char* exist){
    char exit;
    char amal[100] = {};
    for (int i = 0; amal[i] != '\0'; i++)
    {
        amal[i] = tolower(amal[i]);
    }
    if (strcmp(exist, "yo'q") != 0)
    {
        FillAdminInfoToStructure(Admin, UserAppID);
    }
    char belgi = '?';
    char tem[100] = {};
    do
    {
        frontInfoAdminMenyu(Admin);
        printf("   ");
        scanf(" %[^\n]s", tem);
        for (int i = 0; tem[i] != '\0'; i++)
        {
            tem[i] = tolower(tem[i]);
        }
        if (strcmp(tem, "profile") == 0)
        {
            profileAdmin(Admin);
            printf("   ");
            scanf(" %c", &belgi);
        }
        else if (strcmp(tem, "add scooter") == 0)
        {
            Addscooter();
            printf("   ");
            scanf(" %c", &belgi);
        }
        else if (strcmp(tem, "last usage of scooter") == 0)
        {
            LastUsageOfScooter();
            printf("   ");
            scanf(" %c", &belgi);
        }
        else if (strcmp(tem, "<<") == 0)
        {
            break;
        }
    } while (belgi == '<');
}

void FillCurrentUserInfoToStructure(FillDataBase* curUser){
    char def[100] = {};

    FILE* UserInfo = fopen("UserInfo.txt", "r");
    
    if (UserInfo == NULL) {
        perror("Error opening UserInfo.txt");
        exit(EXIT_FAILURE);
    }

     while (fscanf(UserInfo, " %s", def) == 1) {
        if (strcmp(def, "Ism:") == 0) {
            fscanf(UserInfo, " %s", curUser->name);
            // printf("Ism = %s\n", curUser->name);
        } else if (strcmp(def, "Familiya:") == 0) {
            fscanf(UserInfo, " %s", curUser->surname);
            // printf("Familiya = %s\n", curUser->surname);
        } else if (strcmp(def, "Username:") == 0) {
            fscanf(UserInfo, " %s", curUser->username);
            // printf("Username = %s\n", curUser->username);
        } else if (strcmp(def, "Telefon_raqam:") == 0) {
            fscanf(UserInfo, " %s", curUser->phoneNumber);
            // printf("Telefon raqam = %s\n", curUser->phoneNumber);
        } else if (strcmp(def, "ID_raqam:") == 0) {
            fscanf(UserInfo, " %s", curUser->ID_NUMBER);
            // printf("Id number = %s\n", curUser->ID_NUMBER);
        } else if (strcmp(def, "Balance:") == 0) {
            fscanf(UserInfo, "%lf", &curUser->balance);
            // printf("balance = %lf\n", curUser->balance);
        }
    }
    fclose(UserInfo);
}

void frontInfoMainMenyu(FillDataBase* curUser){
    system("cls");
    printf("    - - - - - - - - - - - - - -\n");
    printf("   | %s\n", curUser->username);
    printf("    - - - - - - - - - - - - - -\n\n");
    printf("            Balance         \n");
    printf("           %.3lf\n\n", curUser->balance);
    printf("    - - - - - - - -    - - -   ----\n");
    printf("   | Skuter tanlash | | ... | | << |\n");
    printf("    - - - - - - - -    - - -   ----\n\n");
}

void mainMenyu(FillDataBase* curUser, char* UserAppID, char* exist, char* ScooterID){
    char exit;
    char amal[100] = {};
    do{
        if(strcmp(exist, "yo'q") != 0){
            FillCurrentUserInfoToStructure(curUser);
        }
        frontInfoMainMenyu(curUser);
        printf("   ");
        scanf(" %[^\n]s", amal);
        for (int i = 0; amal[i] != '\0'; i++) {
            amal[i] = tolower(amal[i]);
        }
        if (strcmp(amal, "skuter tanlash") == 0){
            chooseSkuter(curUser, UserAppID, ScooterID);
        }
        else if (strcmp(amal, "...") == 0){
            char belgi;
            char tem[100] = {};
            do{
                frontInfoAditionMayus(curUser);
                printf("   ");
                scanf(" %[^\n]s", tem);
                for (int i = 0; tem[i] != '\0'; i++) {
                    tem[i] = tolower(tem[i]);
                }
                if (strcmp(tem, "profile") == 0){
                    profile(curUser);
                    printf("   ");
                    scanf(" %c", &belgi);
                }else if (strcmp(tem, "to'lov qilish") == 0){
                    system("cls");
                    putDepositeWhileRegister(curUser);
                    AddUserInfoIntoUserDir(curUser);
                    printf("   ");
                    scanf(" %c", &belgi);
                }else if (strcmp(tem, "foydalanish tarixi") == 0){
                    PrintTrevelSheet();
                    printf("   ");
                    scanf(" %c", &belgi);
                }else if (strcmp(tem, "<") != 0){
                    break;
                }
            }while(belgi == '<');
        }
    }while(strcmp(amal, "<<") != 0);
}

void PrintTrevelSheet(){
    system("cls");
    FILE* TrevelSheet = fopen("historyOfTravels.txt", "r");

    printf("   ");
    while(1){
        char tem = fgetc(TrevelSheet);
        if(feof(TrevelSheet)){
            break;
        }
        if(tem == '\n'){
            printf("%c", tem);
            printf("   ");
        }else{
            printf("%c", tem);
        }
    }
    fclose(TrevelSheet);
}

void profile(FillDataBase* curUser){
    system("cls");
    printf("   Ism: %s\n", curUser->name);
    printf("   -----------------------------------------\n");
    printf("   Familiya: %s\n", curUser->surname);
    printf("   -----------------------------------------\n");
    printf("   Username: %s\n", curUser->username);
    printf("   -----------------------------------------\n");
    printf("   Telefon raqam: %s\n", curUser->phoneNumber);
    printf("   -----------------------------------------\n");
    printf("   ID raqam: %s\n", curUser->ID_NUMBER);
    printf("   -----------------------------------------\n\n");
}

void frontInfoAditionMayus(FillDataBase* curUser){
    system("cls");
    printf("    - - - - - - - - - - - -\n");
    printf("   | %s\n", curUser->username);
    printf("    - - - - - - - - - - - -\n\n");
    printf("            Balance         \n");
    printf("           %.3lf\n\n", curUser->balance);
    printf("    - - - - -    - - - - - - - - \n");
    printf("   | profile |  | To'lov qilish |\n");
    printf("    - - - - -    - - - - - - - - \n");
    printf("    - - - - - - - - - -     ---- \n");
    printf("   | Foydalanish tarixi |  | << | \n");
    printf("    - - - - - - - - - -     ---- \n\n");
}

void chooseSkuter(FillDataBase* curUser, char* UserAppID, char* ScooterID){
    system("cls");
    printf("  Skuter ID raqamini kiriting: ");
    scanf(" %s", ScooterID);
    while(1){
        if(IsTrueSkuterId(ScooterID, UserAppID)){
            UseSkuter(curUser, ScooterID, UserAppID);
            break;
        }else if(strcmp(ScooterID, "<") == 0){
            break;
        }else if(!IsTrueSkuterId(ScooterID, UserAppID)){
            printf("  Skuter ID raqamini qayta kiriting: ");
            scanf(" %s", ScooterID);
        }
    }
}

void UseSkuter(FillDataBase* curUser, char* ScooterID, char* UserAppID){
    char UseAgain[100] = "ha";
    while(strcmp(UseAgain, "ha") == 0 && strcmp(UseAgain, "yo'q")){
        int UseSkuterTime = 0;
        system("cls");
        printf("  Nechi minut foydalanmoqchisiz: ");
        scanf("%d", &UseSkuterTime);
        if(!(UseSkuterTime * priceOfUseSkuter <= curUser->balance)){
            puts("  Balansingizdagi mablag' yetarli emas\n");
            break;
        }
        if(UseSkuterTime > 0){
            float summa = 0;
            TimerAndSummaCounter(UseSkuterTime, &summa);
            curUser->balance -= summa;
            FillTravelsHistory(curUser, summa, UseSkuterTime, ScooterID, UserAppID);
            AddUserInfoIntoUserDir(curUser);
            printf("  Yana foydalanasizmi: [Ha/Yo'q] ");
            scanf(" %s", UseAgain);
            for (int i = 0; UseAgain[i] != '\0'; i++) {
                UseAgain[i] = tolower(UseAgain[i]);
            }
        }else{
            system("cls");
            puts("  Matematikani bilasizmi o'zi!!!\n");
            sleep(3);
            system("cls");
            printf("  Nechi minut foydalanmoqchisiz: ");
            scanf("%d", &UseSkuterTime);
        }
    }
}

void FillTravelsHistory(FillDataBase* curUser, float summa, int UseSkuterTime, char* ScooterID, char* UserAppID){
    FILE* History = fopen("historyOfTravels.txt", "a");

    fprintf(History, "Summasi = %g so'm\n", summa);
    fprintf(History, "Foydalangan vaqti = %d minut\n", UseSkuterTime);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int year = tm.tm_year + 1900;
    int month = tm.tm_mon + 1;
    int day = tm.tm_mday;
    int hour = tm.tm_hour;
    int minute =  tm.tm_min;
    int secund =  tm.tm_sec;
    fprintf(History, "Sana: %02d.%02d.%04d\n", day, month, year);
    fprintf(History, "Vaqti: %02d:%02d\n\n", hour, minute);

    fclose(History);

    if (chdir("..") != 0) {
        puts("chdinr() error");
    }

    chdir(ScooterID);

    FILE* History2 = fopen("History.txt", "a");

    fprintf(History2, "\n- - - - - - - - - - - - - - -\n");
    fprintf(History2, "Ism: %s\n", curUser->name);
    fprintf(History2, "Familiya: %s\n", curUser->surname);
    fprintf(History2, "Telefon nomer: %s\n", curUser->phoneNumber);
    fprintf(History2, "ID raqami: %s\n", curUser->ID_NUMBER);
    fprintf(History2, "Summasi = %g so'm\n", summa);
    fprintf(History2, "Foydalangan vaqti = %d minut\n", UseSkuterTime);
  
    fprintf(History2, "Sana: %02d.%02d.%04d\n", day, month, year);
    fprintf(History2, "Vaqti: %02d:%02d", hour, minute);

    fclose(History2); 

    if (chdir("..") != 0) {
        puts("chdinr() error");
    }
    chdir(UserAppID);  
}

void TimerAndSummaCounter(int UseSkuterTime, float* summa){
    system("cls");
    int minutOfUse = 0, secundOfUse = 0;
    int minut = 0, secund = 0;
    float PrintSum = 0;

    while(UseSkuterTime != 0){
        time_t rawtime;
        struct tm *info;

        time(&rawtime);
        info = gmtime(&rawtime);

        int houn = (info->tm_hour + BST) % 24;
        int minutCur = info->tm_min;
        int secundCur = info->tm_sec;

        if(secundOfUse != secundCur){
            if(secund == 59){
                minut++;
                *summa = minut * priceOfUseSkuter;
                secund = 0;
                UseSkuterTime--;
            }else{
                secund++;
            }
            float temtr = (float)(secund) / 60;
            PrintSum = (minut + temtr) * priceOfUseSkuter;
            minutOfUse = minutCur;
            secundOfUse = secundCur;
            system("cls");
            printf("\n\n\n\n\n\n\t     - - - -    - - - - - - - -\n");
            printf("\t    | %02d:%02d |  | %09.3f so'm |\n", minut, secund, PrintSum);
            printf("\t     - - - -    - - - - - - - -\n\n\n\n\n\n\n\n");
        }
    }
    sleep(2);
    system("cls");
}

bool IsTrueSkuterId(char* skuterId, char* UserAppID){
    if (chdir("..") != 0) {
        puts("chdinr() error");
    }
    
    FILE* f = fopen("VehiclesIDNumbers.txt", "r");

    if(f == 0){
        puts("  Error: could not open VehilcesIDNumbers file");
        return false;
    }

    int n = 0;
    while(1){
        char tem[100] = {};
        if(n == 0){
            fseek(f, 19, SEEK_CUR);
            n = 1;
        }else{
            fseek(f, 20, SEEK_CUR);
        }
        fscanf(f, " %s", tem);
        // puts(tem);
        if(strcmp(skuterId, tem) == 0){
            fclose(f);
            chdir(UserAppID);
            return true;
        }
        if(feof(f)){
            break;
        }
    }
    fclose(f);
    chdir(UserAppID);
    return false;
}

void LoginOrRegister(User* odam, char UserAppID[], FillDataBase* New, char* exist){
    printf("  Saytdan ro'yxatdan o'tganmisiz: [Ha/yo'q] ");
    scanf(" %s", exist);
    for (int i = 0; exist[i] != '\0'; i++) {
        exist[i] = tolower(exist[i]);
    }
    if(strcmp(exist, "ha") == 0){
        printf("  Username: ");
        scanf(" %s", odam->username);
        char temPass[100] = {};
        while(UserTrue(odam, temPass, UserAppID) == 0){
            printf("  Username xato.\n");
            sleep(2);
            system("cls");
            printf("  Qayta kiriting: ");
            scanf(" %s", odam->username);
        }
        printf("  Password: ");
        scanf(" %s", odam->password);
        while(1){
            if(strcmp(odam->password, temPass) != 0){
                printf("  Password xato\n");
                sleep(2);
                system("cls");
                printf("  Qayta kiriting: ");
                scanf(" %s", odam->password);
            }else{
                break;
            }
        }
        system("cls");
        puts("\n\n\n\n\n\n\n\n\t\t  Username is exist!\n\n\n\n\n\n\n\n\t\t");
        sleep(2);
        system("cls");
    }else if(strcmp(exist, "yo'q") == 0){
        char NewUserIDNumber[100] = "user";
        NewUser(New, NewUserIDNumber);
        AddUserToDataBase(New, NewUserIDNumber);
    }else{
        puts("   G'ilay ham ko'radi [Ha/yo'q] ni!!!");
        sleep(3);
        system("cls");
    }
}

bool UserTrue(User* odam, char temPass[], char UserAppID[]){
    FILE* DataBase = fopen("DataBase.txt", "r");
    fseek(DataBase, 6, SEEK_SET);
    char CurUsername[100];
    while(1){
        fseek(DataBase, 11, SEEK_CUR);
        fscanf(DataBase, " %s", CurUsername);
        // puts(CurUsername);
        fseek(DataBase, 11, SEEK_CUR);
        fscanf(DataBase, " %s", temPass);
        // puts(temPass);
        fseek(DataBase, 17, SEEK_CUR);
        fscanf(DataBase, " %s", UserAppID);
        // puts(UserAppID);
        // puts("");
        if(feof(DataBase)){
            break;
        }
        if(strcmp(odam->username, CurUsername) == 0){
            return true;
        }
        int count = 5;
        char tem[100];
        while(count != 0){
            fscanf(DataBase, " %[^\n]s", tem);
            count--;
            // puts("0");
        }
    }
    // puts(temPass);
    fclose(DataBase);
    return false;
}

void AddUserToDataBase(FillDataBase* New, char NewUserIDNumber[]){
    FILE* AddToDataBase = fopen("DataBase.txt", "a");
 
    fprintf(AddToDataBase, "\nUser:\n");
    fprintf(AddToDataBase, "Username: %s\n", New->username);
    fprintf(AddToDataBase, "Password: %s\n", New->password);
    fprintf(AddToDataBase, "User ID Number: %s\n", NewUserIDNumber);
    fprintf(AddToDataBase, "Name: %s\n", New->name);
    fprintf(AddToDataBase, "Surname: %s\n", New->surname);
    fprintf(AddToDataBase, "Phone Number: %s\n", New->phoneNumber);
    fprintf(AddToDataBase, "ID Number: %s\n", New->ID_NUMBER);

    fclose(AddToDataBase);
}

void NewUser(FillDataBase* New, char NewUserIDNumber[]){
    system("cls");

    printf("\t\t     --------------\n");
    printf("\t\t    | REGISTRATION |\n");
    printf("\t\t     --------------\n");

    printf(" Ismingizni kiriting: ");
    scanf(" %s", New->name);

    printf(" Familiyangizni kiriting: ");
    scanf(" %s", New->surname);

    printf(" Telefon nomiringizni kiriting: ");
    scanf(" %s", New->phoneNumber);

    printf(" ID raqamingizni kiriting: ");
    scanf(" %s", New->ID_NUMBER);
    
    printf(" Username kiriting: ");
    scanf(" %s", New->username);

    FILE* DataBase = fopen("DataBase.txt", "r");

    if(DataBase == 0){
        puts("   Error While creating an Account in DataBase");
        return;
    }

    fseek(DataBase, 6, SEEK_SET);
    while (1)
    {
        char CurUsername[100] = {};
        fseek(DataBase, 11, SEEK_CUR);
        fscanf(DataBase, " %s", CurUsername);
        if (feof(DataBase))
        {
            break;
        }
        if (strcmp(New->username, CurUsername) == 0)
        {
            printf(" Bunday Username allaqachon bor!\n");
            sleep(2);
            system("cls");
            printf(" Boshqa Username kiriting: ");
            scanf(" %s", New->username);
            fseek(DataBase, 6, SEEK_SET);
            continue;
        }
        int count = 14;
        char tem[100];
        while (count != 0)
        {
            fscanf(DataBase, " %s", tem);
            count--;
        }
    }
    fclose(DataBase);

    printf(" Password kiriting: ");
    scanf(" %s", New->password);

    system("cls");
    char deposit[10] = {};
    printf("   Deposit qo'yishni hohlaysizmi: [ha/yo'q] ");
    scanf(" %s", deposit);
    for (int i = 0; deposit[i] != '\0'; i++) {
        deposit[i] = tolower(deposit[i]);
    }

    if(strcmp(deposit, "ha") == 0){
        system("cls");
        putDepositeWhileRegister(New);
    }else{
        New->balance = 0;
    }
    // puts("Successfully");

    CreateNewUserDir(New, NewUserIDNumber);

    int check;
    check = mkdir(NewUserIDNumber);
    if (check != 0) {
        perror("mkdir() error");
        exit(EXIT_FAILURE);
    }
    chdir(NewUserIDNumber);
    AddUserInfoIntoUserDir(New);
    FILE* file = fopen("historyOfTravels.txt", "w");
    fclose(file);
    
    if (chdir("..") != 0) {
        perror("chdir() error");
        exit(EXIT_FAILURE);
    }

    // FILE* aniqla = fopen("SHo'ttama.txt", "w");
}

void putDepositeWhileRegister(FillDataBase* New){
    char Card[25] = {};
    double summa = 0;
    printf("   Karta raqamingizni kiriting:\n");
    printf("   ");
    scanf(" %[^\n]s", Card);
    while(1){
        if(!IsCardNumberTrue(Card)){
            printf("   Karta raqam xato kiritilgan!\n");
            sleep(2);
            system("cls");
            printf("   Karta raqamingizni qayta kiriting\n");
            printf("   ");
            scanf(" %[^\n]s", Card);
        }else{
            printf("   Summani kiriting: ");
            scanf("%lf", &summa);
            New->balance += summa;
            system("cls");
            puts("\n\n\n\n\n\n\n\n\tTo'lov muvaffaqiyatli amalga oshdi!\n\n\n\n\n\n\n\n");
            sleep(3);
            system("cls");
            break;
        }
    }
}

bool IsCardNumberTrue(char cardNumber[]){
    if (strlen(cardNumber) == 0) {
        return false;
    }
    if(strlen(cardNumber) != 19){
        return false;
    }
    for(int i = 1; i < 20; i++){
        if(i % 5 == 0){
            if(!isspace(cardNumber[i - 1])){
                return false;
            }
        }else{
            if(!isdigit(cardNumber[i - 1])){
                return false;
            }
        }
    }

    return true;
}

void AddUserInfoIntoUserDir(FillDataBase* New){
    FILE* file = fopen("UserInfo.txt", "w");

    fprintf(file, "Ism: %s\n", New->name);
    // printf("Ism = %s\n", New->name);
    
    fprintf(file, "Familiya: %s\n", New->surname);
    // printf("Familiya = %s\n", New->surname);
    
    fprintf(file, "Username: %s\n", New->username);
    // printf("Username = %s\n", New->username);
    
    fprintf(file, "Telefon_raqam: %s\n", New->phoneNumber);
    // printf("Telefon raqam = %s\n", New->phoneNumber);
    
    fprintf(file, "ID_raqam: %s\n", New->ID_NUMBER);
    // printf("Id number = %s\n", New->ID_NUMBER);
    
    fprintf(file, "Balance: %.3lf\n", New->balance);
    // printf("balance = %lf\n", New->balance);

    fclose(file);
}

void CreateNewUserDir(FillDataBase* New, char NewUserIDChar[]){
    int NewUserAppID = FindNewUserId() + 1;
    char sufix[100] = {};
    int i = 0;
    while(NewUserAppID != 0){
        sufix[i++] = NewUserAppID % 10 + '0';
        NewUserAppID /= 10;
    }
    i -= 1;
    for(int j = 0; j < i; j++, i--){
        int box = sufix[j];
        sufix[j] = sufix[i];
        sufix[i] = box;
    }
    strcat(NewUserIDChar, sufix);
}

int FindNewUserId(){
    char UserAppID[100] = {};
    int UserAppIDInt = 0;
    FILE* DataBase = fopen("DataBase.txt", "r");
    if(DataBase == 0){
        puts("Error With Finding New App User ID!");
        return 0;
    }
    for(int i = 0; i < 3; i++){
        fscanf(DataBase, " %[^\n]s", UserAppID);
    }
    while(1){
        for(int i = 0; i < 3; i++){
            fscanf(DataBase, " %s", UserAppID);
        }
        fscanf(DataBase, " %s", UserAppID);
        char tem[4093];
        for(int i = 0; i < 7; i++){
            fscanf(DataBase, " %[^\n]s", tem);
        }
        if(feof(DataBase)){
            break;
        }
    }
    for(int i = 4; i < strlen(UserAppID); i++){
        UserAppIDInt = (UserAppIDInt * 10) + (UserAppID[i] - '0');
    }
    fclose(DataBase);
    return UserAppIDInt;
}
