<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ufs/util.c
 *
 * Copyright (C) 1998
 * Daniel Pirkl <daniel.pirkl@email.cz>
 * Charles University, Faculty of Mathematics and Physics
 */
 
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/buffer_head.h>

#समावेश "ufs_fs.h"
#समावेश "ufs.h"
#समावेश "swab.h"
#समावेश "util.h"

काष्ठा ufs_buffer_head * _ubh_bपढ़ो_ (काष्ठा ufs_sb_निजी_info * uspi,
	काष्ठा super_block *sb, u64 fragment, u64 size)
अणु
	काष्ठा ufs_buffer_head * ubh;
	अचिन्हित i, j ;
	u64  count = 0;
	अगर (size & ~uspi->s_fmask)
		वापस शून्य;
	count = size >> uspi->s_fshअगरt;
	अगर (count > UFS_MAXFRAG)
		वापस शून्य;
	ubh = kदो_स्मृति (माप (काष्ठा ufs_buffer_head), GFP_NOFS);
	अगर (!ubh)
		वापस शून्य;
	ubh->fragment = fragment;
	ubh->count = count;
	क्रम (i = 0; i < count; i++)
		अगर (!(ubh->bh[i] = sb_bपढ़ो(sb, fragment + i)))
			जाओ failed;
	क्रम (; i < UFS_MAXFRAG; i++)
		ubh->bh[i] = शून्य;
	वापस ubh;
failed:
	क्रम (j = 0; j < i; j++)
		brअन्यथा (ubh->bh[j]);
	kमुक्त(ubh);
	वापस शून्य;
पूर्ण

काष्ठा ufs_buffer_head * ubh_bपढ़ो_uspi (काष्ठा ufs_sb_निजी_info * uspi,
	काष्ठा super_block *sb, u64 fragment, u64 size)
अणु
	अचिन्हित i, j;
	u64 count = 0;
	अगर (size & ~uspi->s_fmask)
		वापस शून्य;
	count = size >> uspi->s_fshअगरt;
	अगर (count <= 0 || count > UFS_MAXFRAG)
		वापस शून्य;
	USPI_UBH(uspi)->fragment = fragment;
	USPI_UBH(uspi)->count = count;
	क्रम (i = 0; i < count; i++)
		अगर (!(USPI_UBH(uspi)->bh[i] = sb_bपढ़ो(sb, fragment + i)))
			जाओ failed;
	क्रम (; i < UFS_MAXFRAG; i++)
		USPI_UBH(uspi)->bh[i] = शून्य;
	वापस USPI_UBH(uspi);
failed:
	क्रम (j = 0; j < i; j++)
		brअन्यथा (USPI_UBH(uspi)->bh[j]);
	वापस शून्य;
पूर्ण

व्योम ubh_brअन्यथा (काष्ठा ufs_buffer_head * ubh)
अणु
	अचिन्हित i;
	अगर (!ubh)
		वापस;
	क्रम (i = 0; i < ubh->count; i++)
		brअन्यथा (ubh->bh[i]);
	kमुक्त (ubh);
पूर्ण

व्योम ubh_brअन्यथा_uspi (काष्ठा ufs_sb_निजी_info * uspi)
अणु
	अचिन्हित i;
	अगर (!USPI_UBH(uspi))
		वापस;
	क्रम ( i = 0; i < USPI_UBH(uspi)->count; i++ ) अणु
		brअन्यथा (USPI_UBH(uspi)->bh[i]);
		USPI_UBH(uspi)->bh[i] = शून्य;
	पूर्ण
पूर्ण

व्योम ubh_mark_buffer_dirty (काष्ठा ufs_buffer_head * ubh)
अणु
	अचिन्हित i;
	अगर (!ubh)
		वापस;
	क्रम ( i = 0; i < ubh->count; i++ )
		mark_buffer_dirty (ubh->bh[i]);
पूर्ण

व्योम ubh_mark_buffer_uptodate (काष्ठा ufs_buffer_head * ubh, पूर्णांक flag)
अणु
	अचिन्हित i;
	अगर (!ubh)
		वापस;
	अगर (flag) अणु
		क्रम ( i = 0; i < ubh->count; i++ )
			set_buffer_uptodate (ubh->bh[i]);
	पूर्ण अन्यथा अणु
		क्रम ( i = 0; i < ubh->count; i++ )
			clear_buffer_uptodate (ubh->bh[i]);
	पूर्ण
पूर्ण

व्योम ubh_sync_block(काष्ठा ufs_buffer_head *ubh)
अणु
	अगर (ubh) अणु
		अचिन्हित i;

		क्रम (i = 0; i < ubh->count; i++)
			ग_लिखो_dirty_buffer(ubh->bh[i], 0);

		क्रम (i = 0; i < ubh->count; i++)
			रुको_on_buffer(ubh->bh[i]);
	पूर्ण
पूर्ण

व्योम ubh_bक्रमget (काष्ठा ufs_buffer_head * ubh)
अणु
	अचिन्हित i;
	अगर (!ubh) 
		वापस;
	क्रम ( i = 0; i < ubh->count; i++ ) अगर ( ubh->bh[i] ) 
		bक्रमget (ubh->bh[i]);
पूर्ण
 
पूर्णांक ubh_buffer_dirty (काष्ठा ufs_buffer_head * ubh)
अणु
	अचिन्हित i;
	अचिन्हित result = 0;
	अगर (!ubh)
		वापस 0;
	क्रम ( i = 0; i < ubh->count; i++ )
		result |= buffer_dirty(ubh->bh[i]);
	वापस result;
