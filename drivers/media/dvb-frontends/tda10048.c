<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    NXP TDA10048HN DVB OFDM demodulator driver

    Copyright (C) 2009 Steven Toth <stoth@kernelद_असल.com>


*/

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/math64.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_गणित.स>
#समावेश "tda10048.h"

#घोषणा TDA10048_DEFAULT_FIRMWARE "dvb-fe-tda10048-1.0.fw"
#घोषणा TDA10048_DEFAULT_FIRMWARE_SIZE 24878

/* Register name definitions */
#घोषणा TDA10048_IDENTITY          0x00
#घोषणा TDA10048_VERSION           0x01
#घोषणा TDA10048_DSP_CODE_CPT      0x0C
#घोषणा TDA10048_DSP_CODE_IN       0x0E
#घोषणा TDA10048_IN_CONF1          0x10
#घोषणा TDA10048_IN_CONF2          0x11
#घोषणा TDA10048_IN_CONF3          0x12
#घोषणा TDA10048_OUT_CONF1         0x14
#घोषणा TDA10048_OUT_CONF2         0x15
#घोषणा TDA10048_OUT_CONF3         0x16
#घोषणा TDA10048_AUTO              0x18
#घोषणा TDA10048_SYNC_STATUS       0x1A
#घोषणा TDA10048_CONF_C4_1         0x1E
#घोषणा TDA10048_CONF_C4_2         0x1F
#घोषणा TDA10048_CODE_IN_RAM       0x20
#घोषणा TDA10048_CHANNEL_INFO1_R   0x22
#घोषणा TDA10048_CHANNEL_INFO2_R   0x23
#घोषणा TDA10048_CHANNEL_INFO1     0x24
#घोषणा TDA10048_CHANNEL_INFO2     0x25
#घोषणा TDA10048_TIME_ERROR_R      0x26
#घोषणा TDA10048_TIME_ERROR        0x27
#घोषणा TDA10048_FREQ_ERROR_LSB_R  0x28
#घोषणा TDA10048_FREQ_ERROR_MSB_R  0x29
#घोषणा TDA10048_FREQ_ERROR_LSB    0x2A
#घोषणा TDA10048_FREQ_ERROR_MSB    0x2B
#घोषणा TDA10048_IT_SEL            0x30
#घोषणा TDA10048_IT_STAT           0x32
#घोषणा TDA10048_DSP_AD_LSB        0x3C
#घोषणा TDA10048_DSP_AD_MSB        0x3D
#घोषणा TDA10048_DSP_REG_LSB       0x3E
#घोषणा TDA10048_DSP_REG_MSB       0x3F
#घोषणा TDA10048_CONF_TRISTATE1    0x44
#घोषणा TDA10048_CONF_TRISTATE2    0x45
#घोषणा TDA10048_CONF_POLARITY     0x46
#घोषणा TDA10048_GPIO_SP_DS0       0x48
#घोषणा TDA10048_GPIO_SP_DS1       0x49
#घोषणा TDA10048_GPIO_SP_DS2       0x4A
#घोषणा TDA10048_GPIO_SP_DS3       0x4B
#घोषणा TDA10048_GPIO_OUT_SEL      0x4C
#घोषणा TDA10048_GPIO_SELECT       0x4D
#घोषणा TDA10048_IC_MODE           0x4E
#घोषणा TDA10048_CONF_XO           0x50
#घोषणा TDA10048_CONF_PLL1         0x51
#घोषणा TDA10048_CONF_PLL2         0x52
#घोषणा TDA10048_CONF_PLL3         0x53
#घोषणा TDA10048_CONF_ADC          0x54
#घोषणा TDA10048_CONF_ADC_2        0x55
#घोषणा TDA10048_CONF_C1_1         0x60
#घोषणा TDA10048_CONF_C1_3         0x62
#घोषणा TDA10048_AGC_CONF          0x70
#घोषणा TDA10048_AGC_THRESHOLD_LSB 0x72
#घोषणा TDA10048_AGC_THRESHOLD_MSB 0x73
#घोषणा TDA10048_AGC_RENORM        0x74
#घोषणा TDA10048_AGC_GAINS         0x76
#घोषणा TDA10048_AGC_TUN_MIN       0x78
#घोषणा TDA10048_AGC_TUN_MAX       0x79
#घोषणा TDA10048_AGC_IF_MIN        0x7A
#घोषणा TDA10048_AGC_IF_MAX        0x7B
#घोषणा TDA10048_AGC_TUN_LEVEL     0x7E
#घोषणा TDA10048_AGC_IF_LEVEL      0x7F
#घोषणा TDA10048_DIG_AGC_LEVEL     0x81
#घोषणा TDA10048_FREQ_PHY2_LSB     0x86
#घोषणा TDA10048_FREQ_PHY2_MSB     0x87
#घोषणा TDA10048_TIME_INVWREF_LSB  0x88
#घोषणा TDA10048_TIME_INVWREF_MSB  0x89
#घोषणा TDA10048_TIME_WREF_LSB     0x8A
#घोषणा TDA10048_TIME_WREF_MID1    0x8B
#घोषणा TDA10048_TIME_WREF_MID2    0x8C
#घोषणा TDA10048_TIME_WREF_MSB     0x8D
#घोषणा TDA10048_NP_OUT            0xA2
#घोषणा TDA10048_CELL_ID_LSB       0xA4
#घोषणा TDA10048_CELL_ID_MSB       0xA5
#घोषणा TDA10048_EXTTPS_ODD        0xAA
#घोषणा TDA10048_EXTTPS_EVEN       0xAB
#घोषणा TDA10048_TPS_LENGTH        0xAC
#घोषणा TDA10048_FREE_REG_1        0xB2
#घोषणा TDA10048_FREE_REG_2        0xB3
#घोषणा TDA10048_CONF_C3_1         0xC0
#घोषणा TDA10048_CVBER_CTRL        0xC2
#घोषणा TDA10048_CBER_NMAX_LSB     0xC4
#घोषणा TDA10048_CBER_NMAX_MSB     0xC5
#घोषणा TDA10048_CBER_LSB          0xC6
#घोषणा TDA10048_CBER_MSB          0xC7
#घोषणा TDA10048_VBER_LSB          0xC8
#घोषणा TDA10048_VBER_MID          0xC9
#घोषणा TDA10048_VBER_MSB          0xCA
#घोषणा TDA10048_CVBER_LUT         0xCC
#घोषणा TDA10048_UNCOR_CTRL        0xCD
#घोषणा TDA10048_UNCOR_CPT_LSB     0xCE
#घोषणा TDA10048_UNCOR_CPT_MSB     0xCF
#घोषणा TDA10048_SOFT_IT_C3        0xD6
#घोषणा TDA10048_CONF_TS2          0xE0
#घोषणा TDA10048_CONF_TS1          0xE1

