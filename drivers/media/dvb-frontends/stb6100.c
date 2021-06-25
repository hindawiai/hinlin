<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	STB6100 Silicon Tuner
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

	Copyright (C) ST Microelectronics

*/

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <media/dvb_frontend.h>
#समावेश "stb6100.h"

अटल अचिन्हित पूर्णांक verbose;
module_param(verbose, पूर्णांक, 0644);

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

#घोषणा FE_ERROR		0
#घोषणा FE_NOTICE		1
#घोषणा FE_INFO			2
#घोषणा FE_DEBUG		3

#घोषणा dprपूर्णांकk(x, y, z, क्रमmat, arg...) करो अणु						\
	अगर (z) अणु									\
		अगर	((x > FE_ERROR) && (x > y))					\
			prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", __func__ , ##arg);		\
		अन्यथा अगर	((x > FE_NOTICE) && (x > y))					\
			prपूर्णांकk(KERN_NOTICE "%s: " क्रमmat "\n", __func__ , ##arg);	\
		अन्यथा अगर ((x > FE_INFO) && (x > y))					\
			prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", __func__ , ##arg);		\
		अन्यथा अगर ((x > FE_DEBUG) && (x > y))					\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n", __func__ , ##arg);	\
	पूर्ण अन्यथा अणु									\
		अगर (x > y)								\
			prपूर्णांकk(क्रमmat, ##arg);						\
	पूर्ण										\
पूर्ण जबतक (0)

काष्ठा stb6100_lkup अणु
	u32 val_low;
	u32 val_high;
	u8   reg;
पूर्ण;

अटल व्योम stb6100_release(काष्ठा dvb_frontend *fe);

अटल स्थिर काष्ठा stb6100_lkup lkup[] = अणु
	अणु       0,  950000, 0x0a पूर्ण,
	अणु  950000, 1000000, 0x0a पूर्ण,
	अणु 1000000, 1075000, 0x0c पूर्ण,
	अणु 1075000, 1200000, 0x00 पूर्ण,
	अणु 1200000, 1300000, 0x01 पूर्ण,
	अणु 1300000, 1370000, 0x02 पूर्ण,
	अणु 1370000, 1470000, 0x04 पूर्ण,
	अणु 1470000, 1530000, 0x05 पूर्ण,
	अणु 1530000, 1650000, 0x06 पूर्ण,
	अणु 1650000, 1800000, 0x08 पूर्ण,
	अणु 1800000, 1950000, 0x0a पूर्ण,
	अणु 1950000, 2150000, 0x0c पूर्ण,
	अणु 2150000, 9999999, 0x0c पूर्ण,
	अणु       0,       0, 0x00 पूर्ण
पूर्ण;

/* Register names क्रम easy debugging.	*/
अटल स्थिर अक्षर *stb6100_regnames[] = अणु
	[STB6100_LD]		= "LD",
	[STB6100_VCO]		= "VCO",
	[STB6100_NI]		= "NI",
	[STB6100_NF_LSB]	= "NF",
	[STB6100_K]		= "K",
	[STB6100_G]		= "G",
	[STB6100_F]		= "F",
	[STB6100_DLB]		= "DLB",
	[STB6100_TEST1]		= "TEST1",
	[STB6100_FCCK]		= "FCCK",
	[STB6100_LPEN]		= "LPEN",
	[STB6100_TEST3]		= "TEST3",
पूर्ण;

/* Template क्रम normalisation, i.e. setting unused or unकरोcumented
 * bits as required according to the करोcumentation.
 */
काष्ठा stb6100_regmask अणु
	u8 mask;
	u8 set;
पूर्ण;

