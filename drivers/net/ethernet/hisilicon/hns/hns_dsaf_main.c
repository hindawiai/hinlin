<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "hns_dsaf_mac.h"
#समावेश "hns_dsaf_main.h"
#समावेश "hns_dsaf_ppe.h"
#समावेश "hns_dsaf_rcb.h"
#समावेश "hns_dsaf_misc.h"

अटल स्थिर अक्षर *g_dsaf_mode_match[DSAF_MODE_MAX] = अणु
	[DSAF_MODE_DISABLE_2PORT_64VM] = "2port-64vf",
	[DSAF_MODE_DISABLE_6PORT_0VM] = "6port-16rss",
	[DSAF_MODE_DISABLE_6PORT_16VM] = "6port-16vf",
	[DSAF_MODE_DISABLE_SP] = "single-port",
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id hns_dsaf_acpi_match[] = अणु
	अणु "HISI00B1", 0 पूर्ण,
	अणु "HISI00B2", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hns_dsaf_acpi_match);

अटल पूर्णांक hns_dsaf_get_cfg(काष्ठा dsaf_device *dsaf_dev)
अणु
	पूर्णांक ret, i;
	u32 desc_num;
	u32 buf_size;
	u32 reset_offset = 0;
	u32 res_idx = 0;
	स्थिर अक्षर *mode_str;
	काष्ठा regmap *syscon;
	काष्ठा resource *res;
	काष्ठा device_node *np = dsaf_dev->dev->of_node, *np_temp;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dsaf_dev->dev);

	अगर (dev_of_node(dsaf_dev->dev)) अणु
		अगर (of_device_is_compatible(np, "hisilicon,hns-dsaf-v1"))
			dsaf_dev->dsaf_ver = AE_VERSION_1;
		अन्यथा
			dsaf_dev->dsaf_ver = AE_VERSION_2;
	पूर्ण अन्यथा अगर (is_acpi_node(dsaf_dev->dev->fwnode)) अणु
		अगर (acpi_dev_found(hns_dsaf_acpi_match[0].id))
			dsaf_dev->dsaf_ver = AE_VERSION_1;
		अन्यथा अगर (acpi_dev_found(hns_dsaf_acpi_match[1].id))
			dsaf_dev->dsaf_ver = AE_VERSION_2;
		अन्यथा
			वापस -ENXIO;
	पूर्ण अन्यथा अणु
		dev_err(dsaf_dev->dev, "cannot get cfg data from of or acpi\n");
		वापस -ENXIO;
	पूर्ण

	ret = device_property_पढ़ो_string(dsaf_dev->dev, "mode", &mode_str);
	अगर (ret) अणु
		dev_err(dsaf_dev->dev, "get dsaf mode fail, ret=%d!\n", ret);
		वापस ret;
	पूर्ण
	क्रम (i = 0; i < DSAF_MODE_MAX; i++) अणु
		अगर (g_dsaf_mode_match[i] &&
		    !म_भेद(mode_str, g_dsaf_mode_match[i]))
			अवरोध;
	पूर्ण
	अगर (i >= DSAF_MODE_MAX ||
	    i == DSAF_MODE_INVALID || i == DSAF_MODE_ENABLE) अणु
		dev_err(dsaf_dev->dev,
			"%s prs mode str fail!\n", dsaf_dev->ae_dev.name);
		वापस -EINVAL;
	पूर्ण
	dsaf_dev->dsaf_mode = (क्रमागत dsaf_mode)i;

	अगर (dsaf_dev->dsaf_mode > DSAF_MODE_ENABLE)
		dsaf_dev->dsaf_en = HRD_DSAF_NO_DSAF_MODE;
	अन्यथा
		dsaf_dev->dsaf_en = HRD_DSAF_MODE;

	अगर ((i == DSAF_MODE_ENABLE_16VM) ||
	    (i == DSAF_MODE_DISABLE_2PORT_8VM) ||
	    (i == DSAF_MODE_DISABLE_6PORT_2VM))
		dsaf_dev->dsaf_tc_mode = HRD_DSAF_8TC_MODE;
	अन्यथा
		dsaf_dev->dsaf_tc_mode = HRD_DSAF_4TC_MODE;

	अगर (dev_of_node(dsaf_dev->dev)) अणु
		np_temp = of_parse_phandle(np, "subctrl-syscon", 0);
		syscon = syscon_node_to_regmap(np_temp);
		of_node_put(np_temp);
		अगर (IS_ERR_OR_शून्य(syscon)) अणु
			res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
						    res_idx++);
			अगर (!res) अणु
				dev_err(dsaf_dev->dev, "subctrl info is needed!\n");
				वापस -ENOMEM;
			पूर्ण

			dsaf_dev->sc_base = devm_ioremap_resource(&pdev->dev,
								  res);
			अगर (IS_ERR(dsaf_dev->sc_base))
				वापस PTR_ERR(dsaf_dev->sc_base);

			res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
						    res_idx++);
			अगर (!res) अणु
				dev_err(dsaf_dev->dev, "serdes-ctrl info is needed!\n");
				वापस -ENOMEM;
			पूर्ण

			dsaf_dev->sds_base = devm_ioremap_resource(&pdev->dev,
								   res);
			अगर (IS_ERR(dsaf_dev->sds_base))
				वापस PTR_ERR(dsaf_dev->sds_base);
		पूर्ण अन्यथा अणु
			dsaf_dev->sub_ctrl = syscon;
		पूर्ण
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ppe-base");
	अगर (!res) अणु
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, res_idx++);
		अगर (!res) अणु
			dev_err(dsaf_dev->dev, "ppe-base info is needed!\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	dsaf_dev->ppe_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dsaf_dev->ppe_base))
		वापस PTR_ERR(dsaf_dev->ppe_base);
	dsaf_dev->ppe_paddr = res->start;

	अगर (!HNS_DSAF_IS_DEBUG(dsaf_dev)) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   "dsaf-base");
		अगर (!res) अणु
			res = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
						    res_idx);
			अगर (!res) अणु
				dev_err(dsaf_dev->dev,
					"dsaf-base info is needed!\n");
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		dsaf_dev->io_base = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(dsaf_dev->io_base))
			वापस PTR_ERR(dsaf_dev->io_base);
	पूर्ण

	ret = device_property_पढ़ो_u32(dsaf_dev->dev, "desc-num", &desc_num);
	अगर (ret < 0 || desc_num < HNS_DSAF_MIN_DESC_CNT ||
	    desc_num > HNS_DSAF_MAX_DESC_CNT) अणु
		dev_err(dsaf_dev->dev, "get desc-num(%d) fail, ret=%d!\n",
			desc_num, ret);
		वापस -EINVAL;
	पूर्ण
	dsaf_dev->desc_num = desc_num;

	ret = device_property_पढ़ो_u32(dsaf_dev->dev, "reset-field-offset",
				       &reset_offset);
	अगर (ret < 0) अणु
		dev_dbg(dsaf_dev->dev,
			"get reset-field-offset fail, ret=%d!\r\n", ret);
	पूर्ण
	dsaf_dev->reset_offset = reset_offset;

	ret = device_property_पढ़ो_u32(dsaf_dev->dev, "buf-size", &buf_size);
	अगर (ret < 0) अणु
		dev_err(dsaf_dev->dev,
			"get buf-size fail, ret=%d!\r\n", ret);
		वापस ret;
	पूर्ण
	dsaf_dev->buf_size = buf_size;

	dsaf_dev->buf_माप_प्रकारype = hns_rcb_buf_size2type(buf_size);
	अगर (dsaf_dev->buf_माप_प्रकारype < 0) अणु
		dev_err(dsaf_dev->dev,
			"buf_size(%d) is wrong!\n", buf_size);
		वापस -EINVAL;
	पूर्ण

	dsaf_dev->misc_op = hns_misc_op_get(dsaf_dev);
	अगर (!dsaf_dev->misc_op)
		वापस -ENOMEM;

	अगर (!dma_set_mask_and_coherent(dsaf_dev->dev, DMA_BIT_MASK(64ULL)))
		dev_dbg(dsaf_dev->dev, "set mask to 64bit\n");
	अन्यथा
		dev_err(dsaf_dev->dev, "set mask to 64bit fail!\n");

	वापस 0;
पूर्ण

/**
 * hns_dsaf_sbm_link_sram_init_en - config dsaf_sbm_init_en
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_sbm_link_sram_init_en(काष्ठा dsaf_device *dsaf_dev)
अणु
	dsaf_set_dev_bit(dsaf_dev, DSAF_CFG_0_REG, DSAF_CFG_SBM_INIT_S, 1);
पूर्ण

/**
 * hns_dsaf_reg_cnt_clr_ce - config hns_dsaf_reg_cnt_clr_ce
 * @dsaf_dev: dsa fabric id
 * @reg_cnt_clr_ce: config value
 */
अटल व्योम
hns_dsaf_reg_cnt_clr_ce(काष्ठा dsaf_device *dsaf_dev, u32 reg_cnt_clr_ce)
अणु
	dsaf_set_dev_bit(dsaf_dev, DSAF_DSA_REG_CNT_CLR_CE_REG,
			 DSAF_CNT_CLR_CE_S, reg_cnt_clr_ce);
पूर्ण

/**
 * hns_ppe_qid_cfg - config ppe qid
 * @dsaf_dev: dsa fabric id
 * @qid_cfg: value array
 */
अटल व्योम
hns_dsaf_ppe_qid_cfg(काष्ठा dsaf_device *dsaf_dev, u32 qid_cfg)
अणु
	u32 i;

	क्रम (i = 0; i < DSAF_COMM_CHN; i++) अणु
		dsaf_set_dev_field(dsaf_dev,
				   DSAF_PPE_QID_CFG_0_REG + 0x0004 * i,
				   DSAF_PPE_QID_CFG_M, DSAF_PPE_QID_CFG_S,
				   qid_cfg);
	पूर्ण
पूर्ण

अटल व्योम hns_dsaf_mix_def_qid_cfg(काष्ठा dsaf_device *dsaf_dev)
अणु
	u16 max_q_per_vf, max_vfn;
	u32 q_id, q_num_per_port;
	u32 i;

	hns_rcb_get_queue_mode(dsaf_dev->dsaf_mode, &max_vfn, &max_q_per_vf);
	q_num_per_port = max_vfn * max_q_per_vf;

	क्रम (i = 0, q_id = 0; i < DSAF_SERVICE_NW_NUM; i++) अणु
		dsaf_set_dev_field(dsaf_dev,
				   DSAF_MIX_DEF_QID_0_REG + 0x0004 * i,
				   0xff, 0, q_id);
		q_id += q_num_per_port;
	पूर्ण
पूर्ण

अटल व्योम hns_dsaf_inner_qid_cfg(काष्ठा dsaf_device *dsaf_dev)
अणु
	u16 max_q_per_vf, max_vfn;
	u32 q_id, q_num_per_port;
	u32 mac_id;

	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver))
		वापस;

	hns_rcb_get_queue_mode(dsaf_dev->dsaf_mode, &max_vfn, &max_q_per_vf);
	q_num_per_port = max_vfn * max_q_per_vf;

	क्रम (mac_id = 0, q_id = 0; mac_id < DSAF_SERVICE_NW_NUM; mac_id++) अणु
		dsaf_set_dev_field(dsaf_dev,
				   DSAFV2_SERDES_LBK_0_REG + 4 * mac_id,
				   DSAFV2_SERDES_LBK_QID_M,
				   DSAFV2_SERDES_LBK_QID_S,
				   q_id);
		q_id += q_num_per_port;
	पूर्ण
पूर्ण

/**
 * hns_dsaf_sw_port_type_cfg - cfg sw type
 * @dsaf_dev: dsa fabric id
 * @port_type: array
 */
अटल व्योम hns_dsaf_sw_port_type_cfg(काष्ठा dsaf_device *dsaf_dev,
				      क्रमागत dsaf_sw_port_type port_type)
अणु
	u32 i;

	क्रम (i = 0; i < DSAF_SW_PORT_NUM; i++) अणु
		dsaf_set_dev_field(dsaf_dev,
				   DSAF_SW_PORT_TYPE_0_REG + 0x0004 * i,
				   DSAF_SW_PORT_TYPE_M, DSAF_SW_PORT_TYPE_S,
				   port_type);
	पूर्ण
पूर्ण

/**
 * hns_dsaf_stp_port_type_cfg - cfg stp type
 * @dsaf_dev: dsa fabric id
 * @port_type: array
 */
अटल व्योम hns_dsaf_stp_port_type_cfg(काष्ठा dsaf_device *dsaf_dev,
				       क्रमागत dsaf_stp_port_type port_type)
अणु
	u32 i;

	क्रम (i = 0; i < DSAF_COMM_CHN; i++) अणु
		dsaf_set_dev_field(dsaf_dev,
				   DSAF_STP_PORT_TYPE_0_REG + 0x0004 * i,
				   DSAF_STP_PORT_TYPE_M, DSAF_STP_PORT_TYPE_S,
				   port_type);
	पूर्ण
पूर्ण

#घोषणा HNS_DSAF_SBM_NUM(dev) \
	(AE_IS_VER1((dev)->dsaf_ver) ? DSAF_SBM_NUM : DSAFV2_SBM_NUM)
/**
 * hns_dsaf_sbm_cfg - config sbm
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_sbm_cfg(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 o_sbm_cfg;
	u32 i;

	क्रम (i = 0; i < HNS_DSAF_SBM_NUM(dsaf_dev); i++) अणु
		o_sbm_cfg = dsaf_पढ़ो_dev(dsaf_dev,
					  DSAF_SBM_CFG_REG_0_REG + 0x80 * i);
		dsaf_set_bit(o_sbm_cfg, DSAF_SBM_CFG_EN_S, 1);
		dsaf_set_bit(o_sbm_cfg, DSAF_SBM_CFG_SHCUT_EN_S, 0);
		dsaf_ग_लिखो_dev(dsaf_dev,
			       DSAF_SBM_CFG_REG_0_REG + 0x80 * i, o_sbm_cfg);
	पूर्ण
पूर्ण

/**
 * hns_dsaf_sbm_cfg_mib_en - config sbm
 * @dsaf_dev: dsa fabric id
 */
अटल पूर्णांक hns_dsaf_sbm_cfg_mib_en(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 sbm_cfg_mib_en;
	u32 i;
	u32 reg;
	u32 पढ़ो_cnt;

	/* validate configure by setting SBM_CFG_MIB_EN bit from 0 to 1. */
	क्रम (i = 0; i < HNS_DSAF_SBM_NUM(dsaf_dev); i++) अणु
		reg = DSAF_SBM_CFG_REG_0_REG + 0x80 * i;
		dsaf_set_dev_bit(dsaf_dev, reg, DSAF_SBM_CFG_MIB_EN_S, 0);
	पूर्ण

	क्रम (i = 0; i < HNS_DSAF_SBM_NUM(dsaf_dev); i++) अणु
		reg = DSAF_SBM_CFG_REG_0_REG + 0x80 * i;
		dsaf_set_dev_bit(dsaf_dev, reg, DSAF_SBM_CFG_MIB_EN_S, 1);
	पूर्ण

	/* रुकोपूर्णांक क्रम all sbm enable finished */
	क्रम (i = 0; i < HNS_DSAF_SBM_NUM(dsaf_dev); i++) अणु
		पढ़ो_cnt = 0;
		reg = DSAF_SBM_CFG_REG_0_REG + 0x80 * i;
		करो अणु
			udelay(1);
			sbm_cfg_mib_en = dsaf_get_dev_bit(
					dsaf_dev, reg, DSAF_SBM_CFG_MIB_EN_S);
			पढ़ो_cnt++;
		पूर्ण जबतक (sbm_cfg_mib_en == 0 &&
			पढ़ो_cnt < DSAF_CFG_READ_CNT);

		अगर (sbm_cfg_mib_en == 0) अणु
			dev_err(dsaf_dev->dev,
				"sbm_cfg_mib_en fail,%s,sbm_num=%d\n",
				dsaf_dev->ae_dev.name, i);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * hns_dsaf_sbm_bp_wl_cfg - config sbm
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_sbm_bp_wl_cfg(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 o_sbm_bp_cfg;
	u32 reg;
	u32 i;

	/* XGE */
	क्रम (i = 0; i < DSAF_XGE_NUM; i++) अणु
		reg = DSAF_SBM_BP_CFG_0_XGE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG0_COM_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG0_COM_MAX_BUF_NUM_S, 512);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG0_VC0_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG0_VC0_MAX_BUF_NUM_S, 0);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG0_VC1_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG0_VC1_MAX_BUF_NUM_S, 0);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_1_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG1_TC4_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG1_TC4_MAX_BUF_NUM_S, 0);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG1_TC0_MAX_BUF_NUM_M,
			       DSAF_SBM_CFG1_TC0_MAX_BUF_NUM_S, 0);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_2_XGE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_SET_BUF_NUM_M,
			       DSAF_SBM_CFG2_SET_BUF_NUM_S, 104);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_RESET_BUF_NUM_M,
			       DSAF_SBM_CFG2_RESET_BUF_NUM_S, 128);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_3_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_S, 110);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_RESET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_RESET_BUF_NUM_NO_PFC_S, 160);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		/* क्रम no enable pfc mode */
		reg = DSAF_SBM_BP_CFG_4_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_SET_BUF_NUM_NO_PFC_S, 128);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAF_SBM_CFG3_RESET_BUF_NUM_NO_PFC_M,
			       DSAF_SBM_CFG3_RESET_BUF_NUM_NO_PFC_S, 192);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	पूर्ण

	/* PPE */
	क्रम (i = 0; i < DSAF_COMM_CHN; i++) अणु
		reg = DSAF_SBM_BP_CFG_2_PPE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_SET_BUF_NUM_M,
			       DSAF_SBM_CFG2_SET_BUF_NUM_S, 10);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_RESET_BUF_NUM_M,
			       DSAF_SBM_CFG2_RESET_BUF_NUM_S, 12);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	पूर्ण

	/* RoCEE */
	क्रम (i = 0; i < DSAF_COMM_CHN; i++) अणु
		reg = DSAF_SBM_BP_CFG_2_ROCEE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_SET_BUF_NUM_M,
			       DSAF_SBM_CFG2_SET_BUF_NUM_S, 2);
		dsaf_set_field(o_sbm_bp_cfg, DSAF_SBM_CFG2_RESET_BUF_NUM_M,
			       DSAF_SBM_CFG2_RESET_BUF_NUM_S, 4);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	पूर्ण
