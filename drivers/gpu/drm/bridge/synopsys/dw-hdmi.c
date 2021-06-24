<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DesignWare High-Definition Mulसमयdia Interface (HDMI) driver
 *
 * Copyright (C) 2013-2015 Mentor Graphics Inc.
 * Copyright (C) 2011-2013 Freescale Semiconductor, Inc.
 * Copyright (C) 2010, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/spinlock.h>

#समावेश <media/cec-notअगरier.h>

#समावेश <uapi/linux/media-bus-क्रमmat.h>
#समावेश <uapi/linux/videodev2.h>

#समावेश <drm/bridge/dw_hdmi.h>
#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_scdc_helper.h>

#समावेश "dw-hdmi-audio.h"
#समावेश "dw-hdmi-cec.h"
#समावेश "dw-hdmi.h"

#घोषणा DDC_CI_ADDR		0x37
#घोषणा DDC_SEGMENT_ADDR	0x30

#घोषणा HDMI_EDID_LEN		512

/* DW-HDMI Controller >= 0x200a are at least compliant with SCDC version 1 */
#घोषणा SCDC_MIN_SOURCE_VERSION	0x1

#घोषणा HDMI14_MAX_TMDSCLK	340000000

क्रमागत hdmi_datamap अणु
	RGB444_8B = 0x01,
	RGB444_10B = 0x03,
	RGB444_12B = 0x05,
	RGB444_16B = 0x07,
	YCbCr444_8B = 0x09,
	YCbCr444_10B = 0x0B,
	YCbCr444_12B = 0x0D,
	YCbCr444_16B = 0x0F,
	YCbCr422_8B = 0x16,
	YCbCr422_10B = 0x14,
	YCbCr422_12B = 0x12,
पूर्ण;

अटल स्थिर u16 csc_coeff_शेष[3][4] = अणु
	अणु 0x2000, 0x0000, 0x0000, 0x0000 पूर्ण,
	अणु 0x0000, 0x2000, 0x0000, 0x0000 पूर्ण,
	अणु 0x0000, 0x0000, 0x2000, 0x0000 पूर्ण
पूर्ण;

अटल स्थिर u16 csc_coeff_rgb_out_eitu601[3][4] = अणु
	अणु 0x2000, 0x6926, 0x74fd, 0x010e पूर्ण,
	अणु 0x2000, 0x2cdd, 0x0000, 0x7e9a पूर्ण,
	अणु 0x2000, 0x0000, 0x38b4, 0x7e3b पूर्ण
पूर्ण;

अटल स्थिर u16 csc_coeff_rgb_out_eitu709[3][4] = अणु
	अणु 0x2000, 0x7106, 0x7a02, 0x00a7 पूर्ण,
	अणु 0x2000, 0x3264, 0x0000, 0x7e6d पूर्ण,
	अणु 0x2000, 0x0000, 0x3b61, 0x7e25 पूर्ण
पूर्ण;

अटल स्थिर u16 csc_coeff_rgb_in_eitu601[3][4] = अणु
	अणु 0x2591, 0x1322, 0x074b, 0x0000 पूर्ण,
	अणु 0x6535, 0x2000, 0x7acc, 0x0200 पूर्ण,
	अणु 0x6acd, 0x7534, 0x2000, 0x0200 पूर्ण
पूर्ण;

अटल स्थिर u16 csc_coeff_rgb_in_eitu709[3][4] = अणु
	अणु 0x2dc5, 0x0d9b, 0x049e, 0x0000 पूर्ण,
	अणु 0x62f0, 0x2000, 0x7d11, 0x0200 पूर्ण,
	अणु 0x6756, 0x78ab, 0x2000, 0x0200 पूर्ण
पूर्ण;

अटल स्थिर u16 csc_coeff_rgb_full_to_rgb_limited[3][4] = अणु
	अणु 0x1b7c, 0x0000, 0x0000, 0x0020 पूर्ण,
	अणु 0x0000, 0x1b7c, 0x0000, 0x0020 पूर्ण,
	अणु 0x0000, 0x0000, 0x1b7c, 0x0020 पूर्ण
पूर्ण;

काष्ठा hdmi_vmode अणु
	bool mdataenablepolarity;

	अचिन्हित पूर्णांक mpixelघड़ी;
	अचिन्हित पूर्णांक mpixelrepetitioninput;
	अचिन्हित पूर्णांक mpixelrepetitionoutput;
	अचिन्हित पूर्णांक mपंचांगdsघड़ी;
पूर्ण;

काष्ठा hdmi_data_info अणु
	अचिन्हित पूर्णांक enc_in_bus_क्रमmat;
	अचिन्हित पूर्णांक enc_out_bus_क्रमmat;
	अचिन्हित पूर्णांक enc_in_encoding;
	अचिन्हित पूर्णांक enc_out_encoding;
	अचिन्हित पूर्णांक pix_repet_factor;
	अचिन्हित पूर्णांक hdcp_enable;
	काष्ठा hdmi_vmode video_mode;
	bool rgb_limited_range;
पूर्ण;

काष्ठा dw_hdmi_i2c अणु
	काष्ठा i2c_adapter	adap;

	काष्ठा mutex		lock;	/* used to serialize data transfers */
	काष्ठा completion	cmp;
	u8			stat;

	u8			slave_reg;
	bool			is_regaddr;
	bool			is_segment;
पूर्ण;

काष्ठा dw_hdmi_phy_data अणु
	क्रमागत dw_hdmi_phy_type type;
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक gen;
	bool has_svsret;
	पूर्णांक (*configure)(काष्ठा dw_hdmi *hdmi,
			 स्थिर काष्ठा dw_hdmi_plat_data *pdata,
			 अचिन्हित दीर्घ mpixelघड़ी);
पूर्ण;

काष्ठा dw_hdmi अणु
	काष्ठा drm_connector connector;
	काष्ठा drm_bridge bridge;

	अचिन्हित पूर्णांक version;

	काष्ठा platक्रमm_device *audio;
	काष्ठा platक्रमm_device *cec;
	काष्ठा device *dev;
	काष्ठा clk *isfr_clk;
	काष्ठा clk *iahb_clk;
	काष्ठा clk *cec_clk;
	काष्ठा dw_hdmi_i2c *i2c;

	काष्ठा hdmi_data_info hdmi_data;
	स्थिर काष्ठा dw_hdmi_plat_data *plat_data;

	पूर्णांक vic;

	u8 edid[HDMI_EDID_LEN];

	काष्ठा अणु
		स्थिर काष्ठा dw_hdmi_phy_ops *ops;
		स्थिर अक्षर *name;
		व्योम *data;
		bool enabled;
	पूर्ण phy;

	काष्ठा drm_display_mode previous_mode;

	काष्ठा i2c_adapter *ddc;
	व्योम __iomem *regs;
	bool sink_is_hdmi;
	bool sink_has_audio;

	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *शेष_state;
	काष्ठा pinctrl_state *unwedge_state;

	काष्ठा mutex mutex;		/* क्रम state below and previous_mode */
	क्रमागत drm_connector_क्रमce क्रमce;	/* mutex-रक्षित क्रमce state */
	काष्ठा drm_connector *curr_conn;/* current connector (only valid when !disabled) */
	bool disabled;			/* DRM has disabled our bridge */
	bool bridge_is_on;		/* indicates the bridge is on */
	bool rxsense;			/* rxsense state */
	u8 phy_mask;			/* desired phy पूर्णांक mask settings */
	u8 mc_clkdis;			/* घड़ी disable रेजिस्टर */

	spinlock_t audio_lock;
	काष्ठा mutex audio_mutex;
	अचिन्हित पूर्णांक sample_rate;
	अचिन्हित पूर्णांक audio_cts;
	अचिन्हित पूर्णांक audio_n;
	bool audio_enable;

	अचिन्हित पूर्णांक reg_shअगरt;
	काष्ठा regmap *regm;
	व्योम (*enable_audio)(काष्ठा dw_hdmi *hdmi);
	व्योम (*disable_audio)(काष्ठा dw_hdmi *hdmi);

	काष्ठा mutex cec_notअगरier_mutex;
	काष्ठा cec_notअगरier *cec_notअगरier;

	hdmi_codec_plugged_cb plugged_cb;
	काष्ठा device *codec_dev;
	क्रमागत drm_connector_status last_connector_result;
पूर्ण;

#घोषणा HDMI_IH_PHY_STAT0_RX_SENSE \
	(HDMI_IH_PHY_STAT0_RX_SENSE0 | HDMI_IH_PHY_STAT0_RX_SENSE1 | \
	 HDMI_IH_PHY_STAT0_RX_SENSE2 | HDMI_IH_PHY_STAT0_RX_SENSE3)

#घोषणा HDMI_PHY_RX_SENSE \
	(HDMI_PHY_RX_SENSE0 | HDMI_PHY_RX_SENSE1 | \
	 HDMI_PHY_RX_SENSE2 | HDMI_PHY_RX_SENSE3)

अटल अंतरभूत व्योम hdmi_ग_लिखोb(काष्ठा dw_hdmi *hdmi, u8 val, पूर्णांक offset)
अणु
	regmap_ग_लिखो(hdmi->regm, offset << hdmi->reg_shअगरt, val);
पूर्ण