अटल स्थिर काष्ठा stb6100_regmask stb6100_ढाँचा[] = अणु
	[STB6100_LD]		= अणु 0xff, 0x00 पूर्ण,
	[STB6100_VCO]		= अणु 0xff, 0x00 पूर्ण,
	[STB6100_NI]		= अणु 0xff, 0x00 पूर्ण,
	[STB6100_NF_LSB]	= अणु 0xff, 0x00 पूर्ण,
	[STB6100_K]		= अणु 0xc7, 0x38 पूर्ण,
	[STB6100_G]		= अणु 0xef, 0x10 पूर्ण,
	[STB6100_F]		= अणु 0x1f, 0xc0 पूर्ण,
	[STB6100_DLB]		= अणु 0x38, 0xc4 पूर्ण,
	[STB6100_TEST1]		= अणु 0x00, 0x8f पूर्ण,
	[STB6100_FCCK]		= अणु 0x40, 0x0d पूर्ण,
	[STB6100_LPEN]		= अणु 0xf0, 0x0b पूर्ण,
	[STB6100_TEST3]		= अणु 0x00, 0xde पूर्ण,
पूर्ण;

/*
 * Currently unused. Some boards might need it in the future
 */
अटल अंतरभूत व्योम stb6100_normalise_regs(u8 regs[])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < STB6100_NUMREGS; i++)
		regs[i] = (regs[i] & stb6100_ढाँचा[i].mask) | stb6100_ढाँचा[i].set;
पूर्ण

अटल पूर्णांक stb6100_पढ़ो_regs(काष्ठा stb6100_state *state, u8 regs[])
अणु
	पूर्णांक rc;
	काष्ठा i2c_msg msg = अणु
		.addr	= state->config->tuner_address,
		.flags	= I2C_M_RD,
		.buf	= regs,
		.len	= STB6100_NUMREGS
	पूर्ण;

	rc = i2c_transfer(state->i2c, &msg, 1);
	अगर (unlikely(rc != 1)) अणु
		dprपूर्णांकk(verbose, FE_ERROR, 1, "Read (0x%x) err, rc=[%d]",
			state->config->tuner_address, rc);

		वापस -EREMOTEIO;
	पूर्ण
	अगर (unlikely(verbose > FE_DEBUG)) अणु
		पूर्णांक i;

		dprपूर्णांकk(verbose, FE_DEBUG, 1, "    Read from 0x%02x", state->config->tuner_address);
		क्रम (i = 0; i < STB6100_NUMREGS; i++)
			dprपूर्णांकk(verbose, FE_DEBUG, 1, "        %s: 0x%02x", stb6100_regnames[i], regs[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stb6100_पढ़ो_reg(काष्ठा stb6100_state *state, u8 reg)
अणु
	u8 regs[STB6100_NUMREGS];

	काष्ठा i2c_msg msg = अणु
		.addr	= state->config->tuner_address + reg,
		.flags	= I2C_M_RD,
		.buf	= regs,
		.len	= 1
	पूर्ण;

	i2c_transfer(state->i2c, &msg, 1);

	अगर (unlikely(reg >= STB6100_NUMREGS)) अणु
		dprपूर्णांकk(verbose, FE_ERROR, 1, "Invalid register offset 0x%x", reg);
		वापस -EINVAL;
	पूर्ण
	अगर (unlikely(verbose > FE_DEBUG)) अणु
		dprपूर्णांकk(verbose, FE_DEBUG, 1, "    Read from 0x%02x", state->config->tuner_address);
		dprपूर्णांकk(verbose, FE_DEBUG, 1, "        %s: 0x%02x", stb6100_regnames[reg], regs[0]);
	पूर्ण

	वापस (अचिन्हित पूर्णांक)regs[0];
पूर्ण

अटल पूर्णांक stb6100_ग_लिखो_reg_range(काष्ठा stb6100_state *state, u8 buf[], पूर्णांक start, पूर्णांक len)
अणु
	पूर्णांक rc;
	u8 cmdbuf[MAX_XFER_SIZE];
	काष्ठा i2c_msg msg = अणु
		.addr	= state->config->tuner_address,
		.flags	= 0,
		.buf	= cmdbuf,
		.len	= len + 1
	पूर्ण;

	अगर (1 + len > माप(cmdbuf)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: i2c wr: len=%d is too big!\n",
		       KBUILD_MODNAME, len);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(start < 1 || start + len > STB6100_NUMREGS)) अणु
		dprपूर्णांकk(verbose, FE_ERROR, 1, "Invalid register range %d:%d",
			start, len);
		वापस -EINVAL;
	पूर्ण
	स_नकल(&cmdbuf[1], buf, len);
	cmdbuf[0] = start;

	अगर (unlikely(verbose > FE_DEBUG)) अणु
		पूर्णांक i;

		dprपूर्णांकk(verbose, FE_DEBUG, 1, "    Write @ 0x%02x: [%d:%d]", state->config->tuner_address, start, len);
		क्रम (i = 0; i < len; i++)
			dprपूर्णांकk(verbose, FE_DEBUG, 1, "        %s: 0x%02x", stb6100_regnames[start + i], buf[i]);
	पूर्ण
	rc = i2c_transfer(state->i2c, &msg, 1);
	अगर (unlikely(rc != 1)) अणु
		dprपूर्णांकk(verbose, FE_ERROR, 1, "(0x%x) write err [%d:%d], rc=[%d]",
			(अचिन्हित पूर्णांक)state->config->tuner_address, start, len,	rc);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stb6100_ग_लिखो_reg(काष्ठा stb6100_state *state, u8 reg, u8 data)
अणु
	u8 पंचांगp = data; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	अगर (unlikely(reg >= STB6100_NUMREGS)) अणु
		dprपूर्णांकk(verbose, FE_ERROR, 1, "Invalid register offset 0x%x", reg);
		वापस -EREMOTEIO;
	पूर्ण
	पंचांगp = (पंचांगp & stb6100_ढाँचा[reg].mask) | stb6100_ढाँचा[reg].set;
	वापस stb6100_ग_लिखो_reg_range(state, &पंचांगp, reg, 1);
पूर्ण


अटल पूर्णांक stb6100_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	पूर्णांक rc;
	काष्ठा stb6100_state *state = fe->tuner_priv;

	rc = stb6100_पढ़ो_reg(state, STB6100_LD);
	अगर (rc < 0) अणु
		dprपूर्णांकk(verbose, FE_ERROR, 1, "%s failed", __func__);
		वापस rc;
	पूर्ण
	वापस (rc & STB6100_LD_LOCK) ? TUNER_STATUS_LOCKED : 0;
पूर्ण

अटल पूर्णांक stb6100_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bandwidth)
अणु
	पूर्णांक rc;
	u8 f;
	u32 bw;
	काष्ठा stb6100_state *state = fe->tuner_priv;

	rc = stb6100_पढ़ो_reg(state, STB6100_F);
	अगर (rc < 0)
		वापस rc;
	f = rc & STB6100_F_F;

	bw = (f + 5) * 2000;	/* x2 क्रम ZIF	*/

	*bandwidth = state->bandwidth = bw * 1000;
	dprपूर्णांकk(verbose, FE_DEBUG, 1, "bandwidth = %u Hz", state->bandwidth);
	वापस 0;
