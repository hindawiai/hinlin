<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains work-arounds क्रम x86 and x86_64 platक्रमm bugs.
 */
#समावेश <linux/dmi.h>
#समावेश <linux/pci.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mce.h>

#अगर defined(CONFIG_X86_IO_APIC) && defined(CONFIG_SMP) && defined(CONFIG_PCI)

अटल व्योम quirk_पूर्णांकel_irqbalance(काष्ठा pci_dev *dev)
अणु
	u8 config;
	u16 word;

	/* BIOS may enable hardware IRQ balancing क्रम
	 * E7520/E7320/E7525(revision ID 0x9 and below)
	 * based platक्रमms.
	 * Disable SW irqbalance/affinity on those platक्रमms.
	 */
	अगर (dev->revision > 0x9)
		वापस;

	/* enable access to config space*/
	pci_पढ़ो_config_byte(dev, 0xf4, &config);
	pci_ग_लिखो_config_byte(dev, 0xf4, config|0x2);

	/*
	 * पढ़ो xTPR रेजिस्टर.  We may not have a pci_dev क्रम device 8
	 * because it might be hidden until the above ग_लिखो.
	 */
	pci_bus_पढ़ो_config_word(dev->bus, PCI_DEVFN(8, 0), 0x4c, &word);

	अगर (!(word & (1 << 13))) अणु
		dev_info(&dev->dev, "Intel E7520/7320/7525 detected; "
			"disabling irq balancing and affinity\n");
		noirqdebug_setup("");
#अगर_घोषित CONFIG_PROC_FS
		no_irq_affinity = 1;
#पूर्ण_अगर
	पूर्ण

	/* put back the original value क्रम config space*/
	अगर (!(config & 0x2))
		pci_ग_लिखो_config_byte(dev, 0xf4, config);
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_E7320_MCH,
			quirk_पूर्णांकel_irqbalance);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_E7525_MCH,
			quirk_पूर्णांकel_irqbalance);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_E7520_MCH,
			quirk_पूर्णांकel_irqbalance);
#पूर्ण_अगर

#अगर defined(CONFIG_HPET_TIMER)
अचिन्हित दीर्घ क्रमce_hpet_address;

अटल क्रमागत अणु
	NONE_FORCE_HPET_RESUME,
	OLD_ICH_FORCE_HPET_RESUME,
	ICH_FORCE_HPET_RESUME,
	VT8237_FORCE_HPET_RESUME,
	NVIDIA_FORCE_HPET_RESUME,
	ATI_FORCE_HPET_RESUME,
पूर्ण क्रमce_hpet_resume_type;

अटल व्योम __iomem *rcba_base;

अटल व्योम ich_क्रमce_hpet_resume(व्योम)
अणु
	u32 val;

	अगर (!क्रमce_hpet_address)
		वापस;

	BUG_ON(rcba_base == शून्य);

	/* पढ़ो the Function Disable रेजिस्टर, dword mode only */
	val = पढ़ोl(rcba_base + 0x3404);
	अगर (!(val & 0x80)) अणु
		/* HPET disabled in HPTC. Trying to enable */
		ग_लिखोl(val | 0x80, rcba_base + 0x3404);
	पूर्ण

	val = पढ़ोl(rcba_base + 0x3404);
	अगर (!(val & 0x80))
		BUG();
	अन्यथा
		prपूर्णांकk(KERN_DEBUG "Force enabled HPET at resume\n");
पूर्ण

