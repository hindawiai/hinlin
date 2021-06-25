<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Low-Level PCI Express Support क्रम the SH7786
 *
 *  Copyright (C) 2009 - 2011  Paul Mundt
 */
#घोषणा pr_fmt(fmt) "PCI: " fmt

#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/async.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/sh_clk.h>
#समावेश <linux/sh_पूर्णांकc.h>
#समावेश <cpu/sh7786.h>
#समावेश "pcie-sh7786.h"
#समावेश <linux/sizes.h>

काष्ठा sh7786_pcie_port अणु
	काष्ठा pci_channel	*hose;
	काष्ठा clk		*fclk, phy_clk;
	अचिन्हित पूर्णांक		index;
	पूर्णांक			endpoपूर्णांक;
	पूर्णांक			link;
पूर्ण;

अटल काष्ठा sh7786_pcie_port *sh7786_pcie_ports;
अटल अचिन्हित पूर्णांक nr_ports;
अटल अचिन्हित दीर्घ dma_pfn_offset;
माप_प्रकार memsize;
u64 memstart;

अटल काष्ठा sh7786_pcie_hwops अणु
	पूर्णांक (*core_init)(व्योम);
	async_func_t port_init_hw;
पूर्ण *sh7786_pcie_hwops;

अटल काष्ठा resource sh7786_pci0_resources[] = अणु
	अणु
		.name	= "PCIe0 MEM 0",
		.start	= 0xfd000000,
		.end	= 0xfd000000 + SZ_8M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.name	= "PCIe0 MEM 1",
		.start	= 0xc0000000,
		.end	= 0xc0000000 + SZ_512M - 1,
		.flags	= IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
	पूर्ण, अणु
		.name	= "PCIe0 MEM 2",
		.start	= 0x10000000,
		.end	= 0x10000000 + SZ_64M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.name	= "PCIe0 IO",
		.start	= 0xfe100000,
		.end	= 0xfe100000 + SZ_1M - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sh7786_pci1_resources[] = अणु
	अणु
		.name	= "PCIe1 MEM 0",
		.start	= 0xfd800000,
		.end	= 0xfd800000 + SZ_8M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.name	= "PCIe1 MEM 1",
		.start	= 0xa0000000,
		.end	= 0xa0000000 + SZ_512M - 1,
		.flags	= IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
	पूर्ण, अणु
		.name	= "PCIe1 MEM 2",
		.start	= 0x30000000,
		.end	= 0x30000000 + SZ_256M - 1,
		.flags	= IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
	पूर्ण, अणु
		.name	= "PCIe1 IO",
		.start	= 0xfe300000,
		.end	= 0xfe300000 + SZ_1M - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource sh7786_pci2_resources[] = अणु
	अणु
		.name	= "PCIe2 MEM 0",
		.start	= 0xfc800000,
		.end	= 0xfc800000 + SZ_4M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.name	= "PCIe2 MEM 1",
		.start	= 0x80000000,
		.end	= 0x80000000 + SZ_512M - 1,
		.flags	= IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
	पूर्ण, अणु
		.name	= "PCIe2 MEM 2",
		.start	= 0x20000000,
		.end	= 0x20000000 + SZ_256M - 1,
		.flags	= IORESOURCE_MEM | IORESOURCE_MEM_32BIT,
	पूर्ण, अणु
		.name	= "PCIe2 IO",
		.start	= 0xfcd00000,
		.end	= 0xfcd00000 + SZ_1M - 1,
		.flags	= IORESOURCE_IO,
	पूर्ण,
पूर्ण;

बाह्य काष्ठा pci_ops sh7786_pci_ops;

