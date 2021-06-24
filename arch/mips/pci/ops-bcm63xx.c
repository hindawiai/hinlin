<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश "pci-bcm63xx.h"

/*
 * swizzle 32bits data to वापस only the needed part
 */
अटल पूर्णांक postprocess_पढ़ो(u32 data, पूर्णांक where, अचिन्हित पूर्णांक size)
अणु
	u32 ret;

	ret = 0;
	चयन (size) अणु
	हाल 1:
		ret = (data >> ((where & 3) << 3)) & 0xff;
		अवरोध;
	हाल 2:
		ret = (data >> ((where & 3) << 3)) & 0xffff;
		अवरोध;
	हाल 4:
		ret = data;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक preprocess_ग_लिखो(u32 orig_data, u32 val, पूर्णांक where,
			    अचिन्हित पूर्णांक size)
अणु
	u32 ret;

	ret = 0;
	चयन (size) अणु
	हाल 1:
		ret = (orig_data & ~(0xff << ((where & 3) << 3))) |
			(val << ((where & 3) << 3));
		अवरोध;
	हाल 2:
		ret = (orig_data & ~(0xffff << ((where & 3) << 3))) |
			(val << ((where & 3) << 3));
		अवरोध;
	हाल 4:
		ret = val;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * setup hardware क्रम a configuration cycle with given parameters
 */
अटल पूर्णांक bcm63xx_setup_cfg_access(पूर्णांक type, अचिन्हित पूर्णांक busn,
				    अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	अचिन्हित पूर्णांक slot, func, reg;
	u32 val;

	slot = PCI_SLOT(devfn);
	func = PCI_FUNC(devfn);
	reg = where >> 2;

	/* sanity check */
	अगर (slot > (MPI_L2PCFG_DEVNUM_MASK >> MPI_L2PCFG_DEVNUM_SHIFT))
		वापस 1;

	अगर (func > (MPI_L2PCFG_FUNC_MASK >> MPI_L2PCFG_FUNC_SHIFT))
		वापस 1;

	अगर (reg > (MPI_L2PCFG_REG_MASK >> MPI_L2PCFG_REG_SHIFT))
		वापस 1;

	/* ok, setup config access */
	val = (reg << MPI_L2PCFG_REG_SHIFT);
	val |= (func << MPI_L2PCFG_FUNC_SHIFT);
	val |= (slot << MPI_L2PCFG_DEVNUM_SHIFT);
	val |= MPI_L2PCFG_CFG_USEREG_MASK;
	val |= MPI_L2PCFG_CFG_SEL_MASK;
	/* type 0 cycle क्रम local bus, type 1 cycle क्रम anything अन्यथा */
	अगर (type != 0) अणु
		/* FIXME: how to specअगरy bus ??? */
		val |= (1 << MPI_L2PCFG_CFG_TYPE_SHIFT);
	पूर्ण
	bcm_mpi_ग_लिखोl(val, MPI_L2PCFG_REG);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_करो_cfg_पढ़ो(पूर्णांक type, अचिन्हित पूर्णांक busn,
				अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size,
				u32 *val)
अणु
	u32 data;

	/* two phase cycle, first we ग_लिखो address, then पढ़ो data at
	 * another location, caller alपढ़ोy has a spinlock so no need
	 * to add one here  */
	अगर (bcm63xx_setup_cfg_access(type, busn, devfn, where))
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	iob();
	data = le32_to_cpu(__raw_पढ़ोl(pci_iospace_start));
	/* restore IO space normal behaviour */
	bcm_mpi_ग_लिखोl(0, MPI_L2PCFG_REG);

	*val = postprocess_पढ़ो(data, where, size);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक bcm63xx_करो_cfg_ग_लिखो(पूर्णांक type, अचिन्हित पूर्णांक busn,
				 अचिन्हित पूर्णांक devfn, पूर्णांक where, पूर्णांक size,
				 u32 val)
अणु
	u32 data;

	/* two phase cycle, first we ग_लिखो address, then ग_लिखो data to
	 * another location, caller alपढ़ोy has a spinlock so no need
	 * to add one here  */
	अगर (bcm63xx_setup_cfg_access(type, busn, devfn, where))
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	iob();

	data = le32_to_cpu(__raw_पढ़ोl(pci_iospace_start));
	data = preprocess_ग_लिखो(data, val, where, size);

	__raw_ग_लिखोl(cpu_to_le32(data), pci_iospace_start);
	wmb();
	/* no way to know the access is करोne, we have to रुको */
	udelay(500);
	/* restore IO space normal behaviour */
	bcm_mpi_ग_लिखोl(0, MPI_L2PCFG_REG);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक bcm63xx_pci_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	पूर्णांक type;

	type = bus->parent ? 1 : 0;

	अगर (type == 0 && PCI_SLOT(devfn) == CARDBUS_PCI_IDSEL)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस bcm63xx_करो_cfg_पढ़ो(type, bus->number, devfn,
				    where, size, val);
पूर्ण

अटल पूर्णांक bcm63xx_pci_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, पूर्णांक size, u32 val)
अणु
	पूर्णांक type;

	type = bus->parent ? 1 : 0;

	अगर (type == 0 && PCI_SLOT(devfn) == CARDBUS_PCI_IDSEL)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	वापस bcm63xx_करो_cfg_ग_लिखो(type, bus->number, devfn,
				     where, size, val);
