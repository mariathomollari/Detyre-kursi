#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT 100
#define MAX_INSTRUKTOR 100
#define MAX_KURS 100

struct Student {
    int ID;
    char emri[30];
    char mbiemri[30];
    int ditelindja_dita;
    int ditelindja_muaji;
    int ditelindja_viti;
};

struct Instruktor {
    int ID;
    char emri[30];
    char mbiemri[30];
    char ditelindja[20];
    char kategorite_e_kurseve[50];
};

struct Kurs {
    int ID;
    char data_e_fillimit[20];
    char ditet[20];
    char ora_e_fillimit[10];
    char kategoria_e_kursit[20];
    struct Instruktor instruktor;
    int studentet[MAX_STUDENT];
    int NrStudenteve;
};

struct Student studentet[MAX_STUDENT];
int NriStudenteve = 0;
struct Instruktor instruktoret[MAX_INSTRUKTOR];
int NrInstruktoreve = 0;
struct Kurs kurset[MAX_KURS];
int nrKurseve = 0;

void menu() {
    printf("\n QENDER KURSESH");
    printf("\n *** MENU ***");
    printf("\n Zgjidhni nje opsion:");
    printf("\n\n 1 - Regjistro nje student ne sistem  ");
    printf("\n 2 - Regjistro nje instruktor ");
    printf("\n 3 - Regjistro nje kurs  ");
    printf("\n 4 - Regjistro nje student ne nje kurs  ");
    printf("\n 5 - Fshi nje instruktor  ");
    printf("\n 6 - Fshi nje kurs  ");
    printf("\n 7 - Cregjistro nje student  ");
    printf("\n 8 - Lista e kurseve  ");
    printf("\n 9 - Lista e studenteve  ");
    printf("\n 10 - Lista e instruktoreve ");
    printf("\n 11 - Lista e studenteve te regjistruar ne nje kurs te caktuar ");
    printf("\n 12 - Lista e studenteve qe nje instruktor ka");
    printf("\n 0 - Dil ");
    printf("\n\n ZGJEDHJA:  ");
}

int kontrolloMoshen(struct Student student) {
    int viti_aktual;
    printf("Vendos vitin aktual: ");
    scanf("%d", &viti_aktual);
    int mosha = viti_aktual - student.ditelindja_viti;
    if (mosha >= 5 && mosha <= 14) {
        return 1;
    } else {
        return 0;
    }
}

void regjistro_student() {
    struct Student student;
    printf("\nVendos ID e studentit: ");
    scanf("%d", &student.ID);
    printf("\nVendos emrin e studentit: ");
    scanf("%s", student.emri);
    printf("\nVendos mbiemrin e studentit: ");
    scanf("%s", student.mbiemri);
    printf("\nVendos diten e lindjes: ");
    scanf("%d", &student.ditelindja_dita);
    printf("\nVendos muajin e lindjes (1-12): ");
    scanf("%d", &student.ditelindja_muaji);
    printf("\nVendos vitin e lindjes: ");
    scanf("%d", &student.ditelindja_viti);

    if (kontrolloMoshen(student)) {
        studentet[NriStudenteve] = student;
        NriStudenteve++;
        printf("Studenti u regjistrua me sukses.\n");
    } else {
        printf("Mosha e studentit nuk përputhet me kriteret e regjistrimit.\n");
    }
}

void regjistro_instruktor() {
    struct Instruktor instruktor;
    printf("Vendos ID e instruktorit: ");
    scanf("%d", &instruktor.ID);
    printf("Vendos emrin e instruktorit: ");
    scanf("%s", instruktor.emri);
    printf("Vendos mbiemrin e instruktorit: ");
    scanf("%s", instruktor.mbiemri);
    printf("Vendos ditëlindjen e instruktorit (DD MM YYYY): ");
    scanf("%s", instruktor.ditelindja);
    printf("Vendos kategoritë e kurseve (Robotike; Programim; Graphic Design): ");
    scanf("%s", instruktor.kategorite_e_kurseve);

    instruktoret[NrInstruktoreve] = instruktor;
    NrInstruktoreve++;
    printf("Instruktori u regjistrua me sukses.\n");
}

