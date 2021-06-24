<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp_netvf_मुख्य.c
 * Netronome भव function network device driver: Main entry poपूर्णांक
 * Author: Jason McMullan <jason.mcmullan@netronome.com>
 *         Rolf Neugebauer <rolf.neugebauer@netronome.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/etherdevice.h>

#समावेश "nfp_net_ctrl.h"
#समावेश "nfp_net.h"
#समावेश "nfp_main.h"

/**
 * काष्ठा nfp_net_vf - NFP VF-specअगरic device काष्ठाure
 * @nn:		NFP Net काष्ठाure क्रम this device
 * @irq_entries: Pre-allocated array of MSI-X entries
 * @q_bar:	Poपूर्णांकer to mapped QC memory (शून्य अगर TX/RX mapped directly)
 * @ddir:	Per-device debugfs directory
 */
काष्ठा nfp_net_vf अणु
	काष्ठा nfp_net *nn;

	काष्ठा msix_entry irq_entries[NFP_NET_NON_Q_VECTORS +
				      NFP_NET_MAX_TX_RINGS];
	u8 __iomem *q_bar;

	काष्ठा dentry *ddir;
पूर्ण;

अटल स्थिर अक्षर nfp_net_driver_name[] = "nfp_netvf";

#घोषणा PCI_DEVICE_NFP6000VF		0x6003
अटल स्थिर काष्ठा pci_device_id nfp_netvf_pci_device_ids[] = अणु
	अणु PCI_VENDOR_ID_NETRONOME, PCI_DEVICE_NFP6000VF,
	  PCI_VENDOR_ID_NETRONOME, PCI_ANY_ID,
	  PCI_ANY_ID, 0,
	पूर्ण,
	अणु 0, पूर्ण /* Required last entry. */
पूर्ण;
MODULE_DEVICE_TABLE(pci, nfp_netvf_pci_device_ids);

अटल व्योम nfp_netvf_get_mac_addr(काष्ठा nfp_net *nn)
अणु
	u8 mac_addr[ETH_ALEN];

	put_unaligned_be32(nn_पढ़ोl(nn, NFP_NET_CFG_MACADDR + 0), &mac_addr[0]);
	put_unaligned_be16(nn_पढ़ोw(nn, NFP_NET_CFG_MACADDR + 6), &mac_addr[4]);

	अगर (!is_valid_ether_addr(mac_addr)) अणु
		eth_hw_addr_अक्रमom(nn->dp.netdev);
		वापस;
	पूर्ण

	ether_addr_copy(nn->dp.netdev->dev_addr, mac_addr);
	ether_addr_copy(nn->dp.netdev->perm_addr, mac_addr);
पूर्ण

