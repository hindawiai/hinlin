<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * descriptions + helper functions क्रम simple dvb plls.
 */

#अगर_अघोषित __DVB_PLL_H__
#घोषणा __DVB_PLL_H__

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

#घोषणा DVB_PLL_UNDEFINED               0
#घोषणा DVB_PLL_THOMSON_DTT7579         1
#घोषणा DVB_PLL_THOMSON_DTT759X         2
#घोषणा DVB_PLL_LG_Z201                 3
#घोषणा DVB_PLL_UNKNOWN_1               4
#घोषणा DVB_PLL_TUA6010XS               5
#घोषणा DVB_PLL_ENV57H1XD5              6
#घोषणा DVB_PLL_TUA6034                 7
#घोषणा DVB_PLL_TDA665X                 8
#घोषणा DVB_PLL_TDED4                   9
#घोषणा DVB_PLL_TDHU2                  10
#घोषणा DVB_PLL_SAMSUNG_TBMV           11
#घोषणा DVB_PLL_PHILIPS_SD1878_TDA8261 12
#घोषणा DVB_PLL_OPERA1                 13
#घोषणा DVB_PLL_SAMSUNG_DTOS403IH102A  14
#घोषणा DVB_PLL_SAMSUNG_TDTC9251DH0    15
#घोषणा DVB_PLL_SAMSUNG_TBDU18132      16
#घोषणा DVB_PLL_SAMSUNG_TBMU24112      17
#घोषणा DVB_PLL_TDEE4		       18
#घोषणा DVB_PLL_THOMSON_DTT7520X       19
#घोषणा DVB_PLL_TUA6034_FRIIO          20
#घोषणा DVB_PLL_TDA665X_EARTH_PT1      21

काष्ठा dvb_pll_config अणु
	काष्ठा dvb_frontend *fe;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_DVB_PLL)
/**
 * dvb_pll_attach - Attach a dvb-pll to the supplied frontend काष्ठाure.
 *
 * @fe: Frontend to attach to.
 * @pll_addr: i2c address of the PLL (अगर used).
 * @i2c: i2c adapter to use (set to शून्य अगर not used).
 * @pll_desc_id: dvb_pll_desc to use.
 *
 * वापस: Frontend poपूर्णांकer on success, शून्य on failure
 */
बाह्य काष्ठा dvb_frontend *dvb_pll_attach(काष्ठा dvb_frontend *fe,
					   पूर्णांक pll_addr,
					   काष्ठा i2c_adapter *i2c,
					   अचिन्हित पूर्णांक pll_desc_id);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *dvb_pll_attach(काष्ठा dvb_frontend *fe,
					   पूर्णांक pll_addr,
					   काष्ठा i2c_adapter *i2c,
					   अचिन्हित पूर्णांक pll_desc_id)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
