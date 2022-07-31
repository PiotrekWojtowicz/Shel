#include "libmy_movement.h"

char *
rl_gets()
{
  /* If the buffer has already been allo:w
  cated, return the memory
     to the free pool. */
  if (line_read)
    {
      free(line_read);
      line_read = (char *)NULL;
    }

  /* Get a line from the user. */
  line_read = readline("\033[30;47;5mshell$\033[0;0m ");

  /* If the line has any text in it, save it on the history. */
  if (line_read && *line_read)
    add_history(line_read);

  return (line_read);
}