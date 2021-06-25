<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2017 Chen-Yu Tsai. All rights reserved.
 */

#अगर_अघोषित _CCU_SDM_H
#घोषणा _CCU_SDM_H

#समावेश <linux/clk-provider.h>

#समावेश "ccu_common.h"

काष्ठा ccu_sdm_setting अणु
	अचिन्हित दीर्घ	rate;

	/*
	 * XXX We करोn't know what the step and bottom रेजिस्टर fields
	 * mean. Just copy the whole रेजिस्टर value from the venकरोr
	 * kernel क्रम now.
	 */
	u32		pattern;

	/*
	 * M and N factors here should be the values used in
	 * calculation, not the raw values written to रेजिस्टरs
	 */
	u32		m;
	u32		n;
पूर्ण;

काष्ठा ccu_sdm_पूर्णांकernal अणु
	काष्ठा ccu_sdm_setting	*table;
	u32		table_size;
	/* early SoCs करोn't have the SDM enable bit in the PLL रेजिस्टर */
	u32		enable;
	/* second enable bit in tuning रेजिस्टर */
	u32		tuning_enable;
	u16		tuning_reg;
पूर्ण;

#घोषणा _SUNXI_CCU_SDM(_table, _enable,			\
		       _reg, _reg_enable)		\
	अणु						\
		.table		= _table,		\
		.table_size	= ARRAY_SIZE(_table),	\
		.enable		= _enable,		\
		.tuning_enable	= _reg_enable,		\
		.tuning_reg	= _reg,			\
	पूर्ण

bool ccu_sdm_helper_is_enabled(काष्ठा ccu_common *common,
			       काष्ठा ccu_sdm_पूर्णांकernal *sdm);
व्योम ccu_sdm_helper_enable(काष्ठा ccu_common *common,
			   काष्ठा ccu_sdm_पूर्णांकernal *sdm,
			   अचिन्हित दीर्घ rate);
व्योम ccu_sdm_helper_disable(काष्ठा ccu_common *common,
			    काष्ठा ccu_sdm_पूर्णांकernal *sdm);

bool ccu_sdm_helper_has_rate(काष्ठा ccu_common *common,
			     काष्ठा ccu_sdm_पूर्णांकernal *sdm,
			     अचिन्हित दीर्घ rate);

अचिन्हित दीर्घ ccu_sdm_helper_पढ़ो_rate(काष्ठा ccu_common *common,
				       काष्ठा ccu_sdm_पूर्णांकernal *sdm,
				       u32 m, u32 n);

पूर्णांक ccu_sdm_helper_get_factors(काष्ठा ccu_common *common,
			       काष्ठा ccu_sdm_पूर्णांकernal *sdm,
			       अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ *m, अचिन्हित दीर्घ *n);

#पूर्ण_अगर
