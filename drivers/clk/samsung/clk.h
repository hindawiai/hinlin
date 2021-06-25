<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Copyright (c) 2013 Linaro Ltd.
 * Author: Thomas Abraham <thomas.ab@samsung.com>
 *
 * Common Clock Framework support क्रम all Samsung platक्रमms
*/

#अगर_अघोषित __SAMSUNG_CLK_H
#घोषणा __SAMSUNG_CLK_H

#समावेश <linux/clk-provider.h>
#समावेश "clk-pll.h"

/**
 * काष्ठा samsung_clk_provider: inक्रमmation about घड़ी provider
 * @reg_base: भव address क्रम the रेजिस्टर base.
 * @lock: मुख्यtains exclusion between callbacks क्रम a given घड़ी-provider.
 * @clk_data: holds घड़ी related data like clk_hw* and number of घड़ीs.
 */
काष्ठा samsung_clk_provider अणु
	व्योम __iomem *reg_base;
	काष्ठा device *dev;
	spinlock_t lock;
	/* clk_data must be the last entry due to variable length 'hws' array */
	काष्ठा clk_hw_onecell_data clk_data;
पूर्ण;

/**
 * काष्ठा samsung_घड़ी_alias: inक्रमmation about mux घड़ी
 * @id: platक्रमm specअगरic id of the घड़ी.
 * @dev_name: name of the device to which this घड़ी beदीर्घs.
 * @alias: optional घड़ी alias name to be asचिन्हित to this घड़ी.
 */
काष्ठा samsung_घड़ी_alias अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*dev_name;
	स्थिर अक्षर		*alias;
पूर्ण;

#घोषणा ALIAS(_id, dname, a)	\
	अणु							\
		.id		= _id,				\
		.dev_name	= dname,			\
		.alias		= a,				\
	पूर्ण

#घोषणा MHZ (1000 * 1000)

/**
 * काष्ठा samsung_fixed_rate_घड़ी: inक्रमmation about fixed-rate घड़ी
 * @id: platक्रमm specअगरic id of the घड़ी.
 * @name: name of this fixed-rate घड़ी.
 * @parent_name: optional parent घड़ी name.
 * @flags: optional fixed-rate घड़ी flags.
 * @fixed-rate: fixed घड़ी rate of this घड़ी.
 */
काष्ठा samsung_fixed_rate_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	अक्षर			*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		fixed_rate;
पूर्ण;

#घोषणा FRATE(_id, cname, pname, f, frate)		\
	अणु						\
		.id		= _id,			\
		.name		= cname,		\
		.parent_name	= pname,		\
		.flags		= f,			\
		.fixed_rate	= frate,		\
	पूर्ण

/*
 * काष्ठा samsung_fixed_factor_घड़ी: inक्रमmation about fixed-factor घड़ी
 * @id: platक्रमm specअगरic id of the घड़ी.
 * @name: name of this fixed-factor घड़ी.
 * @parent_name: parent घड़ी name.
 * @mult: fixed multiplication factor.
 * @भाग: fixed भागision factor.
 * @flags: optional fixed-factor घड़ी flags.
 */
काष्ठा samsung_fixed_factor_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	अक्षर			*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		mult;
	अचिन्हित दीर्घ		भाग;
	अचिन्हित दीर्घ		flags;
पूर्ण;

#घोषणा FFACTOR(_id, cname, pname, m, d, f)		\
	अणु						\
		.id		= _id,			\
		.name		= cname,		\
		.parent_name	= pname,		\
		.mult		= m,			\
		.भाग		= d,			\
		.flags		= f,			\
	पूर्ण

/**
 * काष्ठा samsung_mux_घड़ी: inक्रमmation about mux घड़ी
 * @id: platक्रमm specअगरic id of the घड़ी.
 * @name: name of this mux घड़ी.
 * @parent_names: array of poपूर्णांकer to parent घड़ी names.
 * @num_parents: number of parents listed in @parent_names.
 * @flags: optional flags क्रम basic घड़ी.
 * @offset: offset of the रेजिस्टर क्रम configuring the mux.
 * @shअगरt: starting bit location of the mux control bit-field in @reg.
 * @width: width of the mux control bit-field in @reg.
 * @mux_flags: flags क्रम mux-type घड़ी.
 */
