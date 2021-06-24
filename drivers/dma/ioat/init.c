<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel I/OAT DMA Linux driver
 * Copyright(c) 2004 - 2015 Intel Corporation.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/dca.h>
#समावेश <linux/aer.h>
#समावेश <linux/sizes.h>
#समावेश "dma.h"
#समावेश "registers.h"
#समावेश "hw.h"

#समावेश "../dmaengine.h"

MODULE_VERSION(IOAT_DMA_VERSION);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Intel Corporation");

अटल स्थिर काष्ठा pci_device_id ioat_pci_tbl[] = अणु
	/* I/OAT v3 platक्रमms */
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_TBG0) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_TBG1) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_TBG2) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_TBG3) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_TBG4) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_TBG5) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_TBG6) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_TBG7) पूर्ण,

	/* I/OAT v3.2 platक्रमms */
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_JSF0) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_JSF1) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_JSF2) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_JSF3) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_JSF4) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_JSF5) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_JSF6) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_JSF7) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_JSF8) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_JSF9) पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SNB0) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SNB1) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SNB2) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SNB3) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SNB4) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SNB5) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SNB6) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SNB7) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SNB8) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SNB9) पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_IVB0) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_IVB1) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_IVB2) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_IVB3) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_IVB4) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_IVB5) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_IVB6) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_IVB7) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_IVB8) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_IVB9) पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_HSW0) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_HSW1) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_HSW2) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_HSW3) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_HSW4) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_HSW5) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_HSW6) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_HSW7) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_HSW8) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_HSW9) पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDX0) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDX1) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDX2) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDX3) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDX4) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDX5) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDX6) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDX7) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDX8) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDX9) पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_SKX) पूर्ण,

	/* I/OAT v3.3 platक्रमms */
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BWD0) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BWD1) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BWD2) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BWD3) पूर्ण,

	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDXDE0) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDXDE1) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDXDE2) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_BDXDE3) पूर्ण,

	/* I/OAT v3.4 platक्रमms */
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_IOAT_ICX) पूर्ण,

	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ioat_pci_tbl);

अटल पूर्णांक ioat_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id);
अटल व्योम ioat_हटाओ(काष्ठा pci_dev *pdev);
अटल व्योम
ioat_init_channel(काष्ठा ioatdma_device *ioat_dma,
		  काष्ठा ioatdma_chan *ioat_chan, पूर्णांक idx);
अटल व्योम ioat_पूर्णांकr_quirk(काष्ठा ioatdma_device *ioat_dma);
अटल व्योम ioat_क्रमागतerate_channels(काष्ठा ioatdma_device *ioat_dma);
अटल पूर्णांक ioat3_dma_self_test(काष्ठा ioatdma_device *ioat_dma);

अटल पूर्णांक ioat_dca_enabled = 1;
module_param(ioat_dca_enabled, पूर्णांक, 0644);
MODULE_PARM_DESC(ioat_dca_enabled, "control support of dca service (default: 1)");
पूर्णांक ioat_pending_level = 7;
module_param(ioat_pending_level, पूर्णांक, 0644);
MODULE_PARM_DESC(ioat_pending_level,
		 "high-water mark for pushing ioat descriptors (default: 7)");
अटल अक्षर ioat_पूर्णांकerrupt_style[32] = "msix";
module_param_string(ioat_पूर्णांकerrupt_style, ioat_पूर्णांकerrupt_style,
		    माप(ioat_पूर्णांकerrupt_style), 0644);
MODULE_PARM_DESC(ioat_पूर्णांकerrupt_style,
		 "set ioat interrupt style: msix (default), msi, intx");

काष्ठा kmem_cache *ioat_cache;
काष्ठा kmem_cache *ioat_sed_cache;

