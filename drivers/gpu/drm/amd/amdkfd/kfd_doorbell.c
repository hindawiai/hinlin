<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#समावेश "kfd_priv.h"
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/idr.h>

/*
 * This extension supports a kernel level करोorbells management क्रम the
 * kernel queues using the first करोorbell page reserved क्रम the kernel.
 */

/*
 * Each device exposes a करोorbell aperture, a PCI MMIO aperture that
 * receives 32-bit ग_लिखोs that are passed to queues as wptr values.
 * The करोorbells are पूर्णांकended to be written by applications as part
 * of queueing work on user-mode queues.
 * We assign करोorbells to applications in PAGE_SIZE-sized and aligned chunks.
 * We map the करोorbell address space पूर्णांकo user-mode when a process creates
 * its first queue on each device.
 * Although the mapping is करोne by KFD, it is equivalent to an mmap of
 * the /dev/kfd with the particular device encoded in the mmap offset.
 * There will be other uses क्रम mmap of /dev/kfd, so only a range of
 * offsets (KFD_MMAP_DOORBELL_START-END) is used क्रम करोorbells.
 */

/* # of करोorbell bytes allocated क्रम each process. */
माप_प्रकार kfd_करोorbell_process_slice(काष्ठा kfd_dev *kfd)
अणु
	वापस roundup(kfd->device_info->करोorbell_size *
			KFD_MAX_NUM_OF_QUEUES_PER_PROCESS,
			PAGE_SIZE);
पूर्ण

/* Doorbell calculations क्रम device init. */
पूर्णांक kfd_करोorbell_init(काष्ठा kfd_dev *kfd)
अणु
	माप_प्रकार करोorbell_start_offset;
	माप_प्रकार करोorbell_aperture_size;
	माप_प्रकार करोorbell_process_limit;

	/*
	 * We start with calculations in bytes because the input data might
	 * only be byte-aligned.
	 * Only after we have करोne the rounding can we assume any alignment.
	 */

	करोorbell_start_offset =
			roundup(kfd->shared_resources.करोorbell_start_offset,
					kfd_करोorbell_process_slice(kfd));

	करोorbell_aperture_size =
			roundकरोwn(kfd->shared_resources.करोorbell_aperture_size,
					kfd_करोorbell_process_slice(kfd));

	अगर (करोorbell_aperture_size > करोorbell_start_offset)
		करोorbell_process_limit =
			(करोorbell_aperture_size - करोorbell_start_offset) /
						kfd_करोorbell_process_slice(kfd);
	अन्यथा
		वापस -ENOSPC;

	अगर (!kfd->max_करोorbell_slices ||
	    करोorbell_process_limit < kfd->max_करोorbell_slices)
		kfd->max_करोorbell_slices = करोorbell_process_limit;

	kfd->करोorbell_base = kfd->shared_resources.करोorbell_physical_address +
				करोorbell_start_offset;

	kfd->करोorbell_base_dw_offset = करोorbell_start_offset / माप(u32);

	kfd->करोorbell_kernel_ptr = ioremap(kfd->करोorbell_base,
					   kfd_करोorbell_process_slice(kfd));

	अगर (!kfd->करोorbell_kernel_ptr)
		वापस -ENOMEM;

	pr_debug("Doorbell initialization:\n");
	pr_debug("doorbell base           == 0x%08lX\n",
			(uपूर्णांकptr_t)kfd->करोorbell_base);

	pr_debug("doorbell_base_dw_offset      == 0x%08lX\n",
			kfd->करोorbell_base_dw_offset);

	pr_debug("doorbell_process_limit  == 0x%08lX\n",
			करोorbell_process_limit);

	pr_debug("doorbell_kernel_offset  == 0x%08lX\n",
			(uपूर्णांकptr_t)kfd->करोorbell_base);

	pr_debug("doorbell aperture size  == 0x%08lX\n",
			kfd->shared_resources.करोorbell_aperture_size);

	pr_debug("doorbell kernel address == %p\n", kfd->करोorbell_kernel_ptr);

	वापस 0;
पूर्ण

व्योम kfd_करोorbell_fini(काष्ठा kfd_dev *kfd)
अणु
	अगर (kfd->करोorbell_kernel_ptr)
		iounmap(kfd->करोorbell_kernel_ptr);
पूर्ण

पूर्णांक kfd_करोorbell_mmap(काष्ठा kfd_dev *dev, काष्ठा kfd_process *process,
		      काष्ठा vm_area_काष्ठा *vma)
अणु
	phys_addr_t address;
	काष्ठा kfd_process_device *pdd;

	/*
	 * For simplicitly we only allow mapping of the entire करोorbell
	 * allocation of a single device & process.
	 */
	अगर (vma->vm_end - vma->vm_start != kfd_करोorbell_process_slice(dev))
		वापस -EINVAL;

	pdd = kfd_get_process_device_data(dev, process);
	अगर (!pdd)
		वापस -EINVAL;

	/* Calculate physical address of करोorbell */
	address = kfd_get_process_करोorbells(pdd);
	vma->vm_flags |= VM_IO | VM_DONTCOPY | VM_DONTEXPAND | VM_NORESERVE |
				VM_DONTDUMP | VM_PFNMAP;

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	pr_debug("Mapping doorbell page\n"
		 "     target user address == 0x%08llX\n"
		 "     physical address    == 0x%08llX\n"
		 "     vm_flags            == 0x%04lX\n"
		 "     size                == 0x%04lX\n",
		 (अचिन्हित दीर्घ दीर्घ) vma->vm_start, address, vma->vm_flags,
		 kfd_करोorbell_process_slice(dev));


	वापस io_remap_pfn_range(vma,
				vma->vm_start,
				address >> PAGE_SHIFT,
				kfd_करोorbell_process_slice(dev),
				vma->vm_page_prot);
