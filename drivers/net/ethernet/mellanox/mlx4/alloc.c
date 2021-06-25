<शैली गुरु>
/*
 * Copyright (c) 2006, 2007 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "mlx4.h"

u32 mlx4_biपंचांगap_alloc(काष्ठा mlx4_biपंचांगap *biपंचांगap)
अणु
	u32 obj;

	spin_lock(&biपंचांगap->lock);

	obj = find_next_zero_bit(biपंचांगap->table, biपंचांगap->max, biपंचांगap->last);
	अगर (obj >= biपंचांगap->max) अणु
		biपंचांगap->top = (biपंचांगap->top + biपंचांगap->max + biपंचांगap->reserved_top)
				& biपंचांगap->mask;
		obj = find_first_zero_bit(biपंचांगap->table, biपंचांगap->max);
	पूर्ण

	अगर (obj < biपंचांगap->max) अणु
		set_bit(obj, biपंचांगap->table);
		biपंचांगap->last = (obj + 1);
		अगर (biपंचांगap->last == biपंचांगap->max)
			biपंचांगap->last = 0;
		obj |= biपंचांगap->top;
	पूर्ण अन्यथा
		obj = -1;

	अगर (obj != -1)
		--biपंचांगap->avail;

	spin_unlock(&biपंचांगap->lock);

	वापस obj;
पूर्ण

व्योम mlx4_biपंचांगap_मुक्त(काष्ठा mlx4_biपंचांगap *biपंचांगap, u32 obj, पूर्णांक use_rr)
अणु
	mlx4_biपंचांगap_मुक्त_range(biपंचांगap, obj, 1, use_rr);
पूर्ण

अटल अचिन्हित दीर्घ find_aligned_range(अचिन्हित दीर्घ *biपंचांगap,
					u32 start, u32 nbits,
					पूर्णांक len, पूर्णांक align, u32 skip_mask)
अणु
	अचिन्हित दीर्घ end, i;

again:
	start = ALIGN(start, align);

	जबतक ((start < nbits) && (test_bit(start, biपंचांगap) ||
				   (start & skip_mask)))
		start += align;

	अगर (start >= nbits)
		वापस -1;

	end = start+len;
	अगर (end > nbits)
		वापस -1;

	क्रम (i = start + 1; i < end; i++) अणु
		अगर (test_bit(i, biपंचांगap) || ((u32)i & skip_mask)) अणु
			start = i + 1;
			जाओ again;
		पूर्ण
	पूर्ण

	वापस start;
पूर्ण

u32 mlx4_biपंचांगap_alloc_range(काष्ठा mlx4_biपंचांगap *biपंचांगap, पूर्णांक cnt,
			    पूर्णांक align, u32 skip_mask)
अणु
	u32 obj;

	अगर (likely(cnt == 1 && align == 1 && !skip_mask))
		वापस mlx4_biपंचांगap_alloc(biपंचांगap);

	spin_lock(&biपंचांगap->lock);

	obj = find_aligned_range(biपंचांगap->table, biपंचांगap->last,
				 biपंचांगap->max, cnt, align, skip_mask);
	अगर (obj >= biपंचांगap->max) अणु
		biपंचांगap->top = (biपंचांगap->top + biपंचांगap->max + biपंचांगap->reserved_top)
				& biपंचांगap->mask;
		obj = find_aligned_range(biपंचांगap->table, 0, biपंचांगap->max,
					 cnt, align, skip_mask);
	पूर्ण

	अगर (obj < biपंचांगap->max) अणु
		biपंचांगap_set(biपंचांगap->table, obj, cnt);
		अगर (obj == biपंचांगap->last) अणु
			biपंचांगap->last = (obj + cnt);
			अगर (biपंचांगap->last >= biपंचांगap->max)
				biपंचांगap->last = 0;
		पूर्ण
		obj |= biपंचांगap->top;
	पूर्ण अन्यथा
		obj = -1;

	अगर (obj != -1)
		biपंचांगap->avail -= cnt;

	spin_unlock(&biपंचांगap->lock);

	वापस obj;
पूर्ण

u32 mlx4_biपंचांगap_avail(काष्ठा mlx4_biपंचांगap *biपंचांगap)
अणु
	वापस biपंचांगap->avail;
पूर्ण

अटल u32 mlx4_biपंचांगap_masked_value(काष्ठा mlx4_biपंचांगap *biपंचांगap, u32 obj)
अणु
	वापस obj & (biपंचांगap->max + biपंचांगap->reserved_top - 1);
पूर्ण

व्योम mlx4_biपंचांगap_मुक्त_range(काष्ठा mlx4_biपंचांगap *biपंचांगap, u32 obj, पूर्णांक cnt,
			    पूर्णांक use_rr)
अणु
	obj &= biपंचांगap->max + biपंचांगap->reserved_top - 1;

	spin_lock(&biपंचांगap->lock);
	अगर (!use_rr) अणु
		biपंचांगap->last = min(biपंचांगap->last, obj);
		biपंचांगap->top = (biपंचांगap->top + biपंचांगap->max + biपंचांगap->reserved_top)
				& biपंचांगap->mask;
	पूर्ण
	biपंचांगap_clear(biपंचांगap->table, obj, cnt);
	biपंचांगap->avail += cnt;
	spin_unlock(&biपंचांगap->lock);
पूर्ण

पूर्णांक mlx4_biपंचांगap_init(काष्ठा mlx4_biपंचांगap *biपंचांगap, u32 num, u32 mask,
		     u32 reserved_bot, u32 reserved_top)
अणु
	/* num must be a घातer of 2 */
	अगर (num != roundup_घात_of_two(num))
		वापस -EINVAL;

	biपंचांगap->last = 0;
	biपंचांगap->top  = 0;
	biपंचांगap->max  = num - reserved_top;
	biपंचांगap->mask = mask;
	biपंचांगap->reserved_top = reserved_top;
	biपंचांगap->avail = num - reserved_top - reserved_bot;
	biपंचांगap->effective_len = biपंचांगap->avail;
	spin_lock_init(&biपंचांगap->lock);
	biपंचांगap->table = biपंचांगap_zalloc(biपंचांगap->max, GFP_KERNEL);
	अगर (!biपंचांगap->table)
		वापस -ENOMEM;

	biपंचांगap_set(biपंचांगap->table, 0, reserved_bot);

	वापस 0;
