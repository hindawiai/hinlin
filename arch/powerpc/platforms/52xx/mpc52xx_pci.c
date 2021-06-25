<शैली गुरु>
/*
 * PCI code क्रम the Freescale MPC52xx embedded CPU.
 *
 * Copyright (C) 2006 Secret Lab Technologies Ltd.
 *                        Grant Likely <grant.likely@secretlab.ca>
 * Copyright (C) 2004 Sylvain Munaut <tnt@246tNt.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अघोषित DEBUG

#समावेश <linux/pci.h>
#समावेश <यंत्र/mpc52xx.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/machdep.h>
#समावेश <linux/kernel.h>


/* ======================================================================== */
/* Structures mapping & Defines क्रम PCI Unit                                */
/* ======================================================================== */

#घोषणा MPC52xx_PCI_GSCR_BM		0x40000000
#घोषणा MPC52xx_PCI_GSCR_PE		0x20000000
#घोषणा MPC52xx_PCI_GSCR_SE		0x10000000
#घोषणा MPC52xx_PCI_GSCR_XLB2PCI_MASK	0x07000000
#घोषणा MPC52xx_PCI_GSCR_XLB2PCI_SHIFT	24
#घोषणा MPC52xx_PCI_GSCR_IPG2PCI_MASK	0x00070000
#घोषणा MPC52xx_PCI_GSCR_IPG2PCI_SHIFT	16
#घोषणा MPC52xx_PCI_GSCR_BME		0x00004000
#घोषणा MPC52xx_PCI_GSCR_PEE		0x00002000
#घोषणा MPC52xx_PCI_GSCR_SEE		0x00001000
#घोषणा MPC52xx_PCI_GSCR_PR		0x00000001


#घोषणा MPC52xx_PCI_IWBTAR_TRANSLATION(proc_ad,pci_ad,size)	  \
		( ( (proc_ad) & 0xff000000 )			| \
		  ( (((size) - 1) >> 8) & 0x00ff0000 )		| \
		  ( ((pci_ad) >> 16) & 0x0000ff00 ) )

#घोषणा MPC52xx_PCI_IWCR_PACK(win0,win1,win2)	(((win0) << 24) | \
						 ((win1) << 16) | \
						 ((win2) <<  8))

#घोषणा MPC52xx_PCI_IWCR_DISABLE	0x0
#घोषणा MPC52xx_PCI_IWCR_ENABLE		0x1
#घोषणा MPC52xx_PCI_IWCR_READ		0x0
#घोषणा MPC52xx_PCI_IWCR_READ_LINE	0x2
#घोषणा MPC52xx_PCI_IWCR_READ_MULTI	0x4
#घोषणा MPC52xx_PCI_IWCR_MEM		0x0
#घोषणा MPC52xx_PCI_IWCR_IO		0x8

#घोषणा MPC52xx_PCI_TCR_P		0x01000000
#घोषणा MPC52xx_PCI_TCR_LD		0x00010000
#घोषणा MPC52xx_PCI_TCR_WCT8		0x00000008

#घोषणा MPC52xx_PCI_TBATR_DISABLE	0x0
#घोषणा MPC52xx_PCI_TBATR_ENABLE	0x1

काष्ठा mpc52xx_pci अणु
	u32	idr;		/* PCI + 0x00 */
	u32	scr;		/* PCI + 0x04 */
	u32	ccrir;		/* PCI + 0x08 */
	u32	cr1;		/* PCI + 0x0C */
	u32	bar0;		/* PCI + 0x10 */
	u32	bar1;		/* PCI + 0x14 */
	u8	reserved1[16];	/* PCI + 0x18 */
	u32	ccpr;		/* PCI + 0x28 */
	u32	sid;		/* PCI + 0x2C */
	u32	erbar;		/* PCI + 0x30 */
	u32	cpr;		/* PCI + 0x34 */
	u8	reserved2[4];	/* PCI + 0x38 */
	u32	cr2;		/* PCI + 0x3C */
	u8	reserved3[32];	/* PCI + 0x40 */
	u32	gscr;		/* PCI + 0x60 */
	u32	tbatr0;		/* PCI + 0x64 */
	u32	tbatr1;		/* PCI + 0x68 */
	u32	tcr;		/* PCI + 0x6C */
	u32	iw0btar;	/* PCI + 0x70 */
	u32	iw1btar;	/* PCI + 0x74 */
	u32	iw2btar;	/* PCI + 0x78 */
	u8	reserved4[4];	/* PCI + 0x7C */
	u32	iwcr;		/* PCI + 0x80 */
	u32	icr;		/* PCI + 0x84 */
	u32	isr;		/* PCI + 0x88 */
	u32	arb;		/* PCI + 0x8C */
	u8	reserved5[104];	/* PCI + 0x90 */
	u32	car;		/* PCI + 0xF8 */
	u8	reserved6[4];	/* PCI + 0xFC */
