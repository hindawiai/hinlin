<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/fs/ufs/util.h
 *
 * Copyright (C) 1998 
 * Daniel Pirkl <daniel.pirkl@email.cz>
 * Charles University, Faculty of Mathematics and Physics
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/fs.h>
#समावेश "swab.h"


/*
 * some useful macros
 */
#घोषणा in_range(b,first,len)	((b)>=(first)&&(b)<(first)+(len))

/*
 * functions used क्रम retyping
 */
अटल अंतरभूत काष्ठा ufs_buffer_head *UCPI_UBH(काष्ठा ufs_cg_निजी_info *cpi)
अणु
	वापस &cpi->c_ubh;
पूर्ण
अटल अंतरभूत काष्ठा ufs_buffer_head *USPI_UBH(काष्ठा ufs_sb_निजी_info *spi)
अणु
	वापस &spi->s_ubh;
पूर्ण



/*
 * macros used क्रम accessing काष्ठाures
 */
अटल अंतरभूत s32
ufs_get_fs_state(काष्ठा super_block *sb, काष्ठा ufs_super_block_first *usb1,
		 काष्ठा ufs_super_block_third *usb3)
अणु
	चयन (UFS_SB(sb)->s_flags & UFS_ST_MASK) अणु
	हाल UFS_ST_SUNOS:
		अगर (fs32_to_cpu(sb, usb3->fs_postblक्रमmat) == UFS_42POSTBLFMT)
			वापस fs32_to_cpu(sb, usb1->fs_u0.fs_sun.fs_state);
		fallthrough;	/* to UFS_ST_SUN */
	हाल UFS_ST_SUN:
		वापस fs32_to_cpu(sb, usb3->fs_un2.fs_sun.fs_state);
	हाल UFS_ST_SUNx86:
		वापस fs32_to_cpu(sb, usb1->fs_u1.fs_sunx86.fs_state);
	हाल UFS_ST_44BSD:
	शेष:
		वापस fs32_to_cpu(sb, usb3->fs_un2.fs_44.fs_state);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
ufs_set_fs_state(काष्ठा super_block *sb, काष्ठा ufs_super_block_first *usb1,
		 काष्ठा ufs_super_block_third *usb3, s32 value)
अणु
	चयन (UFS_SB(sb)->s_flags & UFS_ST_MASK) अणु
	हाल UFS_ST_SUNOS:
		अगर (fs32_to_cpu(sb, usb3->fs_postblक्रमmat) == UFS_42POSTBLFMT) अणु
			usb1->fs_u0.fs_sun.fs_state = cpu_to_fs32(sb, value);
			अवरोध;
		पूर्ण
		fallthrough;	/* to UFS_ST_SUN */
	हाल UFS_ST_SUN:
		usb3->fs_un2.fs_sun.fs_state = cpu_to_fs32(sb, value);
		अवरोध;
	हाल UFS_ST_SUNx86:
		usb1->fs_u1.fs_sunx86.fs_state = cpu_to_fs32(sb, value);
		अवरोध;
	हाल UFS_ST_44BSD:
		usb3->fs_un2.fs_44.fs_state = cpu_to_fs32(sb, value);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत u32
ufs_get_fs_npsect(काष्ठा super_block *sb, काष्ठा ufs_super_block_first *usb1,
		  काष्ठा ufs_super_block_third *usb3)
अणु
	अगर ((UFS_SB(sb)->s_flags & UFS_ST_MASK) == UFS_ST_SUNx86)
		वापस fs32_to_cpu(sb, usb3->fs_un2.fs_sunx86.fs_npsect);
	अन्यथा
		वापस fs32_to_cpu(sb, usb1->fs_u1.fs_sun.fs_npsect);
पूर्ण