पूर्ण

अटल व्योम hns_dsafv2_sbm_bp_wl_cfg(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 o_sbm_bp_cfg;
	u32 reg;
	u32 i;

	/* XGE */
	क्रम (i = 0; i < DSAFV2_SBM_XGE_CHN; i++) अणु
		reg = DSAF_SBM_BP_CFG_0_XGE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG0_COM_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG0_COM_MAX_BUF_NUM_S, 256);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG0_VC0_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG0_VC0_MAX_BUF_NUM_S, 0);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG0_VC1_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG0_VC1_MAX_BUF_NUM_S, 0);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_1_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG1_TC4_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG1_TC4_MAX_BUF_NUM_S, 0);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG1_TC0_MAX_BUF_NUM_M,
			       DSAFV2_SBM_CFG1_TC0_MAX_BUF_NUM_S, 0);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_2_XGE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG2_SET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_SET_BUF_NUM_S, 104);
		dsaf_set_field(o_sbm_bp_cfg, DSAFV2_SBM_CFG2_RESET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_RESET_BUF_NUM_S, 128);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		reg = DSAF_SBM_BP_CFG_3_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG3_SET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG3_SET_BUF_NUM_NO_PFC_S, 55);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG3_RESET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG3_RESET_BUF_NUM_NO_PFC_S, 110);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);

		/* क्रम no enable pfc mode */
		reg = DSAF_SBM_BP_CFG_4_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG4_SET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG4_SET_BUF_NUM_NO_PFC_S, 128);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG4_RESET_BUF_NUM_NO_PFC_M,
			       DSAFV2_SBM_CFG4_RESET_BUF_NUM_NO_PFC_S, 192);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	पूर्ण

	/* PPE */
	क्रम (i = 0; i < DSAFV2_SBM_PPE_CHN; i++) अणु
		reg = DSAF_SBM_BP_CFG_2_PPE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_PPE_SET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_PPE_SET_BUF_NUM_S, 2);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_PPE_RESET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_PPE_RESET_BUF_NUM_S, 3);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_PPE_CFG_USEFUL_NUM_M,
			       DSAFV2_SBM_CFG2_PPE_CFG_USEFUL_NUM_S, 52);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	पूर्ण

	/* RoCEE */
	क्रम (i = 0; i < DASFV2_ROCEE_CRD_NUM; i++) अणु
		reg = DSAFV2_SBM_BP_CFG_2_ROCEE_REG_0_REG + 0x80 * i;
		o_sbm_bp_cfg = dsaf_पढ़ो_dev(dsaf_dev, reg);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_ROCEE_SET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_ROCEE_SET_BUF_NUM_S, 2);
		dsaf_set_field(o_sbm_bp_cfg,
			       DSAFV2_SBM_CFG2_ROCEE_RESET_BUF_NUM_M,
			       DSAFV2_SBM_CFG2_ROCEE_RESET_BUF_NUM_S, 4);
		dsaf_ग_लिखो_dev(dsaf_dev, reg, o_sbm_bp_cfg);
	पूर्ण
पूर्ण

/**
 * hns_dsaf_voq_bp_all_thrd_cfg -  voq
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_voq_bp_all_thrd_cfg(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 voq_bp_all_thrd;
	u32 i;

	क्रम (i = 0; i < DSAF_VOQ_NUM; i++) अणु
		voq_bp_all_thrd = dsaf_पढ़ो_dev(
			dsaf_dev, DSAF_VOQ_BP_ALL_THRD_0_REG + 0x40 * i);
		अगर (i < DSAF_XGE_NUM) अणु
			dsaf_set_field(voq_bp_all_thrd,
				       DSAF_VOQ_BP_ALL_DOWNTHRD_M,
				       DSAF_VOQ_BP_ALL_DOWNTHRD_S, 930);
			dsaf_set_field(voq_bp_all_thrd,
				       DSAF_VOQ_BP_ALL_UPTHRD_M,
				       DSAF_VOQ_BP_ALL_UPTHRD_S, 950);
		पूर्ण अन्यथा अणु
			dsaf_set_field(voq_bp_all_thrd,
				       DSAF_VOQ_BP_ALL_DOWNTHRD_M,
				       DSAF_VOQ_BP_ALL_DOWNTHRD_S, 220);
			dsaf_set_field(voq_bp_all_thrd,
				       DSAF_VOQ_BP_ALL_UPTHRD_M,
				       DSAF_VOQ_BP_ALL_UPTHRD_S, 230);
		पूर्ण
		dsaf_ग_लिखो_dev(
			dsaf_dev, DSAF_VOQ_BP_ALL_THRD_0_REG + 0x40 * i,
			voq_bp_all_thrd);
	पूर्ण
पूर्ण

अटल व्योम hns_dsaf_tbl_tcam_match_cfg(
	काष्ठा dsaf_device *dsaf_dev,
	काष्ठा dsaf_tbl_tcam_data *ptbl_tcam_data)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MATCH_CFG_L_REG,
		       ptbl_tcam_data->tbl_tcam_data_low);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MATCH_CFG_H_REG,
		       ptbl_tcam_data->tbl_tcam_data_high);
पूर्ण

/**
 * hns_dsaf_tbl_tcam_data_cfg - tbl
 * @dsaf_dev: dsa fabric id
 * @ptbl_tcam_data: addr
 */
अटल व्योम hns_dsaf_tbl_tcam_data_cfg(
	काष्ठा dsaf_device *dsaf_dev,
	काष्ठा dsaf_tbl_tcam_data *ptbl_tcam_data)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_LOW_0_REG,
		       ptbl_tcam_data->tbl_tcam_data_low);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_HIGH_0_REG,
		       ptbl_tcam_data->tbl_tcam_data_high);
पूर्ण

/**
 * dsaf_tbl_tcam_mcast_cfg - tbl
 * @dsaf_dev: dsa fabric id
 * @mcast: addr
 */
अटल व्योम hns_dsaf_tbl_tcam_mcast_cfg(
	काष्ठा dsaf_device *dsaf_dev,
	काष्ठा dsaf_tbl_tcam_mcast_cfg *mcast)
अणु
	u32 mcast_cfg4;

	mcast_cfg4 = dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_4_0_REG);
	dsaf_set_bit(mcast_cfg4, DSAF_TBL_MCAST_CFG4_ITEM_VLD_S,
		     mcast->tbl_mcast_item_vld);
	dsaf_set_bit(mcast_cfg4, DSAF_TBL_MCAST_CFG4_OLD_EN_S,
		     mcast->tbl_mcast_old_en);
	dsaf_set_field(mcast_cfg4, DSAF_TBL_MCAST_CFG4_VM128_112_M,
		       DSAF_TBL_MCAST_CFG4_VM128_112_S,
		       mcast->tbl_mcast_port_msk[4]);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_4_0_REG, mcast_cfg4);

	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_3_0_REG,
		       mcast->tbl_mcast_port_msk[3]);

	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_2_0_REG,
		       mcast->tbl_mcast_port_msk[2]);

	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_1_0_REG,
		       mcast->tbl_mcast_port_msk[1]);

	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_0_0_REG,
		       mcast->tbl_mcast_port_msk[0]);
पूर्ण

/**
 * hns_dsaf_tbl_tcam_ucast_cfg - tbl
 * @dsaf_dev: dsa fabric id
 * @tbl_tcam_ucast: addr
 */
अटल व्योम hns_dsaf_tbl_tcam_ucast_cfg(
	काष्ठा dsaf_device *dsaf_dev,
	काष्ठा dsaf_tbl_tcam_ucast_cfg *tbl_tcam_ucast)
अणु
	u32 ucast_cfg1;

	ucast_cfg1 = dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_UCAST_CFG_0_REG);
	dsaf_set_bit(ucast_cfg1, DSAF_TBL_UCAST_CFG1_MAC_DISCARD_S,
		     tbl_tcam_ucast->tbl_ucast_mac_discard);
	dsaf_set_bit(ucast_cfg1, DSAF_TBL_UCAST_CFG1_ITEM_VLD_S,
		     tbl_tcam_ucast->tbl_ucast_item_vld);
	dsaf_set_bit(ucast_cfg1, DSAF_TBL_UCAST_CFG1_OLD_EN_S,
		     tbl_tcam_ucast->tbl_ucast_old_en);
	dsaf_set_bit(ucast_cfg1, DSAF_TBL_UCAST_CFG1_DVC_S,
		     tbl_tcam_ucast->tbl_ucast_dvc);
	dsaf_set_field(ucast_cfg1, DSAF_TBL_UCAST_CFG1_OUT_PORT_M,
		       DSAF_TBL_UCAST_CFG1_OUT_PORT_S,
		       tbl_tcam_ucast->tbl_ucast_out_port);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_UCAST_CFG_0_REG, ucast_cfg1);
पूर्ण

/**
 * hns_dsaf_tbl_line_cfg - tbl
 * @dsaf_dev: dsa fabric id
 * @tbl_lin: addr
 */
अटल व्योम hns_dsaf_tbl_line_cfg(काष्ठा dsaf_device *dsaf_dev,
				  काष्ठा dsaf_tbl_line_cfg *tbl_lin)
अणु
	u32 tbl_line;

	tbl_line = dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_LIN_CFG_0_REG);
	dsaf_set_bit(tbl_line, DSAF_TBL_LINE_CFG_MAC_DISCARD_S,
		     tbl_lin->tbl_line_mac_discard);
	dsaf_set_bit(tbl_line, DSAF_TBL_LINE_CFG_DVC_S,
		     tbl_lin->tbl_line_dvc);
	dsaf_set_field(tbl_line, DSAF_TBL_LINE_CFG_OUT_PORT_M,
		       DSAF_TBL_LINE_CFG_OUT_PORT_S,
		       tbl_lin->tbl_line_out_port);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_LIN_CFG_0_REG, tbl_line);
पूर्ण

/**
 * hns_dsaf_tbl_tcam_mcast_pul - tbl
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_tbl_tcam_mcast_pul(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 o_tbl_pul;

	o_tbl_pul = dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_MCAST_VLD_S, 1);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, o_tbl_pul);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_MCAST_VLD_S, 0);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, o_tbl_pul);
पूर्ण

/**
 * hns_dsaf_tbl_line_pul - tbl
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_tbl_line_pul(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 tbl_pul;

	tbl_pul = dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG);
	dsaf_set_bit(tbl_pul, DSAF_TBL_PUL_LINE_VLD_S, 1);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, tbl_pul);
	dsaf_set_bit(tbl_pul, DSAF_TBL_PUL_LINE_VLD_S, 0);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, tbl_pul);
पूर्ण

/**
 * hns_dsaf_tbl_tcam_data_mcast_pul - tbl
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_tbl_tcam_data_mcast_pul(
	काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 o_tbl_pul;

	o_tbl_pul = dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_TCAM_DATA_VLD_S, 1);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_MCAST_VLD_S, 1);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, o_tbl_pul);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_TCAM_DATA_VLD_S, 0);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_MCAST_VLD_S, 0);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, o_tbl_pul);
पूर्ण

/**
 * hns_dsaf_tbl_tcam_data_ucast_pul - tbl
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_tbl_tcam_data_ucast_pul(
	काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 o_tbl_pul;

	o_tbl_pul = dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_TCAM_DATA_VLD_S, 1);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_UCAST_VLD_S, 1);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, o_tbl_pul);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_TCAM_DATA_VLD_S, 0);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_UCAST_VLD_S, 0);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, o_tbl_pul);
पूर्ण

व्योम hns_dsaf_set_promisc_mode(काष्ठा dsaf_device *dsaf_dev, u32 en)
अणु
	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver) && !HNS_DSAF_IS_DEBUG(dsaf_dev))
		dsaf_set_dev_bit(dsaf_dev, DSAF_CFG_0_REG,
				 DSAF_CFG_MIX_MODE_S, !!en);
पूर्ण

/**
 * hns_dsaf_tbl_stat_en - tbl
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_tbl_stat_en(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 o_tbl_ctrl;

	o_tbl_ctrl = dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_DFX_CTRL_0_REG);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_LINE_LKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_UC_LKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_MC_LKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_BC_LKUP_NUM_EN_S, 1);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_DFX_CTRL_0_REG, o_tbl_ctrl);
पूर्ण

/**
 * hns_dsaf_rocee_bp_en - rocee back press enable
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_rocee_bp_en(काष्ठा dsaf_device *dsaf_dev)
अणु
	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver))
		dsaf_set_dev_bit(dsaf_dev, DSAF_XGE_CTRL_SIG_CFG_0_REG,
				 DSAF_FC_XGE_TX_PAUSE_S, 1);
पूर्ण

/* set msk क्रम dsaf exception irq*/
अटल व्योम hns_dsaf_पूर्णांक_xge_msk_set(काष्ठा dsaf_device *dsaf_dev,
				     u32 chnn_num, u32 mask_set)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev,
		       DSAF_XGE_INT_MSK_0_REG + 0x4 * chnn_num, mask_set);
पूर्ण

अटल व्योम hns_dsaf_पूर्णांक_ppe_msk_set(काष्ठा dsaf_device *dsaf_dev,
				     u32 chnn_num, u32 msk_set)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev,
		       DSAF_PPE_INT_MSK_0_REG + 0x4 * chnn_num, msk_set);
पूर्ण

अटल व्योम hns_dsaf_पूर्णांक_rocee_msk_set(काष्ठा dsaf_device *dsaf_dev,
				       u32 chnn, u32 msk_set)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev,
		       DSAF_ROCEE_INT_MSK_0_REG + 0x4 * chnn, msk_set);
पूर्ण

अटल व्योम
hns_dsaf_पूर्णांक_tbl_msk_set(काष्ठा dsaf_device *dsaf_dev, u32 msk_set)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_INT_MSK_0_REG, msk_set);
पूर्ण

/* clr dsaf exception irq*/
अटल व्योम hns_dsaf_पूर्णांक_xge_src_clr(काष्ठा dsaf_device *dsaf_dev,
				     u32 chnn_num, u32 पूर्णांक_src)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev,
		       DSAF_XGE_INT_SRC_0_REG + 0x4 * chnn_num, पूर्णांक_src);
पूर्ण

अटल व्योम hns_dsaf_पूर्णांक_ppe_src_clr(काष्ठा dsaf_device *dsaf_dev,
				     u32 chnn, u32 पूर्णांक_src)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev,
		       DSAF_PPE_INT_SRC_0_REG + 0x4 * chnn, पूर्णांक_src);
पूर्ण

अटल व्योम hns_dsaf_पूर्णांक_rocee_src_clr(काष्ठा dsaf_device *dsaf_dev,
				       u32 chnn, u32 पूर्णांक_src)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev,
		       DSAF_ROCEE_INT_SRC_0_REG + 0x4 * chnn, पूर्णांक_src);
पूर्ण

अटल व्योम hns_dsaf_पूर्णांक_tbl_src_clr(काष्ठा dsaf_device *dsaf_dev,
				     u32 पूर्णांक_src)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_INT_SRC_0_REG, पूर्णांक_src);
पूर्ण

/**
 * hns_dsaf_single_line_tbl_cfg - INT
 * @dsaf_dev: dsa fabric id
 * @address: the address
 * @ptbl_line: the line
 */
अटल व्योम hns_dsaf_single_line_tbl_cfg(
	काष्ठा dsaf_device *dsaf_dev,
	u32 address, काष्ठा dsaf_tbl_line_cfg *ptbl_line)
अणु
	spin_lock_bh(&dsaf_dev->tcam_lock);

	/*Write Addr*/
	hns_dsaf_tbl_line_addr_cfg(dsaf_dev, address);

	/*Write Line*/
	hns_dsaf_tbl_line_cfg(dsaf_dev, ptbl_line);

	/*Write Plus*/
	hns_dsaf_tbl_line_pul(dsaf_dev);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
पूर्ण

/**
 * hns_dsaf_tcam_uc_cfg - INT
 * @dsaf_dev: dsa fabric id
 * @address: the address
 * @ptbl_tcam_data: the data
 * @ptbl_tcam_ucast: unicast
 */
