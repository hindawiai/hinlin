<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DMA translation between STA2x11 AMBA memory mapping and the x86 memory mapping
 *
 * ST Microelectronics ConneXt (STA2X11/STA2X10)
 *
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 */

#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/swiotlb.h>
#समावेश <यंत्र/iommu.h>

#घोषणा STA2X11_SWIOTLB_SIZE (4*1024*1024)

/*
 * We build a list of bus numbers that are under the ConneXt. The
 * मुख्य bridge hosts 4 busses, which are the 4 endpoपूर्णांकs, in order.
 */
#घोषणा STA2X11_NR_EP		4	/* 0..3 included */
#घोषणा STA2X11_NR_FUNCS	8	/* 0..7 included */
#घोषणा STA2X11_AMBA_SIZE	(512 << 20)

काष्ठा sta2x11_ahb_regs अणु /* saved during suspend */
	u32 base, pexlbase, pexhbase, crw;
पूर्ण;

काष्ठा sta2x11_mapping अणु
	पूर्णांक is_suspended;
	काष्ठा sta2x11_ahb_regs regs[STA2X11_NR_FUNCS];
पूर्ण;

काष्ठा sta2x11_instance अणु
	काष्ठा list_head list;
	पूर्णांक bus0;
	काष्ठा sta2x11_mapping map[STA2X11_NR_EP];
पूर्ण;

अटल LIST_HEAD(sta2x11_instance_list);

