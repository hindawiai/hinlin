<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/crc32.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश <linux/qed/qed_ll2_अगर.h>
#समावेश <net/devlink.h>
#समावेश <linux/aer.h>
#समावेश <linux/phylink.h>

#समावेश "qed.h"
#समावेश "qed_sriov.h"
#समावेश "qed_sp.h"
#समावेश "qed_dev_api.h"
#समावेश "qed_ll2.h"
#समावेश "qed_fcoe.h"
#समावेश "qed_iscsi.h"

#समावेश "qed_mcp.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_hw.h"
#समावेश "qed_selftest.h"
#समावेश "qed_debug.h"
#समावेश "qed_devlink.h"

#घोषणा QED_ROCE_QPS			(8192)
#घोषणा QED_ROCE_DPIS			(8)
#घोषणा QED_RDMA_SRQS                   QED_ROCE_QPS
#घोषणा QED_NVM_CFG_GET_FLAGS		0xA
#घोषणा QED_NVM_CFG_GET_PF_FLAGS	0x1A
#घोषणा QED_NVM_CFG_MAX_ATTRS		50

अटल अक्षर version[] =
	"QLogic FastLinQ 4xxxx Core Module qed " DRV_MODULE_VERSION "\n";

MODULE_DESCRIPTION("QLogic FastLinQ 4xxxx Core Module");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

#घोषणा FW_खाता_VERSION				\
	__stringअगरy(FW_MAJOR_VERSION) "."	\
	__stringअगरy(FW_MINOR_VERSION) "."	\
	__stringअगरy(FW_REVISION_VERSION) "."	\
	__stringअगरy(FW_ENGINEERING_VERSION)

#घोषणा QED_FW_खाता_NAME	\
	"qed/qed_init_values_zipped-" FW_खाता_VERSION ".bin"

MODULE_FIRMWARE(QED_FW_खाता_NAME);

/* MFW speed capabilities maps */

काष्ठा qed_mfw_speed_map अणु
	u32		mfw_val;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(caps);

	स्थिर u32	*cap_arr;
	u32		arr_size;
पूर्ण;

#घोषणा QED_MFW_SPEED_MAP(type, arr)		\
अणु						\
	.mfw_val	= (type),		\
	.cap_arr	= (arr),		\
	.arr_size	= ARRAY_SIZE(arr),	\
पूर्ण

