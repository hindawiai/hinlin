<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * r8169_phy_config.c: RealTek 8169/8168/8101 ethernet driver.
 *
 * Copyright (c) 2002 ShuChen <shuchen@realtek.com.tw>
 * Copyright (c) 2003 - 2007 Francois Romieu <romieu@fr.zoreil.com>
 * Copyright (c) a lot of people too. Please respect their work.
 *
 * See MAINTAINERS file क्रम support contact inक्रमmation.
 */

#समावेश <linux/delay.h>
#समावेश <linux/phy.h>

#समावेश "r8169.h"

प्रकार व्योम (*rtl_phy_cfg_fct)(काष्ठा rtl8169_निजी *tp,
				काष्ठा phy_device *phydev);

अटल व्योम r8168d_modअगरy_extpage(काष्ठा phy_device *phydev, पूर्णांक extpage,
				  पूर्णांक reg, u16 mask, u16 val)
अणु
	पूर्णांक oldpage = phy_select_page(phydev, 0x0007);

	__phy_ग_लिखो(phydev, 0x1e, extpage);
	__phy_modअगरy(phydev, reg, mask, val);

	phy_restore_page(phydev, oldpage, 0);
पूर्ण

अटल व्योम r8168d_phy_param(काष्ठा phy_device *phydev, u16 parm,
			     u16 mask, u16 val)
अणु
	पूर्णांक oldpage = phy_select_page(phydev, 0x0005);

	__phy_ग_लिखो(phydev, 0x05, parm);
	__phy_modअगरy(phydev, 0x06, mask, val);

	phy_restore_page(phydev, oldpage, 0);
पूर्ण

अटल व्योम r8168g_phy_param(काष्ठा phy_device *phydev, u16 parm,
			     u16 mask, u16 val)
अणु
	पूर्णांक oldpage = phy_select_page(phydev, 0x0a43);

	__phy_ग_लिखो(phydev, 0x13, parm);
	__phy_modअगरy(phydev, 0x14, mask, val);

	phy_restore_page(phydev, oldpage, 0);
पूर्ण

काष्ठा phy_reg अणु
	u16 reg;
	u16 val;
पूर्ण;

अटल व्योम __rtl_ग_लिखोphy_batch(काष्ठा phy_device *phydev,
				 स्थिर काष्ठा phy_reg *regs, पूर्णांक len)
अणु
	phy_lock_mdio_bus(phydev);

	जबतक (len-- > 0) अणु
		__phy_ग_लिखो(phydev, regs->reg, regs->val);
		regs++;
	पूर्ण

	phy_unlock_mdio_bus(phydev);
पूर्ण

#घोषणा rtl_ग_लिखोphy_batch(p, a) __rtl_ग_लिखोphy_batch(p, a, ARRAY_SIZE(a))

अटल व्योम rtl8168f_config_eee_phy(काष्ठा phy_device *phydev)
अणु
	r8168d_modअगरy_extpage(phydev, 0x0020, 0x15, 0, BIT(8));
	r8168d_phy_param(phydev, 0x8b85, 0, BIT(13));
पूर्ण

अटल व्योम rtl8168g_config_eee_phy(काष्ठा phy_device *phydev)
अणु
	phy_modअगरy_paged(phydev, 0x0a43, 0x11, 0, BIT(4));
पूर्ण

अटल व्योम rtl8168h_config_eee_phy(काष्ठा phy_device *phydev)
अणु
	rtl8168g_config_eee_phy(phydev);

	phy_modअगरy_paged(phydev, 0xa4a, 0x11, 0x0000, 0x0200);
	phy_modअगरy_paged(phydev, 0xa42, 0x14, 0x0000, 0x0080);
पूर्ण

अटल व्योम rtl8125a_config_eee_phy(काष्ठा phy_device *phydev)
अणु
	rtl8168h_config_eee_phy(phydev);

	phy_modअगरy_paged(phydev, 0xa6d, 0x12, 0x0001, 0x0000);
	phy_modअगरy_paged(phydev, 0xa6d, 0x14, 0x0010, 0x0000);
पूर्ण

अटल व्योम rtl8125b_config_eee_phy(काष्ठा phy_device *phydev)
अणु
	phy_modअगरy_paged(phydev, 0xa6d, 0x12, 0x0001, 0x0000);
	phy_modअगरy_paged(phydev, 0xa6d, 0x14, 0x0010, 0x0000);
	phy_modअगरy_paged(phydev, 0xa42, 0x14, 0x0080, 0x0000);
	phy_modअगरy_paged(phydev, 0xa4a, 0x11, 0x0200, 0x0000);
पूर्ण

अटल व्योम rtl8169s_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				   काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा phy_reg phy_reg_init[] = अणु
		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x06, 0x006e पूर्ण,
		अणु 0x08, 0x0708 पूर्ण,
		अणु 0x15, 0x4000 पूर्ण,
		अणु 0x18, 0x65c7 पूर्ण,

		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x03, 0x00a1 पूर्ण,
		अणु 0x02, 0x0008 पूर्ण,
		अणु 0x01, 0x0120 पूर्ण,
		अणु 0x00, 0x1000 पूर्ण,
		अणु 0x04, 0x0800 पूर्ण,
		अणु 0x04, 0x0000 पूर्ण,

		अणु 0x03, 0xff41 पूर्ण,
		अणु 0x02, 0xdf60 पूर्ण,
		अणु 0x01, 0x0140 पूर्ण,
		अणु 0x00, 0x0077 पूर्ण,
		अणु 0x04, 0x7800 पूर्ण,
		अणु 0x04, 0x7000 पूर्ण,

		अणु 0x03, 0x802f पूर्ण,
		अणु 0x02, 0x4f02 पूर्ण,
		अणु 0x01, 0x0409 पूर्ण,
		अणु 0x00, 0xf0f9 पूर्ण,
		अणु 0x04, 0x9800 पूर्ण,
		अणु 0x04, 0x9000 पूर्ण,

		अणु 0x03, 0xdf01 पूर्ण,
		अणु 0x02, 0xdf20 पूर्ण,
		अणु 0x01, 0xff95 पूर्ण,
		अणु 0x00, 0xba00 पूर्ण,
		अणु 0x04, 0xa800 पूर्ण,
		अणु 0x04, 0xa000 पूर्ण,

		अणु 0x03, 0xff41 पूर्ण,
		अणु 0x02, 0xdf20 पूर्ण,
		अणु 0x01, 0x0140 पूर्ण,
		अणु 0x00, 0x00bb पूर्ण,
		अणु 0x04, 0xb800 पूर्ण,
		अणु 0x04, 0xb000 पूर्ण,

		अणु 0x03, 0xdf41 पूर्ण,
		अणु 0x02, 0xdc60 पूर्ण,
		अणु 0x01, 0x6340 पूर्ण,
		अणु 0x00, 0x007d पूर्ण,
		अणु 0x04, 0xd800 पूर्ण,
		अणु 0x04, 0xd000 पूर्ण,

		अणु 0x03, 0xdf01 पूर्ण,
		अणु 0x02, 0xdf20 पूर्ण,
		अणु 0x01, 0x100a पूर्ण,
		अणु 0x00, 0xa0ff पूर्ण,
		अणु 0x04, 0xf800 पूर्ण,
		अणु 0x04, 0xf000 पूर्ण,

		अणु 0x1f, 0x0000 पूर्ण,
		अणु 0x0b, 0x0000 पूर्ण,
		अणु 0x00, 0x9200 पूर्ण
	पूर्ण;

	rtl_ग_लिखोphy_batch(phydev, phy_reg_init);
पूर्ण

अटल व्योम rtl8169sb_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				    काष्ठा phy_device *phydev)
अणु
	phy_ग_लिखो_paged(phydev, 0x0002, 0x01, 0x90d0);
पूर्ण

