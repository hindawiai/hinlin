<शैली गुरु>
/******************************************************************************
 * grant_table.c
 *
 * Granting क्रमeign access to our memory reservation.
 *
 * Copyright (c) 2005-2006, Christopher Clark
 * Copyright (c) 2004-2005, K A Fraser
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/memblock.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/moduleparam.h>
#अगर_घोषित CONFIG_XEN_GRANT_DMA_ALLOC
#समावेश <linux/dma-mapping.h>
#पूर्ण_अगर

#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/page.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/hvc-console.h>
#समावेश <xen/swiotlb-xen.h>
#समावेश <xen/balloon.h>
#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/xen/cpuid.h>
#पूर्ण_अगर
#समावेश <xen/mem-reservation.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/पूर्णांकerface.h>

#समावेश <यंत्र/sync_bitops.h>

/* External tools reserve first few grant table entries. */
#घोषणा NR_RESERVED_ENTRIES 8
#घोषणा GNTTAB_LIST_END 0xffffffff

अटल grant_ref_t **gnttab_list;
अटल अचिन्हित पूर्णांक nr_grant_frames;
अटल पूर्णांक gnttab_मुक्त_count;
अटल grant_ref_t gnttab_मुक्त_head;
अटल DEFINE_SPINLOCK(gnttab_list_lock);
काष्ठा grant_frames xen_स्वतः_xlat_grant_frames;
अटल अचिन्हित पूर्णांक xen_gnttab_version;
module_param_named(version, xen_gnttab_version, uपूर्णांक, 0);

अटल जोड़ अणु
	काष्ठा grant_entry_v1 *v1;
	जोड़ grant_entry_v2 *v2;
	व्योम *addr;
पूर्ण gnttab_shared;

/*This is a काष्ठाure of function poपूर्णांकers क्रम grant table*/
काष्ठा gnttab_ops अणु
	/*
	 * Version of the grant पूर्णांकerface.
	 */
	अचिन्हित पूर्णांक version;
	/*
	 * Grant refs per grant frame.
	 */
	अचिन्हित पूर्णांक grefs_per_grant_frame;
	/*
	 * Mapping a list of frames क्रम storing grant entries. Frames parameter
	 * is used to store grant table address when grant table being setup,
	 * nr_gframes is the number of frames to map grant table. Returning
	 * GNTST_okay means success and negative value means failure.
	 */
	पूर्णांक (*map_frames)(xen_pfn_t *frames, अचिन्हित पूर्णांक nr_gframes);
	/*
	 * Release a list of frames which are mapped in map_frames क्रम grant
	 * entry status.
	 */
	व्योम (*unmap_frames)(व्योम);
	/*
	 * Introducing a valid entry पूर्णांकo the grant table, granting the frame of
	 * this grant entry to करोमुख्य क्रम accessing or transfering. Ref
	 * parameter is reference of this पूर्णांकroduced grant entry, करोmid is id of
	 * granted करोमुख्य, frame is the page frame to be granted, and flags is
	 * status of the grant entry to be updated.
	 */
	व्योम (*update_entry)(grant_ref_t ref, करोmid_t करोmid,
			     अचिन्हित दीर्घ frame, अचिन्हित flags);
	/*
	 * Stop granting a grant entry to करोमुख्य क्रम accessing. Ref parameter is
	 * reference of a grant entry whose grant access will be stopped,
	 * पढ़ोonly is not in use in this function. If the grant entry is
	 * currently mapped क्रम पढ़ोing or writing, just वापस failure(==0)
	 * directly and करोn't tear करोwn the grant access. Otherwise, stop grant
	 * access क्रम this entry and वापस success(==1).
	 */
	पूर्णांक (*end_क्रमeign_access_ref)(grant_ref_t ref, पूर्णांक पढ़ोonly);
	/*
	 * Stop granting a grant entry to करोमुख्य क्रम transfer. Ref parameter is
	 * reference of a grant entry whose grant transfer will be stopped. If
	 * tranfer has not started, just reclaim the grant entry and वापस
	 * failure(==0). Otherwise, रुको क्रम the transfer to complete and then
	 * वापस the frame.
	 */
	अचिन्हित दीर्घ (*end_क्रमeign_transfer_ref)(grant_ref_t ref);
	/*
	 * Query the status of a grant entry. Ref parameter is reference of
	 * queried grant entry, वापस value is the status of queried entry.
	 * Detailed status(writing/पढ़ोing) can be gotten from the वापस value
	 * by bit operations.
	 */
	पूर्णांक (*query_क्रमeign_access)(grant_ref_t ref);
पूर्ण;

काष्ठा unmap_refs_callback_data अणु
	काष्ठा completion completion;
	पूर्णांक result;
पूर्ण;

अटल स्थिर काष्ठा gnttab_ops *gnttab_पूर्णांकerface;

/* This reflects status of grant entries, so act as a global value. */
अटल grant_status_t *grstatus;

अटल काष्ठा gnttab_मुक्त_callback *gnttab_मुक्त_callback_list;

अटल पूर्णांक gnttab_expand(अचिन्हित पूर्णांक req_entries);

#घोषणा RPP (PAGE_SIZE / माप(grant_ref_t))
#घोषणा SPP (PAGE_SIZE / माप(grant_status_t))

अटल अंतरभूत grant_ref_t *__gnttab_entry(grant_ref_t entry)
अणु
	वापस &gnttab_list[(entry) / RPP][(entry) % RPP];
पूर्ण
/* This can be used as an l-value */
#घोषणा gnttab_entry(entry) (*__gnttab_entry(entry))

अटल पूर्णांक get_मुक्त_entries(अचिन्हित count)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ref, rc = 0;
	grant_ref_t head;

	spin_lock_irqsave(&gnttab_list_lock, flags);

	अगर ((gnttab_मुक्त_count < count) &&
	    ((rc = gnttab_expand(count - gnttab_मुक्त_count)) < 0)) अणु
		spin_unlock_irqrestore(&gnttab_list_lock, flags);
		वापस rc;
	पूर्ण

	ref = head = gnttab_मुक्त_head;
	gnttab_मुक्त_count -= count;
	जबतक (count-- > 1)
		head = gnttab_entry(head);
	gnttab_मुक्त_head = gnttab_entry(head);
	gnttab_entry(head) = GNTTAB_LIST_END;

	spin_unlock_irqrestore(&gnttab_list_lock, flags);

	वापस ref;
पूर्ण

अटल व्योम करो_मुक्त_callbacks(व्योम)
अणु
	काष्ठा gnttab_मुक्त_callback *callback, *next;

	callback = gnttab_मुक्त_callback_list;
	gnttab_मुक्त_callback_list = शून्य;

	जबतक (callback != शून्य) अणु
		next = callback->next;
		अगर (gnttab_मुक्त_count >= callback->count) अणु
			callback->next = शून्य;
			callback->fn(callback->arg);
		पूर्ण अन्यथा अणु
			callback->next = gnttab_मुक्त_callback_list;
			gnttab_मुक्त_callback_list = callback;
		पूर्ण
		callback = next;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम check_मुक्त_callbacks(व्योम)
अणु
	अगर (unlikely(gnttab_मुक्त_callback_list))
		करो_मुक्त_callbacks();
