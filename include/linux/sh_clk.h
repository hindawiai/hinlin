<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SH_CLOCK_H
#घोषणा __SH_CLOCK_H

#समावेश <linux/list.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/types.h>
#समावेश <linux/kref.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>

काष्ठा clk;

काष्ठा clk_mapping अणु
	phys_addr_t		phys;
	व्योम __iomem		*base;
	अचिन्हित दीर्घ		len;
	काष्ठा kref		ref;
पूर्ण;

काष्ठा sh_clk_ops अणु
#अगर_घोषित CONFIG_SH_CLK_CPG_LEGACY
	व्योम (*init)(काष्ठा clk *clk);
#पूर्ण_अगर
	पूर्णांक (*enable)(काष्ठा clk *clk);
	व्योम (*disable)(काष्ठा clk *clk);
	अचिन्हित दीर्घ (*recalc)(काष्ठा clk *clk);
	पूर्णांक (*set_rate)(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
	पूर्णांक (*set_parent)(काष्ठा clk *clk, काष्ठा clk *parent);
	दीर्घ (*round_rate)(काष्ठा clk *clk, अचिन्हित दीर्घ rate);
पूर्ण;

#घोषणा SH_CLK_DIV_MSK(भाग)	((1 << (भाग)) - 1)
#घोषणा SH_CLK_DIV4_MSK		SH_CLK_DIV_MSK(4)
#घोषणा SH_CLK_DIV6_MSK		SH_CLK_DIV_MSK(6)

काष्ठा clk अणु
	काष्ठा list_head	node;
	काष्ठा clk		*parent;
	काष्ठा clk		**parent_table;	/* list of parents to */
	अचिन्हित लघु		parent_num;	/* choose between */
	अचिन्हित अक्षर		src_shअगरt;	/* source घड़ी field in the */
	अचिन्हित अक्षर		src_width;	/* configuration रेजिस्टर */
	काष्ठा sh_clk_ops	*ops;

	काष्ठा list_head	children;
	काष्ठा list_head	sibling;	/* node क्रम children */

	पूर्णांक			usecount;

	अचिन्हित दीर्घ		rate;
	अचिन्हित दीर्घ		flags;

	व्योम __iomem		*enable_reg;
	व्योम __iomem		*status_reg;
	अचिन्हित पूर्णांक		enable_bit;
	व्योम __iomem		*mapped_reg;

	अचिन्हित पूर्णांक		भाग_mask;
	अचिन्हित दीर्घ		arch_flags;
	व्योम			*priv;
	काष्ठा clk_mapping	*mapping;
	काष्ठा cpufreq_frequency_table *freq_table;
	अचिन्हित पूर्णांक		nr_freqs;
पूर्ण;

#घोषणा CLK_ENABLE_ON_INIT	BIT(0)

#घोषणा CLK_ENABLE_REG_32BIT	BIT(1)	/* शेष access size */
#घोषणा CLK_ENABLE_REG_16BIT	BIT(2)
#घोषणा CLK_ENABLE_REG_8BIT	BIT(3)

#घोषणा CLK_MASK_DIV_ON_DISABLE	BIT(4)

#घोषणा CLK_ENABLE_REG_MASK	(CLK_ENABLE_REG_32BIT | \
				 CLK_ENABLE_REG_16BIT | \
				 CLK_ENABLE_REG_8BIT)

/* drivers/sh/clk.c */
अचिन्हित दीर्घ followparent_recalc(काष्ठा clk *);
व्योम recalculate_root_घड़ीs(व्योम);
व्योम propagate_rate(काष्ठा clk *);
पूर्णांक clk_reparent(काष्ठा clk *child, काष्ठा clk *parent);
पूर्णांक clk_रेजिस्टर(काष्ठा clk *);
व्योम clk_unरेजिस्टर(काष्ठा clk *);
व्योम clk_enable_init_घड़ीs(व्योम);

काष्ठा clk_भाग_mult_table अणु
	अचिन्हित पूर्णांक *भागisors;
	अचिन्हित पूर्णांक nr_भागisors;
	अचिन्हित पूर्णांक *multipliers;
	अचिन्हित पूर्णांक nr_multipliers;
पूर्ण;

काष्ठा cpufreq_frequency_table;
व्योम clk_rate_table_build(काष्ठा clk *clk,
			  काष्ठा cpufreq_frequency_table *freq_table,
			  पूर्णांक nr_freqs,
			  काष्ठा clk_भाग_mult_table *src_table,
			  अचिन्हित दीर्घ *biपंचांगap);

दीर्घ clk_rate_table_round(काष्ठा clk *clk,
			  काष्ठा cpufreq_frequency_table *freq_table,
			  अचिन्हित दीर्घ rate);

पूर्णांक clk_rate_table_find(काष्ठा clk *clk,
			काष्ठा cpufreq_frequency_table *freq_table,
			अचिन्हित दीर्घ rate);

दीर्घ clk_rate_भाग_range_round(काष्ठा clk *clk, अचिन्हित पूर्णांक भाग_min,
			      अचिन्हित पूर्णांक भाग_max, अचिन्हित दीर्घ rate);