पूर्ण;

/* MPC5200 device tree match tables */
स्थिर काष्ठा of_device_id mpc52xx_pci_ids[] __initस्थिर = अणु
	अणु .type = "pci", .compatible = "fsl,mpc5200-pci", पूर्ण,
	अणु .type = "pci", .compatible = "mpc5200-pci", पूर्ण,
	अणुपूर्ण
पूर्ण;

/* ======================================================================== */
/* PCI configuration access                                                 */
/* ======================================================================== */

अटल पूर्णांक
mpc52xx_pci_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक offset, पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	u32 value;

	अगर (ppc_md.pci_exclude_device)
		अगर (ppc_md.pci_exclude_device(hose, bus->number, devfn))
			वापस PCIBIOS_DEVICE_NOT_FOUND;

	out_be32(hose->cfg_addr,
		(1 << 31) |
		(bus->number << 16) |
		(devfn << 8) |
		(offset & 0xfc));
	mb();

#अगर defined(CONFIG_PPC_MPC5200_BUGFIX)
	अगर (bus->number) अणु
		/* workaround क्रम the bug 435 of the MPC5200 (L25R);
		 * Don't करो 32 bits config access during type-1 cycles */
		चयन (len) अणु
		      हाल 1:
			value = in_8(((u8 __iomem *)hose->cfg_data) +
			             (offset & 3));
			अवरोध;
		      हाल 2:
			value = in_le16(((u16 __iomem *)hose->cfg_data) +
			                ((offset>>1) & 1));
			अवरोध;

		      शेष:
			value = in_le16((u16 __iomem *)hose->cfg_data) |
				(in_le16(((u16 __iomem *)hose->cfg_data) + 1) << 16);
			अवरोध;
		पूर्ण
	पूर्ण
	अन्यथा
#पूर्ण_अगर
	अणु
		value = in_le32(hose->cfg_data);

		अगर (len != 4) अणु
			value >>= ((offset & 0x3) << 3);
			value &= 0xffffffff >> (32 - (len << 3));
		पूर्ण
	पूर्ण

	*val = value;

	out_be32(hose->cfg_addr, 0);
	mb();

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक
mpc52xx_pci_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				पूर्णांक offset, पूर्णांक len, u32 val)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bus);
	u32 value, mask;

	अगर (ppc_md.pci_exclude_device)
		अगर (ppc_md.pci_exclude_device(hose, bus->number, devfn))
			वापस PCIBIOS_DEVICE_NOT_FOUND;

	out_be32(hose->cfg_addr,
		(1 << 31) |
		(bus->number << 16) |
		(devfn << 8) |
		(offset & 0xfc));
	mb();

#अगर defined(CONFIG_PPC_MPC5200_BUGFIX)
	अगर (bus->number) अणु
		/* workaround क्रम the bug 435 of the MPC5200 (L25R);
		 * Don't करो 32 bits config access during type-1 cycles */
		चयन (len) अणु
		      हाल 1:
			out_8(((u8 __iomem *)hose->cfg_data) +
				(offset & 3), val);
			अवरोध;
		      हाल 2:
			out_le16(((u16 __iomem *)hose->cfg_data) +
				((offset>>1) & 1), val);
			अवरोध;

		      शेष:
			out_le16((u16 __iomem *)hose->cfg_data,
				(u16)val);
			out_le16(((u16 __iomem *)hose->cfg_data) + 1,
				(u16)(val>>16));
			अवरोध;
		पूर्ण
	पूर्ण
	अन्यथा
#पूर्ण_अगर
	अणु
		अगर (len != 4) अणु
			value = in_le32(hose->cfg_data);

			offset = (offset & 0x3) << 3;
			mask = (0xffffffff >> (32 - (len << 3)));
			mask <<= offset;

			value &= ~mask;
			val = value | ((val << offset) & mask);
		पूर्ण

		out_le32(hose->cfg_data, val);
	पूर्ण
	mb();

	out_be32(hose->cfg_addr, 0);
	mb();

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops mpc52xx_pci_ops = अणु
	.पढ़ो  = mpc52xx_pci_पढ़ो_config,
	.ग_लिखो = mpc52xx_pci_ग_लिखो_config
