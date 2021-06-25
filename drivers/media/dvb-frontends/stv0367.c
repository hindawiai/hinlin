<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * stv0367.c
 *
 * Driver क्रम ST STV0367 DVB-T & DVB-C demodulator IC.
 *
 * Copyright (C) ST Microelectronics.
 * Copyright (C) 2010,2011 NetUP Inc.
 * Copyright (C) 2010,2011 Igor M. Liplianin <liplianin@netup.ru>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>

#समावेश <media/dvb_गणित.स>

#समावेश "stv0367.h"
#समावेश "stv0367_defs.h"
#समावेश "stv0367_regs.h"
#समावेश "stv0367_priv.h"

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  64

अटल पूर्णांक stvdebug;
module_param_named(debug, stvdebug, पूर्णांक, 0644);

अटल पूर्णांक i2cdebug;
module_param_named(i2c_debug, i2cdebug, पूर्णांक, 0644);

#घोषणा dprपूर्णांकk(args...) \
	करो अणु \
		अगर (stvdebug) \
			prपूर्णांकk(KERN_DEBUG args); \
	पूर्ण जबतक (0)
	/* DVB-C */

क्रमागत active_demod_state अणु demod_none, demod_ter, demod_cab पूर्ण;

काष्ठा stv0367cab_state अणु
	क्रमागत stv0367_cab_संकेत_type	state;
	u32	mclk;
	u32	adc_clk;
	s32	search_range;
	s32	derot_offset;
	/* results */
	पूर्णांक locked;			/* channel found		*/
	u32 freq_khz;			/* found frequency (in kHz)	*/
	u32 symbol_rate;		/* found symbol rate (in Bds)	*/
	क्रमागत fe_spectral_inversion spect_inv; /* Spectrum Inversion	*/
	u32 qamfec_status_reg;          /* status reg to poll क्रम FEC Lock */
पूर्ण;

काष्ठा stv0367ter_state अणु
	/* DVB-T */
	क्रमागत stv0367_ter_संकेत_type state;
	क्रमागत stv0367_ter_अगर_iq_mode अगर_iq_mode;
	क्रमागत stv0367_ter_mode mode;/* mode 2K or 8K */
	क्रमागत fe_guard_पूर्णांकerval guard;
	क्रमागत stv0367_ter_hierarchy hierarchy;
	u32 frequency;
	क्रमागत fe_spectral_inversion sense; /*  current search spectrum */
	u8  क्रमce; /* क्रमce mode/guard */
	u8  bw; /* channel width 6, 7 or 8 in MHz */
	u8  pBW; /* channel width used during previous lock */
	u32 pBER;
	u32 pPER;
	u32 ucblocks;
	s8  echo_pos; /* echo position */
	u8  first_lock;
	u8  unlock_counter;
	u32 agc_val;
पूर्ण;

काष्ठा stv0367_state अणु
	काष्ठा dvb_frontend fe;
	काष्ठा i2c_adapter *i2c;
	/* config settings */
	स्थिर काष्ठा stv0367_config *config;
	u8 chip_id;
	/* DVB-C */
	काष्ठा stv0367cab_state *cab_state;
	/* DVB-T */
	काष्ठा stv0367ter_state *ter_state;
	/* flags क्रम operation control */
	u8 use_i2c_gatectrl;
	u8 deftअसल;
	u8 reinit_on_setfrontend;
	u8 स्वतः_अगर_khz;
	क्रमागत active_demod_state activedemod;
पूर्ण;

#घोषणा RF_LOOKUP_TABLE_SIZE  31
#घोषणा RF_LOOKUP_TABLE2_SIZE 16
/* RF Level (क्रम RF AGC->AGC1) Lookup Table, depends on the board and tuner.*/
अटल स्थिर s32 stv0367cab_RF_LookUp1[RF_LOOKUP_TABLE_SIZE][RF_LOOKUP_TABLE_SIZE] = अणु
	अणु/*AGC1*/
		48, 50, 51, 53, 54, 56, 57, 58, 60, 61, 62, 63,
		64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
		76, 77, 78, 80, 83, 85, 88,
	पूर्ण, अणु/*RF(dbm)*/
		22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
		34, 35, 36, 37, 38, 39, 41, 42, 43, 44, 46, 47,
		49, 50, 52, 53, 54, 55, 56,
	पूर्ण
पूर्ण;
/* RF Level (क्रम IF AGC->AGC2) Lookup Table, depends on the board and tuner.*/
अटल स्थिर s32 stv0367cab_RF_LookUp2[RF_LOOKUP_TABLE2_SIZE][RF_LOOKUP_TABLE2_SIZE] = अणु
	अणु/*AGC2*/
		28, 29, 31, 32, 34, 35, 36, 37,
		38, 39, 40, 41, 42, 43, 44, 45,
	पूर्ण, अणु/*RF(dbm)*/
		57, 58, 59, 60, 61, 62, 63, 64,
		65, 66, 67, 68, 69, 70, 71, 72,
	पूर्ण
पूर्ण;

अटल
पूर्णांक stv0367_ग_लिखोregs(काष्ठा stv0367_state *state, u16 reg, u8 *data, पूर्णांक len)
अणु
	u8 buf[MAX_XFER_SIZE];
	काष्ठा i2c_msg msg = अणु
		.addr = state->config->demod_address,
		.flags = 0,
		.buf = buf,
		.len = len + 2
	पूर्ण;
	पूर्णांक ret;

	अगर (2 + len > माप(buf)) अणु
		prपूर्णांकk(KERN_WARNING
		       "%s: i2c wr reg=%04x: len=%d is too big!\n",
		       KBUILD_MODNAME, reg, len);
		वापस -EINVAL;
	पूर्ण


	buf[0] = MSB(reg);
	buf[1] = LSB(reg);
	स_नकल(buf + 2, data, len);

	अगर (i2cdebug)
		prपूर्णांकk(KERN_DEBUG "%s: [%02x] %02x: %02x\n", __func__,
			state->config->demod_address, reg, buf[2]);

	ret = i2c_transfer(state->i2c, &msg, 1);
	अगर (ret != 1)
		prपूर्णांकk(KERN_ERR "%s: i2c write error! ([%02x] %02x: %02x)\n",
			__func__, state->config->demod_address, reg, buf[2]);

	वापस (ret != 1) ? -EREMOTEIO : 0;
पूर्ण

अटल पूर्णांक stv0367_ग_लिखोreg(काष्ठा stv0367_state *state, u16 reg, u8 data)
अणु
	u8 पंचांगp = data; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	वापस stv0367_ग_लिखोregs(state, reg, &पंचांगp, 1);
पूर्ण

अटल u8 stv0367_पढ़ोreg(काष्ठा stv0367_state *state, u16 reg)
अणु
	u8 b0[] = अणु 0, 0 पूर्ण;
	u8 b1[] = अणु 0 पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = state->config->demod_address,
			.flags = 0,
			.buf = b0,
			.len = 2
		पूर्ण, अणु
			.addr = state->config->demod_address,
			.flags = I2C_M_RD,
			.buf = b1,
			.len = 1
		पूर्ण
	पूर्ण;
	पूर्णांक ret;

	b0[0] = MSB(reg);
	b0[1] = LSB(reg);

	ret = i2c_transfer(state->i2c, msg, 2);
	अगर (ret != 2)
		prपूर्णांकk(KERN_ERR "%s: i2c read error ([%02x] %02x: %02x)\n",
			__func__, state->config->demod_address, reg, b1[0]);

	अगर (i2cdebug)
		prपूर्णांकk(KERN_DEBUG "%s: [%02x] %02x: %02x\n", __func__,
			state->config->demod_address, reg, b1[0]);

	वापस b1[0];
पूर्ण

अटल व्योम extract_mask_pos(u32 label, u8 *mask, u8 *pos)
अणु
	u8 position = 0, i = 0;

	(*mask) = label & 0xff;

	जबतक ((position == 0) && (i < 8)) अणु
		position = ((*mask) >> i) & 0x01;
		i++;
	पूर्ण

	(*pos) = (i - 1);
पूर्ण

अटल व्योम stv0367_ग_लिखोbits(काष्ठा stv0367_state *state, u32 label, u8 val)
अणु
	u8 reg, mask, pos;

	reg = stv0367_पढ़ोreg(state, (label >> 16) & 0xffff);
	extract_mask_pos(label, &mask, &pos);

	val = mask & (val << pos);

	reg = (reg & (~mask)) | val;
	stv0367_ग_लिखोreg(state, (label >> 16) & 0xffff, reg);

पूर्ण

अटल व्योम stv0367_setbits(u8 *reg, u32 label, u8 val)
अणु
	u8 mask, pos;

	extract_mask_pos(label, &mask, &pos);

	val = mask & (val << pos);

	(*reg) = ((*reg) & (~mask)) | val;
पूर्ण

अटल u8 stv0367_पढ़ोbits(काष्ठा stv0367_state *state, u32 label)
अणु
	u8 val = 0xff;
	u8 mask, pos;

	extract_mask_pos(label, &mask, &pos);

	val = stv0367_पढ़ोreg(state, label >> 16);
	val = (val & mask) >> pos;

	वापस val;
पूर्ण

#अगर 0 /* Currently, unused */
अटल u8 stv0367_getbits(u8 reg, u32 label)
अणु
	u8 mask, pos;

	extract_mask_pos(label, &mask, &pos);

	वापस (reg & mask) >> pos;
पूर्ण
#पूर्ण_अगर

अटल व्योम stv0367_ग_लिखो_table(काष्ठा stv0367_state *state,
				स्थिर काष्ठा st_रेजिस्टर *deftab)
अणु
	पूर्णांक i = 0;

	जबतक (1) अणु
		अगर (!deftab[i].addr)
			अवरोध;
		stv0367_ग_लिखोreg(state, deftab[i].addr, deftab[i].value);
		i++;
	पूर्ण
पूर्ण

अटल व्योम stv0367_pll_setup(काष्ठा stv0367_state *state,
				u32 icspeed, u32 xtal)
अणु
	/* note on regs: R367TER_* and R367CAB_* defines each poपूर्णांक to
	 * 0xf0d8, so just use R367TER_ क्रम both हालs
	 */

	चयन (icspeed) अणु
	हाल STV0367_ICSPEED_58000:
		चयन (xtal) अणु
		शेष:
		हाल 27000000:
			dprपूर्णांकk("STV0367 SetCLKgen for 58MHz IC and 27Mhz crystal\n");
			/* PLLMDIV: 27, PLLNDIV: 232 */
			stv0367_ग_लिखोreg(state, R367TER_PLLMDIV, 0x1b);
			stv0367_ग_लिखोreg(state, R367TER_PLLNDIV, 0xe8);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
	हाल STV0367_ICSPEED_53125:
		चयन (xtal) अणु
			/* set पूर्णांकernal freq to 53.125MHz */
		हाल 16000000:
			stv0367_ग_लिखोreg(state, R367TER_PLLMDIV, 0x2);
			stv0367_ग_लिखोreg(state, R367TER_PLLNDIV, 0x1b);
			अवरोध;
		हाल 25000000:
			stv0367_ग_लिखोreg(state, R367TER_PLLMDIV, 0xa);
			stv0367_ग_लिखोreg(state, R367TER_PLLNDIV, 0x55);
			अवरोध;
		शेष:
		हाल 27000000:
			dprपूर्णांकk("FE_STV0367TER_SetCLKgen for 27Mhz\n");
			stv0367_ग_लिखोreg(state, R367TER_PLLMDIV, 0x1);
			stv0367_ग_लिखोreg(state, R367TER_PLLNDIV, 0x8);
			अवरोध;
		हाल 30000000:
			stv0367_ग_लिखोreg(state, R367TER_PLLMDIV, 0xc);
			stv0367_ग_लिखोreg(state, R367TER_PLLNDIV, 0x55);
			अवरोध;
		पूर्ण
	पूर्ण

	stv0367_ग_लिखोreg(state, R367TER_PLLSETUP, 0x18);
पूर्ण

अटल पूर्णांक stv0367_get_अगर_khz(काष्ठा stv0367_state *state, u32 *अगरkhz)
अणु
	अगर (state->स्वतः_अगर_khz && state->fe.ops.tuner_ops.get_अगर_frequency) अणु
		state->fe.ops.tuner_ops.get_अगर_frequency(&state->fe, अगरkhz);
		*अगरkhz = *अगरkhz / 1000; /* hz -> khz */
	पूर्ण अन्यथा
		*अगरkhz = state->config->अगर_khz;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367ter_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	u8 पंचांगp = stv0367_पढ़ोreg(state, R367TER_I2CRPT);

	dprपूर्णांकk("%s:\n", __func__);

	अगर (enable) अणु
		stv0367_setbits(&पंचांगp, F367TER_STOP_ENABLE, 0);
		stv0367_setbits(&पंचांगp, F367TER_I2CT_ON, 1);
	पूर्ण अन्यथा अणु
		stv0367_setbits(&पंचांगp, F367TER_STOP_ENABLE, 1);
		stv0367_setbits(&पंचांगp, F367TER_I2CT_ON, 0);
	पूर्ण

	stv0367_ग_लिखोreg(state, R367TER_I2CRPT, पंचांगp);

	वापस 0;
पूर्ण

