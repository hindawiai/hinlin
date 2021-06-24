<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * datastream.h
 *
 */

काष्ठा buffer_head *befs_पढ़ो_datastream(काष्ठा super_block *sb,
					 स्थिर befs_data_stream *ds,
					 befs_off_t pos, uपूर्णांक *off);

पूर्णांक befs_fblock2brun(काष्ठा super_block *sb, स्थिर befs_data_stream *data,
		     befs_blocknr_t fblock, befs_block_run *run);

माप_प्रकार befs_पढ़ो_lsymlink(काष्ठा super_block *sb, स्थिर befs_data_stream *data,
			  व्योम *buff, befs_off_t len);

befs_blocknr_t befs_count_blocks(काष्ठा super_block *sb,
			  स्थिर befs_data_stream *ds);

बाह्य स्थिर befs_inode_addr BAD_IADDR;
