<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 Samsung Electronics
 *
 * Authors:
 *    Tomasz Stanislawski <t.stanislaws@samsung.com>
 *    Maciej Purski <m.purski@samsung.com>
 *
 * Based on sii9234 driver created by:
 *    Adam Hampson <ahampson@sta.samsung.com>
 *    Erik Gilling <konkers@android.com>
 *    Shankar Bandal <shankar.b@samsung.com>
 *    Dharam Kumar <dharam.kr@samsung.com>
 */
#समावेश <drm/bridge/mhl.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#घोषणा CBUS_DEVCAP_OFFSET		0x80

#घोषणा SII9234_MHL_VERSION		0x11
#घोषणा SII9234_SCRATCHPAD_SIZE		0x10
#घोषणा SII9234_INT_STAT_SIZE		0x33

#घोषणा BIT_TMDS_CCTRL_TMDS_OE		BIT(4)
#घोषणा MHL_HPD_OUT_OVR_EN		BIT(4)
#घोषणा MHL_HPD_OUT_OVR_VAL		BIT(5)
#घोषणा MHL_INIT_TIMEOUT		0x0C

/* MHL Tx रेजिस्टरs and bits */
#घोषणा MHL_TX_SRST			0x05
#घोषणा MHL_TX_SYSSTAT_REG		0x09
#घोषणा MHL_TX_INTR1_REG		0x71
#घोषणा MHL_TX_INTR4_REG		0x74
#घोषणा MHL_TX_INTR1_ENABLE_REG		0x75
#घोषणा MHL_TX_INTR4_ENABLE_REG		0x78
#घोषणा MHL_TX_INT_CTRL_REG		0x79
#घोषणा MHL_TX_TMDS_CCTRL		0x80
#घोषणा MHL_TX_DISC_CTRL1_REG		0x90
#घोषणा MHL_TX_DISC_CTRL2_REG		0x91
#घोषणा MHL_TX_DISC_CTRL3_REG		0x92
#घोषणा MHL_TX_DISC_CTRL4_REG		0x93
#घोषणा MHL_TX_DISC_CTRL5_REG		0x94
#घोषणा MHL_TX_DISC_CTRL6_REG		0x95
#घोषणा MHL_TX_DISC_CTRL7_REG		0x96
#घोषणा MHL_TX_DISC_CTRL8_REG		0x97
#घोषणा MHL_TX_STAT2_REG		0x99
#घोषणा MHL_TX_MHLTX_CTL1_REG		0xA0
#घोषणा MHL_TX_MHLTX_CTL2_REG		0xA1
#घोषणा MHL_TX_MHLTX_CTL4_REG		0xA3
#घोषणा MHL_TX_MHLTX_CTL6_REG		0xA5
#घोषणा MHL_TX_MHLTX_CTL7_REG		0xA6

#घोषणा RSEN_STATUS			BIT(2)
#घोषणा HPD_CHANGE_INT			BIT(6)
#घोषणा RSEN_CHANGE_INT			BIT(5)
#घोषणा RGND_READY_INT			BIT(6)
#घोषणा VBUS_LOW_INT			BIT(5)
#घोषणा CBUS_LKOUT_INT			BIT(4)
#घोषणा MHL_DISC_FAIL_INT		BIT(3)
#घोषणा MHL_EST_INT			BIT(2)
#घोषणा HPD_CHANGE_INT_MASK		BIT(6)
#घोषणा RSEN_CHANGE_INT_MASK		BIT(5)

#घोषणा RGND_READY_MASK			BIT(6)
#घोषणा CBUS_LKOUT_MASK			BIT(4)
#घोषणा MHL_DISC_FAIL_MASK		BIT(3)
#घोषणा MHL_EST_MASK			BIT(2)

#घोषणा SKIP_GND			BIT(6)

#घोषणा ATT_THRESH_SHIFT		0x04
#घोषणा ATT_THRESH_MASK			(0x03 << ATT_THRESH_SHIFT)
#घोषणा USB_D_OEN			BIT(3)
#घोषणा DEGLITCH_TIME_MASK		0x07
#घोषणा DEGLITCH_TIME_2MS		0
#घोषणा DEGLITCH_TIME_4MS		1
#घोषणा DEGLITCH_TIME_8MS		2
#घोषणा DEGLITCH_TIME_16MS		3
#घोषणा DEGLITCH_TIME_40MS		4
#घोषणा DEGLITCH_TIME_50MS		5
#घोषणा DEGLITCH_TIME_60MS		6
#घोषणा DEGLITCH_TIME_128MS		7

#घोषणा USB_D_OVR			BIT(7)
#घोषणा USB_ID_OVR			BIT(6)
#घोषणा DVRFLT_SEL			BIT(5)
#घोषणा BLOCK_RGND_INT			BIT(4)
#घोषणा SKIP_DEG			BIT(3)
#घोषणा CI2CA_POL			BIT(2)
#घोषणा CI2CA_WKUP			BIT(1)
#घोषणा SINGLE_ATT			BIT(0)

#घोषणा USB_D_ODN			BIT(5)
#घोषणा VBUS_CHECK			BIT(2)
#घोषणा RGND_INTP_MASK			0x03
#घोषणा RGND_INTP_OPEN			0
#घोषणा RGND_INTP_2K			1
#घोषणा RGND_INTP_1K			2
#घोषणा RGND_INTP_SHORT			3

