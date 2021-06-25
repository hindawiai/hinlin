<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfsplus/biपंचांगap.c
 *
 * Copyright (C) 2001
 * Brad Boyer (flar@allandria.com)
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Handling of allocation file
 */

#समावेश <linux/pagemap.h>

#समावेश "hfsplus_fs.h"
#समावेश "hfsplus_raw.h"

#घोषणा PAGE_CACHE_BITS	(PAGE_SIZE * 8)

पूर्णांक hfsplus_block_allocate(काष्ठा super_block *sb, u32 size,
		u32 offset, u32 *max)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	काष्ठा page *page;
	काष्ठा address_space *mapping;
	__be32 *pptr, *curr, *end;
	u32 mask, start, len, n;
	__be32 val;
	पूर्णांक i;

	len = *max;
	अगर (!len)
		वापस size;

	hfs_dbg(BITMAP, "block_allocate: %u,%u,%u\n", size, offset, len);
	mutex_lock(&sbi->alloc_mutex);
	mapping = sbi->alloc_file->i_mapping;
	page = पढ़ो_mapping_page(mapping, offset / PAGE_CACHE_BITS, शून्य);
	अगर (IS_ERR(page)) अणु
		start = size;
		जाओ out;
	पूर्ण
	pptr = kmap(page);
	curr = pptr + (offset & (PAGE_CACHE_BITS - 1)) / 32;
	i = offset % 32;
	offset &= ~(PAGE_CACHE_BITS - 1);
	अगर ((size ^ offset) / PAGE_CACHE_BITS)
		end = pptr + PAGE_CACHE_BITS / 32;
	अन्यथा
		end = pptr + ((size + 31) & (PAGE_CACHE_BITS - 1)) / 32;

	/* scan the first partial u32 क्रम zero bits */
	val = *curr;
	अगर (~val) अणु
		n = be32_to_cpu(val);
		mask = (1U << 31) >> i;
		क्रम (; i < 32; mask >>= 1, i++) अणु
			अगर (!(n & mask))
				जाओ found;
		पूर्ण
	पूर्ण
	curr++;

	/* scan complete u32s क्रम the first zero bit */
	जबतक (1) अणु
		जबतक (curr < end) अणु
			val = *curr;
			अगर (~val) अणु
				n = be32_to_cpu(val);
				mask = 1 << 31;
				क्रम (i = 0; i < 32; mask >>= 1, i++) अणु
					अगर (!(n & mask))
						जाओ found;
				पूर्ण
			पूर्ण
			curr++;
		पूर्ण
		kunmap(page);
		offset += PAGE_CACHE_BITS;
		अगर (offset >= size)
			अवरोध;
		page = पढ़ो_mapping_page(mapping, offset / PAGE_CACHE_BITS,
					 शून्य);
		अगर (IS_ERR(page)) अणु
			start = size;
			जाओ out;
		पूर्ण
		curr = pptr = kmap(page);
		अगर ((size ^ offset) / PAGE_CACHE_BITS)
			end = pptr + PAGE_CACHE_BITS / 32;
		अन्यथा
			end = pptr + ((size + 31) & (PAGE_CACHE_BITS - 1)) / 32;
	पूर्ण
	hfs_dbg(BITMAP, "bitmap full\n");
	start = size;
	जाओ out;

found:
	start = offset + (curr - pptr) * 32 + i;
	अगर (start >= size) अणु
		hfs_dbg(BITMAP, "bitmap full\n");
		जाओ out;
	पूर्ण
	/* करो any partial u32 at the start */
	len = min(size - start, len);
	जबतक (1) अणु
		n |= mask;
		अगर (++i >= 32)
			अवरोध;
		mask >>= 1;
		अगर (!--len || n & mask)
			जाओ करोne;
	पूर्ण
	अगर (!--len)
		जाओ करोne;
	*curr++ = cpu_to_be32(n);
	/* करो full u32s */
	जबतक (1) अणु
		जबतक (curr < end) अणु
			n = be32_to_cpu(*curr);
			अगर (len < 32)
				जाओ last;
			अगर (n) अणु
				len = 32;
				जाओ last;
			पूर्ण
			*curr++ = cpu_to_be32(0xffffffff);
			len -= 32;
		पूर्ण
		set_page_dirty(page);
		kunmap(page);
		offset += PAGE_CACHE_BITS;
		page = पढ़ो_mapping_page(mapping, offset / PAGE_CACHE_BITS,
					 शून्य);
		अगर (IS_ERR(page)) अणु
			start = size;
			जाओ out;
		पूर्ण
		pptr = kmap(page);
		curr = pptr;
		end = pptr + PAGE_CACHE_BITS / 32;
	पूर्ण
