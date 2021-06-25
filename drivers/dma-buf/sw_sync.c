<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sync File validation framework
 *
 * Copyright (C) 2012 Google, Inc.
 */

#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/sync_file.h>

#समावेश "sync_debug.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "sync_trace.h"

/*
 * SW SYNC validation framework
 *
 * A sync object driver that uses a 32bit counter to coordinate
 * synchronization.  Useful when there is no hardware primitive backing
 * the synchronization.
 *
 * To start the framework just खोलो:
 *
 * <debugfs>/sync/sw_sync
 *
 * That will create a sync समयline, all fences created under this समयline
 * file descriptor will beदीर्घ to the this समयline.
 *
 * The 'sw_sync' file can be खोलोed many बार as to create dअगरferent
 * समयlines.
 *
 * Fences can be created with SW_SYNC_IOC_CREATE_FENCE ioctl with काष्ठा
 * sw_sync_create_fence_data as parameter.
 *
 * To increment the समयline counter, SW_SYNC_IOC_INC ioctl should be used
 * with the increment as u32. This will update the last संकेतed value
 * from the समयline and संकेत any fence that has a seqno smaller or equal
 * to it.
 *
 * काष्ठा sw_sync_create_fence_data
 * @value:	the seqno to initialise the fence with
 * @name:	the name of the new sync poपूर्णांक
 * @fence:	वापस the fd of the new sync_file with the created fence
 */
काष्ठा sw_sync_create_fence_data अणु
	__u32	value;
	अक्षर	name[32];
	__s32	fence; /* fd of new fence */
पूर्ण;

#घोषणा SW_SYNC_IOC_MAGIC	'W'

#घोषणा SW_SYNC_IOC_CREATE_FENCE	_IOWR(SW_SYNC_IOC_MAGIC, 0,\
		काष्ठा sw_sync_create_fence_data)

#घोषणा SW_SYNC_IOC_INC			_IOW(SW_SYNC_IOC_MAGIC, 1, __u32)

अटल स्थिर काष्ठा dma_fence_ops समयline_fence_ops;

अटल अंतरभूत काष्ठा sync_pt *dma_fence_to_sync_pt(काष्ठा dma_fence *fence)
अणु
	अगर (fence->ops != &समयline_fence_ops)
		वापस शून्य;
	वापस container_of(fence, काष्ठा sync_pt, base);
पूर्ण

/**
 * sync_समयline_create() - creates a sync object
 * @name:	sync_समयline name
 *
 * Creates a new sync_समयline. Returns the sync_समयline object or शून्य in
 * हाल of error.
 */
अटल काष्ठा sync_समयline *sync_समयline_create(स्थिर अक्षर *name)
अणु
	काष्ठा sync_समयline *obj;

	obj = kzalloc(माप(*obj), GFP_KERNEL);
	अगर (!obj)
		वापस शून्य;

	kref_init(&obj->kref);
	obj->context = dma_fence_context_alloc(1);
	strlcpy(obj->name, name, माप(obj->name));

	obj->pt_tree = RB_ROOT;
	INIT_LIST_HEAD(&obj->pt_list);
	spin_lock_init(&obj->lock);

	sync_समयline_debug_add(obj);

	वापस obj;
पूर्ण

अटल व्योम sync_समयline_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा sync_समयline *obj =
		container_of(kref, काष्ठा sync_समयline, kref);

	sync_समयline_debug_हटाओ(obj);

	kमुक्त(obj);
पूर्ण

अटल व्योम sync_समयline_get(काष्ठा sync_समयline *obj)
अणु
	kref_get(&obj->kref);
पूर्ण

अटल व्योम sync_समयline_put(काष्ठा sync_समयline *obj)
अणु
	kref_put(&obj->kref, sync_समयline_मुक्त);
पूर्ण

अटल स्थिर अक्षर *समयline_fence_get_driver_name(काष्ठा dma_fence *fence)
अणु
	वापस "sw_sync";
पूर्ण

अटल स्थिर अक्षर *समयline_fence_get_समयline_name(काष्ठा dma_fence *fence)
अणु
	काष्ठा sync_समयline *parent = dma_fence_parent(fence);

	वापस parent->name;
पूर्ण