अटल u32 stv0367_get_tuner_freq(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_ops	*frontend_ops = &fe->ops;
	काष्ठा dvb_tuner_ops	*tuner_ops = &frontend_ops->tuner_ops;
	u32 freq = 0;
	पूर्णांक err = 0;

	dprपूर्णांकk("%s:\n", __func__);

	अगर (tuner_ops->get_frequency) अणु
		err = tuner_ops->get_frequency(fe, &freq);
		अगर (err < 0) अणु
			prपूर्णांकk(KERN_ERR "%s: Invalid parameter\n", __func__);
			वापस err;
		पूर्ण

		dprपूर्णांकk("%s: frequency=%d\n", __func__, freq);

	पूर्ण अन्यथा
		वापस -1;

	वापस freq;
पूर्ण

अटल u16 CellsCoeffs_8MHz_367cofdm[3][6][5] = अणु
	अणु
		अणु0x10EF, 0xE205, 0x10EF, 0xCE49, 0x6DA7पूर्ण, /* CELL 1 COEFFS 27M*/
		अणु0x2151, 0xc557, 0x2151, 0xc705, 0x6f93पूर्ण, /* CELL 2 COEFFS */
		अणु0x2503, 0xc000, 0x2503, 0xc375, 0x7194पूर्ण, /* CELL 3 COEFFS */
		अणु0x20E9, 0xca94, 0x20e9, 0xc153, 0x7194पूर्ण, /* CELL 4 COEFFS */
		अणु0x06EF, 0xF852, 0x06EF, 0xC057, 0x7207पूर्ण, /* CELL 5 COEFFS */
		अणु0x0000, 0x0ECC, 0x0ECC, 0x0000, 0x3647पूर्ण /* CELL 6 COEFFS */
	पूर्ण, अणु
		अणु0x10A0, 0xE2AF, 0x10A1, 0xCE76, 0x6D6Dपूर्ण, /* CELL 1 COEFFS 25M*/
		अणु0x20DC, 0xC676, 0x20D9, 0xC80A, 0x6F29पूर्ण,
		अणु0x2532, 0xC000, 0x251D, 0xC391, 0x706Fपूर्ण,
		अणु0x1F7A, 0xCD2B, 0x2032, 0xC15E, 0x711Fपूर्ण,
		अणु0x0698, 0xFA5E, 0x0568, 0xC059, 0x7193पूर्ण,
		अणु0x0000, 0x0918, 0x149C, 0x0000, 0x3642पूर्ण /* CELL 6 COEFFS */
	पूर्ण, अणु
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण, /* 30M */
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण
	पूर्ण
पूर्ण;

अटल u16 CellsCoeffs_7MHz_367cofdm[3][6][5] = अणु
	अणु
		अणु0x12CA, 0xDDAF, 0x12CA, 0xCCEB, 0x6FB1पूर्ण, /* CELL 1 COEFFS 27M*/
		अणु0x2329, 0xC000, 0x2329, 0xC6B0, 0x725Fपूर्ण, /* CELL 2 COEFFS */
		अणु0x2394, 0xC000, 0x2394, 0xC2C7, 0x7410पूर्ण, /* CELL 3 COEFFS */
		अणु0x251C, 0xC000, 0x251C, 0xC103, 0x74D9पूर्ण, /* CELL 4 COEFFS */
		अणु0x0804, 0xF546, 0x0804, 0xC040, 0x7544पूर्ण, /* CELL 5 COEFFS */
		अणु0x0000, 0x0CD9, 0x0CD9, 0x0000, 0x370Aपूर्ण /* CELL 6 COEFFS */
	पूर्ण, अणु
		अणु0x1285, 0xDE47, 0x1285, 0xCD17, 0x6F76पूर्ण, /*25M*/
		अणु0x234C, 0xC000, 0x2348, 0xC6DA, 0x7206पूर्ण,
		अणु0x23B4, 0xC000, 0x23AC, 0xC2DB, 0x73B3पूर्ण,
		अणु0x253D, 0xC000, 0x25B6, 0xC10B, 0x747Fपूर्ण,
		अणु0x0721, 0xF79C, 0x065F, 0xC041, 0x74EBपूर्ण,
		अणु0x0000, 0x08FA, 0x1162, 0x0000, 0x36FFपूर्ण
	पूर्ण, अणु
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण, /* 30M */
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण
	पूर्ण
पूर्ण;

अटल u16 CellsCoeffs_6MHz_367cofdm[3][6][5] = अणु
	अणु
		अणु0x1699, 0xD5B8, 0x1699, 0xCBC3, 0x713Bपूर्ण, /* CELL 1 COEFFS 27M*/
		अणु0x2245, 0xC000, 0x2245, 0xC568, 0x74D5पूर्ण, /* CELL 2 COEFFS */
		अणु0x227F, 0xC000, 0x227F, 0xC1FC, 0x76C6पूर्ण, /* CELL 3 COEFFS */
		अणु0x235E, 0xC000, 0x235E, 0xC0A7, 0x778Aपूर्ण, /* CELL 4 COEFFS */
		अणु0x0ECB, 0xEA0B, 0x0ECB, 0xC027, 0x77DDपूर्ण, /* CELL 5 COEFFS */
		अणु0x0000, 0x0B68, 0x0B68, 0x0000, 0xC89Aपूर्ण, /* CELL 6 COEFFS */
	पूर्ण, अणु
		अणु0x1655, 0xD64E, 0x1658, 0xCBEF, 0x70FEपूर्ण, /*25M*/
		अणु0x225E, 0xC000, 0x2256, 0xC589, 0x7489पूर्ण,
		अणु0x2293, 0xC000, 0x2295, 0xC209, 0x767Eपूर्ण,
		अणु0x2377, 0xC000, 0x23AA, 0xC0AB, 0x7746पूर्ण,
		अणु0x0DC7, 0xEBC8, 0x0D07, 0xC027, 0x7799पूर्ण,
		अणु0x0000, 0x0888, 0x0E9C, 0x0000, 0x3757पूर्ण

	पूर्ण, अणु
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण, /* 30M */
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण,
		अणु0x0000, 0x0000, 0x0000, 0x0000, 0x0000पूर्ण
	पूर्ण
पूर्ण;

अटल u32 stv0367ter_get_mclk(काष्ठा stv0367_state *state, u32 ExtClk_Hz)
अणु
	u32 mclk_Hz = 0; /* master घड़ी frequency (Hz) */
	u32 m, n, p;

	dprपूर्णांकk("%s:\n", __func__);

	अगर (stv0367_पढ़ोbits(state, F367TER_BYPASS_PLLXN) == 0) अणु
		n = (u32)stv0367_पढ़ोbits(state, F367TER_PLL_NDIV);
		अगर (n == 0)
			n = n + 1;

		m = (u32)stv0367_पढ़ोbits(state, F367TER_PLL_MDIV);
		अगर (m == 0)
			m = m + 1;

		p = (u32)stv0367_पढ़ोbits(state, F367TER_PLL_PDIV);
		अगर (p > 5)
			p = 5;

		mclk_Hz = ((ExtClk_Hz / 2) * n) / (m * (1 << p));

		dprपूर्णांकk("N=%d M=%d P=%d mclk_Hz=%d ExtClk_Hz=%d\n",
				n, m, p, mclk_Hz, ExtClk_Hz);
	पूर्ण अन्यथा
		mclk_Hz = ExtClk_Hz;

	dprपूर्णांकk("%s: mclk_Hz=%d\n", __func__, mclk_Hz);

	वापस mclk_Hz;
पूर्ण

अटल पूर्णांक stv0367ter_filt_coeff_init(काष्ठा stv0367_state *state,
				u16 CellsCoeffs[3][6][5], u32 DemodXtal)
अणु
	पूर्णांक i, j, k, freq;

	dprपूर्णांकk("%s:\n", __func__);

	freq = stv0367ter_get_mclk(state, DemodXtal);

	अगर (freq == 53125000)
		k = 1; /* equivalent to Xtal 25M on 362*/
	अन्यथा अगर (freq == 54000000)
		k = 0; /* equivalent to Xtal 27M on 362*/
	अन्यथा अगर (freq == 52500000)
		k = 2; /* equivalent to Xtal 30M on 362*/
	अन्यथा
		वापस 0;

	क्रम (i = 1; i <= 6; i++) अणु
		stv0367_ग_लिखोbits(state, F367TER_IIR_CELL_NB, i - 1);

		क्रम (j = 1; j <= 5; j++) अणु
			stv0367_ग_लिखोreg(state,
				(R367TER_IIRCX_COEFF1_MSB + 2 * (j - 1)),
				MSB(CellsCoeffs[k][i-1][j-1]));
			stv0367_ग_लिखोreg(state,
				(R367TER_IIRCX_COEFF1_LSB + 2 * (j - 1)),
				LSB(CellsCoeffs[k][i-1][j-1]));
		पूर्ण
	पूर्ण

	वापस 1;

पूर्ण

अटल व्योम stv0367ter_agc_iir_lock_detect_set(काष्ठा stv0367_state *state)
अणु
	dprपूर्णांकk("%s:\n", __func__);

	stv0367_ग_लिखोbits(state, F367TER_LOCK_DETECT_LSB, 0x00);

	/* Lock detect 1 */
	stv0367_ग_लिखोbits(state, F367TER_LOCK_DETECT_CHOICE, 0x00);
	stv0367_ग_लिखोbits(state, F367TER_LOCK_DETECT_MSB, 0x06);
	stv0367_ग_लिखोbits(state, F367TER_AUT_AGC_TARGET_LSB, 0x04);

	/* Lock detect 2 */
	stv0367_ग_लिखोbits(state, F367TER_LOCK_DETECT_CHOICE, 0x01);
	stv0367_ग_लिखोbits(state, F367TER_LOCK_DETECT_MSB, 0x06);
	stv0367_ग_लिखोbits(state, F367TER_AUT_AGC_TARGET_LSB, 0x04);

	/* Lock detect 3 */
	stv0367_ग_लिखोbits(state, F367TER_LOCK_DETECT_CHOICE, 0x02);
	stv0367_ग_लिखोbits(state, F367TER_LOCK_DETECT_MSB, 0x01);
	stv0367_ग_लिखोbits(state, F367TER_AUT_AGC_TARGET_LSB, 0x00);

	/* Lock detect 4 */
	stv0367_ग_लिखोbits(state, F367TER_LOCK_DETECT_CHOICE, 0x03);
	stv0367_ग_लिखोbits(state, F367TER_LOCK_DETECT_MSB, 0x01);
	stv0367_ग_लिखोbits(state, F367TER_AUT_AGC_TARGET_LSB, 0x00);

पूर्ण

अटल पूर्णांक stv0367_iir_filt_init(काष्ठा stv0367_state *state, u8 Bandwidth,
							u32 DemodXtalValue)
अणु
	dprपूर्णांकk("%s:\n", __func__);

	stv0367_ग_लिखोbits(state, F367TER_NRST_IIR, 0);

	चयन (Bandwidth) अणु
	हाल 6:
		अगर (!stv0367ter_filt_coeff_init(state,
				CellsCoeffs_6MHz_367cofdm,
				DemodXtalValue))
			वापस 0;
		अवरोध;
	हाल 7:
		अगर (!stv0367ter_filt_coeff_init(state,
				CellsCoeffs_7MHz_367cofdm,
				DemodXtalValue))
			वापस 0;
		अवरोध;
	हाल 8:
		अगर (!stv0367ter_filt_coeff_init(state,
				CellsCoeffs_8MHz_367cofdm,
				DemodXtalValue))
			वापस 0;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	stv0367_ग_लिखोbits(state, F367TER_NRST_IIR, 1);

	वापस 1;
पूर्ण

अटल व्योम stv0367ter_agc_iir_rst(काष्ठा stv0367_state *state)
अणु

	u8 com_n;

	dprपूर्णांकk("%s:\n", __func__);

	com_n = stv0367_पढ़ोbits(state, F367TER_COM_N);

	stv0367_ग_लिखोbits(state, F367TER_COM_N, 0x07);

	stv0367_ग_लिखोbits(state, F367TER_COM_SOFT_RSTN, 0x00);
	stv0367_ग_लिखोbits(state, F367TER_COM_AGC_ON, 0x00);

	stv0367_ग_लिखोbits(state, F367TER_COM_SOFT_RSTN, 0x01);
	stv0367_ग_लिखोbits(state, F367TER_COM_AGC_ON, 0x01);

	stv0367_ग_लिखोbits(state, F367TER_COM_N, com_n);

पूर्ण

अटल पूर्णांक stv0367ter_duration(s32 mode, पूर्णांक tempo1, पूर्णांक tempo2, पूर्णांक tempo3)
अणु
	पूर्णांक local_tempo = 0;
	चयन (mode) अणु
	हाल 0:
		local_tempo = tempo1;
		अवरोध;
	हाल 1:
		local_tempo = tempo2;
		अवरोध ;

	हाल 2:
		local_tempo = tempo3;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	/*	msleep(local_tempo);  */
	वापस local_tempo;
पूर्ण

अटल क्रमागत
stv0367_ter_संकेत_type stv0367ter_check_syr(काष्ठा stv0367_state *state)
अणु
	पूर्णांक wd = 100;
	अचिन्हित लघु पूर्णांक SYR_var;
	s32 SYRStatus;

	dprपूर्णांकk("%s:\n", __func__);

	SYR_var = stv0367_पढ़ोbits(state, F367TER_SYR_LOCK);

	जबतक ((!SYR_var) && (wd > 0)) अणु
		usleep_range(2000, 3000);
		wd -= 2;
		SYR_var = stv0367_पढ़ोbits(state, F367TER_SYR_LOCK);
	पूर्ण

	अगर (!SYR_var)
		SYRStatus = FE_TER_NOSYMBOL;
	अन्यथा
		SYRStatus =  FE_TER_SYMBOLOK;

	dprपूर्णांकk("stv0367ter_check_syr SYRStatus %s\n",
				SYR_var == 0 ? "No Symbol" : "OK");

	वापस SYRStatus;
पूर्ण

अटल क्रमागत
stv0367_ter_संकेत_type stv0367ter_check_cpamp(काष्ठा stv0367_state *state,
								s32 FFTmode)
अणु

	s32  CPAMPvalue = 0, CPAMPStatus, CPAMPMin;
	पूर्णांक wd = 0;

	dprपूर्णांकk("%s:\n", __func__);

	चयन (FFTmode) अणु
	हाल 0: /*2k mode*/
		CPAMPMin = 20;
		wd = 10;
		अवरोध;
	हाल 1: /*8k mode*/
		CPAMPMin = 80;
		wd = 55;
		अवरोध;
	हाल 2: /*4k mode*/
		CPAMPMin = 40;
		wd = 30;
		अवरोध;
	शेष:
		CPAMPMin = 0xffff;  /*drives to NOCPAMP	*/
		अवरोध;
	पूर्ण

	dprपूर्णांकk("%s: CPAMPMin=%d wd=%d\n", __func__, CPAMPMin, wd);

	CPAMPvalue = stv0367_पढ़ोbits(state, F367TER_PPM_CPAMP_सूचीECT);
	जबतक ((CPAMPvalue < CPAMPMin) && (wd > 0)) अणु
		usleep_range(1000, 2000);
		wd -= 1;
		CPAMPvalue = stv0367_पढ़ोbits(state, F367TER_PPM_CPAMP_सूचीECT);
		/*dprपूर्णांकk("CPAMPvalue= %d at wd=%d\n",CPAMPvalue,wd); */
	पूर्ण
	dprपूर्णांकk("******last CPAMPvalue= %d at wd=%d\n", CPAMPvalue, wd);
	अगर (CPAMPvalue < CPAMPMin) अणु
		CPAMPStatus = FE_TER_NOCPAMP;
		dprपूर्णांकk("%s: CPAMP failed\n", __func__);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("%s: CPAMP OK !\n", __func__);
		CPAMPStatus = FE_TER_CPAMPOK;
	पूर्ण

	वापस CPAMPStatus;
पूर्ण

अटल क्रमागत stv0367_ter_संकेत_type
stv0367ter_lock_algo(काष्ठा stv0367_state *state)
अणु
	क्रमागत stv0367_ter_संकेत_type ret_flag;
	लघु पूर्णांक wd, tempo;
	u8 try, u_var1 = 0, u_var2 = 0, u_var3 = 0, u_var4 = 0, mode, guard;
	u8 पंचांगp, पंचांगp2;

	dprपूर्णांकk("%s:\n", __func__);

	अगर (state == शून्य)
		वापस FE_TER_SWNOK;

	try = 0;
	करो अणु
		ret_flag = FE_TER_LOCKOK;

		stv0367_ग_लिखोbits(state, F367TER_CORE_ACTIVE, 0);

		अगर (state->config->अगर_iq_mode != 0)
			stv0367_ग_लिखोbits(state, F367TER_COM_N, 0x07);

		stv0367_ग_लिखोbits(state, F367TER_GUARD, 3);/* suggest 2k 1/4 */
		stv0367_ग_लिखोbits(state, F367TER_MODE, 0);
		stv0367_ग_लिखोbits(state, F367TER_SYR_TR_DIS, 0);
		usleep_range(5000, 10000);

		stv0367_ग_लिखोbits(state, F367TER_CORE_ACTIVE, 1);


		अगर (stv0367ter_check_syr(state) == FE_TER_NOSYMBOL)
			वापस FE_TER_NOSYMBOL;
		अन्यथा अणु /*
			अगर chip locked on wrong mode first try,
			it must lock correctly second try */
			mode = stv0367_पढ़ोbits(state, F367TER_SYR_MODE);
			अगर (stv0367ter_check_cpamp(state, mode) ==
							FE_TER_NOCPAMP) अणु
				अगर (try == 0)
					ret_flag = FE_TER_NOCPAMP;

			पूर्ण
		पूर्ण

		try++;
	पूर्ण जबतक ((try < 10) && (ret_flag != FE_TER_LOCKOK));

	पंचांगp  = stv0367_पढ़ोreg(state, R367TER_SYR_STAT);
	पंचांगp2 = stv0367_पढ़ोreg(state, R367TER_STATUS);
	dprपूर्णांकk("state=%p\n", state);
	dprपूर्णांकk("LOCK OK! mode=%d SYR_STAT=0x%x R367TER_STATUS=0x%x\n",
							mode, पंचांगp, पंचांगp2);

	पंचांगp  = stv0367_पढ़ोreg(state, R367TER_PRVIT);
	पंचांगp2 = stv0367_पढ़ोreg(state, R367TER_I2CRPT);
	dprपूर्णांकk("PRVIT=0x%x I2CRPT=0x%x\n", पंचांगp, पंचांगp2);

	पंचांगp  = stv0367_पढ़ोreg(state, R367TER_GAIN_SRC1);
	dprपूर्णांकk("GAIN_SRC1=0x%x\n", पंचांगp);

	अगर ((mode != 0) && (mode != 1) && (mode != 2))
		वापस FE_TER_SWNOK;

	/*guard=stv0367_पढ़ोbits(state,F367TER_SYR_GUARD); */

	/*suppress EPQ स्वतः क्रम SYR_GARD 1/16 or 1/32
	and set channel predictor in स्वतःmatic */
#अगर 0
	चयन (guard) अणु

	हाल 0:
	हाल 1:
		stv0367_ग_लिखोbits(state, F367TER_AUTO_LE_EN, 0);
		stv0367_ग_लिखोreg(state, R367TER_CHC_CTL, 0x01);
		अवरोध;
	हाल 2:
	हाल 3:
		stv0367_ग_लिखोbits(state, F367TER_AUTO_LE_EN, 1);
		stv0367_ग_लिखोreg(state, R367TER_CHC_CTL, 0x11);
		अवरोध;

	शेष:
		वापस FE_TER_SWNOK;
	पूर्ण
#पूर्ण_अगर

	/*reset fec an reedsolo FOR 367 only*/
	stv0367_ग_लिखोbits(state, F367TER_RST_SFEC, 1);
	stv0367_ग_लिखोbits(state, F367TER_RST_REEDSOLO, 1);
	usleep_range(1000, 2000);
	stv0367_ग_लिखोbits(state, F367TER_RST_SFEC, 0);
	stv0367_ग_लिखोbits(state, F367TER_RST_REEDSOLO, 0);

	u_var1 = stv0367_पढ़ोbits(state, F367TER_LK);
	u_var2 = stv0367_पढ़ोbits(state, F367TER_PRF);
	u_var3 = stv0367_पढ़ोbits(state, F367TER_TPS_LOCK);
	/*	u_var4=stv0367_पढ़ोbits(state,F367TER_TSFIFO_LINEOK); */

	wd = stv0367ter_duration(mode, 125, 500, 250);
	tempo = stv0367ter_duration(mode, 4, 16, 8);

	/*जबतक ( ((!u_var1)||(!u_var2)||(!u_var3)||(!u_var4))  && (wd>=0)) */
	जबतक (((!u_var1) || (!u_var2) || (!u_var3)) && (wd >= 0)) अणु
		usleep_range(1000 * tempo, 1000 * (tempo + 1));
		wd -= tempo;
		u_var1 = stv0367_पढ़ोbits(state, F367TER_LK);
		u_var2 = stv0367_पढ़ोbits(state, F367TER_PRF);
		u_var3 = stv0367_पढ़ोbits(state, F367TER_TPS_LOCK);
		/*u_var4=stv0367_पढ़ोbits(state, F367TER_TSFIFO_LINEOK); */
	पूर्ण

	अगर (!u_var1)
		वापस FE_TER_NOLOCK;


	अगर (!u_var2)
		वापस FE_TER_NOPRFOUND;

	अगर (!u_var3)
		वापस FE_TER_NOTPS;

	guard = stv0367_पढ़ोbits(state, F367TER_SYR_GUARD);
	stv0367_ग_लिखोreg(state, R367TER_CHC_CTL, 0x11);
	चयन (guard) अणु
	हाल 0:
	हाल 1:
		stv0367_ग_लिखोbits(state, F367TER_AUTO_LE_EN, 0);
		/*stv0367_ग_लिखोreg(state,R367TER_CHC_CTL, 0x1);*/
		stv0367_ग_लिखोbits(state, F367TER_SYR_FILTER, 0);
		अवरोध;
	हाल 2:
	हाल 3:
		stv0367_ग_लिखोbits(state, F367TER_AUTO_LE_EN, 1);
		/*stv0367_ग_लिखोreg(state,R367TER_CHC_CTL, 0x11);*/
		stv0367_ग_लिखोbits(state, F367TER_SYR_FILTER, 1);
		अवरोध;

	शेष:
		वापस FE_TER_SWNOK;
	पूर्ण

	/* apply Sfec workaround अगर 8K 64QAM CR!=1/2*/
	अगर ((stv0367_पढ़ोbits(state, F367TER_TPS_CONST) == 2) &&
			(mode == 1) &&
			(stv0367_पढ़ोbits(state, F367TER_TPS_HPCODE) != 0)) अणु
		stv0367_ग_लिखोreg(state, R367TER_SFDLYSETH, 0xc0);
		stv0367_ग_लिखोreg(state, R367TER_SFDLYSETM, 0x60);
		stv0367_ग_लिखोreg(state, R367TER_SFDLYSETL, 0x0);
	पूर्ण अन्यथा
		stv0367_ग_लिखोreg(state, R367TER_SFDLYSETH, 0x0);

	wd = stv0367ter_duration(mode, 125, 500, 250);
	u_var4 = stv0367_पढ़ोbits(state, F367TER_TSFIFO_LINEOK);

	जबतक ((!u_var4) && (wd >= 0)) अणु
		usleep_range(1000 * tempo, 1000 * (tempo + 1));
		wd -= tempo;
		u_var4 = stv0367_पढ़ोbits(state, F367TER_TSFIFO_LINEOK);
	पूर्ण

	अगर (!u_var4)
		वापस FE_TER_NOLOCK;

	/* क्रम 367 leave COM_N at 0x7 क्रम IQ_mode*/
	/*अगर(ter_state->अगर_iq_mode!=FE_TER_NORMAL_IF_TUNER) अणु
		tempo=0;
		जबतक ((stv0367_पढ़ोbits(state,F367TER_COM_USEGAINTRK)!=1) &&
		(stv0367_पढ़ोbits(state,F367TER_COM_AGCLOCK)!=1)&&(tempo<100)) अणु
			ChipWaitOrAbort(state,1);
			tempo+=1;
		पूर्ण

		stv0367_ग_लिखोbits(state,F367TER_COM_N,0x17);
	पूर्ण */

	stv0367_ग_लिखोbits(state, F367TER_SYR_TR_DIS, 1);

	dprपूर्णांकk("FE_TER_LOCKOK !!!\n");

	वापस	FE_TER_LOCKOK;

पूर्ण

अटल व्योम stv0367ter_set_ts_mode(काष्ठा stv0367_state *state,
					क्रमागत stv0367_ts_mode PathTS)
अणु

	dprपूर्णांकk("%s:\n", __func__);

	अगर (state == शून्य)
		वापस;

	stv0367_ग_लिखोbits(state, F367TER_TS_DIS, 0);
	चयन (PathTS) अणु
	शेष:
		/*क्रम removing warning :शेष we can assume in parallel mode*/
	हाल STV0367_PARALLEL_PUNCT_CLOCK:
		stv0367_ग_लिखोbits(state, F367TER_TSFIFO_SERIAL, 0);
		stv0367_ग_लिखोbits(state, F367TER_TSFIFO_DVBCI, 0);
		अवरोध;
	हाल STV0367_SERIAL_PUNCT_CLOCK:
		stv0367_ग_लिखोbits(state, F367TER_TSFIFO_SERIAL, 1);
		stv0367_ग_लिखोbits(state, F367TER_TSFIFO_DVBCI, 1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम stv0367ter_set_clk_pol(काष्ठा stv0367_state *state,
					क्रमागत stv0367_clk_pol घड़ी)
अणु

	dprपूर्णांकk("%s:\n", __func__);

	अगर (state == शून्य)
		वापस;

	चयन (घड़ी) अणु
	हाल STV0367_RISINGEDGE_CLOCK:
		stv0367_ग_लिखोbits(state, F367TER_TS_BYTE_CLK_INV, 1);
		अवरोध;
	हाल STV0367_FALLINGEDGE_CLOCK:
		stv0367_ग_लिखोbits(state, F367TER_TS_BYTE_CLK_INV, 0);
		अवरोध;
		/*हाल FE_TER_CLOCK_POLARITY_DEFAULT:*/
	शेष:
		stv0367_ग_लिखोbits(state, F367TER_TS_BYTE_CLK_INV, 0);
		अवरोध;
	पूर्ण
पूर्ण

#अगर 0
अटल व्योम stv0367ter_core_sw(काष्ठा stv0367_state *state)
अणु

	dprपूर्णांकk("%s:\n", __func__);

	stv0367_ग_लिखोbits(state, F367TER_CORE_ACTIVE, 0);
	stv0367_ग_लिखोbits(state, F367TER_CORE_ACTIVE, 1);
	msleep(350);
पूर्ण
#पूर्ण_अगर
अटल पूर्णांक stv0367ter_standby(काष्ठा dvb_frontend *fe, u8 standby_on)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s:\n", __func__);

	अगर (standby_on) अणु
		stv0367_ग_लिखोbits(state, F367TER_STDBY, 1);
		stv0367_ग_लिखोbits(state, F367TER_STDBY_FEC, 1);
		stv0367_ग_लिखोbits(state, F367TER_STDBY_CORE, 1);
	पूर्ण अन्यथा अणु
		stv0367_ग_लिखोbits(state, F367TER_STDBY, 0);
		stv0367_ग_लिखोbits(state, F367TER_STDBY_FEC, 0);
		stv0367_ग_लिखोbits(state, F367TER_STDBY_CORE, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367ter_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस stv0367ter_standby(fe, 1);
पूर्ण

अटल पूर्णांक stv0367ter_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा stv0367ter_state *ter_state = state->ter_state;

	dprपूर्णांकk("%s:\n", __func__);

	ter_state->pBER = 0;

	stv0367_ग_लिखो_table(state,
		stv0367_deftअसल[state->deftअसल][STV0367_TAB_TER]);

	stv0367_pll_setup(state, STV0367_ICSPEED_53125, state->config->xtal);

	stv0367_ग_लिखोreg(state, R367TER_I2CRPT, 0xa0);
	stv0367_ग_लिखोreg(state, R367TER_ANACTRL, 0x00);

	/*Set TS1 and TS2 to serial or parallel mode */
	stv0367ter_set_ts_mode(state, state->config->ts_mode);
	stv0367ter_set_clk_pol(state, state->config->clk_pol);

	state->chip_id = stv0367_पढ़ोreg(state, R367TER_ID);
	ter_state->first_lock = 0;
	ter_state->unlock_counter = 2;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367ter_algo(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा stv0367ter_state *ter_state = state->ter_state;
	पूर्णांक offset = 0, tempo = 0;
	u8 u_var;
	u8 /*स्थिरell,*/ counter;
	s8 step;
	s32 timing_offset = 0;
	u32 trl_nomrate = 0, InternalFreq = 0, temp = 0, अगरkhz = 0;

	dprपूर्णांकk("%s:\n", __func__);

	stv0367_get_अगर_khz(state, &अगरkhz);

	ter_state->frequency = p->frequency;
	ter_state->क्रमce = FE_TER_FORCENONE
			+ stv0367_पढ़ोbits(state, F367TER_FORCE) * 2;
	ter_state->अगर_iq_mode = state->config->अगर_iq_mode;
	चयन (state->config->अगर_iq_mode) अणु
	हाल FE_TER_NORMAL_IF_TUNER:  /* Normal IF mode */
		dprपूर्णांकk("ALGO: FE_TER_NORMAL_IF_TUNER selected\n");
		stv0367_ग_लिखोbits(state, F367TER_TUNER_BB, 0);
		stv0367_ग_लिखोbits(state, F367TER_LONGPATH_IF, 0);
		stv0367_ग_लिखोbits(state, F367TER_DEMUX_SWAP, 0);
		अवरोध;
	हाल FE_TER_LONGPATH_IF_TUNER:  /* Long IF mode */
		dprपूर्णांकk("ALGO: FE_TER_LONGPATH_IF_TUNER selected\n");
		stv0367_ग_लिखोbits(state, F367TER_TUNER_BB, 0);
		stv0367_ग_लिखोbits(state, F367TER_LONGPATH_IF, 1);
		stv0367_ग_लिखोbits(state, F367TER_DEMUX_SWAP, 1);
		अवरोध;
	हाल FE_TER_IQ_TUNER:  /* IQ mode */
		dprपूर्णांकk("ALGO: FE_TER_IQ_TUNER selected\n");
		stv0367_ग_लिखोbits(state, F367TER_TUNER_BB, 1);
		stv0367_ग_लिखोbits(state, F367TER_PPM_INVSEL, 0);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "ALGO: wrong TUNER type selected\n");
		वापस -EINVAL;
	पूर्ण

	usleep_range(5000, 7000);

	चयन (p->inversion) अणु
	हाल INVERSION_AUTO:
	शेष:
		dprपूर्णांकk("%s: inversion AUTO\n", __func__);
		अगर (ter_state->अगर_iq_mode == FE_TER_IQ_TUNER)
			stv0367_ग_लिखोbits(state, F367TER_IQ_INVERT,
						ter_state->sense);
		अन्यथा
			stv0367_ग_लिखोbits(state, F367TER_INV_SPECTR,
						ter_state->sense);

		अवरोध;
	हाल INVERSION_ON:
	हाल INVERSION_OFF:
		अगर (ter_state->अगर_iq_mode == FE_TER_IQ_TUNER)
			stv0367_ग_लिखोbits(state, F367TER_IQ_INVERT,
						p->inversion);
		अन्यथा
			stv0367_ग_लिखोbits(state, F367TER_INV_SPECTR,
						p->inversion);

		अवरोध;
	पूर्ण

	अगर ((ter_state->अगर_iq_mode != FE_TER_NORMAL_IF_TUNER) &&
				(ter_state->pBW != ter_state->bw)) अणु
		stv0367ter_agc_iir_lock_detect_set(state);

		/*set fine agc target to 180 क्रम LPIF or IQ mode*/
		/* set Q_AGCTarget */
		stv0367_ग_लिखोbits(state, F367TER_SEL_IQNTAR, 1);
		stv0367_ग_लिखोbits(state, F367TER_AUT_AGC_TARGET_MSB, 0xB);
		/*stv0367_ग_लिखोbits(state,AUT_AGC_TARGET_LSB,0x04); */

		/* set Q_AGCTarget */
		stv0367_ग_लिखोbits(state, F367TER_SEL_IQNTAR, 0);
		stv0367_ग_लिखोbits(state, F367TER_AUT_AGC_TARGET_MSB, 0xB);
		/*stv0367_ग_लिखोbits(state,AUT_AGC_TARGET_LSB,0x04); */

		अगर (!stv0367_iir_filt_init(state, ter_state->bw,
						state->config->xtal))
			वापस -EINVAL;
		/*set IIR filter once क्रम 6,7 or 8MHz BW*/
		ter_state->pBW = ter_state->bw;

		stv0367ter_agc_iir_rst(state);
	पूर्ण

	अगर (ter_state->hierarchy == FE_TER_HIER_LOW_PRIO)
		stv0367_ग_लिखोbits(state, F367TER_BDI_LPSEL, 0x01);
	अन्यथा
		stv0367_ग_लिखोbits(state, F367TER_BDI_LPSEL, 0x00);

	InternalFreq = stv0367ter_get_mclk(state, state->config->xtal) / 1000;
	temp = (पूर्णांक)
		((((ter_state->bw * 64 * (1 << 15) * 100)
						/ (InternalFreq)) * 10) / 7);

	stv0367_ग_लिखोbits(state, F367TER_TRL_NOMRATE_LSB, temp % 2);
	temp = temp / 2;
	stv0367_ग_लिखोbits(state, F367TER_TRL_NOMRATE_HI, temp / 256);
	stv0367_ग_लिखोbits(state, F367TER_TRL_NOMRATE_LO, temp % 256);

	temp = stv0367_पढ़ोbits(state, F367TER_TRL_NOMRATE_HI) * 512 +
			stv0367_पढ़ोbits(state, F367TER_TRL_NOMRATE_LO) * 2 +
			stv0367_पढ़ोbits(state, F367TER_TRL_NOMRATE_LSB);
	temp = (पूर्णांक)(((1 << 17) * ter_state->bw * 1000) / (7 * (InternalFreq)));
	stv0367_ग_लिखोbits(state, F367TER_GAIN_SRC_HI, temp / 256);
	stv0367_ग_लिखोbits(state, F367TER_GAIN_SRC_LO, temp % 256);
	temp = stv0367_पढ़ोbits(state, F367TER_GAIN_SRC_HI) * 256 +
			stv0367_पढ़ोbits(state, F367TER_GAIN_SRC_LO);

	temp = (पूर्णांक)
		((InternalFreq - अगरkhz) * (1 << 16) / (InternalFreq));

	dprपूर्णांकk("DEROT temp=0x%x\n", temp);
	stv0367_ग_लिखोbits(state, F367TER_INC_DEROT_HI, temp / 256);
	stv0367_ग_लिखोbits(state, F367TER_INC_DEROT_LO, temp % 256);

	ter_state->echo_pos = 0;
	ter_state->ucblocks = 0; /* liplianin */
	ter_state->pBER = 0; /* liplianin */
	stv0367_ग_लिखोbits(state, F367TER_LONG_ECHO, ter_state->echo_pos);

	अगर (stv0367ter_lock_algo(state) != FE_TER_LOCKOK)
		वापस 0;

	ter_state->state = FE_TER_LOCKOK;

	ter_state->mode = stv0367_पढ़ोbits(state, F367TER_SYR_MODE);
	ter_state->guard = stv0367_पढ़ोbits(state, F367TER_SYR_GUARD);

	ter_state->first_lock = 1; /* we know sense now :) */

	ter_state->agc_val =
			(stv0367_पढ़ोbits(state, F367TER_AGC1_VAL_LO) << 16) +
			(stv0367_पढ़ोbits(state, F367TER_AGC1_VAL_HI) << 24) +
			stv0367_पढ़ोbits(state, F367TER_AGC2_VAL_LO) +
			(stv0367_पढ़ोbits(state, F367TER_AGC2_VAL_HI) << 8);

	/* Carrier offset calculation */
	stv0367_ग_लिखोbits(state, F367TER_FREEZE, 1);
	offset = (stv0367_पढ़ोbits(state, F367TER_CRL_FOFFSET_VHI) << 16) ;
	offset += (stv0367_पढ़ोbits(state, F367TER_CRL_FOFFSET_HI) << 8);
	offset += (stv0367_पढ़ोbits(state, F367TER_CRL_FOFFSET_LO));
	stv0367_ग_लिखोbits(state, F367TER_FREEZE, 0);
	अगर (offset > 8388607)
		offset -= 16777216;

	offset = offset * 2 / 16384;

	अगर (ter_state->mode == FE_TER_MODE_2K)
		offset = (offset * 4464) / 1000;/*** 1 FFT BIN=4.464khz***/
	अन्यथा अगर (ter_state->mode == FE_TER_MODE_4K)
		offset = (offset * 223) / 100;/*** 1 FFT BIN=2.23khz***/
	अन्यथा  अगर (ter_state->mode == FE_TER_MODE_8K)
		offset = (offset * 111) / 100;/*** 1 FFT BIN=1.1khz***/

	अगर (stv0367_पढ़ोbits(state, F367TER_PPM_INVSEL) == 1) अणु
		अगर ((stv0367_पढ़ोbits(state, F367TER_INV_SPECTR) ==
				(stv0367_पढ़ोbits(state,
					F367TER_STATUS_INV_SPECRUM) == 1)))
			offset = offset * -1;
	पूर्ण

	अगर (ter_state->bw == 6)
		offset = (offset * 6) / 8;
	अन्यथा अगर (ter_state->bw == 7)
		offset = (offset * 7) / 8;

	ter_state->frequency += offset;

	tempo = 10;  /* निकास even अगर timing_offset stays null */
	जबतक ((timing_offset == 0) && (tempo > 0)) अणु
		usleep_range(10000, 20000);	/*was 20ms  */
		/* fine tuning of timing offset अगर required */
		timing_offset = stv0367_पढ़ोbits(state, F367TER_TRL_TOFFSET_LO)
				+ 256 * stv0367_पढ़ोbits(state,
							F367TER_TRL_TOFFSET_HI);
		अगर (timing_offset >= 32768)
			timing_offset -= 65536;
		trl_nomrate = (512 * stv0367_पढ़ोbits(state,
							F367TER_TRL_NOMRATE_HI)
			+ stv0367_पढ़ोbits(state, F367TER_TRL_NOMRATE_LO) * 2
			+ stv0367_पढ़ोbits(state, F367TER_TRL_NOMRATE_LSB));

		timing_offset = ((चिन्हित)(1000000 / trl_nomrate) *
							timing_offset) / 2048;
		tempo--;
	पूर्ण

	अगर (timing_offset <= 0) अणु
		timing_offset = (timing_offset - 11) / 22;
		step = -1;
	पूर्ण अन्यथा अणु
		timing_offset = (timing_offset + 11) / 22;
		step = 1;
	पूर्ण

	क्रम (counter = 0; counter < असल(timing_offset); counter++) अणु
		trl_nomrate += step;
		stv0367_ग_लिखोbits(state, F367TER_TRL_NOMRATE_LSB,
						trl_nomrate % 2);
		stv0367_ग_लिखोbits(state, F367TER_TRL_NOMRATE_LO,
						trl_nomrate / 2);
		usleep_range(1000, 2000);
	पूर्ण

	usleep_range(5000, 6000);
	/* unlocks could happen in हाल of trl centring big step,
	then a core off/on restarts demod */
	u_var = stv0367_पढ़ोbits(state, F367TER_LK);

	अगर (!u_var) अणु
		stv0367_ग_लिखोbits(state, F367TER_CORE_ACTIVE, 0);
		msleep(20);
		stv0367_ग_लिखोbits(state, F367TER_CORE_ACTIVE, 1);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367ter_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा stv0367ter_state *ter_state = state->ter_state;

	/*u8 trials[2]; */
	s8 num_trials, index;
	u8 SenseTrials[] = अणु INVERSION_ON, INVERSION_OFF पूर्ण;

	अगर (state->reinit_on_setfrontend)
		stv0367ter_init(fe);

	अगर (fe->ops.tuner_ops.set_params) अणु
		अगर (state->use_i2c_gatectrl && fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		fe->ops.tuner_ops.set_params(fe);
		अगर (state->use_i2c_gatectrl && fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	चयन (p->transmission_mode) अणु
	शेष:
	हाल TRANSMISSION_MODE_AUTO:
	हाल TRANSMISSION_MODE_2K:
		ter_state->mode = FE_TER_MODE_2K;
		अवरोध;
/*	हाल TRANSMISSION_MODE_4K:
		pLook.mode = FE_TER_MODE_4K;
		अवरोध;*/
	हाल TRANSMISSION_MODE_8K:
		ter_state->mode = FE_TER_MODE_8K;
		अवरोध;
	पूर्ण

	चयन (p->guard_पूर्णांकerval) अणु
	शेष:
	हाल GUARD_INTERVAL_1_32:
	हाल GUARD_INTERVAL_1_16:
	हाल GUARD_INTERVAL_1_8:
	हाल GUARD_INTERVAL_1_4:
		ter_state->guard = p->guard_पूर्णांकerval;
		अवरोध;
	हाल GUARD_INTERVAL_AUTO:
		ter_state->guard = GUARD_INTERVAL_1_32;
		अवरोध;
	पूर्ण

	चयन (p->bandwidth_hz) अणु
	हाल 6000000:
		ter_state->bw = FE_TER_CHAN_BW_6M;
		अवरोध;
	हाल 7000000:
		ter_state->bw = FE_TER_CHAN_BW_7M;
		अवरोध;
	हाल 8000000:
	शेष:
		ter_state->bw = FE_TER_CHAN_BW_8M;
	पूर्ण

	ter_state->hierarchy = FE_TER_HIER_NONE;

	चयन (p->inversion) अणु
	हाल INVERSION_OFF:
	हाल INVERSION_ON:
		num_trials = 1;
		अवरोध;
	शेष:
		num_trials = 2;
		अगर (ter_state->first_lock)
			num_trials = 1;
		अवरोध;
	पूर्ण

	ter_state->state = FE_TER_NOLOCK;
	index = 0;

	जबतक (((index) < num_trials) && (ter_state->state != FE_TER_LOCKOK)) अणु
		अगर (!ter_state->first_lock) अणु
			अगर (p->inversion == INVERSION_AUTO)
				ter_state->sense = SenseTrials[index];

		पूर्ण
		stv0367ter_algo(fe);

		अगर ((ter_state->state == FE_TER_LOCKOK) &&
				(p->inversion == INVERSION_AUTO) &&
								(index == 1)) अणु
			/* invert spectrum sense */
			SenseTrials[index] = SenseTrials[0];
			SenseTrials[(index + 1) % 2] = (SenseTrials[1] + 1) % 2;
		पूर्ण

		index++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367ter_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा stv0367ter_state *ter_state = state->ter_state;
	u32 errs = 0;

	/*रुको क्रम counting completion*/
	अगर (stv0367_पढ़ोbits(state, F367TER_SFERRC_OLDVALUE) == 0) अणु
		errs =
			((u32)stv0367_पढ़ोbits(state, F367TER_ERR_CNT1)
			* (1 << 16))
			+ ((u32)stv0367_पढ़ोbits(state, F367TER_ERR_CNT1_HI)
			* (1 << 8))
			+ ((u32)stv0367_पढ़ोbits(state, F367TER_ERR_CNT1_LO));
		ter_state->ucblocks = errs;
	पूर्ण

	(*ucblocks) = ter_state->ucblocks;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367ter_get_frontend(काष्ठा dvb_frontend *fe,
				   काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा stv0367ter_state *ter_state = state->ter_state;
	क्रमागत stv0367_ter_mode mode;
	पूर्णांक स्थिरell = 0,/* snr = 0,*/ Data = 0;

	p->frequency = stv0367_get_tuner_freq(fe);
	अगर ((पूर्णांक)p->frequency < 0)
		p->frequency = -p->frequency;

	स्थिरell = stv0367_पढ़ोbits(state, F367TER_TPS_CONST);
	अगर (स्थिरell == 0)
		p->modulation = QPSK;
	अन्यथा अगर (स्थिरell == 1)
		p->modulation = QAM_16;
	अन्यथा
		p->modulation = QAM_64;

	p->inversion = stv0367_पढ़ोbits(state, F367TER_INV_SPECTR);

	/* Get the Hierarchical mode */
	Data = stv0367_पढ़ोbits(state, F367TER_TPS_HIERMODE);

	चयन (Data) अणु
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
	शेष:
		p->hierarchy = HIERARCHY_AUTO;
		अवरोध; /* error */
	पूर्ण

	/* Get the FEC Rate */
	अगर (ter_state->hierarchy == FE_TER_HIER_LOW_PRIO)
		Data = stv0367_पढ़ोbits(state, F367TER_TPS_LPCODE);
	अन्यथा
		Data = stv0367_पढ़ोbits(state, F367TER_TPS_HPCODE);

	चयन (Data) अणु
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
	शेष:
		p->code_rate_HP = FEC_AUTO;
		अवरोध; /* error */
	पूर्ण

	mode = stv0367_पढ़ोbits(state, F367TER_SYR_MODE);

	चयन (mode) अणु
	हाल FE_TER_MODE_2K:
		p->transmission_mode = TRANSMISSION_MODE_2K;
		अवरोध;
/*	हाल FE_TER_MODE_4K:
		p->transmission_mode = TRANSMISSION_MODE_4K;
		अवरोध;*/
	हाल FE_TER_MODE_8K:
		p->transmission_mode = TRANSMISSION_MODE_8K;
		अवरोध;
	शेष:
		p->transmission_mode = TRANSMISSION_MODE_AUTO;
	पूर्ण

	p->guard_पूर्णांकerval = stv0367_पढ़ोbits(state, F367TER_SYR_GUARD);

	वापस 0;
पूर्ण

अटल u32 stv0367ter_snr_पढ़ोreg(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	u32 snru32 = 0;
	पूर्णांक cpt = 0;
	u8 cut = stv0367_पढ़ोbits(state, F367TER_IDENTIFICATIONREG);

	जबतक (cpt < 10) अणु
		usleep_range(2000, 3000);
		अगर (cut == 0x50) /*cut 1.0 cut 1.1*/
			snru32 += stv0367_पढ़ोbits(state, F367TER_CHCSNR) / 4;
		अन्यथा /*cu2.0*/
			snru32 += 125 * stv0367_पढ़ोbits(state, F367TER_CHCSNR);

		cpt++;
	पूर्ण
	snru32 /= 10;/*average on 10 values*/

	वापस snru32;
पूर्ण

अटल पूर्णांक stv0367ter_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	u32 snrval = stv0367ter_snr_पढ़ोreg(fe);

	*snr = snrval / 1000;

	वापस 0;
पूर्ण

#अगर 0
अटल पूर्णांक stv0367ter_status(काष्ठा dvb_frontend *fe)
अणु

	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा stv0367ter_state *ter_state = state->ter_state;
	पूर्णांक locked = FALSE;

	locked = (stv0367_पढ़ोbits(state, F367TER_LK));
	अगर (!locked)
		ter_state->unlock_counter += 1;
	अन्यथा
		ter_state->unlock_counter = 0;

	अगर (ter_state->unlock_counter > 2) अणु
		अगर (!stv0367_पढ़ोbits(state, F367TER_TPS_LOCK) ||
				(!stv0367_पढ़ोbits(state, F367TER_LK))) अणु
			stv0367_ग_लिखोbits(state, F367TER_CORE_ACTIVE, 0);
			usleep_range(2000, 3000);
			stv0367_ग_लिखोbits(state, F367TER_CORE_ACTIVE, 1);
			msleep(350);
			locked = (stv0367_पढ़ोbits(state, F367TER_TPS_LOCK)) &&
					(stv0367_पढ़ोbits(state, F367TER_LK));
		पूर्ण

	पूर्ण

	वापस locked;
पूर्ण
#पूर्ण_अगर
अटल पूर्णांक stv0367ter_पढ़ो_status(काष्ठा dvb_frontend *fe,
				  क्रमागत fe_status *status)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s:\n", __func__);

	*status = 0;

	अगर (stv0367_पढ़ोbits(state, F367TER_LK)) अणु
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI
			  | FE_HAS_SYNC | FE_HAS_LOCK;
		dprपूर्णांकk("%s: stv0367 has locked\n", __func__);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367ter_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा stv0367ter_state *ter_state = state->ter_state;
	u32 Errors = 0, tber = 0, temporary = 0;
	पूर्णांक abc = 0, def = 0;


	/*रुको क्रम counting completion*/
	अगर (stv0367_पढ़ोbits(state, F367TER_SFERRC_OLDVALUE) == 0)
		Errors = ((u32)stv0367_पढ़ोbits(state, F367TER_SFEC_ERR_CNT)
			* (1 << 16))
			+ ((u32)stv0367_पढ़ोbits(state, F367TER_SFEC_ERR_CNT_HI)
			* (1 << 8))
			+ ((u32)stv0367_पढ़ोbits(state,
						F367TER_SFEC_ERR_CNT_LO));
	/*measurement not completed, load previous value*/
	अन्यथा अणु
		tber = ter_state->pBER;
		वापस 0;
	पूर्ण

	abc = stv0367_पढ़ोbits(state, F367TER_SFEC_ERR_SOURCE);
	def = stv0367_पढ़ोbits(state, F367TER_SFEC_NUM_EVENT);

	अगर (Errors == 0) अणु
		tber = 0;
	पूर्ण अन्यथा अगर (abc == 0x7) अणु
		अगर (Errors <= 4) अणु
			temporary = (Errors * 1000000000) / (8 * (1 << 14));
		पूर्ण अन्यथा अगर (Errors <= 42) अणु
			temporary = (Errors * 100000000) / (8 * (1 << 14));
			temporary = temporary * 10;
		पूर्ण अन्यथा अगर (Errors <= 429) अणु
			temporary = (Errors * 10000000) / (8 * (1 << 14));
			temporary = temporary * 100;
		पूर्ण अन्यथा अगर (Errors <= 4294) अणु
			temporary = (Errors * 1000000) / (8 * (1 << 14));
			temporary = temporary * 1000;
		पूर्ण अन्यथा अगर (Errors <= 42949) अणु
			temporary = (Errors * 100000) / (8 * (1 << 14));
			temporary = temporary * 10000;
		पूर्ण अन्यथा अगर (Errors <= 429496) अणु
			temporary = (Errors * 10000) / (8 * (1 << 14));
			temporary = temporary * 100000;
		पूर्ण अन्यथा अणु /*अगर (Errors<4294967) 2^22 max error*/
			temporary = (Errors * 1000) / (8 * (1 << 14));
			temporary = temporary * 100000;	/* still to *10 */
		पूर्ण

		/* Byte error*/
		अगर (def == 2)
			/*tber=Errors/(8*(1 <<14));*/
			tber = temporary;
		अन्यथा अगर (def == 3)
			/*tber=Errors/(8*(1 <<16));*/
			tber = temporary / 4;
		अन्यथा अगर (def == 4)
			/*tber=Errors/(8*(1 <<18));*/
			tber = temporary / 16;
		अन्यथा अगर (def == 5)
			/*tber=Errors/(8*(1 <<20));*/
			tber = temporary / 64;
		अन्यथा अगर (def == 6)
			/*tber=Errors/(8*(1 <<22));*/
			tber = temporary / 256;
		अन्यथा
			/* should not pass here*/
			tber = 0;

		अगर ((Errors < 4294967) && (Errors > 429496))
			tber *= 10;

	पूर्ण

	/* save actual value */
	ter_state->pBER = tber;

	(*ber) = tber;

	वापस 0;
पूर्ण
#अगर 0
अटल u32 stv0367ter_get_per(काष्ठा stv0367_state *state)
अणु
	काष्ठा stv0367ter_state *ter_state = state->ter_state;
	u32 Errors = 0, Per = 0, temporary = 0;
	पूर्णांक abc = 0, def = 0, cpt = 0;

	जबतक (((stv0367_पढ़ोbits(state, F367TER_SFERRC_OLDVALUE) == 1) &&
			(cpt < 400)) || ((Errors == 0) && (cpt < 400))) अणु
		usleep_range(1000, 2000);
		Errors = ((u32)stv0367_पढ़ोbits(state, F367TER_ERR_CNT1)
			* (1 << 16))
			+ ((u32)stv0367_पढ़ोbits(state, F367TER_ERR_CNT1_HI)
			* (1 << 8))
			+ ((u32)stv0367_पढ़ोbits(state, F367TER_ERR_CNT1_LO));
		cpt++;
	पूर्ण
	abc = stv0367_पढ़ोbits(state, F367TER_ERR_SRC1);
	def = stv0367_पढ़ोbits(state, F367TER_NUM_EVT1);

	अगर (Errors == 0)
		Per = 0;
	अन्यथा अगर (abc == 0x9) अणु
		अगर (Errors <= 4) अणु
			temporary = (Errors * 1000000000) / (8 * (1 << 8));
		पूर्ण अन्यथा अगर (Errors <= 42) अणु
			temporary = (Errors * 100000000) / (8 * (1 << 8));
			temporary = temporary * 10;
		पूर्ण अन्यथा अगर (Errors <= 429) अणु
			temporary = (Errors * 10000000) / (8 * (1 << 8));
			temporary = temporary * 100;
		पूर्ण अन्यथा अगर (Errors <= 4294) अणु
			temporary = (Errors * 1000000) / (8 * (1 << 8));
			temporary = temporary * 1000;
		पूर्ण अन्यथा अगर (Errors <= 42949) अणु
			temporary = (Errors * 100000) / (8 * (1 << 8));
			temporary = temporary * 10000;
		पूर्ण अन्यथा अणु /*अगर(Errors<=429496)  2^16 errors max*/
			temporary = (Errors * 10000) / (8 * (1 << 8));
			temporary = temporary * 100000;
		पूर्ण

		/* pkt error*/
		अगर (def == 2)
			/*Per=Errors/(1 << 8);*/
			Per = temporary;
		अन्यथा अगर (def == 3)
			/*Per=Errors/(1 << 10);*/
			Per = temporary / 4;
		अन्यथा अगर (def == 4)
			/*Per=Errors/(1 << 12);*/
			Per = temporary / 16;
		अन्यथा अगर (def == 5)
			/*Per=Errors/(1 << 14);*/
			Per = temporary / 64;
		अन्यथा अगर (def == 6)
			/*Per=Errors/(1 << 16);*/
			Per = temporary / 256;
		अन्यथा
			Per = 0;

	पूर्ण
	/* save actual value */
	ter_state->pPER = Per;

	वापस Per;
पूर्ण
#पूर्ण_अगर
अटल पूर्णांक stv0367_get_tune_settings(काष्ठा dvb_frontend *fe,
					काष्ठा dvb_frontend_tune_settings
					*fe_tune_settings)
अणु
	fe_tune_settings->min_delay_ms = 1000;
	fe_tune_settings->step_size = 0;
	fe_tune_settings->max_drअगरt = 0;

	वापस 0;
पूर्ण

अटल व्योम stv0367_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	kमुक्त(state->ter_state);
	kमुक्त(state->cab_state);
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stv0367ter_ops = अणु
	.delsys = अणु SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "ST STV0367 DVB-T",
		.frequency_min_hz	=  47 * MHz,
		.frequency_max_hz	= 862 * MHz,
		.frequency_stepsize_hz	= 15625,
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 | FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_QAM_16 | FE_CAN_QAM_64 |
			FE_CAN_QAM_128 | FE_CAN_QAM_256 | FE_CAN_QAM_AUTO |
			FE_CAN_TRANSMISSION_MODE_AUTO | FE_CAN_RECOVER |
			FE_CAN_INVERSION_AUTO |
			FE_CAN_MUTE_TS
	पूर्ण,
	.release = stv0367_release,
	.init = stv0367ter_init,
	.sleep = stv0367ter_sleep,
	.i2c_gate_ctrl = stv0367ter_gate_ctrl,
	.set_frontend = stv0367ter_set_frontend,
	.get_frontend = stv0367ter_get_frontend,
	.get_tune_settings = stv0367_get_tune_settings,
	.पढ़ो_status = stv0367ter_पढ़ो_status,
	.पढ़ो_ber = stv0367ter_पढ़ो_ber,/* too slow */
/*	.पढ़ो_संकेत_strength = stv0367_पढ़ो_संकेत_strength,*/
	.पढ़ो_snr = stv0367ter_पढ़ो_snr,
	.पढ़ो_ucblocks = stv0367ter_पढ़ो_ucblocks,
पूर्ण;

काष्ठा dvb_frontend *stv0367ter_attach(स्थिर काष्ठा stv0367_config *config,
				   काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा stv0367_state *state = शून्य;
	काष्ठा stv0367ter_state *ter_state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा stv0367_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;
	ter_state = kzalloc(माप(काष्ठा stv0367ter_state), GFP_KERNEL);
	अगर (ter_state == शून्य)
		जाओ error;

	/* setup the state */
	state->i2c = i2c;
	state->config = config;
	state->ter_state = ter_state;
	state->fe.ops = stv0367ter_ops;
	state->fe.demodulator_priv = state;
	state->chip_id = stv0367_पढ़ोreg(state, 0xf000);

	/* demod operation options */
	state->use_i2c_gatectrl = 1;
	state->deftअसल = STV0367_DEFTAB_GENERIC;
	state->reinit_on_setfrontend = 1;
	state->स्वतः_अगर_khz = 0;

	dprपूर्णांकk("%s: chip_id = 0x%x\n", __func__, state->chip_id);

	/* check अगर the demod is there */
	अगर ((state->chip_id != 0x50) && (state->chip_id != 0x60))
		जाओ error;

	वापस &state->fe;

error:
	kमुक्त(ter_state);
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(stv0367ter_attach);

अटल पूर्णांक stv0367cab_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s:\n", __func__);

	stv0367_ग_लिखोbits(state, F367CAB_I2CT_ON, (enable > 0) ? 1 : 0);

	वापस 0;
पूर्ण

अटल u32 stv0367cab_get_mclk(काष्ठा dvb_frontend *fe, u32 ExtClk_Hz)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	u32 mclk_Hz = 0;/* master घड़ी frequency (Hz) */
	u32 M, N, P;


	अगर (stv0367_पढ़ोbits(state, F367CAB_BYPASS_PLLXN) == 0) अणु
		N = (u32)stv0367_पढ़ोbits(state, F367CAB_PLL_NDIV);
		अगर (N == 0)
			N = N + 1;

		M = (u32)stv0367_पढ़ोbits(state, F367CAB_PLL_MDIV);
		अगर (M == 0)
			M = M + 1;

		P = (u32)stv0367_पढ़ोbits(state, F367CAB_PLL_PDIV);

		अगर (P > 5)
			P = 5;

		mclk_Hz = ((ExtClk_Hz / 2) * N) / (M * (1 << P));
		dprपूर्णांकk("stv0367cab_get_mclk BYPASS_PLLXN mclk_Hz=%d\n",
								mclk_Hz);
	पूर्ण अन्यथा
		mclk_Hz = ExtClk_Hz;

	dprपूर्णांकk("stv0367cab_get_mclk final mclk_Hz=%d\n", mclk_Hz);

	वापस mclk_Hz;
पूर्ण

अटल u32 stv0367cab_get_adc_freq(काष्ठा dvb_frontend *fe, u32 ExtClk_Hz)
अणु
	u32 ADCClk_Hz = ExtClk_Hz;

	ADCClk_Hz = stv0367cab_get_mclk(fe, ExtClk_Hz);

	वापस ADCClk_Hz;
पूर्ण

अटल क्रमागत stv0367cab_mod stv0367cab_SetQamSize(काष्ठा stv0367_state *state,
						 u32 SymbolRate,
						 क्रमागत stv0367cab_mod QAMSize)
अणु
	/* Set QAM size */
	stv0367_ग_लिखोbits(state, F367CAB_QAM_MODE, QAMSize);

	/* Set Registers settings specअगरic to the QAM size */
	चयन (QAMSize) अणु
	हाल FE_CAB_MOD_QAM4:
		stv0367_ग_लिखोreg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		अवरोध;
	हाल FE_CAB_MOD_QAM16:
		stv0367_ग_लिखोreg(state, R367CAB_AGC_PWR_REF_L, 0x64);
		stv0367_ग_लिखोreg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		stv0367_ग_लिखोreg(state, R367CAB_FSM_STATE, 0x90);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa7);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LD_SEN, 0x95);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LIMITER, 0x40);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_PNT_GAIN, 0x8a);
		अवरोध;
	हाल FE_CAB_MOD_QAM32:
		stv0367_ग_लिखोreg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		stv0367_ग_लिखोreg(state, R367CAB_AGC_PWR_REF_L, 0x6e);
		stv0367_ग_लिखोreg(state, R367CAB_FSM_STATE, 0xb0);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xb7);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LD_SEN, 0x9d);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LIMITER, 0x7f);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_PNT_GAIN, 0xa7);
		अवरोध;
	हाल FE_CAB_MOD_QAM64:
		stv0367_ग_लिखोreg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x82);
		stv0367_ग_लिखोreg(state, R367CAB_AGC_PWR_REF_L, 0x5a);
		अगर (SymbolRate > 4500000) अणु
			stv0367_ग_लिखोreg(state, R367CAB_FSM_STATE, 0xb0);
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa5);
		पूर्ण अन्यथा अगर (SymbolRate > 2500000) अणु
			stv0367_ग_लिखोreg(state, R367CAB_FSM_STATE, 0xa0);
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa6);
		पूर्ण अन्यथा अणु
			stv0367_ग_लिखोreg(state, R367CAB_FSM_STATE, 0xa0);
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xd1);
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa7);
		पूर्ण
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LD_SEN, 0x95);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LIMITER, 0x40);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_PNT_GAIN, 0x99);
		अवरोध;
	हाल FE_CAB_MOD_QAM128:
		stv0367_ग_लिखोreg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		stv0367_ग_लिखोreg(state, R367CAB_AGC_PWR_REF_L, 0x76);
		stv0367_ग_लिखोreg(state, R367CAB_FSM_STATE, 0x90);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xb1);
		अगर (SymbolRate > 4500000)
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa7);
		अन्यथा अगर (SymbolRate > 2500000)
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa6);
		अन्यथा
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LPF_GAIN, 0x97);

		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LD_SEN, 0x8e);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LIMITER, 0x7f);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_PNT_GAIN, 0xa7);
		अवरोध;
	हाल FE_CAB_MOD_QAM256:
		stv0367_ग_लिखोreg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x94);
		stv0367_ग_लिखोreg(state, R367CAB_AGC_PWR_REF_L, 0x5a);
		stv0367_ग_लिखोreg(state, R367CAB_FSM_STATE, 0xa0);
		अगर (SymbolRate > 4500000)
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
		अन्यथा अगर (SymbolRate > 2500000)
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xc1);
		अन्यथा
			stv0367_ग_लिखोreg(state, R367CAB_EQU_CTR_LPF_GAIN, 0xd1);

		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LPF_GAIN, 0xa7);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LD_SEN, 0x85);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_LIMITER, 0x40);
		stv0367_ग_लिखोreg(state, R367CAB_EQU_PNT_GAIN, 0xa7);
		अवरोध;
	हाल FE_CAB_MOD_QAM512:
		stv0367_ग_लिखोreg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		अवरोध;
	हाल FE_CAB_MOD_QAM1024:
		stv0367_ग_लिखोreg(state, R367CAB_IQDEM_ADJ_AGC_REF, 0x00);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस QAMSize;
