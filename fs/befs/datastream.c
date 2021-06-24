<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/befs/datastream.c
 *
 * Copyright (C) 2001 Will Dyson <will_dyson@pobox.com>
 *
 * Based on portions of file.c by Makoto Kato <m_kato@ga2.so-net.ne.jp>
 *
 * Many thanks to Dominic Giampaolo, author of "Practical File System
 * Design with the Be File System", क्रम such a helpful book.
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/माला.स>

#समावेश "befs.h"
#समावेश "datastream.h"
#समावेश "io.h"

स्थिर befs_inode_addr BAD_IADDR = अणु 0, 0, 0 पूर्ण;

अटल पूर्णांक befs_find_brun_direct(काष्ठा super_block *sb,
				 स्थिर befs_data_stream *data,
				 befs_blocknr_t blockno, befs_block_run *run);

अटल पूर्णांक befs_find_brun_indirect(काष्ठा super_block *sb,
				   स्थिर befs_data_stream *data,
				   befs_blocknr_t blockno,
				   befs_block_run *run);

अटल पूर्णांक befs_find_brun_dblindirect(काष्ठा super_block *sb,
				      स्थिर befs_data_stream *data,
				      befs_blocknr_t blockno,
				      befs_block_run *run);

/**
 * befs_पढ़ो_datastream - get buffer_head containing data, starting from pos.
 * @sb: Fileप्रणाली superblock
 * @ds: datastream to find data with
 * @pos: start of data
 * @off: offset of data in buffer_head->b_data
 *
 * Returns poपूर्णांकer to buffer_head containing data starting with offset @off,
 * अगर you करोn't need to know offset just set @off = शून्य.
 */
काष्ठा buffer_head *
befs_पढ़ो_datastream(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
		     befs_off_t pos, uपूर्णांक *off)
अणु
	काष्ठा buffer_head *bh;
	befs_block_run run;
	befs_blocknr_t block;	/* block coresponding to pos */

	befs_debug(sb, "---> %s %llu", __func__, pos);
	block = pos >> BEFS_SB(sb)->block_shअगरt;
	अगर (off)
		*off = pos - (block << BEFS_SB(sb)->block_shअगरt);

	अगर (befs_fblock2brun(sb, ds, block, &run) != BEFS_OK) अणु
		befs_error(sb, "BeFS: Error finding disk addr of block %lu",
			   (अचिन्हित दीर्घ)block);
		befs_debug(sb, "<--- %s ERROR", __func__);
		वापस शून्य;
	पूर्ण
	bh = befs_bपढ़ो_iaddr(sb, run);
	अगर (!bh) अणु
		befs_error(sb, "BeFS: Error reading block %lu from datastream",
			   (अचिन्हित दीर्घ)block);
		वापस शून्य;
	पूर्ण

	befs_debug(sb, "<--- %s read data, starting at %llu", __func__, pos);

	वापस bh;
पूर्ण

/**
 * befs_fblock2brun - give back block run क्रम fblock
 * @sb: the superblock
 * @data: datastream to पढ़ो from
 * @fblock: the blocknumber with the file position to find
 * @run: The found run is passed back through this poपूर्णांकer
 *
 * Takes a file position and gives back a brun who's starting block
 * is block number fblock of the file.
 *
 * Returns BEFS_OK or BEFS_ERR.
 *
 * Calls specialized functions क्रम each of the three possible
 * datastream regions.
 */
पूर्णांक
befs_fblock2brun(काष्ठा super_block *sb, स्थिर befs_data_stream *data,
		 befs_blocknr_t fblock, befs_block_run *run)
अणु
	पूर्णांक err;
	befs_off_t pos = fblock << BEFS_SB(sb)->block_shअगरt;

	अगर (pos < data->max_direct_range) अणु
		err = befs_find_brun_direct(sb, data, fblock, run);

	पूर्ण अन्यथा अगर (pos < data->max_indirect_range) अणु
		err = befs_find_brun_indirect(sb, data, fblock, run);

	पूर्ण अन्यथा अगर (pos < data->max_द्विगुन_indirect_range) अणु
		err = befs_find_brun_dblindirect(sb, data, fblock, run);

	पूर्ण अन्यथा अणु
		befs_error(sb,
			   "befs_fblock2brun() was asked to find block %lu, "
			   "which is not mapped by the datastream\n",
			   (अचिन्हित दीर्घ)fblock);
		err = BEFS_ERR;
	पूर्ण
	वापस err;
