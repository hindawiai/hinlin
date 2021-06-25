<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश "hns_dsaf_mac.h"
#समावेश "hns_dsaf_misc.h"
#समावेश "hns_dsaf_ppe.h"
#समावेश "hns_dsaf_reg.h"

क्रमागत _dsm_op_index अणु
	HNS_OP_RESET_FUNC               = 0x1,
	HNS_OP_SERDES_LP_FUNC           = 0x2,
	HNS_OP_LED_SET_FUNC             = 0x3,
	HNS_OP_GET_PORT_TYPE_FUNC       = 0x4,
	HNS_OP_GET_SFP_STAT_FUNC        = 0x5,
	HNS_OP_LOCATE_LED_SET_FUNC      = 0x6,
पूर्ण;

क्रमागत _dsm_rst_type अणु
	HNS_DSAF_RESET_FUNC     = 0x1,
	HNS_PPE_RESET_FUNC      = 0x2,
	HNS_XGE_RESET_FUNC      = 0x4,
	HNS_GE_RESET_FUNC       = 0x5,
	HNS_DSAF_CHN_RESET_FUNC = 0x6,
	HNS_ROCE_RESET_FUNC     = 0x7,
पूर्ण;

अटल स्थिर guid_t hns_dsaf_acpi_dsm_guid =
	GUID_INIT(0x1A85AA1A, 0xE293, 0x415E,
		  0x8E, 0x28, 0x8D, 0x69, 0x0A, 0x0F, 0x82, 0x0A);

अटल व्योम dsaf_ग_लिखो_sub(काष्ठा dsaf_device *dsaf_dev, u32 reg, u32 val)
अणु
	अगर (dsaf_dev->sub_ctrl)
		dsaf_ग_लिखो_syscon(dsaf_dev->sub_ctrl, reg, val);
	अन्यथा
		dsaf_ग_लिखो_reg(dsaf_dev->sc_base, reg, val);
पूर्ण

अटल u32 dsaf_पढ़ो_sub(काष्ठा dsaf_device *dsaf_dev, u32 reg)
अणु
	u32 ret = 0;
	पूर्णांक err;

	अगर (dsaf_dev->sub_ctrl) अणु
		err = dsaf_पढ़ो_syscon(dsaf_dev->sub_ctrl, reg, &ret);
		अगर (err)
			dev_err(dsaf_dev->dev, "dsaf_read_syscon error %d!\n",
				err);
	पूर्ण अन्यथा अणु
		ret = dsaf_पढ़ो_reg(dsaf_dev->sc_base, reg);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम hns_dsaf_acpi_ledctrl_by_port(काष्ठा hns_mac_cb *mac_cb, u8 op_type,
                                      u32 link, u32 port, u32 act)
अणु
       जोड़ acpi_object *obj;
       जोड़ acpi_object obj_args[3], argv4;

       obj_args[0].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
       obj_args[0].पूर्णांकeger.value = link;
       obj_args[1].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
       obj_args[1].पूर्णांकeger.value = port;
       obj_args[2].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
       obj_args[2].पूर्णांकeger.value = act;

       argv4.type = ACPI_TYPE_PACKAGE;
       argv4.package.count = 3;
       argv4.package.elements = obj_args;

       obj = acpi_evaluate_dsm(ACPI_HANDLE(mac_cb->dev),
                               &hns_dsaf_acpi_dsm_guid, 0, op_type, &argv4);
       अगर (!obj) अणु
               dev_warn(mac_cb->dev, "ledctrl fail, link:%d port:%d act:%d!\n",
                        link, port, act);
               वापस;
       पूर्ण

       ACPI_FREE(obj);
पूर्ण

अटल व्योम hns_dsaf_acpi_locate_ledctrl_by_port(काष्ठा hns_mac_cb *mac_cb,
						 u8 op_type, u32 locate,
						 u32 port)
