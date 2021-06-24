<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Realtek RTL2832 DVB-T demodulator driver
 *
 * Copyright (C) 2012 Thomas Mair <thomas.mair86@gmail.com>
 * Copyright (C) 2012-2014 Antti Palosaari <crope@iki.fi>
 */

#समावेश "rtl2832_priv.h"

#घोषणा REG_MASK(b) (BIT(b + 1) - 1)

अटल स्थिर काष्ठा rtl2832_reg_entry रेजिस्टरs[] = अणु
	[DVBT_SOFT_RST]		= अणु0x101,  2, 2पूर्ण,
	[DVBT_IIC_REPEAT]	= अणु0x101,  3, 3पूर्ण,
	[DVBT_TR_WAIT_MIN_8K]	= अणु0x188, 11, 2पूर्ण,
	[DVBT_RSD_BER_FAIL_VAL]	= अणु0x18f, 15, 0पूर्ण,
	[DVBT_EN_BK_TRK]	= अणु0x1a6,  7, 7पूर्ण,
	[DVBT_AD_EN_REG]	= अणु0x008,  7, 7पूर्ण,
	[DVBT_AD_EN_REG1]	= अणु0x008,  6, 6पूर्ण,
	[DVBT_EN_BBIN]		= अणु0x1b1,  0, 0पूर्ण,
	[DVBT_MGD_THD0]		= अणु0x195,  7, 0पूर्ण,
	[DVBT_MGD_THD1]		= अणु0x196,  7, 0पूर्ण,
	[DVBT_MGD_THD2]		= अणु0x197,  7, 0पूर्ण,
	[DVBT_MGD_THD3]		= अणु0x198,  7, 0पूर्ण,
	[DVBT_MGD_THD4]		= अणु0x199,  7, 0पूर्ण,
	[DVBT_MGD_THD5]		= अणु0x19a,  7, 0पूर्ण,
	[DVBT_MGD_THD6]		= अणु0x19b,  7, 0पूर्ण,
	[DVBT_MGD_THD7]		= अणु0x19c,  7, 0पूर्ण,
	[DVBT_EN_CACQ_NOTCH]	= अणु0x161,  4, 4पूर्ण,
	[DVBT_AD_AV_REF]	= अणु0x009,  6, 0पूर्ण,
	[DVBT_REG_PI]		= अणु0x00a,  2, 0पूर्ण,
	[DVBT_PIP_ON]		= अणु0x021,  3, 3पूर्ण,
	[DVBT_SCALE1_B92]	= अणु0x292,  7, 0पूर्ण,
	[DVBT_SCALE1_B93]	= अणु0x293,  7, 0पूर्ण,
	[DVBT_SCALE1_BA7]	= अणु0x2a7,  7, 0पूर्ण,
	[DVBT_SCALE1_BA9]	= अणु0x2a9,  7, 0पूर्ण,
	[DVBT_SCALE1_BAA]	= अणु0x2aa,  7, 0पूर्ण,
	[DVBT_SCALE1_BAB]	= अणु0x2ab,  7, 0पूर्ण,
	[DVBT_SCALE1_BAC]	= अणु0x2ac,  7, 0पूर्ण,
	[DVBT_SCALE1_BB0]	= अणु0x2b0,  7, 0पूर्ण,
	[DVBT_SCALE1_BB1]	= अणु0x2b1,  7, 0पूर्ण,
	[DVBT_KB_P1]		= अणु0x164,  3, 1पूर्ण,
	[DVBT_KB_P2]		= अणु0x164,  6, 4पूर्ण,
	[DVBT_KB_P3]		= अणु0x165,  2, 0पूर्ण,
	[DVBT_OPT_ADC_IQ]	= अणु0x006,  5, 4पूर्ण,
	[DVBT_AD_AVI]		= अणु0x009,  1, 0पूर्ण,
	[DVBT_AD_AVQ]		= अणु0x009,  3, 2पूर्ण,
	[DVBT_K1_CR_STEP12]	= अणु0x2ad,  9, 4पूर्ण,
	[DVBT_TRK_KS_P2]	= अणु0x16f,  2, 0पूर्ण,
	[DVBT_TRK_KS_I2]	= अणु0x170,  5, 3पूर्ण,
	[DVBT_TR_THD_SET2]	= अणु0x172,  3, 0पूर्ण,
	[DVBT_TRK_KC_P2]	= अणु0x173,  5, 3पूर्ण,
	[DVBT_TRK_KC_I2]	= अणु0x175,  2, 0पूर्ण,
	[DVBT_CR_THD_SET2]	= अणु0x176,  7, 6पूर्ण,
	[DVBT_PSET_IFFREQ]	= अणु0x119, 21, 0पूर्ण,
	[DVBT_SPEC_INV]		= अणु0x115,  0, 0पूर्ण,
	[DVBT_RSAMP_RATIO]	= अणु0x19f, 27, 2पूर्ण,
	[DVBT_CFREQ_OFF_RATIO]	= अणु0x19d, 23, 4पूर्ण,
	[DVBT_FSM_STAGE]	= अणु0x351,  6, 3पूर्ण,
	[DVBT_RX_CONSTEL]	= अणु0x33c,  3, 2पूर्ण,
	[DVBT_RX_HIER]		= अणु0x33c,  6, 4पूर्ण,
	[DVBT_RX_C_RATE_LP]	= अणु0x33d,  2, 0पूर्ण,
	[DVBT_RX_C_RATE_HP]	= अणु0x33d,  5, 3पूर्ण,
	[DVBT_GI_IDX]		= अणु0x351,  1, 0पूर्ण,
	[DVBT_FFT_MODE_IDX]	= अणु0x351,  2, 2पूर्ण,
	[DVBT_RSD_BER_EST]	= अणु0x34e, 15, 0पूर्ण,
	[DVBT_CE_EST_EVM]	= अणु0x40c, 15, 0पूर्ण,
	[DVBT_RF_AGC_VAL]	= अणु0x35b, 13, 0पूर्ण,
	[DVBT_IF_AGC_VAL]	= अणु0x359, 13, 0पूर्ण,
	[DVBT_DAGC_VAL]		= अणु0x305,  7, 0पूर्ण,
	[DVBT_SFREQ_OFF]	= अणु0x318, 13, 0पूर्ण,
	[DVBT_CFREQ_OFF]	= अणु0x35f, 17, 0पूर्ण,
	[DVBT_POLAR_RF_AGC]	= अणु0x00e,  1, 1पूर्ण,
	[DVBT_POLAR_IF_AGC]	= अणु0x00e,  0, 0पूर्ण,
	[DVBT_AAGC_HOLD]	= अणु0x104,  5, 5पूर्ण,
	[DVBT_EN_RF_AGC]	= अणु0x104,  6, 6पूर्ण,
	[DVBT_EN_IF_AGC]	= अणु0x104,  7, 7पूर्ण,
	[DVBT_IF_AGC_MIN]	= अणु0x108,  7, 0पूर्ण,
	[DVBT_IF_AGC_MAX]	= अणु0x109,  7, 0पूर्ण,
	[DVBT_RF_AGC_MIN]	= अणु0x10a,  7, 0पूर्ण,
	[DVBT_RF_AGC_MAX]	= अणु0x10b,  7, 0पूर्ण,
	[DVBT_IF_AGC_MAN]	= अणु0x10c,  6, 6पूर्ण,
	[DVBT_IF_AGC_MAN_VAL]	= अणु0x10c, 13, 0पूर्ण,
	[DVBT_RF_AGC_MAN]	= अणु0x10e,  6, 6पूर्ण,
	[DVBT_RF_AGC_MAN_VAL]	= अणु0x10e, 13, 0पूर्ण,
	[DVBT_DAGC_TRG_VAL]	= अणु0x112,  7, 0पूर्ण,
	[DVBT_AGC_TARG_VAL_0]	= अणु0x102,  0, 0पूर्ण,
	[DVBT_AGC_TARG_VAL_8_1]	= अणु0x103,  7, 0पूर्ण,
	[DVBT_AAGC_LOOP_GAIN]	= अणु0x1c7,  5, 1पूर्ण,
	[DVBT_LOOP_GAIN2_3_0]	= अणु0x104,  4, 1पूर्ण,
	[DVBT_LOOP_GAIN2_4]	= अणु0x105,  7, 7पूर्ण,
	[DVBT_LOOP_GAIN3]	= अणु0x1c8,  4, 0पूर्ण,
	[DVBT_VTOP1]		= अणु0x106,  5, 0पूर्ण,
	[DVBT_VTOP2]		= अणु0x1c9,  5, 0पूर्ण,
	[DVBT_VTOP3]		= अणु0x1ca,  5, 0पूर्ण,
	[DVBT_KRF1]		= अणु0x1cb,  7, 0पूर्ण,
	[DVBT_KRF2]		= अणु0x107,  7, 0पूर्ण,
	[DVBT_KRF3]		= अणु0x1cd,  7, 0पूर्ण,
	[DVBT_KRF4]		= अणु0x1ce,  7, 0पूर्ण,
	[DVBT_EN_GI_PGA]	= अणु0x1e5,  0, 0पूर्ण,
	[DVBT_THD_LOCK_UP]	= अणु0x1d9,  8, 0पूर्ण,
	[DVBT_THD_LOCK_DW]	= अणु0x1db,  8, 0पूर्ण,
	[DVBT_THD_UP1]		= अणु0x1dd,  7, 0पूर्ण,
	[DVBT_THD_DW1]		= अणु0x1de,  7, 0पूर्ण,
	[DVBT_INTER_CNT_LEN]	= अणु0x1d8,  3, 0पूर्ण,
	[DVBT_GI_PGA_STATE]	= अणु0x1e6,  3, 3पूर्ण,
	[DVBT_EN_AGC_PGA]	= अणु0x1d7,  0, 0पूर्ण,
	[DVBT_CKOUTPAR]		= अणु0x17b,  5, 5पूर्ण,
	[DVBT_CKOUT_PWR]	= अणु0x17b,  6, 6पूर्ण,
	[DVBT_SYNC_DUR]		= अणु0x17b,  7, 7पूर्ण,
	[DVBT_ERR_DUR]		= अणु0x17c,  0, 0पूर्ण,
	[DVBT_SYNC_LVL]		= अणु0x17c,  1, 1पूर्ण,
	[DVBT_ERR_LVL]		= अणु0x17c,  2, 2पूर्ण,
	[DVBT_VAL_LVL]		= अणु0x17c,  3, 3पूर्ण,
	[DVBT_SERIAL]		= अणु0x17c,  4, 4पूर्ण,
	[DVBT_SER_LSB]		= अणु0x17c,  5, 5पूर्ण,
	[DVBT_CDIV_PH0]		= अणु0x17d,  3, 0पूर्ण,
	[DVBT_CDIV_PH1]		= अणु0x17d,  7, 4पूर्ण,
	[DVBT_MPEG_IO_OPT_2_2]	= अणु0x006,  7, 7पूर्ण,
	[DVBT_MPEG_IO_OPT_1_0]	= अणु0x007,  7, 6पूर्ण,
	[DVBT_CKOUTPAR_PIP]	= अणु0x0b7,  4, 4पूर्ण,
	[DVBT_CKOUT_PWR_PIP]	= अणु0x0b7,  3, 3पूर्ण,
	[DVBT_SYNC_LVL_PIP]	= अणु0x0b7,  2, 2पूर्ण,
	[DVBT_ERR_LVL_PIP]	= अणु0x0b7,  1, 1पूर्ण,
	[DVBT_VAL_LVL_PIP]	= अणु0x0b7,  0, 0पूर्ण,
	[DVBT_CKOUTPAR_PID]	= अणु0x0b9,  4, 4पूर्ण,
	[DVBT_CKOUT_PWR_PID]	= अणु0x0b9,  3, 3पूर्ण,
	[DVBT_SYNC_LVL_PID]	= अणु0x0b9,  2, 2पूर्ण,
	[DVBT_ERR_LVL_PID]	= अणु0x0b9,  1, 1पूर्ण,
	[DVBT_VAL_LVL_PID]	= अणु0x0b9,  0, 0पूर्ण,
	[DVBT_SM_PASS]		= अणु0x193, 11, 0पूर्ण,
	[DVBT_AD7_SETTING]	= अणु0x011, 15, 0पूर्ण,
	[DVBT_RSSI_R]		= अणु0x301,  6, 0पूर्ण,
	[DVBT_ACI_DET_IND]	= अणु0x312,  0, 0पूर्ण,
	[DVBT_REG_MON]		= अणु0x00d,  1, 0पूर्ण,
	[DVBT_REG_MONSEL]	= अणु0x00d,  2, 2पूर्ण,
	[DVBT_REG_GPE]		= अणु0x00d,  7, 7पूर्ण,
	[DVBT_REG_GPO]		= अणु0x010,  0, 0पूर्ण,
	[DVBT_REG_4MSEL]	= अणु0x013,  0, 0पूर्ण,