पूर्ण

अटल पूर्णांक stb6100_set_bandwidth(काष्ठा dvb_frontend *fe, u32 bandwidth)
अणु
	u32 पंचांगp;
	पूर्णांक rc;
	काष्ठा stb6100_state *state = fe->tuner_priv;

	dprपूर्णांकk(verbose, FE_DEBUG, 1, "set bandwidth to %u Hz", bandwidth);

	bandwidth /= 2; /* ZIF */

	अगर (bandwidth >= 36000000)	/* F[4:0] BW/2 max =31+5=36 mhz क्रम F=31	*/
		पंचांगp = 31;
	अन्यथा अगर (bandwidth <= 5000000)	/* bw/2 min = 5Mhz क्रम F=0			*/
		पंचांगp = 0;
	अन्यथा				/* अगर 5 < bw/2 < 36				*/
		पंचांगp = (bandwidth + 500000) / 1000000 - 5;

	/* Turn on LPF bandwidth setting घड़ी control,
	 * set bandwidth, रुको 10ms, turn off.
	 */
	rc = stb6100_ग_लिखो_reg(state, STB6100_FCCK, 0x0d | STB6100_FCCK_FCCK);
	अगर (rc < 0)
		वापस rc;
	rc = stb6100_ग_लिखो_reg(state, STB6100_F, 0xc0 | पंचांगp);
	अगर (rc < 0)
		वापस rc;

	msleep(5);  /*  This is dangerous as another (related) thपढ़ो may start */

	rc = stb6100_ग_लिखो_reg(state, STB6100_FCCK, 0x0d);
	अगर (rc < 0)
		वापस rc;

	msleep(10);  /*  This is dangerous as another (related) thपढ़ो may start */

	वापस 0;
