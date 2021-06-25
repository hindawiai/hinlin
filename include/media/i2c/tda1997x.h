<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * tda1997x - NXP HDMI receiver
 *
 * Copyright 2017 Tim Harvey <tharvey@gateworks.com>
 *
 */

#अगर_अघोषित _TDA1997X_
#घोषणा _TDA1997X_

/* Platक्रमm Data */
काष्ठा tda1997x_platक्रमm_data अणु
	क्रमागत v4l2_mbus_type viकरोut_bus_type;
	u32 viकरोut_bus_width;
	u8 viकरोut_port_cfg[9];
	/* pin polarity (1=invert) */
	bool viकरोut_inv_de;
	bool viकरोut_inv_hs;
	bool viकरोut_inv_vs;
	bool viकरोut_inv_pclk;
	/* घड़ी delays (0=-8, 1=-7 ... 15=+7 pixels) */
	u8 viकरोut_delay_hs;
	u8 viकरोut_delay_vs;
	u8 viकरोut_delay_de;
	u8 viकरोut_delay_pclk;
	/* sync selections (controls how sync pins are derived) */
	u8 viकरोut_sel_hs;
	u8 viकरोut_sel_vs;
	u8 viकरोut_sel_de;

	/* Audio Port Output */
	पूर्णांक auकरोut_क्रमmat;
	u32 auकरोut_mclk_fs;	/* घड़ी multiplier */
	u32 auकरोut_width;	/* 13 or 32 bit */
	u32 auकरोut_layout;	/* layout0=AP0 layout1=AP0,AP1,AP2,AP3 */
	bool auकरोut_layoutस्वतः;	/* audio layout dictated by pkt header */
	bool auकरोut_invert_clk;	/* data valid on rising edge of BCLK */
	bool audio_स्वतः_mute;	/* enable hardware audio स्वतः-mute */
पूर्ण;

#पूर्ण_अगर
