<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support PCI/PCIe on PowerNV platक्रमms
 *
 * Copyright 2011 Benjamin Herrenschmidt, IBM Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/msi.h>
#समावेश <linux/iommu.h>
#समावेश <linux/sched/mm.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/msi_biपंचांगap.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/pnv-pci.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/tce.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/eeh_event.h>
#समावेश <यंत्र/eeh.h>

#समावेश "powernv.h"
#समावेश "pci.h"

अटल DEFINE_MUTEX(tunnel_mutex);

पूर्णांक pnv_pci_get_slot_id(काष्ठा device_node *np, uपूर्णांक64_t *id)
अणु
	काष्ठा device_node *node = np;
	u32 bdfn;
	u64 phbid;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "reg", &bdfn);
	अगर (ret)
		वापस -ENXIO;

	bdfn = ((bdfn & 0x00ffff00) >> 8);
	क्रम (node = np; node; node = of_get_parent(node)) अणु
		अगर (!PCI_DN(node)) अणु
			of_node_put(node);
			अवरोध;
		पूर्ण

		अगर (!of_device_is_compatible(node, "ibm,ioda2-phb") &&
		    !of_device_is_compatible(node, "ibm,ioda3-phb") &&
		    !of_device_is_compatible(node, "ibm,ioda2-npu2-opencapi-phb")) अणु
			of_node_put(node);
			जारी;
		पूर्ण

		ret = of_property_पढ़ो_u64(node, "ibm,opal-phbid", &phbid);
		अगर (ret) अणु
			of_node_put(node);
			वापस -ENXIO;
		पूर्ण

		अगर (of_device_is_compatible(node, "ibm,ioda2-npu2-opencapi-phb"))
			*id = PCI_PHB_SLOT_ID(phbid);
		अन्यथा
			*id = PCI_SLOT_ID(phbid, bdfn);
		वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_pci_get_slot_id);

पूर्णांक pnv_pci_get_device_tree(uपूर्णांक32_t phandle, व्योम *buf, uपूर्णांक64_t len)
अणु
	पूर्णांक64_t rc;

	अगर (!opal_check_token(OPAL_GET_DEVICE_TREE))
		वापस -ENXIO;

	rc = opal_get_device_tree(phandle, (uपूर्णांक64_t)buf, len);
	अगर (rc < OPAL_SUCCESS)
		वापस -EIO;

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_pci_get_device_tree);

पूर्णांक pnv_pci_get_presence_state(uपूर्णांक64_t id, uपूर्णांक8_t *state)
अणु
	पूर्णांक64_t rc;

	अगर (!opal_check_token(OPAL_PCI_GET_PRESENCE_STATE))
		वापस -ENXIO;

	rc = opal_pci_get_presence_state(id, (uपूर्णांक64_t)state);
	अगर (rc != OPAL_SUCCESS)
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_pci_get_presence_state);

पूर्णांक pnv_pci_get_घातer_state(uपूर्णांक64_t id, uपूर्णांक8_t *state)
अणु
	पूर्णांक64_t rc;

	अगर (!opal_check_token(OPAL_PCI_GET_POWER_STATE))
		वापस -ENXIO;

	rc = opal_pci_get_घातer_state(id, (uपूर्णांक64_t)state);
	अगर (rc != OPAL_SUCCESS)
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_pci_get_घातer_state);

पूर्णांक pnv_pci_set_घातer_state(uपूर्णांक64_t id, uपूर्णांक8_t state, काष्ठा opal_msg *msg)
अणु
	काष्ठा opal_msg m;
	पूर्णांक token, ret;
	पूर्णांक64_t rc;

	अगर (!opal_check_token(OPAL_PCI_SET_POWER_STATE))
		वापस -ENXIO;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (unlikely(token < 0))
		वापस token;

	rc = opal_pci_set_घातer_state(token, id, (uपूर्णांक64_t)&state);
	अगर (rc == OPAL_SUCCESS) अणु
		ret = 0;
		जाओ निकास;
	पूर्ण अन्यथा अगर (rc != OPAL_ASYNC_COMPLETION) अणु
		ret = -EIO;
		जाओ निकास;
	पूर्ण

	ret = opal_async_रुको_response(token, &m);
	अगर (ret < 0)
		जाओ निकास;

	अगर (msg) अणु
		ret = 1;
		स_नकल(msg, &m, माप(m));
	पूर्ण

निकास:
	opal_async_release_token(token);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_pci_set_घातer_state);

