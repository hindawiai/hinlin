<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CCU_MUX_H_
#घोषणा _CCU_MUX_H_

#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"

काष्ठा ccu_mux_fixed_preभाग अणु
	u8	index;
	u16	भाग;
पूर्ण;

काष्ठा ccu_mux_var_preभाग अणु
	u8	index;
	u8	shअगरt;
	u8	width;
पूर्ण;

काष्ठा ccu_mux_पूर्णांकernal अणु
	u8		shअगरt;
	u8		width;
	स्थिर u8	*table;

	स्थिर काष्ठा ccu_mux_fixed_preभाग	*fixed_preभागs;
	u8		n_preभागs;

	स्थिर काष्ठा ccu_mux_var_preभाग		*var_preभागs;
	u8		n_var_preभागs;
पूर्ण;

#घोषणा _SUNXI_CCU_MUX_TABLE(_shअगरt, _width, _table)	\
	अणु						\
		.shअगरt	= _shअगरt,			\
		.width	= _width,			\
		.table	= _table,			\
	पूर्ण

#घोषणा _SUNXI_CCU_MUX(_shअगरt, _width) \
	_SUNXI_CCU_MUX_TABLE(_shअगरt, _width, शून्य)

काष्ठा ccu_mux अणु
	u16			reg;
	u32			enable;

	काष्ठा ccu_mux_पूर्णांकernal	mux;
	काष्ठा ccu_common	common;
पूर्ण;

#घोषणा SUNXI_CCU_MUX_TABLE_WITH_GATE(_काष्ठा, _name, _parents, _table,	\
				     _reg, _shअगरt, _width, _gate,	\
				     _flags)				\
	काष्ठा ccu_mux _काष्ठा = अणु					\
		.enable	= _gate,					\
		.mux	= _SUNXI_CCU_MUX_TABLE(_shअगरt, _width, _table),	\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT_PARENTS(_name,	\
							      _parents, \
							      &ccu_mux_ops, \
							      _flags),	\
		पूर्ण							\
	पूर्ण

#घोषणा SUNXI_CCU_MUX_WITH_GATE(_काष्ठा, _name, _parents, _reg,		\
				_shअगरt, _width, _gate, _flags)		\
	SUNXI_CCU_MUX_TABLE_WITH_GATE(_काष्ठा, _name, _parents, शून्य,	\
				      _reg, _shअगरt, _width, _gate,	\
				      _flags)

#घोषणा SUNXI_CCU_MUX(_काष्ठा, _name, _parents, _reg, _shअगरt, _width,	\
		      _flags)						\
	SUNXI_CCU_MUX_TABLE_WITH_GATE(_काष्ठा, _name, _parents, शून्य,	\
				      _reg, _shअगरt, _width, 0, _flags)

अटल अंतरभूत काष्ठा ccu_mux *hw_to_ccu_mux(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_common *common = hw_to_ccu_common(hw);

	वापस container_of(common, काष्ठा ccu_mux, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops ccu_mux_ops;

अचिन्हित दीर्घ ccu_mux_helper_apply_preभाग(काष्ठा ccu_common *common,
					  काष्ठा ccu_mux_पूर्णांकernal *cm,
					  पूर्णांक parent_index,
					  अचिन्हित दीर्घ parent_rate);
पूर्णांक ccu_mux_helper_determine_rate(काष्ठा ccu_common *common,
				  काष्ठा ccu_mux_पूर्णांकernal *cm,
				  काष्ठा clk_rate_request *req,
				  अचिन्हित दीर्घ (*round)(काष्ठा ccu_mux_पूर्णांकernal *,
							 काष्ठा clk_hw *,
							 अचिन्हित दीर्घ *,
							 अचिन्हित दीर्घ,
							 व्योम *),
				  व्योम *data);
u8 ccu_mux_helper_get_parent(काष्ठा ccu_common *common,
			     काष्ठा ccu_mux_पूर्णांकernal *cm);
पूर्णांक ccu_mux_helper_set_parent(काष्ठा ccu_common *common,
			      काष्ठा ccu_mux_पूर्णांकernal *cm,
			      u8 index);

काष्ठा ccu_mux_nb अणु
	काष्ठा notअगरier_block	clk_nb;
	काष्ठा ccu_common	*common;
	काष्ठा ccu_mux_पूर्णांकernal	*cm;

	u32	delay_us;	/* How many us to रुको after reparenting */
	u8	bypass_index;	/* Which parent to temporarily use */
	u8	original_index;	/* This is set by the notअगरier callback */
पूर्ण;

#घोषणा to_ccu_mux_nb(_nb) container_of(_nb, काष्ठा ccu_mux_nb, clk_nb)

पूर्णांक ccu_mux_notअगरier_रेजिस्टर(काष्ठा clk *clk, काष्ठा ccu_mux_nb *mux_nb);

#पूर्ण_अगर /* _CCU_MUX_H_ */