अणु
	जोड़ acpi_object obj_args[2], argv4;
	जोड़ acpi_object *obj;

	obj_args[0].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	obj_args[0].पूर्णांकeger.value = locate;
	obj_args[1].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	obj_args[1].पूर्णांकeger.value = port;

	argv4.type = ACPI_TYPE_PACKAGE;
	argv4.package.count = 2;
	argv4.package.elements = obj_args;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(mac_cb->dev),
				&hns_dsaf_acpi_dsm_guid, 0, op_type, &argv4);
	अगर (!obj) अणु
		dev_err(mac_cb->dev, "ledctrl fail, locate:%d port:%d!\n",
			locate, port);
		वापस;
	पूर्ण

	ACPI_FREE(obj);
पूर्ण

अटल व्योम hns_cpld_set_led(काष्ठा hns_mac_cb *mac_cb, पूर्णांक link_status,
			     u16 speed, पूर्णांक data)
अणु
	पूर्णांक speed_reg = 0;
	u8 value;

	अगर (!mac_cb) अणु
		pr_err("sfp_led_opt mac_dev is null!\n");
		वापस;
	पूर्ण
	अगर (!mac_cb->cpld_ctrl) अणु
		dev_err(mac_cb->dev, "mac_id=%d, cpld syscon is null !\n",
			mac_cb->mac_id);
		वापस;
	पूर्ण

	अगर (speed == MAC_SPEED_10000)
		speed_reg = 1;

	value = mac_cb->cpld_led_value;

	अगर (link_status) अणु
		dsaf_set_bit(value, DSAF_LED_LINK_B, link_status);
		dsaf_set_field(value, DSAF_LED_SPEED_M,
			       DSAF_LED_SPEED_S, speed_reg);
		dsaf_set_bit(value, DSAF_LED_DATA_B, data);

		अगर (value != mac_cb->cpld_led_value) अणु
			dsaf_ग_लिखो_syscon(mac_cb->cpld_ctrl,
					  mac_cb->cpld_ctrl_reg, value);
			mac_cb->cpld_led_value = value;
		पूर्ण
	पूर्ण अन्यथा अणु
		value = (mac_cb->cpld_led_value) & (0x1 << DSAF_LED_ANCHOR_B);
		dsaf_ग_लिखो_syscon(mac_cb->cpld_ctrl,
				  mac_cb->cpld_ctrl_reg, value);
		mac_cb->cpld_led_value = value;
	पूर्ण
पूर्ण

अटल व्योम hns_cpld_set_led_acpi(काष्ठा hns_mac_cb *mac_cb, पूर्णांक link_status,
                            u16 speed, पूर्णांक data)
अणु
       अगर (!mac_cb) अणु
               pr_err("cpld_led_set mac_cb is null!\n");
               वापस;
       पूर्ण

       hns_dsaf_acpi_ledctrl_by_port(mac_cb, HNS_OP_LED_SET_FUNC,
               link_status, mac_cb->mac_id, data);
पूर्ण

अटल व्योम cpld_led_reset(काष्ठा hns_mac_cb *mac_cb)
अणु
	अगर (!mac_cb || !mac_cb->cpld_ctrl)
		वापस;

	dsaf_ग_लिखो_syscon(mac_cb->cpld_ctrl, mac_cb->cpld_ctrl_reg,
			  CPLD_LED_DEFAULT_VALUE);
	mac_cb->cpld_led_value = CPLD_LED_DEFAULT_VALUE;
पूर्ण

अटल व्योम cpld_led_reset_acpi(काष्ठा hns_mac_cb *mac_cb)
अणु
       अगर (!mac_cb) अणु
               pr_err("cpld_led_reset mac_cb is null!\n");
               वापस;
       पूर्ण

       अगर (mac_cb->media_type != HNAE_MEDIA_TYPE_FIBER)
                वापस;

       hns_dsaf_acpi_ledctrl_by_port(mac_cb, HNS_OP_LED_SET_FUNC,
               0, mac_cb->mac_id, 0);
पूर्ण

अटल पूर्णांक cpld_set_led_id(काष्ठा hns_mac_cb *mac_cb,
			   क्रमागत hnae_led_state status)
