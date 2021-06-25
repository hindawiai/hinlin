<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2020 Intel Corporation.
 * Zhu YiXin <yixin.zhu@पूर्णांकel.com>
 * Rahul Tanwar <rahul.tanwar@पूर्णांकel.com>
 */

#अगर_अघोषित __CLK_CGU_H
#घोषणा __CLK_CGU_H

#समावेश <linux/पन.स>

काष्ठा lgm_clk_mux अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *membase;
	अचिन्हित पूर्णांक reg;
	u8 shअगरt;
	u8 width;
	अचिन्हित दीर्घ flags;
	spinlock_t lock;
पूर्ण;

काष्ठा lgm_clk_भागider अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *membase;
	अचिन्हित पूर्णांक reg;
	u8 shअगरt;
	u8 width;
	u8 shअगरt_gate;
	u8 width_gate;
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा clk_भाग_प्रकारable *table;
	spinlock_t lock;
पूर्ण;

काष्ठा lgm_clk_dभाग अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *membase;
	अचिन्हित पूर्णांक reg;
	u8 shअगरt0;
	u8 width0;
	u8 shअगरt1;
	u8 width1;
	u8 shअगरt2;
	u8 width2;
	u8 shअगरt_gate;
	u8 width_gate;
	अचिन्हित पूर्णांक mult;
	अचिन्हित पूर्णांक भाग;
	अचिन्हित दीर्घ flags;
	spinlock_t lock;
पूर्ण;

काष्ठा lgm_clk_gate अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *membase;
	अचिन्हित पूर्णांक reg;
	u8 shअगरt;
	अचिन्हित दीर्घ flags;
	spinlock_t lock;
पूर्ण;

क्रमागत lgm_clk_type अणु
	CLK_TYPE_FIXED,
	CLK_TYPE_MUX,
	CLK_TYPE_DIVIDER,
	CLK_TYPE_FIXED_FACTOR,
	CLK_TYPE_GATE,
	CLK_TYPE_NONE,
पूर्ण;

/**
 * काष्ठा lgm_clk_provider
 * @membase: IO mem base address क्रम CGU.
 * @np: device node
 * @dev: device
 * @clk_data: array of hw घड़ीs and clk number.
 */
काष्ठा lgm_clk_provider अणु
	व्योम __iomem *membase;
	काष्ठा device_node *np;
	काष्ठा device *dev;
	काष्ठा clk_hw_onecell_data clk_data;
	spinlock_t lock;
पूर्ण;

क्रमागत pll_type अणु
	TYPE_ROPLL,
	TYPE_LJPLL,
	TYPE_NONE,
पूर्ण;

काष्ठा lgm_clk_pll अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *membase;
	अचिन्हित पूर्णांक reg;
	अचिन्हित दीर्घ flags;
	क्रमागत pll_type type;
	spinlock_t lock;
पूर्ण;

/**
 * काष्ठा lgm_pll_clk_data
 * @id: platक्रमm specअगरic id of the घड़ी.
 * @name: name of this pll घड़ी.
 * @parent_data: parent घड़ी data.
 * @num_parents: number of parents.
 * @flags: optional flags क्रम basic घड़ी.
 * @type: platक्रमm type of pll.
 * @reg: offset of the रेजिस्टर.
 */
काष्ठा lgm_pll_clk_data अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर काष्ठा clk_parent_data *parent_data;
	u8 num_parents;
	अचिन्हित दीर्घ flags;
	क्रमागत pll_type type;
	पूर्णांक reg;
पूर्ण;

#घोषणा LGM_PLL(_id, _name, _pdata, _flags,		\
		_reg, _type)				\
	अणु						\
		.id = _id,				\
		.name = _name,				\
		.parent_data = _pdata,			\
		.num_parents = ARRAY_SIZE(_pdata),	\
		.flags = _flags,			\
		.reg = _reg,				\
		.type = _type,				\
	पूर्ण

