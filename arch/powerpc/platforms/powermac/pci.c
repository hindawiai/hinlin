<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम PCI bridges found on Power Macपूर्णांकoshes.
 *
 * Copyright (C) 2003-2005 Benjamin Herrenschmuidt (benh@kernel.crashing.org)
 * Copyright (C) 1997 Paul Mackerras (paulus@samba.org)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_pci.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/grackle.h>
#समावेश <यंत्र/ppc-pci.h>

#समावेश "pmac.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(x...) prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG(x...)
#पूर्ण_अगर

/* XXX Could be per-controller, but I करोn't think we risk anything by
 * assuming we won't have both UniNorth and Bandit */
अटल पूर्णांक has_uninorth;
#अगर_घोषित CONFIG_PPC64
अटल काष्ठा pci_controller *u3_agp;
#अन्यथा
अटल पूर्णांक has_second_ohare;
#पूर्ण_अगर /* CONFIG_PPC64 */

बाह्य पूर्णांक pcibios_assign_bus_offset;

काष्ठा device_node *k2_skiplist[2];

/*
 * Magic स्थिरants क्रम enabling cache coherency in the bandit/PSX bridge.
 */
#घोषणा BANDIT_DEVID_2	8
#घोषणा BANDIT_REVID	3

#घोषणा BANDIT_DEVNUM	11
#घोषणा BANDIT_MAGIC	0x50
#घोषणा BANDIT_COHERENT	0x40

अटल पूर्णांक __init fixup_one_level_bus_range(काष्ठा device_node *node, पूर्णांक higher)
अणु
	क्रम (; node; node = node->sibling) अणु
		स्थिर पूर्णांक * bus_range;
		स्थिर अचिन्हित पूर्णांक *class_code;
		पूर्णांक len;

		/* For PCI<->PCI bridges or CardBus bridges, we go करोwn */
		class_code = of_get_property(node, "class-code", शून्य);
		अगर (!class_code || ((*class_code >> 8) != PCI_CLASS_BRIDGE_PCI &&
			(*class_code >> 8) != PCI_CLASS_BRIDGE_CARDBUS))
			जारी;
		bus_range = of_get_property(node, "bus-range", &len);
		अगर (bus_range != शून्य && len > 2 * माप(पूर्णांक)) अणु
			अगर (bus_range[1] > higher)
				higher = bus_range[1];
		पूर्ण
		higher = fixup_one_level_bus_range(node->child, higher);
	पूर्ण
	वापस higher;
पूर्ण

/* This routine fixes the "bus-range" property of all bridges in the
 * प्रणाली since they tend to have their "last" member wrong on macs
 *
 * Note that the bus numbers manipulated here are OF bus numbers, they
 * are not Linux bus numbers.
 */
अटल व्योम __init fixup_bus_range(काष्ठा device_node *bridge)
अणु
	पूर्णांक *bus_range, len;
	काष्ठा property *prop;

	/* Lookup the "bus-range" property क्रम the hose */
	prop = of_find_property(bridge, "bus-range", &len);
	अगर (prop == शून्य || prop->length < 2 * माप(पूर्णांक))
		वापस;

	bus_range = prop->value;
	bus_range[1] = fixup_one_level_bus_range(bridge->child, bus_range[1]);
पूर्ण

/*
 * Apple MacRISC (U3, UniNorth, Bandit, Chaos) PCI controllers.
 *
 * The "Bandit" version is present in all early PCI PowerMacs,
 * and up to the first ones using Grackle. Some machines may
 * have 2 bandit controllers (2 PCI busses).
 *
 * "Chaos" is used in some "Bandit"-type machines as a bridge
 * क्रम the separate display bus. It is accessed the same
 * way as bandit, but cannot be probed क्रम devices. It thereक्रमe
 * has its own config access functions.
 *
 * The "UniNorth" version is present in all Core99 machines
 * (iBook, G4, new IMacs, and all the recent Apple machines).
 * It contains 3 controllers in one ASIC.
 *
 * The U3 is the bridge used on G5 machines. It contains an
 * AGP bus which is dealt with the old UniNorth access routines
 * and a HyperTransport bus which uses its own set of access
 * functions.
 */

#घोषणा MACRISC_CFA0(devfn, off)	\
	((1 << (अचिन्हित पूर्णांक)PCI_SLOT(dev_fn)) \
	| (((अचिन्हित पूर्णांक)PCI_FUNC(dev_fn)) << 8) \
	| (((अचिन्हित पूर्णांक)(off)) & 0xFCUL))

#घोषणा MACRISC_CFA1(bus, devfn, off)	\
	((((अचिन्हित पूर्णांक)(bus)) << 16) \
	|(((अचिन्हित पूर्णांक)(devfn)) << 8) \
	|(((अचिन्हित पूर्णांक)(off)) & 0xFCUL) \
	|1UL)

