#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

sem_t pen_sem, paper_sem, question_paper_sem, teacher_sem;

void *teacher(void *arg) {
    while(1) {
        sem_wait(&teacher_sem);
        int item1 = rand() % 3;
        int item2 = rand() % 3;
        while(item1 == item2) {
            item2 = rand() % 3;
        }
        if(item1 == 0 && item2 == 1) {
            printf("Teacher has placed pen and paper on the table\n");
        }
        else if(item1 == 1 && item2 == 0) {
            printf("Teacher has placed pen and paper on the table\n");
        }
        else if(item1 == 0 && item2 == 2) {
            printf("Teacher has placed pen and question paper on the table\n");
        }
        else if(item1 == 2 && item2 == 0) {
            printf("Teacher has placed pen and question paper on the table\n");
        }
        else if(item1 == 1 && item2 == 2) {
            printf("Teacher has placed paper and question paper on the table\n");
        }
            else if(item1 == 1 && item2 == 2) {
            printf("Teacher has placed paper and question paper on the table\n");
        }
        else if(item1 == 2 && item2 == 1) {
            printf("Teacher has placed paper and question paper on the table\n");
        }
        sem_post(&pen_sem);
        sem_post(&paper_sem);
        sem_post(&question_paper_sem);
    }
}

void *student1(void *arg) {
    while(1) {
        sem_wait(&pen_sem);
        printf("Student 1 has picked up the pen\n");
        sem_wait(&paper_sem);
        printf("Student 1 has picked up the paper\n");
        printf("Student 1 is making the assignment\n");

        printf("Student 1 has completed the assignment\n");
        sem_post(&teacher_sem);
    }
}

void *student2(void *arg) {
    while(1) {
        sem_wait(&paper_sem);
        printf("Student 2 has picked up the paper\n");
        sem_wait(&question_paper_sem);
                printf("Student 2 has picked up the question paper\n");
        printf("Student 2 is making the assignment\n");

        printf("Student 2 has completed the assignment\n");
        sem_post(&teacher_sem);
    }
}

void *student3(void *arg) {
    while(1) {
        sem_wait(&pen_sem);
        printf("Student 3 has picked up the pen\n");
        sem_wait(&question_paper_sem);
        printf("Student 3 has picked up the question paper\n");
        printf("Student 3 is making the assignment\n");

        printf("Student 3 has completed the assignment\n");
        sem_post(&teacher_sem);
    }
}

int main() {
    sem_init(&pen_sem, 0, 0);
    sem_init(&paper_sem, 0, 0);
    sem_init(&question_paper_sem, 0, 0);
    sem_init(&teacher_sem, 0, 1);

    pthread_t tid1, tid2, tid3, tid4;

    pthread_create(&tid1, NULL, teacher, NULL);
        pthread_create(&tid2, NULL, student1, NULL);
    pthread_create(&tid3, NULL, student2, NULL);
    pthread_create(&tid4, NULL, student3, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}