काष्ठा samsung_mux_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*स्थिर *parent_names;
	u8			num_parents;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
	u8			shअगरt;
	u8			width;
	u8			mux_flags;
पूर्ण;

#घोषणा __MUX(_id, cname, pnames, o, s, w, f, mf)		\
	अणु							\
		.id		= _id,				\
		.name		= cname,			\
		.parent_names	= pnames,			\
		.num_parents	= ARRAY_SIZE(pnames),		\
		.flags		= (f) | CLK_SET_RATE_NO_REPARENT, \
		.offset		= o,				\
		.shअगरt		= s,				\
		.width		= w,				\
		.mux_flags	= mf,				\
	पूर्ण

#घोषणा MUX(_id, cname, pnames, o, s, w)			\
	__MUX(_id, cname, pnames, o, s, w, 0, 0)

#घोषणा MUX_F(_id, cname, pnames, o, s, w, f, mf)		\
	__MUX(_id, cname, pnames, o, s, w, f, mf)

/**
 * @id: platक्रमm specअगरic id of the घड़ी.
 * काष्ठा samsung_भाग_घड़ी: inक्रमmation about भाग घड़ी
 * @name: name of this भाग घड़ी.
 * @parent_name: name of the parent घड़ी.
 * @flags: optional flags क्रम basic घड़ी.
 * @offset: offset of the रेजिस्टर क्रम configuring the भाग.
 * @shअगरt: starting bit location of the भाग control bit-field in @reg.
 * @भाग_flags: flags क्रम भाग-type घड़ी.
 */
काष्ठा samsung_भाग_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
	u8			shअगरt;
	u8			width;
	u8			भाग_flags;
	काष्ठा clk_भाग_प्रकारable	*table;
पूर्ण;

#घोषणा __DIV(_id, cname, pname, o, s, w, f, df, t)	\
	अणु							\
		.id		= _id,				\
		.name		= cname,			\
		.parent_name	= pname,			\
		.flags		= f,				\
		.offset		= o,				\
		.shअगरt		= s,				\
		.width		= w,				\
		.भाग_flags	= df,				\
		.table		= t,				\
	पूर्ण

#घोषणा DIV(_id, cname, pname, o, s, w)				\
	__DIV(_id, cname, pname, o, s, w, 0, 0, शून्य)

#घोषणा DIV_F(_id, cname, pname, o, s, w, f, df)		\
	__DIV(_id, cname, pname, o, s, w, f, df, शून्य)

#घोषणा DIV_T(_id, cname, pname, o, s, w, t)			\
	__DIV(_id, cname, pname, o, s, w, 0, 0, t)

/**
 * काष्ठा samsung_gate_घड़ी: inक्रमmation about gate घड़ी
 * @id: platक्रमm specअगरic id of the घड़ी.
 * @name: name of this gate घड़ी.
 * @parent_name: name of the parent घड़ी.
 * @flags: optional flags क्रम basic घड़ी.
 * @offset: offset of the रेजिस्टर क्रम configuring the gate.
 * @bit_idx: bit index of the gate control bit-field in @reg.
 * @gate_flags: flags क्रम gate-type घड़ी.
 */
काष्ठा samsung_gate_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
	u8			bit_idx;
	u8			gate_flags;
पूर्ण;

#घोषणा __GATE(_id, cname, pname, o, b, f, gf)			\
	अणु							\
		.id		= _id,				\
		.name		= cname,			\
		.parent_name	= pname,			\
		.flags		= f,				\
		.offset		= o,				\
		.bit_idx	= b,				\
		.gate_flags	= gf,				\
	पूर्ण

#घोषणा GATE(_id, cname, pname, o, b, f, gf)			\
	__GATE(_id, cname, pname, o, b, f, gf)

#घोषणा PNAME(x) अटल स्थिर अक्षर * स्थिर x[] __initस्थिर

/**
 * काष्ठा samsung_clk_reg_dump: रेजिस्टर dump of घड़ी controller रेजिस्टरs.
 * @offset: घड़ी रेजिस्टर offset from the controller base address.
 * @value: the value to be रेजिस्टर at offset.
 */
काष्ठा samsung_clk_reg_dump अणु
	u32	offset;
	u32	value;
पूर्ण;

