<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_FIXMAP_H
#घोषणा __ASM_OPENRISC_FIXMAP_H

/* Why exactly करो we need 2 empty pages between the top of the fixed
 * addresses and the top of भव memory?  Something is using that
 * memory space but not sure what right now... If you find it, leave
 * a comment here.
 */
#घोषणा FIXADDR_TOP	((अचिन्हित दीर्घ) (-2*PAGE_SIZE))

#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/page.h>

/*
 * On OpenRISC we use these special fixed_addresses क्रम करोing ioremap
 * early in the boot process beक्रमe memory initialization is complete.
 * This is used, in particular, by the early serial console code.
 *
 * It's not really 'fixmap', per se, but fits loosely पूर्णांकo the same
 * paradigm.
 */
क्रमागत fixed_addresses अणु
	/*
	 * FIX_IOREMAP entries are useful क्रम mapping physical address
	 * space beक्रमe ioremap() is useable, e.g. really early in boot
	 * beक्रमe kदो_स्मृति() is working.
	 */
#घोषणा FIX_N_IOREMAPS  32
	FIX_IOREMAP_BEGIN,
	FIX_IOREMAP_END = FIX_IOREMAP_BEGIN + FIX_N_IOREMAPS - 1,
	__end_of_fixed_addresses
पूर्ण;

#घोषणा FIXADDR_SIZE		(__end_of_fixed_addresses << PAGE_SHIFT)
/* FIXADDR_BOTTOM might be a better name here... */
#घोषणा FIXADDR_START		(FIXADDR_TOP - FIXADDR_SIZE)

#घोषणा __fix_to_virt(x)	(FIXADDR_TOP - ((x) << PAGE_SHIFT))
#घोषणा __virt_to_fix(x)	((FIXADDR_TOP - ((x)&PAGE_MASK)) >> PAGE_SHIFT)

/*
 * 'index to address' translation. If anyone tries to use the idx
 * directly without tranlation, we catch the bug with a शून्य-deference
 * kernel oops. Illegal ranges of incoming indices are caught too.
 */
अटल __always_अंतरभूत अचिन्हित दीर्घ fix_to_virt(स्थिर अचिन्हित पूर्णांक idx)
अणु
	/*
	 * this branch माला_लो completely eliminated after inlining,
	 * except when someone tries to use fixaddr indices in an
	 * illegal way. (such as mixing up address types or using
	 * out-of-range indices).
	 *
	 * If it करोesn't get हटाओd, the linker will complain
	 * loudly with a reasonably clear error message..
	 */
	अगर (idx >= __end_of_fixed_addresses)
		BUG();

	वापस __fix_to_virt(idx);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ virt_to_fix(स्थिर अचिन्हित दीर्घ vaddr)
अणु
	BUG_ON(vaddr >= FIXADDR_TOP || vaddr < FIXADDR_START);
	वापस __virt_to_fix(vaddr);
पूर्ण

#पूर्ण_अगर
