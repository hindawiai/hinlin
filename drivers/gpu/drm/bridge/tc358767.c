<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tc358767 eDP bridge driver
 *
 * Copyright (C) 2016 CogentEmbedded Inc
 * Author: Andrey Gusakov <andrey.gusakov@cogentembedded.com>
 *
 * Copyright (C) 2016 Pengutronix, Philipp Zabel <p.zabel@pengutronix.de>
 *
 * Copyright (C) 2016 Zodiac Inflight Innovations
 *
 * Initially based on: drivers/gpu/drm/i2c/tda998x_drv.c
 *
 * Copyright (C) 2012 Texas Instruments
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

/* Registers */

/* Display Parallel Interface */
#घोषणा DPIPXLFMT		0x0440
#घोषणा VS_POL_ACTIVE_LOW		(1 << 10)
#घोषणा HS_POL_ACTIVE_LOW		(1 << 9)
#घोषणा DE_POL_ACTIVE_HIGH		(0 << 8)
#घोषणा SUB_CFG_TYPE_CONFIG1		(0 << 2) /* LSB aligned */
#घोषणा SUB_CFG_TYPE_CONFIG2		(1 << 2) /* Loosely Packed */
#घोषणा SUB_CFG_TYPE_CONFIG3		(2 << 2) /* LSB aligned 8-bit */
#घोषणा DPI_BPP_RGB888			(0 << 0)
#घोषणा DPI_BPP_RGB666			(1 << 0)
#घोषणा DPI_BPP_RGB565			(2 << 0)

/* Video Path */
#घोषणा VPCTRL0			0x0450
#घोषणा VSDELAY			GENMASK(31, 20)
#घोषणा OPXLFMT_RGB666			(0 << 8)
#घोषणा OPXLFMT_RGB888			(1 << 8)
#घोषणा FRMSYNC_DISABLED		(0 << 4) /* Video Timing Gen Disabled */
#घोषणा FRMSYNC_ENABLED			(1 << 4) /* Video Timing Gen Enabled */
#घोषणा MSF_DISABLED			(0 << 0) /* Magic Square FRC disabled */
#घोषणा MSF_ENABLED			(1 << 0) /* Magic Square FRC enabled */
#घोषणा HTIM01			0x0454
#घोषणा HPW			GENMASK(8, 0)
#घोषणा HBPR			GENMASK(24, 16)
#घोषणा HTIM02			0x0458
#घोषणा HDISPR			GENMASK(10, 0)
#घोषणा HFPR			GENMASK(24, 16)
#घोषणा VTIM01			0x045c
#घोषणा VSPR			GENMASK(7, 0)
#घोषणा VBPR			GENMASK(23, 16)
#घोषणा VTIM02			0x0460
#घोषणा VFPR			GENMASK(23, 16)
#घोषणा VDISPR			GENMASK(10, 0)
#घोषणा VFUEN0			0x0464
#घोषणा VFUEN				BIT(0)   /* Video Frame Timing Upload */

/* System */
#घोषणा TC_IDREG		0x0500
#घोषणा SYSSTAT			0x0508
#घोषणा SYSCTRL			0x0510
#घोषणा DP0_AUDSRC_NO_INPUT		(0 << 3)
#घोषणा DP0_AUDSRC_I2S_RX		(1 << 3)
#घोषणा DP0_VIDSRC_NO_INPUT		(0 << 0)
#घोषणा DP0_VIDSRC_DSI_RX		(1 << 0)
#घोषणा DP0_VIDSRC_DPI_RX		(2 << 0)
#घोषणा DP0_VIDSRC_COLOR_BAR		(3 << 0)
#घोषणा SYSRSTENB		0x050c
#घोषणा ENBI2C				(1 << 0)
#घोषणा ENBLCD0				(1 << 2)
#घोषणा ENBBM				(1 << 3)
#घोषणा ENBDSIRX			(1 << 4)
#घोषणा ENBREG				(1 << 5)
#घोषणा ENBHDCP				(1 << 8)
#घोषणा GPIOM			0x0540
#घोषणा GPIOC			0x0544
#घोषणा GPIOO			0x0548
#घोषणा GPIOI			0x054c
#घोषणा INTCTL_G		0x0560
#घोषणा INTSTS_G		0x0564

#घोषणा INT_SYSERR		BIT(16)
#घोषणा INT_GPIO_H(x)		(1 << (x == 0 ? 2 : 10))
#घोषणा INT_GPIO_LC(x)		(1 << (x == 0 ? 3 : 11))

#घोषणा INT_GP0_LCNT		0x0584
#घोषणा INT_GP1_LCNT		0x0588

/* Control */
#घोषणा DP0CTL			0x0600
#घोषणा VID_MN_GEN			BIT(6)   /* Auto-generate M/N values */
#घोषणा EF_EN				BIT(5)   /* Enable Enhanced Framing */
#घोषणा VID_EN				BIT(1)   /* Video transmission enable */
#घोषणा DP_EN				BIT(0)   /* Enable DPTX function */

/* Clocks */
#घोषणा DP0_VIDMNGEN0		0x0610
#घोषणा DP0_VIDMNGEN1		0x0614
#घोषणा DP0_VMNGENSTATUS	0x0618

/* Main Channel */
#घोषणा DP0_SECSAMPLE		0x0640
#घोषणा DP0_VIDSYNCDELAY	0x0644
#घोषणा VID_SYNC_DLY		GENMASK(15, 0)
#घोषणा THRESH_DLY		GENMASK(31, 16)

#घोषणा DP0_TOTALVAL		0x0648
#घोषणा H_TOTAL			GENMASK(15, 0)
#घोषणा V_TOTAL			GENMASK(31, 16)
#घोषणा DP0_STARTVAL		0x064c
#घोषणा H_START			GENMASK(15, 0)
#घोषणा V_START			GENMASK(31, 16)
#घोषणा DP0_ACTIVEVAL		0x0650
#घोषणा H_ACT			GENMASK(15, 0)
#घोषणा V_ACT			GENMASK(31, 16)

#घोषणा DP0_SYNCVAL		0x0654
#घोषणा VS_WIDTH		GENMASK(30, 16)
#घोषणा HS_WIDTH		GENMASK(14, 0)
#घोषणा SYNCVAL_HS_POL_ACTIVE_LOW	(1 << 15)
#घोषणा SYNCVAL_VS_POL_ACTIVE_LOW	(1 << 31)
#घोषणा DP0_MISC		0x0658
#घोषणा TU_SIZE_RECOMMENDED		(63) /* LSCLK cycles per TU */
#घोषणा MAX_TU_SYMBOL		GENMASK(28, 23)
#घोषणा TU_SIZE			GENMASK(21, 16)
#घोषणा BPC_6				(0 << 5)
#घोषणा BPC_8				(1 << 5)

/* AUX channel */
#घोषणा DP0_AUXCFG0		0x0660
#घोषणा DP0_AUXCFG0_BSIZE	GENMASK(11, 8)
#घोषणा DP0_AUXCFG0_ADDR_ONLY	BIT(4)
#घोषणा DP0_AUXCFG1		0x0664
#घोषणा AUX_RX_FILTER_EN		BIT(16)

#घोषणा DP0_AUXADDR		0x0668
#घोषणा DP0_AUXWDATA(i)		(0x066c + (i) * 4)
#घोषणा DP0_AUXRDATA(i)		(0x067c + (i) * 4)
#घोषणा DP0_AUXSTATUS		0x068c
#घोषणा AUX_BYTES		GENMASK(15, 8)
#घोषणा AUX_STATUS		GENMASK(7, 4)
#घोषणा AUX_TIMEOUT		BIT(1)
#घोषणा AUX_BUSY		BIT(0)
#घोषणा DP0_AUXI2CADR		0x0698