अटल bool is_jf_ioat(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_IOAT_JSF0:
	हाल PCI_DEVICE_ID_INTEL_IOAT_JSF1:
	हाल PCI_DEVICE_ID_INTEL_IOAT_JSF2:
	हाल PCI_DEVICE_ID_INTEL_IOAT_JSF3:
	हाल PCI_DEVICE_ID_INTEL_IOAT_JSF4:
	हाल PCI_DEVICE_ID_INTEL_IOAT_JSF5:
	हाल PCI_DEVICE_ID_INTEL_IOAT_JSF6:
	हाल PCI_DEVICE_ID_INTEL_IOAT_JSF7:
	हाल PCI_DEVICE_ID_INTEL_IOAT_JSF8:
	हाल PCI_DEVICE_ID_INTEL_IOAT_JSF9:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_snb_ioat(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_IOAT_SNB0:
	हाल PCI_DEVICE_ID_INTEL_IOAT_SNB1:
	हाल PCI_DEVICE_ID_INTEL_IOAT_SNB2:
	हाल PCI_DEVICE_ID_INTEL_IOAT_SNB3:
	हाल PCI_DEVICE_ID_INTEL_IOAT_SNB4:
	हाल PCI_DEVICE_ID_INTEL_IOAT_SNB5:
	हाल PCI_DEVICE_ID_INTEL_IOAT_SNB6:
	हाल PCI_DEVICE_ID_INTEL_IOAT_SNB7:
	हाल PCI_DEVICE_ID_INTEL_IOAT_SNB8:
	हाल PCI_DEVICE_ID_INTEL_IOAT_SNB9:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_ivb_ioat(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_IOAT_IVB0:
	हाल PCI_DEVICE_ID_INTEL_IOAT_IVB1:
	हाल PCI_DEVICE_ID_INTEL_IOAT_IVB2:
	हाल PCI_DEVICE_ID_INTEL_IOAT_IVB3:
	हाल PCI_DEVICE_ID_INTEL_IOAT_IVB4:
	हाल PCI_DEVICE_ID_INTEL_IOAT_IVB5:
	हाल PCI_DEVICE_ID_INTEL_IOAT_IVB6:
	हाल PCI_DEVICE_ID_INTEL_IOAT_IVB7:
	हाल PCI_DEVICE_ID_INTEL_IOAT_IVB8:
	हाल PCI_DEVICE_ID_INTEL_IOAT_IVB9:
		वापस true;
	शेष:
		वापस false;
	पूर्ण

पूर्ण

अटल bool is_hsw_ioat(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_IOAT_HSW0:
	हाल PCI_DEVICE_ID_INTEL_IOAT_HSW1:
	हाल PCI_DEVICE_ID_INTEL_IOAT_HSW2:
	हाल PCI_DEVICE_ID_INTEL_IOAT_HSW3:
	हाल PCI_DEVICE_ID_INTEL_IOAT_HSW4:
	हाल PCI_DEVICE_ID_INTEL_IOAT_HSW5:
	हाल PCI_DEVICE_ID_INTEL_IOAT_HSW6:
	हाल PCI_DEVICE_ID_INTEL_IOAT_HSW7:
	हाल PCI_DEVICE_ID_INTEL_IOAT_HSW8:
	हाल PCI_DEVICE_ID_INTEL_IOAT_HSW9:
		वापस true;
	शेष:
		वापस false;
	पूर्ण

पूर्ण

अटल bool is_bdx_ioat(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDX0:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDX1:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDX2:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDX3:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDX4:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDX5:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDX6:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDX7:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDX8:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDX9:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत bool is_skx_ioat(काष्ठा pci_dev *pdev)
अणु
	वापस (pdev->device == PCI_DEVICE_ID_INTEL_IOAT_SKX) ? true : false;
पूर्ण

अटल bool is_xeon_cb32(काष्ठा pci_dev *pdev)
अणु
	वापस is_jf_ioat(pdev) || is_snb_ioat(pdev) || is_ivb_ioat(pdev) ||
		is_hsw_ioat(pdev) || is_bdx_ioat(pdev) || is_skx_ioat(pdev);
पूर्ण

bool is_bwd_ioat(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_IOAT_BWD0:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BWD1:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BWD2:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BWD3:
	/* even though not Atom, BDX-DE has same DMA silicon */
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDXDE0:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDXDE1:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDXDE2:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDXDE3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_bwd_noraid(काष्ठा pci_dev *pdev)
अणु
	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_IOAT_BWD2:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BWD3:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDXDE0:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDXDE1:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDXDE2:
	हाल PCI_DEVICE_ID_INTEL_IOAT_BDXDE3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण

पूर्ण

/*
 * Perक्रमm a IOAT transaction to verअगरy the HW works.
 */
#घोषणा IOAT_TEST_SIZE 2000

अटल व्योम ioat_dma_test_callback(व्योम *dma_async_param)
अणु
	काष्ठा completion *cmp = dma_async_param;

	complete(cmp);
पूर्ण

/**
 * ioat_dma_self_test - Perक्रमm a IOAT transaction to verअगरy the HW works.
 * @ioat_dma: dma device to be tested
 */
अटल पूर्णांक ioat_dma_self_test(काष्ठा ioatdma_device *ioat_dma)
अणु
	पूर्णांक i;
	u8 *src;
	u8 *dest;
	काष्ठा dma_device *dma = &ioat_dma->dma_dev;
	काष्ठा device *dev = &ioat_dma->pdev->dev;
	काष्ठा dma_chan *dma_chan;
	काष्ठा dma_async_tx_descriptor *tx;
	dma_addr_t dma_dest, dma_src;
	dma_cookie_t cookie;
	पूर्णांक err = 0;
	काष्ठा completion cmp;
	अचिन्हित दीर्घ पंचांगo;
	अचिन्हित दीर्घ flags;

	src = kzalloc(IOAT_TEST_SIZE, GFP_KERNEL);
	अगर (!src)
		वापस -ENOMEM;
	dest = kzalloc(IOAT_TEST_SIZE, GFP_KERNEL);
	अगर (!dest) अणु
		kमुक्त(src);
		वापस -ENOMEM;
	पूर्ण

	/* Fill in src buffer */
	क्रम (i = 0; i < IOAT_TEST_SIZE; i++)
		src[i] = (u8)i;

	/* Start copy, using first DMA channel */
	dma_chan = container_of(dma->channels.next, काष्ठा dma_chan,
				device_node);
	अगर (dma->device_alloc_chan_resources(dma_chan) < 1) अणु
		dev_err(dev, "selftest cannot allocate chan resource\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण

	dma_src = dma_map_single(dev, src, IOAT_TEST_SIZE, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, dma_src)) अणु
		dev_err(dev, "mapping src buffer failed\n");
		err = -ENOMEM;
		जाओ मुक्त_resources;
	पूर्ण
	dma_dest = dma_map_single(dev, dest, IOAT_TEST_SIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, dma_dest)) अणु
		dev_err(dev, "mapping dest buffer failed\n");
		err = -ENOMEM;
		जाओ unmap_src;
	पूर्ण
	flags = DMA_PREP_INTERRUPT;
	tx = ioat_dma->dma_dev.device_prep_dma_स_नकल(dma_chan, dma_dest,
						      dma_src, IOAT_TEST_SIZE,
						      flags);
	अगर (!tx) अणु
		dev_err(dev, "Self-test prep failed, disabling\n");
		err = -ENODEV;
		जाओ unmap_dma;
	पूर्ण

	async_tx_ack(tx);
	init_completion(&cmp);
	tx->callback = ioat_dma_test_callback;
	tx->callback_param = &cmp;
	cookie = tx->tx_submit(tx);
	अगर (cookie < 0) अणु
		dev_err(dev, "Self-test setup failed, disabling\n");
		err = -ENODEV;
		जाओ unmap_dma;
	पूर्ण
	dma->device_issue_pending(dma_chan);

	पंचांगo = रुको_क्रम_completion_समयout(&cmp, msecs_to_jअगरfies(3000));

	अगर (पंचांगo == 0 ||
	    dma->device_tx_status(dma_chan, cookie, शून्य)
					!= DMA_COMPLETE) अणु
		dev_err(dev, "Self-test copy timed out, disabling\n");
		err = -ENODEV;
		जाओ unmap_dma;
	पूर्ण
	अगर (स_भेद(src, dest, IOAT_TEST_SIZE)) अणु
		dev_err(dev, "Self-test copy failed compare, disabling\n");
		err = -ENODEV;
		जाओ unmap_dma;
	पूर्ण

unmap_dma:
	dma_unmap_single(dev, dma_dest, IOAT_TEST_SIZE, DMA_FROM_DEVICE);
unmap_src:
	dma_unmap_single(dev, dma_src, IOAT_TEST_SIZE, DMA_TO_DEVICE);
मुक्त_resources:
	dma->device_मुक्त_chan_resources(dma_chan);
out:
	kमुक्त(src);
	kमुक्त(dest);
	वापस err;
पूर्ण

/**
 * ioat_dma_setup_पूर्णांकerrupts - setup पूर्णांकerrupt handler
 * @ioat_dma: ioat dma device
 */
पूर्णांक ioat_dma_setup_पूर्णांकerrupts(काष्ठा ioatdma_device *ioat_dma)
अणु
	काष्ठा ioatdma_chan *ioat_chan;
	काष्ठा pci_dev *pdev = ioat_dma->pdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा msix_entry *msix;
	पूर्णांक i, j, msixcnt;
	पूर्णांक err = -EINVAL;
	u8 पूर्णांकrctrl = 0;

	अगर (!म_भेद(ioat_पूर्णांकerrupt_style, "msix"))
		जाओ msix;
	अगर (!म_भेद(ioat_पूर्णांकerrupt_style, "msi"))
		जाओ msi;
	अगर (!म_भेद(ioat_पूर्णांकerrupt_style, "intx"))
		जाओ पूर्णांकx;
	dev_err(dev, "invalid ioat_interrupt_style %s\n", ioat_पूर्णांकerrupt_style);
	जाओ err_no_irq;

msix:
	/* The number of MSI-X vectors should equal the number of channels */
	msixcnt = ioat_dma->dma_dev.chancnt;
	क्रम (i = 0; i < msixcnt; i++)
		ioat_dma->msix_entries[i].entry = i;

	err = pci_enable_msix_exact(pdev, ioat_dma->msix_entries, msixcnt);
	अगर (err)
		जाओ msi;

	क्रम (i = 0; i < msixcnt; i++) अणु
		msix = &ioat_dma->msix_entries[i];
		ioat_chan = ioat_chan_by_index(ioat_dma, i);
		err = devm_request_irq(dev, msix->vector,
				       ioat_dma_करो_पूर्णांकerrupt_msix, 0,
				       "ioat-msix", ioat_chan);
		अगर (err) अणु
			क्रम (j = 0; j < i; j++) अणु
				msix = &ioat_dma->msix_entries[j];
				ioat_chan = ioat_chan_by_index(ioat_dma, j);
				devm_मुक्त_irq(dev, msix->vector, ioat_chan);
			पूर्ण
			जाओ msi;
		पूर्ण
	पूर्ण
	पूर्णांकrctrl |= IOAT_INTRCTRL_MSIX_VECTOR_CONTROL;
	ioat_dma->irq_mode = IOAT_MSIX;
	जाओ करोne;

msi:
	err = pci_enable_msi(pdev);
	अगर (err)
		जाओ पूर्णांकx;

	err = devm_request_irq(dev, pdev->irq, ioat_dma_करो_पूर्णांकerrupt, 0,
			       "ioat-msi", ioat_dma);
	अगर (err) अणु
		pci_disable_msi(pdev);
		जाओ पूर्णांकx;
	पूर्ण
	ioat_dma->irq_mode = IOAT_MSI;
	जाओ करोne;

पूर्णांकx:
	err = devm_request_irq(dev, pdev->irq, ioat_dma_करो_पूर्णांकerrupt,
			       IRQF_SHARED, "ioat-intx", ioat_dma);
	अगर (err)
		जाओ err_no_irq;

	ioat_dma->irq_mode = IOAT_INTX;
करोne:
	अगर (is_bwd_ioat(pdev))
		ioat_पूर्णांकr_quirk(ioat_dma);
	पूर्णांकrctrl |= IOAT_INTRCTRL_MASTER_INT_EN;
	ग_लिखोb(पूर्णांकrctrl, ioat_dma->reg_base + IOAT_INTRCTRL_OFFSET);
	वापस 0;

err_no_irq:
	/* Disable all पूर्णांकerrupt generation */
	ग_लिखोb(0, ioat_dma->reg_base + IOAT_INTRCTRL_OFFSET);
	ioat_dma->irq_mode = IOAT_NOIRQ;
	dev_err(dev, "no usable interrupts\n");
	वापस err;
पूर्ण

अटल व्योम ioat_disable_पूर्णांकerrupts(काष्ठा ioatdma_device *ioat_dma)
अणु
	/* Disable all पूर्णांकerrupt generation */
	ग_लिखोb(0, ioat_dma->reg_base + IOAT_INTRCTRL_OFFSET);
पूर्ण

अटल पूर्णांक ioat_probe(काष्ठा ioatdma_device *ioat_dma)
अणु
	पूर्णांक err = -ENODEV;
	काष्ठा dma_device *dma = &ioat_dma->dma_dev;
	काष्ठा pci_dev *pdev = ioat_dma->pdev;
	काष्ठा device *dev = &pdev->dev;

	ioat_dma->completion_pool = dma_pool_create("completion_pool", dev,
						    माप(u64),
						    SMP_CACHE_BYTES,
						    SMP_CACHE_BYTES);

	अगर (!ioat_dma->completion_pool) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	ioat_क्रमागतerate_channels(ioat_dma);

	dma_cap_set(DMA_MEMCPY, dma->cap_mask);
	dma->dev = &pdev->dev;

	अगर (!dma->chancnt) अणु
		dev_err(dev, "channel enumeration error\n");
		जाओ err_setup_पूर्णांकerrupts;
	पूर्ण

	err = ioat_dma_setup_पूर्णांकerrupts(ioat_dma);
	अगर (err)
		जाओ err_setup_पूर्णांकerrupts;

	err = ioat3_dma_self_test(ioat_dma);
	अगर (err)
		जाओ err_self_test;

	वापस 0;

err_self_test:
	ioat_disable_पूर्णांकerrupts(ioat_dma);
err_setup_पूर्णांकerrupts:
	dma_pool_destroy(ioat_dma->completion_pool);
err_out:
	वापस err;
पूर्ण

अटल पूर्णांक ioat_रेजिस्टर(काष्ठा ioatdma_device *ioat_dma)
अणु
	पूर्णांक err = dma_async_device_रेजिस्टर(&ioat_dma->dma_dev);

	अगर (err) अणु
		ioat_disable_पूर्णांकerrupts(ioat_dma);
		dma_pool_destroy(ioat_dma->completion_pool);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ioat_dma_हटाओ(काष्ठा ioatdma_device *ioat_dma)
अणु
	काष्ठा dma_device *dma = &ioat_dma->dma_dev;

	ioat_disable_पूर्णांकerrupts(ioat_dma);

	ioat_kobject_del(ioat_dma);

	dma_async_device_unरेजिस्टर(dma);
पूर्ण

/**
 * ioat_क्रमागतerate_channels - find and initialize the device's channels
 * @ioat_dma: the ioat dma device to be क्रमागतerated
 */
अटल व्योम ioat_क्रमागतerate_channels(काष्ठा ioatdma_device *ioat_dma)
अणु
	काष्ठा ioatdma_chan *ioat_chan;
	काष्ठा device *dev = &ioat_dma->pdev->dev;
	काष्ठा dma_device *dma = &ioat_dma->dma_dev;
	u8 xfercap_log;
	पूर्णांक i;

	INIT_LIST_HEAD(&dma->channels);
	dma->chancnt = पढ़ोb(ioat_dma->reg_base + IOAT_CHANCNT_OFFSET);
	dma->chancnt &= 0x1f; /* bits [4:0] valid */
	अगर (dma->chancnt > ARRAY_SIZE(ioat_dma->idx)) अणु
		dev_warn(dev, "(%d) exceeds max supported channels (%zu)\n",
			 dma->chancnt, ARRAY_SIZE(ioat_dma->idx));
		dma->chancnt = ARRAY_SIZE(ioat_dma->idx);
	पूर्ण
	xfercap_log = पढ़ोb(ioat_dma->reg_base + IOAT_XFERCAP_OFFSET);
	xfercap_log &= 0x1f; /* bits [4:0] valid */
	अगर (xfercap_log == 0)
		वापस;
	dev_dbg(dev, "%s: xfercap = %d\n", __func__, 1 << xfercap_log);

	क्रम (i = 0; i < dma->chancnt; i++) अणु
		ioat_chan = kzalloc(माप(*ioat_chan), GFP_KERNEL);
		अगर (!ioat_chan)
			अवरोध;

		ioat_init_channel(ioat_dma, ioat_chan, i);
		ioat_chan->xfercap_log = xfercap_log;
		spin_lock_init(&ioat_chan->prep_lock);
		अगर (ioat_reset_hw(ioat_chan)) अणु
			i = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	dma->chancnt = i;
पूर्ण

/**
 * ioat_मुक्त_chan_resources - release all the descriptors
 * @c: the channel to be cleaned
 */
अटल व्योम ioat_मुक्त_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
	काष्ठा ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	काष्ठा ioat_ring_ent *desc;
	स्थिर पूर्णांक total_descs = 1 << ioat_chan->alloc_order;
	पूर्णांक descs;
	पूर्णांक i;

	/* Beक्रमe मुक्तing channel resources first check
	 * अगर they have been previously allocated क्रम this channel.
	 */
	अगर (!ioat_chan->ring)
		वापस;

	ioat_stop(ioat_chan);

	अगर (!test_bit(IOAT_CHAN_DOWN, &ioat_chan->state)) अणु
		ioat_reset_hw(ioat_chan);

		/* Put LTR to idle */
		अगर (ioat_dma->version >= IOAT_VER_3_4)
			ग_लिखोb(IOAT_CHAN_LTR_SWSEL_IDLE,
			       ioat_chan->reg_base +
			       IOAT_CHAN_LTR_SWSEL_OFFSET);
	पूर्ण

	spin_lock_bh(&ioat_chan->cleanup_lock);
	spin_lock_bh(&ioat_chan->prep_lock);
	descs = ioat_ring_space(ioat_chan);
	dev_dbg(to_dev(ioat_chan), "freeing %d idle descriptors\n", descs);
	क्रम (i = 0; i < descs; i++) अणु
		desc = ioat_get_ring_ent(ioat_chan, ioat_chan->head + i);
		ioat_मुक्त_ring_ent(desc, c);
	पूर्ण

	अगर (descs < total_descs)
		dev_err(to_dev(ioat_chan), "Freeing %d in use descriptors!\n",
			total_descs - descs);

	क्रम (i = 0; i < total_descs - descs; i++) अणु
		desc = ioat_get_ring_ent(ioat_chan, ioat_chan->tail + i);
		dump_desc_dbg(ioat_chan, desc);
		ioat_मुक्त_ring_ent(desc, c);
	पूर्ण

	क्रम (i = 0; i < ioat_chan->desc_chunks; i++) अणु
		dma_मुक्त_coherent(to_dev(ioat_chan), IOAT_CHUNK_SIZE,
				  ioat_chan->descs[i].virt,
				  ioat_chan->descs[i].hw);
		ioat_chan->descs[i].virt = शून्य;
		ioat_chan->descs[i].hw = 0;
	पूर्ण
	ioat_chan->desc_chunks = 0;

	kमुक्त(ioat_chan->ring);
	ioat_chan->ring = शून्य;
	ioat_chan->alloc_order = 0;
	dma_pool_मुक्त(ioat_dma->completion_pool, ioat_chan->completion,
		      ioat_chan->completion_dma);
	spin_unlock_bh(&ioat_chan->prep_lock);
	spin_unlock_bh(&ioat_chan->cleanup_lock);

	ioat_chan->last_completion = 0;
	ioat_chan->completion_dma = 0;
	ioat_chan->dmacount = 0;
पूर्ण

/* ioat_alloc_chan_resources - allocate/initialize ioat descriptor ring
 * @chan: channel to be initialized
 */
अटल पूर्णांक ioat_alloc_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा ioatdma_chan *ioat_chan = to_ioat_chan(c);
	काष्ठा ioat_ring_ent **ring;
	u64 status;
	पूर्णांक order;
	पूर्णांक i = 0;
	u32 chanerr;

	/* have we alपढ़ोy been set up? */
	अगर (ioat_chan->ring)
		वापस 1 << ioat_chan->alloc_order;

	/* Setup रेजिस्टर to पूर्णांकerrupt and ग_लिखो completion status on error */
	ग_लिखोw(IOAT_CHANCTRL_RUN, ioat_chan->reg_base + IOAT_CHANCTRL_OFFSET);

	/* allocate a completion ग_लिखोback area */
	/* करोing 2 32bit ग_लिखोs to mmio since 1 64b ग_लिखो करोesn't work */
	ioat_chan->completion =
		dma_pool_zalloc(ioat_chan->ioat_dma->completion_pool,
				GFP_NOWAIT, &ioat_chan->completion_dma);
	अगर (!ioat_chan->completion)
		वापस -ENOMEM;

	ग_लिखोl(((u64)ioat_chan->completion_dma) & 0x00000000FFFFFFFF,
	       ioat_chan->reg_base + IOAT_CHANCMP_OFFSET_LOW);
	ग_लिखोl(((u64)ioat_chan->completion_dma) >> 32,
	       ioat_chan->reg_base + IOAT_CHANCMP_OFFSET_HIGH);

	order = IOAT_MAX_ORDER;
	ring = ioat_alloc_ring(c, order, GFP_NOWAIT);
	अगर (!ring)
		वापस -ENOMEM;

	spin_lock_bh(&ioat_chan->cleanup_lock);
	spin_lock_bh(&ioat_chan->prep_lock);
	ioat_chan->ring = ring;
	ioat_chan->head = 0;
	ioat_chan->issued = 0;
	ioat_chan->tail = 0;
	ioat_chan->alloc_order = order;
	set_bit(IOAT_RUN, &ioat_chan->state);
	spin_unlock_bh(&ioat_chan->prep_lock);
	spin_unlock_bh(&ioat_chan->cleanup_lock);

	/* Setting up LTR values क्रम 3.4 or later */
	अगर (ioat_chan->ioat_dma->version >= IOAT_VER_3_4) अणु
		u32 lat_val;

		lat_val = IOAT_CHAN_LTR_ACTIVE_SNVAL |
			IOAT_CHAN_LTR_ACTIVE_SNLATSCALE |
			IOAT_CHAN_LTR_ACTIVE_SNREQMNT;
		ग_लिखोl(lat_val, ioat_chan->reg_base +
				IOAT_CHAN_LTR_ACTIVE_OFFSET);

		lat_val = IOAT_CHAN_LTR_IDLE_SNVAL |
			  IOAT_CHAN_LTR_IDLE_SNLATSCALE |
			  IOAT_CHAN_LTR_IDLE_SNREQMNT;
		ग_लिखोl(lat_val, ioat_chan->reg_base +
				IOAT_CHAN_LTR_IDLE_OFFSET);

		/* Select to active */
		ग_लिखोb(IOAT_CHAN_LTR_SWSEL_ACTIVE,
		       ioat_chan->reg_base +
		       IOAT_CHAN_LTR_SWSEL_OFFSET);
	पूर्ण

	ioat_start_null_desc(ioat_chan);

	/* check that we got off the ground */
	करो अणु
		udelay(1);
		status = ioat_chansts(ioat_chan);
	पूर्ण जबतक (i++ < 20 && !is_ioat_active(status) && !is_ioat_idle(status));

	अगर (is_ioat_active(status) || is_ioat_idle(status))
		वापस 1 << ioat_chan->alloc_order;

	chanerr = पढ़ोl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);

	dev_WARN(to_dev(ioat_chan),
		 "failed to start channel chanerr: %#x\n", chanerr);
	ioat_मुक्त_chan_resources(c);
	वापस -EFAULT;
पूर्ण

/* common channel initialization */
अटल व्योम
ioat_init_channel(काष्ठा ioatdma_device *ioat_dma,
		  काष्ठा ioatdma_chan *ioat_chan, पूर्णांक idx)
अणु
	काष्ठा dma_device *dma = &ioat_dma->dma_dev;

	ioat_chan->ioat_dma = ioat_dma;
	ioat_chan->reg_base = ioat_dma->reg_base + (0x80 * (idx + 1));
	spin_lock_init(&ioat_chan->cleanup_lock);
	ioat_chan->dma_chan.device = dma;
	dma_cookie_init(&ioat_chan->dma_chan);
	list_add_tail(&ioat_chan->dma_chan.device_node, &dma->channels);
	ioat_dma->idx[idx] = ioat_chan;
	समयr_setup(&ioat_chan->समयr, ioat_समयr_event, 0);
	tasklet_setup(&ioat_chan->cleanup_task, ioat_cleanup_event);
पूर्ण

#घोषणा IOAT_NUM_SRC_TEST 6 /* must be <= 8 */
अटल पूर्णांक ioat_xor_val_self_test(काष्ठा ioatdma_device *ioat_dma)
अणु
	पूर्णांक i, src_idx;
	काष्ठा page *dest;
	काष्ठा page *xor_srcs[IOAT_NUM_SRC_TEST];
	काष्ठा page *xor_val_srcs[IOAT_NUM_SRC_TEST + 1];
	dma_addr_t dma_srcs[IOAT_NUM_SRC_TEST + 1];
	dma_addr_t dest_dma;
	काष्ठा dma_async_tx_descriptor *tx;
	काष्ठा dma_chan *dma_chan;
	dma_cookie_t cookie;
	u8 cmp_byte = 0;
	u32 cmp_word;
	u32 xor_val_result;
	पूर्णांक err = 0;
	काष्ठा completion cmp;
	अचिन्हित दीर्घ पंचांगo;
	काष्ठा device *dev = &ioat_dma->pdev->dev;
	काष्ठा dma_device *dma = &ioat_dma->dma_dev;
	u8 op = 0;

	dev_dbg(dev, "%s\n", __func__);

	अगर (!dma_has_cap(DMA_XOR, dma->cap_mask))
		वापस 0;

	क्रम (src_idx = 0; src_idx < IOAT_NUM_SRC_TEST; src_idx++) अणु
		xor_srcs[src_idx] = alloc_page(GFP_KERNEL);
		अगर (!xor_srcs[src_idx]) अणु
			जबतक (src_idx--)
				__मुक्त_page(xor_srcs[src_idx]);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	dest = alloc_page(GFP_KERNEL);
	अगर (!dest) अणु
		जबतक (src_idx--)
			__मुक्त_page(xor_srcs[src_idx]);
		वापस -ENOMEM;
	पूर्ण

	/* Fill in src buffers */
	क्रम (src_idx = 0; src_idx < IOAT_NUM_SRC_TEST; src_idx++) अणु
		u8 *ptr = page_address(xor_srcs[src_idx]);

		क्रम (i = 0; i < PAGE_SIZE; i++)
			ptr[i] = (1 << src_idx);
	पूर्ण

	क्रम (src_idx = 0; src_idx < IOAT_NUM_SRC_TEST; src_idx++)
		cmp_byte ^= (u8) (1 << src_idx);

	cmp_word = (cmp_byte << 24) | (cmp_byte << 16) |
			(cmp_byte << 8) | cmp_byte;

	स_रखो(page_address(dest), 0, PAGE_SIZE);

	dma_chan = container_of(dma->channels.next, काष्ठा dma_chan,
				device_node);
	अगर (dma->device_alloc_chan_resources(dma_chan) < 1) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	/* test xor */
	op = IOAT_OP_XOR;

	dest_dma = dma_map_page(dev, dest, 0, PAGE_SIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, dest_dma)) अणु
		err = -ENOMEM;
		जाओ मुक्त_resources;
	पूर्ण

	क्रम (i = 0; i < IOAT_NUM_SRC_TEST; i++) अणु
		dma_srcs[i] = dma_map_page(dev, xor_srcs[i], 0, PAGE_SIZE,
					   DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, dma_srcs[i])) अणु
			err = -ENOMEM;
			जाओ dma_unmap;
		पूर्ण
	पूर्ण
	tx = dma->device_prep_dma_xor(dma_chan, dest_dma, dma_srcs,
				      IOAT_NUM_SRC_TEST, PAGE_SIZE,
				      DMA_PREP_INTERRUPT);

	अगर (!tx) अणु
		dev_err(dev, "Self-test xor prep failed\n");
		err = -ENODEV;
		जाओ dma_unmap;
	पूर्ण

	async_tx_ack(tx);
	init_completion(&cmp);
	tx->callback = ioat_dma_test_callback;
	tx->callback_param = &cmp;
	cookie = tx->tx_submit(tx);
	अगर (cookie < 0) अणु
		dev_err(dev, "Self-test xor setup failed\n");
		err = -ENODEV;
		जाओ dma_unmap;
	पूर्ण
	dma->device_issue_pending(dma_chan);

	पंचांगo = रुको_क्रम_completion_समयout(&cmp, msecs_to_jअगरfies(3000));

	अगर (पंचांगo == 0 ||
	    dma->device_tx_status(dma_chan, cookie, शून्य) != DMA_COMPLETE) अणु
		dev_err(dev, "Self-test xor timed out\n");
		err = -ENODEV;
		जाओ dma_unmap;
	पूर्ण

	क्रम (i = 0; i < IOAT_NUM_SRC_TEST; i++)
		dma_unmap_page(dev, dma_srcs[i], PAGE_SIZE, DMA_TO_DEVICE);

	dma_sync_single_क्रम_cpu(dev, dest_dma, PAGE_SIZE, DMA_FROM_DEVICE);
	क्रम (i = 0; i < (PAGE_SIZE / माप(u32)); i++) अणु
		u32 *ptr = page_address(dest);

		अगर (ptr[i] != cmp_word) अणु
			dev_err(dev, "Self-test xor failed compare\n");
			err = -ENODEV;
			जाओ मुक्त_resources;
		पूर्ण
	पूर्ण
	dma_sync_single_क्रम_device(dev, dest_dma, PAGE_SIZE, DMA_FROM_DEVICE);

	dma_unmap_page(dev, dest_dma, PAGE_SIZE, DMA_FROM_DEVICE);

	/* skip validate अगर the capability is not present */
	अगर (!dma_has_cap(DMA_XOR_VAL, dma_chan->device->cap_mask))
		जाओ मुक्त_resources;

	op = IOAT_OP_XOR_VAL;

	/* validate the sources with the destपूर्णांकation page */
	क्रम (i = 0; i < IOAT_NUM_SRC_TEST; i++)
		xor_val_srcs[i] = xor_srcs[i];
	xor_val_srcs[i] = dest;

	xor_val_result = 1;

	क्रम (i = 0; i < IOAT_NUM_SRC_TEST + 1; i++) अणु
		dma_srcs[i] = dma_map_page(dev, xor_val_srcs[i], 0, PAGE_SIZE,
					   DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, dma_srcs[i])) अणु
			err = -ENOMEM;
			जाओ dma_unmap;
		पूर्ण
	पूर्ण
	tx = dma->device_prep_dma_xor_val(dma_chan, dma_srcs,
					  IOAT_NUM_SRC_TEST + 1, PAGE_SIZE,
					  &xor_val_result, DMA_PREP_INTERRUPT);
	अगर (!tx) अणु
		dev_err(dev, "Self-test zero prep failed\n");
		err = -ENODEV;
		जाओ dma_unmap;
	पूर्ण

	async_tx_ack(tx);
	init_completion(&cmp);
	tx->callback = ioat_dma_test_callback;
	tx->callback_param = &cmp;
	cookie = tx->tx_submit(tx);
	अगर (cookie < 0) अणु
		dev_err(dev, "Self-test zero setup failed\n");
		err = -ENODEV;
		जाओ dma_unmap;
	पूर्ण
	dma->device_issue_pending(dma_chan);

	पंचांगo = रुको_क्रम_completion_समयout(&cmp, msecs_to_jअगरfies(3000));

	अगर (पंचांगo == 0 ||
	    dma->device_tx_status(dma_chan, cookie, शून्य) != DMA_COMPLETE) अणु
		dev_err(dev, "Self-test validate timed out\n");
		err = -ENODEV;
		जाओ dma_unmap;
	पूर्ण

	क्रम (i = 0; i < IOAT_NUM_SRC_TEST + 1; i++)
		dma_unmap_page(dev, dma_srcs[i], PAGE_SIZE, DMA_TO_DEVICE);

	अगर (xor_val_result != 0) अणु
		dev_err(dev, "Self-test validate failed compare\n");
		err = -ENODEV;
		जाओ मुक्त_resources;
	पूर्ण

	स_रखो(page_address(dest), 0, PAGE_SIZE);

	/* test क्रम non-zero parity sum */
	op = IOAT_OP_XOR_VAL;

	xor_val_result = 0;
	क्रम (i = 0; i < IOAT_NUM_SRC_TEST + 1; i++) अणु
		dma_srcs[i] = dma_map_page(dev, xor_val_srcs[i], 0, PAGE_SIZE,
					   DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, dma_srcs[i])) अणु
			err = -ENOMEM;
			जाओ dma_unmap;
		पूर्ण
	पूर्ण
	tx = dma->device_prep_dma_xor_val(dma_chan, dma_srcs,
					  IOAT_NUM_SRC_TEST + 1, PAGE_SIZE,
					  &xor_val_result, DMA_PREP_INTERRUPT);
	अगर (!tx) अणु
		dev_err(dev, "Self-test 2nd zero prep failed\n");
		err = -ENODEV;
		जाओ dma_unmap;
	पूर्ण

	async_tx_ack(tx);
	init_completion(&cmp);
	tx->callback = ioat_dma_test_callback;
	tx->callback_param = &cmp;
	cookie = tx->tx_submit(tx);
	अगर (cookie < 0) अणु
		dev_err(dev, "Self-test  2nd zero setup failed\n");
		err = -ENODEV;
		जाओ dma_unmap;
	पूर्ण
	dma->device_issue_pending(dma_chan);

	पंचांगo = रुको_क्रम_completion_समयout(&cmp, msecs_to_jअगरfies(3000));

	अगर (पंचांगo == 0 ||
	    dma->device_tx_status(dma_chan, cookie, शून्य) != DMA_COMPLETE) अणु
		dev_err(dev, "Self-test 2nd validate timed out\n");
		err = -ENODEV;
		जाओ dma_unmap;
	पूर्ण

	अगर (xor_val_result != SUM_CHECK_P_RESULT) अणु
		dev_err(dev, "Self-test validate failed compare\n");
		err = -ENODEV;
		जाओ dma_unmap;
	पूर्ण

	क्रम (i = 0; i < IOAT_NUM_SRC_TEST + 1; i++)
		dma_unmap_page(dev, dma_srcs[i], PAGE_SIZE, DMA_TO_DEVICE);

	जाओ मुक्त_resources;
