<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * the ACC Virtual Support Module of AMD CS5536
 *
 * Copyright (C) 2007 Lemote, Inc.
 * Author : jlliu, liujl@lemote.com
 *
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <cs5536/cs5536.h>
#समावेश <cs5536/cs5536_pci.h>

व्योम pci_acc_ग_लिखो_reg(पूर्णांक reg, u32 value)
अणु
	u32 hi = 0, lo = value;

	चयन (reg) अणु
	हाल PCI_COMMAND:
		_rdmsr(GLIU_MSR_REG(GLIU_PAE), &hi, &lo);
		अगर (value & PCI_COMMAND_MASTER)
			lo |= (0x03 << 8);
		अन्यथा
			lo &= ~(0x03 << 8);
		_wrmsr(GLIU_MSR_REG(GLIU_PAE), hi, lo);
		अवरोध;
	हाल PCI_STATUS:
		अगर (value & PCI_STATUS_PARITY) अणु
			_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
			अगर (lo & SB_PARE_ERR_FLAG) अणु
				lo = (lo & 0x0000ffff) | SB_PARE_ERR_FLAG;
				_wrmsr(SB_MSR_REG(SB_ERROR), hi, lo);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल PCI_BAR0_REG:
		अगर (value == PCI_BAR_RANGE_MASK) अणु
			_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
			lo |= SOFT_BAR_ACC_FLAG;
			_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
		पूर्ण अन्यथा अगर (value & 0x01) अणु
			value &= 0xfffffffc;
			hi = 0xA0000000 | ((value & 0x000ff000) >> 12);
			lo = 0x000fff80 | ((value & 0x00000fff) << 20);
			_wrmsr(GLIU_MSR_REG(GLIU_IOD_BM1), hi, lo);
		पूर्ण
		अवरोध;
	हाल PCI_ACC_INT_REG:
		_rdmsr(DIVIL_MSR_REG(PIC_YSEL_LOW), &hi, &lo);
		/* disable all the usb पूर्णांकerrupt in PIC */
		lo &= ~(0xf << PIC_YSEL_LOW_ACC_SHIFT);
		अगर (value)	/* enable all the acc पूर्णांकerrupt in PIC */
			lo |= (CS5536_ACC_INTR << PIC_YSEL_LOW_ACC_SHIFT);
		_wrmsr(DIVIL_MSR_REG(PIC_YSEL_LOW), hi, lo);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

u32 pci_acc_पढ़ो_reg(पूर्णांक reg)
अणु
	u32 hi, lo;
	u32 conf_data = 0;

	चयन (reg) अणु
	हाल PCI_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_ACC_DEVICE_ID, CS5536_VENDOR_ID);
		अवरोध;
	हाल PCI_COMMAND:
		_rdmsr(GLIU_MSR_REG(GLIU_IOD_BM1), &hi, &lo);
		अगर (((lo & 0xfff00000) || (hi & 0x000000ff))
		    && ((hi & 0xf0000000) == 0xa0000000))
			conf_data |= PCI_COMMAND_IO;
		_rdmsr(GLIU_MSR_REG(GLIU_PAE), &hi, &lo);
		अगर ((lo & 0x300) == 0x300)
			conf_data |= PCI_COMMAND_MASTER;
		अवरोध;
	हाल PCI_STATUS:
		conf_data |= PCI_STATUS_66MHZ;
		conf_data |= PCI_STATUS_FAST_BACK;
		_rdmsr(SB_MSR_REG(SB_ERROR), &hi, &lo);
		अगर (lo & SB_PARE_ERR_FLAG)
			conf_data |= PCI_STATUS_PARITY;
		conf_data |= PCI_STATUS_DEVSEL_MEDIUM;
		अवरोध;
	हाल PCI_CLASS_REVISION:
		_rdmsr(ACC_MSR_REG(ACC_CAP), &hi, &lo);
		conf_data = lo & 0x000000ff;
		conf_data |= (CS5536_ACC_CLASS_CODE << 8);
		अवरोध;
	हाल PCI_CACHE_LINE_SIZE:
		conf_data =
		    CFG_PCI_CACHE_LINE_SIZE(PCI_NORMAL_HEADER_TYPE,
					    PCI_NORMAL_LATENCY_TIMER);
		अवरोध;
	हाल PCI_BAR0_REG:
		_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
		अगर (lo & SOFT_BAR_ACC_FLAG) अणु
			conf_data = CS5536_ACC_RANGE |
			    PCI_BASE_ADDRESS_SPACE_IO;
			lo &= ~SOFT_BAR_ACC_FLAG;
			_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
		पूर्ण अन्यथा अणु
			_rdmsr(GLIU_MSR_REG(GLIU_IOD_BM1), &hi, &lo);
			conf_data = (hi & 0x000000ff) << 12;
			conf_data |= (lo & 0xfff00000) >> 20;
			conf_data |= 0x01;
			conf_data &= ~0x02;
		पूर्ण
		अवरोध;
	हाल PCI_CARDBUS_CIS:
		conf_data = PCI_CARDBUS_CIS_POINTER;
		अवरोध;
	हाल PCI_SUBSYSTEM_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_ACC_SUB_ID, CS5536_SUB_VENDOR_ID);
		अवरोध;
	हाल PCI_ROM_ADDRESS:
		conf_data = PCI_EXPANSION_ROM_BAR;
		अवरोध;
	हाल PCI_CAPABILITY_LIST:
		conf_data = PCI_CAPLIST_USB_POINTER;
		अवरोध;
	हाल PCI_INTERRUPT_LINE:
		conf_data =
		    CFG_PCI_INTERRUPT_LINE(PCI_DEFAULT_PIN, CS5536_ACC_INTR);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस conf_data;
पूर्ण
