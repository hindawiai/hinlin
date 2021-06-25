<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014-2018 Intel Corporation
 */

#अगर_अघोषित __INTEL_WORKAROUNDS_TYPES_H__
#घोषणा __INTEL_WORKAROUNDS_TYPES_H__

#समावेश <linux/types.h>

#समावेश "i915_reg.h"

काष्ठा i915_wa अणु
	i915_reg_t	reg;
	u32		clr;
	u32		set;
	u32		पढ़ो;
पूर्ण;

काष्ठा i915_wa_list अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*engine_name;
	काष्ठा i915_wa	*list;
	अचिन्हित पूर्णांक	count;
	अचिन्हित पूर्णांक	wa_count;
पूर्ण;

#पूर्ण_अगर /* __INTEL_WORKAROUNDS_TYPES_H__ */
