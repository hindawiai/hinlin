<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sync File validation framework and debug inक्रमmation
 *
 * Copyright (C) 2012 Google, Inc.
 */

#समावेश <linux/debugfs.h>
#समावेश "sync_debug.h"

अटल काष्ठा dentry *dbgfs;

अटल LIST_HEAD(sync_समयline_list_head);
अटल DEFINE_SPINLOCK(sync_समयline_list_lock);
अटल LIST_HEAD(sync_file_list_head);
अटल DEFINE_SPINLOCK(sync_file_list_lock);

व्योम sync_समयline_debug_add(काष्ठा sync_समयline *obj)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sync_समयline_list_lock, flags);
	list_add_tail(&obj->sync_समयline_list, &sync_समयline_list_head);
	spin_unlock_irqrestore(&sync_समयline_list_lock, flags);
पूर्ण

व्योम sync_समयline_debug_हटाओ(काष्ठा sync_समयline *obj)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sync_समयline_list_lock, flags);
	list_del(&obj->sync_समयline_list);
	spin_unlock_irqrestore(&sync_समयline_list_lock, flags);
पूर्ण

व्योम sync_file_debug_add(काष्ठा sync_file *sync_file)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sync_file_list_lock, flags);
	list_add_tail(&sync_file->sync_file_list, &sync_file_list_head);
	spin_unlock_irqrestore(&sync_file_list_lock, flags);
पूर्ण

व्योम sync_file_debug_हटाओ(काष्ठा sync_file *sync_file)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sync_file_list_lock, flags);
	list_del(&sync_file->sync_file_list);
	spin_unlock_irqrestore(&sync_file_list_lock, flags);
पूर्ण

अटल स्थिर अक्षर *sync_status_str(पूर्णांक status)
अणु
	अगर (status < 0)
		वापस "error";

	अगर (status > 0)
		वापस "signaled";

	वापस "active";
पूर्ण

अटल व्योम sync_prपूर्णांक_fence(काष्ठा seq_file *s,
			     काष्ठा dma_fence *fence, bool show)
अणु
	काष्ठा sync_समयline *parent = dma_fence_parent(fence);
	पूर्णांक status;

	status = dma_fence_get_status_locked(fence);

	seq_म_लिखो(s, "  %s%sfence %s",
		   show ? parent->name : "",
		   show ? "_" : "",
		   sync_status_str(status));

	अगर (test_bit(DMA_FENCE_FLAG_TIMESTAMP_BIT, &fence->flags)) अणु
		काष्ठा बारpec64 ts64 =
			kसमय_प्रकारo_बारpec64(fence->बारtamp);

		seq_म_लिखो(s, "@%lld.%09ld", (s64)ts64.tv_sec, ts64.tv_nsec);
	पूर्ण

	अगर (fence->ops->समयline_value_str &&
		fence->ops->fence_value_str) अणु
		अक्षर value[64];
		bool success;

		fence->ops->fence_value_str(fence, value, माप(value));
		success = म_माप(value);

		अगर (success) अणु
			seq_म_लिखो(s, ": %s", value);

			fence->ops->समयline_value_str(fence, value,
						       माप(value));

			अगर (म_माप(value))
				seq_म_लिखो(s, " / %s", value);
		पूर्ण
	पूर्ण

	seq_अ_दो(s, '\n');
पूर्ण

अटल व्योम sync_prपूर्णांक_obj(काष्ठा seq_file *s, काष्ठा sync_समयline *obj)
अणु
	काष्ठा list_head *pos;

	seq_म_लिखो(s, "%s: %d\n", obj->name, obj->value);

	spin_lock_irq(&obj->lock);
	list_क्रम_each(pos, &obj->pt_list) अणु
		काष्ठा sync_pt *pt = container_of(pos, काष्ठा sync_pt, link);
		sync_prपूर्णांक_fence(s, &pt->base, false);
	पूर्ण
	spin_unlock_irq(&obj->lock);
पूर्ण

अटल व्योम sync_prपूर्णांक_sync_file(काष्ठा seq_file *s,
				  काष्ठा sync_file *sync_file)
अणु
	अक्षर buf[128];
	पूर्णांक i;

	seq_म_लिखो(s, "[%p] %s: %s\n", sync_file,
		   sync_file_get_name(sync_file, buf, माप(buf)),
		   sync_status_str(dma_fence_get_status(sync_file->fence)));

	अगर (dma_fence_is_array(sync_file->fence)) अणु
		काष्ठा dma_fence_array *array = to_dma_fence_array(sync_file->fence);

		क्रम (i = 0; i < array->num_fences; ++i)
			sync_prपूर्णांक_fence(s, array->fences[i], true);
	पूर्ण अन्यथा अणु
		sync_prपूर्णांक_fence(s, sync_file->fence, true);
	पूर्ण
पूर्ण

अटल पूर्णांक sync_info_debugfs_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	काष्ठा list_head *pos;

	seq_माला_दो(s, "objs:\n--------------\n");

	spin_lock_irq(&sync_समयline_list_lock);
	list_क्रम_each(pos, &sync_समयline_list_head) अणु
		काष्ठा sync_समयline *obj =
			container_of(pos, काष्ठा sync_समयline,
				     sync_समयline_list);

		sync_prपूर्णांक_obj(s, obj);
		seq_अ_दो(s, '\n');
	पूर्ण
	spin_unlock_irq(&sync_समयline_list_lock);

	seq_माला_दो(s, "fences:\n--------------\n");

	spin_lock_irq(&sync_file_list_lock);
	list_क्रम_each(pos, &sync_file_list_head) अणु
		काष्ठा sync_file *sync_file =
			container_of(pos, काष्ठा sync_file, sync_file_list);

		sync_prपूर्णांक_sync_file(s, sync_file);
		seq_अ_दो(s, '\n');
	पूर्ण
	spin_unlock_irq(&sync_file_list_lock);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(sync_info_debugfs);

अटल __init पूर्णांक sync_debugfs_init(व्योम)
अणु
	dbgfs = debugfs_create_dir("sync", शून्य);

	/*
	 * The debugfs files won't ever get हटाओd and thus, there is
	 * no need to protect it against removal races. The use of
	 * debugfs_create_file_unsafe() is actually safe here.
	 */
	debugfs_create_file_unsafe("info", 0444, dbgfs, शून्य,
				   &sync_info_debugfs_fops);
	debugfs_create_file_unsafe("sw_sync", 0644, dbgfs, शून्य,
				   &sw_sync_debugfs_fops);

	वापस 0;
पूर्ण
late_initcall(sync_debugfs_init);