अटल व्योम ich_क्रमce_enable_hpet(काष्ठा pci_dev *dev)
अणु
	u32 val;
	u32 rcba;
	पूर्णांक err = 0;

	अगर (hpet_address || क्रमce_hpet_address)
		वापस;

	pci_पढ़ो_config_dword(dev, 0xF0, &rcba);
	rcba &= 0xFFFFC000;
	अगर (rcba == 0) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "RCBA disabled; "
			"cannot force enable HPET\n");
		वापस;
	पूर्ण

	/* use bits 31:14, 16 kB aligned */
	rcba_base = ioremap(rcba, 0x4000);
	अगर (rcba_base == शून्य) अणु
		dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "ioremap failed; "
			"cannot force enable HPET\n");
		वापस;
	पूर्ण

	/* पढ़ो the Function Disable रेजिस्टर, dword mode only */
	val = पढ़ोl(rcba_base + 0x3404);

	अगर (val & 0x80) अणु
		/* HPET is enabled in HPTC. Just not reported by BIOS */
		val = val & 0x3;
		क्रमce_hpet_address = 0xFED00000 | (val << 12);
		dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "Force enabled HPET at "
			"0x%lx\n", क्रमce_hpet_address);
		iounmap(rcba_base);
		वापस;
	पूर्ण

	/* HPET disabled in HPTC. Trying to enable */
	ग_लिखोl(val | 0x80, rcba_base + 0x3404);

	val = पढ़ोl(rcba_base + 0x3404);
	अगर (!(val & 0x80)) अणु
		err = 1;
	पूर्ण अन्यथा अणु
		val = val & 0x3;
		क्रमce_hpet_address = 0xFED00000 | (val << 12);
	पूर्ण

	अगर (err) अणु
		क्रमce_hpet_address = 0;
		iounmap(rcba_base);
		dev_prपूर्णांकk(KERN_DEBUG, &dev->dev,
			"Failed to force enable HPET\n");
	पूर्ण अन्यथा अणु
		क्रमce_hpet_resume_type = ICH_FORCE_HPET_RESUME;
		dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "Force enabled HPET at "
			"0x%lx\n", क्रमce_hpet_address);
	पूर्ण
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ESB2_0,
			 ich_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH6_0,
			 ich_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH6_1,
			 ich_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH7_0,
			 ich_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH7_1,
			 ich_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH7_31,
			 ich_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH8_1,
			 ich_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH8_4,
			 ich_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH9_7,
			 ich_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, 0x3a16,	/* ICH10 */
			 ich_क्रमce_enable_hpet);

अटल काष्ठा pci_dev *cached_dev;

अटल व्योम hpet_prपूर्णांक_क्रमce_info(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "HPET not enabled in BIOS. "
	       "You might try hpet=force boot option\n");
पूर्ण

अटल व्योम old_ich_क्रमce_hpet_resume(व्योम)
अणु
	u32 val;
	u32 gen_cntl;

	अगर (!क्रमce_hpet_address || !cached_dev)
		वापस;

	pci_पढ़ो_config_dword(cached_dev, 0xD0, &gen_cntl);
	gen_cntl &= (~(0x7 << 15));
	gen_cntl |= (0x4 << 15);

	pci_ग_लिखो_config_dword(cached_dev, 0xD0, gen_cntl);
	pci_पढ़ो_config_dword(cached_dev, 0xD0, &gen_cntl);
	val = gen_cntl >> 15;
	val &= 0x7;
	अगर (val == 0x4)
		prपूर्णांकk(KERN_DEBUG "Force enabled HPET at resume\n");
	अन्यथा
		BUG();
पूर्ण

अटल व्योम old_ich_क्रमce_enable_hpet(काष्ठा pci_dev *dev)
अणु
	u32 val;
	u32 gen_cntl;

	अगर (hpet_address || क्रमce_hpet_address)
		वापस;

	pci_पढ़ो_config_dword(dev, 0xD0, &gen_cntl);
	/*
	 * Bit 17 is HPET enable bit.
	 * Bit 16:15 control the HPET base address.
	 */
	val = gen_cntl >> 15;
	val &= 0x7;
	अगर (val & 0x4) अणु
		val &= 0x3;
		क्रमce_hpet_address = 0xFED00000 | (val << 12);
		dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "HPET at 0x%lx\n",
			क्रमce_hpet_address);
		वापस;
	पूर्ण

	/*
	 * HPET is disabled. Trying enabling at FED00000 and check
	 * whether it sticks
	 */
	gen_cntl &= (~(0x7 << 15));
	gen_cntl |= (0x4 << 15);
	pci_ग_लिखो_config_dword(dev, 0xD0, gen_cntl);

	pci_पढ़ो_config_dword(dev, 0xD0, &gen_cntl);

	val = gen_cntl >> 15;
	val &= 0x7;
	अगर (val & 0x4) अणु
		/* HPET is enabled in HPTC. Just not reported by BIOS */
		val &= 0x3;
		क्रमce_hpet_address = 0xFED00000 | (val << 12);
		dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "Force enabled HPET at "
			"0x%lx\n", क्रमce_hpet_address);
		cached_dev = dev;
		क्रमce_hpet_resume_type = OLD_ICH_FORCE_HPET_RESUME;
		वापस;
	पूर्ण

	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "Failed to force enable HPET\n");
पूर्ण

/*
 * Unकरोcumented chipset features. Make sure that the user enक्रमced
 * this.
 */
