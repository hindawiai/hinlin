<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *   Sharp VA3A5JZ921 One Seg Broadcast Module driver
 *   This device is labeled as just S. 921 at the top of the frontend can
 *
 *   Copyright (C) 2009-2010 Mauro Carvalho Chehab
 *   Copyright (C) 2009-2010 Douglas Landgraf <करोugsland@redhat.com>
 *
 *   Developed क्रम Leadership SBTVD 1seg device sold in Brazil
 *
 *   Frontend module based on cx24123 driver, getting some info from
 *	the old s921 driver.
 *
 *   FIXME: Need to port to DVB v5.2 API
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "s921.h"

अटल पूर्णांक debug = 1;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Activates frontend debugging (default:0)");

#घोषणा rc(args...)  करो अणु						\
	prपूर्णांकk(KERN_ERR  "s921: " args);				\
पूर्ण जबतक (0)

#घोषणा dprपूर्णांकk(args...)						\
	करो अणु								\
		अगर (debug) अणु						\
			prपूर्णांकk(KERN_DEBUG "s921: %s: ", __func__);	\
			prपूर्णांकk(args);					\
		पूर्ण							\
	पूर्ण जबतक (0)

काष्ठा s921_state अणु
	काष्ठा i2c_adapter *i2c;
	स्थिर काष्ठा s921_config *config;

	काष्ठा dvb_frontend frontend;

	/* The Demod can't easily provide these, we cache them */
	u32 currentfreq;
पूर्ण;

/*
 * Various tuner शेषs need to be established क्रम a given frequency kHz.
 * fixme: The bounds on the bands करो not match the करोc in real lअगरe.
 * fixme: Some of them have been moved, other might need adjusपंचांगent.
 */
अटल काष्ठा s921_bandselect_val अणु
	u32 freq_low;
	u8  band_reg;
पूर्ण s921_bandselect[] = अणु
	अणु         0, 0x7b पूर्ण,
	अणु 485140000, 0x5b पूर्ण,
	अणु 515140000, 0x3b पूर्ण,
	अणु 545140000, 0x1b पूर्ण,
	अणु 599140000, 0xfb पूर्ण,
	अणु 623140000, 0xdb पूर्ण,
	अणु 659140000, 0xbb पूर्ण,
	अणु 713140000, 0x9b पूर्ण,
पूर्ण;

काष्ठा regdata अणु
	u8 reg;
	u8 data;
पूर्ण;