अणु
	u32 val = 0;
	पूर्णांक ret;

	अगर (!mac_cb->cpld_ctrl)
		वापस 0;

	चयन (status) अणु
	हाल HNAE_LED_ACTIVE:
		ret = dsaf_पढ़ो_syscon(mac_cb->cpld_ctrl, mac_cb->cpld_ctrl_reg,
				       &val);
		अगर (ret)
			वापस ret;

		dsaf_set_bit(val, DSAF_LED_ANCHOR_B, CPLD_LED_ON_VALUE);
		dsaf_ग_लिखो_syscon(mac_cb->cpld_ctrl, mac_cb->cpld_ctrl_reg,
				  val);
		mac_cb->cpld_led_value = val;
		अवरोध;
	हाल HNAE_LED_INACTIVE:
		dsaf_set_bit(mac_cb->cpld_led_value, DSAF_LED_ANCHOR_B,
			     CPLD_LED_DEFAULT_VALUE);
		dsaf_ग_लिखो_syscon(mac_cb->cpld_ctrl, mac_cb->cpld_ctrl_reg,
				  mac_cb->cpld_led_value);
		अवरोध;
	शेष:
		dev_err(mac_cb->dev, "invalid led state: %d!", status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpld_set_led_id_acpi(काष्ठा hns_mac_cb *mac_cb,
				क्रमागत hnae_led_state status)
अणु
	चयन (status) अणु
	हाल HNAE_LED_ACTIVE:
		hns_dsaf_acpi_locate_ledctrl_by_port(mac_cb,
						     HNS_OP_LOCATE_LED_SET_FUNC,
						     CPLD_LED_ON_VALUE,
						     mac_cb->mac_id);
		अवरोध;
	हाल HNAE_LED_INACTIVE:
		hns_dsaf_acpi_locate_ledctrl_by_port(mac_cb,
						     HNS_OP_LOCATE_LED_SET_FUNC,
						     CPLD_LED_DEFAULT_VALUE,
						     mac_cb->mac_id);
		अवरोध;
	शेष:
		dev_err(mac_cb->dev, "invalid led state: %d!", status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा RESET_REQ_OR_DREQ 1

अटल व्योम hns_dsaf_acpi_srst_by_port(काष्ठा dsaf_device *dsaf_dev, u8 op_type,
				       u32 port_type, u32 port, u32 val)
अणु
	जोड़ acpi_object *obj;
	जोड़ acpi_object obj_args[3], argv4;

	obj_args[0].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	obj_args[0].पूर्णांकeger.value = port_type;
	obj_args[1].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	obj_args[1].पूर्णांकeger.value = port;
	obj_args[2].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	obj_args[2].पूर्णांकeger.value = val;

	argv4.type = ACPI_TYPE_PACKAGE;
	argv4.package.count = 3;
	argv4.package.elements = obj_args;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(dsaf_dev->dev),
				&hns_dsaf_acpi_dsm_guid, 0, op_type, &argv4);
	अगर (!obj) अणु
		dev_warn(dsaf_dev->dev, "reset port_type%d port%d fail!",
			 port_type, port);
		वापस;
	पूर्ण

	ACPI_FREE(obj);
पूर्ण

अटल व्योम hns_dsaf_rst(काष्ठा dsaf_device *dsaf_dev, bool dereset)
अणु
	u32 xbar_reg_addr;
	u32 nt_reg_addr;

	अगर (!dereset) अणु
		xbar_reg_addr = DSAF_SUB_SC_XBAR_RESET_REQ_REG;
		nt_reg_addr = DSAF_SUB_SC_NT_RESET_REQ_REG;
	पूर्ण अन्यथा अणु
		xbar_reg_addr = DSAF_SUB_SC_XBAR_RESET_DREQ_REG;
		nt_reg_addr = DSAF_SUB_SC_NT_RESET_DREQ_REG;
	पूर्ण

	dsaf_ग_लिखो_sub(dsaf_dev, xbar_reg_addr, RESET_REQ_OR_DREQ);
	dsaf_ग_लिखो_sub(dsaf_dev, nt_reg_addr, RESET_REQ_OR_DREQ);
पूर्ण

अटल व्योम hns_dsaf_rst_acpi(काष्ठा dsaf_device *dsaf_dev, bool dereset)
अणु
	hns_dsaf_acpi_srst_by_port(dsaf_dev, HNS_OP_RESET_FUNC,
				   HNS_DSAF_RESET_FUNC,
				   0, dereset);
पूर्ण

अटल व्योम hns_dsaf_xge_srst_by_port(काष्ठा dsaf_device *dsaf_dev, u32 port,
				      bool dereset)
अणु
	u32 reg_val = 0;
	u32 reg_addr;

	अगर (port >= DSAF_XGE_NUM)
		वापस;

	reg_val |= RESET_REQ_OR_DREQ;
	reg_val |= 0x2082082 << dsaf_dev->mac_cb[port]->port_rst_off;

	अगर (!dereset)
		reg_addr = DSAF_SUB_SC_XGE_RESET_REQ_REG;
	अन्यथा
		reg_addr = DSAF_SUB_SC_XGE_RESET_DREQ_REG;

	dsaf_ग_लिखो_sub(dsaf_dev, reg_addr, reg_val);
पूर्ण

अटल व्योम hns_dsaf_xge_srst_by_port_acpi(काष्ठा dsaf_device *dsaf_dev,
					   u32 port, bool dereset)
अणु
	hns_dsaf_acpi_srst_by_port(dsaf_dev, HNS_OP_RESET_FUNC,
				   HNS_XGE_RESET_FUNC, port, dereset);
पूर्ण

/**
 * hns_dsaf_srst_chns - reset dsaf channels
 * @dsaf_dev: dsaf device काष्ठा poपूर्णांकer
 * @msk: xbar channels mask value:
 * @dereset: false - request reset , true - drop reset
 *
 * bit0-5 क्रम xge0-5
 * bit6-11 क्रम ppe0-5
 * bit12-17 क्रम roce0-5
 * bit18-19 क्रम com/dfx
 */
अटल व्योम
hns_dsaf_srst_chns(काष्ठा dsaf_device *dsaf_dev, u32 msk, bool dereset)
अणु
	u32 reg_addr;

	अगर (!dereset)
		reg_addr = DSAF_SUB_SC_DSAF_RESET_REQ_REG;
	अन्यथा
		reg_addr = DSAF_SUB_SC_DSAF_RESET_DREQ_REG;

	dsaf_ग_लिखो_sub(dsaf_dev, reg_addr, msk);
पूर्ण

/**
 * hns_dsaf_srst_chns - reset dsaf channels
 * @dsaf_dev: dsaf device काष्ठा poपूर्णांकer
 * @msk: xbar channels mask value:
 * @dereset: false - request reset , true - drop reset
 *
 * bit0-5 क्रम xge0-5
 * bit6-11 क्रम ppe0-5
 * bit12-17 क्रम roce0-5
 * bit18-19 क्रम com/dfx
 */
अटल व्योम
hns_dsaf_srst_chns_acpi(काष्ठा dsaf_device *dsaf_dev, u32 msk, bool dereset)
अणु
	hns_dsaf_acpi_srst_by_port(dsaf_dev, HNS_OP_RESET_FUNC,
				   HNS_DSAF_CHN_RESET_FUNC,
				   msk, dereset);
पूर्ण

अटल व्योम hns_dsaf_roce_srst(काष्ठा dsaf_device *dsaf_dev, bool dereset)
अणु
	अगर (!dereset) अणु
		dsaf_ग_लिखो_sub(dsaf_dev, DSAF_SUB_SC_ROCEE_RESET_REQ_REG, 1);
	पूर्ण अन्यथा अणु
		dsaf_ग_लिखो_sub(dsaf_dev,
			       DSAF_SUB_SC_ROCEE_CLK_DIS_REG, 1);
		dsaf_ग_लिखो_sub(dsaf_dev,
			       DSAF_SUB_SC_ROCEE_RESET_DREQ_REG, 1);
		msleep(20);
		dsaf_ग_लिखो_sub(dsaf_dev, DSAF_SUB_SC_ROCEE_CLK_EN_REG, 1);
	पूर्ण
पूर्ण

अटल व्योम hns_dsaf_roce_srst_acpi(काष्ठा dsaf_device *dsaf_dev, bool dereset)
अणु
	hns_dsaf_acpi_srst_by_port(dsaf_dev, HNS_OP_RESET_FUNC,
				   HNS_ROCE_RESET_FUNC, 0, dereset);
पूर्ण

अटल व्योम hns_dsaf_ge_srst_by_port(काष्ठा dsaf_device *dsaf_dev, u32 port,
				     bool dereset)
अणु
	u32 reg_val_1;
	u32 reg_val_2;
	u32 port_rst_off;

	अगर (port >= DSAF_GE_NUM)
		वापस;

	अगर (!HNS_DSAF_IS_DEBUG(dsaf_dev)) अणु
		reg_val_1  = 0x1 << port;
		port_rst_off = dsaf_dev->mac_cb[port]->port_rst_off;
		/* there is dअगरference between V1 and V2 in रेजिस्टर.*/
		reg_val_2 = AE_IS_VER1(dsaf_dev->dsaf_ver) ?
				0x1041041 : 0x2082082;
		reg_val_2 <<= port_rst_off;

		अगर (!dereset) अणु
			dsaf_ग_लिखो_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_REQ1_REG,
				       reg_val_1);

			dsaf_ग_लिखो_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_REQ0_REG,
				       reg_val_2);
		पूर्ण अन्यथा अणु
			dsaf_ग_लिखो_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_DREQ0_REG,
				       reg_val_2);

			dsaf_ग_लिखो_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_DREQ1_REG,
				       reg_val_1);
		पूर्ण
	पूर्ण अन्यथा अणु
		reg_val_1 = 0x15540;
		reg_val_2 = AE_IS_VER1(dsaf_dev->dsaf_ver) ? 0x100 : 0x40;

		reg_val_1 <<= dsaf_dev->reset_offset;
		reg_val_2 <<= dsaf_dev->reset_offset;

		अगर (!dereset) अणु
			dsaf_ग_लिखो_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_REQ1_REG,
				       reg_val_1);

			dsaf_ग_लिखो_sub(dsaf_dev, DSAF_SUB_SC_PPE_RESET_REQ_REG,
				       reg_val_2);
		पूर्ण अन्यथा अणु
			dsaf_ग_लिखो_sub(dsaf_dev, DSAF_SUB_SC_GE_RESET_DREQ1_REG,
				       reg_val_1);

			dsaf_ग_लिखो_sub(dsaf_dev, DSAF_SUB_SC_PPE_RESET_DREQ_REG,
				       reg_val_2);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम hns_dsaf_ge_srst_by_port_acpi(काष्ठा dsaf_device *dsaf_dev,
					  u32 port, bool dereset)
