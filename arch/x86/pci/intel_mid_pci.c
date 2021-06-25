<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel MID PCI support
 *   Copyright (c) 2008 Intel Corporation
 *     Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 *
 * Moorestown has an पूर्णांकeresting PCI implementation:
 *   - configuration space is memory mapped (as defined by MCFG)
 *   - Lincroft devices also have a real, type 1 configuration space
 *   - Early Lincroft silicon has a type 1 access bug that will cause
 *     a hang अगर non-existent devices are accessed
 *   - some devices have the "fixed BAR" capability, which means
 *     they can't be relocated or modअगरied; check क्रम that during
 *     BAR sizing
 *
 * So, we use the MCFG space क्रम all पढ़ोs and ग_लिखोs, but also send
 * Lincroft ग_लिखोs to type 1 space.  But only पढ़ो/ग_लिखो अगर the device
 * actually exists, otherwise वापस all 1s क्रम पढ़ोs and bit bucket
 * the ग_लिखोs.
 */

#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/smp.h>

#समावेश <यंत्र/cpu_device_id.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/पूर्णांकel-family.h>
#समावेश <यंत्र/पूर्णांकel-mid.h>
#समावेश <यंत्र/acpi.h>

#घोषणा PCIE_CAP_OFFSET	0x100

/* Quirks क्रम the listed devices */
#घोषणा PCI_DEVICE_ID_INTEL_MRFLD_MMC	0x1190
#घोषणा PCI_DEVICE_ID_INTEL_MRFLD_HSU	0x1191

/* Fixed BAR fields */
#घोषणा PCIE_VNDR_CAP_ID_FIXED_BAR 0x00	/* Fixed BAR (TBD) */
#घोषणा PCI_FIXED_BAR_0_SIZE	0x04
#घोषणा PCI_FIXED_BAR_1_SIZE	0x08
#घोषणा PCI_FIXED_BAR_2_SIZE	0x0c
#घोषणा PCI_FIXED_BAR_3_SIZE	0x10
#घोषणा PCI_FIXED_BAR_4_SIZE	0x14
#घोषणा PCI_FIXED_BAR_5_SIZE	0x1c

अटल पूर्णांक pci_soc_mode;

/**
 * fixed_bar_cap - वापस the offset of the fixed BAR cap अगर found
 * @bus: PCI bus
 * @devfn: device in question
 *
 * Look क्रम the fixed BAR cap on @bus and @devfn, वापसing its offset
 * अगर found or 0 otherwise.
 */
अटल पूर्णांक fixed_bar_cap(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn)
अणु
	पूर्णांक pos;
	u32 pcie_cap = 0, cap_data;

	pos = PCIE_CAP_OFFSET;

	अगर (!raw_pci_ext_ops)
		वापस 0;

	जबतक (pos) अणु
		अगर (raw_pci_ext_ops->पढ़ो(pci_करोमुख्य_nr(bus), bus->number,
					  devfn, pos, 4, &pcie_cap))
			वापस 0;

		अगर (PCI_EXT_CAP_ID(pcie_cap) == 0x0000 ||
			PCI_EXT_CAP_ID(pcie_cap) == 0xffff)
			अवरोध;

		अगर (PCI_EXT_CAP_ID(pcie_cap) == PCI_EXT_CAP_ID_VNDR) अणु
			raw_pci_ext_ops->पढ़ो(pci_करोमुख्य_nr(bus), bus->number,
					      devfn, pos + 4, 4, &cap_data);
			अगर ((cap_data & 0xffff) == PCIE_VNDR_CAP_ID_FIXED_BAR)
				वापस pos;
		पूर्ण

		pos = PCI_EXT_CAP_NEXT(pcie_cap);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_device_update_fixed(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
				   पूर्णांक reg, पूर्णांक len, u32 val, पूर्णांक offset)