/* Link Training */
#घोषणा DP0_SRCCTRL		0x06a0
#घोषणा DP0_SRCCTRL_SCRMBLDIS		BIT(13)
#घोषणा DP0_SRCCTRL_EN810B		BIT(12)
#घोषणा DP0_SRCCTRL_NOTP		(0 << 8)
#घोषणा DP0_SRCCTRL_TP1			(1 << 8)
#घोषणा DP0_SRCCTRL_TP2			(2 << 8)
#घोषणा DP0_SRCCTRL_LANESKEW		BIT(7)
#घोषणा DP0_SRCCTRL_SSCG		BIT(3)
#घोषणा DP0_SRCCTRL_LANES_1		(0 << 2)
#घोषणा DP0_SRCCTRL_LANES_2		(1 << 2)
#घोषणा DP0_SRCCTRL_BW27		(1 << 1)
#घोषणा DP0_SRCCTRL_BW162		(0 << 1)
#घोषणा DP0_SRCCTRL_AUTOCORRECT		BIT(0)
#घोषणा DP0_LTSTAT		0x06d0
#घोषणा LT_LOOPDONE			BIT(13)
#घोषणा LT_STATUS_MASK			(0x1f << 8)
#घोषणा LT_CHANNEL1_EQ_BITS		(DP_CHANNEL_EQ_BITS << 4)
#घोषणा LT_INTERLANE_ALIGN_DONE		BIT(3)
#घोषणा LT_CHANNEL0_EQ_BITS		(DP_CHANNEL_EQ_BITS)
#घोषणा DP0_SNKLTCHGREQ		0x06d4
#घोषणा DP0_LTLOOPCTRL		0x06d8
#घोषणा DP0_SNKLTCTRL		0x06e4

#घोषणा DP1_SRCCTRL		0x07a0

/* PHY */
#घोषणा DP_PHY_CTRL		0x0800
#घोषणा DP_PHY_RST			BIT(28)  /* DP PHY Global Soft Reset */
#घोषणा BGREN				BIT(25)  /* AUX PHY BGR Enable */
#घोषणा PWR_SW_EN			BIT(24)  /* PHY Power Switch Enable */
#घोषणा PHY_M1_RST			BIT(12)  /* Reset PHY1 Main Channel */
#घोषणा PHY_RDY				BIT(16)  /* PHY Main Channels Ready */
#घोषणा PHY_M0_RST			BIT(8)   /* Reset PHY0 Main Channel */
#घोषणा PHY_2LANE			BIT(2)   /* PHY Enable 2 lanes */
#घोषणा PHY_A0_EN			BIT(1)   /* PHY Aux Channel0 Enable */
#घोषणा PHY_M0_EN			BIT(0)   /* PHY Main Channel0 Enable */

/* PLL */
#घोषणा DP0_PLLCTRL		0x0900
#घोषणा DP1_PLLCTRL		0x0904	/* not defined in DS */
#घोषणा PXL_PLLCTRL		0x0908
#घोषणा PLLUPDATE			BIT(2)
#घोषणा PLLBYP				BIT(1)
#घोषणा PLLEN				BIT(0)
#घोषणा PXL_PLLPARAM		0x0914
#घोषणा IN_SEL_REFCLK			(0 << 14)
#घोषणा SYS_PLLPARAM		0x0918
#घोषणा REF_FREQ_38M4			(0 << 8) /* 38.4 MHz */
#घोषणा REF_FREQ_19M2			(1 << 8) /* 19.2 MHz */
#घोषणा REF_FREQ_26M			(2 << 8) /* 26 MHz */
#घोषणा REF_FREQ_13M			(3 << 8) /* 13 MHz */
#घोषणा SYSCLK_SEL_LSCLK		(0 << 4)
#घोषणा LSCLK_DIV_1			(0 << 0)
#घोषणा LSCLK_DIV_2			(1 << 0)

/* Test & Debug */
#घोषणा TSTCTL			0x0a00
#घोषणा COLOR_R			GENMASK(31, 24)
#घोषणा COLOR_G			GENMASK(23, 16)
#घोषणा COLOR_B			GENMASK(15, 8)
#घोषणा ENI2CFILTER		BIT(4)
#घोषणा COLOR_BAR_MODE		GENMASK(1, 0)
#घोषणा COLOR_BAR_MODE_BARS	2
#घोषणा PLL_DBG			0x0a04

अटल bool tc_test_pattern;
module_param_named(test, tc_test_pattern, bool, 0644);

काष्ठा tc_edp_link अणु
	u8			dpcd[DP_RECEIVER_CAP_SIZE];
	अचिन्हित पूर्णांक		rate;
	u8			num_lanes;
	u8			assr;
	bool			scrambler_dis;
	bool			spपढ़ो;
पूर्ण;

काष्ठा tc_data अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*regmap;
	काष्ठा drm_dp_aux	aux;

	काष्ठा drm_bridge	bridge;
	काष्ठा drm_bridge	*panel_bridge;
	काष्ठा drm_connector	connector;

	/* link settings */
	काष्ठा tc_edp_link	link;

	/* current mode */
	काष्ठा drm_display_mode	mode;

	u32			rev;
	u8			assr;

	काष्ठा gpio_desc	*sd_gpio;
	काष्ठा gpio_desc	*reset_gpio;
	काष्ठा clk		*refclk;

	/* करो we have IRQ */
	bool			have_irq;

	/* HPD pin number (0 or 1) or -ENODEV */
	पूर्णांक			hpd_pin;
पूर्ण;

अटल अंतरभूत काष्ठा tc_data *aux_to_tc(काष्ठा drm_dp_aux *a)
अणु
	वापस container_of(a, काष्ठा tc_data, aux);
पूर्ण

अटल अंतरभूत काष्ठा tc_data *bridge_to_tc(काष्ठा drm_bridge *b)
अणु
	वापस container_of(b, काष्ठा tc_data, bridge);
पूर्ण

अटल अंतरभूत काष्ठा tc_data *connector_to_tc(काष्ठा drm_connector *c)
अणु
	वापस container_of(c, काष्ठा tc_data, connector);
पूर्ण

अटल अंतरभूत पूर्णांक tc_poll_समयout(काष्ठा tc_data *tc, अचिन्हित पूर्णांक addr,
				  अचिन्हित पूर्णांक cond_mask,
				  अचिन्हित पूर्णांक cond_value,
				  अचिन्हित दीर्घ sleep_us, u64 समयout_us)
अणु
	अचिन्हित पूर्णांक val;

	वापस regmap_पढ़ो_poll_समयout(tc->regmap, addr, val,
					(val & cond_mask) == cond_value,
					sleep_us, समयout_us);
पूर्ण

अटल पूर्णांक tc_aux_रुको_busy(काष्ठा tc_data *tc)
अणु
	वापस tc_poll_समयout(tc, DP0_AUXSTATUS, AUX_BUSY, 0, 100, 100000);
पूर्ण

अटल पूर्णांक tc_aux_ग_लिखो_data(काष्ठा tc_data *tc, स्थिर व्योम *data,
			     माप_प्रकार size)
अणु
	u32 auxwdata[DP_AUX_MAX_PAYLOAD_BYTES / माप(u32)] = अणु 0 पूर्ण;
	पूर्णांक ret, count = ALIGN(size, माप(u32));

	स_नकल(auxwdata, data, size);

	ret = regmap_raw_ग_लिखो(tc->regmap, DP0_AUXWDATA(0), auxwdata, count);
	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण

अटल पूर्णांक tc_aux_पढ़ो_data(काष्ठा tc_data *tc, व्योम *data, माप_प्रकार size)
अणु
	u32 auxrdata[DP_AUX_MAX_PAYLOAD_BYTES / माप(u32)];
	पूर्णांक ret, count = ALIGN(size, माप(u32));

	ret = regmap_raw_पढ़ो(tc->regmap, DP0_AUXRDATA(0), auxrdata, count);
	अगर (ret)
		वापस ret;

	स_नकल(data, auxrdata, size);

	वापस size;
पूर्ण

अटल u32 tc_auxcfg0(काष्ठा drm_dp_aux_msg *msg, माप_प्रकार size)
अणु
	u32 auxcfg0 = msg->request;

	अगर (size)
		auxcfg0 |= FIELD_PREP(DP0_AUXCFG0_BSIZE, size - 1);
	अन्यथा
		auxcfg0 |= DP0_AUXCFG0_ADDR_ONLY;

	वापस auxcfg0;
पूर्ण

