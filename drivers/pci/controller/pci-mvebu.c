<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe driver क्रम Marvell Armada 370 and Armada XP SoCs
 *
 * Author: Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/mbus.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश "../pci.h"
#समावेश "../pci-bridge-emul.h"

/*
 * PCIe unit रेजिस्टर offsets.
 */
#घोषणा PCIE_DEV_ID_OFF		0x0000
#घोषणा PCIE_CMD_OFF		0x0004
#घोषणा PCIE_DEV_REV_OFF	0x0008
#घोषणा PCIE_BAR_LO_OFF(n)	(0x0010 + ((n) << 3))
#घोषणा PCIE_BAR_HI_OFF(n)	(0x0014 + ((n) << 3))
#घोषणा PCIE_CAP_PCIEXP		0x0060
#घोषणा PCIE_HEADER_LOG_4_OFF	0x0128
#घोषणा PCIE_BAR_CTRL_OFF(n)	(0x1804 + (((n) - 1) * 4))
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
#घोषणा  PCIE_CONF_ADDR(bus, devfn, where) \
	(PCIE_CONF_BUS(bus) | PCIE_CONF_DEV(PCI_SLOT(devfn))    | \
	 PCIE_CONF_FUNC(PCI_FUNC(devfn)) | PCIE_CONF_REG(where) | \
	 PCIE_CONF_ADDR_EN)
#घोषणा PCIE_CONF_DATA_OFF	0x18fc
#घोषणा PCIE_MASK_OFF		0x1910
#घोषणा  PCIE_MASK_ENABLE_INTS          0x0f000000
#घोषणा PCIE_CTRL_OFF		0x1a00
#घोषणा  PCIE_CTRL_X1_MODE		0x0001
#घोषणा PCIE_STAT_OFF		0x1a04
#घोषणा  PCIE_STAT_BUS                  0xff00
#घोषणा  PCIE_STAT_DEV                  0x1f0000
#घोषणा  PCIE_STAT_LINK_DOWN		BIT(0)
#घोषणा PCIE_RC_RTSTA		0x1a14
#घोषणा PCIE_DEBUG_CTRL         0x1a60
#घोषणा  PCIE_DEBUG_SOFT_RESET		BIT(20)

काष्ठा mvebu_pcie_port;

/* Structure representing all PCIe पूर्णांकerfaces */
काष्ठा mvebu_pcie अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा mvebu_pcie_port *ports;
	काष्ठा resource io;
	काष्ठा resource realio;
	काष्ठा resource mem;
	काष्ठा resource busn;
	पूर्णांक nports;
पूर्ण;

काष्ठा mvebu_pcie_winकरोw अणु
	phys_addr_t base;
	phys_addr_t remap;
	माप_प्रकार size;
पूर्ण;

/* Structure representing one PCIe पूर्णांकerface */
काष्ठा mvebu_pcie_port अणु
	अक्षर *name;
	व्योम __iomem *base;
	u32 port;
	u32 lane;
	पूर्णांक devfn;
	अचिन्हित पूर्णांक mem_target;
	अचिन्हित पूर्णांक mem_attr;
	अचिन्हित पूर्णांक io_target;
	अचिन्हित पूर्णांक io_attr;
	काष्ठा clk *clk;
	काष्ठा gpio_desc *reset_gpio;
	अक्षर *reset_name;
	काष्ठा pci_bridge_emul bridge;
	काष्ठा device_node *dn;
	काष्ठा mvebu_pcie *pcie;
	काष्ठा mvebu_pcie_winकरोw memwin;
	काष्ठा mvebu_pcie_winकरोw iowin;
	u32 saved_pcie_stat;
	काष्ठा resource regs;
पूर्ण;

अटल अंतरभूत व्योम mvebu_ग_लिखोl(काष्ठा mvebu_pcie_port *port, u32 val, u32 reg)
अणु
	ग_लिखोl(val, port->base + reg);
पूर्ण

अटल अंतरभूत u32 mvebu_पढ़ोl(काष्ठा mvebu_pcie_port *port, u32 reg)
अणु
	वापस पढ़ोl(port->base + reg);
पूर्ण

अटल अंतरभूत bool mvebu_has_ioport(काष्ठा mvebu_pcie_port *port)
अणु
	वापस port->io_target != -1 && port->io_attr != -1;
पूर्ण

अटल bool mvebu_pcie_link_up(काष्ठा mvebu_pcie_port *port)
अणु
	वापस !(mvebu_पढ़ोl(port, PCIE_STAT_OFF) & PCIE_STAT_LINK_DOWN);
पूर्ण

अटल व्योम mvebu_pcie_set_local_bus_nr(काष्ठा mvebu_pcie_port *port, पूर्णांक nr)
अणु
	u32 stat;

	stat = mvebu_पढ़ोl(port, PCIE_STAT_OFF);
	stat &= ~PCIE_STAT_BUS;
	stat |= nr << 8;
	mvebu_ग_लिखोl(port, stat, PCIE_STAT_OFF);
पूर्ण

अटल व्योम mvebu_pcie_set_local_dev_nr(काष्ठा mvebu_pcie_port *port, पूर्णांक nr)
अणु
	u32 stat;

	stat = mvebu_पढ़ोl(port, PCIE_STAT_OFF);
	stat &= ~PCIE_STAT_DEV;
	stat |= nr << 16;
	mvebu_ग_लिखोl(port, stat, PCIE_STAT_OFF);
