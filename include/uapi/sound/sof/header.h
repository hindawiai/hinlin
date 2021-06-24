<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Copyright(c) 2018 Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __INCLUDE_UAPI_SOUND_SOF_USER_HEADER_H__
#घोषणा __INCLUDE_UAPI_SOUND_SOF_USER_HEADER_H__

#समावेश <linux/types.h>

/*
 * Header क्रम all non IPC ABI data.
 *
 * Identअगरies data type, size and ABI.
 * Used by any bespoke component data काष्ठाures or binary blobs.
 */
काष्ठा sof_abi_hdr अणु
	__u32 magic;		/**< 'S', 'O', 'F', '\0' */
	__u32 type;		/**< component specअगरic type */
	__u32 size;		/**< size in bytes of data excl. this काष्ठा */
	__u32 abi;		/**< SOF ABI version */
	__u32 reserved[4];	/**< reserved क्रम future use */
	__u32 data[0];		/**< Component data - opaque to core */
पूर्ण  __packed;

#पूर्ण_अगर