पूर्ण;

अटल पूर्णांक rtl2832_rd_demod_reg(काष्ठा rtl2832_dev *dev, पूर्णांक reg, u32 *val)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret, i;
	u16 reg_start_addr;
	u8 msb, lsb, पढ़ोing[4], len;
	u32 पढ़ोing_पंचांगp, mask;

	reg_start_addr = रेजिस्टरs[reg].start_address;
	msb = रेजिस्टरs[reg].msb;
	lsb = रेजिस्टरs[reg].lsb;
	len = (msb >> 3) + 1;
	mask = REG_MASK(msb - lsb);

	ret = regmap_bulk_पढ़ो(dev->regmap, reg_start_addr, पढ़ोing, len);
	अगर (ret)
		जाओ err;

	पढ़ोing_पंचांगp = 0;
	क्रम (i = 0; i < len; i++)
		पढ़ोing_पंचांगp |= पढ़ोing[i] << ((len - 1 - i) * 8);

	*val = (पढ़ोing_पंचांगp >> lsb) & mask;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_wr_demod_reg(काष्ठा rtl2832_dev *dev, पूर्णांक reg, u32 val)
अणु
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret, i;
	u16 reg_start_addr;
	u8 msb, lsb, पढ़ोing[4], writing[4], len;
	u32 पढ़ोing_पंचांगp, writing_पंचांगp, mask;

	reg_start_addr = रेजिस्टरs[reg].start_address;
	msb = रेजिस्टरs[reg].msb;
	lsb = रेजिस्टरs[reg].lsb;
	len = (msb >> 3) + 1;
	mask = REG_MASK(msb - lsb);

	ret = regmap_bulk_पढ़ो(dev->regmap, reg_start_addr, पढ़ोing, len);
	अगर (ret)
		जाओ err;

	पढ़ोing_पंचांगp = 0;
	क्रम (i = 0; i < len; i++)
		पढ़ोing_पंचांगp |= पढ़ोing[i] << ((len - 1 - i) * 8);

	writing_पंचांगp = पढ़ोing_पंचांगp & ~(mask << lsb);
	writing_पंचांगp |= ((val & mask) << lsb);

	क्रम (i = 0; i < len; i++)
		writing[i] = (writing_पंचांगp >> ((len - 1 - i) * 8)) & 0xff;

	ret = regmap_bulk_ग_लिखो(dev->regmap, reg_start_addr, writing, len);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_set_अगर(काष्ठा dvb_frontend *fe, u32 अगर_freq)
