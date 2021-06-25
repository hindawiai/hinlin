<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित _SUN4I_HDMI_H_
#घोषणा _SUN4I_HDMI_H_

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_encoder.h>
#समावेश <linux/regmap.h>

#समावेश <media/cec-pin.h>

#घोषणा SUN4I_HDMI_CTRL_REG		0x004
#घोषणा SUN4I_HDMI_CTRL_ENABLE			BIT(31)

#घोषणा SUN4I_HDMI_IRQ_REG		0x008
#घोषणा SUN4I_HDMI_IRQ_STA_MASK			0x73
#घोषणा SUN4I_HDMI_IRQ_STA_FIFO_OF		BIT(1)
#घोषणा SUN4I_HDMI_IRQ_STA_FIFO_UF		BIT(0)

#घोषणा SUN4I_HDMI_HPD_REG		0x00c
#घोषणा SUN4I_HDMI_HPD_HIGH			BIT(0)

#घोषणा SUN4I_HDMI_VID_CTRL_REG		0x010
#घोषणा SUN4I_HDMI_VID_CTRL_ENABLE		BIT(31)
#घोषणा SUN4I_HDMI_VID_CTRL_HDMI_MODE		BIT(30)

#घोषणा SUN4I_HDMI_VID_TIMING_ACT_REG	0x014
#घोषणा SUN4I_HDMI_VID_TIMING_BP_REG	0x018
#घोषणा SUN4I_HDMI_VID_TIMING_FP_REG	0x01c
#घोषणा SUN4I_HDMI_VID_TIMING_SPW_REG	0x020

#घोषणा SUN4I_HDMI_VID_TIMING_X(x)		((((x) - 1) & GENMASK(11, 0)))
#घोषणा SUN4I_HDMI_VID_TIMING_Y(y)		((((y) - 1) & GENMASK(11, 0)) << 16)

#घोषणा SUN4I_HDMI_VID_TIMING_POL_REG	0x024
#घोषणा SUN4I_HDMI_VID_TIMING_POL_TX_CLK        (0x3e0 << 16)
#घोषणा SUN4I_HDMI_VID_TIMING_POL_VSYNC		BIT(1)
#घोषणा SUN4I_HDMI_VID_TIMING_POL_HSYNC		BIT(0)

#घोषणा SUN4I_HDMI_AVI_INFOFRAME_REG(n)	(0x080 + (n))

#घोषणा SUN4I_HDMI_PAD_CTRL0_REG	0x200
#घोषणा SUN4I_HDMI_PAD_CTRL0_BIASEN		BIT(31)
#घोषणा SUN4I_HDMI_PAD_CTRL0_LDOCEN		BIT(30)
#घोषणा SUN4I_HDMI_PAD_CTRL0_LDODEN		BIT(29)
#घोषणा SUN4I_HDMI_PAD_CTRL0_PWENC		BIT(28)
#घोषणा SUN4I_HDMI_PAD_CTRL0_PWEND		BIT(27)
#घोषणा SUN4I_HDMI_PAD_CTRL0_PWENG		BIT(26)
#घोषणा SUN4I_HDMI_PAD_CTRL0_CKEN		BIT(25)
#घोषणा SUN4I_HDMI_PAD_CTRL0_TXEN		BIT(23)

