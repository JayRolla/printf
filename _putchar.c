/**
 * _putchar - Writes a character to the standard output
 * @c: The character to be written
 * Return:returns 1 written character
 */
int _putchar(char c)
{
    return write(1, &c, 1);
}

