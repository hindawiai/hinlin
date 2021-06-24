<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fs/f2fs/inode.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
#समावेश <linux/fs.h>
#समावेश <linux/f2fs_fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/ग_लिखोback.h>

#समावेश "f2fs.h"
#समावेश "node.h"
#समावेश "segment.h"
#समावेश "xattr.h"

#समावेश <trace/events/f2fs.h>

व्योम f2fs_mark_inode_dirty_sync(काष्ठा inode *inode, bool sync)
अणु
	अगर (is_inode_flag_set(inode, FI_NEW_INODE))
		वापस;

	अगर (f2fs_inode_dirtied(inode, sync))
		वापस;

	mark_inode_dirty_sync(inode);
पूर्ण

व्योम f2fs_set_inode_flags(काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक flags = F2FS_I(inode)->i_flags;
	अचिन्हित पूर्णांक new_fl = 0;

	अगर (flags & F2FS_SYNC_FL)
		new_fl |= S_SYNC;
	अगर (flags & F2FS_APPEND_FL)
		new_fl |= S_APPEND;
	अगर (flags & F2FS_IMMUTABLE_FL)
		new_fl |= S_IMMUTABLE;
	अगर (flags & F2FS_NOATIME_FL)
		new_fl |= S_NOATIME;
	अगर (flags & F2FS_सूचीSYNC_FL)
		new_fl |= S_सूचीSYNC;
	अगर (file_is_encrypt(inode))
		new_fl |= S_ENCRYPTED;
	अगर (file_is_verity(inode))
		new_fl |= S_VERITY;
	अगर (flags & F2FS_CASEFOLD_FL)
		new_fl |= S_CASEFOLD;
	inode_set_flags(inode, new_fl,
			S_SYNC|S_APPEND|S_IMMUTABLE|S_NOATIME|S_सूचीSYNC|
			S_ENCRYPTED|S_VERITY|S_CASEFOLD);
पूर्ण

अटल व्योम __get_inode_rdev(काष्ठा inode *inode, काष्ठा f2fs_inode *ri)
अणु
	पूर्णांक extra_size = get_extra_isize(inode);

	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode) ||
			S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) अणु
		अगर (ri->i_addr[extra_size])
			inode->i_rdev = old_decode_dev(
				le32_to_cpu(ri->i_addr[extra_size]));
		अन्यथा
			inode->i_rdev = new_decode_dev(
				le32_to_cpu(ri->i_addr[extra_size + 1]));
	पूर्ण
पूर्ण

अटल पूर्णांक __written_first_block(काष्ठा f2fs_sb_info *sbi,
					काष्ठा f2fs_inode *ri)
अणु
	block_t addr = le32_to_cpu(ri->i_addr[offset_in_addr(ri)]);

	अगर (!__is_valid_data_blkaddr(addr))
		वापस 1;
	अगर (!f2fs_is_valid_blkaddr(sbi, addr, DATA_GENERIC_ENHANCE))
		वापस -EFSCORRUPTED;
	वापस 0;
पूर्ण

अटल व्योम __set_inode_rdev(काष्ठा inode *inode, काष्ठा f2fs_inode *ri)
अणु
	पूर्णांक extra_size = get_extra_isize(inode);

	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) अणु
		अगर (old_valid_dev(inode->i_rdev)) अणु
			ri->i_addr[extra_size] =
				cpu_to_le32(old_encode_dev(inode->i_rdev));
			ri->i_addr[extra_size + 1] = 0;
		पूर्ण अन्यथा अणु
			ri->i_addr[extra_size] = 0;
			ri->i_addr[extra_size + 1] =
				cpu_to_le32(new_encode_dev(inode->i_rdev));
			ri->i_addr[extra_size + 2] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __recover_अंतरभूत_status(काष्ठा inode *inode, काष्ठा page *ipage)
अणु
	व्योम *अंतरभूत_data = अंतरभूत_data_addr(inode, ipage);
	__le32 *start = अंतरभूत_data;
	__le32 *end = start + MAX_INLINE_DATA(inode) / माप(__le32);

	जबतक (start < end) अणु
		अगर (*start++) अणु
			f2fs_रुको_on_page_ग_लिखोback(ipage, NODE, true, true);

			set_inode_flag(inode, FI_DATA_EXIST);
			set_raw_अंतरभूत(inode, F2FS_INODE(ipage));
			set_page_dirty(ipage);
			वापस;
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

