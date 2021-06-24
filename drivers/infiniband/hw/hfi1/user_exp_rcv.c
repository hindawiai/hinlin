<शैली गुरु>
/*
 * Copyright(c) 2020 Cornelis Networks, Inc.
 * Copyright(c) 2015-2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#समावेश <यंत्र/page.h>
#समावेश <linux/माला.स>

#समावेश "mmu_rb.h"
#समावेश "user_exp_rcv.h"
#समावेश "trace.h"

अटल व्योम unlock_exp_tids(काष्ठा hfi1_ctxtdata *uctxt,
			    काष्ठा exp_tid_set *set,
			    काष्ठा hfi1_filedata *fd);
अटल u32 find_phys_blocks(काष्ठा tid_user_buf *tidbuf, अचिन्हित पूर्णांक npages);
अटल पूर्णांक set_rcvarray_entry(काष्ठा hfi1_filedata *fd,
			      काष्ठा tid_user_buf *tbuf,
			      u32 rcventry, काष्ठा tid_group *grp,
			      u16 pageidx, अचिन्हित पूर्णांक npages);
अटल व्योम cacheless_tid_rb_हटाओ(काष्ठा hfi1_filedata *fdata,
				    काष्ठा tid_rb_node *tnode);
अटल bool tid_rb_invalidate(काष्ठा mmu_पूर्णांकerval_notअगरier *mni,
			      स्थिर काष्ठा mmu_notअगरier_range *range,
			      अचिन्हित दीर्घ cur_seq);
अटल पूर्णांक program_rcvarray(काष्ठा hfi1_filedata *fd, काष्ठा tid_user_buf *,
			    काष्ठा tid_group *grp,
			    अचिन्हित पूर्णांक start, u16 count,
			    u32 *tidlist, अचिन्हित पूर्णांक *tididx,
			    अचिन्हित पूर्णांक *pmapped);
अटल पूर्णांक unprogram_rcvarray(काष्ठा hfi1_filedata *fd, u32 tidinfo,
			      काष्ठा tid_group **grp);
अटल व्योम clear_tid_node(काष्ठा hfi1_filedata *fd, काष्ठा tid_rb_node *node);

अटल स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops tid_mn_ops = अणु
	.invalidate = tid_rb_invalidate,
पूर्ण;

/*
 * Initialize context and file निजी data needed क्रम Expected
 * receive caching. This needs to be करोne after the context has
 * been configured with the eager/expected RcvEntry counts.
 */
पूर्णांक hfi1_user_exp_rcv_init(काष्ठा hfi1_filedata *fd,
			   काष्ठा hfi1_ctxtdata *uctxt)
अणु
	पूर्णांक ret = 0;

	fd->entry_to_rb = kसुस्मृति(uctxt->expected_count,
				  माप(काष्ठा rb_node *),
				  GFP_KERNEL);
	अगर (!fd->entry_to_rb)
		वापस -ENOMEM;

	अगर (!HFI1_CAP_UGET_MASK(uctxt->flags, TID_UNMAP)) अणु
		fd->invalid_tid_idx = 0;
		fd->invalid_tids = kसुस्मृति(uctxt->expected_count,
					   माप(*fd->invalid_tids),
					   GFP_KERNEL);
		अगर (!fd->invalid_tids) अणु
			kमुक्त(fd->entry_to_rb);
			fd->entry_to_rb = शून्य;
			वापस -ENOMEM;
		पूर्ण
		fd->use_mn = true;
	पूर्ण

	/*
	 * PSM करोes not have a good way to separate, count, and
	 * effectively enक्रमce a limit on RcvArray entries used by
	 * subctxts (when context sharing is used) when TID caching
	 * is enabled. To help with that, we calculate a per-process
	 * RcvArray entry share and enक्रमce that.
	 * If TID caching is not in use, PSM deals with usage on its
	 * own. In that हाल, we allow any subctxt to take all of the
	 * entries.
	 *
	 * Make sure that we set the tid counts only after successful
	 * init.
	 */
	spin_lock(&fd->tid_lock);
	अगर (uctxt->subctxt_cnt && fd->use_mn) अणु
		u16 reमुख्यder;

		fd->tid_limit = uctxt->expected_count / uctxt->subctxt_cnt;
		reमुख्यder = uctxt->expected_count % uctxt->subctxt_cnt;
		अगर (reमुख्यder && fd->subctxt < reमुख्यder)
			fd->tid_limit++;
	पूर्ण अन्यथा अणु
		fd->tid_limit = uctxt->expected_count;
	पूर्ण
	spin_unlock(&fd->tid_lock);

	वापस ret;
