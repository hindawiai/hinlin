<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mst.c - NTFS multi sector transfer protection handling code. Part of the
 *	   Linux-NTFS project.
 *
 * Copyright (c) 2001-2004 Anton Altaparmakov
 */

#समावेश "ntfs.h"

/**
 * post_पढ़ो_mst_fixup - deprotect multi sector transfer रक्षित data
 * @b:		poपूर्णांकer to the data to deprotect
 * @size:	size in bytes of @b
 *
 * Perक्रमm the necessary post पढ़ो multi sector transfer fixup and detect the
 * presence of incomplete multi sector transfers. - In that हाल, overग_लिखो the
 * magic of the ntfs record header being processed with "BAAD" (in memory only!)
 * and पात processing.
 *
 * Return 0 on success and -EINVAL on error ("BAAD" magic will be present).
 *
 * NOTE: We consider the असलence / invalidity of an update sequence array to
 * mean that the काष्ठाure is not रक्षित at all and hence करोesn't need to
 * be fixed up. Thus, we वापस success and not failure in this हाल. This is
 * in contrast to pre_ग_लिखो_mst_fixup(), see below.
 */
पूर्णांक post_पढ़ो_mst_fixup(NTFS_RECORD *b, स्थिर u32 size)
अणु
	u16 usa_ofs, usa_count, usn;
	u16 *usa_pos, *data_pos;

	/* Setup the variables. */
	usa_ofs = le16_to_cpu(b->usa_ofs);
	/* Decrement usa_count to get number of fixups. */
	usa_count = le16_to_cpu(b->usa_count) - 1;
	/* Size and alignment checks. */
	अगर ( size & (NTFS_BLOCK_SIZE - 1)	||
	     usa_ofs & 1			||
	     usa_ofs + (usa_count * 2) > size	||
	     (size >> NTFS_BLOCK_SIZE_BITS) != usa_count)
		वापस 0;
	/* Position of usn in update sequence array. */
	usa_pos = (u16*)b + usa_ofs/माप(u16);
	/*
	 * The update sequence number which has to be equal to each of the
	 * u16 values beक्रमe they are fixed up. Note no need to care क्रम
	 * endianness since we are comparing and moving data क्रम on disk
	 * काष्ठाures which means the data is consistent. - If it is
	 * consistenty the wrong endianness it करोesn't make any dअगरference.
	 */
	usn = *usa_pos;
	/*
	 * Position in रक्षित data of first u16 that needs fixing up.
	 */
	data_pos = (u16*)b + NTFS_BLOCK_SIZE/माप(u16) - 1;
	/*
	 * Check क्रम incomplete multi sector transfer(s).
	 */
	जबतक (usa_count--) अणु
		अगर (*data_pos != usn) अणु
			/*
			 * Incomplete multi sector transfer detected! )-:
			 * Set the magic to "BAAD" and वापस failure.
			 * Note that magic_BAAD is alपढ़ोy converted to le32.
			 */
			b->magic = magic_BAAD;
			वापस -EINVAL;
		पूर्ण
		data_pos += NTFS_BLOCK_SIZE/माप(u16);
	पूर्ण
	/* Re-setup the variables. */
	usa_count = le16_to_cpu(b->usa_count) - 1;
	data_pos = (u16*)b + NTFS_BLOCK_SIZE/माप(u16) - 1;
	/* Fixup all sectors. */
	जबतक (usa_count--) अणु
		/*
		 * Increment position in usa and restore original data from
		 * the usa पूर्णांकo the data buffer.
		 */
		*data_pos = *(++usa_pos);
		/* Increment position in data as well. */
		data_pos += NTFS_BLOCK_SIZE/माप(u16);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pre_ग_लिखो_mst_fixup - apply multi sector transfer protection
 * @b:		poपूर्णांकer to the data to protect
 * @size:	size in bytes of @b
 *
 * Perक्रमm the necessary pre ग_लिखो multi sector transfer fixup on the data
 * poपूर्णांकer to by @b of @size.
 *
 * Return 0 अगर fixup applied (success) or -EINVAL अगर no fixup was perक्रमmed
 * (assumed not needed). This is in contrast to post_पढ़ो_mst_fixup() above.
 *
 * NOTE: We consider the असलence / invalidity of an update sequence array to
 * mean that the काष्ठाure is not subject to protection and hence करोesn't need
 * to be fixed up. This means that you have to create a valid update sequence
 * array header in the ntfs record beक्रमe calling this function, otherwise it
 * will fail (the header needs to contain the position of the update sequence
 * array together with the number of elements in the array). You also need to
 * initialise the update sequence number beक्रमe calling this function
 * otherwise a अक्रमom word will be used (whatever was in the record at that
 * position at that समय).
 */
