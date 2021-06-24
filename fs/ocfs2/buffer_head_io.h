<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ocfs2_buffer_head.h
 *
 * Buffer cache handling functions defined
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_BUFFER_HEAD_IO_H
#घोषणा OCFS2_BUFFER_HEAD_IO_H

#समावेश <linux/buffer_head.h>

पूर्णांक ocfs2_ग_लिखो_block(काष्ठा ocfs2_super          *osb,
		      काष्ठा buffer_head  *bh,
		      काष्ठा ocfs2_caching_info   *ci);
पूर्णांक ocfs2_पढ़ो_blocks_sync(काष्ठा ocfs2_super *osb, u64 block,
			   अचिन्हित पूर्णांक nr, काष्ठा buffer_head *bhs[]);

/*
 * If not शून्य, validate() will be called on a buffer that is freshly
 * पढ़ो from disk.  It will not be called अगर the buffer was in cache.
 * Note that अगर validate() is being used क्रम this buffer, it needs to
 * be set even क्रम a READAHEAD call, as it marks the buffer क्रम later
 * validation.
 */
पूर्णांक ocfs2_पढ़ो_blocks(काष्ठा ocfs2_caching_info *ci, u64 block, पूर्णांक nr,
		      काष्ठा buffer_head *bhs[], पूर्णांक flags,
		      पूर्णांक (*validate)(काष्ठा super_block *sb,
				      काष्ठा buffer_head *bh));

पूर्णांक ocfs2_ग_लिखो_super_or_backup(काष्ठा ocfs2_super *osb,
				काष्ठा buffer_head *bh);

#घोषणा OCFS2_BH_IGNORE_CACHE      1
#घोषणा OCFS2_BH_READAHEAD         8

अटल अंतरभूत पूर्णांक ocfs2_पढ़ो_block(काष्ठा ocfs2_caching_info *ci, u64 off,
				   काष्ठा buffer_head **bh,
				   पूर्णांक (*validate)(काष्ठा super_block *sb,
						   काष्ठा buffer_head *bh))
अणु
	पूर्णांक status = 0;

	अगर (bh == शून्य) अणु
		prपूर्णांकk("ocfs2: bh == NULL\n");
		status = -EINVAL;
		जाओ bail;
	पूर्ण

	status = ocfs2_पढ़ो_blocks(ci, off, 1, bh, 0, validate);

bail:
	वापस status;
पूर्ण

#पूर्ण_अगर /* OCFS2_BUFFER_HEAD_IO_H */
