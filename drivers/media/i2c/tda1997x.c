<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Gateworks Corporation
 */
#समावेश <linux/delay.h>
#समावेश <linux/hdmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/types.h>
#समावेश <linux/v4l2-dv-timings.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-dv-timings.h>
#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/i2c/tda1997x.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश <dt-bindings/media/tda1997x.h>

#समावेश "tda1997x_regs.h"

#घोषणा TDA1997X_MBUS_CODES	5

/* debug level */
अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "debug level (0-2)");

/* Audio क्रमmats */
अटल स्थिर अक्षर * स्थिर audtype_names[] = अणु
	"PCM",			/* PCM Samples */
	"HBR",			/* High Bit Rate Audio */
	"OBA",			/* One-Bit Audio */
	"DST"			/* Direct Stream Transfer */
पूर्ण;

/* Audio output port क्रमmats */
क्रमागत audfmt_types अणु
	AUDFMT_TYPE_DISABLED = 0,
	AUDFMT_TYPE_I2S,
	AUDFMT_TYPE_SPDIF,
पूर्ण;
अटल स्थिर अक्षर * स्थिर audfmt_names[] = अणु
	"Disabled",
	"I2S",
	"SPDIF",
पूर्ण;

/* Video input क्रमmats */
अटल स्थिर अक्षर * स्थिर hdmi_colorspace_names[] = अणु
	"RGB", "YUV422", "YUV444", "YUV420", "", "", "", "",
पूर्ण;
अटल स्थिर अक्षर * स्थिर hdmi_colorimetry_names[] = अणु
	"", "ITU601", "ITU709", "Extended",
पूर्ण;
अटल स्थिर अक्षर * स्थिर v4l2_quantization_names[] = अणु
	"Default",
	"Full Range (0-255)",
	"Limited Range (16-235)",
पूर्ण;

/* Video output port क्रमmats */
अटल स्थिर अक्षर * स्थिर vidfmt_names[] = अणु
	"RGB444/YUV444",	/* RGB/YUV444 16bit data bus, 8bpp */
	"YUV422 semi-planar",	/* YUV422 16bit data base, 8bpp */
	"YUV422 CCIR656",	/* BT656 (YUV 8bpp 2 घड़ी per pixel) */
	"Invalid",
पूर्ण;

/*
 * Colorspace conversion matrices
 */
काष्ठा color_matrix_coefs अणु
	स्थिर अक्षर *name;
	/* Input offsets */
	s16 offपूर्णांक1;
	s16 offपूर्णांक2;
	s16 offपूर्णांक3;
	/* Coeficients */
	s16 p11coef;
	s16 p12coef;
	s16 p13coef;
	s16 p21coef;
	s16 p22coef;
	s16 p23coef;
	s16 p31coef;
	s16 p32coef;
	s16 p33coef;
	/* Output offsets */
	s16 offout1;
	s16 offout2;
	s16 offout3;
पूर्ण;

क्रमागत अणु
	ITU709_RGBFULL,
	ITU601_RGBFULL,
	RGBLIMITED_RGBFULL,
	RGBLIMITED_ITU601,
	RGBLIMITED_ITU709,
	RGBFULL_ITU601,
	RGBFULL_ITU709,
पूर्ण;

/* NB: 4096 is 1.0 using fixed poपूर्णांक numbers */
अटल स्थिर काष्ठा color_matrix_coefs conv_matrix[] = अणु
	अणु
		"YUV709 -> RGB full",
		 -256, -2048,  -2048,
		 4769, -2183,   -873,
		 4769,  7343,      0,
		 4769,     0,   8652,
		    0,     0,      0,
	पूर्ण,
	अणु
		"YUV601 -> RGB full",
		 -256, -2048,  -2048,
		 4769, -3330,  -1602,
		 4769,  6538,      0,
		 4769,     0,   8264,
		  256,   256,    256,
	पूर्ण,
	अणु
		"RGB limited -> RGB full",
		 -256,  -256,   -256,
		    0,  4769,      0,
		    0,     0,   4769,
		 4769,     0,      0,
		    0,     0,      0,
	पूर्ण,
	अणु
		"RGB limited -> ITU601",
		 -256,  -256,   -256,
		 2404,  1225,    467,
		-1754,  2095,   -341,
		-1388,  -707,   2095,
		  256,  2048,   2048,
	पूर्ण,
	अणु
		"RGB limited -> ITU709",
		 -256,  -256,   -256,
		 2918,   867,    295,
		-1894,  2087,   -190,
		-1607,  -477,   2087,
		  256,  2048,   2048,
	पूर्ण,
	अणु
		"RGB full -> ITU601",
		    0,     0,      0,
		 2065,  1052,    401,
		-1506,  1799,   -293,
		-1192,  -607,   1799,
		  256,  2048,   2048,
	पूर्ण,
	अणु
		"RGB full -> ITU709",
		    0,     0,      0,
		 2506,   745,    253,
		-1627,  1792,   -163,
		-1380,  -410,   1792,
		  256,  2048,   2048,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा v4l2_dv_timings_cap tda1997x_dv_timings_cap = अणु
	.type = V4L2_DV_BT_656_1120,
	/* keep this initialization क्रम compatibility with GCC < 4.4.6 */
	.reserved = अणु 0 पूर्ण,

	V4L2_INIT_BT_TIMINGS(
		640, 1920,			/* min/max width */
		350, 1200,			/* min/max height */
		13000000, 165000000,		/* min/max pixelघड़ी */
		/* standards */
		V4L2_DV_BT_STD_CEA861 | V4L2_DV_BT_STD_DMT |
			V4L2_DV_BT_STD_GTF | V4L2_DV_BT_STD_CVT,
		/* capabilities */
		V4L2_DV_BT_CAP_INTERLACED | V4L2_DV_BT_CAP_PROGRESSIVE |
			V4L2_DV_BT_CAP_REDUCED_BLANKING |
			V4L2_DV_BT_CAP_CUSTOM
	)
पूर्ण;

/* regulator supplies */
अटल स्थिर अक्षर * स्थिर tda1997x_supply_name[] = अणु
	"DOVDD", /* Digital I/O supply */
	"DVDD",  /* Digital Core supply */
	"AVDD",  /* Analog supply */
पूर्ण;

#घोषणा TDA1997X_NUM_SUPPLIES ARRAY_SIZE(tda1997x_supply_name)

क्रमागत tda1997x_type अणु
	TDA19971,
	TDA19973,
पूर्ण;

क्रमागत tda1997x_hdmi_pads अणु
	TDA1997X_PAD_SOURCE,
	TDA1997X_NUM_PADS,
पूर्ण;

काष्ठा tda1997x_chip_info अणु
	क्रमागत tda1997x_type type;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा tda1997x_state अणु
	स्थिर काष्ठा tda1997x_chip_info *info;
	काष्ठा tda1997x_platक्रमm_data pdata;
	काष्ठा i2c_client *client;
	काष्ठा i2c_client *client_cec;
	काष्ठा v4l2_subdev sd;
	काष्ठा regulator_bulk_data supplies[TDA1997X_NUM_SUPPLIES];
	काष्ठा media_pad pads[TDA1997X_NUM_PADS];
	काष्ठा mutex lock;
	काष्ठा mutex page_lock;
	अक्षर page;

	/* detected info from chip */
	पूर्णांक chip_revision;
	अक्षर port_30bit;
	अक्षर output_2p5;
	अक्षर पंचांगdsb_clk;
	अक्षर पंचांगdsb_soc;

	/* status info */
	अक्षर hdmi_status;
	अक्षर mptrw_in_progress;
	अक्षर activity_status;
	अक्षर input_detect[2];

	/* video */
	काष्ठा hdmi_avi_infoframe avi_infoframe;
	काष्ठा v4l2_hdmi_colorimetry colorimetry;
	u32 rgb_quantization_range;
	काष्ठा v4l2_dv_timings timings;
	पूर्णांक fps;
	स्थिर काष्ठा color_matrix_coefs *conv;
	u32 mbus_codes[TDA1997X_MBUS_CODES];	/* available modes */
	u32 mbus_code;		/* current mode */
	u8 vid_fmt;

	/* controls */
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl *detect_tx_5v_ctrl;
	काष्ठा v4l2_ctrl *rgb_quantization_range_ctrl;

	/* audio */
	u8  audio_ch_alloc;
	पूर्णांक audio_samplerate;
	पूर्णांक audio_channels;
	पूर्णांक audio_samplesize;
	पूर्णांक audio_type;
	काष्ठा mutex audio_lock;
	काष्ठा snd_pcm_substream *audio_stream;

	/* EDID */
	काष्ठा अणु
		u8 edid[256];
		u32 present;
		अचिन्हित पूर्णांक blocks;
	पूर्ण edid;
	काष्ठा delayed_work delayed_work_enable_hpd;
पूर्ण;

अटल स्थिर काष्ठा v4l2_event tda1997x_ev_fmt = अणु
	.type = V4L2_EVENT_SOURCE_CHANGE,
	.u.src_change.changes = V4L2_EVENT_SRC_CH_RESOLUTION,
पूर्ण;

अटल स्थिर काष्ठा tda1997x_chip_info tda1997x_chip_info[] = अणु
	[TDA19971] = अणु
		.type = TDA19971,
		.name = "tda19971",
	पूर्ण,
	[TDA19973] = अणु
		.type = TDA19973,
		.name = "tda19973",
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा tda1997x_state *to_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा tda1997x_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा tda1997x_state, hdl)->sd;
पूर्ण

अटल पूर्णांक tda1997x_cec_पढ़ो(काष्ठा v4l2_subdev *sd, u8 reg)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	पूर्णांक val;

	val = i2c_smbus_पढ़ो_byte_data(state->client_cec, reg);
	अगर (val < 0) अणु
		v4l_err(state->client, "read reg error: reg=%2x\n", reg);
		val = -1;
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक tda1997x_cec_ग_लिखो(काष्ठा v4l2_subdev *sd, u8 reg, u8 val)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	पूर्णांक ret = 0;

	ret = i2c_smbus_ग_लिखो_byte_data(state->client_cec, reg, val);
	अगर (ret < 0) अणु
		v4l_err(state->client, "write reg error:reg=%2x,val=%2x\n",
			reg, val);
		ret = -1;
	पूर्ण

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * I2C transfer
 */

अटल पूर्णांक tda1997x_setpage(काष्ठा v4l2_subdev *sd, u8 page)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	पूर्णांक ret;

	अगर (state->page != page) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(state->client,
			REG_CURPAGE_00H, page);
		अगर (ret < 0) अणु
			v4l_err(state->client,
				"write reg error:reg=%2x,val=%2x\n",
				REG_CURPAGE_00H, page);
			वापस ret;
		पूर्ण
		state->page = page;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक io_पढ़ो(काष्ठा v4l2_subdev *sd, u16 reg)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	पूर्णांक val;

	mutex_lock(&state->page_lock);
	अगर (tda1997x_setpage(sd, reg >> 8)) अणु
		val = -1;
		जाओ out;
	पूर्ण

	val = i2c_smbus_पढ़ो_byte_data(state->client, reg&0xff);
	अगर (val < 0) अणु
		v4l_err(state->client, "read reg error: reg=%2x\n", reg & 0xff);
		val = -1;
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&state->page_lock);
	वापस val;
पूर्ण

अटल अंतरभूत दीर्घ io_पढ़ो16(काष्ठा v4l2_subdev *sd, u16 reg)
अणु
	पूर्णांक val;
	दीर्घ lval = 0;

	val = io_पढ़ो(sd, reg);
	अगर (val < 0)
		वापस val;
	lval |= (val << 8);
	val = io_पढ़ो(sd, reg + 1);
	अगर (val < 0)
		वापस val;
	lval |= val;

	वापस lval;
पूर्ण

अटल अंतरभूत दीर्घ io_पढ़ो24(काष्ठा v4l2_subdev *sd, u16 reg)
अणु
	पूर्णांक val;
	दीर्घ lval = 0;

	val = io_पढ़ो(sd, reg);
	अगर (val < 0)
		वापस val;
	lval |= (val << 16);
	val = io_पढ़ो(sd, reg + 1);
	अगर (val < 0)
		वापस val;
	lval |= (val << 8);
	val = io_पढ़ो(sd, reg + 2);
	अगर (val < 0)
		वापस val;
	lval |= val;

	वापस lval;
पूर्ण

अटल अचिन्हित पूर्णांक io_पढ़ोn(काष्ठा v4l2_subdev *sd, u16 reg, u8 len, u8 *data)
अणु
	पूर्णांक i;
	पूर्णांक sz = 0;
	पूर्णांक val;

	क्रम (i = 0; i < len; i++) अणु
		val = io_पढ़ो(sd, reg + i);
		अगर (val < 0)
			अवरोध;
		data[i] = val;
		sz++;
	पूर्ण

	वापस sz;
पूर्ण

अटल पूर्णांक io_ग_लिखो(काष्ठा v4l2_subdev *sd, u16 reg, u8 val)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	s32 ret = 0;

	mutex_lock(&state->page_lock);
	अगर (tda1997x_setpage(sd, reg >> 8)) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(state->client, reg & 0xff, val);
	अगर (ret < 0) अणु
		v4l_err(state->client, "write reg error:reg=%2x,val=%2x\n",
			reg&0xff, val);
		ret = -1;
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&state->page_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक io_ग_लिखो16(काष्ठा v4l2_subdev *sd, u16 reg, u16 val)
अणु
	पूर्णांक ret;

	ret = io_ग_लिखो(sd, reg, (val >> 8) & 0xff);
	अगर (ret < 0)
		वापस ret;
	ret = io_ग_लिखो(sd, reg + 1, val & 0xff);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक io_ग_लिखो24(काष्ठा v4l2_subdev *sd, u16 reg, u32 val)
