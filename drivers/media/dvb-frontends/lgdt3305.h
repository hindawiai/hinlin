<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम LG Electronics LGDT3304 and LGDT3305 - VSB/QAM
 *
 *    Copyright (C) 2008, 2009, 2010 Michael Krufky <mkrufky@linuxtv.org>
 */

#अगर_अघोषित _LGDT3305_H_
#घोषणा _LGDT3305_H_

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>


क्रमागत lgdt3305_mpeg_mode अणु
	LGDT3305_MPEG_PARALLEL = 0,
	LGDT3305_MPEG_SERIAL = 1,
पूर्ण;

क्रमागत lgdt3305_tp_घड़ी_edge अणु
	LGDT3305_TPCLK_RISING_EDGE = 0,
	LGDT3305_TPCLK_FALLING_EDGE = 1,
पूर्ण;

क्रमागत lgdt3305_tp_घड़ी_mode अणु
	LGDT3305_TPCLK_GATED = 0,
	LGDT3305_TPCLK_FIXED = 1,
पूर्ण;

क्रमागत lgdt3305_tp_valid_polarity अणु
	LGDT3305_TP_VALID_LOW = 0,
	LGDT3305_TP_VALID_HIGH = 1,
पूर्ण;

क्रमागत lgdt_demod_chip_type अणु
	LGDT3305 = 0,
	LGDT3304 = 1,
पूर्ण;

काष्ठा lgdt3305_config अणु
	u8 i2c_addr;

	/* user defined IF frequency in KHz */
	u16 qam_अगर_khz;
	u16 vsb_अगर_khz;

	/* AGC Power reference - शेषs are used अगर left unset */
	u16 usref_8vsb;   /* शेष: 0x32c4 */
	u16 usref_qam64;  /* शेष: 0x5400 */
	u16 usref_qam256; /* शेष: 0x2a80 */

	/* disable i2c repeater - 0:repeater enabled 1:repeater disabled */
	अचिन्हित पूर्णांक deny_i2c_rptr:1;

	/* spectral inversion - 0:disabled 1:enabled */
	अचिन्हित पूर्णांक spectral_inversion:1;

	/* use RF AGC loop - 0:disabled 1:enabled */
	अचिन्हित पूर्णांक rf_agc_loop:1;

	क्रमागत lgdt3305_mpeg_mode mpeg_mode;
	क्रमागत lgdt3305_tp_घड़ी_edge tpclk_edge;
	क्रमागत lgdt3305_tp_घड़ी_mode tpclk_mode;
	क्रमागत lgdt3305_tp_valid_polarity tpvalid_polarity;
	क्रमागत lgdt_demod_chip_type demod_chip;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_LGDT3305)
बाह्य
काष्ठा dvb_frontend *lgdt3305_attach(स्थिर काष्ठा lgdt3305_config *config,
				     काष्ठा i2c_adapter *i2c_adap);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *lgdt3305_attach(स्थिर काष्ठा lgdt3305_config *config,
				     काष्ठा i2c_adapter *i2c_adap)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_LGDT3305 */

#पूर्ण_अगर /* _LGDT3305_H_ */
