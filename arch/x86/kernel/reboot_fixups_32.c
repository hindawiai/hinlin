<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is a good place to put board specअगरic reboot fixups.
 *
 * List of supported fixups:
 * geode-gx1/cs5530a - Jaya Kumar <jayalk@पूर्णांकworks.biz>
 * geode-gx/lx/cs5536 - Andres Salomon <dilinger@debian.org>
 *
 */

#समावेश <यंत्र/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/reboot_fixups.h>
#समावेश <यंत्र/msr.h>
#समावेश <linux/cs5535.h>

अटल व्योम cs5530a_warm_reset(काष्ठा pci_dev *dev)
अणु
	/* writing 1 to the reset control रेजिस्टर, 0x44 causes the
	cs5530a to perक्रमm a प्रणाली warm reset */
	pci_ग_लिखो_config_byte(dev, 0x44, 0x1);
	udelay(50); /* shouldn't get here but be safe and spin-a-जबतक */
	वापस;
पूर्ण

अटल व्योम cs5536_warm_reset(काष्ठा pci_dev *dev)
अणु
	/* writing 1 to the LSB of this MSR causes a hard reset */
	wrmsrl(MSR_DIVIL_SOFT_RESET, 1ULL);
	udelay(50); /* shouldn't get here but be safe and spin a जबतक */
पूर्ण

अटल व्योम rdc321x_reset(काष्ठा pci_dev *dev)
अणु
	अचिन्हित i;
	/* Voluntary reset the watchकरोg समयr */
	outl(0x80003840, 0xCF8);
	/* Generate a CPU reset on next tick */
	i = inl(0xCFC);
	/* Use the minimum समयr resolution */
	i |= 0x1600;
	outl(i, 0xCFC);
	outb(1, 0x92);
पूर्ण

अटल व्योम ce4100_reset(काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		outb(0x2, 0xcf9);
		udelay(50);
	पूर्ण
पूर्ण

काष्ठा device_fixup अणु
	अचिन्हित पूर्णांक venकरोr;
	अचिन्हित पूर्णांक device;
	व्योम (*reboot_fixup)(काष्ठा pci_dev *);
पूर्ण;

/*
 * PCI ids solely used क्रम fixups_table go here
 */
#घोषणा PCI_DEVICE_ID_INTEL_CE4100	0x0708

अटल स्थिर काष्ठा device_fixup fixups_table[] = अणु
अणु PCI_VENDOR_ID_CYRIX, PCI_DEVICE_ID_CYRIX_5530_LEGACY, cs5530a_warm_reset पूर्ण,
अणु PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_ISA, cs5536_warm_reset पूर्ण,
अणु PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_SC1100_BRIDGE, cs5530a_warm_reset पूर्ण,
अणु PCI_VENDOR_ID_RDC, PCI_DEVICE_ID_RDC_R6030, rdc321x_reset पूर्ण,
अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CE4100, ce4100_reset पूर्ण,
पूर्ण;

/*
 * we see अगर any fixup is available क्रम our current hardware. अगर there
 * is a fixup, we call it and we expect to never वापस from it. अगर we
 * करो वापस, we keep looking and then eventually fall back to the
 * standard mach_reboot on वापस.
 */
व्योम mach_reboot_fixups(व्योम)
अणु
	स्थिर काष्ठा device_fixup *cur;
	काष्ठा pci_dev *dev;
	पूर्णांक i;

	/* we can be called from sysrq-B code. In such a हाल it is
	 * prohibited to dig PCI */
	अगर (in_पूर्णांकerrupt())
		वापस;

	क्रम (i=0; i < ARRAY_SIZE(fixups_table); i++) अणु
		cur = &(fixups_table[i]);
		dev = pci_get_device(cur->venकरोr, cur->device, शून्य);
		अगर (!dev)
			जारी;

		cur->reboot_fixup(dev);
		pci_dev_put(dev);
	पूर्ण
पूर्ण

