<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/dma-buf/sync_file.c
 *
 * Copyright (C) 2012 Google, Inc.
 */

#समावेश <linux/export.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/sync_file.h>
#समावेश <uapi/linux/sync_file.h>

अटल स्थिर काष्ठा file_operations sync_file_fops;

अटल काष्ठा sync_file *sync_file_alloc(व्योम)
अणु
	काष्ठा sync_file *sync_file;

	sync_file = kzalloc(माप(*sync_file), GFP_KERNEL);
	अगर (!sync_file)
		वापस शून्य;

	sync_file->file = anon_inode_getfile("sync_file", &sync_file_fops,
					     sync_file, 0);
	अगर (IS_ERR(sync_file->file))
		जाओ err;

	init_रुकोqueue_head(&sync_file->wq);

	INIT_LIST_HEAD(&sync_file->cb.node);

	वापस sync_file;

err:
	kमुक्त(sync_file);
	वापस शून्य;
पूर्ण

अटल व्योम fence_check_cb_func(काष्ठा dma_fence *f, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा sync_file *sync_file;

	sync_file = container_of(cb, काष्ठा sync_file, cb);

	wake_up_all(&sync_file->wq);
पूर्ण

/**
 * sync_file_create() - creates a sync file
 * @fence:	fence to add to the sync_fence
 *
 * Creates a sync_file containg @fence. This function acquires and additional
 * reference of @fence क्रम the newly-created &sync_file, अगर it succeeds. The
 * sync_file can be released with fput(sync_file->file). Returns the
 * sync_file or शून्य in हाल of error.
 */
काष्ठा sync_file *sync_file_create(काष्ठा dma_fence *fence)
अणु
	काष्ठा sync_file *sync_file;

	sync_file = sync_file_alloc();
	अगर (!sync_file)
		वापस शून्य;

	sync_file->fence = dma_fence_get(fence);

	वापस sync_file;
पूर्ण
EXPORT_SYMBOL(sync_file_create);

अटल काष्ठा sync_file *sync_file_fdget(पूर्णांक fd)
अणु
	काष्ठा file *file = fget(fd);

	अगर (!file)
		वापस शून्य;

	अगर (file->f_op != &sync_file_fops)
		जाओ err;

	वापस file->निजी_data;

err:
	fput(file);
	वापस शून्य;
पूर्ण

/**
 * sync_file_get_fence - get the fence related to the sync_file fd
 * @fd:		sync_file fd to get the fence from
 *
 * Ensures @fd references a valid sync_file and वापसs a fence that
 * represents all fence in the sync_file. On error शून्य is वापसed.
 */
काष्ठा dma_fence *sync_file_get_fence(पूर्णांक fd)
अणु
	काष्ठा sync_file *sync_file;
	काष्ठा dma_fence *fence;

	sync_file = sync_file_fdget(fd);
	अगर (!sync_file)
		वापस शून्य;

	fence = dma_fence_get(sync_file->fence);
	fput(sync_file->file);

	वापस fence;
पूर्ण
EXPORT_SYMBOL(sync_file_get_fence);

/**
 * sync_file_get_name - get the name of the sync_file
 * @sync_file:		sync_file to get the fence from
 * @buf:		destination buffer to copy sync_file name पूर्णांकo
 * @len:		available size of destination buffer.
 *
 * Each sync_file may have a name asचिन्हित either by the user (when merging
 * sync_files together) or created from the fence it contains. In the latter
 * हाल स्थिरruction of the name is deferred until use, and so requires
 * sync_file_get_name().
 *
 * Returns: a string representing the name.
 */
अक्षर *sync_file_get_name(काष्ठा sync_file *sync_file, अक्षर *buf, पूर्णांक len)
अणु
	अगर (sync_file->user_name[0]) अणु
		strlcpy(buf, sync_file->user_name, len);
	पूर्ण अन्यथा अणु
		काष्ठा dma_fence *fence = sync_file->fence;

		snम_लिखो(buf, len, "%s-%s%llu-%lld",
			 fence->ops->get_driver_name(fence),
			 fence->ops->get_समयline_name(fence),
			 fence->context,
			 fence->seqno);
	पूर्ण

	वापस buf;
पूर्ण

अटल पूर्णांक sync_file_set_fence(काष्ठा sync_file *sync_file,
			       काष्ठा dma_fence **fences, पूर्णांक num_fences)
अणु
	काष्ठा dma_fence_array *array;

	/*
	 * The reference क्रम the fences in the new sync_file and held
	 * in add_fence() during the merge procedure, so क्रम num_fences == 1
	 * we alपढ़ोy own a new reference to the fence. For num_fence > 1
	 * we own the reference of the dma_fence_array creation.
	 */
	अगर (num_fences == 1) अणु
		sync_file->fence = fences[0];
		kमुक्त(fences);
	पूर्ण अन्यथा अणु
		array = dma_fence_array_create(num_fences, fences,
					       dma_fence_context_alloc(1),
					       1, false);
		अगर (!array)
			वापस -ENOMEM;

		sync_file->fence = &array->base;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dma_fence **get_fences(काष्ठा sync_file *sync_file,
				     पूर्णांक *num_fences)
अणु
	अगर (dma_fence_is_array(sync_file->fence)) अणु
		काष्ठा dma_fence_array *array = to_dma_fence_array(sync_file->fence);

		*num_fences = array->num_fences;
		वापस array->fences;
	पूर्ण

	*num_fences = 1;
	वापस &sync_file->fence;
पूर्ण

अटल व्योम add_fence(काष्ठा dma_fence **fences,
		      पूर्णांक *i, काष्ठा dma_fence *fence)
अणु
	fences[*i] = fence;

	अगर (!dma_fence_is_संकेतed(fence)) अणु
		dma_fence_get(fence);
		(*i)++;
	पूर्ण
पूर्ण

/**
 * sync_file_merge() - merge two sync_files
 * @name:	name of new fence
 * @a:		sync_file a
 * @b:		sync_file b
 *
 * Creates a new sync_file which contains copies of all the fences in both
 * @a and @b.  @a and @b reमुख्य valid, independent sync_file. Returns the
 * new merged sync_file or शून्य in हाल of error.
 */
अटल काष्ठा sync_file *sync_file_merge(स्थिर अक्षर *name, काष्ठा sync_file *a,
					 काष्ठा sync_file *b)
अणु
	काष्ठा sync_file *sync_file;
	काष्ठा dma_fence **fences, **nfences, **a_fences, **b_fences;
	पूर्णांक i, i_a, i_b, num_fences, a_num_fences, b_num_fences;

	sync_file = sync_file_alloc();
	अगर (!sync_file)
		वापस शून्य;

	a_fences = get_fences(a, &a_num_fences);
	b_fences = get_fences(b, &b_num_fences);
	अगर (a_num_fences > पूर्णांक_उच्च - b_num_fences)
		जाओ err;

	num_fences = a_num_fences + b_num_fences;

	fences = kसुस्मृति(num_fences, माप(*fences), GFP_KERNEL);
	अगर (!fences)
		जाओ err;

	/*
	 * Assume sync_file a and b are both ordered and have no
	 * duplicates with the same context.
	 *
	 * If a sync_file can only be created with sync_file_merge
	 * and sync_file_create, this is a reasonable assumption.
	 */
	क्रम (i = i_a = i_b = 0; i_a < a_num_fences && i_b < b_num_fences; ) अणु
		काष्ठा dma_fence *pt_a = a_fences[i_a];
		काष्ठा dma_fence *pt_b = b_fences[i_b];

		अगर (pt_a->context < pt_b->context) अणु
			add_fence(fences, &i, pt_a);

			i_a++;
		पूर्ण अन्यथा अगर (pt_a->context > pt_b->context) अणु
			add_fence(fences, &i, pt_b);

			i_b++;
		पूर्ण अन्यथा अणु
			अगर (__dma_fence_is_later(pt_a->seqno, pt_b->seqno,
						 pt_a->ops))
				add_fence(fences, &i, pt_a);
			अन्यथा
				add_fence(fences, &i, pt_b);

			i_a++;
			i_b++;
		पूर्ण
	पूर्ण

	क्रम (; i_a < a_num_fences; i_a++)
		add_fence(fences, &i, a_fences[i_a]);

	क्रम (; i_b < b_num_fences; i_b++)
		add_fence(fences, &i, b_fences[i_b]);

	अगर (i == 0)
		fences[i++] = dma_fence_get(a_fences[0]);

	अगर (num_fences > i) अणु
		nfences = kपुनः_स्मृति_array(fences, i, माप(*fences), GFP_KERNEL);
		अगर (!nfences)
			जाओ err;

		fences = nfences;
	पूर्ण

	अगर (sync_file_set_fence(sync_file, fences, i) < 0) अणु
		kमुक्त(fences);
		जाओ err;
	पूर्ण

	strlcpy(sync_file->user_name, name, माप(sync_file->user_name));
	वापस sync_file;

err:
	fput(sync_file->file);
	वापस शून्य;

पूर्ण

अटल पूर्णांक sync_file_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sync_file *sync_file = file->निजी_data;

	अगर (test_bit(POLL_ENABLED, &sync_file->flags))
		dma_fence_हटाओ_callback(sync_file->fence, &sync_file->cb);
	dma_fence_put(sync_file->fence);
	kमुक्त(sync_file);

	वापस 0;
पूर्ण

अटल __poll_t sync_file_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा sync_file *sync_file = file->निजी_data;

	poll_रुको(file, &sync_file->wq, रुको);

	अगर (list_empty(&sync_file->cb.node) &&
	    !test_and_set_bit(POLL_ENABLED, &sync_file->flags)) अणु
		अगर (dma_fence_add_callback(sync_file->fence, &sync_file->cb,
					   fence_check_cb_func) < 0)
			wake_up_all(&sync_file->wq);
	पूर्ण

	वापस dma_fence_is_संकेतed(sync_file->fence) ? EPOLLIN : 0;
पूर्ण

अटल दीर्घ sync_file_ioctl_merge(काष्ठा sync_file *sync_file,
				  अचिन्हित दीर्घ arg)
अणु
	पूर्णांक fd = get_unused_fd_flags(O_CLOEXEC);
	पूर्णांक err;
	काष्ठा sync_file *fence2, *fence3;
	काष्ठा sync_merge_data data;

	अगर (fd < 0)
		वापस fd;

	अगर (copy_from_user(&data, (व्योम __user *)arg, माप(data))) अणु
		err = -EFAULT;
		जाओ err_put_fd;
	पूर्ण

	अगर (data.flags || data.pad) अणु
		err = -EINVAL;
		जाओ err_put_fd;
	पूर्ण

	fence2 = sync_file_fdget(data.fd2);
	अगर (!fence2) अणु
		err = -ENOENT;
		जाओ err_put_fd;
	पूर्ण

	data.name[माप(data.name) - 1] = '\0';
	fence3 = sync_file_merge(data.name, sync_file, fence2);
	अगर (!fence3) अणु
		err = -ENOMEM;
		जाओ err_put_fence2;
	पूर्ण

	data.fence = fd;
	अगर (copy_to_user((व्योम __user *)arg, &data, माप(data))) अणु
		err = -EFAULT;
		जाओ err_put_fence3;
	पूर्ण

	fd_install(fd, fence3->file);
	fput(fence2->file);
	वापस 0;

err_put_fence3:
	fput(fence3->file);

err_put_fence2:
	fput(fence2->file);

err_put_fd:
	put_unused_fd(fd);
	वापस err;
पूर्ण

अटल पूर्णांक sync_fill_fence_info(काष्ठा dma_fence *fence,
				 काष्ठा sync_fence_info *info)
अणु
	strlcpy(info->obj_name, fence->ops->get_समयline_name(fence),
		माप(info->obj_name));
	strlcpy(info->driver_name, fence->ops->get_driver_name(fence),
		माप(info->driver_name));

	info->status = dma_fence_get_status(fence);
	जबतक (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags) &&
	       !test_bit(DMA_FENCE_FLAG_TIMESTAMP_BIT, &fence->flags))
		cpu_relax();
	info->बारtamp_ns =
		test_bit(DMA_FENCE_FLAG_TIMESTAMP_BIT, &fence->flags) ?
		kसमय_प्रकारo_ns(fence->बारtamp) :
		kसमय_set(0, 0);

	वापस info->status;