पूर्ण

व्योम mlx4_biपंचांगap_cleanup(काष्ठा mlx4_biपंचांगap *biपंचांगap)
अणु
	biपंचांगap_मुक्त(biपंचांगap->table);
पूर्ण

काष्ठा mlx4_zone_allocator अणु
	काष्ठा list_head		entries;
	काष्ठा list_head		prios;
	u32				last_uid;
	u32				mask;
	/* protect the zone_allocator from concurrent accesses */
	spinlock_t			lock;
	क्रमागत mlx4_zone_alloc_flags	flags;
पूर्ण;

काष्ठा mlx4_zone_entry अणु
	काष्ठा list_head		list;
	काष्ठा list_head		prio_list;
	u32				uid;
	काष्ठा mlx4_zone_allocator	*allocator;
	काष्ठा mlx4_biपंचांगap		*biपंचांगap;
	पूर्णांक				use_rr;
	पूर्णांक				priority;
	पूर्णांक				offset;
	क्रमागत mlx4_zone_flags		flags;
पूर्ण;

काष्ठा mlx4_zone_allocator *mlx4_zone_allocator_create(क्रमागत mlx4_zone_alloc_flags flags)
अणु
	काष्ठा mlx4_zone_allocator *zones = kदो_स्मृति(माप(*zones), GFP_KERNEL);

	अगर (शून्य == zones)
		वापस शून्य;

	INIT_LIST_HEAD(&zones->entries);
	INIT_LIST_HEAD(&zones->prios);
	spin_lock_init(&zones->lock);
	zones->last_uid = 0;
	zones->mask = 0;
	zones->flags = flags;

	वापस zones;
