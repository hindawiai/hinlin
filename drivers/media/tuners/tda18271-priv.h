<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    tda18271-priv.h - निजी header क्रम the NXP TDA18271 silicon tuner

    Copyright (C) 2007, 2008 Michael Krufky <mkrufky@linuxtv.org>

*/

#अगर_अघोषित __TDA18271_PRIV_H__
#घोषणा __TDA18271_PRIV_H__

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश "tuner-i2c.h"
#समावेश "tda18271.h"

#घोषणा R_ID     0x00	/* ID byte                */
#घोषणा R_TM     0x01	/* Thermo byte            */
#घोषणा R_PL     0x02	/* Power level byte       */
#घोषणा R_EP1    0x03	/* Easy Prog byte 1       */
#घोषणा R_EP2    0x04	/* Easy Prog byte 2       */
#घोषणा R_EP3    0x05	/* Easy Prog byte 3       */
#घोषणा R_EP4    0x06	/* Easy Prog byte 4       */
#घोषणा R_EP5    0x07	/* Easy Prog byte 5       */
#घोषणा R_CPD    0x08	/* Cal Post-Divider byte  */
#घोषणा R_CD1    0x09	/* Cal Divider byte 1     */
#घोषणा R_CD2    0x0a	/* Cal Divider byte 2     */
#घोषणा R_CD3    0x0b	/* Cal Divider byte 3     */
#घोषणा R_MPD    0x0c	/* Main Post-Divider byte */
#घोषणा R_MD1    0x0d	/* Main Divider byte 1    */
#घोषणा R_MD2    0x0e	/* Main Divider byte 2    */
#घोषणा R_MD3    0x0f	/* Main Divider byte 3    */
#घोषणा R_EB1    0x10	/* Extended byte 1        */
#घोषणा R_EB2    0x11	/* Extended byte 2        */
#घोषणा R_EB3    0x12	/* Extended byte 3        */
#घोषणा R_EB4    0x13	/* Extended byte 4        */
#घोषणा R_EB5    0x14	/* Extended byte 5        */
#घोषणा R_EB6    0x15	/* Extended byte 6        */
#घोषणा R_EB7    0x16	/* Extended byte 7        */
#घोषणा R_EB8    0x17	/* Extended byte 8        */
#घोषणा R_EB9    0x18	/* Extended byte 9        */
#घोषणा R_EB10   0x19	/* Extended byte 10       */
#घोषणा R_EB11   0x1a	/* Extended byte 11       */
#घोषणा R_EB12   0x1b	/* Extended byte 12       */
#घोषणा R_EB13   0x1c	/* Extended byte 13       */
#घोषणा R_EB14   0x1d	/* Extended byte 14       */
#घोषणा R_EB15   0x1e	/* Extended byte 15       */
#घोषणा R_EB16   0x1f	/* Extended byte 16       */
#घोषणा R_EB17   0x20	/* Extended byte 17       */
#घोषणा R_EB18   0x21	/* Extended byte 18       */
#घोषणा R_EB19   0x22	/* Extended byte 19       */
#घोषणा R_EB20   0x23	/* Extended byte 20       */
#घोषणा R_EB21   0x24	/* Extended byte 21       */
#घोषणा R_EB22   0x25	/* Extended byte 22       */
#घोषणा R_EB23   0x26	/* Extended byte 23       */

#घोषणा TDA18271_NUM_REGS 39

/*---------------------------------------------------------------------*/

काष्ठा tda18271_rf_tracking_filter_cal अणु
	u32 rfmax;
	u8  rfband;
	u32 rf1_def;
	u32 rf2_def;
	u32 rf3_def;
	u32 rf1;
	u32 rf2;
	u32 rf3;
	s32 rf_a1;
	s32 rf_b1;
	s32 rf_a2;
	s32 rf_b2;
पूर्ण;

क्रमागत tda18271_pll अणु
	TDA18271_MAIN_PLL,
	TDA18271_CAL_PLL,
पूर्ण;

काष्ठा tda18271_map_layout;

क्रमागत tda18271_ver अणु
	TDA18271HDC1,
	TDA18271HDC2,
पूर्ण;

काष्ठा tda18271_priv अणु
	अचिन्हित अक्षर tda18271_regs[TDA18271_NUM_REGS];

	काष्ठा list_head	hybrid_tuner_instance_list;
	काष्ठा tuner_i2c_props	i2c_props;

	क्रमागत tda18271_mode mode;
	क्रमागत tda18271_role role;
	क्रमागत tda18271_i2c_gate gate;
	क्रमागत tda18271_ver id;
	क्रमागत tda18271_output_options output_opt;
	क्रमागत tda18271_small_i2c small_i2c;

	अचिन्हित पूर्णांक config; /* पूर्णांकerface to saa713x / tda829x */
	अचिन्हित पूर्णांक cal_initialized:1;

	u8 पंचांग_rfcal;

	काष्ठा tda18271_map_layout *maps;
	काष्ठा tda18271_std_map std;
	काष्ठा tda18271_rf_tracking_filter_cal rf_cal_state[8];

	काष्ठा mutex lock;

	u16 अगर_freq;

	u32 frequency;
	u32 bandwidth;
पूर्ण;

/*---------------------------------------------------------------------*/

बाह्य पूर्णांक tda18271_debug;

#घोषणा DBG_INFO 1
#घोषणा DBG_MAP  2
#घोषणा DBG_REG  4
#घोषणा DBG_ADV  8
#घोषणा DBG_CAL  16

