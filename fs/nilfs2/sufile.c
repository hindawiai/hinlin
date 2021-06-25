<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * sufile.c - NILFS segment usage file.
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 * Revised by Ryusuke Konishi.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश "mdt.h"
#समावेश "sufile.h"

#समावेश <trace/events/nilfs2.h>

/**
 * काष्ठा nilfs_sufile_info - on-memory निजी data of sufile
 * @mi: on-memory निजी data of metadata file
 * @ncleansegs: number of clean segments
 * @allocmin: lower limit of allocatable segment range
 * @allocmax: upper limit of allocatable segment range
 */
काष्ठा nilfs_sufile_info अणु
	काष्ठा nilfs_mdt_info mi;
	अचिन्हित दीर्घ ncleansegs;/* number of clean segments */
	__u64 allocmin;		/* lower limit of allocatable segment range */
	__u64 allocmax;		/* upper limit of allocatable segment range */
पूर्ण;

अटल अंतरभूत काष्ठा nilfs_sufile_info *NILFS_SUI(काष्ठा inode *sufile)
अणु
	वापस (काष्ठा nilfs_sufile_info *)NILFS_MDT(sufile);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
nilfs_sufile_segment_usages_per_block(स्थिर काष्ठा inode *sufile)
अणु
	वापस NILFS_MDT(sufile)->mi_entries_per_block;
पूर्ण

अटल अचिन्हित दीर्घ
nilfs_sufile_get_blkoff(स्थिर काष्ठा inode *sufile, __u64 segnum)
अणु
	__u64 t = segnum + NILFS_MDT(sufile)->mi_first_entry_offset;

	करो_भाग(t, nilfs_sufile_segment_usages_per_block(sufile));
	वापस (अचिन्हित दीर्घ)t;
पूर्ण

अटल अचिन्हित दीर्घ
nilfs_sufile_get_offset(स्थिर काष्ठा inode *sufile, __u64 segnum)
अणु
	__u64 t = segnum + NILFS_MDT(sufile)->mi_first_entry_offset;

	वापस करो_भाग(t, nilfs_sufile_segment_usages_per_block(sufile));
पूर्ण

अटल अचिन्हित दीर्घ
nilfs_sufile_segment_usages_in_block(स्थिर काष्ठा inode *sufile, __u64 curr,
				     __u64 max)
अणु
	वापस min_t(अचिन्हित दीर्घ,
		     nilfs_sufile_segment_usages_per_block(sufile) -
		     nilfs_sufile_get_offset(sufile, curr),
		     max - curr + 1);
पूर्ण

अटल काष्ठा nilfs_segment_usage *
nilfs_sufile_block_get_segment_usage(स्थिर काष्ठा inode *sufile, __u64 segnum,
				     काष्ठा buffer_head *bh, व्योम *kaddr)
अणु
	वापस kaddr + bh_offset(bh) +
		nilfs_sufile_get_offset(sufile, segnum) *
		NILFS_MDT(sufile)->mi_entry_size;
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_sufile_get_header_block(काष्ठा inode *sufile,
						काष्ठा buffer_head **bhp)
अणु
	वापस nilfs_mdt_get_block(sufile, 0, 0, शून्य, bhp);
पूर्ण

अटल अंतरभूत पूर्णांक
nilfs_sufile_get_segment_usage_block(काष्ठा inode *sufile, __u64 segnum,
				     पूर्णांक create, काष्ठा buffer_head **bhp)
अणु
	वापस nilfs_mdt_get_block(sufile,
				   nilfs_sufile_get_blkoff(sufile, segnum),
				   create, शून्य, bhp);
पूर्ण

अटल पूर्णांक nilfs_sufile_delete_segment_usage_block(काष्ठा inode *sufile,
						   __u64 segnum)
अणु
	वापस nilfs_mdt_delete_block(sufile,
				      nilfs_sufile_get_blkoff(sufile, segnum));
पूर्ण

अटल व्योम nilfs_sufile_mod_counter(काष्ठा buffer_head *header_bh,
				     u64 ncleanadd, u64 ndirtyadd)
अणु
	काष्ठा nilfs_sufile_header *header;
	व्योम *kaddr;

	kaddr = kmap_atomic(header_bh->b_page);
	header = kaddr + bh_offset(header_bh);
	le64_add_cpu(&header->sh_ncleansegs, ncleanadd);
	le64_add_cpu(&header->sh_ndirtysegs, ndirtyadd);
	kunmap_atomic(kaddr);

	mark_buffer_dirty(header_bh);
पूर्ण

/**
 * nilfs_sufile_get_ncleansegs - वापस the number of clean segments
 * @sufile: inode of segment usage file
 */
अचिन्हित दीर्घ nilfs_sufile_get_ncleansegs(काष्ठा inode *sufile)
अणु
	वापस NILFS_SUI(sufile)->ncleansegs;
पूर्ण

/**
 * nilfs_sufile_updatev - modअगरy multiple segment usages at a समय
 * @sufile: inode of segment usage file
 * @segnumv: array of segment numbers
 * @nsegs: size of @segnumv array
 * @create: creation flag
 * @nकरोne: place to store number of modअगरied segments on @segnumv
 * @करोfunc: primitive operation क्रम the update
 *
 * Description: nilfs_sufile_updatev() repeatedly calls @करोfunc
 * against the given array of segments.  The @करोfunc is called with
 * buffers of a header block and the sufile block in which the target
 * segment usage entry is contained.  If @nकरोne is given, the number
 * of successfully modअगरied segments from the head is stored in the
 * place @nकरोne poपूर्णांकs to.
 *
 * Return Value: On success, zero is वापसed.  On error, one of the
 * following negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - Given segment usage is in hole block (may be वापसed अगर
 *            @create is zero)
 *
 * %-EINVAL - Invalid segment usage number
 */