अटल bool f2fs_enable_inode_chksum(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page)
अणु
	काष्ठा f2fs_inode *ri = &F2FS_NODE(page)->i;

	अगर (!f2fs_sb_has_inode_chksum(sbi))
		वापस false;

	अगर (!IS_INODE(page) || !(ri->i_अंतरभूत & F2FS_EXTRA_ATTR))
		वापस false;

	अगर (!F2FS_FITS_IN_INODE(ri, le16_to_cpu(ri->i_extra_isize),
				i_inode_checksum))
		वापस false;

	वापस true;
पूर्ण

अटल __u32 f2fs_inode_chksum(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page)
अणु
	काष्ठा f2fs_node *node = F2FS_NODE(page);
	काष्ठा f2fs_inode *ri = &node->i;
	__le32 ino = node->footer.ino;
	__le32 gen = ri->i_generation;
	__u32 chksum, chksum_seed;
	__u32 dummy_cs = 0;
	अचिन्हित पूर्णांक offset = दुरत्व(काष्ठा f2fs_inode, i_inode_checksum);
	अचिन्हित पूर्णांक cs_size = माप(dummy_cs);

	chksum = f2fs_chksum(sbi, sbi->s_chksum_seed, (__u8 *)&ino,
							माप(ino));
	chksum_seed = f2fs_chksum(sbi, chksum, (__u8 *)&gen, माप(gen));

	chksum = f2fs_chksum(sbi, chksum_seed, (__u8 *)ri, offset);
	chksum = f2fs_chksum(sbi, chksum, (__u8 *)&dummy_cs, cs_size);
	offset += cs_size;
	chksum = f2fs_chksum(sbi, chksum, (__u8 *)ri + offset,
						F2FS_BLKSIZE - offset);
	वापस chksum;
पूर्ण

bool f2fs_inode_chksum_verअगरy(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page)
अणु
	काष्ठा f2fs_inode *ri;
	__u32 provided, calculated;

	अगर (unlikely(is_sbi_flag_set(sbi, SBI_IS_SHUTDOWN)))
		वापस true;

#अगर_घोषित CONFIG_F2FS_CHECK_FS
	अगर (!f2fs_enable_inode_chksum(sbi, page))
#अन्यथा
	अगर (!f2fs_enable_inode_chksum(sbi, page) ||
			PageDirty(page) || PageWriteback(page))
#पूर्ण_अगर
		वापस true;

	ri = &F2FS_NODE(page)->i;
	provided = le32_to_cpu(ri->i_inode_checksum);
	calculated = f2fs_inode_chksum(sbi, page);

	अगर (provided != calculated)
		f2fs_warn(sbi, "checksum invalid, nid = %lu, ino_of_node = %x, %x vs. %x",
			  page->index, ino_of_node(page), provided, calculated);

	वापस provided == calculated;
पूर्ण

व्योम f2fs_inode_chksum_set(काष्ठा f2fs_sb_info *sbi, काष्ठा page *page)
अणु
	काष्ठा f2fs_inode *ri = &F2FS_NODE(page)->i;

	अगर (!f2fs_enable_inode_chksum(sbi, page))
		वापस;

	ri->i_inode_checksum = cpu_to_le32(f2fs_inode_chksum(sbi, page));
पूर्ण