अणु
	पूर्णांक ret;

	ret = io_ग_लिखो(sd, reg, (val >> 16) & 0xff);
	अगर (ret < 0)
		वापस ret;
	ret = io_ग_लिखो(sd, reg + 1, (val >> 8) & 0xff);
	अगर (ret < 0)
		वापस ret;
	ret = io_ग_लिखो(sd, reg + 2, val & 0xff);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Hotplug
 */

क्रमागत hpd_mode अणु
	HPD_LOW_BP,	/* HPD low and pulse of at least 100ms */
	HPD_LOW_OTHER,	/* HPD low and pulse of at least 100ms */
	HPD_HIGH_BP,	/* HIGH */
	HPD_HIGH_OTHER,
	HPD_PULSE,	/* HPD low pulse */
पूर्ण;

/* manual HPD (Hot Plug Detect) control */
अटल पूर्णांक tda1997x_manual_hpd(काष्ठा v4l2_subdev *sd, क्रमागत hpd_mode mode)
अणु
	u8 hpd_स्वतः, hpd_pwr, hpd_man;

	hpd_स्वतः = io_पढ़ो(sd, REG_HPD_AUTO_CTRL);
	hpd_pwr = io_पढ़ो(sd, REG_HPD_POWER);
	hpd_man = io_पढ़ो(sd, REG_HPD_MAN_CTRL);

	/* mask out unused bits */
	hpd_man &= (HPD_MAN_CTRL_HPD_PULSE |
		    HPD_MAN_CTRL_5VEN |
		    HPD_MAN_CTRL_HPD_B |
		    HPD_MAN_CTRL_HPD_A);

	चयन (mode) अणु
	/* HPD low and pulse of at least 100ms */
	हाल HPD_LOW_BP:
		/* hpd_bp=0 */
		hpd_pwr &= ~HPD_POWER_BP_MASK;
		/* disable HPD_A and HPD_B */
		hpd_man &= ~(HPD_MAN_CTRL_HPD_A | HPD_MAN_CTRL_HPD_B);
		io_ग_लिखो(sd, REG_HPD_POWER, hpd_pwr);
		io_ग_लिखो(sd, REG_HPD_MAN_CTRL, hpd_man);
		अवरोध;
	/* HPD high */
	हाल HPD_HIGH_BP:
		/* hpd_bp=1 */
		hpd_pwr &= ~HPD_POWER_BP_MASK;
		hpd_pwr |= 1 << HPD_POWER_BP_SHIFT;
		io_ग_लिखो(sd, REG_HPD_POWER, hpd_pwr);
		अवरोध;
	/* HPD low and pulse of at least 100ms */
	हाल HPD_LOW_OTHER:
		/* disable HPD_A and HPD_B */
		hpd_man &= ~(HPD_MAN_CTRL_HPD_A | HPD_MAN_CTRL_HPD_B);
		/* hp_other=0 */
		hpd_स्वतः &= ~HPD_AUTO_HP_OTHER;
		io_ग_लिखो(sd, REG_HPD_AUTO_CTRL, hpd_स्वतः);
		io_ग_लिखो(sd, REG_HPD_MAN_CTRL, hpd_man);
		अवरोध;
	/* HPD high */
	हाल HPD_HIGH_OTHER:
		hpd_स्वतः |= HPD_AUTO_HP_OTHER;
		io_ग_लिखो(sd, REG_HPD_AUTO_CTRL, hpd_स्वतः);
		अवरोध;
	/* HPD low pulse */
	हाल HPD_PULSE:
		/* disable HPD_A and HPD_B */
		hpd_man &= ~(HPD_MAN_CTRL_HPD_A | HPD_MAN_CTRL_HPD_B);
		io_ग_लिखो(sd, REG_HPD_MAN_CTRL, hpd_man);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tda1997x_delayed_work_enable_hpd(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा tda1997x_state *state = container_of(dwork,
						    काष्ठा tda1997x_state,
						    delayed_work_enable_hpd);
	काष्ठा v4l2_subdev *sd = &state->sd;

	v4l2_dbg(2, debug, sd, "%s:\n", __func__);

	/* Set HPD high */
	tda1997x_manual_hpd(sd, HPD_HIGH_OTHER);
	tda1997x_manual_hpd(sd, HPD_HIGH_BP);

	state->edid.present = 1;
पूर्ण

अटल व्योम tda1997x_disable_edid(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s\n", __func__);
	cancel_delayed_work_sync(&state->delayed_work_enable_hpd);

	/* Set HPD low */
	tda1997x_manual_hpd(sd, HPD_LOW_BP);
पूर्ण

अटल व्योम tda1997x_enable_edid(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);

	v4l2_dbg(1, debug, sd, "%s\n", __func__);

	/* Enable hotplug after 100ms */
	schedule_delayed_work(&state->delayed_work_enable_hpd, HZ / 10);
पूर्ण

/* -----------------------------------------------------------------------------
 * Signal Control
 */

/*
 * configure vid_fmt based on mbus_code
 */
अटल पूर्णांक
tda1997x_setup_क्रमmat(काष्ठा tda1997x_state *state, u32 code)
अणु
	v4l_dbg(1, debug, state->client, "%s code=0x%x\n", __func__, code);
	चयन (code) अणु
	हाल MEDIA_BUS_FMT_RGB121212_1X36:
	हाल MEDIA_BUS_FMT_RGB888_1X24:
	हाल MEDIA_BUS_FMT_YUV12_1X36:
	हाल MEDIA_BUS_FMT_YUV8_1X24:
		state->vid_fmt = OF_FMT_444;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY12_1X24:
	हाल MEDIA_BUS_FMT_UYVY10_1X20:
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
		state->vid_fmt = OF_FMT_422_SMPT;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY12_2X12:
	हाल MEDIA_BUS_FMT_UYVY10_2X10:
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		state->vid_fmt = OF_FMT_422_CCIR;
		अवरोध;
	शेष:
		v4l_err(state->client, "incompatible format (0x%x)\n", code);
		वापस -EINVAL;
	पूर्ण
	v4l_dbg(1, debug, state->client, "%s code=0x%x fmt=%s\n", __func__,
		code, vidfmt_names[state->vid_fmt]);
	state->mbus_code = code;

	वापस 0;
पूर्ण

/*
 * The color conversion matrix will convert between the colorimetry of the
 * HDMI input to the desired output क्रमmat RGB|YUV. RGB output is to be
 * full-range and YUV is to be limited range.
 *
 * RGB full-range uses values from 0 to 255 which is recommended on a monitor
 * and RGB Limited uses values from 16 to 236 (16=black, 235=white) which is
 * typically recommended on a TV.
 */
अटल व्योम
tda1997x_configure_csc(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	काष्ठा hdmi_avi_infoframe *avi = &state->avi_infoframe;
	काष्ठा v4l2_hdmi_colorimetry *c = &state->colorimetry;
	/* Blanking code values depend on output colorspace (RGB or YUV) */
	काष्ठा blanking_codes अणु
		s16 code_gy;
		s16 code_bu;
		s16 code_rv;
	पूर्ण;
	अटल स्थिर काष्ठा blanking_codes rgb_blanking = अणु 64, 64, 64 पूर्ण;
	अटल स्थिर काष्ठा blanking_codes yuv_blanking = अणु 64, 512, 512 पूर्ण;
	स्थिर काष्ठा blanking_codes *blanking_codes = शून्य;
	u8 reg;

	v4l_dbg(1, debug, state->client, "input:%s quant:%s output:%s\n",
		hdmi_colorspace_names[avi->colorspace],
		v4l2_quantization_names[c->quantization],
		vidfmt_names[state->vid_fmt]);
	state->conv = शून्य;
	चयन (state->vid_fmt) अणु
	/* RGB output */
	हाल OF_FMT_444:
		blanking_codes = &rgb_blanking;
		अगर (c->colorspace == V4L2_COLORSPACE_SRGB) अणु
			अगर (c->quantization == V4L2_QUANTIZATION_LIM_RANGE)
				state->conv = &conv_matrix[RGBLIMITED_RGBFULL];
		पूर्ण अन्यथा अणु
			अगर (c->colorspace == V4L2_COLORSPACE_REC709)
				state->conv = &conv_matrix[ITU709_RGBFULL];
			अन्यथा अगर (c->colorspace == V4L2_COLORSPACE_SMPTE170M)
				state->conv = &conv_matrix[ITU601_RGBFULL];
		पूर्ण
		अवरोध;

	/* YUV output */
	हाल OF_FMT_422_SMPT: /* semi-planar */
	हाल OF_FMT_422_CCIR: /* CCIR656 */
		blanking_codes = &yuv_blanking;
		अगर ((c->colorspace == V4L2_COLORSPACE_SRGB) &&
		    (c->quantization == V4L2_QUANTIZATION_FULL_RANGE)) अणु
			अगर (state->timings.bt.height <= 576)
				state->conv = &conv_matrix[RGBFULL_ITU601];
			अन्यथा
				state->conv = &conv_matrix[RGBFULL_ITU709];
		पूर्ण अन्यथा अगर ((c->colorspace == V4L2_COLORSPACE_SRGB) &&
			   (c->quantization == V4L2_QUANTIZATION_LIM_RANGE)) अणु
			अगर (state->timings.bt.height <= 576)
				state->conv = &conv_matrix[RGBLIMITED_ITU601];
			अन्यथा
				state->conv = &conv_matrix[RGBLIMITED_ITU709];
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (state->conv) अणु
		v4l_dbg(1, debug, state->client, "%s\n",
			state->conv->name);
		/* enable matrix conversion */
		reg = io_पढ़ो(sd, REG_VDP_CTRL);
		reg &= ~VDP_CTRL_MATRIX_BP;
		io_ग_लिखो(sd, REG_VDP_CTRL, reg);
		/* offset inमाला_दो */
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 0, state->conv->offपूर्णांक1);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 2, state->conv->offपूर्णांक2);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 4, state->conv->offपूर्णांक3);
		/* coefficients */
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 6, state->conv->p11coef);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 8, state->conv->p12coef);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 10, state->conv->p13coef);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 12, state->conv->p21coef);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 14, state->conv->p22coef);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 16, state->conv->p23coef);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 18, state->conv->p31coef);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 20, state->conv->p32coef);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 22, state->conv->p33coef);
		/* offset outमाला_दो */
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 24, state->conv->offout1);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 26, state->conv->offout2);
		io_ग_लिखो16(sd, REG_VDP_MATRIX + 28, state->conv->offout3);
	पूर्ण अन्यथा अणु
		/* disable matrix conversion */
		reg = io_पढ़ो(sd, REG_VDP_CTRL);
		reg |= VDP_CTRL_MATRIX_BP;
		io_ग_लिखो(sd, REG_VDP_CTRL, reg);
	पूर्ण

	/* SetBlankingCodes */
	अगर (blanking_codes) अणु
		io_ग_लिखो16(sd, REG_BLK_GY, blanking_codes->code_gy);
		io_ग_लिखो16(sd, REG_BLK_BU, blanking_codes->code_bu);
		io_ग_लिखो16(sd, REG_BLK_RV, blanking_codes->code_rv);
	पूर्ण
पूर्ण

