<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC85xx setup and early boot code plus other अक्रमom bits.
 *
 * Maपूर्णांकained by Kumar Gala (see MAINTAINERS क्रम contact inक्रमmation)
 *
 * Copyright 2005, 2011-2012 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/reboot.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/major.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/initrd.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/page.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/ipic.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/irq.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/i8259.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>

#समावेश "mpc85xx.h"

/*
 * The CDS board contains an FPGA/CPLD called "Cadmus", which collects
 * various logic and perक्रमms प्रणाली control functions.
 * Here is the FPGA/CPLD रेजिस्टर map.
 */
काष्ठा cadmus_reg अणु
	u8 cm_ver;		/* Board version */
	u8 cm_csr;		/* General control/status */
	u8 cm_rst;		/* Reset control */
	u8 cm_hsclk;	/* High speed घड़ी */
	u8 cm_hsxclk;	/* High speed घड़ी extended */
	u8 cm_led;		/* LED data */
	u8 cm_pci;		/* PCI control/status */
	u8 cm_dma;		/* DMA control */
	u8 res[248];	/* Total 256 bytes */
पूर्ण;

अटल काष्ठा cadmus_reg *cadmus;

#अगर_घोषित CONFIG_PCI

#घोषणा ARCADIA_HOST_BRIDGE_IDSEL	17
#घोषणा ARCADIA_2ND_BRIDGE_IDSEL	3

अटल पूर्णांक mpc85xx_exclude_device(काष्ठा pci_controller *hose,
				  u_अक्षर bus, u_अक्षर devfn)
अणु
	/* We explicitly करो not go past the Tundra 320 Bridge */
	अगर ((bus == 1) && (PCI_SLOT(devfn) == ARCADIA_2ND_BRIDGE_IDSEL))
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अगर ((bus == 0) && (PCI_SLOT(devfn) == ARCADIA_2ND_BRIDGE_IDSEL))
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	अन्यथा
		वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक mpc85xx_cds_restart(काष्ठा notअगरier_block *this,
			       अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	काष्ठा pci_dev *dev;
	u_अक्षर पंचांगp;

	अगर ((dev = pci_get_device(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C686,
					शून्य))) अणु

		/* Use the VIA Super Southbridge to क्रमce a PCI reset */
		pci_पढ़ो_config_byte(dev, 0x47, &पंचांगp);
		pci_ग_लिखो_config_byte(dev, 0x47, पंचांगp | 1);

		/* Flush the outbound PCI ग_लिखो queues */
		pci_पढ़ो_config_byte(dev, 0x47, &पंचांगp);

		/*
		 *  At this poपूर्णांक, the hardware reset should have triggered.
		 *  However, अगर it करोesn't work क्रम some mysterious reason,
		 *  just fall through to the शेष reset below.
		 */

		pci_dev_put(dev);
	पूर्ण

	/*
	 *  If we can't find the VIA chip (maybe the P2P bridge is
	 *  disabled) or the VIA chip reset didn't work, just वापस
	 *  and let शेष reset sequence happen.
	 */
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक mpc85xx_cds_restart_रेजिस्टर(व्योम)
अणु
	अटल काष्ठा notअगरier_block restart_handler;

	restart_handler.notअगरier_call = mpc85xx_cds_restart;
	restart_handler.priority = 192;

	वापस रेजिस्टर_restart_handler(&restart_handler);
पूर्ण
machine_arch_initcall(mpc85xx_cds, mpc85xx_cds_restart_रेजिस्टर);


अटल व्योम __init mpc85xx_cds_pci_irq_fixup(काष्ठा pci_dev *dev)
अणु
	u_अक्षर c;
	अगर (dev->venकरोr == PCI_VENDOR_ID_VIA) अणु
		चयन (dev->device) अणु
		हाल PCI_DEVICE_ID_VIA_82C586_1:
			/*
			 * U-Boot करोes not set the enable bits
			 * क्रम the IDE device. Force them on here.
			 */
			pci_पढ़ो_config_byte(dev, 0x40, &c);
			c |= 0x03; /* IDE: Chip Enable Bits */
			pci_ग_लिखो_config_byte(dev, 0x40, c);

			/*
			 * Since only primary पूर्णांकerface works, क्रमce the
			 * IDE function to standard primary IDE पूर्णांकerrupt
			 * w/ 8259 offset
			 */
			dev->irq = 14;
			pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, dev->irq);
			अवरोध;
		/*
		 * Force legacy USB पूर्णांकerrupt routing
		 */
		हाल PCI_DEVICE_ID_VIA_82C586_2:
		/* There are two USB controllers.
		 * Identअगरy them by functon number
		 */
			अगर (PCI_FUNC(dev->devfn) == 3)
				dev->irq = 11;
			अन्यथा
				dev->irq = 10;
			pci_ग_लिखो_config_byte(dev, PCI_INTERRUPT_LINE, dev->irq);
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम skip_fake_bridge(काष्ठा pci_dev *dev)
अणु
	/* Make it an error to skip the fake bridge
	 * in pci_setup_device() in probe.c */
	dev->hdr_type = 0x7f;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(0x1957, 0x3fff, skip_fake_bridge);
