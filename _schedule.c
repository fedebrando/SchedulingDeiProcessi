
#include "_schedule.h"

BOOL inizializzazione(const char* path, int* num_processi, int* durata_quanto, PROCESSO** processi, PROCESSO_SCHED** processi_sched)
{
    int i;
    FILE* cfg = fopen(path, "r");

    if (!cfg)
        return FALSE;

    fscanf(cfg, "# %d %d\n", num_processi, durata_quanto);
    *processi = malloc(*num_processi * sizeof(PROCESSO));
    *processi_sched = malloc(*num_processi * sizeof(PROCESSO_SCHED));

    for (i = 0; i < *num_processi; i++)
    {
        fscanf(cfg, "%s %d %d\n", (*processi)[i].nome, &((*processi)[i].durata_burst), &((*processi)[i].priorita));
        (*processi_sched)[i].processo = &(*processi)[i];
        (*processi_sched)[i].burst_rimanente = (*processi)[i].durata_burst;
    }
    fclose(cfg);

    return TRUE;
}

void RRschedule(PROCESSO_SCHED* vps, int num_processi, int quanto)
{
    int attesa_tot = 0;
    int i;
    int num_processi_attivi = num_processi; // processi non ancora terminati (si presume che tutti i processi forniti abbiano un CPUburst > 0)
    PROCESSO_SCHED* prc_corrente; // processo corrente in esecuzione
    int* burst_corrente;

    printlnIntestazione();
    i = 0;
    while (num_processi_attivi > 0)
    {
        prc_corrente = vps + i % num_processi;
        if (!isTerminato(prc_corrente))
        {
            burst_corrente = &prc_corrente->burst_rimanente;
            if (*burst_corrente > quanto)
            {
                *burst_corrente -= quanto;
                attesa_tot += (num_processi_attivi - 1)*quanto;
                printlnEsecuzione(prc_corrente->processo->nome, quanto, FALSE);
            }
            else
            {
                attesa_tot += (num_processi_attivi - 1)*(*burst_corrente);
                printlnEsecuzione(prc_corrente->processo->nome, *burst_corrente, TRUE);
                *burst_corrente = 0;
                num_processi_attivi--;
            }
        }
        i++;
    }
    printlnTempoMedioAttesa(attesa_tot, num_processi);
}

void PrioritySchedule(PROCESSO_SCHED* vps, int num_processi)
{
    int attesa_tot = 0;
    int i, i_maxPri;
    int* burst_corrente;

    printlnIntestazione();
    for (i = 0; i < num_processi; i++)
    {
        i_maxPri = indexOfMaxPriority(vps, num_processi);
        burst_corrente = &vps[i_maxPri].burst_rimanente;
        printlnEsecuzione(vps[i_maxPri].processo->nome, *burst_corrente, TRUE);
        attesa_tot += (num_processi - 1 - i)*(*burst_corrente);
        *burst_corrente = 0;
    }
    printlnTempoMedioAttesa(attesa_tot, num_processi);
}

void resetProcessiSchedule(PROCESSO_SCHED* vps, int num_processi)
{
    int i;

    for (i = 0; i < num_processi; i++)
        vps[i].burst_rimanente = vps[i].processo->durata_burst;
}

int indexOfMaxPriority(const PROCESSO_SCHED* vps, int num_processi)
{
    int i_minValPri = ASSENTE, i;
    int minValPri;

    for (i = 0; i < num_processi; i++)
    {
        if (isTerminato(vps + i))
            continue;
        else if (i_minValPri == ASSENTE || vps[i].processo->priorita < minValPri)
        {
            i_minValPri = i;
            minValPri = vps[i].processo->priorita;
        }
    }
    return i_minValPri;
}

int indexOfMinCpuBurst(const PROCESSO_SCHED* vps, int num_processi)
{
    int i_minCpu = ASSENTE, i;
    int minCpu;

    for (i = 0; i < num_processi; i++)
    {
        if (isTerminato(vps + i))
            continue;
        else if (i_minCpu == ASSENTE || vps[i].burst_rimanente < minCpu)
        {
            i_minCpu = i;
            minCpu = vps[i].burst_rimanente;
        }
    }
    return i_minCpu;
}

void SJFschedule(PROCESSO_SCHED* vps, int num_processi)
{
    int attesa_tot = 0;
    int i, i_minBurst;
    int* burst_corrente;

    printlnIntestazione();
    for (i = 0; i < num_processi; i++)
    {
        i_minBurst = indexOfMinCpuBurst(vps, num_processi);
        burst_corrente = &vps[i_minBurst].burst_rimanente;
        printlnEsecuzione(vps[i_minBurst].processo->nome, *burst_corrente, TRUE);
        attesa_tot += (num_processi - 1 - i)*(*burst_corrente);
        *burst_corrente = 0;
    }

    printlnTempoMedioAttesa(attesa_tot, num_processi);
}

void FCFSschedule(const PROCESSO_SCHED* vps, int num_processi)
{
    int attesa_tot = 0;
    int i;

    printlnIntestazione();
    for (i = 0; i < num_processi; i++)
    {
        printlnEsecuzione(vps[i].processo->nome, vps[i].burst_rimanente, TRUE);
        attesa_tot += (num_processi - 1 - i)*vps[i].burst_rimanente;
    }

    printlnTempoMedioAttesa(attesa_tot, num_processi);
}

BOOL isTerminato(const PROCESSO_SCHED* ps)
{
    return ps->burst_rimanente == 0;
}

void printlnTempoMedioAttesa(int attesa_tot, int num_processi)
{
    printf("Tempo medio d'attesa: %.2f ut\n", (float)attesa_tot/num_processi);
}

void printlnIntestazione(void)
{
    printf("processo\ttempo_exe (ut)\n");
}

void printlnEsecuzione(const char* nome_processo, int durata_exe_burst, BOOL terminato)
{
    printf("%s\t\t%d\t\t%s\n", nome_processo, durata_exe_burst, (terminato ? "terminato" : ""));
}

void printlnProcesso(const PROCESSO* p)
{
    printf("%s\t%d\t\t%d\n", p->nome, p->durata_burst, p->priorita);
}

void printlnProcessi(const PROCESSO* vp, int dim)
{
    int i;

    printf("nome\tcpu_burst (ut)\tpriorita'\n");
    for (i = 0; i < dim; i++)
        printlnProcesso(vp + i);
}
