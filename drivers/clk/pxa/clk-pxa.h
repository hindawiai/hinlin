<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Marvell PXA family घड़ीs
 *
 * Copyright (C) 2014 Robert Jarzmik
 *
 * Common घड़ी code क्रम PXA घड़ीs ("CKEN" type घड़ीs + DT)
 */
#अगर_अघोषित _CLK_PXA_
#घोषणा _CLK_PXA_

#घोषणा CLKCFG_TURBO		0x1
#घोषणा CLKCFG_FCS		0x2
#घोषणा CLKCFG_HALFTURBO	0x4
#घोषणा CLKCFG_FASTBUS		0x8

#घोषणा PARENTS(name) \
	अटल स्थिर अक्षर *स्थिर name ## _parents[] __initस्थिर
#घोषणा MUX_RO_RATE_RO_OPS(name, clk_name)			\
	अटल काष्ठा clk_hw name ## _mux_hw;			\
	अटल काष्ठा clk_hw name ## _rate_hw;			\
	अटल स्थिर काष्ठा clk_ops name ## _mux_ops = अणु	\
		.get_parent = name ## _get_parent,		\
		.set_parent = dummy_clk_set_parent,		\
	पूर्ण;							\
	अटल स्थिर काष्ठा clk_ops name ## _rate_ops = अणु	\
		.recalc_rate = name ## _get_rate,		\
	पूर्ण;							\
	अटल काष्ठा clk * __init clk_रेजिस्टर_ ## name(व्योम)	\
	अणु							\
		वापस clk_रेजिस्टर_composite(शून्य, clk_name,	\
			name ## _parents,			\
			ARRAY_SIZE(name ## _parents),		\
			&name ## _mux_hw, &name ## _mux_ops,	\
			&name ## _rate_hw, &name ## _rate_ops,	\
			शून्य, शून्य, CLK_GET_RATE_NOCACHE);	\
	पूर्ण

#घोषणा RATE_RO_OPS(name, clk_name)				\
	अटल काष्ठा clk_hw name ## _rate_hw;			\
	अटल स्थिर काष्ठा clk_ops name ## _rate_ops = अणु	\
		.recalc_rate = name ## _get_rate,		\
	पूर्ण;							\
	अटल काष्ठा clk * __init clk_रेजिस्टर_ ## name(व्योम)	\
	अणु							\
		वापस clk_रेजिस्टर_composite(शून्य, clk_name,	\
			name ## _parents,			\
			ARRAY_SIZE(name ## _parents),		\
			शून्य, शून्य,				\
			&name ## _rate_hw, &name ## _rate_ops,	\
			शून्य, शून्य, CLK_GET_RATE_NOCACHE);	\
	पूर्ण

#घोषणा RATE_OPS(name, clk_name)				\
	अटल काष्ठा clk_hw name ## _rate_hw;			\
	अटल स्थिर काष्ठा clk_ops name ## _rate_ops = अणु	\
		.recalc_rate = name ## _get_rate,		\
		.set_rate = name ## _set_rate,			\
		.determine_rate = name ## _determine_rate,	\
	पूर्ण;							\
	अटल काष्ठा clk * __init clk_रेजिस्टर_ ## name(व्योम)	\
	अणु							\
		वापस clk_रेजिस्टर_composite(शून्य, clk_name,	\
			name ## _parents,			\
			ARRAY_SIZE(name ## _parents),		\
			शून्य, शून्य,				\
			&name ## _rate_hw, &name ## _rate_ops,	\
			शून्य, शून्य, CLK_GET_RATE_NOCACHE);	\
	पूर्ण

#घोषणा MUX_OPS(name, clk_name, flags)				\
	अटल काष्ठा clk_hw name ## _mux_hw;			\
	अटल स्थिर काष्ठा clk_ops name ## _mux_ops = अणु	\
		.get_parent = name ## _get_parent,		\
		.set_parent = name ## _set_parent,		\
		.determine_rate = name ## _determine_rate,	\
	पूर्ण;							\
	अटल काष्ठा clk * __init clk_रेजिस्टर_ ## name(व्योम)	\
	अणु							\
		वापस clk_रेजिस्टर_composite(शून्य, clk_name,	\
			name ## _parents,			\
			ARRAY_SIZE(name ## _parents),		\
			&name ## _mux_hw, &name ## _mux_ops,	\
			शून्य, शून्य,				\
			शून्य, शून्य,				\
			CLK_GET_RATE_NOCACHE | flags); \
	पूर्ण

/*
 * CKEN घड़ी type
 * This घड़ी takes it source from 2 possible parents :
 *  - a low घातer parent
 *  - a normal parent
 *
 *  +------------+     +-----------+
 *  |  Low Power | --- | x mult_lp |
 *  |    Clock   |     | / भाग_lp  |\
 *  +------------+     +-----------+ \+-----+   +-----------+
 *                                    | Mux |---| CKEN gate |
 *  +------------+     +-----------+ /+-----+   +-----------+
 *  | High Power |     | x mult_hp |/
 *  |    Clock   | --- | / भाग_hp  |
 *  +------------+     +-----------+
 */
काष्ठा desc_clk_cken अणु
	काष्ठा clk_hw hw;
	पूर्णांक ckid;
	स्थिर अक्षर *name;
	स्थिर अक्षर *dev_id;
	स्थिर अक्षर *con_id;
	स्थिर अक्षर * स्थिर *parent_names;
	काष्ठा clk_fixed_factor lp;
	काष्ठा clk_fixed_factor hp;
	काष्ठा clk_gate gate;
	bool (*is_in_low_घातer)(व्योम);
	स्थिर अचिन्हित दीर्घ flags;
पूर्ण;

#घोषणा PXA_CKEN(_dev_id, _con_id, _name, parents, _mult_lp, _भाग_lp,	\
		 _mult_hp, _भाग_hp, is_lp, _cken_reg, _cken_bit, flag)	\
	अणु .ckid = CLK_ ## _name, .name = #_name,			\
	  .dev_id = _dev_id, .con_id = _con_id,	.parent_names = parents,\
	  .lp = अणु .mult = _mult_lp, .भाग = _भाग_lp पूर्ण,			\
	  .hp = अणु .mult = _mult_hp, .भाग = _भाग_hp पूर्ण,			\
	  .is_in_low_घातer = is_lp,					\
	  .gate = अणु .reg = (व्योम __iomem *)_cken_reg, .bit_idx = _cken_bit पूर्ण, \
	  .flags = flag,						\
	पूर्ण
#घोषणा PXA_CKEN_1RATE(dev_id, con_id, name, parents, cken_reg,		\
			    cken_bit, flag)				\
	PXA_CKEN(dev_id, con_id, name, parents, 1, 1, 1, 1,		\
		 शून्य, cken_reg, cken_bit, flag)

काष्ठा pxa2xx_freq अणु
	अचिन्हित दीर्घ cpll;
	अचिन्हित पूर्णांक membus_khz;
	अचिन्हित पूर्णांक cccr;
	अचिन्हित पूर्णांक भाग2;
	अचिन्हित पूर्णांक clkcfg;
पूर्ण;

अटल अंतरभूत पूर्णांक dummy_clk_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	वापस 0;
पूर्ण

बाह्य व्योम clkdev_pxa_रेजिस्टर(पूर्णांक ckid, स्थिर अक्षर *con_id,
				स्थिर अक्षर *dev_id, काष्ठा clk *clk);
बाह्य पूर्णांक clk_pxa_cken_init(स्थिर काष्ठा desc_clk_cken *clks, पूर्णांक nb_clks);
व्योम clk_pxa_dt_common_init(काष्ठा device_node *np);

व्योम pxa2xx_core_turbo_चयन(bool on);
व्योम pxa2xx_cpll_change(काष्ठा pxa2xx_freq *freq,
			u32 (*mdrefr_dri)(अचिन्हित पूर्णांक), व्योम __iomem *mdrefr,
			व्योम __iomem *cccr);
पूर्णांक pxa2xx_determine_rate(काष्ठा clk_rate_request *req,
			  काष्ठा pxa2xx_freq *freqs,  पूर्णांक nb_freqs);

#पूर्ण_अगर