पूर्ण

अटल u32 stv0367cab_set_derot_freq(काष्ठा stv0367_state *state,
					u32 adc_hz, s32 derot_hz)
अणु
	u32 sampled_अगर = 0;
	u32 adc_khz;

	adc_khz = adc_hz / 1000;

	dprपूर्णांकk("%s: adc_hz=%d derot_hz=%d\n", __func__, adc_hz, derot_hz);

	अगर (adc_khz != 0) अणु
		अगर (derot_hz < 1000000)
			derot_hz = adc_hz / 4; /* ZIF operation */
		अगर (derot_hz > adc_hz)
			derot_hz = derot_hz - adc_hz;
		sampled_अगर = (u32)derot_hz / 1000;
		sampled_अगर *= 32768;
		sampled_अगर /= adc_khz;
		sampled_अगर *= 256;
	पूर्ण

	अगर (sampled_अगर > 8388607)
		sampled_अगर = 8388607;

	dprपूर्णांकk("%s: sampled_if=0x%x\n", __func__, sampled_अगर);

	stv0367_ग_लिखोreg(state, R367CAB_MIX_NCO_LL, sampled_अगर);
	stv0367_ग_लिखोreg(state, R367CAB_MIX_NCO_HL, (sampled_अगर >> 8));
	stv0367_ग_लिखोbits(state, F367CAB_MIX_NCO_INC_HH, (sampled_अगर >> 16));

	वापस derot_hz;
