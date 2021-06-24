<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/cred.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/memfd.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/udmabuf.h>

अटल स्थिर u32    list_limit = 1024;  /* udmabuf_create_list->count limit */
अटल स्थिर माप_प्रकार size_limit_mb = 64; /* total dmabuf size, in megabytes  */

काष्ठा udmabuf अणु
	pgoff_t pagecount;
	काष्ठा page **pages;
	काष्ठा sg_table *sg;
	काष्ठा miscdevice *device;
पूर्ण;

अटल vm_fault_t udmabuf_vm_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा udmabuf *ubuf = vma->vm_निजी_data;

	vmf->page = ubuf->pages[vmf->pgoff];
	get_page(vmf->page);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा udmabuf_vm_ops = अणु
	.fault = udmabuf_vm_fault,
पूर्ण;

अटल पूर्णांक mmap_udmabuf(काष्ठा dma_buf *buf, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा udmabuf *ubuf = buf->priv;

	अगर ((vma->vm_flags & (VM_SHARED | VM_MAYSHARE)) == 0)
		वापस -EINVAL;

	vma->vm_ops = &udmabuf_vm_ops;
	vma->vm_निजी_data = ubuf;
	वापस 0;
पूर्ण

अटल काष्ठा sg_table *get_sg_table(काष्ठा device *dev, काष्ठा dma_buf *buf,
				     क्रमागत dma_data_direction direction)
अणु
	काष्ठा udmabuf *ubuf = buf->priv;
	काष्ठा sg_table *sg;
	पूर्णांक ret;

	sg = kzalloc(माप(*sg), GFP_KERNEL);
	अगर (!sg)
		वापस ERR_PTR(-ENOMEM);
	ret = sg_alloc_table_from_pages(sg, ubuf->pages, ubuf->pagecount,
					0, ubuf->pagecount << PAGE_SHIFT,
					GFP_KERNEL);
	अगर (ret < 0)
		जाओ err;
	ret = dma_map_sgtable(dev, sg, direction, 0);
	अगर (ret < 0)
		जाओ err;
	वापस sg;

err:
	sg_मुक्त_table(sg);
	kमुक्त(sg);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम put_sg_table(काष्ठा device *dev, काष्ठा sg_table *sg,
			 क्रमागत dma_data_direction direction)
अणु
	dma_unmap_sgtable(dev, sg, direction, 0);
	sg_मुक्त_table(sg);
	kमुक्त(sg);
पूर्ण

अटल काष्ठा sg_table *map_udmabuf(काष्ठा dma_buf_attachment *at,
				    क्रमागत dma_data_direction direction)
अणु
	वापस get_sg_table(at->dev, at->dmabuf, direction);
पूर्ण

अटल व्योम unmap_udmabuf(काष्ठा dma_buf_attachment *at,
			  काष्ठा sg_table *sg,
			  क्रमागत dma_data_direction direction)
अणु
	वापस put_sg_table(at->dev, sg, direction);
पूर्ण

अटल व्योम release_udmabuf(काष्ठा dma_buf *buf)
अणु
	काष्ठा udmabuf *ubuf = buf->priv;
	काष्ठा device *dev = ubuf->device->this_device;
	pgoff_t pg;

	अगर (ubuf->sg)
		put_sg_table(dev, ubuf->sg, DMA_BIसूचीECTIONAL);

	क्रम (pg = 0; pg < ubuf->pagecount; pg++)
		put_page(ubuf->pages[pg]);
	kमुक्त(ubuf->pages);
	kमुक्त(ubuf);
पूर्ण

अटल पूर्णांक begin_cpu_udmabuf(काष्ठा dma_buf *buf,
			     क्रमागत dma_data_direction direction)
अणु
	काष्ठा udmabuf *ubuf = buf->priv;
	काष्ठा device *dev = ubuf->device->this_device;

	अगर (!ubuf->sg) अणु
		ubuf->sg = get_sg_table(dev, buf, direction);
		अगर (IS_ERR(ubuf->sg))
			वापस PTR_ERR(ubuf->sg);
	पूर्ण अन्यथा अणु
		dma_sync_sg_क्रम_cpu(dev, ubuf->sg->sgl, ubuf->sg->nents,
				    direction);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक end_cpu_udmabuf(काष्ठा dma_buf *buf,
			   क्रमागत dma_data_direction direction)
अणु
	काष्ठा udmabuf *ubuf = buf->priv;
	काष्ठा device *dev = ubuf->device->this_device;

	अगर (!ubuf->sg)
		वापस -EINVAL;

	dma_sync_sg_क्रम_device(dev, ubuf->sg->sgl, ubuf->sg->nents, direction);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dma_buf_ops udmabuf_ops = अणु
	.cache_sgt_mapping = true,
	.map_dma_buf	   = map_udmabuf,
	.unmap_dma_buf	   = unmap_udmabuf,
	.release	   = release_udmabuf,
	.mmap		   = mmap_udmabuf,
	.begin_cpu_access  = begin_cpu_udmabuf,
	.end_cpu_access    = end_cpu_udmabuf,
पूर्ण;

#घोषणा SEALS_WANTED (F_SEAL_SHRINK)
#घोषणा SEALS_DENIED (F_SEAL_WRITE)

अटल दीर्घ udmabuf_create(काष्ठा miscdevice *device,
			   काष्ठा udmabuf_create_list *head,
			   काष्ठा udmabuf_create_item *list)
अणु
	DEFINE_DMA_BUF_EXPORT_INFO(exp_info);
	काष्ठा file *memfd = शून्य;
	काष्ठा udmabuf *ubuf;
	काष्ठा dma_buf *buf;
	pgoff_t pgoff, pgcnt, pgidx, pgbuf = 0, pglimit;
	काष्ठा page *page;
	पूर्णांक seals, ret = -EINVAL;
	u32 i, flags;

	ubuf = kzalloc(माप(*ubuf), GFP_KERNEL);
	अगर (!ubuf)
		वापस -ENOMEM;

	pglimit = (size_limit_mb * 1024 * 1024) >> PAGE_SHIFT;
	क्रम (i = 0; i < head->count; i++) अणु
		अगर (!IS_ALIGNED(list[i].offset, PAGE_SIZE))
			जाओ err;
		अगर (!IS_ALIGNED(list[i].size, PAGE_SIZE))
			जाओ err;
		ubuf->pagecount += list[i].size >> PAGE_SHIFT;
		अगर (ubuf->pagecount > pglimit)
			जाओ err;
	पूर्ण
	ubuf->pages = kदो_स्मृति_array(ubuf->pagecount, माप(*ubuf->pages),
				    GFP_KERNEL);
	अगर (!ubuf->pages) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	pgbuf = 0;
	क्रम (i = 0; i < head->count; i++) अणु
		ret = -EBADFD;
		memfd = fget(list[i].memfd);
		अगर (!memfd)
			जाओ err;
		अगर (!shmem_mapping(file_inode(memfd)->i_mapping))
			जाओ err;
		seals = memfd_fcntl(memfd, F_GET_SEALS, 0);
		अगर (seals == -EINVAL)
			जाओ err;
		ret = -EINVAL;
		अगर ((seals & SEALS_WANTED) != SEALS_WANTED ||
		    (seals & SEALS_DENIED) != 0)
			जाओ err;
		pgoff = list[i].offset >> PAGE_SHIFT;
		pgcnt = list[i].size   >> PAGE_SHIFT;
		क्रम (pgidx = 0; pgidx < pgcnt; pgidx++) अणु
			page = shmem_पढ़ो_mapping_page(
				file_inode(memfd)->i_mapping, pgoff + pgidx);
			अगर (IS_ERR(page)) अणु
				ret = PTR_ERR(page);
				जाओ err;
			पूर्ण
			ubuf->pages[pgbuf++] = page;
		पूर्ण
		fput(memfd);
		memfd = शून्य;
	पूर्ण

	exp_info.ops  = &udmabuf_ops;
	exp_info.size = ubuf->pagecount << PAGE_SHIFT;
	exp_info.priv = ubuf;
	exp_info.flags = O_RDWR;

	ubuf->device = device;
	buf = dma_buf_export(&exp_info);
	अगर (IS_ERR(buf)) अणु
		ret = PTR_ERR(buf);
		जाओ err;
	पूर्ण

	flags = 0;
	अगर (head->flags & UDMABUF_FLAGS_CLOEXEC)
		flags |= O_CLOEXEC;
	वापस dma_buf_fd(buf, flags);

err:
	जबतक (pgbuf > 0)
		put_page(ubuf->pages[--pgbuf]);
	अगर (memfd)
		fput(memfd);
	kमुक्त(ubuf->pages);
	kमुक्त(ubuf);
	वापस ret;
पूर्ण

अटल दीर्घ udmabuf_ioctl_create(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा udmabuf_create create;
	काष्ठा udmabuf_create_list head;
	काष्ठा udmabuf_create_item list;

	अगर (copy_from_user(&create, (व्योम __user *)arg,
			   माप(create)))
		वापस -EFAULT;

	head.flags  = create.flags;
	head.count  = 1;
	list.memfd  = create.memfd;
	list.offset = create.offset;
	list.size   = create.size;

	वापस udmabuf_create(filp->निजी_data, &head, &list);
पूर्ण

अटल दीर्घ udmabuf_ioctl_create_list(काष्ठा file *filp, अचिन्हित दीर्घ arg)
अणु
	काष्ठा udmabuf_create_list head;
	काष्ठा udmabuf_create_item *list;
	पूर्णांक ret = -EINVAL;
	u32 lsize;

	अगर (copy_from_user(&head, (व्योम __user *)arg, माप(head)))
		वापस -EFAULT;
	अगर (head.count > list_limit)
		वापस -EINVAL;
	lsize = माप(काष्ठा udmabuf_create_item) * head.count;
	list = memdup_user((व्योम __user *)(arg + माप(head)), lsize);
	अगर (IS_ERR(list))
		वापस PTR_ERR(list);

	ret = udmabuf_create(filp->निजी_data, &head, list);
	kमुक्त(list);
	वापस ret;
पूर्ण

अटल दीर्घ udmabuf_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl,
			  अचिन्हित दीर्घ arg)
अणु
	दीर्घ ret;

	चयन (ioctl) अणु
	हाल UDMABUF_CREATE:
		ret = udmabuf_ioctl_create(filp, arg);
		अवरोध;
	हाल UDMABUF_CREATE_LIST:
		ret = udmabuf_ioctl_create_list(filp, arg);
		अवरोध;
	शेष:
		ret = -ENOTTY;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations udmabuf_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl = udmabuf_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl   = udmabuf_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा miscdevice udmabuf_misc = अणु
	.minor          = MISC_DYNAMIC_MINOR,
	.name           = "udmabuf",
	.fops           = &udmabuf_fops,
पूर्ण;

अटल पूर्णांक __init udmabuf_dev_init(व्योम)
अणु
	वापस misc_रेजिस्टर(&udmabuf_misc);
पूर्ण

अटल व्योम __निकास udmabuf_dev_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&udmabuf_misc);
पूर्ण

module_init(udmabuf_dev_init)
module_निकास(udmabuf_dev_निकास)

MODULE_AUTHOR("Gerd Hoffmann <kraxel@redhat.com>");
MODULE_LICENSE("GPL v2");
