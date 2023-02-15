/*
 * Federico Brandini (mat. 317271)
 * 24/04/2022
 */
#include "_schedule.h"

int main(int argc, char** argv)
{
    int num_processi;
    int durata_quanto;
    PROCESSO* processi = NULL;
    PROCESSO_SCHED* processi_sched = NULL;

    //validazione parametri su linea di comando
    if (argc != 2)
    {
        printf("Errore: inserire come parametro su linea di comando il nome del file di configurazione o il reativo path.\n");
        return EXIT_ERROR;
    }

    // lettura del file di configurazione (allocazione dei processi nei vettori)
    if (!inizializzazione(argv[1], &num_processi, &durata_quanto, &processi, &processi_sched))
    {
        printf("Errore: lettura del file di configurazione non riuscita.\n");
        return EXIT_ERROR;
    }

    // visualizzazione di tutti i processi
    printf("Processi\n");
    printlnProcessi(processi, num_processi);
    printf("\n");

    // FCFS schedule
    printf("\nFCFS\n");
    FCFSschedule(processi_sched, num_processi);

    // SJF schedule
    printf("\nSJF\n");
    SJFschedule(processi_sched, num_processi);
    resetProcessiSchedule(processi_sched, num_processi);

    // Priorita' schedule
    printf("\nPriorita'\n");
    PrioritySchedule(processi_sched, num_processi);
    resetProcessiSchedule(processi_sched, num_processi);

    // RR schedule
    printf("\nRR (quanto = %d)\n", durata_quanto);
    RRschedule(processi_sched, num_processi, durata_quanto);

    // liberazione della memoria allocata
    free(processi);
    free(processi_sched);

    return 0;
}