अटल अचिन्हित पूर्णांक debug;

#घोषणा dprपूर्णांकk(level, fmt, arg...)\
	करो अणु अगर (debug >= level)\
		prपूर्णांकk(KERN_DEBUG "tda10048: " fmt, ## arg);\
	पूर्ण जबतक (0)

काष्ठा tda10048_state अणु

	काष्ठा i2c_adapter *i2c;

	/* We'll cache and update the attach config settings */
	काष्ठा tda10048_config config;
	काष्ठा dvb_frontend frontend;

	पूर्णांक fwloaded;

	u32 freq_अगर_hz;
	u32 xtal_hz;
	u32 pll_mfactor;
	u32 pll_nfactor;
	u32 pll_pfactor;
	u32 sample_freq;

	u32 bandwidth;
पूर्ण;

अटल काष्ठा init_tab अणु
	u8	reg;
	u16	data;
पूर्ण init_tab[] = अणु
	अणु TDA10048_CONF_PLL1, 0x08 पूर्ण,
	अणु TDA10048_CONF_ADC_2, 0x00 पूर्ण,
	अणु TDA10048_CONF_C4_1, 0x00 पूर्ण,
	अणु TDA10048_CONF_PLL1, 0x0f पूर्ण,
	अणु TDA10048_CONF_PLL2, 0x0a पूर्ण,
	अणु TDA10048_CONF_PLL3, 0x43 पूर्ण,
	अणु TDA10048_FREQ_PHY2_LSB, 0x02 पूर्ण,
	अणु TDA10048_FREQ_PHY2_MSB, 0x0a पूर्ण,
	अणु TDA10048_TIME_WREF_LSB, 0xbd पूर्ण,
	अणु TDA10048_TIME_WREF_MID1, 0xe4 पूर्ण,
	अणु TDA10048_TIME_WREF_MID2, 0xa8 पूर्ण,
	अणु TDA10048_TIME_WREF_MSB, 0x02 पूर्ण,
	अणु TDA10048_TIME_INVWREF_LSB, 0x04 पूर्ण,
	अणु TDA10048_TIME_INVWREF_MSB, 0x06 पूर्ण,
	अणु TDA10048_CONF_C4_1, 0x00 पूर्ण,
	अणु TDA10048_CONF_C1_1, 0xa8 पूर्ण,
	अणु TDA10048_AGC_CONF, 0x16 पूर्ण,
	अणु TDA10048_CONF_C1_3, 0x0b पूर्ण,
	अणु TDA10048_AGC_TUN_MIN, 0x00 पूर्ण,
	अणु TDA10048_AGC_TUN_MAX, 0xff पूर्ण,
	अणु TDA10048_AGC_IF_MIN, 0x00 पूर्ण,
	अणु TDA10048_AGC_IF_MAX, 0xff पूर्ण,
	अणु TDA10048_AGC_THRESHOLD_MSB, 0x00 पूर्ण,
	अणु TDA10048_AGC_THRESHOLD_LSB, 0x70 पूर्ण,
	अणु TDA10048_CVBER_CTRL, 0x38 पूर्ण,
	अणु TDA10048_AGC_GAINS, 0x12 पूर्ण,
	अणु TDA10048_CONF_XO, 0x00 पूर्ण,
	अणु TDA10048_CONF_TS1, 0x07 पूर्ण,
	अणु TDA10048_IC_MODE, 0x00 पूर्ण,
	अणु TDA10048_CONF_TS2, 0xc0 पूर्ण,
	अणु TDA10048_CONF_TRISTATE1, 0x21 पूर्ण,
	अणु TDA10048_CONF_TRISTATE2, 0x00 पूर्ण,
	अणु TDA10048_CONF_POLARITY, 0x00 पूर्ण,
	अणु TDA10048_CONF_C4_2, 0x04 पूर्ण,
	अणु TDA10048_CONF_ADC, 0x60 पूर्ण,
	अणु TDA10048_CONF_ADC_2, 0x10 पूर्ण,
	अणु TDA10048_CONF_ADC, 0x60 पूर्ण,
	अणु TDA10048_CONF_ADC_2, 0x00 पूर्ण,
	अणु TDA10048_CONF_C1_1, 0xa8 पूर्ण,
	अणु TDA10048_UNCOR_CTRL, 0x00 पूर्ण,
	अणु TDA10048_CONF_C4_2, 0x04 पूर्ण,
पूर्ण;

अटल काष्ठा pll_tab अणु
	u32	clk_freq_khz;
	u32	अगर_freq_khz;
पूर्ण pll_tab[] = अणु
	अणु TDA10048_CLK_4000,  TDA10048_IF_36130 पूर्ण,
	अणु TDA10048_CLK_16000, TDA10048_IF_3300 पूर्ण,
	अणु TDA10048_CLK_16000, TDA10048_IF_3500 पूर्ण,
	अणु TDA10048_CLK_16000, TDA10048_IF_3800 पूर्ण,
	अणु TDA10048_CLK_16000, TDA10048_IF_4000 पूर्ण,
	अणु TDA10048_CLK_16000, TDA10048_IF_4300 पूर्ण,
	अणु TDA10048_CLK_16000, TDA10048_IF_4500 पूर्ण,
	अणु TDA10048_CLK_16000, TDA10048_IF_5000 पूर्ण,
	अणु TDA10048_CLK_16000, TDA10048_IF_36130 पूर्ण,
पूर्ण;

अटल पूर्णांक tda10048_ग_लिखोreg(काष्ठा tda10048_state *state, u8 reg, u8 data)
अणु
	काष्ठा tda10048_config *config = &state->config;
	पूर्णांक ret;
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = config->demod_address,
		.flags = 0, .buf = buf, .len = 2 पूर्ण;

	dprपूर्णांकk(2, "%s(reg = 0x%02x, data = 0x%02x)\n", __func__, reg, data);

	ret = i2c_transfer(state->i2c, &msg, 1);

	अगर (ret != 1)
		prपूर्णांकk("%s: writereg error (ret == %i)\n", __func__, ret);

	वापस (ret != 1) ? -1 : 0;
पूर्ण

अटल u8 tda10048_पढ़ोreg(काष्ठा tda10048_state *state, u8 reg)
अणु
	काष्ठा tda10048_config *config = &state->config;
	पूर्णांक ret;
	u8 b0[] = अणु reg पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = config->demod_address,
			.flags = 0, .buf = b0, .len = 1 पूर्ण,
		अणु .addr = config->demod_address,
			.flags = I2C_M_RD, .buf = b1, .len = 1 पूर्ण पूर्ण;

	dprपूर्णांकk(2, "%s(reg = 0x%02x)\n", __func__, reg);

	ret = i2c_transfer(state->i2c, msg, 2);

	अगर (ret != 2)
		prपूर्णांकk(KERN_ERR "%s: readreg error (ret == %i)\n",
			__func__, ret);

	वापस b1[0];
पूर्ण

अटल पूर्णांक tda10048_ग_लिखोregbulk(काष्ठा tda10048_state *state, u8 reg,
				 स्थिर u8 *data, u16 len)
अणु
	काष्ठा tda10048_config *config = &state->config;
	पूर्णांक ret = -EREMOTEIO;
	काष्ठा i2c_msg msg;
	u8 *buf;

	dprपूर्णांकk(2, "%s(%d, ?, len = %d)\n", __func__, reg, len);

	buf = kदो_स्मृति(len + 1, GFP_KERNEL);
	अगर (buf == शून्य) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	*buf = reg;
	स_नकल(buf + 1, data, len);

	msg.addr = config->demod_address;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = len + 1;

	dprपूर्णांकk(2, "%s():  write len = %d\n",
		__func__, msg.len);

	ret = i2c_transfer(state->i2c, &msg, 1);
	अगर (ret != 1) अणु
		prपूर्णांकk(KERN_ERR "%s(): writereg error err %i\n",
			 __func__, ret);
		ret = -EREMOTEIO;
	पूर्ण

error:
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक tda10048_set_phy2(काष्ठा dvb_frontend *fe, u32 sample_freq_hz,
			     u32 अगर_hz)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	u64 t;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (sample_freq_hz == 0)
		वापस -EINVAL;

	अगर (अगर_hz < (sample_freq_hz / 2)) अणु
		/* PHY2 = (अगर2/fs) * 2^15 */
		t = अगर_hz;
		t *= 10;
		t *= 32768;
		करो_भाग(t, sample_freq_hz);
		t += 5;
		करो_भाग(t, 10);
	पूर्ण अन्यथा अणु
		/* PHY2 = ((IF1-fs)/fs) * 2^15 */
		t = sample_freq_hz - अगर_hz;
		t *= 10;
		t *= 32768;
		करो_भाग(t, sample_freq_hz);
		t += 5;
		करो_भाग(t, 10);
		t = ~t + 1;
	पूर्ण

	tda10048_ग_लिखोreg(state, TDA10048_FREQ_PHY2_LSB, (u8)t);
	tda10048_ग_लिखोreg(state, TDA10048_FREQ_PHY2_MSB, (u8)(t >> 8));

	वापस 0;
पूर्ण

अटल पूर्णांक tda10048_set_wref(काष्ठा dvb_frontend *fe, u32 sample_freq_hz,
			     u32 bw)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	u64 t, z;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (sample_freq_hz == 0)
		वापस -EINVAL;

	/* WREF = (B / (7 * fs)) * 2^31 */
	t = bw * 10;
	/* aव्योम warning: this decimal स्थिरant is अचिन्हित only in ISO C90 */
	/* t *= 2147483648 on 32bit platक्रमms */
	t *= (2048 * 1024);
	t *= 1024;
	z = 7 * sample_freq_hz;
	करो_भाग(t, z);
	t += 5;
	करो_भाग(t, 10);

	tda10048_ग_लिखोreg(state, TDA10048_TIME_WREF_LSB, (u8)t);
	tda10048_ग_लिखोreg(state, TDA10048_TIME_WREF_MID1, (u8)(t >> 8));
	tda10048_ग_लिखोreg(state, TDA10048_TIME_WREF_MID2, (u8)(t >> 16));
	tda10048_ग_लिखोreg(state, TDA10048_TIME_WREF_MSB, (u8)(t >> 24));

	वापस 0;
पूर्ण

अटल पूर्णांक tda10048_set_invwref(काष्ठा dvb_frontend *fe, u32 sample_freq_hz,
				u32 bw)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	u64 t;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (sample_freq_hz == 0)
		वापस -EINVAL;

	/* INVWREF = ((7 * fs) / B) * 2^5 */
	t = sample_freq_hz;
	t *= 7;
	t *= 32;
	t *= 10;
	करो_भाग(t, bw);
	t += 5;
	करो_भाग(t, 10);

	tda10048_ग_लिखोreg(state, TDA10048_TIME_INVWREF_LSB, (u8)t);
	tda10048_ग_लिखोreg(state, TDA10048_TIME_INVWREF_MSB, (u8)(t >> 8));

	वापस 0;
पूर्ण

अटल पूर्णांक tda10048_set_bandwidth(काष्ठा dvb_frontend *fe,
	u32 bw)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	dprपूर्णांकk(1, "%s(bw=%d)\n", __func__, bw);

	/* Bandwidth setting may need to be adjusted */
	चयन (bw) अणु
	हाल 6000000:
	हाल 7000000:
	हाल 8000000:
		tda10048_set_wref(fe, state->sample_freq, bw);
		tda10048_set_invwref(fe, state->sample_freq, bw);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s() invalid bandwidth\n", __func__);
		वापस -EINVAL;
	पूर्ण

	state->bandwidth = bw;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10048_set_अगर(काष्ठा dvb_frontend *fe, u32 bw)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	काष्ठा tda10048_config *config = &state->config;
	पूर्णांक i;
	u32 अगर_freq_khz;

	dprपूर्णांकk(1, "%s(bw = %d)\n", __func__, bw);

	/* based on target bandwidth and clk we calculate pll factors */
	चयन (bw) अणु
	हाल 6000000:
		अगर_freq_khz = config->dtv6_अगर_freq_khz;
		अवरोध;
	हाल 7000000:
		अगर_freq_khz = config->dtv7_अगर_freq_khz;
		अवरोध;
	हाल 8000000:
		अगर_freq_khz = config->dtv8_अगर_freq_khz;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s() no default\n", __func__);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(pll_tab); i++) अणु
		अगर ((pll_tab[i].clk_freq_khz == config->clk_freq_khz) &&
			(pll_tab[i].अगर_freq_khz == अगर_freq_khz)) अणु

			state->freq_अगर_hz = pll_tab[i].अगर_freq_khz * 1000;
			state->xtal_hz = pll_tab[i].clk_freq_khz * 1000;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(pll_tab)) अणु
		prपूर्णांकk(KERN_ERR "%s() Incorrect attach settings\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk(1, "- freq_if_hz = %d\n", state->freq_अगर_hz);
	dprपूर्णांकk(1, "- xtal_hz = %d\n", state->xtal_hz);
	dprपूर्णांकk(1, "- pll_mfactor = %d\n", state->pll_mfactor);
	dprपूर्णांकk(1, "- pll_nfactor = %d\n", state->pll_nfactor);
	dprपूर्णांकk(1, "- pll_pfactor = %d\n", state->pll_pfactor);

	/* Calculate the sample frequency */
	state->sample_freq = state->xtal_hz * (state->pll_mfactor + 45);
	state->sample_freq /= (state->pll_nfactor + 1);
	state->sample_freq /= (state->pll_pfactor + 4);
	dprपूर्णांकk(1, "- sample_freq = %d\n", state->sample_freq);

	/* Update the I/F */
	tda10048_set_phy2(fe, state->sample_freq, state->freq_अगर_hz);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10048_firmware_upload(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	काष्ठा tda10048_config *config = &state->config;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;
	पूर्णांक pos = 0;
	पूर्णांक cnt;
	u8 wlen = config->fwbulkग_लिखोlen;

	अगर ((wlen != TDA10048_BULKWRITE_200) && (wlen != TDA10048_BULKWRITE_50))
		wlen = TDA10048_BULKWRITE_200;

	/* request the firmware, this will block and समयout */
	prपूर्णांकk(KERN_INFO "%s: waiting for firmware upload (%s)...\n",
		__func__,
		TDA10048_DEFAULT_FIRMWARE);

	ret = request_firmware(&fw, TDA10048_DEFAULT_FIRMWARE,
		state->i2c->dev.parent);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: Upload failed. (file not found?)\n",
			__func__);
		वापस -EIO;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "%s: firmware read %zu bytes.\n",
			__func__,
			fw->size);
		ret = 0;
	पूर्ण

	अगर (fw->size != TDA10048_DEFAULT_FIRMWARE_SIZE) अणु
		prपूर्णांकk(KERN_ERR "%s: firmware incorrect size\n", __func__);
		ret = -EIO;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "%s: firmware uploading\n", __func__);

		/* Soft reset */
		tda10048_ग_लिखोreg(state, TDA10048_CONF_TRISTATE1,
			tda10048_पढ़ोreg(state, TDA10048_CONF_TRISTATE1)
				& 0xfe);
		tda10048_ग_लिखोreg(state, TDA10048_CONF_TRISTATE1,
			tda10048_पढ़ोreg(state, TDA10048_CONF_TRISTATE1)
				| 0x01);

		/* Put the demod पूर्णांकo host करोwnload mode */
		tda10048_ग_लिखोreg(state, TDA10048_CONF_C4_1,
			tda10048_पढ़ोreg(state, TDA10048_CONF_C4_1) & 0xf9);

		/* Boot the DSP */
		tda10048_ग_लिखोreg(state, TDA10048_CONF_C4_1,
			tda10048_पढ़ोreg(state, TDA10048_CONF_C4_1) | 0x08);

		/* Prepare क्रम करोwnload */
		tda10048_ग_लिखोreg(state, TDA10048_DSP_CODE_CPT, 0);

		/* Download the firmware payload */
		जबतक (pos < fw->size) अणु

			अगर ((fw->size - pos) > wlen)
				cnt = wlen;
			अन्यथा
				cnt = fw->size - pos;

			tda10048_ग_लिखोregbulk(state, TDA10048_DSP_CODE_IN,
				&fw->data[pos], cnt);

			pos += cnt;
		पूर्ण

		ret = -EIO;
		/* Wait up to 250ms क्रम the DSP to boot */
		क्रम (cnt = 0; cnt < 250 ; cnt += 10) अणु

			msleep(10);

			अगर (tda10048_पढ़ोreg(state, TDA10048_SYNC_STATUS)
				& 0x40) अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	release_firmware(fw);

	अगर (ret == 0) अणु
		prपूर्णांकk(KERN_INFO "%s: firmware uploaded\n", __func__);
		state->fwloaded = 1;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "%s: firmware upload failed\n", __func__);

	वापस ret;