अटल अंतरभूत u64
ufs_get_fs_qbmask(काष्ठा super_block *sb, काष्ठा ufs_super_block_third *usb3)
अणु
	__fs64 पंचांगp;

	चयन (UFS_SB(sb)->s_flags & UFS_ST_MASK) अणु
	हाल UFS_ST_SUNOS:
	हाल UFS_ST_SUN:
		((__fs32 *)&पंचांगp)[0] = usb3->fs_un2.fs_sun.fs_qbmask[0];
		((__fs32 *)&पंचांगp)[1] = usb3->fs_un2.fs_sun.fs_qbmask[1];
		अवरोध;
	हाल UFS_ST_SUNx86:
		((__fs32 *)&पंचांगp)[0] = usb3->fs_un2.fs_sunx86.fs_qbmask[0];
		((__fs32 *)&पंचांगp)[1] = usb3->fs_un2.fs_sunx86.fs_qbmask[1];
		अवरोध;
	हाल UFS_ST_44BSD:
		((__fs32 *)&पंचांगp)[0] = usb3->fs_un2.fs_44.fs_qbmask[0];
		((__fs32 *)&पंचांगp)[1] = usb3->fs_un2.fs_44.fs_qbmask[1];
		अवरोध;
	पूर्ण

	वापस fs64_to_cpu(sb, पंचांगp);
पूर्ण

अटल अंतरभूत u64
ufs_get_fs_qfmask(काष्ठा super_block *sb, काष्ठा ufs_super_block_third *usb3)
अणु
	__fs64 पंचांगp;

	चयन (UFS_SB(sb)->s_flags & UFS_ST_MASK) अणु
	हाल UFS_ST_SUNOS:
	हाल UFS_ST_SUN:
		((__fs32 *)&पंचांगp)[0] = usb3->fs_un2.fs_sun.fs_qfmask[0];
		((__fs32 *)&पंचांगp)[1] = usb3->fs_un2.fs_sun.fs_qfmask[1];
		अवरोध;
	हाल UFS_ST_SUNx86:
		((__fs32 *)&पंचांगp)[0] = usb3->fs_un2.fs_sunx86.fs_qfmask[0];
		((__fs32 *)&पंचांगp)[1] = usb3->fs_un2.fs_sunx86.fs_qfmask[1];
		अवरोध;
	हाल UFS_ST_44BSD:
		((__fs32 *)&पंचांगp)[0] = usb3->fs_un2.fs_44.fs_qfmask[0];
		((__fs32 *)&पंचांगp)[1] = usb3->fs_un2.fs_44.fs_qfmask[1];
		अवरोध;
	पूर्ण

	वापस fs64_to_cpu(sb, पंचांगp);
पूर्ण

अटल अंतरभूत u16
ufs_get_de_namlen(काष्ठा super_block *sb, काष्ठा ufs_dir_entry *de)
अणु
	अगर ((UFS_SB(sb)->s_flags & UFS_DE_MASK) == UFS_DE_OLD)
		वापस fs16_to_cpu(sb, de->d_u.d_namlen);
	अन्यथा
		वापस de->d_u.d_44.d_namlen; /* XXX this seems wrong */
पूर्ण

अटल अंतरभूत व्योम
ufs_set_de_namlen(काष्ठा super_block *sb, काष्ठा ufs_dir_entry *de, u16 value)
अणु
	अगर ((UFS_SB(sb)->s_flags & UFS_DE_MASK) == UFS_DE_OLD)
		de->d_u.d_namlen = cpu_to_fs16(sb, value);
	अन्यथा
		de->d_u.d_44.d_namlen = value; /* XXX this seems wrong */
पूर्ण

अटल अंतरभूत व्योम
ufs_set_de_type(काष्ठा super_block *sb, काष्ठा ufs_dir_entry *de, पूर्णांक mode)
अणु
	अगर ((UFS_SB(sb)->s_flags & UFS_DE_MASK) != UFS_DE_44BSD)
		वापस;

	/*
	 * TODO turn this पूर्णांकo a table lookup
	 */
	चयन (mode & S_IFMT) अणु
	हाल S_IFSOCK:
		de->d_u.d_44.d_type = DT_SOCK;
		अवरोध;
	हाल S_IFLNK:
		de->d_u.d_44.d_type = DT_LNK;
		अवरोध;
	हाल S_IFREG:
		de->d_u.d_44.d_type = DT_REG;
		अवरोध;
	हाल S_IFBLK:
		de->d_u.d_44.d_type = DT_BLK;
		अवरोध;
	हाल S_IFसूची:
		de->d_u.d_44.d_type = DT_सूची;
		अवरोध;
	हाल S_IFCHR:
		de->d_u.d_44.d_type = DT_CHR;
		अवरोध;
	हाल S_IFIFO:
		de->d_u.d_44.d_type = DT_FIFO;
		अवरोध;
	शेष:
		de->d_u.d_44.d_type = DT_UNKNOWN;
	पूर्ण
