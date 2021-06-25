<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम V3 Semiconductor PCI Local Bus to PCI Bridge
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 *
 * Based on the code from arch/arm/mach-पूर्णांकegrator/pci_v3.c
 * Copyright (C) 1999 ARM Limited
 * Copyright (C) 2000-2001 Deep Blue Solutions Ltd
 *
 * Contributors to the old driver include:
 * Russell King <linux@armlinux.org.uk>
 * David A. Rusling <david.rusling@linaro.org> (uHAL, ARM Firmware suite)
 * Rob Herring <robh@kernel.org>
 * Liviu Dudau <Liviu.Dudau@arm.com>
 * Grant Likely <grant.likely@secretlab.ca>
 * Arnd Bergmann <arnd@arndb.de>
 * Bjorn Helgaas <bhelgaas@google.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>

#समावेश "../pci.h"

#घोषणा V3_PCI_VENDOR			0x00000000
#घोषणा V3_PCI_DEVICE			0x00000002
#घोषणा V3_PCI_CMD			0x00000004
#घोषणा V3_PCI_STAT			0x00000006
#घोषणा V3_PCI_CC_REV			0x00000008
#घोषणा V3_PCI_HDR_CFG			0x0000000C
#घोषणा V3_PCI_IO_BASE			0x00000010
#घोषणा V3_PCI_BASE0			0x00000014
#घोषणा V3_PCI_BASE1			0x00000018
#घोषणा V3_PCI_SUB_VENDOR		0x0000002C
#घोषणा V3_PCI_SUB_ID			0x0000002E
#घोषणा V3_PCI_ROM			0x00000030
#घोषणा V3_PCI_BPARAM			0x0000003C
#घोषणा V3_PCI_MAP0			0x00000040
#घोषणा V3_PCI_MAP1			0x00000044
#घोषणा V3_PCI_INT_STAT			0x00000048
#घोषणा V3_PCI_INT_CFG			0x0000004C
#घोषणा V3_LB_BASE0			0x00000054
#घोषणा V3_LB_BASE1			0x00000058
#घोषणा V3_LB_MAP0			0x0000005E
#घोषणा V3_LB_MAP1			0x00000062
#घोषणा V3_LB_BASE2			0x00000064
#घोषणा V3_LB_MAP2			0x00000066
#घोषणा V3_LB_SIZE			0x00000068
#घोषणा V3_LB_IO_BASE			0x0000006E
#घोषणा V3_FIFO_CFG			0x00000070
#घोषणा V3_FIFO_PRIORITY		0x00000072
#घोषणा V3_FIFO_STAT			0x00000074
#घोषणा V3_LB_ISTAT			0x00000076
#घोषणा V3_LB_IMASK			0x00000077
#घोषणा V3_SYSTEM			0x00000078
#घोषणा V3_LB_CFG			0x0000007A
#घोषणा V3_PCI_CFG			0x0000007C
#घोषणा V3_DMA_PCI_ADR0			0x00000080
#घोषणा V3_DMA_PCI_ADR1			0x00000090
#घोषणा V3_DMA_LOCAL_ADR0		0x00000084
#घोषणा V3_DMA_LOCAL_ADR1		0x00000094
#घोषणा V3_DMA_LENGTH0			0x00000088
#घोषणा V3_DMA_LENGTH1			0x00000098
#घोषणा V3_DMA_CSR0			0x0000008B
#घोषणा V3_DMA_CSR1			0x0000009B
#घोषणा V3_DMA_CTLB_ADR0		0x0000008C
#घोषणा V3_DMA_CTLB_ADR1		0x0000009C
#घोषणा V3_DMA_DELAY			0x000000E0
#घोषणा V3_MAIL_DATA			0x000000C0
#घोषणा V3_PCI_MAIL_IEWR		0x000000D0
#घोषणा V3_PCI_MAIL_IERD		0x000000D2
#घोषणा V3_LB_MAIL_IEWR			0x000000D4
#घोषणा V3_LB_MAIL_IERD			0x000000D6
#घोषणा V3_MAIL_WR_STAT			0x000000D8
#घोषणा V3_MAIL_RD_STAT			0x000000DA
#घोषणा V3_QBA_MAP			0x000000DC

/* PCI STATUS bits */
#घोषणा V3_PCI_STAT_PAR_ERR		BIT(15)
#घोषणा V3_PCI_STAT_SYS_ERR		BIT(14)
#घोषणा V3_PCI_STAT_M_ABORT_ERR		BIT(13)
#घोषणा V3_PCI_STAT_T_ABORT_ERR		BIT(12)

/* LB ISTAT bits */
#घोषणा V3_LB_ISTAT_MAILBOX		BIT(7)
#घोषणा V3_LB_ISTAT_PCI_RD		BIT(6)
#घोषणा V3_LB_ISTAT_PCI_WR		BIT(5)
#घोषणा V3_LB_ISTAT_PCI_INT		BIT(4)
#घोषणा V3_LB_ISTAT_PCI_PERR		BIT(3)
#घोषणा V3_LB_ISTAT_I2O_QWR		BIT(2)
#घोषणा V3_LB_ISTAT_DMA1		BIT(1)
#घोषणा V3_LB_ISTAT_DMA0		BIT(0)

/* PCI COMMAND bits */
#घोषणा V3_COMMAND_M_FBB_EN		BIT(9)
#घोषणा V3_COMMAND_M_SERR_EN		BIT(8)
#घोषणा V3_COMMAND_M_PAR_EN		BIT(6)
#घोषणा V3_COMMAND_M_MASTER_EN		BIT(2)
#घोषणा V3_COMMAND_M_MEM_EN		BIT(1)
#घोषणा V3_COMMAND_M_IO_EN		BIT(0)

