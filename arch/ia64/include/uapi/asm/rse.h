<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_IA64_RSE_H
#घोषणा _ASM_IA64_RSE_H

/*
 * Copyright (C) 1998, 1999 Hewlett-Packard Co
 * Copyright (C) 1998, 1999 David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * Register stack engine related helper functions.  This file may be
 * used in applications, so be careful about the name-space and give
 * some consideration to non-GNU C compilers (though __अंतरभूत__ is
 * fine).
 */

अटल __अंतरभूत__ अचिन्हित दीर्घ
ia64_rse_slot_num (अचिन्हित दीर्घ *addr)
अणु
	वापस (((अचिन्हित दीर्घ) addr) >> 3) & 0x3f;
पूर्ण

/*
 * Return TRUE अगर ADDR is the address of an RNAT slot.
 */
अटल __अंतरभूत__ अचिन्हित दीर्घ
ia64_rse_is_rnat_slot (अचिन्हित दीर्घ *addr)
अणु
	वापस ia64_rse_slot_num(addr) == 0x3f;
पूर्ण

/*
 * Returns the address of the RNAT slot that covers the slot at
 * address SLOT_ADDR.
 */
अटल __अंतरभूत__ अचिन्हित दीर्घ *
ia64_rse_rnat_addr (अचिन्हित दीर्घ *slot_addr)
अणु
	वापस (अचिन्हित दीर्घ *) ((अचिन्हित दीर्घ) slot_addr | (0x3f << 3));
पूर्ण

/*
 * Calculate the number of रेजिस्टरs in the dirty partition starting at BSPSTORE and
 * ending at BSP.  This isn't simply (BSP-BSPSTORE)/8 because every 64th slot stores
 * ar.rnat.
 */
अटल __अंतरभूत__ अचिन्हित दीर्घ
ia64_rse_num_regs (अचिन्हित दीर्घ *bspstore, अचिन्हित दीर्घ *bsp)
अणु
	अचिन्हित दीर्घ slots = (bsp - bspstore);

	वापस slots - (ia64_rse_slot_num(bspstore) + slots)/0x40;
पूर्ण

/*
 * The inverse of the above: given bspstore and the number of
 * रेजिस्टरs, calculate ar.bsp.
 */
अटल __अंतरभूत__ अचिन्हित दीर्घ *
ia64_rse_skip_regs (अचिन्हित दीर्घ *addr, दीर्घ num_regs)
अणु
	दीर्घ delta = ia64_rse_slot_num(addr) + num_regs;

	अगर (num_regs < 0)
		delta -= 0x3e;
	वापस addr + num_regs + delta/0x3f;
पूर्ण

#पूर्ण_अगर /* _ASM_IA64_RSE_H */