/* HDMI रेजिस्टरs */
#घोषणा HDMI_RX_TMDS0_CCTRL1_REG	0x10
#घोषणा HDMI_RX_TMDS_CLK_EN_REG		0x11
#घोषणा HDMI_RX_TMDS_CH_EN_REG		0x12
#घोषणा HDMI_RX_PLL_CALREFSEL_REG	0x17
#घोषणा HDMI_RX_PLL_VCOCAL_REG		0x1A
#घोषणा HDMI_RX_EQ_DATA0_REG		0x22
#घोषणा HDMI_RX_EQ_DATA1_REG		0x23
#घोषणा HDMI_RX_EQ_DATA2_REG		0x24
#घोषणा HDMI_RX_EQ_DATA3_REG		0x25
#घोषणा HDMI_RX_EQ_DATA4_REG		0x26
#घोषणा HDMI_RX_TMDS_ZONE_CTRL_REG	0x4C
#घोषणा HDMI_RX_TMDS_MODE_CTRL_REG	0x4D

/* CBUS रेजिस्टरs */
#घोषणा CBUS_INT_STATUS_1_REG		0x08
#घोषणा CBUS_INTR1_ENABLE_REG		0x09
#घोषणा CBUS_MSC_REQ_ABORT_REASON_REG	0x0D
#घोषणा CBUS_INT_STATUS_2_REG		0x1E
#घोषणा CBUS_INTR2_ENABLE_REG		0x1F
#घोषणा CBUS_LINK_CONTROL_2_REG		0x31
#घोषणा CBUS_MHL_STATUS_REG_0		0xB0
#घोषणा CBUS_MHL_STATUS_REG_1		0xB1

#घोषणा BIT_CBUS_RESET			BIT(3)
#घोषणा SET_HPD_DOWNSTREAM		BIT(6)

/* TPI रेजिस्टरs */
#घोषणा TPI_DPD_REG			0x3D

/* Timeouts in msec */
#घोषणा T_SRC_VBUS_CBUS_TO_STABLE	200
#घोषणा T_SRC_CBUS_FLOAT		100
#घोषणा T_SRC_CBUS_DEGLITCH		2
#घोषणा T_SRC_RXSENSE_DEGLITCH		110

#घोषणा MHL1_MAX_CLK			75000 /* in kHz */

#घोषणा I2C_TPI_ADDR			0x3D
#घोषणा I2C_HDMI_ADDR			0x49
#घोषणा I2C_CBUS_ADDR			0x64

क्रमागत sii9234_state अणु
	ST_OFF,
	ST_D3,
	ST_RGND_INIT,
	ST_RGND_1K,
	ST_RSEN_HIGH,
	ST_MHL_ESTABLISHED,
	ST_FAILURE_DISCOVERY,
	ST_FAILURE,
पूर्ण;

काष्ठा sii9234 अणु
	काष्ठा i2c_client *client[4];
	काष्ठा drm_bridge bridge;
	काष्ठा device *dev;
	काष्ठा gpio_desc *gpio_reset;
	पूर्णांक i2c_error;
	काष्ठा regulator_bulk_data supplies[4];

	काष्ठा mutex lock; /* Protects fields below and device रेजिस्टरs */
	क्रमागत sii9234_state state;
पूर्ण;

क्रमागत sii9234_client_id अणु
	I2C_MHL,
	I2C_TPI,
	I2C_HDMI,
	I2C_CBUS,
पूर्ण;

अटल स्थिर अक्षर * स्थिर sii9234_client_name[] = अणु
	[I2C_MHL] = "MHL",
	[I2C_TPI] = "TPI",
	[I2C_HDMI] = "HDMI",
	[I2C_CBUS] = "CBUS",
पूर्ण;

अटल पूर्णांक sii9234_ग_लिखोb(काष्ठा sii9234 *ctx, पूर्णांक id, पूर्णांक offset,
			  पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = ctx->client[id];

	अगर (ctx->i2c_error)
		वापस ctx->i2c_error;

	ret = i2c_smbus_ग_लिखो_byte_data(client, offset, value);
	अगर (ret < 0)
		dev_err(ctx->dev, "writeb: %4s[0x%02x] <- 0x%02x\n",
			sii9234_client_name[id], offset, value);
	ctx->i2c_error = ret;

	वापस ret;
पूर्ण

अटल पूर्णांक sii9234_ग_लिखोbm(काष्ठा sii9234 *ctx, पूर्णांक id, पूर्णांक offset,
			   पूर्णांक value, पूर्णांक mask)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = ctx->client[id];

	अगर (ctx->i2c_error)
		वापस ctx->i2c_error;

	ret = i2c_smbus_ग_लिखो_byte(client, offset);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "writebm: %4s[0x%02x] <- 0x%02x\n",
			sii9234_client_name[id], offset, value);
		ctx->i2c_error = ret;
		वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte(client);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "writebm: %4s[0x%02x] <- 0x%02x\n",
			sii9234_client_name[id], offset, value);
		ctx->i2c_error = ret;
		वापस ret;
	पूर्ण

	value = (value & mask) | (ret & ~mask);

	ret = i2c_smbus_ग_लिखो_byte_data(client, offset, value);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "writebm: %4s[0x%02x] <- 0x%02x\n",
			sii9234_client_name[id], offset, value);
		ctx->i2c_error = ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sii9234_पढ़ोb(काष्ठा sii9234 *ctx, पूर्णांक id, पूर्णांक offset)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = ctx->client[id];

	अगर (ctx->i2c_error)
		वापस ctx->i2c_error;

	ret = i2c_smbus_ग_लिखो_byte(client, offset);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "readb: %4s[0x%02x]\n",
			sii9234_client_name[id], offset);
		ctx->i2c_error = ret;
		वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte(client);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "readb: %4s[0x%02x]\n",
			sii9234_client_name[id], offset);
		ctx->i2c_error = ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sii9234_clear_error(काष्ठा sii9234 *ctx)