अटल व्योम old_ich_क्रमce_enable_hpet_user(काष्ठा pci_dev *dev)
अणु
	अगर (hpet_क्रमce_user)
		old_ich_क्रमce_enable_hpet(dev);
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ESB_1,
			 old_ich_क्रमce_enable_hpet_user);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801CA_0,
			 old_ich_क्रमce_enable_hpet_user);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801CA_12,
			 old_ich_क्रमce_enable_hpet_user);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801DB_0,
			 old_ich_क्रमce_enable_hpet_user);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801DB_12,
			 old_ich_क्रमce_enable_hpet_user);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801EB_0,
			 old_ich_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801EB_12,
			 old_ich_क्रमce_enable_hpet);


अटल व्योम vt8237_क्रमce_hpet_resume(व्योम)
अणु
	u32 val;

	अगर (!क्रमce_hpet_address || !cached_dev)
		वापस;

	val = 0xfed00000 | 0x80;
	pci_ग_लिखो_config_dword(cached_dev, 0x68, val);

	pci_पढ़ो_config_dword(cached_dev, 0x68, &val);
	अगर (val & 0x80)
		prपूर्णांकk(KERN_DEBUG "Force enabled HPET at resume\n");
	अन्यथा
		BUG();
पूर्ण

अटल व्योम vt8237_क्रमce_enable_hpet(काष्ठा pci_dev *dev)
अणु
	u32 val;

	अगर (hpet_address || क्रमce_hpet_address)
		वापस;

	अगर (!hpet_क्रमce_user) अणु
		hpet_prपूर्णांक_क्रमce_info();
		वापस;
	पूर्ण

	pci_पढ़ो_config_dword(dev, 0x68, &val);
	/*
	 * Bit 7 is HPET enable bit.
	 * Bit 31:10 is HPET base address (contrary to what datasheet claims)
	 */
	अगर (val & 0x80) अणु
		क्रमce_hpet_address = (val & ~0x3ff);
		dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "HPET at 0x%lx\n",
			क्रमce_hpet_address);
		वापस;
	पूर्ण

	/*
	 * HPET is disabled. Trying enabling at FED00000 and check
	 * whether it sticks
	 */
	val = 0xfed00000 | 0x80;
	pci_ग_लिखो_config_dword(dev, 0x68, val);

	pci_पढ़ो_config_dword(dev, 0x68, &val);
	अगर (val & 0x80) अणु
		क्रमce_hpet_address = (val & ~0x3ff);
		dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "Force enabled HPET at "
			"0x%lx\n", क्रमce_hpet_address);
		cached_dev = dev;
		क्रमce_hpet_resume_type = VT8237_FORCE_HPET_RESUME;
		वापस;
	पूर्ण

	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "Failed to force enable HPET\n");
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8235,
			 vt8237_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_8237,
			 vt8237_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_VIA, PCI_DEVICE_ID_VIA_CX700,
			 vt8237_क्रमce_enable_hpet);

अटल व्योम ati_क्रमce_hpet_resume(व्योम)
अणु
	pci_ग_लिखो_config_dword(cached_dev, 0x14, 0xfed00000);
	prपूर्णांकk(KERN_DEBUG "Force enabled HPET at resume\n");
पूर्ण

अटल u32 ati_ixp4x0_rev(काष्ठा pci_dev *dev)
अणु
	पूर्णांक err = 0;
	u32 d = 0;
	u8  b = 0;

	err = pci_पढ़ो_config_byte(dev, 0xac, &b);
	b &= ~(1<<5);
	err |= pci_ग_लिखो_config_byte(dev, 0xac, b);
	err |= pci_पढ़ो_config_dword(dev, 0x70, &d);
	d |= 1<<8;
	err |= pci_ग_लिखो_config_dword(dev, 0x70, d);
	err |= pci_पढ़ो_config_dword(dev, 0x8, &d);
	d &= 0xff;
	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "SB4X0 revision 0x%x\n", d);

	WARN_ON_ONCE(err);

	वापस d;
पूर्ण

अटल व्योम ati_क्रमce_enable_hpet(काष्ठा pci_dev *dev)
अणु
	u32 d, val;
	u8  b;

	अगर (hpet_address || क्रमce_hpet_address)
		वापस;

	अगर (!hpet_क्रमce_user) अणु
		hpet_prपूर्णांक_क्रमce_info();
		वापस;
	पूर्ण

	d = ati_ixp4x0_rev(dev);
	अगर (d  < 0x82)
		वापस;

	/* base address */
	pci_ग_लिखो_config_dword(dev, 0x14, 0xfed00000);
	pci_पढ़ो_config_dword(dev, 0x14, &val);

	/* enable पूर्णांकerrupt */
	outb(0x72, 0xcd6); b = inb(0xcd7);
	b |= 0x1;
	outb(0x72, 0xcd6); outb(b, 0xcd7);
	outb(0x72, 0xcd6); b = inb(0xcd7);
	अगर (!(b & 0x1))
		वापस;
	pci_पढ़ो_config_dword(dev, 0x64, &d);
	d |= (1<<10);
	pci_ग_लिखो_config_dword(dev, 0x64, d);
	pci_पढ़ो_config_dword(dev, 0x64, &d);
	अगर (!(d & (1<<10)))
		वापस;

	क्रमce_hpet_address = val;
	क्रमce_hpet_resume_type = ATI_FORCE_HPET_RESUME;
	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "Force enabled HPET at 0x%lx\n",
		   क्रमce_hpet_address);
	cached_dev = dev;
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_IXP400_SMBUS,
			 ati_क्रमce_enable_hpet);