अणु
	काष्ठा rtl2832_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u64 pset_अगरfreq;
	u8 en_bbin = (अगर_freq == 0 ? 0x1 : 0x0);

	/*
	* PSET_IFFREQ = - न्यूनमान((IfFreqHz % CrystalFreqHz) * घात(2, 22)
	*		/ CrystalFreqHz)
	*/
	pset_अगरfreq = अगर_freq % dev->pdata->clk;
	pset_अगरfreq *= 0x400000;
	pset_अगरfreq = भाग_u64(pset_अगरfreq, dev->pdata->clk);
	pset_अगरfreq = -pset_अगरfreq;
	pset_अगरfreq = pset_अगरfreq & 0x3fffff;
	dev_dbg(&client->dev, "if_frequency=%d pset_iffreq=%08x\n",
		अगर_freq, (अचिन्हित)pset_अगरfreq);

	ret = rtl2832_wr_demod_reg(dev, DVBT_EN_BBIN, en_bbin);
	अगर (ret)
		जाओ err;

	ret = rtl2832_wr_demod_reg(dev, DVBT_PSET_IFFREQ, pset_अगरfreq);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा rtl2832_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &dev->fe.dtv_property_cache;
	स्थिर काष्ठा rtl2832_reg_value *init;
	पूर्णांक i, ret, len;
	/* initialization values क्रम the demodulator रेजिस्टरs */
	काष्ठा rtl2832_reg_value rtl2832_initial_regs[] = अणु
		अणुDVBT_AD_EN_REG,		0x1पूर्ण,
		अणुDVBT_AD_EN_REG1,		0x1पूर्ण,
		अणुDVBT_RSD_BER_FAIL_VAL,		0x2800पूर्ण,
		अणुDVBT_MGD_THD0,			0x10पूर्ण,
		अणुDVBT_MGD_THD1,			0x20पूर्ण,
		अणुDVBT_MGD_THD2,			0x20पूर्ण,
		अणुDVBT_MGD_THD3,			0x40पूर्ण,
		अणुDVBT_MGD_THD4,			0x22पूर्ण,
		अणुDVBT_MGD_THD5,			0x32पूर्ण,
		अणुDVBT_MGD_THD6,			0x37पूर्ण,
		अणुDVBT_MGD_THD7,			0x39पूर्ण,
		अणुDVBT_EN_BK_TRK,		0x0पूर्ण,
		अणुDVBT_EN_CACQ_NOTCH,		0x0पूर्ण,
		अणुDVBT_AD_AV_REF,		0x2aपूर्ण,
		अणुDVBT_REG_PI,			0x6पूर्ण,
		अणुDVBT_PIP_ON,			0x0पूर्ण,
		अणुDVBT_CDIV_PH0,			0x8पूर्ण,
		अणुDVBT_CDIV_PH1,			0x8पूर्ण,
		अणुDVBT_SCALE1_B92,		0x4पूर्ण,
		अणुDVBT_SCALE1_B93,		0xb0पूर्ण,
		अणुDVBT_SCALE1_BA7,		0x78पूर्ण,
		अणुDVBT_SCALE1_BA9,		0x28पूर्ण,
		अणुDVBT_SCALE1_BAA,		0x59पूर्ण,
		अणुDVBT_SCALE1_BAB,		0x83पूर्ण,
		अणुDVBT_SCALE1_BAC,		0xd4पूर्ण,
		अणुDVBT_SCALE1_BB0,		0x65पूर्ण,
		अणुDVBT_SCALE1_BB1,		0x43पूर्ण,
		अणुDVBT_KB_P1,			0x1पूर्ण,
		अणुDVBT_KB_P2,			0x4पूर्ण,
		अणुDVBT_KB_P3,			0x7पूर्ण,
		अणुDVBT_K1_CR_STEP12,		0xaपूर्ण,
		अणुDVBT_REG_GPE,			0x1पूर्ण,
		अणुDVBT_SERIAL,			0x0पूर्ण,
		अणुDVBT_CDIV_PH0,			0x9पूर्ण,
		अणुDVBT_CDIV_PH1,			0x9पूर्ण,
		अणुDVBT_MPEG_IO_OPT_2_2,		0x0पूर्ण,
		अणुDVBT_MPEG_IO_OPT_1_0,		0x0पूर्ण,
		अणुDVBT_TRK_KS_P2,		0x4पूर्ण,
		अणुDVBT_TRK_KS_I2,		0x7पूर्ण,
		अणुDVBT_TR_THD_SET2,		0x6पूर्ण,
		अणुDVBT_TRK_KC_I2,		0x5पूर्ण,
		अणुDVBT_CR_THD_SET2,		0x1पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	ret = rtl2832_wr_demod_reg(dev, DVBT_SOFT_RST, 0x0);
	अगर (ret)
		जाओ err;

	क्रम (i = 0; i < ARRAY_SIZE(rtl2832_initial_regs); i++) अणु
		ret = rtl2832_wr_demod_reg(dev, rtl2832_initial_regs[i].reg,
			rtl2832_initial_regs[i].value);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* load tuner specअगरic settings */
	dev_dbg(&client->dev, "load settings for tuner=%02x\n",
		dev->pdata->tuner);
	चयन (dev->pdata->tuner) अणु
	हाल RTL2832_TUNER_FC2580:
		len = ARRAY_SIZE(rtl2832_tuner_init_fc2580);
		init = rtl2832_tuner_init_fc2580;
		अवरोध;
	हाल RTL2832_TUNER_FC0012:
	हाल RTL2832_TUNER_FC0013:
		len = ARRAY_SIZE(rtl2832_tuner_init_fc0012);
		init = rtl2832_tuner_init_fc0012;
		अवरोध;
	हाल RTL2832_TUNER_TUA9001:
		len = ARRAY_SIZE(rtl2832_tuner_init_tua9001);
		init = rtl2832_tuner_init_tua9001;
		अवरोध;
	हाल RTL2832_TUNER_E4000:
		len = ARRAY_SIZE(rtl2832_tuner_init_e4000);
		init = rtl2832_tuner_init_e4000;
		अवरोध;
	हाल RTL2832_TUNER_R820T:
	हाल RTL2832_TUNER_R828D:
		len = ARRAY_SIZE(rtl2832_tuner_init_r820t);
		init = rtl2832_tuner_init_r820t;
		अवरोध;
	हाल RTL2832_TUNER_SI2157:
		len = ARRAY_SIZE(rtl2832_tuner_init_si2157);
		init = rtl2832_tuner_init_si2157;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	क्रम (i = 0; i < len; i++) अणु
		ret = rtl2832_wr_demod_reg(dev, init[i].reg, init[i].value);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* init stats here in order संकेत app which stats are supported */
	c->strength.len = 1;
	c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	dev->sleeping = false;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा rtl2832_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	dev_dbg(&client->dev, "\n");

	dev->sleeping = true;
	dev->fe_status = 0;

	ret = rtl2832_wr_demod_reg(dev, DVBT_SOFT_RST, 0x1);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_get_tune_settings(काष्ठा dvb_frontend *fe,
	काष्ठा dvb_frontend_tune_settings *s)