अणु
	पूर्णांक ret = ctx->i2c_error;

	ctx->i2c_error = 0;

	वापस ret;
पूर्ण

#घोषणा mhl_tx_ग_लिखोb(sii9234, offset, value) \
	sii9234_ग_लिखोb(sii9234, I2C_MHL, offset, value)
#घोषणा mhl_tx_ग_लिखोbm(sii9234, offset, value, mask) \
	sii9234_ग_लिखोbm(sii9234, I2C_MHL, offset, value, mask)
#घोषणा mhl_tx_पढ़ोb(sii9234, offset) \
	sii9234_पढ़ोb(sii9234, I2C_MHL, offset)
#घोषणा cbus_ग_लिखोb(sii9234, offset, value) \
	sii9234_ग_लिखोb(sii9234, I2C_CBUS, offset, value)
#घोषणा cbus_ग_लिखोbm(sii9234, offset, value, mask) \
	sii9234_ग_लिखोbm(sii9234, I2C_CBUS, offset, value, mask)
#घोषणा cbus_पढ़ोb(sii9234, offset) \
	sii9234_पढ़ोb(sii9234, I2C_CBUS, offset)
#घोषणा hdmi_ग_लिखोb(sii9234, offset, value) \
	sii9234_ग_लिखोb(sii9234, I2C_HDMI, offset, value)
#घोषणा hdmi_ग_लिखोbm(sii9234, offset, value, mask) \
	sii9234_ग_लिखोbm(sii9234, I2C_HDMI, offset, value, mask)
#घोषणा hdmi_पढ़ोb(sii9234, offset) \
	sii9234_पढ़ोb(sii9234, I2C_HDMI, offset)
#घोषणा tpi_ग_लिखोb(sii9234, offset, value) \
	sii9234_ग_लिखोb(sii9234, I2C_TPI, offset, value)
#घोषणा tpi_ग_लिखोbm(sii9234, offset, value, mask) \
	sii9234_ग_लिखोbm(sii9234, I2C_TPI, offset, value, mask)
#घोषणा tpi_पढ़ोb(sii9234, offset) \
	sii9234_पढ़ोb(sii9234, I2C_TPI, offset)

अटल u8 sii9234_पंचांगds_control(काष्ठा sii9234 *ctx, bool enable)
अणु
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_TMDS_CCTRL, enable ? ~0 : 0,
		       BIT_TMDS_CCTRL_TMDS_OE);
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_INT_CTRL_REG, enable ? ~0 : 0,
		       MHL_HPD_OUT_OVR_EN | MHL_HPD_OUT_OVR_VAL);
	वापस sii9234_clear_error(ctx);
पूर्ण

अटल पूर्णांक sii9234_cbus_reset(काष्ठा sii9234 *ctx)
अणु
	पूर्णांक i;

	mhl_tx_ग_लिखोbm(ctx, MHL_TX_SRST, ~0, BIT_CBUS_RESET);
	msleep(T_SRC_CBUS_DEGLITCH);
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_SRST, 0, BIT_CBUS_RESET);

	क्रम (i = 0; i < 4; i++) अणु
		/*
		 * Enable WRITE_STAT पूर्णांकerrupt क्रम ग_लिखोs to all
		 * 4 MSC Status रेजिस्टरs.
		 */
		cbus_ग_लिखोb(ctx, 0xE0 + i, 0xF2);
		/*
		 * Enable SET_INT पूर्णांकerrupt क्रम ग_लिखोs to all
		 * 4 MSC Interrupt रेजिस्टरs.
		 */
		cbus_ग_लिखोb(ctx, 0xF0 + i, 0xF2);
	पूर्ण

	वापस sii9234_clear_error(ctx);
पूर्ण

