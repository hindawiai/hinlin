<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित _I915_COMPONENT_H_
#घोषणा _I915_COMPONENT_H_

#समावेश "drm_audio_component.h"

क्रमागत i915_component_type अणु
	I915_COMPONENT_AUDIO = 1,
	I915_COMPONENT_HDCP,
पूर्ण;

/* MAX_PORT is the number of port
 * It must be sync with I915_MAX_PORTS defined i915_drv.h
 */
#घोषणा MAX_PORTS 9

/**
 * काष्ठा i915_audio_component - Used क्रम direct communication between i915 and hda drivers
 */
काष्ठा i915_audio_component अणु
	/**
	 * @base: the drm_audio_component base class
	 */
	काष्ठा drm_audio_component	base;

	/**
	 * @aud_sample_rate: the array of audio sample rate per port
	 */
	पूर्णांक aud_sample_rate[MAX_PORTS];
पूर्ण;

#पूर्ण_अगर /* _I915_COMPONENT_H_ */