पूर्ण

अटल पूर्णांक tda10048_set_inversion(काष्ठा dvb_frontend *fe, पूर्णांक inversion)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;

	dprपूर्णांकk(1, "%s(%d)\n", __func__, inversion);

	अगर (inversion == TDA10048_INVERSION_ON)
		tda10048_ग_लिखोreg(state, TDA10048_CONF_C1_1,
			tda10048_पढ़ोreg(state, TDA10048_CONF_C1_1) | 0x20);
	अन्यथा
		tda10048_ग_लिखोreg(state, TDA10048_CONF_C1_1,
			tda10048_पढ़ोreg(state, TDA10048_CONF_C1_1) & 0xdf);

	वापस 0;
पूर्ण

/* Retrieve the demod settings */
अटल पूर्णांक tda10048_get_tps(काष्ठा tda10048_state *state,
	काष्ठा dtv_frontend_properties *p)
अणु
	u8 val;

	/* Make sure the TPS regs are valid */
	अगर (!(tda10048_पढ़ोreg(state, TDA10048_AUTO) & 0x01))
		वापस -EAGAIN;

	val = tda10048_पढ़ोreg(state, TDA10048_OUT_CONF2);
	चयन ((val & 0x60) >> 5) अणु
	हाल 0:
		p->modulation = QPSK;
		अवरोध;
	हाल 1:
		p->modulation = QAM_16;
		अवरोध;
	हाल 2:
		p->modulation = QAM_64;
		अवरोध;
	पूर्ण
	चयन ((val & 0x18) >> 3) अणु
	हाल 0:
		p->hierarchy = HIERARCHY_NONE;
		अवरोध;
	हाल 1:
		p->hierarchy = HIERARCHY_1;
		अवरोध;
	हाल 2:
		p->hierarchy = HIERARCHY_2;
		अवरोध;
	हाल 3:
		p->hierarchy = HIERARCHY_4;
		अवरोध;
	पूर्ण
	चयन (val & 0x07) अणु
	हाल 0:
		p->code_rate_HP = FEC_1_2;
		अवरोध;
	हाल 1:
		p->code_rate_HP = FEC_2_3;
		अवरोध;
	हाल 2:
		p->code_rate_HP = FEC_3_4;
		अवरोध;
	हाल 3:
		p->code_rate_HP = FEC_5_6;
		अवरोध;
	हाल 4:
		p->code_rate_HP = FEC_7_8;
		अवरोध;
	पूर्ण

	val = tda10048_पढ़ोreg(state, TDA10048_OUT_CONF3);
	चयन (val & 0x07) अणु
	हाल 0:
		p->code_rate_LP = FEC_1_2;
		अवरोध;
	हाल 1:
		p->code_rate_LP = FEC_2_3;
		अवरोध;
	हाल 2:
		p->code_rate_LP = FEC_3_4;
		अवरोध;
	हाल 3:
		p->code_rate_LP = FEC_5_6;
		अवरोध;
	हाल 4:
		p->code_rate_LP = FEC_7_8;
		अवरोध;
	पूर्ण

	val = tda10048_पढ़ोreg(state, TDA10048_OUT_CONF1);
	चयन ((val & 0x0c) >> 2) अणु
	हाल 0:
		p->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल 1:
		p->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल 2:
		p->guard_पूर्णांकerval =  GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		p->guard_पूर्णांकerval =  GUARD_INTERVAL_1_4;
		अवरोध;
	पूर्ण
	चयन (val & 0x03) अणु
	हाल 0:
		p->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		p->transmission_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda10048_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	काष्ठा tda10048_config *config = &state->config;
	dprपूर्णांकk(1, "%s(%d)\n", __func__, enable);

	अगर (config->disable_gate_access)
		वापस 0;

	अगर (enable)
		वापस tda10048_ग_लिखोreg(state, TDA10048_CONF_C4_1,
			tda10048_पढ़ोreg(state, TDA10048_CONF_C4_1) | 0x02);
	अन्यथा
		वापस tda10048_ग_लिखोreg(state, TDA10048_CONF_C4_1,
			tda10048_पढ़ोreg(state, TDA10048_CONF_C4_1) & 0xfd);