/* Require to chek mhl imक्रमmation of samsung in cbus_init_रेजिस्टर */
अटल पूर्णांक sii9234_cbus_init(काष्ठा sii9234 *ctx)
अणु
	cbus_ग_लिखोb(ctx, 0x07, 0xF2);
	cbus_ग_लिखोb(ctx, 0x40, 0x03);
	cbus_ग_लिखोb(ctx, 0x42, 0x06);
	cbus_ग_लिखोb(ctx, 0x36, 0x0C);
	cbus_ग_लिखोb(ctx, 0x3D, 0xFD);
	cbus_ग_लिखोb(ctx, 0x1C, 0x01);
	cbus_ग_लिखोb(ctx, 0x1D, 0x0F);
	cbus_ग_लिखोb(ctx, 0x44, 0x02);
	/* Setup our devcap */
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_DEV_STATE, 0x00);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_MHL_VERSION,
		    SII9234_MHL_VERSION);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_CAT,
		    MHL_DCAP_CAT_SOURCE);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_ADOPTER_ID_H, 0x01);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_ADOPTER_ID_L, 0x41);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_VID_LINK_MODE,
		    MHL_DCAP_VID_LINK_RGB444 | MHL_DCAP_VID_LINK_YCBCR444);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_VIDEO_TYPE,
		    MHL_DCAP_VT_GRAPHICS);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_LOG_DEV_MAP,
		    MHL_DCAP_LD_GUI);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_BANDWIDTH, 0x0F);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_FEATURE_FLAG,
		    MHL_DCAP_FEATURE_RCP_SUPPORT | MHL_DCAP_FEATURE_RAP_SUPPORT
			| MHL_DCAP_FEATURE_SP_SUPPORT);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_DEVICE_ID_H, 0x0);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_DEVICE_ID_L, 0x0);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_SCRATCHPAD_SIZE,
		    SII9234_SCRATCHPAD_SIZE);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_INT_STAT_SIZE,
		    SII9234_INT_STAT_SIZE);
	cbus_ग_लिखोb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_RESERVED, 0);
	cbus_ग_लिखोbm(ctx, 0x31, 0x0C, 0x0C);
	cbus_ग_लिखोb(ctx, 0x30, 0x01);
	cbus_ग_लिखोbm(ctx, 0x3C, 0x30, 0x38);
	cbus_ग_लिखोbm(ctx, 0x22, 0x0D, 0x0F);
	cbus_ग_लिखोbm(ctx, 0x2E, 0x15, 0x15);
	cbus_ग_लिखोb(ctx, CBUS_INTR1_ENABLE_REG, 0);
	cbus_ग_लिखोb(ctx, CBUS_INTR2_ENABLE_REG, 0);

	वापस sii9234_clear_error(ctx);
पूर्ण

अटल व्योम क्रमce_usb_id_चयन_खोलो(काष्ठा sii9234 *ctx)
अणु
	/* Disable CBUS discovery */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL1_REG, 0, 0x01);
	/* Force USB ID चयन to खोलो */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL6_REG, ~0, USB_ID_OVR);
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL3_REG, ~0, 0x86);
	/* Force upstream HPD to 0 when not in MHL mode. */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_INT_CTRL_REG, 0, 0x30);
पूर्ण

अटल व्योम release_usb_id_चयन_खोलो(काष्ठा sii9234 *ctx)
अणु
	msleep(T_SRC_CBUS_FLOAT);
	/* Clear USB ID चयन to खोलो */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL6_REG, 0, USB_ID_OVR);
	/* Enable CBUS discovery */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL1_REG, ~0, 0x01);
पूर्ण

अटल पूर्णांक sii9234_घातer_init(काष्ठा sii9234 *ctx)
अणु
	/* Force the SiI9234 पूर्णांकo the D0 state. */
	tpi_ग_लिखोb(ctx, TPI_DPD_REG, 0x3F);
	/* Enable TxPLL Clock */
	hdmi_ग_लिखोb(ctx, HDMI_RX_TMDS_CLK_EN_REG, 0x01);
	/* Enable Tx Clock Path & Equalizer */
	hdmi_ग_लिखोb(ctx, HDMI_RX_TMDS_CH_EN_REG, 0x15);
	/* Power Up TMDS */
	mhl_tx_ग_लिखोb(ctx, 0x08, 0x35);
	वापस sii9234_clear_error(ctx);
पूर्ण

अटल पूर्णांक sii9234_hdmi_init(काष्ठा sii9234 *ctx)
अणु
	hdmi_ग_लिखोb(ctx, HDMI_RX_TMDS0_CCTRL1_REG, 0xC1);
	hdmi_ग_लिखोb(ctx, HDMI_RX_PLL_CALREFSEL_REG, 0x03);
	hdmi_ग_लिखोb(ctx, HDMI_RX_PLL_VCOCAL_REG, 0x20);
	hdmi_ग_लिखोb(ctx, HDMI_RX_EQ_DATA0_REG, 0x8A);
	hdmi_ग_लिखोb(ctx, HDMI_RX_EQ_DATA1_REG, 0x6A);
	hdmi_ग_लिखोb(ctx, HDMI_RX_EQ_DATA2_REG, 0xAA);
	hdmi_ग_लिखोb(ctx, HDMI_RX_EQ_DATA3_REG, 0xCA);
	hdmi_ग_लिखोb(ctx, HDMI_RX_EQ_DATA4_REG, 0xEA);
	hdmi_ग_लिखोb(ctx, HDMI_RX_TMDS_ZONE_CTRL_REG, 0xA0);
	hdmi_ग_लिखोb(ctx, HDMI_RX_TMDS_MODE_CTRL_REG, 0x00);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_TMDS_CCTRL, 0x34);
	hdmi_ग_लिखोb(ctx, 0x45, 0x44);
	hdmi_ग_लिखोb(ctx, 0x31, 0x0A);
	hdmi_ग_लिखोb(ctx, HDMI_RX_TMDS0_CCTRL1_REG, 0xC1);

	वापस sii9234_clear_error(ctx);
पूर्ण