अटल व्योम hns_dsaf_tcam_uc_cfg(
	काष्ठा dsaf_device *dsaf_dev, u32 address,
	काष्ठा dsaf_tbl_tcam_data *ptbl_tcam_data,
	काष्ठा dsaf_tbl_tcam_ucast_cfg *ptbl_tcam_ucast)
अणु
	spin_lock_bh(&dsaf_dev->tcam_lock);

	/*Write Addr*/
	hns_dsaf_tbl_tcam_addr_cfg(dsaf_dev, address);
	/*Write Tcam Data*/
	hns_dsaf_tbl_tcam_data_cfg(dsaf_dev, ptbl_tcam_data);
	/*Write Tcam Ucast*/
	hns_dsaf_tbl_tcam_ucast_cfg(dsaf_dev, ptbl_tcam_ucast);
	/*Write Plus*/
	hns_dsaf_tbl_tcam_data_ucast_pul(dsaf_dev);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
पूर्ण

/**
 * hns_dsaf_tcam_mc_cfg - cfg the tcam क्रम mc
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * @address: tcam index
 * @ptbl_tcam_data: tcam data काष्ठा poपूर्णांकer
 * @ptbl_tcam_mask: tcam mask काष्ठा poपूर्णांकer, it must be null क्रम HNSv1
 * @ptbl_tcam_mcast: tcam data काष्ठा poपूर्णांकer
 */
अटल व्योम hns_dsaf_tcam_mc_cfg(
	काष्ठा dsaf_device *dsaf_dev, u32 address,
	काष्ठा dsaf_tbl_tcam_data *ptbl_tcam_data,
	काष्ठा dsaf_tbl_tcam_data *ptbl_tcam_mask,
	काष्ठा dsaf_tbl_tcam_mcast_cfg *ptbl_tcam_mcast)
अणु
	spin_lock_bh(&dsaf_dev->tcam_lock);

	/*Write Addr*/
	hns_dsaf_tbl_tcam_addr_cfg(dsaf_dev, address);
	/*Write Tcam Data*/
	hns_dsaf_tbl_tcam_data_cfg(dsaf_dev, ptbl_tcam_data);
	/*Write Tcam Mcast*/
	hns_dsaf_tbl_tcam_mcast_cfg(dsaf_dev, ptbl_tcam_mcast);
	/* Write Match Data */
	अगर (ptbl_tcam_mask)
		hns_dsaf_tbl_tcam_match_cfg(dsaf_dev, ptbl_tcam_mask);

	/* Write Puls */
	hns_dsaf_tbl_tcam_data_mcast_pul(dsaf_dev);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
पूर्ण

/**
 * hns_dsaf_tcam_uc_cfg_vague - INT
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * @address: the address
 * @tcam_data: the data
 * @tcam_mask: the mask
 * @tcam_uc: the unicast data
 */
अटल व्योम hns_dsaf_tcam_uc_cfg_vague(काष्ठा dsaf_device *dsaf_dev,
				       u32 address,
				       काष्ठा dsaf_tbl_tcam_data *tcam_data,
				       काष्ठा dsaf_tbl_tcam_data *tcam_mask,
				       काष्ठा dsaf_tbl_tcam_ucast_cfg *tcam_uc)
अणु
	spin_lock_bh(&dsaf_dev->tcam_lock);
	hns_dsaf_tbl_tcam_addr_cfg(dsaf_dev, address);
	hns_dsaf_tbl_tcam_data_cfg(dsaf_dev, tcam_data);
	hns_dsaf_tbl_tcam_ucast_cfg(dsaf_dev, tcam_uc);
	hns_dsaf_tbl_tcam_match_cfg(dsaf_dev, tcam_mask);
	hns_dsaf_tbl_tcam_data_ucast_pul(dsaf_dev);

	/*Restore Match Data*/
	tcam_mask->tbl_tcam_data_high = 0xffffffff;
	tcam_mask->tbl_tcam_data_low = 0xffffffff;
	hns_dsaf_tbl_tcam_match_cfg(dsaf_dev, tcam_mask);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
पूर्ण

/**
 * hns_dsaf_tcam_mc_cfg_vague - INT
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * @address: the address
 * @tcam_data: the data
 * @tcam_mask: the mask
 * @tcam_mc: the multicast data
 */
अटल व्योम hns_dsaf_tcam_mc_cfg_vague(काष्ठा dsaf_device *dsaf_dev,
				       u32 address,
				       काष्ठा dsaf_tbl_tcam_data *tcam_data,
				       काष्ठा dsaf_tbl_tcam_data *tcam_mask,
				       काष्ठा dsaf_tbl_tcam_mcast_cfg *tcam_mc)
अणु
	spin_lock_bh(&dsaf_dev->tcam_lock);
	hns_dsaf_tbl_tcam_addr_cfg(dsaf_dev, address);
	hns_dsaf_tbl_tcam_data_cfg(dsaf_dev, tcam_data);
	hns_dsaf_tbl_tcam_mcast_cfg(dsaf_dev, tcam_mc);
	hns_dsaf_tbl_tcam_match_cfg(dsaf_dev, tcam_mask);
	hns_dsaf_tbl_tcam_data_mcast_pul(dsaf_dev);

	/*Restore Match Data*/
	tcam_mask->tbl_tcam_data_high = 0xffffffff;
	tcam_mask->tbl_tcam_data_low = 0xffffffff;
	hns_dsaf_tbl_tcam_match_cfg(dsaf_dev, tcam_mask);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
पूर्ण

/**
 * hns_dsaf_tcam_mc_invld - INT
 * @dsaf_dev: dsa fabric id
 * @address: the address
 */
अटल व्योम hns_dsaf_tcam_mc_invld(काष्ठा dsaf_device *dsaf_dev, u32 address)
अणु
	spin_lock_bh(&dsaf_dev->tcam_lock);

	/*Write Addr*/
	hns_dsaf_tbl_tcam_addr_cfg(dsaf_dev, address);

	/*ग_लिखो tcam mcast*/
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_0_0_REG, 0);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_1_0_REG, 0);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_2_0_REG, 0);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_3_0_REG, 0);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_4_0_REG, 0);

	/*Write Plus*/
	hns_dsaf_tbl_tcam_mcast_pul(dsaf_dev);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
पूर्ण

अटल व्योम
hns_dsaf_tcam_addr_get(काष्ठा dsaf_drv_tbl_tcam_key *mac_key, u8 *addr)
अणु
	addr[0] = mac_key->high.bits.mac_0;
	addr[1] = mac_key->high.bits.mac_1;
	addr[2] = mac_key->high.bits.mac_2;
	addr[3] = mac_key->high.bits.mac_3;
	addr[4] = mac_key->low.bits.mac_4;
	addr[5] = mac_key->low.bits.mac_5;
पूर्ण

/**
 * hns_dsaf_tcam_uc_get - INT
 * @dsaf_dev: dsa fabric id
 * @address: the address
 * @ptbl_tcam_data: the data
 * @ptbl_tcam_ucast: unicast
 */
अटल व्योम hns_dsaf_tcam_uc_get(
	काष्ठा dsaf_device *dsaf_dev, u32 address,
	काष्ठा dsaf_tbl_tcam_data *ptbl_tcam_data,
	काष्ठा dsaf_tbl_tcam_ucast_cfg *ptbl_tcam_ucast)
अणु
	u32 tcam_पढ़ो_data0;
	u32 tcam_पढ़ो_data4;

	spin_lock_bh(&dsaf_dev->tcam_lock);

	/*Write Addr*/
	hns_dsaf_tbl_tcam_addr_cfg(dsaf_dev, address);

	/*पढ़ो tcam item puls*/
	hns_dsaf_tbl_tcam_load_pul(dsaf_dev);

	/*पढ़ो tcam data*/
	ptbl_tcam_data->tbl_tcam_data_high
		= dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_RDATA_HIGH_0_REG);
	ptbl_tcam_data->tbl_tcam_data_low
		= dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_RDATA_LOW_0_REG);

	/*पढ़ो tcam mcast*/
	tcam_पढ़ो_data0 = dsaf_पढ़ो_dev(dsaf_dev,
					DSAF_TBL_TCAM_RAM_RDATA0_0_REG);
	tcam_पढ़ो_data4 = dsaf_पढ़ो_dev(dsaf_dev,
					DSAF_TBL_TCAM_RAM_RDATA4_0_REG);

	ptbl_tcam_ucast->tbl_ucast_item_vld
		= dsaf_get_bit(tcam_पढ़ो_data4,
			       DSAF_TBL_MCAST_CFG4_ITEM_VLD_S);
	ptbl_tcam_ucast->tbl_ucast_old_en
		= dsaf_get_bit(tcam_पढ़ो_data4, DSAF_TBL_MCAST_CFG4_OLD_EN_S);
	ptbl_tcam_ucast->tbl_ucast_mac_discard
		= dsaf_get_bit(tcam_पढ़ो_data0,
			       DSAF_TBL_UCAST_CFG1_MAC_DISCARD_S);
	ptbl_tcam_ucast->tbl_ucast_out_port
		= dsaf_get_field(tcam_पढ़ो_data0,
				 DSAF_TBL_UCAST_CFG1_OUT_PORT_M,
				 DSAF_TBL_UCAST_CFG1_OUT_PORT_S);
	ptbl_tcam_ucast->tbl_ucast_dvc
		= dsaf_get_bit(tcam_पढ़ो_data0, DSAF_TBL_UCAST_CFG1_DVC_S);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
पूर्ण

/**
 * hns_dsaf_tcam_mc_get - INT
 * @dsaf_dev: dsa fabric id
 * @address: the address
 * @ptbl_tcam_data: the data
 * @ptbl_tcam_mcast: tcam multicast data
 */
अटल व्योम hns_dsaf_tcam_mc_get(
	काष्ठा dsaf_device *dsaf_dev, u32 address,
	काष्ठा dsaf_tbl_tcam_data *ptbl_tcam_data,
	काष्ठा dsaf_tbl_tcam_mcast_cfg *ptbl_tcam_mcast)
अणु
	u32 data_पंचांगp;

	spin_lock_bh(&dsaf_dev->tcam_lock);

	/*Write Addr*/
	hns_dsaf_tbl_tcam_addr_cfg(dsaf_dev, address);

	/*पढ़ो tcam item puls*/
	hns_dsaf_tbl_tcam_load_pul(dsaf_dev);

	/*पढ़ो tcam data*/
	ptbl_tcam_data->tbl_tcam_data_high =
		dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_RDATA_HIGH_0_REG);
	ptbl_tcam_data->tbl_tcam_data_low =
		dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_RDATA_LOW_0_REG);

	/*पढ़ो tcam mcast*/
	ptbl_tcam_mcast->tbl_mcast_port_msk[0] =
		dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_RAM_RDATA0_0_REG);
	ptbl_tcam_mcast->tbl_mcast_port_msk[1] =
		dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_RAM_RDATA1_0_REG);
	ptbl_tcam_mcast->tbl_mcast_port_msk[2] =
		dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_RAM_RDATA2_0_REG);
	ptbl_tcam_mcast->tbl_mcast_port_msk[3] =
		dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_RAM_RDATA3_0_REG);

	data_पंचांगp = dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_TCAM_RAM_RDATA4_0_REG);
	ptbl_tcam_mcast->tbl_mcast_item_vld =
		dsaf_get_bit(data_पंचांगp, DSAF_TBL_MCAST_CFG4_ITEM_VLD_S);
	ptbl_tcam_mcast->tbl_mcast_old_en =
		dsaf_get_bit(data_पंचांगp, DSAF_TBL_MCAST_CFG4_OLD_EN_S);
	ptbl_tcam_mcast->tbl_mcast_port_msk[4] =
		dsaf_get_field(data_पंचांगp, DSAF_TBL_MCAST_CFG4_VM128_112_M,
			       DSAF_TBL_MCAST_CFG4_VM128_112_S);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
पूर्ण

/**
 * hns_dsaf_tbl_line_init - INT
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_tbl_line_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 i;
	/* शेषly set all lineal mac table entry resulting discard */
	काष्ठा dsaf_tbl_line_cfg tbl_line[] = अणुअणु1, 0, 0पूर्ण पूर्ण;

	क्रम (i = 0; i < DSAF_LINE_SUM; i++)
		hns_dsaf_single_line_tbl_cfg(dsaf_dev, i, tbl_line);
पूर्ण

/**
 * hns_dsaf_tbl_tcam_init - INT
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_tbl_tcam_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 i;
	काष्ठा dsaf_tbl_tcam_data tcam_data[] = अणुअणु0, 0पूर्ण पूर्ण;
	काष्ठा dsaf_tbl_tcam_ucast_cfg tcam_ucast[] = अणुअणु0, 0, 0, 0, 0पूर्ण पूर्ण;

	/*tcam tbl*/
	क्रम (i = 0; i < DSAF_TCAM_SUM; i++)
		hns_dsaf_tcam_uc_cfg(dsaf_dev, i, tcam_data, tcam_ucast);
पूर्ण

/**
 * hns_dsaf_pfc_en_cfg - dsaf pfc छोड़ो cfg
 * @dsaf_dev: dsa fabric id
 * @mac_id: mac contrl block
 * @tc_en: traffic class
 */
अटल व्योम hns_dsaf_pfc_en_cfg(काष्ठा dsaf_device *dsaf_dev,
				पूर्णांक mac_id, पूर्णांक tc_en)
अणु
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_PFC_EN_0_REG + mac_id * 4, tc_en);
पूर्ण

अटल व्योम hns_dsaf_set_pfc_छोड़ो(काष्ठा dsaf_device *dsaf_dev,
				   पूर्णांक mac_id, पूर्णांक tx_en, पूर्णांक rx_en)
अणु
	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver)) अणु
		अगर (!tx_en || !rx_en)
			dev_err(dsaf_dev->dev, "dsaf v1 can not close pfc!\n");

		वापस;
	पूर्ण

	dsaf_set_dev_bit(dsaf_dev, DSAF_PAUSE_CFG_REG + mac_id * 4,
			 DSAF_PFC_PAUSE_RX_EN_B, !!rx_en);
	dsaf_set_dev_bit(dsaf_dev, DSAF_PAUSE_CFG_REG + mac_id * 4,
			 DSAF_PFC_PAUSE_TX_EN_B, !!tx_en);
पूर्ण

पूर्णांक hns_dsaf_set_rx_mac_छोड़ो_en(काष्ठा dsaf_device *dsaf_dev, पूर्णांक mac_id,
				 u32 en)
अणु
	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver)) अणु
		अगर (!en) अणु
			dev_err(dsaf_dev->dev, "dsafv1 can't close rx_pause!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dsaf_set_dev_bit(dsaf_dev, DSAF_PAUSE_CFG_REG + mac_id * 4,
			 DSAF_MAC_PAUSE_RX_EN_B, !!en);

	वापस 0;
पूर्ण

व्योम hns_dsaf_get_rx_mac_छोड़ो_en(काष्ठा dsaf_device *dsaf_dev, पूर्णांक mac_id,
				  u32 *en)
अणु
	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver))
		*en = 1;
	अन्यथा
		*en = dsaf_get_dev_bit(dsaf_dev,
				       DSAF_PAUSE_CFG_REG + mac_id * 4,
				       DSAF_MAC_PAUSE_RX_EN_B);
पूर्ण

/**
 * hns_dsaf_tbl_tcam_init - INT
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_comm_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 i;
	u32 o_dsaf_cfg;
	bool is_ver1 = AE_IS_VER1(dsaf_dev->dsaf_ver);

	o_dsaf_cfg = dsaf_पढ़ो_dev(dsaf_dev, DSAF_CFG_0_REG);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_EN_S, dsaf_dev->dsaf_en);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_TC_MODE_S, dsaf_dev->dsaf_tc_mode);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_CRC_EN_S, 0);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_MIX_MODE_S, 0);
	dsaf_set_bit(o_dsaf_cfg, DSAF_CFG_LOCA_ADDR_EN_S, 0);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_CFG_0_REG, o_dsaf_cfg);

	hns_dsaf_reg_cnt_clr_ce(dsaf_dev, 1);
	hns_dsaf_stp_port_type_cfg(dsaf_dev, DSAF_STP_PORT_TYPE_FORWARD);

	/* set 22 queue per tx ppe engine, only used in चयन mode */
	hns_dsaf_ppe_qid_cfg(dsaf_dev, DSAF_DEFAUTL_QUEUE_NUM_PER_PPE);

	/* set promisc def queue id */
	hns_dsaf_mix_def_qid_cfg(dsaf_dev);

	/* set inner loopback queue id */
	hns_dsaf_inner_qid_cfg(dsaf_dev);

	/* in non चयन mode, set all port to access mode */
	hns_dsaf_sw_port_type_cfg(dsaf_dev, DSAF_SW_PORT_TYPE_NON_VLAN);

	/*set dsaf pfc  to 0 क्रम parseing rx छोड़ो*/
	क्रम (i = 0; i < DSAF_COMM_CHN; i++) अणु
		hns_dsaf_pfc_en_cfg(dsaf_dev, i, 0);
		hns_dsaf_set_pfc_छोड़ो(dsaf_dev, i, is_ver1, is_ver1);
	पूर्ण

	/*msk and  clr exception irqs */
	क्रम (i = 0; i < DSAF_COMM_CHN; i++) अणु
		hns_dsaf_पूर्णांक_xge_src_clr(dsaf_dev, i, 0xfffffffful);
		hns_dsaf_पूर्णांक_ppe_src_clr(dsaf_dev, i, 0xfffffffful);
		hns_dsaf_पूर्णांक_rocee_src_clr(dsaf_dev, i, 0xfffffffful);

		hns_dsaf_पूर्णांक_xge_msk_set(dsaf_dev, i, 0xfffffffful);
		hns_dsaf_पूर्णांक_ppe_msk_set(dsaf_dev, i, 0xfffffffful);
		hns_dsaf_पूर्णांक_rocee_msk_set(dsaf_dev, i, 0xfffffffful);
	पूर्ण
	hns_dsaf_पूर्णांक_tbl_src_clr(dsaf_dev, 0xfffffffful);
	hns_dsaf_पूर्णांक_tbl_msk_set(dsaf_dev, 0xfffffffful);