/* SYSTEM bits */
#घोषणा V3_SYSTEM_M_RST_OUT		BIT(15)
#घोषणा V3_SYSTEM_M_LOCK		BIT(14)
#घोषणा V3_SYSTEM_UNLOCK		0xa05f

/* PCI CFG bits */
#घोषणा V3_PCI_CFG_M_I2O_EN		BIT(15)
#घोषणा V3_PCI_CFG_M_IO_REG_DIS		BIT(14)
#घोषणा V3_PCI_CFG_M_IO_DIS		BIT(13)
#घोषणा V3_PCI_CFG_M_EN3V		BIT(12)
#घोषणा V3_PCI_CFG_M_RETRY_EN		BIT(10)
#घोषणा V3_PCI_CFG_M_AD_LOW1		BIT(9)
#घोषणा V3_PCI_CFG_M_AD_LOW0		BIT(8)
/*
 * This is the value applied to C/BE[3:1], with bit 0 always held 0
 * during DMA access.
 */
#घोषणा V3_PCI_CFG_M_RTYPE_SHIFT	5
#घोषणा V3_PCI_CFG_M_WTYPE_SHIFT	1
#घोषणा V3_PCI_CFG_TYPE_DEFAULT		0x3

/* PCI BASE bits (PCI -> Local Bus) */
#घोषणा V3_PCI_BASE_M_ADR_BASE		0xFFF00000U
#घोषणा V3_PCI_BASE_M_ADR_BASEL		0x000FFF00U
#घोषणा V3_PCI_BASE_M_PREFETCH		BIT(3)
#घोषणा V3_PCI_BASE_M_TYPE		(3 << 1)
#घोषणा V3_PCI_BASE_M_IO		BIT(0)

/* PCI MAP bits (PCI -> Local bus) */
#घोषणा V3_PCI_MAP_M_MAP_ADR		0xFFF00000U
#घोषणा V3_PCI_MAP_M_RD_POST_INH	BIT(15)
#घोषणा V3_PCI_MAP_M_ROM_SIZE		(3 << 10)
#घोषणा V3_PCI_MAP_M_SWAP		(3 << 8)
#घोषणा V3_PCI_MAP_M_ADR_SIZE		0x000000F0U
#घोषणा V3_PCI_MAP_M_REG_EN		BIT(1)
#घोषणा V3_PCI_MAP_M_ENABLE		BIT(0)

/* LB_BASE0,1 bits (Local bus -> PCI) */
#घोषणा V3_LB_BASE_ADR_BASE		0xfff00000U
#घोषणा V3_LB_BASE_SWAP			(3 << 8)
#घोषणा V3_LB_BASE_ADR_SIZE		(15 << 4)
#घोषणा V3_LB_BASE_PREFETCH		BIT(3)
#घोषणा V3_LB_BASE_ENABLE		BIT(0)

#घोषणा V3_LB_BASE_ADR_SIZE_1MB		(0 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_2MB		(1 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_4MB		(2 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_8MB		(3 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_16MB	(4 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_32MB	(5 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_64MB	(6 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_128MB	(7 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_256MB	(8 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_512MB	(9 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_1GB		(10 << 4)
#घोषणा V3_LB_BASE_ADR_SIZE_2GB		(11 << 4)

#घोषणा v3_addr_to_lb_base(a)	((a) & V3_LB_BASE_ADR_BASE)

/* LB_MAP0,1 bits (Local bus -> PCI) */
#घोषणा V3_LB_MAP_MAP_ADR		0xfff0U
#घोषणा V3_LB_MAP_TYPE			(7 << 1)
#घोषणा V3_LB_MAP_AD_LOW_EN		BIT(0)

#घोषणा V3_LB_MAP_TYPE_IACK		(0 << 1)
#घोषणा V3_LB_MAP_TYPE_IO		(1 << 1)
#घोषणा V3_LB_MAP_TYPE_MEM		(3 << 1)
#घोषणा V3_LB_MAP_TYPE_CONFIG		(5 << 1)
#घोषणा V3_LB_MAP_TYPE_MEM_MULTIPLE	(6 << 1)

#घोषणा v3_addr_to_lb_map(a)	(((a) >> 16) & V3_LB_MAP_MAP_ADR)

/* LB_BASE2 bits (Local bus -> PCI IO) */
#घोषणा V3_LB_BASE2_ADR_BASE		0xff00U
#घोषणा V3_LB_BASE2_SWAP_AUTO		(3 << 6)
#घोषणा V3_LB_BASE2_ENABLE		BIT(0)

#घोषणा v3_addr_to_lb_base2(a)	(((a) >> 16) & V3_LB_BASE2_ADR_BASE)

/* LB_MAP2 bits (Local bus -> PCI IO) */
#घोषणा V3_LB_MAP2_MAP_ADR		0xff00U

#घोषणा v3_addr_to_lb_map2(a)	(((a) >> 16) & V3_LB_MAP2_MAP_ADR)

