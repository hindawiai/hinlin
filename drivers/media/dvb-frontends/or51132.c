<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Support क्रम OR51132 (pcHDTV HD-3000) - VSB/QAM
 *
 *    Copyright (C) 2007 Trent Piepho <xyzzy@speakeasy.org>
 *
 *    Copyright (C) 2005 Kirk Lapray <kirk_lapray@bigfoot.com>
 *
 *    Based on code from Jack Kelliher (kelliher@xmission.com)
 *                           Copyright (C) 2002 & pcHDTV, inc.
*/

/*
 * This driver needs two बाह्यal firmware files. Please copy
 * "dvb-fe-or51132-vsb.fw" and "dvb-fe-or51132-qam.fw" to
 * /usr/lib/hotplug/firmware/ or /lib/firmware/
 * (depending on configuration of firmware hotplug).
 */
#घोषणा OR51132_VSB_FIRMWARE "dvb-fe-or51132-vsb.fw"
#घोषणा OR51132_QAM_FIRMWARE "dvb-fe-or51132-qam.fw"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <media/dvb_गणित.स>
#समावेश <media/dvb_frontend.h>
#समावेश "or51132.h"

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "or51132: " args); \
	पूर्ण जबतक (0)


काष्ठा or51132_state
अणु
	काष्ठा i2c_adapter* i2c;

	/* Configuration settings */
	स्थिर काष्ठा or51132_config* config;

	काष्ठा dvb_frontend frontend;

	/* Demodulator निजी data */
	क्रमागत fe_modulation current_modulation;
	u32 snr; /* Result of last SNR calculation */

	/* Tuner निजी data */
	u32 current_frequency;
पूर्ण;


/* Write buffer to demod */
अटल पूर्णांक or51132_ग_लिखोbuf(काष्ठा or51132_state *state, स्थिर u8 *buf, पूर्णांक len)
अणु
	पूर्णांक err;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address,
			       .flags = 0, .buf = (u8*)buf, .len = len पूर्ण;

	/* msleep(20); */ /* करोesn't appear to be necessary */
	अगर ((err = i2c_transfer(state->i2c, &msg, 1)) != 1) अणु
		prपूर्णांकk(KERN_WARNING "or51132: I2C write (addr 0x%02x len %d) error: %d\n",
		       msg.addr, msg.len, err);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

/* Write स्थिरant bytes, e.g. or51132_ग_लिखोbytes(state, 0x04, 0x42, 0x00);
   Less code and more efficient that loading a buffer on the stack with
   the bytes to send and then calling or51132_ग_लिखोbuf() on that. */
#घोषणा or51132_ग_लिखोbytes(state, data...)  \
	(अणु अटल स्थिर u8 _data[] = अणुdataपूर्ण; \
	or51132_ग_लिखोbuf(state, _data, माप(_data)); पूर्ण)

/* Read data from demod पूर्णांकo buffer.  Returns 0 on success. */
अटल पूर्णांक or51132_पढ़ोbuf(काष्ठा or51132_state *state, u8 *buf, पूर्णांक len)
अणु
	पूर्णांक err;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address,
			       .flags = I2C_M_RD, .buf = buf, .len = len पूर्ण;

	/* msleep(20); */ /* करोesn't appear to be necessary */
	अगर ((err = i2c_transfer(state->i2c, &msg, 1)) != 1) अणु
		prपूर्णांकk(KERN_WARNING "or51132: I2C read (addr 0x%02x len %d) error: %d\n",
		       msg.addr, msg.len, err);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

/* Reads a 16-bit demod रेजिस्टर.  Returns <0 on error. */
अटल पूर्णांक or51132_पढ़ोreg(काष्ठा or51132_state *state, u8 reg)
अणु
	u8 buf[2] = अणु 0x04, reg पूर्ण;
	काष्ठा i2c_msg msg[2] = अणु
		अणु.addr = state->config->demod_address, .flags = 0,
		 .buf = buf, .len = 2 पूर्ण,
		अणु.addr = state->config->demod_address, .flags = I2C_M_RD,
		 .buf = buf, .len = 2 पूर्णपूर्ण;
	पूर्णांक err;

	अगर ((err = i2c_transfer(state->i2c, msg, 2)) != 2) अणु
		prपूर्णांकk(KERN_WARNING "or51132: I2C error reading register %d: %d\n",
		       reg, err);
		वापस -EREMOTEIO;
	पूर्ण
	वापस buf[0] | (buf[1] << 8);
