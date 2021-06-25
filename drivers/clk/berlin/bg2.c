<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Marvell Technology Group Ltd.
 *
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश <dt-bindings/घड़ी/berlin2.h>

#समावेश "berlin2-avpll.h"
#समावेश "berlin2-div.h"
#समावेश "berlin2-pll.h"
#समावेश "common.h"

#घोषणा REG_PINMUX0		0x0000
#घोषणा REG_PINMUX1		0x0004
#घोषणा REG_SYSPLLCTL0		0x0014
#घोषणा REG_SYSPLLCTL4		0x0024
#घोषणा REG_MEMPLLCTL0		0x0028
#घोषणा REG_MEMPLLCTL4		0x0038
#घोषणा REG_CPUPLLCTL0		0x003c
#घोषणा REG_CPUPLLCTL4		0x004c
#घोषणा REG_AVPLLCTL0		0x0050
#घोषणा REG_AVPLLCTL31		0x00cc
#घोषणा REG_AVPLLCTL62		0x0148
#घोषणा REG_PLLSTATUS		0x014c
#घोषणा REG_CLKENABLE		0x0150
#घोषणा REG_CLKSELECT0		0x0154
#घोषणा REG_CLKSELECT1		0x0158
#घोषणा REG_CLKSELECT2		0x015c
#घोषणा REG_CLKSELECT3		0x0160
#घोषणा REG_CLKSWITCH0		0x0164
#घोषणा REG_CLKSWITCH1		0x0168
#घोषणा REG_RESET_TRIGGER	0x0178
#घोषणा REG_RESET_STATUS0	0x017c
#घोषणा REG_RESET_STATUS1	0x0180
#घोषणा REG_SW_GENERIC0		0x0184
#घोषणा REG_SW_GENERIC3		0x0190
#घोषणा REG_PRODUCTID		0x01cc
#घोषणा REG_PRODUCTID_EXT	0x01d0
#घोषणा REG_GFX3DCORE_CLKCTL	0x022c
#घोषणा REG_GFX3DSYS_CLKCTL	0x0230
#घोषणा REG_ARC_CLKCTL		0x0234
#घोषणा REG_VIP_CLKCTL		0x0238
#घोषणा REG_SDIO0XIN_CLKCTL	0x023c
#घोषणा REG_SDIO1XIN_CLKCTL	0x0240
#घोषणा REG_GFX3DEXTRA_CLKCTL	0x0244
#घोषणा REG_GFX3D_RESET		0x0248
#घोषणा REG_GC360_CLKCTL	0x024c
#घोषणा REG_SDIO_DLLMST_CLKCTL	0x0250

/*
 * BG2/BG2CD SoCs have the following audio/video I/O units:
 *
 * audiohd: HDMI TX audio
 * audio0:  7.1ch TX
 * audio1:  2ch TX
 * audio2:  2ch RX
 * audio3:  SPDIF TX
 * video0:  HDMI video
 * video1:  Secondary video
 * video2:  SD auxiliary video
 *
 * There are no बाह्यal audio घड़ीs (ACLKI0, ACLKI1) and
 * only one बाह्यal video घड़ी (VCLKI0).
 *
 * Currently missing bits and pieces:
 * - audio_fast_pll is unknown
 * - audiohd_pll is unknown
 * - video0_pll is unknown
 * - audio[023], audiohd parent pll is assumed to be audio_fast_pll
 *
 */

#घोषणा	MAX_CLKS 41
अटल काष्ठा clk_hw_onecell_data *clk_data;
अटल DEFINE_SPINLOCK(lock);
अटल व्योम __iomem *gbase;

क्रमागत अणु
	REFCLK, VIDEO_EXT0,
	SYSPLL, MEMPLL, CPUPLL,
	AVPLL_A1, AVPLL_A2, AVPLL_A3, AVPLL_A4,
	AVPLL_A5, AVPLL_A6, AVPLL_A7, AVPLL_A8,
	AVPLL_B1, AVPLL_B2, AVPLL_B3, AVPLL_B4,
	AVPLL_B5, AVPLL_B6, AVPLL_B7, AVPLL_B8,
	AUDIO1_PLL, AUDIO_FAST_PLL,
	VIDEO0_PLL, VIDEO0_IN,
	VIDEO1_PLL, VIDEO1_IN,
	VIDEO2_PLL, VIDEO2_IN,
पूर्ण;