पूर्ण

अटल व्योम put_मुक्त_entry(grant_ref_t ref)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&gnttab_list_lock, flags);
	gnttab_entry(ref) = gnttab_मुक्त_head;
	gnttab_मुक्त_head = ref;
	gnttab_मुक्त_count++;
	check_मुक्त_callbacks();
	spin_unlock_irqrestore(&gnttab_list_lock, flags);
पूर्ण

/*
 * Following applies to gnttab_update_entry_v1 and gnttab_update_entry_v2.
 * Introducing a valid entry पूर्णांकo the grant table:
 *  1. Write ent->करोmid.
 *  2. Write ent->frame:
 *      GTF_permit_access:   Frame to which access is permitted.
 *      GTF_accept_transfer: Pseuकरो-phys frame slot being filled by new
 *                           frame, or zero अगर none.
 *  3. Write memory barrier (WMB).
 *  4. Write ent->flags, inc. valid type.
 */
अटल व्योम gnttab_update_entry_v1(grant_ref_t ref, करोmid_t करोmid,
				   अचिन्हित दीर्घ frame, अचिन्हित flags)
अणु
	gnttab_shared.v1[ref].करोmid = करोmid;
	gnttab_shared.v1[ref].frame = frame;
	wmb();
	gnttab_shared.v1[ref].flags = flags;
पूर्ण

अटल व्योम gnttab_update_entry_v2(grant_ref_t ref, करोmid_t करोmid,
				   अचिन्हित दीर्घ frame, अचिन्हित पूर्णांक flags)
अणु
	gnttab_shared.v2[ref].hdr.करोmid = करोmid;
	gnttab_shared.v2[ref].full_page.frame = frame;
	wmb();	/* Hypervisor concurrent accesses. */
	gnttab_shared.v2[ref].hdr.flags = GTF_permit_access | flags;
पूर्ण

/*
 * Public grant-issuing पूर्णांकerface functions
 */
व्योम gnttab_grant_क्रमeign_access_ref(grant_ref_t ref, करोmid_t करोmid,
				     अचिन्हित दीर्घ frame, पूर्णांक पढ़ोonly)
अणु
	gnttab_पूर्णांकerface->update_entry(ref, करोmid, frame,
			   GTF_permit_access | (पढ़ोonly ? GTF_पढ़ोonly : 0));
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_grant_क्रमeign_access_ref);

पूर्णांक gnttab_grant_क्रमeign_access(करोmid_t करोmid, अचिन्हित दीर्घ frame,
				पूर्णांक पढ़ोonly)
अणु
	पूर्णांक ref;

	ref = get_मुक्त_entries(1);
	अगर (unlikely(ref < 0))
		वापस -ENOSPC;

	gnttab_grant_क्रमeign_access_ref(ref, करोmid, frame, पढ़ोonly);

	वापस ref;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_grant_क्रमeign_access);

अटल पूर्णांक gnttab_query_क्रमeign_access_v1(grant_ref_t ref)
अणु
	वापस gnttab_shared.v1[ref].flags & (GTF_पढ़ोing|GTF_writing);
पूर्ण

अटल पूर्णांक gnttab_query_क्रमeign_access_v2(grant_ref_t ref)
अणु
	वापस grstatus[ref] & (GTF_पढ़ोing|GTF_writing);
पूर्ण

पूर्णांक gnttab_query_क्रमeign_access(grant_ref_t ref)
अणु
	वापस gnttab_पूर्णांकerface->query_क्रमeign_access(ref);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_query_क्रमeign_access);

अटल पूर्णांक gnttab_end_क्रमeign_access_ref_v1(grant_ref_t ref, पूर्णांक पढ़ोonly)
अणु
	u16 flags, nflags;
	u16 *pflags;

	pflags = &gnttab_shared.v1[ref].flags;
	nflags = *pflags;
	करो अणु
		flags = nflags;
		अगर (flags & (GTF_पढ़ोing|GTF_writing))
			वापस 0;
	पूर्ण जबतक ((nflags = sync_cmpxchg(pflags, flags, 0)) != flags);

	वापस 1;
पूर्ण

अटल पूर्णांक gnttab_end_क्रमeign_access_ref_v2(grant_ref_t ref, पूर्णांक पढ़ोonly)
अणु
	gnttab_shared.v2[ref].hdr.flags = 0;
	mb();	/* Concurrent access by hypervisor. */
	अगर (grstatus[ref] & (GTF_पढ़ोing|GTF_writing)) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		/*
		 * The पढ़ो of grstatus needs to have acquire semantics.
		 *  On x86, पढ़ोs alपढ़ोy have that, and we just need to
		 * protect against compiler reorderings.
		 * On other architectures we may need a full barrier.
		 */
#अगर_घोषित CONFIG_X86
		barrier();
#अन्यथा
		mb();
#पूर्ण_अगर
	पूर्ण

	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक _gnttab_end_क्रमeign_access_ref(grant_ref_t ref, पूर्णांक पढ़ोonly)
अणु
	वापस gnttab_पूर्णांकerface->end_क्रमeign_access_ref(ref, पढ़ोonly);
पूर्ण

पूर्णांक gnttab_end_क्रमeign_access_ref(grant_ref_t ref, पूर्णांक पढ़ोonly)
अणु
	अगर (_gnttab_end_क्रमeign_access_ref(ref, पढ़ोonly))
		वापस 1;
	pr_warn("WARNING: g.e. %#x still in use!\n", ref);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_end_क्रमeign_access_ref);

काष्ठा deferred_entry अणु
	काष्ठा list_head list;
	grant_ref_t ref;
	bool ro;
	uपूर्णांक16_t warn_delay;
	काष्ठा page *page;
पूर्ण;
अटल LIST_HEAD(deferred_list);
अटल व्योम gnttab_handle_deferred(काष्ठा समयr_list *);
अटल DEFINE_TIMER(deferred_समयr, gnttab_handle_deferred);

अटल व्योम gnttab_handle_deferred(काष्ठा समयr_list *unused)
अणु
	अचिन्हित पूर्णांक nr = 10;
	काष्ठा deferred_entry *first = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gnttab_list_lock, flags);
	जबतक (nr--) अणु
		काष्ठा deferred_entry *entry
			= list_first_entry(&deferred_list,
					   काष्ठा deferred_entry, list);

		अगर (entry == first)
			अवरोध;
		list_del(&entry->list);
		spin_unlock_irqrestore(&gnttab_list_lock, flags);
		अगर (_gnttab_end_क्रमeign_access_ref(entry->ref, entry->ro)) अणु
			put_मुक्त_entry(entry->ref);
			अगर (entry->page) अणु
				pr_debug("freeing g.e. %#x (pfn %#lx)\n",
					 entry->ref, page_to_pfn(entry->page));
				put_page(entry->page);
			पूर्ण अन्यथा
				pr_info("freeing g.e. %#x\n", entry->ref);
			kमुक्त(entry);
			entry = शून्य;
		पूर्ण अन्यथा अणु
			अगर (!--entry->warn_delay)
				pr_info("g.e. %#x still pending\n", entry->ref);
			अगर (!first)
				first = entry;
		पूर्ण
		spin_lock_irqsave(&gnttab_list_lock, flags);
		अगर (entry)
			list_add_tail(&entry->list, &deferred_list);
		अन्यथा अगर (list_empty(&deferred_list))
			अवरोध;
	पूर्ण
	अगर (!list_empty(&deferred_list) && !समयr_pending(&deferred_समयr)) अणु
		deferred_समयr.expires = jअगरfies + HZ;
		add_समयr(&deferred_समयr);
	पूर्ण
	spin_unlock_irqrestore(&gnttab_list_lock, flags);
