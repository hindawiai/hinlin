<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Support क्रम OR51211 (pcHDTV HD-2000) - VSB
 *
 *    Copyright (C) 2005 Kirk Lapray <kirk_lapray@bigfoot.com>
 *
 *    Based on code from Jack Kelliher (kelliher@xmission.com)
 *                           Copyright (C) 2002 & pcHDTV, inc.
*/

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": %s: " fmt, __func__

/*
 * This driver needs बाह्यal firmware. Please use the command
 * "<kerneldir>/scripts/get_dvb_firmware or51211" to
 * करोwnload/extract it, and then copy it to /usr/lib/hotplug/firmware
 * or /lib/firmware (depending on configuration of firmware hotplug).
 */
#घोषणा OR51211_DEFAULT_FIRMWARE "dvb-fe-or51211.fw"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <media/dvb_गणित.स>
#समावेश <media/dvb_frontend.h>
#समावेश "or51211.h"

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु अगर (debug) pr_debug(args); पूर्ण जबतक (0)

अटल u8 run_buf[] = अणु0x7f,0x01पूर्ण;
अटल u8 cmd_buf[] = अणु0x04,0x01,0x50,0x80,0x06पूर्ण; // ATSC

काष्ठा or51211_state अणु

	काष्ठा i2c_adapter* i2c;

	/* Configuration settings */
	स्थिर काष्ठा or51211_config* config;

	काष्ठा dvb_frontend frontend;
	काष्ठा bt878* bt;

	/* Demodulator निजी data */
	u8 initialized:1;
	u32 snr; /* Result of last SNR calculation */

	/* Tuner निजी data */
	u32 current_frequency;
पूर्ण;

अटल पूर्णांक i2c_ग_लिखोbytes (काष्ठा or51211_state* state, u8 reg, स्थिर u8 *buf,
			   पूर्णांक len)
अणु
	पूर्णांक err;
	काष्ठा i2c_msg msg;
	msg.addr	= reg;
	msg.flags	= 0;
	msg.len		= len;
	msg.buf		= (u8 *)buf;

	अगर ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) अणु
		pr_warn("error (addr %02x, err == %i)\n", reg, err);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_पढ़ोbytes(काष्ठा or51211_state *state, u8 reg, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक err;
	काष्ठा i2c_msg msg;
	msg.addr	= reg;
	msg.flags	= I2C_M_RD;
	msg.len		= len;
	msg.buf		= buf;

	अगर ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) अणु
		pr_warn("error (addr %02x, err == %i)\n", reg, err);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक or51211_load_firmware (काष्ठा dvb_frontend* fe,
				  स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा or51211_state* state = fe->demodulator_priv;
	u8 tudata[585];
	पूर्णांक i;

	dprपूर्णांकk("Firmware is %zu bytes\n", fw->size);

	/* Get eprom data */
	tudata[0] = 17;
	अगर (i2c_ग_लिखोbytes(state,0x50,tudata,1)) अणु
		pr_warn("error eprom addr\n");
		वापस -1;
	पूर्ण
	अगर (i2c_पढ़ोbytes(state,0x50,&tudata[145],192)) अणु
		pr_warn("error eprom\n");
		वापस -1;
	पूर्ण

	/* Create firmware buffer */
	क्रम (i = 0; i < 145; i++)
		tudata[i] = fw->data[i];

	क्रम (i = 0; i < 248; i++)
		tudata[i+337] = fw->data[145+i];

	state->config->reset(fe);

	अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,tudata,585)) अणु
		pr_warn("error 1\n");
		वापस -1;
	पूर्ण
	msleep(1);

	अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,
			   &fw->data[393],8125)) अणु
		pr_warn("error 2\n");
		वापस -1;
	पूर्ण
	msleep(1);

	अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,run_buf,2)) अणु
		pr_warn("error 3\n");
		वापस -1;
	पूर्ण

	/* Wait at least 5 msec */
	msleep(10);
	अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,run_buf,2)) अणु
		pr_warn("error 4\n");
		वापस -1;
	पूर्ण
	msleep(10);

	pr_info("Done.\n");
	वापस 0;
पूर्ण;

