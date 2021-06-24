<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003 Christoph Hellwig (hch@lst.de)
 * Copyright (C) 1999, 2000, 04 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/types.h>
#समावेश <यंत्र/sn/klconfig.h>
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/sn/ioc3.h>
#समावेश <यंत्र/pci/bridge.h>

#अगर_घोषित CONFIG_NUMA
पूर्णांक pcibus_to_node(काष्ठा pci_bus *bus)
अणु
	काष्ठा bridge_controller *bc = BRIDGE_CONTROLLER(bus);

	वापस bc->nasid;
पूर्ण
EXPORT_SYMBOL(pcibus_to_node);
#पूर्ण_अगर /* CONFIG_NUMA */

अटल व्योम ip29_fixup_phy(काष्ठा pci_dev *dev)
अणु
	पूर्णांक nasid = pcibus_to_node(dev->bus);
	u32 sid;

	अगर (nasid != 1)
		वापस; /* only needed on second module */

	/* enable ethernet PHY on IP29 प्रणालीboard */
	pci_पढ़ो_config_dword(dev, PCI_SUBSYSTEM_VENDOR_ID, &sid);
	अगर (sid == (PCI_VENDOR_ID_SGI | (IOC3_SUBSYS_IP29_SYSBOARD) << 16))
		REMOTE_HUB_S(nasid, MD_LED0, 0x09);
पूर्ण

DECLARE_PCI_FIXUP_FINAL(PCI_VENDOR_ID_SGI, PCI_DEVICE_ID_SGI_IOC3,
			ip29_fixup_phy);
