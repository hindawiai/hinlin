<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Platक्रमm UFS Host driver क्रम Cadence controller
 *
 * Copyright (C) 2018 Cadence Design Systems, Inc.
 *
 * Authors:
 *	Jan Kotas <jank@cadence.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/समय.स>

#समावेश "ufshcd-pltfrm.h"

#घोषणा CDNS_UFS_REG_HCLKDIV	0xFC
#घोषणा CDNS_UFS_REG_PHY_XCFGD1	0x113C
#घोषणा CDNS_UFS_MAX_L4_ATTRS 12

काष्ठा cdns_ufs_host अणु
	/**
	 * cdns_ufs_dme_attr_val - क्रम storing L4 attributes
	 */
	u32 cdns_ufs_dme_attr_val[CDNS_UFS_MAX_L4_ATTRS];
पूर्ण;

/**
 * cdns_ufs_get_l4_attr - get L4 attributes on local side
 * @hba: per adapter instance
 *
 */
अटल व्योम cdns_ufs_get_l4_attr(काष्ठा ufs_hba *hba)
अणु
	काष्ठा cdns_ufs_host *host = ufshcd_get_variant(hba);

	ufshcd_dme_get(hba, UIC_ARG_MIB(T_PEERDEVICEID),
		       &host->cdns_ufs_dme_attr_val[0]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_PEERCPORTID),
		       &host->cdns_ufs_dme_attr_val[1]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_TRAFFICCLASS),
		       &host->cdns_ufs_dme_attr_val[2]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_PROTOCOLID),
		       &host->cdns_ufs_dme_attr_val[3]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_CPORTFLAGS),
		       &host->cdns_ufs_dme_attr_val[4]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_TXTOKENVALUE),
		       &host->cdns_ufs_dme_attr_val[5]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_RXTOKENVALUE),
		       &host->cdns_ufs_dme_attr_val[6]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_LOCALBUFFERSPACE),
		       &host->cdns_ufs_dme_attr_val[7]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_PEERBUFFERSPACE),
		       &host->cdns_ufs_dme_attr_val[8]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_CREDITSTOSEND),
		       &host->cdns_ufs_dme_attr_val[9]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_CPORTMODE),
		       &host->cdns_ufs_dme_attr_val[10]);
	ufshcd_dme_get(hba, UIC_ARG_MIB(T_CONNECTIONSTATE),
		       &host->cdns_ufs_dme_attr_val[11]);
पूर्ण

/**
 * cdns_ufs_set_l4_attr - set L4 attributes on local side
 * @hba: per adapter instance
 *
 */
अटल व्योम cdns_ufs_set_l4_attr(काष्ठा ufs_hba *hba)
अणु
	काष्ठा cdns_ufs_host *host = ufshcd_get_variant(hba);

	ufshcd_dme_set(hba, UIC_ARG_MIB(T_CONNECTIONSTATE), 0);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_PEERDEVICEID),
		       host->cdns_ufs_dme_attr_val[0]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_PEERCPORTID),
		       host->cdns_ufs_dme_attr_val[1]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_TRAFFICCLASS),
		       host->cdns_ufs_dme_attr_val[2]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_PROTOCOLID),
		       host->cdns_ufs_dme_attr_val[3]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_CPORTFLAGS),
		       host->cdns_ufs_dme_attr_val[4]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_TXTOKENVALUE),
		       host->cdns_ufs_dme_attr_val[5]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_RXTOKENVALUE),
		       host->cdns_ufs_dme_attr_val[6]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_LOCALBUFFERSPACE),
		       host->cdns_ufs_dme_attr_val[7]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_PEERBUFFERSPACE),
		       host->cdns_ufs_dme_attr_val[8]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_CREDITSTOSEND),
		       host->cdns_ufs_dme_attr_val[9]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_CPORTMODE),
		       host->cdns_ufs_dme_attr_val[10]);
	ufshcd_dme_set(hba, UIC_ARG_MIB(T_CONNECTIONSTATE),
		       host->cdns_ufs_dme_attr_val[11]);
पूर्ण

/**
 * cdns_ufs_set_hclkभाग()
 * Sets HCLKDIV रेजिस्टर value based on the core_clk
 * @hba: host controller instance
 *
 * Return zero क्रम success and non-zero क्रम failure
 */
