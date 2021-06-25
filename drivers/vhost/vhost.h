<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _VHOST_H
#घोषणा _VHOST_H

#समावेश <linux/eventfd.h>
#समावेश <linux/vhost.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/file.h>
#समावेश <linux/uपन.स>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_ring.h>
#समावेश <linux/atomic.h>
#समावेश <linux/vhost_iotlb.h>
#समावेश <linux/irqbypass.h>

काष्ठा vhost_work;
प्रकार व्योम (*vhost_work_fn_t)(काष्ठा vhost_work *work);

#घोषणा VHOST_WORK_QUEUED 1
काष्ठा vhost_work अणु
	काष्ठा llist_node	  node;
	vhost_work_fn_t		  fn;
	अचिन्हित दीर्घ		  flags;
पूर्ण;

/* Poll a file (eventfd or socket) */
/* Note: there's nothing vhost specअगरic about this काष्ठाure. */
काष्ठा vhost_poll अणु
	poll_table                table;
	रुको_queue_head_t        *wqh;
	रुको_queue_entry_t              रुको;
	काष्ठा vhost_work	  work;
	__poll_t		  mask;
	काष्ठा vhost_dev	 *dev;
पूर्ण;

व्योम vhost_work_init(काष्ठा vhost_work *work, vhost_work_fn_t fn);
व्योम vhost_work_queue(काष्ठा vhost_dev *dev, काष्ठा vhost_work *work);
bool vhost_has_work(काष्ठा vhost_dev *dev);

व्योम vhost_poll_init(काष्ठा vhost_poll *poll, vhost_work_fn_t fn,
		     __poll_t mask, काष्ठा vhost_dev *dev);
पूर्णांक vhost_poll_start(काष्ठा vhost_poll *poll, काष्ठा file *file);
व्योम vhost_poll_stop(काष्ठा vhost_poll *poll);
व्योम vhost_poll_flush(काष्ठा vhost_poll *poll);
व्योम vhost_poll_queue(काष्ठा vhost_poll *poll);
व्योम vhost_work_flush(काष्ठा vhost_dev *dev, काष्ठा vhost_work *work);
दीर्घ vhost_vring_ioctl(काष्ठा vhost_dev *d, अचिन्हित पूर्णांक ioctl, व्योम __user *argp);

काष्ठा vhost_log अणु
	u64 addr;
	u64 len;
पूर्ण;

क्रमागत vhost_uaddr_type अणु
	VHOST_ADDR_DESC = 0,
	VHOST_ADDR_AVAIL = 1,
	VHOST_ADDR_USED = 2,
	VHOST_NUM_ADDRS = 3,
पूर्ण;

काष्ठा vhost_vring_call अणु
	काष्ठा eventfd_ctx *ctx;
	काष्ठा irq_bypass_producer producer;
पूर्ण;

/* The virtqueue काष्ठाure describes a queue attached to a device. */
काष्ठा vhost_virtqueue अणु
	काष्ठा vhost_dev *dev;

	/* The actual ring of buffers. */
	काष्ठा mutex mutex;
	अचिन्हित पूर्णांक num;
	vring_desc_t __user *desc;
	vring_avail_t __user *avail;
	vring_used_t __user *used;
	स्थिर काष्ठा vhost_iotlb_map *meta_iotlb[VHOST_NUM_ADDRS];
	काष्ठा file *kick;
	काष्ठा vhost_vring_call call_ctx;
	काष्ठा eventfd_ctx *error_ctx;
	काष्ठा eventfd_ctx *log_ctx;

	काष्ठा vhost_poll poll;

	/* The routine to call when the Guest pings us, or समयout. */
	vhost_work_fn_t handle_kick;

	/* Last available index we saw. */
	u16 last_avail_idx;

	/* Caches available index value from user. */
	u16 avail_idx;

	/* Last index we used. */
	u16 last_used_idx;

	/* Used flags */
	u16 used_flags;

	/* Last used index value we have संकेतled on */
	u16 संकेतled_used;

	/* Last used index value we have संकेतled on */
	bool संकेतled_used_valid;

	/* Log ग_लिखोs to used काष्ठाure. */
	bool log_used;
	u64 log_addr;

	काष्ठा iovec iov[UIO_MAXIOV];
	काष्ठा iovec iotlb_iov[64];
	काष्ठा iovec *indirect;
	काष्ठा vring_used_elem *heads;
	/* Protected by virtqueue mutex. */
	काष्ठा vhost_iotlb *umem;
	काष्ठा vhost_iotlb *iotlb;
	व्योम *निजी_data;
	u64 acked_features;
	u64 acked_backend_features;
	/* Log ग_लिखो descriptors */
	व्योम __user *log_base;
	काष्ठा vhost_log *log;
	काष्ठा iovec log_iov[64];

	/* Ring endianness. Defaults to legacy native endianness.
	 * Set to true when starting a modern virtio device. */
	bool is_le;