दीर्घ clk_rate_mult_range_round(काष्ठा clk *clk, अचिन्हित पूर्णांक mult_min,
			       अचिन्हित पूर्णांक mult_max, अचिन्हित दीर्घ rate);

#घोषणा SH_CLK_MSTP(_parent, _enable_reg, _enable_bit, _status_reg, _flags) \
अणु									\
	.parent		= _parent,					\
	.enable_reg	= (व्योम __iomem *)_enable_reg,			\
	.enable_bit	= _enable_bit,					\
	.status_reg	= _status_reg,					\
	.flags		= _flags,					\
पूर्ण

#घोषणा SH_CLK_MSTP32(_p, _r, _b, _f)				\
	SH_CLK_MSTP(_p, _r, _b, 0, _f | CLK_ENABLE_REG_32BIT)

#घोषणा SH_CLK_MSTP32_STS(_p, _r, _b, _s, _f)			\
	SH_CLK_MSTP(_p, _r, _b, _s, _f | CLK_ENABLE_REG_32BIT)

#घोषणा SH_CLK_MSTP16(_p, _r, _b, _f)				\
	SH_CLK_MSTP(_p, _r, _b, 0, _f | CLK_ENABLE_REG_16BIT)

#घोषणा SH_CLK_MSTP8(_p, _r, _b, _f)				\
	SH_CLK_MSTP(_p, _r, _b, 0, _f | CLK_ENABLE_REG_8BIT)

पूर्णांक sh_clk_mstp_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr);

/*
 * MSTP registration never really cared about access size, despite the
 * original enable/disable pairs assuming a 32-bit access. Clocks are
 * responsible क्रम defining their access sizes either directly or via the
 * घड़ी definition wrappers.
 */
अटल अंतरभूत पूर्णांक __deprecated sh_clk_mstp32_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr)
अणु
	वापस sh_clk_mstp_रेजिस्टर(clks, nr);
पूर्ण

#घोषणा SH_CLK_DIV4(_parent, _reg, _shअगरt, _भाग_biपंचांगap, _flags)	\
अणु								\
	.parent = _parent,					\
	.enable_reg = (व्योम __iomem *)_reg,			\
	.enable_bit = _shअगरt,					\
	.arch_flags = _भाग_biपंचांगap,				\
	.भाग_mask = SH_CLK_DIV4_MSK,				\
	.flags = _flags,					\
पूर्ण

काष्ठा clk_भाग_प्रकारable अणु
	काष्ठा clk_भाग_mult_table *भाग_mult_table;
	व्योम (*kick)(काष्ठा clk *clk);
पूर्ण;

#घोषणा clk_भाग4_table clk_भाग_प्रकारable

पूर्णांक sh_clk_भाग4_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr,
			 काष्ठा clk_भाग4_table *table);
पूर्णांक sh_clk_भाग4_enable_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr,
			 काष्ठा clk_भाग4_table *table);
पूर्णांक sh_clk_भाग4_reparent_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr,
			 काष्ठा clk_भाग4_table *table);

#घोषणा SH_CLK_DIV6_EXT(_reg, _flags, _parents,			\
			_num_parents, _src_shअगरt, _src_width)	\
अणु								\
	.enable_reg = (व्योम __iomem *)_reg,			\
	.enable_bit = 0, /* unused */				\
	.flags = _flags | CLK_MASK_DIV_ON_DISABLE,		\
	.भाग_mask = SH_CLK_DIV6_MSK,				\
	.parent_table = _parents,				\
	.parent_num = _num_parents,				\
	.src_shअगरt = _src_shअगरt,				\
	.src_width = _src_width,				\
पूर्ण

#घोषणा SH_CLK_DIV6(_parent, _reg, _flags)			\
अणु								\
	.parent		= _parent,				\
	.enable_reg	= (व्योम __iomem *)_reg,			\
	.enable_bit	= 0,	/* unused */			\
	.भाग_mask	= SH_CLK_DIV6_MSK,			\
	.flags		= _flags | CLK_MASK_DIV_ON_DISABLE,	\
पूर्ण

पूर्णांक sh_clk_भाग6_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr);
पूर्णांक sh_clk_भाग6_reparent_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr);

#घोषणा CLKDEV_CON_ID(_id, _clk) अणु .con_id = _id, .clk = _clk पूर्ण
#घोषणा CLKDEV_DEV_ID(_id, _clk) अणु .dev_id = _id, .clk = _clk पूर्ण
#घोषणा CLKDEV_ICK_ID(_cid, _did, _clk) अणु .con_id = _cid, .dev_id = _did, .clk = _clk पूर्ण

/* .enable_reg will be updated to .mapping on sh_clk_fsiभाग_रेजिस्टर() */
#घोषणा SH_CLK_FSIDIV(_reg, _parent)		\
अणु						\
	.enable_reg = (व्योम __iomem *)_reg,	\
	.parent		= _parent,		\
पूर्ण

पूर्णांक sh_clk_fsiभाग_रेजिस्टर(काष्ठा clk *clks, पूर्णांक nr);

#पूर्ण_अगर /* __SH_CLOCK_H */
