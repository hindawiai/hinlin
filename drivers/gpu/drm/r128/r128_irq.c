<शैली गुरु>
/* r128_irq.c -- IRQ handling क्रम radeon -*- linux-c -*- */
/*
 * Copyright (C) The Weather Channel, Inc.  2002.  All Rights Reserved.
 *
 * The Weather Channel (TM) funded Tungsten Graphics to develop the
 * initial release of the Radeon 8500 driver under the XFree86 license.
 * This notice must be preserved.
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
 * Authors:
 *    Keith Whitwell <keith@tungstengraphics.com>
 *    Eric Anholt <anholt@FreeBSD.org>
 */

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/r128_drm.h>

#समावेश "r128_drv.h"

u32 r128_get_vblank_counter(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	स्थिर drm_r128_निजी_t *dev_priv = dev->dev_निजी;

	अगर (pipe != 0)
		वापस 0;

	वापस atomic_पढ़ो(&dev_priv->vbl_received);
पूर्ण

irqवापस_t r128_driver_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *) arg;
	drm_r128_निजी_t *dev_priv = (drm_r128_निजी_t *) dev->dev_निजी;
	पूर्णांक status;

	status = R128_READ(R128_GEN_INT_STATUS);

	/* VBLANK पूर्णांकerrupt */
	अगर (status & R128_CRTC_VBLANK_INT) अणु
		R128_WRITE(R128_GEN_INT_STATUS, R128_CRTC_VBLANK_INT_AK);
		atomic_inc(&dev_priv->vbl_received);
		drm_handle_vblank(dev, 0);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

पूर्णांक r128_enable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	drm_r128_निजी_t *dev_priv = dev->dev_निजी;

	अगर (pipe != 0) अणु
		DRM_ERROR("%s:  bad crtc %u\n", __func__, pipe);
		वापस -EINVAL;
	पूर्ण

	R128_WRITE(R128_GEN_INT_CNTL, R128_CRTC_VBLANK_INT_EN);
	वापस 0;
पूर्ण

व्योम r128_disable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	अगर (pipe != 0)
		DRM_ERROR("%s:  bad crtc %u\n", __func__, pipe);

	/*
	 * FIXME: implement proper पूर्णांकerrupt disable by using the vblank
	 * counter रेजिस्टर (अगर available)
	 *
	 * R128_WRITE(R128_GEN_INT_CNTL,
	 *            R128_READ(R128_GEN_INT_CNTL) & ~R128_CRTC_VBLANK_INT_EN);
	 */
पूर्ण

व्योम r128_driver_irq_preinstall(काष्ठा drm_device *dev)
अणु
	drm_r128_निजी_t *dev_priv = (drm_r128_निजी_t *) dev->dev_निजी;

	/* Disable *all* पूर्णांकerrupts */
	R128_WRITE(R128_GEN_INT_CNTL, 0);
	/* Clear vblank bit अगर it's alपढ़ोy high */
	R128_WRITE(R128_GEN_INT_STATUS, R128_CRTC_VBLANK_INT_AK);
पूर्ण

पूर्णांक r128_driver_irq_postinstall(काष्ठा drm_device *dev)
अणु
	वापस 0;
पूर्ण

व्योम r128_driver_irq_uninstall(काष्ठा drm_device *dev)
अणु
	drm_r128_निजी_t *dev_priv = (drm_r128_निजी_t *) dev->dev_निजी;
	अगर (!dev_priv)
		वापस;

	/* Disable *all* पूर्णांकerrupts */
	R128_WRITE(R128_GEN_INT_CNTL, 0);
पूर्ण
