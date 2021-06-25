<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
  /*
     Driver क्रम Philips tda1004xh OFDM Demodulator

     (c) 2003, 2004 Andrew de Quincey & Robert Schlabbach


   */
/*
 * This driver needs बाह्यal firmware. Please use the commands
 * "<kerneldir>/scripts/get_dvb_firmware tda10045",
 * "<kerneldir>/scripts/get_dvb_firmware tda10046" to
 * करोwnload/extract them, and then copy them to /usr/lib/hotplug/firmware
 * or /lib/firmware (depending on configuration of firmware hotplug).
 */
#घोषणा TDA10045_DEFAULT_FIRMWARE "dvb-fe-tda10045.fw"
#घोषणा TDA10046_DEFAULT_FIRMWARE "dvb-fe-tda10046.fw"

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>
#समावेश "tda1004x.h"

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (debug) prपूर्णांकk(KERN_DEBUG "tda1004x: " args); \
	पूर्ण जबतक (0)

#घोषणा TDA1004X_CHIPID		 0x00
#घोषणा TDA1004X_AUTO		 0x01
#घोषणा TDA1004X_IN_CONF1	 0x02
#घोषणा TDA1004X_IN_CONF2	 0x03
#घोषणा TDA1004X_OUT_CONF1	 0x04
#घोषणा TDA1004X_OUT_CONF2	 0x05
#घोषणा TDA1004X_STATUS_CD	 0x06
#घोषणा TDA1004X_CONFC4		 0x07
#घोषणा TDA1004X_DSSPARE2	 0x0C
#घोषणा TDA10045H_CODE_IN	 0x0D
#घोषणा TDA10045H_FWPAGE	 0x0E
#घोषणा TDA1004X_SCAN_CPT	 0x10
#घोषणा TDA1004X_DSP_CMD	 0x11
#घोषणा TDA1004X_DSP_ARG	 0x12
#घोषणा TDA1004X_DSP_DATA1	 0x13
#घोषणा TDA1004X_DSP_DATA2	 0x14
#घोषणा TDA1004X_CONFADC1	 0x15
#घोषणा TDA1004X_CONFC1		 0x16
#घोषणा TDA10045H_S_AGC		 0x1a
#घोषणा TDA10046H_AGC_TUN_LEVEL	 0x1a
#घोषणा TDA1004X_SNR		 0x1c
#घोषणा TDA1004X_CONF_TS1	 0x1e
#घोषणा TDA1004X_CONF_TS2	 0x1f
#घोषणा TDA1004X_CBER_RESET	 0x20
#घोषणा TDA1004X_CBER_MSB	 0x21
#घोषणा TDA1004X_CBER_LSB	 0x22
#घोषणा TDA1004X_CVBER_LUT	 0x23
#घोषणा TDA1004X_VBER_MSB	 0x24
#घोषणा TDA1004X_VBER_MID	 0x25
#घोषणा TDA1004X_VBER_LSB	 0x26
#घोषणा TDA1004X_UNCOR		 0x27

#घोषणा TDA10045H_CONFPLL_P	 0x2D
#घोषणा TDA10045H_CONFPLL_M_MSB	 0x2E
#घोषणा TDA10045H_CONFPLL_M_LSB	 0x2F
#घोषणा TDA10045H_CONFPLL_N	 0x30

#घोषणा TDA10046H_CONFPLL1	 0x2D
#घोषणा TDA10046H_CONFPLL2	 0x2F
#घोषणा TDA10046H_CONFPLL3	 0x30
#घोषणा TDA10046H_TIME_WREF1	 0x31
#घोषणा TDA10046H_TIME_WREF2	 0x32
#घोषणा TDA10046H_TIME_WREF3	 0x33
#घोषणा TDA10046H_TIME_WREF4	 0x34
#घोषणा TDA10046H_TIME_WREF5	 0x35

#घोषणा TDA10045H_UNSURW_MSB	 0x31
#घोषणा TDA10045H_UNSURW_LSB	 0x32
#घोषणा TDA10045H_WREF_MSB	 0x33
#घोषणा TDA10045H_WREF_MID	 0x34
#घोषणा TDA10045H_WREF_LSB	 0x35
#घोषणा TDA10045H_MUXOUT	 0x36
#घोषणा TDA1004X_CONFADC2	 0x37

#घोषणा TDA10045H_IOFFSET	 0x38

#घोषणा TDA10046H_CONF_TRISTATE1 0x3B
#घोषणा TDA10046H_CONF_TRISTATE2 0x3C
#घोषणा TDA10046H_CONF_POLARITY	 0x3D
#घोषणा TDA10046H_FREQ_OFFSET	 0x3E
#घोषणा TDA10046H_GPIO_OUT_SEL	 0x41
#घोषणा TDA10046H_GPIO_SELECT	 0x42
#घोषणा TDA10046H_AGC_CONF	 0x43
#घोषणा TDA10046H_AGC_THR	 0x44
#घोषणा TDA10046H_AGC_RENORM	 0x45
#घोषणा TDA10046H_AGC_GAINS	 0x46
#घोषणा TDA10046H_AGC_TUN_MIN	 0x47
#घोषणा TDA10046H_AGC_TUN_MAX	 0x48
#घोषणा TDA10046H_AGC_IF_MIN	 0x49
#घोषणा TDA10046H_AGC_IF_MAX	 0x4A

#घोषणा TDA10046H_FREQ_PHY2_MSB	 0x4D
#घोषणा TDA10046H_FREQ_PHY2_LSB	 0x4E

#घोषणा TDA10046H_CVBER_CTRL	 0x4F
#घोषणा TDA10046H_AGC_IF_LEVEL	 0x52
#घोषणा TDA10046H_CODE_CPT	 0x57
#घोषणा TDA10046H_CODE_IN	 0x58


अटल पूर्णांक tda1004x_ग_लिखो_byteI(काष्ठा tda1004x_state *state, पूर्णांक reg, पूर्णांक data)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु .flags = 0, .buf = buf, .len = 2 पूर्ण;

	dprपूर्णांकk("%s: reg=0x%x, data=0x%x\n", __func__, reg, data);

	msg.addr = state->config->demod_address;
	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		dprपूर्णांकk("%s: error reg=0x%x, data=0x%x, ret=%i\n",
			__func__, reg, data, ret);

	dprपूर्णांकk("%s: success reg=0x%x, data=0x%x, ret=%i\n", __func__,
		reg, data, ret);
	वापस (ret != 1) ? -1 : 0;
पूर्ण