पूर्ण

व्योम hfi1_user_exp_rcv_मुक्त(काष्ठा hfi1_filedata *fd)
अणु
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;

	mutex_lock(&uctxt->exp_mutex);
	अगर (!EXP_TID_SET_EMPTY(uctxt->tid_full_list))
		unlock_exp_tids(uctxt, &uctxt->tid_full_list, fd);
	अगर (!EXP_TID_SET_EMPTY(uctxt->tid_used_list))
		unlock_exp_tids(uctxt, &uctxt->tid_used_list, fd);
	mutex_unlock(&uctxt->exp_mutex);

	kमुक्त(fd->invalid_tids);
	fd->invalid_tids = शून्य;

	kमुक्त(fd->entry_to_rb);
	fd->entry_to_rb = शून्य;
पूर्ण

/*
 * Release pinned receive buffer pages.
 *
 * @mapped: true अगर the pages have been DMA mapped. false otherwise.
 * @idx: Index of the first page to unpin.
 * @npages: No of pages to unpin.
 *
 * If the pages have been DMA mapped (indicated by mapped parameter), their
 * info will be passed via a काष्ठा tid_rb_node. If they haven't been mapped,
 * their info will be passed via a काष्ठा tid_user_buf.
 */
अटल व्योम unpin_rcv_pages(काष्ठा hfi1_filedata *fd,
			    काष्ठा tid_user_buf *tidbuf,
			    काष्ठा tid_rb_node *node,
			    अचिन्हित पूर्णांक idx,
			    अचिन्हित पूर्णांक npages,
			    bool mapped)
अणु
	काष्ठा page **pages;
	काष्ठा hfi1_devdata *dd = fd->uctxt->dd;
	काष्ठा mm_काष्ठा *mm;

	अगर (mapped) अणु
		pci_unmap_single(dd->pcidev, node->dma_addr,
				 node->npages * PAGE_SIZE, PCI_DMA_FROMDEVICE);
		pages = &node->pages[idx];
		mm = mm_from_tid_node(node);
	पूर्ण अन्यथा अणु
		pages = &tidbuf->pages[idx];
		mm = current->mm;
	पूर्ण
	hfi1_release_user_pages(mm, pages, npages, mapped);
	fd->tid_n_pinned -= npages;
पूर्ण

/*
 * Pin receive buffer pages.
 */
अटल पूर्णांक pin_rcv_pages(काष्ठा hfi1_filedata *fd, काष्ठा tid_user_buf *tidbuf)
अणु
	पूर्णांक pinned;
	अचिन्हित पूर्णांक npages;
	अचिन्हित दीर्घ vaddr = tidbuf->vaddr;
	काष्ठा page **pages = शून्य;
	काष्ठा hfi1_devdata *dd = fd->uctxt->dd;

	/* Get the number of pages the user buffer spans */
	npages = num_user_pages(vaddr, tidbuf->length);
	अगर (!npages)
		वापस -EINVAL;

	अगर (npages > fd->uctxt->expected_count) अणु
		dd_dev_err(dd, "Expected buffer too big\n");
		वापस -EINVAL;
	पूर्ण

	/* Allocate the array of काष्ठा page poपूर्णांकers needed क्रम pinning */
	pages = kसुस्मृति(npages, माप(*pages), GFP_KERNEL);
	अगर (!pages)
		वापस -ENOMEM;

	/*
	 * Pin all the pages of the user buffer. If we can't pin all the
	 * pages, accept the amount pinned so far and program only that.
	 * User space knows how to deal with partially programmed buffers.
	 */
	अगर (!hfi1_can_pin_pages(dd, current->mm, fd->tid_n_pinned, npages)) अणु
		kमुक्त(pages);
		वापस -ENOMEM;
	पूर्ण

	pinned = hfi1_acquire_user_pages(current->mm, vaddr, npages, true, pages);
	अगर (pinned <= 0) अणु
		kमुक्त(pages);
		वापस pinned;
	पूर्ण
	tidbuf->pages = pages;
	tidbuf->npages = npages;
	fd->tid_n_pinned += pinned;
	वापस pinned;
पूर्ण

