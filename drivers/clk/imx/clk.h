<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_IMX_CLK_H
#घोषणा __MACH_IMX_CLK_H

#समावेश <linux/bits.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/clk-provider.h>

बाह्य spinlock_t imx_ccm_lock;

व्योम imx_check_घड़ीs(काष्ठा clk *clks[], अचिन्हित पूर्णांक count);
व्योम imx_check_clk_hws(काष्ठा clk_hw *clks[], अचिन्हित पूर्णांक count);
#अगर_अघोषित MODULE
व्योम imx_रेजिस्टर_uart_घड़ीs(अचिन्हित पूर्णांक clk_count);
#अन्यथा
अटल अंतरभूत व्योम imx_रेजिस्टर_uart_घड़ीs(अचिन्हित पूर्णांक clk_count)
अणु
पूर्ण
#पूर्ण_अगर
व्योम imx_mmdc_mask_handshake(व्योम __iomem *ccm_base, अचिन्हित पूर्णांक chn);
व्योम imx_unरेजिस्टर_घड़ीs(काष्ठा clk *clks[], अचिन्हित पूर्णांक count);
व्योम imx_unरेजिस्टर_hw_घड़ीs(काष्ठा clk_hw *hws[], अचिन्हित पूर्णांक count);

बाह्य व्योम imx_cscmr1_fixup(u32 *val);

क्रमागत imx_pllv1_type अणु
	IMX_PLLV1_IMX1,
	IMX_PLLV1_IMX21,
	IMX_PLLV1_IMX25,
	IMX_PLLV1_IMX27,
	IMX_PLLV1_IMX31,
	IMX_PLLV1_IMX35,
पूर्ण;

क्रमागत imx_sscg_pll_type अणु
	SCCG_PLL1,
	SCCG_PLL2,
पूर्ण;

क्रमागत imx_pll14xx_type अणु
	PLL_1416X,
	PLL_1443X,
पूर्ण;

/* NOTE: Rate table should be kept sorted in descending order. */
काष्ठा imx_pll14xx_rate_table अणु
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक pभाग;
	अचिन्हित पूर्णांक mभाग;
	अचिन्हित पूर्णांक sभाग;
	अचिन्हित पूर्णांक kभाग;
पूर्ण;

काष्ठा imx_pll14xx_clk अणु
	क्रमागत imx_pll14xx_type type;
	स्थिर काष्ठा imx_pll14xx_rate_table *rate_table;
	पूर्णांक rate_count;
	पूर्णांक flags;
पूर्ण;

बाह्य काष्ठा imx_pll14xx_clk imx_1416x_pll;
बाह्य काष्ठा imx_pll14xx_clk imx_1443x_pll;
बाह्य काष्ठा imx_pll14xx_clk imx_1443x_dram_pll;

#घोषणा imx_clk_cpu(name, parent_name, भाग, mux, pll, step) \
	to_clk(imx_clk_hw_cpu(name, parent_name, भाग, mux, pll, step))

#घोषणा clk_रेजिस्टर_gate2(dev, name, parent_name, flags, reg, bit_idx, \
				cgr_val, cgr_mask, clk_gate_flags, lock, share_count) \
	to_clk(clk_hw_रेजिस्टर_gate2(dev, name, parent_name, flags, reg, bit_idx, \
				cgr_val, cgr_mask, clk_gate_flags, lock, share_count))

#घोषणा imx_clk_pllv3(type, name, parent_name, base, भाग_mask) \
	to_clk(imx_clk_hw_pllv3(type, name, parent_name, base, भाग_mask))

#घोषणा imx_clk_pfd(name, parent_name, reg, idx) \
	to_clk(imx_clk_hw_pfd(name, parent_name, reg, idx))

#घोषणा imx_clk_gate_exclusive(name, parent, reg, shअगरt, exclusive_mask) \
	to_clk(imx_clk_hw_gate_exclusive(name, parent, reg, shअगरt, exclusive_mask))

#घोषणा imx_clk_fixed(name, rate) \
	to_clk(imx_clk_hw_fixed(name, rate))