पूर्ण

अटल पूर्णांक tda10048_output_mode(काष्ठा dvb_frontend *fe, पूर्णांक serial)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	dprपूर्णांकk(1, "%s(%d)\n", __func__, serial);

	/* Ensure pins are out of tri-state */
	tda10048_ग_लिखोreg(state, TDA10048_CONF_TRISTATE1, 0x21);
	tda10048_ग_लिखोreg(state, TDA10048_CONF_TRISTATE2, 0x00);

	अगर (serial) अणु
		tda10048_ग_लिखोreg(state, TDA10048_IC_MODE, 0x80 | 0x20);
		tda10048_ग_लिखोreg(state, TDA10048_CONF_TS2, 0xc0);
	पूर्ण अन्यथा अणु
		tda10048_ग_लिखोreg(state, TDA10048_IC_MODE, 0x00);
		tda10048_ग_लिखोreg(state, TDA10048_CONF_TS2, 0x01);
	पूर्ण

	वापस 0;
पूर्ण

/* Talk to the demod, set the FEC, GUARD, QAM settings etc */
/* TODO: Support manual tuning with specअगरic params */
अटल पूर्णांक tda10048_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा tda10048_state *state = fe->demodulator_priv;

	dprपूर्णांकk(1, "%s(frequency=%d)\n", __func__, p->frequency);

	/* Update the I/F pll's अगर the bandwidth changes */
	अगर (p->bandwidth_hz != state->bandwidth) अणु
		tda10048_set_अगर(fe, p->bandwidth_hz);
		tda10048_set_bandwidth(fe, p->bandwidth_hz);
	पूर्ण

	अगर (fe->ops.tuner_ops.set_params) अणु

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		fe->ops.tuner_ops.set_params(fe);

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	/* Enable demod TPS स्वतः detection and begin acquisition */
	tda10048_ग_लिखोreg(state, TDA10048_AUTO, 0x57);
	/* trigger cber and vber acquisition */
	tda10048_ग_लिखोreg(state, TDA10048_CVBER_CTRL, 0x3B);

	वापस 0;
