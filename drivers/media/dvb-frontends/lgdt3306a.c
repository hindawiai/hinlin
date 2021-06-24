<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Support क्रम LGDT3306A - 8VSB/QAM-B
 *
 *    Copyright (C) 2013 Fred Richter <frichter@hauppauge.com>
 *    - driver काष्ठाure based on lgdt3305.[ch] by Michael Krufky
 *    - code based on LG3306_V0.35 API by LG Electronics Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <यंत्र/भाग64.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_गणित.स>
#समावेश "lgdt3306a.h"
#समावेश <linux/i2c-mux.h>


अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debug level (info=1, reg=2 (or-able))");

/*
 * Older drivers treated QAM64 and QAM256 the same; that is the HW always
 * used "Auto" mode during detection.  Setting "forced_manual"=1 allows
 * the user to treat these modes as separate.  For backwards compatibility,
 * it's off by शेष.  QAM_AUTO can now be specअगरied to achive that
 * effect even अगर "forced_manual"=1
 */
अटल पूर्णांक क्रमced_manual;
module_param(क्रमced_manual, पूर्णांक, 0644);
MODULE_PARM_DESC(क्रमced_manual, "if set, QAM64 and QAM256 will only lock to modulation specified");

#घोषणा DBG_INFO 1
#घोषणा DBG_REG  2
#घोषणा DBG_DUMP 4 /* FGR - comment out to हटाओ dump code */

#घोषणा lg_debug(fmt, arg...) \
	prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ## arg)

#घोषणा dbg_info(fmt, arg...)					\
	करो अणु							\
		अगर (debug & DBG_INFO)				\
			lg_debug(fmt, ## arg);			\
	पूर्ण जबतक (0)

#घोषणा dbg_reg(fmt, arg...)					\
	करो अणु							\
		अगर (debug & DBG_REG)				\
			lg_debug(fmt, ## arg);			\
	पूर्ण जबतक (0)

#घोषणा lg_chkerr(ret)							\
(अणु									\
	पूर्णांक __ret;							\
	__ret = (ret < 0);						\
	अगर (__ret)							\
		pr_err("error %d on line %d\n",	ret, __LINE__);		\
	__ret;								\
पूर्ण)

काष्ठा lgdt3306a_state अणु
	काष्ठा i2c_adapter *i2c_adap;
	स्थिर काष्ठा lgdt3306a_config *cfg;

	काष्ठा dvb_frontend frontend;

	क्रमागत fe_modulation current_modulation;
	u32 current_frequency;
	u32 snr;

	काष्ठा i2c_mux_core *muxc;
पूर्ण;

/*
 * LG3306A Register Usage
 *  (LG करोes not really name the रेजिस्टरs, so this code करोes not either)
 *
 * 0000 -> 00FF Common control and status
 * 1000 -> 10FF Synchronizer control and status
 * 1F00 -> 1FFF Smart Antenna control and status
 * 2100 -> 21FF VSB Equalizer control and status
 * 2800 -> 28FF QAM Equalizer control and status
 * 3000 -> 30FF FEC control and status
 */

क्रमागत lgdt3306a_lock_status अणु
	LG3306_UNLOCK       = 0x00,
	LG3306_LOCK         = 0x01,
	LG3306_UNKNOWN_LOCK = 0xff
पूर्ण;

क्रमागत lgdt3306a_neverlock_status अणु
	LG3306_NL_INIT    = 0x00,
	LG3306_NL_PROCESS = 0x01,
	LG3306_NL_LOCK    = 0x02,
	LG3306_NL_FAIL    = 0x03,
	LG3306_NL_UNKNOWN = 0xff
पूर्ण;

क्रमागत lgdt3306a_modulation अणु
	LG3306_VSB          = 0x00,
	LG3306_QAM64        = 0x01,
	LG3306_QAM256       = 0x02,
	LG3306_UNKNOWN_MODE = 0xff
पूर्ण;

क्रमागत lgdt3306a_lock_check अणु
	LG3306_SYNC_LOCK,
	LG3306_FEC_LOCK,
	LG3306_TR_LOCK,
	LG3306_AGC_LOCK,
पूर्ण;


#अगर_घोषित DBG_DUMP
अटल व्योम lgdt3306a_DumpAllRegs(काष्ठा lgdt3306a_state *state);
अटल व्योम lgdt3306a_DumpRegs(काष्ठा lgdt3306a_state *state);
#पूर्ण_अगर


अटल पूर्णांक lgdt3306a_ग_लिखो_reg(काष्ठा lgdt3306a_state *state, u16 reg, u8 val)
अणु
	पूर्णांक ret;
	u8 buf[] = अणु reg >> 8, reg & 0xff, val पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = state->cfg->i2c_addr, .flags = 0,
		.buf = buf, .len = 3,
	पूर्ण;

	dbg_reg("reg: 0x%04x, val: 0x%02x\n", reg, val);

	ret = i2c_transfer(state->i2c_adap, &msg, 1);

	अगर (ret != 1) अणु
		pr_err("error (addr %02x %02x <- %02x, err = %i)\n",
		       msg.buf[0], msg.buf[1], msg.buf[2], ret);
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3306a_पढ़ो_reg(काष्ठा lgdt3306a_state *state, u16 reg, u8 *val)
अणु
	पूर्णांक ret;
	u8 reg_buf[] = अणु reg >> 8, reg & 0xff पूर्ण;
	काष्ठा i2c_msg msg[] = अणु
		अणु .addr = state->cfg->i2c_addr,
		  .flags = 0, .buf = reg_buf, .len = 2 पूर्ण,
		अणु .addr = state->cfg->i2c_addr,
		  .flags = I2C_M_RD, .buf = val, .len = 1 पूर्ण,
	पूर्ण;

	ret = i2c_transfer(state->i2c_adap, msg, 2);

	अगर (ret != 2) अणु
		pr_err("error (addr %02x reg %04x error (ret == %i)\n",
		       state->cfg->i2c_addr, reg, ret);
		अगर (ret < 0)
			वापस ret;
		अन्यथा
			वापस -EREMOTEIO;
	पूर्ण
	dbg_reg("reg: 0x%04x, val: 0x%02x\n", reg, *val);

	वापस 0;
पूर्ण

#घोषणा पढ़ो_reg(state, reg)						\
(अणु									\
	u8 __val;							\
	पूर्णांक ret = lgdt3306a_पढ़ो_reg(state, reg, &__val);		\
	अगर (lg_chkerr(ret))						\
		__val = 0;						\
	__val;								\
पूर्ण)

अटल पूर्णांक lgdt3306a_set_reg_bit(काष्ठा lgdt3306a_state *state,
				u16 reg, पूर्णांक bit, पूर्णांक onoff)
अणु
	u8 val;
	पूर्णांक ret;

	dbg_reg("reg: 0x%04x, bit: %d, level: %d\n", reg, bit, onoff);

	ret = lgdt3306a_पढ़ो_reg(state, reg, &val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	val &= ~(1 << bit);
	val |= (onoff & 1) << bit;

	ret = lgdt3306a_ग_लिखो_reg(state, reg, val);
	lg_chkerr(ret);
fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3306a_soft_reset(काष्ठा lgdt3306a_state *state)
अणु
	पूर्णांक ret;

	dbg_info("\n");

	ret = lgdt3306a_set_reg_bit(state, 0x0000, 7, 0);
	अगर (lg_chkerr(ret))
		जाओ fail;

	msleep(20);
	ret = lgdt3306a_set_reg_bit(state, 0x0000, 7, 1);
	lg_chkerr(ret);

fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_mpeg_mode(काष्ठा lgdt3306a_state *state,
				     क्रमागत lgdt3306a_mpeg_mode mode)
अणु
	u8 val;
	पूर्णांक ret;

	dbg_info("(%d)\n", mode);
	/* transport packet क्रमmat - TPSENB=0x80 */
	ret = lgdt3306a_set_reg_bit(state, 0x0071, 7,
				     mode == LGDT3306A_MPEG_PARALLEL ? 1 : 0);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/*
	 * start of packet संकेत duration
	 * TPSSOPBITEN=0x40; 0=byte duration, 1=bit duration
	 */
	ret = lgdt3306a_set_reg_bit(state, 0x0071, 6, 0);
	अगर (lg_chkerr(ret))
		जाओ fail;

	ret = lgdt3306a_पढ़ो_reg(state, 0x0070, &val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	val |= 0x10; /* TPCLKSUPB=0x10 */

	अगर (mode == LGDT3306A_MPEG_PARALLEL)
		val &= ~0x10;

	ret = lgdt3306a_ग_लिखो_reg(state, 0x0070, val);
	lg_chkerr(ret);

fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_mpeg_mode_polarity(काष्ठा lgdt3306a_state *state,
				       क्रमागत lgdt3306a_tp_घड़ी_edge edge,
				       क्रमागत lgdt3306a_tp_valid_polarity valid)
अणु
	u8 val;
	पूर्णांक ret;

	dbg_info("edge=%d, valid=%d\n", edge, valid);

	ret = lgdt3306a_पढ़ो_reg(state, 0x0070, &val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	val &= ~0x06; /* TPCLKPOL=0x04, TPVALPOL=0x02 */

	अगर (edge == LGDT3306A_TPCLK_RISING_EDGE)
		val |= 0x04;
	अगर (valid == LGDT3306A_TP_VALID_HIGH)
		val |= 0x02;

	ret = lgdt3306a_ग_लिखो_reg(state, 0x0070, val);
	lg_chkerr(ret);

fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_mpeg_tristate(काष्ठा lgdt3306a_state *state,
				     पूर्णांक mode)
अणु
	u8 val;
	पूर्णांक ret;

	dbg_info("(%d)\n", mode);

	अगर (mode) अणु
		ret = lgdt3306a_पढ़ो_reg(state, 0x0070, &val);
		अगर (lg_chkerr(ret))
			जाओ fail;
		/*
		 * Tristate bus; TPOUTEN=0x80, TPCLKOUTEN=0x20,
		 * TPDATAOUTEN=0x08
		 */
		val &= ~0xa8;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x0070, val);
		अगर (lg_chkerr(ret))
			जाओ fail;

		/* AGCIFOUTENB=0x40; 1=Disable IFAGC pin */
		ret = lgdt3306a_set_reg_bit(state, 0x0003, 6, 1);
		अगर (lg_chkerr(ret))
			जाओ fail;

	पूर्ण अन्यथा अणु
		/* enable IFAGC pin */
		ret = lgdt3306a_set_reg_bit(state, 0x0003, 6, 0);
		अगर (lg_chkerr(ret))
			जाओ fail;

		ret = lgdt3306a_पढ़ो_reg(state, 0x0070, &val);
		अगर (lg_chkerr(ret))
			जाओ fail;

		val |= 0xa8; /* enable bus */
		ret = lgdt3306a_ग_लिखो_reg(state, 0x0070, val);
		अगर (lg_chkerr(ret))
			जाओ fail;
	पूर्ण

fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_ts_bus_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक acquire)
अणु
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;

	dbg_info("acquire=%d\n", acquire);

	वापस lgdt3306a_mpeg_tristate(state, acquire ? 0 : 1);

पूर्ण

अटल पूर्णांक lgdt3306a_घातer(काष्ठा lgdt3306a_state *state,
				     पूर्णांक mode)
अणु
	पूर्णांक ret;

	dbg_info("(%d)\n", mode);

	अगर (mode == 0) अणु
		/* पूर्णांकo reset */
		ret = lgdt3306a_set_reg_bit(state, 0x0000, 7, 0);
		अगर (lg_chkerr(ret))
			जाओ fail;

		/* घातer करोwn */
		ret = lgdt3306a_set_reg_bit(state, 0x0000, 0, 0);
		अगर (lg_chkerr(ret))
			जाओ fail;

	पूर्ण अन्यथा अणु
		/* out of reset */
		ret = lgdt3306a_set_reg_bit(state, 0x0000, 7, 1);
		अगर (lg_chkerr(ret))
			जाओ fail;

		/* घातer up */
		ret = lgdt3306a_set_reg_bit(state, 0x0000, 0, 1);
		अगर (lg_chkerr(ret))
			जाओ fail;
	पूर्ण

#अगर_घोषित DBG_DUMP
	lgdt3306a_DumpAllRegs(state);
#पूर्ण_अगर
fail:
	वापस ret;
पूर्ण


अटल पूर्णांक lgdt3306a_set_vsb(काष्ठा lgdt3306a_state *state)
अणु
	u8 val;
	पूर्णांक ret;

	dbg_info("\n");

	/* 0. Spectrum inversion detection manual; spectrum inverted */
	ret = lgdt3306a_पढ़ो_reg(state, 0x0002, &val);
	val &= 0xf7; /* SPECINVAUTO Off */
	val |= 0x04; /* SPECINV On */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0002, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 1. Selection of standard mode(0x08=QAM, 0x80=VSB) */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0008, 0x80);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 2. Bandwidth mode क्रम VSB(6MHz) */
	ret = lgdt3306a_पढ़ो_reg(state, 0x0009, &val);
	val &= 0xe3;
	val |= 0x0c; /* STDOPDETTMODE[2:0]=3 */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0009, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 3. QAM mode detection mode(None) */
	ret = lgdt3306a_पढ़ो_reg(state, 0x0009, &val);
	val &= 0xfc; /* STDOPDETCMODE[1:0]=0 */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0009, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 4. ADC sampling frequency rate(2x sampling) */
	ret = lgdt3306a_पढ़ो_reg(state, 0x000d, &val);
	val &= 0xbf; /* SAMPLING4XFEN=0 */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x000d, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

#अगर 0
	/* FGR - disable any AICC filtering, testing only */

	ret = lgdt3306a_ग_लिखो_reg(state, 0x0024, 0x00);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* AICCFIXFREQ0 NT N-1(Video rejection) */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002e, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002f, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0030, 0x00);

	/* AICCFIXFREQ1 NT N-1(Audio rejection) */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002b, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002c, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002d, 0x00);

	/* AICCFIXFREQ2 NT Co-Channel(Video rejection) */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0028, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0029, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002a, 0x00);

	/* AICCFIXFREQ3 NT Co-Channel(Audio rejection) */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0025, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0026, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0027, 0x00);

