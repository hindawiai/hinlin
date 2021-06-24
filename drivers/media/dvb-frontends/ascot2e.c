<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ascot2e.c
 *
 * Sony Ascot3E DVB-T/T2/C/C2 tuner driver
 *
 * Copyright 2012 Sony Corporation
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
  */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/types.h>
#समावेश "ascot2e.h"
#समावेश <media/dvb_frontend.h>

#घोषणा MAX_WRITE_REGSIZE 10

क्रमागत ascot2e_state अणु
	STATE_UNKNOWN,
	STATE_SLEEP,
	STATE_ACTIVE
पूर्ण;

काष्ठा ascot2e_priv अणु
	u32			frequency;
	u8			i2c_address;
	काष्ठा i2c_adapter	*i2c;
	क्रमागत ascot2e_state	state;
	व्योम			*set_tuner_data;
	पूर्णांक			(*set_tuner)(व्योम *, पूर्णांक);
पूर्ण;

क्रमागत ascot2e_tv_प्रणाली_t अणु
	ASCOT2E_DTV_DVBT_5,
	ASCOT2E_DTV_DVBT_6,
	ASCOT2E_DTV_DVBT_7,
	ASCOT2E_DTV_DVBT_8,
	ASCOT2E_DTV_DVBT2_1_7,
	ASCOT2E_DTV_DVBT2_5,
	ASCOT2E_DTV_DVBT2_6,
	ASCOT2E_DTV_DVBT2_7,
	ASCOT2E_DTV_DVBT2_8,
	ASCOT2E_DTV_DVBC_6,
	ASCOT2E_DTV_DVBC_8,
	ASCOT2E_DTV_DVBC2_6,
	ASCOT2E_DTV_DVBC2_8,
	ASCOT2E_DTV_UNKNOWN
पूर्ण;

काष्ठा ascot2e_band_sett अणु
	u8	अगर_out_sel;
	u8	agc_sel;
	u8	mix_oll;
	u8	rf_gain;
	u8	अगर_bpf_gc;
	u8	fअगर_offset;
	u8	bw_offset;
	u8	bw;
	u8	rf_oldet;
	u8	अगर_bpf_f0;
पूर्ण;

#घोषणा ASCOT2E_AUTO		0xff
#घोषणा ASCOT2E_OFFSET(ofs)	((u8)(ofs) & 0x1F)
#घोषणा ASCOT2E_BW_6		0x00
#घोषणा ASCOT2E_BW_7		0x01
#घोषणा ASCOT2E_BW_8		0x02
#घोषणा ASCOT2E_BW_1_7		0x03

अटल काष्ठा ascot2e_band_sett ascot2e_sett[] = अणु
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x06,
	  ASCOT2E_OFFSET(-8), ASCOT2E_OFFSET(-6), ASCOT2E_BW_6,  0x0B, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x06,
	  ASCOT2E_OFFSET(-8), ASCOT2E_OFFSET(-6), ASCOT2E_BW_6,  0x0B, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x06,
	  ASCOT2E_OFFSET(-6), ASCOT2E_OFFSET(-4), ASCOT2E_BW_7,  0x0B, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x06,
	  ASCOT2E_OFFSET(-4), ASCOT2E_OFFSET(-2), ASCOT2E_BW_8,  0x0B, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x06,
	ASCOT2E_OFFSET(-10), ASCOT2E_OFFSET(-16), ASCOT2E_BW_1_7, 0x0B, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x06,
	  ASCOT2E_OFFSET(-8), ASCOT2E_OFFSET(-6), ASCOT2E_BW_6,  0x0B, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x06,
	  ASCOT2E_OFFSET(-8), ASCOT2E_OFFSET(-6), ASCOT2E_BW_6,  0x0B, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x06,
	  ASCOT2E_OFFSET(-6), ASCOT2E_OFFSET(-4), ASCOT2E_BW_7,  0x0B, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x06,
	  ASCOT2E_OFFSET(-4), ASCOT2E_OFFSET(-2), ASCOT2E_BW_8,  0x0B, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x02, ASCOT2E_AUTO, 0x03,
	  ASCOT2E_OFFSET(-6), ASCOT2E_OFFSET(-8), ASCOT2E_BW_6,  0x09, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x02, ASCOT2E_AUTO, 0x03,
	  ASCOT2E_OFFSET(-2), ASCOT2E_OFFSET(-1), ASCOT2E_BW_8,  0x09, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x01,
	  ASCOT2E_OFFSET(-6), ASCOT2E_OFFSET(-4), ASCOT2E_BW_6,  0x09, 0x00 पूर्ण,
	अणु ASCOT2E_AUTO, ASCOT2E_AUTO, 0x03, ASCOT2E_AUTO, 0x01,
	  ASCOT2E_OFFSET(-2), ASCOT2E_OFFSET(2),  ASCOT2E_BW_8,  0x09, 0x00 पूर्ण
