<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Root Complex Event Collector Support
 *
 * Authors:
 *  Sean V Kelley <sean.v.kelley@पूर्णांकel.com>
 *  Qiuxu Zhuo <qiuxu.zhuo@पूर्णांकel.com>
 *
 * Copyright (C) 2020 Intel Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>

#समावेश "../pci.h"

काष्ठा walk_rcec_data अणु
	काष्ठा pci_dev *rcec;
	पूर्णांक (*user_callback)(काष्ठा pci_dev *dev, व्योम *data);
	व्योम *user_data;
पूर्ण;

अटल bool rcec_assoc_rciep(काष्ठा pci_dev *rcec, काष्ठा pci_dev *rciep)
अणु
	अचिन्हित दीर्घ biपंचांगap = rcec->rcec_ea->biपंचांगap;
	अचिन्हित पूर्णांक devn;

	/* An RCiEP found on a dअगरferent bus in range */
	अगर (rcec->bus->number != rciep->bus->number)
		वापस true;

	/* Same bus, so check biपंचांगap */
	क्रम_each_set_bit(devn, &biपंचांगap, 32)
		अगर (devn == PCI_SLOT(rciep->devfn))
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक link_rcec_helper(काष्ठा pci_dev *dev, व्योम *data)
अणु
	काष्ठा walk_rcec_data *rcec_data = data;
	काष्ठा pci_dev *rcec = rcec_data->rcec;

	अगर ((pci_pcie_type(dev) == PCI_EXP_TYPE_RC_END) &&
	    rcec_assoc_rciep(rcec, dev)) अणु
		dev->rcec = rcec;
		pci_dbg(dev, "PME & error events signaled via %s\n",
			pci_name(rcec));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक walk_rcec_helper(काष्ठा pci_dev *dev, व्योम *data)
अणु
	काष्ठा walk_rcec_data *rcec_data = data;
	काष्ठा pci_dev *rcec = rcec_data->rcec;

	अगर ((pci_pcie_type(dev) == PCI_EXP_TYPE_RC_END) &&
	    rcec_assoc_rciep(rcec, dev))
		rcec_data->user_callback(dev, rcec_data->user_data);

	वापस 0;
पूर्ण

अटल व्योम walk_rcec(पूर्णांक (*cb)(काष्ठा pci_dev *dev, व्योम *data),
		      व्योम *userdata)
अणु
	काष्ठा walk_rcec_data *rcec_data = userdata;
	काष्ठा pci_dev *rcec = rcec_data->rcec;
	u8 nextbusn, lastbusn;
	काष्ठा pci_bus *bus;
	अचिन्हित पूर्णांक bnr;

	अगर (!rcec->rcec_ea)
		वापस;

	/* Walk own bus क्रम biपंचांगap based association */
	pci_walk_bus(rcec->bus, cb, rcec_data);

	nextbusn = rcec->rcec_ea->nextbusn;
	lastbusn = rcec->rcec_ea->lastbusn;

	/* All RCiEP devices are on the same bus as the RCEC */
	अगर (nextbusn == 0xff && lastbusn == 0x00)
		वापस;

	क्रम (bnr = nextbusn; bnr <= lastbusn; bnr++) अणु
		/* No association indicated (PCIe 5.0-1, 7.9.10.3) */
		अगर (bnr == rcec->bus->number)
			जारी;

		bus = pci_find_bus(pci_करोमुख्य_nr(rcec->bus), bnr);
		अगर (!bus)
			जारी;

		/* Find RCiEP devices on the given bus ranges */
		pci_walk_bus(bus, cb, rcec_data);
	पूर्ण
पूर्ण

/**
 * pcie_link_rcec - Link RCiEP devices associated with RCEC.
 * @rcec: RCEC whose RCiEP devices should be linked.
 *
 * Link the given RCEC to each RCiEP device found.
 */
व्योम pcie_link_rcec(काष्ठा pci_dev *rcec)
अणु
	काष्ठा walk_rcec_data rcec_data;

	अगर (!rcec->rcec_ea)
		वापस;

	rcec_data.rcec = rcec;
	rcec_data.user_callback = शून्य;
	rcec_data.user_data = शून्य;

	walk_rcec(link_rcec_helper, &rcec_data);
पूर्ण

/**
 * pcie_walk_rcec - Walk RCiEP devices associating with RCEC and call callback.
 * @rcec:	RCEC whose RCiEP devices should be walked
 * @cb:		Callback to be called क्रम each RCiEP device found
 * @userdata:	Arbitrary poपूर्णांकer to be passed to callback
 *
 * Walk the given RCEC. Call the callback on each RCiEP found.
 *
 * If @cb वापसs anything other than 0, अवरोध out.
 */
व्योम pcie_walk_rcec(काष्ठा pci_dev *rcec, पूर्णांक (*cb)(काष्ठा pci_dev *, व्योम *),
		    व्योम *userdata)
अणु
	काष्ठा walk_rcec_data rcec_data;

	अगर (!rcec->rcec_ea)
		वापस;

	rcec_data.rcec = rcec;
	rcec_data.user_callback = cb;
	rcec_data.user_data = userdata;

	walk_rcec(walk_rcec_helper, &rcec_data);
पूर्ण

व्योम pci_rcec_init(काष्ठा pci_dev *dev)
अणु
	काष्ठा rcec_ea *rcec_ea;
	u32 rcec, hdr, busn;
	u8 ver;

	/* Only क्रम Root Complex Event Collectors */
	अगर (pci_pcie_type(dev) != PCI_EXP_TYPE_RC_EC)
		वापस;

	rcec = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_RCEC);
	अगर (!rcec)
		वापस;

	rcec_ea = kzalloc(माप(*rcec_ea), GFP_KERNEL);
	अगर (!rcec_ea)
		वापस;

	pci_पढ़ो_config_dword(dev, rcec + PCI_RCEC_RCIEP_BITMAP,
			      &rcec_ea->biपंचांगap);

	/* Check whether RCEC BUSN रेजिस्टर is present */
	pci_पढ़ो_config_dword(dev, rcec, &hdr);
	ver = PCI_EXT_CAP_VER(hdr);
	अगर (ver >= PCI_RCEC_BUSN_REG_VER) अणु
		pci_पढ़ो_config_dword(dev, rcec + PCI_RCEC_BUSN, &busn);
		rcec_ea->nextbusn = PCI_RCEC_BUSN_NEXT(busn);
		rcec_ea->lastbusn = PCI_RCEC_BUSN_LAST(busn);
	पूर्ण अन्यथा अणु
		/* Aव्योम later ver check by setting nextbusn */
		rcec_ea->nextbusn = 0xff;
		rcec_ea->lastbusn = 0x00;
	पूर्ण

	dev->rcec_ea = rcec_ea;
पूर्ण

व्योम pci_rcec_निकास(काष्ठा pci_dev *dev)
अणु
	kमुक्त(dev->rcec_ea);
	dev->rcec_ea = शून्य;
पूर्ण