अटल अंतरभूत u8 hdmi_पढ़ोb(काष्ठा dw_hdmi *hdmi, पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक val = 0;

	regmap_पढ़ो(hdmi->regm, offset << hdmi->reg_shअगरt, &val);

	वापस val;
पूर्ण

अटल व्योम handle_plugged_change(काष्ठा dw_hdmi *hdmi, bool plugged)
अणु
	अगर (hdmi->plugged_cb && hdmi->codec_dev)
		hdmi->plugged_cb(hdmi->codec_dev, plugged);
पूर्ण

पूर्णांक dw_hdmi_set_plugged_cb(काष्ठा dw_hdmi *hdmi, hdmi_codec_plugged_cb fn,
			   काष्ठा device *codec_dev)
अणु
	bool plugged;

	mutex_lock(&hdmi->mutex);
	hdmi->plugged_cb = fn;
	hdmi->codec_dev = codec_dev;
	plugged = hdmi->last_connector_result == connector_status_connected;
	handle_plugged_change(hdmi, plugged);
	mutex_unlock(&hdmi->mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_set_plugged_cb);

अटल व्योम hdmi_modb(काष्ठा dw_hdmi *hdmi, u8 data, u8 mask, अचिन्हित reg)
अणु
	regmap_update_bits(hdmi->regm, reg << hdmi->reg_shअगरt, mask, data);
पूर्ण

अटल व्योम hdmi_mask_ग_लिखोb(काष्ठा dw_hdmi *hdmi, u8 data, अचिन्हित पूर्णांक reg,
			     u8 shअगरt, u8 mask)
अणु
	hdmi_modb(hdmi, data << shअगरt, mask, reg);
पूर्ण

अटल व्योम dw_hdmi_i2c_init(काष्ठा dw_hdmi *hdmi)
अणु
	hdmi_ग_लिखोb(hdmi, HDMI_PHY_I2CM_INT_ADDR_DONE_POL,
		    HDMI_PHY_I2CM_INT_ADDR);

	hdmi_ग_लिखोb(hdmi, HDMI_PHY_I2CM_CTLINT_ADDR_NAC_POL |
		    HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_POL,
		    HDMI_PHY_I2CM_CTLINT_ADDR);

	/* Software reset */
	hdmi_ग_लिखोb(hdmi, 0x00, HDMI_I2CM_SOFTRSTZ);

	/* Set Standard Mode speed (determined to be 100KHz on iMX6) */
	hdmi_ग_लिखोb(hdmi, 0x00, HDMI_I2CM_DIV);

	/* Set करोne, not acknowledged and arbitration पूर्णांकerrupt polarities */
	hdmi_ग_लिखोb(hdmi, HDMI_I2CM_INT_DONE_POL, HDMI_I2CM_INT);
	hdmi_ग_लिखोb(hdmi, HDMI_I2CM_CTLINT_NAC_POL | HDMI_I2CM_CTLINT_ARB_POL,
		    HDMI_I2CM_CTLINT);

	/* Clear DONE and ERROR पूर्णांकerrupts */
	hdmi_ग_लिखोb(hdmi, HDMI_IH_I2CM_STAT0_ERROR | HDMI_IH_I2CM_STAT0_DONE,
		    HDMI_IH_I2CM_STAT0);

	/* Mute DONE and ERROR पूर्णांकerrupts */
	hdmi_ग_लिखोb(hdmi, HDMI_IH_I2CM_STAT0_ERROR | HDMI_IH_I2CM_STAT0_DONE,
		    HDMI_IH_MUTE_I2CM_STAT0);
पूर्ण

अटल bool dw_hdmi_i2c_unwedge(काष्ठा dw_hdmi *hdmi)
अणु
	/* If no unwedge state then give up */
	अगर (!hdmi->unwedge_state)
		वापस false;

	dev_info(hdmi->dev, "Attempting to unwedge stuck i2c bus\n");

	/*
	 * This is a huge hack to workaround a problem where the dw_hdmi i2c
	 * bus could someबार get wedged.  Once wedged there करोesn't appear
	 * to be any way to unwedge it (including the HDMI_I2CM_SOFTRSTZ)
	 * other than pulsing the SDA line.
	 *
	 * We appear to be able to pulse the SDA line (in the eyes of dw_hdmi)
	 * by:
	 * 1. Remux the pin as a GPIO output, driven low.
	 * 2. Wait a little जबतक.  1 ms seems to work, but we'll करो 10.
	 * 3. Immediately jump to remux the pin as dw_hdmi i2c again.
	 *
	 * At the moment of remuxing, the line will still be low due to its
	 * recent stपूर्णांक as an output, but then it will be pulled high by the
	 * (presumed) बाह्यal pullup.  dw_hdmi seems to see this as a rising
	 * edge and that seems to get it out of its jam.
	 *
	 * This wedging was only ever seen on one TV, and only on one of
	 * its HDMI ports.  It happened when the TV was घातered on जबतक the
	 * device was plugged in.  A scope trace shows the TV bringing both SDA
	 * and SCL low, then bringing them both back up at roughly the same
	 * समय.  Presumably this confuses dw_hdmi because it saw activity but
	 * no real STOP (maybe it thinks there's another master on the bus?).
	 * Giving it a clean rising edge of SDA जबतक SCL is alपढ़ोy high
	 * presumably makes dw_hdmi see a STOP which seems to bring dw_hdmi out
	 * of its stupor.
	 *
	 * Note that after coming back alive, transfers seem to immediately
	 * resume, so अगर we unwedge due to a समयout we should रुको a little
	 * दीर्घer क्रम our transfer to finish, since it might have just started
	 * now.
	 */
	pinctrl_select_state(hdmi->pinctrl, hdmi->unwedge_state);
	msleep(10);
	pinctrl_select_state(hdmi->pinctrl, hdmi->शेष_state);

	वापस true;
पूर्ण

अटल पूर्णांक dw_hdmi_i2c_रुको(काष्ठा dw_hdmi *hdmi)
अणु
	काष्ठा dw_hdmi_i2c *i2c = hdmi->i2c;
	पूर्णांक stat;

	stat = रुको_क्रम_completion_समयout(&i2c->cmp, HZ / 10);
	अगर (!stat) अणु
		/* If we can't unwedge, वापस समयout */
		अगर (!dw_hdmi_i2c_unwedge(hdmi))
			वापस -EAGAIN;

		/* We tried to unwedge; give it another chance */
		stat = रुको_क्रम_completion_समयout(&i2c->cmp, HZ / 10);
		अगर (!stat)
			वापस -EAGAIN;
	पूर्ण

	/* Check क्रम error condition on the bus */
	अगर (i2c->stat & HDMI_IH_I2CM_STAT0_ERROR)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_i2c_पढ़ो(काष्ठा dw_hdmi *hdmi,
			    अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक length)
अणु
	काष्ठा dw_hdmi_i2c *i2c = hdmi->i2c;
	पूर्णांक ret;

	अगर (!i2c->is_regaddr) अणु
		dev_dbg(hdmi->dev, "set read register address to 0\n");
		i2c->slave_reg = 0x00;
		i2c->is_regaddr = true;
	पूर्ण

	जबतक (length--) अणु
		reinit_completion(&i2c->cmp);

		hdmi_ग_लिखोb(hdmi, i2c->slave_reg++, HDMI_I2CM_ADDRESS);
		अगर (i2c->is_segment)
			hdmi_ग_लिखोb(hdmi, HDMI_I2CM_OPERATION_READ_EXT,
				    HDMI_I2CM_OPERATION);
		अन्यथा
			hdmi_ग_लिखोb(hdmi, HDMI_I2CM_OPERATION_READ,
				    HDMI_I2CM_OPERATION);

		ret = dw_hdmi_i2c_रुको(hdmi);
		अगर (ret)
			वापस ret;

		*buf++ = hdmi_पढ़ोb(hdmi, HDMI_I2CM_DATAI);
	पूर्ण
	i2c->is_segment = false;

	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_i2c_ग_लिखो(काष्ठा dw_hdmi *hdmi,
			     अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक length)
अणु
	काष्ठा dw_hdmi_i2c *i2c = hdmi->i2c;
	पूर्णांक ret;

	अगर (!i2c->is_regaddr) अणु
		/* Use the first ग_लिखो byte as रेजिस्टर address */
		i2c->slave_reg = buf[0];
		length--;
		buf++;
		i2c->is_regaddr = true;
	पूर्ण

	जबतक (length--) अणु
		reinit_completion(&i2c->cmp);

		hdmi_ग_लिखोb(hdmi, *buf++, HDMI_I2CM_DATAO);
		hdmi_ग_लिखोb(hdmi, i2c->slave_reg++, HDMI_I2CM_ADDRESS);
		hdmi_ग_लिखोb(hdmi, HDMI_I2CM_OPERATION_WRITE,
			    HDMI_I2CM_OPERATION);

		ret = dw_hdmi_i2c_रुको(hdmi);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_i2c_xfer(काष्ठा i2c_adapter *adap,
			    काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा dw_hdmi *hdmi = i2c_get_adapdata(adap);
	काष्ठा dw_hdmi_i2c *i2c = hdmi->i2c;
	u8 addr = msgs[0].addr;
	पूर्णांक i, ret = 0;

	अगर (addr == DDC_CI_ADDR)
		/*
		 * The पूर्णांकernal I2C controller करोes not support the multi-byte
		 * पढ़ो and ग_लिखो operations needed क्रम DDC/CI.
		 * TOFIX: Blacklist the DDC/CI address until we filter out
		 * unsupported I2C operations.
		 */
		वापस -EOPNOTSUPP;

	dev_dbg(hdmi->dev, "xfer: num: %d, addr: %#x\n", num, addr);

	क्रम (i = 0; i < num; i++) अणु
		अगर (msgs[i].len == 0) अणु
			dev_dbg(hdmi->dev,
				"unsupported transfer %d/%d, no data\n",
				i + 1, num);
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	mutex_lock(&i2c->lock);

	/* Unmute DONE and ERROR पूर्णांकerrupts */
	hdmi_ग_लिखोb(hdmi, 0x00, HDMI_IH_MUTE_I2CM_STAT0);

	/* Set slave device address taken from the first I2C message */
	hdmi_ग_लिखोb(hdmi, addr, HDMI_I2CM_SLAVE);

	/* Set slave device रेजिस्टर address on transfer */
	i2c->is_regaddr = false;

	/* Set segment poपूर्णांकer क्रम I2C extended पढ़ो mode operation */
	i2c->is_segment = false;

	क्रम (i = 0; i < num; i++) अणु
		dev_dbg(hdmi->dev, "xfer: num: %d/%d, len: %d, flags: %#x\n",
			i + 1, num, msgs[i].len, msgs[i].flags);
		अगर (msgs[i].addr == DDC_SEGMENT_ADDR && msgs[i].len == 1) अणु
			i2c->is_segment = true;
			hdmi_ग_लिखोb(hdmi, DDC_SEGMENT_ADDR, HDMI_I2CM_SEGADDR);
			hdmi_ग_लिखोb(hdmi, *msgs[i].buf, HDMI_I2CM_SEGPTR);
		पूर्ण अन्यथा अणु
			अगर (msgs[i].flags & I2C_M_RD)
				ret = dw_hdmi_i2c_पढ़ो(hdmi, msgs[i].buf,
						       msgs[i].len);
			अन्यथा
				ret = dw_hdmi_i2c_ग_लिखो(hdmi, msgs[i].buf,
							msgs[i].len);
		पूर्ण
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	अगर (!ret)
		ret = num;

	/* Mute DONE and ERROR पूर्णांकerrupts */
	hdmi_ग_लिखोb(hdmi, HDMI_IH_I2CM_STAT0_ERROR | HDMI_IH_I2CM_STAT0_DONE,
		    HDMI_IH_MUTE_I2CM_STAT0);

	mutex_unlock(&i2c->lock);

	वापस ret;
पूर्ण

अटल u32 dw_hdmi_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm dw_hdmi_algorithm = अणु
	.master_xfer	= dw_hdmi_i2c_xfer,
	.functionality	= dw_hdmi_i2c_func,
पूर्ण;

अटल काष्ठा i2c_adapter *dw_hdmi_i2c_adapter(काष्ठा dw_hdmi *hdmi)
अणु
	काष्ठा i2c_adapter *adap;
	काष्ठा dw_hdmi_i2c *i2c;
	पूर्णांक ret;

	i2c = devm_kzalloc(hdmi->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&i2c->lock);
	init_completion(&i2c->cmp);

	adap = &i2c->adap;
	adap->class = I2C_CLASS_DDC;
	adap->owner = THIS_MODULE;
	adap->dev.parent = hdmi->dev;
	adap->algo = &dw_hdmi_algorithm;
	strlcpy(adap->name, "DesignWare HDMI", माप(adap->name));
	i2c_set_adapdata(adap, hdmi);

	ret = i2c_add_adapter(adap);
	अगर (ret) अणु
		dev_warn(hdmi->dev, "cannot add %s I2C adapter\n", adap->name);
		devm_kमुक्त(hdmi->dev, i2c);
		वापस ERR_PTR(ret);
	पूर्ण

	hdmi->i2c = i2c;

	dev_info(hdmi->dev, "registered %s I2C bus driver\n", adap->name);

	वापस adap;
पूर्ण

अटल व्योम hdmi_set_cts_n(काष्ठा dw_hdmi *hdmi, अचिन्हित पूर्णांक cts,
			   अचिन्हित पूर्णांक n)
अणु
	/* Must be set/cleared first */
	hdmi_modb(hdmi, 0, HDMI_AUD_CTS3_CTS_MANUAL, HDMI_AUD_CTS3);

	/* nshअगरt factor = 0 */
	hdmi_modb(hdmi, 0, HDMI_AUD_CTS3_N_SHIFT_MASK, HDMI_AUD_CTS3);

	/* Use स्वतःmatic CTS generation mode when CTS is not set */
	अगर (cts)
		hdmi_ग_लिखोb(hdmi, ((cts >> 16) &
				   HDMI_AUD_CTS3_AUDCTS19_16_MASK) |
				  HDMI_AUD_CTS3_CTS_MANUAL,
			    HDMI_AUD_CTS3);
	अन्यथा
		hdmi_ग_लिखोb(hdmi, 0, HDMI_AUD_CTS3);
	hdmi_ग_लिखोb(hdmi, (cts >> 8) & 0xff, HDMI_AUD_CTS2);
	hdmi_ग_लिखोb(hdmi, cts & 0xff, HDMI_AUD_CTS1);

	hdmi_ग_लिखोb(hdmi, (n >> 16) & 0x0f, HDMI_AUD_N3);
	hdmi_ग_लिखोb(hdmi, (n >> 8) & 0xff, HDMI_AUD_N2);
	hdmi_ग_लिखोb(hdmi, n & 0xff, HDMI_AUD_N1);
पूर्ण

अटल अचिन्हित पूर्णांक hdmi_compute_n(अचिन्हित पूर्णांक freq, अचिन्हित दीर्घ pixel_clk)
अणु
	अचिन्हित पूर्णांक n = (128 * freq) / 1000;
	अचिन्हित पूर्णांक mult = 1;

	जबतक (freq > 48000) अणु
		mult *= 2;
		freq /= 2;
	पूर्ण

	चयन (freq) अणु
	हाल 32000:
		अगर (pixel_clk == 25175000)
			n = 4576;
		अन्यथा अगर (pixel_clk == 27027000)
			n = 4096;
		अन्यथा अगर (pixel_clk == 74176000 || pixel_clk == 148352000)
			n = 11648;
		अन्यथा
			n = 4096;
		n *= mult;
		अवरोध;

	हाल 44100:
		अगर (pixel_clk == 25175000)
			n = 7007;
		अन्यथा अगर (pixel_clk == 74176000)
			n = 17836;
		अन्यथा अगर (pixel_clk == 148352000)
			n = 8918;
		अन्यथा
			n = 6272;
		n *= mult;
		अवरोध;

	हाल 48000:
		अगर (pixel_clk == 25175000)
			n = 6864;
		अन्यथा अगर (pixel_clk == 27027000)
			n = 6144;
		अन्यथा अगर (pixel_clk == 74176000)
			n = 11648;
		अन्यथा अगर (pixel_clk == 148352000)
			n = 5824;
		अन्यथा
			n = 6144;
		n *= mult;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस n;
पूर्ण

/*
 * When transmitting IEC60958 linear PCM audio, these रेजिस्टरs allow to
 * configure the channel status inक्रमmation of all the channel status
 * bits in the IEC60958 frame. For the moment this configuration is only
 * used when the I2S audio पूर्णांकerface, General Purpose Audio (GPA),
 * or AHB audio DMA (AHBAUDDMA) पूर्णांकerface is active
 * (क्रम S/PDIF पूर्णांकerface this inक्रमmation comes from the stream).
 */
व्योम dw_hdmi_set_channel_status(काष्ठा dw_hdmi *hdmi,
				u8 *channel_status)
अणु
	/*
	 * Set channel status रेजिस्टर क्रम frequency and word length.
	 * Use शेष values क्रम other रेजिस्टरs.
	 */
	hdmi_ग_लिखोb(hdmi, channel_status[3], HDMI_FC_AUDSCHNLS7);
	hdmi_ग_लिखोb(hdmi, channel_status[4], HDMI_FC_AUDSCHNLS8);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_set_channel_status);

अटल व्योम hdmi_set_clk_regenerator(काष्ठा dw_hdmi *hdmi,
	अचिन्हित दीर्घ pixel_clk, अचिन्हित पूर्णांक sample_rate)
अणु
	अचिन्हित दीर्घ ftdms = pixel_clk;
	अचिन्हित पूर्णांक n, cts;
	u8 config3;
	u64 पंचांगp;

	n = hdmi_compute_n(sample_rate, pixel_clk);

	config3 = hdmi_पढ़ोb(hdmi, HDMI_CONFIG3_ID);

	/* Only compute CTS when using पूर्णांकernal AHB audio */
	अगर (config3 & HDMI_CONFIG3_AHBAUDDMA) अणु
		/*
		 * Compute the CTS value from the N value.  Note that CTS and N
		 * can be up to 20 bits in total, so we need 64-bit math.  Also
		 * note that our TDMS घड़ी is not fully accurate; it is
		 * accurate to kHz.  This can पूर्णांकroduce an unnecessary reमुख्यder
		 * in the calculation below, so we करोn't try to warn about that.
		 */
		पंचांगp = (u64)ftdms * n;
		करो_भाग(पंचांगp, 128 * sample_rate);
		cts = पंचांगp;

		dev_dbg(hdmi->dev, "%s: fs=%uHz ftdms=%lu.%03luMHz N=%d cts=%d\n",
			__func__, sample_rate,
			ftdms / 1000000, (ftdms / 1000) % 1000,
			n, cts);
	पूर्ण अन्यथा अणु
		cts = 0;
	पूर्ण

	spin_lock_irq(&hdmi->audio_lock);
	hdmi->audio_n = n;
	hdmi->audio_cts = cts;
	hdmi_set_cts_n(hdmi, cts, hdmi->audio_enable ? n : 0);
	spin_unlock_irq(&hdmi->audio_lock);
पूर्ण

अटल व्योम hdmi_init_clk_regenerator(काष्ठा dw_hdmi *hdmi)
अणु
	mutex_lock(&hdmi->audio_mutex);
	hdmi_set_clk_regenerator(hdmi, 74250000, hdmi->sample_rate);
	mutex_unlock(&hdmi->audio_mutex);
पूर्ण

अटल व्योम hdmi_clk_regenerator_update_pixel_घड़ी(काष्ठा dw_hdmi *hdmi)
अणु
	mutex_lock(&hdmi->audio_mutex);
	hdmi_set_clk_regenerator(hdmi, hdmi->hdmi_data.video_mode.mपंचांगdsघड़ी,
				 hdmi->sample_rate);
	mutex_unlock(&hdmi->audio_mutex);
पूर्ण

व्योम dw_hdmi_set_sample_rate(काष्ठा dw_hdmi *hdmi, अचिन्हित पूर्णांक rate)
अणु
	mutex_lock(&hdmi->audio_mutex);
	hdmi->sample_rate = rate;
	hdmi_set_clk_regenerator(hdmi, hdmi->hdmi_data.video_mode.mपंचांगdsघड़ी,
				 hdmi->sample_rate);
	mutex_unlock(&hdmi->audio_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_set_sample_rate);

व्योम dw_hdmi_set_channel_count(काष्ठा dw_hdmi *hdmi, अचिन्हित पूर्णांक cnt)
अणु
	u8 layout;

	mutex_lock(&hdmi->audio_mutex);

	/*
	 * For >2 channel PCM audio, we need to select layout 1
	 * and set an appropriate channel map.
	 */
	अगर (cnt > 2)
		layout = HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_LAYOUT1;
	अन्यथा
		layout = HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_LAYOUT0;

	hdmi_modb(hdmi, layout, HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_MASK,
		  HDMI_FC_AUDSCONF);

	/* Set the audio infoframes channel count */
	hdmi_modb(hdmi, (cnt - 1) << HDMI_FC_AUDICONF0_CC_OFFSET,
		  HDMI_FC_AUDICONF0_CC_MASK, HDMI_FC_AUDICONF0);

	mutex_unlock(&hdmi->audio_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_set_channel_count);

व्योम dw_hdmi_set_channel_allocation(काष्ठा dw_hdmi *hdmi, अचिन्हित पूर्णांक ca)
अणु
	mutex_lock(&hdmi->audio_mutex);

	hdmi_ग_लिखोb(hdmi, ca, HDMI_FC_AUDICONF2);

	mutex_unlock(&hdmi->audio_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_set_channel_allocation);

अटल व्योम hdmi_enable_audio_clk(काष्ठा dw_hdmi *hdmi, bool enable)
अणु
	अगर (enable)
		hdmi->mc_clkdis &= ~HDMI_MC_CLKDIS_AUDCLK_DISABLE;
	अन्यथा
		hdmi->mc_clkdis |= HDMI_MC_CLKDIS_AUDCLK_DISABLE;
	hdmi_ग_लिखोb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);
पूर्ण

अटल व्योम dw_hdmi_ahb_audio_enable(काष्ठा dw_hdmi *hdmi)
अणु
	hdmi_set_cts_n(hdmi, hdmi->audio_cts, hdmi->audio_n);
पूर्ण

अटल व्योम dw_hdmi_ahb_audio_disable(काष्ठा dw_hdmi *hdmi)
अणु
	hdmi_set_cts_n(hdmi, hdmi->audio_cts, 0);
पूर्ण

अटल व्योम dw_hdmi_i2s_audio_enable(काष्ठा dw_hdmi *hdmi)
अणु
	hdmi_set_cts_n(hdmi, hdmi->audio_cts, hdmi->audio_n);
	hdmi_enable_audio_clk(hdmi, true);
पूर्ण

अटल व्योम dw_hdmi_i2s_audio_disable(काष्ठा dw_hdmi *hdmi)
अणु
	hdmi_enable_audio_clk(hdmi, false);
पूर्ण

व्योम dw_hdmi_audio_enable(काष्ठा dw_hdmi *hdmi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hdmi->audio_lock, flags);
	hdmi->audio_enable = true;
	अगर (hdmi->enable_audio)
		hdmi->enable_audio(hdmi);
	spin_unlock_irqrestore(&hdmi->audio_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_audio_enable);

व्योम dw_hdmi_audio_disable(काष्ठा dw_hdmi *hdmi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hdmi->audio_lock, flags);
	hdmi->audio_enable = false;
	अगर (hdmi->disable_audio)
		hdmi->disable_audio(hdmi);
	spin_unlock_irqrestore(&hdmi->audio_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_audio_disable);

