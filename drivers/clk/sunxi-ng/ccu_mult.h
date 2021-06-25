<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _CCU_MULT_H_
#घोषणा _CCU_MULT_H_

#समावेश "ccu_common.h"
#समावेश "ccu_frac.h"
#समावेश "ccu_mux.h"

काष्ठा ccu_mult_पूर्णांकernal अणु
	u8	offset;
	u8	shअगरt;
	u8	width;
	u8	min;
	u8	max;
पूर्ण;

#घोषणा _SUNXI_CCU_MULT_OFFSET_MIN_MAX(_shअगरt, _width, _offset, _min, _max) \
	अणु								\
		.min	= _min,						\
		.max	= _max,						\
		.offset	= _offset,					\
		.shअगरt	= _shअगरt,					\
		.width	= _width,					\
	पूर्ण

#घोषणा _SUNXI_CCU_MULT_MIN(_shअगरt, _width, _min)	\
	_SUNXI_CCU_MULT_OFFSET_MIN_MAX(_shअगरt, _width, 1, _min, 0)

#घोषणा _SUNXI_CCU_MULT_OFFSET(_shअगरt, _width, _offset)	\
	_SUNXI_CCU_MULT_OFFSET_MIN_MAX(_shअगरt, _width, _offset, 1, 0)

#घोषणा _SUNXI_CCU_MULT(_shअगरt, _width)		\
	_SUNXI_CCU_MULT_OFFSET_MIN_MAX(_shअगरt, _width, 1, 1, 0)

काष्ठा ccu_mult अणु
	u32			enable;
	u32			lock;

	काष्ठा ccu_frac_पूर्णांकernal	frac;
	काष्ठा ccu_mult_पूर्णांकernal	mult;
	काष्ठा ccu_mux_पूर्णांकernal	mux;
	काष्ठा ccu_common	common;
पूर्ण;

#घोषणा SUNXI_CCU_N_WITH_GATE_LOCK(_काष्ठा, _name, _parent, _reg,	\
				   _mshअगरt, _mwidth, _gate, _lock,	\
				   _flags)				\
	काष्ठा ccu_mult _काष्ठा = अणु					\
		.enable	= _gate,					\
		.lock	= _lock,					\
		.mult	= _SUNXI_CCU_MULT(_mshअगरt, _mwidth),		\
		.common	= अणु						\
			.reg		= _reg,				\
			.hw.init	= CLK_HW_INIT(_name,		\
						      _parent,		\
						      &ccu_mult_ops,	\
						      _flags),		\
		पूर्ण,							\
	पूर्ण

अटल अंतरभूत काष्ठा ccu_mult *hw_to_ccu_mult(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_common *common = hw_to_ccu_common(hw);

	वापस container_of(common, काष्ठा ccu_mult, common);
पूर्ण

बाह्य स्थिर काष्ठा clk_ops ccu_mult_ops;

#पूर्ण_अगर /* _CCU_MULT_H_ */