पूर्ण

अटल व्योम gnttab_add_deferred(grant_ref_t ref, bool पढ़ोonly,
				काष्ठा page *page)
अणु
	काष्ठा deferred_entry *entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);
	स्थिर अक्षर *what = KERN_WARNING "leaking";

	अगर (entry) अणु
		अचिन्हित दीर्घ flags;

		entry->ref = ref;
		entry->ro = पढ़ोonly;
		entry->page = page;
		entry->warn_delay = 60;
		spin_lock_irqsave(&gnttab_list_lock, flags);
		list_add_tail(&entry->list, &deferred_list);
		अगर (!समयr_pending(&deferred_समयr)) अणु
			deferred_समयr.expires = jअगरfies + HZ;
			add_समयr(&deferred_समयr);
		पूर्ण
		spin_unlock_irqrestore(&gnttab_list_lock, flags);
		what = KERN_DEBUG "deferring";
	पूर्ण
	prपूर्णांकk("%s g.e. %#x (pfn %#lx)\n",
	       what, ref, page ? page_to_pfn(page) : -1);
पूर्ण

व्योम gnttab_end_क्रमeign_access(grant_ref_t ref, पूर्णांक पढ़ोonly,
			       अचिन्हित दीर्घ page)
अणु
	अगर (gnttab_end_क्रमeign_access_ref(ref, पढ़ोonly)) अणु
		put_मुक्त_entry(ref);
		अगर (page != 0)
			put_page(virt_to_page(page));
	पूर्ण अन्यथा
		gnttab_add_deferred(ref, पढ़ोonly,
				    page ? virt_to_page(page) : शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_end_क्रमeign_access);

पूर्णांक gnttab_grant_क्रमeign_transfer(करोmid_t करोmid, अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक ref;

	ref = get_मुक्त_entries(1);
	अगर (unlikely(ref < 0))
		वापस -ENOSPC;
	gnttab_grant_क्रमeign_transfer_ref(ref, करोmid, pfn);

	वापस ref;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_grant_क्रमeign_transfer);

व्योम gnttab_grant_क्रमeign_transfer_ref(grant_ref_t ref, करोmid_t करोmid,
				       अचिन्हित दीर्घ pfn)
अणु
	gnttab_पूर्णांकerface->update_entry(ref, करोmid, pfn, GTF_accept_transfer);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_grant_क्रमeign_transfer_ref);

अटल अचिन्हित दीर्घ gnttab_end_क्रमeign_transfer_ref_v1(grant_ref_t ref)
अणु
	अचिन्हित दीर्घ frame;
	u16           flags;
	u16          *pflags;

	pflags = &gnttab_shared.v1[ref].flags;

	/*
	 * If a transfer is not even yet started, try to reclaim the grant
	 * reference and वापस failure (== 0).
	 */
	जबतक (!((flags = *pflags) & GTF_transfer_committed)) अणु
		अगर (sync_cmpxchg(pflags, flags, 0) == flags)
			वापस 0;
		cpu_relax();
	पूर्ण

	/* If a transfer is in progress then रुको until it is completed. */
	जबतक (!(flags & GTF_transfer_completed)) अणु
		flags = *pflags;
		cpu_relax();
	पूर्ण

	rmb();	/* Read the frame number /after/ पढ़ोing completion status. */
	frame = gnttab_shared.v1[ref].frame;
	BUG_ON(frame == 0);

	वापस frame;
पूर्ण

अटल अचिन्हित दीर्घ gnttab_end_क्रमeign_transfer_ref_v2(grant_ref_t ref)
अणु
	अचिन्हित दीर्घ frame;
	u16           flags;
	u16          *pflags;

	pflags = &gnttab_shared.v2[ref].hdr.flags;

	/*
	 * If a transfer is not even yet started, try to reclaim the grant
	 * reference and वापस failure (== 0).
	 */
	जबतक (!((flags = *pflags) & GTF_transfer_committed)) अणु
		अगर (sync_cmpxchg(pflags, flags, 0) == flags)
			वापस 0;
		cpu_relax();
	पूर्ण

	/* If a transfer is in progress then रुको until it is completed. */
	जबतक (!(flags & GTF_transfer_completed)) अणु
		flags = *pflags;
		cpu_relax();
	पूर्ण

	rmb();  /* Read the frame number /after/ पढ़ोing completion status. */
	frame = gnttab_shared.v2[ref].full_page.frame;
	BUG_ON(frame == 0);

	वापस frame;
पूर्ण

अचिन्हित दीर्घ gnttab_end_क्रमeign_transfer_ref(grant_ref_t ref)
अणु
	वापस gnttab_पूर्णांकerface->end_क्रमeign_transfer_ref(ref);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_end_क्रमeign_transfer_ref);

अचिन्हित दीर्घ gnttab_end_क्रमeign_transfer(grant_ref_t ref)
अणु
	अचिन्हित दीर्घ frame = gnttab_end_क्रमeign_transfer_ref(ref);
	put_मुक्त_entry(ref);
	वापस frame;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_end_क्रमeign_transfer);

व्योम gnttab_मुक्त_grant_reference(grant_ref_t ref)
अणु
	put_मुक्त_entry(ref);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_मुक्त_grant_reference);

व्योम gnttab_मुक्त_grant_references(grant_ref_t head)
अणु
	grant_ref_t ref;
	अचिन्हित दीर्घ flags;
	पूर्णांक count = 1;
	अगर (head == GNTTAB_LIST_END)
		वापस;
	spin_lock_irqsave(&gnttab_list_lock, flags);
	ref = head;
	जबतक (gnttab_entry(ref) != GNTTAB_LIST_END) अणु
		ref = gnttab_entry(ref);
		count++;
	पूर्ण
	gnttab_entry(ref) = gnttab_मुक्त_head;
	gnttab_मुक्त_head = head;
	gnttab_मुक्त_count += count;
	check_मुक्त_callbacks();
	spin_unlock_irqrestore(&gnttab_list_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_मुक्त_grant_references);

पूर्णांक gnttab_alloc_grant_references(u16 count, grant_ref_t *head)
अणु
	पूर्णांक h = get_मुक्त_entries(count);

	अगर (h < 0)
		वापस -ENOSPC;

	*head = h;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_alloc_grant_references);

पूर्णांक gnttab_empty_grant_references(स्थिर grant_ref_t *निजी_head)
अणु
	वापस (*निजी_head == GNTTAB_LIST_END);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_empty_grant_references);

पूर्णांक gnttab_claim_grant_reference(grant_ref_t *निजी_head)
अणु
	grant_ref_t g = *निजी_head;
	अगर (unlikely(g == GNTTAB_LIST_END))
		वापस -ENOSPC;
	*निजी_head = gnttab_entry(g);
	वापस g;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_claim_grant_reference);