void regjistro_kursin() {
    struct Kurs kurs;
    printf("Vendos ID e kursit: ");
    scanf("%d", &kurs.ID);
    printf("Vendos daten e nisjes (DD.MM.YYYY) : ");
    scanf("%s", kurs.data_e_fillimit);
    printf("Vendos ditëte javes kur zhvillohet (1-7) : ");
    scanf("%s", kurs.ditet);
    printf("Vendos orarin e fillimit: ");
    scanf("%s", kurs.ora_e_fillimit);
    printf("Vendos kategorine (Robotike; Programim; Graphic Design): ");
    scanf("%s", kurs.kategoria_e_kursit);
    printf("Vendos ID e instruktorit: ");
    scanf("%d", &kurs.instruktor.ID);

    kurset[nrKurseve] = kurs;
    nrKurseve++;
    printf("Kursi u regjistrua me sukses.\n");
}

void ruaj_student() {
    FILE *f;
    f = fopen("student.txt", "w");
    if (f == NULL) {
        printf("\n \n  Skedari nuk hapet");
        return;
    }
    for (int i = 0; i < NriStudenteve; i++) {
        fwrite(&studentet[i], sizeof(struct Student), 1, f);
    }
    fclose(f);
}

void lexo_student() {
    FILE *f;
    f = fopen("student.txt", "r");
    if (f == NULL) {
        printf("\n\n Skedari i studenteve për këtë kurs nuk ekziston ose nuk mund të hapet. \n");
        return;
    }
    NriStudenteve = 0;
    while (fread(&studentet[NriStudenteve], sizeof(struct Student), 1, f)) {
        NriStudenteve++;
    }
    fclose(f);
}

void ruaj_instruktor() {
    FILE *f;
    f = fopen("instruktor.txt", "w");
    if (f == NULL) {
        printf("\n \n  Skedari nuk hapet");
        return;
    }
    for (int i = 0; i < NrInstruktoreve; i++) {
        fwrite(&instruktoret[i], sizeof(struct Instruktor), 1, f);
    }
    fclose(f);
}

void lexo_instruktoret() {
    FILE *f;
    f = fopen("instruktor.txt", "r");
    if (f == NULL) {
        printf("\n\n Skedari i instruktoreve nuk ekziston ose nuk mund të hapet. \n");
        return;
    }
    NrInstruktoreve = 0;
    while (fread(&instruktoret[NrInstruktoreve], sizeof(struct Instruktor), 1, f)) {
        NrInstruktoreve++;
    }
    fclose(f);
}

void ruaj_kurset() {
    FILE *f;
    f = fopen("kurs.txt", "w");
    if (f == NULL) {
        printf("\n \n  Skedari nuk hapet");
        return;
    }
    for (int i = 0; i < nrKurseve; i++) {
        fwrite(&kurset[i], sizeof(struct Kurs), 1, f);
    }
    fclose(f);
}

void lexo_kurset() {
    FILE *f;
    f = fopen("kurs.txt", "r");
    if (f == NULL) {
        printf("\n\n Skedari i kurseve nuk ekziston ose nuk mund të hapet. \n");
        return;
    }
    nrKurseve = 0;
    while (fread(&kurset[nrKurseve], sizeof(struct Kurs), 1, f)) {
        nrKurseve++;
    }
    fclose(f);
}

int instrukton(struct Instruktor instruktor, char kategori[]) {
    if (strcmp(instruktor.kategorite_e_kurseve, kategori) == 0) {
        return 1;
    }
    return 0;
}

int kontrollo_studentin(struct Student student, struct Student studentet[], int NriStudenteve) {
    for (int i = 0; i < NriStudenteve; i++) {
        if (student.ID == studentet[i].ID) {
            return 1;
        }
    }
    return 0;
}

int grup_i_plote(struct Kurs kurs) {
    return (kurs.NrStudenteve >= 6);
}

void ruaj_studentin_ne_kurs(struct Student student, struct Kurs *kurs) {
    if (kurs->NrStudenteve < MAX_STUDENT) {
        kurs->studentet[kurs->NrStudenteve] = student.ID;
        kurs->NrStudenteve++;
        ruaj_kurset(); 
    } else {
        printf("Kursi është i plotë.\n");
    }
}

