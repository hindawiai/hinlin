<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_MMP_CLK_H
#घोषणा __MACH_MMP_CLK_H

#समावेश <linux/clk-provider.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/clkdev.h>

#घोषणा APBC_NO_BUS_CTRL	BIT(0)
#घोषणा APBC_POWER_CTRL		BIT(1)


/* Clock type "factor" */
काष्ठा mmp_clk_factor_masks अणु
	अचिन्हित पूर्णांक factor;
	अचिन्हित पूर्णांक num_mask;
	अचिन्हित पूर्णांक den_mask;
	अचिन्हित पूर्णांक num_shअगरt;
	अचिन्हित पूर्णांक den_shअगरt;
	अचिन्हित पूर्णांक enable_mask;
पूर्ण;

काष्ठा mmp_clk_factor_tbl अणु
	अचिन्हित पूर्णांक num;
	अचिन्हित पूर्णांक den;
पूर्ण;

काष्ठा mmp_clk_factor अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	काष्ठा mmp_clk_factor_masks *masks;
	काष्ठा mmp_clk_factor_tbl *ftbl;
	अचिन्हित पूर्णांक ftbl_cnt;
	spinlock_t *lock;
पूर्ण;

बाह्य काष्ठा clk *mmp_clk_रेजिस्टर_factor(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *base, काष्ठा mmp_clk_factor_masks *masks,
		काष्ठा mmp_clk_factor_tbl *ftbl, अचिन्हित पूर्णांक ftbl_cnt,
		spinlock_t *lock);

/* Clock type "mix" */
#घोषणा MMP_CLK_BITS_MASK(width, shअगरt)			\
		(((1 << (width)) - 1) << (shअगरt))
#घोषणा MMP_CLK_BITS_GET_VAL(data, width, shअगरt)	\
		((data & MMP_CLK_BITS_MASK(width, shअगरt)) >> (shअगरt))
#घोषणा MMP_CLK_BITS_SET_VAL(val, width, shअगरt)		\
		(((val) << (shअगरt)) & MMP_CLK_BITS_MASK(width, shअगरt))

क्रमागत अणु
	MMP_CLK_MIX_TYPE_V1,
	MMP_CLK_MIX_TYPE_V2,
	MMP_CLK_MIX_TYPE_V3,
पूर्ण;

/* The रेजिस्टर layout */
काष्ठा mmp_clk_mix_reg_info अणु
	व्योम __iomem *reg_clk_ctrl;
	व्योम __iomem *reg_clk_sel;
	u8 width_भाग;
	u8 shअगरt_भाग;
	u8 width_mux;
	u8 shअगरt_mux;
	u8 bit_fc;
पूर्ण;

/* The suggested घड़ी table from user. */
काष्ठा mmp_clk_mix_clk_table अणु
	अचिन्हित दीर्घ rate;
	u8 parent_index;
	अचिन्हित पूर्णांक भागisor;
	अचिन्हित पूर्णांक valid;
पूर्ण;

काष्ठा mmp_clk_mix_config अणु
	काष्ठा mmp_clk_mix_reg_info reg_info;
	काष्ठा mmp_clk_mix_clk_table *table;
	अचिन्हित पूर्णांक table_size;
	u32 *mux_table;
	काष्ठा clk_भाग_प्रकारable *भाग_प्रकारable;
	u8 भाग_flags;
	u8 mux_flags;
पूर्ण;

काष्ठा mmp_clk_mix अणु
	काष्ठा clk_hw hw;
	काष्ठा mmp_clk_mix_reg_info reg_info;
	काष्ठा mmp_clk_mix_clk_table *table;
	u32 *mux_table;
	काष्ठा clk_भाग_प्रकारable *भाग_प्रकारable;
	अचिन्हित पूर्णांक table_size;
	u8 भाग_flags;
	u8 mux_flags;
	अचिन्हित पूर्णांक type;
	spinlock_t *lock;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops mmp_clk_mix_ops;
बाह्य काष्ठा clk *mmp_clk_रेजिस्टर_mix(काष्ठा device *dev,
					स्थिर अक्षर *name,
					स्थिर अक्षर * स्थिर *parent_names,
					u8 num_parents,
					अचिन्हित दीर्घ flags,
					काष्ठा mmp_clk_mix_config *config,
					spinlock_t *lock);


/* Clock type "gate". MMP निजी gate */
#घोषणा MMP_CLK_GATE_NEED_DELAY		BIT(0)

काष्ठा mmp_clk_gate अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *reg;
	u32 mask;
	u32 val_enable;
	u32 val_disable;
	अचिन्हित पूर्णांक flags;
	spinlock_t *lock;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops mmp_clk_gate_ops;
बाह्य काष्ठा clk *mmp_clk_रेजिस्टर_gate(काष्ठा device *dev, स्थिर अक्षर *name,
			स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
			व्योम __iomem *reg, u32 mask, u32 val_enable,
			u32 val_disable, अचिन्हित पूर्णांक gate_flags,
			spinlock_t *lock);

बाह्य काष्ठा clk *mmp_clk_रेजिस्टर_apbc(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, व्योम __iomem *base,
		अचिन्हित पूर्णांक delay, अचिन्हित पूर्णांक apbc_flags, spinlock_t *lock);