#अन्यथा
	/* FGR - this works well क्रम HVR-1955,1975 */

	/* 5. AICCOPMODE  NT N-1 Adj. */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0024, 0x5A);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* AICCFIXFREQ0 NT N-1(Video rejection) */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002e, 0x5A);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002f, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0030, 0x00);

	/* AICCFIXFREQ1 NT N-1(Audio rejection) */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002b, 0x36);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002c, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002d, 0x00);

	/* AICCFIXFREQ2 NT Co-Channel(Video rejection) */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0028, 0x2A);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0029, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x002a, 0x00);

	/* AICCFIXFREQ3 NT Co-Channel(Audio rejection) */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0025, 0x06);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0026, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0027, 0x00);
#पूर्ण_अगर

	ret = lgdt3306a_पढ़ो_reg(state, 0x001e, &val);
	val &= 0x0f;
	val |= 0xa0;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x001e, val);

	ret = lgdt3306a_ग_लिखो_reg(state, 0x0022, 0x08);

	ret = lgdt3306a_ग_लिखो_reg(state, 0x0023, 0xFF);

	ret = lgdt3306a_पढ़ो_reg(state, 0x211f, &val);
	val &= 0xef;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x211f, val);

	ret = lgdt3306a_ग_लिखो_reg(state, 0x2173, 0x01);

	ret = lgdt3306a_पढ़ो_reg(state, 0x1061, &val);
	val &= 0xf8;
	val |= 0x04;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x1061, val);

	ret = lgdt3306a_पढ़ो_reg(state, 0x103d, &val);
	val &= 0xcf;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x103d, val);

	ret = lgdt3306a_ग_लिखो_reg(state, 0x2122, 0x40);

	ret = lgdt3306a_पढ़ो_reg(state, 0x2141, &val);
	val &= 0x3f;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x2141, val);

	ret = lgdt3306a_पढ़ो_reg(state, 0x2135, &val);
	val &= 0x0f;
	val |= 0x70;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x2135, val);

	ret = lgdt3306a_पढ़ो_reg(state, 0x0003, &val);
	val &= 0xf7;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0003, val);

	ret = lgdt3306a_पढ़ो_reg(state, 0x001c, &val);
	val &= 0x7f;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x001c, val);

	/* 6. EQ step size */
	ret = lgdt3306a_पढ़ो_reg(state, 0x2179, &val);
	val &= 0xf8;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x2179, val);

	ret = lgdt3306a_पढ़ो_reg(state, 0x217a, &val);
	val &= 0xf8;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x217a, val);

	/* 7. Reset */
	ret = lgdt3306a_soft_reset(state);
	अगर (lg_chkerr(ret))
		जाओ fail;

	dbg_info("complete\n");
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_set_qam(काष्ठा lgdt3306a_state *state, पूर्णांक modulation)
अणु
	u8 val;
	पूर्णांक ret;

	dbg_info("modulation=%d\n", modulation);

	/* 1. Selection of standard mode(0x08=QAM, 0x80=VSB) */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0008, 0x08);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 1a. Spectrum inversion detection to Auto */
	ret = lgdt3306a_पढ़ो_reg(state, 0x0002, &val);
	val &= 0xfb; /* SPECINV Off */
	val |= 0x08; /* SPECINVAUTO On */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0002, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 2. Bandwidth mode क्रम QAM */
	ret = lgdt3306a_पढ़ो_reg(state, 0x0009, &val);
	val &= 0xe3; /* STDOPDETTMODE[2:0]=0 VSB Off */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0009, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 3. : 64QAM/256QAM detection(manual, स्वतः) */
	ret = lgdt3306a_पढ़ो_reg(state, 0x0009, &val);
	val &= 0xfc;
	/* Check क्रम क्रमced Manual modulation modes; otherwise always "auto" */
	अगर(क्रमced_manual && (modulation != QAM_AUTO))अणु
		val |= 0x01; /* STDOPDETCMODE[1:0]= 1=Manual */
	पूर्ण अन्यथा अणु
		val |= 0x02; /* STDOPDETCMODE[1:0]= 2=Auto */
	पूर्ण
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0009, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 3a. : 64QAM/256QAM selection क्रम manual */
	ret = lgdt3306a_पढ़ो_reg(state, 0x101a, &val);
	val &= 0xf8;
	अगर (modulation == QAM_64)
		val |= 0x02; /* QMDQMODE[2:0]=2=QAM64 */
	अन्यथा
		val |= 0x04; /* QMDQMODE[2:0]=4=QAM256 */

	ret = lgdt3306a_ग_लिखो_reg(state, 0x101a, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 4. ADC sampling frequency rate(4x sampling) */
	ret = lgdt3306a_पढ़ो_reg(state, 0x000d, &val);
	val &= 0xbf;
	val |= 0x40; /* SAMPLING4XFEN=1 */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x000d, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 5. No AICC operation in QAM mode */
	ret = lgdt3306a_पढ़ो_reg(state, 0x0024, &val);
	val &= 0x00;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0024, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 5.1 V0.36 SRDCHKALWAYS : For better QAM detection */
	ret = lgdt3306a_पढ़ो_reg(state, 0x000a, &val);
	val &= 0xfd;
	val |= 0x02;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x000a, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 5.2 V0.36 Control of "no signal" detector function */
	ret = lgdt3306a_पढ़ो_reg(state, 0x2849, &val);
	val &= 0xdf;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x2849, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 5.3 Fix क्रम Blonder Tongue HDE-2H-QAM and AQM modulators */
	ret = lgdt3306a_पढ़ो_reg(state, 0x302b, &val);
	val &= 0x7f;  /* SELFSYNCFINDEN_CQS=0; disable स्वतः reset */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x302b, val);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 6. Reset */
	ret = lgdt3306a_soft_reset(state);
	अगर (lg_chkerr(ret))
		जाओ fail;

	dbg_info("complete\n");
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_set_modulation(काष्ठा lgdt3306a_state *state,
				   काष्ठा dtv_frontend_properties *p)
अणु
	पूर्णांक ret;

	dbg_info("\n");

	चयन (p->modulation) अणु
	हाल VSB_8:
		ret = lgdt3306a_set_vsb(state);
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
	हाल QAM_AUTO:
		ret = lgdt3306a_set_qam(state, p->modulation);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (lg_chkerr(ret))
		जाओ fail;

	state->current_modulation = p->modulation;

fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3306a_agc_setup(काष्ठा lgdt3306a_state *state,
			      काष्ठा dtv_frontend_properties *p)
अणु
	/* TODO: anything we want to करो here??? */
	dbg_info("\n");

	चयन (p->modulation) अणु
	हाल VSB_8:
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
	हाल QAM_AUTO:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3306a_set_inversion(काष्ठा lgdt3306a_state *state,
				       पूर्णांक inversion)
अणु
	पूर्णांक ret;

	dbg_info("(%d)\n", inversion);

	ret = lgdt3306a_set_reg_bit(state, 0x0002, 2, inversion ? 1 : 0);
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_set_inversion_स्वतः(काष्ठा lgdt3306a_state *state,
				       पूर्णांक enabled)
अणु
	पूर्णांक ret;

	dbg_info("(%d)\n", enabled);

	/* 0=Manual 1=Auto(QAM only) - SPECINVAUTO=0x04 */
	ret = lgdt3306a_set_reg_bit(state, 0x0002, 3, enabled);
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_set_अगर(काष्ठा lgdt3306a_state *state,
			   काष्ठा dtv_frontend_properties *p)
अणु
	पूर्णांक ret;
	u16 अगर_freq_khz;
	u8 nco1, nco2;

	चयन (p->modulation) अणु
	हाल VSB_8:
		अगर_freq_khz = state->cfg->vsb_अगर_khz;
		अवरोध;
	हाल QAM_64:
	हाल QAM_256:
	हाल QAM_AUTO:
		अगर_freq_khz = state->cfg->qam_अगर_khz;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (अगर_freq_khz) अणु
	शेष:
		pr_warn("IF=%d KHz is not supported, 3250 assumed\n",
			अगर_freq_khz);
		fallthrough;
	हाल 3250: /* 3.25Mhz */
		nco1 = 0x34;
		nco2 = 0x00;
		अवरोध;
	हाल 3500: /* 3.50Mhz */
		nco1 = 0x38;
		nco2 = 0x00;
		अवरोध;
	हाल 4000: /* 4.00Mhz */
		nco1 = 0x40;
		nco2 = 0x00;
		अवरोध;
	हाल 5000: /* 5.00Mhz */
		nco1 = 0x50;
		nco2 = 0x00;
		अवरोध;
	हाल 5380: /* 5.38Mhz */
		nco1 = 0x56;
		nco2 = 0x14;
		अवरोध;
	पूर्ण
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0010, nco1);
	अगर (ret)
		वापस ret;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0011, nco2);
	अगर (ret)
		वापस ret;

	dbg_info("if_freq=%d KHz->[%04x]\n", अगर_freq_khz, nco1<<8 | nco2);

	वापस 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3306a_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;

	अगर (state->cfg->deny_i2c_rptr) अणु
		dbg_info("deny_i2c_rptr=%d\n", state->cfg->deny_i2c_rptr);
		वापस 0;
	पूर्ण
	dbg_info("(%d)\n", enable);

	/* NI2CRPTEN=0x80 */
	वापस lgdt3306a_set_reg_bit(state, 0x0002, 7, enable ? 0 : 1);
पूर्ण

अटल पूर्णांक lgdt3306a_sleep(काष्ठा lgdt3306a_state *state)
अणु
	पूर्णांक ret;

	dbg_info("\n");
	state->current_frequency = -1; /* क्रमce re-tune, when we wake */

	ret = lgdt3306a_mpeg_tristate(state, 1); /* disable data bus */
	अगर (lg_chkerr(ret))
		जाओ fail;

	ret = lgdt3306a_घातer(state, 0); /* घातer करोwn */
	lg_chkerr(ret);

fail:
	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3306a_fe_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;

	वापस lgdt3306a_sleep(state);
पूर्ण

अटल पूर्णांक lgdt3306a_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 val;
	पूर्णांक ret;

	dbg_info("\n");

	/* 1. Normal operation mode */
	ret = lgdt3306a_set_reg_bit(state, 0x0001, 0, 1); /* SIMFASTENB=0x01 */
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 2. Spectrum inversion स्वतः detection (Not valid क्रम VSB) */
	ret = lgdt3306a_set_inversion_स्वतः(state, 0);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 3. Spectrum inversion(According to the tuner configuration) */
	ret = lgdt3306a_set_inversion(state, 1);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 4. Peak-to-peak voltage of ADC input संकेत */

	/* ADCSEL1V=0x80=1Vpp; 0x00=2Vpp */
	ret = lgdt3306a_set_reg_bit(state, 0x0004, 7, 1);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 5. ADC output data capture घड़ी phase */

	/* 0=same phase as ADC घड़ी */
	ret = lgdt3306a_set_reg_bit(state, 0x0004, 2, 0);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 5a. ADC sampling घड़ी source */

	/* ADCCLKPLLSEL=0x08; 0=use ext घड़ी, not PLL */
	ret = lgdt3306a_set_reg_bit(state, 0x0004, 3, 0);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* 6. Automatic PLL set */

	/* PLLSETAUTO=0x40; 0=off */
	ret = lgdt3306a_set_reg_bit(state, 0x0005, 6, 0);
	अगर (lg_chkerr(ret))
		जाओ fail;

	अगर (state->cfg->xtalMHz == 24) अणु	/* 24MHz */
		/* 7. Frequency क्रम PLL output(0x2564 क्रम 192MHz क्रम 24MHz) */
		ret = lgdt3306a_पढ़ो_reg(state, 0x0005, &val);
		अगर (lg_chkerr(ret))
			जाओ fail;
		val &= 0xc0;
		val |= 0x25;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x0005, val);
		अगर (lg_chkerr(ret))
			जाओ fail;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x0006, 0x64);
		अगर (lg_chkerr(ret))
			जाओ fail;

		/* 8. ADC sampling frequency(0x180000 क्रम 24MHz sampling) */
		ret = lgdt3306a_पढ़ो_reg(state, 0x000d, &val);
		अगर (lg_chkerr(ret))
			जाओ fail;
		val &= 0xc0;
		val |= 0x18;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x000d, val);
		अगर (lg_chkerr(ret))
			जाओ fail;

	पूर्ण अन्यथा अगर (state->cfg->xtalMHz == 25) अणु /* 25MHz */
		/* 7. Frequency क्रम PLL output */
		ret = lgdt3306a_पढ़ो_reg(state, 0x0005, &val);
		अगर (lg_chkerr(ret))
			जाओ fail;
		val &= 0xc0;
		val |= 0x25;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x0005, val);
		अगर (lg_chkerr(ret))
			जाओ fail;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x0006, 0x64);
		अगर (lg_chkerr(ret))
			जाओ fail;

		/* 8. ADC sampling frequency(0x190000 क्रम 25MHz sampling) */
		ret = lgdt3306a_पढ़ो_reg(state, 0x000d, &val);
		अगर (lg_chkerr(ret))
			जाओ fail;
		val &= 0xc0;
		val |= 0x19;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x000d, val);
		अगर (lg_chkerr(ret))
			जाओ fail;
	पूर्ण अन्यथा अणु
		pr_err("Bad xtalMHz=%d\n", state->cfg->xtalMHz);
	पूर्ण
#अगर 0
	ret = lgdt3306a_ग_लिखो_reg(state, 0x000e, 0x00);
	ret = lgdt3306a_ग_लिखो_reg(state, 0x000f, 0x00);
