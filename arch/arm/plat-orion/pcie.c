<शैली गुरु>
/*
 * arch/arm/plat-orion/pcie.c
 *
 * Marvell Orion SoC PCIe handling.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/mbus.h>
#समावेश <यंत्र/mach/pci.h>
#समावेश <plat/pcie.h>
#समावेश <plat/addr-map.h>
#समावेश <linux/delay.h>

/*
 * PCIe unit रेजिस्टर offsets.
 */
#घोषणा PCIE_DEV_ID_OFF		0x0000
#घोषणा PCIE_CMD_OFF		0x0004
#घोषणा PCIE_DEV_REV_OFF	0x0008
#घोषणा PCIE_BAR_LO_OFF(n)	(0x0010 + ((n) << 3))
#घोषणा PCIE_BAR_HI_OFF(n)	(0x0014 + ((n) << 3))
#घोषणा PCIE_HEADER_LOG_4_OFF	0x0128
#घोषणा PCIE_BAR_CTRL_OFF(n)	(0x1804 + ((n - 1) * 4))
#घोषणा PCIE_WIN04_CTRL_OFF(n)	(0x1820 + ((n) << 4))
#घोषणा PCIE_WIN04_BASE_OFF(n)	(0x1824 + ((n) << 4))
#घोषणा PCIE_WIN04_REMAP_OFF(n)	(0x182c + ((n) << 4))
#घोषणा PCIE_WIN5_CTRL_OFF	0x1880
#घोषणा PCIE_WIN5_BASE_OFF	0x1884
#घोषणा PCIE_WIN5_REMAP_OFF	0x188c
#घोषणा PCIE_CONF_ADDR_OFF	0x18f8
#घोषणा  PCIE_CONF_ADDR_EN		0x80000000
#घोषणा  PCIE_CONF_REG(r)		((((r) & 0xf00) << 16) | ((r) & 0xfc))
#घोषणा  PCIE_CONF_BUS(b)		(((b) & 0xff) << 16)
#घोषणा  PCIE_CONF_DEV(d)		(((d) & 0x1f) << 11)
#घोषणा  PCIE_CONF_FUNC(f)		(((f) & 0x7) << 8)
#घोषणा PCIE_CONF_DATA_OFF	0x18fc
#घोषणा PCIE_MASK_OFF		0x1910
#घोषणा PCIE_CTRL_OFF		0x1a00
#घोषणा  PCIE_CTRL_X1_MODE		0x0001
#घोषणा PCIE_STAT_OFF		0x1a04
#घोषणा  PCIE_STAT_DEV_OFFS		20
#घोषणा  PCIE_STAT_DEV_MASK		0x1f
#घोषणा  PCIE_STAT_BUS_OFFS		8
#घोषणा  PCIE_STAT_BUS_MASK		0xff
#घोषणा  PCIE_STAT_LINK_DOWN		1
#घोषणा PCIE_DEBUG_CTRL         0x1a60
#घोषणा  PCIE_DEBUG_SOFT_RESET		(1<<20)


u32 orion_pcie_dev_id(व्योम __iomem *base)
अणु
	वापस पढ़ोl(base + PCIE_DEV_ID_OFF) >> 16;
पूर्ण

u32 orion_pcie_rev(व्योम __iomem *base)
अणु
	वापस पढ़ोl(base + PCIE_DEV_REV_OFF) & 0xff;
पूर्ण

पूर्णांक orion_pcie_link_up(व्योम __iomem *base)
अणु
	वापस !(पढ़ोl(base + PCIE_STAT_OFF) & PCIE_STAT_LINK_DOWN);
पूर्ण

पूर्णांक __init orion_pcie_x4_mode(व्योम __iomem *base)
अणु
	वापस !(पढ़ोl(base + PCIE_CTRL_OFF) & PCIE_CTRL_X1_MODE);
पूर्ण

पूर्णांक orion_pcie_get_local_bus_nr(व्योम __iomem *base)
अणु
	u32 stat = पढ़ोl(base + PCIE_STAT_OFF);

	वापस (stat >> PCIE_STAT_BUS_OFFS) & PCIE_STAT_BUS_MASK;
पूर्ण

