<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * the EHCI Virtual Support Module of AMD CS5536
 *
 * Copyright (C) 2007 Lemote, Inc.
 * Author : jlliu, liujl@lemote.com
 *
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <cs5536/cs5536.h>
#समावेश <cs5536/cs5536_pci.h>

व्योम pci_ehci_ग_लिखो_reg(पूर्णांक reg, u32 value)
अणु
	u32 hi = 0, lo = value;

	चयन (reg) अणु
	हाल PCI_COMMAND:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		अगर (value & PCI_COMMAND_MASTER)
			hi |= PCI_COMMAND_MASTER;
		अन्यथा
			hi &= ~PCI_COMMAND_MASTER;

		अगर (value & PCI_COMMAND_MEMORY)
			hi |= PCI_COMMAND_MEMORY;
		अन्यथा
			hi &= ~PCI_COMMAND_MEMORY;
		_wrmsr(USB_MSR_REG(USB_EHCI), hi, lo);
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
			lo |= SOFT_BAR_EHCI_FLAG;
			_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
		पूर्ण अन्यथा अगर ((value & 0x01) == 0x00) अणु
			_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
			lo = value;
			_wrmsr(USB_MSR_REG(USB_EHCI), hi, lo);

			value &= 0xfffffff0;
			hi = 0x40000000 | ((value & 0xff000000) >> 24);
			lo = 0x000fffff | ((value & 0x00fff000) << 8);
			_wrmsr(GLIU_MSR_REG(GLIU_P2D_BM4), hi, lo);
		पूर्ण
		अवरोध;
	हाल PCI_EHCI_LEGSMIEN_REG:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		hi &= 0x003f0000;
		hi |= (value & 0x3f) << 16;
		_wrmsr(USB_MSR_REG(USB_EHCI), hi, lo);
		अवरोध;
	हाल PCI_EHCI_FLADJ_REG:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		hi &= ~0x00003f00;
		hi |= value & 0x00003f00;
		_wrmsr(USB_MSR_REG(USB_EHCI), hi, lo);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

u32 pci_ehci_पढ़ो_reg(पूर्णांक reg)
अणु
	u32 conf_data = 0;
	u32 hi, lo;

	चयन (reg) अणु
	हाल PCI_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_EHCI_DEVICE_ID, CS5536_VENDOR_ID);
		अवरोध;
	हाल PCI_COMMAND:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		अगर (hi & PCI_COMMAND_MASTER)
			conf_data |= PCI_COMMAND_MASTER;
		अगर (hi & PCI_COMMAND_MEMORY)
			conf_data |= PCI_COMMAND_MEMORY;
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
		_rdmsr(USB_MSR_REG(USB_CAP), &hi, &lo);
		conf_data = lo & 0x000000ff;
		conf_data |= (CS5536_EHCI_CLASS_CODE << 8);
		अवरोध;
	हाल PCI_CACHE_LINE_SIZE:
		conf_data =
		    CFG_PCI_CACHE_LINE_SIZE(PCI_NORMAL_HEADER_TYPE,
					    PCI_NORMAL_LATENCY_TIMER);
		अवरोध;
	हाल PCI_BAR0_REG:
		_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
		अगर (lo & SOFT_BAR_EHCI_FLAG) अणु
			conf_data = CS5536_EHCI_RANGE |
			    PCI_BASE_ADDRESS_SPACE_MEMORY;
			lo &= ~SOFT_BAR_EHCI_FLAG;
			_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
		पूर्ण अन्यथा अणु
			_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
			conf_data = lo & 0xfffff000;
		पूर्ण
		अवरोध;
	हाल PCI_CARDBUS_CIS:
		conf_data = PCI_CARDBUS_CIS_POINTER;
		अवरोध;
	हाल PCI_SUBSYSTEM_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_EHCI_SUB_ID, CS5536_SUB_VENDOR_ID);
		अवरोध;
	हाल PCI_ROM_ADDRESS:
		conf_data = PCI_EXPANSION_ROM_BAR;
		अवरोध;
	हाल PCI_CAPABILITY_LIST:
		conf_data = PCI_CAPLIST_USB_POINTER;
		अवरोध;
	हाल PCI_INTERRUPT_LINE:
		conf_data =
		    CFG_PCI_INTERRUPT_LINE(PCI_DEFAULT_PIN, CS5536_USB_INTR);
		अवरोध;
	हाल PCI_EHCI_LEGSMIEN_REG:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		conf_data = (hi & 0x003f0000) >> 16;
		अवरोध;
	हाल PCI_EHCI_LEGSMISTS_REG:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		conf_data = (hi & 0x3f000000) >> 24;
		अवरोध;
	हाल PCI_EHCI_FLADJ_REG:
		_rdmsr(USB_MSR_REG(USB_EHCI), &hi, &lo);
		conf_data = hi & 0x00003f00;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस conf_data;
पूर्ण
