<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __QCOM_CLK_KRAIT_H
#घोषणा __QCOM_CLK_KRAIT_H

#समावेश <linux/clk-provider.h>

काष्ठा krait_mux_clk अणु
	अचिन्हित पूर्णांक	*parent_map;
	u32		offset;
	u32		mask;
	u32		shअगरt;
	u32		en_mask;
	bool		lpl;
	u8		safe_sel;
	u8		old_index;
	bool		reparent;

	काष्ठा clk_hw	hw;
	काष्ठा notअगरier_block   clk_nb;
पूर्ण;

#घोषणा to_krait_mux_clk(_hw) container_of(_hw, काष्ठा krait_mux_clk, hw)

बाह्य स्थिर काष्ठा clk_ops krait_mux_clk_ops;

काष्ठा krait_भाग2_clk अणु
	u32		offset;
	u8		width;
	u32		shअगरt;
	bool		lpl;

	काष्ठा clk_hw	hw;
पूर्ण;

#घोषणा to_krait_भाग2_clk(_hw) container_of(_hw, काष्ठा krait_भाग2_clk, hw)

बाह्य स्थिर काष्ठा clk_ops krait_भाग2_clk_ops;

#पूर्ण_अगर
