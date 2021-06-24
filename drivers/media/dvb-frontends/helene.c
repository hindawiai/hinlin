<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * helene.c
 *
 * Sony HELENE DVB-S/S2 DVB-T/T2 DVB-C/C2 ISDB-T/S tuner driver (CXD2858ER)
 *
 * Copyright 2012 Sony Corporation
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
  */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/types.h>
#समावेश "helene.h"
#समावेश <media/dvb_frontend.h>

#घोषणा MAX_WRITE_REGSIZE 20

क्रमागत helene_state अणु
	STATE_UNKNOWN,
	STATE_SLEEP,
	STATE_ACTIVE
पूर्ण;

काष्ठा helene_priv अणु
	u32			frequency;
	u8			i2c_address;
	काष्ठा i2c_adapter	*i2c;
	क्रमागत helene_state	state;
	व्योम			*set_tuner_data;
	पूर्णांक			(*set_tuner)(व्योम *, पूर्णांक);
	क्रमागत helene_xtal xtal;
पूर्ण;

#घोषणा TERR_INTERNAL_LOOPFILTER_AVAILABLE(tv_प्रणाली) \
	(((tv_प्रणाली) != SONY_HELENE_DTV_DVBC_6) && \
	 ((tv_प्रणाली) != SONY_HELENE_DTV_DVBC_8)\
	 && ((tv_प्रणाली) != SONY_HELENE_DTV_DVBC2_6) && \
	 ((tv_प्रणाली) != SONY_HELENE_DTV_DVBC2_8))

#घोषणा HELENE_AUTO		0xff
#घोषणा HELENE_OFFSET(ofs)	((u8)(ofs) & 0x1F)
#घोषणा HELENE_BW_6		0x00
#घोषणा HELENE_BW_7		0x01
#घोषणा HELENE_BW_8		0x02
#घोषणा HELENE_BW_1_7		0x03

क्रमागत helene_tv_प्रणाली_t अणु
	SONY_HELENE_TV_SYSTEM_UNKNOWN,
	/* Terrestrial Analog */
	SONY_HELENE_ATV_MN_EIAJ,
	/**< System-M (Japan) (IF: Fp=5.75MHz in शेष) */
	SONY_HELENE_ATV_MN_SAP,
	/**< System-M (US)    (IF: Fp=5.75MHz in शेष) */
	SONY_HELENE_ATV_MN_A2,
	/**< System-M (Korea) (IF: Fp=5.9MHz in शेष) */
	SONY_HELENE_ATV_BG,
	/**< System-B/G       (IF: Fp=7.3MHz in शेष) */
	SONY_HELENE_ATV_I,
	/**< System-I         (IF: Fp=7.85MHz in शेष) */
	SONY_HELENE_ATV_DK,
	/**< System-D/K       (IF: Fp=7.85MHz in शेष) */
	SONY_HELENE_ATV_L,
	/**< System-L         (IF: Fp=7.85MHz in शेष) */
	SONY_HELENE_ATV_L_DASH,
	/**< System-L DASH    (IF: Fp=2.2MHz in शेष) */
	/* Terrestrial/Cable Digital */
	SONY_HELENE_DTV_8VSB,
	/**< ATSC 8VSB        (IF: Fc=3.7MHz in शेष) */
	SONY_HELENE_DTV_QAM,
	/**< US QAM           (IF: Fc=3.7MHz in शेष) */
	SONY_HELENE_DTV_ISDBT_6,
	/**< ISDB-T 6MHzBW    (IF: Fc=3.55MHz in शेष) */
	SONY_HELENE_DTV_ISDBT_7,
	/**< ISDB-T 7MHzBW    (IF: Fc=4.15MHz in शेष) */
	SONY_HELENE_DTV_ISDBT_8,
	/**< ISDB-T 8MHzBW    (IF: Fc=4.75MHz in शेष) */
	SONY_HELENE_DTV_DVBT_5,
	/**< DVB-T 5MHzBW     (IF: Fc=3.6MHz in शेष) */
	SONY_HELENE_DTV_DVBT_6,
	/**< DVB-T 6MHzBW     (IF: Fc=3.6MHz in शेष) */
	SONY_HELENE_DTV_DVBT_7,
	/**< DVB-T 7MHzBW     (IF: Fc=4.2MHz in शेष) */
	SONY_HELENE_DTV_DVBT_8,
	/**< DVB-T 8MHzBW     (IF: Fc=4.8MHz in शेष) */
	SONY_HELENE_DTV_DVBT2_1_7,
	/**< DVB-T2 1.7MHzBW  (IF: Fc=3.5MHz in शेष) */
	SONY_HELENE_DTV_DVBT2_5,
	/**< DVB-T2 5MHzBW    (IF: Fc=3.6MHz in शेष) */
	SONY_HELENE_DTV_DVBT2_6,
	/**< DVB-T2 6MHzBW    (IF: Fc=3.6MHz in शेष) */
	SONY_HELENE_DTV_DVBT2_7,
	/**< DVB-T2 7MHzBW    (IF: Fc=4.2MHz in शेष) */
	SONY_HELENE_DTV_DVBT2_8,
	/**< DVB-T2 8MHzBW    (IF: Fc=4.8MHz in शेष) */
	SONY_HELENE_DTV_DVBC_6,
	/**< DVB-C 6MHzBW     (IF: Fc=3.7MHz in शेष) */
	SONY_HELENE_DTV_DVBC_8,
	/**< DVB-C 8MHzBW     (IF: Fc=4.9MHz in शेष) */
	SONY_HELENE_DTV_DVBC2_6,
	/**< DVB-C2 6MHzBW    (IF: Fc=3.7MHz in शेष) */
	SONY_HELENE_DTV_DVBC2_8,
	/**< DVB-C2 8MHzBW    (IF: Fc=4.9MHz in शेष) */
	SONY_HELENE_DTV_DTMB,
	/**< DTMB             (IF: Fc=5.1MHz in शेष) */
	/* Satellite */
	SONY_HELENE_STV_ISDBS,
	/**< ISDB-S */
	SONY_HELENE_STV_DVBS,
	/**< DVB-S */
	SONY_HELENE_STV_DVBS2,
	/**< DVB-S2 */

	SONY_HELENE_ATV_MIN = SONY_HELENE_ATV_MN_EIAJ,
	/**< Minimum analog terrestrial प्रणाली */
	SONY_HELENE_ATV_MAX = SONY_HELENE_ATV_L_DASH,
	/**< Maximum analog terrestrial प्रणाली */
	SONY_HELENE_DTV_MIN = SONY_HELENE_DTV_8VSB,
	/**< Minimum digital terrestrial प्रणाली */
	SONY_HELENE_DTV_MAX = SONY_HELENE_DTV_DTMB,
	/**< Maximum digital terrestrial प्रणाली */
	SONY_HELENE_TERR_TV_SYSTEM_NUM,
	/**< Number of supported terrestrial broadcasting प्रणाली */
	SONY_HELENE_STV_MIN = SONY_HELENE_STV_ISDBS,
	/**< Minimum satellite प्रणाली */
	SONY_HELENE_STV_MAX = SONY_HELENE_STV_DVBS2
	/**< Maximum satellite प्रणाली */
