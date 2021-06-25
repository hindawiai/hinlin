<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Programming the mspx4xx sound processor family
 *
 * (c) 1997-2001 Gerd Knorr <kraxel@bytesex.org>
 *
 * what works and what करोesn't:
 *
 *  AM-Mono
 *      Support क्रम Hauppauge cards added (decoding handled by tuner) added by
 *      Frederic Crozat <fcrozat@mail.करोtcom.fr>
 *
 *  FM-Mono
 *      should work. The stereo modes are backward compatible to FM-mono,
 *      thereक्रमe FM-Mono should be always available.
 *
 *  FM-Stereo (B/G, used in germany)
 *      should work, with स्वतःdetect
 *
 *  FM-Stereo (satellite)
 *      should work, no स्वतःdetect (i.e. शेष is mono, but you can
 *      चयन to stereo -- untested)
 *
 *  NICAM (B/G, L , used in UK, Scandinavia, Spain and France)
 *      should work, with स्वतःdetect. Support क्रम NICAM was added by
 *      Pekka Pietikainen <pp@netppl.fi>
 *
 * TODO:
 *   - better SAT support
 *
 * 980623  Thomas Sailer (sailer@अगरe.ee.ethz.ch)
 *         using soundcore instead of OSS
 */


#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/drv-पूर्णांकf/msp3400.h>
#समावेश <media/i2c/tvaudपन.स>
#समावेश "msp3400-driver.h"

/* ---------------------------------------------------------------------- */

MODULE_DESCRIPTION("device driver for msp34xx TV sound processor");
MODULE_AUTHOR("Gerd Knorr");
MODULE_LICENSE("GPL");

/* module parameters */
अटल पूर्णांक opmode   = OPMODE_AUTO;
पूर्णांक msp_debug;		 /* msp_debug output */
bool msp_once;		 /* no continuous stereo monitoring */
bool msp_amsound;	 /* hard-wire AM sound at 6.5 Hz (france),
			    the स्वतःscan seems work well only with FM... */
पूर्णांक msp_standard = 1;    /* Override स्वतः detect of audio msp_standard,
			    अगर needed. */
bool msp_करोlby;

पूर्णांक msp_stereo_thresh = 0x190; /* a2 threshold क्रम stereo/bilingual
					(msp34xxg only) 0x00a0-0x03c0 */

/* पढ़ो-only */
module_param(opmode,           पूर्णांक, 0444);

/* पढ़ो-ग_लिखो */
module_param_named(once, msp_once,                      bool, 0644);
module_param_named(debug, msp_debug,                    पूर्णांक,  0644);
module_param_named(stereo_threshold, msp_stereo_thresh, पूर्णांक,  0644);
module_param_named(standard, msp_standard,              पूर्णांक,  0644);
module_param_named(amsound, msp_amsound,                bool, 0644);
module_param_named(करोlby, msp_करोlby,                    bool, 0644);

MODULE_PARM_DESC(opmode, "Forces a MSP3400 opmode. 0=Manual, 1=Autodetect, 2=Autodetect and autoselect");
MODULE_PARM_DESC(once, "No continuous stereo monitoring");
MODULE_PARM_DESC(debug, "Enable debug messages [0-3]");
MODULE_PARM_DESC(stereo_threshold, "Sets signal threshold to activate stereo");
MODULE_PARM_DESC(standard, "Specify audio standard: 32 = NTSC, 64 = radio, Default: Autodetect");
MODULE_PARM_DESC(amsound, "Hardwire AM sound at 6.5Hz (France), FM can autoscan");
MODULE_PARM_DESC(करोlby, "Activates Dolby processing");

/* ---------------------------------------------------------------------- */

/* control subaddress */
#घोषणा I2C_MSP_CONTROL 0x00
/* demodulator unit subaddress */
#घोषणा I2C_MSP_DEM     0x10
/* DSP unit subaddress */
#घोषणा I2C_MSP_DSP     0x12


/* ----------------------------------------------------------------------- */
/* functions क्रम talking to the MSP3400C Sound processor                   */

