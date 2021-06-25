<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause */
/*
 * Definitions क्रम virtio-pmem devices.
 *
 * Copyright (C) 2019 Red Hat, Inc.
 *
 * Author(s): Pankaj Gupta <pagupta@redhat.com>
 */

#अगर_अघोषित _UAPI_LINUX_VIRTIO_PMEM_H
#घोषणा _UAPI_LINUX_VIRTIO_PMEM_H

#समावेश <linux/types.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>

काष्ठा virtio_pmem_config अणु
	__le64 start;
	__le64 size;
पूर्ण;

#घोषणा VIRTIO_PMEM_REQ_TYPE_FLUSH      0

काष्ठा virtio_pmem_resp अणु
	/* Host वापस status corresponding to flush request */
	__le32 ret;
पूर्ण;

काष्ठा virtio_pmem_req अणु
	/* command type */
	__le32 type;
पूर्ण;

#पूर्ण_अगर
