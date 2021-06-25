<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Renesas R-Car MIPI CSI-2 Receiver
 *
 * Copyright (C) 2018 Renesas Electronics Corp.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/sys_soc.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-subdev.h>

काष्ठा rcar_csi2;

/* Register offsets and bits */

/* Control Timing Select */
#घोषणा TREF_REG			0x00
#घोषणा TREF_TREF			BIT(0)

/* Software Reset */
#घोषणा SRST_REG			0x04
#घोषणा SRST_SRST			BIT(0)

/* PHY Operation Control */
#घोषणा PHYCNT_REG			0x08
#घोषणा PHYCNT_SHUTDOWNZ		BIT(17)
#घोषणा PHYCNT_RSTZ			BIT(16)
#घोषणा PHYCNT_ENABLECLK		BIT(4)
#घोषणा PHYCNT_ENABLE_3			BIT(3)
#घोषणा PHYCNT_ENABLE_2			BIT(2)
#घोषणा PHYCNT_ENABLE_1			BIT(1)
#घोषणा PHYCNT_ENABLE_0			BIT(0)

/* Checksum Control */
#घोषणा CHKSUM_REG			0x0c
#घोषणा CHKSUM_ECC_EN			BIT(1)
#घोषणा CHKSUM_CRC_EN			BIT(0)

/*
 * Channel Data Type Select
 * VCDT[0-15]:  Channel 0 VCDT[16-31]:  Channel 1
 * VCDT2[0-15]: Channel 2 VCDT2[16-31]: Channel 3
 */
#घोषणा VCDT_REG			0x10
#घोषणा VCDT2_REG			0x14
#घोषणा VCDT_VCDTN_EN			BIT(15)
#घोषणा VCDT_SEL_VC(n)			(((n) & 0x3) << 8)
#घोषणा VCDT_SEL_DTN_ON			BIT(6)
#घोषणा VCDT_SEL_DT(n)			(((n) & 0x3f) << 0)

/* Frame Data Type Select */
#घोषणा FRDT_REG			0x18

/* Field Detection Control */
#घोषणा FLD_REG				0x1c
#घोषणा FLD_FLD_NUM(n)			(((n) & 0xff) << 16)
#घोषणा FLD_DET_SEL(n)			(((n) & 0x3) << 4)
#घोषणा FLD_FLD_EN4			BIT(3)
#घोषणा FLD_FLD_EN3			BIT(2)
#घोषणा FLD_FLD_EN2			BIT(1)
#घोषणा FLD_FLD_EN			BIT(0)

/* Automatic Standby Control */
#घोषणा ASTBY_REG			0x20

/* Long Data Type Setting 0 */
#घोषणा LNGDT0_REG			0x28

/* Long Data Type Setting 1 */
#घोषणा LNGDT1_REG			0x2c

/* Interrupt Enable */
#घोषणा INTEN_REG			0x30
#घोषणा INTEN_INT_AFIFO_OF		BIT(27)
#घोषणा INTEN_INT_ERRSOTHS		BIT(4)
#घोषणा INTEN_INT_ERRSOTSYNCHS		BIT(3)

/* Interrupt Source Mask */
#घोषणा INTCLOSE_REG			0x34

/* Interrupt Status Monitor */
#घोषणा INTSTATE_REG			0x38
#घोषणा INTSTATE_INT_ULPS_START		BIT(7)
#घोषणा INTSTATE_INT_ULPS_END		BIT(6)

/* Interrupt Error Status Monitor */
#घोषणा INTERRSTATE_REG			0x3c

/* Short Packet Data */
#घोषणा SHPDAT_REG			0x40

/* Short Packet Count */
#घोषणा SHPCNT_REG			0x44

/* LINK Operation Control */
#घोषणा LINKCNT_REG			0x48
#घोषणा LINKCNT_MONITOR_EN		BIT(31)
#घोषणा LINKCNT_REG_MONI_PACT_EN	BIT(25)
#घोषणा LINKCNT_ICLK_NONSTOP		BIT(24)

/* Lane Swap */
#घोषणा LSWAP_REG			0x4c
#घोषणा LSWAP_L3SEL(n)			(((n) & 0x3) << 6)
#घोषणा LSWAP_L2SEL(n)			(((n) & 0x3) << 4)
#घोषणा LSWAP_L1SEL(n)			(((n) & 0x3) << 2)
#घोषणा LSWAP_L0SEL(n)			(((n) & 0x3) << 0)

/* PHY Test Interface Write Register */
#घोषणा PHTW_REG			0x50
#घोषणा PHTW_DWEN			BIT(24)
#घोषणा PHTW_TESTDIN_DATA(n)		(((n & 0xff)) << 16)
#घोषणा PHTW_CWEN			BIT(8)
#घोषणा PHTW_TESTDIN_CODE(n)		((n & 0xff))

काष्ठा phtw_value अणु
	u16 data;
	u16 code;
पूर्ण;

काष्ठा rcsi2_mbps_reg अणु
	u16 mbps;
	u16 reg;
पूर्ण;