पूर्ण

अटल अंतरभूत u32
ufs_get_inode_uid(काष्ठा super_block *sb, काष्ठा ufs_inode *inode)
अणु
	चयन (UFS_SB(sb)->s_flags & UFS_UID_MASK) अणु
	हाल UFS_UID_44BSD:
		वापस fs32_to_cpu(sb, inode->ui_u3.ui_44.ui_uid);
	हाल UFS_UID_EFT:
		अगर (inode->ui_u1.oldids.ui_suid == 0xFFFF)
			वापस fs32_to_cpu(sb, inode->ui_u3.ui_sun.ui_uid);
		fallthrough;
	शेष:
		वापस fs16_to_cpu(sb, inode->ui_u1.oldids.ui_suid);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
ufs_set_inode_uid(काष्ठा super_block *sb, काष्ठा ufs_inode *inode, u32 value)
अणु
	चयन (UFS_SB(sb)->s_flags & UFS_UID_MASK) अणु
	हाल UFS_UID_44BSD:
		inode->ui_u3.ui_44.ui_uid = cpu_to_fs32(sb, value);
		inode->ui_u1.oldids.ui_suid = cpu_to_fs16(sb, value);
		अवरोध;
	हाल UFS_UID_EFT:
		inode->ui_u3.ui_sun.ui_uid = cpu_to_fs32(sb, value);
		अगर (value > 0xFFFF)
			value = 0xFFFF;
		fallthrough;
	शेष:
		inode->ui_u1.oldids.ui_suid = cpu_to_fs16(sb, value);
		अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत u32
ufs_get_inode_gid(काष्ठा super_block *sb, काष्ठा ufs_inode *inode)
अणु
	चयन (UFS_SB(sb)->s_flags & UFS_UID_MASK) अणु
	हाल UFS_UID_44BSD:
		वापस fs32_to_cpu(sb, inode->ui_u3.ui_44.ui_gid);
	हाल UFS_UID_EFT:
		अगर (inode->ui_u1.oldids.ui_sgid == 0xFFFF)
			वापस fs32_to_cpu(sb, inode->ui_u3.ui_sun.ui_gid);
		fallthrough;
	शेष:
		वापस fs16_to_cpu(sb, inode->ui_u1.oldids.ui_sgid);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
ufs_set_inode_gid(काष्ठा super_block *sb, काष्ठा ufs_inode *inode, u32 value)
अणु
	चयन (UFS_SB(sb)->s_flags & UFS_UID_MASK) अणु
	हाल UFS_UID_44BSD:
		inode->ui_u3.ui_44.ui_gid = cpu_to_fs32(sb, value);
		inode->ui_u1.oldids.ui_sgid =  cpu_to_fs16(sb, value);
		अवरोध;
	हाल UFS_UID_EFT:
		inode->ui_u3.ui_sun.ui_gid = cpu_to_fs32(sb, value);
		अगर (value > 0xFFFF)
			value = 0xFFFF;
		fallthrough;
	शेष:
		inode->ui_u1.oldids.ui_sgid =  cpu_to_fs16(sb, value);
		अवरोध;
	पूर्ण
पूर्ण

बाह्य dev_t ufs_get_inode_dev(काष्ठा super_block *, काष्ठा ufs_inode_info *);
बाह्य व्योम ufs_set_inode_dev(काष्ठा super_block *, काष्ठा ufs_inode_info *, dev_t);
बाह्य पूर्णांक ufs_prepare_chunk(काष्ठा page *page, loff_t pos, अचिन्हित len);

/*
 * These functions manipulate ufs buffers
 */