पूर्ण

/**
 * befs_पढ़ो_lsmylink - पढ़ो दीर्घ symlink from datastream.
 * @sb: Fileप्रणाली superblock
 * @ds: Datastream to पढ़ो from
 * @buff: Buffer in which to place दीर्घ symlink data
 * @len: Length of the दीर्घ symlink in bytes
 *
 * Returns the number of bytes पढ़ो
 */
माप_प्रकार
befs_पढ़ो_lsymlink(काष्ठा super_block *sb, स्थिर befs_data_stream *ds,
		   व्योम *buff, befs_off_t len)
अणु
	befs_off_t bytes_पढ़ो = 0;	/* bytes पढ़ोed */
	u16 plen;
	काष्ठा buffer_head *bh;

	befs_debug(sb, "---> %s length: %llu", __func__, len);

	जबतक (bytes_पढ़ो < len) अणु
		bh = befs_पढ़ो_datastream(sb, ds, bytes_पढ़ो, शून्य);
		अगर (!bh) अणु
			befs_error(sb, "BeFS: Error reading datastream block "
				   "starting from %llu", bytes_पढ़ो);
			befs_debug(sb, "<--- %s ERROR", __func__);
			वापस bytes_पढ़ो;

		पूर्ण
		plen = ((bytes_पढ़ो + BEFS_SB(sb)->block_size) < len) ?
		    BEFS_SB(sb)->block_size : len - bytes_पढ़ो;
		स_नकल(buff + bytes_पढ़ो, bh->b_data, plen);
		brअन्यथा(bh);
		bytes_पढ़ो += plen;
	पूर्ण

	befs_debug(sb, "<--- %s read %u bytes", __func__, (अचिन्हित पूर्णांक)
		   bytes_पढ़ो);
	वापस bytes_पढ़ो;
पूर्ण

/**
 * befs_count_blocks - blocks used by a file
 * @sb: Fileप्रणाली superblock
 * @ds: Datastream of the file
 *
 * Counts the number of fs blocks that the file represented by
 * inode occupies on the fileप्रणाली, counting both regular file
 * data and fileप्रणाली metadata (and eventually attribute data
 * when we support attributes)
*/

befs_blocknr_t
befs_count_blocks(काष्ठा super_block *sb, स्थिर befs_data_stream *ds)
अणु
	befs_blocknr_t blocks;
	befs_blocknr_t datablocks;	/* File data blocks */
	befs_blocknr_t metablocks;	/* FS metadata blocks */
	काष्ठा befs_sb_info *befs_sb = BEFS_SB(sb);

	befs_debug(sb, "---> %s", __func__);

	datablocks = ds->size >> befs_sb->block_shअगरt;
	अगर (ds->size & (befs_sb->block_size - 1))
		datablocks += 1;

	metablocks = 1;		/* Start with 1 block क्रम inode */

	/* Size of indirect block */
	अगर (ds->size > ds->max_direct_range)
		metablocks += ds->indirect.len;

	/*
	 * Double indir block, plus all the indirect blocks it maps.
	 * In the द्विगुन-indirect range, all block runs of data are
	 * BEFS_DBLINसूची_BRUN_LEN blocks दीर्घ. Thereक्रमe, we know
	 * how many data block runs are in the द्विगुन-indirect region,
	 * and from that we know how many indirect blocks it takes to
	 * map them. We assume that the indirect blocks are also
	 * BEFS_DBLINसूची_BRUN_LEN blocks दीर्घ.
	 */
	अगर (ds->size > ds->max_indirect_range && ds->max_indirect_range != 0) अणु
		uपूर्णांक dbl_bytes;
		uपूर्णांक dbl_bruns;
		uपूर्णांक indirblocks;

		dbl_bytes =
		    ds->max_द्विगुन_indirect_range - ds->max_indirect_range;
		dbl_bruns =
		    dbl_bytes / (befs_sb->block_size * BEFS_DBLINसूची_BRUN_LEN);
		indirblocks = dbl_bruns / befs_iaddrs_per_block(sb);

		metablocks += ds->द्विगुन_indirect.len;
		metablocks += indirblocks;
	पूर्ण

	blocks = datablocks + metablocks;
	befs_debug(sb, "<--- %s %u blocks", __func__, (अचिन्हित पूर्णांक)blocks);

	वापस blocks;