पूर्णांक msp_reset(काष्ठा i2c_client *client)
अणु
	/* reset and पढ़ो revision code */
	अटल u8 reset_off[3] = अणु I2C_MSP_CONTROL, 0x80, 0x00 पूर्ण;
	अटल u8 reset_on[3]  = अणु I2C_MSP_CONTROL, 0x00, 0x00 पूर्ण;
	अटल u8 ग_लिखो[3]     = अणु I2C_MSP_DSP + 1, 0x00, 0x1e पूर्ण;
	u8 पढ़ो[2];
	काष्ठा i2c_msg reset[2] = अणु
		अणु
			.addr = client->addr,
			.flags = I2C_M_IGNORE_NAK,
			.len = 3,
			.buf = reset_off
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_IGNORE_NAK,
			.len = 3,
			.buf = reset_on
		पूर्ण,
	पूर्ण;
	काष्ठा i2c_msg test[2] = अणु
		अणु
			.addr = client->addr,
			.len = 3,
			.buf = ग_लिखो
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 2,
			.buf = पढ़ो
		पूर्ण,
	पूर्ण;

	dev_dbg_lvl(&client->dev, 3, msp_debug, "msp_reset\n");
	अगर (i2c_transfer(client->adapter, &reset[0], 1) != 1 ||
	    i2c_transfer(client->adapter, &reset[1], 1) != 1 ||
	    i2c_transfer(client->adapter, test, 2) != 2) अणु
		dev_err(&client->dev, "chip reset failed\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msp_पढ़ो(काष्ठा i2c_client *client, पूर्णांक dev, पूर्णांक addr)
अणु
	पूर्णांक err, retval;
	u8 ग_लिखो[3];
	u8 पढ़ो[2];
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = client->addr,
			.len = 3,
			.buf = ग_लिखो
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 2,
			.buf = पढ़ो
		पूर्ण
	पूर्ण;

	ग_लिखो[0] = dev + 1;
	ग_लिखो[1] = addr >> 8;
	ग_लिखो[2] = addr & 0xff;

	क्रम (err = 0; err < 3; err++) अणु
		अगर (i2c_transfer(client->adapter, msgs, 2) == 2)
			अवरोध;
		dev_warn(&client->dev, "I/O error #%d (read 0x%02x/0x%02x)\n", err,
		       dev, addr);
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(10));
	पूर्ण
	अगर (err == 3) अणु
		dev_warn(&client->dev, "resetting chip, sound will go off.\n");
		msp_reset(client);
		वापस -1;
	पूर्ण
	retval = पढ़ो[0] << 8 | पढ़ो[1];
	dev_dbg_lvl(&client->dev, 3, msp_debug, "msp_read(0x%x, 0x%x): 0x%x\n",
			dev, addr, retval);
	वापस retval;
पूर्ण

पूर्णांक msp_पढ़ो_dem(काष्ठा i2c_client *client, पूर्णांक addr)
अणु
	वापस msp_पढ़ो(client, I2C_MSP_DEM, addr);
पूर्ण

पूर्णांक msp_पढ़ो_dsp(काष्ठा i2c_client *client, पूर्णांक addr)
अणु
	वापस msp_पढ़ो(client, I2C_MSP_DSP, addr);
पूर्ण

अटल पूर्णांक msp_ग_लिखो(काष्ठा i2c_client *client, पूर्णांक dev, पूर्णांक addr, पूर्णांक val)
अणु
	पूर्णांक err;
	u8 buffer[5];

	buffer[0] = dev;
	buffer[1] = addr >> 8;
	buffer[2] = addr &  0xff;
	buffer[3] = val  >> 8;
	buffer[4] = val  &  0xff;

	dev_dbg_lvl(&client->dev, 3, msp_debug, "msp_write(0x%x, 0x%x, 0x%x)\n",
			dev, addr, val);
	क्रम (err = 0; err < 3; err++) अणु
		अगर (i2c_master_send(client, buffer, 5) == 5)
			अवरोध;
		dev_warn(&client->dev, "I/O error #%d (write 0x%02x/0x%02x)\n", err,
		       dev, addr);
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(10));
	पूर्ण
	अगर (err == 3) अणु
		dev_warn(&client->dev, "resetting chip, sound will go off.\n");
		msp_reset(client);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक msp_ग_लिखो_dem(काष्ठा i2c_client *client, पूर्णांक addr, पूर्णांक val)
अणु
	वापस msp_ग_लिखो(client, I2C_MSP_DEM, addr, val);
पूर्ण

पूर्णांक msp_ग_लिखो_dsp(काष्ठा i2c_client *client, पूर्णांक addr, पूर्णांक val)
अणु
	वापस msp_ग_लिखो(client, I2C_MSP_DSP, addr, val);
पूर्ण