पूर्ण

/**
 * hns_dsaf_inode_init - INT
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_inode_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 reg;
	u32 tc_cfg;
	u32 i;

	अगर (dsaf_dev->dsaf_tc_mode == HRD_DSAF_4TC_MODE)
		tc_cfg = HNS_DSAF_I4TC_CFG;
	अन्यथा
		tc_cfg = HNS_DSAF_I8TC_CFG;

	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver)) अणु
		क्रम (i = 0; i < DSAF_INODE_NUM; i++) अणु
			reg = DSAF_INODE_IN_PORT_NUM_0_REG + 0x80 * i;
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAF_INODE_IN_PORT_NUM_M,
					   DSAF_INODE_IN_PORT_NUM_S,
					   i % DSAF_XGE_NUM);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < DSAF_PORT_TYPE_NUM; i++) अणु
			reg = DSAF_INODE_IN_PORT_NUM_0_REG + 0x80 * i;
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAF_INODE_IN_PORT_NUM_M,
					   DSAF_INODE_IN_PORT_NUM_S, 0);
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAFV2_INODE_IN_PORT1_NUM_M,
					   DSAFV2_INODE_IN_PORT1_NUM_S, 1);
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAFV2_INODE_IN_PORT2_NUM_M,
					   DSAFV2_INODE_IN_PORT2_NUM_S, 2);
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAFV2_INODE_IN_PORT3_NUM_M,
					   DSAFV2_INODE_IN_PORT3_NUM_S, 3);
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAFV2_INODE_IN_PORT4_NUM_M,
					   DSAFV2_INODE_IN_PORT4_NUM_S, 4);
			dsaf_set_dev_field(dsaf_dev, reg,
					   DSAFV2_INODE_IN_PORT5_NUM_M,
					   DSAFV2_INODE_IN_PORT5_NUM_S, 5);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < DSAF_INODE_NUM; i++) अणु
		reg = DSAF_INODE_PRI_TC_CFG_0_REG + 0x80 * i;
		dsaf_ग_लिखो_dev(dsaf_dev, reg, tc_cfg);
	पूर्ण
पूर्ण

/**
 * hns_dsaf_sbm_init - INT
 * @dsaf_dev: dsa fabric id
 */
अटल पूर्णांक hns_dsaf_sbm_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 flag;
	u32 finish_msk;
	u32 cnt = 0;
	पूर्णांक ret;

	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver)) अणु
		hns_dsaf_sbm_bp_wl_cfg(dsaf_dev);
		finish_msk = DSAF_SRAM_INIT_OVER_M;
	पूर्ण अन्यथा अणु
		hns_dsafv2_sbm_bp_wl_cfg(dsaf_dev);
		finish_msk = DSAFV2_SRAM_INIT_OVER_M;
	पूर्ण

	/* enable sbm chanel, disable sbm chanel shcut function*/
	hns_dsaf_sbm_cfg(dsaf_dev);

	/* enable sbm mib */
	ret = hns_dsaf_sbm_cfg_mib_en(dsaf_dev);
	अगर (ret) अणु
		dev_err(dsaf_dev->dev,
			"hns_dsaf_sbm_cfg_mib_en fail,%s, ret=%d\n",
			dsaf_dev->ae_dev.name, ret);
		वापस ret;
	पूर्ण

	/* enable sbm initial link sram */
	hns_dsaf_sbm_link_sram_init_en(dsaf_dev);

	करो अणु
		usleep_range(200, 210);/*udelay(200);*/
		flag = dsaf_get_dev_field(dsaf_dev, DSAF_SRAM_INIT_OVER_0_REG,
					  finish_msk, DSAF_SRAM_INIT_OVER_S);
		cnt++;
	पूर्ण जबतक (flag != (finish_msk >> DSAF_SRAM_INIT_OVER_S) &&
		 cnt < DSAF_CFG_READ_CNT);

	अगर (flag != (finish_msk >> DSAF_SRAM_INIT_OVER_S)) अणु
		dev_err(dsaf_dev->dev,
			"hns_dsaf_sbm_init fail %s, flag=%d, cnt=%d\n",
			dsaf_dev->ae_dev.name, flag, cnt);
		वापस -ENODEV;
	पूर्ण

	hns_dsaf_rocee_bp_en(dsaf_dev);

	वापस 0;
पूर्ण

/**
 * hns_dsaf_tbl_init - INT
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_tbl_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	hns_dsaf_tbl_stat_en(dsaf_dev);

	hns_dsaf_tbl_tcam_init(dsaf_dev);
	hns_dsaf_tbl_line_init(dsaf_dev);
पूर्ण

/**
 * hns_dsaf_voq_init - INT
 * @dsaf_dev: dsa fabric id
 */
अटल व्योम hns_dsaf_voq_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	hns_dsaf_voq_bp_all_thrd_cfg(dsaf_dev);
पूर्ण

/**
 * hns_dsaf_init_hw - init dsa fabric hardware
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 */
अटल पूर्णांक hns_dsaf_init_hw(काष्ठा dsaf_device *dsaf_dev)
अणु
	पूर्णांक ret;

	dev_dbg(dsaf_dev->dev,
		"hns_dsaf_init_hw begin %s !\n", dsaf_dev->ae_dev.name);

	dsaf_dev->misc_op->dsaf_reset(dsaf_dev, 0);
	mdelay(10);
	dsaf_dev->misc_op->dsaf_reset(dsaf_dev, 1);

	hns_dsaf_comm_init(dsaf_dev);

	/*init XBAR_INODE*/
	hns_dsaf_inode_init(dsaf_dev);

	/*init SBM*/
	ret = hns_dsaf_sbm_init(dsaf_dev);
	अगर (ret)
		वापस ret;

	/*init TBL*/
	hns_dsaf_tbl_init(dsaf_dev);

	/*init VOQ*/
	hns_dsaf_voq_init(dsaf_dev);

	वापस 0;
पूर्ण

/**
 * hns_dsaf_हटाओ_hw - uninit dsa fabric hardware
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 */
अटल व्योम hns_dsaf_हटाओ_hw(काष्ठा dsaf_device *dsaf_dev)
अणु
	/*reset*/
	dsaf_dev->misc_op->dsaf_reset(dsaf_dev, 0);
पूर्ण

/**
 * hns_dsaf_init - init dsa fabric
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * वापस 0 - success , negative --fail
 */
अटल पूर्णांक hns_dsaf_init(काष्ठा dsaf_device *dsaf_dev)
अणु
	काष्ठा dsaf_drv_priv *priv =
	    (काष्ठा dsaf_drv_priv *)hns_dsaf_dev_priv(dsaf_dev);
	u32 i;
	पूर्णांक ret;

	अगर (HNS_DSAF_IS_DEBUG(dsaf_dev))
		वापस 0;

	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver))
		dsaf_dev->tcam_max_num = DSAF_TCAM_SUM;
	अन्यथा
		dsaf_dev->tcam_max_num =
			DSAF_TCAM_SUM - DSAFV2_MAC_FUZZY_TCAM_NUM;

	spin_lock_init(&dsaf_dev->tcam_lock);
	ret = hns_dsaf_init_hw(dsaf_dev);
	अगर (ret)
		वापस ret;

	/* दो_स्मृति mem क्रम tcam mac key(vlan+mac) */
	priv->soft_mac_tbl = vzalloc(array_size(DSAF_TCAM_SUM,
						माप(*priv->soft_mac_tbl)));
	अगर (!priv->soft_mac_tbl) अणु
		ret = -ENOMEM;
		जाओ हटाओ_hw;
	पूर्ण

	/*all entry invall */
	क्रम (i = 0; i < DSAF_TCAM_SUM; i++)
		(priv->soft_mac_tbl + i)->index = DSAF_INVALID_ENTRY_IDX;

	वापस 0;

हटाओ_hw:
	hns_dsaf_हटाओ_hw(dsaf_dev);
	वापस ret;
पूर्ण

/**
 * hns_dsaf_मुक्त - मुक्त dsa fabric
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 */
अटल व्योम hns_dsaf_मुक्त(काष्ठा dsaf_device *dsaf_dev)
अणु
	काष्ठा dsaf_drv_priv *priv =
	    (काष्ठा dsaf_drv_priv *)hns_dsaf_dev_priv(dsaf_dev);

	hns_dsaf_हटाओ_hw(dsaf_dev);

	/* मुक्त all mac mem */
	vमुक्त(priv->soft_mac_tbl);
	priv->soft_mac_tbl = शून्य;
पूर्ण

/**
 * hns_dsaf_find_soft_mac_entry - find dsa fabric soft entry
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * @mac_key: mac entry काष्ठा poपूर्णांकer
 */
अटल u16 hns_dsaf_find_soft_mac_entry(
	काष्ठा dsaf_device *dsaf_dev,
	काष्ठा dsaf_drv_tbl_tcam_key *mac_key)
अणु
	काष्ठा dsaf_drv_priv *priv =
	    (काष्ठा dsaf_drv_priv *)hns_dsaf_dev_priv(dsaf_dev);
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_entry;
	u32 i;

	soft_mac_entry = priv->soft_mac_tbl;
	क्रम (i = 0; i < dsaf_dev->tcam_max_num; i++) अणु
		/* invall tab entry */
		अगर ((soft_mac_entry->index != DSAF_INVALID_ENTRY_IDX) &&
		    (soft_mac_entry->tcam_key.high.val == mac_key->high.val) &&
		    (soft_mac_entry->tcam_key.low.val == mac_key->low.val))
			/* वापस find result --soft index */
			वापस soft_mac_entry->index;

		soft_mac_entry++;
	पूर्ण
	वापस DSAF_INVALID_ENTRY_IDX;
पूर्ण

/**
 * hns_dsaf_find_empty_mac_entry - search dsa fabric soft empty-entry
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 */
अटल u16 hns_dsaf_find_empty_mac_entry(काष्ठा dsaf_device *dsaf_dev)
अणु
	काष्ठा dsaf_drv_priv *priv =
	    (काष्ठा dsaf_drv_priv *)hns_dsaf_dev_priv(dsaf_dev);
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_entry;
	u32 i;

	soft_mac_entry = priv->soft_mac_tbl;
	क्रम (i = 0; i < dsaf_dev->tcam_max_num; i++) अणु
		/* inv all entry */
		अगर (soft_mac_entry->index == DSAF_INVALID_ENTRY_IDX)
			/* वापस find result --soft index */
			वापस i;

		soft_mac_entry++;
	पूर्ण
	वापस DSAF_INVALID_ENTRY_IDX;
पूर्ण

/**
 * hns_dsaf_find_empty_mac_entry_reverse
 * search dsa fabric soft empty-entry from the end
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 */
अटल u16 hns_dsaf_find_empty_mac_entry_reverse(काष्ठा dsaf_device *dsaf_dev)
अणु
	काष्ठा dsaf_drv_priv *priv = hns_dsaf_dev_priv(dsaf_dev);
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_entry;
	पूर्णांक i;

	soft_mac_entry = priv->soft_mac_tbl + (DSAF_TCAM_SUM - 1);
	क्रम (i = (DSAF_TCAM_SUM - 1); i > 0; i--) अणु
		/* search all entry from end to start.*/
		अगर (soft_mac_entry->index == DSAF_INVALID_ENTRY_IDX)
			वापस i;
		soft_mac_entry--;
	पूर्ण
	वापस DSAF_INVALID_ENTRY_IDX;
पूर्ण

/**
 * hns_dsaf_set_mac_key - set mac key
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * @mac_key: tcam key poपूर्णांकer
 * @vlan_id: vlan id
 * @in_port_num: input port num
 * @addr: mac addr
 */
अटल व्योम hns_dsaf_set_mac_key(
	काष्ठा dsaf_device *dsaf_dev,
	काष्ठा dsaf_drv_tbl_tcam_key *mac_key, u16 vlan_id, u8 in_port_num,
	u8 *addr)
अणु
	u8 port;

	अगर (dsaf_dev->dsaf_mode <= DSAF_MODE_ENABLE)
		/*DSAF mode : in port id fixed 0*/
		port = 0;
	अन्यथा
		/*non-dsaf mode*/
		port = in_port_num;

	mac_key->high.bits.mac_0 = addr[0];
	mac_key->high.bits.mac_1 = addr[1];
	mac_key->high.bits.mac_2 = addr[2];
	mac_key->high.bits.mac_3 = addr[3];
	mac_key->low.bits.mac_4 = addr[4];
	mac_key->low.bits.mac_5 = addr[5];
	mac_key->low.bits.port_vlan = 0;
	dsaf_set_field(mac_key->low.bits.port_vlan, DSAF_TBL_TCAM_KEY_VLAN_M,
		       DSAF_TBL_TCAM_KEY_VLAN_S, vlan_id);
	dsaf_set_field(mac_key->low.bits.port_vlan, DSAF_TBL_TCAM_KEY_PORT_M,
		       DSAF_TBL_TCAM_KEY_PORT_S, port);
पूर्ण

/**
 * hns_dsaf_set_mac_uc_entry - set mac uc-entry
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * @mac_entry: uc-mac entry
 */
पूर्णांक hns_dsaf_set_mac_uc_entry(
	काष्ठा dsaf_device *dsaf_dev,
	काष्ठा dsaf_drv_mac_single_dest_entry *mac_entry)
अणु
	u16 entry_index;
	काष्ठा dsaf_drv_tbl_tcam_key mac_key;
	काष्ठा dsaf_tbl_tcam_ucast_cfg mac_data;
	काष्ठा dsaf_drv_priv *priv =
	    (काष्ठा dsaf_drv_priv *)hns_dsaf_dev_priv(dsaf_dev);
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_entry = priv->soft_mac_tbl;
	काष्ठा dsaf_tbl_tcam_data tcam_data;

	/* mac addr check */
	अगर (MAC_IS_ALL_ZEROS(mac_entry->addr) ||
	    MAC_IS_BROADCAST(mac_entry->addr) ||
	    MAC_IS_MULTICAST(mac_entry->addr)) अणु
		dev_err(dsaf_dev->dev, "set_uc %s Mac %pM err!\n",
			dsaf_dev->ae_dev.name, mac_entry->addr);
		वापस -EINVAL;
	पूर्ण

	/* config key */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, mac_entry->in_vlan_id,
			     mac_entry->in_port_num, mac_entry->addr);

	/* entry ie exist? */
	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);
	अगर (entry_index == DSAF_INVALID_ENTRY_IDX) अणु
		/*अगर has not inv entry,find a empty entry */
		entry_index = hns_dsaf_find_empty_mac_entry(dsaf_dev);
		अगर (entry_index == DSAF_INVALID_ENTRY_IDX) अणु
			/* has not empty,वापस error */
			dev_err(dsaf_dev->dev,
				"set_uc_entry failed, %s Mac key(%#x:%#x)\n",
				dsaf_dev->ae_dev.name,
				mac_key.high.val, mac_key.low.val);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	dev_dbg(dsaf_dev->dev,
		"set_uc_entry, %s Mac key(%#x:%#x) entry_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.val,
		mac_key.low.val, entry_index);

	/* config hardware entry */
	mac_data.tbl_ucast_item_vld = 1;
	mac_data.tbl_ucast_mac_discard = 0;
	mac_data.tbl_ucast_old_en = 0;
	/* शेष config dvc to 0 */
	mac_data.tbl_ucast_dvc = 0;
	mac_data.tbl_ucast_out_port = mac_entry->port_num;
	tcam_data.tbl_tcam_data_high = mac_key.high.val;
	tcam_data.tbl_tcam_data_low = mac_key.low.val;

	hns_dsaf_tcam_uc_cfg(dsaf_dev, entry_index, &tcam_data, &mac_data);

	/* config software entry */
	soft_mac_entry += entry_index;
	soft_mac_entry->index = entry_index;
	soft_mac_entry->tcam_key.high.val = mac_key.high.val;
	soft_mac_entry->tcam_key.low.val = mac_key.low.val;

	वापस 0;
पूर्ण

पूर्णांक hns_dsaf_rm_mac_addr(
	काष्ठा dsaf_device *dsaf_dev,
	काष्ठा dsaf_drv_mac_single_dest_entry *mac_entry)