अटल bool hdmi_bus_fmt_is_rgb(अचिन्हित पूर्णांक bus_क्रमmat)
अणु
	चयन (bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_RGB888_1X24:
	हाल MEDIA_BUS_FMT_RGB101010_1X30:
	हाल MEDIA_BUS_FMT_RGB121212_1X36:
	हाल MEDIA_BUS_FMT_RGB161616_1X48:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool hdmi_bus_fmt_is_yuv444(अचिन्हित पूर्णांक bus_क्रमmat)
अणु
	चयन (bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_YUV8_1X24:
	हाल MEDIA_BUS_FMT_YUV10_1X30:
	हाल MEDIA_BUS_FMT_YUV12_1X36:
	हाल MEDIA_BUS_FMT_YUV16_1X48:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool hdmi_bus_fmt_is_yuv422(अचिन्हित पूर्णांक bus_क्रमmat)
अणु
	चयन (bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_UYVY10_1X20:
	हाल MEDIA_BUS_FMT_UYVY12_1X24:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool hdmi_bus_fmt_is_yuv420(अचिन्हित पूर्णांक bus_क्रमmat)
अणु
	चयन (bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_UYYVYY8_0_5X24:
	हाल MEDIA_BUS_FMT_UYYVYY10_0_5X30:
	हाल MEDIA_BUS_FMT_UYYVYY12_0_5X36:
	हाल MEDIA_BUS_FMT_UYYVYY16_0_5X48:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक hdmi_bus_fmt_color_depth(अचिन्हित पूर्णांक bus_क्रमmat)
अणु
	चयन (bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_RGB888_1X24:
	हाल MEDIA_BUS_FMT_YUV8_1X24:
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_UYYVYY8_0_5X24:
		वापस 8;

	हाल MEDIA_BUS_FMT_RGB101010_1X30:
	हाल MEDIA_BUS_FMT_YUV10_1X30:
	हाल MEDIA_BUS_FMT_UYVY10_1X20:
	हाल MEDIA_BUS_FMT_UYYVYY10_0_5X30:
		वापस 10;

	हाल MEDIA_BUS_FMT_RGB121212_1X36:
	हाल MEDIA_BUS_FMT_YUV12_1X36:
	हाल MEDIA_BUS_FMT_UYVY12_1X24:
	हाल MEDIA_BUS_FMT_UYYVYY12_0_5X36:
		वापस 12;

	हाल MEDIA_BUS_FMT_RGB161616_1X48:
	हाल MEDIA_BUS_FMT_YUV16_1X48:
	हाल MEDIA_BUS_FMT_UYYVYY16_0_5X48:
		वापस 16;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * this submodule is responsible क्रम the video data synchronization.
 * क्रम example, क्रम RGB 4:4:4 input, the data map is defined as
 *			pinअणु47~40पूर्ण <==> R[7:0]
 *			pinअणु31~24पूर्ण <==> G[7:0]
 *			pinअणु15~8पूर्ण  <==> B[7:0]
 */
अटल व्योम hdmi_video_sample(काष्ठा dw_hdmi *hdmi)
अणु
	पूर्णांक color_क्रमmat = 0;
	u8 val;

	चयन (hdmi->hdmi_data.enc_in_bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		color_क्रमmat = 0x01;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB101010_1X30:
		color_क्रमmat = 0x03;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB121212_1X36:
		color_क्रमmat = 0x05;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB161616_1X48:
		color_क्रमmat = 0x07;
		अवरोध;

	हाल MEDIA_BUS_FMT_YUV8_1X24:
	हाल MEDIA_BUS_FMT_UYYVYY8_0_5X24:
		color_क्रमmat = 0x09;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUV10_1X30:
	हाल MEDIA_BUS_FMT_UYYVYY10_0_5X30:
		color_क्रमmat = 0x0B;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUV12_1X36:
	हाल MEDIA_BUS_FMT_UYYVYY12_0_5X36:
		color_क्रमmat = 0x0D;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUV16_1X48:
	हाल MEDIA_BUS_FMT_UYYVYY16_0_5X48:
		color_क्रमmat = 0x0F;
		अवरोध;

	हाल MEDIA_BUS_FMT_UYVY8_1X16:
		color_क्रमmat = 0x16;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY10_1X20:
		color_क्रमmat = 0x14;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY12_1X24:
		color_क्रमmat = 0x12;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	val = HDMI_TX_INVID0_INTERNAL_DE_GENERATOR_DISABLE |
		((color_क्रमmat << HDMI_TX_INVID0_VIDEO_MAPPING_OFFSET) &
		HDMI_TX_INVID0_VIDEO_MAPPING_MASK);
	hdmi_ग_लिखोb(hdmi, val, HDMI_TX_INVID0);

	/* Enable TX stuffing: When DE is inactive, fix the output data to 0 */
	val = HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABLE |
		HDMI_TX_INSTUFFING_RCRDATA_STUFFING_ENABLE |
		HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABLE;
	hdmi_ग_लिखोb(hdmi, val, HDMI_TX_INSTUFFING);
	hdmi_ग_लिखोb(hdmi, 0x0, HDMI_TX_GYDATA0);
	hdmi_ग_लिखोb(hdmi, 0x0, HDMI_TX_GYDATA1);
	hdmi_ग_लिखोb(hdmi, 0x0, HDMI_TX_RCRDATA0);
	hdmi_ग_लिखोb(hdmi, 0x0, HDMI_TX_RCRDATA1);
	hdmi_ग_लिखोb(hdmi, 0x0, HDMI_TX_BCBDATA0);
	hdmi_ग_लिखोb(hdmi, 0x0, HDMI_TX_BCBDATA1);
पूर्ण

अटल पूर्णांक is_color_space_conversion(काष्ठा dw_hdmi *hdmi)
अणु
	काष्ठा hdmi_data_info *hdmi_data = &hdmi->hdmi_data;
	bool is_input_rgb, is_output_rgb;

	is_input_rgb = hdmi_bus_fmt_is_rgb(hdmi_data->enc_in_bus_क्रमmat);
	is_output_rgb = hdmi_bus_fmt_is_rgb(hdmi_data->enc_out_bus_क्रमmat);

	वापस (is_input_rgb != is_output_rgb) ||
	       (is_input_rgb && is_output_rgb && hdmi_data->rgb_limited_range);
पूर्ण

अटल पूर्णांक is_color_space_decimation(काष्ठा dw_hdmi *hdmi)
अणु
	अगर (!hdmi_bus_fmt_is_yuv422(hdmi->hdmi_data.enc_out_bus_क्रमmat))
		वापस 0;

	अगर (hdmi_bus_fmt_is_rgb(hdmi->hdmi_data.enc_in_bus_क्रमmat) ||
	    hdmi_bus_fmt_is_yuv444(hdmi->hdmi_data.enc_in_bus_क्रमmat))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक is_color_space_पूर्णांकerpolation(काष्ठा dw_hdmi *hdmi)
अणु
	अगर (!hdmi_bus_fmt_is_yuv422(hdmi->hdmi_data.enc_in_bus_क्रमmat))
		वापस 0;

	अगर (hdmi_bus_fmt_is_rgb(hdmi->hdmi_data.enc_out_bus_क्रमmat) ||
	    hdmi_bus_fmt_is_yuv444(hdmi->hdmi_data.enc_out_bus_क्रमmat))
		वापस 1;

	वापस 0;
पूर्ण

अटल bool is_csc_needed(काष्ठा dw_hdmi *hdmi)
अणु
	वापस is_color_space_conversion(hdmi) ||
	       is_color_space_decimation(hdmi) ||
	       is_color_space_पूर्णांकerpolation(hdmi);
पूर्ण

अटल व्योम dw_hdmi_update_csc_coeffs(काष्ठा dw_hdmi *hdmi)
अणु
	स्थिर u16 (*csc_coeff)[3][4] = &csc_coeff_शेष;
	bool is_input_rgb, is_output_rgb;
	अचिन्हित i;
	u32 csc_scale = 1;

	is_input_rgb = hdmi_bus_fmt_is_rgb(hdmi->hdmi_data.enc_in_bus_क्रमmat);
	is_output_rgb = hdmi_bus_fmt_is_rgb(hdmi->hdmi_data.enc_out_bus_क्रमmat);

	अगर (!is_input_rgb && is_output_rgb) अणु
		अगर (hdmi->hdmi_data.enc_out_encoding == V4L2_YCBCR_ENC_601)
			csc_coeff = &csc_coeff_rgb_out_eitu601;
		अन्यथा
			csc_coeff = &csc_coeff_rgb_out_eitu709;
	पूर्ण अन्यथा अगर (is_input_rgb && !is_output_rgb) अणु
		अगर (hdmi->hdmi_data.enc_out_encoding == V4L2_YCBCR_ENC_601)
			csc_coeff = &csc_coeff_rgb_in_eitu601;
		अन्यथा
			csc_coeff = &csc_coeff_rgb_in_eitu709;
		csc_scale = 0;
	पूर्ण अन्यथा अगर (is_input_rgb && is_output_rgb &&
		   hdmi->hdmi_data.rgb_limited_range) अणु
		csc_coeff = &csc_coeff_rgb_full_to_rgb_limited;
	पूर्ण

	/* The CSC रेजिस्टरs are sequential, alternating MSB then LSB */
	क्रम (i = 0; i < ARRAY_SIZE(csc_coeff_शेष[0]); i++) अणु
		u16 coeff_a = (*csc_coeff)[0][i];
		u16 coeff_b = (*csc_coeff)[1][i];
		u16 coeff_c = (*csc_coeff)[2][i];

		hdmi_ग_लिखोb(hdmi, coeff_a & 0xff, HDMI_CSC_COEF_A1_LSB + i * 2);
		hdmi_ग_लिखोb(hdmi, coeff_a >> 8, HDMI_CSC_COEF_A1_MSB + i * 2);
		hdmi_ग_लिखोb(hdmi, coeff_b & 0xff, HDMI_CSC_COEF_B1_LSB + i * 2);
		hdmi_ग_लिखोb(hdmi, coeff_b >> 8, HDMI_CSC_COEF_B1_MSB + i * 2);
		hdmi_ग_लिखोb(hdmi, coeff_c & 0xff, HDMI_CSC_COEF_C1_LSB + i * 2);
		hdmi_ग_लिखोb(hdmi, coeff_c >> 8, HDMI_CSC_COEF_C1_MSB + i * 2);
	पूर्ण

	hdmi_modb(hdmi, csc_scale, HDMI_CSC_SCALE_CSCSCALE_MASK,
		  HDMI_CSC_SCALE);
पूर्ण

अटल व्योम hdmi_video_csc(काष्ठा dw_hdmi *hdmi)
अणु
	पूर्णांक color_depth = 0;
	पूर्णांक पूर्णांकerpolation = HDMI_CSC_CFG_INTMODE_DISABLE;
	पूर्णांक decimation = 0;

	/* YCC422 पूर्णांकerpolation to 444 mode */
	अगर (is_color_space_पूर्णांकerpolation(hdmi))
		पूर्णांकerpolation = HDMI_CSC_CFG_INTMODE_CHROMA_INT_FORMULA1;
	अन्यथा अगर (is_color_space_decimation(hdmi))
		decimation = HDMI_CSC_CFG_DECMODE_CHROMA_INT_FORMULA3;

	चयन (hdmi_bus_fmt_color_depth(hdmi->hdmi_data.enc_out_bus_क्रमmat)) अणु
	हाल 8:
		color_depth = HDMI_CSC_SCALE_CSC_COLORDE_PTH_24BPP;
		अवरोध;
	हाल 10:
		color_depth = HDMI_CSC_SCALE_CSC_COLORDE_PTH_30BPP;
		अवरोध;
	हाल 12:
		color_depth = HDMI_CSC_SCALE_CSC_COLORDE_PTH_36BPP;
		अवरोध;
	हाल 16:
		color_depth = HDMI_CSC_SCALE_CSC_COLORDE_PTH_48BPP;
		अवरोध;

	शेष:
		वापस;
	पूर्ण

	/* Configure the CSC रेजिस्टरs */
	hdmi_ग_लिखोb(hdmi, पूर्णांकerpolation | decimation, HDMI_CSC_CFG);
	hdmi_modb(hdmi, color_depth, HDMI_CSC_SCALE_CSC_COLORDE_PTH_MASK,
		  HDMI_CSC_SCALE);

	dw_hdmi_update_csc_coeffs(hdmi);
पूर्ण

/*
 * HDMI video packetizer is used to packetize the data.
 * क्रम example, अगर input is YCC422 mode or repeater is used,
 * data should be repacked this module can be bypassed.
 */
अटल व्योम hdmi_video_packetize(काष्ठा dw_hdmi *hdmi)
अणु
	अचिन्हित पूर्णांक color_depth = 0;
	अचिन्हित पूर्णांक remap_size = HDMI_VP_REMAP_YCC422_16bit;
	अचिन्हित पूर्णांक output_select = HDMI_VP_CONF_OUTPUT_SELECTOR_PP;
	काष्ठा hdmi_data_info *hdmi_data = &hdmi->hdmi_data;
	u8 val, vp_conf;

	अगर (hdmi_bus_fmt_is_rgb(hdmi->hdmi_data.enc_out_bus_क्रमmat) ||
	    hdmi_bus_fmt_is_yuv444(hdmi->hdmi_data.enc_out_bus_क्रमmat) ||
	    hdmi_bus_fmt_is_yuv420(hdmi->hdmi_data.enc_out_bus_क्रमmat)) अणु
		चयन (hdmi_bus_fmt_color_depth(
					hdmi->hdmi_data.enc_out_bus_क्रमmat)) अणु
		हाल 8:
			color_depth = 4;
			output_select = HDMI_VP_CONF_OUTPUT_SELECTOR_BYPASS;
			अवरोध;
		हाल 10:
			color_depth = 5;
			अवरोध;
		हाल 12:
			color_depth = 6;
			अवरोध;
		हाल 16:
			color_depth = 7;
			अवरोध;
		शेष:
			output_select = HDMI_VP_CONF_OUTPUT_SELECTOR_BYPASS;
		पूर्ण
	पूर्ण अन्यथा अगर (hdmi_bus_fmt_is_yuv422(hdmi->hdmi_data.enc_out_bus_क्रमmat)) अणु
		चयन (hdmi_bus_fmt_color_depth(
					hdmi->hdmi_data.enc_out_bus_क्रमmat)) अणु
		हाल 0:
		हाल 8:
			remap_size = HDMI_VP_REMAP_YCC422_16bit;
			अवरोध;
		हाल 10:
			remap_size = HDMI_VP_REMAP_YCC422_20bit;
			अवरोध;
		हाल 12:
			remap_size = HDMI_VP_REMAP_YCC422_24bit;
			अवरोध;

		शेष:
			वापस;
		पूर्ण
		output_select = HDMI_VP_CONF_OUTPUT_SELECTOR_YCC422;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	/* set the packetizer रेजिस्टरs */
	val = ((color_depth << HDMI_VP_PR_CD_COLOR_DEPTH_OFFSET) &
		HDMI_VP_PR_CD_COLOR_DEPTH_MASK) |
		((hdmi_data->pix_repet_factor <<
		HDMI_VP_PR_CD_DESIRED_PR_FACTOR_OFFSET) &
		HDMI_VP_PR_CD_DESIRED_PR_FACTOR_MASK);
	hdmi_ग_लिखोb(hdmi, val, HDMI_VP_PR_CD);

	hdmi_modb(hdmi, HDMI_VP_STUFF_PR_STUFFING_STUFFING_MODE,
		  HDMI_VP_STUFF_PR_STUFFING_MASK, HDMI_VP_STUFF);

	/* Data from pixel repeater block */
	अगर (hdmi_data->pix_repet_factor > 1) अणु
		vp_conf = HDMI_VP_CONF_PR_EN_ENABLE |
			  HDMI_VP_CONF_BYPASS_SELECT_PIX_REPEATER;
	पूर्ण अन्यथा अणु /* data from packetizer block */
		vp_conf = HDMI_VP_CONF_PR_EN_DISABLE |
			  HDMI_VP_CONF_BYPASS_SELECT_VID_PACKETIZER;
	पूर्ण

	hdmi_modb(hdmi, vp_conf,
		  HDMI_VP_CONF_PR_EN_MASK |
		  HDMI_VP_CONF_BYPASS_SELECT_MASK, HDMI_VP_CONF);

	hdmi_modb(hdmi, 1 << HDMI_VP_STUFF_IDEFAULT_PHASE_OFFSET,
		  HDMI_VP_STUFF_IDEFAULT_PHASE_MASK, HDMI_VP_STUFF);

	hdmi_ग_लिखोb(hdmi, remap_size, HDMI_VP_REMAP);

	अगर (output_select == HDMI_VP_CONF_OUTPUT_SELECTOR_PP) अणु
		vp_conf = HDMI_VP_CONF_BYPASS_EN_DISABLE |
			  HDMI_VP_CONF_PP_EN_ENABLE |
			  HDMI_VP_CONF_YCC422_EN_DISABLE;
	पूर्ण अन्यथा अगर (output_select == HDMI_VP_CONF_OUTPUT_SELECTOR_YCC422) अणु
		vp_conf = HDMI_VP_CONF_BYPASS_EN_DISABLE |
			  HDMI_VP_CONF_PP_EN_DISABLE |
			  HDMI_VP_CONF_YCC422_EN_ENABLE;
	पूर्ण अन्यथा अगर (output_select == HDMI_VP_CONF_OUTPUT_SELECTOR_BYPASS) अणु
		vp_conf = HDMI_VP_CONF_BYPASS_EN_ENABLE |
			  HDMI_VP_CONF_PP_EN_DISABLE |
			  HDMI_VP_CONF_YCC422_EN_DISABLE;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	hdmi_modb(hdmi, vp_conf,
		  HDMI_VP_CONF_BYPASS_EN_MASK | HDMI_VP_CONF_PP_EN_ENMASK |
		  HDMI_VP_CONF_YCC422_EN_MASK, HDMI_VP_CONF);

	hdmi_modb(hdmi, HDMI_VP_STUFF_PP_STUFFING_STUFFING_MODE |
			HDMI_VP_STUFF_YCC422_STUFFING_STUFFING_MODE,
		  HDMI_VP_STUFF_PP_STUFFING_MASK |
		  HDMI_VP_STUFF_YCC422_STUFFING_MASK, HDMI_VP_STUFF);

	hdmi_modb(hdmi, output_select, HDMI_VP_CONF_OUTPUT_SELECTOR_MASK,
		  HDMI_VP_CONF);
पूर्ण

/* -----------------------------------------------------------------------------
 * Synopsys PHY Handling
 */

अटल अंतरभूत व्योम hdmi_phy_test_clear(काष्ठा dw_hdmi *hdmi,
				       अचिन्हित अक्षर bit)
अणु
	hdmi_modb(hdmi, bit << HDMI_PHY_TST0_TSTCLR_OFFSET,
		  HDMI_PHY_TST0_TSTCLR_MASK, HDMI_PHY_TST0);
पूर्ण

अटल bool hdmi_phy_रुको_i2c_करोne(काष्ठा dw_hdmi *hdmi, पूर्णांक msec)
अणु
	u32 val;

	जबतक ((val = hdmi_पढ़ोb(hdmi, HDMI_IH_I2CMPHY_STAT0) & 0x3) == 0) अणु
		अगर (msec-- == 0)
			वापस false;
		udelay(1000);
	पूर्ण
	hdmi_ग_लिखोb(hdmi, val, HDMI_IH_I2CMPHY_STAT0);

	वापस true;
पूर्ण

व्योम dw_hdmi_phy_i2c_ग_लिखो(काष्ठा dw_hdmi *hdmi, अचिन्हित लघु data,
			   अचिन्हित अक्षर addr)
अणु
	hdmi_ग_लिखोb(hdmi, 0xFF, HDMI_IH_I2CMPHY_STAT0);
	hdmi_ग_लिखोb(hdmi, addr, HDMI_PHY_I2CM_ADDRESS_ADDR);
	hdmi_ग_लिखोb(hdmi, (अचिन्हित अक्षर)(data >> 8),
		    HDMI_PHY_I2CM_DATAO_1_ADDR);
	hdmi_ग_लिखोb(hdmi, (अचिन्हित अक्षर)(data >> 0),
		    HDMI_PHY_I2CM_DATAO_0_ADDR);
	hdmi_ग_लिखोb(hdmi, HDMI_PHY_I2CM_OPERATION_ADDR_WRITE,
		    HDMI_PHY_I2CM_OPERATION_ADDR);
	hdmi_phy_रुको_i2c_करोne(hdmi, 1000);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_phy_i2c_ग_लिखो);

/* Filter out invalid setups to aव्योम configuring SCDC and scrambling */
अटल bool dw_hdmi_support_scdc(काष्ठा dw_hdmi *hdmi,
				 स्थिर काष्ठा drm_display_info *display)
अणु
	/* Completely disable SCDC support क्रम older controllers */
	अगर (hdmi->version < 0x200a)
		वापस false;

	/* Disable अगर no DDC bus */
	अगर (!hdmi->ddc)
		वापस false;

	/* Disable अगर SCDC is not supported, or अगर an HF-VSDB block is असलent */
	अगर (!display->hdmi.scdc.supported ||
	    !display->hdmi.scdc.scrambling.supported)
		वापस false;

	/*
	 * Disable अगर display only support low TMDS rates and scrambling
	 * क्रम low rates is not supported either
	 */
	अगर (!display->hdmi.scdc.scrambling.low_rates &&
	    display->max_पंचांगds_घड़ी <= 340000)
		वापस false;

	वापस true;
पूर्ण

/*
 * HDMI2.0 Specअगरies the following procedure क्रम High TMDS Bit Rates:
 * - The Source shall suspend transmission of the TMDS घड़ी and data
 * - The Source shall ग_लिखो to the TMDS_Bit_Clock_Ratio bit to change it
 * from a 0 to a 1 or from a 1 to a 0
 * - The Source shall allow a minimum of 1 ms and a maximum of 100 ms from
 * the समय the TMDS_Bit_Clock_Ratio bit is written until resuming
 * transmission of TMDS घड़ी and data
 *
 * To respect the 100ms maximum delay, the dw_hdmi_set_high_पंचांगds_घड़ी_ratio()
 * helper should called right beक्रमe enabling the TMDS Clock and Data in
 * the PHY configuration callback.
 */
व्योम dw_hdmi_set_high_पंचांगds_घड़ी_ratio(काष्ठा dw_hdmi *hdmi,
				       स्थिर काष्ठा drm_display_info *display)
अणु
	अचिन्हित दीर्घ mपंचांगdsघड़ी = hdmi->hdmi_data.video_mode.mपंचांगdsघड़ी;

	/* Control क्रम TMDS Bit Period/TMDS Clock-Period Ratio */
	अगर (dw_hdmi_support_scdc(hdmi, display)) अणु
		अगर (mपंचांगdsघड़ी > HDMI14_MAX_TMDSCLK)
			drm_scdc_set_high_पंचांगds_घड़ी_ratio(hdmi->ddc, 1);
		अन्यथा
			drm_scdc_set_high_पंचांगds_घड़ी_ratio(hdmi->ddc, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_set_high_पंचांगds_घड़ी_ratio);

अटल व्योम dw_hdmi_phy_enable_घातerकरोwn(काष्ठा dw_hdmi *hdmi, bool enable)
अणु
	hdmi_mask_ग_लिखोb(hdmi, !enable, HDMI_PHY_CONF0,
			 HDMI_PHY_CONF0_PDZ_OFFSET,
			 HDMI_PHY_CONF0_PDZ_MASK);
पूर्ण

अटल व्योम dw_hdmi_phy_enable_पंचांगds(काष्ठा dw_hdmi *hdmi, u8 enable)
अणु
	hdmi_mask_ग_लिखोb(hdmi, enable, HDMI_PHY_CONF0,
			 HDMI_PHY_CONF0_ENTMDS_OFFSET,
			 HDMI_PHY_CONF0_ENTMDS_MASK);
पूर्ण

अटल व्योम dw_hdmi_phy_enable_svsret(काष्ठा dw_hdmi *hdmi, u8 enable)
अणु
	hdmi_mask_ग_लिखोb(hdmi, enable, HDMI_PHY_CONF0,
			 HDMI_PHY_CONF0_SVSRET_OFFSET,
			 HDMI_PHY_CONF0_SVSRET_MASK);
पूर्ण

व्योम dw_hdmi_phy_gen2_pddq(काष्ठा dw_hdmi *hdmi, u8 enable)
अणु
	hdmi_mask_ग_लिखोb(hdmi, enable, HDMI_PHY_CONF0,
			 HDMI_PHY_CONF0_GEN2_PDDQ_OFFSET,
			 HDMI_PHY_CONF0_GEN2_PDDQ_MASK);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_phy_gen2_pddq);

व्योम dw_hdmi_phy_gen2_txpwron(काष्ठा dw_hdmi *hdmi, u8 enable)
अणु
	hdmi_mask_ग_लिखोb(hdmi, enable, HDMI_PHY_CONF0,
			 HDMI_PHY_CONF0_GEN2_TXPWRON_OFFSET,
			 HDMI_PHY_CONF0_GEN2_TXPWRON_MASK);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_phy_gen2_txpwron);

अटल व्योम dw_hdmi_phy_sel_data_en_pol(काष्ठा dw_hdmi *hdmi, u8 enable)
अणु
	hdmi_mask_ग_लिखोb(hdmi, enable, HDMI_PHY_CONF0,
			 HDMI_PHY_CONF0_SELDATAENPOL_OFFSET,
			 HDMI_PHY_CONF0_SELDATAENPOL_MASK);
पूर्ण

अटल व्योम dw_hdmi_phy_sel_पूर्णांकerface_control(काष्ठा dw_hdmi *hdmi, u8 enable)
अणु
	hdmi_mask_ग_लिखोb(hdmi, enable, HDMI_PHY_CONF0,
			 HDMI_PHY_CONF0_SELDIPIF_OFFSET,
			 HDMI_PHY_CONF0_SELDIPIF_MASK);
पूर्ण

व्योम dw_hdmi_phy_reset(काष्ठा dw_hdmi *hdmi)
अणु
	/* PHY reset. The reset संकेत is active high on Gen2 PHYs. */
	hdmi_ग_लिखोb(hdmi, HDMI_MC_PHYRSTZ_PHYRSTZ, HDMI_MC_PHYRSTZ);
	hdmi_ग_लिखोb(hdmi, 0, HDMI_MC_PHYRSTZ);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_phy_reset);

व्योम dw_hdmi_phy_i2c_set_addr(काष्ठा dw_hdmi *hdmi, u8 address)
अणु
	hdmi_phy_test_clear(hdmi, 1);
	hdmi_ग_लिखोb(hdmi, address, HDMI_PHY_I2CM_SLAVE_ADDR);
	hdmi_phy_test_clear(hdmi, 0);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_phy_i2c_set_addr);

अटल व्योम dw_hdmi_phy_घातer_off(काष्ठा dw_hdmi *hdmi)
अणु
	स्थिर काष्ठा dw_hdmi_phy_data *phy = hdmi->phy.data;
	अचिन्हित पूर्णांक i;
	u16 val;

	अगर (phy->gen == 1) अणु
		dw_hdmi_phy_enable_पंचांगds(hdmi, 0);
		dw_hdmi_phy_enable_घातerकरोwn(hdmi, true);
		वापस;
	पूर्ण

	dw_hdmi_phy_gen2_txpwron(hdmi, 0);

	/*
	 * Wait क्रम TX_PHY_LOCK to be deनिश्चितed to indicate that the PHY went
	 * to low घातer mode.
	 */
	क्रम (i = 0; i < 5; ++i) अणु
		val = hdmi_पढ़ोb(hdmi, HDMI_PHY_STAT0);
		अगर (!(val & HDMI_PHY_TX_PHY_LOCK))
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण

	अगर (val & HDMI_PHY_TX_PHY_LOCK)
		dev_warn(hdmi->dev, "PHY failed to power down\n");
	अन्यथा
		dev_dbg(hdmi->dev, "PHY powered down in %u iterations\n", i);

	dw_hdmi_phy_gen2_pddq(hdmi, 1);
पूर्ण

अटल पूर्णांक dw_hdmi_phy_घातer_on(काष्ठा dw_hdmi *hdmi)
अणु
	स्थिर काष्ठा dw_hdmi_phy_data *phy = hdmi->phy.data;
	अचिन्हित पूर्णांक i;
	u8 val;

	अगर (phy->gen == 1) अणु
		dw_hdmi_phy_enable_घातerकरोwn(hdmi, false);

		/* Toggle TMDS enable. */
		dw_hdmi_phy_enable_पंचांगds(hdmi, 0);
		dw_hdmi_phy_enable_पंचांगds(hdmi, 1);
		वापस 0;
	पूर्ण

	dw_hdmi_phy_gen2_txpwron(hdmi, 1);
	dw_hdmi_phy_gen2_pddq(hdmi, 0);

	/* Wait क्रम PHY PLL lock */
	क्रम (i = 0; i < 5; ++i) अणु
		val = hdmi_पढ़ोb(hdmi, HDMI_PHY_STAT0) & HDMI_PHY_TX_PHY_LOCK;
		अगर (val)
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण

	अगर (!val) अणु
		dev_err(hdmi->dev, "PHY PLL failed to lock\n");
		वापस -ETIMEDOUT;
	पूर्ण

	dev_dbg(hdmi->dev, "PHY PLL locked %u iterations\n", i);
	वापस 0;
पूर्ण

/*
 * PHY configuration function क्रम the DWC HDMI 3D TX PHY. Based on the available
 * inक्रमmation the DWC MHL PHY has the same रेजिस्टर layout and is thus also
 * supported by this function.
 */
अटल पूर्णांक hdmi_phy_configure_dwc_hdmi_3d_tx(काष्ठा dw_hdmi *hdmi,
		स्थिर काष्ठा dw_hdmi_plat_data *pdata,
		अचिन्हित दीर्घ mpixelघड़ी)
अणु
	स्थिर काष्ठा dw_hdmi_mpll_config *mpll_config = pdata->mpll_cfg;
	स्थिर काष्ठा dw_hdmi_curr_ctrl *curr_ctrl = pdata->cur_ctr;
	स्थिर काष्ठा dw_hdmi_phy_config *phy_config = pdata->phy_config;

	/* TOFIX Will need 420 specअगरic PHY configuration tables */

	/* PLL/MPLL Cfg - always match on final entry */
	क्रम (; mpll_config->mpixelघड़ी != ~0UL; mpll_config++)
		अगर (mpixelघड़ी <= mpll_config->mpixelघड़ी)
			अवरोध;

	क्रम (; curr_ctrl->mpixelघड़ी != ~0UL; curr_ctrl++)
		अगर (mpixelघड़ी <= curr_ctrl->mpixelघड़ी)
			अवरोध;

	क्रम (; phy_config->mpixelघड़ी != ~0UL; phy_config++)
		अगर (mpixelघड़ी <= phy_config->mpixelघड़ी)
			अवरोध;

	अगर (mpll_config->mpixelघड़ी == ~0UL ||
	    curr_ctrl->mpixelघड़ी == ~0UL ||
	    phy_config->mpixelघड़ी == ~0UL)
		वापस -EINVAL;

	dw_hdmi_phy_i2c_ग_लिखो(hdmi, mpll_config->res[0].cpce,
			      HDMI_3D_TX_PHY_CPCE_CTRL);
	dw_hdmi_phy_i2c_ग_लिखो(hdmi, mpll_config->res[0].gmp,
			      HDMI_3D_TX_PHY_GMPCTRL);
	dw_hdmi_phy_i2c_ग_लिखो(hdmi, curr_ctrl->curr[0],
			      HDMI_3D_TX_PHY_CURRCTRL);

	dw_hdmi_phy_i2c_ग_लिखो(hdmi, 0, HDMI_3D_TX_PHY_PLLPHBYCTRL);
	dw_hdmi_phy_i2c_ग_लिखो(hdmi, HDMI_3D_TX_PHY_MSM_CTRL_CKO_SEL_FB_CLK,
			      HDMI_3D_TX_PHY_MSM_CTRL);

	dw_hdmi_phy_i2c_ग_लिखो(hdmi, phy_config->term, HDMI_3D_TX_PHY_TXTERM);
	dw_hdmi_phy_i2c_ग_लिखो(hdmi, phy_config->sym_ctr,
			      HDMI_3D_TX_PHY_CKSYMTXCTRL);
	dw_hdmi_phy_i2c_ग_लिखो(hdmi, phy_config->vlev_ctr,
			      HDMI_3D_TX_PHY_VLEVCTRL);

	/* Override and disable घड़ी termination. */
	dw_hdmi_phy_i2c_ग_लिखो(hdmi, HDMI_3D_TX_PHY_CKCALCTRL_OVERRIDE,
			      HDMI_3D_TX_PHY_CKCALCTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक hdmi_phy_configure(काष्ठा dw_hdmi *hdmi,
			      स्थिर काष्ठा drm_display_info *display)
अणु
	स्थिर काष्ठा dw_hdmi_phy_data *phy = hdmi->phy.data;
	स्थिर काष्ठा dw_hdmi_plat_data *pdata = hdmi->plat_data;
	अचिन्हित दीर्घ mpixelघड़ी = hdmi->hdmi_data.video_mode.mpixelघड़ी;
	अचिन्हित दीर्घ mपंचांगdsघड़ी = hdmi->hdmi_data.video_mode.mपंचांगdsघड़ी;
	पूर्णांक ret;

	dw_hdmi_phy_घातer_off(hdmi);

	dw_hdmi_set_high_पंचांगds_घड़ी_ratio(hdmi, display);

	/* Leave low घातer consumption mode by निश्चितing SVSRET. */
	अगर (phy->has_svsret)
		dw_hdmi_phy_enable_svsret(hdmi, 1);

	dw_hdmi_phy_reset(hdmi);

	hdmi_ग_लिखोb(hdmi, HDMI_MC_HEACPHY_RST_ASSERT, HDMI_MC_HEACPHY_RST);

	dw_hdmi_phy_i2c_set_addr(hdmi, HDMI_PHY_I2CM_SLAVE_ADDR_PHY_GEN2);

	/* Write to the PHY as configured by the platक्रमm */
	अगर (pdata->configure_phy)
		ret = pdata->configure_phy(hdmi, pdata->priv_data, mpixelघड़ी);
	अन्यथा
		ret = phy->configure(hdmi, pdata, mpixelघड़ी);
	अगर (ret) अणु
		dev_err(hdmi->dev, "PHY configuration failed (clock %lu)\n",
			mpixelघड़ी);
		वापस ret;
	पूर्ण

	/* Wait क्रम resuming transmission of TMDS घड़ी and data */
	अगर (mपंचांगdsघड़ी > HDMI14_MAX_TMDSCLK)
		msleep(100);

	वापस dw_hdmi_phy_घातer_on(hdmi);
पूर्ण

अटल पूर्णांक dw_hdmi_phy_init(काष्ठा dw_hdmi *hdmi, व्योम *data,
			    स्थिर काष्ठा drm_display_info *display,
			    स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक i, ret;

	/* HDMI Phy spec says to करो the phy initialization sequence twice */
	क्रम (i = 0; i < 2; i++) अणु
		dw_hdmi_phy_sel_data_en_pol(hdmi, 1);
		dw_hdmi_phy_sel_पूर्णांकerface_control(hdmi, 0);

		ret = hdmi_phy_configure(hdmi, display);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw_hdmi_phy_disable(काष्ठा dw_hdmi *hdmi, व्योम *data)
अणु
	dw_hdmi_phy_घातer_off(hdmi);
पूर्ण

क्रमागत drm_connector_status dw_hdmi_phy_पढ़ो_hpd(काष्ठा dw_hdmi *hdmi,
					       व्योम *data)
अणु
	वापस hdmi_पढ़ोb(hdmi, HDMI_PHY_STAT0) & HDMI_PHY_HPD ?
		connector_status_connected : connector_status_disconnected;
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_phy_पढ़ो_hpd);

व्योम dw_hdmi_phy_update_hpd(काष्ठा dw_hdmi *hdmi, व्योम *data,
			    bool क्रमce, bool disabled, bool rxsense)
अणु
	u8 old_mask = hdmi->phy_mask;

	अगर (क्रमce || disabled || !rxsense)
		hdmi->phy_mask |= HDMI_PHY_RX_SENSE;
	अन्यथा
		hdmi->phy_mask &= ~HDMI_PHY_RX_SENSE;

	अगर (old_mask != hdmi->phy_mask)
		hdmi_ग_लिखोb(hdmi, hdmi->phy_mask, HDMI_PHY_MASK0);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_phy_update_hpd);

व्योम dw_hdmi_phy_setup_hpd(काष्ठा dw_hdmi *hdmi, व्योम *data)
अणु
	/*
	 * Configure the PHY RX SENSE and HPD पूर्णांकerrupts polarities and clear
	 * any pending पूर्णांकerrupt.
	 */
	hdmi_ग_लिखोb(hdmi, HDMI_PHY_HPD | HDMI_PHY_RX_SENSE, HDMI_PHY_POL0);
	hdmi_ग_लिखोb(hdmi, HDMI_IH_PHY_STAT0_HPD | HDMI_IH_PHY_STAT0_RX_SENSE,
		    HDMI_IH_PHY_STAT0);

	/* Enable cable hot plug irq. */
	hdmi_ग_लिखोb(hdmi, hdmi->phy_mask, HDMI_PHY_MASK0);

	/* Clear and unmute पूर्णांकerrupts. */
	hdmi_ग_लिखोb(hdmi, HDMI_IH_PHY_STAT0_HPD | HDMI_IH_PHY_STAT0_RX_SENSE,
		    HDMI_IH_PHY_STAT0);
	hdmi_ग_लिखोb(hdmi, ~(HDMI_IH_PHY_STAT0_HPD | HDMI_IH_PHY_STAT0_RX_SENSE),
		    HDMI_IH_MUTE_PHY_STAT0);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_phy_setup_hpd);

