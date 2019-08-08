#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <asm.h>

char	*ft_itoa_bse(int n, int base, int len)
{
	char	*new;
	char	*base_key;

	if (base == 10)
		return (ft_itoa(n));
	base_key = "0123456789abcdef";
	if (!(new = ft_strnew(len)))
		return (NULL);
	len--;
	while (len >= 0)
	{
		new[len] = base_key[n % base];
		n /= base;
		len--;
	}
	return (new);
}

void        write_binary_to_file(const char *code, t_file *file, uint8_t *buff, int *bit_cnt)
{
   char    c;
   int     bit;

    while ((c = *code))
    {
        bit = c - '0';
        *buff |= bit << (7 - *bit_cnt);
        ++(*bit_cnt);
        if (*bit_cnt == 8)
        {
            ft_putchar_fd(*buff, file->fd_cor);
            *buff = 0;
            *bit_cnt = 0;
        }
        code++;
    }
    //add dumping;  
}

void        write_to_cor(int byte, int oct, t_file *file)
{
    char        *byte_code;
    int         bit_cnt;
    uint8_t     buffer;
//2 complements !!

    buffer = 0;
    bit_cnt = 0;
    byte_code = ft_itoa_bse(byte, 2, oct);
    write_binary_to_file(byte_code, file, &buffer, &bit_cnt);
    buffer = 0;
    bit_cnt = 0;
 //   printf("%s = byte\n", byte_code);
}