पूर्णांक pre_ग_लिखो_mst_fixup(NTFS_RECORD *b, स्थिर u32 size)
अणु
	le16 *usa_pos, *data_pos;
	u16 usa_ofs, usa_count, usn;
	le16 le_usn;

	/* Sanity check + only fixup अगर it makes sense. */
	अगर (!b || ntfs_is_baad_record(b->magic) ||
			ntfs_is_hole_record(b->magic))
		वापस -EINVAL;
	/* Setup the variables. */
	usa_ofs = le16_to_cpu(b->usa_ofs);
	/* Decrement usa_count to get number of fixups. */
	usa_count = le16_to_cpu(b->usa_count) - 1;
	/* Size and alignment checks. */
	अगर ( size & (NTFS_BLOCK_SIZE - 1)	||
	     usa_ofs & 1			||
	     usa_ofs + (usa_count * 2) > size	||
	     (size >> NTFS_BLOCK_SIZE_BITS) != usa_count)
		वापस -EINVAL;
	/* Position of usn in update sequence array. */
	usa_pos = (le16*)((u8*)b + usa_ofs);
	/*
	 * Cyclically increment the update sequence number
	 * (skipping 0 and -1, i.e. 0xffff).
	 */
	usn = le16_to_cpup(usa_pos) + 1;
	अगर (usn == 0xffff || !usn)
		usn = 1;
	le_usn = cpu_to_le16(usn);
	*usa_pos = le_usn;
	/* Position in data of first u16 that needs fixing up. */
	data_pos = (le16*)b + NTFS_BLOCK_SIZE/माप(le16) - 1;
	/* Fixup all sectors. */
	जबतक (usa_count--) अणु
		/*
		 * Increment the position in the usa and save the
		 * original data from the data buffer पूर्णांकo the usa.
		 */
		*(++usa_pos) = *data_pos;
		/* Apply fixup to data. */
		*data_pos = le_usn;
		/* Increment position in data as well. */
		data_pos += NTFS_BLOCK_SIZE/माप(le16);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * post_ग_लिखो_mst_fixup - fast deprotect multi sector transfer रक्षित data
 * @b:		poपूर्णांकer to the data to deprotect
 *
 * Perक्रमm the necessary post ग_लिखो multi sector transfer fixup, not checking
 * क्रम any errors, because we assume we have just used pre_ग_लिखो_mst_fixup(),
 * thus the data will be fine or we would never have gotten here.
 */
व्योम post_ग_लिखो_mst_fixup(NTFS_RECORD *b)
अणु
	le16 *usa_pos, *data_pos;

	u16 usa_ofs = le16_to_cpu(b->usa_ofs);
	u16 usa_count = le16_to_cpu(b->usa_count) - 1;

	/* Position of usn in update sequence array. */
	usa_pos = (le16*)b + usa_ofs/माप(le16);

	/* Position in रक्षित data of first u16 that needs fixing up. */
	data_pos = (le16*)b + NTFS_BLOCK_SIZE/माप(le16) - 1;

	/* Fixup all sectors. */
	जबतक (usa_count--) अणु
		/*
		 * Increment position in usa and restore original data from
		 * the usa पूर्णांकo the data buffer.
		 */
		*data_pos = *(++usa_pos);

		/* Increment position in data as well. */
		data_pos += NTFS_BLOCK_SIZE/माप(le16);
	पूर्ण
पूर्ण
