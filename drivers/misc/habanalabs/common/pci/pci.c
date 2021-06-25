<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश "../habanalabs.h"
#समावेश "../../include/hw_ip/pci/pci_general.h"

#समावेश <linux/pci.h>

#घोषणा HL_PLDM_PCI_ELBI_TIMEOUT_MSEC	(HL_PCI_ELBI_TIMEOUT_MSEC * 10)

#घोषणा IATU_REGION_CTRL_REGION_EN_MASK		BIT(31)
#घोषणा IATU_REGION_CTRL_MATCH_MODE_MASK	BIT(30)
#घोषणा IATU_REGION_CTRL_NUM_MATCH_EN_MASK	BIT(19)
#घोषणा IATU_REGION_CTRL_BAR_NUM_MASK		GENMASK(10, 8)

/**
 * hl_pci_bars_map() - Map PCI BARs.
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 * @name: Array of BAR names.
 * @is_wc: Array with flag per BAR whether a ग_लिखो-combined mapping is needed.
 *
 * Request PCI regions and map them to kernel भव addresses.
 *
 * Return: 0 on success, non-zero क्रम failure.
 */
पूर्णांक hl_pci_bars_map(काष्ठा hl_device *hdev, स्थिर अक्षर * स्थिर name[3],
			bool is_wc[3])
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	पूर्णांक rc, i, bar;

	rc = pci_request_regions(pdev, HL_NAME);
	अगर (rc) अणु
		dev_err(hdev->dev, "Cannot obtain PCI resources\n");
		वापस rc;
	पूर्ण

	क्रम (i = 0 ; i < 3 ; i++) अणु
		bar = i * 2; /* 64-bit BARs */
		hdev->pcie_bar[bar] = is_wc[i] ?
				pci_ioremap_wc_bar(pdev, bar) :
				pci_ioremap_bar(pdev, bar);
		अगर (!hdev->pcie_bar[bar]) अणु
			dev_err(hdev->dev, "pci_ioremap%s_bar failed for %s\n",
					is_wc[i] ? "_wc" : "", name[i]);
			rc = -ENODEV;
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	क्रम (i = 2 ; i >= 0 ; i--) अणु
		bar = i * 2; /* 64-bit BARs */
		अगर (hdev->pcie_bar[bar])
			iounmap(hdev->pcie_bar[bar]);
	पूर्ण

	pci_release_regions(pdev);

	वापस rc;
पूर्ण

/**
 * hl_pci_bars_unmap() - Unmap PCI BARS.
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 *
 * Release all PCI BARs and unmap their भव addresses.
 */