अटल स्थिर काष्ठा rcsi2_mbps_reg phtw_mbps_h3_v3h_m3n[] = अणु
	अणु .mbps =   80, .reg = 0x86 पूर्ण,
	अणु .mbps =   90, .reg = 0x86 पूर्ण,
	अणु .mbps =  100, .reg = 0x87 पूर्ण,
	अणु .mbps =  110, .reg = 0x87 पूर्ण,
	अणु .mbps =  120, .reg = 0x88 पूर्ण,
	अणु .mbps =  130, .reg = 0x88 पूर्ण,
	अणु .mbps =  140, .reg = 0x89 पूर्ण,
	अणु .mbps =  150, .reg = 0x89 पूर्ण,
	अणु .mbps =  160, .reg = 0x8a पूर्ण,
	अणु .mbps =  170, .reg = 0x8a पूर्ण,
	अणु .mbps =  180, .reg = 0x8b पूर्ण,
	अणु .mbps =  190, .reg = 0x8b पूर्ण,
	अणु .mbps =  205, .reg = 0x8c पूर्ण,
	अणु .mbps =  220, .reg = 0x8d पूर्ण,
	अणु .mbps =  235, .reg = 0x8e पूर्ण,
	अणु .mbps =  250, .reg = 0x8e पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rcsi2_mbps_reg phtw_mbps_v3m_e3[] = अणु
	अणु .mbps =   80, .reg = 0x00 पूर्ण,
	अणु .mbps =   90, .reg = 0x20 पूर्ण,
	अणु .mbps =  100, .reg = 0x40 पूर्ण,
	अणु .mbps =  110, .reg = 0x02 पूर्ण,
	अणु .mbps =  130, .reg = 0x22 पूर्ण,
	अणु .mbps =  140, .reg = 0x42 पूर्ण,
	अणु .mbps =  150, .reg = 0x04 पूर्ण,
	अणु .mbps =  170, .reg = 0x24 पूर्ण,
	अणु .mbps =  180, .reg = 0x44 पूर्ण,
	अणु .mbps =  200, .reg = 0x06 पूर्ण,
	अणु .mbps =  220, .reg = 0x26 पूर्ण,
	अणु .mbps =  240, .reg = 0x46 पूर्ण,
	अणु .mbps =  250, .reg = 0x08 पूर्ण,
	अणु .mbps =  270, .reg = 0x28 पूर्ण,
	अणु .mbps =  300, .reg = 0x0a पूर्ण,
	अणु .mbps =  330, .reg = 0x2a पूर्ण,
	अणु .mbps =  360, .reg = 0x4a पूर्ण,
	अणु .mbps =  400, .reg = 0x0c पूर्ण,
	अणु .mbps =  450, .reg = 0x2c पूर्ण,
	अणु .mbps =  500, .reg = 0x0e पूर्ण,
	अणु .mbps =  550, .reg = 0x2e पूर्ण,
	अणु .mbps =  600, .reg = 0x10 पूर्ण,
	अणु .mbps =  650, .reg = 0x30 पूर्ण,
	अणु .mbps =  700, .reg = 0x12 पूर्ण,
	अणु .mbps =  750, .reg = 0x32 पूर्ण,
	अणु .mbps =  800, .reg = 0x52 पूर्ण,
	अणु .mbps =  850, .reg = 0x72 पूर्ण,
	अणु .mbps =  900, .reg = 0x14 पूर्ण,
	अणु .mbps =  950, .reg = 0x34 पूर्ण,
	अणु .mbps = 1000, .reg = 0x54 पूर्ण,
	अणु .mbps = 1050, .reg = 0x74 पूर्ण,
	अणु .mbps = 1125, .reg = 0x16 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

/* PHY Test Interface Clear */
#घोषणा PHTC_REG			0x58
#घोषणा PHTC_TESTCLR			BIT(0)

/* PHY Frequency Control */
#घोषणा PHYPLL_REG			0x68
#घोषणा PHYPLL_HSFREQRANGE(n)		((n) << 16)

अटल स्थिर काष्ठा rcsi2_mbps_reg hsfreqrange_h3_v3h_m3n[] = अणु
	अणु .mbps =   80, .reg = 0x00 पूर्ण,
	अणु .mbps =   90, .reg = 0x10 पूर्ण,
	अणु .mbps =  100, .reg = 0x20 पूर्ण,
	अणु .mbps =  110, .reg = 0x30 पूर्ण,
	अणु .mbps =  120, .reg = 0x01 पूर्ण,
	अणु .mbps =  130, .reg = 0x11 पूर्ण,
	अणु .mbps =  140, .reg = 0x21 पूर्ण,
	अणु .mbps =  150, .reg = 0x31 पूर्ण,
	अणु .mbps =  160, .reg = 0x02 पूर्ण,
	अणु .mbps =  170, .reg = 0x12 पूर्ण,
	अणु .mbps =  180, .reg = 0x22 पूर्ण,
	अणु .mbps =  190, .reg = 0x32 पूर्ण,
	अणु .mbps =  205, .reg = 0x03 पूर्ण,
	अणु .mbps =  220, .reg = 0x13 पूर्ण,
	अणु .mbps =  235, .reg = 0x23 पूर्ण,
	अणु .mbps =  250, .reg = 0x33 पूर्ण,
	अणु .mbps =  275, .reg = 0x04 पूर्ण,
	अणु .mbps =  300, .reg = 0x14 पूर्ण,
	अणु .mbps =  325, .reg = 0x25 पूर्ण,
	अणु .mbps =  350, .reg = 0x35 पूर्ण,
	अणु .mbps =  400, .reg = 0x05 पूर्ण,
	अणु .mbps =  450, .reg = 0x16 पूर्ण,
	अणु .mbps =  500, .reg = 0x26 पूर्ण,
	अणु .mbps =  550, .reg = 0x37 पूर्ण,
	अणु .mbps =  600, .reg = 0x07 पूर्ण,
	अणु .mbps =  650, .reg = 0x18 पूर्ण,
	अणु .mbps =  700, .reg = 0x28 पूर्ण,
	अणु .mbps =  750, .reg = 0x39 पूर्ण,
	अणु .mbps =  800, .reg = 0x09 पूर्ण,
	अणु .mbps =  850, .reg = 0x19 पूर्ण,
	अणु .mbps =  900, .reg = 0x29 पूर्ण,
	अणु .mbps =  950, .reg = 0x3a पूर्ण,
	अणु .mbps = 1000, .reg = 0x0a पूर्ण,
	अणु .mbps = 1050, .reg = 0x1a पूर्ण,
	अणु .mbps = 1100, .reg = 0x2a पूर्ण,
	अणु .mbps = 1150, .reg = 0x3b पूर्ण,
	अणु .mbps = 1200, .reg = 0x0b पूर्ण,
	अणु .mbps = 1250, .reg = 0x1b पूर्ण,
	अणु .mbps = 1300, .reg = 0x2b पूर्ण,
	अणु .mbps = 1350, .reg = 0x3c पूर्ण,
	अणु .mbps = 1400, .reg = 0x0c पूर्ण,
	अणु .mbps = 1450, .reg = 0x1c पूर्ण,
	अणु .mbps = 1500, .reg = 0x2c पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rcsi2_mbps_reg hsfreqrange_m3w_h3es1[] = अणु
	अणु .mbps =   80,	.reg = 0x00 पूर्ण,
	अणु .mbps =   90,	.reg = 0x10 पूर्ण,
	अणु .mbps =  100,	.reg = 0x20 पूर्ण,
	अणु .mbps =  110,	.reg = 0x30 पूर्ण,
	अणु .mbps =  120,	.reg = 0x01 पूर्ण,
	अणु .mbps =  130,	.reg = 0x11 पूर्ण,
	अणु .mbps =  140,	.reg = 0x21 पूर्ण,
	अणु .mbps =  150,	.reg = 0x31 पूर्ण,
	अणु .mbps =  160,	.reg = 0x02 पूर्ण,
	अणु .mbps =  170,	.reg = 0x12 पूर्ण,
	अणु .mbps =  180,	.reg = 0x22 पूर्ण,
	अणु .mbps =  190,	.reg = 0x32 पूर्ण,
	अणु .mbps =  205,	.reg = 0x03 पूर्ण,
	अणु .mbps =  220,	.reg = 0x13 पूर्ण,
	अणु .mbps =  235,	.reg = 0x23 पूर्ण,
	अणु .mbps =  250,	.reg = 0x33 पूर्ण,
	अणु .mbps =  275,	.reg = 0x04 पूर्ण,
	अणु .mbps =  300,	.reg = 0x14 पूर्ण,
	अणु .mbps =  325,	.reg = 0x05 पूर्ण,
	अणु .mbps =  350,	.reg = 0x15 पूर्ण,
	अणु .mbps =  400,	.reg = 0x25 पूर्ण,
	अणु .mbps =  450,	.reg = 0x06 पूर्ण,
	अणु .mbps =  500,	.reg = 0x16 पूर्ण,
	अणु .mbps =  550,	.reg = 0x07 पूर्ण,
	अणु .mbps =  600,	.reg = 0x17 पूर्ण,
	अणु .mbps =  650,	.reg = 0x08 पूर्ण,
	अणु .mbps =  700,	.reg = 0x18 पूर्ण,
	अणु .mbps =  750,	.reg = 0x09 पूर्ण,
	अणु .mbps =  800,	.reg = 0x19 पूर्ण,
	अणु .mbps =  850,	.reg = 0x29 पूर्ण,
	अणु .mbps =  900,	.reg = 0x39 पूर्ण,
	अणु .mbps =  950,	.reg = 0x0a पूर्ण,
	अणु .mbps = 1000,	.reg = 0x1a पूर्ण,
	अणु .mbps = 1050,	.reg = 0x2a पूर्ण,
	अणु .mbps = 1100,	.reg = 0x3a पूर्ण,
	अणु .mbps = 1150,	.reg = 0x0b पूर्ण,
	अणु .mbps = 1200,	.reg = 0x1b पूर्ण,
	अणु .mbps = 1250,	.reg = 0x2b पूर्ण,
	अणु .mbps = 1300,	.reg = 0x3b पूर्ण,
	अणु .mbps = 1350,	.reg = 0x0c पूर्ण,
	अणु .mbps = 1400,	.reg = 0x1c पूर्ण,
	अणु .mbps = 1450,	.reg = 0x2c पूर्ण,
	अणु .mbps = 1500,	.reg = 0x3c पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