पूर्ण;

अटल व्योम ascot2e_i2c_debug(काष्ठा ascot2e_priv *priv,
			      u8 reg, u8 ग_लिखो, स्थिर u8 *data, u32 len)
अणु
	dev_dbg(&priv->i2c->dev, "ascot2e: I2C %s reg 0x%02x size %d\n",
		(ग_लिखो == 0 ? "read" : "write"), reg, len);
	prपूर्णांक_hex_dump_bytes("ascot2e: I2C data: ",
		DUMP_PREFIX_OFFSET, data, len);
पूर्ण

अटल पूर्णांक ascot2e_ग_लिखो_regs(काष्ठा ascot2e_priv *priv,
			      u8 reg, स्थिर u8 *data, u32 len)
अणु
	पूर्णांक ret;
	u8 buf[MAX_WRITE_REGSIZE + 1];
	काष्ठा i2c_msg msg[1] = अणु
		अणु
			.addr = priv->i2c_address,
			.flags = 0,
			.len = len + 1,
			.buf = buf,
		पूर्ण
	पूर्ण;

	अगर (len + 1 > माप(buf)) अणु
		dev_warn(&priv->i2c->dev,"wr reg=%04x: len=%d is too big!\n",
			 reg, len + 1);
		वापस -E2BIG;
	पूर्ण

	ascot2e_i2c_debug(priv, reg, 1, data, len);
	buf[0] = reg;
	स_नकल(&buf[1], data, len);
	ret = i2c_transfer(priv->i2c, msg, 1);
	अगर (ret >= 0 && ret != 1)
		ret = -EREMOTEIO;
	अगर (ret < 0) अणु
		dev_warn(&priv->i2c->dev,
			"%s: i2c wr failed=%d reg=%02x len=%d\n",
			KBUILD_MODNAME, ret, reg, len);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ascot2e_ग_लिखो_reg(काष्ठा ascot2e_priv *priv, u8 reg, u8 val)
अणु
	u8 पंचांगp = val; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	वापस ascot2e_ग_लिखो_regs(priv, reg, &पंचांगp, 1);
पूर्ण

अटल पूर्णांक ascot2e_पढ़ो_regs(काष्ठा ascot2e_priv *priv,
			     u8 reg, u8 *val, u32 len)
अणु
	पूर्णांक ret;
	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = priv->i2c_address,
			.flags = 0,
			.len = 1,
			.buf = &reg,
		पूर्ण, अणु
			.addr = priv->i2c_address,
			.flags = I2C_M_RD,
			.len = len,
			.buf = val,
		पूर्ण
	पूर्ण;

	ret = i2c_transfer(priv->i2c, &msg[0], 1);
	अगर (ret >= 0 && ret != 1)
		ret = -EREMOTEIO;
	अगर (ret < 0) अणु
		dev_warn(&priv->i2c->dev,
			"%s: I2C rw failed=%d addr=%02x reg=%02x\n",
			KBUILD_MODNAME, ret, priv->i2c_address, reg);
		वापस ret;
	पूर्ण
	ret = i2c_transfer(priv->i2c, &msg[1], 1);
	अगर (ret >= 0 && ret != 1)
		ret = -EREMOTEIO;
	अगर (ret < 0) अणु
		dev_warn(&priv->i2c->dev,
			"%s: i2c rd failed=%d addr=%02x reg=%02x\n",
			KBUILD_MODNAME, ret, priv->i2c_address, reg);
		वापस ret;
	पूर्ण
	ascot2e_i2c_debug(priv, reg, 0, val, len);
	वापस 0;
