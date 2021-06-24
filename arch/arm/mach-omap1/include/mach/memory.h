<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-omap1/include/mach/memory.h
 */

#अगर_अघोषित __ASM_ARCH_MEMORY_H
#घोषणा __ASM_ARCH_MEMORY_H

/* REVISIT: omap1 legacy drivers still rely on this */
#समावेश <mach/soc.h>

/*
 * Bus address is physical address, except क्रम OMAP-1510 Local Bus.
 * OMAP-1510 bus address is translated पूर्णांकo a Local Bus address अगर the
 * OMAP bus type is lbus. We करो the address translation based on the
 * device overriding the शेषs used in the dma-mapping API.
 */

/*
 * OMAP-1510 Local Bus address offset
 */
#घोषणा OMAP1510_LB_OFFSET	UL(0x30000000)

#पूर्ण_अगर
