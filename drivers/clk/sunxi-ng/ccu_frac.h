<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _CCU_FRAC_H_
#घोषणा _CCU_FRAC_H_

#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"

काष्ठा ccu_frac_पूर्णांकernal अणु
	u32		enable;
	u32		select;

	अचिन्हित दीर्घ	rates[2];
पूर्ण;

#घोषणा _SUNXI_CCU_FRAC(_enable, _select, _rate1, _rate2)		\
	अणु								\
		.enable	= _enable,					\
		.select	= _select,					\
		.rates = अणु _rate1, _rate2 पूर्ण,				\
	पूर्ण

bool ccu_frac_helper_is_enabled(काष्ठा ccu_common *common,
				काष्ठा ccu_frac_पूर्णांकernal *cf);
व्योम ccu_frac_helper_enable(काष्ठा ccu_common *common,
			    काष्ठा ccu_frac_पूर्णांकernal *cf);
व्योम ccu_frac_helper_disable(काष्ठा ccu_common *common,
			     काष्ठा ccu_frac_पूर्णांकernal *cf);

bool ccu_frac_helper_has_rate(काष्ठा ccu_common *common,
			      काष्ठा ccu_frac_पूर्णांकernal *cf,
			      अचिन्हित दीर्घ rate);

अचिन्हित दीर्घ ccu_frac_helper_पढ़ो_rate(काष्ठा ccu_common *common,
					काष्ठा ccu_frac_पूर्णांकernal *cf);

पूर्णांक ccu_frac_helper_set_rate(काष्ठा ccu_common *common,
			     काष्ठा ccu_frac_पूर्णांकernal *cf,
			     अचिन्हित दीर्घ rate, u32 lock);

#पूर्ण_अगर /* _CCU_FRAC_H_ */
