<शैली गुरु>
/*
 * Copyright (c) 2010 - 2017 Intel Corporation.  All rights reserved.
 * Copyright (c) 2008, 2009 QLogic Corporation. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/aer.h>
#समावेश <linux/module.h>

#समावेश "qib.h"

/*
 * This file contains PCIe utility routines that are common to the
 * various QLogic InfiniPath adapters
 */

/*
 * Code to adjust PCIe capabilities.
 * To minimize the change footprपूर्णांक, we call it
 * from qib_pcie_params, which every chip-specअगरic
 * file calls, even though this violates some
 * expectations of harmlessness.
 */
अटल व्योम qib_tune_pcie_caps(काष्ठा qib_devdata *);
अटल व्योम qib_tune_pcie_coalesce(काष्ठा qib_devdata *);

/*
 * Do all the common PCIe setup and initialization.
 * devdata is not yet allocated, and is not allocated until after this
 * routine वापसs success.  Thereक्रमe qib_dev_err() can't be used क्रम error
 * prपूर्णांकing.
 */
पूर्णांक qib_pcie_init(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		/*
		 * This can happen (in theory) अगरf:
		 * We did a chip reset, and then failed to reprogram the
		 * BAR, or the chip reset due to an पूर्णांकernal error.  We then
		 * unloaded the driver and reloaded it.
		 *
		 * Both reset हालs set the BAR back to initial state.  For
		 * the latter हाल, the AER sticky error bit at offset 0x718
		 * should be set, but the Linux kernel करोesn't yet know
		 * about that, it appears.  If the original BAR was retained
		 * in the kernel data काष्ठाures, this may be OK.
		 */
		qib_early_err(&pdev->dev, "pci enable failed: error %d\n",
			      -ret);
		जाओ करोne;
	पूर्ण

	ret = pci_request_regions(pdev, QIB_DRV_NAME);
	अगर (ret) अणु
		qib_devinfo(pdev, "pci_request_regions fails: err %d\n", -ret);
		जाओ bail;
	पूर्ण

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		/*
		 * If the 64 bit setup fails, try 32 bit.  Some प्रणालीs
		 * करो not setup 64 bit maps on प्रणालीs with 2GB or less
		 * memory installed.
		 */
		ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			qib_devinfo(pdev, "Unable to set DMA mask: %d\n", ret);
			जाओ bail;
		पूर्ण
	पूर्ण

	pci_set_master(pdev);
	ret = pci_enable_pcie_error_reporting(pdev);
	अगर (ret) अणु
		qib_early_err(&pdev->dev,
			      "Unable to enable pcie error reporting: %d\n",
			      ret);
		ret = 0;
	पूर्ण
	जाओ करोne;

bail:
	pci_disable_device(pdev);
	pci_release_regions(pdev);
करोne:
	वापस ret;
पूर्ण

/*
 * Do reमुख्यing PCIe setup, once dd is allocated, and save away
 * fields required to re-initialize after a chip reset, or क्रम
 * various other purposes
 */
पूर्णांक qib_pcie_ddinit(काष्ठा qib_devdata *dd, काष्ठा pci_dev *pdev,
		    स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित दीर्घ len;
	resource_माप_प्रकार addr;

	dd->pcidev = pdev;
	pci_set_drvdata(pdev, dd);

	addr = pci_resource_start(pdev, 0);
	len = pci_resource_len(pdev, 0);

	dd->kregbase = ioremap(addr, len);
	अगर (!dd->kregbase)
		वापस -ENOMEM;

	dd->kregend = (u64 __iomem *)((व्योम __iomem *) dd->kregbase + len);
	dd->physaddr = addr;        /* used क्रम io_remap, etc. */

	/*
	 * Save BARs to reग_लिखो after device reset.  Save all 64 bits of
	 * BAR, just in हाल.
	 */
	dd->pcibar0 = addr;
	dd->pcibar1 = addr >> 32;
	dd->deviceid = ent->device; /* save क्रम later use */
	dd->venकरोrid = ent->venकरोr;

	वापस 0;
पूर्ण

/*
 * Do PCIe cleanup, after chip-specअगरic cleanup, etc.  Just prior
 * to releasing the dd memory.
 * व्योम because none of the core pcie cleanup वापसs are व्योम
 */
व्योम qib_pcie_ddcleanup(काष्ठा qib_devdata *dd)
अणु
	u64 __iomem *base = (व्योम __iomem *) dd->kregbase;

	dd->kregbase = शून्य;
	iounmap(base);
	अगर (dd->piobase)
		iounmap(dd->piobase);
	अगर (dd->userbase)
		iounmap(dd->userbase);
	अगर (dd->piovl15base)
		iounmap(dd->piovl15base);

	pci_disable_device(dd->pcidev);
	pci_release_regions(dd->pcidev);

	pci_set_drvdata(dd->pcidev, शून्य);
पूर्ण

/*
 * We save the msi lo and hi values, so we can restore them after
 * chip reset (the kernel PCI infraकाष्ठाure करोesn't yet handle that
 * correctly.
 */
अटल व्योम qib_cache_msi_info(काष्ठा qib_devdata *dd, पूर्णांक pos)
अणु
	काष्ठा pci_dev *pdev = dd->pcidev;
	u16 control;

	pci_पढ़ो_config_dword(pdev, pos + PCI_MSI_ADDRESS_LO, &dd->msi_lo);
	pci_पढ़ो_config_dword(pdev, pos + PCI_MSI_ADDRESS_HI, &dd->msi_hi);
	pci_पढ़ो_config_word(pdev, pos + PCI_MSI_FLAGS, &control);

	/* now save the data (vector) info */
	pci_पढ़ो_config_word(pdev,
			     pos + ((control & PCI_MSI_FLAGS_64BIT) ? 12 : 8),
			     &dd->msi_data);
पूर्ण

पूर्णांक qib_pcie_params(काष्ठा qib_devdata *dd, u32 minw, u32 *nent)
अणु
	u16 linkstat, speed;
	पूर्णांक nvec;
	पूर्णांक maxvec;
	अचिन्हित पूर्णांक flags = PCI_IRQ_MSIX | PCI_IRQ_MSI;

	अगर (!pci_is_pcie(dd->pcidev)) अणु
		qib_dev_err(dd, "Can't find PCI Express capability!\n");
		/* set up something... */
		dd->lbus_width = 1;
		dd->lbus_speed = 2500; /* Gen1, 2.5GHz */
		nvec = -1;
		जाओ bail;
	पूर्ण

	अगर (dd->flags & QIB_HAS_INTX)
		flags |= PCI_IRQ_LEGACY;
	maxvec = (nent && *nent) ? *nent : 1;
	nvec = pci_alloc_irq_vectors(dd->pcidev, 1, maxvec, flags);
	अगर (nvec < 0)
		जाओ bail;

	/*
	 * If nent exists, make sure to record how many vectors were allocated.
	 * If msix_enabled is false, वापस 0 so the fallback code works
	 * correctly.
	 */
	अगर (nent)
		*nent = !dd->pcidev->msix_enabled ? 0 : nvec;

	अगर (dd->pcidev->msi_enabled)
		qib_cache_msi_info(dd, dd->pcidev->msi_cap);

	pcie_capability_पढ़ो_word(dd->pcidev, PCI_EXP_LNKSTA, &linkstat);
	/*
	 * speed is bits 0-3, linkwidth is bits 4-8
	 * no defines क्रम them in headers
	 */
	speed = linkstat & 0xf;
	linkstat >>= 4;
	linkstat &= 0x1f;
	dd->lbus_width = linkstat;

	चयन (speed) अणु
	हाल 1:
		dd->lbus_speed = 2500; /* Gen1, 2.5GHz */
		अवरोध;
	हाल 2:
		dd->lbus_speed = 5000; /* Gen1, 5GHz */
		अवरोध;
	शेष: /* not defined, assume gen1 */
		dd->lbus_speed = 2500;
		अवरोध;
	पूर्ण

	/*
	 * Check against expected pcie width and complain अगर "wrong"
	 * on first initialization, not afterwards (i.e., reset).
	 */
	अगर (minw && linkstat < minw)
		qib_dev_err(dd,
			    "PCIe width %u (x%u HCA), performance reduced\n",
			    linkstat, minw);

	qib_tune_pcie_caps(dd);

	qib_tune_pcie_coalesce(dd);

bail:
	/* fill in string, even on errors */
	snम_लिखो(dd->lbus_info, माप(dd->lbus_info),
		 "PCIe,%uMHz,x%u\n", dd->lbus_speed, dd->lbus_width);
	वापस nvec < 0 ? nvec : 0;
पूर्ण

/**
 * qib_मुक्त_irq - Cleanup INTx and MSI पूर्णांकerrupts
 * @dd: valid poपूर्णांकer to qib dev data
 *
 * Since cleanup क्रम INTx and MSI पूर्णांकerrupts is trivial, have a common
 * routine.
 *
 */
व्योम qib_मुक्त_irq(काष्ठा qib_devdata *dd)
अणु
	pci_मुक्त_irq(dd->pcidev, 0, dd);
	pci_मुक्त_irq_vectors(dd->pcidev);
पूर्ण

/*
 * Setup pcie पूर्णांकerrupt stuff again after a reset.  I'd like to just call
 * pci_enable_msi() again क्रम msi, but when I करो that,
 * the MSI enable bit करोesn't get set in the command word, and
 * we चयन to to a dअगरferent पूर्णांकerrupt vector, which is confusing,
 * so I instead just करो it all अंतरभूत.  Perhaps somehow can tie this
 * पूर्णांकo the PCIe hotplug support at some poपूर्णांक
 */
पूर्णांक qib_reinit_पूर्णांकr(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक pos;
	u16 control;
	पूर्णांक ret = 0;

	/* If we aren't using MSI, don't restore it */
	अगर (!dd->msi_lo)
		जाओ bail;

	pos = dd->pcidev->msi_cap;
	अगर (!pos) अणु
		qib_dev_err(dd,
			"Can't find MSI capability, can't restore MSI settings\n");
		ret = 0;
		/* nothing special क्रम MSIx, just MSI */
		जाओ bail;
	पूर्ण
	pci_ग_लिखो_config_dword(dd->pcidev, pos + PCI_MSI_ADDRESS_LO,
			       dd->msi_lo);
	pci_ग_लिखो_config_dword(dd->pcidev, pos + PCI_MSI_ADDRESS_HI,
			       dd->msi_hi);
	pci_पढ़ो_config_word(dd->pcidev, pos + PCI_MSI_FLAGS, &control);
	अगर (!(control & PCI_MSI_FLAGS_ENABLE)) अणु
		control |= PCI_MSI_FLAGS_ENABLE;
		pci_ग_लिखो_config_word(dd->pcidev, pos + PCI_MSI_FLAGS,
				      control);
	पूर्ण
	/* now reग_लिखो the data (vector) info */
	pci_ग_लिखो_config_word(dd->pcidev, pos +
			      ((control & PCI_MSI_FLAGS_64BIT) ? 12 : 8),
			      dd->msi_data);
	ret = 1;
bail:
	qib_मुक्त_irq(dd);

	अगर (!ret && (dd->flags & QIB_HAS_INTX))
		ret = 1;

	/* and now set the pci master bit again */
	pci_set_master(dd->pcidev);

	वापस ret;
पूर्ण

/*
 * These two routines are helper routines क्रम the device reset code
 * to move all the pcie code out of the chip-specअगरic driver code.
 */
व्योम qib_pcie_अ_लोmd(काष्ठा qib_devdata *dd, u16 *cmd, u8 *iline, u8 *cline)
अणु
	pci_पढ़ो_config_word(dd->pcidev, PCI_COMMAND, cmd);
	pci_पढ़ो_config_byte(dd->pcidev, PCI_INTERRUPT_LINE, iline);
	pci_पढ़ो_config_byte(dd->pcidev, PCI_CACHE_LINE_SIZE, cline);
पूर्ण

व्योम qib_pcie_reenable(काष्ठा qib_devdata *dd, u16 cmd, u8 iline, u8 cline)
अणु
	पूर्णांक r;

	r = pci_ग_लिखो_config_dword(dd->pcidev, PCI_BASE_ADDRESS_0,
				   dd->pcibar0);
	अगर (r)
		qib_dev_err(dd, "rewrite of BAR0 failed: %d\n", r);
	r = pci_ग_लिखो_config_dword(dd->pcidev, PCI_BASE_ADDRESS_1,
				   dd->pcibar1);
	अगर (r)
		qib_dev_err(dd, "rewrite of BAR1 failed: %d\n", r);
	/* now re-enable memory access, and restore cosmetic settings */
	pci_ग_लिखो_config_word(dd->pcidev, PCI_COMMAND, cmd);
	pci_ग_लिखो_config_byte(dd->pcidev, PCI_INTERRUPT_LINE, iline);
	pci_ग_लिखो_config_byte(dd->pcidev, PCI_CACHE_LINE_SIZE, cline);
	r = pci_enable_device(dd->pcidev);
	अगर (r)
		qib_dev_err(dd,
			"pci_enable_device failed after reset: %d\n", r);
पूर्ण


अटल पूर्णांक qib_pcie_coalesce;
module_param_named(pcie_coalesce, qib_pcie_coalesce, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(pcie_coalesce, "tune PCIe coalescing on some Intel chipsets");

/*
 * Enable PCIe completion and data coalescing, on Intel 5x00 and 7300
 * chipsets.   This is known to be unsafe क्रम some revisions of some
 * of these chipsets, with some BIOS settings, and enabling it on those
 * प्रणालीs may result in the प्रणाली crashing, and/or data corruption.
 */
अटल व्योम qib_tune_pcie_coalesce(काष्ठा qib_devdata *dd)
अणु
	काष्ठा pci_dev *parent;
	u16 devid;
	u32 mask, bits, val;

	अगर (!qib_pcie_coalesce)
		वापस;

	/* Find out supported and configured values क्रम parent (root) */
	parent = dd->pcidev->bus->self;
	अगर (parent->bus->parent) अणु
		qib_devinfo(dd->pcidev, "Parent not root\n");
		वापस;
	पूर्ण
	अगर (!pci_is_pcie(parent))
		वापस;
	अगर (parent->venकरोr != 0x8086)
		वापस;

	/*
	 *  - bit 12: Max_rdcmp_Imt_EN: need to set to 1
	 *  - bit 11: COALESCE_FORCE: need to set to 0
	 *  - bit 10: COALESCE_EN: need to set to 1
	 *  (but limitations on some on some chipsets)
	 *
	 *  On the Intel 5000, 5100, and 7300 chipsets, there is
	 *  also: - bit 25:24: COALESCE_MODE, need to set to 0
	 */
	devid = parent->device;
	अगर (devid >= 0x25e2 && devid <= 0x25fa) अणु
		/* 5000 P/V/X/Z */
		अगर (parent->revision <= 0xb2)
			bits = 1U << 10;
		अन्यथा
			bits = 7U << 10;
		mask = (3U << 24) | (7U << 10);
	पूर्ण अन्यथा अगर (devid >= 0x65e2 && devid <= 0x65fa) अणु
		/* 5100 */
		bits = 1U << 10;
		mask = (3U << 24) | (7U << 10);
	पूर्ण अन्यथा अगर (devid >= 0x4021 && devid <= 0x402e) अणु
		/* 5400 */
		bits = 7U << 10;
		mask = 7U << 10;
	पूर्ण अन्यथा अगर (devid >= 0x3604 && devid <= 0x360a) अणु
		/* 7300 */
		bits = 7U << 10;
		mask = (3U << 24) | (7U << 10);
	पूर्ण अन्यथा अणु
		/* not one of the chipsets that we know about */
		वापस;
	पूर्ण
	pci_पढ़ो_config_dword(parent, 0x48, &val);
	val &= ~mask;
	val |= bits;
	pci_ग_लिखो_config_dword(parent, 0x48, val);
पूर्ण

/*
 * BIOS may not set PCIe bus-utilization parameters क्रम best perक्रमmance.
 * Check and optionally adjust them to maximize our throughput.
 */
अटल पूर्णांक qib_pcie_caps;
module_param_named(pcie_caps, qib_pcie_caps, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(pcie_caps, "Max PCIe tuning: Payload (0..3), ReadReq (4..7)");

अटल व्योम qib_tune_pcie_caps(काष्ठा qib_devdata *dd)
अणु
	काष्ठा pci_dev *parent;
	u16 rc_mpss, rc_mps, ep_mpss, ep_mps;
	u16 rc_mrrs, ep_mrrs, max_mrrs;

	/* Find out supported and configured values क्रम parent (root) */
	parent = dd->pcidev->bus->self;
	अगर (!pci_is_root_bus(parent->bus)) अणु
		qib_devinfo(dd->pcidev, "Parent not root\n");
		वापस;
	पूर्ण

	अगर (!pci_is_pcie(parent) || !pci_is_pcie(dd->pcidev))
		वापस;

	rc_mpss = parent->pcie_mpss;
	rc_mps = ffs(pcie_get_mps(parent)) - 8;
	/* Find out supported and configured values क्रम endpoपूर्णांक (us) */
	ep_mpss = dd->pcidev->pcie_mpss;
	ep_mps = ffs(pcie_get_mps(dd->pcidev)) - 8;

	/* Find max payload supported by root, endpoपूर्णांक */
	अगर (rc_mpss > ep_mpss)
		rc_mpss = ep_mpss;

	/* If Supported greater than limit in module param, limit it */
	अगर (rc_mpss > (qib_pcie_caps & 7))
		rc_mpss = qib_pcie_caps & 7;
	/* If less than (allowed, supported), bump root payload */
	अगर (rc_mpss > rc_mps) अणु
		rc_mps = rc_mpss;
		pcie_set_mps(parent, 128 << rc_mps);
	पूर्ण
	/* If less than (allowed, supported), bump endpoपूर्णांक payload */
	अगर (rc_mpss > ep_mps) अणु
		ep_mps = rc_mpss;
		pcie_set_mps(dd->pcidev, 128 << ep_mps);
	पूर्ण

	/*
	 * Now the Read Request size.
	 * No field क्रम max supported, but PCIe spec limits it to 4096,
	 * which is code '5' (log2(4096) - 7)
	 */
	max_mrrs = 5;
	अगर (max_mrrs > ((qib_pcie_caps >> 4) & 7))
		max_mrrs = (qib_pcie_caps >> 4) & 7;

	max_mrrs = 128 << max_mrrs;
	rc_mrrs = pcie_get_पढ़ोrq(parent);
	ep_mrrs = pcie_get_पढ़ोrq(dd->pcidev);

	अगर (max_mrrs > rc_mrrs) अणु
		rc_mrrs = max_mrrs;
		pcie_set_पढ़ोrq(parent, rc_mrrs);
	पूर्ण
	अगर (max_mrrs > ep_mrrs) अणु
		ep_mrrs = max_mrrs;
		pcie_set_पढ़ोrq(dd->pcidev, ep_mrrs);
	पूर्ण
पूर्ण
/* End of PCIe capability tuning */

/*
 * From here through qib_pci_err_handler definition is invoked via
 * PCI error infraकाष्ठाure, रेजिस्टरed via pci
 */
अटल pci_ers_result_t
qib_pci_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा qib_devdata *dd = pci_get_drvdata(pdev);
	pci_ers_result_t ret = PCI_ERS_RESULT_RECOVERED;

	चयन (state) अणु
	हाल pci_channel_io_normal:
		qib_devinfo(pdev, "State Normal, ignoring\n");
		अवरोध;

	हाल pci_channel_io_frozen:
		qib_devinfo(pdev, "State Frozen, requesting reset\n");
		pci_disable_device(pdev);
		ret = PCI_ERS_RESULT_NEED_RESET;
		अवरोध;

	हाल pci_channel_io_perm_failure:
		qib_devinfo(pdev, "State Permanent Failure, disabling\n");
		अगर (dd) अणु
			/* no more रेजिस्टर accesses! */
			dd->flags &= ~QIB_PRESENT;
			qib_disable_after_error(dd);
		पूर्ण
		 /* अन्यथा early, or other problem */
		ret =  PCI_ERS_RESULT_DISCONNECT;
		अवरोध;

	शेष: /* shouldn't happen */
		qib_devinfo(pdev, "QIB PCI errors detected (state %d)\n",
			state);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल pci_ers_result_t
qib_pci_mmio_enabled(काष्ठा pci_dev *pdev)
अणु
	u64 words = 0U;
	काष्ठा qib_devdata *dd = pci_get_drvdata(pdev);
	pci_ers_result_t ret = PCI_ERS_RESULT_RECOVERED;

	अगर (dd && dd->pport) अणु
		words = dd->f_portcntr(dd->pport, QIBPORTCNTR_WORDRCV);
		अगर (words == ~0ULL)
			ret = PCI_ERS_RESULT_NEED_RESET;
	पूर्ण
	qib_devinfo(pdev,
		"QIB mmio_enabled function called, read wordscntr %Lx, returning %d\n",
		words, ret);
	वापस  ret;
पूर्ण

अटल pci_ers_result_t
qib_pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	qib_devinfo(pdev, "QIB slot_reset function called, ignored\n");
	वापस PCI_ERS_RESULT_CAN_RECOVER;
पूर्ण

अटल व्योम
qib_pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qib_devdata *dd = pci_get_drvdata(pdev);

	qib_devinfo(pdev, "QIB resume function called\n");
	/*
	 * Running jobs will fail, since it's asynchronous
	 * unlike sysfs-requested reset.   Better than
	 * करोing nothing.
	 */
	qib_init(dd, 1); /* same as re-init after reset */
पूर्ण

स्थिर काष्ठा pci_error_handlers qib_pci_err_handler = अणु
	.error_detected = qib_pci_error_detected,
	.mmio_enabled = qib_pci_mmio_enabled,
	.slot_reset = qib_pci_slot_reset,
	.resume = qib_pci_resume,
पूर्ण;
