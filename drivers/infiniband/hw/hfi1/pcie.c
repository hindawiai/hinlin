<शैली गुरु>
/*
 * Copyright(c) 2015 - 2019 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/aer.h>
#समावेश <linux/module.h>

#समावेश "hfi.h"
#समावेश "chip_registers.h"
#समावेश "aspm.h"

/*
 * This file contains PCIe utility routines.
 */

/*
 * Do all the common PCIe setup and initialization.
 */
पूर्णांक hfi1_pcie_init(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;
	काष्ठा pci_dev *pdev = dd->pcidev;

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
		dd_dev_err(dd, "pci enable failed: error %d\n", -ret);
		वापस ret;
	पूर्ण

	ret = pci_request_regions(pdev, DRIVER_NAME);
	अगर (ret) अणु
		dd_dev_err(dd, "pci_request_regions fails: err %d\n", -ret);
		जाओ bail;
	पूर्ण

	ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		/*
		 * If the 64 bit setup fails, try 32 bit.  Some प्रणालीs
		 * करो not setup 64 bit maps on प्रणालीs with 2GB or less
		 * memory installed.
		 */
		ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		अगर (ret) अणु
			dd_dev_err(dd, "Unable to set DMA mask: %d\n", ret);
			जाओ bail;
		पूर्ण
		ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	पूर्ण अन्यथा अणु
		ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	पूर्ण
	अगर (ret) अणु
		dd_dev_err(dd, "Unable to set DMA consistent mask: %d\n", ret);
		जाओ bail;
	पूर्ण

	pci_set_master(pdev);
	(व्योम)pci_enable_pcie_error_reporting(pdev);
	वापस 0;

bail:
	hfi1_pcie_cleanup(pdev);
	वापस ret;
पूर्ण

/*
 * Clean what was करोne in hfi1_pcie_init()
 */
व्योम hfi1_pcie_cleanup(काष्ठा pci_dev *pdev)
अणु
	pci_disable_device(pdev);
	/*
	 * Release regions should be called after the disable. OK to
	 * call अगर request regions has not been called or failed.
	 */
	pci_release_regions(pdev);
पूर्ण

/*
 * Do reमुख्यing PCIe setup, once dd is allocated, and save away
 * fields required to re-initialize after a chip reset, or क्रम
 * various other purposes
 */
पूर्णांक hfi1_pcie_ddinit(काष्ठा hfi1_devdata *dd, काष्ठा pci_dev *pdev)
अणु
	अचिन्हित दीर्घ len;
	resource_माप_प्रकार addr;
	पूर्णांक ret = 0;
	u32 rcv_array_count;

	addr = pci_resource_start(pdev, 0);
	len = pci_resource_len(pdev, 0);

	/*
	 * The TXE PIO buffers are at the tail end of the chip space.
	 * Cut them off and map them separately.
	 */

	/* sanity check vs expectations */
	अगर (len != TXE_PIO_SEND + TXE_PIO_SIZE) अणु
		dd_dev_err(dd, "chip PIO range does not match\n");
		वापस -EINVAL;
	पूर्ण

	dd->kregbase1 = ioremap(addr, RCV_ARRAY);
	अगर (!dd->kregbase1) अणु
		dd_dev_err(dd, "UC mapping of kregbase1 failed\n");
		वापस -ENOMEM;
	पूर्ण
	dd_dev_info(dd, "UC base1: %p for %x\n", dd->kregbase1, RCV_ARRAY);

	/* verअगरy that पढ़ोs actually work, save revision क्रम reset check */
	dd->revision = पढ़ोq(dd->kregbase1 + CCE_REVISION);
	अगर (dd->revision == ~(u64)0) अणु
		dd_dev_err(dd, "Cannot read chip CSRs\n");
		जाओ nomem;
	पूर्ण

	rcv_array_count = पढ़ोq(dd->kregbase1 + RCV_ARRAY_CNT);
	dd_dev_info(dd, "RcvArray count: %u\n", rcv_array_count);
	dd->base2_start  = RCV_ARRAY + rcv_array_count * 8;

	dd->kregbase2 = ioremap(
		addr + dd->base2_start,
		TXE_PIO_SEND - dd->base2_start);
	अगर (!dd->kregbase2) अणु
		dd_dev_err(dd, "UC mapping of kregbase2 failed\n");
		जाओ nomem;
	पूर्ण
	dd_dev_info(dd, "UC base2: %p for %x\n", dd->kregbase2,
		    TXE_PIO_SEND - dd->base2_start);

	dd->piobase = ioremap_wc(addr + TXE_PIO_SEND, TXE_PIO_SIZE);
	अगर (!dd->piobase) अणु
		dd_dev_err(dd, "WC mapping of send buffers failed\n");
		जाओ nomem;
	पूर्ण
	dd_dev_info(dd, "WC piobase: %p for %x\n", dd->piobase, TXE_PIO_SIZE);

	dd->physaddr = addr;        /* used क्रम io_remap, etc. */

	/*
	 * Map the chip's RcvArray as ग_लिखो-combining to allow us
	 * to ग_लिखो an entire cacheline worth of entries in one shot.
	 */
	dd->rcvarray_wc = ioremap_wc(addr + RCV_ARRAY,
				     rcv_array_count * 8);
	अगर (!dd->rcvarray_wc) अणु
		dd_dev_err(dd, "WC mapping of receive array failed\n");
		जाओ nomem;
	पूर्ण
	dd_dev_info(dd, "WC RcvArray: %p for %x\n",
		    dd->rcvarray_wc, rcv_array_count * 8);

	dd->flags |= HFI1_PRESENT;	/* chip.c CSR routines now work */
	वापस 0;
nomem:
	ret = -ENOMEM;
	hfi1_pcie_ddcleanup(dd);
	वापस ret;
पूर्ण

/*
 * Do PCIe cleanup related to dd, after chip-specअगरic cleanup, etc.  Just prior
 * to releasing the dd memory.
 * Void because all of the core pcie cleanup functions are व्योम.
 */
व्योम hfi1_pcie_ddcleanup(काष्ठा hfi1_devdata *dd)
अणु
	dd->flags &= ~HFI1_PRESENT;
	अगर (dd->kregbase1)
		iounmap(dd->kregbase1);
	dd->kregbase1 = शून्य;
	अगर (dd->kregbase2)
		iounmap(dd->kregbase2);
	dd->kregbase2 = शून्य;
	अगर (dd->rcvarray_wc)
		iounmap(dd->rcvarray_wc);
	dd->rcvarray_wc = शून्य;
	अगर (dd->piobase)
		iounmap(dd->piobase);
	dd->piobase = शून्य;
पूर्ण

/* वापस the PCIe link speed from the given link status */
अटल u32 extract_speed(u16 linkstat)
अणु
	u32 speed;

	चयन (linkstat & PCI_EXP_LNKSTA_CLS) अणु
	शेष: /* not defined, assume Gen1 */
	हाल PCI_EXP_LNKSTA_CLS_2_5GB:
		speed = 2500; /* Gen 1, 2.5GHz */
		अवरोध;
	हाल PCI_EXP_LNKSTA_CLS_5_0GB:
		speed = 5000; /* Gen 2, 5GHz */
		अवरोध;
	हाल PCI_EXP_LNKSTA_CLS_8_0GB:
		speed = 8000; /* Gen 3, 8GHz */
		अवरोध;
	पूर्ण
	वापस speed;
पूर्ण

/* वापस the PCIe link speed from the given link status */
अटल u32 extract_width(u16 linkstat)
अणु
	वापस (linkstat & PCI_EXP_LNKSTA_NLW) >> PCI_EXP_LNKSTA_NLW_SHIFT;
पूर्ण

/* पढ़ो the link status and set dd->अणुlbus_width,lbus_speed,lbus_infoपूर्ण */
अटल व्योम update_lbus_info(काष्ठा hfi1_devdata *dd)
अणु
	u16 linkstat;
	पूर्णांक ret;

	ret = pcie_capability_पढ़ो_word(dd->pcidev, PCI_EXP_LNKSTA, &linkstat);
	अगर (ret) अणु
		dd_dev_err(dd, "Unable to read from PCI config\n");
		वापस;
	पूर्ण

	dd->lbus_width = extract_width(linkstat);
	dd->lbus_speed = extract_speed(linkstat);
	snम_लिखो(dd->lbus_info, माप(dd->lbus_info),
		 "PCIe,%uMHz,x%u", dd->lbus_speed, dd->lbus_width);
पूर्ण

/*
 * Read in the current PCIe link width and speed.  Find अगर the link is
 * Gen3 capable.
 */
पूर्णांक pcie_speeds(काष्ठा hfi1_devdata *dd)
अणु
	u32 linkcap;
	काष्ठा pci_dev *parent = dd->pcidev->bus->self;
	पूर्णांक ret;

	अगर (!pci_is_pcie(dd->pcidev)) अणु
		dd_dev_err(dd, "Can't find PCI Express capability!\n");
		वापस -EINVAL;
	पूर्ण

	/* find अगर our max speed is Gen3 and parent supports Gen3 speeds */
	dd->link_gen3_capable = 1;

	ret = pcie_capability_पढ़ो_dword(dd->pcidev, PCI_EXP_LNKCAP, &linkcap);
	अगर (ret) अणु
		dd_dev_err(dd, "Unable to read from PCI config\n");
		वापस pcibios_err_to_त्रुटि_सं(ret);
	पूर्ण

	अगर ((linkcap & PCI_EXP_LNKCAP_SLS) != PCI_EXP_LNKCAP_SLS_8_0GB) अणु
		dd_dev_info(dd,
			    "This HFI is not Gen3 capable, max speed 0x%x, need 0x3\n",
			    linkcap & PCI_EXP_LNKCAP_SLS);
		dd->link_gen3_capable = 0;
	पूर्ण

	/*
	 * bus->max_bus_speed is set from the bridge's linkcap Max Link Speed
	 */
	अगर (parent &&
	    (dd->pcidev->bus->max_bus_speed == PCIE_SPEED_2_5GT ||
	     dd->pcidev->bus->max_bus_speed == PCIE_SPEED_5_0GT)) अणु
		dd_dev_info(dd, "Parent PCIe bridge does not support Gen3\n");
		dd->link_gen3_capable = 0;
	पूर्ण

	/* obtain the link width and current speed */
	update_lbus_info(dd);

	dd_dev_info(dd, "%s\n", dd->lbus_info);

	वापस 0;
पूर्ण

/*
 * Restore command and BARs after a reset has wiped them out
 *
 * Returns 0 on success, otherwise a negative error value
 */
पूर्णांक restore_pci_variables(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;

	ret = pci_ग_लिखो_config_word(dd->pcidev, PCI_COMMAND, dd->pci_command);
	अगर (ret)
		जाओ error;

	ret = pci_ग_लिखो_config_dword(dd->pcidev, PCI_BASE_ADDRESS_0,
				     dd->pcibar0);
	अगर (ret)
		जाओ error;

	ret = pci_ग_लिखो_config_dword(dd->pcidev, PCI_BASE_ADDRESS_1,
				     dd->pcibar1);
	अगर (ret)
		जाओ error;

	ret = pci_ग_लिखो_config_dword(dd->pcidev, PCI_ROM_ADDRESS, dd->pci_rom);
	अगर (ret)
		जाओ error;

	ret = pcie_capability_ग_लिखो_word(dd->pcidev, PCI_EXP_DEVCTL,
					 dd->pcie_devctl);
	अगर (ret)
		जाओ error;

	ret = pcie_capability_ग_लिखो_word(dd->pcidev, PCI_EXP_LNKCTL,
					 dd->pcie_lnkctl);
	अगर (ret)
		जाओ error;

	ret = pcie_capability_ग_लिखो_word(dd->pcidev, PCI_EXP_DEVCTL2,
					 dd->pcie_devctl2);
	अगर (ret)
		जाओ error;

	ret = pci_ग_लिखो_config_dword(dd->pcidev, PCI_CFG_MSIX0, dd->pci_msix0);
	अगर (ret)
		जाओ error;

	अगर (pci_find_ext_capability(dd->pcidev, PCI_EXT_CAP_ID_TPH)) अणु
		ret = pci_ग_लिखो_config_dword(dd->pcidev, PCIE_CFG_TPH2,
					     dd->pci_tph2);
		अगर (ret)
			जाओ error;
	पूर्ण
	वापस 0;

error:
	dd_dev_err(dd, "Unable to write to PCI config\n");
	वापस pcibios_err_to_त्रुटि_सं(ret);
पूर्ण

/*
 * Save BARs and command to reग_लिखो after device reset
 *
 * Returns 0 on success, otherwise a negative error value
 */
पूर्णांक save_pci_variables(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक ret;

	ret = pci_पढ़ो_config_dword(dd->pcidev, PCI_BASE_ADDRESS_0,
				    &dd->pcibar0);
	अगर (ret)
		जाओ error;

	ret = pci_पढ़ो_config_dword(dd->pcidev, PCI_BASE_ADDRESS_1,
				    &dd->pcibar1);
	अगर (ret)
		जाओ error;

	ret = pci_पढ़ो_config_dword(dd->pcidev, PCI_ROM_ADDRESS, &dd->pci_rom);
	अगर (ret)
		जाओ error;

	ret = pci_पढ़ो_config_word(dd->pcidev, PCI_COMMAND, &dd->pci_command);
	अगर (ret)
		जाओ error;

	ret = pcie_capability_पढ़ो_word(dd->pcidev, PCI_EXP_DEVCTL,
					&dd->pcie_devctl);
	अगर (ret)
		जाओ error;

	ret = pcie_capability_पढ़ो_word(dd->pcidev, PCI_EXP_LNKCTL,
					&dd->pcie_lnkctl);
	अगर (ret)
		जाओ error;

	ret = pcie_capability_पढ़ो_word(dd->pcidev, PCI_EXP_DEVCTL2,
					&dd->pcie_devctl2);
	अगर (ret)
		जाओ error;

	ret = pci_पढ़ो_config_dword(dd->pcidev, PCI_CFG_MSIX0, &dd->pci_msix0);
	अगर (ret)
		जाओ error;

	अगर (pci_find_ext_capability(dd->pcidev, PCI_EXT_CAP_ID_TPH)) अणु
		ret = pci_पढ़ो_config_dword(dd->pcidev, PCIE_CFG_TPH2,
					    &dd->pci_tph2);
		अगर (ret)
			जाओ error;
	पूर्ण
	वापस 0;

error:
	dd_dev_err(dd, "Unable to read from PCI config\n");
	वापस pcibios_err_to_त्रुटि_सं(ret);
पूर्ण

/*
 * BIOS may not set PCIe bus-utilization parameters क्रम best perक्रमmance.
 * Check and optionally adjust them to maximize our throughput.
 */
अटल पूर्णांक hfi1_pcie_caps;
module_param_named(pcie_caps, hfi1_pcie_caps, पूर्णांक, 0444);
MODULE_PARM_DESC(pcie_caps, "Max PCIe tuning: Payload (0..3), ReadReq (4..7)");

/**
 * tune_pcie_caps() - Code to adjust PCIe capabilities.
 * @dd: Valid device data काष्ठाure
 *
 */
व्योम tune_pcie_caps(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा pci_dev *parent;
	u16 rc_mpss, rc_mps, ep_mpss, ep_mps;
	u16 rc_mrrs, ep_mrrs, max_mrrs, ectl;
	पूर्णांक ret;

	/*
	 * Turn on extended tags in DevCtl in हाल the BIOS has turned it off
	 * to improve WFR SDMA bandwidth
	 */
	ret = pcie_capability_पढ़ो_word(dd->pcidev, PCI_EXP_DEVCTL, &ectl);
	अगर ((!ret) && !(ectl & PCI_EXP_DEVCTL_EXT_TAG)) अणु
		dd_dev_info(dd, "Enabling PCIe extended tags\n");
		ectl |= PCI_EXP_DEVCTL_EXT_TAG;
		ret = pcie_capability_ग_लिखो_word(dd->pcidev,
						 PCI_EXP_DEVCTL, ectl);
		अगर (ret)
			dd_dev_info(dd, "Unable to write to PCI config\n");
	पूर्ण
	/* Find out supported and configured values क्रम parent (root) */
	parent = dd->pcidev->bus->self;
	/*
	 * The driver cannot perक्रमm the tuning अगर it करोes not have
	 * access to the upstream component.
	 */
	अगर (!parent) अणु
		dd_dev_info(dd, "Parent not found\n");
		वापस;
	पूर्ण
	अगर (!pci_is_root_bus(parent->bus)) अणु
		dd_dev_info(dd, "Parent not root\n");
		वापस;
	पूर्ण
	अगर (!pci_is_pcie(parent)) अणु
		dd_dev_info(dd, "Parent is not PCI Express capable\n");
		वापस;
	पूर्ण
	अगर (!pci_is_pcie(dd->pcidev)) अणु
		dd_dev_info(dd, "PCI device is not PCI Express capable\n");
		वापस;
	पूर्ण
	rc_mpss = parent->pcie_mpss;
	rc_mps = ffs(pcie_get_mps(parent)) - 8;
	/* Find out supported and configured values क्रम endpoपूर्णांक (us) */
	ep_mpss = dd->pcidev->pcie_mpss;
	ep_mps = ffs(pcie_get_mps(dd->pcidev)) - 8;

	/* Find max payload supported by root, endpoपूर्णांक */
	अगर (rc_mpss > ep_mpss)
		rc_mpss = ep_mpss;

	/* If Supported greater than limit in module param, limit it */
	अगर (rc_mpss > (hfi1_pcie_caps & 7))
		rc_mpss = hfi1_pcie_caps & 7;
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
	अगर (max_mrrs > ((hfi1_pcie_caps >> 4) & 7))
		max_mrrs = (hfi1_pcie_caps >> 4) & 7;

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
 * From here through hfi1_pci_err_handler definition is invoked via
 * PCI error infraकाष्ठाure, रेजिस्टरed via pci
 */
अटल pci_ers_result_t
pci_error_detected(काष्ठा pci_dev *pdev, pci_channel_state_t state)
अणु
	काष्ठा hfi1_devdata *dd = pci_get_drvdata(pdev);
	pci_ers_result_t ret = PCI_ERS_RESULT_RECOVERED;

	चयन (state) अणु
	हाल pci_channel_io_normal:
		dd_dev_info(dd, "State Normal, ignoring\n");
		अवरोध;

	हाल pci_channel_io_frozen:
		dd_dev_info(dd, "State Frozen, requesting reset\n");
		pci_disable_device(pdev);
		ret = PCI_ERS_RESULT_NEED_RESET;
		अवरोध;

	हाल pci_channel_io_perm_failure:
		अगर (dd) अणु
			dd_dev_info(dd, "State Permanent Failure, disabling\n");
			/* no more रेजिस्टर accesses! */
			dd->flags &= ~HFI1_PRESENT;
			hfi1_disable_after_error(dd);
		पूर्ण
		 /* अन्यथा early, or other problem */
		ret =  PCI_ERS_RESULT_DISCONNECT;
		अवरोध;

	शेष: /* shouldn't happen */
		dd_dev_info(dd, "HFI1 PCI errors detected (state %d)\n",
			    state);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल pci_ers_result_t
pci_mmio_enabled(काष्ठा pci_dev *pdev)
अणु
	u64 words = 0U;
	काष्ठा hfi1_devdata *dd = pci_get_drvdata(pdev);
	pci_ers_result_t ret = PCI_ERS_RESULT_RECOVERED;

	अगर (dd && dd->pport) अणु
		words = पढ़ो_port_cntr(dd->pport, C_RX_WORDS, CNTR_INVALID_VL);
		अगर (words == ~0ULL)
			ret = PCI_ERS_RESULT_NEED_RESET;
		dd_dev_info(dd,
			    "HFI1 mmio_enabled function called, read wordscntr %llx, returning %d\n",
			    words, ret);
	पूर्ण
	वापस  ret;
पूर्ण

अटल pci_ers_result_t
pci_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hfi1_devdata *dd = pci_get_drvdata(pdev);

	dd_dev_info(dd, "HFI1 slot_reset function called, ignored\n");
	वापस PCI_ERS_RESULT_CAN_RECOVER;
पूर्ण

अटल व्योम
pci_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा hfi1_devdata *dd = pci_get_drvdata(pdev);

	dd_dev_info(dd, "HFI1 resume function called\n");
	/*
	 * Running jobs will fail, since it's asynchronous
	 * unlike sysfs-requested reset.   Better than
	 * करोing nothing.
	 */
	hfi1_init(dd, 1); /* same as re-init after reset */
पूर्ण

स्थिर काष्ठा pci_error_handlers hfi1_pci_err_handler = अणु
	.error_detected = pci_error_detected,
	.mmio_enabled = pci_mmio_enabled,
	.slot_reset = pci_slot_reset,
	.resume = pci_resume,
पूर्ण;

/*============================================================================*/
/* PCIe Gen3 support */

/*
 * This code is separated out because it is expected to be हटाओd in the
 * final shipping product.  If not, then it will be revisited and items
 * will be moved to more standard locations.
 */

/* ASIC_PCI_SD_HOST_STATUS.FW_DNLD_STS field values */
#घोषणा DL_STATUS_HFI0 0x1	/* hfi0 firmware करोwnload complete */
#घोषणा DL_STATUS_HFI1 0x2	/* hfi1 firmware करोwnload complete */
#घोषणा DL_STATUS_BOTH 0x3	/* hfi0 and hfi1 firmware करोwnload complete */

/* ASIC_PCI_SD_HOST_STATUS.FW_DNLD_ERR field values */
#घोषणा DL_ERR_NONE		0x0	/* no error */
#घोषणा DL_ERR_SWAP_PARITY	0x1	/* parity error in SerDes पूर्णांकerrupt */
					/*   or response data */
#घोषणा DL_ERR_DISABLED	0x2	/* hfi disabled */
#घोषणा DL_ERR_SECURITY	0x3	/* security check failed */
#घोषणा DL_ERR_SBUS		0x4	/* SBus status error */
#घोषणा DL_ERR_XFR_PARITY	0x5	/* parity error during ROM transfer*/

/* gasket block secondary bus reset delay */
#घोषणा SBR_DELAY_US 200000	/* 200ms */

अटल uपूर्णांक pcie_target = 3;
module_param(pcie_target, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(pcie_target, "PCIe target speed (0 skip, 1-3 Gen1-3)");

अटल uपूर्णांक pcie_क्रमce;
module_param(pcie_क्रमce, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(pcie_क्रमce, "Force driver to do a PCIe firmware download even if already at target speed");

अटल uपूर्णांक pcie_retry = 5;
module_param(pcie_retry, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(pcie_retry, "Driver will try this many times to reach requested speed");

#घोषणा UNSET_PSET 255
#घोषणा DEFAULT_DISCRETE_PSET 2	/* discrete HFI */
#घोषणा DEFAULT_MCP_PSET 6	/* MCP HFI */
अटल uपूर्णांक pcie_pset = UNSET_PSET;
module_param(pcie_pset, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(pcie_pset, "PCIe Eq Pset value to use, range is 0-10");

अटल uपूर्णांक pcie_ctle = 3; /* discrete on, पूर्णांकegrated on */
module_param(pcie_ctle, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(pcie_ctle, "PCIe static CTLE mode, bit 0 - discrete on/off, bit 1 - integrated on/off");

/* equalization columns */
#घोषणा PREC 0
#घोषणा ATTN 1
#घोषणा POST 2

/* discrete silicon preliminary equalization values */
अटल स्थिर u8 discrete_preliminary_eq[11][3] = अणु
	/* prec   attn   post */
	अणु  0x00,  0x00,  0x12 पूर्ण,	/* p0 */
	अणु  0x00,  0x00,  0x0c पूर्ण,	/* p1 */
	अणु  0x00,  0x00,  0x0f पूर्ण,	/* p2 */
	अणु  0x00,  0x00,  0x09 पूर्ण,	/* p3 */
	अणु  0x00,  0x00,  0x00 पूर्ण,	/* p4 */
	अणु  0x06,  0x00,  0x00 पूर्ण,	/* p5 */
	अणु  0x09,  0x00,  0x00 पूर्ण,	/* p6 */
	अणु  0x06,  0x00,  0x0f पूर्ण,	/* p7 */
	अणु  0x09,  0x00,  0x09 पूर्ण,	/* p8 */
	अणु  0x0c,  0x00,  0x00 पूर्ण,	/* p9 */
	अणु  0x00,  0x00,  0x18 पूर्ण,	/* p10 */
पूर्ण;

/* पूर्णांकegrated silicon preliminary equalization values */
अटल स्थिर u8 पूर्णांकegrated_preliminary_eq[11][3] = अणु
	/* prec   attn   post */
	अणु  0x00,  0x1e,  0x07 पूर्ण,	/* p0 */
	अणु  0x00,  0x1e,  0x05 पूर्ण,	/* p1 */
	अणु  0x00,  0x1e,  0x06 पूर्ण,	/* p2 */
	अणु  0x00,  0x1e,  0x04 पूर्ण,	/* p3 */
	अणु  0x00,  0x1e,  0x00 पूर्ण,	/* p4 */
	अणु  0x03,  0x1e,  0x00 पूर्ण,	/* p5 */
	अणु  0x04,  0x1e,  0x00 पूर्ण,	/* p6 */
	अणु  0x03,  0x1e,  0x06 पूर्ण,	/* p7 */
	अणु  0x03,  0x1e,  0x04 पूर्ण,	/* p8 */
	अणु  0x05,  0x1e,  0x00 पूर्ण,	/* p9 */
	अणु  0x00,  0x1e,  0x0a पूर्ण,	/* p10 */
पूर्ण;

अटल स्थिर u8 discrete_ctle_tunings[11][4] = अणु
	/* DC     LF     HF     BW */
	अणु  0x48,  0x0b,  0x04,  0x04 पूर्ण,	/* p0 */
	अणु  0x60,  0x05,  0x0f,  0x0a पूर्ण,	/* p1 */
	अणु  0x50,  0x09,  0x06,  0x06 पूर्ण,	/* p2 */
	अणु  0x68,  0x05,  0x0f,  0x0a पूर्ण,	/* p3 */
	अणु  0x80,  0x05,  0x0f,  0x0a पूर्ण,	/* p4 */
	अणु  0x70,  0x05,  0x0f,  0x0a पूर्ण,	/* p5 */
	अणु  0x68,  0x05,  0x0f,  0x0a पूर्ण,	/* p6 */
	अणु  0x38,  0x0f,  0x00,  0x00 पूर्ण,	/* p7 */
	अणु  0x48,  0x09,  0x06,  0x06 पूर्ण,	/* p8 */
	अणु  0x60,  0x05,  0x0f,  0x0a पूर्ण,	/* p9 */
	अणु  0x38,  0x0f,  0x00,  0x00 पूर्ण,	/* p10 */
पूर्ण;

अटल स्थिर u8 पूर्णांकegrated_ctle_tunings[11][4] = अणु
	/* DC     LF     HF     BW */
	अणु  0x38,  0x0f,  0x00,  0x00 पूर्ण,	/* p0 */
	अणु  0x38,  0x0f,  0x00,  0x00 पूर्ण,	/* p1 */
	अणु  0x38,  0x0f,  0x00,  0x00 पूर्ण,	/* p2 */
	अणु  0x38,  0x0f,  0x00,  0x00 पूर्ण,	/* p3 */
	अणु  0x58,  0x0a,  0x05,  0x05 पूर्ण,	/* p4 */
	अणु  0x48,  0x0a,  0x05,  0x05 पूर्ण,	/* p5 */
	अणु  0x40,  0x0a,  0x05,  0x05 पूर्ण,	/* p6 */
	अणु  0x38,  0x0f,  0x00,  0x00 पूर्ण,	/* p7 */
	अणु  0x38,  0x0f,  0x00,  0x00 पूर्ण,	/* p8 */
	अणु  0x38,  0x09,  0x06,  0x06 पूर्ण,	/* p9 */
	अणु  0x38,  0x0e,  0x01,  0x01 पूर्ण,	/* p10 */
पूर्ण;

/* helper to क्रमmat the value to ग_लिखो to hardware */
#घोषणा eq_value(pre, curr, post) \
	((((u32)(pre)) << \
			PCIE_CFG_REG_PL102_GEN3_EQ_PRE_CURSOR_PSET_SHIFT) \
	| (((u32)(curr)) << PCIE_CFG_REG_PL102_GEN3_EQ_CURSOR_PSET_SHIFT) \
	| (((u32)(post)) << \
		PCIE_CFG_REG_PL102_GEN3_EQ_POST_CURSOR_PSET_SHIFT))

/*
 * Load the given EQ preset table पूर्णांकo the PCIe hardware.
 */
अटल पूर्णांक load_eq_table(काष्ठा hfi1_devdata *dd, स्थिर u8 eq[11][3], u8 fs,
			 u8 भाग)
अणु
	काष्ठा pci_dev *pdev = dd->pcidev;
	u32 hit_error = 0;
	u32 violation;
	u32 i;
	u8 c_minus1, c0, c_plus1;
	पूर्णांक ret;

	क्रम (i = 0; i < 11; i++) अणु
		/* set index */
		pci_ग_लिखो_config_dword(pdev, PCIE_CFG_REG_PL103, i);
		/* ग_लिखो the value */
		c_minus1 = eq[i][PREC] / भाग;
		c0 = fs - (eq[i][PREC] / भाग) - (eq[i][POST] / भाग);
		c_plus1 = eq[i][POST] / भाग;
		pci_ग_लिखो_config_dword(pdev, PCIE_CFG_REG_PL102,
				       eq_value(c_minus1, c0, c_plus1));
		/* check अगर these coefficients violate EQ rules */
		ret = pci_पढ़ो_config_dword(dd->pcidev,
					    PCIE_CFG_REG_PL105, &violation);
		अगर (ret) अणु
			dd_dev_err(dd, "Unable to read from PCI config\n");
			hit_error = 1;
			अवरोध;
		पूर्ण

		अगर (violation
		    & PCIE_CFG_REG_PL105_GEN3_EQ_VIOLATE_COEF_RULES_SMASK)अणु
			अगर (hit_error == 0) अणु
				dd_dev_err(dd,
					   "Gen3 EQ Table Coefficient rule violations\n");
				dd_dev_err(dd, "         prec   attn   post\n");
			पूर्ण
			dd_dev_err(dd, "   p%02d:   %02x     %02x     %02x\n",
				   i, (u32)eq[i][0], (u32)eq[i][1],
				   (u32)eq[i][2]);
			dd_dev_err(dd, "            %02x     %02x     %02x\n",
				   (u32)c_minus1, (u32)c0, (u32)c_plus1);
			hit_error = 1;
		पूर्ण
	पूर्ण
	अगर (hit_error)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * Steps to be करोne after the PCIe firmware is करोwnloaded and
 * beक्रमe the SBR क्रम the Pcie Gen3.
 * The SBus resource is alपढ़ोy being held.
 */
अटल व्योम pcie_post_steps(काष्ठा hfi1_devdata *dd)
अणु
	पूर्णांक i;

	set_sbus_fast_mode(dd);
	/*
	 * Write to the PCIe PCSes to set the G3_LOCKED_NEXT bits to 1.
	 * This aव्योमs a spurious framing error that can otherwise be
	 * generated by the MAC layer.
	 *
	 * Use inभागidual addresses since no broadcast is set up.
	 */
	क्रम (i = 0; i < NUM_PCIE_SERDES; i++) अणु
		sbus_request(dd, pcie_pcs_addrs[dd->hfi1_id][i],
			     0x03, WRITE_SBUS_RECEIVER, 0x00022132);
	पूर्ण

	clear_sbus_fast_mode(dd);
पूर्ण

/*
 * Trigger a secondary bus reset (SBR) on ourselves using our parent.
 *
 * Based on pci_parent_bus_reset() which is not exported by the
 * kernel core.
 */
अटल पूर्णांक trigger_sbr(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा pci_dev *dev = dd->pcidev;
	काष्ठा pci_dev *pdev;

	/* need a parent */
	अगर (!dev->bus->self) अणु
		dd_dev_err(dd, "%s: no parent device\n", __func__);
		वापस -ENOTTY;
	पूर्ण

	/* should not be anyone अन्यथा on the bus */
	list_क्रम_each_entry(pdev, &dev->bus->devices, bus_list)
		अगर (pdev != dev) अणु
			dd_dev_err(dd,
				   "%s: another device is on the same bus\n",
				   __func__);
			वापस -ENOTTY;
		पूर्ण

	/*
	 * This is an end around to करो an SBR during probe समय. A new API needs
	 * to be implemented to have cleaner पूर्णांकerface but this fixes the
	 * current brokenness
	 */
	वापस pci_bridge_secondary_bus_reset(dev->bus->self);
पूर्ण

/*
 * Write the given gasket पूर्णांकerrupt रेजिस्टर.
 */
अटल व्योम ग_लिखो_gasket_पूर्णांकerrupt(काष्ठा hfi1_devdata *dd, पूर्णांक index,
				   u16 code, u16 data)
अणु
	ग_लिखो_csr(dd, ASIC_PCIE_SD_INTRPT_LIST + (index * 8),
		  (((u64)code << ASIC_PCIE_SD_INTRPT_LIST_INTRPT_CODE_SHIFT) |
		   ((u64)data << ASIC_PCIE_SD_INTRPT_LIST_INTRPT_DATA_SHIFT)));
पूर्ण

/*
 * Tell the gasket logic how to react to the reset.
 */
अटल व्योम arm_gasket_logic(काष्ठा hfi1_devdata *dd)
अणु
	u64 reg;

	reg = (((u64)1 << dd->hfi1_id) <<
	       ASIC_PCIE_SD_HOST_CMD_INTRPT_CMD_SHIFT) |
	      ((u64)pcie_serdes_broadcast[dd->hfi1_id] <<
	       ASIC_PCIE_SD_HOST_CMD_SBUS_RCVR_ADDR_SHIFT |
	       ASIC_PCIE_SD_HOST_CMD_SBR_MODE_SMASK |
	       ((u64)SBR_DELAY_US & ASIC_PCIE_SD_HOST_CMD_TIMER_MASK) <<
	       ASIC_PCIE_SD_HOST_CMD_TIMER_SHIFT);
	ग_लिखो_csr(dd, ASIC_PCIE_SD_HOST_CMD, reg);
	/* पढ़ो back to push the ग_लिखो */
	पढ़ो_csr(dd, ASIC_PCIE_SD_HOST_CMD);
पूर्ण

/*
 * CCE_PCIE_CTRL दीर्घ name helpers
 * We redefine these लघुer macros to use in the code जबतक leaving
 * chip_रेजिस्टरs.h to be स्वतःgenerated from the hardware spec.
 */
#घोषणा LANE_BUNDLE_MASK              CCE_PCIE_CTRL_PCIE_LANE_BUNDLE_MASK
#घोषणा LANE_BUNDLE_SHIFT             CCE_PCIE_CTRL_PCIE_LANE_BUNDLE_SHIFT
#घोषणा LANE_DELAY_MASK               CCE_PCIE_CTRL_PCIE_LANE_DELAY_MASK
#घोषणा LANE_DELAY_SHIFT              CCE_PCIE_CTRL_PCIE_LANE_DELAY_SHIFT
#घोषणा MARGIN_OVERWRITE_ENABLE_SHIFT CCE_PCIE_CTRL_XMT_MARGIN_OVERWRITE_ENABLE_SHIFT
#घोषणा MARGIN_SHIFT                  CCE_PCIE_CTRL_XMT_MARGIN_SHIFT
#घोषणा MARGIN_G1_G2_OVERWRITE_MASK   CCE_PCIE_CTRL_XMT_MARGIN_GEN1_GEN2_OVERWRITE_ENABLE_MASK
#घोषणा MARGIN_G1_G2_OVERWRITE_SHIFT  CCE_PCIE_CTRL_XMT_MARGIN_GEN1_GEN2_OVERWRITE_ENABLE_SHIFT
#घोषणा MARGIN_GEN1_GEN2_MASK         CCE_PCIE_CTRL_XMT_MARGIN_GEN1_GEN2_MASK
#घोषणा MARGIN_GEN1_GEN2_SHIFT        CCE_PCIE_CTRL_XMT_MARGIN_GEN1_GEN2_SHIFT

 /*
  * Write xmt_margin क्रम full-swing (WFR-B) or half-swing (WFR-C).
  */
अटल व्योम ग_लिखो_xmt_margin(काष्ठा hfi1_devdata *dd, स्थिर अक्षर *fname)
अणु
	u64 pcie_ctrl;
	u64 xmt_margin;
	u64 xmt_margin_oe;
	u64 lane_delay;
	u64 lane_bundle;

	pcie_ctrl = पढ़ो_csr(dd, CCE_PCIE_CTRL);

	/*
	 * For Discrete, use full-swing.
	 *  - PCIe TX शेषs to full-swing.
	 *    Leave this रेजिस्टर as शेष.
	 * For Integrated, use half-swing
	 *  - Copy xmt_margin and xmt_margin_oe
	 *    from Gen1/Gen2 to Gen3.
	 */
	अगर (dd->pcidev->device == PCI_DEVICE_ID_INTEL1) अणु /* पूर्णांकegrated */
		/* extract initial fields */
		xmt_margin = (pcie_ctrl >> MARGIN_GEN1_GEN2_SHIFT)
			      & MARGIN_GEN1_GEN2_MASK;
		xmt_margin_oe = (pcie_ctrl >> MARGIN_G1_G2_OVERWRITE_SHIFT)
				 & MARGIN_G1_G2_OVERWRITE_MASK;
		lane_delay = (pcie_ctrl >> LANE_DELAY_SHIFT) & LANE_DELAY_MASK;
		lane_bundle = (pcie_ctrl >> LANE_BUNDLE_SHIFT)
			       & LANE_BUNDLE_MASK;

		/*
		 * For A0, EFUSE values are not set.  Override with the
		 * correct values.
		 */
		अगर (is_ax(dd)) अणु
			/*
			 * xmt_margin and OverwiteEnabel should be the
			 * same क्रम Gen1/Gen2 and Gen3
			 */
			xmt_margin = 0x5;
			xmt_margin_oe = 0x1;
			lane_delay = 0xF; /* Delay 240ns. */
			lane_bundle = 0x0; /* Set to 1 lane. */
		पूर्ण

		/* overग_लिखो existing values */
		pcie_ctrl = (xmt_margin << MARGIN_GEN1_GEN2_SHIFT)
			| (xmt_margin_oe << MARGIN_G1_G2_OVERWRITE_SHIFT)
			| (xmt_margin << MARGIN_SHIFT)
			| (xmt_margin_oe << MARGIN_OVERWRITE_ENABLE_SHIFT)
			| (lane_delay << LANE_DELAY_SHIFT)
			| (lane_bundle << LANE_BUNDLE_SHIFT);

		ग_लिखो_csr(dd, CCE_PCIE_CTRL, pcie_ctrl);
	पूर्ण

	dd_dev_dbg(dd, "%s: program XMT margin, CcePcieCtrl 0x%llx\n",
		   fname, pcie_ctrl);
पूर्ण

/*
 * Do all the steps needed to transition the PCIe link to Gen3 speed.
 */
पूर्णांक करो_pcie_gen3_transition(काष्ठा hfi1_devdata *dd)
अणु
	काष्ठा pci_dev *parent = dd->pcidev->bus->self;
	u64 fw_ctrl;
	u64 reg, therm;
	u32 reg32, fs, lf;
	u32 status, err;
	पूर्णांक ret;
	पूर्णांक करो_retry, retry_count = 0;
	पूर्णांक पूर्णांकnum = 0;
	uपूर्णांक शेष_pset;
	uपूर्णांक pset = pcie_pset;
	u16 target_vector, target_speed;
	u16 lnkctl2, venकरोr;
	u8 भाग;
	स्थिर u8 (*eq)[3];
	स्थिर u8 (*ctle_tunings)[4];
	uपूर्णांक अटल_ctle_mode;
	पूर्णांक वापस_error = 0;
	u32 target_width;

	/* PCIe Gen3 is क्रम the ASIC only */
	अगर (dd->icode != ICODE_RTL_SILICON)
		वापस 0;

	अगर (pcie_target == 1) अणु			/* target Gen1 */
		target_vector = PCI_EXP_LNKCTL2_TLS_2_5GT;
		target_speed = 2500;
	पूर्ण अन्यथा अगर (pcie_target == 2) अणु		/* target Gen2 */
		target_vector = PCI_EXP_LNKCTL2_TLS_5_0GT;
		target_speed = 5000;
	पूर्ण अन्यथा अगर (pcie_target == 3) अणु		/* target Gen3 */
		target_vector = PCI_EXP_LNKCTL2_TLS_8_0GT;
		target_speed = 8000;
	पूर्ण अन्यथा अणु
		/* off or invalid target - skip */
		dd_dev_info(dd, "%s: Skipping PCIe transition\n", __func__);
		वापस 0;
	पूर्ण

	/* अगर alपढ़ोy at target speed, करोne (unless क्रमced) */
	अगर (dd->lbus_speed == target_speed) अणु
		dd_dev_info(dd, "%s: PCIe already at gen%d, %s\n", __func__,
			    pcie_target,
			    pcie_क्रमce ? "re-doing anyway" : "skipping");
		अगर (!pcie_क्रमce)
			वापस 0;
	पूर्ण

	/*
	 * The driver cannot करो the transition अगर it has no access to the
	 * upstream component
	 */
	अगर (!parent) अणु
		dd_dev_info(dd, "%s: No upstream, Can't do gen3 transition\n",
			    __func__);
		वापस 0;
	पूर्ण

	/* Previous Gen1/Gen2 bus width */
	target_width = dd->lbus_width;

	/*
	 * Do the Gen3 transition.  Steps are those of the PCIe Gen3
	 * recipe.
	 */

	/* step 1: pcie link working in gen1/gen2 */

	/* step 2: अगर either side is not capable of Gen3, करोne */
	अगर (pcie_target == 3 && !dd->link_gen3_capable) अणु
		dd_dev_err(dd, "The PCIe link is not Gen3 capable\n");
		ret = -ENOSYS;
		जाओ करोne_no_mutex;
	पूर्ण

	/* hold the SBus resource across the firmware करोwnload and SBR */
	ret = acquire_chip_resource(dd, CR_SBUS, SBUS_TIMEOUT);
	अगर (ret) अणु
		dd_dev_err(dd, "%s: unable to acquire SBus resource\n",
			   __func__);
		वापस ret;
	पूर्ण

	/* make sure thermal polling is not causing पूर्णांकerrupts */
	therm = पढ़ो_csr(dd, ASIC_CFG_THERM_POLL_EN);
	अगर (therm) अणु
		ग_लिखो_csr(dd, ASIC_CFG_THERM_POLL_EN, 0x0);
		msleep(100);
		dd_dev_info(dd, "%s: Disabled therm polling\n",
			    __func__);
	पूर्ण

retry:
	/* the SBus करोwnload will reset the spico क्रम thermal */

	/* step 3: करोwnload SBus Master firmware */
	/* step 4: करोwnload PCIe Gen3 SerDes firmware */
	dd_dev_info(dd, "%s: downloading firmware\n", __func__);
	ret = load_pcie_firmware(dd);
	अगर (ret) अणु
		/* करो not proceed अगर the firmware cannot be करोwnloaded */
		वापस_error = 1;
		जाओ करोne;
	पूर्ण

	/* step 5: set up device parameter settings */
	dd_dev_info(dd, "%s: setting PCIe registers\n", __func__);

	/*
	 * PcieCfgSpcie1 - Link Control 3
	 * Leave at reset value.  No need to set PerfEq - link equalization
	 * will be perक्रमmed स्वतःmatically after the SBR when the target
	 * speed is 8GT/s.
	 */

	/* clear all 16 per-lane error bits (PCIe: Lane Error Status) */
	pci_ग_लिखो_config_dword(dd->pcidev, PCIE_CFG_SPCIE2, 0xffff);

	/* step 5a: Set Synopsys Port Logic रेजिस्टरs */

	/*
	 * PcieCfgRegPl2 - Port Force Link
	 *
	 * Set the low घातer field to 0x10 to aव्योम unnecessary घातer
	 * management messages.  All other fields are zero.
	 */
	reg32 = 0x10ul << PCIE_CFG_REG_PL2_LOW_PWR_ENT_CNT_SHIFT;
	pci_ग_लिखो_config_dword(dd->pcidev, PCIE_CFG_REG_PL2, reg32);

	/*
	 * PcieCfgRegPl100 - Gen3 Control
	 *
	 * turn off PcieCfgRegPl100.Gen3ZRxDcNonCompl
	 * turn on PcieCfgRegPl100.EqEieosCnt
	 * Everything अन्यथा zero.
	 */
	reg32 = PCIE_CFG_REG_PL100_EQ_EIEOS_CNT_SMASK;
	pci_ग_लिखो_config_dword(dd->pcidev, PCIE_CFG_REG_PL100, reg32);

	/*
	 * PcieCfgRegPl101 - Gen3 EQ FS and LF
	 * PcieCfgRegPl102 - Gen3 EQ Presets to Coefficients Mapping
	 * PcieCfgRegPl103 - Gen3 EQ Preset Index
	 * PcieCfgRegPl105 - Gen3 EQ Status
	 *
	 * Give initial EQ settings.
	 */
	अगर (dd->pcidev->device == PCI_DEVICE_ID_INTEL0) अणु /* discrete */
		/* 1000mV, FS=24, LF = 8 */
		fs = 24;
		lf = 8;
		भाग = 3;
		eq = discrete_preliminary_eq;
		शेष_pset = DEFAULT_DISCRETE_PSET;
		ctle_tunings = discrete_ctle_tunings;
		/* bit 0 - discrete on/off */
		अटल_ctle_mode = pcie_ctle & 0x1;
	पूर्ण अन्यथा अणु
		/* 400mV, FS=29, LF = 9 */
		fs = 29;
		lf = 9;
		भाग = 1;
		eq = पूर्णांकegrated_preliminary_eq;
		शेष_pset = DEFAULT_MCP_PSET;
		ctle_tunings = पूर्णांकegrated_ctle_tunings;
		/* bit 1 - पूर्णांकegrated on/off */
		अटल_ctle_mode = (pcie_ctle >> 1) & 0x1;
	पूर्ण
	pci_ग_लिखो_config_dword(dd->pcidev, PCIE_CFG_REG_PL101,
			       (fs <<
				PCIE_CFG_REG_PL101_GEN3_EQ_LOCAL_FS_SHIFT) |
			       (lf <<
				PCIE_CFG_REG_PL101_GEN3_EQ_LOCAL_LF_SHIFT));
	ret = load_eq_table(dd, eq, fs, भाग);
	अगर (ret)
		जाओ करोne;

	/*
	 * PcieCfgRegPl106 - Gen3 EQ Control
	 *
	 * Set Gen3EqPsetReqVec, leave other fields 0.
	 */
	अगर (pset == UNSET_PSET)
		pset = शेष_pset;
	अगर (pset > 10) अणु	/* valid range is 0-10, inclusive */
		dd_dev_err(dd, "%s: Invalid Eq Pset %u, setting to %d\n",
			   __func__, pset, शेष_pset);
		pset = शेष_pset;
	पूर्ण
	dd_dev_info(dd, "%s: using EQ Pset %u\n", __func__, pset);
	pci_ग_लिखो_config_dword(dd->pcidev, PCIE_CFG_REG_PL106,
			       ((1 << pset) <<
			PCIE_CFG_REG_PL106_GEN3_EQ_PSET_REQ_VEC_SHIFT) |
			PCIE_CFG_REG_PL106_GEN3_EQ_EVAL2MS_DISABLE_SMASK |
			PCIE_CFG_REG_PL106_GEN3_EQ_PHASE23_EXIT_MODE_SMASK);

	/*
	 * step 5b: Do post firmware करोwnload steps via SBus
	 */
	dd_dev_info(dd, "%s: doing pcie post steps\n", __func__);
	pcie_post_steps(dd);

	/*
	 * step 5c: Program gasket पूर्णांकerrupts
	 */
	/* set the Rx Bit Rate to REFCLK ratio */
	ग_लिखो_gasket_पूर्णांकerrupt(dd, पूर्णांकnum++, 0x0006, 0x0050);
	/* disable pCal क्रम PCIe Gen3 RX equalization */
	/* select adaptive or अटल CTLE */
	ग_लिखो_gasket_पूर्णांकerrupt(dd, पूर्णांकnum++, 0x0026,
			       0x5b01 | (अटल_ctle_mode << 3));
	/*
	 * Enable iCal क्रम PCIe Gen3 RX equalization, and set which
	 * evaluation of RX_EQ_EVAL will launch the iCal procedure.
	 */
	ग_लिखो_gasket_पूर्णांकerrupt(dd, पूर्णांकnum++, 0x0026, 0x5202);

	अगर (अटल_ctle_mode) अणु
		/* apply अटल CTLE tunings */
		u8 pcie_dc, pcie_lf, pcie_hf, pcie_bw;

		pcie_dc = ctle_tunings[pset][0];
		pcie_lf = ctle_tunings[pset][1];
		pcie_hf = ctle_tunings[pset][2];
		pcie_bw = ctle_tunings[pset][3];
		ग_लिखो_gasket_पूर्णांकerrupt(dd, पूर्णांकnum++, 0x0026, 0x0200 | pcie_dc);
		ग_लिखो_gasket_पूर्णांकerrupt(dd, पूर्णांकnum++, 0x0026, 0x0100 | pcie_lf);
		ग_लिखो_gasket_पूर्णांकerrupt(dd, पूर्णांकnum++, 0x0026, 0x0000 | pcie_hf);
		ग_लिखो_gasket_पूर्णांकerrupt(dd, पूर्णांकnum++, 0x0026, 0x5500 | pcie_bw);
	पूर्ण

	/* terminate list */
	ग_लिखो_gasket_पूर्णांकerrupt(dd, पूर्णांकnum++, 0x0000, 0x0000);

	/*
	 * step 5d: program XMT margin
	 */
	ग_लिखो_xmt_margin(dd, __func__);

	/*
	 * step 5e: disable active state घातer management (ASPM). It
	 * will be enabled अगर required later
	 */
	dd_dev_info(dd, "%s: clearing ASPM\n", __func__);
	aspm_hw_disable_l1(dd);

	/*
	 * step 5f: clear DirectSpeedChange
	 * PcieCfgRegPl67.DirectSpeedChange must be zero to prevent the
	 * change in the speed target from starting beक्रमe we are पढ़ोy.
	 * This field शेषs to 0 and we are not changing it, so nothing
	 * needs to be करोne.
	 */

	/* step 5g: Set target link speed */
	/*
	 * Set target link speed to be target on both device and parent.
	 * On setting the parent: Some प्रणाली BIOSs "helpfully" set the
	 * parent target speed to Gen2 to match the ASIC's initial speed.
	 * We can set the target Gen3 because we have alपढ़ोy checked
	 * that it is Gen3 capable earlier.
	 */
	dd_dev_info(dd, "%s: setting parent target link speed\n", __func__);
	ret = pcie_capability_पढ़ो_word(parent, PCI_EXP_LNKCTL2, &lnkctl2);
	अगर (ret) अणु
		dd_dev_err(dd, "Unable to read from PCI config\n");
		वापस_error = 1;
		जाओ करोne;
	पूर्ण

	dd_dev_info(dd, "%s: ..old link control2: 0x%x\n", __func__,
		    (u32)lnkctl2);
	/* only ग_लिखो to parent अगर target is not as high as ours */
	अगर ((lnkctl2 & PCI_EXP_LNKCTL2_TLS) < target_vector) अणु
		lnkctl2 &= ~PCI_EXP_LNKCTL2_TLS;
		lnkctl2 |= target_vector;
		dd_dev_info(dd, "%s: ..new link control2: 0x%x\n", __func__,
			    (u32)lnkctl2);
		ret = pcie_capability_ग_लिखो_word(parent,
						 PCI_EXP_LNKCTL2, lnkctl2);
		अगर (ret) अणु
			dd_dev_err(dd, "Unable to write to PCI config\n");
			वापस_error = 1;
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अणु
		dd_dev_info(dd, "%s: ..target speed is OK\n", __func__);
	पूर्ण

	dd_dev_info(dd, "%s: setting target link speed\n", __func__);
	ret = pcie_capability_पढ़ो_word(dd->pcidev, PCI_EXP_LNKCTL2, &lnkctl2);
	अगर (ret) अणु
		dd_dev_err(dd, "Unable to read from PCI config\n");
		वापस_error = 1;
		जाओ करोne;
	पूर्ण

	dd_dev_info(dd, "%s: ..old link control2: 0x%x\n", __func__,
		    (u32)lnkctl2);
	lnkctl2 &= ~PCI_EXP_LNKCTL2_TLS;
	lnkctl2 |= target_vector;
	dd_dev_info(dd, "%s: ..new link control2: 0x%x\n", __func__,
		    (u32)lnkctl2);
	ret = pcie_capability_ग_लिखो_word(dd->pcidev, PCI_EXP_LNKCTL2, lnkctl2);
	अगर (ret) अणु
		dd_dev_err(dd, "Unable to write to PCI config\n");
		वापस_error = 1;
		जाओ करोne;
	पूर्ण

	/* step 5h: arm gasket logic */
	/* hold DC in reset across the SBR */
	ग_लिखो_csr(dd, CCE_DC_CTRL, CCE_DC_CTRL_DC_RESET_SMASK);
	(व्योम)पढ़ो_csr(dd, CCE_DC_CTRL); /* DC reset hold */
	/* save firmware control across the SBR */
	fw_ctrl = पढ़ो_csr(dd, MISC_CFG_FW_CTRL);

	dd_dev_info(dd, "%s: arming gasket logic\n", __func__);
	arm_gasket_logic(dd);

	/*
	 * step 6: quiesce PCIe link
	 * The chip has alपढ़ोy been reset, so there will be no traffic
	 * from the chip.  Linux has no easy way to enक्रमce that it will
	 * not try to access the device, so we just need to hope it करोesn't
	 * करो it जबतक we are करोing the reset.
	 */

	/*
	 * step 7: initiate the secondary bus reset (SBR)
	 * step 8: hardware brings the links back up
	 * step 9: रुको क्रम link speed transition to be complete
	 */
	dd_dev_info(dd, "%s: calling trigger_sbr\n", __func__);
	ret = trigger_sbr(dd);
	अगर (ret)
		जाओ करोne;

	/* step 10: decide what to करो next */

	/* check अगर we can पढ़ो PCI space */
	ret = pci_पढ़ो_config_word(dd->pcidev, PCI_VENDOR_ID, &venकरोr);
	अगर (ret) अणु
		dd_dev_info(dd,
			    "%s: read of VendorID failed after SBR, err %d\n",
			    __func__, ret);
		वापस_error = 1;
		जाओ करोne;
	पूर्ण
	अगर (venकरोr == 0xffff) अणु
		dd_dev_info(dd, "%s: VendorID is all 1s after SBR\n", __func__);
		वापस_error = 1;
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	/* restore PCI space रेजिस्टरs we know were reset */
	dd_dev_info(dd, "%s: calling restore_pci_variables\n", __func__);
	ret = restore_pci_variables(dd);
	अगर (ret) अणु
		dd_dev_err(dd, "%s: Could not restore PCI variables\n",
			   __func__);
		वापस_error = 1;
		जाओ करोne;
	पूर्ण

	/* restore firmware control */
	ग_लिखो_csr(dd, MISC_CFG_FW_CTRL, fw_ctrl);

	/*
	 * Check the gasket block status.
	 *
	 * This is the first CSR पढ़ो after the SBR.  If the पढ़ो वापसs
	 * all 1s (fails), the link did not make it back.
	 *
	 * Once we're sure we can पढ़ो and ग_लिखो, clear the DC reset after
	 * the SBR.  Then check क्रम any per-lane errors. Then look over
	 * the status.
	 */
	reg = पढ़ो_csr(dd, ASIC_PCIE_SD_HOST_STATUS);
	dd_dev_info(dd, "%s: gasket block status: 0x%llx\n", __func__, reg);
	अगर (reg == ~0ull) अणु	/* PCIe पढ़ो failed/समयout */
		dd_dev_err(dd, "SBR failed - unable to read from device\n");
		वापस_error = 1;
		ret = -ENOSYS;
		जाओ करोne;
	पूर्ण

	/* clear the DC reset */
	ग_लिखो_csr(dd, CCE_DC_CTRL, 0);

	/* Set the LED off */
	setextled(dd, 0);

	/* check क्रम any per-lane errors */
	ret = pci_पढ़ो_config_dword(dd->pcidev, PCIE_CFG_SPCIE2, &reg32);
	अगर (ret) अणु
		dd_dev_err(dd, "Unable to read from PCI config\n");
		वापस_error = 1;
		जाओ करोne;
	पूर्ण

	dd_dev_info(dd, "%s: per-lane errors: 0x%x\n", __func__, reg32);

	/* extract status, look क्रम our HFI */
	status = (reg >> ASIC_PCIE_SD_HOST_STATUS_FW_DNLD_STS_SHIFT)
			& ASIC_PCIE_SD_HOST_STATUS_FW_DNLD_STS_MASK;
	अगर ((status & (1 << dd->hfi1_id)) == 0) अणु
		dd_dev_err(dd,
			   "%s: gasket status 0x%x, expecting 0x%x\n",
			   __func__, status, 1 << dd->hfi1_id);
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	/* extract error */
	err = (reg >> ASIC_PCIE_SD_HOST_STATUS_FW_DNLD_ERR_SHIFT)
		& ASIC_PCIE_SD_HOST_STATUS_FW_DNLD_ERR_MASK;
	अगर (err) अणु
		dd_dev_err(dd, "%s: gasket error %d\n", __func__, err);
		ret = -EIO;
		जाओ करोne;
	पूर्ण

	/* update our link inक्रमmation cache */
	update_lbus_info(dd);
	dd_dev_info(dd, "%s: new speed and width: %s\n", __func__,
		    dd->lbus_info);

	अगर (dd->lbus_speed != target_speed ||
	    dd->lbus_width < target_width) अणु /* not target */
		/* maybe retry */
		करो_retry = retry_count < pcie_retry;
		dd_dev_err(dd, "PCIe link speed or width did not match target%s\n",
			   करो_retry ? ", retrying" : "");
		retry_count++;
		अगर (करो_retry) अणु
			msleep(100); /* allow समय to settle */
			जाओ retry;
		पूर्ण
		ret = -EIO;
	पूर्ण

करोne:
	अगर (therm) अणु
		ग_लिखो_csr(dd, ASIC_CFG_THERM_POLL_EN, 0x1);
		msleep(100);
		dd_dev_info(dd, "%s: Re-enable therm polling\n",
			    __func__);
	पूर्ण
	release_chip_resource(dd, CR_SBUS);
करोne_no_mutex:
	/* वापस no error अगर it is OK to be at current speed */
	अगर (ret && !वापस_error) अणु
		dd_dev_err(dd, "Proceeding at current speed PCIe speed\n");
		ret = 0;
	पूर्ण

	dd_dev_info(dd, "%s: done\n", __func__);
	वापस ret;
पूर्ण
