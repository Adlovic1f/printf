#include <stdio.h>

unsigned int convert_di(va_list args, buffer_t *output,
            unsigned char flags, int wid, int prec, unsigned char len)
{
	long int d;
	unsigned int ret = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	d = (len == LONG) ? va_arg(args, long int) : va_arg(args, int);	
	d = (len == SHORT) ? (short)d : d;

	if (SPACE_FLAG == 1 && d >= 0)
		ret += _memcpy(output, &space, 1);

	if (prec <= 0 && NEG_FLAG == 0)
	{
		count = (d == LONG_MIN) ? 19 : 0;
		for (long int copy = (d < 0) ? -d : d; copy > 0; copy /= 10, count++);
		count += (d == 0) + (d < 0) + (PLUS_FLAG == 1 && d >= 0) + (SPACE_FLAG == 1 && d >= 0);

		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			ret += _memcpy(output, &plus, 1);
		if (ZERO_FLAG == 1 && d < 0)
			ret += _memcpy(output, &neg, 1);

		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (wid -= count; wid > 0; wid--)
			ret += _memcpy(output, &pad, 1);
	}

	if (ZERO_FLAG == 0 && d < 0)
		ret += _memcpy(output, &neg, 1);
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		ret += _memcpy(output, &plus, 1);

	if (!(d == 0 && prec == 0))
		ret += convert_sbase(output, d, "0123456789", flags, 0, prec);

	ret += print_neg_width(output, ret, flags, wid);

	return ret;
}