/*
 * RcvArray entry allocation क्रम Expected Receives is करोne by the
 * following algorithm:
 *
 * The context keeps 3 lists of groups of RcvArray entries:
 *   1. List of empty groups - tid_group_list
 *      This list is created during user context creation and
 *      contains elements which describe sets (of 8) of empty
 *      RcvArray entries.
 *   2. List of partially used groups - tid_used_list
 *      This list contains sets of RcvArray entries which are
 *      not completely used up. Another mapping request could
 *      use some of all of the reमुख्यing entries.
 *   3. List of full groups - tid_full_list
 *      This is the list where sets that are completely used
 *      up go.
 *
 * An attempt to optimize the usage of RcvArray entries is
 * made by finding all sets of physically contiguous pages in a
 * user's buffer.
 * These physically contiguous sets are further split पूर्णांकo
 * sizes supported by the receive engine of the HFI. The
 * resulting sets of pages are stored in काष्ठा tid_pageset,
 * which describes the sets as:
 *    * .count - number of pages in this set
 *    * .idx - starting index पूर्णांकo काष्ठा page ** array
 *                    of this set
 *
 * From this poपूर्णांक on, the algorithm deals with the page sets
 * described above. The number of pagesets is भागided by the
 * RcvArray group size to produce the number of full groups
 * needed.
 *
 * Groups from the 3 lists are manipulated using the following
 * rules:
 *   1. For each set of 8 pagesets, a complete group from
 *      tid_group_list is taken, programmed, and moved to
 *      the tid_full_list list.
 *   2. For all reमुख्यing pagesets:
 *      2.1 If the tid_used_list is empty and the tid_group_list
 *          is empty, stop processing pageset and वापस only
 *          what has been programmed up to this poपूर्णांक.
 *      2.2 If the tid_used_list is empty and the tid_group_list
 *          is not empty, move a group from tid_group_list to
 *          tid_used_list.
 *      2.3 For each group is tid_used_group, program as much as
 *          can fit पूर्णांकo the group. If the group becomes fully
 *          used, move it to tid_full_list.
 */
पूर्णांक hfi1_user_exp_rcv_setup(काष्ठा hfi1_filedata *fd,
			    काष्ठा hfi1_tid_info *tinfo)