पूर्ण

अटल दीर्घ sync_file_ioctl_fence_info(काष्ठा sync_file *sync_file,
				       अचिन्हित दीर्घ arg)
अणु
	काष्ठा sync_file_info info;
	काष्ठा sync_fence_info *fence_info = शून्य;
	काष्ठा dma_fence **fences;
	__u32 size;
	पूर्णांक num_fences, ret, i;

	अगर (copy_from_user(&info, (व्योम __user *)arg, माप(info)))
		वापस -EFAULT;

	अगर (info.flags || info.pad)
		वापस -EINVAL;

	fences = get_fences(sync_file, &num_fences);

	/*
	 * Passing num_fences = 0 means that userspace करोesn't want to
	 * retrieve any sync_fence_info. If num_fences = 0 we skip filling
	 * sync_fence_info and वापस the actual number of fences on
	 * info->num_fences.
	 */
	अगर (!info.num_fences) अणु
		info.status = dma_fence_get_status(sync_file->fence);
		जाओ no_fences;
	पूर्ण अन्यथा अणु
		info.status = 1;
	पूर्ण

	अगर (info.num_fences < num_fences)
		वापस -EINVAL;

	size = num_fences * माप(*fence_info);
	fence_info = kzalloc(size, GFP_KERNEL);
	अगर (!fence_info)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_fences; i++) अणु
		पूर्णांक status = sync_fill_fence_info(fences[i], &fence_info[i]);
		info.status = info.status <= 0 ? info.status : status;
	पूर्ण

	अगर (copy_to_user(u64_to_user_ptr(info.sync_fence_info), fence_info,
			 size)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

no_fences:
	sync_file_get_name(sync_file, info.name, माप(info.name));
	info.num_fences = num_fences;

	अगर (copy_to_user((व्योम __user *)arg, &info, माप(info)))
		ret = -EFAULT;
	अन्यथा
		ret = 0;

out:
	kमुक्त(fence_info);

	वापस ret;
पूर्ण

अटल दीर्घ sync_file_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा sync_file *sync_file = file->निजी_data;

	चयन (cmd) अणु
	हाल SYNC_IOC_MERGE:
		वापस sync_file_ioctl_merge(sync_file, arg);

	हाल SYNC_IOC_खाता_INFO:
		वापस sync_file_ioctl_fence_info(sync_file, arg);

	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा file_operations sync_file_fops = अणु
	.release = sync_file_release,
	.poll = sync_file_poll,
	.unlocked_ioctl = sync_file_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;