अणु
	u32 size;
	अचिन्हित पूर्णांक करोमुख्य, busnum;
	पूर्णांक bar = (reg - PCI_BASE_ADDRESS_0) >> 2;

	करोमुख्य = pci_करोमुख्य_nr(bus);
	busnum = bus->number;

	अगर (val == ~0 && len == 4) अणु
		अचिन्हित दीर्घ decode;

		raw_pci_ext_ops->पढ़ो(करोमुख्य, busnum, devfn,
			       offset + 8 + (bar * 4), 4, &size);

		/* Turn the size पूर्णांकo a decode pattern क्रम the sizing code */
		अगर (size) अणु
			decode = size - 1;
			decode |= decode >> 1;
			decode |= decode >> 2;
			decode |= decode >> 4;
			decode |= decode >> 8;
			decode |= decode >> 16;
			decode++;
			decode = ~(decode - 1);
		पूर्ण अन्यथा अणु
			decode = 0;
		पूर्ण

		/*
		 * If val is all ones, the core code is trying to size the reg,
		 * so update the mmconfig space with the real size.
		 *
		 * Note: this assumes the fixed size we got is a घातer of two.
		 */
		वापस raw_pci_ext_ops->ग_लिखो(करोमुख्य, busnum, devfn, reg, 4,
				       decode);
	पूर्ण

	/* This is some other kind of BAR ग_लिखो, so just करो it. */
	वापस raw_pci_ext_ops->ग_लिखो(करोमुख्य, busnum, devfn, reg, len, val);
पूर्ण

/**
 * type1_access_ok - check whether to use type 1
 * @bus: bus number
 * @devfn: device & function in question
 * @reg: configuration रेजिस्टर offset
 *
 * If the bus is on a Lincroft chip and it exists, or is not on a Lincroft at
 * all, the we can go ahead with any पढ़ोs & ग_लिखोs.  If it's on a Lincroft,
 * but करोesn't exist, aव्योम the access altogether to keep the chip from
 * hanging.
 */
अटल bool type1_access_ok(अचिन्हित पूर्णांक bus, अचिन्हित पूर्णांक devfn, पूर्णांक reg)
अणु
	/*
	 * This is a workaround क्रम A0 LNC bug where PCI status रेजिस्टर करोes
	 * not have new CAP bit set. can not be written by SW either.
	 *
	 * PCI header type in real LNC indicates a single function device, this
	 * will prevent probing other devices under the same function in PCI
	 * shim. Thereक्रमe, use the header type in shim instead.
	 */
	अगर (reg >= 0x100 || reg == PCI_STATUS || reg == PCI_HEADER_TYPE)
		वापस false;
	अगर (bus == 0 && (devfn == PCI_DEVFN(2, 0)
				|| devfn == PCI_DEVFN(0, 0)
				|| devfn == PCI_DEVFN(3, 0)))
		वापस true;
	वापस false; /* Langwell on others */
पूर्ण

अटल पूर्णांक pci_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		    पूर्णांक size, u32 *value)
अणु
	अगर (type1_access_ok(bus->number, devfn, where))
		वापस pci_direct_conf1.पढ़ो(pci_करोमुख्य_nr(bus), bus->number,
					devfn, where, size, value);
	वापस raw_pci_ext_ops->पढ़ो(pci_करोमुख्य_nr(bus), bus->number,
			      devfn, where, size, value);
पूर्ण

अटल पूर्णांक pci_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
		     पूर्णांक size, u32 value)
