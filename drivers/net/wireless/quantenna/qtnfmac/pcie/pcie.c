<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2018 Quantenna Communications, Inc. All rights reserved. */

#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/pci.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/completion.h>

#समावेश "pcie_priv.h"
#समावेश "bus.h"
#समावेश "shm_ipc.h"
#समावेश "core.h"
#समावेश "debug.h"
#समावेश "util.h"
#समावेश "qtn_hw_ids.h"

#घोषणा QTN_SYSCTL_BAR	0
#घोषणा QTN_SHMEM_BAR	2
#घोषणा QTN_DMA_BAR	3

#घोषणा QTN_PCIE_MAX_FW_BUFSZ		(1 * 1024 * 1024)

अटल bool use_msi = true;
module_param(use_msi, bool, 0644);
MODULE_PARM_DESC(use_msi, "set 0 to use legacy interrupt");

अटल अचिन्हित पूर्णांक tx_bd_size_param;
module_param(tx_bd_size_param, uपूर्णांक, 0644);
MODULE_PARM_DESC(tx_bd_size_param, "Tx descriptors queue size");

अटल अचिन्हित पूर्णांक rx_bd_size_param;
module_param(rx_bd_size_param, uपूर्णांक, 0644);
MODULE_PARM_DESC(rx_bd_size_param, "Rx descriptors queue size");

अटल u8 flashboot = 1;
module_param(flashboot, byte, 0644);
MODULE_PARM_DESC(flashboot, "set to 0 to use FW binary file on FS");

अटल अचिन्हित पूर्णांक fw_blksize_param = QTN_PCIE_MAX_FW_BUFSZ;
module_param(fw_blksize_param, uपूर्णांक, 0644);
MODULE_PARM_DESC(fw_blksize_param, "firmware loading block size in bytes");

#घोषणा DRV_NAME	"qtnfmac_pcie"

