<शैली गुरु>
/* radeon_kms.h -- Private header क्रम radeon driver -*- linux-c -*-
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Fremont, Calअगरornia.
 * All rights reserved.
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __RADEON_KMS_H__
#घोषणा __RADEON_KMS_H__

u32 radeon_get_vblank_counter_kms(काष्ठा drm_crtc *crtc);
पूर्णांक radeon_enable_vblank_kms(काष्ठा drm_crtc *crtc);
व्योम radeon_disable_vblank_kms(काष्ठा drm_crtc *crtc);
irqवापस_t radeon_driver_irq_handler_kms(पूर्णांक irq, व्योम *arg);
व्योम radeon_driver_irq_preinstall_kms(काष्ठा drm_device *dev);
पूर्णांक radeon_driver_irq_postinstall_kms(काष्ठा drm_device *dev);
व्योम radeon_driver_irq_uninstall_kms(काष्ठा drm_device *dev);

#पूर्ण_अगर				/* __RADEON_KMS_H__ */