अटल पूर्णांक or51211_seपंचांगode(काष्ठा dvb_frontend* fe, पूर्णांक mode)
अणु
	काष्ठा or51211_state* state = fe->demodulator_priv;
	u8 rec_buf[14];

	state->config->seपंचांगode(fe, mode);

	अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,run_buf,2)) अणु
		pr_warn("error 1\n");
		वापस -1;
	पूर्ण

	/* Wait at least 5 msec */
	msleep(10);
	अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,run_buf,2)) अणु
		pr_warn("error 2\n");
		वापस -1;
	पूर्ण

	msleep(10);

	/* Set operation mode in Receiver 1 रेजिस्टर;
	 * type 1:
	 * data 0x50h  Automatic sets receiver channel conditions
	 *             Automatic NTSC rejection filter
	 *             Enable  MPEG serial data output
	 *             MPEG2tr
	 *             High tuner phase noise
	 *             normal +/-150kHz Carrier acquisition range
	 */
	अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,cmd_buf,3)) अणु
		pr_warn("error 3\n");
		वापस -1;
	पूर्ण

	rec_buf[0] = 0x04;
	rec_buf[1] = 0x00;
	rec_buf[2] = 0x03;
	rec_buf[3] = 0x00;
	msleep(20);
	अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,rec_buf,3)) अणु
		pr_warn("error 5\n");
	पूर्ण
	msleep(3);
	अगर (i2c_पढ़ोbytes(state,state->config->demod_address,&rec_buf[10],2)) अणु
		pr_warn("error 6\n");
		वापस -1;
	पूर्ण
	dprपूर्णांकk("rec status %02x %02x\n", rec_buf[10], rec_buf[11]);

	वापस 0;
पूर्ण

अटल पूर्णांक or51211_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा or51211_state* state = fe->demodulator_priv;

	/* Change only अगर we are actually changing the channel */
	अगर (state->current_frequency != p->frequency) अणु
		अगर (fe->ops.tuner_ops.set_params) अणु
			fe->ops.tuner_ops.set_params(fe);
			अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
		पूर्ण

		/* Set to ATSC mode */
		or51211_seपंचांगode(fe,0);

		/* Update current frequency */
		state->current_frequency = p->frequency;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक or51211_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा or51211_state* state = fe->demodulator_priv;
	अचिन्हित अक्षर rec_buf[2];
	अचिन्हित अक्षर snd_buf[] = अणु0x04,0x00,0x03,0x00पूर्ण;
	*status = 0;

	/* Receiver Status */
	अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,snd_buf,3)) अणु
		pr_warn("write error\n");
		वापस -1;
	पूर्ण
	msleep(3);
	अगर (i2c_पढ़ोbytes(state,state->config->demod_address,rec_buf,2)) अणु
		pr_warn("read error\n");
		वापस -1;
	पूर्ण
	dprपूर्णांकk("%x %x\n", rec_buf[0], rec_buf[1]);

	अगर (rec_buf[0] &  0x01) अणु /* Receiver Lock */
		*status |= FE_HAS_SIGNAL;
		*status |= FE_HAS_CARRIER;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_LOCK;
	पूर्ण
	वापस 0;
पूर्ण

/* Calculate SNR estimation (scaled by 2^24)

   8-VSB SNR equation from Oren datasheets

   For 8-VSB:
     SNR[dB] = 10 * log10(219037.9454 / MSE^2 )

   We re-ग_लिखो the snr equation as:
     SNR * 2^24 = 10*(c - 2*पूर्णांकlog10(MSE))
   Where क्रम 8-VSB, c = log10(219037.9454) * 2^24 */

अटल u32 calculate_snr(u32 mse, u32 c)
अणु
	अगर (mse == 0) /* No संकेत */
		वापस 0;

	mse = 2*पूर्णांकlog10(mse);
	अगर (mse > c) अणु
		/* Negative SNR, which is possible, but realisticly the
		demod will lose lock beक्रमe the संकेत माला_लो this bad.  The
		API only allows क्रम अचिन्हित values, so just वापस 0 */
		वापस 0;
	पूर्ण
	वापस 10*(c - mse);
पूर्ण