अटल स्थिर काष्ठा dw_hdmi_phy_ops dw_hdmi_synopsys_phy_ops = अणु
	.init = dw_hdmi_phy_init,
	.disable = dw_hdmi_phy_disable,
	.पढ़ो_hpd = dw_hdmi_phy_पढ़ो_hpd,
	.update_hpd = dw_hdmi_phy_update_hpd,
	.setup_hpd = dw_hdmi_phy_setup_hpd,
पूर्ण;

/* -----------------------------------------------------------------------------
 * HDMI TX Setup
 */

अटल व्योम hdmi_tx_hdcp_config(काष्ठा dw_hdmi *hdmi)
अणु
	u8 de;

	अगर (hdmi->hdmi_data.video_mode.mdataenablepolarity)
		de = HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_HIGH;
	अन्यथा
		de = HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_LOW;

	/* disable rx detect */
	hdmi_modb(hdmi, HDMI_A_HDCPCFG0_RXDETECT_DISABLE,
		  HDMI_A_HDCPCFG0_RXDETECT_MASK, HDMI_A_HDCPCFG0);

	hdmi_modb(hdmi, de, HDMI_A_VIDPOLCFG_DATAENPOL_MASK, HDMI_A_VIDPOLCFG);

	hdmi_modb(hdmi, HDMI_A_HDCPCFG1_ENCRYPTIONDISABLE_DISABLE,
		  HDMI_A_HDCPCFG1_ENCRYPTIONDISABLE_MASK, HDMI_A_HDCPCFG1);
पूर्ण