अटल पूर्णांक cdns_ufs_set_hclkभाग(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_clk_info *clki;
	काष्ठा list_head *head = &hba->clk_list_head;
	अचिन्हित दीर्घ core_clk_rate = 0;
	u32 core_clk_भाग = 0;

	अगर (list_empty(head))
		वापस 0;

	list_क्रम_each_entry(clki, head, list) अणु
		अगर (IS_ERR_OR_शून्य(clki->clk))
			जारी;
		अगर (!म_भेद(clki->name, "core_clk"))
			core_clk_rate = clk_get_rate(clki->clk);
	पूर्ण

	अगर (!core_clk_rate) अणु
		dev_err(hba->dev, "%s: unable to find core_clk rate\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	core_clk_भाग = core_clk_rate / USEC_PER_SEC;

	ufshcd_ग_लिखोl(hba, core_clk_भाग, CDNS_UFS_REG_HCLKDIV);
	/**
	 * Make sure the रेजिस्टर was updated,
	 * UniPro layer will not work with an incorrect value.
	 */
	mb();

	वापस 0;
पूर्ण

/**
 * cdns_ufs_hce_enable_notअगरy()
 * Called beक्रमe and after HCE enable bit is set.
 * @hba: host controller instance
 * @status: notअगरy stage (pre, post change)
 *
 * Return zero क्रम success and non-zero क्रम failure
 */
अटल पूर्णांक cdns_ufs_hce_enable_notअगरy(काष्ठा ufs_hba *hba,
				      क्रमागत ufs_notअगरy_change_status status)
अणु
	अगर (status != PRE_CHANGE)
		वापस 0;

	वापस cdns_ufs_set_hclkभाग(hba);
पूर्ण

/**
 * cdns_ufs_hibern8_notअगरy()
 * Called around hibern8 enter/निकास.
 * @hba: host controller instance
 * @cmd: UIC Command
 * @status: notअगरy stage (pre, post change)
 *
 */
अटल व्योम cdns_ufs_hibern8_notअगरy(काष्ठा ufs_hba *hba, क्रमागत uic_cmd_dme cmd,
				    क्रमागत ufs_notअगरy_change_status status)
अणु
	अगर (status == PRE_CHANGE && cmd == UIC_CMD_DME_HIBER_ENTER)
		cdns_ufs_get_l4_attr(hba);
	अगर (status == POST_CHANGE && cmd == UIC_CMD_DME_HIBER_EXIT)
		cdns_ufs_set_l4_attr(hba);
पूर्ण

/**
 * cdns_ufs_link_startup_notअगरy()
 * Called beक्रमe and after Link startup is carried out.
 * @hba: host controller instance
 * @status: notअगरy stage (pre, post change)
 *
 * Return zero क्रम success and non-zero क्रम failure
 */
अटल पूर्णांक cdns_ufs_link_startup_notअगरy(काष्ठा ufs_hba *hba,
					क्रमागत ufs_notअगरy_change_status status)
अणु
	अगर (status != PRE_CHANGE)
		वापस 0;

	/*
	 * Some UFS devices have issues अगर LCC is enabled.
	 * So we are setting PA_Local_TX_LCC_Enable to 0
	 * beक्रमe link startup which will make sure that both host
	 * and device TX LCC are disabled once link startup is
	 * completed.
	 */
	ufshcd_disable_host_tx_lcc(hba);

	/*
	 * Disabling Autohibern8 feature in cadence UFS
	 * to mask unexpected पूर्णांकerrupt trigger.
	 */
	hba->ahit = 0;

	वापस 0;
पूर्ण

/**
 * cdns_ufs_init - perक्रमms additional ufs initialization
 * @hba: host controller instance
 *
 * Returns status of initialization
 */
अटल पूर्णांक cdns_ufs_init(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक status = 0;
	काष्ठा cdns_ufs_host *host;
	काष्ठा device *dev = hba->dev;

	host = devm_kzalloc(dev, माप(*host), GFP_KERNEL);

	अगर (!host)
		वापस -ENOMEM;
	ufshcd_set_variant(hba, host);

	status = ufshcd_vops_phy_initialization(hba);

	वापस status;
पूर्ण

/**
 * cdns_ufs_m31_16nm_phy_initialization - perक्रमms m31 phy initialization
 * @hba: host controller instance
 *
 * Always वापसs 0
 */
अटल पूर्णांक cdns_ufs_m31_16nm_phy_initialization(काष्ठा ufs_hba *hba)
अणु
	u32 data;

	/* Increase RX_Advanced_Min_ActivateTime_Capability */
	data = ufshcd_पढ़ोl(hba, CDNS_UFS_REG_PHY_XCFGD1);
	data |= BIT(24);
	ufshcd_ग_लिखोl(hba, data, CDNS_UFS_REG_PHY_XCFGD1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ufs_hba_variant_ops cdns_ufs_pltfm_hba_vops = अणु
	.name = "cdns-ufs-pltfm",
	.init = cdns_ufs_init,
	.hce_enable_notअगरy = cdns_ufs_hce_enable_notअगरy,
	.link_startup_notअगरy = cdns_ufs_link_startup_notअगरy,
	.hibern8_notअगरy = cdns_ufs_hibern8_notअगरy,
पूर्ण;

अटल स्थिर काष्ठा ufs_hba_variant_ops cdns_ufs_m31_16nm_pltfm_hba_vops = अणु
	.name = "cdns-ufs-pltfm",
	.init = cdns_ufs_init,
	.hce_enable_notअगरy = cdns_ufs_hce_enable_notअगरy,
	.link_startup_notअगरy = cdns_ufs_link_startup_notअगरy,
	.phy_initialization = cdns_ufs_m31_16nm_phy_initialization,
	.hibern8_notअगरy = cdns_ufs_hibern8_notअगरy,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdns_ufs_of_match[] = अणु
	अणु
		.compatible = "cdns,ufshc",
		.data =  &cdns_ufs_pltfm_hba_vops,
	पूर्ण,
	अणु
		.compatible = "cdns,ufshc-m31-16nm",
		.data =  &cdns_ufs_m31_16nm_pltfm_hba_vops,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, cdns_ufs_of_match);

/**
 * cdns_ufs_pltfrm_probe - probe routine of the driver
 * @pdev: poपूर्णांकer to platक्रमm device handle
 *
 * Return zero क्रम success and non-zero क्रम failure
 */
अटल पूर्णांक cdns_ufs_pltfrm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा ufs_hba_variant_ops *vops;
	काष्ठा device *dev = &pdev->dev;

	of_id = of_match_node(cdns_ufs_of_match, dev->of_node);
	vops = (काष्ठा ufs_hba_variant_ops *)of_id->data;

	/* Perक्रमm generic probe */
	err = ufshcd_pltfrm_init(pdev, vops);
	अगर (err)
		dev_err(dev, "ufshcd_pltfrm_init() failed %d\n", err);

	वापस err;
पूर्ण

/**
 * cdns_ufs_pltfrm_हटाओ - हटाओs the ufs driver
 * @pdev: poपूर्णांकer to platक्रमm device handle
 *
 * Always वापसs 0
 */
अटल पूर्णांक cdns_ufs_pltfrm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ufs_hba *hba =  platक्रमm_get_drvdata(pdev);

	ufshcd_हटाओ(hba);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cdns_ufs_dev_pm_ops = अणु
	.suspend         = ufshcd_pltfrm_suspend,
	.resume          = ufshcd_pltfrm_resume,
	.runसमय_suspend = ufshcd_pltfrm_runसमय_suspend,
	.runसमय_resume  = ufshcd_pltfrm_runसमय_resume,
	.runसमय_idle    = ufshcd_pltfrm_runसमय_idle,
पूर्ण;

अटल काष्ठा platक्रमm_driver cdns_ufs_pltfrm_driver = अणु
	.probe	= cdns_ufs_pltfrm_probe,
	.हटाओ	= cdns_ufs_pltfrm_हटाओ,
	.shutकरोwn = ufshcd_pltfrm_shutकरोwn,
	.driver	= अणु
		.name   = "cdns-ufshcd",
		.pm     = &cdns_ufs_dev_pm_ops,
		.of_match_table = cdns_ufs_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cdns_ufs_pltfrm_driver);

MODULE_AUTHOR("Jan Kotas <jank@cadence.com>");
MODULE_DESCRIPTION("Cadence UFS host controller platform driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(UFSHCD_DRIVER_VERSION);
