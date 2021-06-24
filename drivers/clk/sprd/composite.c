<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Spपढ़ोtrum composite घड़ी driver
//
// Copyright (C) 2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#समावेश <linux/clk-provider.h>

#समावेश "composite.h"

अटल दीर्घ sprd_comp_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा sprd_comp *cc = hw_to_sprd_comp(hw);

	वापस sprd_भाग_helper_round_rate(&cc->common, &cc->भाग,
					 rate, parent_rate);
पूर्ण

अटल अचिन्हित दीर्घ sprd_comp_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sprd_comp *cc = hw_to_sprd_comp(hw);

	वापस sprd_भाग_helper_recalc_rate(&cc->common, &cc->भाग, parent_rate);
पूर्ण

अटल पूर्णांक sprd_comp_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sprd_comp *cc = hw_to_sprd_comp(hw);

	वापस sprd_भाग_helper_set_rate(&cc->common, &cc->भाग,
				       rate, parent_rate);
पूर्ण

अटल u8 sprd_comp_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा sprd_comp *cc = hw_to_sprd_comp(hw);

	वापस sprd_mux_helper_get_parent(&cc->common, &cc->mux);
पूर्ण

अटल पूर्णांक sprd_comp_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा sprd_comp *cc = hw_to_sprd_comp(hw);

	वापस sprd_mux_helper_set_parent(&cc->common, &cc->mux, index);
पूर्ण

स्थिर काष्ठा clk_ops sprd_comp_ops = अणु
	.get_parent	= sprd_comp_get_parent,
	.set_parent	= sprd_comp_set_parent,

	.round_rate	= sprd_comp_round_rate,
	.recalc_rate	= sprd_comp_recalc_rate,
	.set_rate	= sprd_comp_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(sprd_comp_ops);
