<शैली गुरु>
/*
 * Cobalt Qube/Raq PCI support
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1996, 1997, 2002, 2003 by Ralf Baechle
 * Copyright (C) 2001, 2002, 2003 by Liam Davies (ldavies@agile.tv)
 */
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/gt64120.h>

#समावेश <cobalt.h>
#समावेश <irq.h>

/*
 * PCI slot numbers
 */
#घोषणा COBALT_PCICONF_CPU	0x06
#घोषणा COBALT_PCICONF_ETH0	0x07
#घोषणा COBALT_PCICONF_RAQSCSI	0x08
#घोषणा COBALT_PCICONF_VIA	0x09
#घोषणा COBALT_PCICONF_PCISLOT	0x0A
#घोषणा COBALT_PCICONF_ETH1	0x0C

/*
 * The Cobalt board ID inक्रमmation.  The boards have an ID number wired
 * पूर्णांकo the VIA that is available in the high nibble of रेजिस्टर 94.
 */
#घोषणा VIA_COBALT_BRD_ID_REG  0x94
#घोषणा VIA_COBALT_BRD_REG_to_ID(reg)	((अचिन्हित अक्षर)(reg) >> 4)

अटल व्योम qube_raq_galileo_early_fixup(काष्ठा pci_dev *dev)
अणु
	अगर (dev->devfn == PCI_DEVFN(0, 0) &&
		(dev->class >> 8) == PCI_CLASS_MEMORY_OTHER) अणु

		dev->class = (PCI_CLASS_BRIDGE_HOST << 8) | (dev->class & 0xff);

		prपूर्णांकk(KERN_INFO "Galileo: fixed bridge class\n");
	पूर्ण
पूर्ण

DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_MARVELL, PCI_DEVICE_ID_MARVELL_GT64111,
	 qube_raq_galileo_early_fixup);

अटल व्योम qube_raq_via_bmIDE_fixup(काष्ठा pci_dev *dev)
अणु
	अचिन्हित लघु cfgword;
	अचिन्हित अक्षर lt;

	/* Enable Bus Mastering and fast back to back. */
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cfgword);
	cfgword |= (PCI_COMMAND_FAST_BACK | PCI_COMMAND_MASTER);
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, cfgword);

	/* Enable both ide पूर्णांकerfaces. ROM only enables primary one.  */
	pci_ग_लिखो_config_byte(dev, 0x40, 0xb);

	/* Set latency समयr to reasonable value. */
	pci_पढ़ो_config_byte(dev, PCI_LATENCY_TIMER, &lt);
	अगर (lt < 64)
		pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 64);
	pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, 8);
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C586_1,
	 qube_raq_via_bmIDE_fixup);

अटल व्योम qube_raq_galileo_fixup(काष्ठा pci_dev *dev)
अणु
	अगर (dev->devfn != PCI_DEVFN(0, 0))
		वापस;

	/* Fix PCI latency-समयr and cache-line-size values in Galileo
	 * host bridge.
	 */
	pci_ग_लिखो_config_byte(dev, PCI_LATENCY_TIMER, 64);
	pci_ग_लिखो_config_byte(dev, PCI_CACHE_LINE_SIZE, 8);

	/*
	 * The code described by the comment below has been हटाओd
	 * as it causes bus mastering by the Ethernet controllers
	 * to अवरोध under any kind of network load. We always set
	 * the retry समयouts to their maximum.
	 *
	 * --x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--x--
	 *
	 * On all machines prior to Q2, we had the STOP line disconnected
	 * from Galileo to VIA on PCI.	The new Galileo करोes not function
	 * correctly unless we have it connected.
	 *
	 * Thereक्रमe we must set the disconnect/retry cycle values to
	 * something sensible when using the new Galileo.
	 */

	prपूर्णांकk(KERN_INFO "Galileo: revision %u\n", dev->revision);

#अगर 0
	अगर (dev->revision >= 0x10) अणु
		/* New Galileo, assumes PCI stop line to VIA is connected. */
		GT_WRITE(GT_PCI0_TOR_OFS, 0x4020);
	पूर्ण अन्यथा अगर (dev->revision == 0x1 || dev->revision == 0x2)
