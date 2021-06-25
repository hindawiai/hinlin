<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * the ISA Virtual Support Module of AMD CS5536
 *
 * Copyright (C) 2007 Lemote, Inc.
 * Author : jlliu, liujl@lemote.com
 *
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <linux/pci.h>
#समावेश <cs5536/cs5536.h>
#समावेश <cs5536/cs5536_pci.h>

/* common variables क्रम PCI_ISA_READ/WRITE_BAR */
अटल स्थिर u32 भागil_msr_reg[6] = अणु
	DIVIL_MSR_REG(DIVIL_LBAR_SMB), DIVIL_MSR_REG(DIVIL_LBAR_GPIO),
	DIVIL_MSR_REG(DIVIL_LBAR_MFGPT), DIVIL_MSR_REG(DIVIL_LBAR_IRQ),
	DIVIL_MSR_REG(DIVIL_LBAR_PMS), DIVIL_MSR_REG(DIVIL_LBAR_ACPI),
पूर्ण;

अटल स्थिर u32 soft_bar_flag[6] = अणु
	SOFT_BAR_SMB_FLAG, SOFT_BAR_GPIO_FLAG, SOFT_BAR_MFGPT_FLAG,
	SOFT_BAR_IRQ_FLAG, SOFT_BAR_PMS_FLAG, SOFT_BAR_ACPI_FLAG,
पूर्ण;

अटल स्थिर u32 sb_msr_reg[6] = अणु
	SB_MSR_REG(SB_R0), SB_MSR_REG(SB_R1), SB_MSR_REG(SB_R2),
	SB_MSR_REG(SB_R3), SB_MSR_REG(SB_R4), SB_MSR_REG(SB_R5),
पूर्ण;

अटल स्थिर u32 bar_space_range[6] = अणु
	CS5536_SMB_RANGE, CS5536_GPIO_RANGE, CS5536_MFGPT_RANGE,
	CS5536_IRQ_RANGE, CS5536_PMS_RANGE, CS5536_ACPI_RANGE,
पूर्ण;

अटल स्थिर पूर्णांक bar_space_len[6] = अणु
	CS5536_SMB_LENGTH, CS5536_GPIO_LENGTH, CS5536_MFGPT_LENGTH,
	CS5536_IRQ_LENGTH, CS5536_PMS_LENGTH, CS5536_ACPI_LENGTH,
पूर्ण;

/*
 * enable the भागil module bar space.
 *
 * For all the DIVIL module LBAR, you should control the DIVIL LBAR reg
 * and the RCONFx(0~5) reg to use the modules.
 */
अटल व्योम भागil_lbar_enable(व्योम)
अणु
	u32 hi, lo;
	पूर्णांक offset;

	/*
	 * The DIVIL IRQ is not used yet. and make the RCONF0 reserved.
	 */

	क्रम (offset = DIVIL_LBAR_SMB; offset <= DIVIL_LBAR_PMS; offset++) अणु
		_rdmsr(DIVIL_MSR_REG(offset), &hi, &lo);
		hi |= 0x01;
		_wrmsr(DIVIL_MSR_REG(offset), hi, lo);
	पूर्ण
पूर्ण

/*
 * disable the भागil module bar space.
 */
अटल व्योम भागil_lbar_disable(व्योम)
अणु
	u32 hi, lo;
	पूर्णांक offset;

	क्रम (offset = DIVIL_LBAR_SMB; offset <= DIVIL_LBAR_PMS; offset++) अणु
		_rdmsr(DIVIL_MSR_REG(offset), &hi, &lo);
		hi &= ~0x01;
		_wrmsr(DIVIL_MSR_REG(offset), hi, lo);
	पूर्ण
पूर्ण

/*
 * BAR ग_लिखो: ग_लिखो value to the n BAR
 */

व्योम pci_isa_ग_लिखो_bar(पूर्णांक n, u32 value)
अणु
	u32 hi = 0, lo = value;

	अगर (value == PCI_BAR_RANGE_MASK) अणु
		_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
		lo |= soft_bar_flag[n];
		_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
	पूर्ण अन्यथा अगर (value & 0x01) अणु
		/* NATIVE reg */
		hi = 0x0000f001;
		lo &= bar_space_range[n];
		_wrmsr(भागil_msr_reg[n], hi, lo);

		/* RCONFx is 4bytes in units क्रम I/O space */
		hi = ((value & 0x000ffffc) << 12) |
		    ((bar_space_len[n] - 4) << 12) | 0x01;
		lo = ((value & 0x000ffffc) << 12) | 0x01;
		_wrmsr(sb_msr_reg[n], hi, lo);
	पूर्ण
पूर्ण