/* ----------------------------------------------------------------------- *
 * bits  9  8  5 - SCART DSP input Select:
 *       0  0  0 - SCART 1 to DSP input (reset position)
 *       0  1  0 - MONO to DSP input
 *       1  0  0 - SCART 2 to DSP input
 *       1  1  1 - Mute DSP input
 *
 * bits 11 10  6 - SCART 1 Output Select:
 *       0  0  0 - undefined (reset position)
 *       0  1  0 - SCART 2 Input to SCART 1 Output (क्रम devices with 2 SCARTS)
 *       1  0  0 - MONO input to SCART 1 Output
 *       1  1  0 - SCART 1 DA to SCART 1 Output
 *       0  0  1 - SCART 2 DA to SCART 1 Output
 *       0  1  1 - SCART 1 Input to SCART 1 Output
 *       1  1  1 - Mute SCART 1 Output
 *
 * bits 13 12  7 - SCART 2 Output Select (क्रम devices with 2 Output SCART):
 *       0  0  0 - SCART 1 DA to SCART 2 Output (reset position)
 *       0  1  0 - SCART 1 Input to SCART 2 Output
 *       1  0  0 - MONO input to SCART 2 Output
 *       0  0  1 - SCART 2 DA to SCART 2 Output
 *       0  1  1 - SCART 2 Input to SCART 2 Output
 *       1  1  0 - Mute SCART 2 Output
 *
 * Bits 4 to 0 should be zero.
 * ----------------------------------------------------------------------- */

अटल पूर्णांक scarts[3][9] = अणु
	/* MASK   IN1     IN2     IN3     IN4     IN1_DA  IN2_DA  MONO    MUTE   */
	/* SCART DSP Input select */
	अणु 0x0320, 0x0000, 0x0200, 0x0300, 0x0020, -1,     -1,     0x0100, 0x0320 पूर्ण,
	/* SCART1 Output select */
	अणु 0x0c40, 0x0440, 0x0400, 0x0000, 0x0840, 0x0c00, 0x0040, 0x0800, 0x0c40 पूर्ण,
	/* SCART2 Output select */
	अणु 0x3080, 0x1000, 0x1080, 0x2080, 0x3080, 0x0000, 0x0080, 0x2000, 0x3000 पूर्ण,
पूर्ण;

अटल अक्षर *scart_names[] = अणु
	"in1", "in2", "in3", "in4", "in1 da", "in2 da", "mono", "mute"
पूर्ण;

व्योम msp_set_scart(काष्ठा i2c_client *client, पूर्णांक in, पूर्णांक out)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));

	state->in_scart = in;

	अगर (in >= 0 && in <= 7 && out >= 0 && out <= 2) अणु
		अगर (-1 == scarts[out][in + 1])
			वापस;

		state->acb &= ~scarts[out][0];
		state->acb |=  scarts[out][in + 1];
	पूर्ण अन्यथा
		state->acb = 0xf60; /* Mute Input and SCART 1 Output */

	dev_dbg_lvl(&client->dev, 1, msp_debug, "scart switch: %s => %d (ACB=0x%04x)\n",
					scart_names[in], out, state->acb);
	msp_ग_लिखो_dsp(client, 0x13, state->acb);

	/* Sets I2S speed 0 = 1.024 Mbps, 1 = 2.048 Mbps */
	अगर (state->has_i2s_conf)
		msp_ग_लिखो_dem(client, 0x40, state->i2s_mode);
पूर्ण

/* ------------------------------------------------------------------------ */

अटल व्योम msp_wake_thपढ़ो(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));

	अगर (शून्य == state->kthपढ़ो)
		वापस;
	state->watch_stereo = 0;
	state->restart = 1;
	wake_up_पूर्णांकerruptible(&state->wq);
पूर्ण