dma_unmap:
	अगर (op == IOAT_OP_XOR) अणु
		जबतक (--i >= 0)
			dma_unmap_page(dev, dma_srcs[i], PAGE_SIZE,
				       DMA_TO_DEVICE);
		dma_unmap_page(dev, dest_dma, PAGE_SIZE, DMA_FROM_DEVICE);
	पूर्ण अन्यथा अगर (op == IOAT_OP_XOR_VAL) अणु
		जबतक (--i >= 0)
			dma_unmap_page(dev, dma_srcs[i], PAGE_SIZE,
				       DMA_TO_DEVICE);
	पूर्ण
मुक्त_resources:
	dma->device_मुक्त_chan_resources(dma_chan);
out:
	src_idx = IOAT_NUM_SRC_TEST;
	जबतक (src_idx--)
		__मुक्त_page(xor_srcs[src_idx]);
	__मुक्त_page(dest);
	वापस err;
पूर्ण

अटल पूर्णांक ioat3_dma_self_test(काष्ठा ioatdma_device *ioat_dma)
अणु
	पूर्णांक rc;

	rc = ioat_dma_self_test(ioat_dma);
	अगर (rc)
		वापस rc;

	rc = ioat_xor_val_self_test(ioat_dma);

	वापस rc;
पूर्ण