/* PHY ESC Error Monitor */
#घोषणा PHEERM_REG			0x74

/* PHY Clock Lane Monitor */
#घोषणा PHCLM_REG			0x78
#घोषणा PHCLM_STOPSTATECKL		BIT(0)

/* PHY Data Lane Monitor */
#घोषणा PHDLM_REG			0x7c

/* CSI0CLK Frequency Configuration Preset Register */
#घोषणा CSI0CLKFCPR_REG			0x260
#घोषणा CSI0CLKFREQRANGE(n)		((n & 0x3f) << 16)

काष्ठा rcar_csi2_क्रमmat अणु
	u32 code;
	अचिन्हित पूर्णांक datatype;
	अचिन्हित पूर्णांक bpp;
पूर्ण;

अटल स्थिर काष्ठा rcar_csi2_क्रमmat rcar_csi2_क्रमmats[] = अणु
	अणु .code = MEDIA_BUS_FMT_RGB888_1X24,	.datatype = 0x24, .bpp = 24 पूर्ण,
	अणु .code = MEDIA_BUS_FMT_UYVY8_1X16,	.datatype = 0x1e, .bpp = 16 पूर्ण,
	अणु .code = MEDIA_BUS_FMT_YUYV8_1X16,	.datatype = 0x1e, .bpp = 16 पूर्ण,
	अणु .code = MEDIA_BUS_FMT_UYVY8_2X8,	.datatype = 0x1e, .bpp = 16 पूर्ण,
	अणु .code = MEDIA_BUS_FMT_YUYV10_2X10,	.datatype = 0x1e, .bpp = 20 पूर्ण,
	अणु .code = MEDIA_BUS_FMT_SBGGR8_1X8,     .datatype = 0x2a, .bpp = 8 पूर्ण,
	अणु .code = MEDIA_BUS_FMT_SGBRG8_1X8,     .datatype = 0x2a, .bpp = 8 पूर्ण,
	अणु .code = MEDIA_BUS_FMT_SGRBG8_1X8,     .datatype = 0x2a, .bpp = 8 पूर्ण,
	अणु .code = MEDIA_BUS_FMT_SRGGB8_1X8,     .datatype = 0x2a, .bpp = 8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rcar_csi2_क्रमmat *rcsi2_code_to_fmt(अचिन्हित पूर्णांक code)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rcar_csi2_क्रमmats); i++)
		अगर (rcar_csi2_क्रमmats[i].code == code)
			वापस &rcar_csi2_क्रमmats[i];

	वापस शून्य;
पूर्ण

क्रमागत rcar_csi2_pads अणु
	RCAR_CSI2_SINK,
	RCAR_CSI2_SOURCE_VC0,
	RCAR_CSI2_SOURCE_VC1,
	RCAR_CSI2_SOURCE_VC2,
	RCAR_CSI2_SOURCE_VC3,
	NR_OF_RCAR_CSI2_PAD,
पूर्ण;

काष्ठा rcar_csi2_info अणु
	पूर्णांक (*init_phtw)(काष्ठा rcar_csi2 *priv, अचिन्हित पूर्णांक mbps);
	पूर्णांक (*phy_post_init)(काष्ठा rcar_csi2 *priv);
	स्थिर काष्ठा rcsi2_mbps_reg *hsfreqrange;
	अचिन्हित पूर्णांक csi0clkfreqrange;
	अचिन्हित पूर्णांक num_channels;
	bool clear_ulps;
पूर्ण;

काष्ठा rcar_csi2 अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	स्थिर काष्ठा rcar_csi2_info *info;
	काष्ठा reset_control *rstc;

	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[NR_OF_RCAR_CSI2_PAD];

	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा v4l2_subdev *remote;
	अचिन्हित पूर्णांक remote_pad;

	काष्ठा v4l2_mbus_framefmt mf;

	काष्ठा mutex lock;
	पूर्णांक stream_count;

	अचिन्हित लघु lanes;
	अचिन्हित अक्षर lane_swap[4];
पूर्ण;

अटल अंतरभूत काष्ठा rcar_csi2 *sd_to_csi2(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा rcar_csi2, subdev);
पूर्ण