अणु
	u16 entry_index;
	काष्ठा dsaf_tbl_tcam_ucast_cfg mac_data;
	काष्ठा dsaf_drv_tbl_tcam_key mac_key;

	/* mac addr check */
	अगर (!is_valid_ether_addr(mac_entry->addr)) अणु
		dev_err(dsaf_dev->dev, "rm_uc_addr %s Mac %pM err!\n",
			dsaf_dev->ae_dev.name, mac_entry->addr);
		वापस -EINVAL;
	पूर्ण

	/* config key */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, mac_entry->in_vlan_id,
			     mac_entry->in_port_num, mac_entry->addr);

	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);
	अगर (entry_index == DSAF_INVALID_ENTRY_IDX) अणु
		/* can not find the tcam entry, वापस 0 */
		dev_info(dsaf_dev->dev,
			 "rm_uc_addr no tcam, %s Mac key(%#x:%#x)\n",
			 dsaf_dev->ae_dev.name,
			 mac_key.high.val, mac_key.low.val);
		वापस 0;
	पूर्ण

	dev_dbg(dsaf_dev->dev,
		"rm_uc_addr, %s Mac key(%#x:%#x) entry_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.val,
		mac_key.low.val, entry_index);

	hns_dsaf_tcam_uc_get(
			dsaf_dev, entry_index,
			(काष्ठा dsaf_tbl_tcam_data *)&mac_key,
			&mac_data);

	/* unicast entry not used locally should not clear */
	अगर (mac_entry->port_num != mac_data.tbl_ucast_out_port)
		वापस -EFAULT;

	वापस hns_dsaf_del_mac_entry(dsaf_dev,
				      mac_entry->in_vlan_id,
				      mac_entry->in_port_num,
				      mac_entry->addr);
पूर्ण

अटल व्योम hns_dsaf_setup_mc_mask(काष्ठा dsaf_device *dsaf_dev,
				   u8 port_num, u8 *mask, u8 *addr)
अणु
	अगर (MAC_IS_BROADCAST(addr))
		eth_broadcast_addr(mask);
	अन्यथा
		स_नकल(mask, dsaf_dev->mac_cb[port_num]->mc_mask, ETH_ALEN);
पूर्ण

अटल व्योम hns_dsaf_mc_mask_bit_clear(अक्षर *dst, स्थिर अक्षर *src)
अणु
	u16 *a = (u16 *)dst;
	स्थिर u16 *b = (स्थिर u16 *)src;

	a[0] &= b[0];
	a[1] &= b[1];
	a[2] &= b[2];
पूर्ण

/**
 * hns_dsaf_add_mac_mc_port - add mac mc-port
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * @mac_entry: mc-mac entry
 */
पूर्णांक hns_dsaf_add_mac_mc_port(काष्ठा dsaf_device *dsaf_dev,
			     काष्ठा dsaf_drv_mac_single_dest_entry *mac_entry)
अणु
	u16 entry_index;
	काष्ठा dsaf_drv_tbl_tcam_key mac_key;
	काष्ठा dsaf_drv_tbl_tcam_key mask_key;
	काष्ठा dsaf_tbl_tcam_data *pmask_key = शून्य;
	काष्ठा dsaf_tbl_tcam_mcast_cfg mac_data;
	काष्ठा dsaf_drv_priv *priv = hns_dsaf_dev_priv(dsaf_dev);
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_entry = priv->soft_mac_tbl;
	काष्ठा dsaf_tbl_tcam_data tcam_data;
	u8 mc_addr[ETH_ALEN];
	पूर्णांक mskid;

	/*chechk mac addr */
	अगर (MAC_IS_ALL_ZEROS(mac_entry->addr)) अणु
		dev_err(dsaf_dev->dev, "set_entry failed,addr %pM!\n",
			mac_entry->addr);
		वापस -EINVAL;
	पूर्ण

	ether_addr_copy(mc_addr, mac_entry->addr);
	अगर (!AE_IS_VER1(dsaf_dev->dsaf_ver)) अणु
		u8 mc_mask[ETH_ALEN];

		/* prepare क्रम key data setting */
		hns_dsaf_setup_mc_mask(dsaf_dev, mac_entry->in_port_num,
				       mc_mask, mac_entry->addr);
		hns_dsaf_mc_mask_bit_clear(mc_addr, mc_mask);

		/* config key mask */
		hns_dsaf_set_mac_key(dsaf_dev, &mask_key,
				     0x0,
				     0xff,
				     mc_mask);

		pmask_key = (काष्ठा dsaf_tbl_tcam_data *)(&mask_key);
	पूर्ण

	/*config key */
	hns_dsaf_set_mac_key(
		dsaf_dev, &mac_key, mac_entry->in_vlan_id,
		mac_entry->in_port_num, mc_addr);

	स_रखो(&mac_data, 0, माप(काष्ठा dsaf_tbl_tcam_mcast_cfg));

	/* check अगर the tcam is exist */
	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);
	अगर (entry_index == DSAF_INVALID_ENTRY_IDX) अणु
		/*अगर hasnot , find a empty*/
		entry_index = hns_dsaf_find_empty_mac_entry(dsaf_dev);
		अगर (entry_index == DSAF_INVALID_ENTRY_IDX) अणु
			/*अगर hasnot empty, error*/
			dev_err(dsaf_dev->dev,
				"set_uc_entry failed, %s Mac key(%#x:%#x)\n",
				dsaf_dev->ae_dev.name, mac_key.high.val,
				mac_key.low.val);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* अगर exist, add in */
		hns_dsaf_tcam_mc_get(dsaf_dev, entry_index, &tcam_data,
				     &mac_data);
	पूर्ण

	/* config hardware entry */
	अगर (mac_entry->port_num < DSAF_SERVICE_NW_NUM) अणु
		mskid = mac_entry->port_num;
	पूर्ण अन्यथा अगर (mac_entry->port_num >= DSAF_BASE_INNER_PORT_NUM) अणु
		mskid = mac_entry->port_num -
			DSAF_BASE_INNER_PORT_NUM + DSAF_SERVICE_NW_NUM;
	पूर्ण अन्यथा अणु
		dev_err(dsaf_dev->dev,
			"%s,pnum(%d)error,key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name, mac_entry->port_num,
			mac_key.high.val, mac_key.low.val);
		वापस -EINVAL;
	पूर्ण
	dsaf_set_bit(mac_data.tbl_mcast_port_msk[mskid / 32], mskid % 32, 1);
	mac_data.tbl_mcast_old_en = 0;
	mac_data.tbl_mcast_item_vld = 1;

	dev_dbg(dsaf_dev->dev,
		"set_uc_entry, %s Mac key(%#x:%#x) entry_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.val,
		mac_key.low.val, entry_index);

	tcam_data.tbl_tcam_data_high = mac_key.high.val;
	tcam_data.tbl_tcam_data_low = mac_key.low.val;

	/* config mc entry with mask */
	hns_dsaf_tcam_mc_cfg(dsaf_dev, entry_index, &tcam_data,
			     pmask_key, &mac_data);

	/*config software entry */
	soft_mac_entry += entry_index;
	soft_mac_entry->index = entry_index;
	soft_mac_entry->tcam_key.high.val = mac_key.high.val;
	soft_mac_entry->tcam_key.low.val = mac_key.low.val;

	वापस 0;
पूर्ण

/**
 * hns_dsaf_del_mac_entry - del mac mc-port
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * @vlan_id: vlian id
 * @in_port_num: input port num
 * @addr : mac addr
 */
पूर्णांक hns_dsaf_del_mac_entry(काष्ठा dsaf_device *dsaf_dev, u16 vlan_id,
			   u8 in_port_num, u8 *addr)
अणु
	u16 entry_index;
	काष्ठा dsaf_drv_tbl_tcam_key mac_key;
	काष्ठा dsaf_drv_priv *priv =
	    (काष्ठा dsaf_drv_priv *)hns_dsaf_dev_priv(dsaf_dev);
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_entry = priv->soft_mac_tbl;

	/*check mac addr */
	अगर (MAC_IS_ALL_ZEROS(addr) || MAC_IS_BROADCAST(addr)) अणु
		dev_err(dsaf_dev->dev, "del_entry failed,addr %pM!\n",
			addr);
		वापस -EINVAL;
	पूर्ण

	/*config key */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, vlan_id, in_port_num, addr);

	/*exist ?*/
	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);
	अगर (entry_index == DSAF_INVALID_ENTRY_IDX) अणु
		/*not exist, error */
		dev_err(dsaf_dev->dev,
			"del_mac_entry failed, %s Mac key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name,
			mac_key.high.val, mac_key.low.val);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(dsaf_dev->dev,
		"del_mac_entry, %s Mac key(%#x:%#x) entry_index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.val,
		mac_key.low.val, entry_index);

	/*करो del opt*/
	hns_dsaf_tcam_mc_invld(dsaf_dev, entry_index);

	/*del soft emtry */
	soft_mac_entry += entry_index;
	soft_mac_entry->index = DSAF_INVALID_ENTRY_IDX;

	वापस 0;
पूर्ण

/**
 * hns_dsaf_del_mac_mc_port - del mac mc- port
 * @dsaf_dev: dsa fabric device काष्ठा poपूर्णांकer
 * @mac_entry: mac entry
 */
पूर्णांक hns_dsaf_del_mac_mc_port(काष्ठा dsaf_device *dsaf_dev,
			     काष्ठा dsaf_drv_mac_single_dest_entry *mac_entry)
अणु
	u16 entry_index;
	काष्ठा dsaf_drv_tbl_tcam_key mac_key;
	काष्ठा dsaf_drv_priv *priv = hns_dsaf_dev_priv(dsaf_dev);
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_entry = priv->soft_mac_tbl;
	u16 vlan_id;
	u8 in_port_num;
	काष्ठा dsaf_tbl_tcam_mcast_cfg mac_data;
	काष्ठा dsaf_tbl_tcam_data tcam_data;
	पूर्णांक mskid;
	स्थिर u8 empty_msk[माप(mac_data.tbl_mcast_port_msk)] = अणु0पूर्ण;
	काष्ठा dsaf_drv_tbl_tcam_key mask_key;
	काष्ठा dsaf_tbl_tcam_data *pmask_key = शून्य;
	u8 mc_addr[ETH_ALEN];

	अगर (!(व्योम *)mac_entry) अणु
		dev_err(dsaf_dev->dev,
			"hns_dsaf_del_mac_mc_port mac_entry is NULL\n");
		वापस -EINVAL;
	पूर्ण

	/*check mac addr */
	अगर (MAC_IS_ALL_ZEROS(mac_entry->addr)) अणु
		dev_err(dsaf_dev->dev, "del_port failed, addr %pM!\n",
			mac_entry->addr);
		वापस -EINVAL;
	पूर्ण

	/* always mask vlan_id field */
	ether_addr_copy(mc_addr, mac_entry->addr);

	अगर (!AE_IS_VER1(dsaf_dev->dsaf_ver)) अणु
		u8 mc_mask[ETH_ALEN];

		/* prepare क्रम key data setting */
		hns_dsaf_setup_mc_mask(dsaf_dev, mac_entry->in_port_num,
				       mc_mask, mac_entry->addr);
		hns_dsaf_mc_mask_bit_clear(mc_addr, mc_mask);

		/* config key mask */
		hns_dsaf_set_mac_key(dsaf_dev, &mask_key, 0x00, 0xff, mc_mask);

		pmask_key = (काष्ठा dsaf_tbl_tcam_data *)(&mask_key);
	पूर्ण

	/* get key info */
	vlan_id = mac_entry->in_vlan_id;
	in_port_num = mac_entry->in_port_num;

	/* config key */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, vlan_id, in_port_num, mc_addr);

	/* check अगर the tcam entry is exist */
	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);
	अगर (entry_index == DSAF_INVALID_ENTRY_IDX) अणु
		/*find none */
		dev_err(dsaf_dev->dev,
			"find_soft_mac_entry failed, %s Mac key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name,
			mac_key.high.val, mac_key.low.val);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dsaf_dev->dev,
		"del_mac_mc_port, %s key(%#x:%#x) index%d\n",
		dsaf_dev->ae_dev.name, mac_key.high.val,
		mac_key.low.val, entry_index);

	/* पढ़ो entry */
	hns_dsaf_tcam_mc_get(dsaf_dev, entry_index, &tcam_data, &mac_data);

	/*del the port*/
	अगर (mac_entry->port_num < DSAF_SERVICE_NW_NUM) अणु
		mskid = mac_entry->port_num;
	पूर्ण अन्यथा अगर (mac_entry->port_num >= DSAF_BASE_INNER_PORT_NUM) अणु
		mskid = mac_entry->port_num -
			DSAF_BASE_INNER_PORT_NUM + DSAF_SERVICE_NW_NUM;
	पूर्ण अन्यथा अणु
		dev_err(dsaf_dev->dev,
			"%s,pnum(%d)error,key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name, mac_entry->port_num,
			mac_key.high.val, mac_key.low.val);
		वापस -EINVAL;
	पूर्ण
	dsaf_set_bit(mac_data.tbl_mcast_port_msk[mskid / 32], mskid % 32, 0);

	/*check non port, करो del entry */
	अगर (!स_भेद(mac_data.tbl_mcast_port_msk, empty_msk,
		    माप(mac_data.tbl_mcast_port_msk))) अणु
		hns_dsaf_tcam_mc_invld(dsaf_dev, entry_index);

		/* del soft entry */
		soft_mac_entry += entry_index;
		soft_mac_entry->index = DSAF_INVALID_ENTRY_IDX;
	पूर्ण अन्यथा अणु /* not zero, just del port, update */
		tcam_data.tbl_tcam_data_high = mac_key.high.val;
		tcam_data.tbl_tcam_data_low = mac_key.low.val;

		hns_dsaf_tcam_mc_cfg(dsaf_dev, entry_index,
				     &tcam_data,
				     pmask_key, &mac_data);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hns_dsaf_clr_mac_mc_port(काष्ठा dsaf_device *dsaf_dev, u8 mac_id,
			     u8 port_num)
अणु
	काष्ठा dsaf_drv_priv *priv = hns_dsaf_dev_priv(dsaf_dev);
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_entry;
	काष्ठा dsaf_tbl_tcam_mcast_cfg mac_data;
	पूर्णांक ret = 0, i;

	अगर (HNS_DSAF_IS_DEBUG(dsaf_dev))
		वापस 0;

	क्रम (i = 0; i < DSAF_TCAM_SUM - DSAFV2_MAC_FUZZY_TCAM_NUM; i++) अणु
		u8 addr[ETH_ALEN];
		u8 port;

		soft_mac_entry = priv->soft_mac_tbl + i;

		hns_dsaf_tcam_addr_get(&soft_mac_entry->tcam_key, addr);
		port = dsaf_get_field(
				soft_mac_entry->tcam_key.low.bits.port_vlan,
				DSAF_TBL_TCAM_KEY_PORT_M,
				DSAF_TBL_TCAM_KEY_PORT_S);
		/* check valid tcam mc entry */
		अगर (soft_mac_entry->index != DSAF_INVALID_ENTRY_IDX &&
		    port == mac_id &&
		    is_multicast_ether_addr(addr) &&
		    !is_broadcast_ether_addr(addr)) अणु
			स्थिर u32 empty_msk[DSAF_PORT_MSK_NUM] = अणु0पूर्ण;
			काष्ठा dsaf_drv_mac_single_dest_entry mac_entry;

			/* disable receiving of this multicast address क्रम
			 * the VF.
			 */
			ether_addr_copy(mac_entry.addr, addr);
			mac_entry.in_vlan_id = dsaf_get_field(
				soft_mac_entry->tcam_key.low.bits.port_vlan,
				DSAF_TBL_TCAM_KEY_VLAN_M,
				DSAF_TBL_TCAM_KEY_VLAN_S);
			mac_entry.in_port_num = mac_id;
			mac_entry.port_num = port_num;
			अगर (hns_dsaf_del_mac_mc_port(dsaf_dev, &mac_entry)) अणु
				ret = -EINVAL;
				जारी;
			पूर्ण

			/* disable receiving of this multicast address क्रम
			 * the mac port अगर all VF are disable
			 */
			hns_dsaf_tcam_mc_get(dsaf_dev, i,
					     (काष्ठा dsaf_tbl_tcam_data *)
					     (&soft_mac_entry->tcam_key),
					     &mac_data);
			dsaf_set_bit(mac_data.tbl_mcast_port_msk[mac_id / 32],
				     mac_id % 32, 0);
			अगर (!स_भेद(mac_data.tbl_mcast_port_msk, empty_msk,
				    माप(u32) * DSAF_PORT_MSK_NUM)) अणु
				mac_entry.port_num = mac_id;
				अगर (hns_dsaf_del_mac_mc_port(dsaf_dev,
							     &mac_entry)) अणु
					ret = -EINVAL;
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा dsaf_device *hns_dsaf_alloc_dev(काष्ठा device *dev,
					      माप_प्रकार माप_priv)
अणु
	काष्ठा dsaf_device *dsaf_dev;

	dsaf_dev = devm_kzalloc(dev,
				माप(*dsaf_dev) + माप_priv, GFP_KERNEL);
	अगर (unlikely(!dsaf_dev)) अणु
		dsaf_dev = ERR_PTR(-ENOMEM);
	पूर्ण अन्यथा अणु
		dsaf_dev->dev = dev;
		dev_set_drvdata(dev, dsaf_dev);
	पूर्ण

	वापस dsaf_dev;
