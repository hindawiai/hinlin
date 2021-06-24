<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 Google, Inc.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित _UAPI_LINUX_SYNC_H
#घोषणा _UAPI_LINUX_SYNC_H

#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

/**
 * काष्ठा sync_merge_data - data passed to merge ioctl
 * @name:	name of new fence
 * @fd2:	file descriptor of second fence
 * @fence:	वापसs the fd of the new fence to userspace
 * @flags:	merge_data flags
 * @pad:	padding क्रम 64-bit alignment, should always be zero
 */
काष्ठा sync_merge_data अणु
	अक्षर	name[32];
	__s32	fd2;
	__s32	fence;
	__u32	flags;
	__u32	pad;
पूर्ण;

/**
 * काष्ठा sync_fence_info - detailed fence inक्रमmation
 * @obj_name:		name of parent sync_समयline
* @driver_name:	name of driver implementing the parent
* @status:		status of the fence 0:active 1:संकेतed <0:error
 * @flags:		fence_info flags
 * @बारtamp_ns:	बारtamp of status change in nanoseconds
 */
काष्ठा sync_fence_info अणु
	अक्षर	obj_name[32];
	अक्षर	driver_name[32];
	__s32	status;
	__u32	flags;
	__u64	बारtamp_ns;
पूर्ण;

/**
 * काष्ठा sync_file_info - data वापसed from fence info ioctl
 * @name:	name of fence
 * @status:	status of fence. 1: संकेतed 0:active <0:error
 * @flags:	sync_file_info flags
 * @num_fences	number of fences in the sync_file
 * @pad:	padding क्रम 64-bit alignment, should always be zero
 * @sync_fence_info: poपूर्णांकer to array of काष्ठाs sync_fence_info with all
 *		 fences in the sync_file
 */
काष्ठा sync_file_info अणु
	अक्षर	name[32];
	__s32	status;
	__u32	flags;
	__u32	num_fences;
	__u32	pad;

	__u64	sync_fence_info;
पूर्ण;

#घोषणा SYNC_IOC_MAGIC		'>'

/**
 * Opcodes  0, 1 and 2 were burned during a API change to aव्योम users of the
 * old API to get weird errors when trying to handling sync_files. The API
 * change happened during the de-stage of the Sync Framework when there was
 * no upstream users available.
 */

/**
 * DOC: SYNC_IOC_MERGE - merge two fences
 *
 * Takes a काष्ठा sync_merge_data.  Creates a new fence containing copies of
 * the sync_pts in both the calling fd and sync_merge_data.fd2.  Returns the
 * new fence's fd in sync_merge_data.fence
 */
#घोषणा SYNC_IOC_MERGE		_IOWR(SYNC_IOC_MAGIC, 3, काष्ठा sync_merge_data)

/**
 * DOC: SYNC_IOC_खाता_INFO - get detailed inक्रमmation on a sync_file
 *
 * Takes a काष्ठा sync_file_info. If num_fences is 0, the field is updated
 * with the actual number of fences. If num_fences is > 0, the प्रणाली will
 * use the poपूर्णांकer provided on sync_fence_info to वापस up to num_fences of
 * काष्ठा sync_fence_info, with detailed fence inक्रमmation.
 */
#घोषणा SYNC_IOC_खाता_INFO	_IOWR(SYNC_IOC_MAGIC, 4, काष्ठा sync_file_info)

#पूर्ण_अगर /* _UAPI_LINUX_SYNC_H */