#घोषणा SUN4I_HDMI_PAD_CTRL1_REG	0x204
#घोषणा SUN4I_HDMI_PAD_CTRL1_UNKNOWN		BIT(24)	/* set on A31 */
#घोषणा SUN4I_HDMI_PAD_CTRL1_AMP_OPT		BIT(23)
#घोषणा SUN4I_HDMI_PAD_CTRL1_AMPCK_OPT		BIT(22)
#घोषणा SUN4I_HDMI_PAD_CTRL1_EMP_OPT		BIT(20)
#घोषणा SUN4I_HDMI_PAD_CTRL1_EMPCK_OPT		BIT(19)
#घोषणा SUN4I_HDMI_PAD_CTRL1_PWSCK		BIT(18)
#घोषणा SUN4I_HDMI_PAD_CTRL1_PWSDT		BIT(17)
#घोषणा SUN4I_HDMI_PAD_CTRL1_REG_DEN		BIT(15)
#घोषणा SUN4I_HDMI_PAD_CTRL1_REG_DENCK		BIT(14)
#घोषणा SUN4I_HDMI_PAD_CTRL1_REG_EMP(n)		(((n) & 7) << 10)
#घोषणा SUN4I_HDMI_PAD_CTRL1_HALVE_CLK		BIT(6)
#घोषणा SUN4I_HDMI_PAD_CTRL1_REG_AMP(n)		(((n) & 7) << 3)

/* These bits seem to invert the TMDS data channels */
#घोषणा SUN4I_HDMI_PAD_CTRL1_INVERT_R		BIT(2)
#घोषणा SUN4I_HDMI_PAD_CTRL1_INVERT_G		BIT(1)
#घोषणा SUN4I_HDMI_PAD_CTRL1_INVERT_B		BIT(0)

#घोषणा SUN4I_HDMI_PLL_CTRL_REG		0x208
#घोषणा SUN4I_HDMI_PLL_CTRL_PLL_EN		BIT(31)
#घोषणा SUN4I_HDMI_PLL_CTRL_BWS			BIT(30)
#घोषणा SUN4I_HDMI_PLL_CTRL_HV_IS_33		BIT(29)
#घोषणा SUN4I_HDMI_PLL_CTRL_LDO1_EN		BIT(28)
#घोषणा SUN4I_HDMI_PLL_CTRL_LDO2_EN		BIT(27)
#घोषणा SUN4I_HDMI_PLL_CTRL_SDIV2		BIT(25)
#घोषणा SUN4I_HDMI_PLL_CTRL_VCO_GAIN(n)		(((n) & 7) << 20)
#घोषणा SUN4I_HDMI_PLL_CTRL_S(n)		(((n) & 7) << 17)
#घोषणा SUN4I_HDMI_PLL_CTRL_CP_S(n)		(((n) & 0x1f) << 12)
#घोषणा SUN4I_HDMI_PLL_CTRL_CS(n)		(((n) & 0xf) << 8)
#घोषणा SUN4I_HDMI_PLL_CTRL_DIV(n)		(((n) & 0xf) << 4)
#घोषणा SUN4I_HDMI_PLL_CTRL_DIV_MASK		GENMASK(7, 4)
#घोषणा SUN4I_HDMI_PLL_CTRL_VCO_S(n)		((n) & 0xf)

#घोषणा SUN4I_HDMI_PLL_DBG0_REG		0x20c
#घोषणा SUN4I_HDMI_PLL_DBG0_TMDS_PARENT(n)	(((n) & 1) << 21)
#घोषणा SUN4I_HDMI_PLL_DBG0_TMDS_PARENT_MASK	BIT(21)
#घोषणा SUN4I_HDMI_PLL_DBG0_TMDS_PARENT_SHIFT	21

#घोषणा SUN4I_HDMI_CEC			0x214
#घोषणा SUN4I_HDMI_CEC_ENABLE			BIT(11)
#घोषणा SUN4I_HDMI_CEC_TX			BIT(9)
#घोषणा SUN4I_HDMI_CEC_RX			BIT(8)

#घोषणा SUN4I_HDMI_PKT_CTRL_REG(n)	(0x2f0 + (4 * (n)))
#घोषणा SUN4I_HDMI_PKT_CTRL_TYPE(n, t)		((t) << (((n) % 4) * 4))

#घोषणा SUN4I_HDMI_UNKNOWN_REG		0x300
#घोषणा SUN4I_HDMI_UNKNOWN_INPUT_SYNC		BIT(27)

