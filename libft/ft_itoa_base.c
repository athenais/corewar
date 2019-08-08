#include "libft.h"

int	ft_digitcount_base(unsigned int n, int base)
{
	int i;

	if (n == 0)
		return (1);
	i = 0;
	while (n > 0)
	{
		i++;
		n /= base;
	}
	return (i);
}

char	*ft_itoa_base(int n, int base)
{
	char	*new;
	char	*base_key;
	int		len;

	if (base == 10)
		return (ft_itoa(n));
	base_key = "0123456789abcdef";
	len = ft_digitcount_base(n, base);
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