#अगर_घोषित CONFIG_VHOST_CROSS_ENDIAN_LEGACY
	/* Ring endianness requested by userspace क्रम cross-endian support. */
	bool user_be;
#पूर्ण_अगर
	u32 busyloop_समयout;
पूर्ण;

काष्ठा vhost_msg_node अणु
  जोड़ अणु
	  काष्ठा vhost_msg msg;
	  काष्ठा vhost_msg_v2 msg_v2;
  पूर्ण;
  काष्ठा vhost_virtqueue *vq;
  काष्ठा list_head node;
पूर्ण;

काष्ठा vhost_dev अणु
	काष्ठा mm_काष्ठा *mm;
	काष्ठा mutex mutex;
	काष्ठा vhost_virtqueue **vqs;
	पूर्णांक nvqs;
	काष्ठा eventfd_ctx *log_ctx;
	काष्ठा llist_head work_list;
	काष्ठा task_काष्ठा *worker;
	काष्ठा vhost_iotlb *umem;
	काष्ठा vhost_iotlb *iotlb;
	spinlock_t iotlb_lock;
	काष्ठा list_head पढ़ो_list;
	काष्ठा list_head pending_list;
	रुको_queue_head_t रुको;
	पूर्णांक iov_limit;
	पूर्णांक weight;
	पूर्णांक byte_weight;
	u64 kcov_handle;
	bool use_worker;
	पूर्णांक (*msg_handler)(काष्ठा vhost_dev *dev,
			   काष्ठा vhost_iotlb_msg *msg);
पूर्ण;

bool vhost_exceeds_weight(काष्ठा vhost_virtqueue *vq, पूर्णांक pkts, पूर्णांक total_len);
व्योम vhost_dev_init(काष्ठा vhost_dev *, काष्ठा vhost_virtqueue **vqs,
		    पूर्णांक nvqs, पूर्णांक iov_limit, पूर्णांक weight, पूर्णांक byte_weight,
		    bool use_worker,
		    पूर्णांक (*msg_handler)(काष्ठा vhost_dev *dev,
				       काष्ठा vhost_iotlb_msg *msg));
दीर्घ vhost_dev_set_owner(काष्ठा vhost_dev *dev);
bool vhost_dev_has_owner(काष्ठा vhost_dev *dev);
दीर्घ vhost_dev_check_owner(काष्ठा vhost_dev *);
काष्ठा vhost_iotlb *vhost_dev_reset_owner_prepare(व्योम);
व्योम vhost_dev_reset_owner(काष्ठा vhost_dev *dev, काष्ठा vhost_iotlb *iotlb);
व्योम vhost_dev_cleanup(काष्ठा vhost_dev *);
व्योम vhost_dev_stop(काष्ठा vhost_dev *);
दीर्घ vhost_dev_ioctl(काष्ठा vhost_dev *, अचिन्हित पूर्णांक ioctl, व्योम __user *argp);
दीर्घ vhost_vring_ioctl(काष्ठा vhost_dev *d, अचिन्हित पूर्णांक ioctl, व्योम __user *argp);
bool vhost_vq_access_ok(काष्ठा vhost_virtqueue *vq);
bool vhost_log_access_ok(काष्ठा vhost_dev *);