अणु
	hns_dsaf_acpi_srst_by_port(dsaf_dev, HNS_OP_RESET_FUNC,
				   HNS_GE_RESET_FUNC, port, dereset);
पूर्ण

अटल व्योम hns_ppe_srst_by_port(काष्ठा dsaf_device *dsaf_dev, u32 port,
				 bool dereset)
अणु
	u32 reg_val = 0;
	u32 reg_addr;

	reg_val |= RESET_REQ_OR_DREQ <<	dsaf_dev->mac_cb[port]->port_rst_off;

	अगर (!dereset)
		reg_addr = DSAF_SUB_SC_PPE_RESET_REQ_REG;
	अन्यथा
		reg_addr = DSAF_SUB_SC_PPE_RESET_DREQ_REG;

	dsaf_ग_लिखो_sub(dsaf_dev, reg_addr, reg_val);
पूर्ण

अटल व्योम
hns_ppe_srst_by_port_acpi(काष्ठा dsaf_device *dsaf_dev, u32 port, bool dereset)
अणु
	hns_dsaf_acpi_srst_by_port(dsaf_dev, HNS_OP_RESET_FUNC,
				   HNS_PPE_RESET_FUNC, port, dereset);
पूर्ण

अटल व्योम hns_ppe_com_srst(काष्ठा dsaf_device *dsaf_dev, bool dereset)
अणु
	u32 reg_val;
	u32 reg_addr;

	अगर (!(dev_of_node(dsaf_dev->dev)))
		वापस;

	अगर (!HNS_DSAF_IS_DEBUG(dsaf_dev)) अणु
		reg_val = RESET_REQ_OR_DREQ;
		अगर (!dereset)
			reg_addr = DSAF_SUB_SC_RCB_PPE_COM_RESET_REQ_REG;
		अन्यथा
			reg_addr = DSAF_SUB_SC_RCB_PPE_COM_RESET_DREQ_REG;

	पूर्ण अन्यथा अणु
		reg_val = 0x100 << dsaf_dev->reset_offset;

		अगर (!dereset)
			reg_addr = DSAF_SUB_SC_PPE_RESET_REQ_REG;
		अन्यथा
			reg_addr = DSAF_SUB_SC_PPE_RESET_DREQ_REG;
	पूर्ण

	dsaf_ग_लिखो_sub(dsaf_dev, reg_addr, reg_val);