पूर्ण;


/* ======================================================================== */
/* PCI setup                                                                */
/* ======================================================================== */

अटल व्योम __init
mpc52xx_pci_setup(काष्ठा pci_controller *hose,
                  काष्ठा mpc52xx_pci __iomem *pci_regs, phys_addr_t pci_phys)
अणु
	काष्ठा resource *res;
	u32 पंचांगp;
	पूर्णांक iwcr0 = 0, iwcr1 = 0, iwcr2 = 0;

	pr_debug("mpc52xx_pci_setup(hose=%p, pci_regs=%p)\n", hose, pci_regs);

	/* pci_process_bridge_OF_ranges() found all our addresses क्रम us;
	 * now store them in the right places */
	hose->cfg_addr = &pci_regs->car;
	hose->cfg_data = hose->io_base_virt;

	/* Control regs */
	पंचांगp = in_be32(&pci_regs->scr);
	पंचांगp |= PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY;
	out_be32(&pci_regs->scr, पंचांगp);

	/* Memory winकरोws */
	res = &hose->mem_resources[0];
	अगर (res->flags) अणु
		pr_debug("mem_resource[0] = "
		         "{.start=%llx, .end=%llx, .flags=%llx}\n",
		         (अचिन्हित दीर्घ दीर्घ)res->start,
			 (अचिन्हित दीर्घ दीर्घ)res->end,
			 (अचिन्हित दीर्घ दीर्घ)res->flags);
		out_be32(&pci_regs->iw0btar,
		         MPC52xx_PCI_IWBTAR_TRANSLATION(res->start, res->start,
							resource_size(res)));
		iwcr0 = MPC52xx_PCI_IWCR_ENABLE | MPC52xx_PCI_IWCR_MEM;
		अगर (res->flags & IORESOURCE_PREFETCH)
			iwcr0 |= MPC52xx_PCI_IWCR_READ_MULTI;
		अन्यथा
			iwcr0 |= MPC52xx_PCI_IWCR_READ;
	पूर्ण

	res = &hose->mem_resources[1];
	अगर (res->flags) अणु
		pr_debug("mem_resource[1] = {.start=%x, .end=%x, .flags=%lx}\n",
		         res->start, res->end, res->flags);
		out_be32(&pci_regs->iw1btar,
		         MPC52xx_PCI_IWBTAR_TRANSLATION(res->start, res->start,
							resource_size(res)));
		iwcr1 = MPC52xx_PCI_IWCR_ENABLE | MPC52xx_PCI_IWCR_MEM;
		अगर (res->flags & IORESOURCE_PREFETCH)
			iwcr1 |= MPC52xx_PCI_IWCR_READ_MULTI;
		अन्यथा
			iwcr1 |= MPC52xx_PCI_IWCR_READ;
	पूर्ण

	/* IO resources */
	res = &hose->io_resource;
	अगर (!res) अणु
		prपूर्णांकk(KERN_ERR "%s: Didn't find IO resources\n", __खाता__);
		वापस;
	पूर्ण
	pr_debug(".io_resource={.start=%llx,.end=%llx,.flags=%llx} "
	         ".io_base_phys=0x%p\n",
	         (अचिन्हित दीर्घ दीर्घ)res->start,
		 (अचिन्हित दीर्घ दीर्घ)res->end,
		 (अचिन्हित दीर्घ दीर्घ)res->flags, (व्योम*)hose->io_base_phys);
	out_be32(&pci_regs->iw2btar,
	         MPC52xx_PCI_IWBTAR_TRANSLATION(hose->io_base_phys,
	                                        res->start,
						resource_size(res)));
	iwcr2 = MPC52xx_PCI_IWCR_ENABLE | MPC52xx_PCI_IWCR_IO;

	/* Set all the IWCR fields at once; they're in the same reg */
	out_be32(&pci_regs->iwcr, MPC52xx_PCI_IWCR_PACK(iwcr0, iwcr1, iwcr2));

	/* Map IMMR onto PCI bus */
	pci_phys &= 0xfffc0000; /* bar0 has only 14 signअगरicant bits */
	out_be32(&pci_regs->tbatr0, MPC52xx_PCI_TBATR_ENABLE | pci_phys);
	out_be32(&pci_regs->bar0, PCI_BASE_ADDRESS_MEM_PREFETCH | pci_phys);

	/* Map memory onto PCI bus */
	out_be32(&pci_regs->tbatr1, MPC52xx_PCI_TBATR_ENABLE);
	out_be32(&pci_regs->bar1, PCI_BASE_ADDRESS_MEM_PREFETCH);

	out_be32(&pci_regs->tcr, MPC52xx_PCI_TCR_LD | MPC52xx_PCI_TCR_WCT8);

	पंचांगp = in_be32(&pci_regs->gscr);
