<शैली गुरु>
/*
 * PCI support क्रम Xilinx plbv46_pci soft-core which can be used on
 * Xilinx Virtex ML410 / ML510 boards.
 *
 * Copyright 2009 Roderick Colenbअक्रमer
 * Copyright 2009 Secret Lab Technologies Ltd.
 *
 * The pci bridge fixup code was copied from ppc4xx_pci.c and was written
 * by Benjamin Herrenschmidt.
 * Copyright 2007 Ben. Herrenschmidt <benh@kernel.crashing.org>, IBM Corp.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/ioport.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>

#घोषणा XPLB_PCI_ADDR 0x10c
#घोषणा XPLB_PCI_DATA 0x110
#घोषणा XPLB_PCI_BUS  0x114

#घोषणा PCI_HOST_ENABLE_CMD (PCI_COMMAND_SERR | PCI_COMMAND_PARITY | \
				PCI_COMMAND_MASTER | PCI_COMMAND_MEMORY)

अटल काष्ठा of_device_id xilinx_pci_match[] = अणु
	अणु .compatible = "xlnx,plbv46-pci-1.03.a", पूर्ण,
	अणुपूर्ण
पूर्ण;

/**
 * xilinx_pci_fixup_bridge - Block Xilinx PHB configuration.
 */
अटल व्योम xilinx_pci_fixup_bridge(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose;
	पूर्णांक i;

	अगर (dev->devfn || dev->bus->self)
		वापस;

	hose = pci_bus_to_host(dev->bus);
	अगर (!hose)
		वापस;

	अगर (!of_match_node(xilinx_pci_match, hose->dn))
		वापस;

	/* Hide the PCI host BARs from the kernel as their content करोesn't
	 * fit well in the resource management
	 */
	क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
		dev->resource[i].start = 0;
		dev->resource[i].end = 0;
		dev->resource[i].flags = 0;
	पूर्ण

	dev_info(&dev->dev, "Hiding Xilinx plb-pci host bridge resources %s\n",
		 pci_name(dev));
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_ANY_ID, PCI_ANY_ID, xilinx_pci_fixup_bridge);

#अगर_घोषित DEBUG
/**
 * xilinx_pci_exclude_device - Don't करो config access क्रम non-root bus
 *
 * This is a hack.  Config access to any bus other than bus 0 करोes not
 * currently work on the ML510 so we prevent it here.
 */
अटल पूर्णांक
xilinx_pci_exclude_device(काष्ठा pci_controller *hose, u_अक्षर bus, u8 devfn)
अणु
	वापस (bus != 0);
पूर्ण

/**
 * xilinx_early_pci_scan - List pci config space क्रम available devices
 *
 * List pci devices in very early phase.
 */
अटल व्योम __init xilinx_early_pci_scan(काष्ठा pci_controller *hose)
अणु
	u32 bus = 0;
	u32 val, dev, func, offset;

	/* Currently we have only 2 device connected - up-to 32 devices */
	क्रम (dev = 0; dev < 2; dev++) अणु
		/* List only first function number - up-to 8 functions */
		क्रम (func = 0; func < 1; func++) अणु
			pr_info("%02x:%02x:%02x", bus, dev, func);
			/* पढ़ो the first 64 standardized bytes */
			/* Up-to 192 bytes can be list of capabilities */
			क्रम (offset = 0; offset < 64; offset += 4) अणु
				early_पढ़ो_config_dword(hose, bus,
					PCI_DEVFN(dev, func), offset, &val);
				अगर (offset == 0 && val == 0xFFFFFFFF) अणु
					pr_cont("\nABSENT");
					अवरोध;
				पूर्ण
				अगर (!(offset % 0x10))
					pr_cont("\n%04x:    ", offset);

				pr_cont("%08x  ", val);
			पूर्ण
			pr_info("\n");
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init xilinx_early_pci_scan(काष्ठा pci_controller *hose)
अणु
पूर्ण
#पूर्ण_अगर

/**
 * xilinx_pci_init - Find and रेजिस्टर a Xilinx PCI host bridge
 */
व्योम __init xilinx_pci_init(व्योम)
अणु
	काष्ठा pci_controller *hose;
	काष्ठा resource r;
	व्योम __iomem *pci_reg;
	काष्ठा device_node *pci_node;

	pci_node = of_find_matching_node(शून्य, xilinx_pci_match);
	अगर (!pci_node)
		वापस;

	अगर (of_address_to_resource(pci_node, 0, &r)) अणु
		pr_err("xilinx-pci: cannot resolve base address\n");
		वापस;
	पूर्ण

	hose = pcibios_alloc_controller(pci_node);
	अगर (!hose) अणु
		pr_err("xilinx-pci: pcibios_alloc_controller() failed\n");
		वापस;
	पूर्ण

	/* Setup config space */
	setup_indirect_pci(hose, r.start + XPLB_PCI_ADDR,
			   r.start + XPLB_PCI_DATA,
			   INसूचीECT_TYPE_SET_CFG_TYPE);

	/* According to the xilinx plbv46_pci करोcumentation the soft-core starts
	 * a self-init when the bus master enable bit is set. Without this bit
	 * set the pci bus can't be scanned.
	 */
	early_ग_लिखो_config_word(hose, 0, 0, PCI_COMMAND, PCI_HOST_ENABLE_CMD);

	/* Set the max latency समयr to 255 */
	early_ग_लिखो_config_byte(hose, 0, 0, PCI_LATENCY_TIMER, 0xff);

	/* Set the max bus number to 255, and bus/subbus no's to 0 */
	pci_reg = of_iomap(pci_node, 0);
	WARN_ON(!pci_reg);
	out_be32(pci_reg + XPLB_PCI_BUS, 0x000000ff);
	iounmap(pci_reg);

	/* Register the host bridge with the linux kernel! */
	pci_process_bridge_OF_ranges(hose, pci_node,
					INसूचीECT_TYPE_SET_CFG_TYPE);

	pr_info("xilinx-pci: Registered PCI host bridge\n");
	xilinx_early_pci_scan(hose);
पूर्ण
