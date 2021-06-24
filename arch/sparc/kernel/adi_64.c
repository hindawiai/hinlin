<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* adi_64.c: support क्रम ADI (Application Data Integrity) feature on
 * sparc m7 and newer processors. This feature is also known as
 * SSM (Silicon Secured Memory).
 *
 * Copyright (C) 2016 Oracle and/or its affiliates. All rights reserved.
 * Author: Khalid Aziz (khalid.aziz@oracle.com)
 */
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm_types.h>
#समावेश <यंत्र/mdesc.h>
#समावेश <यंत्र/adi_64.h>
#समावेश <यंत्र/mmu_64.h>
#समावेश <यंत्र/pgtable_64.h>

/* Each page of storage क्रम ADI tags can accommodate tags क्रम 128
 * pages. When ADI enabled pages are being swapped out, it would be
 * prudent to allocate at least enough tag storage space to accommodate
 * SWAPखाता_CLUSTER number of pages. Allocate enough tag storage to
 * store tags क्रम four SWAPखाता_CLUSTER pages to reduce need क्रम
 * further allocations क्रम same vma.
 */
#घोषणा TAG_STORAGE_PAGES	8

काष्ठा adi_config adi_state;
EXPORT_SYMBOL(adi_state);

/* mdesc_adi_init() : Parse machine description provided by the
 *	hypervisor to detect ADI capabilities
 *
 * Hypervisor reports ADI capabilities of platक्रमm in "hwcap-list" property
 * क्रम "cpu" node. If the platक्रमm supports ADI, "hwcap-list" property
 * contains the keyword "adp". If the platक्रमm supports ADI, "platform"
 * node will contain "adp-blksz", "adp-nbits" and "ue-on-adp" properties
 * to describe the ADI capabilities.
 */
व्योम __init mdesc_adi_init(व्योम)
अणु
	काष्ठा mdesc_handle *hp = mdesc_grab();
	स्थिर अक्षर *prop;
	u64 pn, *val;
	पूर्णांक len;

	अगर (!hp)
		जाओ adi_not_found;

	pn = mdesc_node_by_name(hp, MDESC_NODE_शून्य, "cpu");
	अगर (pn == MDESC_NODE_शून्य)
		जाओ adi_not_found;

	prop = mdesc_get_property(hp, pn, "hwcap-list", &len);
	अगर (!prop)
		जाओ adi_not_found;

	/*
	 * Look क्रम "adp" keyword in hwcap-list which would indicate
	 * ADI support
	 */
	adi_state.enabled = false;
	जबतक (len) अणु
		पूर्णांक plen;

		अगर (!म_भेद(prop, "adp")) अणु
			adi_state.enabled = true;
			अवरोध;
		पूर्ण

		plen = म_माप(prop) + 1;
		prop += plen;
		len -= plen;
	पूर्ण

	अगर (!adi_state.enabled)
		जाओ adi_not_found;

	/* Find the ADI properties in "platform" node. If all ADI
	 * properties are not found, ADI support is incomplete and
	 * करो not enable ADI in the kernel.
	 */
	pn = mdesc_node_by_name(hp, MDESC_NODE_शून्य, "platform");
	अगर (pn == MDESC_NODE_शून्य)
		जाओ adi_not_found;

	val = (u64 *) mdesc_get_property(hp, pn, "adp-blksz", &len);
	अगर (!val)
		जाओ adi_not_found;
	adi_state.caps.blksz = *val;

	val = (u64 *) mdesc_get_property(hp, pn, "adp-nbits", &len);
	अगर (!val)
		जाओ adi_not_found;
	adi_state.caps.nbits = *val;

	val = (u64 *) mdesc_get_property(hp, pn, "ue-on-adp", &len);
	अगर (!val)
		जाओ adi_not_found;
	adi_state.caps.ue_on_adi = *val;

	/* Some of the code to support swapping ADI tags is written
	 * assumption that two ADI tags can fit inside one byte. If
	 * this assumption is broken by a future architecture change,
	 * that code will have to be revisited. If that were to happen,
	 * disable ADI support so we करो not get unpredictable results
	 * with programs trying to use ADI and their pages getting
	 * swapped out
	 */
	अगर (adi_state.caps.nbits > 4) अणु
		pr_warn("WARNING: ADI tag size >4 on this platform. Disabling AADI support\n");
		adi_state.enabled = false;
	पूर्ण

	mdesc_release(hp);
	वापस;

