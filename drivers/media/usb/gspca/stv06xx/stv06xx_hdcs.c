<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2001 Jean-Fredric Clere, Nikolas Zimmermann, Georg Acher
 *		      Mark Cave-Ayland, Carlo E Prelz, Dick Streefland
 * Copyright (c) 2002, 2003 Tuukka Toivonen
 * Copyright (c) 2008 Erik Andrथऊn
 * Copyright (c) 2008 Chia-I Wu
 *
 * P/N 861037:      Sensor HDCS1000        ASIC STV0600
 * P/N 861050-0010: Sensor HDCS1000        ASIC STV0600
 * P/N 861050-0020: Sensor Photobit PB100  ASIC STV0600-1 - QuickCam Express
 * P/N 861055:      Sensor ST VV6410       ASIC STV0610   - LEGO cam
 * P/N 861075-0040: Sensor HDCS1000        ASIC
 * P/N 961179-0700: Sensor ST VV6410       ASIC STV0602   - Dexxa WebCam USB
 * P/N 861040-0000: Sensor ST VV6410       ASIC STV0610   - QuickCam Web
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "stv06xx_hdcs.h"

अटल काष्ठा v4l2_pix_क्रमmat hdcs1x00_mode[] = अणु
	अणु
		HDCS_1X00_DEF_WIDTH,
		HDCS_1X00_DEF_HEIGHT,
		V4L2_PIX_FMT_SGRBG8,
		V4L2_FIELD_NONE,
		.sizeimage =
			HDCS_1X00_DEF_WIDTH * HDCS_1X00_DEF_HEIGHT,
		.bytesperline = HDCS_1X00_DEF_WIDTH,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1
	पूर्ण
पूर्ण;

अटल काष्ठा v4l2_pix_क्रमmat hdcs1020_mode[] = अणु
	अणु
		HDCS_1020_DEF_WIDTH,
		HDCS_1020_DEF_HEIGHT,
		V4L2_PIX_FMT_SGRBG8,
		V4L2_FIELD_NONE,
		.sizeimage =
			HDCS_1020_DEF_WIDTH * HDCS_1020_DEF_HEIGHT,
		.bytesperline = HDCS_1020_DEF_WIDTH,
		.colorspace = V4L2_COLORSPACE_SRGB,
		.priv = 1
	पूर्ण
पूर्ण;

क्रमागत hdcs_घातer_state अणु
	HDCS_STATE_SLEEP,
	HDCS_STATE_IDLE,
	HDCS_STATE_RUN
पूर्ण;

/* no lock? */
काष्ठा hdcs अणु
	क्रमागत hdcs_घातer_state state;
	पूर्णांक w, h;

	/* visible area of the sensor array */
	काष्ठा अणु
		पूर्णांक left, top;
		पूर्णांक width, height;
		पूर्णांक border;
	पूर्ण array;

	काष्ठा अणु
		/* Column timing overhead */
		u8 cto;
		/* Column processing overhead */
		u8 cpo;
		/* Row sample period स्थिरant */
		u16 rs;
		/* Exposure reset duration */
		u16 er;
	पूर्ण exp;

	पूर्णांक psmp;
पूर्ण;

अटल पूर्णांक hdcs_reg_ग_लिखो_seq(काष्ठा sd *sd, u8 reg, u8 *vals, u8 len)
अणु
	u8 regs[I2C_MAX_BYTES * 2];
	पूर्णांक i;

	अगर (unlikely((len <= 0) || (len >= I2C_MAX_BYTES) ||
		     (reg + len > 0xff)))
		वापस -EINVAL;

	क्रम (i = 0; i < len; i++) अणु
		regs[2 * i] = reg;
		regs[2 * i + 1] = vals[i];
		/* All addresses are shअगरted left one bit
		 * as bit 0 toggles r/w */
		reg += 2;
	पूर्ण

	वापस stv06xx_ग_लिखो_sensor_bytes(sd, regs, len);
पूर्ण