पूर्ण

अटल u32 stv0367cab_get_derot_freq(काष्ठा stv0367_state *state, u32 adc_hz)
अणु
	u32 sampled_अगर;

	sampled_अगर = stv0367_पढ़ोbits(state, F367CAB_MIX_NCO_INC_LL) +
			(stv0367_पढ़ोbits(state, F367CAB_MIX_NCO_INC_HL) << 8) +
			(stv0367_पढ़ोbits(state, F367CAB_MIX_NCO_INC_HH) << 16);

	sampled_अगर /= 256;
	sampled_अगर *= (adc_hz / 1000);
	sampled_अगर += 1;
	sampled_अगर /= 32768;

	वापस sampled_अगर;
पूर्ण

अटल u32 stv0367cab_set_srate(काष्ठा stv0367_state *state, u32 adc_hz,
			u32 mclk_hz, u32 SymbolRate,
			क्रमागत stv0367cab_mod QAMSize)
अणु
	u32 QamSizeCorr = 0;
	u32 u32_पंचांगp = 0, u32_पंचांगp1 = 0;
	u32 adp_khz;

	dprपूर्णांकk("%s:\n", __func__);

	/* Set Correction factor of SRC gain */
	चयन (QAMSize) अणु
	हाल FE_CAB_MOD_QAM4:
		QamSizeCorr = 1110;
		अवरोध;
	हाल FE_CAB_MOD_QAM16:
		QamSizeCorr = 1032;
		अवरोध;
	हाल FE_CAB_MOD_QAM32:
		QamSizeCorr =  954;
		अवरोध;
	हाल FE_CAB_MOD_QAM64:
		QamSizeCorr =  983;
		अवरोध;
	हाल FE_CAB_MOD_QAM128:
		QamSizeCorr =  957;
		अवरोध;
	हाल FE_CAB_MOD_QAM256:
		QamSizeCorr =  948;
		अवरोध;
	हाल FE_CAB_MOD_QAM512:
		QamSizeCorr =    0;
		अवरोध;
	हाल FE_CAB_MOD_QAM1024:
		QamSizeCorr =  944;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Transfer ratio calculation */
	अगर (adc_hz != 0) अणु
		u32_पंचांगp = 256 * SymbolRate;
		u32_पंचांगp = u32_पंचांगp / adc_hz;
	पूर्ण
	stv0367_ग_लिखोreg(state, R367CAB_EQU_CRL_TFR, (u8)u32_पंचांगp);

	/* Symbol rate and SRC gain calculation */
	adp_khz = (mclk_hz >> 1) / 1000;/* TRL works at half the प्रणाली घड़ी */
	अगर (adp_khz != 0) अणु
		u32_पंचांगp = SymbolRate;
		u32_पंचांगp1 = SymbolRate;

		अगर (u32_पंचांगp < 2097152) अणु /* 2097152 = 2^21 */
			/* Symbol rate calculation */
			u32_पंचांगp *= 2048; /* 2048 = 2^11 */
			u32_पंचांगp = u32_पंचांगp / adp_khz;
			u32_पंचांगp = u32_पंचांगp * 16384; /* 16384 = 2^14 */
			u32_पंचांगp /= 125 ; /* 125 = 1000/2^3 */
			u32_पंचांगp = u32_पंचांगp * 8; /* 8 = 2^3 */

			/* SRC Gain Calculation */
			u32_पंचांगp1 *= 2048; /* *2*2^10 */
			u32_पंचांगp1 /= 439; /* *2/878 */
			u32_पंचांगp1 *= 256; /* *2^8 */
			u32_पंचांगp1 = u32_पंचांगp1 / adp_khz; /* /(AdpClk in kHz) */
			u32_पंचांगp1 *= QamSizeCorr * 9; /* *1000*corr factor */
			u32_पंचांगp1 = u32_पंचांगp1 / 10000000;

		पूर्ण अन्यथा अगर (u32_पंचांगp < 4194304) अणु /* 4194304 = 2**22 */
			/* Symbol rate calculation */
			u32_पंचांगp *= 1024 ; /* 1024 = 2**10 */
			u32_पंचांगp = u32_पंचांगp / adp_khz;
			u32_पंचांगp = u32_पंचांगp * 16384; /* 16384 = 2**14 */
			u32_पंचांगp /= 125 ; /* 125 = 1000/2**3 */
			u32_पंचांगp = u32_पंचांगp * 16; /* 16 = 2**4 */

			/* SRC Gain Calculation */
			u32_पंचांगp1 *= 1024; /* *2*2^9 */
			u32_पंचांगp1 /= 439; /* *2/878 */
			u32_पंचांगp1 *= 256; /* *2^8 */
			u32_पंचांगp1 = u32_पंचांगp1 / adp_khz; /* /(AdpClk in kHz)*/
			u32_पंचांगp1 *= QamSizeCorr * 9; /* *1000*corr factor */
			u32_पंचांगp1 = u32_पंचांगp1 / 5000000;
		पूर्ण अन्यथा अगर (u32_पंचांगp < 8388607) अणु /* 8388607 = 2**23 */
			/* Symbol rate calculation */
			u32_पंचांगp *= 512 ; /* 512 = 2**9 */
			u32_पंचांगp = u32_पंचांगp / adp_khz;
			u32_पंचांगp = u32_पंचांगp * 16384; /* 16384 = 2**14 */
			u32_पंचांगp /= 125 ; /* 125 = 1000/2**3 */
			u32_पंचांगp = u32_पंचांगp * 32; /* 32 = 2**5 */

			/* SRC Gain Calculation */
			u32_पंचांगp1 *= 512; /* *2*2^8 */
			u32_पंचांगp1 /= 439; /* *2/878 */
			u32_पंचांगp1 *= 256; /* *2^8 */
			u32_पंचांगp1 = u32_पंचांगp1 / adp_khz; /* /(AdpClk in kHz) */
			u32_पंचांगp1 *= QamSizeCorr * 9; /* *1000*corr factor */
			u32_पंचांगp1 = u32_पंचांगp1 / 2500000;
		पूर्ण अन्यथा अणु
			/* Symbol rate calculation */
			u32_पंचांगp *= 256 ; /* 256 = 2**8 */
			u32_पंचांगp = u32_पंचांगp / adp_khz;
			u32_पंचांगp = u32_पंचांगp * 16384; /* 16384 = 2**13 */
			u32_पंचांगp /= 125 ; /* 125 = 1000/2**3 */
			u32_पंचांगp = u32_पंचांगp * 64; /* 64 = 2**6 */

			/* SRC Gain Calculation */
			u32_पंचांगp1 *= 256; /* 2*2^7 */
			u32_पंचांगp1 /= 439; /* *2/878 */
			u32_पंचांगp1 *= 256; /* *2^8 */
			u32_पंचांगp1 = u32_पंचांगp1 / adp_khz; /* /(AdpClk in kHz) */
			u32_पंचांगp1 *= QamSizeCorr * 9; /* *1000*corr factor */
			u32_पंचांगp1 = u32_पंचांगp1 / 1250000;
		पूर्ण
	पूर्ण
