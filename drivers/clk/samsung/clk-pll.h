<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Copyright (c) 2013 Linaro Ltd.
 *
 * Common Clock Framework support क्रम all PLL's in Samsung platक्रमms
*/

#अगर_अघोषित __SAMSUNG_CLK_PLL_H
#घोषणा __SAMSUNG_CLK_PLL_H

क्रमागत samsung_pll_type अणु
	pll_2126,
	pll_3000,
	pll_35xx,
	pll_36xx,
	pll_2550,
	pll_2650,
	pll_4500,
	pll_4502,
	pll_4508,
	pll_4600,
	pll_4650,
	pll_4650c,
	pll_6552,
	pll_6552_s3c2416,
	pll_6553,
	pll_s3c2410_mpll,
	pll_s3c2410_upll,
	pll_s3c2440_mpll,
	pll_2550x,
	pll_2550xx,
	pll_2650x,
	pll_2650xx,
	pll_1450x,
	pll_1451x,
	pll_1452x,
	pll_1460x,
पूर्ण;

#घोषणा PLL_RATE(_fin, _m, _p, _s, _k, _ks) \
	((u64)(_fin) * (BIT(_ks) * (_m) + (_k)) / BIT(_ks) / ((_p) << (_s)))
#घोषणा PLL_VALID_RATE(_fin, _fout, _m, _p, _s, _k, _ks) ((_fout) + \
	BUILD_BUG_ON_ZERO(PLL_RATE(_fin, _m, _p, _s, _k, _ks) != (_fout)))

#घोषणा PLL_35XX_RATE(_fin, _rate, _m, _p, _s)			\
	अणु							\
		.rate	=	PLL_VALID_RATE(_fin, _rate,	\
				_m, _p, _s, 0, 16),		\
		.mभाग	=	(_m),				\
		.pभाग	=	(_p),				\
		.sभाग	=	(_s),				\
	पूर्ण

#घोषणा PLL_S3C2410_MPLL_RATE(_fin, _rate, _m, _p, _s)		\
	अणु							\
		.rate	=	PLL_VALID_RATE(_fin, _rate,	\
				_m + 8, _p + 2, _s, 0, 16),	\
		.mभाग	=	(_m),				\
		.pभाग	=	(_p),				\
		.sभाग	=	(_s),				\
	पूर्ण

#घोषणा PLL_S3C2440_MPLL_RATE(_fin, _rate, _m, _p, _s)		\
	अणु							\
		.rate	=	PLL_VALID_RATE(_fin, _rate,	\
				2 * (_m + 8), _p + 2, _s, 0, 16), \
		.mभाग	=	(_m),				\
		.pभाग	=	(_p),				\
		.sभाग	=	(_s),				\
	पूर्ण

#घोषणा PLL_36XX_RATE(_fin, _rate, _m, _p, _s, _k)		\
	अणु							\
		.rate	=	PLL_VALID_RATE(_fin, _rate,	\
				_m, _p, _s, _k, 16),		\
		.mभाग	=	(_m),				\
		.pभाग	=	(_p),				\
		.sभाग	=	(_s),				\
		.kभाग	=	(_k),				\
	पूर्ण

#घोषणा PLL_4508_RATE(_fin, _rate, _m, _p, _s, _afc)		\
	अणु							\
		.rate	=	PLL_VALID_RATE(_fin, _rate,	\
				_m, _p, _s - 1, 0, 16),		\
		.mभाग	=	(_m),				\
		.pभाग	=	(_p),				\
		.sभाग	=	(_s),				\
		.afc	=	(_afc),				\
	पूर्ण

#घोषणा PLL_4600_RATE(_fin, _rate, _m, _p, _s, _k, _vsel)	\
	अणु							\
		.rate	=	PLL_VALID_RATE(_fin, _rate,	\
				_m, _p, _s, _k, 16),		\
		.mभाग	=	(_m),				\
		.pभाग	=	(_p),				\
		.sभाग	=	(_s),				\
		.kभाग	=	(_k),				\
		.vsel	=	(_vsel),			\
	पूर्ण

#घोषणा PLL_4650_RATE(_fin, _rate, _m, _p, _s, _k, _mfr, _mrr, _vsel) \
	अणु							\
		.rate	=	PLL_VALID_RATE(_fin, _rate,	\
				_m, _p, _s, _k, 10),		\
		.mभाग	=	(_m),				\
		.pभाग	=	(_p),				\
		.sभाग	=	(_s),				\
		.kभाग	=	(_k),				\
		.mfr	=	(_mfr),				\
		.mrr	=	(_mrr),				\
		.vsel	=	(_vsel),			\
	पूर्ण

/* NOTE: Rate table should be kept sorted in descending order. */

काष्ठा samsung_pll_rate_table अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक pभाग;
	अचिन्हित पूर्णांक mभाग;
	अचिन्हित पूर्णांक sभाग;
	अचिन्हित पूर्णांक kभाग;
	अचिन्हित पूर्णांक afc;
	अचिन्हित पूर्णांक mfr;
	अचिन्हित पूर्णांक mrr;
	अचिन्हित पूर्णांक vsel;
पूर्ण;

#पूर्ण_अगर /* __SAMSUNG_CLK_PLL_H */
