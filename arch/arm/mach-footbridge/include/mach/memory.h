<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-footbridge/include/mach/memory.h
 *
 *  Copyright (C) 1996-1999 Russell King.
 *
 *  Changelog:
 *   20-Oct-1996 RMK	Created
 *   31-Dec-1997 RMK	Fixed definitions to reduce warnings.
 *   17-May-1998 DAG	Added __virt_to_bus and __bus_to_virt functions.
 *   21-Nov-1998 RMK	Changed __virt_to_bus and __bus_to_virt to macros.
 *   21-Mar-1999 RMK	Added PAGE_OFFSET क्रम co285 architecture.
 *			Renamed to memory.h
 *			Moved PAGE_OFFSET and TASK_SIZE here
 */
#अगर_अघोषित __ASM_ARCH_MEMORY_H
#घोषणा __ASM_ARCH_MEMORY_H


#अगर defined(CONFIG_FOOTBRIDGE_ADDIN)
/*
 * If we may be using add-in footbridge mode, then we must
 * use the out-of-line translation that makes use of the
 * PCI BAR
 */
#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित दीर्घ __virt_to_bus(अचिन्हित दीर्घ);
बाह्य अचिन्हित दीर्घ __bus_to_virt(अचिन्हित दीर्घ);
बाह्य अचिन्हित दीर्घ __pfn_to_bus(अचिन्हित दीर्घ);
बाह्य अचिन्हित दीर्घ __bus_to_pfn(अचिन्हित दीर्घ);
#पूर्ण_अगर
#घोषणा __virt_to_bus	__virt_to_bus
#घोषणा __bus_to_virt	__bus_to_virt

#या_अगर defined(CONFIG_FOOTBRIDGE_HOST)

/*
 * The footbridge is programmed to expose the प्रणाली RAM at 0xe0000000.
 * The requirement is that the RAM isn't placed at bus address 0, which
 * would clash with VGA cards.
 */
#घोषणा BUS_OFFSET		0xe0000000
#घोषणा __virt_to_bus(x)	((x) + (BUS_OFFSET - PAGE_OFFSET))
#घोषणा __bus_to_virt(x)	((x) - (BUS_OFFSET - PAGE_OFFSET))
#घोषणा __pfn_to_bus(x)		(__pfn_to_phys(x) + (BUS_OFFSET - PHYS_OFFSET))
#घोषणा __bus_to_pfn(x)		__phys_to_pfn((x) - (BUS_OFFSET - PHYS_OFFSET))

#अन्यथा

#त्रुटि "Undefined footbridge mode"

#पूर्ण_अगर

/*
 * Cache flushing area.
 */
#घोषणा FLUSH_BASE		0xf9000000

#घोषणा FLUSH_BASE_PHYS		0x50000000

#पूर्ण_अगर
