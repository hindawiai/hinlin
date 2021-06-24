<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs/f2fs/node.h
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 */
/* start node id of a node block dedicated to the given node id */
#घोषणा	START_NID(nid) (((nid) / NAT_ENTRY_PER_BLOCK) * NAT_ENTRY_PER_BLOCK)

/* node block offset on the NAT area dedicated to the given start node id */
#घोषणा	NAT_BLOCK_OFFSET(start_nid) ((start_nid) / NAT_ENTRY_PER_BLOCK)

/* # of pages to perक्रमm synchronous पढ़ोahead beक्रमe building मुक्त nids */
#घोषणा FREE_NID_PAGES	8
#घोषणा MAX_FREE_NIDS	(NAT_ENTRY_PER_BLOCK * FREE_NID_PAGES)

/* size of मुक्त nid batch when shrinking */
#घोषणा SHRINK_NID_BATCH_SIZE	8

#घोषणा DEF_RA_NID_PAGES	0	/* # of nid pages to be पढ़ोaheaded */

/* maximum पढ़ोahead size क्रम node during getting data blocks */
#घोषणा MAX_RA_NODE		128

/* control the memory footprपूर्णांक threshold (10MB per 1GB ram) */
#घोषणा DEF_RAM_THRESHOLD	1

/* control dirty nats ratio threshold (शेष: 10% over max nid count) */
#घोषणा DEF_सूचीTY_NAT_RATIO_THRESHOLD		10
/* control total # of nats */
#घोषणा DEF_NAT_CACHE_THRESHOLD			100000

/* vector size क्रम gang look-up from nat cache that consists of radix tree */
#घोषणा NATVEC_SIZE	64
#घोषणा SETVEC_SIZE	32

/* वापस value क्रम पढ़ो_node_page */
#घोषणा LOCKED_PAGE	1

/* For flag in काष्ठा node_info */
क्रमागत अणु
	IS_CHECKPOINTED,	/* is it checkpoपूर्णांकed beक्रमe? */
	HAS_FSYNCED_INODE,	/* is the inode fsynced beक्रमe? */
	HAS_LAST_FSYNC,		/* has the latest node fsync mark? */
	IS_सूचीTY,		/* this nat entry is dirty? */
	IS_PREALLOC,		/* nat entry is pपुनः_स्मृतिated */
पूर्ण;

/*
 * For node inक्रमmation
 */
काष्ठा node_info अणु
	nid_t nid;		/* node id */
	nid_t ino;		/* inode number of the node's owner */
	block_t	blk_addr;	/* block address of the node */
	अचिन्हित अक्षर version;	/* version of the node */
	अचिन्हित अक्षर flag;	/* क्रम node inक्रमmation bits */
पूर्ण;

काष्ठा nat_entry अणु
	काष्ठा list_head list;	/* क्रम clean or dirty nat list */
	काष्ठा node_info ni;	/* in-memory node inक्रमmation */
पूर्ण;

#घोषणा nat_get_nid(nat)		((nat)->ni.nid)
#घोषणा nat_set_nid(nat, n)		((nat)->ni.nid = (n))
#घोषणा nat_get_blkaddr(nat)		((nat)->ni.blk_addr)
#घोषणा nat_set_blkaddr(nat, b)		((nat)->ni.blk_addr = (b))
#घोषणा nat_get_ino(nat)		((nat)->ni.ino)
#घोषणा nat_set_ino(nat, i)		((nat)->ni.ino = (i))
#घोषणा nat_get_version(nat)		((nat)->ni.version)
#घोषणा nat_set_version(nat, v)		((nat)->ni.version = (v))

#घोषणा inc_node_version(version)	(++(version))

अटल अंतरभूत व्योम copy_node_info(काष्ठा node_info *dst,
						काष्ठा node_info *src)
अणु
	dst->nid = src->nid;
	dst->ino = src->ino;
	dst->blk_addr = src->blk_addr;
	dst->version = src->version;
	/* should not copy flag here */