अटल sमाप_प्रकार tc_aux_transfer(काष्ठा drm_dp_aux *aux,
			       काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा tc_data *tc = aux_to_tc(aux);
	माप_प्रकार size = min_t(माप_प्रकार, DP_AUX_MAX_PAYLOAD_BYTES - 1, msg->size);
	u8 request = msg->request & ~DP_AUX_I2C_MOT;
	u32 auxstatus;
	पूर्णांक ret;

	ret = tc_aux_रुको_busy(tc);
	अगर (ret)
		वापस ret;

	चयन (request) अणु
	हाल DP_AUX_NATIVE_READ:
	हाल DP_AUX_I2C_READ:
		अवरोध;
	हाल DP_AUX_NATIVE_WRITE:
	हाल DP_AUX_I2C_WRITE:
		अगर (size) अणु
			ret = tc_aux_ग_लिखो_data(tc, msg->buffer, size);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Store address */
	ret = regmap_ग_लिखो(tc->regmap, DP0_AUXADDR, msg->address);
	अगर (ret)
		वापस ret;
	/* Start transfer */
	ret = regmap_ग_लिखो(tc->regmap, DP0_AUXCFG0, tc_auxcfg0(msg, size));
	अगर (ret)
		वापस ret;

	ret = tc_aux_रुको_busy(tc);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(tc->regmap, DP0_AUXSTATUS, &auxstatus);
	अगर (ret)
		वापस ret;

	अगर (auxstatus & AUX_TIMEOUT)
		वापस -ETIMEDOUT;
	/*
	 * For some reason address-only DP_AUX_I2C_WRITE (MOT), still
	 * reports 1 byte transferred in its status. To deal we that
	 * we ignore aux_bytes field अगर we know that this was an
	 * address-only transfer
	 */
	अगर (size)
		size = FIELD_GET(AUX_BYTES, auxstatus);
	msg->reply = FIELD_GET(AUX_STATUS, auxstatus);

	चयन (request) अणु
	हाल DP_AUX_NATIVE_READ:
	हाल DP_AUX_I2C_READ:
		अगर (size)
			वापस tc_aux_पढ़ो_data(tc, msg->buffer, size);
		अवरोध;
	पूर्ण

	वापस size;
पूर्ण

अटल स्थिर अक्षर * स्थिर training_pattern1_errors[] = अणु
	"No errors",
	"Aux write error",
	"Aux read error",
	"Max voltage reached error",
	"Loop counter expired error",
	"res", "res", "res"
पूर्ण;

अटल स्थिर अक्षर * स्थिर training_pattern2_errors[] = अणु
	"No errors",
	"Aux write error",
	"Aux read error",
	"Clock recovery failed error",
	"Loop counter expired error",
	"res", "res", "res"
पूर्ण;

अटल u32 tc_srcctrl(काष्ठा tc_data *tc)
अणु
	/*
	 * No training pattern, skew lane 1 data by two LSCLK cycles with
	 * respect to lane 0 data, AutoCorrect Mode = 0
	 */
	u32 reg = DP0_SRCCTRL_NOTP | DP0_SRCCTRL_LANESKEW | DP0_SRCCTRL_EN810B;

	अगर (tc->link.scrambler_dis)
		reg |= DP0_SRCCTRL_SCRMBLDIS;	/* Scrambler Disabled */
	अगर (tc->link.spपढ़ो)
		reg |= DP0_SRCCTRL_SSCG;	/* Spपढ़ो Spectrum Enable */
	अगर (tc->link.num_lanes == 2)
		reg |= DP0_SRCCTRL_LANES_2;	/* Two Main Channel Lanes */
	अगर (tc->link.rate != 162000)
		reg |= DP0_SRCCTRL_BW27;	/* 2.7 Gbps link */
	वापस reg;
पूर्ण

अटल पूर्णांक tc_pllupdate(काष्ठा tc_data *tc, अचिन्हित पूर्णांक pllctrl)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(tc->regmap, pllctrl, PLLUPDATE | PLLEN);
	अगर (ret)
		वापस ret;

	/* Wait क्रम PLL to lock: up to 2.09 ms, depending on refclk */
	usleep_range(3000, 6000);

	वापस 0;
पूर्ण

अटल पूर्णांक tc_pxl_pll_en(काष्ठा tc_data *tc, u32 refclk, u32 pixelघड़ी)
अणु
	पूर्णांक ret;
	पूर्णांक i_pre, best_pre = 1;
	पूर्णांक i_post, best_post = 1;
	पूर्णांक भाग, best_भाग = 1;
	पूर्णांक mul, best_mul = 1;
	पूर्णांक delta, best_delta;
	पूर्णांक ext_भाग[] = अणु1, 2, 3, 5, 7पूर्ण;
	पूर्णांक best_pixelघड़ी = 0;
	पूर्णांक vco_hi = 0;
	u32 pxl_pllparam;

	dev_dbg(tc->dev, "PLL: requested %d pixelclock, ref %d\n", pixelघड़ी,
		refclk);
	best_delta = pixelघड़ी;
	/* Loop over all possible ext_भागs, skipping invalid configurations */
	क्रम (i_pre = 0; i_pre < ARRAY_SIZE(ext_भाग); i_pre++) अणु
		/*
		 * refclk / ext_pre_भाग should be in the 1 to 200 MHz range.
		 * We करोn't allow any refclk > 200 MHz, only check lower bounds.
		 */
		अगर (refclk / ext_भाग[i_pre] < 1000000)
			जारी;
		क्रम (i_post = 0; i_post < ARRAY_SIZE(ext_भाग); i_post++) अणु
			क्रम (भाग = 1; भाग <= 16; भाग++) अणु
				u32 clk;
				u64 पंचांगp;

				पंचांगp = pixelघड़ी * ext_भाग[i_pre] *
				      ext_भाग[i_post] * भाग;
				करो_भाग(पंचांगp, refclk);
				mul = पंचांगp;

				/* Check limits */
				अगर ((mul < 1) || (mul > 128))
					जारी;

				clk = (refclk / ext_भाग[i_pre] / भाग) * mul;
				/*
				 * refclk * mul / (ext_pre_भाग * pre_भाग)
				 * should be in the 150 to 650 MHz range
				 */
				अगर ((clk > 650000000) || (clk < 150000000))
					जारी;

				clk = clk / ext_भाग[i_post];
				delta = clk - pixelघड़ी;

				अगर (असल(delta) < असल(best_delta)) अणु
					best_pre = i_pre;
					best_post = i_post;
					best_भाग = भाग;
					best_mul = mul;
					best_delta = delta;
					best_pixelघड़ी = clk;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (best_pixelघड़ी == 0) अणु
		dev_err(tc->dev, "Failed to calc clock for %d pixelclock\n",
			pixelघड़ी);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(tc->dev, "PLL: got %d, delta %d\n", best_pixelघड़ी,
		best_delta);
	dev_dbg(tc->dev, "PLL: %d / %d / %d * %d / %d\n", refclk,
		ext_भाग[best_pre], best_भाग, best_mul, ext_भाग[best_post]);

	/* अगर VCO >= 300 MHz */
	अगर (refclk / ext_भाग[best_pre] / best_भाग * best_mul >= 300000000)
		vco_hi = 1;
	/* see DS */
	अगर (best_भाग == 16)
		best_भाग = 0;
	अगर (best_mul == 128)
		best_mul = 0;

	/* Power up PLL and चयन to bypass */
	ret = regmap_ग_लिखो(tc->regmap, PXL_PLLCTRL, PLLBYP | PLLEN);
	अगर (ret)
		वापस ret;

	pxl_pllparam  = vco_hi << 24; /* For PLL VCO >= 300 MHz = 1 */
	pxl_pllparam |= ext_भाग[best_pre] << 20; /* External Pre-भागider */
	pxl_pllparam |= ext_भाग[best_post] << 16; /* External Post-भागider */
	pxl_pllparam |= IN_SEL_REFCLK; /* Use RefClk as PLL input */
	pxl_pllparam |= best_भाग << 8; /* Divider क्रम PLL RefClk */
	pxl_pllparam |= best_mul; /* Multiplier क्रम PLL */

	ret = regmap_ग_लिखो(tc->regmap, PXL_PLLPARAM, pxl_pllparam);
	अगर (ret)
		वापस ret;

	/* Force PLL parameter update and disable bypass */
	वापस tc_pllupdate(tc, PXL_PLLCTRL);
पूर्ण

अटल पूर्णांक tc_pxl_pll_dis(काष्ठा tc_data *tc)
अणु
	/* Enable PLL bypass, घातer करोwn PLL */
	वापस regmap_ग_लिखो(tc->regmap, PXL_PLLCTRL, PLLBYP);
पूर्ण

अटल पूर्णांक tc_stream_घड़ी_calc(काष्ठा tc_data *tc)
अणु
	/*
	 * If the Stream घड़ी and Link Symbol घड़ी are
	 * asynchronous with each other, the value of M changes over
	 * समय. This way of generating link घड़ी and stream
	 * घड़ी is called Asynchronous Clock mode. The value M
	 * must change जबतक the value N stays स्थिरant. The
	 * value of N in this Asynchronous Clock mode must be set
	 * to 2^15 or 32,768.
	 *
	 * LSCLK = 1/10 of high speed link घड़ी
	 *
	 * f_STRMCLK = M/N * f_LSCLK
	 * M/N = f_STRMCLK / f_LSCLK
	 *
	 */
	वापस regmap_ग_लिखो(tc->regmap, DP0_VIDMNGEN1, 32768);
पूर्ण

अटल पूर्णांक tc_set_syspllparam(काष्ठा tc_data *tc)
अणु
	अचिन्हित दीर्घ rate;
	u32 pllparam = SYSCLK_SEL_LSCLK | LSCLK_DIV_2;

	rate = clk_get_rate(tc->refclk);
	चयन (rate) अणु
	हाल 38400000:
		pllparam |= REF_FREQ_38M4;
		अवरोध;
	हाल 26000000:
		pllparam |= REF_FREQ_26M;
		अवरोध;
	हाल 19200000:
		pllparam |= REF_FREQ_19M2;
		अवरोध;
	हाल 13000000:
		pllparam |= REF_FREQ_13M;
		अवरोध;
	शेष:
		dev_err(tc->dev, "Invalid refclk rate: %lu Hz\n", rate);
		वापस -EINVAL;
	पूर्ण

	वापस regmap_ग_लिखो(tc->regmap, SYS_PLLPARAM, pllparam);
पूर्ण

अटल पूर्णांक tc_aux_link_setup(काष्ठा tc_data *tc)
अणु
	पूर्णांक ret;
	u32 dp0_auxcfg1;

	/* Setup DP-PHY / PLL */
	ret = tc_set_syspllparam(tc);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(tc->regmap, DP_PHY_CTRL,
			   BGREN | PWR_SW_EN | PHY_A0_EN);
	अगर (ret)
		जाओ err;
	/*
	 * Initially PLLs are in bypass. Force PLL parameter update,
	 * disable PLL bypass, enable PLL
	 */
	ret = tc_pllupdate(tc, DP0_PLLCTRL);
	अगर (ret)
		जाओ err;

	ret = tc_pllupdate(tc, DP1_PLLCTRL);
	अगर (ret)
		जाओ err;

	ret = tc_poll_समयout(tc, DP_PHY_CTRL, PHY_RDY, PHY_RDY, 100, 100000);
	अगर (ret == -ETIMEDOUT) अणु
		dev_err(tc->dev, "Timeout waiting for PHY to become ready");
		वापस ret;
	पूर्ण अन्यथा अगर (ret) अणु
		जाओ err;
	पूर्ण

	/* Setup AUX link */
	dp0_auxcfg1  = AUX_RX_FILTER_EN;
	dp0_auxcfg1 |= 0x06 << 8; /* Aux Bit Period Calculator Threshold */
	dp0_auxcfg1 |= 0x3f << 0; /* Aux Response Timeout Timer */

	ret = regmap_ग_लिखो(tc->regmap, DP0_AUXCFG1, dp0_auxcfg1);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_err(tc->dev, "tc_aux_link_setup failed: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tc_get_display_props(काष्ठा tc_data *tc)
अणु
	u8 revision, num_lanes;
	अचिन्हित पूर्णांक rate;
	पूर्णांक ret;
	u8 reg;

	/* Read DP Rx Link Capability */
	ret = drm_dp_dpcd_पढ़ो(&tc->aux, DP_DPCD_REV, tc->link.dpcd,
			       DP_RECEIVER_CAP_SIZE);
	अगर (ret < 0)
		जाओ err_dpcd_पढ़ो;

	revision = tc->link.dpcd[DP_DPCD_REV];
	rate = drm_dp_max_link_rate(tc->link.dpcd);
	num_lanes = drm_dp_max_lane_count(tc->link.dpcd);

	अगर (rate != 162000 && rate != 270000) अणु
		dev_dbg(tc->dev, "Falling to 2.7 Gbps rate\n");
		rate = 270000;
	पूर्ण

	tc->link.rate = rate;

	अगर (num_lanes > 2) अणु
		dev_dbg(tc->dev, "Falling to 2 lanes\n");
		num_lanes = 2;
	पूर्ण

	tc->link.num_lanes = num_lanes;

	ret = drm_dp_dpcd_पढ़ोb(&tc->aux, DP_MAX_DOWNSPREAD, &reg);
	अगर (ret < 0)
		जाओ err_dpcd_पढ़ो;
	tc->link.spपढ़ो = reg & DP_MAX_DOWNSPREAD_0_5;

	ret = drm_dp_dpcd_पढ़ोb(&tc->aux, DP_MAIN_LINK_CHANNEL_CODING, &reg);
	अगर (ret < 0)
		जाओ err_dpcd_पढ़ो;

	tc->link.scrambler_dis = false;
	/* पढ़ो assr */
	ret = drm_dp_dpcd_पढ़ोb(&tc->aux, DP_EDP_CONFIGURATION_SET, &reg);
	अगर (ret < 0)
		जाओ err_dpcd_पढ़ो;
	tc->link.assr = reg & DP_ALTERNATE_SCRAMBLER_RESET_ENABLE;

	dev_dbg(tc->dev, "DPCD rev: %d.%d, rate: %s, lanes: %d, framing: %s\n",
		revision >> 4, revision & 0x0f,
		(tc->link.rate == 162000) ? "1.62Gbps" : "2.7Gbps",
		tc->link.num_lanes,
		drm_dp_enhanced_frame_cap(tc->link.dpcd) ?
		"enhanced" : "default");
	dev_dbg(tc->dev, "Downspread: %s, scrambler: %s\n",
		tc->link.spपढ़ो ? "0.5%" : "0.0%",
		tc->link.scrambler_dis ? "disabled" : "enabled");
	dev_dbg(tc->dev, "Display ASSR: %d, TC358767 ASSR: %d\n",
		tc->link.assr, tc->assr);

	वापस 0;

err_dpcd_पढ़ो:
	dev_err(tc->dev, "failed to read DPCD: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tc_set_video_mode(काष्ठा tc_data *tc,
			     स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक ret;
	पूर्णांक vid_sync_dly;
	पूर्णांक max_tu_symbol;

	पूर्णांक left_margin = mode->htotal - mode->hsync_end;
	पूर्णांक right_margin = mode->hsync_start - mode->hdisplay;
	पूर्णांक hsync_len = mode->hsync_end - mode->hsync_start;
	पूर्णांक upper_margin = mode->vtotal - mode->vsync_end;
	पूर्णांक lower_margin = mode->vsync_start - mode->vdisplay;
	पूर्णांक vsync_len = mode->vsync_end - mode->vsync_start;
	u32 dp0_syncval;
	u32 bits_per_pixel = 24;
	u32 in_bw, out_bw;

	/*
	 * Recommended maximum number of symbols transferred in a transfer unit:
	 * DIV_ROUND_UP((input active video bandwidth in bytes) * tu_size,
	 *              (output active video bandwidth in bytes))
	 * Must be less than tu_size.
	 */

	in_bw = mode->घड़ी * bits_per_pixel / 8;
	out_bw = tc->link.num_lanes * tc->link.rate;
	max_tu_symbol = DIV_ROUND_UP(in_bw * TU_SIZE_RECOMMENDED, out_bw);

	dev_dbg(tc->dev, "set mode %dx%d\n",
		mode->hdisplay, mode->vdisplay);
	dev_dbg(tc->dev, "H margin %d,%d sync %d\n",
		left_margin, right_margin, hsync_len);
	dev_dbg(tc->dev, "V margin %d,%d sync %d\n",
		upper_margin, lower_margin, vsync_len);
	dev_dbg(tc->dev, "total: %dx%d\n", mode->htotal, mode->vtotal);


	/*
	 * LCD Ctl Frame Size
	 * datasheet is not clear of vsdelay in हाल of DPI
	 * assume we करो not need any delay when DPI is a source of
	 * sync संकेतs
	 */
	ret = regmap_ग_लिखो(tc->regmap, VPCTRL0,
			   FIELD_PREP(VSDELAY, 0) |
			   OPXLFMT_RGB888 | FRMSYNC_DISABLED | MSF_DISABLED);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, HTIM01,
			   FIELD_PREP(HBPR, ALIGN(left_margin, 2)) |
			   FIELD_PREP(HPW, ALIGN(hsync_len, 2)));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, HTIM02,
			   FIELD_PREP(HDISPR, ALIGN(mode->hdisplay, 2)) |
			   FIELD_PREP(HFPR, ALIGN(right_margin, 2)));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, VTIM01,
			   FIELD_PREP(VBPR, upper_margin) |
			   FIELD_PREP(VSPR, vsync_len));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, VTIM02,
			   FIELD_PREP(VFPR, lower_margin) |
			   FIELD_PREP(VDISPR, mode->vdisplay));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, VFUEN0, VFUEN); /* update settings */
	अगर (ret)
		वापस ret;

	/* Test pattern settings */
	ret = regmap_ग_लिखो(tc->regmap, TSTCTL,
			   FIELD_PREP(COLOR_R, 120) |
			   FIELD_PREP(COLOR_G, 20) |
			   FIELD_PREP(COLOR_B, 99) |
			   ENI2CFILTER |
			   FIELD_PREP(COLOR_BAR_MODE, COLOR_BAR_MODE_BARS));
	अगर (ret)
		वापस ret;

	/* DP Main Stream Attributes */
	vid_sync_dly = hsync_len + left_margin + mode->hdisplay;
	ret = regmap_ग_लिखो(tc->regmap, DP0_VIDSYNCDELAY,
		 FIELD_PREP(THRESH_DLY, max_tu_symbol) |
		 FIELD_PREP(VID_SYNC_DLY, vid_sync_dly));

	ret = regmap_ग_लिखो(tc->regmap, DP0_TOTALVAL,
			   FIELD_PREP(H_TOTAL, mode->htotal) |
			   FIELD_PREP(V_TOTAL, mode->vtotal));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, DP0_STARTVAL,
			   FIELD_PREP(H_START, left_margin + hsync_len) |
			   FIELD_PREP(V_START, upper_margin + vsync_len));
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, DP0_ACTIVEVAL,
			   FIELD_PREP(V_ACT, mode->vdisplay) |
			   FIELD_PREP(H_ACT, mode->hdisplay));
	अगर (ret)
		वापस ret;

	dp0_syncval = FIELD_PREP(VS_WIDTH, vsync_len) |
		      FIELD_PREP(HS_WIDTH, hsync_len);

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		dp0_syncval |= SYNCVAL_VS_POL_ACTIVE_LOW;

	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		dp0_syncval |= SYNCVAL_HS_POL_ACTIVE_LOW;

	ret = regmap_ग_लिखो(tc->regmap, DP0_SYNCVAL, dp0_syncval);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, DPIPXLFMT,
			   VS_POL_ACTIVE_LOW | HS_POL_ACTIVE_LOW |
			   DE_POL_ACTIVE_HIGH | SUB_CFG_TYPE_CONFIG1 |
			   DPI_BPP_RGB888);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, DP0_MISC,
			   FIELD_PREP(MAX_TU_SYMBOL, max_tu_symbol) |
			   FIELD_PREP(TU_SIZE, TU_SIZE_RECOMMENDED) |
			   BPC_8);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tc_रुको_link_training(काष्ठा tc_data *tc)
