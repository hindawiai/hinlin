<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Access to VGA videoram
 *
 *	(c) 1998 Martin Mares <mj@ucw.cz>
 *	(c) 1999 Asit Mallick <asit.k.mallick@पूर्णांकel.com>
 *	(c) 1999 Don Dugger <करोn.dugger@पूर्णांकel.com>
 */

#अगर_अघोषित __ASM_IA64_VGA_H_
#घोषणा __ASM_IA64_VGA_H_

/*
 * On the PC, we can just recalculate addresses and then access the
 * videoram directly without any black magic.
 */

बाह्य अचिन्हित दीर्घ vga_console_iobase;
बाह्य अचिन्हित दीर्घ vga_console_membase;

#घोषणा VGA_MAP_MEM(x,s)	((अचिन्हित दीर्घ) ioremap(vga_console_membase + (x), s))

#घोषणा vga_पढ़ोb(x)	(*(x))
#घोषणा vga_ग_लिखोb(x,y)	(*(y) = (x))

#पूर्ण_अगर /* __ASM_IA64_VGA_H_ */
