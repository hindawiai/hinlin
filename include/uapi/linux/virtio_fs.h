<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */

#अगर_अघोषित _UAPI_LINUX_VIRTIO_FS_H
#घोषणा _UAPI_LINUX_VIRTIO_FS_H

#समावेश <linux/types.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_types.h>

काष्ठा virtio_fs_config अणु
	/* Fileप्रणाली name (UTF-8, not NUL-terminated, padded with NULs) */
	__u8 tag[36];

	/* Number of request queues */
	__le32 num_request_queues;
पूर्ण __attribute__((packed));

/* For the id field in virtio_pci_shm_cap */
#घोषणा VIRTIO_FS_SHMCAP_ID_CACHE 0

#पूर्ण_अगर /* _UAPI_LINUX_VIRTIO_FS_H */
