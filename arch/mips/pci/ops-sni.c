<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SNI specअगरic PCI support क्रम RM200/RM300.
 *
 * Copyright (C) 1997 - 2000, 2003 Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/sni.h>

/*
 * It seems that on the RM200 only lower 3 bits of the 5 bit PCI device
 * address are decoded.	 We thereक्रमe manually have to reject attempts at
 * पढ़ोing outside this range.	Being on the paranoid side we only करो this
 * test क्रम bus 0 and hope क्रमwarding and decoding work properly क्रम any
 * subordinated busses.
 *
 * ASIC PCI only supports type 1 config cycles.
 */
अटल पूर्णांक set_config_address(अचिन्हित पूर्णांक busno, अचिन्हित पूर्णांक devfn, पूर्णांक reg)
अणु
	अगर ((devfn > 255) || (reg > 255))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	अगर (busno == 0 && devfn >= PCI_DEVFN(8, 0))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	*(अस्थिर u32 *)PCIMT_CONFIG_ADDRESS =
		 ((busno    & 0xff) << 16) |
		 ((devfn    & 0xff) <<	8) |
		  (reg	    & 0xfc);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक pcimt_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक reg,
		      पूर्णांक size, u32 * val)
अणु
	पूर्णांक res;

	अगर ((res = set_config_address(bus->number, devfn, reg)))
		वापस res;

	चयन (size) अणु
	हाल 1:
		*val = inb(PCIMT_CONFIG_DATA + (reg & 3));
		अवरोध;
	हाल 2:
		*val = inw(PCIMT_CONFIG_DATA + (reg & 2));
		अवरोध;
	हाल 4:
		*val = inl(PCIMT_CONFIG_DATA);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcimt_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक reg,
		       पूर्णांक size, u32 val)
अणु
	पूर्णांक res;

	अगर ((res = set_config_address(bus->number, devfn, reg)))
		वापस res;

	चयन (size) अणु
	हाल 1:
		outb(val, PCIMT_CONFIG_DATA + (reg & 3));
		अवरोध;
	हाल 2:
		outw(val, PCIMT_CONFIG_DATA + (reg & 2));
		अवरोध;
	हाल 4:
		outl(val, PCIMT_CONFIG_DATA);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा pci_ops sni_pcimt_ops = अणु
	.पढ़ो = pcimt_पढ़ो,
	.ग_लिखो = pcimt_ग_लिखो,
पूर्ण;

अटल पूर्णांक pcit_set_config_address(अचिन्हित पूर्णांक busno, अचिन्हित पूर्णांक devfn, पूर्णांक reg)
अणु
	अगर ((devfn > 255) || (reg > 255) || (busno > 255))
		वापस PCIBIOS_BAD_REGISTER_NUMBER;

	outl((1 << 31) | ((busno & 0xff) << 16) | ((devfn & 0xff) << 8) | (reg & 0xfc), 0xcf8);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक pcit_पढ़ो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक reg,
		      पूर्णांक size, u32 * val)
अणु
	पूर्णांक res;

	/*
	 * on bus 0 we need to check, whether there is a device answering
	 * क्रम the devfn by करोing a config ग_लिखो and checking the result. If
	 * we करोn't करो it, we will get a data bus error
	 */
	अगर (bus->number == 0) अणु
		pcit_set_config_address(0, 0, 0x68);
		outl(inl(0xcfc) | 0xc0000000, 0xcfc);
		अगर ((res = pcit_set_config_address(0, devfn, 0)))
			वापस res;
		outl(0xffffffff, 0xcfc);
		pcit_set_config_address(0, 0, 0x68);
		अगर (inl(0xcfc) & 0x100000)
			वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण
	अगर ((res = pcit_set_config_address(bus->number, devfn, reg)))
		वापस res;

	चयन (size) अणु
	हाल 1:
		*val = inb(PCIMT_CONFIG_DATA + (reg & 3));
		अवरोध;
	हाल 2:
		*val = inw(PCIMT_CONFIG_DATA + (reg & 2));
		अवरोध;
	हाल 4:
		*val = inl(PCIMT_CONFIG_DATA);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcit_ग_लिखो(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn, पूर्णांक reg,
		       पूर्णांक size, u32 val)
अणु
	पूर्णांक res;

	अगर ((res = pcit_set_config_address(bus->number, devfn, reg)))
		वापस res;

	चयन (size) अणु
	हाल 1:
		outb(val, PCIMT_CONFIG_DATA + (reg & 3));
		अवरोध;
	हाल 2:
		outw(val, PCIMT_CONFIG_DATA + (reg & 2));
		अवरोध;
	हाल 4:
		outl(val, PCIMT_CONFIG_DATA);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण


काष्ठा pci_ops sni_pcit_ops = अणु
	.पढ़ो = pcit_पढ़ो,
	.ग_लिखो = pcit_ग_लिखो,
पूर्ण;