अटल व्योम rtl8169scd_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा phy_reg phy_reg_init[] = अणु
		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x04, 0x0000 पूर्ण,
		अणु 0x03, 0x00a1 पूर्ण,
		अणु 0x02, 0x0008 पूर्ण,
		अणु 0x01, 0x0120 पूर्ण,
		अणु 0x00, 0x1000 पूर्ण,
		अणु 0x04, 0x0800 पूर्ण,
		अणु 0x04, 0x9000 पूर्ण,
		अणु 0x03, 0x802f पूर्ण,
		अणु 0x02, 0x4f02 पूर्ण,
		अणु 0x01, 0x0409 पूर्ण,
		अणु 0x00, 0xf099 पूर्ण,
		अणु 0x04, 0x9800 पूर्ण,
		अणु 0x04, 0xa000 पूर्ण,
		अणु 0x03, 0xdf01 पूर्ण,
		अणु 0x02, 0xdf20 पूर्ण,
		अणु 0x01, 0xff95 पूर्ण,
		अणु 0x00, 0xba00 पूर्ण,
		अणु 0x04, 0xa800 पूर्ण,
		अणु 0x04, 0xf000 पूर्ण,
		अणु 0x03, 0xdf01 पूर्ण,
		अणु 0x02, 0xdf20 पूर्ण,
		अणु 0x01, 0x101a पूर्ण,
		अणु 0x00, 0xa0ff पूर्ण,
		अणु 0x04, 0xf800 पूर्ण,
		अणु 0x04, 0x0000 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण,

		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x10, 0xf41b पूर्ण,
		अणु 0x14, 0xfb54 पूर्ण,
		अणु 0x18, 0xf5c7 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण,

		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x17, 0x0cc0 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण
	पूर्ण;

	rtl_ग_लिखोphy_batch(phydev, phy_reg_init);
पूर्ण

अटल व्योम rtl8169sce_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा phy_reg phy_reg_init[] = अणु
		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x04, 0x0000 पूर्ण,
		अणु 0x03, 0x00a1 पूर्ण,
		अणु 0x02, 0x0008 पूर्ण,
		अणु 0x01, 0x0120 पूर्ण,
		अणु 0x00, 0x1000 पूर्ण,
		अणु 0x04, 0x0800 पूर्ण,
		अणु 0x04, 0x9000 पूर्ण,
		अणु 0x03, 0x802f पूर्ण,
		अणु 0x02, 0x4f02 पूर्ण,
		अणु 0x01, 0x0409 पूर्ण,
		अणु 0x00, 0xf099 पूर्ण,
		अणु 0x04, 0x9800 पूर्ण,
		अणु 0x04, 0xa000 पूर्ण,
		अणु 0x03, 0xdf01 पूर्ण,
		अणु 0x02, 0xdf20 पूर्ण,
		अणु 0x01, 0xff95 पूर्ण,
		अणु 0x00, 0xba00 पूर्ण,
		अणु 0x04, 0xa800 पूर्ण,
		अणु 0x04, 0xf000 पूर्ण,
		अणु 0x03, 0xdf01 पूर्ण,
		अणु 0x02, 0xdf20 पूर्ण,
		अणु 0x01, 0x101a पूर्ण,
		अणु 0x00, 0xa0ff पूर्ण,
		अणु 0x04, 0xf800 पूर्ण,
		अणु 0x04, 0x0000 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण,

		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x0b, 0x8480 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण,

		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x18, 0x67c7 पूर्ण,
		अणु 0x04, 0x2000 पूर्ण,
		अणु 0x03, 0x002f पूर्ण,
		अणु 0x02, 0x4360 पूर्ण,
		अणु 0x01, 0x0109 पूर्ण,
		अणु 0x00, 0x3022 पूर्ण,
		अणु 0x04, 0x2800 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण,

		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x17, 0x0cc0 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण
	पूर्ण;

	rtl_ग_लिखोphy_batch(phydev, phy_reg_init);
पूर्ण

अटल व्योम rtl8168bb_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				    काष्ठा phy_device *phydev)
अणु
	phy_ग_लिखो(phydev, 0x1f, 0x0001);
	phy_set_bits(phydev, 0x16, BIT(0));
	phy_ग_लिखो(phydev, 0x10, 0xf41b);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);
पूर्ण

अटल व्योम rtl8168bef_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	phy_ग_लिखो_paged(phydev, 0x0001, 0x10, 0xf41b);
पूर्ण

अटल व्योम rtl8168cp_1_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				      काष्ठा phy_device *phydev)
अणु
	phy_ग_लिखो(phydev, 0x1d, 0x0f00);
	phy_ग_लिखो_paged(phydev, 0x0002, 0x0c, 0x1ec8);
पूर्ण

अटल व्योम rtl8168cp_2_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				      काष्ठा phy_device *phydev)
अणु
	phy_set_bits(phydev, 0x14, BIT(5));
	phy_set_bits(phydev, 0x0d, BIT(5));
	phy_ग_लिखो_paged(phydev, 0x0001, 0x1d, 0x3d98);
पूर्ण

अटल व्योम rtl8168c_1_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा phy_reg phy_reg_init[] = अणु
		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x12, 0x2300 पूर्ण,
		अणु 0x1f, 0x0002 पूर्ण,
		अणु 0x00, 0x88d4 पूर्ण,
		अणु 0x01, 0x82b1 पूर्ण,
		अणु 0x03, 0x7002 पूर्ण,
		अणु 0x08, 0x9e30 पूर्ण,
		अणु 0x09, 0x01f0 पूर्ण,
		अणु 0x0a, 0x5500 पूर्ण,
		अणु 0x0c, 0x00c8 पूर्ण,
		अणु 0x1f, 0x0003 पूर्ण,
		अणु 0x12, 0xc096 पूर्ण,
		अणु 0x16, 0x000a पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण,
		अणु 0x09, 0x2000 पूर्ण,
		अणु 0x09, 0x0000 पूर्ण
	पूर्ण;

	rtl_ग_लिखोphy_batch(phydev, phy_reg_init);

	phy_set_bits(phydev, 0x14, BIT(5));
	phy_set_bits(phydev, 0x0d, BIT(5));
पूर्ण

अटल व्योम rtl8168c_2_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा phy_reg phy_reg_init[] = अणु
		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x12, 0x2300 पूर्ण,
		अणु 0x03, 0x802f पूर्ण,
		अणु 0x02, 0x4f02 पूर्ण,
		अणु 0x01, 0x0409 पूर्ण,
		अणु 0x00, 0xf099 पूर्ण,
		अणु 0x04, 0x9800 पूर्ण,
		अणु 0x04, 0x9000 पूर्ण,
		अणु 0x1d, 0x3d98 पूर्ण,
		अणु 0x1f, 0x0002 पूर्ण,
		अणु 0x0c, 0x7eb8 पूर्ण,
		अणु 0x06, 0x0761 पूर्ण,
		अणु 0x1f, 0x0003 पूर्ण,
		अणु 0x16, 0x0f0a पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण
	पूर्ण;

	rtl_ग_लिखोphy_batch(phydev, phy_reg_init);

	phy_set_bits(phydev, 0x16, BIT(0));
	phy_set_bits(phydev, 0x14, BIT(5));
	phy_set_bits(phydev, 0x0d, BIT(5));
पूर्ण

अटल व्योम rtl8168c_3_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा phy_reg phy_reg_init[] = अणु
		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x12, 0x2300 पूर्ण,
		अणु 0x1d, 0x3d98 पूर्ण,
		अणु 0x1f, 0x0002 पूर्ण,
		अणु 0x0c, 0x7eb8 पूर्ण,
		अणु 0x06, 0x5461 पूर्ण,
		अणु 0x1f, 0x0003 पूर्ण,
		अणु 0x16, 0x0f0a पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण
	पूर्ण;

	rtl_ग_लिखोphy_batch(phydev, phy_reg_init);

	phy_set_bits(phydev, 0x16, BIT(0));
	phy_set_bits(phydev, 0x14, BIT(5));
	phy_set_bits(phydev, 0x0d, BIT(5));
पूर्ण