व्योम gnttab_release_grant_reference(grant_ref_t *निजी_head,
				    grant_ref_t release)
अणु
	gnttab_entry(release) = *निजी_head;
	*निजी_head = release;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_release_grant_reference);

व्योम gnttab_request_मुक्त_callback(काष्ठा gnttab_मुक्त_callback *callback,
				  व्योम (*fn)(व्योम *), व्योम *arg, u16 count)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा gnttab_मुक्त_callback *cb;

	spin_lock_irqsave(&gnttab_list_lock, flags);

	/* Check अगर the callback is alपढ़ोy on the list */
	cb = gnttab_मुक्त_callback_list;
	जबतक (cb) अणु
		अगर (cb == callback)
			जाओ out;
		cb = cb->next;
	पूर्ण

	callback->fn = fn;
	callback->arg = arg;
	callback->count = count;
	callback->next = gnttab_मुक्त_callback_list;
	gnttab_मुक्त_callback_list = callback;
	check_मुक्त_callbacks();
out:
	spin_unlock_irqrestore(&gnttab_list_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_request_मुक्त_callback);

व्योम gnttab_cancel_मुक्त_callback(काष्ठा gnttab_मुक्त_callback *callback)
अणु
	काष्ठा gnttab_मुक्त_callback **pcb;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gnttab_list_lock, flags);
	क्रम (pcb = &gnttab_मुक्त_callback_list; *pcb; pcb = &(*pcb)->next) अणु
		अगर (*pcb == callback) अणु
			*pcb = callback->next;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&gnttab_list_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_cancel_मुक्त_callback);

अटल अचिन्हित पूर्णांक gnttab_frames(अचिन्हित पूर्णांक frames, अचिन्हित पूर्णांक align)
अणु
	वापस (frames * gnttab_पूर्णांकerface->grefs_per_grant_frame + align - 1) /
	       align;
पूर्ण

अटल पूर्णांक grow_gnttab_list(अचिन्हित पूर्णांक more_frames)
अणु
	अचिन्हित पूर्णांक new_nr_grant_frames, extra_entries, i;
	अचिन्हित पूर्णांक nr_glist_frames, new_nr_glist_frames;
	अचिन्हित पूर्णांक grefs_per_frame;

	grefs_per_frame = gnttab_पूर्णांकerface->grefs_per_grant_frame;

	new_nr_grant_frames = nr_grant_frames + more_frames;
	extra_entries = more_frames * grefs_per_frame;

	nr_glist_frames = gnttab_frames(nr_grant_frames, RPP);
	new_nr_glist_frames = gnttab_frames(new_nr_grant_frames, RPP);
	क्रम (i = nr_glist_frames; i < new_nr_glist_frames; i++) अणु
		gnttab_list[i] = (grant_ref_t *)__get_मुक्त_page(GFP_ATOMIC);
		अगर (!gnttab_list[i])
			जाओ grow_nomem;
	पूर्ण


	क्रम (i = grefs_per_frame * nr_grant_frames;
	     i < grefs_per_frame * new_nr_grant_frames - 1; i++)
		gnttab_entry(i) = i + 1;

	gnttab_entry(i) = gnttab_मुक्त_head;
	gnttab_मुक्त_head = grefs_per_frame * nr_grant_frames;
	gnttab_मुक्त_count += extra_entries;

	nr_grant_frames = new_nr_grant_frames;

	check_मुक्त_callbacks();

	वापस 0;

grow_nomem:
	जबतक (i-- > nr_glist_frames)
		मुक्त_page((अचिन्हित दीर्घ) gnttab_list[i]);
	वापस -ENOMEM;
पूर्ण

अटल अचिन्हित पूर्णांक __max_nr_grant_frames(व्योम)
अणु
	काष्ठा gnttab_query_size query;
	पूर्णांक rc;

	query.करोm = DOMID_SELF;

	rc = HYPERVISOR_grant_table_op(GNTTABOP_query_size, &query, 1);
	अगर ((rc < 0) || (query.status != GNTST_okay))
		वापस 4; /* Legacy max supported number of frames */

	वापस query.max_nr_frames;
पूर्ण

अचिन्हित पूर्णांक gnttab_max_grant_frames(व्योम)
अणु
	अचिन्हित पूर्णांक xen_max = __max_nr_grant_frames();
	अटल अचिन्हित पूर्णांक boot_max_nr_grant_frames;

	/* First समय, initialize it properly. */
	अगर (!boot_max_nr_grant_frames)
		boot_max_nr_grant_frames = __max_nr_grant_frames();

	अगर (xen_max > boot_max_nr_grant_frames)
		वापस boot_max_nr_grant_frames;
	वापस xen_max;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_max_grant_frames);

पूर्णांक gnttab_setup_स्वतः_xlat_frames(phys_addr_t addr)
अणु
	xen_pfn_t *pfn;
	अचिन्हित पूर्णांक max_nr_gframes = __max_nr_grant_frames();
	अचिन्हित पूर्णांक i;
	व्योम *vaddr;

	अगर (xen_स्वतः_xlat_grant_frames.count)
		वापस -EINVAL;

	vaddr = xen_remap(addr, XEN_PAGE_SIZE * max_nr_gframes);
	अगर (vaddr == शून्य) अणु
		pr_warn("Failed to ioremap gnttab share frames (addr=%pa)!\n",
			&addr);
		वापस -ENOMEM;
	पूर्ण
	pfn = kसुस्मृति(max_nr_gframes, माप(pfn[0]), GFP_KERNEL);
	अगर (!pfn) अणु
		xen_unmap(vaddr);
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < max_nr_gframes; i++)
		pfn[i] = XEN_PFN_DOWN(addr) + i;

	xen_स्वतः_xlat_grant_frames.vaddr = vaddr;
	xen_स्वतः_xlat_grant_frames.pfn = pfn;
	xen_स्वतः_xlat_grant_frames.count = max_nr_gframes;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_setup_स्वतः_xlat_frames);

व्योम gnttab_मुक्त_स्वतः_xlat_frames(व्योम)
अणु
	अगर (!xen_स्वतः_xlat_grant_frames.count)
		वापस;
	kमुक्त(xen_स्वतः_xlat_grant_frames.pfn);
	xen_unmap(xen_स्वतः_xlat_grant_frames.vaddr);

	xen_स्वतः_xlat_grant_frames.pfn = शून्य;
	xen_स्वतः_xlat_grant_frames.count = 0;
	xen_स्वतः_xlat_grant_frames.vaddr = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_मुक्त_स्वतः_xlat_frames);

पूर्णांक gnttab_pages_set_निजी(पूर्णांक nr_pages, काष्ठा page **pages)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_pages; i++) अणु
#अगर BITS_PER_LONG < 64
		काष्ठा xen_page_क्रमeign *क्रमeign;

		क्रमeign = kzalloc(माप(*क्रमeign), GFP_KERNEL);
		अगर (!क्रमeign)
			वापस -ENOMEM;

		set_page_निजी(pages[i], (अचिन्हित दीर्घ)क्रमeign);
#पूर्ण_अगर
		SetPagePrivate(pages[i]);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_pages_set_निजी);