#घोषणा SUN4I_HDMI_DDC_CTRL_REG		0x500
#घोषणा SUN4I_HDMI_DDC_CTRL_ENABLE		BIT(31)
#घोषणा SUN4I_HDMI_DDC_CTRL_START_CMD		BIT(30)
#घोषणा SUN4I_HDMI_DDC_CTRL_FIFO_सूची_MASK	BIT(8)
#घोषणा SUN4I_HDMI_DDC_CTRL_FIFO_सूची_WRITE	(1 << 8)
#घोषणा SUN4I_HDMI_DDC_CTRL_FIFO_सूची_READ	(0 << 8)
#घोषणा SUN4I_HDMI_DDC_CTRL_RESET		BIT(0)

#घोषणा SUN4I_HDMI_DDC_ADDR_REG		0x504
#घोषणा SUN4I_HDMI_DDC_ADDR_SEGMENT(seg)	(((seg) & 0xff) << 24)
#घोषणा SUN4I_HDMI_DDC_ADDR_EDDC(addr)		(((addr) & 0xff) << 16)
#घोषणा SUN4I_HDMI_DDC_ADDR_OFFSET(off)		(((off) & 0xff) << 8)
#घोषणा SUN4I_HDMI_DDC_ADDR_SLAVE(addr)		((addr) & 0xff)

#घोषणा SUN4I_HDMI_DDC_INT_STATUS_REG		0x50c
#घोषणा SUN4I_HDMI_DDC_INT_STATUS_ILLEGAL_FIFO_OPERATION	BIT(7)
#घोषणा SUN4I_HDMI_DDC_INT_STATUS_DDC_RX_FIFO_UNDERFLOW		BIT(6)
#घोषणा SUN4I_HDMI_DDC_INT_STATUS_DDC_TX_FIFO_OVERFLOW		BIT(5)
#घोषणा SUN4I_HDMI_DDC_INT_STATUS_FIFO_REQUEST			BIT(4)
#घोषणा SUN4I_HDMI_DDC_INT_STATUS_ARBITRATION_ERROR		BIT(3)
#घोषणा SUN4I_HDMI_DDC_INT_STATUS_ACK_ERROR			BIT(2)
#घोषणा SUN4I_HDMI_DDC_INT_STATUS_BUS_ERROR			BIT(1)
#घोषणा SUN4I_HDMI_DDC_INT_STATUS_TRANSFER_COMPLETE		BIT(0)

#घोषणा SUN4I_HDMI_DDC_FIFO_CTRL_REG	0x510
#घोषणा SUN4I_HDMI_DDC_FIFO_CTRL_CLEAR		BIT(31)
#घोषणा SUN4I_HDMI_DDC_FIFO_CTRL_RX_THRES(n)	(((n) & 0xf) << 4)
#घोषणा SUN4I_HDMI_DDC_FIFO_CTRL_RX_THRES_MASK	GENMASK(7, 4)
#घोषणा SUN4I_HDMI_DDC_FIFO_CTRL_RX_THRES_MAX	(BIT(4) - 1)
#घोषणा SUN4I_HDMI_DDC_FIFO_CTRL_TX_THRES(n)	((n) & 0xf)
#घोषणा SUN4I_HDMI_DDC_FIFO_CTRL_TX_THRES_MASK	GENMASK(3, 0)
#घोषणा SUN4I_HDMI_DDC_FIFO_CTRL_TX_THRES_MAX	(BIT(4) - 1)

#घोषणा SUN4I_HDMI_DDC_FIFO_DATA_REG	0x518

#घोषणा SUN4I_HDMI_DDC_BYTE_COUNT_REG	0x51c
#घोषणा SUN4I_HDMI_DDC_BYTE_COUNT_MAX		(BIT(10) - 1)

#घोषणा SUN4I_HDMI_DDC_CMD_REG		0x520
#घोषणा SUN4I_HDMI_DDC_CMD_EXPLICIT_EDDC_READ	6
#घोषणा SUN4I_HDMI_DDC_CMD_IMPLICIT_READ	5
#घोषणा SUN4I_HDMI_DDC_CMD_IMPLICIT_WRITE	3