अटल व्योम hdmi_config_AVI(काष्ठा dw_hdmi *hdmi,
			    स्थिर काष्ठा drm_connector *connector,
			    स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा hdmi_avi_infoframe frame;
	u8 val;

	/* Initialise info frame from DRM mode */
	drm_hdmi_avi_infoframe_from_display_mode(&frame, connector, mode);

	अगर (hdmi_bus_fmt_is_rgb(hdmi->hdmi_data.enc_out_bus_क्रमmat)) अणु
		drm_hdmi_avi_infoframe_quant_range(&frame, connector, mode,
						   hdmi->hdmi_data.rgb_limited_range ?
						   HDMI_QUANTIZATION_RANGE_LIMITED :
						   HDMI_QUANTIZATION_RANGE_FULL);
	पूर्ण अन्यथा अणु
		frame.quantization_range = HDMI_QUANTIZATION_RANGE_DEFAULT;
		frame.ycc_quantization_range =
			HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
	पूर्ण

	अगर (hdmi_bus_fmt_is_yuv444(hdmi->hdmi_data.enc_out_bus_क्रमmat))
		frame.colorspace = HDMI_COLORSPACE_YUV444;
	अन्यथा अगर (hdmi_bus_fmt_is_yuv422(hdmi->hdmi_data.enc_out_bus_क्रमmat))
		frame.colorspace = HDMI_COLORSPACE_YUV422;
	अन्यथा अगर (hdmi_bus_fmt_is_yuv420(hdmi->hdmi_data.enc_out_bus_क्रमmat))
		frame.colorspace = HDMI_COLORSPACE_YUV420;
	अन्यथा
		frame.colorspace = HDMI_COLORSPACE_RGB;

	/* Set up colorimetry */
	अगर (!hdmi_bus_fmt_is_rgb(hdmi->hdmi_data.enc_out_bus_क्रमmat)) अणु
		चयन (hdmi->hdmi_data.enc_out_encoding) अणु
		हाल V4L2_YCBCR_ENC_601:
			अगर (hdmi->hdmi_data.enc_in_encoding == V4L2_YCBCR_ENC_XV601)
				frame.colorimetry = HDMI_COLORIMETRY_EXTENDED;
			अन्यथा
				frame.colorimetry = HDMI_COLORIMETRY_ITU_601;
			frame.extended_colorimetry =
					HDMI_EXTENDED_COLORIMETRY_XV_YCC_601;
			अवरोध;
		हाल V4L2_YCBCR_ENC_709:
			अगर (hdmi->hdmi_data.enc_in_encoding == V4L2_YCBCR_ENC_XV709)
				frame.colorimetry = HDMI_COLORIMETRY_EXTENDED;
			अन्यथा
				frame.colorimetry = HDMI_COLORIMETRY_ITU_709;
			frame.extended_colorimetry =
					HDMI_EXTENDED_COLORIMETRY_XV_YCC_709;
			अवरोध;
		शेष: /* Carries no data */
			frame.colorimetry = HDMI_COLORIMETRY_ITU_601;
			frame.extended_colorimetry =
					HDMI_EXTENDED_COLORIMETRY_XV_YCC_601;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		frame.colorimetry = HDMI_COLORIMETRY_NONE;
		frame.extended_colorimetry =
			HDMI_EXTENDED_COLORIMETRY_XV_YCC_601;
	पूर्ण

	/*
	 * The Designware IP uses a dअगरferent byte क्रमmat from standard
	 * AVI info frames, though generally the bits are in the correct
	 * bytes.
	 */

	/*
	 * AVI data byte 1 dअगरferences: Colorspace in bits 0,1 rather than 5,6,
	 * scan info in bits 4,5 rather than 0,1 and active aspect present in
	 * bit 6 rather than 4.
	 */
	val = (frame.scan_mode & 3) << 4 | (frame.colorspace & 3);
	अगर (frame.active_aspect & 15)
		val |= HDMI_FC_AVICONF0_ACTIVE_FMT_INFO_PRESENT;
	अगर (frame.top_bar || frame.bottom_bar)
		val |= HDMI_FC_AVICONF0_BAR_DATA_HORIZ_BAR;
	अगर (frame.left_bar || frame.right_bar)
		val |= HDMI_FC_AVICONF0_BAR_DATA_VERT_BAR;
	hdmi_ग_लिखोb(hdmi, val, HDMI_FC_AVICONF0);

	/* AVI data byte 2 dअगरferences: none */
	val = ((frame.colorimetry & 0x3) << 6) |
	      ((frame.picture_aspect & 0x3) << 4) |
	      (frame.active_aspect & 0xf);
	hdmi_ग_लिखोb(hdmi, val, HDMI_FC_AVICONF1);

	/* AVI data byte 3 dअगरferences: none */
	val = ((frame.extended_colorimetry & 0x7) << 4) |
	      ((frame.quantization_range & 0x3) << 2) |
	      (frame.nups & 0x3);
	अगर (frame.itc)
		val |= HDMI_FC_AVICONF2_IT_CONTENT_VALID;
	hdmi_ग_लिखोb(hdmi, val, HDMI_FC_AVICONF2);

	/* AVI data byte 4 dअगरferences: none */
	val = frame.video_code & 0x7f;
	hdmi_ग_लिखोb(hdmi, val, HDMI_FC_AVIVID);

	/* AVI Data Byte 5- set up input and output pixel repetition */
	val = (((hdmi->hdmi_data.video_mode.mpixelrepetitioninput + 1) <<
		HDMI_FC_PRCONF_INCOMING_PR_FACTOR_OFFSET) &
		HDMI_FC_PRCONF_INCOMING_PR_FACTOR_MASK) |
		((hdmi->hdmi_data.video_mode.mpixelrepetitionoutput <<
		HDMI_FC_PRCONF_OUTPUT_PR_FACTOR_OFFSET) &
		HDMI_FC_PRCONF_OUTPUT_PR_FACTOR_MASK);
	hdmi_ग_लिखोb(hdmi, val, HDMI_FC_PRCONF);

	/*
	 * AVI data byte 5 dअगरferences: content type in 0,1 rather than 4,5,
	 * ycc range in bits 2,3 rather than 6,7
	 */
	val = ((frame.ycc_quantization_range & 0x3) << 2) |
	      (frame.content_type & 0x3);
	hdmi_ग_लिखोb(hdmi, val, HDMI_FC_AVICONF3);

	/* AVI Data Bytes 6-13 */
	hdmi_ग_लिखोb(hdmi, frame.top_bar & 0xff, HDMI_FC_AVIETB0);
	hdmi_ग_लिखोb(hdmi, (frame.top_bar >> 8) & 0xff, HDMI_FC_AVIETB1);
	hdmi_ग_लिखोb(hdmi, frame.bottom_bar & 0xff, HDMI_FC_AVISBB0);
	hdmi_ग_लिखोb(hdmi, (frame.bottom_bar >> 8) & 0xff, HDMI_FC_AVISBB1);
	hdmi_ग_लिखोb(hdmi, frame.left_bar & 0xff, HDMI_FC_AVIELB0);
	hdmi_ग_लिखोb(hdmi, (frame.left_bar >> 8) & 0xff, HDMI_FC_AVIELB1);
	hdmi_ग_लिखोb(hdmi, frame.right_bar & 0xff, HDMI_FC_AVISRB0);
	hdmi_ग_लिखोb(hdmi, (frame.right_bar >> 8) & 0xff, HDMI_FC_AVISRB1);
पूर्ण

अटल व्योम hdmi_config_venकरोr_specअगरic_infoframe(काष्ठा dw_hdmi *hdmi,
						  स्थिर काष्ठा drm_connector *connector,
						  स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा hdmi_venकरोr_infoframe frame;
	u8 buffer[10];
	sमाप_प्रकार err;

	err = drm_hdmi_venकरोr_infoframe_from_display_mode(&frame, connector,
							  mode);
	अगर (err < 0)
		/*
		 * Going पूर्णांकo that statement करोes not means venकरोr infoframe
		 * fails. It just inक्रमmed us that venकरोr infoframe is not
		 * needed क्रम the selected mode. Only 4k or stereoscopic 3D
		 * mode requires venकरोr infoframe. So just simply वापस.
		 */
		वापस;

	err = hdmi_venकरोr_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "Failed to pack vendor infoframe: %zd\n",
			err);
		वापस;
	पूर्ण
	hdmi_mask_ग_लिखोb(hdmi, 0, HDMI_FC_DATAUTO0, HDMI_FC_DATAUTO0_VSD_OFFSET,
			HDMI_FC_DATAUTO0_VSD_MASK);

	/* Set the length of HDMI venकरोr specअगरic InfoFrame payload */
	hdmi_ग_लिखोb(hdmi, buffer[2], HDMI_FC_VSDSIZE);

	/* Set 24bit IEEE Registration Identअगरier */
	hdmi_ग_लिखोb(hdmi, buffer[4], HDMI_FC_VSDIEEEID0);
	hdmi_ग_लिखोb(hdmi, buffer[5], HDMI_FC_VSDIEEEID1);
	hdmi_ग_लिखोb(hdmi, buffer[6], HDMI_FC_VSDIEEEID2);

	/* Set HDMI_Video_Format and HDMI_VIC/3D_Structure */
	hdmi_ग_लिखोb(hdmi, buffer[7], HDMI_FC_VSDPAYLOAD0);
	hdmi_ग_लिखोb(hdmi, buffer[8], HDMI_FC_VSDPAYLOAD1);

	अगर (frame.s3d_काष्ठा >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF)
		hdmi_ग_लिखोb(hdmi, buffer[9], HDMI_FC_VSDPAYLOAD2);

	/* Packet frame पूर्णांकerpolation */
	hdmi_ग_लिखोb(hdmi, 1, HDMI_FC_DATAUTO1);

	/* Auto packets per frame and line spacing */
	hdmi_ग_लिखोb(hdmi, 0x11, HDMI_FC_DATAUTO2);

	/* Configures the Frame Composer On RDRB mode */
	hdmi_mask_ग_लिखोb(hdmi, 1, HDMI_FC_DATAUTO0, HDMI_FC_DATAUTO0_VSD_OFFSET,
			HDMI_FC_DATAUTO0_VSD_MASK);
पूर्ण

अटल व्योम hdmi_config_drm_infoframe(काष्ठा dw_hdmi *hdmi,
				      स्थिर काष्ठा drm_connector *connector)
अणु
	स्थिर काष्ठा drm_connector_state *conn_state = connector->state;
	काष्ठा hdmi_drm_infoframe frame;
	u8 buffer[30];
	sमाप_प्रकार err;
	पूर्णांक i;

	अगर (!hdmi->plat_data->use_drm_infoframe)
		वापस;

	hdmi_modb(hdmi, HDMI_FC_PACKET_TX_EN_DRM_DISABLE,
		  HDMI_FC_PACKET_TX_EN_DRM_MASK, HDMI_FC_PACKET_TX_EN);

	err = drm_hdmi_infoframe_set_hdr_metadata(&frame, conn_state);
	अगर (err < 0)
		वापस;

	err = hdmi_drm_infoframe_pack(&frame, buffer, माप(buffer));
	अगर (err < 0) अणु
		dev_err(hdmi->dev, "Failed to pack drm infoframe: %zd\n", err);
		वापस;
	पूर्ण

	hdmi_ग_लिखोb(hdmi, frame.version, HDMI_FC_DRM_HB0);
	hdmi_ग_लिखोb(hdmi, frame.length, HDMI_FC_DRM_HB1);

	क्रम (i = 0; i < frame.length; i++)
		hdmi_ग_लिखोb(hdmi, buffer[4 + i], HDMI_FC_DRM_PB0 + i);

	hdmi_ग_लिखोb(hdmi, 1, HDMI_FC_DRM_UP);
	hdmi_modb(hdmi, HDMI_FC_PACKET_TX_EN_DRM_ENABLE,
		  HDMI_FC_PACKET_TX_EN_DRM_MASK, HDMI_FC_PACKET_TX_EN);
पूर्ण

अटल व्योम hdmi_av_composer(काष्ठा dw_hdmi *hdmi,
			     स्थिर काष्ठा drm_display_info *display,
			     स्थिर काष्ठा drm_display_mode *mode)
अणु
	u8 inv_val, bytes;
	स्थिर काष्ठा drm_hdmi_info *hdmi_info = &display->hdmi;
	काष्ठा hdmi_vmode *vmode = &hdmi->hdmi_data.video_mode;
	पूर्णांक hblank, vblank, h_de_hs, v_de_vs, hsync_len, vsync_len;
	अचिन्हित पूर्णांक vdisplay, hdisplay;

	vmode->mpixelघड़ी = mode->घड़ी * 1000;

	dev_dbg(hdmi->dev, "final pixclk = %d\n", vmode->mpixelघड़ी);

	vmode->mपंचांगdsघड़ी = vmode->mpixelघड़ी;

	अगर (!hdmi_bus_fmt_is_yuv422(hdmi->hdmi_data.enc_out_bus_क्रमmat)) अणु
		चयन (hdmi_bus_fmt_color_depth(
				hdmi->hdmi_data.enc_out_bus_क्रमmat)) अणु
		हाल 16:
			vmode->mपंचांगdsघड़ी = vmode->mpixelघड़ी * 2;
			अवरोध;
		हाल 12:
			vmode->mपंचांगdsघड़ी = vmode->mpixelघड़ी * 3 / 2;
			अवरोध;
		हाल 10:
			vmode->mपंचांगdsघड़ी = vmode->mpixelघड़ी * 5 / 4;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (hdmi_bus_fmt_is_yuv420(hdmi->hdmi_data.enc_out_bus_क्रमmat))
		vmode->mपंचांगdsघड़ी /= 2;

	dev_dbg(hdmi->dev, "final tmdsclock = %d\n", vmode->mपंचांगdsघड़ी);

	/* Set up HDMI_FC_INVIDCONF */
	inv_val = (hdmi->hdmi_data.hdcp_enable ||
		   (dw_hdmi_support_scdc(hdmi, display) &&
		    (vmode->mपंचांगdsघड़ी > HDMI14_MAX_TMDSCLK ||
		     hdmi_info->scdc.scrambling.low_rates)) ?
		HDMI_FC_INVIDCONF_HDCP_KEEPOUT_ACTIVE :
		HDMI_FC_INVIDCONF_HDCP_KEEPOUT_INACTIVE);

	inv_val |= mode->flags & DRM_MODE_FLAG_PVSYNC ?
		HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_HIGH :
		HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_LOW;

	inv_val |= mode->flags & DRM_MODE_FLAG_PHSYNC ?
		HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_HIGH :
		HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_LOW;

	inv_val |= (vmode->mdataenablepolarity ?
		HDMI_FC_INVIDCONF_DE_IN_POLARITY_ACTIVE_HIGH :
		HDMI_FC_INVIDCONF_DE_IN_POLARITY_ACTIVE_LOW);

	अगर (hdmi->vic == 39)
		inv_val |= HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_HIGH;
	अन्यथा
		inv_val |= mode->flags & DRM_MODE_FLAG_INTERLACE ?
			HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_HIGH :
			HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_LOW;

	inv_val |= mode->flags & DRM_MODE_FLAG_INTERLACE ?
		HDMI_FC_INVIDCONF_IN_I_P_INTERLACED :
		HDMI_FC_INVIDCONF_IN_I_P_PROGRESSIVE;

	inv_val |= hdmi->sink_is_hdmi ?
		HDMI_FC_INVIDCONF_DVI_MODEZ_HDMI_MODE :
		HDMI_FC_INVIDCONF_DVI_MODEZ_DVI_MODE;

	hdmi_ग_लिखोb(hdmi, inv_val, HDMI_FC_INVIDCONF);

	hdisplay = mode->hdisplay;
	hblank = mode->htotal - mode->hdisplay;
	h_de_hs = mode->hsync_start - mode->hdisplay;
	hsync_len = mode->hsync_end - mode->hsync_start;

	/*
	 * When we're setting a YCbCr420 mode, we need
	 * to adjust the horizontal timing to suit.
	 */
	अगर (hdmi_bus_fmt_is_yuv420(hdmi->hdmi_data.enc_out_bus_क्रमmat)) अणु
		hdisplay /= 2;
		hblank /= 2;
		h_de_hs /= 2;
		hsync_len /= 2;
	पूर्ण

	vdisplay = mode->vdisplay;
	vblank = mode->vtotal - mode->vdisplay;
	v_de_vs = mode->vsync_start - mode->vdisplay;
	vsync_len = mode->vsync_end - mode->vsync_start;

	/*
	 * When we're setting an पूर्णांकerlaced mode, we need
	 * to adjust the vertical timing to suit.
	 */
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		vdisplay /= 2;
		vblank /= 2;
		v_de_vs /= 2;
		vsync_len /= 2;
	पूर्ण

	/* Scrambling Control */
	अगर (dw_hdmi_support_scdc(hdmi, display)) अणु
		अगर (vmode->mपंचांगdsघड़ी > HDMI14_MAX_TMDSCLK ||
		    hdmi_info->scdc.scrambling.low_rates) अणु
			/*
			 * HDMI2.0 Specअगरies the following procedure:
			 * After the Source Device has determined that
			 * SCDC_Present is set (=1), the Source Device should
			 * ग_लिखो the accurate Version of the Source Device
			 * to the Source Version field in the SCDCS.
			 * Source Devices compliant shall set the
			 * Source Version = 1.
			 */
			drm_scdc_पढ़ोb(hdmi->ddc, SCDC_SINK_VERSION,
				       &bytes);
			drm_scdc_ग_लिखोb(hdmi->ddc, SCDC_SOURCE_VERSION,
				min_t(u8, bytes, SCDC_MIN_SOURCE_VERSION));

			/* Enabled Scrambling in the Sink */
			drm_scdc_set_scrambling(hdmi->ddc, 1);

			/*
			 * To activate the scrambler feature, you must ensure
			 * that the quasi-अटल configuration bit
			 * fc_invidconf.HDCP_keepout is set at configuration
			 * समय, beक्रमe the required mc_swrstzreq.पंचांगdsswrst_req
			 * reset request is issued.
			 */
			hdmi_ग_लिखोb(hdmi, (u8)~HDMI_MC_SWRSTZ_TMDSSWRST_REQ,
				    HDMI_MC_SWRSTZ);
			hdmi_ग_लिखोb(hdmi, 1, HDMI_FC_SCRAMBLER_CTRL);
		पूर्ण अन्यथा अणु
			hdmi_ग_लिखोb(hdmi, 0, HDMI_FC_SCRAMBLER_CTRL);
			hdmi_ग_लिखोb(hdmi, (u8)~HDMI_MC_SWRSTZ_TMDSSWRST_REQ,
				    HDMI_MC_SWRSTZ);
			drm_scdc_set_scrambling(hdmi->ddc, 0);
		पूर्ण
	पूर्ण

	/* Set up horizontal active pixel width */
	hdmi_ग_लिखोb(hdmi, hdisplay >> 8, HDMI_FC_INHACTV1);
	hdmi_ग_लिखोb(hdmi, hdisplay, HDMI_FC_INHACTV0);

	/* Set up vertical active lines */
	hdmi_ग_लिखोb(hdmi, vdisplay >> 8, HDMI_FC_INVACTV1);
	hdmi_ग_लिखोb(hdmi, vdisplay, HDMI_FC_INVACTV0);

	/* Set up horizontal blanking pixel region width */
	hdmi_ग_लिखोb(hdmi, hblank >> 8, HDMI_FC_INHBLANK1);
	hdmi_ग_लिखोb(hdmi, hblank, HDMI_FC_INHBLANK0);

	/* Set up vertical blanking pixel region width */
	hdmi_ग_लिखोb(hdmi, vblank, HDMI_FC_INVBLANK);

	/* Set up HSYNC active edge delay width (in pixel clks) */
	hdmi_ग_लिखोb(hdmi, h_de_hs >> 8, HDMI_FC_HSYNCINDELAY1);
	hdmi_ग_लिखोb(hdmi, h_de_hs, HDMI_FC_HSYNCINDELAY0);

	/* Set up VSYNC active edge delay (in lines) */
	hdmi_ग_लिखोb(hdmi, v_de_vs, HDMI_FC_VSYNCINDELAY);

	/* Set up HSYNC active pulse width (in pixel clks) */
	hdmi_ग_लिखोb(hdmi, hsync_len >> 8, HDMI_FC_HSYNCINWIDTH1);
	hdmi_ग_लिखोb(hdmi, hsync_len, HDMI_FC_HSYNCINWIDTH0);

	/* Set up VSYNC active edge delay (in lines) */
	hdmi_ग_लिखोb(hdmi, vsync_len, HDMI_FC_VSYNCINWIDTH);
पूर्ण

/* HDMI Initialization Step B.4 */
अटल व्योम dw_hdmi_enable_video_path(काष्ठा dw_hdmi *hdmi)
अणु
	/* control period minimum duration */
	hdmi_ग_लिखोb(hdmi, 12, HDMI_FC_CTRLDUR);
	hdmi_ग_लिखोb(hdmi, 32, HDMI_FC_EXCTRLDUR);
	hdmi_ग_लिखोb(hdmi, 1, HDMI_FC_EXCTRLSPAC);

	/* Set to fill TMDS data channels */
	hdmi_ग_लिखोb(hdmi, 0x0B, HDMI_FC_CH0PREAM);
	hdmi_ग_लिखोb(hdmi, 0x16, HDMI_FC_CH1PREAM);
	hdmi_ग_लिखोb(hdmi, 0x21, HDMI_FC_CH2PREAM);

	/* Enable pixel घड़ी and पंचांगds data path */
	hdmi->mc_clkdis |= HDMI_MC_CLKDIS_HDCPCLK_DISABLE |
			   HDMI_MC_CLKDIS_CSCCLK_DISABLE |
			   HDMI_MC_CLKDIS_AUDCLK_DISABLE |
			   HDMI_MC_CLKDIS_PREPCLK_DISABLE |
			   HDMI_MC_CLKDIS_TMDSCLK_DISABLE;
	hdmi->mc_clkdis &= ~HDMI_MC_CLKDIS_PIXELCLK_DISABLE;
	hdmi_ग_लिखोb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);

	hdmi->mc_clkdis &= ~HDMI_MC_CLKDIS_TMDSCLK_DISABLE;
	hdmi_ग_लिखोb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);

	/* Enable csc path */
	अगर (is_csc_needed(hdmi)) अणु
		hdmi->mc_clkdis &= ~HDMI_MC_CLKDIS_CSCCLK_DISABLE;
		hdmi_ग_लिखोb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);

		hdmi_ग_लिखोb(hdmi, HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_IN_PATH,
			    HDMI_MC_FLOWCTRL);
	पूर्ण अन्यथा अणु
		hdmi->mc_clkdis |= HDMI_MC_CLKDIS_CSCCLK_DISABLE;
		hdmi_ग_लिखोb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);

		hdmi_ग_लिखोb(hdmi, HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_BYPASS,
			    HDMI_MC_FLOWCTRL);
	पूर्ण
पूर्ण

/* Workaround to clear the overflow condition */
अटल व्योम dw_hdmi_clear_overflow(काष्ठा dw_hdmi *hdmi)
अणु
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक i;
	u8 val;

	/*
	 * Under some circumstances the Frame Composer arithmetic unit can miss
	 * an FC रेजिस्टर ग_लिखो due to being busy processing the previous one.
	 * The issue can be worked around by issuing a TMDS software reset and
	 * then ग_लिखो one of the FC रेजिस्टरs several बार.
	 *
	 * The number of iterations matters and depends on the HDMI TX revision
	 * (and possibly on the platक्रमm). So far i.MX6Q (v1.30a), i.MX6DL
	 * (v1.31a) and multiple Allwinner SoCs (v1.32a) have been identअगरied
	 * as needing the workaround, with 4 iterations क्रम v1.30a and 1
	 * iteration क्रम others.
	 * The Amlogic Meson GX SoCs (v2.01a) have been identअगरied as needing
	 * the workaround with a single iteration.
	 * The Rockchip RK3288 SoC (v2.00a) and RK3328/RK3399 SoCs (v2.11a) have
	 * been identअगरied as needing the workaround with a single iteration.
	 */

	चयन (hdmi->version) अणु
	हाल 0x130a:
		count = 4;
		अवरोध;
	हाल 0x131a:
	हाल 0x132a:
	हाल 0x200a:
	हाल 0x201a:
	हाल 0x211a:
	हाल 0x212a:
		count = 1;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* TMDS software reset */
	hdmi_ग_लिखोb(hdmi, (u8)~HDMI_MC_SWRSTZ_TMDSSWRST_REQ, HDMI_MC_SWRSTZ);

	val = hdmi_पढ़ोb(hdmi, HDMI_FC_INVIDCONF);
	क्रम (i = 0; i < count; i++)
		hdmi_ग_लिखोb(hdmi, val, HDMI_FC_INVIDCONF);
पूर्ण

