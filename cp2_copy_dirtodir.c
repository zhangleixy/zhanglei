/** cp1.c
 *     version 1 of cp - uses read and write with tunable buffer size
 *
 *     usage: cp1 src dest
 */
#include        <stdio.h>
#include        <unistd.h>
#include        <fcntl.h>
#include	<dirent.h>

#define BUFFERSIZE      4096
#define COPYMODE        0644

void oops(char *, char *);
void cpdtd(char *, char *);

main(int ac, char *av[])
{
        int     in_fd, out_fd, n_chars;
        char    buf[BUFFERSIZE];
						/* check args 	*/
        if ( ac != 3 ){
                fprintf( stderr, "usage: %s source destination\n", *av);
                exit(1);
        }
                            /* open files	*/

        if ( (in_fd=open(av[1], O_RDONLY)) == -1  )
            if ( ( opendir( av[1] ) ) == NULL )
                oops("Cannot open ", av[1]);
            else if ( ( opendir( av[2] ) ) != NULL )
                cpdtd(av[1],av[2]);

        if ( (out_fd=creat( av[2], COPYMODE)) == -1 )
            if ( ( opendir( av[1] ) ) == NULL )
                oops( "Cannot creat", av[2]);
	
						/* copy files	*/

        while ( (n_chars = read(in_fd , buf, BUFFERSIZE)) > 0 )
                if ( write( out_fd, buf, n_chars ) != n_chars )
                        oops("Write error to ", av[2]);
	if ( n_chars == -1 )
			oops("Read error from ", av[1]);

						/* close files	*/

        if ( close(in_fd) == -1 || close(out_fd) == -1 )
                oops("Error closing files","");
}

void oops(char *s1, char *s2)
{
        fprintf(stderr,"Error: %s ", s1);
        perror(s2);
        exit(1);
}


void cpdtd(char *av1, char *av2);
{
    int     in_fd, out_fd, n_chars;
    char    buf[BUFFERSIZE];
    DIR		*dir_ptr;		/* the directory */
    struct dirent	*direntp;		/* each entry	 */

    if ( ( dir_ptr = opendir( av1 ) ) == NULL )
        fprintf(stderr,"ls1: cannot open %s\n", dirname);
    else
    {

        while ( ( direntp = readdir( dir_ptr ) ) != NULL && in_fd=open(direntp->d_name, O_RDONLY) > 0)

        {
            while ( (n_chars = read(in_fd , buf, BUFFERSIZE)) > 0 && write( out_fd, buf, n_chars ) == n_chars )
                if ( write( out_fd, buf, n_chars ) != n_chars )
                    oops("Write error to ", av[2]);

        }

        closedir(dir_ptr);
    }

}