/* Configure frame detection winकरोw and VHREF timing generator */
अटल व्योम
tda1997x_configure_vhref(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	स्थिर काष्ठा v4l2_bt_timings *bt = &state->timings.bt;
	पूर्णांक width, lines;
	u16 href_start, href_end;
	u16 vref_f1_start, vref_f2_start;
	u8 vref_f1_width, vref_f2_width;
	u8 field_polarity;
	u16 fieldref_f1_start, fieldref_f2_start;
	u8 reg;

	href_start = bt->hbackporch + bt->hsync + 1;
	href_end = href_start + bt->width;
	vref_f1_start = bt->height + bt->vbackporch + bt->vsync +
			bt->il_vbackporch + bt->il_vsync +
			bt->il_vfrontporch;
	vref_f1_width = bt->vbackporch + bt->vsync + bt->vfrontporch;
	vref_f2_start = 0;
	vref_f2_width = 0;
	fieldref_f1_start = 0;
	fieldref_f2_start = 0;
	अगर (bt->पूर्णांकerlaced) अणु
		vref_f2_start = (bt->height / 2) +
				(bt->il_vbackporch + bt->il_vsync - 1);
		vref_f2_width = bt->il_vbackporch + bt->il_vsync +
				bt->il_vfrontporch;
		fieldref_f2_start = vref_f2_start + bt->il_vfrontporch +
				    fieldref_f1_start;
	पूर्ण
	field_polarity = 0;

	width = V4L2_DV_BT_FRAME_WIDTH(bt);
	lines = V4L2_DV_BT_FRAME_HEIGHT(bt);

	/*
	 * Configure Frame Detection Winकरोw:
	 *  horiz area where the VHREF module consider a VSYNC a new frame
	 */
	io_ग_लिखो16(sd, REG_FDW_S, 0x2ef); /* start position */
	io_ग_लिखो16(sd, REG_FDW_E, 0x141); /* end position */

	/* Set Pixel And Line Counters */
	अगर (state->chip_revision == 0)
		io_ग_लिखो16(sd, REG_PXCNT_PR, 4);
	अन्यथा
		io_ग_लिखो16(sd, REG_PXCNT_PR, 1);
	io_ग_लिखो16(sd, REG_PXCNT_NPIX, width & MASK_VHREF);
	io_ग_लिखो16(sd, REG_LCNT_PR, 1);
	io_ग_लिखो16(sd, REG_LCNT_NLIN, lines & MASK_VHREF);

	/*
	 * Configure the VHRef timing generator responsible क्रम rebuilding all
	 * horiz and vert synch and ref संकेतs from its input allowing स्वतः
	 * detection algorithms and क्रमcing predefined modes (480i & 576i)
	 */
	reg = VHREF_STD_DET_OFF << VHREF_STD_DET_SHIFT;
	io_ग_लिखो(sd, REG_VHREF_CTRL, reg);

	/*
	 * Configure the VHRef timing values. In हाल the VHREF generator has
	 * been configured in manual mode, this will allow to manually set all
	 * horiz and vert ref values (non-active pixel areas) of the generator
	 * and allows setting the frame reference params.
	 */
	/* horizontal reference start/end */
	io_ग_लिखो16(sd, REG_HREF_S, href_start & MASK_VHREF);
	io_ग_लिखो16(sd, REG_HREF_E, href_end & MASK_VHREF);
	/* vertical reference f1 start/end */
	io_ग_लिखो16(sd, REG_VREF_F1_S, vref_f1_start & MASK_VHREF);
	io_ग_लिखो(sd, REG_VREF_F1_WIDTH, vref_f1_width);
	/* vertical reference f2 start/end */
	io_ग_लिखो16(sd, REG_VREF_F2_S, vref_f2_start & MASK_VHREF);
	io_ग_लिखो(sd, REG_VREF_F2_WIDTH, vref_f2_width);

	/* F1/F2 FREF, field polarity */
	reg = fieldref_f1_start & MASK_VHREF;
	reg |= field_polarity << 8;
	io_ग_लिखो16(sd, REG_FREF_F1_S, reg);
	reg = fieldref_f2_start & MASK_VHREF;
	io_ग_लिखो16(sd, REG_FREF_F2_S, reg);
पूर्ण

/* Configure Video Output port संकेतs */
अटल पूर्णांक
tda1997x_configure_viकरोut(काष्ठा tda1997x_state *state)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	काष्ठा tda1997x_platक्रमm_data *pdata = &state->pdata;
	u8 prefilter;
	u8 reg;

	/* Configure pixel घड़ी generator: delay, polarity, rate */
	reg = (state->vid_fmt == OF_FMT_422_CCIR) ?
	       PCLK_SEL_X2 : PCLK_SEL_X1;
	reg |= pdata->viकरोut_delay_pclk << PCLK_DELAY_SHIFT;
	reg |= pdata->viकरोut_inv_pclk << PCLK_INV_SHIFT;
	io_ग_लिखो(sd, REG_PCLK, reg);

	/* Configure pre-filter */
	prefilter = 0; /* filters off */
	/* YUV422 mode requires conversion */
	अगर ((state->vid_fmt == OF_FMT_422_SMPT) ||
	    (state->vid_fmt == OF_FMT_422_CCIR)) अणु
		/* 2/7 taps क्रम Rv and Bu */
		prefilter = FILTERS_CTRL_2_7TAP << FILTERS_CTRL_BU_SHIFT |
			    FILTERS_CTRL_2_7TAP << FILTERS_CTRL_RV_SHIFT;
	पूर्ण
	io_ग_लिखो(sd, REG_FILTERS_CTRL, prefilter);

	/* Configure video port */
	reg = state->vid_fmt & OF_FMT_MASK;
	अगर (state->vid_fmt == OF_FMT_422_CCIR)
		reg |= (OF_BLK | OF_TRC);
	reg |= OF_VP_ENABLE;
	io_ग_लिखो(sd, REG_OF, reg);

	/* Configure क्रमmatter and conversions */
	reg = io_पढ़ो(sd, REG_VDP_CTRL);
	/* pre-filter is needed unless (REG_FILTERS_CTRL == 0) */
	अगर (!prefilter)
		reg |= VDP_CTRL_PREFILTER_BP;
	अन्यथा
		reg &= ~VDP_CTRL_PREFILTER_BP;
	/* क्रमmatter is needed क्रम YUV422 and क्रम trc/blc codes */
	अगर (state->vid_fmt == OF_FMT_444)
		reg |= VDP_CTRL_FORMATTER_BP;
	/* क्रमmatter and compdel needed क्रम timing/blanking codes */
	अन्यथा
		reg &= ~(VDP_CTRL_FORMATTER_BP | VDP_CTRL_COMPDEL_BP);
	/* activate compdel क्रम small sync delays */
	अगर ((pdata->viकरोut_delay_vs < 4) || (pdata->viकरोut_delay_hs < 4))
		reg &= ~VDP_CTRL_COMPDEL_BP;
	io_ग_लिखो(sd, REG_VDP_CTRL, reg);

	/* Configure DE output संकेत: delay, polarity, and source */
	reg = pdata->viकरोut_delay_de << DE_FREF_DELAY_SHIFT |
	      pdata->viकरोut_inv_de << DE_FREF_INV_SHIFT |
	      pdata->viकरोut_sel_de << DE_FREF_SEL_SHIFT;
	io_ग_लिखो(sd, REG_DE_FREF, reg);

	/* Configure HS/HREF output संकेत: delay, polarity, and source */
	अगर (state->vid_fmt != OF_FMT_422_CCIR) अणु
		reg = pdata->viकरोut_delay_hs << HS_HREF_DELAY_SHIFT |
		      pdata->viकरोut_inv_hs << HS_HREF_INV_SHIFT |
		      pdata->viकरोut_sel_hs << HS_HREF_SEL_SHIFT;
	पूर्ण अन्यथा
		reg = HS_HREF_SEL_NONE << HS_HREF_SEL_SHIFT;
	io_ग_लिखो(sd, REG_HS_HREF, reg);

	/* Configure VS/VREF output संकेत: delay, polarity, and source */
	अगर (state->vid_fmt != OF_FMT_422_CCIR) अणु
		reg = pdata->viकरोut_delay_vs << VS_VREF_DELAY_SHIFT |
		      pdata->viकरोut_inv_vs << VS_VREF_INV_SHIFT |
		      pdata->viकरोut_sel_vs << VS_VREF_SEL_SHIFT;
	पूर्ण अन्यथा
		reg = VS_VREF_SEL_NONE << VS_VREF_SEL_SHIFT;
	io_ग_लिखो(sd, REG_VS_VREF, reg);

	वापस 0;
पूर्ण

/* Configure Audio output port संकेतs */
अटल पूर्णांक
tda1997x_configure_auकरोut(काष्ठा v4l2_subdev *sd, u8 channel_assignment)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	काष्ठा tda1997x_platक्रमm_data *pdata = &state->pdata;
	bool sp_used_by_fअगरo = true;
	u8 reg;

	अगर (!pdata->auकरोut_क्रमmat)
		वापस 0;

	/* channel assignment (CEA-861-D Table 20) */
	io_ग_लिखो(sd, REG_AUDIO_PATH, channel_assignment);

	/* Audio output configuration */
	reg = 0;
	चयन (pdata->auकरोut_क्रमmat) अणु
	हाल AUDFMT_TYPE_I2S:
		reg |= AUDCFG_BUS_I2S << AUDCFG_BUS_SHIFT;
		अवरोध;
	हाल AUDFMT_TYPE_SPDIF:
		reg |= AUDCFG_BUS_SPDIF << AUDCFG_BUS_SHIFT;
		अवरोध;
	पूर्ण
	चयन (state->audio_type) अणु
	हाल AUDCFG_TYPE_PCM:
		reg |= AUDCFG_TYPE_PCM << AUDCFG_TYPE_SHIFT;
		अवरोध;
	हाल AUDCFG_TYPE_OBA:
		reg |= AUDCFG_TYPE_OBA << AUDCFG_TYPE_SHIFT;
		अवरोध;
	हाल AUDCFG_TYPE_DST:
		reg |= AUDCFG_TYPE_DST << AUDCFG_TYPE_SHIFT;
		sp_used_by_fअगरo = false;
		अवरोध;
	हाल AUDCFG_TYPE_HBR:
		reg |= AUDCFG_TYPE_HBR << AUDCFG_TYPE_SHIFT;
		अगर (pdata->auकरोut_layout == 1) अणु
			/* demuxed via AP0:AP3 */
			reg |= AUDCFG_HBR_DEMUX << AUDCFG_HBR_SHIFT;
			अगर (pdata->auकरोut_क्रमmat == AUDFMT_TYPE_SPDIF)
				sp_used_by_fअगरo = false;
		पूर्ण अन्यथा अणु
			/* straight via AP0 */
			reg |= AUDCFG_HBR_STRAIGHT << AUDCFG_HBR_SHIFT;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (pdata->auकरोut_width == 32)
		reg |= AUDCFG_I2SW_32 << AUDCFG_I2SW_SHIFT;
	अन्यथा
		reg |= AUDCFG_I2SW_16 << AUDCFG_I2SW_SHIFT;

	/* स्वतःmatic hardware mute */
	अगर (pdata->audio_स्वतः_mute)
		reg |= AUDCFG_AUTO_MUTE_EN;
	/* घड़ी polarity */
	अगर (pdata->auकरोut_invert_clk)
		reg |= AUDCFG_CLK_INVERT;
	io_ग_लिखो(sd, REG_AUDCFG, reg);

	/* audio layout */
	reg = (pdata->auकरोut_layout) ? AUDIO_LAYOUT_LAYOUT1 : 0;
	अगर (!pdata->auकरोut_layoutस्वतः)
		reg |= AUDIO_LAYOUT_MANUAL;
	अगर (sp_used_by_fअगरo)
		reg |= AUDIO_LAYOUT_SP_FLAG;
	io_ग_लिखो(sd, REG_AUDIO_LAYOUT, reg);

	/* FIFO Latency value */
	io_ग_लिखो(sd, REG_FIFO_LATENCY_VAL, 0x80);

	/* Audio output port config */
	अगर (sp_used_by_fअगरo) अणु
		reg = AUDIO_OUT_ENABLE_AP0;
		अगर (channel_assignment >= 0x01)
			reg |= AUDIO_OUT_ENABLE_AP1;
		अगर (channel_assignment >= 0x04)
			reg |= AUDIO_OUT_ENABLE_AP2;
		अगर (channel_assignment >= 0x0c)
			reg |= AUDIO_OUT_ENABLE_AP3;
		/* specअगरic हालs where AP1 is not used */
		अगर ((channel_assignment == 0x04)
		 || (channel_assignment == 0x08)
		 || (channel_assignment == 0x0c)
		 || (channel_assignment == 0x10)
		 || (channel_assignment == 0x14)
		 || (channel_assignment == 0x18)
		 || (channel_assignment == 0x1c))
			reg &= ~AUDIO_OUT_ENABLE_AP1;
		/* specअगरic हालs where AP2 is not used */
		अगर ((channel_assignment >= 0x14)
		 && (channel_assignment <= 0x17))
			reg &= ~AUDIO_OUT_ENABLE_AP2;
	पूर्ण अन्यथा अणु
		reg = AUDIO_OUT_ENABLE_AP3 |
		      AUDIO_OUT_ENABLE_AP2 |
		      AUDIO_OUT_ENABLE_AP1 |
		      AUDIO_OUT_ENABLE_AP0;
	पूर्ण
	अगर (pdata->auकरोut_क्रमmat == AUDFMT_TYPE_I2S)
		reg |= (AUDIO_OUT_ENABLE_ACLK | AUDIO_OUT_ENABLE_WS);
	io_ग_लिखो(sd, REG_AUDIO_OUT_ENABLE, reg);

	/* reset test mode to normal audio freq स्वतः selection */
	io_ग_लिखो(sd, REG_TEST_MODE, 0x00);

	वापस 0;
पूर्ण

/* Soft Reset of specअगरic hdmi info */
अटल पूर्णांक
tda1997x_hdmi_info_reset(काष्ठा v4l2_subdev *sd, u8 info_rst, bool reset_sus)
अणु
	u8 reg;

	/* reset infoframe engine packets */
	reg = io_पढ़ो(sd, REG_HDMI_INFO_RST);
	io_ग_लिखो(sd, REG_HDMI_INFO_RST, info_rst);

	/* अगर infoframe engine has been reset clear INT_FLG_MODE */
	अगर (reg & RESET_IF) अणु
		reg = io_पढ़ो(sd, REG_INT_FLG_CLR_MODE);
		io_ग_लिखो(sd, REG_INT_FLG_CLR_MODE, reg);
	पूर्ण

	/* Disable REFTIM to restart start-up-sequencer (SUS) */
	reg = io_पढ़ो(sd, REG_RATE_CTRL);
	reg &= ~RATE_REFTIM_ENABLE;
	अगर (!reset_sus)
		reg |= RATE_REFTIM_ENABLE;
	reg = io_ग_लिखो(sd, REG_RATE_CTRL, reg);

	वापस 0;
पूर्ण

अटल व्योम
tda1997x_घातer_mode(काष्ठा tda1997x_state *state, bool enable)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 reg;

	अगर (enable) अणु
		/* Automatic control of TMDS */
		io_ग_लिखो(sd, REG_PON_OVR_EN, PON_DIS);
		/* Enable current bias unit */
		io_ग_लिखो(sd, REG_CFG1, PON_EN);
		/* Enable deep color PLL */
		io_ग_लिखो(sd, REG_DEEP_PLL7_BYP, PON_DIS);
		/* Output buffers active */
		reg = io_पढ़ो(sd, REG_OF);
		reg &= ~OF_VP_ENABLE;
		io_ग_लिखो(sd, REG_OF, reg);
	पूर्ण अन्यथा अणु
		/* Power करोwn EDID mode sequence */
		/* Output buffers in HiZ */
		reg = io_पढ़ो(sd, REG_OF);
		reg |= OF_VP_ENABLE;
		io_ग_लिखो(sd, REG_OF, reg);
		/* Disable deep color PLL */
		io_ग_लिखो(sd, REG_DEEP_PLL7_BYP, PON_EN);
		/* Disable current bias unit */
		io_ग_लिखो(sd, REG_CFG1, PON_DIS);
		/* Manual control of TMDS */
		io_ग_लिखो(sd, REG_PON_OVR_EN, PON_EN);
	पूर्ण
पूर्ण

अटल bool
tda1997x_detect_tx_5v(काष्ठा v4l2_subdev *sd)
अणु
	u8 reg = io_पढ़ो(sd, REG_DETECT_5V);

	वापस ((reg & DETECT_5V_SEL) ? 1 : 0);
पूर्ण

अटल bool
tda1997x_detect_tx_hpd(काष्ठा v4l2_subdev *sd)
अणु
	u8 reg = io_पढ़ो(sd, REG_DETECT_5V);

	वापस ((reg & DETECT_HPD) ? 1 : 0);
पूर्ण

अटल पूर्णांक
tda1997x_detect_std(काष्ठा tda1997x_state *state,
		    काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	u32 vper;
	u16 hper;
	u16 hsper;
	पूर्णांक i;

	/*
	 * Read the FMT रेजिस्टरs
	 *   REG_V_PER: Period of a frame (or two fields) in MCLK(27MHz) cycles
	 *   REG_H_PER: Period of a line in MCLK(27MHz) cycles
	 *   REG_HS_WIDTH: Period of horiz sync pulse in MCLK(27MHz) cycles
	 */
	vper = io_पढ़ो24(sd, REG_V_PER) & MASK_VPER;
	hper = io_पढ़ो16(sd, REG_H_PER) & MASK_HPER;
	hsper = io_पढ़ो16(sd, REG_HS_WIDTH) & MASK_HSWIDTH;
	v4l2_dbg(1, debug, sd, "Signal Timings: %u/%u/%u\n", vper, hper, hsper);
	अगर (!vper || !hper || !hsper)
		वापस -ENOLINK;

	क्रम (i = 0; v4l2_dv_timings_presets[i].bt.width; i++) अणु
		स्थिर काष्ठा v4l2_bt_timings *bt;
		u32 lines, width, _hper, _hsper;
		u32 vmin, vmax, hmin, hmax, hsmin, hsmax;
		bool vmatch, hmatch, hsmatch;

		bt = &v4l2_dv_timings_presets[i].bt;
		width = V4L2_DV_BT_FRAME_WIDTH(bt);
		lines = V4L2_DV_BT_FRAME_HEIGHT(bt);
		_hper = (u32)bt->pixelघड़ी / width;
		अगर (bt->पूर्णांकerlaced)
			lines /= 2;
		/* vper +/- 0.7% */
		vmin = ((27000000 / 1000) * 993) / _hper * lines;
		vmax = ((27000000 / 1000) * 1007) / _hper * lines;
		/* hper +/- 1.0% */
		hmin = ((27000000 / 100) * 99) / _hper;
		hmax = ((27000000 / 100) * 101) / _hper;
		/* hsper +/- 2 (take care to aव्योम 32bit overflow) */
		_hsper = 27000 * bt->hsync / ((u32)bt->pixelघड़ी/1000);
		hsmin = _hsper - 2;
		hsmax = _hsper + 2;

		/* vmatch matches the framerate */
		vmatch = ((vper <= vmax) && (vper >= vmin)) ? 1 : 0;
		/* hmatch matches the width */
		hmatch = ((hper <= hmax) && (hper >= hmin)) ? 1 : 0;
		/* hsmatch matches the hswidth */
		hsmatch = ((hsper <= hsmax) && (hsper >= hsmin)) ? 1 : 0;
		अगर (hmatch && vmatch && hsmatch) अणु
			v4l2_prपूर्णांक_dv_timings(sd->name, "Detected format: ",
					      &v4l2_dv_timings_presets[i],
					      false);
			अगर (timings)
				*timings = v4l2_dv_timings_presets[i];
			वापस 0;
		पूर्ण
	पूर्ण

	v4l_err(state->client, "no resolution match for timings: %d/%d/%d\n",
		vper, hper, hsper);
	वापस -दुस्फल;
पूर्ण

/* some sort of errata workaround क्रम chip revision 0 (N1) */
अटल व्योम tda1997x_reset_n1(काष्ठा tda1997x_state *state)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 reg;

	/* clear HDMI mode flag in BCAPS */
	io_ग_लिखो(sd, REG_CLK_CFG, CLK_CFG_SEL_ACLK_EN | CLK_CFG_SEL_ACLK);
	io_ग_लिखो(sd, REG_PON_OVR_EN, PON_EN);
	io_ग_लिखो(sd, REG_PON_CBIAS, PON_EN);
	io_ग_लिखो(sd, REG_PON_PLL, PON_EN);

	reg = io_पढ़ो(sd, REG_MODE_REC_CFG1);
	reg &= ~0x06;
	reg |= 0x02;
	io_ग_लिखो(sd, REG_MODE_REC_CFG1, reg);
	io_ग_लिखो(sd, REG_CLK_CFG, CLK_CFG_DIS);
	io_ग_लिखो(sd, REG_PON_OVR_EN, PON_DIS);
	reg = io_पढ़ो(sd, REG_MODE_REC_CFG1);
	reg &= ~0x06;
	io_ग_लिखो(sd, REG_MODE_REC_CFG1, reg);
पूर्ण

/*
 * Activity detection must only be notअगरied when stable_clk_x AND active_x
 * bits are set to 1. If only stable_clk_x bit is set to 1 but not
 * active_x, it means that the TMDS घड़ी is not in the defined range
 * and activity detection must not be notअगरied.
 */
अटल u8
tda1997x_पढ़ो_activity_status_regs(काष्ठा v4l2_subdev *sd)
अणु
	u8 reg, status = 0;

	/* Read CLK_A_STATUS रेजिस्टर */
	reg = io_पढ़ो(sd, REG_CLK_A_STATUS);
	/* ignore अगर not active */
	अगर ((reg & MASK_CLK_STABLE) && !(reg & MASK_CLK_ACTIVE))
		reg &= ~MASK_CLK_STABLE;
	status |= ((reg & MASK_CLK_STABLE) >> 2);

	/* Read CLK_B_STATUS रेजिस्टर */
	reg = io_पढ़ो(sd, REG_CLK_B_STATUS);
	/* ignore अगर not active */
	अगर ((reg & MASK_CLK_STABLE) && !(reg & MASK_CLK_ACTIVE))
		reg &= ~MASK_CLK_STABLE;
	status |= ((reg & MASK_CLK_STABLE) >> 1);

	/* Read the SUS_STATUS रेजिस्टर */
	reg = io_पढ़ो(sd, REG_SUS_STATUS);

	/* If state = 5 => TMDS is locked */
	अगर ((reg & MASK_SUS_STATUS) == LAST_STATE_REACHED)
		status |= MASK_SUS_STATE;
	अन्यथा
		status &= ~MASK_SUS_STATE;

	वापस status;
पूर्ण

अटल व्योम
set_rgb_quantization_range(काष्ठा tda1997x_state *state)
अणु
	काष्ठा v4l2_hdmi_colorimetry *c = &state->colorimetry;

	state->colorimetry = v4l2_hdmi_rx_colorimetry(&state->avi_infoframe,
						      शून्य,
						      state->timings.bt.height);
	/* If ycbcr_enc is V4L2_YCBCR_ENC_DEFAULT, we receive RGB */
	अगर (c->ycbcr_enc == V4L2_YCBCR_ENC_DEFAULT) अणु
		चयन (state->rgb_quantization_range) अणु
		हाल V4L2_DV_RGB_RANGE_LIMITED:
			c->quantization = V4L2_QUANTIZATION_FULL_RANGE;
			अवरोध;
		हाल V4L2_DV_RGB_RANGE_FULL:
			c->quantization = V4L2_QUANTIZATION_LIM_RANGE;
			अवरोध;
		पूर्ण
	पूर्ण
	v4l_dbg(1, debug, state->client,
		"colorspace=%d/%d colorimetry=%d range=%s content=%d\n",
		state->avi_infoframe.colorspace, c->colorspace,
		state->avi_infoframe.colorimetry,
		v4l2_quantization_names[c->quantization],
		state->avi_infoframe.content_type);
पूर्ण

/* parse an infoframe and करो some sanity checks on it */
अटल अचिन्हित पूर्णांक
tda1997x_parse_infoframe(काष्ठा tda1997x_state *state, u16 addr)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	जोड़ hdmi_infoframe frame;
	u8 buffer[40];
	u8 reg;
	पूर्णांक len, err;

	/* पढ़ो data */
	len = io_पढ़ोn(sd, addr, माप(buffer), buffer);
	err = hdmi_infoframe_unpack(&frame, buffer, माप(buffer));
	अगर (err) अणु
		v4l_err(state->client,
			"failed parsing %d byte infoframe: 0x%04x/0x%02x\n",
			len, addr, buffer[0]);
		वापस err;
	पूर्ण
	hdmi_infoframe_log(KERN_INFO, &state->client->dev, &frame);
	चयन (frame.any.type) अणु
	/* Audio InfoFrame: see HDMI spec 8.2.2 */
	हाल HDMI_INFOFRAME_TYPE_AUDIO:
		/* sample rate */
		चयन (frame.audio.sample_frequency) अणु
		हाल HDMI_AUDIO_SAMPLE_FREQUENCY_32000:
			state->audio_samplerate = 32000;
			अवरोध;
		हाल HDMI_AUDIO_SAMPLE_FREQUENCY_44100:
			state->audio_samplerate = 44100;
			अवरोध;
		हाल HDMI_AUDIO_SAMPLE_FREQUENCY_48000:
			state->audio_samplerate = 48000;
			अवरोध;
		हाल HDMI_AUDIO_SAMPLE_FREQUENCY_88200:
			state->audio_samplerate = 88200;
			अवरोध;
		हाल HDMI_AUDIO_SAMPLE_FREQUENCY_96000:
			state->audio_samplerate = 96000;
			अवरोध;
		हाल HDMI_AUDIO_SAMPLE_FREQUENCY_176400:
			state->audio_samplerate = 176400;
			अवरोध;
		हाल HDMI_AUDIO_SAMPLE_FREQUENCY_192000:
			state->audio_samplerate = 192000;
			अवरोध;
		शेष:
		हाल HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM:
			अवरोध;
		पूर्ण

		/* sample size */
		चयन (frame.audio.sample_size) अणु
		हाल HDMI_AUDIO_SAMPLE_SIZE_16:
			state->audio_samplesize = 16;
			अवरोध;
		हाल HDMI_AUDIO_SAMPLE_SIZE_20:
			state->audio_samplesize = 20;
			अवरोध;
		हाल HDMI_AUDIO_SAMPLE_SIZE_24:
			state->audio_samplesize = 24;
			अवरोध;
		हाल HDMI_AUDIO_SAMPLE_SIZE_STREAM:
		शेष:
			अवरोध;
		पूर्ण

		/* Channel Count */
		state->audio_channels = frame.audio.channels;
		अगर (frame.audio.channel_allocation &&
		    frame.audio.channel_allocation != state->audio_ch_alloc) अणु
			/* use the channel assignment from the infoframe */
			state->audio_ch_alloc = frame.audio.channel_allocation;
			tda1997x_configure_auकरोut(sd, state->audio_ch_alloc);
			/* reset the audio FIFO */
			tda1997x_hdmi_info_reset(sd, RESET_AUDIO, false);
		पूर्ण
		अवरोध;

	/* Auxiliary Video inक्रमmation (AVI) InfoFrame: see HDMI spec 8.2.1 */
	हाल HDMI_INFOFRAME_TYPE_AVI:
		state->avi_infoframe = frame.avi;
		set_rgb_quantization_range(state);

		/* configure upsampler: 0=bypass 1=repeatchroma 2=पूर्णांकerpolate */
		reg = io_पढ़ो(sd, REG_PIX_REPEAT);
		reg &= ~PIX_REPEAT_MASK_UP_SEL;
		अगर (frame.avi.colorspace == HDMI_COLORSPACE_YUV422)
			reg |= (PIX_REPEAT_CHROMA << PIX_REPEAT_SHIFT);
		io_ग_लिखो(sd, REG_PIX_REPEAT, reg);

		/* ConfigurePixelRepeater: repeat n-बार each pixel */
		reg = io_पढ़ो(sd, REG_PIX_REPEAT);
		reg &= ~PIX_REPEAT_MASK_REP;
		reg |= frame.avi.pixel_repeat;
		io_ग_लिखो(sd, REG_PIX_REPEAT, reg);

		/* configure the receiver with the new colorspace */
		tda1997x_configure_csc(sd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tda1997x_irq_sus(काष्ठा tda1997x_state *state, u8 *flags)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 reg, source;

	source = io_पढ़ो(sd, REG_INT_FLG_CLR_SUS);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_SUS, source);

	अगर (source & MASK_MPT) अणु
		/* reset MTP in use flag अगर set */
		अगर (state->mptrw_in_progress)
			state->mptrw_in_progress = 0;
	पूर्ण

	अगर (source & MASK_SUS_END) अणु
		/* reset audio FIFO */
		reg = io_पढ़ो(sd, REG_HDMI_INFO_RST);
		reg |= MASK_SR_FIFO_FIFO_CTRL;
		io_ग_लिखो(sd, REG_HDMI_INFO_RST, reg);
		reg &= ~MASK_SR_FIFO_FIFO_CTRL;
		io_ग_लिखो(sd, REG_HDMI_INFO_RST, reg);

		/* reset HDMI flags */
		state->hdmi_status = 0;
	पूर्ण

	/* filter FMT पूर्णांकerrupt based on SUS state */
	reg = io_पढ़ो(sd, REG_SUS_STATUS);
	अगर (((reg & MASK_SUS_STATUS) != LAST_STATE_REACHED)
	   || (source & MASK_MPT)) अणु
		source &= ~MASK_FMT;
	पूर्ण

	अगर (source & (MASK_FMT | MASK_SUS_END)) अणु
		reg = io_पढ़ो(sd, REG_SUS_STATUS);
		अगर ((reg & MASK_SUS_STATUS) != LAST_STATE_REACHED) अणु
			v4l_err(state->client, "BAD SUS STATUS\n");
			वापस;
		पूर्ण
		अगर (debug)
			tda1997x_detect_std(state, शून्य);
		/* notअगरy user of change in resolution */
		v4l2_subdev_notअगरy_event(&state->sd, &tda1997x_ev_fmt);
	पूर्ण
पूर्ण

अटल व्योम tda1997x_irq_ddc(काष्ठा tda1997x_state *state, u8 *flags)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 source;

	source = io_पढ़ो(sd, REG_INT_FLG_CLR_DDC);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_DDC, source);
	अगर (source & MASK_EDID_MTP) अणु
		/* reset MTP in use flag अगर set */
		अगर (state->mptrw_in_progress)
			state->mptrw_in_progress = 0;
	पूर्ण

	/* Detection of +5V */
	अगर (source & MASK_DET_5V) अणु
		v4l2_ctrl_s_ctrl(state->detect_tx_5v_ctrl,
				 tda1997x_detect_tx_5v(sd));
	पूर्ण
पूर्ण

अटल व्योम tda1997x_irq_rate(काष्ठा tda1997x_state *state, u8 *flags)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 reg, source;

	u8 irq_status;

	source = io_पढ़ो(sd, REG_INT_FLG_CLR_RATE);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_RATE, source);

	/* पढ़ो status regs */
	irq_status = tda1997x_पढ़ो_activity_status_regs(sd);

	/*
	 * पढ़ो घड़ी status reg until INT_FLG_CLR_RATE is still 0
	 * after the पढ़ो to make sure its the last one
	 */
	reg = source;
	जबतक (reg != 0) अणु
		irq_status = tda1997x_पढ़ो_activity_status_regs(sd);
		reg = io_पढ़ो(sd, REG_INT_FLG_CLR_RATE);
		io_ग_लिखो(sd, REG_INT_FLG_CLR_RATE, reg);
		source |= reg;
	पूर्ण

	/* we only pay attention to stability change events */
	अगर (source & (MASK_RATE_A_ST | MASK_RATE_B_ST)) अणु
		पूर्णांक input = (source & MASK_RATE_A_ST)?0:1;
		u8 mask = 1<<input;

		/* state change */
		अगर ((irq_status & mask) != (state->activity_status & mask)) अणु
			/* activity lost */
			अगर ((irq_status & mask) == 0) अणु
				v4l_info(state->client,
					 "HDMI-%c: Digital Activity Lost\n",
					 input+'A');

				/* bypass up/करोwn sampler and pixel repeater */
				reg = io_पढ़ो(sd, REG_PIX_REPEAT);
				reg &= ~PIX_REPEAT_MASK_UP_SEL;
				reg &= ~PIX_REPEAT_MASK_REP;
				io_ग_लिखो(sd, REG_PIX_REPEAT, reg);

				अगर (state->chip_revision == 0)
					tda1997x_reset_n1(state);

				state->input_detect[input] = 0;
				v4l2_subdev_notअगरy_event(sd, &tda1997x_ev_fmt);
			पूर्ण

			/* activity detected */
			अन्यथा अणु
				v4l_info(state->client,
					 "HDMI-%c: Digital Activity Detected\n",
					 input+'A');
				state->input_detect[input] = 1;
			पूर्ण

			/* hold onto current state */
			state->activity_status = (irq_status & mask);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम tda1997x_irq_info(काष्ठा tda1997x_state *state, u8 *flags)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 source;

	source = io_पढ़ो(sd, REG_INT_FLG_CLR_INFO);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_INFO, source);

	/* Audio infoframe */
	अगर (source & MASK_AUD_IF) अणु
		tda1997x_parse_infoframe(state, AUD_IF);
		source &= ~MASK_AUD_IF;
	पूर्ण

	/* Source Product Descriptor infoframe change */
	अगर (source & MASK_SPD_IF) अणु
		tda1997x_parse_infoframe(state, SPD_IF);
		source &= ~MASK_SPD_IF;
	पूर्ण

	/* Auxiliary Video Inक्रमmation infoframe */
	अगर (source & MASK_AVI_IF) अणु
		tda1997x_parse_infoframe(state, AVI_IF);
		source &= ~MASK_AVI_IF;
	पूर्ण
