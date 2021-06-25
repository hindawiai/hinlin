<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 * privcmd.c
 *
 * Interface to privileged करोमुख्य-0 commands.
 *
 * Copyright (c) 2002-2004, K A Fraser, B Dragovic
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/swap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/moduleparam.h>

#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/xen.h>
#समावेश <xen/privcmd.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/पूर्णांकerface/hvm/dm_op.h>
#समावेश <xen/features.h>
#समावेश <xen/page.h>
#समावेश <xen/xen-ops.h>
#समावेश <xen/balloon.h>

#समावेश "privcmd.h"

MODULE_LICENSE("GPL");

#घोषणा PRIV_VMA_LOCKED ((व्योम *)1)

अटल अचिन्हित पूर्णांक privcmd_dm_op_max_num = 16;
module_param_named(dm_op_max_nr_bufs, privcmd_dm_op_max_num, uपूर्णांक, 0644);
MODULE_PARM_DESC(dm_op_max_nr_bufs,
		 "Maximum number of buffers per dm_op hypercall");

अटल अचिन्हित पूर्णांक privcmd_dm_op_buf_max_size = 4096;
module_param_named(dm_op_buf_max_size, privcmd_dm_op_buf_max_size, uपूर्णांक,
		   0644);
MODULE_PARM_DESC(dm_op_buf_max_size,
		 "Maximum size of a dm_op hypercall buffer");

काष्ठा privcmd_data अणु
	करोmid_t करोmid;
पूर्ण;

अटल पूर्णांक privcmd_vma_range_is_mapped(
               काष्ठा vm_area_काष्ठा *vma,
               अचिन्हित दीर्घ addr,
               अचिन्हित दीर्घ nr_pages);

अटल दीर्घ privcmd_ioctl_hypercall(काष्ठा file *file, व्योम __user *udata)
अणु
	काष्ठा privcmd_data *data = file->निजी_data;
	काष्ठा privcmd_hypercall hypercall;
	दीर्घ ret;

	/* Disallow arbitrary hypercalls अगर restricted */
	अगर (data->करोmid != DOMID_INVALID)
		वापस -EPERM;

	अगर (copy_from_user(&hypercall, udata, माप(hypercall)))
		वापस -EFAULT;

	xen_preemptible_hcall_begin();
	ret = privcmd_call(hypercall.op,
			   hypercall.arg[0], hypercall.arg[1],
			   hypercall.arg[2], hypercall.arg[3],
			   hypercall.arg[4]);
	xen_preemptible_hcall_end();

	वापस ret;
पूर्ण

अटल व्योम मुक्त_page_list(काष्ठा list_head *pages)
अणु
	काष्ठा page *p, *n;

	list_क्रम_each_entry_safe(p, n, pages, lru)
		__मुक्त_page(p);

	INIT_LIST_HEAD(pages);
पूर्ण

/*
 * Given an array of items in userspace, वापस a list of pages
 * containing the data.  If copying fails, either because of memory
 * allocation failure or a problem पढ़ोing user memory, वापस an
 * error code; its up to the caller to dispose of any partial list.
 */
अटल पूर्णांक gather_array(काष्ठा list_head *pagelist,
			अचिन्हित nelem, माप_प्रकार size,
			स्थिर व्योम __user *data)
अणु
	अचिन्हित pageidx;
	व्योम *pagedata;
	पूर्णांक ret;

	अगर (size > PAGE_SIZE)
		वापस 0;

	pageidx = PAGE_SIZE;
	pagedata = शून्य;	/* quiet, gcc */
	जबतक (nelem--) अणु
		अगर (pageidx > PAGE_SIZE-size) अणु
			काष्ठा page *page = alloc_page(GFP_KERNEL);

			ret = -ENOMEM;
			अगर (page == शून्य)
				जाओ fail;

			pagedata = page_address(page);

			list_add_tail(&page->lru, pagelist);
			pageidx = 0;
		पूर्ण

		ret = -EFAULT;
		अगर (copy_from_user(pagedata + pageidx, data, size))
			जाओ fail;

		data += size;
		pageidx += size;
	पूर्ण

	ret = 0;