अटल स्थिर काष्ठा phy_reg rtl8168d_1_phy_reg_init_0[] = अणु
	/* Channel Estimation */
	अणु 0x1f, 0x0001 पूर्ण,
	अणु 0x06, 0x4064 पूर्ण,
	अणु 0x07, 0x2863 पूर्ण,
	अणु 0x08, 0x059c पूर्ण,
	अणु 0x09, 0x26b4 पूर्ण,
	अणु 0x0a, 0x6a19 पूर्ण,
	अणु 0x0b, 0xdcc8 पूर्ण,
	अणु 0x10, 0xf06d पूर्ण,
	अणु 0x14, 0x7f68 पूर्ण,
	अणु 0x18, 0x7fd9 पूर्ण,
	अणु 0x1c, 0xf0ff पूर्ण,
	अणु 0x1d, 0x3d9c पूर्ण,
	अणु 0x1f, 0x0003 पूर्ण,
	अणु 0x12, 0xf49f पूर्ण,
	अणु 0x13, 0x070b पूर्ण,
	अणु 0x1a, 0x05ad पूर्ण,
	अणु 0x14, 0x94c0 पूर्ण,

	/*
	 * Tx Error Issue
	 * Enhance line driver घातer
	 */
	अणु 0x1f, 0x0002 पूर्ण,
	अणु 0x06, 0x5561 पूर्ण,
	अणु 0x1f, 0x0005 पूर्ण,
	अणु 0x05, 0x8332 पूर्ण,
	अणु 0x06, 0x5561 पूर्ण,

	/*
	 * Can not link to 1Gbps with bad cable
	 * Decrease SNR threshold क्रमm 21.07dB to 19.04dB
	 */
	अणु 0x1f, 0x0001 पूर्ण,
	अणु 0x17, 0x0cc0 पूर्ण,

	अणु 0x1f, 0x0000 पूर्ण,
	अणु 0x0d, 0xf880 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा phy_reg rtl8168d_1_phy_reg_init_1[] = अणु
	अणु 0x1f, 0x0002 पूर्ण,
	अणु 0x05, 0x669a पूर्ण,
	अणु 0x1f, 0x0005 पूर्ण,
	अणु 0x05, 0x8330 पूर्ण,
	अणु 0x06, 0x669a पूर्ण,
	अणु 0x1f, 0x0002 पूर्ण
पूर्ण;

अटल व्योम rtl8168d_apply_firmware_cond(काष्ठा rtl8169_निजी *tp,
					 काष्ठा phy_device *phydev,
					 u16 val)
अणु
	u16 reg_val;

	phy_ग_लिखो(phydev, 0x1f, 0x0005);
	phy_ग_लिखो(phydev, 0x05, 0x001b);
	reg_val = phy_पढ़ो(phydev, 0x06);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	अगर (reg_val != val)
		phydev_warn(phydev, "chipset not ready for firmware\n");
	अन्यथा
		r8169_apply_firmware(tp);
पूर्ण

