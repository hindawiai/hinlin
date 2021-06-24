<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Framework क्रम userspace DMA-BUF allocations
 *
 * Copyright (C) 2011 Google, Inc.
 * Copyright (C) 2019 Linaro Ltd.
 */

#समावेश <linux/cdev.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/err.h>
#समावेश <linux/xarray.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/dma-heap.h>
#समावेश <uapi/linux/dma-heap.h>

#घोषणा DEVNAME "dma_heap"

#घोषणा NUM_HEAP_MINORS 128

/**
 * काष्ठा dma_heap - represents a dmabuf heap in the प्रणाली
 * @name:		used क्रम debugging/device-node name
 * @ops:		ops काष्ठा क्रम this heap
 * @heap_devt		heap device node
 * @list		list head connecting to list of heaps
 * @heap_cdev		heap अक्षर device
 *
 * Represents a heap of memory from which buffers can be made.
 */
काष्ठा dma_heap अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा dma_heap_ops *ops;
	व्योम *priv;
	dev_t heap_devt;
	काष्ठा list_head list;
	काष्ठा cdev heap_cdev;
पूर्ण;

अटल LIST_HEAD(heap_list);
अटल DEFINE_MUTEX(heap_list_lock);
अटल dev_t dma_heap_devt;
अटल काष्ठा class *dma_heap_class;
अटल DEFINE_XARRAY_ALLOC(dma_heap_minors);

अटल पूर्णांक dma_heap_buffer_alloc(काष्ठा dma_heap *heap, माप_प्रकार len,
				 अचिन्हित पूर्णांक fd_flags,
				 अचिन्हित पूर्णांक heap_flags)
अणु
	काष्ठा dma_buf *dmabuf;
	पूर्णांक fd;

	/*
	 * Allocations from all heaps have to begin
	 * and end on page boundaries.
	 */
	len = PAGE_ALIGN(len);
	अगर (!len)
		वापस -EINVAL;

	dmabuf = heap->ops->allocate(heap, len, fd_flags, heap_flags);
	अगर (IS_ERR(dmabuf))
		वापस PTR_ERR(dmabuf);

	fd = dma_buf_fd(dmabuf, fd_flags);
	अगर (fd < 0) अणु
		dma_buf_put(dmabuf);
		/* just वापस, as put will call release and that will मुक्त */
	पूर्ण
	वापस fd;
पूर्ण

अटल पूर्णांक dma_heap_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dma_heap *heap;

	heap = xa_load(&dma_heap_minors, iminor(inode));
	अगर (!heap) अणु
		pr_err("dma_heap: minor %d unknown.\n", iminor(inode));
		वापस -ENODEV;
	पूर्ण

	/* instance data as context */
	file->निजी_data = heap;
	nonseekable_खोलो(inode, file);

	वापस 0;
पूर्ण

अटल दीर्घ dma_heap_ioctl_allocate(काष्ठा file *file, व्योम *data)
अणु
	काष्ठा dma_heap_allocation_data *heap_allocation = data;
	काष्ठा dma_heap *heap = file->निजी_data;
	पूर्णांक fd;

	अगर (heap_allocation->fd)
		वापस -EINVAL;

	अगर (heap_allocation->fd_flags & ~DMA_HEAP_VALID_FD_FLAGS)
		वापस -EINVAL;

	अगर (heap_allocation->heap_flags & ~DMA_HEAP_VALID_HEAP_FLAGS)
		वापस -EINVAL;

	fd = dma_heap_buffer_alloc(heap, heap_allocation->len,
				   heap_allocation->fd_flags,
				   heap_allocation->heap_flags);
	अगर (fd < 0)
		वापस fd;

	heap_allocation->fd = fd;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक dma_heap_ioctl_cmds[] = अणु
	DMA_HEAP_IOCTL_ALLOC,
पूर्ण;

अटल दीर्घ dma_heap_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक ucmd,
			   अचिन्हित दीर्घ arg)
अणु
	अक्षर stack_kdata[128];
	अक्षर *kdata = stack_kdata;
	अचिन्हित पूर्णांक kcmd;
	अचिन्हित पूर्णांक in_size, out_size, drv_size, ksize;
	पूर्णांक nr = _IOC_NR(ucmd);
	पूर्णांक ret = 0;

	अगर (nr >= ARRAY_SIZE(dma_heap_ioctl_cmds))
		वापस -EINVAL;

	/* Get the kernel ioctl cmd that matches */
	kcmd = dma_heap_ioctl_cmds[nr];

	/* Figure out the delta between user cmd size and kernel cmd size */
	drv_size = _IOC_SIZE(kcmd);
	out_size = _IOC_SIZE(ucmd);
	in_size = out_size;
	अगर ((ucmd & kcmd & IOC_IN) == 0)
		in_size = 0;
	अगर ((ucmd & kcmd & IOC_OUT) == 0)
		out_size = 0;
	ksize = max(max(in_size, out_size), drv_size);

	/* If necessary, allocate buffer क्रम ioctl argument */
	अगर (ksize > माप(stack_kdata)) अणु
		kdata = kदो_स्मृति(ksize, GFP_KERNEL);
		अगर (!kdata)
			वापस -ENOMEM;
	पूर्ण

	अगर (copy_from_user(kdata, (व्योम __user *)arg, in_size) != 0) अणु
		ret = -EFAULT;
		जाओ err;
	पूर्ण

	/* zero out any dअगरference between the kernel/user काष्ठाure size */
	अगर (ksize > in_size)
		स_रखो(kdata + in_size, 0, ksize - in_size);

	चयन (kcmd) अणु
	हाल DMA_HEAP_IOCTL_ALLOC:
		ret = dma_heap_ioctl_allocate(file, kdata);
		अवरोध;
	शेष:
		ret = -ENOTTY;
		जाओ err;
	पूर्ण

	अगर (copy_to_user((व्योम __user *)arg, kdata, out_size) != 0)
		ret = -EFAULT;