पूर्ण

/**
 * befs_find_brun_direct - find a direct block run in the datastream
 * @sb: the superblock
 * @data: the datastream
 * @blockno: the blocknumber to find
 * @run: The found run is passed back through this poपूर्णांकer
 *
 * Finds the block run that starts at file block number blockno
 * in the file represented by the datastream data, अगर that
 * blockno is in the direct region of the datastream.
 *
 * Return value is BEFS_OK अगर the blockrun is found, BEFS_ERR
 * otherwise.
 *
 * Algorithm:
 * Linear search. Checks each element of array[] to see अगर it
 * contains the blockno-th fileप्रणाली block. This is necessary
 * because the block runs map variable amounts of data. Simply
 * keeps a count of the number of blocks searched so far (sum),
 * incrementing this by the length of each block run as we come
 * across it. Adds sum to *count beक्रमe वापसing (this is so
 * you can search multiple arrays that are logicaly one array,
 * as in the indirect region code).
 *
 * When/अगर blockno is found, अगर blockno is inside of a block
 * run as stored on disk, we offset the start and length members
 * of the block run, so that blockno is the start and len is
 * still valid (the run ends in the same place).
 */
अटल पूर्णांक
befs_find_brun_direct(काष्ठा super_block *sb, स्थिर befs_data_stream *data,
		      befs_blocknr_t blockno, befs_block_run *run)
अणु
	पूर्णांक i;
	स्थिर befs_block_run *array = data->direct;
	befs_blocknr_t sum;

	befs_debug(sb, "---> %s, find %lu", __func__, (अचिन्हित दीर्घ)blockno);

	क्रम (i = 0, sum = 0; i < BEFS_NUM_सूचीECT_BLOCKS;
	     sum += array[i].len, i++) अणु
		अगर (blockno >= sum && blockno < sum + (array[i].len)) अणु
			पूर्णांक offset = blockno - sum;

			run->allocation_group = array[i].allocation_group;
			run->start = array[i].start + offset;
			run->len = array[i].len - offset;

			befs_debug(sb, "---> %s, "
				   "found %lu at direct[%d]", __func__,
				   (अचिन्हित दीर्घ)blockno, i);
			वापस BEFS_OK;
		पूर्ण
	पूर्ण

	befs_error(sb, "%s failed to find file block %lu", __func__,
		   (अचिन्हित दीर्घ)blockno);
	befs_debug(sb, "---> %s ERROR", __func__);
	वापस BEFS_ERR;
पूर्ण

/**
 * befs_find_brun_indirect - find a block run in the datastream
 * @sb: the superblock
 * @data: the datastream
 * @blockno: the blocknumber to find
 * @run: The found run is passed back through this poपूर्णांकer
 *
 * Finds the block run that starts at file block number blockno
 * in the file represented by the datastream data, अगर that
 * blockno is in the indirect region of the datastream.
 *
 * Return value is BEFS_OK अगर the blockrun is found, BEFS_ERR
 * otherwise.
 *
 * Algorithm:
 * For each block in the indirect run of the datastream, पढ़ो
 * it in and search through it क्रम search_blk.
 *
 * XXX:
 * Really should check to make sure blockno is inside indirect
 * region.
 */
अटल पूर्णांक
befs_find_brun_indirect(काष्ठा super_block *sb,
			स्थिर befs_data_stream *data,
			befs_blocknr_t blockno,
			befs_block_run *run)