#घोषणा SUN4I_HDMI_DDC_CLK_REG		0x528
#घोषणा SUN4I_HDMI_DDC_CLK_M(m)			(((m) & 0xf) << 3)
#घोषणा SUN4I_HDMI_DDC_CLK_N(n)			((n) & 0x7)

#घोषणा SUN4I_HDMI_DDC_LINE_CTRL_REG	0x540
#घोषणा SUN4I_HDMI_DDC_LINE_CTRL_SDA_ENABLE	BIT(9)
#घोषणा SUN4I_HDMI_DDC_LINE_CTRL_SCL_ENABLE	BIT(8)

#घोषणा SUN4I_HDMI_DDC_FIFO_SIZE	16

/* A31 specअगरic */
#घोषणा SUN6I_HDMI_DDC_CTRL_REG		0x500
#घोषणा SUN6I_HDMI_DDC_CTRL_RESET		BIT(31)
#घोषणा SUN6I_HDMI_DDC_CTRL_START_CMD		BIT(27)
#घोषणा SUN6I_HDMI_DDC_CTRL_SDA_ENABLE		BIT(6)
#घोषणा SUN6I_HDMI_DDC_CTRL_SCL_ENABLE		BIT(4)
#घोषणा SUN6I_HDMI_DDC_CTRL_ENABLE		BIT(0)

#घोषणा SUN6I_HDMI_DDC_CMD_REG		0x508
#घोषणा SUN6I_HDMI_DDC_CMD_BYTE_COUNT(count)	((count) << 16)
/* command types in lower 3 bits are the same as sun4i */

#घोषणा SUN6I_HDMI_DDC_ADDR_REG		0x50c
#घोषणा SUN6I_HDMI_DDC_ADDR_SEGMENT(seg)	(((seg) & 0xff) << 24)
#घोषणा SUN6I_HDMI_DDC_ADDR_EDDC(addr)		(((addr) & 0xff) << 16)
#घोषणा SUN6I_HDMI_DDC_ADDR_OFFSET(off)		(((off) & 0xff) << 8)
#घोषणा SUN6I_HDMI_DDC_ADDR_SLAVE(addr)		(((addr) & 0xff) << 1)

#घोषणा SUN6I_HDMI_DDC_INT_STATUS_REG	0x514
#घोषणा SUN6I_HDMI_DDC_INT_STATUS_TIMEOUT	BIT(8)
/* lower 8 bits are the same as sun4i */

#घोषणा SUN6I_HDMI_DDC_FIFO_CTRL_REG	0x518
#घोषणा SUN6I_HDMI_DDC_FIFO_CTRL_CLEAR		BIT(15)
/* lower 9 bits are the same as sun4i */

#घोषणा SUN6I_HDMI_DDC_CLK_REG		0x520
/* DDC CLK bit fields are the same, but the क्रमmula is not */

#घोषणा SUN6I_HDMI_DDC_FIFO_DATA_REG	0x580

क्रमागत sun4i_hdmi_pkt_type अणु
	SUN4I_HDMI_PKT_AVI = 2,
	SUN4I_HDMI_PKT_END = 15,
पूर्ण;