अटल व्योम ioat_पूर्णांकr_quirk(काष्ठा ioatdma_device *ioat_dma)
अणु
	काष्ठा dma_device *dma;
	काष्ठा dma_chan *c;
	काष्ठा ioatdma_chan *ioat_chan;
	u32 errmask;

	dma = &ioat_dma->dma_dev;

	/*
	 * अगर we have descriptor ग_लिखो back error status, we mask the
	 * error पूर्णांकerrupts
	 */
	अगर (ioat_dma->cap & IOAT_CAP_DWBES) अणु
		list_क्रम_each_entry(c, &dma->channels, device_node) अणु
			ioat_chan = to_ioat_chan(c);
			errmask = पढ़ोl(ioat_chan->reg_base +
					IOAT_CHANERR_MASK_OFFSET);
			errmask |= IOAT_CHANERR_XOR_P_OR_CRC_ERR |
				   IOAT_CHANERR_XOR_Q_ERR;
			ग_लिखोl(errmask, ioat_chan->reg_base +
					IOAT_CHANERR_MASK_OFFSET);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ioat3_dma_probe(काष्ठा ioatdma_device *ioat_dma, पूर्णांक dca)
अणु
	काष्ठा pci_dev *pdev = ioat_dma->pdev;
	पूर्णांक dca_en = प्रणाली_has_dca_enabled(pdev);
	काष्ठा dma_device *dma;
	काष्ठा dma_chan *c;
	काष्ठा ioatdma_chan *ioat_chan;
	पूर्णांक err;
	u16 val16;

	dma = &ioat_dma->dma_dev;
	dma->device_prep_dma_स_नकल = ioat_dma_prep_स_नकल_lock;
	dma->device_issue_pending = ioat_issue_pending;
	dma->device_alloc_chan_resources = ioat_alloc_chan_resources;
	dma->device_मुक्त_chan_resources = ioat_मुक्त_chan_resources;

	dma_cap_set(DMA_INTERRUPT, dma->cap_mask);
	dma->device_prep_dma_पूर्णांकerrupt = ioat_prep_पूर्णांकerrupt_lock;

	ioat_dma->cap = पढ़ोl(ioat_dma->reg_base + IOAT_DMA_CAP_OFFSET);

	अगर (is_xeon_cb32(pdev) || is_bwd_noraid(pdev))
		ioat_dma->cap &=
			~(IOAT_CAP_XOR | IOAT_CAP_PQ | IOAT_CAP_RAID16SS);

	/* dca is incompatible with raid operations */
	अगर (dca_en && (ioat_dma->cap & (IOAT_CAP_XOR|IOAT_CAP_PQ)))
		ioat_dma->cap &= ~(IOAT_CAP_XOR|IOAT_CAP_PQ);

	अगर (ioat_dma->cap & IOAT_CAP_XOR) अणु
		dma->max_xor = 8;

		dma_cap_set(DMA_XOR, dma->cap_mask);
		dma->device_prep_dma_xor = ioat_prep_xor;

		dma_cap_set(DMA_XOR_VAL, dma->cap_mask);
		dma->device_prep_dma_xor_val = ioat_prep_xor_val;
	पूर्ण

	अगर (ioat_dma->cap & IOAT_CAP_PQ) अणु

		dma->device_prep_dma_pq = ioat_prep_pq;
		dma->device_prep_dma_pq_val = ioat_prep_pq_val;
		dma_cap_set(DMA_PQ, dma->cap_mask);
		dma_cap_set(DMA_PQ_VAL, dma->cap_mask);

		अगर (ioat_dma->cap & IOAT_CAP_RAID16SS)
			dma_set_maxpq(dma, 16, 0);
		अन्यथा
			dma_set_maxpq(dma, 8, 0);

		अगर (!(ioat_dma->cap & IOAT_CAP_XOR)) अणु
			dma->device_prep_dma_xor = ioat_prep_pqxor;
			dma->device_prep_dma_xor_val = ioat_prep_pqxor_val;
			dma_cap_set(DMA_XOR, dma->cap_mask);
			dma_cap_set(DMA_XOR_VAL, dma->cap_mask);

			अगर (ioat_dma->cap & IOAT_CAP_RAID16SS)
				dma->max_xor = 16;
			अन्यथा
				dma->max_xor = 8;
		पूर्ण
	पूर्ण

	dma->device_tx_status = ioat_tx_status;

	/* starting with CB3.3 super extended descriptors are supported */
	अगर (ioat_dma->cap & IOAT_CAP_RAID16SS) अणु
		अक्षर pool_name[14];
		पूर्णांक i;

		क्रम (i = 0; i < MAX_SED_POOLS; i++) अणु
			snम_लिखो(pool_name, 14, "ioat_hw%d_sed", i);

			/* allocate SED DMA pool */
			ioat_dma->sed_hw_pool[i] = dmam_pool_create(pool_name,
					&pdev->dev,
					SED_SIZE * (i + 1), 64, 0);
			अगर (!ioat_dma->sed_hw_pool[i])
				वापस -ENOMEM;

		पूर्ण
	पूर्ण

	अगर (!(ioat_dma->cap & (IOAT_CAP_XOR | IOAT_CAP_PQ)))
		dma_cap_set(DMA_PRIVATE, dma->cap_mask);

	err = ioat_probe(ioat_dma);
	अगर (err)
		वापस err;

	list_क्रम_each_entry(c, &dma->channels, device_node) अणु
		ioat_chan = to_ioat_chan(c);
		ग_लिखोl(IOAT_DMA_DCA_ANY_CPU,
		       ioat_chan->reg_base + IOAT_DCACTRL_OFFSET);
	पूर्ण

	err = ioat_रेजिस्टर(ioat_dma);
	अगर (err)
		वापस err;

	ioat_kobject_add(ioat_dma, &ioat_ktype);

	अगर (dca)
		ioat_dma->dca = ioat_dca_init(pdev, ioat_dma->reg_base);

	/* disable relaxed ordering */
	err = pcie_capability_पढ़ो_word(pdev, IOAT_DEVCTRL_OFFSET, &val16);
	अगर (err)
		वापस pcibios_err_to_त्रुटि_सं(err);

	/* clear relaxed ordering enable */
	val16 &= ~IOAT_DEVCTRL_ROE;
	err = pcie_capability_ग_लिखो_word(pdev, IOAT_DEVCTRL_OFFSET, val16);
	अगर (err)
		वापस pcibios_err_to_त्रुटि_सं(err);

	अगर (ioat_dma->cap & IOAT_CAP_DPS)
		ग_लिखोb(ioat_pending_level + 1,
		       ioat_dma->reg_base + IOAT_PREFETCH_LIMIT_OFFSET);

	वापस 0;