अटल व्योम __iomem *macrisc_cfg_map_bus(काष्ठा pci_bus *bus,
					 अचिन्हित पूर्णांक dev_fn,
					 पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक caddr;
	काष्ठा pci_controller *hose;

	hose = pci_bus_to_host(bus);
	अगर (hose == शून्य)
		वापस शून्य;

	अगर (bus->number == hose->first_busno) अणु
		अगर (dev_fn < (11 << 3))
			वापस शून्य;
		caddr = MACRISC_CFA0(dev_fn, offset);
	पूर्ण अन्यथा
		caddr = MACRISC_CFA1(bus->number, dev_fn, offset);

	/* Uninorth will वापस garbage अगर we करोn't पढ़ो back the value ! */
	करो अणु
		out_le32(hose->cfg_addr, caddr);
	पूर्ण जबतक (in_le32(hose->cfg_addr) != caddr);

	offset &= has_uninorth ? 0x07 : 0x03;
	वापस hose->cfg_data + offset;
पूर्ण

अटल काष्ठा pci_ops macrisc_pci_ops =
अणु
	.map_bus = macrisc_cfg_map_bus,
	.पढ़ो = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

#अगर_घोषित CONFIG_PPC32
/*
 * Verअगरy that a specअगरic (bus, dev_fn) exists on chaos
 */
अटल व्योम __iomem *chaos_map_bus(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक offset)
अणु
	काष्ठा device_node *np;
	स्थिर u32 *venकरोr, *device;

	अगर (offset >= 0x100)
		वापस शून्य;
	np = of_pci_find_child_device(bus->dev.of_node, devfn);
	अगर (np == शून्य)
		वापस शून्य;

	venकरोr = of_get_property(np, "vendor-id", शून्य);
	device = of_get_property(np, "device-id", शून्य);
	अगर (venकरोr == शून्य || device == शून्य)
		वापस शून्य;

	अगर ((*venकरोr == 0x106b) && (*device == 3) && (offset >= 0x10)
	    && (offset != 0x14) && (offset != 0x18) && (offset <= 0x24))
		वापस शून्य;

	वापस macrisc_cfg_map_bus(bus, devfn, offset);
पूर्ण

अटल काष्ठा pci_ops chaos_pci_ops =
अणु
	.map_bus = chaos_map_bus,
	.पढ़ो = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

अटल व्योम __init setup_chaos(काष्ठा pci_controller *hose,
			       काष्ठा resource *addr)
अणु
	/* assume a `chaos' bridge */
	hose->ops = &chaos_pci_ops;
	hose->cfg_addr = ioremap(addr->start + 0x800000, 0x1000);
	hose->cfg_data = ioremap(addr->start + 0xc00000, 0x1000);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 */

#अगर_घोषित CONFIG_PPC64
/*
 * These versions of U3 HyperTransport config space access ops करो not
 * implement self-view of the HT host yet
 */

/*
 * This function deals with some "special cases" devices.
 *
 *  0 -> No special हाल
 *  1 -> Skip the device but act as अगर the access was successful
 *       (वापस 0xff's on पढ़ोs, eventually, cache config space
 *       accesses in a later version)
 * -1 -> Hide the device (unsuccessful access)
 */
अटल पूर्णांक u3_ht_skip_device(काष्ठा pci_controller *hose,
			     काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn)
अणु
	काष्ठा device_node *busdn, *dn;
	पूर्णांक i;

	/* We only allow config cycles to devices that are in OF device-tree
	 * as we are apparently having some weird things going on with some
	 * revs of K2 on recent G5s, except क्रम the host bridge itself, which
	 * is missing from the tree but we know we can probe.
	 */
	अगर (bus->self)
		busdn = pci_device_to_OF_node(bus->self);
	अन्यथा अगर (devfn == 0)
		वापस 0;
	अन्यथा
		busdn = hose->dn;
	क्रम (dn = busdn->child; dn; dn = dn->sibling)
		अगर (PCI_DN(dn) && PCI_DN(dn)->devfn == devfn)
			अवरोध;
	अगर (dn == शून्य)
		वापस -1;

	/*
	 * When a device in K2 is घातered करोwn, we die on config
	 * cycle accesses. Fix that here.
	 */
	क्रम (i=0; i<2; i++)
		अगर (k2_skiplist[i] == dn)
			वापस 1;

	वापस 0;
पूर्ण

#घोषणा U3_HT_CFA0(devfn, off)		\
		((((अचिन्हित पूर्णांक)devfn) << 8) | offset)
#घोषणा U3_HT_CFA1(bus, devfn, off)	\
		(U3_HT_CFA0(devfn, off) \
		+ (((अचिन्हित पूर्णांक)bus) << 16) \
		+ 0x01000000UL)

अटल व्योम __iomem *u3_ht_cfg_access(काष्ठा pci_controller *hose, u8 bus,
				      u8 devfn, u8 offset, पूर्णांक *swap)
अणु
	*swap = 1;
	अगर (bus == hose->first_busno) अणु
		अगर (devfn != 0)
			वापस hose->cfg_data + U3_HT_CFA0(devfn, offset);
		*swap = 0;
		वापस ((व्योम __iomem *)hose->cfg_addr) + (offset << 2);
	पूर्ण अन्यथा
		वापस hose->cfg_data + U3_HT_CFA1(bus, devfn, offset);
पूर्ण

अटल पूर्णांक u3_ht_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				    पूर्णांक offset, पूर्णांक len, u32 *val)
अणु
	काष्ठा pci_controller *hose;
	व्योम __iomem *addr;
	पूर्णांक swap;

	hose = pci_bus_to_host(bus);
	अगर (hose == शून्य)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अगर (offset >= 0x100)
		वापस  PCIBIOS_BAD_REGISTER_NUMBER;
	addr = u3_ht_cfg_access(hose, bus->number, devfn, offset, &swap);
	अगर (!addr)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	चयन (u3_ht_skip_device(hose, bus, devfn)) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		चयन (len) अणु
		हाल 1:
			*val = 0xff; अवरोध;
		हाल 2:
			*val = 0xffff; अवरोध;
		शेष:
			*val = 0xfffffffful; अवरोध;
		पूर्ण
		वापस PCIBIOS_SUCCESSFUL;
	शेष:
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	/*
	 * Note: the caller has alपढ़ोy checked that offset is
	 * suitably aligned and that len is 1, 2 or 4.
	 */
	चयन (len) अणु
	हाल 1:
		*val = in_8(addr);
		अवरोध;
	हाल 2:
		*val = swap ? in_le16(addr) : in_be16(addr);
		अवरोध;
	शेष:
		*val = swap ? in_le32(addr) : in_be32(addr);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक u3_ht_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				     पूर्णांक offset, पूर्णांक len, u32 val)
अणु
	काष्ठा pci_controller *hose;
	व्योम __iomem *addr;
	पूर्णांक swap;

	hose = pci_bus_to_host(bus);
	अगर (hose == शून्य)
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अगर (offset >= 0x100)
		वापस  PCIBIOS_BAD_REGISTER_NUMBER;
	addr = u3_ht_cfg_access(hose, bus->number, devfn, offset, &swap);
	अगर (!addr)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	चयन (u3_ht_skip_device(hose, bus, devfn)) अणु
	हाल 0:
		अवरोध;
	हाल 1:
		वापस PCIBIOS_SUCCESSFUL;
	शेष:
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	/*
	 * Note: the caller has alपढ़ोy checked that offset is
	 * suitably aligned and that len is 1, 2 or 4.
	 */
	चयन (len) अणु
	हाल 1:
		out_8(addr, val);
		अवरोध;
	हाल 2:
		swap ? out_le16(addr, val) : out_be16(addr, val);
		अवरोध;
	शेष:
		swap ? out_le32(addr, val) : out_be32(addr, val);
		अवरोध;
	पूर्ण
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops u3_ht_pci_ops =
अणु
	.पढ़ो = u3_ht_पढ़ो_config,
	.ग_लिखो = u3_ht_ग_लिखो_config,
