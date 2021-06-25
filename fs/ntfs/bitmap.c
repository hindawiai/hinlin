<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * biपंचांगap.c - NTFS kernel biपंचांगap handling.  Part of the Linux-NTFS project.
 *
 * Copyright (c) 2004-2005 Anton Altaparmakov
 */

#अगर_घोषित NTFS_RW

#समावेश <linux/pagemap.h>

#समावेश "bitmap.h"
#समावेश "debug.h"
#समावेश "aops.h"
#समावेश "ntfs.h"

/**
 * __ntfs_biपंचांगap_set_bits_in_run - set a run of bits in a biपंचांगap to a value
 * @vi:			vfs inode describing the biपंचांगap
 * @start_bit:		first bit to set
 * @count:		number of bits to set
 * @value:		value to set the bits to (i.e. 0 or 1)
 * @is_rollback:	अगर 'true' this is a rollback operation
 *
 * Set @count bits starting at bit @start_bit in the biपंचांगap described by the
 * vfs inode @vi to @value, where @value is either 0 or 1.
 *
 * @is_rollback should always be 'false', it is क्रम पूर्णांकernal use to rollback
 * errors.  You probably want to use ntfs_biपंचांगap_set_bits_in_run() instead.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 */
पूर्णांक __ntfs_biपंचांगap_set_bits_in_run(काष्ठा inode *vi, स्थिर s64 start_bit,
		स्थिर s64 count, स्थिर u8 value, स्थिर bool is_rollback)
अणु
	s64 cnt = count;
	pgoff_t index, end_index;
	काष्ठा address_space *mapping;
	काष्ठा page *page;
	u8 *kaddr;
	पूर्णांक pos, len;
	u8 bit;

	BUG_ON(!vi);
	ntfs_debug("Entering for i_ino 0x%lx, start_bit 0x%llx, count 0x%llx, "
			"value %u.%s", vi->i_ino, (अचिन्हित दीर्घ दीर्घ)start_bit,
			(अचिन्हित दीर्घ दीर्घ)cnt, (अचिन्हित पूर्णांक)value,
			is_rollback ? " (rollback)" : "");
	BUG_ON(start_bit < 0);
	BUG_ON(cnt < 0);
	BUG_ON(value > 1);
	/*
	 * Calculate the indices क्रम the pages containing the first and last
	 * bits, i.e. @start_bit and @start_bit + @cnt - 1, respectively.
	 */
	index = start_bit >> (3 + PAGE_SHIFT);
	end_index = (start_bit + cnt - 1) >> (3 + PAGE_SHIFT);

	/* Get the page containing the first bit (@start_bit). */
	mapping = vi->i_mapping;
	page = ntfs_map_page(mapping, index);
	अगर (IS_ERR(page)) अणु
		अगर (!is_rollback)
			ntfs_error(vi->i_sb, "Failed to map first page (error "
					"%li), aborting.", PTR_ERR(page));
		वापस PTR_ERR(page);
	पूर्ण
	kaddr = page_address(page);

	/* Set @pos to the position of the byte containing @start_bit. */
	pos = (start_bit >> 3) & ~PAGE_MASK;

	/* Calculate the position of @start_bit in the first byte. */
	bit = start_bit & 7;

	/* If the first byte is partial, modअगरy the appropriate bits in it. */
	अगर (bit) अणु
		u8 *byte = kaddr + pos;
		जबतक ((bit & 7) && cnt) अणु
			cnt--;
			अगर (value)
				*byte |= 1 << bit++;
			अन्यथा
				*byte &= ~(1 << bit++);
		पूर्ण
		/* If we are करोne, unmap the page and वापस success. */
		अगर (!cnt)
			जाओ करोne;

		/* Update @pos to the new position. */
		pos++;
	पूर्ण
	/*
	 * Depending on @value, modअगरy all reमुख्यing whole bytes in the page up
	 * to @cnt.
	 */
	len = min_t(s64, cnt >> 3, PAGE_SIZE - pos);
	स_रखो(kaddr + pos, value ? 0xff : 0, len);
	cnt -= len << 3;

	/* Update @len to poपूर्णांक to the first not-करोne byte in the page. */
	अगर (cnt < 8)
		len += pos;

	/* If we are not in the last page, deal with all subsequent pages. */
	जबतक (index < end_index) अणु
		BUG_ON(cnt <= 0);

		/* Update @index and get the next page. */
		flush_dcache_page(page);
		set_page_dirty(page);
		ntfs_unmap_page(page);
		page = ntfs_map_page(mapping, ++index);
		अगर (IS_ERR(page))
			जाओ rollback;
		kaddr = page_address(page);
		/*
		 * Depending on @value, modअगरy all reमुख्यing whole bytes in the
		 * page up to @cnt.
		 */
		len = min_t(s64, cnt >> 3, PAGE_SIZE);
		स_रखो(kaddr, value ? 0xff : 0, len);
		cnt -= len << 3;
	पूर्ण
	/*
	 * The currently mapped page is the last one.  If the last byte is
	 * partial, modअगरy the appropriate bits in it.  Note, @len is the
	 * position of the last byte inside the page.
	 */
	अगर (cnt) अणु
		u8 *byte;

		BUG_ON(cnt > 7);

		bit = cnt;
		byte = kaddr + len;
		जबतक (bit--) अणु
			अगर (value)
				*byte |= 1 << bit;
			अन्यथा
				*byte &= ~(1 << bit);
		पूर्ण
	पूर्ण
करोne:
	/* We are करोne.  Unmap the page and वापस success. */
	flush_dcache_page(page);
	set_page_dirty(page);
	ntfs_unmap_page(page);
	ntfs_debug("Done.");
	वापस 0;
rollback:
	/*
	 * Current state:
	 *	- no pages are mapped
	 *	- @count - @cnt is the number of bits that have been modअगरied
	 */
	अगर (is_rollback)
		वापस PTR_ERR(page);
	अगर (count != cnt)
		pos = __ntfs_biपंचांगap_set_bits_in_run(vi, start_bit, count - cnt,
				value ? 0 : 1, true);
	अन्यथा
		pos = 0;
	अगर (!pos) अणु
		/* Rollback was successful. */
		ntfs_error(vi->i_sb, "Failed to map subsequent page (error "
				"%li), aborting.", PTR_ERR(page));
	पूर्ण अन्यथा अणु
		/* Rollback failed. */
		ntfs_error(vi->i_sb, "Failed to map subsequent page (error "
				"%li) and rollback failed (error %i).  "
				"Aborting and leaving inconsistent metadata.  "
				"Unmount and run chkdsk.", PTR_ERR(page), pos);
		NVolSetErrors(NTFS_SB(vi->i_sb));
	पूर्ण
	वापस PTR_ERR(page);
पूर्ण

#पूर्ण_अगर /* NTFS_RW */
