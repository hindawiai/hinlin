<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-rpc/include/mach/hardware.h
 *
 *  Copyright (C) 1996-1999 Russell King.
 *
 *  This file contains the hardware definitions of the RiscPC series machines.
 */
#अगर_अघोषित __ASM_ARCH_HARDWARE_H
#घोषणा __ASM_ARCH_HARDWARE_H

#समावेश <mach/memory.h>

/*
 * What hardware must be present
 */
#घोषणा HAS_IOMD
#घोषणा HAS_VIDC20

/* Hardware addresses of major areas.
 *  *_START is the physical address
 *  *_SIZE  is the size of the region
 *  *_BASE  is the भव address
 */
#घोषणा RPC_RAM_SIZE		0x10000000
#घोषणा RPC_RAM_START		0x10000000

#घोषणा EASI_SIZE		0x08000000	/* EASI I/O */
#घोषणा EASI_START		0x08000000
#घोषणा EASI_BASE		IOMEM(0xe5000000)

#घोषणा IO_START		0x03000000	/* I/O */
#घोषणा IO_SIZE			0x01000000
#घोषणा IO_BASE			IOMEM(0xe0000000)

#घोषणा SCREEN_START		0x02000000	/* VRAM */
#घोषणा SCREEN_END		0xdfc00000
#घोषणा SCREEN_BASE		0xdf800000

#घोषणा UNCACHEABLE_ADDR	(FLUSH_BASE + 0x10000)

/*
 * IO Addresses
 */
#घोषणा ECARD_EASI_BASE		(EASI_BASE)
#घोषणा VIDC_BASE		(IO_BASE + 0x00400000)
#घोषणा EXPMASK_BASE		(IO_BASE + 0x00360000)
#घोषणा ECARD_IOC4_BASE		(IO_BASE + 0x00270000)
#घोषणा ECARD_IOC_BASE		(IO_BASE + 0x00240000)
#घोषणा IOMD_BASE		(IO_BASE + 0x00200000)
#घोषणा IOC_BASE		(IO_BASE + 0x00200000)
#घोषणा ECARD_MEMC8_BASE	(IO_BASE + 0x0002b000)
#घोषणा FLOPPYDMA_BASE		(IO_BASE + 0x0002a000)
#घोषणा PCIO_BASE		(IO_BASE + 0x00010000)
#घोषणा ECARD_MEMC_BASE		(IO_BASE + 0x00000000)

#घोषणा vidc_ग_लिखोl(val)	__raw_ग_लिखोl(val, VIDC_BASE)

#घोषणा NETSLOT_BASE		0x0302b000
#घोषणा NETSLOT_SIZE		0x00001000

#घोषणा PODSLOT_IOC0_BASE	0x03240000
#घोषणा PODSLOT_IOC4_BASE	0x03270000
#घोषणा PODSLOT_IOC_SIZE	(1 << 14)
#घोषणा PODSLOT_MEMC_BASE	0x03000000
#घोषणा PODSLOT_MEMC_SIZE	(1 << 14)
#घोषणा PODSLOT_EASI_BASE	0x08000000
#घोषणा PODSLOT_EASI_SIZE	(1 << 24)

#घोषणा	EXPMASK_STATUS		(EXPMASK_BASE + 0x00)
#घोषणा EXPMASK_ENABLE		(EXPMASK_BASE + 0x04)

#पूर्ण_अगर