पूर्ण;

#घोषणा U4_PCIE_CFA0(devfn, off)	\
	((1 << ((अचिन्हित पूर्णांक)PCI_SLOT(dev_fn)))	\
	 | (((अचिन्हित पूर्णांक)PCI_FUNC(dev_fn)) << 8)	\
	 | ((((अचिन्हित पूर्णांक)(off)) >> 8) << 28) \
	 | (((अचिन्हित पूर्णांक)(off)) & 0xfcU))

#घोषणा U4_PCIE_CFA1(bus, devfn, off)	\
	((((अचिन्हित पूर्णांक)(bus)) << 16) \
	 |(((अचिन्हित पूर्णांक)(devfn)) << 8)	\
	 | ((((अचिन्हित पूर्णांक)(off)) >> 8) << 28) \
	 |(((अचिन्हित पूर्णांक)(off)) & 0xfcU)	\
	 |1UL)

अटल व्योम __iomem *u4_pcie_cfg_map_bus(काष्ठा pci_bus *bus,
					 अचिन्हित पूर्णांक dev_fn,
					 पूर्णांक offset)
अणु
	काष्ठा pci_controller *hose;
	अचिन्हित पूर्णांक caddr;

	अगर (offset >= 0x1000)
		वापस शून्य;

	hose = pci_bus_to_host(bus);
	अगर (!hose)
		वापस शून्य;

	अगर (bus->number == hose->first_busno) अणु
		caddr = U4_PCIE_CFA0(dev_fn, offset);
	पूर्ण अन्यथा
		caddr = U4_PCIE_CFA1(bus->number, dev_fn, offset);

	/* Uninorth will वापस garbage अगर we करोn't पढ़ो back the value ! */
	करो अणु
		out_le32(hose->cfg_addr, caddr);
	पूर्ण जबतक (in_le32(hose->cfg_addr) != caddr);

	offset &= 0x03;
	वापस hose->cfg_data + offset;
पूर्ण

अटल काष्ठा pci_ops u4_pcie_pci_ops =
अणु
	.map_bus = u4_pcie_cfg_map_bus,
	.पढ़ो = pci_generic_config_पढ़ो,
	.ग_लिखो = pci_generic_config_ग_लिखो,
पूर्ण;

अटल व्योम pmac_pci_fixup_u4_of_node(काष्ठा pci_dev *dev)
अणु
	/* Apple's device-tree "hides" the root complex भव P2P bridge
	 * on U4. However, Linux sees it, causing the PCI <-> OF matching
	 * code to fail to properly match devices below it. This works around
	 * it by setting the node of the bridge to poपूर्णांक to the PHB node,
	 * which is not entirely correct but fixes the matching code and
	 * करोesn't break anything else. It's also the simplest possible fix.
	 */
	अगर (dev->dev.of_node == शून्य)
		dev->dev.of_node = pcibios_get_phb_of_node(dev->bus);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_APPLE, 0x5b, pmac_pci_fixup_u4_of_node);

#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_घोषित CONFIG_PPC32
/*
 * For a bandit bridge, turn on cache coherency अगर necessary.
 * N.B. we could clean this up using the hose ops directly.
 */
अटल व्योम __init init_bandit(काष्ठा pci_controller *bp)
अणु
	अचिन्हित पूर्णांक vendev, magic;
	पूर्णांक rev;

	/* पढ़ो the word at offset 0 in config space क्रम device 11 */
	out_le32(bp->cfg_addr, (1UL << BANDIT_DEVNUM) + PCI_VENDOR_ID);
	udelay(2);
	vendev = in_le32(bp->cfg_data);
	अगर (vendev == (PCI_DEVICE_ID_APPLE_BANDIT << 16) +
			PCI_VENDOR_ID_APPLE) अणु
		/* पढ़ो the revision id */
		out_le32(bp->cfg_addr,
			 (1UL << BANDIT_DEVNUM) + PCI_REVISION_ID);
		udelay(2);
		rev = in_8(bp->cfg_data);
		अगर (rev != BANDIT_REVID)
			prपूर्णांकk(KERN_WARNING
			       "Unknown revision %d for bandit\n", rev);
	पूर्ण अन्यथा अगर (vendev != (BANDIT_DEVID_2 << 16) + PCI_VENDOR_ID_APPLE) अणु
		prपूर्णांकk(KERN_WARNING "bandit isn't? (%x)\n", vendev);
		वापस;
	पूर्ण

	/* पढ़ो the word at offset 0x50 */
	out_le32(bp->cfg_addr, (1UL << BANDIT_DEVNUM) + BANDIT_MAGIC);
	udelay(2);
	magic = in_le32(bp->cfg_data);
	अगर ((magic & BANDIT_COHERENT) != 0)
		वापस;
	magic |= BANDIT_COHERENT;
	udelay(2);
	out_le32(bp->cfg_data, magic);
	prपूर्णांकk(KERN_INFO "Cache coherency enabled for bandit/PSX\n");
पूर्ण

/*
 * Tweak the PCI-PCI bridge chip on the blue & white G3s.
 */
अटल व्योम __init init_p2pbridge(व्योम)
अणु
	काष्ठा device_node *p2pbridge;
	काष्ठा pci_controller* hose;
	u8 bus, devfn;
	u16 val;

	/* XXX it would be better here to identअगरy the specअगरic
	   PCI-PCI bridge chip we have. */
	p2pbridge = of_find_node_by_name(शून्य, "pci-bridge");
	अगर (p2pbridge == शून्य || !of_node_name_eq(p2pbridge->parent, "pci"))
		जाओ करोne;
	अगर (pci_device_from_OF_node(p2pbridge, &bus, &devfn) < 0) अणु
		DBG("Can't find PCI infos for PCI<->PCI bridge\n");
		जाओ करोne;
	पूर्ण
	/* Warning: At this poपूर्णांक, we have not yet rक्रमागतbered all busses.
	 * So we must use OF walking to find out hose
	 */
	hose = pci_find_hose_क्रम_OF_device(p2pbridge);
	अगर (!hose) अणु
		DBG("Can't find hose for PCI<->PCI bridge\n");
		जाओ करोne;
	पूर्ण
	अगर (early_पढ़ो_config_word(hose, bus, devfn,
				   PCI_BRIDGE_CONTROL, &val) < 0) अणु
		prपूर्णांकk(KERN_ERR "init_p2pbridge: couldn't read bridge"
		       " control\n");
		जाओ करोne;
	पूर्ण
	val &= ~PCI_BRIDGE_CTL_MASTER_ABORT;
	early_ग_लिखो_config_word(hose, bus, devfn, PCI_BRIDGE_CONTROL, val);
