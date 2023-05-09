Ihandle *filedlg;
Ihandle *controlbtn, *currword;
Ihandle *timer;

FILE *book;

int wpm = 100;

void updatewpm();

int dec(){
  if(wpm > 10)
    wpm--;

  updatewpm();

  return IUP_DEFAULT;
}

int inc(){
  if(wpm < 500)
    wpm++;

  updatewpm();

  return IUP_DEFAULT;
}

int ctrl();

void nextword(){
  char word[50];

  char c;

  for(int i = 0; i < 50; i++){
    c = fgetc(book);
    
    if(c == ',' || c == '.' || c == ' ' || c == '\n'){
      word[i] = 0;
      break;
    } else if(c == EOF){
      ctrl();
      break;
    }

    word[i] = c;
  }

  IupSetAttribute(currword, "TITLE", (char* ) word);
}

void ucountdown(){
  float ms = (60.0/wpm) * 1000;
  char *millis = malloc(4);

  itoa((int) ms, millis, 10);

  IupSetAttribute(timer, "TIME", millis);
}