अणु
	पूर्णांक i, j;
	befs_blocknr_t sum = 0;
	befs_blocknr_t indir_start_blk;
	befs_blocknr_t search_blk;
	काष्ठा buffer_head *indirblock;
	befs_disk_block_run *array;

	befs_block_run indirect = data->indirect;
	befs_blocknr_t indirblockno = iaddr2blockno(sb, &indirect);
	पूर्णांक arraylen = befs_iaddrs_per_block(sb);

	befs_debug(sb, "---> %s, find %lu", __func__, (अचिन्हित दीर्घ)blockno);

	indir_start_blk = data->max_direct_range >> BEFS_SB(sb)->block_shअगरt;
	search_blk = blockno - indir_start_blk;

	/* Examine blocks of the indirect run one at a समय */
	क्रम (i = 0; i < indirect.len; i++) अणु
		indirblock = sb_bपढ़ो(sb, indirblockno + i);
		अगर (indirblock == शून्य) अणु
			befs_error(sb, "---> %s failed to read "
				   "disk block %lu from the indirect brun",
				   __func__, (अचिन्हित दीर्घ)indirblockno + i);
			befs_debug(sb, "<--- %s ERROR", __func__);
			वापस BEFS_ERR;
		पूर्ण

		array = (befs_disk_block_run *) indirblock->b_data;

		क्रम (j = 0; j < arraylen; ++j) अणु
			पूर्णांक len = fs16_to_cpu(sb, array[j].len);

			अगर (search_blk >= sum && search_blk < sum + len) अणु
				पूर्णांक offset = search_blk - sum;
				run->allocation_group =
				    fs32_to_cpu(sb, array[j].allocation_group);
				run->start =
				    fs16_to_cpu(sb, array[j].start) + offset;
				run->len =
				    fs16_to_cpu(sb, array[j].len) - offset;

				brअन्यथा(indirblock);
				befs_debug(sb,
					   "<--- %s found file block "
					   "%lu at indirect[%d]", __func__,
					   (अचिन्हित दीर्घ)blockno,
					   j + (i * arraylen));
				वापस BEFS_OK;
			पूर्ण
			sum += len;
		पूर्ण

		brअन्यथा(indirblock);
	पूर्ण

	/* Only fallthrough is an error */
	befs_error(sb, "BeFS: %s failed to find "
		   "file block %lu", __func__, (अचिन्हित दीर्घ)blockno);

	befs_debug(sb, "<--- %s ERROR", __func__);
	वापस BEFS_ERR;
पूर्ण

/**
 * befs_find_brun_dblindirect - find a block run in the datastream
 * @sb: the superblock
 * @data: the datastream
 * @blockno: the blocknumber to find
 * @run: The found run is passed back through this poपूर्णांकer
 *
 * Finds the block run that starts at file block number blockno
 * in the file represented by the datastream data, अगर that
 * blockno is in the द्विगुन-indirect region of the datastream.
 *
 * Return value is BEFS_OK अगर the blockrun is found, BEFS_ERR
 * otherwise.
 *
 * Algorithm:
 * The block runs in the द्विगुन-indirect region are dअगरferent.
 * They are always allocated 4 fs blocks at a समय, so each
 * block run maps a स्थिरant amount of file data. This means
 * that we can directly calculate how many block runs पूर्णांकo the
 * द्विगुन-indirect region we need to go to get to the one that
 * maps a particular fileप्रणाली block.
 *
 * We करो this in two stages. First we calculate which of the
 * inode addresses in the द्विगुन-indirect block will poपूर्णांक us
 * to the indirect block that contains the mapping क्रम the data,
 * then we calculate which of the inode addresses in that
 * indirect block maps the data block we are after.
 *
 * Oh, and once we've करोne that, we actually पढ़ो in the blocks
 * that contain the inode addresses we calculated above. Even
 * though the द्विगुन-indirect run may be several blocks दीर्घ,
 * we can calculate which of those blocks will contain the index
 * we are after and only पढ़ो that one. We then follow it to
 * the indirect block and perक्रमm a similar process to find
 * the actual block run that maps the data block we are पूर्णांकerested
 * in.
 *
 * Then we offset the run as in befs_find_brun_array() and we are
 * करोne.
 */
अटल पूर्णांक
befs_find_brun_dblindirect(काष्ठा super_block *sb,
			   स्थिर befs_data_stream *data,
			   befs_blocknr_t blockno,
			   befs_block_run *run)