करोne:
	of_node_put(p2pbridge);
पूर्ण

अटल व्योम __init init_second_ohare(व्योम)
अणु
	काष्ठा device_node *np = of_find_node_by_name(शून्य, "pci106b,7");
	अचिन्हित अक्षर bus, devfn;
	अचिन्हित लघु cmd;

	अगर (np == शून्य)
		वापस;

	/* This must run beक्रमe we initialize the PICs since the second
	 * ohare hosts a PIC that will be accessed there.
	 */
	अगर (pci_device_from_OF_node(np, &bus, &devfn) == 0) अणु
		काष्ठा pci_controller* hose =
			pci_find_hose_क्रम_OF_device(np);
		अगर (!hose) अणु
			prपूर्णांकk(KERN_ERR "Can't find PCI hose for OHare2 !\n");
			of_node_put(np);
			वापस;
		पूर्ण
		early_पढ़ो_config_word(hose, bus, devfn, PCI_COMMAND, &cmd);
		cmd |= PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER;
		cmd &= ~PCI_COMMAND_IO;
		early_ग_लिखो_config_word(hose, bus, devfn, PCI_COMMAND, cmd);
	पूर्ण
	has_second_ohare = 1;
	of_node_put(np);
पूर्ण

/*
 * Some Apple desktop machines have a NEC PD720100A USB2 controller
 * on the motherboard. Open Firmware, on these, will disable the
 * EHCI part of it so it behaves like a pair of OHCI's. This fixup
 * code re-enables it ;)
 */
अटल व्योम __init fixup_nec_usb2(व्योम)
अणु
	काष्ठा device_node *nec;

	क्रम_each_node_by_name(nec, "usb") अणु
		काष्ठा pci_controller *hose;
		u32 data;
		स्थिर u32 *prop;
		u8 bus, devfn;

		prop = of_get_property(nec, "vendor-id", शून्य);
		अगर (prop == शून्य)
			जारी;
		अगर (0x1033 != *prop)
			जारी;
		prop = of_get_property(nec, "device-id", शून्य);
		अगर (prop == शून्य)
			जारी;
		अगर (0x0035 != *prop)
			जारी;
		prop = of_get_property(nec, "reg", शून्य);
		अगर (prop == शून्य)
			जारी;
		devfn = (prop[0] >> 8) & 0xff;
		bus = (prop[0] >> 16) & 0xff;
		अगर (PCI_FUNC(devfn) != 0)
			जारी;
		hose = pci_find_hose_क्रम_OF_device(nec);
		अगर (!hose)
			जारी;
		early_पढ़ो_config_dword(hose, bus, devfn, 0xe4, &data);
		अगर (data & 1UL) अणु
			prपूर्णांकk("Found NEC PD720100A USB2 chip with disabled"
			       " EHCI, fixing up...\n");
			data &= ~1UL;
			early_ग_लिखो_config_dword(hose, bus, devfn, 0xe4, data);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __init setup_bandit(काष्ठा pci_controller *hose,
				काष्ठा resource *addr)
अणु
	hose->ops = &macrisc_pci_ops;
	hose->cfg_addr = ioremap(addr->start + 0x800000, 0x1000);
	hose->cfg_data = ioremap(addr->start + 0xc00000, 0x1000);
	init_bandit(hose);
पूर्ण

अटल पूर्णांक __init setup_uninorth(काष्ठा pci_controller *hose,
				 काष्ठा resource *addr)
अणु
	pci_add_flags(PCI_REASSIGN_ALL_BUS);
	has_uninorth = 1;
	hose->ops = &macrisc_pci_ops;
	hose->cfg_addr = ioremap(addr->start + 0x800000, 0x1000);
	hose->cfg_data = ioremap(addr->start + 0xc00000, 0x1000);
	/* We "know" that the bridge at f2000000 has the PCI slots. */
	वापस addr->start == 0xf2000000;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 */

#अगर_घोषित CONFIG_PPC64
अटल व्योम __init setup_u3_agp(काष्ठा pci_controller* hose)
अणु
	/* On G5, we move AGP up to high bus number so we करोn't need
	 * to reassign bus numbers क्रम HT. If we ever have P2P bridges
	 * on AGP, we'll have to move pci_assign_all_busses to the
	 * pci_controller काष्ठाure so we enable it क्रम AGP and not क्रम
	 * HT childs.
	 * We hard code the address because of the dअगरferent size of
	 * the reg address cell, we shall fix that by समाप्तing काष्ठा
	 * reg_property and using some accessor functions instead
	 */
	hose->first_busno = 0xf0;
	hose->last_busno = 0xff;
	has_uninorth = 1;
	hose->ops = &macrisc_pci_ops;
	hose->cfg_addr = ioremap(0xf0000000 + 0x800000, 0x1000);
	hose->cfg_data = ioremap(0xf0000000 + 0xc00000, 0x1000);
	u3_agp = hose;
पूर्ण

अटल व्योम __init setup_u4_pcie(काष्ठा pci_controller* hose)
अणु
	/* We currently only implement the "non-atomic" config space, to
	 * be optimised later.
	 */
	hose->ops = &u4_pcie_pci_ops;
	hose->cfg_addr = ioremap(0xf0000000 + 0x800000, 0x1000);
	hose->cfg_data = ioremap(0xf0000000 + 0xc00000, 0x1000);

	/* The bus contains a bridge from root -> device, we need to
	 * make it visible on bus 0 so that we pick the right type
	 * of config cycles. If we didn't, we would have to क्रमce all
	 * config cycles to be type 1. So we override the "bus-range"
	 * property here
	 */
	hose->first_busno = 0x00;
	hose->last_busno = 0xff;
