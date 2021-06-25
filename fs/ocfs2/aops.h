<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2002, 2004, 2005 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_AOPS_H
#घोषणा OCFS2_AOPS_H

#समावेश <linux/fs.h>

handle_t *ocfs2_start_walk_page_trans(काष्ठा inode *inode,
							 काष्ठा page *page,
							 अचिन्हित from,
							 अचिन्हित to);

पूर्णांक ocfs2_map_page_blocks(काष्ठा page *page, u64 *p_blkno,
			  काष्ठा inode *inode, अचिन्हित पूर्णांक from,
			  अचिन्हित पूर्णांक to, पूर्णांक new);

व्योम ocfs2_unlock_and_मुक्त_pages(काष्ठा page **pages, पूर्णांक num_pages);

पूर्णांक walk_page_buffers(	handle_t *handle,
			काष्ठा buffer_head *head,
			अचिन्हित from,
			अचिन्हित to,
			पूर्णांक *partial,
			पूर्णांक (*fn)(	handle_t *handle,
					काष्ठा buffer_head *bh));

पूर्णांक ocfs2_ग_लिखो_end_nolock(काष्ठा address_space *mapping,
			   loff_t pos, अचिन्हित len, अचिन्हित copied, व्योम *fsdata);

प्रकार क्रमागत अणु
	OCFS2_WRITE_BUFFER = 0,
	OCFS2_WRITE_सूचीECT,
	OCFS2_WRITE_MMAP,
पूर्ण ocfs2_ग_लिखो_type_t;

पूर्णांक ocfs2_ग_लिखो_begin_nolock(काष्ठा address_space *mapping,
			     loff_t pos, अचिन्हित len, ocfs2_ग_लिखो_type_t type,
			     काष्ठा page **pagep, व्योम **fsdata,
			     काष्ठा buffer_head *di_bh, काष्ठा page *mmap_page);

पूर्णांक ocfs2_पढ़ो_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *page,
			   काष्ठा buffer_head *di_bh);
पूर्णांक ocfs2_size_fits_अंतरभूत_data(काष्ठा buffer_head *di_bh, u64 new_size);

पूर्णांक ocfs2_get_block(काष्ठा inode *inode, sector_t iblock,
		    काष्ठा buffer_head *bh_result, पूर्णांक create);
/* all ocfs2_dio_end_io()'s fault */
#घोषणा ocfs2_iocb_is_rw_locked(iocb) \
	test_bit(0, (अचिन्हित दीर्घ *)&iocb->निजी)
अटल अंतरभूत व्योम ocfs2_iocb_set_rw_locked(काष्ठा kiocb *iocb, पूर्णांक level)
अणु
	set_bit(0, (अचिन्हित दीर्घ *)&iocb->निजी);
	अगर (level)
		set_bit(1, (अचिन्हित दीर्घ *)&iocb->निजी);
	अन्यथा
		clear_bit(1, (अचिन्हित दीर्घ *)&iocb->निजी);
पूर्ण

/*
 * Using a named क्रमागत representing lock types in terms of #N bit stored in
 * iocb->निजी, which is going to be used क्रम communication between
 * ocfs2_dio_end_io() and ocfs2_file_ग_लिखो/पढ़ो_iter().
 */
क्रमागत ocfs2_iocb_lock_bits अणु
	OCFS2_IOCB_RW_LOCK = 0,
	OCFS2_IOCB_RW_LOCK_LEVEL,
	OCFS2_IOCB_NUM_LOCKS
पूर्ण;

#घोषणा ocfs2_iocb_clear_rw_locked(iocb) \
	clear_bit(OCFS2_IOCB_RW_LOCK, (अचिन्हित दीर्घ *)&iocb->निजी)
#घोषणा ocfs2_iocb_rw_locked_level(iocb) \
	test_bit(OCFS2_IOCB_RW_LOCK_LEVEL, (अचिन्हित दीर्घ *)&iocb->निजी)

#पूर्ण_अगर /* OCFS2_खाता_H */