पूर्णांक msp_sleep(काष्ठा msp_state *state, पूर्णांक समयout)
अणु
	DECLARE_WAITQUEUE(रुको, current);

	add_रुको_queue(&state->wq, &रुको);
	अगर (!kthपढ़ो_should_stop()) अणु
		अगर (समयout < 0) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			schedule();
		पूर्ण अन्यथा अणु
			schedule_समयout_पूर्णांकerruptible
						(msecs_to_jअगरfies(समयout));
		पूर्ण
	पूर्ण

	हटाओ_रुको_queue(&state->wq, &रुको);
	try_to_मुक्तze();
	वापस state->restart;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक msp_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा msp_state *state = ctrl_to_state(ctrl);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&state->sd);
	पूर्णांक val = ctrl->val;

	चयन (ctrl->id) अणु
	हाल V4L2_CID_AUDIO_VOLUME: अणु
		/* audio volume cluster */
		पूर्णांक reallymuted = state->muted->val | state->scan_in_progress;

		अगर (!reallymuted)
			val = (val * 0x7f / 65535) << 8;

		dev_dbg_lvl(&client->dev, 1, msp_debug, "mute=%s scanning=%s volume=%d\n",
				state->muted->val ? "on" : "off",
				state->scan_in_progress ? "yes" : "no",
				state->volume->val);

		msp_ग_लिखो_dsp(client, 0x0000, val);
		msp_ग_लिखो_dsp(client, 0x0007, reallymuted ? 0x1 : (val | 0x1));
		अगर (state->has_scart2_out_volume)
			msp_ग_लिखो_dsp(client, 0x0040, reallymuted ? 0x1 : (val | 0x1));
		अगर (state->has_headphones)
			msp_ग_लिखो_dsp(client, 0x0006, val);
		अवरोध;
	पूर्ण

	हाल V4L2_CID_AUDIO_BASS:
		val = ((val - 32768) * 0x60 / 65535) << 8;
		msp_ग_लिखो_dsp(client, 0x0002, val);
		अगर (state->has_headphones)
			msp_ग_लिखो_dsp(client, 0x0031, val);
		अवरोध;

	हाल V4L2_CID_AUDIO_TREBLE:
		val = ((val - 32768) * 0x60 / 65535) << 8;
		msp_ग_लिखो_dsp(client, 0x0003, val);
		अगर (state->has_headphones)
			msp_ग_लिखो_dsp(client, 0x0032, val);
		अवरोध;

	हाल V4L2_CID_AUDIO_LOUDNESS:
		val = val ? ((5 * 4) << 8) : 0;
		msp_ग_लिखो_dsp(client, 0x0004, val);
		अगर (state->has_headphones)
			msp_ग_लिखो_dsp(client, 0x0033, val);
		अवरोध;

	हाल V4L2_CID_AUDIO_BALANCE:
		val = (u8)((val / 256) - 128);
		msp_ग_लिखो_dsp(client, 0x0001, val << 8);
		अगर (state->has_headphones)
			msp_ग_लिखो_dsp(client, 0x0030, val << 8);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम msp_update_volume(काष्ठा msp_state *state)
अणु
	/* Force an update of the volume/mute cluster */
	v4l2_ctrl_lock(state->volume);
	state->volume->val = state->volume->cur.val;
	state->muted->val = state->muted->cur.val;
	msp_s_ctrl(state->volume);
	v4l2_ctrl_unlock(state->volume);
पूर्ण

