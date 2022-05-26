#include <stdio.h>

struct Patient{
  int no;
  char name[50];
  int age;
  char disease_info[50];
};
typedef struct Patient setPatient;

int main(){
  FILE *fptr;
  setPatient Patient;
  int selection=0;
  int search=0;
  int line_ct=0;

  while (selection != -1){
    printf("Select number to choose operation:\n\t1 -> Create file\n\t2 -> Insert a new record\n\t3 -> List all records\n\t4 -> Search a record\n\t5 -> Delete a record\n\t6 -> Modify a record\n\nPress -1 for stop the program...\n\n");
    scanf("%d", &selection);
    printf("\n");
    switch (selection){
      case 1:
        if ((fptr = fopen("patients_db.dat", "w")) == NULL){
          printf("[ERR] File can't be created!\n");
        } 
        else{
          printf("The file is successfully created!\n");
          fclose(fptr);
        }
        break;
      case 2:
        if ((fptr = fopen("patients_db.dat", "a")) == NULL){
          printf("[ERR] File can't be created!\n");
        } 
        else{
          printf("Enter 'Patient No', 'Name', 'Age' and 'Disease Infos':\n");
          scanf("%d%s%d%s", &Patient.no, Patient.name, &Patient.age, Patient.disease_info);
          fwrite(&Patient, sizeof(struct Patient), 1, fptr);
          printf("The record created successfully.\n");
          fclose(fptr);
        }          
        break;
      case 3:
        if ((fptr = fopen("patients_db.dat", "r")) == NULL){
          printf("[ERR] File can't be created!\n");
        }
        else{
          while (!feof(fptr)){
            fread(&Patient, sizeof(struct Patient), 1, fptr);
            if (Patient.no != 0){
              printf("%-15d%-15s%-15d%-15s\n", Patient.no, Patient.name, Patient.age, Patient.disease_info);              
            }
            fread(&Patient, sizeof(struct Patient), 1, fptr);
          }          
          fclose(fptr);
        }
        break;
      case 4:
         if ((fptr = fopen("patients_db.dat", "r")) == NULL){
          printf("[ERR] File can't be created!\n");
        }
        else{
          printf("Enter a Patient Number (to search): ");
          scanf("%d", &search);
          while (!feof(fptr)){
            fread(&Patient, sizeof(struct Patient), 1, fptr);
            if (Patient.no == search)
              printf("\n%-15d%-15s%-15d%-15s\n", Patient.no, Patient.name, Patient.age, Patient.disease_info);
            fread(&Patient, sizeof(struct Patient), 1, fptr);
          }
        }
        break;
        case 5:
         if ((fptr = fopen("patients_db.dat", "r+")) == NULL){
          printf("[ERR] File can't be created!\n");
        }
        else{
          printf("Enter the Patient Number (to delete): ");
          scanf("%d", &search);
          while (!feof(fptr)){
            fread(&Patient, sizeof(struct Patient), 1, fptr);
            if (Patient.no == search){
              setPatient DeletedPatient = { 
                .no = 0,
                .name = "deleted\0",
                .age = 0,
                .disease_info = "deleted\0"
              };
              fseek(fptr, 0, line_ct);
              fwrite(&DeletedPatient, sizeof(struct Patient), 1, fptr);
            }
            fread(&Patient, sizeof(struct Patient), 1, fptr);
            line_ct++;
          }
          printf("Successfully Deleted!");
          line_ct = 0;
        }
        break;
        case 6:
         if ((fptr = fopen("patients_db.dat", "r+")) == NULL){
          printf("[ERR] File can't be created!\n");
        }
        else{
          printf("Enter the Patient Number (to modify): ");
          scanf("%d", &search);
          while (!feof(fptr)){
            fread(&Patient, sizeof(struct Patient), 1, fptr);
            if (Patient.no == search){
              printf("Enter 'Patient No', 'Name', 'Age' and 'Disease Infos':\n");
              scanf("%d%s%d%s", &Patient.no, Patient.name, &Patient.age, Patient.disease_info);
              fseek(fptr, 0, line_ct);
              fwrite(&Patient, sizeof(struct Patient), 1, fptr);
            }
            fread(&Patient, sizeof(struct Patient), 1, fptr);
            line_ct++;
          }
          printf("Successfully Modified!");
          line_ct = 0;
        }
        break;    
    }
    printf("\n---------------------------------\n");
    printf("---------------------------------\n\n");
  }
  return 0;
}