अटल व्योम rtl8168d_1_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	rtl_ग_लिखोphy_batch(phydev, rtl8168d_1_phy_reg_init_0);

	/*
	 * Rx Error Issue
	 * Fine Tune Switching regulator parameter
	 */
	phy_ग_लिखो(phydev, 0x1f, 0x0002);
	phy_modअगरy(phydev, 0x0b, 0x00ef, 0x0010);
	phy_modअगरy(phydev, 0x0c, 0x5d00, 0xa200);

	अगर (rtl8168d_efuse_पढ़ो(tp, 0x01) == 0xb1) अणु
		पूर्णांक val;

		rtl_ग_लिखोphy_batch(phydev, rtl8168d_1_phy_reg_init_1);

		val = phy_पढ़ो(phydev, 0x0d);

		अगर ((val & 0x00ff) != 0x006c) अणु
			अटल स्थिर u32 set[] = अणु
				0x0065, 0x0066, 0x0067, 0x0068,
				0x0069, 0x006a, 0x006b, 0x006c
			पूर्ण;
			पूर्णांक i;

			phy_ग_लिखो(phydev, 0x1f, 0x0002);

			val &= 0xff00;
			क्रम (i = 0; i < ARRAY_SIZE(set); i++)
				phy_ग_लिखो(phydev, 0x0d, val | set[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		phy_ग_लिखो_paged(phydev, 0x0002, 0x05, 0x6662);
		r8168d_phy_param(phydev, 0x8330, 0xffff, 0x6662);
	पूर्ण

	/* RSET couple improve */
	phy_ग_लिखो(phydev, 0x1f, 0x0002);
	phy_set_bits(phydev, 0x0d, 0x0300);
	phy_set_bits(phydev, 0x0f, 0x0010);

	/* Fine tune PLL perक्रमmance */
	phy_ग_लिखो(phydev, 0x1f, 0x0002);
	phy_modअगरy(phydev, 0x02, 0x0600, 0x0100);
	phy_clear_bits(phydev, 0x03, 0xe000);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	rtl8168d_apply_firmware_cond(tp, phydev, 0xbf00);
पूर्ण

अटल व्योम rtl8168d_2_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	rtl_ग_लिखोphy_batch(phydev, rtl8168d_1_phy_reg_init_0);

	अगर (rtl8168d_efuse_पढ़ो(tp, 0x01) == 0xb1) अणु
		पूर्णांक val;

		rtl_ग_लिखोphy_batch(phydev, rtl8168d_1_phy_reg_init_1);

		val = phy_पढ़ो(phydev, 0x0d);
		अगर ((val & 0x00ff) != 0x006c) अणु
			अटल स्थिर u32 set[] = अणु
				0x0065, 0x0066, 0x0067, 0x0068,
				0x0069, 0x006a, 0x006b, 0x006c
			पूर्ण;
			पूर्णांक i;

			phy_ग_लिखो(phydev, 0x1f, 0x0002);

			val &= 0xff00;
			क्रम (i = 0; i < ARRAY_SIZE(set); i++)
				phy_ग_लिखो(phydev, 0x0d, val | set[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		phy_ग_लिखो_paged(phydev, 0x0002, 0x05, 0x2642);
		r8168d_phy_param(phydev, 0x8330, 0xffff, 0x2642);
	पूर्ण

	/* Fine tune PLL perक्रमmance */
	phy_ग_लिखो(phydev, 0x1f, 0x0002);
	phy_modअगरy(phydev, 0x02, 0x0600, 0x0100);
	phy_clear_bits(phydev, 0x03, 0xe000);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	/* Switching regulator Slew rate */
	phy_modअगरy_paged(phydev, 0x0002, 0x0f, 0x0000, 0x0017);

	rtl8168d_apply_firmware_cond(tp, phydev, 0xb300);
पूर्ण

अटल व्योम rtl8168d_3_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा phy_reg phy_reg_init[] = अणु
		अणु 0x1f, 0x0002 पूर्ण,
		अणु 0x10, 0x0008 पूर्ण,
		अणु 0x0d, 0x006c पूर्ण,

		अणु 0x1f, 0x0000 पूर्ण,
		अणु 0x0d, 0xf880 पूर्ण,

		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x17, 0x0cc0 पूर्ण,

		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x0b, 0xa4d8 पूर्ण,
		अणु 0x09, 0x281c पूर्ण,
		अणु 0x07, 0x2883 पूर्ण,
		अणु 0x0a, 0x6b35 पूर्ण,
		अणु 0x1d, 0x3da4 पूर्ण,
		अणु 0x1c, 0xeffd पूर्ण,
		अणु 0x14, 0x7f52 पूर्ण,
		अणु 0x18, 0x7fc6 पूर्ण,
		अणु 0x08, 0x0601 पूर्ण,
		अणु 0x06, 0x4063 पूर्ण,
		अणु 0x10, 0xf074 पूर्ण,
		अणु 0x1f, 0x0003 पूर्ण,
		अणु 0x13, 0x0789 पूर्ण,
		अणु 0x12, 0xf4bd पूर्ण,
		अणु 0x1a, 0x04fd पूर्ण,
		अणु 0x14, 0x84b0 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण,
		अणु 0x00, 0x9200 पूर्ण,

		अणु 0x1f, 0x0005 पूर्ण,
		अणु 0x01, 0x0340 पूर्ण,
		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x04, 0x4000 पूर्ण,
		अणु 0x03, 0x1d21 पूर्ण,
		अणु 0x02, 0x0c32 पूर्ण,
		अणु 0x01, 0x0200 पूर्ण,
		अणु 0x00, 0x5554 पूर्ण,
		अणु 0x04, 0x4800 पूर्ण,
		अणु 0x04, 0x4000 पूर्ण,
		अणु 0x04, 0xf000 पूर्ण,
		अणु 0x03, 0xdf01 पूर्ण,
		अणु 0x02, 0xdf20 पूर्ण,
		अणु 0x01, 0x101a पूर्ण,
		अणु 0x00, 0xa0ff पूर्ण,
		अणु 0x04, 0xf800 पूर्ण,
		अणु 0x04, 0xf000 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण,
	पूर्ण;

	rtl_ग_लिखोphy_batch(phydev, phy_reg_init);
	r8168d_modअगरy_extpage(phydev, 0x0023, 0x16, 0xffff, 0x0000);
पूर्ण

अटल व्योम rtl8168d_4_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	phy_ग_लिखो_paged(phydev, 0x0001, 0x17, 0x0cc0);
	r8168d_modअगरy_extpage(phydev, 0x002d, 0x18, 0xffff, 0x0040);
	phy_set_bits(phydev, 0x0d, BIT(5));
पूर्ण

अटल व्योम rtl8168e_1_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा phy_reg phy_reg_init[] = अणु
		/* Channel estimation fine tune */
		अणु 0x1f, 0x0001 पूर्ण,
		अणु 0x0b, 0x6c20 पूर्ण,
		अणु 0x07, 0x2872 पूर्ण,
		अणु 0x1c, 0xefff पूर्ण,
		अणु 0x1f, 0x0003 पूर्ण,
		अणु 0x14, 0x6420 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण,
	पूर्ण;

	r8169_apply_firmware(tp);

	/* Enable Delay cap */
	r8168d_phy_param(phydev, 0x8b80, 0xffff, 0xc896);

	rtl_ग_लिखोphy_batch(phydev, phy_reg_init);

	/* Update PFM & 10M TX idle समयr */
	r8168d_modअगरy_extpage(phydev, 0x002f, 0x15, 0xffff, 0x1919);

	r8168d_modअगरy_extpage(phydev, 0x00ac, 0x18, 0xffff, 0x0006);

	/* DCO enable क्रम 10M IDLE Power */
	r8168d_modअगरy_extpage(phydev, 0x0023, 0x17, 0x0000, 0x0006);

	/* For impedance matching */
	phy_modअगरy_paged(phydev, 0x0002, 0x08, 0x7f00, 0x8000);

	/* PHY स्वतः speed करोwn */
	r8168d_modअगरy_extpage(phydev, 0x002d, 0x18, 0x0000, 0x0050);
	phy_set_bits(phydev, 0x14, BIT(15));

	r8168d_phy_param(phydev, 0x8b86, 0x0000, 0x0001);
	r8168d_phy_param(phydev, 0x8b85, 0x2000, 0x0000);

	r8168d_modअगरy_extpage(phydev, 0x0020, 0x15, 0x1100, 0x0000);
	phy_ग_लिखो_paged(phydev, 0x0006, 0x00, 0x5a00);

	phy_ग_लिखो_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV, 0x0000);
पूर्ण

अटल व्योम rtl8168e_2_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	r8169_apply_firmware(tp);

	/* Enable Delay cap */
	r8168d_modअगरy_extpage(phydev, 0x00ac, 0x18, 0xffff, 0x0006);

	/* Channel estimation fine tune */
	phy_ग_लिखो_paged(phydev, 0x0003, 0x09, 0xa20f);

	/* Green Setting */
	r8168d_phy_param(phydev, 0x8b5b, 0xffff, 0x9222);
	r8168d_phy_param(phydev, 0x8b6d, 0xffff, 0x8000);
	r8168d_phy_param(phydev, 0x8b76, 0xffff, 0x8000);

	/* For 4-corner perक्रमmance improve */
	phy_ग_लिखो(phydev, 0x1f, 0x0005);
	phy_ग_लिखो(phydev, 0x05, 0x8b80);
	phy_set_bits(phydev, 0x17, 0x0006);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	/* PHY स्वतः speed करोwn */
	r8168d_modअगरy_extpage(phydev, 0x002d, 0x18, 0x0000, 0x0010);
	phy_set_bits(phydev, 0x14, BIT(15));

	/* improve 10M EEE waveक्रमm */
	r8168d_phy_param(phydev, 0x8b86, 0x0000, 0x0001);

	/* Improve 2-pair detection perक्रमmance */
	r8168d_phy_param(phydev, 0x8b85, 0x0000, 0x4000);

	rtl8168f_config_eee_phy(phydev);

	/* Green feature */
	phy_ग_लिखो(phydev, 0x1f, 0x0003);
	phy_set_bits(phydev, 0x19, BIT(0));
	phy_set_bits(phydev, 0x10, BIT(10));
	phy_ग_लिखो(phydev, 0x1f, 0x0000);
	phy_modअगरy_paged(phydev, 0x0005, 0x01, 0, BIT(8));
पूर्ण

अटल व्योम rtl8168f_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				   काष्ठा phy_device *phydev)
अणु
	/* For 4-corner perक्रमmance improve */
	r8168d_phy_param(phydev, 0x8b80, 0x0000, 0x0006);

	/* PHY स्वतः speed करोwn */
	r8168d_modअगरy_extpage(phydev, 0x002d, 0x18, 0x0000, 0x0010);
	phy_set_bits(phydev, 0x14, BIT(15));

	/* Improve 10M EEE waveक्रमm */
	r8168d_phy_param(phydev, 0x8b86, 0x0000, 0x0001);

	rtl8168f_config_eee_phy(phydev);
पूर्ण

अटल व्योम rtl8168f_1_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	r8169_apply_firmware(tp);

	/* Channel estimation fine tune */
	phy_ग_लिखो_paged(phydev, 0x0003, 0x09, 0xa20f);

	/* Modअगरy green table क्रम giga & fnet */
	r8168d_phy_param(phydev, 0x8b55, 0xffff, 0x0000);
	r8168d_phy_param(phydev, 0x8b5e, 0xffff, 0x0000);
	r8168d_phy_param(phydev, 0x8b67, 0xffff, 0x0000);
	r8168d_phy_param(phydev, 0x8b70, 0xffff, 0x0000);
	r8168d_modअगरy_extpage(phydev, 0x0078, 0x17, 0xffff, 0x0000);
	r8168d_modअगरy_extpage(phydev, 0x0078, 0x19, 0xffff, 0x00fb);

	/* Modअगरy green table क्रम 10M */
	r8168d_phy_param(phydev, 0x8b79, 0xffff, 0xaa00);

	/* Disable hiimpedance detection (RTCT) */
	phy_ग_लिखो_paged(phydev, 0x0003, 0x01, 0x328a);

	rtl8168f_hw_phy_config(tp, phydev);

	/* Improve 2-pair detection perक्रमmance */
	r8168d_phy_param(phydev, 0x8b85, 0x0000, 0x4000);
पूर्ण

अटल व्योम rtl8168f_2_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	r8169_apply_firmware(tp);

	rtl8168f_hw_phy_config(tp, phydev);
पूर्ण

अटल व्योम rtl8411_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				  काष्ठा phy_device *phydev)
अणु
	r8169_apply_firmware(tp);

	rtl8168f_hw_phy_config(tp, phydev);

	/* Improve 2-pair detection perक्रमmance */
	r8168d_phy_param(phydev, 0x8b85, 0x0000, 0x4000);

	/* Channel estimation fine tune */
	phy_ग_लिखो_paged(phydev, 0x0003, 0x09, 0xa20f);

	/* Modअगरy green table क्रम giga & fnet */
	r8168d_phy_param(phydev, 0x8b55, 0xffff, 0x0000);
	r8168d_phy_param(phydev, 0x8b5e, 0xffff, 0x0000);
	r8168d_phy_param(phydev, 0x8b67, 0xffff, 0x0000);
	r8168d_phy_param(phydev, 0x8b70, 0xffff, 0x0000);
	r8168d_modअगरy_extpage(phydev, 0x0078, 0x17, 0xffff, 0x0000);
	r8168d_modअगरy_extpage(phydev, 0x0078, 0x19, 0xffff, 0x00aa);

	/* Modअगरy green table क्रम 10M */
	r8168d_phy_param(phydev, 0x8b79, 0xffff, 0xaa00);

	/* Disable hiimpedance detection (RTCT) */
	phy_ग_लिखो_paged(phydev, 0x0003, 0x01, 0x328a);

	/* Modअगरy green table क्रम giga */
	r8168d_phy_param(phydev, 0x8b54, 0x0800, 0x0000);
	r8168d_phy_param(phydev, 0x8b5d, 0x0800, 0x0000);
	r8168d_phy_param(phydev, 0x8a7c, 0x0100, 0x0000);
	r8168d_phy_param(phydev, 0x8a7f, 0x0000, 0x0100);
	r8168d_phy_param(phydev, 0x8a82, 0x0100, 0x0000);
	r8168d_phy_param(phydev, 0x8a85, 0x0100, 0x0000);
	r8168d_phy_param(phydev, 0x8a88, 0x0100, 0x0000);

	/* uc same-seed solution */
	r8168d_phy_param(phydev, 0x8b85, 0x0000, 0x8000);

	/* Green feature */
	phy_ग_लिखो(phydev, 0x1f, 0x0003);
	phy_clear_bits(phydev, 0x19, BIT(0));
	phy_clear_bits(phydev, 0x10, BIT(10));
	phy_ग_लिखो(phydev, 0x1f, 0x0000);
पूर्ण

अटल व्योम rtl8168g_disable_aldps(काष्ठा phy_device *phydev)
अणु
	phy_modअगरy_paged(phydev, 0x0a43, 0x10, BIT(2), 0);
पूर्ण

अटल व्योम rtl8168g_enable_gphy_10m(काष्ठा phy_device *phydev)
अणु
	phy_modअगरy_paged(phydev, 0x0a44, 0x11, 0, BIT(11));
पूर्ण

अटल व्योम rtl8168g_phy_adjust_10m_aldps(काष्ठा phy_device *phydev)
अणु
	phy_modअगरy_paged(phydev, 0x0bcc, 0x14, BIT(8), 0);
	phy_modअगरy_paged(phydev, 0x0a44, 0x11, 0, BIT(7) | BIT(6));
	r8168g_phy_param(phydev, 0x8084, 0x6000, 0x0000);
	phy_modअगरy_paged(phydev, 0x0a43, 0x10, 0x0000, 0x1003);
पूर्ण

अटल व्योम rtl8168g_1_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	r8169_apply_firmware(tp);

	ret = phy_पढ़ो_paged(phydev, 0x0a46, 0x10);
	अगर (ret & BIT(8))
		phy_modअगरy_paged(phydev, 0x0bcc, 0x12, BIT(15), 0);
	अन्यथा
		phy_modअगरy_paged(phydev, 0x0bcc, 0x12, 0, BIT(15));

	ret = phy_पढ़ो_paged(phydev, 0x0a46, 0x13);
	अगर (ret & BIT(8))
		phy_modअगरy_paged(phydev, 0x0c41, 0x15, 0, BIT(1));
	अन्यथा
		phy_modअगरy_paged(phydev, 0x0c41, 0x15, BIT(1), 0);

	/* Enable PHY स्वतः speed करोwn */
	phy_modअगरy_paged(phydev, 0x0a44, 0x11, 0, BIT(3) | BIT(2));

	rtl8168g_phy_adjust_10m_aldps(phydev);

	/* EEE स्वतः-fallback function */
	phy_modअगरy_paged(phydev, 0x0a4b, 0x11, 0, BIT(2));

	/* Enable UC LPF tune function */
	r8168g_phy_param(phydev, 0x8012, 0x0000, 0x8000);

	phy_modअगरy_paged(phydev, 0x0c42, 0x11, BIT(13), BIT(14));

	/* Improve SWR Efficiency */
	phy_ग_लिखो(phydev, 0x1f, 0x0bcd);
	phy_ग_लिखो(phydev, 0x14, 0x5065);
	phy_ग_लिखो(phydev, 0x14, 0xd065);
	phy_ग_लिखो(phydev, 0x1f, 0x0bc8);
	phy_ग_लिखो(phydev, 0x11, 0x5655);
	phy_ग_लिखो(phydev, 0x1f, 0x0bcd);
	phy_ग_लिखो(phydev, 0x14, 0x1065);
	phy_ग_लिखो(phydev, 0x14, 0x9065);
	phy_ग_लिखो(phydev, 0x14, 0x1065);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	rtl8168g_disable_aldps(phydev);
	rtl8168g_config_eee_phy(phydev);
पूर्ण

अटल व्योम rtl8168g_2_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	r8169_apply_firmware(tp);
	rtl8168g_config_eee_phy(phydev);
पूर्ण

अटल व्योम rtl8168h_1_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	u16 करोut_tapbin;
	u32 data;

	r8169_apply_firmware(tp);

	/* CHN EST parameters adjust - giga master */
	r8168g_phy_param(phydev, 0x809b, 0xf800, 0x8000);
	r8168g_phy_param(phydev, 0x80a2, 0xff00, 0x8000);
	r8168g_phy_param(phydev, 0x80a4, 0xff00, 0x8500);
	r8168g_phy_param(phydev, 0x809c, 0xff00, 0xbd00);

	/* CHN EST parameters adjust - giga slave */
	r8168g_phy_param(phydev, 0x80ad, 0xf800, 0x7000);
	r8168g_phy_param(phydev, 0x80b4, 0xff00, 0x5000);
	r8168g_phy_param(phydev, 0x80ac, 0xff00, 0x4000);

	/* CHN EST parameters adjust - fnet */
	r8168g_phy_param(phydev, 0x808e, 0xff00, 0x1200);
	r8168g_phy_param(phydev, 0x8090, 0xff00, 0xe500);
	r8168g_phy_param(phydev, 0x8092, 0xff00, 0x9f00);

	/* enable R-tune & PGA-retune function */
	करोut_tapbin = 0;
	data = phy_पढ़ो_paged(phydev, 0x0a46, 0x13);
	data &= 3;
	data <<= 2;
	करोut_tapbin |= data;
	data = phy_पढ़ो_paged(phydev, 0x0a46, 0x12);
	data &= 0xc000;
	data >>= 14;
	करोut_tapbin |= data;
	करोut_tapbin = ~(करोut_tapbin ^ 0x08);
	करोut_tapbin <<= 12;
	करोut_tapbin &= 0xf000;

	r8168g_phy_param(phydev, 0x827a, 0xf000, करोut_tapbin);
	r8168g_phy_param(phydev, 0x827b, 0xf000, करोut_tapbin);
	r8168g_phy_param(phydev, 0x827c, 0xf000, करोut_tapbin);
	r8168g_phy_param(phydev, 0x827d, 0xf000, करोut_tapbin);
	r8168g_phy_param(phydev, 0x0811, 0x0000, 0x0800);
	phy_modअगरy_paged(phydev, 0x0a42, 0x16, 0x0000, 0x0002);

	rtl8168g_enable_gphy_10m(phydev);

	/* SAR ADC perक्रमmance */
	phy_modअगरy_paged(phydev, 0x0bca, 0x17, BIT(12) | BIT(13), BIT(14));

	r8168g_phy_param(phydev, 0x803f, 0x3000, 0x0000);
	r8168g_phy_param(phydev, 0x8047, 0x3000, 0x0000);
	r8168g_phy_param(phydev, 0x804f, 0x3000, 0x0000);
	r8168g_phy_param(phydev, 0x8057, 0x3000, 0x0000);
	r8168g_phy_param(phydev, 0x805f, 0x3000, 0x0000);
	r8168g_phy_param(phydev, 0x8067, 0x3000, 0x0000);
	r8168g_phy_param(phydev, 0x806f, 0x3000, 0x0000);

	/* disable phy pfm mode */
	phy_modअगरy_paged(phydev, 0x0a44, 0x11, BIT(7), 0);

	rtl8168g_disable_aldps(phydev);
	rtl8168h_config_eee_phy(phydev);
पूर्ण

अटल व्योम rtl8168h_2_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	u16 ioffset, rlen;
	u32 data;

	r8169_apply_firmware(tp);

	/* CHIN EST parameter update */
	r8168g_phy_param(phydev, 0x808a, 0x003f, 0x000a);

	/* enable R-tune & PGA-retune function */
	r8168g_phy_param(phydev, 0x0811, 0x0000, 0x0800);
	phy_modअगरy_paged(phydev, 0x0a42, 0x16, 0x0000, 0x0002);

	rtl8168g_enable_gphy_10m(phydev);

	ioffset = rtl8168h_2_get_adc_bias_ioffset(tp);
	अगर (ioffset != 0xffff)
		phy_ग_लिखो_paged(phydev, 0x0bcf, 0x16, ioffset);

	/* Modअगरy rlen (TX LPF corner frequency) level */
	data = phy_पढ़ो_paged(phydev, 0x0bcd, 0x16);
	data &= 0x000f;
	rlen = 0;
	अगर (data > 3)
		rlen = data - 3;
	data = rlen | (rlen << 4) | (rlen << 8) | (rlen << 12);
	phy_ग_लिखो_paged(phydev, 0x0bcd, 0x17, data);

	/* disable phy pfm mode */
	phy_modअगरy_paged(phydev, 0x0a44, 0x11, BIT(7), 0);

	rtl8168g_disable_aldps(phydev);
	rtl8168g_config_eee_phy(phydev);
पूर्ण

अटल व्योम rtl8168ep_1_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				      काष्ठा phy_device *phydev)
अणु
	/* Enable PHY स्वतः speed करोwn */
	phy_modअगरy_paged(phydev, 0x0a44, 0x11, 0, BIT(3) | BIT(2));

	rtl8168g_phy_adjust_10m_aldps(phydev);

	/* Enable EEE स्वतः-fallback function */
	phy_modअगरy_paged(phydev, 0x0a4b, 0x11, 0, BIT(2));

	/* Enable UC LPF tune function */
	r8168g_phy_param(phydev, 0x8012, 0x0000, 0x8000);

	/* set rg_sel_sdm_rate */
	phy_modअगरy_paged(phydev, 0x0c42, 0x11, BIT(13), BIT(14));

	rtl8168g_disable_aldps(phydev);
	rtl8168g_config_eee_phy(phydev);