अटल व्योम hdmi_disable_overflow_पूर्णांकerrupts(काष्ठा dw_hdmi *hdmi)
अणु
	hdmi_ग_लिखोb(hdmi, HDMI_IH_MUTE_FC_STAT2_OVERFLOW_MASK,
		    HDMI_IH_MUTE_FC_STAT2);
पूर्ण

अटल पूर्णांक dw_hdmi_setup(काष्ठा dw_hdmi *hdmi,
			 स्थिर काष्ठा drm_connector *connector,
			 स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक ret;

	hdmi_disable_overflow_पूर्णांकerrupts(hdmi);

	hdmi->vic = drm_match_cea_mode(mode);

	अगर (!hdmi->vic) अणु
		dev_dbg(hdmi->dev, "Non-CEA mode used in HDMI\n");
	पूर्ण अन्यथा अणु
		dev_dbg(hdmi->dev, "CEA mode used vic=%d\n", hdmi->vic);
	पूर्ण

	अगर ((hdmi->vic == 6) || (hdmi->vic == 7) ||
	    (hdmi->vic == 21) || (hdmi->vic == 22) ||
	    (hdmi->vic == 2) || (hdmi->vic == 3) ||
	    (hdmi->vic == 17) || (hdmi->vic == 18))
		hdmi->hdmi_data.enc_out_encoding = V4L2_YCBCR_ENC_601;
	अन्यथा
		hdmi->hdmi_data.enc_out_encoding = V4L2_YCBCR_ENC_709;

	hdmi->hdmi_data.video_mode.mpixelrepetitionoutput = 0;
	hdmi->hdmi_data.video_mode.mpixelrepetitioninput = 0;

	अगर (hdmi->hdmi_data.enc_in_bus_क्रमmat == MEDIA_BUS_FMT_FIXED)
		hdmi->hdmi_data.enc_in_bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;

	/* TOFIX: Get input encoding from plat data or fallback to none */
	अगर (hdmi->plat_data->input_bus_encoding)
		hdmi->hdmi_data.enc_in_encoding =
			hdmi->plat_data->input_bus_encoding;
	अन्यथा
		hdmi->hdmi_data.enc_in_encoding = V4L2_YCBCR_ENC_DEFAULT;

	अगर (hdmi->hdmi_data.enc_out_bus_क्रमmat == MEDIA_BUS_FMT_FIXED)
		hdmi->hdmi_data.enc_out_bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;

	hdmi->hdmi_data.rgb_limited_range = hdmi->sink_is_hdmi &&
		drm_शेष_rgb_quant_range(mode) ==
		HDMI_QUANTIZATION_RANGE_LIMITED;

	hdmi->hdmi_data.pix_repet_factor = 0;
	hdmi->hdmi_data.hdcp_enable = 0;
	hdmi->hdmi_data.video_mode.mdataenablepolarity = true;

	/* HDMI Initialization Step B.1 */
	hdmi_av_composer(hdmi, &connector->display_info, mode);

	/* HDMI Initializateion Step B.2 */
	ret = hdmi->phy.ops->init(hdmi, hdmi->phy.data,
				  &connector->display_info,
				  &hdmi->previous_mode);
	अगर (ret)
		वापस ret;
	hdmi->phy.enabled = true;

	/* HDMI Initialization Step B.3 */
	dw_hdmi_enable_video_path(hdmi);

	अगर (hdmi->sink_has_audio) अणु
		dev_dbg(hdmi->dev, "sink has audio support\n");

		/* HDMI Initialization Step E - Configure audio */
		hdmi_clk_regenerator_update_pixel_घड़ी(hdmi);
		hdmi_enable_audio_clk(hdmi, hdmi->audio_enable);
	पूर्ण

	/* not क्रम DVI mode */
	अगर (hdmi->sink_is_hdmi) अणु
		dev_dbg(hdmi->dev, "%s HDMI mode\n", __func__);

		/* HDMI Initialization Step F - Configure AVI InfoFrame */
		hdmi_config_AVI(hdmi, connector, mode);
		hdmi_config_venकरोr_specअगरic_infoframe(hdmi, connector, mode);
		hdmi_config_drm_infoframe(hdmi, connector);
	पूर्ण अन्यथा अणु
		dev_dbg(hdmi->dev, "%s DVI mode\n", __func__);
	पूर्ण

	hdmi_video_packetize(hdmi);
	hdmi_video_csc(hdmi);
	hdmi_video_sample(hdmi);
	hdmi_tx_hdcp_config(hdmi);

	dw_hdmi_clear_overflow(hdmi);

	वापस 0;
पूर्ण

अटल व्योम initialize_hdmi_ih_mutes(काष्ठा dw_hdmi *hdmi)
अणु
	u8 ih_mute;

	/*
	 * Boot up शेषs are:
	 * HDMI_IH_MUTE   = 0x03 (disabled)
	 * HDMI_IH_MUTE_* = 0x00 (enabled)
	 *
	 * Disable top level पूर्णांकerrupt bits in HDMI block
	 */
	ih_mute = hdmi_पढ़ोb(hdmi, HDMI_IH_MUTE) |
		  HDMI_IH_MUTE_MUTE_WAKEUP_INTERRUPT |
		  HDMI_IH_MUTE_MUTE_ALL_INTERRUPT;

	hdmi_ग_लिखोb(hdmi, ih_mute, HDMI_IH_MUTE);

	/* by शेष mask all पूर्णांकerrupts */
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_VP_MASK);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_FC_MASK0);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_FC_MASK1);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_FC_MASK2);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_PHY_MASK0);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_PHY_I2CM_INT_ADDR);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_PHY_I2CM_CTLINT_ADDR);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_AUD_INT);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_AUD_SPDIFINT);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_AUD_HBR_MASK);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_GP_MASK);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_A_APIINTMSK);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_I2CM_INT);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_I2CM_CTLINT);

	/* Disable पूर्णांकerrupts in the IH_MUTE_* रेजिस्टरs */
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_IH_MUTE_FC_STAT0);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_IH_MUTE_FC_STAT1);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_IH_MUTE_FC_STAT2);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_IH_MUTE_AS_STAT0);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_IH_MUTE_PHY_STAT0);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_IH_MUTE_I2CM_STAT0);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_IH_MUTE_CEC_STAT0);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_IH_MUTE_VP_STAT0);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_IH_MUTE_I2CMPHY_STAT0);
	hdmi_ग_लिखोb(hdmi, 0xff, HDMI_IH_MUTE_AHBDMAAUD_STAT0);

	/* Enable top level पूर्णांकerrupt bits in HDMI block */
	ih_mute &= ~(HDMI_IH_MUTE_MUTE_WAKEUP_INTERRUPT |
		    HDMI_IH_MUTE_MUTE_ALL_INTERRUPT);
	hdmi_ग_लिखोb(hdmi, ih_mute, HDMI_IH_MUTE);
पूर्ण

अटल व्योम dw_hdmi_घातeron(काष्ठा dw_hdmi *hdmi)
अणु
	hdmi->bridge_is_on = true;

	/*
	 * The curr_conn field is guaranteed to be valid here, as this function
	 * is only be called when !hdmi->disabled.
	 */
	dw_hdmi_setup(hdmi, hdmi->curr_conn, &hdmi->previous_mode);
पूर्ण

अटल व्योम dw_hdmi_घातeroff(काष्ठा dw_hdmi *hdmi)
अणु
	अगर (hdmi->phy.enabled) अणु
		hdmi->phy.ops->disable(hdmi, hdmi->phy.data);
		hdmi->phy.enabled = false;
	पूर्ण

	hdmi->bridge_is_on = false;
पूर्ण

अटल व्योम dw_hdmi_update_घातer(काष्ठा dw_hdmi *hdmi)
अणु
	पूर्णांक क्रमce = hdmi->क्रमce;

	अगर (hdmi->disabled) अणु
		क्रमce = DRM_FORCE_OFF;
	पूर्ण अन्यथा अगर (क्रमce == DRM_FORCE_UNSPECIFIED) अणु
		अगर (hdmi->rxsense)
			क्रमce = DRM_FORCE_ON;
		अन्यथा
			क्रमce = DRM_FORCE_OFF;
	पूर्ण

	अगर (क्रमce == DRM_FORCE_OFF) अणु
		अगर (hdmi->bridge_is_on)
			dw_hdmi_घातeroff(hdmi);
	पूर्ण अन्यथा अणु
		अगर (!hdmi->bridge_is_on)
			dw_hdmi_घातeron(hdmi);
	पूर्ण
पूर्ण

/*
 * Adjust the detection of RXSENSE according to whether we have a क्रमced
 * connection mode enabled, or whether we have been disabled.  There is
 * no poपूर्णांक processing RXSENSE पूर्णांकerrupts अगर we have a क्रमced connection
 * state, or DRM has us disabled.
 *
 * We also disable rxsense पूर्णांकerrupts when we think we're disconnected
 * to aव्योम भग्नing TDMS संकेतs giving false rxsense पूर्णांकerrupts.
 *
 * Note: we still need to listen क्रम HPD पूर्णांकerrupts even when DRM has us
 * disabled so that we can detect a connect event.
 */
अटल व्योम dw_hdmi_update_phy_mask(काष्ठा dw_hdmi *hdmi)
अणु
	अगर (hdmi->phy.ops->update_hpd)
		hdmi->phy.ops->update_hpd(hdmi, hdmi->phy.data,
					  hdmi->क्रमce, hdmi->disabled,
					  hdmi->rxsense);
पूर्ण

अटल क्रमागत drm_connector_status dw_hdmi_detect(काष्ठा dw_hdmi *hdmi)
अणु
	क्रमागत drm_connector_status result;

	result = hdmi->phy.ops->पढ़ो_hpd(hdmi, hdmi->phy.data);

	mutex_lock(&hdmi->mutex);
	अगर (result != hdmi->last_connector_result) अणु
		dev_dbg(hdmi->dev, "read_hpd result: %d", result);
		handle_plugged_change(hdmi,
				      result == connector_status_connected);
		hdmi->last_connector_result = result;
	पूर्ण
	mutex_unlock(&hdmi->mutex);

	वापस result;
पूर्ण

अटल काष्ठा edid *dw_hdmi_get_edid(काष्ठा dw_hdmi *hdmi,
				     काष्ठा drm_connector *connector)
अणु
	काष्ठा edid *edid;

	अगर (!hdmi->ddc)
		वापस शून्य;

	edid = drm_get_edid(connector, hdmi->ddc);
	अगर (!edid) अणु
		dev_dbg(hdmi->dev, "failed to get edid\n");
		वापस शून्य;
	पूर्ण

	dev_dbg(hdmi->dev, "got edid: width[%d] x height[%d]\n",
		edid->width_cm, edid->height_cm);

	hdmi->sink_is_hdmi = drm_detect_hdmi_monitor(edid);
	hdmi->sink_has_audio = drm_detect_monitor_audio(edid);

	वापस edid;
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM Connector Operations
 */

अटल क्रमागत drm_connector_status
dw_hdmi_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा dw_hdmi *hdmi = container_of(connector, काष्ठा dw_hdmi,
					     connector);
	वापस dw_hdmi_detect(hdmi);
पूर्ण

अटल पूर्णांक dw_hdmi_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा dw_hdmi *hdmi = container_of(connector, काष्ठा dw_hdmi,
					     connector);
	काष्ठा edid *edid;
	पूर्णांक ret;

	edid = dw_hdmi_get_edid(hdmi, connector);
	अगर (!edid)
		वापस 0;

	drm_connector_update_edid_property(connector, edid);
	cec_notअगरier_set_phys_addr_from_edid(hdmi->cec_notअगरier, edid);
	ret = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल bool hdr_metadata_equal(स्थिर काष्ठा drm_connector_state *old_state,
			       स्थिर काष्ठा drm_connector_state *new_state)
अणु
	काष्ठा drm_property_blob *old_blob = old_state->hdr_output_metadata;
	काष्ठा drm_property_blob *new_blob = new_state->hdr_output_metadata;

	अगर (!old_blob || !new_blob)
		वापस old_blob == new_blob;

	अगर (old_blob->length != new_blob->length)
		वापस false;

	वापस !स_भेद(old_blob->data, new_blob->data, old_blob->length);
पूर्ण

अटल पूर्णांक dw_hdmi_connector_atomic_check(काष्ठा drm_connector *connector,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *old_state =
		drm_atomic_get_old_connector_state(state, connector);
	काष्ठा drm_connector_state *new_state =
		drm_atomic_get_new_connector_state(state, connector);
	काष्ठा drm_crtc *crtc = new_state->crtc;
	काष्ठा drm_crtc_state *crtc_state;

	अगर (!crtc)
		वापस 0;

	अगर (!hdr_metadata_equal(old_state, new_state)) अणु
		crtc_state = drm_atomic_get_crtc_state(state, crtc);
		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);

		crtc_state->mode_changed = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw_hdmi_connector_क्रमce(काष्ठा drm_connector *connector)
अणु
	काष्ठा dw_hdmi *hdmi = container_of(connector, काष्ठा dw_hdmi,
					     connector);

	mutex_lock(&hdmi->mutex);
	hdmi->क्रमce = connector->क्रमce;
	dw_hdmi_update_घातer(hdmi);
	dw_hdmi_update_phy_mask(hdmi);
	mutex_unlock(&hdmi->mutex);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs dw_hdmi_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = dw_hdmi_connector_detect,
	.destroy = drm_connector_cleanup,
	.क्रमce = dw_hdmi_connector_क्रमce,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs dw_hdmi_connector_helper_funcs = अणु
	.get_modes = dw_hdmi_connector_get_modes,
	.atomic_check = dw_hdmi_connector_atomic_check,
पूर्ण;

अटल पूर्णांक dw_hdmi_connector_create(काष्ठा dw_hdmi *hdmi)
अणु
	काष्ठा drm_connector *connector = &hdmi->connector;
	काष्ठा cec_connector_info conn_info;
	काष्ठा cec_notअगरier *notअगरier;

	अगर (hdmi->version >= 0x200a)
		connector->ycbcr_420_allowed =
			hdmi->plat_data->ycbcr_420_allowed;
	अन्यथा
		connector->ycbcr_420_allowed = false;

	connector->पूर्णांकerlace_allowed = 1;
	connector->polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_helper_add(connector, &dw_hdmi_connector_helper_funcs);

	drm_connector_init_with_ddc(hdmi->bridge.dev, connector,
				    &dw_hdmi_connector_funcs,
				    DRM_MODE_CONNECTOR_HDMIA,
				    hdmi->ddc);

	/*
	 * drm_connector_attach_max_bpc_property() requires the
	 * connector to have a state.
	 */
	drm_atomic_helper_connector_reset(connector);

	drm_connector_attach_max_bpc_property(connector, 8, 16);

	अगर (hdmi->version >= 0x200a && hdmi->plat_data->use_drm_infoframe)
		drm_object_attach_property(&connector->base,
			connector->dev->mode_config.hdr_output_metadata_property, 0);

	drm_connector_attach_encoder(connector, hdmi->bridge.encoder);

	cec_fill_conn_info_from_drm(&conn_info, connector);

	notअगरier = cec_notअगरier_conn_रेजिस्टर(hdmi->dev, शून्य, &conn_info);
	अगर (!notअगरier)
		वापस -ENOMEM;

	mutex_lock(&hdmi->cec_notअगरier_mutex);
	hdmi->cec_notअगरier = notअगरier;
	mutex_unlock(&hdmi->cec_notअगरier_mutex);

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * DRM Bridge Operations
 */

/*
 * Possible output क्रमmats :
 * - MEDIA_BUS_FMT_UYYVYY16_0_5X48,
 * - MEDIA_BUS_FMT_UYYVYY12_0_5X36,
 * - MEDIA_BUS_FMT_UYYVYY10_0_5X30,
 * - MEDIA_BUS_FMT_UYYVYY8_0_5X24,
 * - MEDIA_BUS_FMT_YUV16_1X48,
 * - MEDIA_BUS_FMT_RGB161616_1X48,
 * - MEDIA_BUS_FMT_UYVY12_1X24,
 * - MEDIA_BUS_FMT_YUV12_1X36,
 * - MEDIA_BUS_FMT_RGB121212_1X36,
 * - MEDIA_BUS_FMT_UYVY10_1X20,
 * - MEDIA_BUS_FMT_YUV10_1X30,
 * - MEDIA_BUS_FMT_RGB101010_1X30,
 * - MEDIA_BUS_FMT_UYVY8_1X16,
 * - MEDIA_BUS_FMT_YUV8_1X24,
 * - MEDIA_BUS_FMT_RGB888_1X24,
 */

/* Can वापस a maximum of 11 possible output क्रमmats क्रम a mode/connector */
#घोषणा MAX_OUTPUT_SEL_FORMATS	11

अटल u32 *dw_hdmi_bridge_atomic_get_output_bus_fmts(काष्ठा drm_bridge *bridge,
					काष्ठा drm_bridge_state *bridge_state,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state,
					अचिन्हित पूर्णांक *num_output_fmts)
अणु
	काष्ठा drm_connector *conn = conn_state->connector;
	काष्ठा drm_display_info *info = &conn->display_info;
	काष्ठा drm_display_mode *mode = &crtc_state->mode;
	u8 max_bpc = conn_state->max_requested_bpc;
	bool is_hdmi2_sink = info->hdmi.scdc.supported ||
			     (info->color_क्रमmats & DRM_COLOR_FORMAT_YCRCB420);
	u32 *output_fmts;
	अचिन्हित पूर्णांक i = 0;

	*num_output_fmts = 0;

	output_fmts = kसुस्मृति(MAX_OUTPUT_SEL_FORMATS, माप(*output_fmts),
			      GFP_KERNEL);
	अगर (!output_fmts)
		वापस शून्य;

	/* If dw-hdmi is the only bridge, aव्योम negociating with ourselves */
	अगर (list_is_singular(&bridge->encoder->bridge_chain)) अणु
		*num_output_fmts = 1;
		output_fmts[0] = MEDIA_BUS_FMT_FIXED;

		वापस output_fmts;
	पूर्ण

	/*
	 * If the current mode enक्रमces 4:2:0, क्रमce the output but क्रमmat
	 * to 4:2:0 and करो not add the YUV422/444/RGB क्रमmats
	 */
	अगर (conn->ycbcr_420_allowed &&
	    (drm_mode_is_420_only(info, mode) ||
	     (is_hdmi2_sink && drm_mode_is_420_also(info, mode)))) अणु

		/* Order bus क्रमmats from 16bit to 8bit अगर supported */
		अगर (max_bpc >= 16 && info->bpc == 16 &&
		    (info->hdmi.y420_dc_modes & DRM_EDID_YCBCR420_DC_48))
			output_fmts[i++] = MEDIA_BUS_FMT_UYYVYY16_0_5X48;

		अगर (max_bpc >= 12 && info->bpc >= 12 &&
		    (info->hdmi.y420_dc_modes & DRM_EDID_YCBCR420_DC_36))
			output_fmts[i++] = MEDIA_BUS_FMT_UYYVYY12_0_5X36;

		अगर (max_bpc >= 10 && info->bpc >= 10 &&
		    (info->hdmi.y420_dc_modes & DRM_EDID_YCBCR420_DC_30))
			output_fmts[i++] = MEDIA_BUS_FMT_UYYVYY10_0_5X30;

		/* Default 8bit fallback */
		output_fmts[i++] = MEDIA_BUS_FMT_UYYVYY8_0_5X24;

		*num_output_fmts = i;

		वापस output_fmts;
	पूर्ण

	/*
	 * Order bus क्रमmats from 16bit to 8bit and from YUV422 to RGB
	 * अगर supported. In any हाल the शेष RGB888 क्रमmat is added
	 */

	अगर (max_bpc >= 16 && info->bpc == 16) अणु
		अगर (info->color_क्रमmats & DRM_COLOR_FORMAT_YCRCB444)
			output_fmts[i++] = MEDIA_BUS_FMT_YUV16_1X48;

		output_fmts[i++] = MEDIA_BUS_FMT_RGB161616_1X48;
	पूर्ण

	अगर (max_bpc >= 12 && info->bpc >= 12) अणु
		अगर (info->color_क्रमmats & DRM_COLOR_FORMAT_YCRCB422)
			output_fmts[i++] = MEDIA_BUS_FMT_UYVY12_1X24;

		अगर (info->color_क्रमmats & DRM_COLOR_FORMAT_YCRCB444)
			output_fmts[i++] = MEDIA_BUS_FMT_YUV12_1X36;

		output_fmts[i++] = MEDIA_BUS_FMT_RGB121212_1X36;
	पूर्ण

	अगर (max_bpc >= 10 && info->bpc >= 10) अणु
		अगर (info->color_क्रमmats & DRM_COLOR_FORMAT_YCRCB422)
			output_fmts[i++] = MEDIA_BUS_FMT_UYVY10_1X20;

		अगर (info->color_क्रमmats & DRM_COLOR_FORMAT_YCRCB444)
			output_fmts[i++] = MEDIA_BUS_FMT_YUV10_1X30;

		output_fmts[i++] = MEDIA_BUS_FMT_RGB101010_1X30;
	पूर्ण

	अगर (info->color_क्रमmats & DRM_COLOR_FORMAT_YCRCB422)
		output_fmts[i++] = MEDIA_BUS_FMT_UYVY8_1X16;

	अगर (info->color_क्रमmats & DRM_COLOR_FORMAT_YCRCB444)
		output_fmts[i++] = MEDIA_BUS_FMT_YUV8_1X24;

	/* Default 8bit RGB fallback */
	output_fmts[i++] = MEDIA_BUS_FMT_RGB888_1X24;

	*num_output_fmts = i;

	वापस output_fmts;