पूर्ण

/* Establish sane शेषs and load firmware. */
अटल पूर्णांक tda10048_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	काष्ठा tda10048_config *config = &state->config;
	पूर्णांक ret = 0, i;

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* PLL */
	init_tab[4].data = (u8)(state->pll_mfactor);
	init_tab[5].data = (u8)(state->pll_nfactor) | 0x40;

	/* Apply रेजिस्टर शेषs */
	क्रम (i = 0; i < ARRAY_SIZE(init_tab); i++)
		tda10048_ग_लिखोreg(state, init_tab[i].reg, init_tab[i].data);

	अगर (state->fwloaded == 0)
		ret = tda10048_firmware_upload(fe);

	/* Set either serial or parallel */
	tda10048_output_mode(fe, config->output_mode);

	/* Set inversion */
	tda10048_set_inversion(fe, config->inversion);

	/* Establish शेष RF values */
	tda10048_set_अगर(fe, 8000000);
	tda10048_set_bandwidth(fe, 8000000);

	/* Ensure we leave the gate बंदd */
	tda10048_i2c_gate_ctrl(fe, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक tda10048_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	u8 reg;

	*status = 0;

	reg = tda10048_पढ़ोreg(state, TDA10048_SYNC_STATUS);

	dprपूर्णांकk(1, "%s() status =0x%02x\n", __func__, reg);

	अगर (reg & 0x02)
		*status |= FE_HAS_CARRIER;

	अगर (reg & 0x04)
		*status |= FE_HAS_SIGNAL;

	अगर (reg & 0x08) अणु
		*status |= FE_HAS_LOCK;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_SYNC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tda10048_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	अटल u32 cber_current;
	u32 cber_nmax;
	u64 cber_पंचांगp;

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* update cber on पूर्णांकerrupt */
	अगर (tda10048_पढ़ोreg(state, TDA10048_SOFT_IT_C3) & 0x01) अणु
		cber_पंचांगp = tda10048_पढ़ोreg(state, TDA10048_CBER_MSB) << 8 |
			tda10048_पढ़ोreg(state, TDA10048_CBER_LSB);
		cber_nmax = tda10048_पढ़ोreg(state, TDA10048_CBER_NMAX_MSB) << 8 |
			tda10048_पढ़ोreg(state, TDA10048_CBER_NMAX_LSB);
		cber_पंचांगp *= 100000000;
		cber_पंचांगp *= 2;
		cber_पंचांगp = भाग_u64(cber_पंचांगp, (cber_nmax * 32) + 1);
		cber_current = (u32)cber_पंचांगp;
		/* retrigger cber acquisition */
		tda10048_ग_लिखोreg(state, TDA10048_CVBER_CTRL, 0x39);
	पूर्ण
	/* actual cber is (*ber)/1e8 */
	*ber = cber_current;

	वापस 0;
पूर्ण

अटल पूर्णांक tda10048_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
	u16 *संकेत_strength)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	u8 v;

	dprपूर्णांकk(1, "%s()\n", __func__);

	*संकेत_strength = 65535;

	v = tda10048_पढ़ोreg(state, TDA10048_NP_OUT);
	अगर (v > 0)
		*संकेत_strength -= (v << 8) | v;

	वापस 0;