fail:
	वापस ret;
पूर्ण

/*
 * Call function "fn" on each element of the array fragmented
 * over a list of pages.
 */
अटल पूर्णांक traverse_pages(अचिन्हित nelem, माप_प्रकार size,
			  काष्ठा list_head *pos,
			  पूर्णांक (*fn)(व्योम *data, व्योम *state),
			  व्योम *state)
अणु
	व्योम *pagedata;
	अचिन्हित pageidx;
	पूर्णांक ret = 0;

	BUG_ON(size > PAGE_SIZE);

	pageidx = PAGE_SIZE;
	pagedata = शून्य;	/* hush, gcc */

	जबतक (nelem--) अणु
		अगर (pageidx > PAGE_SIZE-size) अणु
			काष्ठा page *page;
			pos = pos->next;
			page = list_entry(pos, काष्ठा page, lru);
			pagedata = page_address(page);
			pageidx = 0;
		पूर्ण

		ret = (*fn)(pagedata + pageidx, state);
		अगर (ret)
			अवरोध;
		pageidx += size;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Similar to traverse_pages, but use each page as a "block" of
 * data to be processed as one unit.
 */
अटल पूर्णांक traverse_pages_block(अचिन्हित nelem, माप_प्रकार size,
				काष्ठा list_head *pos,
				पूर्णांक (*fn)(व्योम *data, पूर्णांक nr, व्योम *state),
				व्योम *state)
अणु
	व्योम *pagedata;
	पूर्णांक ret = 0;

	BUG_ON(size > PAGE_SIZE);

	जबतक (nelem) अणु
		पूर्णांक nr = (PAGE_SIZE/size);
		काष्ठा page *page;
		अगर (nr > nelem)
			nr = nelem;
		pos = pos->next;
		page = list_entry(pos, काष्ठा page, lru);
		pagedata = page_address(page);
		ret = (*fn)(pagedata, nr, state);
		अगर (ret)
			अवरोध;
		nelem -= nr;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा mmap_gfn_state अणु
	अचिन्हित दीर्घ va;
	काष्ठा vm_area_काष्ठा *vma;
	करोmid_t करोमुख्य;
पूर्ण;

अटल पूर्णांक mmap_gfn_range(व्योम *data, व्योम *state)
अणु
	काष्ठा privcmd_mmap_entry *msg = data;
	काष्ठा mmap_gfn_state *st = state;
	काष्ठा vm_area_काष्ठा *vma = st->vma;
	पूर्णांक rc;

	/* Do not allow range to wrap the address space. */
	अगर ((msg->npages > (दीर्घ_उच्च >> PAGE_SHIFT)) ||
	    ((अचिन्हित दीर्घ)(msg->npages << PAGE_SHIFT) >= -st->va))
		वापस -EINVAL;

	/* Range chunks must be contiguous in va space. */
	अगर ((msg->va != st->va) ||
	    ((msg->va+(msg->npages<<PAGE_SHIFT)) > vma->vm_end))
		वापस -EINVAL;

	rc = xen_remap_करोमुख्य_gfn_range(vma,
					msg->va & PAGE_MASK,
					msg->mfn, msg->npages,
					vma->vm_page_prot,
					st->करोमुख्य, शून्य);
	अगर (rc < 0)
		वापस rc;

	st->va += msg->npages << PAGE_SHIFT;

	वापस 0;
पूर्ण