अणु
	काष्ठा rtl2832_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;

	dev_dbg(&client->dev, "\n");
	s->min_delay_ms = 1000;
	s->step_size = fe->ops.info.frequency_stepsize_hz * 2;
	s->max_drअगरt = (fe->ops.info.frequency_stepsize_hz * 2) + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा rtl2832_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret, i, j;
	u64 bw_mode, num, num2;
	u32 resamp_ratio, cfreq_off_ratio;
	अटल u8 bw_params[3][32] = अणु
	/* 6 MHz bandwidth */
		अणु
		0xf5, 0xff, 0x15, 0x38, 0x5d, 0x6d, 0x52, 0x07, 0xfa, 0x2f,
		0x53, 0xf5, 0x3f, 0xca, 0x0b, 0x91, 0xea, 0x30, 0x63, 0xb2,
		0x13, 0xda, 0x0b, 0xc4, 0x18, 0x7e, 0x16, 0x66, 0x08, 0x67,
		0x19, 0xe0,
		पूर्ण,

	/*  7 MHz bandwidth */
		अणु
		0xe7, 0xcc, 0xb5, 0xba, 0xe8, 0x2f, 0x67, 0x61, 0x00, 0xaf,
		0x86, 0xf2, 0xbf, 0x59, 0x04, 0x11, 0xb6, 0x33, 0xa4, 0x30,
		0x15, 0x10, 0x0a, 0x42, 0x18, 0xf8, 0x17, 0xd9, 0x07, 0x22,
		0x19, 0x10,
		पूर्ण,

	/*  8 MHz bandwidth */
		अणु
		0x09, 0xf6, 0xd2, 0xa7, 0x9a, 0xc9, 0x27, 0x77, 0x06, 0xbf,
		0xec, 0xf4, 0x4f, 0x0b, 0xfc, 0x01, 0x63, 0x35, 0x54, 0xa7,
		0x16, 0x66, 0x08, 0xb4, 0x19, 0x6e, 0x19, 0x65, 0x05, 0xc8,
		0x19, 0xe0,
		पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev, "frequency=%u bandwidth_hz=%u inversion=%u\n",
		c->frequency, c->bandwidth_hz, c->inversion);

	/* program tuner */
	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	/* If the frontend has get_अगर_frequency(), use it */
	अगर (fe->ops.tuner_ops.get_अगर_frequency) अणु
		u32 अगर_freq;

		ret = fe->ops.tuner_ops.get_अगर_frequency(fe, &अगर_freq);
		अगर (ret)
			जाओ err;

		ret = rtl2832_set_अगर(fe, अगर_freq);
		अगर (ret)
			जाओ err;
	पूर्ण

	चयन (c->bandwidth_hz) अणु
	हाल 6000000:
		i = 0;
		bw_mode = 48000000;
		अवरोध;
	हाल 7000000:
		i = 1;
		bw_mode = 56000000;
		अवरोध;
	हाल 8000000:
		i = 2;
		bw_mode = 64000000;
		अवरोध;
	शेष:
		dev_err(&client->dev, "invalid bandwidth_hz %u\n",
			c->bandwidth_hz);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	क्रम (j = 0; j < माप(bw_params[0]); j++) अणु
		ret = regmap_bulk_ग_लिखो(dev->regmap,
					0x11c + j, &bw_params[i][j], 1);
		अगर (ret)
			जाओ err;
	पूर्ण

	/* calculate and set resample ratio
	* RSAMP_RATIO = न्यूनमान(CrystalFreqHz * 7 * घात(2, 22)
	*	/ ConstWithBandwidthMode)
	*/
	num = dev->pdata->clk * 7ULL;
	num *= 0x400000;
	num = भाग_u64(num, bw_mode);
	resamp_ratio =  num & 0x3ffffff;
	ret = rtl2832_wr_demod_reg(dev, DVBT_RSAMP_RATIO, resamp_ratio);
	अगर (ret)
		जाओ err;

	/* calculate and set cfreq off ratio
	* CFREQ_OFF_RATIO = - न्यूनमान(ConstWithBandwidthMode * घात(2, 20)
	*	/ (CrystalFreqHz * 7))
	*/
	num = bw_mode << 20;
	num2 = dev->pdata->clk * 7ULL;
	num = भाग_u64(num, num2);
	num = -num;
	cfreq_off_ratio = num & 0xfffff;
	ret = rtl2832_wr_demod_reg(dev, DVBT_CFREQ_OFF_RATIO, cfreq_off_ratio);
	अगर (ret)
		जाओ err;

	/* soft reset */
	ret = rtl2832_wr_demod_reg(dev, DVBT_SOFT_RST, 0x1);
	अगर (ret)
		जाओ err;

	ret = rtl2832_wr_demod_reg(dev, DVBT_SOFT_RST, 0x0);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_get_frontend(काष्ठा dvb_frontend *fe,
				काष्ठा dtv_frontend_properties *c)