पूर्ण

अटल व्योम ioat_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ioatdma_device *ioat_dma = pci_get_drvdata(pdev);
	काष्ठा ioatdma_chan *ioat_chan;
	पूर्णांक i;

	अगर (!ioat_dma)
		वापस;

	क्रम (i = 0; i < IOAT_MAX_CHANS; i++) अणु
		ioat_chan = ioat_dma->idx[i];
		अगर (!ioat_chan)
			जारी;

		spin_lock_bh(&ioat_chan->prep_lock);
		set_bit(IOAT_CHAN_DOWN, &ioat_chan->state);
		spin_unlock_bh(&ioat_chan->prep_lock);
		/*
		 * Synchronization rule क्रम del_समयr_sync():
		 *  - The caller must not hold locks which would prevent
		 *    completion of the समयr's handler.
		 * So prep_lock cannot be held beक्रमe calling it.
		 */
		del_समयr_sync(&ioat_chan->समयr);

		/* this should quiesce then reset */
		ioat_reset_hw(ioat_chan);
	पूर्ण

	ioat_disable_पूर्णांकerrupts(ioat_dma);
पूर्ण

अटल व्योम ioat_resume(काष्ठा ioatdma_device *ioat_dma)
अणु
	काष्ठा ioatdma_chan *ioat_chan;
	u32 chanerr;
	पूर्णांक i;

	क्रम (i = 0; i < IOAT_MAX_CHANS; i++) अणु
		ioat_chan = ioat_dma->idx[i];
		अगर (!ioat_chan)
			जारी;

		spin_lock_bh(&ioat_chan->prep_lock);
		clear_bit(IOAT_CHAN_DOWN, &ioat_chan->state);
		spin_unlock_bh(&ioat_chan->prep_lock);

		chanerr = पढ़ोl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);
		ग_लिखोl(chanerr, ioat_chan->reg_base + IOAT_CHANERR_OFFSET);

		/* no need to reset as shutकरोwn alपढ़ोy did that */
	पूर्ण
