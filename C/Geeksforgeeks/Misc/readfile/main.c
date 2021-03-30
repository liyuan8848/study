/* A program to find day of a given date */
#include <stdio.h>
#include <string.h>

#define MAX_LEN 256
#define NUM_SYSTEMS 	  	48
#define index_len    5
#define datetime_len    20
#define id_len    4
#define category_len 15
#define part_len    4
#define severity_len     8
#define summary_len    49
#define phyloc_len    30


// definition of HPE Event event structure
struct HpeEvent
{
	char index[index_len + 1];
	char datetime[datetime_len + 1];
	char id[id_len + 1];
	char category[category_len + 1];
	char part[part_len + 1];
	char severity[severity_len + 1];
	char summary[summary_len + 1];
	char phyloc[phyloc_len + 1];
};

// last HPE Text record
static char hpe_timestamps[NUM_SYSTEMS][128] =
{
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z",
	"0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z", "0000-01-01 00:00:00Z"
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
    char lastrecord[128] = {0};
    char search_pattern[6] = "=====";

    
  
    fp = fopen("ocsarchive_hpetextrest","r");
    
    if (fp == NULL) {
      perror("Failed: ");
      return 1;
    }

    strncpy(lastrecord, hpe_timestamps[0], strlen(hpe_timestamps[0]));

    // -1 to allow room for NULL terminator for really long string
    while (fgets(buffer, MAX_LEN - 1, fp))
    {
        // Remove trailing newline
        // buffer[strcspn(buffer, "\n")] = 0;

        // printf("%s\n", buffer);
        //printf("Line number is %d \n", line_num);
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
             
              strncpy(hpeEvtarr[idx].index, buffer+cur_pos, index_len);
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].index);
              hpeEvtarr[idx].index[index_len] = '\0';
              strncpy(hpeEvtarr[idx].datetime, buffer+cur_pos, datetime_len);
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].datetime);
              hpeEvtarr[idx].datetime[datetime_len] = '\0';
              strncpy(hpeEvtarr[idx].id, buffer+cur_pos, id_len);
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].id);
              hpeEvtarr[idx].id[id_len] = '\0';
              strncpy(hpeEvtarr[idx].category, buffer+cur_pos, category_len);
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].category);
              hpeEvtarr[idx].category[category_len] = '\0';
              strncpy(hpeEvtarr[idx].part, buffer+cur_pos, part_len);
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].part);
              hpeEvtarr[idx].part[part_len] = '\0';
              strncpy(hpeEvtarr[idx].severity, buffer+cur_pos, severity_len);
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].severity);
              hpeEvtarr[idx].severity[severity_len] = '\0';
              strncpy(hpeEvtarr[idx].summary, buffer+cur_pos, summary_len);
              cur_pos = cur_pos + sizeof(hpeEvtarr[idx].summary);
              hpeEvtarr[idx].summary[summary_len] = '\0';
              // printf("current postion %d \n", cur_pos);
              strncpy(hpeEvtarr[idx].phyloc, buffer+cur_pos, phyloc_len);
              hpeEvtarr[idx].phyloc[phyloc_len] = '\0';

              if(strncasecmp(hpe_timestamps[0], hpeEvtarr[idx].datetime, strlen(hpeEvtarr[idx].datetime)) < 0) {
		            // log data
                  printf("Log data  %s \n", hpeEvtarr[idx].datetime);
                  if (strncasecmp(lastrecord, hpeEvtarr[idx].datetime, strlen(hpeEvtarr[idx].datetime)) < 0)
                  {
                    strncpy(lastrecord, hpeEvtarr[idx].datetime, strlen(hpeEvtarr[idx].datetime));
                  }

		          }
              idx++;
           }

        // }else if (buffer[0] == '=' && buffer[1]=='=')
        }else if (strstr(buffer, search_pattern)!=NULL)
        {
          event_start = 1;
        }
    }
    strncpy(hpe_timestamps[0], lastrecord, strlen(lastrecord));
    printf("hpe_timestamps is set to %s \n", hpe_timestamps[0]);
    
    fclose(fp);

    strncpy(lastrecord, hpe_timestamps[0], strlen(hpe_timestamps[0]));

    // for (int i = 0; i < idx; i++)
    //   {
    //     // printf("%s %s %s %s %s %s %s %s %s\n", hpeEvtarr[i].index, hpeEvtarr[i].datetime, hpeEvtarr[i].id,hpeEvtarr[i].category,
    //     //  hpeEvtarr[i].part, hpeEvtarr[i].severity, hpeEvtarr[i].summary, hpeEvtarr[i].phyloc);

    //     // printf("%s \n", hpeEvtarr[i].datetime);
    //     // printf("size of hpeEvtarr[i].datetime is %d \n", strlen(hpeEvtarr[i].datetime));

    //     if(strncasecmp(hpe_timestamps[0], hpeEvtarr[i].datetime, strlen(hpeEvtarr[i].datetime)) < 0) {
		//       // log data
    //       printf("Log data  %s \n", hpeEvtarr[i].datetime);
    //       if (strncasecmp(lastrecord, hpeEvtarr[i].datetime, strlen(hpeEvtarr[i].datetime)) < 0)
    //       {
    //         strncpy(lastrecord, hpeEvtarr[i].datetime, strlen(hpeEvtarr[i].datetime));
    //       }

		//    }
    //     // char print_buf[128];
    //     // // snprintf(print_buf,sizeof(print_buf), hpeEvtarr[i].datetime);
    //     // snprintf(print_buf,sizeof(hpeEvtarr[i].datetime)+1, hpeEvtarr[i].datetime);
    //     // printf("%d \n", sizeof(hpeEvtarr[i].index));
    //     // printf("%s \n", hpeEvtarr[i].index);
    //     // printf("%s \n", print_buf);
    //     // printf("size of printbuf is %d \n", sizeof(print_buf));
    //   }

    //     strncpy(hpe_timestamps[0], lastrecord, strlen(lastrecord));
    //     printf("hpe_timestamps is set to %s \n", hpe_timestamps[0]);
    return 0;


} 