अणु
	काष्ठा rtl2832_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 buf[3];

	अगर (dev->sleeping)
		वापस 0;

	ret = regmap_bulk_पढ़ो(dev->regmap, 0x33c, buf, 2);
	अगर (ret)
		जाओ err;

	ret = regmap_bulk_पढ़ो(dev->regmap, 0x351, &buf[2], 1);
	अगर (ret)
		जाओ err;

	dev_dbg(&client->dev, "TPS=%*ph\n", 3, buf);

	चयन ((buf[0] >> 2) & 3) अणु
	हाल 0:
		c->modulation = QPSK;
		अवरोध;
	हाल 1:
		c->modulation = QAM_16;
		अवरोध;
	हाल 2:
		c->modulation = QAM_64;
		अवरोध;
	पूर्ण

	चयन ((buf[2] >> 2) & 1) अणु
	हाल 0:
		c->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
	हाल 1:
		c->transmission_mode = TRANSMISSION_MODE_8K;
	पूर्ण

	चयन ((buf[2] >> 0) & 3) अणु
	हाल 0:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_32;
		अवरोध;
	हाल 1:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_16;
		अवरोध;
	हाल 2:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_8;
		अवरोध;
	हाल 3:
		c->guard_पूर्णांकerval = GUARD_INTERVAL_1_4;
		अवरोध;
	पूर्ण

	चयन ((buf[0] >> 4) & 7) अणु
	हाल 0:
		c->hierarchy = HIERARCHY_NONE;
		अवरोध;
	हाल 1:
		c->hierarchy = HIERARCHY_1;
		अवरोध;
	हाल 2:
		c->hierarchy = HIERARCHY_2;
		अवरोध;
	हाल 3:
		c->hierarchy = HIERARCHY_4;
		अवरोध;
	पूर्ण

	चयन ((buf[1] >> 3) & 7) अणु
	हाल 0:
		c->code_rate_HP = FEC_1_2;
		अवरोध;
	हाल 1:
		c->code_rate_HP = FEC_2_3;
		अवरोध;
	हाल 2:
		c->code_rate_HP = FEC_3_4;
		अवरोध;
	हाल 3:
		c->code_rate_HP = FEC_5_6;
		अवरोध;
	हाल 4:
		c->code_rate_HP = FEC_7_8;
		अवरोध;
	पूर्ण

	चयन ((buf[1] >> 0) & 7) अणु
	हाल 0:
		c->code_rate_LP = FEC_1_2;
		अवरोध;
	हाल 1:
		c->code_rate_LP = FEC_2_3;
		अवरोध;
	हाल 2:
		c->code_rate_LP = FEC_3_4;
		अवरोध;
	हाल 3:
		c->code_rate_LP = FEC_5_6;
		अवरोध;
	हाल 4:
		c->code_rate_LP = FEC_7_8;
		अवरोध;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा rtl2832_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक ret;
	u32 पंचांगp;
	u8 u8पंचांगp, buf[2];
	u16 u16पंचांगp;

	dev_dbg(&client->dev, "\n");

	*status = 0;
	अगर (dev->sleeping)
		वापस 0;

	ret = rtl2832_rd_demod_reg(dev, DVBT_FSM_STAGE, &पंचांगp);
	अगर (ret)
		जाओ err;

	अगर (पंचांगp == 11) अणु
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
	पूर्ण अन्यथा अगर (पंचांगp == 10) अणु
		*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER |
				FE_HAS_VITERBI;
	पूर्ण

	dev->fe_status = *status;

	/* संकेत strength */
	अगर (dev->fe_status & FE_HAS_SIGNAL) अणु
		/* पढ़ो digital AGC */
		ret = regmap_bulk_पढ़ो(dev->regmap, 0x305, &u8पंचांगp, 1);
		अगर (ret)
			जाओ err;

		dev_dbg(&client->dev, "digital agc=%02x", u8पंचांगp);

		u8पंचांगp = ~u8पंचांगp;
		u16पंचांगp = u8पंचांगp << 8 | u8पंचांगp << 0;

		c->strength.stat[0].scale = FE_SCALE_RELATIVE;
		c->strength.stat[0].uvalue = u16पंचांगp;
	पूर्ण अन्यथा अणु
		c->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* CNR */
	अगर (dev->fe_status & FE_HAS_VITERBI) अणु
		अचिन्हित hierarchy, स्थिरellation;
		#घोषणा CONSTELLATION_NUM 3
		#घोषणा HIERARCHY_NUM 4
		अटल स्थिर u32 स्थिरant[CONSTELLATION_NUM][HIERARCHY_NUM] = अणु
			अणु85387325, 85387325, 85387325, 85387325पूर्ण,
			अणु86676178, 86676178, 87167949, 87795660पूर्ण,
			अणु87659938, 87659938, 87885178, 88241743पूर्ण,
		पूर्ण;

		ret = regmap_bulk_पढ़ो(dev->regmap, 0x33c, &u8पंचांगp, 1);
		अगर (ret)
			जाओ err;

		स्थिरellation = (u8पंचांगp >> 2) & 0x03; /* [3:2] */
		ret = -EINVAL;
		अगर (स्थिरellation > CONSTELLATION_NUM - 1)
			जाओ err;

		hierarchy = (u8पंचांगp >> 4) & 0x07; /* [6:4] */
		अगर (hierarchy > HIERARCHY_NUM - 1)
			जाओ err;

		ret = regmap_bulk_पढ़ो(dev->regmap, 0x40c, buf, 2);
		अगर (ret)
			जाओ err;

		u16पंचांगp = buf[0] << 8 | buf[1] << 0;
		अगर (u16पंचांगp)
			पंचांगp = (स्थिरant[स्थिरellation][hierarchy] -
			       पूर्णांकlog10(u16पंचांगp)) / ((1 << 24) / 10000);
		अन्यथा
			पंचांगp = 0;

		dev_dbg(&client->dev, "cnr raw=%u\n", u16पंचांगp);

		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = पंचांगp;
	पूर्ण अन्यथा अणु
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	/* BER */
	अगर (dev->fe_status & FE_HAS_LOCK) अणु
		ret = regmap_bulk_पढ़ो(dev->regmap, 0x34e, buf, 2);
		अगर (ret)
			जाओ err;

		u16पंचांगp = buf[0] << 8 | buf[1] << 0;
		dev->post_bit_error += u16पंचांगp;
		dev->post_bit_count += 1000000;

		dev_dbg(&client->dev, "ber errors=%u total=1000000\n", u16पंचांगp);

		c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_error.stat[0].uvalue = dev->post_bit_error;
		c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
		c->post_bit_count.stat[0].uvalue = dev->post_bit_count;
	पूर्ण अन्यथा अणु
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	/* report SNR in resolution of 0.1 dB */
	अगर (c->cnr.stat[0].scale == FE_SCALE_DECIBEL)
		*snr = भाग_s64(c->cnr.stat[0].svalue, 100);
	अन्यथा
		*snr = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक rtl2832_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा rtl2832_dev *dev = fe->demodulator_priv;

	*ber = (dev->post_bit_error - dev->post_bit_error_prev);
	dev->post_bit_error_prev = dev->post_bit_error;

	वापस 0;
