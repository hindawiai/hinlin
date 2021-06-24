<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * bsbe1.h - ALPS BSBE1 tuner support
 *
 * the project's page is at https://linuxtv.org
 */

#अगर_अघोषित BSBE1_H
#घोषणा BSBE1_H

अटल u8 alps_bsbe1_inittab[] = अणु
	0x01, 0x15,   /* XTAL = 4MHz, VCO = 352 MHz */
	0x02, 0x30,   /* MCLK = 88 MHz */
	0x03, 0x00,   /* ACR output 0 */
	0x04, 0x7d,   /* F22FR = 0x7d, F22 = f_VCO / 128 / 0x7d = 22 kHz */
	0x05, 0x05,   /* I2CT = 0, SCLT = 1, SDAT = 1 */
	0x06, 0x00,   /* DAC output 0 */
	0x08, 0x40,   /* DiSEqC off, LNB घातer on OP2/LOCK pin on */
	0x09, 0x00,   /* FIFO */
	0x0c, 0x51,   /* OP1/OP0 normal, val = 1 (LNB घातer on) */
	0x0d, 0x82,   /* DC offset compensation = on, beta_agc1 = 2 */
	0x0f, 0x92,   /* AGC1R */
	0x10, 0x34,   /* AGC2O */
	0x11, 0x84,   /* TLSR */
	0x12, 0xb9,   /* CFD */
	0x15, 0xc9,   /* lock detector threshold */
	0x28, 0x00,   /* out imp: normal, type: parallel, FEC mode: QPSK */
	0x33, 0xfc,   /* RS control */
	0x34, 0x93,   /* count viterbi bit errors per 2E18 bytes */
	0xff, 0xff
पूर्ण;


अटल पूर्णांक alps_bsbe1_set_symbol_rate(काष्ठा dvb_frontend* fe, u32 srate, u32 ratio)
अणु
	u8 aclk = 0;
	u8 bclk = 0;

	अगर (srate < 1500000) अणु aclk = 0xb7; bclk = 0x47; पूर्ण
	अन्यथा अगर (srate < 3000000) अणु aclk = 0xb7; bclk = 0x4b; पूर्ण
	अन्यथा अगर (srate < 7000000) अणु aclk = 0xb7; bclk = 0x4f; पूर्ण
	अन्यथा अगर (srate < 14000000) अणु aclk = 0xb7; bclk = 0x53; पूर्ण
	अन्यथा अगर (srate < 30000000) अणु aclk = 0xb6; bclk = 0x53; पूर्ण
	अन्यथा अगर (srate < 45000000) अणु aclk = 0xb4; bclk = 0x51; पूर्ण

	stv0299_ग_लिखोreg(fe, 0x13, aclk);
	stv0299_ग_लिखोreg(fe, 0x14, bclk);
	stv0299_ग_लिखोreg(fe, 0x1f, (ratio >> 16) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x20, (ratio >>  8) & 0xff);
	stv0299_ग_लिखोreg(fe, 0x21, (ratio      ) & 0xf0);

	वापस 0;
पूर्ण

अटल पूर्णांक alps_bsbe1_tuner_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	पूर्णांक ret;
	u8 data[4];
	u32 भाग;
	काष्ठा i2c_msg msg = अणु .addr = 0x61, .flags = 0, .buf = data, .len = माप(data) पूर्ण;
	काष्ठा i2c_adapter *i2c = fe->tuner_priv;

	अगर ((p->frequency < 950000) || (p->frequency > 2150000))
		वापस -EINVAL;

	भाग = p->frequency / 1000;
	data[0] = (भाग >> 8) & 0x7f;
	data[1] = भाग & 0xff;
	data[2] = 0x80 | ((भाग & 0x18000) >> 10) | 0x1;
	data[3] = 0xe0;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	ret = i2c_transfer(i2c, &msg, 1);
	वापस (ret != 1) ? -EIO : 0;
पूर्ण

अटल काष्ठा stv0299_config alps_bsbe1_config = अणु
	.demod_address = 0x68,
	.inittab = alps_bsbe1_inittab,
	.mclk = 88000000UL,
	.invert = 1,
	.skip_reinit = 0,
	.min_delay_ms = 100,
	.set_symbol_rate = alps_bsbe1_set_symbol_rate,
पूर्ण;

#पूर्ण_अगर