पूर्ण

/*
 * Setup PCIE BARs and Address Decode Wins:
 * BAR[0] -> पूर्णांकernal रेजिस्टरs (needed क्रम MSI)
 * BAR[1] -> covers all DRAM banks
 * BAR[2] -> Disabled
 * WIN[0-3] -> DRAM bank[0-3]
 */
अटल व्योम mvebu_pcie_setup_wins(काष्ठा mvebu_pcie_port *port)
अणु
	स्थिर काष्ठा mbus_dram_target_info *dram;
	u32 size;
	पूर्णांक i;

	dram = mv_mbus_dram_info();

	/* First, disable and clear BARs and winकरोws. */
	क्रम (i = 1; i < 3; i++) अणु
		mvebu_ग_लिखोl(port, 0, PCIE_BAR_CTRL_OFF(i));
		mvebu_ग_लिखोl(port, 0, PCIE_BAR_LO_OFF(i));
		mvebu_ग_लिखोl(port, 0, PCIE_BAR_HI_OFF(i));
	पूर्ण

	क्रम (i = 0; i < 5; i++) अणु
		mvebu_ग_लिखोl(port, 0, PCIE_WIN04_CTRL_OFF(i));
		mvebu_ग_लिखोl(port, 0, PCIE_WIN04_BASE_OFF(i));
		mvebu_ग_लिखोl(port, 0, PCIE_WIN04_REMAP_OFF(i));
	पूर्ण

	mvebu_ग_लिखोl(port, 0, PCIE_WIN5_CTRL_OFF);
	mvebu_ग_लिखोl(port, 0, PCIE_WIN5_BASE_OFF);
	mvebu_ग_लिखोl(port, 0, PCIE_WIN5_REMAP_OFF);

	/* Setup winकरोws क्रम DDR banks.  Count total DDR size on the fly. */
	size = 0;
	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		mvebu_ग_लिखोl(port, cs->base & 0xffff0000,
			     PCIE_WIN04_BASE_OFF(i));
		mvebu_ग_लिखोl(port, 0, PCIE_WIN04_REMAP_OFF(i));
		mvebu_ग_लिखोl(port,
			     ((cs->size - 1) & 0xffff0000) |
			     (cs->mbus_attr << 8) |
			     (dram->mbus_dram_target_id << 4) | 1,
			     PCIE_WIN04_CTRL_OFF(i));

		size += cs->size;
	पूर्ण

	/* Round up 'size' to the nearest घातer of two. */
	अगर ((size & (size - 1)) != 0)
		size = 1 << fls(size);

	/* Setup BAR[1] to all DRAM banks. */
	mvebu_ग_लिखोl(port, dram->cs[0].base, PCIE_BAR_LO_OFF(1));
	mvebu_ग_लिखोl(port, 0, PCIE_BAR_HI_OFF(1));
	mvebu_ग_लिखोl(port, ((size - 1) & 0xffff0000) | 1,
		     PCIE_BAR_CTRL_OFF(1));

	/*
	 * Poपूर्णांक BAR[0] to the device's पूर्णांकernal रेजिस्टरs.
	 */
	mvebu_ग_लिखोl(port, round_करोwn(port->regs.start, SZ_1M), PCIE_BAR_LO_OFF(0));
	mvebu_ग_लिखोl(port, 0, PCIE_BAR_HI_OFF(0));
पूर्ण

अटल व्योम mvebu_pcie_setup_hw(काष्ठा mvebu_pcie_port *port)
अणु
	u32 cmd, mask;

	/* Poपूर्णांक PCIe unit MBUS decode winकरोws to DRAM space. */
	mvebu_pcie_setup_wins(port);

	/* Master + slave enable. */
	cmd = mvebu_पढ़ोl(port, PCIE_CMD_OFF);
	cmd |= PCI_COMMAND_IO;
	cmd |= PCI_COMMAND_MEMORY;
	cmd |= PCI_COMMAND_MASTER;
	mvebu_ग_लिखोl(port, cmd, PCIE_CMD_OFF);

	/* Enable पूर्णांकerrupt lines A-D. */
	mask = mvebu_पढ़ोl(port, PCIE_MASK_OFF);
	mask |= PCIE_MASK_ENABLE_INTS;
	mvebu_ग_लिखोl(port, mask, PCIE_MASK_OFF);
पूर्ण

