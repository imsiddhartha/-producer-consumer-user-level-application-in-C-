#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<unistd.h>
#include <sys/types.h>


int str_to_int(char []);

int main(int argc,char* argv[])
{
	if(argc<3)									//command line args required
	{
		printf("ERROR\n");
		_exit(-1);
	}
	int stnum,nums;
	stnum=str_to_int(argv[1]);	
	nums=str_to_int(argv[2]);
	
	
	int *shm,shmid,*semaphore,var,ans;
	key_t key;

	key=2408;
	//int shmget(key_t key, size_t size, int shmflg);----------Create Shared memory
	shmid = shmget(key, 100, 0666);					//100 bytes of shared mem with 0666 permisssion
	
	if(shmid < 0)
	{
		printf("Error while Creating Shared Memory \n");
		_exit(-1);
	}
	
	//void *shmat(int shmid, const void *shmaddr, int shmflg);---------------Attach Shared Memory
	
	shm = (int *)shmat(shmid,NULL,0);					//-NULL sys will itself assigned memory,shm m add of shared mem
	int *shmrm1=shm;
	if(*shm ==  -1) 
	{
        printf("Error while Attaching Shared Memory \n");
        _exit(-1);
      }
      
      key=9000;
	var=shmget(key, sizeof(int), 0666);
	semaphore=(int *)shmat(var,NULL,0);
	
	int *shmrm2=semaphore;
	*shm=0;
	
	int res=stnum;
	int count=1;ans=0;
    	
    	while(count<nums)
    	{
    		
    		//writing
    		res=ans+res;
    		*shm=res;
    		*semaphore=1;			//signal
    		
    		if(count !=1)
 	   		printf("Sending %d to Producer.\n",*shm);				//first time this should not be printing
    		
    		count+=2;
    		
    		if(count>nums)
    			break;
    		
    		while(*semaphore==1);		//1 pe wait 
    		
    		//reading
    		ans=*shm;
 		printf("Revieved %d from Producer. \n",ans);
    	}
    	
    	shmdt((void *) shmrm1);
	shmdt((void *) shmrm2);
	
return 0;
}

int str_to_int(char p[])
{
    int i=0,s=0;

    while(p[i]!='\0')
         {
             s = s*10 + (p[i] - 48);
             i++;
         }
        return s;
    }
