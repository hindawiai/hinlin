<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  This contains the functions to handle the pci driver.

  Copyright (C) 2011-2012  Vayavya Lअसल Pvt Ltd


  Author: Rayagond Kokatanur <rayagond@vayavyaद_असल.com>
  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <linux/clk-provider.h>
#समावेश <linux/pci.h>
#समावेश <linux/dmi.h>

#समावेश "stmmac.h"

काष्ठा sपंचांगmac_pci_info अणु
	पूर्णांक (*setup)(काष्ठा pci_dev *pdev, काष्ठा plat_sपंचांगmacenet_data *plat);
पूर्ण;

अटल व्योम common_शेष_data(काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	plat->clk_csr = 2;	/* clk_csr_i = 20-35MHz & MDC = clk_csr_i/16 */
	plat->has_gmac = 1;
	plat->क्रमce_sf_dma_mode = 1;

	plat->mdio_bus_data->needs_reset = true;

	/* Set शेष value क्रम multicast hash bins */
	plat->multicast_filter_bins = HASH_TABLE_SIZE;

	/* Set शेष value क्रम unicast filter entries */
	plat->unicast_filter_entries = 1;

	/* Set the maxmtu to a शेष of JUMBO_LEN */
	plat->maxmtu = JUMBO_LEN;

	/* Set शेष number of RX and TX queues to use */
	plat->tx_queues_to_use = 1;
	plat->rx_queues_to_use = 1;

	/* Disable Priority config by शेष */
	plat->tx_queues_cfg[0].use_prio = false;
	plat->rx_queues_cfg[0].use_prio = false;

	/* Disable RX queues routing by शेष */
	plat->rx_queues_cfg[0].pkt_route = 0x0;
पूर्ण

अटल पूर्णांक sपंचांगmac_शेष_data(काष्ठा pci_dev *pdev,
			       काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	/* Set common शेष data first */
	common_शेष_data(plat);

	plat->bus_id = 1;
	plat->phy_addr = 0;
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_GMII;

	plat->dma_cfg->pbl = 32;
	plat->dma_cfg->pblx8 = true;
	/* TODO: AXI */

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sपंचांगmac_pci_info sपंचांगmac_pci_info = अणु
	.setup = sपंचांगmac_शेष_data,
पूर्ण;

अटल पूर्णांक snps_gmac5_शेष_data(काष्ठा pci_dev *pdev,
				   काष्ठा plat_sपंचांगmacenet_data *plat)
अणु
	पूर्णांक i;

	plat->clk_csr = 5;
	plat->has_gmac4 = 1;
	plat->क्रमce_sf_dma_mode = 1;
	plat->tso_en = 1;
	plat->pmt = 1;

	/* Set शेष value क्रम multicast hash bins */
	plat->multicast_filter_bins = HASH_TABLE_SIZE;

	/* Set शेष value क्रम unicast filter entries */
	plat->unicast_filter_entries = 1;

	/* Set the maxmtu to a शेष of JUMBO_LEN */
	plat->maxmtu = JUMBO_LEN;

	/* Set शेष number of RX and TX queues to use */
	plat->tx_queues_to_use = 4;
	plat->rx_queues_to_use = 4;

	plat->tx_sched_algorithm = MTL_TX_ALGORITHM_WRR;
	क्रम (i = 0; i < plat->tx_queues_to_use; i++) अणु
		plat->tx_queues_cfg[i].use_prio = false;
		plat->tx_queues_cfg[i].mode_to_use = MTL_QUEUE_DCB;
		plat->tx_queues_cfg[i].weight = 25;
		अगर (i > 0)
			plat->tx_queues_cfg[i].tbs_en = 1;
	पूर्ण

	plat->rx_sched_algorithm = MTL_RX_ALGORITHM_SP;
	क्रम (i = 0; i < plat->rx_queues_to_use; i++) अणु
		plat->rx_queues_cfg[i].use_prio = false;
		plat->rx_queues_cfg[i].mode_to_use = MTL_QUEUE_DCB;
		plat->rx_queues_cfg[i].pkt_route = 0x0;
		plat->rx_queues_cfg[i].chan = i;
	पूर्ण

	plat->bus_id = 1;
	plat->phy_addr = -1;
	plat->phy_पूर्णांकerface = PHY_INTERFACE_MODE_GMII;

	plat->dma_cfg->pbl = 32;
	plat->dma_cfg->pblx8 = true;

	/* Axi Configuration */
	plat->axi = devm_kzalloc(&pdev->dev, माप(*plat->axi), GFP_KERNEL);
	अगर (!plat->axi)
		वापस -ENOMEM;

	plat->axi->axi_wr_osr_lmt = 31;
	plat->axi->axi_rd_osr_lmt = 31;

	plat->axi->axi_fb = false;
	plat->axi->axi_blen[0] = 4;
	plat->axi->axi_blen[1] = 8;
	plat->axi->axi_blen[2] = 16;
	plat->axi->axi_blen[3] = 32;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sपंचांगmac_pci_info snps_gmac5_pci_info = अणु
	.setup = snps_gmac5_शेष_data,
पूर्ण;

/**
 * sपंचांगmac_pci_probe
 *
 * @pdev: pci device poपूर्णांकer
 * @id: poपूर्णांकer to table of device id/id's.
 *
 * Description: This probing function माला_लो called क्रम all PCI devices which
 * match the ID table and are not "owned" by other driver yet. This function
 * माला_लो passed a "struct pci_dev *" क्रम each device whose entry in the ID table
 * matches the device. The probe functions वापसs zero when the driver choose
 * to take "ownership" of the device or an error code(-ve no) otherwise.
 */
अटल पूर्णांक sपंचांगmac_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा sपंचांगmac_pci_info *info = (काष्ठा sपंचांगmac_pci_info *)id->driver_data;
	काष्ठा plat_sपंचांगmacenet_data *plat;
	काष्ठा sपंचांगmac_resources res;
	पूर्णांक i;
	पूर्णांक ret;

	plat = devm_kzalloc(&pdev->dev, माप(*plat), GFP_KERNEL);
	अगर (!plat)
		वापस -ENOMEM;

	plat->mdio_bus_data = devm_kzalloc(&pdev->dev,
					   माप(*plat->mdio_bus_data),
					   GFP_KERNEL);
	अगर (!plat->mdio_bus_data)
		वापस -ENOMEM;

	plat->dma_cfg = devm_kzalloc(&pdev->dev, माप(*plat->dma_cfg),
				     GFP_KERNEL);
	अगर (!plat->dma_cfg)
		वापस -ENOMEM;

	/* Enable pci device */
	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "%s: ERROR: failed to enable device\n",
			__func__);
		वापस ret;
	पूर्ण

	/* Get the base address of device */
	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		अगर (pci_resource_len(pdev, i) == 0)
			जारी;
		ret = pcim_iomap_regions(pdev, BIT(i), pci_name(pdev));
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण

	pci_set_master(pdev);

	ret = info->setup(pdev, plat);
	अगर (ret)
		वापस ret;

	स_रखो(&res, 0, माप(res));
	res.addr = pcim_iomap_table(pdev)[i];
	res.wol_irq = pdev->irq;
	res.irq = pdev->irq;

	वापस sपंचांगmac_dvr_probe(&pdev->dev, plat, &res);
पूर्ण

/**
 * sपंचांगmac_pci_हटाओ
 *
 * @pdev: platक्रमm device poपूर्णांकer
 * Description: this function calls the मुख्य to मुक्त the net resources
 * and releases the PCI resources.
 */
अटल व्योम sपंचांगmac_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;

	sपंचांगmac_dvr_हटाओ(&pdev->dev);

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		अगर (pci_resource_len(pdev, i) == 0)
			जारी;
		pcim_iounmap_regions(pdev, BIT(i));
		अवरोध;
	पूर्ण

	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगmac_pci_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक ret;

	ret = sपंचांगmac_suspend(dev);
	अगर (ret)
		वापस ret;

	ret = pci_save_state(pdev);
	अगर (ret)
		वापस ret;

	pci_disable_device(pdev);
	pci_wake_from_d3(pdev, true);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगmac_pci_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक ret;

	pci_restore_state(pdev);
	pci_set_घातer_state(pdev, PCI_D0);

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	pci_set_master(pdev);

	वापस sपंचांगmac_resume(dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांगmac_pm_ops, sपंचांगmac_pci_suspend, sपंचांगmac_pci_resume);

/* synthetic ID, no official venकरोr */
#घोषणा PCI_VENDOR_ID_STMMAC		0x0700

#घोषणा PCI_DEVICE_ID_STMMAC_STMMAC		0x1108
#घोषणा PCI_DEVICE_ID_SYNOPSYS_GMAC5_ID		0x7102

अटल स्थिर काष्ठा pci_device_id sपंचांगmac_id_table[] = अणु
	अणु PCI_DEVICE_DATA(STMMAC, STMMAC, &sपंचांगmac_pci_info) पूर्ण,
	अणु PCI_DEVICE_DATA(STMICRO, MAC, &sपंचांगmac_pci_info) पूर्ण,
	अणु PCI_DEVICE_DATA(SYNOPSYS, GMAC5_ID, &snps_gmac5_pci_info) पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, sपंचांगmac_id_table);

अटल काष्ठा pci_driver sपंचांगmac_pci_driver = अणु
	.name = STMMAC_RESOURCE_NAME,
	.id_table = sपंचांगmac_id_table,
	.probe = sपंचांगmac_pci_probe,
	.हटाओ = sपंचांगmac_pci_हटाओ,
	.driver         = अणु
		.pm     = &sपंचांगmac_pm_ops,
	पूर्ण,
पूर्ण;

module_pci_driver(sपंचांगmac_pci_driver);

MODULE_DESCRIPTION("STMMAC 10/100/1000 Ethernet PCI driver");
MODULE_AUTHOR("Rayagond Kokatanur <rayagond.kokatanur@vayavyalabs.com>");
MODULE_AUTHOR("Giuseppe Cavallaro <peppe.cavallaro@st.com>");
MODULE_LICENSE("GPL");