अटल पूर्णांक or51211_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा or51211_state* state = fe->demodulator_priv;
	u8 rec_buf[2];
	u8 snd_buf[3];

	/* SNR after Equalizer */
	snd_buf[0] = 0x04;
	snd_buf[1] = 0x00;
	snd_buf[2] = 0x04;

	अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,snd_buf,3)) अणु
		pr_warn("error writing snr reg\n");
		वापस -1;
	पूर्ण
	अगर (i2c_पढ़ोbytes(state,state->config->demod_address,rec_buf,2)) अणु
		pr_warn("read_status read error\n");
		वापस -1;
	पूर्ण

	state->snr = calculate_snr(rec_buf[0], 89599047);
	*snr = (state->snr) >> 16;

	dprपूर्णांकk("noise = 0x%02x, snr = %d.%02d dB\n", rec_buf[0],
		state->snr >> 24, (((state->snr>>8) & 0xffff) * 100) >> 16);

	वापस 0;
पूर्ण

अटल पूर्णांक or51211_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	/* Calculate Strength from SNR up to 35dB */
	/* Even though the SNR can go higher than 35dB, there is some comक्रमt */
	/* factor in having a range of strong संकेतs that can show at 100%   */
	काष्ठा or51211_state* state = (काष्ठा or51211_state*)fe->demodulator_priv;
	u16 snr;
	पूर्णांक ret;

	ret = fe->ops.पढ़ो_snr(fe, &snr);
	अगर (ret != 0)
		वापस ret;
	/* Rather than use the 8.8 value snr, use state->snr which is 8.24 */
	/* scale the range 0 - 35*2^24 पूर्णांकo 0 - 65535 */
	अगर (state->snr >= 8960 * 0x10000)
		*strength = 0xffff;
	अन्यथा
		*strength = state->snr / 8960;

	वापस 0;
पूर्ण

अटल पूर्णांक or51211_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	*ber = -ENOSYS;
	वापस 0;
पूर्ण

अटल पूर्णांक or51211_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	*ucblocks = -ENOSYS;
	वापस 0;
पूर्ण