पूर्ण

/* SNR lookup table */
अटल काष्ठा snr_tab अणु
	u8 val;
	u8 data;
पूर्ण snr_tab[] = अणु
	अणु   0,   0 पूर्ण,
	अणु   1, 246 पूर्ण,
	अणु   2, 215 पूर्ण,
	अणु   3, 198 पूर्ण,
	अणु   4, 185 पूर्ण,
	अणु   5, 176 पूर्ण,
	अणु   6, 168 पूर्ण,
	अणु   7, 161 पूर्ण,
	अणु   8, 155 पूर्ण,
	अणु   9, 150 पूर्ण,
	अणु  10, 146 पूर्ण,
	अणु  11, 141 पूर्ण,
	अणु  12, 138 पूर्ण,
	अणु  13, 134 पूर्ण,
	अणु  14, 131 पूर्ण,
	अणु  15, 128 पूर्ण,
	अणु  16, 125 पूर्ण,
	अणु  17, 122 पूर्ण,
	अणु  18, 120 पूर्ण,
	अणु  19, 118 पूर्ण,
	अणु  20, 115 पूर्ण,
	अणु  21, 113 पूर्ण,
	अणु  22, 111 पूर्ण,
	अणु  23, 109 पूर्ण,
	अणु  24, 107 पूर्ण,
	अणु  25, 106 पूर्ण,
	अणु  26, 104 पूर्ण,
	अणु  27, 102 पूर्ण,
	अणु  28, 101 पूर्ण,
	अणु  29,  99 पूर्ण,
	अणु  30,  98 पूर्ण,
	अणु  31,  96 पूर्ण,
	अणु  32,  95 पूर्ण,
	अणु  33,  94 पूर्ण,
	अणु  34,  92 पूर्ण,
	अणु  35,  91 पूर्ण,
	अणु  36,  90 पूर्ण,
	अणु  37,  89 पूर्ण,
	अणु  38,  88 पूर्ण,
	अणु  39,  86 पूर्ण,
	अणु  40,  85 पूर्ण,
	अणु  41,  84 पूर्ण,
	अणु  42,  83 पूर्ण,
	अणु  43,  82 पूर्ण,
	अणु  44,  81 पूर्ण,
	अणु  45,  80 पूर्ण,
	अणु  46,  79 पूर्ण,
	अणु  47,  78 पूर्ण,
	अणु  48,  77 पूर्ण,
	अणु  49,  76 पूर्ण,
	अणु  50,  76 पूर्ण,
	अणु  51,  75 पूर्ण,
	अणु  52,  74 पूर्ण,
	अणु  53,  73 पूर्ण,
	अणु  54,  72 पूर्ण,
	अणु  56,  71 पूर्ण,
	अणु  57,  70 पूर्ण,
	अणु  58,  69 पूर्ण,
	अणु  60,  68 पूर्ण,
	अणु  61,  67 पूर्ण,
	अणु  63,  66 पूर्ण,
	अणु  64,  65 पूर्ण,
	अणु  66,  64 पूर्ण,
	अणु  67,  63 पूर्ण,
	अणु  68,  62 पूर्ण,
	अणु  69,  62 पूर्ण,
	अणु  70,  61 पूर्ण,
	अणु  72,  60 पूर्ण,
	अणु  74,  59 पूर्ण,
	अणु  75,  58 पूर्ण,
	अणु  77,  57 पूर्ण,
	अणु  79,  56 पूर्ण,
	अणु  81,  55 पूर्ण,
	अणु  83,  54 पूर्ण,
	अणु  85,  53 पूर्ण,
	अणु  87,  52 पूर्ण,
	अणु  89,  51 पूर्ण,
	अणु  91,  50 पूर्ण,
	अणु  93,  49 पूर्ण,
	अणु  95,  48 पूर्ण,
	अणु  97,  47 पूर्ण,
	अणु 100,  46 पूर्ण,
	अणु 102,  45 पूर्ण,
	अणु 104,  44 पूर्ण,
	अणु 107,  43 पूर्ण,
	अणु 109,  42 पूर्ण,
	अणु 112,  41 पूर्ण,
	अणु 114,  40 पूर्ण,
	अणु 117,  39 पूर्ण,
	अणु 120,  38 पूर्ण,
	अणु 123,  37 पूर्ण,
	अणु 125,  36 पूर्ण,
	अणु 128,  35 पूर्ण,
	अणु 131,  34 पूर्ण,
	अणु 134,  33 पूर्ण,
	अणु 138,  32 पूर्ण,
	अणु 141,  31 पूर्ण,
	अणु 144,  30 पूर्ण,
	अणु 147,  29 पूर्ण,
	अणु 151,  28 पूर्ण,
	अणु 154,  27 पूर्ण,
	अणु 158,  26 पूर्ण,
	अणु 162,  25 पूर्ण,
	अणु 165,  24 पूर्ण,
	अणु 169,  23 पूर्ण,
	अणु 173,  22 पूर्ण,
	अणु 177,  21 पूर्ण,
	अणु 181,  20 पूर्ण,
	अणु 186,  19 पूर्ण,
	अणु 190,  18 पूर्ण,
	अणु 194,  17 पूर्ण,
	अणु 199,  16 पूर्ण,
	अणु 204,  15 पूर्ण,
	अणु 208,  14 पूर्ण,
	अणु 213,  13 पूर्ण,
	अणु 218,  12 पूर्ण,
	अणु 223,  11 पूर्ण,
	अणु 229,  10 पूर्ण,
	अणु 234,   9 पूर्ण,
	अणु 239,   8 पूर्ण,
	अणु 245,   7 पूर्ण,
	अणु 251,   6 पूर्ण,
	अणु 255,   5 पूर्ण,