पूर्ण

/**
 * hns_dsaf_मुक्त_dev - मुक्त dev mem
 * @dsaf_dev: काष्ठा device poपूर्णांकer
 */
अटल व्योम hns_dsaf_मुक्त_dev(काष्ठा dsaf_device *dsaf_dev)
अणु
	(व्योम)dev_set_drvdata(dsaf_dev->dev, शून्य);
पूर्ण

/**
 * dsaf_pfc_unit_cnt - set pfc unit count
 * @dsaf_dev: dsa fabric id
 * @mac_id: id in use
 * @rate:  value array
 */
अटल व्योम hns_dsaf_pfc_unit_cnt(काष्ठा dsaf_device *dsaf_dev, पूर्णांक  mac_id,
				  क्रमागत dsaf_port_rate_mode rate)
अणु
	u32 unit_cnt;

	चयन (rate) अणु
	हाल DSAF_PORT_RATE_10000:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOR_XGE;
		अवरोध;
	हाल DSAF_PORT_RATE_1000:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOR_GE_1000;
		अवरोध;
	हाल DSAF_PORT_RATE_2500:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOR_GE_1000;
		अवरोध;
	शेष:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOR_XGE;
	पूर्ण

	dsaf_set_dev_field(dsaf_dev,
			   (DSAF_PFC_UNIT_CNT_0_REG + 0x4 * (u64)mac_id),
			   DSAF_PFC_UNINT_CNT_M, DSAF_PFC_UNINT_CNT_S,
			   unit_cnt);
पूर्ण

/**
 * dsaf_port_work_rate_cfg - fअगरo
 * @dsaf_dev: dsa fabric id
 * @mac_id: mac contrl block
 * @rate_mode: value array
 */
अटल व्योम
hns_dsaf_port_work_rate_cfg(काष्ठा dsaf_device *dsaf_dev, पूर्णांक mac_id,
			    क्रमागत dsaf_port_rate_mode rate_mode)
अणु
	u32 port_work_mode;

	port_work_mode = dsaf_पढ़ो_dev(
		dsaf_dev, DSAF_XGE_GE_WORK_MODE_0_REG + 0x4 * (u64)mac_id);

	अगर (rate_mode == DSAF_PORT_RATE_10000)
		dsaf_set_bit(port_work_mode, DSAF_XGE_GE_WORK_MODE_S, 1);
	अन्यथा
		dsaf_set_bit(port_work_mode, DSAF_XGE_GE_WORK_MODE_S, 0);

	dsaf_ग_लिखो_dev(dsaf_dev,
		       DSAF_XGE_GE_WORK_MODE_0_REG + 0x4 * (u64)mac_id,
		       port_work_mode);

	hns_dsaf_pfc_unit_cnt(dsaf_dev, mac_id, rate_mode);
पूर्ण

/**
 * hns_dsaf_fix_mac_mode - dsaf modअगरy mac mode
 * @mac_cb: mac contrl block
 */
व्योम hns_dsaf_fix_mac_mode(काष्ठा hns_mac_cb *mac_cb)
अणु
	क्रमागत dsaf_port_rate_mode mode;
	काष्ठा dsaf_device *dsaf_dev = mac_cb->dsaf_dev;
	पूर्णांक mac_id = mac_cb->mac_id;

	अगर (mac_cb->mac_type != HNAE_PORT_SERVICE)
		वापस;
	अगर (mac_cb->phy_अगर == PHY_INTERFACE_MODE_XGMII)
		mode = DSAF_PORT_RATE_10000;
	अन्यथा
		mode = DSAF_PORT_RATE_1000;

	hns_dsaf_port_work_rate_cfg(dsaf_dev, mac_id, mode);
पूर्ण

अटल u32 hns_dsaf_get_inode_prio_reg(पूर्णांक index)
अणु
	पूर्णांक base_index, offset;
	u32 base_addr = DSAF_INODE_IN_PRIO_PAUSE_BASE_REG;

	base_index = (index + 1) / DSAF_REG_PER_ZONE;
	offset = (index + 1) % DSAF_REG_PER_ZONE;

	वापस base_addr + DSAF_INODE_IN_PRIO_PAUSE_BASE_OFFSET * base_index +
		DSAF_INODE_IN_PRIO_PAUSE_OFFSET * offset;
पूर्ण

व्योम hns_dsaf_update_stats(काष्ठा dsaf_device *dsaf_dev, u32 node_num)
अणु
	काष्ठा dsaf_hw_stats *hw_stats
		= &dsaf_dev->hw_stats[node_num];
	bool is_ver1 = AE_IS_VER1(dsaf_dev->dsaf_ver);
	पूर्णांक i;
	u32 reg_पंचांगp;

	hw_stats->pad_drop += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_PAD_DISCARD_NUM_0_REG + 0x80 * (u64)node_num);
	hw_stats->man_pkts += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_FINAL_IN_MAN_NUM_0_REG + 0x80 * (u64)node_num);
	hw_stats->rx_pkts += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_FINAL_IN_PKT_NUM_0_REG + 0x80 * (u64)node_num);
	hw_stats->rx_pkt_id += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_SBM_PID_NUM_0_REG + 0x80 * (u64)node_num);

	reg_पंचांगp = is_ver1 ? DSAF_INODE_FINAL_IN_PAUSE_NUM_0_REG :
			    DSAFV2_INODE_FINAL_IN_PAUSE_NUM_0_REG;
	hw_stats->rx_छोड़ो_frame +=
		dsaf_पढ़ो_dev(dsaf_dev, reg_पंचांगp + 0x80 * (u64)node_num);

	hw_stats->release_buf_num += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_SBM_RELS_NUM_0_REG + 0x80 * (u64)node_num);
	hw_stats->sbm_drop += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_SBM_DROP_NUM_0_REG + 0x80 * (u64)node_num);
	hw_stats->crc_false += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_CRC_FALSE_NUM_0_REG + 0x80 * (u64)node_num);
	hw_stats->bp_drop += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_BP_DISCARD_NUM_0_REG + 0x80 * (u64)node_num);
	hw_stats->rslt_drop += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_RSLT_DISCARD_NUM_0_REG + 0x80 * (u64)node_num);
	hw_stats->local_addr_false += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_LOCAL_ADDR_FALSE_NUM_0_REG + 0x80 * (u64)node_num);

	hw_stats->vlan_drop += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_SW_VLAN_TAG_DISC_0_REG + 4 * (u64)node_num);
	hw_stats->stp_drop += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_INODE_IN_DATA_STP_DISC_0_REG + 4 * (u64)node_num);

	/* pfc छोड़ो frame statistics stored in dsaf inode*/
	अगर ((node_num < DSAF_SERVICE_NW_NUM) && !is_ver1) अणु
		क्रम (i = 0; i < DSAF_PRIO_NR; i++) अणु
			reg_पंचांगp = hns_dsaf_get_inode_prio_reg(i);
			hw_stats->rx_pfc[i] += dsaf_पढ़ो_dev(dsaf_dev,
				reg_पंचांगp + 0x4 * (u64)node_num);
			hw_stats->tx_pfc[i] += dsaf_पढ़ो_dev(dsaf_dev,
				DSAF_XOD_XGE_PFC_PRIO_CNT_BASE_REG +
				DSAF_XOD_XGE_PFC_PRIO_CNT_OFFSET * i +
				0xF0 * (u64)node_num);
		पूर्ण
	पूर्ण
	hw_stats->tx_pkts += dsaf_पढ़ो_dev(dsaf_dev,
		DSAF_XOD_RCVPKT_CNT_0_REG + 0x90 * (u64)node_num);
पूर्ण

/**
 *hns_dsaf_get_regs - dump dsaf regs
 *@ddev: dsaf device
 *@port: port
 *@data:data क्रम value of regs
 */
व्योम hns_dsaf_get_regs(काष्ठा dsaf_device *ddev, u32 port, व्योम *data)
अणु
	u32 i;
	u32 j;
	u32 *p = data;
	u32 reg_पंचांगp;
	bool is_ver1 = AE_IS_VER1(ddev->dsaf_ver);

	/* dsaf common रेजिस्टरs */
	p[0] = dsaf_पढ़ो_dev(ddev, DSAF_SRAM_INIT_OVER_0_REG);
	p[1] = dsaf_पढ़ो_dev(ddev, DSAF_CFG_0_REG);
	p[2] = dsaf_पढ़ो_dev(ddev, DSAF_ECC_ERR_INVERT_0_REG);
	p[3] = dsaf_पढ़ो_dev(ddev, DSAF_ABNORMAL_TIMEOUT_0_REG);
	p[4] = dsaf_पढ़ो_dev(ddev, DSAF_FSM_TIMEOUT_0_REG);
	p[5] = dsaf_पढ़ो_dev(ddev, DSAF_DSA_REG_CNT_CLR_CE_REG);
	p[6] = dsaf_पढ़ो_dev(ddev, DSAF_DSA_SBM_INF_FIFO_THRD_REG);
	p[7] = dsaf_पढ़ो_dev(ddev, DSAF_DSA_SRAM_1BIT_ECC_SEL_REG);
	p[8] = dsaf_पढ़ो_dev(ddev, DSAF_DSA_SRAM_1BIT_ECC_CNT_REG);

	p[9] = dsaf_पढ़ो_dev(ddev, DSAF_PFC_EN_0_REG + port * 4);
	p[10] = dsaf_पढ़ो_dev(ddev, DSAF_PFC_UNIT_CNT_0_REG + port * 4);
	p[11] = dsaf_पढ़ो_dev(ddev, DSAF_XGE_INT_MSK_0_REG + port * 4);
	p[12] = dsaf_पढ़ो_dev(ddev, DSAF_XGE_INT_SRC_0_REG + port * 4);
	p[13] = dsaf_पढ़ो_dev(ddev, DSAF_XGE_INT_STS_0_REG + port * 4);
	p[14] = dsaf_पढ़ो_dev(ddev, DSAF_XGE_INT_MSK_0_REG + port * 4);
	p[15] = dsaf_पढ़ो_dev(ddev, DSAF_PPE_INT_MSK_0_REG + port * 4);
	p[16] = dsaf_पढ़ो_dev(ddev, DSAF_ROCEE_INT_MSK_0_REG + port * 4);
	p[17] = dsaf_पढ़ो_dev(ddev, DSAF_XGE_INT_SRC_0_REG + port * 4);
	p[18] = dsaf_पढ़ो_dev(ddev, DSAF_PPE_INT_SRC_0_REG + port * 4);
	p[19] =  dsaf_पढ़ो_dev(ddev, DSAF_ROCEE_INT_SRC_0_REG + port * 4);
	p[20] = dsaf_पढ़ो_dev(ddev, DSAF_XGE_INT_STS_0_REG + port * 4);
	p[21] = dsaf_पढ़ो_dev(ddev, DSAF_PPE_INT_STS_0_REG + port * 4);
	p[22] = dsaf_पढ़ो_dev(ddev, DSAF_ROCEE_INT_STS_0_REG + port * 4);
	p[23] = dsaf_पढ़ो_dev(ddev, DSAF_PPE_QID_CFG_0_REG + port * 4);

	क्रम (i = 0; i < DSAF_SW_PORT_NUM; i++)
		p[24 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SW_PORT_TYPE_0_REG + i * 4);

	p[32] = dsaf_पढ़ो_dev(ddev, DSAF_MIX_DEF_QID_0_REG + port * 4);

	क्रम (i = 0; i < DSAF_SW_PORT_NUM; i++)
		p[33 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_PORT_DEF_VLAN_0_REG + i * 4);

	क्रम (i = 0; i < DSAF_TOTAL_QUEUE_NUM; i++)
		p[41 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_VM_DEF_VLAN_0_REG + i * 4);

	/* dsaf inode रेजिस्टरs */
	p[170] = dsaf_पढ़ो_dev(ddev, DSAF_INODE_CUT_THROUGH_CFG_0_REG);

	p[171] = dsaf_पढ़ो_dev(ddev,
			DSAF_INODE_ECC_ERR_ADDR_0_REG + port * 0x80);

	क्रम (i = 0; i < DSAF_INODE_NUM / DSAF_COMM_CHN; i++) अणु
		j = i * DSAF_COMM_CHN + port;
		p[172 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_IN_PORT_NUM_0_REG + j * 0x80);
		p[175 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_PRI_TC_CFG_0_REG + j * 0x80);
		p[178 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_BP_STATUS_0_REG + j * 0x80);
		p[181 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_PAD_DISCARD_NUM_0_REG + j * 0x80);
		p[184 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_FINAL_IN_MAN_NUM_0_REG + j * 0x80);
		p[187 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_FINAL_IN_PKT_NUM_0_REG + j * 0x80);
		p[190 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_SBM_PID_NUM_0_REG + j * 0x80);
		reg_पंचांगp = is_ver1 ? DSAF_INODE_FINAL_IN_PAUSE_NUM_0_REG :
				    DSAFV2_INODE_FINAL_IN_PAUSE_NUM_0_REG;
		p[193 + i] = dsaf_पढ़ो_dev(ddev, reg_पंचांगp + j * 0x80);
		p[196 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_SBM_RELS_NUM_0_REG + j * 0x80);
		p[199 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_SBM_DROP_NUM_0_REG + j * 0x80);
		p[202 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_CRC_FALSE_NUM_0_REG + j * 0x80);
		p[205 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_BP_DISCARD_NUM_0_REG + j * 0x80);
		p[208 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_RSLT_DISCARD_NUM_0_REG + j * 0x80);
		p[211 + i] = dsaf_पढ़ो_dev(ddev,
			DSAF_INODE_LOCAL_ADDR_FALSE_NUM_0_REG + j * 0x80);
		p[214 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_VOQ_OVER_NUM_0_REG + j * 0x80);
		p[217 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_BD_SAVE_STATUS_0_REG + j * 4);
		p[220 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_BD_ORDER_STATUS_0_REG + j * 4);
		p[223 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_SW_VLAN_TAG_DISC_0_REG + j * 4);
		p[226 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_IN_DATA_STP_DISC_0_REG + j * 4);
	पूर्ण

	p[229] = dsaf_पढ़ो_dev(ddev, DSAF_INODE_GE_FC_EN_0_REG + port * 4);

	क्रम (i = 0; i < DSAF_INODE_NUM / DSAF_COMM_CHN; i++) अणु
		j = i * DSAF_COMM_CHN + port;
		p[230 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_INODE_VC0_IN_PKT_NUM_0_REG + j * 4);
	पूर्ण

	p[233] = dsaf_पढ़ो_dev(ddev,
		DSAF_INODE_VC1_IN_PKT_NUM_0_REG + port * 0x80);

	/* dsaf inode रेजिस्टरs */
	क्रम (i = 0; i < HNS_DSAF_SBM_NUM(ddev) / DSAF_COMM_CHN; i++) अणु
		j = i * DSAF_COMM_CHN + port;
		p[234 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_CFG_REG_0_REG + j * 0x80);
		p[237 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_BP_CFG_0_XGE_REG_0_REG + j * 0x80);
		p[240 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_BP_CFG_1_REG_0_REG + j * 0x80);
		p[243 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_BP_CFG_2_XGE_REG_0_REG + j * 0x80);
		p[246 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_FREE_CNT_0_0_REG + j * 0x80);
		p[249 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_FREE_CNT_1_0_REG + j * 0x80);
		p[252 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_BP_CNT_0_0_REG + j * 0x80);
		p[255 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_BP_CNT_1_0_REG + j * 0x80);
		p[258 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_BP_CNT_2_0_REG + j * 0x80);
		p[261 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_BP_CNT_3_0_REG + j * 0x80);
		p[264 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_INER_ST_0_REG + j * 0x80);
		p[267 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_MIB_REQ_FAILED_TC_0_REG + j * 0x80);
		p[270 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_INPORT_CNT_0_REG + j * 0x80);
		p[273 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_DROP_CNT_0_REG + j * 0x80);
		p[276 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_INF_OUTPORT_CNT_0_REG + j * 0x80);
		p[279 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC0_CNT_0_REG + j * 0x80);
		p[282 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC1_CNT_0_REG + j * 0x80);
		p[285 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC2_CNT_0_REG + j * 0x80);
		p[288 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC3_CNT_0_REG + j * 0x80);
		p[291 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC4_CNT_0_REG + j * 0x80);
		p[294 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC5_CNT_0_REG + j * 0x80);
		p[297 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC6_CNT_0_REG + j * 0x80);
		p[300 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_INPORT_TC7_CNT_0_REG + j * 0x80);
		p[303 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_REQ_CNT_0_REG + j * 0x80);
		p[306 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_LNK_RELS_CNT_0_REG + j * 0x80);
		p[309 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_BP_CFG_3_REG_0_REG + j * 0x80);
		p[312 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_SBM_BP_CFG_4_REG_0_REG + j * 0x80);
	पूर्ण

	/* dsaf onode रेजिस्टरs */
	क्रम (i = 0; i < DSAF_XOD_NUM; i++) अणु
		p[315 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_ETS_TSA_TC0_TC3_CFG_0_REG + i * 0x90);
		p[323 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_ETS_TSA_TC4_TC7_CFG_0_REG + i * 0x90);
		p[331 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_ETS_BW_TC0_TC3_CFG_0_REG + i * 0x90);
		p[339 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_ETS_BW_TC4_TC7_CFG_0_REG + i * 0x90);
		p[347 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_ETS_BW_OFFSET_CFG_0_REG + i * 0x90);
		p[355 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_ETS_TOKEN_CFG_0_REG + i * 0x90);
	पूर्ण

	p[363] = dsaf_पढ़ो_dev(ddev, DSAF_XOD_PFS_CFG_0_0_REG + port * 0x90);
	p[364] = dsaf_पढ़ो_dev(ddev, DSAF_XOD_PFS_CFG_1_0_REG + port * 0x90);
	p[365] = dsaf_पढ़ो_dev(ddev, DSAF_XOD_PFS_CFG_2_0_REG + port * 0x90);

	क्रम (i = 0; i < DSAF_XOD_BIG_NUM / DSAF_COMM_CHN; i++) अणु
		j = i * DSAF_COMM_CHN + port;
		p[366 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_GNT_L_0_REG + j * 0x90);
		p[369 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_GNT_H_0_REG + j * 0x90);
		p[372 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_CONNECT_STATE_0_REG + j * 0x90);
		p[375 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_RCVPKT_CNT_0_REG + j * 0x90);
		p[378 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_RCVTC0_CNT_0_REG + j * 0x90);
		p[381 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_RCVTC1_CNT_0_REG + j * 0x90);
		p[384 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_RCVTC2_CNT_0_REG + j * 0x90);
		p[387 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_RCVTC3_CNT_0_REG + j * 0x90);
		p[390 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_RCVVC0_CNT_0_REG + j * 0x90);
		p[393 + i] = dsaf_पढ़ो_dev(ddev,
				DSAF_XOD_RCVVC1_CNT_0_REG + j * 0x90);
	पूर्ण

	p[396] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_XGE_RCVIN0_CNT_0_REG + port * 0x90);
	p[397] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_XGE_RCVIN1_CNT_0_REG + port * 0x90);
	p[398] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_XGE_RCVIN2_CNT_0_REG + port * 0x90);
	p[399] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_XGE_RCVIN3_CNT_0_REG + port * 0x90);
	p[400] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_XGE_RCVIN4_CNT_0_REG + port * 0x90);
	p[401] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_XGE_RCVIN5_CNT_0_REG + port * 0x90);
	p[402] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_XGE_RCVIN6_CNT_0_REG + port * 0x90);
	p[403] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_XGE_RCVIN7_CNT_0_REG + port * 0x90);
	p[404] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_PPE_RCVIN0_CNT_0_REG + port * 0x90);
	p[405] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_PPE_RCVIN1_CNT_0_REG + port * 0x90);
	p[406] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_ROCEE_RCVIN0_CNT_0_REG + port * 0x90);
	p[407] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_ROCEE_RCVIN1_CNT_0_REG + port * 0x90);
	p[408] = dsaf_पढ़ो_dev(ddev,
		DSAF_XOD_FIFO_STATUS_0_REG + port * 0x90);

	/* dsaf voq रेजिस्टरs */
	क्रम (i = 0; i < DSAF_VOQ_NUM / DSAF_COMM_CHN; i++) अणु
		j = (i * DSAF_COMM_CHN + port) * 0x90;
		p[409 + i] = dsaf_पढ़ो_dev(ddev,
			DSAF_VOQ_ECC_INVERT_EN_0_REG + j);
		p[412 + i] = dsaf_पढ़ो_dev(ddev,
			DSAF_VOQ_SRAM_PKT_NUM_0_REG + j);
		p[415 + i] = dsaf_पढ़ो_dev(ddev, DSAF_VOQ_IN_PKT_NUM_0_REG + j);
		p[418 + i] = dsaf_पढ़ो_dev(ddev,
			DSAF_VOQ_OUT_PKT_NUM_0_REG + j);
		p[421 + i] = dsaf_पढ़ो_dev(ddev,
			DSAF_VOQ_ECC_ERR_ADDR_0_REG + j);
		p[424 + i] = dsaf_पढ़ो_dev(ddev, DSAF_VOQ_BP_STATUS_0_REG + j);
		p[427 + i] = dsaf_पढ़ो_dev(ddev, DSAF_VOQ_SPUP_IDLE_0_REG + j);
		p[430 + i] = dsaf_पढ़ो_dev(ddev,
			DSAF_VOQ_XGE_XOD_REQ_0_0_REG + j);
		p[433 + i] = dsaf_पढ़ो_dev(ddev,
			DSAF_VOQ_XGE_XOD_REQ_1_0_REG + j);
		p[436 + i] = dsaf_पढ़ो_dev(ddev,
			DSAF_VOQ_PPE_XOD_REQ_0_REG + j);
		p[439 + i] = dsaf_पढ़ो_dev(ddev,
			DSAF_VOQ_ROCEE_XOD_REQ_0_REG + j);
		p[442 + i] = dsaf_पढ़ो_dev(ddev,
			DSAF_VOQ_BP_ALL_THRD_0_REG + j);
	पूर्ण

	/* dsaf tbl रेजिस्टरs */
	p[445] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_CTRL_0_REG);
	p[446] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_INT_MSK_0_REG);
	p[447] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_INT_SRC_0_REG);
	p[448] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_INT_STS_0_REG);
	p[449] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_ADDR_0_REG);
	p[450] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_LINE_ADDR_0_REG);
	p[451] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_HIGH_0_REG);
	p[452] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_LOW_0_REG);
	p[453] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_MCAST_CFG_4_0_REG);
	p[454] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_MCAST_CFG_3_0_REG);
	p[455] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_MCAST_CFG_2_0_REG);
	p[456] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_MCAST_CFG_1_0_REG);
	p[457] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_MCAST_CFG_0_0_REG);
	p[458] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_UCAST_CFG_0_REG);
	p[459] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_LIN_CFG_0_REG);
	p[460] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_RDATA_HIGH_0_REG);
	p[461] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_RDATA_LOW_0_REG);
	p[462] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_RAM_RDATA4_0_REG);
	p[463] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_RAM_RDATA3_0_REG);
	p[464] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_RAM_RDATA2_0_REG);
	p[465] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_RAM_RDATA1_0_REG);
	p[466] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_TCAM_RAM_RDATA0_0_REG);
	p[467] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_LIN_RDATA_0_REG);

	क्रम (i = 0; i < DSAF_SW_PORT_NUM; i++) अणु
		j = i * 0x8;
		p[468 + 2 * i] = dsaf_पढ़ो_dev(ddev,
			DSAF_TBL_DA0_MIS_INFO1_0_REG + j);
		p[469 + 2 * i] = dsaf_पढ़ो_dev(ddev,
			DSAF_TBL_DA0_MIS_INFO0_0_REG + j);
	पूर्ण

	p[484] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_SA_MIS_INFO2_0_REG);
	p[485] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_SA_MIS_INFO1_0_REG);
	p[486] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_SA_MIS_INFO0_0_REG);
	p[487] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_PUL_0_REG);
	p[488] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_OLD_RSLT_0_REG);
	p[489] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_OLD_SCAN_VAL_0_REG);
	p[490] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_DFX_CTRL_0_REG);
	p[491] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_DFX_STAT_0_REG);
	p[492] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_DFX_STAT_2_0_REG);
	p[493] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_LKUP_NUM_I_0_REG);
	p[494] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_LKUP_NUM_O_0_REG);
	p[495] = dsaf_पढ़ो_dev(ddev, DSAF_TBL_UCAST_BCAST_MIS_INFO_0_0_REG);

	/* dsaf other रेजिस्टरs */
	p[496] = dsaf_पढ़ो_dev(ddev, DSAF_INODE_FIFO_WL_0_REG + port * 0x4);
	p[497] = dsaf_पढ़ो_dev(ddev, DSAF_ONODE_FIFO_WL_0_REG + port * 0x4);
	p[498] = dsaf_पढ़ो_dev(ddev, DSAF_XGE_GE_WORK_MODE_0_REG + port * 0x4);
	p[499] = dsaf_पढ़ो_dev(ddev,
		DSAF_XGE_APP_RX_LINK_UP_0_REG + port * 0x4);
	p[500] = dsaf_पढ़ो_dev(ddev, DSAF_NETPORT_CTRL_SIG_0_REG + port * 0x4);
	p[501] = dsaf_पढ़ो_dev(ddev, DSAF_XGE_CTRL_SIG_CFG_0_REG + port * 0x4);

	अगर (!is_ver1)
		p[502] = dsaf_पढ़ो_dev(ddev, DSAF_PAUSE_CFG_REG + port * 0x4);

	/* mark end of dsaf regs */
	क्रम (i = 503; i < 504; i++)
		p[i] = 0xdddddddd;