पूर्ण

अटल पूर्णांक ascot2e_पढ़ो_reg(काष्ठा ascot2e_priv *priv, u8 reg, u8 *val)
अणु
	वापस ascot2e_पढ़ो_regs(priv, reg, val, 1);
पूर्ण

अटल पूर्णांक ascot2e_set_reg_bits(काष्ठा ascot2e_priv *priv,
				u8 reg, u8 data, u8 mask)
अणु
	पूर्णांक res;
	u8 rdata;

	अगर (mask != 0xff) अणु
		res = ascot2e_पढ़ो_reg(priv, reg, &rdata);
		अगर (res != 0)
			वापस res;
		data = ((data & mask) | (rdata & (mask ^ 0xFF)));
	पूर्ण
	वापस ascot2e_ग_लिखो_reg(priv, reg, data);
पूर्ण

अटल पूर्णांक ascot2e_enter_घातer_save(काष्ठा ascot2e_priv *priv)
अणु
	u8 data[2];

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state == STATE_SLEEP)
		वापस 0;
	data[0] = 0x00;
	data[1] = 0x04;
	ascot2e_ग_लिखो_regs(priv, 0x14, data, 2);
	ascot2e_ग_लिखो_reg(priv, 0x50, 0x01);
	priv->state = STATE_SLEEP;
	वापस 0;
पूर्ण

अटल पूर्णांक ascot2e_leave_घातer_save(काष्ठा ascot2e_priv *priv)
अणु
	u8 data[2] = अणु 0xFB, 0x0F पूर्ण;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state == STATE_ACTIVE)
		वापस 0;
	ascot2e_ग_लिखो_regs(priv, 0x14, data, 2);
	ascot2e_ग_लिखो_reg(priv, 0x50, 0x00);
	priv->state = STATE_ACTIVE;
	वापस 0;
पूर्ण

अटल पूर्णांक ascot2e_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ascot2e_priv *priv = fe->tuner_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	वापस ascot2e_leave_घातer_save(priv);
पूर्ण

अटल व्योम ascot2e_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ascot2e_priv *priv = fe->tuner_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक ascot2e_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा ascot2e_priv *priv = fe->tuner_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	ascot2e_enter_घातer_save(priv);
	वापस 0;
पूर्ण

अटल क्रमागत ascot2e_tv_प्रणाली_t ascot2e_get_tv_प्रणाली(काष्ठा dvb_frontend *fe)
अणु
	क्रमागत ascot2e_tv_प्रणाली_t प्रणाली = ASCOT2E_DTV_UNKNOWN;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ascot2e_priv *priv = fe->tuner_priv;

	अगर (p->delivery_प्रणाली == SYS_DVBT) अणु
		अगर (p->bandwidth_hz <= 5000000)
			प्रणाली = ASCOT2E_DTV_DVBT_5;
		अन्यथा अगर (p->bandwidth_hz <= 6000000)
			प्रणाली = ASCOT2E_DTV_DVBT_6;
		अन्यथा अगर (p->bandwidth_hz <= 7000000)
			प्रणाली = ASCOT2E_DTV_DVBT_7;
		अन्यथा अगर (p->bandwidth_hz <= 8000000)
			प्रणाली = ASCOT2E_DTV_DVBT_8;
		अन्यथा अणु
			प्रणाली = ASCOT2E_DTV_DVBT_8;
			p->bandwidth_hz = 8000000;
		पूर्ण
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_DVBT2) अणु
		अगर (p->bandwidth_hz <= 5000000)
			प्रणाली = ASCOT2E_DTV_DVBT2_5;
		अन्यथा अगर (p->bandwidth_hz <= 6000000)
			प्रणाली = ASCOT2E_DTV_DVBT2_6;
		अन्यथा अगर (p->bandwidth_hz <= 7000000)
			प्रणाली = ASCOT2E_DTV_DVBT2_7;
		अन्यथा अगर (p->bandwidth_hz <= 8000000)
			प्रणाली = ASCOT2E_DTV_DVBT2_8;
		अन्यथा अणु
			प्रणाली = ASCOT2E_DTV_DVBT2_8;
			p->bandwidth_hz = 8000000;
		पूर्ण
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_DVBC_ANNEX_A) अणु
		अगर (p->bandwidth_hz <= 6000000)
			प्रणाली = ASCOT2E_DTV_DVBC_6;
		अन्यथा अगर (p->bandwidth_hz <= 8000000)
			प्रणाली = ASCOT2E_DTV_DVBC_8;
	पूर्ण
	dev_dbg(&priv->i2c->dev,
		"%s(): ASCOT2E DTV system %d (delsys %d, bandwidth %d)\n",
		__func__, (पूर्णांक)प्रणाली, p->delivery_प्रणाली, p->bandwidth_hz);
	वापस प्रणाली;