अटल दीर्घ privcmd_ioctl_mmap(काष्ठा file *file, व्योम __user *udata)
अणु
	काष्ठा privcmd_data *data = file->निजी_data;
	काष्ठा privcmd_mmap mmapcmd;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक rc;
	LIST_HEAD(pagelist);
	काष्ठा mmap_gfn_state state;

	/* We only support privcmd_ioctl_mmap_batch क्रम स्वतः translated. */
	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		वापस -ENOSYS;

	अगर (copy_from_user(&mmapcmd, udata, माप(mmapcmd)))
		वापस -EFAULT;

	/* If restriction is in place, check the करोmid matches */
	अगर (data->करोmid != DOMID_INVALID && data->करोmid != mmapcmd.करोm)
		वापस -EPERM;

	rc = gather_array(&pagelist,
			  mmapcmd.num, माप(काष्ठा privcmd_mmap_entry),
			  mmapcmd.entry);

	अगर (rc || list_empty(&pagelist))
		जाओ out;

	mmap_ग_लिखो_lock(mm);

	अणु
		काष्ठा page *page = list_first_entry(&pagelist,
						     काष्ठा page, lru);
		काष्ठा privcmd_mmap_entry *msg = page_address(page);

		vma = find_vma(mm, msg->va);
		rc = -EINVAL;

		अगर (!vma || (msg->va != vma->vm_start) || vma->vm_निजी_data)
			जाओ out_up;
		vma->vm_निजी_data = PRIV_VMA_LOCKED;
	पूर्ण

	state.va = vma->vm_start;
	state.vma = vma;
	state.करोमुख्य = mmapcmd.करोm;

	rc = traverse_pages(mmapcmd.num, माप(काष्ठा privcmd_mmap_entry),
			    &pagelist,
			    mmap_gfn_range, &state);


out_up:
	mmap_ग_लिखो_unlock(mm);

out:
	मुक्त_page_list(&pagelist);

	वापस rc;
पूर्ण

काष्ठा mmap_batch_state अणु
	करोmid_t करोमुख्य;
	अचिन्हित दीर्घ va;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक index;
	/* A tristate:
	 *      0 क्रम no errors
	 *      1 अगर at least one error has happened (and no
	 *          -ENOENT errors have happened)
	 *      -ENOENT अगर at least 1 -ENOENT has happened.
	 */
	पूर्णांक global_error;
	पूर्णांक version;

	/* User-space gfn array to store errors in the second pass क्रम V1. */
	xen_pfn_t __user *user_gfn;
	/* User-space पूर्णांक array to store errors in the second pass क्रम V2. */
	पूर्णांक __user *user_err;
पूर्ण;

/* स्वतः translated करोm0 note: अगर करोmU being created is PV, then gfn is
 * mfn(addr on bus). If it's स्वतः xlated, then gfn is pfn (input to HAP).
 */
अटल पूर्णांक mmap_batch_fn(व्योम *data, पूर्णांक nr, व्योम *state)
अणु
	xen_pfn_t *gfnp = data;
	काष्ठा mmap_batch_state *st = state;
	काष्ठा vm_area_काष्ठा *vma = st->vma;
	काष्ठा page **pages = vma->vm_निजी_data;
	काष्ठा page **cur_pages = शून्य;
	पूर्णांक ret;

	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		cur_pages = &pages[st->index];

	BUG_ON(nr < 0);
	ret = xen_remap_करोमुख्य_gfn_array(st->vma, st->va & PAGE_MASK, gfnp, nr,
					 (पूर्णांक *)gfnp, st->vma->vm_page_prot,
					 st->करोमुख्य, cur_pages);

	/* Adjust the global_error? */
	अगर (ret != nr) अणु
		अगर (ret == -ENOENT)
			st->global_error = -ENOENT;
		अन्यथा अणु
			/* Record that at least one error has happened. */
			अगर (st->global_error == 0)
				st->global_error = 1;
		पूर्ण
	पूर्ण
	st->va += XEN_PAGE_SIZE * nr;
	st->index += nr / XEN_PFN_PER_PAGE;

	वापस 0;
पूर्ण