#अगर 0
	/* Filters' coefficients are calculated and written
	पूर्णांकo रेजिस्टरs only अगर the filters are enabled */
	अगर (stv0367_पढ़ोbits(state, F367CAB_ADJ_EN)) अणु
		stv0367cab_SetIirAdjacentcoefficient(state, mclk_hz,
								SymbolRate);
		/* AllPass filter must be enabled
		when the adjacents filter is used */
		stv0367_ग_लिखोbits(state, F367CAB_ALLPASSFILT_EN, 1);
		stv0367cab_SetAllPasscoefficient(state, mclk_hz, SymbolRate);
	पूर्ण अन्यथा
		/* AllPass filter must be disabled
		when the adjacents filter is not used */
#पूर्ण_अगर
	stv0367_ग_लिखोbits(state, F367CAB_ALLPASSFILT_EN, 0);

	stv0367_ग_लिखोreg(state, R367CAB_SRC_NCO_LL, u32_पंचांगp);
	stv0367_ग_लिखोreg(state, R367CAB_SRC_NCO_LH, (u32_पंचांगp >> 8));
	stv0367_ग_लिखोreg(state, R367CAB_SRC_NCO_HL, (u32_पंचांगp >> 16));
	stv0367_ग_लिखोreg(state, R367CAB_SRC_NCO_HH, (u32_पंचांगp >> 24));

	stv0367_ग_लिखोreg(state, R367CAB_IQDEM_GAIN_SRC_L, u32_पंचांगp1 & 0x00ff);
	stv0367_ग_लिखोbits(state, F367CAB_GAIN_SRC_HI, (u32_पंचांगp1 >> 8) & 0x00ff);

	वापस SymbolRate ;