अटल पूर्णांक sii9234_mhl_tx_ctl_पूर्णांक(काष्ठा sii9234 *ctx)
अणु
	mhl_tx_ग_लिखोb(ctx, MHL_TX_MHLTX_CTL1_REG, 0xD0);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_MHLTX_CTL2_REG, 0xFC);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_MHLTX_CTL4_REG, 0xEB);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_MHLTX_CTL7_REG, 0x0C);

	वापस sii9234_clear_error(ctx);
पूर्ण

अटल पूर्णांक sii9234_reset(काष्ठा sii9234 *ctx)
अणु
	पूर्णांक ret;

	sii9234_clear_error(ctx);

	ret = sii9234_घातer_init(ctx);
	अगर (ret < 0)
		वापस ret;
	ret = sii9234_cbus_reset(ctx);
	अगर (ret < 0)
		वापस ret;
	ret = sii9234_hdmi_init(ctx);
	अगर (ret < 0)
		वापस ret;
	ret = sii9234_mhl_tx_ctl_पूर्णांक(ctx);
	अगर (ret < 0)
		वापस ret;

	/* Enable HDCP Compliance safety */
	mhl_tx_ग_लिखोb(ctx, 0x2B, 0x01);
	/* CBUS discovery cycle समय क्रम each drive and भग्न = 150us */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL1_REG, 0x04, 0x06);
	/* Clear bit 6 (reg_skip_rgnd) */
	mhl_tx_ग_लिखोb(ctx, MHL_TX_DISC_CTRL2_REG, (1 << 7) /* Reserved */
		      | 2 << ATT_THRESH_SHIFT | DEGLITCH_TIME_50MS);
	/*
	 * Changed from 66 to 65 क्रम 94[1:0] = 01 = 5k reg_cbusmhl_pup_sel
	 * 1.8V CBUS VTH & GND threshold
	 * to meet CTS 3.3.7.2 spec
	 */
	mhl_tx_ग_लिखोb(ctx, MHL_TX_DISC_CTRL5_REG, 0x77);
	cbus_ग_लिखोbm(ctx, CBUS_LINK_CONTROL_2_REG, ~0, MHL_INIT_TIMEOUT);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_MHLTX_CTL6_REG, 0xA0);
	/* RGND & single discovery attempt (RGND blocking) */
	mhl_tx_ग_लिखोb(ctx, MHL_TX_DISC_CTRL6_REG, BLOCK_RGND_INT |
		      DVRFLT_SEL | SINGLE_ATT);
	/* Use VBUS path of discovery state machine */
	mhl_tx_ग_लिखोb(ctx, MHL_TX_DISC_CTRL8_REG, 0);
	/* 0x92[3] sets the CBUS / ID चयन */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL6_REG, ~0, USB_ID_OVR);
	/*
	 * To allow RGND engine to operate correctly.
	 * When moving the chip from D2 to D0 (घातer up, init regs)
	 * the values should be
	 * 94[1:0] = 01  reg_cbusmhl_pup_sel[1:0] should be set क्रम 5k
	 * 93[7:6] = 10  reg_cbusdisc_pup_sel[1:0] should be
	 * set क्रम 10k (शेष)
	 * 93[5:4] = 00  reg_cbusidle_pup_sel[1:0] = खोलो (शेष)
	 */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL3_REG, ~0, 0x86);
	/*
	 * Change from CC to 8C to match 5K
	 * to meet CTS 3.3.72 spec
	 */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL4_REG, ~0, 0x8C);
	/* Configure the पूर्णांकerrupt as active high */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_INT_CTRL_REG, 0, 0x06);

	msleep(25);

	/* Release usb_id चयन */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL6_REG, 0,  USB_ID_OVR);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_DISC_CTRL1_REG, 0x27);

	ret = sii9234_clear_error(ctx);
	अगर (ret < 0)
		वापस ret;
	ret = sii9234_cbus_init(ctx);
	अगर (ret < 0)
		वापस ret;

	/* Enable Auto soft reset on SCDT = 0 */
	mhl_tx_ग_लिखोb(ctx, 0x05, 0x04);
	/* HDMI Transcode mode enable */
	mhl_tx_ग_लिखोb(ctx, 0x0D, 0x1C);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_INTR4_ENABLE_REG,
		      RGND_READY_MASK | CBUS_LKOUT_MASK
			| MHL_DISC_FAIL_MASK | MHL_EST_MASK);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_INTR1_ENABLE_REG, 0x60);

	/* This poपूर्णांक is very important beक्रमe measure RGND impedance */
	क्रमce_usb_id_चयन_खोलो(ctx);
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL4_REG, 0, 0xF0);
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL5_REG, 0, 0x03);
	release_usb_id_चयन_खोलो(ctx);

	/* Force upstream HPD to 0 when not in MHL mode */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_INT_CTRL_REG, 0, 1 << 5);
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_INT_CTRL_REG, ~0, 1 << 4);

	वापस sii9234_clear_error(ctx);
पूर्ण