/**
 * gnttab_alloc_pages - alloc pages suitable क्रम grant mapping पूर्णांकo
 * @nr_pages: number of pages to alloc
 * @pages: वापसs the pages
 */
पूर्णांक gnttab_alloc_pages(पूर्णांक nr_pages, काष्ठा page **pages)
अणु
	पूर्णांक ret;

	ret = xen_alloc_unpopulated_pages(nr_pages, pages);
	अगर (ret < 0)
		वापस ret;

	ret = gnttab_pages_set_निजी(nr_pages, pages);
	अगर (ret < 0)
		gnttab_मुक्त_pages(nr_pages, pages);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_alloc_pages);

#अगर_घोषित CONFIG_XEN_UNPOPULATED_ALLOC
अटल अंतरभूत व्योम cache_init(काष्ठा gnttab_page_cache *cache)
अणु
	cache->pages = शून्य;
पूर्ण

अटल अंतरभूत bool cache_empty(काष्ठा gnttab_page_cache *cache)
अणु
	वापस !cache->pages;
पूर्ण

अटल अंतरभूत काष्ठा page *cache_deq(काष्ठा gnttab_page_cache *cache)
अणु
	काष्ठा page *page;

	page = cache->pages;
	cache->pages = page->zone_device_data;

	वापस page;
पूर्ण

अटल अंतरभूत व्योम cache_enq(काष्ठा gnttab_page_cache *cache, काष्ठा page *page)
अणु
	page->zone_device_data = cache->pages;
	cache->pages = page;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cache_init(काष्ठा gnttab_page_cache *cache)
अणु
	INIT_LIST_HEAD(&cache->pages);
पूर्ण

अटल अंतरभूत bool cache_empty(काष्ठा gnttab_page_cache *cache)
अणु
	वापस list_empty(&cache->pages);
पूर्ण

अटल अंतरभूत काष्ठा page *cache_deq(काष्ठा gnttab_page_cache *cache)
अणु
	काष्ठा page *page;

	page = list_first_entry(&cache->pages, काष्ठा page, lru);
	list_del(&page->lru);

	वापस page;
पूर्ण

अटल अंतरभूत व्योम cache_enq(काष्ठा gnttab_page_cache *cache, काष्ठा page *page)
अणु
	list_add(&page->lru, &cache->pages);
पूर्ण
#पूर्ण_अगर

व्योम gnttab_page_cache_init(काष्ठा gnttab_page_cache *cache)
अणु
	spin_lock_init(&cache->lock);
	cache_init(cache);
	cache->num_pages = 0;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_page_cache_init);

पूर्णांक gnttab_page_cache_get(काष्ठा gnttab_page_cache *cache, काष्ठा page **page)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cache->lock, flags);

	अगर (cache_empty(cache)) अणु
		spin_unlock_irqrestore(&cache->lock, flags);
		वापस gnttab_alloc_pages(1, page);
	पूर्ण

	page[0] = cache_deq(cache);
	cache->num_pages--;

	spin_unlock_irqrestore(&cache->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_page_cache_get);

व्योम gnttab_page_cache_put(काष्ठा gnttab_page_cache *cache, काष्ठा page **page,
			   अचिन्हित पूर्णांक num)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	spin_lock_irqsave(&cache->lock, flags);

	क्रम (i = 0; i < num; i++)
		cache_enq(cache, page[i]);
	cache->num_pages += num;

	spin_unlock_irqrestore(&cache->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_page_cache_put);

व्योम gnttab_page_cache_shrink(काष्ठा gnttab_page_cache *cache, अचिन्हित पूर्णांक num)
अणु
	काष्ठा page *page[10];
	अचिन्हित पूर्णांक i = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cache->lock, flags);

	जबतक (cache->num_pages > num) अणु
		page[i] = cache_deq(cache);
		cache->num_pages--;
		अगर (++i == ARRAY_SIZE(page)) अणु
			spin_unlock_irqrestore(&cache->lock, flags);
			gnttab_मुक्त_pages(i, page);
			i = 0;
			spin_lock_irqsave(&cache->lock, flags);
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&cache->lock, flags);

	अगर (i != 0)
		gnttab_मुक्त_pages(i, page);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_page_cache_shrink);

व्योम gnttab_pages_clear_निजी(पूर्णांक nr_pages, काष्ठा page **pages)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_pages; i++) अणु
		अगर (PagePrivate(pages[i])) अणु
#अगर BITS_PER_LONG < 64
			kमुक्त((व्योम *)page_निजी(pages[i]));
#पूर्ण_अगर
			ClearPagePrivate(pages[i]);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_pages_clear_निजी);

/**
 * gnttab_मुक्त_pages - मुक्त pages allocated by gnttab_alloc_pages()
 * @nr_pages; number of pages to मुक्त
 * @pages: the pages
 */
व्योम gnttab_मुक्त_pages(पूर्णांक nr_pages, काष्ठा page **pages)
अणु
	gnttab_pages_clear_निजी(nr_pages, pages);
	xen_मुक्त_unpopulated_pages(nr_pages, pages);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_मुक्त_pages);

#अगर_घोषित CONFIG_XEN_GRANT_DMA_ALLOC
/**
 * gnttab_dma_alloc_pages - alloc DMAable pages suitable क्रम grant mapping पूर्णांकo
 * @args: arguments to the function
 */
पूर्णांक gnttab_dma_alloc_pages(काष्ठा gnttab_dma_alloc_args *args)
अणु
	अचिन्हित दीर्घ pfn, start_pfn;
	माप_प्रकार size;
	पूर्णांक i, ret;

	size = args->nr_pages << PAGE_SHIFT;
	अगर (args->coherent)
		args->vaddr = dma_alloc_coherent(args->dev, size,
						 &args->dev_bus_addr,
						 GFP_KERNEL | __GFP_NOWARN);
	अन्यथा
		args->vaddr = dma_alloc_wc(args->dev, size,
					   &args->dev_bus_addr,
					   GFP_KERNEL | __GFP_NOWARN);
	अगर (!args->vaddr) अणु
		pr_debug("Failed to allocate DMA buffer of size %zu\n", size);
		वापस -ENOMEM;
	पूर्ण

	start_pfn = __phys_to_pfn(args->dev_bus_addr);
	क्रम (pfn = start_pfn, i = 0; pfn < start_pfn + args->nr_pages;
			pfn++, i++) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		args->pages[i] = page;
		args->frames[i] = xen_page_to_gfn(page);
		xenmem_reservation_scrub_page(page);
	पूर्ण

	xenmem_reservation_va_mapping_reset(args->nr_pages, args->pages);

	ret = xenmem_reservation_decrease(args->nr_pages, args->frames);
	अगर (ret != args->nr_pages) अणु
		pr_debug("Failed to decrease reservation for DMA buffer\n");
		ret = -EFAULT;
		जाओ fail;
	पूर्ण

	ret = gnttab_pages_set_निजी(args->nr_pages, args->pages);
	अगर (ret < 0)
		जाओ fail;

	वापस 0;

fail:
	gnttab_dma_मुक्त_pages(args);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_dma_alloc_pages);

/**
 * gnttab_dma_मुक्त_pages - मुक्त DMAable pages
 * @args: arguments to the function
 */
