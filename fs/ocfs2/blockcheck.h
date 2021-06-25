<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * blockcheck.h
 *
 * Checksum and ECC codes क्रम the OCFS2 userspace library.
 *
 * Copyright (C) 2004, 2008 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_BLOCKCHECK_H
#घोषणा OCFS2_BLOCKCHECK_H


/* Count errors and error correction from blockcheck.c */
काष्ठा ocfs2_blockcheck_stats अणु
	spinlock_t b_lock;
	u64 b_check_count;	/* Number of blocks we've checked */
	u64 b_failure_count;	/* Number of failed checksums */
	u64 b_recover_count;	/* Number of blocks fixed by ecc */

	/*
	 * debugfs entries, used अगर this is passed to
	 * ocfs2_blockcheck_stats_debugfs_install()
	 */
	काष्ठा dentry *b_debug_dir;	/* Parent of the debugfs  files */
पूर्ण;


/* High level block API */
व्योम ocfs2_compute_meta_ecc(काष्ठा super_block *sb, व्योम *data,
			    काष्ठा ocfs2_block_check *bc);
पूर्णांक ocfs2_validate_meta_ecc(काष्ठा super_block *sb, व्योम *data,
			    काष्ठा ocfs2_block_check *bc);
व्योम ocfs2_compute_meta_ecc_bhs(काष्ठा super_block *sb,
				काष्ठा buffer_head **bhs, पूर्णांक nr,
				काष्ठा ocfs2_block_check *bc);
पूर्णांक ocfs2_validate_meta_ecc_bhs(काष्ठा super_block *sb,
				काष्ठा buffer_head **bhs, पूर्णांक nr,
				काष्ठा ocfs2_block_check *bc);

/* Lower level API */
व्योम ocfs2_block_check_compute(व्योम *data, माप_प्रकार blocksize,
			       काष्ठा ocfs2_block_check *bc);
पूर्णांक ocfs2_block_check_validate(व्योम *data, माप_प्रकार blocksize,
			       काष्ठा ocfs2_block_check *bc,
			       काष्ठा ocfs2_blockcheck_stats *stats);
व्योम ocfs2_block_check_compute_bhs(काष्ठा buffer_head **bhs, पूर्णांक nr,
				   काष्ठा ocfs2_block_check *bc);
पूर्णांक ocfs2_block_check_validate_bhs(काष्ठा buffer_head **bhs, पूर्णांक nr,
				   काष्ठा ocfs2_block_check *bc,
				   काष्ठा ocfs2_blockcheck_stats *stats);

/* Debug Initialization */
व्योम ocfs2_blockcheck_stats_debugfs_install(काष्ठा ocfs2_blockcheck_stats *stats,
					    काष्ठा dentry *parent);
व्योम ocfs2_blockcheck_stats_debugfs_हटाओ(काष्ठा ocfs2_blockcheck_stats *stats);

/*
 * Hamming code functions
 */

/*
 * Encoding hamming code parity bits क्रम a buffer.
 *
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
u32 ocfs2_hamming_encode(u32 parity, व्योम *data, अचिन्हित पूर्णांक d,
			 अचिन्हित पूर्णांक nr);
/*
 * Fix a buffer with a bit error.  The 'fix' is the original parity
 * xor'd with the parity calculated now.
 *
 * Like ocfs2_hamming_encode(), this can handle hunks.  nr is the bit
 * offset of the current hunk.  If bit to be fixed is not part of the
 * current hunk, this करोes nothing.
 *
 * If you only have one buffer, use ocfs2_hamming_fix_block().
 */
व्योम ocfs2_hamming_fix(व्योम *data, अचिन्हित पूर्णांक d, अचिन्हित पूर्णांक nr,
		       अचिन्हित पूर्णांक fix);

/* Convenience wrappers क्रम a single buffer of data */
बाह्य u32 ocfs2_hamming_encode_block(व्योम *data, अचिन्हित पूर्णांक blocksize);
बाह्य व्योम ocfs2_hamming_fix_block(व्योम *data, अचिन्हित पूर्णांक blocksize,
				    अचिन्हित पूर्णांक fix);
#पूर्ण_अगर