#घोषणा ubh_bपढ़ो(sb,fragment,size) _ubh_bपढ़ो_(uspi,sb,fragment,size)  
बाह्य काष्ठा ufs_buffer_head * _ubh_bपढ़ो_(काष्ठा ufs_sb_निजी_info *, काष्ठा super_block *, u64 , u64);
बाह्य काष्ठा ufs_buffer_head * ubh_bपढ़ो_uspi(काष्ठा ufs_sb_निजी_info *, काष्ठा super_block *, u64, u64);
बाह्य व्योम ubh_brअन्यथा (काष्ठा ufs_buffer_head *);
बाह्य व्योम ubh_brअन्यथा_uspi (काष्ठा ufs_sb_निजी_info *);
बाह्य व्योम ubh_mark_buffer_dirty (काष्ठा ufs_buffer_head *);
बाह्य व्योम ubh_mark_buffer_uptodate (काष्ठा ufs_buffer_head *, पूर्णांक);
बाह्य व्योम ubh_sync_block(काष्ठा ufs_buffer_head *);
बाह्य व्योम ubh_bक्रमget (काष्ठा ufs_buffer_head *);
बाह्य पूर्णांक  ubh_buffer_dirty (काष्ठा ufs_buffer_head *);
#घोषणा ubh_ubhcpymem(mem,ubh,size) _ubh_ubhcpymem_(uspi,mem,ubh,size)
बाह्य व्योम _ubh_ubhcpymem_(काष्ठा ufs_sb_निजी_info *, अचिन्हित अक्षर *, काष्ठा ufs_buffer_head *, अचिन्हित);
#घोषणा ubh_स_नकलubh(ubh,mem,size) _ubh_स_नकलubh_(uspi,ubh,mem,size)
बाह्य व्योम _ubh_स_नकलubh_(काष्ठा ufs_sb_निजी_info *, काष्ठा ufs_buffer_head *, अचिन्हित अक्षर *, अचिन्हित);

/* This functions works with cache pages*/
बाह्य काष्ठा page *ufs_get_locked_page(काष्ठा address_space *mapping,
					pgoff_t index);
अटल अंतरभूत व्योम ufs_put_locked_page(काष्ठा page *page)
अणु
       unlock_page(page);
       put_page(page);
पूर्ण


/*
 * macros and अंतरभूत function to get important काष्ठाures from ufs_sb_निजी_info
 */

