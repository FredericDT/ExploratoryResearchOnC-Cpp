#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct record {
    int id = 0;
    char name[36] = "";
    unsigned int amount = 0;
    double price = 0.0;
} *Record;

const char filePath[] = "commodity.dat";

const struct record EMPTY_RECORD = {0, "", 0, 0.0};

const size_t RECORD_SIZE = sizeof(struct record);

void checkFile(FILE *f) {
    if (!f) {
        printf("Couldn't open file\n");
        exit(1);
    }
}

void initRecordFile() {
    FILE *f = fopen(filePath, "wb+");
    checkFile(f);
    for (int i = 0; i < 100; ++i) {
        fwrite(&EMPTY_RECORD, RECORD_SIZE, 1, f);
    }
    fclose(f);
    printf("done\n");
}

void preconditionValidRecord(struct record r) {
    if (r.id < 1) {
        printf("invalid id\n");
        exit(1);
    }
}

void insertRecord(struct record r) {
    preconditionValidRecord(r);
    FILE *f = fopen(filePath, "rb+");
    checkFile(f);
    fseek(f, (r.id - 1) * RECORD_SIZE, SEEK_SET);
    fwrite(&r, RECORD_SIZE, 1, f);
    fclose(f);
}

void updateRecord(struct record r) {
    preconditionValidRecord(r);
    FILE *f = fopen(filePath, "rb+");
    checkFile(f);
    struct record t;
    fseek(f, (r.id - 1) * RECORD_SIZE, SEEK_SET);
    fread(&t, RECORD_SIZE, 1, f);
    preconditionValidRecord(t);
    fseek(f, (r.id - 1) * RECORD_SIZE, SEEK_SET);
    fwrite(&r, RECORD_SIZE, 1, f);
    printf("done\n");
    fclose(f);
}

void getRecordById(Record r) {
    preconditionValidRecord(*r);
    FILE *f = fopen(filePath, "rb+");
    checkFile(f);
    fseek(f, (r->id - 1) * RECORD_SIZE, SEEK_SET);
    fread(r, RECORD_SIZE, 1, f);
    fclose(f);
}

void deleteRecord(struct record r) {
    preconditionValidRecord(r);
    FILE *f = fopen(filePath, "rb+");
    checkFile(f);
    fseek(f, (r.id - 1) * RECORD_SIZE, SEEK_SET);
    fwrite(&EMPTY_RECORD, RECORD_SIZE, 1, f);
    printf("done\n");
    fclose(f);
}

void printHeader() {
    printf("id\tname\tamount\tprice\n");
}

void printRecord(struct record r) {
    printf("%d\t%s\t%d\t%lf\n",
           r.id,
           r.name,
           r.amount,
           r.price);
}

void printAllRecords() {
    FILE *f = fopen(filePath, "rb+");
    checkFile(f);
    struct record r;
    printHeader();
    for (int i = 0; i < 100; ++i) {
        fread(&r, RECORD_SIZE, 1, f);
        fseek(f, RECORD_SIZE, SEEK_CUR);
        if (r.id < 1) {
            continue;
        }
        printRecord(r);
    }
    printf("done\n");
    fclose(f);
}

void rTrimStream(FILE *f) {
    char c;
    while((c = fgetc(f)) && (c == '\n' || c == ' '));
    ungetc(c, f);
}

const char USAGE[] =
        "please input func:\n"
        "1 - create init empty record file\n"
        "2 - insert a record\n"
        "3 - update record\n"
        "4 - delete record\n"
        "5 - print all records\n"
        "6 - exit\n";

int readAnInt() {
    int t = 0;
    scanf("%d", &t);
    return t;
}

struct record readARecordFromSTDIN(char name[35]) {
    printf("please input good's info (whose id is -1 means end):\n");
    struct record r = EMPTY_RECORD;
    int id = 0;
    printf("input id:");
    scanf("%d", &id);
    if (id < 1) {
        return EMPTY_RECORD;
    }
    r.id = id;
    printf("input name:");
    rTrimStream(stdin);
    scanf("%[^\n]", name);
    strcpy(r.name, name);
    int amount = 0;
    printf("input amount:");
    scanf("%d", &amount);
    r.amount = amount;
    double price = 0.0;
    printf("input price:");
    scanf("%lf", &price);
    r.price = price;
    return r;
}

void insertFuncWrapper() {
    while (1) {
        char name[35];
        struct record r = readARecordFromSTDIN(name);
        if (r.id < 1) {
            break;
        }
        insertRecord(r);
    }
    printAllRecords();
}

void updateFuncWrapper() {

    while (1) {
        int id = 0;
        printf("please input an id (-1 means end):");
        rTrimStream(stdin);
        scanf("%d", &id);
        if (id < 1) {
            break;
        }
        struct record r = EMPTY_RECORD;
        r.id = id;
        getRecordById(&r);
        if (r.id < 1) {
            printf("record not found");
            continue;
        }
        printHeader();
        printRecord(r);
        getchar();

        //name
        printf("input name:");
        int i = getchar();
        if (i != '\n') {
            ungetc(i, stdin);
            scanf("%[^\n]", r.name);
            getchar();
        }
        printf("input amount:");
        i = getchar();
        if (i != '\n') {
            ungetc(i, stdin);
            scanf("%d", &r.amount);
            getchar();
        }
        printf("input price:");
        i = getchar();
        if (i != '\n') {
            ungetc(i, stdin);
            scanf("%lf", &r.price);
        }
        updateRecord(r);
        getRecordById(&r);
        printf("info after update are:\n");
        printHeader();
        printRecord(r);
    }
    printf("done");
}

void deleteFuncWrapper() {
    while (1) {
        int id = 0;
        printf("please input an id (-1 mean end):");
        char name[35];
        struct record r = EMPTY_RECORD;
        r.id = id;
        getRecordById(&r);
        if (id < 1) {
            printf("not found\n");
            continue;
        }
        printf("input Y/N to confirm:");
        rTrimStream(stdin);
        int s = getchar();
        switch (s) {
            case 'Y':
            case 'y':
                deleteRecord(r);
            default:
                break;
        }
        printAllRecords();
        if (id < 1) {
            break;
        }
    }
}

int main() {
    while (1) {
        printf(USAGE);
        rTrimStream(stdin);
        int func = 0;
        scanf("%d", &func);
        //printf("%d", func);
        switch (func) {
            default:
            case 6:
                exit(0);
            case 1:
                initRecordFile();
                break;
            case 2:
                insertFuncWrapper();
                break;
            case 3:
                updateFuncWrapper();
                break;
            case 4:
                deleteFuncWrapper();
                break;
            case 5:
                printAllRecords();
        }
    }

    return 0;
}