/* FIFO priority bits */
#घोषणा V3_FIFO_PRIO_LOCAL		BIT(12)
#घोषणा V3_FIFO_PRIO_LB_RD1_FLUSH_EOB	BIT(10)
#घोषणा V3_FIFO_PRIO_LB_RD1_FLUSH_AP1	BIT(11)
#घोषणा V3_FIFO_PRIO_LB_RD1_FLUSH_ANY	(BIT(10)|BIT(11))
#घोषणा V3_FIFO_PRIO_LB_RD0_FLUSH_EOB	BIT(8)
#घोषणा V3_FIFO_PRIO_LB_RD0_FLUSH_AP1	BIT(9)
#घोषणा V3_FIFO_PRIO_LB_RD0_FLUSH_ANY	(BIT(8)|BIT(9))
#घोषणा V3_FIFO_PRIO_PCI		BIT(4)
#घोषणा V3_FIFO_PRIO_PCI_RD1_FLUSH_EOB	BIT(2)
#घोषणा V3_FIFO_PRIO_PCI_RD1_FLUSH_AP1	BIT(3)
#घोषणा V3_FIFO_PRIO_PCI_RD1_FLUSH_ANY	(BIT(2)|BIT(3))
#घोषणा V3_FIFO_PRIO_PCI_RD0_FLUSH_EOB	BIT(0)
#घोषणा V3_FIFO_PRIO_PCI_RD0_FLUSH_AP1	BIT(1)
#घोषणा V3_FIFO_PRIO_PCI_RD0_FLUSH_ANY	(BIT(0)|BIT(1))

/* Local bus configuration bits */
#घोषणा V3_LB_CFG_LB_TO_64_CYCLES	0x0000
#घोषणा V3_LB_CFG_LB_TO_256_CYCLES	BIT(13)
#घोषणा V3_LB_CFG_LB_TO_512_CYCLES	BIT(14)
#घोषणा V3_LB_CFG_LB_TO_1024_CYCLES	(BIT(13)|BIT(14))
#घोषणा V3_LB_CFG_LB_RST		BIT(12)
#घोषणा V3_LB_CFG_LB_PPC_RDY		BIT(11)
#घोषणा V3_LB_CFG_LB_LB_INT		BIT(10)
#घोषणा V3_LB_CFG_LB_ERR_EN		BIT(9)
#घोषणा V3_LB_CFG_LB_RDY_EN		BIT(8)
#घोषणा V3_LB_CFG_LB_BE_IMODE		BIT(7)
#घोषणा V3_LB_CFG_LB_BE_OMODE		BIT(6)
#घोषणा V3_LB_CFG_LB_ENDIAN		BIT(5)
#घोषणा V3_LB_CFG_LB_PARK_EN		BIT(4)
#घोषणा V3_LB_CFG_LB_FBB_DIS		BIT(2)

/* ARM Integrator-specअगरic extended control रेजिस्टरs */
#घोषणा INTEGRATOR_SC_PCI_OFFSET	0x18
#घोषणा INTEGRATOR_SC_PCI_ENABLE	BIT(0)
#घोषणा INTEGRATOR_SC_PCI_INTCLR	BIT(1)
#घोषणा INTEGRATOR_SC_LBFADDR_OFFSET	0x20
#घोषणा INTEGRATOR_SC_LBFCODE_OFFSET	0x24

काष्ठा v3_pci अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	व्योम __iomem *config_base;
	u32 config_mem;
	u32 non_pre_mem;
	u32 pre_mem;
	phys_addr_t non_pre_bus_addr;
	phys_addr_t pre_bus_addr;
	काष्ठा regmap *map;
पूर्ण;

/*
 * The V3 PCI पूर्णांकerface chip in Integrator provides several winकरोws from
 * local bus memory पूर्णांकo the PCI memory areas. Unक्रमtunately, there
 * are not really enough winकरोws क्रम our usage, thereक्रमe we reuse
 * one of the winकरोws क्रम access to PCI configuration space. On the
 * Integrator/AP, the memory map is as follows:
 *
 * Local Bus Memory         Usage
 *
 * 40000000 - 4FFFFFFF      PCI memory.  256M non-prefetchable
 * 50000000 - 5FFFFFFF      PCI memory.  256M prefetchable
 * 60000000 - 60FFFFFF      PCI IO.  16M
 * 61000000 - 61FFFFFF      PCI Configuration. 16M
 *
 * There are three V3 winकरोws, each described by a pair of V3 रेजिस्टरs.
 * These are LB_BASE0/LB_MAP0, LB_BASE1/LB_MAP1 and LB_BASE2/LB_MAP2.
 * Base0 and Base1 can be used क्रम any type of PCI memory access.   Base2
 * can be used either क्रम PCI I/O or क्रम I20 accesses.  By शेष, uHAL
 * uses this only क्रम PCI IO space.
 *
 * Normally these spaces are mapped using the following base रेजिस्टरs:
 *
 * Usage Local Bus Memory         Base/Map रेजिस्टरs used
 *
 * Mem   40000000 - 4FFFFFFF      LB_BASE0/LB_MAP0
 * Mem   50000000 - 5FFFFFFF      LB_BASE1/LB_MAP1
 * IO    60000000 - 60FFFFFF      LB_BASE2/LB_MAP2
 * Cfg   61000000 - 61FFFFFF
 *
 * This means that I20 and PCI configuration space accesses will fail.
 * When PCI configuration accesses are needed (via the uHAL PCI
 * configuration space primitives) we must remap the spaces as follows:
 *
 * Usage Local Bus Memory         Base/Map रेजिस्टरs used
 *
 * Mem   40000000 - 4FFFFFFF      LB_BASE0/LB_MAP0
 * Mem   50000000 - 5FFFFFFF      LB_BASE0/LB_MAP0
 * IO    60000000 - 60FFFFFF      LB_BASE2/LB_MAP2
 * Cfg   61000000 - 61FFFFFF      LB_BASE1/LB_MAP1
 *
 * To make this work, the code depends on overlapping winकरोws working.
 * The V3 chip translates an address by checking its range within
 * each of the BASE/MAP pairs in turn (in ascending रेजिस्टर number
 * order).  It will use the first matching pair.   So, क्रम example,
 * अगर the same address is mapped by both LB_BASE0/LB_MAP0 and
 * LB_BASE1/LB_MAP1, the V3 will use the translation from
 * LB_BASE0/LB_MAP0.
 *
 * To allow PCI Configuration space access, the code enlarges the
 * winकरोw mapped by LB_BASE0/LB_MAP0 from 256M to 512M.  This occludes
 * the winकरोws currently mapped by LB_BASE1/LB_MAP1 so that it can
 * be remapped क्रम use by configuration cycles.
 *
 * At the end of the PCI Configuration space accesses,
 * LB_BASE1/LB_MAP1 is reset to map PCI Memory.  Finally the winकरोw
 * mapped by LB_BASE0/LB_MAP0 is reduced in size from 512M to 256M to
 * reveal the now restored LB_BASE1/LB_MAP1 winकरोw.
 *
 * NOTE: We करो not set up I2O mapping.  I suspect that this is only
 * क्रम an पूर्णांकelligent (target) device.  Using I2O disables most of
 * the mappings पूर्णांकo PCI memory.
 */
