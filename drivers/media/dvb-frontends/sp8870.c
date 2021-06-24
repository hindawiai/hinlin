<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Driver क्रम Spase SP8870 demodulator

    Copyright (C) 1999 Juergen Peitz


*/
/*
 * This driver needs बाह्यal firmware. Please use the command
 * "<kerneldir>/scripts/get_dvb_firmware alps_tdlb7" to
 * करोwnload/extract it, and then copy it to /usr/lib/hotplug/firmware
 * or /lib/firmware (depending on configuration of firmware hotplug).
 */
#घोषणा SP8870_DEFAULT_FIRMWARE "dvb-fe-sp8870.fw"

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "sp8870.h"


काष्ठा sp8870_state अणु

	काष्ठा i2c_adapter* i2c;

	स्थिर काष्ठा sp8870_config* config;

	काष्ठा dvb_frontend frontend;

	/* demodulator निजी data */
	u8 initialised:1;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "sp8870: " args); \
	पूर्ण जबतक (0)

/* firmware size क्रम sp8870 */
#घोषणा SP8870_FIRMWARE_SIZE 16382

/* starting poपूर्णांक क्रम firmware in file 'Sc_main.mc' */
#घोषणा SP8870_FIRMWARE_OFFSET 0x0A

अटल पूर्णांक sp8870_ग_लिखोreg (काष्ठा sp8870_state* state, u16 reg, u16 data)
अणु
	u8 buf [] = अणु reg >> 8, reg & 0xff, data >> 8, data & 0xff पूर्ण;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf, .len = 4 पूर्ण;
	पूर्णांक err;

	अगर ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) अणु
		dprपूर्णांकk ("%s: writereg error (err == %i, reg == 0x%02x, data == 0x%02x)\n", __func__, err, reg, data);
		वापस -EREMOTEIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sp8870_पढ़ोreg (काष्ठा sp8870_state* state, u16 reg)
अणु
	पूर्णांक ret;
	u8 b0 [] = अणु reg >> 8 , reg & 0xff पूर्ण;
	u8 b1 [] = अणु 0, 0 पूर्ण;
	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = b0, .len = 2 पूर्ण,
			   अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = b1, .len = 2 पूर्ण पूर्ण;

	ret = i2c_transfer (state->i2c, msg, 2);

	अगर (ret != 2) अणु
		dprपूर्णांकk("%s: readreg error (ret == %i)\n", __func__, ret);
		वापस -1;
	पूर्ण

	वापस (b1[0] << 8 | b1[1]);
पूर्ण

अटल पूर्णांक sp8870_firmware_upload (काष्ठा sp8870_state* state, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा i2c_msg msg;
	स्थिर अक्षर *fw_buf = fw->data;
	पूर्णांक fw_pos;
	u8 tx_buf[255];
	पूर्णांक tx_len;
	पूर्णांक err = 0;

	dprपूर्णांकk ("%s: ...\n", __func__);

	अगर (fw->size < SP8870_FIRMWARE_SIZE + SP8870_FIRMWARE_OFFSET)
		वापस -EINVAL;

	// प्रणाली controller stop
	sp8870_ग_लिखोreg(state, 0x0F00, 0x0000);

	// inकाष्ठाion RAM रेजिस्टर hiword
	sp8870_ग_लिखोreg(state, 0x8F08, ((SP8870_FIRMWARE_SIZE / 2) & 0xFFFF));

	// inकाष्ठाion RAM MWR
	sp8870_ग_लिखोreg(state, 0x8F0A, ((SP8870_FIRMWARE_SIZE / 2) >> 16));

	// करो firmware upload
	fw_pos = SP8870_FIRMWARE_OFFSET;
	जबतक (fw_pos < SP8870_FIRMWARE_SIZE + SP8870_FIRMWARE_OFFSET)अणु
		tx_len = (fw_pos <= SP8870_FIRMWARE_SIZE + SP8870_FIRMWARE_OFFSET - 252) ? 252 : SP8870_FIRMWARE_SIZE + SP8870_FIRMWARE_OFFSET - fw_pos;
		// ग_लिखो रेजिस्टर 0xCF0A
		tx_buf[0] = 0xCF;
		tx_buf[1] = 0x0A;
		स_नकल(&tx_buf[2], fw_buf + fw_pos, tx_len);
		msg.addr = state->config->demod_address;
		msg.flags = 0;
		msg.buf = tx_buf;
		msg.len = tx_len + 2;
		अगर ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) अणु
			prपूर्णांकk("%s: firmware upload failed!\n", __func__);
			prपूर्णांकk ("%s: i2c error (err == %i)\n", __func__, err);
			वापस err;
		पूर्ण
		fw_pos += tx_len;
	पूर्ण

	dprपूर्णांकk ("%s: done!\n", __func__);
	वापस 0;