अटल पूर्णांक mmap_वापस_error(पूर्णांक err, काष्ठा mmap_batch_state *st)
अणु
	पूर्णांक ret;

	अगर (st->version == 1) अणु
		अगर (err) अणु
			xen_pfn_t gfn;

			ret = get_user(gfn, st->user_gfn);
			अगर (ret < 0)
				वापस ret;
			/*
			 * V1 encodes the error codes in the 32bit top
			 * nibble of the gfn (with its known
			 * limitations vis-a-vis 64 bit callers).
			 */
			gfn |= (err == -ENOENT) ?
				PRIVCMD_MMAPBATCH_PAGED_ERROR :
				PRIVCMD_MMAPBATCH_MFN_ERROR;
			वापस __put_user(gfn, st->user_gfn++);
		पूर्ण अन्यथा
			st->user_gfn++;
	पूर्ण अन्यथा अणु /* st->version == 2 */
		अगर (err)
			वापस __put_user(err, st->user_err++);
		अन्यथा
			st->user_err++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmap_वापस_errors(व्योम *data, पूर्णांक nr, व्योम *state)
अणु
	काष्ठा mmap_batch_state *st = state;
	पूर्णांक *errs = data;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < nr; i++) अणु
		ret = mmap_वापस_error(errs[i], st);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/* Allocate pfns that are then mapped with gfns from क्रमeign करोmid. Update
 * the vma with the page info to use later.
 * Returns: 0 अगर success, otherwise -त्रुटि_सं
 */
अटल पूर्णांक alloc_empty_pages(काष्ठा vm_area_काष्ठा *vma, पूर्णांक numpgs)
अणु
	पूर्णांक rc;
	काष्ठा page **pages;

	pages = kसुस्मृति(numpgs, माप(pages[0]), GFP_KERNEL);
	अगर (pages == शून्य)
		वापस -ENOMEM;

	rc = xen_alloc_unpopulated_pages(numpgs, pages);
	अगर (rc != 0) अणु
		pr_warn("%s Could not alloc %d pfns rc:%d\n", __func__,
			numpgs, rc);
		kमुक्त(pages);
		वापस -ENOMEM;
	पूर्ण
	BUG_ON(vma->vm_निजी_data != शून्य);
	vma->vm_निजी_data = pages;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा privcmd_vm_ops;

अटल दीर्घ privcmd_ioctl_mmap_batch(
	काष्ठा file *file, व्योम __user *udata, पूर्णांक version)
