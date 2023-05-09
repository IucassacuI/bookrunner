#include <iup.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "gui.h"

int main(int argc, char **argv){

  IupOpen(&argc, &argv);

  openbook();
  
  layout();

  timer = IupTimer();
  IupSetAttribute(timer, "TIME", "400");
  IupSetCallback(timer, "ACTION_CB", (Icallback) nextword);
  
  IupMainLoop();

  IupDestroy(timer);
  
  IupClose();

  fclose(book);

  return EXIT_SUCCESS;
}
