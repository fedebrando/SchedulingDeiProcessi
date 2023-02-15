#ifndef PROTEZIONE
#define PROTEZIONE


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define EXIT_ERROR 1
#define ASSENTE -1

typedef int BOOL;
#define TRUE 1
#define FALSE 0

typedef struct
{
    char nome[2 + 1];
    int durata_burst;
    int priorita;
} PROCESSO;

typedef struct
{
    PROCESSO* processo;
    int burst_rimanente;
} PROCESSO_SCHED;

BOOL inizializzazione(const char* path, int* num_processi, int* durata_quanto, PROCESSO** processi, PROCESSO_SCHED** processi_sched);
void RRschedule(PROCESSO_SCHED* vps, int num_processi, int quanto);
void PrioritySchedule(PROCESSO_SCHED* vps, int num_processi);
void resetProcessiSchedule(PROCESSO_SCHED* vps, int num_processi);
int indexOfMaxPriority(const PROCESSO_SCHED* vps, int num_processi);
void SJFschedule(PROCESSO_SCHED* vps, int num_processi);
int indexOfMinCpuBurst(const PROCESSO_SCHED* vps, int num_processi);
void FCFSschedule(const PROCESSO_SCHED* vps, int num_processi);
BOOL isTerminato(const PROCESSO_SCHED* ps);
void printlnTempoMedioAttesa(int attesa_tot, int num_processi);
void printlnIntestazione(void);
void printlnEsecuzione(const char* nome_processo, int durata_exe_burst, BOOL terminato);
void printlnProcesso(const PROCESSO* p);
void printlnProcessi(const PROCESSO* vp, int dim);


#endif // PROTEZIONE