अटल काष्ठा regdata s921_init[] = अणु
	अणु 0x01, 0x80 पूर्ण,		/* Probably, a reset sequence */
	अणु 0x01, 0x40 पूर्ण,
	अणु 0x01, 0x80 पूर्ण,
	अणु 0x01, 0x40 पूर्ण,

	अणु 0x02, 0x00 पूर्ण,
	अणु 0x03, 0x40 पूर्ण,
	अणु 0x04, 0x01 पूर्ण,
	अणु 0x05, 0x00 पूर्ण,
	अणु 0x06, 0x00 पूर्ण,
	अणु 0x07, 0x00 पूर्ण,
	अणु 0x08, 0x00 पूर्ण,
	अणु 0x09, 0x00 पूर्ण,
	अणु 0x0a, 0x00 पूर्ण,
	अणु 0x0b, 0x5a पूर्ण,
	अणु 0x0c, 0x00 पूर्ण,
	अणु 0x0d, 0x00 पूर्ण,
	अणु 0x0f, 0x00 पूर्ण,
	अणु 0x13, 0x1b पूर्ण,
	अणु 0x14, 0x80 पूर्ण,
	अणु 0x15, 0x40 पूर्ण,
	अणु 0x17, 0x70 पूर्ण,
	अणु 0x18, 0x01 पूर्ण,
	अणु 0x19, 0x12 पूर्ण,
	अणु 0x1a, 0x01 पूर्ण,
	अणु 0x1b, 0x12 पूर्ण,
	अणु 0x1c, 0xa0 पूर्ण,
	अणु 0x1d, 0x00 पूर्ण,
	अणु 0x1e, 0x0a पूर्ण,
	अणु 0x1f, 0x08 पूर्ण,
	अणु 0x20, 0x40 पूर्ण,
	अणु 0x21, 0xff पूर्ण,
	अणु 0x22, 0x4c पूर्ण,
	अणु 0x23, 0x4e पूर्ण,
	अणु 0x24, 0x4c पूर्ण,
	अणु 0x25, 0x00 पूर्ण,
	अणु 0x26, 0x00 पूर्ण,
	अणु 0x27, 0xf4 पूर्ण,
	अणु 0x28, 0x60 पूर्ण,
	अणु 0x29, 0x88 पूर्ण,
	अणु 0x2a, 0x40 पूर्ण,
	अणु 0x2b, 0x40 पूर्ण,
	अणु 0x2c, 0xff पूर्ण,
	अणु 0x2d, 0x00 पूर्ण,
	अणु 0x2e, 0xff पूर्ण,
	अणु 0x2f, 0x00 पूर्ण,
	अणु 0x30, 0x20 पूर्ण,
	अणु 0x31, 0x06 पूर्ण,
	अणु 0x32, 0x0c पूर्ण,
	अणु 0x34, 0x0f पूर्ण,
	अणु 0x37, 0xfe पूर्ण,
	अणु 0x38, 0x00 पूर्ण,
	अणु 0x39, 0x63 पूर्ण,
	अणु 0x3a, 0x10 पूर्ण,
	अणु 0x3b, 0x10 पूर्ण,
	अणु 0x47, 0x00 पूर्ण,
	अणु 0x49, 0xe5 पूर्ण,
	अणु 0x4b, 0x00 पूर्ण,
	अणु 0x50, 0xc0 पूर्ण,
	अणु 0x52, 0x20 पूर्ण,
	अणु 0x54, 0x5a पूर्ण,
	अणु 0x55, 0x5b पूर्ण,
	अणु 0x56, 0x40 पूर्ण,
	अणु 0x57, 0x70 पूर्ण,
	अणु 0x5c, 0x50 पूर्ण,
	अणु 0x5d, 0x00 पूर्ण,
	अणु 0x62, 0x17 पूर्ण,
	अणु 0x63, 0x2f पूर्ण,
	अणु 0x64, 0x6f पूर्ण,
	अणु 0x68, 0x00 पूर्ण,
	अणु 0x69, 0x89 पूर्ण,
	अणु 0x6a, 0x00 पूर्ण,
	अणु 0x6b, 0x00 पूर्ण,
	अणु 0x6c, 0x00 पूर्ण,
	अणु 0x6d, 0x00 पूर्ण,
	अणु 0x6e, 0x00 पूर्ण,
	अणु 0x70, 0x10 पूर्ण,
	अणु 0x71, 0x00 पूर्ण,
	अणु 0x75, 0x00 पूर्ण,
	अणु 0x76, 0x30 पूर्ण,
	अणु 0x77, 0x01 पूर्ण,
	अणु 0xaf, 0x00 पूर्ण,
	अणु 0xb0, 0xa0 पूर्ण,
	अणु 0xb2, 0x3d पूर्ण,
	अणु 0xb3, 0x25 पूर्ण,
	अणु 0xb4, 0x8b पूर्ण,
	अणु 0xb5, 0x4b पूर्ण,
	अणु 0xb6, 0x3f पूर्ण,
	अणु 0xb7, 0xff पूर्ण,
	अणु 0xb8, 0xff पूर्ण,
	अणु 0xb9, 0xfc पूर्ण,
	अणु 0xba, 0x00 पूर्ण,
	अणु 0xbb, 0x00 पूर्ण,
	अणु 0xbc, 0x00 पूर्ण,
	अणु 0xd0, 0x30 पूर्ण,
	अणु 0xe4, 0x84 पूर्ण,
	अणु 0xf0, 0x48 पूर्ण,
	अणु 0xf1, 0x19 पूर्ण,
	अणु 0xf2, 0x5a पूर्ण,
	अणु 0xf3, 0x8e पूर्ण,
	अणु 0xf4, 0x2d पूर्ण,
	अणु 0xf5, 0x07 पूर्ण,
	अणु 0xf6, 0x5a पूर्ण,
	अणु 0xf7, 0xba पूर्ण,
	अणु 0xf8, 0xd7 पूर्ण,