पूर्ण

अटल व्योम __init parse_region_decode(काष्ठा pci_controller *hose,
				       u32 decode)
अणु
	अचिन्हित दीर्घ base, end, next = -1;
	पूर्णांक i, cur = -1;

	/* Iterate through all bits. We ignore the last bit as this region is
	 * reserved क्रम the ROM among other niceties
	 */
	क्रम (i = 0; i < 31; i++) अणु
		अगर ((decode & (0x80000000 >> i)) == 0)
			जारी;
		अगर (i < 16) अणु
			base = 0xf0000000 | (((u32)i) << 24);
			end = base + 0x00ffffff;
		पूर्ण अन्यथा अणु
			base = ((u32)i-16) << 28;
			end = base + 0x0fffffff;
		पूर्ण
		अगर (base != next) अणु
			अगर (++cur >= 3) अणु
				prपूर्णांकk(KERN_WARNING "PCI: Too many ranges !\n");
				अवरोध;
			पूर्ण
			hose->mem_resources[cur].flags = IORESOURCE_MEM;
			hose->mem_resources[cur].name = hose->dn->full_name;
			hose->mem_resources[cur].start = base;
			hose->mem_resources[cur].end = end;
			hose->mem_offset[cur] = 0;
			DBG("  %d: 0x%08lx-0x%08lx\n", cur, base, end);
		पूर्ण अन्यथा अणु
			DBG("   :           -0x%08lx\n", end);
			hose->mem_resources[cur].end = end;
		पूर्ण
		next = end + 1;
	पूर्ण
पूर्ण

अटल व्योम __init setup_u3_ht(काष्ठा pci_controller* hose)
अणु
	काष्ठा device_node *np = hose->dn;
	काष्ठा resource cfg_res, self_res;
	u32 decode;

	hose->ops = &u3_ht_pci_ops;

	/* Get base addresses from OF tree
	 */
	अगर (of_address_to_resource(np, 0, &cfg_res) ||
	    of_address_to_resource(np, 1, &self_res)) अणु
		prपूर्णांकk(KERN_ERR "PCI: Failed to get U3/U4 HT resources !\n");
		वापस;
	पूर्ण

	/* Map बाह्यal cfg space access पूर्णांकo cfg_data and self रेजिस्टरs
	 * पूर्णांकo cfg_addr
	 */
	hose->cfg_data = ioremap(cfg_res.start, 0x02000000);
	hose->cfg_addr = ioremap(self_res.start, resource_size(&self_res));

	/*
	 * /ht node करोesn't expose a "ranges" property, we पढ़ो the रेजिस्टर
	 * that controls the decoding logic and use that क्रम memory regions.
	 * The IO region is hard coded since it is fixed in HW as well.
	 */
	hose->io_base_phys = 0xf4000000;
	hose->pci_io_size = 0x00400000;
	hose->io_resource.name = np->full_name;
	hose->io_resource.start = 0;
	hose->io_resource.end = 0x003fffff;
	hose->io_resource.flags = IORESOURCE_IO;
	hose->first_busno = 0;
	hose->last_busno = 0xef;

	/* Note: fix offset when cfg_addr becomes a व्योम * */
	decode = in_be32(hose->cfg_addr + 0x80);

	DBG("PCI: Apple HT bridge decode register: 0x%08x\n", decode);

	/* NOTE: The decode रेजिस्टर setup is a bit weird... region
	 * 0xf8000000 क्रम example is marked as enabled in there जबतक it's
	 & actually the memory controller रेजिस्टरs.
	 * That means that we are incorrectly attributing it to HT.
	 *
	 * In a similar vein, region 0xf4000000 is actually the HT IO space but
	 * also marked as enabled in here and 0xf9000000 is used by some other
	 * पूर्णांकernal bits of the northbridge.
	 *
	 * Unक्रमtunately, we can't just mask out those bit as we would end
	 * up with more regions than we can cope (linux can only cope with
	 * 3 memory regions क्रम a PHB at this stage).
	 *
	 * So क्रम now, we just करो a little hack. We happen to -know- that
	 * Apple firmware करोesn't assign things below 0xfa000000 क्रम that
	 * bridge anyway so we mask out all bits we करोn't want.
	 */
	decode &= 0x003fffff;

	/* Now parse the resulting bits and build resources */
	parse_region_decode(hose, decode);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

/*
 * We assume that अगर we have a G3 घातermac, we have one bridge called
 * "pci" (a MPC106) and no bandit or chaos bridges, and contrariwise,
 * अगर we have one or more bandit or chaos bridges, we करोn't have a MPC106.
 */
अटल पूर्णांक __init pmac_add_bridge(काष्ठा device_node *dev)
अणु
	पूर्णांक len;
	काष्ठा pci_controller *hose;
	काष्ठा resource rsrc;
	अक्षर *disp_name;
	स्थिर पूर्णांक *bus_range;
	पूर्णांक primary = 1;

	DBG("Adding PCI host bridge %pOF\n", dev);

	/* Fetch host bridge रेजिस्टरs address */
	of_address_to_resource(dev, 0, &rsrc);

	/* Get bus range अगर any */
	bus_range = of_get_property(dev, "bus-range", &len);
	अगर (bus_range == शून्य || len < 2 * माप(पूर्णांक)) अणु
		prपूर्णांकk(KERN_WARNING "Can't get bus-range for %pOF, assume"
		       " bus 0\n", dev);
	पूर्ण

	hose = pcibios_alloc_controller(dev);
	अगर (!hose)
		वापस -ENOMEM;
	hose->first_busno = bus_range ? bus_range[0] : 0;
	hose->last_busno = bus_range ? bus_range[1] : 0xff;
	hose->controller_ops = pmac_pci_controller_ops;

	disp_name = शून्य;

	/* 64 bits only bridges */
#अगर_घोषित CONFIG_PPC64
	अगर (of_device_is_compatible(dev, "u3-agp")) अणु
		setup_u3_agp(hose);
		disp_name = "U3-AGP";
		primary = 0;
	पूर्ण अन्यथा अगर (of_device_is_compatible(dev, "u3-ht")) अणु
		setup_u3_ht(hose);
		disp_name = "U3-HT";
		primary = 1;
	पूर्ण अन्यथा अगर (of_device_is_compatible(dev, "u4-pcie")) अणु
		setup_u4_pcie(hose);
		disp_name = "U4-PCIE";
		primary = 0;
	पूर्ण
	prपूर्णांकk(KERN_INFO "Found %s PCI host bridge.  Firmware bus number:"
	       " %d->%d\n", disp_name, hose->first_busno, hose->last_busno);