अटल स्थिर अक्षर *clk_names[] = अणु
	[REFCLK]		= "refclk",
	[VIDEO_EXT0]		= "video_ext0",
	[SYSPLL]		= "syspll",
	[MEMPLL]		= "mempll",
	[CPUPLL]		= "cpupll",
	[AVPLL_A1]		= "avpll_a1",
	[AVPLL_A2]		= "avpll_a2",
	[AVPLL_A3]		= "avpll_a3",
	[AVPLL_A4]		= "avpll_a4",
	[AVPLL_A5]		= "avpll_a5",
	[AVPLL_A6]		= "avpll_a6",
	[AVPLL_A7]		= "avpll_a7",
	[AVPLL_A8]		= "avpll_a8",
	[AVPLL_B1]		= "avpll_b1",
	[AVPLL_B2]		= "avpll_b2",
	[AVPLL_B3]		= "avpll_b3",
	[AVPLL_B4]		= "avpll_b4",
	[AVPLL_B5]		= "avpll_b5",
	[AVPLL_B6]		= "avpll_b6",
	[AVPLL_B7]		= "avpll_b7",
	[AVPLL_B8]		= "avpll_b8",
	[AUDIO1_PLL]		= "audio1_pll",
	[AUDIO_FAST_PLL]	= "audio_fast_pll",
	[VIDEO0_PLL]		= "video0_pll",
	[VIDEO0_IN]		= "video0_in",
	[VIDEO1_PLL]		= "video1_pll",
	[VIDEO1_IN]		= "video1_in",
	[VIDEO2_PLL]		= "video2_pll",
	[VIDEO2_IN]		= "video2_in",
पूर्ण;

अटल स्थिर काष्ठा berlin2_pll_map bg2_pll_map __initस्थिर = अणु
	.vcoभाग		= अणु10, 15, 20, 25, 30, 40, 50, 60, 80पूर्ण,
	.mult		= 10,
	.fbभाग_shअगरt	= 6,
	.rfभाग_shअगरt	= 1,
	.भागsel_shअगरt	= 7,
पूर्ण;

अटल स्थिर u8 शेष_parent_ids[] = अणु
	SYSPLL, AVPLL_B4, AVPLL_A5, AVPLL_B6, AVPLL_B7, SYSPLL
पूर्ण;

