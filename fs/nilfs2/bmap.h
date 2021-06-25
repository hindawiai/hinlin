<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * bmap.h - NILFS block mapping.
 *
 * Copyright (C) 2006-2008 Nippon Telegraph and Telephone Corporation.
 *
 * Written by Koji Sato.
 */

#अगर_अघोषित _NILFS_BMAP_H
#घोषणा _NILFS_BMAP_H

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/nilfs2_ondisk.h>	/* nilfs_binfo, nilfs_inode, etc */
#समावेश "alloc.h"
#समावेश "dat.h"

#घोषणा NILFS_BMAP_INVALID_PTR	0

#घोषणा nilfs_bmap_keydअगरf_असल(dअगरf)	((dअगरf) < 0 ? -(dअगरf) : (dअगरf))


काष्ठा nilfs_bmap;

/**
 * जोड़ nilfs_bmap_ptr_req - request क्रम bmap ptr
 * @bpr_ptr: bmap poपूर्णांकer
 * @bpr_req: request क्रम persistent allocator
 */
जोड़ nilfs_bmap_ptr_req अणु
	__u64 bpr_ptr;
	काष्ठा nilfs_palloc_req bpr_req;
पूर्ण;

/**
 * काष्ठा nilfs_bmap_stats - bmap statistics
 * @bs_nblocks: number of blocks created or deleted
 */
काष्ठा nilfs_bmap_stats अणु
	अचिन्हित पूर्णांक bs_nblocks;
पूर्ण;

/**
 * काष्ठा nilfs_bmap_operations - bmap operation table
 */
काष्ठा nilfs_bmap_operations अणु
	पूर्णांक (*bop_lookup)(स्थिर काष्ठा nilfs_bmap *, __u64, पूर्णांक, __u64 *);
	पूर्णांक (*bop_lookup_contig)(स्थिर काष्ठा nilfs_bmap *, __u64, __u64 *,
				 अचिन्हित पूर्णांक);
	पूर्णांक (*bop_insert)(काष्ठा nilfs_bmap *, __u64, __u64);
	पूर्णांक (*bop_delete)(काष्ठा nilfs_bmap *, __u64);
	व्योम (*bop_clear)(काष्ठा nilfs_bmap *);

	पूर्णांक (*bop_propagate)(काष्ठा nilfs_bmap *, काष्ठा buffer_head *);
	व्योम (*bop_lookup_dirty_buffers)(काष्ठा nilfs_bmap *,
					 काष्ठा list_head *);

	पूर्णांक (*bop_assign)(काष्ठा nilfs_bmap *,
			  काष्ठा buffer_head **,
			  sector_t,
			  जोड़ nilfs_binfo *);
	पूर्णांक (*bop_mark)(काष्ठा nilfs_bmap *, __u64, पूर्णांक);

	पूर्णांक (*bop_seek_key)(स्थिर काष्ठा nilfs_bmap *, __u64, __u64 *);
	पूर्णांक (*bop_last_key)(स्थिर काष्ठा nilfs_bmap *, __u64 *);

	/* The following functions are पूर्णांकernal use only. */
	पूर्णांक (*bop_check_insert)(स्थिर काष्ठा nilfs_bmap *, __u64);
	पूर्णांक (*bop_check_delete)(काष्ठा nilfs_bmap *, __u64);
	पूर्णांक (*bop_gather_data)(काष्ठा nilfs_bmap *, __u64 *, __u64 *, पूर्णांक);
पूर्ण;


#घोषणा NILFS_BMAP_SIZE		(NILFS_INODE_BMAP_SIZE * माप(__le64))
#घोषणा NILFS_BMAP_KEY_BIT	(माप(अचिन्हित दीर्घ) * 8 /* अक्षर_बिट */)
#घोषणा NILFS_BMAP_NEW_PTR_INIT	\
	(1UL << (माप(अचिन्हित दीर्घ) * 8 /* अक्षर_बिट */ - 1))

अटल अंतरभूत पूर्णांक nilfs_bmap_is_new_ptr(अचिन्हित दीर्घ ptr)
अणु
	वापस !!(ptr & NILFS_BMAP_NEW_PTR_INIT);
पूर्ण


/**
 * काष्ठा nilfs_bmap - bmap काष्ठाure
 * @b_u: raw data
 * @b_sem: semaphore
 * @b_inode: owner of bmap
 * @b_ops: bmap operation table
 * @b_last_allocated_key: last allocated key क्रम data block
 * @b_last_allocated_ptr: last allocated ptr क्रम data block
 * @b_ptr_type: poपूर्णांकer type
 * @b_state: state
 * @b_nchildren_per_block: maximum number of child nodes क्रम non-root nodes
 */