पूर्ण

पूर्णांक mlx4_zone_add_one(काष्ठा mlx4_zone_allocator *zone_alloc,
		      काष्ठा mlx4_biपंचांगap *biपंचांगap,
		      u32 flags,
		      पूर्णांक priority,
		      पूर्णांक offset,
		      u32 *puid)
अणु
	u32 mask = mlx4_biपंचांगap_masked_value(biपंचांगap, (u32)-1);
	काष्ठा mlx4_zone_entry *it;
	काष्ठा mlx4_zone_entry *zone = kदो_स्मृति(माप(*zone), GFP_KERNEL);

	अगर (शून्य == zone)
		वापस -ENOMEM;

	zone->flags = flags;
	zone->biपंचांगap = biपंचांगap;
	zone->use_rr = (flags & MLX4_ZONE_USE_RR) ? MLX4_USE_RR : 0;
	zone->priority = priority;
	zone->offset = offset;

	spin_lock(&zone_alloc->lock);

	zone->uid = zone_alloc->last_uid++;
	zone->allocator = zone_alloc;

	अगर (zone_alloc->mask < mask)
		zone_alloc->mask = mask;

	list_क्रम_each_entry(it, &zone_alloc->prios, prio_list)
		अगर (it->priority >= priority)
			अवरोध;

	अगर (&it->prio_list == &zone_alloc->prios || it->priority > priority)
		list_add_tail(&zone->prio_list, &it->prio_list);
	list_add_tail(&zone->list, &it->list);

	spin_unlock(&zone_alloc->lock);

	*puid = zone->uid;

	वापस 0;
पूर्ण

/* Should be called under a lock */
अटल व्योम __mlx4_zone_हटाओ_one_entry(काष्ठा mlx4_zone_entry *entry)
अणु
	काष्ठा mlx4_zone_allocator *zone_alloc = entry->allocator;

	अगर (!list_empty(&entry->prio_list)) अणु
		/* Check अगर we need to add an alternative node to the prio list */
		अगर (!list_is_last(&entry->list, &zone_alloc->entries)) अणु
			काष्ठा mlx4_zone_entry *next = list_first_entry(&entry->list,
									typeof(*next),
									list);

			अगर (next->priority == entry->priority)
				list_add_tail(&next->prio_list, &entry->prio_list);
		पूर्ण

		list_del(&entry->prio_list);
	पूर्ण

	list_del(&entry->list);

	अगर (zone_alloc->flags & MLX4_ZONE_ALLOC_FLAGS_NO_OVERLAP) अणु
		u32 mask = 0;
		काष्ठा mlx4_zone_entry *it;

		list_क्रम_each_entry(it, &zone_alloc->prios, prio_list) अणु
			u32 cur_mask = mlx4_biपंचांगap_masked_value(it->biपंचांगap, (u32)-1);

			अगर (mask < cur_mask)
				mask = cur_mask;
		पूर्ण
		zone_alloc->mask = mask;
	पूर्ण
पूर्ण

व्योम mlx4_zone_allocator_destroy(काष्ठा mlx4_zone_allocator *zone_alloc)
अणु
	काष्ठा mlx4_zone_entry *zone, *पंचांगp;

	spin_lock(&zone_alloc->lock);

	list_क्रम_each_entry_safe(zone, पंचांगp, &zone_alloc->entries, list) अणु
		list_del(&zone->list);
		list_del(&zone->prio_list);
		kमुक्त(zone);
	पूर्ण

	spin_unlock(&zone_alloc->lock);
	kमुक्त(zone_alloc);
पूर्ण

/* Should be called under a lock */
अटल u32 __mlx4_alloc_from_zone(काष्ठा mlx4_zone_entry *zone, पूर्णांक count,
				  पूर्णांक align, u32 skip_mask, u32 *puid)
