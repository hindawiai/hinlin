<शैली गुरु>
/* radeon_atomमूलप्रण.स -- Private header क्रम radeon driver -*- linux-c -*-
 *
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 */

#अगर_अघोषित __RADEON_ATOMBIOS_H__
#घोषणा __RADEON_ATOMBIOS_H__

काष्ठा drm_connector;
काष्ठा drm_device;
काष्ठा drm_display_mode;
काष्ठा radeon_device;
काष्ठा radeon_encoder;

bool radeon_atom_get_tv_timings(काष्ठा radeon_device *rdev, पूर्णांक index,
				काष्ठा drm_display_mode *mode);
व्योम radeon_add_atom_encoder(काष्ठा drm_device *dev, uपूर्णांक32_t encoder_क्रमागत,
			     uपूर्णांक32_t supported_device, u16 caps);
व्योम radeon_atom_backlight_init(काष्ठा radeon_encoder *radeon_encoder,
				काष्ठा drm_connector *drm_connector);


#पूर्ण_अगर                         /* __RADEON_ATOMBIOS_H__ */
