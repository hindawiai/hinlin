<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/ext4/mbभाग.स
 *
 *  Written by: Alex Tomas <alex@clusterfs.com>
 *
 */
#अगर_अघोषित _EXT4_MBALLOC_H
#घोषणा _EXT4_MBALLOC_H

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/module.h>
#समावेश <linux/swap.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/mutex.h>
#समावेश "ext4_jbd2.h"
#समावेश "ext4.h"

/*
 * mb_debug() dynamic prपूर्णांकk msgs could be used to debug mballoc code.
 */
#अगर_घोषित CONFIG_EXT4_DEBUG
#घोषणा mb_debug(sb, fmt, ...)						\
	pr_debug("[%s/%d] EXT4-fs (%s): (%s, %d): %s: " fmt,		\
		current->comm, task_pid_nr(current), sb->s_id,		\
	       __खाता__, __LINE__, __func__, ##__VA_ARGS__)
#अन्यथा
#घोषणा mb_debug(sb, fmt, ...)	no_prपूर्णांकk(fmt, ##__VA_ARGS__)
#पूर्ण_अगर

#घोषणा EXT4_MB_HISTORY_ALLOC		1	/* allocation */
#घोषणा EXT4_MB_HISTORY_PREALLOC	2	/* pपुनः_स्मृतिated blocks used */

/*
 * How दीर्घ mballoc can look क्रम a best extent (in found extents)
 */
#घोषणा MB_DEFAULT_MAX_TO_SCAN		200

/*
 * How दीर्घ mballoc must look क्रम a best extent
 */
#घोषणा MB_DEFAULT_MIN_TO_SCAN		10

/*
 * with 'ext4_mb_stats' allocator will collect stats that will be
 * shown at umount. The collecting costs though!
 */
#घोषणा MB_DEFAULT_STATS		0

/*
 * files smaller than MB_DEFAULT_STREAM_THRESHOLD are served
 * by the stream allocator, which purpose is to pack requests
 * as बंद each to other as possible to produce smooth I/O traffic
 * We use locality group pपुनः_स्मृति space क्रम stream request.
 * We can tune the same via /proc/fs/ext4/<partition>/stream_req
 */
#घोषणा MB_DEFAULT_STREAM_THRESHOLD	16	/* 64K */

/*
 * क्रम which requests use 2^N search using buddies
 */
#घोषणा MB_DEFAULT_ORDER2_REQS		2

/*
 * शेष group pपुनः_स्मृति size 512 blocks
 */
#घोषणा MB_DEFAULT_GROUP_PREALLOC	512

/*
 * maximum length of inode pपुनः_स्मृति list
 */
#घोषणा MB_DEFAULT_MAX_INODE_PREALLOC	512

/*
 * Number of groups to search linearly beक्रमe perक्रमming group scanning
 * optimization.
 */
#घोषणा MB_DEFAULT_LINEAR_LIMIT		4

/*
 * Minimum number of groups that should be present in the file प्रणाली to perक्रमm
 * group scanning optimizations.
 */
#घोषणा MB_DEFAULT_LINEAR_SCAN_THRESHOLD	16

/*
 * Number of valid buddy orders
 */
#घोषणा MB_NUM_ORDERS(sb)		((sb)->s_blocksize_bits + 2)

काष्ठा ext4_मुक्त_data अणु
	/* this links the मुक्त block inक्रमmation from sb_info */
	काष्ठा list_head		efd_list;

	/* this links the मुक्त block inक्रमmation from group_info */
	काष्ठा rb_node			efd_node;

	/* group which मुक्त block extent beदीर्घs */
	ext4_group_t			efd_group;

	/* मुक्त block extent */
	ext4_grpblk_t			efd_start_cluster;
	ext4_grpblk_t			efd_count;

	/* transaction which मुक्तd this extent */
	tid_t				efd_tid;
पूर्ण;

काष्ठा ext4_pपुनः_स्मृति_space अणु
	काष्ठा list_head	pa_inode_list;
	काष्ठा list_head	pa_group_list;
	जोड़ अणु
		काष्ठा list_head pa_पंचांगp_list;
		काष्ठा rcu_head	pa_rcu;
	पूर्ण u;
	spinlock_t		pa_lock;
	atomic_t		pa_count;
	अचिन्हित		pa_deleted;
	ext4_fsblk_t		pa_pstart;	/* phys. block */
	ext4_lblk_t		pa_lstart;	/* log. block */
	ext4_grpblk_t		pa_len;		/* len of pपुनः_स्मृतिated chunk */
	ext4_grpblk_t		pa_मुक्त;	/* how many blocks are मुक्त */
	अचिन्हित लघु		pa_type;	/* pa type. inode or group */
	spinlock_t		*pa_obj_lock;
	काष्ठा inode		*pa_inode;	/* hack, क्रम history only */
पूर्ण;

क्रमागत अणु
	MB_INODE_PA = 0,
	MB_GROUP_PA = 1
पूर्ण;

काष्ठा ext4_मुक्त_extent अणु
	ext4_lblk_t fe_logical;
	ext4_grpblk_t fe_start;	/* In cluster units */
	ext4_group_t fe_group;
	ext4_grpblk_t fe_len;	/* In cluster units */
पूर्ण;

/*
 * Locality group:
 *   we try to group all related changes together
 *   so that ग_लिखोback can flush/allocate them together as well
 *   Size of lg_pपुनः_स्मृति_list hash is determined by MB_DEFAULT_GROUP_PREALLOC
 *   (512). We store pपुनः_स्मृति space पूर्णांकo the hash based on the pa_मुक्त blocks
 *   order value.ie, fls(pa_मुक्त)-1;
 */
#घोषणा PREALLOC_TB_SIZE 10
काष्ठा ext4_locality_group अणु
	/* क्रम allocator */
	/* to serialize allocates */
	काष्ठा mutex		lg_mutex;
	/* list of pपुनः_स्मृतिations */
	काष्ठा list_head	lg_pपुनः_स्मृति_list[PREALLOC_TB_SIZE];
	spinlock_t		lg_pपुनः_स्मृति_lock;
पूर्ण;

काष्ठा ext4_allocation_context अणु
	काष्ठा inode *ac_inode;
	काष्ठा super_block *ac_sb;

	/* original request */
	काष्ठा ext4_मुक्त_extent ac_o_ex;

	/* goal request (normalized ac_o_ex) */
	काष्ठा ext4_मुक्त_extent ac_g_ex;

	/* the best found extent */
	काष्ठा ext4_मुक्त_extent ac_b_ex;

	/* copy of the best found extent taken beक्रमe pपुनः_स्मृतिation efक्रमts */
	काष्ठा ext4_मुक्त_extent ac_f_ex;

	ext4_group_t ac_last_optimal_group;
	__u32 ac_groups_considered;
	__u32 ac_flags;		/* allocation hपूर्णांकs */
	__u16 ac_groups_scanned;
	__u16 ac_groups_linear_reमुख्यing;
	__u16 ac_found;
	__u16 ac_tail;
	__u16 ac_buddy;
	__u8 ac_status;
	__u8 ac_criteria;
	__u8 ac_2order;		/* अगर request is to allocate 2^N blocks and
				 * N > 0, the field stores N, otherwise 0 */
	__u8 ac_op;		/* operation, क्रम history only */
	काष्ठा page *ac_biपंचांगap_page;
	काष्ठा page *ac_buddy_page;
	काष्ठा ext4_pपुनः_स्मृति_space *ac_pa;
	काष्ठा ext4_locality_group *ac_lg;
पूर्ण;

#घोषणा AC_STATUS_CONTINUE	1
#घोषणा AC_STATUS_FOUND		2
#घोषणा AC_STATUS_BREAK		3

काष्ठा ext4_buddy अणु
	काष्ठा page *bd_buddy_page;
	व्योम *bd_buddy;
	काष्ठा page *bd_biपंचांगap_page;
	व्योम *bd_biपंचांगap;
	काष्ठा ext4_group_info *bd_info;
	काष्ठा super_block *bd_sb;
	__u16 bd_blkbits;
	ext4_group_t bd_group;
पूर्ण;

अटल अंतरभूत ext4_fsblk_t ext4_grp_offs_to_block(काष्ठा super_block *sb,
					काष्ठा ext4_मुक्त_extent *fex)
अणु
	वापस ext4_group_first_block_no(sb, fex->fe_group) +
		(fex->fe_start << EXT4_SB(sb)->s_cluster_bits);
पूर्ण

प्रकार पूर्णांक (*ext4_mballoc_query_range_fn)(
	काष्ठा super_block		*sb,
	ext4_group_t			agno,
	ext4_grpblk_t			start,
	ext4_grpblk_t			len,
	व्योम				*priv);

पूर्णांक
ext4_mballoc_query_range(
	काष्ठा super_block		*sb,
	ext4_group_t			agno,
	ext4_grpblk_t			start,
	ext4_grpblk_t			end,
	ext4_mballoc_query_range_fn	क्रमmatter,
	व्योम				*priv);

#पूर्ण_अगर