पूर्ण;

अटल व्योम sp8870_microcontroller_stop (काष्ठा sp8870_state* state)
अणु
	sp8870_ग_लिखोreg(state, 0x0F08, 0x000);
	sp8870_ग_लिखोreg(state, 0x0F09, 0x000);

	// microcontroller STOP
	sp8870_ग_लिखोreg(state, 0x0F00, 0x000);
पूर्ण

अटल व्योम sp8870_microcontroller_start (काष्ठा sp8870_state* state)
अणु
	sp8870_ग_लिखोreg(state, 0x0F08, 0x000);
	sp8870_ग_लिखोreg(state, 0x0F09, 0x000);

	// microcontroller START
	sp8870_ग_लिखोreg(state, 0x0F00, 0x001);
	// not करोcumented but अगर we करोn't पढ़ो 0x0D01 out here
	// we करोn't get a correct data valid संकेत
	sp8870_पढ़ोreg(state, 0x0D01);
पूर्ण

अटल पूर्णांक sp8870_पढ़ो_data_valid_संकेत(काष्ठा sp8870_state* state)
अणु
	वापस (sp8870_पढ़ोreg(state, 0x0D02) > 0);
पूर्ण

अटल पूर्णांक configure_reg0xc05 (काष्ठा dtv_frontend_properties *p, u16 *reg0xc05)
अणु
	पूर्णांक known_parameters = 1;

	*reg0xc05 = 0x000;

	चयन (p->modulation) अणु
	हाल QPSK:
		अवरोध;
	हाल QAM_16:
		*reg0xc05 |= (1 << 10);
		अवरोध;
	हाल QAM_64:
		*reg0xc05 |= (2 << 10);
		अवरोध;
	हाल QAM_AUTO:
		known_parameters = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (p->hierarchy) अणु
	हाल HIERARCHY_NONE:
		अवरोध;
	हाल HIERARCHY_1:
		*reg0xc05 |= (1 << 7);
		अवरोध;
	हाल HIERARCHY_2:
		*reg0xc05 |= (2 << 7);
		अवरोध;
	हाल HIERARCHY_4:
		*reg0xc05 |= (3 << 7);
		अवरोध;
	हाल HIERARCHY_AUTO:
		known_parameters = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (p->code_rate_HP) अणु
	हाल FEC_1_2:
		अवरोध;
	हाल FEC_2_3:
		*reg0xc05 |= (1 << 3);
		अवरोध;
	हाल FEC_3_4:
		*reg0xc05 |= (2 << 3);
		अवरोध;
	हाल FEC_5_6:
		*reg0xc05 |= (3 << 3);
		अवरोध;
	हाल FEC_7_8:
		*reg0xc05 |= (4 << 3);
		अवरोध;
	हाल FEC_AUTO:
		known_parameters = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (known_parameters)
		*reg0xc05 |= (2 << 1);	/* use specअगरied parameters */
	अन्यथा
		*reg0xc05 |= (1 << 1);	/* enable स्वतःprobing */

	वापस 0;