#घोषणा imx_clk_fixed_factor(name, parent, mult, भाग) \
	to_clk(imx_clk_hw_fixed_factor(name, parent, mult, भाग))

#घोषणा imx_clk_भागider(name, parent, reg, shअगरt, width) \
	to_clk(imx_clk_hw_भागider(name, parent, reg, shअगरt, width))

#घोषणा imx_clk_भागider2(name, parent, reg, shअगरt, width) \
	to_clk(imx_clk_hw_भागider2(name, parent, reg, shअगरt, width))

#घोषणा imx_clk_भागider_flags(name, parent, reg, shअगरt, width, flags) \
	to_clk(imx_clk_hw_भागider_flags(name, parent, reg, shअगरt, width, flags))

#घोषणा imx_clk_gate(name, parent, reg, shअगरt) \
	to_clk(imx_clk_hw_gate(name, parent, reg, shअगरt))

#घोषणा imx_clk_gate_dis(name, parent, reg, shअगरt) \
	to_clk(imx_clk_hw_gate_dis(name, parent, reg, shअगरt))

#घोषणा imx_clk_gate2(name, parent, reg, shअगरt) \
	to_clk(imx_clk_hw_gate2(name, parent, reg, shअगरt))

#घोषणा imx_clk_gate2_flags(name, parent, reg, shअगरt, flags) \
	to_clk(imx_clk_hw_gate2_flags(name, parent, reg, shअगरt, flags))

#घोषणा imx_clk_gate2_shared2(name, parent, reg, shअगरt, share_count) \
	to_clk(imx_clk_hw_gate2_shared2(name, parent, reg, shअगरt, share_count))

#घोषणा imx_clk_gate3(name, parent, reg, shअगरt) \
	to_clk(imx_clk_hw_gate3(name, parent, reg, shअगरt))

#घोषणा imx_clk_gate4(name, parent, reg, shअगरt) \
	to_clk(imx_clk_hw_gate4(name, parent, reg, shअगरt))

#घोषणा imx_clk_mux(name, reg, shअगरt, width, parents, num_parents) \
	to_clk(imx_clk_hw_mux(name, reg, shअगरt, width, parents, num_parents))

#घोषणा imx_clk_pllv1(type, name, parent, base) \
	to_clk(imx_clk_hw_pllv1(type, name, parent, base))

#घोषणा imx_clk_pllv2(name, parent, base) \
	to_clk(imx_clk_hw_pllv2(name, parent, base))

#घोषणा imx_clk_frac_pll(name, parent_name, base) \
	to_clk(imx_clk_hw_frac_pll(name, parent_name, base))

#घोषणा imx_clk_sscg_pll(name, parent_names, num_parents, parent,\
				bypass1, bypass2, base, flags) \
	to_clk(imx_clk_hw_sscg_pll(name, parent_names, num_parents, parent,\
				bypass1, bypass2, base, flags))

काष्ठा clk *imx_clk_pll14xx(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		 व्योम __iomem *base, स्थिर काष्ठा imx_pll14xx_clk *pll_clk);

#घोषणा imx_clk_pll14xx(name, parent_name, base, pll_clk) \
	to_clk(imx_clk_hw_pll14xx(name, parent_name, base, pll_clk))

काष्ठा clk_hw *imx_dev_clk_hw_pll14xx(काष्ठा device *dev, स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name, व्योम __iomem *base,
				स्थिर काष्ठा imx_pll14xx_clk *pll_clk);

काष्ठा clk_hw *imx_clk_hw_pllv1(क्रमागत imx_pllv1_type type, स्थिर अक्षर *name,
		स्थिर अक्षर *parent, व्योम __iomem *base);

काष्ठा clk_hw *imx_clk_hw_pllv2(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *base);

काष्ठा clk_hw *imx_clk_hw_frac_pll(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			     व्योम __iomem *base);

काष्ठा clk_hw *imx_clk_hw_sscg_pll(स्थिर अक्षर *name,
				स्थिर अक्षर * स्थिर *parent_names,
				u8 num_parents,
				u8 parent, u8 bypass1, u8 bypass2,
				व्योम __iomem *base,
				अचिन्हित दीर्घ flags);

