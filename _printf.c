#include <stdarg.h>
#include <unistd.h>

/**
 * _putchar - Writes a character to stdout.
 * @c: The character to be written.
 * Return: On success, the number of characters written.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return write(1, &c, 1);
}

/**
 * _printf - Print output according to a format.
 * @format: A character string with format specifiers.
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char current_char;

	va_start(args, format);

	if (format == NULL)
		return -1;

	while (*format)
	{
		current_char = *format;
		if (current_char == '%')
		{
			format++;
			if (*format == '\0')
				return -1;

			if (*format == '%')
			{
				_putchar('%');
				format++;
				count++;
			}
			else if (*format == 'c')
			{
				char c = va_arg(args, int);
				_putchar(c);
				format++;
				count++;
			}
			else if (*format == 's')
			{
				char *str = va_arg(args, char*);
				if (str == NULL)
					str = "(null)";
				while (*str)
				{
					_putchar(*str);
					str++;
					count++;
				}
				format++;
			}
			else
			{
				_putchar('%');
				count++;
			}
		}
		else
		{
			_putchar(current_char);
			format++;
			count++;
		}
	}

	va_end(args);
	return count;
}