काष्ठा sun4i_hdmi_variant अणु
	bool has_ddc_parent_clk;
	bool has_reset_control;

	u32 pad_ctrl0_init_val;
	u32 pad_ctrl1_init_val;
	u32 pll_ctrl_init_val;

	काष्ठा reg_field ddc_clk_reg;
	u8 ddc_clk_pre_भागider;
	u8 ddc_clk_m_offset;

	u8 पंचांगds_clk_भाग_offset;

	/* Register fields क्रम I2C adapter */
	काष्ठा reg_field	field_ddc_en;
	काष्ठा reg_field	field_ddc_start;
	काष्ठा reg_field	field_ddc_reset;
	काष्ठा reg_field	field_ddc_addr_reg;
	काष्ठा reg_field	field_ddc_slave_addr;
	काष्ठा reg_field	field_ddc_पूर्णांक_mask;
	काष्ठा reg_field	field_ddc_पूर्णांक_status;
	काष्ठा reg_field	field_ddc_fअगरo_clear;
	काष्ठा reg_field	field_ddc_fअगरo_rx_thres;
	काष्ठा reg_field	field_ddc_fअगरo_tx_thres;
	काष्ठा reg_field	field_ddc_byte_count;
	काष्ठा reg_field	field_ddc_cmd;
	काष्ठा reg_field	field_ddc_sda_en;
	काष्ठा reg_field	field_ddc_sck_en;

	/* DDC FIFO रेजिस्टर offset */
	u32			ddc_fअगरo_reg;

	/*
	 * DDC FIFO threshold boundary conditions
	 *
	 * This is used to cope with the threshold boundary condition
	 * being slightly dअगरferent on sun5i and sun6i.
	 *
	 * On sun5i the threshold is exclusive, i.e. करोes not include,
	 * the value of the threshold. ( > क्रम RX; < क्रम TX )
	 * On sun6i the threshold is inclusive, i.e. includes, the
	 * value of the threshold. ( >= क्रम RX; <= क्रम TX )
	 */
	bool			ddc_fअगरo_thres_incl;

	bool			ddc_fअगरo_has_dir;
पूर्ण;

काष्ठा sun4i_hdmi अणु
	काष्ठा drm_connector	connector;
	काष्ठा drm_encoder	encoder;
	काष्ठा device		*dev;

	व्योम __iomem		*base;
	काष्ठा regmap		*regmap;

	/* Reset control */
	काष्ठा reset_control	*reset;

	/* Parent घड़ीs */
	काष्ठा clk		*bus_clk;
	काष्ठा clk		*mod_clk;
	काष्ठा clk		*ddc_parent_clk;
	काष्ठा clk		*pll0_clk;
	काष्ठा clk		*pll1_clk;

	/* And the घड़ीs we create */
	काष्ठा clk		*ddc_clk;
	काष्ठा clk		*पंचांगds_clk;

	काष्ठा i2c_adapter	*i2c;
	काष्ठा i2c_adapter	*ddc_i2c;

	/* Regmap fields क्रम I2C adapter */
	काष्ठा regmap_field	*field_ddc_en;
	काष्ठा regmap_field	*field_ddc_start;
	काष्ठा regmap_field	*field_ddc_reset;
	काष्ठा regmap_field	*field_ddc_addr_reg;
	काष्ठा regmap_field	*field_ddc_slave_addr;
	काष्ठा regmap_field	*field_ddc_पूर्णांक_mask;
	काष्ठा regmap_field	*field_ddc_पूर्णांक_status;
	काष्ठा regmap_field	*field_ddc_fअगरo_clear;
	काष्ठा regmap_field	*field_ddc_fअगरo_rx_thres;
	काष्ठा regmap_field	*field_ddc_fअगरo_tx_thres;
	काष्ठा regmap_field	*field_ddc_byte_count;
	काष्ठा regmap_field	*field_ddc_cmd;
	काष्ठा regmap_field	*field_ddc_sda_en;
	काष्ठा regmap_field	*field_ddc_sck_en;

	काष्ठा sun4i_drv	*drv;

	bool			hdmi_monitor;
	काष्ठा cec_adapter	*cec_adap;

	स्थिर काष्ठा sun4i_hdmi_variant	*variant;
पूर्ण;

पूर्णांक sun4i_ddc_create(काष्ठा sun4i_hdmi *hdmi, काष्ठा clk *clk);
पूर्णांक sun4i_पंचांगds_create(काष्ठा sun4i_hdmi *hdmi);
पूर्णांक sun4i_hdmi_i2c_create(काष्ठा device *dev, काष्ठा sun4i_hdmi *hdmi);

#पूर्ण_अगर /* _SUN4I_HDMI_H_ */