व्योम __init orion_pcie_set_local_bus_nr(व्योम __iomem *base, पूर्णांक nr)
अणु
	u32 stat;

	stat = पढ़ोl(base + PCIE_STAT_OFF);
	stat &= ~(PCIE_STAT_BUS_MASK << PCIE_STAT_BUS_OFFS);
	stat |= nr << PCIE_STAT_BUS_OFFS;
	ग_लिखोl(stat, base + PCIE_STAT_OFF);
पूर्ण

व्योम __init orion_pcie_reset(व्योम __iomem *base)
अणु
	u32 reg;
	पूर्णांक i;

	/*
	 * MV-S104860-U0, Rev. C:
	 * PCI Express Unit Soft Reset
	 * When set, generates an पूर्णांकernal reset in the PCI Express unit.
	 * This bit should be cleared after the link is re-established.
	 */
	reg = पढ़ोl(base + PCIE_DEBUG_CTRL);
	reg |= PCIE_DEBUG_SOFT_RESET;
	ग_लिखोl(reg, base + PCIE_DEBUG_CTRL);

	क्रम (i = 0; i < 20; i++) अणु
		mdelay(10);

		अगर (orion_pcie_link_up(base))
			अवरोध;
	पूर्ण

	reg &= ~(PCIE_DEBUG_SOFT_RESET);
	ग_लिखोl(reg, base + PCIE_DEBUG_CTRL);
पूर्ण

/*
 * Setup PCIE BARs and Address Decode Wins:
 * BAR[0,2] -> disabled, BAR[1] -> covers all DRAM banks
 * WIN[0-3] -> DRAM bank[0-3]
 */
अटल व्योम __init orion_pcie_setup_wins(व्योम __iomem *base)
अणु
	स्थिर काष्ठा mbus_dram_target_info *dram;
	u32 size;
	पूर्णांक i;

	dram = mv_mbus_dram_info();

	/*
	 * First, disable and clear BARs and winकरोws.
	 */
	क्रम (i = 1; i <= 2; i++) अणु
		ग_लिखोl(0, base + PCIE_BAR_CTRL_OFF(i));
		ग_लिखोl(0, base + PCIE_BAR_LO_OFF(i));
		ग_लिखोl(0, base + PCIE_BAR_HI_OFF(i));
	पूर्ण

	क्रम (i = 0; i < 5; i++) अणु
		ग_लिखोl(0, base + PCIE_WIN04_CTRL_OFF(i));
		ग_लिखोl(0, base + PCIE_WIN04_BASE_OFF(i));
		ग_लिखोl(0, base + PCIE_WIN04_REMAP_OFF(i));
	पूर्ण

	ग_लिखोl(0, base + PCIE_WIN5_CTRL_OFF);
	ग_लिखोl(0, base + PCIE_WIN5_BASE_OFF);
	ग_लिखोl(0, base + PCIE_WIN5_REMAP_OFF);

	/*
	 * Setup winकरोws क्रम DDR banks.  Count total DDR size on the fly.
	 */
	size = 0;
	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		ग_लिखोl(cs->base & 0xffff0000, base + PCIE_WIN04_BASE_OFF(i));
		ग_लिखोl(0, base + PCIE_WIN04_REMAP_OFF(i));
		ग_लिखोl(((cs->size - 1) & 0xffff0000) |
			(cs->mbus_attr << 8) |
			(dram->mbus_dram_target_id << 4) | 1,
				base + PCIE_WIN04_CTRL_OFF(i));

		size += cs->size;
	पूर्ण

	/*
	 * Round up 'size' to the nearest घातer of two.
	 */
	अगर ((size & (size - 1)) != 0)
		size = 1 << fls(size);

	/*
	 * Setup BAR[1] to all DRAM banks.
	 */
	ग_लिखोl(dram->cs[0].base, base + PCIE_BAR_LO_OFF(1));
	ग_लिखोl(0, base + PCIE_BAR_HI_OFF(1));
	ग_लिखोl(((size - 1) & 0xffff0000) | 1, base + PCIE_BAR_CTRL_OFF(1));
पूर्ण