/* --- v4l2 ioctls --- */
अटल पूर्णांक msp_s_radio(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा msp_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (state->radio)
		वापस 0;
	state->radio = 1;
	dev_dbg_lvl(&client->dev, 1, msp_debug, "switching to radio mode\n");
	state->watch_stereo = 0;
	चयन (state->opmode) अणु
	हाल OPMODE_MANUAL:
		/* set msp3400 to FM radio mode */
		msp3400c_set_mode(client, MSP_MODE_FM_RADIO);
		msp3400c_set_carrier(client, MSP_CARRIER(10.7),
				MSP_CARRIER(10.7));
		msp_update_volume(state);
		अवरोध;
	हाल OPMODE_AUTODETECT:
	हाल OPMODE_AUTOSELECT:
		/* the thपढ़ो will करो क्रम us */
		msp_wake_thपढ़ो(client);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msp_s_frequency(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_frequency *freq)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	/* new channel -- kick audio carrier scan */
	msp_wake_thपढ़ो(client);
	वापस 0;
पूर्ण

अटल पूर्णांक msp_querystd(काष्ठा v4l2_subdev *sd, v4l2_std_id *id)
अणु
	काष्ठा msp_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	*id &= state->detected_std;

	dev_dbg_lvl(&client->dev, 2, msp_debug,
		"detected standard: %s(0x%08Lx)\n",
		msp_standard_std_name(state->std), state->detected_std);

	वापस 0;
पूर्ण

अटल पूर्णांक msp_s_std(काष्ठा v4l2_subdev *sd, v4l2_std_id id)
अणु
	काष्ठा msp_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक update = state->radio || state->v4l2_std != id;

	state->v4l2_std = id;
	state->radio = 0;
	अगर (update)
		msp_wake_thपढ़ो(client);
	वापस 0;
पूर्ण

अटल पूर्णांक msp_s_routing(काष्ठा v4l2_subdev *sd,
			 u32 input, u32 output, u32 config)
अणु
	काष्ठा msp_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	पूर्णांक tuner = (input >> 3) & 1;
	पूर्णांक sc_in = input & 0x7;
	पूर्णांक sc1_out = output & 0xf;
	पूर्णांक sc2_out = (output >> 4) & 0xf;
	u16 val, reg;
	पूर्णांक i;
	पूर्णांक बाह्य_input = 1;

	अगर (state->route_in == input && state->route_out == output)
		वापस 0;
	state->route_in = input;
	state->route_out = output;
	/* check अगर the tuner input is used */
	क्रम (i = 0; i < 5; i++) अणु
		अगर (((input >> (4 + i * 4)) & 0xf) == 0)
			बाह्य_input = 0;
	पूर्ण
	state->mode = बाह्य_input ? MSP_MODE_EXTERN : MSP_MODE_AM_DETECT;
	state->rxsubchans = V4L2_TUNER_SUB_STEREO;
	msp_set_scart(client, sc_in, 0);
	msp_set_scart(client, sc1_out, 1);
	msp_set_scart(client, sc2_out, 2);
	msp_set_audmode(client);
	reg = (state->opmode == OPMODE_AUTOSELECT) ? 0x30 : 0xbb;
	val = msp_पढ़ो_dem(client, reg);
	msp_ग_लिखो_dem(client, reg, (val & ~0x100) | (tuner << 8));
	/* wake thपढ़ो when a new input is chosen */
	msp_wake_thपढ़ो(client);
	वापस 0;
पूर्ण

अटल पूर्णांक msp_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा msp_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (vt->type != V4L2_TUNER_ANALOG_TV)
		वापस 0;
	अगर (!state->radio) अणु
		अगर (state->opmode == OPMODE_AUTOSELECT)
			msp_detect_stereo(client);
		vt->rxsubchans = state->rxsubchans;
	पूर्ण
	vt->audmode = state->audmode;
	vt->capability |= V4L2_TUNER_CAP_STEREO |
		V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2;
	वापस 0;
पूर्ण

अटल पूर्णांक msp_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा msp_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	अगर (state->radio)  /* TODO: add mono/stereo support क्रम radio */
		वापस 0;
	अगर (state->audmode == vt->audmode)
		वापस 0;
	state->audmode = vt->audmode;
	/* only set audmode */
	msp_set_audmode(client);
	वापस 0;
पूर्ण

अटल पूर्णांक msp_s_i2s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq)
अणु
	काष्ठा msp_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);

	dev_dbg_lvl(&client->dev, 1, msp_debug, "Setting I2S speed to %d\n", freq);

	चयन (freq) अणु
		हाल 1024000:
			state->i2s_mode = 0;
			अवरोध;
		हाल 2048000:
			state->i2s_mode = 1;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msp_log_status(काष्ठा v4l2_subdev *sd)