अटल पूर्णांक nfp_netvf_pci_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा nfp_net_fw_version fw_ver;
	पूर्णांक max_tx_rings, max_rx_rings;
	u32 tx_bar_off, rx_bar_off;
	u32 tx_bar_sz, rx_bar_sz;
	पूर्णांक tx_bar_no, rx_bar_no;
	काष्ठा nfp_net_vf *vf;
	अचिन्हित पूर्णांक num_irqs;
	u8 __iomem *ctrl_bar;
	काष्ठा nfp_net *nn;
	u32 startq;
	पूर्णांक stride;
	पूर्णांक err;

	vf = kzalloc(माप(*vf), GFP_KERNEL);
	अगर (!vf)
		वापस -ENOMEM;
	pci_set_drvdata(pdev, vf);

	err = pci_enable_device_mem(pdev);
	अगर (err)
		जाओ err_मुक्त_vf;

	err = pci_request_regions(pdev, nfp_net_driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev, "Unable to allocate device memory.\n");
		जाओ err_pci_disable;
	पूर्ण

	pci_set_master(pdev);

	err = dma_set_mask_and_coherent(&pdev->dev,
					DMA_BIT_MASK(NFP_NET_MAX_DMA_BITS));
	अगर (err)
		जाओ err_pci_regions;

	/* Map the Control BAR.
	 *
	 * Irrespective of the advertised BAR size we only map the
	 * first NFP_NET_CFG_BAR_SZ of the BAR.  This keeps the code
	 * the identical क्रम PF and VF drivers.
	 */
	ctrl_bar = ioremap(pci_resource_start(pdev, NFP_NET_CTRL_BAR),
				   NFP_NET_CFG_BAR_SZ);
	अगर (!ctrl_bar) अणु
		dev_err(&pdev->dev,
			"Failed to map resource %d\n", NFP_NET_CTRL_BAR);
		err = -EIO;
		जाओ err_pci_regions;
	पूर्ण

	nfp_net_get_fw_version(&fw_ver, ctrl_bar);
	अगर (fw_ver.resv || fw_ver.class != NFP_NET_CFG_VERSION_CLASS_GENERIC) अणु
		dev_err(&pdev->dev, "Unknown Firmware ABI %d.%d.%d.%d\n",
			fw_ver.resv, fw_ver.class, fw_ver.major, fw_ver.minor);
		err = -EINVAL;
		जाओ err_ctrl_unmap;
	पूर्ण

	/* Determine stride */
	अगर (nfp_net_fw_ver_eq(&fw_ver, 0, 0, 0, 1)) अणु
		stride = 2;
		tx_bar_no = NFP_NET_Q0_BAR;
		rx_bar_no = NFP_NET_Q1_BAR;
		dev_warn(&pdev->dev, "OBSOLETE Firmware detected - VF isolation not available\n");
	पूर्ण अन्यथा अणु
		चयन (fw_ver.major) अणु
		हाल 1 ... 5:
			stride = 4;
			tx_bar_no = NFP_NET_Q0_BAR;
			rx_bar_no = tx_bar_no;
			अवरोध;
		शेष:
			dev_err(&pdev->dev, "Unsupported Firmware ABI %d.%d.%d.%d\n",
				fw_ver.resv, fw_ver.class,
				fw_ver.major, fw_ver.minor);
			err = -EINVAL;
			जाओ err_ctrl_unmap;
		पूर्ण
	पूर्ण

	/* Find out how many rings are supported */
	max_tx_rings = पढ़ोl(ctrl_bar + NFP_NET_CFG_MAX_TXRINGS);
	max_rx_rings = पढ़ोl(ctrl_bar + NFP_NET_CFG_MAX_RXRINGS);

	tx_bar_sz = NFP_QCP_QUEUE_ADDR_SZ * max_tx_rings * stride;
	rx_bar_sz = NFP_QCP_QUEUE_ADDR_SZ * max_rx_rings * stride;

	/* Sanity checks */
	अगर (tx_bar_sz > pci_resource_len(pdev, tx_bar_no)) अणु
		dev_err(&pdev->dev,
			"TX BAR too small for number of TX rings. Adjusting\n");
		tx_bar_sz = pci_resource_len(pdev, tx_bar_no);
		max_tx_rings = (tx_bar_sz / NFP_QCP_QUEUE_ADDR_SZ) / 2;
	पूर्ण
	अगर (rx_bar_sz > pci_resource_len(pdev, rx_bar_no)) अणु
		dev_err(&pdev->dev,
			"RX BAR too small for number of RX rings. Adjusting\n");
		rx_bar_sz = pci_resource_len(pdev, rx_bar_no);
		max_rx_rings = (rx_bar_sz / NFP_QCP_QUEUE_ADDR_SZ) / 2;
	पूर्ण

	startq = पढ़ोl(ctrl_bar + NFP_NET_CFG_START_TXQ);
	tx_bar_off = NFP_PCIE_QUEUE(startq);
	startq = पढ़ोl(ctrl_bar + NFP_NET_CFG_START_RXQ);
	rx_bar_off = NFP_PCIE_QUEUE(startq);

	/* Allocate and initialise the netdev */
	nn = nfp_net_alloc(pdev, ctrl_bar, true, max_tx_rings, max_rx_rings);
	अगर (IS_ERR(nn)) अणु
		err = PTR_ERR(nn);
		जाओ err_ctrl_unmap;
	पूर्ण
	vf->nn = nn;

	nn->fw_ver = fw_ver;
	nn->dp.is_vf = 1;
	nn->stride_tx = stride;
	nn->stride_rx = stride;

	अगर (rx_bar_no == tx_bar_no) अणु
		u32 bar_off, bar_sz;
		resource_माप_प्रकार map_addr;

		/* Make a single overlapping BAR mapping */
		अगर (tx_bar_off < rx_bar_off)
			bar_off = tx_bar_off;
		अन्यथा
			bar_off = rx_bar_off;

		अगर ((tx_bar_off + tx_bar_sz) > (rx_bar_off + rx_bar_sz))
			bar_sz = (tx_bar_off + tx_bar_sz) - bar_off;
		अन्यथा
			bar_sz = (rx_bar_off + rx_bar_sz) - bar_off;

		map_addr = pci_resource_start(pdev, tx_bar_no) + bar_off;
		vf->q_bar = ioremap(map_addr, bar_sz);
		अगर (!vf->q_bar) अणु
			nn_err(nn, "Failed to map resource %d\n", tx_bar_no);
			err = -EIO;
			जाओ err_netdev_मुक्त;
		पूर्ण

		/* TX queues */
		nn->tx_bar = vf->q_bar + (tx_bar_off - bar_off);
		/* RX queues */
		nn->rx_bar = vf->q_bar + (rx_bar_off - bar_off);
	पूर्ण अन्यथा अणु
		resource_माप_प्रकार map_addr;

		/* TX queues */
		map_addr = pci_resource_start(pdev, tx_bar_no) + tx_bar_off;
		nn->tx_bar = ioremap(map_addr, tx_bar_sz);
		अगर (!nn->tx_bar) अणु
			nn_err(nn, "Failed to map resource %d\n", tx_bar_no);
			err = -EIO;
			जाओ err_netdev_मुक्त;
		पूर्ण

		/* RX queues */
		map_addr = pci_resource_start(pdev, rx_bar_no) + rx_bar_off;
		nn->rx_bar = ioremap(map_addr, rx_bar_sz);
		अगर (!nn->rx_bar) अणु
			nn_err(nn, "Failed to map resource %d\n", rx_bar_no);
			err = -EIO;
			जाओ err_unmap_tx;
		पूर्ण
	पूर्ण

	nfp_netvf_get_mac_addr(nn);

	num_irqs = nfp_net_irqs_alloc(pdev, vf->irq_entries,
				      NFP_NET_MIN_VNIC_IRQS,
				      NFP_NET_NON_Q_VECTORS +
				      nn->dp.num_r_vecs);
	अगर (!num_irqs) अणु
		nn_warn(nn, "Unable to allocate MSI-X Vectors. Exiting\n");
		err = -EIO;
		जाओ err_unmap_rx;
	पूर्ण
	nfp_net_irqs_assign(nn, vf->irq_entries, num_irqs);

	err = nfp_net_init(nn);
	अगर (err)
		जाओ err_irqs_disable;

	nfp_net_info(nn);
	vf->ddir = nfp_net_debugfs_device_add(pdev);
	nfp_net_debugfs_vnic_add(nn, vf->ddir);

	वापस 0;