अणु
	पूर्णांक dblindir_indx;
	पूर्णांक indir_indx;
	पूर्णांक offset;
	पूर्णांक dbl_which_block;
	पूर्णांक which_block;
	पूर्णांक dbl_block_indx;
	पूर्णांक block_indx;
	off_t dblindir_leftover;
	befs_blocknr_t blockno_at_run_start;
	काष्ठा buffer_head *dbl_indir_block;
	काष्ठा buffer_head *indir_block;
	befs_block_run indir_run;
	befs_disk_inode_addr *iaddr_array;

	befs_blocknr_t indir_start_blk =
	    data->max_indirect_range >> BEFS_SB(sb)->block_shअगरt;

	off_t dbl_indir_off = blockno - indir_start_blk;

	/* number of data blocks mapped by each of the iaddrs in
	 * the indirect block poपूर्णांकed to by the द्विगुन indirect block
	 */
	माप_प्रकार iblklen = BEFS_DBLINसूची_BRUN_LEN;

	/* number of data blocks mapped by each of the iaddrs in
	 * the द्विगुन indirect block
	 */
	माप_प्रकार diblklen = iblklen * befs_iaddrs_per_block(sb)
	    * BEFS_DBLINसूची_BRUN_LEN;

	befs_debug(sb, "---> %s find %lu", __func__, (अचिन्हित दीर्घ)blockno);

	/* First, discover which of the द्विगुन_indir->indir blocks
	 * contains pos. Then figure out how much of pos that
	 * accounted क्रम. Then discover which of the iaddrs in
	 * the indirect block contains pos.
	 */

	dblindir_indx = dbl_indir_off / diblklen;
	dblindir_leftover = dbl_indir_off % diblklen;
	indir_indx = dblindir_leftover / diblklen;

	/* Read द्विगुन indirect block */
	dbl_which_block = dblindir_indx / befs_iaddrs_per_block(sb);
	अगर (dbl_which_block > data->द्विगुन_indirect.len) अणु
		befs_error(sb, "The double-indirect index calculated by "
			   "%s, %d, is outside the range "
			   "of the double-indirect block", __func__,
			   dblindir_indx);
		वापस BEFS_ERR;
	पूर्ण

	dbl_indir_block =
	    sb_bपढ़ो(sb, iaddr2blockno(sb, &data->द्विगुन_indirect) +
					dbl_which_block);
	अगर (dbl_indir_block == शून्य) अणु
		befs_error(sb, "%s couldn't read the "
			   "double-indirect block at blockno %lu", __func__,
			   (अचिन्हित दीर्घ)
			   iaddr2blockno(sb, &data->द्विगुन_indirect) +
			   dbl_which_block);
		वापस BEFS_ERR;
	पूर्ण

	dbl_block_indx =
	    dblindir_indx - (dbl_which_block * befs_iaddrs_per_block(sb));
	iaddr_array = (befs_disk_inode_addr *) dbl_indir_block->b_data;
	indir_run = fsrun_to_cpu(sb, iaddr_array[dbl_block_indx]);
	brअन्यथा(dbl_indir_block);

	/* Read indirect block */
	which_block = indir_indx / befs_iaddrs_per_block(sb);
	अगर (which_block > indir_run.len) अणु
		befs_error(sb, "The indirect index calculated by "
			   "%s, %d, is outside the range "
			   "of the indirect block", __func__, indir_indx);
		वापस BEFS_ERR;
	पूर्ण

	indir_block =
	    sb_bपढ़ो(sb, iaddr2blockno(sb, &indir_run) + which_block);
	अगर (indir_block == शून्य) अणु
		befs_error(sb, "%s couldn't read the indirect block "
			   "at blockno %lu", __func__, (अचिन्हित दीर्घ)
			   iaddr2blockno(sb, &indir_run) + which_block);
		वापस BEFS_ERR;
	पूर्ण

	block_indx = indir_indx - (which_block * befs_iaddrs_per_block(sb));
	iaddr_array = (befs_disk_inode_addr *) indir_block->b_data;
	*run = fsrun_to_cpu(sb, iaddr_array[block_indx]);
	brअन्यथा(indir_block);

	blockno_at_run_start = indir_start_blk;
	blockno_at_run_start += diblklen * dblindir_indx;
	blockno_at_run_start += iblklen * indir_indx;
	offset = blockno - blockno_at_run_start;

	run->start += offset;
	run->len -= offset;

	befs_debug(sb, "Found file block %lu in double_indirect[%d][%d],"
		   " double_indirect_leftover = %lu", (अचिन्हित दीर्घ)
		   blockno, dblindir_indx, indir_indx, dblindir_leftover);

	वापस BEFS_OK;
पूर्ण
