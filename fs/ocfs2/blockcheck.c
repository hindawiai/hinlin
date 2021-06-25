<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * blockcheck.c
 *
 * Checksum and ECC codes क्रम the OCFS2 userspace library.
 *
 * Copyright (C) 2006, 2008 Oracle.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/crc32.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "blockcheck.h"


/*
 * We use the following conventions:
 *
 * d = # data bits
 * p = # parity bits
 * c = # total code bits (d + p)
 */


/*
 * Calculate the bit offset in the hamming code buffer based on the bit's
 * offset in the data buffer.  Since the hamming code reserves all
 * घातer-of-two bits क्रम parity, the data bit number and the code bit
 * number are offset by all the parity bits beक्रमehand.
 *
 * Recall that bit numbers in hamming code are 1-based.  This function
 * takes the 0-based data bit from the caller.
 *
 * An example.  Take bit 1 of the data buffer.  1 is a घातer of two (2^0),
 * so it's a parity bit.  2 is a power of two (2^1), so it's a parity bit.
 * 3 is not a घातer of two.  So bit 1 of the data buffer ends up as bit 3
 * in the code buffer.
 *
 * The caller can pass in *p अगर it wants to keep track of the most recent
 * number of parity bits added.  This allows the function to start the
 * calculation at the last place.
 */
अटल अचिन्हित पूर्णांक calc_code_bit(अचिन्हित पूर्णांक i, अचिन्हित पूर्णांक *p_cache)
अणु
	अचिन्हित पूर्णांक b, p = 0;

	/*
	 * Data bits are 0-based, but we're talking code bits, which
	 * are 1-based.
	 */
	b = i + 1;

	/* Use the cache अगर it is there */
	अगर (p_cache)
		p = *p_cache;
        b += p;

	/*
	 * For every घातer of two below our bit number, bump our bit.
	 *
	 * We compare with (b + 1) because we have to compare with what b
	 * would be _अगर_ it were bumped up by the parity bit.  Capice?
	 *
	 * p is set above.
	 */
	क्रम (; (1 << p) < (b + 1); p++)
		b++;

	अगर (p_cache)
		*p_cache = p;

	वापस b;
पूर्ण

/*
 * This is the low level encoder function.  It can be called across
 * multiple hunks just like the crc32 code.  'd' is the number of bits
 * _in_this_hunk_.  nr is the bit offset of this hunk.  So, अगर you had
 * two 512B buffers, you would करो it like so:
 *
 * parity = ocfs2_hamming_encode(0, buf1, 512 * 8, 0);
 * parity = ocfs2_hamming_encode(parity, buf2, 512 * 8, 512 * 8);
 *
 * If you just have one buffer, use ocfs2_hamming_encode_block().
 */
