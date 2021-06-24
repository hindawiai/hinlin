<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Linux host-side vring helpers; क्रम when the kernel needs to access
 * someone अन्यथा's vring.
 *
 * Copyright IBM Corporation, 2013.
 * Parts taken from drivers/vhost/vhost.c Copyright 2009 Red Hat, Inc.
 *
 * Written by: Rusty Russell <rusty@rustcorp.com.au>
 */
#अगर_अघोषित _LINUX_VRINGH_H
#घोषणा _LINUX_VRINGH_H
#समावेश <uapi/linux/virtio_ring.h>
#समावेश <linux/virtio_byteorder.h>
#समावेश <linux/uपन.स>
#समावेश <linux/slab.h>
#अगर IS_REACHABLE(CONFIG_VHOST_IOTLB)
#समावेश <linux/dma-direction.h>
#समावेश <linux/vhost_iotlb.h>
#पूर्ण_अगर
#समावेश <यंत्र/barrier.h>

/* virtio_ring with inक्रमmation needed क्रम host access. */
काष्ठा vringh अणु
	/* Everything is little endian */
	bool little_endian;

	/* Guest publishes used event idx (note: we always करो). */
	bool event_indices;

	/* Can we get away with weak barriers? */
	bool weak_barriers;

	/* Last available index we saw (ie. where we're up to). */
	u16 last_avail_idx;

	/* Last index we used. */
	u16 last_used_idx;

	/* How many descriptors we've completed since last need_notअगरy(). */
	u32 completed;

	/* The vring (note: it may contain user poपूर्णांकers!) */
	काष्ठा vring vring;

	/* IOTLB क्रम this vring */
	काष्ठा vhost_iotlb *iotlb;

	/* spinlock to synchronize IOTLB accesses */
	spinlock_t *iotlb_lock;

	/* The function to call to notअगरy the guest about added buffers */
	व्योम (*notअगरy)(काष्ठा vringh *);
पूर्ण;

/**
 * काष्ठा vringh_config_ops - ops क्रम creating a host vring from a virtio driver
 * @find_vrhs: find the host vrings and instantiate them
 *	vdev: the virtio_device
 *	nhvrs: the number of host vrings to find
 *	hvrs: on success, includes new host vrings
 *	callbacks: array of driver callbacks, क्रम each host vring
 *		include a शून्य entry क्रम vqs that करो not need a callback
 *	Returns 0 on success or error status
 * @del_vrhs: मुक्त the host vrings found by find_vrhs().
 */
काष्ठा virtio_device;
प्रकार व्योम vrh_callback_t(काष्ठा virtio_device *, काष्ठा vringh *);
काष्ठा vringh_config_ops अणु
	पूर्णांक (*find_vrhs)(काष्ठा virtio_device *vdev, अचिन्हित nhvrs,
			 काष्ठा vringh *vrhs[], vrh_callback_t *callbacks[]);
	व्योम (*del_vrhs)(काष्ठा virtio_device *vdev);
पूर्ण;

/* The memory the vring can access, and what offset to apply. */
काष्ठा vringh_range अणु
	u64 start, end_incl;
	u64 offset;
पूर्ण;

/**
 * काष्ठा vringh_iov - iovec mangler.
 *
 * Mangles iovec in place, and restores it.
 * Reमुख्यing data is iov + i, of used - i elements.
 */
काष्ठा vringh_iov अणु
	काष्ठा iovec *iov;
	माप_प्रकार consumed; /* Within iov[i] */
	अचिन्हित i, used, max_num;
पूर्ण;

/**
 * काष्ठा vringh_iov - kvec mangler.
 *
 * Mangles kvec in place, and restores it.
 * Reमुख्यing data is iov + i, of used - i elements.
 */
काष्ठा vringh_kiov अणु
	काष्ठा kvec *iov;
	माप_प्रकार consumed; /* Within iov[i] */
	अचिन्हित i, used, max_num;
पूर्ण;

/* Flag on max_num to indicate we're kदो_स्मृतिed. */
#घोषणा VRINGH_IOV_ALLOCATED 0x8000000

/* Helpers क्रम userspace vrings. */
पूर्णांक vringh_init_user(काष्ठा vringh *vrh, u64 features,
		     अचिन्हित पूर्णांक num, bool weak_barriers,
		     vring_desc_t __user *desc,
		     vring_avail_t __user *avail,
		     vring_used_t __user *used);

अटल अंतरभूत व्योम vringh_iov_init(काष्ठा vringh_iov *iov,
				   काष्ठा iovec *iovec, अचिन्हित num)