#पूर्ण_अगर /* CONFIG_PPC64 */

	/* 32 bits only bridges */
#अगर_घोषित CONFIG_PPC32
	अगर (of_device_is_compatible(dev, "uni-north")) अणु
		primary = setup_uninorth(hose, &rsrc);
		disp_name = "UniNorth";
	पूर्ण अन्यथा अगर (of_node_name_eq(dev, "pci")) अणु
		/* XXX assume this is a mpc106 (grackle) */
		setup_grackle(hose);
		disp_name = "Grackle (MPC106)";
	पूर्ण अन्यथा अगर (of_node_name_eq(dev, "bandit")) अणु
		setup_bandit(hose, &rsrc);
		disp_name = "Bandit";
	पूर्ण अन्यथा अगर (of_node_name_eq(dev, "chaos")) अणु
		setup_chaos(hose, &rsrc);
		disp_name = "Chaos";
		primary = 0;
	पूर्ण
	prपूर्णांकk(KERN_INFO "Found %s PCI host bridge at 0x%016llx. "
	       "Firmware bus number: %d->%d\n",
		disp_name, (अचिन्हित दीर्घ दीर्घ)rsrc.start, hose->first_busno,
		hose->last_busno);
#पूर्ण_अगर /* CONFIG_PPC32 */

	DBG(" ->Hose at 0x%p, cfg_addr=0x%p,cfg_data=0x%p\n",
		hose, hose->cfg_addr, hose->cfg_data);

	/* Interpret the "ranges" property */
	/* This also maps the I/O region and sets isa_io/mem_base */
	pci_process_bridge_OF_ranges(hose, dev, primary);

	/* Fixup "bus-range" OF property */
	fixup_bus_range(dev);

	/* create pci_dn's क्रम DT nodes under this PHB */
	अगर (IS_ENABLED(CONFIG_PPC64))
		pci_devs_phb_init_dynamic(hose);

	वापस 0;
पूर्ण

व्योम pmac_pci_irq_fixup(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_PPC32
	/* Fixup पूर्णांकerrupt क्रम the modem/ethernet combo controller.
	 * on machines with a second ohare chip.
	 * The number in the device tree (27) is bogus (correct क्रम
	 * the ethernet-only board but not the combo ethernet/modem
	 * board). The real पूर्णांकerrupt is 28 on the second controller
	 * -> 28+32 = 60.
	 */
	अगर (has_second_ohare &&
	    dev->venकरोr == PCI_VENDOR_ID_DEC &&
	    dev->device == PCI_DEVICE_ID_DEC_TULIP_PLUS) अणु
		dev->irq = irq_create_mapping(शून्य, 60);
		irq_set_irq_type(dev->irq, IRQ_TYPE_LEVEL_LOW);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 */
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल पूर्णांक pmac_pci_root_bridge_prepare(काष्ठा pci_host_bridge *bridge)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(bridge->bus);
	काष्ठा device_node *np, *child;

	अगर (hose != u3_agp)
		वापस 0;

	/* Fixup the PCI<->OF mapping क्रम U3 AGP due to bus rक्रमागतbering. We
	 * assume there is no P2P bridge on the AGP bus, which should be a
	 * safe assumptions क्रम now. We should करो something better in the
	 * future though
	 */
	np = hose->dn;
	PCI_DN(np)->busno = 0xf0;
	क्रम_each_child_of_node(np, child)
		PCI_DN(child)->busno = 0xf0;

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

व्योम __init pmac_pci_init(व्योम)
अणु
	काष्ठा device_node *np, *root;
	काष्ठा device_node *ht __maybe_unused = शून्य;

	pci_set_flags(PCI_CAN_SKIP_ISA_ALIGN);

	root = of_find_node_by_path("/");
	अगर (root == शून्य) अणु
		prपूर्णांकk(KERN_CRIT "pmac_pci_init: can't find root "
		       "of device tree\n");
		वापस;
	पूर्ण
	क्रम_each_child_of_node(root, np) अणु
		अगर (of_node_name_eq(np, "bandit")
		    || of_node_name_eq(np, "chaos")
		    || of_node_name_eq(np, "pci")) अणु
			अगर (pmac_add_bridge(np) == 0)
				of_node_get(np);
		पूर्ण
		अगर (of_node_name_eq(np, "ht")) अणु
			of_node_get(np);
			ht = np;
		पूर्ण
	पूर्ण
	of_node_put(root);

#अगर_घोषित CONFIG_PPC64
	/* Probe HT last as it relies on the agp resources to be alपढ़ोy
	 * setup
	 */
	अगर (ht && pmac_add_bridge(ht) != 0)
		of_node_put(ht);

	ppc_md.pcibios_root_bridge_prepare = pmac_pci_root_bridge_prepare;
	/* pmac_check_ht_link(); */

#अन्यथा /* CONFIG_PPC64 */
	init_p2pbridge();
	init_second_ohare();
	fixup_nec_usb2();

	/* We are still having some issues with the Xserve G4, enabling
	 * some offset between bus number and करोमुख्यs क्रम now when we
	 * assign all busses should help क्रम now
	 */
	अगर (pci_has_flag(PCI_REASSIGN_ALL_BUS))
		pcibios_assign_bus_offset = 0x10;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_PPC32
अटल bool pmac_pci_enable_device_hook(काष्ठा pci_dev *dev)
अणु
	काष्ठा device_node* node;
	पूर्णांक updatecfg = 0;
	पूर्णांक uninorth_child;

	node = pci_device_to_OF_node(dev);

	/* We करोn't want to enable USB controllers असलent from the OF tree
	 * (iBook second controller)
	 */
	अगर (dev->venकरोr == PCI_VENDOR_ID_APPLE
	    && dev->class == PCI_CLASS_SERIAL_USB_OHCI
	    && !node) अणु
		prपूर्णांकk(KERN_INFO "Apple USB OHCI %s disabled by firmware\n",
		       pci_name(dev));
		वापस false;
	पूर्ण

	अगर (!node)
		वापस true;

	uninorth_child = node->parent &&
		of_device_is_compatible(node->parent, "uni-north");

	/* Firewire & GMAC were disabled after PCI probe, the driver is
	 * claiming them, we must re-enable them now.
	 */
	अगर (uninorth_child && of_node_name_eq(node, "firewire") &&
	    (of_device_is_compatible(node, "pci106b,18") ||
	     of_device_is_compatible(node, "pci106b,30") ||
	     of_device_is_compatible(node, "pci11c1,5811"))) अणु
		pmac_call_feature(PMAC_FTR_1394_CABLE_POWER, node, 0, 1);
		pmac_call_feature(PMAC_FTR_1394_ENABLE, node, 0, 1);
		updatecfg = 1;
	पूर्ण
	अगर (uninorth_child && of_node_name_eq(node, "ethernet") &&
	    of_device_is_compatible(node, "gmac")) अणु
		pmac_call_feature(PMAC_FTR_GMAC_ENABLE, node, 0, 1);
		updatecfg = 1;
	पूर्ण

	/*
	 * Fixup various header fields on 32 bits. We करोn't करो that on
	 * 64 bits as some of these have strange values behind the HT
	 * bridge and we must not, क्रम example, enable MWI or set the
	 * cache line size on them.
	 */
	अगर (updatecfg) अणु
		u16 cmd;

		pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
		cmd |= PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER
			| PCI_COMMAND_INVALIDATE;
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
		pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 16);

		pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE,
				      L1_CACHE_BYTES >> 2);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम pmac_pci_fixup_ohci(काष्ठा pci_dev *dev)
