<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// em28xx-vbi.c - VBI driver क्रम em28xx
//
// Copyright (C) 2009 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
//
// This work was sponsored by EyeMagnet Limited.
//
// This program is मुक्त software; you can redistribute it and/or modअगरy
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License क्रम more details.

#समावेश "em28xx.h"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/init.h>
#समावेश <linux/usb.h>

#समावेश "em28xx-v4l.h"

/* ------------------------------------------------------------------ */

अटल पूर्णांक vbi_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा em28xx *dev = vb2_get_drv_priv(vq);
	काष्ठा em28xx_v4l2 *v4l2 = dev->v4l2;
	अचिन्हित दीर्घ size = v4l2->vbi_width * v4l2->vbi_height * 2;

	अगर (*nbuffers < 2)
		*nbuffers = 2;

	अगर (*nplanes) अणु
		अगर (sizes[0] < size)
			वापस -EINVAL;
		size = sizes[0];
	पूर्ण

	*nplanes = 1;
	sizes[0] = size;

	वापस 0;
पूर्ण

अटल पूर्णांक vbi_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा em28xx        *dev  = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा em28xx_v4l2   *v4l2 = dev->v4l2;
	अचिन्हित दीर्घ        size;

	size = v4l2->vbi_width * v4l2->vbi_height * 2;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		dev_info(&dev->पूर्णांकf->dev,
			 "%s data will not fit into plane (%lu < %lu)\n",
			 __func__, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण
	vb2_set_plane_payload(vb, 0, size);

	वापस 0;
पूर्ण

अटल व्योम
vbi_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा em28xx *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा em28xx_buffer *buf =
		container_of(vbuf, काष्ठा em28xx_buffer, vb);
	काष्ठा em28xx_dmaqueue *vbiq = &dev->vbiq;
	अचिन्हित दीर्घ flags = 0;

	buf->mem = vb2_plane_vaddr(vb, 0);
	buf->length = vb2_plane_size(vb, 0);

	spin_lock_irqsave(&dev->slock, flags);
	list_add_tail(&buf->list, &vbiq->active);
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

स्थिर काष्ठा vb2_ops em28xx_vbi_qops = अणु
	.queue_setup    = vbi_queue_setup,
	.buf_prepare    = vbi_buffer_prepare,
	.buf_queue      = vbi_buffer_queue,
	.start_streaming = em28xx_start_analog_streaming,
	.stop_streaming = em28xx_stop_vbi_streaming,
	.रुको_prepare   = vb2_ops_रुको_prepare,
	.रुको_finish    = vb2_ops_रुको_finish,
पूर्ण;