पूर्ण

अटल व्योम rtl8168ep_2_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				      काष्ठा phy_device *phydev)
अणु
	rtl8168g_phy_adjust_10m_aldps(phydev);

	/* Enable UC LPF tune function */
	r8168g_phy_param(phydev, 0x8012, 0x0000, 0x8000);

	/* Set rg_sel_sdm_rate */
	phy_modअगरy_paged(phydev, 0x0c42, 0x11, BIT(13), BIT(14));

	/* Channel estimation parameters */
	r8168g_phy_param(phydev, 0x80f3, 0xff00, 0x8b00);
	r8168g_phy_param(phydev, 0x80f0, 0xff00, 0x3a00);
	r8168g_phy_param(phydev, 0x80ef, 0xff00, 0x0500);
	r8168g_phy_param(phydev, 0x80f6, 0xff00, 0x6e00);
	r8168g_phy_param(phydev, 0x80ec, 0xff00, 0x6800);
	r8168g_phy_param(phydev, 0x80ed, 0xff00, 0x7c00);
	r8168g_phy_param(phydev, 0x80f2, 0xff00, 0xf400);
	r8168g_phy_param(phydev, 0x80f4, 0xff00, 0x8500);
	r8168g_phy_param(phydev, 0x8110, 0xff00, 0xa800);
	r8168g_phy_param(phydev, 0x810f, 0xff00, 0x1d00);
	r8168g_phy_param(phydev, 0x8111, 0xff00, 0xf500);
	r8168g_phy_param(phydev, 0x8113, 0xff00, 0x6100);
	r8168g_phy_param(phydev, 0x8115, 0xff00, 0x9200);
	r8168g_phy_param(phydev, 0x810e, 0xff00, 0x0400);
	r8168g_phy_param(phydev, 0x810c, 0xff00, 0x7c00);
	r8168g_phy_param(phydev, 0x810b, 0xff00, 0x5a00);
	r8168g_phy_param(phydev, 0x80d1, 0xff00, 0xff00);
	r8168g_phy_param(phydev, 0x80cd, 0xff00, 0x9e00);
	r8168g_phy_param(phydev, 0x80d3, 0xff00, 0x0e00);
	r8168g_phy_param(phydev, 0x80d5, 0xff00, 0xca00);
	r8168g_phy_param(phydev, 0x80d7, 0xff00, 0x8400);

	/* Force PWM-mode */
	phy_ग_लिखो(phydev, 0x1f, 0x0bcd);
	phy_ग_लिखो(phydev, 0x14, 0x5065);
	phy_ग_लिखो(phydev, 0x14, 0xd065);
	phy_ग_लिखो(phydev, 0x1f, 0x0bc8);
	phy_ग_लिखो(phydev, 0x12, 0x00ed);
	phy_ग_लिखो(phydev, 0x1f, 0x0bcd);
	phy_ग_लिखो(phydev, 0x14, 0x1065);
	phy_ग_लिखो(phydev, 0x14, 0x9065);
	phy_ग_लिखो(phydev, 0x14, 0x1065);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	rtl8168g_disable_aldps(phydev);
	rtl8168g_config_eee_phy(phydev);
