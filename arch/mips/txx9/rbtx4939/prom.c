<शैली गुरु>
/*
 * rbtx4939 specअगरic prom routines
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/rbtx4939.h>

व्योम __init rbtx4939_prom_init(व्योम)
अणु
	अचिन्हित दीर्घ start, size;
	u64 win;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (!((__u32)____raw_पढ़ोq(&tx4939_ddrcptr->winen) & (1 << i)))
			जारी;
		win = ____raw_पढ़ोq(&tx4939_ddrcptr->win[i]);
		start = (अचिन्हित दीर्घ)(win >> 48);
		size = (((अचिन्हित दीर्घ)(win >> 32) & 0xffff) + 1) - start;
		memblock_add(start << 20, size << 20);
	पूर्ण
	txx9_sio_अक्षर_दो_init(TX4939_SIO_REG(0) & 0xfffffffffULL);
पूर्ण