DECLARE_PCI_FIXUP_EARLY(0x3fff, 0x1957, skip_fake_bridge);
DECLARE_PCI_FIXUP_EARLY(0xff3f, 0x5719, skip_fake_bridge);

#घोषणा PCI_DEVICE_ID_IDT_TSI310	0x01a7

/*
 * Fix Tsi310 PCI-X bridge resource.
 * Force the bridge to खोलो a winकरोw from 0x0000-0x1fff in PCI I/O space.
 * This allows legacy I/O(i8259, etc) on the VIA southbridge to be accessed.
 */
व्योम mpc85xx_cds_fixup_bus(काष्ठा pci_bus *bus)
अणु
	काष्ठा pci_dev *dev = bus->self;
	काष्ठा resource *res = bus->resource[0];

	अगर (dev != शून्य &&
	    dev->venकरोr == PCI_VENDOR_ID_IBM &&
	    dev->device == PCI_DEVICE_ID_IDT_TSI310) अणु
		अगर (res) अणु
			res->start = 0;
			res->end   = 0x1fff;
			res->flags = IORESOURCE_IO;
			pr_info("mpc85xx_cds: PCI bridge resource fixup applied\n");
			pr_info("mpc85xx_cds: %pR\n", res);
		पूर्ण
	पूर्ण

	fsl_pcibios_fixup_bus(bus);
पूर्ण

