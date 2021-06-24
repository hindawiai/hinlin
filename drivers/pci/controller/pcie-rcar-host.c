<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCIe driver क्रम Renesas R-Car SoCs
 *  Copyright (C) 2014-2020 Renesas Electronics Europe Ltd
 *
 * Based on:
 *  arch/sh/drivers/pci/pcie-sh7786.c
 *  arch/sh/drivers/pci/ops-sh7786.c
 *  Copyright (C) 2009 - 2011  Paul Mundt
 *
 * Author: Phil Edworthy <phil.edworthy@renesas.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>

#समावेश "pcie-rcar.h"

काष्ठा rcar_msi अणु
	DECLARE_BITMAP(used, INT_PCI_MSI_NR);
	काष्ठा irq_करोमुख्य *करोमुख्य;
	काष्ठा mutex map_lock;
	spinlock_t mask_lock;
	पूर्णांक irq1;
	पूर्णांक irq2;
पूर्ण;

/* Structure representing the PCIe पूर्णांकerface */
काष्ठा rcar_pcie_host अणु
	काष्ठा rcar_pcie	pcie;
	काष्ठा phy		*phy;
	काष्ठा clk		*bus_clk;
	काष्ठा			rcar_msi msi;
	पूर्णांक			(*phy_init_fn)(काष्ठा rcar_pcie_host *host);
पूर्ण;

अटल काष्ठा rcar_pcie_host *msi_to_host(काष्ठा rcar_msi *msi)
अणु
	वापस container_of(msi, काष्ठा rcar_pcie_host, msi);
पूर्ण

अटल u32 rcar_पढ़ो_conf(काष्ठा rcar_pcie *pcie, पूर्णांक where)
अणु
	अचिन्हित पूर्णांक shअगरt = BITS_PER_BYTE * (where & 3);
	u32 val = rcar_pci_पढ़ो_reg(pcie, where & ~3);

	वापस val >> shअगरt;
पूर्ण

/* Serialization is provided by 'pci_lock' in drivers/pci/access.c */
अटल पूर्णांक rcar_pcie_config_access(काष्ठा rcar_pcie_host *host,
		अचिन्हित अक्षर access_type, काष्ठा pci_bus *bus,
		अचिन्हित पूर्णांक devfn, पूर्णांक where, u32 *data)
अणु
	काष्ठा rcar_pcie *pcie = &host->pcie;
	अचिन्हित पूर्णांक dev, func, reg, index;

	dev = PCI_SLOT(devfn);
	func = PCI_FUNC(devfn);
	reg = where & ~3;
	index = reg / 4;

	/*
	 * While each channel has its own memory-mapped extended config
	 * space, it's generally only accessible when in endpoपूर्णांक mode.
	 * When in root complex mode, the controller is unable to target
	 * itself with either type 0 or type 1 accesses, and indeed, any
	 * controller initiated target transfer to its own config space
	 * result in a completer पात.
	 *
	 * Each channel effectively only supports a single device, but as
	 * the same channel <-> device access works क्रम any PCI_SLOT()
	 * value, we cheat a bit here and bind the controller's config
	 * space to devfn 0 in order to enable self-क्रमागतeration. In this
	 * हाल the regular ECAR/ECDR path is sidelined and the mangled
	 * config access itself is initiated as an पूर्णांकernal bus transaction.
	 */
	अगर (pci_is_root_bus(bus)) अणु
		अगर (dev != 0)
			वापस PCIBIOS_DEVICE_NOT_FOUND;

		अगर (access_type == RCAR_PCI_ACCESS_READ)
			*data = rcar_pci_पढ़ो_reg(pcie, PCICONF(index));
		अन्यथा
			rcar_pci_ग_लिखो_reg(pcie, *data, PCICONF(index));

		वापस PCIBIOS_SUCCESSFUL;
	पूर्ण

	/* Clear errors */
	rcar_pci_ग_लिखो_reg(pcie, rcar_pci_पढ़ो_reg(pcie, PCIEERRFR), PCIEERRFR);

	/* Set the PIO address */
	rcar_pci_ग_लिखो_reg(pcie, PCIE_CONF_BUS(bus->number) |
		PCIE_CONF_DEV(dev) | PCIE_CONF_FUNC(func) | reg, PCIECAR);

	/* Enable the configuration access */
	अगर (pci_is_root_bus(bus->parent))
		rcar_pci_ग_लिखो_reg(pcie, CONFIG_SEND_ENABLE | TYPE0, PCIECCTLR);
	अन्यथा
		rcar_pci_ग_लिखो_reg(pcie, CONFIG_SEND_ENABLE | TYPE1, PCIECCTLR);

	/* Check क्रम errors */
	अगर (rcar_pci_पढ़ो_reg(pcie, PCIEERRFR) & UNSUPPORTED_REQUEST)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	/* Check क्रम master and target पातs */
	अगर (rcar_पढ़ो_conf(pcie, RCONF(PCI_STATUS)) &
		(PCI_STATUS_REC_MASTER_ABORT | PCI_STATUS_REC_TARGET_ABORT))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (access_type == RCAR_PCI_ACCESS_READ)
		*data = rcar_pci_पढ़ो_reg(pcie, PCIECDR);
	अन्यथा
		rcar_pci_ग_लिखो_reg(pcie, *data, PCIECDR);

	/* Disable the configuration access */
	rcar_pci_ग_लिखो_reg(pcie, 0, PCIECCTLR);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक rcar_pcie_पढ़ो_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
			       पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा rcar_pcie_host *host = bus->sysdata;
	पूर्णांक ret;

	ret = rcar_pcie_config_access(host, RCAR_PCI_ACCESS_READ,
				      bus, devfn, where, val);
	अगर (ret != PCIBIOS_SUCCESSFUL) अणु
		*val = 0xffffffff;
		वापस ret;
	पूर्ण

	अगर (size == 1)
		*val = (*val >> (BITS_PER_BYTE * (where & 3))) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (*val >> (BITS_PER_BYTE * (where & 2))) & 0xffff;

	dev_dbg(&bus->dev, "pcie-config-read: bus=%3d devfn=0x%04x where=0x%04x size=%d val=0x%08x\n",
		bus->number, devfn, where, size, *val);

	वापस ret;
