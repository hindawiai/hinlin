<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017~2018 NXP
 *
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

#समावेश "clk.h"

#घोषणा PCG_PCS_SHIFT	24
#घोषणा PCG_PCS_MASK	0x7
#घोषणा PCG_CGC_SHIFT	30
#घोषणा PCG_FRAC_SHIFT	3
#घोषणा PCG_FRAC_WIDTH	1
#घोषणा PCG_FRAC_MASK	BIT(3)
#घोषणा PCG_PCD_SHIFT	0
#घोषणा PCG_PCD_WIDTH	3
#घोषणा PCG_PCD_MASK	0x7

काष्ठा clk_hw *imx7ulp_clk_hw_composite(स्थिर अक्षर *name,
				     स्थिर अक्षर * स्थिर *parent_names,
				     पूर्णांक num_parents, bool mux_present,
				     bool rate_present, bool gate_present,
				     व्योम __iomem *reg)
अणु
	काष्ठा clk_hw *mux_hw = शून्य, *fd_hw = शून्य, *gate_hw = शून्य;
	काष्ठा clk_fractional_भागider *fd = शून्य;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा clk_mux *mux = शून्य;
	काष्ठा clk_hw *hw;

	अगर (mux_present) अणु
		mux = kzalloc(माप(*mux), GFP_KERNEL);
		अगर (!mux)
			वापस ERR_PTR(-ENOMEM);
		mux_hw = &mux->hw;
		mux->reg = reg;
		mux->shअगरt = PCG_PCS_SHIFT;
		mux->mask = PCG_PCS_MASK;
	पूर्ण

	अगर (rate_present) अणु
		fd = kzalloc(माप(*fd), GFP_KERNEL);
		अगर (!fd) अणु
			kमुक्त(mux);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		fd_hw = &fd->hw;
		fd->reg = reg;
		fd->mshअगरt = PCG_FRAC_SHIFT;
		fd->mwidth = PCG_FRAC_WIDTH;
		fd->mmask  = PCG_FRAC_MASK;
		fd->nshअगरt = PCG_PCD_SHIFT;
		fd->nwidth = PCG_PCD_WIDTH;
		fd->nmask = PCG_PCD_MASK;
		fd->flags = CLK_FRAC_DIVIDER_ZERO_BASED;
	पूर्ण

	अगर (gate_present) अणु
		gate = kzalloc(माप(*gate), GFP_KERNEL);
		अगर (!gate) अणु
			kमुक्त(mux);
			kमुक्त(fd);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		gate_hw = &gate->hw;
		gate->reg = reg;
		gate->bit_idx = PCG_CGC_SHIFT;
	पूर्ण

	hw = clk_hw_रेजिस्टर_composite(शून्य, name, parent_names, num_parents,
				       mux_hw, &clk_mux_ops, fd_hw,
				       &clk_fractional_भागider_ops, gate_hw,
				       &clk_gate_ops, CLK_SET_RATE_GATE |
				       CLK_SET_PARENT_GATE);
	अगर (IS_ERR(hw)) अणु
		kमुक्त(mux);
		kमुक्त(fd);
		kमुक्त(gate);
	पूर्ण

	वापस hw;
पूर्ण
