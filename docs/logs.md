## bugs 1 ##
In file app/load.c  
Date: 15 may
  
    fprintf(stdout, "Load file successeed!\n");  
> Opened stream never closed. Potential resource leak    

Fixed by closing the stream fclose(f)  

## bugs 2 ##
In file app/move.c  
Date: 15 may  
  
    if (k == line) {  
> The left operand of '==' is a garbage value    

Fixed by adding k = 0 before  