अटल पूर्णांक mvebu_pcie_hw_rd_conf(काष्ठा mvebu_pcie_port *port,
				 काष्ठा pci_bus *bus,
				 u32 devfn, पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	व्योम __iomem *conf_data = port->base + PCIE_CONF_DATA_OFF;

	mvebu_ग_लिखोl(port, PCIE_CONF_ADDR(bus->number, devfn, where),
		     PCIE_CONF_ADDR_OFF);

	चयन (size) अणु
	हाल 1:
		*val = पढ़ोb_relaxed(conf_data + (where & 3));
		अवरोध;
	हाल 2:
		*val = पढ़ोw_relaxed(conf_data + (where & 2));
		अवरोध;
	हाल 4:
		*val = पढ़ोl_relaxed(conf_data);
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक mvebu_pcie_hw_wr_conf(काष्ठा mvebu_pcie_port *port,
				 काष्ठा pci_bus *bus,
				 u32 devfn, पूर्णांक where, पूर्णांक size, u32 val)
अणु
	व्योम __iomem *conf_data = port->base + PCIE_CONF_DATA_OFF;

	mvebu_ग_लिखोl(port, PCIE_CONF_ADDR(bus->number, devfn, where),
		     PCIE_CONF_ADDR_OFF);

	चयन (size) अणु
	हाल 1:
		ग_लिखोb(val, conf_data + (where & 3));
		अवरोध;
	हाल 2:
		ग_लिखोw(val, conf_data + (where & 2));
		अवरोध;
	हाल 4:
		ग_लिखोl(val, conf_data);
		अवरोध;
	शेष:
		वापस PCIBIOS_BAD_REGISTER_NUMBER;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

/*
 * Remove winकरोws, starting from the largest ones to the smallest
 * ones.
 */
अटल व्योम mvebu_pcie_del_winकरोws(काष्ठा mvebu_pcie_port *port,
				   phys_addr_t base, माप_प्रकार size)
अणु
	जबतक (size) अणु
		माप_प्रकार sz = 1 << (fls(size) - 1);

		mvebu_mbus_del_winकरोw(base, sz);
		base += sz;
		size -= sz;
	पूर्ण
पूर्ण

/*
 * MBus winकरोws can only have a घातer of two size, but PCI BARs करो not
 * have this स्थिरraपूर्णांक. Thereक्रमe, we have to split the PCI BAR पूर्णांकo
 * areas each having a घातer of two size. We start from the largest
 * one (i.e highest order bit set in the size).
 */
अटल व्योम mvebu_pcie_add_winकरोws(काष्ठा mvebu_pcie_port *port,
				   अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक attribute,
				   phys_addr_t base, माप_प्रकार size,
				   phys_addr_t remap)
अणु
	माप_प्रकार size_mapped = 0;

	जबतक (size) अणु
		माप_प्रकार sz = 1 << (fls(size) - 1);
		पूर्णांक ret;

		ret = mvebu_mbus_add_winकरोw_remap_by_id(target, attribute, base,
							sz, remap);
		अगर (ret) अणु
			phys_addr_t end = base + sz - 1;

			dev_err(&port->pcie->pdev->dev,
				"Could not create MBus window at [mem %pa-%pa]: %d\n",
				&base, &end, ret);
			mvebu_pcie_del_winकरोws(port, base - size_mapped,
					       size_mapped);
			वापस;
		पूर्ण

		size -= sz;
		size_mapped += sz;
		base += sz;
		अगर (remap != MVEBU_MBUS_NO_REMAP)
			remap += sz;
	पूर्ण
पूर्ण

अटल व्योम mvebu_pcie_set_winकरोw(काष्ठा mvebu_pcie_port *port,
				  अचिन्हित पूर्णांक target, अचिन्हित पूर्णांक attribute,
				  स्थिर काष्ठा mvebu_pcie_winकरोw *desired,
				  काष्ठा mvebu_pcie_winकरोw *cur)
अणु
	अगर (desired->base == cur->base && desired->remap == cur->remap &&
	    desired->size == cur->size)
		वापस;

	अगर (cur->size != 0) अणु
		mvebu_pcie_del_winकरोws(port, cur->base, cur->size);
		cur->size = 0;
		cur->base = 0;

		/*
		 * If something tries to change the winकरोw जबतक it is enabled
		 * the change will not be करोne atomically. That would be
		 * dअगरficult to करो in the general हाल.
		 */
	पूर्ण

	अगर (desired->size == 0)
		वापस;

	mvebu_pcie_add_winकरोws(port, target, attribute, desired->base,
			       desired->size, desired->remap);
	*cur = *desired;
पूर्ण

अटल व्योम mvebu_pcie_handle_iobase_change(काष्ठा mvebu_pcie_port *port)
अणु
	काष्ठा mvebu_pcie_winकरोw desired = अणुपूर्ण;
	काष्ठा pci_bridge_emul_conf *conf = &port->bridge.conf;

	/* Are the new iobase/iolimit values invalid? */
	अगर (conf->iolimit < conf->iobase ||
	    conf->iolimitupper < conf->iobaseupper ||
	    !(conf->command & PCI_COMMAND_IO)) अणु
		mvebu_pcie_set_winकरोw(port, port->io_target, port->io_attr,
				      &desired, &port->iowin);
		वापस;
	पूर्ण

	अगर (!mvebu_has_ioport(port)) अणु
		dev_WARN(&port->pcie->pdev->dev,
			 "Attempt to set IO when IO is disabled\n");
		वापस;
	पूर्ण

	/*
	 * We पढ़ो the PCI-to-PCI bridge emulated रेजिस्टरs, and
	 * calculate the base address and size of the address decoding
	 * winकरोw to setup, according to the PCI-to-PCI bridge
	 * specअगरications. iobase is the bus address, port->iowin_base
	 * is the CPU address.
	 */
	desired.remap = ((conf->iobase & 0xF0) << 8) |
			(conf->iobaseupper << 16);
	desired.base = port->pcie->io.start + desired.remap;
	desired.size = ((0xFFF | ((conf->iolimit & 0xF0) << 8) |
			 (conf->iolimitupper << 16)) -
			desired.remap) +
		       1;

	mvebu_pcie_set_winकरोw(port, port->io_target, port->io_attr, &desired,
			      &port->iowin);
पूर्ण

अटल व्योम mvebu_pcie_handle_membase_change(काष्ठा mvebu_pcie_port *port)
अणु
	काष्ठा mvebu_pcie_winकरोw desired = अणु.remap = MVEBU_MBUS_NO_REMAPपूर्ण;
	काष्ठा pci_bridge_emul_conf *conf = &port->bridge.conf;

	/* Are the new membase/memlimit values invalid? */
	अगर (conf->memlimit < conf->membase ||
	    !(conf->command & PCI_COMMAND_MEMORY)) अणु
		mvebu_pcie_set_winकरोw(port, port->mem_target, port->mem_attr,
				      &desired, &port->memwin);
		वापस;
	पूर्ण

	/*
	 * We पढ़ो the PCI-to-PCI bridge emulated रेजिस्टरs, and
	 * calculate the base address and size of the address decoding
	 * winकरोw to setup, according to the PCI-to-PCI bridge
	 * specअगरications.
	 */
	desired.base = ((conf->membase & 0xFFF0) << 16);
	desired.size = (((conf->memlimit & 0xFFF0) << 16) | 0xFFFFF) -
		       desired.base + 1;

	mvebu_pcie_set_winकरोw(port, port->mem_target, port->mem_attr, &desired,
			      &port->memwin);
पूर्ण

अटल pci_bridge_emul_पढ़ो_status_t
mvebu_pci_bridge_emul_pcie_conf_पढ़ो(काष्ठा pci_bridge_emul *bridge,
				     पूर्णांक reg, u32 *value)
अणु
	काष्ठा mvebu_pcie_port *port = bridge->data;

	चयन (reg) अणु
	हाल PCI_EXP_DEVCAP:
		*value = mvebu_पढ़ोl(port, PCIE_CAP_PCIEXP + PCI_EXP_DEVCAP);
		अवरोध;

	हाल PCI_EXP_DEVCTL:
		*value = mvebu_पढ़ोl(port, PCIE_CAP_PCIEXP + PCI_EXP_DEVCTL) &
				 ~(PCI_EXP_DEVCTL_URRE | PCI_EXP_DEVCTL_FERE |
				   PCI_EXP_DEVCTL_NFERE | PCI_EXP_DEVCTL_CERE);
		अवरोध;

	हाल PCI_EXP_LNKCAP:
		/*
		 * PCIe requires the घड़ी घातer management capability to be
		 * hard-wired to zero क्रम करोwnstream ports
		 */
		*value = mvebu_पढ़ोl(port, PCIE_CAP_PCIEXP + PCI_EXP_LNKCAP) &
			 ~PCI_EXP_LNKCAP_CLKPM;
		अवरोध;

	हाल PCI_EXP_LNKCTL:
		*value = mvebu_पढ़ोl(port, PCIE_CAP_PCIEXP + PCI_EXP_LNKCTL);
		अवरोध;

	हाल PCI_EXP_SLTCTL:
		*value = PCI_EXP_SLTSTA_PDS << 16;
		अवरोध;

	हाल PCI_EXP_RTSTA:
		*value = mvebu_पढ़ोl(port, PCIE_RC_RTSTA);
		अवरोध;

	शेष:
		वापस PCI_BRIDGE_EMUL_NOT_HANDLED;
	पूर्ण

	वापस PCI_BRIDGE_EMUL_HANDLED;
पूर्ण

अटल व्योम
mvebu_pci_bridge_emul_base_conf_ग_लिखो(काष्ठा pci_bridge_emul *bridge,
				      पूर्णांक reg, u32 old, u32 new, u32 mask)
अणु
	काष्ठा mvebu_pcie_port *port = bridge->data;
	काष्ठा pci_bridge_emul_conf *conf = &bridge->conf;

	चयन (reg) अणु
	हाल PCI_COMMAND:
	अणु
		अगर (!mvebu_has_ioport(port))
			conf->command &= ~PCI_COMMAND_IO;

		अगर ((old ^ new) & PCI_COMMAND_IO)
			mvebu_pcie_handle_iobase_change(port);
		अगर ((old ^ new) & PCI_COMMAND_MEMORY)
			mvebu_pcie_handle_membase_change(port);

		अवरोध;
	पूर्ण

	हाल PCI_IO_BASE:
		/*
		 * We keep bit 1 set, it is a पढ़ो-only bit that
		 * indicates we support 32 bits addressing क्रम the
		 * I/O
		 */
		conf->iobase |= PCI_IO_RANGE_TYPE_32;
		conf->iolimit |= PCI_IO_RANGE_TYPE_32;
		mvebu_pcie_handle_iobase_change(port);
		अवरोध;

	हाल PCI_MEMORY_BASE:
		mvebu_pcie_handle_membase_change(port);
		अवरोध;

	हाल PCI_IO_BASE_UPPER16:
		mvebu_pcie_handle_iobase_change(port);
		अवरोध;

	हाल PCI_PRIMARY_BUS:
		mvebu_pcie_set_local_bus_nr(port, conf->secondary_bus);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mvebu_pci_bridge_emul_pcie_conf_ग_लिखो(काष्ठा pci_bridge_emul *bridge,
				      पूर्णांक reg, u32 old, u32 new, u32 mask)
अणु
	काष्ठा mvebu_pcie_port *port = bridge->data;

	चयन (reg) अणु
	हाल PCI_EXP_DEVCTL:
		/*
		 * Armada370 data says these bits must always
		 * be zero when in root complex mode.
		 */
		new &= ~(PCI_EXP_DEVCTL_URRE | PCI_EXP_DEVCTL_FERE |
			 PCI_EXP_DEVCTL_NFERE | PCI_EXP_DEVCTL_CERE);

		mvebu_ग_लिखोl(port, new, PCIE_CAP_PCIEXP + PCI_EXP_DEVCTL);
		अवरोध;

	हाल PCI_EXP_LNKCTL:
		/*
		 * If we करोn't support CLKREQ, we must ensure that the
		 * CLKREQ enable bit always पढ़ोs zero.  Since we haven't
		 * had this capability, and it's dependent on board wiring,
		 * disable it क्रम the समय being.
		 */
		new &= ~PCI_EXP_LNKCTL_CLKREQ_EN;

		mvebu_ग_लिखोl(port, new, PCIE_CAP_PCIEXP + PCI_EXP_LNKCTL);
		अवरोध;

	हाल PCI_EXP_RTSTA:
		mvebu_ग_लिखोl(port, new, PCIE_RC_RTSTA);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा pci_bridge_emul_ops mvebu_pci_bridge_emul_ops = अणु
	.ग_लिखो_base = mvebu_pci_bridge_emul_base_conf_ग_लिखो,
	.पढ़ो_pcie = mvebu_pci_bridge_emul_pcie_conf_पढ़ो,
	.ग_लिखो_pcie = mvebu_pci_bridge_emul_pcie_conf_ग_लिखो,
पूर्ण;

/*
 * Initialize the configuration space of the PCI-to-PCI bridge
 * associated with the given PCIe पूर्णांकerface.
 */
अटल व्योम mvebu_pci_bridge_emul_init(काष्ठा mvebu_pcie_port *port)
अणु
	काष्ठा pci_bridge_emul *bridge = &port->bridge;

	bridge->conf.venकरोr = PCI_VENDOR_ID_MARVELL;
	bridge->conf.device = mvebu_पढ़ोl(port, PCIE_DEV_ID_OFF) >> 16;
	bridge->conf.class_revision =
		mvebu_पढ़ोl(port, PCIE_DEV_REV_OFF) & 0xff;

	अगर (mvebu_has_ioport(port)) अणु
		/* We support 32 bits I/O addressing */
		bridge->conf.iobase = PCI_IO_RANGE_TYPE_32;
		bridge->conf.iolimit = PCI_IO_RANGE_TYPE_32;
	पूर्ण

	bridge->has_pcie = true;
	bridge->data = port;
	bridge->ops = &mvebu_pci_bridge_emul_ops;

	pci_bridge_emul_init(bridge, PCI_BRIDGE_EMUL_NO_PREFETCHABLE_BAR);
पूर्ण

अटल अंतरभूत काष्ठा mvebu_pcie *sys_to_pcie(काष्ठा pci_sys_data *sys)
अणु
	वापस sys->निजी_data;
पूर्ण

अटल काष्ठा mvebu_pcie_port *mvebu_pcie_find_port(काष्ठा mvebu_pcie *pcie,
						    काष्ठा pci_bus *bus,
						    पूर्णांक devfn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pcie->nports; i++) अणु
		काष्ठा mvebu_pcie_port *port = &pcie->ports[i];

		अगर (bus->number == 0 && port->devfn == devfn)
			वापस port;
		अगर (bus->number != 0 &&
		    bus->number >= port->bridge.conf.secondary_bus &&
		    bus->number <= port->bridge.conf.subordinate_bus)
			वापस port;
	पूर्ण

	वापस शून्य;
पूर्ण

/* PCI configuration space ग_लिखो function */
अटल पूर्णांक mvebu_pcie_wr_conf(काष्ठा pci_bus *bus, u32 devfn,
			      पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा mvebu_pcie *pcie = bus->sysdata;
	काष्ठा mvebu_pcie_port *port;
	पूर्णांक ret;

	port = mvebu_pcie_find_port(pcie, bus, devfn);
	अगर (!port)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/* Access the emulated PCI-to-PCI bridge */
	अगर (bus->number == 0)
		वापस pci_bridge_emul_conf_ग_लिखो(&port->bridge, where,
						  size, val);

	अगर (!mvebu_pcie_link_up(port))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/* Access the real PCIe पूर्णांकerface */
	ret = mvebu_pcie_hw_wr_conf(port, bus, devfn,
				    where, size, val);

	वापस ret;
पूर्ण

/* PCI configuration space पढ़ो function */
अटल पूर्णांक mvebu_pcie_rd_conf(काष्ठा pci_bus *bus, u32 devfn, पूर्णांक where,
			      पूर्णांक size, u32 *val)
अणु
	काष्ठा mvebu_pcie *pcie = bus->sysdata;
	काष्ठा mvebu_pcie_port *port;
	पूर्णांक ret;

	port = mvebu_pcie_find_port(pcie, bus, devfn);
	अगर (!port) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	/* Access the emulated PCI-to-PCI bridge */
	अगर (bus->number == 0)
		वापस pci_bridge_emul_conf_पढ़ो(&port->bridge, where,
						 size, val);

	अगर (!mvebu_pcie_link_up(port)) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	/* Access the real PCIe पूर्णांकerface */
	ret = mvebu_pcie_hw_rd_conf(port, bus, devfn,
				    where, size, val);

	वापस ret;
पूर्ण

अटल काष्ठा pci_ops mvebu_pcie_ops = अणु
	.पढ़ो = mvebu_pcie_rd_conf,
	.ग_लिखो = mvebu_pcie_wr_conf,
पूर्ण;

अटल resource_माप_प्रकार mvebu_pcie_align_resource(काष्ठा pci_dev *dev,
						 स्थिर काष्ठा resource *res,
						 resource_माप_प्रकार start,
						 resource_माप_प्रकार size,
						 resource_माप_प्रकार align)
अणु
	अगर (dev->bus->number != 0)
		वापस start;

	/*
	 * On the PCI-to-PCI bridge side, the I/O winकरोws must have at
	 * least a 64 KB size and the memory winकरोws must have at
	 * least a 1 MB size. Moreover, MBus winकरोws need to have a
	 * base address aligned on their size, and their size must be
	 * a घातer of two. This means that अगर the BAR करोesn't have a
	 * घातer of two size, several MBus winकरोws will actually be
	 * created. We need to ensure that the biggest MBus winकरोw
	 * (which will be the first one) is aligned on its size, which
	 * explains the roundकरोwn_घात_of_two() being करोne here.
	 */
	अगर (res->flags & IORESOURCE_IO)
		वापस round_up(start, max_t(resource_माप_प्रकार, SZ_64K,
					     roundकरोwn_घात_of_two(size)));
	अन्यथा अगर (res->flags & IORESOURCE_MEM)
		वापस round_up(start, max_t(resource_माप_प्रकार, SZ_1M,
					     roundकरोwn_घात_of_two(size)));
	अन्यथा
		वापस start;
पूर्ण

अटल व्योम __iomem *mvebu_pcie_map_रेजिस्टरs(काष्ठा platक्रमm_device *pdev,
					      काष्ठा device_node *np,
					      काष्ठा mvebu_pcie_port *port)
अणु
	पूर्णांक ret = 0;

	ret = of_address_to_resource(np, 0, &port->regs);
	अगर (ret)
		वापस (व्योम __iomem *)ERR_PTR(ret);

	वापस devm_ioremap_resource(&pdev->dev, &port->regs);
पूर्ण

#घोषणा DT_FLAGS_TO_TYPE(flags)       (((flags) >> 24) & 0x03)
#घोषणा    DT_TYPE_IO                 0x1
#घोषणा    DT_TYPE_MEM32              0x2
#घोषणा DT_CPUADDR_TO_TARGET(cpuaddr) (((cpuaddr) >> 56) & 0xFF)
#घोषणा DT_CPUADDR_TO_ATTR(cpuaddr)   (((cpuaddr) >> 48) & 0xFF)

अटल पूर्णांक mvebu_get_tgt_attr(काष्ठा device_node *np, पूर्णांक devfn,
			      अचिन्हित दीर्घ type,
			      अचिन्हित पूर्णांक *tgt,
			      अचिन्हित पूर्णांक *attr)
अणु
	स्थिर पूर्णांक na = 3, ns = 2;
	स्थिर __be32 *range;
	पूर्णांक rlen, nranges, rangesz, pna, i;

	*tgt = -1;
	*attr = -1;

	range = of_get_property(np, "ranges", &rlen);
	अगर (!range)
		वापस -EINVAL;

	pna = of_n_addr_cells(np);
	rangesz = pna + na + ns;
	nranges = rlen / माप(__be32) / rangesz;

	क्रम (i = 0; i < nranges; i++, range += rangesz) अणु
		u32 flags = of_पढ़ो_number(range, 1);
		u32 slot = of_पढ़ो_number(range + 1, 1);
		u64 cpuaddr = of_पढ़ो_number(range + na, pna);
		अचिन्हित दीर्घ rtype;

		अगर (DT_FLAGS_TO_TYPE(flags) == DT_TYPE_IO)
			rtype = IORESOURCE_IO;
		अन्यथा अगर (DT_FLAGS_TO_TYPE(flags) == DT_TYPE_MEM32)
			rtype = IORESOURCE_MEM;
		अन्यथा
			जारी;

		अगर (slot == PCI_SLOT(devfn) && type == rtype) अणु
			*tgt = DT_CPUADDR_TO_TARGET(cpuaddr);
			*attr = DT_CPUADDR_TO_ATTR(cpuaddr);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mvebu_pcie_suspend(काष्ठा device *dev)
अणु
	काष्ठा mvebu_pcie *pcie;
	पूर्णांक i;

	pcie = dev_get_drvdata(dev);
	क्रम (i = 0; i < pcie->nports; i++) अणु
		काष्ठा mvebu_pcie_port *port = pcie->ports + i;
		port->saved_pcie_stat = mvebu_पढ़ोl(port, PCIE_STAT_OFF);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_pcie_resume(काष्ठा device *dev)
अणु
	काष्ठा mvebu_pcie *pcie;
	पूर्णांक i;

	pcie = dev_get_drvdata(dev);
	क्रम (i = 0; i < pcie->nports; i++) अणु
		काष्ठा mvebu_pcie_port *port = pcie->ports + i;
		mvebu_ग_लिखोl(port, port->saved_pcie_stat, PCIE_STAT_OFF);
		mvebu_pcie_setup_hw(port);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम mvebu_pcie_port_clk_put(व्योम *data)
अणु
	काष्ठा mvebu_pcie_port *port = data;

	clk_put(port->clk);
पूर्ण

अटल पूर्णांक mvebu_pcie_parse_port(काष्ठा mvebu_pcie *pcie,
	काष्ठा mvebu_pcie_port *port, काष्ठा device_node *child)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	क्रमागत of_gpio_flags flags;
	पूर्णांक reset_gpio, ret;

	port->pcie = pcie;

	अगर (of_property_पढ़ो_u32(child, "marvell,pcie-port", &port->port)) अणु
		dev_warn(dev, "ignoring %pOF, missing pcie-port property\n",
			 child);
		जाओ skip;
	पूर्ण

	अगर (of_property_पढ़ो_u32(child, "marvell,pcie-lane", &port->lane))
		port->lane = 0;

	port->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "pcie%d.%d", port->port,
				    port->lane);
	अगर (!port->name) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	port->devfn = of_pci_get_devfn(child);
	अगर (port->devfn < 0)
		जाओ skip;

	ret = mvebu_get_tgt_attr(dev->of_node, port->devfn, IORESOURCE_MEM,
				 &port->mem_target, &port->mem_attr);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: cannot get tgt/attr for mem window\n",
			port->name);
		जाओ skip;
	पूर्ण

	अगर (resource_size(&pcie->io) != 0) अणु
		mvebu_get_tgt_attr(dev->of_node, port->devfn, IORESOURCE_IO,
				   &port->io_target, &port->io_attr);
	पूर्ण अन्यथा अणु
		port->io_target = -1;
		port->io_attr = -1;
	पूर्ण

	reset_gpio = of_get_named_gpio_flags(child, "reset-gpios", 0, &flags);
	अगर (reset_gpio == -EPROBE_DEFER) अणु
		ret = reset_gpio;
		जाओ err;
	पूर्ण

	अगर (gpio_is_valid(reset_gpio)) अणु
		अचिन्हित दीर्घ gpio_flags;

		port->reset_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s-reset",
						  port->name);
		अगर (!port->reset_name) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण

		अगर (flags & OF_GPIO_ACTIVE_LOW) अणु
			dev_info(dev, "%pOF: reset gpio is active low\n",
				 child);
			gpio_flags = GPIOF_ACTIVE_LOW |
				     GPIOF_OUT_INIT_LOW;
		पूर्ण अन्यथा अणु
			gpio_flags = GPIOF_OUT_INIT_HIGH;
		पूर्ण

		ret = devm_gpio_request_one(dev, reset_gpio, gpio_flags,
					    port->reset_name);
		अगर (ret) अणु
			अगर (ret == -EPROBE_DEFER)
				जाओ err;
			जाओ skip;
		पूर्ण

		port->reset_gpio = gpio_to_desc(reset_gpio);
	पूर्ण

	port->clk = of_clk_get_by_name(child, शून्य);
	अगर (IS_ERR(port->clk)) अणु
		dev_err(dev, "%s: cannot get clock\n", port->name);
		जाओ skip;
	पूर्ण

	ret = devm_add_action(dev, mvebu_pcie_port_clk_put, port);
	अगर (ret < 0) अणु
		clk_put(port->clk);
		जाओ err;
	पूर्ण

	वापस 1;