#पूर्ण_अगर

	/* 9. Center frequency of input संकेत of ADC */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0010, 0x34); /* 3.25MHz */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0011, 0x00);

	/* 10. Fixed gain error value */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0014, 0); /* gain error=0 */

	/* 10a. VSB TR BW gear shअगरt initial step */
	ret = lgdt3306a_पढ़ो_reg(state, 0x103c, &val);
	val &= 0x0f;
	val |= 0x20; /* SAMGSAUTOSTL_V[3:0] = 2 */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x103c, val);

	/* 10b. Timing offset calibration in low temperature क्रम VSB */
	ret = lgdt3306a_पढ़ो_reg(state, 0x103d, &val);
	val &= 0xfc;
	val |= 0x03;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x103d, val);

	/* 10c. Timing offset calibration in low temperature क्रम QAM */
	ret = lgdt3306a_पढ़ो_reg(state, 0x1036, &val);
	val &= 0xf0;
	val |= 0x0c;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x1036, val);

	/* 11. Using the imaginary part of CIR in CIR loading */
	ret = lgdt3306a_पढ़ो_reg(state, 0x211f, &val);
	val &= 0xef; /* करो not use imaginary of CIR */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x211f, val);

	/* 12. Control of no संकेत detector function */
	ret = lgdt3306a_पढ़ो_reg(state, 0x2849, &val);
	val &= 0xef; /* NOUSENOSIGDET=0, enable no संकेत detector */
	ret = lgdt3306a_ग_लिखो_reg(state, 0x2849, val);

	/* FGR - put demod in some known mode */
	ret = lgdt3306a_set_vsb(state);

	/* 13. TP stream क्रमmat */
	ret = lgdt3306a_mpeg_mode(state, state->cfg->mpeg_mode);

	/* 14. disable output buses */
	ret = lgdt3306a_mpeg_tristate(state, 1);

	/* 15. Sleep (in reset) */
	ret = lgdt3306a_sleep(state);
	lg_chkerr(ret);

	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_set_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;
	पूर्णांक ret;

	dbg_info("(%d, %d)\n", p->frequency, p->modulation);

	अगर (state->current_frequency  == p->frequency &&
	   state->current_modulation == p->modulation) अणु
		dbg_info(" (already set, skipping ...)\n");
		वापस 0;
	पूर्ण
	state->current_frequency = -1;
	state->current_modulation = -1;

	ret = lgdt3306a_घातer(state, 1); /* घातer up */
	अगर (lg_chkerr(ret))
		जाओ fail;

	अगर (fe->ops.tuner_ops.set_params) अणु
		ret = fe->ops.tuner_ops.set_params(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
#अगर 0
		अगर (lg_chkerr(ret))
			जाओ fail;
		state->current_frequency = p->frequency;
#पूर्ण_अगर
	पूर्ण

	ret = lgdt3306a_set_modulation(state, p);
	अगर (lg_chkerr(ret))
		जाओ fail;

	ret = lgdt3306a_agc_setup(state, p);
	अगर (lg_chkerr(ret))
		जाओ fail;

	ret = lgdt3306a_set_अगर(state, p);
	अगर (lg_chkerr(ret))
		जाओ fail;

	/* spectral_inversion शेषs alपढ़ोy set क्रम VSB and QAM */

	ret = lgdt3306a_mpeg_mode(state, state->cfg->mpeg_mode);
	अगर (lg_chkerr(ret))
		जाओ fail;

	ret = lgdt3306a_mpeg_mode_polarity(state,
					  state->cfg->tpclk_edge,
					  state->cfg->tpvalid_polarity);
	अगर (lg_chkerr(ret))
		जाओ fail;

	ret = lgdt3306a_mpeg_tristate(state, 0); /* enable data bus */
	अगर (lg_chkerr(ret))
		जाओ fail;

	ret = lgdt3306a_soft_reset(state);
	अगर (lg_chkerr(ret))
		जाओ fail;

#अगर_घोषित DBG_DUMP
	lgdt3306a_DumpAllRegs(state);
#पूर्ण_अगर
	state->current_frequency = p->frequency;
fail:
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_get_frontend(काष्ठा dvb_frontend *fe,
				  काष्ठा dtv_frontend_properties *p)
अणु
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;

	dbg_info("(%u, %d)\n",
		 state->current_frequency, state->current_modulation);

	p->modulation = state->current_modulation;
	p->frequency = state->current_frequency;
	वापस 0;
पूर्ण

अटल क्रमागत dvbfe_algo lgdt3306a_get_frontend_algo(काष्ठा dvb_frontend *fe)
अणु
#अगर 1
	वापस DVBFE_ALGO_CUSTOM;
#अन्यथा
	वापस DVBFE_ALGO_HW;
#पूर्ण_अगर
पूर्ण

/* ------------------------------------------------------------------------ */
अटल पूर्णांक lgdt3306a_monitor_vsb(काष्ठा lgdt3306a_state *state)
अणु
	u8 val;
	पूर्णांक ret;
	u8 snrRef, maxPowerMan, nCombDet;
	u16 fbDlyCir;

	ret = lgdt3306a_पढ़ो_reg(state, 0x21a1, &val);
	अगर (ret)
		वापस ret;
	snrRef = val & 0x3f;

	ret = lgdt3306a_पढ़ो_reg(state, 0x2185, &maxPowerMan);
	अगर (ret)
		वापस ret;

	ret = lgdt3306a_पढ़ो_reg(state, 0x2191, &val);
	अगर (ret)
		वापस ret;
	nCombDet = (val & 0x80) >> 7;

	ret = lgdt3306a_पढ़ो_reg(state, 0x2180, &val);
	अगर (ret)
		वापस ret;
	fbDlyCir = (val & 0x03) << 8;

	ret = lgdt3306a_पढ़ो_reg(state, 0x2181, &val);
	अगर (ret)
		वापस ret;
	fbDlyCir |= val;

	dbg_info("snrRef=%d maxPowerMan=0x%x nCombDet=%d fbDlyCir=0x%x\n",
		snrRef, maxPowerMan, nCombDet, fbDlyCir);

	/* Carrier offset sub loop bandwidth */
	ret = lgdt3306a_पढ़ो_reg(state, 0x1061, &val);
	अगर (ret)
		वापस ret;
	val &= 0xf8;
	अगर ((snrRef > 18) && (maxPowerMan > 0x68)
	    && (nCombDet == 0x01)
	    && ((fbDlyCir == 0x03FF) || (fbDlyCir < 0x6C))) अणु
		/* SNR is over 18dB and no ghosting */
		val |= 0x00; /* final bandwidth = 0 */
	पूर्ण अन्यथा अणु
		val |= 0x04; /* final bandwidth = 4 */
	पूर्ण
	ret = lgdt3306a_ग_लिखो_reg(state, 0x1061, val);
	अगर (ret)
		वापस ret;

	/* Adjust Notch Filter */
	ret = lgdt3306a_पढ़ो_reg(state, 0x0024, &val);
	अगर (ret)
		वापस ret;
	val &= 0x0f;
	अगर (nCombDet == 0) अणु /* Turn on the Notch Filter */
		val |= 0x50;
	पूर्ण
	ret = lgdt3306a_ग_लिखो_reg(state, 0x0024, val);
	अगर (ret)
		वापस ret;

	/* VSB Timing Recovery output normalization */
	ret = lgdt3306a_पढ़ो_reg(state, 0x103d, &val);
	अगर (ret)
		वापस ret;
	val &= 0xcf;
	val |= 0x20;
	ret = lgdt3306a_ग_लिखो_reg(state, 0x103d, val);

	वापस ret;
पूर्ण

अटल क्रमागत lgdt3306a_modulation
lgdt3306a_check_oper_mode(काष्ठा lgdt3306a_state *state)
अणु
	u8 val = 0;
	पूर्णांक ret;

	ret = lgdt3306a_पढ़ो_reg(state, 0x0081, &val);
	अगर (ret)
		जाओ err;

	अगर (val & 0x80)	अणु
		dbg_info("VSB\n");
		वापस LG3306_VSB;
	पूर्ण
	अगर (val & 0x08) अणु
		ret = lgdt3306a_पढ़ो_reg(state, 0x00a6, &val);
		अगर (ret)
			जाओ err;
		val = val >> 2;
		अगर (val & 0x01) अणु
			dbg_info("QAM256\n");
			वापस LG3306_QAM256;
		पूर्ण
		dbg_info("QAM64\n");
		वापस LG3306_QAM64;
	पूर्ण
err:
	pr_warn("UNKNOWN\n");
	वापस LG3306_UNKNOWN_MODE;
पूर्ण

अटल क्रमागत lgdt3306a_lock_status
lgdt3306a_check_lock_status(काष्ठा lgdt3306a_state *state,
			    क्रमागत lgdt3306a_lock_check whatLock)
अणु
	u8 val = 0;
	पूर्णांक ret;
	क्रमागत lgdt3306a_modulation	modeOper;
	क्रमागत lgdt3306a_lock_status lockStatus;

	modeOper = LG3306_UNKNOWN_MODE;

	चयन (whatLock) अणु
	हाल LG3306_SYNC_LOCK:
	अणु
		ret = lgdt3306a_पढ़ो_reg(state, 0x00a6, &val);
		अगर (ret)
			वापस ret;

		अगर ((val & 0x80) == 0x80)
			lockStatus = LG3306_LOCK;
		अन्यथा
			lockStatus = LG3306_UNLOCK;

		dbg_info("SYNC_LOCK=%x\n", lockStatus);
		अवरोध;
	पूर्ण
	हाल LG3306_AGC_LOCK:
	अणु
		ret = lgdt3306a_पढ़ो_reg(state, 0x0080, &val);
		अगर (ret)
			वापस ret;

		अगर ((val & 0x40) == 0x40)
			lockStatus = LG3306_LOCK;
		अन्यथा
			lockStatus = LG3306_UNLOCK;

		dbg_info("AGC_LOCK=%x\n", lockStatus);
		अवरोध;
	पूर्ण
	हाल LG3306_TR_LOCK:
	अणु
		modeOper = lgdt3306a_check_oper_mode(state);
		अगर ((modeOper == LG3306_QAM64) || (modeOper == LG3306_QAM256)) अणु
			ret = lgdt3306a_पढ़ो_reg(state, 0x1094, &val);
			अगर (ret)
				वापस ret;

			अगर ((val & 0x80) == 0x80)
				lockStatus = LG3306_LOCK;
			अन्यथा
				lockStatus = LG3306_UNLOCK;
		पूर्ण अन्यथा
			lockStatus = LG3306_UNKNOWN_LOCK;

		dbg_info("TR_LOCK=%x\n", lockStatus);
		अवरोध;
	पूर्ण
	हाल LG3306_FEC_LOCK:
	अणु
		modeOper = lgdt3306a_check_oper_mode(state);
		अगर ((modeOper == LG3306_QAM64) || (modeOper == LG3306_QAM256)) अणु
			ret = lgdt3306a_पढ़ो_reg(state, 0x0080, &val);
			अगर (ret)
				वापस ret;

			अगर ((val & 0x10) == 0x10)
				lockStatus = LG3306_LOCK;
			अन्यथा
				lockStatus = LG3306_UNLOCK;
		पूर्ण अन्यथा
			lockStatus = LG3306_UNKNOWN_LOCK;

		dbg_info("FEC_LOCK=%x\n", lockStatus);
		अवरोध;
	पूर्ण

	शेष:
		lockStatus = LG3306_UNKNOWN_LOCK;
		pr_warn("UNKNOWN whatLock=%d\n", whatLock);
		अवरोध;
	पूर्ण

	वापस lockStatus;
पूर्ण

अटल क्रमागत lgdt3306a_neverlock_status
lgdt3306a_check_neverlock_status(काष्ठा lgdt3306a_state *state)
अणु
	u8 val = 0;
	पूर्णांक ret;
	क्रमागत lgdt3306a_neverlock_status lockStatus;

	ret = lgdt3306a_पढ़ो_reg(state, 0x0080, &val);
	अगर (ret)
		वापस ret;
	lockStatus = (क्रमागत lgdt3306a_neverlock_status)(val & 0x03);

	dbg_info("NeverLock=%d", lockStatus);

	वापस lockStatus;
पूर्ण

अटल पूर्णांक lgdt3306a_pre_monitoring(काष्ठा lgdt3306a_state *state)
अणु
	u8 val = 0;
	पूर्णांक ret;
	u8 currChDअगरfACQ, snrRef, मुख्यStrong, aiccrejStatus;

	/* Channel variation */
	ret = lgdt3306a_पढ़ो_reg(state, 0x21bc, &currChDअगरfACQ);
	अगर (ret)
		वापस ret;

	/* SNR of Frame sync */
	ret = lgdt3306a_पढ़ो_reg(state, 0x21a1, &val);
	अगर (ret)
		वापस ret;
	snrRef = val & 0x3f;

	/* Strong Main CIR */
	ret = lgdt3306a_पढ़ो_reg(state, 0x2199, &val);
	अगर (ret)
		वापस ret;
	मुख्यStrong = (val & 0x40) >> 6;

	ret = lgdt3306a_पढ़ो_reg(state, 0x0090, &val);
	अगर (ret)
		वापस ret;
	aiccrejStatus = (val & 0xf0) >> 4;

	dbg_info("snrRef=%d mainStrong=%d aiccrejStatus=%d currChDiffACQ=0x%x\n",
		snrRef, मुख्यStrong, aiccrejStatus, currChDअगरfACQ);

#अगर 0
	/* Dynamic ghost exists */
	अगर ((मुख्यStrong == 0) && (currChDअगरfACQ > 0x70))
#पूर्ण_अगर
	अगर (मुख्यStrong == 0) अणु
		ret = lgdt3306a_पढ़ो_reg(state, 0x2135, &val);
		अगर (ret)
			वापस ret;
		val &= 0x0f;
		val |= 0xa0;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x2135, val);
		अगर (ret)
			वापस ret;

		ret = lgdt3306a_पढ़ो_reg(state, 0x2141, &val);
		अगर (ret)
			वापस ret;
		val &= 0x3f;
		val |= 0x80;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x2141, val);
		अगर (ret)
			वापस ret;

		ret = lgdt3306a_ग_लिखो_reg(state, 0x2122, 0x70);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु /* Weak ghost or अटल channel */
		ret = lgdt3306a_पढ़ो_reg(state, 0x2135, &val);
		अगर (ret)
			वापस ret;
		val &= 0x0f;
		val |= 0x70;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x2135, val);
		अगर (ret)
			वापस ret;

		ret = lgdt3306a_पढ़ो_reg(state, 0x2141, &val);
		अगर (ret)
			वापस ret;
		val &= 0x3f;
		val |= 0x40;
		ret = lgdt3306a_ग_लिखो_reg(state, 0x2141, val);
		अगर (ret)
			वापस ret;

		ret = lgdt3306a_ग_लिखो_reg(state, 0x2122, 0x40);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत lgdt3306a_lock_status