अणु
	u32 value;
	पूर्णांक ret;

	ret = tc_poll_समयout(tc, DP0_LTSTAT, LT_LOOPDONE,
			      LT_LOOPDONE, 500, 100000);
	अगर (ret) अणु
		dev_err(tc->dev, "Link training timeout waiting for LT_LOOPDONE!\n");
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(tc->regmap, DP0_LTSTAT, &value);
	अगर (ret)
		वापस ret;

	वापस (value >> 8) & 0x7;
पूर्ण

अटल पूर्णांक tc_मुख्य_link_enable(काष्ठा tc_data *tc)
अणु
	काष्ठा drm_dp_aux *aux = &tc->aux;
	काष्ठा device *dev = tc->dev;
	u32 dp_phy_ctrl;
	u32 value;
	पूर्णांक ret;
	u8 पंचांगp[DP_LINK_STATUS_SIZE];

	dev_dbg(tc->dev, "link enable\n");

	ret = regmap_पढ़ो(tc->regmap, DP0CTL, &value);
	अगर (ret)
		वापस ret;

	अगर (WARN_ON(value & DP_EN)) अणु
		ret = regmap_ग_लिखो(tc->regmap, DP0CTL, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(tc->regmap, DP0_SRCCTRL, tc_srcctrl(tc));
	अगर (ret)
		वापस ret;
	/* SSCG and BW27 on DP1 must be set to the same as on DP0 */
	ret = regmap_ग_लिखो(tc->regmap, DP1_SRCCTRL,
		 (tc->link.spपढ़ो ? DP0_SRCCTRL_SSCG : 0) |
		 ((tc->link.rate != 162000) ? DP0_SRCCTRL_BW27 : 0));
	अगर (ret)
		वापस ret;

	ret = tc_set_syspllparam(tc);
	अगर (ret)
		वापस ret;

	/* Setup Main Link */
	dp_phy_ctrl = BGREN | PWR_SW_EN | PHY_A0_EN | PHY_M0_EN;
	अगर (tc->link.num_lanes == 2)
		dp_phy_ctrl |= PHY_2LANE;

	ret = regmap_ग_लिखो(tc->regmap, DP_PHY_CTRL, dp_phy_ctrl);
	अगर (ret)
		वापस ret;

	/* PLL setup */
	ret = tc_pllupdate(tc, DP0_PLLCTRL);
	अगर (ret)
		वापस ret;

	ret = tc_pllupdate(tc, DP1_PLLCTRL);
	अगर (ret)
		वापस ret;

	/* Reset/Enable Main Links */
	dp_phy_ctrl |= DP_PHY_RST | PHY_M1_RST | PHY_M0_RST;
	ret = regmap_ग_लिखो(tc->regmap, DP_PHY_CTRL, dp_phy_ctrl);
	usleep_range(100, 200);
	dp_phy_ctrl &= ~(DP_PHY_RST | PHY_M1_RST | PHY_M0_RST);
	ret = regmap_ग_लिखो(tc->regmap, DP_PHY_CTRL, dp_phy_ctrl);

	ret = tc_poll_समयout(tc, DP_PHY_CTRL, PHY_RDY, PHY_RDY, 500, 100000);
	अगर (ret) अणु
		dev_err(dev, "timeout waiting for phy become ready");
		वापस ret;
	पूर्ण

	/* Set misc: 8 bits per color */
	ret = regmap_update_bits(tc->regmap, DP0_MISC, BPC_8, BPC_8);
	अगर (ret)
		वापस ret;

	/*
	 * ASSR mode
	 * on TC358767 side ASSR configured through strap pin
	 * seems there is no way to change this setting from SW
	 *
	 * check is tc configured क्रम same mode
	 */
	अगर (tc->assr != tc->link.assr) अणु
		dev_dbg(dev, "Trying to set display to ASSR: %d\n",
			tc->assr);
		/* try to set ASSR on display side */
		पंचांगp[0] = tc->assr;
		ret = drm_dp_dpcd_ग_लिखोb(aux, DP_EDP_CONFIGURATION_SET, पंचांगp[0]);
		अगर (ret < 0)
			जाओ err_dpcd_पढ़ो;
		/* पढ़ो back */
		ret = drm_dp_dpcd_पढ़ोb(aux, DP_EDP_CONFIGURATION_SET, पंचांगp);
		अगर (ret < 0)
			जाओ err_dpcd_पढ़ो;

		अगर (पंचांगp[0] != tc->assr) अणु
			dev_dbg(dev, "Failed to switch display ASSR to %d, falling back to unscrambled mode\n",
				tc->assr);
			/* trying with disabled scrambler */
			tc->link.scrambler_dis = true;
		पूर्ण
	पूर्ण

	/* Setup Link & DPRx Config क्रम Training */
	पंचांगp[0] = drm_dp_link_rate_to_bw_code(tc->link.rate);
	पंचांगp[1] = tc->link.num_lanes;

	अगर (drm_dp_enhanced_frame_cap(tc->link.dpcd))
		पंचांगp[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;

	ret = drm_dp_dpcd_ग_लिखो(aux, DP_LINK_BW_SET, पंचांगp, 2);
	अगर (ret < 0)
		जाओ err_dpcd_ग_लिखो;

	/* DOWNSPREAD_CTRL */
	पंचांगp[0] = tc->link.spपढ़ो ? DP_SPREAD_AMP_0_5 : 0x00;
	/* MAIN_LINK_CHANNEL_CODING_SET */
	पंचांगp[1] =  DP_SET_ANSI_8B10B;
	ret = drm_dp_dpcd_ग_लिखो(aux, DP_DOWNSPREAD_CTRL, पंचांगp, 2);
	अगर (ret < 0)
		जाओ err_dpcd_ग_लिखो;

	/* Reset voltage-swing & pre-emphasis */
	पंचांगp[0] = पंचांगp[1] = DP_TRAIN_VOLTAGE_SWING_LEVEL_0 |
			  DP_TRAIN_PRE_EMPH_LEVEL_0;
	ret = drm_dp_dpcd_ग_लिखो(aux, DP_TRAINING_LANE0_SET, पंचांगp, 2);
	अगर (ret < 0)
		जाओ err_dpcd_ग_लिखो;

	/* Clock-Recovery */

	/* Set DPCD 0x102 क्रम Training Pattern 1 */
	ret = regmap_ग_लिखो(tc->regmap, DP0_SNKLTCTRL,
			   DP_LINK_SCRAMBLING_DISABLE |
			   DP_TRAINING_PATTERN_1);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, DP0_LTLOOPCTRL,
			   (15 << 28) |	/* Defer Iteration Count */
			   (15 << 24) |	/* Loop Iteration Count */
			   (0xd << 0));	/* Loop Timer Delay */
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, DP0_SRCCTRL,
			   tc_srcctrl(tc) | DP0_SRCCTRL_SCRMBLDIS |
			   DP0_SRCCTRL_AUTOCORRECT |
			   DP0_SRCCTRL_TP1);
	अगर (ret)
		वापस ret;

	/* Enable DP0 to start Link Training */
	ret = regmap_ग_लिखो(tc->regmap, DP0CTL,
			   (drm_dp_enhanced_frame_cap(tc->link.dpcd) ?
				EF_EN : 0) | DP_EN);
	अगर (ret)
		वापस ret;

	/* रुको */

	ret = tc_रुको_link_training(tc);
	अगर (ret < 0)
		वापस ret;

	अगर (ret) अणु
		dev_err(tc->dev, "Link training phase 1 failed: %s\n",
			training_pattern1_errors[ret]);
		वापस -ENODEV;
	पूर्ण

	/* Channel Equalization */

	/* Set DPCD 0x102 क्रम Training Pattern 2 */
	ret = regmap_ग_लिखो(tc->regmap, DP0_SNKLTCTRL,
			   DP_LINK_SCRAMBLING_DISABLE |
			   DP_TRAINING_PATTERN_2);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(tc->regmap, DP0_SRCCTRL,
			   tc_srcctrl(tc) | DP0_SRCCTRL_SCRMBLDIS |
			   DP0_SRCCTRL_AUTOCORRECT |
			   DP0_SRCCTRL_TP2);
	अगर (ret)
		वापस ret;

	/* रुको */
	ret = tc_रुको_link_training(tc);
	अगर (ret < 0)
		वापस ret;

	अगर (ret) अणु
		dev_err(tc->dev, "Link training phase 2 failed: %s\n",
			training_pattern2_errors[ret]);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Toshiba's करोcumentation suggests to first clear DPCD 0x102, then
	 * clear the training pattern bit in DP0_SRCCTRL. Testing shows
	 * that the link someबार drops अगर those steps are करोne in that order,
	 * but अगर the steps are करोne in reverse order, the link stays up.
	 *
	 * So we करो the steps dअगरferently than करोcumented here.
	 */

	/* Clear Training Pattern, set AutoCorrect Mode = 1 */
	ret = regmap_ग_लिखो(tc->regmap, DP0_SRCCTRL, tc_srcctrl(tc) |
			   DP0_SRCCTRL_AUTOCORRECT);
	अगर (ret)
		वापस ret;

	/* Clear DPCD 0x102 */
	/* Note: Can Not use DP0_SNKLTCTRL (0x06E4) लघु cut */
	पंचांगp[0] = tc->link.scrambler_dis ? DP_LINK_SCRAMBLING_DISABLE : 0x00;
	ret = drm_dp_dpcd_ग_लिखोb(aux, DP_TRAINING_PATTERN_SET, पंचांगp[0]);
	अगर (ret < 0)
		जाओ err_dpcd_ग_लिखो;

	/* Check link status */
	ret = drm_dp_dpcd_पढ़ो_link_status(aux, पंचांगp);
	अगर (ret < 0)
		जाओ err_dpcd_पढ़ो;

	ret = 0;

	value = पंचांगp[0] & DP_CHANNEL_EQ_BITS;

	अगर (value != DP_CHANNEL_EQ_BITS) अणु
		dev_err(tc->dev, "Lane 0 failed: %x\n", value);
		ret = -ENODEV;
	पूर्ण

	अगर (tc->link.num_lanes == 2) अणु
		value = (पंचांगp[0] >> 4) & DP_CHANNEL_EQ_BITS;

		अगर (value != DP_CHANNEL_EQ_BITS) अणु
			dev_err(tc->dev, "Lane 1 failed: %x\n", value);
			ret = -ENODEV;
		पूर्ण

		अगर (!(पंचांगp[2] & DP_INTERLANE_ALIGN_DONE)) अणु
			dev_err(tc->dev, "Interlane align failed\n");
			ret = -ENODEV;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		dev_err(dev, "0x0202 LANE0_1_STATUS:            0x%02x\n", पंचांगp[0]);
		dev_err(dev, "0x0203 LANE2_3_STATUS             0x%02x\n", पंचांगp[1]);
		dev_err(dev, "0x0204 LANE_ALIGN_STATUS_UPDATED: 0x%02x\n", पंचांगp[2]);
		dev_err(dev, "0x0205 SINK_STATUS:               0x%02x\n", पंचांगp[3]);
		dev_err(dev, "0x0206 ADJUST_REQUEST_LANE0_1:    0x%02x\n", पंचांगp[4]);
		dev_err(dev, "0x0207 ADJUST_REQUEST_LANE2_3:    0x%02x\n", पंचांगp[5]);
		वापस ret;
	पूर्ण

	वापस 0;
