<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * io.c
 *
 * Buffer cache handling
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/bपन.स>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "uptodate.h"
#समावेश "buffer_head_io.h"
#समावेश "ocfs2_trace.h"

/*
 * Bits on bh->b_state used by ocfs2.
 *
 * These MUST be after the JBD2 bits.  Hence, we use BH_JBDPrivateStart.
 */
क्रमागत ocfs2_state_bits अणु
	BH_NeedsValidate = BH_JBDPrivateStart,
पूर्ण;

/* Expand the magic b_state functions */
BUFFER_FNS(NeedsValidate, needs_validate);

पूर्णांक ocfs2_ग_लिखो_block(काष्ठा ocfs2_super *osb, काष्ठा buffer_head *bh,
		      काष्ठा ocfs2_caching_info *ci)
अणु
	पूर्णांक ret = 0;

	trace_ocfs2_ग_लिखो_block((अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, ci);

	BUG_ON(bh->b_blocknr < OCFS2_SUPER_BLOCK_BLKNO);
	BUG_ON(buffer_jbd(bh));

	/* No need to check क्रम a soft पढ़ोonly file प्रणाली here. non
	 * journalled ग_लिखोs are only ever करोne on प्रणाली files which
	 * can get modअगरied during recovery even अगर पढ़ो-only. */
	अगर (ocfs2_is_hard_पढ़ोonly(osb)) अणु
		ret = -EROFS;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_metadata_cache_io_lock(ci);

	lock_buffer(bh);
	set_buffer_uptodate(bh);

	/* हटाओ from dirty list beक्रमe I/O. */
	clear_buffer_dirty(bh);

	get_bh(bh); /* क्रम end_buffer_ग_लिखो_sync() */
	bh->b_end_io = end_buffer_ग_लिखो_sync;
	submit_bh(REQ_OP_WRITE, 0, bh);

	रुको_on_buffer(bh);

	अगर (buffer_uptodate(bh)) अणु
		ocfs2_set_buffer_uptodate(ci, bh);
	पूर्ण अन्यथा अणु
		/* We करोn't need to हटाओ the clustered uptodate
		 * inक्रमmation क्रम this bh as it's not marked locally
		 * uptodate. */
		ret = -EIO;
		mlog_त्रुटि_सं(ret);
	पूर्ण

	ocfs2_metadata_cache_io_unlock(ci);
out:
	वापस ret;
पूर्ण

/* Caller must provide a bhs[] with all शून्य or non-शून्य entries, so it
 * will be easier to handle पढ़ो failure.
 */
पूर्णांक ocfs2_पढ़ो_blocks_sync(काष्ठा ocfs2_super *osb, u64 block,
			   अचिन्हित पूर्णांक nr, काष्ठा buffer_head *bhs[])
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा buffer_head *bh;
	पूर्णांक new_bh = 0;

	trace_ocfs2_पढ़ो_blocks_sync((अचिन्हित दीर्घ दीर्घ)block, nr);

	अगर (!nr)
		जाओ bail;

	/* Don't put buffer head and re-assign it to शून्य अगर it is allocated
	 * outside since the caller can't be aware of this alternation!
	 */
	new_bh = (bhs[0] == शून्य);

	क्रम (i = 0 ; i < nr ; i++) अणु
		अगर (bhs[i] == शून्य) अणु
			bhs[i] = sb_getblk(osb->sb, block++);
			अगर (bhs[i] == शून्य) अणु
				status = -ENOMEM;
				mlog_त्रुटि_सं(status);
				अवरोध;
			पूर्ण
		पूर्ण
		bh = bhs[i];

		अगर (buffer_jbd(bh)) अणु
			trace_ocfs2_पढ़ो_blocks_sync_jbd(
					(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
			जारी;
		पूर्ण

		अगर (buffer_dirty(bh)) अणु
			/* This should probably be a BUG, or
			 * at least वापस an error. */
			mlog(ML_ERROR,
			     "trying to sync read a dirty "
			     "buffer! (blocknr = %llu), skipping\n",
			     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
			जारी;
		पूर्ण

		lock_buffer(bh);
		अगर (buffer_jbd(bh)) अणु
#अगर_घोषित CATCH_BH_JBD_RACES
			mlog(ML_ERROR,
			     "block %llu had the JBD bit set "
			     "while I was in lock_buffer!",
			     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
			BUG();
#अन्यथा
			unlock_buffer(bh);
			जारी;
#पूर्ण_अगर
		पूर्ण

		get_bh(bh); /* क्रम end_buffer_पढ़ो_sync() */
		bh->b_end_io = end_buffer_पढ़ो_sync;
		submit_bh(REQ_OP_READ, 0, bh);
	पूर्ण

पढ़ो_failure:
	क्रम (i = nr; i > 0; i--) अणु
		bh = bhs[i - 1];

		अगर (unlikely(status)) अणु
			अगर (new_bh && bh) अणु
				/* If middle bh fails, let previous bh
				 * finish its पढ़ो and then put it to
				 * aoव्योम bh leak
				 */
				अगर (!buffer_jbd(bh))
					रुको_on_buffer(bh);
				put_bh(bh);
				bhs[i - 1] = शून्य;
			पूर्ण अन्यथा अगर (bh && buffer_uptodate(bh)) अणु
				clear_buffer_uptodate(bh);
			पूर्ण
			जारी;
		पूर्ण

		/* No need to रुको on the buffer अगर it's managed by JBD. */
		अगर (!buffer_jbd(bh))
			रुको_on_buffer(bh);

		अगर (!buffer_uptodate(bh)) अणु
			/* Status won't be cleared from here on out,
			 * so we can safely record this and loop back
			 * to cleanup the other buffers. */
			status = -EIO;
			जाओ पढ़ो_failure;
		पूर्ण
	पूर्ण

bail:
	वापस status;
पूर्ण

/* Caller must provide a bhs[] with all शून्य or non-शून्य entries, so it
 * will be easier to handle पढ़ो failure.
 */
पूर्णांक ocfs2_पढ़ो_blocks(काष्ठा ocfs2_caching_info *ci, u64 block, पूर्णांक nr,
		      काष्ठा buffer_head *bhs[], पूर्णांक flags,
		      पूर्णांक (*validate)(काष्ठा super_block *sb,
				      काष्ठा buffer_head *bh))
अणु
	पूर्णांक status = 0;
	पूर्णांक i, ignore_cache = 0;
	काष्ठा buffer_head *bh;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(ci);
	पूर्णांक new_bh = 0;

	trace_ocfs2_पढ़ो_blocks_begin(ci, (अचिन्हित दीर्घ दीर्घ)block, nr, flags);

	BUG_ON(!ci);
	BUG_ON((flags & OCFS2_BH_READAHEAD) &&
	       (flags & OCFS2_BH_IGNORE_CACHE));

	अगर (bhs == शून्य) अणु
		status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	अगर (nr < 0) अणु
		mlog(ML_ERROR, "asked to read %d blocks!\n", nr);
		status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	अगर (nr == 0) अणु
		status = 0;
		जाओ bail;
	पूर्ण

	/* Don't put buffer head and re-assign it to शून्य अगर it is allocated
	 * outside since the caller can't be aware of this alternation!
	 */
	new_bh = (bhs[0] == शून्य);

	ocfs2_metadata_cache_io_lock(ci);
	क्रम (i = 0 ; i < nr ; i++) अणु
		अगर (bhs[i] == शून्य) अणु
			bhs[i] = sb_getblk(sb, block++);
			अगर (bhs[i] == शून्य) अणु
				ocfs2_metadata_cache_io_unlock(ci);
				status = -ENOMEM;
				mlog_त्रुटि_सं(status);
				/* Don't क्रमget to put previous bh! */
				अवरोध;
			पूर्ण
		पूर्ण
		bh = bhs[i];
		ignore_cache = (flags & OCFS2_BH_IGNORE_CACHE);

		/* There are three पढ़ो-ahead हालs here which we need to
		 * be concerned with. All three assume a buffer has
		 * previously been submitted with OCFS2_BH_READAHEAD
		 * and it hasn't yet completed I/O.
		 *
		 * 1) The current request is sync to disk. This rarely
		 *    happens these days, and never when perक्रमmance
		 *    matters - the code can just रुको on the buffer
		 *    lock and re-submit.
		 *
		 * 2) The current request is cached, but not
		 *    पढ़ोahead. ocfs2_buffer_uptodate() will वापस
		 *    false anyway, so we'll wind up रुकोing on the
		 *    buffer lock to करो I/O. We re-check the request
		 *    with after getting the lock to aव्योम a re-submit.
		 *
		 * 3) The current request is पढ़ोahead (and so must
		 *    also be a caching one). We लघु circuit अगर the
		 *    buffer is locked (under I/O) and अगर it's in the
		 *    uptodate cache. The re-check from #2 catches the
		 *    हाल that the previous पढ़ो-ahead completes just
		 *    beक्रमe our is-it-in-flight check.
		 */

		अगर (!ignore_cache && !ocfs2_buffer_uptodate(ci, bh)) अणु
			trace_ocfs2_पढ़ो_blocks_from_disk(
			     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			     (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci));
			/* We're using ignore_cache here to say
			 * "go to disk" */
			ignore_cache = 1;
		पूर्ण

		trace_ocfs2_पढ़ो_blocks_bh((अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
			ignore_cache, buffer_jbd(bh), buffer_dirty(bh));

		अगर (buffer_jbd(bh)) अणु
			जारी;
		पूर्ण

		अगर (ignore_cache) अणु
			अगर (buffer_dirty(bh)) अणु
				/* This should probably be a BUG, or
				 * at least वापस an error. */
				जारी;
			पूर्ण

			/* A पढ़ो-ahead request was made - अगर the
			 * buffer is alपढ़ोy under पढ़ो-ahead from a
			 * previously submitted request than we are
			 * करोne here. */
			अगर ((flags & OCFS2_BH_READAHEAD)
			    && ocfs2_buffer_पढ़ो_ahead(ci, bh))
				जारी;

			lock_buffer(bh);
			अगर (buffer_jbd(bh)) अणु
#अगर_घोषित CATCH_BH_JBD_RACES
				mlog(ML_ERROR, "block %llu had the JBD bit set "
					       "while I was in lock_buffer!",
				     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
				BUG();
#अन्यथा
				unlock_buffer(bh);
				जारी;
#पूर्ण_अगर
			पूर्ण

			/* Re-check ocfs2_buffer_uptodate() as a
			 * previously पढ़ो-ahead buffer may have
			 * completed I/O जबतक we were रुकोing क्रम the
			 * buffer lock. */
			अगर (!(flags & OCFS2_BH_IGNORE_CACHE)
			    && !(flags & OCFS2_BH_READAHEAD)
			    && ocfs2_buffer_uptodate(ci, bh)) अणु
				unlock_buffer(bh);
				जारी;
			पूर्ण

			get_bh(bh); /* क्रम end_buffer_पढ़ो_sync() */
			अगर (validate)
				set_buffer_needs_validate(bh);
			bh->b_end_io = end_buffer_पढ़ो_sync;
			submit_bh(REQ_OP_READ, 0, bh);
			जारी;
		पूर्ण
	पूर्ण

पढ़ो_failure:
	क्रम (i = (nr - 1); i >= 0; i--) अणु
		bh = bhs[i];

		अगर (!(flags & OCFS2_BH_READAHEAD)) अणु
			अगर (unlikely(status)) अणु
				/* Clear the buffers on error including those
				 * ever succeeded in पढ़ोing
				 */
				अगर (new_bh && bh) अणु
					/* If middle bh fails, let previous bh
					 * finish its पढ़ो and then put it to
					 * aoव्योम bh leak
					 */
					अगर (!buffer_jbd(bh))
						रुको_on_buffer(bh);
					put_bh(bh);
					bhs[i] = शून्य;
				पूर्ण अन्यथा अगर (bh && buffer_uptodate(bh)) अणु
					clear_buffer_uptodate(bh);
				पूर्ण
				जारी;
			पूर्ण
			/* We know this can't have changed as we hold the
			 * owner sem. Aव्योम करोing any work on the bh अगर the
			 * journal has it. */
			अगर (!buffer_jbd(bh))
				रुको_on_buffer(bh);

			अगर (!buffer_uptodate(bh)) अणु
				/* Status won't be cleared from here on out,
				 * so we can safely record this and loop back
				 * to cleanup the other buffers. Don't need to
				 * हटाओ the clustered uptodate inक्रमmation
				 * क्रम this bh as it's not marked locally
				 * uptodate. */
				status = -EIO;
				clear_buffer_needs_validate(bh);
				जाओ पढ़ो_failure;
			पूर्ण

			अगर (buffer_needs_validate(bh)) अणु
				/* We never set NeedsValidate अगर the
				 * buffer was held by the journal, so
				 * that better not have changed */
				BUG_ON(buffer_jbd(bh));
				clear_buffer_needs_validate(bh);
				status = validate(sb, bh);
				अगर (status)
					जाओ पढ़ो_failure;
			पूर्ण
		पूर्ण

		/* Always set the buffer in the cache, even अगर it was
		 * a क्रमced पढ़ो, or पढ़ो-ahead which hasn't yet
		 * completed. */
		ocfs2_set_buffer_uptodate(ci, bh);
	पूर्ण
	ocfs2_metadata_cache_io_unlock(ci);

	trace_ocfs2_पढ़ो_blocks_end((अचिन्हित दीर्घ दीर्घ)block, nr,
				    flags, ignore_cache);

bail:

	वापस status;
पूर्ण

/* Check whether the blkno is the super block or one of the backups. */
अटल व्योम ocfs2_check_super_or_backup(काष्ठा super_block *sb,
					sector_t blkno)
अणु
	पूर्णांक i;
	u64 backup_blkno;

	अगर (blkno == OCFS2_SUPER_BLOCK_BLKNO)
		वापस;

	क्रम (i = 0; i < OCFS2_MAX_BACKUP_SUPERBLOCKS; i++) अणु
		backup_blkno = ocfs2_backup_super_blkno(sb, i);
		अगर (backup_blkno == blkno)
			वापस;
	पूर्ण

	BUG();
पूर्ण

/*
 * Write super block and backups करोesn't need to collaborate with journal,
 * so we करोn't need to lock ip_io_mutex and ci doesn't need to bea passed
 * पूर्णांकo this function.
 */
पूर्णांक ocfs2_ग_लिखो_super_or_backup(काष्ठा ocfs2_super *osb,
				काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)bh->b_data;

	BUG_ON(buffer_jbd(bh));
	ocfs2_check_super_or_backup(osb->sb, bh->b_blocknr);

	अगर (ocfs2_is_hard_पढ़ोonly(osb) || ocfs2_is_soft_पढ़ोonly(osb)) अणु
		ret = -EROFS;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	lock_buffer(bh);
	set_buffer_uptodate(bh);

	/* हटाओ from dirty list beक्रमe I/O. */
	clear_buffer_dirty(bh);

	get_bh(bh); /* क्रम end_buffer_ग_लिखो_sync() */
	bh->b_end_io = end_buffer_ग_लिखो_sync;
	ocfs2_compute_meta_ecc(osb->sb, bh->b_data, &di->i_check);
	submit_bh(REQ_OP_WRITE, 0, bh);

	रुको_on_buffer(bh);

	अगर (!buffer_uptodate(bh)) अणु
		ret = -EIO;
		mlog_त्रुटि_सं(ret);
	पूर्ण

out:
	वापस ret;
पूर्ण
