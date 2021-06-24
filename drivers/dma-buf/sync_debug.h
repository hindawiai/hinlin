<शैली गुरु>
/*
 * Sync File validation framework and debug infomation
 *
 * Copyright (C) 2012 Google, Inc.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 */

#अगर_अघोषित _LINUX_SYNC_H
#घोषणा _LINUX_SYNC_H

#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-fence.h>

#समावेश <linux/sync_file.h>
#समावेश <uapi/linux/sync_file.h>

/**
 * काष्ठा sync_समयline - sync object
 * @kref:		reference count on fence.
 * @name:		name of the sync_समयline. Useful क्रम debugging
 * @lock:		lock protecting @pt_list and @value
 * @pt_tree:		rbtree of active (unसंकेतed/errored) sync_pts
 * @pt_list:		list of active (unसंकेतed/errored) sync_pts
 * @sync_समयline_list:	membership in global sync_समयline_list
 */
काष्ठा sync_समयline अणु
	काष्ठा kref		kref;
	अक्षर			name[32];

	/* रक्षित by lock */
	u64			context;
	पूर्णांक			value;

	काष्ठा rb_root		pt_tree;
	काष्ठा list_head	pt_list;
	spinlock_t		lock;

	काष्ठा list_head	sync_समयline_list;
पूर्ण;

अटल अंतरभूत काष्ठा sync_समयline *dma_fence_parent(काष्ठा dma_fence *fence)
अणु
	वापस container_of(fence->lock, काष्ठा sync_समयline, lock);
पूर्ण

/**
 * काष्ठा sync_pt - sync_pt object
 * @base: base fence object
 * @link: link on the sync समयline's list
 * @node: node in the sync समयline's tree
 */
काष्ठा sync_pt अणु
	काष्ठा dma_fence base;
	काष्ठा list_head link;
	काष्ठा rb_node node;
पूर्ण;

बाह्य स्थिर काष्ठा file_operations sw_sync_debugfs_fops;

व्योम sync_समयline_debug_add(काष्ठा sync_समयline *obj);
व्योम sync_समयline_debug_हटाओ(काष्ठा sync_समयline *obj);
व्योम sync_file_debug_add(काष्ठा sync_file *fence);
व्योम sync_file_debug_हटाओ(काष्ठा sync_file *fence);

#पूर्ण_अगर /* _LINUX_SYNC_H */
