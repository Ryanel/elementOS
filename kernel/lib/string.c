int strlen(const char *str)
{
	const char *wrk=str;
    int retval;
    for(retval = 0; *wrk != '\0'; wrk++) retval++;
    return retval;
}