अटल व्योम hl_pci_bars_unmap(काष्ठा hl_device *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	पूर्णांक i, bar;

	क्रम (i = 2 ; i >= 0 ; i--) अणु
		bar = i * 2; /* 64-bit BARs */
		iounmap(hdev->pcie_bar[bar]);
	पूर्ण

	pci_release_regions(pdev);
पूर्ण

पूर्णांक hl_pci_elbi_पढ़ो(काष्ठा hl_device *hdev, u64 addr, u32 *data)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	kसमय_प्रकार समयout;
	u64 msec;
	u32 val;

	अगर (hdev->pldm)
		msec = HL_PLDM_PCI_ELBI_TIMEOUT_MSEC;
	अन्यथा
		msec = HL_PCI_ELBI_TIMEOUT_MSEC;

	/* Clear previous status */
	pci_ग_लिखो_config_dword(pdev, mmPCI_CONFIG_ELBI_STS, 0);

	pci_ग_लिखो_config_dword(pdev, mmPCI_CONFIG_ELBI_ADDR, (u32) addr);
	pci_ग_लिखो_config_dword(pdev, mmPCI_CONFIG_ELBI_CTRL, 0);

	समयout = kसमय_add_ms(kसमय_get(), msec);
	क्रम (;;) अणु
		pci_पढ़ो_config_dword(pdev, mmPCI_CONFIG_ELBI_STS, &val);
		अगर (val & PCI_CONFIG_ELBI_STS_MASK)
			अवरोध;
		अगर (kसमय_compare(kसमय_get(), समयout) > 0) अणु
			pci_पढ़ो_config_dword(pdev, mmPCI_CONFIG_ELBI_STS,
						&val);
			अवरोध;
		पूर्ण

		usleep_range(300, 500);
	पूर्ण

	अगर ((val & PCI_CONFIG_ELBI_STS_MASK) == PCI_CONFIG_ELBI_STS_DONE) अणु
		pci_पढ़ो_config_dword(pdev, mmPCI_CONFIG_ELBI_DATA, data);

		वापस 0;
	पूर्ण

	अगर (val & PCI_CONFIG_ELBI_STS_ERR) अणु
		dev_err(hdev->dev, "Error reading from ELBI\n");
		वापस -EIO;
	पूर्ण

	अगर (!(val & PCI_CONFIG_ELBI_STS_MASK)) अणु
		dev_err(hdev->dev, "ELBI read didn't finish in time\n");
		वापस -EIO;
	पूर्ण

	dev_err(hdev->dev, "ELBI read has undefined bits in status\n");
	वापस -EIO;
पूर्ण

/**
 * hl_pci_elbi_ग_लिखो() - Write through the ELBI पूर्णांकerface.
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 * @addr: Address to ग_लिखो to
 * @data: Data to ग_लिखो
 *
 * Return: 0 on success, negative value क्रम failure.
 */
अटल पूर्णांक hl_pci_elbi_ग_लिखो(काष्ठा hl_device *hdev, u64 addr, u32 data)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	kसमय_प्रकार समयout;
	u64 msec;
	u32 val;

	अगर (hdev->pldm)
		msec = HL_PLDM_PCI_ELBI_TIMEOUT_MSEC;
	अन्यथा
		msec = HL_PCI_ELBI_TIMEOUT_MSEC;

	/* Clear previous status */
	pci_ग_लिखो_config_dword(pdev, mmPCI_CONFIG_ELBI_STS, 0);

	pci_ग_लिखो_config_dword(pdev, mmPCI_CONFIG_ELBI_ADDR, (u32) addr);
	pci_ग_लिखो_config_dword(pdev, mmPCI_CONFIG_ELBI_DATA, data);
	pci_ग_लिखो_config_dword(pdev, mmPCI_CONFIG_ELBI_CTRL,
				PCI_CONFIG_ELBI_CTRL_WRITE);

	समयout = kसमय_add_ms(kसमय_get(), msec);
	क्रम (;;) अणु
		pci_पढ़ो_config_dword(pdev, mmPCI_CONFIG_ELBI_STS, &val);
		अगर (val & PCI_CONFIG_ELBI_STS_MASK)
			अवरोध;
		अगर (kसमय_compare(kसमय_get(), समयout) > 0) अणु
			pci_पढ़ो_config_dword(pdev, mmPCI_CONFIG_ELBI_STS,
						&val);
			अवरोध;
		पूर्ण

		usleep_range(300, 500);
	पूर्ण

	अगर ((val & PCI_CONFIG_ELBI_STS_MASK) == PCI_CONFIG_ELBI_STS_DONE)
		वापस 0;

	अगर (val & PCI_CONFIG_ELBI_STS_ERR)
		वापस -EIO;

	अगर (!(val & PCI_CONFIG_ELBI_STS_MASK)) अणु
		dev_err(hdev->dev, "ELBI write didn't finish in time\n");
		वापस -EIO;
	पूर्ण

	dev_err(hdev->dev, "ELBI write has undefined bits in status\n");
	वापस -EIO;
पूर्ण

/**
 * hl_pci_iatu_ग_लिखो() - iatu ग_लिखो routine.
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 * @addr: Address to ग_लिखो to
 * @data: Data to ग_लिखो
 *
 * Return: 0 on success, negative value क्रम failure.
 */
पूर्णांक hl_pci_iatu_ग_लिखो(काष्ठा hl_device *hdev, u32 addr, u32 data)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u32 dbi_offset;
	पूर्णांक rc;

	dbi_offset = addr & 0xFFF;

	/* Ignore result of writing to pcie_aux_dbi_reg_addr as it could fail
	 * in हाल the firmware security is enabled
	 */
	hl_pci_elbi_ग_लिखो(hdev, prop->pcie_aux_dbi_reg_addr, 0x00300000);

	rc = hl_pci_elbi_ग_लिखो(hdev, prop->pcie_dbi_base_address + dbi_offset,
				data);

	अगर (rc)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * hl_pci_reset_link_through_bridge() - Reset PCI link.
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 */
अटल व्योम hl_pci_reset_link_through_bridge(काष्ठा hl_device *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	काष्ठा pci_dev *parent_port;
	u16 val;

	parent_port = pdev->bus->self;
	pci_पढ़ो_config_word(parent_port, PCI_BRIDGE_CONTROL, &val);
	val |= PCI_BRIDGE_CTL_BUS_RESET;
	pci_ग_लिखो_config_word(parent_port, PCI_BRIDGE_CONTROL, val);
	ssleep(1);

	val &= ~(PCI_BRIDGE_CTL_BUS_RESET);
	pci_ग_लिखो_config_word(parent_port, PCI_BRIDGE_CONTROL, val);
	ssleep(3);
पूर्ण

/**
 * hl_pci_set_inbound_region() - Configure inbound region
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 * @region: Inbound region number.
 * @pci_region: Inbound region parameters.
 *
 * Configure the iATU inbound region.
 *
 * Return: 0 on success, negative value क्रम failure.
 */
पूर्णांक hl_pci_set_inbound_region(काष्ठा hl_device *hdev, u8 region,
		काष्ठा hl_inbound_pci_region *pci_region)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 bar_phys_base, region_base, region_end_address;
	u32 offset, ctrl_reg_val;
	पूर्णांक rc = 0;

	/* region offset */
	offset = (0x200 * region) + 0x100;

	अगर (pci_region->mode == PCI_ADDRESS_MATCH_MODE) अणु
		bar_phys_base = hdev->pcie_bar_phys[pci_region->bar];
		region_base = bar_phys_base + pci_region->offset_in_bar;
		region_end_address = region_base + pci_region->size - 1;

		rc |= hl_pci_iatu_ग_लिखो(hdev, offset + 0x8,
				lower_32_bits(region_base));
		rc |= hl_pci_iatu_ग_लिखो(hdev, offset + 0xC,
				upper_32_bits(region_base));
		rc |= hl_pci_iatu_ग_लिखो(hdev, offset + 0x10,
				lower_32_bits(region_end_address));
	पूर्ण

	/* Poपूर्णांक to the specअगरied address */
	rc |= hl_pci_iatu_ग_लिखो(hdev, offset + 0x14,
			lower_32_bits(pci_region->addr));
	rc |= hl_pci_iatu_ग_लिखो(hdev, offset + 0x18,
			upper_32_bits(pci_region->addr));
	rc |= hl_pci_iatu_ग_लिखो(hdev, offset + 0x0, 0);

	/* Enable + bar/address match + match enable + bar number */
	ctrl_reg_val = FIELD_PREP(IATU_REGION_CTRL_REGION_EN_MASK, 1);
	ctrl_reg_val |= FIELD_PREP(IATU_REGION_CTRL_MATCH_MODE_MASK,
			pci_region->mode);
	ctrl_reg_val |= FIELD_PREP(IATU_REGION_CTRL_NUM_MATCH_EN_MASK, 1);

	अगर (pci_region->mode == PCI_BAR_MATCH_MODE)
		ctrl_reg_val |= FIELD_PREP(IATU_REGION_CTRL_BAR_NUM_MASK,
				pci_region->bar);

	rc |= hl_pci_iatu_ग_लिखो(hdev, offset + 0x4, ctrl_reg_val);

	/* Return the DBI winकरोw to the शेष location
	 * Ignore result of writing to pcie_aux_dbi_reg_addr as it could fail
	 * in हाल the firmware security is enabled
	 */
	hl_pci_elbi_ग_लिखो(hdev, prop->pcie_aux_dbi_reg_addr, 0);

	अगर (rc)
		dev_err(hdev->dev, "failed to map bar %u to 0x%08llx\n",
				pci_region->bar, pci_region->addr);

	वापस rc;
पूर्ण

/**
 * hl_pci_set_outbound_region() - Configure outbound region 0
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 * @pci_region: Outbound region parameters.
 *
 * Configure the iATU outbound region 0.
 *
 * Return: 0 on success, negative value क्रम failure.
 */
पूर्णांक hl_pci_set_outbound_region(काष्ठा hl_device *hdev,
		काष्ठा hl_outbound_pci_region *pci_region)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	u64 outbound_region_end_address;
	पूर्णांक rc = 0;

	/* Outbound Region 0 */
	outbound_region_end_address =
			pci_region->addr + pci_region->size - 1;
	rc |= hl_pci_iatu_ग_लिखो(hdev, 0x008,
				lower_32_bits(pci_region->addr));
	rc |= hl_pci_iatu_ग_लिखो(hdev, 0x00C,
				upper_32_bits(pci_region->addr));
	rc |= hl_pci_iatu_ग_लिखो(hdev, 0x010,
				lower_32_bits(outbound_region_end_address));
	rc |= hl_pci_iatu_ग_लिखो(hdev, 0x014, 0);

	अगर ((hdev->घातer9_64bit_dma_enable) && (hdev->dma_mask == 64))
		rc |= hl_pci_iatu_ग_लिखो(hdev, 0x018, 0x08000000);
	अन्यथा
		rc |= hl_pci_iatu_ग_लिखो(hdev, 0x018, 0);

	rc |= hl_pci_iatu_ग_लिखो(hdev, 0x020,
				upper_32_bits(outbound_region_end_address));
	/* Increase region size */
	rc |= hl_pci_iatu_ग_लिखो(hdev, 0x000, 0x00002000);
	/* Enable */
	rc |= hl_pci_iatu_ग_लिखो(hdev, 0x004, 0x80000000);

	/* Return the DBI winकरोw to the शेष location
	 * Ignore result of writing to pcie_aux_dbi_reg_addr as it could fail
	 * in हाल the firmware security is enabled
	 */
	hl_pci_elbi_ग_लिखो(hdev, prop->pcie_aux_dbi_reg_addr, 0);

	वापस rc;
पूर्ण

/**
 * hl_pci_init() - PCI initialization code.
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure.
 *
 * Set DMA masks, initialize the PCI controller and map the PCI BARs.
 *
 * Return: 0 on success, non-zero क्रम failure.
 */
पूर्णांक hl_pci_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा pci_dev *pdev = hdev->pdev;
	पूर्णांक rc;

	अगर (hdev->reset_pcilink)
		hl_pci_reset_link_through_bridge(hdev);

	rc = pci_enable_device_mem(pdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "can't enable PCI device\n");
		वापस rc;
	पूर्ण

	pci_set_master(pdev);

	rc = hdev->asic_funcs->pci_bars_map(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to initialize PCI BARs\n");
		जाओ disable_device;
	पूर्ण

	rc = hdev->asic_funcs->init_iatu(hdev);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to initialize iATU\n");
		जाओ unmap_pci_bars;
	पूर्ण

	rc = dma_set_mask_and_coherent(&pdev->dev,
					DMA_BIT_MASK(hdev->dma_mask));
	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to set dma mask to %d bits, error %d\n",
			hdev->dma_mask, rc);
		जाओ unmap_pci_bars;
	पूर्ण

	वापस 0;

unmap_pci_bars:
	hl_pci_bars_unmap(hdev);
disable_device:
	pci_clear_master(pdev);
	pci_disable_device(pdev);

	वापस rc;
पूर्ण

/**
 * hl_fw_fini() - PCI finalization code.
 * @hdev: Poपूर्णांकer to hl_device काष्ठाure
 *
 * Unmap PCI bars and disable PCI device.
 */
व्योम hl_pci_fini(काष्ठा hl_device *hdev)
अणु
	hl_pci_bars_unmap(hdev);

	pci_clear_master(hdev->pdev);
	pci_disable_device(hdev->pdev);
पूर्ण
