<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (C) 1999 by Kaz Kojima
 *
 * Defitions क्रम the address spaces of the SH CPUs.
 */
#अगर_अघोषित __ASM_SH_ADDRSPACE_H
#घोषणा __ASM_SH_ADDRSPACE_H

#समावेश <cpu/addrspace.h>

/* If this CPU supports segmentation, hook up the helpers */
#अगर_घोषित P1SEG

/*
   [ P0/U0 (भव) ]		0x00000000     <------ User space
   [ P1 (fixed)   cached ]	0x80000000     <------ Kernel space
   [ P2 (fixed)  non-cachable]	0xA0000000     <------ Physical access
   [ P3 (भव) cached]	0xC0000000     <------ vदो_स्मृतिed area
   [ P4 control   ]		0xE0000000
 */

/* Returns the privileged segment base of a given address  */
#घोषणा PXSEG(a)	(((अचिन्हित दीर्घ)(a)) & 0xe0000000)

#अगर_घोषित CONFIG_29BIT
/*
 * Map an address to a certain privileged segment
 */
#घोषणा P1SEGADDR(a)	\
	((__typeof__(a))(((अचिन्हित दीर्घ)(a) & 0x1fffffff) | P1SEG))
#घोषणा P2SEGADDR(a)	\
	((__typeof__(a))(((अचिन्हित दीर्घ)(a) & 0x1fffffff) | P2SEG))
#घोषणा P3SEGADDR(a)	\
	((__typeof__(a))(((अचिन्हित दीर्घ)(a) & 0x1fffffff) | P3SEG))
#घोषणा P4SEGADDR(a)	\
	((__typeof__(a))(((अचिन्हित दीर्घ)(a) & 0x1fffffff) | P4SEG))
#अन्यथा
/*
 * These will never work in 32-bit, करोn't even bother.
 */
#घोषणा P1SEGADDR(a)	(अणु (व्योम)(a); BUG(); शून्य; पूर्ण)
#घोषणा P2SEGADDR(a)	(अणु (व्योम)(a); BUG(); शून्य; पूर्ण)
#घोषणा P3SEGADDR(a)	(अणु (व्योम)(a); BUG(); शून्य; पूर्ण)
#घोषणा P4SEGADDR(a)	(अणु (व्योम)(a); BUG(); शून्य; पूर्ण)
#पूर्ण_अगर
#पूर्ण_अगर /* P1SEG */

/* Check अगर an address can be reached in 29 bits */
#घोषणा IS_29BIT(a)	(((अचिन्हित दीर्घ)(a)) < 0x20000000)

#अगर_घोषित CONFIG_SH_STORE_QUEUES
/*
 * This is a special हाल क्रम the SH-4 store queues, as pages क्रम this
 * space still need to be faulted in beक्रमe it's possible to flush the
 * store queue cache क्रम ग_लिखोout to the remapped region.
 */
#घोषणा P3_ADDR_MAX		(P4SEG_STORE_QUE + 0x04000000)
#अन्यथा
#घोषणा P3_ADDR_MAX		P4SEG
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_ADDRSPACE_H */