adi_not_found:
	adi_state.enabled = false;
	adi_state.caps.blksz = 0;
	adi_state.caps.nbits = 0;
	अगर (hp)
		mdesc_release(hp);
पूर्ण

tag_storage_desc_t *find_tag_store(काष्ठा mm_काष्ठा *mm,
				   काष्ठा vm_area_काष्ठा *vma,
				   अचिन्हित दीर्घ addr)
अणु
	tag_storage_desc_t *tag_desc = शून्य;
	अचिन्हित दीर्घ i, max_desc, flags;

	/* Check अगर this vma alपढ़ोy has tag storage descriptor
	 * allocated क्रम it.
	 */
	max_desc = PAGE_SIZE/माप(tag_storage_desc_t);
	अगर (mm->context.tag_store) अणु
		tag_desc = mm->context.tag_store;
		spin_lock_irqsave(&mm->context.tag_lock, flags);
		क्रम (i = 0; i < max_desc; i++) अणु
			अगर ((addr >= tag_desc->start) &&
			    ((addr + PAGE_SIZE - 1) <= tag_desc->end))
				अवरोध;
			tag_desc++;
		पूर्ण
		spin_unlock_irqrestore(&mm->context.tag_lock, flags);

		/* If no matching entries were found, this must be a
		 * freshly allocated page
		 */
		अगर (i >= max_desc)
			tag_desc = शून्य;
	पूर्ण

	वापस tag_desc;
पूर्ण

tag_storage_desc_t *alloc_tag_store(काष्ठा mm_काष्ठा *mm,
				    काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ addr)
