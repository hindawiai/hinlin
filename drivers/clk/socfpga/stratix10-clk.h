<शैली गुरु>
/* SPDX-License-Identअगरier:    GPL-2.0 */
/*
 * Copyright (C) 2017, Intel Corporation
 */

#अगर_अघोषित	__STRATIX10_CLK_H
#घोषणा	__STRATIX10_CLK_H

काष्ठा stratix10_घड़ी_data अणु
	काष्ठा clk_hw_onecell_data	clk_data;
	व्योम __iomem		*base;
पूर्ण;

काष्ठा stratix10_pll_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर काष्ठा clk_parent_data	*parent_data;
	u8			num_parents;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
पूर्ण;

काष्ठा stratix10_perip_c_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	स्थिर काष्ठा clk_parent_data	*parent_data;
	u8			num_parents;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
पूर्ण;

काष्ठा n5x_perip_c_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	स्थिर अक्षर		*स्थिर *parent_names;
	u8			num_parents;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
	अचिन्हित दीर्घ		shअगरt;
पूर्ण;

काष्ठा stratix10_perip_cnt_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	स्थिर काष्ठा clk_parent_data	*parent_data;
	u8			num_parents;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		offset;
	u8			fixed_भागider;
	अचिन्हित दीर्घ		bypass_reg;
	अचिन्हित दीर्घ		bypass_shअगरt;
पूर्ण;

काष्ठा stratix10_gate_घड़ी अणु
	अचिन्हित पूर्णांक		id;
	स्थिर अक्षर		*name;
	स्थिर अक्षर		*parent_name;
	स्थिर काष्ठा clk_parent_data	*parent_data;
	u8			num_parents;
	अचिन्हित दीर्घ		flags;
	अचिन्हित दीर्घ		gate_reg;
	u8			gate_idx;
	अचिन्हित दीर्घ		भाग_reg;
	u8			भाग_offset;
	u8			भाग_width;
	अचिन्हित दीर्घ		bypass_reg;
	u8			bypass_shअगरt;
	u8			fixed_भाग;
पूर्ण;

काष्ठा clk_hw *s10_रेजिस्टर_pll(स्थिर काष्ठा stratix10_pll_घड़ी *clks,
			     व्योम __iomem *reg);
काष्ठा clk_hw *agilex_रेजिस्टर_pll(स्थिर काष्ठा stratix10_pll_घड़ी *clks,
				व्योम __iomem *reg);
काष्ठा clk_hw *n5x_रेजिस्टर_pll(स्थिर काष्ठा stratix10_pll_घड़ी *clks,
			     व्योम __iomem *reg);
काष्ठा clk_hw *s10_रेजिस्टर_periph(स्थिर काष्ठा stratix10_perip_c_घड़ी *clks,
				व्योम __iomem *reg);
काष्ठा clk_hw *n5x_रेजिस्टर_periph(स्थिर काष्ठा n5x_perip_c_घड़ी *clks,
				व्योम __iomem *reg);
काष्ठा clk_hw *s10_रेजिस्टर_cnt_periph(स्थिर काष्ठा stratix10_perip_cnt_घड़ी *clks,
				    व्योम __iomem *reg);
काष्ठा clk_hw *s10_रेजिस्टर_gate(स्थिर काष्ठा stratix10_gate_घड़ी *clks,
			      व्योम __iomem *reg);
#पूर्ण_अगर	/* __STRATIX10_CLK_H */