पूर्ण

/**
 * hns_mac_get_sds_mode - get phy अगरterface क्रमm serdes mode
 * @mac_cb: mac control block
 * retuen phy पूर्णांकerface
 */
अटल phy_पूर्णांकerface_t hns_mac_get_phy_अगर(काष्ठा hns_mac_cb *mac_cb)
अणु
	u32 mode;
	u32 reg;
	bool is_ver1 = AE_IS_VER1(mac_cb->dsaf_dev->dsaf_ver);
	पूर्णांक mac_id = mac_cb->mac_id;
	phy_पूर्णांकerface_t phy_अगर;

	अगर (is_ver1) अणु
		अगर (HNS_DSAF_IS_DEBUG(mac_cb->dsaf_dev))
			वापस PHY_INTERFACE_MODE_SGMII;

		अगर (mac_id >= 0 && mac_id <= 3)
			reg = HNS_MAC_HILINK4_REG;
		अन्यथा
			reg = HNS_MAC_HILINK3_REG;
	पूर्ण अन्यथाअणु
		अगर (!HNS_DSAF_IS_DEBUG(mac_cb->dsaf_dev) && mac_id <= 3)
			reg = HNS_MAC_HILINK4V2_REG;
		अन्यथा
			reg = HNS_MAC_HILINK3V2_REG;
	पूर्ण

	mode = dsaf_पढ़ो_sub(mac_cb->dsaf_dev, reg);
	अगर (dsaf_get_bit(mode, mac_cb->port_mode_off))
		phy_अगर = PHY_INTERFACE_MODE_XGMII;
	अन्यथा
		phy_अगर = PHY_INTERFACE_MODE_SGMII;

	वापस phy_अगर;