पूर्ण

/*
 * I2C gate/mux/repeater logic
 * There is delay mechanism to aव्योम unneeded I2C gate खोलो / बंद. Gate बंद
 * is delayed here a little bit in order to see अगर there is sequence of I2C
 * messages sent to same I2C bus.
 */
अटल व्योम rtl2832_i2c_gate_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl2832_dev *dev = container_of(work, काष्ठा rtl2832_dev, i2c_gate_work.work);
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	/* बंद gate */
	ret = regmap_update_bits(dev->regmap, 0x101, 0x08, 0x00);
	अगर (ret)
		जाओ err;

	वापस;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
पूर्ण

अटल पूर्णांक rtl2832_select(काष्ठा i2c_mux_core *muxc, u32 chan_id)
अणु
	काष्ठा rtl2832_dev *dev = i2c_mux_priv(muxc);
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;

	/* terminate possible gate closing */
	cancel_delayed_work(&dev->i2c_gate_work);

	/* खोलो gate */
	ret = regmap_update_bits(dev->regmap, 0x101, 0x08, 0x08);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_deselect(काष्ठा i2c_mux_core *muxc, u32 chan_id)
अणु
	काष्ठा rtl2832_dev *dev = i2c_mux_priv(muxc);

	schedule_delayed_work(&dev->i2c_gate_work, usecs_to_jअगरfies(100));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops rtl2832_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name = "Realtek RTL2832 (DVB-T)",
		.frequency_min_hz	= 174 * MHz,
		.frequency_max_hz	= 862 * MHz,
		.frequency_stepsize_hz	= 166667,
		.caps = FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO |
			FE_CAN_RECOVER |
			FE_CAN_MUTE_TS
	 पूर्ण,

	.init = rtl2832_init,
	.sleep = rtl2832_sleep,

	.get_tune_settings = rtl2832_get_tune_settings,

	.set_frontend = rtl2832_set_frontend,
	.get_frontend = rtl2832_get_frontend,

	.पढ़ो_status = rtl2832_पढ़ो_status,
	.पढ़ो_snr = rtl2832_पढ़ो_snr,
	.पढ़ो_ber = rtl2832_पढ़ो_ber,
