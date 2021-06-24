<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _PPC_BOOT_PAGE_H
#घोषणा _PPC_BOOT_PAGE_H
/*
 * Copyright (C) 2001 PPC64 Team, IBM Corp
 */

#अगर_घोषित __ASSEMBLY__
#घोषणा ASM_CONST(x) x
#अन्यथा
#घोषणा __ASM_CONST(x) x##UL
#घोषणा ASM_CONST(x) __ASM_CONST(x)
#पूर्ण_अगर

/* PAGE_SHIFT determines the page size */
#घोषणा PAGE_SHIFT	12
#घोषणा PAGE_SIZE	(ASM_CONST(1) << PAGE_SHIFT)
#घोषणा PAGE_MASK	(~(PAGE_SIZE-1))

/* align addr on a size boundary - adjust address up/करोwn अगर needed */
#घोषणा _ALIGN_UP(addr, size)	(((addr)+((size)-1))&(~((typeof(addr))(size)-1)))
#घोषणा _ALIGN_DOWN(addr, size)	((addr)&(~((typeof(addr))(size)-1)))

/* align addr on a size boundary - adjust address up अगर needed */
#घोषणा _ALIGN(addr,size)     _ALIGN_UP(addr,size)

/* to align the poपूर्णांकer to the (next) page boundary */
#घोषणा PAGE_ALIGN(addr)	_ALIGN(addr, PAGE_SIZE)

#पूर्ण_अगर				/* _PPC_BOOT_PAGE_H */