पूर्ण

अटल अंतरभूत व्योम set_nat_flag(काष्ठा nat_entry *ne,
				अचिन्हित पूर्णांक type, bool set)
अणु
	अचिन्हित अक्षर mask = 0x01 << type;
	अगर (set)
		ne->ni.flag |= mask;
	अन्यथा
		ne->ni.flag &= ~mask;
पूर्ण

अटल अंतरभूत bool get_nat_flag(काष्ठा nat_entry *ne, अचिन्हित पूर्णांक type)
अणु
	अचिन्हित अक्षर mask = 0x01 << type;
	वापस ne->ni.flag & mask;
पूर्ण

अटल अंतरभूत व्योम nat_reset_flag(काष्ठा nat_entry *ne)
अणु
	/* these states can be set only after checkpoपूर्णांक was करोne */
	set_nat_flag(ne, IS_CHECKPOINTED, true);
	set_nat_flag(ne, HAS_FSYNCED_INODE, false);
	set_nat_flag(ne, HAS_LAST_FSYNC, true);
पूर्ण

अटल अंतरभूत व्योम node_info_from_raw_nat(काष्ठा node_info *ni,
						काष्ठा f2fs_nat_entry *raw_ne)
अणु
	ni->ino = le32_to_cpu(raw_ne->ino);
	ni->blk_addr = le32_to_cpu(raw_ne->block_addr);
	ni->version = raw_ne->version;
पूर्ण

अटल अंतरभूत व्योम raw_nat_from_node_info(काष्ठा f2fs_nat_entry *raw_ne,
						काष्ठा node_info *ni)
अणु
	raw_ne->ino = cpu_to_le32(ni->ino);
	raw_ne->block_addr = cpu_to_le32(ni->blk_addr);
	raw_ne->version = ni->version;
पूर्ण

अटल अंतरभूत bool excess_dirty_nats(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस NM_I(sbi)->nat_cnt[सूचीTY_NAT] >= NM_I(sbi)->max_nid *
					NM_I(sbi)->dirty_nats_ratio / 100;
पूर्ण

अटल अंतरभूत bool excess_cached_nats(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस NM_I(sbi)->nat_cnt[TOTAL_NAT] >= DEF_NAT_CACHE_THRESHOLD;
पूर्ण

अटल अंतरभूत bool excess_dirty_nodes(काष्ठा f2fs_sb_info *sbi)
अणु
	वापस get_pages(sbi, F2FS_सूचीTY_NODES) >= sbi->blocks_per_seg * 8;
पूर्ण

क्रमागत mem_type अणु
	FREE_NIDS,	/* indicates the मुक्त nid list */
	NAT_ENTRIES,	/* indicates the cached nat entry */
	सूचीTY_DENTS,	/* indicates dirty dentry pages */
	INO_ENTRIES,	/* indicates inode entries */
	EXTENT_CACHE,	/* indicates extent cache */
	INMEM_PAGES,	/* indicates inmemory pages */
	DISCARD_CACHE,	/* indicates memory of cached discard cmds */
	BASE_CHECK,	/* check kernel status */
पूर्ण;

काष्ठा nat_entry_set अणु
	काष्ठा list_head set_list;	/* link with other nat sets */
	काष्ठा list_head entry_list;	/* link with dirty nat entries */
	nid_t set;			/* set number*/
	अचिन्हित पूर्णांक entry_cnt;		/* the # of nat entries in set */
पूर्ण;

काष्ठा मुक्त_nid अणु
	काष्ठा list_head list;	/* क्रम मुक्त node id list */
	nid_t nid;		/* node id */
	पूर्णांक state;		/* in use or not: FREE_NID or PREALLOC_NID */
पूर्ण;

अटल अंतरभूत व्योम next_मुक्त_nid(काष्ठा f2fs_sb_info *sbi, nid_t *nid)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	काष्ठा मुक्त_nid *fnid;

	spin_lock(&nm_i->nid_list_lock);
	अगर (nm_i->nid_cnt[FREE_NID] <= 0) अणु
		spin_unlock(&nm_i->nid_list_lock);
		वापस;
	पूर्ण
	fnid = list_first_entry(&nm_i->मुक्त_nid_list, काष्ठा मुक्त_nid, list);
	*nid = fnid->nid;
	spin_unlock(&nm_i->nid_list_lock);
पूर्ण

/*
 * अंतरभूत functions
 */
अटल अंतरभूत व्योम get_nat_biपंचांगap(काष्ठा f2fs_sb_info *sbi, व्योम *addr)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);

#अगर_घोषित CONFIG_F2FS_CHECK_FS
	अगर (स_भेद(nm_i->nat_biपंचांगap, nm_i->nat_biपंचांगap_mir,
						nm_i->biपंचांगap_size))
		f2fs_bug_on(sbi, 1);
#पूर्ण_अगर
	स_नकल(addr, nm_i->nat_biपंचांगap, nm_i->biपंचांगap_size);
पूर्ण

अटल अंतरभूत pgoff_t current_nat_addr(काष्ठा f2fs_sb_info *sbi, nid_t start)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);
	pgoff_t block_off;
	pgoff_t block_addr;

	/*
	 * block_off = segment_off * 512 + off_in_segment
	 * OLD = (segment_off * 512) * 2 + off_in_segment
	 * NEW = 2 * (segment_off * 512 + off_in_segment) - off_in_segment
	 */
	block_off = NAT_BLOCK_OFFSET(start);

	block_addr = (pgoff_t)(nm_i->nat_blkaddr +
		(block_off << 1) -
		(block_off & (sbi->blocks_per_seg - 1)));

	अगर (f2fs_test_bit(block_off, nm_i->nat_biपंचांगap))
		block_addr += sbi->blocks_per_seg;

	वापस block_addr;