पूर्णांक gnttab_dma_मुक्त_pages(काष्ठा gnttab_dma_alloc_args *args)
अणु
	माप_प्रकार size;
	पूर्णांक i, ret;

	gnttab_pages_clear_निजी(args->nr_pages, args->pages);

	क्रम (i = 0; i < args->nr_pages; i++)
		args->frames[i] = page_to_xen_pfn(args->pages[i]);

	ret = xenmem_reservation_increase(args->nr_pages, args->frames);
	अगर (ret != args->nr_pages) अणु
		pr_debug("Failed to increase reservation for DMA buffer\n");
		ret = -EFAULT;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	xenmem_reservation_va_mapping_update(args->nr_pages, args->pages,
					     args->frames);

	size = args->nr_pages << PAGE_SHIFT;
	अगर (args->coherent)
		dma_मुक्त_coherent(args->dev, size,
				  args->vaddr, args->dev_bus_addr);
	अन्यथा
		dma_मुक्त_wc(args->dev, size,
			    args->vaddr, args->dev_bus_addr);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_dma_मुक्त_pages);
#पूर्ण_अगर

/* Handling of paged out grant tarमाला_लो (GNTST_eagain) */
#घोषणा MAX_DELAY 256
अटल अंतरभूत व्योम
gnttab_retry_eagain_gop(अचिन्हित पूर्णांक cmd, व्योम *gop, पूर्णांक16_t *status,
						स्थिर अक्षर *func)
अणु
	अचिन्हित delay = 1;

	करो अणु
		BUG_ON(HYPERVISOR_grant_table_op(cmd, gop, 1));
		अगर (*status == GNTST_eagain)
			msleep(delay++);
	पूर्ण जबतक ((*status == GNTST_eagain) && (delay < MAX_DELAY));

	अगर (delay >= MAX_DELAY) अणु
		pr_err("%s: %s eagain grant\n", func, current->comm);
		*status = GNTST_bad_page;
	पूर्ण
पूर्ण

व्योम gnttab_batch_map(काष्ठा gnttab_map_grant_ref *batch, अचिन्हित count)
अणु
	काष्ठा gnttab_map_grant_ref *op;

	अगर (HYPERVISOR_grant_table_op(GNTTABOP_map_grant_ref, batch, count))
		BUG();
	क्रम (op = batch; op < batch + count; op++)
		अगर (op->status == GNTST_eagain)
			gnttab_retry_eagain_gop(GNTTABOP_map_grant_ref, op,
						&op->status, __func__);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_batch_map);

व्योम gnttab_batch_copy(काष्ठा gnttab_copy *batch, अचिन्हित count)
अणु
	काष्ठा gnttab_copy *op;

	अगर (HYPERVISOR_grant_table_op(GNTTABOP_copy, batch, count))
		BUG();
	क्रम (op = batch; op < batch + count; op++)
		अगर (op->status == GNTST_eagain)
			gnttab_retry_eagain_gop(GNTTABOP_copy, op,
						&op->status, __func__);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_batch_copy);

व्योम gnttab_क्रमeach_grant_in_range(काष्ठा page *page,
				   अचिन्हित पूर्णांक offset,
				   अचिन्हित पूर्णांक len,
				   xen_grant_fn_t fn,
				   व्योम *data)
अणु
	अचिन्हित पूर्णांक goffset;
	अचिन्हित पूर्णांक glen;
	अचिन्हित दीर्घ xen_pfn;

	len = min_t(अचिन्हित पूर्णांक, PAGE_SIZE - offset, len);
	goffset = xen_offset_in_page(offset);

	xen_pfn = page_to_xen_pfn(page) + XEN_PFN_DOWN(offset);

	जबतक (len) अणु
		glen = min_t(अचिन्हित पूर्णांक, XEN_PAGE_SIZE - goffset, len);
		fn(pfn_to_gfn(xen_pfn), goffset, glen, data);

		goffset = 0;
		xen_pfn++;
		len -= glen;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_क्रमeach_grant_in_range);

व्योम gnttab_क्रमeach_grant(काष्ठा page **pages,
			  अचिन्हित पूर्णांक nr_grefs,
			  xen_grant_fn_t fn,
			  व्योम *data)
अणु
	अचिन्हित पूर्णांक goffset = 0;
	अचिन्हित दीर्घ xen_pfn = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < nr_grefs; i++) अणु
		अगर ((i % XEN_PFN_PER_PAGE) == 0) अणु
			xen_pfn = page_to_xen_pfn(pages[i / XEN_PFN_PER_PAGE]);
			goffset = 0;
		पूर्ण

		fn(pfn_to_gfn(xen_pfn), goffset, XEN_PAGE_SIZE, data);

		goffset += XEN_PAGE_SIZE;
		xen_pfn++;
	पूर्ण
पूर्ण

पूर्णांक gnttab_map_refs(काष्ठा gnttab_map_grant_ref *map_ops,
		    काष्ठा gnttab_map_grant_ref *kmap_ops,
		    काष्ठा page **pages, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i, ret;

	ret = HYPERVISOR_grant_table_op(GNTTABOP_map_grant_ref, map_ops, count);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < count; i++) अणु
		चयन (map_ops[i].status) अणु
		हाल GNTST_okay:
		अणु
			काष्ठा xen_page_क्रमeign *क्रमeign;

			SetPageForeign(pages[i]);
			क्रमeign = xen_page_क्रमeign(pages[i]);
			क्रमeign->करोmid = map_ops[i].करोm;
			क्रमeign->gref = map_ops[i].ref;
			अवरोध;
		पूर्ण

		हाल GNTST_no_device_space:
			pr_warn_ratelimited("maptrack limit reached, can't map all guest pages\n");
			अवरोध;

		हाल GNTST_eagain:
			/* Retry eagain maps */
			gnttab_retry_eagain_gop(GNTTABOP_map_grant_ref,
						map_ops + i,
						&map_ops[i].status, __func__);
			/* Test status in next loop iteration. */
			i--;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस set_क्रमeign_p2m_mapping(map_ops, kmap_ops, pages, count);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_map_refs);

पूर्णांक gnttab_unmap_refs(काष्ठा gnttab_unmap_grant_ref *unmap_ops,
		      काष्ठा gnttab_unmap_grant_ref *kunmap_ops,
		      काष्ठा page **pages, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = HYPERVISOR_grant_table_op(GNTTABOP_unmap_grant_ref, unmap_ops, count);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < count; i++)
		ClearPageForeign(pages[i]);

	वापस clear_क्रमeign_p2m_mapping(unmap_ops, kunmap_ops, pages, count);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_unmap_refs);

#घोषणा GNTTAB_UNMAP_REFS_DELAY 5

अटल व्योम __gnttab_unmap_refs_async(काष्ठा gntab_unmap_queue_data* item);

अटल व्योम gnttab_unmap_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gntab_unmap_queue_data
		*unmap_data = container_of(work, 
					   काष्ठा gntab_unmap_queue_data,
					   gnttab_work.work);
	अगर (unmap_data->age != अच_पूर्णांक_उच्च)
		unmap_data->age++;
	__gnttab_unmap_refs_async(unmap_data);
पूर्ण