अणु
	काष्ठा device_node *node = pci_device_to_OF_node(dev);

	/* We करोn't want to assign resources to USB controllers
	 * असलent from the OF tree (iBook second controller)
	 */
	अगर (dev->class == PCI_CLASS_SERIAL_USB_OHCI && !node)
		dev->resource[0].flags = 0;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_APPLE, PCI_ANY_ID, pmac_pci_fixup_ohci);

/* We घातer करोwn some devices after they have been probed. They'll
 * be घातered back on later on
 */
व्योम __init pmac_pcibios_after_init(व्योम)
अणु
	काष्ठा device_node* nd;

	क्रम_each_node_by_name(nd, "firewire") अणु
		अगर (nd->parent && (of_device_is_compatible(nd, "pci106b,18") ||
				   of_device_is_compatible(nd, "pci106b,30") ||
				   of_device_is_compatible(nd, "pci11c1,5811"))
		    && of_device_is_compatible(nd->parent, "uni-north")) अणु
			pmac_call_feature(PMAC_FTR_1394_ENABLE, nd, 0, 0);
			pmac_call_feature(PMAC_FTR_1394_CABLE_POWER, nd, 0, 0);
		पूर्ण
	पूर्ण
	क्रम_each_node_by_name(nd, "ethernet") अणु
		अगर (nd->parent && of_device_is_compatible(nd, "gmac")
		    && of_device_is_compatible(nd->parent, "uni-north"))
			pmac_call_feature(PMAC_FTR_GMAC_ENABLE, nd, 0, 0);
	पूर्ण
पूर्ण

अटल व्योम pmac_pci_fixup_cardbus(काष्ठा pci_dev *dev)
अणु
	अगर (!machine_is(घातermac))
		वापस;
	/*
	 * Fix the पूर्णांकerrupt routing on the various cardbus bridges
	 * used on घातerbooks
	 */
	अगर (dev->venकरोr != PCI_VENDOR_ID_TI)
		वापस;
	अगर (dev->device == PCI_DEVICE_ID_TI_1130 ||
	    dev->device == PCI_DEVICE_ID_TI_1131) अणु
		u8 val;
		/* Enable PCI पूर्णांकerrupt */
		अगर (pci_पढ़ो_config_byte(dev, 0x91, &val) == 0)
			pci_ग_लिखो_config_byte(dev, 0x91, val | 0x30);
		/* Disable ISA पूर्णांकerrupt mode */
		अगर (pci_पढ़ो_config_byte(dev, 0x92, &val) == 0)
			pci_ग_लिखो_config_byte(dev, 0x92, val & ~0x06);
	पूर्ण
	अगर (dev->device == PCI_DEVICE_ID_TI_1210 ||
	    dev->device == PCI_DEVICE_ID_TI_1211 ||
	    dev->device == PCI_DEVICE_ID_TI_1410 ||
	    dev->device == PCI_DEVICE_ID_TI_1510) अणु
		u8 val;
		/* 0x8c == TI122X_IRQMUX, 2 says to route the INTA
		   संकेत out the MFUNC0 pin */
		अगर (pci_पढ़ो_config_byte(dev, 0x8c, &val) == 0)
			pci_ग_लिखो_config_byte(dev, 0x8c, (val & ~0x0f) | 2);
		/* Disable ISA पूर्णांकerrupt mode */
		अगर (pci_पढ़ो_config_byte(dev, 0x92, &val) == 0)
			pci_ग_लिखो_config_byte(dev, 0x92, val & ~0x06);
	पूर्ण
पूर्ण

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_TI, PCI_ANY_ID, pmac_pci_fixup_cardbus);