अटल व्योम __iomem *v3_map_bus(काष्ठा pci_bus *bus,
				अचिन्हित पूर्णांक devfn, पूर्णांक offset)
अणु
	काष्ठा v3_pci *v3 = bus->sysdata;
	अचिन्हित पूर्णांक address, mapaddress, busnr;

	busnr = bus->number;
	अगर (busnr == 0) अणु
		पूर्णांक slot = PCI_SLOT(devfn);

		/*
		 * local bus segment so need a type 0 config cycle
		 *
		 * build the PCI configuration "address" with one-hot in
		 * A31-A11
		 *
		 * mapaddress:
		 *  3:1 = config cycle (101)
		 *  0   = PCI A1 & A0 are 0 (0)
		 */
		address = PCI_FUNC(devfn) << 8;
		mapaddress = V3_LB_MAP_TYPE_CONFIG;

		अगर (slot > 12)
			/*
			 * high order bits are handled by the MAP रेजिस्टर
			 */
			mapaddress |= BIT(slot - 5);
		अन्यथा
			/*
			 * low order bits handled directly in the address
			 */
			address |= BIT(slot + 11);
	पूर्ण अन्यथा अणु
		/*
		 * not the local bus segment so need a type 1 config cycle
		 *
		 * address:
		 *  23:16 = bus number
		 *  15:11 = slot number (7:3 of devfn)
		 *  10:8  = func number (2:0 of devfn)
		 *
		 * mapaddress:
		 *  3:1 = config cycle (101)
		 *  0   = PCI A1 & A0 from host bus (1)
		 */
		mapaddress = V3_LB_MAP_TYPE_CONFIG | V3_LB_MAP_AD_LOW_EN;
		address = (busnr << 16) | (devfn << 8);
	पूर्ण

	/*
	 * Set up base0 to see all 512Mbytes of memory space (not
	 * prefetchable), this मुक्तs up base1 क्रम re-use by
	 * configuration memory
	 */
	ग_लिखोl(v3_addr_to_lb_base(v3->non_pre_mem) |
	       V3_LB_BASE_ADR_SIZE_512MB | V3_LB_BASE_ENABLE,
	       v3->base + V3_LB_BASE0);

	/*
	 * Set up base1/map1 to poपूर्णांक पूर्णांकo configuration space.
	 * The config mem is always 16MB.
	 */
	ग_लिखोl(v3_addr_to_lb_base(v3->config_mem) |
	       V3_LB_BASE_ADR_SIZE_16MB | V3_LB_BASE_ENABLE,
	       v3->base + V3_LB_BASE1);
	ग_लिखोw(mapaddress, v3->base + V3_LB_MAP1);

	वापस v3->config_base + address + offset;
पूर्ण

अटल व्योम v3_unmap_bus(काष्ठा v3_pci *v3)
अणु
	/*
	 * Reassign base1 क्रम use by prefetchable PCI memory
	 */
	ग_लिखोl(v3_addr_to_lb_base(v3->pre_mem) |
	       V3_LB_BASE_ADR_SIZE_256MB | V3_LB_BASE_PREFETCH |
	       V3_LB_BASE_ENABLE,
	       v3->base + V3_LB_BASE1);
	ग_लिखोw(v3_addr_to_lb_map(v3->pre_bus_addr) |
	       V3_LB_MAP_TYPE_MEM, /* was V3_LB_MAP_TYPE_MEM_MULTIPLE */
	       v3->base + V3_LB_MAP1);

	/*
	 * And shrink base0 back to a 256M winकरोw (NOTE: MAP0 alपढ़ोy correct)
	 */
	ग_लिखोl(v3_addr_to_lb_base(v3->non_pre_mem) |
	       V3_LB_BASE_ADR_SIZE_256MB | V3_LB_BASE_ENABLE,
	       v3->base + V3_LB_BASE0);
पूर्ण

अटल पूर्णांक v3_pci_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक fn,
			      पूर्णांक config, पूर्णांक size, u32 *value)