void fshi_instruktorin(int instruktor_ID) {
    int instruktor_index = -1;
    for (int i = 0; i < NrInstruktoreve; i++) {
        if (instruktoret[i].ID == instruktor_ID) {
            instruktor_index = i;
            break;
        }
    }
    if (instruktor_index == -1) {
        printf("Instruktori me numrin identifikues %d nuk u gjet.\n", instruktor_ID);
        return;
    }
    for (int i = instruktor_index; i < NrInstruktoreve - 1; i++) {
        instruktoret[i] = instruktoret[i + 1];
    }
    NrInstruktoreve--;
    ruaj_instruktor();
    printf("Instruktori u fshi me sukses.\n");
}

void fshi_kursin(int kurs_ID) {
    int kurs_index = -1;
    for (int i = 0; i < nrKurseve; i++) {
        if (kurset[i].ID == kurs_ID) {
            kurs_index = i;
            break;
        }
    }
    if (kurs_index == -1) {
        printf("Kursi me numrin identifikues %d nuk u gjet.\n", kurs_ID);
        return;
    }
    for (int i = kurs_index; i < nrKurseve - 1; i++) {
        kurset[i] = kurset[i + 1];
    }
    nrKurseve--;
    ruaj_kurset();
    printf("Kursi u fshi me sukses.\n");
}

void cregjistro_studentin(int student_ID) {
    int student_index = -1;
    for (int i = 0; i < NriStudenteve; i++) {
        if (studentet[i].ID == student_ID) {
            student_index = i;
            break;
        }
    }
    if (student_index == -1) {
        printf("Studenti me numrin identifikues %d nuk u gjet.\n", student_ID);
        return;
    }
    for (int i = student_index; i < NriStudenteve - 1; i++) {
        studentet[i] = studentet[i + 1];
    }
    NriStudenteve--;
    ruaj_student();
    printf("Studenti u çregjistrua me sukses.\n");
}

void lista_e_kurseve() {
    if (nrKurseve == 0) {
        printf("Nuk ka kurse të regjistruara.\n");
        return;
    }
    printf("\nLista e kurseve të regjistruara:\n");
    for (int i = 0; i < nrKurseve; i++) {
        printf("\nID e kursit: %d\n", kurset[i].ID);
        printf("Data e fillimit: %s\n", kurset[i].data_e_fillimit);
        printf("Ditët: %s\n", kurset[i].ditet);
        printf("Ora e fillimit: %s\n", kurset[i].ora_e_fillimit);
        printf("Kategoria e kursit: %s\n", kurset[i].kategoria_e_kursit);
        printf("Instruktori: %s %s\n", kurset[i].instruktor.emri, kurset[i].instruktor.mbiemri);
    }
}

void lista_e_studenteve() {
    if (NriStudenteve == 0) {
        printf("Nuk ka studentë të regjistruar.\n");
        return;
    }
    printf("\nLista e studentëve të regjistruar:\n");
    for (int i = 0; i < NriStudenteve; i++) {
        printf("\nID e studentit: %d\n", studentet[i].ID);
        printf("Emri: %s\n", studentet[i].emri);
        printf("Mbiemri: %s\n", studentet[i].mbiemri);
        printf("Data e lindjes: %02d/%02d/%04d\n", studentet[i].ditelindja_dita, studentet[i].ditelindja_muaji, studentet[i].ditelindja_viti);
    }
}

void lista_e_instruktoreve() {
    if (NrInstruktoreve == 0) {
        printf("Nuk ka instruktorë të regjistruar.\n");
        return;
    }
    printf("\nLista e instruktorëve të regjistruar:\n");
    for (int i = 0; i < NrInstruktoreve; i++) {
        printf("\nID e instruktorit: %d\n", instruktoret[i].ID);
        printf("Emri: %s\n", instruktoret[i].emri);
        printf("Mbiemri: %s\n", instruktoret[i].mbiemri);
        printf("Data e lindjes: %s\n", instruktoret[i].ditelindja);
        printf("Kategoritë e kurseve: %s\n", instruktoret[i].kategorite_e_kurseve);
    }
}