पूर्ण

अटल पूर्णांक stb6100_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	पूर्णांक rc;
	u32 nपूर्णांक, nfrac, fvco;
	पूर्णांक psd2, oभाग;
	काष्ठा stb6100_state *state = fe->tuner_priv;
	u8 regs[STB6100_NUMREGS];

	rc = stb6100_पढ़ो_regs(state, regs);
	अगर (rc < 0)
		वापस rc;

	oभाग = (regs[STB6100_VCO] & STB6100_VCO_ODIV) >> STB6100_VCO_ODIV_SHIFT;
	psd2 = (regs[STB6100_K] & STB6100_K_PSD2) >> STB6100_K_PSD2_SHIFT;
	nपूर्णांक = regs[STB6100_NI];
	nfrac = ((regs[STB6100_K] & STB6100_K_NF_MSB) << 8) | regs[STB6100_NF_LSB];
	fvco = (nfrac * state->reference >> (9 - psd2)) + (nपूर्णांक * state->reference << psd2);
	*frequency = state->frequency = fvco >> (oभाग + 1);

	dprपूर्णांकk(verbose, FE_DEBUG, 1,
		"frequency = %u kHz, odiv = %u, psd2 = %u, fxtal = %u kHz, fvco = %u kHz, N(I) = %u, N(F) = %u",
		state->frequency, oभाग, psd2, state->reference,	fvco, nपूर्णांक, nfrac);
	वापस 0;
पूर्ण


