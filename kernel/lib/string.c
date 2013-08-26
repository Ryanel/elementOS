unsigned int strlen(unsigned char *str)
{
	unsigned const char *wrk=str;
    int retval;
    for(retval = 0; *wrk != '\0'; wrk++) retval++;
    return retval;
}