पूर्ण

काष्ठा pci_ops bcm63xx_pci_ops = अणु
	.पढ़ो	= bcm63xx_pci_पढ़ो,
	.ग_लिखो	= bcm63xx_pci_ग_लिखो
पूर्ण;

#अगर_घोषित CONFIG_CARDBUS
/*
 * emulate configuration पढ़ो access on a cardbus bridge
 */
#घोषणा FAKE_CB_BRIDGE_SLOT	0x1e

अटल पूर्णांक fake_cb_bridge_bus_number = -1;

अटल काष्ठा अणु
	u16 pci_command;
	u8 cb_latency;
	u8 subordinate_busn;
	u8 cardbus_busn;
	u8 pci_busn;
	पूर्णांक bus_asचिन्हित;
	u16 bridge_control;

	u32 mem_base0;
	u32 mem_limit0;
	u32 mem_base1;
	u32 mem_limit1;

	u32 io_base0;
	u32 io_limit0;
	u32 io_base1;
	u32 io_limit1;
पूर्ण fake_cb_bridge_regs;

अटल पूर्णांक fake_cb_bridge_पढ़ो(पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	अचिन्हित पूर्णांक reg;
	u32 data;

	data = 0;
	reg = where >> 2;
	चयन (reg) अणु
	हाल (PCI_VENDOR_ID >> 2):
	हाल (PCI_CB_SUBSYSTEM_VENDOR_ID >> 2):
		/* create dummy venकरोr/device id from our cpu id */
		data = (bcm63xx_get_cpu_id() << 16) | PCI_VENDOR_ID_BROADCOM;
		अवरोध;

	हाल (PCI_COMMAND >> 2):
		data = (PCI_STATUS_DEVSEL_SLOW << 16);
		data |= fake_cb_bridge_regs.pci_command;
		अवरोध;

	हाल (PCI_CLASS_REVISION >> 2):
		data = (PCI_CLASS_BRIDGE_CARDBUS << 16);
		अवरोध;

	हाल (PCI_CACHE_LINE_SIZE >> 2):
		data = (PCI_HEADER_TYPE_CARDBUS << 16);
		अवरोध;

	हाल (PCI_INTERRUPT_LINE >> 2):
		/* bridge control */
		data = (fake_cb_bridge_regs.bridge_control << 16);
		/* pin:पूर्णांकA line:0xff */
		data |= (0x1 << 8) | 0xff;
		अवरोध;

	हाल (PCI_CB_PRIMARY_BUS >> 2):
		data = (fake_cb_bridge_regs.cb_latency << 24);
		data |= (fake_cb_bridge_regs.subordinate_busn << 16);
		data |= (fake_cb_bridge_regs.cardbus_busn << 8);
		data |= fake_cb_bridge_regs.pci_busn;
		अवरोध;

	हाल (PCI_CB_MEMORY_BASE_0 >> 2):
		data = fake_cb_bridge_regs.mem_base0;
		अवरोध;

	हाल (PCI_CB_MEMORY_LIMIT_0 >> 2):
		data = fake_cb_bridge_regs.mem_limit0;
		अवरोध;

	हाल (PCI_CB_MEMORY_BASE_1 >> 2):
		data = fake_cb_bridge_regs.mem_base1;
		अवरोध;

	हाल (PCI_CB_MEMORY_LIMIT_1 >> 2):
		data = fake_cb_bridge_regs.mem_limit1;
		अवरोध;

	हाल (PCI_CB_IO_BASE_0 >> 2):
		/* | 1 क्रम 32bits io support */
		data = fake_cb_bridge_regs.io_base0 | 0x1;
		अवरोध;

	हाल (PCI_CB_IO_LIMIT_0 >> 2):
		data = fake_cb_bridge_regs.io_limit0;
		अवरोध;

	हाल (PCI_CB_IO_BASE_1 >> 2):
		/* | 1 क्रम 32bits io support */
		data = fake_cb_bridge_regs.io_base1 | 0x1;
		अवरोध;

	हाल (PCI_CB_IO_LIMIT_1 >> 2):
		data = fake_cb_bridge_regs.io_limit1;
		अवरोध;
	पूर्ण

	*val = postprocess_पढ़ो(data, where, size);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

/*
 * emulate configuration ग_लिखो access on a cardbus bridge
 */
अटल पूर्णांक fake_cb_bridge_ग_लिखो(पूर्णांक where, पूर्णांक size, u32 val)
अणु
	अचिन्हित पूर्णांक reg;
	u32 data, पंचांगp;
	पूर्णांक ret;

	ret = fake_cb_bridge_पढ़ो((where & ~0x3), 4, &data);
	अगर (ret != PCIBIOS_SUCCESSFUL)
		वापस ret;

	data = preprocess_ग_लिखो(data, val, where, size);

	reg = where >> 2;
	चयन (reg) अणु
	हाल (PCI_COMMAND >> 2):
		fake_cb_bridge_regs.pci_command = (data & 0xffff);
		अवरोध;

	हाल (PCI_CB_PRIMARY_BUS >> 2):
		fake_cb_bridge_regs.cb_latency = (data >> 24) & 0xff;
		fake_cb_bridge_regs.subordinate_busn = (data >> 16) & 0xff;
		fake_cb_bridge_regs.cardbus_busn = (data >> 8) & 0xff;
		fake_cb_bridge_regs.pci_busn = data & 0xff;
		अगर (fake_cb_bridge_regs.cardbus_busn)
			fake_cb_bridge_regs.bus_asचिन्हित = 1;
		अवरोध;

	हाल (PCI_INTERRUPT_LINE >> 2):
		पंचांगp = (data >> 16) & 0xffff;
		/* disable memory prefetch support */
		पंचांगp &= ~PCI_CB_BRIDGE_CTL_PREFETCH_MEM0;
		पंचांगp &= ~PCI_CB_BRIDGE_CTL_PREFETCH_MEM1;
		fake_cb_bridge_regs.bridge_control = पंचांगp;
		अवरोध;

	हाल (PCI_CB_MEMORY_BASE_0 >> 2):
		fake_cb_bridge_regs.mem_base0 = data;
		अवरोध;

	हाल (PCI_CB_MEMORY_LIMIT_0 >> 2):
		fake_cb_bridge_regs.mem_limit0 = data;
		अवरोध;

	हाल (PCI_CB_MEMORY_BASE_1 >> 2):
		fake_cb_bridge_regs.mem_base1 = data;
		अवरोध;

	हाल (PCI_CB_MEMORY_LIMIT_1 >> 2):
		fake_cb_bridge_regs.mem_limit1 = data;
		अवरोध;

	हाल (PCI_CB_IO_BASE_0 >> 2):
		fake_cb_bridge_regs.io_base0 = data;
		अवरोध;

	हाल (PCI_CB_IO_LIMIT_0 >> 2):
		fake_cb_bridge_regs.io_limit0 = data;
		अवरोध;

	हाल (PCI_CB_IO_BASE_1 >> 2):
		fake_cb_bridge_regs.io_base1 = data;
		अवरोध;

	हाल (PCI_CB_IO_LIMIT_1 >> 2):
		fake_cb_bridge_regs.io_limit1 = data;
		अवरोध;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक bcm63xx_cb_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			   पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	/* snoop access to slot 0x1e on root bus, we fake a cardbus
	 * bridge at this location */
	अगर (!bus->parent && PCI_SLOT(devfn) == FAKE_CB_BRIDGE_SLOT) अणु
		fake_cb_bridge_bus_number = bus->number;
		वापस fake_cb_bridge_पढ़ो(where, size, val);
	पूर्ण

	/* a  configuration  cycle क्रम	the  device  behind the	 cardbus
	 * bridge is  actually करोne as a  type 0 cycle	on the primary
	 * bus. This means that only  one device can be on the cardbus
	 * bus */
	अगर (fake_cb_bridge_regs.bus_asचिन्हित &&
	    bus->number == fake_cb_bridge_regs.cardbus_busn &&
	    PCI_SLOT(devfn) == 0)
		वापस bcm63xx_करो_cfg_पढ़ो(0, 0,
					   PCI_DEVFN(CARDBUS_PCI_IDSEL, 0),
					   where, size, val);

	वापस PCIBIOS_DEVICE_NOT_FOUND;
पूर्ण

अटल पूर्णांक bcm63xx_cb_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			    पूर्णांक where, पूर्णांक size, u32 val)
अणु
	अगर (!bus->parent && PCI_SLOT(devfn) == FAKE_CB_BRIDGE_SLOT) अणु
		fake_cb_bridge_bus_number = bus->number;
		वापस fake_cb_bridge_ग_लिखो(where, size, val);
	पूर्ण

	अगर (fake_cb_bridge_regs.bus_asचिन्हित &&
	    bus->number == fake_cb_bridge_regs.cardbus_busn &&
	    PCI_SLOT(devfn) == 0)
		वापस bcm63xx_करो_cfg_ग_लिखो(0, 0,
					    PCI_DEVFN(CARDBUS_PCI_IDSEL, 0),
					    where, size, val);

	वापस PCIBIOS_DEVICE_NOT_FOUND;
