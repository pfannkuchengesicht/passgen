#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>

#include "argParser.h"

int main(int argc, char **argv)
{
  int passwords = 10;
  int passlength = 8;
  unsigned char mask = 0x0F;
  char *passbuf;

  ArgList_t *args = arg_initArgs(argc, argv);
  ArgParam_t *parPws = arg_addParam(args, 'n', "passwords", "Number of passwords to generate.");
  ArgParam_t *parPwl = arg_addParam(args, 'l', "password-length", "Length of each generated password.");
  ArgSwitch_t *swUcAlpha = arg_addSwitch(args, 'A', "UAlpha", "Allow upper case letters.");
  ArgSwitch_t *swLcAlpha = arg_addSwitch(args, 'a', "LAlpha", "Allow lower case letters.");
  ArgSwitch_t *swNumbers = arg_addSwitch(args, '0', "Numbers", "Allow numbers.");
  ArgSwitch_t *swSpecial = arg_addSwitch(args, 's', "Special", "Allow special characters.");
  ArgSwitch_t *swHelp = arg_addSwitch(args, 'h', "help", "Prints the help page.");
  arg_parseArgs(args);

  if(swHelp->switched)
  {
    printf("Usage: %s [<options>]\nOptions:\n", argv[0]);
    arg_printHelp(args);
    arg_destroyArgs(args);
    return 0;
  }


  if(parPws->value && strlen(parPws->value))
  {
    sscanf(parPws->value, "%u", &passwords);
		if(passwords >= 0x00FFFFFF) passwords = 0x00EFFFFF;
		if(passwords <= 0) passwords = 1;
  }

  if(parPwl->value && strlen(parPwl->value))
  {
    sscanf(parPwl->value, "%u", &passlength);
		if(passlength >= 0x00FFFFFF) passlength = 0x00EFFFFF;
		if(passlength <= 0) passlength = 1;
  }

  if(swUcAlpha->switched || swLcAlpha->switched || swNumbers->switched || swSpecial->switched) mask = 0; 
  if(swUcAlpha->switched) mask |= 1 << 0;
  if(swLcAlpha->switched) mask |= 1 << 1;
  if(swNumbers->switched) mask |= 1 << 2;
  if(swSpecial->switched) mask |= 1 << 3;


  passbuf = malloc(passlength + 1);
	if(!passbuf)
	{
		perror("Failed to allocate the password buffer!");
		return EXIT_FAILURE;
	}
  passbuf[passlength] = 0;

  srand(time(0));
  
  int i, j;
  
  for(j = 0; j < passwords; j++)
  {
    for(i = 0; i < passlength; i++)
    {
      int ch = 0;
      while(1)
      {
        ch = rand() % 255;
        if(!isgraph(ch)) continue;
        if((mask & 1 << 0) && isupper(ch)) break;
        if((mask & 1 << 1) && islower(ch)) break;
        if((mask & 1 << 2) && isdigit(ch)) break;
        if((mask & 1 << 3) && ispunct(ch)) break;
      }

      passbuf[i] = ch;
    }
    printf("%s\n", passbuf);
  }

	for(i = 0; i < passlength; i++) passbuf[i] = 0; //zero the memory, just in case	

  free(passbuf); 
  arg_destroyArgs(args); 

  return EXIT_SUCCESS;
}