अटल पूर्णांक stb6100_set_frequency(काष्ठा dvb_frontend *fe, u32 frequency)
अणु
	पूर्णांक rc;
	स्थिर काष्ठा stb6100_lkup *ptr;
	काष्ठा stb6100_state *state = fe->tuner_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	u32 srate = 0, fvco, nपूर्णांक, nfrac;
	u8 regs[STB6100_NUMREGS];
	u8 g, psd2, oभाग;

	dprपूर्णांकk(verbose, FE_DEBUG, 1, "Version 2010-8-14 13:51");

	अगर (fe->ops.get_frontend) अणु
		dprपूर्णांकk(verbose, FE_DEBUG, 1, "Get frontend parameters");
		fe->ops.get_frontend(fe, p);
	पूर्ण
	srate = p->symbol_rate;

	/* Set up tuner cleanly, LPF calibration on */
	rc = stb6100_ग_लिखो_reg(state, STB6100_FCCK, 0x4d | STB6100_FCCK_FCCK);
	अगर (rc < 0)
		वापस rc;  /* allow LPF calibration */

	/* PLL Loop disabled, bias on, VCO on, synth on */
	regs[STB6100_LPEN] = 0xeb;
	rc = stb6100_ग_लिखो_reg(state, STB6100_LPEN, regs[STB6100_LPEN]);
	अगर (rc < 0)
		वापस rc;

	/* Program the रेजिस्टरs with their data values */

	/* VCO भागide ratio (LO भागide ratio, VCO prescaler enable).	*/
	अगर (frequency <= 1075000)
		oभाग = 1;
	अन्यथा
		oभाग = 0;

	/* VCO enabled, search घड़ी off as per LL3.7, 3.4.1 */
	regs[STB6100_VCO] = 0xe0 | (oभाग << STB6100_VCO_ODIV_SHIFT);

	/* OSM	*/
	क्रम (ptr = lkup;
	     (ptr->val_high != 0) && !CHKRANGE(frequency, ptr->val_low, ptr->val_high);
	     ptr++);

	अगर (ptr->val_high == 0) अणु
		prपूर्णांकk(KERN_ERR "%s: frequency out of range: %u kHz\n", __func__, frequency);
		वापस -EINVAL;
	पूर्ण
	regs[STB6100_VCO] = (regs[STB6100_VCO] & ~STB6100_VCO_OSM) | ptr->reg;
	rc = stb6100_ग_लिखो_reg(state, STB6100_VCO, regs[STB6100_VCO]);
	अगर (rc < 0)
		वापस rc;

	अगर ((frequency > 1075000) && (frequency <= 1325000))
		psd2 = 0;
	अन्यथा
		psd2 = 1;
	/* F(VCO) = F(LO) * (ODIV == 0 ? 2 : 4)			*/
	fvco = frequency << (1 + oभाग);
	/* N(I) = न्यूनमान(f(VCO) / (f(XTAL) * (PSD2 ? 2 : 1)))	*/
	nपूर्णांक = fvco / (state->reference << psd2);
	/* N(F) = round(f(VCO) / f(XTAL) * (PSD2 ? 2 : 1) - N(I)) * 2 ^ 9	*/
	nfrac = DIV_ROUND_CLOSEST((fvco - (nपूर्णांक * state->reference << psd2))
					 << (9 - psd2), state->reference);

	/* NI */
	regs[STB6100_NI] = nपूर्णांक;
	rc = stb6100_ग_लिखो_reg(state, STB6100_NI, regs[STB6100_NI]);
	अगर (rc < 0)
		वापस rc;

	/* NF */
	regs[STB6100_NF_LSB] = nfrac;
	rc = stb6100_ग_लिखो_reg(state, STB6100_NF_LSB, regs[STB6100_NF_LSB]);
	अगर (rc < 0)
		वापस rc;

	/* K */
	regs[STB6100_K] = (0x38 & ~STB6100_K_PSD2) | (psd2 << STB6100_K_PSD2_SHIFT);
	regs[STB6100_K] = (regs[STB6100_K] & ~STB6100_K_NF_MSB) | ((nfrac >> 8) & STB6100_K_NF_MSB);
	rc = stb6100_ग_लिखो_reg(state, STB6100_K, regs[STB6100_K]);
	अगर (rc < 0)
		वापस rc;

	/* G Baseband gain. */
	अगर (srate >= 15000000)
		g = 9;  /*  +4 dB */
	अन्यथा अगर (srate >= 5000000)
		g = 11; /*  +8 dB */
	अन्यथा
		g = 14; /* +14 dB */

	regs[STB6100_G] = (0x10 & ~STB6100_G_G) | g;
	regs[STB6100_G] &= ~STB6100_G_GCT; /* mask GCT */
	regs[STB6100_G] |= (1 << 5); /* 2Vp-p Mode */
	rc = stb6100_ग_लिखो_reg(state, STB6100_G, regs[STB6100_G]);
	अगर (rc < 0)
		वापस rc;

	/* F we करोn't ग_लिखो as it is set up in BW set */

	/* DLB set DC servo loop BW to 160Hz (LLA 3.8 / 2.1) */
	regs[STB6100_DLB] = 0xcc;
	rc = stb6100_ग_लिखो_reg(state, STB6100_DLB, regs[STB6100_DLB]);
	अगर (rc < 0)
		वापस rc;

	dprपूर्णांकk(verbose, FE_DEBUG, 1,
		"frequency = %u, srate = %u, g = %u, odiv = %u, psd2 = %u, fxtal = %u, osm = %u, fvco = %u, N(I) = %u, N(F) = %u",
		frequency, srate, (अचिन्हित पूर्णांक)g, (अचिन्हित पूर्णांक)oभाग,
		(अचिन्हित पूर्णांक)psd2, state->reference,
		ptr->reg, fvco, nपूर्णांक, nfrac);

	/* Set up the test रेजिस्टरs */
	regs[STB6100_TEST1] = 0x8f;
	rc = stb6100_ग_लिखो_reg(state, STB6100_TEST1, regs[STB6100_TEST1]);
	अगर (rc < 0)
		वापस rc;
	regs[STB6100_TEST3] = 0xde;
	rc = stb6100_ग_लिखो_reg(state, STB6100_TEST3, regs[STB6100_TEST3]);
	अगर (rc < 0)
		वापस rc;

	/* Bring up tuner according to LLA 3.7 3.4.1, step 2 */
	regs[STB6100_LPEN] = 0xfb; /* PLL Loop enabled, bias on, VCO on, synth on */
	rc = stb6100_ग_लिखो_reg(state, STB6100_LPEN, regs[STB6100_LPEN]);
	अगर (rc < 0)
		वापस rc;

	msleep(2);

	/* Bring up tuner according to LLA 3.7 3.4.1, step 3 */
	regs[STB6100_VCO] &= ~STB6100_VCO_OCK;		/* VCO fast search		*/
	rc = stb6100_ग_लिखो_reg(state, STB6100_VCO, regs[STB6100_VCO]);
	अगर (rc < 0)
		वापस rc;

	msleep(10);  /*  This is dangerous as another (related) thपढ़ो may start */ /* रुको क्रम LO to lock */

	regs[STB6100_VCO] &= ~STB6100_VCO_OSCH;		/* vco search disabled		*/
	regs[STB6100_VCO] |= STB6100_VCO_OCK;		/* search घड़ी off		*/
	rc = stb6100_ग_लिखो_reg(state, STB6100_VCO, regs[STB6100_VCO]);
	अगर (rc < 0)
		वापस rc;

	rc = stb6100_ग_लिखो_reg(state, STB6100_FCCK, 0x0d);
	अगर (rc < 0)
		वापस rc;  /* Stop LPF calibration */

	msleep(10);  /*  This is dangerous as another (related) thपढ़ो may start */
		     /* रुको क्रम stabilisation, (should not be necessary)		*/
	वापस 0;