last:
	/* करो any partial u32 at end */
	mask = 1U << 31;
	क्रम (i = 0; i < len; i++) अणु
		अगर (n & mask)
			अवरोध;
		n |= mask;
		mask >>= 1;
	पूर्ण
करोne:
	*curr = cpu_to_be32(n);
	set_page_dirty(page);
	kunmap(page);
	*max = offset + (curr - pptr) * 32 + i - start;
	sbi->मुक्त_blocks -= *max;
	hfsplus_mark_mdb_dirty(sb);
	hfs_dbg(BITMAP, "-> %u,%u\n", start, *max);
out:
	mutex_unlock(&sbi->alloc_mutex);
	वापस start;
पूर्ण

पूर्णांक hfsplus_block_मुक्त(काष्ठा super_block *sb, u32 offset, u32 count)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	काष्ठा page *page;
	काष्ठा address_space *mapping;
	__be32 *pptr, *curr, *end;
	u32 mask, len, pnr;
	पूर्णांक i;

	/* is there any actual work to be करोne? */
	अगर (!count)
		वापस 0;

	hfs_dbg(BITMAP, "block_free: %u,%u\n", offset, count);
	/* are all of the bits in range? */
	अगर ((offset + count) > sbi->total_blocks)
		वापस -ENOENT;

	mutex_lock(&sbi->alloc_mutex);
	mapping = sbi->alloc_file->i_mapping;
	pnr = offset / PAGE_CACHE_BITS;
	page = पढ़ो_mapping_page(mapping, pnr, शून्य);
	अगर (IS_ERR(page))
		जाओ kaboom;
	pptr = kmap(page);
	curr = pptr + (offset & (PAGE_CACHE_BITS - 1)) / 32;
	end = pptr + PAGE_CACHE_BITS / 32;
	len = count;

	/* करो any partial u32 at the start */
	i = offset % 32;
	अगर (i) अणु
		पूर्णांक j = 32 - i;
		mask = 0xffffffffU << j;
		अगर (j > count) अणु
			mask |= 0xffffffffU >> (i + count);
			*curr++ &= cpu_to_be32(mask);
			जाओ out;
		पूर्ण
		*curr++ &= cpu_to_be32(mask);
		count -= j;
	पूर्ण

	/* करो full u32s */
	जबतक (1) अणु
		जबतक (curr < end) अणु
			अगर (count < 32)
				जाओ करोne;
			*curr++ = 0;
			count -= 32;
		पूर्ण
		अगर (!count)
			अवरोध;
		set_page_dirty(page);
		kunmap(page);
		page = पढ़ो_mapping_page(mapping, ++pnr, शून्य);
		अगर (IS_ERR(page))
			जाओ kaboom;
		pptr = kmap(page);
		curr = pptr;
		end = pptr + PAGE_CACHE_BITS / 32;
	पूर्ण
करोne:
	/* करो any partial u32 at end */
	अगर (count) अणु
		mask = 0xffffffffU >> count;
		*curr &= cpu_to_be32(mask);
	पूर्ण
out:
	set_page_dirty(page);
	kunmap(page);
	sbi->मुक्त_blocks += len;
	hfsplus_mark_mdb_dirty(sb);
	mutex_unlock(&sbi->alloc_mutex);

	वापस 0;

kaboom:
	pr_crit("unable to mark blocks free: error %ld\n", PTR_ERR(page));
	mutex_unlock(&sbi->alloc_mutex);

	वापस -EIO;
पूर्ण
