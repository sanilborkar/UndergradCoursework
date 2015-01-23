#include "iostream"
#include "cstdio"
#include "cstdlib"

using namespace std;

const int FRAMESIZE = 64;
const int DLE = 10;
const int STX = 2;
const int ETX = 3;
const int SEQLEN = 5;

void NetworkLayer ( char *filename )
{
     FILE *fp,*fp2;
     fp = fopen(filename, "r");
     fp2 = fopen(strcat(filename,".output"), "w");
     if ( fp == NULL )
     {
          cout<<"Error accessing network layer!";
          exit(1);
     }
     if ( fp2 == NULL )
     {
          cout<<"Error accessing physical layer!";
          exit(1);
     }
     
     int seqno = 0;
     while ( !feof(fp) )
     {

         int checksum;
         char frame[FRAMESIZE+SEQLEN+6];
            
         frame[0]=DLE;
         frame[1]=STX;

         char chrno[SEQLEN];
         itoa(seqno,chrno,10);
                
         for (int i=0 ; i<SEQLEN-strlen(chrno) ; i++)
             frame[2+i] = '0';
         for (int i=SEQLEN-strlen(chrno) ; i<SEQLEN ; i++)
             frame[2+i] = chrno[i-(SEQLEN-strlen(chrno))];
                  
         for ( int i=1 ; i<=FRAMESIZE ; i++ )
         {
             frame[SEQLEN+1+i] = fgetc(fp);       
             checksum = checksum^frame[SEQLEN+1+i];
             if ( feof(fp) )
             {
                  for (;i<=FRAMESIZE;i++)
                  {
                     frame[SEQLEN+1+i] = ' ';       
                     checksum = checksum^frame[SEQLEN+1+i];                      
                  }
                  break;
             }   
         }
                
         frame[SEQLEN+FRAMESIZE+2]=checksum;
         frame[SEQLEN+FRAMESIZE+3]=DLE;
         frame[SEQLEN+FRAMESIZE+4]=ETX;
         frame[SEQLEN+FRAMESIZE+5]='\0';
         fputs(frame,fp2);
         
         seqno++;
    }
}

void PhysicalLayer(char *filename)
{
     FILE *fp,*fp2;
     fp = fopen(filename, "r");
     char *tmpname = new char[strlen(filename)+7];
     strcpy(tmpname,filename);
     strcat(tmpname,".output");
     fp2 = fopen(tmpname, "w");
     if ( fp == NULL )
     {
          cout<<"Error accessing physical layer!";
          exit(1);
     }
     if ( fp2 == NULL )
     {
          cout<<"Error accessing physical layer!";
          exit(1);
     }
     fclose(fp2);
     int seqno = 0;
     int errcount=0;
     while ( !feof(fp) )
     {
         int checksum;
         char frame[FRAMESIZE+SEQLEN+6];
            
         frame[0]=fgetc(fp);
         frame[1]=fgetc(fp);

         if (feof(fp))
            exit(0);
                 
         if ( frame[0]!=DLE || frame[1]!=STX )
         {
              char* errmsg;
              char *frameno;
              itoa(seqno,frameno,10);
              strcpy(errmsg,frameno);              
              strcat(errmsg," ");
              char *errnum;
              itoa(errcount,errnum,10);
              strcat(errmsg,errnum);
              strcat(errmsg," MISSING START FLAG\n");
              strcpy(tmpname,filename);
              strcat(tmpname,".error");
              fp2 = fopen(tmpname, "a");
              fputs(errmsg,fp2);
              fclose(fp2);
              fputs(errmsg,fp2);
         }
        
         char chrno[SEQLEN];
         for (int i=0;i<SEQLEN;i++)
             chrno[i]=fgetc(fp);
         
         chrno[SEQLEN]='\0';
         
         int fseqno = atoi(chrno);
         
         if ( fseqno > seqno )
         {
              char errmsg[80];
              char frameno[SEQLEN];
              itoa(seqno,frameno,10);
              strcpy(errmsg,frameno);              
              strcat(errmsg," ");
              char errnum[SEQLEN];
              itoa(errcount,errnum,10);
              strcat(errmsg,errnum);
              strcat(errmsg," MISSING SEQUENCE NUMBER\n");
              strcpy(tmpname,filename);
              strcat(tmpname,".error");
              fp2 = fopen(tmpname, "a");
              fputs(errmsg,fp2);
              fclose(fp2);
              fputs(errmsg,fp2);
         }

         bool flag = true;
         if ( fseqno < seqno )
         {
              flag = false;
         }
         
         for ( int i=1 ; i<=FRAMESIZE ; i++ )
         {
             frame[SEQLEN+1+i] = fgetc(fp);       
             checksum = checksum^frame[SEQLEN+1+i];
             if ( feof(fp) )
             {
                  char* errmsg;
                  char *frameno;
                  itoa(seqno,frameno,10);
                  strcpy(errmsg,frameno);              
                  strcat(errmsg," ");
                  char *errnum;
                  itoa(errcount,errnum,10);
                  strcat(errmsg,errnum);
                  strcat(errmsg," MISSING END FLAG\n");
                  strcpy(tmpname,filename);
                  strcat(tmpname,".error");
                  fp2 = fopen(tmpname, "a");
                  fputs(errmsg,fp2);
                  fclose(fp2);
                  fputs(errmsg,fp2);
             }
         }
       
         int fchecksum = fgetc(fp);
         
         if ( checksum != checksum )
         {
              char* errmsg;
              char *frameno;
              itoa(seqno,frameno,10);
              strcpy(errmsg,frameno);              
              strcat(errmsg," ");
              char *errnum;
              itoa(errcount,errnum,10);
              strcat(errmsg,errnum);
              strcpy(tmpname,filename);
              strcat(tmpname,".error");
              fp2 = fopen(tmpname, "a");
              fputs(errmsg,fp2);
              fclose(fp2);
              fputs(errmsg,fp2);
         }
   
         frame[SEQLEN+FRAMESIZE+3]=fgetc(fp);
         frame[SEQLEN+FRAMESIZE+4]=fgetc(fp);
                      
         if ( frame[SEQLEN+FRAMESIZE+3]!=DLE || frame[SEQLEN+FRAMESIZE+4]!=ETX )
         {
              char* errmsg;
              char *frameno;
              itoa(seqno,frameno,10);
              strcpy(errmsg,frameno);              
              strcat(errmsg," ");
              char *errnum;
              itoa(errcount,errnum,10);
              strcat(errmsg,errnum);
              strcat(errmsg," MISSING END FLAG\n");
              strcpy(tmpname,filename);
              strcat(tmpname,".error");
              fp2 = fopen(tmpname, "a");
              fputs(errmsg,fp2);
              fclose(fp2);
         }

         if ( flag==true )
         {
              strcpy(tmpname,filename);
              strcat(tmpname,".output");
              fp2 = fopen(tmpname, "a");
              fputs(frame+SEQLEN+2,fp2);
              fclose(fp2);
         }                        
         seqno++;
    }
}

int main(int argc, char* argv[])
{
    if ( argc != 3 )
    {
         cout<<"Incorrect number of arguments!!!";
         exit(1);
    }
    
    if ( argv[1][0] == '-' && argv[1][1] == 'n' )
    {
         NetworkLayer( argv[2] );
    }
    else
    {
        if ( argv[1][0] == '-' && argv[1][1] == 'p' )
        {
             PhysicalLayer( argv[2] );
        }
        else
        {
             cout<<"Incorrect number of arguments!!!";
             exit(1);
        }
    }
}