पूर्ण;

काष्ठा helene_terr_adjust_param_t अणु
	/* < Addr:0x69 Bit[6:4] : RFVGA gain.
	 * 0xFF means Auto. (RF_GAIN_SEL = 1)
	 */
	uपूर्णांक8_t RF_GAIN;
	/* < Addr:0x69 Bit[3:0] : IF_BPF gain.
	*/
	uपूर्णांक8_t IF_BPF_GC;
	/* < Addr:0x6B Bit[3:0] : RF overload
	 * RF input detect level. (FRF <= 172MHz)
	*/
	uपूर्णांक8_t RFOVLD_DET_LV1_VL;
	/* < Addr:0x6B Bit[3:0] : RF overload
	 * RF input detect level. (172MHz < FRF <= 464MHz)
	*/
	uपूर्णांक8_t RFOVLD_DET_LV1_VH;
	/* < Addr:0x6B Bit[3:0] : RF overload
	 * RF input detect level. (FRF > 464MHz)
	*/
	uपूर्णांक8_t RFOVLD_DET_LV1_U;
	/* < Addr:0x6C Bit[2:0] :
	 * Internal RFAGC detect level. (FRF <= 172MHz)
	*/
	uपूर्णांक8_t IFOVLD_DET_LV_VL;
	/* < Addr:0x6C Bit[2:0] :
	 * Internal RFAGC detect level. (172MHz < FRF <= 464MHz)
	*/
	uपूर्णांक8_t IFOVLD_DET_LV_VH;
	/* < Addr:0x6C Bit[2:0] :
	 * Internal RFAGC detect level. (FRF > 464MHz)
	*/
	uपूर्णांक8_t IFOVLD_DET_LV_U;
	/* < Addr:0x6D Bit[5:4] :
	 * IF filter center offset.
	*/
	uपूर्णांक8_t IF_BPF_F0;
	/* < Addr:0x6D Bit[1:0] :
	 * 6MHzBW(0x00) or 7MHzBW(0x01)
	 * or 8MHzBW(0x02) or 1.7MHzBW(0x03)
	*/
	uपूर्णांक8_t BW;
	/* < Addr:0x6E Bit[4:0] :
	 * 5bit चिन्हित. IF offset (kHz) = FIF_OFFSET x 50
	*/
	uपूर्णांक8_t FIF_OFFSET;
	/* < Addr:0x6F Bit[4:0] :
	 * 5bit चिन्हित. BW offset (kHz) =
	 * BW_OFFSET x 50 (BW_OFFSET x 10 in 1.7MHzBW)
	*/
	uपूर्णांक8_t BW_OFFSET;
	/* < Addr:0x9C Bit[0]   :
	 * Local polarity. (0: Upper Local, 1: Lower Local)
	*/
	uपूर्णांक8_t IS_LOWERLOCAL;
पूर्ण;