अटल अंतरभूत काष्ठा rcar_csi2 *notअगरier_to_csi2(काष्ठा v4l2_async_notअगरier *n)
अणु
	वापस container_of(n, काष्ठा rcar_csi2, notअगरier);
पूर्ण

अटल u32 rcsi2_पढ़ो(काष्ठा rcar_csi2 *priv, अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो32(priv->base + reg);
पूर्ण

अटल व्योम rcsi2_ग_लिखो(काष्ठा rcar_csi2 *priv, अचिन्हित पूर्णांक reg, u32 data)
अणु
	ioग_लिखो32(data, priv->base + reg);
पूर्ण

अटल व्योम rcsi2_enter_standby(काष्ठा rcar_csi2 *priv)
अणु
	rcsi2_ग_लिखो(priv, PHYCNT_REG, 0);
	rcsi2_ग_लिखो(priv, PHTC_REG, PHTC_TESTCLR);
	reset_control_निश्चित(priv->rstc);
	usleep_range(100, 150);
	pm_runसमय_put(priv->dev);
पूर्ण

अटल व्योम rcsi2_निकास_standby(काष्ठा rcar_csi2 *priv)
अणु
	pm_runसमय_get_sync(priv->dev);
	reset_control_deनिश्चित(priv->rstc);
पूर्ण

अटल पूर्णांक rcsi2_रुको_phy_start(काष्ठा rcar_csi2 *priv,
				अचिन्हित पूर्णांक lanes)
अणु
	अचिन्हित पूर्णांक समयout;

	/* Wait क्रम the घड़ी and data lanes to enter LP-11 state. */
	क्रम (समयout = 0; समयout <= 20; समयout++) अणु
		स्थिर u32 lane_mask = (1 << lanes) - 1;

		अगर ((rcsi2_पढ़ो(priv, PHCLM_REG) & PHCLM_STOPSTATECKL)  &&
		    (rcsi2_पढ़ो(priv, PHDLM_REG) & lane_mask) == lane_mask)
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण

	dev_err(priv->dev, "Timeout waiting for LP-11 state\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक rcsi2_set_phypll(काष्ठा rcar_csi2 *priv, अचिन्हित पूर्णांक mbps)
अणु
	स्थिर काष्ठा rcsi2_mbps_reg *hsfreq;

	क्रम (hsfreq = priv->info->hsfreqrange; hsfreq->mbps != 0; hsfreq++)
		अगर (hsfreq->mbps >= mbps)
			अवरोध;

	अगर (!hsfreq->mbps) अणु
		dev_err(priv->dev, "Unsupported PHY speed (%u Mbps)", mbps);
		वापस -दुस्फल;
	पूर्ण

	rcsi2_ग_लिखो(priv, PHYPLL_REG, PHYPLL_HSFREQRANGE(hsfreq->reg));

	वापस 0;
पूर्ण

अटल पूर्णांक rcsi2_calc_mbps(काष्ठा rcar_csi2 *priv, अचिन्हित पूर्णांक bpp,
			   अचिन्हित पूर्णांक lanes)
अणु
	काष्ठा v4l2_subdev *source;
	काष्ठा v4l2_ctrl *ctrl;
	u64 mbps;

	अगर (!priv->remote)
		वापस -ENODEV;

	source = priv->remote;

	/* Read the pixel rate control from remote. */
	ctrl = v4l2_ctrl_find(source->ctrl_handler, V4L2_CID_PIXEL_RATE);
	अगर (!ctrl) अणु
		dev_err(priv->dev, "no pixel rate control in subdev %s\n",
			source->name);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Calculate the phypll in mbps.
	 * link_freq = (pixel_rate * bits_per_sample) / (2 * nr_of_lanes)
	 * bps = link_freq * 2
	 */
	mbps = v4l2_ctrl_g_ctrl_पूर्णांक64(ctrl) * bpp;
	करो_भाग(mbps, lanes * 1000000);

	वापस mbps;
पूर्ण

अटल पूर्णांक rcsi2_get_active_lanes(काष्ठा rcar_csi2 *priv,
				  अचिन्हित पूर्णांक *lanes)
अणु
	काष्ठा v4l2_mbus_config mbus_config = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक num_lanes = अच_पूर्णांक_उच्च;
	पूर्णांक ret;

	*lanes = priv->lanes;

	ret = v4l2_subdev_call(priv->remote, pad, get_mbus_config,
			       priv->remote_pad, &mbus_config);
	अगर (ret == -ENOIOCTLCMD) अणु
		dev_dbg(priv->dev, "No remote mbus configuration available\n");
		वापस 0;
	पूर्ण

	अगर (ret) अणु
		dev_err(priv->dev, "Failed to get remote mbus configuration\n");
		वापस ret;
	पूर्ण

	अगर (mbus_config.type != V4L2_MBUS_CSI2_DPHY) अणु
		dev_err(priv->dev, "Unsupported media bus type %u\n",
			mbus_config.type);
		वापस -EINVAL;
	पूर्ण

	अगर (mbus_config.flags & V4L2_MBUS_CSI2_1_LANE)
		num_lanes = 1;
	अन्यथा अगर (mbus_config.flags & V4L2_MBUS_CSI2_2_LANE)
		num_lanes = 2;
	अन्यथा अगर (mbus_config.flags & V4L2_MBUS_CSI2_3_LANE)
		num_lanes = 3;
	अन्यथा अगर (mbus_config.flags & V4L2_MBUS_CSI2_4_LANE)
		num_lanes = 4;

	अगर (num_lanes > priv->lanes) अणु
		dev_err(priv->dev,
			"Unsupported mbus config: too many data lanes %u\n",
			num_lanes);
		वापस -EINVAL;
	पूर्ण

	*lanes = num_lanes;

	वापस 0;
पूर्ण

अटल पूर्णांक rcsi2_start_receiver(काष्ठा rcar_csi2 *priv)
अणु
	स्थिर काष्ठा rcar_csi2_क्रमmat *क्रमmat;
	u32 phycnt, vcdt = 0, vcdt2 = 0, fld = 0;
	अचिन्हित पूर्णांक lanes;
	अचिन्हित पूर्णांक i;
	पूर्णांक mbps, ret;

	dev_dbg(priv->dev, "Input size (%ux%u%c)\n",
		priv->mf.width, priv->mf.height,
		priv->mf.field == V4L2_FIELD_NONE ? 'p' : 'i');

	/* Code is validated in set_fmt. */
	क्रमmat = rcsi2_code_to_fmt(priv->mf.code);

	/*
	 * Enable all supported CSI-2 channels with भव channel and
	 * data type matching.
	 *
	 * NOTE: It's not possible to get inभागidual datatype क्रम each
	 *       source भव channel. Once this is possible in V4L2
	 *       it should be used here.
	 */
	क्रम (i = 0; i < priv->info->num_channels; i++) अणु
		u32 vcdt_part;

		vcdt_part = VCDT_SEL_VC(i) | VCDT_VCDTN_EN | VCDT_SEL_DTN_ON |
			VCDT_SEL_DT(क्रमmat->datatype);

		/* Store in correct reg and offset. */
		अगर (i < 2)
			vcdt |= vcdt_part << ((i % 2) * 16);
		अन्यथा
			vcdt2 |= vcdt_part << ((i % 2) * 16);
	पूर्ण

	अगर (priv->mf.field == V4L2_FIELD_ALTERNATE) अणु
		fld = FLD_DET_SEL(1) | FLD_FLD_EN4 | FLD_FLD_EN3 | FLD_FLD_EN2
			| FLD_FLD_EN;

		अगर (priv->mf.height == 240)
			fld |= FLD_FLD_NUM(0);
		अन्यथा
			fld |= FLD_FLD_NUM(1);
	पूर्ण

	/*
	 * Get the number of active data lanes inspecting the remote mbus
	 * configuration.
	 */
	ret = rcsi2_get_active_lanes(priv, &lanes);
	अगर (ret)
		वापस ret;

	phycnt = PHYCNT_ENABLECLK;
	phycnt |= (1 << lanes) - 1;

	mbps = rcsi2_calc_mbps(priv, क्रमmat->bpp, lanes);
	अगर (mbps < 0)
		वापस mbps;

	/* Enable पूर्णांकerrupts. */
	rcsi2_ग_लिखो(priv, INTEN_REG, INTEN_INT_AFIFO_OF | INTEN_INT_ERRSOTHS
		    | INTEN_INT_ERRSOTSYNCHS);

	/* Init */
	rcsi2_ग_लिखो(priv, TREF_REG, TREF_TREF);
	rcsi2_ग_लिखो(priv, PHTC_REG, 0);

	/* Configure */
	rcsi2_ग_लिखो(priv, VCDT_REG, vcdt);
	अगर (vcdt2)
		rcsi2_ग_लिखो(priv, VCDT2_REG, vcdt2);
	/* Lanes are zero indexed. */
	rcsi2_ग_लिखो(priv, LSWAP_REG,
		    LSWAP_L0SEL(priv->lane_swap[0] - 1) |
		    LSWAP_L1SEL(priv->lane_swap[1] - 1) |
		    LSWAP_L2SEL(priv->lane_swap[2] - 1) |
		    LSWAP_L3SEL(priv->lane_swap[3] - 1));

	/* Start */
	अगर (priv->info->init_phtw) अणु
		ret = priv->info->init_phtw(priv, mbps);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (priv->info->hsfreqrange) अणु
		ret = rcsi2_set_phypll(priv, mbps);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (priv->info->csi0clkfreqrange)
		rcsi2_ग_लिखो(priv, CSI0CLKFCPR_REG,
			    CSI0CLKFREQRANGE(priv->info->csi0clkfreqrange));

	rcsi2_ग_लिखो(priv, PHYCNT_REG, phycnt);
	rcsi2_ग_लिखो(priv, LINKCNT_REG, LINKCNT_MONITOR_EN |
		    LINKCNT_REG_MONI_PACT_EN | LINKCNT_ICLK_NONSTOP);
	rcsi2_ग_लिखो(priv, FLD_REG, fld);
	rcsi2_ग_लिखो(priv, PHYCNT_REG, phycnt | PHYCNT_SHUTDOWNZ);
	rcsi2_ग_लिखो(priv, PHYCNT_REG, phycnt | PHYCNT_SHUTDOWNZ | PHYCNT_RSTZ);

	ret = rcsi2_रुको_phy_start(priv, lanes);
	अगर (ret)
		वापस ret;

	/* Run post PHY start initialization, अगर needed. */
	अगर (priv->info->phy_post_init) अणु
		ret = priv->info->phy_post_init(priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Clear Ultra Low Power पूर्णांकerrupt. */
	अगर (priv->info->clear_ulps)
		rcsi2_ग_लिखो(priv, INTSTATE_REG,
			    INTSTATE_INT_ULPS_START |
			    INTSTATE_INT_ULPS_END);
	वापस 0;
पूर्ण

अटल पूर्णांक rcsi2_start(काष्ठा rcar_csi2 *priv)
अणु
	पूर्णांक ret;

	rcsi2_निकास_standby(priv);

	ret = rcsi2_start_receiver(priv);
	अगर (ret) अणु
		rcsi2_enter_standby(priv);
		वापस ret;
	पूर्ण

	ret = v4l2_subdev_call(priv->remote, video, s_stream, 1);
	अगर (ret) अणु
		rcsi2_enter_standby(priv);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rcsi2_stop(काष्ठा rcar_csi2 *priv)
अणु
	rcsi2_enter_standby(priv);
	v4l2_subdev_call(priv->remote, video, s_stream, 0);
पूर्ण

अटल पूर्णांक rcsi2_s_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	काष्ठा rcar_csi2 *priv = sd_to_csi2(sd);
	पूर्णांक ret = 0;

	mutex_lock(&priv->lock);

	अगर (!priv->remote) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (enable && priv->stream_count == 0) अणु
		ret = rcsi2_start(priv);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अगर (!enable && priv->stream_count == 1) अणु
		rcsi2_stop(priv);
	पूर्ण

	priv->stream_count += enable ? 1 : -1;
out:
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rcsi2_set_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा rcar_csi2 *priv = sd_to_csi2(sd);
	काष्ठा v4l2_mbus_framefmt *framefmt;

	अगर (!rcsi2_code_to_fmt(क्रमmat->क्रमmat.code))
		क्रमmat->क्रमmat.code = rcar_csi2_क्रमmats[0].code;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE) अणु
		priv->mf = क्रमmat->क्रमmat;
	पूर्ण अन्यथा अणु
		framefmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
		*framefmt = क्रमmat->क्रमmat;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rcsi2_get_pad_क्रमmat(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_subdev_pad_config *cfg,
				काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा rcar_csi2 *priv = sd_to_csi2(sd);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		क्रमmat->क्रमmat = priv->mf;
	अन्यथा
		क्रमmat->क्रमmat = *v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops rcar_csi2_video_ops = अणु
	.s_stream = rcsi2_s_stream,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_pad_ops rcar_csi2_pad_ops = अणु
	.set_fmt = rcsi2_set_pad_क्रमmat,
	.get_fmt = rcsi2_get_pad_क्रमmat,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops rcar_csi2_subdev_ops = अणु
	.video	= &rcar_csi2_video_ops,
	.pad	= &rcar_csi2_pad_ops,
पूर्ण;

अटल irqवापस_t rcsi2_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rcar_csi2 *priv = data;
	u32 status, err_status;

	status = rcsi2_पढ़ो(priv, INTSTATE_REG);
	err_status = rcsi2_पढ़ो(priv, INTERRSTATE_REG);

	अगर (!status)
		वापस IRQ_HANDLED;

	rcsi2_ग_लिखो(priv, INTSTATE_REG, status);

	अगर (!err_status)
		वापस IRQ_HANDLED;

	rcsi2_ग_लिखो(priv, INTERRSTATE_REG, err_status);

	dev_info(priv->dev, "Transfer error, restarting CSI-2 receiver\n");

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t rcsi2_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rcar_csi2 *priv = data;

	mutex_lock(&priv->lock);
	rcsi2_stop(priv);
	usleep_range(1000, 2000);
	अगर (rcsi2_start(priv))
		dev_warn(priv->dev, "Failed to restart CSI-2 receiver\n");
	mutex_unlock(&priv->lock);

	वापस IRQ_HANDLED;
पूर्ण

/* -----------------------------------------------------------------------------
 * Async handling and registration of subdevices and links.
 */

अटल पूर्णांक rcsi2_notअगरy_bound(काष्ठा v4l2_async_notअगरier *notअगरier,
			      काष्ठा v4l2_subdev *subdev,
			      काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा rcar_csi2 *priv = notअगरier_to_csi2(notअगरier);
	पूर्णांक pad;

	pad = media_entity_get_fwnode_pad(&subdev->entity, asd->match.fwnode,
					  MEDIA_PAD_FL_SOURCE);
	अगर (pad < 0) अणु
		dev_err(priv->dev, "Failed to find pad for %s\n", subdev->name);
		वापस pad;
	पूर्ण

	priv->remote = subdev;
	priv->remote_pad = pad;

	dev_dbg(priv->dev, "Bound %s pad: %d\n", subdev->name, pad);

	वापस media_create_pad_link(&subdev->entity, pad,
				     &priv->subdev.entity, 0,
				     MEDIA_LNK_FL_ENABLED |
				     MEDIA_LNK_FL_IMMUTABLE);
पूर्ण

अटल व्योम rcsi2_notअगरy_unbind(काष्ठा v4l2_async_notअगरier *notअगरier,
				काष्ठा v4l2_subdev *subdev,
				काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा rcar_csi2 *priv = notअगरier_to_csi2(notअगरier);

	priv->remote = शून्य;

	dev_dbg(priv->dev, "Unbind %s\n", subdev->name);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations rcar_csi2_notअगरy_ops = अणु
	.bound = rcsi2_notअगरy_bound,
	.unbind = rcsi2_notअगरy_unbind,
पूर्ण;

अटल पूर्णांक rcsi2_parse_v4l2(काष्ठा rcar_csi2 *priv,
			    काष्ठा v4l2_fwnode_endpoपूर्णांक *vep)
अणु
	अचिन्हित पूर्णांक i;

	/* Only port 0 endpoपूर्णांक 0 is valid. */
	अगर (vep->base.port || vep->base.id)
		वापस -ENOTCONN;

	अगर (vep->bus_type != V4L2_MBUS_CSI2_DPHY) अणु
		dev_err(priv->dev, "Unsupported bus: %u\n", vep->bus_type);
		वापस -EINVAL;
	पूर्ण

	priv->lanes = vep->bus.mipi_csi2.num_data_lanes;
	अगर (priv->lanes != 1 && priv->lanes != 2 && priv->lanes != 4) अणु
		dev_err(priv->dev, "Unsupported number of data-lanes: %u\n",
			priv->lanes);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(priv->lane_swap); i++) अणु
		priv->lane_swap[i] = i < priv->lanes ?
			vep->bus.mipi_csi2.data_lanes[i] : i;

		/* Check क्रम valid lane number. */
		अगर (priv->lane_swap[i] < 1 || priv->lane_swap[i] > 4) अणु
			dev_err(priv->dev, "data-lanes must be in 1-4 range\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rcsi2_parse_dt(काष्ठा rcar_csi2 *priv)
अणु
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा fwnode_handle *fwnode;
	काष्ठा fwnode_handle *ep;
	काष्ठा v4l2_fwnode_endpoपूर्णांक v4l2_ep = अणु
		.bus_type = V4L2_MBUS_CSI2_DPHY
	पूर्ण;
	पूर्णांक ret;

	ep = fwnode_graph_get_endpoपूर्णांक_by_id(dev_fwnode(priv->dev), 0, 0, 0);
	अगर (!ep) अणु
		dev_err(priv->dev, "Not connected to subdevice\n");
		वापस -EINVAL;
	पूर्ण

	ret = v4l2_fwnode_endpoपूर्णांक_parse(ep, &v4l2_ep);
	अगर (ret) अणु
		dev_err(priv->dev, "Could not parse v4l2 endpoint\n");
		fwnode_handle_put(ep);
		वापस -EINVAL;
	पूर्ण

	ret = rcsi2_parse_v4l2(priv, &v4l2_ep);
	अगर (ret) अणु
		fwnode_handle_put(ep);
		वापस ret;
	पूर्ण

	fwnode = fwnode_graph_get_remote_endpoपूर्णांक(ep);
	fwnode_handle_put(ep);

	dev_dbg(priv->dev, "Found '%pOF'\n", to_of_node(fwnode));

	v4l2_async_notअगरier_init(&priv->notअगरier);
	priv->notअगरier.ops = &rcar_csi2_notअगरy_ops;

	asd = v4l2_async_notअगरier_add_fwnode_subdev(&priv->notअगरier, fwnode,
						    काष्ठा v4l2_async_subdev);
	fwnode_handle_put(fwnode);
	अगर (IS_ERR(asd))
		वापस PTR_ERR(asd);

	ret = v4l2_async_subdev_notअगरier_रेजिस्टर(&priv->subdev,
						  &priv->notअगरier);
	अगर (ret)
		v4l2_async_notअगरier_cleanup(&priv->notअगरier);

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * PHTW initialization sequences.
 *
 * NOTE: Magic values are from the datasheet and lack करोcumentation.
 */

अटल पूर्णांक rcsi2_phtw_ग_लिखो(काष्ठा rcar_csi2 *priv, u16 data, u16 code)
अणु
	अचिन्हित पूर्णांक समयout;

	rcsi2_ग_लिखो(priv, PHTW_REG,
		    PHTW_DWEN | PHTW_TESTDIN_DATA(data) |
		    PHTW_CWEN | PHTW_TESTDIN_CODE(code));

	/* Wait क्रम DWEN and CWEN to be cleared by hardware. */
	क्रम (समयout = 0; समयout <= 20; समयout++) अणु
		अगर (!(rcsi2_पढ़ो(priv, PHTW_REG) & (PHTW_DWEN | PHTW_CWEN)))
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण

	dev_err(priv->dev, "Timeout waiting for PHTW_DWEN and/or PHTW_CWEN\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक rcsi2_phtw_ग_लिखो_array(काष्ठा rcar_csi2 *priv,
				  स्थिर काष्ठा phtw_value *values)
अणु
	स्थिर काष्ठा phtw_value *value;
	पूर्णांक ret;

	क्रम (value = values; value->data || value->code; value++) अणु
		ret = rcsi2_phtw_ग_लिखो(priv, value->data, value->code);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rcsi2_phtw_ग_लिखो_mbps(काष्ठा rcar_csi2 *priv, अचिन्हित पूर्णांक mbps,
				 स्थिर काष्ठा rcsi2_mbps_reg *values, u16 code)
अणु
	स्थिर काष्ठा rcsi2_mbps_reg *value;

	क्रम (value = values; value->mbps; value++)
		अगर (value->mbps >= mbps)
			अवरोध;

	अगर (!value->mbps) अणु
		dev_err(priv->dev, "Unsupported PHY speed (%u Mbps)", mbps);
		वापस -दुस्फल;
	पूर्ण

	वापस rcsi2_phtw_ग_लिखो(priv, value->reg, code);
पूर्ण

अटल पूर्णांक __rcsi2_init_phtw_h3_v3h_m3n(काष्ठा rcar_csi2 *priv,
					अचिन्हित पूर्णांक mbps)
अणु
	अटल स्थिर काष्ठा phtw_value step1[] = अणु
		अणु .data = 0xcc, .code = 0xe2 पूर्ण,
		अणु .data = 0x01, .code = 0xe3 पूर्ण,
		अणु .data = 0x11, .code = 0xe4 पूर्ण,
		अणु .data = 0x01, .code = 0xe5 पूर्ण,
		अणु .data = 0x10, .code = 0x04 पूर्ण,
		अणु /* sentinel */ पूर्ण,
	पूर्ण;

	अटल स्थिर काष्ठा phtw_value step2[] = अणु
		अणु .data = 0x38, .code = 0x08 पूर्ण,
		अणु .data = 0x01, .code = 0x00 पूर्ण,
		अणु .data = 0x4b, .code = 0xac पूर्ण,
		अणु .data = 0x03, .code = 0x00 पूर्ण,
		अणु .data = 0x80, .code = 0x07 पूर्ण,
		अणु /* sentinel */ पूर्ण,
	पूर्ण;

	पूर्णांक ret;

	ret = rcsi2_phtw_ग_लिखो_array(priv, step1);
	अगर (ret)
		वापस ret;

	अगर (mbps != 0 && mbps <= 250) अणु
		ret = rcsi2_phtw_ग_लिखो(priv, 0x39, 0x05);
		अगर (ret)
			वापस ret;

		ret = rcsi2_phtw_ग_लिखो_mbps(priv, mbps, phtw_mbps_h3_v3h_m3n,
					    0xf1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस rcsi2_phtw_ग_लिखो_array(priv, step2);
पूर्ण

अटल पूर्णांक rcsi2_init_phtw_h3_v3h_m3n(काष्ठा rcar_csi2 *priv, अचिन्हित पूर्णांक mbps)
अणु
	वापस __rcsi2_init_phtw_h3_v3h_m3n(priv, mbps);
पूर्ण

अटल पूर्णांक rcsi2_init_phtw_h3es2(काष्ठा rcar_csi2 *priv, अचिन्हित पूर्णांक mbps)
अणु
	वापस __rcsi2_init_phtw_h3_v3h_m3n(priv, 0);
पूर्ण

अटल पूर्णांक rcsi2_init_phtw_v3m_e3(काष्ठा rcar_csi2 *priv, अचिन्हित पूर्णांक mbps)
अणु
	वापस rcsi2_phtw_ग_लिखो_mbps(priv, mbps, phtw_mbps_v3m_e3, 0x44);
पूर्ण

अटल पूर्णांक rcsi2_phy_post_init_v3m_e3(काष्ठा rcar_csi2 *priv)
अणु
	अटल स्थिर काष्ठा phtw_value step1[] = अणु
		अणु .data = 0xee, .code = 0x34 पूर्ण,
		अणु .data = 0xee, .code = 0x44 पूर्ण,
		अणु .data = 0xee, .code = 0x54 पूर्ण,
		अणु .data = 0xee, .code = 0x84 पूर्ण,
		अणु .data = 0xee, .code = 0x94 पूर्ण,
		अणु /* sentinel */ पूर्ण,
	पूर्ण;

	वापस rcsi2_phtw_ग_लिखो_array(priv, step1);
पूर्ण

/* -----------------------------------------------------------------------------
 * Platक्रमm Device Driver.
 */

अटल स्थिर काष्ठा media_entity_operations rcar_csi2_entity_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

अटल पूर्णांक rcsi2_probe_resources(काष्ठा rcar_csi2 *priv,
				 काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	पूर्णांक irq, ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, rcsi2_irq,
					rcsi2_irq_thपढ़ो, IRQF_SHARED,
					KBUILD_MODNAME, priv);
	अगर (ret)
		वापस ret;

	priv->rstc = devm_reset_control_get(&pdev->dev, शून्य);

	वापस PTR_ERR_OR_ZERO(priv->rstc);
पूर्ण

अटल स्थिर काष्ठा rcar_csi2_info rcar_csi2_info_r8a7795 = अणु
	.init_phtw = rcsi2_init_phtw_h3_v3h_m3n,
	.hsfreqrange = hsfreqrange_h3_v3h_m3n,
	.csi0clkfreqrange = 0x20,
	.num_channels = 4,
	.clear_ulps = true,
पूर्ण;

अटल स्थिर काष्ठा rcar_csi2_info rcar_csi2_info_r8a7795es1 = अणु
	.hsfreqrange = hsfreqrange_m3w_h3es1,
	.num_channels = 4,
पूर्ण;

अटल स्थिर काष्ठा rcar_csi2_info rcar_csi2_info_r8a7795es2 = अणु
	.init_phtw = rcsi2_init_phtw_h3es2,
	.hsfreqrange = hsfreqrange_h3_v3h_m3n,
	.csi0clkfreqrange = 0x20,
	.num_channels = 4,
	.clear_ulps = true,
पूर्ण;

अटल स्थिर काष्ठा rcar_csi2_info rcar_csi2_info_r8a7796 = अणु
	.hsfreqrange = hsfreqrange_m3w_h3es1,
	.num_channels = 4,
पूर्ण;

अटल स्थिर काष्ठा rcar_csi2_info rcar_csi2_info_r8a77965 = अणु
	.init_phtw = rcsi2_init_phtw_h3_v3h_m3n,
	.hsfreqrange = hsfreqrange_h3_v3h_m3n,
	.csi0clkfreqrange = 0x20,
	.num_channels = 4,
	.clear_ulps = true,
पूर्ण;

अटल स्थिर काष्ठा rcar_csi2_info rcar_csi2_info_r8a77970 = अणु
	.init_phtw = rcsi2_init_phtw_v3m_e3,
	.phy_post_init = rcsi2_phy_post_init_v3m_e3,
	.num_channels = 4,
पूर्ण;

अटल स्थिर काष्ठा rcar_csi2_info rcar_csi2_info_r8a77980 = अणु
	.init_phtw = rcsi2_init_phtw_h3_v3h_m3n,
	.hsfreqrange = hsfreqrange_h3_v3h_m3n,
	.csi0clkfreqrange = 0x20,
	.clear_ulps = true,
पूर्ण;

अटल स्थिर काष्ठा rcar_csi2_info rcar_csi2_info_r8a77990 = अणु
	.init_phtw = rcsi2_init_phtw_v3m_e3,
	.phy_post_init = rcsi2_phy_post_init_v3m_e3,
	.num_channels = 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rcar_csi2_of_table[] = अणु
	अणु
		.compatible = "renesas,r8a774a1-csi2",
		.data = &rcar_csi2_info_r8a7796,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a774b1-csi2",
		.data = &rcar_csi2_info_r8a77965,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a774c0-csi2",
		.data = &rcar_csi2_info_r8a77990,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a774e1-csi2",
		.data = &rcar_csi2_info_r8a7795,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a7795-csi2",
		.data = &rcar_csi2_info_r8a7795,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a7796-csi2",
		.data = &rcar_csi2_info_r8a7796,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a77965-csi2",
		.data = &rcar_csi2_info_r8a77965,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a77970-csi2",
		.data = &rcar_csi2_info_r8a77970,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a77980-csi2",
		.data = &rcar_csi2_info_r8a77980,
	पूर्ण,
	अणु
		.compatible = "renesas,r8a77990-csi2",
		.data = &rcar_csi2_info_r8a77990,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_csi2_of_table);

अटल स्थिर काष्ठा soc_device_attribute r8a7795[] = अणु
	अणु
		.soc_id = "r8a7795", .revision = "ES1.*",
		.data = &rcar_csi2_info_r8a7795es1,
	पूर्ण,
	अणु
		.soc_id = "r8a7795", .revision = "ES2.*",
		.data = &rcar_csi2_info_r8a7795es2,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक rcsi2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा soc_device_attribute *attr;
	काष्ठा rcar_csi2 *priv;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->info = of_device_get_match_data(&pdev->dev);

	/*
	 * The dअगरferent ES versions of r8a7795 (H3) behave dअगरferently but
	 * share the same compatible string.
	 */
	attr = soc_device_match(r8a7795);
	अगर (attr)
		priv->info = attr->data;

	priv->dev = &pdev->dev;

	mutex_init(&priv->lock);
	priv->stream_count = 0;

	ret = rcsi2_probe_resources(priv, pdev);
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to get resources\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	ret = rcsi2_parse_dt(priv);
	अगर (ret)
		वापस ret;

	priv->subdev.owner = THIS_MODULE;
	priv->subdev.dev = &pdev->dev;
	v4l2_subdev_init(&priv->subdev, &rcar_csi2_subdev_ops);
	v4l2_set_subdevdata(&priv->subdev, &pdev->dev);
	snम_लिखो(priv->subdev.name, V4L2_SUBDEV_NAME_SIZE, "%s %s",
		 KBUILD_MODNAME, dev_name(&pdev->dev));
	priv->subdev.flags = V4L2_SUBDEV_FL_HAS_DEVNODE;

	priv->subdev.entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
	priv->subdev.entity.ops = &rcar_csi2_entity_ops;

	priv->pads[RCAR_CSI2_SINK].flags = MEDIA_PAD_FL_SINK;
	क्रम (i = RCAR_CSI2_SOURCE_VC0; i < NR_OF_RCAR_CSI2_PAD; i++)
		priv->pads[i].flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&priv->subdev.entity, NR_OF_RCAR_CSI2_PAD,
				     priv->pads);
	अगर (ret)
		जाओ error;

	pm_runसमय_enable(&pdev->dev);

	ret = v4l2_async_रेजिस्टर_subdev(&priv->subdev);
	अगर (ret < 0)
		जाओ error;

	dev_info(priv->dev, "%d lanes found\n", priv->lanes);

	वापस 0;

error:
	v4l2_async_notअगरier_unरेजिस्टर(&priv->notअगरier);
	v4l2_async_notअगरier_cleanup(&priv->notअगरier);

	वापस ret;
पूर्ण

अटल पूर्णांक rcsi2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_csi2 *priv = platक्रमm_get_drvdata(pdev);

	v4l2_async_notअगरier_unरेजिस्टर(&priv->notअगरier);
	v4l2_async_notअगरier_cleanup(&priv->notअगरier);
	v4l2_async_unरेजिस्टर_subdev(&priv->subdev);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rcar_csi2_pdrv = अणु
	.हटाओ	= rcsi2_हटाओ,
	.probe	= rcsi2_probe,
	.driver	= अणु
		.name	= "rcar-csi2",
		.of_match_table	= rcar_csi2_of_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rcar_csi2_pdrv);

MODULE_AUTHOR("Niklas Sथघderlund <niklas.soderlund@ragnatech.se>");
MODULE_DESCRIPTION("Renesas R-Car MIPI CSI-2 receiver driver");
MODULE_LICENSE("GPL");