#अगर 0
	/* Reset the exteral bus ( पूर्णांकernal PCI controller is NOT reset ) */
	/* Not necessary and can be a bad thing अगर क्रम example the bootloader
	   is displaying a splash screen or ... Just left here क्रम
	   करोcumentation purpose अगर anyone need it */
	out_be32(&pci_regs->gscr, पंचांगp | MPC52xx_PCI_GSCR_PR);
	udelay(50);
#पूर्ण_अगर

	/* Make sure the PCI bridge is out of reset */
	out_be32(&pci_regs->gscr, पंचांगp & ~MPC52xx_PCI_GSCR_PR);
पूर्ण

अटल व्योम
mpc52xx_pci_fixup_resources(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	pr_debug("mpc52xx_pci_fixup_resources() %.4x:%.4x\n",
	         dev->venकरोr, dev->device);

	/* We करोn't rely on boot loader क्रम PCI and resets all
	   devices */
	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		काष्ठा resource *res = &dev->resource[i];
		अगर (res->end > res->start) अणु	/* Only valid resources */
			res->end -= res->start;
			res->start = 0;
			res->flags |= IORESOURCE_UNSET;
		पूर्ण
	पूर्ण

	/* The PCI Host bridge of MPC52xx has a prefetch memory resource
	   fixed to 1Gb. Doesn't fit in the resource प्रणाली so we हटाओ it */
	अगर ( (dev->venकरोr == PCI_VENDOR_ID_MOTOROLA) &&
	     (   dev->device == PCI_DEVICE_ID_MOTOROLA_MPC5200
	      || dev->device == PCI_DEVICE_ID_MOTOROLA_MPC5200B) ) अणु
		काष्ठा resource *res = &dev->resource[1];
		res->start = res->end = res->flags = 0;
	पूर्ण
पूर्ण

पूर्णांक __init
mpc52xx_add_bridge(काष्ठा device_node *node)
अणु
	पूर्णांक len;
	काष्ठा mpc52xx_pci __iomem *pci_regs;
	काष्ठा pci_controller *hose;
	स्थिर पूर्णांक *bus_range;
	काष्ठा resource rsrc;

	pr_debug("Adding MPC52xx PCI host bridge %pOF\n", node);

	pci_add_flags(PCI_REASSIGN_ALL_BUS);

	अगर (of_address_to_resource(node, 0, &rsrc) != 0) अणु
		prपूर्णांकk(KERN_ERR "Can't get %pOF resources\n", node);
		वापस -EINVAL;
	पूर्ण

	bus_range = of_get_property(node, "bus-range", &len);
	अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक)) अणु
		prपूर्णांकk(KERN_WARNING "Can't get %pOF bus-range, assume bus 0\n",
		       node);
		bus_range = शून्य;
	पूर्ण

	/* There are some PCI quirks on the 52xx, रेजिस्टर the hook to
	 * fix them. */
	ppc_md.pcibios_fixup_resources = mpc52xx_pci_fixup_resources;

	/* Alloc and initialize the pci controller.  Values in the device
	 * tree are needed to configure the 52xx PCI controller.  Rather
	 * than parse the tree here, let pci_process_bridge_OF_ranges()
	 * करो it क्रम us and extract the values after the fact */
	hose = pcibios_alloc_controller(node);
	अगर (!hose)
		वापस -ENOMEM;

	hose->first_busno = bus_range ? bus_range[0] : 0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;

	hose->ops = &mpc52xx_pci_ops;

	pci_regs = ioremap(rsrc.start, resource_size(&rsrc));
	अगर (!pci_regs)
		वापस -ENOMEM;

	pci_process_bridge_OF_ranges(hose, node, 1);

	/* Finish setting up PCI using values obtained by
	 * pci_proces_bridge_OF_ranges */
	mpc52xx_pci_setup(hose, pci_regs, rsrc.start);

	वापस 0;
पूर्ण

व्योम __init mpc52xx_setup_pci(व्योम)
अणु
	काष्ठा device_node *pci;

	pci = of_find_matching_node(शून्य, mpc52xx_pci_ids);
	अगर (!pci)
		वापस;

	mpc52xx_add_bridge(pci);
	of_node_put(pci);
पूर्ण