काष्ठा lgm_clk_dभाग_data अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर काष्ठा clk_parent_data *parent_data;
	u8 flags;
	अचिन्हित दीर्घ भाग_flags;
	अचिन्हित पूर्णांक reg;
	u8 shअगरt0;
	u8 width0;
	u8 shअगरt1;
	u8 width1;
	u8 shअगरt_gate;
	u8 width_gate;
	u8 ex_shअगरt;
	u8 ex_width;
पूर्ण;

#घोषणा LGM_DDIV(_id, _name, _pname, _flags, _reg,		\
		 _shft0, _wdth0, _shft1, _wdth1,		\
		 _shft_gate, _wdth_gate, _xshft, _df)		\
	अणु							\
		.id = _id,					\
		.name = _name,					\
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु	\
			.fw_name = _pname,			\
			.name = _pname,				\
		पूर्ण,						\
		.flags = _flags,				\
		.reg = _reg,					\
		.shअगरt0 = _shft0,				\
		.width0 = _wdth0,				\
		.shअगरt1 = _shft1,				\
		.width1 = _wdth1,				\
		.shअगरt_gate = _shft_gate,			\
		.width_gate = _wdth_gate,			\
		.ex_shअगरt = _xshft,				\
		.ex_width = 1,					\
		.भाग_flags = _df,				\
	पूर्ण

काष्ठा lgm_clk_branch अणु
	अचिन्हित पूर्णांक id;
	क्रमागत lgm_clk_type type;
	स्थिर अक्षर *name;
	स्थिर काष्ठा clk_parent_data *parent_data;
	u8 num_parents;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक mux_off;
	u8 mux_shअगरt;
	u8 mux_width;
	अचिन्हित दीर्घ mux_flags;
	अचिन्हित पूर्णांक mux_val;
	अचिन्हित पूर्णांक भाग_off;
	u8 भाग_shअगरt;
	u8 भाग_width;
	u8 भाग_shअगरt_gate;
	u8 भाग_width_gate;
	अचिन्हित दीर्घ भाग_flags;
	अचिन्हित पूर्णांक भाग_val;
	स्थिर काष्ठा clk_भाग_प्रकारable *भाग_प्रकारable;
	अचिन्हित पूर्णांक gate_off;
	u8 gate_shअगरt;
	अचिन्हित दीर्घ gate_flags;
	अचिन्हित पूर्णांक gate_val;
	अचिन्हित पूर्णांक mult;
	अचिन्हित पूर्णांक भाग;
पूर्ण;

/* घड़ी flags definition */
#घोषणा CLOCK_FLAG_VAL_INIT	BIT(16)
#घोषणा MUX_CLK_SW		BIT(17)

#घोषणा LGM_MUX(_id, _name, _pdata, _f, _reg,		\
		_shअगरt, _width, _cf, _v)		\
	अणु						\
		.id = _id,				\
		.type = CLK_TYPE_MUX,			\
		.name = _name,				\
		.parent_data = _pdata,			\
		.num_parents = ARRAY_SIZE(_pdata),	\
		.flags = _f,				\
		.mux_off = _reg,			\
		.mux_shअगरt = _shअगरt,			\
		.mux_width = _width,			\
		.mux_flags = _cf,			\
		.mux_val = _v,				\
	पूर्ण

#घोषणा LGM_DIV(_id, _name, _pname, _f, _reg, _shअगरt, _width,	\
		_shअगरt_gate, _width_gate, _cf, _v, _dtable)	\
	अणु							\
		.id = _id,					\
		.type = CLK_TYPE_DIVIDER,			\
		.name = _name,					\
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु	\
			.fw_name = _pname,			\
			.name = _pname,				\
		पूर्ण,						\
		.num_parents = 1,				\
		.flags = _f,					\
		.भाग_off = _reg,				\
		.भाग_shअगरt = _shअगरt,				\
		.भाग_width = _width,				\
		.भाग_shअगरt_gate = _shअगरt_gate,			\
		.भाग_width_gate = _width_gate,			\
		.भाग_flags = _cf,				\
		.भाग_val = _v,					\
		.भाग_प्रकारable = _dtable,				\
	पूर्ण

