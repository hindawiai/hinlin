<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ops-vr41xx.c, PCI configuration routines क्रम the PCIU of NEC VR4100 series.
 *
 *  Copyright (C) 2001-2003 MontaVista Software Inc.
 *    Author: Yoichi Yuasa <source@mvista.com>
 *  Copyright (C) 2004-2005  Yoichi Yuasa <yuasa@linux-mips.org>
 */
/*
 * Changes:
 *  MontaVista Software Inc. <source@mvista.com>
 *  - New creation, NEC VR4122 and VR4131 are supported.
 */
#समावेश <linux/pci.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>

#घोषणा PCICONFDREG	(व्योम __iomem *)KSEG1ADDR(0x0f000c14)
#घोषणा PCICONFAREG	(व्योम __iomem *)KSEG1ADDR(0x0f000c18)

अटल अंतरभूत पूर्णांक set_pci_configuration_address(अचिन्हित अक्षर number,
						अचिन्हित पूर्णांक devfn, पूर्णांक where)
अणु
	अगर (number == 0) अणु
		/*
		 * Type 0 configuration
		 */
		अगर (PCI_SLOT(devfn) < 11 || where > 0xff)
			वापस -EINVAL;

		ग_लिखोl((1U << PCI_SLOT(devfn)) | (PCI_FUNC(devfn) << 8) |
		       (where & 0xfc), PCICONFAREG);
	पूर्ण अन्यथा अणु
		/*
		 * Type 1 configuration
		 */
		अगर (where > 0xff)
			वापस -EINVAL;

		ग_लिखोl(((uपूर्णांक32_t)number << 16) | ((devfn & 0xff) << 8) |
		       (where & 0xfc) | 1U, PCICONFAREG);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pci_config_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
			   पूर्णांक size, uपूर्णांक32_t *val)
अणु
	uपूर्णांक32_t data;

	*val = 0xffffffffU;
	अगर (set_pci_configuration_address(bus->number, devfn, where) < 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	data = पढ़ोl(PCICONFDREG);

	चयन (size) अणु
	हाल 1:
		*val = (data >> ((where & 3) << 3)) & 0xffU;
		अवरोध;
	हाल 2:
		*val = (data >> ((where & 2) << 3)) & 0xffffU;
		अवरोध;
	हाल 4:
		*val = data;
		अवरोध;
	शेष:
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक pci_config_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक where,
			    पूर्णांक size, uपूर्णांक32_t val)
अणु
	uपूर्णांक32_t data;
	पूर्णांक shअगरt;

	अगर (set_pci_configuration_address(bus->number, devfn, where) < 0)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	data = पढ़ोl(PCICONFDREG);

	चयन (size) अणु
	हाल 1:
		shअगरt = (where & 3) << 3;
		data &= ~(0xffU << shअगरt);
		data |= ((val & 0xffU) << shअगरt);
		अवरोध;
	हाल 2:
		shअगरt = (where & 2) << 3;
		data &= ~(0xffffU << shअगरt);
		data |= ((val & 0xffffU) << shअगरt);
		अवरोध;
	हाल 4:
		data = val;
		अवरोध;
	शेष:
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;
	पूर्ण

	ग_लिखोl(data, PCICONFDREG);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops vr41xx_pci_ops = अणु
	.पढ़ो	= pci_config_पढ़ो,
	.ग_लिखो	= pci_config_ग_लिखो,
पूर्ण;
