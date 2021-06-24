<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Generic ULPI USB transceiver support
 *
 * Copyright (C) 2009 Daniel Mack <daniel@caiaq.de>
 *
 * Based on sources from
 *
 *   Sascha Hauer <s.hauer@pengutronix.de>
 *   Freescale Semiconductors
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/otg.h>
#समावेश <linux/usb/ulpi.h>


काष्ठा ulpi_info अणु
	अचिन्हित पूर्णांक	id;
	अक्षर		*name;
पूर्ण;

#घोषणा ULPI_ID(venकरोr, product) (((venकरोr) << 16) | (product))
#घोषणा ULPI_INFO(_id, _name)		\
	अणु				\
		.id	= (_id),	\
		.name	= (_name),	\
	पूर्ण

/* ULPI hardcoded IDs, used क्रम probing */
अटल काष्ठा ulpi_info ulpi_ids[] = अणु
	ULPI_INFO(ULPI_ID(0x04cc, 0x1504), "NXP ISP1504"),
	ULPI_INFO(ULPI_ID(0x0424, 0x0006), "SMSC USB331x"),
	ULPI_INFO(ULPI_ID(0x0424, 0x0007), "SMSC USB3320"),
	ULPI_INFO(ULPI_ID(0x0424, 0x0009), "SMSC USB334x"),
	ULPI_INFO(ULPI_ID(0x0451, 0x1507), "TI TUSB1210"),
पूर्ण;

अटल पूर्णांक ulpi_set_otg_flags(काष्ठा usb_phy *phy)
अणु
	अचिन्हित पूर्णांक flags = ULPI_OTG_CTRL_DP_PULLDOWN |
			     ULPI_OTG_CTRL_DM_PULLDOWN;

	अगर (phy->flags & ULPI_OTG_ID_PULLUP)
		flags |= ULPI_OTG_CTRL_ID_PULLUP;

	/*
	 * ULPI Specअगरication rev.1.1 शेष
	 * क्रम Dp/DmPullकरोwn is enabled.
	 */
	अगर (phy->flags & ULPI_OTG_DP_PULLDOWN_DIS)
		flags &= ~ULPI_OTG_CTRL_DP_PULLDOWN;

	अगर (phy->flags & ULPI_OTG_DM_PULLDOWN_DIS)
		flags &= ~ULPI_OTG_CTRL_DM_PULLDOWN;

	अगर (phy->flags & ULPI_OTG_EXTVBUSIND)
		flags |= ULPI_OTG_CTRL_EXTVBUSIND;

	वापस usb_phy_io_ग_लिखो(phy, flags, ULPI_OTG_CTRL);
पूर्ण

अटल पूर्णांक ulpi_set_fc_flags(काष्ठा usb_phy *phy)
अणु
	अचिन्हित पूर्णांक flags = 0;

	/*
	 * ULPI Specअगरication rev.1.1 शेष
	 * क्रम XcvrSelect is Full Speed.
	 */
	अगर (phy->flags & ULPI_FC_HS)
		flags |= ULPI_FUNC_CTRL_HIGH_SPEED;
	अन्यथा अगर (phy->flags & ULPI_FC_LS)
		flags |= ULPI_FUNC_CTRL_LOW_SPEED;
	अन्यथा अगर (phy->flags & ULPI_FC_FS4LS)
		flags |= ULPI_FUNC_CTRL_FS4LS;
	अन्यथा
		flags |= ULPI_FUNC_CTRL_FULL_SPEED;

	अगर (phy->flags & ULPI_FC_TERMSEL)
		flags |= ULPI_FUNC_CTRL_TERMSELECT;

	/*
	 * ULPI Specअगरication rev.1.1 शेष
	 * क्रम OpMode is Normal Operation.
	 */
	अगर (phy->flags & ULPI_FC_OP_NODRV)
		flags |= ULPI_FUNC_CTRL_OPMODE_NONDRIVING;
	अन्यथा अगर (phy->flags & ULPI_FC_OP_DIS_NRZI)
		flags |= ULPI_FUNC_CTRL_OPMODE_DISABLE_NRZI;
	अन्यथा अगर (phy->flags & ULPI_FC_OP_NSYNC_NEOP)
		flags |= ULPI_FUNC_CTRL_OPMODE_NOSYNC_NOEOP;
	अन्यथा
		flags |= ULPI_FUNC_CTRL_OPMODE_NORMAL;

	/*
	 * ULPI Specअगरication rev.1.1 शेष
	 * क्रम SuspendM is Powered.
	 */
	flags |= ULPI_FUNC_CTRL_SUSPENDM;

	वापस usb_phy_io_ग_लिखो(phy, flags, ULPI_FUNC_CTRL);
