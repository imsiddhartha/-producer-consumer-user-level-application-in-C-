#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<unistd.h>
#include <sys/types.h>

int str_to_int(char []);


int main(int argc,char* argv[])
{
	if(argc<3)
	{
		printf("ERROR\n");
		_exit(-1);
	}

	int stnum,nums;

	stnum=str_to_int(argv[1]);	
	nums=str_to_int(argv[2]);
		
	int *shm,shmid,var,*semaphore,ans;
	key_t key;

	key=2408;
	//Create Shared memory
	shmid = shmget(key, 100, IPC_CREAT|0666);				//100 bytes of shared mem with 0666 permisssion
	if(shmid < 0)
	{
		printf("Error while Creating Shared Memory \n");
		_exit(-1);
	}
	
	//void *shmat(int shmid, const void *shmaddr, int shmflg);---------------Attach Shared Memory
	shm =(int *) shmat(shmid,NULL,0);					//-NULL sys will itself assigned memory,shm m add of shared mem
	int *shmrm1=shm;
	if(*shm ==  -1) 
	{
        printf("Error while Attaching Shared Memory \n");
        _exit(-1);
      }
      
      key=9000;
	var=shmget(key, sizeof(int), IPC_CREAT|0666);
	semaphore=(int *)shmat(var,NULL,0);
	
	int *shmrm2=semaphore;
	
	*semaphore=0;
	*shm=0;
	
	int res=stnum;
	int count=2;
 	
 	while(count<nums)
 	{
 		while(*semaphore==0);
 		//reading
 		
 		ans=*shm;
 		printf("Revieved %d from Consumer. \n",ans);
 		
 		//write
 		
 		res=ans+res;
 		*shm=res;
 		printf("Sending %d to Consumer.\n",*shm);
 		
 		*semaphore=0;
 		count+=2;
 	}

	//int shmdt(const void *shmaddr);
	shmdt((void *) shmrm1);										//deattaching shared mem
	shmdt((void *) shmrm2);
    
    //       int shmctl(int shmid, int cmd, struct shmid_ds *buf);
	shmctl(shmid,IPC_RMID,NULL);									//removing shared mem
	shmctl(var,IPC_RMID,NULL);
	
return 0;
}
int str_to_int(char p[])										//fucntion to convert str to int
{
    int i=0,s=0;

    while(p[i]!='\0')
         {
             s = s*10 + (p[i] - 48);
             i++;
         }
        return s;
    }