अणु
	काष्ठा v3_pci *v3 = bus->sysdata;
	पूर्णांक ret;

	dev_dbg(&bus->dev,
		"[read]  slt: %.2d, fnc: %d, cnf: 0x%.2X, val (%d bytes): 0x%.8X\n",
		PCI_SLOT(fn), PCI_FUNC(fn), config, size, *value);
	ret = pci_generic_config_पढ़ो(bus, fn, config, size, value);
	v3_unmap_bus(v3);
	वापस ret;
पूर्ण

अटल पूर्णांक v3_pci_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक fn,
				    पूर्णांक config, पूर्णांक size, u32 value)
अणु
	काष्ठा v3_pci *v3 = bus->sysdata;
	पूर्णांक ret;

	dev_dbg(&bus->dev,
		"[write] slt: %.2d, fnc: %d, cnf: 0x%.2X, val (%d bytes): 0x%.8X\n",
		PCI_SLOT(fn), PCI_FUNC(fn), config, size, value);
	ret = pci_generic_config_ग_लिखो(bus, fn, config, size, value);
	v3_unmap_bus(v3);
	वापस ret;
पूर्ण

अटल काष्ठा pci_ops v3_pci_ops = अणु
	.map_bus = v3_map_bus,
	.पढ़ो = v3_pci_पढ़ो_config,
	.ग_लिखो = v3_pci_ग_लिखो_config,
पूर्ण;

अटल irqवापस_t v3_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा v3_pci *v3 = data;
	काष्ठा device *dev = v3->dev;
	u32 status;

	status = पढ़ोw(v3->base + V3_PCI_STAT);
	अगर (status & V3_PCI_STAT_PAR_ERR)
		dev_err(dev, "parity error interrupt\n");
	अगर (status & V3_PCI_STAT_SYS_ERR)
		dev_err(dev, "system error interrupt\n");
	अगर (status & V3_PCI_STAT_M_ABORT_ERR)
		dev_err(dev, "master abort error interrupt\n");
	अगर (status & V3_PCI_STAT_T_ABORT_ERR)
		dev_err(dev, "target abort error interrupt\n");
	ग_लिखोw(status, v3->base + V3_PCI_STAT);

	status = पढ़ोb(v3->base + V3_LB_ISTAT);
	अगर (status & V3_LB_ISTAT_MAILBOX)
		dev_info(dev, "PCI mailbox interrupt\n");
	अगर (status & V3_LB_ISTAT_PCI_RD)
		dev_err(dev, "PCI target LB->PCI READ abort interrupt\n");
	अगर (status & V3_LB_ISTAT_PCI_WR)
		dev_err(dev, "PCI target LB->PCI WRITE abort interrupt\n");
	अगर (status &  V3_LB_ISTAT_PCI_INT)
		dev_info(dev, "PCI pin interrupt\n");
	अगर (status & V3_LB_ISTAT_PCI_PERR)
		dev_err(dev, "PCI parity error interrupt\n");
	अगर (status & V3_LB_ISTAT_I2O_QWR)
		dev_info(dev, "I2O inbound post queue interrupt\n");
	अगर (status & V3_LB_ISTAT_DMA1)
		dev_info(dev, "DMA channel 1 interrupt\n");
	अगर (status & V3_LB_ISTAT_DMA0)
		dev_info(dev, "DMA channel 0 interrupt\n");
	/* Clear all possible पूर्णांकerrupts on the local bus */
	ग_लिखोb(0, v3->base + V3_LB_ISTAT);
	अगर (v3->map)
		regmap_ग_लिखो(v3->map, INTEGRATOR_SC_PCI_OFFSET,
			     INTEGRATOR_SC_PCI_ENABLE |
			     INTEGRATOR_SC_PCI_INTCLR);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक v3_पूर्णांकegrator_init(काष्ठा v3_pci *v3)
अणु
	अचिन्हित पूर्णांक val;

	v3->map =
		syscon_regmap_lookup_by_compatible("arm,integrator-ap-syscon");
	अगर (IS_ERR(v3->map)) अणु
		dev_err(v3->dev, "no syscon\n");
		वापस -ENODEV;
	पूर्ण

	regmap_पढ़ो(v3->map, INTEGRATOR_SC_PCI_OFFSET, &val);
	/* Take the PCI bridge out of reset, clear IRQs */
	regmap_ग_लिखो(v3->map, INTEGRATOR_SC_PCI_OFFSET,
		     INTEGRATOR_SC_PCI_ENABLE |
		     INTEGRATOR_SC_PCI_INTCLR);

	अगर (!(val & INTEGRATOR_SC_PCI_ENABLE)) अणु
		/* If we were in reset we need to sleep a bit */
		msleep(230);

		/* Set the physical base क्रम the controller itself */
		ग_लिखोl(0x6200, v3->base + V3_LB_IO_BASE);

		/* Wait क्रम the mailbox to settle after reset */
		करो अणु
			ग_लिखोb(0xaa, v3->base + V3_MAIL_DATA);
			ग_लिखोb(0x55, v3->base + V3_MAIL_DATA + 4);
		पूर्ण जबतक (पढ़ोb(v3->base + V3_MAIL_DATA) != 0xaa &&
			 पढ़ोb(v3->base + V3_MAIL_DATA) != 0x55);
	पूर्ण

	dev_info(v3->dev, "initialized PCI V3 Integrator/AP integration\n");

	वापस 0;
पूर्ण

अटल पूर्णांक v3_pci_setup_resource(काष्ठा v3_pci *v3,
				 काष्ठा pci_host_bridge *host,
				 काष्ठा resource_entry *win)