अणु
	काष्ठा privcmd_data *data = file->निजी_data;
	पूर्णांक ret;
	काष्ठा privcmd_mmapbatch_v2 m;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ nr_pages;
	LIST_HEAD(pagelist);
	काष्ठा mmap_batch_state state;

	चयन (version) अणु
	हाल 1:
		अगर (copy_from_user(&m, udata, माप(काष्ठा privcmd_mmapbatch)))
			वापस -EFAULT;
		/* Returns per-frame error in m.arr. */
		m.err = शून्य;
		अगर (!access_ok(m.arr, m.num * माप(*m.arr)))
			वापस -EFAULT;
		अवरोध;
	हाल 2:
		अगर (copy_from_user(&m, udata, माप(काष्ठा privcmd_mmapbatch_v2)))
			वापस -EFAULT;
		/* Returns per-frame error code in m.err. */
		अगर (!access_ok(m.err, m.num * (माप(*m.err))))
			वापस -EFAULT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* If restriction is in place, check the करोmid matches */
	अगर (data->करोmid != DOMID_INVALID && data->करोmid != m.करोm)
		वापस -EPERM;

	nr_pages = DIV_ROUND_UP(m.num, XEN_PFN_PER_PAGE);
	अगर ((m.num <= 0) || (nr_pages > (दीर्घ_उच्च >> PAGE_SHIFT)))
		वापस -EINVAL;

	ret = gather_array(&pagelist, m.num, माप(xen_pfn_t), m.arr);

	अगर (ret)
		जाओ out;
	अगर (list_empty(&pagelist)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (version == 2) अणु
		/* Zero error array now to only copy back actual errors. */
		अगर (clear_user(m.err, माप(पूर्णांक) * m.num)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	mmap_ग_लिखो_lock(mm);

	vma = find_vma(mm, m.addr);
	अगर (!vma ||
	    vma->vm_ops != &privcmd_vm_ops) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/*
	 * Caller must either:
	 *
	 * Map the whole VMA range, which will also allocate all the
	 * pages required क्रम the स्वतः_translated_physmap हाल.
	 *
	 * Or
	 *
	 * Map unmapped holes left from a previous map attempt (e.g.,
	 * because those क्रमeign frames were previously paged out).
	 */
	अगर (vma->vm_निजी_data == शून्य) अणु
		अगर (m.addr != vma->vm_start ||
		    m.addr + (nr_pages << PAGE_SHIFT) != vma->vm_end) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		अगर (xen_feature(XENFEAT_स्वतः_translated_physmap)) अणु
			ret = alloc_empty_pages(vma, nr_pages);
			अगर (ret < 0)
				जाओ out_unlock;
		पूर्ण अन्यथा
			vma->vm_निजी_data = PRIV_VMA_LOCKED;
	पूर्ण अन्यथा अणु
		अगर (m.addr < vma->vm_start ||
		    m.addr + (nr_pages << PAGE_SHIFT) > vma->vm_end) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		अगर (privcmd_vma_range_is_mapped(vma, m.addr, nr_pages)) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	state.करोमुख्य        = m.करोm;
	state.vma           = vma;
	state.va            = m.addr;
	state.index         = 0;
	state.global_error  = 0;
	state.version       = version;

	BUILD_BUG_ON(((PAGE_SIZE / माप(xen_pfn_t)) % XEN_PFN_PER_PAGE) != 0);
	/* mmap_batch_fn guarantees ret == 0 */
	BUG_ON(traverse_pages_block(m.num, माप(xen_pfn_t),
				    &pagelist, mmap_batch_fn, &state));

	mmap_ग_लिखो_unlock(mm);

	अगर (state.global_error) अणु
		/* Write back errors in second pass. */
		state.user_gfn = (xen_pfn_t *)m.arr;
		state.user_err = m.err;
		ret = traverse_pages_block(m.num, माप(xen_pfn_t),
					   &pagelist, mmap_वापस_errors, &state);
	पूर्ण अन्यथा
		ret = 0;

	/* If we have not had any EFAULT-like global errors then set the global
	 * error to -ENOENT अगर necessary. */
	अगर ((ret == 0) && (state.global_error == -ENOENT))
		ret = -ENOENT;

out:
	मुक्त_page_list(&pagelist);
	वापस ret;

out_unlock:
	mmap_ग_लिखो_unlock(mm);
	जाओ out;
पूर्ण

अटल पूर्णांक lock_pages(
	काष्ठा privcmd_dm_op_buf kbufs[], अचिन्हित पूर्णांक num,
	काष्ठा page *pages[], अचिन्हित पूर्णांक nr_pages, अचिन्हित पूर्णांक *pinned)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		अचिन्हित पूर्णांक requested;
		पूर्णांक page_count;

		requested = DIV_ROUND_UP(
			offset_in_page(kbufs[i].uptr) + kbufs[i].size,
			PAGE_SIZE);
		अगर (requested > nr_pages)
			वापस -ENOSPC;

		page_count = pin_user_pages_fast(
			(अचिन्हित दीर्घ) kbufs[i].uptr,
			requested, FOLL_WRITE, pages);
		अगर (page_count < 0)
			वापस page_count;

		*pinned += page_count;
		nr_pages -= page_count;
		pages += page_count;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम unlock_pages(काष्ठा page *pages[], अचिन्हित पूर्णांक nr_pages)
अणु
	unpin_user_pages_dirty_lock(pages, nr_pages, true);
पूर्ण

अटल दीर्घ privcmd_ioctl_dm_op(काष्ठा file *file, व्योम __user *udata)
अणु
	काष्ठा privcmd_data *data = file->निजी_data;
	काष्ठा privcmd_dm_op kdata;
	काष्ठा privcmd_dm_op_buf *kbufs;
	अचिन्हित पूर्णांक nr_pages = 0;
	काष्ठा page **pages = शून्य;
	काष्ठा xen_dm_op_buf *xbufs = शून्य;
	अचिन्हित पूर्णांक i;
	दीर्घ rc;
	अचिन्हित पूर्णांक pinned = 0;

	अगर (copy_from_user(&kdata, udata, माप(kdata)))
		वापस -EFAULT;

	/* If restriction is in place, check the करोmid matches */
	अगर (data->करोmid != DOMID_INVALID && data->करोmid != kdata.करोm)
		वापस -EPERM;

	अगर (kdata.num == 0)
		वापस 0;

	अगर (kdata.num > privcmd_dm_op_max_num)
		वापस -E2BIG;

	kbufs = kसुस्मृति(kdata.num, माप(*kbufs), GFP_KERNEL);
	अगर (!kbufs)
		वापस -ENOMEM;

	अगर (copy_from_user(kbufs, kdata.ubufs,
			   माप(*kbufs) * kdata.num)) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < kdata.num; i++) अणु
		अगर (kbufs[i].size > privcmd_dm_op_buf_max_size) अणु
			rc = -E2BIG;
			जाओ out;
		पूर्ण

		अगर (!access_ok(kbufs[i].uptr,
			       kbufs[i].size)) अणु
			rc = -EFAULT;
			जाओ out;
		पूर्ण

		nr_pages += DIV_ROUND_UP(
			offset_in_page(kbufs[i].uptr) + kbufs[i].size,
			PAGE_SIZE);
	पूर्ण

	pages = kसुस्मृति(nr_pages, माप(*pages), GFP_KERNEL);
	अगर (!pages) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	xbufs = kसुस्मृति(kdata.num, माप(*xbufs), GFP_KERNEL);
	अगर (!xbufs) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	rc = lock_pages(kbufs, kdata.num, pages, nr_pages, &pinned);
	अगर (rc < 0) अणु
		nr_pages = pinned;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < kdata.num; i++) अणु
		set_xen_guest_handle(xbufs[i].h, kbufs[i].uptr);
		xbufs[i].size = kbufs[i].size;
	पूर्ण

	xen_preemptible_hcall_begin();
	rc = HYPERVISOR_dm_op(kdata.करोm, kdata.num, xbufs);
	xen_preemptible_hcall_end();