पूर्ण

व्योम _ubh_ubhcpymem_(काष्ठा ufs_sb_निजी_info * uspi, 
	अचिन्हित अक्षर * mem, काष्ठा ufs_buffer_head * ubh, अचिन्हित size)
अणु
	अचिन्हित len, bhno;
	अगर (size > (ubh->count << uspi->s_fshअगरt))
		size = ubh->count << uspi->s_fshअगरt;
	bhno = 0;
	जबतक (size) अणु
		len = min_t(अचिन्हित पूर्णांक, size, uspi->s_fsize);
		स_नकल (mem, ubh->bh[bhno]->b_data, len);
		mem += uspi->s_fsize;
		size -= len;
		bhno++;
	पूर्ण
पूर्ण

व्योम _ubh_स_नकलubh_(काष्ठा ufs_sb_निजी_info * uspi, 
	काष्ठा ufs_buffer_head * ubh, अचिन्हित अक्षर * mem, अचिन्हित size)
अणु
	अचिन्हित len, bhno;
	अगर (size > (ubh->count << uspi->s_fshअगरt))
		size = ubh->count << uspi->s_fshअगरt;
	bhno = 0;
	जबतक (size) अणु
		len = min_t(अचिन्हित पूर्णांक, size, uspi->s_fsize);
		स_नकल (ubh->bh[bhno]->b_data, mem, len);
		mem += uspi->s_fsize;
		size -= len;
		bhno++;
	पूर्ण
पूर्ण

dev_t
ufs_get_inode_dev(काष्ठा super_block *sb, काष्ठा ufs_inode_info *ufsi)
अणु
	__u32 fs32;
	dev_t dev;

	अगर ((UFS_SB(sb)->s_flags & UFS_ST_MASK) == UFS_ST_SUNx86)
		fs32 = fs32_to_cpu(sb, ufsi->i_u1.i_data[1]);
	अन्यथा
		fs32 = fs32_to_cpu(sb, ufsi->i_u1.i_data[0]);
	चयन (UFS_SB(sb)->s_flags & UFS_ST_MASK) अणु
	हाल UFS_ST_SUNx86:
	हाल UFS_ST_SUN:
		अगर ((fs32 & 0xffff0000) == 0 ||
		    (fs32 & 0xffff0000) == 0xffff0000)
			dev = old_decode_dev(fs32 & 0x7fff);
		अन्यथा
			dev = MKDEV(sysv_major(fs32), sysv_minor(fs32));
		अवरोध;

	शेष:
		dev = old_decode_dev(fs32);
		अवरोध;
	पूर्ण
	वापस dev;
पूर्ण

व्योम
ufs_set_inode_dev(काष्ठा super_block *sb, काष्ठा ufs_inode_info *ufsi, dev_t dev)
अणु
	__u32 fs32;

	चयन (UFS_SB(sb)->s_flags & UFS_ST_MASK) अणु
	हाल UFS_ST_SUNx86:
	हाल UFS_ST_SUN:
		fs32 = sysv_encode_dev(dev);
		अगर ((fs32 & 0xffff8000) == 0) अणु
			fs32 = old_encode_dev(dev);
		पूर्ण
		अवरोध;

	शेष:
		fs32 = old_encode_dev(dev);
		अवरोध;
	पूर्ण
	अगर ((UFS_SB(sb)->s_flags & UFS_ST_MASK) == UFS_ST_SUNx86)
		ufsi->i_u1.i_data[1] = cpu_to_fs32(sb, fs32);
	अन्यथा
		ufsi->i_u1.i_data[0] = cpu_to_fs32(sb, fs32);
पूर्ण

/**
 * ufs_get_locked_page() - locate, pin and lock a pagecache page, अगर not exist
 * पढ़ो it from disk.
 * @mapping: the address_space to search
 * @index: the page index
 *
 * Locates the desired pagecache page, अगर not exist we'll पढ़ो it,
 * locks it, increments its reference
 * count and वापसs its address.
 *
 */

काष्ठा page *ufs_get_locked_page(काष्ठा address_space *mapping,
				 pgoff_t index)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा page *page = find_lock_page(mapping, index);
	अगर (!page) अणु
		page = पढ़ो_mapping_page(mapping, index, शून्य);

		अगर (IS_ERR(page)) अणु
			prपूर्णांकk(KERN_ERR "ufs_change_blocknr: "
			       "read_mapping_page error: ino %lu, index: %lu\n",
			       mapping->host->i_ino, index);
			वापस page;
		पूर्ण

		lock_page(page);

		अगर (unlikely(page->mapping == शून्य)) अणु
			/* Truncate got there first */
			unlock_page(page);
			put_page(page);
			वापस शून्य;
		पूर्ण

		अगर (!PageUptodate(page) || PageError(page)) अणु
			unlock_page(page);
			put_page(page);

			prपूर्णांकk(KERN_ERR "ufs_change_blocknr: "
			       "can not read page: ino %lu, index: %lu\n",
			       inode->i_ino, index);

			वापस ERR_PTR(-EIO);
		पूर्ण
	पूर्ण
	अगर (!page_has_buffers(page))
		create_empty_buffers(page, 1 << inode->i_blkbits, 0);
	वापस page;
पूर्ण
