<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * the IDE Virtual Support Module of AMD CS5536
 *
 * Copyright (C) 2007 Lemote, Inc.
 * Author : jlliu, liujl@lemote.com
 *
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 */

#समावेश <cs5536/cs5536.h>
#समावेश <cs5536/cs5536_pci.h>

व्योम pci_ide_ग_लिखो_reg(पूर्णांक reg, u32 value)
अणु
	u32 hi = 0, lo = value;

	चयन (reg) अणु
	हाल PCI_COMMAND:
		_rdmsr(GLIU_MSR_REG(GLIU_PAE), &hi, &lo);
		अगर (value & PCI_COMMAND_MASTER)
			lo |= (0x03 << 4);
		अन्यथा
			lo &= ~(0x03 << 4);
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
	हाल PCI_CACHE_LINE_SIZE:
		value &= 0x0000ff00;
		_rdmsr(SB_MSR_REG(SB_CTRL), &hi, &lo);
		hi &= 0xffffff00;
		hi |= (value >> 8);
		_wrmsr(SB_MSR_REG(SB_CTRL), hi, lo);
		अवरोध;
	हाल PCI_BAR4_REG:
		अगर (value == PCI_BAR_RANGE_MASK) अणु
			_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
			lo |= SOFT_BAR_IDE_FLAG;
			_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
		पूर्ण अन्यथा अगर (value & 0x01) अणु
			_rdmsr(IDE_MSR_REG(IDE_IO_BAR), &hi, &lo);
			lo = (value & 0xfffffff0) | 0x1;
			_wrmsr(IDE_MSR_REG(IDE_IO_BAR), hi, lo);

			value &= 0xfffffffc;
			hi = 0x60000000 | ((value & 0x000ff000) >> 12);
			lo = 0x000ffff0 | ((value & 0x00000fff) << 20);
			_wrmsr(GLIU_MSR_REG(GLIU_IOD_BM2), hi, lo);
		पूर्ण
		अवरोध;
	हाल PCI_IDE_CFG_REG:
		अगर (value == CS5536_IDE_FLASH_SIGNATURE) अणु
			_rdmsr(DIVIL_MSR_REG(DIVIL_BALL_OPTS), &hi, &lo);
			lo |= 0x01;
			_wrmsr(DIVIL_MSR_REG(DIVIL_BALL_OPTS), hi, lo);
		पूर्ण अन्यथा अणु
			_rdmsr(IDE_MSR_REG(IDE_CFG), &hi, &lo);
			lo = value;
			_wrmsr(IDE_MSR_REG(IDE_CFG), hi, lo);
		पूर्ण
		अवरोध;
	हाल PCI_IDE_DTC_REG:
		_rdmsr(IDE_MSR_REG(IDE_DTC), &hi, &lo);
		lo = value;
		_wrmsr(IDE_MSR_REG(IDE_DTC), hi, lo);
		अवरोध;
	हाल PCI_IDE_CAST_REG:
		_rdmsr(IDE_MSR_REG(IDE_CAST), &hi, &lo);
		lo = value;
		_wrmsr(IDE_MSR_REG(IDE_CAST), hi, lo);
		अवरोध;
	हाल PCI_IDE_ETC_REG:
		_rdmsr(IDE_MSR_REG(IDE_ETC), &hi, &lo);
		lo = value;
		_wrmsr(IDE_MSR_REG(IDE_ETC), hi, lo);
		अवरोध;
	हाल PCI_IDE_PM_REG:
		_rdmsr(IDE_MSR_REG(IDE_INTERNAL_PM), &hi, &lo);
		lo = value;
		_wrmsr(IDE_MSR_REG(IDE_INTERNAL_PM), hi, lo);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

u32 pci_ide_पढ़ो_reg(पूर्णांक reg)
अणु
	u32 conf_data = 0;
	u32 hi, lo;

	चयन (reg) अणु
	हाल PCI_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_IDE_DEVICE_ID, CS5536_VENDOR_ID);
		अवरोध;
	हाल PCI_COMMAND:
		_rdmsr(IDE_MSR_REG(IDE_IO_BAR), &hi, &lo);
		अगर (lo & 0xfffffff0)
			conf_data |= PCI_COMMAND_IO;
		_rdmsr(GLIU_MSR_REG(GLIU_PAE), &hi, &lo);
		अगर ((lo & 0x30) == 0x30)
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
		_rdmsr(IDE_MSR_REG(IDE_CAP), &hi, &lo);
		conf_data = lo & 0x000000ff;
		conf_data |= (CS5536_IDE_CLASS_CODE << 8);
		अवरोध;
	हाल PCI_CACHE_LINE_SIZE:
		_rdmsr(SB_MSR_REG(SB_CTRL), &hi, &lo);
		hi &= 0x000000f8;
		conf_data = CFG_PCI_CACHE_LINE_SIZE(PCI_NORMAL_HEADER_TYPE, hi);
		अवरोध;
	हाल PCI_BAR4_REG:
		_rdmsr(GLCP_MSR_REG(GLCP_SOFT_COM), &hi, &lo);
		अगर (lo & SOFT_BAR_IDE_FLAG) अणु
			conf_data = CS5536_IDE_RANGE |
			    PCI_BASE_ADDRESS_SPACE_IO;
			lo &= ~SOFT_BAR_IDE_FLAG;
			_wrmsr(GLCP_MSR_REG(GLCP_SOFT_COM), hi, lo);
		पूर्ण अन्यथा अणु
			_rdmsr(IDE_MSR_REG(IDE_IO_BAR), &hi, &lo);
			conf_data = lo & 0xfffffff0;
			conf_data |= 0x01;
			conf_data &= ~0x02;
		पूर्ण
		अवरोध;
	हाल PCI_CARDBUS_CIS:
		conf_data = PCI_CARDBUS_CIS_POINTER;
		अवरोध;
	हाल PCI_SUBSYSTEM_VENDOR_ID:
		conf_data =
		    CFG_PCI_VENDOR_ID(CS5536_IDE_SUB_ID, CS5536_SUB_VENDOR_ID);
		अवरोध;
	हाल PCI_ROM_ADDRESS:
		conf_data = PCI_EXPANSION_ROM_BAR;
		अवरोध;
	हाल PCI_CAPABILITY_LIST:
		conf_data = PCI_CAPLIST_POINTER;
		अवरोध;
	हाल PCI_INTERRUPT_LINE:
		conf_data =
		    CFG_PCI_INTERRUPT_LINE(PCI_DEFAULT_PIN, CS5536_IDE_INTR);
		अवरोध;
	हाल PCI_IDE_CFG_REG:
		_rdmsr(IDE_MSR_REG(IDE_CFG), &hi, &lo);
		conf_data = lo;
		अवरोध;
	हाल PCI_IDE_DTC_REG:
		_rdmsr(IDE_MSR_REG(IDE_DTC), &hi, &lo);
		conf_data = lo;
		अवरोध;
	हाल PCI_IDE_CAST_REG:
		_rdmsr(IDE_MSR_REG(IDE_CAST), &hi, &lo);
		conf_data = lo;
		अवरोध;
	हाल PCI_IDE_ETC_REG:
		_rdmsr(IDE_MSR_REG(IDE_ETC), &hi, &lo);
		conf_data = lo;
		अवरोध;
	हाल PCI_IDE_PM_REG:
		_rdmsr(IDE_MSR_REG(IDE_INTERNAL_PM), &hi, &lo);
		conf_data = lo;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस conf_data;
पूर्ण