err_dpcd_पढ़ो:
	dev_err(tc->dev, "Failed to read DPCD: %d\n", ret);
	वापस ret;
err_dpcd_ग_लिखो:
	dev_err(tc->dev, "Failed to write DPCD: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक tc_मुख्य_link_disable(काष्ठा tc_data *tc)
अणु
	पूर्णांक ret;

	dev_dbg(tc->dev, "link disable\n");

	ret = regmap_ग_लिखो(tc->regmap, DP0_SRCCTRL, 0);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(tc->regmap, DP0CTL, 0);
पूर्ण

अटल पूर्णांक tc_stream_enable(काष्ठा tc_data *tc)
अणु
	पूर्णांक ret;
	u32 value;

	dev_dbg(tc->dev, "enable video stream\n");

	/* PXL PLL setup */
	अगर (tc_test_pattern) अणु
		ret = tc_pxl_pll_en(tc, clk_get_rate(tc->refclk),
				    1000 * tc->mode.घड़ी);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = tc_set_video_mode(tc, &tc->mode);
	अगर (ret)
		वापस ret;

	/* Set M/N */
	ret = tc_stream_घड़ी_calc(tc);
	अगर (ret)
		वापस ret;

	value = VID_MN_GEN | DP_EN;
	अगर (drm_dp_enhanced_frame_cap(tc->link.dpcd))
		value |= EF_EN;
	ret = regmap_ग_लिखो(tc->regmap, DP0CTL, value);
	अगर (ret)
		वापस ret;
	/*
	 * VID_EN निश्चितion should be delayed by at least N * LSCLK
	 * cycles from the समय VID_MN_GEN is enabled in order to
	 * generate stable values क्रम VID_M. LSCLK is 270 MHz or
	 * 162 MHz, VID_N is set to 32768 in  tc_stream_घड़ी_calc(),
	 * so a delay of at least 203 us should suffice.
	 */
	usleep_range(500, 1000);
	value |= VID_EN;
	ret = regmap_ग_लिखो(tc->regmap, DP0CTL, value);
	अगर (ret)
		वापस ret;
	/* Set input पूर्णांकerface */
	value = DP0_AUDSRC_NO_INPUT;
	अगर (tc_test_pattern)
		value |= DP0_VIDSRC_COLOR_BAR;
	अन्यथा
		value |= DP0_VIDSRC_DPI_RX;
	ret = regmap_ग_लिखो(tc->regmap, SYSCTRL, value);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tc_stream_disable(काष्ठा tc_data *tc)
अणु
	पूर्णांक ret;

	dev_dbg(tc->dev, "disable video stream\n");

	ret = regmap_update_bits(tc->regmap, DP0CTL, VID_EN, 0);
	अगर (ret)
		वापस ret;

	tc_pxl_pll_dis(tc);

	वापस 0;
पूर्ण

अटल व्योम tc_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);
	पूर्णांक ret;

	ret = tc_get_display_props(tc);
	अगर (ret < 0) अणु
		dev_err(tc->dev, "failed to read display props: %d\n", ret);
		वापस;
	पूर्ण

	ret = tc_मुख्य_link_enable(tc);
	अगर (ret < 0) अणु
		dev_err(tc->dev, "main link enable error: %d\n", ret);
		वापस;
	पूर्ण

	ret = tc_stream_enable(tc);
	अगर (ret < 0) अणु
		dev_err(tc->dev, "main link stream start error: %d\n", ret);
		tc_मुख्य_link_disable(tc);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम tc_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);
	पूर्णांक ret;

	ret = tc_stream_disable(tc);
	अगर (ret < 0)
		dev_err(tc->dev, "main link stream stop error: %d\n", ret);

	ret = tc_मुख्य_link_disable(tc);
	अगर (ret < 0)
		dev_err(tc->dev, "main link disable error: %d\n", ret);