अटल पूर्णांक sii9234_जाओ_d3(काष्ठा sii9234 *ctx)
अणु
	पूर्णांक ret;

	dev_dbg(ctx->dev, "sii9234: detection started d3\n");

	ret = sii9234_reset(ctx);
	अगर (ret < 0)
		जाओ निकास;

	hdmi_ग_लिखोb(ctx, 0x01, 0x03);
	tpi_ग_लिखोbm(ctx, TPI_DPD_REG, 0, 1);
	/* I2C above is expected to fail because घातer goes करोwn */
	sii9234_clear_error(ctx);

	ctx->state = ST_D3;

	वापस 0;
 निकास:
	dev_err(ctx->dev, "%s failed\n", __func__);
	वापस -1;
पूर्ण

अटल पूर्णांक sii9234_hw_on(काष्ठा sii9234 *ctx)
अणु
	वापस regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
पूर्ण

अटल व्योम sii9234_hw_off(काष्ठा sii9234 *ctx)
अणु
	gpiod_set_value(ctx->gpio_reset, 1);
	msleep(20);
	regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
पूर्ण

अटल व्योम sii9234_hw_reset(काष्ठा sii9234 *ctx)
अणु
	gpiod_set_value(ctx->gpio_reset, 1);
	msleep(20);
	gpiod_set_value(ctx->gpio_reset, 0);
पूर्ण

अटल व्योम sii9234_cable_in(काष्ठा sii9234 *ctx)
अणु
	पूर्णांक ret;

	mutex_lock(&ctx->lock);
	अगर (ctx->state != ST_OFF)
		जाओ unlock;
	ret = sii9234_hw_on(ctx);
	अगर (ret < 0)
		जाओ unlock;

	sii9234_hw_reset(ctx);
	sii9234_जाओ_d3(ctx);
	/* To aव्योम irq storm, when hw is in meta state */
	enable_irq(to_i2c_client(ctx->dev)->irq);

unlock:
	mutex_unlock(&ctx->lock);
पूर्ण

अटल व्योम sii9234_cable_out(काष्ठा sii9234 *ctx)
अणु
	mutex_lock(&ctx->lock);

	अगर (ctx->state == ST_OFF)
		जाओ unlock;

	disable_irq(to_i2c_client(ctx->dev)->irq);
	tpi_ग_लिखोb(ctx, TPI_DPD_REG, 0);
	/* Turn on&off hpd festure क्रम only QCT HDMI */
	sii9234_hw_off(ctx);

	ctx->state = ST_OFF;

unlock:
	mutex_unlock(&ctx->lock);
पूर्ण

अटल क्रमागत sii9234_state sii9234_rgnd_पढ़ोy_irq(काष्ठा sii9234 *ctx)
अणु
	पूर्णांक value;

	अगर (ctx->state == ST_D3) अणु
		पूर्णांक ret;

		dev_dbg(ctx->dev, "RGND_READY_INT\n");
		sii9234_hw_reset(ctx);

		ret = sii9234_reset(ctx);
		अगर (ret < 0) अणु
			dev_err(ctx->dev, "sii9234_reset() failed\n");
			वापस ST_FAILURE;
		पूर्ण

		वापस ST_RGND_INIT;
	पूर्ण

	/* Got पूर्णांकerrupt in inappropriate state */
	अगर (ctx->state != ST_RGND_INIT)
		वापस ST_FAILURE;

	value = mhl_tx_पढ़ोb(ctx, MHL_TX_STAT2_REG);
	अगर (sii9234_clear_error(ctx))
		वापस ST_FAILURE;

	अगर ((value & RGND_INTP_MASK) != RGND_INTP_1K) अणु
		dev_warn(ctx->dev, "RGND is not 1k\n");
		वापस ST_RGND_INIT;
	पूर्ण
	dev_dbg(ctx->dev, "RGND 1K!!\n");
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL4_REG, ~0, 0x8C);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_DISC_CTRL5_REG, 0x77);
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL6_REG, ~0, 0x05);
	अगर (sii9234_clear_error(ctx))
		वापस ST_FAILURE;

	msleep(T_SRC_VBUS_CBUS_TO_STABLE);
	वापस ST_RGND_1K;
पूर्ण

अटल क्रमागत sii9234_state sii9234_mhl_established(काष्ठा sii9234 *ctx)
अणु
	dev_dbg(ctx->dev, "mhl est interrupt\n");

	/* Discovery override */
	mhl_tx_ग_लिखोb(ctx, MHL_TX_MHLTX_CTL1_REG, 0x10);
	/* Increase DDC translation layer समयr (byte mode) */
	cbus_ग_लिखोb(ctx, 0x07, 0x32);
	cbus_ग_लिखोbm(ctx, 0x44, ~0, 1 << 1);
	/* Keep the discovery enabled. Need RGND पूर्णांकerrupt */
	mhl_tx_ग_लिखोbm(ctx, MHL_TX_DISC_CTRL1_REG, ~0, 1);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_INTR1_ENABLE_REG,
		      RSEN_CHANGE_INT_MASK | HPD_CHANGE_INT_MASK);

	अगर (sii9234_clear_error(ctx))
		वापस ST_FAILURE;

	वापस ST_MHL_ESTABLISHED;
पूर्ण

अटल क्रमागत sii9234_state sii9234_hpd_change(काष्ठा sii9234 *ctx)
अणु
	पूर्णांक value;

	value = cbus_पढ़ोb(ctx, CBUS_MSC_REQ_ABORT_REASON_REG);
	अगर (sii9234_clear_error(ctx))
		वापस ST_FAILURE;

	अगर (value & SET_HPD_DOWNSTREAM) अणु
		/* Downstream HPD High, Enable TMDS */
		sii9234_पंचांगds_control(ctx, true);
	पूर्ण अन्यथा अणु
		/* Downstream HPD Low, Disable TMDS */
		sii9234_पंचांगds_control(ctx, false);
	पूर्ण

	वापस ctx->state;