पूर्णांक pnv_setup_msi_irqs(काष्ठा pci_dev *pdev, पूर्णांक nvec, पूर्णांक type)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	काष्ठा msi_desc *entry;
	काष्ठा msi_msg msg;
	पूर्णांक hwirq;
	अचिन्हित पूर्णांक virq;
	पूर्णांक rc;

	अगर (WARN_ON(!phb) || !phb->msi_bmp.biपंचांगap)
		वापस -ENODEV;

	अगर (pdev->no_64bit_msi && !phb->msi32_support)
		वापस -ENODEV;

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		अगर (!entry->msi_attrib.is_64 && !phb->msi32_support) अणु
			pr_warn("%s: Supports only 64-bit MSIs\n",
				pci_name(pdev));
			वापस -ENXIO;
		पूर्ण
		hwirq = msi_biपंचांगap_alloc_hwirqs(&phb->msi_bmp, 1);
		अगर (hwirq < 0) अणु
			pr_warn("%s: Failed to find a free MSI\n",
				pci_name(pdev));
			वापस -ENOSPC;
		पूर्ण
		virq = irq_create_mapping(शून्य, phb->msi_base + hwirq);
		अगर (!virq) अणु
			pr_warn("%s: Failed to map MSI to linux irq\n",
				pci_name(pdev));
			msi_biपंचांगap_मुक्त_hwirqs(&phb->msi_bmp, hwirq, 1);
			वापस -ENOMEM;
		पूर्ण
		rc = phb->msi_setup(phb, pdev, phb->msi_base + hwirq,
				    virq, entry->msi_attrib.is_64, &msg);
		अगर (rc) अणु
			pr_warn("%s: Failed to setup MSI\n", pci_name(pdev));
			irq_dispose_mapping(virq);
			msi_biपंचांगap_मुक्त_hwirqs(&phb->msi_bmp, hwirq, 1);
			वापस rc;
		पूर्ण
		irq_set_msi_desc(virq, entry);
		pci_ग_लिखो_msi_msg(virq, &msg);
	पूर्ण
	वापस 0;
पूर्ण