पूर्ण

अटल पूर्णांक ulpi_set_ic_flags(काष्ठा usb_phy *phy)
अणु
	अचिन्हित पूर्णांक flags = 0;

	अगर (phy->flags & ULPI_IC_AUTORESUME)
		flags |= ULPI_IFC_CTRL_AUTORESUME;

	अगर (phy->flags & ULPI_IC_EXTVBUS_INDINV)
		flags |= ULPI_IFC_CTRL_EXTERNAL_VBUS;

	अगर (phy->flags & ULPI_IC_IND_PASSTHRU)
		flags |= ULPI_IFC_CTRL_PASSTHRU;

	अगर (phy->flags & ULPI_IC_PROTECT_DIS)
		flags |= ULPI_IFC_CTRL_PROTECT_IFC_DISABLE;

	वापस usb_phy_io_ग_लिखो(phy, flags, ULPI_IFC_CTRL);
पूर्ण

अटल पूर्णांक ulpi_set_flags(काष्ठा usb_phy *phy)
अणु
	पूर्णांक ret;

	ret = ulpi_set_otg_flags(phy);
	अगर (ret)
		वापस ret;

	ret = ulpi_set_ic_flags(phy);
	अगर (ret)
		वापस ret;

	वापस ulpi_set_fc_flags(phy);
पूर्ण

