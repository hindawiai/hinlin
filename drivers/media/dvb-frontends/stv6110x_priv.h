<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	STV6110(A) Silicon tuner driver

	Copyright (C) Manu Abraham <abraham.manu@gmail.com>

	Copyright (C) ST Microelectronics

*/

#अगर_अघोषित __STV6110x_PRIV_H
#घोषणा __STV6110x_PRIV_H

#घोषणा FE_ERROR				0
#घोषणा FE_NOTICE				1
#घोषणा FE_INFO					2
#घोषणा FE_DEBUG				3
#घोषणा FE_DEBUGREG				4

#घोषणा dprपूर्णांकk(__y, __z, क्रमmat, arg...) करो अणु						\
	अगर (__z) अणु									\
		अगर	((verbose > FE_ERROR) && (verbose > __y))			\
			prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", __func__ , ##arg);		\
		अन्यथा अगर	((verbose > FE_NOTICE) && (verbose > __y))			\
			prपूर्णांकk(KERN_NOTICE "%s: " क्रमmat "\n", __func__ , ##arg);	\
		अन्यथा अगर ((verbose > FE_INFO) && (verbose > __y))			\
			prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", __func__ , ##arg);		\
		अन्यथा अगर ((verbose > FE_DEBUG) && (verbose > __y))			\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n", __func__ , ##arg);	\
	पूर्ण अन्यथा अणु									\
		अगर (verbose > __y)							\
			prपूर्णांकk(क्रमmat, ##arg);						\
	पूर्ण										\
पूर्ण जबतक (0)


#घोषणा STV6110x_SETFIELD(mask, bitf, val)				\
	(mask = (mask & (~(((1 << STV6110x_WIDTH_##bitf) - 1) <<	\
				  STV6110x_OFFST_##bitf))) |		\
			  (val << STV6110x_OFFST_##bitf))

#घोषणा STV6110x_GETFIELD(bitf, val)					\
	((val >> STV6110x_OFFST_##bitf) &				\
	((1 << STV6110x_WIDTH_##bitf) - 1))

#घोषणा MAKEWORD16(a, b)			(((a) << 8) | (b))

#घोषणा LSB(x)					((x & 0xff))
#घोषणा MSB(y)					((y >> 8) & 0xff)

#घोषणा TRIALS					10
#घोषणा R_DIV(__भाग)				(1 << (__भाग + 1))
#घोषणा REFCLOCK_kHz				(stv6110x->config->refclk /    1000)
#घोषणा REFCLOCK_MHz				(stv6110x->config->refclk / 1000000)

काष्ठा stv6110x_state अणु
	काष्ठा dvb_frontend		*frontend;
	काष्ठा i2c_adapter		*i2c;
	स्थिर काष्ठा stv6110x_config	*config;
	u8				regs[8];

	काष्ठा stv6110x_devctl	*devctl;
पूर्ण;

#पूर्ण_अगर /* __STV6110x_PRIV_H */