अणु
	iov->used = iov->i = 0;
	iov->consumed = 0;
	iov->max_num = num;
	iov->iov = iovec;
पूर्ण

अटल अंतरभूत व्योम vringh_iov_reset(काष्ठा vringh_iov *iov)
अणु
	iov->iov[iov->i].iov_len += iov->consumed;
	iov->iov[iov->i].iov_base -= iov->consumed;
	iov->consumed = 0;
	iov->i = 0;
पूर्ण

अटल अंतरभूत व्योम vringh_iov_cleanup(काष्ठा vringh_iov *iov)
अणु
	अगर (iov->max_num & VRINGH_IOV_ALLOCATED)
		kमुक्त(iov->iov);
	iov->max_num = iov->used = iov->i = iov->consumed = 0;
	iov->iov = शून्य;
पूर्ण

/* Convert a descriptor पूर्णांकo iovecs. */
पूर्णांक vringh_getdesc_user(काष्ठा vringh *vrh,
			काष्ठा vringh_iov *riov,
			काष्ठा vringh_iov *wiov,
			bool (*getrange)(काष्ठा vringh *vrh,
					 u64 addr, काष्ठा vringh_range *r),
			u16 *head);

/* Copy bytes from पढ़ोable vsg, consuming it (and incrementing wiov->i). */
sमाप_प्रकार vringh_iov_pull_user(काष्ठा vringh_iov *riov, व्योम *dst, माप_प्रकार len);

/* Copy bytes पूर्णांकo writable vsg, consuming it (and incrementing wiov->i). */
sमाप_प्रकार vringh_iov_push_user(काष्ठा vringh_iov *wiov,
			     स्थिर व्योम *src, माप_प्रकार len);

/* Mark a descriptor as used. */
पूर्णांक vringh_complete_user(काष्ठा vringh *vrh, u16 head, u32 len);
पूर्णांक vringh_complete_multi_user(काष्ठा vringh *vrh,
			       स्थिर काष्ठा vring_used_elem used[],
			       अचिन्हित num_used);

/* Pretend we've never seen descriptor (क्रम easy error handling). */
व्योम vringh_abanकरोn_user(काष्ठा vringh *vrh, अचिन्हित पूर्णांक num);

/* Do we need to fire the eventfd to notअगरy the other side? */
पूर्णांक vringh_need_notअगरy_user(काष्ठा vringh *vrh);

bool vringh_notअगरy_enable_user(काष्ठा vringh *vrh);
व्योम vringh_notअगरy_disable_user(काष्ठा vringh *vrh);

/* Helpers क्रम kernelspace vrings. */
पूर्णांक vringh_init_kern(काष्ठा vringh *vrh, u64 features,
		     अचिन्हित पूर्णांक num, bool weak_barriers,
		     काष्ठा vring_desc *desc,
		     काष्ठा vring_avail *avail,
		     काष्ठा vring_used *used);

अटल अंतरभूत व्योम vringh_kiov_init(काष्ठा vringh_kiov *kiov,
				    काष्ठा kvec *kvec, अचिन्हित num)
अणु
	kiov->used = kiov->i = 0;
	kiov->consumed = 0;
	kiov->max_num = num;
	kiov->iov = kvec;
पूर्ण

अटल अंतरभूत व्योम vringh_kiov_reset(काष्ठा vringh_kiov *kiov)
अणु
	kiov->iov[kiov->i].iov_len += kiov->consumed;
	kiov->iov[kiov->i].iov_base -= kiov->consumed;
	kiov->consumed = 0;
	kiov->i = 0;
पूर्ण

अटल अंतरभूत व्योम vringh_kiov_cleanup(काष्ठा vringh_kiov *kiov)
अणु
	अगर (kiov->max_num & VRINGH_IOV_ALLOCATED)
		kमुक्त(kiov->iov);
	kiov->max_num = kiov->used = kiov->i = kiov->consumed = 0;
	kiov->iov = शून्य;
पूर्ण

अटल अंतरभूत माप_प्रकार vringh_kiov_length(काष्ठा vringh_kiov *kiov)
अणु
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = kiov->i; i < kiov->used; i++)
		len += kiov->iov[i].iov_len;

	वापस len;
पूर्ण

व्योम vringh_kiov_advance(काष्ठा vringh_kiov *kiov, माप_प्रकार len);

पूर्णांक vringh_getdesc_kern(काष्ठा vringh *vrh,
			काष्ठा vringh_kiov *riov,
			काष्ठा vringh_kiov *wiov,
			u16 *head,
			gfp_t gfp);