अणु
	u32 uid = 0;
	u32 res;
	काष्ठा mlx4_zone_allocator *zone_alloc = zone->allocator;
	काष्ठा mlx4_zone_entry *curr_node;

	res = mlx4_biपंचांगap_alloc_range(zone->biपंचांगap, count,
				      align, skip_mask);

	अगर (res != (u32)-1) अणु
		res += zone->offset;
		uid = zone->uid;
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(curr_node, &zone_alloc->prios, prio_list) अणु
		अगर (unlikely(curr_node->priority == zone->priority))
			अवरोध;
	पूर्ण

	अगर (zone->flags & MLX4_ZONE_ALLOW_ALLOC_FROM_LOWER_PRIO) अणु
		काष्ठा mlx4_zone_entry *it = curr_node;

		list_क्रम_each_entry_जारी_reverse(it, &zone_alloc->entries, list) अणु
			res = mlx4_biपंचांगap_alloc_range(it->biपंचांगap, count,
						      align, skip_mask);
			अगर (res != (u32)-1) अणु
				res += it->offset;
				uid = it->uid;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (zone->flags & MLX4_ZONE_ALLOW_ALLOC_FROM_EQ_PRIO) अणु
		काष्ठा mlx4_zone_entry *it = curr_node;

		list_क्रम_each_entry_from(it, &zone_alloc->entries, list) अणु
			अगर (unlikely(it == zone))
				जारी;

			अगर (unlikely(it->priority != curr_node->priority))
				अवरोध;

			res = mlx4_biपंचांगap_alloc_range(it->biपंचांगap, count,
						      align, skip_mask);
			अगर (res != (u32)-1) अणु
				res += it->offset;
				uid = it->uid;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (zone->flags & MLX4_ZONE_FALLBACK_TO_HIGHER_PRIO) अणु
		अगर (list_is_last(&curr_node->prio_list, &zone_alloc->prios))
			जाओ out;

		curr_node = list_first_entry(&curr_node->prio_list,
					     typeof(*curr_node),
					     prio_list);

		list_क्रम_each_entry_from(curr_node, &zone_alloc->entries, list) अणु
			res = mlx4_biपंचांगap_alloc_range(curr_node->biपंचांगap, count,
						      align, skip_mask);
			अगर (res != (u32)-1) अणु
				res += curr_node->offset;
				uid = curr_node->uid;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	अगर (शून्य != puid && res != (u32)-1)
		*puid = uid;
	वापस res;
पूर्ण

/* Should be called under a lock */
अटल व्योम __mlx4_मुक्त_from_zone(काष्ठा mlx4_zone_entry *zone, u32 obj,
				  u32 count)
अणु
	mlx4_biपंचांगap_मुक्त_range(zone->biपंचांगap, obj - zone->offset, count, zone->use_rr);
पूर्ण

/* Should be called under a lock */
अटल काष्ठा mlx4_zone_entry *__mlx4_find_zone_by_uid(
		काष्ठा mlx4_zone_allocator *zones, u32 uid)
अणु
	काष्ठा mlx4_zone_entry *zone;

	list_क्रम_each_entry(zone, &zones->entries, list) अणु
		अगर (zone->uid == uid)
			वापस zone;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा mlx4_biपंचांगap *mlx4_zone_get_biपंचांगap(काष्ठा mlx4_zone_allocator *zones, u32 uid)
अणु
	काष्ठा mlx4_zone_entry *zone;
	काष्ठा mlx4_biपंचांगap *biपंचांगap;

	spin_lock(&zones->lock);

	zone = __mlx4_find_zone_by_uid(zones, uid);

	biपंचांगap = zone == शून्य ? शून्य : zone->biपंचांगap;

	spin_unlock(&zones->lock);

	वापस biपंचांगap;
पूर्ण