अणु
	पूर्णांक offset;

	/*
	 * On MRST, there is no PCI ROM BAR, this will cause a subsequent पढ़ो
	 * to ROM BAR वापस 0 then being ignored.
	 */
	अगर (where == PCI_ROM_ADDRESS)
		वापस 0;

	/*
	 * Devices with fixed BARs need special handling:
	 *   - BAR sizing code will save, ग_लिखो ~0, पढ़ो size, restore
	 *   - so ग_लिखोs to fixed BARs need special handling
	 *   - other ग_लिखोs to fixed BAR devices should go through mmconfig
	 */
	offset = fixed_bar_cap(bus, devfn);
	अगर (offset &&
	    (where >= PCI_BASE_ADDRESS_0 && where <= PCI_BASE_ADDRESS_5)) अणु
		वापस pci_device_update_fixed(bus, devfn, where, size, value,
					       offset);
	पूर्ण

	/*
	 * On Moorestown update both real & mmconfig space
	 * Note: early Lincroft silicon can't handle type 1 accesses to
	 *       non-existent devices, so just eat the ग_लिखो in that हाल.
	 */
	अगर (type1_access_ok(bus->number, devfn, where))
		वापस pci_direct_conf1.ग_लिखो(pci_करोमुख्य_nr(bus), bus->number,
					      devfn, where, size, value);
	वापस raw_pci_ext_ops->ग_लिखो(pci_करोमुख्य_nr(bus), bus->number, devfn,
			       where, size, value);
पूर्ण

अटल स्थिर काष्ठा x86_cpu_id पूर्णांकel_mid_cpu_ids[] = अणु
	X86_MATCH_INTEL_FAM6_MODEL(ATOM_SILVERMONT_MID, शून्य),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक पूर्णांकel_mid_pci_irq_enable(काष्ठा pci_dev *dev)
अणु
	स्थिर काष्ठा x86_cpu_id *id;
	काष्ठा irq_alloc_info info;
	bool polarity_low;
	u16 model = 0;
	पूर्णांक ret;
	u8 gsi;

	अगर (dev->irq_managed && dev->irq > 0)
		वापस 0;

	ret = pci_पढ़ो_config_byte(dev, PCI_INTERRUPT_LINE, &gsi);
	अगर (ret < 0) अणु
		dev_warn(&dev->dev, "Failed to read interrupt line: %d\n", ret);
		वापस ret;
	पूर्ण

	id = x86_match_cpu(पूर्णांकel_mid_cpu_ids);
	अगर (id)
		model = id->model;

	चयन (model) अणु
	हाल INTEL_FAM6_ATOM_SILVERMONT_MID:
		polarity_low = false;

		/* Special treaपंचांगent क्रम IRQ0 */
		अगर (gsi == 0) अणु
			/*
			 * Skip HS UART common रेजिस्टरs device since it has
			 * IRQ0 asचिन्हित and not used by the kernel.
			 */
			अगर (dev->device == PCI_DEVICE_ID_INTEL_MRFLD_HSU)
				वापस -EBUSY;
			/*
			 * TNG has IRQ0 asचिन्हित to eMMC controller. But there
			 * are also other devices with bogus PCI configuration
			 * that have IRQ0 asचिन्हित. This check ensures that
			 * eMMC माला_लो it. The rest of devices still could be
			 * enabled without पूर्णांकerrupt line being allocated.
			 */
			अगर (dev->device != PCI_DEVICE_ID_INTEL_MRFLD_MMC)
				वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		polarity_low = true;
		अवरोध;
	पूर्ण

	ioapic_set_alloc_attr(&info, dev_to_node(&dev->dev), 1, polarity_low);

	/*
	 * MRST only have IOAPIC, the PCI irq lines are 1:1 mapped to
	 * IOAPIC RTE entries, so we just enable RTE क्रम the device.
	 */
	ret = mp_map_gsi_to_irq(gsi, IOAPIC_MAP_ALLOC, &info);
	अगर (ret < 0)
		वापस ret;

	dev->irq = ret;
	dev->irq_managed = 1;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_mid_pci_irq_disable(काष्ठा pci_dev *dev)
अणु
	अगर (!mp_should_keep_irq(&dev->dev) && dev->irq_managed &&
	    dev->irq > 0) अणु
		mp_unmap_irq(dev->irq);
		dev->irq_managed = 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_ops पूर्णांकel_mid_pci_ops __initस्थिर = अणु
	.पढ़ो = pci_पढ़ो,
	.ग_लिखो = pci_ग_लिखो,
पूर्ण;