skip:
	ret = 0;

	/* In the हाल of skipping, we need to मुक्त these */
	devm_kमुक्त(dev, port->reset_name);
	port->reset_name = शून्य;
	devm_kमुक्त(dev, port->name);
	port->name = शून्य;

err:
	वापस ret;
पूर्ण

/*
 * Power up a PCIe port.  PCIe requires the refclk to be stable क्रम 100तगs
 * prior to releasing PERST.  See table 2-4 in section 2.6.2 AC Specअगरications
 * of the PCI Express Card Electromechanical Specअगरication, 1.1.
 */
अटल पूर्णांक mvebu_pcie_घातerup(काष्ठा mvebu_pcie_port *port)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(port->clk);
	अगर (ret < 0)
		वापस ret;

	अगर (port->reset_gpio) अणु
		u32 reset_udelay = PCI_PM_D3COLD_WAIT * 1000;

		of_property_पढ़ो_u32(port->dn, "reset-delay-us",
				     &reset_udelay);

		udelay(100);

		gpiod_set_value_cansleep(port->reset_gpio, 0);
		msleep(reset_udelay / 1000);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Power करोwn a PCIe port.  Strictly, PCIe requires us to place the card
 * in D3hot state beक्रमe निश्चितing PERST#.
 */
अटल व्योम mvebu_pcie_घातerकरोwn(काष्ठा mvebu_pcie_port *port)
अणु
	gpiod_set_value_cansleep(port->reset_gpio, 1);

	clk_disable_unprepare(port->clk);
