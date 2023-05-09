#include "speedctrl.h"

Ihandle *vbox, *dialog;
Ihandle *wpmhbox, *wpmtext;
Ihandle *incbtn, *decbtn;

bool ctrlswitch = false;

void openbook(){

  filedlg = IupFileDlg();
  IupSetAttribute(filedlg, "TITLE", "Escolher Livro");
  IupSetAttribute(filedlg, "ALLOWNEW", "NO");
  IupSetAttribute(filedlg, "FILTER", "*.txt");
  IupPopup(filedlg, IUP_CURRENT, IUP_CURRENT);
  
  char *bookname = IupGetAttribute(filedlg, "VALUE");

  book = fopen(bookname, "r");

  IupDestroy(filedlg);
}

void ucountdown();

void updatewpm(){
  char *text = malloc(9);

  sprintf(text, "WPM: %d", wpm);
  text[9] = 0;

  IupSetAttribute(wpmtext, "TITLE", text);

  ucountdown();

  free(text);
}

void layout(){

  incbtn = IupButton("+", NULL);
  decbtn = IupButton("-", NULL);
  IupSetCallback(incbtn, "ACTION", (Icallback) inc);
  IupSetCallback(decbtn, "ACTION", (Icallback) dec);
  
  wpmtext = IupLabel("WPM: 100");
  IupSetAttribute(wpmtext, "PADDING", "10");
  
  wpmhbox = IupHbox(wpmtext, incbtn, decbtn, NULL);
  IupSetAttribute(wpmhbox, "GAP", "10");
  
  currword = IupLabel("");
  IupSetAttribute(currword, "FONT", "Helvetica, 15");
  IupSetAttribute(currword, "PADDING", "100");
  IupSetAttribute(currword, "ALIGNMENT", "ACENTER");

  controlbtn = IupButton("Ler", NULL);
  IupSetCallback(controlbtn, "ACTION", (Icallback) ctrl);
  IupSetAttribute(controlbtn, "PADDING", "10x3");

  vbox = IupVbox(wpmhbox, currword, controlbtn, NULL);
  IupSetAttribute(vbox, "ALIGNMENT", "ACENTER");
  IupSetAttribute(vbox, "MARGIN", "60x10");
  IupSetAttribute(vbox, "GAP", "10");

  dialog = IupDialog(vbox);
  IupSetAttribute(dialog, "SIZE", "250xQUARTER");
  IupSetAttribute(dialog, "TITLE", "bookrunner");

  IupShowXY(dialog, IUP_CENTER, IUP_CENTER);
}

int ctrl(){
  ctrlswitch = !ctrlswitch;

  char *msg = "";
  char *run = "";

  if(ctrlswitch){
    msg = "Parar";
    run = "YES";
  } else {
    msg = "Ler";
    run = "NO";
  }

  IupSetAttribute(controlbtn, "TITLE", msg);
  IupSetAttribute(timer, "RUN", run);
  
  return IUP_DEFAULT;
}
