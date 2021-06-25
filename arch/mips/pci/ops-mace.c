<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000, 2001 Keith M Wesolowski
 */
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/ip32/mace.h>

#अगर 0
# define DPRINTK(args...) prपूर्णांकk(args);
#अन्यथा
# define DPRINTK(args...)
#पूर्ण_अगर

/*
 * O2 has up to 5 PCI devices connected पूर्णांकo the MACE bridge.  The device
 * map looks like this:
 *
 * 0  aic7xxx 0
 * 1  aic7xxx 1
 * 2  expansion slot
 * 3  N/C
 * 4  N/C
 */

अटल अंतरभूत पूर्णांक mkaddr(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
	अचिन्हित पूर्णांक reg)
अणु
	वापस ((bus->number & 0xff) << 16) |
		((devfn & 0xff) << 8) |
		(reg & 0xfc);
पूर्ण


अटल पूर्णांक
mace_pci_पढ़ो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
		     पूर्णांक reg, पूर्णांक size, u32 *val)
अणु
	u32 control = mace->pci.control;

	/* disable master पातs पूर्णांकerrupts during config पढ़ो */
	mace->pci.control = control & ~MACEPCI_CONTROL_MAR_INT;
	mace->pci.config_addr = mkaddr(bus, devfn, reg);
	चयन (size) अणु
	हाल 1:
		*val = mace->pci.config_data.b[(reg & 3) ^ 3];
		अवरोध;
	हाल 2:
		*val = mace->pci.config_data.w[((reg >> 1) & 1) ^ 1];
		अवरोध;
	हाल 4:
		*val = mace->pci.config_data.l;
		अवरोध;
	पूर्ण
	/* ack possible master पात */
	mace->pci.error &= ~MACEPCI_ERROR_MASTER_ABORT;
	mace->pci.control = control;
	/*
	 * someone क्रमgot to set the ultra bit क्रम the onboard
	 * scsi chips; we fake it here
	 */
	अगर (bus->number == 0 && reg == 0x40 && size == 4 &&
	    (devfn == (1 << 3) || devfn == (2 << 3)))
		*val |= 0x1000;

	DPRINTK("read%d: reg=%08x,val=%02x\n", size * 8, reg, *val);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक
mace_pci_ग_लिखो_config(काष्ठा pci_bus *bus, अचिन्हित पूर्णांक devfn,
		      पूर्णांक reg, पूर्णांक size, u32 val)
अणु
	mace->pci.config_addr = mkaddr(bus, devfn, reg);
	चयन (size) अणु
	हाल 1:
		mace->pci.config_data.b[(reg & 3) ^ 3] = val;
		अवरोध;
	हाल 2:
		mace->pci.config_data.w[((reg >> 1) & 1) ^ 1] = val;
		अवरोध;
	हाल 4:
		mace->pci.config_data.l = val;
		अवरोध;
	पूर्ण

	DPRINTK("write%d: reg=%08x,val=%02x\n", size * 8, reg, val);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

काष्ठा pci_ops mace_pci_ops = अणु
	.पढ़ो = mace_pci_पढ़ो_config,
	.ग_लिखो = mace_pci_ग_लिखो_config,
पूर्ण;