अटल पूर्णांक tda1004x_पढ़ो_byte(काष्ठा tda1004x_state *state, पूर्णांक reg)
अणु
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणुअणु .flags = 0, .buf = b0, .len = 1 पूर्ण,
				अणु .flags = I2C_M_RD, .buf = b1, .len = 1 पूर्णपूर्ण;

	dprपूर्णांकk("%s: reg=0x%x\n", __func__, reg);

	msg[0].addr = state->config->demod_address;
	msg[1].addr = state->config->demod_address;
	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2) अणु
		dprपूर्णांकk("%s: error reg=0x%x, ret=%i\n", __func__, reg,
			ret);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk("%s: success reg=0x%x, data=0x%x, ret=%i\n", __func__,
		reg, b1[0], ret);
	वापस b1[0];
पूर्ण

अटल पूर्णांक tda1004x_ग_लिखो_mask(काष्ठा tda1004x_state *state, पूर्णांक reg, पूर्णांक mask, पूर्णांक data)
अणु
	पूर्णांक val;
	dprपूर्णांकk("%s: reg=0x%x, mask=0x%x, data=0x%x\n", __func__, reg,
		mask, data);

	// पढ़ो a byte and check
	val = tda1004x_पढ़ो_byte(state, reg);
	अगर (val < 0)
		वापस val;

	// mask अगर off
	val = val & ~mask;
	val |= data & 0xff;

	// ग_लिखो it out again
	वापस tda1004x_ग_लिखो_byteI(state, reg, val);
पूर्ण

अटल पूर्णांक tda1004x_ग_लिखो_buf(काष्ठा tda1004x_state *state, पूर्णांक reg, अचिन्हित अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i;
	पूर्णांक result;

	dprपूर्णांकk("%s: reg=0x%x, len=0x%x\n", __func__, reg, len);

	result = 0;
	क्रम (i = 0; i < len; i++) अणु
		result = tda1004x_ग_लिखो_byteI(state, reg + i, buf[i]);
		अगर (result != 0)
			अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक tda1004x_enable_tuner_i2c(काष्ठा tda1004x_state *state)
अणु
	पूर्णांक result;
	dprपूर्णांकk("%s\n", __func__);

	result = tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 2, 2);
	msleep(20);
	वापस result;
पूर्ण

अटल पूर्णांक tda1004x_disable_tuner_i2c(काष्ठा tda1004x_state *state)
अणु
	dprपूर्णांकk("%s\n", __func__);

	वापस tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 2, 0);
पूर्ण

अटल पूर्णांक tda10045h_set_bandwidth(काष्ठा tda1004x_state *state,
				   u32 bandwidth)
अणु
	अटल u8 bandwidth_6mhz[] = अणु 0x02, 0x00, 0x3d, 0x00, 0x60, 0x1e, 0xa7, 0x45, 0x4f पूर्ण;
	अटल u8 bandwidth_7mhz[] = अणु 0x02, 0x00, 0x37, 0x00, 0x4a, 0x2f, 0x6d, 0x76, 0xdb पूर्ण;
	अटल u8 bandwidth_8mhz[] = अणु 0x02, 0x00, 0x3d, 0x00, 0x48, 0x17, 0x89, 0xc7, 0x14 पूर्ण;

	चयन (bandwidth) अणु
	हाल 6000000:
		tda1004x_ग_लिखो_buf(state, TDA10045H_CONFPLL_P, bandwidth_6mhz, माप(bandwidth_6mhz));
		अवरोध;

	हाल 7000000:
		tda1004x_ग_लिखो_buf(state, TDA10045H_CONFPLL_P, bandwidth_7mhz, माप(bandwidth_7mhz));
		अवरोध;

	हाल 8000000:
		tda1004x_ग_लिखो_buf(state, TDA10045H_CONFPLL_P, bandwidth_8mhz, माप(bandwidth_8mhz));
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	tda1004x_ग_लिखो_byteI(state, TDA10045H_IOFFSET, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10046h_set_bandwidth(काष्ठा tda1004x_state *state,
				   u32 bandwidth)
अणु
	अटल u8 bandwidth_6mhz_53M[] = अणु 0x7b, 0x2e, 0x11, 0xf0, 0xd2 पूर्ण;
	अटल u8 bandwidth_7mhz_53M[] = अणु 0x6a, 0x02, 0x6a, 0x43, 0x9f पूर्ण;
	अटल u8 bandwidth_8mhz_53M[] = अणु 0x5c, 0x32, 0xc2, 0x96, 0x6d पूर्ण;

	अटल u8 bandwidth_6mhz_48M[] = अणु 0x70, 0x02, 0x49, 0x24, 0x92 पूर्ण;
	अटल u8 bandwidth_7mhz_48M[] = अणु 0x60, 0x02, 0xaa, 0xaa, 0xab पूर्ण;
	अटल u8 bandwidth_8mhz_48M[] = अणु 0x54, 0x03, 0x0c, 0x30, 0xc3 पूर्ण;
	पूर्णांक tda10046_clk53m;

	अगर ((state->config->अगर_freq == TDA10046_FREQ_045) ||
	    (state->config->अगर_freq == TDA10046_FREQ_052))
		tda10046_clk53m = 0;
	अन्यथा
		tda10046_clk53m = 1;
	चयन (bandwidth) अणु
	हाल 6000000:
		अगर (tda10046_clk53m)
			tda1004x_ग_लिखो_buf(state, TDA10046H_TIME_WREF1, bandwidth_6mhz_53M,
						  माप(bandwidth_6mhz_53M));
		अन्यथा
			tda1004x_ग_लिखो_buf(state, TDA10046H_TIME_WREF1, bandwidth_6mhz_48M,
						  माप(bandwidth_6mhz_48M));
		अगर (state->config->अगर_freq == TDA10046_FREQ_045) अणु
			tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_MSB, 0x0a);
			tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_LSB, 0xab);
		पूर्ण
		अवरोध;

	हाल 7000000:
		अगर (tda10046_clk53m)
			tda1004x_ग_लिखो_buf(state, TDA10046H_TIME_WREF1, bandwidth_7mhz_53M,
						  माप(bandwidth_7mhz_53M));
		अन्यथा
			tda1004x_ग_लिखो_buf(state, TDA10046H_TIME_WREF1, bandwidth_7mhz_48M,
						  माप(bandwidth_7mhz_48M));
		अगर (state->config->अगर_freq == TDA10046_FREQ_045) अणु
			tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_MSB, 0x0c);
			tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_LSB, 0x00);
		पूर्ण
		अवरोध;

	हाल 8000000:
		अगर (tda10046_clk53m)
			tda1004x_ग_लिखो_buf(state, TDA10046H_TIME_WREF1, bandwidth_8mhz_53M,
						  माप(bandwidth_8mhz_53M));
		अन्यथा
			tda1004x_ग_लिखो_buf(state, TDA10046H_TIME_WREF1, bandwidth_8mhz_48M,
						  माप(bandwidth_8mhz_48M));
		अगर (state->config->अगर_freq == TDA10046_FREQ_045) अणु
			tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_MSB, 0x0d);
			tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_LSB, 0x55);
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_करो_upload(काष्ठा tda1004x_state *state,
			      स्थिर अचिन्हित अक्षर *mem, अचिन्हित पूर्णांक len,
			      u8 dspCodeCounterReg, u8 dspCodeInReg)