पूर्ण

काष्ठा pci_ops bcm63xx_cb_ops = अणु
	.पढ़ो	= bcm63xx_cb_पढ़ो,
	.ग_लिखो	 = bcm63xx_cb_ग_लिखो,
पूर्ण;

/*
 * only one IO winकरोw, so it  cannot be shared by PCI and cardbus, use
 * fixup to choose and detect unhandled configuration
 */
अटल व्योम bcm63xx_fixup(काष्ठा pci_dev *dev)
अणु
	अटल पूर्णांक io_winकरोw = -1;
	पूर्णांक i, found, new_io_winकरोw;
	u32 val;

	/* look क्रम any io resource */
	found = 0;
	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		अगर (pci_resource_flags(dev, i) & IORESOURCE_IO) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस;

	/* skip our fake bus with only cardbus bridge on it */
	अगर (dev->bus->number == fake_cb_bridge_bus_number)
		वापस;

	/* find on which bus the device is */
	अगर (fake_cb_bridge_regs.bus_asचिन्हित &&
	    dev->bus->number == fake_cb_bridge_regs.cardbus_busn &&
	    PCI_SLOT(dev->devfn) == 0)
		new_io_winकरोw = 1;
	अन्यथा
		new_io_winकरोw = 0;

	अगर (new_io_winकरोw == io_winकरोw)
		वापस;

	अगर (io_winकरोw != -1) अणु
		prपूर्णांकk(KERN_ERR "bcm63xx: both PCI and cardbus devices "
		       "need IO, which hardware cannot do\n");
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_INFO "bcm63xx: PCI IO window assigned to %s\n",
	       (new_io_winकरोw == 0) ? "PCI" : "cardbus");

	val = bcm_mpi_पढ़ोl(MPI_L2PIOREMAP_REG);
	अगर (io_winकरोw)
		val |= MPI_L2PREMAP_IS_CARDBUS_MASK;
	अन्यथा
		val &= ~MPI_L2PREMAP_IS_CARDBUS_MASK;
	bcm_mpi_ग_लिखोl(val, MPI_L2PIOREMAP_REG);

	io_winकरोw = new_io_winकरोw;
