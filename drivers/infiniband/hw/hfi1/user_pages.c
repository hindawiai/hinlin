<शैली गुरु>
/*
 * Copyright(c) 2015-2017 Intel Corporation.
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

#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/device.h>
#समावेश <linux/module.h>

#समावेश "hfi.h"

अटल अचिन्हित दीर्घ cache_size = 256;
module_param(cache_size, uदीर्घ, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(cache_size, "Send and receive side cache size limit (in MB)");

/*
 * Determine whether the caller can pin pages.
 *
 * This function should be used in the implementation of buffer caches.
 * The cache implementation should call this function prior to attempting
 * to pin buffer pages in order to determine whether they should करो so.
 * The function computes cache limits based on the configured ulimit and
 * cache size. Use of this function is especially important क्रम caches
 * which are not limited in any other way (e.g. by HW resources) and, thus,
 * could keeping caching buffers.
 *
 */
bool hfi1_can_pin_pages(काष्ठा hfi1_devdata *dd, काष्ठा mm_काष्ठा *mm,
			u32 nlocked, u32 npages)
अणु
	अचिन्हित दीर्घ ulimit = rlimit(RLIMIT_MEMLOCK), pinned, cache_limit,
		size = (cache_size * (1UL << 20)); /* convert to bytes */
	अचिन्हित पूर्णांक usr_ctxts =
			dd->num_rcv_contexts - dd->first_dyn_alloc_ctxt;
	bool can_lock = capable(CAP_IPC_LOCK);

	/*
	 * Calculate per-cache size. The calculation below uses only a quarter
	 * of the available per-context limit. This leaves space क्रम other
	 * pinning. Should we worry about shared ctxts?
	 */
	cache_limit = (ulimit / usr_ctxts) / 4;

	/* If ulimit isn't set to "unlimited" and is smaller than cache_size. */
	अगर (ulimit != (-1UL) && size > cache_limit)
		size = cache_limit;

	/* Convert to number of pages */
	size = DIV_ROUND_UP(size, PAGE_SIZE);

	pinned = atomic64_पढ़ो(&mm->pinned_vm);

	/* First, check the असलolute limit against all pinned pages. */
	अगर (pinned + npages >= ulimit && !can_lock)
		वापस false;

	वापस ((nlocked + npages) <= size) || can_lock;
पूर्ण

पूर्णांक hfi1_acquire_user_pages(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr, माप_प्रकार npages,
			    bool writable, काष्ठा page **pages)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक gup_flags = FOLL_LONGTERM | (writable ? FOLL_WRITE : 0);

	ret = pin_user_pages_fast(vaddr, npages, gup_flags, pages);
	अगर (ret < 0)
		वापस ret;

	atomic64_add(ret, &mm->pinned_vm);

	वापस ret;
पूर्ण

व्योम hfi1_release_user_pages(काष्ठा mm_काष्ठा *mm, काष्ठा page **p,
			     माप_प्रकार npages, bool dirty)
अणु
	unpin_user_pages_dirty_lock(p, npages, dirty);

	अगर (mm) अणु /* during बंद after संकेत, mm can be शून्य */
		atomic64_sub(npages, &mm->pinned_vm);
	पूर्ण
पूर्ण