/* At probe समय, record new instances of this bridge (likely one only) */
अटल व्योम sta2x11_new_instance(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sta2x11_instance *instance;

	instance = kzalloc(माप(*instance), GFP_ATOMIC);
	अगर (!instance)
		वापस;
	/* This has a subordinate bridge, with 4 more-subordinate ones */
	instance->bus0 = pdev->subordinate->number + 1;

	अगर (list_empty(&sta2x11_instance_list)) अणु
		पूर्णांक size = STA2X11_SWIOTLB_SIZE;
		/* First instance: रेजिस्टर your own swiotlb area */
		dev_info(&pdev->dev, "Using SWIOTLB (size %i)\n", size);
		अगर (swiotlb_late_init_with_शेष_size(size))
			dev_emerg(&pdev->dev, "init swiotlb failed\n");
	पूर्ण
	list_add(&instance->list, &sta2x11_instance_list);
पूर्ण
DECLARE_PCI_FIXUP_ENABLE(PCI_VENDOR_ID_STMICRO, 0xcc17, sta2x11_new_instance);

/*
 * Utility functions used in this file from below
 */
अटल काष्ठा sta2x11_instance *sta2x11_pdev_to_instance(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sta2x11_instance *instance;
	पूर्णांक ep;

	list_क्रम_each_entry(instance, &sta2x11_instance_list, list) अणु
		ep = pdev->bus->number - instance->bus0;
		अगर (ep >= 0 && ep < STA2X11_NR_EP)
			वापस instance;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक sta2x11_pdev_to_ep(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sta2x11_instance *instance;

	instance = sta2x11_pdev_to_instance(pdev);
	अगर (!instance)
		वापस -1;

	वापस pdev->bus->number - instance->bus0;
पूर्ण

/* This is exported, as some devices need to access the MFD रेजिस्टरs */
काष्ठा sta2x11_instance *sta2x11_get_instance(काष्ठा pci_dev *pdev)
अणु
	वापस sta2x11_pdev_to_instance(pdev);
पूर्ण
EXPORT_SYMBOL(sta2x11_get_instance);

/* At setup समय, we use our own ops अगर the device is a ConneXt one */
अटल व्योम sta2x11_setup_pdev(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sta2x11_instance *instance = sta2x11_pdev_to_instance(pdev);

	अगर (!instance) /* either a sta2x11 bridge or another ST device */
		वापस;

	/* We must enable all devices as master, क्रम audio DMA to work */
	pci_set_master(pdev);
पूर्ण
DECLARE_PCI_FIXUP_ENABLE(PCI_VENDOR_ID_STMICRO, PCI_ANY_ID, sta2x11_setup_pdev);

/*
 * At boot we must set up the mappings क्रम the pcie-to-amba bridge.
 * It involves device access, and the same happens at suspend/resume समय
 */

#घोषणा AHB_MAPB		0xCA4
#घोषणा AHB_CRW(i)		(AHB_MAPB + 0  + (i) * 0x10)
#घोषणा AHB_CRW_SZMASK			0xfffffc00UL
#घोषणा AHB_CRW_ENABLE			(1 << 0)
#घोषणा AHB_CRW_WTYPE_MEM		(2 << 1)
#घोषणा AHB_CRW_ROE			(1UL << 3)	/* Relax Order Ena */
#घोषणा AHB_CRW_NSE			(1UL << 4)	/* No Snoop Enable */
#घोषणा AHB_BASE(i)		(AHB_MAPB + 4  + (i) * 0x10)
#घोषणा AHB_PEXLBASE(i)		(AHB_MAPB + 8  + (i) * 0x10)
#घोषणा AHB_PEXHBASE(i)		(AHB_MAPB + 12 + (i) * 0x10)

/* At probe समय, enable mapping क्रम each endpoपूर्णांक, using the pdev */
अटल व्योम sta2x11_map_ep(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sta2x11_instance *instance = sta2x11_pdev_to_instance(pdev);
	काष्ठा device *dev = &pdev->dev;
	u32 amba_base, max_amba_addr;
	पूर्णांक i, ret;

	अगर (!instance)
		वापस;

	pci_पढ़ो_config_dword(pdev, AHB_BASE(0), &amba_base);
	max_amba_addr = amba_base + STA2X11_AMBA_SIZE - 1;

	ret = dma_direct_set_offset(dev, 0, amba_base, STA2X11_AMBA_SIZE);
	अगर (ret)
		dev_err(dev, "sta2x11: could not set DMA offset\n");

	dev->bus_dma_limit = max_amba_addr;
	pci_set_consistent_dma_mask(pdev, max_amba_addr);
	pci_set_dma_mask(pdev, max_amba_addr);

	/* Configure AHB mapping */
	pci_ग_लिखो_config_dword(pdev, AHB_PEXLBASE(0), 0);
	pci_ग_लिखो_config_dword(pdev, AHB_PEXHBASE(0), 0);
	pci_ग_लिखो_config_dword(pdev, AHB_CRW(0), STA2X11_AMBA_SIZE |
			       AHB_CRW_WTYPE_MEM | AHB_CRW_ENABLE);

	/* Disable all the other winकरोws */
	क्रम (i = 1; i < STA2X11_NR_FUNCS; i++)
		pci_ग_लिखो_config_dword(pdev, AHB_CRW(i), 0);

	dev_info(&pdev->dev,
		 "sta2x11: Map EP %i: AMBA address %#8x-%#8x\n",
		 sta2x11_pdev_to_ep(pdev), amba_base, max_amba_addr);
पूर्ण
DECLARE_PCI_FIXUP_ENABLE(PCI_VENDOR_ID_STMICRO, PCI_ANY_ID, sta2x11_map_ep);

#अगर_घोषित CONFIG_PM /* Some रेजिस्टर values must be saved and restored */

अटल काष्ठा sta2x11_mapping *sta2x11_pdev_to_mapping(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sta2x11_instance *instance;
	पूर्णांक ep;

	instance = sta2x11_pdev_to_instance(pdev);
	अगर (!instance)
		वापस शून्य;
	ep = sta2x11_pdev_to_ep(pdev);
	वापस instance->map + ep;
पूर्ण

अटल व्योम suspend_mapping(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sta2x11_mapping *map = sta2x11_pdev_to_mapping(pdev);
	पूर्णांक i;

	अगर (!map)
		वापस;

	अगर (map->is_suspended)
		वापस;
	map->is_suspended = 1;

	/* Save all winकरोw configs */
	क्रम (i = 0; i < STA2X11_NR_FUNCS; i++) अणु
		काष्ठा sta2x11_ahb_regs *regs = map->regs + i;

		pci_पढ़ो_config_dword(pdev, AHB_BASE(i), &regs->base);
		pci_पढ़ो_config_dword(pdev, AHB_PEXLBASE(i), &regs->pexlbase);
		pci_पढ़ो_config_dword(pdev, AHB_PEXHBASE(i), &regs->pexhbase);
		pci_पढ़ो_config_dword(pdev, AHB_CRW(i), &regs->crw);
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_SUSPEND(PCI_VENDOR_ID_STMICRO, PCI_ANY_ID, suspend_mapping);

अटल व्योम resume_mapping(काष्ठा pci_dev *pdev)
अणु
	काष्ठा sta2x11_mapping *map = sta2x11_pdev_to_mapping(pdev);
	पूर्णांक i;

	अगर (!map)
		वापस;


	अगर (!map->is_suspended)
		जाओ out;
	map->is_suspended = 0;

	/* Restore all winकरोw configs */
	क्रम (i = 0; i < STA2X11_NR_FUNCS; i++) अणु
		काष्ठा sta2x11_ahb_regs *regs = map->regs + i;

		pci_ग_लिखो_config_dword(pdev, AHB_BASE(i), regs->base);
		pci_ग_लिखो_config_dword(pdev, AHB_PEXLBASE(i), regs->pexlbase);
		pci_ग_लिखो_config_dword(pdev, AHB_PEXHBASE(i), regs->pexhbase);
		pci_ग_लिखो_config_dword(pdev, AHB_CRW(i), regs->crw);
	पूर्ण
out:
	pci_set_master(pdev); /* Like at boot, enable master on all devices */
पूर्ण
DECLARE_PCI_FIXUP_RESUME(PCI_VENDOR_ID_STMICRO, PCI_ANY_ID, resume_mapping);

#पूर्ण_अगर /* CONFIG_PM */
