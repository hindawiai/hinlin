<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Access to VGA videoram
 *
 *	(c) 1998 Martin Mares <mj@ucw.cz>
 */

#अगर_अघोषित _ASM_X86_VGA_H
#घोषणा _ASM_X86_VGA_H

#समावेश <यंत्र/set_memory.h>

/*
 *	On the PC, we can just recalculate addresses and then
 *	access the videoram directly without any black magic.
 *	To support memory encryption however, we need to access
 *	the videoram as decrypted memory.
 */

#घोषणा VGA_MAP_MEM(x, s)					\
(अणु								\
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)phys_to_virt(x);	\
								\
	अगर (IS_ENABLED(CONFIG_AMD_MEM_ENCRYPT))			\
		set_memory_decrypted(start, (s) >> PAGE_SHIFT);	\
								\
	start;							\
पूर्ण)

#घोषणा vga_पढ़ोb(x) (*(x))
#घोषणा vga_ग_लिखोb(x, y) (*(y) = (x))

#पूर्ण_अगर /* _ASM_X86_VGA_H */