पूर्ण

DECLARE_PCI_FIXUP_ENABLE(PCI_ANY_ID, PCI_ANY_ID, bcm63xx_fixup);
#पूर्ण_अगर

अटल पूर्णांक bcm63xx_pcie_can_access(काष्ठा pci_bus *bus, पूर्णांक devfn)
अणु
	चयन (bus->number) अणु
	हाल PCIE_BUS_BRIDGE:
		वापस PCI_SLOT(devfn) == 0;
	हाल PCIE_BUS_DEVICE:
		अगर (PCI_SLOT(devfn) == 0)
			वापस bcm_pcie_पढ़ोl(PCIE_DLSTATUS_REG)
					& DLSTATUS_PHYLINKUP;
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm63xx_pcie_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			     पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	u32 data;
	u32 reg = where & ~3;

	अगर (!bcm63xx_pcie_can_access(bus, devfn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (bus->number == PCIE_BUS_DEVICE)
		reg += PCIE_DEVICE_OFFSET;

	data = bcm_pcie_पढ़ोl(reg);

	*val = postprocess_पढ़ो(data, where, size);

	वापस PCIBIOS_SUCCESSFUL;

पूर्ण

अटल पूर्णांक bcm63xx_pcie_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			      पूर्णांक where, पूर्णांक size, u32 val)
अणु
	u32 data;
	u32 reg = where & ~3;

	अगर (!bcm63xx_pcie_can_access(bus, devfn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (bus->number == PCIE_BUS_DEVICE)
		reg += PCIE_DEVICE_OFFSET;


	data = bcm_pcie_पढ़ोl(reg);

	data = preprocess_ग_लिखो(data, val, where, size);
	bcm_pcie_ग_लिखोl(data, reg);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण


काष्ठा pci_ops bcm63xx_pcie_ops = अणु
	.पढ़ो	= bcm63xx_pcie_पढ़ो,
	.ग_लिखो	= bcm63xx_pcie_ग_लिखो
पूर्ण;