अणु
	काष्ठा device *dev = v3->dev;
	काष्ठा resource *mem;
	काष्ठा resource *io;

	चयन (resource_type(win->res)) अणु
	हाल IORESOURCE_IO:
		io = win->res;

		/* Setup winकरोw 2 - PCI I/O */
		ग_लिखोl(v3_addr_to_lb_base2(pci_pio_to_address(io->start)) |
		       V3_LB_BASE2_ENABLE,
		       v3->base + V3_LB_BASE2);
		ग_लिखोw(v3_addr_to_lb_map2(io->start - win->offset),
		       v3->base + V3_LB_MAP2);
		अवरोध;
	हाल IORESOURCE_MEM:
		mem = win->res;
		अगर (mem->flags & IORESOURCE_PREFETCH) अणु
			mem->name = "V3 PCI PRE-MEM";
			v3->pre_mem = mem->start;
			v3->pre_bus_addr = mem->start - win->offset;
			dev_dbg(dev, "PREFETCHABLE MEM window %pR, bus addr %pap\n",
				mem, &v3->pre_bus_addr);
			अगर (resource_size(mem) != SZ_256M) अणु
				dev_err(dev, "prefetchable memory range is not 256MB\n");
				वापस -EINVAL;
			पूर्ण
			अगर (v3->non_pre_mem &&
			    (mem->start != v3->non_pre_mem + SZ_256M)) अणु
				dev_err(dev,
					"prefetchable memory is not adjacent to non-prefetchable memory\n");
				वापस -EINVAL;
			पूर्ण
			/* Setup winकरोw 1 - PCI prefetchable memory */
			ग_लिखोl(v3_addr_to_lb_base(v3->pre_mem) |
			       V3_LB_BASE_ADR_SIZE_256MB |
			       V3_LB_BASE_PREFETCH |
			       V3_LB_BASE_ENABLE,
			       v3->base + V3_LB_BASE1);
			ग_लिखोw(v3_addr_to_lb_map(v3->pre_bus_addr) |
			       V3_LB_MAP_TYPE_MEM, /* Was V3_LB_MAP_TYPE_MEM_MULTIPLE */
			       v3->base + V3_LB_MAP1);
		पूर्ण अन्यथा अणु
			mem->name = "V3 PCI NON-PRE-MEM";
			v3->non_pre_mem = mem->start;
			v3->non_pre_bus_addr = mem->start - win->offset;
			dev_dbg(dev, "NON-PREFETCHABLE MEM window %pR, bus addr %pap\n",
				mem, &v3->non_pre_bus_addr);
			अगर (resource_size(mem) != SZ_256M) अणु
				dev_err(dev,
					"non-prefetchable memory range is not 256MB\n");
				वापस -EINVAL;
			पूर्ण
			/* Setup winकरोw 0 - PCI non-prefetchable memory */
			ग_लिखोl(v3_addr_to_lb_base(v3->non_pre_mem) |
			       V3_LB_BASE_ADR_SIZE_256MB |
			       V3_LB_BASE_ENABLE,
			       v3->base + V3_LB_BASE0);
			ग_लिखोw(v3_addr_to_lb_map(v3->non_pre_bus_addr) |
			       V3_LB_MAP_TYPE_MEM,
			       v3->base + V3_LB_MAP0);
		पूर्ण
		अवरोध;
	हाल IORESOURCE_BUS:
		अवरोध;
	शेष:
		dev_info(dev, "Unknown resource type %lu\n",
			 resource_type(win->res));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक v3_get_dma_range_config(काष्ठा v3_pci *v3,
				   काष्ठा resource_entry *entry,
				   u32 *pci_base, u32 *pci_map)
अणु
	काष्ठा device *dev = v3->dev;
	u64 cpu_addr = entry->res->start;
	u64 cpu_end = entry->res->end;
	u64 pci_end = cpu_end - entry->offset;
	u64 pci_addr = entry->res->start - entry->offset;
	u32 val;

	अगर (pci_addr & ~V3_PCI_BASE_M_ADR_BASE) अणु
		dev_err(dev, "illegal range, only PCI bits 31..20 allowed\n");
		वापस -EINVAL;
	पूर्ण
	val = ((u32)pci_addr) & V3_PCI_BASE_M_ADR_BASE;
	*pci_base = val;

	अगर (cpu_addr & ~V3_PCI_MAP_M_MAP_ADR) अणु
		dev_err(dev, "illegal range, only CPU bits 31..20 allowed\n");
		वापस -EINVAL;
	पूर्ण
	val = ((u32)cpu_addr) & V3_PCI_MAP_M_MAP_ADR;

	चयन (resource_size(entry->res)) अणु
	हाल SZ_1M:
		val |= V3_LB_BASE_ADR_SIZE_1MB;
		अवरोध;
	हाल SZ_2M:
		val |= V3_LB_BASE_ADR_SIZE_2MB;
		अवरोध;
	हाल SZ_4M:
		val |= V3_LB_BASE_ADR_SIZE_4MB;
		अवरोध;
	हाल SZ_8M:
		val |= V3_LB_BASE_ADR_SIZE_8MB;
		अवरोध;
	हाल SZ_16M:
		val |= V3_LB_BASE_ADR_SIZE_16MB;
		अवरोध;
	हाल SZ_32M:
		val |= V3_LB_BASE_ADR_SIZE_32MB;
		अवरोध;
	हाल SZ_64M:
		val |= V3_LB_BASE_ADR_SIZE_64MB;
		अवरोध;
	हाल SZ_128M:
		val |= V3_LB_BASE_ADR_SIZE_128MB;
		अवरोध;
	हाल SZ_256M:
		val |= V3_LB_BASE_ADR_SIZE_256MB;
		अवरोध;
	हाल SZ_512M:
		val |= V3_LB_BASE_ADR_SIZE_512MB;
		अवरोध;
	हाल SZ_1G:
		val |= V3_LB_BASE_ADR_SIZE_1GB;
		अवरोध;
	हाल SZ_2G:
		val |= V3_LB_BASE_ADR_SIZE_2GB;
		अवरोध;
	शेष:
		dev_err(v3->dev, "illegal dma memory chunk size\n");
		वापस -EINVAL;
	पूर्ण
	val |= V3_PCI_MAP_M_REG_EN | V3_PCI_MAP_M_ENABLE;
	*pci_map = val;

	dev_dbg(dev,
		"DMA MEM CPU: 0x%016llx -> 0x%016llx => "
		"PCI: 0x%016llx -> 0x%016llx base %08x map %08x\n",
		cpu_addr, cpu_end,
		pci_addr, pci_end,
		*pci_base, *pci_map);

	वापस 0;