पूर्ण

/*
 * Possible input क्रमmats :
 * - MEDIA_BUS_FMT_RGB888_1X24
 * - MEDIA_BUS_FMT_YUV8_1X24
 * - MEDIA_BUS_FMT_UYVY8_1X16
 * - MEDIA_BUS_FMT_UYYVYY8_0_5X24
 * - MEDIA_BUS_FMT_RGB101010_1X30
 * - MEDIA_BUS_FMT_YUV10_1X30
 * - MEDIA_BUS_FMT_UYVY10_1X20
 * - MEDIA_BUS_FMT_UYYVYY10_0_5X30
 * - MEDIA_BUS_FMT_RGB121212_1X36
 * - MEDIA_BUS_FMT_YUV12_1X36
 * - MEDIA_BUS_FMT_UYVY12_1X24
 * - MEDIA_BUS_FMT_UYYVYY12_0_5X36
 * - MEDIA_BUS_FMT_RGB161616_1X48
 * - MEDIA_BUS_FMT_YUV16_1X48
 * - MEDIA_BUS_FMT_UYYVYY16_0_5X48
 */

/* Can वापस a maximum of 3 possible input क्रमmats क्रम an output क्रमmat */
#घोषणा MAX_INPUT_SEL_FORMATS	3

अटल u32 *dw_hdmi_bridge_atomic_get_input_bus_fmts(काष्ठा drm_bridge *bridge,
					काष्ठा drm_bridge_state *bridge_state,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state,
					u32 output_fmt,
					अचिन्हित पूर्णांक *num_input_fmts)
अणु
	u32 *input_fmts;
	अचिन्हित पूर्णांक i = 0;

	*num_input_fmts = 0;

	input_fmts = kसुस्मृति(MAX_INPUT_SEL_FORMATS, माप(*input_fmts),
			     GFP_KERNEL);
	अगर (!input_fmts)
		वापस शून्य;

	चयन (output_fmt) अणु
	/* If MEDIA_BUS_FMT_FIXED is tested, वापस शेष bus क्रमmat */
	हाल MEDIA_BUS_FMT_FIXED:
		input_fmts[i++] = MEDIA_BUS_FMT_RGB888_1X24;
		अवरोध;
	/* 8bit */
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		input_fmts[i++] = MEDIA_BUS_FMT_RGB888_1X24;
		input_fmts[i++] = MEDIA_BUS_FMT_YUV8_1X24;
		input_fmts[i++] = MEDIA_BUS_FMT_UYVY8_1X16;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUV8_1X24:
		input_fmts[i++] = MEDIA_BUS_FMT_YUV8_1X24;
		input_fmts[i++] = MEDIA_BUS_FMT_UYVY8_1X16;
		input_fmts[i++] = MEDIA_BUS_FMT_RGB888_1X24;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
		input_fmts[i++] = MEDIA_BUS_FMT_UYVY8_1X16;
		input_fmts[i++] = MEDIA_BUS_FMT_YUV8_1X24;
		input_fmts[i++] = MEDIA_BUS_FMT_RGB888_1X24;
		अवरोध;

	/* 10bit */
	हाल MEDIA_BUS_FMT_RGB101010_1X30:
		input_fmts[i++] = MEDIA_BUS_FMT_RGB101010_1X30;
		input_fmts[i++] = MEDIA_BUS_FMT_YUV10_1X30;
		input_fmts[i++] = MEDIA_BUS_FMT_UYVY10_1X20;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUV10_1X30:
		input_fmts[i++] = MEDIA_BUS_FMT_YUV10_1X30;
		input_fmts[i++] = MEDIA_BUS_FMT_UYVY10_1X20;
		input_fmts[i++] = MEDIA_BUS_FMT_RGB101010_1X30;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY10_1X20:
		input_fmts[i++] = MEDIA_BUS_FMT_UYVY10_1X20;
		input_fmts[i++] = MEDIA_BUS_FMT_YUV10_1X30;
		input_fmts[i++] = MEDIA_BUS_FMT_RGB101010_1X30;
		अवरोध;

	/* 12bit */
	हाल MEDIA_BUS_FMT_RGB121212_1X36:
		input_fmts[i++] = MEDIA_BUS_FMT_RGB121212_1X36;
		input_fmts[i++] = MEDIA_BUS_FMT_YUV12_1X36;
		input_fmts[i++] = MEDIA_BUS_FMT_UYVY12_1X24;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUV12_1X36:
		input_fmts[i++] = MEDIA_BUS_FMT_YUV12_1X36;
		input_fmts[i++] = MEDIA_BUS_FMT_UYVY12_1X24;
		input_fmts[i++] = MEDIA_BUS_FMT_RGB121212_1X36;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY12_1X24:
		input_fmts[i++] = MEDIA_BUS_FMT_UYVY12_1X24;
		input_fmts[i++] = MEDIA_BUS_FMT_YUV12_1X36;
		input_fmts[i++] = MEDIA_BUS_FMT_RGB121212_1X36;
		अवरोध;

	/* 16bit */
	हाल MEDIA_BUS_FMT_RGB161616_1X48:
		input_fmts[i++] = MEDIA_BUS_FMT_RGB161616_1X48;
		input_fmts[i++] = MEDIA_BUS_FMT_YUV16_1X48;
		अवरोध;
	हाल MEDIA_BUS_FMT_YUV16_1X48:
		input_fmts[i++] = MEDIA_BUS_FMT_YUV16_1X48;
		input_fmts[i++] = MEDIA_BUS_FMT_RGB161616_1X48;
		अवरोध;

	/*YUV 4:2:0 */
	हाल MEDIA_BUS_FMT_UYYVYY8_0_5X24:
	हाल MEDIA_BUS_FMT_UYYVYY10_0_5X30:
	हाल MEDIA_BUS_FMT_UYYVYY12_0_5X36:
	हाल MEDIA_BUS_FMT_UYYVYY16_0_5X48:
		input_fmts[i++] = output_fmt;
		अवरोध;
	पूर्ण

	*num_input_fmts = i;

	अगर (*num_input_fmts == 0) अणु
		kमुक्त(input_fmts);
		input_fmts = शून्य;
	पूर्ण

	वापस input_fmts;
पूर्ण

