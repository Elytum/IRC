int  command_match(const char *str, const char *command)
{
   while (*command && *command == *str)
   {
      command++;
      str++;
   }
   return (!*command && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\0'));
}