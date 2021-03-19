/* A program to find day of a given date */
#include <stdio.h>
#include <string.h>

#define MAX_LEN 256


// definition of HPE Event event structure
struct HpeEvent
{
	char index[5];
	char date[10];
	char time[9];
	char id[4];
	char category[15];
	char part[4];
	char severity[8];
	char summary[49];
	char phyloc[30];
};

  
/* Driver function to test above function */
int main() 
{ 
    FILE *fp;
    struct HpeEvent hpeEvtarr[1024];
    int idx = 0;
    int line_num = 1;
    int event_start = 0;
    char buffer[MAX_LEN];
    fp = fopen("ocsarchive_hpetextrest","r");
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }
    // -1 to allow room for NULL terminator for really long string
    while (fgets(buffer, MAX_LEN - 1, fp))
    {
        // Remove trailing newline
        // buffer[strcspn(buffer, "\n")] = 0;

        // printf("%s\n", buffer);
        printf("Line number is %d \n", line_num);
        line_num++;
        if (event_start == 1)
        {
           if (buffer[0]== '\n')
           {
             event_start = 0;
             break;
           }
           else
             {
              int cur_pos = 0;
             
              strncpy(hpeEvtarr[idx].index, buffer+cur_pos, sizeof(hpeEvtarr[idx].index));
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].index) + 1;
              strncpy(hpeEvtarr[idx].date, buffer+cur_pos, sizeof(hpeEvtarr[idx].date));
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].date) + 1;
              strncpy(hpeEvtarr[idx].time, buffer+cur_pos, sizeof(hpeEvtarr[idx].time));
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].time) + 1;
              strncpy(hpeEvtarr[idx].id, buffer+cur_pos, sizeof(hpeEvtarr[idx].id));
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].id) + 1;
              strncpy(hpeEvtarr[idx].category, buffer+cur_pos, sizeof(hpeEvtarr[idx].category));
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].category) + 1;
              strncpy(hpeEvtarr[idx].part, buffer+cur_pos, sizeof(hpeEvtarr[idx].part));
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].part) + 1;
              strncpy(hpeEvtarr[idx].severity, buffer+cur_pos, sizeof(hpeEvtarr[idx].severity));
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].severity) + 1;
              strncpy(hpeEvtarr[idx].summary, buffer+cur_pos, sizeof(hpeEvtarr[idx].summary));
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].summary) + 1;
              // printf("current postion %d", cur_pos);
              strncpy(hpeEvtarr[idx].phyloc, buffer+cur_pos, sizeof(hpeEvtarr[idx].phyloc)-1);
              idx++;
           }

        }else if (buffer[0] == '=' && buffer[1]=='=')
        {
          event_start = 1;
        }
    }
    
    fclose(fp);

    for (int i = 0; i < idx; i++)
      {
        // printf("%s %s %s %s %s %s %s %s %s \n", hpeEvtarr[i].index, hpeEvtarr[i].date, hpeEvtarr[i].time, hpeEvtarr[i].id,hpeEvtarr[i].category,
        //  hpeEvtarr[i].part, hpeEvtarr[i].severity, hpeEvtarr[i].summary, hpeEvtarr[i].phyloc);

        // printf("%s \n", hpeEvtarr[i].index);
        printf("%s \n", hpeEvtarr[i].phyloc);
      }
    return 0;


} 