अटल व्योम __gnttab_unmap_refs_async(काष्ठा gntab_unmap_queue_data* item)
अणु
	पूर्णांक ret;
	पूर्णांक pc;

	क्रम (pc = 0; pc < item->count; pc++) अणु
		अगर (page_count(item->pages[pc]) > 1) अणु
			अचिन्हित दीर्घ delay = GNTTAB_UNMAP_REFS_DELAY * (item->age + 1);
			schedule_delayed_work(&item->gnttab_work,
					      msecs_to_jअगरfies(delay));
			वापस;
		पूर्ण
	पूर्ण

	ret = gnttab_unmap_refs(item->unmap_ops, item->kunmap_ops,
				item->pages, item->count);
	item->करोne(ret, item);
पूर्ण

व्योम gnttab_unmap_refs_async(काष्ठा gntab_unmap_queue_data* item)
अणु
	INIT_DELAYED_WORK(&item->gnttab_work, gnttab_unmap_work);
	item->age = 0;

	__gnttab_unmap_refs_async(item);
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_unmap_refs_async);

अटल व्योम unmap_refs_callback(पूर्णांक result,
		काष्ठा gntab_unmap_queue_data *data)
अणु
	काष्ठा unmap_refs_callback_data *d = data->data;

	d->result = result;
	complete(&d->completion);
पूर्ण

पूर्णांक gnttab_unmap_refs_sync(काष्ठा gntab_unmap_queue_data *item)
अणु
	काष्ठा unmap_refs_callback_data data;

	init_completion(&data.completion);
	item->data = &data;
	item->करोne = &unmap_refs_callback;
	gnttab_unmap_refs_async(item);
	रुको_क्रम_completion(&data.completion);

	वापस data.result;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_unmap_refs_sync);

अटल अचिन्हित पूर्णांक nr_status_frames(अचिन्हित पूर्णांक nr_grant_frames)
अणु
	वापस gnttab_frames(nr_grant_frames, SPP);
पूर्ण

अटल पूर्णांक gnttab_map_frames_v1(xen_pfn_t *frames, अचिन्हित पूर्णांक nr_gframes)
अणु
	पूर्णांक rc;

	rc = arch_gnttab_map_shared(frames, nr_gframes,
				    gnttab_max_grant_frames(),
				    &gnttab_shared.addr);
	BUG_ON(rc);

	वापस 0;
पूर्ण

अटल व्योम gnttab_unmap_frames_v1(व्योम)
अणु
	arch_gnttab_unmap(gnttab_shared.addr, nr_grant_frames);
पूर्ण

अटल पूर्णांक gnttab_map_frames_v2(xen_pfn_t *frames, अचिन्हित पूर्णांक nr_gframes)
अणु
	uपूर्णांक64_t *sframes;
	अचिन्हित पूर्णांक nr_sframes;
	काष्ठा gnttab_get_status_frames getframes;
	पूर्णांक rc;

	nr_sframes = nr_status_frames(nr_gframes);

	/* No need क्रम kzalloc as it is initialized in following hypercall
	 * GNTTABOP_get_status_frames.
	 */
	sframes = kदो_स्मृति_array(nr_sframes, माप(uपूर्णांक64_t), GFP_ATOMIC);
	अगर (!sframes)
		वापस -ENOMEM;

	getframes.करोm        = DOMID_SELF;
	getframes.nr_frames  = nr_sframes;
	set_xen_guest_handle(getframes.frame_list, sframes);

	rc = HYPERVISOR_grant_table_op(GNTTABOP_get_status_frames,
				       &getframes, 1);
	अगर (rc == -ENOSYS) अणु
		kमुक्त(sframes);
		वापस -ENOSYS;
	पूर्ण

	BUG_ON(rc || getframes.status);

	rc = arch_gnttab_map_status(sframes, nr_sframes,
				    nr_status_frames(gnttab_max_grant_frames()),
				    &grstatus);
	BUG_ON(rc);
	kमुक्त(sframes);

	rc = arch_gnttab_map_shared(frames, nr_gframes,
				    gnttab_max_grant_frames(),
				    &gnttab_shared.addr);
	BUG_ON(rc);

	वापस 0;
पूर्ण

अटल व्योम gnttab_unmap_frames_v2(व्योम)
अणु
	arch_gnttab_unmap(gnttab_shared.addr, nr_grant_frames);
	arch_gnttab_unmap(grstatus, nr_status_frames(nr_grant_frames));
पूर्ण

अटल पूर्णांक gnttab_map(अचिन्हित पूर्णांक start_idx, अचिन्हित पूर्णांक end_idx)
अणु
	काष्ठा gnttab_setup_table setup;
	xen_pfn_t *frames;
	अचिन्हित पूर्णांक nr_gframes = end_idx + 1;
	पूर्णांक rc;

	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap)) अणु
		काष्ठा xen_add_to_physmap xatp;
		अचिन्हित पूर्णांक i = end_idx;
		rc = 0;
		BUG_ON(xen_स्वतः_xlat_grant_frames.count < nr_gframes);
		/*
		 * Loop backwards, so that the first hypercall has the largest
		 * index, ensuring that the table will grow only once.
		 */
		करो अणु
			xatp.करोmid = DOMID_SELF;
			xatp.idx = i;
			xatp.space = XENMAPSPACE_grant_table;
			xatp.gpfn = xen_स्वतः_xlat_grant_frames.pfn[i];
			rc = HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp);
			अगर (rc != 0) अणु
				pr_warn("grant table add_to_physmap failed, err=%d\n",
					rc);
				अवरोध;
			पूर्ण
		पूर्ण जबतक (i-- > start_idx);

		वापस rc;
	पूर्ण

	/* No need क्रम kzalloc as it is initialized in following hypercall
	 * GNTTABOP_setup_table.
	 */
	frames = kदो_स्मृति_array(nr_gframes, माप(अचिन्हित दीर्घ), GFP_ATOMIC);
	अगर (!frames)
		वापस -ENOMEM;

	setup.करोm        = DOMID_SELF;
	setup.nr_frames  = nr_gframes;
	set_xen_guest_handle(setup.frame_list, frames);

	rc = HYPERVISOR_grant_table_op(GNTTABOP_setup_table, &setup, 1);
	अगर (rc == -ENOSYS) अणु
		kमुक्त(frames);
		वापस -ENOSYS;
	पूर्ण

	BUG_ON(rc || setup.status);

	rc = gnttab_पूर्णांकerface->map_frames(frames, nr_gframes);

	kमुक्त(frames);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा gnttab_ops gnttab_v1_ops = अणु
	.version			= 1,
	.grefs_per_grant_frame		= XEN_PAGE_SIZE /
					  माप(काष्ठा grant_entry_v1),
	.map_frames			= gnttab_map_frames_v1,
	.unmap_frames			= gnttab_unmap_frames_v1,
	.update_entry			= gnttab_update_entry_v1,
	.end_क्रमeign_access_ref		= gnttab_end_क्रमeign_access_ref_v1,
	.end_क्रमeign_transfer_ref	= gnttab_end_क्रमeign_transfer_ref_v1,
	.query_क्रमeign_access		= gnttab_query_क्रमeign_access_v1,
पूर्ण;

