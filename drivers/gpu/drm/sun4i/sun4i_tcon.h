<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित __SUN4I_TCON_H__
#घोषणा __SUN4I_TCON_H__

#समावेश <drm/drm_crtc.h>

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/reset.h>

#घोषणा SUN4I_TCON_GCTL_REG			0x0
#घोषणा SUN4I_TCON_GCTL_TCON_ENABLE			BIT(31)
#घोषणा SUN4I_TCON_GCTL_IOMAP_MASK			BIT(0)
#घोषणा SUN4I_TCON_GCTL_IOMAP_TCON1			(1 << 0)
#घोषणा SUN4I_TCON_GCTL_IOMAP_TCON0			(0 << 0)

#घोषणा SUN4I_TCON_GINT0_REG			0x4
#घोषणा SUN4I_TCON_GINT0_VBLANK_ENABLE(pipe)		BIT(31 - (pipe))
#घोषणा SUN4I_TCON_GINT0_TCON0_TRI_FINISH_ENABLE	BIT(27)
#घोषणा SUN4I_TCON_GINT0_TCON0_TRI_COUNTER_ENABLE	BIT(26)
#घोषणा SUN4I_TCON_GINT0_VBLANK_INT(pipe)		BIT(15 - (pipe))
#घोषणा SUN4I_TCON_GINT0_TCON0_TRI_FINISH_INT		BIT(11)
#घोषणा SUN4I_TCON_GINT0_TCON0_TRI_COUNTER_INT		BIT(10)

#घोषणा SUN4I_TCON_GINT1_REG			0x8

#घोषणा SUN4I_TCON_FRM_CTL_REG			0x10
#घोषणा SUN4I_TCON0_FRM_CTL_EN				BIT(31)
#घोषणा SUN4I_TCON0_FRM_CTL_MODE_R			BIT(6)
#घोषणा SUN4I_TCON0_FRM_CTL_MODE_G			BIT(5)
#घोषणा SUN4I_TCON0_FRM_CTL_MODE_B			BIT(4)

#घोषणा SUN4I_TCON0_FRM_SEED_PR_REG		0x14
#घोषणा SUN4I_TCON0_FRM_SEED_PG_REG		0x18
#घोषणा SUN4I_TCON0_FRM_SEED_PB_REG		0x1c
#घोषणा SUN4I_TCON0_FRM_SEED_LR_REG		0x20
#घोषणा SUN4I_TCON0_FRM_SEED_LG_REG		0x24
#घोषणा SUN4I_TCON0_FRM_SEED_LB_REG		0x28
#घोषणा SUN4I_TCON0_FRM_TBL0_REG		0x2c
#घोषणा SUN4I_TCON0_FRM_TBL1_REG		0x30
#घोषणा SUN4I_TCON0_FRM_TBL2_REG		0x34
#घोषणा SUN4I_TCON0_FRM_TBL3_REG		0x38

#घोषणा SUN4I_TCON0_CTL_REG			0x40
#घोषणा SUN4I_TCON0_CTL_TCON_ENABLE			BIT(31)
#घोषणा SUN4I_TCON0_CTL_IF_MASK				GENMASK(25, 24)
#घोषणा SUN4I_TCON0_CTL_IF_8080				(1 << 24)
#घोषणा SUN4I_TCON0_CTL_CLK_DELAY_MASK			GENMASK(8, 4)
#घोषणा SUN4I_TCON0_CTL_CLK_DELAY(delay)		((delay << 4) & SUN4I_TCON0_CTL_CLK_DELAY_MASK)
#घोषणा SUN4I_TCON0_CTL_SRC_SEL_MASK			GENMASK(2, 0)

#घोषणा SUN4I_TCON0_DCLK_REG			0x44
#घोषणा SUN4I_TCON0_DCLK_GATE_BIT			(31)
#घोषणा SUN4I_TCON0_DCLK_DIV_SHIFT			(0)
#घोषणा SUN4I_TCON0_DCLK_DIV_WIDTH			(7)

#घोषणा SUN4I_TCON0_BASIC0_REG			0x48
#घोषणा SUN4I_TCON0_BASIC0_X(width)			((((width) - 1) & 0xfff) << 16)
#घोषणा SUN4I_TCON0_BASIC0_Y(height)			(((height) - 1) & 0xfff)