/*
 * Unकरोcumented chipset feature taken from LinuxBIOS.
 */
अटल व्योम nvidia_क्रमce_hpet_resume(व्योम)
अणु
	pci_ग_लिखो_config_dword(cached_dev, 0x44, 0xfed00001);
	prपूर्णांकk(KERN_DEBUG "Force enabled HPET at resume\n");
पूर्ण

अटल व्योम nvidia_क्रमce_enable_hpet(काष्ठा pci_dev *dev)
अणु
	u32 val;

	अगर (hpet_address || क्रमce_hpet_address)
		वापस;

	अगर (!hpet_क्रमce_user) अणु
		hpet_prपूर्णांक_क्रमce_info();
		वापस;
	पूर्ण

	pci_ग_लिखो_config_dword(dev, 0x44, 0xfed00001);
	pci_पढ़ो_config_dword(dev, 0x44, &val);
	क्रमce_hpet_address = val & 0xfffffffe;
	क्रमce_hpet_resume_type = NVIDIA_FORCE_HPET_RESUME;
	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "Force enabled HPET at 0x%lx\n",
		क्रमce_hpet_address);
	cached_dev = dev;
पूर्ण

/* ISA Bridges */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0050,
			nvidia_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0051,
			nvidia_क्रमce_enable_hpet);

/* LPC bridges */
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0260,
			nvidia_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0360,
			nvidia_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0361,
			nvidia_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0362,
			nvidia_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0363,
			nvidia_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0364,
			nvidia_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0365,
			nvidia_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0366,
			nvidia_क्रमce_enable_hpet);
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_NVIDIA, 0x0367,
			nvidia_क्रमce_enable_hpet);

व्योम क्रमce_hpet_resume(व्योम)
अणु
	चयन (क्रमce_hpet_resume_type) अणु
	हाल ICH_FORCE_HPET_RESUME:
		ich_क्रमce_hpet_resume();
		वापस;
	हाल OLD_ICH_FORCE_HPET_RESUME:
		old_ich_क्रमce_hpet_resume();
		वापस;
	हाल VT8237_FORCE_HPET_RESUME:
		vt8237_क्रमce_hpet_resume();
		वापस;
	हाल NVIDIA_FORCE_HPET_RESUME:
		nvidia_क्रमce_hpet_resume();
		वापस;
	हाल ATI_FORCE_HPET_RESUME:
		ati_क्रमce_hpet_resume();
		वापस;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * According to the datasheet e6xx प्रणालीs have the HPET hardwired to
 * 0xfed00000
 */
अटल व्योम e6xx_क्रमce_enable_hpet(काष्ठा pci_dev *dev)
अणु
	अगर (hpet_address || क्रमce_hpet_address)
		वापस;

	क्रमce_hpet_address = 0xFED00000;
	क्रमce_hpet_resume_type = NONE_FORCE_HPET_RESUME;
	dev_prपूर्णांकk(KERN_DEBUG, &dev->dev, "Force enabled HPET at "
		"0x%lx\n", क्रमce_hpet_address);
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_E6XX_CU,
			 e6xx_क्रमce_enable_hpet);

/*
 * HPET MSI on some boards (ATI SB700/SB800) has side effect on
 * floppy DMA. Disable HPET MSI on such platक्रमms.
 * See erratum #27 (Misपूर्णांकerpreted MSI Requests May Result in
 * Corrupted LPC DMA Data) in AMD Publication #46837,
 * "SB700 Family Product Errata", Rev. 1.0, March 2010.
 */
अटल व्योम क्रमce_disable_hpet_msi(काष्ठा pci_dev *unused)
अणु
	hpet_msi_disable = true;
पूर्ण

DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_SBX00_SMBUS,
			 क्रमce_disable_hpet_msi);

#पूर्ण_अगर