अटल व्योम समयline_fence_release(काष्ठा dma_fence *fence)
अणु
	काष्ठा sync_pt *pt = dma_fence_to_sync_pt(fence);
	काष्ठा sync_समयline *parent = dma_fence_parent(fence);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(fence->lock, flags);
	अगर (!list_empty(&pt->link)) अणु
		list_del(&pt->link);
		rb_erase(&pt->node, &parent->pt_tree);
	पूर्ण
	spin_unlock_irqrestore(fence->lock, flags);

	sync_समयline_put(parent);
	dma_fence_मुक्त(fence);
पूर्ण

अटल bool समयline_fence_संकेतed(काष्ठा dma_fence *fence)
अणु
	काष्ठा sync_समयline *parent = dma_fence_parent(fence);

	वापस !__dma_fence_is_later(fence->seqno, parent->value, fence->ops);
पूर्ण

अटल bool समयline_fence_enable_संकेतing(काष्ठा dma_fence *fence)
अणु
	वापस true;
पूर्ण

अटल व्योम समयline_fence_value_str(काष्ठा dma_fence *fence,
				    अक्षर *str, पूर्णांक size)
अणु
	snम_लिखो(str, size, "%lld", fence->seqno);
पूर्ण

अटल व्योम समयline_fence_समयline_value_str(काष्ठा dma_fence *fence,
					     अक्षर *str, पूर्णांक size)
अणु
	काष्ठा sync_समयline *parent = dma_fence_parent(fence);

	snम_लिखो(str, size, "%d", parent->value);
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops समयline_fence_ops = अणु
	.get_driver_name = समयline_fence_get_driver_name,
	.get_समयline_name = समयline_fence_get_समयline_name,
	.enable_संकेतing = समयline_fence_enable_संकेतing,
	.संकेतed = समयline_fence_संकेतed,
	.release = समयline_fence_release,
	.fence_value_str = समयline_fence_value_str,
	.समयline_value_str = समयline_fence_समयline_value_str,
पूर्ण;

/**
 * sync_समयline_संकेत() - संकेत a status change on a sync_समयline
 * @obj:	sync_समयline to संकेत
 * @inc:	num to increment on समयline->value
 *
 * A sync implementation should call this any समय one of it's fences
 * has संकेतed or has an error condition.
 */
अटल व्योम sync_समयline_संकेत(काष्ठा sync_समयline *obj, अचिन्हित पूर्णांक inc)
अणु
	काष्ठा sync_pt *pt, *next;

	trace_sync_समयline(obj);

	spin_lock_irq(&obj->lock);

	obj->value += inc;

	list_क्रम_each_entry_safe(pt, next, &obj->pt_list, link) अणु
		अगर (!समयline_fence_संकेतed(&pt->base))
			अवरोध;

		list_del_init(&pt->link);
		rb_erase(&pt->node, &obj->pt_tree);

		/*
		 * A संकेत callback may release the last reference to this
		 * fence, causing it to be मुक्तd. That operation has to be
		 * last to aव्योम a use after मुक्त inside this loop, and must
		 * be after we हटाओ the fence from the समयline in order to
		 * prevent deadlocking on समयline->lock inside
		 * समयline_fence_release().
		 */
		dma_fence_संकेत_locked(&pt->base);
	पूर्ण

	spin_unlock_irq(&obj->lock);
पूर्ण

/**
 * sync_pt_create() - creates a sync pt
 * @obj:	parent sync_समयline
 * @value:	value of the fence
 *
 * Creates a new sync_pt (fence) as a child of @parent.  @size bytes will be
 * allocated allowing क्रम implementation specअगरic data to be kept after
 * the generic sync_समयline काष्ठा. Returns the sync_pt object or
 * शून्य in हाल of error.
 */
अटल काष्ठा sync_pt *sync_pt_create(काष्ठा sync_समयline *obj,
				      अचिन्हित पूर्णांक value)