अणु
	पूर्णांक ret = 0, need_group = 0, pinned;
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	अचिन्हित पूर्णांक ngroups, pageidx = 0, pageset_count,
		tididx = 0, mapped, mapped_pages = 0;
	u32 *tidlist = शून्य;
	काष्ठा tid_user_buf *tidbuf;

	अगर (!PAGE_ALIGNED(tinfo->vaddr))
		वापस -EINVAL;

	tidbuf = kzalloc(माप(*tidbuf), GFP_KERNEL);
	अगर (!tidbuf)
		वापस -ENOMEM;

	tidbuf->vaddr = tinfo->vaddr;
	tidbuf->length = tinfo->length;
	tidbuf->psets = kसुस्मृति(uctxt->expected_count, माप(*tidbuf->psets),
				GFP_KERNEL);
	अगर (!tidbuf->psets) अणु
		kमुक्त(tidbuf);
		वापस -ENOMEM;
	पूर्ण

	pinned = pin_rcv_pages(fd, tidbuf);
	अगर (pinned <= 0) अणु
		kमुक्त(tidbuf->psets);
		kमुक्त(tidbuf);
		वापस pinned;
	पूर्ण

	/* Find sets of physically contiguous pages */
	tidbuf->n_psets = find_phys_blocks(tidbuf, pinned);

	/*
	 * We करोn't need to access this under a lock since tid_used is per
	 * process and the same process cannot be in hfi1_user_exp_rcv_clear()
	 * and hfi1_user_exp_rcv_setup() at the same समय.
	 */
	spin_lock(&fd->tid_lock);
	अगर (fd->tid_used + tidbuf->n_psets > fd->tid_limit)
		pageset_count = fd->tid_limit - fd->tid_used;
	अन्यथा
		pageset_count = tidbuf->n_psets;
	spin_unlock(&fd->tid_lock);

	अगर (!pageset_count)
		जाओ bail;

	ngroups = pageset_count / dd->rcv_entries.group_size;
	tidlist = kसुस्मृति(pageset_count, माप(*tidlist), GFP_KERNEL);
	अगर (!tidlist) अणु
		ret = -ENOMEM;
		जाओ nomem;
	पूर्ण

	tididx = 0;

	/*
	 * From this poपूर्णांक on, we are going to be using shared (between master
	 * and subcontexts) context resources. We need to take the lock.
	 */
	mutex_lock(&uctxt->exp_mutex);
	/*
	 * The first step is to program the RcvArray entries which are complete
	 * groups.
	 */
	जबतक (ngroups && uctxt->tid_group_list.count) अणु
		काष्ठा tid_group *grp =
			tid_group_pop(&uctxt->tid_group_list);

		ret = program_rcvarray(fd, tidbuf, grp,
				       pageidx, dd->rcv_entries.group_size,
				       tidlist, &tididx, &mapped);
		/*
		 * If there was a failure to program the RcvArray
		 * entries क्रम the entire group, reset the grp fields
		 * and add the grp back to the मुक्त group list.
		 */
		अगर (ret <= 0) अणु
			tid_group_add_tail(grp, &uctxt->tid_group_list);
			hfi1_cdbg(TID,
				  "Failed to program RcvArray group %d", ret);
			जाओ unlock;
		पूर्ण

		tid_group_add_tail(grp, &uctxt->tid_full_list);
		ngroups--;
		pageidx += ret;
		mapped_pages += mapped;
	पूर्ण

	जबतक (pageidx < pageset_count) अणु
		काष्ठा tid_group *grp, *ptr;
		/*
		 * If we करोn't have any partially used tid groups, check
		 * अगर we have empty groups. If so, take one from there and
		 * put in the partially used list.
		 */
		अगर (!uctxt->tid_used_list.count || need_group) अणु
			अगर (!uctxt->tid_group_list.count)
				जाओ unlock;

			grp = tid_group_pop(&uctxt->tid_group_list);
			tid_group_add_tail(grp, &uctxt->tid_used_list);
			need_group = 0;
		पूर्ण
		/*
		 * There is an optimization opportunity here - instead of
		 * fitting as many page sets as we can, check क्रम a group
		 * later on in the list that could fit all of them.
		 */
		list_क्रम_each_entry_safe(grp, ptr, &uctxt->tid_used_list.list,
					 list) अणु
			अचिन्हित use = min_t(अचिन्हित, pageset_count - pageidx,
					     grp->size - grp->used);

			ret = program_rcvarray(fd, tidbuf, grp,
					       pageidx, use, tidlist,
					       &tididx, &mapped);
			अगर (ret < 0) अणु
				hfi1_cdbg(TID,
					  "Failed to program RcvArray entries %d",
					  ret);
				जाओ unlock;
			पूर्ण अन्यथा अगर (ret > 0) अणु
				अगर (grp->used == grp->size)
					tid_group_move(grp,
						       &uctxt->tid_used_list,
						       &uctxt->tid_full_list);
				pageidx += ret;
				mapped_pages += mapped;
				need_group = 0;
				/* Check अगर we are करोne so we अवरोध out early */
				अगर (pageidx >= pageset_count)
					अवरोध;
			पूर्ण अन्यथा अगर (WARN_ON(ret == 0)) अणु
				/*
				 * If ret is 0, we did not program any entries
				 * पूर्णांकo this group, which can only happen अगर
				 * we've screwed up the accounting somewhere.
				 * Warn and try to जारी.
				 */
				need_group = 1;
			पूर्ण
		पूर्ण
	पूर्ण
unlock:
	mutex_unlock(&uctxt->exp_mutex);
nomem:
	hfi1_cdbg(TID, "total mapped: tidpairs:%u pages:%u (%d)", tididx,
		  mapped_pages, ret);
	अगर (tididx) अणु
		spin_lock(&fd->tid_lock);
		fd->tid_used += tididx;
		spin_unlock(&fd->tid_lock);
		tinfo->tidcnt = tididx;
		tinfo->length = mapped_pages * PAGE_SIZE;

		अगर (copy_to_user(u64_to_user_ptr(tinfo->tidlist),
				 tidlist, माप(tidlist[0]) * tididx)) अणु
			/*
			 * On failure to copy to the user level, we need to unकरो
			 * everything करोne so far so we करोn't leak resources.
			 */
			tinfo->tidlist = (अचिन्हित दीर्घ)&tidlist;
			hfi1_user_exp_rcv_clear(fd, tinfo);
			tinfo->tidlist = 0;
			ret = -EFAULT;
			जाओ bail;
		पूर्ण
	पूर्ण

	/*
	 * If not everything was mapped (due to insufficient RcvArray entries,
	 * क्रम example), unpin all unmapped pages so we can pin them nex समय.
	 */
	अगर (mapped_pages != pinned)
		unpin_rcv_pages(fd, tidbuf, शून्य, mapped_pages,
				(pinned - mapped_pages), false);
bail:
	kमुक्त(tidbuf->psets);
	kमुक्त(tidlist);
	kमुक्त(tidbuf->pages);
	kमुक्त(tidbuf);
	वापस ret > 0 ? 0 : ret;
पूर्ण

पूर्णांक hfi1_user_exp_rcv_clear(काष्ठा hfi1_filedata *fd,
			    काष्ठा hfi1_tid_info *tinfo)