पूर्ण

अटल phy_पूर्णांकerface_t hns_mac_get_phy_अगर_acpi(काष्ठा hns_mac_cb *mac_cb)
अणु
	phy_पूर्णांकerface_t phy_अगर = PHY_INTERFACE_MODE_NA;
	जोड़ acpi_object *obj;
	जोड़ acpi_object obj_args, argv4;

	obj_args.पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	obj_args.पूर्णांकeger.value = mac_cb->mac_id;

	argv4.type = ACPI_TYPE_PACKAGE;
	argv4.package.count = 1;
	argv4.package.elements = &obj_args;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(mac_cb->dev),
				&hns_dsaf_acpi_dsm_guid, 0,
				HNS_OP_GET_PORT_TYPE_FUNC, &argv4);

	अगर (!obj || obj->type != ACPI_TYPE_INTEGER)
		वापस phy_अगर;

	phy_अगर = obj->पूर्णांकeger.value ?
		PHY_INTERFACE_MODE_XGMII : PHY_INTERFACE_MODE_SGMII;

	dev_dbg(mac_cb->dev, "mac_id=%d, phy_if=%d\n", mac_cb->mac_id, phy_अगर);

	ACPI_FREE(obj);

	वापस phy_अगर;
पूर्ण

अटल पूर्णांक hns_mac_get_sfp_prsnt(काष्ठा hns_mac_cb *mac_cb, पूर्णांक *sfp_prsnt)
अणु
	u32 val = 0;
	पूर्णांक ret;

	अगर (!mac_cb->cpld_ctrl)
		वापस -ENODEV;

	ret = dsaf_पढ़ो_syscon(mac_cb->cpld_ctrl,
			       mac_cb->cpld_ctrl_reg + MAC_SFP_PORT_OFFSET,
			       &val);
	अगर (ret)
		वापस ret;

	*sfp_prsnt = !val;
	वापस 0;
