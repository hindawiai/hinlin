<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_UDMABUF_H
#घोषणा _UAPI_LINUX_UDMABUF_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा UDMABUF_FLAGS_CLOEXEC	0x01

काष्ठा udmabuf_create अणु
	__u32 memfd;
	__u32 flags;
	__u64 offset;
	__u64 size;
पूर्ण;

काष्ठा udmabuf_create_item अणु
	__u32 memfd;
	__u32 __pad;
	__u64 offset;
	__u64 size;
पूर्ण;

काष्ठा udmabuf_create_list अणु
	__u32 flags;
	__u32 count;
	काष्ठा udmabuf_create_item list[];
पूर्ण;

#घोषणा UDMABUF_CREATE       _IOW('u', 0x42, काष्ठा udmabuf_create)
#घोषणा UDMABUF_CREATE_LIST  _IOW('u', 0x43, काष्ठा udmabuf_create_list)

#पूर्ण_अगर /* _UAPI_LINUX_UDMABUF_H */