अटल स्थिर काष्ठा gnttab_ops gnttab_v2_ops = अणु
	.version			= 2,
	.grefs_per_grant_frame		= XEN_PAGE_SIZE /
					  माप(जोड़ grant_entry_v2),
	.map_frames			= gnttab_map_frames_v2,
	.unmap_frames			= gnttab_unmap_frames_v2,
	.update_entry			= gnttab_update_entry_v2,
	.end_क्रमeign_access_ref		= gnttab_end_क्रमeign_access_ref_v2,
	.end_क्रमeign_transfer_ref	= gnttab_end_क्रमeign_transfer_ref_v2,
	.query_क्रमeign_access		= gnttab_query_क्रमeign_access_v2,
पूर्ण;

अटल bool gnttab_need_v2(व्योम)
अणु
#अगर_घोषित CONFIG_X86
	uपूर्णांक32_t base, width;

	अगर (xen_pv_करोमुख्य()) अणु
		base = xen_cpuid_base();
		अगर (cpuid_eax(base) < 5)
			वापस false;	/* Inक्रमmation not available, use V1. */
		width = cpuid_ebx(base + 5) &
			XEN_CPUID_MACHINE_ADDRESS_WIDTH_MASK;
		वापस width > 32 + PAGE_SHIFT;
	पूर्ण
#पूर्ण_अगर
	वापस !!(max_possible_pfn >> 32);
पूर्ण

अटल व्योम gnttab_request_version(व्योम)
अणु
	दीर्घ rc;
	काष्ठा gnttab_set_version gsv;

	अगर (gnttab_need_v2())
		gsv.version = 2;
	अन्यथा
		gsv.version = 1;

	/* Boot parameter overrides स्वतःmatic selection. */
	अगर (xen_gnttab_version >= 1 && xen_gnttab_version <= 2)
		gsv.version = xen_gnttab_version;

	rc = HYPERVISOR_grant_table_op(GNTTABOP_set_version, &gsv, 1);
	अगर (rc == 0 && gsv.version == 2)
		gnttab_पूर्णांकerface = &gnttab_v2_ops;
	अन्यथा
		gnttab_पूर्णांकerface = &gnttab_v1_ops;
	pr_info("Grant tables using version %d layout\n",
		gnttab_पूर्णांकerface->version);
पूर्ण

अटल पूर्णांक gnttab_setup(व्योम)
अणु
	अचिन्हित पूर्णांक max_nr_gframes;

	max_nr_gframes = gnttab_max_grant_frames();
	अगर (max_nr_gframes < nr_grant_frames)
		वापस -ENOSYS;

	अगर (xen_feature(XENFEAT_स्वतः_translated_physmap) && gnttab_shared.addr == शून्य) अणु
		gnttab_shared.addr = xen_स्वतः_xlat_grant_frames.vaddr;
		अगर (gnttab_shared.addr == शून्य) अणु
			pr_warn("gnttab share frames is not mapped!\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस gnttab_map(0, nr_grant_frames - 1);
पूर्ण

पूर्णांक gnttab_resume(व्योम)
अणु
	gnttab_request_version();
	वापस gnttab_setup();
पूर्ण

पूर्णांक gnttab_suspend(व्योम)
अणु
	अगर (!xen_feature(XENFEAT_स्वतः_translated_physmap))
		gnttab_पूर्णांकerface->unmap_frames();
	वापस 0;
पूर्ण

अटल पूर्णांक gnttab_expand(अचिन्हित पूर्णांक req_entries)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक cur, extra;

	cur = nr_grant_frames;
	extra = ((req_entries + gnttab_पूर्णांकerface->grefs_per_grant_frame - 1) /
		 gnttab_पूर्णांकerface->grefs_per_grant_frame);
	अगर (cur + extra > gnttab_max_grant_frames()) अणु
		pr_warn_ratelimited("xen/grant-table: max_grant_frames reached"
				    " cur=%u extra=%u limit=%u"
				    " gnttab_free_count=%u req_entries=%u\n",
				    cur, extra, gnttab_max_grant_frames(),
				    gnttab_मुक्त_count, req_entries);
		वापस -ENOSPC;
	पूर्ण

	rc = gnttab_map(cur, cur + extra - 1);
	अगर (rc == 0)
		rc = grow_gnttab_list(extra);

	वापस rc;
पूर्ण

पूर्णांक gnttab_init(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ max_nr_grant_frames;
	अचिन्हित पूर्णांक max_nr_glist_frames, nr_glist_frames;
	अचिन्हित पूर्णांक nr_init_grefs;
	पूर्णांक ret;

	gnttab_request_version();
	max_nr_grant_frames = gnttab_max_grant_frames();
	nr_grant_frames = 1;

	/* Determine the maximum number of frames required क्रम the
	 * grant reference मुक्त list on the current hypervisor.
	 */
	max_nr_glist_frames = (max_nr_grant_frames *
			       gnttab_पूर्णांकerface->grefs_per_grant_frame / RPP);

	gnttab_list = kदो_स्मृति_array(max_nr_glist_frames,
				    माप(grant_ref_t *),
				    GFP_KERNEL);
	अगर (gnttab_list == शून्य)
		वापस -ENOMEM;

	nr_glist_frames = gnttab_frames(nr_grant_frames, RPP);
	क्रम (i = 0; i < nr_glist_frames; i++) अणु
		gnttab_list[i] = (grant_ref_t *)__get_मुक्त_page(GFP_KERNEL);
		अगर (gnttab_list[i] == शून्य) अणु
			ret = -ENOMEM;
			जाओ ini_nomem;
		पूर्ण
	पूर्ण

	ret = arch_gnttab_init(max_nr_grant_frames,
			       nr_status_frames(max_nr_grant_frames));
	अगर (ret < 0)
		जाओ ini_nomem;

	अगर (gnttab_setup() < 0) अणु
		ret = -ENODEV;
		जाओ ini_nomem;
	पूर्ण

	nr_init_grefs = nr_grant_frames *
			gnttab_पूर्णांकerface->grefs_per_grant_frame;

	क्रम (i = NR_RESERVED_ENTRIES; i < nr_init_grefs - 1; i++)
		gnttab_entry(i) = i + 1;

	gnttab_entry(nr_init_grefs - 1) = GNTTAB_LIST_END;
	gnttab_मुक्त_count = nr_init_grefs - NR_RESERVED_ENTRIES;
	gnttab_मुक्त_head  = NR_RESERVED_ENTRIES;

	prपूर्णांकk("Grant table initialized\n");
	वापस 0;

 ini_nomem:
	क्रम (i--; i >= 0; i--)
		मुक्त_page((अचिन्हित दीर्घ)gnttab_list[i]);
	kमुक्त(gnttab_list);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(gnttab_init);

अटल पूर्णांक __gnttab_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	/* Delay grant-table initialization in the PV on HVM हाल */
	अगर (xen_hvm_करोमुख्य() && !xen_pvh_करोमुख्य())
		वापस 0;

	वापस gnttab_init();
पूर्ण
/* Starts after core_initcall so that xen_pvh_gnttab_setup can be called
 * beक्रमehand to initialize xen_स्वतः_xlat_grant_frames. */
core_initcall_sync(__gnttab_init);
