<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: James Liao <jamesjj.liao@mediatek.com>
 */

#अगर_अघोषित __DRV_CLK_GATE_H
#घोषणा __DRV_CLK_GATE_H

#समावेश <linux/regmap.h>
#समावेश <linux/clk-provider.h>

काष्ठा clk;

काष्ठा mtk_clk_gate अणु
	काष्ठा clk_hw	hw;
	काष्ठा regmap	*regmap;
	पूर्णांक		set_ofs;
	पूर्णांक		clr_ofs;
	पूर्णांक		sta_ofs;
	u8		bit;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_clk_gate *to_mtk_clk_gate(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा mtk_clk_gate, hw);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops mtk_clk_gate_ops_setclr;
बाह्य स्थिर काष्ठा clk_ops mtk_clk_gate_ops_setclr_inv;
बाह्य स्थिर काष्ठा clk_ops mtk_clk_gate_ops_no_setclr;
बाह्य स्थिर काष्ठा clk_ops mtk_clk_gate_ops_no_setclr_inv;

काष्ठा clk *mtk_clk_रेजिस्टर_gate(
		स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name,
		काष्ठा regmap *regmap,
		पूर्णांक set_ofs,
		पूर्णांक clr_ofs,
		पूर्णांक sta_ofs,
		u8 bit,
		स्थिर काष्ठा clk_ops *ops,
		अचिन्हित दीर्घ flags,
		काष्ठा device *dev);

#घोषणा GATE_MTK_FLAGS(_id, _name, _parent, _regs, _shअगरt,	\
			_ops, _flags) अणु				\
		.id = _id,					\
		.name = _name,					\
		.parent_name = _parent,				\
		.regs = _regs,					\
		.shअगरt = _shअगरt,				\
		.ops = _ops,					\
		.flags = _flags,				\
	पूर्ण

#घोषणा GATE_MTK(_id, _name, _parent, _regs, _shअगरt, _ops)		\
	GATE_MTK_FLAGS(_id, _name, _parent, _regs, _shअगरt, _ops, 0)

#पूर्ण_अगर /* __DRV_CLK_GATE_H */