अणु
	काष्ठा sync_pt *pt;

	pt = kzalloc(माप(*pt), GFP_KERNEL);
	अगर (!pt)
		वापस शून्य;

	sync_समयline_get(obj);
	dma_fence_init(&pt->base, &समयline_fence_ops, &obj->lock,
		       obj->context, value);
	INIT_LIST_HEAD(&pt->link);

	spin_lock_irq(&obj->lock);
	अगर (!dma_fence_is_संकेतed_locked(&pt->base)) अणु
		काष्ठा rb_node **p = &obj->pt_tree.rb_node;
		काष्ठा rb_node *parent = शून्य;

		जबतक (*p) अणु
			काष्ठा sync_pt *other;
			पूर्णांक cmp;

			parent = *p;
			other = rb_entry(parent, typeof(*pt), node);
			cmp = value - other->base.seqno;
			अगर (cmp > 0) अणु
				p = &parent->rb_right;
			पूर्ण अन्यथा अगर (cmp < 0) अणु
				p = &parent->rb_left;
			पूर्ण अन्यथा अणु
				अगर (dma_fence_get_rcu(&other->base)) अणु
					sync_समयline_put(obj);
					kमुक्त(pt);
					pt = other;
					जाओ unlock;
				पूर्ण
				p = &parent->rb_left;
			पूर्ण
		पूर्ण
		rb_link_node(&pt->node, parent, p);
		rb_insert_color(&pt->node, &obj->pt_tree);

		parent = rb_next(&pt->node);
		list_add_tail(&pt->link,
			      parent ? &rb_entry(parent, typeof(*pt), node)->link : &obj->pt_list);
	पूर्ण
unlock:
	spin_unlock_irq(&obj->lock);

	वापस pt;
पूर्ण

/*
 * *WARNING*
 *
 * improper use of this can result in deadlocking kernel drivers from userspace.
 */

/* खोलोing sw_sync create a new sync obj */
अटल पूर्णांक sw_sync_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sync_समयline *obj;
	अक्षर task_comm[TASK_COMM_LEN];

	get_task_comm(task_comm, current);

	obj = sync_समयline_create(task_comm);
	अगर (!obj)
		वापस -ENOMEM;

	file->निजी_data = obj;

	वापस 0;
पूर्ण

अटल पूर्णांक sw_sync_debugfs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sync_समयline *obj = file->निजी_data;
	काष्ठा sync_pt *pt, *next;

	spin_lock_irq(&obj->lock);

	list_क्रम_each_entry_safe(pt, next, &obj->pt_list, link) अणु
		dma_fence_set_error(&pt->base, -ENOENT);
		dma_fence_संकेत_locked(&pt->base);
	पूर्ण

	spin_unlock_irq(&obj->lock);

	sync_समयline_put(obj);
	वापस 0;
पूर्ण

अटल दीर्घ sw_sync_ioctl_create_fence(काष्ठा sync_समयline *obj,
				       अचिन्हित दीर्घ arg)
अणु
	पूर्णांक fd = get_unused_fd_flags(O_CLOEXEC);
	पूर्णांक err;
	काष्ठा sync_pt *pt;
	काष्ठा sync_file *sync_file;
	काष्ठा sw_sync_create_fence_data data;

	अगर (fd < 0)
		वापस fd;

	अगर (copy_from_user(&data, (व्योम __user *)arg, माप(data))) अणु
		err = -EFAULT;
		जाओ err;
	पूर्ण

	pt = sync_pt_create(obj, data.value);
	अगर (!pt) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	sync_file = sync_file_create(&pt->base);
	dma_fence_put(&pt->base);
	अगर (!sync_file) अणु
		err = -ENOMEM;
		जाओ err;
	पूर्ण

	data.fence = fd;
	अगर (copy_to_user((व्योम __user *)arg, &data, माप(data))) अणु
		fput(sync_file->file);
		err = -EFAULT;
		जाओ err;
	पूर्ण

	fd_install(fd, sync_file->file);

	वापस 0;

err:
	put_unused_fd(fd);
	वापस err;
पूर्ण

अटल दीर्घ sw_sync_ioctl_inc(काष्ठा sync_समयline *obj, अचिन्हित दीर्घ arg)
अणु
	u32 value;

	अगर (copy_from_user(&value, (व्योम __user *)arg, माप(value)))
		वापस -EFAULT;

	जबतक (value > पूर्णांक_उच्च)  अणु
		sync_समयline_संकेत(obj, पूर्णांक_उच्च);
		value -= पूर्णांक_उच्च;
	पूर्ण

	sync_समयline_संकेत(obj, value);

	वापस 0;
पूर्ण

अटल दीर्घ sw_sync_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा sync_समयline *obj = file->निजी_data;

	चयन (cmd) अणु
	हाल SW_SYNC_IOC_CREATE_FENCE:
		वापस sw_sync_ioctl_create_fence(obj, arg);

	हाल SW_SYNC_IOC_INC:
		वापस sw_sync_ioctl_inc(obj, arg);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

स्थिर काष्ठा file_operations sw_sync_debugfs_fops = अणु
	.खोलो           = sw_sync_debugfs_खोलो,
	.release        = sw_sync_debugfs_release,
	.unlocked_ioctl = sw_sync_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;