अटल स्थिर काष्ठा helene_terr_adjust_param_t
terr_params[SONY_HELENE_TERR_TV_SYSTEM_NUM] = अणु
	/*< SONY_HELENE_TV_SYSTEM_UNKNOWN */
	अणुHELENE_AUTO, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		HELENE_BW_6, HELENE_OFFSET(0),  HELENE_OFFSET(0),  0x00पूर्ण,
	/* Analog */
	/**< SONY_HELENE_ATV_MN_EIAJ   (System-M (Japan)) */
	अणुHELENE_AUTO, 0x05, 0x03, 0x06, 0x03, 0x01, 0x01, 0x01, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(0),  HELENE_OFFSET(1),  0x00पूर्ण,
	/**< SONY_HELENE_ATV_MN_SAP    (System-M (US)) */
	अणुHELENE_AUTO, 0x05, 0x03, 0x06, 0x03, 0x01, 0x01, 0x01, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(0),  HELENE_OFFSET(1),  0x00पूर्ण,
	अणुHELENE_AUTO, 0x05, 0x03, 0x06, 0x03, 0x01, 0x01, 0x01, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(3),  HELENE_OFFSET(1),  0x00पूर्ण,
	/**< SONY_HELENE_ATV_MN_A2     (System-M (Korea)) */
	अणुHELENE_AUTO, 0x05, 0x03, 0x06, 0x03, 0x01, 0x01, 0x01, 0x00,
		HELENE_BW_7,  HELENE_OFFSET(11), HELENE_OFFSET(5),  0x00पूर्ण,
	/**< SONY_HELENE_ATV_BG        (System-B/G) */
	अणुHELENE_AUTO, 0x05, 0x03, 0x06, 0x03, 0x01, 0x01, 0x01, 0x00,
		HELENE_BW_8,  HELENE_OFFSET(2),  HELENE_OFFSET(-3), 0x00पूर्ण,
	/**< SONY_HELENE_ATV_I         (System-I) */
	अणुHELENE_AUTO, 0x05, 0x03, 0x06, 0x03, 0x01, 0x01, 0x01, 0x00,
		HELENE_BW_8,  HELENE_OFFSET(2),  HELENE_OFFSET(-3), 0x00पूर्ण,
	/**< SONY_HELENE_ATV_DK        (System-D/K) */
	अणुHELENE_AUTO, 0x03, 0x04, 0x0A, 0x04, 0x04, 0x04, 0x04, 0x00,
		HELENE_BW_8,  HELENE_OFFSET(2),  HELENE_OFFSET(-3), 0x00पूर्ण,
	/**< SONY_HELENE_ATV_L         (System-L) */
	अणुHELENE_AUTO, 0x03, 0x04, 0x0A, 0x04, 0x04, 0x04, 0x04, 0x00,
		HELENE_BW_8,  HELENE_OFFSET(-1), HELENE_OFFSET(4),  0x00पूर्ण,
	/**< SONY_HELENE_ATV_L_DASH    (System-L DASH) */
	/* Digital */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x03, 0x03, 0x03, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(-6), HELENE_OFFSET(-3), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_8VSB      (ATSC 8VSB) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(-6), HELENE_OFFSET(-3), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_QAM       (US QAM) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(-9), HELENE_OFFSET(-5), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_ISDBT_6   (ISDB-T 6MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_7,  HELENE_OFFSET(-7), HELENE_OFFSET(-6), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_ISDBT_7   (ISDB-T 7MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_8,  HELENE_OFFSET(-5), HELENE_OFFSET(-7), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_ISDBT_8   (ISDB-T 8MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(-8), HELENE_OFFSET(-3), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBT_5    (DVB-T 5MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(-8), HELENE_OFFSET(-3), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBT_6    (DVB-T 6MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_7,  HELENE_OFFSET(-6), HELENE_OFFSET(-5), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBT_7    (DVB-T 7MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_8,  HELENE_OFFSET(-4), HELENE_OFFSET(-6), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBT_8    (DVB-T 8MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_1_7, HELENE_OFFSET(-10), HELENE_OFFSET(-10), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBT2_1_7 (DVB-T2 1.7MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(-8), HELENE_OFFSET(-3), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBT2_5   (DVB-T2 5MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(-8), HELENE_OFFSET(-3), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBT2_6   (DVB-T2 6MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_7,  HELENE_OFFSET(-6), HELENE_OFFSET(-5), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBT2_7   (DVB-T2 7MHzBW) */
	अणुHELENE_AUTO, 0x09, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_8,  HELENE_OFFSET(-4), HELENE_OFFSET(-6), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBT2_8   (DVB-T2 8MHzBW) */
	अणुHELENE_AUTO, 0x05, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(-6), HELENE_OFFSET(-4), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBC_6    (DVB-C 6MHzBW) */
	अणुHELENE_AUTO, 0x05, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x00,
		HELENE_BW_8,  HELENE_OFFSET(-2), HELENE_OFFSET(-3), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBC_8    (DVB-C 8MHzBW) */
	अणुHELENE_AUTO, 0x03, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_6,  HELENE_OFFSET(-6), HELENE_OFFSET(-2), 0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBC2_6   (DVB-C2 6MHzBW) */
	अणुHELENE_AUTO, 0x03, 0x09, 0x09, 0x09, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_8,  HELENE_OFFSET(-2), HELENE_OFFSET(0),  0x00पूर्ण,
	/**< SONY_HELENE_DTV_DVBC2_8   (DVB-C2 8MHzBW) */
	अणुHELENE_AUTO, 0x04, 0x0B, 0x0B, 0x0B, 0x02, 0x02, 0x02, 0x00,
		HELENE_BW_8,  HELENE_OFFSET(2),  HELENE_OFFSET(1),  0x00पूर्ण
	/**< SONY_HELENE_DTV_DTMB      (DTMB) */
पूर्ण;

अटल व्योम helene_i2c_debug(काष्ठा helene_priv *priv,
		u8 reg, u8 ग_लिखो, स्थिर u8 *data, u32 len)
अणु
	dev_dbg(&priv->i2c->dev, "helene: I2C %s reg 0x%02x size %d\n",
			(ग_लिखो == 0 ? "read" : "write"), reg, len);
	prपूर्णांक_hex_dump_bytes("helene: I2C data: ",
			DUMP_PREFIX_OFFSET, data, len);
पूर्ण

अटल पूर्णांक helene_ग_लिखो_regs(काष्ठा helene_priv *priv,
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
		dev_warn(&priv->i2c->dev,
				"wr reg=%04x: len=%d vs %zu is too big!\n",
				reg, len + 1, माप(buf));
		वापस -E2BIG;
	पूर्ण

	helene_i2c_debug(priv, reg, 1, data, len);
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

अटल पूर्णांक helene_ग_लिखो_reg(काष्ठा helene_priv *priv, u8 reg, u8 val)
अणु
	u8 पंचांगp = val; /* see gcc.gnu.org/bugzilla/show_bug.cgi?id=81715 */

	वापस helene_ग_लिखो_regs(priv, reg, &पंचांगp, 1);
पूर्ण

अटल पूर्णांक helene_पढ़ो_regs(काष्ठा helene_priv *priv,
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
	helene_i2c_debug(priv, reg, 0, val, len);
	वापस 0;
पूर्ण

अटल पूर्णांक helene_पढ़ो_reg(काष्ठा helene_priv *priv, u8 reg, u8 *val)
अणु
	वापस helene_पढ़ो_regs(priv, reg, val, 1);
पूर्ण

अटल पूर्णांक helene_set_reg_bits(काष्ठा helene_priv *priv,
		u8 reg, u8 data, u8 mask)
अणु
	पूर्णांक res;
	u8 rdata;

	अगर (mask != 0xff) अणु
		res = helene_पढ़ो_reg(priv, reg, &rdata);
		अगर (res != 0)
			वापस res;
		data = ((data & mask) | (rdata & (mask ^ 0xFF)));
	पूर्ण
	वापस helene_ग_लिखो_reg(priv, reg, data);
पूर्ण

अटल पूर्णांक helene_enter_घातer_save(काष्ठा helene_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state == STATE_SLEEP)
		वापस 0;

	/* Standby setting क्रम CPU */
	helene_ग_लिखो_reg(priv, 0x88, 0x0);

	/* Standby setting क्रम पूर्णांकernal logic block */
	helene_ग_लिखो_reg(priv, 0x87, 0xC0);

	priv->state = STATE_SLEEP;
	वापस 0;
पूर्ण

अटल पूर्णांक helene_leave_घातer_save(काष्ठा helene_priv *priv)
अणु
	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	अगर (priv->state == STATE_ACTIVE)
		वापस 0;

	/* Standby setting क्रम पूर्णांकernal logic block */
	helene_ग_लिखो_reg(priv, 0x87, 0xC4);

	/* Standby setting क्रम CPU */
	helene_ग_लिखो_reg(priv, 0x88, 0x40);

	priv->state = STATE_ACTIVE;
	वापस 0;
पूर्ण

अटल पूर्णांक helene_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा helene_priv *priv = fe->tuner_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	वापस helene_leave_घातer_save(priv);
पूर्ण

अटल व्योम helene_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा helene_priv *priv = fe->tuner_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	kमुक्त(fe->tuner_priv);
	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक helene_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा helene_priv *priv = fe->tuner_priv;

	dev_dbg(&priv->i2c->dev, "%s()\n", __func__);
	helene_enter_घातer_save(priv);
	वापस 0;
पूर्ण

अटल क्रमागत helene_tv_प्रणाली_t helene_get_tv_प्रणाली(काष्ठा dvb_frontend *fe)
अणु
	क्रमागत helene_tv_प्रणाली_t प्रणाली = SONY_HELENE_TV_SYSTEM_UNKNOWN;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा helene_priv *priv = fe->tuner_priv;

	अगर (p->delivery_प्रणाली == SYS_DVBT) अणु
		अगर (p->bandwidth_hz <= 5000000)
			प्रणाली = SONY_HELENE_DTV_DVBT_5;
		अन्यथा अगर (p->bandwidth_hz <= 6000000)
			प्रणाली = SONY_HELENE_DTV_DVBT_6;
		अन्यथा अगर (p->bandwidth_hz <= 7000000)
			प्रणाली = SONY_HELENE_DTV_DVBT_7;
		अन्यथा अगर (p->bandwidth_hz <= 8000000)
			प्रणाली = SONY_HELENE_DTV_DVBT_8;
		अन्यथा अणु
			प्रणाली = SONY_HELENE_DTV_DVBT_8;
			p->bandwidth_hz = 8000000;
		पूर्ण
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_DVBT2) अणु
		अगर (p->bandwidth_hz <= 5000000)
			प्रणाली = SONY_HELENE_DTV_DVBT2_5;
		अन्यथा अगर (p->bandwidth_hz <= 6000000)
			प्रणाली = SONY_HELENE_DTV_DVBT2_6;
		अन्यथा अगर (p->bandwidth_hz <= 7000000)
			प्रणाली = SONY_HELENE_DTV_DVBT2_7;
		अन्यथा अगर (p->bandwidth_hz <= 8000000)
			प्रणाली = SONY_HELENE_DTV_DVBT2_8;
		अन्यथा अणु
			प्रणाली = SONY_HELENE_DTV_DVBT2_8;
			p->bandwidth_hz = 8000000;
		पूर्ण
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_DVBS) अणु
		प्रणाली = SONY_HELENE_STV_DVBS;
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_DVBS2) अणु
		प्रणाली = SONY_HELENE_STV_DVBS2;
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_ISDBS) अणु
		प्रणाली = SONY_HELENE_STV_ISDBS;
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_ISDBT) अणु
		अगर (p->bandwidth_hz <= 6000000)
			प्रणाली = SONY_HELENE_DTV_ISDBT_6;
		अन्यथा अगर (p->bandwidth_hz <= 7000000)
			प्रणाली = SONY_HELENE_DTV_ISDBT_7;
		अन्यथा अगर (p->bandwidth_hz <= 8000000)
			प्रणाली = SONY_HELENE_DTV_ISDBT_8;
		अन्यथा अणु
			प्रणाली = SONY_HELENE_DTV_ISDBT_8;
			p->bandwidth_hz = 8000000;
		पूर्ण
	पूर्ण अन्यथा अगर (p->delivery_प्रणाली == SYS_DVBC_ANNEX_A) अणु
		अगर (p->bandwidth_hz <= 6000000)
			प्रणाली = SONY_HELENE_DTV_DVBC_6;
		अन्यथा अगर (p->bandwidth_hz <= 8000000)
			प्रणाली = SONY_HELENE_DTV_DVBC_8;
	पूर्ण
	dev_dbg(&priv->i2c->dev,
			"%s(): HELENE DTV system %d (delsys %d, bandwidth %d)\n",
			__func__, (पूर्णांक)प्रणाली, p->delivery_प्रणाली,
			p->bandwidth_hz);
	वापस प्रणाली;
पूर्ण

अटल पूर्णांक helene_set_params_s(काष्ठा dvb_frontend *fe)
अणु
	u8 data[MAX_WRITE_REGSIZE];
	u32 frequency;
	क्रमागत helene_tv_प्रणाली_t tv_प्रणाली;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा helene_priv *priv = fe->tuner_priv;
	पूर्णांक frequencykHz = p->frequency;
	uपूर्णांक32_t frequency4kHz = 0;
	u32 symbol_rate = p->symbol_rate/1000;

	dev_dbg(&priv->i2c->dev, "%s(): tune frequency %dkHz sr=%uKsps\n",
			__func__, frequencykHz, symbol_rate);
	tv_प्रणाली = helene_get_tv_प्रणाली(fe);

	अगर (tv_प्रणाली == SONY_HELENE_TV_SYSTEM_UNKNOWN) अणु
		dev_err(&priv->i2c->dev, "%s(): unknown DTV system\n",
				__func__);
		वापस -EINVAL;
	पूर्ण
	/* RF चयन turn to satellite */
	अगर (priv->set_tuner)
		priv->set_tuner(priv->set_tuner_data, 0);
	frequency = roundup(p->frequency / 1000, 1);

	/* Disable IF संकेत output */
	helene_ग_लिखो_reg(priv, 0x15, 0x02);

	/* RFIN matching in घातer save (Sat) reset */
	helene_ग_लिखो_reg(priv, 0x43, 0x06);

	/* Analog block setting (0x6A, 0x6B) */
	data[0] = 0x00;
	data[1] = 0x00;
	helene_ग_लिखो_regs(priv, 0x6A, data, 2);
	helene_ग_लिखो_reg(priv, 0x75, 0x99);
	helene_ग_लिखो_reg(priv, 0x9D, 0x00);

	/* Tuning setting क्रम CPU (0x61) */
	helene_ग_लिखो_reg(priv, 0x61, 0x07);

	/* Satellite mode select (0x01) */
	helene_ग_लिखो_reg(priv, 0x01, 0x01);

	/* Clock enable क्रम पूर्णांकernal logic block, CPU wake-up (0x04, 0x05) */
	data[0] = 0xC4;
	data[1] = 0x40;

	चयन (priv->xtal) अणु
	हाल SONY_HELENE_XTAL_16000:
		data[2] = 0x02;
		अवरोध;
	हाल SONY_HELENE_XTAL_20500:
		data[2] = 0x02;
		अवरोध;
	हाल SONY_HELENE_XTAL_24000:
		data[2] = 0x03;
		अवरोध;
	हाल SONY_HELENE_XTAL_41000:
		data[2] = 0x05;
		अवरोध;
	शेष:
		dev_err(&priv->i2c->dev, "%s(): unknown xtal %d\n",
				__func__, priv->xtal);
		वापस -EINVAL;
	पूर्ण

	/* Setting क्रम analog block (0x07). LOOPFILTER INTERNAL */
	data[3] = 0x80;

	/* Tuning setting क्रम analog block
	 * (0x08, 0x09, 0x0A, 0x0B). LOOPFILTER INTERNAL
	*/
	अगर (priv->xtal == SONY_HELENE_XTAL_20500)
		data[4] = 0x58;
	अन्यथा
		data[4] = 0x70;

	data[5] = 0x1E;
	data[6] = 0x02;
	data[7] = 0x24;

	/* Enable क्रम analog block (0x0C, 0x0D, 0x0E). SAT LNA ON */
	data[8] = 0x0F;
	data[8] |= 0xE0; /* POWERSAVE_TERR_RF_ACTIVE */
	data[9]  = 0x02;
	data[10] = 0x1E;

	/* Setting क्रम LPF cutoff frequency (0x0F) */
	चयन (tv_प्रणाली) अणु
	हाल SONY_HELENE_STV_ISDBS:
		data[11] = 0x22; /* 22MHz */
		अवरोध;
	हाल SONY_HELENE_STV_DVBS:
		अगर (symbol_rate <= 4000)
			data[11] = 0x05;
		अन्यथा अगर (symbol_rate <= 10000)
			data[11] = (uपूर्णांक8_t)((symbol_rate * 47
						+ (40000-1)) / 40000);
		अन्यथा
			data[11] = (uपूर्णांक8_t)((symbol_rate * 27
						+ (40000-1)) / 40000 + 5);

		अगर (data[11] > 36)
			data[11] = 36; /* 5 <= lpf_cutoff <= 36 is valid */
		अवरोध;
	हाल SONY_HELENE_STV_DVBS2:
		अगर (symbol_rate <= 4000)
			data[11] = 0x05;
		अन्यथा अगर (symbol_rate <= 10000)
			data[11] = (uपूर्णांक8_t)((symbol_rate * 11
						+ (10000-1)) / 10000);
		अन्यथा
			data[11] = (uपूर्णांक8_t)((symbol_rate * 3
						+ (5000-1)) / 5000 + 5);

		अगर (data[11] > 36)
			data[11] = 36; /* 5 <= lpf_cutoff <= 36 is valid */
		अवरोध;
	शेष:
		dev_err(&priv->i2c->dev, "%s(): unknown standard %d\n",
				__func__, tv_प्रणाली);
		वापस -EINVAL;
	पूर्ण

	/* RF tuning frequency setting (0x10, 0x11, 0x12) */
	frequency4kHz = (frequencykHz + 2) / 4;
	data[12] = (uपूर्णांक8_t)(frequency4kHz & 0xFF);         /* FRF_L */
	data[13] = (uपूर्णांक8_t)((frequency4kHz >> 8) & 0xFF);  /* FRF_M */
	/* FRF_H (bit[3:0]) */
	data[14] = (uपूर्णांक8_t)((frequency4kHz >> 16) & 0x0F);

	/* Tuning command (0x13) */
	data[15] = 0xFF;

	/* Setting क्रम IQOUT_LIMIT (0x14) 0.75Vpp */
	data[16] = 0x00;

	/* Enable IQ output (0x15) */
	data[17] = 0x01;

	helene_ग_लिखो_regs(priv, 0x04, data, 18);

	dev_dbg(&priv->i2c->dev, "%s(): tune done\n",
			__func__);

	priv->frequency = frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक helene_set_params_t(काष्ठा dvb_frontend *fe)
अणु
	u8 data[MAX_WRITE_REGSIZE];
	u32 frequency;
	क्रमागत helene_tv_प्रणाली_t tv_प्रणाली;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा helene_priv *priv = fe->tuner_priv;
	पूर्णांक frequencykHz = p->frequency / 1000;

	dev_dbg(&priv->i2c->dev, "%s(): tune frequency %dkHz\n",
			__func__, frequencykHz);
	tv_प्रणाली = helene_get_tv_प्रणाली(fe);

	अगर (tv_प्रणाली == SONY_HELENE_TV_SYSTEM_UNKNOWN) अणु
		dev_dbg(&priv->i2c->dev, "%s(): unknown DTV system\n",
				__func__);
		वापस -EINVAL;
	पूर्ण
	अगर (priv->set_tuner)
		priv->set_tuner(priv->set_tuner_data, 1);
	frequency = roundup(p->frequency / 1000, 25);

	/* mode select */
	helene_ग_लिखो_reg(priv, 0x01, 0x00);

	/* Disable IF संकेत output */
	helene_ग_लिखो_reg(priv, 0x74, 0x02);

	अगर (priv->state == STATE_SLEEP)
		helene_leave_घातer_save(priv);

	/* Initial setting क्रम पूर्णांकernal analog block (0x91, 0x92) */
	अगर ((tv_प्रणाली == SONY_HELENE_DTV_DVBC_6) ||
			(tv_प्रणाली == SONY_HELENE_DTV_DVBC_8)) अणु
		data[0] = 0x16;
		data[1] = 0x26;
	पूर्ण अन्यथा अणु
		data[0] = 0x10;
		data[1] = 0x20;
	पूर्ण
	helene_ग_लिखो_regs(priv, 0x91, data, 2);

	/* Setting क्रम analog block */
	अगर (TERR_INTERNAL_LOOPFILTER_AVAILABLE(tv_प्रणाली))
		data[0] = 0x90;
	अन्यथा
		data[0] = 0x00;

	/* Setting क्रम local polarity (0x9D) */
	data[1] = (uपूर्णांक8_t)(terr_params[tv_प्रणाली].IS_LOWERLOCAL & 0x01);
	helene_ग_लिखो_regs(priv, 0x9C, data, 2);

	/* Enable क्रम analog block */
	data[0] = 0xEE;
	data[1] = 0x02;
	data[2] = 0x1E;
	data[3] = 0x67; /* Tuning setting क्रम CPU */

	/* Setting क्रम PLL reference भागider क्रम xtal=24MHz */
	अगर ((tv_प्रणाली == SONY_HELENE_DTV_DVBC_6) ||
			(tv_प्रणाली == SONY_HELENE_DTV_DVBC_8))
		data[4] = 0x18;
	अन्यथा
		data[4] = 0x03;

	/* Tuning setting क्रम analog block */
	अगर (TERR_INTERNAL_LOOPFILTER_AVAILABLE(tv_प्रणाली)) अणु
		data[5] = 0x38;
		data[6] = 0x1E;
		data[7] = 0x02;
		data[8] = 0x24;
	पूर्ण अन्यथा अगर ((tv_प्रणाली == SONY_HELENE_DTV_DVBC_6) ||
			(tv_प्रणाली == SONY_HELENE_DTV_DVBC_8)) अणु
		data[5] = 0x1C;
		data[6] = 0x78;
		data[7] = 0x08;
		data[8] = 0x1C;
	पूर्ण अन्यथा अणु
		data[5] = 0xB4;
		data[6] = 0x78;
		data[7] = 0x08;
		data[8] = 0x30;
	पूर्ण
	helene_ग_लिखो_regs(priv, 0x5E, data, 9);

	/* LT_AMP_EN should be 0 */
	helene_set_reg_bits(priv, 0x67, 0x0, 0x02);

	/* Setting क्रम IFOUT_LIMIT */
	data[0] = 0x00; /* 1.5Vpp */

	/* RF_GAIN setting */
	अगर (terr_params[tv_प्रणाली].RF_GAIN == HELENE_AUTO)
		data[1] = 0x80; /* RF_GAIN_SEL = 1 */
	अन्यथा
		data[1] = (uपूर्णांक8_t)((terr_params[tv_प्रणाली].RF_GAIN
					<< 4) & 0x70);

	/* IF_BPF_GC setting */
	data[1] |= (uपूर्णांक8_t)(terr_params[tv_प्रणाली].IF_BPF_GC & 0x0F);

	/* Setting क्रम पूर्णांकernal RFAGC (0x6A, 0x6B, 0x6C) */
	data[2] = 0x00;
	अगर (frequencykHz <= 172000) अणु
		data[3] = (uपूर्णांक8_t)(terr_params[tv_प्रणाली].RFOVLD_DET_LV1_VL
				& 0x0F);
		data[4] = (uपूर्णांक8_t)(terr_params[tv_प्रणाली].IFOVLD_DET_LV_VL
				& 0x07);
	पूर्ण अन्यथा अगर (frequencykHz <= 464000) अणु
		data[3] = (uपूर्णांक8_t)(terr_params[tv_प्रणाली].RFOVLD_DET_LV1_VH
				& 0x0F);
		data[4] = (uपूर्णांक8_t)(terr_params[tv_प्रणाली].IFOVLD_DET_LV_VH
				& 0x07);
	पूर्ण अन्यथा अणु
		data[3] = (uपूर्णांक8_t)(terr_params[tv_प्रणाली].RFOVLD_DET_LV1_U
				& 0x0F);
		data[4] = (uपूर्णांक8_t)(terr_params[tv_प्रणाली].IFOVLD_DET_LV_U
				& 0x07);
	पूर्ण
	data[4] |= 0x20;

	/* Setting क्रम IF frequency and bandwidth */

	/* IF filter center frequency offset (IF_BPF_F0) (0x6D) */
	data[5] = (uपूर्णांक8_t)((terr_params[tv_प्रणाली].IF_BPF_F0 << 4) & 0x30);

	/* IF filter band width (BW) (0x6D) */
	data[5] |= (uपूर्णांक8_t)(terr_params[tv_प्रणाली].BW & 0x03);

	/* IF frequency offset value (FIF_OFFSET) (0x6E) */
	data[6] = (uपूर्णांक8_t)(terr_params[tv_प्रणाली].FIF_OFFSET & 0x1F);

	/* IF band width offset value (BW_OFFSET) (0x6F) */
	data[7] = (uपूर्णांक8_t)(terr_params[tv_प्रणाली].BW_OFFSET & 0x1F);

	/* RF tuning frequency setting (0x70, 0x71, 0x72) */
	data[8]  = (uपूर्णांक8_t)(frequencykHz & 0xFF);         /* FRF_L */
	data[9]  = (uपूर्णांक8_t)((frequencykHz >> 8) & 0xFF);  /* FRF_M */
	data[10] = (uपूर्णांक8_t)((frequencykHz >> 16)
			& 0x0F); /* FRF_H (bit[3:0]) */

	/* Tuning command */
	data[11] = 0xFF;

	/* Enable IF output, AGC and IFOUT pin selection (0x74) */
	data[12] = 0x01;

	अगर ((tv_प्रणाली == SONY_HELENE_DTV_DVBC_6) ||
			(tv_प्रणाली == SONY_HELENE_DTV_DVBC_8)) अणु
		data[13] = 0xD9;
		data[14] = 0x0F;
		data[15] = 0x24;
		data[16] = 0x87;
	पूर्ण अन्यथा अणु
		data[13] = 0x99;
		data[14] = 0x00;
		data[15] = 0x24;
		data[16] = 0x87;
	पूर्ण

	helene_ग_लिखो_regs(priv, 0x68, data, 17);

	dev_dbg(&priv->i2c->dev, "%s(): tune done\n",
			__func__);

	priv->frequency = frequency;
	वापस 0;
पूर्ण

अटल पूर्णांक helene_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	अगर (p->delivery_प्रणाली == SYS_DVBT ||
	    p->delivery_प्रणाली == SYS_DVBT2 ||
	    p->delivery_प्रणाली == SYS_ISDBT ||
	    p->delivery_प्रणाली == SYS_DVBC_ANNEX_A)
		वापस helene_set_params_t(fe);

	वापस helene_set_params_s(fe);
पूर्ण

अटल पूर्णांक helene_get_frequency(काष्ठा dvb_frontend *fe, u32 *frequency)
अणु
	काष्ठा helene_priv *priv = fe->tuner_priv;

	*frequency = priv->frequency * 1000;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops helene_tuner_ops_t = अणु
	.info = अणु
		.name = "Sony HELENE Ter tuner",
		.frequency_min_hz  =    1 * MHz,
		.frequency_max_hz  = 1200 * MHz,
		.frequency_step_hz =   25 * kHz,
	पूर्ण,
	.init = helene_init,
	.release = helene_release,
	.sleep = helene_sleep,
	.set_params = helene_set_params_t,
	.get_frequency = helene_get_frequency,
पूर्ण;

अटल स्थिर काष्ठा dvb_tuner_ops helene_tuner_ops_s = अणु
	.info = अणु
		.name = "Sony HELENE Sat tuner",
		.frequency_min_hz  =  500 * MHz,
		.frequency_max_hz  = 2500 * MHz,
		.frequency_step_hz =    1 * MHz,
	पूर्ण,
	.init = helene_init,
	.release = helene_release,
	.sleep = helene_sleep,
	.set_params = helene_set_params_s,
	.get_frequency = helene_get_frequency,
पूर्ण;

अटल स्थिर काष्ठा dvb_tuner_ops helene_tuner_ops = अणु
	.info = अणु
		.name = "Sony HELENE Sat/Ter tuner",
		.frequency_min_hz  =    1 * MHz,
		.frequency_max_hz  = 2500 * MHz,
		.frequency_step_hz =   25 * kHz,
	पूर्ण,
	.init = helene_init,
	.release = helene_release,
	.sleep = helene_sleep,
	.set_params = helene_set_params,
	.get_frequency = helene_get_frequency,
पूर्ण;

/* घातer-on tuner
 * call once after reset
 */
अटल पूर्णांक helene_x_pon(काष्ठा helene_priv *priv)
अणु
	/* RFIN matching in घातer save (terrestrial) = ACTIVE */
	/* RFIN matching in घातer save (satellite) = ACTIVE */
	u8 dataT[] = अणु 0x06, 0x00, 0x02, 0x00 पूर्ण;
	/* SAT_RF_ACTIVE = true, lnaOff = false, terrRfActive = true */
	u8 dataS[] = अणु 0x05, 0x06 पूर्ण;
	u8 cdata[] = अणु0x7A, 0x01पूर्ण;
	u8 data[20];
	u8 rdata[2];

	/* mode select */
	helene_ग_लिखो_reg(priv, 0x01, 0x00);

	helene_ग_लिखो_reg(priv, 0x67, dataT[3]);
	helene_ग_लिखो_reg(priv, 0x43, dataS[1]);
	helene_ग_लिखो_regs(priv, 0x5E, dataT, 3);
	helene_ग_लिखो_reg(priv, 0x0C, dataS[0]);

	/* Initial setting क्रम पूर्णांकernal logic block */
	helene_ग_लिखो_regs(priv, 0x99, cdata, माप(cdata));

	/* 0x81 - 0x94 */
	अगर (priv->xtal == SONY_HELENE_XTAL_16000)
		data[0] = 0x10; /* xtal 16 MHz */
	अन्यथा
		data[0] = 0x18; /* xtal 24 MHz */
	data[1] = (uपूर्णांक8_t)(0x80 | (0x04 & 0x1F)); /* 4 x 25 = 100uA */
	data[2] = (uपूर्णांक8_t)(0x80 | (0x26 & 0x7F)); /* 38 x 0.25 = 9.5pF */
	data[3] = 0x80; /* REFOUT संकेत output 500mVpp */
	data[4] = 0x00; /* GPIO settings */
	data[5] = 0x00; /* GPIO settings */
	data[6] = 0xC4; /* Clock enable क्रम पूर्णांकernal logic block */
	data[7] = 0x40; /* Start CPU boot-up */
	data[8] = 0x10; /* For burst-ग_लिखो */

	/* Setting क्रम पूर्णांकernal RFAGC */
	data[9] = 0x00;
	data[10] = 0x45;
	data[11] = 0x75;

	data[12] = 0x07; /* Setting क्रम analog block */

	/* Initial setting क्रम पूर्णांकernal analog block */
	data[13] = 0x1C;
	data[14] = 0x3F;
	data[15] = 0x02;
	data[16] = 0x10;
	data[17] = 0x20;
	data[18] = 0x0A;
	data[19] = 0x00;

	helene_ग_लिखो_regs(priv, 0x81, data, माप(data));

	/* Setting क्रम पूर्णांकernal RFAGC */
	helene_ग_लिखो_reg(priv, 0x9B, 0x00);

	msleep(20);

	/* Check CPU_STT/CPU_ERR */
	helene_पढ़ो_regs(priv, 0x1A, rdata, माप(rdata));

	अगर (rdata[0] != 0x00) अणु
		dev_err(&priv->i2c->dev,
				"HELENE tuner CPU error 0x%x\n", rdata[0]);
		वापस -EIO;
	पूर्ण

	/* VCO current setting */
	cdata[0] = 0x90;
	cdata[1] = 0x06;
	helene_ग_लिखो_regs(priv, 0x17, cdata, माप(cdata));
	msleep(20);
	helene_पढ़ो_reg(priv, 0x19, data);
	helene_ग_लिखो_reg(priv, 0x95, (uपूर्णांक8_t)((data[0] >> 4) & 0x0F));

	/* Disable IF संकेत output */
	helene_ग_लिखो_reg(priv, 0x74, 0x02);

	/* Standby setting क्रम CPU */
	helene_ग_लिखो_reg(priv, 0x88, 0x00);

	/* Standby setting क्रम पूर्णांकernal logic block */
	helene_ग_लिखो_reg(priv, 0x87, 0xC0);

	/* Load capacitance control setting क्रम crystal oscillator */
	helene_ग_लिखो_reg(priv, 0x80, 0x01);

	/* Satellite initial setting */
	cdata[0] = 0x07;
	cdata[1] = 0x00;
	helene_ग_लिखो_regs(priv, 0x41, cdata, माप(cdata));

	dev_info(&priv->i2c->dev,
			"HELENE tuner x_pon done\n");

	वापस 0;
पूर्ण

काष्ठा dvb_frontend *helene_attach_s(काष्ठा dvb_frontend *fe,
		स्थिर काष्ठा helene_config *config,
		काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा helene_priv *priv = शून्य;

	priv = kzalloc(माप(काष्ठा helene_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;
	priv->i2c_address = (config->i2c_address >> 1);
	priv->i2c = i2c;
	priv->set_tuner_data = config->set_tuner_priv;
	priv->set_tuner = config->set_tuner_callback;
	priv->xtal = config->xtal;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	अगर (helene_x_pon(priv) != 0) अणु
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	स_नकल(&fe->ops.tuner_ops, &helene_tuner_ops_s,
			माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = priv;
	dev_info(&priv->i2c->dev,
			"Sony HELENE Sat attached on addr=%x at I2C adapter %p\n",
			priv->i2c_address, priv->i2c);
	वापस fe;
पूर्ण
EXPORT_SYMBOL(helene_attach_s);

काष्ठा dvb_frontend *helene_attach(काष्ठा dvb_frontend *fe,
		स्थिर काष्ठा helene_config *config,
		काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा helene_priv *priv = शून्य;

	priv = kzalloc(माप(काष्ठा helene_priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस शून्य;
	priv->i2c_address = (config->i2c_address >> 1);
	priv->i2c = i2c;
	priv->set_tuner_data = config->set_tuner_priv;
	priv->set_tuner = config->set_tuner_callback;
	priv->xtal = config->xtal;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	अगर (helene_x_pon(priv) != 0) अणु
		kमुक्त(priv);
		वापस शून्य;
	पूर्ण

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	स_नकल(&fe->ops.tuner_ops, &helene_tuner_ops_t,
			माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = priv;
	dev_info(&priv->i2c->dev,
			"Sony HELENE Ter attached on addr=%x at I2C adapter %p\n",
			priv->i2c_address, priv->i2c);
	वापस fe;
पूर्ण
EXPORT_SYMBOL(helene_attach);

अटल पूर्णांक helene_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा helene_config *config = client->dev.platक्रमm_data;
	काष्ठा dvb_frontend *fe = config->fe;
	काष्ठा device *dev = &client->dev;
	काष्ठा helene_priv *priv;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->i2c_address = client->addr;
	priv->i2c = client->adapter;
	priv->set_tuner_data = config->set_tuner_priv;
	priv->set_tuner = config->set_tuner_callback;
	priv->xtal = config->xtal;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	अगर (helene_x_pon(priv) != 0)
		वापस -EINVAL;

	अगर (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	स_नकल(&fe->ops.tuner_ops, &helene_tuner_ops,
	       माप(काष्ठा dvb_tuner_ops));
	fe->tuner_priv = priv;
	i2c_set_clientdata(client, priv);

	dev_info(dev, "Sony HELENE attached on addr=%x at I2C adapter %p\n",
		 priv->i2c_address, priv->i2c);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id helene_id[] = अणु
	अणु "helene", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, helene_id);

अटल काष्ठा i2c_driver helene_driver = अणु
	.driver = अणु
		.name = "helene",
	पूर्ण,
	.probe    = helene_probe,
	.id_table = helene_id,
पूर्ण;
module_i2c_driver(helene_driver);

MODULE_DESCRIPTION("Sony HELENE Sat/Ter tuner driver");
MODULE_AUTHOR("Abylay Ospan <aospan@netup.ru>");
MODULE_LICENSE("GPL");