पूर्ण

अटल u32 stv0367cab_GetSymbolRate(काष्ठा stv0367_state *state, u32 mclk_hz)
अणु
	u32 regsym;
	u32 adp_khz;

	regsym = stv0367_पढ़ोreg(state, R367CAB_SRC_NCO_LL) +
		(stv0367_पढ़ोreg(state, R367CAB_SRC_NCO_LH) << 8) +
		(stv0367_पढ़ोreg(state, R367CAB_SRC_NCO_HL) << 16) +
		(stv0367_पढ़ोreg(state, R367CAB_SRC_NCO_HH) << 24);

	adp_khz = (mclk_hz >> 1) / 1000;/* TRL works at half the प्रणाली घड़ी */

	अगर (regsym < 134217728) अणु		/* 134217728L = 2**27*/
		regsym = regsym * 32;		/* 32 = 2**5 */
		regsym = regsym / 32768;	/* 32768L = 2**15 */
		regsym = adp_khz * regsym;	/* AdpClk in kHz */
		regsym = regsym / 128;		/* 128 = 2**7 */
		regsym *= 125 ;			/* 125 = 1000/2**3 */
		regsym /= 2048 ;		/* 2048 = 2**11	*/
	पूर्ण अन्यथा अगर (regsym < 268435456) अणु	/* 268435456L = 2**28 */
		regsym = regsym * 16;		/* 16 = 2**4 */
		regsym = regsym / 32768;	/* 32768L = 2**15 */
		regsym = adp_khz * regsym;	/* AdpClk in kHz */
		regsym = regsym / 128;		/* 128 = 2**7 */
		regsym *= 125 ;			/* 125 = 1000/2**3*/
		regsym /= 1024 ;		/* 256 = 2**10*/
	पूर्ण अन्यथा अगर (regsym < 536870912) अणु	/* 536870912L = 2**29*/
		regsym = regsym * 8;		/* 8 = 2**3 */
		regsym = regsym / 32768;	/* 32768L = 2**15 */
		regsym = adp_khz * regsym;	/* AdpClk in kHz */
		regsym = regsym / 128;		/* 128 = 2**7 */
		regsym *= 125 ;			/* 125 = 1000/2**3 */
		regsym /= 512 ;			/* 128 = 2**9 */
	पूर्ण अन्यथा अणु
		regsym = regsym * 4;		/* 4 = 2**2 */
		regsym = regsym / 32768;	/* 32768L = 2**15 */
		regsym = adp_khz * regsym;	/* AdpClk in kHz */
		regsym = regsym / 128;		/* 128 = 2**7 */
		regsym *= 125 ;			/* 125 = 1000/2**3 */
		regsym /= 256 ;			/* 64 = 2**8 */
	पूर्ण

	वापस regsym;
पूर्ण

अटल u32 stv0367cab_fsm_status(काष्ठा stv0367_state *state)
अणु
	वापस stv0367_पढ़ोbits(state, F367CAB_FSM_STATUS);
पूर्ण

अटल u32 stv0367cab_qamfec_lock(काष्ठा stv0367_state *state)
अणु
	वापस stv0367_पढ़ोbits(state,
		(state->cab_state->qamfec_status_reg ?
		 state->cab_state->qamfec_status_reg :
		 F367CAB_QAMFEC_LOCK));
पूर्ण

अटल
क्रमागत stv0367_cab_संकेत_type stv0367cab_fsm_संकेतtype(u32 qam_fsm_status)
अणु
	क्रमागत stv0367_cab_संकेत_type संकेतtype = FE_CAB_NOAGC;

	चयन (qam_fsm_status) अणु
	हाल 1:
		संकेतtype = FE_CAB_NOAGC;
		अवरोध;
	हाल 2:
		संकेतtype = FE_CAB_NOTIMING;
		अवरोध;
	हाल 3:
		संकेतtype = FE_CAB_TIMINGOK;
		अवरोध;
	हाल 4:
		संकेतtype = FE_CAB_NOCARRIER;
		अवरोध;
	हाल 5:
		संकेतtype = FE_CAB_CARRIEROK;
		अवरोध;
	हाल 7:
		संकेतtype = FE_CAB_NOBLIND;
		अवरोध;
	हाल 8:
		संकेतtype = FE_CAB_BLINDOK;
		अवरोध;
	हाल 10:
		संकेतtype = FE_CAB_NODEMOD;
		अवरोध;
	हाल 11:
		संकेतtype = FE_CAB_DEMODOK;
		अवरोध;
	हाल 12:
		संकेतtype = FE_CAB_DEMODOK;
		अवरोध;
	हाल 13:
		संकेतtype = FE_CAB_NODEMOD;
		अवरोध;
	हाल 14:
		संकेतtype = FE_CAB_NOBLIND;
		अवरोध;
	हाल 15:
		संकेतtype = FE_CAB_NOSIGNAL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस संकेतtype;
पूर्ण

