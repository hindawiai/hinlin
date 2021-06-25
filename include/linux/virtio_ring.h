<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VIRTIO_RING_H
#घोषणा _LINUX_VIRTIO_RING_H

#समावेश <यंत्र/barrier.h>
#समावेश <linux/irqवापस.h>
#समावेश <uapi/linux/virtio_ring.h>

/*
 * Barriers in virtio are tricky.  Non-SMP virtio guests can't assume
 * they're not on an SMP host प्रणाली, so they need to assume real
 * barriers.  Non-SMP virtio hosts could skip the barriers, but करोes
 * anyone care?
 *
 * For virtio_pci on SMP, we करोn't need to order with respect to MMIO
 * accesses through relaxed memory I/O winकरोws, so virt_mb() et al are
 * sufficient.
 *
 * For using virtio to talk to real devices (eg. other heterogeneous
 * CPUs) we करो need real barriers.  In theory, we could be using both
 * kinds of virtio, so it's a runसमय decision, and the branch is
 * actually quite cheap.
 */

अटल अंतरभूत व्योम virtio_mb(bool weak_barriers)
अणु
	अगर (weak_barriers)
		virt_mb();
	अन्यथा
		mb();
पूर्ण

अटल अंतरभूत व्योम virtio_rmb(bool weak_barriers)
अणु
	अगर (weak_barriers)
		virt_rmb();
	अन्यथा
		dma_rmb();
पूर्ण

अटल अंतरभूत व्योम virtio_wmb(bool weak_barriers)
अणु
	अगर (weak_barriers)
		virt_wmb();
	अन्यथा
		dma_wmb();
पूर्ण

#घोषणा virtio_store_mb(weak_barriers, p, v) \
करो अणु \
	अगर (weak_barriers) अणु \
		virt_store_mb(*p, v); \
	पूर्ण अन्यथा अणु \
		WRITE_ONCE(*p, v); \
		mb(); \
	पूर्ण \
पूर्ण जबतक (0) \

काष्ठा virtio_device;
काष्ठा virtqueue;

/*
 * Creates a virtqueue and allocates the descriptor ring.  If
 * may_reduce_num is set, then this may allocate a smaller ring than
 * expected.  The caller should query virtqueue_get_vring_size to learn
 * the actual size of the ring.
 */
काष्ठा virtqueue *vring_create_virtqueue(अचिन्हित पूर्णांक index,
					 अचिन्हित पूर्णांक num,
					 अचिन्हित पूर्णांक vring_align,
					 काष्ठा virtio_device *vdev,
					 bool weak_barriers,
					 bool may_reduce_num,
					 bool ctx,
					 bool (*notअगरy)(काष्ठा virtqueue *vq),
					 व्योम (*callback)(काष्ठा virtqueue *vq),
					 स्थिर अक्षर *name);

/* Creates a virtqueue with a custom layout. */
काष्ठा virtqueue *__vring_new_virtqueue(अचिन्हित पूर्णांक index,
					काष्ठा vring vring,
					काष्ठा virtio_device *vdev,
					bool weak_barriers,
					bool ctx,
					bool (*notअगरy)(काष्ठा virtqueue *),
					व्योम (*callback)(काष्ठा virtqueue *),
					स्थिर अक्षर *name);

/*
 * Creates a virtqueue with a standard layout but a caller-allocated
 * ring.
 */
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

/*
 * Destroys a virtqueue.  If created with vring_create_virtqueue, this
 * also मुक्तs the ring.
 */
व्योम vring_del_virtqueue(काष्ठा virtqueue *vq);

/* Filter out transport-specअगरic feature bits. */
व्योम vring_transport_features(काष्ठा virtio_device *vdev);

irqवापस_t vring_पूर्णांकerrupt(पूर्णांक irq, व्योम *_vq);
#पूर्ण_अगर /* _LINUX_VIRTIO_RING_H */