अटल पूर्णांक ulpi_check_पूर्णांकegrity(काष्ठा usb_phy *phy)
अणु
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक val = 0x55;

	क्रम (i = 0; i < 2; i++) अणु
		ret = usb_phy_io_ग_लिखो(phy, val, ULPI_SCRATCH);
		अगर (ret < 0)
			वापस ret;

		ret = usb_phy_io_पढ़ो(phy, ULPI_SCRATCH);
		अगर (ret < 0)
			वापस ret;

		अगर (ret != val) अणु
			pr_err("ULPI integrity check: failed!");
			वापस -ENODEV;
		पूर्ण
		val = val << 1;
	पूर्ण

	pr_info("ULPI integrity check: passed.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ulpi_init(काष्ठा usb_phy *phy)
अणु
	पूर्णांक i, vid, pid, ret;
	u32 ulpi_id = 0;

	क्रम (i = 0; i < 4; i++) अणु
		ret = usb_phy_io_पढ़ो(phy, ULPI_PRODUCT_ID_HIGH - i);
		अगर (ret < 0)
			वापस ret;
		ulpi_id = (ulpi_id << 8) | ret;
	पूर्ण
	vid = ulpi_id & 0xffff;
	pid = ulpi_id >> 16;

	pr_info("ULPI transceiver vendor/product ID 0x%04x/0x%04x\n", vid, pid);

	क्रम (i = 0; i < ARRAY_SIZE(ulpi_ids); i++) अणु
		अगर (ulpi_ids[i].id == ULPI_ID(vid, pid)) अणु
			pr_info("Found %s ULPI transceiver.\n",
				ulpi_ids[i].name);
			अवरोध;
		पूर्ण
	पूर्ण

	ret = ulpi_check_पूर्णांकegrity(phy);
	अगर (ret)
		वापस ret;

	वापस ulpi_set_flags(phy);
पूर्ण

अटल पूर्णांक ulpi_set_host(काष्ठा usb_otg *otg, काष्ठा usb_bus *host)
अणु
	काष्ठा usb_phy *phy = otg->usb_phy;
	अचिन्हित पूर्णांक flags = usb_phy_io_पढ़ो(phy, ULPI_IFC_CTRL);

	अगर (!host) अणु
		otg->host = शून्य;
		वापस 0;
	पूर्ण

	otg->host = host;

	flags &= ~(ULPI_IFC_CTRL_6_PIN_SERIAL_MODE |
		   ULPI_IFC_CTRL_3_PIN_SERIAL_MODE |
		   ULPI_IFC_CTRL_CARKITMODE);

	अगर (phy->flags & ULPI_IC_6PIN_SERIAL)
		flags |= ULPI_IFC_CTRL_6_PIN_SERIAL_MODE;
	अन्यथा अगर (phy->flags & ULPI_IC_3PIN_SERIAL)
		flags |= ULPI_IFC_CTRL_3_PIN_SERIAL_MODE;
	अन्यथा अगर (phy->flags & ULPI_IC_CARKIT)
		flags |= ULPI_IFC_CTRL_CARKITMODE;

	वापस usb_phy_io_ग_लिखो(phy, flags, ULPI_IFC_CTRL);
पूर्ण

अटल पूर्णांक ulpi_set_vbus(काष्ठा usb_otg *otg, bool on)
अणु
	काष्ठा usb_phy *phy = otg->usb_phy;
	अचिन्हित पूर्णांक flags = usb_phy_io_पढ़ो(phy, ULPI_OTG_CTRL);

	flags &= ~(ULPI_OTG_CTRL_DRVVBUS | ULPI_OTG_CTRL_DRVVBUS_EXT);

	अगर (on) अणु
		अगर (phy->flags & ULPI_OTG_DRVVBUS)
			flags |= ULPI_OTG_CTRL_DRVVBUS;

		अगर (phy->flags & ULPI_OTG_DRVVBUS_EXT)
			flags |= ULPI_OTG_CTRL_DRVVBUS_EXT;
	पूर्ण

	वापस usb_phy_io_ग_लिखो(phy, flags, ULPI_OTG_CTRL);
पूर्ण

अटल व्योम otg_ulpi_init(काष्ठा usb_phy *phy, काष्ठा usb_otg *otg,
			  काष्ठा usb_phy_io_ops *ops,
			  अचिन्हित पूर्णांक flags)
अणु
	phy->label	= "ULPI";
	phy->flags	= flags;
	phy->io_ops	= ops;
	phy->otg	= otg;
	phy->init	= ulpi_init;

	otg->usb_phy	= phy;
	otg->set_host	= ulpi_set_host;
	otg->set_vbus	= ulpi_set_vbus;
पूर्ण

काष्ठा usb_phy *
otg_ulpi_create(काष्ठा usb_phy_io_ops *ops,
		अचिन्हित पूर्णांक flags)
अणु
	काष्ठा usb_phy *phy;
	काष्ठा usb_otg *otg;

	phy = kzalloc(माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस शून्य;

	otg = kzalloc(माप(*otg), GFP_KERNEL);
	अगर (!otg) अणु
		kमुक्त(phy);
		वापस शून्य;
	पूर्ण

	otg_ulpi_init(phy, otg, ops, flags);

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(otg_ulpi_create);

काष्ठा usb_phy *
devm_otg_ulpi_create(काष्ठा device *dev,
		     काष्ठा usb_phy_io_ops *ops,
		     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा usb_phy *phy;
	काष्ठा usb_otg *otg;

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस शून्य;

	otg = devm_kzalloc(dev, माप(*otg), GFP_KERNEL);
	अगर (!otg) अणु
		devm_kमुक्त(dev, phy);
		वापस शून्य;
	पूर्ण

	otg_ulpi_init(phy, otg, ops, flags);

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_otg_ulpi_create);