/**
 * पूर्णांकel_mid_pci_init - installs पूर्णांकel_mid_pci_ops
 *
 * Moorestown has an पूर्णांकeresting PCI implementation (see above).
 * Called when the early platक्रमm detection installs it.
 */
पूर्णांक __init पूर्णांकel_mid_pci_init(व्योम)
अणु
	pr_info("Intel MID platform detected, using MID PCI ops\n");
	pci_mmcfg_late_init();
	pcibios_enable_irq = पूर्णांकel_mid_pci_irq_enable;
	pcibios_disable_irq = पूर्णांकel_mid_pci_irq_disable;
	pci_root_ops = पूर्णांकel_mid_pci_ops;
	pci_soc_mode = 1;
	/* Continue with standard init */
	acpi_noirq_set();
	वापस 1;
पूर्ण

/*
 * Langwell devices are not true PCI devices; they are not subject to 10 ms
 * d3 to d0 delay required by PCI spec.
 */
अटल व्योम pci_d3delay_fixup(काष्ठा pci_dev *dev)
अणु
	/*
	 * PCI fixups are effectively decided compile समय. If we have a dual
	 * SoC/non-SoC kernel we करोn't want to mangle d3 on non-SoC devices.
	 */
	अगर (!pci_soc_mode)
		वापस;
	/*
	 * True PCI devices in Lincroft should allow type 1 access, the rest
	 * are Langwell fake PCI devices.
	 */
	अगर (type1_access_ok(dev->bus->number, dev->devfn, PCI_DEVICE_ID))
		वापस;
	dev->d3hot_delay = 0;
पूर्ण
DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_ANY_ID, pci_d3delay_fixup);

अटल व्योम mid_घातer_off_one_device(काष्ठा pci_dev *dev)
अणु
	u16 pmcsr;

	/*
	 * Update current state first, otherwise PCI core enक्रमces PCI_D0 in
	 * pci_set_घातer_state() क्रम devices which status was PCI_UNKNOWN.
	 */
	pci_पढ़ो_config_word(dev, dev->pm_cap + PCI_PM_CTRL, &pmcsr);
	dev->current_state = (pci_घातer_t __क्रमce)(pmcsr & PCI_PM_CTRL_STATE_MASK);

	pci_set_घातer_state(dev, PCI_D3hot);
पूर्ण

अटल व्योम mid_घातer_off_devices(काष्ठा pci_dev *dev)
अणु
	पूर्णांक id;

	अगर (!pci_soc_mode)
		वापस;

	id = पूर्णांकel_mid_pwr_get_lss_id(dev);
	अगर (id < 0)
		वापस;

	/*
	 * This sets only PMCSR bits. The actual घातer off will happen in
	 * arch/x86/platक्रमm/पूर्णांकel-mid/pwr.c.
	 */
	mid_घातer_off_one_device(dev);
पूर्ण

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_INTEL, PCI_ANY_ID, mid_घातer_off_devices);

/*
 * Langwell devices reside at fixed offsets, करोn't try to move them.
 */
अटल व्योम pci_fixed_bar_fixup(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ offset;
	u32 size;
	पूर्णांक i;

	अगर (!pci_soc_mode)
		वापस;

	/* Must have extended configuration space */
	अगर (dev->cfg_size < PCIE_CAP_OFFSET + 4)
		वापस;

	/* Fixup the BAR sizes क्रम fixed BAR devices and make them unmoveable */
	offset = fixed_bar_cap(dev->bus, dev->devfn);
	अगर (!offset || PCI_DEVFN(2, 0) == dev->devfn ||
	    PCI_DEVFN(2, 2) == dev->devfn)
		वापस;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		pci_पढ़ो_config_dword(dev, offset + 8 + (i * 4), &size);
		dev->resource[i].end = dev->resource[i].start + size - 1;
		dev->resource[i].flags |= IORESOURCE_PCI_FIXED;
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_HEADER(PCI_VENDOR_ID_INTEL, PCI_ANY_ID, pci_fixed_bar_fixup);