out:
	unlock_pages(pages, nr_pages);
	kमुक्त(xbufs);
	kमुक्त(pages);
	kमुक्त(kbufs);

	वापस rc;
पूर्ण

अटल दीर्घ privcmd_ioctl_restrict(काष्ठा file *file, व्योम __user *udata)
अणु
	काष्ठा privcmd_data *data = file->निजी_data;
	करोmid_t करोm;

	अगर (copy_from_user(&करोm, udata, माप(करोm)))
		वापस -EFAULT;

	/* Set restriction to the specअगरied करोमुख्य, or check it matches */
	अगर (data->करोmid == DOMID_INVALID)
		data->करोmid = करोm;
	अन्यथा अगर (data->करोmid != करोm)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल दीर्घ privcmd_ioctl_mmap_resource(काष्ठा file *file,
				काष्ठा privcmd_mmap_resource __user *udata)
अणु
	काष्ठा privcmd_data *data = file->निजी_data;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा privcmd_mmap_resource kdata;
	xen_pfn_t *pfns = शून्य;
	काष्ठा xen_mem_acquire_resource xdata = अणु पूर्ण;
	पूर्णांक rc;

	अगर (copy_from_user(&kdata, udata, माप(kdata)))
		वापस -EFAULT;

	/* If restriction is in place, check the करोmid matches */
	अगर (data->करोmid != DOMID_INVALID && data->करोmid != kdata.करोm)
		वापस -EPERM;

	/* Both fields must be set or unset */
	अगर (!!kdata.addr != !!kdata.num)
		वापस -EINVAL;

	xdata.करोmid = kdata.करोm;
	xdata.type = kdata.type;
	xdata.id = kdata.id;

	अगर (!kdata.addr && !kdata.num) अणु
		/* Query the size of the resource. */
		rc = HYPERVISOR_memory_op(XENMEM_acquire_resource, &xdata);
		अगर (rc)
			वापस rc;
		वापस __put_user(xdata.nr_frames, &udata->num);
	पूर्ण

	mmap_ग_लिखो_lock(mm);

	vma = find_vma(mm, kdata.addr);
	अगर (!vma || vma->vm_ops != &privcmd_vm_ops) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	pfns = kसुस्मृति(kdata.num, माप(*pfns), GFP_KERNEL);
	अगर (!pfns) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_XEN_AUTO_XLATE) &&
	    xen_feature(XENFEAT_स्वतः_translated_physmap)) अणु
		अचिन्हित पूर्णांक nr = DIV_ROUND_UP(kdata.num, XEN_PFN_PER_PAGE);
		काष्ठा page **pages;
		अचिन्हित पूर्णांक i;

		rc = alloc_empty_pages(vma, nr);
		अगर (rc < 0)
			जाओ out;

		pages = vma->vm_निजी_data;
		क्रम (i = 0; i < kdata.num; i++) अणु
			xen_pfn_t pfn =
				page_to_xen_pfn(pages[i / XEN_PFN_PER_PAGE]);

			pfns[i] = pfn + (i % XEN_PFN_PER_PAGE);
		पूर्ण
	पूर्ण अन्यथा
		vma->vm_निजी_data = PRIV_VMA_LOCKED;

	xdata.frame = kdata.idx;
	xdata.nr_frames = kdata.num;
	set_xen_guest_handle(xdata.frame_list, pfns);

	xen_preemptible_hcall_begin();
	rc = HYPERVISOR_memory_op(XENMEM_acquire_resource, &xdata);
	xen_preemptible_hcall_end();

	अगर (rc)
		जाओ out;

	अगर (IS_ENABLED(CONFIG_XEN_AUTO_XLATE) &&
	    xen_feature(XENFEAT_स्वतः_translated_physmap)) अणु
		rc = xen_remap_vma_range(vma, kdata.addr, kdata.num << PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक करोmid =
			(xdata.flags & XENMEM_rsrc_acq_caller_owned) ?
			DOMID_SELF : kdata.करोm;
		पूर्णांक num;

		num = xen_remap_करोमुख्य_mfn_array(vma,
						 kdata.addr & PAGE_MASK,
						 pfns, kdata.num, (पूर्णांक *)pfns,
						 vma->vm_page_prot,
						 करोmid,
						 vma->vm_निजी_data);
		अगर (num < 0)
			rc = num;
		अन्यथा अगर (num != kdata.num) अणु
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < num; i++) अणु
				rc = pfns[i];
				अगर (rc < 0)
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			rc = 0;
	पूर्ण