पूर्णांक nilfs_sufile_updatev(काष्ठा inode *sufile, __u64 *segnumv, माप_प्रकार nsegs,
			 पूर्णांक create, माप_प्रकार *nकरोne,
			 व्योम (*करोfunc)(काष्ठा inode *, __u64,
					काष्ठा buffer_head *,
					काष्ठा buffer_head *))
अणु
	काष्ठा buffer_head *header_bh, *bh;
	अचिन्हित दीर्घ blkoff, prev_blkoff;
	__u64 *seg;
	माप_प्रकार nerr = 0, n = 0;
	पूर्णांक ret = 0;

	अगर (unlikely(nsegs == 0))
		जाओ out;

	करोwn_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);
	क्रम (seg = segnumv; seg < segnumv + nsegs; seg++) अणु
		अगर (unlikely(*seg >= nilfs_sufile_get_nsegments(sufile))) अणु
			nilfs_warn(sufile->i_sb,
				   "%s: invalid segment number: %llu",
				   __func__, (अचिन्हित दीर्घ दीर्घ)*seg);
			nerr++;
		पूर्ण
	पूर्ण
	अगर (nerr > 0) अणु
		ret = -EINVAL;
		जाओ out_sem;
	पूर्ण

	ret = nilfs_sufile_get_header_block(sufile, &header_bh);
	अगर (ret < 0)
		जाओ out_sem;

	seg = segnumv;
	blkoff = nilfs_sufile_get_blkoff(sufile, *seg);
	ret = nilfs_mdt_get_block(sufile, blkoff, create, शून्य, &bh);
	अगर (ret < 0)
		जाओ out_header;

	क्रम (;;) अणु
		करोfunc(sufile, *seg, header_bh, bh);

		अगर (++seg >= segnumv + nsegs)
			अवरोध;
		prev_blkoff = blkoff;
		blkoff = nilfs_sufile_get_blkoff(sufile, *seg);
		अगर (blkoff == prev_blkoff)
			जारी;

		/* get dअगरferent block */
		brअन्यथा(bh);
		ret = nilfs_mdt_get_block(sufile, blkoff, create, शून्य, &bh);
		अगर (unlikely(ret < 0))
			जाओ out_header;
	पूर्ण
	brअन्यथा(bh);

 out_header:
	n = seg - segnumv;
	brअन्यथा(header_bh);
 out_sem:
	up_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);
 out:
	अगर (nकरोne)
		*nकरोne = n;
	वापस ret;
पूर्ण

पूर्णांक nilfs_sufile_update(काष्ठा inode *sufile, __u64 segnum, पूर्णांक create,
			व्योम (*करोfunc)(काष्ठा inode *, __u64,
				       काष्ठा buffer_head *,
				       काष्ठा buffer_head *))
अणु
	काष्ठा buffer_head *header_bh, *bh;
	पूर्णांक ret;

	अगर (unlikely(segnum >= nilfs_sufile_get_nsegments(sufile))) अणु
		nilfs_warn(sufile->i_sb, "%s: invalid segment number: %llu",
			   __func__, (अचिन्हित दीर्घ दीर्घ)segnum);
		वापस -EINVAL;
	पूर्ण
	करोwn_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);

	ret = nilfs_sufile_get_header_block(sufile, &header_bh);
	अगर (ret < 0)
		जाओ out_sem;

	ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, create, &bh);
	अगर (!ret) अणु
		करोfunc(sufile, segnum, header_bh, bh);
		brअन्यथा(bh);
	पूर्ण
	brअन्यथा(header_bh);

 out_sem:
	up_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_sufile_set_alloc_range - limit range of segment to be allocated
 * @sufile: inode of segment usage file
 * @start: minimum segment number of allocatable region (inclusive)
 * @end: maximum segment number of allocatable region (inclusive)
 *
 * Return Value: On success, 0 is वापसed.  On error, one of the
 * following negative error codes is वापसed.
 *
 * %-दुस्फल - invalid segment region
 */
पूर्णांक nilfs_sufile_set_alloc_range(काष्ठा inode *sufile, __u64 start, __u64 end)
अणु
	काष्ठा nilfs_sufile_info *sui = NILFS_SUI(sufile);
	__u64 nsegs;
	पूर्णांक ret = -दुस्फल;

	करोwn_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);
	nsegs = nilfs_sufile_get_nsegments(sufile);

	अगर (start <= end && end < nsegs) अणु
		sui->allocmin = start;
		sui->allocmax = end;
		ret = 0;
	पूर्ण
	up_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_sufile_alloc - allocate a segment
 * @sufile: inode of segment usage file
 * @segnump: poपूर्णांकer to segment number
 *
 * Description: nilfs_sufile_alloc() allocates a clean segment.
 *
 * Return Value: On success, 0 is वापसed and the segment number of the
 * allocated segment is stored in the place poपूर्णांकed by @segnump. On error, one
 * of the following negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOSPC - No clean segment left.
 */