पूर्ण

#घोषणा DRV_NAME "ioatdma"

अटल pci_ers_result_t ioat_pcie_error_detected(काष्ठा pci_dev *pdev,
						 pci_channel_state_t error)
अणु
	dev_dbg(&pdev->dev, "%s: PCIe AER error %d\n", DRV_NAME, error);

	/* quiesce and block I/O */
	ioat_shutकरोwn(pdev);

	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

अटल pci_ers_result_t ioat_pcie_error_slot_reset(काष्ठा pci_dev *pdev)
अणु
	pci_ers_result_t result = PCI_ERS_RESULT_RECOVERED;

	dev_dbg(&pdev->dev, "%s post reset handling\n", DRV_NAME);

	अगर (pci_enable_device_mem(pdev) < 0) अणु
		dev_err(&pdev->dev,
			"Failed to enable PCIe device after reset.\n");
		result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण अन्यथा अणु
		pci_set_master(pdev);
		pci_restore_state(pdev);
		pci_save_state(pdev);
		pci_wake_from_d3(pdev, false);
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम ioat_pcie_error_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ioatdma_device *ioat_dma = pci_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "%s: AER handling resuming\n", DRV_NAME);

	/* initialize and bring everything back */
	ioat_resume(ioat_dma);
पूर्ण