अणु
	अचिन्हित अक्षर *tags;
	अचिन्हित दीर्घ i, size, max_desc, flags;
	tag_storage_desc_t *tag_desc, *खोलो_desc;
	अचिन्हित दीर्घ end_addr, hole_start, hole_end;

	max_desc = PAGE_SIZE/माप(tag_storage_desc_t);
	खोलो_desc = शून्य;
	hole_start = 0;
	hole_end = अच_दीर्घ_उच्च;
	end_addr = addr + PAGE_SIZE - 1;

	/* Check अगर this vma alपढ़ोy has tag storage descriptor
	 * allocated क्रम it.
	 */
	spin_lock_irqsave(&mm->context.tag_lock, flags);
	अगर (mm->context.tag_store) अणु
		tag_desc = mm->context.tag_store;

		/* Look क्रम a matching entry क्रम this address. While करोing
		 * that, look क्रम the first खोलो slot as well and find
		 * the hole in alपढ़ोy allocated range where this request
		 * will fit in.
		 */
		क्रम (i = 0; i < max_desc; i++) अणु
			अगर (tag_desc->tag_users == 0) अणु
				अगर (खोलो_desc == शून्य)
					खोलो_desc = tag_desc;
			पूर्ण अन्यथा अणु
				अगर ((addr >= tag_desc->start) &&
				    (tag_desc->end >= (addr + PAGE_SIZE - 1))) अणु
					tag_desc->tag_users++;
					जाओ out;
				पूर्ण
			पूर्ण
			अगर ((tag_desc->start > end_addr) &&
			    (tag_desc->start < hole_end))
				hole_end = tag_desc->start;
			अगर ((tag_desc->end < addr) &&
			    (tag_desc->end > hole_start))
				hole_start = tag_desc->end;
			tag_desc++;
		पूर्ण

	पूर्ण अन्यथा अणु
		size = माप(tag_storage_desc_t)*max_desc;
		mm->context.tag_store = kzalloc(size, GFP_NOWAIT|__GFP_NOWARN);
		अगर (mm->context.tag_store == शून्य) अणु
			tag_desc = शून्य;
			जाओ out;
		पूर्ण
		tag_desc = mm->context.tag_store;
		क्रम (i = 0; i < max_desc; i++, tag_desc++)
			tag_desc->tag_users = 0;
		खोलो_desc = mm->context.tag_store;
		i = 0;
	पूर्ण

	/* Check अगर we ran out of tag storage descriptors */
	अगर (खोलो_desc == शून्य) अणु
		tag_desc = शून्य;
		जाओ out;
	पूर्ण

	/* Mark this tag descriptor slot in use and then initialize it */
	tag_desc = खोलो_desc;
	tag_desc->tag_users = 1;

	/* Tag storage has not been allocated क्रम this vma and space
	 * is available in tag storage descriptor. Since this page is
	 * being swapped out, there is high probability subsequent pages
	 * in the VMA will be swapped out as well. Allocate pages to
	 * store tags क्रम as many pages in this vma as possible but not
	 * more than TAG_STORAGE_PAGES. Each byte in tag space holds
	 * two ADI tags since each ADI tag is 4 bits. Each ADI tag
	 * covers adi_blksize() worth of addresses. Check अगर the hole is
	 * big enough to accommodate full address range क्रम using
	 * TAG_STORAGE_PAGES number of tag pages.
	 */
	size = TAG_STORAGE_PAGES * PAGE_SIZE;
	end_addr = addr + (size*2*adi_blksize()) - 1;
	/* Check क्रम overflow. If overflow occurs, allocate only one page */
	अगर (end_addr < addr) अणु
		size = PAGE_SIZE;
		end_addr = addr + (size*2*adi_blksize()) - 1;
		/* If overflow happens with the minimum tag storage
		 * allocation as well, adjust ending address क्रम this
		 * tag storage.
		 */
		अगर (end_addr < addr)
			end_addr = अच_दीर्घ_उच्च;
	पूर्ण
	अगर (hole_end < end_addr) अणु
		/* Available hole is too small on the upper end of
		 * address. Can we expand the range towards the lower
		 * address and maximize use of this slot?
		 */
		अचिन्हित दीर्घ पंचांगp_addr;

		end_addr = hole_end - 1;
		पंचांगp_addr = end_addr - (size*2*adi_blksize()) + 1;
		/* Check क्रम underflow. If underflow occurs, allocate
		 * only one page क्रम storing ADI tags
		 */
		अगर (पंचांगp_addr > addr) अणु
			size = PAGE_SIZE;
			पंचांगp_addr = end_addr - (size*2*adi_blksize()) - 1;
			/* If underflow happens with the minimum tag storage
			 * allocation as well, adjust starting address क्रम
			 * this tag storage.
			 */
			अगर (पंचांगp_addr > addr)
				पंचांगp_addr = 0;
		पूर्ण
		अगर (पंचांगp_addr < hole_start) अणु
			/* Available hole is restricted on lower address
			 * end as well
			 */
			पंचांगp_addr = hole_start + 1;
		पूर्ण
		addr = पंचांगp_addr;
		size = (end_addr + 1 - addr)/(2*adi_blksize());
		size = (size + (PAGE_SIZE-adi_blksize()))/PAGE_SIZE;
		size = size * PAGE_SIZE;
	पूर्ण
	tags = kzalloc(size, GFP_NOWAIT|__GFP_NOWARN);
	अगर (tags == शून्य) अणु
		tag_desc->tag_users = 0;
		tag_desc = शून्य;
		जाओ out;
	पूर्ण
	tag_desc->start = addr;
	tag_desc->tags = tags;
	tag_desc->end = end_addr;

out:
	spin_unlock_irqrestore(&mm->context.tag_lock, flags);
	वापस tag_desc;
पूर्ण

