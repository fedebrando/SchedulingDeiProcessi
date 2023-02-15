Il programma deve essere lanciato da linea di comando con la seguente sintassi.

$ ./scheduling [fileCfg_path]		(Linux)

C:\> scheduling [fileCfg_path]	(Windows)

Inizialmente vengono mostrati a video tutti i processi letti dal file di configurazione specificato (che ho chiamato "processi.cfg"); successivamente, per ogni algoritmo di scheduling, viene mostrato (su più righe) il loro ordine di esecuzione e infine il tempo medio d'attesa (con precisione fino alla seconda cifra decimale). Ogni riga relativa all'ordine d'esecuzione dei processi contiene le seguenti informazioni:
- il nome del processo eseguito;
- il tempo di esecuzione (in unità temporali);
- una nota finale indicante se il processo risulta terminato (segnalato con la stringa "terminato") o meno.

**************************

L'assegnamento è stato svolto in linguaggio C e implementato in un progetto con l'IDE Code::Blocks. Tutte le funzioni o procedure utilizzate sono state raccolte in una libreria di codice con file di intestazione "_schedule.h".
All'interno di questa cartella sono presenti due files target: uno per Linux ("scheduling") e uno per Windows ("scheduling.exe").

**************************

Federico Brandini
mat. 317271