पूर्ण

अटल bool tc_bridge_mode_fixup(काष्ठा drm_bridge *bridge,
				 स्थिर काष्ठा drm_display_mode *mode,
				 काष्ठा drm_display_mode *adj)
अणु
	/* Fixup sync polarities, both hsync and vsync are active low */
	adj->flags = mode->flags;
	adj->flags |= (DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC);
	adj->flags &= ~(DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_PVSYNC);

	वापस true;
पूर्ण

अटल क्रमागत drm_mode_status tc_mode_valid(काष्ठा drm_bridge *bridge,
					  स्थिर काष्ठा drm_display_info *info,
					  स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);
	u32 req, avail;
	u32 bits_per_pixel = 24;

	/* DPI पूर्णांकerface घड़ी limitation: upto 154 MHz */
	अगर (mode->घड़ी > 154000)
		वापस MODE_CLOCK_HIGH;

	req = mode->घड़ी * bits_per_pixel / 8;
	avail = tc->link.num_lanes * tc->link.rate;

	अगर (req > avail)
		वापस MODE_BAD;

	वापस MODE_OK;
पूर्ण

अटल व्योम tc_bridge_mode_set(काष्ठा drm_bridge *bridge,
			       स्थिर काष्ठा drm_display_mode *mode,
			       स्थिर काष्ठा drm_display_mode *adj)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);

	tc->mode = *mode;