lgdt3306a_sync_lock_poll(काष्ठा lgdt3306a_state *state)
अणु
	क्रमागत lgdt3306a_lock_status syncLockStatus = LG3306_UNLOCK;
	पूर्णांक	i;

	क्रम (i = 0; i < 2; i++)	अणु
		msleep(30);

		syncLockStatus = lgdt3306a_check_lock_status(state,
							     LG3306_SYNC_LOCK);

		अगर (syncLockStatus == LG3306_LOCK) अणु
			dbg_info("locked(%d)\n", i);
			वापस LG3306_LOCK;
		पूर्ण
	पूर्ण
	dbg_info("not locked\n");
	वापस LG3306_UNLOCK;
पूर्ण

अटल क्रमागत lgdt3306a_lock_status
lgdt3306a_fec_lock_poll(काष्ठा lgdt3306a_state *state)
अणु
	क्रमागत lgdt3306a_lock_status FECLockStatus = LG3306_UNLOCK;
	पूर्णांक	i;

	क्रम (i = 0; i < 2; i++)	अणु
		msleep(30);

		FECLockStatus = lgdt3306a_check_lock_status(state,
							    LG3306_FEC_LOCK);

		अगर (FECLockStatus == LG3306_LOCK) अणु
			dbg_info("locked(%d)\n", i);
			वापस FECLockStatus;
		पूर्ण
	पूर्ण
	dbg_info("not locked\n");
	वापस FECLockStatus;
पूर्ण

अटल क्रमागत lgdt3306a_neverlock_status
lgdt3306a_neverlock_poll(काष्ठा lgdt3306a_state *state)
अणु
	क्रमागत lgdt3306a_neverlock_status NLLockStatus = LG3306_NL_FAIL;
	पूर्णांक	i;

	क्रम (i = 0; i < 5; i++) अणु
		msleep(30);

		NLLockStatus = lgdt3306a_check_neverlock_status(state);

		अगर (NLLockStatus == LG3306_NL_LOCK) अणु
			dbg_info("NL_LOCK(%d)\n", i);
			वापस NLLockStatus;
		पूर्ण
	पूर्ण
	dbg_info("NLLockStatus=%d\n", NLLockStatus);
	वापस NLLockStatus;
पूर्ण

अटल u8 lgdt3306a_get_packet_error(काष्ठा lgdt3306a_state *state)
अणु
	u8 val;
	पूर्णांक ret;

	ret = lgdt3306a_पढ़ो_reg(state, 0x00fa, &val);
	अगर (ret)
		वापस ret;

	वापस val;
पूर्ण

अटल स्थिर u32 valx_x10[] = अणु
	10,  11,  13,  15,  17,  20,  25,  33,  41,  50,  59,  73,  87,  100
पूर्ण;
अटल स्थिर u32 log10x_x1000[] = अणु
	0,   41, 114, 176, 230, 301, 398, 518, 613, 699, 771, 863, 939, 1000
पूर्ण;

अटल u32 log10_x1000(u32 x)
अणु
	u32 dअगरf_val, step_val, step_log10;
	u32 log_val = 0;
	u32 i;

	अगर (x <= 0)
		वापस -1000000; /* संकेत error */

	अगर (x == 10)
		वापस 0; /* log(1)=0 */

	अगर (x < 10) अणु
		जबतक (x < 10) अणु
			x = x * 10;
			log_val--;
		पूर्ण
	पूर्ण अन्यथा अणु	/* x > 10 */
		जबतक (x >= 100) अणु
			x = x / 10;
			log_val++;
		पूर्ण
	पूर्ण
	log_val *= 1000;

	अगर (x == 10) /* was our input an exact multiple of 10 */
		वापस log_val;	/* करोn't need to पूर्णांकerpolate */

	/* find our place on the log curve */
	क्रम (i = 1; i < ARRAY_SIZE(valx_x10); i++) अणु
		अगर (valx_x10[i] >= x)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(valx_x10))
		वापस log_val + log10x_x1000[i - 1];

	dअगरf_val   = x - valx_x10[i-1];
	step_val   = valx_x10[i] - valx_x10[i - 1];
	step_log10 = log10x_x1000[i] - log10x_x1000[i - 1];

	/* करो a linear पूर्णांकerpolation to get in-between values */
	वापस log_val + log10x_x1000[i - 1] +
		((dअगरf_val*step_log10) / step_val);
पूर्ण

अटल u32 lgdt3306a_calculate_snr_x100(काष्ठा lgdt3306a_state *state)
अणु
	u32 mse; /* Mean-Square Error */
	u32 pwr; /* Constelation घातer */
	u32 snr_x100;

	mse = (पढ़ो_reg(state, 0x00ec) << 8) |
	      (पढ़ो_reg(state, 0x00ed));
	pwr = (पढ़ो_reg(state, 0x00e8) << 8) |
	      (पढ़ो_reg(state, 0x00e9));

	अगर (mse == 0) /* no संकेत */
		वापस 0;

	snr_x100 = log10_x1000((pwr * 10000) / mse) - 3000;
	dbg_info("mse=%u, pwr=%u, snr_x100=%d\n", mse, pwr, snr_x100);

	वापस snr_x100;
पूर्ण

अटल क्रमागत lgdt3306a_lock_status
lgdt3306a_vsb_lock_poll(काष्ठा lgdt3306a_state *state)
अणु
	पूर्णांक ret;
	u8 cnt = 0;
	u8 packet_error;
	u32 snr;

	क्रम (cnt = 0; cnt < 10; cnt++) अणु
		अगर (lgdt3306a_sync_lock_poll(state) == LG3306_UNLOCK) अणु
			dbg_info("no sync lock!\n");
			वापस LG3306_UNLOCK;
		पूर्ण

		msleep(20);
		ret = lgdt3306a_pre_monitoring(state);
		अगर (ret)
			अवरोध;

		packet_error = lgdt3306a_get_packet_error(state);
		snr = lgdt3306a_calculate_snr_x100(state);
		dbg_info("cnt=%d errors=%d snr=%d\n", cnt, packet_error, snr);

		अगर ((snr >= 1500) && (packet_error < 0xff))
			वापस LG3306_LOCK;
	पूर्ण

	dbg_info("not locked!\n");
	वापस LG3306_UNLOCK;
पूर्ण

अटल क्रमागत lgdt3306a_lock_status
lgdt3306a_qam_lock_poll(काष्ठा lgdt3306a_state *state)
अणु
	u8 cnt;
	u8 packet_error;
	u32	snr;

	क्रम (cnt = 0; cnt < 10; cnt++) अणु
		अगर (lgdt3306a_fec_lock_poll(state) == LG3306_UNLOCK) अणु
			dbg_info("no fec lock!\n");
			वापस LG3306_UNLOCK;
		पूर्ण

		msleep(20);

		packet_error = lgdt3306a_get_packet_error(state);
		snr = lgdt3306a_calculate_snr_x100(state);
		dbg_info("cnt=%d errors=%d snr=%d\n", cnt, packet_error, snr);

		अगर ((snr >= 1500) && (packet_error < 0xff))
			वापस LG3306_LOCK;
	पूर्ण

	dbg_info("not locked!\n");
	वापस LG3306_UNLOCK;
पूर्ण

अटल पूर्णांक lgdt3306a_पढ़ो_status(काष्ठा dvb_frontend *fe,
				 क्रमागत fe_status *status)
अणु
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u16 strength = 0;
	पूर्णांक ret = 0;

	अगर (fe->ops.tuner_ops.get_rf_strength) अणु
		ret = fe->ops.tuner_ops.get_rf_strength(fe, &strength);
		अगर (ret == 0)
			dbg_info("strength=%d\n", strength);
		अन्यथा
			dbg_info("fe->ops.tuner_ops.get_rf_strength() failed\n");
	पूर्ण

	*status = 0;
	अगर (lgdt3306a_neverlock_poll(state) == LG3306_NL_LOCK) अणु
		*status |= FE_HAS_SIGNAL;
		*status |= FE_HAS_CARRIER;

		चयन (state->current_modulation) अणु
		हाल QAM_256:
		हाल QAM_64:
		हाल QAM_AUTO:
			अगर (lgdt3306a_qam_lock_poll(state) == LG3306_LOCK) अणु
				*status |= FE_HAS_VITERBI;
				*status |= FE_HAS_SYNC;

				*status |= FE_HAS_LOCK;
			पूर्ण
			अवरोध;
		हाल VSB_8:
			अगर (lgdt3306a_vsb_lock_poll(state) == LG3306_LOCK) अणु
				*status |= FE_HAS_VITERBI;
				*status |= FE_HAS_SYNC;

				*status |= FE_HAS_LOCK;

				ret = lgdt3306a_monitor_vsb(state);
			पूर्ण
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण

		अगर (*status & FE_HAS_SYNC) अणु
			c->cnr.len = 1;
			c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			c->cnr.stat[0].svalue = lgdt3306a_calculate_snr_x100(state) * 10;
		पूर्ण अन्यथा अणु
			c->cnr.len = 1;
			c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण


अटल पूर्णांक lgdt3306a_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;

	state->snr = lgdt3306a_calculate_snr_x100(state);
	/* report SNR in dB * 10 */
	*snr = state->snr/10;

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3306a_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					 u16 *strength)
अणु
	/*
	 * Calculate some sort of "strength" from SNR
	 */
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;
	u8 val;
	u16 snr; /* snr_x10 */
	पूर्णांक ret;
	u32 ref_snr; /* snr*100 */
	u32 str;

	*strength = 0;

	चयन (state->current_modulation) अणु
	हाल VSB_8:
		 ref_snr = 1600; /* 16dB */
		 अवरोध;
	हाल QAM_64:
	हाल QAM_256:
	हाल QAM_AUTO:
		/* need to know actual modulation to set proper SNR baseline */
		ret = lgdt3306a_पढ़ो_reg(state, 0x00a6, &val);
		अगर (lg_chkerr(ret))
			जाओ fail;

		अगर(val & 0x04)
			ref_snr = 2800; /* QAM-256 28dB */
		अन्यथा
			ref_snr = 2200; /* QAM-64  22dB */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = fe->ops.पढ़ो_snr(fe, &snr);
	अगर (lg_chkerr(ret))
		जाओ fail;

	अगर (state->snr <= (ref_snr - 100))
		str = 0;
	अन्यथा अगर (state->snr <= ref_snr)
		str = (0xffff * 65) / 100; /* 65% */
	अन्यथा अणु
		str = state->snr - ref_snr;
		str /= 50;
		str += 78; /* 78%-100% */
		अगर (str > 100)
			str = 100;
		str = (0xffff * str) / 100;
	पूर्ण
	*strength = (u16)str;
	dbg_info("strength=%u\n", *strength);

fail:
	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल पूर्णांक lgdt3306a_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;
	u32 पंचांगp;

	*ber = 0;
#अगर 1
	/* FGR - FIXME - I करोn't know what value is expected by dvb_core
	 * what is the scale of the value?? */
	पंचांगp =              पढ़ो_reg(state, 0x00fc); /* NBERVALUE[24-31] */
	पंचांगp = (पंचांगp << 8) | पढ़ो_reg(state, 0x00fd); /* NBERVALUE[16-23] */
	पंचांगp = (पंचांगp << 8) | पढ़ो_reg(state, 0x00fe); /* NBERVALUE[8-15] */
	पंचांगp = (पंचांगp << 8) | पढ़ो_reg(state, 0x00ff); /* NBERVALUE[0-7] */
	*ber = पंचांगp;
	dbg_info("ber=%u\n", पंचांगp);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3306a_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucblocks)
अणु
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;

	*ucblocks = 0;
#अगर 1
	/* FGR - FIXME - I करोn't know what value is expected by dvb_core
	 * what happens when value wraps? */
	*ucblocks = पढ़ो_reg(state, 0x00f4); /* TPIFTPERRCNT[0-7] */
	dbg_info("ucblocks=%u\n", *ucblocks);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक lgdt3306a_tune(काष्ठा dvb_frontend *fe, bool re_tune,
			  अचिन्हित पूर्णांक mode_flags, अचिन्हित पूर्णांक *delay,
			  क्रमागत fe_status *status)
अणु
	पूर्णांक ret = 0;
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;

	dbg_info("re_tune=%u\n", re_tune);

	अगर (re_tune) अणु
		state->current_frequency = -1; /* क्रमce re-tune */
		ret = lgdt3306a_set_parameters(fe);
		अगर (ret != 0)
			वापस ret;
	पूर्ण
	*delay = 125;
	ret = lgdt3306a_पढ़ो_status(fe, status);

	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_get_tune_settings(काष्ठा dvb_frontend *fe,
				       काष्ठा dvb_frontend_tune_settings
				       *fe_tune_settings)
अणु
	fe_tune_settings->min_delay_ms = 100;
	dbg_info("\n");
	वापस 0;
पूर्ण

अटल क्रमागत dvbfe_search lgdt3306a_search(काष्ठा dvb_frontend *fe)
अणु
	क्रमागत fe_status status = 0;
	पूर्णांक ret;

	/* set frontend */
	ret = lgdt3306a_set_parameters(fe);
	अगर (ret)
		जाओ error;

	ret = lgdt3306a_पढ़ो_status(fe, &status);
	अगर (ret)
		जाओ error;

	/* check अगर we have a valid संकेत */
	अगर (status & FE_HAS_LOCK)
		वापस DVBFE_ALGO_SEARCH_SUCCESS;
	अन्यथा
		वापस DVBFE_ALGO_SEARCH_AGAIN;

error:
	dbg_info("failed (%d)\n", ret);
	वापस DVBFE_ALGO_SEARCH_ERROR;
पूर्ण

अटल व्योम lgdt3306a_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा lgdt3306a_state *state = fe->demodulator_priv;

	dbg_info("\n");
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops lgdt3306a_ops;

काष्ठा dvb_frontend *lgdt3306a_attach(स्थिर काष्ठा lgdt3306a_config *config,
				      काष्ठा i2c_adapter *i2c_adap)