अटल bool sanity_check_inode(काष्ठा inode *inode, काष्ठा page *node_page)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	काष्ठा f2fs_inode *ri = F2FS_INODE(node_page);
	अचिन्हित दीर्घ दीर्घ iblocks;

	iblocks = le64_to_cpu(F2FS_INODE(node_page)->i_blocks);
	अगर (!iblocks) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: corrupted inode i_blocks i_ino=%lx iblocks=%llu, run fsck to fix.",
			  __func__, inode->i_ino, iblocks);
		वापस false;
	पूर्ण

	अगर (ino_of_node(node_page) != nid_of_node(node_page)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: corrupted inode footer i_ino=%lx, ino,nid: [%u, %u] run fsck to fix.",
			  __func__, inode->i_ino,
			  ino_of_node(node_page), nid_of_node(node_page));
		वापस false;
	पूर्ण

	अगर (f2fs_sb_has_flexible_अंतरभूत_xattr(sbi)
			&& !f2fs_has_extra_attr(inode)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: corrupted inode ino=%lx, run fsck to fix.",
			  __func__, inode->i_ino);
		वापस false;
	पूर्ण

	अगर (f2fs_has_extra_attr(inode) &&
			!f2fs_sb_has_extra_attr(sbi)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: inode (ino=%lx) is with extra_attr, but extra_attr feature is off",
			  __func__, inode->i_ino);
		वापस false;
	पूर्ण

	अगर (fi->i_extra_isize > F2FS_TOTAL_EXTRA_ATTR_SIZE ||
			fi->i_extra_isize % माप(__le32)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: inode (ino=%lx) has corrupted i_extra_isize: %d, max: %zu",
			  __func__, inode->i_ino, fi->i_extra_isize,
			  F2FS_TOTAL_EXTRA_ATTR_SIZE);
		वापस false;
	पूर्ण

	अगर (f2fs_has_extra_attr(inode) &&
		f2fs_sb_has_flexible_अंतरभूत_xattr(sbi) &&
		f2fs_has_अंतरभूत_xattr(inode) &&
		(!fi->i_अंतरभूत_xattr_size ||
		fi->i_अंतरभूत_xattr_size > MAX_INLINE_XATTR_SIZE)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: inode (ino=%lx) has corrupted i_inline_xattr_size: %d, max: %zu",
			  __func__, inode->i_ino, fi->i_अंतरभूत_xattr_size,
			  MAX_INLINE_XATTR_SIZE);
		वापस false;
	पूर्ण

	अगर (F2FS_I(inode)->extent_tree) अणु
		काष्ठा extent_info *ei = &F2FS_I(inode)->extent_tree->largest;

		अगर (ei->len &&
			(!f2fs_is_valid_blkaddr(sbi, ei->blk,
						DATA_GENERIC_ENHANCE) ||
			!f2fs_is_valid_blkaddr(sbi, ei->blk + ei->len - 1,
						DATA_GENERIC_ENHANCE))) अणु
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			f2fs_warn(sbi, "%s: inode (ino=%lx) extent info [%u, %u, %u] is incorrect, run fsck to fix",
				  __func__, inode->i_ino,
				  ei->blk, ei->fofs, ei->len);
			वापस false;
		पूर्ण
	पूर्ण

	अगर (f2fs_has_अंतरभूत_data(inode) &&
			(!S_ISREG(inode->i_mode) && !S_ISLNK(inode->i_mode))) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: inode (ino=%lx, mode=%u) should not have inline_data, run fsck to fix",
			  __func__, inode->i_ino, inode->i_mode);
		वापस false;
	पूर्ण

	अगर (f2fs_has_अंतरभूत_dentry(inode) && !S_ISसूची(inode->i_mode)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: inode (ino=%lx, mode=%u) should not have inline_dentry, run fsck to fix",
			  __func__, inode->i_ino, inode->i_mode);
		वापस false;
	पूर्ण

	अगर ((fi->i_flags & F2FS_CASEFOLD_FL) && !f2fs_sb_has_हालfold(sbi)) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "%s: inode (ino=%lx) has casefold flag, but casefold feature is off",
			  __func__, inode->i_ino);
		वापस false;
	पूर्ण

	अगर (f2fs_has_extra_attr(inode) && f2fs_sb_has_compression(sbi) &&
			fi->i_flags & F2FS_COMPR_FL &&
			F2FS_FITS_IN_INODE(ri, fi->i_extra_isize,
						i_log_cluster_size)) अणु
		अगर (ri->i_compress_algorithm >= COMPRESS_MAX) अणु
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			f2fs_warn(sbi, "%s: inode (ino=%lx) has unsupported "
				"compress algorithm: %u, run fsck to fix",
				  __func__, inode->i_ino,
				  ri->i_compress_algorithm);
			वापस false;
		पूर्ण
		अगर (le64_to_cpu(ri->i_compr_blocks) >
				SECTOR_TO_BLOCK(inode->i_blocks)) अणु
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			f2fs_warn(sbi, "%s: inode (ino=%lx) has inconsistent "
				"i_compr_blocks:%llu, i_blocks:%llu, run fsck to fix",
				  __func__, inode->i_ino,
				  le64_to_cpu(ri->i_compr_blocks),
				  SECTOR_TO_BLOCK(inode->i_blocks));
			वापस false;
		पूर्ण
		अगर (ri->i_log_cluster_size < MIN_COMPRESS_LOG_SIZE ||
			ri->i_log_cluster_size > MAX_COMPRESS_LOG_SIZE) अणु
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			f2fs_warn(sbi, "%s: inode (ino=%lx) has unsupported "
				"log cluster size: %u, run fsck to fix",
				  __func__, inode->i_ino,
				  ri->i_log_cluster_size);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक करो_पढ़ो_inode(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा f2fs_inode_info *fi = F2FS_I(inode);
	काष्ठा page *node_page;
	काष्ठा f2fs_inode *ri;
	projid_t i_projid;
	पूर्णांक err;

	/* Check अगर ino is within scope */
	अगर (f2fs_check_nid_range(sbi, inode->i_ino))
		वापस -EINVAL;

	node_page = f2fs_get_node_page(sbi, inode->i_ino);
	अगर (IS_ERR(node_page))
		वापस PTR_ERR(node_page);

	ri = F2FS_INODE(node_page);

	inode->i_mode = le16_to_cpu(ri->i_mode);
	i_uid_ग_लिखो(inode, le32_to_cpu(ri->i_uid));
	i_gid_ग_लिखो(inode, le32_to_cpu(ri->i_gid));
	set_nlink(inode, le32_to_cpu(ri->i_links));
	inode->i_size = le64_to_cpu(ri->i_size);
	inode->i_blocks = SECTOR_FROM_BLOCK(le64_to_cpu(ri->i_blocks) - 1);

	inode->i_aसमय.tv_sec = le64_to_cpu(ri->i_aसमय);
	inode->i_स_समय.tv_sec = le64_to_cpu(ri->i_स_समय);
	inode->i_mसमय.tv_sec = le64_to_cpu(ri->i_mसमय);
	inode->i_aसमय.tv_nsec = le32_to_cpu(ri->i_aसमय_nsec);
	inode->i_स_समय.tv_nsec = le32_to_cpu(ri->i_स_समय_nsec);
	inode->i_mसमय.tv_nsec = le32_to_cpu(ri->i_mसमय_nsec);
	inode->i_generation = le32_to_cpu(ri->i_generation);
	अगर (S_ISसूची(inode->i_mode))
		fi->i_current_depth = le32_to_cpu(ri->i_current_depth);
	अन्यथा अगर (S_ISREG(inode->i_mode))
		fi->i_gc_failures[GC_FAILURE_PIN] =
					le16_to_cpu(ri->i_gc_failures);
	fi->i_xattr_nid = le32_to_cpu(ri->i_xattr_nid);
	fi->i_flags = le32_to_cpu(ri->i_flags);
	अगर (S_ISREG(inode->i_mode))
		fi->i_flags &= ~F2FS_PROJINHERIT_FL;
	biपंचांगap_zero(fi->flags, FI_MAX);
	fi->i_advise = ri->i_advise;
	fi->i_pino = le32_to_cpu(ri->i_pino);
	fi->i_dir_level = ri->i_dir_level;

	f2fs_init_extent_tree(inode, node_page);

	get_अंतरभूत_info(inode, ri);

	fi->i_extra_isize = f2fs_has_extra_attr(inode) ?
					le16_to_cpu(ri->i_extra_isize) : 0;

	अगर (f2fs_sb_has_flexible_अंतरभूत_xattr(sbi)) अणु
		fi->i_अंतरभूत_xattr_size = le16_to_cpu(ri->i_अंतरभूत_xattr_size);
	पूर्ण अन्यथा अगर (f2fs_has_अंतरभूत_xattr(inode) ||
				f2fs_has_अंतरभूत_dentry(inode)) अणु
		fi->i_अंतरभूत_xattr_size = DEFAULT_INLINE_XATTR_ADDRS;
	पूर्ण अन्यथा अणु

		/*
		 * Previous अंतरभूत data or directory always reserved 200 bytes
		 * in inode layout, even अगर अंतरभूत_xattr is disabled. In order
		 * to keep अंतरभूत_dentry's काष्ठाure क्रम backward compatibility,
		 * we get the space back only from अंतरभूत_data.
		 */
		fi->i_अंतरभूत_xattr_size = 0;
	पूर्ण

	अगर (!sanity_check_inode(inode, node_page)) अणु
		f2fs_put_page(node_page, 1);
		वापस -EFSCORRUPTED;
	पूर्ण

	/* check data exist */
	अगर (f2fs_has_अंतरभूत_data(inode) && !f2fs_exist_data(inode))
		__recover_अंतरभूत_status(inode, node_page);

	/* try to recover cold bit क्रम non-dir inode */
	अगर (!S_ISसूची(inode->i_mode) && !is_cold_node(node_page)) अणु
		f2fs_रुको_on_page_ग_लिखोback(node_page, NODE, true, true);
		set_cold_node(node_page, false);
		set_page_dirty(node_page);
	पूर्ण

	/* get rdev by using अंतरभूत_info */
	__get_inode_rdev(inode, ri);

	अगर (S_ISREG(inode->i_mode)) अणु
		err = __written_first_block(sbi, ri);
		अगर (err < 0) अणु
			f2fs_put_page(node_page, 1);
			वापस err;
		पूर्ण
		अगर (!err)
			set_inode_flag(inode, FI_FIRST_BLOCK_WRITTEN);
	पूर्ण

	अगर (!f2fs_need_inode_block_update(sbi, inode->i_ino))
		fi->last_disk_size = inode->i_size;

	अगर (fi->i_flags & F2FS_PROJINHERIT_FL)
		set_inode_flag(inode, FI_PROJ_INHERIT);

	अगर (f2fs_has_extra_attr(inode) && f2fs_sb_has_project_quota(sbi) &&
			F2FS_FITS_IN_INODE(ri, fi->i_extra_isize, i_projid))
		i_projid = (projid_t)le32_to_cpu(ri->i_projid);
	अन्यथा
		i_projid = F2FS_DEF_PROJID;
	fi->i_projid = make_kprojid(&init_user_ns, i_projid);

	अगर (f2fs_has_extra_attr(inode) && f2fs_sb_has_inode_crसमय(sbi) &&
			F2FS_FITS_IN_INODE(ri, fi->i_extra_isize, i_crसमय)) अणु
		fi->i_crसमय.tv_sec = le64_to_cpu(ri->i_crसमय);
		fi->i_crसमय.tv_nsec = le32_to_cpu(ri->i_crसमय_nsec);
	पूर्ण

	अगर (f2fs_has_extra_attr(inode) && f2fs_sb_has_compression(sbi) &&
					(fi->i_flags & F2FS_COMPR_FL)) अणु
		अगर (F2FS_FITS_IN_INODE(ri, fi->i_extra_isize,
					i_log_cluster_size)) अणु
			atomic_set(&fi->i_compr_blocks,
					le64_to_cpu(ri->i_compr_blocks));
			fi->i_compress_algorithm = ri->i_compress_algorithm;
			fi->i_log_cluster_size = ri->i_log_cluster_size;
			fi->i_compress_flag = le16_to_cpu(ri->i_compress_flag);
			fi->i_cluster_size = 1 << fi->i_log_cluster_size;
			set_inode_flag(inode, FI_COMPRESSED_खाता);
		पूर्ण
	पूर्ण

	F2FS_I(inode)->i_disk_समय[0] = inode->i_aसमय;
	F2FS_I(inode)->i_disk_समय[1] = inode->i_स_समय;
	F2FS_I(inode)->i_disk_समय[2] = inode->i_mसमय;
	F2FS_I(inode)->i_disk_समय[3] = F2FS_I(inode)->i_crसमय;
	f2fs_put_page(node_page, 1);

	stat_inc_अंतरभूत_xattr(inode);
	stat_inc_अंतरभूत_inode(inode);
	stat_inc_अंतरभूत_dir(inode);
	stat_inc_compr_inode(inode);
	stat_add_compr_blocks(inode, atomic_पढ़ो(&fi->i_compr_blocks));

	वापस 0;
पूर्ण

काष्ठा inode *f2fs_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_SB(sb);
	काष्ठा inode *inode;
	पूर्णांक ret = 0;

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	अगर (!(inode->i_state & I_NEW)) अणु
		trace_f2fs_iget(inode);
		वापस inode;
	पूर्ण
	अगर (ino == F2FS_NODE_INO(sbi) || ino == F2FS_META_INO(sbi))
		जाओ make_now;

	ret = करो_पढ़ो_inode(inode);
	अगर (ret)
		जाओ bad_inode;
make_now:
	अगर (ino == F2FS_NODE_INO(sbi)) अणु
		inode->i_mapping->a_ops = &f2fs_node_aops;
		mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);
	पूर्ण अन्यथा अगर (ino == F2FS_META_INO(sbi)) अणु
		inode->i_mapping->a_ops = &f2fs_meta_aops;
		mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);
	पूर्ण अन्यथा अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_op = &f2fs_file_inode_operations;
		inode->i_fop = &f2fs_file_operations;
		inode->i_mapping->a_ops = &f2fs_dblock_aops;
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &f2fs_dir_inode_operations;
		inode->i_fop = &f2fs_dir_operations;
		inode->i_mapping->a_ops = &f2fs_dblock_aops;
		inode_nohighmem(inode);
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		अगर (file_is_encrypt(inode))
			inode->i_op = &f2fs_encrypted_symlink_inode_operations;
		अन्यथा
			inode->i_op = &f2fs_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &f2fs_dblock_aops;
	पूर्ण अन्यथा अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode) ||
			S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) अणु
		inode->i_op = &f2fs_special_inode_operations;
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
	पूर्ण अन्यथा अणु
		ret = -EIO;
		जाओ bad_inode;
	पूर्ण
	f2fs_set_inode_flags(inode);
	unlock_new_inode(inode);
	trace_f2fs_iget(inode);
	वापस inode;