err_irqs_disable:
	nfp_net_irqs_disable(pdev);
err_unmap_rx:
	अगर (!vf->q_bar)
		iounmap(nn->rx_bar);
err_unmap_tx:
	अगर (!vf->q_bar)
		iounmap(nn->tx_bar);
	अन्यथा
		iounmap(vf->q_bar);
err_netdev_मुक्त:
	nfp_net_मुक्त(nn);
err_ctrl_unmap:
	iounmap(ctrl_bar);
err_pci_regions:
	pci_release_regions(pdev);
err_pci_disable:
	pci_disable_device(pdev);
err_मुक्त_vf:
	pci_set_drvdata(pdev, शून्य);
	kमुक्त(vf);
	वापस err;
पूर्ण

अटल व्योम nfp_netvf_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा nfp_net_vf *vf;
	काष्ठा nfp_net *nn;

	vf = pci_get_drvdata(pdev);
	अगर (!vf)
		वापस;

	nn = vf->nn;

	/* Note, the order is slightly dअगरferent from above as we need
	 * to keep the nn poपूर्णांकer around till we have मुक्तd everything.
	 */
	nfp_net_debugfs_dir_clean(&nn->debugfs_dir);
	nfp_net_debugfs_dir_clean(&vf->ddir);

	nfp_net_clean(nn);

	nfp_net_irqs_disable(pdev);

	अगर (!vf->q_bar) अणु
		iounmap(nn->rx_bar);
		iounmap(nn->tx_bar);
	पूर्ण अन्यथा अणु
		iounmap(vf->q_bar);
	पूर्ण
	iounmap(nn->dp.ctrl_bar);

	nfp_net_मुक्त(nn);

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	pci_set_drvdata(pdev, शून्य);
	kमुक्त(vf);
पूर्ण

काष्ठा pci_driver nfp_netvf_pci_driver = अणु
	.name        = nfp_net_driver_name,
	.id_table    = nfp_netvf_pci_device_ids,
	.probe       = nfp_netvf_pci_probe,
	.हटाओ      = nfp_netvf_pci_हटाओ,
	.shutकरोwn    = nfp_netvf_pci_हटाओ,
पूर्ण;