अटल स्थिर काष्ठा pci_error_handlers ioat_err_handler = अणु
	.error_detected = ioat_pcie_error_detected,
	.slot_reset = ioat_pcie_error_slot_reset,
	.resume = ioat_pcie_error_resume,
पूर्ण;

अटल काष्ठा pci_driver ioat_pci_driver = अणु
	.name		= DRV_NAME,
	.id_table	= ioat_pci_tbl,
	.probe		= ioat_pci_probe,
	.हटाओ		= ioat_हटाओ,
	.shutकरोwn	= ioat_shutकरोwn,
	.err_handler	= &ioat_err_handler,
पूर्ण;

अटल व्योम release_ioatdma(काष्ठा dma_device *device)
अणु
	काष्ठा ioatdma_device *d = to_ioatdma_device(device);
	पूर्णांक i;

	क्रम (i = 0; i < IOAT_MAX_CHANS; i++)
		kमुक्त(d->idx[i]);

	dma_pool_destroy(d->completion_pool);
	kमुक्त(d);
पूर्ण

अटल काष्ठा ioatdma_device *
alloc_ioatdma(काष्ठा pci_dev *pdev, व्योम __iomem *iobase)
अणु
	काष्ठा ioatdma_device *d = kzalloc(माप(*d), GFP_KERNEL);

	अगर (!d)
		वापस शून्य;
	d->pdev = pdev;
	d->reg_base = iobase;
	d->dma_dev.device_release = release_ioatdma;
	वापस d;
