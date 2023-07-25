#include <stdarg.h>
#include <unistd.h>

/**
 * _putchar - Writes a character to stdout.
 * @c: The character to be written.
 * Return: On success, the number of characters written.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return write(1, &c, 1);
}

/**
 * print_binary - Print an unsigned int in binary format.
 * @n: The unsigned int to print.
 * Return: The number of characters printed.
 */
int print_binary(unsigned int n)
{
	int count = 0;
	unsigned int mask = 1 << ((sizeof(unsigned int) * 8) - 1);

	while (mask > 0)
	{
		if (n & mask)
			_putchar('1');
		else
			_putchar('0');
		count++;
		mask >>= 1;
	}

	return count;
}

/**
 * print_hex - Print an unsigned int in hexadecimal format.
 * @n: The unsigned int to print.
 * @uppercase: Whether to use uppercase or lowercase hex digits.
 * Return: The number of characters printed.
 */
int print_hex(unsigned int n, int uppercase)
{
	int count = 0;
	char *hex_digits_lowercase = "0123456789abcdef";
	char *hex_digits_uppercase = "0123456789ABCDEF";
	char *hex_digits = uppercase ? hex_digits_uppercase : hex_digits_lowercase;
	int digit;

	if (n == 0)
	{
		_putchar('0');
		count++;
	}
	else
	{
		while (n > 0)
		{
			digit = n % 16;
			_putchar(hex_digits[digit]);
			count++;
			n /= 16;
		}
	}

	return count;
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
			else if (*format == 'd' || *format == 'i')
			{
				int num = va_arg(args, int);
				int divisor = 1;
				if (num < 0)
				{
					_putchar('-');
					count++;
					num = -num;
				}
				while (num / divisor > 9)
					divisor *= 10;
				while (divisor > 0)
				{
					_putchar((num / divisor) + '0');
					count++;
					num %= divisor;
					divisor /= 10;
				}
				format++;
			}
			else if (*format == 'u')
			{
				unsigned int num = va_arg(args, unsigned int);
				int divisor = 1;
				while (num / divisor > 9)
					divisor *= 10;
				while (divisor > 0)
				{
					_putchar((num / divisor) + '0');
					count++;
					num %= divisor;
					divisor /= 10;
				}
				format++;
			}
			else if (*format == 'o')
			{
				unsigned int num = va_arg(args, unsigned int);
				int divisor = 1;
				while (num / divisor > 7)
					divisor *= 8;
				while (divisor > 0)
				{
					_putchar((num / divisor) + '0');
					count++;
					num %= divisor;
					divisor /= 8;
				}
				format++;
			}
			else if (*format == 'x')
			{
				unsigned int num = va_arg(args, unsigned int);
				count += print_hex(num, 0);
				format++;
			}
			else if (*format == 'X')
			{
				unsigned int num = va_arg(args, unsigned int);
				count += print_hex(num, 1);
				format++;
			}
			else if (*format == 'b')
			{
				unsigned int num = va_arg(args, unsigned int);
				count += print_binary(num);
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