void lista_e_studenteve_ne_kurs(int kurs_ID) {
    int kurs_index = -1;
    for (int i = 0; i < nrKurseve; i++) {
        if (kurset[i].ID == kurs_ID) {
            kurs_index = i;
            break;
        }
    }
    if (kurs_index == -1) {
        printf("Kursi me numrin identifikues %d nuk u gjet.\n", kurs_ID);
        return;
    }
    struct Kurs kurs = kurset[kurs_index];
    if (kurs.NrStudenteve == 0) {
        printf("Nuk ka studentë të regjistruar në këtë kurs.\n");
        return;
    }
    printf("\nLista e studentëve të regjistruar në kursin me ID %d:\n", kurs.ID);
    for (int i = 0; i < kurs.NrStudenteve; i++) {
        int student_ID = kurs.studentet[i];
        for (int j = 0; j < NriStudenteve; j++) {
            if (studentet[j].ID == student_ID) {
                printf("\nID e studentit: %d\n", studentet[j].ID);
                printf("Emri: %s\n", studentet[j].emri);
                printf("Mbiemri: %s\n", studentet[j].mbiemri);
                printf("Data e lindjes: %02d/%02d/%04d\n", studentet[j].ditelindja_dita, studentet[j].ditelindja_muaji, studentet[j].ditelindja_viti);
                break;
            }
        }
    }
}

void lista_e_studenteve_te_instruktorit(int instruktor_ID) {
    printf("\nLista e kurseve të udhëhequra nga instruktori me ID %d:\n", instruktor_ID);
    for (int i = 0; i < nrKurseve; i++) {
        if (kurset[i].instruktor.ID == instruktor_ID) {
            printf("\nKursi me ID %d:\n", kurset[i].ID);
            lista_e_studenteve_ne_kurs(kurset[i].ID);
        }
    }
}

int main() {
    lexo_student();
    lexo_instruktoret();
    lexo_kurset();
    
    char zgjedhja;
    do {
        menu();
        scanf(" %c", &zgjedhja);
        
        switch (zgjedhja) {
            case '1':
                regjistro_student();
                break;
            case '2':
                regjistro_instruktor();
                break;
            case '3':
                regjistro_kursin();
                break;
            case '4': {
                int student_ID, kurs_ID;
                printf("Vendos ID e studentit: ");
                scanf("%d", &student_ID);
                printf("Vendos ID e kursit: ");
                scanf("%d", &kurs_ID);
                
                int student_index = -1, kurs_index = -1;
                for (int i = 0; i < NriStudenteve; i++) {
                    if (studentet[i].ID == student_ID) {
                        student_index = i;
                        break;
                    }
                }
                for (int i = 0; i < nrKurseve; i++) {
                    if (kurset[i].ID == kurs_ID) {
                        kurs_index = i;
                        break;
                    }
                }
                if (student_index == -1) {
                    printf("Studenti me numrin identifikues %d nuk u gjet.\n", student_ID);
                } else if (kurs_index == -1) {
                    printf("Kursi me numrin identifikues %d nuk u gjet.\n", kurs_ID);
                } else {
                    ruaj_studentin_ne_kurs(studentet[student_index], &kurset[kurs_index]);
                }
                break;
            }
            case '5': {
                int instruktor_ID;
                printf("Vendos ID e instruktorit për të fshirë: ");
                scanf("%d", &instruktor_ID);
                fshi_instruktorin(instruktor_ID);
                break;
            }
            case '6': {
                int kurs_ID;
                printf("Vendos ID e kursit për të fshirë: ");
                scanf("%d", &kurs_ID);
                fshi_kursin(kurs_ID);
                break;
            }
            case '7': {
                int student_ID;
                printf("Vendos ID e studentit për të çregjistruar: ");
                scanf("%d", &student_ID);
                cregjistro_studentin(student_ID);
                break;
            }
            case '8':
                lista_e_kurseve();
                break;
            case '9':
                lista_e_studenteve();
                break;
            case '10':
                lista_e_instruktoreve();
                break;
            case '11': {
                int kurs_ID;
                printf("Vendos ID e kursit për të parë studentët: ");
                scanf("%d", &kurs_ID);
                lista_e_studenteve_ne_kurs(kurs_ID);
                break;
            }
            case '12': {
                int instruktor_ID;
                printf("Vendos ID e instruktorit për të parë studentët: ");
                scanf("%d", &instruktor_ID);
                lista_e_studenteve_te_instruktorit(instruktor_ID);
                break;
            }
            case '0':
                printf("Dalje nga programi.\n");
                break;
            default:
                printf("Zgjedhje e pavlefshme. Provoni përsëri.\n");
                break;
        }
    } while (zgjedhja != '0');
    
    return 0;
}