#घोषणा LGM_GATE(_id, _name, _pname, _f, _reg,			\
		 _shअगरt, _cf, _v)				\
	अणु							\
		.id = _id,					\
		.type = CLK_TYPE_GATE,				\
		.name = _name,					\
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु	\
			.fw_name = _pname,			\
			.name = _pname,				\
		पूर्ण,						\
		.num_parents = !_pname ? 0 : 1,			\
		.flags = _f,					\
		.gate_off = _reg,				\
		.gate_shअगरt = _shअगरt,				\
		.gate_flags = _cf,				\
		.gate_val = _v,					\
	पूर्ण

#घोषणा LGM_FIXED(_id, _name, _pname, _f, _reg,			\
		  _shअगरt, _width, _cf, _freq, _v)		\
	अणु							\
		.id = _id,					\
		.type = CLK_TYPE_FIXED,				\
		.name = _name,					\
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु	\
			.fw_name = _pname,			\
			.name = _pname,				\
		पूर्ण,						\
		.num_parents = !_pname ? 0 : 1,			\
		.flags = _f,					\
		.भाग_off = _reg,				\
		.भाग_shअगरt = _shअगरt,				\
		.भाग_width = _width,				\
		.भाग_flags = _cf,				\
		.भाग_val = _v,					\
		.mux_flags = _freq,				\
	पूर्ण

#घोषणा LGM_FIXED_FACTOR(_id, _name, _pname, _f, _reg,		\
			 _shअगरt, _width, _cf, _v, _m, _d)	\
	अणु							\
		.id = _id,					\
		.type = CLK_TYPE_FIXED_FACTOR,			\
		.name = _name,					\
		.parent_data = &(स्थिर काष्ठा clk_parent_data)अणु	\
			.fw_name = _pname,			\
			.name = _pname,				\
		पूर्ण,						\
		.num_parents = 1,				\
		.flags = _f,					\
		.भाग_off = _reg,				\
		.भाग_shअगरt = _shअगरt,				\
		.भाग_width = _width,				\
		.भाग_flags = _cf,				\
		.भाग_val = _v,					\
		.mult = _m,					\
		.भाग = _d,					\
	पूर्ण

अटल अंतरभूत व्योम lgm_set_clk_val(व्योम __iomem *membase, u32 reg,
				   u8 shअगरt, u8 width, u32 set_val)
अणु
	u32 mask = (GENMASK(width - 1, 0) << shअगरt);
	u32 regval;

	regval = पढ़ोl(membase + reg);
	regval = (regval & ~mask) | ((set_val << shअगरt) & mask);
	ग_लिखोl(regval, membase + reg);
पूर्ण

अटल अंतरभूत u32 lgm_get_clk_val(व्योम __iomem *membase, u32 reg,
				  u8 shअगरt, u8 width)
अणु
	u32 mask = (GENMASK(width - 1, 0) << shअगरt);
	u32 val;

	val = पढ़ोl(membase + reg);
	val = (val & mask) >> shअगरt;

	वापस val;
पूर्ण

पूर्णांक lgm_clk_रेजिस्टर_branches(काष्ठा lgm_clk_provider *ctx,
			      स्थिर काष्ठा lgm_clk_branch *list,
			      अचिन्हित पूर्णांक nr_clk);
पूर्णांक lgm_clk_रेजिस्टर_plls(काष्ठा lgm_clk_provider *ctx,
			  स्थिर काष्ठा lgm_pll_clk_data *list,
			  अचिन्हित पूर्णांक nr_clk);
पूर्णांक lgm_clk_रेजिस्टर_dभाग(काष्ठा lgm_clk_provider *ctx,
			  स्थिर काष्ठा lgm_clk_dभाग_data *list,
			  अचिन्हित पूर्णांक nr_clk);
#पूर्ण_अगर	/* __CLK_CGU_H */
