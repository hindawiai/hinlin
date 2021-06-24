<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2001-2006 Silicon Graphics, Inc.  All rights
 * reserved.
 */

/*
 * SN Platक्रमm Special Memory (mspec) Support
 *
 * This driver exports the SN special memory (mspec) facility to user
 * processes.
 * There are two types of memory made available thru this driver:
 * uncached and cached.
 *
 * Uncached are used क्रम memory ग_लिखो combining feature of the ia64
 * cpu.
 *
 * Cached are used क्रम areas of memory that are used as cached addresses
 * on our partition and used as uncached addresses from other partitions.
 * Due to a design स्थिरraपूर्णांक of the SN2 Shub, you can not have processors
 * on the same FSB perक्रमm both a cached and uncached reference to the
 * same cache line.  These special memory cached regions prevent the
 * kernel from ever dropping in a TLB entry and thereक्रमe prevent the
 * processor from ever speculating a cache line from this page.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/miscdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/numa.h>
#समावेश <linux/refcount.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/uncached.h>


#घोषणा CACHED_ID	"Cached,"
#घोषणा UNCACHED_ID	"Uncached"
#घोषणा REVISION	"4.0"
#घोषणा MSPEC_BASENAME	"mspec"

/*
 * Page types allocated by the device.
 */
क्रमागत mspec_page_type अणु
	MSPEC_CACHED = 2,
	MSPEC_UNCACHED
पूर्ण;

/*
 * One of these काष्ठाures is allocated when an mspec region is mmaped. The
 * काष्ठाure is poपूर्णांकed to by the vma->vm_निजी_data field in the vma काष्ठा.
 * This काष्ठाure is used to record the addresses of the mspec pages.
 * This काष्ठाure is shared by all vma's that are split off from the
 * original vma when split_vma()'s are करोne.
 *
 * The refcnt is incremented atomically because mm->mmap_lock करोes not
 * protect in विभाजन हाल where multiple tasks share the vma_data.
 */
काष्ठा vma_data अणु
	refcount_t refcnt;	/* Number of vmas sharing the data. */
	spinlock_t lock;	/* Serialize access to this काष्ठाure. */
	पूर्णांक count;		/* Number of pages allocated. */
	क्रमागत mspec_page_type type; /* Type of pages allocated. */
	अचिन्हित दीर्घ vm_start;	/* Original (unsplit) base. */
	अचिन्हित दीर्घ vm_end;	/* Original (unsplit) end. */
	अचिन्हित दीर्घ maddr[];	/* Array of MSPEC addresses. */
पूर्ण;

/*
 * mspec_खोलो
 *
 * Called when a device mapping is created by a means other than mmap
 * (via विभाजन, munmap, etc.).  Increments the reference count on the
 * underlying mspec data so it is not मुक्तd prematurely.
 */
अटल व्योम
mspec_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vma_data *vdata;

	vdata = vma->vm_निजी_data;
	refcount_inc(&vdata->refcnt);
पूर्ण

/*
 * mspec_बंद
 *
 * Called when unmapping a device mapping. Frees all mspec pages
 * beदीर्घing to all the vma's sharing this vma_data काष्ठाure.
 */
अटल व्योम
mspec_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा vma_data *vdata;
	पूर्णांक index, last_index;
	अचिन्हित दीर्घ my_page;

	vdata = vma->vm_निजी_data;

	अगर (!refcount_dec_and_test(&vdata->refcnt))
		वापस;

	last_index = (vdata->vm_end - vdata->vm_start) >> PAGE_SHIFT;
	क्रम (index = 0; index < last_index; index++) अणु
		अगर (vdata->maddr[index] == 0)
			जारी;
		/*
		 * Clear the page beक्रमe sticking it back
		 * पूर्णांकo the pool.
		 */
		my_page = vdata->maddr[index];
		vdata->maddr[index] = 0;
		स_रखो((अक्षर *)my_page, 0, PAGE_SIZE);
		uncached_मुक्त_page(my_page, 1);
	पूर्ण

	kvमुक्त(vdata);
पूर्ण

/*
 * mspec_fault
 *
 * Creates a mspec page and maps it to user space.
 */