काष्ठा nilfs_bmap अणु
	जोड़ अणु
		__u8 u_flags;
		__le64 u_data[NILFS_BMAP_SIZE / माप(__le64)];
	पूर्ण b_u;
	काष्ठा rw_semaphore b_sem;
	काष्ठा inode *b_inode;
	स्थिर काष्ठा nilfs_bmap_operations *b_ops;
	__u64 b_last_allocated_key;
	__u64 b_last_allocated_ptr;
	पूर्णांक b_ptr_type;
	पूर्णांक b_state;
	__u16 b_nchildren_per_block;
पूर्ण;

/* poपूर्णांकer type */
#घोषणा NILFS_BMAP_PTR_P	0	/* physical block number (i.e. LBN) */
#घोषणा NILFS_BMAP_PTR_VS	1	/*
					 * भव block number (single
					 * version)
					 */
#घोषणा NILFS_BMAP_PTR_VM	2	/*
					 * भव block number (has multiple
					 * versions)
					 */
#घोषणा NILFS_BMAP_PTR_U	(-1)	/* never perक्रमm poपूर्णांकer operations */

#घोषणा NILFS_BMAP_USE_VBN(bmap)	((bmap)->b_ptr_type > 0)

/* state */
#घोषणा NILFS_BMAP_सूचीTY	0x00000001

/**
 * काष्ठा nilfs_bmap_store - shaकरोw copy of bmap state
 * @data: cached raw block mapping of on-disk inode
 * @last_allocated_key: cached value of last allocated key क्रम data block
 * @last_allocated_ptr: cached value of last allocated ptr क्रम data block
 * @state: cached value of state field of bmap काष्ठाure
 */
काष्ठा nilfs_bmap_store अणु
	__le64 data[NILFS_BMAP_SIZE / माप(__le64)];
	__u64 last_allocated_key;
	__u64 last_allocated_ptr;
	पूर्णांक state;
पूर्ण;

पूर्णांक nilfs_bmap_test_and_clear_dirty(काष्ठा nilfs_bmap *);
पूर्णांक nilfs_bmap_पढ़ो(काष्ठा nilfs_bmap *, काष्ठा nilfs_inode *);
व्योम nilfs_bmap_ग_लिखो(काष्ठा nilfs_bmap *, काष्ठा nilfs_inode *);
पूर्णांक nilfs_bmap_lookup_contig(काष्ठा nilfs_bmap *, __u64, __u64 *, अचिन्हित पूर्णांक);
पूर्णांक nilfs_bmap_insert(काष्ठा nilfs_bmap *bmap, __u64 key, अचिन्हित दीर्घ rec);
पूर्णांक nilfs_bmap_delete(काष्ठा nilfs_bmap *bmap, __u64 key);
पूर्णांक nilfs_bmap_seek_key(काष्ठा nilfs_bmap *bmap, __u64 start, __u64 *keyp);
पूर्णांक nilfs_bmap_last_key(काष्ठा nilfs_bmap *bmap, __u64 *keyp);
पूर्णांक nilfs_bmap_truncate(काष्ठा nilfs_bmap *bmap, __u64 key);
व्योम nilfs_bmap_clear(काष्ठा nilfs_bmap *);
पूर्णांक nilfs_bmap_propagate(काष्ठा nilfs_bmap *, काष्ठा buffer_head *);
व्योम nilfs_bmap_lookup_dirty_buffers(काष्ठा nilfs_bmap *, काष्ठा list_head *);
पूर्णांक nilfs_bmap_assign(काष्ठा nilfs_bmap *, काष्ठा buffer_head **,
		      अचिन्हित दीर्घ, जोड़ nilfs_binfo *);
पूर्णांक nilfs_bmap_lookup_at_level(काष्ठा nilfs_bmap *, __u64, पूर्णांक, __u64 *);
पूर्णांक nilfs_bmap_mark(काष्ठा nilfs_bmap *, __u64, पूर्णांक);

व्योम nilfs_bmap_init_gc(काष्ठा nilfs_bmap *);

व्योम nilfs_bmap_save(स्थिर काष्ठा nilfs_bmap *, काष्ठा nilfs_bmap_store *);
व्योम nilfs_bmap_restore(काष्ठा nilfs_bmap *, स्थिर काष्ठा nilfs_bmap_store *);

अटल अंतरभूत पूर्णांक nilfs_bmap_lookup(काष्ठा nilfs_bmap *bmap, __u64 key,
				    __u64 *ptr)
अणु
	वापस nilfs_bmap_lookup_at_level(bmap, key, 1, ptr);
पूर्ण