पूर्ण;

अटल काष्ठा regdata s921_prefreq[] = अणु
	अणु 0x47, 0x60 पूर्ण,
	अणु 0x68, 0x00 पूर्ण,
	अणु 0x69, 0x89 पूर्ण,
	अणु 0xf0, 0x48 पूर्ण,
	अणु 0xf1, 0x19 पूर्ण,
पूर्ण;

अटल काष्ठा regdata s921_postfreq[] = अणु
	अणु 0xf5, 0xae पूर्ण,
	अणु 0xf6, 0xb7 पूर्ण,
	अणु 0xf7, 0xba पूर्ण,
	अणु 0xf8, 0xd7 पूर्ण,
	अणु 0x68, 0x0a पूर्ण,
	अणु 0x69, 0x09 पूर्ण,
पूर्ण;

अटल पूर्णांक s921_i2c_ग_लिखोreg(काष्ठा s921_state *state,
			     u8 i2c_addr, पूर्णांक reg, पूर्णांक data)
अणु
	u8 buf[] = अणु reg, data पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = i2c_addr, .flags = 0, .buf = buf, .len = 2
	पूर्ण;
	पूर्णांक rc;

	rc = i2c_transfer(state->i2c, &msg, 1);
	अगर (rc != 1) अणु
		prपूर्णांकk("%s: writereg rcor(rc == %i, reg == 0x%02x, data == 0x%02x)\n",
		       __func__, rc, reg, data);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s921_i2c_ग_लिखोregdata(काष्ठा s921_state *state, u8 i2c_addr,
				 काष्ठा regdata *rd, पूर्णांक size)
अणु
	पूर्णांक i, rc;

	क्रम (i = 0; i < size; i++) अणु
		rc = s921_i2c_ग_लिखोreg(state, i2c_addr, rd[i].reg, rd[i].data);
		अगर (rc < 0)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक s921_i2c_पढ़ोreg(काष्ठा s921_state *state, u8 i2c_addr, u8 reg)
अणु
	u8 val;
	पूर्णांक rc;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = i2c_addr, .flags = 0, .buf = &reg, .len = 1 पूर्ण,
		अणु .addr = i2c_addr, .flags = I2C_M_RD, .buf = &val, .len = 1 पूर्ण
	पूर्ण;

	rc = i2c_transfer(state->i2c, msg, 2);

	अगर (rc != 2) अणु
		rc("%s: reg=0x%x (rcor=%d)\n", __func__, reg, rc);
		वापस rc;
	पूर्ण

	वापस val;
पूर्ण

#घोषणा s921_पढ़ोreg(state, reg) \
	s921_i2c_पढ़ोreg(state, state->config->demod_address, reg)
#घोषणा s921_ग_लिखोreg(state, reg, val) \
	s921_i2c_ग_लिखोreg(state, state->config->demod_address, reg, val)
#घोषणा s921_ग_लिखोregdata(state, regdata) \
	s921_i2c_ग_लिखोregdata(state, state->config->demod_address, \
	regdata, ARRAY_SIZE(regdata))

