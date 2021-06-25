<शैली गुरु>
/*
 * Copyright(c) 2011-2015 Intel Corporation. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित _I915_VGPU_H_
#घोषणा _I915_VGPU_H_

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा i915_ggtt;

व्योम पूर्णांकel_vgpu_detect(काष्ठा drm_i915_निजी *i915);
bool पूर्णांकel_vgpu_active(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_vgpu_रेजिस्टर(काष्ठा drm_i915_निजी *i915);
bool पूर्णांकel_vgpu_has_full_ppgtt(काष्ठा drm_i915_निजी *i915);
bool पूर्णांकel_vgpu_has_hwsp_emulation(काष्ठा drm_i915_निजी *i915);
bool पूर्णांकel_vgpu_has_huge_gtt(काष्ठा drm_i915_निजी *i915);

पूर्णांक पूर्णांकel_vgt_balloon(काष्ठा i915_ggtt *ggtt);
व्योम पूर्णांकel_vgt_deballoon(काष्ठा i915_ggtt *ggtt);

#पूर्ण_अगर /* _I915_VGPU_H_ */