पूर्ण

अटल पूर्णांक or51132_load_firmware (काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा or51132_state* state = fe->demodulator_priv;
	अटल स्थिर u8 run_buf[] = अणु0x7F,0x01पूर्ण;
	u8 rec_buf[8];
	u32 firmwareAsize, firmwareBsize;
	पूर्णांक i,ret;

	dprपूर्णांकk("Firmware is %zd bytes\n",fw->size);

	/* Get size of firmware A and B */
	firmwareAsize = le32_to_cpu(*((__le32*)fw->data));
	dprपूर्णांकk("FirmwareA is %i bytes\n",firmwareAsize);
	firmwareBsize = le32_to_cpu(*((__le32*)(fw->data+4)));
	dprपूर्णांकk("FirmwareB is %i bytes\n",firmwareBsize);

	/* Upload firmware */
	अगर ((ret = or51132_ग_लिखोbuf(state, &fw->data[8], firmwareAsize))) अणु
		prपूर्णांकk(KERN_WARNING "or51132: load_firmware error 1\n");
		वापस ret;
	पूर्ण
	अगर ((ret = or51132_ग_लिखोbuf(state, &fw->data[8+firmwareAsize],
				    firmwareBsize))) अणु
		prपूर्णांकk(KERN_WARNING "or51132: load_firmware error 2\n");
		वापस ret;
	पूर्ण

	अगर ((ret = or51132_ग_लिखोbuf(state, run_buf, 2))) अणु
		prपूर्णांकk(KERN_WARNING "or51132: load_firmware error 3\n");
		वापस ret;
	पूर्ण
	अगर ((ret = or51132_ग_लिखोbuf(state, run_buf, 2))) अणु
		prपूर्णांकk(KERN_WARNING "or51132: load_firmware error 4\n");
		वापस ret;
	पूर्ण

	/* 50ms क्रम operation to begin */
	msleep(50);

	/* Read back ucode version to besure we loaded correctly and are really up and running */
	/* Get uCode version */
	अगर ((ret = or51132_ग_लिखोbytes(state, 0x10, 0x10, 0x00))) अणु
		prपूर्णांकk(KERN_WARNING "or51132: load_firmware error a\n");
		वापस ret;
	पूर्ण
	अगर ((ret = or51132_ग_लिखोbytes(state, 0x04, 0x17))) अणु
		prपूर्णांकk(KERN_WARNING "or51132: load_firmware error b\n");
		वापस ret;
	पूर्ण
	अगर ((ret = or51132_ग_लिखोbytes(state, 0x00, 0x00))) अणु
		prपूर्णांकk(KERN_WARNING "or51132: load_firmware error c\n");
		वापस ret;
	पूर्ण
	क्रम (i=0;i<4;i++) अणु
		/* Once upon a समय, this command might have had something
		   to करो with getting the firmware version, but it's
		   not used anymore:
		   अणु0x04,0x00,0x30,0x00,i+1पूर्ण */
		/* Read 8 bytes, two bytes at a समय */
		अगर ((ret = or51132_पढ़ोbuf(state, &rec_buf[i*2], 2))) अणु
			prपूर्णांकk(KERN_WARNING
			       "or51132: load_firmware error d - %d\n",i);
			वापस ret;
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_WARNING
	       "or51132: Version: %02X%02X%02X%02X-%02X%02X%02X%02X (%02X%01X-%01X-%02X%01X-%01X)\n",
	       rec_buf[1],rec_buf[0],rec_buf[3],rec_buf[2],
	       rec_buf[5],rec_buf[4],rec_buf[7],rec_buf[6],
	       rec_buf[3],rec_buf[2]>>4,rec_buf[2]&0x0f,
	       rec_buf[5],rec_buf[4]>>4,rec_buf[4]&0x0f);

	अगर ((ret = or51132_ग_लिखोbytes(state, 0x10, 0x00, 0x00))) अणु
		prपूर्णांकk(KERN_WARNING "or51132: load_firmware error e\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण;

अटल पूर्णांक or51132_init(काष्ठा dvb_frontend* fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक or51132_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	*ber = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक or51132_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	*ucblocks = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक or51132_sleep(काष्ठा dvb_frontend* fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक or51132_seपंचांगode(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा or51132_state* state = fe->demodulator_priv;
	u8 cmd_buf1[3] = अणु0x04, 0x01, 0x5fपूर्ण;
	u8 cmd_buf2[3] = अणु0x1c, 0x00, 0 पूर्ण;

	dprपूर्णांकk("setmode %d\n",(पूर्णांक)state->current_modulation);

	चयन (state->current_modulation) अणु
	हाल VSB_8:
		/* Auto CH, Auto NTSC rej, MPEGser, MPEG2tr, phase noise-high */
		cmd_buf1[2] = 0x50;
		/* REC MODE inv IF spectrum, Normal */
		cmd_buf2[1] = 0x03;
		/* Channel MODE ATSC/VSB8 */
		cmd_buf2[2] = 0x06;
		अवरोध;
	/* All QAM modes are:
	   Auto-deपूर्णांकerleave; MPEGser, MPEG2tr, phase noise-high
	   REC MODE Normal Carrier Lock */
	हाल QAM_AUTO:
		/* Channel MODE Auto QAM64/256 */
		cmd_buf2[2] = 0x4f;
		अवरोध;
	हाल QAM_256:
		/* Channel MODE QAM256 */
		cmd_buf2[2] = 0x45;
		अवरोध;
	हाल QAM_64:
		/* Channel MODE QAM64 */
		cmd_buf2[2] = 0x43;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING
		       "or51132: setmode: Modulation set to unsupported value (%d)\n",
		       state->current_modulation);
		वापस -EINVAL;
	पूर्ण

	/* Set Receiver 1 रेजिस्टर */
	अगर (or51132_ग_लिखोbuf(state, cmd_buf1, 3)) अणु
		prपूर्णांकk(KERN_WARNING "or51132: set_mode error 1\n");
		वापस -EREMOTEIO;
	पूर्ण
	dprपूर्णांकk("set #1 to %02x\n", cmd_buf1[2]);

	/* Set operation mode in Receiver 6 रेजिस्टर */
	अगर (or51132_ग_लिखोbuf(state, cmd_buf2, 3)) अणु
		prपूर्णांकk(KERN_WARNING "or51132: set_mode error 2\n");
		वापस -EREMOTEIO;
	पूर्ण
	dprपूर्णांकk("set #6 to 0x%02x%02x\n", cmd_buf2[1], cmd_buf2[2]);

	वापस 0;
पूर्ण

/* Some modulations use the same firmware.  This classअगरies modulations
   by the firmware they use. */
#घोषणा MOD_FWCLASS_UNKNOWN	0
#घोषणा MOD_FWCLASS_VSB		1
#घोषणा MOD_FWCLASS_QAM		2
अटल पूर्णांक modulation_fw_class(क्रमागत fe_modulation modulation)
अणु
	चयन(modulation) अणु
	हाल VSB_8:
		वापस MOD_FWCLASS_VSB;
	हाल QAM_AUTO:
	हाल QAM_64:
	हाल QAM_256:
		वापस MOD_FWCLASS_QAM;
	शेष:
		वापस MOD_FWCLASS_UNKNOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक or51132_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	पूर्णांक ret;
	काष्ठा or51132_state* state = fe->demodulator_priv;
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर *fwname;
	पूर्णांक घड़ी_mode;

	/* Upload new firmware only अगर we need a dअगरferent one */
	अगर (modulation_fw_class(state->current_modulation) !=
	    modulation_fw_class(p->modulation)) अणु
		चयन (modulation_fw_class(p->modulation)) अणु
		हाल MOD_FWCLASS_VSB:
			dprपूर्णांकk("set_parameters VSB MODE\n");
			fwname = OR51132_VSB_FIRMWARE;

			/* Set non-punctured घड़ी क्रम VSB */
			घड़ी_mode = 0;
			अवरोध;
		हाल MOD_FWCLASS_QAM:
			dprपूर्णांकk("set_parameters QAM MODE\n");
			fwname = OR51132_QAM_FIRMWARE;

			/* Set punctured घड़ी क्रम QAM */
			घड़ी_mode = 1;
			अवरोध;
		शेष:
			prपूर्णांकk("or51132: Modulation type(%d) UNSUPPORTED\n",
			       p->modulation);
			वापस -1;
		पूर्ण
		prपूर्णांकk("or51132: Waiting for firmware upload(%s)...\n",
		       fwname);
		ret = request_firmware(&fw, fwname, state->i2c->dev.parent);
		अगर (ret) अणु
			prपूर्णांकk(KERN_WARNING "or51132: No firmware uploaded(timeout or file not found?)\n");
			वापस ret;
		पूर्ण
		ret = or51132_load_firmware(fe, fw);
		release_firmware(fw);
		अगर (ret) अणु
			prपूर्णांकk(KERN_WARNING "or51132: Writing firmware to device failed!\n");
			वापस ret;
		पूर्ण
		prपूर्णांकk("or51132: Firmware upload complete.\n");
		state->config->set_ts_params(fe, घड़ी_mode);
	पूर्ण
	/* Change only अगर we are actually changing the modulation */
	अगर (state->current_modulation != p->modulation) अणु
		state->current_modulation = p->modulation;
		or51132_seपंचांगode(fe);
	पूर्ण

	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* Set to current mode */
	or51132_seपंचांगode(fe);

	/* Update current frequency */
	state->current_frequency = p->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक or51132_get_parameters(काष्ठा dvb_frontend* fe,
				  काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा or51132_state* state = fe->demodulator_priv;
	पूर्णांक status;
	पूर्णांक retry = 1;

start:
	/* Receiver Status */
	अगर ((status = or51132_पढ़ोreg(state, 0x00)) < 0) अणु
		prपूर्णांकk(KERN_WARNING "or51132: get_parameters: error reading receiver status\n");
		वापस -EREMOTEIO;
	पूर्ण
	चयन(status&0xff) अणु
	हाल 0x06:
		p->modulation = VSB_8;
		अवरोध;
	हाल 0x43:
		p->modulation = QAM_64;
		अवरोध;
	हाल 0x45:
		p->modulation = QAM_256;
		अवरोध;
	शेष:
		अगर (retry--)
			जाओ start;
		prपूर्णांकk(KERN_WARNING "or51132: unknown status 0x%02x\n",
		       status&0xff);
		वापस -EREMOTEIO;
	पूर्ण

	/* FIXME: Read frequency from frontend, take AFC पूर्णांकo account */
	p->frequency = state->current_frequency;

	/* FIXME: How to पढ़ो inversion setting? Receiver 6 रेजिस्टर? */
	p->inversion = INVERSION_AUTO;

	वापस 0;
पूर्ण

अटल पूर्णांक or51132_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा or51132_state* state = fe->demodulator_priv;
	पूर्णांक reg;

	/* Receiver Status */
	अगर ((reg = or51132_पढ़ोreg(state, 0x00)) < 0) अणु
		prपूर्णांकk(KERN_WARNING "or51132: read_status: error reading receiver status: %d\n", reg);
		*status = 0;
		वापस -EREMOTEIO;
	पूर्ण
	dprपूर्णांकk("%s: read_status %04x\n", __func__, reg);

	अगर (reg & 0x0100) /* Receiver Lock */
		*status = FE_HAS_SIGNAL|FE_HAS_CARRIER|FE_HAS_VITERBI|
			  FE_HAS_SYNC|FE_HAS_LOCK;
	अन्यथा
		*status = 0;
	वापस 0;
पूर्ण

/* Calculate SNR estimation (scaled by 2^24)

   8-VSB SNR and QAM equations from Oren datasheets

   For 8-VSB:
     SNR[dB] = 10 * log10(897152044.8282 / MSE^2 ) - K

     Where K = 0 अगर NTSC rejection filter is OFF; and
	   K = 3 अगर NTSC rejection filter is ON

   For QAM64:
     SNR[dB] = 10 * log10(897152044.8282 / MSE^2 )

   For QAM256:
     SNR[dB] = 10 * log10(907832426.314266  / MSE^2 )

   We re-ग_लिखो the snr equation as:
     SNR * 2^24 = 10*(c - 2*पूर्णांकlog10(MSE))
   Where क्रम QAM256, c = log10(907832426.314266) * 2^24
   and क्रम 8-VSB and QAM64, c = log10(897152044.8282) * 2^24 */

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

अटल पूर्णांक or51132_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु
	काष्ठा or51132_state* state = fe->demodulator_priv;
	पूर्णांक noise, reg;
	u32 c, usK = 0;
	पूर्णांक retry = 1;

start:
	/* SNR after Equalizer */
	noise = or51132_पढ़ोreg(state, 0x02);
	अगर (noise < 0) अणु
		prपूर्णांकk(KERN_WARNING "or51132: read_snr: error reading equalizer\n");
		वापस -EREMOTEIO;
	पूर्ण
	dprपूर्णांकk("read_snr noise (%d)\n", noise);

	/* Read status, contains modulation type क्रम QAM_AUTO and
	   NTSC filter क्रम VSB */
	reg = or51132_पढ़ोreg(state, 0x00);
	अगर (reg < 0) अणु
		prपूर्णांकk(KERN_WARNING "or51132: read_snr: error reading receiver status\n");
		वापस -EREMOTEIO;
	पूर्ण

	चयन (reg&0xff) अणु
	हाल 0x06:
		अगर (reg & 0x1000) usK = 3 << 24;
		fallthrough;
	हाल 0x43: /* QAM64 */
		c = 150204167;
		अवरोध;
	हाल 0x45:
		c = 150290396;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "or51132: unknown status 0x%02x\n", reg&0xff);
		अगर (retry--) जाओ start;
		वापस -EREMOTEIO;
	पूर्ण
	dprपूर्णांकk("%s: modulation %02x, NTSC rej O%s\n", __func__,
		reg&0xff, reg&0x1000?"n":"ff");

	/* Calculate SNR using noise, c, and NTSC rejection correction */
	state->snr = calculate_snr(noise, c) - usK;
	*snr = (state->snr) >> 16;

	dprपूर्णांकk("%s: noise = 0x%08x, snr = %d.%02d dB\n", __func__, noise,
		state->snr >> 24, (((state->snr>>8) & 0xffff) * 100) >> 16);

	वापस 0;
पूर्ण

अटल पूर्णांक or51132_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	/* Calculate Strength from SNR up to 35dB */
	/* Even though the SNR can go higher than 35dB, there is some comक्रमt */
	/* factor in having a range of strong संकेतs that can show at 100%   */
	काष्ठा or51132_state* state = (काष्ठा or51132_state*) fe->demodulator_priv;
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

अटल पूर्णांक or51132_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* fe_tune_settings)
अणु
	fe_tune_settings->min_delay_ms = 500;
	fe_tune_settings->step_size = 0;
	fe_tune_settings->max_drअगरt = 0;

	वापस 0;
पूर्ण

अटल व्योम or51132_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा or51132_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops or51132_ops;

काष्ठा dvb_frontend* or51132_attach(स्थिर काष्ठा or51132_config* config,
				    काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा or51132_state* state = शून्य;

	/* Allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा or51132_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	/* Setup the state */
	state->config = config;
	state->i2c = i2c;
	state->current_frequency = -1;
	state->current_modulation = -1;

	/* Create dvb_frontend */
	स_नकल(&state->frontend.ops, &or51132_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops or51132_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name			= "Oren OR51132 VSB/QAM Frontend",
		.frequency_min_hz	=  44 * MHz,
		.frequency_max_hz	= 958 * MHz,
		.frequency_stepsize_hz	= 166666,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_QAM_AUTO |
			FE_CAN_8VSB
	पूर्ण,

	.release = or51132_release,

	.init = or51132_init,
	.sleep = or51132_sleep,

	.set_frontend = or51132_set_parameters,
	.get_frontend = or51132_get_parameters,
	.get_tune_settings = or51132_get_tune_settings,

	.पढ़ो_status = or51132_पढ़ो_status,
	.पढ़ो_ber = or51132_पढ़ो_ber,
	.पढ़ो_संकेत_strength = or51132_पढ़ो_संकेत_strength,
	.पढ़ो_snr = or51132_पढ़ो_snr,
	.पढ़ो_ucblocks = or51132_पढ़ो_ucblocks,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("OR51132 ATSC [pcHDTV HD-3000] (8VSB & ITU J83 AnnexB FEC QAM64/256) Demodulator Driver");
MODULE_AUTHOR("Kirk Lapray");
MODULE_AUTHOR("Trent Piepho");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(or51132_attach);