out:
	mmap_ग_लिखो_unlock(mm);
	kमुक्त(pfns);

	वापस rc;
पूर्ण

अटल दीर्घ privcmd_ioctl(काष्ठा file *file,
			  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ data)
अणु
	पूर्णांक ret = -ENOTTY;
	व्योम __user *udata = (व्योम __user *) data;

	चयन (cmd) अणु
	हाल IOCTL_PRIVCMD_HYPERCALL:
		ret = privcmd_ioctl_hypercall(file, udata);
		अवरोध;

	हाल IOCTL_PRIVCMD_MMAP:
		ret = privcmd_ioctl_mmap(file, udata);
		अवरोध;

	हाल IOCTL_PRIVCMD_MMAPBATCH:
		ret = privcmd_ioctl_mmap_batch(file, udata, 1);
		अवरोध;

	हाल IOCTL_PRIVCMD_MMAPBATCH_V2:
		ret = privcmd_ioctl_mmap_batch(file, udata, 2);
		अवरोध;

	हाल IOCTL_PRIVCMD_DM_OP:
		ret = privcmd_ioctl_dm_op(file, udata);
		अवरोध;

	हाल IOCTL_PRIVCMD_RESTRICT:
		ret = privcmd_ioctl_restrict(file, udata);
		अवरोध;

	हाल IOCTL_PRIVCMD_MMAP_RESOURCE:
		ret = privcmd_ioctl_mmap_resource(file, udata);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक privcmd_खोलो(काष्ठा inode *ino, काष्ठा file *file)