पूर्ण

अटल पूर्णांक ascot2e_set_params(काष्ठा dvb_frontend *fe)
अणु
	u8 data[10];
	u32 frequency;
	क्रमागत ascot2e_tv_प्रणाली_t tv_प्रणाली;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा ascot2e_priv *priv = fe->tuner_priv;

	dev_dbg(&priv->i2c->dev, "%s(): tune frequency %dkHz\n",
		__func__, p->frequency / 1000);
	tv_प्रणाली = ascot2e_get_tv_प्रणाली(fe);

	अगर (tv_प्रणाली == ASCOT2E_DTV_UNKNOWN) अणु
		dev_dbg(&priv->i2c->dev, "%s(): unknown DTV system\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	अगर (priv->set_tuner)
		priv->set_tuner(priv->set_tuner_data, 1);
	frequency = roundup(p->frequency / 1000, 25);
	अगर (priv->state == STATE_SLEEP)
		ascot2e_leave_घातer_save(priv);

	/* IF_OUT_SEL / AGC_SEL setting */
	data[0] = 0x00;
	अगर (ascot2e_sett[tv_प्रणाली].agc_sel != ASCOT2E_AUTO) अणु
		/* AGC pin setting from parameter table */
		data[0] |= (u8)(
			(ascot2e_sett[tv_प्रणाली].agc_sel & 0x03) << 3);
	पूर्ण
	अगर (ascot2e_sett[tv_प्रणाली].अगर_out_sel != ASCOT2E_AUTO) अणु
		/* IFOUT pin setting from parameter table */
		data[0] |= (u8)(
			(ascot2e_sett[tv_प्रणाली].अगर_out_sel & 0x01) << 2);
	पूर्ण
	/* Set bit[4:2] only */
	ascot2e_set_reg_bits(priv, 0x05, data[0], 0x1c);
	/* 0x06 - 0x0F */
	/* REF_R setting (0x06) */
	अगर (tv_प्रणाली == ASCOT2E_DTV_DVBC_6 ||
			tv_प्रणाली == ASCOT2E_DTV_DVBC_8) अणु
		/* xtal, xtal*2 */
		data[0] = (frequency > 500000) ? 16 : 32;
	पूर्ण अन्यथा अणु
		/* xtal/8, xtal/4 */
		data[0] = (frequency > 500000) ? 2 : 4;
	पूर्ण
	/* XOSC_SEL=100uA */
	data[1] = 0x04;
	/* KBW setting (0x08), KC0 setting (0x09), KC1 setting (0x0A) */
	अगर (tv_प्रणाली == ASCOT2E_DTV_DVBC_6 ||
			tv_प्रणाली == ASCOT2E_DTV_DVBC_8) अणु
		data[2] = 18;
		data[3] = 120;
		data[4] = 20;
	पूर्ण अन्यथा अणु
		data[2] = 48;
		data[3] = 10;
		data[4] = 30;
	पूर्ण
	/* ORDER/R2_RANGE/R2_BANK/C2_BANK setting (0x0B) */
	अगर (tv_प्रणाली == ASCOT2E_DTV_DVBC_6 ||
			tv_प्रणाली == ASCOT2E_DTV_DVBC_8)
		data[5] = (frequency > 500000) ? 0x08 : 0x0c;
	अन्यथा
		data[5] = (frequency > 500000) ? 0x30 : 0x38;
	/* Set MIX_OLL (0x0C) value from parameter table */
	data[6] = ascot2e_sett[tv_प्रणाली].mix_oll;
	/* Set RF_GAIN (0x0D) setting from parameter table */
	अगर (ascot2e_sett[tv_प्रणाली].rf_gain == ASCOT2E_AUTO) अणु
		/* RF_GAIN स्वतः control enable */
		ascot2e_ग_लिखो_reg(priv, 0x4E, 0x01);
		/* RF_GAIN Default value */
		data[7] = 0x00;
	पूर्ण अन्यथा अणु
		/* RF_GAIN स्वतः control disable */
		ascot2e_ग_लिखो_reg(priv, 0x4E, 0x00);
		data[7] = ascot2e_sett[tv_प्रणाली].rf_gain;
	पूर्ण
	/* Set IF_BPF_GC/FIF_OFFSET (0x0E) value from parameter table */
	data[8] = (u8)((ascot2e_sett[tv_प्रणाली].fअगर_offset << 3) |
		(ascot2e_sett[tv_प्रणाली].अगर_bpf_gc & 0x07));
	/* Set BW_OFFSET (0x0F) value from parameter table */
	data[9] = ascot2e_sett[tv_प्रणाली].bw_offset;
	ascot2e_ग_लिखो_regs(priv, 0x06, data, 10);
	/*
	 * 0x45 - 0x47
	 * LNA optimization setting
	 * RF_LNA_DIST1-5, RF_LNA_CM
	 */
	अगर (tv_प्रणाली == ASCOT2E_DTV_DVBC_6 ||
			tv_प्रणाली == ASCOT2E_DTV_DVBC_8) अणु
		data[0] = 0x0F;
		data[1] = 0x00;
		data[2] = 0x01;
	पूर्ण अन्यथा अणु
		data[0] = 0x0F;
		data[1] = 0x00;
		data[2] = 0x03;
	पूर्ण
	ascot2e_ग_लिखो_regs(priv, 0x45, data, 3);
	/* 0x49 - 0x4A
	 Set RF_OLDET_ENX/RF_OLDET_OLL value from parameter table */
	data[0] = ascot2e_sett[tv_प्रणाली].rf_oldet;
	/* Set IF_BPF_F0 value from parameter table */
	data[1] = ascot2e_sett[tv_प्रणाली].अगर_bpf_f0;
	ascot2e_ग_लिखो_regs(priv, 0x49, data, 2);
	/*
	 * Tune now
	 * RFAGC fast mode / RFAGC स्वतः control enable
	 * (set bit[7], bit[5:4] only)
	 * vco_cal = 1, set MIX_OL_CPU_EN
	 */
	ascot2e_set_reg_bits(priv, 0x0c, 0x90, 0xb0);
	/* Logic wake up, CPU wake up */
	data[0] = 0xc4;
	data[1] = 0x40;
	ascot2e_ग_लिखो_regs(priv, 0x03, data, 2);
	/* 0x10 - 0x14 */
	data[0] = (u8)(frequency & 0xFF);         /* 0x10: FRF_L */
	data[1] = (u8)((frequency >> 8) & 0xFF);  /* 0x11: FRF_M */
	data[2] = (u8)((frequency >> 16) & 0x0F); /* 0x12: FRF_H (bit[3:0]) */
	/* 0x12: BW (bit[5:4]) */
	data[2] |= (u8)(ascot2e_sett[tv_प्रणाली].bw << 4);
	data[3] = 0xFF; /* 0x13: VCO calibration enable */
	data[4] = 0xFF; /* 0x14: Analog block enable */
	/* Tune (Burst ग_लिखो) */
	ascot2e_ग_लिखो_regs(priv, 0x10, data, 5);
	msleep(50);
	/* CPU deep sleep */
	ascot2e_ग_लिखो_reg(priv, 0x04, 0x00);
	/* Logic sleep */
	ascot2e_ग_लिखो_reg(priv, 0x03, 0xC0);
	/* RFAGC normal mode (set bit[5:4] only) */
	ascot2e_set_reg_bits(priv, 0x0C, 0x00, 0x30);
	priv->frequency = frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक ascot2e_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा ascot2e_priv *priv = fe->tuner_priv;

	*frequency = priv->frequency * 1000;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops ascot2e_tuner_ops = अणु
	.info = अणु
		.name = "Sony ASCOT2E",
		.frequency_min_hz  =    1 * MHz,
		.frequency_max_hz  = 1200 * MHz,
		.frequency_step_hz =   25 * kHz,
	पूर्ण,
	.init = ascot2e_init,
	.release = ascot2e_release,
	.sleep = ascot2e_sleep,
	.set_params = ascot2e_set_params,
	.get_frequency = ascot2e_get_frequency,
पूर्ण;

काष्ठा dvb_frontend *ascot2e_attach(काष्ठा dvb_frontend *fe,
				    स्थिर काष्ठा ascot2e_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	u8 data[4];
	काष्ठा ascot2e_priv *priv = शून्य;

	priv = kzalloc(माप(काष्ठा ascot2e_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;
	priv->i2c_address = (config->i2c_address >> 1);
	priv->i2c = i2c;
	priv->set_tuner_data = config->set_tuner_priv;
	priv->set_tuner = config->set_tuner_callback;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* 16 MHz xTal frequency */
	data[0] = 16;
	/* VCO current setting */
	data[1] = 0x06;
	/* Logic wake up, CPU boot */
	data[2] = 0xC4;
	data[3] = 0x40;
	ascot2e_ग_लिखो_regs(priv, 0x01, data, 4);
	/* RFVGA optimization setting (RF_DIST0 - RF_DIST2) */
	data[0] = 0x10;
	data[1] = 0x3F;
	data[2] = 0x25;
	ascot2e_ग_लिखो_regs(priv, 0x22, data, 3);
	/* PLL mode setting */
	ascot2e_ग_लिखो_reg(priv, 0x28, 0x1e);
	/* RSSI setting */
	ascot2e_ग_लिखो_reg(priv, 0x59, 0x04);
	/* TODO check CPU HW error state here */
	msleep(80);
	/* Xtal oscillator current control setting */
	ascot2e_ग_लिखो_reg(priv, 0x4c, 0x01);
	/* XOSC_SEL=100uA */
	ascot2e_ग_लिखो_reg(priv, 0x07, 0x04);
	/* CPU deep sleep */
	ascot2e_ग_लिखो_reg(priv, 0x04, 0x00);
	/* Logic sleep */
	ascot2e_ग_लिखो_reg(priv, 0x03, 0xc0);
	/* Power save setting */
	data[0] = 0x00;
	data[1] = 0x04;
	ascot2e_ग_लिखो_regs(priv, 0x14, data, 2);
	ascot2e_ग_लिखो_reg(priv, 0x50, 0x01);
	priv->state = STATE_SLEEP;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	स_नकल(&fe->ops.tuner_ops, &ascot2e_tuner_ops,
				माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = priv;
	dev_info(&priv->i2c->dev,
		"Sony ASCOT2E attached on addr=%x at I2C adapter %p\n",
		priv->i2c_address, priv->i2c);
	वापस fe;
पूर्ण
EXPORT_SYMBOL(ascot2e_attach);

MODULE_DESCRIPTION("Sony ASCOT2E terr/cab tuner driver");
MODULE_AUTHOR("info@netup.ru");
MODULE_LICENSE("GPL");