sमाप_प्रकार vringh_iov_pull_kern(काष्ठा vringh_kiov *riov, व्योम *dst, माप_प्रकार len);
sमाप_प्रकार vringh_iov_push_kern(काष्ठा vringh_kiov *wiov,
			     स्थिर व्योम *src, माप_प्रकार len);
व्योम vringh_abanकरोn_kern(काष्ठा vringh *vrh, अचिन्हित पूर्णांक num);
पूर्णांक vringh_complete_kern(काष्ठा vringh *vrh, u16 head, u32 len);

bool vringh_notअगरy_enable_kern(काष्ठा vringh *vrh);
व्योम vringh_notअगरy_disable_kern(काष्ठा vringh *vrh);

पूर्णांक vringh_need_notअगरy_kern(काष्ठा vringh *vrh);

/* Notअगरy the guest about buffers added to the used ring */
अटल अंतरभूत व्योम vringh_notअगरy(काष्ठा vringh *vrh)
अणु
	अगर (vrh->notअगरy)
		vrh->notअगरy(vrh);
पूर्ण

अटल अंतरभूत bool vringh_is_little_endian(स्थिर काष्ठा vringh *vrh)
अणु
	वापस vrh->little_endian ||
		virtio_legacy_is_little_endian();
पूर्ण

अटल अंतरभूत u16 vringh16_to_cpu(स्थिर काष्ठा vringh *vrh, __virtio16 val)
अणु
	वापस __virtio16_to_cpu(vringh_is_little_endian(vrh), val);
पूर्ण

अटल अंतरभूत __virtio16 cpu_to_vringh16(स्थिर काष्ठा vringh *vrh, u16 val)
अणु
	वापस __cpu_to_virtio16(vringh_is_little_endian(vrh), val);
पूर्ण

अटल अंतरभूत u32 vringh32_to_cpu(स्थिर काष्ठा vringh *vrh, __virtio32 val)
अणु
	वापस __virtio32_to_cpu(vringh_is_little_endian(vrh), val);
पूर्ण

अटल अंतरभूत __virtio32 cpu_to_vringh32(स्थिर काष्ठा vringh *vrh, u32 val)
अणु
	वापस __cpu_to_virtio32(vringh_is_little_endian(vrh), val);
पूर्ण

अटल अंतरभूत u64 vringh64_to_cpu(स्थिर काष्ठा vringh *vrh, __virtio64 val)
अणु
	वापस __virtio64_to_cpu(vringh_is_little_endian(vrh), val);
पूर्ण

अटल अंतरभूत __virtio64 cpu_to_vringh64(स्थिर काष्ठा vringh *vrh, u64 val)
अणु
	वापस __cpu_to_virtio64(vringh_is_little_endian(vrh), val);
पूर्ण

#अगर IS_REACHABLE(CONFIG_VHOST_IOTLB)

व्योम vringh_set_iotlb(काष्ठा vringh *vrh, काष्ठा vhost_iotlb *iotlb,
		      spinlock_t *iotlb_lock);

पूर्णांक vringh_init_iotlb(काष्ठा vringh *vrh, u64 features,
		      अचिन्हित पूर्णांक num, bool weak_barriers,
		      काष्ठा vring_desc *desc,
		      काष्ठा vring_avail *avail,
		      काष्ठा vring_used *used);

पूर्णांक vringh_getdesc_iotlb(काष्ठा vringh *vrh,
			 काष्ठा vringh_kiov *riov,
			 काष्ठा vringh_kiov *wiov,
			 u16 *head,
			 gfp_t gfp);

sमाप_प्रकार vringh_iov_pull_iotlb(काष्ठा vringh *vrh,
			      काष्ठा vringh_kiov *riov,
			      व्योम *dst, माप_प्रकार len);
sमाप_प्रकार vringh_iov_push_iotlb(काष्ठा vringh *vrh,
			      काष्ठा vringh_kiov *wiov,
			      स्थिर व्योम *src, माप_प्रकार len);

व्योम vringh_abanकरोn_iotlb(काष्ठा vringh *vrh, अचिन्हित पूर्णांक num);

पूर्णांक vringh_complete_iotlb(काष्ठा vringh *vrh, u16 head, u32 len);

bool vringh_notअगरy_enable_iotlb(काष्ठा vringh *vrh);
व्योम vringh_notअगरy_disable_iotlb(काष्ठा vringh *vrh);

पूर्णांक vringh_need_notअगरy_iotlb(काष्ठा vringh *vrh);

#पूर्ण_अगर /* CONFIG_VHOST_IOTLB */

#पूर्ण_अगर /* _LINUX_VRINGH_H */
