<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Owen Chen <owen.chen@mediatek.com>
 */

#अगर_अघोषित __DRV_CLK_MTK_MUX_H
#घोषणा __DRV_CLK_MTK_MUX_H

#समावेश <linux/clk-provider.h>

काष्ठा mtk_clk_mux अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा mtk_mux *data;
	spinlock_t *lock;
	bool reparent;
पूर्ण;

काष्ठा mtk_mux अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *parent_names;
	अचिन्हित पूर्णांक flags;

	u32 mux_ofs;
	u32 set_ofs;
	u32 clr_ofs;
	u32 upd_ofs;

	u8 mux_shअगरt;
	u8 mux_width;
	u8 gate_shअगरt;
	s8 upd_shअगरt;

	चिन्हित अक्षर num_parents;
पूर्ण;

#घोषणा GATE_CLR_SET_UPD_FLAGS(_id, _name, _parents, _mux_ofs,		\
			_mux_set_ofs, _mux_clr_ofs, _shअगरt, _width,	\
			_gate, _upd_ofs, _upd, _flags) अणु		\
		.id = _id,						\
		.name = _name,						\
		.mux_ofs = _mux_ofs,					\
		.set_ofs = _mux_set_ofs,				\
		.clr_ofs = _mux_clr_ofs,				\
		.upd_ofs = _upd_ofs,					\
		.mux_shअगरt = _shअगरt,					\
		.mux_width = _width,					\
		.gate_shअगरt = _gate,					\
		.upd_shअगरt = _upd,					\
		.parent_names = _parents,				\
		.num_parents = ARRAY_SIZE(_parents),			\
		.flags = _flags,					\
	पूर्ण

#घोषणा MUX_GATE_CLR_SET_UPD_FLAGS(_id, _name, _parents, _mux_ofs,	\
			_mux_set_ofs, _mux_clr_ofs, _shअगरt, _width,	\
			_gate, _upd_ofs, _upd, _flags)			\
		GATE_CLR_SET_UPD_FLAGS(_id, _name, _parents, _mux_ofs,	\
			_mux_set_ofs, _mux_clr_ofs, _shअगरt, _width,	\
			_gate, _upd_ofs, _upd, _flags)			\

#घोषणा MUX_GATE_CLR_SET_UPD(_id, _name, _parents, _mux_ofs,		\
			_mux_set_ofs, _mux_clr_ofs, _shअगरt, _width,	\
			_gate, _upd_ofs, _upd)				\
		MUX_GATE_CLR_SET_UPD_FLAGS(_id, _name, _parents,	\
			_mux_ofs, _mux_set_ofs, _mux_clr_ofs, _shअगरt,	\
			_width, _gate, _upd_ofs, _upd,			\
			CLK_SET_RATE_PARENT)

पूर्णांक mtk_clk_रेजिस्टर_muxes(स्थिर काष्ठा mtk_mux *muxes,
			   पूर्णांक num, काष्ठा device_node *node,
			   spinlock_t *lock,
			   काष्ठा clk_onecell_data *clk_data);

#पूर्ण_अगर /* __DRV_CLK_MTK_MUX_H */