अणु
	पूर्णांक ret = 0;
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	u32 *tidinfo;
	अचिन्हित tididx;

	अगर (unlikely(tinfo->tidcnt > fd->tid_used))
		वापस -EINVAL;

	tidinfo = memdup_user(u64_to_user_ptr(tinfo->tidlist),
			      माप(tidinfo[0]) * tinfo->tidcnt);
	अगर (IS_ERR(tidinfo))
		वापस PTR_ERR(tidinfo);

	mutex_lock(&uctxt->exp_mutex);
	क्रम (tididx = 0; tididx < tinfo->tidcnt; tididx++) अणु
		ret = unprogram_rcvarray(fd, tidinfo[tididx], शून्य);
		अगर (ret) अणु
			hfi1_cdbg(TID, "Failed to unprogram rcv array %d",
				  ret);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_lock(&fd->tid_lock);
	fd->tid_used -= tididx;
	spin_unlock(&fd->tid_lock);
	tinfo->tidcnt = tididx;
	mutex_unlock(&uctxt->exp_mutex);

	kमुक्त(tidinfo);
	वापस ret;
पूर्ण

पूर्णांक hfi1_user_exp_rcv_invalid(काष्ठा hfi1_filedata *fd,
			      काष्ठा hfi1_tid_info *tinfo)
अणु
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	अचिन्हित दीर्घ *ev = uctxt->dd->events +
		(uctxt_offset(uctxt) + fd->subctxt);
	u32 *array;
	पूर्णांक ret = 0;

	/*
	 * copy_to_user() can sleep, which will leave the invalid_lock
	 * locked and cause the MMU notअगरier to be blocked on the lock
	 * क्रम a दीर्घ समय.
	 * Copy the data to a local buffer so we can release the lock.
	 */
	array = kसुस्मृति(uctxt->expected_count, माप(*array), GFP_KERNEL);
	अगर (!array)
		वापस -EFAULT;

	spin_lock(&fd->invalid_lock);
	अगर (fd->invalid_tid_idx) अणु
		स_नकल(array, fd->invalid_tids, माप(*array) *
		       fd->invalid_tid_idx);
		स_रखो(fd->invalid_tids, 0, माप(*fd->invalid_tids) *
		       fd->invalid_tid_idx);
		tinfo->tidcnt = fd->invalid_tid_idx;
		fd->invalid_tid_idx = 0;
		/*
		 * Reset the user flag जबतक still holding the lock.
		 * Otherwise, PSM can miss events.
		 */
		clear_bit(_HFI1_EVENT_TID_MMU_NOTIFY_BIT, ev);
	पूर्ण अन्यथा अणु
		tinfo->tidcnt = 0;
	पूर्ण
	spin_unlock(&fd->invalid_lock);

	अगर (tinfo->tidcnt) अणु
		अगर (copy_to_user((व्योम __user *)tinfo->tidlist,
				 array, माप(*array) * tinfo->tidcnt))
			ret = -EFAULT;
	पूर्ण
	kमुक्त(array);

	वापस ret;
पूर्ण

अटल u32 find_phys_blocks(काष्ठा tid_user_buf *tidbuf, अचिन्हित पूर्णांक npages)
अणु
	अचिन्हित pagecount, pageidx, setcount = 0, i;
	अचिन्हित दीर्घ pfn, this_pfn;
	काष्ठा page **pages = tidbuf->pages;
	काष्ठा tid_pageset *list = tidbuf->psets;

	अगर (!npages)
		वापस 0;

	/*
	 * Look क्रम sets of physically contiguous pages in the user buffer.
	 * This will allow us to optimize Expected RcvArray entry usage by
	 * using the bigger supported sizes.
	 */
	pfn = page_to_pfn(pages[0]);
	क्रम (pageidx = 0, pagecount = 1, i = 1; i <= npages; i++) अणु
		this_pfn = i < npages ? page_to_pfn(pages[i]) : 0;

		/*
		 * If the pfn's are not sequential, pages are not physically
		 * contiguous.
		 */
		अगर (this_pfn != ++pfn) अणु
			/*
			 * At this poपूर्णांक we have to loop over the set of
			 * physically contiguous pages and अवरोध them करोwn it
			 * sizes supported by the HW.
			 * There are two मुख्य स्थिरraपूर्णांकs:
			 *     1. The max buffer size is MAX_EXPECTED_BUFFER.
			 *        If the total set size is bigger than that
			 *        program only a MAX_EXPECTED_BUFFER chunk.
			 *     2. The buffer size has to be a घातer of two. If
			 *        it is not, round करोwn to the बंदs घातer of
			 *        2 and program that size.
			 */
			जबतक (pagecount) अणु
				पूर्णांक maxpages = pagecount;
				u32 bufsize = pagecount * PAGE_SIZE;

				अगर (bufsize > MAX_EXPECTED_BUFFER)
					maxpages =
						MAX_EXPECTED_BUFFER >>
						PAGE_SHIFT;
				अन्यथा अगर (!is_घातer_of_2(bufsize))
					maxpages =
						roundकरोwn_घात_of_two(bufsize) >>
						PAGE_SHIFT;

				list[setcount].idx = pageidx;
				list[setcount].count = maxpages;
				pagecount -= maxpages;
				pageidx += maxpages;
				setcount++;
			पूर्ण
			pageidx = i;
			pagecount = 1;
			pfn = this_pfn;
		पूर्ण अन्यथा अणु
			pagecount++;
		पूर्ण
	पूर्ण
	वापस setcount;