पूर्ण

अटल पूर्णांक ioat_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	व्योम __iomem * स्थिर *iomap;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ioatdma_device *device;
	पूर्णांक err;

	err = pcim_enable_device(pdev);
	अगर (err)
		वापस err;

	err = pcim_iomap_regions(pdev, 1 << IOAT_MMIO_BAR, DRV_NAME);
	अगर (err)
		वापस err;
	iomap = pcim_iomap_table(pdev);
	अगर (!iomap)
		वापस -ENOMEM;

	err = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err)
		err = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (err)
		वापस err;

	err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64));
	अगर (err)
		err = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	अगर (err)
		वापस err;

	device = alloc_ioatdma(pdev, iomap[IOAT_MMIO_BAR]);
	अगर (!device)
		वापस -ENOMEM;
	pci_set_master(pdev);
	pci_set_drvdata(pdev, device);

	device->version = पढ़ोb(device->reg_base + IOAT_VER_OFFSET);
	अगर (device->version >= IOAT_VER_3_4)
		ioat_dca_enabled = 0;
	अगर (device->version >= IOAT_VER_3_0) अणु
		अगर (is_skx_ioat(pdev))
			device->version = IOAT_VER_3_2;
		err = ioat3_dma_probe(device, ioat_dca_enabled);

		अगर (device->version >= IOAT_VER_3_3)
			pci_enable_pcie_error_reporting(pdev);
	पूर्ण अन्यथा
		वापस -ENODEV;

	अगर (err) अणु
		dev_err(dev, "Intel(R) I/OAT DMA Engine init failed\n");
		pci_disable_pcie_error_reporting(pdev);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ioat_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ioatdma_device *device = pci_get_drvdata(pdev);

	अगर (!device)
		वापस;

	ioat_shutकरोwn(pdev);

	dev_err(&pdev->dev, "Removing dma and dca services\n");
	अगर (device->dca) अणु
		unरेजिस्टर_dca_provider(device->dca, &pdev->dev);
		मुक्त_dca_provider(device->dca);
		device->dca = शून्य;
	पूर्ण

	pci_disable_pcie_error_reporting(pdev);
	ioat_dma_हटाओ(device);
पूर्ण

अटल पूर्णांक __init ioat_init_module(व्योम)
अणु
	पूर्णांक err = -ENOMEM;

	pr_info("%s: Intel(R) QuickData Technology Driver %s\n",
		DRV_NAME, IOAT_DMA_VERSION);

	ioat_cache = kmem_cache_create("ioat", माप(काष्ठा ioat_ring_ent),
					0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!ioat_cache)
		वापस -ENOMEM;

	ioat_sed_cache = KMEM_CACHE(ioat_sed_ent, 0);
	अगर (!ioat_sed_cache)
		जाओ err_ioat_cache;

	err = pci_रेजिस्टर_driver(&ioat_pci_driver);
	अगर (err)
		जाओ err_ioat3_cache;

	वापस 0;

 err_ioat3_cache:
	kmem_cache_destroy(ioat_sed_cache);

 err_ioat_cache:
	kmem_cache_destroy(ioat_cache);

	वापस err;
पूर्ण
module_init(ioat_init_module);

अटल व्योम __निकास ioat_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ioat_pci_driver);
	kmem_cache_destroy(ioat_cache);
पूर्ण
module_निकास(ioat_निकास_module);
