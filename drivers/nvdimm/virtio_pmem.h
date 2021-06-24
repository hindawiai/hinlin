<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * virtio_pस्मृति.स: virtio pmem Driver
 *
 * Discovers persistent memory range inक्रमmation
 * from host and provides a virtio based flushing
 * पूर्णांकerface.
 **/

#अगर_अघोषित _LINUX_VIRTIO_PMEM_H
#घोषणा _LINUX_VIRTIO_PMEM_H

#समावेश <linux/module.h>
#समावेश <uapi/linux/virtio_pस्मृति.स>
#समावेश <linux/libnvdimm.h>
#समावेश <linux/spinlock.h>

काष्ठा virtio_pmem_request अणु
	काष्ठा virtio_pmem_req req;
	काष्ठा virtio_pmem_resp resp;

	/* Wait queue to process deferred work after ack from host */
	रुको_queue_head_t host_acked;
	bool करोne;

	/* Wait queue to process deferred work after virt queue buffer avail */
	रुको_queue_head_t wq_buf;
	bool wq_buf_avail;
	काष्ठा list_head list;
पूर्ण;

काष्ठा virtio_pmem अणु
	काष्ठा virtio_device *vdev;

	/* Virtio pmem request queue */
	काष्ठा virtqueue *req_vq;

	/* nvdimm bus रेजिस्टरs virtio pmem device */
	काष्ठा nvdimm_bus *nvdimm_bus;
	काष्ठा nvdimm_bus_descriptor nd_desc;

	/* List to store deferred work अगर virtqueue is full */
	काष्ठा list_head req_list;

	/* Synchronize virtqueue data */
	spinlock_t pmem_lock;

	/* Memory region inक्रमmation */
	__u64 start;
	__u64 size;
पूर्ण;

व्योम virtio_pmem_host_ack(काष्ठा virtqueue *vq);
पूर्णांक async_pmem_flush(काष्ठा nd_region *nd_region, काष्ठा bio *bio);
#पूर्ण_अगर