अणु
	u8 buf[65];
	काष्ठा i2c_msg fw_msg = अणु .flags = 0, .buf = buf, .len = 0 पूर्ण;
	पूर्णांक tx_size;
	पूर्णांक pos = 0;

	/* clear code counter */
	tda1004x_ग_लिखो_byteI(state, dspCodeCounterReg, 0);
	fw_msg.addr = state->config->demod_address;

	i2c_lock_bus(state->i2c, I2C_LOCK_SEGMENT);
	buf[0] = dspCodeInReg;
	जबतक (pos != len) अणु
		// work out how much to send this समय
		tx_size = len - pos;
		अगर (tx_size > 0x10)
			tx_size = 0x10;

		// send the chunk
		स_नकल(buf + 1, mem + pos, tx_size);
		fw_msg.len = tx_size + 1;
		अगर (__i2c_transfer(state->i2c, &fw_msg, 1) != 1) अणु
			prपूर्णांकk(KERN_ERR "tda1004x: Error during firmware upload\n");
			i2c_unlock_bus(state->i2c, I2C_LOCK_SEGMENT);
			वापस -EIO;
		पूर्ण
		pos += tx_size;

		dprपूर्णांकk("%s: fw_pos=0x%x\n", __func__, pos);
	पूर्ण
	i2c_unlock_bus(state->i2c, I2C_LOCK_SEGMENT);

	/* give the DSP a chance to settle 03/10/05 Hac */
	msleep(100);

	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_check_upload_ok(काष्ठा tda1004x_state *state)
अणु
	u8 data1, data2;
	अचिन्हित दीर्घ समयout;

	अगर (state->demod_type == TDA1004X_DEMOD_TDA10046) अणु
		समयout = jअगरfies + 2 * HZ;
		जबतक(!(tda1004x_पढ़ो_byte(state, TDA1004X_STATUS_CD) & 0x20)) अणु
			अगर (समय_after(jअगरfies, समयout)) अणु
				prपूर्णांकk(KERN_ERR "tda1004x: timeout waiting for DSP ready\n");
				अवरोध;
			पूर्ण
			msleep(1);
		पूर्ण
	पूर्ण अन्यथा
		msleep(100);

	// check upload was OK
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 0x10, 0); // we want to पढ़ो from the DSP
	tda1004x_ग_लिखो_byteI(state, TDA1004X_DSP_CMD, 0x67);

	data1 = tda1004x_पढ़ो_byte(state, TDA1004X_DSP_DATA1);
	data2 = tda1004x_पढ़ो_byte(state, TDA1004X_DSP_DATA2);
	अगर (data1 != 0x67 || data2 < 0x20 || data2 > 0x2e) अणु
		prपूर्णांकk(KERN_INFO "tda1004x: found firmware revision %x -- invalid\n", data2);
		वापस -EIO;
	पूर्ण
	prपूर्णांकk(KERN_INFO "tda1004x: found firmware revision %x -- ok\n", data2);
	वापस 0;
पूर्ण

अटल पूर्णांक tda10045_fwupload(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw;

	/* करोn't re-upload unless necessary */
	अगर (tda1004x_check_upload_ok(state) == 0)
		वापस 0;

	/* request the firmware, this will block until someone uploads it */
	prपूर्णांकk(KERN_INFO "tda1004x: waiting for firmware upload (%s)...\n", TDA10045_DEFAULT_FIRMWARE);
	ret = state->config->request_firmware(fe, &fw, TDA10045_DEFAULT_FIRMWARE);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "tda1004x: no firmware upload (timeout or file not found?)\n");
		वापस ret;
	पूर्ण

	/* reset chip */
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 0x10, 0);
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 8, 8);
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 8, 0);
	msleep(10);

	/* set parameters */
	tda10045h_set_bandwidth(state, 8000000);

	ret = tda1004x_करो_upload(state, fw->data, fw->size, TDA10045H_FWPAGE, TDA10045H_CODE_IN);
	release_firmware(fw);
	अगर (ret)
		वापस ret;
	prपूर्णांकk(KERN_INFO "tda1004x: firmware upload complete\n");

	/* रुको क्रम DSP to initialise */
	/* DSPREADY करोesn't seem to work on the TDA10045H */
	msleep(100);

	वापस tda1004x_check_upload_ok(state);
पूर्ण

अटल व्योम tda10046_init_plls(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक tda10046_clk53m;

	अगर ((state->config->अगर_freq == TDA10046_FREQ_045) ||
	    (state->config->अगर_freq == TDA10046_FREQ_052))
		tda10046_clk53m = 0;
	अन्यथा
		tda10046_clk53m = 1;

	tda1004x_ग_लिखो_byteI(state, TDA10046H_CONFPLL1, 0xf0);
	अगर(tda10046_clk53m) अणु
		prपूर्णांकk(KERN_INFO "tda1004x: setting up plls for 53MHz sampling clock\n");
		tda1004x_ग_लिखो_byteI(state, TDA10046H_CONFPLL2, 0x08); // PLL M = 8
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "tda1004x: setting up plls for 48MHz sampling clock\n");
		tda1004x_ग_लिखो_byteI(state, TDA10046H_CONFPLL2, 0x03); // PLL M = 3
	पूर्ण
	अगर (state->config->xtal_freq == TDA10046_XTAL_4M ) अणु
		dprपूर्णांकk("%s: setting up PLLs for a 4 MHz Xtal\n", __func__);
		tda1004x_ग_लिखो_byteI(state, TDA10046H_CONFPLL3, 0); // PLL P = N = 0
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("%s: setting up PLLs for a 16 MHz Xtal\n", __func__);
		tda1004x_ग_लिखो_byteI(state, TDA10046H_CONFPLL3, 3); // PLL P = 0, N = 3
	पूर्ण
	अगर(tda10046_clk53m)
		tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_OFFSET, 0x67);
	अन्यथा
		tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_OFFSET, 0x72);
	/* Note घड़ी frequency is handled implicitly */
	चयन (state->config->अगर_freq) अणु
	हाल TDA10046_FREQ_045:
		tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_MSB, 0x0c);
		tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_LSB, 0x00);
		अवरोध;
	हाल TDA10046_FREQ_052:
		tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_MSB, 0x0d);
		tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_LSB, 0xc7);
		अवरोध;
	हाल TDA10046_FREQ_3617:
		tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_MSB, 0xd7);
		tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_LSB, 0x59);
		अवरोध;
	हाल TDA10046_FREQ_3613:
		tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_MSB, 0xd7);
		tda1004x_ग_लिखो_byteI(state, TDA10046H_FREQ_PHY2_LSB, 0x3f);
		अवरोध;
	पूर्ण
	tda10046h_set_bandwidth(state, 8000000); /* शेष bandwidth 8 MHz */
	/* let the PLLs settle */
	msleep(120);
