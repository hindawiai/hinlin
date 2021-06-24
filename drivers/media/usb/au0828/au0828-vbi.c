<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
   au0828-vbi.c - VBI driver क्रम au0828

   Copyright (C) 2010 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>

   This work was sponsored by GetWellNetwork Inc.

 */

#समावेश "au0828.h"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>

/* ------------------------------------------------------------------ */

अटल पूर्णांक vbi_queue_setup(काष्ठा vb2_queue *vq,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा au0828_dev *dev = vb2_get_drv_priv(vq);
	अचिन्हित दीर्घ size = dev->vbi_width * dev->vbi_height * 2;

	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = size;
	वापस 0;
पूर्ण

अटल पूर्णांक vbi_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा au0828_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size;

	size = dev->vbi_width * dev->vbi_height * 2;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		pr_err("%s data will not fit into plane (%lu < %lu)\n",
			__func__, vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण
	vb2_set_plane_payload(vb, 0, size);

	वापस 0;
पूर्ण

अटल व्योम
vbi_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा au0828_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा au0828_buffer *buf =
			container_of(vbuf, काष्ठा au0828_buffer, vb);
	काष्ठा au0828_dmaqueue *vbiq = &dev->vbiq;
	अचिन्हित दीर्घ flags = 0;

	buf->mem = vb2_plane_vaddr(vb, 0);
	buf->length = vb2_plane_size(vb, 0);

	spin_lock_irqsave(&dev->slock, flags);
	list_add_tail(&buf->list, &vbiq->active);
	spin_unlock_irqrestore(&dev->slock, flags);
पूर्ण

स्थिर काष्ठा vb2_ops au0828_vbi_qops = अणु
	.queue_setup     = vbi_queue_setup,
	.buf_prepare     = vbi_buffer_prepare,
	.buf_queue       = vbi_buffer_queue,
	.start_streaming = au0828_start_analog_streaming,
	.stop_streaming  = au0828_stop_vbi_streaming,
	.रुको_prepare    = vb2_ops_रुको_prepare,
	.रुको_finish     = vb2_ops_रुको_finish,
पूर्ण;