/*
 * BAR पढ़ो: पढ़ो the n BAR
 */

u32 pci_isa_पढ़ो_bar(पूर्णांक n)
अणु
	u32 conf_data = 0;
	u32 hi, lo;

	_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
	अगर (lo & soft_bar_flag[n]) अणु
		conf_data = bar_space_range[n] | PCI_BASE_ADDRESS_SPACE_IO;
		lo &= ~soft_bar_flag[n];
		_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
	पूर्ण अन्यथा अणु
		_rdmsr(भागil_msr_reg[n], &hi, &lo);
		conf_data = lo & bar_space_range[n];
		conf_data |= 0x01;
		conf_data &= ~0x02;
	पूर्ण
	वापस conf_data;
पूर्ण

/*
 * isa_ग_लिखो: ISA ग_लिखो transfer
 *
 * We assume that this is not a bus master transfer.
 */
व्योम pci_isa_ग_लिखो_reg(पूर्णांक reg, u32 value)
अणु
	u32 hi = 0, lo = value;
	u32 temp;

	चयन (reg) अणु
	हाल PCI_COMMAND:
		अगर (value & PCI_COMMAND_IO)
			भागil_lbar_enable();
		अन्यथा
			भागil_lbar_disable();
		अवरोध;
	हाल PCI_STATUS:
		_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
		temp = lo & 0x0000ffff;
		अगर ((value & PCI_STATUS_SIG_TARGET_ABORT) &&
		    (lo & SB_TAS_ERR_EN))
			temp |= SB_TAS_ERR_FLAG;

		अगर ((value & PCI_STATUS_REC_TARGET_ABORT) &&
		    (lo & SB_TAR_ERR_EN))
			temp |= SB_TAR_ERR_FLAG;

		अगर ((value & PCI_STATUS_REC_MASTER_ABORT)
		    && (lo & SB_MAR_ERR_EN))
			temp |= SB_MAR_ERR_FLAG;

		अगर ((value & PCI_STATUS_DETECTED_PARITY)
		    && (lo & SB_PARE_ERR_EN))
			temp |= SB_PARE_ERR_FLAG;

		lo = temp;
		_wrmsr(SB_MSR_REG(SB_ERROR), hi, lo);
		अवरोध;
	हाल PCI_CACHE_LINE_SIZE:
		value &= 0x0000ff00;
		_rdmsr(SB_MSR_REG(SB_CTRL), &hi, &lo);
		hi &= 0xffffff00;
		hi |= (value >> 8);
		_wrmsr(SB_MSR_REG(SB_CTRL), hi, lo);
		अवरोध;
	हाल PCI_BAR0_REG:
		pci_isa_ग_लिखो_bar(0, value);
		अवरोध;
	हाल PCI_BAR1_REG:
		pci_isa_ग_लिखो_bar(1, value);
		अवरोध;
	हाल PCI_BAR2_REG:
		pci_isa_ग_लिखो_bar(2, value);
		अवरोध;
	हाल PCI_BAR3_REG:
		pci_isa_ग_लिखो_bar(3, value);
		अवरोध;
	हाल PCI_BAR4_REG:
		pci_isa_ग_लिखो_bar(4, value);
		अवरोध;
	हाल PCI_BAR5_REG:
		pci_isa_ग_लिखो_bar(5, value);
		अवरोध;
	हाल PCI_UART1_INT_REG:
		_rdmsr(DIVIL_MSR_REG(PIC_YSEL_HIGH), &hi, &lo);
		/* disable uart1 पूर्णांकerrupt in PIC */
		lo &= ~(0xf << 24);
		अगर (value)	/* enable uart1 पूर्णांकerrupt in PIC */
			lo |= (CS5536_UART1_INTR << 24);
		_wrmsr(DIVIL_MSR_REG(PIC_YSEL_HIGH), hi, lo);
		अवरोध;
	हाल PCI_UART2_INT_REG:
		_rdmsr(DIVIL_MSR_REG(PIC_YSEL_HIGH), &hi, &lo);
		/* disable uart2 पूर्णांकerrupt in PIC */
		lo &= ~(0xf << 28);
		अगर (value)	/* enable uart2 पूर्णांकerrupt in PIC */
			lo |= (CS5536_UART2_INTR << 28);
		_wrmsr(DIVIL_MSR_REG(PIC_YSEL_HIGH), hi, lo);
		अवरोध;
	हाल PCI_ISA_FIXUP_REG:
		अगर (value) अणु
			/* enable the TARGET ABORT/MASTER ABORT etc. */
			_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
			lo |= 0x00000063;
			_wrmsr(SB_MSR_REG(SB_ERROR), hi, lo);
		पूर्ण

	शेष:
		/* ALL OTHER PCI CONFIG SPACE HEADER IS NOT IMPLEMENTED. */
		अवरोध;
	पूर्ण
