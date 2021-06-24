<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 * Copyright (C) 2014 Fujitsu.  All rights reserved.
 */

#अगर_अघोषित BTRFS_ASYNC_THREAD_H
#घोषणा BTRFS_ASYNC_THREAD_H

#समावेश <linux/workqueue.h>

काष्ठा btrfs_fs_info;
काष्ठा btrfs_workqueue;
/* Internal use only */
काष्ठा __btrfs_workqueue;
काष्ठा btrfs_work;
प्रकार व्योम (*btrfs_func_t)(काष्ठा btrfs_work *arg);
प्रकार व्योम (*btrfs_work_func_t)(काष्ठा work_काष्ठा *arg);

काष्ठा btrfs_work अणु
	btrfs_func_t func;
	btrfs_func_t ordered_func;
	btrfs_func_t ordered_मुक्त;

	/* Don't touch things below */
	काष्ठा work_काष्ठा normal_work;
	काष्ठा list_head ordered_list;
	काष्ठा __btrfs_workqueue *wq;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा btrfs_workqueue *btrfs_alloc_workqueue(काष्ठा btrfs_fs_info *fs_info,
					      स्थिर अक्षर *name,
					      अचिन्हित पूर्णांक flags,
					      पूर्णांक limit_active,
					      पूर्णांक thresh);
व्योम btrfs_init_work(काष्ठा btrfs_work *work, btrfs_func_t func,
		     btrfs_func_t ordered_func, btrfs_func_t ordered_मुक्त);
व्योम btrfs_queue_work(काष्ठा btrfs_workqueue *wq,
		      काष्ठा btrfs_work *work);
व्योम btrfs_destroy_workqueue(काष्ठा btrfs_workqueue *wq);
व्योम btrfs_workqueue_set_max(काष्ठा btrfs_workqueue *wq, पूर्णांक max);
व्योम btrfs_set_work_high_priority(काष्ठा btrfs_work *work);
काष्ठा btrfs_fs_info * __pure btrfs_work_owner(स्थिर काष्ठा btrfs_work *work);
काष्ठा btrfs_fs_info * __pure btrfs_workqueue_owner(स्थिर काष्ठा __btrfs_workqueue *wq);
bool btrfs_workqueue_normal_congested(स्थिर काष्ठा btrfs_workqueue *wq);
व्योम btrfs_flush_workqueue(काष्ठा btrfs_workqueue *wq);

#पूर्ण_अगर