#अगर defined(CONFIG_PCI) && defined(CONFIG_NUMA)
/* Set correct numa_node inक्रमmation क्रम AMD NB functions */
अटल व्योम quirk_amd_nb_node(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *nb_ht;
	अचिन्हित पूर्णांक devfn;
	u32 node;
	u32 val;

	devfn = PCI_DEVFN(PCI_SLOT(dev->devfn), 0);
	nb_ht = pci_get_slot(dev->bus, devfn);
	अगर (!nb_ht)
		वापस;

	pci_पढ़ो_config_dword(nb_ht, 0x60, &val);
	node = pcibus_to_node(dev->bus) | (val & 7);
	/*
	 * Some hardware may वापस an invalid node ID,
	 * so check it first:
	 */
	अगर (node_online(node))
		set_dev_node(&dev->dev, node);
	pci_dev_put(nb_ht);
पूर्ण

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB_ADDRMAP,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB_MEMCTL,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB_MISC,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_HT,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_MAP,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_DRAM,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_MISC,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_10H_NB_LINK,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F0,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F1,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F2,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F3,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F4,
			quirk_amd_nb_node);
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_15H_NB_F5,
			quirk_amd_nb_node);

#पूर्ण_अगर

#अगर_घोषित CONFIG_PCI
/*
 * Processor करोes not ensure DRAM scrub पढ़ो/ग_लिखो sequence
 * is atomic wrt accesses to CC6 save state area. Thereक्रमe
 * अगर a concurrent scrub पढ़ो/ग_लिखो access is to same address
 * the entry may appear as अगर it is not written. This quirk
 * applies to Fam16h models 00h-0Fh
 *
 * See "Revision Guide" क्रम AMD F16h models 00h-0fh,
 * करोcument 51810 rev. 3.04, Nov 2013
 */
अटल व्योम amd_disable_seq_and_redirect_scrub(काष्ठा pci_dev *dev)
अणु
	u32 val;

	/*
	 * Suggested workaround:
	 * set D18F3x58[4:0] = 00h and set D18F3x5C[0] = 0b
	 */
	pci_पढ़ो_config_dword(dev, 0x58, &val);
	अगर (val & 0x1F) अणु
		val &= ~(0x1F);
		pci_ग_लिखो_config_dword(dev, 0x58, val);
	पूर्ण

	pci_पढ़ो_config_dword(dev, 0x5C, &val);
	अगर (val & BIT(0)) अणु
		val &= ~BIT(0);
		pci_ग_लिखो_config_dword(dev, 0x5c, val);
	पूर्ण
पूर्ण

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_16H_NB_F3,
			amd_disable_seq_and_redirect_scrub);

/* Ivy Bridge, Haswell, Broadwell */
अटल व्योम quirk_पूर्णांकel_brickland_xeon_ras_cap(काष्ठा pci_dev *pdev)
अणु
	u32 capid0;

	pci_पढ़ो_config_dword(pdev, 0x84, &capid0);

	अगर (capid0 & 0x10)
		enable_copy_mc_fragile();
पूर्ण

/* Skylake */
अटल व्योम quirk_पूर्णांकel_purley_xeon_ras_cap(काष्ठा pci_dev *pdev)
अणु
	u32 capid0, capid5;

	pci_पढ़ो_config_dword(pdev, 0x84, &capid0);
	pci_पढ़ो_config_dword(pdev, 0x98, &capid5);

	/*
	 * CAPID0अणु7:6पूर्ण indicate whether this is an advanced RAS SKU
	 * CAPID5अणु8:5पूर्ण indicate that various NVDIMM usage modes are
	 * enabled, so memory machine check recovery is also enabled.
	 */
	अगर ((capid0 & 0xc0) == 0xc0 || (capid5 & 0x1e0))
		enable_copy_mc_fragile();

पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x0ec3, quirk_पूर्णांकel_brickland_xeon_ras_cap);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x2fc0, quirk_पूर्णांकel_brickland_xeon_ras_cap);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x6fc0, quirk_पूर्णांकel_brickland_xeon_ras_cap);
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_INTEL, 0x2083, quirk_पूर्णांकel_purley_xeon_ras_cap);
#पूर्ण_अगर

bool x86_apple_machine;
EXPORT_SYMBOL(x86_apple_machine);

व्योम __init early_platक्रमm_quirks(व्योम)
अणु
	x86_apple_machine = dmi_match(DMI_SYS_VENDOR, "Apple Inc.") ||
			    dmi_match(DMI_SYS_VENDOR, "Apple Computer, Inc.");
पूर्ण
