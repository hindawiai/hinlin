<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#अगर_अघोषित I915_USER_EXTENSIONS_H
#घोषणा I915_USER_EXTENSIONS_H

काष्ठा i915_user_extension;

प्रकार पूर्णांक (*i915_user_extension_fn)(काष्ठा i915_user_extension __user *ext,
				      व्योम *data);

पूर्णांक i915_user_extensions(काष्ठा i915_user_extension __user *ext,
			 स्थिर i915_user_extension_fn *tbl,
			 अचिन्हित पूर्णांक count,
			 व्योम *data);

#पूर्ण_अगर /* I915_USER_EXTENSIONS_H */