पूर्णांक mlx4_zone_हटाओ_one(काष्ठा mlx4_zone_allocator *zones, u32 uid)
अणु
	काष्ठा mlx4_zone_entry *zone;
	पूर्णांक res = 0;

	spin_lock(&zones->lock);

	zone = __mlx4_find_zone_by_uid(zones, uid);

	अगर (शून्य == zone) अणु
		res = -1;
		जाओ out;
	पूर्ण

	__mlx4_zone_हटाओ_one_entry(zone);

out:
	spin_unlock(&zones->lock);
	kमुक्त(zone);

	वापस res;
पूर्ण

/* Should be called under a lock */
अटल काष्ठा mlx4_zone_entry *__mlx4_find_zone_by_uid_unique(
		काष्ठा mlx4_zone_allocator *zones, u32 obj)
अणु
	काष्ठा mlx4_zone_entry *zone, *zone_candidate = शून्य;
	u32 dist = (u32)-1;

	/* Search क्रम the smallest zone that this obj could be
	 * allocated from. This is करोne in order to handle
	 * situations when small biपंचांगaps are allocated from bigger
	 * biपंचांगaps (and the allocated space is marked as reserved in
	 * the bigger biपंचांगap.
	 */
	list_क्रम_each_entry(zone, &zones->entries, list) अणु
		अगर (obj >= zone->offset) अणु
			u32 mobj = (obj - zone->offset) & zones->mask;

			अगर (mobj < zone->biपंचांगap->max) अणु
				u32 curr_dist = zone->biपंचांगap->effective_len;

				अगर (curr_dist < dist) अणु
					dist = curr_dist;
					zone_candidate = zone;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस zone_candidate;
पूर्ण

u32 mlx4_zone_alloc_entries(काष्ठा mlx4_zone_allocator *zones, u32 uid, पूर्णांक count,
			    पूर्णांक align, u32 skip_mask, u32 *puid)
अणु
	काष्ठा mlx4_zone_entry *zone;
	पूर्णांक res = -1;

	spin_lock(&zones->lock);

	zone = __mlx4_find_zone_by_uid(zones, uid);

	अगर (शून्य == zone)
		जाओ out;

	res = __mlx4_alloc_from_zone(zone, count, align, skip_mask, puid);

out:
	spin_unlock(&zones->lock);

	वापस res;
पूर्ण

u32 mlx4_zone_मुक्त_entries(काष्ठा mlx4_zone_allocator *zones, u32 uid, u32 obj, u32 count)
अणु
	काष्ठा mlx4_zone_entry *zone;
	पूर्णांक res = 0;

	spin_lock(&zones->lock);

	zone = __mlx4_find_zone_by_uid(zones, uid);

	अगर (शून्य == zone) अणु
		res = -1;
		जाओ out;
	पूर्ण

	__mlx4_मुक्त_from_zone(zone, obj, count);

out:
	spin_unlock(&zones->lock);

	वापस res;
पूर्ण

u32 mlx4_zone_मुक्त_entries_unique(काष्ठा mlx4_zone_allocator *zones, u32 obj, u32 count)
अणु
	काष्ठा mlx4_zone_entry *zone;
	पूर्णांक res;

	अगर (!(zones->flags & MLX4_ZONE_ALLOC_FLAGS_NO_OVERLAP))
		वापस -EFAULT;

	spin_lock(&zones->lock);

	zone = __mlx4_find_zone_by_uid_unique(zones, obj);

	अगर (शून्य == zone) अणु
		res = -1;
		जाओ out;
	पूर्ण

	__mlx4_मुक्त_from_zone(zone, obj, count);
	res = 0;

out:
	spin_unlock(&zones->lock);

	वापस res;
पूर्ण

अटल पूर्णांक mlx4_buf_direct_alloc(काष्ठा mlx4_dev *dev, पूर्णांक size,
				 काष्ठा mlx4_buf *buf)