पूर्णांक nilfs_sufile_alloc(काष्ठा inode *sufile, __u64 *segnump)
अणु
	काष्ठा buffer_head *header_bh, *su_bh;
	काष्ठा nilfs_sufile_header *header;
	काष्ठा nilfs_segment_usage *su;
	काष्ठा nilfs_sufile_info *sui = NILFS_SUI(sufile);
	माप_प्रकार susz = NILFS_MDT(sufile)->mi_entry_size;
	__u64 segnum, maxsegnum, last_alloc;
	व्योम *kaddr;
	अचिन्हित दीर्घ nsegments, nsus, cnt;
	पूर्णांक ret, j;

	करोwn_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);

	ret = nilfs_sufile_get_header_block(sufile, &header_bh);
	अगर (ret < 0)
		जाओ out_sem;
	kaddr = kmap_atomic(header_bh->b_page);
	header = kaddr + bh_offset(header_bh);
	last_alloc = le64_to_cpu(header->sh_last_alloc);
	kunmap_atomic(kaddr);

	nsegments = nilfs_sufile_get_nsegments(sufile);
	maxsegnum = sui->allocmax;
	segnum = last_alloc + 1;
	अगर (segnum < sui->allocmin || segnum > sui->allocmax)
		segnum = sui->allocmin;

	क्रम (cnt = 0; cnt < nsegments; cnt += nsus) अणु
		अगर (segnum > maxsegnum) अणु
			अगर (cnt < sui->allocmax - sui->allocmin + 1) अणु
				/*
				 * wrap around in the limited region.
				 * अगर allocation started from
				 * sui->allocmin, this never happens.
				 */
				segnum = sui->allocmin;
				maxsegnum = last_alloc;
			पूर्ण अन्यथा अगर (segnum > sui->allocmin &&
				   sui->allocmax + 1 < nsegments) अणु
				segnum = sui->allocmax + 1;
				maxsegnum = nsegments - 1;
			पूर्ण अन्यथा अगर (sui->allocmin > 0)  अणु
				segnum = 0;
				maxsegnum = sui->allocmin - 1;
			पूर्ण अन्यथा अणु
				अवरोध; /* never happens */
			पूर्ण
		पूर्ण
		trace_nilfs2_segment_usage_check(sufile, segnum, cnt);
		ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 1,
							   &su_bh);
		अगर (ret < 0)
			जाओ out_header;
		kaddr = kmap_atomic(su_bh->b_page);
		su = nilfs_sufile_block_get_segment_usage(
			sufile, segnum, su_bh, kaddr);

		nsus = nilfs_sufile_segment_usages_in_block(
			sufile, segnum, maxsegnum);
		क्रम (j = 0; j < nsus; j++, su = (व्योम *)su + susz, segnum++) अणु
			अगर (!nilfs_segment_usage_clean(su))
				जारी;
			/* found a clean segment */
			nilfs_segment_usage_set_dirty(su);
			kunmap_atomic(kaddr);

			kaddr = kmap_atomic(header_bh->b_page);
			header = kaddr + bh_offset(header_bh);
			le64_add_cpu(&header->sh_ncleansegs, -1);
			le64_add_cpu(&header->sh_ndirtysegs, 1);
			header->sh_last_alloc = cpu_to_le64(segnum);
			kunmap_atomic(kaddr);

			sui->ncleansegs--;
			mark_buffer_dirty(header_bh);
			mark_buffer_dirty(su_bh);
			nilfs_mdt_mark_dirty(sufile);
			brअन्यथा(su_bh);
			*segnump = segnum;

			trace_nilfs2_segment_usage_allocated(sufile, segnum);

			जाओ out_header;
		पूर्ण

		kunmap_atomic(kaddr);
		brअन्यथा(su_bh);
	पूर्ण

	/* no segments left */
	ret = -ENOSPC;

 out_header:
	brअन्यथा(header_bh);

 out_sem:
	up_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);
	वापस ret;
पूर्ण

व्योम nilfs_sufile_करो_cancel_मुक्त(काष्ठा inode *sufile, __u64 segnum,
				 काष्ठा buffer_head *header_bh,
				 काष्ठा buffer_head *su_bh)
अणु
	काष्ठा nilfs_segment_usage *su;
	व्योम *kaddr;

	kaddr = kmap_atomic(su_bh->b_page);
	su = nilfs_sufile_block_get_segment_usage(sufile, segnum, su_bh, kaddr);
	अगर (unlikely(!nilfs_segment_usage_clean(su))) अणु
		nilfs_warn(sufile->i_sb, "%s: segment %llu must be clean",
			   __func__, (अचिन्हित दीर्घ दीर्घ)segnum);
		kunmap_atomic(kaddr);
		वापस;
	पूर्ण
	nilfs_segment_usage_set_dirty(su);
	kunmap_atomic(kaddr);

	nilfs_sufile_mod_counter(header_bh, -1, 1);
	NILFS_SUI(sufile)->ncleansegs--;

	mark_buffer_dirty(su_bh);
	nilfs_mdt_mark_dirty(sufile);
पूर्ण

व्योम nilfs_sufile_करो_scrap(काष्ठा inode *sufile, __u64 segnum,
			   काष्ठा buffer_head *header_bh,
			   काष्ठा buffer_head *su_bh)
अणु
	काष्ठा nilfs_segment_usage *su;
	व्योम *kaddr;
	पूर्णांक clean, dirty;

	kaddr = kmap_atomic(su_bh->b_page);
	su = nilfs_sufile_block_get_segment_usage(sufile, segnum, su_bh, kaddr);
	अगर (su->su_flags == cpu_to_le32(BIT(NILFS_SEGMENT_USAGE_सूचीTY)) &&
	    su->su_nblocks == cpu_to_le32(0)) अणु
		kunmap_atomic(kaddr);
		वापस;
	पूर्ण
	clean = nilfs_segment_usage_clean(su);
	dirty = nilfs_segment_usage_dirty(su);

	/* make the segment garbage */
	su->su_lasपंचांगod = cpu_to_le64(0);
	su->su_nblocks = cpu_to_le32(0);
	su->su_flags = cpu_to_le32(BIT(NILFS_SEGMENT_USAGE_सूचीTY));
	kunmap_atomic(kaddr);

	nilfs_sufile_mod_counter(header_bh, clean ? (u64)-1 : 0, dirty ? 0 : 1);
	NILFS_SUI(sufile)->ncleansegs -= clean;

	mark_buffer_dirty(su_bh);
	nilfs_mdt_mark_dirty(sufile);