अणु
	काष्ठा msp_state *state = to_state(sd);
	काष्ठा i2c_client *client = v4l2_get_subdevdata(sd);
	स्थिर अक्षर *p;
	अक्षर prefix[V4L2_SUBDEV_NAME_SIZE + 20];

	अगर (state->opmode == OPMODE_AUTOSELECT)
		msp_detect_stereo(client);
	dev_info(&client->dev, "%s rev1 = 0x%04x rev2 = 0x%04x\n",
			client->name, state->rev1, state->rev2);
	snम_लिखो(prefix, माप(prefix), "%s: Audio:    ", sd->name);
	v4l2_ctrl_handler_log_status(&state->hdl, prefix);
	चयन (state->mode) अणु
		हाल MSP_MODE_AM_DETECT: p = "AM (for carrier detect)"; अवरोध;
		हाल MSP_MODE_FM_RADIO: p = "FM Radio"; अवरोध;
		हाल MSP_MODE_FM_TERRA: p = "Terrestrial FM-mono/stereo"; अवरोध;
		हाल MSP_MODE_FM_SAT: p = "Satellite FM-mono"; अवरोध;
		हाल MSP_MODE_FM_NICAM1: p = "NICAM/FM (B/G, D/K)"; अवरोध;
		हाल MSP_MODE_FM_NICAM2: p = "NICAM/FM (I)"; अवरोध;
		हाल MSP_MODE_AM_NICAM: p = "NICAM/AM (L)"; अवरोध;
		हाल MSP_MODE_BTSC: p = "BTSC"; अवरोध;
		हाल MSP_MODE_EXTERN: p = "External input"; अवरोध;
		शेष: p = "unknown"; अवरोध;
	पूर्ण
	अगर (state->mode == MSP_MODE_EXTERN) अणु
		dev_info(&client->dev, "Mode:     %s\n", p);
	पूर्ण अन्यथा अगर (state->opmode == OPMODE_MANUAL) अणु
		dev_info(&client->dev, "Mode:     %s (%s%s)\n", p,
				(state->rxsubchans & V4L2_TUNER_SUB_STEREO) ? "stereo" : "mono",
				(state->rxsubchans & V4L2_TUNER_SUB_LANG2) ? ", dual" : "");
	पूर्ण अन्यथा अणु
		अगर (state->opmode == OPMODE_AUTODETECT)
			dev_info(&client->dev, "Mode:     %s\n", p);
		dev_info(&client->dev, "Standard: %s (%s%s)\n",
				msp_standard_std_name(state->std),
				(state->rxsubchans & V4L2_TUNER_SUB_STEREO) ? "stereo" : "mono",
				(state->rxsubchans & V4L2_TUNER_SUB_LANG2) ? ", dual" : "");
	पूर्ण
	dev_info(&client->dev, "Audmode:  0x%04x\n", state->audmode);
	dev_info(&client->dev, "Routing:  0x%08x (input) 0x%08x (output)\n",
			state->route_in, state->route_out);
	dev_info(&client->dev, "ACB:      0x%04x\n", state->acb);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक msp_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	dev_dbg_lvl(&client->dev, 1, msp_debug, "suspend\n");
	msp_reset(client);
	वापस 0;
पूर्ण

अटल पूर्णांक msp_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	dev_dbg_lvl(&client->dev, 1, msp_debug, "resume\n");
	msp_wake_thपढ़ो(client);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_ctrl_ops msp_ctrl_ops = अणु
	.s_ctrl = msp_s_ctrl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_core_ops msp_core_ops = अणु
	.log_status = msp_log_status,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_video_ops msp_video_ops = अणु
	.s_std = msp_s_std,
	.querystd = msp_querystd,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops msp_tuner_ops = अणु
	.s_frequency = msp_s_frequency,
	.g_tuner = msp_g_tuner,
	.s_tuner = msp_s_tuner,
	.s_radio = msp_s_radio,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_audio_ops msp_audio_ops = अणु
	.s_routing = msp_s_routing,
	.s_i2s_घड़ी_freq = msp_s_i2s_घड़ी_freq,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops msp_ops = अणु
	.core = &msp_core_ops,
	.video = &msp_video_ops,
	.tuner = &msp_tuner_ops,
	.audio = &msp_audio_ops,
पूर्ण;

/* ----------------------------------------------------------------------- */


अटल स्थिर अक्षर * स्थिर opmode_str[] = अणु
	[OPMODE_MANUAL] = "manual",
	[OPMODE_AUTODETECT] = "autodetect",
	[OPMODE_AUTOSELECT] = "autodetect and autoselect",
पूर्ण;