/*
 * Internal use only
 */
काष्ठा inode *nilfs_bmap_get_dat(स्थिर काष्ठा nilfs_bmap *);

अटल अंतरभूत पूर्णांक nilfs_bmap_prepare_alloc_ptr(काष्ठा nilfs_bmap *bmap,
					       जोड़ nilfs_bmap_ptr_req *req,
					       काष्ठा inode *dat)
अणु
	अगर (dat)
		वापस nilfs_dat_prepare_alloc(dat, &req->bpr_req);
	/* ignore target ptr */
	req->bpr_ptr = bmap->b_last_allocated_ptr++;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nilfs_bmap_commit_alloc_ptr(काष्ठा nilfs_bmap *bmap,
					       जोड़ nilfs_bmap_ptr_req *req,
					       काष्ठा inode *dat)
अणु
	अगर (dat)
		nilfs_dat_commit_alloc(dat, &req->bpr_req);
पूर्ण

अटल अंतरभूत व्योम nilfs_bmap_पात_alloc_ptr(काष्ठा nilfs_bmap *bmap,
					      जोड़ nilfs_bmap_ptr_req *req,
					      काष्ठा inode *dat)
अणु
	अगर (dat)
		nilfs_dat_पात_alloc(dat, &req->bpr_req);
	अन्यथा
		bmap->b_last_allocated_ptr--;
पूर्ण

अटल अंतरभूत पूर्णांक nilfs_bmap_prepare_end_ptr(काष्ठा nilfs_bmap *bmap,
					     जोड़ nilfs_bmap_ptr_req *req,
					     काष्ठा inode *dat)
अणु
	वापस dat ? nilfs_dat_prepare_end(dat, &req->bpr_req) : 0;
पूर्ण

अटल अंतरभूत व्योम nilfs_bmap_commit_end_ptr(काष्ठा nilfs_bmap *bmap,
					     जोड़ nilfs_bmap_ptr_req *req,
					     काष्ठा inode *dat)
अणु
	अगर (dat)
		nilfs_dat_commit_end(dat, &req->bpr_req,
				     bmap->b_ptr_type == NILFS_BMAP_PTR_VS);
पूर्ण

अटल अंतरभूत व्योम nilfs_bmap_पात_end_ptr(काष्ठा nilfs_bmap *bmap,
					    जोड़ nilfs_bmap_ptr_req *req,
					    काष्ठा inode *dat)
अणु
	अगर (dat)
		nilfs_dat_पात_end(dat, &req->bpr_req);
पूर्ण

अटल अंतरभूत व्योम nilfs_bmap_set_target_v(काष्ठा nilfs_bmap *bmap, __u64 key,
					   __u64 ptr)
अणु
	bmap->b_last_allocated_key = key;
	bmap->b_last_allocated_ptr = ptr;
पूर्ण

__u64 nilfs_bmap_data_get_key(स्थिर काष्ठा nilfs_bmap *,
			      स्थिर काष्ठा buffer_head *);

__u64 nilfs_bmap_find_target_seq(स्थिर काष्ठा nilfs_bmap *, __u64);
__u64 nilfs_bmap_find_target_in_group(स्थिर काष्ठा nilfs_bmap *);


/* Assume that bmap semaphore is locked. */
अटल अंतरभूत पूर्णांक nilfs_bmap_dirty(स्थिर काष्ठा nilfs_bmap *bmap)
अणु
	वापस !!(bmap->b_state & NILFS_BMAP_सूचीTY);
पूर्ण

/* Assume that bmap semaphore is locked. */
अटल अंतरभूत व्योम nilfs_bmap_set_dirty(काष्ठा nilfs_bmap *bmap)
अणु
	bmap->b_state |= NILFS_BMAP_सूचीTY;
पूर्ण

/* Assume that bmap semaphore is locked. */
अटल अंतरभूत व्योम nilfs_bmap_clear_dirty(काष्ठा nilfs_bmap *bmap)
अणु
	bmap->b_state &= ~NILFS_BMAP_सूचीTY;
पूर्ण


#घोषणा NILFS_BMAP_LARGE	0x1

#घोषणा NILFS_BMAP_SMALL_LOW	NILFS_सूचीECT_KEY_MIN
#घोषणा NILFS_BMAP_SMALL_HIGH	NILFS_सूचीECT_KEY_MAX
#घोषणा NILFS_BMAP_LARGE_LOW	NILFS_BTREE_ROOT_NCHILDREN_MAX
#घोषणा NILFS_BMAP_LARGE_HIGH	NILFS_BTREE_KEY_MAX

#पूर्ण_अगर	/* _NILFS_BMAP_H */