पूर्ण

अटल पूर्णांक sp8870_wake_up(काष्ठा sp8870_state* state)
अणु
	// enable TS output and पूर्णांकerface pins
	वापस sp8870_ग_लिखोreg(state, 0xC18, 0x00D);
पूर्ण

अटल पूर्णांक sp8870_set_frontend_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा sp8870_state* state = fe->demodulator_priv;
	पूर्णांक  err;
	u16 reg0xc05;

	अगर ((err = configure_reg0xc05(p, &reg0xc05)))
		वापस err;

	// प्रणाली controller stop
	sp8870_microcontroller_stop(state);

	// set tuner parameters
	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl) fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	// sample rate correction bit [23..17]
	sp8870_ग_लिखोreg(state, 0x0319, 0x000A);

	// sample rate correction bit [16..0]
	sp8870_ग_लिखोreg(state, 0x031A, 0x0AAB);

	// पूर्णांकeger carrier offset
	sp8870_ग_लिखोreg(state, 0x0309, 0x0400);

	// fractional carrier offset
	sp8870_ग_लिखोreg(state, 0x030A, 0x0000);

	// filter क्रम 6/7/8 Mhz channel
	अगर (p->bandwidth_hz == 6000000)
		sp8870_ग_लिखोreg(state, 0x0311, 0x0002);
	अन्यथा अगर (p->bandwidth_hz == 7000000)
		sp8870_ग_लिखोreg(state, 0x0311, 0x0001);
	अन्यथा
		sp8870_ग_लिखोreg(state, 0x0311, 0x0000);

	// scan order: 2k first = 0x0000, 8k first = 0x0001
	अगर (p->transmission_mode == TRANSMISSION_MODE_2K)
		sp8870_ग_लिखोreg(state, 0x0338, 0x0000);
	अन्यथा
		sp8870_ग_लिखोreg(state, 0x0338, 0x0001);

	sp8870_ग_लिखोreg(state, 0xc05, reg0xc05);

	// पढ़ो status reg in order to clear pending irqs
	err = sp8870_पढ़ोreg(state, 0x200);
	अगर (err < 0)
		वापस err;

	// प्रणाली controller start
	sp8870_microcontroller_start(state);

	वापस 0;
पूर्ण

अटल पूर्णांक sp8870_init (काष्ठा dvb_frontend* fe)
अणु
	काष्ठा sp8870_state* state = fe->demodulator_priv;
	स्थिर काष्ठा firmware *fw = शून्य;

	sp8870_wake_up(state);
	अगर (state->initialised) वापस 0;
	state->initialised = 1;

	dprपूर्णांकk ("%s\n", __func__);


	/* request the firmware, this will block until someone uploads it */
	prपूर्णांकk("sp8870: waiting for firmware upload (%s)...\n", SP8870_DEFAULT_FIRMWARE);
	अगर (state->config->request_firmware(fe, &fw, SP8870_DEFAULT_FIRMWARE)) अणु
		prपूर्णांकk("sp8870: no firmware upload (timeout or file not found?)\n");
		वापस -EIO;
	पूर्ण

	अगर (sp8870_firmware_upload(state, fw)) अणु
		prपूर्णांकk("sp8870: writing firmware to device failed\n");
		release_firmware(fw);
		वापस -EIO;
	पूर्ण
	release_firmware(fw);
	prपूर्णांकk("sp8870: firmware upload complete\n");

	/* enable TS output and पूर्णांकerface pins */
	sp8870_ग_लिखोreg(state, 0xc18, 0x00d);

	// प्रणाली controller stop
	sp8870_microcontroller_stop(state);

	// ADC mode
	sp8870_ग_लिखोreg(state, 0x0301, 0x0003);

	// Reed Solomon parity bytes passed to output
	sp8870_ग_लिखोreg(state, 0x0C13, 0x0001);

	// MPEG घड़ी is suppressed अगर no valid data
	sp8870_ग_लिखोreg(state, 0x0C14, 0x0001);

	/* bit 0x010: enable data valid संकेत */
	sp8870_ग_लिखोreg(state, 0x0D00, 0x010);
	sp8870_ग_लिखोreg(state, 0x0D01, 0x000);

	वापस 0;
