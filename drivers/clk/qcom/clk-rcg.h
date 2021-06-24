<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2013, 2018, The Linux Foundation. All rights reserved. */

#अगर_अघोषित __QCOM_CLK_RCG_H__
#घोषणा __QCOM_CLK_RCG_H__

#समावेश <linux/clk-provider.h>
#समावेश "clk-regmap.h"

#घोषणा F(f, s, h, m, n) अणु (f), (s), (2 * (h) - 1), (m), (n) पूर्ण

काष्ठा freq_tbl अणु
	अचिन्हित दीर्घ freq;
	u8 src;
	u8 pre_भाग;
	u16 m;
	u16 n;
पूर्ण;

/**
 * काष्ठा mn - M/N:D counter
 * @mnctr_en_bit: bit to enable mn counter
 * @mnctr_reset_bit: bit to निश्चित mn counter reset
 * @mnctr_mode_shअगरt: lowest bit of mn counter mode field
 * @n_val_shअगरt: lowest bit of n value field
 * @m_val_shअगरt: lowest bit of m value field
 * @width: number of bits in m/n/d values
 * @reset_in_cc: true अगर the mnctr_reset_bit is in the CC रेजिस्टर
 */
काष्ठा mn अणु
	u8		mnctr_en_bit;
	u8		mnctr_reset_bit;
	u8		mnctr_mode_shअगरt;
#घोषणा MNCTR_MODE_DUAL 0x2
#घोषणा MNCTR_MODE_MASK 0x3
	u8		n_val_shअगरt;
	u8		m_val_shअगरt;
	u8		width;
	bool		reset_in_cc;
पूर्ण;

/**
 * काष्ठा pre_भाग - pre-भागider
 * @pre_भाग_shअगरt: lowest bit of pre भागider field
 * @pre_भाग_width: number of bits in preभागider
 */
काष्ठा pre_भाग अणु
	u8		pre_भाग_shअगरt;
	u8		pre_भाग_width;
पूर्ण;

/**
 * काष्ठा src_sel - source selector
 * @src_sel_shअगरt: lowest bit of source selection field
 * @parent_map: map from software's parent index to hardware's src_sel field
 */
काष्ठा src_sel अणु
	u8		src_sel_shअगरt;
#घोषणा SRC_SEL_MASK	0x7
	स्थिर काष्ठा parent_map	*parent_map;
पूर्ण;

/**
 * काष्ठा clk_rcg - root घड़ी generator
 *
 * @ns_reg: NS रेजिस्टर
 * @md_reg: MD रेजिस्टर
 * @mn: mn counter
 * @p: pre भागider
 * @s: source selector
 * @freq_tbl: frequency table
 * @clkr: regmap घड़ी handle
 * @lock: रेजिस्टर lock
 */
काष्ठा clk_rcg अणु
	u32		ns_reg;
	u32		md_reg;

	काष्ठा mn	mn;
	काष्ठा pre_भाग	p;
	काष्ठा src_sel	s;

	स्थिर काष्ठा freq_tbl	*freq_tbl;

	काष्ठा clk_regmap	clkr;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops clk_rcg_ops;
बाह्य स्थिर काष्ठा clk_ops clk_rcg_bypass_ops;
बाह्य स्थिर काष्ठा clk_ops clk_rcg_bypass2_ops;
बाह्य स्थिर काष्ठा clk_ops clk_rcg_pixel_ops;
बाह्य स्थिर काष्ठा clk_ops clk_rcg_esc_ops;
बाह्य स्थिर काष्ठा clk_ops clk_rcg_lcc_ops;

#घोषणा to_clk_rcg(_hw) container_of(to_clk_regmap(_hw), काष्ठा clk_rcg, clkr)