/**
 * काष्ठा samsung_pll_घड़ी: inक्रमmation about pll घड़ी
 * @id: platक्रमm specअगरic id of the घड़ी.
 * @name: name of this pll घड़ी.
 * @parent_name: name of the parent घड़ी.
 * @flags: optional flags क्रम basic घड़ी.
 * @con_offset: offset of the रेजिस्टर क्रम configuring the PLL.
 * @lock_offset: offset of the रेजिस्टर क्रम locking the PLL.
 * @type: Type of PLL to be रेजिस्टरed.
 */
काष्ठा samsung_pll_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	अचिन्हित दीर्घ		flags;
	पूर्णांक			con_offset;
	पूर्णांक			lock_offset;
	क्रमागत samsung_pll_type	type;
	स्थिर काष्ठा samsung_pll_rate_table *rate_table;
पूर्ण;

#घोषणा __PLL(_typ, _id, _name, _pname, _flags, _lock, _con, _rtable)	\
	अणु								\
		.id		= _id,					\
		.type		= _typ,					\
		.name		= _name,				\
		.parent_name	= _pname,				\
		.flags		= _flags,				\
		.con_offset	= _con,					\
		.lock_offset	= _lock,				\
		.rate_table	= _rtable,				\
	पूर्ण

#घोषणा PLL(_typ, _id, _name, _pname, _lock, _con, _rtable)	\
	__PLL(_typ, _id, _name, _pname, CLK_GET_RATE_NOCACHE, _lock,	\
	      _con, _rtable)

काष्ठा samsung_घड़ी_reg_cache अणु
	काष्ठा list_head node;
	व्योम __iomem *reg_base;
	काष्ठा samsung_clk_reg_dump *rdump;
	अचिन्हित पूर्णांक rd_num;
	स्थिर काष्ठा samsung_clk_reg_dump *rsuspend;
	अचिन्हित पूर्णांक rsuspend_num;
पूर्ण;

काष्ठा samsung_cmu_info अणु
	/* list of pll घड़ीs and respective count */
	स्थिर काष्ठा samsung_pll_घड़ी *pll_clks;
	अचिन्हित पूर्णांक nr_pll_clks;
	/* list of mux घड़ीs and respective count */
	स्थिर काष्ठा samsung_mux_घड़ी *mux_clks;
	अचिन्हित पूर्णांक nr_mux_clks;
	/* list of भाग घड़ीs and respective count */
	स्थिर काष्ठा samsung_भाग_घड़ी *भाग_clks;
	अचिन्हित पूर्णांक nr_भाग_clks;
	/* list of gate घड़ीs and respective count */
	स्थिर काष्ठा samsung_gate_घड़ी *gate_clks;
	अचिन्हित पूर्णांक nr_gate_clks;
	/* list of fixed घड़ीs and respective count */
	स्थिर काष्ठा samsung_fixed_rate_घड़ी *fixed_clks;
	अचिन्हित पूर्णांक nr_fixed_clks;
	/* list of fixed factor घड़ीs and respective count */
	स्थिर काष्ठा samsung_fixed_factor_घड़ी *fixed_factor_clks;
	अचिन्हित पूर्णांक nr_fixed_factor_clks;
	/* total number of घड़ीs with IDs asचिन्हित*/
	अचिन्हित पूर्णांक nr_clk_ids;

	/* list and number of घड़ीs रेजिस्टरs */
	स्थिर अचिन्हित दीर्घ *clk_regs;
	अचिन्हित पूर्णांक nr_clk_regs;

	/* list and number of घड़ीs रेजिस्टरs to set beक्रमe suspend */
	स्थिर काष्ठा samsung_clk_reg_dump *suspend_regs;
	अचिन्हित पूर्णांक nr_suspend_regs;
	/* name of the parent घड़ी needed क्रम CMU रेजिस्टर access */
	स्थिर अक्षर *clk_name;
पूर्ण;

बाह्य काष्ठा samsung_clk_provider *__init samsung_clk_init(
			काष्ठा device_node *np, व्योम __iomem *base,
			अचिन्हित दीर्घ nr_clks);
बाह्य व्योम __init samsung_clk_of_add_provider(काष्ठा device_node *np,
			काष्ठा samsung_clk_provider *ctx);
बाह्य व्योम __init samsung_clk_of_रेजिस्टर_fixed_ext(
			काष्ठा samsung_clk_provider *ctx,
			काष्ठा samsung_fixed_rate_घड़ी *fixed_rate_clk,
			अचिन्हित पूर्णांक nr_fixed_rate_clk,
			स्थिर काष्ठा of_device_id *clk_matches);