अटल व्योम pmac_pci_fixup_pciata(काष्ठा pci_dev *dev)
अणु
       u8 progअगर = 0;

       /*
        * On PowerMacs, we try to चयन any PCI ATA controller to
	* fully native mode
        */
	अगर (!machine_is(घातermac))
		वापस;

	/* Some controllers करोn't have the class IDE */
	अगर (dev->venकरोr == PCI_VENDOR_ID_PROMISE)
		चयन(dev->device) अणु
		हाल PCI_DEVICE_ID_PROMISE_20246:
		हाल PCI_DEVICE_ID_PROMISE_20262:
		हाल PCI_DEVICE_ID_PROMISE_20263:
		हाल PCI_DEVICE_ID_PROMISE_20265:
		हाल PCI_DEVICE_ID_PROMISE_20267:
		हाल PCI_DEVICE_ID_PROMISE_20268:
		हाल PCI_DEVICE_ID_PROMISE_20269:
		हाल PCI_DEVICE_ID_PROMISE_20270:
		हाल PCI_DEVICE_ID_PROMISE_20271:
		हाल PCI_DEVICE_ID_PROMISE_20275:
		हाल PCI_DEVICE_ID_PROMISE_20276:
		हाल PCI_DEVICE_ID_PROMISE_20277:
			जाओ good;
		पूर्ण
	/* Others, check PCI class */
	अगर ((dev->class >> 8) != PCI_CLASS_STORAGE_IDE)
		वापस;
 good:
	pci_पढ़ो_config_byte(dev, PCI_CLASS_PROG, &progअगर);
	अगर ((progअगर & 5) != 5) अणु
		prपूर्णांकk(KERN_INFO "PCI: %s Forcing PCI IDE into native mode\n",
		       pci_name(dev));
		(व्योम) pci_ग_लिखो_config_byte(dev, PCI_CLASS_PROG, progअगर|5);
		अगर (pci_पढ़ो_config_byte(dev, PCI_CLASS_PROG, &progअगर) ||
		    (progअगर & 5) != 5)
			prपूर्णांकk(KERN_ERR "Rewrite of PROGIF failed !\n");
		अन्यथा अणु
			/* Clear IO BARs, they will be reasचिन्हित */
			pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_0, 0);
			pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_1, 0);
			pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_2, 0);
			pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_3, 0);
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_ANY_ID, PCI_ANY_ID, pmac_pci_fixup_pciata);
#पूर्ण_अगर /* CONFIG_PPC32 */

/*
 * Disable second function on K2-SATA, it's broken
 * and disable IO BARs on first one
 */
अटल व्योम fixup_k2_sata(काष्ठा pci_dev* dev)
अणु
	पूर्णांक i;
	u16 cmd;

	अगर (PCI_FUNC(dev->devfn) > 0) अणु
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
		cmd &= ~(PCI_COMMAND_IO | PCI_COMMAND_MEMORY);
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
		क्रम (i = 0; i < 6; i++) अणु
			dev->resource[i].start = dev->resource[i].end = 0;
			dev->resource[i].flags = 0;
			pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_0 + 4 * i,
					       0);
		पूर्ण
	पूर्ण अन्यथा अणु
		pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
		cmd &= ~PCI_COMMAND_IO;
		pci_ग_लिखो_config_word(dev, PCI_COMMAND, cmd);
		क्रम (i = 0; i < 5; i++) अणु
			dev->resource[i].start = dev->resource[i].end = 0;
			dev->resource[i].flags = 0;
			pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_0 + 4 * i,
					       0);
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_SERVERWORKS, 0x0240, fixup_k2_sata);

/*
 * On U4 (aka CPC945) the PCIe root complex "P2P" bridge resource ranges aren't
 * configured by the firmware. The bridge itself seems to ignore them but it
 * causes problems with Linux which then re-assigns devices below the bridge,
 * thus changing addresses of those devices from what was in the device-tree,
 * which sucks when those are video cards using offb
 *
 * We could just mark it transparent but I prefer fixing up the resources to
 * properly show what's going on here, as I have some करोubts about having them
 * badly configured potentially being an issue क्रम DMA.
 *
 * We leave PIO alone, it seems to be fine
 *
 * Oh and there's another funny bug. The OF properties advertize the region
 * 0xf1000000..0xf1ffffff as being क्रमwarded as memory space. But that's
 * actually not true, this region is the memory mapped config space. So we
 * also need to filter it out or we'll map things in the wrong place.
 */
अटल व्योम fixup_u4_pcie(काष्ठा pci_dev* dev)
अणु
	काष्ठा pci_controller *host = pci_bus_to_host(dev->bus);
	काष्ठा resource *region = शून्य;
	u32 reg;
	पूर्णांक i;

	/* Only करो that on PowerMac */
	अगर (!machine_is(घातermac))
		वापस;

	/* Find the largest MMIO region */
	क्रम (i = 0; i < 3; i++) अणु
		काष्ठा resource *r = &host->mem_resources[i];
		अगर (!(r->flags & IORESOURCE_MEM))
			जारी;
		/* Skip the 0xf0xxxxxx..f2xxxxxx regions, we know they
		 * are reserved by HW क्रम other things
		 */
		अगर (r->start >= 0xf0000000 && r->start < 0xf3000000)
			जारी;
		अगर (!region || resource_size(r) > resource_size(region))
			region = r;
	पूर्ण
	/* Nothing found, bail */
	अगर (!region)
		वापस;

	/* Prपूर्णांक things out */
	prपूर्णांकk(KERN_INFO "PCI: Fixup U4 PCIe bridge range: %pR\n", region);

	/* Fixup bridge config space. We know it's a Mac, resource aren't
	 * offset so let's just blast them as-is. We also know that they
	 * fit in 32 bits
	 */
	reg = ((region->start >> 16) & 0xfff0) | (region->end & 0xfff00000);
	pci_ग_लिखो_config_dword(dev, PCI_MEMORY_BASE, reg);
	pci_ग_लिखो_config_dword(dev, PCI_PREF_BASE_UPPER32, 0);
	pci_ग_लिखो_config_dword(dev, PCI_PREF_LIMIT_UPPER32, 0);
	pci_ग_लिखो_config_dword(dev, PCI_PREF_MEMORY_BASE, 0);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_U4_PCIE, fixup_u4_pcie);

#अगर_घोषित CONFIG_PPC64
अटल पूर्णांक pmac_pci_probe_mode(काष्ठा pci_bus *bus)
अणु
	काष्ठा device_node *node = pci_bus_to_OF_node(bus);

	/* We need to use normal PCI probing क्रम the AGP bus,
	 * since the device क्रम the AGP bridge isn't in the tree.
	 * Same क्रम the PCIe host on U4 and the HT host bridge.
	 */
	अगर (bus->self == शून्य && (of_device_is_compatible(node, "u3-agp") ||
				  of_device_is_compatible(node, "u4-pcie") ||
				  of_device_is_compatible(node, "u3-ht")))
		वापस PCI_PROBE_NORMAL;
	वापस PCI_PROBE_DEVTREE;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

काष्ठा pci_controller_ops pmac_pci_controller_ops = अणु
#अगर_घोषित CONFIG_PPC64
	.probe_mode		= pmac_pci_probe_mode,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC32
	.enable_device_hook	= pmac_pci_enable_device_hook,
#पूर्ण_अगर
पूर्ण;