u32 ocfs2_hamming_encode(u32 parity, व्योम *data, अचिन्हित पूर्णांक d, अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक i, b, p = 0;

	BUG_ON(!d);

	/*
	 * b is the hamming code bit number.  Hamming code specअगरies a
	 * 1-based array, but C uses 0-based.  So 'i' is for C, and 'b' is
	 * क्रम the algorithm.
	 *
	 * The i++ in the क्रम loop is so that the start offset passed
	 * to ocfs2_find_next_bit_set() is one greater than the previously
	 * found bit.
	 */
	क्रम (i = 0; (i = ocfs2_find_next_bit(data, d, i)) < d; i++)
	अणु
		/*
		 * i is the offset in this hunk, nr + i is the total bit
		 * offset.
		 */
		b = calc_code_bit(nr + i, &p);

		/*
		 * Data bits in the resultant code are checked by
		 * parity bits that are part of the bit number
		 * representation.  Huh?
		 *
		 * <wikipedia href="https://en.wikipedia.org/wiki/Hamming_code">
		 * In other words, the parity bit at position 2^k
		 * checks bits in positions having bit k set in
		 * their binary representation.  Conversely, क्रम
		 * instance, bit 13, i.e. 1101(2), is checked by
		 * bits 1000(2) = 8, 0100(2)=4 and 0001(2) = 1.
		 * </wikipedia>
		 *
		 * Note that 'k' is the _code_ bit number.  'b' in
		 * our loop.
		 */
		parity ^= b;
	पूर्ण

	/* While the data buffer was treated as little endian, the
	 * वापस value is in host endian. */
	वापस parity;
पूर्ण

u32 ocfs2_hamming_encode_block(व्योम *data, अचिन्हित पूर्णांक blocksize)
अणु
	वापस ocfs2_hamming_encode(0, data, blocksize * 8, 0);
पूर्ण

/*
 * Like ocfs2_hamming_encode(), this can handle hunks.  nr is the bit
 * offset of the current hunk.  If bit to be fixed is not part of the
 * current hunk, this करोes nothing.
 *
 * If you only have one hunk, use ocfs2_hamming_fix_block().
 */
व्योम ocfs2_hamming_fix(व्योम *data, अचिन्हित पूर्णांक d, अचिन्हित पूर्णांक nr,
		       अचिन्हित पूर्णांक fix)
अणु
	अचिन्हित पूर्णांक i, b;

	BUG_ON(!d);

	/*
	 * If the bit to fix has an hweight of 1, it's a parity bit.  One
	 * busted parity bit is its own error.  Nothing to करो here.
	 */
	अगर (hweight32(fix) == 1)
		वापस;

	/*
	 * nr + d is the bit right past the data hunk we're looking at.
	 * If fix after that, nothing to करो
	 */
	अगर (fix >= calc_code_bit(nr + d, शून्य))
		वापस;

	/*
	 * nr is the offset in the data hunk we're starting at.  Let's
	 * start b at the offset in the code buffer.  See hamming_encode()
	 * क्रम a more detailed description of 'b'.
	 */
	b = calc_code_bit(nr, शून्य);
	/* If the fix is beक्रमe this hunk, nothing to करो */
	अगर (fix < b)
		वापस;

	क्रम (i = 0; i < d; i++, b++)
	अणु
		/* Skip past parity bits */
		जबतक (hweight32(b) == 1)
			b++;

		/*
		 * i is the offset in this data hunk.
		 * nr + i is the offset in the total data buffer.
		 * b is the offset in the total code buffer.
		 *
		 * Thus, when b == fix, bit i in the current hunk needs
		 * fixing.
		 */
		अगर (b == fix)
		अणु
			अगर (ocfs2_test_bit(i, data))
				ocfs2_clear_bit(i, data);
			अन्यथा
				ocfs2_set_bit(i, data);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ocfs2_hamming_fix_block(व्योम *data, अचिन्हित पूर्णांक blocksize,
			     अचिन्हित पूर्णांक fix)
अणु
	ocfs2_hamming_fix(data, blocksize * 8, 0, fix);
पूर्ण


/*
 * Debugfs handling.
 */

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक blockcheck_u64_get(व्योम *data, u64 *val)
अणु
	*val = *(u64 *)data;
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(blockcheck_fops, blockcheck_u64_get, शून्य, "%llu\n");

अटल व्योम ocfs2_blockcheck_debug_हटाओ(काष्ठा ocfs2_blockcheck_stats *stats)
अणु
	अगर (stats) अणु
		debugfs_हटाओ_recursive(stats->b_debug_dir);
		stats->b_debug_dir = शून्य;
	पूर्ण
पूर्ण

अटल व्योम ocfs2_blockcheck_debug_install(काष्ठा ocfs2_blockcheck_stats *stats,
					   काष्ठा dentry *parent)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir("blockcheck", parent);
	stats->b_debug_dir = dir;

	debugfs_create_file("blocks_checked", S_IFREG | S_IRUSR, dir,
			    &stats->b_check_count, &blockcheck_fops);

	debugfs_create_file("checksums_failed", S_IFREG | S_IRUSR, dir,
			    &stats->b_failure_count, &blockcheck_fops);

	debugfs_create_file("ecc_recoveries", S_IFREG | S_IRUSR, dir,
			    &stats->b_recover_count, &blockcheck_fops);

पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ocfs2_blockcheck_debug_install(काष्ठा ocfs2_blockcheck_stats *stats,
						  काष्ठा dentry *parent)
अणु
पूर्ण

अटल अंतरभूत व्योम ocfs2_blockcheck_debug_हटाओ(काष्ठा ocfs2_blockcheck_stats *stats)
अणु
पूर्ण
#पूर्ण_अगर  /* CONFIG_DEBUG_FS */

/* Always-called wrappers क्रम starting and stopping the debugfs files */
व्योम ocfs2_blockcheck_stats_debugfs_install(काष्ठा ocfs2_blockcheck_stats *stats,
					    काष्ठा dentry *parent)
अणु
	ocfs2_blockcheck_debug_install(stats, parent);
पूर्ण

व्योम ocfs2_blockcheck_stats_debugfs_हटाओ(काष्ठा ocfs2_blockcheck_stats *stats)
अणु
	ocfs2_blockcheck_debug_हटाओ(stats);
पूर्ण

अटल व्योम ocfs2_blockcheck_inc_check(काष्ठा ocfs2_blockcheck_stats *stats)
अणु
	u64 new_count;

	अगर (!stats)
		वापस;

	spin_lock(&stats->b_lock);
	stats->b_check_count++;
	new_count = stats->b_check_count;
	spin_unlock(&stats->b_lock);

	अगर (!new_count)
		mlog(ML_NOTICE, "Block check count has wrapped\n");
पूर्ण

अटल व्योम ocfs2_blockcheck_inc_failure(काष्ठा ocfs2_blockcheck_stats *stats)
अणु
	u64 new_count;

	अगर (!stats)
		वापस;

	spin_lock(&stats->b_lock);
	stats->b_failure_count++;
	new_count = stats->b_failure_count;
	spin_unlock(&stats->b_lock);

	अगर (!new_count)
		mlog(ML_NOTICE, "Checksum failure count has wrapped\n");
पूर्ण

अटल व्योम ocfs2_blockcheck_inc_recover(काष्ठा ocfs2_blockcheck_stats *stats)
अणु
	u64 new_count;

	अगर (!stats)
		वापस;

	spin_lock(&stats->b_lock);
	stats->b_recover_count++;
	new_count = stats->b_recover_count;
	spin_unlock(&stats->b_lock);

	अगर (!new_count)
		mlog(ML_NOTICE, "ECC recovery count has wrapped\n");
पूर्ण



/*
 * These are the low-level APIs क्रम using the ocfs2_block_check काष्ठाure.
 */

/*
 * This function generates check inक्रमmation क्रम a block.
 * data is the block to be checked.  bc is a poपूर्णांकer to the
 * ocfs2_block_check काष्ठाure describing the crc32 and the ecc.
 *
 * bc should be a poपूर्णांकer inside data, as the function will
 * take care of zeroing it beक्रमe calculating the check inक्रमmation.  If
 * bc करोes not poपूर्णांक inside data, the caller must make sure any अंतरभूत
 * ocfs2_block_check काष्ठाures are zeroed.
 *
 * The data buffer must be in on-disk endian (little endian क्रम ocfs2).
 * bc will be filled with little-endian values and will be पढ़ोy to go to
 * disk.
 */
व्योम ocfs2_block_check_compute(व्योम *data, माप_प्रकार blocksize,
			       काष्ठा ocfs2_block_check *bc)
अणु
	u32 crc;
	u32 ecc;

	स_रखो(bc, 0, माप(काष्ठा ocfs2_block_check));

	crc = crc32_le(~0, data, blocksize);
	ecc = ocfs2_hamming_encode_block(data, blocksize);

	/*
	 * No ecc'd ocfs2 काष्ठाure is larger than 4K, so ecc will be no
	 * larger than 16 bits.
	 */
	BUG_ON(ecc > अच_लघु_उच्च);

	bc->bc_crc32e = cpu_to_le32(crc);
	bc->bc_ecc = cpu_to_le16((u16)ecc);
पूर्ण

/*
 * This function validates existing check inक्रमmation.  Like _compute,
 * the function will take care of zeroing bc beक्रमe calculating check codes.
 * If bc is not a poपूर्णांकer inside data, the caller must have zeroed any
 * अंतरभूत ocfs2_block_check काष्ठाures.
 *
 * Again, the data passed in should be the on-disk endian.
 */
पूर्णांक ocfs2_block_check_validate(व्योम *data, माप_प्रकार blocksize,
			       काष्ठा ocfs2_block_check *bc,
			       काष्ठा ocfs2_blockcheck_stats *stats)
अणु
	पूर्णांक rc = 0;
	u32 bc_crc32e;
	u16 bc_ecc;
	u32 crc, ecc;

	ocfs2_blockcheck_inc_check(stats);

	bc_crc32e = le32_to_cpu(bc->bc_crc32e);
	bc_ecc = le16_to_cpu(bc->bc_ecc);

	स_रखो(bc, 0, माप(काष्ठा ocfs2_block_check));

	/* Fast path - अगर the crc32 validates, we're good to go */
	crc = crc32_le(~0, data, blocksize);
	अगर (crc == bc_crc32e)
		जाओ out;

	ocfs2_blockcheck_inc_failure(stats);
	mlog(ML_ERROR,
	     "CRC32 failed: stored: 0x%x, computed 0x%x. Applying ECC.\n",
	     (अचिन्हित पूर्णांक)bc_crc32e, (अचिन्हित पूर्णांक)crc);

	/* Ok, try ECC fixups */
	ecc = ocfs2_hamming_encode_block(data, blocksize);
	ocfs2_hamming_fix_block(data, blocksize, ecc ^ bc_ecc);

	/* And check the crc32 again */
	crc = crc32_le(~0, data, blocksize);
	अगर (crc == bc_crc32e) अणु
		ocfs2_blockcheck_inc_recover(stats);
		जाओ out;
	पूर्ण

	mlog(ML_ERROR, "Fixed CRC32 failed: stored: 0x%x, computed 0x%x\n",
	     (अचिन्हित पूर्णांक)bc_crc32e, (अचिन्हित पूर्णांक)crc);

	rc = -EIO;

out:
	bc->bc_crc32e = cpu_to_le32(bc_crc32e);
	bc->bc_ecc = cpu_to_le16(bc_ecc);

	वापस rc;
पूर्ण

/*
 * This function generates check inक्रमmation क्रम a list of buffer_heads.
 * bhs is the blocks to be checked.  bc is a poपूर्णांकer to the
 * ocfs2_block_check काष्ठाure describing the crc32 and the ecc.
 *
 * bc should be a poपूर्णांकer inside data, as the function will
 * take care of zeroing it beक्रमe calculating the check inक्रमmation.  If
 * bc करोes not poपूर्णांक inside data, the caller must make sure any अंतरभूत
 * ocfs2_block_check काष्ठाures are zeroed.
 *
 * The data buffer must be in on-disk endian (little endian क्रम ocfs2).
 * bc will be filled with little-endian values and will be पढ़ोy to go to
 * disk.
 */
व्योम ocfs2_block_check_compute_bhs(काष्ठा buffer_head **bhs, पूर्णांक nr,
				   काष्ठा ocfs2_block_check *bc)
अणु
	पूर्णांक i;
	u32 crc, ecc;

	BUG_ON(nr < 0);

	अगर (!nr)
		वापस;

	स_रखो(bc, 0, माप(काष्ठा ocfs2_block_check));

	क्रम (i = 0, crc = ~0, ecc = 0; i < nr; i++) अणु
		crc = crc32_le(crc, bhs[i]->b_data, bhs[i]->b_size);
		/*
		 * The number of bits in a buffer is obviously b_size*8.
		 * The offset of this buffer is b_size*i, so the bit offset
		 * of this buffer is b_size*8*i.
		 */
		ecc = (u16)ocfs2_hamming_encode(ecc, bhs[i]->b_data,
						bhs[i]->b_size * 8,
						bhs[i]->b_size * 8 * i);
	पूर्ण

	/*
	 * No ecc'd ocfs2 काष्ठाure is larger than 4K, so ecc will be no
	 * larger than 16 bits.
	 */
	BUG_ON(ecc > अच_लघु_उच्च);

	bc->bc_crc32e = cpu_to_le32(crc);
	bc->bc_ecc = cpu_to_le16((u16)ecc);
पूर्ण

/*
 * This function validates existing check inक्रमmation on a list of
 * buffer_heads.  Like _compute_bhs, the function will take care of
 * zeroing bc beक्रमe calculating check codes.  If bc is not a poपूर्णांकer
 * inside data, the caller must have zeroed any अंतरभूत
 * ocfs2_block_check काष्ठाures.
 *
 * Again, the data passed in should be the on-disk endian.
 */
पूर्णांक ocfs2_block_check_validate_bhs(काष्ठा buffer_head **bhs, पूर्णांक nr,
				   काष्ठा ocfs2_block_check *bc,
				   काष्ठा ocfs2_blockcheck_stats *stats)
अणु
	पूर्णांक i, rc = 0;
	u32 bc_crc32e;
	u16 bc_ecc;
	u32 crc, ecc, fix;

	BUG_ON(nr < 0);

	अगर (!nr)
		वापस 0;

	ocfs2_blockcheck_inc_check(stats);

	bc_crc32e = le32_to_cpu(bc->bc_crc32e);
	bc_ecc = le16_to_cpu(bc->bc_ecc);

	स_रखो(bc, 0, माप(काष्ठा ocfs2_block_check));

	/* Fast path - अगर the crc32 validates, we're good to go */
	क्रम (i = 0, crc = ~0; i < nr; i++)
		crc = crc32_le(crc, bhs[i]->b_data, bhs[i]->b_size);
	अगर (crc == bc_crc32e)
		जाओ out;

	ocfs2_blockcheck_inc_failure(stats);
	mlog(ML_ERROR,
	     "CRC32 failed: stored: %u, computed %u.  Applying ECC.\n",
	     (अचिन्हित पूर्णांक)bc_crc32e, (अचिन्हित पूर्णांक)crc);

	/* Ok, try ECC fixups */
	क्रम (i = 0, ecc = 0; i < nr; i++) अणु
		/*
		 * The number of bits in a buffer is obviously b_size*8.
		 * The offset of this buffer is b_size*i, so the bit offset
		 * of this buffer is b_size*8*i.
		 */
		ecc = (u16)ocfs2_hamming_encode(ecc, bhs[i]->b_data,
						bhs[i]->b_size * 8,
						bhs[i]->b_size * 8 * i);
	पूर्ण
	fix = ecc ^ bc_ecc;
	क्रम (i = 0; i < nr; i++) अणु
		/*
		 * Try the fix against each buffer.  It will only affect
		 * one of them.
		 */
		ocfs2_hamming_fix(bhs[i]->b_data, bhs[i]->b_size * 8,
				  bhs[i]->b_size * 8 * i, fix);
	पूर्ण

	/* And check the crc32 again */
	क्रम (i = 0, crc = ~0; i < nr; i++)
		crc = crc32_le(crc, bhs[i]->b_data, bhs[i]->b_size);
	अगर (crc == bc_crc32e) अणु
		ocfs2_blockcheck_inc_recover(stats);
		जाओ out;
	पूर्ण

	mlog(ML_ERROR, "Fixed CRC32 failed: stored: %u, computed %u\n",
	     (अचिन्हित पूर्णांक)bc_crc32e, (अचिन्हित पूर्णांक)crc);

	rc = -EIO;

out:
	bc->bc_crc32e = cpu_to_le32(bc_crc32e);
	bc->bc_ecc = cpu_to_le16(bc_ecc);

	वापस rc;
पूर्ण

/*
 * These are the मुख्य API.  They check the superblock flag beक्रमe
 * calling the underlying operations.
 *
 * They expect the buffer(s) to be in disk क्रमmat.
 */
व्योम ocfs2_compute_meta_ecc(काष्ठा super_block *sb, व्योम *data,
			    काष्ठा ocfs2_block_check *bc)
अणु
	अगर (ocfs2_meta_ecc(OCFS2_SB(sb)))
		ocfs2_block_check_compute(data, sb->s_blocksize, bc);
पूर्ण

पूर्णांक ocfs2_validate_meta_ecc(काष्ठा super_block *sb, व्योम *data,
			    काष्ठा ocfs2_block_check *bc)
अणु
	पूर्णांक rc = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);

	अगर (ocfs2_meta_ecc(osb))
		rc = ocfs2_block_check_validate(data, sb->s_blocksize, bc,
						&osb->osb_ecc_stats);

	वापस rc;
पूर्ण

व्योम ocfs2_compute_meta_ecc_bhs(काष्ठा super_block *sb,
				काष्ठा buffer_head **bhs, पूर्णांक nr,
				काष्ठा ocfs2_block_check *bc)
अणु
	अगर (ocfs2_meta_ecc(OCFS2_SB(sb)))
		ocfs2_block_check_compute_bhs(bhs, nr, bc);
पूर्ण

पूर्णांक ocfs2_validate_meta_ecc_bhs(काष्ठा super_block *sb,
				काष्ठा buffer_head **bhs, पूर्णांक nr,
				काष्ठा ocfs2_block_check *bc)
अणु
	पूर्णांक rc = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);

	अगर (ocfs2_meta_ecc(osb))
		rc = ocfs2_block_check_validate_bhs(bhs, nr, bc,
						    &osb->osb_ecc_stats);

	वापस rc;
पूर्ण

