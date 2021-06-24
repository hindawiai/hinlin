<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Integrant ITD1000 "Zero-IF Tuner IC for Direct Broadcast Satellite"
 *
 *  Copyright (c) 2007-8 Patrick Boettcher <pb@linuxtv.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/delay.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <media/dvb_frontend.h>

#समावेश "itd1000.h"
#समावेश "itd1000_priv.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

#घोषणा itd_dbg(args...)  करो अणु \
	अगर (debug) अणु \
		prपूर्णांकk(KERN_DEBUG   "ITD1000: " args);\
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा itd_warn(args...) करो अणु \
	prपूर्णांकk(KERN_WARNING "ITD1000: " args); \
पूर्ण जबतक (0)

#घोषणा itd_info(args...) करो अणु \
	prपूर्णांकk(KERN_INFO    "ITD1000: " args); \
पूर्ण जबतक (0)

/* करोn't ग_लिखो more than one byte with flexcop behind */
अटल पूर्णांक itd1000_ग_लिखो_regs(काष्ठा itd1000_state *state, u8 reg, u8 v[], u8 len)
अणु
	u8 buf[MAX_XFER_SIZE];
	काष्ठा i2c_msg msg = अणु
		.addr = state->cfg->i2c_address, .flags = 0, .buf = buf, .len = len+1
	पूर्ण;

	अगर (1 + len > माप(buf)) अणु
		prपूर्णांकk(KERN_WARNING
		       "itd1000: i2c wr reg=%04x: len=%d is too big!\n",
		       reg, len);
		वापस -EINVAL;
	पूर्ण

	buf[0] = reg;
	स_नकल(&buf[1], v, len);

	/* itd_dbg("wr %02x: %02x\n", reg, v[0]); */

	अगर (i2c_transfer(state->i2c, &msg, 1) != 1) अणु
		prपूर्णांकk(KERN_WARNING "itd1000 I2C write failed\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक itd1000_पढ़ो_reg(काष्ठा itd1000_state *state, u8 reg)
अणु
	u8 val;
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = state->cfg->i2c_address, .flags = 0,        .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = state->cfg->i2c_address, .flags = I2C_M_RD, .buf = &val, .len = 1 पूर्ण,
	पूर्ण;

	/* ugly flexcop workaround */
	itd1000_ग_लिखो_regs(state, (reg - 1) & 0xff, &state->shaकरोw[(reg - 1) & 0xff], 1);

	अगर (i2c_transfer(state->i2c, msg, 2) != 2) अणु
		itd_warn("itd1000 I2C read failed\n");
		वापस -EREMOTEIO;
	पूर्ण
	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक itd1000_ग_लिखो_reg(काष्ठा itd1000_state *state, u8 r, u8 v)
अणु
	u8 पंचांगp = v; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */
	पूर्णांक ret = itd1000_ग_लिखो_regs(state, r, &पंचांगp, 1);
	state->shaकरोw[r] = पंचांगp;
	वापस ret;
पूर्ण


अटल काष्ठा अणु
	u32 symbol_rate;
	u8  pgaext  : 4; /* PLLFH */
	u8  bbgvmin : 4; /* BBGVMIN */
पूर्ण itd1000_lpf_pga[] = अणु
	अणु        0, 0x8, 0x3 पूर्ण,
	अणु  5200000, 0x8, 0x3 पूर्ण,
	अणु 12200000, 0x4, 0x3 पूर्ण,
	अणु 15400000, 0x2, 0x3 पूर्ण,
	अणु 19800000, 0x2, 0x3 पूर्ण,
	अणु 21500000, 0x2, 0x3 पूर्ण,
	अणु 24500000, 0x2, 0x3 पूर्ण,
	अणु 28400000, 0x2, 0x3 पूर्ण,
	अणु 33400000, 0x2, 0x3 पूर्ण,
	अणु 34400000, 0x1, 0x4 पूर्ण,
	अणु 34400000, 0x1, 0x4 पूर्ण,
	अणु 38400000, 0x1, 0x4 पूर्ण,
	अणु 38400000, 0x1, 0x4 पूर्ण,
	अणु 40400000, 0x1, 0x4 पूर्ण,
	अणु 45400000, 0x1, 0x4 पूर्ण,
पूर्ण;

अटल व्योम itd1000_set_lpf_bw(काष्ठा itd1000_state *state, u32 symbol_rate)
अणु
	u8 i;
	u8 con1    = itd1000_पढ़ो_reg(state, CON1)    & 0xfd;
	u8 pllfh   = itd1000_पढ़ो_reg(state, PLLFH)   & 0x0f;
	u8 bbgvmin = itd1000_पढ़ो_reg(state, BBGVMIN) & 0xf0;
	u8 bw      = itd1000_पढ़ो_reg(state, BW)      & 0xf0;

	itd_dbg("symbol_rate = %d\n", symbol_rate);

	/* not sure what is that ? - starting to करोwnload the table */
	itd1000_ग_लिखो_reg(state, CON1, con1 | (1 << 1));

	क्रम (i = 0; i < ARRAY_SIZE(itd1000_lpf_pga); i++)
		अगर (symbol_rate < itd1000_lpf_pga[i].symbol_rate) अणु
			itd_dbg("symrate: index: %d pgaext: %x, bbgvmin: %x\n", i, itd1000_lpf_pga[i].pgaext, itd1000_lpf_pga[i].bbgvmin);
			itd1000_ग_लिखो_reg(state, PLLFH,   pllfh | (itd1000_lpf_pga[i].pgaext << 4));
			itd1000_ग_लिखो_reg(state, BBGVMIN, bbgvmin | (itd1000_lpf_pga[i].bbgvmin));
			itd1000_ग_लिखो_reg(state, BW,      bw | (i & 0x0f));
			अवरोध;
		पूर्ण

	itd1000_ग_लिखो_reg(state, CON1, con1 | (0 << 1));
पूर्ण

अटल काष्ठा अणु
	u8 vcorg;
	u32 fmax_rg;
पूर्ण itd1000_vcorg[] = अणु
	अणु  1,  920000 पूर्ण,
	अणु  2,  971000 पूर्ण,
	अणु  3, 1031000 पूर्ण,
	अणु  4, 1091000 पूर्ण,
	अणु  5, 1171000 पूर्ण,
	अणु  6, 1281000 पूर्ण,
	अणु  7, 1381000 पूर्ण,
	अणु  8,  500000 पूर्ण,	/* this is पूर्णांकentional. */
	अणु  9, 1451000 पूर्ण,
	अणु 10, 1531000 पूर्ण,
	अणु 11, 1631000 पूर्ण,
	अणु 12, 1741000 पूर्ण,
	अणु 13, 1891000 पूर्ण,
	अणु 14, 2071000 पूर्ण,
	अणु 15, 2250000 पूर्ण,
पूर्ण;

अटल व्योम itd1000_set_vco(काष्ठा itd1000_state *state, u32 freq_khz)
अणु
	u8 i;
	u8 gvbb_i2c     = itd1000_पढ़ो_reg(state, GVBB_I2C) & 0xbf;
	u8 vco_chp1_i2c = itd1000_पढ़ो_reg(state, VCO_CHP1_I2C) & 0x0f;
	u8 adcout;

	/* reserved bit again (reset ?) */
	itd1000_ग_लिखो_reg(state, GVBB_I2C, gvbb_i2c | (1 << 6));

	क्रम (i = 0; i < ARRAY_SIZE(itd1000_vcorg); i++) अणु
		अगर (freq_khz < itd1000_vcorg[i].fmax_rg) अणु
			itd1000_ग_लिखो_reg(state, VCO_CHP1_I2C, vco_chp1_i2c | (itd1000_vcorg[i].vcorg << 4));
			msleep(1);

			adcout = itd1000_पढ़ो_reg(state, PLLLOCK) & 0x0f;

			itd_dbg("VCO: %dkHz: %d -> ADCOUT: %d %02x\n", freq_khz, itd1000_vcorg[i].vcorg, adcout, vco_chp1_i2c);

			अगर (adcout > 13) अणु
				अगर (!(itd1000_vcorg[i].vcorg == 7 || itd1000_vcorg[i].vcorg == 15))
					itd1000_ग_लिखो_reg(state, VCO_CHP1_I2C, vco_chp1_i2c | ((itd1000_vcorg[i].vcorg + 1) << 4));
			पूर्ण अन्यथा अगर (adcout < 2) अणु
				अगर (!(itd1000_vcorg[i].vcorg == 1 || itd1000_vcorg[i].vcorg == 9))
					itd1000_ग_लिखो_reg(state, VCO_CHP1_I2C, vco_chp1_i2c | ((itd1000_vcorg[i].vcorg - 1) << 4));
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा अणु
	u32 freq;
	u8 values[10]; /* RFTR, RFST1 - RFST9 */
पूर्ण itd1000_fre_values[] = अणु
	अणु 1075000, अणु 0x59, 0x1d, 0x1c, 0x17, 0x16, 0x0f, 0x0e, 0x0c, 0x0b, 0x0a पूर्ण पूर्ण,
	अणु 1250000, अणु 0x89, 0x1e, 0x1d, 0x17, 0x15, 0x0f, 0x0e, 0x0c, 0x0b, 0x0a पूर्ण पूर्ण,
	अणु 1450000, अणु 0x89, 0x1e, 0x1d, 0x17, 0x15, 0x0f, 0x0e, 0x0c, 0x0b, 0x0a पूर्ण पूर्ण,
	अणु 1650000, अणु 0x69, 0x1e, 0x1d, 0x17, 0x15, 0x0f, 0x0e, 0x0c, 0x0b, 0x0a पूर्ण पूर्ण,
	अणु 1750000, अणु 0x69, 0x1e, 0x17, 0x15, 0x14, 0x0f, 0x0e, 0x0c, 0x0b, 0x0a पूर्ण पूर्ण,
	अणु 1850000, अणु 0x69, 0x1d, 0x17, 0x16, 0x14, 0x0f, 0x0e, 0x0d, 0x0b, 0x0a पूर्ण पूर्ण,
	अणु 1900000, अणु 0x69, 0x1d, 0x17, 0x15, 0x14, 0x0f, 0x0e, 0x0d, 0x0b, 0x0a पूर्ण पूर्ण,
	अणु 1950000, अणु 0x69, 0x1d, 0x17, 0x16, 0x14, 0x13, 0x0e, 0x0d, 0x0b, 0x0a पूर्ण पूर्ण,
	अणु 2050000, अणु 0x69, 0x1e, 0x1d, 0x17, 0x16, 0x14, 0x13, 0x0e, 0x0b, 0x0a पूर्ण पूर्ण,
	अणु 2150000, अणु 0x69, 0x1d, 0x1c, 0x17, 0x15, 0x14, 0x13, 0x0f, 0x0e, 0x0b पूर्ण पूर्ण
पूर्ण;


#घोषणा FREF 16

अटल व्योम itd1000_set_lo(काष्ठा itd1000_state *state, u32 freq_khz)
अणु
	पूर्णांक i, j;
	u32 plln, pllf;
	u64 पंचांगp;

	plln = (freq_khz * 1000) / 2 / FREF;

	/* Compute the factional part बार 1000 */
	पंचांगp  = plln % 1000000;
	plln /= 1000000;

	पंचांगp *= 1048576;
	करो_भाग(पंचांगp, 1000000);
	pllf = (u32) पंचांगp;

	state->frequency = ((plln * 1000) + (pllf * 1000)/1048576) * 2*FREF;
	itd_dbg("frequency: %dkHz (wanted) %dkHz (set), PLLF = %d, PLLN = %d\n", freq_khz, state->frequency, pllf, plln);

	itd1000_ग_लिखो_reg(state, PLLNH, 0x80); /* PLLNH */
	itd1000_ग_लिखो_reg(state, PLLNL, plln & 0xff);
	itd1000_ग_लिखो_reg(state, PLLFH, (itd1000_पढ़ो_reg(state, PLLFH) & 0xf0) | ((pllf >> 16) & 0x0f));
	itd1000_ग_लिखो_reg(state, PLLFM, (pllf >> 8) & 0xff);
	itd1000_ग_लिखो_reg(state, PLLFL, (pllf >> 0) & 0xff);

	क्रम (i = 0; i < ARRAY_SIZE(itd1000_fre_values); i++) अणु
		अगर (freq_khz <= itd1000_fre_values[i].freq) अणु
			itd_dbg("fre_values: %d\n", i);
			itd1000_ग_लिखो_reg(state, RFTR, itd1000_fre_values[i].values[0]);
			क्रम (j = 0; j < 9; j++)
				itd1000_ग_लिखो_reg(state, RFST1+j, itd1000_fre_values[i].values[j+1]);
			अवरोध;
		पूर्ण
	पूर्ण

	itd1000_set_vco(state, freq_khz);
पूर्ण

अटल पूर्णांक itd1000_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा itd1000_state *state = fe->tuner_priv;
	u8 pllcon1;

	itd1000_set_lo(state, c->frequency);
	itd1000_set_lpf_bw(state, c->symbol_rate);

	pllcon1 = itd1000_पढ़ो_reg(state, PLLCON1) & 0x7f;
	itd1000_ग_लिखो_reg(state, PLLCON1, pllcon1 | (1 << 7));
	itd1000_ग_लिखो_reg(state, PLLCON1, pllcon1);

	वापस 0;
पूर्ण

अटल पूर्णांक itd1000_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा itd1000_state *state = fe->tuner_priv;
	*frequency = state->frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक itd1000_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	वापस 0;
पूर्ण

अटल u8 itd1000_init_tab[][2] = अणु
	अणु PLLCON1,       0x65 पूर्ण, /* Register करोes not change */
	अणु PLLNH,         0x80 पूर्ण, /* Bits [7:6] करो not change */
	अणु RESERVED_0X6D, 0x3b पूर्ण,
	अणु VCO_CHP2_I2C,  0x12 पूर्ण,
	अणु 0x72,          0xf9 पूर्ण, /* No such regsister defined */
	अणु RESERVED_0X73, 0xff पूर्ण,
	अणु RESERVED_0X74, 0xb2 पूर्ण,
	अणु RESERVED_0X75, 0xc7 पूर्ण,
	अणु EXTGVBBRF,     0xf0 पूर्ण,
	अणु DIVAGCCK,      0x80 पूर्ण,
	अणु BBTR,          0xa0 पूर्ण,
	अणु RESERVED_0X7E, 0x4f पूर्ण,
	अणु 0x82,          0x88 पूर्ण, /* No such regsister defined */
	अणु 0x83,          0x80 पूर्ण, /* No such regsister defined */
	अणु 0x84,          0x80 पूर्ण, /* No such regsister defined */
	अणु RESERVED_0X85, 0x74 पूर्ण,
	अणु RESERVED_0X86, 0xff पूर्ण,
	अणु RESERVED_0X88, 0x02 पूर्ण,
	अणु RESERVED_0X89, 0x16 पूर्ण,
	अणु RFST0,         0x1f पूर्ण,
	अणु RESERVED_0X94, 0x66 पूर्ण,
	अणु RESERVED_0X95, 0x66 पूर्ण,
	अणु RESERVED_0X96, 0x77 पूर्ण,
	अणु RESERVED_0X97, 0x99 पूर्ण,
	अणु RESERVED_0X98, 0xff पूर्ण,
	अणु RESERVED_0X99, 0xfc पूर्ण,
	अणु RESERVED_0X9A, 0xba पूर्ण,
	अणु RESERVED_0X9B, 0xaa पूर्ण,
पूर्ण;

अटल u8 itd1000_reinit_tab[][2] = अणु
	अणु VCO_CHP1_I2C, 0x8a पूर्ण,
	अणु BW,           0x87 पूर्ण,
	अणु GVBB_I2C,     0x03 पूर्ण,
	अणु BBGVMIN,      0x03 पूर्ण,
	अणु CON1,         0x2e पूर्ण,
पूर्ण;


अटल पूर्णांक itd1000_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा itd1000_state *state = fe->tuner_priv;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(itd1000_init_tab); i++)
		itd1000_ग_लिखो_reg(state, itd1000_init_tab[i][0], itd1000_init_tab[i][1]);

	क्रम (i = 0; i < ARRAY_SIZE(itd1000_reinit_tab); i++)
		itd1000_ग_लिखो_reg(state, itd1000_reinit_tab[i][0], itd1000_reinit_tab[i][1]);

	वापस 0;
पूर्ण

अटल पूर्णांक itd1000_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस 0;
पूर्ण

अटल व्योम itd1000_release(काष्ठा dvb_frontend *fe)
अणु
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops itd1000_tuner_ops = अणु
	.info = अणु
		.name              = "Integrant ITD1000",
		.frequency_min_hz  =  950 * MHz,
		.frequency_max_hz  = 2150 * MHz,
		.frequency_step_hz =  125 * kHz,
	पूर्ण,

	.release       = itd1000_release,

	.init          = itd1000_init,
	.sleep         = itd1000_sleep,

	.set_params    = itd1000_set_parameters,
	.get_frequency = itd1000_get_frequency,
	.get_bandwidth = itd1000_get_bandwidth
पूर्ण;


काष्ठा dvb_frontend *itd1000_attach(काष्ठा dvb_frontend *fe, काष्ठा i2c_adapter *i2c, काष्ठा itd1000_config *cfg)
अणु
	काष्ठा itd1000_state *state = शून्य;
	u8 i = 0;

	state = kzalloc(माप(काष्ठा itd1000_state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस शून्य;

	state->cfg = cfg;
	state->i2c = i2c;

	i = itd1000_पढ़ो_reg(state, 0);
	अगर (i != 0) अणु
		kमुक्त(state);
		वापस शून्य;
	पूर्ण
	itd_info("successfully identified (ID: %d)\n", i);

	स_रखो(state->shaकरोw, 0xff, माप(state->shaकरोw));
	क्रम (i = 0x65; i < 0x9c; i++)
		state->shaकरोw[i] = itd1000_पढ़ो_reg(state, i);

	स_नकल(&fe->ops.tuner_ops, &itd1000_tuner_ops, माप(काष्ठा dvb_tuner_ops));

	fe->tuner_priv = state;

	वापस fe;
पूर्ण
EXPORT_SYMBOL(itd1000_attach);

MODULE_AUTHOR("Patrick Boettcher <pb@linuxtv.org>");
MODULE_DESCRIPTION("Integrant ITD1000 driver");
MODULE_LICENSE("GPL");
