<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_DE_H__
#घोषणा __INTEL_DE_H__

#समावेश "i915_drv.h"
#समावेश "i915_reg.h"
#समावेश "intel_uncore.h"

अटल अंतरभूत u32
पूर्णांकel_de_पढ़ो(काष्ठा drm_i915_निजी *i915, i915_reg_t reg)
अणु
	वापस पूर्णांकel_uncore_पढ़ो(&i915->uncore, reg);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_de_posting_पढ़ो(काष्ठा drm_i915_निजी *i915, i915_reg_t reg)
अणु
	पूर्णांकel_uncore_posting_पढ़ो(&i915->uncore, reg);
पूर्ण

/* Note: पढ़ो the warnings क्रम पूर्णांकel_uncore_*_fw() functions! */
अटल अंतरभूत u32
पूर्णांकel_de_पढ़ो_fw(काष्ठा drm_i915_निजी *i915, i915_reg_t reg)
अणु
	वापस पूर्णांकel_uncore_पढ़ो_fw(&i915->uncore, reg);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_de_ग_लिखो(काष्ठा drm_i915_निजी *i915, i915_reg_t reg, u32 val)
अणु
	पूर्णांकel_uncore_ग_लिखो(&i915->uncore, reg, val);
पूर्ण

/* Note: पढ़ो the warnings क्रम पूर्णांकel_uncore_*_fw() functions! */
अटल अंतरभूत व्योम
पूर्णांकel_de_ग_लिखो_fw(काष्ठा drm_i915_निजी *i915, i915_reg_t reg, u32 val)
अणु
	पूर्णांकel_uncore_ग_लिखो_fw(&i915->uncore, reg, val);
पूर्ण

अटल अंतरभूत व्योम
पूर्णांकel_de_rmw(काष्ठा drm_i915_निजी *i915, i915_reg_t reg, u32 clear, u32 set)
अणु
	पूर्णांकel_uncore_rmw(&i915->uncore, reg, clear, set);
पूर्ण

अटल अंतरभूत पूर्णांक
पूर्णांकel_de_रुको_क्रम_रेजिस्टर(काष्ठा drm_i915_निजी *i915, i915_reg_t reg,
			   u32 mask, u32 value, अचिन्हित पूर्णांक समयout)
अणु
	वापस पूर्णांकel_रुको_क्रम_रेजिस्टर(&i915->uncore, reg, mask, value, समयout);
पूर्ण

अटल अंतरभूत पूर्णांक
पूर्णांकel_de_रुको_क्रम_set(काष्ठा drm_i915_निजी *i915, i915_reg_t reg,
		      u32 mask, अचिन्हित पूर्णांक समयout)
अणु
	वापस पूर्णांकel_de_रुको_क्रम_रेजिस्टर(i915, reg, mask, mask, समयout);
पूर्ण

अटल अंतरभूत पूर्णांक
पूर्णांकel_de_रुको_क्रम_clear(काष्ठा drm_i915_निजी *i915, i915_reg_t reg,
			u32 mask, अचिन्हित पूर्णांक समयout)
अणु
	वापस पूर्णांकel_de_रुको_क्रम_रेजिस्टर(i915, reg, mask, 0, समयout);
पूर्ण

#पूर्ण_अगर /* __INTEL_DE_H__ */