#घोषणा DEFINE_CONTROLLER(start, idx)					\
अणु									\
	.pci_ops	= &sh7786_pci_ops,				\
	.resources	= sh7786_pci##idx##_resources,			\
	.nr_resources	= ARRAY_SIZE(sh7786_pci##idx##_resources),	\
	.reg_base	= start,					\
	.mem_offset	= 0,						\
	.io_offset	= 0,						\
पूर्ण

अटल काष्ठा pci_channel sh7786_pci_channels[] = अणु
	DEFINE_CONTROLLER(0xfe000000, 0),
	DEFINE_CONTROLLER(0xfe200000, 1),
	DEFINE_CONTROLLER(0xfcc00000, 2),
पूर्ण;

अटल काष्ठा clk fixed_pciexclkp = अणु
	.rate = 100000000,	/* 100 MHz reference घड़ी */
पूर्ण;

अटल व्योम sh7786_pci_fixup(काष्ठा pci_dev *dev)
अणु
	/*
	 * Prevent क्रमागतeration of root complex resources.
	 */
	अगर (pci_is_root_bus(dev->bus) && dev->devfn == 0) अणु
		पूर्णांक i;

		क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
			dev->resource[i].start	= 0;
			dev->resource[i].end	= 0;
			dev->resource[i].flags	= 0;
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_RENESAS, PCI_DEVICE_ID_RENESAS_SH7786,
			 sh7786_pci_fixup);

