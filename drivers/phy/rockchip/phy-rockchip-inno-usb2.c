<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Rockchip USB2.0 PHY with Innosilicon IP block driver
 *
 * Copyright (C) 2016 Fuzhou Rockchip Electronics Co., Ltd
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/usb/otg.h>

#घोषणा BIT_WRITEABLE_SHIFT	16
#घोषणा SCHEDULE_DELAY		(60 * HZ)
#घोषणा OTG_SCHEDULE_DELAY	(2 * HZ)

क्रमागत rockchip_usb2phy_port_id अणु
	USB2PHY_PORT_OTG,
	USB2PHY_PORT_HOST,
	USB2PHY_NUM_PORTS,
पूर्ण;

क्रमागत rockchip_usb2phy_host_state अणु
	PHY_STATE_HS_ONLINE	= 0,
	PHY_STATE_DISCONNECT	= 1,
	PHY_STATE_CONNECT	= 2,
	PHY_STATE_FS_LS_ONLINE	= 4,
पूर्ण;

/**
 * क्रमागत usb_chg_state - Dअगरferent states involved in USB अक्षरger detection.
 * @USB_CHG_STATE_UNDEFINED:	USB अक्षरger is not connected or detection
 *				process is not yet started.
 * @USB_CHG_STATE_WAIT_FOR_DCD:	Waiting क्रम Data pins contact.
 * @USB_CHG_STATE_DCD_DONE:	Data pin contact is detected.
 * @USB_CHG_STATE_PRIMARY_DONE:	Primary detection is completed (Detects
 *				between SDP and DCP/CDP).
 * @USB_CHG_STATE_SECONDARY_DONE: Secondary detection is completed (Detects
 *				  between DCP and CDP).
 * @USB_CHG_STATE_DETECTED:	USB अक्षरger type is determined.
 */
क्रमागत usb_chg_state अणु
	USB_CHG_STATE_UNDEFINED = 0,
	USB_CHG_STATE_WAIT_FOR_DCD,
	USB_CHG_STATE_DCD_DONE,
	USB_CHG_STATE_PRIMARY_DONE,
	USB_CHG_STATE_SECONDARY_DONE,
	USB_CHG_STATE_DETECTED,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rockchip_usb2phy_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_CHG_USB_SDP,
	EXTCON_CHG_USB_CDP,
	EXTCON_CHG_USB_DCP,
	EXTCON_CHG_USB_SLOW,
	EXTCON_NONE,
पूर्ण;

काष्ठा usb2phy_reg अणु
	अचिन्हित पूर्णांक	offset;
	अचिन्हित पूर्णांक	bitend;
	अचिन्हित पूर्णांक	bitstart;
	अचिन्हित पूर्णांक	disable;
	अचिन्हित पूर्णांक	enable;
पूर्ण;

/**
 * काष्ठा rockchip_chg_det_reg - usb अक्षरger detect रेजिस्टरs
 * @cp_det: अक्षरging port detected successfully.
 * @dcp_det: dedicated अक्षरging port detected successfully.
 * @dp_det: निश्चित data pin connect successfully.
 * @idm_sink_en: खोलो dm sink curren.
 * @idp_sink_en: खोलो dp sink current.
 * @idp_src_en: खोलो dm source current.
 * @rdm_pdwn_en: खोलो dm pull करोwn resistor.
 * @vdm_src_en: खोलो dm voltage source.
 * @vdp_src_en: खोलो dp voltage source.
 * @opmode: uपंचांगi operational mode.
 */
काष्ठा rockchip_chg_det_reg अणु
	काष्ठा usb2phy_reg	cp_det;
	काष्ठा usb2phy_reg	dcp_det;
	काष्ठा usb2phy_reg	dp_det;
	काष्ठा usb2phy_reg	idm_sink_en;
	काष्ठा usb2phy_reg	idp_sink_en;
	काष्ठा usb2phy_reg	idp_src_en;
	काष्ठा usb2phy_reg	rdm_pdwn_en;
	काष्ठा usb2phy_reg	vdm_src_en;
	काष्ठा usb2phy_reg	vdp_src_en;
	काष्ठा usb2phy_reg	opmode;
पूर्ण;

/**
 * काष्ठा rockchip_usb2phy_port_cfg - usb-phy port configuration.
 * @phy_sus: phy suspend रेजिस्टर.
 * @bvalid_det_en: vbus valid rise detection enable रेजिस्टर.
 * @bvalid_det_st: vbus valid rise detection status रेजिस्टर.
 * @bvalid_det_clr: vbus valid rise detection clear रेजिस्टर.
 * @ls_det_en: linestate detection enable रेजिस्टर.
 * @ls_det_st: linestate detection state रेजिस्टर.
 * @ls_det_clr: linestate detection clear रेजिस्टर.
 * @uपंचांगi_avalid: uपंचांगi vbus avalid status रेजिस्टर.
 * @uपंचांगi_bvalid: uपंचांगi vbus bvalid status रेजिस्टर.
 * @uपंचांगi_ls: uपंचांगi linestate state रेजिस्टर.
 * @uपंचांगi_hstdet: uपंचांगi host disconnect रेजिस्टर.
 */
काष्ठा rockchip_usb2phy_port_cfg अणु
	काष्ठा usb2phy_reg	phy_sus;
	काष्ठा usb2phy_reg	bvalid_det_en;
	काष्ठा usb2phy_reg	bvalid_det_st;
	काष्ठा usb2phy_reg	bvalid_det_clr;
	काष्ठा usb2phy_reg	ls_det_en;
	काष्ठा usb2phy_reg	ls_det_st;
	काष्ठा usb2phy_reg	ls_det_clr;
	काष्ठा usb2phy_reg	uपंचांगi_avalid;
	काष्ठा usb2phy_reg	uपंचांगi_bvalid;
	काष्ठा usb2phy_reg	uपंचांगi_ls;
	काष्ठा usb2phy_reg	uपंचांगi_hstdet;
पूर्ण;

/**
 * काष्ठा rockchip_usb2phy_cfg - usb-phy configuration.
 * @reg: the address offset of grf क्रम usb-phy config.
 * @num_ports: specअगरy how many ports that the phy has.
 * @clkout_ctl: keep on/turn off output clk of phy.
 * @port_cfgs: usb-phy port configurations.
 * @chg_det: अक्षरger detection रेजिस्टरs.
 */
काष्ठा rockchip_usb2phy_cfg अणु
	अचिन्हित पूर्णांक	reg;
	अचिन्हित पूर्णांक	num_ports;
	काष्ठा usb2phy_reg	clkout_ctl;
	स्थिर काष्ठा rockchip_usb2phy_port_cfg	port_cfgs[USB2PHY_NUM_PORTS];
	स्थिर काष्ठा rockchip_chg_det_reg	chg_det;
पूर्ण;

/**
 * काष्ठा rockchip_usb2phy_port - usb-phy port data.
 * @phy: generic phy.
 * @port_id: flag क्रम otg port or host port.
 * @suspended: phy suspended flag.
 * @vbus_attached: otg device vbus status.
 * @bvalid_irq: IRQ number asचिन्हित क्रम vbus valid rise detection.
 * @ls_irq: IRQ number asचिन्हित क्रम linestate detection.
 * @otg_mux_irq: IRQ number which multiplex otg-id/otg-bvalid/linestate
 *		 irqs to one irq in otg-port.
 * @mutex: क्रम रेजिस्टर updating in sm_work.
 * @chg_work: अक्षरge detect work.
 * @otg_sm_work: OTG state machine work.
 * @sm_work: HOST state machine work.
 * @port_cfg: port रेजिस्टर configuration, asचिन्हित by driver data.
 * @event_nb: hold event notअगरication callback.
 * @state: define OTG क्रमागतeration states beक्रमe device reset.
 * @mode: the dr_mode of the controller.
 */