पूर्ण

व्योम nilfs_sufile_करो_मुक्त(काष्ठा inode *sufile, __u64 segnum,
			  काष्ठा buffer_head *header_bh,
			  काष्ठा buffer_head *su_bh)
अणु
	काष्ठा nilfs_segment_usage *su;
	व्योम *kaddr;
	पूर्णांक sudirty;

	kaddr = kmap_atomic(su_bh->b_page);
	su = nilfs_sufile_block_get_segment_usage(sufile, segnum, su_bh, kaddr);
	अगर (nilfs_segment_usage_clean(su)) अणु
		nilfs_warn(sufile->i_sb, "%s: segment %llu is already clean",
			   __func__, (अचिन्हित दीर्घ दीर्घ)segnum);
		kunmap_atomic(kaddr);
		वापस;
	पूर्ण
	WARN_ON(nilfs_segment_usage_error(su));
	WARN_ON(!nilfs_segment_usage_dirty(su));

	sudirty = nilfs_segment_usage_dirty(su);
	nilfs_segment_usage_set_clean(su);
	kunmap_atomic(kaddr);
	mark_buffer_dirty(su_bh);

	nilfs_sufile_mod_counter(header_bh, 1, sudirty ? (u64)-1 : 0);
	NILFS_SUI(sufile)->ncleansegs++;

	nilfs_mdt_mark_dirty(sufile);

	trace_nilfs2_segment_usage_मुक्तd(sufile, segnum);
पूर्ण

/**
 * nilfs_sufile_mark_dirty - mark the buffer having a segment usage dirty
 * @sufile: inode of segment usage file
 * @segnum: segment number
 */
पूर्णांक nilfs_sufile_mark_dirty(काष्ठा inode *sufile, __u64 segnum)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक ret;

	ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 0, &bh);
	अगर (!ret) अणु
		mark_buffer_dirty(bh);
		nilfs_mdt_mark_dirty(sufile);
		brअन्यथा(bh);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * nilfs_sufile_set_segment_usage - set usage of a segment
 * @sufile: inode of segment usage file
 * @segnum: segment number
 * @nblocks: number of live blocks in the segment
 * @modसमय: modअगरication समय (option)
 */
पूर्णांक nilfs_sufile_set_segment_usage(काष्ठा inode *sufile, __u64 segnum,
				   अचिन्हित दीर्घ nblocks, समय64_t modसमय)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_segment_usage *su;
	व्योम *kaddr;
	पूर्णांक ret;

	करोwn_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);
	ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 0, &bh);
	अगर (ret < 0)
		जाओ out_sem;

	kaddr = kmap_atomic(bh->b_page);
	su = nilfs_sufile_block_get_segment_usage(sufile, segnum, bh, kaddr);
	WARN_ON(nilfs_segment_usage_error(su));
	अगर (modसमय)
		su->su_lasपंचांगod = cpu_to_le64(modसमय);
	su->su_nblocks = cpu_to_le32(nblocks);
	kunmap_atomic(kaddr);

	mark_buffer_dirty(bh);
	nilfs_mdt_mark_dirty(sufile);
	brअन्यथा(bh);

 out_sem:
	up_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_sufile_get_stat - get segment usage statistics
 * @sufile: inode of segment usage file
 * @sustat: poपूर्णांकer to a काष्ठाure of segment usage statistics
 *
 * Description: nilfs_sufile_get_stat() वापसs inक्रमmation about segment
 * usage.
 *
 * Return Value: On success, 0 is वापसed, and segment usage inक्रमmation is
 * stored in the place poपूर्णांकed by @sustat. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
पूर्णांक nilfs_sufile_get_stat(काष्ठा inode *sufile, काष्ठा nilfs_sustat *sustat)
अणु
	काष्ठा buffer_head *header_bh;
	काष्ठा nilfs_sufile_header *header;
	काष्ठा the_nilfs *nilfs = sufile->i_sb->s_fs_info;
	व्योम *kaddr;
	पूर्णांक ret;

	करोwn_पढ़ो(&NILFS_MDT(sufile)->mi_sem);

	ret = nilfs_sufile_get_header_block(sufile, &header_bh);
	अगर (ret < 0)
		जाओ out_sem;

	kaddr = kmap_atomic(header_bh->b_page);
	header = kaddr + bh_offset(header_bh);
	sustat->ss_nsegs = nilfs_sufile_get_nsegments(sufile);
	sustat->ss_ncleansegs = le64_to_cpu(header->sh_ncleansegs);
	sustat->ss_ndirtysegs = le64_to_cpu(header->sh_ndirtysegs);
	sustat->ss_स_समय = nilfs->ns_स_समय;
	sustat->ss_nongc_स_समय = nilfs->ns_nongc_स_समय;
	spin_lock(&nilfs->ns_last_segment_lock);
	sustat->ss_prot_seq = nilfs->ns_prot_seq;
	spin_unlock(&nilfs->ns_last_segment_lock);
	kunmap_atomic(kaddr);
	brअन्यथा(header_bh);

 out_sem:
	up_पढ़ो(&NILFS_MDT(sufile)->mi_sem);
	वापस ret;
पूर्ण

व्योम nilfs_sufile_करो_set_error(काष्ठा inode *sufile, __u64 segnum,
			       काष्ठा buffer_head *header_bh,
			       काष्ठा buffer_head *su_bh)
अणु
	काष्ठा nilfs_segment_usage *su;
	व्योम *kaddr;
	पूर्णांक suclean;

	kaddr = kmap_atomic(su_bh->b_page);
	su = nilfs_sufile_block_get_segment_usage(sufile, segnum, su_bh, kaddr);
	अगर (nilfs_segment_usage_error(su)) अणु
		kunmap_atomic(kaddr);
		वापस;
	पूर्ण
	suclean = nilfs_segment_usage_clean(su);
	nilfs_segment_usage_set_error(su);
	kunmap_atomic(kaddr);

	अगर (suclean) अणु
		nilfs_sufile_mod_counter(header_bh, -1, 0);
		NILFS_SUI(sufile)->ncleansegs--;
	पूर्ण
	mark_buffer_dirty(su_bh);
	nilfs_mdt_mark_dirty(sufile);
पूर्ण

/**
 * nilfs_sufile_truncate_range - truncate range of segment array
 * @sufile: inode of segment usage file
 * @start: start segment number (inclusive)
 * @end: end segment number (inclusive)
 *
 * Return Value: On success, 0 is वापसed.  On error, one of the
 * following negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EINVAL - Invalid number of segments specअगरied
 *
 * %-EBUSY - Dirty or active segments are present in the range
 */
अटल पूर्णांक nilfs_sufile_truncate_range(काष्ठा inode *sufile,
				       __u64 start, __u64 end)
अणु
	काष्ठा the_nilfs *nilfs = sufile->i_sb->s_fs_info;
	काष्ठा buffer_head *header_bh;
	काष्ठा buffer_head *su_bh;
	काष्ठा nilfs_segment_usage *su, *su2;
	माप_प्रकार susz = NILFS_MDT(sufile)->mi_entry_size;
	अचिन्हित दीर्घ segusages_per_block;
	अचिन्हित दीर्घ nsegs, ncleaned;
	__u64 segnum;
	व्योम *kaddr;
	sमाप_प्रकार n, nc;
	पूर्णांक ret;
	पूर्णांक j;

	nsegs = nilfs_sufile_get_nsegments(sufile);

	ret = -EINVAL;
	अगर (start > end || start >= nsegs)
		जाओ out;

	ret = nilfs_sufile_get_header_block(sufile, &header_bh);
	अगर (ret < 0)
		जाओ out;

	segusages_per_block = nilfs_sufile_segment_usages_per_block(sufile);
	ncleaned = 0;

	क्रम (segnum = start; segnum <= end; segnum += n) अणु
		n = min_t(अचिन्हित दीर्घ,
			  segusages_per_block -
				  nilfs_sufile_get_offset(sufile, segnum),
			  end - segnum + 1);
		ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 0,
							   &su_bh);
		अगर (ret < 0) अणु
			अगर (ret != -ENOENT)
				जाओ out_header;
			/* hole */
			जारी;
		पूर्ण
		kaddr = kmap_atomic(su_bh->b_page);
		su = nilfs_sufile_block_get_segment_usage(
			sufile, segnum, su_bh, kaddr);
		su2 = su;
		क्रम (j = 0; j < n; j++, su = (व्योम *)su + susz) अणु
			अगर ((le32_to_cpu(su->su_flags) &
			     ~BIT(NILFS_SEGMENT_USAGE_ERROR)) ||
			    nilfs_segment_is_active(nilfs, segnum + j)) अणु
				ret = -EBUSY;
				kunmap_atomic(kaddr);
				brअन्यथा(su_bh);
				जाओ out_header;
			पूर्ण
		पूर्ण
		nc = 0;
		क्रम (su = su2, j = 0; j < n; j++, su = (व्योम *)su + susz) अणु
			अगर (nilfs_segment_usage_error(su)) अणु
				nilfs_segment_usage_set_clean(su);
				nc++;
			पूर्ण
		पूर्ण
		kunmap_atomic(kaddr);
		अगर (nc > 0) अणु
			mark_buffer_dirty(su_bh);
			ncleaned += nc;
		पूर्ण
		brअन्यथा(su_bh);

		अगर (n == segusages_per_block) अणु
			/* make hole */
			nilfs_sufile_delete_segment_usage_block(sufile, segnum);
		पूर्ण
	पूर्ण
	ret = 0;

out_header:
	अगर (ncleaned > 0) अणु
		NILFS_SUI(sufile)->ncleansegs += ncleaned;
		nilfs_sufile_mod_counter(header_bh, ncleaned, 0);
		nilfs_mdt_mark_dirty(sufile);
	पूर्ण
	brअन्यथा(header_bh);
out:
	वापस ret;
पूर्ण

/**
 * nilfs_sufile_resize - resize segment array
 * @sufile: inode of segment usage file
 * @newnsegs: new number of segments
 *
 * Return Value: On success, 0 is वापसed.  On error, one of the
 * following negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOSPC - Enough मुक्त space is not left क्रम shrinking
 *
 * %-EBUSY - Dirty or active segments exist in the region to be truncated
 */
पूर्णांक nilfs_sufile_resize(काष्ठा inode *sufile, __u64 newnsegs)
अणु
	काष्ठा the_nilfs *nilfs = sufile->i_sb->s_fs_info;
	काष्ठा buffer_head *header_bh;
	काष्ठा nilfs_sufile_header *header;
	काष्ठा nilfs_sufile_info *sui = NILFS_SUI(sufile);
	व्योम *kaddr;
	अचिन्हित दीर्घ nsegs, nrsvsegs;
	पूर्णांक ret = 0;

	करोwn_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);

	nsegs = nilfs_sufile_get_nsegments(sufile);
	अगर (nsegs == newnsegs)
		जाओ out;

	ret = -ENOSPC;
	nrsvsegs = nilfs_nrsvsegs(nilfs, newnsegs);
	अगर (newnsegs < nsegs && nsegs - newnsegs + nrsvsegs > sui->ncleansegs)
		जाओ out;

	ret = nilfs_sufile_get_header_block(sufile, &header_bh);
	अगर (ret < 0)
		जाओ out;

	अगर (newnsegs > nsegs) अणु
		sui->ncleansegs += newnsegs - nsegs;
	पूर्ण अन्यथा /* newnsegs < nsegs */ अणु
		ret = nilfs_sufile_truncate_range(sufile, newnsegs, nsegs - 1);
		अगर (ret < 0)
			जाओ out_header;

		sui->ncleansegs -= nsegs - newnsegs;
	पूर्ण

	kaddr = kmap_atomic(header_bh->b_page);
	header = kaddr + bh_offset(header_bh);
	header->sh_ncleansegs = cpu_to_le64(sui->ncleansegs);
	kunmap_atomic(kaddr);

	mark_buffer_dirty(header_bh);
	nilfs_mdt_mark_dirty(sufile);
	nilfs_set_nsegments(nilfs, newnsegs);

out_header:
	brअन्यथा(header_bh);
out:
	up_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_sufile_get_suinfo -
 * @sufile: inode of segment usage file
 * @segnum: segment number to start looking
 * @buf: array of suinfo
 * @sisz: byte size of suinfo
 * @nsi: size of suinfo array
 *
 * Description:
 *
 * Return Value: On success, 0 is वापसed and .... On error, one of the
 * following negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
sमाप_प्रकार nilfs_sufile_get_suinfo(काष्ठा inode *sufile, __u64 segnum, व्योम *buf,
				अचिन्हित पूर्णांक sisz, माप_प्रकार nsi)
अणु
	काष्ठा buffer_head *su_bh;
	काष्ठा nilfs_segment_usage *su;
	काष्ठा nilfs_suinfo *si = buf;
	माप_प्रकार susz = NILFS_MDT(sufile)->mi_entry_size;
	काष्ठा the_nilfs *nilfs = sufile->i_sb->s_fs_info;
	व्योम *kaddr;
	अचिन्हित दीर्घ nsegs, segusages_per_block;
	sमाप_प्रकार n;
	पूर्णांक ret, i, j;

	करोwn_पढ़ो(&NILFS_MDT(sufile)->mi_sem);

	segusages_per_block = nilfs_sufile_segment_usages_per_block(sufile);
	nsegs = min_t(अचिन्हित दीर्घ,
		      nilfs_sufile_get_nsegments(sufile) - segnum,
		      nsi);
	क्रम (i = 0; i < nsegs; i += n, segnum += n) अणु
		n = min_t(अचिन्हित दीर्घ,
			  segusages_per_block -
				  nilfs_sufile_get_offset(sufile, segnum),
			  nsegs - i);
		ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 0,
							   &su_bh);
		अगर (ret < 0) अणु
			अगर (ret != -ENOENT)
				जाओ out;
			/* hole */
			स_रखो(si, 0, sisz * n);
			si = (व्योम *)si + sisz * n;
			जारी;
		पूर्ण

		kaddr = kmap_atomic(su_bh->b_page);
		su = nilfs_sufile_block_get_segment_usage(
			sufile, segnum, su_bh, kaddr);
		क्रम (j = 0; j < n;
		     j++, su = (व्योम *)su + susz, si = (व्योम *)si + sisz) अणु
			si->sui_lasपंचांगod = le64_to_cpu(su->su_lasपंचांगod);
			si->sui_nblocks = le32_to_cpu(su->su_nblocks);
			si->sui_flags = le32_to_cpu(su->su_flags) &
				~BIT(NILFS_SEGMENT_USAGE_ACTIVE);
			अगर (nilfs_segment_is_active(nilfs, segnum + j))
				si->sui_flags |=
					BIT(NILFS_SEGMENT_USAGE_ACTIVE);
		पूर्ण
		kunmap_atomic(kaddr);
		brअन्यथा(su_bh);
	पूर्ण
	ret = nsegs;

 out:
	up_पढ़ो(&NILFS_MDT(sufile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_sufile_set_suinfo - sets segment usage info
 * @sufile: inode of segment usage file
 * @buf: array of suinfo_update
 * @supsz: byte size of suinfo_update
 * @nsup: size of suinfo_update array
 *
 * Description: Takes an array of nilfs_suinfo_update काष्ठाs and updates
 * segment usage accordingly. Only the fields indicated by the sup_flags
 * are updated.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the
 * following negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EINVAL - Invalid values in input (segment number, flags or nblocks)
 */
sमाप_प्रकार nilfs_sufile_set_suinfo(काष्ठा inode *sufile, व्योम *buf,
				अचिन्हित पूर्णांक supsz, माप_प्रकार nsup)
अणु
	काष्ठा the_nilfs *nilfs = sufile->i_sb->s_fs_info;
	काष्ठा buffer_head *header_bh, *bh;
	काष्ठा nilfs_suinfo_update *sup, *supend = buf + supsz * nsup;
	काष्ठा nilfs_segment_usage *su;
	व्योम *kaddr;
	अचिन्हित दीर्घ blkoff, prev_blkoff;
	पूर्णांक cleansi, cleansu, dirtysi, dirtysu;
	दीर्घ ncleaned = 0, ndirtied = 0;
	पूर्णांक ret = 0;

	अगर (unlikely(nsup == 0))
		वापस ret;

	क्रम (sup = buf; sup < supend; sup = (व्योम *)sup + supsz) अणु
		अगर (sup->sup_segnum >= nilfs->ns_nsegments
			|| (sup->sup_flags &
				(~0UL << __NR_NILFS_SUINFO_UPDATE_FIELDS))
			|| (nilfs_suinfo_update_nblocks(sup) &&
				sup->sup_sui.sui_nblocks >
				nilfs->ns_blocks_per_segment))
			वापस -EINVAL;
	पूर्ण

	करोwn_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);

	ret = nilfs_sufile_get_header_block(sufile, &header_bh);
	अगर (ret < 0)
		जाओ out_sem;

	sup = buf;
	blkoff = nilfs_sufile_get_blkoff(sufile, sup->sup_segnum);
	ret = nilfs_mdt_get_block(sufile, blkoff, 1, शून्य, &bh);
	अगर (ret < 0)
		जाओ out_header;

	क्रम (;;) अणु
		kaddr = kmap_atomic(bh->b_page);
		su = nilfs_sufile_block_get_segment_usage(
			sufile, sup->sup_segnum, bh, kaddr);

		अगर (nilfs_suinfo_update_lasपंचांगod(sup))
			su->su_lasपंचांगod = cpu_to_le64(sup->sup_sui.sui_lasपंचांगod);

		अगर (nilfs_suinfo_update_nblocks(sup))
			su->su_nblocks = cpu_to_le32(sup->sup_sui.sui_nblocks);

		अगर (nilfs_suinfo_update_flags(sup)) अणु
			/*
			 * Active flag is a भव flag projected by running
			 * nilfs kernel code - drop it not to ग_लिखो it to
			 * disk.
			 */
			sup->sup_sui.sui_flags &=
					~BIT(NILFS_SEGMENT_USAGE_ACTIVE);

			cleansi = nilfs_suinfo_clean(&sup->sup_sui);
			cleansu = nilfs_segment_usage_clean(su);
			dirtysi = nilfs_suinfo_dirty(&sup->sup_sui);
			dirtysu = nilfs_segment_usage_dirty(su);

			अगर (cleansi && !cleansu)
				++ncleaned;
			अन्यथा अगर (!cleansi && cleansu)
				--ncleaned;

			अगर (dirtysi && !dirtysu)
				++ndirtied;
			अन्यथा अगर (!dirtysi && dirtysu)
				--ndirtied;

			su->su_flags = cpu_to_le32(sup->sup_sui.sui_flags);
		पूर्ण

		kunmap_atomic(kaddr);

		sup = (व्योम *)sup + supsz;
		अगर (sup >= supend)
			अवरोध;

		prev_blkoff = blkoff;
		blkoff = nilfs_sufile_get_blkoff(sufile, sup->sup_segnum);
		अगर (blkoff == prev_blkoff)
			जारी;

		/* get dअगरferent block */
		mark_buffer_dirty(bh);
		put_bh(bh);
		ret = nilfs_mdt_get_block(sufile, blkoff, 1, शून्य, &bh);
		अगर (unlikely(ret < 0))
			जाओ out_mark;
	पूर्ण
	mark_buffer_dirty(bh);
	put_bh(bh);

 out_mark:
	अगर (ncleaned || ndirtied) अणु
		nilfs_sufile_mod_counter(header_bh, (u64)ncleaned,
				(u64)ndirtied);
		NILFS_SUI(sufile)->ncleansegs += ncleaned;
	पूर्ण
	nilfs_mdt_mark_dirty(sufile);
 out_header:
	put_bh(header_bh);
 out_sem:
	up_ग_लिखो(&NILFS_MDT(sufile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_sufile_trim_fs() - trim ioctl handle function
 * @sufile: inode of segment usage file
 * @range: fstrim_range काष्ठाure
 *
 * start:	First Byte to trim
 * len:		number of Bytes to trim from start
 * minlen:	minimum extent length in Bytes
 *
 * Decription: nilfs_sufile_trim_fs goes through all segments containing bytes
 * from start to start+len. start is rounded up to the next block boundary
 * and start+len is rounded करोwn. For each clean segment blkdev_issue_discard
 * function is invoked.
 *
 * Return Value: On success, 0 is वापसed or negative error code, otherwise.
 */
पूर्णांक nilfs_sufile_trim_fs(काष्ठा inode *sufile, काष्ठा fstrim_range *range)
अणु
	काष्ठा the_nilfs *nilfs = sufile->i_sb->s_fs_info;
	काष्ठा buffer_head *su_bh;
	काष्ठा nilfs_segment_usage *su;
	व्योम *kaddr;
	माप_प्रकार n, i, susz = NILFS_MDT(sufile)->mi_entry_size;
	sector_t seg_start, seg_end, start_block, end_block;
	sector_t start = 0, nblocks = 0;
	u64 segnum, segnum_end, minlen, len, max_blocks, ndiscarded = 0;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक sects_per_block;

	sects_per_block = (1 << nilfs->ns_blocksize_bits) /
			bdev_logical_block_size(nilfs->ns_bdev);
	len = range->len >> nilfs->ns_blocksize_bits;
	minlen = range->minlen >> nilfs->ns_blocksize_bits;
	max_blocks = ((u64)nilfs->ns_nsegments * nilfs->ns_blocks_per_segment);

	अगर (!len || range->start >= max_blocks << nilfs->ns_blocksize_bits)
		वापस -EINVAL;

	start_block = (range->start + nilfs->ns_blocksize - 1) >>
			nilfs->ns_blocksize_bits;

	/*
	 * range->len can be very large (actually, it is set to
	 * ULदीर्घ_उच्च by शेष) - truncate upper end of the range
	 * carefully so as not to overflow.
	 */
	अगर (max_blocks - start_block < len)
		end_block = max_blocks - 1;
	अन्यथा
		end_block = start_block + len - 1;

	segnum = nilfs_get_segnum_of_block(nilfs, start_block);
	segnum_end = nilfs_get_segnum_of_block(nilfs, end_block);

	करोwn_पढ़ो(&NILFS_MDT(sufile)->mi_sem);

	जबतक (segnum <= segnum_end) अणु
		n = nilfs_sufile_segment_usages_in_block(sufile, segnum,
				segnum_end);

		ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 0,
							   &su_bh);
		अगर (ret < 0) अणु
			अगर (ret != -ENOENT)
				जाओ out_sem;
			/* hole */
			segnum += n;
			जारी;
		पूर्ण

		kaddr = kmap_atomic(su_bh->b_page);
		su = nilfs_sufile_block_get_segment_usage(sufile, segnum,
				su_bh, kaddr);
		क्रम (i = 0; i < n; ++i, ++segnum, su = (व्योम *)su + susz) अणु
			अगर (!nilfs_segment_usage_clean(su))
				जारी;

			nilfs_get_segment_range(nilfs, segnum, &seg_start,
						&seg_end);

			अगर (!nblocks) अणु
				/* start new extent */
				start = seg_start;
				nblocks = seg_end - seg_start + 1;
				जारी;
			पूर्ण

			अगर (start + nblocks == seg_start) अणु
				/* add to previous extent */
				nblocks += seg_end - seg_start + 1;
				जारी;
			पूर्ण

			/* discard previous extent */
			अगर (start < start_block) अणु
				nblocks -= start_block - start;
				start = start_block;
			पूर्ण

			अगर (nblocks >= minlen) अणु
				kunmap_atomic(kaddr);

				ret = blkdev_issue_discard(nilfs->ns_bdev,
						start * sects_per_block,
						nblocks * sects_per_block,
						GFP_NOFS, 0);
				अगर (ret < 0) अणु
					put_bh(su_bh);
					जाओ out_sem;
				पूर्ण

				ndiscarded += nblocks;
				kaddr = kmap_atomic(su_bh->b_page);
				su = nilfs_sufile_block_get_segment_usage(
					sufile, segnum, su_bh, kaddr);
			पूर्ण

			/* start new extent */
			start = seg_start;
			nblocks = seg_end - seg_start + 1;
		पूर्ण
		kunmap_atomic(kaddr);
		put_bh(su_bh);
	पूर्ण


	अगर (nblocks) अणु
		/* discard last extent */
		अगर (start < start_block) अणु
			nblocks -= start_block - start;
			start = start_block;
		पूर्ण
		अगर (start + nblocks > end_block + 1)
			nblocks = end_block - start + 1;

		अगर (nblocks >= minlen) अणु
			ret = blkdev_issue_discard(nilfs->ns_bdev,
					start * sects_per_block,
					nblocks * sects_per_block,
					GFP_NOFS, 0);
			अगर (!ret)
				ndiscarded += nblocks;
		पूर्ण
	पूर्ण

out_sem:
	up_पढ़ो(&NILFS_MDT(sufile)->mi_sem);

	range->len = ndiscarded << nilfs->ns_blocksize_bits;
	वापस ret;
पूर्ण

/**
 * nilfs_sufile_पढ़ो - पढ़ो or get sufile inode
 * @sb: super block instance
 * @susize: size of a segment usage entry
 * @raw_inode: on-disk sufile inode
 * @inodep: buffer to store the inode
 */
पूर्णांक nilfs_sufile_पढ़ो(काष्ठा super_block *sb, माप_प्रकार susize,
		      काष्ठा nilfs_inode *raw_inode, काष्ठा inode **inodep)
अणु
	काष्ठा inode *sufile;
	काष्ठा nilfs_sufile_info *sui;
	काष्ठा buffer_head *header_bh;
	काष्ठा nilfs_sufile_header *header;
	व्योम *kaddr;
	पूर्णांक err;

	अगर (susize > sb->s_blocksize) अणु
		nilfs_err(sb, "too large segment usage size: %zu bytes",
			  susize);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (susize < NILFS_MIN_SEGMENT_USAGE_SIZE) अणु
		nilfs_err(sb, "too small segment usage size: %zu bytes",
			  susize);
		वापस -EINVAL;
	पूर्ण

	sufile = nilfs_iget_locked(sb, शून्य, NILFS_SUखाता_INO);
	अगर (unlikely(!sufile))
		वापस -ENOMEM;
	अगर (!(sufile->i_state & I_NEW))
		जाओ out;

	err = nilfs_mdt_init(sufile, NILFS_MDT_GFP, माप(*sui));
	अगर (err)
		जाओ failed;

	nilfs_mdt_set_entry_size(sufile, susize,
				 माप(काष्ठा nilfs_sufile_header));

	err = nilfs_पढ़ो_inode_common(sufile, raw_inode);
	अगर (err)
		जाओ failed;

	err = nilfs_sufile_get_header_block(sufile, &header_bh);
	अगर (err)
		जाओ failed;

	sui = NILFS_SUI(sufile);
	kaddr = kmap_atomic(header_bh->b_page);
	header = kaddr + bh_offset(header_bh);
	sui->ncleansegs = le64_to_cpu(header->sh_ncleansegs);
	kunmap_atomic(kaddr);
	brअन्यथा(header_bh);

	sui->allocmax = nilfs_sufile_get_nsegments(sufile) - 1;
	sui->allocmin = 0;

	unlock_new_inode(sufile);
 out:
	*inodep = sufile;
	वापस 0;
 failed:
	iget_failed(sufile);
	वापस err;
पूर्ण