पूर्ण;

अटल पूर्णांक tda10048_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	u8 v;
	पूर्णांक i, ret = -EINVAL;

	dprपूर्णांकk(1, "%s()\n", __func__);

	v = tda10048_पढ़ोreg(state, TDA10048_NP_OUT);
	क्रम (i = 0; i < ARRAY_SIZE(snr_tab); i++) अणु
		अगर (v <= snr_tab[i].val) अणु
			*snr = snr_tab[i].data;
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक tda10048_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;

	dprपूर्णांकk(1, "%s()\n", __func__);

	*ucblocks = tda10048_पढ़ोreg(state, TDA10048_UNCOR_CPT_MSB) << 8 |
		tda10048_पढ़ोreg(state, TDA10048_UNCOR_CPT_LSB);
	/* clear the uncorrected TS packets counter when saturated */
	अगर (*ucblocks == 0xFFFF)
		tda10048_ग_लिखोreg(state, TDA10048_UNCOR_CTRL, 0x80);

	वापस 0;
पूर्ण

अटल पूर्णांक tda10048_get_frontend(काष्ठा dvb_frontend *fe,
				 काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;

	dprपूर्णांकk(1, "%s()\n", __func__);

	p->inversion = tda10048_पढ़ोreg(state, TDA10048_CONF_C1_1)
		& 0x20 ? INVERSION_ON : INVERSION_OFF;

	वापस tda10048_get_tps(state, p);
पूर्ण

अटल पूर्णांक tda10048_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल व्योम tda10048_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	dprपूर्णांकk(1, "%s()\n", __func__);
	kमुक्त(state);
पूर्ण

अटल व्योम tda10048_establish_शेषs(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा tda10048_state *state = fe->demodulator_priv;
	काष्ठा tda10048_config *config = &state->config;

	/* Validate/शेष the config */
	अगर (config->dtv6_अगर_freq_khz == 0) अणु
		config->dtv6_अगर_freq_khz = TDA10048_IF_4300;
		prपूर्णांकk(KERN_WARNING "%s() tda10048_config.dtv6_if_freq_khz is not set (defaulting to %d)\n",
			__func__,
			config->dtv6_अगर_freq_khz);
	पूर्ण

	अगर (config->dtv7_अगर_freq_khz == 0) अणु
		config->dtv7_अगर_freq_khz = TDA10048_IF_4300;
		prपूर्णांकk(KERN_WARNING "%s() tda10048_config.dtv7_if_freq_khz is not set (defaulting to %d)\n",
			__func__,
			config->dtv7_अगर_freq_khz);
	पूर्ण

	अगर (config->dtv8_अगर_freq_khz == 0) अणु
		config->dtv8_अगर_freq_khz = TDA10048_IF_4300;
		prपूर्णांकk(KERN_WARNING "%s() tda10048_config.dtv8_if_freq_khz is not set (defaulting to %d)\n",
			__func__,
			config->dtv8_अगर_freq_khz);
	पूर्ण

	अगर (config->clk_freq_khz == 0) अणु
		config->clk_freq_khz = TDA10048_CLK_16000;
		prपूर्णांकk(KERN_WARNING "%s() tda10048_config.clk_freq_khz is not set (defaulting to %d)\n",
			__func__,
			config->clk_freq_khz);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops tda10048_ops;

काष्ठा dvb_frontend *tda10048_attach(स्थिर काष्ठा tda10048_config *config,
	काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा tda10048_state *state = शून्य;

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा tda10048_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state and clone the config */
	स_नकल(&state->config, config, माप(*config));
	state->i2c = i2c;
	state->fwloaded = config->no_firmware;
	state->bandwidth = 8000000;

	/* check अगर the demod is present */
	अगर (tda10048_पढ़ोreg(state, TDA10048_IDENTITY) != 0x048)
		जाओ error;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &tda10048_ops,
		माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	/* set pll */
	अगर (config->set_pll) अणु
		state->pll_mfactor = config->pll_m;
		state->pll_nfactor = config->pll_n;
		state->pll_pfactor = config->pll_p;
	पूर्ण अन्यथा अणु
		state->pll_mfactor = 10;
		state->pll_nfactor = 3;
		state->pll_pfactor = 0;
	पूर्ण

	/* Establish any शेषs the the user didn't pass */
	tda10048_establish_शेषs(&state->frontend);

	/* Set the xtal and freq शेषs */
	अगर (tda10048_set_अगर(&state->frontend, 8000000) != 0)
		जाओ error;

	/* Default bandwidth */
	अगर (tda10048_set_bandwidth(&state->frontend, 8000000) != 0)
		जाओ error;

	/* Leave the gate बंदd */
	tda10048_i2c_gate_ctrl(&state->frontend, 0);

	वापस &state->frontend;

error:
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(tda10048_attach);

अटल स्थिर काष्ठा dvb_frontend_ops tda10048_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "NXP TDA10048HN DVB-T",
		.frequency_min_hz	= 177 * MHz,
		.frequency_max_hz	= 858 * MHz,
		.frequency_stepsize_hz	= 166666,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
		FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
		FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 | FE_CAN_QAM_AUTO |
		FE_CAN_HIERARCHY_AUTO | FE_CAN_GUARD_INTERVAL_AUTO |
		FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_RECOVER
	पूर्ण,

	.release = tda10048_release,
	.init = tda10048_init,
	.i2c_gate_ctrl = tda10048_i2c_gate_ctrl,
	.set_frontend = tda10048_set_frontend,
	.get_frontend = tda10048_get_frontend,
	.get_tune_settings = tda10048_get_tune_settings,
	.पढ़ो_status = tda10048_पढ़ो_status,
	.पढ़ो_ber = tda10048_पढ़ो_ber,
	.पढ़ो_संकेत_strength = tda10048_पढ़ो_संकेत_strength,
	.पढ़ो_snr = tda10048_पढ़ो_snr,
	.पढ़ो_ucblocks = tda10048_पढ़ो_ucblocks,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Enable verbose debug messages");

MODULE_DESCRIPTION("NXP TDA10048HN DVB-T Demodulator driver");
MODULE_AUTHOR("Steven Toth");
MODULE_LICENSE("GPL");