पूर्ण

अटल व्योम tda1997x_irq_audio(काष्ठा tda1997x_state *state, u8 *flags)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 reg, source;

	source = io_पढ़ो(sd, REG_INT_FLG_CLR_AUDIO);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_AUDIO, source);

	/* reset audio FIFO on FIFO poपूर्णांकer error or audio mute */
	अगर (source & MASK_ERROR_FIFO_PT ||
	    source & MASK_MUTE_FLG) अणु
		/* audio reset audio FIFO */
		reg = io_पढ़ो(sd, REG_SUS_STATUS);
		अगर ((reg & MASK_SUS_STATUS) == LAST_STATE_REACHED) अणु
			reg = io_पढ़ो(sd, REG_HDMI_INFO_RST);
			reg |= MASK_SR_FIFO_FIFO_CTRL;
			io_ग_लिखो(sd, REG_HDMI_INFO_RST, reg);
			reg &= ~MASK_SR_FIFO_FIFO_CTRL;
			io_ग_लिखो(sd, REG_HDMI_INFO_RST, reg);
			/* reset channel status IT अगर present */
			source &= ~(MASK_CH_STATE);
		पूर्ण
	पूर्ण
	अगर (source & MASK_AUDIO_FREQ_FLG) अणु
		अटल स्थिर पूर्णांक freq[] = अणु
			0, 32000, 44100, 48000, 88200, 96000, 176400, 192000
		पूर्ण;

		reg = io_पढ़ो(sd, REG_AUDIO_FREQ);
		state->audio_samplerate = freq[reg & 7];
		v4l_info(state->client, "Audio Frequency Change: %dHz\n",
			 state->audio_samplerate);
	पूर्ण
	अगर (source & MASK_AUDIO_FLG) अणु
		reg = io_पढ़ो(sd, REG_AUDIO_FLAGS);
		अगर (reg & BIT(AUDCFG_TYPE_DST))
			state->audio_type = AUDCFG_TYPE_DST;
		अगर (reg & BIT(AUDCFG_TYPE_OBA))
			state->audio_type = AUDCFG_TYPE_OBA;
		अगर (reg & BIT(AUDCFG_TYPE_HBR))
			state->audio_type = AUDCFG_TYPE_HBR;
		अगर (reg & BIT(AUDCFG_TYPE_PCM))
			state->audio_type = AUDCFG_TYPE_PCM;
		v4l_info(state->client, "Audio Type: %s\n",
			 audtype_names[state->audio_type]);
	पूर्ण