अटल vm_fault_t
mspec_fault(काष्ठा vm_fault *vmf)
अणु
	अचिन्हित दीर्घ paddr, maddr;
	अचिन्हित दीर्घ pfn;
	pgoff_t index = vmf->pgoff;
	काष्ठा vma_data *vdata = vmf->vma->vm_निजी_data;

	maddr = (अस्थिर अचिन्हित दीर्घ) vdata->maddr[index];
	अगर (maddr == 0) अणु
		maddr = uncached_alloc_page(numa_node_id(), 1);
		अगर (maddr == 0)
			वापस VM_FAULT_OOM;

		spin_lock(&vdata->lock);
		अगर (vdata->maddr[index] == 0) अणु
			vdata->count++;
			vdata->maddr[index] = maddr;
		पूर्ण अन्यथा अणु
			uncached_मुक्त_page(maddr, 1);
			maddr = vdata->maddr[index];
		पूर्ण
		spin_unlock(&vdata->lock);
	पूर्ण

	paddr = maddr & ~__IA64_UNCACHED_OFFSET;
	pfn = paddr >> PAGE_SHIFT;

	वापस vmf_insert_pfn(vmf->vma, vmf->address, pfn);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा mspec_vm_ops = अणु
	.खोलो = mspec_खोलो,
	.बंद = mspec_बंद,
	.fault = mspec_fault,
पूर्ण;

/*
 * mspec_mmap
 *
 * Called when mmapping the device.  Initializes the vma with a fault handler
 * and निजी data काष्ठाure necessary to allocate, track, and मुक्त the
 * underlying pages.
 */
अटल पूर्णांक
mspec_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma,
					क्रमागत mspec_page_type type)
अणु
	काष्ठा vma_data *vdata;
	पूर्णांक pages, vdata_size;

	अगर (vma->vm_pgoff != 0)
		वापस -EINVAL;

	अगर ((vma->vm_flags & VM_SHARED) == 0)
		वापस -EINVAL;

	अगर ((vma->vm_flags & VM_WRITE) == 0)
		वापस -EPERM;

	pages = vma_pages(vma);
	vdata_size = माप(काष्ठा vma_data) + pages * माप(दीर्घ);
	vdata = kvzalloc(vdata_size, GFP_KERNEL);
	अगर (!vdata)
		वापस -ENOMEM;

	vdata->vm_start = vma->vm_start;
	vdata->vm_end = vma->vm_end;
	vdata->type = type;
	spin_lock_init(&vdata->lock);
	refcount_set(&vdata->refcnt, 1);
	vma->vm_निजी_data = vdata;

	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;
	अगर (vdata->type == MSPEC_UNCACHED)
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_ops = &mspec_vm_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक
cached_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस mspec_mmap(file, vma, MSPEC_CACHED);
पूर्ण

अटल पूर्णांक
uncached_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस mspec_mmap(file, vma, MSPEC_UNCACHED);
पूर्ण

अटल स्थिर काष्ठा file_operations cached_fops = अणु
	.owner = THIS_MODULE,
	.mmap = cached_mmap,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice cached_miscdev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "mspec_cached",
	.fops = &cached_fops
पूर्ण;

अटल स्थिर काष्ठा file_operations uncached_fops = अणु
	.owner = THIS_MODULE,
	.mmap = uncached_mmap,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice uncached_miscdev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "mspec_uncached",
	.fops = &uncached_fops
पूर्ण;

/*
 * mspec_init
 *
 * Called at boot समय to initialize the mspec facility.
 */
अटल पूर्णांक __init
mspec_init(व्योम)
अणु
	पूर्णांक ret;

	ret = misc_रेजिस्टर(&cached_miscdev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to register device %i\n",
		       CACHED_ID, ret);
		वापस ret;
	पूर्ण
	ret = misc_रेजिस्टर(&uncached_miscdev);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "%s: failed to register device %i\n",
		       UNCACHED_ID, ret);
		misc_deरेजिस्टर(&cached_miscdev);
		वापस ret;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s %s initialized devices: %s %s\n",
	       MSPEC_BASENAME, REVISION, CACHED_ID, UNCACHED_ID);

	वापस 0;
पूर्ण

अटल व्योम __निकास
mspec_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&uncached_miscdev);
	misc_deरेजिस्टर(&cached_miscdev);
पूर्ण

module_init(mspec_init);
module_निकास(mspec_निकास);

MODULE_AUTHOR("Silicon Graphics, Inc. <linux-altix@sgi.com>");
MODULE_DESCRIPTION("Driver for SGI SN special memory operations");
MODULE_LICENSE("GPL");