पूर्ण

अटल पूर्णांक hns_mac_get_sfp_prsnt_acpi(काष्ठा hns_mac_cb *mac_cb, पूर्णांक *sfp_prsnt)
अणु
	जोड़ acpi_object *obj;
	जोड़ acpi_object obj_args, argv4;

	obj_args.पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	obj_args.पूर्णांकeger.value = mac_cb->mac_id;

	argv4.type = ACPI_TYPE_PACKAGE;
	argv4.package.count = 1;
	argv4.package.elements = &obj_args;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(mac_cb->dev),
				&hns_dsaf_acpi_dsm_guid, 0,
				HNS_OP_GET_SFP_STAT_FUNC, &argv4);

	अगर (!obj || obj->type != ACPI_TYPE_INTEGER)
		वापस -ENODEV;

	*sfp_prsnt = obj->पूर्णांकeger.value;

	ACPI_FREE(obj);

	वापस 0;
पूर्ण

/**
 * hns_mac_config_sds_loopback - set loop back क्रम serdes
 * @mac_cb: mac control block
 * @en: enable or disable
 * वापस 0 == success
 */
अटल पूर्णांक hns_mac_config_sds_loopback(काष्ठा hns_mac_cb *mac_cb, bool en)
अणु
	स्थिर u8 lane_id[] = अणु
		0,	/* mac 0 -> lane 0 */
		1,	/* mac 1 -> lane 1 */
		2,	/* mac 2 -> lane 2 */
		3,	/* mac 3 -> lane 3 */
		2,	/* mac 4 -> lane 2 */
		3,	/* mac 5 -> lane 3 */
		0,	/* mac 6 -> lane 0 */
		1	/* mac 7 -> lane 1 */
	पूर्ण;
#घोषणा RX_CSR(lane, reg) ((0x4080 + (reg) * 0x0002 + (lane) * 0x0200) * 2)
	u64 reg_offset = RX_CSR(lane_id[mac_cb->mac_id], 0);

	पूर्णांक sfp_prsnt = 0;
	पूर्णांक ret = hns_mac_get_sfp_prsnt(mac_cb, &sfp_prsnt);

	अगर (!mac_cb->phy_dev) अणु
		अगर (ret)
			pr_info("please confirm sfp is present or not\n");
		अन्यथा
			अगर (!sfp_prsnt)
				pr_info("no sfp in this eth\n");
	पूर्ण

	अगर (mac_cb->serdes_ctrl) अणु
		u32 origin = 0;

		अगर (!AE_IS_VER1(mac_cb->dsaf_dev->dsaf_ver)) अणु
#घोषणा HILINK_ACCESS_SEL_CFG		0x40008
			/* hilink4 & hilink3 use the same xge training and
			 * xge u adaptor. There is a hilink access sel cfg
			 * रेजिस्टर to select which one to be configed
			 */
			अगर ((!HNS_DSAF_IS_DEBUG(mac_cb->dsaf_dev)) &&
			    (mac_cb->mac_id <= 3))
				dsaf_ग_लिखो_syscon(mac_cb->serdes_ctrl,
						  HILINK_ACCESS_SEL_CFG, 0);
			अन्यथा
				dsaf_ग_लिखो_syscon(mac_cb->serdes_ctrl,
						  HILINK_ACCESS_SEL_CFG, 3);
		पूर्ण

		ret = dsaf_पढ़ो_syscon(mac_cb->serdes_ctrl, reg_offset,
				       &origin);
		अगर (ret)
			वापस ret;

		dsaf_set_field(origin, 1ull << 10, 10, en);
		dsaf_ग_लिखो_syscon(mac_cb->serdes_ctrl, reg_offset, origin);
	पूर्ण अन्यथा अणु
		u8 __iomem *base_addr = mac_cb->serdes_vaddr +
				(mac_cb->mac_id <= 3 ? 0x00280000 : 0x00200000);
		dsaf_set_reg_field(base_addr, reg_offset, 1ull << 10, 10, en);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
