<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2017 Intel Corporation. All rights reserved.
 */
#समावेश <linux/libnvdimm.h>
#समावेश <linux/badblocks.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/ndctl.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश "nd-core.h"
#समावेश "nd.h"

व्योम badrange_init(काष्ठा badrange *badrange)
अणु
	INIT_LIST_HEAD(&badrange->list);
	spin_lock_init(&badrange->lock);
पूर्ण
EXPORT_SYMBOL_GPL(badrange_init);

अटल व्योम append_badrange_entry(काष्ठा badrange *badrange,
		काष्ठा badrange_entry *bre, u64 addr, u64 length)
अणु
	lockdep_निश्चित_held(&badrange->lock);
	bre->start = addr;
	bre->length = length;
	list_add_tail(&bre->list, &badrange->list);
पूर्ण

अटल पूर्णांक alloc_and_append_badrange_entry(काष्ठा badrange *badrange,
		u64 addr, u64 length, gfp_t flags)
अणु
	काष्ठा badrange_entry *bre;

	bre = kzalloc(माप(*bre), flags);
	अगर (!bre)
		वापस -ENOMEM;

	append_badrange_entry(badrange, bre, addr, length);
	वापस 0;
पूर्ण

अटल पूर्णांक add_badrange(काष्ठा badrange *badrange, u64 addr, u64 length)
अणु
	काष्ठा badrange_entry *bre, *bre_new;

	spin_unlock(&badrange->lock);
	bre_new = kzalloc(माप(*bre_new), GFP_KERNEL);
	spin_lock(&badrange->lock);

	अगर (list_empty(&badrange->list)) अणु
		अगर (!bre_new)
			वापस -ENOMEM;
		append_badrange_entry(badrange, bre_new, addr, length);
		वापस 0;
	पूर्ण

	/*
	 * There is a chance this is a duplicate, check क्रम those first.
	 * This will be the common हाल as ARS_STATUS वापसs all known
	 * errors in the SPA space, and we can't query it per region
	 */
	list_क्रम_each_entry(bre, &badrange->list, list)
		अगर (bre->start == addr) अणु
			/* If length has changed, update this list entry */
			अगर (bre->length != length)
				bre->length = length;
			kमुक्त(bre_new);
			वापस 0;
		पूर्ण

	/*
	 * If not a duplicate or a simple length update, add the entry as is,
	 * as any overlapping ranges will get resolved when the list is consumed
	 * and converted to badblocks
	 */
	अगर (!bre_new)
		वापस -ENOMEM;
	append_badrange_entry(badrange, bre_new, addr, length);

	वापस 0;
पूर्ण

