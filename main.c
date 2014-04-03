#include <malloc.h>
#include <unistd.h>
#include <sys/mman.h>
void
* my_malloc ( size_t size)
{
void *p;
p = sbrk (0); // current location of break pointer
/* If sbrk fails , we return NULL */
if ( sbrk (size) == (void *) -1)
return NULL;
return p;
}
void * malloc2 ( size_t size )
{
    int *plen;
    int len = size + sizeof( size ); // Add sizeof( size ) for holding length.

    plen = mmap( 0, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0 );

    *plen = len;                     // First 4 bytes contain length.
    return (void*)(&plen[1]);        // Memory that is after length variable.
}

void free2 ( void * ptr )
{
    int *plen = (int*)ptr;
    int len;

    plen--;                          // Reach top of memory
    len = *plen;                     // Read length

    munmap( (void*)plen, len );
}
void main()
{
	printf("\nBytes Left: %x\n",sbrk(0));
	char *p = malloc2(10);
	strcpy(p,"Hello");
	printf("\n Data : %s: size :%x Bytes Left\n",p,sbrk(0));
//	brk(p+100);
	free2(p);
	//printf("\n Data : %s: size :%x Bytes Left\n",p,sbrk(0));
}
