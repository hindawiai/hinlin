<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __I915_MEMCPY_H__
#घोषणा __I915_MEMCPY_H__

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;

व्योम i915_स_नकल_init_early(काष्ठा drm_i915_निजी *i915);

bool i915_स_नकल_from_wc(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ len);
व्योम i915_unaligned_स_नकल_from_wc(व्योम *dst, स्थिर व्योम *src, अचिन्हित दीर्घ len);

/* The movntdqa inकाष्ठाions used क्रम स_नकल-from-wc require 16-byte alignment,
 * as well as SSE4.1 support. i915_स_नकल_from_wc() will report अगर it cannot
 * perक्रमm the operation. To check beक्रमehand, pass in the parameters to
 * to i915_can_स_नकल_from_wc() - since we only care about the low 4 bits,
 * you only need to pass in the minor offsets, page-aligned poपूर्णांकers are
 * always valid.
 *
 * For just checking क्रम SSE4.1, in the क्रमeknowledge that the future use
 * will be correctly aligned, just use i915_has_स_नकल_from_wc().
 */
#घोषणा i915_can_स_नकल_from_wc(dst, src, len) \
	i915_स_नकल_from_wc((व्योम *)((अचिन्हित दीर्घ)(dst) | (अचिन्हित दीर्घ)(src) | (len)), शून्य, 0)

#घोषणा i915_has_स_नकल_from_wc() \
	i915_स_नकल_from_wc(शून्य, शून्य, 0)

#पूर्ण_अगर /* __I915_MEMCPY_H__ */