पूर्ण

अटल पूर्णांक stb6100_sleep(काष्ठा dvb_frontend *fe)
अणु
	/* TODO: घातer करोwn	*/
	वापस 0;
पूर्ण

अटल पूर्णांक stb6100_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stb6100_state *state = fe->tuner_priv;
	पूर्णांक refclk = 27000000; /* Hz */

	/*
	 * iqsense = 1
	 * tunerstep = 125000
	 */
	state->bandwidth        = 36000000;		/* Hz	*/
	state->reference	= refclk / 1000;	/* kHz	*/

	/* Set शेष bandwidth. Modअगरied, PN 13-May-10	*/
	वापस 0;
पूर्ण

अटल पूर्णांक stb6100_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->frequency > 0)
		stb6100_set_frequency(fe, c->frequency);

	अगर (c->bandwidth_hz > 0)
		stb6100_set_bandwidth(fe, c->bandwidth_hz);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops stb6100_ops = अणु
	.info = अणु
		.name			= "STB6100 Silicon Tuner",
		.frequency_min_hz	=  950 * MHz,
		.frequency_max_hz	= 2150 * MHz,
	पूर्ण,

	.init		= stb6100_init,
	.sleep          = stb6100_sleep,
	.get_status	= stb6100_get_status,
	.set_params	= stb6100_set_params,
	.get_frequency  = stb6100_get_frequency,
	.get_bandwidth  = stb6100_get_bandwidth,
	.release	= stb6100_release
पूर्ण;

काष्ठा dvb_frontend *stb6100_attach(काष्ठा dvb_frontend *fe,
				    स्थिर काष्ठा stb6100_config *config,
				    काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा stb6100_state *state = शून्य;

	state = kzalloc(माप (काष्ठा stb6100_state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	state->config		= config;
	state->i2c		= i2c;
	state->frontend		= fe;
	state->reference	= config->refघड़ी / 1000; /* kHz */
	fe->tuner_priv		= state;
	fe->ops.tuner_ops	= stb6100_ops;

	prपूर्णांकk("%s: Attaching STB6100 \n", __func__);
	वापस fe;
पूर्ण

अटल व्योम stb6100_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stb6100_state *state = fe->tuner_priv;

	fe->tuner_priv = शून्य;
	kमुक्त(state);
पूर्ण

EXPORT_SYMBOL(stb6100_attach);
MODULE_PARM_DESC(verbose, "Set Verbosity level");

MODULE_AUTHOR("Manu Abraham");
MODULE_DESCRIPTION("STB6100 Silicon tuner");
MODULE_LICENSE("GPL");