पूर्ण

अटल काष्ठा edid *tc_get_edid(काष्ठा drm_bridge *bridge,
				काष्ठा drm_connector *connector)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);

	वापस drm_get_edid(connector, &tc->aux.ddc);
पूर्ण

अटल पूर्णांक tc_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा tc_data *tc = connector_to_tc(connector);
	पूर्णांक num_modes;
	काष्ठा edid *edid;
	पूर्णांक ret;

	ret = tc_get_display_props(tc);
	अगर (ret < 0) अणु
		dev_err(tc->dev, "failed to read display props: %d\n", ret);
		वापस 0;
	पूर्ण

	अगर (tc->panel_bridge) अणु
		num_modes = drm_bridge_get_modes(tc->panel_bridge, connector);
		अगर (num_modes > 0)
			वापस num_modes;
	पूर्ण

	edid = tc_get_edid(&tc->bridge, connector);
	num_modes = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस num_modes;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs tc_connector_helper_funcs = अणु
	.get_modes = tc_connector_get_modes,
पूर्ण;

अटल क्रमागत drm_connector_status tc_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा tc_data *tc = bridge_to_tc(bridge);
	bool conn;
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(tc->regmap, GPIOI, &val);
	अगर (ret)
		वापस connector_status_unknown;

	conn = val & BIT(tc->hpd_pin);

	अगर (conn)
		वापस connector_status_connected;
	अन्यथा
		वापस connector_status_disconnected;
पूर्ण

अटल क्रमागत drm_connector_status
tc_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा tc_data *tc = connector_to_tc(connector);

	अगर (tc->hpd_pin >= 0)
		वापस tc_bridge_detect(&tc->bridge);

	अगर (tc->panel_bridge)
		वापस connector_status_connected;
	अन्यथा
		वापस connector_status_unknown;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs tc_connector_funcs = अणु
	.detect = tc_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक tc_bridge_attach(काष्ठा drm_bridge *bridge,
			    क्रमागत drm_bridge_attach_flags flags)
अणु
	u32 bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;
	काष्ठा tc_data *tc = bridge_to_tc(bridge);
	काष्ठा drm_device *drm = bridge->dev;
	पूर्णांक ret;

	अगर (tc->panel_bridge) अणु
		/* If a connector is required then this driver shall create it */
		ret = drm_bridge_attach(tc->bridge.encoder, tc->panel_bridge,
					&tc->bridge, flags | DRM_BRIDGE_ATTACH_NO_CONNECTOR);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)
		वापस 0;

	ret = drm_dp_aux_रेजिस्टर(&tc->aux);
	अगर (ret < 0)
		वापस ret;

	/* Create DP/eDP connector */
	drm_connector_helper_add(&tc->connector, &tc_connector_helper_funcs);
	ret = drm_connector_init(drm, &tc->connector, &tc_connector_funcs, tc->bridge.type);
	अगर (ret)
		जाओ aux_unरेजिस्टर;

	/* Don't poll if don't have HPD connected */
	अगर (tc->hpd_pin >= 0) अणु
		अगर (tc->have_irq)
			tc->connector.polled = DRM_CONNECTOR_POLL_HPD;
		अन्यथा
			tc->connector.polled = DRM_CONNECTOR_POLL_CONNECT |
					       DRM_CONNECTOR_POLL_DISCONNECT;
	पूर्ण

	drm_display_info_set_bus_क्रमmats(&tc->connector.display_info,
					 &bus_क्रमmat, 1);
	tc->connector.display_info.bus_flags =
		DRM_BUS_FLAG_DE_HIGH |
		DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE |
		DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE;
	drm_connector_attach_encoder(&tc->connector, tc->bridge.encoder);

	वापस 0;
aux_unरेजिस्टर:
	drm_dp_aux_unरेजिस्टर(&tc->aux);
	वापस ret;
पूर्ण

अटल व्योम tc_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	drm_dp_aux_unरेजिस्टर(&bridge_to_tc(bridge)->aux);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs tc_bridge_funcs = अणु
	.attach = tc_bridge_attach,
	.detach = tc_bridge_detach,
	.mode_valid = tc_mode_valid,
	.mode_set = tc_bridge_mode_set,
	.enable = tc_bridge_enable,
	.disable = tc_bridge_disable,
	.mode_fixup = tc_bridge_mode_fixup,
	.detect = tc_bridge_detect,
	.get_edid = tc_get_edid,
पूर्ण;

अटल bool tc_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg != SYSCTRL;
पूर्ण

अटल स्थिर काष्ठा regmap_range tc_अस्थिर_ranges[] = अणु
	regmap_reg_range(DP0_AUXWDATA(0), DP0_AUXSTATUS),
	regmap_reg_range(DP0_LTSTAT, DP0_SNKLTCHGREQ),
	regmap_reg_range(DP_PHY_CTRL, DP_PHY_CTRL),
	regmap_reg_range(DP0_PLLCTRL, PXL_PLLCTRL),
	regmap_reg_range(VFUEN0, VFUEN0),
	regmap_reg_range(INTSTS_G, INTSTS_G),
	regmap_reg_range(GPIOI, GPIOI),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table tc_अस्थिर_table = अणु
	.yes_ranges = tc_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(tc_अस्थिर_ranges),
पूर्ण;

अटल bool tc_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg != TC_IDREG) &&
	       (reg != DP0_LTSTAT) &&
	       (reg != DP0_SNKLTCHGREQ);
पूर्ण

अटल स्थिर काष्ठा regmap_config tc_regmap_config = अणु
	.name = "tc358767",
	.reg_bits = 16,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = PLL_DBG,
	.cache_type = REGCACHE_RBTREE,
	.पढ़ोable_reg = tc_पढ़ोable_reg,
	.अस्थिर_table = &tc_अस्थिर_table,
	.ग_लिखोable_reg = tc_ग_लिखोable_reg,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