पूर्ण

अटल व्योम rtl8117_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				  काष्ठा phy_device *phydev)
अणु
	/* CHN EST parameters adjust - fnet */
	r8168g_phy_param(phydev, 0x808e, 0xff00, 0x4800);
	r8168g_phy_param(phydev, 0x8090, 0xff00, 0xcc00);
	r8168g_phy_param(phydev, 0x8092, 0xff00, 0xb000);

	r8168g_phy_param(phydev, 0x8088, 0xff00, 0x6000);
	r8168g_phy_param(phydev, 0x808b, 0x3f00, 0x0b00);
	r8168g_phy_param(phydev, 0x808d, 0x1f00, 0x0600);
	r8168g_phy_param(phydev, 0x808c, 0xff00, 0xb000);
	r8168g_phy_param(phydev, 0x80a0, 0xff00, 0x2800);
	r8168g_phy_param(phydev, 0x80a2, 0xff00, 0x5000);
	r8168g_phy_param(phydev, 0x809b, 0xf800, 0xb000);
	r8168g_phy_param(phydev, 0x809a, 0xff00, 0x4b00);
	r8168g_phy_param(phydev, 0x809d, 0x3f00, 0x0800);
	r8168g_phy_param(phydev, 0x80a1, 0xff00, 0x7000);
	r8168g_phy_param(phydev, 0x809f, 0x1f00, 0x0300);
	r8168g_phy_param(phydev, 0x809e, 0xff00, 0x8800);
	r8168g_phy_param(phydev, 0x80b2, 0xff00, 0x2200);
	r8168g_phy_param(phydev, 0x80ad, 0xf800, 0x9800);
	r8168g_phy_param(phydev, 0x80af, 0x3f00, 0x0800);
	r8168g_phy_param(phydev, 0x80b3, 0xff00, 0x6f00);
	r8168g_phy_param(phydev, 0x80b1, 0x1f00, 0x0300);
	r8168g_phy_param(phydev, 0x80b0, 0xff00, 0x9300);

	r8168g_phy_param(phydev, 0x8011, 0x0000, 0x0800);

	rtl8168g_enable_gphy_10m(phydev);

	r8168g_phy_param(phydev, 0x8016, 0x0000, 0x0400);

	rtl8168g_disable_aldps(phydev);
	rtl8168h_config_eee_phy(phydev);