पूर्ण

अटल अंतरभूत pgoff_t next_nat_addr(काष्ठा f2fs_sb_info *sbi,
						pgoff_t block_addr)
अणु
	काष्ठा f2fs_nm_info *nm_i = NM_I(sbi);

	block_addr -= nm_i->nat_blkaddr;
	block_addr ^= 1 << sbi->log_blocks_per_seg;
	वापस block_addr + nm_i->nat_blkaddr;
पूर्ण

अटल अंतरभूत व्योम set_to_next_nat(काष्ठा f2fs_nm_info *nm_i, nid_t start_nid)
अणु
	अचिन्हित पूर्णांक block_off = NAT_BLOCK_OFFSET(start_nid);

	f2fs_change_bit(block_off, nm_i->nat_biपंचांगap);
#अगर_घोषित CONFIG_F2FS_CHECK_FS
	f2fs_change_bit(block_off, nm_i->nat_biपंचांगap_mir);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत nid_t ino_of_node(काष्ठा page *node_page)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(node_page);
	वापस le32_to_cpu(rn->footer.ino);
पूर्ण

अटल अंतरभूत nid_t nid_of_node(काष्ठा page *node_page)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(node_page);
	वापस le32_to_cpu(rn->footer.nid);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ofs_of_node(काष्ठा page *node_page)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(node_page);
	अचिन्हित flag = le32_to_cpu(rn->footer.flag);
	वापस flag >> OFFSET_BIT_SHIFT;
पूर्ण

अटल अंतरभूत __u64 cpver_of_node(काष्ठा page *node_page)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(node_page);
	वापस le64_to_cpu(rn->footer.cp_ver);
पूर्ण

अटल अंतरभूत block_t next_blkaddr_of_node(काष्ठा page *node_page)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(node_page);
	वापस le32_to_cpu(rn->footer.next_blkaddr);
पूर्ण