पूर्ण

अटल अक्षर *hns_dsaf_get_node_stats_strings(अक्षर *data, पूर्णांक node,
					     काष्ठा dsaf_device *dsaf_dev)
अणु
	अक्षर *buff = data;
	पूर्णांक i;
	bool is_ver1 = AE_IS_VER1(dsaf_dev->dsaf_ver);

	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_pad_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_manage_pkts", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_rx_pkts", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_rx_pkt_id", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_rx_pause_frame", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_release_buf_num", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_sbm_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_crc_false_pkts", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_bp_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_lookup_rslt_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_local_rslt_fail_pkts", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_vlan_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	snम_लिखो(buff, ETH_GSTRING_LEN, "innod%d_stp_drop_pkts", node);
	buff += ETH_GSTRING_LEN;
	अगर (node < DSAF_SERVICE_NW_NUM && !is_ver1) अणु
		क्रम (i = 0; i < DSAF_PRIO_NR; i++) अणु
			snम_लिखो(buff + 0 * ETH_GSTRING_LEN * DSAF_PRIO_NR,
				 ETH_GSTRING_LEN, "inod%d_pfc_prio%d_pkts",
				 node, i);
			snम_लिखो(buff + 1 * ETH_GSTRING_LEN * DSAF_PRIO_NR,
				 ETH_GSTRING_LEN, "onod%d_pfc_prio%d_pkts",
				 node, i);
			buff += ETH_GSTRING_LEN;
		पूर्ण
		buff += 1 * DSAF_PRIO_NR * ETH_GSTRING_LEN;
	पूर्ण
	snम_लिखो(buff, ETH_GSTRING_LEN, "onnod%d_tx_pkts", node);
	buff += ETH_GSTRING_LEN;

	वापस buff;
पूर्ण

अटल u64 *hns_dsaf_get_node_stats(काष्ठा dsaf_device *ddev, u64 *data,
				    पूर्णांक node_num)
अणु
	u64 *p = data;
	पूर्णांक i;
	काष्ठा dsaf_hw_stats *hw_stats = &ddev->hw_stats[node_num];
	bool is_ver1 = AE_IS_VER1(ddev->dsaf_ver);

	p[0] = hw_stats->pad_drop;
	p[1] = hw_stats->man_pkts;
	p[2] = hw_stats->rx_pkts;
	p[3] = hw_stats->rx_pkt_id;
	p[4] = hw_stats->rx_छोड़ो_frame;
	p[5] = hw_stats->release_buf_num;
	p[6] = hw_stats->sbm_drop;
	p[7] = hw_stats->crc_false;
	p[8] = hw_stats->bp_drop;
	p[9] = hw_stats->rslt_drop;
	p[10] = hw_stats->local_addr_false;
	p[11] = hw_stats->vlan_drop;
	p[12] = hw_stats->stp_drop;
	अगर (node_num < DSAF_SERVICE_NW_NUM && !is_ver1) अणु
		क्रम (i = 0; i < DSAF_PRIO_NR; i++) अणु
			p[13 + i + 0 * DSAF_PRIO_NR] = hw_stats->rx_pfc[i];
			p[13 + i + 1 * DSAF_PRIO_NR] = hw_stats->tx_pfc[i];
		पूर्ण
		p[29] = hw_stats->tx_pkts;
		वापस &p[30];
	पूर्ण

	p[13] = hw_stats->tx_pkts;
	वापस &p[14];
पूर्ण

/**
 *hns_dsaf_get_stats - get dsaf statistic
 *@ddev: dsaf device
 *@data:statistic value
 *@port: port num
 */
व्योम hns_dsaf_get_stats(काष्ठा dsaf_device *ddev, u64 *data, पूर्णांक port)
अणु
	u64 *p = data;
	पूर्णांक node_num = port;

	/* क्रम ge/xge node info */
	p = hns_dsaf_get_node_stats(ddev, p, node_num);

	/* क्रम ppe node info */
	node_num = port + DSAF_PPE_INODE_BASE;
	(व्योम)hns_dsaf_get_node_stats(ddev, p, node_num);
पूर्ण

/**
 *hns_dsaf_get_sset_count - get dsaf string set count
 *@dsaf_dev: dsaf device
 *@stringset: type of values in data
 *वापस dsaf string name count
 */
पूर्णांक hns_dsaf_get_sset_count(काष्ठा dsaf_device *dsaf_dev, पूर्णांक stringset)
अणु
	bool is_ver1 = AE_IS_VER1(dsaf_dev->dsaf_ver);

	अगर (stringset == ETH_SS_STATS) अणु
		अगर (is_ver1)
			वापस DSAF_STATIC_NUM;
		अन्यथा
			वापस DSAF_V2_STATIC_NUM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *hns_dsaf_get_strings - get dsaf string set
 *@stringset:srting set index
 *@data:strings name value
 *@port:port index
 *@dsaf_dev: dsaf device
 */
व्योम hns_dsaf_get_strings(पूर्णांक stringset, u8 *data, पूर्णांक port,
			  काष्ठा dsaf_device *dsaf_dev)
अणु
	अक्षर *buff = (अक्षर *)data;
	पूर्णांक node = port;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	/* क्रम ge/xge node info */
	buff = hns_dsaf_get_node_stats_strings(buff, node, dsaf_dev);

	/* क्रम ppe node info */
	node = port + DSAF_PPE_INODE_BASE;
	(व्योम)hns_dsaf_get_node_stats_strings(buff, node, dsaf_dev);
पूर्ण

/**
 *hns_dsaf_get_sset_count - get dsaf regs count
 *वापस dsaf regs count
 */
पूर्णांक hns_dsaf_get_regs_count(व्योम)
अणु
	वापस DSAF_DUMP_REGS_NUM;
पूर्ण

अटल पूर्णांक hns_dsaf_get_port_id(u8 port)
अणु
	अगर (port < DSAF_SERVICE_NW_NUM)
		वापस port;

	अगर (port >= DSAF_BASE_INNER_PORT_NUM)
		वापस port - DSAF_BASE_INNER_PORT_NUM + DSAF_SERVICE_NW_NUM;

	वापस -EINVAL;
पूर्ण

