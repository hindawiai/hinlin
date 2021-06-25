<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Clocks क्रम ux500 platक्रमms
 *
 * Copyright (C) 2012 ST-Ericsson SA
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 */

#अगर_अघोषित __UX500_CLK_H
#घोषणा __UX500_CLK_H

#समावेश <linux/device.h>
#समावेश <linux/types.h>

काष्ठा clk;

काष्ठा clk *clk_reg_prcc_pclk(स्थिर अक्षर *name,
			      स्थिर अक्षर *parent_name,
			      resource_माप_प्रकार phy_base,
			      u32 cg_sel,
			      अचिन्हित दीर्घ flags);

काष्ठा clk *clk_reg_prcc_kclk(स्थिर अक्षर *name,
			      स्थिर अक्षर *parent_name,
			      resource_माप_प्रकार phy_base,
			      u32 cg_sel,
			      अचिन्हित दीर्घ flags);

काष्ठा clk *clk_reg_prcmu_scalable(स्थिर अक्षर *name,
				   स्थिर अक्षर *parent_name,
				   u8 cg_sel,
				   अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ flags);

काष्ठा clk *clk_reg_prcmu_gate(स्थिर अक्षर *name,
			       स्थिर अक्षर *parent_name,
			       u8 cg_sel,
			       अचिन्हित दीर्घ flags);

काष्ठा clk *clk_reg_prcmu_scalable_rate(स्थिर अक्षर *name,
					स्थिर अक्षर *parent_name,
					u8 cg_sel,
					अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ flags);

काष्ठा clk *clk_reg_prcmu_rate(स्थिर अक्षर *name,
			       स्थिर अक्षर *parent_name,
			       u8 cg_sel,
			       अचिन्हित दीर्घ flags);

काष्ठा clk *clk_reg_prcmu_opp_gate(स्थिर अक्षर *name,
				   स्थिर अक्षर *parent_name,
				   u8 cg_sel,
				   अचिन्हित दीर्घ flags);

काष्ठा clk *clk_reg_prcmu_opp_volt_scalable(स्थिर अक्षर *name,
					    स्थिर अक्षर *parent_name,
					    u8 cg_sel,
					    अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ flags);

काष्ठा clk *clk_reg_sysctrl_gate(काष्ठा device *dev,
				 स्थिर अक्षर *name,
				 स्थिर अक्षर *parent_name,
				 u16 reg_sel,
				 u8 reg_mask,
				 u8 reg_bits,
				 अचिन्हित दीर्घ enable_delay_us,
				 अचिन्हित दीर्घ flags);

काष्ठा clk *clk_reg_sysctrl_gate_fixed_rate(काष्ठा device *dev,
					    स्थिर अक्षर *name,
					    स्थिर अक्षर *parent_name,
					    u16 reg_sel,
					    u8 reg_mask,
					    u8 reg_bits,
					    अचिन्हित दीर्घ rate,
					    अचिन्हित दीर्घ enable_delay_us,
					    अचिन्हित दीर्घ flags);

काष्ठा clk *clk_reg_sysctrl_set_parent(काष्ठा device *dev,
				       स्थिर अक्षर *name,
				       स्थिर अक्षर **parent_names,
				       u8 num_parents,
				       u16 *reg_sel,
				       u8 *reg_mask,
				       u8 *reg_bits,
				       अचिन्हित दीर्घ flags);

#पूर्ण_अगर /* __UX500_CLK_H */