व्योम pnv_tearकरोwn_msi_irqs(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	काष्ठा msi_desc *entry;
	irq_hw_number_t hwirq;

	अगर (WARN_ON(!phb))
		वापस;

	क्रम_each_pci_msi_entry(entry, pdev) अणु
		अगर (!entry->irq)
			जारी;
		hwirq = virq_to_hw(entry->irq);
		irq_set_msi_desc(entry->irq, शून्य);
		irq_dispose_mapping(entry->irq);
		msi_biपंचांगap_मुक्त_hwirqs(&phb->msi_bmp, hwirq - phb->msi_base, 1);
	पूर्ण
पूर्ण

/* Nicely prपूर्णांक the contents of the PE State Tables (PEST). */
अटल व्योम pnv_pci_dump_pest(__be64 pestA[], __be64 pestB[], पूर्णांक pest_size)
अणु
	__be64 prevA = अच_दीर्घ_उच्च, prevB = अच_दीर्घ_उच्च;
	bool dup = false;
	पूर्णांक i;

	क्रम (i = 0; i < pest_size; i++) अणु
		__be64 peA = be64_to_cpu(pestA[i]);
		__be64 peB = be64_to_cpu(pestB[i]);

		अगर (peA != prevA || peB != prevB) अणु
			अगर (dup) अणु
				pr_info("PE[..%03x] A/B: as above\n", i-1);
				dup = false;
			पूर्ण
			prevA = peA;
			prevB = peB;
			अगर (peA & PNV_IODA_STOPPED_STATE ||
			    peB & PNV_IODA_STOPPED_STATE)
				pr_info("PE[%03x] A/B: %016llx %016llx\n",
					i, peA, peB);
		पूर्ण अन्यथा अगर (!dup && (peA & PNV_IODA_STOPPED_STATE ||
				    peB & PNV_IODA_STOPPED_STATE)) अणु
			dup = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pnv_pci_dump_p7ioc_diag_data(काष्ठा pci_controller *hose,
					 काष्ठा OpalIoPhbErrorCommon *common)
अणु
	काष्ठा OpalIoP7IOCPhbErrorData *data;

	data = (काष्ठा OpalIoP7IOCPhbErrorData *)common;
	pr_info("P7IOC PHB#%x Diag-data (Version: %d)\n",
		hose->global_number, be32_to_cpu(common->version));

	अगर (data->brdgCtl)
		pr_info("brdgCtl:     %08x\n",
			be32_to_cpu(data->brdgCtl));
	अगर (data->portStatusReg || data->rootCmplxStatus ||
	    data->busAgentStatus)
		pr_info("UtlSts:      %08x %08x %08x\n",
			be32_to_cpu(data->portStatusReg),
			be32_to_cpu(data->rootCmplxStatus),
			be32_to_cpu(data->busAgentStatus));
	अगर (data->deviceStatus || data->slotStatus   ||
	    data->linkStatus   || data->devCmdStatus ||
	    data->devSecStatus)
		pr_info("RootSts:     %08x %08x %08x %08x %08x\n",
			be32_to_cpu(data->deviceStatus),
			be32_to_cpu(data->slotStatus),
			be32_to_cpu(data->linkStatus),
			be32_to_cpu(data->devCmdStatus),
			be32_to_cpu(data->devSecStatus));
	अगर (data->rootErrorStatus   || data->uncorrErrorStatus ||
	    data->corrErrorStatus)
		pr_info("RootErrSts:  %08x %08x %08x\n",
			be32_to_cpu(data->rootErrorStatus),
			be32_to_cpu(data->uncorrErrorStatus),
			be32_to_cpu(data->corrErrorStatus));
	अगर (data->tlpHdr1 || data->tlpHdr2 ||
	    data->tlpHdr3 || data->tlpHdr4)
		pr_info("RootErrLog:  %08x %08x %08x %08x\n",
			be32_to_cpu(data->tlpHdr1),
			be32_to_cpu(data->tlpHdr2),
			be32_to_cpu(data->tlpHdr3),
			be32_to_cpu(data->tlpHdr4));
	अगर (data->sourceId || data->errorClass ||
	    data->correlator)
		pr_info("RootErrLog1: %08x %016llx %016llx\n",
			be32_to_cpu(data->sourceId),
			be64_to_cpu(data->errorClass),
			be64_to_cpu(data->correlator));
	अगर (data->p7iocPlssr || data->p7iocCsr)
		pr_info("PhbSts:      %016llx %016llx\n",
			be64_to_cpu(data->p7iocPlssr),
			be64_to_cpu(data->p7iocCsr));
	अगर (data->lemFir)
		pr_info("Lem:         %016llx %016llx %016llx\n",
			be64_to_cpu(data->lemFir),
			be64_to_cpu(data->lemErrorMask),
			be64_to_cpu(data->lemWOF));
	अगर (data->phbErrorStatus)
		pr_info("PhbErr:      %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->phbErrorStatus),
			be64_to_cpu(data->phbFirstErrorStatus),
			be64_to_cpu(data->phbErrorLog0),
			be64_to_cpu(data->phbErrorLog1));
	अगर (data->mmioErrorStatus)
		pr_info("OutErr:      %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->mmioErrorStatus),
			be64_to_cpu(data->mmioFirstErrorStatus),
			be64_to_cpu(data->mmioErrorLog0),
			be64_to_cpu(data->mmioErrorLog1));
	अगर (data->dma0ErrorStatus)
		pr_info("InAErr:      %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->dma0ErrorStatus),
			be64_to_cpu(data->dma0FirstErrorStatus),
			be64_to_cpu(data->dma0ErrorLog0),
			be64_to_cpu(data->dma0ErrorLog1));
	अगर (data->dma1ErrorStatus)
		pr_info("InBErr:      %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->dma1ErrorStatus),
			be64_to_cpu(data->dma1FirstErrorStatus),
			be64_to_cpu(data->dma1ErrorLog0),
			be64_to_cpu(data->dma1ErrorLog1));

	pnv_pci_dump_pest(data->pestA, data->pestB, OPAL_P7IOC_NUM_PEST_REGS);
पूर्ण

अटल व्योम pnv_pci_dump_phb3_diag_data(काष्ठा pci_controller *hose,
					काष्ठा OpalIoPhbErrorCommon *common)
अणु
	काष्ठा OpalIoPhb3ErrorData *data;

	data = (काष्ठा OpalIoPhb3ErrorData*)common;
	pr_info("PHB3 PHB#%x Diag-data (Version: %d)\n",
		hose->global_number, be32_to_cpu(common->version));
	अगर (data->brdgCtl)
		pr_info("brdgCtl:     %08x\n",
			be32_to_cpu(data->brdgCtl));
	अगर (data->portStatusReg || data->rootCmplxStatus ||
	    data->busAgentStatus)
		pr_info("UtlSts:      %08x %08x %08x\n",
			be32_to_cpu(data->portStatusReg),
			be32_to_cpu(data->rootCmplxStatus),
			be32_to_cpu(data->busAgentStatus));
	अगर (data->deviceStatus || data->slotStatus   ||
	    data->linkStatus   || data->devCmdStatus ||
	    data->devSecStatus)
		pr_info("RootSts:     %08x %08x %08x %08x %08x\n",
			be32_to_cpu(data->deviceStatus),
			be32_to_cpu(data->slotStatus),
			be32_to_cpu(data->linkStatus),
			be32_to_cpu(data->devCmdStatus),
			be32_to_cpu(data->devSecStatus));
	अगर (data->rootErrorStatus || data->uncorrErrorStatus ||
	    data->corrErrorStatus)
		pr_info("RootErrSts:  %08x %08x %08x\n",
			be32_to_cpu(data->rootErrorStatus),
			be32_to_cpu(data->uncorrErrorStatus),
			be32_to_cpu(data->corrErrorStatus));
	अगर (data->tlpHdr1 || data->tlpHdr2 ||
	    data->tlpHdr3 || data->tlpHdr4)
		pr_info("RootErrLog:  %08x %08x %08x %08x\n",
			be32_to_cpu(data->tlpHdr1),
			be32_to_cpu(data->tlpHdr2),
			be32_to_cpu(data->tlpHdr3),
			be32_to_cpu(data->tlpHdr4));
	अगर (data->sourceId || data->errorClass ||
	    data->correlator)
		pr_info("RootErrLog1: %08x %016llx %016llx\n",
			be32_to_cpu(data->sourceId),
			be64_to_cpu(data->errorClass),
			be64_to_cpu(data->correlator));
	अगर (data->nFir)
		pr_info("nFir:        %016llx %016llx %016llx\n",
			be64_to_cpu(data->nFir),
			be64_to_cpu(data->nFirMask),
			be64_to_cpu(data->nFirWOF));
	अगर (data->phbPlssr || data->phbCsr)
		pr_info("PhbSts:      %016llx %016llx\n",
			be64_to_cpu(data->phbPlssr),
			be64_to_cpu(data->phbCsr));
	अगर (data->lemFir)
		pr_info("Lem:         %016llx %016llx %016llx\n",
			be64_to_cpu(data->lemFir),
			be64_to_cpu(data->lemErrorMask),
			be64_to_cpu(data->lemWOF));
	अगर (data->phbErrorStatus)
		pr_info("PhbErr:      %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->phbErrorStatus),
			be64_to_cpu(data->phbFirstErrorStatus),
			be64_to_cpu(data->phbErrorLog0),
			be64_to_cpu(data->phbErrorLog1));
	अगर (data->mmioErrorStatus)
		pr_info("OutErr:      %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->mmioErrorStatus),
			be64_to_cpu(data->mmioFirstErrorStatus),
			be64_to_cpu(data->mmioErrorLog0),
			be64_to_cpu(data->mmioErrorLog1));
	अगर (data->dma0ErrorStatus)
		pr_info("InAErr:      %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->dma0ErrorStatus),
			be64_to_cpu(data->dma0FirstErrorStatus),
			be64_to_cpu(data->dma0ErrorLog0),
			be64_to_cpu(data->dma0ErrorLog1));
	अगर (data->dma1ErrorStatus)
		pr_info("InBErr:      %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->dma1ErrorStatus),
			be64_to_cpu(data->dma1FirstErrorStatus),
			be64_to_cpu(data->dma1ErrorLog0),
			be64_to_cpu(data->dma1ErrorLog1));

	pnv_pci_dump_pest(data->pestA, data->pestB, OPAL_PHB3_NUM_PEST_REGS);
पूर्ण

अटल व्योम pnv_pci_dump_phb4_diag_data(काष्ठा pci_controller *hose,
					काष्ठा OpalIoPhbErrorCommon *common)
अणु
	काष्ठा OpalIoPhb4ErrorData *data;

	data = (काष्ठा OpalIoPhb4ErrorData*)common;
	pr_info("PHB4 PHB#%d Diag-data (Version: %d)\n",
		hose->global_number, be32_to_cpu(common->version));
	अगर (data->brdgCtl)
		pr_info("brdgCtl:    %08x\n",
			be32_to_cpu(data->brdgCtl));
	अगर (data->deviceStatus || data->slotStatus   ||
	    data->linkStatus   || data->devCmdStatus ||
	    data->devSecStatus)
		pr_info("RootSts:    %08x %08x %08x %08x %08x\n",
			be32_to_cpu(data->deviceStatus),
			be32_to_cpu(data->slotStatus),
			be32_to_cpu(data->linkStatus),
			be32_to_cpu(data->devCmdStatus),
			be32_to_cpu(data->devSecStatus));
	अगर (data->rootErrorStatus || data->uncorrErrorStatus ||
	    data->corrErrorStatus)
		pr_info("RootErrSts: %08x %08x %08x\n",
			be32_to_cpu(data->rootErrorStatus),
			be32_to_cpu(data->uncorrErrorStatus),
			be32_to_cpu(data->corrErrorStatus));
	अगर (data->tlpHdr1 || data->tlpHdr2 ||
	    data->tlpHdr3 || data->tlpHdr4)
		pr_info("RootErrLog: %08x %08x %08x %08x\n",
			be32_to_cpu(data->tlpHdr1),
			be32_to_cpu(data->tlpHdr2),
			be32_to_cpu(data->tlpHdr3),
			be32_to_cpu(data->tlpHdr4));
	अगर (data->sourceId)
		pr_info("sourceId:   %08x\n", be32_to_cpu(data->sourceId));
	अगर (data->nFir)
		pr_info("nFir:       %016llx %016llx %016llx\n",
			be64_to_cpu(data->nFir),
			be64_to_cpu(data->nFirMask),
			be64_to_cpu(data->nFirWOF));
	अगर (data->phbPlssr || data->phbCsr)
		pr_info("PhbSts:     %016llx %016llx\n",
			be64_to_cpu(data->phbPlssr),
			be64_to_cpu(data->phbCsr));
	अगर (data->lemFir)
		pr_info("Lem:        %016llx %016llx %016llx\n",
			be64_to_cpu(data->lemFir),
			be64_to_cpu(data->lemErrorMask),
			be64_to_cpu(data->lemWOF));
	अगर (data->phbErrorStatus)
		pr_info("PhbErr:     %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->phbErrorStatus),
			be64_to_cpu(data->phbFirstErrorStatus),
			be64_to_cpu(data->phbErrorLog0),
			be64_to_cpu(data->phbErrorLog1));
	अगर (data->phbTxeErrorStatus)
		pr_info("PhbTxeErr:  %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->phbTxeErrorStatus),
			be64_to_cpu(data->phbTxeFirstErrorStatus),
			be64_to_cpu(data->phbTxeErrorLog0),
			be64_to_cpu(data->phbTxeErrorLog1));
	अगर (data->phbRxeArbErrorStatus)
		pr_info("RxeArbErr:  %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->phbRxeArbErrorStatus),
			be64_to_cpu(data->phbRxeArbFirstErrorStatus),
			be64_to_cpu(data->phbRxeArbErrorLog0),
			be64_to_cpu(data->phbRxeArbErrorLog1));
	अगर (data->phbRxeMrgErrorStatus)
		pr_info("RxeMrgErr:  %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->phbRxeMrgErrorStatus),
			be64_to_cpu(data->phbRxeMrgFirstErrorStatus),
			be64_to_cpu(data->phbRxeMrgErrorLog0),
			be64_to_cpu(data->phbRxeMrgErrorLog1));
	अगर (data->phbRxeTceErrorStatus)
		pr_info("RxeTceErr:  %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->phbRxeTceErrorStatus),
			be64_to_cpu(data->phbRxeTceFirstErrorStatus),
			be64_to_cpu(data->phbRxeTceErrorLog0),
			be64_to_cpu(data->phbRxeTceErrorLog1));

	अगर (data->phbPblErrorStatus)
		pr_info("PblErr:     %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->phbPblErrorStatus),
			be64_to_cpu(data->phbPblFirstErrorStatus),
			be64_to_cpu(data->phbPblErrorLog0),
			be64_to_cpu(data->phbPblErrorLog1));
	अगर (data->phbPcieDlpErrorStatus)
		pr_info("PcieDlp:    %016llx %016llx %016llx\n",
			be64_to_cpu(data->phbPcieDlpErrorLog1),
			be64_to_cpu(data->phbPcieDlpErrorLog2),
			be64_to_cpu(data->phbPcieDlpErrorStatus));
	अगर (data->phbRegbErrorStatus)
		pr_info("RegbErr:    %016llx %016llx %016llx %016llx\n",
			be64_to_cpu(data->phbRegbErrorStatus),
			be64_to_cpu(data->phbRegbFirstErrorStatus),
			be64_to_cpu(data->phbRegbErrorLog0),
			be64_to_cpu(data->phbRegbErrorLog1));


	pnv_pci_dump_pest(data->pestA, data->pestB, OPAL_PHB4_NUM_PEST_REGS);
पूर्ण

व्योम pnv_pci_dump_phb_diag_data(काष्ठा pci_controller *hose,
				अचिन्हित अक्षर *log_buff)
अणु
	काष्ठा OpalIoPhbErrorCommon *common;

	अगर (!hose || !log_buff)
		वापस;

	common = (काष्ठा OpalIoPhbErrorCommon *)log_buff;
	चयन (be32_to_cpu(common->ioType)) अणु
	हाल OPAL_PHB_ERROR_DATA_TYPE_P7IOC:
		pnv_pci_dump_p7ioc_diag_data(hose, common);
		अवरोध;
	हाल OPAL_PHB_ERROR_DATA_TYPE_PHB3:
		pnv_pci_dump_phb3_diag_data(hose, common);
		अवरोध;
	हाल OPAL_PHB_ERROR_DATA_TYPE_PHB4:
		pnv_pci_dump_phb4_diag_data(hose, common);
		अवरोध;
	शेष:
		pr_warn("%s: Unrecognized ioType %d\n",
			__func__, be32_to_cpu(common->ioType));
	पूर्ण
पूर्ण

अटल व्योम pnv_pci_handle_eeh_config(काष्ठा pnv_phb *phb, u32 pe_no)
अणु
	अचिन्हित दीर्घ flags, rc;
	पूर्णांक has_diag, ret = 0;

	spin_lock_irqsave(&phb->lock, flags);

	/* Fetch PHB diag-data */
	rc = opal_pci_get_phb_diag_data2(phb->opal_id, phb->diag_data,
					 phb->diag_data_size);
	has_diag = (rc == OPAL_SUCCESS);

	/* If PHB supports compound PE, to handle it */
	अगर (phb->unमुक्तze_pe) अणु
		ret = phb->unमुक्तze_pe(phb,
				       pe_no,
				       OPAL_EEH_ACTION_CLEAR_FREEZE_ALL);
	पूर्ण अन्यथा अणु
		rc = opal_pci_eeh_मुक्तze_clear(phb->opal_id,
					     pe_no,
					     OPAL_EEH_ACTION_CLEAR_FREEZE_ALL);
		अगर (rc) अणु
			pr_warn("%s: Failure %ld clearing frozen "
				"PHB#%x-PE#%x\n",
				__func__, rc, phb->hose->global_number,
				pe_no);
			ret = -EIO;
		पूर्ण
	पूर्ण

	/*
	 * For now, let's only display the diag buffer when we fail to clear
	 * the EEH status. We'll करो more sensible things later when we have
	 * proper EEH support. We need to make sure we करोn't pollute ourselves
	 * with the normal errors generated when probing empty slots
	 */
	अगर (has_diag && ret)
		pnv_pci_dump_phb_diag_data(phb->hose, phb->diag_data);

	spin_unlock_irqrestore(&phb->lock, flags);
पूर्ण

अटल व्योम pnv_pci_config_check_eeh(काष्ठा pci_dn *pdn)
अणु
	काष्ठा pnv_phb *phb = pdn->phb->निजी_data;
	u8	ख_स्थितिe = 0;
	__be16	pcierr = 0;
	अचिन्हित पूर्णांक pe_no;
	s64	rc;

	/*
	 * Get the PE#. During the PCI probe stage, we might not
	 * setup that yet. So all ER errors should be mapped to
	 * reserved PE.
	 */
	pe_no = pdn->pe_number;
	अगर (pe_no == IODA_INVALID_PE) अणु
		pe_no = phb->ioda.reserved_pe_idx;
	पूर्ण

	/*
	 * Fetch frozen state. If the PHB support compound PE,
	 * we need handle that हाल.
	 */
	अगर (phb->get_pe_state) अणु
		ख_स्थितिe = phb->get_pe_state(phb, pe_no);
	पूर्ण अन्यथा अणु
		rc = opal_pci_eeh_मुक्तze_status(phb->opal_id,
						pe_no,
						&ख_स्थितिe,
						&pcierr,
						शून्य);
		अगर (rc) अणु
			pr_warn("%s: Failure %lld getting PHB#%x-PE#%x state\n",
				__func__, rc, phb->hose->global_number, pe_no);
			वापस;
		पूर्ण
	पूर्ण

	pr_devel(" -> EEH check, bdfn=%04x PE#%x fstate=%x\n",
		 (pdn->busno << 8) | (pdn->devfn), pe_no, ख_स्थितिe);

	/* Clear the frozen state अगर applicable */
	अगर (ख_स्थितिe == OPAL_EEH_STOPPED_MMIO_FREEZE ||
	    ख_स्थितिe == OPAL_EEH_STOPPED_DMA_FREEZE  ||
	    ख_स्थितिe == OPAL_EEH_STOPPED_MMIO_DMA_FREEZE) अणु
		/*
		 * If PHB supports compound PE, मुक्तze it क्रम
		 * consistency.
		 */
		अगर (phb->मुक्तze_pe)
			phb->मुक्तze_pe(phb, pe_no);

		pnv_pci_handle_eeh_config(phb, pe_no);
	पूर्ण
पूर्ण

पूर्णांक pnv_pci_cfg_पढ़ो(काष्ठा pci_dn *pdn,
		     पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा pnv_phb *phb = pdn->phb->निजी_data;
	u32 bdfn = (pdn->busno << 8) | pdn->devfn;
	s64 rc;

	चयन (size) अणु
	हाल 1: अणु
		u8 v8;
		rc = opal_pci_config_पढ़ो_byte(phb->opal_id, bdfn, where, &v8);
		*val = (rc == OPAL_SUCCESS) ? v8 : 0xff;
		अवरोध;
	पूर्ण
	हाल 2: अणु
		__be16 v16;
		rc = opal_pci_config_पढ़ो_half_word(phb->opal_id, bdfn, where,
						   &v16);
		*val = (rc == OPAL_SUCCESS) ? be16_to_cpu(v16) : 0xffff;
		अवरोध;
	पूर्ण
	हाल 4: अणु
		__be32 v32;
		rc = opal_pci_config_पढ़ो_word(phb->opal_id, bdfn, where, &v32);
		*val = (rc == OPAL_SUCCESS) ? be32_to_cpu(v32) : 0xffffffff;
		अवरोध;
	पूर्ण
	शेष:
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;
	पूर्ण

	pr_devel("%s: bus: %x devfn: %x +%x/%x -> %08x\n",
		 __func__, pdn->busno, pdn->devfn, where, size, *val);
	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

पूर्णांक pnv_pci_cfg_ग_लिखो(काष्ठा pci_dn *pdn,
		      पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा pnv_phb *phb = pdn->phb->निजी_data;
	u32 bdfn = (pdn->busno << 8) | pdn->devfn;

	pr_devel("%s: bus: %x devfn: %x +%x/%x -> %08x\n",
		 __func__, pdn->busno, pdn->devfn, where, size, val);
	चयन (size) अणु
	हाल 1:
		opal_pci_config_ग_लिखो_byte(phb->opal_id, bdfn, where, val);
		अवरोध;
	हाल 2:
		opal_pci_config_ग_लिखो_half_word(phb->opal_id, bdfn, where, val);
		अवरोध;
	हाल 4:
		opal_pci_config_ग_लिखो_word(phb->opal_id, bdfn, where, val);
		अवरोध;
	शेष:
		वापस PCIBIOS_FUNC_NOT_SUPPORTED;
	पूर्ण

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

#अगर CONFIG_EEH
अटल bool pnv_pci_cfg_check(काष्ठा pci_dn *pdn)
अणु
	काष्ठा eeh_dev *edev = शून्य;
	काष्ठा pnv_phb *phb = pdn->phb->निजी_data;

	/* EEH not enabled ? */
	अगर (!(phb->flags & PNV_PHB_FLAG_EEH))
		वापस true;

	/* PE reset or device हटाओd ? */
	edev = pdn->edev;
	अगर (edev) अणु
		अगर (edev->pe &&
		    (edev->pe->state & EEH_PE_CFG_BLOCKED))
			वापस false;

		अगर (edev->mode & EEH_DEV_REMOVED)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत pnv_pci_cfg_check(काष्ठा pci_dn *pdn)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_EEH */

अटल पूर्णांक pnv_pci_पढ़ो_config(काष्ठा pci_bus *bus,
			       अचिन्हित पूर्णांक devfn,
			       पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा pci_dn *pdn;
	काष्ठा pnv_phb *phb;
	पूर्णांक ret;

	*val = 0xFFFFFFFF;
	pdn = pci_get_pdn_by_devfn(bus, devfn);
	अगर (!pdn)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (!pnv_pci_cfg_check(pdn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	ret = pnv_pci_cfg_पढ़ो(pdn, where, size, val);
	phb = pdn->phb->निजी_data;
	अगर (phb->flags & PNV_PHB_FLAG_EEH && pdn->edev) अणु
		अगर (*val == EEH_IO_ERROR_VALUE(size) &&
		    eeh_dev_check_failure(pdn->edev))
                        वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण अन्यथा अणु
		pnv_pci_config_check_eeh(pdn);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pnv_pci_ग_लिखो_config(काष्ठा pci_bus *bus,
				अचिन्हित पूर्णांक devfn,
				पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा pci_dn *pdn;
	काष्ठा pnv_phb *phb;
	पूर्णांक ret;

	pdn = pci_get_pdn_by_devfn(bus, devfn);
	अगर (!pdn)
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (!pnv_pci_cfg_check(pdn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	ret = pnv_pci_cfg_ग_लिखो(pdn, where, size, val);
	phb = pdn->phb->निजी_data;
	अगर (!(phb->flags & PNV_PHB_FLAG_EEH))
		pnv_pci_config_check_eeh(pdn);

	वापस ret;
पूर्ण

काष्ठा pci_ops pnv_pci_ops = अणु
	.पढ़ो  = pnv_pci_पढ़ो_config,
	.ग_लिखो = pnv_pci_ग_लिखो_config,
पूर्ण;

काष्ठा iommu_table *pnv_pci_table_alloc(पूर्णांक nid)
अणु
	काष्ठा iommu_table *tbl;

	tbl = kzalloc_node(माप(काष्ठा iommu_table), GFP_KERNEL, nid);
	अगर (!tbl)
		वापस शून्य;

	INIT_LIST_HEAD_RCU(&tbl->it_group_list);
	kref_init(&tbl->it_kref);

	वापस tbl;
पूर्ण

काष्ठा device_node *pnv_pci_get_phb_node(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_controller *hose = pci_bus_to_host(dev->bus);

	वापस of_node_get(hose->dn);
पूर्ण
EXPORT_SYMBOL(pnv_pci_get_phb_node);

पूर्णांक pnv_pci_set_tunnel_bar(काष्ठा pci_dev *dev, u64 addr, पूर्णांक enable)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(dev->bus);
	u64 tunnel_bar;
	__be64 val;
	पूर्णांक rc;

	अगर (!opal_check_token(OPAL_PCI_GET_PBCQ_TUNNEL_BAR))
		वापस -ENXIO;
	अगर (!opal_check_token(OPAL_PCI_SET_PBCQ_TUNNEL_BAR))
		वापस -ENXIO;

	mutex_lock(&tunnel_mutex);
	rc = opal_pci_get_pbcq_tunnel_bar(phb->opal_id, &val);
	अगर (rc != OPAL_SUCCESS) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण
	tunnel_bar = be64_to_cpu(val);
	अगर (enable) अणु
		/*
		* Only one device per PHB can use atomics.
		* Our policy is first-come, first-served.
		*/
		अगर (tunnel_bar) अणु
			अगर (tunnel_bar != addr)
				rc = -EBUSY;
			अन्यथा
				rc = 0;	/* Setting same address twice is ok */
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		* The device that owns atomics and wants to release
		* them must pass the same address with enable == 0.
		*/
		अगर (tunnel_bar != addr) अणु
			rc = -EPERM;
			जाओ out;
		पूर्ण
		addr = 0x0ULL;
	पूर्ण
	rc = opal_pci_set_pbcq_tunnel_bar(phb->opal_id, addr);
	rc = opal_error_code(rc);
out:
	mutex_unlock(&tunnel_mutex);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(pnv_pci_set_tunnel_bar);

व्योम pnv_pci_shutकरोwn(व्योम)
अणु
	काष्ठा pci_controller *hose;

	list_क्रम_each_entry(hose, &hose_list, list_node)
		अगर (hose->controller_ops.shutकरोwn)
			hose->controller_ops.shutकरोwn(hose);
पूर्ण

/* Fixup wrong class code in p7ioc and p8 root complex */
अटल व्योम pnv_p7ioc_rc_quirk(काष्ठा pci_dev *dev)
अणु
	dev->class = PCI_CLASS_BRIDGE_PCI << 8;
पूर्ण
DECLARE_PCI_FIXUP_EARLY(PCI_VENDOR_ID_IBM, 0x3b9, pnv_p7ioc_rc_quirk);

व्योम __init pnv_pci_init(व्योम)
अणु
	काष्ठा device_node *np;

	pci_add_flags(PCI_CAN_SKIP_ISA_ALIGN);

	/* If we करोn't have OPAL, eg. in sim, just skip PCI probe */
	अगर (!firmware_has_feature(FW_FEATURE_OPAL))
		वापस;

#अगर_घोषित CONFIG_PCIEPORTBUS
	/*
	 * On PowerNV PCIe devices are (currently) managed in cooperation
	 * with firmware. This isn't *strictly* required, but there's enough
	 * assumptions baked पूर्णांकo both firmware and the platक्रमm code that
	 * it's unwise to allow the portbus services to be used.
	 *
	 * We need to fix this eventually, but क्रम now set this flag to disable
	 * the portbus driver. The AER service isn't required since that AER
	 * events are handled via EEH. The pciehp hotplug driver can't work
	 * without kernel changes (and portbus binding अवरोधs pnv_php). The
	 * other services also require some thinking about how we're going
	 * to पूर्णांकegrate them.
	 */
	pcie_ports_disabled = true;
#पूर्ण_अगर

	/* Look क्रम IODA IO-Hubs. */
	क्रम_each_compatible_node(np, शून्य, "ibm,ioda-hub") अणु
		pnv_pci_init_ioda_hub(np);
	पूर्ण

	/* Look क्रम ioda2 built-in PHB3's */
	क्रम_each_compatible_node(np, शून्य, "ibm,ioda2-phb")
		pnv_pci_init_ioda2_phb(np);

	/* Look क्रम ioda3 built-in PHB4's, we treat them as IODA2 */
	क्रम_each_compatible_node(np, शून्य, "ibm,ioda3-phb")
		pnv_pci_init_ioda2_phb(np);

	/* Look क्रम NPU2 OpenCAPI PHBs */
	क्रम_each_compatible_node(np, शून्य, "ibm,ioda2-npu2-opencapi-phb")
		pnv_pci_init_npu2_खोलोcapi_phb(np);

	/* Configure IOMMU DMA hooks */
	set_pci_dma_ops(&dma_iommu_ops);
पूर्ण

अटल पूर्णांक pnv_tce_iommu_bus_notअगरier(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;

	चयन (action) अणु
	हाल BUS_NOTIFY_DEL_DEVICE:
		iommu_del_device(dev);
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block pnv_tce_iommu_bus_nb = अणु
	.notअगरier_call = pnv_tce_iommu_bus_notअगरier,
पूर्ण;

अटल पूर्णांक __init pnv_tce_iommu_bus_notअगरier_init(व्योम)
अणु
	bus_रेजिस्टर_notअगरier(&pci_bus_type, &pnv_tce_iommu_bus_nb);
	वापस 0;
पूर्ण
machine_subsys_initcall_sync(घातernv, pnv_tce_iommu_bus_notअगरier_init);