अणु
	काष्ठा privcmd_data *data = kzalloc(माप(*data), GFP_KERNEL);

	अगर (!data)
		वापस -ENOMEM;

	/* DOMID_INVALID implies no restriction */
	data->करोmid = DOMID_INVALID;

	file->निजी_data = data;
	वापस 0;
पूर्ण

अटल पूर्णांक privcmd_release(काष्ठा inode *ino, काष्ठा file *file)
अणु
	काष्ठा privcmd_data *data = file->निजी_data;

	kमुक्त(data);
	वापस 0;
पूर्ण

अटल व्योम privcmd_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा page **pages = vma->vm_निजी_data;
	पूर्णांक numpgs = vma_pages(vma);
	पूर्णांक numgfns = (vma->vm_end - vma->vm_start) >> XEN_PAGE_SHIFT;
	पूर्णांक rc;

	अगर (!xen_feature(XENFEAT_स्वतः_translated_physmap) || !numpgs || !pages)
		वापस;

	rc = xen_unmap_करोमुख्य_gfn_range(vma, numgfns, pages);
	अगर (rc == 0)
		xen_मुक्त_unpopulated_pages(numpgs, pages);
	अन्यथा
		pr_crit("unable to unmap MFN range: leaking %d pages. rc=%d\n",
			numpgs, rc);
	kमुक्त(pages);
पूर्ण

अटल vm_fault_t privcmd_fault(काष्ठा vm_fault *vmf)
अणु
	prपूर्णांकk(KERN_DEBUG "privcmd_fault: vma=%p %lx-%lx, pgoff=%lx, uv=%p\n",
	       vmf->vma, vmf->vma->vm_start, vmf->vma->vm_end,
	       vmf->pgoff, (व्योम *)vmf->address);

	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा privcmd_vm_ops = अणु
	.बंद = privcmd_बंद,
	.fault = privcmd_fault
पूर्ण;

अटल पूर्णांक privcmd_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	/* DONTCOPY is essential क्रम Xen because copy_page_range करोesn't know
	 * how to recreate these mappings */
	vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTCOPY |
			 VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &privcmd_vm_ops;
	vma->vm_निजी_data = शून्य;

	वापस 0;
पूर्ण

/*
 * For MMAPBATCH*. This allows निश्चितing the singleshot mapping
 * on a per pfn/pte basis. Mapping calls that fail with ENOENT
 * can be then retried until success.
 */
अटल पूर्णांक is_mapped_fn(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	वापस pte_none(*pte) ? 0 : -EBUSY;
पूर्ण

अटल पूर्णांक privcmd_vma_range_is_mapped(
	           काष्ठा vm_area_काष्ठा *vma,
	           अचिन्हित दीर्घ addr,
	           अचिन्हित दीर्घ nr_pages)
अणु
	वापस apply_to_page_range(vma->vm_mm, addr, nr_pages << PAGE_SHIFT,
				   is_mapped_fn, शून्य) != 0;
पूर्ण

स्थिर काष्ठा file_operations xen_privcmd_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = privcmd_ioctl,
	.खोलो = privcmd_खोलो,
	.release = privcmd_release,
	.mmap = privcmd_mmap,
पूर्ण;
EXPORT_SYMBOL_GPL(xen_privcmd_fops);

अटल काष्ठा miscdevice privcmd_dev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "xen/privcmd",
	.fops = &xen_privcmd_fops,
पूर्ण;

अटल पूर्णांक __init privcmd_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	err = misc_रेजिस्टर(&privcmd_dev);
	अगर (err != 0) अणु
		pr_err("Could not register Xen privcmd device\n");
		वापस err;
	पूर्ण

	err = misc_रेजिस्टर(&xen_privcmdbuf_dev);
	अगर (err != 0) अणु
		pr_err("Could not register Xen hypercall-buf device\n");
		misc_deरेजिस्टर(&privcmd_dev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास privcmd_निकास(व्योम)
अणु
	misc_deरेजिस्टर(&privcmd_dev);
	misc_deरेजिस्टर(&xen_privcmdbuf_dev);
पूर्ण

module_init(privcmd_init);
module_निकास(privcmd_निकास);