/**
 * काष्ठा clk_dyn_rcg - root घड़ी generator with glitch मुक्त mux
 *
 * @mux_sel_bit: bit to चयन glitch मुक्त mux
 * @ns_reg: NS0 and NS1 रेजिस्टर
 * @md_reg: MD0 and MD1 रेजिस्टर
 * @bank_reg: रेजिस्टर to XOR @mux_sel_bit पूर्णांकo to चयन glitch मुक्त mux
 * @mn: mn counter (banked)
 * @s: source selector (banked)
 * @freq_tbl: frequency table
 * @clkr: regmap घड़ी handle
 * @lock: रेजिस्टर lock
 */
काष्ठा clk_dyn_rcg अणु
	u32	ns_reg[2];
	u32	md_reg[2];
	u32	bank_reg;

	u8	mux_sel_bit;

	काष्ठा mn	mn[2];
	काष्ठा pre_भाग	p[2];
	काष्ठा src_sel	s[2];

	स्थिर काष्ठा freq_tbl *freq_tbl;

	काष्ठा clk_regmap clkr;
पूर्ण;

बाह्य स्थिर काष्ठा clk_ops clk_dyn_rcg_ops;

#घोषणा to_clk_dyn_rcg(_hw) \
	container_of(to_clk_regmap(_hw), काष्ठा clk_dyn_rcg, clkr)

/**
 * काष्ठा clk_rcg2 - root घड़ी generator
 *
 * @cmd_rcgr: corresponds to *_CMD_RCGR
 * @mnd_width: number of bits in m/n/d values
 * @hid_width: number of bits in half पूर्णांकeger भागider
 * @safe_src_index: safe src index value
 * @parent_map: map from software's parent index to hardware's src_sel field
 * @freq_tbl: frequency table
 * @clkr: regmap घड़ी handle
 * @cfg_off: defines the cfg रेजिस्टर offset from the CMD_RCGR + CFG_REG
 */
काष्ठा clk_rcg2 अणु
	u32			cmd_rcgr;
	u8			mnd_width;
	u8			hid_width;
	u8			safe_src_index;
	स्थिर काष्ठा parent_map	*parent_map;
	स्थिर काष्ठा freq_tbl	*freq_tbl;
	काष्ठा clk_regmap	clkr;
	u8			cfg_off;
पूर्ण;

#घोषणा to_clk_rcg2(_hw) container_of(to_clk_regmap(_hw), काष्ठा clk_rcg2, clkr)

काष्ठा clk_rcg2_gfx3d अणु
	u8 भाग;
	काष्ठा clk_rcg2 rcg;
	काष्ठा clk_hw **hws;
पूर्ण;

#घोषणा to_clk_rcg2_gfx3d(_hw) \
	container_of(to_clk_rcg2(_hw), काष्ठा clk_rcg2_gfx3d, rcg)

बाह्य स्थिर काष्ठा clk_ops clk_rcg2_ops;
बाह्य स्थिर काष्ठा clk_ops clk_rcg2_न्यूनमान_ops;
बाह्य स्थिर काष्ठा clk_ops clk_edp_pixel_ops;
बाह्य स्थिर काष्ठा clk_ops clk_byte_ops;
बाह्य स्थिर काष्ठा clk_ops clk_byte2_ops;
बाह्य स्थिर काष्ठा clk_ops clk_pixel_ops;
बाह्य स्थिर काष्ठा clk_ops clk_gfx3d_ops;
बाह्य स्थिर काष्ठा clk_ops clk_rcg2_shared_ops;
बाह्य स्थिर काष्ठा clk_ops clk_dp_ops;

काष्ठा clk_rcg_dfs_data अणु
	काष्ठा clk_rcg2 *rcg;
	काष्ठा clk_init_data *init;
पूर्ण;

#घोषणा DEFINE_RCG_DFS(r) \
	अणु .rcg = &r, .init = &r##_init पूर्ण

बाह्य पूर्णांक qcom_cc_रेजिस्टर_rcg_dfs(काष्ठा regmap *regmap,
				    स्थिर काष्ठा clk_rcg_dfs_data *rcgs,
				    माप_प्रकार len);
#पूर्ण_अगर
