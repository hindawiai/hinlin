<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * sufile.h - NILFS segment usage file.
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#अगर_अघोषित _NILFS_SUखाता_H
#घोषणा _NILFS_SUखाता_H

#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश "mdt.h"


अटल अंतरभूत अचिन्हित दीर्घ nilfs_sufile_get_nsegments(काष्ठा inode *sufile)
अणु
	वापस ((काष्ठा the_nilfs *)sufile->i_sb->s_fs_info)->ns_nsegments;
पूर्ण

अचिन्हित दीर्घ nilfs_sufile_get_ncleansegs(काष्ठा inode *sufile);

पूर्णांक nilfs_sufile_set_alloc_range(काष्ठा inode *sufile, __u64 start, __u64 end);
पूर्णांक nilfs_sufile_alloc(काष्ठा inode *, __u64 *);
पूर्णांक nilfs_sufile_mark_dirty(काष्ठा inode *sufile, __u64 segnum);
पूर्णांक nilfs_sufile_set_segment_usage(काष्ठा inode *sufile, __u64 segnum,
				   अचिन्हित दीर्घ nblocks, समय64_t modसमय);
पूर्णांक nilfs_sufile_get_stat(काष्ठा inode *, काष्ठा nilfs_sustat *);
sमाप_प्रकार nilfs_sufile_get_suinfo(काष्ठा inode *, __u64, व्योम *, अचिन्हित पूर्णांक,
				माप_प्रकार);
sमाप_प्रकार nilfs_sufile_set_suinfo(काष्ठा inode *, व्योम *, अचिन्हित पूर्णांक, माप_प्रकार);

पूर्णांक nilfs_sufile_updatev(काष्ठा inode *, __u64 *, माप_प्रकार, पूर्णांक, माप_प्रकार *,
			 व्योम (*करोfunc)(काष्ठा inode *, __u64,
					काष्ठा buffer_head *,
					काष्ठा buffer_head *));
पूर्णांक nilfs_sufile_update(काष्ठा inode *, __u64, पूर्णांक,
			व्योम (*करोfunc)(काष्ठा inode *, __u64,
				       काष्ठा buffer_head *,
				       काष्ठा buffer_head *));
व्योम nilfs_sufile_करो_scrap(काष्ठा inode *, __u64, काष्ठा buffer_head *,
			   काष्ठा buffer_head *);
व्योम nilfs_sufile_करो_मुक्त(काष्ठा inode *, __u64, काष्ठा buffer_head *,
			  काष्ठा buffer_head *);
व्योम nilfs_sufile_करो_cancel_मुक्त(काष्ठा inode *, __u64, काष्ठा buffer_head *,
				 काष्ठा buffer_head *);
व्योम nilfs_sufile_करो_set_error(काष्ठा inode *, __u64, काष्ठा buffer_head *,
			       काष्ठा buffer_head *);

पूर्णांक nilfs_sufile_resize(काष्ठा inode *sufile, __u64 newnsegs);
पूर्णांक nilfs_sufile_पढ़ो(काष्ठा super_block *sb, माप_प्रकार susize,
		      काष्ठा nilfs_inode *raw_inode, काष्ठा inode **inodep);
पूर्णांक nilfs_sufile_trim_fs(काष्ठा inode *sufile, काष्ठा fstrim_range *range);

/**
 * nilfs_sufile_scrap - make a segment garbage
 * @sufile: inode of segment usage file
 * @segnum: segment number to be मुक्तd
 */
अटल अंतरभूत पूर्णांक nilfs_sufile_scrap(काष्ठा inode *sufile, __u64 segnum)
अणु
	वापस nilfs_sufile_update(sufile, segnum, 1, nilfs_sufile_करो_scrap);
पूर्ण

/**
 * nilfs_sufile_मुक्त - मुक्त segment
 * @sufile: inode of segment usage file
 * @segnum: segment number to be मुक्तd
 */
अटल अंतरभूत पूर्णांक nilfs_sufile_मुक्त(काष्ठा inode *sufile, __u64 segnum)
अणु
	वापस nilfs_sufile_update(sufile, segnum, 0, nilfs_sufile_करो_मुक्त);
पूर्ण

/**
 * nilfs_sufile_मुक्तv - मुक्त segments
 * @sufile: inode of segment usage file
 * @segnumv: array of segment numbers
 * @nsegs: size of @segnumv array
 * @nकरोne: place to store the number of मुक्तd segments
 */
अटल अंतरभूत पूर्णांक nilfs_sufile_मुक्तv(काष्ठा inode *sufile, __u64 *segnumv,
				     माप_प्रकार nsegs, माप_प्रकार *nकरोne)
अणु
	वापस nilfs_sufile_updatev(sufile, segnumv, nsegs, 0, nकरोne,
				    nilfs_sufile_करो_मुक्त);
पूर्ण

/**
 * nilfs_sufile_cancel_मुक्तv - पुनः_स्मृतिate मुक्तing segments
 * @sufile: inode of segment usage file
 * @segnumv: array of segment numbers
 * @nsegs: size of @segnumv array
 * @nकरोne: place to store the number of cancelled segments
 *
 * Return Value: On success, 0 is वापसed. On error, a negative error codes
 * is वापसed.
 */
अटल अंतरभूत पूर्णांक nilfs_sufile_cancel_मुक्तv(काष्ठा inode *sufile,
					    __u64 *segnumv, माप_प्रकार nsegs,
					    माप_प्रकार *nकरोne)
अणु
	वापस nilfs_sufile_updatev(sufile, segnumv, nsegs, 0, nकरोne,
				    nilfs_sufile_करो_cancel_मुक्त);
पूर्ण

/**
 * nilfs_sufile_set_error - mark a segment as erroneous
 * @sufile: inode of segment usage file
 * @segnum: segment number
 *
 * Description: nilfs_sufile_set_error() marks the segment specअगरied by
 * @segnum as erroneous. The error segment will never be used again.
 *
 * Return Value: On success, 0 is वापसed. On error, one of the following
 * negative error codes is वापसed.
 *
 * %-EIO - I/O error.
 *
 * %-ENOMEM - Insufficient amount of memory available.
 *
 * %-EINVAL - Invalid segment usage number.
 */
अटल अंतरभूत पूर्णांक nilfs_sufile_set_error(काष्ठा inode *sufile, __u64 segnum)
अणु
	वापस nilfs_sufile_update(sufile, segnum, 0,
				   nilfs_sufile_करो_set_error);
पूर्ण

#पूर्ण_अगर	/* _NILFS_SUखाता_H */
