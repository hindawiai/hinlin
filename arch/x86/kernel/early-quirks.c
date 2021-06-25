<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Various workarounds क्रम chipset bugs.
   This code runs very early and can't use the regular PCI subप्रणाली
   The entries are keyed to PCI bridges which usually identअगरy chipsets
   uniquely.
   This is only क्रम whole classes of chipsets with specअगरic problems which
   need early invasive action (e.g. beक्रमe the समयrs are initialized).
   Most PCI device specअगरic workarounds can be करोne later and should be
   in standard PCI quirks
   Mainboard specअगरic bugs should be handled by DMI entries.
   CPU specअगरic bugs in setup.c */

#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <linux/bcma/bcma_regs.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>
#समावेश <drm/i915_drm.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/gart.h>
#समावेश <यंत्र/irq_remapping.h>
#समावेश <यंत्र/early_ioremap.h>

अटल व्योम __init fix_hypertransport_config(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u32 htcfg;
	/*
	 * we found a hypertransport bus
	 * make sure that we are broadcasting
	 * पूर्णांकerrupts to all cpus on the ht bus
	 * अगर we're using extended apic ids
	 */
	htcfg = पढ़ो_pci_config(num, slot, func, 0x68);
	अगर (htcfg & (1 << 18)) अणु
		prपूर्णांकk(KERN_INFO "Detected use of extended apic ids "
				 "on hypertransport bus\n");
		अगर ((htcfg & (1 << 17)) == 0) अणु
			prपूर्णांकk(KERN_INFO "Enabling hypertransport extended "
					 "apic interrupt broadcast\n");
			prपूर्णांकk(KERN_INFO "Note this is a bios bug, "
					 "please contact your hw vendor\n");
			htcfg |= (1 << 17);
			ग_लिखो_pci_config(num, slot, func, 0x68, htcfg);
		पूर्ण
	पूर्ण


पूर्ण

अटल व्योम __init via_bugs(पूर्णांक  num, पूर्णांक slot, पूर्णांक func)
अणु
#अगर_घोषित CONFIG_GART_IOMMU
	अगर ((max_pfn > MAX_DMA32_PFN ||  क्रमce_iommu) &&
	    !gart_iommu_aperture_allowed) अणु
		prपूर्णांकk(KERN_INFO
		       "Looks like a VIA chipset. Disabling IOMMU."
		       " Override with iommu=allowed\n");
		gart_iommu_aperture_disabled = 1;
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_ACPI
#अगर_घोषित CONFIG_X86_IO_APIC

अटल पूर्णांक __init nvidia_hpet_check(काष्ठा acpi_table_header *header)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_IO_APIC */
#पूर्ण_अगर /* CONFIG_ACPI */

अटल व्योम __init nvidia_bugs(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
#अगर_घोषित CONFIG_ACPI
#अगर_घोषित CONFIG_X86_IO_APIC
	/*
	 * Only applies to Nvidia root ports (bus 0) and not to
	 * Nvidia graphics cards with PCI ports on secondary buses.
	 */
	अगर (num)
		वापस;

	/*
	 * All समयr overrides on Nvidia are
	 * wrong unless HPET is enabled.
	 * Unक्रमtunately that's not true on many Asus boards.
	 * We करोn't know yet how to detect this स्वतःmatically, but
	 * at least allow a command line override.
	 */
	अगर (acpi_use_समयr_override)
		वापस;

	अगर (acpi_table_parse(ACPI_SIG_HPET, nvidia_hpet_check)) अणु
		acpi_skip_समयr_override = 1;
		prपूर्णांकk(KERN_INFO "Nvidia board "
		       "detected. Ignoring ACPI "
		       "timer override.\n");
		prपूर्णांकk(KERN_INFO "If you got timer trouble "
			"try acpi_use_timer_override\n");
	पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
	/* RED-PEN skip them on mptables too? */

पूर्ण

#अगर defined(CONFIG_ACPI) && defined(CONFIG_X86_IO_APIC)
अटल u32 __init ati_ixp4x0_rev(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u32 d;
	u8  b;

	b = पढ़ो_pci_config_byte(num, slot, func, 0xac);
	b &= ~(1<<5);
	ग_लिखो_pci_config_byte(num, slot, func, 0xac, b);

	d = पढ़ो_pci_config(num, slot, func, 0x70);
	d |= 1<<8;
	ग_लिखो_pci_config(num, slot, func, 0x70, d);

	d = पढ़ो_pci_config(num, slot, func, 0x8);
	d &= 0xff;
	वापस d;
पूर्ण

अटल व्योम __init ati_bugs(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u32 d;
	u8  b;

	अगर (acpi_use_समयr_override)
		वापस;

	d = ati_ixp4x0_rev(num, slot, func);
	अगर (d  < 0x82)
		acpi_skip_समयr_override = 1;
	अन्यथा अणु
		/* check क्रम IRQ0 पूर्णांकerrupt swap */
		outb(0x72, 0xcd6); b = inb(0xcd7);
		अगर (!(b & 0x2))
			acpi_skip_समयr_override = 1;
	पूर्ण

	अगर (acpi_skip_समयr_override) अणु
		prपूर्णांकk(KERN_INFO "SB4X0 revision 0x%x\n", d);
		prपूर्णांकk(KERN_INFO "Ignoring ACPI timer override.\n");
		prपूर्णांकk(KERN_INFO "If you got timer trouble "
		       "try acpi_use_timer_override\n");
	पूर्ण
पूर्ण

अटल u32 __init ati_sbx00_rev(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u32 d;

	d = पढ़ो_pci_config(num, slot, func, 0x8);
	d &= 0xff;

	वापस d;
पूर्ण

अटल व्योम __init ati_bugs_contd(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u32 d, rev;

	rev = ati_sbx00_rev(num, slot, func);
	अगर (rev >= 0x40)
		acpi_fix_pin2_polarity = 1;

	/*
	 * SB600: revisions 0x11, 0x12, 0x13, 0x14, ...
	 * SB700: revisions 0x39, 0x3a, ...
	 * SB800: revisions 0x40, 0x41, ...
	 */
	अगर (rev >= 0x39)
		वापस;

	अगर (acpi_use_समयr_override)
		वापस;

	/* check क्रम IRQ0 पूर्णांकerrupt swap */
	d = पढ़ो_pci_config(num, slot, func, 0x64);
	अगर (!(d & (1<<14)))
		acpi_skip_समयr_override = 1;

	अगर (acpi_skip_समयr_override) अणु
		prपूर्णांकk(KERN_INFO "SB600 revision 0x%x\n", rev);
		prपूर्णांकk(KERN_INFO "Ignoring ACPI timer override.\n");
		prपूर्णांकk(KERN_INFO "If you got timer trouble "
		       "try acpi_use_timer_override\n");
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम __init ati_bugs(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
पूर्ण

अटल व्योम __init ati_bugs_contd(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम __init पूर्णांकel_remapping_check(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u8 revision;
	u16 device;

	device = पढ़ो_pci_config_16(num, slot, func, PCI_DEVICE_ID);
	revision = पढ़ो_pci_config_byte(num, slot, func, PCI_REVISION_ID);

	/*
	 * Revision <= 13 of all triggering devices id in this quirk
	 * have a problem draining पूर्णांकerrupts when irq remapping is
	 * enabled, and should be flagged as broken. Additionally
	 * revision 0x22 of device id 0x3405 has this problem.
	 */
	अगर (revision <= 0x13)
		set_irq_remapping_broken();
	अन्यथा अगर (device == 0x3405 && revision == 0x22)
		set_irq_remapping_broken();
पूर्ण

/*
 * Systems with Intel graphics controllers set aside memory exclusively
 * क्रम gfx driver use.  This memory is not marked in the E820 as reserved
 * or as RAM, and so is subject to overlap from E820 manipulation later
 * in the boot process.  On some प्रणालीs, MMIO space is allocated on top,
 * despite the efक्रमts of the "RAM buffer" approach, which simply rounds
 * memory boundaries up to 64M to try to catch space that may decode
 * as RAM and so is not suitable क्रम MMIO.
 */

#घोषणा KB(x)	((x) * 1024UL)
#घोषणा MB(x)	(KB (KB (x)))

अटल resource_माप_प्रकार __init i830_tseg_size(व्योम)
अणु
	u8 esmramc = पढ़ो_pci_config_byte(0, 0, 0, I830_ESMRAMC);

	अगर (!(esmramc & TSEG_ENABLE))
		वापस 0;

	अगर (esmramc & I830_TSEG_SIZE_1M)
		वापस MB(1);
	अन्यथा
		वापस KB(512);
पूर्ण

अटल resource_माप_प्रकार __init i845_tseg_size(व्योम)
अणु
	u8 esmramc = पढ़ो_pci_config_byte(0, 0, 0, I845_ESMRAMC);
	u8 tseg_size = esmramc & I845_TSEG_SIZE_MASK;

	अगर (!(esmramc & TSEG_ENABLE))
		वापस 0;

	चयन (tseg_size) अणु
	हाल I845_TSEG_SIZE_512K:	वापस KB(512);
	हाल I845_TSEG_SIZE_1M:		वापस MB(1);
	शेष:
		WARN(1, "Unknown ESMRAMC value: %x!\n", esmramc);
	पूर्ण
	वापस 0;
पूर्ण

अटल resource_माप_प्रकार __init i85x_tseg_size(व्योम)
अणु
	u8 esmramc = पढ़ो_pci_config_byte(0, 0, 0, I85X_ESMRAMC);

	अगर (!(esmramc & TSEG_ENABLE))
		वापस 0;

	वापस MB(1);
पूर्ण

अटल resource_माप_प्रकार __init i830_mem_size(व्योम)
अणु
	वापस पढ़ो_pci_config_byte(0, 0, 0, I830_DRB3) * MB(32);
पूर्ण

अटल resource_माप_प्रकार __init i85x_mem_size(व्योम)
अणु
	वापस पढ़ो_pci_config_byte(0, 0, 1, I85X_DRB3) * MB(32);
पूर्ण

/*
 * On 830/845/85x the stolen memory base isn't available in any
 * रेजिस्टर. We need to calculate it as TOM-TSEG_SIZE-stolen_size.
 */
अटल resource_माप_प्रकार __init i830_stolen_base(पूर्णांक num, पूर्णांक slot, पूर्णांक func,
					       resource_माप_प्रकार stolen_size)
अणु
	वापस i830_mem_size() - i830_tseg_size() - stolen_size;
पूर्ण

अटल resource_माप_प्रकार __init i845_stolen_base(पूर्णांक num, पूर्णांक slot, पूर्णांक func,
					       resource_माप_प्रकार stolen_size)
अणु
	वापस i830_mem_size() - i845_tseg_size() - stolen_size;
पूर्ण

अटल resource_माप_प्रकार __init i85x_stolen_base(पूर्णांक num, पूर्णांक slot, पूर्णांक func,
					       resource_माप_प्रकार stolen_size)
अणु
	वापस i85x_mem_size() - i85x_tseg_size() - stolen_size;
पूर्ण

अटल resource_माप_प्रकार __init i865_stolen_base(पूर्णांक num, पूर्णांक slot, पूर्णांक func,
					       resource_माप_प्रकार stolen_size)
अणु
	u16 toud = 0;

	toud = पढ़ो_pci_config_16(0, 0, 0, I865_TOUD);

	वापस toud * KB(64) + i845_tseg_size();
पूर्ण

अटल resource_माप_प्रकार __init gen3_stolen_base(पूर्णांक num, पूर्णांक slot, पूर्णांक func,
					       resource_माप_प्रकार stolen_size)
अणु
	u32 bsm;

	/* Almost universally we can find the Graphics Base of Stolen Memory
	 * at रेजिस्टर BSM (0x5c) in the igfx configuration space. On a few
	 * (desktop) machines this is also mirrored in the bridge device at
	 * dअगरferent locations, or in the MCHBAR.
	 */
	bsm = पढ़ो_pci_config(num, slot, func, INTEL_BSM);

	वापस bsm & INTEL_BSM_MASK;
पूर्ण

अटल resource_माप_प्रकार __init gen11_stolen_base(पूर्णांक num, पूर्णांक slot, पूर्णांक func,
						resource_माप_प्रकार stolen_size)
अणु
	u64 bsm;

	bsm = पढ़ो_pci_config(num, slot, func, INTEL_GEN11_BSM_DW0);
	bsm &= INTEL_BSM_MASK;
	bsm |= (u64)पढ़ो_pci_config(num, slot, func, INTEL_GEN11_BSM_DW1) << 32;

	वापस bsm;
पूर्ण

अटल resource_माप_प्रकार __init i830_stolen_size(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u16 gmch_ctrl;
	u16 gms;

	gmch_ctrl = पढ़ो_pci_config_16(0, 0, 0, I830_GMCH_CTRL);
	gms = gmch_ctrl & I830_GMCH_GMS_MASK;

	चयन (gms) अणु
	हाल I830_GMCH_GMS_STOLEN_512:	वापस KB(512);
	हाल I830_GMCH_GMS_STOLEN_1024:	वापस MB(1);
	हाल I830_GMCH_GMS_STOLEN_8192:	वापस MB(8);
	/* local memory isn't part of the normal address space */
	हाल I830_GMCH_GMS_LOCAL:	वापस 0;
	शेष:
		WARN(1, "Unknown GMCH_CTRL value: %x!\n", gmch_ctrl);
	पूर्ण

	वापस 0;
पूर्ण

अटल resource_माप_प्रकार __init gen3_stolen_size(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u16 gmch_ctrl;
	u16 gms;

	gmch_ctrl = पढ़ो_pci_config_16(0, 0, 0, I830_GMCH_CTRL);
	gms = gmch_ctrl & I855_GMCH_GMS_MASK;

	चयन (gms) अणु
	हाल I855_GMCH_GMS_STOLEN_1M:	वापस MB(1);
	हाल I855_GMCH_GMS_STOLEN_4M:	वापस MB(4);
	हाल I855_GMCH_GMS_STOLEN_8M:	वापस MB(8);
	हाल I855_GMCH_GMS_STOLEN_16M:	वापस MB(16);
	हाल I855_GMCH_GMS_STOLEN_32M:	वापस MB(32);
	हाल I915_GMCH_GMS_STOLEN_48M:	वापस MB(48);
	हाल I915_GMCH_GMS_STOLEN_64M:	वापस MB(64);
	हाल G33_GMCH_GMS_STOLEN_128M:	वापस MB(128);
	हाल G33_GMCH_GMS_STOLEN_256M:	वापस MB(256);
	हाल INTEL_GMCH_GMS_STOLEN_96M:	वापस MB(96);
	हाल INTEL_GMCH_GMS_STOLEN_160M:वापस MB(160);
	हाल INTEL_GMCH_GMS_STOLEN_224M:वापस MB(224);
	हाल INTEL_GMCH_GMS_STOLEN_352M:वापस MB(352);
	शेष:
		WARN(1, "Unknown GMCH_CTRL value: %x!\n", gmch_ctrl);
	पूर्ण

	वापस 0;
पूर्ण

अटल resource_माप_प्रकार __init gen6_stolen_size(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u16 gmch_ctrl;
	u16 gms;

	gmch_ctrl = पढ़ो_pci_config_16(num, slot, func, SNB_GMCH_CTRL);
	gms = (gmch_ctrl >> SNB_GMCH_GMS_SHIFT) & SNB_GMCH_GMS_MASK;

	वापस gms * MB(32);
पूर्ण

अटल resource_माप_प्रकार __init gen8_stolen_size(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u16 gmch_ctrl;
	u16 gms;

	gmch_ctrl = पढ़ो_pci_config_16(num, slot, func, SNB_GMCH_CTRL);
	gms = (gmch_ctrl >> BDW_GMCH_GMS_SHIFT) & BDW_GMCH_GMS_MASK;

	वापस gms * MB(32);
पूर्ण

अटल resource_माप_प्रकार __init chv_stolen_size(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u16 gmch_ctrl;
	u16 gms;

	gmch_ctrl = पढ़ो_pci_config_16(num, slot, func, SNB_GMCH_CTRL);
	gms = (gmch_ctrl >> SNB_GMCH_GMS_SHIFT) & SNB_GMCH_GMS_MASK;

	/*
	 * 0x0  to 0x10: 32MB increments starting at 0MB
	 * 0x11 to 0x16: 4MB increments starting at 8MB
	 * 0x17 to 0x1d: 4MB increments start at 36MB
	 */
	अगर (gms < 0x11)
		वापस gms * MB(32);
	अन्यथा अगर (gms < 0x17)
		वापस (gms - 0x11) * MB(4) + MB(8);
	अन्यथा
		वापस (gms - 0x17) * MB(4) + MB(36);
पूर्ण

अटल resource_माप_प्रकार __init gen9_stolen_size(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u16 gmch_ctrl;
	u16 gms;

	gmch_ctrl = पढ़ो_pci_config_16(num, slot, func, SNB_GMCH_CTRL);
	gms = (gmch_ctrl >> BDW_GMCH_GMS_SHIFT) & BDW_GMCH_GMS_MASK;

	/* 0x0  to 0xef: 32MB increments starting at 0MB */
	/* 0xf0 to 0xfe: 4MB increments starting at 4MB */
	अगर (gms < 0xf0)
		वापस gms * MB(32);
	अन्यथा
		वापस (gms - 0xf0) * MB(4) + MB(4);
पूर्ण

काष्ठा पूर्णांकel_early_ops अणु
	resource_माप_प्रकार (*stolen_size)(पूर्णांक num, पूर्णांक slot, पूर्णांक func);
	resource_माप_प्रकार (*stolen_base)(पूर्णांक num, पूर्णांक slot, पूर्णांक func,
				       resource_माप_प्रकार size);
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_early_ops i830_early_ops __initस्थिर = अणु
	.stolen_base = i830_stolen_base,
	.stolen_size = i830_stolen_size,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_early_ops i845_early_ops __initस्थिर = अणु
	.stolen_base = i845_stolen_base,
	.stolen_size = i830_stolen_size,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_early_ops i85x_early_ops __initस्थिर = अणु
	.stolen_base = i85x_stolen_base,
	.stolen_size = gen3_stolen_size,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_early_ops i865_early_ops __initस्थिर = अणु
	.stolen_base = i865_stolen_base,
	.stolen_size = gen3_stolen_size,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_early_ops gen3_early_ops __initस्थिर = अणु
	.stolen_base = gen3_stolen_base,
	.stolen_size = gen3_stolen_size,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_early_ops gen6_early_ops __initस्थिर = अणु
	.stolen_base = gen3_stolen_base,
	.stolen_size = gen6_stolen_size,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_early_ops gen8_early_ops __initस्थिर = अणु
	.stolen_base = gen3_stolen_base,
	.stolen_size = gen8_stolen_size,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_early_ops gen9_early_ops __initस्थिर = अणु
	.stolen_base = gen3_stolen_base,
	.stolen_size = gen9_stolen_size,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_early_ops chv_early_ops __initस्थिर = अणु
	.stolen_base = gen3_stolen_base,
	.stolen_size = chv_stolen_size,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_early_ops gen11_early_ops __initस्थिर = अणु
	.stolen_base = gen11_stolen_base,
	.stolen_size = gen9_stolen_size,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id पूर्णांकel_early_ids[] __initस्थिर = अणु
	INTEL_I830_IDS(&i830_early_ops),
	INTEL_I845G_IDS(&i845_early_ops),
	INTEL_I85X_IDS(&i85x_early_ops),
	INTEL_I865G_IDS(&i865_early_ops),
	INTEL_I915G_IDS(&gen3_early_ops),
	INTEL_I915GM_IDS(&gen3_early_ops),
	INTEL_I945G_IDS(&gen3_early_ops),
	INTEL_I945GM_IDS(&gen3_early_ops),
	INTEL_VLV_IDS(&gen6_early_ops),
	INTEL_PINEVIEW_G_IDS(&gen3_early_ops),
	INTEL_PINEVIEW_M_IDS(&gen3_early_ops),
	INTEL_I965G_IDS(&gen3_early_ops),
	INTEL_G33_IDS(&gen3_early_ops),
	INTEL_I965GM_IDS(&gen3_early_ops),
	INTEL_GM45_IDS(&gen3_early_ops),
	INTEL_G45_IDS(&gen3_early_ops),
	INTEL_IRONLAKE_D_IDS(&gen3_early_ops),
	INTEL_IRONLAKE_M_IDS(&gen3_early_ops),
	INTEL_SNB_D_IDS(&gen6_early_ops),
	INTEL_SNB_M_IDS(&gen6_early_ops),
	INTEL_IVB_M_IDS(&gen6_early_ops),
	INTEL_IVB_D_IDS(&gen6_early_ops),
	INTEL_HSW_IDS(&gen6_early_ops),
	INTEL_BDW_IDS(&gen8_early_ops),
	INTEL_CHV_IDS(&chv_early_ops),
	INTEL_SKL_IDS(&gen9_early_ops),
	INTEL_BXT_IDS(&gen9_early_ops),
	INTEL_KBL_IDS(&gen9_early_ops),
	INTEL_CFL_IDS(&gen9_early_ops),
	INTEL_GLK_IDS(&gen9_early_ops),
	INTEL_CNL_IDS(&gen9_early_ops),
	INTEL_ICL_11_IDS(&gen11_early_ops),
	INTEL_EHL_IDS(&gen11_early_ops),
	INTEL_TGL_12_IDS(&gen11_early_ops),
	INTEL_RKL_IDS(&gen11_early_ops),
	INTEL_ADLS_IDS(&gen11_early_ops),
पूर्ण;

काष्ठा resource पूर्णांकel_graphics_stolen_res __ro_after_init = DEFINE_RES_MEM(0, 0);
EXPORT_SYMBOL(पूर्णांकel_graphics_stolen_res);

अटल व्योम __init
पूर्णांकel_graphics_stolen(पूर्णांक num, पूर्णांक slot, पूर्णांक func,
		      स्थिर काष्ठा पूर्णांकel_early_ops *early_ops)
अणु
	resource_माप_प्रकार base, size;
	resource_माप_प्रकार end;

	size = early_ops->stolen_size(num, slot, func);
	base = early_ops->stolen_base(num, slot, func, size);

	अगर (!size || !base)
		वापस;

	end = base + size - 1;

	पूर्णांकel_graphics_stolen_res.start = base;
	पूर्णांकel_graphics_stolen_res.end = end;

	prपूर्णांकk(KERN_INFO "Reserving Intel graphics memory at %pR\n",
	       &पूर्णांकel_graphics_stolen_res);

	/* Mark this space as reserved */
	e820__range_add(base, size, E820_TYPE_RESERVED);
	e820__update_table(e820_table);
पूर्ण

अटल व्योम __init पूर्णांकel_graphics_quirks(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	स्थिर काष्ठा पूर्णांकel_early_ops *early_ops;
	u16 device;
	पूर्णांक i;

	device = पढ़ो_pci_config_16(num, slot, func, PCI_DEVICE_ID);

	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकel_early_ids); i++) अणु
		kernel_uदीर्घ_t driver_data = पूर्णांकel_early_ids[i].driver_data;

		अगर (पूर्णांकel_early_ids[i].device != device)
			जारी;

		early_ops = (typeof(early_ops))driver_data;

		पूर्णांकel_graphics_stolen(num, slot, func, early_ops);

		वापस;
	पूर्ण
पूर्ण

अटल व्योम __init क्रमce_disable_hpet(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
#अगर_घोषित CONFIG_HPET_TIMER
	boot_hpet_disable = true;
	pr_info("x86/hpet: Will disable the HPET for this platform because it's not reliable\n");
#पूर्ण_अगर
पूर्ण

#घोषणा BCM4331_MMIO_SIZE	16384
#घोषणा BCM4331_PM_CAP		0x40
#घोषणा bcma_aपढ़ो32(reg)	ioपढ़ो32(mmio + 1 * BCMA_CORE_SIZE + reg)
#घोषणा bcma_aग_लिखो32(reg, val)	ioग_लिखो32(val, mmio + 1 * BCMA_CORE_SIZE + reg)

अटल व्योम __init apple_airport_reset(पूर्णांक bus, पूर्णांक slot, पूर्णांक func)
अणु
	व्योम __iomem *mmio;
	u16 pmcsr;
	u64 addr;
	पूर्णांक i;

	अगर (!x86_apple_machine)
		वापस;

	/* Card may have been put पूर्णांकo PCI_D3hot by grub quirk */
	pmcsr = पढ़ो_pci_config_16(bus, slot, func, BCM4331_PM_CAP + PCI_PM_CTRL);

	अगर ((pmcsr & PCI_PM_CTRL_STATE_MASK) != PCI_D0) अणु
		pmcsr &= ~PCI_PM_CTRL_STATE_MASK;
		ग_लिखो_pci_config_16(bus, slot, func, BCM4331_PM_CAP + PCI_PM_CTRL, pmcsr);
		mdelay(10);

		pmcsr = पढ़ो_pci_config_16(bus, slot, func, BCM4331_PM_CAP + PCI_PM_CTRL);
		अगर ((pmcsr & PCI_PM_CTRL_STATE_MASK) != PCI_D0) अणु
			pr_err("pci 0000:%02x:%02x.%d: Cannot power up Apple AirPort card\n",
			       bus, slot, func);
			वापस;
		पूर्ण
	पूर्ण

	addr  =      पढ़ो_pci_config(bus, slot, func, PCI_BASE_ADDRESS_0);
	addr |= (u64)पढ़ो_pci_config(bus, slot, func, PCI_BASE_ADDRESS_1) << 32;
	addr &= PCI_BASE_ADDRESS_MEM_MASK;

	mmio = early_ioremap(addr, BCM4331_MMIO_SIZE);
	अगर (!mmio) अणु
		pr_err("pci 0000:%02x:%02x.%d: Cannot iomap Apple AirPort card\n",
		       bus, slot, func);
		वापस;
	पूर्ण

	pr_info("Resetting Apple AirPort card (left enabled by EFI)\n");

	क्रम (i = 0; bcma_aपढ़ो32(BCMA_RESET_ST) && i < 30; i++)
		udelay(10);

	bcma_aग_लिखो32(BCMA_RESET_CTL, BCMA_RESET_CTL_RESET);
	bcma_aपढ़ो32(BCMA_RESET_CTL);
	udelay(1);

	bcma_aग_लिखो32(BCMA_RESET_CTL, 0);
	bcma_aपढ़ो32(BCMA_RESET_CTL);
	udelay(10);

	early_iounmap(mmio, BCM4331_MMIO_SIZE);
पूर्ण

#घोषणा QFLAG_APPLY_ONCE 	0x1
#घोषणा QFLAG_APPLIED		0x2
#घोषणा QFLAG_DONE		(QFLAG_APPLY_ONCE|QFLAG_APPLIED)
काष्ठा chipset अणु
	u32 venकरोr;
	u32 device;
	u32 class;
	u32 class_mask;
	u32 flags;
	व्योम (*f)(पूर्णांक num, पूर्णांक slot, पूर्णांक func);
पूर्ण;

अटल काष्ठा chipset early_qrk[] __initdata = अणु
	अणु PCI_VENDOR_ID_NVIDIA, PCI_ANY_ID,
	  PCI_CLASS_BRIDGE_PCI, PCI_ANY_ID, QFLAG_APPLY_ONCE, nvidia_bugs पूर्ण,
	अणु PCI_VENDOR_ID_VIA, PCI_ANY_ID,
	  PCI_CLASS_BRIDGE_PCI, PCI_ANY_ID, QFLAG_APPLY_ONCE, via_bugs पूर्ण,
	अणु PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_K8_NB,
	  PCI_CLASS_BRIDGE_HOST, PCI_ANY_ID, 0, fix_hypertransport_config पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_IXP400_SMBUS,
	  PCI_CLASS_SERIAL_SMBUS, PCI_ANY_ID, 0, ati_bugs पूर्ण,
	अणु PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_SBX00_SMBUS,
	  PCI_CLASS_SERIAL_SMBUS, PCI_ANY_ID, 0, ati_bugs_contd पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x3403, PCI_CLASS_BRIDGE_HOST,
	  PCI_BASE_CLASS_BRIDGE, 0, पूर्णांकel_remapping_check पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x3405, PCI_CLASS_BRIDGE_HOST,
	  PCI_BASE_CLASS_BRIDGE, 0, पूर्णांकel_remapping_check पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x3406, PCI_CLASS_BRIDGE_HOST,
	  PCI_BASE_CLASS_BRIDGE, 0, पूर्णांकel_remapping_check पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA, PCI_ANY_ID,
	  QFLAG_APPLY_ONCE, पूर्णांकel_graphics_quirks पूर्ण,
	/*
	 * HPET on the current version of the Baytrail platक्रमm has accuracy
	 * problems: it will halt in deep idle state - so we disable it.
	 *
	 * More details can be found in section 18.10.1.3 of the datasheet:
	 *
	 *    http://www.पूर्णांकel.com/content/dam/www/खुला/us/en/करोcuments/datasheets/atom-z8000-datasheet-vol-1.pdf
	 */
	अणु PCI_VENDOR_ID_INTEL, 0x0f00,
		PCI_CLASS_BRIDGE_HOST, PCI_ANY_ID, 0, क्रमce_disable_hpetपूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x3e20,
		PCI_CLASS_BRIDGE_HOST, PCI_ANY_ID, 0, क्रमce_disable_hpetपूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x3ec4,
		PCI_CLASS_BRIDGE_HOST, PCI_ANY_ID, 0, क्रमce_disable_hpetपूर्ण,
	अणु PCI_VENDOR_ID_INTEL, 0x8a12,
		PCI_CLASS_BRIDGE_HOST, PCI_ANY_ID, 0, क्रमce_disable_hpetपूर्ण,
	अणु PCI_VENDOR_ID_BROADCOM, 0x4331,
	  PCI_CLASS_NETWORK_OTHER, PCI_ANY_ID, 0, apple_airport_resetपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम __init early_pci_scan_bus(पूर्णांक bus);

/**
 * check_dev_quirk - apply early quirks to a given PCI device
 * @num: bus number
 * @slot: slot number
 * @func: PCI function
 *
 * Check the venकरोr & device ID against the early quirks table.
 *
 * If the device is single function, let early_pci_scan_bus() know so we करोn't
 * poke at this device again.
 */
अटल पूर्णांक __init check_dev_quirk(पूर्णांक num, पूर्णांक slot, पूर्णांक func)
अणु
	u16 class;
	u16 venकरोr;
	u16 device;
	u8 type;
	u8 sec;
	पूर्णांक i;

	class = पढ़ो_pci_config_16(num, slot, func, PCI_CLASS_DEVICE);

	अगर (class == 0xffff)
		वापस -1; /* no class, treat as single function */

	venकरोr = पढ़ो_pci_config_16(num, slot, func, PCI_VENDOR_ID);

	device = पढ़ो_pci_config_16(num, slot, func, PCI_DEVICE_ID);

	क्रम (i = 0; early_qrk[i].f != शून्य; i++) अणु
		अगर (((early_qrk[i].venकरोr == PCI_ANY_ID) ||
			(early_qrk[i].venकरोr == venकरोr)) &&
			((early_qrk[i].device == PCI_ANY_ID) ||
			(early_qrk[i].device == device)) &&
			(!((early_qrk[i].class ^ class) &
			    early_qrk[i].class_mask))) अणु
				अगर ((early_qrk[i].flags &
				     QFLAG_DONE) != QFLAG_DONE)
					early_qrk[i].f(num, slot, func);
				early_qrk[i].flags |= QFLAG_APPLIED;
			पूर्ण
	पूर्ण

	type = पढ़ो_pci_config_byte(num, slot, func,
				    PCI_HEADER_TYPE);

	अगर ((type & 0x7f) == PCI_HEADER_TYPE_BRIDGE) अणु
		sec = पढ़ो_pci_config_byte(num, slot, func, PCI_SECONDARY_BUS);
		अगर (sec > num)
			early_pci_scan_bus(sec);
	पूर्ण

	अगर (!(type & 0x80))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम __init early_pci_scan_bus(पूर्णांक bus)
अणु
	पूर्णांक slot, func;

	/* Poor man's PCI discovery */
	क्रम (slot = 0; slot < 32; slot++)
		क्रम (func = 0; func < 8; func++) अणु
			/* Only probe function 0 on single fn devices */
			अगर (check_dev_quirk(bus, slot, func))
				अवरोध;
		पूर्ण
पूर्ण

व्योम __init early_quirks(व्योम)
अणु
	अगर (!early_pci_allowed())
		वापस;

	early_pci_scan_bus(0);
पूर्ण