#घोषणा SUN4I_TCON0_BASIC1_REG			0x4c
#घोषणा SUN4I_TCON0_BASIC1_H_TOTAL(total)		((((total) - 1) & 0x1fff) << 16)
#घोषणा SUN4I_TCON0_BASIC1_H_BACKPORCH(bp)		(((bp) - 1) & 0xfff)

#घोषणा SUN4I_TCON0_BASIC2_REG			0x50
#घोषणा SUN4I_TCON0_BASIC2_V_TOTAL(total)		(((total) & 0x1fff) << 16)
#घोषणा SUN4I_TCON0_BASIC2_V_BACKPORCH(bp)		(((bp) - 1) & 0xfff)

#घोषणा SUN4I_TCON0_BASIC3_REG			0x54
#घोषणा SUN4I_TCON0_BASIC3_H_SYNC(width)		((((width) - 1) & 0x7ff) << 16)
#घोषणा SUN4I_TCON0_BASIC3_V_SYNC(height)		(((height) - 1) & 0x7ff)

#घोषणा SUN4I_TCON0_HV_IF_REG			0x58

#घोषणा SUN4I_TCON0_CPU_IF_REG			0x60
#घोषणा SUN4I_TCON0_CPU_IF_MODE_MASK			GENMASK(31, 28)
#घोषणा SUN4I_TCON0_CPU_IF_MODE_DSI			(1 << 28)
#घोषणा SUN4I_TCON0_CPU_IF_TRI_FIFO_FLUSH		BIT(16)
#घोषणा SUN4I_TCON0_CPU_IF_TRI_FIFO_EN			BIT(2)
#घोषणा SUN4I_TCON0_CPU_IF_TRI_EN			BIT(0)

#घोषणा SUN4I_TCON0_CPU_WR_REG			0x64
#घोषणा SUN4I_TCON0_CPU_RD0_REG			0x68
#घोषणा SUN4I_TCON0_CPU_RDA_REG			0x6c
#घोषणा SUN4I_TCON0_TTL0_REG			0x70
#घोषणा SUN4I_TCON0_TTL1_REG			0x74
#घोषणा SUN4I_TCON0_TTL2_REG			0x78
#घोषणा SUN4I_TCON0_TTL3_REG			0x7c
#घोषणा SUN4I_TCON0_TTL4_REG			0x80

#घोषणा SUN4I_TCON0_LVDS_IF_REG			0x84
#घोषणा SUN4I_TCON0_LVDS_IF_EN				BIT(31)
#घोषणा SUN4I_TCON0_LVDS_IF_BITWIDTH_MASK		BIT(26)
#घोषणा SUN4I_TCON0_LVDS_IF_BITWIDTH_18BITS		(1 << 26)
#घोषणा SUN4I_TCON0_LVDS_IF_BITWIDTH_24BITS		(0 << 26)
#घोषणा SUN4I_TCON0_LVDS_IF_CLK_SEL_MASK		BIT(20)
#घोषणा SUN4I_TCON0_LVDS_IF_CLK_SEL_TCON0		(1 << 20)
#घोषणा SUN4I_TCON0_LVDS_IF_CLK_POL_MASK		BIT(4)
#घोषणा SUN4I_TCON0_LVDS_IF_CLK_POL_NORMAL		(1 << 4)
#घोषणा SUN4I_TCON0_LVDS_IF_CLK_POL_INV			(0 << 4)
#घोषणा SUN4I_TCON0_LVDS_IF_DATA_POL_MASK		GENMASK(3, 0)
#घोषणा SUN4I_TCON0_LVDS_IF_DATA_POL_NORMAL		(0xf)
#घोषणा SUN4I_TCON0_LVDS_IF_DATA_POL_INV		(0)

#घोषणा SUN4I_TCON0_IO_POL_REG			0x88
#घोषणा SUN4I_TCON0_IO_POL_DCLK_PHASE(phase)		((phase & 3) << 28)
#घोषणा SUN4I_TCON0_IO_POL_DE_NEGATIVE			BIT(27)
#घोषणा SUN4I_TCON0_IO_POL_DCLK_DRIVE_NEGEDGE		BIT(26)
#घोषणा SUN4I_TCON0_IO_POL_HSYNC_POSITIVE		BIT(25)
#घोषणा SUN4I_TCON0_IO_POL_VSYNC_POSITIVE		BIT(24)