पूर्ण

अटल व्योम tda1997x_irq_hdcp(काष्ठा tda1997x_state *state, u8 *flags)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 reg, source;

	source = io_पढ़ो(sd, REG_INT_FLG_CLR_HDCP);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_HDCP, source);

	/* reset MTP in use flag अगर set */
	अगर (source & MASK_HDCP_MTP)
		state->mptrw_in_progress = 0;
	अगर (source & MASK_STATE_C5) अणु
		/* REPEATER: mask AUDIO and IF irqs to aव्योम IF during auth */
		reg = io_पढ़ो(sd, REG_INT_MASK_TOP);
		reg &= ~(INTERRUPT_AUDIO | INTERRUPT_INFO);
		io_ग_लिखो(sd, REG_INT_MASK_TOP, reg);
		*flags &= (INTERRUPT_AUDIO | INTERRUPT_INFO);
	पूर्ण
पूर्ण

अटल irqवापस_t tda1997x_isr_thपढ़ो(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा tda1997x_state *state = d;
	काष्ठा v4l2_subdev *sd = &state->sd;
	u8 flags;

	mutex_lock(&state->lock);
	करो अणु
		/* पढ़ो पूर्णांकerrupt flags */
		flags = io_पढ़ो(sd, REG_INT_FLG_CLR_TOP);
		अगर (flags == 0)
			अवरोध;

		/* SUS पूर्णांकerrupt source (Input activity events) */
		अगर (flags & INTERRUPT_SUS)
			tda1997x_irq_sus(state, &flags);
		/* DDC पूर्णांकerrupt source (Display Data Channel) */
		अन्यथा अगर (flags & INTERRUPT_DDC)
			tda1997x_irq_ddc(state, &flags);
		/* RATE पूर्णांकerrupt source (Digital Input activity) */
		अन्यथा अगर (flags & INTERRUPT_RATE)
			tda1997x_irq_rate(state, &flags);
		/* Infoframe change पूर्णांकerrupt */
		अन्यथा अगर (flags & INTERRUPT_INFO)
			tda1997x_irq_info(state, &flags);
		/* Audio पूर्णांकerrupt source:
		 *   freq change, DST,OBA,HBR,ASP flags, mute, FIFO err
		 */
		अन्यथा अगर (flags & INTERRUPT_AUDIO)
			tda1997x_irq_audio(state, &flags);
		/* HDCP पूर्णांकerrupt source (content protection) */
		अगर (flags & INTERRUPT_HDCP)
			tda1997x_irq_hdcp(state, &flags);
	पूर्ण जबतक (flags != 0);
	mutex_unlock(&state->lock);

	वापस IRQ_HANDLED;
पूर्ण

/* -----------------------------------------------------------------------------
 * v4l2_subdev_video_ops
 */

अटल पूर्णांक
tda1997x_g_input_status(काष्ठा v4l2_subdev *sd, u32 *status)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	u32 vper;
	u16 hper;
	u16 hsper;

	mutex_lock(&state->lock);
	vper = io_पढ़ो24(sd, REG_V_PER) & MASK_VPER;
	hper = io_पढ़ो16(sd, REG_H_PER) & MASK_HPER;
	hsper = io_पढ़ो16(sd, REG_HS_WIDTH) & MASK_HSWIDTH;
	/*
	 * The tda1997x supports A/B inमाला_दो but only a single output.
	 * The irq handler monitors क्रम timing changes on both inमाला_दो and
	 * sets the input_detect array to 0|1 depending on संकेत presence.
	 * I believe selection of A vs B is स्वतःmatic.
	 *
	 * The vper/hper/hsper रेजिस्टरs provide the frame period, line period
	 * and horiz sync period (units of MCLK घड़ी cycles (27MHz)) and
	 * testing shows these values to be अक्रमom अगर no संकेत is present
	 * or locked.
	 */
	v4l2_dbg(1, debug, sd, "inputs:%d/%d timings:%d/%d/%d\n",
		 state->input_detect[0], state->input_detect[1],
		 vper, hper, hsper);
	अगर (!state->input_detect[0] && !state->input_detect[1])
		*status = V4L2_IN_ST_NO_SIGNAL;
	अन्यथा अगर (!vper || !hper || !hsper)
		*status = V4L2_IN_ST_NO_SYNC;
	अन्यथा
		*status = 0;
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण;

अटल पूर्णांक tda1997x_s_dv_timings(काष्ठा v4l2_subdev *sd,
				काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);

	v4l_dbg(1, debug, state->client, "%s\n", __func__);

	अगर (v4l2_match_dv_timings(&state->timings, timings, 0, false))
		वापस 0; /* no changes */

	अगर (!v4l2_valid_dv_timings(timings, &tda1997x_dv_timings_cap,
				   शून्य, शून्य))
		वापस -दुस्फल;

	mutex_lock(&state->lock);
	state->timings = *timings;
	/* setup frame detection winकरोw and VHREF timing generator */
	tda1997x_configure_vhref(sd);
	/* configure colorspace conversion */
	tda1997x_configure_csc(sd);
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_g_dv_timings(काष्ठा v4l2_subdev *sd,
				 काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);

	v4l_dbg(1, debug, state->client, "%s\n", __func__);
	mutex_lock(&state->lock);
	*timings = state->timings;
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_query_dv_timings(काष्ठा v4l2_subdev *sd,
				     काष्ठा v4l2_dv_timings *timings)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);

	v4l_dbg(1, debug, state->client, "%s\n", __func__);
	स_रखो(timings, 0, माप(काष्ठा v4l2_dv_timings));
	mutex_lock(&state->lock);
	tda1997x_detect_std(state, timings);
	mutex_unlock(&state->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_video_ops tda1997x_video_ops = अणु
	.g_input_status = tda1997x_g_input_status,
	.s_dv_timings = tda1997x_s_dv_timings,
	.g_dv_timings = tda1997x_g_dv_timings,
	.query_dv_timings = tda1997x_query_dv_timings,
पूर्ण;


/* -----------------------------------------------------------------------------
 * v4l2_subdev_pad_ops
 */

अटल पूर्णांक tda1997x_init_cfg(काष्ठा v4l2_subdev *sd,
			     काष्ठा v4l2_subdev_pad_config *cfg)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	काष्ठा v4l2_mbus_framefmt *mf;

	mf = v4l2_subdev_get_try_क्रमmat(sd, cfg, 0);
	mf->code = state->mbus_codes[0];

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
				  काष्ठा v4l2_subdev_pad_config *cfg,
				  काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);

	v4l_dbg(1, debug, state->client, "%s %d\n", __func__, code->index);
	अगर (code->index >= ARRAY_SIZE(state->mbus_codes))
		वापस -EINVAL;

	अगर (!state->mbus_codes[code->index])
		वापस -EINVAL;

	code->code = state->mbus_codes[code->index];

	वापस 0;