पूर्ण;

अटल irqवापस_t tc_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा tc_data *tc = arg;
	u32 val;
	पूर्णांक r;

	r = regmap_पढ़ो(tc->regmap, INTSTS_G, &val);
	अगर (r)
		वापस IRQ_NONE;

	अगर (!val)
		वापस IRQ_NONE;

	अगर (val & INT_SYSERR) अणु
		u32 stat = 0;

		regmap_पढ़ो(tc->regmap, SYSSTAT, &stat);

		dev_err(tc->dev, "syserr %x\n", stat);
	पूर्ण

	अगर (tc->hpd_pin >= 0 && tc->bridge.dev) अणु
		/*
		 * H is triggered when the GPIO goes high.
		 *
		 * LC is triggered when the GPIO goes low and stays low क्रम
		 * the duration of LCNT
		 */
		bool h = val & INT_GPIO_H(tc->hpd_pin);
		bool lc = val & INT_GPIO_LC(tc->hpd_pin);

		dev_dbg(tc->dev, "GPIO%d: %s %s\n", tc->hpd_pin,
			h ? "H" : "", lc ? "LC" : "");

		अगर (h || lc)
			drm_kms_helper_hotplug_event(tc->bridge.dev);
	पूर्ण

	regmap_ग_लिखो(tc->regmap, INTSTS_G, val);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tc_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा drm_panel *panel;
	काष्ठा tc_data *tc;
	पूर्णांक ret;

	tc = devm_kzalloc(dev, माप(*tc), GFP_KERNEL);
	अगर (!tc)
		वापस -ENOMEM;

	tc->dev = dev;

	/* port@2 is the output port */
	ret = drm_of_find_panel_or_bridge(dev->of_node, 2, 0, &panel, शून्य);
	अगर (ret && ret != -ENODEV)
		वापस ret;

	अगर (panel) अणु
		काष्ठा drm_bridge *panel_bridge;

		panel_bridge = devm_drm_panel_bridge_add(dev, panel);
		अगर (IS_ERR(panel_bridge))
			वापस PTR_ERR(panel_bridge);

		tc->panel_bridge = panel_bridge;
		tc->bridge.type = DRM_MODE_CONNECTOR_eDP;
	पूर्ण अन्यथा अणु
		tc->bridge.type = DRM_MODE_CONNECTOR_DisplayPort;
	पूर्ण

	/* Shut करोwn GPIO is optional */
	tc->sd_gpio = devm_gpiod_get_optional(dev, "shutdown", GPIOD_OUT_HIGH);
	अगर (IS_ERR(tc->sd_gpio))
		वापस PTR_ERR(tc->sd_gpio);

	अगर (tc->sd_gpio) अणु
		gpiod_set_value_cansleep(tc->sd_gpio, 0);
		usleep_range(5000, 10000);
	पूर्ण

	/* Reset GPIO is optional */
	tc->reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(tc->reset_gpio))
		वापस PTR_ERR(tc->reset_gpio);

	अगर (tc->reset_gpio) अणु
		gpiod_set_value_cansleep(tc->reset_gpio, 1);
		usleep_range(5000, 10000);
	पूर्ण

	tc->refclk = devm_clk_get(dev, "ref");
	अगर (IS_ERR(tc->refclk)) अणु
		ret = PTR_ERR(tc->refclk);
		dev_err(dev, "Failed to get refclk: %d\n", ret);
		वापस ret;
	पूर्ण

	tc->regmap = devm_regmap_init_i2c(client, &tc_regmap_config);
	अगर (IS_ERR(tc->regmap)) अणु
		ret = PTR_ERR(tc->regmap);
		dev_err(dev, "Failed to initialize regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dev->of_node, "toshiba,hpd-pin",
				   &tc->hpd_pin);
	अगर (ret) अणु
		tc->hpd_pin = -ENODEV;
	पूर्ण अन्यथा अणु
		अगर (tc->hpd_pin < 0 || tc->hpd_pin > 1) अणु
			dev_err(dev, "failed to parse HPD number\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (client->irq > 0) अणु
		/* enable SysErr */
		regmap_ग_लिखो(tc->regmap, INTCTL_G, INT_SYSERR);

		ret = devm_request_thपढ़ोed_irq(dev, client->irq,
						शून्य, tc_irq_handler,
						IRQF_ONESHOT,
						"tc358767-irq", tc);
		अगर (ret) अणु
			dev_err(dev, "failed to register dp interrupt\n");
			वापस ret;
		पूर्ण

		tc->have_irq = true;
	पूर्ण

	ret = regmap_पढ़ो(tc->regmap, TC_IDREG, &tc->rev);
	अगर (ret) अणु
		dev_err(tc->dev, "can not read device ID: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर ((tc->rev != 0x6601) && (tc->rev != 0x6603)) अणु
		dev_err(tc->dev, "invalid device ID: 0x%08x\n", tc->rev);
		वापस -EINVAL;
	पूर्ण

	tc->assr = (tc->rev == 0x6601); /* Enable ASSR क्रम eDP panels */

	अगर (!tc->reset_gpio) अणु
		/*
		 * If the reset pin isn't present, do a software reset. It isn't
		 * as thorough as the hardware reset, as we can't reset the I2C
		 * communication block क्रम obvious reasons, but it's getting the
		 * chip पूर्णांकo a defined state.
		 */
		regmap_update_bits(tc->regmap, SYSRSTENB,
				ENBLCD0 | ENBBM | ENBDSIRX | ENBREG | ENBHDCP,
				0);
		regmap_update_bits(tc->regmap, SYSRSTENB,
				ENBLCD0 | ENBBM | ENBDSIRX | ENBREG | ENBHDCP,
				ENBLCD0 | ENBBM | ENBDSIRX | ENBREG | ENBHDCP);
		usleep_range(5000, 10000);
	पूर्ण

	अगर (tc->hpd_pin >= 0) अणु
		u32 lcnt_reg = tc->hpd_pin == 0 ? INT_GP0_LCNT : INT_GP1_LCNT;
		u32 h_lc = INT_GPIO_H(tc->hpd_pin) | INT_GPIO_LC(tc->hpd_pin);

		/* Set LCNT to 2ms */
		regmap_ग_लिखो(tc->regmap, lcnt_reg,
			     clk_get_rate(tc->refclk) * 2 / 1000);
		/* We need the "alternate" mode क्रम HPD */
		regmap_ग_लिखो(tc->regmap, GPIOM, BIT(tc->hpd_pin));

		अगर (tc->have_irq) अणु
			/* enable H & LC */
			regmap_update_bits(tc->regmap, INTCTL_G, h_lc, h_lc);
		पूर्ण
	पूर्ण

	ret = tc_aux_link_setup(tc);
	अगर (ret)
		वापस ret;

	/* Register DP AUX channel */
	tc->aux.name = "TC358767 AUX i2c adapter";
	tc->aux.dev = tc->dev;
	tc->aux.transfer = tc_aux_transfer;
	drm_dp_aux_init(&tc->aux);

	tc->bridge.funcs = &tc_bridge_funcs;
	अगर (tc->hpd_pin >= 0)
		tc->bridge.ops |= DRM_BRIDGE_OP_DETECT;
	tc->bridge.ops |= DRM_BRIDGE_OP_EDID;

	tc->bridge.of_node = dev->of_node;
	drm_bridge_add(&tc->bridge);

	i2c_set_clientdata(client, tc);

	वापस 0;
पूर्ण

अटल पूर्णांक tc_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tc_data *tc = i2c_get_clientdata(client);

	drm_bridge_हटाओ(&tc->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tc358767_i2c_ids[] = अणु
	अणु "tc358767", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tc358767_i2c_ids);

अटल स्थिर काष्ठा of_device_id tc358767_of_ids[] = अणु
	अणु .compatible = "toshiba,tc358767", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tc358767_of_ids);

अटल काष्ठा i2c_driver tc358767_driver = अणु
	.driver = अणु
		.name = "tc358767",
		.of_match_table = tc358767_of_ids,
	पूर्ण,
	.id_table = tc358767_i2c_ids,
	.probe = tc_probe,
	.हटाओ	= tc_हटाओ,
पूर्ण;
module_i2c_driver(tc358767_driver);

MODULE_AUTHOR("Andrey Gusakov <andrey.gusakov@cogentembedded.com>");
MODULE_DESCRIPTION("tc358767 eDP encoder driver");
MODULE_LICENSE("GPL");
