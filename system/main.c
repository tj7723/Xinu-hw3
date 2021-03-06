/*  main.c  - main */

#include <xinu.h>

void sndch(char , int32 );

process	main(void)
{

    //sleep(1); // give the system time to full boot before running out test.
    resume(create(sndch, 2000, 1, "send a", 2, 'A', 10));
    resume(create(sndch, 2000, 200, "send b", 2, 'B', 25));
    resume(create(sndch, 2000, 1, "send c", 2, 'C', 9));
    resume(create(sndch, 2000, 50, "send d", 2, 'D', 5));
    resume(create(sndch, 2000, 5, "send e", 2, 'E', 8));

    return OK;
}

void sndch(char ch, int32 xtimes)
{
    int32 i;
    
    while(i < xtimes)
    {
        kputc(ch);
		i++;
    }
}
char *prssb[] = 
{
	"FREE ",
	"CURR ", 
	"READY ", 
	"RECV ", 
	"SLEEP ", 
	"SUSP ", 
	"WAIT ", 
	"RECTIM",
};

void dumpProctab(int32 freeflag)

{ 
	int32 i;

	struct procent *p;

	kprintf("Process table dump:\n\n"); 
	//kprintf("Num\tState\tPrio\tSem\tName\tmall\n"); 
        kprintf("Num\tState\tPrio\tSem\tName\n"); 
	kprintf("----------------------------------"); 
	kprintf("----------------------------------\n");
	
	for (i = 0; i < NPROC; i++) 
	{

		p = &proctab[i];

		if (freeflag || (p->prstate != PR_FREE)) 
		{
			kprintf("%d\t%6s\t%d\t%d\t%s\t\n", i, prssb[p->prstate], p->prprio, p->prsem, p->prname);
                        //kprintf("%d\t%6s\t%d\t%d\t%s\t%u\n", i, prssb[p->prstate], p->prprio, p->prsem, p->prname, p->malleable);
		}

	}
}