अटल पूर्णांक or51211_sleep(काष्ठा dvb_frontend* fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक or51211_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा or51211_state* state = fe->demodulator_priv;
	स्थिर काष्ठा or51211_config* config = state->config;
	स्थिर काष्ठा firmware* fw;
	अचिन्हित अक्षर get_ver_buf[] = अणु0x04,0x00,0x30,0x00,0x00पूर्ण;
	अचिन्हित अक्षर rec_buf[14];
	पूर्णांक ret,i;

	अगर (!state->initialized) अणु
		/* Request the firmware, this will block until it uploads */
		pr_info("Waiting for firmware upload (%s)...\n",
			OR51211_DEFAULT_FIRMWARE);
		ret = config->request_firmware(fe, &fw,
					       OR51211_DEFAULT_FIRMWARE);
		pr_info("Got Hotplug firmware\n");
		अगर (ret) अणु
			pr_warn("No firmware uploaded (timeout or file not found?)\n");
			वापस ret;
		पूर्ण

		ret = or51211_load_firmware(fe, fw);
		release_firmware(fw);
		अगर (ret) अणु
			pr_warn("Writing firmware to device failed!\n");
			वापस ret;
		पूर्ण
		pr_info("Firmware upload complete.\n");

		/* Set operation mode in Receiver 1 रेजिस्टर;
		 * type 1:
		 * data 0x50h  Automatic sets receiver channel conditions
		 *             Automatic NTSC rejection filter
		 *             Enable  MPEG serial data output
		 *             MPEG2tr
		 *             High tuner phase noise
		 *             normal +/-150kHz Carrier acquisition range
		 */
		अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,
				   cmd_buf,3)) अणु
			pr_warn("Load DVR Error 5\n");
			वापस -1;
		पूर्ण

		/* Read back ucode version to besure we loaded correctly */
		/* and are really up and running */
		rec_buf[0] = 0x04;
		rec_buf[1] = 0x00;
		rec_buf[2] = 0x03;
		rec_buf[3] = 0x00;
		msleep(30);
		अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,
				   rec_buf,3)) अणु
			pr_warn("Load DVR Error A\n");
			वापस -1;
		पूर्ण
		msleep(3);
		अगर (i2c_पढ़ोbytes(state,state->config->demod_address,
				  &rec_buf[10],2)) अणु
			pr_warn("Load DVR Error B\n");
			वापस -1;
		पूर्ण

		rec_buf[0] = 0x04;
		rec_buf[1] = 0x00;
		rec_buf[2] = 0x01;
		rec_buf[3] = 0x00;
		msleep(20);
		अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,
				   rec_buf,3)) अणु
			pr_warn("Load DVR Error C\n");
			वापस -1;
		पूर्ण
		msleep(3);
		अगर (i2c_पढ़ोbytes(state,state->config->demod_address,
				  &rec_buf[12],2)) अणु
			pr_warn("Load DVR Error D\n");
			वापस -1;
		पूर्ण

		क्रम (i = 0; i < 8; i++)
			rec_buf[i]=0xed;

		क्रम (i = 0; i < 5; i++) अणु
			msleep(30);
			get_ver_buf[4] = i+1;
			अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,
					   get_ver_buf,5)) अणु
				pr_warn("Load DVR Error 6 - %d\n", i);
				वापस -1;
			पूर्ण
			msleep(3);

			अगर (i2c_पढ़ोbytes(state,state->config->demod_address,
					  &rec_buf[i*2],2)) अणु
				pr_warn("Load DVR Error 7 - %d\n", i);
				वापस -1;
			पूर्ण
			/* If we didn't receive the right index, try again */
			अगर ((पूर्णांक)rec_buf[i*2+1]!=i+1)अणु
			  i--;
			पूर्ण
		पूर्ण
		dprपूर्णांकk("read_fwbits %10ph\n", rec_buf);

		pr_info("ver TU%02x%02x%02x VSB mode %02x Status %02x\n",
			rec_buf[2], rec_buf[4], rec_buf[6], rec_buf[12],
			rec_buf[10]);

		rec_buf[0] = 0x04;
		rec_buf[1] = 0x00;
		rec_buf[2] = 0x03;
		rec_buf[3] = 0x00;
		msleep(20);
		अगर (i2c_ग_लिखोbytes(state,state->config->demod_address,
				   rec_buf,3)) अणु
			pr_warn("Load DVR Error 8\n");
			वापस -1;
		पूर्ण
		msleep(20);
		अगर (i2c_पढ़ोbytes(state,state->config->demod_address,
				  &rec_buf[8],2)) अणु
			pr_warn("Load DVR Error 9\n");
			वापस -1;
		पूर्ण
		state->initialized = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक or51211_get_tune_settings(काष्ठा dvb_frontend* fe,
				     काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
	fesettings->min_delay_ms = 500;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल व्योम or51211_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा or51211_state* state = fe->demodulator_priv;
	state->config->sleep(fe);
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops or51211_ops;

काष्ठा dvb_frontend* or51211_attach(स्थिर काष्ठा or51211_config* config,
				    काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा or51211_state* state = शून्य;

	/* Allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा or51211_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	/* Setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialized = 0;
	state->current_frequency = 0;

	/* Create dvb_frontend */
	स_नकल(&state->frontend.ops, &or51211_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops or51211_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name                  = "Oren OR51211 VSB Frontend",
		.frequency_min_hz      =  44 * MHz,
		.frequency_max_hz      = 958 * MHz,
		.frequency_stepsize_hz = 166666,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_8VSB
	पूर्ण,

	.release = or51211_release,

	.init = or51211_init,
	.sleep = or51211_sleep,

	.set_frontend = or51211_set_parameters,
	.get_tune_settings = or51211_get_tune_settings,

	.पढ़ो_status = or51211_पढ़ो_status,
	.पढ़ो_ber = or51211_पढ़ो_ber,
	.पढ़ो_संकेत_strength = or51211_पढ़ो_संकेत_strength,
	.पढ़ो_snr = or51211_पढ़ो_snr,
	.पढ़ो_ucblocks = or51211_पढ़ो_ucblocks,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Oren OR51211 VSB [pcHDTV HD-2000] Demodulator Driver");
MODULE_AUTHOR("Kirk Lapray");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(or51211_attach);