क्रमागत imx_pllv3_type अणु
	IMX_PLLV3_GENERIC,
	IMX_PLLV3_SYS,
	IMX_PLLV3_USB,
	IMX_PLLV3_USB_VF610,
	IMX_PLLV3_AV,
	IMX_PLLV3_ENET,
	IMX_PLLV3_ENET_IMX7,
	IMX_PLLV3_SYS_VF610,
	IMX_PLLV3_DDR_IMX7,
	IMX_PLLV3_AV_IMX7,
पूर्ण;

काष्ठा clk_hw *imx_clk_hw_pllv3(क्रमागत imx_pllv3_type type, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, व्योम __iomem *base, u32 भाग_mask);

#घोषणा PLL_1416X_RATE(_rate, _m, _p, _s)		\
	अणु						\
		.rate	=	(_rate),		\
		.mभाग	=	(_m),			\
		.pभाग	=	(_p),			\
		.sभाग	=	(_s),			\
	पूर्ण

#घोषणा PLL_1443X_RATE(_rate, _m, _p, _s, _k)		\
	अणु						\
		.rate	=	(_rate),		\
		.mभाग	=	(_m),			\
		.pभाग	=	(_p),			\
		.sभाग	=	(_s),			\
		.kभाग	=	(_k),			\
	पूर्ण

काष्ठा clk_hw *imx_clk_hw_pllv4(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			     व्योम __iomem *base);

काष्ठा clk_hw *clk_hw_रेजिस्टर_gate2(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 bit_idx, u8 cgr_val, u8 cgr_mask,
		u8 clk_gate_flags, spinlock_t *lock,
		अचिन्हित पूर्णांक *share_count);

काष्ठा clk * imx_obtain_fixed_घड़ी(
			स्थिर अक्षर *name, अचिन्हित दीर्घ rate);

काष्ठा clk_hw *imx_obtain_fixed_घड़ी_hw(
			स्थिर अक्षर *name, अचिन्हित दीर्घ rate);

काष्ठा clk_hw *imx_obtain_fixed_clk_hw(काष्ठा device_node *np,
				       स्थिर अक्षर *name);

काष्ठा clk_hw *imx_clk_hw_gate_exclusive(स्थिर अक्षर *name, स्थिर अक्षर *parent,
	 व्योम __iomem *reg, u8 shअगरt, u32 exclusive_mask);

काष्ठा clk_hw *imx_clk_hw_pfd(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		व्योम __iomem *reg, u8 idx);

काष्ठा clk_hw *imx_clk_hw_pfdv2(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
			     व्योम __iomem *reg, u8 idx);

काष्ठा clk_hw *imx_clk_hw_busy_भागider(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				 व्योम __iomem *reg, u8 shअगरt, u8 width,
				 व्योम __iomem *busy_reg, u8 busy_shअगरt);

काष्ठा clk_hw *imx_clk_hw_busy_mux(स्थिर अक्षर *name, व्योम __iomem *reg, u8 shअगरt,
			     u8 width, व्योम __iomem *busy_reg, u8 busy_shअगरt,
			     स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents);

काष्ठा clk_hw *imx7ulp_clk_hw_composite(स्थिर अक्षर *name,
				     स्थिर अक्षर * स्थिर *parent_names,
				     पूर्णांक num_parents, bool mux_present,
				     bool rate_present, bool gate_present,
				     व्योम __iomem *reg);

काष्ठा clk_hw *imx_clk_hw_fixup_भागider(स्थिर अक्षर *name, स्थिर अक्षर *parent,
				  व्योम __iomem *reg, u8 shअगरt, u8 width,
				  व्योम (*fixup)(u32 *val));

काष्ठा clk_hw *imx_clk_hw_fixup_mux(स्थिर अक्षर *name, व्योम __iomem *reg,
			      u8 shअगरt, u8 width, स्थिर अक्षर * स्थिर *parents,
			      पूर्णांक num_parents, व्योम (*fixup)(u32 *val));