पूर्णांक vhost_get_vq_desc(काष्ठा vhost_virtqueue *,
		      काष्ठा iovec iov[], अचिन्हित पूर्णांक iov_count,
		      अचिन्हित पूर्णांक *out_num, अचिन्हित पूर्णांक *in_num,
		      काष्ठा vhost_log *log, अचिन्हित पूर्णांक *log_num);
व्योम vhost_discard_vq_desc(काष्ठा vhost_virtqueue *, पूर्णांक n);

bool vhost_vq_is_setup(काष्ठा vhost_virtqueue *vq);
पूर्णांक vhost_vq_init_access(काष्ठा vhost_virtqueue *);
पूर्णांक vhost_add_used(काष्ठा vhost_virtqueue *, अचिन्हित पूर्णांक head, पूर्णांक len);
पूर्णांक vhost_add_used_n(काष्ठा vhost_virtqueue *, काष्ठा vring_used_elem *heads,
		     अचिन्हित count);
व्योम vhost_add_used_and_संकेत(काष्ठा vhost_dev *, काष्ठा vhost_virtqueue *,
			       अचिन्हित पूर्णांक id, पूर्णांक len);
व्योम vhost_add_used_and_संकेत_n(काष्ठा vhost_dev *, काष्ठा vhost_virtqueue *,
			       काष्ठा vring_used_elem *heads, अचिन्हित count);
व्योम vhost_संकेत(काष्ठा vhost_dev *, काष्ठा vhost_virtqueue *);
व्योम vhost_disable_notअगरy(काष्ठा vhost_dev *, काष्ठा vhost_virtqueue *);
bool vhost_vq_avail_empty(काष्ठा vhost_dev *, काष्ठा vhost_virtqueue *);
bool vhost_enable_notअगरy(काष्ठा vhost_dev *, काष्ठा vhost_virtqueue *);

पूर्णांक vhost_log_ग_लिखो(काष्ठा vhost_virtqueue *vq, काष्ठा vhost_log *log,
		    अचिन्हित पूर्णांक log_num, u64 len,
		    काष्ठा iovec *iov, पूर्णांक count);
पूर्णांक vq_meta_prefetch(काष्ठा vhost_virtqueue *vq);

काष्ठा vhost_msg_node *vhost_new_msg(काष्ठा vhost_virtqueue *vq, पूर्णांक type);
व्योम vhost_enqueue_msg(काष्ठा vhost_dev *dev,
		       काष्ठा list_head *head,
		       काष्ठा vhost_msg_node *node);
काष्ठा vhost_msg_node *vhost_dequeue_msg(काष्ठा vhost_dev *dev,
					 काष्ठा list_head *head);
व्योम vhost_set_backend_features(काष्ठा vhost_dev *dev, u64 features);

__poll_t vhost_chr_poll(काष्ठा file *file, काष्ठा vhost_dev *dev,
			    poll_table *रुको);
sमाप_प्रकार vhost_chr_पढ़ो_iter(काष्ठा vhost_dev *dev, काष्ठा iov_iter *to,
			    पूर्णांक noblock);
sमाप_प्रकार vhost_chr_ग_लिखो_iter(काष्ठा vhost_dev *dev,
			     काष्ठा iov_iter *from);
पूर्णांक vhost_init_device_iotlb(काष्ठा vhost_dev *d, bool enabled);

व्योम vhost_iotlb_map_मुक्त(काष्ठा vhost_iotlb *iotlb,
			  काष्ठा vhost_iotlb_map *map);

