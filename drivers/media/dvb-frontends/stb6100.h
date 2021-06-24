<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	STB6100 Silicon Tuner
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

	Copyright (C) ST Microelectronics

*/

#अगर_अघोषित __STB_6100_REG_H
#घोषणा __STB_6100_REG_H

#समावेश <linux/dvb/frontend.h>
#समावेश <media/dvb_frontend.h>

#घोषणा STB6100_LD			0x00
#घोषणा STB6100_LD_LOCK			(1 << 0)

#घोषणा STB6100_VCO			0x01
#घोषणा STB6100_VCO_OSCH		(0x01 << 7)
#घोषणा STB6100_VCO_OSCH_SHIFT		7
#घोषणा STB6100_VCO_OCK			(0x03 << 5)
#घोषणा STB6100_VCO_OCK_SHIFT		5
#घोषणा STB6100_VCO_ODIV		(0x01 << 4)
#घोषणा STB6100_VCO_ODIV_SHIFT		4
#घोषणा STB6100_VCO_OSM			(0x0f << 0)

#घोषणा STB6100_NI			0x02
#घोषणा STB6100_NF_LSB			0x03

#घोषणा STB6100_K			0x04
#घोषणा STB6100_K_PSD2			(0x01 << 2)
#घोषणा STB6100_K_PSD2_SHIFT            2
#घोषणा STB6100_K_NF_MSB		(0x03 << 0)

#घोषणा STB6100_G			0x05
#घोषणा STB6100_G_G			(0x0f << 0)
#घोषणा STB6100_G_GCT			(0x07 << 5)

#घोषणा STB6100_F			0x06
#घोषणा STB6100_F_F			(0x1f << 0)

#घोषणा STB6100_DLB			0x07

#घोषणा STB6100_TEST1			0x08

#घोषणा STB6100_FCCK			0x09
#घोषणा STB6100_FCCK_FCCK		(0x01 << 6)

#घोषणा STB6100_LPEN			0x0a
#घोषणा STB6100_LPEN_LPEN		(0x01 << 4)
#घोषणा STB6100_LPEN_SYNP		(0x01 << 5)
#घोषणा STB6100_LPEN_OSCP		(0x01 << 6)
#घोषणा STB6100_LPEN_BEN		(0x01 << 7)

#घोषणा STB6100_TEST3			0x0b

#घोषणा STB6100_NUMREGS                 0x0c


#घोषणा INRANGE(val, x, y)		(((x <= val) && (val <= y)) ||		\
					 ((y <= val) && (val <= x)) ? 1 : 0)

#घोषणा CHKRANGE(val, x, y)		(((val >= x) && (val < y)) ? 1 : 0)

काष्ठा stb6100_config अणु
	u8	tuner_address;
	u32	refघड़ी;
पूर्ण;

काष्ठा stb6100_state अणु
	काष्ठा i2c_adapter *i2c;

	स्थिर काष्ठा stb6100_config	*config;
	काष्ठा dvb_tuner_ops		ops;
	काष्ठा dvb_frontend		*frontend;

	u32 frequency;
	u32 srate;
	u32 bandwidth;
	u32 reference;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_STB6100)

बाह्य काष्ठा dvb_frontend *stb6100_attach(काष्ठा dvb_frontend *fe,
					   स्थिर काष्ठा stb6100_config *config,
					   काष्ठा i2c_adapter *i2c);

#अन्यथा

अटल अंतरभूत काष्ठा dvb_frontend *stb6100_attach(काष्ठा dvb_frontend *fe,
						  स्थिर काष्ठा stb6100_config *config,
						  काष्ठा i2c_adapter *i2c)
अणु
	prपूर्णांकk(KERN_WARNING "%s: Driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर //CONFIG_DVB_STB6100

#पूर्ण_अगर