पूर्ण

/* Serialization is provided by 'pci_lock' in drivers/pci/access.c */
अटल पूर्णांक rcar_pcie_ग_लिखो_conf(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा rcar_pcie_host *host = bus->sysdata;
	अचिन्हित पूर्णांक shअगरt;
	u32 data;
	पूर्णांक ret;

	ret = rcar_pcie_config_access(host, RCAR_PCI_ACCESS_READ,
				      bus, devfn, where, &data);
	अगर (ret != PCIBIOS_SUCCESSFUL)
		वापस ret;

	dev_dbg(&bus->dev, "pcie-config-write: bus=%3d devfn=0x%04x where=0x%04x size=%d val=0x%08x\n",
		bus->number, devfn, where, size, val);

	अगर (size == 1) अणु
		shअगरt = BITS_PER_BYTE * (where & 3);
		data &= ~(0xff << shअगरt);
		data |= ((val & 0xff) << shअगरt);
	पूर्ण अन्यथा अगर (size == 2) अणु
		shअगरt = BITS_PER_BYTE * (where & 2);
		data &= ~(0xffff << shअगरt);
		data |= ((val & 0xffff) << shअगरt);
	पूर्ण अन्यथा
		data = val;

	ret = rcar_pcie_config_access(host, RCAR_PCI_ACCESS_WRITE,
				      bus, devfn, where, &data);

	वापस ret;
पूर्ण

अटल काष्ठा pci_ops rcar_pcie_ops = अणु
	.पढ़ो	= rcar_pcie_पढ़ो_conf,
	.ग_लिखो	= rcar_pcie_ग_लिखो_conf,
पूर्ण;

अटल व्योम rcar_pcie_क्रमce_speedup(काष्ठा rcar_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	अचिन्हित पूर्णांक समयout = 1000;
	u32 macsr;

	अगर ((rcar_pci_पढ़ो_reg(pcie, MACS2R) & LINK_SPEED) != LINK_SPEED_5_0GTS)
		वापस;

	अगर (rcar_pci_पढ़ो_reg(pcie, MACCTLR) & SPEED_CHANGE) अणु
		dev_err(dev, "Speed change already in progress\n");
		वापस;
	पूर्ण

	macsr = rcar_pci_पढ़ो_reg(pcie, MACSR);
	अगर ((macsr & LINK_SPEED) == LINK_SPEED_5_0GTS)
		जाओ करोne;

	/* Set target link speed to 5.0 GT/s */
	rcar_rmw32(pcie, EXPCAP(12), PCI_EXP_LNKSTA_CLS,
		   PCI_EXP_LNKSTA_CLS_5_0GB);

	/* Set speed change reason as पूर्णांकentional factor */
	rcar_rmw32(pcie, MACCGSPSETR, SPCNGRSN, 0);

	/* Clear SPCHGFIN, SPCHGSUC, and SPCHGFAIL */
	अगर (macsr & (SPCHGFIN | SPCHGSUC | SPCHGFAIL))
		rcar_pci_ग_लिखो_reg(pcie, macsr, MACSR);

	/* Start link speed change */
	rcar_rmw32(pcie, MACCTLR, SPEED_CHANGE, SPEED_CHANGE);

	जबतक (समयout--) अणु
		macsr = rcar_pci_पढ़ो_reg(pcie, MACSR);
		अगर (macsr & SPCHGFIN) अणु
			/* Clear the पूर्णांकerrupt bits */
			rcar_pci_ग_लिखो_reg(pcie, macsr, MACSR);

			अगर (macsr & SPCHGFAIL)
				dev_err(dev, "Speed change failed\n");

			जाओ करोne;
		पूर्ण

		msleep(1);
	पूर्ण

	dev_err(dev, "Speed change timed out\n");

करोne:
	dev_info(dev, "Current link speed is %s GT/s\n",
		 (macsr & LINK_SPEED) == LINK_SPEED_5_0GTS ? "5" : "2.5");
पूर्ण

अटल व्योम rcar_pcie_hw_enable(काष्ठा rcar_pcie_host *host)
अणु
	काष्ठा rcar_pcie *pcie = &host->pcie;
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(host);
	काष्ठा resource_entry *win;
	LIST_HEAD(res);
	पूर्णांक i = 0;

	/* Try setting 5 GT/s link speed */
	rcar_pcie_क्रमce_speedup(pcie);

	/* Setup PCI resources */
	resource_list_क्रम_each_entry(win, &bridge->winकरोws) अणु
		काष्ठा resource *res = win->res;

		अगर (!res->flags)
			जारी;

		चयन (resource_type(res)) अणु
		हाल IORESOURCE_IO:
		हाल IORESOURCE_MEM:
			rcar_pcie_set_outbound(pcie, i, win);
			i++;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rcar_pcie_enable(काष्ठा rcar_pcie_host *host)
अणु
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(host);

	rcar_pcie_hw_enable(host);

	pci_add_flags(PCI_REASSIGN_ALL_BUS);

	bridge->sysdata = host;
	bridge->ops = &rcar_pcie_ops;

	वापस pci_host_probe(bridge);
पूर्ण

अटल पूर्णांक phy_रुको_क्रम_ack(काष्ठा rcar_pcie *pcie)
अणु
	काष्ठा device *dev = pcie->dev;
	अचिन्हित पूर्णांक समयout = 100;

	जबतक (समयout--) अणु
		अगर (rcar_pci_पढ़ो_reg(pcie, H1_PCIEPHYADRR) & PHY_ACK)
			वापस 0;

		udelay(100);
	पूर्ण

	dev_err(dev, "Access to PCIe phy timed out\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम phy_ग_लिखो_reg(काष्ठा rcar_pcie *pcie,
			  अचिन्हित पूर्णांक rate, u32 addr,
			  अचिन्हित पूर्णांक lane, u32 data)
अणु
	u32 phyaddr;

	phyaddr = WRITE_CMD |
		((rate & 1) << RATE_POS) |
		((lane & 0xf) << LANE_POS) |
		((addr & 0xff) << ADR_POS);

	/* Set ग_लिखो data */
	rcar_pci_ग_लिखो_reg(pcie, data, H1_PCIEPHYDOUTR);
	rcar_pci_ग_लिखो_reg(pcie, phyaddr, H1_PCIEPHYADRR);

	/* Ignore errors as they will be dealt with अगर the data link is करोwn */
	phy_रुको_क्रम_ack(pcie);

	/* Clear command */
	rcar_pci_ग_लिखो_reg(pcie, 0, H1_PCIEPHYDOUTR);
	rcar_pci_ग_लिखो_reg(pcie, 0, H1_PCIEPHYADRR);

	/* Ignore errors as they will be dealt with अगर the data link is करोwn */
	phy_रुको_क्रम_ack(pcie);
पूर्ण

अटल पूर्णांक rcar_pcie_hw_init(काष्ठा rcar_pcie *pcie)
अणु
	पूर्णांक err;

	/* Begin initialization */
	rcar_pci_ग_लिखो_reg(pcie, 0, PCIETCTLR);

	/* Set mode */
	rcar_pci_ग_लिखो_reg(pcie, 1, PCIEMSR);

	err = rcar_pcie_रुको_क्रम_phyrdy(pcie);
	अगर (err)
		वापस err;

	/*
	 * Initial header क्रम port config space is type 1, set the device
	 * class to match. Hardware takes care of propagating the IDSETR
	 * settings, so there is no need to bother with a quirk.
	 */
	rcar_pci_ग_लिखो_reg(pcie, PCI_CLASS_BRIDGE_PCI << 16, IDSETR1);

	/*
	 * Setup Secondary Bus Number & Subordinate Bus Number, even though
	 * they aren't used, to aव्योम bridge being detected as broken.
	 */
	rcar_rmw32(pcie, RCONF(PCI_SECONDARY_BUS), 0xff, 1);
	rcar_rmw32(pcie, RCONF(PCI_SUBORDINATE_BUS), 0xff, 1);

	/* Initialize शेष capabilities. */
	rcar_rmw32(pcie, REXPCAP(0), 0xff, PCI_CAP_ID_EXP);
	rcar_rmw32(pcie, REXPCAP(PCI_EXP_FLAGS),
		PCI_EXP_FLAGS_TYPE, PCI_EXP_TYPE_ROOT_PORT << 4);
	rcar_rmw32(pcie, RCONF(PCI_HEADER_TYPE), 0x7f,
		PCI_HEADER_TYPE_BRIDGE);

	/* Enable data link layer active state reporting */
	rcar_rmw32(pcie, REXPCAP(PCI_EXP_LNKCAP), PCI_EXP_LNKCAP_DLLLARC,
		PCI_EXP_LNKCAP_DLLLARC);

	/* Write out the physical slot number = 0 */
	rcar_rmw32(pcie, REXPCAP(PCI_EXP_SLTCAP), PCI_EXP_SLTCAP_PSN, 0);

	/* Set the completion समयr समयout to the maximum 50ms. */
	rcar_rmw32(pcie, TLCTLR + 1, 0x3f, 50);

	/* Terminate list of capabilities (Next Capability Offset=0) */
	rcar_rmw32(pcie, RVCCAP(0), 0xfff00000, 0);

	/* Enable MSI */
	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		rcar_pci_ग_लिखो_reg(pcie, 0x801f0000, PCIEMSITXR);

	rcar_pci_ग_लिखो_reg(pcie, MACCTLR_INIT_VAL, MACCTLR);

	/* Finish initialization - establish a PCI Express link */
	rcar_pci_ग_लिखो_reg(pcie, CFINIT, PCIETCTLR);

	/* This will समयout अगर we करोn't have a link. */
	err = rcar_pcie_रुको_क्रम_dl(pcie);
	अगर (err)
		वापस err;

	/* Enable INTx पूर्णांकerrupts */
	rcar_rmw32(pcie, PCIEINTXR, 0, 0xF << 8);

	wmb();

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_phy_init_h1(काष्ठा rcar_pcie_host *host)
अणु
	काष्ठा rcar_pcie *pcie = &host->pcie;

	/* Initialize the phy */
	phy_ग_लिखो_reg(pcie, 0, 0x42, 0x1, 0x0EC34191);
	phy_ग_लिखो_reg(pcie, 1, 0x42, 0x1, 0x0EC34180);
	phy_ग_लिखो_reg(pcie, 0, 0x43, 0x1, 0x00210188);
	phy_ग_लिखो_reg(pcie, 1, 0x43, 0x1, 0x00210188);
	phy_ग_लिखो_reg(pcie, 0, 0x44, 0x1, 0x015C0014);
	phy_ग_लिखो_reg(pcie, 1, 0x44, 0x1, 0x015C0014);
	phy_ग_लिखो_reg(pcie, 1, 0x4C, 0x1, 0x786174A0);
	phy_ग_लिखो_reg(pcie, 1, 0x4D, 0x1, 0x048000BB);
	phy_ग_लिखो_reg(pcie, 0, 0x51, 0x1, 0x079EC062);
	phy_ग_लिखो_reg(pcie, 0, 0x52, 0x1, 0x20000000);
	phy_ग_लिखो_reg(pcie, 1, 0x52, 0x1, 0x20000000);
	phy_ग_लिखो_reg(pcie, 1, 0x56, 0x1, 0x00003806);

	phy_ग_लिखो_reg(pcie, 0, 0x60, 0x1, 0x004B03A5);
	phy_ग_लिखो_reg(pcie, 0, 0x64, 0x1, 0x3F0F1F0F);
	phy_ग_लिखो_reg(pcie, 0, 0x66, 0x1, 0x00008000);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_phy_init_gen2(काष्ठा rcar_pcie_host *host)
अणु
	काष्ठा rcar_pcie *pcie = &host->pcie;

	/*
	 * These settings come from the R-Car Series, 2nd Generation User's
	 * Manual, section 50.3.1 (2) Initialization of the physical layer.
	 */
	rcar_pci_ग_लिखो_reg(pcie, 0x000f0030, GEN2_PCIEPHYADDR);
	rcar_pci_ग_लिखो_reg(pcie, 0x00381203, GEN2_PCIEPHYDATA);
	rcar_pci_ग_लिखो_reg(pcie, 0x00000001, GEN2_PCIEPHYCTRL);
	rcar_pci_ग_लिखो_reg(pcie, 0x00000006, GEN2_PCIEPHYCTRL);

	rcar_pci_ग_लिखो_reg(pcie, 0x000f0054, GEN2_PCIEPHYADDR);
	/* The following value is क्रम DC connection, no termination resistor */
	rcar_pci_ग_लिखो_reg(pcie, 0x13802007, GEN2_PCIEPHYDATA);
	rcar_pci_ग_लिखो_reg(pcie, 0x00000001, GEN2_PCIEPHYCTRL);
	rcar_pci_ग_लिखो_reg(pcie, 0x00000006, GEN2_PCIEPHYCTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_phy_init_gen3(काष्ठा rcar_pcie_host *host)
अणु
	पूर्णांक err;

	err = phy_init(host->phy);
	अगर (err)
		वापस err;

	err = phy_घातer_on(host->phy);
	अगर (err)
		phy_निकास(host->phy);

	वापस err;
पूर्ण

अटल irqवापस_t rcar_pcie_msi_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rcar_pcie_host *host = data;
	काष्ठा rcar_pcie *pcie = &host->pcie;
	काष्ठा rcar_msi *msi = &host->msi;
	काष्ठा device *dev = pcie->dev;
	अचिन्हित दीर्घ reg;

	reg = rcar_pci_पढ़ो_reg(pcie, PCIEMSIFR);

	/* MSI & INTx share an पूर्णांकerrupt - we only handle MSI here */
	अगर (!reg)
		वापस IRQ_NONE;

	जबतक (reg) अणु
		अचिन्हित पूर्णांक index = find_first_bit(&reg, 32);
		अचिन्हित पूर्णांक msi_irq;

		msi_irq = irq_find_mapping(msi->करोमुख्य->parent, index);
		अगर (msi_irq) अणु
			generic_handle_irq(msi_irq);
		पूर्ण अन्यथा अणु
			/* Unknown MSI, just clear it */
			dev_dbg(dev, "unexpected MSI\n");
			rcar_pci_ग_लिखो_reg(pcie, BIT(index), PCIEMSIFR);
		पूर्ण

		/* see अगर there's any more pending in this vector */
		reg = rcar_pci_पढ़ो_reg(pcie, PCIEMSIFR);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम rcar_msi_top_irq_ack(काष्ठा irq_data *d)
अणु
	irq_chip_ack_parent(d);
पूर्ण

अटल व्योम rcar_msi_top_irq_mask(काष्ठा irq_data *d)
अणु
	pci_msi_mask_irq(d);
	irq_chip_mask_parent(d);
पूर्ण

अटल व्योम rcar_msi_top_irq_unmask(काष्ठा irq_data *d)
अणु
	pci_msi_unmask_irq(d);
	irq_chip_unmask_parent(d);
पूर्ण

अटल काष्ठा irq_chip rcar_msi_top_chip = अणु
	.name		= "PCIe MSI",
	.irq_ack	= rcar_msi_top_irq_ack,
	.irq_mask	= rcar_msi_top_irq_mask,
	.irq_unmask	= rcar_msi_top_irq_unmask,
पूर्ण;

अटल व्योम rcar_msi_irq_ack(काष्ठा irq_data *d)
अणु
	काष्ठा rcar_msi *msi = irq_data_get_irq_chip_data(d);
	काष्ठा rcar_pcie *pcie = &msi_to_host(msi)->pcie;

	/* clear the पूर्णांकerrupt */
	rcar_pci_ग_लिखो_reg(pcie, BIT(d->hwirq), PCIEMSIFR);
पूर्ण

अटल व्योम rcar_msi_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा rcar_msi *msi = irq_data_get_irq_chip_data(d);
	काष्ठा rcar_pcie *pcie = &msi_to_host(msi)->pcie;
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&msi->mask_lock, flags);
	value = rcar_pci_पढ़ो_reg(pcie, PCIEMSIIER);
	value &= ~BIT(d->hwirq);
	rcar_pci_ग_लिखो_reg(pcie, value, PCIEMSIIER);
	spin_unlock_irqrestore(&msi->mask_lock, flags);
पूर्ण

अटल व्योम rcar_msi_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा rcar_msi *msi = irq_data_get_irq_chip_data(d);
	काष्ठा rcar_pcie *pcie = &msi_to_host(msi)->pcie;
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&msi->mask_lock, flags);
	value = rcar_pci_पढ़ो_reg(pcie, PCIEMSIIER);
	value |= BIT(d->hwirq);
	rcar_pci_ग_लिखो_reg(pcie, value, PCIEMSIIER);
	spin_unlock_irqrestore(&msi->mask_lock, flags);
पूर्ण

अटल पूर्णांक rcar_msi_set_affinity(काष्ठा irq_data *d, स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम rcar_compose_msi_msg(काष्ठा irq_data *data, काष्ठा msi_msg *msg)
अणु
	काष्ठा rcar_msi *msi = irq_data_get_irq_chip_data(data);
	काष्ठा rcar_pcie *pcie = &msi_to_host(msi)->pcie;

	msg->address_lo = rcar_pci_पढ़ो_reg(pcie, PCIEMSIALR) & ~MSIFE;
	msg->address_hi = rcar_pci_पढ़ो_reg(pcie, PCIEMSIAUR);
	msg->data = data->hwirq;
पूर्ण

अटल काष्ठा irq_chip rcar_msi_bottom_chip = अणु
	.name			= "Rcar MSI",
	.irq_ack		= rcar_msi_irq_ack,
	.irq_mask		= rcar_msi_irq_mask,
	.irq_unmask		= rcar_msi_irq_unmask,
	.irq_set_affinity 	= rcar_msi_set_affinity,
	.irq_compose_msi_msg	= rcar_compose_msi_msg,
पूर्ण;

अटल पूर्णांक rcar_msi_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा rcar_msi *msi = करोमुख्य->host_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक hwirq;

	mutex_lock(&msi->map_lock);

	hwirq = biपंचांगap_find_मुक्त_region(msi->used, INT_PCI_MSI_NR, order_base_2(nr_irqs));

	mutex_unlock(&msi->map_lock);

	अगर (hwirq < 0)
		वापस -ENOSPC;

	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, hwirq + i,
				    &rcar_msi_bottom_chip, करोमुख्य->host_data,
				    handle_edge_irq, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल व्योम rcar_msi_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक virq,
				  अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा rcar_msi *msi = करोमुख्य->host_data;

	mutex_lock(&msi->map_lock);

	biपंचांगap_release_region(msi->used, d->hwirq, order_base_2(nr_irqs));

	mutex_unlock(&msi->map_lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops rcar_msi_करोमुख्य_ops = अणु
	.alloc	= rcar_msi_करोमुख्य_alloc,
	.मुक्त	= rcar_msi_करोमुख्य_मुक्त,
पूर्ण;

अटल काष्ठा msi_करोमुख्य_info rcar_msi_info = अणु
	.flags	= (MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		   MSI_FLAG_MULTI_PCI_MSI),
	.chip	= &rcar_msi_top_chip,
पूर्ण;

अटल पूर्णांक rcar_allocate_करोमुख्यs(काष्ठा rcar_msi *msi)
अणु
	काष्ठा rcar_pcie *pcie = &msi_to_host(msi)->pcie;
	काष्ठा fwnode_handle *fwnode = dev_fwnode(pcie->dev);
	काष्ठा irq_करोमुख्य *parent;

	parent = irq_करोमुख्य_create_linear(fwnode, INT_PCI_MSI_NR,
					  &rcar_msi_करोमुख्य_ops, msi);
	अगर (!parent) अणु
		dev_err(pcie->dev, "failed to create IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण
	irq_करोमुख्य_update_bus_token(parent, DOMAIN_BUS_NEXUS);

	msi->करोमुख्य = pci_msi_create_irq_करोमुख्य(fwnode, &rcar_msi_info, parent);
	अगर (!msi->करोमुख्य) अणु
		dev_err(pcie->dev, "failed to create MSI domain\n");
		irq_करोमुख्य_हटाओ(parent);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rcar_मुक्त_करोमुख्यs(काष्ठा rcar_msi *msi)
अणु
	काष्ठा irq_करोमुख्य *parent = msi->करोमुख्य->parent;

	irq_करोमुख्य_हटाओ(msi->करोमुख्य);
	irq_करोमुख्य_हटाओ(parent);
पूर्ण

अटल पूर्णांक rcar_pcie_enable_msi(काष्ठा rcar_pcie_host *host)
अणु
	काष्ठा rcar_pcie *pcie = &host->pcie;
	काष्ठा device *dev = pcie->dev;
	काष्ठा rcar_msi *msi = &host->msi;
	काष्ठा resource res;
	पूर्णांक err;

	mutex_init(&msi->map_lock);
	spin_lock_init(&msi->mask_lock);

	err = of_address_to_resource(dev->of_node, 0, &res);
	अगर (err)
		वापस err;

	err = rcar_allocate_करोमुख्यs(msi);
	अगर (err)
		वापस err;

	/* Two irqs are क्रम MSI, but they are also used क्रम non-MSI irqs */
	err = devm_request_irq(dev, msi->irq1, rcar_pcie_msi_irq,
			       IRQF_SHARED | IRQF_NO_THREAD,
			       rcar_msi_bottom_chip.name, host);
	अगर (err < 0) अणु
		dev_err(dev, "failed to request IRQ: %d\n", err);
		जाओ err;
	पूर्ण

	err = devm_request_irq(dev, msi->irq2, rcar_pcie_msi_irq,
			       IRQF_SHARED | IRQF_NO_THREAD,
			       rcar_msi_bottom_chip.name, host);
	अगर (err < 0) अणु
		dev_err(dev, "failed to request IRQ: %d\n", err);
		जाओ err;
	पूर्ण

	/* disable all MSIs */
	rcar_pci_ग_लिखो_reg(pcie, 0, PCIEMSIIER);

	/*
	 * Setup MSI data target using RC base address address, which
	 * is guaranteed to be in the low 32bit range on any RCar HW.
	 */
	rcar_pci_ग_लिखो_reg(pcie, lower_32_bits(res.start) | MSIFE, PCIEMSIALR);
	rcar_pci_ग_लिखो_reg(pcie, upper_32_bits(res.start), PCIEMSIAUR);

	वापस 0;

err:
	rcar_मुक्त_करोमुख्यs(msi);
	वापस err;
पूर्ण

अटल व्योम rcar_pcie_tearकरोwn_msi(काष्ठा rcar_pcie_host *host)
अणु
	काष्ठा rcar_pcie *pcie = &host->pcie;

	/* Disable all MSI पूर्णांकerrupts */
	rcar_pci_ग_लिखो_reg(pcie, 0, PCIEMSIIER);

	/* Disable address decoding of the MSI पूर्णांकerrupt, MSIFE */
	rcar_pci_ग_लिखो_reg(pcie, 0, PCIEMSIALR);

	rcar_मुक्त_करोमुख्यs(&host->msi);
पूर्ण

अटल पूर्णांक rcar_pcie_get_resources(काष्ठा rcar_pcie_host *host)
अणु
	काष्ठा rcar_pcie *pcie = &host->pcie;
	काष्ठा device *dev = pcie->dev;
	काष्ठा resource res;
	पूर्णांक err, i;

	host->phy = devm_phy_optional_get(dev, "pcie");
	अगर (IS_ERR(host->phy))
		वापस PTR_ERR(host->phy);

	err = of_address_to_resource(dev->of_node, 0, &res);
	अगर (err)
		वापस err;

	pcie->base = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(pcie->base))
		वापस PTR_ERR(pcie->base);

	host->bus_clk = devm_clk_get(dev, "pcie_bus");
	अगर (IS_ERR(host->bus_clk)) अणु
		dev_err(dev, "cannot get pcie bus clock\n");
		वापस PTR_ERR(host->bus_clk);
	पूर्ण

	i = irq_of_parse_and_map(dev->of_node, 0);
	अगर (!i) अणु
		dev_err(dev, "cannot get platform resources for msi interrupt\n");
		err = -ENOENT;
		जाओ err_irq1;
	पूर्ण
	host->msi.irq1 = i;

	i = irq_of_parse_and_map(dev->of_node, 1);
	अगर (!i) अणु
		dev_err(dev, "cannot get platform resources for msi interrupt\n");
		err = -ENOENT;
		जाओ err_irq2;
	पूर्ण
	host->msi.irq2 = i;

	वापस 0;

err_irq2:
	irq_dispose_mapping(host->msi.irq1);
err_irq1:
	वापस err;
पूर्ण

अटल पूर्णांक rcar_pcie_inbound_ranges(काष्ठा rcar_pcie *pcie,
				    काष्ठा resource_entry *entry,
				    पूर्णांक *index)
अणु
	u64 restype = entry->res->flags;
	u64 cpu_addr = entry->res->start;
	u64 cpu_end = entry->res->end;
	u64 pci_addr = entry->res->start - entry->offset;
	u32 flags = LAM_64BIT | LAR_ENABLE;
	u64 mask;
	u64 size = resource_size(entry->res);
	पूर्णांक idx = *index;

	अगर (restype & IORESOURCE_PREFETCH)
		flags |= LAM_PREFETCH;

	जबतक (cpu_addr < cpu_end) अणु
		अगर (idx >= MAX_NR_INBOUND_MAPS - 1) अणु
			dev_err(pcie->dev, "Failed to map inbound regions!\n");
			वापस -EINVAL;
		पूर्ण
		/*
		 * If the size of the range is larger than the alignment of
		 * the start address, we have to use multiple entries to
		 * perक्रमm the mapping.
		 */
		अगर (cpu_addr > 0) अणु
			अचिन्हित दीर्घ nr_zeros = __ffs64(cpu_addr);
			u64 alignment = 1ULL << nr_zeros;

			size = min(size, alignment);
		पूर्ण
		/* Hardware supports max 4GiB inbound region */
		size = min(size, 1ULL << 32);

		mask = roundup_घात_of_two(size) - 1;
		mask &= ~0xf;

		rcar_pcie_set_inbound(pcie, cpu_addr, pci_addr,
				      lower_32_bits(mask) | flags, idx, true);

		pci_addr += size;
		cpu_addr += size;
		idx += 2;
	पूर्ण
	*index = idx;

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_parse_map_dma_ranges(काष्ठा rcar_pcie_host *host)
अणु
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(host);
	काष्ठा resource_entry *entry;
	पूर्णांक index = 0, err = 0;

	resource_list_क्रम_each_entry(entry, &bridge->dma_ranges) अणु
		err = rcar_pcie_inbound_ranges(&host->pcie, entry, &index);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id rcar_pcie_of_match[] = अणु
	अणु .compatible = "renesas,pcie-r8a7779",
	  .data = rcar_pcie_phy_init_h1 पूर्ण,
	अणु .compatible = "renesas,pcie-r8a7790",
	  .data = rcar_pcie_phy_init_gen2 पूर्ण,
	अणु .compatible = "renesas,pcie-r8a7791",
	  .data = rcar_pcie_phy_init_gen2 पूर्ण,
	अणु .compatible = "renesas,pcie-rcar-gen2",
	  .data = rcar_pcie_phy_init_gen2 पूर्ण,
	अणु .compatible = "renesas,pcie-r8a7795",
	  .data = rcar_pcie_phy_init_gen3 पूर्ण,
	अणु .compatible = "renesas,pcie-rcar-gen3",
	  .data = rcar_pcie_phy_init_gen3 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक rcar_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rcar_pcie_host *host;
	काष्ठा rcar_pcie *pcie;
	u32 data;
	पूर्णांक err;
	काष्ठा pci_host_bridge *bridge;

	bridge = devm_pci_alloc_host_bridge(dev, माप(*host));
	अगर (!bridge)
		वापस -ENOMEM;

	host = pci_host_bridge_priv(bridge);
	pcie = &host->pcie;
	pcie->dev = dev;
	platक्रमm_set_drvdata(pdev, host);

	pm_runसमय_enable(pcie->dev);
	err = pm_runसमय_get_sync(pcie->dev);
	अगर (err < 0) अणु
		dev_err(pcie->dev, "pm_runtime_get_sync failed\n");
		जाओ err_pm_put;
	पूर्ण

	err = rcar_pcie_get_resources(host);
	अगर (err < 0) अणु
		dev_err(dev, "failed to request resources: %d\n", err);
		जाओ err_pm_put;
	पूर्ण

	err = clk_prepare_enable(host->bus_clk);
	अगर (err) अणु
		dev_err(dev, "failed to enable bus clock: %d\n", err);
		जाओ err_unmap_msi_irqs;
	पूर्ण

	err = rcar_pcie_parse_map_dma_ranges(host);
	अगर (err)
		जाओ err_clk_disable;

	host->phy_init_fn = of_device_get_match_data(dev);
	err = host->phy_init_fn(host);
	अगर (err) अणु
		dev_err(dev, "failed to init PCIe PHY\n");
		जाओ err_clk_disable;
	पूर्ण

	/* Failure to get a link might just be that no cards are inserted */
	अगर (rcar_pcie_hw_init(pcie)) अणु
		dev_info(dev, "PCIe link down\n");
		err = -ENODEV;
		जाओ err_phy_shutकरोwn;
	पूर्ण

	data = rcar_pci_पढ़ो_reg(pcie, MACSR);
	dev_info(dev, "PCIe x%d: link up\n", (data >> 20) & 0x3f);

	अगर (IS_ENABLED(CONFIG_PCI_MSI)) अणु
		err = rcar_pcie_enable_msi(host);
		अगर (err < 0) अणु
			dev_err(dev,
				"failed to enable MSI support: %d\n",
				err);
			जाओ err_phy_shutकरोwn;
		पूर्ण
	पूर्ण

	err = rcar_pcie_enable(host);
	अगर (err)
		जाओ err_msi_tearकरोwn;

	वापस 0;

err_msi_tearकरोwn:
	अगर (IS_ENABLED(CONFIG_PCI_MSI))
		rcar_pcie_tearकरोwn_msi(host);

err_phy_shutकरोwn:
	अगर (host->phy) अणु
		phy_घातer_off(host->phy);
		phy_निकास(host->phy);
	पूर्ण

err_clk_disable:
	clk_disable_unprepare(host->bus_clk);

err_unmap_msi_irqs:
	irq_dispose_mapping(host->msi.irq2);
	irq_dispose_mapping(host->msi.irq1);

err_pm_put:
	pm_runसमय_put(dev);
	pm_runसमय_disable(dev);

	वापस err;
पूर्ण

अटल पूर्णांक __maybe_unused rcar_pcie_resume(काष्ठा device *dev)
अणु
	काष्ठा rcar_pcie_host *host = dev_get_drvdata(dev);
	काष्ठा rcar_pcie *pcie = &host->pcie;
	अचिन्हित पूर्णांक data;
	पूर्णांक err;

	err = rcar_pcie_parse_map_dma_ranges(host);
	अगर (err)
		वापस 0;

	/* Failure to get a link might just be that no cards are inserted */
	err = host->phy_init_fn(host);
	अगर (err) अणु
		dev_info(dev, "PCIe link down\n");
		वापस 0;
	पूर्ण

	data = rcar_pci_पढ़ो_reg(pcie, MACSR);
	dev_info(dev, "PCIe x%d: link up\n", (data >> 20) & 0x3f);

	/* Enable MSI */
	अगर (IS_ENABLED(CONFIG_PCI_MSI)) अणु
		काष्ठा resource res;
		u32 val;

		of_address_to_resource(dev->of_node, 0, &res);
		rcar_pci_ग_लिखो_reg(pcie, upper_32_bits(res.start), PCIEMSIAUR);
		rcar_pci_ग_लिखो_reg(pcie, lower_32_bits(res.start) | MSIFE, PCIEMSIALR);

		biपंचांगap_to_arr32(&val, host->msi.used, INT_PCI_MSI_NR);
		rcar_pci_ग_लिखो_reg(pcie, val, PCIEMSIIER);
	पूर्ण

	rcar_pcie_hw_enable(host);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pcie_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा rcar_pcie_host *host = dev_get_drvdata(dev);
	काष्ठा rcar_pcie *pcie = &host->pcie;

	अगर (rcar_pci_पढ़ो_reg(pcie, PMSR) &&
	    !(rcar_pci_पढ़ो_reg(pcie, PCIETCTLR) & DL_DOWN))
		वापस 0;

	/* Re-establish the PCIe link */
	rcar_pci_ग_लिखो_reg(pcie, MACCTLR_INIT_VAL, MACCTLR);
	rcar_pci_ग_लिखो_reg(pcie, CFINIT, PCIETCTLR);
	वापस rcar_pcie_रुको_क्रम_dl(pcie);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops rcar_pcie_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(शून्य, rcar_pcie_resume)
	.resume_noirq = rcar_pcie_resume_noirq,
पूर्ण;

अटल काष्ठा platक्रमm_driver rcar_pcie_driver = अणु
	.driver = अणु
		.name = "rcar-pcie",
		.of_match_table = rcar_pcie_of_match,
		.pm = &rcar_pcie_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = rcar_pcie_probe,
पूर्ण;
builtin_platक्रमm_driver(rcar_pcie_driver);