पूर्ण

/**
 * program_rcvarray() - program an RcvArray group with receive buffers
 * @fd: filedata poपूर्णांकer
 * @tbuf: poपूर्णांकer to काष्ठा tid_user_buf that has the user buffer starting
 *	  भव address, buffer length, page poपूर्णांकers, pagesets (array of
 *	  काष्ठा tid_pageset holding inक्रमmation on physically contiguous
 *	  chunks from the user buffer), and other fields.
 * @grp: RcvArray group
 * @start: starting index पूर्णांकo sets array
 * @count: number of काष्ठा tid_pageset's to program
 * @tidlist: the array of u32 elements when the inक्रमmation about the
 *           programmed RcvArray entries is to be encoded.
 * @tididx: starting offset पूर्णांकo tidlist
 * @pmapped: (output parameter) number of pages programmed पूर्णांकo the RcvArray
 *           entries.
 *
 * This function will program up to 'count' number of RcvArray entries from the
 * group 'grp'. To make best use of ग_लिखो-combining ग_लिखोs, the function will
 * perक्रमm ग_लिखोs to the unused RcvArray entries which will be ignored by the
 * HW. Each RcvArray entry will be programmed with a physically contiguous
 * buffer chunk from the user's भव buffer.
 *
 * Return:
 * -EINVAL अगर the requested count is larger than the size of the group,
 * -ENOMEM or -EFAULT on error from set_rcvarray_entry(), or
 * number of RcvArray entries programmed.
 */
अटल पूर्णांक program_rcvarray(काष्ठा hfi1_filedata *fd, काष्ठा tid_user_buf *tbuf,
			    काष्ठा tid_group *grp,
			    अचिन्हित पूर्णांक start, u16 count,
			    u32 *tidlist, अचिन्हित पूर्णांक *tididx,
			    अचिन्हित पूर्णांक *pmapped)
अणु
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	u16 idx;
	u32 tidinfo = 0, rcventry, useidx = 0;
	पूर्णांक mapped = 0;

	/* Count should never be larger than the group size */
	अगर (count > grp->size)
		वापस -EINVAL;

	/* Find the first unused entry in the group */
	क्रम (idx = 0; idx < grp->size; idx++) अणु
		अगर (!(grp->map & (1 << idx))) अणु
			useidx = idx;
			अवरोध;
		पूर्ण
		rcv_array_wc_fill(dd, grp->base + idx);
	पूर्ण

	idx = 0;
	जबतक (idx < count) अणु
		u16 npages, pageidx, setidx = start + idx;
		पूर्णांक ret = 0;

		/*
		 * If this entry in the group is used, move to the next one.
		 * If we go past the end of the group, निकास the loop.
		 */
		अगर (useidx >= grp->size) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (grp->map & (1 << useidx)) अणु
			rcv_array_wc_fill(dd, grp->base + useidx);
			useidx++;
			जारी;
		पूर्ण

		rcventry = grp->base + useidx;
		npages = tbuf->psets[setidx].count;
		pageidx = tbuf->psets[setidx].idx;

		ret = set_rcvarray_entry(fd, tbuf,
					 rcventry, grp, pageidx,
					 npages);
		अगर (ret)
			वापस ret;
		mapped += npages;

		tidinfo = rcventry2tidinfo(rcventry - uctxt->expected_base) |
			EXP_TID_SET(LEN, npages);
		tidlist[(*tididx)++] = tidinfo;
		grp->used++;
		grp->map |= 1 << useidx++;
		idx++;
	पूर्ण

	/* Fill the rest of the group with "blank" ग_लिखोs */
	क्रम (; useidx < grp->size; useidx++)
		rcv_array_wc_fill(dd, grp->base + useidx);
	*pmapped = mapped;
	वापस idx;