err:
	अगर (kdata != stack_kdata)
		kमुक्त(kdata);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations dma_heap_fops = अणु
	.owner          = THIS_MODULE,
	.खोलो		= dma_heap_खोलो,
	.unlocked_ioctl = dma_heap_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= dma_heap_ioctl,
#पूर्ण_अगर
पूर्ण;

/**
 * dma_heap_get_drvdata() - get per-subdriver data क्रम the heap
 * @heap: DMA-Heap to retrieve निजी data क्रम
 *
 * Returns:
 * The per-subdriver data क्रम the heap.
 */
व्योम *dma_heap_get_drvdata(काष्ठा dma_heap *heap)
अणु
	वापस heap->priv;
पूर्ण

/**
 * dma_heap_get_name() - get heap name
 * @heap: DMA-Heap to retrieve निजी data क्रम
 *
 * Returns:
 * The अक्षर* क्रम the heap name.
 */
स्थिर अक्षर *dma_heap_get_name(काष्ठा dma_heap *heap)
अणु
	वापस heap->name;
पूर्ण

काष्ठा dma_heap *dma_heap_add(स्थिर काष्ठा dma_heap_export_info *exp_info)
अणु
	काष्ठा dma_heap *heap, *h, *err_ret;
	काष्ठा device *dev_ret;
	अचिन्हित पूर्णांक minor;
	पूर्णांक ret;

	अगर (!exp_info->name || !म_भेद(exp_info->name, "")) अणु
		pr_err("dma_heap: Cannot add heap without a name\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!exp_info->ops || !exp_info->ops->allocate) अणु
		pr_err("dma_heap: Cannot add heap with invalid ops struct\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* check the name is unique */
	mutex_lock(&heap_list_lock);
	list_क्रम_each_entry(h, &heap_list, list) अणु
		अगर (!म_भेद(h->name, exp_info->name)) अणु
			mutex_unlock(&heap_list_lock);
			pr_err("dma_heap: Already registered heap named %s\n",
			       exp_info->name);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण
	mutex_unlock(&heap_list_lock);

	heap = kzalloc(माप(*heap), GFP_KERNEL);
	अगर (!heap)
		वापस ERR_PTR(-ENOMEM);

	heap->name = exp_info->name;
	heap->ops = exp_info->ops;
	heap->priv = exp_info->priv;

	/* Find unused minor number */
	ret = xa_alloc(&dma_heap_minors, &minor, heap,
		       XA_LIMIT(0, NUM_HEAP_MINORS - 1), GFP_KERNEL);
	अगर (ret < 0) अणु
		pr_err("dma_heap: Unable to get minor number for heap\n");
		err_ret = ERR_PTR(ret);
		जाओ err0;
	पूर्ण

	/* Create device */
	heap->heap_devt = MKDEV(MAJOR(dma_heap_devt), minor);

	cdev_init(&heap->heap_cdev, &dma_heap_fops);
	ret = cdev_add(&heap->heap_cdev, heap->heap_devt, 1);
	अगर (ret < 0) अणु
		pr_err("dma_heap: Unable to add char device\n");
		err_ret = ERR_PTR(ret);
		जाओ err1;
	पूर्ण

	dev_ret = device_create(dma_heap_class,
				शून्य,
				heap->heap_devt,
				शून्य,
				heap->name);
	अगर (IS_ERR(dev_ret)) अणु
		pr_err("dma_heap: Unable to create device\n");
		err_ret = ERR_CAST(dev_ret);
		जाओ err2;
	पूर्ण
	/* Add heap to the list */
	mutex_lock(&heap_list_lock);
	list_add(&heap->list, &heap_list);
	mutex_unlock(&heap_list_lock);

	वापस heap;

err2:
	cdev_del(&heap->heap_cdev);
err1:
	xa_erase(&dma_heap_minors, minor);
err0:
	kमुक्त(heap);
	वापस err_ret;
पूर्ण

अटल अक्षर *dma_heap_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "dma_heap/%s", dev_name(dev));
पूर्ण

अटल पूर्णांक dma_heap_init(व्योम)
अणु
	पूर्णांक ret;

	ret = alloc_chrdev_region(&dma_heap_devt, 0, NUM_HEAP_MINORS, DEVNAME);
	अगर (ret)
		वापस ret;

	dma_heap_class = class_create(THIS_MODULE, DEVNAME);
	अगर (IS_ERR(dma_heap_class)) अणु
		unरेजिस्टर_chrdev_region(dma_heap_devt, NUM_HEAP_MINORS);
		वापस PTR_ERR(dma_heap_class);
	पूर्ण
	dma_heap_class->devnode = dma_heap_devnode;

	वापस 0;
पूर्ण
subsys_initcall(dma_heap_init);