अटल पूर्णांक stv0367cab_पढ़ो_status(काष्ठा dvb_frontend *fe,
				  क्रमागत fe_status *status)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s:\n", __func__);

	*status = 0;

	/* update cab_state->state from QAM_FSM_STATUS */
	state->cab_state->state = stv0367cab_fsm_संकेतtype(
		stv0367cab_fsm_status(state));

	अगर (stv0367cab_qamfec_lock(state)) अणु
		*status = FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_VITERBI
			  | FE_HAS_SYNC | FE_HAS_LOCK;
		dprपूर्णांकk("%s: stv0367 has locked\n", __func__);
	पूर्ण अन्यथा अणु
		अगर (state->cab_state->state > FE_CAB_NOSIGNAL)
			*status |= FE_HAS_SIGNAL;

		अगर (state->cab_state->state > FE_CAB_NOCARRIER)
			*status |= FE_HAS_CARRIER;

		अगर (state->cab_state->state >= FE_CAB_DEMODOK)
			*status |= FE_HAS_VITERBI;

		अगर (state->cab_state->state >= FE_CAB_DATAOK)
			*status |= FE_HAS_SYNC;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367cab_standby(काष्ठा dvb_frontend *fe, u8 standby_on)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	dprपूर्णांकk("%s:\n", __func__);

	अगर (standby_on) अणु
		stv0367_ग_लिखोbits(state, F367CAB_BYPASS_PLLXN, 0x03);
		stv0367_ग_लिखोbits(state, F367CAB_STDBY_PLLXN, 0x01);
		stv0367_ग_लिखोbits(state, F367CAB_STDBY, 1);
		stv0367_ग_लिखोbits(state, F367CAB_STDBY_CORE, 1);
		stv0367_ग_लिखोbits(state, F367CAB_EN_BUFFER_I, 0);
		stv0367_ग_लिखोbits(state, F367CAB_EN_BUFFER_Q, 0);
		stv0367_ग_लिखोbits(state, F367CAB_POFFQ, 1);
		stv0367_ग_लिखोbits(state, F367CAB_POFFI, 1);
	पूर्ण अन्यथा अणु
		stv0367_ग_लिखोbits(state, F367CAB_STDBY_PLLXN, 0x00);
		stv0367_ग_लिखोbits(state, F367CAB_BYPASS_PLLXN, 0x00);
		stv0367_ग_लिखोbits(state, F367CAB_STDBY, 0);
		stv0367_ग_लिखोbits(state, F367CAB_STDBY_CORE, 0);
		stv0367_ग_लिखोbits(state, F367CAB_EN_BUFFER_I, 1);
		stv0367_ग_लिखोbits(state, F367CAB_EN_BUFFER_Q, 1);
		stv0367_ग_लिखोbits(state, F367CAB_POFFQ, 0);
		stv0367_ग_लिखोbits(state, F367CAB_POFFI, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367cab_sleep(काष्ठा dvb_frontend *fe)
अणु
	वापस stv0367cab_standby(fe, 1);
पूर्ण

अटल पूर्णांक stv0367cab_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा stv0367cab_state *cab_state = state->cab_state;

	dprपूर्णांकk("%s:\n", __func__);

	stv0367_ग_लिखो_table(state,
		stv0367_deftअसल[state->deftअसल][STV0367_TAB_CAB]);

	चयन (state->config->ts_mode) अणु
	हाल STV0367_DVBCI_CLOCK:
		dprपूर्णांकk("Setting TSMode = STV0367_DVBCI_CLOCK\n");
		stv0367_ग_लिखोbits(state, F367CAB_OUTFORMAT, 0x03);
		अवरोध;
	हाल STV0367_SERIAL_PUNCT_CLOCK:
	हाल STV0367_SERIAL_CONT_CLOCK:
		stv0367_ग_लिखोbits(state, F367CAB_OUTFORMAT, 0x01);
		अवरोध;
	हाल STV0367_PARALLEL_PUNCT_CLOCK:
	हाल STV0367_OUTPUTMODE_DEFAULT:
		stv0367_ग_लिखोbits(state, F367CAB_OUTFORMAT, 0x00);
		अवरोध;
	पूर्ण

	चयन (state->config->clk_pol) अणु
	हाल STV0367_RISINGEDGE_CLOCK:
		stv0367_ग_लिखोbits(state, F367CAB_CLK_POLARITY, 0x00);
		अवरोध;
	हाल STV0367_FALLINGEDGE_CLOCK:
	हाल STV0367_CLOCKPOLARITY_DEFAULT:
		stv0367_ग_लिखोbits(state, F367CAB_CLK_POLARITY, 0x01);
		अवरोध;
	पूर्ण

	stv0367_ग_लिखोbits(state, F367CAB_SYNC_STRIP, 0x00);

	stv0367_ग_लिखोbits(state, F367CAB_CT_NBST, 0x01);

	stv0367_ग_लिखोbits(state, F367CAB_TS_SWAP, 0x01);

	stv0367_ग_लिखोbits(state, F367CAB_FIFO_BYPASS, 0x00);

	stv0367_ग_लिखोreg(state, R367CAB_ANACTRL, 0x00);/*PLL enabled and used */

	cab_state->mclk = stv0367cab_get_mclk(fe, state->config->xtal);
	cab_state->adc_clk = stv0367cab_get_adc_freq(fe, state->config->xtal);

	वापस 0;
पूर्ण
अटल
क्रमागत stv0367_cab_संकेत_type stv0367cab_algo(काष्ठा stv0367_state *state,
					     काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा stv0367cab_state *cab_state = state->cab_state;
	क्रमागत stv0367_cab_संकेत_type संकेतType = FE_CAB_NOAGC;
	u32	QAMFEC_Lock, QAM_Lock, u32_पंचांगp, अगरkhz,
		LockTime, TRLTimeOut, AGCTimeOut, CRLSymbols,
		CRLTimeOut, EQLTimeOut, DemodTimeOut, FECTimeOut;
	u8	TrackAGCAccum;
	s32	पंचांगp;

	dprपूर्णांकk("%s:\n", __func__);

	stv0367_get_अगर_khz(state, &अगरkhz);

	/* Timeouts calculation */
	/* A max lock समय of 25 ms is allowed क्रम delayed AGC */
	AGCTimeOut = 25;
	/* 100000 symbols needed by the TRL as a maximum value */
	TRLTimeOut = 100000000 / p->symbol_rate;
	/* CRLSymbols is the needed number of symbols to achieve a lock
	   within [-4%, +4%] of the symbol rate.
	   CRL समयout is calculated
	   क्रम a lock within [-search_range, +search_range].
	   EQL समयout can be changed depending on
	   the micro-reflections we want to handle.
	   A अक्षरacterization must be perक्रमmed
	   with these echoes to get new समयout values.
	*/
	चयन (p->modulation) अणु
	हाल QAM_16:
		CRLSymbols = 150000;
		EQLTimeOut = 100;
		अवरोध;
	हाल QAM_32:
		CRLSymbols = 250000;
		EQLTimeOut = 100;
		अवरोध;
	हाल QAM_64:
		CRLSymbols = 200000;
		EQLTimeOut = 100;
		अवरोध;
	हाल QAM_128:
		CRLSymbols = 250000;
		EQLTimeOut = 100;
		अवरोध;
	हाल QAM_256:
		CRLSymbols = 250000;
		EQLTimeOut = 100;
		अवरोध;
	शेष:
		CRLSymbols = 200000;
		EQLTimeOut = 100;
		अवरोध;
	पूर्ण
#अगर 0
	अगर (pIntParams->search_range < 0) अणु
		CRLTimeOut = (25 * CRLSymbols *
				(-pIntParams->search_range / 1000)) /
					(pIntParams->symbol_rate / 1000);
	पूर्ण अन्यथा
#पूर्ण_अगर
	CRLTimeOut = (25 * CRLSymbols * (cab_state->search_range / 1000)) /
					(p->symbol_rate / 1000);

	CRLTimeOut = (1000 * CRLTimeOut) / p->symbol_rate;
	/* Timeouts below 50ms are coerced */
	अगर (CRLTimeOut < 50)
		CRLTimeOut = 50;
	/* A maximum of 100 TS packets is needed to get FEC lock even in हाल
	the spectrum inversion needs to be changed.
	   This is equal to 20 ms in हाल of the lowest symbol rate of 0.87Msps
	*/
	FECTimeOut = 20;
	DemodTimeOut = AGCTimeOut + TRLTimeOut + CRLTimeOut + EQLTimeOut;

	dprपूर्णांकk("%s: DemodTimeOut=%d\n", __func__, DemodTimeOut);

	/* Reset the TRL to ensure nothing starts until the
	   AGC is stable which ensures a better lock समय
	*/
	stv0367_ग_लिखोreg(state, R367CAB_CTRL_1, 0x04);
	/* Set AGC accumulation समय to minimum and lock threshold to maximum
	in order to speed up the AGC lock */
	TrackAGCAccum = stv0367_पढ़ोbits(state, F367CAB_AGC_ACCUMRSTSEL);
	stv0367_ग_लिखोbits(state, F367CAB_AGC_ACCUMRSTSEL, 0x0);
	/* Modulus Mapper is disabled */
	stv0367_ग_लिखोbits(state, F367CAB_MODULUSMAP_EN, 0);
	/* Disable the sweep function */
	stv0367_ग_लिखोbits(state, F367CAB_SWEEP_EN, 0);
	/* The sweep function is never used, Sweep rate must be set to 0 */
	/* Set the derotator frequency in Hz */
	stv0367cab_set_derot_freq(state, cab_state->adc_clk,
		(1000 * (s32)अगरkhz + cab_state->derot_offset));
	/* Disable the Allpass Filter when the symbol rate is out of range */
	अगर ((p->symbol_rate > 10800000) | (p->symbol_rate < 1800000)) अणु
		stv0367_ग_लिखोbits(state, F367CAB_ADJ_EN, 0);
		stv0367_ग_लिखोbits(state, F367CAB_ALLPASSFILT_EN, 0);
	पूर्ण
#अगर 0
	/* Check अगर the tuner is locked */
	tuner_lock = stv0367cab_tuner_get_status(fe);
	अगर (tuner_lock == 0)
		वापस FE_367CAB_NOTUNER;
#पूर्ण_अगर
	/* Release the TRL to start demodulator acquisition */
	/* Wait क्रम QAM lock */
	LockTime = 0;
	stv0367_ग_लिखोreg(state, R367CAB_CTRL_1, 0x00);
	करो अणु
		QAM_Lock = stv0367cab_fsm_status(state);
		अगर ((LockTime >= (DemodTimeOut - EQLTimeOut)) &&
							(QAM_Lock == 0x04))
			/*
			 * We करोn't रुको दीर्घer, the frequency/phase offset
			 * must be too big
			 */
			LockTime = DemodTimeOut;
		अन्यथा अगर ((LockTime >= (AGCTimeOut + TRLTimeOut)) &&
							(QAM_Lock == 0x02))
			/*
			 * We करोn't रुको दीर्घer, either there is no संकेत or
			 * it is not the right symbol rate or it is an analog
			 * carrier
			 */
		अणु
			LockTime = DemodTimeOut;
			u32_पंचांगp = stv0367_पढ़ोbits(state,
						F367CAB_AGC_PWR_WORD_LO) +
					(stv0367_पढ़ोbits(state,
						F367CAB_AGC_PWR_WORD_ME) << 8) +
					(stv0367_पढ़ोbits(state,
						F367CAB_AGC_PWR_WORD_HI) << 16);
			अगर (u32_पंचांगp >= 131072)
				u32_पंचांगp = 262144 - u32_पंचांगp;
			u32_पंचांगp = u32_पंचांगp / (1 << (11 - stv0367_पढ़ोbits(state,
							F367CAB_AGC_IF_BWSEL)));

			अगर (u32_पंचांगp < stv0367_पढ़ोbits(state,
						F367CAB_AGC_PWRREF_LO) +
					256 * stv0367_पढ़ोbits(state,
						F367CAB_AGC_PWRREF_HI) - 10)
				QAM_Lock = 0x0f;
		पूर्ण अन्यथा अणु
			usleep_range(10000, 20000);
			LockTime += 10;
		पूर्ण
		dprपूर्णांकk("QAM_Lock=0x%x LockTime=%d\n", QAM_Lock, LockTime);
		पंचांगp = stv0367_पढ़ोreg(state, R367CAB_IT_STATUS1);

		dprपूर्णांकk("R367CAB_IT_STATUS1=0x%x\n", पंचांगp);

	पूर्ण जबतक (((QAM_Lock != 0x0c) && (QAM_Lock != 0x0b)) &&
						(LockTime < DemodTimeOut));

	dprपूर्णांकk("QAM_Lock=0x%x\n", QAM_Lock);

	पंचांगp = stv0367_पढ़ोreg(state, R367CAB_IT_STATUS1);
	dprपूर्णांकk("R367CAB_IT_STATUS1=0x%x\n", पंचांगp);
	पंचांगp = stv0367_पढ़ोreg(state, R367CAB_IT_STATUS2);
	dprपूर्णांकk("R367CAB_IT_STATUS2=0x%x\n", पंचांगp);

	पंचांगp  = stv0367cab_get_derot_freq(state, cab_state->adc_clk);
	dprपूर्णांकk("stv0367cab_get_derot_freq=0x%x\n", पंचांगp);

	अगर ((QAM_Lock == 0x0c) || (QAM_Lock == 0x0b)) अणु
		/* Wait क्रम FEC lock */
		LockTime = 0;
		करो अणु
			usleep_range(5000, 7000);
			LockTime += 5;
			QAMFEC_Lock = stv0367cab_qamfec_lock(state);
		पूर्ण जबतक (!QAMFEC_Lock && (LockTime < FECTimeOut));
	पूर्ण अन्यथा
		QAMFEC_Lock = 0;

	अगर (QAMFEC_Lock) अणु
		संकेतType = FE_CAB_DATAOK;
		cab_state->spect_inv = stv0367_पढ़ोbits(state,
							F367CAB_QUAD_INV);
#अगर 0
/* not clear क्रम me */
		अगर (अगरkhz != 0) अणु
			अगर (अगरkhz > cab_state->adc_clk / 1000) अणु
				cab_state->freq_khz =
					FE_Cab_TunerGetFrequency(pIntParams->hTuner)
				- stv0367cab_get_derot_freq(state, cab_state->adc_clk)
				- cab_state->adc_clk / 1000 + अगरkhz;
			पूर्ण अन्यथा अणु
				cab_state->freq_khz =
						FE_Cab_TunerGetFrequency(pIntParams->hTuner)
						- stv0367cab_get_derot_freq(state, cab_state->adc_clk)
						+ अगरkhz;
			पूर्ण
		पूर्ण अन्यथा अणु
			cab_state->freq_khz =
				FE_Cab_TunerGetFrequency(pIntParams->hTuner) +
				stv0367cab_get_derot_freq(state,
							cab_state->adc_clk) -
				cab_state->adc_clk / 4000;
		पूर्ण
#पूर्ण_अगर
		cab_state->symbol_rate = stv0367cab_GetSymbolRate(state,
							cab_state->mclk);
		cab_state->locked = 1;

		/* stv0367_setbits(state, F367CAB_AGC_ACCUMRSTSEL,7);*/
	पूर्ण अन्यथा
		संकेतType = stv0367cab_fsm_संकेतtype(QAM_Lock);

	/* Set the AGC control values to tracking values */
	stv0367_ग_लिखोbits(state, F367CAB_AGC_ACCUMRSTSEL, TrackAGCAccum);
	वापस संकेतType;
पूर्ण

अटल पूर्णांक stv0367cab_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा stv0367cab_state *cab_state = state->cab_state;
	क्रमागत stv0367cab_mod QAMSize = 0;

	dprपूर्णांकk("%s: freq = %d, srate = %d\n", __func__,
					p->frequency, p->symbol_rate);

	cab_state->derot_offset = 0;

	चयन (p->modulation) अणु
	हाल QAM_16:
		QAMSize = FE_CAB_MOD_QAM16;
		अवरोध;
	हाल QAM_32:
		QAMSize = FE_CAB_MOD_QAM32;
		अवरोध;
	हाल QAM_64:
		QAMSize = FE_CAB_MOD_QAM64;
		अवरोध;
	हाल QAM_128:
		QAMSize = FE_CAB_MOD_QAM128;
		अवरोध;
	हाल QAM_256:
		QAMSize = FE_CAB_MOD_QAM256;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (state->reinit_on_setfrontend)
		stv0367cab_init(fe);

	/* Tuner Frequency Setting */
	अगर (fe->ops.tuner_ops.set_params) अणु
		अगर (state->use_i2c_gatectrl && fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		fe->ops.tuner_ops.set_params(fe);
		अगर (state->use_i2c_gatectrl && fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	stv0367cab_SetQamSize(
			state,
			p->symbol_rate,
			QAMSize);

	stv0367cab_set_srate(state,
			cab_state->adc_clk,
			cab_state->mclk,
			p->symbol_rate,
			QAMSize);
	/* Search algorithm launch, [-1.1*RangeOffset, +1.1*RangeOffset] scan */
	cab_state->state = stv0367cab_algo(state, p);
	वापस 0;
पूर्ण

अटल पूर्णांक stv0367cab_get_frontend(काष्ठा dvb_frontend *fe,
				   काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा stv0367cab_state *cab_state = state->cab_state;
	u32 अगरkhz = 0;

	क्रमागत stv0367cab_mod QAMSize;

	dprपूर्णांकk("%s:\n", __func__);

	stv0367_get_अगर_khz(state, &अगरkhz);
	p->symbol_rate = stv0367cab_GetSymbolRate(state, cab_state->mclk);

	QAMSize = stv0367_पढ़ोbits(state, F367CAB_QAM_MODE);
	चयन (QAMSize) अणु
	हाल FE_CAB_MOD_QAM16:
		p->modulation = QAM_16;
		अवरोध;
	हाल FE_CAB_MOD_QAM32:
		p->modulation = QAM_32;
		अवरोध;
	हाल FE_CAB_MOD_QAM64:
		p->modulation = QAM_64;
		अवरोध;
	हाल FE_CAB_MOD_QAM128:
		p->modulation = QAM_128;
		अवरोध;
	हाल FE_CAB_MOD_QAM256:
		p->modulation = QAM_256;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	p->frequency = stv0367_get_tuner_freq(fe);

	dprपूर्णांकk("%s: tuner frequency = %d\n", __func__, p->frequency);

	अगर (अगरkhz == 0) अणु
		p->frequency +=
			(stv0367cab_get_derot_freq(state, cab_state->adc_clk) -
			cab_state->adc_clk / 4000);
		वापस 0;
	पूर्ण

	अगर (अगरkhz > cab_state->adc_clk / 1000)
		p->frequency += (अगरkhz
			- stv0367cab_get_derot_freq(state, cab_state->adc_clk)
			- cab_state->adc_clk / 1000);
	अन्यथा
		p->frequency += (अगरkhz
			- stv0367cab_get_derot_freq(state, cab_state->adc_clk));

	वापस 0;
पूर्ण

#अगर 0
व्योम stv0367cab_GetErrorCount(state, क्रमागत stv0367cab_mod QAMSize,
			u32 symbol_rate, FE_367qam_Monitor *Monitor_results)
अणु
	stv0367cab_OptimiseNByteAndGetBER(state, QAMSize, symbol_rate, Monitor_results);
	stv0367cab_GetPacketsCount(state, Monitor_results);

	वापस;
पूर्ण

अटल पूर्णांक stv0367cab_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	वापस 0;
पूर्ण
#पूर्ण_अगर
अटल s32 stv0367cab_get_rf_lvl(काष्ठा stv0367_state *state)
अणु
	s32 rfLevel = 0;
	s32 RfAgcPwm = 0, IfAgcPwm = 0;
	u8 i;

	stv0367_ग_लिखोbits(state, F367CAB_STDBY_ADCGP, 0x0);

	RfAgcPwm =
		(stv0367_पढ़ोbits(state, F367CAB_RF_AGC1_LEVEL_LO) & 0x03) +
		(stv0367_पढ़ोbits(state, F367CAB_RF_AGC1_LEVEL_HI) << 2);
	RfAgcPwm = 100 * RfAgcPwm / 1023;

	IfAgcPwm =
		stv0367_पढ़ोbits(state, F367CAB_AGC_IF_PWMCMD_LO) +
		(stv0367_पढ़ोbits(state, F367CAB_AGC_IF_PWMCMD_HI) << 8);
	अगर (IfAgcPwm >= 2048)
		IfAgcPwm -= 2048;
	अन्यथा
		IfAgcPwm += 2048;

	IfAgcPwm = 100 * IfAgcPwm / 4095;

	/* For DTT75467 on NIM */
	अगर (RfAgcPwm < 90  && IfAgcPwm < 28) अणु
		क्रम (i = 0; i < RF_LOOKUP_TABLE_SIZE; i++) अणु
			अगर (RfAgcPwm <= stv0367cab_RF_LookUp1[0][i]) अणु
				rfLevel = (-1) * stv0367cab_RF_LookUp1[1][i];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == RF_LOOKUP_TABLE_SIZE)
			rfLevel = -56;
	पूर्ण अन्यथा अणु /*अगर IF AGC>10*/
		क्रम (i = 0; i < RF_LOOKUP_TABLE2_SIZE; i++) अणु
			अगर (IfAgcPwm <= stv0367cab_RF_LookUp2[0][i]) अणु
				rfLevel = (-1) * stv0367cab_RF_LookUp2[1][i];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == RF_LOOKUP_TABLE2_SIZE)
			rfLevel = -72;
	पूर्ण
	वापस rfLevel;
पूर्ण

अटल पूर्णांक stv0367cab_पढ़ो_strength(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	s32 संकेत =  stv0367cab_get_rf_lvl(state);

	dprपूर्णांकk("%s: signal=%d dBm\n", __func__, संकेत);

	अगर (संकेत <= -72)
		*strength = 65535;
	अन्यथा
		*strength = (22 + संकेत) * (-1311);

	dprपूर्णांकk("%s: strength=%d\n", __func__, (*strength));

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367cab_snr_घातer(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	क्रमागत stv0367cab_mod QAMSize;

	QAMSize = stv0367_पढ़ोbits(state, F367CAB_QAM_MODE);
	चयन (QAMSize) अणु
	हाल FE_CAB_MOD_QAM4:
		वापस 21904;
	हाल FE_CAB_MOD_QAM16:
		वापस 20480;
	हाल FE_CAB_MOD_QAM32:
		वापस 23040;
	हाल FE_CAB_MOD_QAM64:
		वापस 21504;
	हाल FE_CAB_MOD_QAM128:
		वापस 23616;
	हाल FE_CAB_MOD_QAM256:
		वापस 21760;
	हाल FE_CAB_MOD_QAM1024:
		वापस 21280;
	शेष:
		अवरोध;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक stv0367cab_snr_पढ़ोreg(काष्ठा dvb_frontend *fe, पूर्णांक avgभाग)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	u32 regval = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 10; i++) अणु
		regval += (stv0367_पढ़ोbits(state, F367CAB_SNR_LO)
			+ 256 * stv0367_पढ़ोbits(state, F367CAB_SNR_HI));
	पूर्ण

	अगर (avgभाग)
		regval /= 10;

	वापस regval;
पूर्ण

अटल पूर्णांक stv0367cab_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	u32 noisepercentage;
	u32 regval = 0, temp = 0;
	पूर्णांक घातer;

	घातer = stv0367cab_snr_घातer(fe);
	regval = stv0367cab_snr_पढ़ोreg(fe, 1);

	अगर (regval != 0) अणु
		temp = घातer
			* (1 << (3 + stv0367_पढ़ोbits(state, F367CAB_SNR_PER)));
		temp /= regval;
	पूर्ण

	/* table values, not needed to calculate logarithms */
	अगर (temp >= 5012)
		noisepercentage = 100;
	अन्यथा अगर (temp >= 3981)
		noisepercentage = 93;
	अन्यथा अगर (temp >= 3162)
		noisepercentage = 86;
	अन्यथा अगर (temp >= 2512)
		noisepercentage = 79;
	अन्यथा अगर (temp >= 1995)
		noisepercentage = 72;
	अन्यथा अगर (temp >= 1585)
		noisepercentage = 65;
	अन्यथा अगर (temp >= 1259)
		noisepercentage = 58;
	अन्यथा अगर (temp >= 1000)
		noisepercentage = 50;
	अन्यथा अगर (temp >= 794)
		noisepercentage = 43;
	अन्यथा अगर (temp >= 501)
		noisepercentage = 36;
	अन्यथा अगर (temp >= 316)
		noisepercentage = 29;
	अन्यथा अगर (temp >= 200)
		noisepercentage = 22;
	अन्यथा अगर (temp >= 158)
		noisepercentage = 14;
	अन्यथा अगर (temp >= 126)
		noisepercentage = 7;
	अन्यथा
		noisepercentage = 0;

	dprपूर्णांकk("%s: noisepercentage=%d\n", __func__, noisepercentage);

	*snr = (noisepercentage * 65535) / 100;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367cab_पढ़ो_ucblcks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	पूर्णांक corrected, tscount;

	*ucblocks = (stv0367_पढ़ोreg(state, R367CAB_RS_COUNTER_5) << 8)
			| stv0367_पढ़ोreg(state, R367CAB_RS_COUNTER_4);
	corrected = (stv0367_पढ़ोreg(state, R367CAB_RS_COUNTER_3) << 8)
			| stv0367_पढ़ोreg(state, R367CAB_RS_COUNTER_2);
	tscount = (stv0367_पढ़ोreg(state, R367CAB_RS_COUNTER_2) << 8)
			| stv0367_पढ़ोreg(state, R367CAB_RS_COUNTER_1);

	dprपूर्णांकk("%s: uncorrected blocks=%d corrected blocks=%d tscount=%d\n",
				__func__, *ucblocks, corrected, tscount);

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा dvb_frontend_ops stv0367cab_ops = अणु
	.delsys = अणु SYS_DVBC_ANNEX_A पूर्ण,
	.info = अणु
		.name = "ST STV0367 DVB-C",
		.frequency_min_hz =  47 * MHz,
		.frequency_max_hz = 862 * MHz,
		.frequency_stepsize_hz = 62500,
		.symbol_rate_min = 870000,
		.symbol_rate_max = 11700000,
		.caps = 0x400 |/* FE_CAN_QAM_4 */
			FE_CAN_QAM_16 | FE_CAN_QAM_32  |
			FE_CAN_QAM_64 | FE_CAN_QAM_128 |
			FE_CAN_QAM_256 | FE_CAN_FEC_AUTO
	पूर्ण,
	.release				= stv0367_release,
	.init					= stv0367cab_init,
	.sleep					= stv0367cab_sleep,
	.i2c_gate_ctrl				= stv0367cab_gate_ctrl,
	.set_frontend				= stv0367cab_set_frontend,
	.get_frontend				= stv0367cab_get_frontend,
	.पढ़ो_status				= stv0367cab_पढ़ो_status,
/*	.पढ़ो_ber				= stv0367cab_पढ़ो_ber, */
	.पढ़ो_संकेत_strength			= stv0367cab_पढ़ो_strength,
	.पढ़ो_snr				= stv0367cab_पढ़ो_snr,
	.पढ़ो_ucblocks				= stv0367cab_पढ़ो_ucblcks,
	.get_tune_settings			= stv0367_get_tune_settings,
पूर्ण;

काष्ठा dvb_frontend *stv0367cab_attach(स्थिर काष्ठा stv0367_config *config,
				   काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा stv0367_state *state = शून्य;
	काष्ठा stv0367cab_state *cab_state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा stv0367_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;
	cab_state = kzalloc(माप(काष्ठा stv0367cab_state), GFP_KERNEL);
	अगर (cab_state == शून्य)
		जाओ error;

	/* setup the state */
	state->i2c = i2c;
	state->config = config;
	cab_state->search_range = 280000;
	cab_state->qamfec_status_reg = F367CAB_QAMFEC_LOCK;
	state->cab_state = cab_state;
	state->fe.ops = stv0367cab_ops;
	state->fe.demodulator_priv = state;
	state->chip_id = stv0367_पढ़ोreg(state, 0xf000);

	/* demod operation options */
	state->use_i2c_gatectrl = 1;
	state->deftअसल = STV0367_DEFTAB_GENERIC;
	state->reinit_on_setfrontend = 1;
	state->स्वतः_अगर_khz = 0;

	dprपूर्णांकk("%s: chip_id = 0x%x\n", __func__, state->chip_id);

	/* check अगर the demod is there */
	अगर ((state->chip_id != 0x50) && (state->chip_id != 0x60))
		जाओ error;

	वापस &state->fe;

error:
	kमुक्त(cab_state);
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(stv0367cab_attach);

/*
 * Functions क्रम operation on Digital Devices hardware
 */

अटल व्योम stv0367ddb_setup_ter(काष्ठा stv0367_state *state)
अणु
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT4, 0x00);
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT5, 0x00);
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT6, 0x00); /* R367CAB_CTRL_1 */
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT7, 0x00); /* R367CAB_CTRL_2 */
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT8, 0x00);
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT9, 0x00);

	/* Tuner Setup */
	/* Buffer Q disabled, I Enabled, अचिन्हित ADC */
	stv0367_ग_लिखोreg(state, R367TER_ANADIGCTRL, 0x89);
	stv0367_ग_लिखोreg(state, R367TER_DUAL_AD12, 0x04); /* ADCQ disabled */

	/* Clock setup */
	/* PLL bypassed and disabled */
	stv0367_ग_लिखोreg(state, R367TER_ANACTRL, 0x0D);
	stv0367_ग_लिखोreg(state, R367TER_TOPCTRL, 0x00); /* Set OFDM */

	/* IC runs at 54 MHz with a 27 MHz crystal */
	stv0367_pll_setup(state, STV0367_ICSPEED_53125, state->config->xtal);

	msleep(50);
	/* PLL enabled and used */
	stv0367_ग_लिखोreg(state, R367TER_ANACTRL, 0x00);

	state->activedemod = demod_ter;