पूर्ण

अटल व्योम tda1997x_fill_क्रमmat(काष्ठा tda1997x_state *state,
				 काष्ठा v4l2_mbus_framefmt *क्रमmat)
अणु
	स्थिर काष्ठा v4l2_bt_timings *bt;

	स_रखो(क्रमmat, 0, माप(*क्रमmat));
	bt = &state->timings.bt;
	क्रमmat->width = bt->width;
	क्रमmat->height = bt->height;
	क्रमmat->colorspace = state->colorimetry.colorspace;
	क्रमmat->field = (bt->पूर्णांकerlaced) ?
		V4L2_FIELD_SEQ_TB : V4L2_FIELD_NONE;
पूर्ण

अटल पूर्णांक tda1997x_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);

	v4l_dbg(1, debug, state->client, "%s pad=%d which=%d\n",
		__func__, क्रमmat->pad, क्रमmat->which);

	tda1997x_fill_क्रमmat(state, &क्रमmat->क्रमmat);

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		क्रमmat->क्रमmat.code = fmt->code;
	पूर्ण अन्यथा
		क्रमmat->क्रमmat.code = state->mbus_code;

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_क्रमmat *क्रमmat)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	u32 code = 0;
	पूर्णांक i;

	v4l_dbg(1, debug, state->client, "%s pad=%d which=%d fmt=0x%x\n",
		__func__, क्रमmat->pad, क्रमmat->which, क्रमmat->क्रमmat.code);

	क्रम (i = 0; i < ARRAY_SIZE(state->mbus_codes); i++) अणु
		अगर (क्रमmat->क्रमmat.code == state->mbus_codes[i]) अणु
			code = state->mbus_codes[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!code)
		code = state->mbus_codes[0];

	tda1997x_fill_क्रमmat(state, &क्रमmat->क्रमmat);
	क्रमmat->क्रमmat.code = code;

	अगर (क्रमmat->which == V4L2_SUBDEV_FORMAT_TRY) अणु
		काष्ठा v4l2_mbus_framefmt *fmt;

		fmt = v4l2_subdev_get_try_क्रमmat(sd, cfg, क्रमmat->pad);
		*fmt = क्रमmat->क्रमmat;
	पूर्ण अन्यथा अणु
		पूर्णांक ret = tda1997x_setup_क्रमmat(state, क्रमmat->क्रमmat.code);

		अगर (ret)
			वापस ret;
		/* mbus_code has changed - re-configure csc/viकरोut */
		tda1997x_configure_csc(sd);
		tda1997x_configure_viकरोut(state);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_get_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);

	v4l_dbg(1, debug, state->client, "%s pad=%d\n", __func__, edid->pad);
	स_रखो(edid->reserved, 0, माप(edid->reserved));

	अगर (edid->start_block == 0 && edid->blocks == 0) अणु
		edid->blocks = state->edid.blocks;
		वापस 0;
	पूर्ण

	अगर (!state->edid.present)
		वापस -ENODATA;

	अगर (edid->start_block >= state->edid.blocks)
		वापस -EINVAL;

	अगर (edid->start_block + edid->blocks > state->edid.blocks)
		edid->blocks = state->edid.blocks - edid->start_block;

	स_नकल(edid->edid, state->edid.edid + edid->start_block * 128,
	       edid->blocks * 128);

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_set_edid(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_edid *edid)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	पूर्णांक i;

	v4l_dbg(1, debug, state->client, "%s pad=%d\n", __func__, edid->pad);
	स_रखो(edid->reserved, 0, माप(edid->reserved));

	अगर (edid->start_block != 0)
		वापस -EINVAL;

	अगर (edid->blocks == 0) अणु
		state->edid.blocks = 0;
		state->edid.present = 0;
		tda1997x_disable_edid(sd);
		वापस 0;
	पूर्ण

	अगर (edid->blocks > 2) अणु
		edid->blocks = 2;
		वापस -E2BIG;
	पूर्ण

	tda1997x_disable_edid(sd);

	/* ग_लिखो base EDID */
	क्रम (i = 0; i < 128; i++)
		io_ग_लिखो(sd, REG_EDID_IN_BYTE0 + i, edid->edid[i]);

	/* ग_लिखो CEA Extension */
	क्रम (i = 0; i < 128; i++)
		io_ग_लिखो(sd, REG_EDID_IN_BYTE128 + i, edid->edid[i+128]);

	/* store state */
	स_नकल(state->edid.edid, edid->edid, 256);
	state->edid.blocks = edid->blocks;

	tda1997x_enable_edid(sd);

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_get_dv_timings_cap(काष्ठा v4l2_subdev *sd,
				       काष्ठा v4l2_dv_timings_cap *cap)
अणु
	*cap = tda1997x_dv_timings_cap;
	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_क्रमागत_dv_timings(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	वापस v4l2_क्रमागत_dv_timings_cap(timings, &tda1997x_dv_timings_cap,
					शून्य, शून्य);
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_pad_ops tda1997x_pad_ops = अणु
	.init_cfg = tda1997x_init_cfg,
	.क्रमागत_mbus_code = tda1997x_क्रमागत_mbus_code,
	.get_fmt = tda1997x_get_क्रमmat,
	.set_fmt = tda1997x_set_क्रमmat,
	.get_edid = tda1997x_get_edid,
	.set_edid = tda1997x_set_edid,
	.dv_timings_cap = tda1997x_get_dv_timings_cap,
	.क्रमागत_dv_timings = tda1997x_क्रमागत_dv_timings,
पूर्ण;

/* -----------------------------------------------------------------------------
 * v4l2_subdev_core_ops
 */

अटल पूर्णांक tda1997x_log_infoframe(काष्ठा v4l2_subdev *sd, पूर्णांक addr)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	जोड़ hdmi_infoframe frame;
	u8 buffer[40];
	पूर्णांक len, err;

	/* पढ़ो data */
	len = io_पढ़ोn(sd, addr, माप(buffer), buffer);
	v4l2_dbg(1, debug, sd, "infoframe: addr=%d len=%d\n", addr, len);
	err = hdmi_infoframe_unpack(&frame, buffer, माप(buffer));
	अगर (err) अणु
		v4l_err(state->client,
			"failed parsing %d byte infoframe: 0x%04x/0x%02x\n",
			len, addr, buffer[0]);
		वापस err;
	पूर्ण
	hdmi_infoframe_log(KERN_INFO, &state->client->dev, &frame);

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	काष्ठा v4l2_dv_timings timings;
	काष्ठा hdmi_avi_infoframe *avi = &state->avi_infoframe;

	v4l2_info(sd, "-----Chip status-----\n");
	v4l2_info(sd, "Chip: %s N%d\n", state->info->name,
		  state->chip_revision + 1);
	v4l2_info(sd, "EDID Enabled: %s\n", state->edid.present ? "yes" : "no");

	v4l2_info(sd, "-----Signal status-----\n");
	v4l2_info(sd, "Cable detected (+5V power): %s\n",
		  tda1997x_detect_tx_5v(sd) ? "yes" : "no");
	v4l2_info(sd, "HPD detected: %s\n",
		  tda1997x_detect_tx_hpd(sd) ? "yes" : "no");

	v4l2_info(sd, "-----Video Timings-----\n");
	चयन (tda1997x_detect_std(state, &timings)) अणु
	हाल -ENOLINK:
		v4l2_info(sd, "No video detected\n");
		अवरोध;
	हाल -दुस्फल:
		v4l2_info(sd, "Invalid signal detected\n");
		अवरोध;
	पूर्ण
	v4l2_prपूर्णांक_dv_timings(sd->name, "Configured format: ",
			      &state->timings, true);

	v4l2_info(sd, "-----Color space-----\n");
	v4l2_info(sd, "Input color space: %s %s %s",
		  hdmi_colorspace_names[avi->colorspace],
		  (avi->colorspace == HDMI_COLORSPACE_RGB) ? "" :
			hdmi_colorimetry_names[avi->colorimetry],
		  v4l2_quantization_names[state->colorimetry.quantization]);
	v4l2_info(sd, "Output color space: %s",
		  vidfmt_names[state->vid_fmt]);
	v4l2_info(sd, "Color space conversion: %s", state->conv ?
		  state->conv->name : "None");

	v4l2_info(sd, "-----Audio-----\n");
	अगर (state->audio_channels) अणु
		v4l2_info(sd, "audio: %dch %dHz\n", state->audio_channels,
			  state->audio_samplerate);
	पूर्ण अन्यथा अणु
		v4l2_info(sd, "audio: none\n");
	पूर्ण

	v4l2_info(sd, "-----Infoframes-----\n");
	tda1997x_log_infoframe(sd, AUD_IF);
	tda1997x_log_infoframe(sd, SPD_IF);
	tda1997x_log_infoframe(sd, AVI_IF);

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_subscribe_event(काष्ठा v4l2_subdev *sd,
				    काष्ठा v4l2_fh *fh,
				    काष्ठा v4l2_event_subscription *sub)
अणु
	चयन (sub->type) अणु
	हाल V4L2_EVENT_SOURCE_CHANGE:
		वापस v4l2_src_change_event_subdev_subscribe(sd, fh, sub);
	हाल V4L2_EVENT_CTRL:
		वापस v4l2_ctrl_subdev_subscribe_event(sd, fh, sub);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा v4l2_subdev_core_ops tda1997x_core_ops = अणु
	.log_status = tda1997x_log_status,
	.subscribe_event = tda1997x_subscribe_event,
	.unsubscribe_event = v4l2_event_subdev_unsubscribe,
पूर्ण;

/* -----------------------------------------------------------------------------
 * v4l2_subdev_ops
 */

अटल स्थिर काष्ठा v4l2_subdev_ops tda1997x_subdev_ops = अणु
	.core = &tda1997x_core_ops,
	.video = &tda1997x_video_ops,
	.pad = &tda1997x_pad_ops,
पूर्ण;

/* -----------------------------------------------------------------------------
 * v4l2_controls
 */

अटल पूर्णांक tda1997x_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा tda1997x_state *state = to_state(sd);

	चयन (ctrl->id) अणु
	/* allow overriding the शेष RGB quantization range */
	हाल V4L2_CID_DV_RX_RGB_RANGE:
		state->rgb_quantization_range = ctrl->val;
		set_rgb_quantization_range(state);
		tda1997x_configure_csc(sd);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण;

अटल पूर्णांक tda1997x_g_अस्थिर_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा v4l2_subdev *sd = to_sd(ctrl);
	काष्ठा tda1997x_state *state = to_state(sd);

	अगर (ctrl->id == V4L2_CID_DV_RX_IT_CONTENT_TYPE) अणु
		ctrl->val = state->avi_infoframe.content_type;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops tda1997x_ctrl_ops = अणु
	.s_ctrl = tda1997x_s_ctrl,
	.g_अस्थिर_ctrl = tda1997x_g_अस्थिर_ctrl,
पूर्ण;

अटल पूर्णांक tda1997x_core_init(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा tda1997x_state *state = to_state(sd);
	काष्ठा tda1997x_platक्रमm_data *pdata = &state->pdata;
	u8 reg;
	पूर्णांक i;

	/* disable HPD */
	io_ग_लिखो(sd, REG_HPD_AUTO_CTRL, HPD_AUTO_HPD_UNSEL);
	अगर (state->chip_revision == 0) अणु
		io_ग_लिखो(sd, REG_MAN_SUS_HDMI_SEL, MAN_DIS_HDCP | MAN_RST_HDCP);
		io_ग_लिखो(sd, REG_CGU_DBG_SEL, 1 << CGU_DBG_CLK_SEL_SHIFT);
	पूर्ण

	/* reset infoframe at end of start-up-sequencer */
	io_ग_लिखो(sd, REG_SUS_SET_RGB2, 0x06);
	io_ग_लिखो(sd, REG_SUS_SET_RGB3, 0x06);

	/* Enable TMDS pull-ups */
	io_ग_लिखो(sd, REG_RT_MAN_CTRL, RT_MAN_CTRL_RT |
		 RT_MAN_CTRL_RT_B | RT_MAN_CTRL_RT_A);

	/* enable sync measurement timing */
	tda1997x_cec_ग_लिखो(sd, REG_PWR_CONTROL & 0xff, 0x04);
	/* adjust CEC घड़ी भागider */
	tda1997x_cec_ग_लिखो(sd, REG_OSC_DIVIDER & 0xff, 0x03);
	tda1997x_cec_ग_लिखो(sd, REG_EN_OSC_PERIOD_LSB & 0xff, 0xa0);
	io_ग_लिखो(sd, REG_TIMER_D, 0x54);
	/* enable घातer चयन */
	reg = tda1997x_cec_पढ़ो(sd, REG_CONTROL & 0xff);
	reg |= 0x20;
	tda1997x_cec_ग_लिखो(sd, REG_CONTROL & 0xff, reg);
	mdelay(50);

	/* पढ़ो the chip version */
	reg = io_पढ़ो(sd, REG_VERSION);
	/* get the chip configuration */
	reg = io_पढ़ो(sd, REG_CMTP_REG10);

	/* enable पूर्णांकerrupts we care about */
	io_ग_लिखो(sd, REG_INT_MASK_TOP,
		 INTERRUPT_HDCP | INTERRUPT_AUDIO | INTERRUPT_INFO |
		 INTERRUPT_RATE | INTERRUPT_SUS);
	/* config_mtp,fmt,sus_end,sus_st */
	io_ग_लिखो(sd, REG_INT_MASK_SUS, MASK_MPT | MASK_FMT | MASK_SUS_END);
	/* rate stability change क्रम inमाला_दो A/B */
	io_ग_लिखो(sd, REG_INT_MASK_RATE, MASK_RATE_B_ST | MASK_RATE_A_ST);
	/* aud,spd,avi*/
	io_ग_लिखो(sd, REG_INT_MASK_INFO,
		 MASK_AUD_IF | MASK_SPD_IF | MASK_AVI_IF);
	/* audio_freq,audio_flg,mute_flg,fअगरo_err */
	io_ग_लिखो(sd, REG_INT_MASK_AUDIO,
		 MASK_AUDIO_FREQ_FLG | MASK_AUDIO_FLG | MASK_MUTE_FLG |
		 MASK_ERROR_FIFO_PT);
	/* HDCP C5 state reached */
	io_ग_लिखो(sd, REG_INT_MASK_HDCP, MASK_STATE_C5);
	/* 5V detect and HDP pulse end */
	io_ग_लिखो(sd, REG_INT_MASK_DDC, MASK_DET_5V);
	/* करोn't care about AFE/MODE */
	io_ग_लिखो(sd, REG_INT_MASK_AFE, 0);
	io_ग_लिखो(sd, REG_INT_MASK_MODE, 0);

	/* clear all पूर्णांकerrupts */
	io_ग_लिखो(sd, REG_INT_FLG_CLR_TOP, 0xff);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_SUS, 0xff);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_DDC, 0xff);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_RATE, 0xff);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_MODE, 0xff);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_INFO, 0xff);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_AUDIO, 0xff);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_HDCP, 0xff);
	io_ग_लिखो(sd, REG_INT_FLG_CLR_AFE, 0xff);

	/* init TMDS equalizer */
	अगर (state->chip_revision == 0)
		io_ग_लिखो(sd, REG_CGU_DBG_SEL, 1 << CGU_DBG_CLK_SEL_SHIFT);
	io_ग_लिखो24(sd, REG_CLK_MIN_RATE, CLK_MIN_RATE);
	io_ग_लिखो24(sd, REG_CLK_MAX_RATE, CLK_MAX_RATE);
	अगर (state->chip_revision == 0)
		io_ग_लिखो(sd, REG_WDL_CFG, WDL_CFG_VAL);
	/* DC filter */
	io_ग_लिखो(sd, REG_DEEP_COLOR_CTRL, DC_FILTER_VAL);
	/* disable test pattern */
	io_ग_लिखो(sd, REG_SVC_MODE, 0x00);
	/* update HDMI INFO CTRL */
	io_ग_लिखो(sd, REG_INFO_CTRL, 0xff);
	/* ग_लिखो HDMI INFO EXCEED value */
	io_ग_लिखो(sd, REG_INFO_EXCEED, 3);

	अगर (state->chip_revision == 0)
		tda1997x_reset_n1(state);

	/*
	 * No HDCP acknowledge when HDCP is disabled
	 * and reset SUS to क्रमce क्रमmat detection
	 */
	tda1997x_hdmi_info_reset(sd, NACK_HDCP, true);

	/* Set HPD low */
	tda1997x_manual_hpd(sd, HPD_LOW_BP);

	/* Configure receiver capabilities */
	io_ग_लिखो(sd, REG_HDCP_BCAPS, HDCP_HDMI | HDCP_FAST_REAUTH);

	/* Configure HDMI: Auto HDCP mode, packet controlled mute */
	reg = HDMI_CTRL_MUTE_AUTO << HDMI_CTRL_MUTE_SHIFT;
	reg |= HDMI_CTRL_HDCP_AUTO << HDMI_CTRL_HDCP_SHIFT;
	io_ग_लिखो(sd, REG_HDMI_CTRL, reg);

	/* reset start-up-sequencer to क्रमce क्रमmat detection */
	tda1997x_hdmi_info_reset(sd, 0, true);

	/* disable matrix conversion */
	reg = io_पढ़ो(sd, REG_VDP_CTRL);
	reg |= VDP_CTRL_MATRIX_BP;
	io_ग_लिखो(sd, REG_VDP_CTRL, reg);

	/* set video output mode */
	tda1997x_configure_viकरोut(state);

	/* configure video output port */
	क्रम (i = 0; i < 9; i++) अणु
		v4l_dbg(1, debug, state->client, "vidout_cfg[%d]=0x%02x\n", i,
			pdata->viकरोut_port_cfg[i]);
		io_ग_लिखो(sd, REG_VP35_32_CTRL + i, pdata->viकरोut_port_cfg[i]);
	पूर्ण

	/* configure audio output port */
	tda1997x_configure_auकरोut(sd, 0);

	/* configure audio घड़ी freq */
	चयन (pdata->auकरोut_mclk_fs) अणु
	हाल 512:
		reg = AUDIO_CLOCK_SEL_512FS;
		अवरोध;
	हाल 256:
		reg = AUDIO_CLOCK_SEL_256FS;
		अवरोध;
	हाल 128:
		reg = AUDIO_CLOCK_SEL_128FS;
		अवरोध;
	हाल 64:
		reg = AUDIO_CLOCK_SEL_64FS;
		अवरोध;
	हाल 32:
		reg = AUDIO_CLOCK_SEL_32FS;
		अवरोध;
	शेष:
		reg = AUDIO_CLOCK_SEL_16FS;
		अवरोध;
	पूर्ण
	io_ग_लिखो(sd, REG_AUDIO_CLOCK, reg);

	/* reset advanced infoframes (ISRC1/ISRC2/ACP) */
	tda1997x_hdmi_info_reset(sd, RESET_AI, false);
	/* reset infoframe */
	tda1997x_hdmi_info_reset(sd, RESET_IF, false);
	/* reset audio infoframes */
	tda1997x_hdmi_info_reset(sd, RESET_AUDIO, false);
	/* reset gamut */
	tda1997x_hdmi_info_reset(sd, RESET_GAMUT, false);

	/* get initial HDMI status */
	state->hdmi_status = io_पढ़ो(sd, REG_HDMI_FLAGS);

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_set_घातer(काष्ठा tda1997x_state *state, bool on)
अणु
	पूर्णांक ret = 0;

	अगर (on) अणु
		ret = regulator_bulk_enable(TDA1997X_NUM_SUPPLIES,
					     state->supplies);
		msleep(300);
	पूर्ण अन्यथा अणु
		ret = regulator_bulk_disable(TDA1997X_NUM_SUPPLIES,
					     state->supplies);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tda1997x_i2c_id[] = अणु
	अणु"tda19971", (kernel_uदीर्घ_t)&tda1997x_chip_info[TDA19971]पूर्ण,
	अणु"tda19973", (kernel_uदीर्घ_t)&tda1997x_chip_info[TDA19973]पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tda1997x_i2c_id);