पूर्ण

अटल क्रमागत sii9234_state sii9234_rsen_change(काष्ठा sii9234 *ctx)
अणु
	पूर्णांक value;

	/* Work_around code to handle wrong पूर्णांकerrupt */
	अगर (ctx->state != ST_RGND_1K) अणु
		dev_err(ctx->dev, "RSEN_HIGH without RGND_1K\n");
		वापस ST_FAILURE;
	पूर्ण
	value = mhl_tx_पढ़ोb(ctx, MHL_TX_SYSSTAT_REG);
	अगर (value < 0)
		वापस ST_FAILURE;

	अगर (value & RSEN_STATUS) अणु
		dev_dbg(ctx->dev, "MHL cable connected.. RSEN High\n");
		वापस ST_RSEN_HIGH;
	पूर्ण
	dev_dbg(ctx->dev, "RSEN lost\n");
	/*
	 * Once RSEN loss is confirmed,we need to check
	 * based on cable status and chip घातer status,whether
	 * it is SINK Loss(HDMI cable not connected, TV Off)
	 * or MHL cable disconnection
	 * TODO: Define the below mhl_disconnection()
	 */
	msleep(T_SRC_RXSENSE_DEGLITCH);
	value = mhl_tx_पढ़ोb(ctx, MHL_TX_SYSSTAT_REG);
	अगर (value < 0)
		वापस ST_FAILURE;
	dev_dbg(ctx->dev, "sys_stat: %x\n", value);

	अगर (value & RSEN_STATUS) अणु
		dev_dbg(ctx->dev, "RSEN recovery\n");
		वापस ST_RSEN_HIGH;
	पूर्ण
	dev_dbg(ctx->dev, "RSEN Really LOW\n");
	/* To meet CTS 3.3.22.2 spec */
	sii9234_पंचांगds_control(ctx, false);
	क्रमce_usb_id_चयन_खोलो(ctx);
	release_usb_id_चयन_खोलो(ctx);

	वापस ST_FAILURE;
पूर्ण

