<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Access to VGA videoram
 *
 *	(c) 1998 Martin Mares <mj@ucw.cz>
 */
#अगर_अघोषित __ASM_GENERIC_VGA_H
#घोषणा __ASM_GENERIC_VGA_H

/*
 *	On most architectures that support VGA, we can just
 *	recalculate addresses and then access the videoram
 *	directly without any black magic.
 *
 *	Everyone अन्यथा needs to ioremap the address and use
 *	proper I/O accesses.
 */
#अगर_अघोषित VGA_MAP_MEM
#घोषणा VGA_MAP_MEM(x, s) (अचिन्हित दीर्घ)phys_to_virt(x)
#पूर्ण_अगर

#घोषणा vga_पढ़ोb(x) (*(x))
#घोषणा vga_ग_लिखोb(x, y) (*(y) = (x))

#पूर्ण_अगर /* _ASM_GENERIC_VGA_H */