अटल अंतरभूत व्योम *get_usb_offset(काष्ठा ufs_sb_निजी_info *uspi,
				   अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक index;
	
	index = offset >> uspi->s_fshअगरt;
	offset &= ~uspi->s_fmask;
	वापस uspi->s_ubh.bh[index]->b_data + offset;
पूर्ण

#घोषणा ubh_get_usb_first(uspi) \
	((काष्ठा ufs_super_block_first *)get_usb_offset((uspi), 0))

#घोषणा ubh_get_usb_second(uspi) \
	((काष्ठा ufs_super_block_second *)get_usb_offset((uspi), UFS_SECTOR_SIZE))

#घोषणा ubh_get_usb_third(uspi)	\
	((काष्ठा ufs_super_block_third *)get_usb_offset((uspi), 2*UFS_SECTOR_SIZE))


#घोषणा ubh_get_ucg(ubh) \
	((काष्ठा ufs_cylinder_group *)((ubh)->bh[0]->b_data))


/*
 * Extract byte from ufs_buffer_head
 * Extract the bits क्रम a block from a map inside ufs_buffer_head
 */
#घोषणा ubh_get_addr8(ubh,begin) \
	((u8*)(ubh)->bh[(begin) >> uspi->s_fshअगरt]->b_data + \
	((begin) & ~uspi->s_fmask))

#घोषणा ubh_get_addr16(ubh,begin) \
	(((__fs16*)((ubh)->bh[(begin) >> (uspi->s_fshअगरt-1)]->b_data)) + \
	((begin) & ((uspi->fsize>>1) - 1)))

#घोषणा ubh_get_addr32(ubh,begin) \
	(((__fs32*)((ubh)->bh[(begin) >> (uspi->s_fshअगरt-2)]->b_data)) + \
	((begin) & ((uspi->s_fsize>>2) - 1)))

#घोषणा ubh_get_addr64(ubh,begin) \
	(((__fs64*)((ubh)->bh[(begin) >> (uspi->s_fshअगरt-3)]->b_data)) + \
	((begin) & ((uspi->s_fsize>>3) - 1)))

#घोषणा ubh_get_addr ubh_get_addr8

अटल अंतरभूत व्योम *ubh_get_data_ptr(काष्ठा ufs_sb_निजी_info *uspi,
				     काष्ठा ufs_buffer_head *ubh,
				     u64 blk)
अणु
	अगर (uspi->fs_magic == UFS2_MAGIC)
		वापस ubh_get_addr64(ubh, blk);
	अन्यथा
		वापस ubh_get_addr32(ubh, blk);
पूर्ण

#घोषणा ubh_blkmap(ubh,begin,bit) \
	((*ubh_get_addr(ubh, (begin) + ((bit) >> 3)) >> ((bit) & 7)) & (0xff >> (UFS_MAXFRAG - uspi->s_fpb)))

अटल अंतरभूत u64
ufs_मुक्तfrags(काष्ठा ufs_sb_निजी_info *uspi)
अणु
	वापस ufs_blkstofrags(uspi->cs_total.cs_nbमुक्त) +
		uspi->cs_total.cs_nfमुक्त;
पूर्ण

/*
 * Macros to access cylinder group array काष्ठाures
 */
#घोषणा ubh_cg_blktot(ucpi,cylno) \
	(*((__fs32*)ubh_get_addr(UCPI_UBH(ucpi), (ucpi)->c_btotoff + ((cylno) << 2))))

#घोषणा ubh_cg_blks(ucpi,cylno,rpos) \
	(*((__fs16*)ubh_get_addr(UCPI_UBH(ucpi), \
	(ucpi)->c_boff + (((cylno) * uspi->s_nrpos + (rpos)) << 1 ))))

/*
 * Biपंचांगap operations
 * These functions work like classical biपंचांगap operations.
 * The dअगरference is that we करोn't have the whole biपंचांगap
 * in one contiguous chunk of memory, but in several buffers.
 * The parameters of each function are super_block, ufs_buffer_head and
 * position of the beginning of the biपंचांगap.
 */
#घोषणा ubh_setbit(ubh,begin,bit) \
	(*ubh_get_addr(ubh, (begin) + ((bit) >> 3)) |= (1 << ((bit) & 7)))

#घोषणा ubh_clrbit(ubh,begin,bit) \
	(*ubh_get_addr (ubh, (begin) + ((bit) >> 3)) &= ~(1 << ((bit) & 7)))

#घोषणा ubh_isset(ubh,begin,bit) \
	(*ubh_get_addr (ubh, (begin) + ((bit) >> 3)) & (1 << ((bit) & 7)))

#घोषणा ubh_isclr(ubh,begin,bit) (!ubh_isset(ubh,begin,bit))

#घोषणा ubh_find_first_zero_bit(ubh,begin,size) _ubh_find_next_zero_bit_(uspi,ubh,begin,size,0)

#घोषणा ubh_find_next_zero_bit(ubh,begin,size,offset) _ubh_find_next_zero_bit_(uspi,ubh,begin,size,offset)
अटल अंतरभूत अचिन्हित _ubh_find_next_zero_bit_(
	काष्ठा ufs_sb_निजी_info * uspi, काष्ठा ufs_buffer_head * ubh,
	अचिन्हित begin, अचिन्हित size, अचिन्हित offset)
अणु
	अचिन्हित base, count, pos;

	size -= offset;
	begin <<= 3;
	offset += begin;
	base = offset >> uspi->s_bpfshअगरt;
	offset &= uspi->s_bpfmask;
	क्रम (;;) अणु
		count = min_t(अचिन्हित पूर्णांक, size + offset, uspi->s_bpf);
		size -= count - offset;
		pos = find_next_zero_bit_le(ubh->bh[base]->b_data, count, offset);
		अगर (pos < count || !size)
			अवरोध;
		base++;
		offset = 0;
	पूर्ण
	वापस (base << uspi->s_bpfshअगरt) + pos - begin;
पूर्ण 	

अटल अंतरभूत अचिन्हित find_last_zero_bit (अचिन्हित अक्षर * biपंचांगap,
	अचिन्हित size, अचिन्हित offset)
अणु
	अचिन्हित bit, i;
	अचिन्हित अक्षर * mapp;
	अचिन्हित अक्षर map;

	mapp = biपंचांगap + (size >> 3);
	map = *mapp--;
	bit = 1 << (size & 7);
	क्रम (i = size; i > offset; i--) अणु
		अगर ((map & bit) == 0)
			अवरोध;
		अगर ((i & 7) != 0) अणु
			bit >>= 1;
		पूर्ण अन्यथा अणु
			map = *mapp--;
			bit = 1 << 7;
		पूर्ण
	पूर्ण
	वापस i;
पूर्ण

#घोषणा ubh_find_last_zero_bit(ubh,begin,size,offset) _ubh_find_last_zero_bit_(uspi,ubh,begin,size,offset)
अटल अंतरभूत अचिन्हित _ubh_find_last_zero_bit_(
	काष्ठा ufs_sb_निजी_info * uspi, काष्ठा ufs_buffer_head * ubh,
	अचिन्हित begin, अचिन्हित start, अचिन्हित end)
अणु
	अचिन्हित base, count, pos, size;

	size = start - end;
	begin <<= 3;
	start += begin;
	base = start >> uspi->s_bpfshअगरt;
	start &= uspi->s_bpfmask;
	क्रम (;;) अणु
		count = min_t(अचिन्हित पूर्णांक,
			    size + (uspi->s_bpf - start), uspi->s_bpf)
			- (uspi->s_bpf - start);
		size -= count;
		pos = find_last_zero_bit (ubh->bh[base]->b_data,
			start, start - count);
		अगर (pos > start - count || !size)
			अवरोध;
		base--;
		start = uspi->s_bpf;
	पूर्ण
	वापस (base << uspi->s_bpfshअगरt) + pos - begin;
पूर्ण 	

#घोषणा ubh_isblockclear(ubh,begin,block) (!_ubh_isblockset_(uspi,ubh,begin,block))

#घोषणा ubh_isblockset(ubh,begin,block) _ubh_isblockset_(uspi,ubh,begin,block)
अटल अंतरभूत पूर्णांक _ubh_isblockset_(काष्ठा ufs_sb_निजी_info * uspi,
	काष्ठा ufs_buffer_head * ubh, अचिन्हित begin, अचिन्हित block)
अणु
	u8 mask;
	चयन (uspi->s_fpb) अणु
	हाल 8:
	    	वापस (*ubh_get_addr (ubh, begin + block) == 0xff);
	हाल 4:
		mask = 0x0f << ((block & 0x01) << 2);
		वापस (*ubh_get_addr (ubh, begin + (block >> 1)) & mask) == mask;
	हाल 2:
		mask = 0x03 << ((block & 0x03) << 1);
		वापस (*ubh_get_addr (ubh, begin + (block >> 2)) & mask) == mask;
	हाल 1:
		mask = 0x01 << (block & 0x07);
		वापस (*ubh_get_addr (ubh, begin + (block >> 3)) & mask) == mask;
	पूर्ण
	वापस 0;	
पूर्ण

#घोषणा ubh_clrblock(ubh,begin,block) _ubh_clrblock_(uspi,ubh,begin,block)
अटल अंतरभूत व्योम _ubh_clrblock_(काष्ठा ufs_sb_निजी_info * uspi,
	काष्ठा ufs_buffer_head * ubh, अचिन्हित begin, अचिन्हित block)
अणु
	चयन (uspi->s_fpb) अणु
	हाल 8:
	    	*ubh_get_addr (ubh, begin + block) = 0x00;
	    	वापस; 
	हाल 4:
		*ubh_get_addr (ubh, begin + (block >> 1)) &= ~(0x0f << ((block & 0x01) << 2));
		वापस;
	हाल 2:
		*ubh_get_addr (ubh, begin + (block >> 2)) &= ~(0x03 << ((block & 0x03) << 1));
		वापस;
	हाल 1:
		*ubh_get_addr (ubh, begin + (block >> 3)) &= ~(0x01 << ((block & 0x07)));
		वापस;
	पूर्ण
पूर्ण

#घोषणा ubh_setblock(ubh,begin,block) _ubh_setblock_(uspi,ubh,begin,block)
अटल अंतरभूत व्योम _ubh_setblock_(काष्ठा ufs_sb_निजी_info * uspi,
	काष्ठा ufs_buffer_head * ubh, अचिन्हित begin, अचिन्हित block)
अणु
	चयन (uspi->s_fpb) अणु
	हाल 8:
	    	*ubh_get_addr(ubh, begin + block) = 0xff;
	    	वापस;
	हाल 4:
		*ubh_get_addr(ubh, begin + (block >> 1)) |= (0x0f << ((block & 0x01) << 2));
		वापस;
	हाल 2:
		*ubh_get_addr(ubh, begin + (block >> 2)) |= (0x03 << ((block & 0x03) << 1));
		वापस;
	हाल 1:
		*ubh_get_addr(ubh, begin + (block >> 3)) |= (0x01 << ((block & 0x07)));
		वापस;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ufs_fragacct (काष्ठा super_block * sb, अचिन्हित blockmap,
	__fs32 * fraglist, पूर्णांक cnt)
अणु
	काष्ठा ufs_sb_निजी_info * uspi;
	अचिन्हित fragsize, pos;
	
	uspi = UFS_SB(sb)->s_uspi;
	
	fragsize = 0;
	क्रम (pos = 0; pos < uspi->s_fpb; pos++) अणु
		अगर (blockmap & (1 << pos)) अणु
			fragsize++;
		पूर्ण
		अन्यथा अगर (fragsize > 0) अणु
			fs32_add(sb, &fraglist[fragsize], cnt);
			fragsize = 0;
		पूर्ण
	पूर्ण
	अगर (fragsize > 0 && fragsize < uspi->s_fpb)
		fs32_add(sb, &fraglist[fragsize], cnt);
पूर्ण

अटल अंतरभूत व्योम *ufs_get_direct_data_ptr(काष्ठा ufs_sb_निजी_info *uspi,
					    काष्ठा ufs_inode_info *ufsi,
					    अचिन्हित blk)
अणु
	BUG_ON(blk > UFS_TIND_BLOCK);
	वापस uspi->fs_magic == UFS2_MAGIC ?
		(व्योम *)&ufsi->i_u1.u2_i_data[blk] :
		(व्योम *)&ufsi->i_u1.i_data[blk];
पूर्ण

अटल अंतरभूत u64 ufs_data_ptr_to_cpu(काष्ठा super_block *sb, व्योम *p)
अणु
	वापस UFS_SB(sb)->s_uspi->fs_magic == UFS2_MAGIC ?
		fs64_to_cpu(sb, *(__fs64 *)p) :
		fs32_to_cpu(sb, *(__fs32 *)p);
पूर्ण

अटल अंतरभूत व्योम ufs_cpu_to_data_ptr(काष्ठा super_block *sb, व्योम *p, u64 val)
अणु
	अगर (UFS_SB(sb)->s_uspi->fs_magic == UFS2_MAGIC)
		*(__fs64 *)p = cpu_to_fs64(sb, val);
	अन्यथा
		*(__fs32 *)p = cpu_to_fs32(sb, val);
पूर्ण

अटल अंतरभूत व्योम ufs_data_ptr_clear(काष्ठा ufs_sb_निजी_info *uspi,
				      व्योम *p)
अणु
	अगर (uspi->fs_magic == UFS2_MAGIC)
		*(__fs64 *)p = 0;
	अन्यथा
		*(__fs32 *)p = 0;
पूर्ण

अटल अंतरभूत पूर्णांक ufs_is_data_ptr_zero(काष्ठा ufs_sb_निजी_info *uspi,
				       व्योम *p)
अणु
	अगर (uspi->fs_magic == UFS2_MAGIC)
		वापस *(__fs64 *)p == 0;
	अन्यथा
		वापस *(__fs32 *)p == 0;
पूर्ण

अटल अंतरभूत __fs32 ufs_get_seconds(काष्ठा super_block *sbp)
अणु
	समय64_t now = kसमय_get_real_seconds();

	/* Signed 32-bit पूर्णांकerpretation wraps around in 2038, which
	 * happens in ufs1 inode stamps but not ufs2 using 64-bits
	 * stamps. For superblock and blockgroup, let's assume
	 * अचिन्हित 32-bit stamps, which are good until y2106.
	 * Wrap around rather than clamp here to make the dirty
	 * file प्रणाली detection work in the superblock stamp.
	 */
	वापस cpu_to_fs32(sbp, lower_32_bits(now));
पूर्ण