बाह्य व्योम samsung_clk_add_lookup(काष्ठा samsung_clk_provider *ctx,
			काष्ठा clk_hw *clk_hw, अचिन्हित पूर्णांक id);

बाह्य व्योम __init samsung_clk_रेजिस्टर_alias(काष्ठा samsung_clk_provider *ctx,
			स्थिर काष्ठा samsung_घड़ी_alias *list,
			अचिन्हित पूर्णांक nr_clk);
बाह्य व्योम __init samsung_clk_रेजिस्टर_fixed_rate(
			काष्ठा samsung_clk_provider *ctx,
			स्थिर काष्ठा samsung_fixed_rate_घड़ी *clk_list,
			अचिन्हित पूर्णांक nr_clk);
बाह्य व्योम __init samsung_clk_रेजिस्टर_fixed_factor(
			काष्ठा samsung_clk_provider *ctx,
			स्थिर काष्ठा samsung_fixed_factor_घड़ी *list,
			अचिन्हित पूर्णांक nr_clk);
बाह्य व्योम __init samsung_clk_रेजिस्टर_mux(काष्ठा samsung_clk_provider *ctx,
			स्थिर काष्ठा samsung_mux_घड़ी *clk_list,
			अचिन्हित पूर्णांक nr_clk);
बाह्य व्योम __init samsung_clk_रेजिस्टर_भाग(काष्ठा samsung_clk_provider *ctx,
			स्थिर काष्ठा samsung_भाग_घड़ी *clk_list,
			अचिन्हित पूर्णांक nr_clk);
बाह्य व्योम __init samsung_clk_रेजिस्टर_gate(काष्ठा samsung_clk_provider *ctx,
			स्थिर काष्ठा samsung_gate_घड़ी *clk_list,
			अचिन्हित पूर्णांक nr_clk);
बाह्य व्योम __init samsung_clk_रेजिस्टर_pll(काष्ठा samsung_clk_provider *ctx,
			स्थिर काष्ठा samsung_pll_घड़ी *pll_list,
			अचिन्हित पूर्णांक nr_clk, व्योम __iomem *base);

बाह्य काष्ठा samsung_clk_provider __init *samsung_cmu_रेजिस्टर_one(
			काष्ठा device_node *,
			स्थिर काष्ठा samsung_cmu_info *);

बाह्य अचिन्हित दीर्घ _get_rate(स्थिर अक्षर *clk_name);

#अगर_घोषित CONFIG_PM_SLEEP
बाह्य व्योम samsung_clk_extended_sleep_init(व्योम __iomem *reg_base,
			स्थिर अचिन्हित दीर्घ *rdump,
			अचिन्हित दीर्घ nr_rdump,
			स्थिर काष्ठा samsung_clk_reg_dump *rsuspend,
			अचिन्हित दीर्घ nr_rsuspend);
#अन्यथा
अटल अंतरभूत व्योम samsung_clk_extended_sleep_init(व्योम __iomem *reg_base,
			स्थिर अचिन्हित दीर्घ *rdump,
			अचिन्हित दीर्घ nr_rdump,
			स्थिर काष्ठा samsung_clk_reg_dump *rsuspend,
			अचिन्हित दीर्घ nr_rsuspend) अणुपूर्ण
#पूर्ण_अगर
#घोषणा samsung_clk_sleep_init(reg_base, rdump, nr_rdump) \
	samsung_clk_extended_sleep_init(reg_base, rdump, nr_rdump, शून्य, 0)

बाह्य व्योम samsung_clk_save(व्योम __iomem *base,
			काष्ठा samsung_clk_reg_dump *rd,
			अचिन्हित पूर्णांक num_regs);
बाह्य व्योम samsung_clk_restore(व्योम __iomem *base,
			स्थिर काष्ठा samsung_clk_reg_dump *rd,
			अचिन्हित पूर्णांक num_regs);
बाह्य काष्ठा samsung_clk_reg_dump *samsung_clk_alloc_reg_dump(
			स्थिर अचिन्हित दीर्घ *rdump,
			अचिन्हित दीर्घ nr_rdump);

#पूर्ण_अगर /* __SAMSUNG_CLK_H */