अटल अंतरभूत व्योम fill_node_footer(काष्ठा page *page, nid_t nid,
				nid_t ino, अचिन्हित पूर्णांक ofs, bool reset)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(page);
	अचिन्हित पूर्णांक old_flag = 0;

	अगर (reset)
		स_रखो(rn, 0, माप(*rn));
	अन्यथा
		old_flag = le32_to_cpu(rn->footer.flag);

	rn->footer.nid = cpu_to_le32(nid);
	rn->footer.ino = cpu_to_le32(ino);

	/* should reमुख्य old flag bits such as COLD_BIT_SHIFT */
	rn->footer.flag = cpu_to_le32((ofs << OFFSET_BIT_SHIFT) |
					(old_flag & OFFSET_BIT_MASK));
पूर्ण

अटल अंतरभूत व्योम copy_node_footer(काष्ठा page *dst, काष्ठा page *src)
अणु
	काष्ठा f2fs_node *src_rn = F2FS_NODE(src);
	काष्ठा f2fs_node *dst_rn = F2FS_NODE(dst);
	स_नकल(&dst_rn->footer, &src_rn->footer, माप(काष्ठा node_footer));
पूर्ण

अटल अंतरभूत व्योम fill_node_footer_blkaddr(काष्ठा page *page, block_t blkaddr)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(F2FS_P_SB(page));
	काष्ठा f2fs_node *rn = F2FS_NODE(page);
	__u64 cp_ver = cur_cp_version(ckpt);

	अगर (__is_set_ckpt_flags(ckpt, CP_CRC_RECOVERY_FLAG))
		cp_ver |= (cur_cp_crc(ckpt) << 32);

	rn->footer.cp_ver = cpu_to_le64(cp_ver);
	rn->footer.next_blkaddr = cpu_to_le32(blkaddr);
पूर्ण

अटल अंतरभूत bool is_recoverable_dnode(काष्ठा page *page)
अणु
	काष्ठा f2fs_checkpoपूर्णांक *ckpt = F2FS_CKPT(F2FS_P_SB(page));
	__u64 cp_ver = cur_cp_version(ckpt);

	/* Don't care crc part, अगर fsck.f2fs sets it. */
	अगर (__is_set_ckpt_flags(ckpt, CP_NOCRC_RECOVERY_FLAG))
		वापस (cp_ver << 32) == (cpver_of_node(page) << 32);

	अगर (__is_set_ckpt_flags(ckpt, CP_CRC_RECOVERY_FLAG))
		cp_ver |= (cur_cp_crc(ckpt) << 32);

	वापस cp_ver == cpver_of_node(page);
पूर्ण

/*
 * f2fs assigns the following node offsets described as (num).
 * N = NIDS_PER_BLOCK
 *
 *  Inode block (0)
 *    |- direct node (1)
 *    |- direct node (2)
 *    |- indirect node (3)
 *    |            `- direct node (4 => 4 + N - 1)
 *    |- indirect node (4 + N)
 *    |            `- direct node (5 + N => 5 + 2N - 1)
 *    `- द्विगुन indirect node (5 + 2N)
 *                 `- indirect node (6 + 2N)
 *                       `- direct node
 *                 ......
 *                 `- indirect node ((6 + 2N) + x(N + 1))
 *                       `- direct node
 *                 ......
 *                 `- indirect node ((6 + 2N) + (N - 1)(N + 1))
 *                       `- direct node
 */