पूर्ण

अटल पूर्णांक sp8870_पढ़ो_status(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_status *fe_status)
अणु
	काष्ठा sp8870_state* state = fe->demodulator_priv;
	पूर्णांक status;
	पूर्णांक संकेत;

	*fe_status = 0;

	status = sp8870_पढ़ोreg (state, 0x0200);
	अगर (status < 0)
		वापस -EIO;

	संकेत = sp8870_पढ़ोreg (state, 0x0303);
	अगर (संकेत < 0)
		वापस -EIO;

	अगर (संकेत > 0x0F)
		*fe_status |= FE_HAS_SIGNAL;
	अगर (status & 0x08)
		*fe_status |= FE_HAS_SYNC;
	अगर (status & 0x04)
		*fe_status |= FE_HAS_LOCK | FE_HAS_CARRIER | FE_HAS_VITERBI;

	वापस 0;
पूर्ण

अटल पूर्णांक sp8870_पढ़ो_ber (काष्ठा dvb_frontend* fe, u32 * ber)
अणु
	काष्ठा sp8870_state* state = fe->demodulator_priv;
	पूर्णांक ret;
	u32 पंचांगp;

	*ber = 0;

	ret = sp8870_पढ़ोreg(state, 0xC08);
	अगर (ret < 0)
		वापस -EIO;

	पंचांगp = ret & 0x3F;

	ret = sp8870_पढ़ोreg(state, 0xC07);
	अगर (ret < 0)
		वापस -EIO;

	पंचांगp = ret << 6;
	अगर (पंचांगp >= 0x3FFF0)
		पंचांगp = ~0;

	*ber = पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक sp8870_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe,  u16 * संकेत)
अणु
	काष्ठा sp8870_state* state = fe->demodulator_priv;
	पूर्णांक ret;
	u16 पंचांगp;

	*संकेत = 0;

	ret = sp8870_पढ़ोreg (state, 0x306);
	अगर (ret < 0)
		वापस -EIO;

	पंचांगp = ret << 8;

	ret = sp8870_पढ़ोreg (state, 0x303);
	अगर (ret < 0)
		वापस -EIO;

	पंचांगp |= ret;

	अगर (पंचांगp)
		*संकेत = 0xFFFF - पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक sp8870_पढ़ो_uncorrected_blocks (काष्ठा dvb_frontend* fe, u32* ublocks)
अणु
	काष्ठा sp8870_state* state = fe->demodulator_priv;
	पूर्णांक ret;

	*ublocks = 0;

	ret = sp8870_पढ़ोreg(state, 0xC0C);
	अगर (ret < 0)
		वापस -EIO;

	अगर (ret == 0xFFFF)
		ret = ~0;

	*ublocks = ret;

	वापस 0;
पूर्ण

/* number of trials to recover from lockup */
#घोषणा MAXTRIALS 5
/* maximum checks क्रम data valid संकेत */
#घोषणा MAXCHECKS 100

/* only क्रम debugging: counter क्रम detected lockups */
अटल पूर्णांक lockups;
/* only क्रम debugging: counter क्रम channel चयनes */
अटल पूर्णांक चयनes;

