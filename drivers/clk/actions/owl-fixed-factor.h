<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
//
// OWL fixed factor घड़ी driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#अगर_अघोषित _OWL_FIXED_FACTOR_H_
#घोषणा _OWL_FIXED_FACTOR_H_

#समावेश "owl-common.h"

#घोषणा OWL_FIX_FACT(_काष्ठा, _name, _parent, _mul, _भाग, _flags)	\
	काष्ठा clk_fixed_factor _काष्ठा = अणु				\
		.mult		= _mul,					\
		.भाग		= _भाग,					\
		.hw.init	= CLK_HW_INIT(_name,			\
					      _parent,			\
					      &clk_fixed_factor_ops,	\
					      _flags),			\
	पूर्ण

बाह्य स्थिर काष्ठा clk_ops clk_fixed_factor_ops;

#पूर्ण_अगर /* _OWL_FIXED_FACTOR_H_ */
