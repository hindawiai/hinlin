<शैली गुरु>
/* mga_irq.c -- IRQ handling क्रम radeon -*- linux-c -*-
 */
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

#समावेश "mga_drv.h"

u32 mga_get_vblank_counter(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	स्थिर drm_mga_निजी_t *स्थिर dev_priv =
		(drm_mga_निजी_t *) dev->dev_निजी;

	अगर (pipe != 0)
		वापस 0;

	वापस atomic_पढ़ो(&dev_priv->vbl_received);
पूर्ण


irqवापस_t mga_driver_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *) arg;
	drm_mga_निजी_t *dev_priv = (drm_mga_निजी_t *) dev->dev_निजी;
	पूर्णांक status;
	पूर्णांक handled = 0;

	status = MGA_READ(MGA_STATUS);

	/* VBLANK पूर्णांकerrupt */
	अगर (status & MGA_VLINEPEN) अणु
		MGA_WRITE(MGA_ICLEAR, MGA_VLINEICLR);
		atomic_inc(&dev_priv->vbl_received);
		drm_handle_vblank(dev, 0);
		handled = 1;
	पूर्ण

	/* SOFTRAP पूर्णांकerrupt */
	अगर (status & MGA_SOFTRAPEN) अणु
		स्थिर u32 prim_start = MGA_READ(MGA_PRIMADDRESS);
		स्थिर u32 prim_end = MGA_READ(MGA_PRIMEND);


		MGA_WRITE(MGA_ICLEAR, MGA_SOFTRAPICLR);

		/* In addition to clearing the पूर्णांकerrupt-pending bit, we
		 * have to ग_लिखो to MGA_PRIMEND to re-start the DMA operation.
		 */
		अगर ((prim_start & ~0x03) != (prim_end & ~0x03))
			MGA_WRITE(MGA_PRIMEND, prim_end);

		atomic_inc(&dev_priv->last_fence_retired);
		wake_up(&dev_priv->fence_queue);
		handled = 1;
	पूर्ण

	अगर (handled)
		वापस IRQ_HANDLED;
	वापस IRQ_NONE;
पूर्ण

पूर्णांक mga_enable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	drm_mga_निजी_t *dev_priv = (drm_mga_निजी_t *) dev->dev_निजी;

	अगर (pipe != 0) अणु
		DRM_ERROR("tried to enable vblank on non-existent crtc %u\n",
			  pipe);
		वापस 0;
	पूर्ण

	MGA_WRITE(MGA_IEN, MGA_VLINEIEN | MGA_SOFTRAPEN);
	वापस 0;
पूर्ण


व्योम mga_disable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	अगर (pipe != 0) अणु
		DRM_ERROR("tried to disable vblank on non-existent crtc %u\n",
			  pipe);
	पूर्ण

	/* Do *NOT* disable the vertical refresh पूर्णांकerrupt.  MGA करोesn't have
	 * a nice hardware counter that tracks the number of refreshes when
	 * the पूर्णांकerrupt is disabled, and the kernel करोesn't know the refresh
	 * rate to calculate an estimate.
	 */
	/* MGA_WRITE(MGA_IEN, MGA_VLINEIEN | MGA_SOFTRAPEN); */
पूर्ण

व्योम mga_driver_fence_रुको(काष्ठा drm_device *dev, अचिन्हित पूर्णांक *sequence)
अणु
	drm_mga_निजी_t *dev_priv = (drm_mga_निजी_t *) dev->dev_निजी;
	अचिन्हित पूर्णांक cur_fence;

	/* Assume that the user has missed the current sequence number
	 * by about a day rather than she wants to रुको क्रम years
	 * using fences.
	 */
	रुको_event_समयout(dev_priv->fence_queue,
		    (((cur_fence = atomic_पढ़ो(&dev_priv->last_fence_retired))
		      - *sequence) <= (1 << 23)),
		    msecs_to_jअगरfies(3000));

	*sequence = cur_fence;
पूर्ण

व्योम mga_driver_irq_preinstall(काष्ठा drm_device *dev)
अणु
	drm_mga_निजी_t *dev_priv = (drm_mga_निजी_t *) dev->dev_निजी;

	/* Disable *all* पूर्णांकerrupts */
	MGA_WRITE(MGA_IEN, 0);
	/* Clear bits अगर they're alपढ़ोy high */
	MGA_WRITE(MGA_ICLEAR, ~0);
पूर्ण

पूर्णांक mga_driver_irq_postinstall(काष्ठा drm_device *dev)
अणु
	drm_mga_निजी_t *dev_priv = (drm_mga_निजी_t *) dev->dev_निजी;

	init_रुकोqueue_head(&dev_priv->fence_queue);

	/* Turn on soft trap पूर्णांकerrupt.  Vertical blank पूर्णांकerrupts are enabled
	 * in mga_enable_vblank.
	 */
	MGA_WRITE(MGA_IEN, MGA_SOFTRAPEN);
	वापस 0;
पूर्ण

व्योम mga_driver_irq_uninstall(काष्ठा drm_device *dev)
अणु
	drm_mga_निजी_t *dev_priv = (drm_mga_निजी_t *) dev->dev_निजी;
	अगर (!dev_priv)
		वापस;

	/* Disable *all* पूर्णांकerrupts */
	MGA_WRITE(MGA_IEN, 0);

	dev->irq_enabled = false;
पूर्ण