अटल पूर्णांक s921_pll_tune(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा s921_state *state = fe->demodulator_priv;
	पूर्णांक band, rc, i;
	अचिन्हित दीर्घ f_offset;
	u8 f_चयन;
	u64 offset;

	dprपूर्णांकk("frequency=%i\n", p->frequency);

	क्रम (band = 0; band < ARRAY_SIZE(s921_bandselect); band++)
		अगर (p->frequency < s921_bandselect[band].freq_low)
			अवरोध;
	band--;

	अगर (band < 0) अणु
		rc("%s: frequency out of range\n", __func__);
		वापस -EINVAL;
	पूर्ण

	f_चयन = s921_bandselect[band].band_reg;

	offset = ((u64)p->frequency) * 258;
	करो_भाग(offset, 6000000);
	f_offset = ((अचिन्हित दीर्घ)offset) + 2321;

	rc = s921_ग_लिखोregdata(state, s921_prefreq);
	अगर (rc < 0)
		वापस rc;

	rc = s921_ग_लिखोreg(state, 0xf2, (f_offset >> 8) & 0xff);
	अगर (rc < 0)
		वापस rc;

	rc = s921_ग_लिखोreg(state, 0xf3, f_offset & 0xff);
	अगर (rc < 0)
		वापस rc;

	rc = s921_ग_लिखोreg(state, 0xf4, f_चयन);
	अगर (rc < 0)
		वापस rc;

	rc = s921_ग_लिखोregdata(state, s921_postfreq);
	अगर (rc < 0)
		वापस rc;

	क्रम (i = 0 ; i < 6; i++) अणु
		rc = s921_पढ़ोreg(state, 0x80);
		dprपूर्णांकk("status 0x80: %02x\n", rc);
	पूर्ण
	rc = s921_ग_लिखोreg(state, 0x01, 0x40);
	अगर (rc < 0)
		वापस rc;

	rc = s921_पढ़ोreg(state, 0x01);
	dprपूर्णांकk("status 0x01: %02x\n", rc);

	rc = s921_पढ़ोreg(state, 0x80);
	dprपूर्णांकk("status 0x80: %02x\n", rc);

	rc = s921_पढ़ोreg(state, 0x80);
	dprपूर्णांकk("status 0x80: %02x\n", rc);

	rc = s921_पढ़ोreg(state, 0x32);
	dprपूर्णांकk("status 0x32: %02x\n", rc);

	dprपूर्णांकk("pll tune band=%d, pll=%d\n", f_चयन, (पूर्णांक)f_offset);

	वापस 0;
पूर्ण

अटल पूर्णांक s921_initfe(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s921_state *state = fe->demodulator_priv;
	पूर्णांक rc;

	dprपूर्णांकk("\n");

	rc = s921_ग_लिखोregdata(state, s921_init);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक s921_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा s921_state *state = fe->demodulator_priv;
	पूर्णांक regstatus, rc;

	*status = 0;

	rc = s921_पढ़ोreg(state, 0x81);
	अगर (rc < 0)
		वापस rc;

	regstatus = rc << 8;

	rc = s921_पढ़ोreg(state, 0x82);
	अगर (rc < 0)
		वापस rc;

	regstatus |= rc;

	dprपूर्णांकk("status = %04x\n", regstatus);

	/* Full Sync - We करोn't know what each bit means on regs 0x81/0x82 */
	अगर ((regstatus & 0xff) == 0x40) अणु
		*status = FE_HAS_SIGNAL  |
			  FE_HAS_CARRIER |
			  FE_HAS_VITERBI |
			  FE_HAS_SYNC    |
			  FE_HAS_LOCK;
	पूर्ण अन्यथा अगर (regstatus & 0x40) अणु
		/* This is बंद to Full Sync, but not enough to get useful info */
		*status = FE_HAS_SIGNAL  |
			  FE_HAS_CARRIER |
			  FE_HAS_VITERBI |
			  FE_HAS_SYNC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s921_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	क्रमागत fe_status	status;
	काष्ठा s921_state *state = fe->demodulator_priv;
	पूर्णांक rc;

	/* FIXME: Use the proper रेजिस्टर क्रम it... 0x80? */
	rc = s921_पढ़ो_status(fe, &status);
	अगर (rc < 0)
		वापस rc;

	*strength = (status & FE_HAS_LOCK) ? 0xffff : 0;

	dprपूर्णांकk("strength = 0x%04x\n", *strength);

	rc = s921_पढ़ोreg(state, 0x01);
	dprपूर्णांकk("status 0x01: %02x\n", rc);

	rc = s921_पढ़ोreg(state, 0x80);
	dprपूर्णांकk("status 0x80: %02x\n", rc);

	rc = s921_पढ़ोreg(state, 0x32);
	dprपूर्णांकk("status 0x32: %02x\n", rc);

	वापस 0;
पूर्ण

अटल पूर्णांक s921_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा s921_state *state = fe->demodulator_priv;
	पूर्णांक rc;

	dprपूर्णांकk("\n");

	/* FIXME: We करोn't know how to use non-स्वतः mode */

	rc = s921_pll_tune(fe);
	अगर (rc < 0)
		वापस rc;

	state->currentfreq = p->frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक s921_get_frontend(काष्ठा dvb_frontend *fe,
			     काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा s921_state *state = fe->demodulator_priv;

	/* FIXME: Probably it is possible to get it from regs f1 and f2 */
	p->frequency = state->currentfreq;
	p->delivery_प्रणाली = SYS_ISDBT;

	वापस 0;
पूर्ण

अटल पूर्णांक s921_tune(काष्ठा dvb_frontend *fe,
			bool re_tune,
			अचिन्हित पूर्णांक mode_flags,
			अचिन्हित पूर्णांक *delay,
			क्रमागत fe_status *status)
अणु
	पूर्णांक rc = 0;

	dprपूर्णांकk("\n");

	अगर (re_tune)
		rc = s921_set_frontend(fe);

	अगर (!(mode_flags & FE_TUNE_MODE_ONESHOT))
		s921_पढ़ो_status(fe, status);

	वापस rc;
पूर्ण

अटल क्रमागत dvbfe_algo s921_get_algo(काष्ठा dvb_frontend *fe)
अणु
	वापस DVBFE_ALGO_HW;
पूर्ण

अटल व्योम s921_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा s921_state *state = fe->demodulator_priv;

	dprपूर्णांकk("\n");
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops s921_ops;

काष्ठा dvb_frontend *s921_attach(स्थिर काष्ठा s921_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	/* allocate memory क्रम the पूर्णांकernal state */
	काष्ठा s921_state *state =
		kzalloc(माप(काष्ठा s921_state), GFP_KERNEL);

	dprपूर्णांकk("\n");
	अगर (!state) अणु
		rc("Unable to kzalloc\n");
		वापस शून्य;
	पूर्ण

	/* setup the state */
	state->config = config;
	state->i2c = i2c;

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &s921_ops,
		माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	वापस &state->frontend;
पूर्ण
EXPORT_SYMBOL(s921_attach);

अटल स्थिर काष्ठा dvb_frontend_ops s921_ops = अणु
	.delsys = अणु SYS_ISDBT पूर्ण,
	/* Use dib8000 values per शेष */
	.info = अणु
		.name = "Sharp S921",
		.frequency_min_hz = 470 * MHz,
		/*
		 * Max should be 770MHz instead, according with Sharp करोcs,
		 * but Leadership करोc says it works up to 806 MHz. This is
		 * required to get channel 69, used in Brazil
		 */
		.frequency_max_hz = 806 * MHz,
		.caps =  FE_CAN_INVERSION_AUTO |
			 FE_CAN_FEC_1_2  | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			 FE_CAN_FEC_5_6  | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			 FE_CAN_QPSK     | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
			 FE_CAN_QAM_AUTO | FE_CAN_TRANSMISSION_MODE_AUTO |
			 FE_CAN_GUARD_INTERVAL_AUTO | FE_CAN_RECOVER |
			 FE_CAN_HIERARCHY_AUTO,
	पूर्ण,

	.release = s921_release,

	.init = s921_initfe,
	.set_frontend = s921_set_frontend,
	.get_frontend = s921_get_frontend,
	.पढ़ो_status = s921_पढ़ो_status,
	.पढ़ो_संकेत_strength = s921_पढ़ो_संकेत_strength,
	.tune = s921_tune,
	.get_frontend_algo = s921_get_algo,
पूर्ण;

MODULE_DESCRIPTION("DVB Frontend module for Sharp S921 hardware");
MODULE_AUTHOR("Mauro Carvalho Chehab");
MODULE_AUTHOR("Douglas Landgraf <dougsland@redhat.com>");
MODULE_LICENSE("GPL");