अटल स्थिर काष्ठा of_device_id tda1997x_of_id[] __maybe_unused = अणु
	अणु .compatible = "nxp,tda19971", .data = &tda1997x_chip_info[TDA19971] पूर्ण,
	अणु .compatible = "nxp,tda19973", .data = &tda1997x_chip_info[TDA19973] पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tda1997x_of_id);

अटल पूर्णांक tda1997x_parse_dt(काष्ठा tda1997x_state *state)
अणु
	काष्ठा tda1997x_platक्रमm_data *pdata = &state->pdata;
	काष्ठा v4l2_fwnode_endpoपूर्णांक bus_cfg = अणु .bus_type = 0 पूर्ण;
	काष्ठा device_node *ep;
	काष्ठा device_node *np;
	अचिन्हित पूर्णांक flags;
	स्थिर अक्षर *str;
	पूर्णांक ret;
	u32 v;

	/*
	 * setup शेष values:
	 * - HREF: active high from start to end of row
	 * - VS: Vertical Sync active high at beginning of frame
	 * - DE: Active high when data valid
	 * - A_CLK: 128*Fs
	 */
	pdata->viकरोut_sel_hs = HS_HREF_SEL_HREF_VHREF;
	pdata->viकरोut_sel_vs = VS_VREF_SEL_VREF_HDMI;
	pdata->viकरोut_sel_de = DE_FREF_SEL_DE_VHREF;

	np = state->client->dev.of_node;
	ep = of_graph_get_next_endpoपूर्णांक(np, शून्य);
	अगर (!ep)
		वापस -EINVAL;

	ret = v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(ep), &bus_cfg);
	अगर (ret) अणु
		of_node_put(ep);
		वापस ret;
	पूर्ण
	of_node_put(ep);
	pdata->viकरोut_bus_type = bus_cfg.bus_type;

	/* polarity of HS/VS/DE */
	flags = bus_cfg.bus.parallel.flags;
	अगर (flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		pdata->viकरोut_inv_hs = 1;
	अगर (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		pdata->viकरोut_inv_vs = 1;
	अगर (flags & V4L2_MBUS_DATA_ACTIVE_LOW)
		pdata->viकरोut_inv_de = 1;
	pdata->viकरोut_bus_width = bus_cfg.bus.parallel.bus_width;

	/* video output port config */
	ret = of_property_count_u32_elems(np, "nxp,vidout-portcfg");
	अगर (ret > 0) अणु
		u32 reg, val, i;

		क्रम (i = 0; i < ret / 2 && i < 9; i++) अणु
			of_property_पढ़ो_u32_index(np, "nxp,vidout-portcfg",
						   i * 2, &reg);
			of_property_पढ़ो_u32_index(np, "nxp,vidout-portcfg",
						   i * 2 + 1, &val);
			अगर (reg < 9)
				pdata->viकरोut_port_cfg[reg] = val;
		पूर्ण
	पूर्ण अन्यथा अणु
		v4l_err(state->client, "nxp,vidout-portcfg missing\n");
		वापस -EINVAL;
	पूर्ण

	/* शेष to channel layout dictated by packet header */
	pdata->auकरोut_layoutस्वतः = true;

	pdata->auकरोut_क्रमmat = AUDFMT_TYPE_DISABLED;
	अगर (!of_property_पढ़ो_string(np, "nxp,audout-format", &str)) अणु
		अगर (म_भेद(str, "i2s") == 0)
			pdata->auकरोut_क्रमmat = AUDFMT_TYPE_I2S;
		अन्यथा अगर (म_भेद(str, "spdif") == 0)
			pdata->auकरोut_क्रमmat = AUDFMT_TYPE_SPDIF;
		अन्यथा अणु
			v4l_err(state->client, "nxp,audout-format invalid\n");
			वापस -EINVAL;
		पूर्ण
		अगर (!of_property_पढ़ो_u32(np, "nxp,audout-layout", &v)) अणु
			चयन (v) अणु
			हाल 0:
			हाल 1:
				अवरोध;
			शेष:
				v4l_err(state->client,
					"nxp,audout-layout invalid\n");
				वापस -EINVAL;
			पूर्ण
			pdata->auकरोut_layout = v;
		पूर्ण
		अगर (!of_property_पढ़ो_u32(np, "nxp,audout-width", &v)) अणु
			चयन (v) अणु
			हाल 16:
			हाल 32:
				अवरोध;
			शेष:
				v4l_err(state->client,
					"nxp,audout-width invalid\n");
				वापस -EINVAL;
			पूर्ण
			pdata->auकरोut_width = v;
		पूर्ण
		अगर (!of_property_पढ़ो_u32(np, "nxp,audout-mclk-fs", &v)) अणु
			चयन (v) अणु
			हाल 512:
			हाल 256:
			हाल 128:
			हाल 64:
			हाल 32:
			हाल 16:
				अवरोध;
			शेष:
				v4l_err(state->client,
					"nxp,audout-mclk-fs invalid\n");
				वापस -EINVAL;
			पूर्ण
			pdata->auकरोut_mclk_fs = v;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda1997x_get_regulators(काष्ठा tda1997x_state *state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TDA1997X_NUM_SUPPLIES; i++)
		state->supplies[i].supply = tda1997x_supply_name[i];

	वापस devm_regulator_bulk_get(&state->client->dev,
				       TDA1997X_NUM_SUPPLIES,
				       state->supplies);
पूर्ण

अटल पूर्णांक tda1997x_identअगरy_module(काष्ठा tda1997x_state *state)
अणु
	काष्ठा v4l2_subdev *sd = &state->sd;
	क्रमागत tda1997x_type type;
	u8 reg;

	/* Read chip configuration*/
	reg = io_पढ़ो(sd, REG_CMTP_REG10);
	state->पंचांगdsb_clk = (reg >> 6) & 0x01; /* use पंचांगds घड़ी B_inv क्रम B */
	state->पंचांगdsb_soc = (reg >> 5) & 0x01; /* पंचांगds of input B */
	state->port_30bit = (reg >> 2) & 0x03; /* 30bit vs 24bit */
	state->output_2p5 = (reg >> 1) & 0x01; /* output supply 2.5v */
	चयन ((reg >> 4) & 0x03) अणु
	हाल 0x00:
		type = TDA19971;
		अवरोध;
	हाल 0x02:
	हाल 0x03:
		type = TDA19973;
		अवरोध;
	शेष:
		dev_err(&state->client->dev, "unsupported chip ID\n");
		वापस -EIO;
	पूर्ण
	अगर (state->info->type != type) अणु
		dev_err(&state->client->dev, "chip id mismatch\n");
		वापस -EIO;
	पूर्ण

	/* पढ़ो chip revision */
	state->chip_revision = io_पढ़ो(sd, REG_CMTP_REG11);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा media_entity_operations tda1997x_media_ops = अणु
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;


/* -----------------------------------------------------------------------------
 * HDMI Audio Codec
 */

/* refine sample-rate based on HDMI source */
अटल पूर्णांक tda1997x_pcm_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tda1997x_state *state = snd_soc_dai_get_drvdata(dai);
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_pcm_runसमय *rtd = substream->runसमय;
	पूर्णांक rate, err;

	rate = state->audio_samplerate;
	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(rtd, SNDRV_PCM_HW_PARAM_RATE,
					   rate, rate);
	अगर (err < 0) अणु
		dev_err(component->dev, "failed to constrain samplerate to %dHz\n",
			rate);
		वापस err;
	पूर्ण
	dev_info(component->dev, "set samplerate constraint to %dHz\n", rate);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tda1997x_dai_ops = अणु
	.startup = tda1997x_pcm_startup,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tda1997x_audio_dai = अणु
	.name = "tda1997x",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
			 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |
			 SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |
			 SNDRV_PCM_RATE_192000,
	पूर्ण,
	.ops = &tda1997x_dai_ops,
पूर्ण;

अटल पूर्णांक tda1997x_codec_probe(काष्ठा snd_soc_component *component)
अणु
	वापस 0;
पूर्ण

अटल व्योम tda1997x_codec_हटाओ(काष्ठा snd_soc_component *component)
अणु
पूर्ण

अटल काष्ठा snd_soc_component_driver tda1997x_codec_driver = अणु
	.probe			= tda1997x_codec_probe,
	.हटाओ			= tda1997x_codec_हटाओ,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक tda1997x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tda1997x_state *state;
	काष्ठा tda1997x_platक्रमm_data *pdata;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_ctrl_handler *hdl;
	काष्ठा v4l2_ctrl *ctrl;
	अटल स्थिर काष्ठा v4l2_dv_timings cea1920x1080 =
		V4L2_DV_BT_CEA_1920X1080P60;
	u32 *mbus_codes;
	पूर्णांक i, ret;

	/* Check अगर the adapter supports the needed features */
	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	state = kzalloc(माप(काष्ठा tda1997x_state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	state->client = client;
	pdata = &state->pdata;
	अगर (IS_ENABLED(CONFIG_OF) && client->dev.of_node) अणु
		स्थिर काष्ठा of_device_id *oid;

		oid = of_match_node(tda1997x_of_id, client->dev.of_node);
		state->info = oid->data;

		ret = tda1997x_parse_dt(state);
		अगर (ret < 0) अणु
			v4l_err(client, "DT parsing error\n");
			जाओ err_मुक्त_state;
		पूर्ण
	पूर्ण अन्यथा अगर (client->dev.platक्रमm_data) अणु
		काष्ठा tda1997x_platक्रमm_data *pdata =
			client->dev.platक्रमm_data;
		state->info =
			(स्थिर काष्ठा tda1997x_chip_info *)id->driver_data;
		state->pdata = *pdata;
	पूर्ण अन्यथा अणु
		v4l_err(client, "No platform data\n");
		ret = -ENODEV;
		जाओ err_मुक्त_state;
	पूर्ण

	ret = tda1997x_get_regulators(state);
	अगर (ret)
		जाओ err_मुक्त_state;

	ret = tda1997x_set_घातer(state, 1);
	अगर (ret)
		जाओ err_मुक्त_state;

	mutex_init(&state->page_lock);
	mutex_init(&state->lock);
	state->page = 0xff;

	INIT_DELAYED_WORK(&state->delayed_work_enable_hpd,
			  tda1997x_delayed_work_enable_hpd);

	/* set video क्रमmat based on chip and bus width */
	ret = tda1997x_identअगरy_module(state);
	अगर (ret)
		जाओ err_मुक्त_mutex;

	/* initialize subdev */
	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &tda1997x_subdev_ops);
	snम_लिखो(sd->name, माप(sd->name), "%s %d-%04x",
		 id->name, i2c_adapter_id(client->adapter),
		 client->addr);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
	sd->entity.function = MEDIA_ENT_F_DV_DECODER;
	sd->entity.ops = &tda1997x_media_ops;

	/* set allowed mbus modes based on chip, bus-type, and bus-width */
	i = 0;
	mbus_codes = state->mbus_codes;
	चयन (state->info->type) अणु
	हाल TDA19973:
		चयन (pdata->viकरोut_bus_type) अणु
		हाल V4L2_MBUS_PARALLEL:
			चयन (pdata->viकरोut_bus_width) अणु
			हाल 36:
				mbus_codes[i++] = MEDIA_BUS_FMT_RGB121212_1X36;
				mbus_codes[i++] = MEDIA_BUS_FMT_YUV12_1X36;
				fallthrough;
			हाल 24:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY12_1X24;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल V4L2_MBUS_BT656:
			चयन (pdata->viकरोut_bus_width) अणु
			हाल 36:
			हाल 24:
			हाल 12:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY12_2X12;
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY10_2X10;
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY8_2X8;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल TDA19971:
		चयन (pdata->viकरोut_bus_type) अणु
		हाल V4L2_MBUS_PARALLEL:
			चयन (pdata->viकरोut_bus_width) अणु
			हाल 24:
				mbus_codes[i++] = MEDIA_BUS_FMT_RGB888_1X24;
				mbus_codes[i++] = MEDIA_BUS_FMT_YUV8_1X24;
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY12_1X24;
				fallthrough;
			हाल 20:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY10_1X20;
				fallthrough;
			हाल 16:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY8_1X16;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल V4L2_MBUS_BT656:
			चयन (pdata->viकरोut_bus_width) अणु
			हाल 24:
			हाल 20:
			हाल 16:
			हाल 12:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY12_2X12;
				fallthrough;
			हाल 10:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY10_2X10;
				fallthrough;
			हाल 8:
				mbus_codes[i++] = MEDIA_BUS_FMT_UYVY8_2X8;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (WARN_ON(i > ARRAY_SIZE(state->mbus_codes))) अणु
		ret = -EINVAL;
		जाओ err_मुक्त_mutex;
	पूर्ण

	/* शेष क्रमmat */
	tda1997x_setup_क्रमmat(state, state->mbus_codes[0]);
	state->timings = cea1920x1080;

	/*
	 * शेष to SRGB full range quantization
	 * (in हाल we करोn't get an infoframe such as DVI संकेत
	 */
	state->colorimetry.colorspace = V4L2_COLORSPACE_SRGB;
	state->colorimetry.quantization = V4L2_QUANTIZATION_FULL_RANGE;

	/* disable/reset HDCP to get correct I2C access to Rx HDMI */
	io_ग_लिखो(sd, REG_MAN_SUS_HDMI_SEL, MAN_RST_HDCP | MAN_DIS_HDCP);

	/*
	 * अगर N2 version, reset compdel_bp as it may generate some small pixel
	 * shअगरts in हाल of embedded sync/or delay lower than 4
	 */
	अगर (state->chip_revision != 0) अणु
		io_ग_लिखो(sd, REG_MAN_SUS_HDMI_SEL, 0x00);
		io_ग_लिखो(sd, REG_VDP_CTRL, 0x1f);
	पूर्ण

	v4l_info(client, "NXP %s N%d detected\n", state->info->name,
		 state->chip_revision + 1);
	v4l_info(client, "video: %dbit %s %d formats available\n",
		pdata->viकरोut_bus_width,
		(pdata->viकरोut_bus_type == V4L2_MBUS_PARALLEL) ?
			"parallel" : "BT656",
		i);
	अगर (pdata->auकरोut_क्रमmat) अणु
		v4l_info(client, "audio: %dch %s layout%d sysclk=%d*fs\n",
			 pdata->auकरोut_layout ? 2 : 8,
			 audfmt_names[pdata->auकरोut_क्रमmat],
			 pdata->auकरोut_layout,
			 pdata->auकरोut_mclk_fs);
	पूर्ण

	ret = 0x34 + ((io_पढ़ो(sd, REG_SLAVE_ADDR)>>4) & 0x03);
	state->client_cec = devm_i2c_new_dummy_device(&client->dev,
						      client->adapter, ret);
	अगर (IS_ERR(state->client_cec)) अणु
		ret = PTR_ERR(state->client_cec);
		जाओ err_मुक्त_mutex;
	पूर्ण

	v4l_info(client, "CEC slave address 0x%02x\n", ret);

	ret = tda1997x_core_init(sd);
	अगर (ret)
		जाओ err_मुक्त_mutex;

	/* control handlers */
	hdl = &state->hdl;
	v4l2_ctrl_handler_init(hdl, 3);
	ctrl = v4l2_ctrl_new_std_menu(hdl, &tda1997x_ctrl_ops,
			V4L2_CID_DV_RX_IT_CONTENT_TYPE,
			V4L2_DV_IT_CONTENT_TYPE_NO_ITC, 0,
			V4L2_DV_IT_CONTENT_TYPE_NO_ITC);
	अगर (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;
	/* custom controls */
	state->detect_tx_5v_ctrl = v4l2_ctrl_new_std(hdl, शून्य,
			V4L2_CID_DV_RX_POWER_PRESENT, 0, 1, 0, 0);
	state->rgb_quantization_range_ctrl = v4l2_ctrl_new_std_menu(hdl,
			&tda1997x_ctrl_ops,
			V4L2_CID_DV_RX_RGB_RANGE, V4L2_DV_RGB_RANGE_FULL, 0,
			V4L2_DV_RGB_RANGE_AUTO);
	state->sd.ctrl_handler = hdl;
	अगर (hdl->error) अणु
		ret = hdl->error;
		जाओ err_मुक्त_handler;
	पूर्ण
	v4l2_ctrl_handler_setup(hdl);

	/* initialize source pads */
	state->pads[TDA1997X_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&sd->entity, TDA1997X_NUM_PADS,
		state->pads);
	अगर (ret) अणु
		v4l_err(client, "failed entity_init: %d", ret);
		जाओ err_मुक्त_handler;
	पूर्ण

	ret = v4l2_async_रेजिस्टर_subdev(sd);
	अगर (ret)
		जाओ err_मुक्त_media;

	/* रेजिस्टर audio DAI */
	अगर (pdata->auकरोut_क्रमmat) अणु
		u64 क्रमmats;

		अगर (pdata->auकरोut_width == 32)
			क्रमmats = SNDRV_PCM_FMTBIT_S32_LE;
		अन्यथा
			क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
		tda1997x_audio_dai.capture.क्रमmats = क्रमmats;
		ret = devm_snd_soc_रेजिस्टर_component(&state->client->dev,
					     &tda1997x_codec_driver,
					     &tda1997x_audio_dai, 1);
		अगर (ret) अणु
			dev_err(&client->dev, "register audio codec failed\n");
			जाओ err_मुक्त_media;
		पूर्ण
		dev_set_drvdata(&state->client->dev, state);
		v4l_info(state->client, "registered audio codec\n");
	पूर्ण

	/* request irq */
	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, tda1997x_isr_thपढ़ो,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					KBUILD_MODNAME, state);
	अगर (ret) अणु
		v4l_err(client, "irq%d reg failed: %d\n", client->irq, ret);
		जाओ err_मुक्त_media;
	पूर्ण

	वापस 0;

err_मुक्त_media:
	media_entity_cleanup(&sd->entity);
err_मुक्त_handler:
	v4l2_ctrl_handler_मुक्त(&state->hdl);
err_मुक्त_mutex:
	cancel_delayed_work(&state->delayed_work_enable_hpd);
	mutex_destroy(&state->page_lock);
	mutex_destroy(&state->lock);
err_मुक्त_state:
	kमुक्त(state);
	dev_err(&client->dev, "%s failed: %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक tda1997x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा tda1997x_state *state = to_state(sd);
	काष्ठा tda1997x_platक्रमm_data *pdata = &state->pdata;

	अगर (pdata->auकरोut_क्रमmat) अणु
		mutex_destroy(&state->audio_lock);
	पूर्ण

	disable_irq(state->client->irq);
	tda1997x_घातer_mode(state, 0);

	v4l2_async_unरेजिस्टर_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_मुक्त(&state->hdl);
	regulator_bulk_disable(TDA1997X_NUM_SUPPLIES, state->supplies);
	cancel_delayed_work_sync(&state->delayed_work_enable_hpd);
	mutex_destroy(&state->page_lock);
	mutex_destroy(&state->lock);

	kमुक्त(state);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver tda1997x_i2c_driver = अणु
	.driver = अणु
		.name = "tda1997x",
		.of_match_table = of_match_ptr(tda1997x_of_id),
	पूर्ण,
	.probe = tda1997x_probe,
	.हटाओ = tda1997x_हटाओ,
	.id_table = tda1997x_i2c_id,
पूर्ण;

module_i2c_driver(tda1997x_i2c_driver);

MODULE_AUTHOR("Tim Harvey <tharvey@gateworks.com>");
MODULE_DESCRIPTION("TDA1997X HDMI Receiver driver");
MODULE_LICENSE("GPL v2");