अटल पूर्णांक msp_probe(काष्ठा i2c_client *client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा msp_state *state;
	काष्ठा v4l2_subdev *sd;
	काष्ठा v4l2_ctrl_handler *hdl;
	पूर्णांक (*thपढ़ो_func)(व्योम *data) = शून्य;
	पूर्णांक msp_hard;
	पूर्णांक msp_family;
	पूर्णांक msp_revision;
	पूर्णांक msp_product, msp_prod_hi, msp_prod_lo;
	पूर्णांक msp_rom;
#अगर defined(CONFIG_MEDIA_CONTROLLER)
	पूर्णांक ret;
#पूर्ण_अगर

	अगर (!id)
		strscpy(client->name, "msp3400", माप(client->name));

	अगर (msp_reset(client) == -1) अणु
		dev_dbg_lvl(&client->dev, 1, msp_debug, "msp3400 not found\n");
		वापस -ENODEV;
	पूर्ण

	state = devm_kzalloc(&client->dev, माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	sd = &state->sd;
	v4l2_i2c_subdev_init(sd, client, &msp_ops);

#अगर defined(CONFIG_MEDIA_CONTROLLER)
	state->pads[MSP3400_PAD_IF_INPUT].flags = MEDIA_PAD_FL_SINK;
	state->pads[MSP3400_PAD_IF_INPUT].sig_type = PAD_SIGNAL_AUDIO;
	state->pads[MSP3400_PAD_OUT].flags = MEDIA_PAD_FL_SOURCE;
	state->pads[MSP3400_PAD_OUT].sig_type = PAD_SIGNAL_AUDIO;

	sd->entity.function = MEDIA_ENT_F_IF_AUD_DECODER;

	ret = media_entity_pads_init(&sd->entity, 2, state->pads);
	अगर (ret < 0)
		वापस ret;
#पूर्ण_अगर

	state->v4l2_std = V4L2_STD_NTSC;
	state->detected_std = V4L2_STD_ALL;
	state->audmode = V4L2_TUNER_MODE_STEREO;
	state->input = -1;
	state->i2s_mode = 0;
	init_रुकोqueue_head(&state->wq);
	/* These are the reset input/output positions */
	state->route_in = MSP_INPUT_DEFAULT;
	state->route_out = MSP_OUTPUT_DEFAULT;

	state->rev1 = msp_पढ़ो_dsp(client, 0x1e);
	अगर (state->rev1 != -1)
		state->rev2 = msp_पढ़ो_dsp(client, 0x1f);
	dev_dbg_lvl(&client->dev, 1, msp_debug, "rev1=0x%04x, rev2=0x%04x\n",
			state->rev1, state->rev2);
	अगर (state->rev1 == -1 || (state->rev1 == 0 && state->rev2 == 0)) अणु
		dev_dbg_lvl(&client->dev, 1, msp_debug,
				"not an msp3400 (cannot read chip version)\n");
		वापस -ENODEV;
	पूर्ण

	msp_family = ((state->rev1 >> 4) & 0x0f) + 3;
	msp_product = (state->rev2 >> 8) & 0xff;
	msp_prod_hi = msp_product / 10;
	msp_prod_lo = msp_product % 10;
	msp_revision = (state->rev1 & 0x0f) + '@';
	msp_hard = ((state->rev1 >> 8) & 0xff) + '@';
	msp_rom = state->rev2 & 0x1f;
	/* Rev B=2, C=3, D=4, G=7 */
	state->ident = msp_family * 10000 + 4000 + msp_product * 10 +
			msp_revision - '@';

	/* Has NICAM support: all mspx41x and mspx45x products have NICAM */
	state->has_nicam =
		msp_prod_hi == 1 || msp_prod_hi == 5;
	/* Has radio support: was added with revision G */
	state->has_radio =
		msp_revision >= 'G';
	/* Has headphones output: not क्रम stripped करोwn products */
	state->has_headphones =
		msp_prod_lo < 5;
	/* Has scart2 input: not in stripped करोwn products of the '3' family */
	state->has_scart2 =
		msp_family >= 4 || msp_prod_lo < 7;
	/* Has scart3 input: not in stripped करोwn products of the '3' family */
	state->has_scart3 =
		msp_family >= 4 || msp_prod_lo < 5;
	/* Has scart4 input: not in pre D revisions, not in stripped D revs */
	state->has_scart4 =
		msp_family >= 4 || (msp_revision >= 'D' && msp_prod_lo < 5);
	/* Has scart2 output: not in stripped करोwn products of
	 * the '3' family */
	state->has_scart2_out =
		msp_family >= 4 || msp_prod_lo < 5;
	/* Has scart2 a volume control? Not in pre-D revisions. */
	state->has_scart2_out_volume =
		msp_revision > 'C' && state->has_scart2_out;
	/* Has a configurable i2s out? */
	state->has_i2s_conf =
		msp_revision >= 'G' && msp_prod_lo < 7;
	/* Has subwoofer output: not in pre-D revs and not in stripped करोwn
	 * products */
	state->has_subwoofer =
		msp_revision >= 'D' && msp_prod_lo < 5;
	/* Has soundprocessing (bass/treble/balance/loudness/equalizer):
	 *  not in stripped करोwn products */
	state->has_sound_processing =
		msp_prod_lo < 7;
	/* Has Virtual Dolby Surround: only in msp34x1 */
	state->has_भव_करोlby_surround =
		msp_revision == 'G' && msp_prod_lo == 1;
	/* Has Virtual Dolby Surround & Dolby Pro Logic: only in msp34x2 */
	state->has_करोlby_pro_logic =
		msp_revision == 'G' && msp_prod_lo == 2;
	/* The msp343xG supports BTSC only and cannot करो Automatic Standard
	 * Detection. */
	state->क्रमce_btsc =
		msp_family == 3 && msp_revision == 'G' && msp_prod_hi == 3;

	state->opmode = opmode;
	अगर (state->opmode < OPMODE_MANUAL
	    || state->opmode > OPMODE_AUTOSELECT) अणु
		/* MSP revision G and up have both स्वतःdetect and स्वतःselect */
		अगर (msp_revision >= 'G')
			state->opmode = OPMODE_AUTOSELECT;
		/* MSP revision D and up have स्वतःdetect */
		अन्यथा अगर (msp_revision >= 'D')
			state->opmode = OPMODE_AUTODETECT;
		अन्यथा
			state->opmode = OPMODE_MANUAL;
	पूर्ण

	hdl = &state->hdl;
	v4l2_ctrl_handler_init(hdl, 6);
	अगर (state->has_sound_processing) अणु
		v4l2_ctrl_new_std(hdl, &msp_ctrl_ops,
			V4L2_CID_AUDIO_BASS, 0, 65535, 65535 / 100, 32768);
		v4l2_ctrl_new_std(hdl, &msp_ctrl_ops,
			V4L2_CID_AUDIO_TREBLE, 0, 65535, 65535 / 100, 32768);
		v4l2_ctrl_new_std(hdl, &msp_ctrl_ops,
			V4L2_CID_AUDIO_LOUDNESS, 0, 1, 1, 0);
	पूर्ण
	state->volume = v4l2_ctrl_new_std(hdl, &msp_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, 0, 65535, 65535 / 100, 58880);
	v4l2_ctrl_new_std(hdl, &msp_ctrl_ops,
			V4L2_CID_AUDIO_BALANCE, 0, 65535, 65535 / 100, 32768);
	state->muted = v4l2_ctrl_new_std(hdl, &msp_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 0);
	sd->ctrl_handler = hdl;
	अगर (hdl->error) अणु
		पूर्णांक err = hdl->error;

		v4l2_ctrl_handler_मुक्त(hdl);
		वापस err;
	पूर्ण

	v4l2_ctrl_cluster(2, &state->volume);
	v4l2_ctrl_handler_setup(hdl);

	dev_info(&client->dev,
		 "MSP%d4%02d%c-%c%d found on %s: supports %s%s%s, mode is %s\n",
		 msp_family, msp_product,
		 msp_revision, msp_hard, msp_rom,
		 client->adapter->name,
		 (state->has_nicam) ? "nicam" : "",
		 (state->has_nicam && state->has_radio) ? " and " : "",
		 (state->has_radio) ? "radio" : "",
		 opmode_str[state->opmode]);

	/* version-specअगरic initialization */
	चयन (state->opmode) अणु
	हाल OPMODE_MANUAL:
		thपढ़ो_func = msp3400c_thपढ़ो;
		अवरोध;
	हाल OPMODE_AUTODETECT:
		thपढ़ो_func = msp3410d_thपढ़ो;
		अवरोध;
	हाल OPMODE_AUTOSELECT:
		thपढ़ो_func = msp34xxg_thपढ़ो;
		अवरोध;
	पूर्ण

	/* startup control thपढ़ो अगर needed */
	अगर (thपढ़ो_func) अणु
		state->kthपढ़ो = kthपढ़ो_run(thपढ़ो_func, client, "msp34xx");

		अगर (IS_ERR(state->kthपढ़ो))
			dev_warn(&client->dev, "kernel_thread() failed\n");
		msp_wake_thपढ़ो(client);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msp_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा msp_state *state = to_state(i2c_get_clientdata(client));

	v4l2_device_unरेजिस्टर_subdev(&state->sd);
	/* shutकरोwn control thपढ़ो */
	अगर (state->kthपढ़ो) अणु
		state->restart = 1;
		kthपढ़ो_stop(state->kthपढ़ो);
	पूर्ण
	msp_reset(client);

	v4l2_ctrl_handler_मुक्त(&state->hdl);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा dev_pm_ops msp3400_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(msp_suspend, msp_resume)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id msp_id[] = अणु
	अणु "msp3400", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, msp_id);

अटल काष्ठा i2c_driver msp_driver = अणु
	.driver = अणु
		.name	= "msp3400",
		.pm	= &msp3400_pm_ops,
	पूर्ण,
	.probe		= msp_probe,
	.हटाओ		= msp_हटाओ,
	.id_table	= msp_id,
पूर्ण;

module_i2c_driver(msp_driver);