bad_inode:
	f2fs_inode_synced(inode);
	iget_failed(inode);
	trace_f2fs_iget_निकास(inode, ret);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा inode *f2fs_iget_retry(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा inode *inode;
retry:
	inode = f2fs_iget(sb, ino);
	अगर (IS_ERR(inode)) अणु
		अगर (PTR_ERR(inode) == -ENOMEM) अणु
			congestion_रुको(BLK_RW_ASYNC, DEFAULT_IO_TIMEOUT);
			जाओ retry;
		पूर्ण
	पूर्ण
	वापस inode;
पूर्ण

व्योम f2fs_update_inode(काष्ठा inode *inode, काष्ठा page *node_page)
अणु
	काष्ठा f2fs_inode *ri;
	काष्ठा extent_tree *et = F2FS_I(inode)->extent_tree;

	f2fs_रुको_on_page_ग_लिखोback(node_page, NODE, true, true);
	set_page_dirty(node_page);

	f2fs_inode_synced(inode);

	ri = F2FS_INODE(node_page);

	ri->i_mode = cpu_to_le16(inode->i_mode);
	ri->i_advise = F2FS_I(inode)->i_advise;
	ri->i_uid = cpu_to_le32(i_uid_पढ़ो(inode));
	ri->i_gid = cpu_to_le32(i_gid_पढ़ो(inode));
	ri->i_links = cpu_to_le32(inode->i_nlink);
	ri->i_size = cpu_to_le64(i_size_पढ़ो(inode));
	ri->i_blocks = cpu_to_le64(SECTOR_TO_BLOCK(inode->i_blocks) + 1);

	अगर (et) अणु
		पढ़ो_lock(&et->lock);
		set_raw_extent(&et->largest, &ri->i_ext);
		पढ़ो_unlock(&et->lock);
	पूर्ण अन्यथा अणु
		स_रखो(&ri->i_ext, 0, माप(ri->i_ext));
	पूर्ण
	set_raw_अंतरभूत(inode, ri);

	ri->i_aसमय = cpu_to_le64(inode->i_aसमय.tv_sec);
	ri->i_स_समय = cpu_to_le64(inode->i_स_समय.tv_sec);
	ri->i_mसमय = cpu_to_le64(inode->i_mसमय.tv_sec);
	ri->i_aसमय_nsec = cpu_to_le32(inode->i_aसमय.tv_nsec);
	ri->i_स_समय_nsec = cpu_to_le32(inode->i_स_समय.tv_nsec);
	ri->i_mसमय_nsec = cpu_to_le32(inode->i_mसमय.tv_nsec);
	अगर (S_ISसूची(inode->i_mode))
		ri->i_current_depth =
			cpu_to_le32(F2FS_I(inode)->i_current_depth);
	अन्यथा अगर (S_ISREG(inode->i_mode))
		ri->i_gc_failures =
			cpu_to_le16(F2FS_I(inode)->i_gc_failures[GC_FAILURE_PIN]);
	ri->i_xattr_nid = cpu_to_le32(F2FS_I(inode)->i_xattr_nid);
	ri->i_flags = cpu_to_le32(F2FS_I(inode)->i_flags);
	ri->i_pino = cpu_to_le32(F2FS_I(inode)->i_pino);
	ri->i_generation = cpu_to_le32(inode->i_generation);
	ri->i_dir_level = F2FS_I(inode)->i_dir_level;

	अगर (f2fs_has_extra_attr(inode)) अणु
		ri->i_extra_isize = cpu_to_le16(F2FS_I(inode)->i_extra_isize);

		अगर (f2fs_sb_has_flexible_अंतरभूत_xattr(F2FS_I_SB(inode)))
			ri->i_अंतरभूत_xattr_size =
				cpu_to_le16(F2FS_I(inode)->i_अंतरभूत_xattr_size);

		अगर (f2fs_sb_has_project_quota(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(ri, F2FS_I(inode)->i_extra_isize,
								i_projid)) अणु
			projid_t i_projid;

			i_projid = from_kprojid(&init_user_ns,
						F2FS_I(inode)->i_projid);
			ri->i_projid = cpu_to_le32(i_projid);
		पूर्ण

		अगर (f2fs_sb_has_inode_crसमय(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(ri, F2FS_I(inode)->i_extra_isize,
								i_crसमय)) अणु
			ri->i_crसमय =
				cpu_to_le64(F2FS_I(inode)->i_crसमय.tv_sec);
			ri->i_crसमय_nsec =
				cpu_to_le32(F2FS_I(inode)->i_crसमय.tv_nsec);
		पूर्ण

		अगर (f2fs_sb_has_compression(F2FS_I_SB(inode)) &&
			F2FS_FITS_IN_INODE(ri, F2FS_I(inode)->i_extra_isize,
							i_log_cluster_size)) अणु
			ri->i_compr_blocks =
				cpu_to_le64(atomic_पढ़ो(
					&F2FS_I(inode)->i_compr_blocks));
			ri->i_compress_algorithm =
				F2FS_I(inode)->i_compress_algorithm;
			ri->i_compress_flag =
				cpu_to_le16(F2FS_I(inode)->i_compress_flag);
			ri->i_log_cluster_size =
				F2FS_I(inode)->i_log_cluster_size;
		पूर्ण
	पूर्ण

	__set_inode_rdev(inode, ri);

	/* deleted inode */
	अगर (inode->i_nlink == 0)
		clear_अंतरभूत_node(node_page);

	F2FS_I(inode)->i_disk_समय[0] = inode->i_aसमय;
	F2FS_I(inode)->i_disk_समय[1] = inode->i_स_समय;
	F2FS_I(inode)->i_disk_समय[2] = inode->i_mसमय;
	F2FS_I(inode)->i_disk_समय[3] = F2FS_I(inode)->i_crसमय;

#अगर_घोषित CONFIG_F2FS_CHECK_FS
	f2fs_inode_chksum_set(F2FS_I_SB(inode), node_page);
#पूर्ण_अगर
पूर्ण

व्योम f2fs_update_inode_page(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा page *node_page;
retry:
	node_page = f2fs_get_node_page(sbi, inode->i_ino);
	अगर (IS_ERR(node_page)) अणु
		पूर्णांक err = PTR_ERR(node_page);

		अगर (err == -ENOMEM) अणु
			cond_resched();
			जाओ retry;
		पूर्ण अन्यथा अगर (err != -ENOENT) अणु
			f2fs_stop_checkpoपूर्णांक(sbi, false);
		पूर्ण
		वापस;
	पूर्ण
	f2fs_update_inode(inode, node_page);
	f2fs_put_page(node_page, 1);
पूर्ण

पूर्णांक f2fs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);

	अगर (inode->i_ino == F2FS_NODE_INO(sbi) ||
			inode->i_ino == F2FS_META_INO(sbi))
		वापस 0;

	/*
	 * aसमय could be updated without dirtying f2fs inode in lazyसमय mode
	 */
	अगर (f2fs_is_समय_consistent(inode) &&
		!is_inode_flag_set(inode, FI_सूचीTY_INODE))
		वापस 0;

	अगर (!f2fs_is_checkpoपूर्णांक_पढ़ोy(sbi))
		वापस -ENOSPC;

	/*
	 * We need to balance fs here to prevent from producing dirty node pages
	 * during the urgent cleaning समय when running out of मुक्त sections.
	 */
	f2fs_update_inode_page(inode);
	अगर (wbc && wbc->nr_to_ग_लिखो)
		f2fs_balance_fs(sbi, true);
	वापस 0;
पूर्ण

/*
 * Called at the last iput() अगर i_nlink is zero
 */
व्योम f2fs_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	nid_t xnid = F2FS_I(inode)->i_xattr_nid;
	पूर्णांक err = 0;

	/* some reमुख्यed atomic pages should discarded */
	अगर (f2fs_is_atomic_file(inode))
		f2fs_drop_inmem_pages(inode);

	trace_f2fs_evict_inode(inode);
	truncate_inode_pages_final(&inode->i_data);

	अगर (inode->i_ino == F2FS_NODE_INO(sbi) ||
			inode->i_ino == F2FS_META_INO(sbi))
		जाओ out_clear;

	f2fs_bug_on(sbi, get_dirty_pages(inode));
	f2fs_हटाओ_dirty_inode(inode);

	f2fs_destroy_extent_tree(inode);

	अगर (inode->i_nlink || is_bad_inode(inode))
		जाओ no_delete;

	err = dquot_initialize(inode);
	अगर (err) अणु
		err = 0;
		set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
	पूर्ण

	f2fs_हटाओ_ino_entry(sbi, inode->i_ino, APPEND_INO);
	f2fs_हटाओ_ino_entry(sbi, inode->i_ino, UPDATE_INO);
	f2fs_हटाओ_ino_entry(sbi, inode->i_ino, FLUSH_INO);

	sb_start_पूर्णांकग_लिखो(inode->i_sb);
	set_inode_flag(inode, FI_NO_ALLOC);
	i_size_ग_लिखो(inode, 0);
retry:
	अगर (F2FS_HAS_BLOCKS(inode))
		err = f2fs_truncate(inode);

	अगर (समय_प्रकारo_inject(sbi, FAULT_EVICT_INODE)) अणु
		f2fs_show_injection_info(sbi, FAULT_EVICT_INODE);
		err = -EIO;
	पूर्ण

	अगर (!err) अणु
		f2fs_lock_op(sbi);
		err = f2fs_हटाओ_inode_page(inode);
		f2fs_unlock_op(sbi);
		अगर (err == -ENOENT)
			err = 0;
	पूर्ण

	/* give more chances, अगर ENOMEM हाल */
	अगर (err == -ENOMEM) अणु
		err = 0;
		जाओ retry;
	पूर्ण

	अगर (err) अणु
		f2fs_update_inode_page(inode);
		अगर (dquot_initialize_needed(inode))
			set_sbi_flag(sbi, SBI_QUOTA_NEED_REPAIR);
	पूर्ण
	sb_end_पूर्णांकग_लिखो(inode->i_sb);
no_delete:
	dquot_drop(inode);

	stat_dec_अंतरभूत_xattr(inode);
	stat_dec_अंतरभूत_dir(inode);
	stat_dec_अंतरभूत_inode(inode);
	stat_dec_compr_inode(inode);
	stat_sub_compr_blocks(inode,
			atomic_पढ़ो(&F2FS_I(inode)->i_compr_blocks));

	अगर (likely(!f2fs_cp_error(sbi) &&
				!is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		f2fs_bug_on(sbi, is_inode_flag_set(inode, FI_सूचीTY_INODE));
	अन्यथा
		f2fs_inode_synced(inode);

	/* क्रम the हाल f2fs_new_inode() was failed, .i_ino is zero, skip it */
	अगर (inode->i_ino)
		invalidate_mapping_pages(NODE_MAPPING(sbi), inode->i_ino,
							inode->i_ino);
	अगर (xnid)
		invalidate_mapping_pages(NODE_MAPPING(sbi), xnid, xnid);
	अगर (inode->i_nlink) अणु
		अगर (is_inode_flag_set(inode, FI_APPEND_WRITE))
			f2fs_add_ino_entry(sbi, inode->i_ino, APPEND_INO);
		अगर (is_inode_flag_set(inode, FI_UPDATE_WRITE))
			f2fs_add_ino_entry(sbi, inode->i_ino, UPDATE_INO);
	पूर्ण
	अगर (is_inode_flag_set(inode, FI_FREE_NID)) अणु
		f2fs_alloc_nid_failed(sbi, inode->i_ino);
		clear_inode_flag(inode, FI_FREE_NID);
	पूर्ण अन्यथा अणु
		/*
		 * If xattr nid is corrupted, we can reach out error condition,
		 * err & !f2fs_exist_written_data(sbi, inode->i_ino, ORPHAN_INO)).
		 * In that हाल, f2fs_check_nid_range() is enough to give a clue.
		 */
	पूर्ण
out_clear:
	fscrypt_put_encryption_info(inode);
	fsverity_cleanup_inode(inode);
	clear_inode(inode);
पूर्ण

/* caller should call f2fs_lock_op() */
व्योम f2fs_handle_failed_inode(काष्ठा inode *inode)
अणु
	काष्ठा f2fs_sb_info *sbi = F2FS_I_SB(inode);
	काष्ठा node_info ni;
	पूर्णांक err;

	/*
	 * clear nlink of inode in order to release resource of inode
	 * immediately.
	 */
	clear_nlink(inode);

	/*
	 * we must call this to aव्योम inode being reमुख्यed as dirty, resulting
	 * in a panic when flushing dirty inodes in gdirty_list.
	 */
	f2fs_update_inode_page(inode);
	f2fs_inode_synced(inode);

	/* करोn't make bad inode, since it becomes a regular file. */
	unlock_new_inode(inode);

	/*
	 * Note: we should add inode to orphan list beक्रमe f2fs_unlock_op()
	 * so we can prevent losing this orphan when encoutering checkpoपूर्णांक
	 * and following suddenly घातer-off.
	 */
	err = f2fs_get_node_info(sbi, inode->i_ino, &ni);
	अगर (err) अणु
		set_sbi_flag(sbi, SBI_NEED_FSCK);
		f2fs_warn(sbi, "May loss orphan inode, run fsck to fix.");
		जाओ out;
	पूर्ण

	अगर (ni.blk_addr != शून्य_ADDR) अणु
		err = f2fs_acquire_orphan_inode(sbi);
		अगर (err) अणु
			set_sbi_flag(sbi, SBI_NEED_FSCK);
			f2fs_warn(sbi, "Too many orphan inodes, run fsck to fix.");
		पूर्ण अन्यथा अणु
			f2fs_add_orphan_inode(inode);
		पूर्ण
		f2fs_alloc_nid_करोne(sbi, inode->i_ino);
	पूर्ण अन्यथा अणु
		set_inode_flag(inode, FI_FREE_NID);
	पूर्ण

out:
	f2fs_unlock_op(sbi);

	/* iput will drop the inode object */
	iput(inode);
पूर्ण