अटल पूर्णांक hdcs_set_state(काष्ठा sd *sd, क्रमागत hdcs_घातer_state state)
अणु
	काष्ठा hdcs *hdcs = sd->sensor_priv;
	u8 val;
	पूर्णांक ret;

	अगर (hdcs->state == state)
		वापस 0;

	/* we need to go idle beक्रमe running or sleeping */
	अगर (hdcs->state != HDCS_STATE_IDLE) अणु
		ret = stv06xx_ग_लिखो_sensor(sd, HDCS_REG_CONTROL(sd), 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	hdcs->state = HDCS_STATE_IDLE;

	अगर (state == HDCS_STATE_IDLE)
		वापस 0;

	चयन (state) अणु
	हाल HDCS_STATE_SLEEP:
		val = HDCS_SLEEP_MODE;
		अवरोध;

	हाल HDCS_STATE_RUN:
		val = HDCS_RUN_ENABLE;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = stv06xx_ग_लिखो_sensor(sd, HDCS_REG_CONTROL(sd), val);

	/* Update the state अगर the ग_लिखो succeeded */
	अगर (!ret)
		hdcs->state = state;

	वापस ret;
पूर्ण

अटल पूर्णांक hdcs_reset(काष्ठा sd *sd)
अणु
	काष्ठा hdcs *hdcs = sd->sensor_priv;
	पूर्णांक err;

	err = stv06xx_ग_लिखो_sensor(sd, HDCS_REG_CONTROL(sd), 1);
	अगर (err < 0)
		वापस err;

	err = stv06xx_ग_लिखो_sensor(sd, HDCS_REG_CONTROL(sd), 0);
	अगर (err < 0)
		hdcs->state = HDCS_STATE_IDLE;

	वापस err;
पूर्ण

अटल पूर्णांक hdcs_set_exposure(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;
	काष्ठा hdcs *hdcs = sd->sensor_priv;
	पूर्णांक rowexp, srowexp;
	पूर्णांक max_srowexp;
	/* Column समय period */
	पूर्णांक ct;
	/* Column processing period */
	पूर्णांक cp;
	/* Row processing period */
	पूर्णांक rp;
	/* Minimum number of column timing periods
	   within the column processing period */
	पूर्णांक mnct;
	पूर्णांक cycles, err;
	u8 exp[14];

	cycles = val * HDCS_CLK_FREQ_MHZ * 257;

	ct = hdcs->exp.cto + hdcs->psmp + (HDCS_ADC_START_SIG_DUR + 2);
	cp = hdcs->exp.cto + (hdcs->w * ct / 2);

	/* the cycles one row takes */
	rp = hdcs->exp.rs + cp;

	rowexp = cycles / rp;

	/* the reमुख्यing cycles */
	cycles -= rowexp * rp;

	/* calculate sub-row exposure */
	अगर (IS_1020(sd)) अणु
		/* see HDCS-1020 datasheet 3.5.6.4, p. 63 */
		srowexp = hdcs->w - (cycles + hdcs->exp.er + 13) / ct;

		mnct = (hdcs->exp.er + 12 + ct - 1) / ct;
		max_srowexp = hdcs->w - mnct;
	पूर्ण अन्यथा अणु
		/* see HDCS-1000 datasheet 3.4.5.5, p. 61 */
		srowexp = cp - hdcs->exp.er - 6 - cycles;

		mnct = (hdcs->exp.er + 5 + ct - 1) / ct;
		max_srowexp = cp - mnct * ct - 1;
	पूर्ण

	अगर (srowexp < 0)
		srowexp = 0;
	अन्यथा अगर (srowexp > max_srowexp)
		srowexp = max_srowexp;

	अगर (IS_1020(sd)) अणु
		exp[0] = HDCS20_CONTROL;
		exp[1] = 0x00;		/* Stop streaming */
		exp[2] = HDCS_ROWEXPL;
		exp[3] = rowexp & 0xff;
		exp[4] = HDCS_ROWEXPH;
		exp[5] = rowexp >> 8;
		exp[6] = HDCS20_SROWEXP;
		exp[7] = (srowexp >> 2) & 0xff;
		exp[8] = HDCS20_ERROR;
		exp[9] = 0x10;		/* Clear exposure error flag*/
		exp[10] = HDCS20_CONTROL;
		exp[11] = 0x04;		/* Restart streaming */
		err = stv06xx_ग_लिखो_sensor_bytes(sd, exp, 6);
	पूर्ण अन्यथा अणु
		exp[0] = HDCS00_CONTROL;
		exp[1] = 0x00;         /* Stop streaming */
		exp[2] = HDCS_ROWEXPL;
		exp[3] = rowexp & 0xff;
		exp[4] = HDCS_ROWEXPH;
		exp[5] = rowexp >> 8;
		exp[6] = HDCS00_SROWEXPL;
		exp[7] = srowexp & 0xff;
		exp[8] = HDCS00_SROWEXPH;
		exp[9] = srowexp >> 8;
		exp[10] = HDCS_STATUS;
		exp[11] = 0x10;         /* Clear exposure error flag*/
		exp[12] = HDCS00_CONTROL;
		exp[13] = 0x04;         /* Restart streaming */
		err = stv06xx_ग_लिखो_sensor_bytes(sd, exp, 7);
		अगर (err < 0)
			वापस err;
	पूर्ण
	gspca_dbg(gspca_dev, D_CONF, "Writing exposure %d, rowexp %d, srowexp %d\n",
		  val, rowexp, srowexp);
	वापस err;
पूर्ण

अटल पूर्णांक hdcs_set_gains(काष्ठा sd *sd, u8 g)
अणु
	पूर्णांक err;
	u8 gains[4];

	/* the voltage gain Av = (1 + 19 * val / 127) * (1 + bit7) */
	अगर (g > 127)
		g = 0x80 | (g / 2);

	gains[0] = g;
	gains[1] = g;
	gains[2] = g;
	gains[3] = g;

	err = hdcs_reg_ग_लिखो_seq(sd, HDCS_ERECPGA, gains, 4);
	वापस err;
पूर्ण

अटल पूर्णांक hdcs_set_gain(काष्ठा gspca_dev *gspca_dev, __s32 val)
अणु
	gspca_dbg(gspca_dev, D_CONF, "Writing gain %d\n", val);
	वापस hdcs_set_gains((काष्ठा sd *) gspca_dev,
			       val & 0xff);
पूर्ण

अटल पूर्णांक hdcs_set_size(काष्ठा sd *sd,
		अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	काष्ठा hdcs *hdcs = sd->sensor_priv;
	u8 win[4];
	अचिन्हित पूर्णांक x, y;
	पूर्णांक err;

	/* must be multiple of 4 */
	width = (width + 3) & ~0x3;
	height = (height + 3) & ~0x3;

	अगर (width > hdcs->array.width)
		width = hdcs->array.width;

	अगर (IS_1020(sd)) अणु
		/* the borders are also invalid */
		अगर (height + 2 * hdcs->array.border + HDCS_1020_BOTTOM_Y_SKIP
				  > hdcs->array.height)
			height = hdcs->array.height - 2 * hdcs->array.border -
				HDCS_1020_BOTTOM_Y_SKIP;

		y = (hdcs->array.height - HDCS_1020_BOTTOM_Y_SKIP - height) / 2
				+ hdcs->array.top;
	पूर्ण अन्यथा अणु
		अगर (height > hdcs->array.height)
			height = hdcs->array.height;

		y = hdcs->array.top + (hdcs->array.height - height) / 2;
	पूर्ण

	x = hdcs->array.left + (hdcs->array.width - width) / 2;

	win[0] = y / 4;
	win[1] = x / 4;
	win[2] = (y + height) / 4 - 1;
	win[3] = (x + width) / 4 - 1;

	err = hdcs_reg_ग_लिखो_seq(sd, HDCS_FWROW, win, 4);
	अगर (err < 0)
		वापस err;

	/* Update the current width and height */
	hdcs->w = width;
	hdcs->h = height;
	वापस err;
पूर्ण

अटल पूर्णांक hdcs_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा gspca_dev *gspca_dev =
		container_of(ctrl->handler, काष्ठा gspca_dev, ctrl_handler);
	पूर्णांक err = -EINVAL;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_GAIN:
		err = hdcs_set_gain(gspca_dev, ctrl->val);
		अवरोध;
	हाल V4L2_CID_EXPOSURE:
		err = hdcs_set_exposure(gspca_dev, ctrl->val);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops hdcs_ctrl_ops = अणु
	.s_ctrl = hdcs_s_ctrl,
पूर्ण;

अटल पूर्णांक hdcs_init_controls(काष्ठा sd *sd)
अणु
	काष्ठा v4l2_ctrl_handler *hdl = &sd->gspca_dev.ctrl_handler;

	v4l2_ctrl_handler_init(hdl, 2);
	v4l2_ctrl_new_std(hdl, &hdcs_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 0xff, 1, HDCS_DEFAULT_EXPOSURE);
	v4l2_ctrl_new_std(hdl, &hdcs_ctrl_ops,
			V4L2_CID_GAIN, 0, 0xff, 1, HDCS_DEFAULT_GAIN);
	वापस hdl->error;
पूर्ण

अटल पूर्णांक hdcs_probe_1x00(काष्ठा sd *sd)
अणु
	काष्ठा hdcs *hdcs;
	u16 sensor;
	पूर्णांक ret;

	ret = stv06xx_पढ़ो_sensor(sd, HDCS_IDENT, &sensor);
	अगर (ret < 0 || sensor != 0x08)
		वापस -ENODEV;

	pr_info("HDCS-1000/1100 sensor detected\n");

	sd->gspca_dev.cam.cam_mode = hdcs1x00_mode;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(hdcs1x00_mode);

	hdcs = kदो_स्मृति(माप(काष्ठा hdcs), GFP_KERNEL);
	अगर (!hdcs)
		वापस -ENOMEM;

	hdcs->array.left = 8;
	hdcs->array.top = 8;
	hdcs->array.width = HDCS_1X00_DEF_WIDTH;
	hdcs->array.height = HDCS_1X00_DEF_HEIGHT;
	hdcs->array.border = 4;

	hdcs->exp.cto = 4;
	hdcs->exp.cpo = 2;
	hdcs->exp.rs = 186;
	hdcs->exp.er = 100;

	/*
	 * Frame rate on HDCS-1000 with STV600 depends on PSMP:
	 *  4 = करोesn't work at all
	 *  5 = 7.8 fps,
	 *  6 = 6.9 fps,
	 *  8 = 6.3 fps,
	 * 10 = 5.5 fps,
	 * 15 = 4.4 fps,
	 * 31 = 2.8 fps
	 *
	 * Frame rate on HDCS-1000 with STV602 depends on PSMP:
	 * 15 = करोesn't work at all
	 * 18 = करोesn't work at all
	 * 19 = 7.3 fps
	 * 20 = 7.4 fps
	 * 21 = 7.4 fps
	 * 22 = 7.4 fps
	 * 24 = 6.3 fps
	 * 30 = 5.4 fps
	 */
	hdcs->psmp = (sd->bridge == BRIDGE_STV602) ? 20 : 5;

	sd->sensor_priv = hdcs;

	वापस 0;
पूर्ण

अटल पूर्णांक hdcs_probe_1020(काष्ठा sd *sd)
अणु
	काष्ठा hdcs *hdcs;
	u16 sensor;
	पूर्णांक ret;

	ret = stv06xx_पढ़ो_sensor(sd, HDCS_IDENT, &sensor);
	अगर (ret < 0 || sensor != 0x10)
		वापस -ENODEV;

	pr_info("HDCS-1020 sensor detected\n");

	sd->gspca_dev.cam.cam_mode = hdcs1020_mode;
	sd->gspca_dev.cam.nmodes = ARRAY_SIZE(hdcs1020_mode);

	hdcs = kदो_स्मृति(माप(काष्ठा hdcs), GFP_KERNEL);
	अगर (!hdcs)
		वापस -ENOMEM;

	/*
	 * From Andrey's test image: looks like HDCS-1020 upper-left
	 * visible pixel is at 24,8 (y maybe even smaller?) and lower-right
	 * visible pixel at 375,299 (x maybe even larger?)
	 */
	hdcs->array.left = 24;
	hdcs->array.top  = 4;
	hdcs->array.width = HDCS_1020_DEF_WIDTH;
	hdcs->array.height = 304;
	hdcs->array.border = 4;

	hdcs->psmp = 6;

	hdcs->exp.cto = 3;
	hdcs->exp.cpo = 3;
	hdcs->exp.rs = 155;
	hdcs->exp.er = 96;

	sd->sensor_priv = hdcs;

	वापस 0;
पूर्ण

अटल पूर्णांक hdcs_start(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	gspca_dbg(gspca_dev, D_STREAM, "Starting stream\n");

	वापस hdcs_set_state(sd, HDCS_STATE_RUN);
पूर्ण

अटल पूर्णांक hdcs_stop(काष्ठा sd *sd)
अणु
	काष्ठा gspca_dev *gspca_dev = (काष्ठा gspca_dev *)sd;

	gspca_dbg(gspca_dev, D_STREAM, "Halting stream\n");

	वापस hdcs_set_state(sd, HDCS_STATE_SLEEP);
पूर्ण

अटल पूर्णांक hdcs_init(काष्ठा sd *sd)
अणु
	काष्ठा hdcs *hdcs = sd->sensor_priv;
	पूर्णांक i, err = 0;

	/* Set the STV0602AA in STV0600 emulation mode */
	अगर (sd->bridge == BRIDGE_STV602)
		stv06xx_ग_लिखो_bridge(sd, STV_STV0600_EMULATION, 1);

	/* Execute the bridge init */
	क्रम (i = 0; i < ARRAY_SIZE(stv_bridge_init) && !err; i++) अणु
		err = stv06xx_ग_लिखो_bridge(sd, stv_bridge_init[i][0],
					   stv_bridge_init[i][1]);
	पूर्ण
	अगर (err < 0)
		वापस err;

	/* sensor soft reset */
	hdcs_reset(sd);

	/* Execute the sensor init */
	क्रम (i = 0; i < ARRAY_SIZE(stv_sensor_init) && !err; i++) अणु
		err = stv06xx_ग_लिखो_sensor(sd, stv_sensor_init[i][0],
					     stv_sensor_init[i][1]);
	पूर्ण
	अगर (err < 0)
		वापस err;

	/* Enable continuous frame capture, bit 2: stop when frame complete */
	err = stv06xx_ग_लिखो_sensor(sd, HDCS_REG_CONFIG(sd), BIT(3));
	अगर (err < 0)
		वापस err;

	/* Set PGA sample duration
	(was 0x7E क्रम the STV602, but caused slow framerate with HDCS-1020) */
	अगर (IS_1020(sd))
		err = stv06xx_ग_लिखो_sensor(sd, HDCS_TCTRL,
				(HDCS_ADC_START_SIG_DUR << 6) | hdcs->psmp);
	अन्यथा
		err = stv06xx_ग_लिखो_sensor(sd, HDCS_TCTRL,
				(HDCS_ADC_START_SIG_DUR << 5) | hdcs->psmp);
	अगर (err < 0)
		वापस err;

	वापस hdcs_set_size(sd, hdcs->array.width, hdcs->array.height);
पूर्ण

अटल पूर्णांक hdcs_dump(काष्ठा sd *sd)
अणु
	u16 reg, val;

	pr_info("Dumping sensor registers:\n");

	क्रम (reg = HDCS_IDENT; reg <= HDCS_ROWEXPH; reg++) अणु
		stv06xx_पढ़ो_sensor(sd, reg, &val);
		pr_info("reg 0x%02x = 0x%02x\n", reg, val);
	पूर्ण
	वापस 0;
पूर्ण