#पूर्ण_अगर
	अणु
		चिन्हित पूर्णांक समयo;
		/* XXX WE MUST DO THIS ELSE GALILEO LOCKS UP! -DaveM */
		समयo = GT_READ(GT_PCI0_TOR_OFS);
		/* Old Galileo, assumes PCI STOP line to VIA is disconnected. */
		GT_WRITE(GT_PCI0_TOR_OFS,
			(0xff << 16) |		/* retry count */
			(0xff << 8) |		/* समयout 1   */
			0xff);			/* समयout 0   */

		/* enable PCI retry exceeded पूर्णांकerrupt */
		GT_WRITE(GT_INTRMASK_OFS, GT_INTR_RETRYCTR0_MSK | GT_READ(GT_INTRMASK_OFS));
	पूर्ण
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_MARVELL, PCI_DEVICE_ID_MARVELL_GT64111,
	 qube_raq_galileo_fixup);

पूर्णांक cobalt_board_id;

अटल व्योम qube_raq_via_board_id_fixup(काष्ठा pci_dev *dev)
अणु
	u8 id;
	पूर्णांक retval;

	retval = pci_पढ़ो_config_byte(dev, VIA_COBALT_BRD_ID_REG, &id);
	अगर (retval) अणु
		panic("Cannot read board ID");
		वापस;
	पूर्ण

	cobalt_board_id = VIA_COBALT_BRD_REG_to_ID(id);

	prपूर्णांकk(KERN_INFO "Cobalt board ID: %d\n", cobalt_board_id);
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_82C586_0,
	 qube_raq_via_board_id_fixup);

अटल अक्षर irq_tab_qube1[] = अणु
  [COBALT_PCICONF_CPU]	   = 0,
  [COBALT_PCICONF_ETH0]	   = QUBE1_ETH0_IRQ,
  [COBALT_PCICONF_RAQSCSI] = SCSI_IRQ,
  [COBALT_PCICONF_VIA]	   = 0,
  [COBALT_PCICONF_PCISLOT] = PCISLOT_IRQ,
  [COBALT_PCICONF_ETH1]	   = 0
पूर्ण;

अटल अक्षर irq_tab_cobalt[] = अणु
  [COBALT_PCICONF_CPU]	   = 0,
  [COBALT_PCICONF_ETH0]	   = ETH0_IRQ,
  [COBALT_PCICONF_RAQSCSI] = SCSI_IRQ,
  [COBALT_PCICONF_VIA]	   = 0,
  [COBALT_PCICONF_PCISLOT] = PCISLOT_IRQ,
  [COBALT_PCICONF_ETH1]	   = ETH1_IRQ
पूर्ण;

अटल अक्षर irq_tab_raq2[] = अणु
  [COBALT_PCICONF_CPU]	   = 0,
  [COBALT_PCICONF_ETH0]	   = ETH0_IRQ,
  [COBALT_PCICONF_RAQSCSI] = RAQ2_SCSI_IRQ,
  [COBALT_PCICONF_VIA]	   = 0,
  [COBALT_PCICONF_PCISLOT] = PCISLOT_IRQ,
  [COBALT_PCICONF_ETH1]	   = ETH1_IRQ
पूर्ण;

पूर्णांक pcibios_map_irq(स्थिर काष्ठा pci_dev *dev, u8 slot, u8 pin)
अणु
	अगर (cobalt_board_id <= COBALT_BRD_ID_QUBE1)
		वापस irq_tab_qube1[slot];

	अगर (cobalt_board_id == COBALT_BRD_ID_RAQ2)
		वापस irq_tab_raq2[slot];

	वापस irq_tab_cobalt[slot];
पूर्ण

/* Do platक्रमm specअगरic device initialization at pci_enable_device() समय */
पूर्णांक pcibios_plat_dev_init(काष्ठा pci_dev *dev)
अणु
	वापस 0;
पूर्ण