अटल व्योम set_promisc_tcam_enable(काष्ठा dsaf_device *dsaf_dev, u32 port)
अणु
	काष्ठा dsaf_tbl_tcam_ucast_cfg tbl_tcam_ucast = अणु0, 1, 0, 0, 0x80पूर्ण;
	काष्ठा dsaf_tbl_tcam_data tbl_tcam_data_mc = अणु0x01000000, portपूर्ण;
	काष्ठा dsaf_tbl_tcam_data tbl_tcam_mask_uc = अणु0x01000000, 0xfपूर्ण;
	काष्ठा dsaf_tbl_tcam_mcast_cfg tbl_tcam_mcast = अणु0, 0, अणु0पूर्ण पूर्ण;
	काष्ठा dsaf_drv_priv *priv = hns_dsaf_dev_priv(dsaf_dev);
	काष्ठा dsaf_tbl_tcam_data tbl_tcam_data_uc = अणु0, portपूर्ण;
	काष्ठा dsaf_drv_mac_single_dest_entry mask_entry;
	काष्ठा dsaf_drv_tbl_tcam_key temp_key, mask_key;
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_entry;
	u16 entry_index;
	काष्ठा dsaf_drv_tbl_tcam_key mac_key;
	काष्ठा hns_mac_cb *mac_cb;
	u8 addr[ETH_ALEN] = अणु0पूर्ण;
	u8 port_num;
	पूर्णांक mskid;

	/* promisc use vague table match with vlanid = 0 & macaddr = 0 */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, 0x00, port, addr);
	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);
	अगर (entry_index != DSAF_INVALID_ENTRY_IDX)
		वापस;

	/* put promisc tcam entry in the end. */
	/* 1. set promisc unicast vague tcam entry. */
	entry_index = hns_dsaf_find_empty_mac_entry_reverse(dsaf_dev);
	अगर (entry_index == DSAF_INVALID_ENTRY_IDX) अणु
		dev_err(dsaf_dev->dev,
			"enable uc promisc failed (port:%#x)\n",
			port);
		वापस;
	पूर्ण

	mac_cb = dsaf_dev->mac_cb[port];
	(व्योम)hns_mac_get_inner_port_num(mac_cb, 0, &port_num);
	tbl_tcam_ucast.tbl_ucast_out_port = port_num;

	/* config uc vague table */
	hns_dsaf_tcam_uc_cfg_vague(dsaf_dev, entry_index, &tbl_tcam_data_uc,
				   &tbl_tcam_mask_uc, &tbl_tcam_ucast);

	/* update software entry */
	soft_mac_entry = priv->soft_mac_tbl;
	soft_mac_entry += entry_index;
	soft_mac_entry->index = entry_index;
	soft_mac_entry->tcam_key.high.val = mac_key.high.val;
	soft_mac_entry->tcam_key.low.val = mac_key.low.val;
	/* step back to the START क्रम mc. */
	soft_mac_entry = priv->soft_mac_tbl;

	/* 2. set promisc multicast vague tcam entry. */
	entry_index = hns_dsaf_find_empty_mac_entry_reverse(dsaf_dev);
	अगर (entry_index == DSAF_INVALID_ENTRY_IDX) अणु
		dev_err(dsaf_dev->dev,
			"enable mc promisc failed (port:%#x)\n",
			port);
		वापस;
	पूर्ण

	स_रखो(&mask_entry, 0x0, माप(mask_entry));
	स_रखो(&mask_key, 0x0, माप(mask_key));
	स_रखो(&temp_key, 0x0, माप(temp_key));
	mask_entry.addr[0] = 0x01;
	hns_dsaf_set_mac_key(dsaf_dev, &mask_key, mask_entry.in_vlan_id,
			     0xf, mask_entry.addr);
	tbl_tcam_mcast.tbl_mcast_item_vld = 1;
	tbl_tcam_mcast.tbl_mcast_old_en = 0;

	/* set MAC port to handle multicast */
	mskid = hns_dsaf_get_port_id(port);
	अगर (mskid == -EINVAL) अणु
		dev_err(dsaf_dev->dev, "%s,pnum(%d)error,key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name, port,
			mask_key.high.val, mask_key.low.val);
		वापस;
	पूर्ण
	dsaf_set_bit(tbl_tcam_mcast.tbl_mcast_port_msk[mskid / 32],
		     mskid % 32, 1);

	/* set pool bit map to handle multicast */
	mskid = hns_dsaf_get_port_id(port_num);
	अगर (mskid == -EINVAL) अणु
		dev_err(dsaf_dev->dev,
			"%s, pool bit map pnum(%d)error,key(%#x:%#x)\n",
			dsaf_dev->ae_dev.name, port_num,
			mask_key.high.val, mask_key.low.val);
		वापस;
	पूर्ण
	dsaf_set_bit(tbl_tcam_mcast.tbl_mcast_port_msk[mskid / 32],
		     mskid % 32, 1);

	स_नकल(&temp_key, &mask_key, माप(mask_key));
	hns_dsaf_tcam_mc_cfg_vague(dsaf_dev, entry_index, &tbl_tcam_data_mc,
				   (काष्ठा dsaf_tbl_tcam_data *)(&mask_key),
				   &tbl_tcam_mcast);

	/* update software entry */
	soft_mac_entry += entry_index;
	soft_mac_entry->index = entry_index;
	soft_mac_entry->tcam_key.high.val = temp_key.high.val;
	soft_mac_entry->tcam_key.low.val = temp_key.low.val;
पूर्ण

अटल व्योम set_promisc_tcam_disable(काष्ठा dsaf_device *dsaf_dev, u32 port)
अणु
	काष्ठा dsaf_tbl_tcam_data tbl_tcam_data_mc = अणु0x01000000, portपूर्ण;
	काष्ठा dsaf_tbl_tcam_ucast_cfg tbl_tcam_ucast = अणु0, 0, 0, 0, 0पूर्ण;
	काष्ठा dsaf_tbl_tcam_mcast_cfg tbl_tcam_mcast = अणु0, 0, अणु0पूर्ण पूर्ण;
	काष्ठा dsaf_drv_priv *priv = hns_dsaf_dev_priv(dsaf_dev);
	काष्ठा dsaf_tbl_tcam_data tbl_tcam_data_uc = अणु0, 0पूर्ण;
	काष्ठा dsaf_tbl_tcam_data tbl_tcam_mask = अणु0, 0पूर्ण;
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_entry;
	u16 entry_index;
	काष्ठा dsaf_drv_tbl_tcam_key mac_key;
	u8 addr[ETH_ALEN] = अणु0पूर्ण;

	/* 1. delete uc vague tcam entry. */
	/* promisc use vague table match with vlanid = 0 & macaddr = 0 */
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, 0x00, port, addr);
	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);

	अगर (entry_index == DSAF_INVALID_ENTRY_IDX)
		वापस;

	/* config uc vague table */
	hns_dsaf_tcam_uc_cfg_vague(dsaf_dev, entry_index, &tbl_tcam_data_uc,
				   &tbl_tcam_mask, &tbl_tcam_ucast);
	/* update soft management table. */
	soft_mac_entry = priv->soft_mac_tbl;
	soft_mac_entry += entry_index;
	soft_mac_entry->index = DSAF_INVALID_ENTRY_IDX;
	/* step back to the START क्रम mc. */
	soft_mac_entry = priv->soft_mac_tbl;

	/* 2. delete mc vague tcam entry. */
	addr[0] = 0x01;
	स_रखो(&mac_key, 0x0, माप(mac_key));
	hns_dsaf_set_mac_key(dsaf_dev, &mac_key, 0x00, port, addr);
	entry_index = hns_dsaf_find_soft_mac_entry(dsaf_dev, &mac_key);

	अगर (entry_index == DSAF_INVALID_ENTRY_IDX)
		वापस;

	/* config mc vague table */
	hns_dsaf_tcam_mc_cfg_vague(dsaf_dev, entry_index, &tbl_tcam_data_mc,
				   &tbl_tcam_mask, &tbl_tcam_mcast);
	/* update soft management table. */
	soft_mac_entry += entry_index;
	soft_mac_entry->index = DSAF_INVALID_ENTRY_IDX;
पूर्ण

/* Reserve the last TCAM entry क्रम promisc support */
व्योम hns_dsaf_set_promisc_tcam(काष्ठा dsaf_device *dsaf_dev,
			       u32 port, bool enable)
अणु
	अगर (enable)
		set_promisc_tcam_enable(dsaf_dev, port);
	अन्यथा
		set_promisc_tcam_disable(dsaf_dev, port);
पूर्ण

पूर्णांक hns_dsaf_रुको_pkt_clean(काष्ठा dsaf_device *dsaf_dev, पूर्णांक port)
अणु
	u32 val, val_पंचांगp;
	पूर्णांक रुको_cnt;

	अगर (port >= DSAF_SERVICE_NW_NUM)
		वापस 0;

	रुको_cnt = 0;
	जबतक (रुको_cnt++ < HNS_MAX_WAIT_CNT) अणु
		val = dsaf_पढ़ो_dev(dsaf_dev, DSAF_VOQ_IN_PKT_NUM_0_REG +
			(port + DSAF_XGE_NUM) * 0x40);
		val_पंचांगp = dsaf_पढ़ो_dev(dsaf_dev, DSAF_VOQ_OUT_PKT_NUM_0_REG +
			(port + DSAF_XGE_NUM) * 0x40);
		अगर (val == val_पंचांगp)
			अवरोध;

		usleep_range(100, 200);
	पूर्ण

	अगर (रुको_cnt >= HNS_MAX_WAIT_CNT) अणु
		dev_err(dsaf_dev->dev, "hns dsaf clean wait timeout(%u - %u).\n",
			val, val_पंचांगp);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dsaf_probe - probo dsaf dev
 * @pdev: dasf platक्रमm device
 * वापस 0 - success , negative --fail
 */
अटल पूर्णांक hns_dsaf_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dsaf_device *dsaf_dev;
	पूर्णांक ret;

	dsaf_dev = hns_dsaf_alloc_dev(&pdev->dev, माप(काष्ठा dsaf_drv_priv));
	अगर (IS_ERR(dsaf_dev)) अणु
		ret = PTR_ERR(dsaf_dev);
		dev_err(&pdev->dev,
			"dsaf_probe dsaf_alloc_dev failed, ret = %#x!\n", ret);
		वापस ret;
	पूर्ण

	ret = hns_dsaf_get_cfg(dsaf_dev);
	अगर (ret)
		जाओ मुक्त_dev;

	ret = hns_dsaf_init(dsaf_dev);
	अगर (ret)
		जाओ मुक्त_dev;

	ret = hns_mac_init(dsaf_dev);
	अगर (ret)
		जाओ uninit_dsaf;

	ret = hns_ppe_init(dsaf_dev);
	अगर (ret)
		जाओ uninit_mac;

	ret = hns_dsaf_ae_init(dsaf_dev);
	अगर (ret)
		जाओ uninit_ppe;

	वापस 0;

uninit_ppe:
	hns_ppe_uninit(dsaf_dev);

uninit_mac:
	hns_mac_uninit(dsaf_dev);

uninit_dsaf:
	hns_dsaf_मुक्त(dsaf_dev);

मुक्त_dev:
	hns_dsaf_मुक्त_dev(dsaf_dev);

	वापस ret;
पूर्ण

/**
 * dsaf_हटाओ - हटाओ dsaf dev
 * @pdev: dasf platक्रमm device
 */
अटल पूर्णांक hns_dsaf_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dsaf_device *dsaf_dev = dev_get_drvdata(&pdev->dev);

	hns_dsaf_ae_uninit(dsaf_dev);

	hns_ppe_uninit(dsaf_dev);

	hns_mac_uninit(dsaf_dev);

	hns_dsaf_मुक्त(dsaf_dev);

	hns_dsaf_मुक्त_dev(dsaf_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id g_dsaf_match[] = अणु
	अणु.compatible = "hisilicon,hns-dsaf-v1"पूर्ण,
	अणु.compatible = "hisilicon,hns-dsaf-v2"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, g_dsaf_match);

अटल काष्ठा platक्रमm_driver g_dsaf_driver = अणु
	.probe = hns_dsaf_probe,
	.हटाओ = hns_dsaf_हटाओ,
	.driver = अणु
		.name = DSAF_DRV_NAME,
		.of_match_table = g_dsaf_match,
		.acpi_match_table = hns_dsaf_acpi_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(g_dsaf_driver);

/**
 * hns_dsaf_roce_reset - reset dsaf and roce
 * @dsaf_fwnode: Poपूर्णांकer to framework node क्रम the dasf
 * @dereset: false - request reset , true - drop reset
 * वापस 0 - success , negative -fail
 */
पूर्णांक hns_dsaf_roce_reset(काष्ठा fwnode_handle *dsaf_fwnode, bool dereset)
अणु
	काष्ठा dsaf_device *dsaf_dev;
	काष्ठा platक्रमm_device *pdev;
	u32 mp;
	u32 sl;
	u32 credit;
	पूर्णांक i;
	अटल स्थिर u32 port_map[DSAF_ROCE_CREDIT_CHN][DSAF_ROCE_CHAN_MODE_NUM] = अणु
		अणुDSAF_ROCE_PORT_0, DSAF_ROCE_PORT_0, DSAF_ROCE_PORT_0पूर्ण,
		अणुDSAF_ROCE_PORT_1, DSAF_ROCE_PORT_0, DSAF_ROCE_PORT_0पूर्ण,
		अणुDSAF_ROCE_PORT_2, DSAF_ROCE_PORT_1, DSAF_ROCE_PORT_0पूर्ण,
		अणुDSAF_ROCE_PORT_3, DSAF_ROCE_PORT_1, DSAF_ROCE_PORT_0पूर्ण,
		अणुDSAF_ROCE_PORT_4, DSAF_ROCE_PORT_2, DSAF_ROCE_PORT_1पूर्ण,
		अणुDSAF_ROCE_PORT_4, DSAF_ROCE_PORT_2, DSAF_ROCE_PORT_1पूर्ण,
		अणुDSAF_ROCE_PORT_5, DSAF_ROCE_PORT_3, DSAF_ROCE_PORT_1पूर्ण,
		अणुDSAF_ROCE_PORT_5, DSAF_ROCE_PORT_3, DSAF_ROCE_PORT_1पूर्ण,
	पूर्ण;
	अटल स्थिर u32 sl_map[DSAF_ROCE_CREDIT_CHN][DSAF_ROCE_CHAN_MODE_NUM] = अणु
		अणुDSAF_ROCE_SL_0, DSAF_ROCE_SL_0, DSAF_ROCE_SL_0पूर्ण,
		अणुDSAF_ROCE_SL_0, DSAF_ROCE_SL_1, DSAF_ROCE_SL_1पूर्ण,
		अणुDSAF_ROCE_SL_0, DSAF_ROCE_SL_0, DSAF_ROCE_SL_2पूर्ण,
		अणुDSAF_ROCE_SL_0, DSAF_ROCE_SL_1, DSAF_ROCE_SL_3पूर्ण,
		अणुDSAF_ROCE_SL_0, DSAF_ROCE_SL_0, DSAF_ROCE_SL_0पूर्ण,
		अणुDSAF_ROCE_SL_1, DSAF_ROCE_SL_1, DSAF_ROCE_SL_1पूर्ण,
		अणुDSAF_ROCE_SL_0, DSAF_ROCE_SL_0, DSAF_ROCE_SL_2पूर्ण,
		अणुDSAF_ROCE_SL_1, DSAF_ROCE_SL_1, DSAF_ROCE_SL_3पूर्ण,
	पूर्ण;

	/* find the platक्रमm device corresponding to fwnode */
	अगर (is_of_node(dsaf_fwnode)) अणु
		pdev = of_find_device_by_node(to_of_node(dsaf_fwnode));
	पूर्ण अन्यथा अगर (is_acpi_device_node(dsaf_fwnode)) अणु
		pdev = hns_dsaf_find_platक्रमm_device(dsaf_fwnode);
	पूर्ण अन्यथा अणु
		pr_err("fwnode is neither OF or ACPI type\n");
		वापस -EINVAL;
	पूर्ण

	/* check अगर we were a success in fetching pdev */
	अगर (!pdev) अणु
		pr_err("couldn't find platform device for node\n");
		वापस -ENODEV;
	पूर्ण

	/* retrieve the dsaf_device from the driver data */
	dsaf_dev = dev_get_drvdata(&pdev->dev);
	अगर (!dsaf_dev) अणु
		dev_err(&pdev->dev, "dsaf_dev is NULL\n");
		put_device(&pdev->dev);
		वापस -ENODEV;
	पूर्ण

	/* now, make sure we are running on compatible SoC */
	अगर (AE_IS_VER1(dsaf_dev->dsaf_ver)) अणु
		dev_err(dsaf_dev->dev, "%s v1 chip doesn't support RoCE!\n",
			dsaf_dev->ae_dev.name);
		put_device(&pdev->dev);
		वापस -ENODEV;
	पूर्ण

	/* करो reset or de-reset according to the flag */
	अगर (!dereset) अणु
		/* reset rocee-channels in dsaf and rocee */
		dsaf_dev->misc_op->hns_dsaf_srst_chns(dsaf_dev, DSAF_CHNS_MASK,
						      false);
		dsaf_dev->misc_op->hns_dsaf_roce_srst(dsaf_dev, false);
	पूर्ण अन्यथा अणु
		/* configure dsaf tx roce correspond to port map and sl map */
		mp = dsaf_पढ़ो_dev(dsaf_dev, DSAF_ROCE_PORT_MAP_REG);
		क्रम (i = 0; i < DSAF_ROCE_CREDIT_CHN; i++)
			dsaf_set_field(mp, 7 << i * 3, i * 3,
				       port_map[i][DSAF_ROCE_6PORT_MODE]);
		dsaf_set_field(mp, 3 << i * 3, i * 3, 0);
		dsaf_ग_लिखो_dev(dsaf_dev, DSAF_ROCE_PORT_MAP_REG, mp);

		sl = dsaf_पढ़ो_dev(dsaf_dev, DSAF_ROCE_SL_MAP_REG);
		क्रम (i = 0; i < DSAF_ROCE_CREDIT_CHN; i++)
			dsaf_set_field(sl, 3 << i * 2, i * 2,
				       sl_map[i][DSAF_ROCE_6PORT_MODE]);
		dsaf_ग_लिखो_dev(dsaf_dev, DSAF_ROCE_SL_MAP_REG, sl);

		/* de-reset rocee-channels in dsaf and rocee */
		dsaf_dev->misc_op->hns_dsaf_srst_chns(dsaf_dev, DSAF_CHNS_MASK,
						      true);
		msleep(SRST_TIME_INTERVAL);
		dsaf_dev->misc_op->hns_dsaf_roce_srst(dsaf_dev, true);

		/* enable dsaf channel rocee credit */
		credit = dsaf_पढ़ो_dev(dsaf_dev, DSAF_SBM_ROCEE_CFG_REG_REG);
		dsaf_set_bit(credit, DSAF_SBM_ROCEE_CFG_CRD_EN_B, 0);
		dsaf_ग_लिखो_dev(dsaf_dev, DSAF_SBM_ROCEE_CFG_REG_REG, credit);

		dsaf_set_bit(credit, DSAF_SBM_ROCEE_CFG_CRD_EN_B, 1);
		dsaf_ग_लिखो_dev(dsaf_dev, DSAF_SBM_ROCEE_CFG_REG_REG, credit);
	पूर्ण

	put_device(&pdev->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hns_dsaf_roce_reset);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Huawei Tech. Co., Ltd.");
MODULE_DESCRIPTION("HNS DSAF driver");
MODULE_VERSION(DSAF_MOD_VERSION);
