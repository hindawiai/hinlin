<शैली गुरु>
/*
 * include/यंत्र-mips/txx9pपन.स
 * TX39/TX49 PIO controller definitions.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __ASM_TXX9PIO_H
#घोषणा __ASM_TXX9PIO_H

#समावेश <linux/types.h>

काष्ठा txx9_pio_reg अणु
	__u32 करोut;
	__u32 din;
	__u32 dir;
	__u32 od;
	__u32 flag[2];
	__u32 pol;
	__u32 पूर्णांकc;
	__u32 maskcpu;
	__u32 maskext;
पूर्ण;

पूर्णांक txx9_gpio_init(अचिन्हित दीर्घ baseaddr,
		   अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक num);

#पूर्ण_अगर /* __ASM_TXX9PIO_H */