अटल अंतरभूत काष्ठा clk *to_clk(काष्ठा clk_hw *hw)
अणु
	अगर (IS_ERR_OR_शून्य(hw))
		वापस ERR_CAST(hw);
	वापस hw->clk;
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_pll14xx(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
				  व्योम __iomem *base,
				  स्थिर काष्ठा imx_pll14xx_clk *pll_clk)
अणु
	वापस imx_dev_clk_hw_pll14xx(शून्य, name, parent_name, base, pll_clk);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_fixed(स्थिर अक्षर *name, पूर्णांक rate)
अणु
	वापस clk_hw_रेजिस्टर_fixed_rate(शून्य, name, शून्य, 0, rate);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_mux_ldb(स्थिर अक्षर *name, व्योम __iomem *reg,
			u8 shअगरt, u8 width, स्थिर अक्षर * स्थिर *parents,
			पूर्णांक num_parents)
अणु
	वापस clk_hw_रेजिस्टर_mux(शून्य, name, parents, num_parents,
			CLK_SET_RATE_NO_REPARENT | CLK_SET_RATE_PARENT, reg,
			shअगरt, width, CLK_MUX_READ_ONLY, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_fixed_factor(स्थिर अक्षर *name,
		स्थिर अक्षर *parent, अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग)
अणु
	वापस clk_hw_रेजिस्टर_fixed_factor(शून्य, name, parent,
			CLK_SET_RATE_PARENT, mult, भाग);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_भागider(स्थिर अक्षर *name,
						स्थिर अक्षर *parent,
						व्योम __iomem *reg, u8 shअगरt,
						u8 width)
अणु
	वापस clk_hw_रेजिस्टर_भागider(शून्य, name, parent, CLK_SET_RATE_PARENT,
				       reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_भागider_flags(स्थिर अक्षर *name,
						   स्थिर अक्षर *parent,
						   व्योम __iomem *reg, u8 shअगरt,
						   u8 width, अचिन्हित दीर्घ flags)
अणु
	वापस clk_hw_रेजिस्टर_भागider(शून्य, name, parent, flags,
				       reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_भागider2(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *reg, u8 shअगरt, u8 width)
अणु
	वापस clk_hw_रेजिस्टर_भागider(शून्य, name, parent,
			CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
			reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk *imx_clk_भागider2_flags(स्थिर अक्षर *name,
		स्थिर अक्षर *parent, व्योम __iomem *reg, u8 shअगरt, u8 width,
		अचिन्हित दीर्घ flags)
अणु
	वापस clk_रेजिस्टर_भागider(शून्य, name, parent,
			flags | CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
			reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate_flags(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *reg, u8 shअगरt, अचिन्हित दीर्घ flags)
अणु
	वापस clk_hw_रेजिस्टर_gate(शून्य, name, parent, flags | CLK_SET_RATE_PARENT, reg,
			shअगरt, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate(स्थिर अक्षर *name, स्थिर अक्षर *parent,
					     व्योम __iomem *reg, u8 shअगरt)
अणु
	वापस clk_hw_रेजिस्टर_gate(शून्य, name, parent, CLK_SET_RATE_PARENT, reg,
				    shअगरt, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_dev_clk_hw_gate(काष्ठा device *dev, स्थिर अक्षर *name,
						स्थिर अक्षर *parent, व्योम __iomem *reg, u8 shअगरt)
अणु
	वापस clk_hw_रेजिस्टर_gate(dev, name, parent, CLK_SET_RATE_PARENT, reg,
				    shअगरt, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate_dis(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *reg, u8 shअगरt)
अणु
	वापस clk_hw_रेजिस्टर_gate(शून्य, name, parent, CLK_SET_RATE_PARENT, reg,
			shअगरt, CLK_GATE_SET_TO_DISABLE, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate_dis_flags(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *reg, u8 shअगरt, अचिन्हित दीर्घ flags)
अणु
	वापस clk_hw_रेजिस्टर_gate(शून्य, name, parent, flags | CLK_SET_RATE_PARENT, reg,
			shअगरt, CLK_GATE_SET_TO_DISABLE, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate2(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *reg, u8 shअगरt)
अणु
	वापस clk_hw_रेजिस्टर_gate2(शून्य, name, parent, CLK_SET_RATE_PARENT, reg,
			shअगरt, 0x3, 0x3, 0, &imx_ccm_lock, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate2_flags(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *reg, u8 shअगरt, अचिन्हित दीर्घ flags)
अणु
	वापस clk_hw_रेजिस्टर_gate2(शून्य, name, parent, flags | CLK_SET_RATE_PARENT, reg,
			shअगरt, 0x3, 0x3, 0, &imx_ccm_lock, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate2_shared(स्थिर अक्षर *name,
		स्थिर अक्षर *parent, व्योम __iomem *reg, u8 shअगरt,
		अचिन्हित पूर्णांक *share_count)
अणु
	वापस clk_hw_रेजिस्टर_gate2(शून्य, name, parent, CLK_SET_RATE_PARENT, reg,
			shअगरt, 0x3, 0x3, 0, &imx_ccm_lock, share_count);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate2_shared2(स्थिर अक्षर *name,
		स्थिर अक्षर *parent, व्योम __iomem *reg, u8 shअगरt,
		अचिन्हित पूर्णांक *share_count)
अणु
	वापस clk_hw_रेजिस्टर_gate2(शून्य, name, parent, CLK_SET_RATE_PARENT |
				  CLK_OPS_PARENT_ENABLE, reg, shअगरt, 0x3, 0x3, 0,
				  &imx_ccm_lock, share_count);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_dev_clk_hw_gate_shared(काष्ठा device *dev,
				स्थिर अक्षर *name, स्थिर अक्षर *parent,
				व्योम __iomem *reg, u8 shअगरt,
				अचिन्हित पूर्णांक *share_count)
अणु
	वापस clk_hw_रेजिस्टर_gate2(शून्य, name, parent, CLK_SET_RATE_PARENT |
					CLK_OPS_PARENT_ENABLE, reg, shअगरt, 0x1,
					0x1, 0, &imx_ccm_lock, share_count);
पूर्ण

अटल अंतरभूत काष्ठा clk *imx_clk_gate2_cgr(स्थिर अक्षर *name,
		स्थिर अक्षर *parent, व्योम __iomem *reg, u8 shअगरt, u8 cgr_val)
अणु
	वापस clk_रेजिस्टर_gate2(शून्य, name, parent, CLK_SET_RATE_PARENT, reg,
			shअगरt, cgr_val, 0x3, 0, &imx_ccm_lock, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate3(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *reg, u8 shअगरt)
अणु
	वापस clk_hw_रेजिस्टर_gate(शून्य, name, parent,
			CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
			reg, shअगरt, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate3_flags(स्थिर अक्षर *name,
		स्थिर अक्षर *parent, व्योम __iomem *reg, u8 shअगरt,
		अचिन्हित दीर्घ flags)
अणु
	वापस clk_hw_रेजिस्टर_gate(शून्य, name, parent,
			flags | CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
			reg, shअगरt, 0, &imx_ccm_lock);
पूर्ण

#घोषणा imx_clk_gate3_flags(name, parent, reg, shअगरt, flags) \
	to_clk(imx_clk_hw_gate3_flags(name, parent, reg, shअगरt, flags))

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate4(स्थिर अक्षर *name, स्थिर अक्षर *parent,
		व्योम __iomem *reg, u8 shअगरt)
अणु
	वापस clk_hw_रेजिस्टर_gate2(शून्य, name, parent,
			CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
			reg, shअगरt, 0x3, 0x3, 0, &imx_ccm_lock, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_gate4_flags(स्थिर अक्षर *name,
		स्थिर अक्षर *parent, व्योम __iomem *reg, u8 shअगरt,
		अचिन्हित दीर्घ flags)
अणु
	वापस clk_hw_रेजिस्टर_gate2(शून्य, name, parent,
			flags | CLK_SET_RATE_PARENT | CLK_OPS_PARENT_ENABLE,
			reg, shअगरt, 0x3, 0x3, 0, &imx_ccm_lock, शून्य);
पूर्ण

#घोषणा imx_clk_gate4_flags(name, parent, reg, shअगरt, flags) \
	to_clk(imx_clk_hw_gate4_flags(name, parent, reg, shअगरt, flags))

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_mux(स्थिर अक्षर *name, व्योम __iomem *reg,
			u8 shअगरt, u8 width, स्थिर अक्षर * स्थिर *parents,
			पूर्णांक num_parents)
अणु
	वापस clk_hw_रेजिस्टर_mux(शून्य, name, parents, num_parents,
			CLK_SET_RATE_NO_REPARENT, reg, shअगरt,
			width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_dev_clk_hw_mux(काष्ठा device *dev,
			स्थिर अक्षर *name, व्योम __iomem *reg, u8 shअगरt,
			u8 width, स्थिर अक्षर * स्थिर *parents, पूर्णांक num_parents)
अणु
	वापस clk_hw_रेजिस्टर_mux(dev, name, parents, num_parents,
			CLK_SET_RATE_NO_REPARENT | CLK_SET_PARENT_GATE,
			reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk *imx_clk_mux2(स्थिर अक्षर *name, व्योम __iomem *reg,
			u8 shअगरt, u8 width, स्थिर अक्षर * स्थिर *parents,
			पूर्णांक num_parents)
अणु
	वापस clk_रेजिस्टर_mux(शून्य, name, parents, num_parents,
			CLK_SET_RATE_NO_REPARENT | CLK_OPS_PARENT_ENABLE,
			reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_mux2(स्थिर अक्षर *name, व्योम __iomem *reg,
					     u8 shअगरt, u8 width,
					     स्थिर अक्षर * स्थिर *parents,
					     पूर्णांक num_parents)
अणु
	वापस clk_hw_रेजिस्टर_mux(शून्य, name, parents, num_parents,
				   CLK_SET_RATE_NO_REPARENT |
				   CLK_OPS_PARENT_ENABLE,
				   reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk *imx_clk_mux_flags(स्थिर अक्षर *name,
			व्योम __iomem *reg, u8 shअगरt, u8 width,
			स्थिर अक्षर * स्थिर *parents, पूर्णांक num_parents,
			अचिन्हित दीर्घ flags)
अणु
	वापस clk_रेजिस्टर_mux(शून्य, name, parents, num_parents,
			flags | CLK_SET_RATE_NO_REPARENT, reg, shअगरt, width, 0,
			&imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_mux2_flags(स्थिर अक्षर *name,
		व्योम __iomem *reg, u8 shअगरt, u8 width,
		स्थिर अक्षर * स्थिर *parents,
		पूर्णांक num_parents, अचिन्हित दीर्घ flags)
अणु
	वापस clk_hw_रेजिस्टर_mux(शून्य, name, parents, num_parents,
			flags | CLK_SET_RATE_NO_REPARENT | CLK_OPS_PARENT_ENABLE,
			reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk *imx_clk_mux2_flags(स्थिर अक्षर *name,
		व्योम __iomem *reg, u8 shअगरt, u8 width,
		स्थिर अक्षर * स्थिर *parents,
		पूर्णांक num_parents, अचिन्हित दीर्घ flags)
अणु
	वापस clk_रेजिस्टर_mux(शून्य, name, parents, num_parents,
			flags | CLK_SET_RATE_NO_REPARENT | CLK_OPS_PARENT_ENABLE,
			reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_hw_mux_flags(स्थिर अक्षर *name,
						  व्योम __iomem *reg, u8 shअगरt,
						  u8 width,
						  स्थिर अक्षर * स्थिर *parents,
						  पूर्णांक num_parents,
						  अचिन्हित दीर्घ flags)
अणु
	वापस clk_hw_रेजिस्टर_mux(शून्य, name, parents, num_parents,
				   flags | CLK_SET_RATE_NO_REPARENT,
				   reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_dev_clk_hw_mux_flags(काष्ठा device *dev,
						  स्थिर अक्षर *name,
						  व्योम __iomem *reg, u8 shअगरt,
						  u8 width,
						  स्थिर अक्षर * स्थिर *parents,
						  पूर्णांक num_parents,
						  अचिन्हित दीर्घ flags)
अणु
	वापस clk_hw_रेजिस्टर_mux(dev, name, parents, num_parents,
				   flags | CLK_SET_RATE_NO_REPARENT,
				   reg, shअगरt, width, 0, &imx_ccm_lock);
पूर्ण

काष्ठा clk_hw *imx_clk_hw_cpu(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		काष्ठा clk *भाग, काष्ठा clk *mux, काष्ठा clk *pll,
		काष्ठा clk *step);

#घोषणा IMX_COMPOSITE_CORE	BIT(0)
#घोषणा IMX_COMPOSITE_BUS	BIT(1)

काष्ठा clk_hw *imx8m_clk_hw_composite_flags(स्थिर अक्षर *name,
					    स्थिर अक्षर * स्थिर *parent_names,
					    पूर्णांक num_parents,
					    व्योम __iomem *reg,
					    u32 composite_flags,
					    अचिन्हित दीर्घ flags);

#घोषणा imx8m_clk_hw_composite_bus(name, parent_names, reg)	\
	imx8m_clk_hw_composite_flags(name, parent_names, \
			ARRAY_SIZE(parent_names), reg, \
			IMX_COMPOSITE_BUS, \
			CLK_SET_RATE_NO_REPARENT | CLK_OPS_PARENT_ENABLE)

#घोषणा imx8m_clk_hw_composite_bus_critical(name, parent_names, reg)	\
	imx8m_clk_hw_composite_flags(name, parent_names, ARRAY_SIZE(parent_names), reg, \
			IMX_COMPOSITE_BUS, \
			CLK_SET_RATE_NO_REPARENT | CLK_OPS_PARENT_ENABLE | CLK_IS_CRITICAL)

#घोषणा imx8m_clk_hw_composite_core(name, parent_names, reg)	\
	imx8m_clk_hw_composite_flags(name, parent_names, \
			ARRAY_SIZE(parent_names), reg, \
			IMX_COMPOSITE_CORE, \
			CLK_SET_RATE_NO_REPARENT | CLK_OPS_PARENT_ENABLE)

#घोषणा imx8m_clk_composite_flags(name, parent_names, num_parents, reg, \
				  flags) \
	to_clk(imx8m_clk_hw_composite_flags(name, parent_names, \
				num_parents, reg, 0, flags))

#घोषणा __imx8m_clk_hw_composite(name, parent_names, reg, flags) \
	imx8m_clk_hw_composite_flags(name, parent_names, \
		ARRAY_SIZE(parent_names), reg, 0, \
		flags | CLK_SET_RATE_NO_REPARENT | CLK_OPS_PARENT_ENABLE)

#घोषणा __imx8m_clk_composite(name, parent_names, reg, flags) \
	to_clk(__imx8m_clk_hw_composite(name, parent_names, reg, flags))

#घोषणा imx8m_clk_hw_composite(name, parent_names, reg) \
	__imx8m_clk_hw_composite(name, parent_names, reg, 0)

#घोषणा imx8m_clk_composite(name, parent_names, reg) \
	__imx8m_clk_composite(name, parent_names, reg, 0)

#घोषणा imx8m_clk_hw_composite_critical(name, parent_names, reg) \
	__imx8m_clk_hw_composite(name, parent_names, reg, CLK_IS_CRITICAL)

#घोषणा imx8m_clk_composite_critical(name, parent_names, reg) \
	__imx8m_clk_composite(name, parent_names, reg, CLK_IS_CRITICAL)

काष्ठा clk_hw *imx_clk_hw_भागider_gate(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
		अचिन्हित दीर्घ flags, व्योम __iomem *reg, u8 shअगरt, u8 width,
		u8 clk_भागider_flags, स्थिर काष्ठा clk_भाग_प्रकारable *table,
		spinlock_t *lock);
#पूर्ण_अगर