अटल स्थिर काष्ठा berlin2_भाग_data bg2_भागs[] __initस्थिर = अणु
	अणु
		.name = "sys",
		.parent_ids = (स्थिर u8 [])अणु
			SYSPLL, AVPLL_B4, AVPLL_B5, AVPLL_B6, AVPLL_B7, SYSPLL
		पूर्ण,
		.num_parents = 6,
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 0),
			BERLIN2_PLL_SELECT(REG_CLKSELECT0, 0),
			BERLIN2_DIV_SELECT(REG_CLKSELECT0, 3),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 3),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 4),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 5),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	अणु
		.name = "cpu",
		.parent_ids = (स्थिर u8 [])अणु
			CPUPLL, MEMPLL, MEMPLL, MEMPLL, MEMPLL
		पूर्ण,
		.num_parents = 5,
		.map = अणु
			BERLIN2_PLL_SELECT(REG_CLKSELECT0, 6),
			BERLIN2_DIV_SELECT(REG_CLKSELECT0, 9),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 6),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 7),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 8),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "drmfigo",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 16),
			BERLIN2_PLL_SELECT(REG_CLKSELECT0, 17),
			BERLIN2_DIV_SELECT(REG_CLKSELECT0, 20),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 12),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 13),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 14),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "cfg",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 1),
			BERLIN2_PLL_SELECT(REG_CLKSELECT0, 23),
			BERLIN2_DIV_SELECT(REG_CLKSELECT0, 26),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 15),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 16),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 17),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "gfx",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 4),
			BERLIN2_PLL_SELECT(REG_CLKSELECT0, 29),
			BERLIN2_DIV_SELECT(REG_CLKSELECT1, 0),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 18),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 19),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 20),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "zsp",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 5),
			BERLIN2_PLL_SELECT(REG_CLKSELECT1, 3),
			BERLIN2_DIV_SELECT(REG_CLKSELECT1, 6),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 21),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 22),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 23),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "perif",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 6),
			BERLIN2_PLL_SELECT(REG_CLKSELECT1, 9),
			BERLIN2_DIV_SELECT(REG_CLKSELECT1, 12),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 24),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 25),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 26),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = CLK_IGNORE_UNUSED,
	पूर्ण,
	अणु
		.name = "pcube",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 2),
			BERLIN2_PLL_SELECT(REG_CLKSELECT1, 15),
			BERLIN2_DIV_SELECT(REG_CLKSELECT1, 18),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 27),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 28),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH0, 29),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "vscope",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 3),
			BERLIN2_PLL_SELECT(REG_CLKSELECT1, 21),
			BERLIN2_DIV_SELECT(REG_CLKSELECT1, 24),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH0, 30),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH0, 31),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH1, 0),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "nfc_ecc",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 18),
			BERLIN2_PLL_SELECT(REG_CLKSELECT1, 27),
			BERLIN2_DIV_SELECT(REG_CLKSELECT2, 0),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH1, 1),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH1, 2),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH1, 3),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "vpp",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 21),
			BERLIN2_PLL_SELECT(REG_CLKSELECT2, 3),
			BERLIN2_DIV_SELECT(REG_CLKSELECT2, 6),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH1, 4),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH1, 5),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH1, 6),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "app",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 20),
			BERLIN2_PLL_SELECT(REG_CLKSELECT2, 9),
			BERLIN2_DIV_SELECT(REG_CLKSELECT2, 12),
			BERLIN2_PLL_SWITCH(REG_CLKSWITCH1, 7),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH1, 8),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH1, 9),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "audio0",
		.parent_ids = (स्थिर u8 [])अणु AUDIO_FAST_PLL पूर्ण,
		.num_parents = 1,
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 22),
			BERLIN2_DIV_SELECT(REG_CLKSELECT2, 17),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH1, 10),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH1, 11),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "audio2",
		.parent_ids = (स्थिर u8 [])अणु AUDIO_FAST_PLL पूर्ण,
		.num_parents = 1,
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 24),
			BERLIN2_DIV_SELECT(REG_CLKSELECT2, 20),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH1, 14),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH1, 15),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "audio3",
		.parent_ids = (स्थिर u8 [])अणु AUDIO_FAST_PLL पूर्ण,
		.num_parents = 1,
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 25),
			BERLIN2_DIV_SELECT(REG_CLKSELECT2, 23),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH1, 16),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH1, 17),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "audio1",
		.parent_ids = (स्थिर u8 [])अणु AUDIO1_PLL पूर्ण,
		.num_parents = 1,
		.map = अणु
			BERLIN2_DIV_GATE(REG_CLKENABLE, 23),
			BERLIN2_DIV_SELECT(REG_CLKSELECT3, 0),
			BERLIN2_DIV_SWITCH(REG_CLKSWITCH1, 12),
			BERLIN2_DIV_D3SWITCH(REG_CLKSWITCH1, 13),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "gfx3d_core",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_GFX3DCORE_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "gfx3d_sys",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_GFX3DSYS_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "arc",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_ARC_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "vip",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_VIP_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "sdio0xin",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_SDIO0XIN_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "sdio1xin",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_SDIO1XIN_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "gfx3d_extra",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_GFX3DEXTRA_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "gc360",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_GC360_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
	अणु
		.name = "sdio_dllmst",
		.parent_ids = शेष_parent_ids,
		.num_parents = ARRAY_SIZE(शेष_parent_ids),
		.map = अणु
			BERLIN2_SINGLE_DIV(REG_SDIO_DLLMST_CLKCTL),
		पूर्ण,
		.भाग_flags = BERLIN2_DIV_HAS_GATE | BERLIN2_DIV_HAS_MUX,
		.flags = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा berlin2_gate_data bg2_gates[] __initस्थिर = अणु
	अणु "geth0",	"perif",	7 पूर्ण,
	अणु "geth1",	"perif",	8 पूर्ण,
	अणु "sata",	"perif",	9 पूर्ण,
	अणु "ahbapb",	"perif",	10, CLK_IGNORE_UNUSED पूर्ण,
	अणु "usb0",	"perif",	11 पूर्ण,
	अणु "usb1",	"perif",	12 पूर्ण,
	अणु "pbridge",	"perif",	13, CLK_IGNORE_UNUSED पूर्ण,
	अणु "sdio0",	"perif",	14 पूर्ण,
	अणु "sdio1",	"perif",	15 पूर्ण,
	अणु "nfc",	"perif",	17 पूर्ण,
	अणु "smemc",	"perif",	19 पूर्ण,
	अणु "audiohd",	"audiohd_pll",	26 पूर्ण,
	अणु "video0",	"video0_in",	27 पूर्ण,
	अणु "video1",	"video1_in",	28 पूर्ण,
	अणु "video2",	"video2_in",	29 पूर्ण,
पूर्ण;