पूर्ण;

अटल bool rtl2832_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x305:
	हाल 0x33c:
	हाल 0x34e:
	हाल 0x351:
	हाल 0x40c ... 0x40d:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा dvb_frontend *rtl2832_get_dvb_frontend(काष्ठा i2c_client *client)
अणु
	काष्ठा rtl2832_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");
	वापस &dev->fe;
पूर्ण

अटल काष्ठा i2c_adapter *rtl2832_get_i2c_adapter(काष्ठा i2c_client *client)
अणु
	काष्ठा rtl2832_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");
	वापस dev->muxc->adapter[0];
पूर्ण

अटल पूर्णांक rtl2832_slave_ts_ctrl(काष्ठा i2c_client *client, bool enable)
अणु
	काष्ठा rtl2832_dev *dev = i2c_get_clientdata(client);
	पूर्णांक ret;

	dev_dbg(&client->dev, "enable=%d\n", enable);

	अगर (enable) अणु
		ret = rtl2832_wr_demod_reg(dev, DVBT_SOFT_RST, 0x0);
		अगर (ret)
			जाओ err;
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x10c, "\x5f\xff", 2);
		अगर (ret)
			जाओ err;
		ret = rtl2832_wr_demod_reg(dev, DVBT_PIP_ON, 0x1);
		अगर (ret)
			जाओ err;
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x0bc, "\x18", 1);
		अगर (ret)
			जाओ err;
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x192, "\x7f\xf7\xff", 3);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अणु
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x192, "\x00\x0f\xff", 3);
		अगर (ret)
			जाओ err;
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x0bc, "\x08", 1);
		अगर (ret)
			जाओ err;
		ret = rtl2832_wr_demod_reg(dev, DVBT_PIP_ON, 0x0);
		अगर (ret)
			जाओ err;
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x10c, "\x00\x00", 2);
		अगर (ret)
			जाओ err;
		ret = rtl2832_wr_demod_reg(dev, DVBT_SOFT_RST, 0x1);
		अगर (ret)
			जाओ err;
	पूर्ण

	dev->slave_ts = enable;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_pid_filter_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा rtl2832_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 u8पंचांगp;

	dev_dbg(&client->dev, "onoff=%d, slave_ts=%d\n", onoff, dev->slave_ts);

	/* enable / disable PID filter */
	अगर (onoff)
		u8पंचांगp = 0x80;
	अन्यथा
		u8पंचांगp = 0x00;

	अगर (dev->slave_ts)
		ret = regmap_update_bits(dev->regmap, 0x021, 0xc0, u8पंचांगp);
	अन्यथा
		ret = regmap_update_bits(dev->regmap, 0x061, 0xc0, u8पंचांगp);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_pid_filter(काष्ठा dvb_frontend *fe, u8 index, u16 pid,
			      पूर्णांक onoff)
