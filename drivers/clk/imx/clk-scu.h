<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2018 NXP
 *   Dong Aisheng <aisheng.करोng@nxp.com>
 */

#अगर_अघोषित __IMX_CLK_SCU_H
#घोषणा __IMX_CLK_SCU_H

#समावेश <linux/firmware/imx/sci.h>
#समावेश <linux/of.h>

बाह्य काष्ठा list_head imx_scu_clks[];
बाह्य स्थिर काष्ठा dev_pm_ops imx_clk_lpcg_scu_pm_ops;

पूर्णांक imx_clk_scu_init(काष्ठा device_node *np);
काष्ठा clk_hw *imx_scu_of_clk_src_get(काष्ठा of_phandle_args *clkspec,
				      व्योम *data);
काष्ठा clk_hw *imx_clk_scu_alloc_dev(स्थिर अक्षर *name,
				     स्थिर अक्षर * स्थिर *parents,
				     पूर्णांक num_parents, u32 rsrc_id, u8 clk_type);

काष्ठा clk_hw *__imx_clk_scu(काष्ठा device *dev, स्थिर अक्षर *name,
			     स्थिर अक्षर * स्थिर *parents, पूर्णांक num_parents,
			     u32 rsrc_id, u8 clk_type);

व्योम imx_clk_scu_unरेजिस्टर(व्योम);

काष्ठा clk_hw *__imx_clk_lpcg_scu(काष्ठा device *dev, स्थिर अक्षर *name,
				  स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
				  व्योम __iomem *reg, u8 bit_idx, bool hw_gate);
व्योम imx_clk_lpcg_scu_unरेजिस्टर(काष्ठा clk_hw *hw);

अटल अंतरभूत काष्ठा clk_hw *imx_clk_scu(स्थिर अक्षर *name, u32 rsrc_id,
					 u8 clk_type, u8 clk_cells)
अणु
	अगर (clk_cells == 2)
		वापस imx_clk_scu_alloc_dev(name, शून्य, 0, rsrc_id, clk_type);
	अन्यथा
		वापस __imx_clk_scu(शून्य, name, शून्य, 0, rsrc_id, clk_type);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_scu2(स्थिर अक्षर *name, स्थिर अक्षर * स्थिर *parents,
					  पूर्णांक num_parents, u32 rsrc_id, u8 clk_type,
					  u8 clk_cells)
अणु
	अगर (clk_cells == 2)
		वापस imx_clk_scu_alloc_dev(name, parents, num_parents, rsrc_id, clk_type);
	अन्यथा
		वापस __imx_clk_scu(शून्य, name, parents, num_parents, rsrc_id, clk_type);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_lpcg_scu_dev(काष्ठा device *dev, स्थिर अक्षर *name,
						  स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
						  व्योम __iomem *reg, u8 bit_idx, bool hw_gate)
अणु
	वापस __imx_clk_lpcg_scu(dev, name, parent_name, flags, reg,
				  bit_idx, hw_gate);
पूर्ण

अटल अंतरभूत काष्ठा clk_hw *imx_clk_lpcg_scu(स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
					      अचिन्हित दीर्घ flags, व्योम __iomem *reg,
					      u8 bit_idx, bool hw_gate)
अणु
	वापस __imx_clk_lpcg_scu(शून्य, name, parent_name, flags, reg,
				  bit_idx, hw_gate);
पूर्ण
#पूर्ण_अगर