बाह्य काष्ठा clk *mmp_clk_रेजिस्टर_apmu(स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, व्योम __iomem *base, u32 enable_mask,
		spinlock_t *lock);

काष्ठा mmp_clk_unit अणु
	अचिन्हित पूर्णांक nr_clks;
	काष्ठा clk **clk_table;
	काष्ठा clk_onecell_data clk_data;
पूर्ण;

काष्ठा mmp_param_fixed_rate_clk अणु
	अचिन्हित पूर्णांक id;
	अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ fixed_rate;
पूर्ण;
व्योम mmp_रेजिस्टर_fixed_rate_clks(काष्ठा mmp_clk_unit *unit,
				काष्ठा mmp_param_fixed_rate_clk *clks,
				पूर्णांक size);

काष्ठा mmp_param_fixed_factor_clk अणु
	अचिन्हित पूर्णांक id;
	अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ mult;
	अचिन्हित दीर्घ भाग;
	अचिन्हित दीर्घ flags;
पूर्ण;
व्योम mmp_रेजिस्टर_fixed_factor_clks(काष्ठा mmp_clk_unit *unit,
				काष्ठा mmp_param_fixed_factor_clk *clks,
				पूर्णांक size);

काष्ठा mmp_param_general_gate_clk अणु
	अचिन्हित पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ offset;
	u8 bit_idx;
	u8 gate_flags;
	spinlock_t *lock;
पूर्ण;
व्योम mmp_रेजिस्टर_general_gate_clks(काष्ठा mmp_clk_unit *unit,
				काष्ठा mmp_param_general_gate_clk *clks,
				व्योम __iomem *base, पूर्णांक size);

काष्ठा mmp_param_gate_clk अणु
	अचिन्हित पूर्णांक id;
	अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ offset;
	u32 mask;
	u32 val_enable;
	u32 val_disable;
	अचिन्हित पूर्णांक gate_flags;
	spinlock_t *lock;
पूर्ण;
व्योम mmp_रेजिस्टर_gate_clks(काष्ठा mmp_clk_unit *unit,
			काष्ठा mmp_param_gate_clk *clks,
			व्योम __iomem *base, पूर्णांक size);

काष्ठा mmp_param_mux_clk अणु
	अचिन्हित पूर्णांक id;
	अक्षर *name;
	स्थिर अक्षर * स्थिर *parent_name;
	u8 num_parents;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ offset;
	u8 shअगरt;
	u8 width;
	u8 mux_flags;
	spinlock_t *lock;
पूर्ण;
व्योम mmp_रेजिस्टर_mux_clks(काष्ठा mmp_clk_unit *unit,
			काष्ठा mmp_param_mux_clk *clks,
			व्योम __iomem *base, पूर्णांक size);

काष्ठा mmp_param_भाग_clk अणु
	अचिन्हित पूर्णांक id;
	अक्षर *name;
	स्थिर अक्षर *parent_name;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ offset;
	u8 shअगरt;
	u8 width;
	u8 भाग_flags;
	spinlock_t *lock;
पूर्ण;
व्योम mmp_रेजिस्टर_भाग_clks(काष्ठा mmp_clk_unit *unit,
			काष्ठा mmp_param_भाग_clk *clks,
			व्योम __iomem *base, पूर्णांक size);

काष्ठा mmp_param_pll_clk अणु
	अचिन्हित पूर्णांक id;
	अक्षर *name;
	अचिन्हित दीर्घ शेष_rate;
	अचिन्हित दीर्घ enable_offset;
	u32 enable;
	अचिन्हित दीर्घ offset;
	u8 shअगरt;
	/* MMP3 specअगरic: */
	अचिन्हित दीर्घ input_rate;
	अचिन्हित दीर्घ postभाग_offset;
	अचिन्हित दीर्घ postभाग_shअगरt;
पूर्ण;
व्योम mmp_रेजिस्टर_pll_clks(काष्ठा mmp_clk_unit *unit,
			काष्ठा mmp_param_pll_clk *clks,
			व्योम __iomem *base, पूर्णांक size);

#घोषणा DEFINE_MIX_REG_INFO(w_d, s_d, w_m, s_m, fc)	\
अणु							\
	.width_भाग = (w_d),				\
	.shअगरt_भाग = (s_d),				\
	.width_mux = (w_m),				\
	.shअगरt_mux = (s_m),				\
	.bit_fc = (fc),					\
पूर्ण

व्योम mmp_clk_init(काष्ठा device_node *np, काष्ठा mmp_clk_unit *unit,
		पूर्णांक nr_clks);
व्योम mmp_clk_add(काष्ठा mmp_clk_unit *unit, अचिन्हित पूर्णांक id,
		काष्ठा clk *clk);

/* Power islands */
#घोषणा MMP_PM_DOMAIN_NO_DISABLE		BIT(0)

काष्ठा generic_pm_करोमुख्य *mmp_pm_करोमुख्य_रेजिस्टर(स्थिर अक्षर *name,
		व्योम __iomem *reg,
		u32 घातer_on, u32 reset, u32 घड़ी_enable,
		अचिन्हित पूर्णांक flags, spinlock_t *lock);

#पूर्ण_अगर
