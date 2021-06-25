<शैली गुरु>
/*
 * include/linux/sync_file.h
 *
 * Copyright (C) 2012 Google, Inc.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित _LINUX_SYNC_खाता_H
#घोषणा _LINUX_SYNC_खाता_H

#समावेश <linux/types.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/dma-fence-array.h>

/**
 * काष्ठा sync_file - sync file to export to the userspace
 * @file:		file representing this fence
 * @sync_file_list:	membership in global file list
 * @wq:			रुको queue क्रम fence संकेतing
 * @flags:		flags क्रम the sync_file
 * @fence:		fence with the fences in the sync_file
 * @cb:			fence callback inक्रमmation
 *
 * flags:
 * POLL_ENABLED: whether userspace is currently poll()'ing or not
 */
काष्ठा sync_file अणु
	काष्ठा file		*file;
	/**
	 * @user_name:
	 *
	 * Name of the sync file provided by userspace, क्रम merged fences.
	 * Otherwise generated through driver callbacks (in which हाल the
	 * entire array is 0).
	 */
	अक्षर			user_name[32];
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा list_head	sync_file_list;
#पूर्ण_अगर

	रुको_queue_head_t	wq;
	अचिन्हित दीर्घ		flags;

	काष्ठा dma_fence	*fence;
	काष्ठा dma_fence_cb cb;
पूर्ण;

#घोषणा POLL_ENABLED 0

काष्ठा sync_file *sync_file_create(काष्ठा dma_fence *fence);
काष्ठा dma_fence *sync_file_get_fence(पूर्णांक fd);
अक्षर *sync_file_get_name(काष्ठा sync_file *sync_file, अक्षर *buf, पूर्णांक len);

#पूर्ण_अगर /* _LINUX_SYNC_H */