अणु
	dma_addr_t t;

	buf->nbufs        = 1;
	buf->npages       = 1;
	buf->page_shअगरt   = get_order(size) + PAGE_SHIFT;
	buf->direct.buf   =
		dma_alloc_coherent(&dev->persist->pdev->dev, size, &t,
				   GFP_KERNEL);
	अगर (!buf->direct.buf)
		वापस -ENOMEM;

	buf->direct.map = t;

	जबतक (t & ((1 << buf->page_shअगरt) - 1)) अणु
		--buf->page_shअगरt;
		buf->npages *= 2;
	पूर्ण

	वापस 0;
पूर्ण

/* Handling क्रम queue buffers -- we allocate a bunch of memory and
 * रेजिस्टर it in a memory region at HCA भव address 0. If the
 *  requested size is > max_direct, we split the allocation पूर्णांकo
 *  multiple pages, so we करोn't require too much contiguous memory.
 */
पूर्णांक mlx4_buf_alloc(काष्ठा mlx4_dev *dev, पूर्णांक size, पूर्णांक max_direct,
		   काष्ठा mlx4_buf *buf)
अणु
	अगर (size <= max_direct) अणु
		वापस mlx4_buf_direct_alloc(dev, size, buf);
	पूर्ण अन्यथा अणु
		dma_addr_t t;
		पूर्णांक i;

		buf->direct.buf = शून्य;
		buf->nbufs      = DIV_ROUND_UP(size, PAGE_SIZE);
		buf->npages	= buf->nbufs;
		buf->page_shअगरt  = PAGE_SHIFT;
		buf->page_list   = kसुस्मृति(buf->nbufs, माप(*buf->page_list),
					   GFP_KERNEL);
		अगर (!buf->page_list)
			वापस -ENOMEM;

		क्रम (i = 0; i < buf->nbufs; ++i) अणु
			buf->page_list[i].buf =
				dma_alloc_coherent(&dev->persist->pdev->dev,
						   PAGE_SIZE, &t, GFP_KERNEL);
			अगर (!buf->page_list[i].buf)
				जाओ err_मुक्त;

			buf->page_list[i].map = t;
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त:
	mlx4_buf_मुक्त(dev, size, buf);

	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_buf_alloc);

व्योम mlx4_buf_मुक्त(काष्ठा mlx4_dev *dev, पूर्णांक size, काष्ठा mlx4_buf *buf)
अणु
	अगर (buf->nbufs == 1) अणु
		dma_मुक्त_coherent(&dev->persist->pdev->dev, size,
				  buf->direct.buf, buf->direct.map);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < buf->nbufs; ++i)
			अगर (buf->page_list[i].buf)
				dma_मुक्त_coherent(&dev->persist->pdev->dev,
						  PAGE_SIZE,
						  buf->page_list[i].buf,
						  buf->page_list[i].map);
		kमुक्त(buf->page_list);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_buf_मुक्त);

अटल काष्ठा mlx4_db_pgdir *mlx4_alloc_db_pgdir(काष्ठा device *dma_device)
अणु
	काष्ठा mlx4_db_pgdir *pgdir;

	pgdir = kzalloc(माप(*pgdir), GFP_KERNEL);
	अगर (!pgdir)
		वापस शून्य;

	biपंचांगap_fill(pgdir->order1, MLX4_DB_PER_PAGE / 2);
	pgdir->bits[0] = pgdir->order0;
	pgdir->bits[1] = pgdir->order1;
	pgdir->db_page = dma_alloc_coherent(dma_device, PAGE_SIZE,
					    &pgdir->db_dma, GFP_KERNEL);
	अगर (!pgdir->db_page) अणु
		kमुक्त(pgdir);
		वापस शून्य;
	पूर्ण

	वापस pgdir;
पूर्ण

अटल पूर्णांक mlx4_alloc_db_from_pgdir(काष्ठा mlx4_db_pgdir *pgdir,
				    काष्ठा mlx4_db *db, पूर्णांक order)
अणु
	पूर्णांक o;
	पूर्णांक i;

	क्रम (o = order; o <= 1; ++o) अणु
		i = find_first_bit(pgdir->bits[o], MLX4_DB_PER_PAGE >> o);
		अगर (i < MLX4_DB_PER_PAGE >> o)
			जाओ found;
	पूर्ण

	वापस -ENOMEM;