अणु
	काष्ठा rtl2832_dev *dev = fe->demodulator_priv;
	काष्ठा i2c_client *client = dev->client;
	पूर्णांक ret;
	u8 buf[4];

	dev_dbg(&client->dev, "index=%d pid=%04x onoff=%d slave_ts=%d\n",
		index, pid, onoff, dev->slave_ts);

	/* skip invalid PIDs (0x2000) */
	अगर (pid > 0x1fff || index > 32)
		वापस 0;

	अगर (onoff)
		set_bit(index, &dev->filters);
	अन्यथा
		clear_bit(index, &dev->filters);

	/* enable / disable PIDs */
	buf[0] = (dev->filters >>  0) & 0xff;
	buf[1] = (dev->filters >>  8) & 0xff;
	buf[2] = (dev->filters >> 16) & 0xff;
	buf[3] = (dev->filters >> 24) & 0xff;

	अगर (dev->slave_ts)
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x022, buf, 4);
	अन्यथा
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x062, buf, 4);
	अगर (ret)
		जाओ err;

	/* add PID */
	buf[0] = (pid >> 8) & 0xff;
	buf[1] = (pid >> 0) & 0xff;

	अगर (dev->slave_ts)
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x026 + 2 * index, buf, 2);
	अन्यथा
		ret = regmap_bulk_ग_लिखो(dev->regmap, 0x066 + 2 * index, buf, 2);
	अगर (ret)
		जाओ err;

	वापस 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rtl2832_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा i2c_adapter *i2c = client->adapter;
	काष्ठा rtl2832_dev *dev;
	पूर्णांक ret;
	u8 पंचांगp;
	अटल स्थिर काष्ठा regmap_range_cfg regmap_range_cfg[] = अणु
		अणु
			.selector_reg     = 0x00,
			.selector_mask    = 0xff,
			.selector_shअगरt   = 0,
			.winकरोw_start     = 0,
			.winकरोw_len       = 0x100,
			.range_min        = 0 * 0x100,
			.range_max        = 5 * 0x100,
		पूर्ण,
	पूर्ण;

	dev_dbg(&client->dev, "\n");

	/* allocate memory क्रम the पूर्णांकernal state */
	dev = kzalloc(माप(काष्ठा rtl2832_dev), GFP_KERNEL);
	अगर (dev == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	/* setup the state */
	i2c_set_clientdata(client, dev);
	dev->client = client;
	dev->pdata = client->dev.platक्रमm_data;
	dev->sleeping = true;
	INIT_DELAYED_WORK(&dev->i2c_gate_work, rtl2832_i2c_gate_work);
	/* create regmap */
	dev->regmap_config.reg_bits =  8;
	dev->regmap_config.val_bits =  8;
	dev->regmap_config.अस्थिर_reg = rtl2832_अस्थिर_reg;
	dev->regmap_config.max_रेजिस्टर = 5 * 0x100;
	dev->regmap_config.ranges = regmap_range_cfg;
	dev->regmap_config.num_ranges = ARRAY_SIZE(regmap_range_cfg);
	dev->regmap_config.cache_type = REGCACHE_NONE;
	dev->regmap = regmap_init_i2c(client, &dev->regmap_config);
	अगर (IS_ERR(dev->regmap)) अणु
		ret = PTR_ERR(dev->regmap);
		जाओ err_kमुक्त;
	पूर्ण

	/* check अगर the demod is there */
	ret = regmap_bulk_पढ़ो(dev->regmap, 0x000, &पंचांगp, 1);
	अगर (ret)
		जाओ err_regmap_निकास;

	/* create muxed i2c adapter क्रम demod tuner bus */
	dev->muxc = i2c_mux_alloc(i2c, &i2c->dev, 1, 0, I2C_MUX_LOCKED,
				  rtl2832_select, rtl2832_deselect);
	अगर (!dev->muxc) अणु
		ret = -ENOMEM;
		जाओ err_regmap_निकास;
	पूर्ण
	dev->muxc->priv = dev;
	ret = i2c_mux_add_adapter(dev->muxc, 0, 0, 0);
	अगर (ret)
		जाओ err_regmap_निकास;

	/* create dvb_frontend */
	स_नकल(&dev->fe.ops, &rtl2832_ops, माप(काष्ठा dvb_frontend_ops));
	dev->fe.demodulator_priv = dev;

	/* setup callbacks */
	pdata->get_dvb_frontend = rtl2832_get_dvb_frontend;
	pdata->get_i2c_adapter = rtl2832_get_i2c_adapter;
	pdata->slave_ts_ctrl = rtl2832_slave_ts_ctrl;
	pdata->pid_filter = rtl2832_pid_filter;
	pdata->pid_filter_ctrl = rtl2832_pid_filter_ctrl;
	pdata->regmap = dev->regmap;

	dev_info(&client->dev, "Realtek RTL2832 successfully attached\n");
	वापस 0;
err_regmap_निकास:
	regmap_निकास(dev->regmap);
err_kमुक्त:
	kमुक्त(dev);
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl2832_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा rtl2832_dev *dev = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	cancel_delayed_work_sync(&dev->i2c_gate_work);

	i2c_mux_del_adapters(dev->muxc);

	regmap_निकास(dev->regmap);

	kमुक्त(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rtl2832_id_table[] = अणु
	अणु"rtl2832", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rtl2832_id_table);

अटल काष्ठा i2c_driver rtl2832_driver = अणु
	.driver = अणु
		.name	= "rtl2832",
		.suppress_bind_attrs	= true,
	पूर्ण,
	.probe		= rtl2832_probe,
	.हटाओ		= rtl2832_हटाओ,
	.id_table	= rtl2832_id_table,
पूर्ण;

module_i2c_driver(rtl2832_driver);

MODULE_AUTHOR("Thomas Mair <mair.thomas86@gmail.com>");
MODULE_AUTHOR("Antti Palosaari <crope@iki.fi>");
MODULE_DESCRIPTION("Realtek RTL2832 DVB-T demodulator driver");
MODULE_LICENSE("GPL");
