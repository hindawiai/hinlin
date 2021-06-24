<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * पढ़ो/ग_लिखो operation to the PCI config space of CS5536
 *
 * Copyright (C) 2007 Lemote, Inc.
 * Author : jlliu, liujl@lemote.com
 *
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 *
 *	the Virtual Support Module(VSM) क्रम virtulizing the PCI
 *	configure space are defined in cs5536_modulename.c respectively,
 *
 *	after this virtulizing, user can access the PCI configure space
 *	directly as a normal multi-function PCI device which follows
 *	the PCI-2.2 spec.
 */

#समावेश <linux/types.h>
#समावेश <cs5536/cs5536_pci.h>
#समावेश <cs5536/cs5536_vsm.h>

क्रमागत अणु
	CS5536_FUNC_START = -1,
	CS5536_ISA_FUNC,
	reserved_func,
	CS5536_IDE_FUNC,
	CS5536_ACC_FUNC,
	CS5536_OHCI_FUNC,
	CS5536_EHCI_FUNC,
	CS5536_FUNC_END,
पूर्ण;

अटल स्थिर cs5536_pci_vsm_ग_लिखो vsm_conf_ग_लिखो[] = अणु
	[CS5536_ISA_FUNC]	= pci_isa_ग_लिखो_reg,
	[reserved_func]		= शून्य,
	[CS5536_IDE_FUNC]	= pci_ide_ग_लिखो_reg,
	[CS5536_ACC_FUNC]	= pci_acc_ग_लिखो_reg,
	[CS5536_OHCI_FUNC]	= pci_ohci_ग_लिखो_reg,
	[CS5536_EHCI_FUNC]	= pci_ehci_ग_लिखो_reg,
पूर्ण;

अटल स्थिर cs5536_pci_vsm_पढ़ो vsm_conf_पढ़ो[] = अणु
	[CS5536_ISA_FUNC]	= pci_isa_पढ़ो_reg,
	[reserved_func]		= शून्य,
	[CS5536_IDE_FUNC]	= pci_ide_पढ़ो_reg,
	[CS5536_ACC_FUNC]	= pci_acc_पढ़ो_reg,
	[CS5536_OHCI_FUNC]	= pci_ohci_पढ़ो_reg,
	[CS5536_EHCI_FUNC]	= pci_ehci_पढ़ो_reg,
पूर्ण;

/*
 * ग_लिखो to PCI config space and transfer it to MSR ग_लिखो.
 */
व्योम cs5536_pci_conf_ग_लिखो4(पूर्णांक function, पूर्णांक reg, u32 value)
अणु
	अगर ((function <= CS5536_FUNC_START) || (function >= CS5536_FUNC_END))
		वापस;
	अगर ((reg < 0) || (reg > 0x100) || ((reg & 0x03) != 0))
		वापस;

	अगर (vsm_conf_ग_लिखो[function] != शून्य)
		vsm_conf_ग_लिखो[function](reg, value);
पूर्ण

/*
 * पढ़ो PCI config space and transfer it to MSR access.
 */
u32 cs5536_pci_conf_पढ़ो4(पूर्णांक function, पूर्णांक reg)
अणु
	u32 data = 0;

	अगर ((function <= CS5536_FUNC_START) || (function >= CS5536_FUNC_END))
		वापस 0;
	अगर ((reg < 0) || ((reg & 0x03) != 0))
		वापस 0;
	अगर (reg > 0x100)
		वापस 0xffffffff;

	अगर (vsm_conf_पढ़ो[function] != शून्य)
		data = vsm_conf_पढ़ो[function](reg);

	वापस data;
पूर्ण