व्योम del_tag_store(tag_storage_desc_t *tag_desc, काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर *tags = शून्य;

	spin_lock_irqsave(&mm->context.tag_lock, flags);
	tag_desc->tag_users--;
	अगर (tag_desc->tag_users == 0) अणु
		tag_desc->start = tag_desc->end = 0;
		/* Do not मुक्त up the tag storage space allocated
		 * by the first descriptor. This is persistent
		 * emergency tag storage space क्रम the task.
		 */
		अगर (tag_desc != mm->context.tag_store) अणु
			tags = tag_desc->tags;
			tag_desc->tags = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&mm->context.tag_lock, flags);
	kमुक्त(tags);
पूर्ण

#घोषणा tag_start(addr, tag_desc)		\
	((tag_desc)->tags + ((addr - (tag_desc)->start)/(2*adi_blksize())))

/* Retrieve any saved ADI tags क्रम the page being swapped back in and
 * restore these tags to the newly allocated physical page.
 */
व्योम adi_restore_tags(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ addr, pte_t pte)
अणु
	अचिन्हित अक्षर *tag;
	tag_storage_desc_t *tag_desc;
	अचिन्हित दीर्घ paddr, पंचांगp, version1, version2;

	/* Check अगर the swapped out page has an ADI version
	 * saved. If yes, restore version tag to the newly
	 * allocated page.
	 */
	tag_desc = find_tag_store(mm, vma, addr);
	अगर (tag_desc == शून्य)
		वापस;

	tag = tag_start(addr, tag_desc);
	paddr = pte_val(pte) & _PAGE_PADDR_4V;
	क्रम (पंचांगp = paddr; पंचांगp < (paddr+PAGE_SIZE); पंचांगp += adi_blksize()) अणु
		version1 = (*tag) >> 4;
		version2 = (*tag) & 0x0f;
		*tag++ = 0;
		यंत्र अस्थिर("stxa %0, [%1] %2\n\t"
			:
			: "r" (version1), "r" (पंचांगp),
			  "i" (ASI_MCD_REAL));
		पंचांगp += adi_blksize();
		यंत्र अस्थिर("stxa %0, [%1] %2\n\t"
			:
			: "r" (version2), "r" (पंचांगp),
			  "i" (ASI_MCD_REAL));
	पूर्ण
	यंत्र अस्थिर("membar #Sync\n\t");

	/* Check and mark this tag space क्रम release later अगर
	 * the swapped in page was the last user of tag space
	 */
	del_tag_store(tag_desc, mm);
पूर्ण

/* A page is about to be swapped out. Save any ADI tags associated with
 * this physical page so they can be restored later when the page is swapped
 * back in.
 */
पूर्णांक adi_save_tags(काष्ठा mm_काष्ठा *mm, काष्ठा vm_area_काष्ठा *vma,
		  अचिन्हित दीर्घ addr, pte_t oldpte)
अणु
	अचिन्हित अक्षर *tag;
	tag_storage_desc_t *tag_desc;
	अचिन्हित दीर्घ version1, version2, paddr, पंचांगp;

	tag_desc = alloc_tag_store(mm, vma, addr);
	अगर (tag_desc == शून्य)
		वापस -1;

	tag = tag_start(addr, tag_desc);
	paddr = pte_val(oldpte) & _PAGE_PADDR_4V;
	क्रम (पंचांगp = paddr; पंचांगp < (paddr+PAGE_SIZE); पंचांगp += adi_blksize()) अणु
		यंत्र अस्थिर("ldxa [%1] %2, %0\n\t"
				: "=r" (version1)
				: "r" (पंचांगp), "i" (ASI_MCD_REAL));
		पंचांगp += adi_blksize();
		यंत्र अस्थिर("ldxa [%1] %2, %0\n\t"
				: "=r" (version2)
				: "r" (पंचांगp), "i" (ASI_MCD_REAL));
		*tag = (version1 << 4) | version2;
		tag++;
	पूर्ण

	वापस 0;
पूर्ण