#घोषणा SUN4I_TCON0_IO_TRI_REG			0x8c
#घोषणा SUN4I_TCON0_IO_TRI_HSYNC_DISABLE		BIT(25)
#घोषणा SUN4I_TCON0_IO_TRI_VSYNC_DISABLE		BIT(24)
#घोषणा SUN4I_TCON0_IO_TRI_DATA_PINS_DISABLE(pins)	GENMASK(pins, 0)

#घोषणा SUN4I_TCON1_CTL_REG			0x90
#घोषणा SUN4I_TCON1_CTL_TCON_ENABLE			BIT(31)
#घोषणा SUN4I_TCON1_CTL_INTERLACE_ENABLE		BIT(20)
#घोषणा SUN4I_TCON1_CTL_CLK_DELAY_MASK			GENMASK(8, 4)
#घोषणा SUN4I_TCON1_CTL_CLK_DELAY(delay)		((delay << 4) & SUN4I_TCON1_CTL_CLK_DELAY_MASK)
#घोषणा SUN4I_TCON1_CTL_SRC_SEL_MASK			GENMASK(1, 0)

#घोषणा SUN4I_TCON1_BASIC0_REG			0x94
#घोषणा SUN4I_TCON1_BASIC0_X(width)			((((width) - 1) & 0xfff) << 16)
#घोषणा SUN4I_TCON1_BASIC0_Y(height)			(((height) - 1) & 0xfff)

#घोषणा SUN4I_TCON1_BASIC1_REG			0x98
#घोषणा SUN4I_TCON1_BASIC1_X(width)			((((width) - 1) & 0xfff) << 16)
#घोषणा SUN4I_TCON1_BASIC1_Y(height)			(((height) - 1) & 0xfff)

#घोषणा SUN4I_TCON1_BASIC2_REG			0x9c
#घोषणा SUN4I_TCON1_BASIC2_X(width)			((((width) - 1) & 0xfff) << 16)
#घोषणा SUN4I_TCON1_BASIC2_Y(height)			(((height) - 1) & 0xfff)

#घोषणा SUN4I_TCON1_BASIC3_REG			0xa0
#घोषणा SUN4I_TCON1_BASIC3_H_TOTAL(total)		((((total) - 1) & 0x1fff) << 16)
#घोषणा SUN4I_TCON1_BASIC3_H_BACKPORCH(bp)		(((bp) - 1) & 0xfff)

#घोषणा SUN4I_TCON1_BASIC4_REG			0xa4
#घोषणा SUN4I_TCON1_BASIC4_V_TOTAL(total)		(((total) & 0x1fff) << 16)
#घोषणा SUN4I_TCON1_BASIC4_V_BACKPORCH(bp)		(((bp) - 1) & 0xfff)

#घोषणा SUN4I_TCON1_BASIC5_REG			0xa8
#घोषणा SUN4I_TCON1_BASIC5_H_SYNC(width)		((((width) - 1) & 0x3ff) << 16)
#घोषणा SUN4I_TCON1_BASIC5_V_SYNC(height)		(((height) - 1) & 0x3ff)

#घोषणा SUN4I_TCON1_IO_POL_REG			0xf0
/* there is no करोcumentation about this bit */
#घोषणा SUN4I_TCON1_IO_POL_UNKNOWN			BIT(26)
#घोषणा SUN4I_TCON1_IO_POL_HSYNC_POSITIVE		BIT(25)
#घोषणा SUN4I_TCON1_IO_POL_VSYNC_POSITIVE		BIT(24)

#घोषणा SUN4I_TCON1_IO_TRI_REG			0xf4

#घोषणा SUN4I_TCON_ECC_FIFO_REG			0xf8
#घोषणा SUN4I_TCON_ECC_FIFO_EN				BIT(3)