अटल पूर्णांक sp8870_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा sp8870_state* state = fe->demodulator_priv;

	/*
	    The firmware of the sp8870 someबार locks up after setting frontend parameters.
	    We try to detect this by checking the data valid संकेत.
	    If it is not set after MAXCHECKS we try to recover the lockup by setting
	    the frontend parameters again.
	*/

	पूर्णांक err = 0;
	पूर्णांक valid = 0;
	पूर्णांक trials = 0;
	पूर्णांक check_count = 0;

	dprपूर्णांकk("%s: frequency = %i\n", __func__, p->frequency);

	क्रम (trials = 1; trials <= MAXTRIALS; trials++) अणु

		err = sp8870_set_frontend_parameters(fe);
		अगर (err)
			वापस err;

		क्रम (check_count = 0; check_count < MAXCHECKS; check_count++) अणु
//			valid = ((sp8870_पढ़ोreg(i2c, 0x0200) & 4) == 0);
			valid = sp8870_पढ़ो_data_valid_संकेत(state);
			अगर (valid) अणु
				dprपूर्णांकk("%s: delay = %i usec\n",
					__func__, check_count * 10);
				अवरोध;
			पूर्ण
			udelay(10);
		पूर्ण
		अगर (valid)
			अवरोध;
	पूर्ण

	अगर (!valid) अणु
		prपूर्णांकk("%s: firmware crash!!!!!!\n", __func__);
		वापस -EIO;
	पूर्ण

	अगर (debug) अणु
		अगर (valid) अणु
			अगर (trials > 1) अणु
				prपूर्णांकk("%s: firmware lockup!!!\n", __func__);
				prपूर्णांकk("%s: recovered after %i trial(s))\n",  __func__, trials - 1);
				lockups++;
			पूर्ण
		पूर्ण
		चयनes++;
		prपूर्णांकk("%s: switches = %i lockups = %i\n", __func__, चयनes, lockups);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sp8870_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा sp8870_state* state = fe->demodulator_priv;

	// tristate TS output and disable पूर्णांकerface pins
	वापस sp8870_ग_लिखोreg(state, 0xC18, 0x000);
पूर्ण

अटल पूर्णांक sp8870_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
	fesettings->min_delay_ms = 350;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक sp8870_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा sp8870_state* state = fe->demodulator_priv;

	अगर (enable) अणु
		वापस sp8870_ग_लिखोreg(state, 0x206, 0x001);
	पूर्ण अन्यथा अणु
		वापस sp8870_ग_लिखोreg(state, 0x206, 0x000);
	पूर्ण
पूर्ण

अटल व्योम sp8870_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा sp8870_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops sp8870_ops;

काष्ठा dvb_frontend* sp8870_attach(स्थिर काष्ठा sp8870_config* config,
				   काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा sp8870_state* state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा sp8870_state), GFP_KERNEL);
	अगर (state == शून्य) जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialised = 0;

	/* check अगर the demod is there */
	अगर (sp8870_पढ़ोreg(state, 0x0200) < 0) जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &sp8870_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops sp8870_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "Spase SP8870 DVB-T",
		.frequency_min_hz	= 470 * MHz,
		.frequency_max_hz	= 860 * MHz,
		.frequency_stepsize_hz	= 166666,
		.caps			= FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
					  FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 |
					  FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
					  FE_CAN_QPSK | FE_CAN_QAM_16 |
					  FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
					  FE_CAN_HIERARCHY_AUTO |  FE_CAN_RECOVER
	पूर्ण,

	.release = sp8870_release,

	.init = sp8870_init,
	.sleep = sp8870_sleep,
	.i2c_gate_ctrl = sp8870_i2c_gate_ctrl,

	.set_frontend = sp8870_set_frontend,
	.get_tune_settings = sp8870_get_tune_settings,

	.पढ़ो_status = sp8870_पढ़ो_status,
	.पढ़ो_ber = sp8870_पढ़ो_ber,
	.पढ़ो_संकेत_strength = sp8870_पढ़ो_संकेत_strength,
	.पढ़ो_ucblocks = sp8870_पढ़ो_uncorrected_blocks,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Spase SP8870 DVB-T Demodulator driver");
MODULE_AUTHOR("Juergen Peitz");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(sp8870_attach);