hns_mac_config_sds_loopback_acpi(काष्ठा hns_mac_cb *mac_cb, bool en)
अणु
	जोड़ acpi_object *obj;
	जोड़ acpi_object obj_args[3], argv4;

	obj_args[0].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	obj_args[0].पूर्णांकeger.value = mac_cb->mac_id;
	obj_args[1].पूर्णांकeger.type = ACPI_TYPE_INTEGER;
	obj_args[1].पूर्णांकeger.value = en;

	argv4.type = ACPI_TYPE_PACKAGE;
	argv4.package.count = 2;
	argv4.package.elements = obj_args;

	obj = acpi_evaluate_dsm(ACPI_HANDLE(mac_cb->dsaf_dev->dev),
				&hns_dsaf_acpi_dsm_guid, 0,
				HNS_OP_SERDES_LP_FUNC, &argv4);
	अगर (!obj) अणु
		dev_warn(mac_cb->dsaf_dev->dev, "set port%d serdes lp fail!",
			 mac_cb->mac_id);

		वापस -ENOTSUPP;
	पूर्ण

	ACPI_FREE(obj);

	वापस 0;
पूर्ण

काष्ठा dsaf_misc_op *hns_misc_op_get(काष्ठा dsaf_device *dsaf_dev)
अणु
	काष्ठा dsaf_misc_op *misc_op;

	misc_op = devm_kzalloc(dsaf_dev->dev, माप(*misc_op), GFP_KERNEL);
	अगर (!misc_op)
		वापस शून्य;

	अगर (dev_of_node(dsaf_dev->dev)) अणु
		misc_op->cpld_set_led = hns_cpld_set_led;
		misc_op->cpld_reset_led = cpld_led_reset;
		misc_op->cpld_set_led_id = cpld_set_led_id;

		misc_op->dsaf_reset = hns_dsaf_rst;
		misc_op->xge_srst = hns_dsaf_xge_srst_by_port;
		misc_op->ge_srst = hns_dsaf_ge_srst_by_port;
		misc_op->ppe_srst = hns_ppe_srst_by_port;
		misc_op->ppe_comm_srst = hns_ppe_com_srst;
		misc_op->hns_dsaf_srst_chns = hns_dsaf_srst_chns;
		misc_op->hns_dsaf_roce_srst = hns_dsaf_roce_srst;

		misc_op->get_phy_अगर = hns_mac_get_phy_अगर;
		misc_op->get_sfp_prsnt = hns_mac_get_sfp_prsnt;

		misc_op->cfg_serdes_loopback = hns_mac_config_sds_loopback;
	पूर्ण अन्यथा अगर (is_acpi_node(dsaf_dev->dev->fwnode)) अणु
		misc_op->cpld_set_led = hns_cpld_set_led_acpi;
		misc_op->cpld_reset_led = cpld_led_reset_acpi;
		misc_op->cpld_set_led_id = cpld_set_led_id_acpi;

		misc_op->dsaf_reset = hns_dsaf_rst_acpi;
		misc_op->xge_srst = hns_dsaf_xge_srst_by_port_acpi;
		misc_op->ge_srst = hns_dsaf_ge_srst_by_port_acpi;
		misc_op->ppe_srst = hns_ppe_srst_by_port_acpi;
		misc_op->ppe_comm_srst = hns_ppe_com_srst;
		misc_op->hns_dsaf_srst_chns = hns_dsaf_srst_chns_acpi;
		misc_op->hns_dsaf_roce_srst = hns_dsaf_roce_srst_acpi;

		misc_op->get_phy_अगर = hns_mac_get_phy_अगर_acpi;
		misc_op->get_sfp_prsnt = hns_mac_get_sfp_prsnt_acpi;

		misc_op->cfg_serdes_loopback = hns_mac_config_sds_loopback_acpi;
	पूर्ण अन्यथा अणु
		devm_kमुक्त(dsaf_dev->dev, (व्योम *)misc_op);
		misc_op = शून्य;
	पूर्ण

	वापस (व्योम *)misc_op;
पूर्ण

काष्ठा
platक्रमm_device *hns_dsaf_find_platक्रमm_device(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device *dev;

	dev = bus_find_device_by_fwnode(&platक्रमm_bus_type, fwnode);
	वापस dev ? to_platक्रमm_device(dev) : शून्य;
पूर्ण