#घोषणा SUN4I_TCON_CEU_CTL_REG			0x100
#घोषणा SUN4I_TCON_CEU_MUL_RR_REG		0x110
#घोषणा SUN4I_TCON_CEU_MUL_RG_REG		0x114
#घोषणा SUN4I_TCON_CEU_MUL_RB_REG		0x118
#घोषणा SUN4I_TCON_CEU_ADD_RC_REG		0x11c
#घोषणा SUN4I_TCON_CEU_MUL_GR_REG		0x120
#घोषणा SUN4I_TCON_CEU_MUL_GG_REG		0x124
#घोषणा SUN4I_TCON_CEU_MUL_GB_REG		0x128
#घोषणा SUN4I_TCON_CEU_ADD_GC_REG		0x12c
#घोषणा SUN4I_TCON_CEU_MUL_BR_REG		0x130
#घोषणा SUN4I_TCON_CEU_MUL_BG_REG		0x134
#घोषणा SUN4I_TCON_CEU_MUL_BB_REG		0x138
#घोषणा SUN4I_TCON_CEU_ADD_BC_REG		0x13c
#घोषणा SUN4I_TCON_CEU_RANGE_R_REG		0x140
#घोषणा SUN4I_TCON_CEU_RANGE_G_REG		0x144
#घोषणा SUN4I_TCON_CEU_RANGE_B_REG		0x148

#घोषणा SUN4I_TCON0_CPU_TRI0_REG		0x160
#घोषणा SUN4I_TCON0_CPU_TRI0_BLOCK_SPACE(space)		((((space) - 1) & 0xfff) << 16)
#घोषणा SUN4I_TCON0_CPU_TRI0_BLOCK_SIZE(size)		(((size) - 1) & 0xfff)

#घोषणा SUN4I_TCON0_CPU_TRI1_REG		0x164
#घोषणा SUN4I_TCON0_CPU_TRI1_BLOCK_NUM(num)		(((num) - 1) & 0xffff)

#घोषणा SUN4I_TCON0_CPU_TRI2_REG		0x168
#घोषणा SUN4I_TCON0_CPU_TRI2_START_DELAY(delay)		(((delay) & 0xffff) << 16)
#घोषणा SUN4I_TCON0_CPU_TRI2_TRANS_START_SET(set)	((set) & 0xfff)

#घोषणा SUN4I_TCON_SAFE_PERIOD_REG		0x1f0
#घोषणा SUN4I_TCON_SAFE_PERIOD_NUM(num)			(((num) & 0xfff) << 16)
#घोषणा SUN4I_TCON_SAFE_PERIOD_MODE(mode)		((mode) & 0x3)

#घोषणा SUN4I_TCON_MUX_CTRL_REG			0x200

#घोषणा SUN4I_TCON0_LVDS_ANA0_REG		0x220
#घोषणा SUN4I_TCON0_LVDS_ANA0_DCHS			BIT(16)
#घोषणा SUN4I_TCON0_LVDS_ANA0_PD			(BIT(20) | BIT(21))
#घोषणा SUN4I_TCON0_LVDS_ANA0_EN_MB			BIT(22)
#घोषणा SUN4I_TCON0_LVDS_ANA0_REG_C			(BIT(24) | BIT(25))
#घोषणा SUN4I_TCON0_LVDS_ANA0_REG_V			(BIT(26) | BIT(27))
#घोषणा SUN4I_TCON0_LVDS_ANA0_CK_EN			(BIT(29) | BIT(28))

#घोषणा SUN6I_TCON0_LVDS_ANA0_EN_MB			BIT(31)
#घोषणा SUN6I_TCON0_LVDS_ANA0_EN_LDO			BIT(30)
#घोषणा SUN6I_TCON0_LVDS_ANA0_EN_DRVC			BIT(24)
#घोषणा SUN6I_TCON0_LVDS_ANA0_EN_DRVD(x)		(((x) & 0xf) << 20)
#घोषणा SUN6I_TCON0_LVDS_ANA0_C(x)			(((x) & 3) << 17)
#घोषणा SUN6I_TCON0_LVDS_ANA0_V(x)			(((x) & 3) << 8)
#घोषणा SUN6I_TCON0_LVDS_ANA0_PD(x)			(((x) & 3) << 4)

#घोषणा SUN4I_TCON0_LVDS_ANA1_REG		0x224
#घोषणा SUN4I_TCON0_LVDS_ANA1_INIT			(0x1f << 26 | 0x1f << 10)
#घोषणा SUN4I_TCON0_LVDS_ANA1_UPDATE			(0x1f << 16 | 0x1f << 00)