पूर्ण

अटल पूर्णांक set_rcvarray_entry(काष्ठा hfi1_filedata *fd,
			      काष्ठा tid_user_buf *tbuf,
			      u32 rcventry, काष्ठा tid_group *grp,
			      u16 pageidx, अचिन्हित पूर्णांक npages)
अणु
	पूर्णांक ret;
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	काष्ठा tid_rb_node *node;
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	dma_addr_t phys;
	काष्ठा page **pages = tbuf->pages + pageidx;

	/*
	 * Allocate the node first so we can handle a potential
	 * failure beक्रमe we've programmed anything.
	 */
	node = kzalloc(माप(*node) + (माप(काष्ठा page *) * npages),
		       GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	phys = pci_map_single(dd->pcidev,
			      __va(page_to_phys(pages[0])),
			      npages * PAGE_SIZE, PCI_DMA_FROMDEVICE);
	अगर (dma_mapping_error(&dd->pcidev->dev, phys)) अणु
		dd_dev_err(dd, "Failed to DMA map Exp Rcv pages 0x%llx\n",
			   phys);
		kमुक्त(node);
		वापस -EFAULT;
	पूर्ण

	node->fdata = fd;
	node->phys = page_to_phys(pages[0]);
	node->npages = npages;
	node->rcventry = rcventry;
	node->dma_addr = phys;
	node->grp = grp;
	node->मुक्तd = false;
	स_नकल(node->pages, pages, माप(काष्ठा page *) * npages);

	अगर (fd->use_mn) अणु
		ret = mmu_पूर्णांकerval_notअगरier_insert(
			&node->notअगरier, current->mm,
			tbuf->vaddr + (pageidx * PAGE_SIZE), npages * PAGE_SIZE,
			&tid_mn_ops);
		अगर (ret)
			जाओ out_unmap;
		/*
		 * FIXME: This is in the wrong order, the notअगरier should be
		 * established beक्रमe the pages are pinned by pin_rcv_pages.
		 */
		mmu_पूर्णांकerval_पढ़ो_begin(&node->notअगरier);
	पूर्ण
	fd->entry_to_rb[node->rcventry - uctxt->expected_base] = node;

	hfi1_put_tid(dd, rcventry, PT_EXPECTED, phys, ilog2(npages) + 1);
	trace_hfi1_exp_tid_reg(uctxt->ctxt, fd->subctxt, rcventry, npages,
			       node->notअगरier.पूर्णांकerval_tree.start, node->phys,
			       phys);
	वापस 0;

out_unmap:
	hfi1_cdbg(TID, "Failed to insert RB node %u 0x%lx, 0x%lx %d",
		  node->rcventry, node->notअगरier.पूर्णांकerval_tree.start,
		  node->phys, ret);
	pci_unmap_single(dd->pcidev, phys, npages * PAGE_SIZE,
			 PCI_DMA_FROMDEVICE);
	kमुक्त(node);
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक unprogram_rcvarray(काष्ठा hfi1_filedata *fd, u32 tidinfo,
			      काष्ठा tid_group **grp)
अणु
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	काष्ठा hfi1_devdata *dd = uctxt->dd;
	काष्ठा tid_rb_node *node;
	u8 tidctrl = EXP_TID_GET(tidinfo, CTRL);
	u32 tididx = EXP_TID_GET(tidinfo, IDX) << 1, rcventry;

	अगर (tididx >= uctxt->expected_count) अणु
		dd_dev_err(dd, "Invalid RcvArray entry (%u) index for ctxt %u\n",
			   tididx, uctxt->ctxt);
		वापस -EINVAL;
	पूर्ण

	अगर (tidctrl == 0x3)
		वापस -EINVAL;

	rcventry = tididx + (tidctrl - 1);

	node = fd->entry_to_rb[rcventry];
	अगर (!node || node->rcventry != (uctxt->expected_base + rcventry))
		वापस -EBADF;

	अगर (grp)
		*grp = node->grp;

	अगर (fd->use_mn)
		mmu_पूर्णांकerval_notअगरier_हटाओ(&node->notअगरier);
	cacheless_tid_rb_हटाओ(fd, node);

	वापस 0;
पूर्ण

अटल व्योम clear_tid_node(काष्ठा hfi1_filedata *fd, काष्ठा tid_rb_node *node)
अणु
	काष्ठा hfi1_ctxtdata *uctxt = fd->uctxt;
	काष्ठा hfi1_devdata *dd = uctxt->dd;

	trace_hfi1_exp_tid_unreg(uctxt->ctxt, fd->subctxt, node->rcventry,
				 node->npages,
				 node->notअगरier.पूर्णांकerval_tree.start, node->phys,
				 node->dma_addr);

	/*
	 * Make sure device has seen the ग_लिखो beक्रमe we unpin the
	 * pages.
	 */
	hfi1_put_tid(dd, node->rcventry, PT_INVALID_FLUSH, 0, 0);

	unpin_rcv_pages(fd, शून्य, node, 0, node->npages, true);

	node->grp->used--;
	node->grp->map &= ~(1 << (node->rcventry - node->grp->base));

	अगर (node->grp->used == node->grp->size - 1)
		tid_group_move(node->grp, &uctxt->tid_full_list,
			       &uctxt->tid_used_list);
	अन्यथा अगर (!node->grp->used)
		tid_group_move(node->grp, &uctxt->tid_used_list,
			       &uctxt->tid_group_list);
	kमुक्त(node);
पूर्ण

/*
 * As a simple helper क्रम hfi1_user_exp_rcv_मुक्त, this function deals with
 * clearing nodes in the non-cached हाल.
 */
अटल व्योम unlock_exp_tids(काष्ठा hfi1_ctxtdata *uctxt,
			    काष्ठा exp_tid_set *set,
			    काष्ठा hfi1_filedata *fd)
अणु
	काष्ठा tid_group *grp, *ptr;
	पूर्णांक i;

	list_क्रम_each_entry_safe(grp, ptr, &set->list, list) अणु
		list_del_init(&grp->list);

		क्रम (i = 0; i < grp->size; i++) अणु
			अगर (grp->map & (1 << i)) अणु
				u16 rcventry = grp->base + i;
				काष्ठा tid_rb_node *node;

				node = fd->entry_to_rb[rcventry -
							  uctxt->expected_base];
				अगर (!node || node->rcventry != rcventry)
					जारी;

				अगर (fd->use_mn)
					mmu_पूर्णांकerval_notअगरier_हटाओ(
						&node->notअगरier);
				cacheless_tid_rb_हटाओ(fd, node);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल bool tid_rb_invalidate(काष्ठा mmu_पूर्णांकerval_notअगरier *mni,
			      स्थिर काष्ठा mmu_notअगरier_range *range,
			      अचिन्हित दीर्घ cur_seq)
अणु
	काष्ठा tid_rb_node *node =
		container_of(mni, काष्ठा tid_rb_node, notअगरier);
	काष्ठा hfi1_filedata *fdata = node->fdata;
	काष्ठा hfi1_ctxtdata *uctxt = fdata->uctxt;

	अगर (node->मुक्तd)
		वापस true;

	trace_hfi1_exp_tid_inval(uctxt->ctxt, fdata->subctxt,
				 node->notअगरier.पूर्णांकerval_tree.start,
				 node->rcventry, node->npages, node->dma_addr);
	node->मुक्तd = true;

	spin_lock(&fdata->invalid_lock);
	अगर (fdata->invalid_tid_idx < uctxt->expected_count) अणु
		fdata->invalid_tids[fdata->invalid_tid_idx] =
			rcventry2tidinfo(node->rcventry - uctxt->expected_base);
		fdata->invalid_tids[fdata->invalid_tid_idx] |=
			EXP_TID_SET(LEN, node->npages);
		अगर (!fdata->invalid_tid_idx) अणु
			अचिन्हित दीर्घ *ev;

			/*
			 * hfi1_set_uevent_bits() sets a user event flag
			 * क्रम all processes. Because calling पूर्णांकo the
			 * driver to process TID cache invalidations is
			 * expensive and TID cache invalidations are
			 * handled on a per-process basis, we can
			 * optimize this to set the flag only क्रम the
			 * process in question.
			 */
			ev = uctxt->dd->events +
				(uctxt_offset(uctxt) + fdata->subctxt);
			set_bit(_HFI1_EVENT_TID_MMU_NOTIFY_BIT, ev);
		पूर्ण
		fdata->invalid_tid_idx++;
	पूर्ण
	spin_unlock(&fdata->invalid_lock);
	वापस true;
पूर्ण

अटल व्योम cacheless_tid_rb_हटाओ(काष्ठा hfi1_filedata *fdata,
				    काष्ठा tid_rb_node *tnode)
अणु
	u32 base = fdata->uctxt->expected_base;

	fdata->entry_to_rb[tnode->rcventry - base] = शून्य;
	clear_tid_node(fdata, tnode);
पूर्ण