पूर्ण

अटल पूर्णांक tda10046_fwupload(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक ret, confc4;
	स्थिर काष्ठा firmware *fw;

	/* reset + wake up chip */
	अगर (state->config->xtal_freq == TDA10046_XTAL_4M) अणु
		confc4 = 0;
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("%s: 16MHz Xtal, reducing I2C speed\n", __func__);
		confc4 = 0x80;
	पूर्ण
	tda1004x_ग_लिखो_byteI(state, TDA1004X_CONFC4, confc4);

	tda1004x_ग_लिखो_mask(state, TDA10046H_CONF_TRISTATE1, 1, 0);
	/* set GPIO 1 and 3 */
	अगर (state->config->gpio_config != TDA10046_GPTRI) अणु
		tda1004x_ग_लिखो_byteI(state, TDA10046H_CONF_TRISTATE2, 0x33);
		tda1004x_ग_लिखो_mask(state, TDA10046H_CONF_POLARITY, 0x0f, state->config->gpio_config &0x0f);
	पूर्ण
	/* let the घड़ीs recover from sleep */
	msleep(10);

	/* The PLLs need to be reprogrammed after sleep */
	tda10046_init_plls(fe);
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFADC2, 0xc0, 0);

	/* करोn't re-upload unless necessary */
	अगर (tda1004x_check_upload_ok(state) == 0)
		वापस 0;

	/*
	   For i2c normal work, we need to slow करोwn the bus speed.
	   However, the slow करोwn अवरोधs the eeprom firmware load.
	   So, use normal speed क्रम eeprom booting and then restore the
	   i2c speed after that. Tested with MSI TV @nyware A/D board,
	   that comes with firmware version 29 inside their eeprom.

	   It should also be noticed that no other I2C transfer should
	   be in course जबतक booting from eeprom, otherwise, tda10046
	   goes पूर्णांकo an instable state. So, proper locking are needed
	   at the i2c bus master.
	 */
	prपूर्णांकk(KERN_INFO "tda1004x: trying to boot from eeprom\n");
	tda1004x_ग_लिखो_byteI(state, TDA1004X_CONFC4, 4);
	msleep(300);
	tda1004x_ग_लिखो_byteI(state, TDA1004X_CONFC4, confc4);

	/* Checks अगर eeprom firmware went without troubles */
	अगर (tda1004x_check_upload_ok(state) == 0)
		वापस 0;

	/* eeprom firmware didn't work. Load one manually. */

	अगर (state->config->request_firmware != शून्य) अणु
		/* request the firmware, this will block until someone uploads it */
		prपूर्णांकk(KERN_INFO "tda1004x: waiting for firmware upload...\n");
		ret = state->config->request_firmware(fe, &fw, TDA10046_DEFAULT_FIRMWARE);
		अगर (ret) अणु
			/* reमुख्य compatible to old bug: try to load with tda10045 image name */
			ret = state->config->request_firmware(fe, &fw, TDA10045_DEFAULT_FIRMWARE);
			अगर (ret) अणु
				prपूर्णांकk(KERN_ERR "tda1004x: no firmware upload (timeout or file not found?)\n");
				वापस ret;
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_INFO "tda1004x: please rename the firmware file to %s\n",
						  TDA10046_DEFAULT_FIRMWARE);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "tda1004x: no request function defined, can't upload from file\n");
		वापस -EIO;
	पूर्ण
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 8, 8); // going to boot from HOST
	ret = tda1004x_करो_upload(state, fw->data, fw->size, TDA10046H_CODE_CPT, TDA10046H_CODE_IN);
	release_firmware(fw);
	वापस tda1004x_check_upload_ok(state);
पूर्ण

अटल पूर्णांक tda1004x_encode_fec(पूर्णांक fec)
अणु
	// convert known FEC values
	चयन (fec) अणु
	हाल FEC_1_2:
		वापस 0;
	हाल FEC_2_3:
		वापस 1;
	हाल FEC_3_4:
		वापस 2;
	हाल FEC_5_6:
		वापस 3;
	हाल FEC_7_8:
		वापस 4;
	पूर्ण

	// unsupported
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tda1004x_decode_fec(पूर्णांक tdafec)
अणु
	// convert known FEC values
	चयन (tdafec) अणु
	हाल 0:
		वापस FEC_1_2;
	हाल 1:
		वापस FEC_2_3;
	हाल 2:
		वापस FEC_3_4;
	हाल 3:
		वापस FEC_5_6;
	हाल 4:
		वापस FEC_7_8;
	पूर्ण

	// unsupported
	वापस -1;
पूर्ण

अटल पूर्णांक tda1004x_ग_लिखो(काष्ठा dvb_frontend* fe, स्थिर u8 buf[], पूर्णांक len)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;

	अगर (len != 2)
		वापस -EINVAL;

	वापस tda1004x_ग_लिखो_byteI(state, buf[0], buf[1]);
पूर्ण