अटल पूर्णांक dw_hdmi_bridge_atomic_check(काष्ठा drm_bridge *bridge,
				       काष्ठा drm_bridge_state *bridge_state,
				       काष्ठा drm_crtc_state *crtc_state,
				       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा dw_hdmi *hdmi = bridge->driver_निजी;

	hdmi->hdmi_data.enc_out_bus_क्रमmat =
			bridge_state->output_bus_cfg.क्रमmat;

	hdmi->hdmi_data.enc_in_bus_क्रमmat =
			bridge_state->input_bus_cfg.क्रमmat;

	dev_dbg(hdmi->dev, "input format 0x%04x, output format 0x%04x\n",
		bridge_state->input_bus_cfg.क्रमmat,
		bridge_state->output_bus_cfg.क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा dw_hdmi *hdmi = bridge->driver_निजी;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)
		वापस 0;

	वापस dw_hdmi_connector_create(hdmi);
पूर्ण

अटल व्योम dw_hdmi_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा dw_hdmi *hdmi = bridge->driver_निजी;

	mutex_lock(&hdmi->cec_notअगरier_mutex);
	cec_notअगरier_conn_unरेजिस्टर(hdmi->cec_notअगरier);
	hdmi->cec_notअगरier = शून्य;
	mutex_unlock(&hdmi->cec_notअगरier_mutex);
पूर्ण

अटल क्रमागत drm_mode_status
dw_hdmi_bridge_mode_valid(काष्ठा drm_bridge *bridge,
			  स्थिर काष्ठा drm_display_info *info,
			  स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा dw_hdmi *hdmi = bridge->driver_निजी;
	स्थिर काष्ठा dw_hdmi_plat_data *pdata = hdmi->plat_data;
	क्रमागत drm_mode_status mode_status = MODE_OK;

	/* We करोn't support द्विगुन-घड़ीed modes */
	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		वापस MODE_BAD;

	अगर (pdata->mode_valid)
		mode_status = pdata->mode_valid(hdmi, pdata->priv_data, info,
						mode);

	वापस mode_status;
पूर्ण

अटल व्योम dw_hdmi_bridge_mode_set(काष्ठा drm_bridge *bridge,
				    स्थिर काष्ठा drm_display_mode *orig_mode,
				    स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा dw_hdmi *hdmi = bridge->driver_निजी;

	mutex_lock(&hdmi->mutex);

	/* Store the display mode क्रम plugin/DKMS घातeron events */
	स_नकल(&hdmi->previous_mode, mode, माप(hdmi->previous_mode));

	mutex_unlock(&hdmi->mutex);
पूर्ण

अटल व्योम dw_hdmi_bridge_atomic_disable(काष्ठा drm_bridge *bridge,
					  काष्ठा drm_bridge_state *old_state)
अणु
	काष्ठा dw_hdmi *hdmi = bridge->driver_निजी;

	mutex_lock(&hdmi->mutex);
	hdmi->disabled = true;
	hdmi->curr_conn = शून्य;
	dw_hdmi_update_घातer(hdmi);
	dw_hdmi_update_phy_mask(hdmi);
	mutex_unlock(&hdmi->mutex);
पूर्ण

अटल व्योम dw_hdmi_bridge_atomic_enable(काष्ठा drm_bridge *bridge,
					 काष्ठा drm_bridge_state *old_state)
अणु
	काष्ठा dw_hdmi *hdmi = bridge->driver_निजी;
	काष्ठा drm_atomic_state *state = old_state->base.state;
	काष्ठा drm_connector *connector;

	connector = drm_atomic_get_new_connector_क्रम_encoder(state,
							     bridge->encoder);

	mutex_lock(&hdmi->mutex);
	hdmi->disabled = false;
	hdmi->curr_conn = connector;
	dw_hdmi_update_घातer(hdmi);
	dw_hdmi_update_phy_mask(hdmi);
	mutex_unlock(&hdmi->mutex);
पूर्ण

अटल क्रमागत drm_connector_status dw_hdmi_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा dw_hdmi *hdmi = bridge->driver_निजी;

	वापस dw_hdmi_detect(hdmi);
पूर्ण

अटल काष्ठा edid *dw_hdmi_bridge_get_edid(काष्ठा drm_bridge *bridge,
					    काष्ठा drm_connector *connector)
अणु
	काष्ठा dw_hdmi *hdmi = bridge->driver_निजी;

	वापस dw_hdmi_get_edid(hdmi, connector);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs dw_hdmi_bridge_funcs = अणु
	.atomic_duplicate_state = drm_atomic_helper_bridge_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_bridge_destroy_state,
	.atomic_reset = drm_atomic_helper_bridge_reset,
	.attach = dw_hdmi_bridge_attach,
	.detach = dw_hdmi_bridge_detach,
	.atomic_check = dw_hdmi_bridge_atomic_check,
	.atomic_get_output_bus_fmts = dw_hdmi_bridge_atomic_get_output_bus_fmts,
	.atomic_get_input_bus_fmts = dw_hdmi_bridge_atomic_get_input_bus_fmts,
	.atomic_enable = dw_hdmi_bridge_atomic_enable,
	.atomic_disable = dw_hdmi_bridge_atomic_disable,
	.mode_set = dw_hdmi_bridge_mode_set,
	.mode_valid = dw_hdmi_bridge_mode_valid,
	.detect = dw_hdmi_bridge_detect,
	.get_edid = dw_hdmi_bridge_get_edid,
पूर्ण;

/* -----------------------------------------------------------------------------
 * IRQ Handling
 */

अटल irqवापस_t dw_hdmi_i2c_irq(काष्ठा dw_hdmi *hdmi)
अणु
	काष्ठा dw_hdmi_i2c *i2c = hdmi->i2c;
	अचिन्हित पूर्णांक stat;

	stat = hdmi_पढ़ोb(hdmi, HDMI_IH_I2CM_STAT0);
	अगर (!stat)
		वापस IRQ_NONE;

	hdmi_ग_लिखोb(hdmi, stat, HDMI_IH_I2CM_STAT0);

	i2c->stat = stat;

	complete(&i2c->cmp);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dw_hdmi_hardirq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dw_hdmi *hdmi = dev_id;
	u8 पूर्णांकr_stat;
	irqवापस_t ret = IRQ_NONE;

	अगर (hdmi->i2c)
		ret = dw_hdmi_i2c_irq(hdmi);

	पूर्णांकr_stat = hdmi_पढ़ोb(hdmi, HDMI_IH_PHY_STAT0);
	अगर (पूर्णांकr_stat) अणु
		hdmi_ग_लिखोb(hdmi, ~0, HDMI_IH_MUTE_PHY_STAT0);
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	वापस ret;
पूर्ण

व्योम dw_hdmi_setup_rx_sense(काष्ठा dw_hdmi *hdmi, bool hpd, bool rx_sense)
अणु
	mutex_lock(&hdmi->mutex);

	अगर (!hdmi->क्रमce) अणु
		/*
		 * If the RX sense status indicates we're disconnected,
		 * clear the software rxsense status.
		 */
		अगर (!rx_sense)
			hdmi->rxsense = false;

		/*
		 * Only set the software rxsense status when both
		 * rxsense and hpd indicates we're connected.
		 * This aव्योमs what seems to be bad behaviour in
		 * at least iMX6S versions of the phy.
		 */
		अगर (hpd)
			hdmi->rxsense = true;

		dw_hdmi_update_घातer(hdmi);
		dw_hdmi_update_phy_mask(hdmi);
	पूर्ण
	mutex_unlock(&hdmi->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_setup_rx_sense);

अटल irqवापस_t dw_hdmi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dw_hdmi *hdmi = dev_id;
	u8 पूर्णांकr_stat, phy_पूर्णांक_pol, phy_pol_mask, phy_stat;

	पूर्णांकr_stat = hdmi_पढ़ोb(hdmi, HDMI_IH_PHY_STAT0);
	phy_पूर्णांक_pol = hdmi_पढ़ोb(hdmi, HDMI_PHY_POL0);
	phy_stat = hdmi_पढ़ोb(hdmi, HDMI_PHY_STAT0);

	phy_pol_mask = 0;
	अगर (पूर्णांकr_stat & HDMI_IH_PHY_STAT0_HPD)
		phy_pol_mask |= HDMI_PHY_HPD;
	अगर (पूर्णांकr_stat & HDMI_IH_PHY_STAT0_RX_SENSE0)
		phy_pol_mask |= HDMI_PHY_RX_SENSE0;
	अगर (पूर्णांकr_stat & HDMI_IH_PHY_STAT0_RX_SENSE1)
		phy_pol_mask |= HDMI_PHY_RX_SENSE1;
	अगर (पूर्णांकr_stat & HDMI_IH_PHY_STAT0_RX_SENSE2)
		phy_pol_mask |= HDMI_PHY_RX_SENSE2;
	अगर (पूर्णांकr_stat & HDMI_IH_PHY_STAT0_RX_SENSE3)
		phy_pol_mask |= HDMI_PHY_RX_SENSE3;

	अगर (phy_pol_mask)
		hdmi_modb(hdmi, ~phy_पूर्णांक_pol, phy_pol_mask, HDMI_PHY_POL0);

	/*
	 * RX sense tells us whether the TDMS transmitters are detecting
	 * load - in other words, there's something listening on the
	 * other end of the link.  Use this to decide whether we should
	 * घातer on the phy as HPD may be toggled by the sink to merely
	 * ask the source to re-पढ़ो the EDID.
	 */
	अगर (पूर्णांकr_stat &
	    (HDMI_IH_PHY_STAT0_RX_SENSE | HDMI_IH_PHY_STAT0_HPD)) अणु
		dw_hdmi_setup_rx_sense(hdmi,
				       phy_stat & HDMI_PHY_HPD,
				       phy_stat & HDMI_PHY_RX_SENSE);

		अगर ((phy_stat & (HDMI_PHY_RX_SENSE | HDMI_PHY_HPD)) == 0) अणु
			mutex_lock(&hdmi->cec_notअगरier_mutex);
			cec_notअगरier_phys_addr_invalidate(hdmi->cec_notअगरier);
			mutex_unlock(&hdmi->cec_notअगरier_mutex);
		पूर्ण
	पूर्ण

	अगर (पूर्णांकr_stat & HDMI_IH_PHY_STAT0_HPD) अणु
		क्रमागत drm_connector_status status = phy_पूर्णांक_pol & HDMI_PHY_HPD
						 ? connector_status_connected
						 : connector_status_disconnected;

		dev_dbg(hdmi->dev, "EVENT=%s\n",
			status == connector_status_connected ?
			"plugin" : "plugout");

		अगर (hdmi->bridge.dev) अणु
			drm_helper_hpd_irq_event(hdmi->bridge.dev);
			drm_bridge_hpd_notअगरy(&hdmi->bridge, status);
		पूर्ण
	पूर्ण

	hdmi_ग_लिखोb(hdmi, पूर्णांकr_stat, HDMI_IH_PHY_STAT0);
	hdmi_ग_लिखोb(hdmi, ~(HDMI_IH_PHY_STAT0_HPD | HDMI_IH_PHY_STAT0_RX_SENSE),
		    HDMI_IH_MUTE_PHY_STAT0);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा dw_hdmi_phy_data dw_hdmi_phys[] = अणु
	अणु
		.type = DW_HDMI_PHY_DWC_HDMI_TX_PHY,
		.name = "DWC HDMI TX PHY",
		.gen = 1,
	पूर्ण, अणु
		.type = DW_HDMI_PHY_DWC_MHL_PHY_HEAC,
		.name = "DWC MHL PHY + HEAC PHY",
		.gen = 2,
		.has_svsret = true,
		.configure = hdmi_phy_configure_dwc_hdmi_3d_tx,
	पूर्ण, अणु
		.type = DW_HDMI_PHY_DWC_MHL_PHY,
		.name = "DWC MHL PHY",
		.gen = 2,
		.has_svsret = true,
		.configure = hdmi_phy_configure_dwc_hdmi_3d_tx,
	पूर्ण, अणु
		.type = DW_HDMI_PHY_DWC_HDMI_3D_TX_PHY_HEAC,
		.name = "DWC HDMI 3D TX PHY + HEAC PHY",
		.gen = 2,
		.configure = hdmi_phy_configure_dwc_hdmi_3d_tx,
	पूर्ण, अणु
		.type = DW_HDMI_PHY_DWC_HDMI_3D_TX_PHY,
		.name = "DWC HDMI 3D TX PHY",
		.gen = 2,
		.configure = hdmi_phy_configure_dwc_hdmi_3d_tx,
	पूर्ण, अणु
		.type = DW_HDMI_PHY_DWC_HDMI20_TX_PHY,
		.name = "DWC HDMI 2.0 TX PHY",
		.gen = 2,
		.has_svsret = true,
		.configure = hdmi_phy_configure_dwc_hdmi_3d_tx,
	पूर्ण, अणु
		.type = DW_HDMI_PHY_VENDOR_PHY,
		.name = "Vendor PHY",
	पूर्ण
पूर्ण;

अटल पूर्णांक dw_hdmi_detect_phy(काष्ठा dw_hdmi *hdmi)
अणु
	अचिन्हित पूर्णांक i;
	u8 phy_type;

	phy_type = hdmi->plat_data->phy_क्रमce_venकरोr ?
				DW_HDMI_PHY_VENDOR_PHY :
				hdmi_पढ़ोb(hdmi, HDMI_CONFIG2_ID);

	अगर (phy_type == DW_HDMI_PHY_VENDOR_PHY) अणु
		/* Venकरोr PHYs require support from the glue layer. */
		अगर (!hdmi->plat_data->phy_ops || !hdmi->plat_data->phy_name) अणु
			dev_err(hdmi->dev,
				"Vendor HDMI PHY not supported by glue layer\n");
			वापस -ENODEV;
		पूर्ण

		hdmi->phy.ops = hdmi->plat_data->phy_ops;
		hdmi->phy.data = hdmi->plat_data->phy_data;
		hdmi->phy.name = hdmi->plat_data->phy_name;
		वापस 0;
	पूर्ण

	/* Synopsys PHYs are handled पूर्णांकernally. */
	क्रम (i = 0; i < ARRAY_SIZE(dw_hdmi_phys); ++i) अणु
		अगर (dw_hdmi_phys[i].type == phy_type) अणु
			hdmi->phy.ops = &dw_hdmi_synopsys_phy_ops;
			hdmi->phy.name = dw_hdmi_phys[i].name;
			hdmi->phy.data = (व्योम *)&dw_hdmi_phys[i];

			अगर (!dw_hdmi_phys[i].configure &&
			    !hdmi->plat_data->configure_phy) अणु
				dev_err(hdmi->dev, "%s requires platform support\n",
					hdmi->phy.name);
				वापस -ENODEV;
			पूर्ण

			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(hdmi->dev, "Unsupported HDMI PHY type (%02x)\n", phy_type);
	वापस -ENODEV;
पूर्ण

अटल व्योम dw_hdmi_cec_enable(काष्ठा dw_hdmi *hdmi)
अणु
	mutex_lock(&hdmi->mutex);
	hdmi->mc_clkdis &= ~HDMI_MC_CLKDIS_CECCLK_DISABLE;
	hdmi_ग_लिखोb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);
	mutex_unlock(&hdmi->mutex);
पूर्ण

अटल व्योम dw_hdmi_cec_disable(काष्ठा dw_hdmi *hdmi)
अणु
	mutex_lock(&hdmi->mutex);
	hdmi->mc_clkdis |= HDMI_MC_CLKDIS_CECCLK_DISABLE;
	hdmi_ग_लिखोb(hdmi, hdmi->mc_clkdis, HDMI_MC_CLKDIS);
	mutex_unlock(&hdmi->mutex);
पूर्ण

अटल स्थिर काष्ठा dw_hdmi_cec_ops dw_hdmi_cec_ops = अणु
	.ग_लिखो = hdmi_ग_लिखोb,
	.पढ़ो = hdmi_पढ़ोb,
	.enable = dw_hdmi_cec_enable,
	.disable = dw_hdmi_cec_disable,
पूर्ण;

अटल स्थिर काष्ठा regmap_config hdmi_regmap_8bit_config = अणु
	.reg_bits	= 32,
	.val_bits	= 8,
	.reg_stride	= 1,
	.max_रेजिस्टर	= HDMI_I2CM_FS_SCL_LCNT_0_ADDR,
पूर्ण;

अटल स्थिर काष्ठा regmap_config hdmi_regmap_32bit_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= HDMI_I2CM_FS_SCL_LCNT_0_ADDR << 2,
पूर्ण;

अटल व्योम dw_hdmi_init_hw(काष्ठा dw_hdmi *hdmi)
अणु
	initialize_hdmi_ih_mutes(hdmi);

	/*
	 * Reset HDMI DDC I2C master controller and mute I2CM पूर्णांकerrupts.
	 * Even अगर we are using a separate i2c adapter करोing this करोesn't
	 * hurt.
	 */
	dw_hdmi_i2c_init(hdmi);

	अगर (hdmi->phy.ops->setup_hpd)
		hdmi->phy.ops->setup_hpd(hdmi, hdmi->phy.data);
पूर्ण

/* -----------------------------------------------------------------------------
 * Probe/हटाओ API, used from platक्रमms based on the DRM bridge API.
 */
काष्ठा dw_hdmi *dw_hdmi_probe(काष्ठा platक्रमm_device *pdev,
			      स्थिर काष्ठा dw_hdmi_plat_data *plat_data)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा platक्रमm_device_info pdevinfo;
	काष्ठा device_node *ddc_node;
	काष्ठा dw_hdmi_cec_data cec;
	काष्ठा dw_hdmi *hdmi;
	काष्ठा resource *iores = शून्य;
	पूर्णांक irq;
	पूर्णांक ret;
	u32 val = 1;
	u8 prod_id0;
	u8 prod_id1;
	u8 config0;
	u8 config3;

	hdmi = devm_kzalloc(dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi)
		वापस ERR_PTR(-ENOMEM);

	hdmi->plat_data = plat_data;
	hdmi->dev = dev;
	hdmi->sample_rate = 48000;
	hdmi->disabled = true;
	hdmi->rxsense = true;
	hdmi->phy_mask = (u8)~(HDMI_PHY_HPD | HDMI_PHY_RX_SENSE);
	hdmi->mc_clkdis = 0x7f;
	hdmi->last_connector_result = connector_status_disconnected;

	mutex_init(&hdmi->mutex);
	mutex_init(&hdmi->audio_mutex);
	mutex_init(&hdmi->cec_notअगरier_mutex);
	spin_lock_init(&hdmi->audio_lock);

	ddc_node = of_parse_phandle(np, "ddc-i2c-bus", 0);
	अगर (ddc_node) अणु
		hdmi->ddc = of_get_i2c_adapter_by_node(ddc_node);
		of_node_put(ddc_node);
		अगर (!hdmi->ddc) अणु
			dev_dbg(hdmi->dev, "failed to read ddc node\n");
			वापस ERR_PTR(-EPROBE_DEFER);
		पूर्ण

	पूर्ण अन्यथा अणु
		dev_dbg(hdmi->dev, "no ddc property found\n");
	पूर्ण

	अगर (!plat_data->regm) अणु
		स्थिर काष्ठा regmap_config *reg_config;

		of_property_पढ़ो_u32(np, "reg-io-width", &val);
		चयन (val) अणु
		हाल 4:
			reg_config = &hdmi_regmap_32bit_config;
			hdmi->reg_shअगरt = 2;
			अवरोध;
		हाल 1:
			reg_config = &hdmi_regmap_8bit_config;
			अवरोध;
		शेष:
			dev_err(dev, "reg-io-width must be 1 or 4\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		iores = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		hdmi->regs = devm_ioremap_resource(dev, iores);
		अगर (IS_ERR(hdmi->regs)) अणु
			ret = PTR_ERR(hdmi->regs);
			जाओ err_res;
		पूर्ण

		hdmi->regm = devm_regmap_init_mmio(dev, hdmi->regs, reg_config);
		अगर (IS_ERR(hdmi->regm)) अणु
			dev_err(dev, "Failed to configure regmap\n");
			ret = PTR_ERR(hdmi->regm);
			जाओ err_res;
		पूर्ण
	पूर्ण अन्यथा अणु
		hdmi->regm = plat_data->regm;
	पूर्ण

	hdmi->isfr_clk = devm_clk_get(hdmi->dev, "isfr");
	अगर (IS_ERR(hdmi->isfr_clk)) अणु
		ret = PTR_ERR(hdmi->isfr_clk);
		dev_err(hdmi->dev, "Unable to get HDMI isfr clk: %d\n", ret);
		जाओ err_res;
	पूर्ण

	ret = clk_prepare_enable(hdmi->isfr_clk);
	अगर (ret) अणु
		dev_err(hdmi->dev, "Cannot enable HDMI isfr clock: %d\n", ret);
		जाओ err_res;
	पूर्ण

	hdmi->iahb_clk = devm_clk_get(hdmi->dev, "iahb");
	अगर (IS_ERR(hdmi->iahb_clk)) अणु
		ret = PTR_ERR(hdmi->iahb_clk);
		dev_err(hdmi->dev, "Unable to get HDMI iahb clk: %d\n", ret);
		जाओ err_isfr;
	पूर्ण

	ret = clk_prepare_enable(hdmi->iahb_clk);
	अगर (ret) अणु
		dev_err(hdmi->dev, "Cannot enable HDMI iahb clock: %d\n", ret);
		जाओ err_isfr;
	पूर्ण

	hdmi->cec_clk = devm_clk_get(hdmi->dev, "cec");
	अगर (PTR_ERR(hdmi->cec_clk) == -ENOENT) अणु
		hdmi->cec_clk = शून्य;
	पूर्ण अन्यथा अगर (IS_ERR(hdmi->cec_clk)) अणु
		ret = PTR_ERR(hdmi->cec_clk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(hdmi->dev, "Cannot get HDMI cec clock: %d\n",
				ret);

		hdmi->cec_clk = शून्य;
		जाओ err_iahb;
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(hdmi->cec_clk);
		अगर (ret) अणु
			dev_err(hdmi->dev, "Cannot enable HDMI cec clock: %d\n",
				ret);
			जाओ err_iahb;
		पूर्ण
	पूर्ण

	/* Product and revision IDs */
	hdmi->version = (hdmi_पढ़ोb(hdmi, HDMI_DESIGN_ID) << 8)
		      | (hdmi_पढ़ोb(hdmi, HDMI_REVISION_ID) << 0);
	prod_id0 = hdmi_पढ़ोb(hdmi, HDMI_PRODUCT_ID0);
	prod_id1 = hdmi_पढ़ोb(hdmi, HDMI_PRODUCT_ID1);

	अगर (prod_id0 != HDMI_PRODUCT_ID0_HDMI_TX ||
	    (prod_id1 & ~HDMI_PRODUCT_ID1_HDCP) != HDMI_PRODUCT_ID1_HDMI_TX) अणु
		dev_err(dev, "Unsupported HDMI controller (%04x:%02x:%02x)\n",
			hdmi->version, prod_id0, prod_id1);
		ret = -ENODEV;
		जाओ err_iahb;
	पूर्ण

	ret = dw_hdmi_detect_phy(hdmi);
	अगर (ret < 0)
		जाओ err_iahb;

	dev_info(dev, "Detected HDMI TX controller v%x.%03x %s HDCP (%s)\n",
		 hdmi->version >> 12, hdmi->version & 0xfff,
		 prod_id1 & HDMI_PRODUCT_ID1_HDCP ? "with" : "without",
		 hdmi->phy.name);

	dw_hdmi_init_hw(hdmi);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ err_iahb;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, irq, dw_hdmi_hardirq,
					dw_hdmi_irq, IRQF_SHARED,
					dev_name(dev), hdmi);
	अगर (ret)
		जाओ err_iahb;

	/*
	 * To prevent overflows in HDMI_IH_FC_STAT2, set the clk regenerator
	 * N and cts values beक्रमe enabling phy
	 */
	hdmi_init_clk_regenerator(hdmi);

	/* If DDC bus is not specअगरied, try to रेजिस्टर HDMI I2C bus */
	अगर (!hdmi->ddc) अणु
		/* Look क्रम (optional) stuff related to unwedging */
		hdmi->pinctrl = devm_pinctrl_get(dev);
		अगर (!IS_ERR(hdmi->pinctrl)) अणु
			hdmi->unwedge_state =
				pinctrl_lookup_state(hdmi->pinctrl, "unwedge");
			hdmi->शेष_state =
				pinctrl_lookup_state(hdmi->pinctrl, "default");

			अगर (IS_ERR(hdmi->शेष_state) ||
			    IS_ERR(hdmi->unwedge_state)) अणु
				अगर (!IS_ERR(hdmi->unwedge_state))
					dev_warn(dev,
						 "Unwedge requires default pinctrl\n");
				hdmi->शेष_state = शून्य;
				hdmi->unwedge_state = शून्य;
			पूर्ण
		पूर्ण

		hdmi->ddc = dw_hdmi_i2c_adapter(hdmi);
		अगर (IS_ERR(hdmi->ddc))
			hdmi->ddc = शून्य;
	पूर्ण

	hdmi->bridge.driver_निजी = hdmi;
	hdmi->bridge.funcs = &dw_hdmi_bridge_funcs;
	hdmi->bridge.ops = DRM_BRIDGE_OP_DETECT | DRM_BRIDGE_OP_EDID
			 | DRM_BRIDGE_OP_HPD;
#अगर_घोषित CONFIG_OF
	hdmi->bridge.of_node = pdev->dev.of_node;
#पूर्ण_अगर

	स_रखो(&pdevinfo, 0, माप(pdevinfo));
	pdevinfo.parent = dev;
	pdevinfo.id = PLATFORM_DEVID_AUTO;

	config0 = hdmi_पढ़ोb(hdmi, HDMI_CONFIG0_ID);
	config3 = hdmi_पढ़ोb(hdmi, HDMI_CONFIG3_ID);

	अगर (iores && config3 & HDMI_CONFIG3_AHBAUDDMA) अणु
		काष्ठा dw_hdmi_audio_data audio;

		audio.phys = iores->start;
		audio.base = hdmi->regs;
		audio.irq = irq;
		audपन.सdmi = hdmi;
		audio.eld = hdmi->connector.eld;
		hdmi->enable_audio = dw_hdmi_ahb_audio_enable;
		hdmi->disable_audio = dw_hdmi_ahb_audio_disable;

		pdevinfo.name = "dw-hdmi-ahb-audio";
		pdevinfo.data = &audio;
		pdevinfo.size_data = माप(audio);
		pdevinfo.dma_mask = DMA_BIT_MASK(32);
		hdmi->audio = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
	पूर्ण अन्यथा अगर (config0 & HDMI_CONFIG0_I2S) अणु
		काष्ठा dw_hdmi_i2s_audio_data audio;

		audपन.सdmi	= hdmi;
		audio.eld	= hdmi->connector.eld;
		audio.ग_लिखो	= hdmi_ग_लिखोb;
		audio.पढ़ो	= hdmi_पढ़ोb;
		hdmi->enable_audio = dw_hdmi_i2s_audio_enable;
		hdmi->disable_audio = dw_hdmi_i2s_audio_disable;

		pdevinfo.name = "dw-hdmi-i2s-audio";
		pdevinfo.data = &audio;
		pdevinfo.size_data = माप(audio);
		pdevinfo.dma_mask = DMA_BIT_MASK(32);
		hdmi->audio = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
	पूर्ण

	अगर (config0 & HDMI_CONFIG0_CEC) अणु
		cec.hdmi = hdmi;
		cec.ops = &dw_hdmi_cec_ops;
		cec.irq = irq;

		pdevinfo.name = "dw-hdmi-cec";
		pdevinfo.data = &cec;
		pdevinfo.size_data = माप(cec);
		pdevinfo.dma_mask = 0;

		hdmi->cec = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
	पूर्ण

	drm_bridge_add(&hdmi->bridge);

	वापस hdmi;

err_iahb:
	clk_disable_unprepare(hdmi->iahb_clk);
	clk_disable_unprepare(hdmi->cec_clk);
err_isfr:
	clk_disable_unprepare(hdmi->isfr_clk);
err_res:
	i2c_put_adapter(hdmi->ddc);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_probe);

व्योम dw_hdmi_हटाओ(काष्ठा dw_hdmi *hdmi)
अणु
	drm_bridge_हटाओ(&hdmi->bridge);

	अगर (hdmi->audio && !IS_ERR(hdmi->audio))
		platक्रमm_device_unरेजिस्टर(hdmi->audio);
	अगर (!IS_ERR(hdmi->cec))
		platक्रमm_device_unरेजिस्टर(hdmi->cec);

	/* Disable all पूर्णांकerrupts */
	hdmi_ग_लिखोb(hdmi, ~0, HDMI_IH_MUTE_PHY_STAT0);

	clk_disable_unprepare(hdmi->iahb_clk);
	clk_disable_unprepare(hdmi->isfr_clk);
	clk_disable_unprepare(hdmi->cec_clk);

	अगर (hdmi->i2c)
		i2c_del_adapter(&hdmi->i2c->adap);
	अन्यथा
		i2c_put_adapter(hdmi->ddc);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_हटाओ);

/* -----------------------------------------------------------------------------
 * Bind/unbind API, used from platक्रमms based on the component framework.
 */
काष्ठा dw_hdmi *dw_hdmi_bind(काष्ठा platक्रमm_device *pdev,
			     काष्ठा drm_encoder *encoder,
			     स्थिर काष्ठा dw_hdmi_plat_data *plat_data)
अणु
	काष्ठा dw_hdmi *hdmi;
	पूर्णांक ret;

	hdmi = dw_hdmi_probe(pdev, plat_data);
	अगर (IS_ERR(hdmi))
		वापस hdmi;

	ret = drm_bridge_attach(encoder, &hdmi->bridge, शून्य, 0);
	अगर (ret) अणु
		dw_hdmi_हटाओ(hdmi);
		DRM_ERROR("Failed to initialize bridge with drm\n");
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hdmi;
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_bind);

व्योम dw_hdmi_unbind(काष्ठा dw_hdmi *hdmi)
अणु
	dw_hdmi_हटाओ(hdmi);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_unbind);

व्योम dw_hdmi_resume(काष्ठा dw_hdmi *hdmi)
अणु
	dw_hdmi_init_hw(hdmi);
पूर्ण
EXPORT_SYMBOL_GPL(dw_hdmi_resume);

MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_AUTHOR("Andy Yan <andy.yan@rock-chips.com>");
MODULE_AUTHOR("Yakir Yang <ykk@rock-chips.com>");
MODULE_AUTHOR("Vladimir Zapolskiy <vladimir_zapolskiy@mentor.com>");
MODULE_DESCRIPTION("DW HDMI transmitter driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:dw-hdmi");