पूर्ण

अटल पूर्णांक v3_pci_parse_map_dma_ranges(काष्ठा v3_pci *v3,
				       काष्ठा device_node *np)
अणु
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(v3);
	काष्ठा device *dev = v3->dev;
	काष्ठा resource_entry *entry;
	पूर्णांक i = 0;

	resource_list_क्रम_each_entry(entry, &bridge->dma_ranges) अणु
		पूर्णांक ret;
		u32 pci_base, pci_map;

		ret = v3_get_dma_range_config(v3, entry, &pci_base, &pci_map);
		अगर (ret)
			वापस ret;

		अगर (i == 0) अणु
			ग_लिखोl(pci_base, v3->base + V3_PCI_BASE0);
			ग_लिखोl(pci_map, v3->base + V3_PCI_MAP0);
		पूर्ण अन्यथा अगर (i == 1) अणु
			ग_लिखोl(pci_base, v3->base + V3_PCI_BASE1);
			ग_लिखोl(pci_map, v3->base + V3_PCI_MAP1);
		पूर्ण अन्यथा अणु
			dev_err(dev, "too many ranges, only two supported\n");
			dev_err(dev, "range %d ignored\n", i);
		पूर्ण
		i++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक v3_pci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा resource *regs;
	काष्ठा resource_entry *win;
	काष्ठा v3_pci *v3;
	काष्ठा pci_host_bridge *host;
	काष्ठा clk *clk;
	u16 val;
	पूर्णांक irq;
	पूर्णांक ret;

	host = devm_pci_alloc_host_bridge(dev, माप(*v3));
	अगर (!host)
		वापस -ENOMEM;

	host->ops = &v3_pci_ops;
	v3 = pci_host_bridge_priv(host);
	host->sysdata = v3;
	v3->dev = dev;

	/* Get and enable host घड़ी */
	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "clock not found\n");
		वापस PTR_ERR(clk);
	पूर्ण
	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(dev, "unable to enable clock\n");
		वापस ret;
	पूर्ण

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	v3->base = devm_ioremap_resource(dev, regs);
	अगर (IS_ERR(v3->base))
		वापस PTR_ERR(v3->base);
	/*
	 * The hardware has a रेजिस्टर with the physical base address
	 * of the V3 controller itself, verअगरy that this is the same
	 * as the physical memory we've remapped it from.
	 */
	अगर (पढ़ोl(v3->base + V3_LB_IO_BASE) != (regs->start >> 16))
		dev_err(dev, "V3_LB_IO_BASE = %08x but device is @%pR\n",
			पढ़ोl(v3->base + V3_LB_IO_BASE), regs);

	/* Configuration space is 16MB directly mapped */
	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (resource_size(regs) != SZ_16M) अणु
		dev_err(dev, "config mem is not 16MB!\n");
		वापस -EINVAL;
	पूर्ण
	v3->config_mem = regs->start;
	v3->config_base = devm_ioremap_resource(dev, regs);
	अगर (IS_ERR(v3->config_base))
		वापस PTR_ERR(v3->config_base);

	/* Get and request error IRQ resource */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, v3_irq, 0,
			"PCIv3 error", v3);
	अगर (ret < 0) अणु
		dev_err(dev,
			"unable to request PCIv3 error IRQ %d (%d)\n",
			irq, ret);
		वापस ret;
	पूर्ण

	/*
	 * Unlock V3 रेजिस्टरs, but only अगर they were previously locked.
	 */
	अगर (पढ़ोw(v3->base + V3_SYSTEM) & V3_SYSTEM_M_LOCK)
		ग_लिखोw(V3_SYSTEM_UNLOCK, v3->base + V3_SYSTEM);

	/* Disable all slave access जबतक we set up the winकरोws */
	val = पढ़ोw(v3->base + V3_PCI_CMD);
	val &= ~(PCI_COMMAND_IO | PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	ग_लिखोw(val, v3->base + V3_PCI_CMD);

	/* Put the PCI bus पूर्णांकo reset */
	val = पढ़ोw(v3->base + V3_SYSTEM);
	val &= ~V3_SYSTEM_M_RST_OUT;
	ग_लिखोw(val, v3->base + V3_SYSTEM);

	/* Retry until we're पढ़ोy */
	val = पढ़ोw(v3->base + V3_PCI_CFG);
	val |= V3_PCI_CFG_M_RETRY_EN;
	ग_लिखोw(val, v3->base + V3_PCI_CFG);

	/* Set up the local bus protocol */
	val = पढ़ोw(v3->base + V3_LB_CFG);
	val |= V3_LB_CFG_LB_BE_IMODE; /* Byte enable input */
	val |= V3_LB_CFG_LB_BE_OMODE; /* Byte enable output */
	val &= ~V3_LB_CFG_LB_ENDIAN; /* Little endian */
	val &= ~V3_LB_CFG_LB_PPC_RDY; /* TODO: when using on PPC403Gx, set to 1 */
	ग_लिखोw(val, v3->base + V3_LB_CFG);

	/* Enable the PCI bus master */
	val = पढ़ोw(v3->base + V3_PCI_CMD);
	val |= PCI_COMMAND_MASTER;
	ग_लिखोw(val, v3->base + V3_PCI_CMD);

	/* Get the I/O and memory ranges from DT */
	resource_list_क्रम_each_entry(win, &host->winकरोws) अणु
		ret = v3_pci_setup_resource(v3, host, win);
		अगर (ret) अणु
			dev_err(dev, "error setting up resources\n");
			वापस ret;
		पूर्ण
	पूर्ण
	ret = v3_pci_parse_map_dma_ranges(v3, np);
	अगर (ret)
		वापस ret;

	/*
	 * Disable PCI to host IO cycles, enable I/O buffers @3.3V,
	 * set AD_LOW0 to 1 अगर one of the LB_MAP रेजिस्टरs choose
	 * to use this (should be unused).
	 */
	ग_लिखोl(0x00000000, v3->base + V3_PCI_IO_BASE);
	val = V3_PCI_CFG_M_IO_REG_DIS | V3_PCI_CFG_M_IO_DIS |
		V3_PCI_CFG_M_EN3V | V3_PCI_CFG_M_AD_LOW0;
	/*
	 * DMA पढ़ो and ग_लिखो from PCI bus commands types
	 */
	val |=  V3_PCI_CFG_TYPE_DEFAULT << V3_PCI_CFG_M_RTYPE_SHIFT;
	val |=  V3_PCI_CFG_TYPE_DEFAULT << V3_PCI_CFG_M_WTYPE_SHIFT;
	ग_लिखोw(val, v3->base + V3_PCI_CFG);

	/*
	 * Set the V3 FIFO such that ग_लिखोs have higher priority than
	 * पढ़ोs, and local bus ग_लिखो causes local bus पढ़ो fअगरo flush
	 * on aperture 1. Same क्रम PCI.
	 */
	ग_लिखोw(V3_FIFO_PRIO_LB_RD1_FLUSH_AP1 |
	       V3_FIFO_PRIO_LB_RD0_FLUSH_AP1 |
	       V3_FIFO_PRIO_PCI_RD1_FLUSH_AP1 |
	       V3_FIFO_PRIO_PCI_RD0_FLUSH_AP1,
	       v3->base + V3_FIFO_PRIORITY);


	/*
	 * Clear any error पूर्णांकerrupts, and enable parity and ग_लिखो error
	 * पूर्णांकerrupts
	 */
	ग_लिखोb(0, v3->base + V3_LB_ISTAT);
	val = पढ़ोw(v3->base + V3_LB_CFG);
	val |= V3_LB_CFG_LB_LB_INT;
	ग_लिखोw(val, v3->base + V3_LB_CFG);
	ग_लिखोb(V3_LB_ISTAT_PCI_WR | V3_LB_ISTAT_PCI_PERR,
	       v3->base + V3_LB_IMASK);

	/* Special Integrator initialization */
	अगर (of_device_is_compatible(np, "arm,integrator-ap-pci")) अणु
		ret = v3_पूर्णांकegrator_init(v3);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Post-init: enable PCI memory and invalidate (master alपढ़ोy on) */
	val = पढ़ोw(v3->base + V3_PCI_CMD);
	val |= PCI_COMMAND_MEMORY | PCI_COMMAND_INVALIDATE;
	ग_लिखोw(val, v3->base + V3_PCI_CMD);

	/* Clear pending पूर्णांकerrupts */
	ग_लिखोb(0, v3->base + V3_LB_ISTAT);
	/* Read or ग_लिखो errors and parity errors cause पूर्णांकerrupts */
	ग_लिखोb(V3_LB_ISTAT_PCI_RD | V3_LB_ISTAT_PCI_WR | V3_LB_ISTAT_PCI_PERR,
	       v3->base + V3_LB_IMASK);

	/* Take the PCI bus out of reset so devices can initialize */
	val = पढ़ोw(v3->base + V3_SYSTEM);
	val |= V3_SYSTEM_M_RST_OUT;
	ग_लिखोw(val, v3->base + V3_SYSTEM);

	/*
	 * Re-lock the प्रणाली रेजिस्टर.
	 */
	val = पढ़ोw(v3->base + V3_SYSTEM);
	val |= V3_SYSTEM_M_LOCK;
	ग_लिखोw(val, v3->base + V3_SYSTEM);

	वापस pci_host_probe(host);
पूर्ण

अटल स्थिर काष्ठा of_device_id v3_pci_of_match[] = अणु
	अणु
		.compatible = "v3,v360epc-pci",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver v3_pci_driver = अणु
	.driver = अणु
		.name = "pci-v3-semi",
		.of_match_table = of_match_ptr(v3_pci_of_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe  = v3_pci_probe,
पूर्ण;
builtin_platक्रमm_driver(v3_pci_driver);