found:
	clear_bit(i, pgdir->bits[o]);

	i <<= o;

	अगर (o > order)
		set_bit(i ^ 1, pgdir->bits[order]);

	db->u.pgdir = pgdir;
	db->index   = i;
	db->db      = pgdir->db_page + db->index;
	db->dma     = pgdir->db_dma  + db->index * 4;
	db->order   = order;

	वापस 0;
पूर्ण

पूर्णांक mlx4_db_alloc(काष्ठा mlx4_dev *dev, काष्ठा mlx4_db *db, पूर्णांक order)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_db_pgdir *pgdir;
	पूर्णांक ret = 0;

	mutex_lock(&priv->pgdir_mutex);

	list_क्रम_each_entry(pgdir, &priv->pgdir_list, list)
		अगर (!mlx4_alloc_db_from_pgdir(pgdir, db, order))
			जाओ out;

	pgdir = mlx4_alloc_db_pgdir(&dev->persist->pdev->dev);
	अगर (!pgdir) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	list_add(&pgdir->list, &priv->pgdir_list);

	/* This should never fail -- we just allocated an empty page: */
	WARN_ON(mlx4_alloc_db_from_pgdir(pgdir, db, order));

out:
	mutex_unlock(&priv->pgdir_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_db_alloc);

व्योम mlx4_db_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_db *db)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक o;
	पूर्णांक i;

	mutex_lock(&priv->pgdir_mutex);

	o = db->order;
	i = db->index;

	अगर (db->order == 0 && test_bit(i ^ 1, db->u.pgdir->order0)) अणु
		clear_bit(i ^ 1, db->u.pgdir->order0);
		++o;
	पूर्ण
	i >>= o;
	set_bit(i, db->u.pgdir->bits[o]);

	अगर (biपंचांगap_full(db->u.pgdir->order1, MLX4_DB_PER_PAGE / 2)) अणु
		dma_मुक्त_coherent(&dev->persist->pdev->dev, PAGE_SIZE,
				  db->u.pgdir->db_page, db->u.pgdir->db_dma);
		list_del(&db->u.pgdir->list);
		kमुक्त(db->u.pgdir);
	पूर्ण

	mutex_unlock(&priv->pgdir_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_db_मुक्त);

पूर्णांक mlx4_alloc_hwq_res(काष्ठा mlx4_dev *dev, काष्ठा mlx4_hwq_resources *wqres,
		       पूर्णांक size)
अणु
	पूर्णांक err;

	err = mlx4_db_alloc(dev, &wqres->db, 1);
	अगर (err)
		वापस err;

	*wqres->db.db = 0;

	err = mlx4_buf_direct_alloc(dev, size, &wqres->buf);
	अगर (err)
		जाओ err_db;

	err = mlx4_mtt_init(dev, wqres->buf.npages, wqres->buf.page_shअगरt,
			    &wqres->mtt);
	अगर (err)
		जाओ err_buf;

	err = mlx4_buf_ग_लिखो_mtt(dev, &wqres->mtt, &wqres->buf);
	अगर (err)
		जाओ err_mtt;

	वापस 0;

err_mtt:
	mlx4_mtt_cleanup(dev, &wqres->mtt);
err_buf:
	mlx4_buf_मुक्त(dev, size, &wqres->buf);
err_db:
	mlx4_db_मुक्त(dev, &wqres->db);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_alloc_hwq_res);

व्योम mlx4_मुक्त_hwq_res(काष्ठा mlx4_dev *dev, काष्ठा mlx4_hwq_resources *wqres,
		       पूर्णांक size)
अणु
	mlx4_mtt_cleanup(dev, &wqres->mtt);
	mlx4_buf_मुक्त(dev, size, &wqres->buf);
	mlx4_db_मुक्त(dev, &wqres->db);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_मुक्त_hwq_res);