पूर्ण

अटल व्योम stv0367ddb_setup_cab(काष्ठा stv0367_state *state)
अणु
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT4, 0x00);
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT5, 0x01);
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT6, 0x06); /* R367CAB_CTRL_1 */
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT7, 0x03); /* R367CAB_CTRL_2 */
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT8, 0x00);
	stv0367_ग_लिखोreg(state, R367TER_DEBUG_LT9, 0x00);

	/* Tuner Setup */
	/* Buffer Q disabled, I Enabled, चिन्हित ADC */
	stv0367_ग_लिखोreg(state, R367TER_ANADIGCTRL, 0x8B);
	/* ADCQ disabled */
	stv0367_ग_लिखोreg(state, R367TER_DUAL_AD12, 0x04);

	/* Clock setup */
	/* PLL bypassed and disabled */
	stv0367_ग_लिखोreg(state, R367TER_ANACTRL, 0x0D);
	/* Set QAM */
	stv0367_ग_लिखोreg(state, R367TER_TOPCTRL, 0x10);

	/* IC runs at 58 MHz with a 27 MHz crystal */
	stv0367_pll_setup(state, STV0367_ICSPEED_58000, state->config->xtal);

	msleep(50);
	/* PLL enabled and used */
	stv0367_ग_लिखोreg(state, R367TER_ANACTRL, 0x00);

	state->cab_state->mclk = stv0367cab_get_mclk(&state->fe,
		state->config->xtal);
	state->cab_state->adc_clk = stv0367cab_get_adc_freq(&state->fe,
		state->config->xtal);

	state->activedemod = demod_cab;
पूर्ण

अटल पूर्णांक stv0367ddb_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	चयन (fe->dtv_property_cache.delivery_प्रणाली) अणु
	हाल SYS_DVBT:
		अगर (state->activedemod != demod_ter)
			stv0367ddb_setup_ter(state);

		वापस stv0367ter_set_frontend(fe);
	हाल SYS_DVBC_ANNEX_A:
		अगर (state->activedemod != demod_cab)
			stv0367ddb_setup_cab(state);

		/* protect against भागision error oopses */
		अगर (fe->dtv_property_cache.symbol_rate == 0) अणु
			prपूर्णांकk(KERN_ERR "Invalid symbol rate\n");
			वापस -EINVAL;
		पूर्ण

		वापस stv0367cab_set_frontend(fe);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम stv0367ddb_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	s32 संकेतstrength;

	चयन (state->activedemod) अणु
	हाल demod_cab:
		संकेतstrength = stv0367cab_get_rf_lvl(state) * 1000;
		अवरोध;
	शेष:
		p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस;
	पूर्ण

	p->strength.stat[0].scale = FE_SCALE_DECIBEL;
	p->strength.stat[0].uvalue = संकेतstrength;
पूर्ण

अटल व्योम stv0367ddb_पढ़ो_snr(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	पूर्णांक cab_pwr;
	u32 regval, पंचांगpval, snrval = 0;

	चयन (state->activedemod) अणु
	हाल demod_ter:
		snrval = stv0367ter_snr_पढ़ोreg(fe);
		अवरोध;
	हाल demod_cab:
		cab_pwr = stv0367cab_snr_घातer(fe);
		regval = stv0367cab_snr_पढ़ोreg(fe, 0);

		/* prevent भागision by zero */
		अगर (!regval) अणु
			snrval = 0;
			अवरोध;
		पूर्ण

		पंचांगpval = (cab_pwr * 320) / regval;
		snrval = ((पंचांगpval != 0) ? (पूर्णांकlog2(पंचांगpval) / 5581) : 0);
		अवरोध;
	शेष:
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस;
	पूर्ण

	p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	p->cnr.stat[0].uvalue = snrval;
पूर्ण

अटल व्योम stv0367ddb_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 ucblocks = 0;

	चयन (state->activedemod) अणु
	हाल demod_ter:
		stv0367ter_पढ़ो_ucblocks(fe, &ucblocks);
		अवरोध;
	हाल demod_cab:
		stv0367cab_पढ़ो_ucblcks(fe, &ucblocks);
		अवरोध;
	शेष:
		p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		वापस;
	पूर्ण

	p->block_error.stat[0].scale = FE_SCALE_COUNTER;
	p->block_error.stat[0].uvalue = ucblocks;
पूर्ण

अटल पूर्णांक stv0367ddb_पढ़ो_status(काष्ठा dvb_frontend *fe,
				  क्रमागत fe_status *status)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	पूर्णांक ret = 0;

	चयन (state->activedemod) अणु
	हाल demod_ter:
		ret = stv0367ter_पढ़ो_status(fe, status);
		अवरोध;
	हाल demod_cab:
		ret = stv0367cab_पढ़ो_status(fe, status);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* stop and report on *_पढ़ो_status failure */
	अगर (ret)
		वापस ret;

	stv0367ddb_पढ़ो_संकेत_strength(fe);

	/* पढ़ो carrier/noise when a carrier is detected */
	अगर (*status & FE_HAS_CARRIER)
		stv0367ddb_पढ़ो_snr(fe);
	अन्यथा
		p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	/* पढ़ो uncorrected blocks on FE_HAS_LOCK */
	अगर (*status & FE_HAS_LOCK)
		stv0367ddb_पढ़ो_ucblocks(fe);
	अन्यथा
		p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367ddb_get_frontend(काष्ठा dvb_frontend *fe,
				   काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	चयन (state->activedemod) अणु
	हाल demod_ter:
		वापस stv0367ter_get_frontend(fe, p);
	हाल demod_cab:
		वापस stv0367cab_get_frontend(fe, p);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stv0367ddb_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा stv0367_state *state = fe->demodulator_priv;

	चयन (state->activedemod) अणु
	हाल demod_ter:
		state->activedemod = demod_none;
		वापस stv0367ter_sleep(fe);
	हाल demod_cab:
		state->activedemod = demod_none;
		वापस stv0367cab_sleep(fe);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक stv0367ddb_init(काष्ठा stv0367_state *state)
अणु
	काष्ठा stv0367ter_state *ter_state = state->ter_state;
	काष्ठा dtv_frontend_properties *p = &state->fe.dtv_property_cache;

	stv0367_ग_लिखोreg(state, R367TER_TOPCTRL, 0x10);

	अगर (stv0367_deftअसल[state->deftअसल][STV0367_TAB_BASE])
		stv0367_ग_लिखो_table(state,
			stv0367_deftअसल[state->deftअसल][STV0367_TAB_BASE]);

	stv0367_ग_लिखो_table(state,
		stv0367_deftअसल[state->deftअसल][STV0367_TAB_CAB]);

	stv0367_ग_लिखोreg(state, R367TER_TOPCTRL, 0x00);
	stv0367_ग_लिखो_table(state,
		stv0367_deftअसल[state->deftअसल][STV0367_TAB_TER]);

	stv0367_ग_लिखोreg(state, R367TER_GAIN_SRC1, 0x2A);
	stv0367_ग_लिखोreg(state, R367TER_GAIN_SRC2, 0xD6);
	stv0367_ग_लिखोreg(state, R367TER_INC_DEROT1, 0x55);
	stv0367_ग_लिखोreg(state, R367TER_INC_DEROT2, 0x55);
	stv0367_ग_लिखोreg(state, R367TER_TRL_CTL, 0x14);
	stv0367_ग_लिखोreg(state, R367TER_TRL_NOMRATE1, 0xAE);
	stv0367_ग_लिखोreg(state, R367TER_TRL_NOMRATE2, 0x56);
	stv0367_ग_लिखोreg(state, R367TER_FEPATH_CFG, 0x0);

	/* OFDM TS Setup */

	stv0367_ग_लिखोreg(state, R367TER_TSCFGH, 0x70);
	stv0367_ग_लिखोreg(state, R367TER_TSCFGM, 0xC0);
	stv0367_ग_लिखोreg(state, R367TER_TSCFGL, 0x20);
	stv0367_ग_लिखोreg(state, R367TER_TSSPEED, 0x40); /* Fixed at 54 MHz */

	stv0367_ग_लिखोreg(state, R367TER_TSCFGH, 0x71);
	stv0367_ग_लिखोreg(state, R367TER_TSCFGH, 0x70);

	stv0367_ग_लिखोreg(state, R367TER_TOPCTRL, 0x10);

	/* Also needed क्रम QAM */
	stv0367_ग_लिखोreg(state, R367TER_AGC12C, 0x01); /* AGC Pin setup */

	stv0367_ग_लिखोreg(state, R367TER_AGCCTRL1, 0x8A);

	/* QAM TS setup, note exact क्रमmat also depends on descrambler */
	/* settings */
	/* Inverted Clock, Swap, serial */
	stv0367_ग_लिखोreg(state, R367CAB_OUTFORMAT_0, 0x85);

	/* Clock setup (PLL bypassed and disabled) */
	stv0367_ग_लिखोreg(state, R367TER_ANACTRL, 0x0D);

	/* IC runs at 58 MHz with a 27 MHz crystal */
	stv0367_pll_setup(state, STV0367_ICSPEED_58000, state->config->xtal);

	/* Tuner setup */
	/* Buffer Q disabled, I Enabled, चिन्हित ADC */
	stv0367_ग_लिखोreg(state, R367TER_ANADIGCTRL, 0x8b);
	stv0367_ग_लिखोreg(state, R367TER_DUAL_AD12, 0x04); /* ADCQ disabled */

	/* Improves the C/N lock limit */
	stv0367_ग_लिखोreg(state, R367CAB_FSM_SNR2_HTH, 0x23);
	/* ZIF/IF Automatic mode */
	stv0367_ग_लिखोreg(state, R367CAB_IQ_QAM, 0x01);
	/* Improving burst noise perक्रमmances */
	stv0367_ग_लिखोreg(state, R367CAB_EQU_FFE_LEAKAGE, 0x83);
	/* Improving ACI perक्रमmances */
	stv0367_ग_लिखोreg(state, R367CAB_IQDEM_ADJ_EN, 0x05);

	/* PLL enabled and used */
	stv0367_ग_लिखोreg(state, R367TER_ANACTRL, 0x00);

	stv0367_ग_लिखोreg(state, R367TER_I2CRPT, (0x08 | ((5 & 0x07) << 4)));

	ter_state->pBER = 0;
	ter_state->first_lock = 0;
	ter_state->unlock_counter = 2;

	p->strength.len = 1;
	p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->cnr.len = 1;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_error.len = 1;
	p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops stv0367ddb_ops = अणु
	.delsys = अणु SYS_DVBC_ANNEX_A, SYS_DVBT पूर्ण,
	.info = अणु
		.name			= "ST STV0367 DDB DVB-C/T",
		.frequency_min_hz	=  47 * MHz,
		.frequency_max_hz	= 865 * MHz,
		.frequency_stepsize_hz	= 166667,
		.symbol_rate_min	= 870000,
		.symbol_rate_max	= 11700000,
		.caps = /* DVB-C */
			0x400 |/* FE_CAN_QAM_4 */
			FE_CAN_QAM_16 | FE_CAN_QAM_32  |
			FE_CAN_QAM_64 | FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			/* DVB-T */
			FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_QPSK | FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_RECOVER | FE_CAN_INVERSION_AUTO |
			FE_CAN_MUTE_TS
	पूर्ण,
	.release = stv0367_release,
	.sleep = stv0367ddb_sleep,
	.i2c_gate_ctrl = stv0367cab_gate_ctrl, /* valid क्रम TER and CAB */
	.set_frontend = stv0367ddb_set_frontend,
	.get_frontend = stv0367ddb_get_frontend,
	.get_tune_settings = stv0367_get_tune_settings,
	.पढ़ो_status = stv0367ddb_पढ़ो_status,
पूर्ण;

काष्ठा dvb_frontend *stv0367ddb_attach(स्थिर काष्ठा stv0367_config *config,
				   काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा stv0367_state *state = शून्य;
	काष्ठा stv0367ter_state *ter_state = शून्य;
	काष्ठा stv0367cab_state *cab_state = शून्य;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा stv0367_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;
	ter_state = kzalloc(माप(काष्ठा stv0367ter_state), GFP_KERNEL);
	अगर (ter_state == शून्य)
		जाओ error;
	cab_state = kzalloc(माप(काष्ठा stv0367cab_state), GFP_KERNEL);
	अगर (cab_state == शून्य)
		जाओ error;

	/* setup the state */
	state->i2c = i2c;
	state->config = config;
	state->ter_state = ter_state;
	cab_state->search_range = 280000;
	cab_state->qamfec_status_reg = F367CAB_DESCR_SYNCSTATE;
	state->cab_state = cab_state;
	state->fe.ops = stv0367ddb_ops;
	state->fe.demodulator_priv = state;
	state->chip_id = stv0367_पढ़ोreg(state, R367TER_ID);

	/* demod operation options */
	state->use_i2c_gatectrl = 0;
	state->deftअसल = STV0367_DEFTAB_DDB;
	state->reinit_on_setfrontend = 0;
	state->स्वतः_अगर_khz = 1;
	state->activedemod = demod_none;

	dprपूर्णांकk("%s: chip_id = 0x%x\n", __func__, state->chip_id);

	/* check अगर the demod is there */
	अगर ((state->chip_id != 0x50) && (state->chip_id != 0x60))
		जाओ error;

	dev_info(&i2c->dev, "Found %s with ChipID %02X at adr %02X\n",
		state->fe.ops.info.name, state->chip_id,
		config->demod_address);

	stv0367ddb_init(state);

	वापस &state->fe;

error:
	kमुक्त(cab_state);
	kमुक्त(ter_state);
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(stv0367ddb_attach);

MODULE_PARM_DESC(debug, "Set debug");
MODULE_PARM_DESC(i2c_debug, "Set i2c debug");

MODULE_AUTHOR("Igor M. Liplianin");
MODULE_DESCRIPTION("ST STV0367 DVB-C/T demodulator driver");
MODULE_LICENSE("GPL");
