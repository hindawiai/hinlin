<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *    Support क्रम LGDT3306A - 8VSB/QAM-B
 *
 *    Copyright (C) 2013,2014 Fred Richter <frichter@hauppauge.com>
 *      based on lgdt3305.[ch] by Michael Krufky
 */

#अगर_अघोषित _LGDT3306A_H_
#घोषणा _LGDT3306A_H_

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>


क्रमागत lgdt3306a_mpeg_mode अणु
	LGDT3306A_MPEG_PARALLEL = 0,
	LGDT3306A_MPEG_SERIAL = 1,
पूर्ण;

क्रमागत lgdt3306a_tp_घड़ी_edge अणु
	LGDT3306A_TPCLK_RISING_EDGE = 0,
	LGDT3306A_TPCLK_FALLING_EDGE = 1,
पूर्ण;

क्रमागत lgdt3306a_tp_valid_polarity अणु
	LGDT3306A_TP_VALID_LOW = 0,
	LGDT3306A_TP_VALID_HIGH = 1,
पूर्ण;

काष्ठा lgdt3306a_config अणु
	u8 i2c_addr;

	/* user defined IF frequency in KHz */
	u16 qam_अगर_khz;
	u16 vsb_अगर_khz;

	/* disable i2c repeater - 0:repeater enabled 1:repeater disabled */
	अचिन्हित पूर्णांक deny_i2c_rptr:1;

	/* spectral inversion - 0:disabled 1:enabled */
	अचिन्हित पूर्णांक spectral_inversion:1;

	क्रमागत lgdt3306a_mpeg_mode mpeg_mode;
	क्रमागत lgdt3306a_tp_घड़ी_edge tpclk_edge;
	क्रमागत lgdt3306a_tp_valid_polarity tpvalid_polarity;

	/* demod घड़ी freq in MHz; 24 or 25 supported */
	पूर्णांक  xtalMHz;

	/* वापसed by driver अगर using i2c bus multiplexing */
	काष्ठा dvb_frontend **fe;
	काष्ठा i2c_adapter **i2c_adapter;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_LGDT3306A)
काष्ठा dvb_frontend *lgdt3306a_attach(स्थिर काष्ठा lgdt3306a_config *config,
				      काष्ठा i2c_adapter *i2c_adap);
#अन्यथा
अटल अंतरभूत
काष्ठा dvb_frontend *lgdt3306a_attach(स्थिर काष्ठा lgdt3306a_config *config,
				      काष्ठा i2c_adapter *i2c_adap)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_LGDT3306A */

#पूर्ण_अगर /* _LGDT3306A_H_ */