पूर्ण

/*
 * devm_of_pci_get_host_bridge_resources() only sets up translateable resources,
 * so we need extra resource setup parsing our special DT properties encoding
 * the MEM and IO apertures.
 */
अटल पूर्णांक mvebu_pcie_parse_request_resources(काष्ठा mvebu_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(pcie);
	पूर्णांक ret;

	/* Get the PCIe memory aperture */
	mvebu_mbus_get_pcie_mem_aperture(&pcie->mem);
	अगर (resource_size(&pcie->mem) == 0) अणु
		dev_err(dev, "invalid memory aperture size\n");
		वापस -EINVAL;
	पूर्ण

	pcie->mem.name = "PCI MEM";
	pci_add_resource(&bridge->winकरोws, &pcie->mem);
	ret = devm_request_resource(dev, &iomem_resource, &pcie->mem);
	अगर (ret)
		वापस ret;

	/* Get the PCIe IO aperture */
	mvebu_mbus_get_pcie_io_aperture(&pcie->io);

	अगर (resource_size(&pcie->io) != 0) अणु
		pcie->realio.flags = pcie->io.flags;
		pcie->realio.start = PCIBIOS_MIN_IO;
		pcie->realio.end = min_t(resource_माप_प्रकार,
					 IO_SPACE_LIMIT - SZ_64K,
					 resource_size(&pcie->io) - 1);
		pcie->realio.name = "PCI I/O";

		pci_add_resource(&bridge->winकरोws, &pcie->realio);
		ret = devm_request_resource(dev, &ioport_resource, &pcie->realio);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This is a copy of pci_host_probe(), except that it करोes the I/O
 * remap as the last step, once we are sure we won't fail.
 *
 * It should be हटाओd once the I/O remap error handling issue has
 * been sorted out.
 */
अटल पूर्णांक mvebu_pci_host_probe(काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा mvebu_pcie *pcie;
	काष्ठा pci_bus *bus, *child;
	पूर्णांक ret;

	ret = pci_scan_root_bus_bridge(bridge);
	अगर (ret < 0) अणु
		dev_err(bridge->dev.parent, "Scanning root bridge failed");
		वापस ret;
	पूर्ण

	pcie = pci_host_bridge_priv(bridge);
	अगर (resource_size(&pcie->io) != 0) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < resource_size(&pcie->realio); i += SZ_64K)
			pci_ioremap_io(i, pcie->io.start + i);
	पूर्ण

	bus = bridge->bus;

	/*
	 * We insert PCI resources पूर्णांकo the iomem_resource and
	 * ioport_resource trees in either pci_bus_claim_resources()
	 * or pci_bus_assign_resources().
	 */
	अगर (pci_has_flag(PCI_PROBE_ONLY)) अणु
		pci_bus_claim_resources(bus);
	पूर्ण अन्यथा अणु
		pci_bus_size_bridges(bus);
		pci_bus_assign_resources(bus);

		list_क्रम_each_entry(child, &bus->children, node)
			pcie_bus_configure_settings(child);
	पूर्ण

	pci_bus_add_devices(bus);
	वापस 0;
पूर्ण

अटल पूर्णांक mvebu_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mvebu_pcie *pcie;
	काष्ठा pci_host_bridge *bridge;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child;
	पूर्णांक num, i, ret;

	bridge = devm_pci_alloc_host_bridge(dev, माप(काष्ठा mvebu_pcie));
	अगर (!bridge)
		वापस -ENOMEM;

	pcie = pci_host_bridge_priv(bridge);
	pcie->pdev = pdev;
	platक्रमm_set_drvdata(pdev, pcie);

	ret = mvebu_pcie_parse_request_resources(pcie);
	अगर (ret)
		वापस ret;

	num = of_get_available_child_count(np);

	pcie->ports = devm_kसुस्मृति(dev, num, माप(*pcie->ports), GFP_KERNEL);
	अगर (!pcie->ports)
		वापस -ENOMEM;

	i = 0;
	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा mvebu_pcie_port *port = &pcie->ports[i];

		ret = mvebu_pcie_parse_port(pcie, port, child);
		अगर (ret < 0) अणु
			of_node_put(child);
			वापस ret;
		पूर्ण अन्यथा अगर (ret == 0) अणु
			जारी;
		पूर्ण

		port->dn = child;
		i++;
	पूर्ण
	pcie->nports = i;

	क्रम (i = 0; i < pcie->nports; i++) अणु
		काष्ठा mvebu_pcie_port *port = &pcie->ports[i];

		child = port->dn;
		अगर (!child)
			जारी;

		ret = mvebu_pcie_घातerup(port);
		अगर (ret < 0)
			जारी;

		port->base = mvebu_pcie_map_रेजिस्टरs(pdev, child, port);
		अगर (IS_ERR(port->base)) अणु
			dev_err(dev, "%s: cannot map registers\n", port->name);
			port->base = शून्य;
			mvebu_pcie_घातerकरोwn(port);
			जारी;
		पूर्ण

		mvebu_pcie_setup_hw(port);
		mvebu_pcie_set_local_dev_nr(port, 1);
		mvebu_pci_bridge_emul_init(port);
	पूर्ण

	pcie->nports = i;

	bridge->sysdata = pcie;
	bridge->ops = &mvebu_pcie_ops;
	bridge->align_resource = mvebu_pcie_align_resource;

	वापस mvebu_pci_host_probe(bridge);
पूर्ण

अटल स्थिर काष्ठा of_device_id mvebu_pcie_of_match_table[] = अणु
	अणु .compatible = "marvell,armada-xp-pcie", पूर्ण,
	अणु .compatible = "marvell,armada-370-pcie", पूर्ण,
	अणु .compatible = "marvell,dove-pcie", पूर्ण,
	अणु .compatible = "marvell,kirkwood-pcie", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops mvebu_pcie_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(mvebu_pcie_suspend, mvebu_pcie_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver mvebu_pcie_driver = अणु
	.driver = अणु
		.name = "mvebu-pcie",
		.of_match_table = mvebu_pcie_of_match_table,
		/* driver unloading/unbinding currently not supported */
		.suppress_bind_attrs = true,
		.pm = &mvebu_pcie_pm_ops,
	पूर्ण,
	.probe = mvebu_pcie_probe,
पूर्ण;
builtin_platक्रमm_driver(mvebu_pcie_driver);