#घोषणा vq_err(vq, fmt, ...) करो अणु                                  \
		pr_debug(pr_fmt(fmt), ##__VA_ARGS__);       \
		अगर ((vq)->error_ctx)                               \
				eventfd_संकेत((vq)->error_ctx, 1);\
	पूर्ण जबतक (0)

क्रमागत अणु
	VHOST_FEATURES = (1ULL << VIRTIO_F_NOTIFY_ON_EMPTY) |
			 (1ULL << VIRTIO_RING_F_INसूचीECT_DESC) |
			 (1ULL << VIRTIO_RING_F_EVENT_IDX) |
			 (1ULL << VHOST_F_LOG_ALL) |
			 (1ULL << VIRTIO_F_ANY_LAYOUT) |
			 (1ULL << VIRTIO_F_VERSION_1)
पूर्ण;

/**
 * vhost_vq_set_backend - Set backend.
 *
 * @vq            Virtqueue.
 * @निजी_data  The निजी data.
 *
 * Context: Need to call with vq->mutex acquired.
 */
अटल अंतरभूत व्योम vhost_vq_set_backend(काष्ठा vhost_virtqueue *vq,
					व्योम *निजी_data)
अणु
	vq->निजी_data = निजी_data;
पूर्ण

/**
 * vhost_vq_get_backend - Get backend.
 *
 * @vq            Virtqueue.
 *
 * Context: Need to call with vq->mutex acquired.
 * Return: Private data previously set with vhost_vq_set_backend.
 */
अटल अंतरभूत व्योम *vhost_vq_get_backend(काष्ठा vhost_virtqueue *vq)
अणु
	वापस vq->निजी_data;
पूर्ण

अटल अंतरभूत bool vhost_has_feature(काष्ठा vhost_virtqueue *vq, पूर्णांक bit)
अणु
	वापस vq->acked_features & (1ULL << bit);
पूर्ण

अटल अंतरभूत bool vhost_backend_has_feature(काष्ठा vhost_virtqueue *vq, पूर्णांक bit)
अणु
	वापस vq->acked_backend_features & (1ULL << bit);
पूर्ण

#अगर_घोषित CONFIG_VHOST_CROSS_ENDIAN_LEGACY
अटल अंतरभूत bool vhost_is_little_endian(काष्ठा vhost_virtqueue *vq)
अणु
	वापस vq->is_le;
पूर्ण
#अन्यथा
अटल अंतरभूत bool vhost_is_little_endian(काष्ठा vhost_virtqueue *vq)
अणु
	वापस virtio_legacy_is_little_endian() || vq->is_le;
पूर्ण
#पूर्ण_अगर

/* Memory accessors */
अटल अंतरभूत u16 vhost16_to_cpu(काष्ठा vhost_virtqueue *vq, __virtio16 val)
अणु
	वापस __virtio16_to_cpu(vhost_is_little_endian(vq), val);
पूर्ण

अटल अंतरभूत __virtio16 cpu_to_vhost16(काष्ठा vhost_virtqueue *vq, u16 val)
अणु
	वापस __cpu_to_virtio16(vhost_is_little_endian(vq), val);
पूर्ण

अटल अंतरभूत u32 vhost32_to_cpu(काष्ठा vhost_virtqueue *vq, __virtio32 val)
अणु
	वापस __virtio32_to_cpu(vhost_is_little_endian(vq), val);
पूर्ण

अटल अंतरभूत __virtio32 cpu_to_vhost32(काष्ठा vhost_virtqueue *vq, u32 val)
अणु
	वापस __cpu_to_virtio32(vhost_is_little_endian(vq), val);
पूर्ण

अटल अंतरभूत u64 vhost64_to_cpu(काष्ठा vhost_virtqueue *vq, __virtio64 val)
अणु
	वापस __virtio64_to_cpu(vhost_is_little_endian(vq), val);
पूर्ण

अटल अंतरभूत __virtio64 cpu_to_vhost64(काष्ठा vhost_virtqueue *vq, u64 val)
अणु
	वापस __cpu_to_virtio64(vhost_is_little_endian(vq), val);
पूर्ण
#पूर्ण_अगर