#घोषणा SUN4I_TCON1_FILL_CTL_REG		0x300
#घोषणा SUN4I_TCON1_FILL_BEG0_REG		0x304
#घोषणा SUN4I_TCON1_FILL_END0_REG		0x308
#घोषणा SUN4I_TCON1_FILL_DATA0_REG		0x30c
#घोषणा SUN4I_TCON1_FILL_BEG1_REG		0x310
#घोषणा SUN4I_TCON1_FILL_END1_REG		0x314
#घोषणा SUN4I_TCON1_FILL_DATA1_REG		0x318
#घोषणा SUN4I_TCON1_FILL_BEG2_REG		0x31c
#घोषणा SUN4I_TCON1_FILL_END2_REG		0x320
#घोषणा SUN4I_TCON1_FILL_DATA2_REG		0x324
#घोषणा SUN4I_TCON1_GAMMA_TABLE_REG		0x400

#घोषणा SUN4I_TCON_MAX_CHANNELS		2

काष्ठा sun4i_tcon;

काष्ठा sun4i_tcon_quirks अणु
	bool	has_channel_0;	/* a83t करोes not have channel 0 on second TCON */
	bool	has_channel_1;	/* a33 करोes not have channel 1 */
	bool	has_lvds_alt;	/* Does the LVDS घड़ी have a parent other than the TCON घड़ी? */
	bool	needs_de_be_mux; /* sun6i needs mux to select backend */
	bool    needs_edp_reset; /* a80 edp reset needed क्रम tcon0 access */
	bool	supports_lvds;   /* Does the TCON support an LVDS output? */
	bool	polarity_in_ch0; /* some tcon1 channels have polarity bits in tcon0 pol रेजिस्टर */
	u8	dclk_min_भाग;	/* minimum भागider क्रम TCON0 DCLK */

	/* callback to handle tcon muxing options */
	पूर्णांक	(*set_mux)(काष्ठा sun4i_tcon *, स्थिर काष्ठा drm_encoder *);
	/* handler क्रम LVDS setup routine */
	व्योम	(*setup_lvds_phy)(काष्ठा sun4i_tcon *tcon,
				  स्थिर काष्ठा drm_encoder *encoder);
पूर्ण;

काष्ठा sun4i_tcon अणु
	काष्ठा device			*dev;
	काष्ठा drm_device		*drm;
	काष्ठा regmap			*regs;

	/* Main bus घड़ी */
	काष्ठा clk			*clk;

	/* Clocks क्रम the TCON channels */
	काष्ठा clk			*sclk0;
	काष्ठा clk			*sclk1;

	/* Possible mux क्रम the LVDS घड़ी */
	काष्ठा clk			*lvds_pll;

	/* Pixel घड़ी */
	काष्ठा clk			*dclk;
	u8				dclk_max_भाग;
	u8				dclk_min_भाग;

	/* Reset control */
	काष्ठा reset_control		*lcd_rst;
	काष्ठा reset_control		*lvds_rst;

	/* Platक्रमm adjusपंचांगents */
	स्थिर काष्ठा sun4i_tcon_quirks	*quirks;

	/* Associated crtc */
	काष्ठा sun4i_crtc		*crtc;

	पूर्णांक				id;

	/* TCON list management */
	काष्ठा list_head		list;
पूर्ण;

काष्ठा drm_bridge *sun4i_tcon_find_bridge(काष्ठा device_node *node);
काष्ठा drm_panel *sun4i_tcon_find_panel(काष्ठा device_node *node);

व्योम sun4i_tcon_enable_vblank(काष्ठा sun4i_tcon *tcon, bool enable);
व्योम sun4i_tcon_mode_set(काष्ठा sun4i_tcon *tcon,
			 स्थिर काष्ठा drm_encoder *encoder,
			 स्थिर काष्ठा drm_display_mode *mode);
व्योम sun4i_tcon_set_status(काष्ठा sun4i_tcon *crtc,
			   स्थिर काष्ठा drm_encoder *encoder, bool enable);

बाह्य स्थिर काष्ठा of_device_id sun4i_tcon_of_table[];

#पूर्ण_अगर /* __SUN4I_TCON_H__ */