अटल स्थिर u32 qed_mfw_ext_1g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
	ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
	ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_ext_10g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseR_FEC_BIT,
	ETHTOOL_LINK_MODE_10000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseLRM_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_ext_20g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_20000baseKR2_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_ext_25g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_ext_40g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_ext_50g_base_r[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_50000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseSR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseLR_ER_FR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseDR_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_ext_50g_base_r2[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_ext_100g_base_r2[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_100000baseKR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseSR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseCR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseDR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseLR2_ER2_FR2_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_ext_100g_base_r4[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT,
पूर्ण;

अटल काष्ठा qed_mfw_speed_map qed_mfw_ext_maps[] __ro_after_init = अणु
	QED_MFW_SPEED_MAP(ETH_EXT_ADV_SPEED_1G, qed_mfw_ext_1g),
	QED_MFW_SPEED_MAP(ETH_EXT_ADV_SPEED_10G, qed_mfw_ext_10g),
	QED_MFW_SPEED_MAP(ETH_EXT_ADV_SPEED_20G, qed_mfw_ext_20g),
	QED_MFW_SPEED_MAP(ETH_EXT_ADV_SPEED_25G, qed_mfw_ext_25g),
	QED_MFW_SPEED_MAP(ETH_EXT_ADV_SPEED_40G, qed_mfw_ext_40g),
	QED_MFW_SPEED_MAP(ETH_EXT_ADV_SPEED_50G_BASE_R,
			  qed_mfw_ext_50g_base_r),
	QED_MFW_SPEED_MAP(ETH_EXT_ADV_SPEED_50G_BASE_R2,
			  qed_mfw_ext_50g_base_r2),
	QED_MFW_SPEED_MAP(ETH_EXT_ADV_SPEED_100G_BASE_R2,
			  qed_mfw_ext_100g_base_r2),
	QED_MFW_SPEED_MAP(ETH_EXT_ADV_SPEED_100G_BASE_R4,
			  qed_mfw_ext_100g_base_r4),
पूर्ण;

अटल स्थिर u32 qed_mfw_legacy_1g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
	ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
	ETHTOOL_LINK_MODE_1000baseX_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_legacy_10g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseR_FEC_BIT,
	ETHTOOL_LINK_MODE_10000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseLRM_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_legacy_20g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_20000baseKR2_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_legacy_25g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_legacy_40g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_legacy_50g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT,
पूर्ण;

अटल स्थिर u32 qed_mfw_legacy_bb_100g[] __initस्थिर = अणु
	ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT,
पूर्ण;

अटल काष्ठा qed_mfw_speed_map qed_mfw_legacy_maps[] __ro_after_init = अणु
	QED_MFW_SPEED_MAP(NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G,
			  qed_mfw_legacy_1g),
	QED_MFW_SPEED_MAP(NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G,
			  qed_mfw_legacy_10g),
	QED_MFW_SPEED_MAP(NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G,
			  qed_mfw_legacy_20g),
	QED_MFW_SPEED_MAP(NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G,
			  qed_mfw_legacy_25g),
	QED_MFW_SPEED_MAP(NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G,
			  qed_mfw_legacy_40g),
	QED_MFW_SPEED_MAP(NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G,
			  qed_mfw_legacy_50g),
	QED_MFW_SPEED_MAP(NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G,
			  qed_mfw_legacy_bb_100g),
पूर्ण;

अटल व्योम __init qed_mfw_speed_map_populate(काष्ठा qed_mfw_speed_map *map)
अणु
	linkmode_set_bit_array(map->cap_arr, map->arr_size, map->caps);

	map->cap_arr = शून्य;
	map->arr_size = 0;
पूर्ण

अटल व्योम __init qed_mfw_speed_maps_init(व्योम)
अणु
	u32 i;

	क्रम (i = 0; i < ARRAY_SIZE(qed_mfw_ext_maps); i++)
		qed_mfw_speed_map_populate(qed_mfw_ext_maps + i);

	क्रम (i = 0; i < ARRAY_SIZE(qed_mfw_legacy_maps); i++)
		qed_mfw_speed_map_populate(qed_mfw_legacy_maps + i);
पूर्ण

अटल पूर्णांक __init qed_init(व्योम)
अणु
	pr_info("%s", version);

	qed_mfw_speed_maps_init();

	वापस 0;
पूर्ण
module_init(qed_init);

अटल व्योम __निकास qed_निकास(व्योम)
अणु
	/* To prevent marking this module as "permanent" */
पूर्ण
module_निकास(qed_निकास);

/* Check अगर the DMA controller on the machine can properly handle the DMA
 * addressing required by the device.
*/
अटल पूर्णांक qed_set_coherency_mask(काष्ठा qed_dev *cdev)
अणु
	काष्ठा device *dev = &cdev->pdev->dev;

	अगर (dma_set_mask(dev, DMA_BIT_MASK(64)) == 0) अणु
		अगर (dma_set_coherent_mask(dev, DMA_BIT_MASK(64)) != 0) अणु
			DP_NOTICE(cdev,
				  "Can't request 64-bit consistent allocations\n");
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अगर (dma_set_mask(dev, DMA_BIT_MASK(32)) != 0) अणु
		DP_NOTICE(cdev, "Can't request 64b/32b DMA addresses\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qed_मुक्त_pci(काष्ठा qed_dev *cdev)
अणु
	काष्ठा pci_dev *pdev = cdev->pdev;

	pci_disable_pcie_error_reporting(pdev);

	अगर (cdev->करोorbells && cdev->db_size)
		iounmap(cdev->करोorbells);
	अगर (cdev->regview)
		iounmap(cdev->regview);
	अगर (atomic_पढ़ो(&pdev->enable_cnt) == 1)
		pci_release_regions(pdev);

	pci_disable_device(pdev);
पूर्ण

#घोषणा PCI_REVISION_ID_ERROR_VAL	0xff

/* Perक्रमms PCI initializations as well as initializing PCI-related parameters
 * in the device काष्ठाrue. Returns 0 in हाल of success.
 */
अटल पूर्णांक qed_init_pci(काष्ठा qed_dev *cdev, काष्ठा pci_dev *pdev)
अणु
	u8 rev_id;
	पूर्णांक rc;

	cdev->pdev = pdev;

	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		DP_NOTICE(cdev, "Cannot enable PCI device\n");
		जाओ err0;
	पूर्ण

	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		DP_NOTICE(cdev, "No memory region found in bar #0\n");
		rc = -EIO;
		जाओ err1;
	पूर्ण

	अगर (IS_PF(cdev) && !(pci_resource_flags(pdev, 2) & IORESOURCE_MEM)) अणु
		DP_NOTICE(cdev, "No memory region found in bar #2\n");
		rc = -EIO;
		जाओ err1;
	पूर्ण

	अगर (atomic_पढ़ो(&pdev->enable_cnt) == 1) अणु
		rc = pci_request_regions(pdev, "qed");
		अगर (rc) अणु
			DP_NOTICE(cdev,
				  "Failed to request PCI memory resources\n");
			जाओ err1;
		पूर्ण
		pci_set_master(pdev);
		pci_save_state(pdev);
	पूर्ण

	pci_पढ़ो_config_byte(pdev, PCI_REVISION_ID, &rev_id);
	अगर (rev_id == PCI_REVISION_ID_ERROR_VAL) अणु
		DP_NOTICE(cdev,
			  "Detected PCI device error [rev_id 0x%x]. Probably due to prior indication. Aborting.\n",
			  rev_id);
		rc = -ENODEV;
		जाओ err2;
	पूर्ण
	अगर (!pci_is_pcie(pdev)) अणु
		DP_NOTICE(cdev, "The bus is not PCI Express\n");
		rc = -EIO;
		जाओ err2;
	पूर्ण

	cdev->pci_params.pm_cap = pci_find_capability(pdev, PCI_CAP_ID_PM);
	अगर (IS_PF(cdev) && !cdev->pci_params.pm_cap)
		DP_NOTICE(cdev, "Cannot find power management capability\n");

	rc = qed_set_coherency_mask(cdev);
	अगर (rc)
		जाओ err2;

	cdev->pci_params.mem_start = pci_resource_start(pdev, 0);
	cdev->pci_params.mem_end = pci_resource_end(pdev, 0);
	cdev->pci_params.irq = pdev->irq;

	cdev->regview = pci_ioremap_bar(pdev, 0);
	अगर (!cdev->regview) अणु
		DP_NOTICE(cdev, "Cannot map register space, aborting\n");
		rc = -ENOMEM;
		जाओ err2;
	पूर्ण

	cdev->db_phys_addr = pci_resource_start(cdev->pdev, 2);
	cdev->db_size = pci_resource_len(cdev->pdev, 2);
	अगर (!cdev->db_size) अणु
		अगर (IS_PF(cdev)) अणु
			DP_NOTICE(cdev, "No Doorbell bar available\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	cdev->करोorbells = ioremap_wc(cdev->db_phys_addr, cdev->db_size);

	अगर (!cdev->करोorbells) अणु
		DP_NOTICE(cdev, "Cannot map doorbell space\n");
		वापस -ENOMEM;
	पूर्ण

	/* AER (Advanced Error reporting) configuration */
	rc = pci_enable_pcie_error_reporting(pdev);
	अगर (rc)
		DP_VERBOSE(cdev, NETIF_MSG_DRV,
			   "Failed to configure PCIe AER [%d]\n", rc);

	वापस 0;

err2:
	pci_release_regions(pdev);
err1:
	pci_disable_device(pdev);
err0:
	वापस rc;
पूर्ण

पूर्णांक qed_fill_dev_info(काष्ठा qed_dev *cdev,
		      काष्ठा qed_dev_info *dev_info)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_hw_info *hw_info = &p_hwfn->hw_info;
	काष्ठा qed_tunnel_info *tun = &cdev->tunnel;
	काष्ठा qed_ptt  *ptt;

	स_रखो(dev_info, 0, माप(काष्ठा qed_dev_info));

	अगर (tun->vxlan.tun_cls == QED_TUNN_CLSS_MAC_VLAN &&
	    tun->vxlan.b_mode_enabled)
		dev_info->vxlan_enable = true;

	अगर (tun->l2_gre.b_mode_enabled && tun->ip_gre.b_mode_enabled &&
	    tun->l2_gre.tun_cls == QED_TUNN_CLSS_MAC_VLAN &&
	    tun->ip_gre.tun_cls == QED_TUNN_CLSS_MAC_VLAN)
		dev_info->gre_enable = true;

	अगर (tun->l2_geneve.b_mode_enabled && tun->ip_geneve.b_mode_enabled &&
	    tun->l2_geneve.tun_cls == QED_TUNN_CLSS_MAC_VLAN &&
	    tun->ip_geneve.tun_cls == QED_TUNN_CLSS_MAC_VLAN)
		dev_info->geneve_enable = true;

	dev_info->num_hwfns = cdev->num_hwfns;
	dev_info->pci_mem_start = cdev->pci_params.mem_start;
	dev_info->pci_mem_end = cdev->pci_params.mem_end;
	dev_info->pci_irq = cdev->pci_params.irq;
	dev_info->rdma_supported = QED_IS_RDMA_PERSONALITY(p_hwfn);
	dev_info->dev_type = cdev->type;
	ether_addr_copy(dev_info->hw_mac, hw_info->hw_mac_addr);

	अगर (IS_PF(cdev)) अणु
		dev_info->fw_major = FW_MAJOR_VERSION;
		dev_info->fw_minor = FW_MINOR_VERSION;
		dev_info->fw_rev = FW_REVISION_VERSION;
		dev_info->fw_eng = FW_ENGINEERING_VERSION;
		dev_info->b_पूर्णांकer_pf_चयन = test_bit(QED_MF_INTER_PF_SWITCH,
						       &cdev->mf_bits);
		अगर (!test_bit(QED_MF_DISABLE_ARFS, &cdev->mf_bits))
			dev_info->b_arfs_capable = true;
		dev_info->tx_चयनing = true;

		अगर (hw_info->b_wol_support == QED_WOL_SUPPORT_PME)
			dev_info->wol_support = true;

		dev_info->smart_an = qed_mcp_is_smart_an_supported(p_hwfn);

		dev_info->असल_pf_id = QED_LEADING_HWFN(cdev)->असल_pf_id;
	पूर्ण अन्यथा अणु
		qed_vf_get_fw_version(&cdev->hwfns[0], &dev_info->fw_major,
				      &dev_info->fw_minor, &dev_info->fw_rev,
				      &dev_info->fw_eng);
	पूर्ण

	अगर (IS_PF(cdev)) अणु
		ptt = qed_ptt_acquire(QED_LEADING_HWFN(cdev));
		अगर (ptt) अणु
			qed_mcp_get_mfw_ver(QED_LEADING_HWFN(cdev), ptt,
					    &dev_info->mfw_rev, शून्य);

			qed_mcp_get_mbi_ver(QED_LEADING_HWFN(cdev), ptt,
					    &dev_info->mbi_version);

			qed_mcp_get_flash_size(QED_LEADING_HWFN(cdev), ptt,
					       &dev_info->flash_size);

			qed_ptt_release(QED_LEADING_HWFN(cdev), ptt);
		पूर्ण
	पूर्ण अन्यथा अणु
		qed_mcp_get_mfw_ver(QED_LEADING_HWFN(cdev), शून्य,
				    &dev_info->mfw_rev, शून्य);
	पूर्ण

	dev_info->mtu = hw_info->mtu;
	cdev->common_dev_info = *dev_info;

	वापस 0;
पूर्ण

अटल व्योम qed_मुक्त_cdev(काष्ठा qed_dev *cdev)
अणु
	kमुक्त((व्योम *)cdev);
पूर्ण

अटल काष्ठा qed_dev *qed_alloc_cdev(काष्ठा pci_dev *pdev)
अणु
	काष्ठा qed_dev *cdev;

	cdev = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस cdev;

	qed_init_काष्ठा(cdev);

	वापस cdev;
पूर्ण

/* Sets the requested घातer state */
अटल पूर्णांक qed_set_घातer_state(काष्ठा qed_dev *cdev, pci_घातer_t state)
अणु
	अगर (!cdev)
		वापस -ENODEV;

	DP_VERBOSE(cdev, NETIF_MSG_DRV, "Omitting Power state change\n");
	वापस 0;
पूर्ण

/* probing */
अटल काष्ठा qed_dev *qed_probe(काष्ठा pci_dev *pdev,
				 काष्ठा qed_probe_params *params)
अणु
	काष्ठा qed_dev *cdev;
	पूर्णांक rc;

	cdev = qed_alloc_cdev(pdev);
	अगर (!cdev)
		जाओ err0;

	cdev->drv_type = DRV_ID_DRV_TYPE_LINUX;
	cdev->protocol = params->protocol;

	अगर (params->is_vf)
		cdev->b_is_vf = true;

	qed_init_dp(cdev, params->dp_module, params->dp_level);

	cdev->recov_in_prog = params->recov_in_prog;

	rc = qed_init_pci(cdev, pdev);
	अगर (rc) अणु
		DP_ERR(cdev, "init pci failed\n");
		जाओ err1;
	पूर्ण
	DP_INFO(cdev, "PCI init completed successfully\n");

	rc = qed_hw_prepare(cdev, QED_PCI_DEFAULT);
	अगर (rc) अणु
		DP_ERR(cdev, "hw prepare failed\n");
		जाओ err2;
	पूर्ण

	DP_INFO(cdev, "qed_probe completed successfully\n");

	वापस cdev;

err2:
	qed_मुक्त_pci(cdev);
err1:
	qed_मुक्त_cdev(cdev);
err0:
	वापस शून्य;
पूर्ण

अटल व्योम qed_हटाओ(काष्ठा qed_dev *cdev)
अणु
	अगर (!cdev)
		वापस;

	qed_hw_हटाओ(cdev);

	qed_मुक्त_pci(cdev);

	qed_set_घातer_state(cdev, PCI_D3hot);

	qed_मुक्त_cdev(cdev);
पूर्ण

अटल व्योम qed_disable_msix(काष्ठा qed_dev *cdev)
अणु
	अगर (cdev->पूर्णांक_params.out.पूर्णांक_mode == QED_INT_MODE_MSIX) अणु
		pci_disable_msix(cdev->pdev);
		kमुक्त(cdev->पूर्णांक_params.msix_table);
	पूर्ण अन्यथा अगर (cdev->पूर्णांक_params.out.पूर्णांक_mode == QED_INT_MODE_MSI) अणु
		pci_disable_msi(cdev->pdev);
	पूर्ण

	स_रखो(&cdev->पूर्णांक_params.out, 0, माप(काष्ठा qed_पूर्णांक_param));
पूर्ण

अटल पूर्णांक qed_enable_msix(काष्ठा qed_dev *cdev,
			   काष्ठा qed_पूर्णांक_params *पूर्णांक_params)
अणु
	पूर्णांक i, rc, cnt;

	cnt = पूर्णांक_params->in.num_vectors;

	क्रम (i = 0; i < cnt; i++)
		पूर्णांक_params->msix_table[i].entry = i;

	rc = pci_enable_msix_range(cdev->pdev, पूर्णांक_params->msix_table,
				   पूर्णांक_params->in.min_msix_cnt, cnt);
	अगर (rc < cnt && rc >= पूर्णांक_params->in.min_msix_cnt &&
	    (rc % cdev->num_hwfns)) अणु
		pci_disable_msix(cdev->pdev);

		/* If fastpath is initialized, we need at least one पूर्णांकerrupt
		 * per hwfn [and the slow path पूर्णांकerrupts]. New requested number
		 * should be a multiple of the number of hwfns.
		 */
		cnt = (rc / cdev->num_hwfns) * cdev->num_hwfns;
		DP_NOTICE(cdev,
			  "Trying to enable MSI-X with less vectors (%d out of %d)\n",
			  cnt, पूर्णांक_params->in.num_vectors);
		rc = pci_enable_msix_exact(cdev->pdev, पूर्णांक_params->msix_table,
					   cnt);
		अगर (!rc)
			rc = cnt;
	पूर्ण

	अगर (rc > 0) अणु
		/* MSI-x configuration was achieved */
		पूर्णांक_params->out.पूर्णांक_mode = QED_INT_MODE_MSIX;
		पूर्णांक_params->out.num_vectors = rc;
		rc = 0;
	पूर्ण अन्यथा अणु
		DP_NOTICE(cdev,
			  "Failed to enable MSI-X [Requested %d vectors][rc %d]\n",
			  cnt, rc);
	पूर्ण

	वापस rc;
पूर्ण

/* This function outमाला_दो the पूर्णांक mode and the number of enabled msix vector */
अटल पूर्णांक qed_set_पूर्णांक_mode(काष्ठा qed_dev *cdev, bool क्रमce_mode)
अणु
	काष्ठा qed_पूर्णांक_params *पूर्णांक_params = &cdev->पूर्णांक_params;
	काष्ठा msix_entry *tbl;
	पूर्णांक rc = 0, cnt;

	चयन (पूर्णांक_params->in.पूर्णांक_mode) अणु
	हाल QED_INT_MODE_MSIX:
		/* Allocate MSIX table */
		cnt = पूर्णांक_params->in.num_vectors;
		पूर्णांक_params->msix_table = kसुस्मृति(cnt, माप(*tbl), GFP_KERNEL);
		अगर (!पूर्णांक_params->msix_table) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		/* Enable MSIX */
		rc = qed_enable_msix(cdev, पूर्णांक_params);
		अगर (!rc)
			जाओ out;

		DP_NOTICE(cdev, "Failed to enable MSI-X\n");
		kमुक्त(पूर्णांक_params->msix_table);
		अगर (क्रमce_mode)
			जाओ out;
		fallthrough;

	हाल QED_INT_MODE_MSI:
		अगर (cdev->num_hwfns == 1) अणु
			rc = pci_enable_msi(cdev->pdev);
			अगर (!rc) अणु
				पूर्णांक_params->out.पूर्णांक_mode = QED_INT_MODE_MSI;
				जाओ out;
			पूर्ण

			DP_NOTICE(cdev, "Failed to enable MSI\n");
			अगर (क्रमce_mode)
				जाओ out;
		पूर्ण
		fallthrough;

	हाल QED_INT_MODE_INTA:
			पूर्णांक_params->out.पूर्णांक_mode = QED_INT_MODE_INTA;
			rc = 0;
			जाओ out;
	शेष:
		DP_NOTICE(cdev, "Unknown int_mode value %d\n",
			  पूर्णांक_params->in.पूर्णांक_mode);
		rc = -EINVAL;
	पूर्ण

out:
	अगर (!rc)
		DP_INFO(cdev, "Using %s interrupts\n",
			पूर्णांक_params->out.पूर्णांक_mode == QED_INT_MODE_INTA ?
			"INTa" : पूर्णांक_params->out.पूर्णांक_mode == QED_INT_MODE_MSI ?
			"MSI" : "MSIX");
	cdev->पूर्णांक_coalescing_mode = QED_COAL_MODE_ENABLE;

	वापस rc;
पूर्ण

अटल व्योम qed_simd_handler_config(काष्ठा qed_dev *cdev, व्योम *token,
				    पूर्णांक index, व्योम(*handler)(व्योम *))
अणु
	काष्ठा qed_hwfn *hwfn = &cdev->hwfns[index % cdev->num_hwfns];
	पूर्णांक relative_idx = index / cdev->num_hwfns;

	hwfn->simd_proto_handler[relative_idx].func = handler;
	hwfn->simd_proto_handler[relative_idx].token = token;
पूर्ण

अटल व्योम qed_simd_handler_clean(काष्ठा qed_dev *cdev, पूर्णांक index)
अणु
	काष्ठा qed_hwfn *hwfn = &cdev->hwfns[index % cdev->num_hwfns];
	पूर्णांक relative_idx = index / cdev->num_hwfns;

	स_रखो(&hwfn->simd_proto_handler[relative_idx], 0,
	       माप(काष्ठा qed_simd_fp_handler));
पूर्ण

अटल irqवापस_t qed_msix_sp_पूर्णांक(पूर्णांक irq, व्योम *tasklet)
अणु
	tasklet_schedule((काष्ठा tasklet_काष्ठा *)tasklet);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qed_single_पूर्णांक(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा qed_dev *cdev = (काष्ठा qed_dev *)dev_instance;
	काष्ठा qed_hwfn *hwfn;
	irqवापस_t rc = IRQ_NONE;
	u64 status;
	पूर्णांक i, j;

	क्रम (i = 0; i < cdev->num_hwfns; i++) अणु
		status = qed_पूर्णांक_igu_पढ़ो_sisr_reg(&cdev->hwfns[i]);

		अगर (!status)
			जारी;

		hwfn = &cdev->hwfns[i];

		/* Slowpath पूर्णांकerrupt */
		अगर (unlikely(status & 0x1)) अणु
			tasklet_schedule(&hwfn->sp_dpc);
			status &= ~0x1;
			rc = IRQ_HANDLED;
		पूर्ण

		/* Fastpath पूर्णांकerrupts */
		क्रम (j = 0; j < 64; j++) अणु
			अगर ((0x2ULL << j) & status) अणु
				काष्ठा qed_simd_fp_handler *p_handler =
					&hwfn->simd_proto_handler[j];

				अगर (p_handler->func)
					p_handler->func(p_handler->token);
				अन्यथा
					DP_NOTICE(hwfn,
						  "Not calling fastpath handler as it is NULL [handler #%d, status 0x%llx]\n",
						  j, status);

				status &= ~(0x2ULL << j);
				rc = IRQ_HANDLED;
			पूर्ण
		पूर्ण

		अगर (unlikely(status))
			DP_VERBOSE(hwfn, NETIF_MSG_INTR,
				   "got an unknown interrupt status 0x%llx\n",
				   status);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qed_slowpath_irq_req(काष्ठा qed_hwfn *hwfn)
अणु
	काष्ठा qed_dev *cdev = hwfn->cdev;
	u32 पूर्णांक_mode;
	पूर्णांक rc = 0;
	u8 id;

	पूर्णांक_mode = cdev->पूर्णांक_params.out.पूर्णांक_mode;
	अगर (पूर्णांक_mode == QED_INT_MODE_MSIX) अणु
		id = hwfn->my_id;
		snम_लिखो(hwfn->name, NAME_SIZE, "sp-%d-%02x:%02x.%02x",
			 id, cdev->pdev->bus->number,
			 PCI_SLOT(cdev->pdev->devfn), hwfn->असल_pf_id);
		rc = request_irq(cdev->पूर्णांक_params.msix_table[id].vector,
				 qed_msix_sp_पूर्णांक, 0, hwfn->name, &hwfn->sp_dpc);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ flags = 0;

		snम_लिखो(cdev->name, NAME_SIZE, "%02x:%02x.%02x",
			 cdev->pdev->bus->number, PCI_SLOT(cdev->pdev->devfn),
			 PCI_FUNC(cdev->pdev->devfn));

		अगर (cdev->पूर्णांक_params.out.पूर्णांक_mode == QED_INT_MODE_INTA)
			flags |= IRQF_SHARED;

		rc = request_irq(cdev->pdev->irq, qed_single_पूर्णांक,
				 flags, cdev->name, cdev);
	पूर्ण

	अगर (rc)
		DP_NOTICE(cdev, "request_irq failed, rc = %d\n", rc);
	अन्यथा
		DP_VERBOSE(hwfn, (NETIF_MSG_INTR | QED_MSG_SP),
			   "Requested slowpath %s\n",
			   (पूर्णांक_mode == QED_INT_MODE_MSIX) ? "MSI-X" : "IRQ");

	वापस rc;
पूर्ण

अटल व्योम qed_slowpath_tasklet_flush(काष्ठा qed_hwfn *p_hwfn)
अणु
	/* Calling the disable function will make sure that any
	 * currently-running function is completed. The following call to the
	 * enable function makes this sequence a flush-like operation.
	 */
	अगर (p_hwfn->b_sp_dpc_enabled) अणु
		tasklet_disable(&p_hwfn->sp_dpc);
		tasklet_enable(&p_hwfn->sp_dpc);
	पूर्ण
पूर्ण

व्योम qed_slowpath_irq_sync(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	u8 id = p_hwfn->my_id;
	u32 पूर्णांक_mode;

	पूर्णांक_mode = cdev->पूर्णांक_params.out.पूर्णांक_mode;
	अगर (पूर्णांक_mode == QED_INT_MODE_MSIX)
		synchronize_irq(cdev->पूर्णांक_params.msix_table[id].vector);
	अन्यथा
		synchronize_irq(cdev->pdev->irq);

	qed_slowpath_tasklet_flush(p_hwfn);
पूर्ण

अटल व्योम qed_slowpath_irq_मुक्त(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक i;

	अगर (cdev->पूर्णांक_params.out.पूर्णांक_mode == QED_INT_MODE_MSIX) अणु
		क्रम_each_hwfn(cdev, i) अणु
			अगर (!cdev->hwfns[i].b_पूर्णांक_requested)
				अवरोध;
			synchronize_irq(cdev->पूर्णांक_params.msix_table[i].vector);
			मुक्त_irq(cdev->पूर्णांक_params.msix_table[i].vector,
				 &cdev->hwfns[i].sp_dpc);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (QED_LEADING_HWFN(cdev)->b_पूर्णांक_requested)
			मुक्त_irq(cdev->pdev->irq, cdev);
	पूर्ण
	qed_पूर्णांक_disable_post_isr_release(cdev);
पूर्ण

अटल पूर्णांक qed_nic_stop(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक i, rc;

	rc = qed_hw_stop(cdev);

	क्रम (i = 0; i < cdev->num_hwfns; i++) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		अगर (p_hwfn->b_sp_dpc_enabled) अणु
			tasklet_disable(&p_hwfn->sp_dpc);
			p_hwfn->b_sp_dpc_enabled = false;
			DP_VERBOSE(cdev, NETIF_MSG_IFDOWN,
				   "Disabled sp tasklet [hwfn %d] at %p\n",
				   i, &p_hwfn->sp_dpc);
		पूर्ण
	पूर्ण

	qed_dbg_pf_निकास(cdev);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_nic_setup(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक rc, i;

	/* Determine अगर पूर्णांकerface is going to require LL2 */
	अगर (QED_LEADING_HWFN(cdev)->hw_info.personality != QED_PCI_ETH) अणु
		क्रम (i = 0; i < cdev->num_hwfns; i++) अणु
			काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

			p_hwfn->using_ll2 = true;
		पूर्ण
	पूर्ण

	rc = qed_resc_alloc(cdev);
	अगर (rc)
		वापस rc;

	DP_INFO(cdev, "Allocated qed resources\n");

	qed_resc_setup(cdev);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_set_पूर्णांक_fp(काष्ठा qed_dev *cdev, u16 cnt)
अणु
	पूर्णांक limit = 0;

	/* Mark the fastpath as मुक्त/used */
	cdev->पूर्णांक_params.fp_initialized = cnt ? true : false;

	अगर (cdev->पूर्णांक_params.out.पूर्णांक_mode != QED_INT_MODE_MSIX)
		limit = cdev->num_hwfns * 63;
	अन्यथा अगर (cdev->पूर्णांक_params.fp_msix_cnt)
		limit = cdev->पूर्णांक_params.fp_msix_cnt;

	अगर (!limit)
		वापस -ENOMEM;

	वापस min_t(पूर्णांक, cnt, limit);
पूर्ण

अटल पूर्णांक qed_get_पूर्णांक_fp(काष्ठा qed_dev *cdev, काष्ठा qed_पूर्णांक_info *info)
अणु
	स_रखो(info, 0, माप(काष्ठा qed_पूर्णांक_info));

	अगर (!cdev->पूर्णांक_params.fp_initialized) अणु
		DP_INFO(cdev,
			"Protocol driver requested interrupt information, but its support is not yet configured\n");
		वापस -EINVAL;
	पूर्ण

	/* Need to expose only MSI-X inक्रमmation; Single IRQ is handled solely
	 * by qed.
	 */
	अगर (cdev->पूर्णांक_params.out.पूर्णांक_mode == QED_INT_MODE_MSIX) अणु
		पूर्णांक msix_base = cdev->पूर्णांक_params.fp_msix_base;

		info->msix_cnt = cdev->पूर्णांक_params.fp_msix_cnt;
		info->msix = &cdev->पूर्णांक_params.msix_table[msix_base];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_slowpath_setup_पूर्णांक(काष्ठा qed_dev *cdev,
				  क्रमागत qed_पूर्णांक_mode पूर्णांक_mode)
अणु
	काष्ठा qed_sb_cnt_info sb_cnt_info;
	पूर्णांक num_l2_queues = 0;
	पूर्णांक rc;
	पूर्णांक i;

	अगर ((पूर्णांक_mode == QED_INT_MODE_MSI) && (cdev->num_hwfns > 1)) अणु
		DP_NOTICE(cdev, "MSI mode is not supported for CMT devices\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&cdev->पूर्णांक_params, 0, माप(काष्ठा qed_पूर्णांक_params));
	cdev->पूर्णांक_params.in.पूर्णांक_mode = पूर्णांक_mode;
	क्रम_each_hwfn(cdev, i) अणु
		स_रखो(&sb_cnt_info, 0, माप(sb_cnt_info));
		qed_पूर्णांक_get_num_sbs(&cdev->hwfns[i], &sb_cnt_info);
		cdev->पूर्णांक_params.in.num_vectors += sb_cnt_info.cnt;
		cdev->पूर्णांक_params.in.num_vectors++; /* slowpath */
	पूर्ण

	/* We want a minimum of one slowpath and one fastpath vector per hwfn */
	cdev->पूर्णांक_params.in.min_msix_cnt = cdev->num_hwfns * 2;

	अगर (is_kdump_kernel()) अणु
		DP_INFO(cdev,
			"Kdump kernel: Limit the max number of requested MSI-X vectors to %hd\n",
			cdev->पूर्णांक_params.in.min_msix_cnt);
		cdev->पूर्णांक_params.in.num_vectors =
			cdev->पूर्णांक_params.in.min_msix_cnt;
	पूर्ण

	rc = qed_set_पूर्णांक_mode(cdev, false);
	अगर (rc)  अणु
		DP_ERR(cdev, "qed_slowpath_setup_int ERR\n");
		वापस rc;
	पूर्ण

	cdev->पूर्णांक_params.fp_msix_base = cdev->num_hwfns;
	cdev->पूर्णांक_params.fp_msix_cnt = cdev->पूर्णांक_params.out.num_vectors -
				       cdev->num_hwfns;

	अगर (!IS_ENABLED(CONFIG_QED_RDMA) ||
	    !QED_IS_RDMA_PERSONALITY(QED_LEADING_HWFN(cdev)))
		वापस 0;

	क्रम_each_hwfn(cdev, i)
		num_l2_queues += FEAT_NUM(&cdev->hwfns[i], QED_PF_L2_QUE);

	DP_VERBOSE(cdev, QED_MSG_RDMA,
		   "cdev->int_params.fp_msix_cnt=%d num_l2_queues=%d\n",
		   cdev->पूर्णांक_params.fp_msix_cnt, num_l2_queues);

	अगर (cdev->पूर्णांक_params.fp_msix_cnt > num_l2_queues) अणु
		cdev->पूर्णांक_params.rdma_msix_cnt =
			(cdev->पूर्णांक_params.fp_msix_cnt - num_l2_queues)
			/ cdev->num_hwfns;
		cdev->पूर्णांक_params.rdma_msix_base =
			cdev->पूर्णांक_params.fp_msix_base + num_l2_queues;
		cdev->पूर्णांक_params.fp_msix_cnt = num_l2_queues;
	पूर्ण अन्यथा अणु
		cdev->पूर्णांक_params.rdma_msix_cnt = 0;
	पूर्ण

	DP_VERBOSE(cdev, QED_MSG_RDMA, "roce_msix_cnt=%d roce_msix_base=%d\n",
		   cdev->पूर्णांक_params.rdma_msix_cnt,
		   cdev->पूर्णांक_params.rdma_msix_base);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_slowpath_vf_setup_पूर्णांक(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक rc;

	स_रखो(&cdev->पूर्णांक_params, 0, माप(काष्ठा qed_पूर्णांक_params));
	cdev->पूर्णांक_params.in.पूर्णांक_mode = QED_INT_MODE_MSIX;

	qed_vf_get_num_rxqs(QED_LEADING_HWFN(cdev),
			    &cdev->पूर्णांक_params.in.num_vectors);
	अगर (cdev->num_hwfns > 1) अणु
		u8 vectors = 0;

		qed_vf_get_num_rxqs(&cdev->hwfns[1], &vectors);
		cdev->पूर्णांक_params.in.num_vectors += vectors;
	पूर्ण

	/* We want a minimum of one fastpath vector per vf hwfn */
	cdev->पूर्णांक_params.in.min_msix_cnt = cdev->num_hwfns;

	rc = qed_set_पूर्णांक_mode(cdev, true);
	अगर (rc)
		वापस rc;

	cdev->पूर्णांक_params.fp_msix_base = 0;
	cdev->पूर्णांक_params.fp_msix_cnt = cdev->पूर्णांक_params.out.num_vectors;

	वापस 0;
पूर्ण

u32 qed_unzip_data(काष्ठा qed_hwfn *p_hwfn, u32 input_len,
		   u8 *input_buf, u32 max_size, u8 *unzip_buf)
अणु
	पूर्णांक rc;

	p_hwfn->stream->next_in = input_buf;
	p_hwfn->stream->avail_in = input_len;
	p_hwfn->stream->next_out = unzip_buf;
	p_hwfn->stream->avail_out = max_size;

	rc = zlib_inflateInit2(p_hwfn->stream, MAX_WBITS);

	अगर (rc != Z_OK) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_DRV, "zlib init failed, rc = %d\n",
			   rc);
		वापस 0;
	पूर्ण

	rc = zlib_inflate(p_hwfn->stream, Z_FINISH);
	zlib_inflateEnd(p_hwfn->stream);

	अगर (rc != Z_OK && rc != Z_STREAM_END) अणु
		DP_VERBOSE(p_hwfn, NETIF_MSG_DRV, "FW unzip error: %s, rc=%d\n",
			   p_hwfn->stream->msg, rc);
		वापस 0;
	पूर्ण

	वापस p_hwfn->stream->total_out / 4;
पूर्ण

अटल पूर्णांक qed_alloc_stream_mem(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक i;
	व्योम *workspace;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		p_hwfn->stream = kzalloc(माप(*p_hwfn->stream), GFP_KERNEL);
		अगर (!p_hwfn->stream)
			वापस -ENOMEM;

		workspace = vzalloc(zlib_inflate_workspacesize());
		अगर (!workspace)
			वापस -ENOMEM;
		p_hwfn->stream->workspace = workspace;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qed_मुक्त_stream_mem(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक i;

	क्रम_each_hwfn(cdev, i) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		अगर (!p_hwfn->stream)
			वापस;

		vमुक्त(p_hwfn->stream->workspace);
		kमुक्त(p_hwfn->stream);
	पूर्ण
पूर्ण

अटल व्योम qed_update_pf_params(काष्ठा qed_dev *cdev,
				 काष्ठा qed_pf_params *params)
अणु
	पूर्णांक i;

	अगर (IS_ENABLED(CONFIG_QED_RDMA)) अणु
		params->rdma_pf_params.num_qps = QED_ROCE_QPS;
		params->rdma_pf_params.min_dpis = QED_ROCE_DPIS;
		params->rdma_pf_params.num_srqs = QED_RDMA_SRQS;
		/* भागide by 3 the MRs to aव्योम MF ILT overflow */
		params->rdma_pf_params.gl_pi = QED_ROCE_PROTOCOL_INDEX;
	पूर्ण

	अगर (cdev->num_hwfns > 1 || IS_VF(cdev))
		params->eth_pf_params.num_arfs_filters = 0;

	/* In हाल we might support RDMA, करोn't allow qede to be greedy
	 * with the L2 contexts. Allow क्रम 64 queues [rx, tx cos, xdp]
	 * per hwfn.
	 */
	अगर (QED_IS_RDMA_PERSONALITY(QED_LEADING_HWFN(cdev))) अणु
		u16 *num_cons;

		num_cons = &params->eth_pf_params.num_cons;
		*num_cons = min_t(u16, *num_cons, QED_MAX_L2_CONS);
	पूर्ण

	क्रम (i = 0; i < cdev->num_hwfns; i++) अणु
		काष्ठा qed_hwfn *p_hwfn = &cdev->hwfns[i];

		p_hwfn->pf_params = *params;
	पूर्ण
पूर्ण

#घोषणा QED_PERIODIC_DB_REC_COUNT		10
#घोषणा QED_PERIODIC_DB_REC_INTERVAL_MS		100
#घोषणा QED_PERIODIC_DB_REC_INTERVAL \
	msecs_to_jअगरfies(QED_PERIODIC_DB_REC_INTERVAL_MS)

अटल पूर्णांक qed_slowpath_delayed_work(काष्ठा qed_hwfn *hwfn,
				     क्रमागत qed_slowpath_wq_flag wq_flag,
				     अचिन्हित दीर्घ delay)
अणु
	अगर (!hwfn->slowpath_wq_active)
		वापस -EINVAL;

	/* Memory barrier क्रम setting atomic bit */
	smp_mb__beक्रमe_atomic();
	set_bit(wq_flag, &hwfn->slowpath_task_flags);
	smp_mb__after_atomic();
	queue_delayed_work(hwfn->slowpath_wq, &hwfn->slowpath_task, delay);

	वापस 0;
पूर्ण

व्योम qed_periodic_db_rec_start(काष्ठा qed_hwfn *p_hwfn)
अणु
	/* Reset periodic Doorbell Recovery counter */
	p_hwfn->periodic_db_rec_count = QED_PERIODIC_DB_REC_COUNT;

	/* Don't schedule periodic Doorbell Recovery अगर alपढ़ोy scheduled */
	अगर (test_bit(QED_SLOWPATH_PERIODIC_DB_REC,
		     &p_hwfn->slowpath_task_flags))
		वापस;

	qed_slowpath_delayed_work(p_hwfn, QED_SLOWPATH_PERIODIC_DB_REC,
				  QED_PERIODIC_DB_REC_INTERVAL);
पूर्ण

अटल व्योम qed_slowpath_wq_stop(काष्ठा qed_dev *cdev)
अणु
	पूर्णांक i;

	अगर (IS_VF(cdev))
		वापस;

	क्रम_each_hwfn(cdev, i) अणु
		अगर (!cdev->hwfns[i].slowpath_wq)
			जारी;

		/* Stop queuing new delayed works */
		cdev->hwfns[i].slowpath_wq_active = false;

		cancel_delayed_work(&cdev->hwfns[i].slowpath_task);
		destroy_workqueue(cdev->hwfns[i].slowpath_wq);
	पूर्ण
पूर्ण

अटल व्योम qed_slowpath_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qed_hwfn *hwfn = container_of(work, काष्ठा qed_hwfn,
					     slowpath_task.work);
	काष्ठा qed_ptt *ptt = qed_ptt_acquire(hwfn);

	अगर (!ptt) अणु
		अगर (hwfn->slowpath_wq_active)
			queue_delayed_work(hwfn->slowpath_wq,
					   &hwfn->slowpath_task, 0);

		वापस;
	पूर्ण

	अगर (test_and_clear_bit(QED_SLOWPATH_MFW_TLV_REQ,
			       &hwfn->slowpath_task_flags))
		qed_mfw_process_tlv_req(hwfn, ptt);

	अगर (test_and_clear_bit(QED_SLOWPATH_PERIODIC_DB_REC,
			       &hwfn->slowpath_task_flags)) अणु
		qed_db_rec_handler(hwfn, ptt);
		अगर (hwfn->periodic_db_rec_count--)
			qed_slowpath_delayed_work(hwfn,
						  QED_SLOWPATH_PERIODIC_DB_REC,
						  QED_PERIODIC_DB_REC_INTERVAL);
	पूर्ण

	qed_ptt_release(hwfn, ptt);
पूर्ण

अटल पूर्णांक qed_slowpath_wq_start(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *hwfn;
	अक्षर name[NAME_SIZE];
	पूर्णांक i;

	अगर (IS_VF(cdev))
		वापस 0;

	क्रम_each_hwfn(cdev, i) अणु
		hwfn = &cdev->hwfns[i];

		snम_लिखो(name, NAME_SIZE, "slowpath-%02x:%02x.%02x",
			 cdev->pdev->bus->number,
			 PCI_SLOT(cdev->pdev->devfn), hwfn->असल_pf_id);

		hwfn->slowpath_wq = alloc_workqueue(name, 0, 0);
		अगर (!hwfn->slowpath_wq) अणु
			DP_NOTICE(hwfn, "Cannot create slowpath workqueue\n");
			वापस -ENOMEM;
		पूर्ण

		INIT_DELAYED_WORK(&hwfn->slowpath_task, qed_slowpath_task);
		hwfn->slowpath_wq_active = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_slowpath_start(काष्ठा qed_dev *cdev,
			      काष्ठा qed_slowpath_params *params)
अणु
	काष्ठा qed_drv_load_params drv_load_params;
	काष्ठा qed_hw_init_params hw_init_params;
	काष्ठा qed_mcp_drv_version drv_version;
	काष्ठा qed_tunnel_info tunn_info;
	स्थिर u8 *data = शून्य;
	काष्ठा qed_hwfn *hwfn;
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = -EINVAL;

	अगर (qed_iov_wq_start(cdev))
		जाओ err;

	अगर (qed_slowpath_wq_start(cdev))
		जाओ err;

	अगर (IS_PF(cdev)) अणु
		rc = request_firmware(&cdev->firmware, QED_FW_खाता_NAME,
				      &cdev->pdev->dev);
		अगर (rc) अणु
			DP_NOTICE(cdev,
				  "Failed to find fw file - /lib/firmware/%s\n",
				  QED_FW_खाता_NAME);
			जाओ err;
		पूर्ण

		अगर (cdev->num_hwfns == 1) अणु
			p_ptt = qed_ptt_acquire(QED_LEADING_HWFN(cdev));
			अगर (p_ptt) अणु
				QED_LEADING_HWFN(cdev)->p_arfs_ptt = p_ptt;
			पूर्ण अन्यथा अणु
				DP_NOTICE(cdev,
					  "Failed to acquire PTT for aRFS\n");
				जाओ err;
			पूर्ण
		पूर्ण
	पूर्ण

	cdev->rx_coalesce_usecs = QED_DEFAULT_RX_USECS;
	rc = qed_nic_setup(cdev);
	अगर (rc)
		जाओ err;

	अगर (IS_PF(cdev))
		rc = qed_slowpath_setup_पूर्णांक(cdev, params->पूर्णांक_mode);
	अन्यथा
		rc = qed_slowpath_vf_setup_पूर्णांक(cdev);
	अगर (rc)
		जाओ err1;

	अगर (IS_PF(cdev)) अणु
		/* Allocate stream क्रम unzipping */
		rc = qed_alloc_stream_mem(cdev);
		अगर (rc)
			जाओ err2;

		/* First Dword used to dअगरferentiate between various sources */
		data = cdev->firmware->data + माप(u32);

		qed_dbg_pf_init(cdev);
	पूर्ण

	/* Start the slowpath */
	स_रखो(&hw_init_params, 0, माप(hw_init_params));
	स_रखो(&tunn_info, 0, माप(tunn_info));
	tunn_info.vxlan.b_mode_enabled = true;
	tunn_info.l2_gre.b_mode_enabled = true;
	tunn_info.ip_gre.b_mode_enabled = true;
	tunn_info.l2_geneve.b_mode_enabled = true;
	tunn_info.ip_geneve.b_mode_enabled = true;
	tunn_info.vxlan.tun_cls = QED_TUNN_CLSS_MAC_VLAN;
	tunn_info.l2_gre.tun_cls = QED_TUNN_CLSS_MAC_VLAN;
	tunn_info.ip_gre.tun_cls = QED_TUNN_CLSS_MAC_VLAN;
	tunn_info.l2_geneve.tun_cls = QED_TUNN_CLSS_MAC_VLAN;
	tunn_info.ip_geneve.tun_cls = QED_TUNN_CLSS_MAC_VLAN;
	hw_init_params.p_tunn = &tunn_info;
	hw_init_params.b_hw_start = true;
	hw_init_params.पूर्णांक_mode = cdev->पूर्णांक_params.out.पूर्णांक_mode;
	hw_init_params.allow_npar_tx_चयन = true;
	hw_init_params.bin_fw_data = data;

	स_रखो(&drv_load_params, 0, माप(drv_load_params));
	drv_load_params.is_crash_kernel = is_kdump_kernel();
	drv_load_params.mfw_समयout_val = QED_LOAD_REQ_LOCK_TO_DEFAULT;
	drv_load_params.aव्योम_eng_reset = false;
	drv_load_params.override_क्रमce_load = QED_OVERRIDE_FORCE_LOAD_NONE;
	hw_init_params.p_drv_load_params = &drv_load_params;

	rc = qed_hw_init(cdev, &hw_init_params);
	अगर (rc)
		जाओ err2;

	DP_INFO(cdev,
		"HW initialization and function start completed successfully\n");

	अगर (IS_PF(cdev)) अणु
		cdev->tunn_feature_mask = (BIT(QED_MODE_VXLAN_TUNN) |
					   BIT(QED_MODE_L2GENEVE_TUNN) |
					   BIT(QED_MODE_IPGENEVE_TUNN) |
					   BIT(QED_MODE_L2GRE_TUNN) |
					   BIT(QED_MODE_IPGRE_TUNN));
	पूर्ण

	/* Allocate LL2 पूर्णांकerface अगर needed */
	अगर (QED_LEADING_HWFN(cdev)->using_ll2) अणु
		rc = qed_ll2_alloc_अगर(cdev);
		अगर (rc)
			जाओ err3;
	पूर्ण
	अगर (IS_PF(cdev)) अणु
		hwfn = QED_LEADING_HWFN(cdev);
		drv_version.version = (params->drv_major << 24) |
				      (params->drv_minor << 16) |
				      (params->drv_rev << 8) |
				      (params->drv_eng);
		strlcpy(drv_version.name, params->name,
			MCP_DRV_VER_STR_SIZE - 4);
		rc = qed_mcp_send_drv_version(hwfn, hwfn->p_मुख्य_ptt,
					      &drv_version);
		अगर (rc) अणु
			DP_NOTICE(cdev, "Failed sending drv version command\n");
			जाओ err4;
		पूर्ण
	पूर्ण

	qed_reset_vport_stats(cdev);

	वापस 0;

err4:
	qed_ll2_dealloc_अगर(cdev);
err3:
	qed_hw_stop(cdev);
err2:
	qed_hw_समयrs_stop_all(cdev);
	अगर (IS_PF(cdev))
		qed_slowpath_irq_मुक्त(cdev);
	qed_मुक्त_stream_mem(cdev);
	qed_disable_msix(cdev);
err1:
	qed_resc_मुक्त(cdev);
err:
	अगर (IS_PF(cdev))
		release_firmware(cdev->firmware);

	अगर (IS_PF(cdev) && (cdev->num_hwfns == 1) &&
	    QED_LEADING_HWFN(cdev)->p_arfs_ptt)
		qed_ptt_release(QED_LEADING_HWFN(cdev),
				QED_LEADING_HWFN(cdev)->p_arfs_ptt);

	qed_iov_wq_stop(cdev, false);

	qed_slowpath_wq_stop(cdev);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_slowpath_stop(काष्ठा qed_dev *cdev)
अणु
	अगर (!cdev)
		वापस -ENODEV;

	qed_slowpath_wq_stop(cdev);

	qed_ll2_dealloc_अगर(cdev);

	अगर (IS_PF(cdev)) अणु
		अगर (cdev->num_hwfns == 1)
			qed_ptt_release(QED_LEADING_HWFN(cdev),
					QED_LEADING_HWFN(cdev)->p_arfs_ptt);
		qed_मुक्त_stream_mem(cdev);
		अगर (IS_QED_ETH_IF(cdev))
			qed_sriov_disable(cdev, true);
	पूर्ण

	qed_nic_stop(cdev);

	अगर (IS_PF(cdev))
		qed_slowpath_irq_मुक्त(cdev);

	qed_disable_msix(cdev);

	qed_resc_मुक्त(cdev);

	qed_iov_wq_stop(cdev, true);

	अगर (IS_PF(cdev))
		release_firmware(cdev->firmware);

	वापस 0;
पूर्ण

अटल व्योम qed_set_name(काष्ठा qed_dev *cdev, अक्षर name[NAME_SIZE])
अणु
	पूर्णांक i;

	स_नकल(cdev->name, name, NAME_SIZE);
	क्रम_each_hwfn(cdev, i)
		snम_लिखो(cdev->hwfns[i].name, NAME_SIZE, "%s-%d", name, i);
पूर्ण

अटल u32 qed_sb_init(काष्ठा qed_dev *cdev,
		       काष्ठा qed_sb_info *sb_info,
		       व्योम *sb_virt_addr,
		       dma_addr_t sb_phy_addr, u16 sb_id,
		       क्रमागत qed_sb_type type)
अणु
	काष्ठा qed_hwfn *p_hwfn;
	काष्ठा qed_ptt *p_ptt;
	u16 rel_sb_id;
	u32 rc;

	/* RoCE/Storage use a single engine in CMT mode जबतक L2 uses both */
	अगर (type == QED_SB_TYPE_L2_QUEUE) अणु
		p_hwfn = &cdev->hwfns[sb_id % cdev->num_hwfns];
		rel_sb_id = sb_id / cdev->num_hwfns;
	पूर्ण अन्यथा अणु
		p_hwfn = QED_AFFIN_HWFN(cdev);
		rel_sb_id = sb_id;
	पूर्ण

	DP_VERBOSE(cdev, NETIF_MSG_INTR,
		   "hwfn [%d] <--[init]-- SB %04x [0x%04x upper]\n",
		   IS_LEAD_HWFN(p_hwfn) ? 0 : 1, rel_sb_id, sb_id);

	अगर (IS_PF(p_hwfn->cdev)) अणु
		p_ptt = qed_ptt_acquire(p_hwfn);
		अगर (!p_ptt)
			वापस -EBUSY;

		rc = qed_पूर्णांक_sb_init(p_hwfn, p_ptt, sb_info, sb_virt_addr,
				     sb_phy_addr, rel_sb_id);
		qed_ptt_release(p_hwfn, p_ptt);
	पूर्ण अन्यथा अणु
		rc = qed_पूर्णांक_sb_init(p_hwfn, शून्य, sb_info, sb_virt_addr,
				     sb_phy_addr, rel_sb_id);
	पूर्ण

	वापस rc;
पूर्ण

अटल u32 qed_sb_release(काष्ठा qed_dev *cdev,
			  काष्ठा qed_sb_info *sb_info,
			  u16 sb_id,
			  क्रमागत qed_sb_type type)
अणु
	काष्ठा qed_hwfn *p_hwfn;
	u16 rel_sb_id;
	u32 rc;

	/* RoCE/Storage use a single engine in CMT mode जबतक L2 uses both */
	अगर (type == QED_SB_TYPE_L2_QUEUE) अणु
		p_hwfn = &cdev->hwfns[sb_id % cdev->num_hwfns];
		rel_sb_id = sb_id / cdev->num_hwfns;
	पूर्ण अन्यथा अणु
		p_hwfn = QED_AFFIN_HWFN(cdev);
		rel_sb_id = sb_id;
	पूर्ण

	DP_VERBOSE(cdev, NETIF_MSG_INTR,
		   "hwfn [%d] <--[init]-- SB %04x [0x%04x upper]\n",
		   IS_LEAD_HWFN(p_hwfn) ? 0 : 1, rel_sb_id, sb_id);

	rc = qed_पूर्णांक_sb_release(p_hwfn, sb_info, rel_sb_id);

	वापस rc;
पूर्ण

अटल bool qed_can_link_change(काष्ठा qed_dev *cdev)
अणु
	वापस true;
पूर्ण

अटल व्योम qed_set_ext_speed_params(काष्ठा qed_mcp_link_params *link_params,
				     स्थिर काष्ठा qed_link_params *params)
अणु
	काष्ठा qed_mcp_link_speed_params *ext_speed = &link_params->ext_speed;
	स्थिर काष्ठा qed_mfw_speed_map *map;
	u32 i;

	अगर (params->override_flags & QED_LINK_OVERRIDE_SPEED_AUTONEG)
		ext_speed->स्वतःneg = !!params->स्वतःneg;

	अगर (params->override_flags & QED_LINK_OVERRIDE_SPEED_ADV_SPEEDS) अणु
		ext_speed->advertised_speeds = 0;

		क्रम (i = 0; i < ARRAY_SIZE(qed_mfw_ext_maps); i++) अणु
			map = qed_mfw_ext_maps + i;

			अगर (linkmode_पूर्णांकersects(params->adv_speeds, map->caps))
				ext_speed->advertised_speeds |= map->mfw_val;
		पूर्ण
	पूर्ण

	अगर (params->override_flags & QED_LINK_OVERRIDE_SPEED_FORCED_SPEED) अणु
		चयन (params->क्रमced_speed) अणु
		हाल SPEED_1000:
			ext_speed->क्रमced_speed = QED_EXT_SPEED_1G;
			अवरोध;
		हाल SPEED_10000:
			ext_speed->क्रमced_speed = QED_EXT_SPEED_10G;
			अवरोध;
		हाल SPEED_20000:
			ext_speed->क्रमced_speed = QED_EXT_SPEED_20G;
			अवरोध;
		हाल SPEED_25000:
			ext_speed->क्रमced_speed = QED_EXT_SPEED_25G;
			अवरोध;
		हाल SPEED_40000:
			ext_speed->क्रमced_speed = QED_EXT_SPEED_40G;
			अवरोध;
		हाल SPEED_50000:
			ext_speed->क्रमced_speed = QED_EXT_SPEED_50G_R |
						  QED_EXT_SPEED_50G_R2;
			अवरोध;
		हाल SPEED_100000:
			ext_speed->क्रमced_speed = QED_EXT_SPEED_100G_R2 |
						  QED_EXT_SPEED_100G_R4 |
						  QED_EXT_SPEED_100G_P4;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!(params->override_flags & QED_LINK_OVERRIDE_FEC_CONFIG))
		वापस;

	चयन (params->क्रमced_speed) अणु
	हाल SPEED_25000:
		चयन (params->fec) अणु
		हाल FEC_FORCE_MODE_NONE:
			link_params->ext_fec_mode = ETH_EXT_FEC_25G_NONE;
			अवरोध;
		हाल FEC_FORCE_MODE_FIRECODE:
			link_params->ext_fec_mode = ETH_EXT_FEC_25G_BASE_R;
			अवरोध;
		हाल FEC_FORCE_MODE_RS:
			link_params->ext_fec_mode = ETH_EXT_FEC_25G_RS528;
			अवरोध;
		हाल FEC_FORCE_MODE_AUTO:
			link_params->ext_fec_mode = ETH_EXT_FEC_25G_RS528 |
						    ETH_EXT_FEC_25G_BASE_R |
						    ETH_EXT_FEC_25G_NONE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अवरोध;
	हाल SPEED_40000:
		चयन (params->fec) अणु
		हाल FEC_FORCE_MODE_NONE:
			link_params->ext_fec_mode = ETH_EXT_FEC_40G_NONE;
			अवरोध;
		हाल FEC_FORCE_MODE_FIRECODE:
			link_params->ext_fec_mode = ETH_EXT_FEC_40G_BASE_R;
			अवरोध;
		हाल FEC_FORCE_MODE_AUTO:
			link_params->ext_fec_mode = ETH_EXT_FEC_40G_BASE_R |
						    ETH_EXT_FEC_40G_NONE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अवरोध;
	हाल SPEED_50000:
		चयन (params->fec) अणु
		हाल FEC_FORCE_MODE_NONE:
			link_params->ext_fec_mode = ETH_EXT_FEC_50G_NONE;
			अवरोध;
		हाल FEC_FORCE_MODE_FIRECODE:
			link_params->ext_fec_mode = ETH_EXT_FEC_50G_BASE_R;
			अवरोध;
		हाल FEC_FORCE_MODE_RS:
			link_params->ext_fec_mode = ETH_EXT_FEC_50G_RS528;
			अवरोध;
		हाल FEC_FORCE_MODE_AUTO:
			link_params->ext_fec_mode = ETH_EXT_FEC_50G_RS528 |
						    ETH_EXT_FEC_50G_BASE_R |
						    ETH_EXT_FEC_50G_NONE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अवरोध;
	हाल SPEED_100000:
		चयन (params->fec) अणु
		हाल FEC_FORCE_MODE_NONE:
			link_params->ext_fec_mode = ETH_EXT_FEC_100G_NONE;
			अवरोध;
		हाल FEC_FORCE_MODE_FIRECODE:
			link_params->ext_fec_mode = ETH_EXT_FEC_100G_BASE_R;
			अवरोध;
		हाल FEC_FORCE_MODE_RS:
			link_params->ext_fec_mode = ETH_EXT_FEC_100G_RS528;
			अवरोध;
		हाल FEC_FORCE_MODE_AUTO:
			link_params->ext_fec_mode = ETH_EXT_FEC_100G_RS528 |
						    ETH_EXT_FEC_100G_BASE_R |
						    ETH_EXT_FEC_100G_NONE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक qed_set_link(काष्ठा qed_dev *cdev, काष्ठा qed_link_params *params)
अणु
	काष्ठा qed_mcp_link_params *link_params;
	काष्ठा qed_mcp_link_speed_params *speed;
	स्थिर काष्ठा qed_mfw_speed_map *map;
	काष्ठा qed_hwfn *hwfn;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;
	u32 i;

	अगर (!cdev)
		वापस -ENODEV;

	/* The link should be set only once per PF */
	hwfn = &cdev->hwfns[0];

	/* When VF wants to set link, क्रमce it to पढ़ो the bulletin instead.
	 * This mimics the PF behavior, where a noitअगरication [both immediate
	 * and possible later] would be generated when changing properties.
	 */
	अगर (IS_VF(cdev)) अणु
		qed_schedule_iov(hwfn, QED_IOV_WQ_VF_FORCE_LINK_QUERY_FLAG);
		वापस 0;
	पूर्ण

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EBUSY;

	link_params = qed_mcp_get_link_params(hwfn);
	अगर (!link_params)
		वापस -ENODATA;

	speed = &link_params->speed;

	अगर (params->override_flags & QED_LINK_OVERRIDE_SPEED_AUTONEG)
		speed->स्वतःneg = !!params->स्वतःneg;

	अगर (params->override_flags & QED_LINK_OVERRIDE_SPEED_ADV_SPEEDS) अणु
		speed->advertised_speeds = 0;

		क्रम (i = 0; i < ARRAY_SIZE(qed_mfw_legacy_maps); i++) अणु
			map = qed_mfw_legacy_maps + i;

			अगर (linkmode_पूर्णांकersects(params->adv_speeds, map->caps))
				speed->advertised_speeds |= map->mfw_val;
		पूर्ण
	पूर्ण

	अगर (params->override_flags & QED_LINK_OVERRIDE_SPEED_FORCED_SPEED)
		speed->क्रमced_speed = params->क्रमced_speed;

	अगर (qed_mcp_is_ext_speed_supported(hwfn))
		qed_set_ext_speed_params(link_params, params);

	अगर (params->override_flags & QED_LINK_OVERRIDE_PAUSE_CONFIG) अणु
		अगर (params->छोड़ो_config & QED_LINK_PAUSE_AUTONEG_ENABLE)
			link_params->छोड़ो.स्वतःneg = true;
		अन्यथा
			link_params->छोड़ो.स्वतःneg = false;
		अगर (params->छोड़ो_config & QED_LINK_PAUSE_RX_ENABLE)
			link_params->छोड़ो.क्रमced_rx = true;
		अन्यथा
			link_params->छोड़ो.क्रमced_rx = false;
		अगर (params->छोड़ो_config & QED_LINK_PAUSE_TX_ENABLE)
			link_params->छोड़ो.क्रमced_tx = true;
		अन्यथा
			link_params->छोड़ो.क्रमced_tx = false;
	पूर्ण

	अगर (params->override_flags & QED_LINK_OVERRIDE_LOOPBACK_MODE) अणु
		चयन (params->loopback_mode) अणु
		हाल QED_LINK_LOOPBACK_INT_PHY:
			link_params->loopback_mode = ETH_LOOPBACK_INT_PHY;
			अवरोध;
		हाल QED_LINK_LOOPBACK_EXT_PHY:
			link_params->loopback_mode = ETH_LOOPBACK_EXT_PHY;
			अवरोध;
		हाल QED_LINK_LOOPBACK_EXT:
			link_params->loopback_mode = ETH_LOOPBACK_EXT;
			अवरोध;
		हाल QED_LINK_LOOPBACK_MAC:
			link_params->loopback_mode = ETH_LOOPBACK_MAC;
			अवरोध;
		हाल QED_LINK_LOOPBACK_CNIG_AH_ONLY_0123:
			link_params->loopback_mode =
				ETH_LOOPBACK_CNIG_AH_ONLY_0123;
			अवरोध;
		हाल QED_LINK_LOOPBACK_CNIG_AH_ONLY_2301:
			link_params->loopback_mode =
				ETH_LOOPBACK_CNIG_AH_ONLY_2301;
			अवरोध;
		हाल QED_LINK_LOOPBACK_PCS_AH_ONLY:
			link_params->loopback_mode = ETH_LOOPBACK_PCS_AH_ONLY;
			अवरोध;
		हाल QED_LINK_LOOPBACK_REVERSE_MAC_AH_ONLY:
			link_params->loopback_mode =
				ETH_LOOPBACK_REVERSE_MAC_AH_ONLY;
			अवरोध;
		हाल QED_LINK_LOOPBACK_INT_PHY_FEA_AH_ONLY:
			link_params->loopback_mode =
				ETH_LOOPBACK_INT_PHY_FEA_AH_ONLY;
			अवरोध;
		शेष:
			link_params->loopback_mode = ETH_LOOPBACK_NONE;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (params->override_flags & QED_LINK_OVERRIDE_EEE_CONFIG)
		स_नकल(&link_params->eee, &params->eee,
		       माप(link_params->eee));

	अगर (params->override_flags & QED_LINK_OVERRIDE_FEC_CONFIG)
		link_params->fec = params->fec;

	rc = qed_mcp_set_link(hwfn, ptt, params->link_up);

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_get_port_type(u32 media_type)
अणु
	पूर्णांक port_type;

	चयन (media_type) अणु
	हाल MEDIA_SFPP_10G_FIBER:
	हाल MEDIA_SFP_1G_FIBER:
	हाल MEDIA_XFP_FIBER:
	हाल MEDIA_MODULE_FIBER:
		port_type = PORT_FIBRE;
		अवरोध;
	हाल MEDIA_DA_TWINAX:
		port_type = PORT_DA;
		अवरोध;
	हाल MEDIA_BASE_T:
		port_type = PORT_TP;
		अवरोध;
	हाल MEDIA_KR:
	हाल MEDIA_NOT_PRESENT:
		port_type = PORT_NONE;
		अवरोध;
	हाल MEDIA_UNSPECIFIED:
	शेष:
		port_type = PORT_OTHER;
		अवरोध;
	पूर्ण
	वापस port_type;
पूर्ण

अटल पूर्णांक qed_get_link_data(काष्ठा qed_hwfn *hwfn,
			     काष्ठा qed_mcp_link_params *params,
			     काष्ठा qed_mcp_link_state *link,
			     काष्ठा qed_mcp_link_capabilities *link_caps)
अणु
	व्योम *p;

	अगर (!IS_PF(hwfn->cdev)) अणु
		qed_vf_get_link_params(hwfn, params);
		qed_vf_get_link_state(hwfn, link);
		qed_vf_get_link_caps(hwfn, link_caps);

		वापस 0;
	पूर्ण

	p = qed_mcp_get_link_params(hwfn);
	अगर (!p)
		वापस -ENXIO;
	स_नकल(params, p, माप(*params));

	p = qed_mcp_get_link_state(hwfn);
	अगर (!p)
		वापस -ENXIO;
	स_नकल(link, p, माप(*link));

	p = qed_mcp_get_link_capabilities(hwfn);
	अगर (!p)
		वापस -ENXIO;
	स_नकल(link_caps, p, माप(*link_caps));

	वापस 0;
पूर्ण

अटल व्योम qed_fill_link_capability(काष्ठा qed_hwfn *hwfn,
				     काष्ठा qed_ptt *ptt, u32 capability,
				     अचिन्हित दीर्घ *अगर_caps)
अणु
	u32 media_type, tcvr_state, tcvr_type;
	u32 speed_mask, board_cfg;

	अगर (qed_mcp_get_media_type(hwfn, ptt, &media_type))
		media_type = MEDIA_UNSPECIFIED;

	अगर (qed_mcp_get_transceiver_data(hwfn, ptt, &tcvr_state, &tcvr_type))
		tcvr_type = ETH_TRANSCEIVER_STATE_UNPLUGGED;

	अगर (qed_mcp_trans_speed_mask(hwfn, ptt, &speed_mask))
		speed_mask = 0xFFFFFFFF;

	अगर (qed_mcp_get_board_config(hwfn, ptt, &board_cfg))
		board_cfg = NVM_CFG1_PORT_PORT_TYPE_UNDEFINED;

	DP_VERBOSE(hwfn->cdev, NETIF_MSG_DRV,
		   "Media_type = 0x%x tcvr_state = 0x%x tcvr_type = 0x%x speed_mask = 0x%x board_cfg = 0x%x\n",
		   media_type, tcvr_state, tcvr_type, speed_mask, board_cfg);

	चयन (media_type) अणु
	हाल MEDIA_DA_TWINAX:
		phylink_set(अगर_caps, FIBRE);

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G)
			phylink_set(अगर_caps, 20000baseKR2_Full);

		/* For DAC media multiple speed capabilities are supported */
		capability |= speed_mask;

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G)
			phylink_set(अगर_caps, 1000baseKX_Full);
		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G)
			phylink_set(अगर_caps, 10000baseCR_Full);

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G)
			चयन (tcvr_type) अणु
			हाल ETH_TRANSCEIVER_TYPE_40G_CR4:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_CR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_CR:
				phylink_set(अगर_caps, 40000baseCR4_Full);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G)
			phylink_set(अगर_caps, 25000baseCR_Full);
		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G)
			phylink_set(अगर_caps, 50000baseCR2_Full);

		अगर (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G)
			चयन (tcvr_type) अणु
			हाल ETH_TRANSCEIVER_TYPE_100G_CR4:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_CR:
				phylink_set(अगर_caps, 100000baseCR4_Full);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

		अवरोध;
	हाल MEDIA_BASE_T:
		phylink_set(अगर_caps, TP);

		अगर (board_cfg & NVM_CFG1_PORT_PORT_TYPE_EXT_PHY) अणु
			अगर (capability &
			    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G)
				phylink_set(अगर_caps, 1000baseT_Full);
			अगर (capability &
			    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G)
				phylink_set(अगर_caps, 10000baseT_Full);
		पूर्ण

		अगर (board_cfg & NVM_CFG1_PORT_PORT_TYPE_MODULE) अणु
			phylink_set(अगर_caps, FIBRE);

			चयन (tcvr_type) अणु
			हाल ETH_TRANSCEIVER_TYPE_1000BASET:
				phylink_set(अगर_caps, 1000baseT_Full);
				अवरोध;
			हाल ETH_TRANSCEIVER_TYPE_10G_BASET:
				phylink_set(अगर_caps, 10000baseT_Full);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		अवरोध;
	हाल MEDIA_SFP_1G_FIBER:
	हाल MEDIA_SFPP_10G_FIBER:
	हाल MEDIA_XFP_FIBER:
	हाल MEDIA_MODULE_FIBER:
		phylink_set(अगर_caps, FIBRE);
		capability |= speed_mask;

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G)
			चयन (tcvr_type) अणु
			हाल ETH_TRANSCEIVER_TYPE_1G_LX:
			हाल ETH_TRANSCEIVER_TYPE_1G_SX:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_1G_10G_SR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_1G_10G_LR:
				phylink_set(अगर_caps, 1000baseKX_Full);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G)
			चयन (tcvr_type) अणु
			हाल ETH_TRANSCEIVER_TYPE_10G_SR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_SR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_25G_SR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_1G_10G_SR:
				phylink_set(अगर_caps, 10000baseSR_Full);
				अवरोध;
			हाल ETH_TRANSCEIVER_TYPE_10G_LR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_LR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_25G_LR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_1G_10G_LR:
				phylink_set(अगर_caps, 10000baseLR_Full);
				अवरोध;
			हाल ETH_TRANSCEIVER_TYPE_10G_LRM:
				phylink_set(अगर_caps, 10000baseLRM_Full);
				अवरोध;
			हाल ETH_TRANSCEIVER_TYPE_10G_ER:
				phylink_set(अगर_caps, 10000baseR_FEC);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G)
			phylink_set(अगर_caps, 20000baseKR2_Full);

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G)
			चयन (tcvr_type) अणु
			हाल ETH_TRANSCEIVER_TYPE_25G_SR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_25G_SR:
				phylink_set(अगर_caps, 25000baseSR_Full);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G)
			चयन (tcvr_type) अणु
			हाल ETH_TRANSCEIVER_TYPE_40G_LR4:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_LR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_LR:
				phylink_set(अगर_caps, 40000baseLR4_Full);
				अवरोध;
			हाल ETH_TRANSCEIVER_TYPE_40G_SR4:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_SR:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_10G_40G_SR:
				phylink_set(अगर_caps, 40000baseSR4_Full);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G)
			phylink_set(अगर_caps, 50000baseKR2_Full);

		अगर (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G)
			चयन (tcvr_type) अणु
			हाल ETH_TRANSCEIVER_TYPE_100G_SR4:
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_SR:
				phylink_set(अगर_caps, 100000baseSR4_Full);
				अवरोध;
			हाल ETH_TRANSCEIVER_TYPE_MULTI_RATE_40G_100G_LR:
				phylink_set(अगर_caps, 100000baseLR4_ER4_Full);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

		अवरोध;
	हाल MEDIA_KR:
		phylink_set(अगर_caps, Backplane);

		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G)
			phylink_set(अगर_caps, 20000baseKR2_Full);
		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G)
			phylink_set(अगर_caps, 1000baseKX_Full);
		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G)
			phylink_set(अगर_caps, 10000baseKR_Full);
		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G)
			phylink_set(अगर_caps, 25000baseKR_Full);
		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G)
			phylink_set(अगर_caps, 40000baseKR4_Full);
		अगर (capability & NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G)
			phylink_set(अगर_caps, 50000baseKR2_Full);
		अगर (capability &
		    NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G)
			phylink_set(अगर_caps, 100000baseKR4_Full);

		अवरोध;
	हाल MEDIA_UNSPECIFIED:
	हाल MEDIA_NOT_PRESENT:
	शेष:
		DP_VERBOSE(hwfn->cdev, QED_MSG_DEBUG,
			   "Unknown media and transceiver type;\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qed_lp_caps_to_speed_mask(u32 caps, u32 *speed_mask)
अणु
	*speed_mask = 0;

	अगर (caps &
	    (QED_LINK_PARTNER_SPEED_1G_FD | QED_LINK_PARTNER_SPEED_1G_HD))
		*speed_mask |= NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_1G;
	अगर (caps & QED_LINK_PARTNER_SPEED_10G)
		*speed_mask |= NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_10G;
	अगर (caps & QED_LINK_PARTNER_SPEED_20G)
		*speed_mask |= NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_20G;
	अगर (caps & QED_LINK_PARTNER_SPEED_25G)
		*speed_mask |= NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_25G;
	अगर (caps & QED_LINK_PARTNER_SPEED_40G)
		*speed_mask |= NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_40G;
	अगर (caps & QED_LINK_PARTNER_SPEED_50G)
		*speed_mask |= NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_50G;
	अगर (caps & QED_LINK_PARTNER_SPEED_100G)
		*speed_mask |= NVM_CFG1_PORT_DRV_SPEED_CAPABILITY_MASK_BB_100G;
पूर्ण

अटल व्योम qed_fill_link(काष्ठा qed_hwfn *hwfn,
			  काष्ठा qed_ptt *ptt,
			  काष्ठा qed_link_output *अगर_link)
अणु
	काष्ठा qed_mcp_link_capabilities link_caps;
	काष्ठा qed_mcp_link_params params;
	काष्ठा qed_mcp_link_state link;
	u32 media_type, speed_mask;

	स_रखो(अगर_link, 0, माप(*अगर_link));

	/* Prepare source inमाला_दो */
	अगर (qed_get_link_data(hwfn, &params, &link, &link_caps)) अणु
		dev_warn(&hwfn->cdev->pdev->dev, "no link data available\n");
		वापस;
	पूर्ण

	/* Set the link parameters to pass to protocol driver */
	अगर (link.link_up)
		अगर_link->link_up = true;

	अगर (IS_PF(hwfn->cdev) && qed_mcp_is_ext_speed_supported(hwfn)) अणु
		अगर (link_caps.शेष_ext_स्वतःneg)
			phylink_set(अगर_link->supported_caps, Autoneg);

		linkmode_copy(अगर_link->advertised_caps, अगर_link->supported_caps);

		अगर (params.ext_speed.स्वतःneg)
			phylink_set(अगर_link->advertised_caps, Autoneg);
		अन्यथा
			phylink_clear(अगर_link->advertised_caps, Autoneg);

		qed_fill_link_capability(hwfn, ptt,
					 params.ext_speed.advertised_speeds,
					 अगर_link->advertised_caps);
	पूर्ण अन्यथा अणु
		अगर (link_caps.शेष_speed_स्वतःneg)
			phylink_set(अगर_link->supported_caps, Autoneg);

		linkmode_copy(अगर_link->advertised_caps, अगर_link->supported_caps);

		अगर (params.speed.स्वतःneg)
			phylink_set(अगर_link->advertised_caps, Autoneg);
		अन्यथा
			phylink_clear(अगर_link->advertised_caps, Autoneg);
	पूर्ण

	अगर (params.छोड़ो.स्वतःneg ||
	    (params.छोड़ो.क्रमced_rx && params.छोड़ो.क्रमced_tx))
		phylink_set(अगर_link->supported_caps, Asym_Pause);
	अगर (params.छोड़ो.स्वतःneg || params.छोड़ो.क्रमced_rx ||
	    params.छोड़ो.क्रमced_tx)
		phylink_set(अगर_link->supported_caps, Pause);

	अगर_link->sup_fec = link_caps.fec_शेष;
	अगर_link->active_fec = params.fec;

	/* Fill link advertised capability */
	qed_fill_link_capability(hwfn, ptt, params.speed.advertised_speeds,
				 अगर_link->advertised_caps);

	/* Fill link supported capability */
	qed_fill_link_capability(hwfn, ptt, link_caps.speed_capabilities,
				 अगर_link->supported_caps);

	/* Fill partner advertised capability */
	qed_lp_caps_to_speed_mask(link.partner_adv_speed, &speed_mask);
	qed_fill_link_capability(hwfn, ptt, speed_mask, अगर_link->lp_caps);

	अगर (link.link_up)
		अगर_link->speed = link.speed;

	/* TODO - fill duplex properly */
	अगर_link->duplex = DUPLEX_FULL;
	qed_mcp_get_media_type(hwfn, ptt, &media_type);
	अगर_link->port = qed_get_port_type(media_type);

	अगर_link->स्वतःneg = params.speed.स्वतःneg;

	अगर (params.छोड़ो.स्वतःneg)
		अगर_link->छोड़ो_config |= QED_LINK_PAUSE_AUTONEG_ENABLE;
	अगर (params.छोड़ो.क्रमced_rx)
		अगर_link->छोड़ो_config |= QED_LINK_PAUSE_RX_ENABLE;
	अगर (params.छोड़ो.क्रमced_tx)
		अगर_link->छोड़ो_config |= QED_LINK_PAUSE_TX_ENABLE;

	अगर (link.an_complete)
		phylink_set(अगर_link->lp_caps, Autoneg);
	अगर (link.partner_adv_छोड़ो)
		phylink_set(अगर_link->lp_caps, Pause);
	अगर (link.partner_adv_छोड़ो == QED_LINK_PARTNER_ASYMMETRIC_PAUSE ||
	    link.partner_adv_छोड़ो == QED_LINK_PARTNER_BOTH_PAUSE)
		phylink_set(अगर_link->lp_caps, Asym_Pause);

	अगर (link_caps.शेष_eee == QED_MCP_EEE_UNSUPPORTED) अणु
		अगर_link->eee_supported = false;
	पूर्ण अन्यथा अणु
		अगर_link->eee_supported = true;
		अगर_link->eee_active = link.eee_active;
		अगर_link->sup_caps = link_caps.eee_speed_caps;
		/* MFW clears adv_caps on eee disable; use configured value */
		अगर_link->eee.adv_caps = link.eee_adv_caps ? link.eee_adv_caps :
					params.eee.adv_caps;
		अगर_link->eee.lp_adv_caps = link.eee_lp_adv_caps;
		अगर_link->eee.enable = params.eee.enable;
		अगर_link->eee.tx_lpi_enable = params.eee.tx_lpi_enable;
		अगर_link->eee.tx_lpi_समयr = params.eee.tx_lpi_समयr;
	पूर्ण
पूर्ण

अटल व्योम qed_get_current_link(काष्ठा qed_dev *cdev,
				 काष्ठा qed_link_output *अगर_link)
अणु
	काष्ठा qed_hwfn *hwfn;
	काष्ठा qed_ptt *ptt;
	पूर्णांक i;

	hwfn = &cdev->hwfns[0];
	अगर (IS_PF(cdev)) अणु
		ptt = qed_ptt_acquire(hwfn);
		अगर (ptt) अणु
			qed_fill_link(hwfn, ptt, अगर_link);
			qed_ptt_release(hwfn, ptt);
		पूर्ण अन्यथा अणु
			DP_NOTICE(hwfn, "Failed to fill link; No PTT\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		qed_fill_link(hwfn, शून्य, अगर_link);
	पूर्ण

	क्रम_each_hwfn(cdev, i)
		qed_inक्रमm_vf_link_state(&cdev->hwfns[i]);
पूर्ण

व्योम qed_link_update(काष्ठा qed_hwfn *hwfn, काष्ठा qed_ptt *ptt)
अणु
	व्योम *cookie = hwfn->cdev->ops_cookie;
	काष्ठा qed_common_cb_ops *op = hwfn->cdev->protocol_ops.common;
	काष्ठा qed_link_output अगर_link;

	qed_fill_link(hwfn, ptt, &अगर_link);
	qed_inक्रमm_vf_link_state(hwfn);

	अगर (IS_LEAD_HWFN(hwfn) && cookie)
		op->link_update(cookie, &अगर_link);
पूर्ण

व्योम qed_bw_update(काष्ठा qed_hwfn *hwfn, काष्ठा qed_ptt *ptt)
अणु
	व्योम *cookie = hwfn->cdev->ops_cookie;
	काष्ठा qed_common_cb_ops *op = hwfn->cdev->protocol_ops.common;

	अगर (IS_LEAD_HWFN(hwfn) && cookie && op && op->bw_update)
		op->bw_update(cookie);
पूर्ण

अटल पूर्णांक qed_drain(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *hwfn;
	काष्ठा qed_ptt *ptt;
	पूर्णांक i, rc;

	अगर (IS_VF(cdev))
		वापस 0;

	क्रम_each_hwfn(cdev, i) अणु
		hwfn = &cdev->hwfns[i];
		ptt = qed_ptt_acquire(hwfn);
		अगर (!ptt) अणु
			DP_NOTICE(hwfn, "Failed to drain NIG; No PTT\n");
			वापस -EBUSY;
		पूर्ण
		rc = qed_mcp_drain(hwfn, ptt);
		qed_ptt_release(hwfn, ptt);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 qed_nvm_flash_image_access_crc(काष्ठा qed_dev *cdev,
					  काष्ठा qed_nvm_image_att *nvm_image,
					  u32 *crc)
अणु
	u8 *buf = शून्य;
	पूर्णांक rc;

	/* Allocate a buffer क्रम holding the nvram image */
	buf = kzalloc(nvm_image->length, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	/* Read image पूर्णांकo buffer */
	rc = qed_mcp_nvm_पढ़ो(cdev, nvm_image->start_addr,
			      buf, nvm_image->length);
	अगर (rc) अणु
		DP_ERR(cdev, "Failed reading image from nvm\n");
		जाओ out;
	पूर्ण

	/* Convert the buffer पूर्णांकo big-endian क्रमmat (excluding the
	 * closing 4 bytes of CRC).
	 */
	cpu_to_be32_array((__क्रमce __be32 *)buf, (स्थिर u32 *)buf,
			  DIV_ROUND_UP(nvm_image->length - 4, 4));

	/* Calc CRC क्रम the "actual" image buffer, i.e. not including
	 * the last 4 CRC bytes.
	 */
	*crc = ~crc32(~0U, buf, nvm_image->length - 4);
	*crc = (__क्रमce u32)cpu_to_be32p(crc);

out:
	kमुक्त(buf);

	वापस rc;
पूर्ण

/* Binary file क्रमmat -
 *     /----------------------------------------------------------------------\
 * 0B  |                       0x4 [command index]                            |
 * 4B  | image_type     | Options        |  Number of रेजिस्टर settings       |
 * 8B  |                       Value                                          |
 * 12B |                       Mask                                           |
 * 16B |                       Offset                                         |
 *     \----------------------------------------------------------------------/
 * There can be several Value-Mask-Offset sets as specअगरied by 'Number of...'.
 * Options - 0'b - Calculate & Update CRC क्रम image
 */
अटल पूर्णांक qed_nvm_flash_image_access(काष्ठा qed_dev *cdev, स्थिर u8 **data,
				      bool *check_resp)
अणु
	काष्ठा qed_nvm_image_att nvm_image;
	काष्ठा qed_hwfn *p_hwfn;
	bool is_crc = false;
	u32 image_type;
	पूर्णांक rc = 0, i;
	u16 len;

	*data += 4;
	image_type = **data;
	p_hwfn = QED_LEADING_HWFN(cdev);
	क्रम (i = 0; i < p_hwfn->nvm_info.num_images; i++)
		अगर (image_type == p_hwfn->nvm_info.image_att[i].image_type)
			अवरोध;
	अगर (i == p_hwfn->nvm_info.num_images) अणु
		DP_ERR(cdev, "Failed to find nvram image of type %08x\n",
		       image_type);
		वापस -ENOENT;
	पूर्ण

	nvm_image.start_addr = p_hwfn->nvm_info.image_att[i].nvm_start_addr;
	nvm_image.length = p_hwfn->nvm_info.image_att[i].len;

	DP_VERBOSE(cdev, NETIF_MSG_DRV,
		   "Read image %02x; type = %08x; NVM [%08x,...,%08x]\n",
		   **data, image_type, nvm_image.start_addr,
		   nvm_image.start_addr + nvm_image.length - 1);
	(*data)++;
	is_crc = !!(**data & BIT(0));
	(*data)++;
	len = *((u16 *)*data);
	*data += 2;
	अगर (is_crc) अणु
		u32 crc = 0;

		rc = qed_nvm_flash_image_access_crc(cdev, &nvm_image, &crc);
		अगर (rc) अणु
			DP_ERR(cdev, "Failed calculating CRC, rc = %d\n", rc);
			जाओ निकास;
		पूर्ण

		rc = qed_mcp_nvm_ग_लिखो(cdev, QED_NVM_WRITE_NVRAM,
				       (nvm_image.start_addr +
					nvm_image.length - 4), (u8 *)&crc, 4);
		अगर (rc)
			DP_ERR(cdev, "Failed writing to %08x, rc = %d\n",
			       nvm_image.start_addr + nvm_image.length - 4, rc);
		जाओ निकास;
	पूर्ण

	/* Iterate over the values क्रम setting */
	जबतक (len) अणु
		u32 offset, mask, value, cur_value;
		u8 buf[4];

		value = *((u32 *)*data);
		*data += 4;
		mask = *((u32 *)*data);
		*data += 4;
		offset = *((u32 *)*data);
		*data += 4;

		rc = qed_mcp_nvm_पढ़ो(cdev, nvm_image.start_addr + offset, buf,
				      4);
		अगर (rc) अणु
			DP_ERR(cdev, "Failed reading from %08x\n",
			       nvm_image.start_addr + offset);
			जाओ निकास;
		पूर्ण

		cur_value = le32_to_cpu(*((__le32 *)buf));
		DP_VERBOSE(cdev, NETIF_MSG_DRV,
			   "NVM %08x: %08x -> %08x [Value %08x Mask %08x]\n",
			   nvm_image.start_addr + offset, cur_value,
			   (cur_value & ~mask) | (value & mask), value, mask);
		value = (value & mask) | (cur_value & ~mask);
		rc = qed_mcp_nvm_ग_लिखो(cdev, QED_NVM_WRITE_NVRAM,
				       nvm_image.start_addr + offset,
				       (u8 *)&value, 4);
		अगर (rc) अणु
			DP_ERR(cdev, "Failed writing to %08x\n",
			       nvm_image.start_addr + offset);
			जाओ निकास;
		पूर्ण

		len--;
	पूर्ण
निकास:
	वापस rc;
पूर्ण

/* Binary file क्रमmat -
 *     /----------------------------------------------------------------------\
 * 0B  |                       0x3 [command index]                            |
 * 4B  | b'0: check_response?   | b'1-31  reserved                            |
 * 8B  | File-type |                   reserved                               |
 * 12B |                    Image length in bytes                             |
 *     \----------------------------------------------------------------------/
 *     Start a new file of the provided type
 */
अटल पूर्णांक qed_nvm_flash_image_file_start(काष्ठा qed_dev *cdev,
					  स्थिर u8 **data, bool *check_resp)
अणु
	u32 file_type, file_size = 0;
	पूर्णांक rc;

	*data += 4;
	*check_resp = !!(**data & BIT(0));
	*data += 4;
	file_type = **data;

	DP_VERBOSE(cdev, NETIF_MSG_DRV,
		   "About to start a new file of type %02x\n", file_type);
	अगर (file_type == DRV_MB_PARAM_NVM_PUT_खाता_BEGIN_MBI) अणु
		*data += 4;
		file_size = *((u32 *)(*data));
	पूर्ण

	rc = qed_mcp_nvm_ग_लिखो(cdev, QED_PUT_खाता_BEGIN, file_type,
			       (u8 *)(&file_size), 4);
	*data += 4;

	वापस rc;
पूर्ण

/* Binary file क्रमmat -
 *     /----------------------------------------------------------------------\
 * 0B  |                       0x2 [command index]                            |
 * 4B  |                       Length in bytes                                |
 * 8B  | b'0: check_response?   | b'1-31  reserved                            |
 * 12B |                       Offset in bytes                                |
 * 16B |                       Data ...                                       |
 *     \----------------------------------------------------------------------/
 *     Write data as part of a file that was previously started. Data should be
 *     of length equal to that provided in the message
 */
अटल पूर्णांक qed_nvm_flash_image_file_data(काष्ठा qed_dev *cdev,
					 स्थिर u8 **data, bool *check_resp)
अणु
	u32 offset, len;
	पूर्णांक rc;

	*data += 4;
	len = *((u32 *)(*data));
	*data += 4;
	*check_resp = !!(**data & BIT(0));
	*data += 4;
	offset = *((u32 *)(*data));
	*data += 4;

	DP_VERBOSE(cdev, NETIF_MSG_DRV,
		   "About to write File-data: %08x bytes to offset %08x\n",
		   len, offset);

	rc = qed_mcp_nvm_ग_लिखो(cdev, QED_PUT_खाता_DATA, offset,
			       (अक्षर *)(*data), len);
	*data += len;

	वापस rc;
पूर्ण

/* Binary file क्रमmat [General header] -
 *     /----------------------------------------------------------------------\
 * 0B  |                       QED_NVM_SIGNATURE                              |
 * 4B  |                       Length in bytes                                |
 * 8B  | Highest command in this batchfile |          Reserved                |
 *     \----------------------------------------------------------------------/
 */
अटल पूर्णांक qed_nvm_flash_image_validate(काष्ठा qed_dev *cdev,
					स्थिर काष्ठा firmware *image,
					स्थिर u8 **data)
अणु
	u32 signature, len;

	/* Check minimum size */
	अगर (image->size < 12) अणु
		DP_ERR(cdev, "Image is too short [%08x]\n", (u32)image->size);
		वापस -EINVAL;
	पूर्ण

	/* Check signature */
	signature = *((u32 *)(*data));
	अगर (signature != QED_NVM_SIGNATURE) अणु
		DP_ERR(cdev, "Wrong signature '%08x'\n", signature);
		वापस -EINVAL;
	पूर्ण

	*data += 4;
	/* Validate पूर्णांकernal size equals the image-size */
	len = *((u32 *)(*data));
	अगर (len != image->size) अणु
		DP_ERR(cdev, "Size mismatch: internal = %08x image = %08x\n",
		       len, (u32)image->size);
		वापस -EINVAL;
	पूर्ण

	*data += 4;
	/* Make sure driver familiar with all commands necessary क्रम this */
	अगर (*((u16 *)(*data)) >= QED_NVM_FLASH_CMD_NVM_MAX) अणु
		DP_ERR(cdev, "File contains unsupported commands [Need %04x]\n",
		       *((u16 *)(*data)));
		वापस -EINVAL;
	पूर्ण

	*data += 4;

	वापस 0;
पूर्ण

/* Binary file क्रमmat -
 *     /----------------------------------------------------------------------\
 * 0B  |                       0x5 [command index]                            |
 * 4B  | Number of config attributes     |          Reserved                  |
 * 4B  | Config ID                       | Entity ID      | Length            |
 * 4B  | Value                                                                |
 *     |                                                                      |
 *     \----------------------------------------------------------------------/
 * There can be several cfg_id-entity_id-Length-Value sets as specअगरied by
 * 'Number of config attributes'.
 *
 * The API parses config attributes from the user provided buffer and flashes
 * them to the respective NVM path using Management FW inerface.
 */
अटल पूर्णांक qed_nvm_flash_cfg_ग_लिखो(काष्ठा qed_dev *cdev, स्थिर u8 **data)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	u8 entity_id, len, buf[32];
	bool need_nvm_init = true;
	काष्ठा qed_ptt *ptt;
	u16 cfg_id, count;
	पूर्णांक rc = 0, i;
	u32 flags;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EAGAIN;

	/* NVM CFG ID attribute header */
	*data += 4;
	count = *((u16 *)*data);
	*data += 4;

	DP_VERBOSE(cdev, NETIF_MSG_DRV,
		   "Read config ids: num_attrs = %0d\n", count);
	/* NVM CFG ID attributes. Start loop index from 1 to aव्योम additional
	 * arithmetic operations in the implementation.
	 */
	क्रम (i = 1; i <= count; i++) अणु
		cfg_id = *((u16 *)*data);
		*data += 2;
		entity_id = **data;
		(*data)++;
		len = **data;
		(*data)++;
		स_नकल(buf, *data, len);
		*data += len;

		flags = 0;
		अगर (need_nvm_init) अणु
			flags |= QED_NVM_CFG_OPTION_INIT;
			need_nvm_init = false;
		पूर्ण

		/* Commit to flash and मुक्त the resources */
		अगर (!(i % QED_NVM_CFG_MAX_ATTRS) || i == count) अणु
			flags |= QED_NVM_CFG_OPTION_COMMIT |
				 QED_NVM_CFG_OPTION_FREE;
			need_nvm_init = true;
		पूर्ण

		अगर (entity_id)
			flags |= QED_NVM_CFG_OPTION_ENTITY_SEL;

		DP_VERBOSE(cdev, NETIF_MSG_DRV,
			   "cfg_id = %d entity = %d len = %d\n", cfg_id,
			   entity_id, len);
		rc = qed_mcp_nvm_set_cfg(hwfn, ptt, cfg_id, entity_id, flags,
					 buf, len);
		अगर (rc) अणु
			DP_ERR(cdev, "Error %d configuring %d\n", rc, cfg_id);
			अवरोध;
		पूर्ण
	पूर्ण

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

#घोषणा QED_MAX_NVM_BUF_LEN	32
अटल पूर्णांक qed_nvm_flash_cfg_len(काष्ठा qed_dev *cdev, u32 cmd)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	u8 buf[QED_MAX_NVM_BUF_LEN];
	काष्ठा qed_ptt *ptt;
	u32 len;
	पूर्णांक rc;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस QED_MAX_NVM_BUF_LEN;

	rc = qed_mcp_nvm_get_cfg(hwfn, ptt, cmd, 0, QED_NVM_CFG_GET_FLAGS, buf,
				 &len);
	अगर (rc || !len) अणु
		DP_ERR(cdev, "Error %d reading %d\n", rc, cmd);
		len = QED_MAX_NVM_BUF_LEN;
	पूर्ण

	qed_ptt_release(hwfn, ptt);

	वापस len;
पूर्ण

अटल पूर्णांक qed_nvm_flash_cfg_पढ़ो(काष्ठा qed_dev *cdev, u8 **data,
				  u32 cmd, u32 entity_id)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *ptt;
	u32 flags, len;
	पूर्णांक rc = 0;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EAGAIN;

	DP_VERBOSE(cdev, NETIF_MSG_DRV,
		   "Read config cmd = %d entity id %d\n", cmd, entity_id);
	flags = entity_id ? QED_NVM_CFG_GET_PF_FLAGS : QED_NVM_CFG_GET_FLAGS;
	rc = qed_mcp_nvm_get_cfg(hwfn, ptt, cmd, entity_id, flags, *data, &len);
	अगर (rc)
		DP_ERR(cdev, "Error %d reading %d\n", rc, cmd);

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_nvm_flash(काष्ठा qed_dev *cdev, स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा firmware *image;
	स्थिर u8 *data, *data_end;
	u32 cmd_type;
	पूर्णांक rc;

	rc = request_firmware(&image, name, &cdev->pdev->dev);
	अगर (rc) अणु
		DP_ERR(cdev, "Failed to find '%s'\n", name);
		वापस rc;
	पूर्ण

	DP_VERBOSE(cdev, NETIF_MSG_DRV,
		   "Flashing '%s' - firmware's data at %p, size is %08x\n",
		   name, image->data, (u32)image->size);
	data = image->data;
	data_end = data + image->size;

	rc = qed_nvm_flash_image_validate(cdev, image, &data);
	अगर (rc)
		जाओ निकास;

	जबतक (data < data_end) अणु
		bool check_resp = false;

		/* Parse the actual command */
		cmd_type = *((u32 *)data);
		चयन (cmd_type) अणु
		हाल QED_NVM_FLASH_CMD_खाता_DATA:
			rc = qed_nvm_flash_image_file_data(cdev, &data,
							   &check_resp);
			अवरोध;
		हाल QED_NVM_FLASH_CMD_खाता_START:
			rc = qed_nvm_flash_image_file_start(cdev, &data,
							    &check_resp);
			अवरोध;
		हाल QED_NVM_FLASH_CMD_NVM_CHANGE:
			rc = qed_nvm_flash_image_access(cdev, &data,
							&check_resp);
			अवरोध;
		हाल QED_NVM_FLASH_CMD_NVM_CFG_ID:
			rc = qed_nvm_flash_cfg_ग_लिखो(cdev, &data);
			अवरोध;
		शेष:
			DP_ERR(cdev, "Unknown command %08x\n", cmd_type);
			rc = -EINVAL;
			जाओ निकास;
		पूर्ण

		अगर (rc) अणु
			DP_ERR(cdev, "Command %08x failed\n", cmd_type);
			जाओ निकास;
		पूर्ण

		/* Check response अगर needed */
		अगर (check_resp) अणु
			u32 mcp_response = 0;

			अगर (qed_mcp_nvm_resp(cdev, (u8 *)&mcp_response)) अणु
				DP_ERR(cdev, "Failed getting MCP response\n");
				rc = -EINVAL;
				जाओ निकास;
			पूर्ण

			चयन (mcp_response & FW_MSG_CODE_MASK) अणु
			हाल FW_MSG_CODE_OK:
			हाल FW_MSG_CODE_NVM_OK:
			हाल FW_MSG_CODE_NVM_PUT_खाता_FINISH_OK:
			हाल FW_MSG_CODE_PHY_OK:
				अवरोध;
			शेष:
				DP_ERR(cdev, "MFW returns error: %08x\n",
				       mcp_response);
				rc = -EINVAL;
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण

निकास:
	release_firmware(image);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_nvm_get_image(काष्ठा qed_dev *cdev, क्रमागत qed_nvm_images type,
			     u8 *buf, u16 len)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);

	वापस qed_mcp_get_nvm_image(hwfn, type, buf, len);
पूर्ण

व्योम qed_schedule_recovery_handler(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_common_cb_ops *ops = p_hwfn->cdev->protocol_ops.common;
	व्योम *cookie = p_hwfn->cdev->ops_cookie;

	अगर (ops && ops->schedule_recovery_handler)
		ops->schedule_recovery_handler(cookie);
पूर्ण

अटल स्थिर अक्षर * स्थिर qed_hw_err_type_descr[] = अणु
	[QED_HW_ERR_FAN_FAIL]		= "Fan Failure",
	[QED_HW_ERR_MFW_RESP_FAIL]	= "MFW Response Failure",
	[QED_HW_ERR_HW_ATTN]		= "HW Attention",
	[QED_HW_ERR_DMAE_FAIL]		= "DMAE Failure",
	[QED_HW_ERR_RAMROD_FAIL]	= "Ramrod Failure",
	[QED_HW_ERR_FW_ASSERT]		= "FW Assertion",
	[QED_HW_ERR_LAST]		= "Unknown",
पूर्ण;

व्योम qed_hw_error_occurred(काष्ठा qed_hwfn *p_hwfn,
			   क्रमागत qed_hw_err_type err_type)
अणु
	काष्ठा qed_common_cb_ops *ops = p_hwfn->cdev->protocol_ops.common;
	व्योम *cookie = p_hwfn->cdev->ops_cookie;
	स्थिर अक्षर *err_str;

	अगर (err_type > QED_HW_ERR_LAST)
		err_type = QED_HW_ERR_LAST;
	err_str = qed_hw_err_type_descr[err_type];

	DP_NOTICE(p_hwfn, "HW error occurred [%s]\n", err_str);

	/* Call the HW error handler of the protocol driver.
	 * If it is not available - perक्रमm a minimal handling of preventing
	 * HW attentions from being reनिश्चितed.
	 */
	अगर (ops && ops->schedule_hw_err_handler)
		ops->schedule_hw_err_handler(cookie, err_type);
	अन्यथा
		qed_पूर्णांक_attn_clr_enable(p_hwfn->cdev, true);
पूर्ण

अटल पूर्णांक qed_set_coalesce(काष्ठा qed_dev *cdev, u16 rx_coal, u16 tx_coal,
			    व्योम *handle)
अणु
		वापस qed_set_queue_coalesce(rx_coal, tx_coal, handle);
पूर्ण

अटल पूर्णांक qed_set_led(काष्ठा qed_dev *cdev, क्रमागत qed_led_mode mode)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *ptt;
	पूर्णांक status = 0;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EAGAIN;

	status = qed_mcp_set_led(hwfn, ptt, mode);

	qed_ptt_release(hwfn, ptt);

	वापस status;
पूर्ण

पूर्णांक qed_recovery_process(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc = 0;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EAGAIN;

	rc = qed_start_recovery_process(p_hwfn, p_ptt);

	qed_ptt_release(p_hwfn, p_ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_update_wol(काष्ठा qed_dev *cdev, bool enabled)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc = 0;

	अगर (IS_VF(cdev))
		वापस 0;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EAGAIN;

	rc = qed_mcp_ov_update_wol(hwfn, ptt, enabled ? QED_OV_WOL_ENABLED
				   : QED_OV_WOL_DISABLED);
	अगर (rc)
		जाओ out;
	rc = qed_mcp_ov_update_current_config(hwfn, ptt, QED_OV_CLIENT_DRV);

out:
	qed_ptt_release(hwfn, ptt);
	वापस rc;
पूर्ण

अटल पूर्णांक qed_update_drv_state(काष्ठा qed_dev *cdev, bool active)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *ptt;
	पूर्णांक status = 0;

	अगर (IS_VF(cdev))
		वापस 0;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EAGAIN;

	status = qed_mcp_ov_update_driver_state(hwfn, ptt, active ?
						QED_OV_DRIVER_STATE_ACTIVE :
						QED_OV_DRIVER_STATE_DISABLED);

	qed_ptt_release(hwfn, ptt);

	वापस status;
पूर्ण

अटल पूर्णांक qed_update_mac(काष्ठा qed_dev *cdev, u8 *mac)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *ptt;
	पूर्णांक status = 0;

	अगर (IS_VF(cdev))
		वापस 0;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EAGAIN;

	status = qed_mcp_ov_update_mac(hwfn, ptt, mac);
	अगर (status)
		जाओ out;

	status = qed_mcp_ov_update_current_config(hwfn, ptt, QED_OV_CLIENT_DRV);

out:
	qed_ptt_release(hwfn, ptt);
	वापस status;
पूर्ण

अटल पूर्णांक qed_update_mtu(काष्ठा qed_dev *cdev, u16 mtu)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *ptt;
	पूर्णांक status = 0;

	अगर (IS_VF(cdev))
		वापस 0;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EAGAIN;

	status = qed_mcp_ov_update_mtu(hwfn, ptt, mtu);
	अगर (status)
		जाओ out;

	status = qed_mcp_ov_update_current_config(hwfn, ptt, QED_OV_CLIENT_DRV);

out:
	qed_ptt_release(hwfn, ptt);
	वापस status;
पूर्ण

अटल पूर्णांक qed_पढ़ो_module_eeprom(काष्ठा qed_dev *cdev, अक्षर *buf,
				  u8 dev_addr, u32 offset, u32 len)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc = 0;

	अगर (IS_VF(cdev))
		वापस 0;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EAGAIN;

	rc = qed_mcp_phy_sfp_पढ़ो(hwfn, ptt, MFW_PORT(hwfn), dev_addr,
				  offset, len, buf);

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_set_grc_config(काष्ठा qed_dev *cdev, u32 cfg_id, u32 val)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc = 0;

	अगर (IS_VF(cdev))
		वापस 0;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EAGAIN;

	rc = qed_dbg_grc_config(hwfn, cfg_id, val);

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

अटल u8 qed_get_affin_hwfn_idx(काष्ठा qed_dev *cdev)
अणु
	वापस QED_AFFIN_HWFN_IDX(cdev);
पूर्ण

अटल काष्ठा qed_selftest_ops qed_selftest_ops_pass = अणु
	.selftest_memory = &qed_selftest_memory,
	.selftest_पूर्णांकerrupt = &qed_selftest_पूर्णांकerrupt,
	.selftest_रेजिस्टर = &qed_selftest_रेजिस्टर,
	.selftest_घड़ी = &qed_selftest_घड़ी,
	.selftest_nvram = &qed_selftest_nvram,
पूर्ण;

स्थिर काष्ठा qed_common_ops qed_common_ops_pass = अणु
	.selftest = &qed_selftest_ops_pass,
	.probe = &qed_probe,
	.हटाओ = &qed_हटाओ,
	.set_घातer_state = &qed_set_घातer_state,
	.set_name = &qed_set_name,
	.update_pf_params = &qed_update_pf_params,
	.slowpath_start = &qed_slowpath_start,
	.slowpath_stop = &qed_slowpath_stop,
	.set_fp_पूर्णांक = &qed_set_पूर्णांक_fp,
	.get_fp_पूर्णांक = &qed_get_पूर्णांक_fp,
	.sb_init = &qed_sb_init,
	.sb_release = &qed_sb_release,
	.simd_handler_config = &qed_simd_handler_config,
	.simd_handler_clean = &qed_simd_handler_clean,
	.dbg_grc = &qed_dbg_grc,
	.dbg_grc_size = &qed_dbg_grc_size,
	.can_link_change = &qed_can_link_change,
	.set_link = &qed_set_link,
	.get_link = &qed_get_current_link,
	.drain = &qed_drain,
	.update_msglvl = &qed_init_dp,
	.devlink_रेजिस्टर = qed_devlink_रेजिस्टर,
	.devlink_unरेजिस्टर = qed_devlink_unरेजिस्टर,
	.report_fatal_error = qed_report_fatal_error,
	.dbg_all_data = &qed_dbg_all_data,
	.dbg_all_data_size = &qed_dbg_all_data_size,
	.chain_alloc = &qed_chain_alloc,
	.chain_मुक्त = &qed_chain_मुक्त,
	.nvm_flash = &qed_nvm_flash,
	.nvm_get_image = &qed_nvm_get_image,
	.set_coalesce = &qed_set_coalesce,
	.set_led = &qed_set_led,
	.recovery_process = &qed_recovery_process,
	.recovery_prolog = &qed_recovery_prolog,
	.attn_clr_enable = &qed_पूर्णांक_attn_clr_enable,
	.update_drv_state = &qed_update_drv_state,
	.update_mac = &qed_update_mac,
	.update_mtu = &qed_update_mtu,
	.update_wol = &qed_update_wol,
	.db_recovery_add = &qed_db_recovery_add,
	.db_recovery_del = &qed_db_recovery_del,
	.पढ़ो_module_eeprom = &qed_पढ़ो_module_eeprom,
	.get_affin_hwfn_idx = &qed_get_affin_hwfn_idx,
	.पढ़ो_nvm_cfg = &qed_nvm_flash_cfg_पढ़ो,
	.पढ़ो_nvm_cfg_len = &qed_nvm_flash_cfg_len,
	.set_grc_config = &qed_set_grc_config,
पूर्ण;

व्योम qed_get_protocol_stats(काष्ठा qed_dev *cdev,
			    क्रमागत qed_mcp_protocol_type type,
			    जोड़ qed_mcp_protocol_stats *stats)
अणु
	काष्ठा qed_eth_stats eth_stats;

	स_रखो(stats, 0, माप(*stats));

	चयन (type) अणु
	हाल QED_MCP_LAN_STATS:
		qed_get_vport_stats(cdev, &eth_stats);
		stats->lan_stats.ucast_rx_pkts =
					eth_stats.common.rx_ucast_pkts;
		stats->lan_stats.ucast_tx_pkts =
					eth_stats.common.tx_ucast_pkts;
		stats->lan_stats.fcs_err = -1;
		अवरोध;
	हाल QED_MCP_FCOE_STATS:
		qed_get_protocol_stats_fcoe(cdev, &stats->fcoe_stats);
		अवरोध;
	हाल QED_MCP_ISCSI_STATS:
		qed_get_protocol_stats_iscsi(cdev, &stats->iscsi_stats);
		अवरोध;
	शेष:
		DP_VERBOSE(cdev, QED_MSG_SP,
			   "Invalid protocol type = %d\n", type);
		वापस;
	पूर्ण
पूर्ण

पूर्णांक qed_mfw_tlv_req(काष्ठा qed_hwfn *hwfn)
अणु
	DP_VERBOSE(hwfn->cdev, NETIF_MSG_DRV,
		   "Scheduling slowpath task [Flag: %d]\n",
		   QED_SLOWPATH_MFW_TLV_REQ);
	smp_mb__beक्रमe_atomic();
	set_bit(QED_SLOWPATH_MFW_TLV_REQ, &hwfn->slowpath_task_flags);
	smp_mb__after_atomic();
	queue_delayed_work(hwfn->slowpath_wq, &hwfn->slowpath_task, 0);

	वापस 0;
पूर्ण

अटल व्योम
qed_fill_generic_tlv_data(काष्ठा qed_dev *cdev, काष्ठा qed_mfw_tlv_generic *tlv)
अणु
	काष्ठा qed_common_cb_ops *op = cdev->protocol_ops.common;
	काष्ठा qed_eth_stats_common *p_common;
	काष्ठा qed_generic_tlvs gen_tlvs;
	काष्ठा qed_eth_stats stats;
	पूर्णांक i;

	स_रखो(&gen_tlvs, 0, माप(gen_tlvs));
	op->get_generic_tlv_data(cdev->ops_cookie, &gen_tlvs);

	अगर (gen_tlvs.feat_flags & QED_TLV_IP_CSUM)
		tlv->flags.ipv4_csum_offload = true;
	अगर (gen_tlvs.feat_flags & QED_TLV_LSO)
		tlv->flags.lso_supported = true;
	tlv->flags.b_set = true;

	क्रम (i = 0; i < QED_TLV_MAC_COUNT; i++) अणु
		अगर (is_valid_ether_addr(gen_tlvs.mac[i])) अणु
			ether_addr_copy(tlv->mac[i], gen_tlvs.mac[i]);
			tlv->mac_set[i] = true;
		पूर्ण
	पूर्ण

	qed_get_vport_stats(cdev, &stats);
	p_common = &stats.common;
	tlv->rx_frames = p_common->rx_ucast_pkts + p_common->rx_mcast_pkts +
			 p_common->rx_bcast_pkts;
	tlv->rx_frames_set = true;
	tlv->rx_bytes = p_common->rx_ucast_bytes + p_common->rx_mcast_bytes +
			p_common->rx_bcast_bytes;
	tlv->rx_bytes_set = true;
	tlv->tx_frames = p_common->tx_ucast_pkts + p_common->tx_mcast_pkts +
			 p_common->tx_bcast_pkts;
	tlv->tx_frames_set = true;
	tlv->tx_bytes = p_common->tx_ucast_bytes + p_common->tx_mcast_bytes +
			p_common->tx_bcast_bytes;
	tlv->rx_bytes_set = true;
पूर्ण

पूर्णांक qed_mfw_fill_tlv_data(काष्ठा qed_hwfn *hwfn, क्रमागत qed_mfw_tlv_type type,
			  जोड़ qed_mfw_tlv_data *tlv_buf)
अणु
	काष्ठा qed_dev *cdev = hwfn->cdev;
	काष्ठा qed_common_cb_ops *ops;

	ops = cdev->protocol_ops.common;
	अगर (!ops || !ops->get_protocol_tlv_data || !ops->get_generic_tlv_data) अणु
		DP_NOTICE(hwfn, "Can't collect TLV management info\n");
		वापस -EINVAL;
	पूर्ण

	चयन (type) अणु
	हाल QED_MFW_TLV_GENERIC:
		qed_fill_generic_tlv_data(hwfn->cdev, &tlv_buf->generic);
		अवरोध;
	हाल QED_MFW_TLV_ETH:
		ops->get_protocol_tlv_data(cdev->ops_cookie, &tlv_buf->eth);
		अवरोध;
	हाल QED_MFW_TLV_FCOE:
		ops->get_protocol_tlv_data(cdev->ops_cookie, &tlv_buf->fcoe);
		अवरोध;
	हाल QED_MFW_TLV_ISCSI:
		ops->get_protocol_tlv_data(cdev->ops_cookie, &tlv_buf->iscsi);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