पूर्णांक qtnf_pcie_control_tx(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = get_bus_priv(bus);
	पूर्णांक ret;

	ret = qtnf_shm_ipc_send(&priv->shm_ipc_ep_in, skb->data, skb->len);

	अगर (ret == -ETIMEDOUT) अणु
		pr_err("EP firmware is dead\n");
		bus->fw_state = QTNF_FW_STATE_DEAD;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक qtnf_pcie_alloc_skb_array(काष्ठा qtnf_pcie_bus_priv *priv)
अणु
	काष्ठा sk_buff **vaddr;
	पूर्णांक len;

	len = priv->tx_bd_num * माप(*priv->tx_skb) +
		priv->rx_bd_num * माप(*priv->rx_skb);
	vaddr = devm_kzalloc(&priv->pdev->dev, len, GFP_KERNEL);

	अगर (!vaddr)
		वापस -ENOMEM;

	priv->tx_skb = vaddr;

	vaddr += priv->tx_bd_num;
	priv->rx_skb = vaddr;

	वापस 0;
पूर्ण

अटल व्योम qtnf_pcie_bringup_fw_async(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = get_bus_priv(bus);
	काष्ठा pci_dev *pdev = priv->pdev;

	get_device(&pdev->dev);
	schedule_work(&bus->fw_work);
पूर्ण

अटल पूर्णांक qtnf_dbg_mps_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा qtnf_bus *bus = dev_get_drvdata(s->निजी);
	काष्ठा qtnf_pcie_bus_priv *priv = get_bus_priv(bus);

	seq_म_लिखो(s, "%d\n", pcie_get_mps(priv->pdev));

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_dbg_msi_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा qtnf_bus *bus = dev_get_drvdata(s->निजी);
	काष्ठा qtnf_pcie_bus_priv *priv = get_bus_priv(bus);

	seq_म_लिखो(s, "%u\n", priv->msi_enabled);

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_dbg_shm_stats(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा qtnf_bus *bus = dev_get_drvdata(s->निजी);
	काष्ठा qtnf_pcie_bus_priv *priv = get_bus_priv(bus);

	seq_म_लिखो(s, "shm_ipc_ep_in.tx_packet_count(%zu)\n",
		   priv->shm_ipc_ep_in.tx_packet_count);
	seq_म_लिखो(s, "shm_ipc_ep_in.rx_packet_count(%zu)\n",
		   priv->shm_ipc_ep_in.rx_packet_count);
	seq_म_लिखो(s, "shm_ipc_ep_out.tx_packet_count(%zu)\n",
		   priv->shm_ipc_ep_out.tx_समयout_count);
	seq_म_लिखो(s, "shm_ipc_ep_out.rx_packet_count(%zu)\n",
		   priv->shm_ipc_ep_out.rx_packet_count);

	वापस 0;
पूर्ण

पूर्णांक qtnf_pcie_fw_boot_करोne(काष्ठा qtnf_bus *bus)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = get_bus_priv(bus);
	अक्षर card_id[64];
	पूर्णांक ret;

	bus->fw_state = QTNF_FW_STATE_BOOT_DONE;
	ret = qtnf_core_attach(bus);
	अगर (ret) अणु
		pr_err("failed to attach core\n");
	पूर्ण अन्यथा अणु
		snम_लिखो(card_id, माप(card_id), "%s:%s",
			 DRV_NAME, pci_name(priv->pdev));
		qtnf_debugfs_init(bus, card_id);
		qtnf_debugfs_add_entry(bus, "mps", qtnf_dbg_mps_show);
		qtnf_debugfs_add_entry(bus, "msi_enabled", qtnf_dbg_msi_show);
		qtnf_debugfs_add_entry(bus, "shm_stats", qtnf_dbg_shm_stats);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम qtnf_tune_pcie_mps(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pci_dev *parent;
	पूर्णांक mps_p, mps_o, mps_m, mps;
	पूर्णांक ret;

	/* current mps */
	mps_o = pcie_get_mps(pdev);

	/* maximum supported mps */
	mps_m = 128 << pdev->pcie_mpss;

	/* suggested new mps value */
	mps = mps_m;

	अगर (pdev->bus && pdev->bus->self) अणु
		/* parent (bus) mps */
		parent = pdev->bus->self;

		अगर (pci_is_pcie(parent)) अणु
			mps_p = pcie_get_mps(parent);
			mps = min(mps_m, mps_p);
		पूर्ण
	पूर्ण

	ret = pcie_set_mps(pdev, mps);
	अगर (ret) अणु
		pr_err("failed to set mps to %d, keep using current %d\n",
		       mps, mps_o);
		वापस;
	पूर्ण

	pr_debug("set mps to %d (was %d, max %d)\n", mps, mps_o, mps_m);
पूर्ण

अटल व्योम qtnf_pcie_init_irq(काष्ठा qtnf_pcie_bus_priv *priv, bool use_msi)
अणु
	काष्ठा pci_dev *pdev = priv->pdev;

	/* fall back to legacy INTx पूर्णांकerrupts by शेष */
	priv->msi_enabled = 0;

	/* check अगर MSI capability is available */
	अगर (use_msi) अणु
		अगर (!pci_enable_msi(pdev)) अणु
			pr_debug("enabled MSI interrupt\n");
			priv->msi_enabled = 1;
		पूर्ण अन्यथा अणु
			pr_warn("failed to enable MSI interrupts");
		पूर्ण
	पूर्ण

	अगर (!priv->msi_enabled) अणु
		pr_warn("legacy PCIE interrupts enabled\n");
		pci_पूर्णांकx(pdev, 1);
	पूर्ण
पूर्ण

अटल व्योम __iomem *qtnf_map_bar(काष्ठा pci_dev *pdev, u8 index)
अणु
	व्योम __iomem *vaddr;
	dma_addr_t busaddr;
	माप_प्रकार len;
	पूर्णांक ret;

	ret = pcim_iomap_regions(pdev, 1 << index, "qtnfmac_pcie");
	अगर (ret)
		वापस IOMEM_ERR_PTR(ret);

	busaddr = pci_resource_start(pdev, index);
	len = pci_resource_len(pdev, index);
	vaddr = pcim_iomap_table(pdev)[index];
	अगर (!vaddr)
		वापस IOMEM_ERR_PTR(-ENOMEM);

	pr_debug("BAR%u vaddr=0x%p busaddr=%pad len=%u\n",
		 index, vaddr, &busaddr, (पूर्णांक)len);

	वापस vaddr;
पूर्ण

अटल व्योम qtnf_pcie_control_rx_callback(व्योम *arg, स्थिर u8 __iomem *buf,
					  माप_प्रकार len)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv = arg;
	काष्ठा qtnf_bus *bus = pci_get_drvdata(priv->pdev);
	काष्ठा sk_buff *skb;

	अगर (unlikely(len == 0)) अणु
		pr_warn("zero length packet received\n");
		वापस;
	पूर्ण

	skb = __dev_alloc_skb(len, GFP_KERNEL);

	अगर (unlikely(!skb)) अणु
		pr_err("failed to allocate skb\n");
		वापस;
	पूर्ण

	स_नकल_fromio(skb_put(skb, len), buf, len);

	qtnf_trans_handle_rx_ctl_packet(bus, skb);
पूर्ण

व्योम qtnf_pcie_init_shm_ipc(काष्ठा qtnf_pcie_bus_priv *priv,
			    काष्ठा qtnf_shm_ipc_region __iomem *ipc_tx_reg,
			    काष्ठा qtnf_shm_ipc_region __iomem *ipc_rx_reg,
			    स्थिर काष्ठा qtnf_shm_ipc_पूर्णांक *ipc_पूर्णांक)
अणु
	स्थिर काष्ठा qtnf_shm_ipc_rx_callback rx_callback = अणु
					qtnf_pcie_control_rx_callback, priv पूर्ण;

	qtnf_shm_ipc_init(&priv->shm_ipc_ep_in, QTNF_SHM_IPC_OUTBOUND,
			  ipc_tx_reg, priv->workqueue,
			  ipc_पूर्णांक, &rx_callback);
	qtnf_shm_ipc_init(&priv->shm_ipc_ep_out, QTNF_SHM_IPC_INBOUND,
			  ipc_rx_reg, priv->workqueue,
			  ipc_पूर्णांक, &rx_callback);
पूर्ण

अटल पूर्णांक qtnf_pcie_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा qtnf_pcie_bus_priv *pcie_priv;
	काष्ठा qtnf_bus *bus;
	व्योम __iomem *sysctl_bar;
	व्योम __iomem *epmem_bar;
	व्योम __iomem *dmareg_bar;
	अचिन्हित पूर्णांक chipid;
	पूर्णांक ret;

	अगर (!pci_is_pcie(pdev)) अणु
		pr_err("device %s is not PCI Express\n", pci_name(pdev));
		वापस -EIO;
	पूर्ण

	qtnf_tune_pcie_mps(pdev);

	ret = pcim_enable_device(pdev);
	अगर (ret) अणु
		pr_err("failed to init PCI device %x\n", pdev->device);
		वापस ret;
	पूर्ण

	pci_set_master(pdev);

	sysctl_bar = qtnf_map_bar(pdev, QTN_SYSCTL_BAR);
	अगर (IS_ERR(sysctl_bar)) अणु
		pr_err("failed to map BAR%u\n", QTN_SYSCTL_BAR);
		वापस PTR_ERR(sysctl_bar);
	पूर्ण

	dmareg_bar = qtnf_map_bar(pdev, QTN_DMA_BAR);
	अगर (IS_ERR(dmareg_bar)) अणु
		pr_err("failed to map BAR%u\n", QTN_DMA_BAR);
		वापस PTR_ERR(dmareg_bar);
	पूर्ण

	epmem_bar = qtnf_map_bar(pdev, QTN_SHMEM_BAR);
	अगर (IS_ERR(epmem_bar)) अणु
		pr_err("failed to map BAR%u\n", QTN_SHMEM_BAR);
		वापस PTR_ERR(epmem_bar);
	पूर्ण

	chipid = qtnf_chip_id_get(sysctl_bar);

	pr_info("identified device: %s\n", qtnf_chipid_to_string(chipid));

	चयन (chipid) अणु
	हाल QTN_CHIP_ID_PEARL:
	हाल QTN_CHIP_ID_PEARL_B:
	हाल QTN_CHIP_ID_PEARL_C:
		bus = qtnf_pcie_pearl_alloc(pdev);
		अवरोध;
	हाल QTN_CHIP_ID_TOPAZ:
		bus = qtnf_pcie_topaz_alloc(pdev);
		अवरोध;
	शेष:
		pr_err("unsupported chip ID 0x%x\n", chipid);
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!bus)
		वापस -ENOMEM;

	pcie_priv = get_bus_priv(bus);
	pci_set_drvdata(pdev, bus);
	bus->dev = &pdev->dev;
	bus->fw_state = QTNF_FW_STATE_DETACHED;
	pcie_priv->pdev = pdev;
	pcie_priv->tx_stopped = 0;
	pcie_priv->flashboot = flashboot;

	अगर (fw_blksize_param > QTN_PCIE_MAX_FW_BUFSZ)
		pcie_priv->fw_blksize =  QTN_PCIE_MAX_FW_BUFSZ;
	अन्यथा
		pcie_priv->fw_blksize = fw_blksize_param;

	mutex_init(&bus->bus_lock);
	spin_lock_init(&pcie_priv->tx_lock);
	spin_lock_init(&pcie_priv->tx_reclaim_lock);

	pcie_priv->tx_full_count = 0;
	pcie_priv->tx_करोne_count = 0;
	pcie_priv->pcie_irq_count = 0;
	pcie_priv->tx_reclaim_करोne = 0;
	pcie_priv->tx_reclaim_req = 0;

	pcie_priv->workqueue = create_singlethपढ़ो_workqueue("QTNF_PCIE");
	अगर (!pcie_priv->workqueue) अणु
		pr_err("failed to alloc bus workqueue\n");
		वापस -ENODEV;
	पूर्ण

	ret = dma_set_mask_and_coherent(&pdev->dev,
					pcie_priv->dma_mask_get_cb());
	अगर (ret) अणु
		pr_err("PCIE DMA coherent mask init failed 0x%llx\n",
		       pcie_priv->dma_mask_get_cb());
		जाओ error;
	पूर्ण

	init_dummy_netdev(&bus->mux_dev);
	qtnf_pcie_init_irq(pcie_priv, use_msi);
	pcie_priv->sysctl_bar = sysctl_bar;
	pcie_priv->dmareg_bar = dmareg_bar;
	pcie_priv->epmem_bar = epmem_bar;
	pci_save_state(pdev);

	ret = pcie_priv->probe_cb(bus, tx_bd_size_param, rx_bd_size_param);
	अगर (ret)
		जाओ error;

	qtnf_pcie_bringup_fw_async(bus);
	वापस 0;

error:
	flush_workqueue(pcie_priv->workqueue);
	destroy_workqueue(pcie_priv->workqueue);
	pci_set_drvdata(pdev, शून्य);
	वापस ret;
पूर्ण

अटल व्योम qtnf_pcie_मुक्त_shm_ipc(काष्ठा qtnf_pcie_bus_priv *priv)
अणु
	qtnf_shm_ipc_मुक्त(&priv->shm_ipc_ep_in);
	qtnf_shm_ipc_मुक्त(&priv->shm_ipc_ep_out);
पूर्ण

अटल व्योम qtnf_pcie_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv;
	काष्ठा qtnf_bus *bus;

	bus = pci_get_drvdata(dev);
	अगर (!bus)
		वापस;

	priv = get_bus_priv(bus);

	cancel_work_sync(&bus->fw_work);

	अगर (qtnf_fw_is_attached(bus))
		qtnf_core_detach(bus);

	netअगर_napi_del(&bus->mux_napi);
	flush_workqueue(priv->workqueue);
	destroy_workqueue(priv->workqueue);
	tasklet_समाप्त(&priv->reclaim_tq);

	qtnf_pcie_मुक्त_shm_ipc(priv);
	qtnf_debugfs_हटाओ(bus);
	priv->हटाओ_cb(bus);
	pci_set_drvdata(priv->pdev, शून्य);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक qtnf_pcie_suspend(काष्ठा device *dev)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv;
	काष्ठा qtnf_bus *bus;

	bus = dev_get_drvdata(dev);
	अगर (!bus)
		वापस -EFAULT;

	priv = get_bus_priv(bus);
	वापस priv->suspend_cb(bus);
पूर्ण

अटल पूर्णांक qtnf_pcie_resume(काष्ठा device *dev)
अणु
	काष्ठा qtnf_pcie_bus_priv *priv;
	काष्ठा qtnf_bus *bus;

	bus = dev_get_drvdata(dev);
	अगर (!bus)
		वापस -EFAULT;

	priv = get_bus_priv(bus);
	वापस priv->resume_cb(bus);
पूर्ण

/* Power Management Hooks */
अटल SIMPLE_DEV_PM_OPS(qtnf_pcie_pm_ops, qtnf_pcie_suspend,
			 qtnf_pcie_resume);
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id qtnf_pcie_devid_table[] = अणु
	अणु
		PCIE_VENDOR_ID_QUANTENNA, PCIE_DEVICE_ID_QSR,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, qtnf_pcie_devid_table);

अटल काष्ठा pci_driver qtnf_pcie_drv_data = अणु
	.name = DRV_NAME,
	.id_table = qtnf_pcie_devid_table,
	.probe = qtnf_pcie_probe,
	.हटाओ = qtnf_pcie_हटाओ,
#अगर_घोषित CONFIG_PM_SLEEP
	.driver = अणु
		.pm = &qtnf_pcie_pm_ops,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(qtnf_pcie_drv_data)

MODULE_AUTHOR("Quantenna Communications");
MODULE_DESCRIPTION("Quantenna PCIe bus driver for 802.11 wireless LAN.");
MODULE_LICENSE("GPL");