काष्ठा rockchip_usb2phy_port अणु
	काष्ठा phy	*phy;
	अचिन्हित पूर्णांक	port_id;
	bool		suspended;
	bool		vbus_attached;
	पूर्णांक		bvalid_irq;
	पूर्णांक		ls_irq;
	पूर्णांक		otg_mux_irq;
	काष्ठा mutex	mutex;
	काष्ठा		delayed_work chg_work;
	काष्ठा		delayed_work otg_sm_work;
	काष्ठा		delayed_work sm_work;
	स्थिर काष्ठा	rockchip_usb2phy_port_cfg *port_cfg;
	काष्ठा notअगरier_block	event_nb;
	क्रमागत usb_otg_state	state;
	क्रमागत usb_dr_mode	mode;
पूर्ण;

/**
 * काष्ठा rockchip_usb2phy - usb2.0 phy driver data.
 * @dev: poपूर्णांकer to device.
 * @grf: General Register Files regmap.
 * @usbgrf: USB General Register Files regmap.
 * @clk: घड़ी काष्ठा of phy input clk.
 * @clk480m: घड़ी काष्ठा of phy output clk.
 * @clk480m_hw: घड़ी काष्ठा of phy output clk management.
 * @chg_state: states involved in USB अक्षरger detection.
 * @chg_type: USB अक्षरger types.
 * @dcd_retries: The retry count used to track Data contact
 *		 detection process.
 * @edev: extcon device क्रम notअगरication registration
 * @phy_cfg: phy रेजिस्टर configuration, asचिन्हित by driver data.
 * @ports: phy port instance.
 */
काष्ठा rockchip_usb2phy अणु
	काष्ठा device	*dev;
	काष्ठा regmap	*grf;
	काष्ठा regmap	*usbgrf;
	काष्ठा clk	*clk;
	काष्ठा clk	*clk480m;
	काष्ठा clk_hw	clk480m_hw;
	क्रमागत usb_chg_state	chg_state;
	क्रमागत घातer_supply_type	chg_type;
	u8			dcd_retries;
	काष्ठा extcon_dev	*edev;
	स्थिर काष्ठा rockchip_usb2phy_cfg	*phy_cfg;
	काष्ठा rockchip_usb2phy_port	ports[USB2PHY_NUM_PORTS];
पूर्ण;

अटल अंतरभूत काष्ठा regmap *get_reg_base(काष्ठा rockchip_usb2phy *rphy)
अणु
	वापस rphy->usbgrf == शून्य ? rphy->grf : rphy->usbgrf;
पूर्ण

अटल अंतरभूत पूर्णांक property_enable(काष्ठा regmap *base,
				  स्थिर काष्ठा usb2phy_reg *reg, bool en)
अणु
	अचिन्हित पूर्णांक val, mask, पंचांगp;

	पंचांगp = en ? reg->enable : reg->disable;
	mask = GENMASK(reg->bitend, reg->bitstart);
	val = (पंचांगp << reg->bitstart) | (mask << BIT_WRITEABLE_SHIFT);

	वापस regmap_ग_लिखो(base, reg->offset, val);
पूर्ण

अटल अंतरभूत bool property_enabled(काष्ठा regmap *base,
				    स्थिर काष्ठा usb2phy_reg *reg)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पंचांगp, orig;
	अचिन्हित पूर्णांक mask = GENMASK(reg->bitend, reg->bitstart);

	ret = regmap_पढ़ो(base, reg->offset, &orig);
	अगर (ret)
		वापस false;

	पंचांगp = (orig & mask) >> reg->bitstart;
	वापस पंचांगp == reg->enable;
पूर्ण

अटल पूर्णांक rockchip_usb2phy_clk480m_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_usb2phy *rphy =
		container_of(hw, काष्ठा rockchip_usb2phy, clk480m_hw);
	काष्ठा regmap *base = get_reg_base(rphy);
	पूर्णांक ret;

	/* turn on 480m clk output अगर it is off */
	अगर (!property_enabled(base, &rphy->phy_cfg->clkout_ctl)) अणु
		ret = property_enable(base, &rphy->phy_cfg->clkout_ctl, true);
		अगर (ret)
			वापस ret;

		/* रुकोing क्रम the clk become stable */
		usleep_range(1200, 1300);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rockchip_usb2phy_clk480m_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_usb2phy *rphy =
		container_of(hw, काष्ठा rockchip_usb2phy, clk480m_hw);
	काष्ठा regmap *base = get_reg_base(rphy);

	/* turn off 480m clk output */
	property_enable(base, &rphy->phy_cfg->clkout_ctl, false);
पूर्ण

अटल पूर्णांक rockchip_usb2phy_clk480m_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा rockchip_usb2phy *rphy =
		container_of(hw, काष्ठा rockchip_usb2phy, clk480m_hw);
	काष्ठा regmap *base = get_reg_base(rphy);

	वापस property_enabled(base, &rphy->phy_cfg->clkout_ctl);
पूर्ण

अटल अचिन्हित दीर्घ
rockchip_usb2phy_clk480m_recalc_rate(काष्ठा clk_hw *hw,
				     अचिन्हित दीर्घ parent_rate)
अणु
	वापस 480000000;
पूर्ण

अटल स्थिर काष्ठा clk_ops rockchip_usb2phy_clkout_ops = अणु
	.prepare = rockchip_usb2phy_clk480m_prepare,
	.unprepare = rockchip_usb2phy_clk480m_unprepare,
	.is_prepared = rockchip_usb2phy_clk480m_prepared,
	.recalc_rate = rockchip_usb2phy_clk480m_recalc_rate,
पूर्ण;

अटल व्योम rockchip_usb2phy_clk480m_unरेजिस्टर(व्योम *data)
अणु
	काष्ठा rockchip_usb2phy *rphy = data;

	of_clk_del_provider(rphy->dev->of_node);
	clk_unरेजिस्टर(rphy->clk480m);
पूर्ण

अटल पूर्णांक
rockchip_usb2phy_clk480m_रेजिस्टर(काष्ठा rockchip_usb2phy *rphy)
अणु
	काष्ठा device_node *node = rphy->dev->of_node;
	काष्ठा clk_init_data init;
	स्थिर अक्षर *clk_name;
	पूर्णांक ret;

	init.flags = 0;
	init.name = "clk_usbphy_480m";
	init.ops = &rockchip_usb2phy_clkout_ops;

	/* optional override of the घड़ीname */
	of_property_पढ़ो_string(node, "clock-output-names", &init.name);

	अगर (rphy->clk) अणु
		clk_name = __clk_get_name(rphy->clk);
		init.parent_names = &clk_name;
		init.num_parents = 1;
	पूर्ण अन्यथा अणु
		init.parent_names = शून्य;
		init.num_parents = 0;
	पूर्ण

	rphy->clk480m_hw.init = &init;

	/* रेजिस्टर the घड़ी */
	rphy->clk480m = clk_रेजिस्टर(rphy->dev, &rphy->clk480m_hw);
	अगर (IS_ERR(rphy->clk480m)) अणु
		ret = PTR_ERR(rphy->clk480m);
		जाओ err_ret;
	पूर्ण

	ret = of_clk_add_provider(node, of_clk_src_simple_get, rphy->clk480m);
	अगर (ret < 0)
		जाओ err_clk_provider;

	ret = devm_add_action(rphy->dev, rockchip_usb2phy_clk480m_unरेजिस्टर,
			      rphy);
	अगर (ret < 0)
		जाओ err_unreg_action;

	वापस 0;

err_unreg_action:
	of_clk_del_provider(node);
err_clk_provider:
	clk_unरेजिस्टर(rphy->clk480m);
err_ret:
	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_usb2phy_extcon_रेजिस्टर(काष्ठा rockchip_usb2phy *rphy)