__attribute__((क्रमmat(म_लिखो, 4, 5)))
व्योम _tda_prपूर्णांकk(काष्ठा tda18271_priv *state, स्थिर अक्षर *level,
		 स्थिर अक्षर *func, स्थिर अक्षर *fmt, ...);

#घोषणा tda_prपूर्णांकk(st, lvl, fmt, arg...)			\
	_tda_prपूर्णांकk(st, lvl, __func__, fmt, ##arg)

#घोषणा tda_dprपूर्णांकk(st, lvl, fmt, arg...)			\
करो अणु								\
	अगर (tda18271_debug & lvl)				\
		tda_prपूर्णांकk(st, KERN_DEBUG, fmt, ##arg);		\
पूर्ण जबतक (0)

#घोषणा tda_info(fmt, arg...)	pr_info(fmt, ##arg)
#घोषणा tda_warn(fmt, arg...)	tda_prपूर्णांकk(priv, KERN_WARNING, fmt, ##arg)
#घोषणा tda_err(fmt, arg...)	tda_prपूर्णांकk(priv, KERN_ERR,     fmt, ##arg)
#घोषणा tda_dbg(fmt, arg...)	tda_dprपूर्णांकk(priv, DBG_INFO,    fmt, ##arg)
#घोषणा tda_map(fmt, arg...)	tda_dprपूर्णांकk(priv, DBG_MAP,     fmt, ##arg)
#घोषणा tda_reg(fmt, arg...)	tda_dprपूर्णांकk(priv, DBG_REG,     fmt, ##arg)
#घोषणा tda_cal(fmt, arg...)	tda_dprपूर्णांकk(priv, DBG_CAL,     fmt, ##arg)

#घोषणा tda_fail(ret)							     \
(अणु									     \
	पूर्णांक __ret;							     \
	__ret = (ret < 0);						     \
	अगर (__ret)							     \
		tda_prपूर्णांकk(priv, KERN_ERR,				     \
			   "error %d on line %d\n", ret, __LINE__);	     \
	__ret;								     \
पूर्ण)

/*---------------------------------------------------------------------*/

क्रमागत tda18271_map_type अणु
	/* tda18271_pll_map */
	MAIN_PLL,
	CAL_PLL,
	/* tda18271_map */
	RF_CAL,
	RF_CAL_KMCO,
	RF_CAL_DC_OVER_DT,
	BP_FILTER,
	RF_BAND,
	GAIN_TAPER,
	IR_MEASURE,
पूर्ण;

बाह्य पूर्णांक tda18271_lookup_pll_map(काष्ठा dvb_frontend *fe,
				   क्रमागत tda18271_map_type map_type,
				   u32 *freq, u8 *post_भाग, u8 *भाग);
बाह्य पूर्णांक tda18271_lookup_map(काष्ठा dvb_frontend *fe,
			       क्रमागत tda18271_map_type map_type,
			       u32 *freq, u8 *val);

बाह्य पूर्णांक tda18271_lookup_thermometer(काष्ठा dvb_frontend *fe);

बाह्य पूर्णांक tda18271_lookup_rf_band(काष्ठा dvb_frontend *fe,
				   u32 *freq, u8 *rf_band);

बाह्य पूर्णांक tda18271_lookup_cid_target(काष्ठा dvb_frontend *fe,
				      u32 *freq, u8 *cid_target,
				      u16 *count_limit);

बाह्य पूर्णांक tda18271_assign_map_layout(काष्ठा dvb_frontend *fe);

/*---------------------------------------------------------------------*/

बाह्य पूर्णांक tda18271_पढ़ो_regs(काष्ठा dvb_frontend *fe);
बाह्य पूर्णांक tda18271_पढ़ो_extended(काष्ठा dvb_frontend *fe);
बाह्य पूर्णांक tda18271_ग_लिखो_regs(काष्ठा dvb_frontend *fe, पूर्णांक idx, पूर्णांक len);
बाह्य पूर्णांक tda18271_init_regs(काष्ठा dvb_frontend *fe);

बाह्य पूर्णांक tda18271_अक्षरge_pump_source(काष्ठा dvb_frontend *fe,
				       क्रमागत tda18271_pll pll, पूर्णांक क्रमce);
बाह्य पूर्णांक tda18271_set_standby_mode(काष्ठा dvb_frontend *fe,
				     पूर्णांक sm, पूर्णांक sm_lt, पूर्णांक sm_xt);

बाह्य पूर्णांक tda18271_calc_मुख्य_pll(काष्ठा dvb_frontend *fe, u32 freq);
बाह्य पूर्णांक tda18271_calc_cal_pll(काष्ठा dvb_frontend *fe, u32 freq);

बाह्य पूर्णांक tda18271_calc_bp_filter(काष्ठा dvb_frontend *fe, u32 *freq);
बाह्य पूर्णांक tda18271_calc_km(काष्ठा dvb_frontend *fe, u32 *freq);
बाह्य पूर्णांक tda18271_calc_rf_band(काष्ठा dvb_frontend *fe, u32 *freq);
बाह्य पूर्णांक tda18271_calc_gain_taper(काष्ठा dvb_frontend *fe, u32 *freq);
बाह्य पूर्णांक tda18271_calc_ir_measure(काष्ठा dvb_frontend *fe, u32 *freq);
बाह्य पूर्णांक tda18271_calc_rf_cal(काष्ठा dvb_frontend *fe, u32 *freq);

#पूर्ण_अगर /* __TDA18271_PRIV_H__ */