व्योम __init orion_pcie_setup(व्योम __iomem *base)
अणु
	u16 cmd;
	u32 mask;

	/*
	 * Poपूर्णांक PCIe unit MBUS decode winकरोws to DRAM space.
	 */
	orion_pcie_setup_wins(base);

	/*
	 * Master + slave enable.
	 */
	cmd = पढ़ोw(base + PCIE_CMD_OFF);
	cmd |= PCI_COMMAND_IO;
	cmd |= PCI_COMMAND_MEMORY;
	cmd |= PCI_COMMAND_MASTER;
	ग_लिखोw(cmd, base + PCIE_CMD_OFF);

	/*
	 * Enable पूर्णांकerrupt lines A-D.
	 */
	mask = पढ़ोl(base + PCIE_MASK_OFF);
	mask |= 0x0f000000;
	ग_लिखोl(mask, base + PCIE_MASK_OFF);
पूर्ण

पूर्णांक orion_pcie_rd_conf(व्योम __iomem *base, काष्ठा pci_bus *bus,
		       u32 devfn, पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	ग_लिखोl(PCIE_CONF_BUS(bus->number) |
		PCIE_CONF_DEV(PCI_SLOT(devfn)) |
		PCIE_CONF_FUNC(PCI_FUNC(devfn)) |
		PCIE_CONF_REG(where) | PCIE_CONF_ADDR_EN,
			base + PCIE_CONF_ADDR_OFF);

	*val = पढ़ोl(base + PCIE_CONF_DATA_OFF);

	अगर (size == 1)
		*val = (*val >> (8 * (where & 3))) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (*val >> (8 * (where & 3))) & 0xffff;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

पूर्णांक orion_pcie_rd_conf_tlp(व्योम __iomem *base, काष्ठा pci_bus *bus,
			   u32 devfn, पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	ग_लिखोl(PCIE_CONF_BUS(bus->number) |
		PCIE_CONF_DEV(PCI_SLOT(devfn)) |
		PCIE_CONF_FUNC(PCI_FUNC(devfn)) |
		PCIE_CONF_REG(where) | PCIE_CONF_ADDR_EN,
			base + PCIE_CONF_ADDR_OFF);

	*val = पढ़ोl(base + PCIE_CONF_DATA_OFF);

	अगर (bus->number != orion_pcie_get_local_bus_nr(base) ||
	    PCI_FUNC(devfn) != 0)
		*val = पढ़ोl(base + PCIE_HEADER_LOG_4_OFF);

	अगर (size == 1)
		*val = (*val >> (8 * (where & 3))) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (*val >> (8 * (where & 3))) & 0xffff;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

पूर्णांक orion_pcie_rd_conf_wa(व्योम __iomem *wa_base, काष्ठा pci_bus *bus,
			  u32 devfn, पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	*val = पढ़ोl(wa_base + (PCIE_CONF_BUS(bus->number) |
				PCIE_CONF_DEV(PCI_SLOT(devfn)) |
				PCIE_CONF_FUNC(PCI_FUNC(devfn)) |
				PCIE_CONF_REG(where)));

	अगर (size == 1)
		*val = (*val >> (8 * (where & 3))) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (*val >> (8 * (where & 3))) & 0xffff;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

पूर्णांक orion_pcie_wr_conf(व्योम __iomem *base, काष्ठा pci_bus *bus,
		       u32 devfn, पूर्णांक where, पूर्णांक size, u32 val)
अणु
	पूर्णांक ret = PCIBIOS_SUCCESSFUL;

	ग_लिखोl(PCIE_CONF_BUS(bus->number) |
		PCIE_CONF_DEV(PCI_SLOT(devfn)) |
		PCIE_CONF_FUNC(PCI_FUNC(devfn)) |
		PCIE_CONF_REG(where) | PCIE_CONF_ADDR_EN,
			base + PCIE_CONF_ADDR_OFF);

	अगर (size == 4) अणु
		ग_लिखोl(val, base + PCIE_CONF_DATA_OFF);
	पूर्ण अन्यथा अगर (size == 2) अणु
		ग_लिखोw(val, base + PCIE_CONF_DATA_OFF + (where & 3));
	पूर्ण अन्यथा अगर (size == 1) अणु
		ग_लिखोb(val, base + PCIE_CONF_DATA_OFF + (where & 3));
	पूर्ण अन्यथा अणु
		ret = PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	वापस ret;
पूर्ण