अटल व्योम __init berlin2_घड़ी_setup(काष्ठा device_node *np)
अणु
	काष्ठा device_node *parent_np = of_get_parent(np);
	स्थिर अक्षर *parent_names[9];
	काष्ठा clk *clk;
	काष्ठा clk_hw *hw;
	काष्ठा clk_hw **hws;
	u8 avpll_flags = 0;
	पूर्णांक n, ret;

	clk_data = kzalloc(काष्ठा_size(clk_data, hws, MAX_CLKS), GFP_KERNEL);
	अगर (!clk_data)
		वापस;
	clk_data->num = MAX_CLKS;
	hws = clk_data->hws;

	gbase = of_iomap(parent_np, 0);
	अगर (!gbase)
		वापस;

	/* overग_लिखो शेष घड़ी names with DT provided ones */
	clk = of_clk_get_by_name(np, clk_names[REFCLK]);
	अगर (!IS_ERR(clk)) अणु
		clk_names[REFCLK] = __clk_get_name(clk);
		clk_put(clk);
	पूर्ण

	clk = of_clk_get_by_name(np, clk_names[VIDEO_EXT0]);
	अगर (!IS_ERR(clk)) अणु
		clk_names[VIDEO_EXT0] = __clk_get_name(clk);
		clk_put(clk);
	पूर्ण

	/* simple रेजिस्टर PLLs */
	ret = berlin2_pll_रेजिस्टर(&bg2_pll_map, gbase + REG_SYSPLLCTL0,
				   clk_names[SYSPLL], clk_names[REFCLK], 0);
	अगर (ret)
		जाओ bg2_fail;

	ret = berlin2_pll_रेजिस्टर(&bg2_pll_map, gbase + REG_MEMPLLCTL0,
				   clk_names[MEMPLL], clk_names[REFCLK], 0);
	अगर (ret)
		जाओ bg2_fail;

	ret = berlin2_pll_रेजिस्टर(&bg2_pll_map, gbase + REG_CPUPLLCTL0,
				   clk_names[CPUPLL], clk_names[REFCLK], 0);
	अगर (ret)
		जाओ bg2_fail;

	अगर (of_device_is_compatible(np, "marvell,berlin2-global-register"))
		avpll_flags |= BERLIN2_AVPLL_SCRAMBLE_QUIRK;

	/* audio/video VCOs */
	ret = berlin2_avpll_vco_रेजिस्टर(gbase + REG_AVPLLCTL0, "avpll_vcoA",
			 clk_names[REFCLK], avpll_flags, 0);
	अगर (ret)
		जाओ bg2_fail;

	क्रम (n = 0; n < 8; n++) अणु
		ret = berlin2_avpll_channel_रेजिस्टर(gbase + REG_AVPLLCTL0,
			     clk_names[AVPLL_A1 + n], n, "avpll_vcoA",
			     avpll_flags, 0);
		अगर (ret)
			जाओ bg2_fail;
	पूर्ण

	ret = berlin2_avpll_vco_रेजिस्टर(gbase + REG_AVPLLCTL31, "avpll_vcoB",
				 clk_names[REFCLK], BERLIN2_AVPLL_BIT_QUIRK |
				 avpll_flags, 0);
	अगर (ret)
		जाओ bg2_fail;

	क्रम (n = 0; n < 8; n++) अणु
		ret = berlin2_avpll_channel_रेजिस्टर(gbase + REG_AVPLLCTL31,
			     clk_names[AVPLL_B1 + n], n, "avpll_vcoB",
			     BERLIN2_AVPLL_BIT_QUIRK | avpll_flags, 0);
		अगर (ret)
			जाओ bg2_fail;
	पूर्ण

	/* reference घड़ी bypass चयनes */
	parent_names[0] = clk_names[SYSPLL];
	parent_names[1] = clk_names[REFCLK];
	hw = clk_hw_रेजिस्टर_mux(शून्य, "syspll_byp", parent_names, 2,
			       0, gbase + REG_CLKSWITCH0, 0, 1, 0, &lock);
	अगर (IS_ERR(hw))
		जाओ bg2_fail;
	clk_names[SYSPLL] = clk_hw_get_name(hw);

	parent_names[0] = clk_names[MEMPLL];
	parent_names[1] = clk_names[REFCLK];
	hw = clk_hw_रेजिस्टर_mux(शून्य, "mempll_byp", parent_names, 2,
			       0, gbase + REG_CLKSWITCH0, 1, 1, 0, &lock);
	अगर (IS_ERR(hw))
		जाओ bg2_fail;
	clk_names[MEMPLL] = clk_hw_get_name(hw);

	parent_names[0] = clk_names[CPUPLL];
	parent_names[1] = clk_names[REFCLK];
	hw = clk_hw_रेजिस्टर_mux(शून्य, "cpupll_byp", parent_names, 2,
			       0, gbase + REG_CLKSWITCH0, 2, 1, 0, &lock);
	अगर (IS_ERR(hw))
		जाओ bg2_fail;
	clk_names[CPUPLL] = clk_hw_get_name(hw);

	/* घड़ी muxes */
	parent_names[0] = clk_names[AVPLL_B3];
	parent_names[1] = clk_names[AVPLL_A3];
	hw = clk_hw_रेजिस्टर_mux(शून्य, clk_names[AUDIO1_PLL], parent_names, 2,
			       0, gbase + REG_CLKSELECT2, 29, 1, 0, &lock);
	अगर (IS_ERR(hw))
		जाओ bg2_fail;

	parent_names[0] = clk_names[VIDEO0_PLL];
	parent_names[1] = clk_names[VIDEO_EXT0];
	hw = clk_hw_रेजिस्टर_mux(शून्य, clk_names[VIDEO0_IN], parent_names, 2,
			       0, gbase + REG_CLKSELECT3, 4, 1, 0, &lock);
	अगर (IS_ERR(hw))
		जाओ bg2_fail;

	parent_names[0] = clk_names[VIDEO1_PLL];
	parent_names[1] = clk_names[VIDEO_EXT0];
	hw = clk_hw_रेजिस्टर_mux(शून्य, clk_names[VIDEO1_IN], parent_names, 2,
			       0, gbase + REG_CLKSELECT3, 6, 1, 0, &lock);
	अगर (IS_ERR(hw))
		जाओ bg2_fail;

	parent_names[0] = clk_names[AVPLL_A2];
	parent_names[1] = clk_names[AVPLL_B2];
	hw = clk_hw_रेजिस्टर_mux(शून्य, clk_names[VIDEO1_PLL], parent_names, 2,
			       0, gbase + REG_CLKSELECT3, 7, 1, 0, &lock);
	अगर (IS_ERR(hw))
		जाओ bg2_fail;

	parent_names[0] = clk_names[VIDEO2_PLL];
	parent_names[1] = clk_names[VIDEO_EXT0];
	hw = clk_hw_रेजिस्टर_mux(शून्य, clk_names[VIDEO2_IN], parent_names, 2,
			       0, gbase + REG_CLKSELECT3, 9, 1, 0, &lock);
	अगर (IS_ERR(hw))
		जाओ bg2_fail;

	parent_names[0] = clk_names[AVPLL_B1];
	parent_names[1] = clk_names[AVPLL_A5];
	hw = clk_hw_रेजिस्टर_mux(शून्य, clk_names[VIDEO2_PLL], parent_names, 2,
			       0, gbase + REG_CLKSELECT3, 10, 1, 0, &lock);
	अगर (IS_ERR(hw))
		जाओ bg2_fail;

	/* घड़ी भागider cells */
	क्रम (n = 0; n < ARRAY_SIZE(bg2_भागs); n++) अणु
		स्थिर काष्ठा berlin2_भाग_data *dd = &bg2_भागs[n];
		पूर्णांक k;

		क्रम (k = 0; k < dd->num_parents; k++)
			parent_names[k] = clk_names[dd->parent_ids[k]];

		hws[CLKID_SYS + n] = berlin2_भाग_रेजिस्टर(&dd->map, gbase,
				dd->name, dd->भाग_flags, parent_names,
				dd->num_parents, dd->flags, &lock);
	पूर्ण

	/* घड़ी gate cells */
	क्रम (n = 0; n < ARRAY_SIZE(bg2_gates); n++) अणु
		स्थिर काष्ठा berlin2_gate_data *gd = &bg2_gates[n];

		hws[CLKID_GETH0 + n] = clk_hw_रेजिस्टर_gate(शून्य, gd->name,
			    gd->parent_name, gd->flags, gbase + REG_CLKENABLE,
			    gd->bit_idx, 0, &lock);
	पूर्ण

	/* twdclk is derived from cpu/3 */
	hws[CLKID_TWD] =
		clk_hw_रेजिस्टर_fixed_factor(शून्य, "twd", "cpu", 0, 1, 3);

	/* check क्रम errors on leaf घड़ीs */
	क्रम (n = 0; n < MAX_CLKS; n++) अणु
		अगर (!IS_ERR(hws[n]))
			जारी;

		pr_err("%pOF: Unable to register leaf clock %d\n", np, n);
		जाओ bg2_fail;
	पूर्ण

	/* रेजिस्टर clk-provider */
	of_clk_add_hw_provider(np, of_clk_hw_onecell_get, clk_data);

	वापस;

bg2_fail:
	iounmap(gbase);
पूर्ण
CLK_OF_DECLARE(berlin2_clk, "marvell,berlin2-clk",
	       berlin2_घड़ी_setup);
