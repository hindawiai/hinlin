<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*-
 * Finger Sensing Pad PS/2 mouse driver.
 *
 * Copyright (C) 2005-2007 Asia Vital Components Co., Ltd.
 * Copyright (C) 2005-2012 Tai-hwa Liang, Sentelic Corporation.
 */

#अगर_अघोषित	__SENTELIC_H
#घोषणा	__SENTELIC_H

/* Finger-sensing Pad inक्रमmation रेजिस्टरs */
#घोषणा	FSP_REG_DEVICE_ID	0x00
#घोषणा	FSP_REG_VERSION		0x01
#घोषणा	FSP_REG_REVISION	0x04
#घोषणा	FSP_REG_TMOD_STATUS1	0x0B
#घोषणा	FSP_BIT_NO_ROTATION	BIT(3)
#घोषणा	FSP_REG_PAGE_CTRL	0x0F

/* Finger-sensing Pad control रेजिस्टरs */
#घोषणा	FSP_REG_SYSCTL1		0x10
#घोषणा	FSP_BIT_EN_REG_CLK	BIT(5)
#घोषणा	FSP_REG_TMOD_STATUS	0x20
#घोषणा	FSP_REG_OPC_QDOWN	0x31
#घोषणा	FSP_BIT_EN_OPC_TAG	BIT(7)
#घोषणा	FSP_REG_OPTZ_XLO	0x34
#घोषणा	FSP_REG_OPTZ_XHI	0x35
#घोषणा	FSP_REG_OPTZ_YLO	0x36
#घोषणा	FSP_REG_OPTZ_YHI	0x37
#घोषणा	FSP_REG_SYSCTL5		0x40
#घोषणा	FSP_BIT_90_DEGREE	BIT(0)
#घोषणा	FSP_BIT_EN_MSID6	BIT(1)
#घोषणा	FSP_BIT_EN_MSID7	BIT(2)
#घोषणा	FSP_BIT_EN_MSID8	BIT(3)
#घोषणा	FSP_BIT_EN_AUTO_MSID8	BIT(5)
#घोषणा	FSP_BIT_EN_PKT_G0	BIT(6)

#घोषणा	FSP_REG_ONPAD_CTL	0x43
#घोषणा	FSP_BIT_ONPAD_ENABLE	BIT(0)
#घोषणा	FSP_BIT_ONPAD_FBBB	BIT(1)
#घोषणा	FSP_BIT_FIX_VSCR	BIT(3)
#घोषणा	FSP_BIT_FIX_HSCR	BIT(5)
#घोषणा	FSP_BIT_DRAG_LOCK	BIT(6)

#घोषणा	FSP_REG_SWC1		(0x90)
#घोषणा	FSP_BIT_SWC1_EN_ABS_1F	BIT(0)
#घोषणा	FSP_BIT_SWC1_EN_GID	BIT(1)
#घोषणा	FSP_BIT_SWC1_EN_ABS_2F	BIT(2)
#घोषणा	FSP_BIT_SWC1_EN_FUP_OUT	BIT(3)
#घोषणा	FSP_BIT_SWC1_EN_ABS_CON	BIT(4)
#घोषणा	FSP_BIT_SWC1_GST_GRP0	BIT(5)
#घोषणा	FSP_BIT_SWC1_GST_GRP1	BIT(6)
#घोषणा	FSP_BIT_SWC1_BX_COMPAT	BIT(7)

#घोषणा	FSP_PAGE_0B		(0x0b)
#घोषणा	FSP_PAGE_82		(0x82)
#घोषणा	FSP_PAGE_DEFAULT	FSP_PAGE_82

#घोषणा	FSP_REG_SN0		(0x40)
#घोषणा	FSP_REG_SN1		(0x41)
#घोषणा	FSP_REG_SN2		(0x42)

/* Finger-sensing Pad packet क्रमmating related definitions */

/* असलolute packet type */
#घोषणा	FSP_PKT_TYPE_NORMAL	(0x00)
#घोषणा	FSP_PKT_TYPE_ABS	(0x01)
#घोषणा	FSP_PKT_TYPE_NOTIFY	(0x02)
#घोषणा	FSP_PKT_TYPE_NORMAL_OPC	(0x03)
#घोषणा	FSP_PKT_TYPE_SHIFT	(6)

/* bit definitions क्रम the first byte of report packet */
#घोषणा	FSP_PB0_LBTN		BIT(0)
#घोषणा	FSP_PB0_RBTN		BIT(1)
#घोषणा	FSP_PB0_MBTN		BIT(2)
#घोषणा	FSP_PB0_MFMC_FGR2	FSP_PB0_MBTN
#घोषणा	FSP_PB0_MUST_SET	BIT(3)
#घोषणा	FSP_PB0_PHY_BTN		BIT(4)
#घोषणा	FSP_PB0_MFMC		BIT(5)

/* hardware revisions */
#घोषणा	FSP_VER_STL3888_A4	(0xC1)
#घोषणा	FSP_VER_STL3888_B0	(0xD0)
#घोषणा	FSP_VER_STL3888_B1	(0xD1)
#घोषणा	FSP_VER_STL3888_B2	(0xD2)
#घोषणा	FSP_VER_STL3888_C0	(0xE0)
#घोषणा	FSP_VER_STL3888_C1	(0xE1)
#घोषणा	FSP_VER_STL3888_D0	(0xE2)
#घोषणा	FSP_VER_STL3888_D1	(0xE3)
#घोषणा	FSP_VER_STL3888_E0	(0xE4)

#अगर_घोषित __KERNEL__

काष्ठा fsp_data अणु
	अचिन्हित अक्षर	ver;		/* hardware version */
	अचिन्हित अक्षर	rev;		/* hardware revison */
	अचिन्हित पूर्णांक	buttons;	/* Number of buttons */
	अचिन्हित पूर्णांक	flags;
#घोषणा	FSPDRV_FLAG_EN_OPC	(0x001)	/* enable on-pad clicking */

	bool		vscroll;	/* Vertical scroll zone enabled */
	bool		hscroll;	/* Horizontal scroll zone enabled */

	अचिन्हित अक्षर	last_reg;	/* Last रेजिस्टर we requested पढ़ो from */
	अचिन्हित अक्षर	last_val;
	अचिन्हित पूर्णांक	last_mt_fgr;	/* Last seen finger(multitouch) */
पूर्ण;

बाह्य पूर्णांक fsp_detect(काष्ठा psmouse *psmouse, bool set_properties);
बाह्य पूर्णांक fsp_init(काष्ठा psmouse *psmouse);

#पूर्ण_अगर	/* __KERNEL__ */

#पूर्ण_अगर	/* !__SENTELIC_H */