अणु
	काष्ठा lgdt3306a_state *state = शून्य;
	पूर्णांक ret;
	u8 val;

	dbg_info("(%d-%04x)\n",
	       i2c_adap ? i2c_adapter_id(i2c_adap) : 0,
	       config ? config->i2c_addr : 0);

	state = kzalloc(माप(काष्ठा lgdt3306a_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ fail;

	state->cfg = config;
	state->i2c_adap = i2c_adap;

	स_नकल(&state->frontend.ops, &lgdt3306a_ops,
	       माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;

	/* verअगरy that we're talking to a lg3306a */
	/* FGR - NOTE - there is no obvious ChipId to check; we check
	 * some "known" bits after reset, but it's still just a guess */
	ret = lgdt3306a_पढ़ो_reg(state, 0x0000, &val);
	अगर (lg_chkerr(ret))
		जाओ fail;
	अगर ((val & 0x74) != 0x74) अणु
		pr_warn("expected 0x74, got 0x%x\n", (val & 0x74));
#अगर 0
		/* FIXME - re-enable when we know this is right */
		जाओ fail;
#पूर्ण_अगर
	पूर्ण
	ret = lgdt3306a_पढ़ो_reg(state, 0x0001, &val);
	अगर (lg_chkerr(ret))
		जाओ fail;
	अगर ((val & 0xf6) != 0xc6) अणु
		pr_warn("expected 0xc6, got 0x%x\n", (val & 0xf6));
#अगर 0
		/* FIXME - re-enable when we know this is right */
		जाओ fail;
#पूर्ण_अगर
	पूर्ण
	ret = lgdt3306a_पढ़ो_reg(state, 0x0002, &val);
	अगर (lg_chkerr(ret))
		जाओ fail;
	अगर ((val & 0x73) != 0x03) अणु
		pr_warn("expected 0x03, got 0x%x\n", (val & 0x73));
#अगर 0
		/* FIXME - re-enable when we know this is right */
		जाओ fail;
#पूर्ण_अगर
	पूर्ण

	state->current_frequency = -1;
	state->current_modulation = -1;

	lgdt3306a_sleep(state);

	वापस &state->frontend;

fail:
	pr_warn("unable to detect LGDT3306A hardware\n");
	kमुक्त(state);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(lgdt3306a_attach);

#अगर_घोषित DBG_DUMP

अटल स्थिर लघु regtab[] = अणु
	0x0000, /* SOFTRSTB 1'b1 1'b1 1'b1 ADCPDB 1'b1 PLLPDB GBBPDB 11111111 */
	0x0001, /* 1'b1 1'b1 1'b0 1'b0 AUTORPTRS */
	0x0002, /* NI2CRPTEN 1'b0 1'b0 1'b0 SPECINVAUT */
	0x0003, /* AGCRFOUT */
	0x0004, /* ADCSEL1V ADCCNT ADCCNF ADCCNS ADCCLKPLL */
	0x0005, /* PLLINDIVSE */
	0x0006, /* PLLCTRL[7:0] 11100001 */
	0x0007, /* SYSINITWAITTIME[7:0] (msec) 00001000 */
	0x0008, /* STDOPMODE[7:0] 10000000 */
	0x0009, /* 1'b0 1'b0 1'b0 STDOPDETTMODE[2:0] STDOPDETCMODE[1:0] 00011110 */
	0x000a, /* DAFTEN 1'b1 x x SCSYSLOCK */
	0x000b, /* SCSYSLOCKCHKTIME[7:0] (10msec) 01100100 */
	0x000d, /* x SAMPLING4 */
	0x000e, /* SAMFREQ[15:8] 00000000 */
	0x000f, /* SAMFREQ[7:0] 00000000 */
	0x0010, /* IFFREQ[15:8] 01100000 */
	0x0011, /* IFFREQ[7:0] 00000000 */
	0x0012, /* AGCEN AGCREFMO */
	0x0013, /* AGCRFFIXB AGCIFFIXB AGCLOCKDETRNGSEL[1:0] 1'b1 1'b0 1'b0 1'b0 11101000 */
	0x0014, /* AGCFIXVALUE[7:0] 01111111 */
	0x0015, /* AGCREF[15:8] 00001010 */
	0x0016, /* AGCREF[7:0] 11100100 */
	0x0017, /* AGCDELAY[7:0] 00100000 */
	0x0018, /* AGCRFBW[3:0] AGCIFBW[3:0] 10001000 */
	0x0019, /* AGCUDOUTMODE[1:0] AGCUDCTRLLEN[1:0] AGCUDCTRL */
	0x001c, /* 1'b1 PFEN MFEN AICCVSYNC */
	0x001d, /* 1'b0 1'b1 1'b0 1'b1 AICCVSYNC */
	0x001e, /* AICCALPHA[3:0] 1'b1 1'b0 1'b1 1'b0 01111010 */
	0x001f, /* AICCDETTH[19:16] AICCOFFTH[19:16] 00000000 */
	0x0020, /* AICCDETTH[15:8] 01111100 */
	0x0021, /* AICCDETTH[7:0] 00000000 */
	0x0022, /* AICCOFFTH[15:8] 00000101 */
	0x0023, /* AICCOFFTH[7:0] 11100000 */
	0x0024, /* AICCOPMODE3[1:0] AICCOPMODE2[1:0] AICCOPMODE1[1:0] AICCOPMODE0[1:0] 00000000 */
	0x0025, /* AICCFIXFREQ3[23:16] 00000000 */
	0x0026, /* AICCFIXFREQ3[15:8] 00000000 */
	0x0027, /* AICCFIXFREQ3[7:0] 00000000 */
	0x0028, /* AICCFIXFREQ2[23:16] 00000000 */
	0x0029, /* AICCFIXFREQ2[15:8] 00000000 */
	0x002a, /* AICCFIXFREQ2[7:0] 00000000 */
	0x002b, /* AICCFIXFREQ1[23:16] 00000000 */
	0x002c, /* AICCFIXFREQ1[15:8] 00000000 */
	0x002d, /* AICCFIXFREQ1[7:0] 00000000 */
	0x002e, /* AICCFIXFREQ0[23:16] 00000000 */
	0x002f, /* AICCFIXFREQ0[15:8] 00000000 */
	0x0030, /* AICCFIXFREQ0[7:0] 00000000 */
	0x0031, /* 1'b0 1'b1 1'b0 1'b0 x DAGC1STER */
	0x0032, /* DAGC1STEN DAGC1STER */
	0x0033, /* DAGC1STREF[15:8] 00001010 */
	0x0034, /* DAGC1STREF[7:0] 11100100 */
	0x0035, /* DAGC2NDE */
	0x0036, /* DAGC2NDREF[15:8] 00001010 */
	0x0037, /* DAGC2NDREF[7:0] 10000000 */
	0x0038, /* DAGC2NDLOCKDETRNGSEL[1:0] */
	0x003d, /* 1'b1 SAMGEARS */
	0x0040, /* SAMLFGMA */
	0x0041, /* SAMLFBWM */
	0x0044, /* 1'b1 CRGEARSHE */
	0x0045, /* CRLFGMAN */
	0x0046, /* CFLFBWMA */
	0x0047, /* CRLFGMAN */
	0x0048, /* x x x x CRLFGSTEP_VS[3:0] xxxx1001 */
	0x0049, /* CRLFBWMA */
	0x004a, /* CRLFBWMA */
	0x0050, /* 1'b0 1'b1 1'b1 1'b0 MSECALCDA */
	0x0070, /* TPOUTEN TPIFEN TPCLKOUTE */
	0x0071, /* TPSENB TPSSOPBITE */
	0x0073, /* TP47HINS x x CHBERINT PERMODE[1:0] PERINT[1:0] 1xx11100 */
	0x0075, /* x x x x x IQSWAPCTRL[2:0] xxxxx000 */
	0x0076, /* NBERCON NBERST NBERPOL NBERWSYN */
	0x0077, /* x NBERLOSTTH[2:0] NBERACQTH[3:0] x0000000 */
	0x0078, /* NBERPOLY[31:24] 00000000 */
	0x0079, /* NBERPOLY[23:16] 00000000 */
	0x007a, /* NBERPOLY[15:8] 00000000 */
	0x007b, /* NBERPOLY[7:0] 00000000 */
	0x007c, /* NBERPED[31:24] 00000000 */
	0x007d, /* NBERPED[23:16] 00000000 */
	0x007e, /* NBERPED[15:8] 00000000 */
	0x007f, /* NBERPED[7:0] 00000000 */
	0x0080, /* x AGCLOCK DAGCLOCK SYSLOCK x x NEVERLOCK[1:0] */
	0x0085, /* SPECINVST */
	0x0088, /* SYSLOCKTIME[15:8] */
	0x0089, /* SYSLOCKTIME[7:0] */
	0x008c, /* FECLOCKTIME[15:8] */
	0x008d, /* FECLOCKTIME[7:0] */
	0x008e, /* AGCACCOUT[15:8] */
	0x008f, /* AGCACCOUT[7:0] */
	0x0090, /* AICCREJSTATUS[3:0] AICCREJBUSY[3:0] */
	0x0091, /* AICCVSYNC */
	0x009c, /* CARRFREQOFFSET[15:8] */
	0x009d, /* CARRFREQOFFSET[7:0] */
	0x00a1, /* SAMFREQOFFSET[23:16] */
	0x00a2, /* SAMFREQOFFSET[15:8] */
	0x00a3, /* SAMFREQOFFSET[7:0] */
	0x00a6, /* SYNCLOCK SYNCLOCKH */
#अगर 0 /* covered अन्यथाwhere */
	0x00e8, /* CONSTPWR[15:8] */
	0x00e9, /* CONSTPWR[7:0] */
	0x00ea, /* BMSE[15:8] */
	0x00eb, /* BMSE[7:0] */
	0x00ec, /* MSE[15:8] */
	0x00ed, /* MSE[7:0] */
	0x00ee, /* CONSTI[7:0] */
	0x00ef, /* CONSTQ[7:0] */
#पूर्ण_अगर
	0x00f4, /* TPIFTPERRCNT[7:0] */
	0x00f5, /* TPCORREC */
	0x00f6, /* VBBER[15:8] */
	0x00f7, /* VBBER[7:0] */
	0x00f8, /* VABER[15:8] */
	0x00f9, /* VABER[7:0] */
	0x00fa, /* TPERRCNT[7:0] */
	0x00fb, /* NBERLOCK x x x x x x x */
	0x00fc, /* NBERVALUE[31:24] */
	0x00fd, /* NBERVALUE[23:16] */
	0x00fe, /* NBERVALUE[15:8] */
	0x00ff, /* NBERVALUE[7:0] */
	0x1000, /* 1'b0 WODAGCOU */
	0x1005, /* x x 1'b1 1'b1 x SRD_Q_QM */
	0x1009, /* SRDWAITTIME[7:0] (10msec) 00100011 */
	0x100a, /* SRDWAITTIME_CQS[7:0] (msec) 01100100 */
	0x101a, /* x 1'b1 1'b0 1'b0 x QMDQAMMODE[2:0] x100x010 */
	0x1036, /* 1'b0 1'b1 1'b0 1'b0 SAMGSEND_CQS[3:0] 01001110 */
	0x103c, /* SAMGSAUTOSTL_V[3:0] SAMGSAUTOEDL_V[3:0] 01000110 */
	0x103d, /* 1'b1 1'b1 SAMCNORMBP_V[1:0] 1'b0 1'b0 SAMMODESEL_V[1:0] 11100001 */
	0x103f, /* SAMZTEDSE */
	0x105d, /* EQSTATUSE */
	0x105f, /* x PMAPG2_V[2:0] x DMAPG2_V[2:0] x001x011 */
	0x1060, /* 1'b1 EQSTATUSE */
	0x1061, /* CRMAPBWSTL_V[3:0] CRMAPBWEDL_V[3:0] 00000100 */
	0x1065, /* 1'b0 x CRMODE_V[1:0] 1'b1 x 1'b1 x 0x111x1x */
	0x1066, /* 1'b0 1'b0 1'b1 1'b0 1'b1 PNBOOSTSE */
	0x1068, /* CREPHNGAIN2_V[3:0] CREPHNPBW_V[3:0] 10010001 */
	0x106e, /* x x x x x CREPHNEN_ */
	0x106f, /* CREPHNTH_V[7:0] 00010101 */
	0x1072, /* CRSWEEPN */
	0x1073, /* CRPGAIN_V[3:0] x x 1'b1 1'b1 1001xx11 */
	0x1074, /* CRPBW_V[3:0] x x 1'b1 1'b1 0001xx11 */
	0x1080, /* DAFTSTATUS[1:0] x x x x x x */
	0x1081, /* SRDSTATUS[1:0] x x x x x SRDLOCK */
	0x10a9, /* EQSTATUS_CQS[1:0] x x x x x x */
	0x10b7, /* EQSTATUS_V[1:0] x x x x x x */
#अगर 0 /* SMART_ANT */
	0x1f00, /* MODEDETE */
	0x1f01, /* x x x x x x x SFNRST xxxxxxx0 */
	0x1f03, /* NUMOFANT[7:0] 10000000 */
	0x1f04, /* x SELMASK[6:0] x0000000 */
	0x1f05, /* x SETMASK[6:0] x0000000 */
	0x1f06, /* x TXDATA[6:0] x0000000 */
	0x1f07, /* x CHNUMBER[6:0] x0000000 */
	0x1f09, /* AGCTIME[23:16] 10011000 */
	0x1f0a, /* AGCTIME[15:8] 10010110 */
	0x1f0b, /* AGCTIME[7:0] 10000000 */
	0x1f0c, /* ANTTIME[31:24] 00000000 */
	0x1f0d, /* ANTTIME[23:16] 00000011 */
	0x1f0e, /* ANTTIME[15:8] 10010000 */
	0x1f0f, /* ANTTIME[7:0] 10010000 */
	0x1f11, /* SYNCTIME[23:16] 10011000 */
	0x1f12, /* SYNCTIME[15:8] 10010110 */
	0x1f13, /* SYNCTIME[7:0] 10000000 */
	0x1f14, /* SNRTIME[31:24] 00000001 */
	0x1f15, /* SNRTIME[23:16] 01111101 */
	0x1f16, /* SNRTIME[15:8] 01111000 */
	0x1f17, /* SNRTIME[7:0] 01000000 */
	0x1f19, /* FECTIME[23:16] 00000000 */
	0x1f1a, /* FECTIME[15:8] 01110010 */
	0x1f1b, /* FECTIME[7:0] 01110000 */
	0x1f1d, /* FECTHD[7:0] 00000011 */
	0x1f1f, /* SNRTHD[23:16] 00001000 */
	0x1f20, /* SNRTHD[15:8] 01111111 */
	0x1f21, /* SNRTHD[7:0] 10000101 */
	0x1f80, /* IRQFLG x x SFSDRFLG MODEBFLG SAVEFLG SCANFLG TRACKFLG */
	0x1f81, /* x SYNCCON SNRCON FECCON x STDBUSY SYNCRST AGCFZCO */
	0x1f82, /* x x x SCANOPCD[4:0] */
	0x1f83, /* x x x x MAINOPCD[3:0] */
	0x1f84, /* x x RXDATA[13:8] */
	0x1f85, /* RXDATA[7:0] */
	0x1f86, /* x x SDTDATA[13:8] */
	0x1f87, /* SDTDATA[7:0] */
	0x1f89, /* ANTSNR[23:16] */
	0x1f8a, /* ANTSNR[15:8] */
	0x1f8b, /* ANTSNR[7:0] */
	0x1f8c, /* x x x x ANTFEC[13:8] */
	0x1f8d, /* ANTFEC[7:0] */
	0x1f8e, /* MAXCNT[7:0] */
	0x1f8f, /* SCANCNT[7:0] */
	0x1f91, /* MAXPW[23:16] */
	0x1f92, /* MAXPW[15:8] */
	0x1f93, /* MAXPW[7:0] */
	0x1f95, /* CURPWMSE[23:16] */
	0x1f96, /* CURPWMSE[15:8] */
	0x1f97, /* CURPWMSE[7:0] */
#पूर्ण_अगर /* SMART_ANT */
	0x211f, /* 1'b1 1'b1 1'b1 CIRQEN x x 1'b0 1'b0 1111xx00 */
	0x212a, /* EQAUTOST */
	0x2122, /* CHFAST[7:0] 01100000 */
	0x212b, /* FFFSTEP_V[3:0] x FBFSTEP_V[2:0] 0001x001 */
	0x212c, /* PHDEROTBWSEL[3:0] 1'b1 1'b1 1'b1 1'b0 10001110 */
	0x212d, /* 1'b1 1'b1 1'b1 1'b1 x x TPIFLOCKS */
	0x2135, /* DYNTRACKFDEQ[3:0] x 1'b0 1'b0 1'b0 1010x000 */
	0x2141, /* TRMODE[1:0] 1'b1 1'b1 1'b0 1'b1 1'b1 1'b1 01110111 */
	0x2162, /* AICCCTRLE */
	0x2173, /* PHNCNFCNT[7:0] 00000100 */
	0x2179, /* 1'b0 1'b0 1'b0 1'b1 x BADSINGLEDYNTRACKFBF[2:0] 0001x001 */
	0x217a, /* 1'b0 1'b0 1'b0 1'b1 x BADSLOWSINGLEDYNTRACKFBF[2:0] 0001x001 */
	0x217e, /* CNFCNTTPIF[7:0] 00001000 */
	0x217f, /* TPERRCNTTPIF[7:0] 00000001 */
	0x2180, /* x x x x x x FBDLYCIR[9:8] */
	0x2181, /* FBDLYCIR[7:0] */
	0x2185, /* MAXPWRMAIN[7:0] */
	0x2191, /* NCOMBDET x x x x x x x */
	0x2199, /* x MAINSTRON */
	0x219a, /* FFFEQSTEPOUT_V[3:0] FBFSTEPOUT_V[2:0] */
	0x21a1, /* x x SNRREF[5:0] */
	0x2845, /* 1'b0 1'b1 x x FFFSTEP_CQS[1:0] FFFCENTERTAP[1:0] 01xx1110 */
	0x2846, /* 1'b0 x 1'b0 1'b1 FBFSTEP_CQS[1:0] 1'b1 1'b0 0x011110 */
	0x2847, /* ENNOSIGDE */
	0x2849, /* 1'b1 1'b1 NOUSENOSI */
	0x284a, /* EQINITWAITTIME[7:0] 01100100 */
	0x3000, /* 1'b1 1'b1 1'b1 x x x 1'b0 RPTRSTM */
	0x3001, /* RPTRSTWAITTIME[7:0] (100msec) 00110010 */
	0x3031, /* FRAMELOC */
	0x3032, /* 1'b1 1'b0 1'b0 1'b0 x x FRAMELOCKMODE_CQS[1:0] 1000xx11 */
	0x30a9, /* VDLOCK_Q FRAMELOCK */
	0x30aa, /* MPEGLOCK */
पूर्ण;

#घोषणा numDumpRegs (ARRAY_SIZE(regtab))
अटल u8 regval1[numDumpRegs] = अणु0, पूर्ण;
अटल u8 regval2[numDumpRegs] = अणु0, पूर्ण;

अटल व्योम lgdt3306a_DumpAllRegs(काष्ठा lgdt3306a_state *state)
अणु
		स_रखो(regval2, 0xff, माप(regval2));
		lgdt3306a_DumpRegs(state);
पूर्ण

अटल व्योम lgdt3306a_DumpRegs(काष्ठा lgdt3306a_state *state)
अणु
	पूर्णांक i;
	पूर्णांक sav_debug = debug;

	अगर ((debug & DBG_DUMP) == 0)
		वापस;
	debug &= ~DBG_REG; /* suppress DBG_REG during reg dump */

	lg_debug("\n");

	क्रम (i = 0; i < numDumpRegs; i++) अणु
		lgdt3306a_पढ़ो_reg(state, regtab[i], &regval1[i]);
		अगर (regval1[i] != regval2[i]) अणु
			lg_debug(" %04X = %02X\n", regtab[i], regval1[i]);
			regval2[i] = regval1[i];
		पूर्ण
	पूर्ण
	debug = sav_debug;
पूर्ण
#पूर्ण_अगर /* DBG_DUMP */



अटल स्थिर काष्ठा dvb_frontend_ops lgdt3306a_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name = "LG Electronics LGDT3306A VSB/QAM Frontend",
		.frequency_min_hz      =  54 * MHz,
		.frequency_max_hz      = 858 * MHz,
		.frequency_stepsize_hz = 62500,
		.caps = FE_CAN_QAM_AUTO | FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	पूर्ण,
	.i2c_gate_ctrl        = lgdt3306a_i2c_gate_ctrl,
	.init                 = lgdt3306a_init,
	.sleep                = lgdt3306a_fe_sleep,
	/* अगर this is set, it overrides the शेष swzigzag */
	.tune                 = lgdt3306a_tune,
	.set_frontend         = lgdt3306a_set_parameters,
	.get_frontend         = lgdt3306a_get_frontend,
	.get_frontend_algo    = lgdt3306a_get_frontend_algo,
	.get_tune_settings    = lgdt3306a_get_tune_settings,
	.पढ़ो_status          = lgdt3306a_पढ़ो_status,
	.पढ़ो_ber             = lgdt3306a_पढ़ो_ber,
	.पढ़ो_संकेत_strength = lgdt3306a_पढ़ो_संकेत_strength,
	.पढ़ो_snr             = lgdt3306a_पढ़ो_snr,
	.पढ़ो_ucblocks        = lgdt3306a_पढ़ो_ucblocks,
	.release              = lgdt3306a_release,
	.ts_bus_ctrl          = lgdt3306a_ts_bus_ctrl,
	.search               = lgdt3306a_search,
पूर्ण;

अटल पूर्णांक lgdt3306a_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा i2c_client *client = i2c_mux_priv(muxc);
	काष्ठा lgdt3306a_state *state = i2c_get_clientdata(client);

	वापस lgdt3306a_i2c_gate_ctrl(&state->frontend, 1);
पूर्ण

अटल पूर्णांक lgdt3306a_deselect(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा i2c_client *client = i2c_mux_priv(muxc);
	काष्ठा lgdt3306a_state *state = i2c_get_clientdata(client);

	वापस lgdt3306a_i2c_gate_ctrl(&state->frontend, 0);
पूर्ण

अटल पूर्णांक lgdt3306a_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lgdt3306a_config *config;
	काष्ठा lgdt3306a_state *state;
	काष्ठा dvb_frontend *fe;
	पूर्णांक ret;

	config = kmemdup(client->dev.platक्रमm_data,
			 माप(काष्ठा lgdt3306a_config), GFP_KERNEL);
	अगर (config == शून्य) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	config->i2c_addr = client->addr;
	fe = lgdt3306a_attach(config, client->adapter);
	अगर (fe == शून्य) अणु
		ret = -ENODEV;
		जाओ err_fe;
	पूर्ण

	i2c_set_clientdata(client, fe->demodulator_priv);
	state = fe->demodulator_priv;
	state->frontend.ops.release = शून्य;

	/* create mux i2c adapter क्रम tuner */
	state->muxc = i2c_mux_alloc(client->adapter, &client->dev,
				  1, 0, I2C_MUX_LOCKED,
				  lgdt3306a_select, lgdt3306a_deselect);
	अगर (!state->muxc) अणु
		ret = -ENOMEM;
		जाओ err_kमुक्त;
	पूर्ण
	state->muxc->priv = client;
	ret = i2c_mux_add_adapter(state->muxc, 0, 0, 0);
	अगर (ret)
		जाओ err_kमुक्त;

	/* create dvb_frontend */
	fe->ops.i2c_gate_ctrl = शून्य;
	*config->i2c_adapter = state->muxc->adapter[0];
	*config->fe = fe;

	dev_info(&client->dev, "LG Electronics LGDT3306A successfully identified\n");

	वापस 0;

err_kमुक्त:
	kमुक्त(state);
err_fe:
	kमुक्त(config);
fail:
	dev_warn(&client->dev, "probe failed = %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक lgdt3306a_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lgdt3306a_state *state = i2c_get_clientdata(client);

	i2c_mux_del_adapters(state->muxc);

	state->frontend.ops.release = शून्य;
	state->frontend.demodulator_priv = शून्य;

	kमुक्त(state->cfg);
	kमुक्त(state);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lgdt3306a_id_table[] = अणु
	अणु"lgdt3306a", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lgdt3306a_id_table);

अटल काष्ठा i2c_driver lgdt3306a_driver = अणु
	.driver = अणु
		.name                = "lgdt3306a",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= lgdt3306a_probe,
	.हटाओ		= lgdt3306a_हटाओ,
	.id_table	= lgdt3306a_id_table,
पूर्ण;

module_i2c_driver(lgdt3306a_driver);

MODULE_DESCRIPTION("LG Electronics LGDT3306A ATSC/QAM-B Demodulator Driver");
MODULE_AUTHOR("Fred Richter <frichter@hauppauge.com>");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.2");