अटल पूर्णांक tda10045_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;

	dprपूर्णांकk("%s\n", __func__);

	अगर (tda10045_fwupload(fe)) अणु
		prपूर्णांकk("tda1004x: firmware upload failed\n");
		वापस -EIO;
	पूर्ण

	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFADC1, 0x10, 0); // wake up the ADC

	// tda setup
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 0x20, 0); // disable DSP watchकरोg समयr
	tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 8, 0); // select HP stream
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC1, 0x40, 0); // set polarity of VAGC संकेत
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC1, 0x80, 0x80); // enable pulse समाप्तer
	tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 0x10, 0x10); // enable स्वतः offset
	tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF2, 0xC0, 0x0); // no frequency offset
	tda1004x_ग_लिखो_byteI(state, TDA1004X_CONF_TS1, 0); // setup MPEG2 TS पूर्णांकerface
	tda1004x_ग_लिखो_byteI(state, TDA1004X_CONF_TS2, 0); // setup MPEG2 TS पूर्णांकerface
	tda1004x_ग_लिखो_mask(state, TDA1004X_VBER_MSB, 0xe0, 0xa0); // 10^6 VBER measurement bits
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC1, 0x10, 0); // VAGC polarity
	tda1004x_ग_लिखो_byteI(state, TDA1004X_CONFADC1, 0x2e);

	tda1004x_ग_लिखो_mask(state, 0x1f, 0x01, state->config->invert_oclk);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10046_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	dprपूर्णांकk("%s\n", __func__);

	अगर (tda10046_fwupload(fe)) अणु
		prपूर्णांकk("tda1004x: firmware upload failed\n");
		वापस -EIO;
	पूर्ण

	// tda setup
	tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 0x20, 0); // disable DSP watchकरोg समयr
	tda1004x_ग_लिखो_byteI(state, TDA1004X_AUTO, 0x87);    // 100 ppm crystal, select HP stream
	tda1004x_ग_लिखो_byteI(state, TDA1004X_CONFC1, 0x88);      // enable pulse समाप्तer

	चयन (state->config->agc_config) अणु
	हाल TDA10046_AGC_DEFAULT:
		tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_CONF, 0x00); // AGC setup
		tda1004x_ग_लिखो_mask(state, TDA10046H_CONF_POLARITY, 0xf0, 0x60);  // set AGC polarities
		अवरोध;
	हाल TDA10046_AGC_IFO_AUTO_NEG:
		tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_CONF, 0x0a); // AGC setup
		tda1004x_ग_लिखो_mask(state, TDA10046H_CONF_POLARITY, 0xf0, 0x60);  // set AGC polarities
		अवरोध;
	हाल TDA10046_AGC_IFO_AUTO_POS:
		tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_CONF, 0x0a); // AGC setup
		tda1004x_ग_लिखो_mask(state, TDA10046H_CONF_POLARITY, 0xf0, 0x00);  // set AGC polarities
		अवरोध;
	हाल TDA10046_AGC_TDA827X:
		tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_CONF, 0x02);   // AGC setup
		tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_THR, 0x70);    // AGC Threshold
		tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_RENORM, 0x08); // Gain Renormalize
		tda1004x_ग_लिखो_mask(state, TDA10046H_CONF_POLARITY, 0xf0, 0x60);  // set AGC polarities
		अवरोध;
	पूर्ण
	अगर (state->config->ts_mode == 0) अणु
		tda1004x_ग_लिखो_mask(state, TDA10046H_CONF_TRISTATE1, 0xc0, 0x40);
		tda1004x_ग_लिखो_mask(state, 0x3a, 0x80, state->config->invert_oclk << 7);
	पूर्ण अन्यथा अणु
		tda1004x_ग_लिखो_mask(state, TDA10046H_CONF_TRISTATE1, 0xc0, 0x80);
		tda1004x_ग_लिखो_mask(state, TDA10046H_CONF_POLARITY, 0x10,
							state->config->invert_oclk << 4);
	पूर्ण
	tda1004x_ग_लिखो_byteI(state, TDA1004X_CONFADC2, 0x38);
	tda1004x_ग_लिखो_mask (state, TDA10046H_CONF_TRISTATE1, 0x3e, 0x38); // Turn IF AGC output on
	tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_TUN_MIN, 0);	  // पूर्ण
	tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_TUN_MAX, 0xff); // पूर्ण AGC min/max values
	tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_IF_MIN, 0);	  // पूर्ण
	tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_IF_MAX, 0xff);  // पूर्ण
	tda1004x_ग_लिखो_byteI(state, TDA10046H_AGC_GAINS, 0x12); // IF gain 2, TUN gain 1
	tda1004x_ग_लिखो_byteI(state, TDA10046H_CVBER_CTRL, 0x1a); // 10^6 VBER measurement bits
	tda1004x_ग_लिखो_byteI(state, TDA1004X_CONF_TS1, 7); // MPEG2 पूर्णांकerface config
	tda1004x_ग_लिखो_byteI(state, TDA1004X_CONF_TS2, 0xc0); // MPEG2 पूर्णांकerface config
	// tda1004x_ग_लिखो_mask(state, 0x50, 0x80, 0x80);         // handle out of guard echoes

	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_set_fe(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *fe_params = &fe->dtv_property_cache;
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक पंचांगp;
	पूर्णांक inversion;

	dprपूर्णांकk("%s\n", __func__);

	अगर (state->demod_type == TDA1004X_DEMOD_TDA10046) अणु
		// setup स्वतः offset
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 0x10, 0x10);
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x80, 0);
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF2, 0xC0, 0);

		// disable agc_conf[2]
		tda1004x_ग_लिखो_mask(state, TDA10046H_AGC_CONF, 4, 0);
	पूर्ण

	// set frequency
	अगर (fe->ops.tuner_ops.set_params) अणु
		fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	// Hardcoded to use स्वतः as much as possible on the TDA10045 as it
	// is very unreliable अगर AUTO mode is _not_ used.
	अगर (state->demod_type == TDA1004X_DEMOD_TDA10045) अणु
		fe_params->code_rate_HP = FEC_AUTO;
		fe_params->guard_पूर्णांकerval = GUARD_INTERVAL_AUTO;
		fe_params->transmission_mode = TRANSMISSION_MODE_AUTO;
	पूर्ण

	// Set standard params.. or put them to स्वतः
	अगर ((fe_params->code_rate_HP == FEC_AUTO) ||
		(fe_params->code_rate_LP == FEC_AUTO) ||
		(fe_params->modulation == QAM_AUTO) ||
		(fe_params->hierarchy == HIERARCHY_AUTO)) अणु
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 1, 1);	// enable स्वतः
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x03, 0);	/* turn off modulation bits */
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x60, 0);	// turn off hierarchy bits
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF2, 0x3f, 0);	// turn off FEC bits
	पूर्ण अन्यथा अणु
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 1, 0);	// disable स्वतः

		// set HP FEC
		पंचांगp = tda1004x_encode_fec(fe_params->code_rate_HP);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF2, 7, पंचांगp);

		// set LP FEC
		पंचांगp = tda1004x_encode_fec(fe_params->code_rate_LP);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF2, 0x38, पंचांगp << 3);

		/* set modulation */
		चयन (fe_params->modulation) अणु
		हाल QPSK:
			tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 3, 0);
			अवरोध;

		हाल QAM_16:
			tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 3, 1);
			अवरोध;

		हाल QAM_64:
			tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 3, 2);
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

		// set hierarchy
		चयन (fe_params->hierarchy) अणु
		हाल HIERARCHY_NONE:
			tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x60, 0 << 5);
			अवरोध;

		हाल HIERARCHY_1:
			tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x60, 1 << 5);
			अवरोध;

		हाल HIERARCHY_2:
			tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x60, 2 << 5);
			अवरोध;

		हाल HIERARCHY_4:
			tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x60, 3 << 5);
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	// set bandwidth
	चयन (state->demod_type) अणु
	हाल TDA1004X_DEMOD_TDA10045:
		tda10045h_set_bandwidth(state, fe_params->bandwidth_hz);
		अवरोध;

	हाल TDA1004X_DEMOD_TDA10046:
		tda10046h_set_bandwidth(state, fe_params->bandwidth_hz);
		अवरोध;
	पूर्ण

	// set inversion
	inversion = fe_params->inversion;
	अगर (state->config->invert)
		inversion = inversion ? INVERSION_OFF : INVERSION_ON;
	चयन (inversion) अणु
	हाल INVERSION_OFF:
		tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC1, 0x20, 0);
		अवरोध;

	हाल INVERSION_ON:
		tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC1, 0x20, 0x20);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	// set guard पूर्णांकerval
	चयन (fe_params->guard_पूर्णांकerval) अणु
	हाल GUARD_INTERVAL_1_32:
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 2, 0);
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x0c, 0 << 2);
		अवरोध;

	हाल GUARD_INTERVAL_1_16:
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 2, 0);
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x0c, 1 << 2);
		अवरोध;

	हाल GUARD_INTERVAL_1_8:
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 2, 0);
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x0c, 2 << 2);
		अवरोध;

	हाल GUARD_INTERVAL_1_4:
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 2, 0);
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x0c, 3 << 2);
		अवरोध;

	हाल GUARD_INTERVAL_AUTO:
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 2, 2);
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x0c, 0 << 2);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	// set transmission mode
	चयन (fe_params->transmission_mode) अणु
	हाल TRANSMISSION_MODE_2K:
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 4, 0);
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x10, 0 << 4);
		अवरोध;

	हाल TRANSMISSION_MODE_8K:
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 4, 0);
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x10, 1 << 4);
		अवरोध;

	हाल TRANSMISSION_MODE_AUTO:
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 4, 4);
		tda1004x_ग_लिखो_mask(state, TDA1004X_IN_CONF1, 0x10, 0);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	// start the lock
	चयन (state->demod_type) अणु
	हाल TDA1004X_DEMOD_TDA10045:
		tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 8, 8);
		tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 8, 0);
		अवरोध;

	हाल TDA1004X_DEMOD_TDA10046:
		tda1004x_ग_लिखो_mask(state, TDA1004X_AUTO, 0x40, 0x40);
		msleep(1);
		tda1004x_ग_लिखो_mask(state, TDA10046H_AGC_CONF, 4, 1);
		अवरोध;
	पूर्ण

	msleep(10);

	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_get_fe(काष्ठा dvb_frontend *fe,
			   काष्ठा dtv_frontend_properties *fe_params)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक status;

	dprपूर्णांकk("%s\n", __func__);

	status = tda1004x_पढ़ो_byte(state, TDA1004X_STATUS_CD);
	अगर (status == -1)
		वापस -EIO;

	/* Only update the properties cache अगर device is locked */
	अगर (!(status & 8))
		वापस 0;

	// inversion status
	fe_params->inversion = INVERSION_OFF;
	अगर (tda1004x_पढ़ो_byte(state, TDA1004X_CONFC1) & 0x20)
		fe_params->inversion = INVERSION_ON;
	अगर (state->config->invert)
		fe_params->inversion = fe_params->inversion ? INVERSION_OFF : INVERSION_ON;

	// bandwidth
	चयन (state->demod_type) अणु
	हाल TDA1004X_DEMOD_TDA10045:
		चयन (tda1004x_पढ़ो_byte(state, TDA10045H_WREF_LSB)) अणु
		हाल 0x14:
			fe_params->bandwidth_hz = 8000000;
			अवरोध;
		हाल 0xdb:
			fe_params->bandwidth_hz = 7000000;
			अवरोध;
		हाल 0x4f:
			fe_params->bandwidth_hz = 6000000;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल TDA1004X_DEMOD_TDA10046:
		चयन (tda1004x_पढ़ो_byte(state, TDA10046H_TIME_WREF1)) अणु
		हाल 0x5c:
		हाल 0x54:
			fe_params->bandwidth_hz = 8000000;
			अवरोध;
		हाल 0x6a:
		हाल 0x60:
			fe_params->bandwidth_hz = 7000000;
			अवरोध;
		हाल 0x7b:
		हाल 0x70:
			fe_params->bandwidth_hz = 6000000;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	// FEC
	fe_params->code_rate_HP =
	    tda1004x_decode_fec(tda1004x_पढ़ो_byte(state, TDA1004X_OUT_CONF2) & 7);
	fe_params->code_rate_LP =
	    tda1004x_decode_fec((tda1004x_पढ़ो_byte(state, TDA1004X_OUT_CONF2) >> 3) & 7);

	/* modulation */
	चयन (tda1004x_पढ़ो_byte(state, TDA1004X_OUT_CONF1) & 3) अणु
	हाल 0:
		fe_params->modulation = QPSK;
		अवरोध;
	हाल 1:
		fe_params->modulation = QAM_16;
		अवरोध;
	हाल 2:
		fe_params->modulation = QAM_64;
		अवरोध;
	पूर्ण

	// transmission mode
	fe_params->transmission_mode = TRANSMISSION_MODE_2K;
	अगर (tda1004x_पढ़ो_byte(state, TDA1004X_OUT_CONF1) & 0x10)
		fe_params->transmission_mode = TRANSMISSION_MODE_8K;

	// guard पूर्णांकerval
	चयन ((tda1004x_पढ़ो_byte(state, TDA1004X_OUT_CONF1) & 0x0c) >> 2) अणु
	हाल 0:
		fe_params->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल 1:
		fe_params->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल 2:
		fe_params->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		fe_params->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		अवरोध;
	पूर्ण

	// hierarchy
	चयन ((tda1004x_पढ़ो_byte(state, TDA1004X_OUT_CONF1) & 0x60) >> 5) अणु
	हाल 0:
		fe_params->hierarchy = HIERARCHY_NONE;
		अवरोध;
	हाल 1:
		fe_params->hierarchy = HIERARCHY_1;
		अवरोध;
	हाल 2:
		fe_params->hierarchy = HIERARCHY_2;
		अवरोध;
	हाल 3:
		fe_params->hierarchy = HIERARCHY_4;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_पढ़ो_status(काष्ठा dvb_frontend *fe,
				क्रमागत fe_status *fe_status)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक status;
	पूर्णांक cber;
	पूर्णांक vber;

	dprपूर्णांकk("%s\n", __func__);

	// पढ़ो status
	status = tda1004x_पढ़ो_byte(state, TDA1004X_STATUS_CD);
	अगर (status == -1)
		वापस -EIO;

	// decode
	*fe_status = 0;
	अगर (status & 4)
		*fe_status |= FE_HAS_SIGNAL;
	अगर (status & 2)
		*fe_status |= FE_HAS_CARRIER;
	अगर (status & 8)
		*fe_status |= FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;

	// अगर we करोn't alपढ़ोy have VITERBI (i.e. not LOCKED), see अगर the viterbi
	// is getting anything valid
	अगर (!(*fe_status & FE_HAS_VITERBI)) अणु
		// पढ़ो the CBER
		cber = tda1004x_पढ़ो_byte(state, TDA1004X_CBER_LSB);
		अगर (cber == -1)
			वापस -EIO;
		status = tda1004x_पढ़ो_byte(state, TDA1004X_CBER_MSB);
		अगर (status == -1)
			वापस -EIO;
		cber |= (status << 8);
		// The address 0x20 should be पढ़ो to cope with a TDA10046 bug
		tda1004x_पढ़ो_byte(state, TDA1004X_CBER_RESET);

		अगर (cber != 65535)
			*fe_status |= FE_HAS_VITERBI;
	पूर्ण

	// अगर we DO have some valid VITERBI output, but करोn't alपढ़ोy have SYNC
	// bytes (i.e. not LOCKED), see अगर the RS decoder is getting anything valid.
	अगर ((*fe_status & FE_HAS_VITERBI) && (!(*fe_status & FE_HAS_SYNC))) अणु
		// पढ़ो the VBER
		vber = tda1004x_पढ़ो_byte(state, TDA1004X_VBER_LSB);
		अगर (vber == -1)
			वापस -EIO;
		status = tda1004x_पढ़ो_byte(state, TDA1004X_VBER_MID);
		अगर (status == -1)
			वापस -EIO;
		vber |= (status << 8);
		status = tda1004x_पढ़ो_byte(state, TDA1004X_VBER_MSB);
		अगर (status == -1)
			वापस -EIO;
		vber |= (status & 0x0f) << 16;
		// The CVBER_LUT should be पढ़ो to cope with TDA10046 hardware bug
		tda1004x_पढ़ो_byte(state, TDA1004X_CVBER_LUT);

		// अगर RS has passed some valid TS packets, then we must be
		// getting some SYNC bytes
		अगर (vber < 16632)
			*fe_status |= FE_HAS_SYNC;
	पूर्ण

	// success
	dprपूर्णांकk("%s: fe_status=0x%x\n", __func__, *fe_status);
	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16 * संकेत)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक पंचांगp;
	पूर्णांक reg = 0;

	dprपूर्णांकk("%s\n", __func__);

	// determine the रेजिस्टर to use
	चयन (state->demod_type) अणु
	हाल TDA1004X_DEMOD_TDA10045:
		reg = TDA10045H_S_AGC;
		अवरोध;

	हाल TDA1004X_DEMOD_TDA10046:
		reg = TDA10046H_AGC_IF_LEVEL;
		अवरोध;
	पूर्ण

	// पढ़ो it
	पंचांगp = tda1004x_पढ़ो_byte(state, reg);
	अगर (पंचांगp < 0)
		वापस -EIO;

	*संकेत = (पंचांगp << 8) | पंचांगp;
	dprपूर्णांकk("%s: signal=0x%x\n", __func__, *संकेत);
	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16 * snr)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक पंचांगp;

	dprपूर्णांकk("%s\n", __func__);

	// पढ़ो it
	पंचांगp = tda1004x_पढ़ो_byte(state, TDA1004X_SNR);
	अगर (पंचांगp < 0)
		वापस -EIO;
	पंचांगp = 255 - पंचांगp;

	*snr = ((पंचांगp << 8) | पंचांगp);
	dprपूर्णांकk("%s: snr=0x%x\n", __func__, *snr);
	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक पंचांगp;
	पूर्णांक पंचांगp2;
	पूर्णांक counter;

	dprपूर्णांकk("%s\n", __func__);

	// पढ़ो the UCBLOCKS and reset
	counter = 0;
	पंचांगp = tda1004x_पढ़ो_byte(state, TDA1004X_UNCOR);
	अगर (पंचांगp < 0)
		वापस -EIO;
	पंचांगp &= 0x7f;
	जबतक (counter++ < 5) अणु
		tda1004x_ग_लिखो_mask(state, TDA1004X_UNCOR, 0x80, 0);
		tda1004x_ग_लिखो_mask(state, TDA1004X_UNCOR, 0x80, 0);
		tda1004x_ग_लिखो_mask(state, TDA1004X_UNCOR, 0x80, 0);

		पंचांगp2 = tda1004x_पढ़ो_byte(state, TDA1004X_UNCOR);
		अगर (पंचांगp2 < 0)
			वापस -EIO;
		पंचांगp2 &= 0x7f;
		अगर ((पंचांगp2 < पंचांगp) || (पंचांगp2 == 0))
			अवरोध;
	पूर्ण

	अगर (पंचांगp != 0x7f)
		*ucblocks = पंचांगp;
	अन्यथा
		*ucblocks = 0xffffffff;

	dprपूर्णांकk("%s: ucblocks=0x%x\n", __func__, *ucblocks);
	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक पंचांगp;

	dprपूर्णांकk("%s\n", __func__);

	// पढ़ो it in
	पंचांगp = tda1004x_पढ़ो_byte(state, TDA1004X_CBER_LSB);
	अगर (पंचांगp < 0)
		वापस -EIO;
	*ber = पंचांगp << 1;
	पंचांगp = tda1004x_पढ़ो_byte(state, TDA1004X_CBER_MSB);
	अगर (पंचांगp < 0)
		वापस -EIO;
	*ber |= (पंचांगp << 9);
	// The address 0x20 should be पढ़ो to cope with a TDA10046 bug
	tda1004x_पढ़ो_byte(state, TDA1004X_CBER_RESET);

	dprपूर्णांकk("%s: ber=0x%x\n", __func__, *ber);
	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_sleep(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;
	पूर्णांक gpio_conf;

	चयन (state->demod_type) अणु
	हाल TDA1004X_DEMOD_TDA10045:
		tda1004x_ग_लिखो_mask(state, TDA1004X_CONFADC1, 0x10, 0x10);
		अवरोध;

	हाल TDA1004X_DEMOD_TDA10046:
		/* set outमाला_दो to tristate */
		tda1004x_ग_लिखो_byteI(state, TDA10046H_CONF_TRISTATE1, 0xff);
		/* invert GPIO 1 and 3 अगर desired*/
		gpio_conf = state->config->gpio_config;
		अगर (gpio_conf >= TDA10046_GP00_I)
			tda1004x_ग_लिखो_mask(state, TDA10046H_CONF_POLARITY, 0x0f,
							(gpio_conf & 0x0f) ^ 0x0a);

		tda1004x_ग_लिखो_mask(state, TDA1004X_CONFADC2, 0xc0, 0xc0);
		tda1004x_ग_लिखो_mask(state, TDA1004X_CONFC4, 1, 1);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda1004x_i2c_gate_ctrl(काष्ठा dvb_frontend* fe, पूर्णांक enable)
अणु
	काष्ठा tda1004x_state* state = fe->demodulator_priv;

	अगर (enable) अणु
		वापस tda1004x_enable_tuner_i2c(state);
	पूर्ण अन्यथा अणु
		वापस tda1004x_disable_tuner_i2c(state);
	पूर्ण
पूर्ण

अटल पूर्णांक tda1004x_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
	fesettings->min_delay_ms = 800;
	/* Drअगरt compensation makes no sense क्रम DVB-T */
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल व्योम tda1004x_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा tda1004x_state *state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda10045_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "Philips TDA10045H DVB-T",
		.frequency_min_hz =  51 * MHz,
		.frequency_max_hz = 858 * MHz,
		.frequency_stepsize_hz = 166667,
		.caps =
		    FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		    FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		    FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		    FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_GUARD_INTERVAL_AUTO
	पूर्ण,

	.release = tda1004x_release,

	.init = tda10045_init,
	.sleep = tda1004x_sleep,
	.ग_लिखो = tda1004x_ग_लिखो,
	.i2c_gate_ctrl = tda1004x_i2c_gate_ctrl,

	.set_frontend = tda1004x_set_fe,
	.get_frontend = tda1004x_get_fe,
	.get_tune_settings = tda1004x_get_tune_settings,

	.पढ़ो_status = tda1004x_पढ़ो_status,
	.पढ़ो_ber = tda1004x_पढ़ो_ber,
	.पढ़ो_संकेत_strength = tda1004x_पढ़ो_संकेत_strength,
	.पढ़ो_snr = tda1004x_पढ़ो_snr,
	.पढ़ो_ucblocks = tda1004x_पढ़ो_ucblocks,
पूर्ण;

काष्ठा dvb_frontend* tda10045_attach(स्थिर काष्ठा tda1004x_config* config,
				     काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा tda1004x_state *state;
	पूर्णांक id;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा tda1004x_state), GFP_KERNEL);
	अगर (!state) अणु
		prपूर्णांकk(KERN_ERR "Can't allocate memory for tda10045 state\n");
		वापस शून्य;
	पूर्ण

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->demod_type = TDA1004X_DEMOD_TDA10045;

	/* check अगर the demod is there */
	id = tda1004x_पढ़ो_byte(state, TDA1004X_CHIPID);
	अगर (id < 0) अणु
		prपूर्णांकk(KERN_ERR "tda10045: chip is not answering. Giving up.\n");
		kमुक्त(state);
		वापस शून्य;
	पूर्ण

	अगर (id != 0x25) अणु
		prपूर्णांकk(KERN_ERR "Invalid tda1004x ID = 0x%02x. Can't proceed\n", id);
		kमुक्त(state);
		वापस शून्य;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &tda10045_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda10046_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "Philips TDA10046H DVB-T",
		.frequency_min_hz =  51 * MHz,
		.frequency_max_hz = 858 * MHz,
		.frequency_stepsize_hz = 166667,
		.caps =
		    FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		    FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		    FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		    FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_GUARD_INTERVAL_AUTO
	पूर्ण,

	.release = tda1004x_release,

	.init = tda10046_init,
	.sleep = tda1004x_sleep,
	.ग_लिखो = tda1004x_ग_लिखो,
	.i2c_gate_ctrl = tda1004x_i2c_gate_ctrl,

	.set_frontend = tda1004x_set_fe,
	.get_frontend = tda1004x_get_fe,
	.get_tune_settings = tda1004x_get_tune_settings,

	.पढ़ो_status = tda1004x_पढ़ो_status,
	.पढ़ो_ber = tda1004x_पढ़ो_ber,
	.पढ़ो_संकेत_strength = tda1004x_पढ़ो_संकेत_strength,
	.पढ़ो_snr = tda1004x_पढ़ो_snr,
	.पढ़ो_ucblocks = tda1004x_पढ़ो_ucblocks,