#अगर_घोषित CONFIG_PPC_I8259
अटल व्योम mpc85xx_8259_cascade_handler(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक cascade_irq = i8259_irq();

	अगर (cascade_irq)
		/* handle an पूर्णांकerrupt from the 8259 */
		generic_handle_irq(cascade_irq);

	/* check क्रम any पूर्णांकerrupts from the shared IRQ line */
	handle_fasteoi_irq(desc);
पूर्ण

अटल irqवापस_t mpc85xx_8259_cascade_action(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर /* PPC_I8259 */
#पूर्ण_अगर /* CONFIG_PCI */

अटल व्योम __init mpc85xx_cds_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic;
	mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN,
			0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
पूर्ण

#अगर defined(CONFIG_PPC_I8259) && defined(CONFIG_PCI)
अटल पूर्णांक mpc85xx_cds_8259_attach(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा device_node *np = शून्य;
	काष्ठा device_node *cascade_node = शून्य;
	पूर्णांक cascade_irq;

	/* Initialize the i8259 controller */
	क्रम_each_node_by_type(np, "interrupt-controller")
		अगर (of_device_is_compatible(np, "chrp,iic")) अणु
			cascade_node = np;
			अवरोध;
		पूर्ण

	अगर (cascade_node == शून्य) अणु
		prपूर्णांकk(KERN_DEBUG "Could not find i8259 PIC\n");
		वापस -ENODEV;
	पूर्ण

	cascade_irq = irq_of_parse_and_map(cascade_node, 0);
	अगर (!cascade_irq) अणु
		prपूर्णांकk(KERN_ERR "Failed to map cascade interrupt\n");
		वापस -ENXIO;
	पूर्ण

	i8259_init(cascade_node, 0);
	of_node_put(cascade_node);

	/*
	 *  Hook the पूर्णांकerrupt to make sure desc->action is never शून्य.
	 *  This is required to ensure that the पूर्णांकerrupt करोes not get
	 *  disabled when the last user of the shared IRQ line मुक्तs their
	 *  पूर्णांकerrupt.
	 */
	ret = request_irq(cascade_irq, mpc85xx_8259_cascade_action,
			  IRQF_SHARED | IRQF_NO_THREAD, "8259 cascade",
			  cascade_node);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Failed to setup cascade interrupt\n");
		वापस ret;
	पूर्ण

	/* Success. Connect our low-level cascade handler. */
	irq_set_handler(cascade_irq, mpc85xx_8259_cascade_handler);

	वापस 0;
पूर्ण
machine_device_initcall(mpc85xx_cds, mpc85xx_cds_8259_attach);

#पूर्ण_अगर /* CONFIG_PPC_I8259 */

अटल व्योम mpc85xx_cds_pci_assign_primary(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	काष्ठा device_node *np;

	अगर (fsl_pci_primary)
		वापस;

	/*
	 * MPC85xx_CDS has ISA bridge but unक्रमtunately there is no
	 * isa node in device tree. We now looking क्रम i8259 node as
	 * a workaround क्रम such a broken device tree. This routine
	 * is क्रम complying to all device trees.
	 */
	np = of_find_node_by_name(शून्य, "i8259");
	जबतक ((fsl_pci_primary = of_get_parent(np))) अणु
		of_node_put(np);
		np = fsl_pci_primary;

		अगर ((of_device_is_compatible(np, "fsl,mpc8540-pci") ||
		    of_device_is_compatible(np, "fsl,mpc8548-pcie")) &&
		    of_device_is_available(np))
			वापस;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init mpc85xx_cds_setup_arch(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक cds_pci_slot;

	अगर (ppc_md.progress)
		ppc_md.progress("mpc85xx_cds_setup_arch()", 0);

	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc8548cds-fpga");
	अगर (!np) अणु
		pr_err("Could not find FPGA node.\n");
		वापस;
	पूर्ण

	cadmus = of_iomap(np, 0);
	of_node_put(np);
	अगर (!cadmus) अणु
		pr_err("Fail to map FPGA area.\n");
		वापस;
	पूर्ण

	अगर (ppc_md.progress) अणु
		अक्षर buf[40];
		cds_pci_slot = ((in_8(&cadmus->cm_csr) >> 6) & 0x3) + 1;
		snम_लिखो(buf, 40, "CDS Version = 0x%x in slot %d\n",
				in_8(&cadmus->cm_ver), cds_pci_slot);
		ppc_md.progress(buf, 0);
	पूर्ण

#अगर_घोषित CONFIG_PCI
	ppc_md.pci_irq_fixup = mpc85xx_cds_pci_irq_fixup;
	ppc_md.pci_exclude_device = mpc85xx_exclude_device;
#पूर्ण_अगर

	mpc85xx_cds_pci_assign_primary();
	fsl_pci_assign_primary();
पूर्ण

अटल व्योम mpc85xx_cds_show_cpuinfo(काष्ठा seq_file *m)
अणु
	uपूर्णांक pvid, svid, phid1;

	pvid = mfspr(SPRN_PVR);
	svid = mfspr(SPRN_SVR);

	seq_म_लिखो(m, "Vendor\t\t: Freescale Semiconductor\n");
	seq_म_लिखो(m, "Machine\t\t: MPC85xx CDS (0x%x)\n",
			in_8(&cadmus->cm_ver));
	seq_म_लिखो(m, "PVR\t\t: 0x%x\n", pvid);
	seq_म_लिखो(m, "SVR\t\t: 0x%x\n", svid);

	/* Display cpu Pll setting */
	phid1 = mfspr(SPRN_HID1);
	seq_म_लिखो(m, "PLL setting\t: 0x%x\n", ((phid1 >> 24) & 0x3f));
पूर्ण


/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc85xx_cds_probe(व्योम)
अणु
	वापस of_machine_is_compatible("MPC85xxCDS");
पूर्ण

machine_arch_initcall(mpc85xx_cds, mpc85xx_common_publish_devices);

define_machine(mpc85xx_cds) अणु
	.name		= "MPC85xx CDS",
	.probe		= mpc85xx_cds_probe,
	.setup_arch	= mpc85xx_cds_setup_arch,
	.init_IRQ	= mpc85xx_cds_pic_init,
	.show_cpuinfo	= mpc85xx_cds_show_cpuinfo,
	.get_irq	= mpic_get_irq,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= mpc85xx_cds_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.calibrate_decr = generic_calibrate_decr,
	.progress	= udbg_progress,
पूर्ण;