पूर्ण

/*
 * isa_पढ़ो: ISA पढ़ो transfers
 *
 * We assume that this is not a bus master transfer.
 */
u32 pci_isa_पढ़ो_reg(पूर्णांक reg)
अणु
	u32 conf_data = 0;
	u32 hi, lo;

	चयन (reg) अणु
	हाल PCI_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_ISA_DEVICE_ID, CS5536_VENDOR_ID);
		अवरोध;
	हाल PCI_COMMAND:
		/* we just check the first LBAR क्रम the IO enable bit, */
		/* maybe we should changed later. */
		_rdmsr(DIVIL_MSR_REG(DIVIL_LBAR_SMB), &hi, &lo);
		अगर (hi & 0x01)
			conf_data |= PCI_COMMAND_IO;
		अवरोध;
	हाल PCI_STATUS:
		conf_data |= PCI_STATUS_66MHZ;
		conf_data |= PCI_STATUS_DEVSEL_MEDIUM;
		conf_data |= PCI_STATUS_FAST_BACK;

		_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
		अगर (lo & SB_TAS_ERR_FLAG)
			conf_data |= PCI_STATUS_SIG_TARGET_ABORT;
		अगर (lo & SB_TAR_ERR_FLAG)
			conf_data |= PCI_STATUS_REC_TARGET_ABORT;
		अगर (lo & SB_MAR_ERR_FLAG)
			conf_data |= PCI_STATUS_REC_MASTER_ABORT;
		अगर (lo & SB_PARE_ERR_FLAG)
			conf_data |= PCI_STATUS_DETECTED_PARITY;
		अवरोध;
	हाल PCI_CLASS_REVISION:
		_rdmsr(GLCP_MSR_REG(GLCP_CHIP_REV_ID), &hi, &lo);
		conf_data = lo & 0x000000ff;
		conf_data |= (CS5536_ISA_CLASS_CODE << 8);
		अवरोध;
	हाल PCI_CACHE_LINE_SIZE:
		_rdmsr(SB_MSR_REG(SB_CTRL), &hi, &lo);
		hi &= 0x000000f8;
		conf_data = CFG_PCI_CACHE_LINE_SIZE(PCI_BRIDGE_HEADER_TYPE, hi);
		अवरोध;
		/*
		 * we only use the LBAR of DIVIL, no RCONF used.
		 * all of them are IO space.
		 */
	हाल PCI_BAR0_REG:
		वापस pci_isa_पढ़ो_bar(0);
		अवरोध;
	हाल PCI_BAR1_REG:
		वापस pci_isa_पढ़ो_bar(1);
		अवरोध;
	हाल PCI_BAR2_REG:
		वापस pci_isa_पढ़ो_bar(2);
		अवरोध;
	हाल PCI_BAR3_REG:
		अवरोध;
	हाल PCI_BAR4_REG:
		वापस pci_isa_पढ़ो_bar(4);
		अवरोध;
	हाल PCI_BAR5_REG:
		वापस pci_isa_पढ़ो_bar(5);
		अवरोध;
	हाल PCI_CARDBUS_CIS:
		conf_data = PCI_CARDBUS_CIS_POINTER;
		अवरोध;
	हाल PCI_SUBSYSTEM_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_ISA_SUB_ID, CS5536_SUB_VENDOR_ID);
		अवरोध;
	हाल PCI_ROM_ADDRESS:
		conf_data = PCI_EXPANSION_ROM_BAR;
		अवरोध;
	हाल PCI_CAPABILITY_LIST:
		conf_data = PCI_CAPLIST_POINTER;
		अवरोध;
	हाल PCI_INTERRUPT_LINE:
		/* no पूर्णांकerrupt used here */
		conf_data = CFG_PCI_INTERRUPT_LINE(0x00, 0x00);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस conf_data;
पूर्ण

/*
 * The mfgpt समयr पूर्णांकerrupt is running early, so we must keep the south bridge
 * mmio always enabled. Otherwise we may race with the PCI configuration which
 * may temporarily disable it. When that happens and the समयr पूर्णांकerrupt fires,
 * we are not able to clear it and the प्रणाली will hang.
 */
अटल व्योम cs5536_isa_mmio_always_on(काष्ठा pci_dev *dev)
अणु
	dev->mmio_always_on = 1;
पूर्ण
DECLARE_PCI_FIXUP_CLASS_EARLY(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_CS5536_ISA,
	PCI_CLASS_BRIDGE_ISA, 8, cs5536_isa_mmio_always_on);
