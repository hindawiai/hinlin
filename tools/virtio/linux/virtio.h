<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_VIRTIO_H
#घोषणा LINUX_VIRTIO_H
#समावेश <linux/scatterlist.h>
#समावेश <linux/kernel.h>

काष्ठा device अणु
	व्योम *parent;
पूर्ण;

काष्ठा virtio_device अणु
	काष्ठा device dev;
	u64 features;
	काष्ठा list_head vqs;
पूर्ण;

काष्ठा virtqueue अणु
	काष्ठा list_head list;
	व्योम (*callback)(काष्ठा virtqueue *vq);
	स्थिर अक्षर *name;
	काष्ठा virtio_device *vdev;
        अचिन्हित पूर्णांक index;
        अचिन्हित पूर्णांक num_मुक्त;
	व्योम *priv;
पूर्ण;

/* Interfaces exported by virtio_ring. */
पूर्णांक virtqueue_add_sgs(काष्ठा virtqueue *vq,
		      काष्ठा scatterlist *sgs[],
		      अचिन्हित पूर्णांक out_sgs,
		      अचिन्हित पूर्णांक in_sgs,
		      व्योम *data,
		      gfp_t gfp);

पूर्णांक virtqueue_add_outbuf(काष्ठा virtqueue *vq,
			 काष्ठा scatterlist sg[], अचिन्हित पूर्णांक num,
			 व्योम *data,
			 gfp_t gfp);

पूर्णांक virtqueue_add_inbuf(काष्ठा virtqueue *vq,
			काष्ठा scatterlist sg[], अचिन्हित पूर्णांक num,
			व्योम *data,
			gfp_t gfp);

bool virtqueue_kick(काष्ठा virtqueue *vq);

व्योम *virtqueue_get_buf(काष्ठा virtqueue *vq, अचिन्हित पूर्णांक *len);

व्योम virtqueue_disable_cb(काष्ठा virtqueue *vq);

bool virtqueue_enable_cb(काष्ठा virtqueue *vq);
bool virtqueue_enable_cb_delayed(काष्ठा virtqueue *vq);

व्योम *virtqueue_detach_unused_buf(काष्ठा virtqueue *vq);
काष्ठा virtqueue *vring_new_virtqueue(अचिन्हित पूर्णांक index,
				      अचिन्हित पूर्णांक num,
				      अचिन्हित पूर्णांक vring_align,
				      काष्ठा virtio_device *vdev,
				      bool weak_barriers,
				      bool ctx,
				      व्योम *pages,
				      bool (*notअगरy)(काष्ठा virtqueue *vq),
				      व्योम (*callback)(काष्ठा virtqueue *vq),
				      स्थिर अक्षर *name);
व्योम vring_del_virtqueue(काष्ठा virtqueue *vq);

#पूर्ण_अगर