अटल irqवापस_t sii9234_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sii9234 *ctx = data;
	पूर्णांक पूर्णांकr1, पूर्णांकr4;
	पूर्णांक पूर्णांकr1_en, पूर्णांकr4_en;
	पूर्णांक cbus_पूर्णांकr1, cbus_पूर्णांकr2;

	dev_dbg(ctx->dev, "%s\n", __func__);

	mutex_lock(&ctx->lock);

	पूर्णांकr1 = mhl_tx_पढ़ोb(ctx, MHL_TX_INTR1_REG);
	पूर्णांकr4 = mhl_tx_पढ़ोb(ctx, MHL_TX_INTR4_REG);
	पूर्णांकr1_en = mhl_tx_पढ़ोb(ctx, MHL_TX_INTR1_ENABLE_REG);
	पूर्णांकr4_en = mhl_tx_पढ़ोb(ctx, MHL_TX_INTR4_ENABLE_REG);
	cbus_पूर्णांकr1 = cbus_पढ़ोb(ctx, CBUS_INT_STATUS_1_REG);
	cbus_पूर्णांकr2 = cbus_पढ़ोb(ctx, CBUS_INT_STATUS_2_REG);

	अगर (sii9234_clear_error(ctx))
		जाओ करोne;

	dev_dbg(ctx->dev, "irq %02x/%02x %02x/%02x %02x/%02x\n",
		पूर्णांकr1, पूर्णांकr1_en, पूर्णांकr4, पूर्णांकr4_en, cbus_पूर्णांकr1, cbus_पूर्णांकr2);

	अगर (पूर्णांकr4 & RGND_READY_INT)
		ctx->state = sii9234_rgnd_पढ़ोy_irq(ctx);
	अगर (पूर्णांकr1 & RSEN_CHANGE_INT)
		ctx->state = sii9234_rsen_change(ctx);
	अगर (पूर्णांकr4 & MHL_EST_INT)
		ctx->state = sii9234_mhl_established(ctx);
	अगर (पूर्णांकr1 & HPD_CHANGE_INT)
		ctx->state = sii9234_hpd_change(ctx);
	अगर (पूर्णांकr4 & CBUS_LKOUT_INT)
		ctx->state = ST_FAILURE;
	अगर (पूर्णांकr4 & MHL_DISC_FAIL_INT)
		ctx->state = ST_FAILURE_DISCOVERY;

 करोne:
	/* Clean पूर्णांकerrupt status and pending flags */
	mhl_tx_ग_लिखोb(ctx, MHL_TX_INTR1_REG, पूर्णांकr1);
	mhl_tx_ग_लिखोb(ctx, MHL_TX_INTR4_REG, पूर्णांकr4);
	cbus_ग_लिखोb(ctx, CBUS_MHL_STATUS_REG_0, 0xFF);
	cbus_ग_लिखोb(ctx, CBUS_MHL_STATUS_REG_1, 0xFF);
	cbus_ग_लिखोb(ctx, CBUS_INT_STATUS_1_REG, cbus_पूर्णांकr1);
	cbus_ग_लिखोb(ctx, CBUS_INT_STATUS_2_REG, cbus_पूर्णांकr2);

	sii9234_clear_error(ctx);

	अगर (ctx->state == ST_FAILURE) अणु
		dev_dbg(ctx->dev, "try to reset after failure\n");
		sii9234_hw_reset(ctx);
		sii9234_जाओ_d3(ctx);
	पूर्ण

	अगर (ctx->state == ST_FAILURE_DISCOVERY) अणु
		dev_err(ctx->dev, "discovery failed, no power for MHL?\n");
		tpi_ग_लिखोbm(ctx, TPI_DPD_REG, 0, 1);
		ctx->state = ST_D3;
	पूर्ण

	mutex_unlock(&ctx->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sii9234_init_resources(काष्ठा sii9234 *ctx,
				  काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक ret;

	अगर (!ctx->dev->of_node) अणु
		dev_err(ctx->dev, "not DT device\n");
		वापस -ENODEV;
	पूर्ण

	ctx->gpio_reset = devm_gpiod_get(ctx->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(ctx->gpio_reset)) अणु
		dev_err(ctx->dev, "failed to get reset gpio from DT\n");
		वापस PTR_ERR(ctx->gpio_reset);
	पूर्ण

	ctx->supplies[0].supply = "avcc12";
	ctx->supplies[1].supply = "avcc33";
	ctx->supplies[2].supply = "iovcc18";
	ctx->supplies[3].supply = "cvcc12";
	ret = devm_regulator_bulk_get(ctx->dev, 4, ctx->supplies);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(ctx->dev, "regulator_bulk failed\n");
		वापस ret;
	पूर्ण

	ctx->client[I2C_MHL] = client;

	ctx->client[I2C_TPI] = devm_i2c_new_dummy_device(&client->dev, adapter,
							 I2C_TPI_ADDR);
	अगर (IS_ERR(ctx->client[I2C_TPI])) अणु
		dev_err(ctx->dev, "failed to create TPI client\n");
		वापस PTR_ERR(ctx->client[I2C_TPI]);
	पूर्ण

	ctx->client[I2C_HDMI] = devm_i2c_new_dummy_device(&client->dev, adapter,
							  I2C_HDMI_ADDR);
	अगर (IS_ERR(ctx->client[I2C_HDMI])) अणु
		dev_err(ctx->dev, "failed to create HDMI RX client\n");
		वापस PTR_ERR(ctx->client[I2C_HDMI]);
	पूर्ण

	ctx->client[I2C_CBUS] = devm_i2c_new_dummy_device(&client->dev, adapter,
							  I2C_CBUS_ADDR);
	अगर (IS_ERR(ctx->client[I2C_CBUS])) अणु
		dev_err(ctx->dev, "failed to create CBUS client\n");
		वापस PTR_ERR(ctx->client[I2C_CBUS]);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा sii9234 *bridge_to_sii9234(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा sii9234, bridge);
पूर्ण

अटल क्रमागत drm_mode_status sii9234_mode_valid(काष्ठा drm_bridge *bridge,
					 स्थिर काष्ठा drm_display_info *info,
					 स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी > MHL1_MAX_CLK)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs sii9234_bridge_funcs = अणु
	.mode_valid = sii9234_mode_valid,
पूर्ण;

अटल पूर्णांक sii9234_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा sii9234 *ctx;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = dev;
	mutex_init(&ctx->lock);

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(dev, "I2C adapter lacks SMBUS feature\n");
		वापस -EIO;
	पूर्ण

	अगर (!client->irq) अणु
		dev_err(dev, "no irq provided\n");
		वापस -EINVAL;
	पूर्ण

	irq_set_status_flags(client->irq, IRQ_NOAUTOEN);
	ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
					sii9234_irq_thपढ़ो,
					IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
					"sii9234", ctx);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to install IRQ handler\n");
		वापस ret;
	पूर्ण

	ret = sii9234_init_resources(ctx, client);
	अगर (ret < 0)
		वापस ret;

	i2c_set_clientdata(client, ctx);

	ctx->bridge.funcs = &sii9234_bridge_funcs;
	ctx->bridge.of_node = dev->of_node;
	drm_bridge_add(&ctx->bridge);

	sii9234_cable_in(ctx);

	वापस 0;
पूर्ण

अटल पूर्णांक sii9234_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा sii9234 *ctx = i2c_get_clientdata(client);

	sii9234_cable_out(ctx);
	drm_bridge_हटाओ(&ctx->bridge);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sii9234_dt_match[] = अणु
	अणु .compatible = "sil,sii9234" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sii9234_dt_match);

अटल स्थिर काष्ठा i2c_device_id sii9234_id[] = अणु
	अणु "SII9234", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sii9234_id);

अटल काष्ठा i2c_driver sii9234_driver = अणु
	.driver = अणु
		.name	= "sii9234",
		.of_match_table = sii9234_dt_match,
	पूर्ण,
	.probe = sii9234_probe,
	.हटाओ = sii9234_हटाओ,
	.id_table = sii9234_id,
पूर्ण;

module_i2c_driver(sii9234_driver);
MODULE_LICENSE("GPL");
