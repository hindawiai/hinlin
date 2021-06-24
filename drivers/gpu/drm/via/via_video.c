<शैली गुरु>
/*
 * Copyright 2005 Thomas Hellstrom. All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHOR(S), AND/OR THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Author: Thomas Hellstrom 2005.
 *
 * Video and XvMC related functions.
 */

#समावेश <drm/drm_device.h>
#समावेश <drm/via_drm.h>

#समावेश "via_drv.h"

व्योम via_init_futex(drm_via_निजी_t *dev_priv)
अणु
	अचिन्हित पूर्णांक i;

	DRM_DEBUG("\n");

	क्रम (i = 0; i < VIA_NR_XVMC_LOCKS; ++i) अणु
		init_रुकोqueue_head(&(dev_priv->decoder_queue[i]));
		XVMCLOCKPTR(dev_priv->sarea_priv, i)->lock = 0;
	पूर्ण
पूर्ण

व्योम via_cleanup_futex(drm_via_निजी_t *dev_priv)
अणु
पूर्ण

व्योम via_release_futex(drm_via_निजी_t *dev_priv, पूर्णांक context)
अणु
	अचिन्हित पूर्णांक i;
	अस्थिर पूर्णांक *lock;

	अगर (!dev_priv->sarea_priv)
		वापस;

	क्रम (i = 0; i < VIA_NR_XVMC_LOCKS; ++i) अणु
		lock = (अस्थिर पूर्णांक *)XVMCLOCKPTR(dev_priv->sarea_priv, i);
		अगर ((_DRM_LOCKING_CONTEXT(*lock) == context)) अणु
			अगर (_DRM_LOCK_IS_HELD(*lock)
			    && (*lock & _DRM_LOCK_CONT)) अणु
				wake_up(&(dev_priv->decoder_queue[i]));
			पूर्ण
			*lock = 0;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक via_decoder_futex(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_futex_t *fx = data;
	अस्थिर पूर्णांक *lock;
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	drm_via_sarea_t *sAPriv = dev_priv->sarea_priv;
	पूर्णांक ret = 0;

	DRM_DEBUG("\n");

	अगर (fx->lock >= VIA_NR_XVMC_LOCKS)
		वापस -EFAULT;

	lock = (अस्थिर पूर्णांक *)XVMCLOCKPTR(sAPriv, fx->lock);

	चयन (fx->func) अणु
	हाल VIA_FUTEX_WAIT:
		VIA_WAIT_ON(ret, dev_priv->decoder_queue[fx->lock],
			    (fx->ms / 10) * (HZ / 100), *lock != fx->val);
		वापस ret;
	हाल VIA_FUTEX_WAKE:
		wake_up(&(dev_priv->decoder_queue[fx->lock]));
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण
