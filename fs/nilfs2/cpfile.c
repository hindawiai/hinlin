<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * cpfile.c - NILFS checkpoपूर्णांक file.
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश "mdt.h"
#समावेश "cpfile.h"


अटल अंतरभूत अचिन्हित दीर्घ
nilfs_cpfile_checkpoपूर्णांकs_per_block(स्थिर काष्ठा inode *cpfile)
अणु
	वापस NILFS_MDT(cpfile)->mi_entries_per_block;
पूर्ण

/* block number from the beginning of the file */
अटल अचिन्हित दीर्घ
nilfs_cpfile_get_blkoff(स्थिर काष्ठा inode *cpfile, __u64 cno)
अणु
	__u64 tcno = cno + NILFS_MDT(cpfile)->mi_first_entry_offset - 1;

	करो_भाग(tcno, nilfs_cpfile_checkpoपूर्णांकs_per_block(cpfile));
	वापस (अचिन्हित दीर्घ)tcno;
पूर्ण

/* offset in block */
अटल अचिन्हित दीर्घ
nilfs_cpfile_get_offset(स्थिर काष्ठा inode *cpfile, __u64 cno)
अणु
	__u64 tcno = cno + NILFS_MDT(cpfile)->mi_first_entry_offset - 1;

	वापस करो_भाग(tcno, nilfs_cpfile_checkpoपूर्णांकs_per_block(cpfile));
पूर्ण

अटल __u64 nilfs_cpfile_first_checkpoपूर्णांक_in_block(स्थिर काष्ठा inode *cpfile,
						    अचिन्हित दीर्घ blkoff)
अणु
	वापस (__u64)nilfs_cpfile_checkpoपूर्णांकs_per_block(cpfile) * blkoff
		+ 1 - NILFS_MDT(cpfile)->mi_first_entry_offset;
पूर्ण

अटल अचिन्हित दीर्घ
nilfs_cpfile_checkpoपूर्णांकs_in_block(स्थिर काष्ठा inode *cpfile,
				  __u64 curr,
				  __u64 max)
अणु
	वापस min_t(__u64,
		     nilfs_cpfile_checkpoपूर्णांकs_per_block(cpfile) -
		     nilfs_cpfile_get_offset(cpfile, curr),
		     max - curr);
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_cpfile_is_in_first(स्थिर काष्ठा inode *cpfile,
					   __u64 cno)
अणु
	वापस nilfs_cpfile_get_blkoff(cpfile, cno) == 0;
पूर्ण

अटल अचिन्हित पूर्णांक
nilfs_cpfile_block_add_valid_checkpoपूर्णांकs(स्थिर काष्ठा inode *cpfile,
					 काष्ठा buffer_head *bh,
					 व्योम *kaddr,
					 अचिन्हित पूर्णांक n)
अणु
	काष्ठा nilfs_checkpoपूर्णांक *cp = kaddr + bh_offset(bh);
	अचिन्हित पूर्णांक count;

	count = le32_to_cpu(cp->cp_checkpoपूर्णांकs_count) + n;
	cp->cp_checkpoपूर्णांकs_count = cpu_to_le32(count);
	वापस count;
पूर्ण

अटल अचिन्हित पूर्णांक
nilfs_cpfile_block_sub_valid_checkpoपूर्णांकs(स्थिर काष्ठा inode *cpfile,
					 काष्ठा buffer_head *bh,
					 व्योम *kaddr,
					 अचिन्हित पूर्णांक n)
अणु
	काष्ठा nilfs_checkpoपूर्णांक *cp = kaddr + bh_offset(bh);
	अचिन्हित पूर्णांक count;

	WARN_ON(le32_to_cpu(cp->cp_checkpoपूर्णांकs_count) < n);
	count = le32_to_cpu(cp->cp_checkpoपूर्णांकs_count) - n;
	cp->cp_checkpoपूर्णांकs_count = cpu_to_le32(count);
	वापस count;
पूर्ण

अटल अंतरभूत काष्ठा nilfs_cpfile_header *
nilfs_cpfile_block_get_header(स्थिर काष्ठा inode *cpfile,
			      काष्ठा buffer_head *bh,
			      व्योम *kaddr)
अणु
	वापस kaddr + bh_offset(bh);
पूर्ण

अटल काष्ठा nilfs_checkpoपूर्णांक *
nilfs_cpfile_block_get_checkpoपूर्णांक(स्थिर काष्ठा inode *cpfile, __u64 cno,
				  काष्ठा buffer_head *bh,
				  व्योम *kaddr)
अणु
	वापस kaddr + bh_offset(bh) + nilfs_cpfile_get_offset(cpfile, cno) *
		NILFS_MDT(cpfile)->mi_entry_size;
पूर्ण

अटल व्योम nilfs_cpfile_block_init(काष्ठा inode *cpfile,
				    काष्ठा buffer_head *bh,
				    व्योम *kaddr)
अणु
	काष्ठा nilfs_checkpoपूर्णांक *cp = kaddr + bh_offset(bh);
	माप_प्रकार cpsz = NILFS_MDT(cpfile)->mi_entry_size;
	पूर्णांक n = nilfs_cpfile_checkpoपूर्णांकs_per_block(cpfile);

	जबतक (n-- > 0) अणु
		nilfs_checkpoपूर्णांक_set_invalid(cp);
		cp = (व्योम *)cp + cpsz;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_cpfile_get_header_block(काष्ठा inode *cpfile,
						काष्ठा buffer_head **bhp)
अणु
	वापस nilfs_mdt_get_block(cpfile, 0, 0, शून्य, bhp);
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_cpfile_get_checkpoपूर्णांक_block(काष्ठा inode *cpfile,
						    __u64 cno,
						    पूर्णांक create,
						    काष्ठा buffer_head **bhp)
अणु
	वापस nilfs_mdt_get_block(cpfile,
				   nilfs_cpfile_get_blkoff(cpfile, cno),
				   create, nilfs_cpfile_block_init, bhp);
पूर्ण

/**
 * nilfs_cpfile_find_checkpoपूर्णांक_block - find and get a buffer on cpfile
 * @cpfile: inode of cpfile
 * @start_cno: start checkpoपूर्णांक number (inclusive)
 * @end_cno: end checkpoपूर्णांक number (inclusive)
 * @cnop: place to store the next checkpoपूर्णांक number
 * @bhp: place to store a poपूर्णांकer to buffer_head काष्ठा
 *
 * Return Value: On success, it वापसs 0. On error, the following negative
 * error code is वापसed.
 *
 * %-ENOMEM - Insufficient memory available.
 *
 * %-EIO - I/O error
 *
 * %-ENOENT - no block exists in the range.
 */
अटल पूर्णांक nilfs_cpfile_find_checkpoपूर्णांक_block(काष्ठा inode *cpfile,
					      __u64 start_cno, __u64 end_cno,
					      __u64 *cnop,
					      काष्ठा buffer_head **bhp)
अणु
	अचिन्हित दीर्घ start, end, blkoff;
	पूर्णांक ret;

	अगर (unlikely(start_cno > end_cno))
		वापस -ENOENT;

	start = nilfs_cpfile_get_blkoff(cpfile, start_cno);
	end = nilfs_cpfile_get_blkoff(cpfile, end_cno);

	ret = nilfs_mdt_find_block(cpfile, start, end, &blkoff, bhp);
	अगर (!ret)
		*cnop = (blkoff == start) ? start_cno :
			nilfs_cpfile_first_checkpoपूर्णांक_in_block(cpfile, blkoff);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_cpfile_delete_checkpoपूर्णांक_block(काष्ठा inode *cpfile,
						       __u64 cno)
अणु
	वापस nilfs_mdt_delete_block(cpfile,
				      nilfs_cpfile_get_blkoff(cpfile, cno));
पूर्ण

/**
 * nilfs_cpfile_get_checkpoपूर्णांक - get a checkpoपूर्णांक
 * @cpfile: inode of checkpoपूर्णांक file
 * @cno: checkpoपूर्णांक number
 * @create: create flag
 * @cpp: poपूर्णांकer to a checkpoपूर्णांक
 * @bhp: poपूर्णांकer to a buffer head
 *
 * Description: nilfs_cpfile_get_checkpoपूर्णांक() acquires the checkpoपूर्णांक
 * specअगरied by @cno. A new checkpoपूर्णांक will be created अगर @cno is the current
 * checkpoपूर्णांक number and @create is nonzero.
 *
 * Return Value: On success, 0 is वापसed, and the checkpoपूर्णांक and the
 * buffer head of the buffer on which the checkpoपूर्णांक is located are stored in
 * the place poपूर्णांकed by @cpp and @bhp, respectively. On error, one of the
 * following negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - No such checkpoपूर्णांक.
 *
 * %-EINVAL - invalid checkpoपूर्णांक.
 */
पूर्णांक nilfs_cpfile_get_checkpoपूर्णांक(काष्ठा inode *cpfile,
				__u64 cno,
				पूर्णांक create,
				काष्ठा nilfs_checkpoपूर्णांक **cpp,
				काष्ठा buffer_head **bhp)
अणु
	काष्ठा buffer_head *header_bh, *cp_bh;
	काष्ठा nilfs_cpfile_header *header;
	काष्ठा nilfs_checkpoपूर्णांक *cp;
	व्योम *kaddr;
	पूर्णांक ret;

	अगर (unlikely(cno < 1 || cno > nilfs_mdt_cno(cpfile) ||
		     (cno < nilfs_mdt_cno(cpfile) && create)))
		वापस -EINVAL;

	करोwn_ग_लिखो(&NILFS_MDT(cpfile)->mi_sem);

	ret = nilfs_cpfile_get_header_block(cpfile, &header_bh);
	अगर (ret < 0)
		जाओ out_sem;
	ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, cno, create, &cp_bh);
	अगर (ret < 0)
		जाओ out_header;
	kaddr = kmap(cp_bh->b_page);
	cp = nilfs_cpfile_block_get_checkpoपूर्णांक(cpfile, cno, cp_bh, kaddr);
	अगर (nilfs_checkpoपूर्णांक_invalid(cp)) अणु
		अगर (!create) अणु
			kunmap(cp_bh->b_page);
			brअन्यथा(cp_bh);
			ret = -ENOENT;
			जाओ out_header;
		पूर्ण
		/* a newly-created checkpoपूर्णांक */
		nilfs_checkpoपूर्णांक_clear_invalid(cp);
		अगर (!nilfs_cpfile_is_in_first(cpfile, cno))
			nilfs_cpfile_block_add_valid_checkpoपूर्णांकs(cpfile, cp_bh,
								 kaddr, 1);
		mark_buffer_dirty(cp_bh);

		kaddr = kmap_atomic(header_bh->b_page);
		header = nilfs_cpfile_block_get_header(cpfile, header_bh,
						       kaddr);
		le64_add_cpu(&header->ch_ncheckpoपूर्णांकs, 1);
		kunmap_atomic(kaddr);
		mark_buffer_dirty(header_bh);
		nilfs_mdt_mark_dirty(cpfile);
	पूर्ण

	अगर (cpp != शून्य)
		*cpp = cp;
	*bhp = cp_bh;

 out_header:
	brअन्यथा(header_bh);

 out_sem:
	up_ग_लिखो(&NILFS_MDT(cpfile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_cpfile_put_checkpoपूर्णांक - put a checkpoपूर्णांक
 * @cpfile: inode of checkpoपूर्णांक file
 * @cno: checkpoपूर्णांक number
 * @bh: buffer head
 *
 * Description: nilfs_cpfile_put_checkpoपूर्णांक() releases the checkpoपूर्णांक
 * specअगरied by @cno. @bh must be the buffer head which has been वापसed by
 * a previous call to nilfs_cpfile_get_checkpoपूर्णांक() with @cno.
 */
व्योम nilfs_cpfile_put_checkpoपूर्णांक(काष्ठा inode *cpfile, __u64 cno,
				 काष्ठा buffer_head *bh)
अणु
	kunmap(bh->b_page);
	brअन्यथा(bh);
पूर्ण

/**
 * nilfs_cpfile_delete_checkpoपूर्णांकs - delete checkpoपूर्णांकs
 * @cpfile: inode of checkpoपूर्णांक file
 * @start: start checkpoपूर्णांक number
 * @end: end checkpoपूर्णांक number
 *
 * Description: nilfs_cpfile_delete_checkpoपूर्णांकs() deletes the checkpoपूर्णांकs in
 * the period from @start to @end, excluding @end itself. The checkpoपूर्णांकs
 * which have been alपढ़ोy deleted are ignored.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EINVAL - invalid checkpoपूर्णांकs.
 */
पूर्णांक nilfs_cpfile_delete_checkpoपूर्णांकs(काष्ठा inode *cpfile,
				    __u64 start,
				    __u64 end)
अणु
	काष्ठा buffer_head *header_bh, *cp_bh;
	काष्ठा nilfs_cpfile_header *header;
	काष्ठा nilfs_checkpoपूर्णांक *cp;
	माप_प्रकार cpsz = NILFS_MDT(cpfile)->mi_entry_size;
	__u64 cno;
	व्योम *kaddr;
	अचिन्हित दीर्घ tnicps;
	पूर्णांक ret, ncps, nicps, nss, count, i;

	अगर (unlikely(start == 0 || start > end)) अणु
		nilfs_err(cpfile->i_sb,
			  "cannot delete checkpoints: invalid range [%llu, %llu)",
			  (अचिन्हित दीर्घ दीर्घ)start, (अचिन्हित दीर्घ दीर्घ)end);
		वापस -EINVAL;
	पूर्ण

	करोwn_ग_लिखो(&NILFS_MDT(cpfile)->mi_sem);

	ret = nilfs_cpfile_get_header_block(cpfile, &header_bh);
	अगर (ret < 0)
		जाओ out_sem;
	tnicps = 0;
	nss = 0;

	क्रम (cno = start; cno < end; cno += ncps) अणु
		ncps = nilfs_cpfile_checkpoपूर्णांकs_in_block(cpfile, cno, end);
		ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, cno, 0, &cp_bh);
		अगर (ret < 0) अणु
			अगर (ret != -ENOENT)
				अवरोध;
			/* skip hole */
			ret = 0;
			जारी;
		पूर्ण

		kaddr = kmap_atomic(cp_bh->b_page);
		cp = nilfs_cpfile_block_get_checkpoपूर्णांक(
			cpfile, cno, cp_bh, kaddr);
		nicps = 0;
		क्रम (i = 0; i < ncps; i++, cp = (व्योम *)cp + cpsz) अणु
			अगर (nilfs_checkpoपूर्णांक_snapshot(cp)) अणु
				nss++;
			पूर्ण अन्यथा अगर (!nilfs_checkpoपूर्णांक_invalid(cp)) अणु
				nilfs_checkpoपूर्णांक_set_invalid(cp);
				nicps++;
			पूर्ण
		पूर्ण
		अगर (nicps > 0) अणु
			tnicps += nicps;
			mark_buffer_dirty(cp_bh);
			nilfs_mdt_mark_dirty(cpfile);
			अगर (!nilfs_cpfile_is_in_first(cpfile, cno)) अणु
				count =
				  nilfs_cpfile_block_sub_valid_checkpoपूर्णांकs(
						cpfile, cp_bh, kaddr, nicps);
				अगर (count == 0) अणु
					/* make hole */
					kunmap_atomic(kaddr);
					brअन्यथा(cp_bh);
					ret =
					  nilfs_cpfile_delete_checkpoपूर्णांक_block(
								   cpfile, cno);
					अगर (ret == 0)
						जारी;
					nilfs_err(cpfile->i_sb,
						  "error %d deleting checkpoint block",
						  ret);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		kunmap_atomic(kaddr);
		brअन्यथा(cp_bh);
	पूर्ण

	अगर (tnicps > 0) अणु
		kaddr = kmap_atomic(header_bh->b_page);
		header = nilfs_cpfile_block_get_header(cpfile, header_bh,
						       kaddr);
		le64_add_cpu(&header->ch_ncheckpoपूर्णांकs, -(u64)tnicps);
		mark_buffer_dirty(header_bh);
		nilfs_mdt_mark_dirty(cpfile);
		kunmap_atomic(kaddr);
	पूर्ण

	brअन्यथा(header_bh);
	अगर (nss > 0)
		ret = -EBUSY;

 out_sem:
	up_ग_लिखो(&NILFS_MDT(cpfile)->mi_sem);
	वापस ret;
पूर्ण

अटल व्योम nilfs_cpfile_checkpoपूर्णांक_to_cpinfo(काष्ठा inode *cpfile,
					      काष्ठा nilfs_checkpoपूर्णांक *cp,
					      काष्ठा nilfs_cpinfo *ci)
अणु
	ci->ci_flags = le32_to_cpu(cp->cp_flags);
	ci->ci_cno = le64_to_cpu(cp->cp_cno);
	ci->ci_create = le64_to_cpu(cp->cp_create);
	ci->ci_nblk_inc = le64_to_cpu(cp->cp_nblk_inc);
	ci->ci_inodes_count = le64_to_cpu(cp->cp_inodes_count);
	ci->ci_blocks_count = le64_to_cpu(cp->cp_blocks_count);
	ci->ci_next = le64_to_cpu(cp->cp_snapshot_list.ssl_next);
पूर्ण

अटल sमाप_प्रकार nilfs_cpfile_करो_get_cpinfo(काष्ठा inode *cpfile, __u64 *cnop,
					  व्योम *buf, अचिन्हित पूर्णांक cisz,
					  माप_प्रकार nci)
अणु
	काष्ठा nilfs_checkpoपूर्णांक *cp;
	काष्ठा nilfs_cpinfo *ci = buf;
	काष्ठा buffer_head *bh;
	माप_प्रकार cpsz = NILFS_MDT(cpfile)->mi_entry_size;
	__u64 cur_cno = nilfs_mdt_cno(cpfile), cno = *cnop;
	व्योम *kaddr;
	पूर्णांक n, ret;
	पूर्णांक ncps, i;

	अगर (cno == 0)
		वापस -ENOENT; /* checkpoपूर्णांक number 0 is invalid */
	करोwn_पढ़ो(&NILFS_MDT(cpfile)->mi_sem);

	क्रम (n = 0; n < nci; cno += ncps) अणु
		ret = nilfs_cpfile_find_checkpoपूर्णांक_block(
			cpfile, cno, cur_cno - 1, &cno, &bh);
		अगर (ret < 0) अणु
			अगर (likely(ret == -ENOENT))
				अवरोध;
			जाओ out;
		पूर्ण
		ncps = nilfs_cpfile_checkpoपूर्णांकs_in_block(cpfile, cno, cur_cno);

		kaddr = kmap_atomic(bh->b_page);
		cp = nilfs_cpfile_block_get_checkpoपूर्णांक(cpfile, cno, bh, kaddr);
		क्रम (i = 0; i < ncps && n < nci; i++, cp = (व्योम *)cp + cpsz) अणु
			अगर (!nilfs_checkpoपूर्णांक_invalid(cp)) अणु
				nilfs_cpfile_checkpoपूर्णांक_to_cpinfo(cpfile, cp,
								  ci);
				ci = (व्योम *)ci + cisz;
				n++;
			पूर्ण
		पूर्ण
		kunmap_atomic(kaddr);
		brअन्यथा(bh);
	पूर्ण

	ret = n;
	अगर (n > 0) अणु
		ci = (व्योम *)ci - cisz;
		*cnop = ci->ci_cno + 1;
	पूर्ण

 out:
	up_पढ़ो(&NILFS_MDT(cpfile)->mi_sem);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार nilfs_cpfile_करो_get_ssinfo(काष्ठा inode *cpfile, __u64 *cnop,
					  व्योम *buf, अचिन्हित पूर्णांक cisz,
					  माप_प्रकार nci)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_cpfile_header *header;
	काष्ठा nilfs_checkpoपूर्णांक *cp;
	काष्ठा nilfs_cpinfo *ci = buf;
	__u64 curr = *cnop, next;
	अचिन्हित दीर्घ curr_blkoff, next_blkoff;
	व्योम *kaddr;
	पूर्णांक n = 0, ret;

	करोwn_पढ़ो(&NILFS_MDT(cpfile)->mi_sem);

	अगर (curr == 0) अणु
		ret = nilfs_cpfile_get_header_block(cpfile, &bh);
		अगर (ret < 0)
			जाओ out;
		kaddr = kmap_atomic(bh->b_page);
		header = nilfs_cpfile_block_get_header(cpfile, bh, kaddr);
		curr = le64_to_cpu(header->ch_snapshot_list.ssl_next);
		kunmap_atomic(kaddr);
		brअन्यथा(bh);
		अगर (curr == 0) अणु
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(curr == ~(__u64)0)) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	curr_blkoff = nilfs_cpfile_get_blkoff(cpfile, curr);
	ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, curr, 0, &bh);
	अगर (unlikely(ret < 0)) अणु
		अगर (ret == -ENOENT)
			ret = 0; /* No snapshots (started from a hole block) */
		जाओ out;
	पूर्ण
	kaddr = kmap_atomic(bh->b_page);
	जबतक (n < nci) अणु
		cp = nilfs_cpfile_block_get_checkpoपूर्णांक(cpfile, curr, bh, kaddr);
		curr = ~(__u64)0; /* Terminator */
		अगर (unlikely(nilfs_checkpoपूर्णांक_invalid(cp) ||
			     !nilfs_checkpoपूर्णांक_snapshot(cp)))
			अवरोध;
		nilfs_cpfile_checkpoपूर्णांक_to_cpinfo(cpfile, cp, ci);
		ci = (व्योम *)ci + cisz;
		n++;
		next = le64_to_cpu(cp->cp_snapshot_list.ssl_next);
		अगर (next == 0)
			अवरोध; /* reach end of the snapshot list */

		next_blkoff = nilfs_cpfile_get_blkoff(cpfile, next);
		अगर (curr_blkoff != next_blkoff) अणु
			kunmap_atomic(kaddr);
			brअन्यथा(bh);
			ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, next,
								0, &bh);
			अगर (unlikely(ret < 0)) अणु
				WARN_ON(ret == -ENOENT);
				जाओ out;
			पूर्ण
			kaddr = kmap_atomic(bh->b_page);
		पूर्ण
		curr = next;
		curr_blkoff = next_blkoff;
	पूर्ण
	kunmap_atomic(kaddr);
	brअन्यथा(bh);
	*cnop = curr;
	ret = n;

 out:
	up_पढ़ो(&NILFS_MDT(cpfile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_cpfile_get_cpinfo -
 * @cpfile:
 * @cno:
 * @ci:
 * @nci:
 */

sमाप_प्रकार nilfs_cpfile_get_cpinfo(काष्ठा inode *cpfile, __u64 *cnop, पूर्णांक mode,
				व्योम *buf, अचिन्हित पूर्णांक cisz, माप_प्रकार nci)
अणु
	चयन (mode) अणु
	हाल NILFS_CHECKPOINT:
		वापस nilfs_cpfile_करो_get_cpinfo(cpfile, cnop, buf, cisz, nci);
	हाल NILFS_SNAPSHOT:
		वापस nilfs_cpfile_करो_get_ssinfo(cpfile, cnop, buf, cisz, nci);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * nilfs_cpfile_delete_checkpoपूर्णांक -
 * @cpfile:
 * @cno:
 */
पूर्णांक nilfs_cpfile_delete_checkpoपूर्णांक(काष्ठा inode *cpfile, __u64 cno)
अणु
	काष्ठा nilfs_cpinfo ci;
	__u64 tcno = cno;
	sमाप_प्रकार nci;

	nci = nilfs_cpfile_करो_get_cpinfo(cpfile, &tcno, &ci, माप(ci), 1);
	अगर (nci < 0)
		वापस nci;
	अन्यथा अगर (nci == 0 || ci.ci_cno != cno)
		वापस -ENOENT;
	अन्यथा अगर (nilfs_cpinfo_snapshot(&ci))
		वापस -EBUSY;

	वापस nilfs_cpfile_delete_checkpoपूर्णांकs(cpfile, cno, cno + 1);
पूर्ण

अटल काष्ठा nilfs_snapshot_list *
nilfs_cpfile_block_get_snapshot_list(स्थिर काष्ठा inode *cpfile,
				     __u64 cno,
				     काष्ठा buffer_head *bh,
				     व्योम *kaddr)
अणु
	काष्ठा nilfs_cpfile_header *header;
	काष्ठा nilfs_checkpoपूर्णांक *cp;
	काष्ठा nilfs_snapshot_list *list;

	अगर (cno != 0) अणु
		cp = nilfs_cpfile_block_get_checkpoपूर्णांक(cpfile, cno, bh, kaddr);
		list = &cp->cp_snapshot_list;
	पूर्ण अन्यथा अणु
		header = nilfs_cpfile_block_get_header(cpfile, bh, kaddr);
		list = &header->ch_snapshot_list;
	पूर्ण
	वापस list;
पूर्ण

अटल पूर्णांक nilfs_cpfile_set_snapshot(काष्ठा inode *cpfile, __u64 cno)
अणु
	काष्ठा buffer_head *header_bh, *curr_bh, *prev_bh, *cp_bh;
	काष्ठा nilfs_cpfile_header *header;
	काष्ठा nilfs_checkpoपूर्णांक *cp;
	काष्ठा nilfs_snapshot_list *list;
	__u64 curr, prev;
	अचिन्हित दीर्घ curr_blkoff, prev_blkoff;
	व्योम *kaddr;
	पूर्णांक ret;

	अगर (cno == 0)
		वापस -ENOENT; /* checkpoपूर्णांक number 0 is invalid */
	करोwn_ग_लिखो(&NILFS_MDT(cpfile)->mi_sem);

	ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, cno, 0, &cp_bh);
	अगर (ret < 0)
		जाओ out_sem;
	kaddr = kmap_atomic(cp_bh->b_page);
	cp = nilfs_cpfile_block_get_checkpoपूर्णांक(cpfile, cno, cp_bh, kaddr);
	अगर (nilfs_checkpoपूर्णांक_invalid(cp)) अणु
		ret = -ENOENT;
		kunmap_atomic(kaddr);
		जाओ out_cp;
	पूर्ण
	अगर (nilfs_checkpoपूर्णांक_snapshot(cp)) अणु
		ret = 0;
		kunmap_atomic(kaddr);
		जाओ out_cp;
	पूर्ण
	kunmap_atomic(kaddr);

	ret = nilfs_cpfile_get_header_block(cpfile, &header_bh);
	अगर (ret < 0)
		जाओ out_cp;
	kaddr = kmap_atomic(header_bh->b_page);
	header = nilfs_cpfile_block_get_header(cpfile, header_bh, kaddr);
	list = &header->ch_snapshot_list;
	curr_bh = header_bh;
	get_bh(curr_bh);
	curr = 0;
	curr_blkoff = 0;
	prev = le64_to_cpu(list->ssl_prev);
	जबतक (prev > cno) अणु
		prev_blkoff = nilfs_cpfile_get_blkoff(cpfile, prev);
		curr = prev;
		अगर (curr_blkoff != prev_blkoff) अणु
			kunmap_atomic(kaddr);
			brअन्यथा(curr_bh);
			ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, curr,
								0, &curr_bh);
			अगर (ret < 0)
				जाओ out_header;
			kaddr = kmap_atomic(curr_bh->b_page);
		पूर्ण
		curr_blkoff = prev_blkoff;
		cp = nilfs_cpfile_block_get_checkpoपूर्णांक(
			cpfile, curr, curr_bh, kaddr);
		list = &cp->cp_snapshot_list;
		prev = le64_to_cpu(list->ssl_prev);
	पूर्ण
	kunmap_atomic(kaddr);

	अगर (prev != 0) अणु
		ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, prev, 0,
							&prev_bh);
		अगर (ret < 0)
			जाओ out_curr;
	पूर्ण अन्यथा अणु
		prev_bh = header_bh;
		get_bh(prev_bh);
	पूर्ण

	kaddr = kmap_atomic(curr_bh->b_page);
	list = nilfs_cpfile_block_get_snapshot_list(
		cpfile, curr, curr_bh, kaddr);
	list->ssl_prev = cpu_to_le64(cno);
	kunmap_atomic(kaddr);

	kaddr = kmap_atomic(cp_bh->b_page);
	cp = nilfs_cpfile_block_get_checkpoपूर्णांक(cpfile, cno, cp_bh, kaddr);
	cp->cp_snapshot_list.ssl_next = cpu_to_le64(curr);
	cp->cp_snapshot_list.ssl_prev = cpu_to_le64(prev);
	nilfs_checkpoपूर्णांक_set_snapshot(cp);
	kunmap_atomic(kaddr);

	kaddr = kmap_atomic(prev_bh->b_page);
	list = nilfs_cpfile_block_get_snapshot_list(
		cpfile, prev, prev_bh, kaddr);
	list->ssl_next = cpu_to_le64(cno);
	kunmap_atomic(kaddr);

	kaddr = kmap_atomic(header_bh->b_page);
	header = nilfs_cpfile_block_get_header(cpfile, header_bh, kaddr);
	le64_add_cpu(&header->ch_nsnapshots, 1);
	kunmap_atomic(kaddr);

	mark_buffer_dirty(prev_bh);
	mark_buffer_dirty(curr_bh);
	mark_buffer_dirty(cp_bh);
	mark_buffer_dirty(header_bh);
	nilfs_mdt_mark_dirty(cpfile);

	brअन्यथा(prev_bh);

 out_curr:
	brअन्यथा(curr_bh);

 out_header:
	brअन्यथा(header_bh);

 out_cp:
	brअन्यथा(cp_bh);

 out_sem:
	up_ग_लिखो(&NILFS_MDT(cpfile)->mi_sem);
	वापस ret;
पूर्ण

अटल पूर्णांक nilfs_cpfile_clear_snapshot(काष्ठा inode *cpfile, __u64 cno)
अणु
	काष्ठा buffer_head *header_bh, *next_bh, *prev_bh, *cp_bh;
	काष्ठा nilfs_cpfile_header *header;
	काष्ठा nilfs_checkpoपूर्णांक *cp;
	काष्ठा nilfs_snapshot_list *list;
	__u64 next, prev;
	व्योम *kaddr;
	पूर्णांक ret;

	अगर (cno == 0)
		वापस -ENOENT; /* checkpoपूर्णांक number 0 is invalid */
	करोwn_ग_लिखो(&NILFS_MDT(cpfile)->mi_sem);

	ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, cno, 0, &cp_bh);
	अगर (ret < 0)
		जाओ out_sem;
	kaddr = kmap_atomic(cp_bh->b_page);
	cp = nilfs_cpfile_block_get_checkpoपूर्णांक(cpfile, cno, cp_bh, kaddr);
	अगर (nilfs_checkpoपूर्णांक_invalid(cp)) अणु
		ret = -ENOENT;
		kunmap_atomic(kaddr);
		जाओ out_cp;
	पूर्ण
	अगर (!nilfs_checkpoपूर्णांक_snapshot(cp)) अणु
		ret = 0;
		kunmap_atomic(kaddr);
		जाओ out_cp;
	पूर्ण

	list = &cp->cp_snapshot_list;
	next = le64_to_cpu(list->ssl_next);
	prev = le64_to_cpu(list->ssl_prev);
	kunmap_atomic(kaddr);

	ret = nilfs_cpfile_get_header_block(cpfile, &header_bh);
	अगर (ret < 0)
		जाओ out_cp;
	अगर (next != 0) अणु
		ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, next, 0,
							&next_bh);
		अगर (ret < 0)
			जाओ out_header;
	पूर्ण अन्यथा अणु
		next_bh = header_bh;
		get_bh(next_bh);
	पूर्ण
	अगर (prev != 0) अणु
		ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, prev, 0,
							&prev_bh);
		अगर (ret < 0)
			जाओ out_next;
	पूर्ण अन्यथा अणु
		prev_bh = header_bh;
		get_bh(prev_bh);
	पूर्ण

	kaddr = kmap_atomic(next_bh->b_page);
	list = nilfs_cpfile_block_get_snapshot_list(
		cpfile, next, next_bh, kaddr);
	list->ssl_prev = cpu_to_le64(prev);
	kunmap_atomic(kaddr);

	kaddr = kmap_atomic(prev_bh->b_page);
	list = nilfs_cpfile_block_get_snapshot_list(
		cpfile, prev, prev_bh, kaddr);
	list->ssl_next = cpu_to_le64(next);
	kunmap_atomic(kaddr);

	kaddr = kmap_atomic(cp_bh->b_page);
	cp = nilfs_cpfile_block_get_checkpoपूर्णांक(cpfile, cno, cp_bh, kaddr);
	cp->cp_snapshot_list.ssl_next = cpu_to_le64(0);
	cp->cp_snapshot_list.ssl_prev = cpu_to_le64(0);
	nilfs_checkpoपूर्णांक_clear_snapshot(cp);
	kunmap_atomic(kaddr);

	kaddr = kmap_atomic(header_bh->b_page);
	header = nilfs_cpfile_block_get_header(cpfile, header_bh, kaddr);
	le64_add_cpu(&header->ch_nsnapshots, -1);
	kunmap_atomic(kaddr);

	mark_buffer_dirty(next_bh);
	mark_buffer_dirty(prev_bh);
	mark_buffer_dirty(cp_bh);
	mark_buffer_dirty(header_bh);
	nilfs_mdt_mark_dirty(cpfile);

	brअन्यथा(prev_bh);

 out_next:
	brअन्यथा(next_bh);

 out_header:
	brअन्यथा(header_bh);

 out_cp:
	brअन्यथा(cp_bh);

 out_sem:
	up_ग_लिखो(&NILFS_MDT(cpfile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_cpfile_is_snapshot -
 * @cpfile: inode of checkpoपूर्णांक file
 * @cno: checkpoपूर्णांक number
 *
 * Description:
 *
 * Return Value: On success, 1 is वापसed अगर the checkpoपूर्णांक specअगरied by
 * @cno is a snapshot, or 0 अगर not. On error, one of the following negative
 * error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - No such checkpoपूर्णांक.
 */
पूर्णांक nilfs_cpfile_is_snapshot(काष्ठा inode *cpfile, __u64 cno)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_checkpoपूर्णांक *cp;
	व्योम *kaddr;
	पूर्णांक ret;

	/*
	 * CP number is invalid अगर it's zero or larger than the
	 * largest existing one.
	 */
	अगर (cno == 0 || cno >= nilfs_mdt_cno(cpfile))
		वापस -ENOENT;
	करोwn_पढ़ो(&NILFS_MDT(cpfile)->mi_sem);

	ret = nilfs_cpfile_get_checkpoपूर्णांक_block(cpfile, cno, 0, &bh);
	अगर (ret < 0)
		जाओ out;
	kaddr = kmap_atomic(bh->b_page);
	cp = nilfs_cpfile_block_get_checkpoपूर्णांक(cpfile, cno, bh, kaddr);
	अगर (nilfs_checkpoपूर्णांक_invalid(cp))
		ret = -ENOENT;
	अन्यथा
		ret = nilfs_checkpoपूर्णांक_snapshot(cp);
	kunmap_atomic(kaddr);
	brअन्यथा(bh);

 out:
	up_पढ़ो(&NILFS_MDT(cpfile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_cpfile_change_cpmode - change checkpoपूर्णांक mode
 * @cpfile: inode of checkpoपूर्णांक file
 * @cno: checkpoपूर्णांक number
 * @mode: mode of checkpoपूर्णांक
 *
 * Description: nilfs_change_cpmode() changes the mode of the checkpoपूर्णांक
 * specअगरied by @cno. The mode @mode is NILFS_CHECKPOINT or NILFS_SNAPSHOT.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-ENOENT - No such checkpoपूर्णांक.
 */
पूर्णांक nilfs_cpfile_change_cpmode(काष्ठा inode *cpfile, __u64 cno, पूर्णांक mode)
अणु
	पूर्णांक ret;

	चयन (mode) अणु
	हाल NILFS_CHECKPOINT:
		अगर (nilfs_checkpoपूर्णांक_is_mounted(cpfile->i_sb, cno))
			/*
			 * Current implementation करोes not have to protect
			 * plain पढ़ो-only mounts since they are exclusive
			 * with a पढ़ो/ग_लिखो mount and are रक्षित from the
			 * cleaner.
			 */
			ret = -EBUSY;
		अन्यथा
			ret = nilfs_cpfile_clear_snapshot(cpfile, cno);
		वापस ret;
	हाल NILFS_SNAPSHOT:
		वापस nilfs_cpfile_set_snapshot(cpfile, cno);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * nilfs_cpfile_get_stat - get checkpoपूर्णांक statistics
 * @cpfile: inode of checkpoपूर्णांक file
 * @cpstat: poपूर्णांकer to a काष्ठाure of checkpoपूर्णांक statistics
 *
 * Description: nilfs_cpfile_get_stat() वापसs inक्रमmation about checkpoपूर्णांकs.
 *
 * Return Value: On success, 0 is वापसed, and checkpoपूर्णांकs inक्रमmation is
 * stored in the place poपूर्णांकed by @cpstat. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 */
पूर्णांक nilfs_cpfile_get_stat(काष्ठा inode *cpfile, काष्ठा nilfs_cpstat *cpstat)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा nilfs_cpfile_header *header;
	व्योम *kaddr;
	पूर्णांक ret;

	करोwn_पढ़ो(&NILFS_MDT(cpfile)->mi_sem);

	ret = nilfs_cpfile_get_header_block(cpfile, &bh);
	अगर (ret < 0)
		जाओ out_sem;
	kaddr = kmap_atomic(bh->b_page);
	header = nilfs_cpfile_block_get_header(cpfile, bh, kaddr);
	cpstat->cs_cno = nilfs_mdt_cno(cpfile);
	cpstat->cs_ncps = le64_to_cpu(header->ch_ncheckpoपूर्णांकs);
	cpstat->cs_nsss = le64_to_cpu(header->ch_nsnapshots);
	kunmap_atomic(kaddr);
	brअन्यथा(bh);

 out_sem:
	up_पढ़ो(&NILFS_MDT(cpfile)->mi_sem);
	वापस ret;
पूर्ण

/**
 * nilfs_cpfile_पढ़ो - पढ़ो or get cpfile inode
 * @sb: super block instance
 * @cpsize: size of a checkpoपूर्णांक entry
 * @raw_inode: on-disk cpfile inode
 * @inodep: buffer to store the inode
 */
पूर्णांक nilfs_cpfile_पढ़ो(काष्ठा super_block *sb, माप_प्रकार cpsize,
		      काष्ठा nilfs_inode *raw_inode, काष्ठा inode **inodep)
अणु
	काष्ठा inode *cpfile;
	पूर्णांक err;

	अगर (cpsize > sb->s_blocksize) अणु
		nilfs_err(sb, "too large checkpoint size: %zu bytes", cpsize);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (cpsize < NILFS_MIN_CHECKPOINT_SIZE) अणु
		nilfs_err(sb, "too small checkpoint size: %zu bytes", cpsize);
		वापस -EINVAL;
	पूर्ण

	cpfile = nilfs_iget_locked(sb, शून्य, NILFS_CPखाता_INO);
	अगर (unlikely(!cpfile))
		वापस -ENOMEM;
	अगर (!(cpfile->i_state & I_NEW))
		जाओ out;

	err = nilfs_mdt_init(cpfile, NILFS_MDT_GFP, 0);
	अगर (err)
		जाओ failed;

	nilfs_mdt_set_entry_size(cpfile, cpsize,
				 माप(काष्ठा nilfs_cpfile_header));

	err = nilfs_पढ़ो_inode_common(cpfile, raw_inode);
	अगर (err)
		जाओ failed;

	unlock_new_inode(cpfile);
 out:
	*inodep = cpfile;
	वापस 0;
 failed:
	iget_failed(cpfile);
	वापस err;
पूर्ण