पूर्ण


/* get kernel iomem poपूर्णांकer क्रम a करोorbell */
व्योम __iomem *kfd_get_kernel_करोorbell(काष्ठा kfd_dev *kfd,
					अचिन्हित पूर्णांक *करोorbell_off)
अणु
	u32 inx;

	mutex_lock(&kfd->करोorbell_mutex);
	inx = find_first_zero_bit(kfd->करोorbell_available_index,
					KFD_MAX_NUM_OF_QUEUES_PER_PROCESS);

	__set_bit(inx, kfd->करोorbell_available_index);
	mutex_unlock(&kfd->करोorbell_mutex);

	अगर (inx >= KFD_MAX_NUM_OF_QUEUES_PER_PROCESS)
		वापस शून्य;

	inx *= kfd->device_info->करोorbell_size / माप(u32);

	/*
	 * Calculating the kernel करोorbell offset using the first
	 * करोorbell page.
	 */
	*करोorbell_off = kfd->करोorbell_base_dw_offset + inx;

	pr_debug("Get kernel queue doorbell\n"
			"     doorbell offset   == 0x%08X\n"
			"     doorbell index    == 0x%x\n",
		*करोorbell_off, inx);

	वापस kfd->करोorbell_kernel_ptr + inx;
पूर्ण

व्योम kfd_release_kernel_करोorbell(काष्ठा kfd_dev *kfd, u32 __iomem *db_addr)
अणु
	अचिन्हित पूर्णांक inx;

	inx = (अचिन्हित पूर्णांक)(db_addr - kfd->करोorbell_kernel_ptr)
		* माप(u32) / kfd->device_info->करोorbell_size;

	mutex_lock(&kfd->करोorbell_mutex);
	__clear_bit(inx, kfd->करोorbell_available_index);
	mutex_unlock(&kfd->करोorbell_mutex);
पूर्ण

व्योम ग_लिखो_kernel_करोorbell(व्योम __iomem *db, u32 value)
अणु
	अगर (db) अणु
		ग_लिखोl(value, db);
		pr_debug("Writing %d to doorbell address %p\n", value, db);
	पूर्ण
पूर्ण

व्योम ग_लिखो_kernel_करोorbell64(व्योम __iomem *db, u64 value)
अणु
	अगर (db) अणु
		WARN(((अचिन्हित दीर्घ)db & 7) != 0,
		     "Unaligned 64-bit doorbell");
		ग_लिखोq(value, (u64 __iomem *)db);
		pr_debug("writing %llu to doorbell address %p\n", value, db);
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक kfd_get_करोorbell_dw_offset_in_bar(काष्ठा kfd_dev *kfd,
					काष्ठा kfd_process_device *pdd,
					अचिन्हित पूर्णांक करोorbell_id)
अणु
	/*
	 * करोorbell_base_dw_offset accounts क्रम करोorbells taken by KGD.
	 * index * kfd_करोorbell_process_slice/माप(u32) adjusts to
	 * the process's करोorbells. The offset वापसed is in dword
	 * units regardless of the ASIC-dependent करोorbell size.
	 */
	वापस kfd->करोorbell_base_dw_offset +
		pdd->करोorbell_index
		* kfd_करोorbell_process_slice(kfd) / माप(u32) +
		करोorbell_id * kfd->device_info->करोorbell_size / माप(u32);
पूर्ण

uपूर्णांक64_t kfd_get_number_elems(काष्ठा kfd_dev *kfd)
अणु
	uपूर्णांक64_t num_of_elems = (kfd->shared_resources.करोorbell_aperture_size -
				kfd->shared_resources.करोorbell_start_offset) /
					kfd_करोorbell_process_slice(kfd) + 1;

	वापस num_of_elems;

पूर्ण

phys_addr_t kfd_get_process_करोorbells(काष्ठा kfd_process_device *pdd)
अणु
	वापस pdd->dev->करोorbell_base +
		pdd->करोorbell_index * kfd_करोorbell_process_slice(pdd->dev);
पूर्ण

पूर्णांक kfd_alloc_process_करोorbells(काष्ठा kfd_dev *kfd, अचिन्हित पूर्णांक *करोorbell_index)
अणु
	पूर्णांक r = ida_simple_get(&kfd->करोorbell_ida, 1, kfd->max_करोorbell_slices,
				GFP_KERNEL);
	अगर (r > 0)
		*करोorbell_index = r;

	वापस r;
पूर्ण

व्योम kfd_मुक्त_process_करोorbells(काष्ठा kfd_dev *kfd, अचिन्हित पूर्णांक करोorbell_index)
अणु
	अगर (करोorbell_index)
		ida_simple_हटाओ(&kfd->करोorbell_ida, करोorbell_index);
पूर्ण