पूर्णांक badrange_add(काष्ठा badrange *badrange, u64 addr, u64 length)
अणु
	पूर्णांक rc;

	spin_lock(&badrange->lock);
	rc = add_badrange(badrange, addr, length);
	spin_unlock(&badrange->lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(badrange_add);

व्योम badrange_क्रमget(काष्ठा badrange *badrange, phys_addr_t start,
		अचिन्हित पूर्णांक len)
अणु
	काष्ठा list_head *badrange_list = &badrange->list;
	u64 clr_end = start + len - 1;
	काष्ठा badrange_entry *bre, *next;

	spin_lock(&badrange->lock);

	/*
	 * [start, clr_end] is the badrange पूर्णांकerval being cleared.
	 * [bre->start, bre_end] is the badrange_list entry we're comparing
	 * the above पूर्णांकerval against. The badrange list entry may need
	 * to be modअगरied (update either start or length), deleted, or
	 * split पूर्णांकo two based on the overlap अक्षरacteristics
	 */

	list_क्रम_each_entry_safe(bre, next, badrange_list, list) अणु
		u64 bre_end = bre->start + bre->length - 1;

		/* Skip पूर्णांकervals with no पूर्णांकersection */
		अगर (bre_end < start)
			जारी;
		अगर (bre->start >  clr_end)
			जारी;
		/* Delete completely overlapped badrange entries */
		अगर ((bre->start >= start) && (bre_end <= clr_end)) अणु
			list_del(&bre->list);
			kमुक्त(bre);
			जारी;
		पूर्ण
		/* Adjust start poपूर्णांक of partially cleared entries */
		अगर ((start <= bre->start) && (clr_end > bre->start)) अणु
			bre->length -= clr_end - bre->start + 1;
			bre->start = clr_end + 1;
			जारी;
		पूर्ण
		/* Adjust bre->length क्रम partial clearing at the tail end */
		अगर ((bre->start < start) && (bre_end <= clr_end)) अणु
			/* bre->start reमुख्यs the same */
			bre->length = start - bre->start;
			जारी;
		पूर्ण
		/*
		 * If clearing in the middle of an entry, we split it पूर्णांकo
		 * two by modअगरying the current entry to represent one half of
		 * the split, and adding a new entry क्रम the second half.
		 */
		अगर ((bre->start < start) && (bre_end > clr_end)) अणु
			u64 new_start = clr_end + 1;
			u64 new_len = bre_end - new_start + 1;

			/* Add new entry covering the right half */
			alloc_and_append_badrange_entry(badrange, new_start,
					new_len, GFP_NOWAIT);
			/* Adjust this entry to cover the left half */
			bre->length = start - bre->start;
			जारी;
		पूर्ण
	पूर्ण
	spin_unlock(&badrange->lock);
पूर्ण
EXPORT_SYMBOL_GPL(badrange_क्रमget);

अटल व्योम set_badblock(काष्ठा badblocks *bb, sector_t s, पूर्णांक num)
अणु
	dev_dbg(bb->dev, "Found a bad range (0x%llx, 0x%llx)\n",
			(u64) s * 512, (u64) num * 512);
	/* this isn't an error as the hardware will still throw an exception */
	अगर (badblocks_set(bb, s, num, 1))
		dev_info_once(bb->dev, "%s: failed for sector %llx\n",
				__func__, (u64) s);
पूर्ण

/**
 * __add_badblock_range() - Convert a physical address range to bad sectors
 * @bb:		badblocks instance to populate
 * @ns_offset:	namespace offset where the error range begins (in bytes)
 * @len:	number of bytes of badrange to be added
 *
 * This assumes that the range provided with (ns_offset, len) is within
 * the bounds of physical addresses क्रम this namespace, i.e. lies in the
 * पूर्णांकerval [ns_start, ns_start + ns_size)
 */
अटल व्योम __add_badblock_range(काष्ठा badblocks *bb, u64 ns_offset, u64 len)
अणु
	स्थिर अचिन्हित पूर्णांक sector_size = 512;
	sector_t start_sector, end_sector;
	u64 num_sectors;
	u32 rem;

	start_sector = भाग_u64(ns_offset, sector_size);
	end_sector = भाग_u64_rem(ns_offset + len, sector_size, &rem);
	अगर (rem)
		end_sector++;
	num_sectors = end_sector - start_sector;

	अगर (unlikely(num_sectors > (u64)पूर्णांक_उच्च)) अणु
		u64 reमुख्यing = num_sectors;
		sector_t s = start_sector;

		जबतक (reमुख्यing) अणु
			पूर्णांक करोne = min_t(u64, reमुख्यing, पूर्णांक_उच्च);

			set_badblock(bb, s, करोne);
			reमुख्यing -= करोne;
			s += करोne;
		पूर्ण
	पूर्ण अन्यथा
		set_badblock(bb, start_sector, num_sectors);
पूर्ण

अटल व्योम badblocks_populate(काष्ठा badrange *badrange,
		काष्ठा badblocks *bb, स्थिर काष्ठा range *range)
अणु
	काष्ठा badrange_entry *bre;

	अगर (list_empty(&badrange->list))
		वापस;

	list_क्रम_each_entry(bre, &badrange->list, list) अणु
		u64 bre_end = bre->start + bre->length - 1;

		/* Discard पूर्णांकervals with no पूर्णांकersection */
		अगर (bre_end < range->start)
			जारी;
		अगर (bre->start > range->end)
			जारी;
		/* Deal with any overlap after start of the namespace */
		अगर (bre->start >= range->start) अणु
			u64 start = bre->start;
			u64 len;

			अगर (bre_end <= range->end)
				len = bre->length;
			अन्यथा
				len = range->start + range_len(range)
					- bre->start;
			__add_badblock_range(bb, start - range->start, len);
			जारी;
		पूर्ण
		/*
		 * Deal with overlap क्रम badrange starting beक्रमe
		 * the namespace.
		 */
		अगर (bre->start < range->start) अणु
			u64 len;

			अगर (bre_end < range->end)
				len = bre->start + bre->length - range->start;
			अन्यथा
				len = range_len(range);
			__add_badblock_range(bb, 0, len);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * nvdimm_badblocks_populate() - Convert a list of badranges to badblocks
 * @region: parent region of the range to पूर्णांकerrogate
 * @bb: badblocks instance to populate
 * @res: resource range to consider
 *
 * The badrange list generated during bus initialization may contain
 * multiple, possibly overlapping physical address ranges.  Compare each
 * of these ranges to the resource range currently being initialized,
 * and add badblocks entries क्रम all matching sub-ranges
 */
व्योम nvdimm_badblocks_populate(काष्ठा nd_region *nd_region,
		काष्ठा badblocks *bb, स्थिर काष्ठा range *range)
अणु
	काष्ठा nvdimm_bus *nvdimm_bus;

	अगर (!is_memory(&nd_region->dev)) अणु
		dev_WARN_ONCE(&nd_region->dev, 1,
				"%s only valid for pmem regions\n", __func__);
		वापस;
	पूर्ण
	nvdimm_bus = walk_to_nvdimm_bus(&nd_region->dev);

	nvdimm_bus_lock(&nvdimm_bus->dev);
	badblocks_populate(&nvdimm_bus->badrange, bb, range);
	nvdimm_bus_unlock(&nvdimm_bus->dev);
पूर्ण
EXPORT_SYMBOL_GPL(nvdimm_badblocks_populate);