अटल पूर्णांक __init phy_रुको_क्रम_ack(काष्ठा pci_channel *chan)
अणु
	अचिन्हित पूर्णांक समयout = 100;

	जबतक (समयout--) अणु
		अगर (pci_पढ़ो_reg(chan, SH4A_PCIEPHYADRR) & (1 << BITS_ACK))
			वापस 0;

		udelay(100);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक __init pci_रुको_क्रम_irq(काष्ठा pci_channel *chan, अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक समयout = 100;

	जबतक (समयout--) अणु
		अगर ((pci_पढ़ो_reg(chan, SH4A_PCIEINTR) & mask) == mask)
			वापस 0;

		udelay(100);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम __init phy_ग_लिखो_reg(काष्ठा pci_channel *chan, अचिन्हित पूर्णांक addr,
				 अचिन्हित पूर्णांक lane, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित दीर्घ phyaddr;

	phyaddr = (1 << BITS_CMD) + ((lane & 0xf) << BITS_LANE) +
			((addr & 0xff) << BITS_ADR);

	/* Set ग_लिखो data */
	pci_ग_लिखो_reg(chan, data, SH4A_PCIEPHYDOUTR);
	pci_ग_लिखो_reg(chan, phyaddr, SH4A_PCIEPHYADRR);

	phy_रुको_क्रम_ack(chan);

	/* Clear command */
	pci_ग_लिखो_reg(chan, 0, SH4A_PCIEPHYDOUTR);
	pci_ग_लिखो_reg(chan, 0, SH4A_PCIEPHYADRR);

	phy_रुको_क्रम_ack(chan);
पूर्ण

अटल पूर्णांक __init pcie_clk_init(काष्ठा sh7786_pcie_port *port)
अणु
	काष्ठा pci_channel *chan = port->hose;
	काष्ठा clk *clk;
	अक्षर fclk_name[16];
	पूर्णांक ret;

	/*
	 * First रेजिस्टर the fixed घड़ी
	 */
	ret = clk_रेजिस्टर(&fixed_pciexclkp);
	अगर (unlikely(ret != 0))
		वापस ret;

	/*
	 * Grab the port's function घड़ी, which the PHY घड़ी depends
	 * on. घड़ी lookups करोn't help us much at this poपूर्णांक, since no
	 * dev_id is available this early. Lame.
	 */
	snम_लिखो(fclk_name, माप(fclk_name), "pcie%d_fck", port->index);

	port->fclk = clk_get(शून्य, fclk_name);
	अगर (IS_ERR(port->fclk)) अणु
		ret = PTR_ERR(port->fclk);
		जाओ err_fclk;
	पूर्ण

	clk_enable(port->fclk);

	/*
	 * And now, set up the PHY घड़ी
	 */
	clk = &port->phy_clk;

	स_रखो(clk, 0, माप(काष्ठा clk));

	clk->parent = &fixed_pciexclkp;
	clk->enable_reg = (व्योम __iomem *)(chan->reg_base + SH4A_PCIEPHYCTLR);
	clk->enable_bit = BITS_CKE;

	ret = sh_clk_mstp_रेजिस्टर(clk, 1);
	अगर (unlikely(ret < 0))
		जाओ err_phy;

	वापस 0;

err_phy:
	clk_disable(port->fclk);
	clk_put(port->fclk);
err_fclk:
	clk_unरेजिस्टर(&fixed_pciexclkp);

	वापस ret;
पूर्ण

अटल पूर्णांक __init phy_init(काष्ठा sh7786_pcie_port *port)
अणु
	काष्ठा pci_channel *chan = port->hose;
	अचिन्हित पूर्णांक समयout = 100;

	clk_enable(&port->phy_clk);

	/* Initialize the phy */
	phy_ग_लिखो_reg(chan, 0x60, 0xf, 0x004b008b);
	phy_ग_लिखो_reg(chan, 0x61, 0xf, 0x00007b41);
	phy_ग_लिखो_reg(chan, 0x64, 0xf, 0x00ff4f00);
	phy_ग_लिखो_reg(chan, 0x65, 0xf, 0x09070907);
	phy_ग_लिखो_reg(chan, 0x66, 0xf, 0x00000010);
	phy_ग_लिखो_reg(chan, 0x74, 0xf, 0x0007001c);
	phy_ग_लिखो_reg(chan, 0x79, 0xf, 0x01fc000d);
	phy_ग_लिखो_reg(chan, 0xb0, 0xf, 0x00000610);

	/* Deनिश्चित Standby */
	phy_ग_लिखो_reg(chan, 0x67, 0x1, 0x00000400);

	/* Disable घड़ी */
	clk_disable(&port->phy_clk);

	जबतक (समयout--) अणु
		अगर (pci_पढ़ो_reg(chan, SH4A_PCIEPHYSR))
			वापस 0;

		udelay(100);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम __init pcie_reset(काष्ठा sh7786_pcie_port *port)
अणु
	काष्ठा pci_channel *chan = port->hose;

	pci_ग_लिखो_reg(chan, 1, SH4A_PCIESRSTR);
	pci_ग_लिखो_reg(chan, 0, SH4A_PCIETCTLR);
	pci_ग_लिखो_reg(chan, 0, SH4A_PCIESRSTR);
	pci_ग_लिखो_reg(chan, 0, SH4A_PCIETXVC0SR);
पूर्ण

अटल पूर्णांक __init pcie_init(काष्ठा sh7786_pcie_port *port)
अणु
	काष्ठा pci_channel *chan = port->hose;
	अचिन्हित पूर्णांक data;
	phys_addr_t memstart, memend;
	पूर्णांक ret, i, win;

	/* Begin initialization */
	pcie_reset(port);

	/*
	 * Initial header क्रम port config space is type 1, set the device
	 * class to match. Hardware takes care of propagating the IDSETR
	 * settings, so there is no need to bother with a quirk.
	 */
	pci_ग_लिखो_reg(chan, PCI_CLASS_BRIDGE_PCI << 16, SH4A_PCIEIDSETR1);

	/* Initialize शेष capabilities. */
	data = pci_पढ़ो_reg(chan, SH4A_PCIEEXPCAP0);
	data &= ~(PCI_EXP_FLAGS_TYPE << 16);

	अगर (port->endpoपूर्णांक)
		data |= PCI_EXP_TYPE_ENDPOINT << 20;
	अन्यथा
		data |= PCI_EXP_TYPE_ROOT_PORT << 20;

	data |= PCI_CAP_ID_EXP;
	pci_ग_लिखो_reg(chan, data, SH4A_PCIEEXPCAP0);

	/* Enable data link layer active state reporting */
	pci_ग_लिखो_reg(chan, PCI_EXP_LNKCAP_DLLLARC, SH4A_PCIEEXPCAP3);

	/* Enable extended sync and ASPM L0s support */
	data = pci_पढ़ो_reg(chan, SH4A_PCIEEXPCAP4);
	data &= ~PCI_EXP_LNKCTL_ASPMC;
	data |= PCI_EXP_LNKCTL_ES | 1;
	pci_ग_लिखो_reg(chan, data, SH4A_PCIEEXPCAP4);

	/* Write out the physical slot number */
	data = pci_पढ़ो_reg(chan, SH4A_PCIEEXPCAP5);
	data &= ~PCI_EXP_SLTCAP_PSN;
	data |= (port->index + 1) << 19;
	pci_ग_लिखो_reg(chan, data, SH4A_PCIEEXPCAP5);

	/* Set the completion समयr समयout to the maximum 32ms. */
	data = pci_पढ़ो_reg(chan, SH4A_PCIETLCTLR);
	data &= ~0x3f00;
	data |= 0x32 << 8;
	pci_ग_लिखो_reg(chan, data, SH4A_PCIETLCTLR);

	/*
	 * Set fast training sequences to the maximum 255,
	 * and enable MAC data scrambling.
	 */
	data = pci_पढ़ो_reg(chan, SH4A_PCIEMACCTLR);
	data &= ~PCIEMACCTLR_SCR_DIS;
	data |= (0xff << 16);
	pci_ग_लिखो_reg(chan, data, SH4A_PCIEMACCTLR);

	memstart = __pa(memory_start);
	memend   = __pa(memory_end);
	memsize = roundup_घात_of_two(memend - memstart);

	/*
	 * The start address must be aligned on its size. So we round
	 * it करोwn, and then recalculate the size so that it covers
	 * the entire memory.
	 */
	memstart = ALIGN_DOWN(memstart, memsize);
	memsize = roundup_घात_of_two(memend - memstart);

	/*
	 * If there's more than 512MB of memory, we need to roll over to
	 * LAR1/LAMR1.
	 */
	अगर (memsize > SZ_512M) अणु
		pci_ग_लिखो_reg(chan, memstart + SZ_512M, SH4A_PCIELAR1);
		pci_ग_लिखो_reg(chan, ((memsize - SZ_512M) - SZ_256) | 1,
			      SH4A_PCIELAMR1);
		memsize = SZ_512M;
	पूर्ण अन्यथा अणु
		/*
		 * Otherwise just zero it out and disable it.
		 */
		pci_ग_लिखो_reg(chan, 0, SH4A_PCIELAR1);
		pci_ग_लिखो_reg(chan, 0, SH4A_PCIELAMR1);
	पूर्ण

	/*
	 * LAR0/LAMR0 covers up to the first 512MB, which is enough to
	 * cover all of lowmem on most platक्रमms.
	 */
	pci_ग_लिखो_reg(chan, memstart, SH4A_PCIELAR0);
	pci_ग_लिखो_reg(chan, (memsize - SZ_256) | 1, SH4A_PCIELAMR0);

	/* Finish initialization */
	data = pci_पढ़ो_reg(chan, SH4A_PCIETCTLR);
	data |= 0x1;
	pci_ग_लिखो_reg(chan, data, SH4A_PCIETCTLR);

	/* Let things settle करोwn a bit.. */
	mdelay(100);

	/* Enable DL_Active Interrupt generation */
	data = pci_पढ़ो_reg(chan, SH4A_PCIEDLINTENR);
	data |= PCIEDLINTENR_DLL_ACT_ENABLE;
	pci_ग_लिखो_reg(chan, data, SH4A_PCIEDLINTENR);

	/* Disable MAC data scrambling. */
	data = pci_पढ़ो_reg(chan, SH4A_PCIEMACCTLR);
	data |= PCIEMACCTLR_SCR_DIS | (0xff << 16);
	pci_ग_लिखो_reg(chan, data, SH4A_PCIEMACCTLR);

	/*
	 * This will समयout अगर we करोn't have a link, but we permit the
	 * port to रेजिस्टर anyways in order to support hotplug on future
	 * hardware.
	 */
	ret = pci_रुको_क्रम_irq(chan, MASK_INT_TX_CTRL);

	data = pci_पढ़ो_reg(chan, SH4A_PCIEPCICONF1);
	data &= ~(PCI_STATUS_DEVSEL_MASK << 16);
	data |= PCI_COMMAND_IO | PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER |
		(PCI_STATUS_CAP_LIST | PCI_STATUS_DEVSEL_FAST) << 16;
	pci_ग_लिखो_reg(chan, data, SH4A_PCIEPCICONF1);

	pci_ग_लिखो_reg(chan, 0x80888000, SH4A_PCIETXVC0DCTLR);
	pci_ग_लिखो_reg(chan, 0x00222000, SH4A_PCIERXVC0DCTLR);

	wmb();

	अगर (ret == 0) अणु
		data = pci_पढ़ो_reg(chan, SH4A_PCIEMACSR);
		prपूर्णांकk(KERN_NOTICE "PCI: PCIe#%d x%d link detected\n",
		       port->index, (data >> 20) & 0x3f);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_NOTICE "PCI: PCIe#%d link down\n",
		       port->index);

	क्रम (i = win = 0; i < chan->nr_resources; i++) अणु
		काष्ठा resource *res = chan->resources + i;
		resource_माप_प्रकार size;
		u32 mask;

		/*
		 * We can't use the 32-bit mode winकरोws in legacy 29-bit
		 * mode, so just skip them entirely.
		 */
		अगर ((res->flags & IORESOURCE_MEM_32BIT) && __in_29bit_mode())
			res->flags |= IORESOURCE_DISABLED;

		अगर (res->flags & IORESOURCE_DISABLED)
			जारी;

		pci_ग_लिखो_reg(chan, 0x00000000, SH4A_PCIEPTCTLR(win));

		/*
		 * The PAMR mask is calculated in units of 256kB, which
		 * keeps things pretty simple.
		 */
		size = resource_size(res);
		mask = (roundup_घात_of_two(size) / SZ_256K) - 1;
		pci_ग_लिखो_reg(chan, mask << 18, SH4A_PCIEPAMR(win));

		pci_ग_लिखो_reg(chan, upper_32_bits(res->start),
			      SH4A_PCIEPARH(win));
		pci_ग_लिखो_reg(chan, lower_32_bits(res->start),
			      SH4A_PCIEPARL(win));

		mask = MASK_PARE;
		अगर (res->flags & IORESOURCE_IO)
			mask |= MASK_SPC;

		pci_ग_लिखो_reg(chan, mask, SH4A_PCIEPTCTLR(win));

		win++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pcibios_map_platक्रमm_irq(स्थिर काष्ठा pci_dev *pdev, u8 slot, u8 pin)
अणु
        वापस evt2irq(0xae0);
पूर्ण

व्योम pcibios_bus_add_device(काष्ठा pci_dev *pdev)
अणु
	dma_direct_set_offset(&pdev->dev, __pa(memory_start),
			      __pa(memory_start) - memstart, memsize);
पूर्ण

अटल पूर्णांक __init sh7786_pcie_core_init(व्योम)
अणु
	/* Return the number of ports */
	वापस test_mode_pin(MODE_PIN12) ? 3 : 2;
पूर्ण

अटल व्योम __init sh7786_pcie_init_hw(व्योम *data, async_cookie_t cookie)
अणु
	काष्ठा sh7786_pcie_port *port = data;
	पूर्णांक ret;

	/*
	 * Check अगर we are configured in endpoपूर्णांक or root complex mode,
	 * this is a fixed pin setting that applies to all PCIe ports.
	 */
	port->endpoपूर्णांक = test_mode_pin(MODE_PIN11);

	/*
	 * Setup घड़ीs, needed both क्रम PHY and PCIe रेजिस्टरs.
	 */
	ret = pcie_clk_init(port);
	अगर (unlikely(ret < 0)) अणु
		pr_err("clock initialization failed for port#%d\n",
		       port->index);
		वापस;
	पूर्ण

	ret = phy_init(port);
	अगर (unlikely(ret < 0)) अणु
		pr_err("phy initialization failed for port#%d\n",
		       port->index);
		वापस;
	पूर्ण

	ret = pcie_init(port);
	अगर (unlikely(ret < 0)) अणु
		pr_err("core initialization failed for port#%d\n",
			       port->index);
		वापस;
	पूर्ण

	/* In the पूर्णांकerest of preserving device ordering, synchronize */
	async_synchronize_cookie(cookie);

	रेजिस्टर_pci_controller(port->hose);
पूर्ण

अटल काष्ठा sh7786_pcie_hwops sh7786_65nm_pcie_hwops __initdata = अणु
	.core_init	= sh7786_pcie_core_init,
	.port_init_hw	= sh7786_pcie_init_hw,
पूर्ण;

अटल पूर्णांक __init sh7786_pcie_init(व्योम)
अणु
	काष्ठा clk *platclk;
	u32 mm_sel;
	पूर्णांक i;

	prपूर्णांकk(KERN_NOTICE "PCI: Starting initialization.\n");

	sh7786_pcie_hwops = &sh7786_65nm_pcie_hwops;

	nr_ports = sh7786_pcie_hwops->core_init();
	BUG_ON(nr_ports > ARRAY_SIZE(sh7786_pci_channels));

	अगर (unlikely(nr_ports == 0))
		वापस -ENODEV;

	sh7786_pcie_ports = kसुस्मृति(nr_ports, माप(काष्ठा sh7786_pcie_port),
				    GFP_KERNEL);
	अगर (unlikely(!sh7786_pcie_ports))
		वापस -ENOMEM;

	/*
	 * Fetch any optional platक्रमm घड़ी associated with this block.
	 *
	 * This is a rather nasty hack क्रम boards with spec-mocking FPGAs
	 * that have a secondary set of घड़ीs outside of the on-chip
	 * ones that need to be accounted क्रम beक्रमe there is any chance
	 * of touching the existing MSTP bits or CPG घड़ीs.
	 */
	platclk = clk_get(शून्य, "pcie_plat_clk");
	अगर (IS_ERR(platclk)) अणु
		/* Sane hardware should probably get a WARN_ON.. */
		platclk = शून्य;
	पूर्ण

	clk_enable(platclk);

	mm_sel = sh7786_mm_sel();

	/*
	 * Depending on the MMSELR रेजिस्टर value, the PCIe0 MEM 1
	 * area may not be available. See Table 13.11 of the SH7786
	 * datasheet.
	 */
	अगर (mm_sel != 1 && mm_sel != 2 && mm_sel != 5 && mm_sel != 6)
		sh7786_pci0_resources[2].flags |= IORESOURCE_DISABLED;

	prपूर्णांकk(KERN_NOTICE "PCI: probing %d ports.\n", nr_ports);

	क्रम (i = 0; i < nr_ports; i++) अणु
		काष्ठा sh7786_pcie_port *port = sh7786_pcie_ports + i;

		port->index		= i;
		port->hose		= sh7786_pci_channels + i;
		port->hose->io_map_base	= port->hose->resources[0].start;

		async_schedule(sh7786_pcie_hwops->port_init_hw, port);
	पूर्ण

	async_synchronize_full();

	वापस 0;
पूर्ण
arch_initcall(sh7786_pcie_init);