पूर्ण;

काष्ठा dvb_frontend* tda10046_attach(स्थिर काष्ठा tda1004x_config* config,
				     काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा tda1004x_state *state;
	पूर्णांक id;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा tda1004x_state), GFP_KERNEL);
	अगर (!state) अणु
		prपूर्णांकk(KERN_ERR "Can't allocate memory for tda10046 state\n");
		वापस शून्य;
	पूर्ण

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->demod_type = TDA1004X_DEMOD_TDA10046;

	/* check अगर the demod is there */
	id = tda1004x_पढ़ो_byte(state, TDA1004X_CHIPID);
	अगर (id < 0) अणु
		prपूर्णांकk(KERN_ERR "tda10046: chip is not answering. Giving up.\n");
		kमुक्त(state);
		वापस शून्य;
	पूर्ण
	अगर (id != 0x46) अणु
		prपूर्णांकk(KERN_ERR "Invalid tda1004x ID = 0x%02x. Can't proceed\n", id);
		kमुक्त(state);
		वापस शून्य;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &tda10046_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;
पूर्ण

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("Philips TDA10045H & TDA10046H DVB-T Demodulator");
MODULE_AUTHOR("Andrew de Quincey & Robert Schlabbach");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(tda10045_attach);
EXPORT_SYMBOL(tda10046_attach);