अणु
	पूर्णांक ret;
	काष्ठा device_node *node = rphy->dev->of_node;
	काष्ठा extcon_dev *edev;

	अगर (of_property_पढ़ो_bool(node, "extcon")) अणु
		edev = extcon_get_edev_by_phandle(rphy->dev, 0);
		अगर (IS_ERR(edev)) अणु
			अगर (PTR_ERR(edev) != -EPROBE_DEFER)
				dev_err(rphy->dev, "Invalid or missing extcon\n");
			वापस PTR_ERR(edev);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Initialize extcon device */
		edev = devm_extcon_dev_allocate(rphy->dev,
						rockchip_usb2phy_extcon_cable);

		अगर (IS_ERR(edev))
			वापस -ENOMEM;

		ret = devm_extcon_dev_रेजिस्टर(rphy->dev, edev);
		अगर (ret) अणु
			dev_err(rphy->dev, "failed to register extcon device\n");
			वापस ret;
		पूर्ण
	पूर्ण

	rphy->edev = edev;

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_usb2phy_init(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_usb2phy_port *rport = phy_get_drvdata(phy);
	काष्ठा rockchip_usb2phy *rphy = dev_get_drvdata(phy->dev.parent);
	पूर्णांक ret = 0;

	mutex_lock(&rport->mutex);

	अगर (rport->port_id == USB2PHY_PORT_OTG) अणु
		अगर (rport->mode != USB_DR_MODE_HOST &&
		    rport->mode != USB_DR_MODE_UNKNOWN) अणु
			/* clear bvalid status and enable bvalid detect irq */
			ret = property_enable(rphy->grf,
					      &rport->port_cfg->bvalid_det_clr,
					      true);
			अगर (ret)
				जाओ out;

			ret = property_enable(rphy->grf,
					      &rport->port_cfg->bvalid_det_en,
					      true);
			अगर (ret)
				जाओ out;

			schedule_delayed_work(&rport->otg_sm_work,
					      OTG_SCHEDULE_DELAY * 3);
		पूर्ण अन्यथा अणु
			/* If OTG works in host only mode, करो nothing. */
			dev_dbg(&rport->phy->dev, "mode %d\n", rport->mode);
		पूर्ण
	पूर्ण अन्यथा अगर (rport->port_id == USB2PHY_PORT_HOST) अणु
		/* clear linestate and enable linestate detect irq */
		ret = property_enable(rphy->grf,
				      &rport->port_cfg->ls_det_clr, true);
		अगर (ret)
			जाओ out;

		ret = property_enable(rphy->grf,
				      &rport->port_cfg->ls_det_en, true);
		अगर (ret)
			जाओ out;

		schedule_delayed_work(&rport->sm_work, SCHEDULE_DELAY);
	पूर्ण

out:
	mutex_unlock(&rport->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_usb2phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_usb2phy_port *rport = phy_get_drvdata(phy);
	काष्ठा rockchip_usb2phy *rphy = dev_get_drvdata(phy->dev.parent);
	काष्ठा regmap *base = get_reg_base(rphy);
	पूर्णांक ret;

	dev_dbg(&rport->phy->dev, "port power on\n");

	अगर (!rport->suspended)
		वापस 0;

	ret = clk_prepare_enable(rphy->clk480m);
	अगर (ret)
		वापस ret;

	ret = property_enable(base, &rport->port_cfg->phy_sus, false);
	अगर (ret)
		वापस ret;

	/* रुकोing क्रम the uपंचांगi_clk to become stable */
	usleep_range(1500, 2000);

	rport->suspended = false;
	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_usb2phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_usb2phy_port *rport = phy_get_drvdata(phy);
	काष्ठा rockchip_usb2phy *rphy = dev_get_drvdata(phy->dev.parent);
	काष्ठा regmap *base = get_reg_base(rphy);
	पूर्णांक ret;

	dev_dbg(&rport->phy->dev, "port power off\n");

	अगर (rport->suspended)
		वापस 0;

	ret = property_enable(base, &rport->port_cfg->phy_sus, true);
	अगर (ret)
		वापस ret;

	rport->suspended = true;
	clk_disable_unprepare(rphy->clk480m);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_usb2phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_usb2phy_port *rport = phy_get_drvdata(phy);

	अगर (rport->port_id == USB2PHY_PORT_OTG &&
	    rport->mode != USB_DR_MODE_HOST &&
	    rport->mode != USB_DR_MODE_UNKNOWN) अणु
		cancel_delayed_work_sync(&rport->otg_sm_work);
		cancel_delayed_work_sync(&rport->chg_work);
	पूर्ण अन्यथा अगर (rport->port_id == USB2PHY_PORT_HOST)
		cancel_delayed_work_sync(&rport->sm_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops rockchip_usb2phy_ops = अणु
	.init		= rockchip_usb2phy_init,
	.निकास		= rockchip_usb2phy_निकास,
	.घातer_on	= rockchip_usb2phy_घातer_on,
	.घातer_off	= rockchip_usb2phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल व्योम rockchip_usb2phy_otg_sm_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rockchip_usb2phy_port *rport =
		container_of(work, काष्ठा rockchip_usb2phy_port,
			     otg_sm_work.work);
	काष्ठा rockchip_usb2phy *rphy = dev_get_drvdata(rport->phy->dev.parent);
	अटल अचिन्हित पूर्णांक cable;
	अचिन्हित दीर्घ delay;
	bool vbus_attach, sch_work, notअगरy_अक्षरger;

	vbus_attach = property_enabled(rphy->grf,
				       &rport->port_cfg->uपंचांगi_bvalid);

	sch_work = false;
	notअगरy_अक्षरger = false;
	delay = OTG_SCHEDULE_DELAY;
	dev_dbg(&rport->phy->dev, "%s otg sm work\n",
		usb_otg_state_string(rport->state));

	चयन (rport->state) अणु
	हाल OTG_STATE_UNDEFINED:
		rport->state = OTG_STATE_B_IDLE;
		अगर (!vbus_attach)
			rockchip_usb2phy_घातer_off(rport->phy);
		fallthrough;
	हाल OTG_STATE_B_IDLE:
		अगर (extcon_get_state(rphy->edev, EXTCON_USB_HOST) > 0) अणु
			dev_dbg(&rport->phy->dev, "usb otg host connect\n");
			rport->state = OTG_STATE_A_HOST;
			rockchip_usb2phy_घातer_on(rport->phy);
			वापस;
		पूर्ण अन्यथा अगर (vbus_attach) अणु
			dev_dbg(&rport->phy->dev, "vbus_attach\n");
			चयन (rphy->chg_state) अणु
			हाल USB_CHG_STATE_UNDEFINED:
				schedule_delayed_work(&rport->chg_work, 0);
				वापस;
			हाल USB_CHG_STATE_DETECTED:
				चयन (rphy->chg_type) अणु
				हाल POWER_SUPPLY_TYPE_USB:
					dev_dbg(&rport->phy->dev, "sdp cable is connected\n");
					rockchip_usb2phy_घातer_on(rport->phy);
					rport->state = OTG_STATE_B_PERIPHERAL;
					notअगरy_अक्षरger = true;
					sch_work = true;
					cable = EXTCON_CHG_USB_SDP;
					अवरोध;
				हाल POWER_SUPPLY_TYPE_USB_DCP:
					dev_dbg(&rport->phy->dev, "dcp cable is connected\n");
					rockchip_usb2phy_घातer_off(rport->phy);
					notअगरy_अक्षरger = true;
					sch_work = true;
					cable = EXTCON_CHG_USB_DCP;
					अवरोध;
				हाल POWER_SUPPLY_TYPE_USB_CDP:
					dev_dbg(&rport->phy->dev, "cdp cable is connected\n");
					rockchip_usb2phy_घातer_on(rport->phy);
					rport->state = OTG_STATE_B_PERIPHERAL;
					notअगरy_अक्षरger = true;
					sch_work = true;
					cable = EXTCON_CHG_USB_CDP;
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			notअगरy_अक्षरger = true;
			rphy->chg_state = USB_CHG_STATE_UNDEFINED;
			rphy->chg_type = POWER_SUPPLY_TYPE_UNKNOWN;
		पूर्ण

		अगर (rport->vbus_attached != vbus_attach) अणु
			rport->vbus_attached = vbus_attach;

			अगर (notअगरy_अक्षरger && rphy->edev) अणु
				extcon_set_state_sync(rphy->edev,
							cable, vbus_attach);
				अगर (cable == EXTCON_CHG_USB_SDP)
					extcon_set_state_sync(rphy->edev,
							      EXTCON_USB,
							      vbus_attach);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल OTG_STATE_B_PERIPHERAL:
		अगर (!vbus_attach) अणु
			dev_dbg(&rport->phy->dev, "usb disconnect\n");
			rphy->chg_state = USB_CHG_STATE_UNDEFINED;
			rphy->chg_type = POWER_SUPPLY_TYPE_UNKNOWN;
			rport->state = OTG_STATE_B_IDLE;
			delay = 0;
			rockchip_usb2phy_घातer_off(rport->phy);
		पूर्ण
		sch_work = true;
		अवरोध;
	हाल OTG_STATE_A_HOST:
		अगर (extcon_get_state(rphy->edev, EXTCON_USB_HOST) == 0) अणु
			dev_dbg(&rport->phy->dev, "usb otg host disconnect\n");
			rport->state = OTG_STATE_B_IDLE;
			rockchip_usb2phy_घातer_off(rport->phy);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (sch_work)
		schedule_delayed_work(&rport->otg_sm_work, delay);
पूर्ण

अटल स्थिर अक्षर *chg_to_string(क्रमागत घातer_supply_type chg_type)
अणु
	चयन (chg_type) अणु
	हाल POWER_SUPPLY_TYPE_USB:
		वापस "USB_SDP_CHARGER";
	हाल POWER_SUPPLY_TYPE_USB_DCP:
		वापस "USB_DCP_CHARGER";
	हाल POWER_SUPPLY_TYPE_USB_CDP:
		वापस "USB_CDP_CHARGER";
	शेष:
		वापस "INVALID_CHARGER";
	पूर्ण
पूर्ण

अटल व्योम rockchip_chg_enable_dcd(काष्ठा rockchip_usb2phy *rphy,
				    bool en)
अणु
	काष्ठा regmap *base = get_reg_base(rphy);

	property_enable(base, &rphy->phy_cfg->chg_det.rdm_pdwn_en, en);
	property_enable(base, &rphy->phy_cfg->chg_det.idp_src_en, en);
पूर्ण

अटल व्योम rockchip_chg_enable_primary_det(काष्ठा rockchip_usb2phy *rphy,
					    bool en)
अणु
	काष्ठा regmap *base = get_reg_base(rphy);

	property_enable(base, &rphy->phy_cfg->chg_det.vdp_src_en, en);
	property_enable(base, &rphy->phy_cfg->chg_det.idm_sink_en, en);
पूर्ण

अटल व्योम rockchip_chg_enable_secondary_det(काष्ठा rockchip_usb2phy *rphy,
					      bool en)
अणु
	काष्ठा regmap *base = get_reg_base(rphy);

	property_enable(base, &rphy->phy_cfg->chg_det.vdm_src_en, en);
	property_enable(base, &rphy->phy_cfg->chg_det.idp_sink_en, en);
पूर्ण

#घोषणा CHG_DCD_POLL_TIME	(100 * HZ / 1000)
#घोषणा CHG_DCD_MAX_RETRIES	6
#घोषणा CHG_PRIMARY_DET_TIME	(40 * HZ / 1000)
#घोषणा CHG_SECONDARY_DET_TIME	(40 * HZ / 1000)
अटल व्योम rockchip_chg_detect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rockchip_usb2phy_port *rport =
		container_of(work, काष्ठा rockchip_usb2phy_port, chg_work.work);
	काष्ठा rockchip_usb2phy *rphy = dev_get_drvdata(rport->phy->dev.parent);
	काष्ठा regmap *base = get_reg_base(rphy);
	bool is_dcd, पंचांगout, vout;
	अचिन्हित दीर्घ delay;

	dev_dbg(&rport->phy->dev, "chg detection work state = %d\n",
		rphy->chg_state);
	चयन (rphy->chg_state) अणु
	हाल USB_CHG_STATE_UNDEFINED:
		अगर (!rport->suspended)
			rockchip_usb2phy_घातer_off(rport->phy);
		/* put the controller in non-driving mode */
		property_enable(base, &rphy->phy_cfg->chg_det.opmode, false);
		/* Start DCD processing stage 1 */
		rockchip_chg_enable_dcd(rphy, true);
		rphy->chg_state = USB_CHG_STATE_WAIT_FOR_DCD;
		rphy->dcd_retries = 0;
		delay = CHG_DCD_POLL_TIME;
		अवरोध;
	हाल USB_CHG_STATE_WAIT_FOR_DCD:
		/* get data contact detection status */
		is_dcd = property_enabled(rphy->grf,
					  &rphy->phy_cfg->chg_det.dp_det);
		पंचांगout = ++rphy->dcd_retries == CHG_DCD_MAX_RETRIES;
		/* stage 2 */
		अगर (is_dcd || पंचांगout) अणु
			/* stage 4 */
			/* Turn off DCD circuitry */
			rockchip_chg_enable_dcd(rphy, false);
			/* Voltage Source on DP, Probe on DM */
			rockchip_chg_enable_primary_det(rphy, true);
			delay = CHG_PRIMARY_DET_TIME;
			rphy->chg_state = USB_CHG_STATE_DCD_DONE;
		पूर्ण अन्यथा अणु
			/* stage 3 */
			delay = CHG_DCD_POLL_TIME;
		पूर्ण
		अवरोध;
	हाल USB_CHG_STATE_DCD_DONE:
		vout = property_enabled(rphy->grf,
					&rphy->phy_cfg->chg_det.cp_det);
		rockchip_chg_enable_primary_det(rphy, false);
		अगर (vout) अणु
			/* Voltage Source on DM, Probe on DP  */
			rockchip_chg_enable_secondary_det(rphy, true);
			delay = CHG_SECONDARY_DET_TIME;
			rphy->chg_state = USB_CHG_STATE_PRIMARY_DONE;
		पूर्ण अन्यथा अणु
			अगर (rphy->dcd_retries == CHG_DCD_MAX_RETRIES) अणु
				/* भग्नing अक्षरger found */
				rphy->chg_type = POWER_SUPPLY_TYPE_USB_DCP;
				rphy->chg_state = USB_CHG_STATE_DETECTED;
				delay = 0;
			पूर्ण अन्यथा अणु
				rphy->chg_type = POWER_SUPPLY_TYPE_USB;
				rphy->chg_state = USB_CHG_STATE_DETECTED;
				delay = 0;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल USB_CHG_STATE_PRIMARY_DONE:
		vout = property_enabled(rphy->grf,
					&rphy->phy_cfg->chg_det.dcp_det);
		/* Turn off voltage source */
		rockchip_chg_enable_secondary_det(rphy, false);
		अगर (vout)
			rphy->chg_type = POWER_SUPPLY_TYPE_USB_DCP;
		अन्यथा
			rphy->chg_type = POWER_SUPPLY_TYPE_USB_CDP;
		fallthrough;
	हाल USB_CHG_STATE_SECONDARY_DONE:
		rphy->chg_state = USB_CHG_STATE_DETECTED;
		delay = 0;
		fallthrough;
	हाल USB_CHG_STATE_DETECTED:
		/* put the controller in normal mode */
		property_enable(base, &rphy->phy_cfg->chg_det.opmode, true);
		rockchip_usb2phy_otg_sm_work(&rport->otg_sm_work.work);
		dev_dbg(&rport->phy->dev, "charger = %s\n",
			 chg_to_string(rphy->chg_type));
		वापस;
	शेष:
		वापस;
	पूर्ण

	schedule_delayed_work(&rport->chg_work, delay);
पूर्ण

/*
 * The function manage host-phy port state and suspend/resume phy port
 * to save घातer.
 *
 * we rely on uपंचांगi_linestate and uपंचांगi_hostdisconnect to identअगरy whether
 * devices is disconnect or not. Besides, we करो not need care it is FS/LS
 * disconnected or HS disconnected, actually, we just only need get the
 * device is disconnected at last through rearm the delayed work,
 * to suspend the phy port in _PHY_STATE_DISCONNECT_ हाल.
 *
 * NOTE: It may invoke *phy_घातr_off or *phy_घातer_on which will invoke
 * some clk related APIs, so करो not invoke it from पूर्णांकerrupt context directly.
 */
अटल व्योम rockchip_usb2phy_sm_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rockchip_usb2phy_port *rport =
		container_of(work, काष्ठा rockchip_usb2phy_port, sm_work.work);
	काष्ठा rockchip_usb2phy *rphy = dev_get_drvdata(rport->phy->dev.parent);
	अचिन्हित पूर्णांक sh = rport->port_cfg->uपंचांगi_hstdet.bitend -
			  rport->port_cfg->uपंचांगi_hstdet.bitstart + 1;
	अचिन्हित पूर्णांक ul, uhd, state;
	अचिन्हित पूर्णांक ul_mask, uhd_mask;
	पूर्णांक ret;

	mutex_lock(&rport->mutex);

	ret = regmap_पढ़ो(rphy->grf, rport->port_cfg->uपंचांगi_ls.offset, &ul);
	अगर (ret < 0)
		जाओ next_schedule;

	ret = regmap_पढ़ो(rphy->grf, rport->port_cfg->uपंचांगi_hstdet.offset, &uhd);
	अगर (ret < 0)
		जाओ next_schedule;

	uhd_mask = GENMASK(rport->port_cfg->uपंचांगi_hstdet.bitend,
			   rport->port_cfg->uपंचांगi_hstdet.bitstart);
	ul_mask = GENMASK(rport->port_cfg->uपंचांगi_ls.bitend,
			  rport->port_cfg->uपंचांगi_ls.bitstart);

	/* stitch on uपंचांगi_ls and uपंचांगi_hstdet as phy state */
	state = ((uhd & uhd_mask) >> rport->port_cfg->uपंचांगi_hstdet.bitstart) |
		(((ul & ul_mask) >> rport->port_cfg->uपंचांगi_ls.bitstart) << sh);

	चयन (state) अणु
	हाल PHY_STATE_HS_ONLINE:
		dev_dbg(&rport->phy->dev, "HS online\n");
		अवरोध;
	हाल PHY_STATE_FS_LS_ONLINE:
		/*
		 * For FS/LS device, the online state share with connect state
		 * from uपंचांगi_ls and uपंचांगi_hstdet रेजिस्टर, so we distinguish
		 * them via suspended flag.
		 *
		 * Plus, there are two हालs, one is D- Line pull-up, and D+
		 * line pull-करोwn, the state is 4; another is D+ line pull-up,
		 * and D- line pull-करोwn, the state is 2.
		 */
		अगर (!rport->suspended) अणु
			/* D- line pull-up, D+ line pull-करोwn */
			dev_dbg(&rport->phy->dev, "FS/LS online\n");
			अवरोध;
		पूर्ण
		fallthrough;
	हाल PHY_STATE_CONNECT:
		अगर (rport->suspended) अणु
			dev_dbg(&rport->phy->dev, "Connected\n");
			rockchip_usb2phy_घातer_on(rport->phy);
			rport->suspended = false;
		पूर्ण अन्यथा अणु
			/* D+ line pull-up, D- line pull-करोwn */
			dev_dbg(&rport->phy->dev, "FS/LS online\n");
		पूर्ण
		अवरोध;
	हाल PHY_STATE_DISCONNECT:
		अगर (!rport->suspended) अणु
			dev_dbg(&rport->phy->dev, "Disconnected\n");
			rockchip_usb2phy_घातer_off(rport->phy);
			rport->suspended = true;
		पूर्ण

		/*
		 * activate the linestate detection to get the next device
		 * plug-in irq.
		 */
		property_enable(rphy->grf, &rport->port_cfg->ls_det_clr, true);
		property_enable(rphy->grf, &rport->port_cfg->ls_det_en, true);

		/*
		 * we करोn't need to rearm the delayed work when the phy port
		 * is suspended.
		 */
		mutex_unlock(&rport->mutex);
		वापस;
	शेष:
		dev_dbg(&rport->phy->dev, "unknown phy state\n");
		अवरोध;
	पूर्ण

next_schedule:
	mutex_unlock(&rport->mutex);
	schedule_delayed_work(&rport->sm_work, SCHEDULE_DELAY);
पूर्ण

अटल irqवापस_t rockchip_usb2phy_linestate_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rockchip_usb2phy_port *rport = data;
	काष्ठा rockchip_usb2phy *rphy = dev_get_drvdata(rport->phy->dev.parent);

	अगर (!property_enabled(rphy->grf, &rport->port_cfg->ls_det_st))
		वापस IRQ_NONE;

	mutex_lock(&rport->mutex);

	/* disable linestate detect irq and clear its status */
	property_enable(rphy->grf, &rport->port_cfg->ls_det_en, false);
	property_enable(rphy->grf, &rport->port_cfg->ls_det_clr, true);

	mutex_unlock(&rport->mutex);

	/*
	 * In this हाल क्रम host phy port, a new device is plugged in,
	 * meanजबतक, अगर the phy port is suspended, we need rearm the work to
	 * resume it and mange its states; otherwise, we करो nothing about that.
	 */
	अगर (rport->suspended && rport->port_id == USB2PHY_PORT_HOST)
		rockchip_usb2phy_sm_work(&rport->sm_work.work);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rockchip_usb2phy_bvalid_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rockchip_usb2phy_port *rport = data;
	काष्ठा rockchip_usb2phy *rphy = dev_get_drvdata(rport->phy->dev.parent);

	अगर (!property_enabled(rphy->grf, &rport->port_cfg->bvalid_det_st))
		वापस IRQ_NONE;

	mutex_lock(&rport->mutex);

	/* clear bvalid detect irq pending status */
	property_enable(rphy->grf, &rport->port_cfg->bvalid_det_clr, true);

	mutex_unlock(&rport->mutex);

	rockchip_usb2phy_otg_sm_work(&rport->otg_sm_work.work);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t rockchip_usb2phy_otg_mux_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rockchip_usb2phy_port *rport = data;
	काष्ठा rockchip_usb2phy *rphy = dev_get_drvdata(rport->phy->dev.parent);

	अगर (property_enabled(rphy->grf, &rport->port_cfg->bvalid_det_st))
		वापस rockchip_usb2phy_bvalid_irq(irq, data);
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक rockchip_usb2phy_host_port_init(काष्ठा rockchip_usb2phy *rphy,
					   काष्ठा rockchip_usb2phy_port *rport,
					   काष्ठा device_node *child_np)
अणु
	पूर्णांक ret;

	rport->port_id = USB2PHY_PORT_HOST;
	rport->port_cfg = &rphy->phy_cfg->port_cfgs[USB2PHY_PORT_HOST];
	rport->suspended = true;

	mutex_init(&rport->mutex);
	INIT_DELAYED_WORK(&rport->sm_work, rockchip_usb2phy_sm_work);

	rport->ls_irq = of_irq_get_byname(child_np, "linestate");
	अगर (rport->ls_irq < 0) अणु
		dev_err(rphy->dev, "no linestate irq provided\n");
		वापस rport->ls_irq;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(rphy->dev, rport->ls_irq, शून्य,
					rockchip_usb2phy_linestate_irq,
					IRQF_ONESHOT,
					"rockchip_usb2phy", rport);
	अगर (ret) अणु
		dev_err(rphy->dev, "failed to request linestate irq handle\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_otg_event(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा rockchip_usb2phy_port *rport =
		container_of(nb, काष्ठा rockchip_usb2phy_port, event_nb);

	schedule_delayed_work(&rport->otg_sm_work, OTG_SCHEDULE_DELAY);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक rockchip_usb2phy_otg_port_init(काष्ठा rockchip_usb2phy *rphy,
					  काष्ठा rockchip_usb2phy_port *rport,
					  काष्ठा device_node *child_np)
अणु
	पूर्णांक ret;

	rport->port_id = USB2PHY_PORT_OTG;
	rport->port_cfg = &rphy->phy_cfg->port_cfgs[USB2PHY_PORT_OTG];
	rport->state = OTG_STATE_UNDEFINED;

	/*
	 * set suspended flag to true, but actually करोn't
	 * put phy in suspend mode, it aims to enable usb
	 * phy and घड़ी in घातer_on() called by usb controller
	 * driver during probe.
	 */
	rport->suspended = true;
	rport->vbus_attached = false;

	mutex_init(&rport->mutex);

	rport->mode = of_usb_get_dr_mode_by_phy(child_np, -1);
	अगर (rport->mode == USB_DR_MODE_HOST ||
	    rport->mode == USB_DR_MODE_UNKNOWN) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	INIT_DELAYED_WORK(&rport->chg_work, rockchip_chg_detect_work);
	INIT_DELAYED_WORK(&rport->otg_sm_work, rockchip_usb2phy_otg_sm_work);

	/*
	 * Some SoCs use one पूर्णांकerrupt with otg-id/otg-bvalid/linestate
	 * पूर्णांकerrupts muxed together, so probe the otg-mux पूर्णांकerrupt first,
	 * अगर not found, then look क्रम the regular पूर्णांकerrupts one by one.
	 */
	rport->otg_mux_irq = of_irq_get_byname(child_np, "otg-mux");
	अगर (rport->otg_mux_irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(rphy->dev, rport->otg_mux_irq,
						शून्य,
						rockchip_usb2phy_otg_mux_irq,
						IRQF_ONESHOT,
						"rockchip_usb2phy_otg",
						rport);
		अगर (ret) अणु
			dev_err(rphy->dev,
				"failed to request otg-mux irq handle\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		rport->bvalid_irq = of_irq_get_byname(child_np, "otg-bvalid");
		अगर (rport->bvalid_irq < 0) अणु
			dev_err(rphy->dev, "no vbus valid irq provided\n");
			ret = rport->bvalid_irq;
			जाओ out;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(rphy->dev, rport->bvalid_irq,
						शून्य,
						rockchip_usb2phy_bvalid_irq,
						IRQF_ONESHOT,
						"rockchip_usb2phy_bvalid",
						rport);
		अगर (ret) अणु
			dev_err(rphy->dev,
				"failed to request otg-bvalid irq handle\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(rphy->edev)) अणु
		rport->event_nb.notअगरier_call = rockchip_otg_event;

		ret = devm_extcon_रेजिस्टर_notअगरier(rphy->dev, rphy->edev,
					EXTCON_USB_HOST, &rport->event_nb);
		अगर (ret)
			dev_err(rphy->dev, "register USB HOST notifier failed\n");
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_usb2phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child_np;
	काष्ठा phy_provider *provider;
	काष्ठा rockchip_usb2phy *rphy;
	स्थिर काष्ठा rockchip_usb2phy_cfg *phy_cfgs;
	स्थिर काष्ठा of_device_id *match;
	अचिन्हित पूर्णांक reg;
	पूर्णांक index, ret;

	rphy = devm_kzalloc(dev, माप(*rphy), GFP_KERNEL);
	अगर (!rphy)
		वापस -ENOMEM;

	match = of_match_device(dev->driver->of_match_table, dev);
	अगर (!match || !match->data) अणु
		dev_err(dev, "phy configs are not assigned!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!dev->parent || !dev->parent->of_node)
		वापस -EINVAL;

	rphy->grf = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(rphy->grf))
		वापस PTR_ERR(rphy->grf);

	अगर (of_device_is_compatible(np, "rockchip,rv1108-usb2phy")) अणु
		rphy->usbgrf =
			syscon_regmap_lookup_by_phandle(dev->of_node,
							"rockchip,usbgrf");
		अगर (IS_ERR(rphy->usbgrf))
			वापस PTR_ERR(rphy->usbgrf);
	पूर्ण अन्यथा अणु
		rphy->usbgrf = शून्य;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "reg", &reg)) अणु
		dev_err(dev, "the reg property is not assigned in %pOFn node\n",
			np);
		वापस -EINVAL;
	पूर्ण

	rphy->dev = dev;
	phy_cfgs = match->data;
	rphy->chg_state = USB_CHG_STATE_UNDEFINED;
	rphy->chg_type = POWER_SUPPLY_TYPE_UNKNOWN;
	platक्रमm_set_drvdata(pdev, rphy);

	ret = rockchip_usb2phy_extcon_रेजिस्टर(rphy);
	अगर (ret)
		वापस ret;

	/* find out a proper config which can be matched with dt. */
	index = 0;
	जबतक (phy_cfgs[index].reg) अणु
		अगर (phy_cfgs[index].reg == reg) अणु
			rphy->phy_cfg = &phy_cfgs[index];
			अवरोध;
		पूर्ण

		++index;
	पूर्ण

	अगर (!rphy->phy_cfg) अणु
		dev_err(dev, "no phy-config can be matched with %pOFn node\n",
			np);
		वापस -EINVAL;
	पूर्ण

	rphy->clk = of_clk_get_by_name(np, "phyclk");
	अगर (!IS_ERR(rphy->clk)) अणु
		clk_prepare_enable(rphy->clk);
	पूर्ण अन्यथा अणु
		dev_info(&pdev->dev, "no phyclk specified\n");
		rphy->clk = शून्य;
	पूर्ण

	ret = rockchip_usb2phy_clk480m_रेजिस्टर(rphy);
	अगर (ret) अणु
		dev_err(dev, "failed to register 480m output clock\n");
		जाओ disable_clks;
	पूर्ण

	index = 0;
	क्रम_each_available_child_of_node(np, child_np) अणु
		काष्ठा rockchip_usb2phy_port *rport = &rphy->ports[index];
		काष्ठा phy *phy;

		/* This driver aims to support both otg-port and host-port */
		अगर (!of_node_name_eq(child_np, "host-port") &&
		    !of_node_name_eq(child_np, "otg-port"))
			जाओ next_child;

		phy = devm_phy_create(dev, child_np, &rockchip_usb2phy_ops);
		अगर (IS_ERR(phy)) अणु
			dev_err(dev, "failed to create phy\n");
			ret = PTR_ERR(phy);
			जाओ put_child;
		पूर्ण

		rport->phy = phy;
		phy_set_drvdata(rport->phy, rport);

		/* initialize otg/host port separately */
		अगर (of_node_name_eq(child_np, "host-port")) अणु
			ret = rockchip_usb2phy_host_port_init(rphy, rport,
							      child_np);
			अगर (ret)
				जाओ put_child;
		पूर्ण अन्यथा अणु
			ret = rockchip_usb2phy_otg_port_init(rphy, rport,
							     child_np);
			अगर (ret)
				जाओ put_child;
		पूर्ण

next_child:
		/* to prevent out of boundary */
		अगर (++index >= rphy->phy_cfg->num_ports)
			अवरोध;
	पूर्ण

	provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	वापस PTR_ERR_OR_ZERO(provider);

put_child:
	of_node_put(child_np);
disable_clks:
	अगर (rphy->clk) अणु
		clk_disable_unprepare(rphy->clk);
		clk_put(rphy->clk);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rockchip_usb2phy_cfg rk3228_phy_cfgs[] = अणु
	अणु
		.reg = 0x760,
		.num_ports	= 2,
		.clkout_ctl	= अणु 0x0768, 4, 4, 1, 0 पूर्ण,
		.port_cfgs	= अणु
			[USB2PHY_PORT_OTG] = अणु
				.phy_sus	= अणु 0x0760, 15, 0, 0, 0x1d1 पूर्ण,
				.bvalid_det_en	= अणु 0x0680, 3, 3, 0, 1 पूर्ण,
				.bvalid_det_st	= अणु 0x0690, 3, 3, 0, 1 पूर्ण,
				.bvalid_det_clr	= अणु 0x06a0, 3, 3, 0, 1 पूर्ण,
				.ls_det_en	= अणु 0x0680, 2, 2, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0x0690, 2, 2, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0x06a0, 2, 2, 0, 1 पूर्ण,
				.uपंचांगi_bvalid	= अणु 0x0480, 4, 4, 0, 1 पूर्ण,
				.uपंचांगi_ls	= अणु 0x0480, 3, 2, 0, 1 पूर्ण,
			पूर्ण,
			[USB2PHY_PORT_HOST] = अणु
				.phy_sus	= अणु 0x0764, 15, 0, 0, 0x1d1 पूर्ण,
				.ls_det_en	= अणु 0x0680, 4, 4, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0x0690, 4, 4, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0x06a0, 4, 4, 0, 1 पूर्ण
			पूर्ण
		पूर्ण,
		.chg_det = अणु
			.opmode		= अणु 0x0760, 3, 0, 5, 1 पूर्ण,
			.cp_det		= अणु 0x0884, 4, 4, 0, 1 पूर्ण,
			.dcp_det	= अणु 0x0884, 3, 3, 0, 1 पूर्ण,
			.dp_det		= अणु 0x0884, 5, 5, 0, 1 पूर्ण,
			.idm_sink_en	= अणु 0x0768, 8, 8, 0, 1 पूर्ण,
			.idp_sink_en	= अणु 0x0768, 7, 7, 0, 1 पूर्ण,
			.idp_src_en	= अणु 0x0768, 9, 9, 0, 1 पूर्ण,
			.rdm_pdwn_en	= अणु 0x0768, 10, 10, 0, 1 पूर्ण,
			.vdm_src_en	= अणु 0x0768, 12, 12, 0, 1 पूर्ण,
			.vdp_src_en	= अणु 0x0768, 11, 11, 0, 1 पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.reg = 0x800,
		.num_ports	= 2,
		.clkout_ctl	= अणु 0x0808, 4, 4, 1, 0 पूर्ण,
		.port_cfgs	= अणु
			[USB2PHY_PORT_OTG] = अणु
				.phy_sus	= अणु 0x800, 15, 0, 0, 0x1d1 पूर्ण,
				.ls_det_en	= अणु 0x0684, 0, 0, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0x0694, 0, 0, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0x06a4, 0, 0, 0, 1 पूर्ण
			पूर्ण,
			[USB2PHY_PORT_HOST] = अणु
				.phy_sus	= अणु 0x804, 15, 0, 0, 0x1d1 पूर्ण,
				.ls_det_en	= अणु 0x0684, 1, 1, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0x0694, 1, 1, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0x06a4, 1, 1, 0, 1 पूर्ण
			पूर्ण
		पूर्ण,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rockchip_usb2phy_cfg rk3328_phy_cfgs[] = अणु
	अणु
		.reg = 0x100,
		.num_ports	= 2,
		.clkout_ctl	= अणु 0x108, 4, 4, 1, 0 पूर्ण,
		.port_cfgs	= अणु
			[USB2PHY_PORT_OTG] = अणु
				.phy_sus	= अणु 0x0100, 15, 0, 0, 0x1d1 पूर्ण,
				.bvalid_det_en	= अणु 0x0110, 2, 2, 0, 1 पूर्ण,
				.bvalid_det_st	= अणु 0x0114, 2, 2, 0, 1 पूर्ण,
				.bvalid_det_clr = अणु 0x0118, 2, 2, 0, 1 पूर्ण,
				.ls_det_en	= अणु 0x0110, 0, 0, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0x0114, 0, 0, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0x0118, 0, 0, 0, 1 पूर्ण,
				.uपंचांगi_avalid	= अणु 0x0120, 10, 10, 0, 1 पूर्ण,
				.uपंचांगi_bvalid	= अणु 0x0120, 9, 9, 0, 1 पूर्ण,
				.uपंचांगi_ls	= अणु 0x0120, 5, 4, 0, 1 पूर्ण,
			पूर्ण,
			[USB2PHY_PORT_HOST] = अणु
				.phy_sus	= अणु 0x104, 15, 0, 0, 0x1d1 पूर्ण,
				.ls_det_en	= अणु 0x110, 1, 1, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0x114, 1, 1, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0x118, 1, 1, 0, 1 पूर्ण,
				.uपंचांगi_ls	= अणु 0x120, 17, 16, 0, 1 पूर्ण,
				.uपंचांगi_hstdet	= अणु 0x120, 19, 19, 0, 1 पूर्ण
			पूर्ण
		पूर्ण,
		.chg_det = अणु
			.opmode		= अणु 0x0100, 3, 0, 5, 1 पूर्ण,
			.cp_det		= अणु 0x0120, 24, 24, 0, 1 पूर्ण,
			.dcp_det	= अणु 0x0120, 23, 23, 0, 1 पूर्ण,
			.dp_det		= अणु 0x0120, 25, 25, 0, 1 पूर्ण,
			.idm_sink_en	= अणु 0x0108, 8, 8, 0, 1 पूर्ण,
			.idp_sink_en	= अणु 0x0108, 7, 7, 0, 1 पूर्ण,
			.idp_src_en	= अणु 0x0108, 9, 9, 0, 1 पूर्ण,
			.rdm_pdwn_en	= अणु 0x0108, 10, 10, 0, 1 पूर्ण,
			.vdm_src_en	= अणु 0x0108, 12, 12, 0, 1 पूर्ण,
			.vdp_src_en	= अणु 0x0108, 11, 11, 0, 1 पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rockchip_usb2phy_cfg rk3366_phy_cfgs[] = अणु
	अणु
		.reg = 0x700,
		.num_ports	= 2,
		.clkout_ctl	= अणु 0x0724, 15, 15, 1, 0 पूर्ण,
		.port_cfgs	= अणु
			[USB2PHY_PORT_HOST] = अणु
				.phy_sus	= अणु 0x0728, 15, 0, 0, 0x1d1 पूर्ण,
				.ls_det_en	= अणु 0x0680, 4, 4, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0x0690, 4, 4, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0x06a0, 4, 4, 0, 1 पूर्ण,
				.uपंचांगi_ls	= अणु 0x049c, 14, 13, 0, 1 पूर्ण,
				.uपंचांगi_hstdet	= अणु 0x049c, 12, 12, 0, 1 पूर्ण
			पूर्ण
		पूर्ण,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rockchip_usb2phy_cfg rk3399_phy_cfgs[] = अणु
	अणु
		.reg		= 0xe450,
		.num_ports	= 2,
		.clkout_ctl	= अणु 0xe450, 4, 4, 1, 0 पूर्ण,
		.port_cfgs	= अणु
			[USB2PHY_PORT_OTG] = अणु
				.phy_sus	= अणु 0xe454, 1, 0, 2, 1 पूर्ण,
				.bvalid_det_en	= अणु 0xe3c0, 3, 3, 0, 1 पूर्ण,
				.bvalid_det_st	= अणु 0xe3e0, 3, 3, 0, 1 पूर्ण,
				.bvalid_det_clr	= अणु 0xe3d0, 3, 3, 0, 1 पूर्ण,
				.uपंचांगi_avalid	= अणु 0xe2ac, 7, 7, 0, 1 पूर्ण,
				.uपंचांगi_bvalid	= अणु 0xe2ac, 12, 12, 0, 1 पूर्ण,
			पूर्ण,
			[USB2PHY_PORT_HOST] = अणु
				.phy_sus	= अणु 0xe458, 1, 0, 0x2, 0x1 पूर्ण,
				.ls_det_en	= अणु 0xe3c0, 6, 6, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0xe3e0, 6, 6, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0xe3d0, 6, 6, 0, 1 पूर्ण,
				.uपंचांगi_ls	= अणु 0xe2ac, 22, 21, 0, 1 पूर्ण,
				.uपंचांगi_hstdet	= अणु 0xe2ac, 23, 23, 0, 1 पूर्ण
			पूर्ण
		पूर्ण,
		.chg_det = अणु
			.opmode		= अणु 0xe454, 3, 0, 5, 1 पूर्ण,
			.cp_det		= अणु 0xe2ac, 2, 2, 0, 1 पूर्ण,
			.dcp_det	= अणु 0xe2ac, 1, 1, 0, 1 पूर्ण,
			.dp_det		= अणु 0xe2ac, 0, 0, 0, 1 पूर्ण,
			.idm_sink_en	= अणु 0xe450, 8, 8, 0, 1 पूर्ण,
			.idp_sink_en	= अणु 0xe450, 7, 7, 0, 1 पूर्ण,
			.idp_src_en	= अणु 0xe450, 9, 9, 0, 1 पूर्ण,
			.rdm_pdwn_en	= अणु 0xe450, 10, 10, 0, 1 पूर्ण,
			.vdm_src_en	= अणु 0xe450, 12, 12, 0, 1 पूर्ण,
			.vdp_src_en	= अणु 0xe450, 11, 11, 0, 1 पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु
		.reg		= 0xe460,
		.num_ports	= 2,
		.clkout_ctl	= अणु 0xe460, 4, 4, 1, 0 पूर्ण,
		.port_cfgs	= अणु
			[USB2PHY_PORT_OTG] = अणु
				.phy_sus        = अणु 0xe464, 1, 0, 2, 1 पूर्ण,
				.bvalid_det_en  = अणु 0xe3c0, 8, 8, 0, 1 पूर्ण,
				.bvalid_det_st  = अणु 0xe3e0, 8, 8, 0, 1 पूर्ण,
				.bvalid_det_clr = अणु 0xe3d0, 8, 8, 0, 1 पूर्ण,
				.uपंचांगi_avalid	= अणु 0xe2ac, 10, 10, 0, 1 पूर्ण,
				.uपंचांगi_bvalid    = अणु 0xe2ac, 16, 16, 0, 1 पूर्ण,
			पूर्ण,
			[USB2PHY_PORT_HOST] = अणु
				.phy_sus	= अणु 0xe468, 1, 0, 0x2, 0x1 पूर्ण,
				.ls_det_en	= अणु 0xe3c0, 11, 11, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0xe3e0, 11, 11, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0xe3d0, 11, 11, 0, 1 पूर्ण,
				.uपंचांगi_ls	= अणु 0xe2ac, 26, 25, 0, 1 पूर्ण,
				.uपंचांगi_hstdet	= अणु 0xe2ac, 27, 27, 0, 1 पूर्ण
			पूर्ण
		पूर्ण,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा rockchip_usb2phy_cfg rv1108_phy_cfgs[] = अणु
	अणु
		.reg = 0x100,
		.num_ports	= 2,
		.clkout_ctl	= अणु 0x108, 4, 4, 1, 0 पूर्ण,
		.port_cfgs	= अणु
			[USB2PHY_PORT_OTG] = अणु
				.phy_sus	= अणु 0x0100, 15, 0, 0, 0x1d1 पूर्ण,
				.bvalid_det_en	= अणु 0x0680, 3, 3, 0, 1 पूर्ण,
				.bvalid_det_st	= अणु 0x0690, 3, 3, 0, 1 पूर्ण,
				.bvalid_det_clr = अणु 0x06a0, 3, 3, 0, 1 पूर्ण,
				.ls_det_en	= अणु 0x0680, 2, 2, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0x0690, 2, 2, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0x06a0, 2, 2, 0, 1 पूर्ण,
				.uपंचांगi_bvalid	= अणु 0x0804, 10, 10, 0, 1 पूर्ण,
				.uपंचांगi_ls	= अणु 0x0804, 13, 12, 0, 1 पूर्ण,
			पूर्ण,
			[USB2PHY_PORT_HOST] = अणु
				.phy_sus	= अणु 0x0104, 15, 0, 0, 0x1d1 पूर्ण,
				.ls_det_en	= अणु 0x0680, 4, 4, 0, 1 पूर्ण,
				.ls_det_st	= अणु 0x0690, 4, 4, 0, 1 पूर्ण,
				.ls_det_clr	= अणु 0x06a0, 4, 4, 0, 1 पूर्ण,
				.uपंचांगi_ls	= अणु 0x0804, 9, 8, 0, 1 पूर्ण,
				.uपंचांगi_hstdet	= अणु 0x0804, 7, 7, 0, 1 पूर्ण
			पूर्ण
		पूर्ण,
		.chg_det = अणु
			.opmode		= अणु 0x0100, 3, 0, 5, 1 पूर्ण,
			.cp_det		= अणु 0x0804, 1, 1, 0, 1 पूर्ण,
			.dcp_det	= अणु 0x0804, 0, 0, 0, 1 पूर्ण,
			.dp_det		= अणु 0x0804, 2, 2, 0, 1 पूर्ण,
			.idm_sink_en	= अणु 0x0108, 8, 8, 0, 1 पूर्ण,
			.idp_sink_en	= अणु 0x0108, 7, 7, 0, 1 पूर्ण,
			.idp_src_en	= अणु 0x0108, 9, 9, 0, 1 पूर्ण,
			.rdm_pdwn_en	= अणु 0x0108, 10, 10, 0, 1 पूर्ण,
			.vdm_src_en	= अणु 0x0108, 12, 12, 0, 1 पूर्ण,
			.vdp_src_en	= अणु 0x0108, 11, 11, 0, 1 पूर्ण,
		पूर्ण,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_usb2phy_dt_match[] = अणु
	अणु .compatible = "rockchip,px30-usb2phy", .data = &rk3328_phy_cfgs पूर्ण,
	अणु .compatible = "rockchip,rk3228-usb2phy", .data = &rk3228_phy_cfgs पूर्ण,
	अणु .compatible = "rockchip,rk3328-usb2phy", .data = &rk3328_phy_cfgs पूर्ण,
	अणु .compatible = "rockchip,rk3366-usb2phy", .data = &rk3366_phy_cfgs पूर्ण,
	अणु .compatible = "rockchip,rk3399-usb2phy", .data = &rk3399_phy_cfgs पूर्ण,
	अणु .compatible = "rockchip,rv1108-usb2phy", .data = &rv1108_phy_cfgs पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_usb2phy_dt_match);

अटल काष्ठा platक्रमm_driver rockchip_usb2phy_driver = अणु
	.probe		= rockchip_usb2phy_probe,
	.driver		= अणु
		.name	= "rockchip-usb2phy",
		.of_match_table = rockchip_usb2phy_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rockchip_usb2phy_driver);

MODULE_AUTHOR("Frank Wang <frank.wang@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip USB2.0 PHY driver");
MODULE_LICENSE("GPL v2");