पूर्ण

अटल व्योम rtl8102e_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				   काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा phy_reg phy_reg_init[] = अणु
		अणु 0x1f, 0x0003 पूर्ण,
		अणु 0x08, 0x441d पूर्ण,
		अणु 0x01, 0x9100 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण
	पूर्ण;

	phy_set_bits(phydev, 0x11, BIT(12));
	phy_set_bits(phydev, 0x19, BIT(13));
	phy_set_bits(phydev, 0x10, BIT(15));

	rtl_ग_लिखोphy_batch(phydev, phy_reg_init);
पूर्ण

अटल व्योम rtl8401_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				  काष्ठा phy_device *phydev)
अणु
	phy_set_bits(phydev, 0x11, BIT(12));
	phy_modअगरy_paged(phydev, 0x0002, 0x0f, 0x0000, 0x0003);
पूर्ण

अटल व्योम rtl8105e_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				   काष्ठा phy_device *phydev)
अणु
	/* Disable ALDPS beक्रमe ram code */
	phy_ग_लिखो(phydev, 0x18, 0x0310);
	msleep(100);

	r8169_apply_firmware(tp);

	phy_ग_लिखो_paged(phydev, 0x0005, 0x1a, 0x0000);
	phy_ग_लिखो_paged(phydev, 0x0004, 0x1c, 0x0000);
	phy_ग_लिखो_paged(phydev, 0x0001, 0x15, 0x7701);
पूर्ण

अटल व्योम rtl8402_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				  काष्ठा phy_device *phydev)
अणु
	/* Disable ALDPS beक्रमe setting firmware */
	phy_ग_लिखो(phydev, 0x18, 0x0310);
	msleep(20);

	r8169_apply_firmware(tp);

	/* EEE setting */
	phy_ग_लिखो(phydev, 0x1f, 0x0004);
	phy_ग_लिखो(phydev, 0x10, 0x401f);
	phy_ग_लिखो(phydev, 0x19, 0x7030);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);
पूर्ण

अटल व्योम rtl8106e_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				   काष्ठा phy_device *phydev)
अणु
	अटल स्थिर काष्ठा phy_reg phy_reg_init[] = अणु
		अणु 0x1f, 0x0004 पूर्ण,
		अणु 0x10, 0xc07f पूर्ण,
		अणु 0x19, 0x7030 पूर्ण,
		अणु 0x1f, 0x0000 पूर्ण
	पूर्ण;

	/* Disable ALDPS beक्रमe ram code */
	phy_ग_लिखो(phydev, 0x18, 0x0310);
	msleep(100);

	r8169_apply_firmware(tp);

	rtl_ग_लिखोphy_batch(phydev, phy_reg_init);
पूर्ण

अटल व्योम rtl8125_legacy_क्रमce_mode(काष्ठा phy_device *phydev)
अणु
	phy_modअगरy_paged(phydev, 0xa5b, 0x12, BIT(15), 0);
पूर्ण

अटल व्योम rtl8125a_1_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	phy_modअगरy_paged(phydev, 0xad4, 0x10, 0x03ff, 0x0084);
	phy_modअगरy_paged(phydev, 0xad4, 0x17, 0x0000, 0x0010);
	phy_modअगरy_paged(phydev, 0xad1, 0x13, 0x03ff, 0x0006);
	phy_modअगरy_paged(phydev, 0xad3, 0x11, 0x003f, 0x0006);
	phy_modअगरy_paged(phydev, 0xac0, 0x14, 0x0000, 0x1100);
	phy_modअगरy_paged(phydev, 0xac8, 0x15, 0xf000, 0x7000);
	phy_modअगरy_paged(phydev, 0xad1, 0x14, 0x0000, 0x0400);
	phy_modअगरy_paged(phydev, 0xad1, 0x15, 0x0000, 0x03ff);
	phy_modअगरy_paged(phydev, 0xad1, 0x16, 0x0000, 0x03ff);

	r8168g_phy_param(phydev, 0x80ea, 0xff00, 0xc400);
	r8168g_phy_param(phydev, 0x80eb, 0x0700, 0x0300);
	r8168g_phy_param(phydev, 0x80f8, 0xff00, 0x1c00);
	r8168g_phy_param(phydev, 0x80f1, 0xff00, 0x3000);
	r8168g_phy_param(phydev, 0x80fe, 0xff00, 0xa500);
	r8168g_phy_param(phydev, 0x8102, 0xff00, 0x5000);
	r8168g_phy_param(phydev, 0x8105, 0xff00, 0x3300);
	r8168g_phy_param(phydev, 0x8100, 0xff00, 0x7000);
	r8168g_phy_param(phydev, 0x8104, 0xff00, 0xf000);
	r8168g_phy_param(phydev, 0x8106, 0xff00, 0x6500);
	r8168g_phy_param(phydev, 0x80dc, 0xff00, 0xed00);
	r8168g_phy_param(phydev, 0x80df, 0x0000, 0x0100);
	r8168g_phy_param(phydev, 0x80e1, 0x0100, 0x0000);

	phy_modअगरy_paged(phydev, 0xbf0, 0x13, 0x003f, 0x0038);
	r8168g_phy_param(phydev, 0x819f, 0xffff, 0xd0b6);

	phy_ग_लिखो_paged(phydev, 0xbc3, 0x12, 0x5555);
	phy_modअगरy_paged(phydev, 0xbf0, 0x15, 0x0e00, 0x0a00);
	phy_modअगरy_paged(phydev, 0xa5c, 0x10, 0x0400, 0x0000);
	rtl8168g_enable_gphy_10m(phydev);

	rtl8125a_config_eee_phy(phydev);
पूर्ण

अटल व्योम rtl8125a_2_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				     काष्ठा phy_device *phydev)
अणु
	पूर्णांक i;

	phy_modअगरy_paged(phydev, 0xad4, 0x17, 0x0000, 0x0010);
	phy_modअगरy_paged(phydev, 0xad1, 0x13, 0x03ff, 0x03ff);
	phy_modअगरy_paged(phydev, 0xad3, 0x11, 0x003f, 0x0006);
	phy_modअगरy_paged(phydev, 0xac0, 0x14, 0x1100, 0x0000);
	phy_modअगरy_paged(phydev, 0xacc, 0x10, 0x0003, 0x0002);
	phy_modअगरy_paged(phydev, 0xad4, 0x10, 0x00e7, 0x0044);
	phy_modअगरy_paged(phydev, 0xac1, 0x12, 0x0080, 0x0000);
	phy_modअगरy_paged(phydev, 0xac8, 0x10, 0x0300, 0x0000);
	phy_modअगरy_paged(phydev, 0xac5, 0x17, 0x0007, 0x0002);
	phy_ग_लिखो_paged(phydev, 0xad4, 0x16, 0x00a8);
	phy_ग_लिखो_paged(phydev, 0xac5, 0x16, 0x01ff);
	phy_modअगरy_paged(phydev, 0xac8, 0x15, 0x00f0, 0x0030);

	phy_ग_लिखो(phydev, 0x1f, 0x0b87);
	phy_ग_लिखो(phydev, 0x16, 0x80a2);
	phy_ग_लिखो(phydev, 0x17, 0x0153);
	phy_ग_लिखो(phydev, 0x16, 0x809c);
	phy_ग_लिखो(phydev, 0x17, 0x0153);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	phy_ग_लिखो(phydev, 0x1f, 0x0a43);
	phy_ग_लिखो(phydev, 0x13, 0x81B3);
	phy_ग_लिखो(phydev, 0x14, 0x0043);
	phy_ग_लिखो(phydev, 0x14, 0x00A7);
	phy_ग_लिखो(phydev, 0x14, 0x00D6);
	phy_ग_लिखो(phydev, 0x14, 0x00EC);
	phy_ग_लिखो(phydev, 0x14, 0x00F6);
	phy_ग_लिखो(phydev, 0x14, 0x00FB);
	phy_ग_लिखो(phydev, 0x14, 0x00FD);
	phy_ग_लिखो(phydev, 0x14, 0x00FF);
	phy_ग_लिखो(phydev, 0x14, 0x00BB);
	phy_ग_लिखो(phydev, 0x14, 0x0058);
	phy_ग_लिखो(phydev, 0x14, 0x0029);
	phy_ग_लिखो(phydev, 0x14, 0x0013);
	phy_ग_लिखो(phydev, 0x14, 0x0009);
	phy_ग_लिखो(phydev, 0x14, 0x0004);
	phy_ग_लिखो(phydev, 0x14, 0x0002);
	क्रम (i = 0; i < 25; i++)
		phy_ग_लिखो(phydev, 0x14, 0x0000);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	r8168g_phy_param(phydev, 0x8257, 0xffff, 0x020F);
	r8168g_phy_param(phydev, 0x80ea, 0xffff, 0x7843);

	r8169_apply_firmware(tp);

	phy_modअगरy_paged(phydev, 0xd06, 0x14, 0x0000, 0x2000);

	r8168g_phy_param(phydev, 0x81a2, 0x0000, 0x0100);

	phy_modअगरy_paged(phydev, 0xb54, 0x16, 0xff00, 0xdb00);
	phy_modअगरy_paged(phydev, 0xa45, 0x12, 0x0001, 0x0000);
	phy_modअगरy_paged(phydev, 0xa5d, 0x12, 0x0000, 0x0020);
	phy_modअगरy_paged(phydev, 0xad4, 0x17, 0x0010, 0x0000);
	phy_modअगरy_paged(phydev, 0xa86, 0x15, 0x0001, 0x0000);
	rtl8168g_enable_gphy_10m(phydev);

	rtl8125a_config_eee_phy(phydev);