अटल अंतरभूत bool IS_DNODE(काष्ठा page *node_page)
अणु
	अचिन्हित पूर्णांक ofs = ofs_of_node(node_page);

	अगर (f2fs_has_xattr_block(ofs))
		वापस true;

	अगर (ofs == 3 || ofs == 4 + NIDS_PER_BLOCK ||
			ofs == 5 + 2 * NIDS_PER_BLOCK)
		वापस false;
	अगर (ofs >= 6 + 2 * NIDS_PER_BLOCK) अणु
		ofs -= 6 + 2 * NIDS_PER_BLOCK;
		अगर (!((दीर्घ पूर्णांक)ofs % (NIDS_PER_BLOCK + 1)))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक set_nid(काष्ठा page *p, पूर्णांक off, nid_t nid, bool i)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(p);

	f2fs_रुको_on_page_ग_लिखोback(p, NODE, true, true);

	अगर (i)
		rn->i.i_nid[off - NODE_सूची1_BLOCK] = cpu_to_le32(nid);
	अन्यथा
		rn->in.nid[off] = cpu_to_le32(nid);
	वापस set_page_dirty(p);
पूर्ण

अटल अंतरभूत nid_t get_nid(काष्ठा page *p, पूर्णांक off, bool i)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(p);

	अगर (i)
		वापस le32_to_cpu(rn->i.i_nid[off - NODE_सूची1_BLOCK]);
	वापस le32_to_cpu(rn->in.nid[off]);
पूर्ण

/*
 * Coldness identअगरication:
 *  - Mark cold files in f2fs_inode_info
 *  - Mark cold node blocks in their node footer
 *  - Mark cold data pages in page cache
 */
अटल अंतरभूत पूर्णांक is_cold_data(काष्ठा page *page)
अणु
	वापस PageChecked(page);
पूर्ण

अटल अंतरभूत व्योम set_cold_data(काष्ठा page *page)
अणु
	SetPageChecked(page);
पूर्ण

अटल अंतरभूत व्योम clear_cold_data(काष्ठा page *page)
अणु
	ClearPageChecked(page);
पूर्ण

अटल अंतरभूत पूर्णांक is_node(काष्ठा page *page, पूर्णांक type)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(page);
	वापस le32_to_cpu(rn->footer.flag) & (1 << type);
पूर्ण

#घोषणा is_cold_node(page)	is_node(page, COLD_BIT_SHIFT)
#घोषणा is_fsync_dnode(page)	is_node(page, FSYNC_BIT_SHIFT)
#घोषणा is_dent_dnode(page)	is_node(page, DENT_BIT_SHIFT)

अटल अंतरभूत पूर्णांक is_अंतरभूत_node(काष्ठा page *page)
अणु
	वापस PageChecked(page);
पूर्ण

अटल अंतरभूत व्योम set_अंतरभूत_node(काष्ठा page *page)
अणु
	SetPageChecked(page);
पूर्ण

अटल अंतरभूत व्योम clear_अंतरभूत_node(काष्ठा page *page)
अणु
	ClearPageChecked(page);
पूर्ण

अटल अंतरभूत व्योम set_cold_node(काष्ठा page *page, bool is_dir)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(page);
	अचिन्हित पूर्णांक flag = le32_to_cpu(rn->footer.flag);

	अगर (is_dir)
		flag &= ~(0x1 << COLD_BIT_SHIFT);
	अन्यथा
		flag |= (0x1 << COLD_BIT_SHIFT);
	rn->footer.flag = cpu_to_le32(flag);
पूर्ण

अटल अंतरभूत व्योम set_mark(काष्ठा page *page, पूर्णांक mark, पूर्णांक type)
अणु
	काष्ठा f2fs_node *rn = F2FS_NODE(page);
	अचिन्हित पूर्णांक flag = le32_to_cpu(rn->footer.flag);
	अगर (mark)
		flag |= (0x1 << type);
	अन्यथा
		flag &= ~(0x1 << type);
	rn->footer.flag = cpu_to_le32(flag);

#अगर_घोषित CONFIG_F2FS_CHECK_FS
	f2fs_inode_chksum_set(F2FS_P_SB(page), page);
#पूर्ण_अगर
पूर्ण
#घोषणा set_dentry_mark(page, mark)	set_mark(page, mark, DENT_BIT_SHIFT)
#घोषणा set_fsync_mark(page, mark)	set_mark(page, mark, FSYNC_BIT_SHIFT)