पूर्ण

अटल व्योम rtl8125b_hw_phy_config(काष्ठा rtl8169_निजी *tp,
				   काष्ठा phy_device *phydev)
अणु
	r8169_apply_firmware(tp);

	phy_modअगरy_paged(phydev, 0xa44, 0x11, 0x0000, 0x0800);
	phy_modअगरy_paged(phydev, 0xac4, 0x13, 0x00f0, 0x0090);
	phy_modअगरy_paged(phydev, 0xad3, 0x10, 0x0003, 0x0001);

	phy_ग_लिखो(phydev, 0x1f, 0x0b87);
	phy_ग_लिखो(phydev, 0x16, 0x80f5);
	phy_ग_लिखो(phydev, 0x17, 0x760e);
	phy_ग_लिखो(phydev, 0x16, 0x8107);
	phy_ग_लिखो(phydev, 0x17, 0x360e);
	phy_ग_लिखो(phydev, 0x16, 0x8551);
	phy_modअगरy(phydev, 0x17, 0xff00, 0x0800);
	phy_ग_लिखो(phydev, 0x1f, 0x0000);

	phy_modअगरy_paged(phydev, 0xbf0, 0x10, 0xe000, 0xa000);
	phy_modअगरy_paged(phydev, 0xbf4, 0x13, 0x0f00, 0x0300);

	r8168g_phy_param(phydev, 0x8044, 0xffff, 0x2417);
	r8168g_phy_param(phydev, 0x804a, 0xffff, 0x2417);
	r8168g_phy_param(phydev, 0x8050, 0xffff, 0x2417);
	r8168g_phy_param(phydev, 0x8056, 0xffff, 0x2417);
	r8168g_phy_param(phydev, 0x805c, 0xffff, 0x2417);
	r8168g_phy_param(phydev, 0x8062, 0xffff, 0x2417);
	r8168g_phy_param(phydev, 0x8068, 0xffff, 0x2417);
	r8168g_phy_param(phydev, 0x806e, 0xffff, 0x2417);
	r8168g_phy_param(phydev, 0x8074, 0xffff, 0x2417);
	r8168g_phy_param(phydev, 0x807a, 0xffff, 0x2417);

	phy_modअगरy_paged(phydev, 0xa4c, 0x15, 0x0000, 0x0040);
	phy_modअगरy_paged(phydev, 0xbf8, 0x12, 0xe000, 0xa000);

	rtl8125_legacy_क्रमce_mode(phydev);
	rtl8125b_config_eee_phy(phydev);
पूर्ण

व्योम r8169_hw_phy_config(काष्ठा rtl8169_निजी *tp, काष्ठा phy_device *phydev,
			 क्रमागत mac_version ver)
अणु
	अटल स्थिर rtl_phy_cfg_fct phy_configs[] = अणु
		/* PCI devices. */
		[RTL_GIGA_MAC_VER_02] = rtl8169s_hw_phy_config,
		[RTL_GIGA_MAC_VER_03] = rtl8169s_hw_phy_config,
		[RTL_GIGA_MAC_VER_04] = rtl8169sb_hw_phy_config,
		[RTL_GIGA_MAC_VER_05] = rtl8169scd_hw_phy_config,
		[RTL_GIGA_MAC_VER_06] = rtl8169sce_hw_phy_config,
		/* PCI-E devices. */
		[RTL_GIGA_MAC_VER_07] = rtl8102e_hw_phy_config,
		[RTL_GIGA_MAC_VER_08] = rtl8102e_hw_phy_config,
		[RTL_GIGA_MAC_VER_09] = rtl8102e_hw_phy_config,
		[RTL_GIGA_MAC_VER_10] = शून्य,
		[RTL_GIGA_MAC_VER_11] = rtl8168bb_hw_phy_config,
		[RTL_GIGA_MAC_VER_12] = rtl8168bef_hw_phy_config,
		[RTL_GIGA_MAC_VER_13] = शून्य,
		[RTL_GIGA_MAC_VER_14] = rtl8401_hw_phy_config,
		[RTL_GIGA_MAC_VER_16] = शून्य,
		[RTL_GIGA_MAC_VER_17] = rtl8168bef_hw_phy_config,
		[RTL_GIGA_MAC_VER_18] = rtl8168cp_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_19] = rtl8168c_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_20] = rtl8168c_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_21] = rtl8168c_3_hw_phy_config,
		[RTL_GIGA_MAC_VER_22] = rtl8168c_3_hw_phy_config,
		[RTL_GIGA_MAC_VER_23] = rtl8168cp_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_24] = rtl8168cp_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_25] = rtl8168d_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_26] = rtl8168d_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_27] = rtl8168d_3_hw_phy_config,
		[RTL_GIGA_MAC_VER_28] = rtl8168d_4_hw_phy_config,
		[RTL_GIGA_MAC_VER_29] = rtl8105e_hw_phy_config,
		[RTL_GIGA_MAC_VER_30] = rtl8105e_hw_phy_config,
		[RTL_GIGA_MAC_VER_31] = शून्य,
		[RTL_GIGA_MAC_VER_32] = rtl8168e_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_33] = rtl8168e_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_34] = rtl8168e_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_35] = rtl8168f_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_36] = rtl8168f_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_37] = rtl8402_hw_phy_config,
		[RTL_GIGA_MAC_VER_38] = rtl8411_hw_phy_config,
		[RTL_GIGA_MAC_VER_39] = rtl8106e_hw_phy_config,
		[RTL_GIGA_MAC_VER_40] = rtl8168g_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_41] = शून्य,
		[RTL_GIGA_MAC_VER_42] = rtl8168g_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_43] = rtl8168g_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_44] = rtl8168g_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_45] = rtl8168h_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_46] = rtl8168h_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_47] = rtl8168h_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_48] = rtl8168h_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_49] = rtl8168ep_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_50] = rtl8168ep_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_51] = rtl8168ep_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_52] = rtl8117_hw_phy_config,
		[RTL_GIGA_MAC_VER_53] = rtl8117_hw_phy_config,
		[RTL_GIGA_MAC_VER_60] = rtl8125a_1_hw_phy_config,
		[RTL_GIGA_MAC_VER_61] = rtl8125a_2_hw_phy_config,
		[RTL_GIGA_MAC_VER_63] = rtl8125b_hw_phy_config,
	पूर्ण;

	अगर (phy_configs[ver])
		phy_configs[ver](tp, phydev);
पूर्ण
