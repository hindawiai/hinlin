<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2003-2006, Cluster File Systems, Inc, info@clusterfs.com
 * Written by Alex Tomas <alex@clusterfs.com>
 */


/*
 * mballoc.c contains the multiblocks allocation routines
 */

#समावेश "ext4_jbd2.h"
#समावेश "mballoc.h"
#समावेश <linux/log2.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/nospec.h>
#समावेश <linux/backing-dev.h>
#समावेश <trace/events/ext4.h>

/*
 * MUSTDO:
 *   - test ext4_ext_search_left() and ext4_ext_search_right()
 *   - search क्रम metadata in few groups
 *
 * TODO v4:
 *   - normalization should take पूर्णांकo account whether file is still खोलो
 *   - discard pपुनः_स्मृतिations अगर no मुक्त space left (policy?)
 *   - करोn't normalize tails
 *   - quota
 *   - reservation क्रम superuser
 *
 * TODO v3:
 *   - biपंचांगap पढ़ो-ahead (proposed by Oleg Drokin aka green)
 *   - track min/max extents in each group क्रम better group selection
 *   - mb_mark_used() may allocate chunk right after splitting buddy
 *   - tree of groups sorted by number of मुक्त blocks
 *   - error handling
 */

/*
 * The allocation request involve request क्रम multiple number of blocks
 * near to the goal(block) value specअगरied.
 *
 * During initialization phase of the allocator we decide to use the
 * group pपुनः_स्मृतिation or inode pपुनः_स्मृतिation depending on the size of
 * the file. The size of the file could be the resulting file size we
 * would have after allocation, or the current file size, which ever
 * is larger. If the size is less than sbi->s_mb_stream_request we
 * select to use the group pपुनः_स्मृतिation. The शेष value of
 * s_mb_stream_request is 16 blocks. This can also be tuned via
 * /sys/fs/ext4/<partition>/mb_stream_req. The value is represented in
 * terms of number of blocks.
 *
 * The मुख्य motivation क्रम having small file use group pपुनः_स्मृतिation is to
 * ensure that we have small files बंदr together on the disk.
 *
 * First stage the allocator looks at the inode pपुनः_स्मृति list,
 * ext4_inode_info->i_pपुनः_स्मृति_list, which contains list of pपुनः_स्मृति
 * spaces क्रम this particular inode. The inode pपुनः_स्मृति space is
 * represented as:
 *
 * pa_lstart -> the logical start block क्रम this pपुनः_स्मृति space
 * pa_pstart -> the physical start block क्रम this pपुनः_स्मृति space
 * pa_len    -> length क्रम this pपुनः_स्मृति space (in clusters)
 * pa_मुक्त   ->  मुक्त space available in this pपुनः_स्मृति space (in clusters)
 *
 * The inode pपुनः_स्मृतिation space is used looking at the _logical_ start
 * block. If only the logical file block falls within the range of pपुनः_स्मृति
 * space we will consume the particular pपुनः_स्मृति space. This makes sure that
 * we have contiguous physical blocks representing the file blocks
 *
 * The important thing to be noted in हाल of inode pपुनः_स्मृति space is that
 * we करोn't modअगरy the values associated to inode pपुनः_स्मृति space except
 * pa_मुक्त.
 *
 * If we are not able to find blocks in the inode pपुनः_स्मृति space and अगर we
 * have the group allocation flag set then we look at the locality group
 * pपुनः_स्मृति space. These are per CPU pपुनः_स्मृति list represented as
 *
 * ext4_sb_info.s_locality_groups[smp_processor_id()]
 *
 * The reason क्रम having a per cpu locality group is to reduce the contention
 * between CPUs. It is possible to get scheduled at this poपूर्णांक.
 *
 * The locality group pपुनः_स्मृति space is used looking at whether we have
 * enough मुक्त space (pa_मुक्त) within the pपुनः_स्मृति space.
 *
 * If we can't allocate blocks via inode pपुनः_स्मृति or/and locality group
 * pपुनः_स्मृति then we look at the buddy cache. The buddy cache is represented
 * by ext4_sb_info.s_buddy_cache (काष्ठा inode) whose file offset माला_लो
 * mapped to the buddy and biपंचांगap inक्रमmation regarding dअगरferent
 * groups. The buddy inक्रमmation is attached to buddy cache inode so that
 * we can access them through the page cache. The inक्रमmation regarding
 * each group is loaded via ext4_mb_load_buddy.  The inक्रमmation involve
 * block biपंचांगap and buddy inक्रमmation. The inक्रमmation are stored in the
 * inode as:
 *
 *  अणु                        page                        पूर्ण
 *  [ group 0 biपंचांगap][ group 0 buddy] [group 1][ group 1]...
 *
 *
 * one block each क्रम biपंचांगap and buddy inक्रमmation.  So क्रम each group we
 * take up 2 blocks. A page can contain blocks_per_page (PAGE_SIZE /
 * blocksize) blocks.  So it can have inक्रमmation regarding groups_per_page
 * which is blocks_per_page/2
 *
 * The buddy cache inode is not stored on disk. The inode is thrown
 * away when the fileप्रणाली is unmounted.
 *
 * We look क्रम count number of blocks in the buddy cache. If we were able
 * to locate that many मुक्त blocks we वापस with additional inक्रमmation
 * regarding rest of the contiguous physical block available
 *
 * Beक्रमe allocating blocks via buddy cache we normalize the request
 * blocks. This ensure we ask क्रम more blocks that we needed. The extra
 * blocks that we get after allocation is added to the respective pपुनः_स्मृति
 * list. In हाल of inode pपुनः_स्मृतिation we follow a list of heuristics
 * based on file size. This can be found in ext4_mb_normalize_request. If
 * we are करोing a group pपुनः_स्मृति we try to normalize the request to
 * sbi->s_mb_group_pपुनः_स्मृति.  The शेष value of s_mb_group_pपुनः_स्मृति is
 * dependent on the cluster size; क्रम non-bigalloc file प्रणालीs, it is
 * 512 blocks. This can be tuned via
 * /sys/fs/ext4/<partition>/mb_group_pपुनः_स्मृति. The value is represented in
 * terms of number of blocks. If we have mounted the file प्रणाली with -O
 * stripe=<value> option the group pपुनः_स्मृति request is normalized to the
 * smallest multiple of the stripe value (sbi->s_stripe) which is
 * greater than the शेष mb_group_pपुनः_स्मृति.
 *
 * If "mb_optimize_scan" mount option is set, we मुख्यtain in memory group info
 * काष्ठाures in two data काष्ठाures:
 *
 * 1) Array of largest मुक्त order lists (sbi->s_mb_largest_मुक्त_orders)
 *
 *    Locking: sbi->s_mb_largest_मुक्त_orders_locks(array of rw locks)
 *
 *    This is an array of lists where the index in the array represents the
 *    largest मुक्त order in the buddy biपंचांगap of the participating group infos of
 *    that list. So, there are exactly MB_NUM_ORDERS(sb) (which means total
 *    number of buddy biपंचांगap orders possible) number of lists. Group-infos are
 *    placed in appropriate lists.
 *
 * 2) Average fragment size rb tree (sbi->s_mb_avg_fragment_size_root)
 *
 *    Locking: sbi->s_mb_rb_lock (rwlock)
 *
 *    This is a red black tree consisting of group infos and the tree is sorted
 *    by average fragment sizes (which is calculated as ext4_group_info->bb_मुक्त
 *    / ext4_group_info->bb_fragments).
 *
 * When "mb_optimize_scan" mount option is set, mballoc consults the above data
 * काष्ठाures to decide the order in which groups are to be traversed क्रम
 * fulfilling an allocation request.
 *
 * At CR = 0, we look क्रम groups which have the largest_मुक्त_order >= the order
 * of the request. We directly look at the largest मुक्त order list in the data
 * काष्ठाure (1) above where largest_मुक्त_order = order of the request. If that
 * list is empty, we look at reमुख्यing list in the increasing order of
 * largest_मुक्त_order. This allows us to perक्रमm CR = 0 lookup in O(1) समय.
 *
 * At CR = 1, we only consider groups where average fragment size > request
 * size. So, we lookup a group which has average fragment size just above or
 * equal to request size using our rb tree (data काष्ठाure 2) in O(log N) समय.
 *
 * If "mb_optimize_scan" mount option is not set, mballoc traverses groups in
 * linear order which requires O(N) search समय क्रम each CR 0 and CR 1 phase.
 *
 * The regular allocator (using the buddy cache) supports a few tunables.
 *
 * /sys/fs/ext4/<partition>/mb_min_to_scan
 * /sys/fs/ext4/<partition>/mb_max_to_scan
 * /sys/fs/ext4/<partition>/mb_order2_req
 * /sys/fs/ext4/<partition>/mb_linear_limit
 *
 * The regular allocator uses buddy scan only अगर the request len is घातer of
 * 2 blocks and the order of allocation is >= sbi->s_mb_order2_reqs. The
 * value of s_mb_order2_reqs can be tuned via
 * /sys/fs/ext4/<partition>/mb_order2_req.  If the request len is equal to
 * stripe size (sbi->s_stripe), we try to search क्रम contiguous block in
 * stripe size. This should result in better allocation on RAID setups. If
 * not, we search in the specअगरic group using biपंचांगap क्रम best extents. The
 * tunable min_to_scan and max_to_scan control the behaviour here.
 * min_to_scan indicate how दीर्घ the mballoc __must__ look क्रम a best
 * extent and max_to_scan indicates how दीर्घ the mballoc __can__ look क्रम a
 * best extent in the found extents. Searching क्रम the blocks starts with
 * the group specअगरied as the goal value in allocation context via
 * ac_g_ex. Each group is first checked based on the criteria whether it
 * can be used क्रम allocation. ext4_mb_good_group explains how the groups are
 * checked.
 *
 * When "mb_optimize_scan" is turned on, as mentioned above, the groups may not
 * get traversed linearly. That may result in subsequent allocations being not
 * बंद to each other. And so, the underlying device may get filled up in a
 * non-linear fashion. While that may not matter on non-rotational devices, क्रम
 * rotational devices that may result in higher seek बार. "mb_linear_limit"
 * tells mballoc how many groups mballoc should search linearly beक्रमe
 * perक्रमming consulting above data काष्ठाures क्रम more efficient lookups. For
 * non rotational devices, this value शेषs to 0 and क्रम rotational devices
 * this is set to MB_DEFAULT_LINEAR_LIMIT.
 *
 * Both the pपुनः_स्मृति space are getting populated as above. So क्रम the first
 * request we will hit the buddy cache which will result in this pपुनः_स्मृति
 * space getting filled. The pपुनः_स्मृति space is then later used क्रम the
 * subsequent request.
 */

/*
 * mballoc operates on the following data:
 *  - on-disk biपंचांगap
 *  - in-core buddy (actually includes buddy and biपंचांगap)
 *  - pपुनः_स्मृतिation descriptors (PAs)
 *
 * there are two types of pपुनः_स्मृतिations:
 *  - inode
 *    assiged to specअगरic inode and can be used क्रम this inode only.
 *    it describes part of inode's space pपुनः_स्मृतिated to specअगरic
 *    physical blocks. any block from that pपुनः_स्मृतिated can be used
 *    independent. the descriptor just tracks number of blocks left
 *    unused. so, beक्रमe taking some block from descriptor, one must
 *    make sure corresponded logical block isn't allocated yet. this
 *    also means that मुक्तing any block within descriptor's range
 *    must discard all pपुनः_स्मृतिated blocks.
 *  - locality group
 *    asचिन्हित to specअगरic locality group which करोes not translate to
 *    permanent set of inodes: inode can join and leave group. space
 *    from this type of pपुनः_स्मृतिation can be used क्रम any inode. thus
 *    it's consumed from the beginning to the end.
 *
 * relation between them can be expressed as:
 *    in-core buddy = on-disk biपंचांगap + pपुनः_स्मृतिation descriptors
 *
 * this mean blocks mballoc considers used are:
 *  - allocated blocks (persistent)
 *  - pपुनः_स्मृतिated blocks (non-persistent)
 *
 * consistency in mballoc world means that at any समय a block is either
 * मुक्त or used in ALL काष्ठाures. notice: "any time" should not be पढ़ो
 * literally -- समय is discrete and delimited by locks.
 *
 *  to keep it simple, we करोn't use block numbers, instead we count number of
 *  blocks: how many blocks marked used/मुक्त in on-disk biपंचांगap, buddy and PA.
 *
 * all operations can be expressed as:
 *  - init buddy:			buddy = on-disk + PAs
 *  - new PA:				buddy += N; PA = N
 *  - use inode PA:			on-disk += N; PA -= N
 *  - discard inode PA			buddy -= on-disk - PA; PA = 0
 *  - use locality group PA		on-disk += N; PA -= N
 *  - discard locality group PA		buddy -= PA; PA = 0
 *  note: 'buddy -= on-disk - PA' is used to show that on-disk biपंचांगap
 *        is used in real operation because we can't know actual used
 *        bits from PA, only from on-disk biपंचांगap
 *
 * अगर we follow this strict logic, then all operations above should be atomic.
 * given some of them can block, we'd have to use something like semaphores
 * समाप्तing perक्रमmance on high-end SMP hardware. let's try to relax it using
 * the following knowledge:
 *  1) अगर buddy is referenced, it's alपढ़ोy initialized
 *  2) जबतक block is used in buddy and the buddy is referenced,
 *     nobody can re-allocate that block
 *  3) we work on biपंचांगaps and '+' actually means 'set bits'. अगर on-disk has
 *     bit set and PA claims same block, it's OK. IOW, one can set bit in
 *     on-disk biपंचांगap अगर buddy has same bit set or/and PA covers corresponded
 *     block
 *
 * so, now we're building a concurrency table:
 *  - init buddy vs.
 *    - new PA
 *      blocks क्रम PA are allocated in the buddy, buddy must be referenced
 *      until PA is linked to allocation group to aव्योम concurrent buddy init
 *    - use inode PA
 *      we need to make sure that either on-disk biपंचांगap or PA has uptodate data
 *      given (3) we care that PA-=N operation करोesn't पूर्णांकerfere with init
 *    - discard inode PA
 *      the simplest way would be to have buddy initialized by the discard
 *    - use locality group PA
 *      again PA-=N must be serialized with init
 *    - discard locality group PA
 *      the simplest way would be to have buddy initialized by the discard
 *  - new PA vs.
 *    - use inode PA
 *      i_data_sem serializes them
 *    - discard inode PA
 *      discard process must रुको until PA isn't used by another process
 *    - use locality group PA
 *      some mutex should serialize them
 *    - discard locality group PA
 *      discard process must रुको until PA isn't used by another process
 *  - use inode PA
 *    - use inode PA
 *      i_data_sem or another mutex should serializes them
 *    - discard inode PA
 *      discard process must रुको until PA isn't used by another process
 *    - use locality group PA
 *      nothing wrong here -- they're dअगरferent PAs covering dअगरferent blocks
 *    - discard locality group PA
 *      discard process must रुको until PA isn't used by another process
 *
 * now we're पढ़ोy to make few consequences:
 *  - PA is referenced and जबतक it is no discard is possible
 *  - PA is referenced until block isn't marked in on-disk biपंचांगap
 *  - PA changes only after on-disk biपंचांगap
 *  - discard must not compete with init. either init is करोne beक्रमe
 *    any discard or they're serialized somehow
 *  - buddy init as sum of on-disk biपंचांगap and PAs is करोne atomically
 *
 * a special हाल when we've used PA to emptiness. no need to modअगरy buddy
 * in this हाल, but we should care about concurrent init
 *
 */

 /*
 * Logic in few words:
 *
 *  - allocation:
 *    load group
 *    find blocks
 *    mark bits in on-disk biपंचांगap
 *    release group
 *
 *  - use pपुनः_स्मृतिation:
 *    find proper PA (per-inode or group)
 *    load group
 *    mark bits in on-disk biपंचांगap
 *    release group
 *    release PA
 *
 *  - मुक्त:
 *    load group
 *    mark bits in on-disk biपंचांगap
 *    release group
 *
 *  - discard pपुनः_स्मृतिations in group:
 *    mark PAs deleted
 *    move them onto local list
 *    load on-disk biपंचांगap
 *    load group
 *    हटाओ PA from object (inode or locality group)
 *    mark मुक्त blocks in-core
 *
 *  - discard inode's pपुनः_स्मृतिations:
 */

/*
 * Locking rules
 *
 * Locks:
 *  - bitlock on a group	(group)
 *  - object (inode/locality)	(object)
 *  - per-pa lock		(pa)
 *  - cr0 lists lock		(cr0)
 *  - cr1 tree lock		(cr1)
 *
 * Paths:
 *  - new pa
 *    object
 *    group
 *
 *  - find and use pa:
 *    pa
 *
 *  - release consumed pa:
 *    pa
 *    group
 *    object
 *
 *  - generate in-core biपंचांगap:
 *    group
 *        pa
 *
 *  - discard all क्रम given object (inode, locality group):
 *    object
 *        pa
 *    group
 *
 *  - discard all क्रम given group:
 *    group
 *        pa
 *    group
 *        object
 *
 *  - allocation path (ext4_mb_regular_allocator)
 *    group
 *    cr0/cr1
 */
अटल काष्ठा kmem_cache *ext4_pspace_cachep;
अटल काष्ठा kmem_cache *ext4_ac_cachep;
अटल काष्ठा kmem_cache *ext4_मुक्त_data_cachep;

/* We create slab caches क्रम groupinfo data काष्ठाures based on the
 * superblock block size.  There will be one per mounted fileप्रणाली क्रम
 * each unique s_blocksize_bits */
#घोषणा NR_GRPINFO_CACHES 8
अटल काष्ठा kmem_cache *ext4_groupinfo_caches[NR_GRPINFO_CACHES];

अटल स्थिर अक्षर * स्थिर ext4_groupinfo_slab_names[NR_GRPINFO_CACHES] = अणु
	"ext4_groupinfo_1k", "ext4_groupinfo_2k", "ext4_groupinfo_4k",
	"ext4_groupinfo_8k", "ext4_groupinfo_16k", "ext4_groupinfo_32k",
	"ext4_groupinfo_64k", "ext4_groupinfo_128k"
पूर्ण;

अटल व्योम ext4_mb_generate_from_pa(काष्ठा super_block *sb, व्योम *biपंचांगap,
					ext4_group_t group);
अटल व्योम ext4_mb_generate_from_मुक्तlist(काष्ठा super_block *sb, व्योम *biपंचांगap,
						ext4_group_t group);
अटल व्योम ext4_mb_new_pपुनः_स्मृतिation(काष्ठा ext4_allocation_context *ac);

अटल bool ext4_mb_good_group(काष्ठा ext4_allocation_context *ac,
			       ext4_group_t group, पूर्णांक cr);

/*
 * The algorithm using this percpu seq counter goes below:
 * 1. We sample the percpu discard_pa_seq counter beक्रमe trying क्रम block
 *    allocation in ext4_mb_new_blocks().
 * 2. We increment this percpu discard_pa_seq counter when we either allocate
 *    or मुक्त these blocks i.e. जबतक marking those blocks as used/मुक्त in
 *    mb_mark_used()/mb_मुक्त_blocks().
 * 3. We also increment this percpu seq counter when we successfully identअगरy
 *    that the bb_pपुनः_स्मृति_list is not empty and hence proceed क्रम discarding
 *    of those PAs inside ext4_mb_discard_group_pपुनः_स्मृतिations().
 *
 * Now to make sure that the regular fast path of block allocation is not
 * affected, as a small optimization we only sample the percpu seq counter
 * on that cpu. Only when the block allocation fails and when मुक्तd blocks
 * found were 0, that is when we sample percpu seq counter क्रम all cpus using
 * below function ext4_get_discard_pa_seq_sum(). This happens after making
 * sure that all the PAs on grp->bb_pपुनः_स्मृति_list got मुक्तd or अगर it's empty.
 */
अटल DEFINE_PER_CPU(u64, discard_pa_seq);
अटल अंतरभूत u64 ext4_get_discard_pa_seq_sum(व्योम)
अणु
	पूर्णांक __cpu;
	u64 __seq = 0;

	क्रम_each_possible_cpu(__cpu)
		__seq += per_cpu(discard_pa_seq, __cpu);
	वापस __seq;
पूर्ण

अटल अंतरभूत व्योम *mb_correct_addr_and_bit(पूर्णांक *bit, व्योम *addr)
अणु
#अगर BITS_PER_LONG == 64
	*bit += ((अचिन्हित दीर्घ) addr & 7UL) << 3;
	addr = (व्योम *) ((अचिन्हित दीर्घ) addr & ~7UL);
#या_अगर BITS_PER_LONG == 32
	*bit += ((अचिन्हित दीर्घ) addr & 3UL) << 3;
	addr = (व्योम *) ((अचिन्हित दीर्घ) addr & ~3UL);
#अन्यथा
#त्रुटि "how many bits you are?!"
#पूर्ण_अगर
	वापस addr;
पूर्ण

अटल अंतरभूत पूर्णांक mb_test_bit(पूर्णांक bit, व्योम *addr)
अणु
	/*
	 * ext4_test_bit on architecture like घातerpc
	 * needs अचिन्हित दीर्घ aligned address
	 */
	addr = mb_correct_addr_and_bit(&bit, addr);
	वापस ext4_test_bit(bit, addr);
पूर्ण

अटल अंतरभूत व्योम mb_set_bit(पूर्णांक bit, व्योम *addr)
अणु
	addr = mb_correct_addr_and_bit(&bit, addr);
	ext4_set_bit(bit, addr);
पूर्ण

अटल अंतरभूत व्योम mb_clear_bit(पूर्णांक bit, व्योम *addr)
अणु
	addr = mb_correct_addr_and_bit(&bit, addr);
	ext4_clear_bit(bit, addr);
पूर्ण

अटल अंतरभूत पूर्णांक mb_test_and_clear_bit(पूर्णांक bit, व्योम *addr)
अणु
	addr = mb_correct_addr_and_bit(&bit, addr);
	वापस ext4_test_and_clear_bit(bit, addr);
पूर्ण

अटल अंतरभूत पूर्णांक mb_find_next_zero_bit(व्योम *addr, पूर्णांक max, पूर्णांक start)
अणु
	पूर्णांक fix = 0, ret, पंचांगpmax;
	addr = mb_correct_addr_and_bit(&fix, addr);
	पंचांगpmax = max + fix;
	start += fix;

	ret = ext4_find_next_zero_bit(addr, पंचांगpmax, start) - fix;
	अगर (ret > max)
		वापस max;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक mb_find_next_bit(व्योम *addr, पूर्णांक max, पूर्णांक start)
अणु
	पूर्णांक fix = 0, ret, पंचांगpmax;
	addr = mb_correct_addr_and_bit(&fix, addr);
	पंचांगpmax = max + fix;
	start += fix;

	ret = ext4_find_next_bit(addr, पंचांगpmax, start) - fix;
	अगर (ret > max)
		वापस max;
	वापस ret;
पूर्ण

अटल व्योम *mb_find_buddy(काष्ठा ext4_buddy *e4b, पूर्णांक order, पूर्णांक *max)
अणु
	अक्षर *bb;

	BUG_ON(e4b->bd_biपंचांगap == e4b->bd_buddy);
	BUG_ON(max == शून्य);

	अगर (order > e4b->bd_blkbits + 1) अणु
		*max = 0;
		वापस शून्य;
	पूर्ण

	/* at order 0 we see each particular block */
	अगर (order == 0) अणु
		*max = 1 << (e4b->bd_blkbits + 3);
		वापस e4b->bd_biपंचांगap;
	पूर्ण

	bb = e4b->bd_buddy + EXT4_SB(e4b->bd_sb)->s_mb_offsets[order];
	*max = EXT4_SB(e4b->bd_sb)->s_mb_maxs[order];

	वापस bb;
पूर्ण

#अगर_घोषित DOUBLE_CHECK
अटल व्योम mb_मुक्त_blocks_द्विगुन(काष्ठा inode *inode, काष्ठा ext4_buddy *e4b,
			   पूर्णांक first, पूर्णांक count)
अणु
	पूर्णांक i;
	काष्ठा super_block *sb = e4b->bd_sb;

	अगर (unlikely(e4b->bd_info->bb_biपंचांगap == शून्य))
		वापस;
	निश्चित_spin_locked(ext4_group_lock_ptr(sb, e4b->bd_group));
	क्रम (i = 0; i < count; i++) अणु
		अगर (!mb_test_bit(first + i, e4b->bd_info->bb_biपंचांगap)) अणु
			ext4_fsblk_t blocknr;

			blocknr = ext4_group_first_block_no(sb, e4b->bd_group);
			blocknr += EXT4_C2B(EXT4_SB(sb), first + i);
			ext4_grp_locked_error(sb, e4b->bd_group,
					      inode ? inode->i_ino : 0,
					      blocknr,
					      "freeing block already freed "
					      "(bit %u)",
					      first + i);
			ext4_mark_group_biपंचांगap_corrupted(sb, e4b->bd_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		पूर्ण
		mb_clear_bit(first + i, e4b->bd_info->bb_biपंचांगap);
	पूर्ण
पूर्ण

अटल व्योम mb_mark_used_द्विगुन(काष्ठा ext4_buddy *e4b, पूर्णांक first, पूर्णांक count)
अणु
	पूर्णांक i;

	अगर (unlikely(e4b->bd_info->bb_biपंचांगap == शून्य))
		वापस;
	निश्चित_spin_locked(ext4_group_lock_ptr(e4b->bd_sb, e4b->bd_group));
	क्रम (i = 0; i < count; i++) अणु
		BUG_ON(mb_test_bit(first + i, e4b->bd_info->bb_biपंचांगap));
		mb_set_bit(first + i, e4b->bd_info->bb_biपंचांगap);
	पूर्ण
पूर्ण

अटल व्योम mb_cmp_biपंचांगaps(काष्ठा ext4_buddy *e4b, व्योम *biपंचांगap)
अणु
	अगर (unlikely(e4b->bd_info->bb_biपंचांगap == शून्य))
		वापस;
	अगर (स_भेद(e4b->bd_info->bb_biपंचांगap, biपंचांगap, e4b->bd_sb->s_blocksize)) अणु
		अचिन्हित अक्षर *b1, *b2;
		पूर्णांक i;
		b1 = (अचिन्हित अक्षर *) e4b->bd_info->bb_biपंचांगap;
		b2 = (अचिन्हित अक्षर *) biपंचांगap;
		क्रम (i = 0; i < e4b->bd_sb->s_blocksize; i++) अणु
			अगर (b1[i] != b2[i]) अणु
				ext4_msg(e4b->bd_sb, KERN_ERR,
					 "corruption in group %u "
					 "at byte %u(%u): %x in copy != %x "
					 "on disk/prealloc",
					 e4b->bd_group, i, i * 8, b1[i], b2[i]);
				BUG();
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mb_group_bb_biपंचांगap_alloc(काष्ठा super_block *sb,
			काष्ठा ext4_group_info *grp, ext4_group_t group)
अणु
	काष्ठा buffer_head *bh;

	grp->bb_biपंचांगap = kदो_स्मृति(sb->s_blocksize, GFP_NOFS);
	अगर (!grp->bb_biपंचांगap)
		वापस;

	bh = ext4_पढ़ो_block_biपंचांगap(sb, group);
	अगर (IS_ERR_OR_शून्य(bh)) अणु
		kमुक्त(grp->bb_biपंचांगap);
		grp->bb_biपंचांगap = शून्य;
		वापस;
	पूर्ण

	स_नकल(grp->bb_biपंचांगap, bh->b_data, sb->s_blocksize);
	put_bh(bh);
पूर्ण

अटल व्योम mb_group_bb_biपंचांगap_मुक्त(काष्ठा ext4_group_info *grp)
अणु
	kमुक्त(grp->bb_biपंचांगap);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम mb_मुक्त_blocks_द्विगुन(काष्ठा inode *inode,
				काष्ठा ext4_buddy *e4b, पूर्णांक first, पूर्णांक count)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम mb_mark_used_द्विगुन(काष्ठा ext4_buddy *e4b,
						पूर्णांक first, पूर्णांक count)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम mb_cmp_biपंचांगaps(काष्ठा ext4_buddy *e4b, व्योम *biपंचांगap)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम mb_group_bb_biपंचांगap_alloc(काष्ठा super_block *sb,
			काष्ठा ext4_group_info *grp, ext4_group_t group)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम mb_group_bb_biपंचांगap_मुक्त(काष्ठा ext4_group_info *grp)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित AGGRESSIVE_CHECK

#घोषणा MB_CHECK_ASSERT(निश्चित)						\
करो अणु									\
	अगर (!(निश्चित)) अणु						\
		prपूर्णांकk(KERN_EMERG					\
			"Assertion failure in %s() at %s:%d: \"%s\"\n",	\
			function, file, line, # निश्चित);		\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

अटल पूर्णांक __mb_check_buddy(काष्ठा ext4_buddy *e4b, अक्षर *file,
				स्थिर अक्षर *function, पूर्णांक line)
अणु
	काष्ठा super_block *sb = e4b->bd_sb;
	पूर्णांक order = e4b->bd_blkbits + 1;
	पूर्णांक max;
	पूर्णांक max2;
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक k;
	पूर्णांक count;
	काष्ठा ext4_group_info *grp;
	पूर्णांक fragments = 0;
	पूर्णांक fstart;
	काष्ठा list_head *cur;
	व्योम *buddy;
	व्योम *buddy2;

	अगर (e4b->bd_info->bb_check_counter++ % 10)
		वापस 0;

	जबतक (order > 1) अणु
		buddy = mb_find_buddy(e4b, order, &max);
		MB_CHECK_ASSERT(buddy);
		buddy2 = mb_find_buddy(e4b, order - 1, &max2);
		MB_CHECK_ASSERT(buddy2);
		MB_CHECK_ASSERT(buddy != buddy2);
		MB_CHECK_ASSERT(max * 2 == max2);

		count = 0;
		क्रम (i = 0; i < max; i++) अणु

			अगर (mb_test_bit(i, buddy)) अणु
				/* only single bit in buddy2 may be 1 */
				अगर (!mb_test_bit(i << 1, buddy2)) अणु
					MB_CHECK_ASSERT(
						mb_test_bit((i<<1)+1, buddy2));
				पूर्ण अन्यथा अगर (!mb_test_bit((i << 1) + 1, buddy2)) अणु
					MB_CHECK_ASSERT(
						mb_test_bit(i << 1, buddy2));
				पूर्ण
				जारी;
			पूर्ण

			/* both bits in buddy2 must be 1 */
			MB_CHECK_ASSERT(mb_test_bit(i << 1, buddy2));
			MB_CHECK_ASSERT(mb_test_bit((i << 1) + 1, buddy2));

			क्रम (j = 0; j < (1 << order); j++) अणु
				k = (i * (1 << order)) + j;
				MB_CHECK_ASSERT(
					!mb_test_bit(k, e4b->bd_biपंचांगap));
			पूर्ण
			count++;
		पूर्ण
		MB_CHECK_ASSERT(e4b->bd_info->bb_counters[order] == count);
		order--;
	पूर्ण

	fstart = -1;
	buddy = mb_find_buddy(e4b, 0, &max);
	क्रम (i = 0; i < max; i++) अणु
		अगर (!mb_test_bit(i, buddy)) अणु
			MB_CHECK_ASSERT(i >= e4b->bd_info->bb_first_मुक्त);
			अगर (fstart == -1) अणु
				fragments++;
				fstart = i;
			पूर्ण
			जारी;
		पूर्ण
		fstart = -1;
		/* check used bits only */
		क्रम (j = 0; j < e4b->bd_blkbits + 1; j++) अणु
			buddy2 = mb_find_buddy(e4b, j, &max2);
			k = i >> j;
			MB_CHECK_ASSERT(k < max2);
			MB_CHECK_ASSERT(mb_test_bit(k, buddy2));
		पूर्ण
	पूर्ण
	MB_CHECK_ASSERT(!EXT4_MB_GRP_NEED_INIT(e4b->bd_info));
	MB_CHECK_ASSERT(e4b->bd_info->bb_fragments == fragments);

	grp = ext4_get_group_info(sb, e4b->bd_group);
	list_क्रम_each(cur, &grp->bb_pपुनः_स्मृति_list) अणु
		ext4_group_t groupnr;
		काष्ठा ext4_pपुनः_स्मृति_space *pa;
		pa = list_entry(cur, काष्ठा ext4_pपुनः_स्मृति_space, pa_group_list);
		ext4_get_group_no_and_offset(sb, pa->pa_pstart, &groupnr, &k);
		MB_CHECK_ASSERT(groupnr == e4b->bd_group);
		क्रम (i = 0; i < pa->pa_len; i++)
			MB_CHECK_ASSERT(mb_test_bit(k + i, buddy));
	पूर्ण
	वापस 0;
पूर्ण
#अघोषित MB_CHECK_ASSERT
#घोषणा mb_check_buddy(e4b) __mb_check_buddy(e4b,	\
					__खाता__, __func__, __LINE__)
#अन्यथा
#घोषणा mb_check_buddy(e4b)
#पूर्ण_अगर

/*
 * Divide blocks started from @first with length @len पूर्णांकo
 * smaller chunks with घातer of 2 blocks.
 * Clear the bits in biपंचांगap which the blocks of the chunk(s) covered,
 * then increase bb_counters[] क्रम corresponded chunk size.
 */
अटल व्योम ext4_mb_mark_मुक्त_simple(काष्ठा super_block *sb,
				व्योम *buddy, ext4_grpblk_t first, ext4_grpblk_t len,
					काष्ठा ext4_group_info *grp)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_grpblk_t min;
	ext4_grpblk_t max;
	ext4_grpblk_t chunk;
	अचिन्हित पूर्णांक border;

	BUG_ON(len > EXT4_CLUSTERS_PER_GROUP(sb));

	border = 2 << sb->s_blocksize_bits;

	जबतक (len > 0) अणु
		/* find how many blocks can be covered since this position */
		max = ffs(first | border) - 1;

		/* find how many blocks of घातer 2 we need to mark */
		min = fls(len) - 1;

		अगर (max < min)
			min = max;
		chunk = 1 << min;

		/* mark multiblock chunks only */
		grp->bb_counters[min]++;
		अगर (min > 0)
			mb_clear_bit(first >> min,
				     buddy + sbi->s_mb_offsets[min]);

		len -= chunk;
		first += chunk;
	पूर्ण
पूर्ण

अटल व्योम ext4_mb_rb_insert(काष्ठा rb_root *root, काष्ठा rb_node *new,
			पूर्णांक (*cmp)(काष्ठा rb_node *, काष्ठा rb_node *))
अणु
	काष्ठा rb_node **iter = &root->rb_node, *parent = शून्य;

	जबतक (*iter) अणु
		parent = *iter;
		अगर (cmp(new, *iter) > 0)
			iter = &((*iter)->rb_left);
		अन्यथा
			iter = &((*iter)->rb_right);
	पूर्ण

	rb_link_node(new, parent, iter);
	rb_insert_color(new, root);
पूर्ण

अटल पूर्णांक
ext4_mb_avg_fragment_size_cmp(काष्ठा rb_node *rb1, काष्ठा rb_node *rb2)
अणु
	काष्ठा ext4_group_info *grp1 = rb_entry(rb1,
						काष्ठा ext4_group_info,
						bb_avg_fragment_size_rb);
	काष्ठा ext4_group_info *grp2 = rb_entry(rb2,
						काष्ठा ext4_group_info,
						bb_avg_fragment_size_rb);
	पूर्णांक num_frags_1, num_frags_2;

	num_frags_1 = grp1->bb_fragments ?
		grp1->bb_मुक्त / grp1->bb_fragments : 0;
	num_frags_2 = grp2->bb_fragments ?
		grp2->bb_मुक्त / grp2->bb_fragments : 0;

	वापस (num_frags_2 - num_frags_1);
पूर्ण

/*
 * Reinsert grpinfo पूर्णांकo the avg_fragment_size tree with new average
 * fragment size.
 */
अटल व्योम
mb_update_avg_fragment_size(काष्ठा super_block *sb, काष्ठा ext4_group_info *grp)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (!test_opt2(sb, MB_OPTIMIZE_SCAN) || grp->bb_मुक्त == 0)
		वापस;

	ग_लिखो_lock(&sbi->s_mb_rb_lock);
	अगर (!RB_EMPTY_NODE(&grp->bb_avg_fragment_size_rb)) अणु
		rb_erase(&grp->bb_avg_fragment_size_rb,
				&sbi->s_mb_avg_fragment_size_root);
		RB_CLEAR_NODE(&grp->bb_avg_fragment_size_rb);
	पूर्ण

	ext4_mb_rb_insert(&sbi->s_mb_avg_fragment_size_root,
		&grp->bb_avg_fragment_size_rb,
		ext4_mb_avg_fragment_size_cmp);
	ग_लिखो_unlock(&sbi->s_mb_rb_lock);
पूर्ण

/*
 * Choose next group by traversing largest_मुक्त_order lists. Updates *new_cr अगर
 * cr level needs an update.
 */
अटल व्योम ext4_mb_choose_next_group_cr0(काष्ठा ext4_allocation_context *ac,
			पूर्णांक *new_cr, ext4_group_t *group, ext4_group_t ngroups)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);
	काष्ठा ext4_group_info *iter, *grp;
	पूर्णांक i;

	अगर (ac->ac_status == AC_STATUS_FOUND)
		वापस;

	अगर (unlikely(sbi->s_mb_stats && ac->ac_flags & EXT4_MB_CR0_OPTIMIZED))
		atomic_inc(&sbi->s_bal_cr0_bad_suggestions);

	grp = शून्य;
	क्रम (i = ac->ac_2order; i < MB_NUM_ORDERS(ac->ac_sb); i++) अणु
		अगर (list_empty(&sbi->s_mb_largest_मुक्त_orders[i]))
			जारी;
		पढ़ो_lock(&sbi->s_mb_largest_मुक्त_orders_locks[i]);
		अगर (list_empty(&sbi->s_mb_largest_मुक्त_orders[i])) अणु
			पढ़ो_unlock(&sbi->s_mb_largest_मुक्त_orders_locks[i]);
			जारी;
		पूर्ण
		grp = शून्य;
		list_क्रम_each_entry(iter, &sbi->s_mb_largest_मुक्त_orders[i],
				    bb_largest_मुक्त_order_node) अणु
			अगर (sbi->s_mb_stats)
				atomic64_inc(&sbi->s_bal_cX_groups_considered[0]);
			अगर (likely(ext4_mb_good_group(ac, iter->bb_group, 0))) अणु
				grp = iter;
				अवरोध;
			पूर्ण
		पूर्ण
		पढ़ो_unlock(&sbi->s_mb_largest_मुक्त_orders_locks[i]);
		अगर (grp)
			अवरोध;
	पूर्ण

	अगर (!grp) अणु
		/* Increment cr and search again */
		*new_cr = 1;
	पूर्ण अन्यथा अणु
		*group = grp->bb_group;
		ac->ac_last_optimal_group = *group;
		ac->ac_flags |= EXT4_MB_CR0_OPTIMIZED;
	पूर्ण
पूर्ण

/*
 * Choose next group by traversing average fragment size tree. Updates *new_cr
 * अगर cr lvel needs an update. Sets EXT4_MB_SEARCH_NEXT_LINEAR to indicate that
 * the linear search should जारी क्रम one iteration since there's lock
 * contention on the rb tree lock.
 */
अटल व्योम ext4_mb_choose_next_group_cr1(काष्ठा ext4_allocation_context *ac,
		पूर्णांक *new_cr, ext4_group_t *group, ext4_group_t ngroups)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);
	पूर्णांक avg_fragment_size, best_so_far;
	काष्ठा rb_node *node, *found;
	काष्ठा ext4_group_info *grp;

	/*
	 * If there is contention on the lock, instead of रुकोing क्रम the lock
	 * to become available, just जारी searching lineraly. We'll resume
	 * our rb tree search later starting at ac->ac_last_optimal_group.
	 */
	अगर (!पढ़ो_trylock(&sbi->s_mb_rb_lock)) अणु
		ac->ac_flags |= EXT4_MB_SEARCH_NEXT_LINEAR;
		वापस;
	पूर्ण

	अगर (unlikely(ac->ac_flags & EXT4_MB_CR1_OPTIMIZED)) अणु
		अगर (sbi->s_mb_stats)
			atomic_inc(&sbi->s_bal_cr1_bad_suggestions);
		/* We have found something at CR 1 in the past */
		grp = ext4_get_group_info(ac->ac_sb, ac->ac_last_optimal_group);
		क्रम (found = rb_next(&grp->bb_avg_fragment_size_rb); found != शून्य;
		     found = rb_next(found)) अणु
			grp = rb_entry(found, काष्ठा ext4_group_info,
				       bb_avg_fragment_size_rb);
			अगर (sbi->s_mb_stats)
				atomic64_inc(&sbi->s_bal_cX_groups_considered[1]);
			अगर (likely(ext4_mb_good_group(ac, grp->bb_group, 1)))
				अवरोध;
		पूर्ण
		जाओ करोne;
	पूर्ण

	node = sbi->s_mb_avg_fragment_size_root.rb_node;
	best_so_far = 0;
	found = शून्य;

	जबतक (node) अणु
		grp = rb_entry(node, काष्ठा ext4_group_info,
			       bb_avg_fragment_size_rb);
		avg_fragment_size = 0;
		अगर (ext4_mb_good_group(ac, grp->bb_group, 1)) अणु
			avg_fragment_size = grp->bb_fragments ?
				grp->bb_मुक्त / grp->bb_fragments : 0;
			अगर (!best_so_far || avg_fragment_size < best_so_far) अणु
				best_so_far = avg_fragment_size;
				found = node;
			पूर्ण
		पूर्ण
		अगर (avg_fragment_size > ac->ac_g_ex.fe_len)
			node = node->rb_right;
		अन्यथा
			node = node->rb_left;
	पूर्ण

करोne:
	अगर (found) अणु
		grp = rb_entry(found, काष्ठा ext4_group_info,
			       bb_avg_fragment_size_rb);
		*group = grp->bb_group;
		ac->ac_flags |= EXT4_MB_CR1_OPTIMIZED;
	पूर्ण अन्यथा अणु
		*new_cr = 2;
	पूर्ण

	पढ़ो_unlock(&sbi->s_mb_rb_lock);
	ac->ac_last_optimal_group = *group;
पूर्ण

अटल अंतरभूत पूर्णांक should_optimize_scan(काष्ठा ext4_allocation_context *ac)
अणु
	अगर (unlikely(!test_opt2(ac->ac_sb, MB_OPTIMIZE_SCAN)))
		वापस 0;
	अगर (ac->ac_criteria >= 2)
		वापस 0;
	अगर (ext4_test_inode_flag(ac->ac_inode, EXT4_INODE_EXTENTS))
		वापस 0;
	वापस 1;
पूर्ण

/*
 * Return next linear group क्रम allocation. If linear traversal should not be
 * perक्रमmed, this function just वापसs the same group
 */
अटल पूर्णांक
next_linear_group(काष्ठा ext4_allocation_context *ac, पूर्णांक group, पूर्णांक ngroups)
अणु
	अगर (!should_optimize_scan(ac))
		जाओ inc_and_वापस;

	अगर (ac->ac_groups_linear_reमुख्यing) अणु
		ac->ac_groups_linear_reमुख्यing--;
		जाओ inc_and_वापस;
	पूर्ण

	अगर (ac->ac_flags & EXT4_MB_SEARCH_NEXT_LINEAR) अणु
		ac->ac_flags &= ~EXT4_MB_SEARCH_NEXT_LINEAR;
		जाओ inc_and_वापस;
	पूर्ण

	वापस group;
inc_and_वापस:
	/*
	 * Artअगरicially restricted ngroups क्रम non-extent
	 * files makes group > ngroups possible on first loop.
	 */
	वापस group + 1 >= ngroups ? 0 : group + 1;
पूर्ण

/*
 * ext4_mb_choose_next_group: choose next group क्रम allocation.
 *
 * @ac        Allocation Context
 * @new_cr    This is an output parameter. If the there is no good group
 *            available at current CR level, this field is updated to indicate
 *            the new cr level that should be used.
 * @group     This is an input / output parameter. As an input it indicates the
 *            next group that the allocator पूर्णांकends to use क्रम allocation. As
 *            output, this field indicates the next group that should be used as
 *            determined by the optimization functions.
 * @ngroups   Total number of groups
 */
अटल व्योम ext4_mb_choose_next_group(काष्ठा ext4_allocation_context *ac,
		पूर्णांक *new_cr, ext4_group_t *group, ext4_group_t ngroups)
अणु
	*new_cr = ac->ac_criteria;

	अगर (!should_optimize_scan(ac) || ac->ac_groups_linear_reमुख्यing)
		वापस;

	अगर (*new_cr == 0) अणु
		ext4_mb_choose_next_group_cr0(ac, new_cr, group, ngroups);
	पूर्ण अन्यथा अगर (*new_cr == 1) अणु
		ext4_mb_choose_next_group_cr1(ac, new_cr, group, ngroups);
	पूर्ण अन्यथा अणु
		/*
		 * TODO: For CR=2, we can arrange groups in an rb tree sorted by
		 * bb_मुक्त. But until that happens, we should never come here.
		 */
		WARN_ON(1);
	पूर्ण
पूर्ण

/*
 * Cache the order of the largest मुक्त extent we have available in this block
 * group.
 */
अटल व्योम
mb_set_largest_मुक्त_order(काष्ठा super_block *sb, काष्ठा ext4_group_info *grp)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक i;

	अगर (test_opt2(sb, MB_OPTIMIZE_SCAN) && grp->bb_largest_मुक्त_order >= 0) अणु
		ग_लिखो_lock(&sbi->s_mb_largest_मुक्त_orders_locks[
					      grp->bb_largest_मुक्त_order]);
		list_del_init(&grp->bb_largest_मुक्त_order_node);
		ग_लिखो_unlock(&sbi->s_mb_largest_मुक्त_orders_locks[
					      grp->bb_largest_मुक्त_order]);
	पूर्ण
	grp->bb_largest_मुक्त_order = -1; /* uninit */

	क्रम (i = MB_NUM_ORDERS(sb) - 1; i >= 0; i--) अणु
		अगर (grp->bb_counters[i] > 0) अणु
			grp->bb_largest_मुक्त_order = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (test_opt2(sb, MB_OPTIMIZE_SCAN) &&
	    grp->bb_largest_मुक्त_order >= 0 && grp->bb_मुक्त) अणु
		ग_लिखो_lock(&sbi->s_mb_largest_मुक्त_orders_locks[
					      grp->bb_largest_मुक्त_order]);
		list_add_tail(&grp->bb_largest_मुक्त_order_node,
		      &sbi->s_mb_largest_मुक्त_orders[grp->bb_largest_मुक्त_order]);
		ग_लिखो_unlock(&sbi->s_mb_largest_मुक्त_orders_locks[
					      grp->bb_largest_मुक्त_order]);
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack
व्योम ext4_mb_generate_buddy(काष्ठा super_block *sb,
				व्योम *buddy, व्योम *biपंचांगap, ext4_group_t group)
अणु
	काष्ठा ext4_group_info *grp = ext4_get_group_info(sb, group);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_grpblk_t max = EXT4_CLUSTERS_PER_GROUP(sb);
	ext4_grpblk_t i = 0;
	ext4_grpblk_t first;
	ext4_grpblk_t len;
	अचिन्हित मुक्त = 0;
	अचिन्हित fragments = 0;
	अचिन्हित दीर्घ दीर्घ period = get_cycles();

	/* initialize buddy from biपंचांगap which is aggregation
	 * of on-disk biपंचांगap and pपुनः_स्मृतिations */
	i = mb_find_next_zero_bit(biपंचांगap, max, 0);
	grp->bb_first_मुक्त = i;
	जबतक (i < max) अणु
		fragments++;
		first = i;
		i = mb_find_next_bit(biपंचांगap, max, i);
		len = i - first;
		मुक्त += len;
		अगर (len > 1)
			ext4_mb_mark_मुक्त_simple(sb, buddy, first, len, grp);
		अन्यथा
			grp->bb_counters[0]++;
		अगर (i < max)
			i = mb_find_next_zero_bit(biपंचांगap, max, i);
	पूर्ण
	grp->bb_fragments = fragments;

	अगर (मुक्त != grp->bb_मुक्त) अणु
		ext4_grp_locked_error(sb, group, 0, 0,
				      "block bitmap and bg descriptor "
				      "inconsistent: %u vs %u free clusters",
				      मुक्त, grp->bb_मुक्त);
		/*
		 * If we पूर्णांकend to जारी, we consider group descriptor
		 * corrupt and update bb_मुक्त using biपंचांगap value
		 */
		grp->bb_मुक्त = मुक्त;
		ext4_mark_group_biपंचांगap_corrupted(sb, group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
	पूर्ण
	mb_set_largest_मुक्त_order(sb, grp);

	clear_bit(EXT4_GROUP_INFO_NEED_INIT_BIT, &(grp->bb_state));

	period = get_cycles() - period;
	atomic_inc(&sbi->s_mb_buddies_generated);
	atomic64_add(period, &sbi->s_mb_generation_समय);
	mb_update_avg_fragment_size(sb, grp);
पूर्ण

/* The buddy inक्रमmation is attached the buddy cache inode
 * क्रम convenience. The inक्रमmation regarding each group
 * is loaded via ext4_mb_load_buddy. The inक्रमmation involve
 * block biपंचांगap and buddy inक्रमmation. The inक्रमmation are
 * stored in the inode as
 *
 * अणु                        page                        पूर्ण
 * [ group 0 biपंचांगap][ group 0 buddy] [group 1][ group 1]...
 *
 *
 * one block each क्रम biपंचांगap and buddy inक्रमmation.
 * So क्रम each group we take up 2 blocks. A page can
 * contain blocks_per_page (PAGE_SIZE / blocksize)  blocks.
 * So it can have inक्रमmation regarding groups_per_page which
 * is blocks_per_page/2
 *
 * Locking note:  This routine takes the block group lock of all groups
 * क्रम this page; करो not hold this lock when calling this routine!
 */

अटल पूर्णांक ext4_mb_init_cache(काष्ठा page *page, अक्षर *incore, gfp_t gfp)
अणु
	ext4_group_t ngroups;
	पूर्णांक blocksize;
	पूर्णांक blocks_per_page;
	पूर्णांक groups_per_page;
	पूर्णांक err = 0;
	पूर्णांक i;
	ext4_group_t first_group, group;
	पूर्णांक first_block;
	काष्ठा super_block *sb;
	काष्ठा buffer_head *bhs;
	काष्ठा buffer_head **bh = शून्य;
	काष्ठा inode *inode;
	अक्षर *data;
	अक्षर *biपंचांगap;
	काष्ठा ext4_group_info *grinfo;

	inode = page->mapping->host;
	sb = inode->i_sb;
	ngroups = ext4_get_groups_count(sb);
	blocksize = i_blocksize(inode);
	blocks_per_page = PAGE_SIZE / blocksize;

	mb_debug(sb, "init page %lu\n", page->index);

	groups_per_page = blocks_per_page >> 1;
	अगर (groups_per_page == 0)
		groups_per_page = 1;

	/* allocate buffer_heads to पढ़ो biपंचांगaps */
	अगर (groups_per_page > 1) अणु
		i = माप(काष्ठा buffer_head *) * groups_per_page;
		bh = kzalloc(i, gfp);
		अगर (bh == शून्य) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		bh = &bhs;

	first_group = page->index * blocks_per_page / 2;

	/* पढ़ो all groups the page covers पूर्णांकo the cache */
	क्रम (i = 0, group = first_group; i < groups_per_page; i++, group++) अणु
		अगर (group >= ngroups)
			अवरोध;

		grinfo = ext4_get_group_info(sb, group);
		/*
		 * If page is uptodate then we came here after online resize
		 * which added some new uninitialized group info काष्ठाs, so
		 * we must skip all initialized uptodate buddies on the page,
		 * which may be currently in use by an allocating task.
		 */
		अगर (PageUptodate(page) && !EXT4_MB_GRP_NEED_INIT(grinfo)) अणु
			bh[i] = शून्य;
			जारी;
		पूर्ण
		bh[i] = ext4_पढ़ो_block_biपंचांगap_noरुको(sb, group, false);
		अगर (IS_ERR(bh[i])) अणु
			err = PTR_ERR(bh[i]);
			bh[i] = शून्य;
			जाओ out;
		पूर्ण
		mb_debug(sb, "read bitmap for group %u\n", group);
	पूर्ण

	/* रुको क्रम I/O completion */
	क्रम (i = 0, group = first_group; i < groups_per_page; i++, group++) अणु
		पूर्णांक err2;

		अगर (!bh[i])
			जारी;
		err2 = ext4_रुको_block_biपंचांगap(sb, group, bh[i]);
		अगर (!err)
			err = err2;
	पूर्ण

	first_block = page->index * blocks_per_page;
	क्रम (i = 0; i < blocks_per_page; i++) अणु
		group = (first_block + i) >> 1;
		अगर (group >= ngroups)
			अवरोध;

		अगर (!bh[group - first_group])
			/* skip initialized uptodate buddy */
			जारी;

		अगर (!buffer_verअगरied(bh[group - first_group]))
			/* Skip faulty biपंचांगaps */
			जारी;
		err = 0;

		/*
		 * data carry inक्रमmation regarding this
		 * particular group in the क्रमmat specअगरied
		 * above
		 *
		 */
		data = page_address(page) + (i * blocksize);
		biपंचांगap = bh[group - first_group]->b_data;

		/*
		 * We place the buddy block and biपंचांगap block
		 * बंद together
		 */
		अगर ((first_block + i) & 1) अणु
			/* this is block of buddy */
			BUG_ON(incore == शून्य);
			mb_debug(sb, "put buddy for group %u in page %lu/%x\n",
				group, page->index, i * blocksize);
			trace_ext4_mb_buddy_biपंचांगap_load(sb, group);
			grinfo = ext4_get_group_info(sb, group);
			grinfo->bb_fragments = 0;
			स_रखो(grinfo->bb_counters, 0,
			       माप(*grinfo->bb_counters) *
			       (MB_NUM_ORDERS(sb)));
			/*
			 * incore got set to the group block biपंचांगap below
			 */
			ext4_lock_group(sb, group);
			/* init the buddy */
			स_रखो(data, 0xff, blocksize);
			ext4_mb_generate_buddy(sb, data, incore, group);
			ext4_unlock_group(sb, group);
			incore = शून्य;
		पूर्ण अन्यथा अणु
			/* this is block of biपंचांगap */
			BUG_ON(incore != शून्य);
			mb_debug(sb, "put bitmap for group %u in page %lu/%x\n",
				group, page->index, i * blocksize);
			trace_ext4_mb_biपंचांगap_load(sb, group);

			/* see comments in ext4_mb_put_pa() */
			ext4_lock_group(sb, group);
			स_नकल(data, biपंचांगap, blocksize);

			/* mark all pपुनः_स्मृतिated blks used in in-core biपंचांगap */
			ext4_mb_generate_from_pa(sb, data, group);
			ext4_mb_generate_from_मुक्तlist(sb, data, group);
			ext4_unlock_group(sb, group);

			/* set incore so that the buddy inक्रमmation can be
			 * generated using this
			 */
			incore = data;
		पूर्ण
	पूर्ण
	SetPageUptodate(page);

out:
	अगर (bh) अणु
		क्रम (i = 0; i < groups_per_page; i++)
			brअन्यथा(bh[i]);
		अगर (bh != &bhs)
			kमुक्त(bh);
	पूर्ण
	वापस err;
पूर्ण

/*
 * Lock the buddy and biपंचांगap pages. This make sure other parallel init_group
 * on the same buddy page करोesn't happen whild holding the buddy page lock.
 * Return locked buddy and biपंचांगap pages on e4b काष्ठा. If buddy and biपंचांगap
 * are on the same page e4b->bd_buddy_page is शून्य and वापस value is 0.
 */
अटल पूर्णांक ext4_mb_get_buddy_page_lock(काष्ठा super_block *sb,
		ext4_group_t group, काष्ठा ext4_buddy *e4b, gfp_t gfp)
अणु
	काष्ठा inode *inode = EXT4_SB(sb)->s_buddy_cache;
	पूर्णांक block, pnum, poff;
	पूर्णांक blocks_per_page;
	काष्ठा page *page;

	e4b->bd_buddy_page = शून्य;
	e4b->bd_biपंचांगap_page = शून्य;

	blocks_per_page = PAGE_SIZE / sb->s_blocksize;
	/*
	 * the buddy cache inode stores the block biपंचांगap
	 * and buddy inक्रमmation in consecutive blocks.
	 * So क्रम each group we need two blocks.
	 */
	block = group * 2;
	pnum = block / blocks_per_page;
	poff = block % blocks_per_page;
	page = find_or_create_page(inode->i_mapping, pnum, gfp);
	अगर (!page)
		वापस -ENOMEM;
	BUG_ON(page->mapping != inode->i_mapping);
	e4b->bd_biपंचांगap_page = page;
	e4b->bd_biपंचांगap = page_address(page) + (poff * sb->s_blocksize);

	अगर (blocks_per_page >= 2) अणु
		/* buddy and biपंचांगap are on the same page */
		वापस 0;
	पूर्ण

	block++;
	pnum = block / blocks_per_page;
	page = find_or_create_page(inode->i_mapping, pnum, gfp);
	अगर (!page)
		वापस -ENOMEM;
	BUG_ON(page->mapping != inode->i_mapping);
	e4b->bd_buddy_page = page;
	वापस 0;
पूर्ण

अटल व्योम ext4_mb_put_buddy_page_lock(काष्ठा ext4_buddy *e4b)
अणु
	अगर (e4b->bd_biपंचांगap_page) अणु
		unlock_page(e4b->bd_biपंचांगap_page);
		put_page(e4b->bd_biपंचांगap_page);
	पूर्ण
	अगर (e4b->bd_buddy_page) अणु
		unlock_page(e4b->bd_buddy_page);
		put_page(e4b->bd_buddy_page);
	पूर्ण
पूर्ण

/*
 * Locking note:  This routine calls ext4_mb_init_cache(), which takes the
 * block group lock of all groups क्रम this page; करो not hold the BG lock when
 * calling this routine!
 */
अटल noअंतरभूत_क्रम_stack
पूर्णांक ext4_mb_init_group(काष्ठा super_block *sb, ext4_group_t group, gfp_t gfp)
अणु

	काष्ठा ext4_group_info *this_grp;
	काष्ठा ext4_buddy e4b;
	काष्ठा page *page;
	पूर्णांक ret = 0;

	might_sleep();
	mb_debug(sb, "init group %u\n", group);
	this_grp = ext4_get_group_info(sb, group);
	/*
	 * This ensures that we करोn't reinit the buddy cache
	 * page which map to the group from which we are alपढ़ोy
	 * allocating. If we are looking at the buddy cache we would
	 * have taken a reference using ext4_mb_load_buddy and that
	 * would have pinned buddy page to page cache.
	 * The call to ext4_mb_get_buddy_page_lock will mark the
	 * page accessed.
	 */
	ret = ext4_mb_get_buddy_page_lock(sb, group, &e4b, gfp);
	अगर (ret || !EXT4_MB_GRP_NEED_INIT(this_grp)) अणु
		/*
		 * somebody initialized the group
		 * वापस without करोing anything
		 */
		जाओ err;
	पूर्ण

	page = e4b.bd_biपंचांगap_page;
	ret = ext4_mb_init_cache(page, शून्य, gfp);
	अगर (ret)
		जाओ err;
	अगर (!PageUptodate(page)) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	अगर (e4b.bd_buddy_page == शून्य) अणु
		/*
		 * If both the biपंचांगap and buddy are in
		 * the same page we करोn't need to क्रमce
		 * init the buddy
		 */
		ret = 0;
		जाओ err;
	पूर्ण
	/* init buddy cache */
	page = e4b.bd_buddy_page;
	ret = ext4_mb_init_cache(page, e4b.bd_biपंचांगap, gfp);
	अगर (ret)
		जाओ err;
	अगर (!PageUptodate(page)) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण
err:
	ext4_mb_put_buddy_page_lock(&e4b);
	वापस ret;
पूर्ण

/*
 * Locking note:  This routine calls ext4_mb_init_cache(), which takes the
 * block group lock of all groups क्रम this page; करो not hold the BG lock when
 * calling this routine!
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक
ext4_mb_load_buddy_gfp(काष्ठा super_block *sb, ext4_group_t group,
		       काष्ठा ext4_buddy *e4b, gfp_t gfp)
अणु
	पूर्णांक blocks_per_page;
	पूर्णांक block;
	पूर्णांक pnum;
	पूर्णांक poff;
	काष्ठा page *page;
	पूर्णांक ret;
	काष्ठा ext4_group_info *grp;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा inode *inode = sbi->s_buddy_cache;

	might_sleep();
	mb_debug(sb, "load group %u\n", group);

	blocks_per_page = PAGE_SIZE / sb->s_blocksize;
	grp = ext4_get_group_info(sb, group);

	e4b->bd_blkbits = sb->s_blocksize_bits;
	e4b->bd_info = grp;
	e4b->bd_sb = sb;
	e4b->bd_group = group;
	e4b->bd_buddy_page = शून्य;
	e4b->bd_biपंचांगap_page = शून्य;

	अगर (unlikely(EXT4_MB_GRP_NEED_INIT(grp))) अणु
		/*
		 * we need full data about the group
		 * to make a good selection
		 */
		ret = ext4_mb_init_group(sb, group, gfp);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * the buddy cache inode stores the block biपंचांगap
	 * and buddy inक्रमmation in consecutive blocks.
	 * So क्रम each group we need two blocks.
	 */
	block = group * 2;
	pnum = block / blocks_per_page;
	poff = block % blocks_per_page;

	/* we could use find_or_create_page(), but it locks page
	 * what we'd like to aव्योम in fast path ... */
	page = find_get_page_flags(inode->i_mapping, pnum, FGP_ACCESSED);
	अगर (page == शून्य || !PageUptodate(page)) अणु
		अगर (page)
			/*
			 * drop the page reference and try
			 * to get the page with lock. If we
			 * are not uptodate that implies
			 * somebody just created the page but
			 * is yet to initialize the same. So
			 * रुको क्रम it to initialize.
			 */
			put_page(page);
		page = find_or_create_page(inode->i_mapping, pnum, gfp);
		अगर (page) अणु
			BUG_ON(page->mapping != inode->i_mapping);
			अगर (!PageUptodate(page)) अणु
				ret = ext4_mb_init_cache(page, शून्य, gfp);
				अगर (ret) अणु
					unlock_page(page);
					जाओ err;
				पूर्ण
				mb_cmp_biपंचांगaps(e4b, page_address(page) +
					       (poff * sb->s_blocksize));
			पूर्ण
			unlock_page(page);
		पूर्ण
	पूर्ण
	अगर (page == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	अगर (!PageUptodate(page)) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	/* Pages marked accessed alपढ़ोy */
	e4b->bd_biपंचांगap_page = page;
	e4b->bd_biपंचांगap = page_address(page) + (poff * sb->s_blocksize);

	block++;
	pnum = block / blocks_per_page;
	poff = block % blocks_per_page;

	page = find_get_page_flags(inode->i_mapping, pnum, FGP_ACCESSED);
	अगर (page == शून्य || !PageUptodate(page)) अणु
		अगर (page)
			put_page(page);
		page = find_or_create_page(inode->i_mapping, pnum, gfp);
		अगर (page) अणु
			BUG_ON(page->mapping != inode->i_mapping);
			अगर (!PageUptodate(page)) अणु
				ret = ext4_mb_init_cache(page, e4b->bd_biपंचांगap,
							 gfp);
				अगर (ret) अणु
					unlock_page(page);
					जाओ err;
				पूर्ण
			पूर्ण
			unlock_page(page);
		पूर्ण
	पूर्ण
	अगर (page == शून्य) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	अगर (!PageUptodate(page)) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	/* Pages marked accessed alपढ़ोy */
	e4b->bd_buddy_page = page;
	e4b->bd_buddy = page_address(page) + (poff * sb->s_blocksize);

	वापस 0;

err:
	अगर (page)
		put_page(page);
	अगर (e4b->bd_biपंचांगap_page)
		put_page(e4b->bd_biपंचांगap_page);
	अगर (e4b->bd_buddy_page)
		put_page(e4b->bd_buddy_page);
	e4b->bd_buddy = शून्य;
	e4b->bd_biपंचांगap = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_mb_load_buddy(काष्ठा super_block *sb, ext4_group_t group,
			      काष्ठा ext4_buddy *e4b)
अणु
	वापस ext4_mb_load_buddy_gfp(sb, group, e4b, GFP_NOFS);
पूर्ण

अटल व्योम ext4_mb_unload_buddy(काष्ठा ext4_buddy *e4b)
अणु
	अगर (e4b->bd_biपंचांगap_page)
		put_page(e4b->bd_biपंचांगap_page);
	अगर (e4b->bd_buddy_page)
		put_page(e4b->bd_buddy_page);
पूर्ण


अटल पूर्णांक mb_find_order_क्रम_block(काष्ठा ext4_buddy *e4b, पूर्णांक block)
अणु
	पूर्णांक order = 1, max;
	व्योम *bb;

	BUG_ON(e4b->bd_biपंचांगap == e4b->bd_buddy);
	BUG_ON(block >= (1 << (e4b->bd_blkbits + 3)));

	जबतक (order <= e4b->bd_blkbits + 1) अणु
		bb = mb_find_buddy(e4b, order, &max);
		अगर (!mb_test_bit(block >> order, bb)) अणु
			/* this block is part of buddy of order 'order' */
			वापस order;
		पूर्ण
		order++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mb_clear_bits(व्योम *bm, पूर्णांक cur, पूर्णांक len)
अणु
	__u32 *addr;

	len = cur + len;
	जबतक (cur < len) अणु
		अगर ((cur & 31) == 0 && (len - cur) >= 32) अणु
			/* fast path: clear whole word at once */
			addr = bm + (cur >> 3);
			*addr = 0;
			cur += 32;
			जारी;
		पूर्ण
		mb_clear_bit(cur, bm);
		cur++;
	पूर्ण
पूर्ण

/* clear bits in given range
 * will वापस first found zero bit अगर any, -1 otherwise
 */
अटल पूर्णांक mb_test_and_clear_bits(व्योम *bm, पूर्णांक cur, पूर्णांक len)
अणु
	__u32 *addr;
	पूर्णांक zero_bit = -1;

	len = cur + len;
	जबतक (cur < len) अणु
		अगर ((cur & 31) == 0 && (len - cur) >= 32) अणु
			/* fast path: clear whole word at once */
			addr = bm + (cur >> 3);
			अगर (*addr != (__u32)(-1) && zero_bit == -1)
				zero_bit = cur + mb_find_next_zero_bit(addr, 32, 0);
			*addr = 0;
			cur += 32;
			जारी;
		पूर्ण
		अगर (!mb_test_and_clear_bit(cur, bm) && zero_bit == -1)
			zero_bit = cur;
		cur++;
	पूर्ण

	वापस zero_bit;
पूर्ण

व्योम ext4_set_bits(व्योम *bm, पूर्णांक cur, पूर्णांक len)
अणु
	__u32 *addr;

	len = cur + len;
	जबतक (cur < len) अणु
		अगर ((cur & 31) == 0 && (len - cur) >= 32) अणु
			/* fast path: set whole word at once */
			addr = bm + (cur >> 3);
			*addr = 0xffffffff;
			cur += 32;
			जारी;
		पूर्ण
		mb_set_bit(cur, bm);
		cur++;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक mb_buddy_adjust_border(पूर्णांक* bit, व्योम* biपंचांगap, पूर्णांक side)
अणु
	अगर (mb_test_bit(*bit + side, biपंचांगap)) अणु
		mb_clear_bit(*bit, biपंचांगap);
		(*bit) -= side;
		वापस 1;
	पूर्ण
	अन्यथा अणु
		(*bit) += side;
		mb_set_bit(*bit, biपंचांगap);
		वापस -1;
	पूर्ण
पूर्ण

अटल व्योम mb_buddy_mark_मुक्त(काष्ठा ext4_buddy *e4b, पूर्णांक first, पूर्णांक last)
अणु
	पूर्णांक max;
	पूर्णांक order = 1;
	व्योम *buddy = mb_find_buddy(e4b, order, &max);

	जबतक (buddy) अणु
		व्योम *buddy2;

		/* Bits in range [first; last] are known to be set since
		 * corresponding blocks were allocated. Bits in range
		 * (first; last) will stay set because they क्रमm buddies on
		 * upper layer. We just deal with borders अगर they करोn't
		 * align with upper layer and then go up.
		 * Releasing entire group is all about clearing
		 * single bit of highest order buddy.
		 */

		/* Example:
		 * ---------------------------------
		 * |   1   |   1   |   1   |   1   |
		 * ---------------------------------
		 * | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
		 * ---------------------------------
		 *   0   1   2   3   4   5   6   7
		 *      \_____________________/
		 *
		 * Neither [1] nor [6] is aligned to above layer.
		 * Left neighbour [0] is मुक्त, so mark it busy,
		 * decrease bb_counters and extend range to
		 * [0; 6]
		 * Right neighbour [7] is busy. It can't be coaleasced with [6], so
		 * mark [6] मुक्त, increase bb_counters and shrink range to
		 * [0; 5].
		 * Then shअगरt range to [0; 2], go up and करो the same.
		 */


		अगर (first & 1)
			e4b->bd_info->bb_counters[order] += mb_buddy_adjust_border(&first, buddy, -1);
		अगर (!(last & 1))
			e4b->bd_info->bb_counters[order] += mb_buddy_adjust_border(&last, buddy, 1);
		अगर (first > last)
			अवरोध;
		order++;

		अगर (first == last || !(buddy2 = mb_find_buddy(e4b, order, &max))) अणु
			mb_clear_bits(buddy, first, last - first + 1);
			e4b->bd_info->bb_counters[order - 1] += last - first + 1;
			अवरोध;
		पूर्ण
		first >>= 1;
		last >>= 1;
		buddy = buddy2;
	पूर्ण
पूर्ण

अटल व्योम mb_मुक्त_blocks(काष्ठा inode *inode, काष्ठा ext4_buddy *e4b,
			   पूर्णांक first, पूर्णांक count)
अणु
	पूर्णांक left_is_मुक्त = 0;
	पूर्णांक right_is_मुक्त = 0;
	पूर्णांक block;
	पूर्णांक last = first + count - 1;
	काष्ठा super_block *sb = e4b->bd_sb;

	अगर (WARN_ON(count == 0))
		वापस;
	BUG_ON(last >= (sb->s_blocksize << 3));
	निश्चित_spin_locked(ext4_group_lock_ptr(sb, e4b->bd_group));
	/* Don't bother अगर the block group is corrupt. */
	अगर (unlikely(EXT4_MB_GRP_BBITMAP_CORRUPT(e4b->bd_info)))
		वापस;

	mb_check_buddy(e4b);
	mb_मुक्त_blocks_द्विगुन(inode, e4b, first, count);

	this_cpu_inc(discard_pa_seq);
	e4b->bd_info->bb_मुक्त += count;
	अगर (first < e4b->bd_info->bb_first_मुक्त)
		e4b->bd_info->bb_first_मुक्त = first;

	/* access memory sequentially: check left neighbour,
	 * clear range and then check right neighbour
	 */
	अगर (first != 0)
		left_is_मुक्त = !mb_test_bit(first - 1, e4b->bd_biपंचांगap);
	block = mb_test_and_clear_bits(e4b->bd_biपंचांगap, first, count);
	अगर (last + 1 < EXT4_SB(sb)->s_mb_maxs[0])
		right_is_मुक्त = !mb_test_bit(last + 1, e4b->bd_biपंचांगap);

	अगर (unlikely(block != -1)) अणु
		काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
		ext4_fsblk_t blocknr;

		blocknr = ext4_group_first_block_no(sb, e4b->bd_group);
		blocknr += EXT4_C2B(sbi, block);
		अगर (!(sbi->s_mount_state & EXT4_FC_REPLAY)) अणु
			ext4_grp_locked_error(sb, e4b->bd_group,
					      inode ? inode->i_ino : 0,
					      blocknr,
					      "freeing already freed block (bit %u); block bitmap corrupt.",
					      block);
			ext4_mark_group_biपंचांगap_corrupted(
				sb, e4b->bd_group,
				EXT4_GROUP_INFO_BBITMAP_CORRUPT);
		पूर्ण
		जाओ करोne;
	पूर्ण

	/* let's मुख्यtain fragments counter */
	अगर (left_is_मुक्त && right_is_मुक्त)
		e4b->bd_info->bb_fragments--;
	अन्यथा अगर (!left_is_मुक्त && !right_is_मुक्त)
		e4b->bd_info->bb_fragments++;

	/* buddy[0] == bd_biपंचांगap is a special हाल, so handle
	 * it right away and let mb_buddy_mark_मुक्त stay मुक्त of
	 * zero order checks.
	 * Check अगर neighbours are to be coaleasced,
	 * adjust biपंचांगap bb_counters and borders appropriately.
	 */
	अगर (first & 1) अणु
		first += !left_is_मुक्त;
		e4b->bd_info->bb_counters[0] += left_is_मुक्त ? -1 : 1;
	पूर्ण
	अगर (!(last & 1)) अणु
		last -= !right_is_मुक्त;
		e4b->bd_info->bb_counters[0] += right_is_मुक्त ? -1 : 1;
	पूर्ण

	अगर (first <= last)
		mb_buddy_mark_मुक्त(e4b, first >> 1, last >> 1);

करोne:
	mb_set_largest_मुक्त_order(sb, e4b->bd_info);
	mb_update_avg_fragment_size(sb, e4b->bd_info);
	mb_check_buddy(e4b);
पूर्ण

अटल पूर्णांक mb_find_extent(काष्ठा ext4_buddy *e4b, पूर्णांक block,
				पूर्णांक needed, काष्ठा ext4_मुक्त_extent *ex)
अणु
	पूर्णांक next = block;
	पूर्णांक max, order;
	व्योम *buddy;

	निश्चित_spin_locked(ext4_group_lock_ptr(e4b->bd_sb, e4b->bd_group));
	BUG_ON(ex == शून्य);

	buddy = mb_find_buddy(e4b, 0, &max);
	BUG_ON(buddy == शून्य);
	BUG_ON(block >= max);
	अगर (mb_test_bit(block, buddy)) अणु
		ex->fe_len = 0;
		ex->fe_start = 0;
		ex->fe_group = 0;
		वापस 0;
	पूर्ण

	/* find actual order */
	order = mb_find_order_क्रम_block(e4b, block);
	block = block >> order;

	ex->fe_len = 1 << order;
	ex->fe_start = block << order;
	ex->fe_group = e4b->bd_group;

	/* calc dअगरference from given start */
	next = next - ex->fe_start;
	ex->fe_len -= next;
	ex->fe_start += next;

	जबतक (needed > ex->fe_len &&
	       mb_find_buddy(e4b, order, &max)) अणु

		अगर (block + 1 >= max)
			अवरोध;

		next = (block + 1) * (1 << order);
		अगर (mb_test_bit(next, e4b->bd_biपंचांगap))
			अवरोध;

		order = mb_find_order_क्रम_block(e4b, next);

		block = next >> order;
		ex->fe_len += 1 << order;
	पूर्ण

	अगर (ex->fe_start + ex->fe_len > EXT4_CLUSTERS_PER_GROUP(e4b->bd_sb)) अणु
		/* Should never happen! (but apparently someबार करोes?!?) */
		WARN_ON(1);
		ext4_error(e4b->bd_sb, "corruption or bug in mb_find_extent "
			   "block=%d, order=%d needed=%d ex=%u/%d/%d@%u",
			   block, order, needed, ex->fe_group, ex->fe_start,
			   ex->fe_len, ex->fe_logical);
		ex->fe_len = 0;
		ex->fe_start = 0;
		ex->fe_group = 0;
	पूर्ण
	वापस ex->fe_len;
पूर्ण

अटल पूर्णांक mb_mark_used(काष्ठा ext4_buddy *e4b, काष्ठा ext4_मुक्त_extent *ex)
अणु
	पूर्णांक ord;
	पूर्णांक mlen = 0;
	पूर्णांक max = 0;
	पूर्णांक cur;
	पूर्णांक start = ex->fe_start;
	पूर्णांक len = ex->fe_len;
	अचिन्हित ret = 0;
	पूर्णांक len0 = len;
	व्योम *buddy;

	BUG_ON(start + len > (e4b->bd_sb->s_blocksize << 3));
	BUG_ON(e4b->bd_group != ex->fe_group);
	निश्चित_spin_locked(ext4_group_lock_ptr(e4b->bd_sb, e4b->bd_group));
	mb_check_buddy(e4b);
	mb_mark_used_द्विगुन(e4b, start, len);

	this_cpu_inc(discard_pa_seq);
	e4b->bd_info->bb_मुक्त -= len;
	अगर (e4b->bd_info->bb_first_मुक्त == start)
		e4b->bd_info->bb_first_मुक्त += len;

	/* let's मुख्यtain fragments counter */
	अगर (start != 0)
		mlen = !mb_test_bit(start - 1, e4b->bd_biपंचांगap);
	अगर (start + len < EXT4_SB(e4b->bd_sb)->s_mb_maxs[0])
		max = !mb_test_bit(start + len, e4b->bd_biपंचांगap);
	अगर (mlen && max)
		e4b->bd_info->bb_fragments++;
	अन्यथा अगर (!mlen && !max)
		e4b->bd_info->bb_fragments--;

	/* let's मुख्यtain buddy itself */
	जबतक (len) अणु
		ord = mb_find_order_क्रम_block(e4b, start);

		अगर (((start >> ord) << ord) == start && len >= (1 << ord)) अणु
			/* the whole chunk may be allocated at once! */
			mlen = 1 << ord;
			buddy = mb_find_buddy(e4b, ord, &max);
			BUG_ON((start >> ord) >= max);
			mb_set_bit(start >> ord, buddy);
			e4b->bd_info->bb_counters[ord]--;
			start += mlen;
			len -= mlen;
			BUG_ON(len < 0);
			जारी;
		पूर्ण

		/* store क्रम history */
		अगर (ret == 0)
			ret = len | (ord << 16);

		/* we have to split large buddy */
		BUG_ON(ord <= 0);
		buddy = mb_find_buddy(e4b, ord, &max);
		mb_set_bit(start >> ord, buddy);
		e4b->bd_info->bb_counters[ord]--;

		ord--;
		cur = (start >> ord) & ~1U;
		buddy = mb_find_buddy(e4b, ord, &max);
		mb_clear_bit(cur, buddy);
		mb_clear_bit(cur + 1, buddy);
		e4b->bd_info->bb_counters[ord]++;
		e4b->bd_info->bb_counters[ord]++;
	पूर्ण
	mb_set_largest_मुक्त_order(e4b->bd_sb, e4b->bd_info);

	mb_update_avg_fragment_size(e4b->bd_sb, e4b->bd_info);
	ext4_set_bits(e4b->bd_biपंचांगap, ex->fe_start, len0);
	mb_check_buddy(e4b);

	वापस ret;
पूर्ण

/*
 * Must be called under group lock!
 */
अटल व्योम ext4_mb_use_best_found(काष्ठा ext4_allocation_context *ac,
					काष्ठा ext4_buddy *e4b)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);
	पूर्णांक ret;

	BUG_ON(ac->ac_b_ex.fe_group != e4b->bd_group);
	BUG_ON(ac->ac_status == AC_STATUS_FOUND);

	ac->ac_b_ex.fe_len = min(ac->ac_b_ex.fe_len, ac->ac_g_ex.fe_len);
	ac->ac_b_ex.fe_logical = ac->ac_g_ex.fe_logical;
	ret = mb_mark_used(e4b, &ac->ac_b_ex);

	/* pपुनः_स्मृतिation can change ac_b_ex, thus we store actually
	 * allocated blocks क्रम history */
	ac->ac_f_ex = ac->ac_b_ex;

	ac->ac_status = AC_STATUS_FOUND;
	ac->ac_tail = ret & 0xffff;
	ac->ac_buddy = ret >> 16;

	/*
	 * take the page reference. We want the page to be pinned
	 * so that we करोn't get a ext4_mb_init_cache_call क्रम this
	 * group until we update the biपंचांगap. That would mean we
	 * द्विगुन allocate blocks. The reference is dropped
	 * in ext4_mb_release_context
	 */
	ac->ac_biपंचांगap_page = e4b->bd_biपंचांगap_page;
	get_page(ac->ac_biपंचांगap_page);
	ac->ac_buddy_page = e4b->bd_buddy_page;
	get_page(ac->ac_buddy_page);
	/* store last allocated क्रम subsequent stream allocation */
	अगर (ac->ac_flags & EXT4_MB_STREAM_ALLOC) अणु
		spin_lock(&sbi->s_md_lock);
		sbi->s_mb_last_group = ac->ac_f_ex.fe_group;
		sbi->s_mb_last_start = ac->ac_f_ex.fe_start;
		spin_unlock(&sbi->s_md_lock);
	पूर्ण
	/*
	 * As we've just pपुनः_स्मृतिated more space than
	 * user requested originally, we store allocated
	 * space in a special descriptor.
	 */
	अगर (ac->ac_o_ex.fe_len < ac->ac_b_ex.fe_len)
		ext4_mb_new_pपुनः_स्मृतिation(ac);

पूर्ण

अटल व्योम ext4_mb_check_limits(काष्ठा ext4_allocation_context *ac,
					काष्ठा ext4_buddy *e4b,
					पूर्णांक finish_group)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);
	काष्ठा ext4_मुक्त_extent *bex = &ac->ac_b_ex;
	काष्ठा ext4_मुक्त_extent *gex = &ac->ac_g_ex;
	काष्ठा ext4_मुक्त_extent ex;
	पूर्णांक max;

	अगर (ac->ac_status == AC_STATUS_FOUND)
		वापस;
	/*
	 * We करोn't want to scan क्रम a whole year
	 */
	अगर (ac->ac_found > sbi->s_mb_max_to_scan &&
			!(ac->ac_flags & EXT4_MB_HINT_FIRST)) अणु
		ac->ac_status = AC_STATUS_BREAK;
		वापस;
	पूर्ण

	/*
	 * Haven't found good chunk so far, let's जारी
	 */
	अगर (bex->fe_len < gex->fe_len)
		वापस;

	अगर ((finish_group || ac->ac_found > sbi->s_mb_min_to_scan)
			&& bex->fe_group == e4b->bd_group) अणु
		/* recheck chunk's availability - we don't know
		 * when it was found (within this lock-unlock
		 * period or not) */
		max = mb_find_extent(e4b, bex->fe_start, gex->fe_len, &ex);
		अगर (max >= gex->fe_len) अणु
			ext4_mb_use_best_found(ac, e4b);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * The routine checks whether found extent is good enough. If it is,
 * then the extent माला_लो marked used and flag is set to the context
 * to stop scanning. Otherwise, the extent is compared with the
 * previous found extent and अगर new one is better, then it's stored
 * in the context. Later, the best found extent will be used, अगर
 * mballoc can't find good enough extent.
 *
 * FIXME: real allocation policy is to be deचिन्हित yet!
 */
अटल व्योम ext4_mb_measure_extent(काष्ठा ext4_allocation_context *ac,
					काष्ठा ext4_मुक्त_extent *ex,
					काष्ठा ext4_buddy *e4b)
अणु
	काष्ठा ext4_मुक्त_extent *bex = &ac->ac_b_ex;
	काष्ठा ext4_मुक्त_extent *gex = &ac->ac_g_ex;

	BUG_ON(ex->fe_len <= 0);
	BUG_ON(ex->fe_len > EXT4_CLUSTERS_PER_GROUP(ac->ac_sb));
	BUG_ON(ex->fe_start >= EXT4_CLUSTERS_PER_GROUP(ac->ac_sb));
	BUG_ON(ac->ac_status != AC_STATUS_CONTINUE);

	ac->ac_found++;

	/*
	 * The special हाल - take what you catch first
	 */
	अगर (unlikely(ac->ac_flags & EXT4_MB_HINT_FIRST)) अणु
		*bex = *ex;
		ext4_mb_use_best_found(ac, e4b);
		वापस;
	पूर्ण

	/*
	 * Let's check whether the chuck is good enough
	 */
	अगर (ex->fe_len == gex->fe_len) अणु
		*bex = *ex;
		ext4_mb_use_best_found(ac, e4b);
		वापस;
	पूर्ण

	/*
	 * If this is first found extent, just store it in the context
	 */
	अगर (bex->fe_len == 0) अणु
		*bex = *ex;
		वापस;
	पूर्ण

	/*
	 * If new found extent is better, store it in the context
	 */
	अगर (bex->fe_len < gex->fe_len) अणु
		/* अगर the request isn't satisfied, any found extent
		 * larger than previous best one is better */
		अगर (ex->fe_len > bex->fe_len)
			*bex = *ex;
	पूर्ण अन्यथा अगर (ex->fe_len > gex->fe_len) अणु
		/* अगर the request is satisfied, then we try to find
		 * an extent that still satisfy the request, but is
		 * smaller than previous one */
		अगर (ex->fe_len < bex->fe_len)
			*bex = *ex;
	पूर्ण

	ext4_mb_check_limits(ac, e4b, 0);
पूर्ण

अटल noअंतरभूत_क्रम_stack
पूर्णांक ext4_mb_try_best_found(काष्ठा ext4_allocation_context *ac,
					काष्ठा ext4_buddy *e4b)
अणु
	काष्ठा ext4_मुक्त_extent ex = ac->ac_b_ex;
	ext4_group_t group = ex.fe_group;
	पूर्णांक max;
	पूर्णांक err;

	BUG_ON(ex.fe_len <= 0);
	err = ext4_mb_load_buddy(ac->ac_sb, group, e4b);
	अगर (err)
		वापस err;

	ext4_lock_group(ac->ac_sb, group);
	max = mb_find_extent(e4b, ex.fe_start, ex.fe_len, &ex);

	अगर (max > 0) अणु
		ac->ac_b_ex = ex;
		ext4_mb_use_best_found(ac, e4b);
	पूर्ण

	ext4_unlock_group(ac->ac_sb, group);
	ext4_mb_unload_buddy(e4b);

	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack
पूर्णांक ext4_mb_find_by_goal(काष्ठा ext4_allocation_context *ac,
				काष्ठा ext4_buddy *e4b)
अणु
	ext4_group_t group = ac->ac_g_ex.fe_group;
	पूर्णांक max;
	पूर्णांक err;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);
	काष्ठा ext4_group_info *grp = ext4_get_group_info(ac->ac_sb, group);
	काष्ठा ext4_मुक्त_extent ex;

	अगर (!(ac->ac_flags & EXT4_MB_HINT_TRY_GOAL))
		वापस 0;
	अगर (grp->bb_मुक्त == 0)
		वापस 0;

	err = ext4_mb_load_buddy(ac->ac_sb, group, e4b);
	अगर (err)
		वापस err;

	अगर (unlikely(EXT4_MB_GRP_BBITMAP_CORRUPT(e4b->bd_info))) अणु
		ext4_mb_unload_buddy(e4b);
		वापस 0;
	पूर्ण

	ext4_lock_group(ac->ac_sb, group);
	max = mb_find_extent(e4b, ac->ac_g_ex.fe_start,
			     ac->ac_g_ex.fe_len, &ex);
	ex.fe_logical = 0xDEADFA11; /* debug value */

	अगर (max >= ac->ac_g_ex.fe_len && ac->ac_g_ex.fe_len == sbi->s_stripe) अणु
		ext4_fsblk_t start;

		start = ext4_group_first_block_no(ac->ac_sb, e4b->bd_group) +
			ex.fe_start;
		/* use करो_भाग to get reमुख्यder (would be 64-bit modulo) */
		अगर (करो_भाग(start, sbi->s_stripe) == 0) अणु
			ac->ac_found++;
			ac->ac_b_ex = ex;
			ext4_mb_use_best_found(ac, e4b);
		पूर्ण
	पूर्ण अन्यथा अगर (max >= ac->ac_g_ex.fe_len) अणु
		BUG_ON(ex.fe_len <= 0);
		BUG_ON(ex.fe_group != ac->ac_g_ex.fe_group);
		BUG_ON(ex.fe_start != ac->ac_g_ex.fe_start);
		ac->ac_found++;
		ac->ac_b_ex = ex;
		ext4_mb_use_best_found(ac, e4b);
	पूर्ण अन्यथा अगर (max > 0 && (ac->ac_flags & EXT4_MB_HINT_MERGE)) अणु
		/* Someबार, caller may want to merge even small
		 * number of blocks to an existing extent */
		BUG_ON(ex.fe_len <= 0);
		BUG_ON(ex.fe_group != ac->ac_g_ex.fe_group);
		BUG_ON(ex.fe_start != ac->ac_g_ex.fe_start);
		ac->ac_found++;
		ac->ac_b_ex = ex;
		ext4_mb_use_best_found(ac, e4b);
	पूर्ण
	ext4_unlock_group(ac->ac_sb, group);
	ext4_mb_unload_buddy(e4b);

	वापस 0;
पूर्ण

/*
 * The routine scans buddy काष्ठाures (not biपंचांगap!) from given order
 * to max order and tries to find big enough chunk to satisfy the req
 */
अटल noअंतरभूत_क्रम_stack
व्योम ext4_mb_simple_scan_group(काष्ठा ext4_allocation_context *ac,
					काष्ठा ext4_buddy *e4b)
अणु
	काष्ठा super_block *sb = ac->ac_sb;
	काष्ठा ext4_group_info *grp = e4b->bd_info;
	व्योम *buddy;
	पूर्णांक i;
	पूर्णांक k;
	पूर्णांक max;

	BUG_ON(ac->ac_2order <= 0);
	क्रम (i = ac->ac_2order; i < MB_NUM_ORDERS(sb); i++) अणु
		अगर (grp->bb_counters[i] == 0)
			जारी;

		buddy = mb_find_buddy(e4b, i, &max);
		BUG_ON(buddy == शून्य);

		k = mb_find_next_zero_bit(buddy, max, 0);
		अगर (k >= max) अणु
			ext4_grp_locked_error(ac->ac_sb, e4b->bd_group, 0, 0,
				"%d free clusters of order %d. But found 0",
				grp->bb_counters[i], i);
			ext4_mark_group_biपंचांगap_corrupted(ac->ac_sb,
					 e4b->bd_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
			अवरोध;
		पूर्ण
		ac->ac_found++;

		ac->ac_b_ex.fe_len = 1 << i;
		ac->ac_b_ex.fe_start = k << i;
		ac->ac_b_ex.fe_group = e4b->bd_group;

		ext4_mb_use_best_found(ac, e4b);

		BUG_ON(ac->ac_f_ex.fe_len != ac->ac_g_ex.fe_len);

		अगर (EXT4_SB(sb)->s_mb_stats)
			atomic_inc(&EXT4_SB(sb)->s_bal_2orders);

		अवरोध;
	पूर्ण
पूर्ण

/*
 * The routine scans the group and measures all found extents.
 * In order to optimize scanning, caller must pass number of
 * मुक्त blocks in the group, so the routine can know upper limit.
 */
अटल noअंतरभूत_क्रम_stack
व्योम ext4_mb_complex_scan_group(काष्ठा ext4_allocation_context *ac,
					काष्ठा ext4_buddy *e4b)
अणु
	काष्ठा super_block *sb = ac->ac_sb;
	व्योम *biपंचांगap = e4b->bd_biपंचांगap;
	काष्ठा ext4_मुक्त_extent ex;
	पूर्णांक i;
	पूर्णांक मुक्त;

	मुक्त = e4b->bd_info->bb_मुक्त;
	अगर (WARN_ON(मुक्त <= 0))
		वापस;

	i = e4b->bd_info->bb_first_मुक्त;

	जबतक (मुक्त && ac->ac_status == AC_STATUS_CONTINUE) अणु
		i = mb_find_next_zero_bit(biपंचांगap,
						EXT4_CLUSTERS_PER_GROUP(sb), i);
		अगर (i >= EXT4_CLUSTERS_PER_GROUP(sb)) अणु
			/*
			 * IF we have corrupt biपंचांगap, we won't find any
			 * मुक्त blocks even though group info says we
			 * have मुक्त blocks
			 */
			ext4_grp_locked_error(sb, e4b->bd_group, 0, 0,
					"%d free clusters as per "
					"group info. But bitmap says 0",
					मुक्त);
			ext4_mark_group_biपंचांगap_corrupted(sb, e4b->bd_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
			अवरोध;
		पूर्ण

		mb_find_extent(e4b, i, ac->ac_g_ex.fe_len, &ex);
		अगर (WARN_ON(ex.fe_len <= 0))
			अवरोध;
		अगर (मुक्त < ex.fe_len) अणु
			ext4_grp_locked_error(sb, e4b->bd_group, 0, 0,
					"%d free clusters as per "
					"group info. But got %d blocks",
					मुक्त, ex.fe_len);
			ext4_mark_group_biपंचांगap_corrupted(sb, e4b->bd_group,
					EXT4_GROUP_INFO_BBITMAP_CORRUPT);
			/*
			 * The number of मुक्त blocks dअगरfers. This mostly
			 * indicate that the biपंचांगap is corrupt. So निकास
			 * without claiming the space.
			 */
			अवरोध;
		पूर्ण
		ex.fe_logical = 0xDEADC0DE; /* debug value */
		ext4_mb_measure_extent(ac, &ex, e4b);

		i += ex.fe_len;
		मुक्त -= ex.fe_len;
	पूर्ण

	ext4_mb_check_limits(ac, e4b, 1);
पूर्ण

/*
 * This is a special हाल क्रम storages like raid5
 * we try to find stripe-aligned chunks क्रम stripe-size-multiple requests
 */
अटल noअंतरभूत_क्रम_stack
व्योम ext4_mb_scan_aligned(काष्ठा ext4_allocation_context *ac,
				 काष्ठा ext4_buddy *e4b)
अणु
	काष्ठा super_block *sb = ac->ac_sb;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	व्योम *biपंचांगap = e4b->bd_biपंचांगap;
	काष्ठा ext4_मुक्त_extent ex;
	ext4_fsblk_t first_group_block;
	ext4_fsblk_t a;
	ext4_grpblk_t i;
	पूर्णांक max;

	BUG_ON(sbi->s_stripe == 0);

	/* find first stripe-aligned block in group */
	first_group_block = ext4_group_first_block_no(sb, e4b->bd_group);

	a = first_group_block + sbi->s_stripe - 1;
	करो_भाग(a, sbi->s_stripe);
	i = (a * sbi->s_stripe) - first_group_block;

	जबतक (i < EXT4_CLUSTERS_PER_GROUP(sb)) अणु
		अगर (!mb_test_bit(i, biपंचांगap)) अणु
			max = mb_find_extent(e4b, i, sbi->s_stripe, &ex);
			अगर (max >= sbi->s_stripe) अणु
				ac->ac_found++;
				ex.fe_logical = 0xDEADF00D; /* debug value */
				ac->ac_b_ex = ex;
				ext4_mb_use_best_found(ac, e4b);
				अवरोध;
			पूर्ण
		पूर्ण
		i += sbi->s_stripe;
	पूर्ण
पूर्ण

/*
 * This is also called BEFORE we load the buddy biपंचांगap.
 * Returns either 1 or 0 indicating that the group is either suitable
 * क्रम the allocation or not.
 */
अटल bool ext4_mb_good_group(काष्ठा ext4_allocation_context *ac,
				ext4_group_t group, पूर्णांक cr)
अणु
	ext4_grpblk_t मुक्त, fragments;
	पूर्णांक flex_size = ext4_flex_bg_size(EXT4_SB(ac->ac_sb));
	काष्ठा ext4_group_info *grp = ext4_get_group_info(ac->ac_sb, group);

	BUG_ON(cr < 0 || cr >= 4);

	अगर (unlikely(EXT4_MB_GRP_BBITMAP_CORRUPT(grp)))
		वापस false;

	मुक्त = grp->bb_मुक्त;
	अगर (मुक्त == 0)
		वापस false;

	fragments = grp->bb_fragments;
	अगर (fragments == 0)
		वापस false;

	चयन (cr) अणु
	हाल 0:
		BUG_ON(ac->ac_2order == 0);

		/* Aव्योम using the first bg of a flexgroup क्रम data files */
		अगर ((ac->ac_flags & EXT4_MB_HINT_DATA) &&
		    (flex_size >= EXT4_FLEX_SIZE_सूची_ALLOC_SCHEME) &&
		    ((group % flex_size) == 0))
			वापस false;

		अगर (मुक्त < ac->ac_g_ex.fe_len)
			वापस false;

		अगर (ac->ac_2order >= MB_NUM_ORDERS(ac->ac_sb))
			वापस true;

		अगर (grp->bb_largest_मुक्त_order < ac->ac_2order)
			वापस false;

		वापस true;
	हाल 1:
		अगर ((मुक्त / fragments) >= ac->ac_g_ex.fe_len)
			वापस true;
		अवरोध;
	हाल 2:
		अगर (मुक्त >= ac->ac_g_ex.fe_len)
			वापस true;
		अवरोध;
	हाल 3:
		वापस true;
	शेष:
		BUG();
	पूर्ण

	वापस false;
पूर्ण

/*
 * This could वापस negative error code अगर something goes wrong
 * during ext4_mb_init_group(). This should not be called with
 * ext4_lock_group() held.
 */
अटल पूर्णांक ext4_mb_good_group_nolock(काष्ठा ext4_allocation_context *ac,
				     ext4_group_t group, पूर्णांक cr)
अणु
	काष्ठा ext4_group_info *grp = ext4_get_group_info(ac->ac_sb, group);
	काष्ठा super_block *sb = ac->ac_sb;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	bool should_lock = ac->ac_flags & EXT4_MB_STRICT_CHECK;
	ext4_grpblk_t मुक्त;
	पूर्णांक ret = 0;

	अगर (sbi->s_mb_stats)
		atomic64_inc(&sbi->s_bal_cX_groups_considered[ac->ac_criteria]);
	अगर (should_lock)
		ext4_lock_group(sb, group);
	मुक्त = grp->bb_मुक्त;
	अगर (मुक्त == 0)
		जाओ out;
	अगर (cr <= 2 && मुक्त < ac->ac_g_ex.fe_len)
		जाओ out;
	अगर (unlikely(EXT4_MB_GRP_BBITMAP_CORRUPT(grp)))
		जाओ out;
	अगर (should_lock)
		ext4_unlock_group(sb, group);

	/* We only करो this अगर the grp has never been initialized */
	अगर (unlikely(EXT4_MB_GRP_NEED_INIT(grp))) अणु
		काष्ठा ext4_group_desc *gdp =
			ext4_get_group_desc(sb, group, शून्य);
		पूर्णांक ret;

		/* cr=0/1 is a very optimistic search to find large
		 * good chunks almost क्रम मुक्त.  If buddy data is not
		 * पढ़ोy, then this optimization makes no sense.  But
		 * we never skip the first block group in a flex_bg,
		 * since this माला_लो used क्रम metadata block allocation,
		 * and we want to make sure we locate metadata blocks
		 * in the first block group in the flex_bg अगर possible.
		 */
		अगर (cr < 2 &&
		    (!sbi->s_log_groups_per_flex ||
		     ((group & ((1 << sbi->s_log_groups_per_flex) - 1)) != 0)) &&
		    !(ext4_has_group_desc_csum(sb) &&
		      (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))))
			वापस 0;
		ret = ext4_mb_init_group(sb, group, GFP_NOFS);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (should_lock)
		ext4_lock_group(sb, group);
	ret = ext4_mb_good_group(ac, group, cr);
out:
	अगर (should_lock)
		ext4_unlock_group(sb, group);
	वापस ret;
पूर्ण

/*
 * Start prefetching @nr block biपंचांगaps starting at @group.
 * Return the next group which needs to be prefetched.
 */
ext4_group_t ext4_mb_prefetch(काष्ठा super_block *sb, ext4_group_t group,
			      अचिन्हित पूर्णांक nr, पूर्णांक *cnt)
अणु
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	काष्ठा buffer_head *bh;
	काष्ठा blk_plug plug;

	blk_start_plug(&plug);
	जबतक (nr-- > 0) अणु
		काष्ठा ext4_group_desc *gdp = ext4_get_group_desc(sb, group,
								  शून्य);
		काष्ठा ext4_group_info *grp = ext4_get_group_info(sb, group);

		/*
		 * Prefetch block groups with मुक्त blocks; but करोn't
		 * bother अगर it is marked uninitialized on disk, since
		 * it won't require I/O to पढ़ो.  Also only try to
		 * prefetch once, so we aव्योम getblk() call, which can
		 * be expensive.
		 */
		अगर (!EXT4_MB_GRP_TEST_AND_SET_READ(grp) &&
		    EXT4_MB_GRP_NEED_INIT(grp) &&
		    ext4_मुक्त_group_clusters(sb, gdp) > 0 &&
		    !(ext4_has_group_desc_csum(sb) &&
		      (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)))) अणु
			bh = ext4_पढ़ो_block_biपंचांगap_noरुको(sb, group, true);
			अगर (bh && !IS_ERR(bh)) अणु
				अगर (!buffer_uptodate(bh) && cnt)
					(*cnt)++;
				brअन्यथा(bh);
			पूर्ण
		पूर्ण
		अगर (++group >= ngroups)
			group = 0;
	पूर्ण
	blk_finish_plug(&plug);
	वापस group;
पूर्ण

/*
 * Prefetching पढ़ोs the block biपंचांगap पूर्णांकo the buffer cache; but we
 * need to make sure that the buddy biपंचांगap in the page cache has been
 * initialized.  Note that ext4_mb_init_group() will block अगर the I/O
 * is not yet completed, or indeed अगर it was not initiated by
 * ext4_mb_prefetch did not start the I/O.
 *
 * TODO: We should actually kick off the buddy biपंचांगap setup in a work
 * queue when the buffer I/O is completed, so that we करोn't block
 * रुकोing क्रम the block allocation biपंचांगap पढ़ो to finish when
 * ext4_mb_prefetch_fini is called from ext4_mb_regular_allocator().
 */
व्योम ext4_mb_prefetch_fini(काष्ठा super_block *sb, ext4_group_t group,
			   अचिन्हित पूर्णांक nr)
अणु
	जबतक (nr-- > 0) अणु
		काष्ठा ext4_group_desc *gdp = ext4_get_group_desc(sb, group,
								  शून्य);
		काष्ठा ext4_group_info *grp = ext4_get_group_info(sb, group);

		अगर (!group)
			group = ext4_get_groups_count(sb);
		group--;
		grp = ext4_get_group_info(sb, group);

		अगर (EXT4_MB_GRP_NEED_INIT(grp) &&
		    ext4_मुक्त_group_clusters(sb, gdp) > 0 &&
		    !(ext4_has_group_desc_csum(sb) &&
		      (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)))) अणु
			अगर (ext4_mb_init_group(sb, group, GFP_NOFS))
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ext4_mb_regular_allocator(काष्ठा ext4_allocation_context *ac)
अणु
	ext4_group_t prefetch_grp = 0, ngroups, group, i;
	पूर्णांक cr = -1;
	पूर्णांक err = 0, first_err = 0;
	अचिन्हित पूर्णांक nr = 0, prefetch_ios = 0;
	काष्ठा ext4_sb_info *sbi;
	काष्ठा super_block *sb;
	काष्ठा ext4_buddy e4b;
	पूर्णांक lost;

	sb = ac->ac_sb;
	sbi = EXT4_SB(sb);
	ngroups = ext4_get_groups_count(sb);
	/* non-extent files are limited to low blocks/groups */
	अगर (!(ext4_test_inode_flag(ac->ac_inode, EXT4_INODE_EXTENTS)))
		ngroups = sbi->s_blockfile_groups;

	BUG_ON(ac->ac_status == AC_STATUS_FOUND);

	/* first, try the goal */
	err = ext4_mb_find_by_goal(ac, &e4b);
	अगर (err || ac->ac_status == AC_STATUS_FOUND)
		जाओ out;

	अगर (unlikely(ac->ac_flags & EXT4_MB_HINT_GOAL_ONLY))
		जाओ out;

	/*
	 * ac->ac_2order is set only अगर the fe_len is a घातer of 2
	 * अगर ac->ac_2order is set we also set criteria to 0 so that we
	 * try exact allocation using buddy.
	 */
	i = fls(ac->ac_g_ex.fe_len);
	ac->ac_2order = 0;
	/*
	 * We search using buddy data only अगर the order of the request
	 * is greater than equal to the sbi_s_mb_order2_reqs
	 * You can tune it via /sys/fs/ext4/<partition>/mb_order2_req
	 * We also support searching क्रम घातer-of-two requests only क्रम
	 * requests upto maximum buddy size we have स्थिरructed.
	 */
	अगर (i >= sbi->s_mb_order2_reqs && i <= MB_NUM_ORDERS(sb)) अणु
		/*
		 * This should tell अगर fe_len is exactly घातer of 2
		 */
		अगर ((ac->ac_g_ex.fe_len & (~(1 << (i - 1)))) == 0)
			ac->ac_2order = array_index_nospec(i - 1,
							   MB_NUM_ORDERS(sb));
	पूर्ण

	/* अगर stream allocation is enabled, use global goal */
	अगर (ac->ac_flags & EXT4_MB_STREAM_ALLOC) अणु
		/* TBD: may be hot poपूर्णांक */
		spin_lock(&sbi->s_md_lock);
		ac->ac_g_ex.fe_group = sbi->s_mb_last_group;
		ac->ac_g_ex.fe_start = sbi->s_mb_last_start;
		spin_unlock(&sbi->s_md_lock);
	पूर्ण

	/* Let's just scan groups to find more-less suitable blocks */
	cr = ac->ac_2order ? 0 : 1;
	/*
	 * cr == 0 try to get exact allocation,
	 * cr == 3  try to get anything
	 */
repeat:
	क्रम (; cr < 4 && ac->ac_status == AC_STATUS_CONTINUE; cr++) अणु
		ac->ac_criteria = cr;
		/*
		 * searching क्रम the right group start
		 * from the goal value specअगरied
		 */
		group = ac->ac_g_ex.fe_group;
		ac->ac_last_optimal_group = group;
		ac->ac_groups_linear_reमुख्यing = sbi->s_mb_max_linear_groups;
		prefetch_grp = group;

		क्रम (i = 0; i < ngroups; group = next_linear_group(ac, group, ngroups),
			     i++) अणु
			पूर्णांक ret = 0, new_cr;

			cond_resched();

			ext4_mb_choose_next_group(ac, &new_cr, &group, ngroups);
			अगर (new_cr != cr) अणु
				cr = new_cr;
				जाओ repeat;
			पूर्ण

			/*
			 * Batch पढ़ोs of the block allocation biपंचांगaps
			 * to get multiple READs in flight; limit
			 * prefetching at cr=0/1, otherwise mballoc can
			 * spend a lot of समय loading imperfect groups
			 */
			अगर ((prefetch_grp == group) &&
			    (cr > 1 ||
			     prefetch_ios < sbi->s_mb_prefetch_limit)) अणु
				अचिन्हित पूर्णांक curr_ios = prefetch_ios;

				nr = sbi->s_mb_prefetch;
				अगर (ext4_has_feature_flex_bg(sb)) अणु
					nr = 1 << sbi->s_log_groups_per_flex;
					nr -= group & (nr - 1);
					nr = min(nr, sbi->s_mb_prefetch);
				पूर्ण
				prefetch_grp = ext4_mb_prefetch(sb, group,
							nr, &prefetch_ios);
				अगर (prefetch_ios == curr_ios)
					nr = 0;
			पूर्ण

			/* This now checks without needing the buddy page */
			ret = ext4_mb_good_group_nolock(ac, group, cr);
			अगर (ret <= 0) अणु
				अगर (!first_err)
					first_err = ret;
				जारी;
			पूर्ण

			err = ext4_mb_load_buddy(sb, group, &e4b);
			अगर (err)
				जाओ out;

			ext4_lock_group(sb, group);

			/*
			 * We need to check again after locking the
			 * block group
			 */
			ret = ext4_mb_good_group(ac, group, cr);
			अगर (ret == 0) अणु
				ext4_unlock_group(sb, group);
				ext4_mb_unload_buddy(&e4b);
				जारी;
			पूर्ण

			ac->ac_groups_scanned++;
			अगर (cr == 0)
				ext4_mb_simple_scan_group(ac, &e4b);
			अन्यथा अगर (cr == 1 && sbi->s_stripe &&
					!(ac->ac_g_ex.fe_len % sbi->s_stripe))
				ext4_mb_scan_aligned(ac, &e4b);
			अन्यथा
				ext4_mb_complex_scan_group(ac, &e4b);

			ext4_unlock_group(sb, group);
			ext4_mb_unload_buddy(&e4b);

			अगर (ac->ac_status != AC_STATUS_CONTINUE)
				अवरोध;
		पूर्ण
		/* Processed all groups and haven't found blocks */
		अगर (sbi->s_mb_stats && i == ngroups)
			atomic64_inc(&sbi->s_bal_cX_failed[cr]);
	पूर्ण

	अगर (ac->ac_b_ex.fe_len > 0 && ac->ac_status != AC_STATUS_FOUND &&
	    !(ac->ac_flags & EXT4_MB_HINT_FIRST)) अणु
		/*
		 * We've been searching too long. Let's try to allocate
		 * the best chunk we've found so far
		 */
		ext4_mb_try_best_found(ac, &e4b);
		अगर (ac->ac_status != AC_STATUS_FOUND) अणु
			/*
			 * Someone more lucky has alपढ़ोy allocated it.
			 * The only thing we can करो is just take first
			 * found block(s)
			 */
			lost = atomic_inc_वापस(&sbi->s_mb_lost_chunks);
			mb_debug(sb, "lost chunk, group: %u, start: %d, len: %d, lost: %d\n",
				 ac->ac_b_ex.fe_group, ac->ac_b_ex.fe_start,
				 ac->ac_b_ex.fe_len, lost);

			ac->ac_b_ex.fe_group = 0;
			ac->ac_b_ex.fe_start = 0;
			ac->ac_b_ex.fe_len = 0;
			ac->ac_status = AC_STATUS_CONTINUE;
			ac->ac_flags |= EXT4_MB_HINT_FIRST;
			cr = 3;
			जाओ repeat;
		पूर्ण
	पूर्ण

	अगर (sbi->s_mb_stats && ac->ac_status == AC_STATUS_FOUND)
		atomic64_inc(&sbi->s_bal_cX_hits[ac->ac_criteria]);
out:
	अगर (!err && ac->ac_status != AC_STATUS_FOUND && first_err)
		err = first_err;

	mb_debug(sb, "Best len %d, origin len %d, ac_status %u, ac_flags 0x%x, cr %d ret %d\n",
		 ac->ac_b_ex.fe_len, ac->ac_o_ex.fe_len, ac->ac_status,
		 ac->ac_flags, cr, err);

	अगर (nr)
		ext4_mb_prefetch_fini(sb, prefetch_grp, nr);

	वापस err;
पूर्ण

अटल व्योम *ext4_mb_seq_groups_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा super_block *sb = PDE_DATA(file_inode(seq->file));
	ext4_group_t group;

	अगर (*pos < 0 || *pos >= ext4_get_groups_count(sb))
		वापस शून्य;
	group = *pos + 1;
	वापस (व्योम *) ((अचिन्हित दीर्घ) group);
पूर्ण

अटल व्योम *ext4_mb_seq_groups_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा super_block *sb = PDE_DATA(file_inode(seq->file));
	ext4_group_t group;

	++*pos;
	अगर (*pos < 0 || *pos >= ext4_get_groups_count(sb))
		वापस शून्य;
	group = *pos + 1;
	वापस (व्योम *) ((अचिन्हित दीर्घ) group);
पूर्ण

अटल पूर्णांक ext4_mb_seq_groups_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा super_block *sb = PDE_DATA(file_inode(seq->file));
	ext4_group_t group = (ext4_group_t) ((अचिन्हित दीर्घ) v);
	पूर्णांक i;
	पूर्णांक err, buddy_loaded = 0;
	काष्ठा ext4_buddy e4b;
	काष्ठा ext4_group_info *grinfo;
	अचिन्हित अक्षर blocksize_bits = min_t(अचिन्हित अक्षर,
					     sb->s_blocksize_bits,
					     EXT4_MAX_BLOCK_LOG_SIZE);
	काष्ठा sg अणु
		काष्ठा ext4_group_info info;
		ext4_grpblk_t counters[EXT4_MAX_BLOCK_LOG_SIZE + 2];
	पूर्ण sg;

	group--;
	अगर (group == 0)
		seq_माला_दो(seq, "#group: free  frags first ["
			      " 2^0   2^1   2^2   2^3   2^4   2^5   2^6  "
			      " 2^7   2^8   2^9   2^10  2^11  2^12  2^13  ]\न");

	i = (blocksize_bits + 2) * माप(sg.info.bb_counters[0]) +
		माप(काष्ठा ext4_group_info);

	grinfo = ext4_get_group_info(sb, group);
	/* Load the group info in memory only अगर not alपढ़ोy loaded. */
	अगर (unlikely(EXT4_MB_GRP_NEED_INIT(grinfo))) अणु
		err = ext4_mb_load_buddy(sb, group, &e4b);
		अगर (err) अणु
			seq_म_लिखो(seq, "#%-5u: I/O error\n", group);
			वापस 0;
		पूर्ण
		buddy_loaded = 1;
	पूर्ण

	स_नकल(&sg, ext4_get_group_info(sb, group), i);

	अगर (buddy_loaded)
		ext4_mb_unload_buddy(&e4b);

	seq_म_लिखो(seq, "#%-5u: %-5u %-5u %-5u [", group, sg.info.bb_मुक्त,
			sg.info.bb_fragments, sg.info.bb_first_मुक्त);
	क्रम (i = 0; i <= 13; i++)
		seq_म_लिखो(seq, " %-5u", i <= blocksize_bits + 1 ?
				sg.info.bb_counters[i] : 0);
	seq_माला_दो(seq, " ]\n");

	वापस 0;
पूर्ण

अटल व्योम ext4_mb_seq_groups_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

स्थिर काष्ठा seq_operations ext4_mb_seq_groups_ops = अणु
	.start  = ext4_mb_seq_groups_start,
	.next   = ext4_mb_seq_groups_next,
	.stop   = ext4_mb_seq_groups_stop,
	.show   = ext4_mb_seq_groups_show,
पूर्ण;

पूर्णांक ext4_seq_mb_stats_show(काष्ठा seq_file *seq, व्योम *offset)
अणु
	काष्ठा super_block *sb = (काष्ठा super_block *)seq->निजी;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	seq_माला_दो(seq, "mballoc:\n");
	अगर (!sbi->s_mb_stats) अणु
		seq_माला_दो(seq, "\tmb stats collection turned off.\n");
		seq_माला_दो(seq, "\tTo enable, please write \"1\" to sysfs file mb_stats.\n");
		वापस 0;
	पूर्ण
	seq_म_लिखो(seq, "\treqs: %u\n", atomic_पढ़ो(&sbi->s_bal_reqs));
	seq_म_लिखो(seq, "\tsuccess: %u\n", atomic_पढ़ो(&sbi->s_bal_success));

	seq_म_लिखो(seq, "\tgroups_scanned: %u\n",  atomic_पढ़ो(&sbi->s_bal_groups_scanned));

	seq_माला_दो(seq, "\tcr0_stats:\n");
	seq_म_लिखो(seq, "\t\thits: %llu\n", atomic64_पढ़ो(&sbi->s_bal_cX_hits[0]));
	seq_म_लिखो(seq, "\t\tgroups_considered: %llu\n",
		   atomic64_पढ़ो(&sbi->s_bal_cX_groups_considered[0]));
	seq_म_लिखो(seq, "\t\tuseless_loops: %llu\n",
		   atomic64_पढ़ो(&sbi->s_bal_cX_failed[0]));
	seq_म_लिखो(seq, "\t\tbad_suggestions: %u\n",
		   atomic_पढ़ो(&sbi->s_bal_cr0_bad_suggestions));

	seq_माला_दो(seq, "\tcr1_stats:\n");
	seq_म_लिखो(seq, "\t\thits: %llu\n", atomic64_पढ़ो(&sbi->s_bal_cX_hits[1]));
	seq_म_लिखो(seq, "\t\tgroups_considered: %llu\n",
		   atomic64_पढ़ो(&sbi->s_bal_cX_groups_considered[1]));
	seq_म_लिखो(seq, "\t\tuseless_loops: %llu\n",
		   atomic64_पढ़ो(&sbi->s_bal_cX_failed[1]));
	seq_म_लिखो(seq, "\t\tbad_suggestions: %u\n",
		   atomic_पढ़ो(&sbi->s_bal_cr1_bad_suggestions));

	seq_माला_दो(seq, "\tcr2_stats:\n");
	seq_म_लिखो(seq, "\t\thits: %llu\n", atomic64_पढ़ो(&sbi->s_bal_cX_hits[2]));
	seq_म_लिखो(seq, "\t\tgroups_considered: %llu\n",
		   atomic64_पढ़ो(&sbi->s_bal_cX_groups_considered[2]));
	seq_म_लिखो(seq, "\t\tuseless_loops: %llu\n",
		   atomic64_पढ़ो(&sbi->s_bal_cX_failed[2]));

	seq_माला_दो(seq, "\tcr3_stats:\n");
	seq_म_लिखो(seq, "\t\thits: %llu\n", atomic64_पढ़ो(&sbi->s_bal_cX_hits[3]));
	seq_म_लिखो(seq, "\t\tgroups_considered: %llu\n",
		   atomic64_पढ़ो(&sbi->s_bal_cX_groups_considered[3]));
	seq_म_लिखो(seq, "\t\tuseless_loops: %llu\n",
		   atomic64_पढ़ो(&sbi->s_bal_cX_failed[3]));
	seq_म_लिखो(seq, "\textents_scanned: %u\n", atomic_पढ़ो(&sbi->s_bal_ex_scanned));
	seq_म_लिखो(seq, "\t\tgoal_hits: %u\n", atomic_पढ़ो(&sbi->s_bal_goals));
	seq_म_लिखो(seq, "\ट\ट2^n_hits: %u\न", atomic_पढ़ो(&sbi->s_bal_2orders));
	seq_म_लिखो(seq, "\t\tbreaks: %u\n", atomic_पढ़ो(&sbi->s_bal_अवरोधs));
	seq_म_लिखो(seq, "\t\tlost: %u\n", atomic_पढ़ो(&sbi->s_mb_lost_chunks));

	seq_म_लिखो(seq, "\tbuddies_generated: %u/%u\n",
		   atomic_पढ़ो(&sbi->s_mb_buddies_generated),
		   ext4_get_groups_count(sb));
	seq_म_लिखो(seq, "\tbuddies_time_used: %llu\n",
		   atomic64_पढ़ो(&sbi->s_mb_generation_समय));
	seq_म_लिखो(seq, "\tpreallocated: %u\n",
		   atomic_पढ़ो(&sbi->s_mb_pपुनः_स्मृतिated));
	seq_म_लिखो(seq, "\tdiscarded: %u\n",
		   atomic_पढ़ो(&sbi->s_mb_discarded));
	वापस 0;
पूर्ण

अटल व्योम *ext4_mb_seq_काष्ठाs_summary_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा super_block *sb = PDE_DATA(file_inode(seq->file));
	अचिन्हित दीर्घ position;

	पढ़ो_lock(&EXT4_SB(sb)->s_mb_rb_lock);

	अगर (*pos < 0 || *pos >= MB_NUM_ORDERS(sb) + 1)
		वापस शून्य;
	position = *pos + 1;
	वापस (व्योम *) ((अचिन्हित दीर्घ) position);
पूर्ण

अटल व्योम *ext4_mb_seq_काष्ठाs_summary_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा super_block *sb = PDE_DATA(file_inode(seq->file));
	अचिन्हित दीर्घ position;

	++*pos;
	अगर (*pos < 0 || *pos >= MB_NUM_ORDERS(sb) + 1)
		वापस शून्य;
	position = *pos + 1;
	वापस (व्योम *) ((अचिन्हित दीर्घ) position);
पूर्ण

अटल पूर्णांक ext4_mb_seq_काष्ठाs_summary_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा super_block *sb = PDE_DATA(file_inode(seq->file));
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	अचिन्हित दीर्घ position = ((अचिन्हित दीर्घ) v);
	काष्ठा ext4_group_info *grp;
	काष्ठा rb_node *n;
	अचिन्हित पूर्णांक count, min, max;

	position--;
	अगर (position >= MB_NUM_ORDERS(sb)) अणु
		seq_माला_दो(seq, "fragment_size_tree:\n");
		n = rb_first(&sbi->s_mb_avg_fragment_size_root);
		अगर (!n) अणु
			seq_माला_दो(seq, "\ttree_min: 0\n\ttree_max: 0\n\ttree_nodes: 0\n");
			वापस 0;
		पूर्ण
		grp = rb_entry(n, काष्ठा ext4_group_info, bb_avg_fragment_size_rb);
		min = grp->bb_fragments ? grp->bb_मुक्त / grp->bb_fragments : 0;
		count = 1;
		जबतक (rb_next(n)) अणु
			count++;
			n = rb_next(n);
		पूर्ण
		grp = rb_entry(n, काष्ठा ext4_group_info, bb_avg_fragment_size_rb);
		max = grp->bb_fragments ? grp->bb_मुक्त / grp->bb_fragments : 0;

		seq_म_लिखो(seq, "\ttree_min: %u\n\ttree_max: %u\n\ttree_nodes: %u\n",
			   min, max, count);
		वापस 0;
	पूर्ण

	अगर (position == 0) अणु
		seq_म_लिखो(seq, "optimize_scan: %d\n",
			   test_opt2(sb, MB_OPTIMIZE_SCAN) ? 1 : 0);
		seq_माला_दो(seq, "max_free_order_lists:\n");
	पूर्ण
	count = 0;
	list_क्रम_each_entry(grp, &sbi->s_mb_largest_मुक्त_orders[position],
			    bb_largest_मुक्त_order_node)
		count++;
	seq_म_लिखो(seq, "\tlist_order_%u_groups: %u\n",
		   (अचिन्हित पूर्णांक)position, count);

	वापस 0;
पूर्ण

अटल व्योम ext4_mb_seq_काष्ठाs_summary_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा super_block *sb = PDE_DATA(file_inode(seq->file));

	पढ़ो_unlock(&EXT4_SB(sb)->s_mb_rb_lock);
पूर्ण

स्थिर काष्ठा seq_operations ext4_mb_seq_काष्ठाs_summary_ops = अणु
	.start  = ext4_mb_seq_काष्ठाs_summary_start,
	.next   = ext4_mb_seq_काष्ठाs_summary_next,
	.stop   = ext4_mb_seq_काष्ठाs_summary_stop,
	.show   = ext4_mb_seq_काष्ठाs_summary_show,
पूर्ण;

अटल काष्ठा kmem_cache *get_groupinfo_cache(पूर्णांक blocksize_bits)
अणु
	पूर्णांक cache_index = blocksize_bits - EXT4_MIN_BLOCK_LOG_SIZE;
	काष्ठा kmem_cache *cachep = ext4_groupinfo_caches[cache_index];

	BUG_ON(!cachep);
	वापस cachep;
पूर्ण

/*
 * Allocate the top-level s_group_info array क्रम the specअगरied number
 * of groups
 */
पूर्णांक ext4_mb_alloc_groupinfo(काष्ठा super_block *sb, ext4_group_t ngroups)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	अचिन्हित size;
	काष्ठा ext4_group_info ***old_groupinfo, ***new_groupinfo;

	size = (ngroups + EXT4_DESC_PER_BLOCK(sb) - 1) >>
		EXT4_DESC_PER_BLOCK_BITS(sb);
	अगर (size <= sbi->s_group_info_size)
		वापस 0;

	size = roundup_घात_of_two(माप(*sbi->s_group_info) * size);
	new_groupinfo = kvzalloc(size, GFP_KERNEL);
	अगर (!new_groupinfo) अणु
		ext4_msg(sb, KERN_ERR, "can't allocate buddy meta group");
		वापस -ENOMEM;
	पूर्ण
	rcu_पढ़ो_lock();
	old_groupinfo = rcu_dereference(sbi->s_group_info);
	अगर (old_groupinfo)
		स_नकल(new_groupinfo, old_groupinfo,
		       sbi->s_group_info_size * माप(*sbi->s_group_info));
	rcu_पढ़ो_unlock();
	rcu_assign_poपूर्णांकer(sbi->s_group_info, new_groupinfo);
	sbi->s_group_info_size = size / माप(*sbi->s_group_info);
	अगर (old_groupinfo)
		ext4_kvमुक्त_array_rcu(old_groupinfo);
	ext4_debug("allocated s_groupinfo array for %d meta_bg's\n",
		   sbi->s_group_info_size);
	वापस 0;
पूर्ण

/* Create and initialize ext4_group_info data क्रम the given group. */
पूर्णांक ext4_mb_add_groupinfo(काष्ठा super_block *sb, ext4_group_t group,
			  काष्ठा ext4_group_desc *desc)
अणु
	पूर्णांक i;
	पूर्णांक metalen = 0;
	पूर्णांक idx = group >> EXT4_DESC_PER_BLOCK_BITS(sb);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_group_info **meta_group_info;
	काष्ठा kmem_cache *cachep = get_groupinfo_cache(sb->s_blocksize_bits);

	/*
	 * First check अगर this group is the first of a reserved block.
	 * If it's true, we have to allocate a new table of poपूर्णांकers
	 * to ext4_group_info काष्ठाures
	 */
	अगर (group % EXT4_DESC_PER_BLOCK(sb) == 0) अणु
		metalen = माप(*meta_group_info) <<
			EXT4_DESC_PER_BLOCK_BITS(sb);
		meta_group_info = kदो_स्मृति(metalen, GFP_NOFS);
		अगर (meta_group_info == शून्य) अणु
			ext4_msg(sb, KERN_ERR, "can't allocate mem "
				 "for a buddy group");
			जाओ निकास_meta_group_info;
		पूर्ण
		rcu_पढ़ो_lock();
		rcu_dereference(sbi->s_group_info)[idx] = meta_group_info;
		rcu_पढ़ो_unlock();
	पूर्ण

	meta_group_info = sbi_array_rcu_deref(sbi, s_group_info, idx);
	i = group & (EXT4_DESC_PER_BLOCK(sb) - 1);

	meta_group_info[i] = kmem_cache_zalloc(cachep, GFP_NOFS);
	अगर (meta_group_info[i] == शून्य) अणु
		ext4_msg(sb, KERN_ERR, "can't allocate buddy mem");
		जाओ निकास_group_info;
	पूर्ण
	set_bit(EXT4_GROUP_INFO_NEED_INIT_BIT,
		&(meta_group_info[i]->bb_state));

	/*
	 * initialize bb_मुक्त to be able to skip
	 * empty groups without initialization
	 */
	अगर (ext4_has_group_desc_csum(sb) &&
	    (desc->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))) अणु
		meta_group_info[i]->bb_मुक्त =
			ext4_मुक्त_clusters_after_init(sb, group, desc);
	पूर्ण अन्यथा अणु
		meta_group_info[i]->bb_मुक्त =
			ext4_मुक्त_group_clusters(sb, desc);
	पूर्ण

	INIT_LIST_HEAD(&meta_group_info[i]->bb_pपुनः_स्मृति_list);
	init_rwsem(&meta_group_info[i]->alloc_sem);
	meta_group_info[i]->bb_मुक्त_root = RB_ROOT;
	INIT_LIST_HEAD(&meta_group_info[i]->bb_largest_मुक्त_order_node);
	RB_CLEAR_NODE(&meta_group_info[i]->bb_avg_fragment_size_rb);
	meta_group_info[i]->bb_largest_मुक्त_order = -1;  /* uninit */
	meta_group_info[i]->bb_group = group;

	mb_group_bb_biपंचांगap_alloc(sb, meta_group_info[i], group);
	वापस 0;

निकास_group_info:
	/* If a meta_group_info table has been allocated, release it now */
	अगर (group % EXT4_DESC_PER_BLOCK(sb) == 0) अणु
		काष्ठा ext4_group_info ***group_info;

		rcu_पढ़ो_lock();
		group_info = rcu_dereference(sbi->s_group_info);
		kमुक्त(group_info[idx]);
		group_info[idx] = शून्य;
		rcu_पढ़ो_unlock();
	पूर्ण
निकास_meta_group_info:
	वापस -ENOMEM;
पूर्ण /* ext4_mb_add_groupinfo */

अटल पूर्णांक ext4_mb_init_backend(काष्ठा super_block *sb)
अणु
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	ext4_group_t i;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक err;
	काष्ठा ext4_group_desc *desc;
	काष्ठा ext4_group_info ***group_info;
	काष्ठा kmem_cache *cachep;

	err = ext4_mb_alloc_groupinfo(sb, ngroups);
	अगर (err)
		वापस err;

	sbi->s_buddy_cache = new_inode(sb);
	अगर (sbi->s_buddy_cache == शून्य) अणु
		ext4_msg(sb, KERN_ERR, "can't get new inode");
		जाओ err_मुक्तsgi;
	पूर्ण
	/* To aव्योम potentially colliding with an valid on-disk inode number,
	 * use EXT4_BAD_INO क्रम the buddy cache inode number.  This inode is
	 * not in the inode hash, so it should never be found by iget(), but
	 * this will aव्योम confusion अगर it ever shows up during debugging. */
	sbi->s_buddy_cache->i_ino = EXT4_BAD_INO;
	EXT4_I(sbi->s_buddy_cache)->i_disksize = 0;
	क्रम (i = 0; i < ngroups; i++) अणु
		cond_resched();
		desc = ext4_get_group_desc(sb, i, शून्य);
		अगर (desc == शून्य) अणु
			ext4_msg(sb, KERN_ERR, "can't read descriptor %u", i);
			जाओ err_मुक्तbuddy;
		पूर्ण
		अगर (ext4_mb_add_groupinfo(sb, i, desc) != 0)
			जाओ err_मुक्तbuddy;
	पूर्ण

	अगर (ext4_has_feature_flex_bg(sb)) अणु
		/* a single flex group is supposed to be पढ़ो by a single IO.
		 * 2 ^ s_log_groups_per_flex != अच_पूर्णांक_उच्च as s_mb_prefetch is
		 * अचिन्हित पूर्णांकeger, so the maximum shअगरt is 32.
		 */
		अगर (sbi->s_es->s_log_groups_per_flex >= 32) अणु
			ext4_msg(sb, KERN_ERR, "too many log groups per flexible block group");
			जाओ err_मुक्तbuddy;
		पूर्ण
		sbi->s_mb_prefetch = min_t(uपूर्णांक, 1 << sbi->s_es->s_log_groups_per_flex,
			BLK_MAX_SEGMENT_SIZE >> (sb->s_blocksize_bits - 9));
		sbi->s_mb_prefetch *= 8; /* 8 prefetch IOs in flight at most */
	पूर्ण अन्यथा अणु
		sbi->s_mb_prefetch = 32;
	पूर्ण
	अगर (sbi->s_mb_prefetch > ext4_get_groups_count(sb))
		sbi->s_mb_prefetch = ext4_get_groups_count(sb);
	/* now many real IOs to prefetch within a single allocation at cr=0
	 * given cr=0 is an CPU-related optimization we shouldn't try to
	 * load too many groups, at some poपूर्णांक we should start to use what
	 * we've got in memory.
	 * with an average अक्रमom access समय 5ms, it'd take a second to get
	 * 200 groups (* N with flex_bg), so let's make this limit 4
	 */
	sbi->s_mb_prefetch_limit = sbi->s_mb_prefetch * 4;
	अगर (sbi->s_mb_prefetch_limit > ext4_get_groups_count(sb))
		sbi->s_mb_prefetch_limit = ext4_get_groups_count(sb);

	वापस 0;

err_मुक्तbuddy:
	cachep = get_groupinfo_cache(sb->s_blocksize_bits);
	जबतक (i-- > 0)
		kmem_cache_मुक्त(cachep, ext4_get_group_info(sb, i));
	i = sbi->s_group_info_size;
	rcu_पढ़ो_lock();
	group_info = rcu_dereference(sbi->s_group_info);
	जबतक (i-- > 0)
		kमुक्त(group_info[i]);
	rcu_पढ़ो_unlock();
	iput(sbi->s_buddy_cache);
err_मुक्तsgi:
	rcu_पढ़ो_lock();
	kvमुक्त(rcu_dereference(sbi->s_group_info));
	rcu_पढ़ो_unlock();
	वापस -ENOMEM;
पूर्ण

अटल व्योम ext4_groupinfo_destroy_sद_असल(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_GRPINFO_CACHES; i++) अणु
		kmem_cache_destroy(ext4_groupinfo_caches[i]);
		ext4_groupinfo_caches[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ext4_groupinfo_create_slab(माप_प्रकार size)
अणु
	अटल DEFINE_MUTEX(ext4_grpinfo_slab_create_mutex);
	पूर्णांक slab_size;
	पूर्णांक blocksize_bits = order_base_2(size);
	पूर्णांक cache_index = blocksize_bits - EXT4_MIN_BLOCK_LOG_SIZE;
	काष्ठा kmem_cache *cachep;

	अगर (cache_index >= NR_GRPINFO_CACHES)
		वापस -EINVAL;

	अगर (unlikely(cache_index < 0))
		cache_index = 0;

	mutex_lock(&ext4_grpinfo_slab_create_mutex);
	अगर (ext4_groupinfo_caches[cache_index]) अणु
		mutex_unlock(&ext4_grpinfo_slab_create_mutex);
		वापस 0;	/* Alपढ़ोy created */
	पूर्ण

	slab_size = दुरत्व(काष्ठा ext4_group_info,
				bb_counters[blocksize_bits + 2]);

	cachep = kmem_cache_create(ext4_groupinfo_slab_names[cache_index],
					slab_size, 0, SLAB_RECLAIM_ACCOUNT,
					शून्य);

	ext4_groupinfo_caches[cache_index] = cachep;

	mutex_unlock(&ext4_grpinfo_slab_create_mutex);
	अगर (!cachep) अणु
		prपूर्णांकk(KERN_EMERG
		       "EXT4-fs: no memory for groupinfo slab cache\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ext4_mb_init(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	अचिन्हित i, j;
	अचिन्हित offset, offset_incr;
	अचिन्हित max;
	पूर्णांक ret;

	i = MB_NUM_ORDERS(sb) * माप(*sbi->s_mb_offsets);

	sbi->s_mb_offsets = kदो_स्मृति(i, GFP_KERNEL);
	अगर (sbi->s_mb_offsets == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	i = MB_NUM_ORDERS(sb) * माप(*sbi->s_mb_maxs);
	sbi->s_mb_maxs = kदो_स्मृति(i, GFP_KERNEL);
	अगर (sbi->s_mb_maxs == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = ext4_groupinfo_create_slab(sb->s_blocksize);
	अगर (ret < 0)
		जाओ out;

	/* order 0 is regular biपंचांगap */
	sbi->s_mb_maxs[0] = sb->s_blocksize << 3;
	sbi->s_mb_offsets[0] = 0;

	i = 1;
	offset = 0;
	offset_incr = 1 << (sb->s_blocksize_bits - 1);
	max = sb->s_blocksize << 2;
	करो अणु
		sbi->s_mb_offsets[i] = offset;
		sbi->s_mb_maxs[i] = max;
		offset += offset_incr;
		offset_incr = offset_incr >> 1;
		max = max >> 1;
		i++;
	पूर्ण जबतक (i < MB_NUM_ORDERS(sb));

	sbi->s_mb_avg_fragment_size_root = RB_ROOT;
	sbi->s_mb_largest_मुक्त_orders =
		kदो_स्मृति_array(MB_NUM_ORDERS(sb), माप(काष्ठा list_head),
			GFP_KERNEL);
	अगर (!sbi->s_mb_largest_मुक्त_orders) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	sbi->s_mb_largest_मुक्त_orders_locks =
		kदो_स्मृति_array(MB_NUM_ORDERS(sb), माप(rwlock_t),
			GFP_KERNEL);
	अगर (!sbi->s_mb_largest_मुक्त_orders_locks) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < MB_NUM_ORDERS(sb); i++) अणु
		INIT_LIST_HEAD(&sbi->s_mb_largest_मुक्त_orders[i]);
		rwlock_init(&sbi->s_mb_largest_मुक्त_orders_locks[i]);
	पूर्ण
	rwlock_init(&sbi->s_mb_rb_lock);

	spin_lock_init(&sbi->s_md_lock);
	sbi->s_mb_मुक्त_pending = 0;
	INIT_LIST_HEAD(&sbi->s_मुक्तd_data_list);

	sbi->s_mb_max_to_scan = MB_DEFAULT_MAX_TO_SCAN;
	sbi->s_mb_min_to_scan = MB_DEFAULT_MIN_TO_SCAN;
	sbi->s_mb_stats = MB_DEFAULT_STATS;
	sbi->s_mb_stream_request = MB_DEFAULT_STREAM_THRESHOLD;
	sbi->s_mb_order2_reqs = MB_DEFAULT_ORDER2_REQS;
	sbi->s_mb_max_inode_pपुनः_स्मृति = MB_DEFAULT_MAX_INODE_PREALLOC;
	/*
	 * The शेष group pपुनः_स्मृतिation is 512, which क्रम 4k block
	 * sizes translates to 2 megabytes.  However क्रम bigalloc file
	 * प्रणालीs, this is probably too big (i.e, अगर the cluster size
	 * is 1 megabyte, then group pपुनः_स्मृतिation size becomes half a
	 * gigabyte!).  As a शेष, we will keep a two megabyte
	 * group pralloc size क्रम cluster sizes up to 64k, and after
	 * that, we will क्रमce a minimum group pपुनः_स्मृतिation size of
	 * 32 clusters.  This translates to 8 megs when the cluster
	 * size is 256k, and 32 megs when the cluster size is 1 meg,
	 * which seems reasonable as a शेष.
	 */
	sbi->s_mb_group_pपुनः_स्मृति = max(MB_DEFAULT_GROUP_PREALLOC >>
				       sbi->s_cluster_bits, 32);
	/*
	 * If there is a s_stripe > 1, then we set the s_mb_group_pपुनः_स्मृति
	 * to the lowest multiple of s_stripe which is bigger than
	 * the s_mb_group_pपुनः_स्मृति as determined above. We want
	 * the pपुनः_स्मृतिation size to be an exact multiple of the
	 * RAID stripe size so that pपुनः_स्मृतिations करोn't fragment
	 * the stripes.
	 */
	अगर (sbi->s_stripe > 1) अणु
		sbi->s_mb_group_pपुनः_स्मृति = roundup(
			sbi->s_mb_group_pपुनः_स्मृति, sbi->s_stripe);
	पूर्ण

	sbi->s_locality_groups = alloc_percpu(काष्ठा ext4_locality_group);
	अगर (sbi->s_locality_groups == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	क्रम_each_possible_cpu(i) अणु
		काष्ठा ext4_locality_group *lg;
		lg = per_cpu_ptr(sbi->s_locality_groups, i);
		mutex_init(&lg->lg_mutex);
		क्रम (j = 0; j < PREALLOC_TB_SIZE; j++)
			INIT_LIST_HEAD(&lg->lg_pपुनः_स्मृति_list[j]);
		spin_lock_init(&lg->lg_pपुनः_स्मृति_lock);
	पूर्ण

	अगर (blk_queue_nonrot(bdev_get_queue(sb->s_bdev)))
		sbi->s_mb_max_linear_groups = 0;
	अन्यथा
		sbi->s_mb_max_linear_groups = MB_DEFAULT_LINEAR_LIMIT;
	/* init file क्रम buddy data */
	ret = ext4_mb_init_backend(sb);
	अगर (ret != 0)
		जाओ out_मुक्त_locality_groups;

	वापस 0;

out_मुक्त_locality_groups:
	मुक्त_percpu(sbi->s_locality_groups);
	sbi->s_locality_groups = शून्य;
out:
	kमुक्त(sbi->s_mb_largest_मुक्त_orders);
	kमुक्त(sbi->s_mb_largest_मुक्त_orders_locks);
	kमुक्त(sbi->s_mb_offsets);
	sbi->s_mb_offsets = शून्य;
	kमुक्त(sbi->s_mb_maxs);
	sbi->s_mb_maxs = शून्य;
	वापस ret;
पूर्ण

/* need to called with the ext4 group lock held */
अटल पूर्णांक ext4_mb_cleanup_pa(काष्ठा ext4_group_info *grp)
अणु
	काष्ठा ext4_pपुनः_स्मृति_space *pa;
	काष्ठा list_head *cur, *पंचांगp;
	पूर्णांक count = 0;

	list_क्रम_each_safe(cur, पंचांगp, &grp->bb_pपुनः_स्मृति_list) अणु
		pa = list_entry(cur, काष्ठा ext4_pपुनः_स्मृति_space, pa_group_list);
		list_del(&pa->pa_group_list);
		count++;
		kmem_cache_मुक्त(ext4_pspace_cachep, pa);
	पूर्ण
	वापस count;
पूर्ण

पूर्णांक ext4_mb_release(काष्ठा super_block *sb)
अणु
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	ext4_group_t i;
	पूर्णांक num_meta_group_infos;
	काष्ठा ext4_group_info *grinfo, ***group_info;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा kmem_cache *cachep = get_groupinfo_cache(sb->s_blocksize_bits);
	पूर्णांक count;

	अगर (sbi->s_group_info) अणु
		क्रम (i = 0; i < ngroups; i++) अणु
			cond_resched();
			grinfo = ext4_get_group_info(sb, i);
			mb_group_bb_biपंचांगap_मुक्त(grinfo);
			ext4_lock_group(sb, i);
			count = ext4_mb_cleanup_pa(grinfo);
			अगर (count)
				mb_debug(sb, "mballoc: %d PAs left\n",
					 count);
			ext4_unlock_group(sb, i);
			kmem_cache_मुक्त(cachep, grinfo);
		पूर्ण
		num_meta_group_infos = (ngroups +
				EXT4_DESC_PER_BLOCK(sb) - 1) >>
			EXT4_DESC_PER_BLOCK_BITS(sb);
		rcu_पढ़ो_lock();
		group_info = rcu_dereference(sbi->s_group_info);
		क्रम (i = 0; i < num_meta_group_infos; i++)
			kमुक्त(group_info[i]);
		kvमुक्त(group_info);
		rcu_पढ़ो_unlock();
	पूर्ण
	kमुक्त(sbi->s_mb_largest_मुक्त_orders);
	kमुक्त(sbi->s_mb_largest_मुक्त_orders_locks);
	kमुक्त(sbi->s_mb_offsets);
	kमुक्त(sbi->s_mb_maxs);
	iput(sbi->s_buddy_cache);
	अगर (sbi->s_mb_stats) अणु
		ext4_msg(sb, KERN_INFO,
		       "mballoc: %u blocks %u reqs (%u success)",
				atomic_पढ़ो(&sbi->s_bal_allocated),
				atomic_पढ़ो(&sbi->s_bal_reqs),
				atomic_पढ़ो(&sbi->s_bal_success));
		ext4_msg(sb, KERN_INFO,
		      "mballoc: %u extents scanned, %u groups scanned, %u goal hits, "
				"%u 2^N hits, %u अवरोधs, %u lost",
				atomic_पढ़ो(&sbi->s_bal_ex_scanned),
				atomic_पढ़ो(&sbi->s_bal_groups_scanned),
				atomic_पढ़ो(&sbi->s_bal_goals),
				atomic_पढ़ो(&sbi->s_bal_2orders),
				atomic_पढ़ो(&sbi->s_bal_अवरोधs),
				atomic_पढ़ो(&sbi->s_mb_lost_chunks));
		ext4_msg(sb, KERN_INFO,
		       "mballoc: %u generated and it took %llu",
				atomic_पढ़ो(&sbi->s_mb_buddies_generated),
				atomic64_पढ़ो(&sbi->s_mb_generation_समय));
		ext4_msg(sb, KERN_INFO,
		       "mballoc: %u preallocated, %u discarded",
				atomic_पढ़ो(&sbi->s_mb_pपुनः_स्मृतिated),
				atomic_पढ़ो(&sbi->s_mb_discarded));
	पूर्ण

	मुक्त_percpu(sbi->s_locality_groups);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_issue_discard(काष्ठा super_block *sb,
		ext4_group_t block_group, ext4_grpblk_t cluster, पूर्णांक count,
		काष्ठा bio **biop)
अणु
	ext4_fsblk_t discard_block;

	discard_block = (EXT4_C2B(EXT4_SB(sb), cluster) +
			 ext4_group_first_block_no(sb, block_group));
	count = EXT4_C2B(EXT4_SB(sb), count);
	trace_ext4_discard_blocks(sb,
			(अचिन्हित दीर्घ दीर्घ) discard_block, count);
	अगर (biop) अणु
		वापस __blkdev_issue_discard(sb->s_bdev,
			(sector_t)discard_block << (sb->s_blocksize_bits - 9),
			(sector_t)count << (sb->s_blocksize_bits - 9),
			GFP_NOFS, 0, biop);
	पूर्ण अन्यथा
		वापस sb_issue_discard(sb, discard_block, count, GFP_NOFS, 0);
पूर्ण

अटल व्योम ext4_मुक्त_data_in_buddy(काष्ठा super_block *sb,
				    काष्ठा ext4_मुक्त_data *entry)
अणु
	काष्ठा ext4_buddy e4b;
	काष्ठा ext4_group_info *db;
	पूर्णांक err, count = 0, count2 = 0;

	mb_debug(sb, "gonna free %u blocks in group %u (0x%p):",
		 entry->efd_count, entry->efd_group, entry);

	err = ext4_mb_load_buddy(sb, entry->efd_group, &e4b);
	/* we expect to find existing buddy because it's pinned */
	BUG_ON(err != 0);

	spin_lock(&EXT4_SB(sb)->s_md_lock);
	EXT4_SB(sb)->s_mb_मुक्त_pending -= entry->efd_count;
	spin_unlock(&EXT4_SB(sb)->s_md_lock);

	db = e4b.bd_info;
	/* there are blocks to put in buddy to make them really मुक्त */
	count += entry->efd_count;
	count2++;
	ext4_lock_group(sb, entry->efd_group);
	/* Take it out of per group rb tree */
	rb_erase(&entry->efd_node, &(db->bb_मुक्त_root));
	mb_मुक्त_blocks(शून्य, &e4b, entry->efd_start_cluster, entry->efd_count);

	/*
	 * Clear the trimmed flag क्रम the group so that the next
	 * ext4_trim_fs can trim it.
	 * If the volume is mounted with -o discard, online discard
	 * is supported and the मुक्त blocks will be trimmed online.
	 */
	अगर (!test_opt(sb, DISCARD))
		EXT4_MB_GRP_CLEAR_TRIMMED(db);

	अगर (!db->bb_मुक्त_root.rb_node) अणु
		/* No more items in the per group rb tree
		 * balance refcounts from ext4_mb_मुक्त_metadata()
		 */
		put_page(e4b.bd_buddy_page);
		put_page(e4b.bd_biपंचांगap_page);
	पूर्ण
	ext4_unlock_group(sb, entry->efd_group);
	kmem_cache_मुक्त(ext4_मुक्त_data_cachep, entry);
	ext4_mb_unload_buddy(&e4b);

	mb_debug(sb, "freed %d blocks in %d structures\n", count,
		 count2);
पूर्ण

/*
 * This function is called by the jbd2 layer once the commit has finished,
 * so we know we can मुक्त the blocks that were released with that commit.
 */
व्योम ext4_process_मुक्तd_data(काष्ठा super_block *sb, tid_t commit_tid)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_मुक्त_data *entry, *पंचांगp;
	काष्ठा bio *discard_bio = शून्य;
	काष्ठा list_head मुक्तd_data_list;
	काष्ठा list_head *cut_pos = शून्य;
	पूर्णांक err;

	INIT_LIST_HEAD(&मुक्तd_data_list);

	spin_lock(&sbi->s_md_lock);
	list_क्रम_each_entry(entry, &sbi->s_मुक्तd_data_list, efd_list) अणु
		अगर (entry->efd_tid != commit_tid)
			अवरोध;
		cut_pos = &entry->efd_list;
	पूर्ण
	अगर (cut_pos)
		list_cut_position(&मुक्तd_data_list, &sbi->s_मुक्तd_data_list,
				  cut_pos);
	spin_unlock(&sbi->s_md_lock);

	अगर (test_opt(sb, DISCARD)) अणु
		list_क्रम_each_entry(entry, &मुक्तd_data_list, efd_list) अणु
			err = ext4_issue_discard(sb, entry->efd_group,
						 entry->efd_start_cluster,
						 entry->efd_count,
						 &discard_bio);
			अगर (err && err != -EOPNOTSUPP) अणु
				ext4_msg(sb, KERN_WARNING, "discard request in"
					 " group:%d block:%d count:%d failed"
					 " with %d", entry->efd_group,
					 entry->efd_start_cluster,
					 entry->efd_count, err);
			पूर्ण अन्यथा अगर (err == -EOPNOTSUPP)
				अवरोध;
		पूर्ण

		अगर (discard_bio) अणु
			submit_bio_रुको(discard_bio);
			bio_put(discard_bio);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_safe(entry, पंचांगp, &मुक्तd_data_list, efd_list)
		ext4_मुक्त_data_in_buddy(sb, entry);
पूर्ण

पूर्णांक __init ext4_init_mballoc(व्योम)
अणु
	ext4_pspace_cachep = KMEM_CACHE(ext4_pपुनः_स्मृति_space,
					SLAB_RECLAIM_ACCOUNT);
	अगर (ext4_pspace_cachep == शून्य)
		जाओ out;

	ext4_ac_cachep = KMEM_CACHE(ext4_allocation_context,
				    SLAB_RECLAIM_ACCOUNT);
	अगर (ext4_ac_cachep == शून्य)
		जाओ out_pa_मुक्त;

	ext4_मुक्त_data_cachep = KMEM_CACHE(ext4_मुक्त_data,
					   SLAB_RECLAIM_ACCOUNT);
	अगर (ext4_मुक्त_data_cachep == शून्य)
		जाओ out_ac_मुक्त;

	वापस 0;

out_ac_मुक्त:
	kmem_cache_destroy(ext4_ac_cachep);
out_pa_मुक्त:
	kmem_cache_destroy(ext4_pspace_cachep);
out:
	वापस -ENOMEM;
पूर्ण

व्योम ext4_निकास_mballoc(व्योम)
अणु
	/*
	 * Wait क्रम completion of call_rcu()'s on ext4_pspace_cachep
	 * beक्रमe destroying the slab cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(ext4_pspace_cachep);
	kmem_cache_destroy(ext4_ac_cachep);
	kmem_cache_destroy(ext4_मुक्त_data_cachep);
	ext4_groupinfo_destroy_sद_असल();
पूर्ण


/*
 * Check quota and mark chosen space (ac->ac_b_ex) non-मुक्त in biपंचांगaps
 * Returns 0 अगर success or error code
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक
ext4_mb_mark_diskspace_used(काष्ठा ext4_allocation_context *ac,
				handle_t *handle, अचिन्हित पूर्णांक reserv_clstrs)
अणु
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा ext4_group_desc *gdp;
	काष्ठा buffer_head *gdp_bh;
	काष्ठा ext4_sb_info *sbi;
	काष्ठा super_block *sb;
	ext4_fsblk_t block;
	पूर्णांक err, len;

	BUG_ON(ac->ac_status != AC_STATUS_FOUND);
	BUG_ON(ac->ac_b_ex.fe_len <= 0);

	sb = ac->ac_sb;
	sbi = EXT4_SB(sb);

	biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, ac->ac_b_ex.fe_group);
	अगर (IS_ERR(biपंचांगap_bh)) अणु
		err = PTR_ERR(biपंचांगap_bh);
		biपंचांगap_bh = शून्य;
		जाओ out_err;
	पूर्ण

	BUFFER_TRACE(biपंचांगap_bh, "getting write access");
	err = ext4_journal_get_ग_लिखो_access(handle, biपंचांगap_bh);
	अगर (err)
		जाओ out_err;

	err = -EIO;
	gdp = ext4_get_group_desc(sb, ac->ac_b_ex.fe_group, &gdp_bh);
	अगर (!gdp)
		जाओ out_err;

	ext4_debug("using block group %u(%d)\n", ac->ac_b_ex.fe_group,
			ext4_मुक्त_group_clusters(sb, gdp));

	BUFFER_TRACE(gdp_bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, gdp_bh);
	अगर (err)
		जाओ out_err;

	block = ext4_grp_offs_to_block(sb, &ac->ac_b_ex);

	len = EXT4_C2B(sbi, ac->ac_b_ex.fe_len);
	अगर (!ext4_inode_block_valid(ac->ac_inode, block, len)) अणु
		ext4_error(sb, "Allocating blocks %llu-%llu which overlap "
			   "fs metadata", block, block+len);
		/* File प्रणाली mounted not to panic on error
		 * Fix the biपंचांगap and वापस EFSCORRUPTED
		 * We leak some of the blocks here.
		 */
		ext4_lock_group(sb, ac->ac_b_ex.fe_group);
		ext4_set_bits(biपंचांगap_bh->b_data, ac->ac_b_ex.fe_start,
			      ac->ac_b_ex.fe_len);
		ext4_unlock_group(sb, ac->ac_b_ex.fe_group);
		err = ext4_handle_dirty_metadata(handle, शून्य, biपंचांगap_bh);
		अगर (!err)
			err = -EFSCORRUPTED;
		जाओ out_err;
	पूर्ण

	ext4_lock_group(sb, ac->ac_b_ex.fe_group);
#अगर_घोषित AGGRESSIVE_CHECK
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < ac->ac_b_ex.fe_len; i++) अणु
			BUG_ON(mb_test_bit(ac->ac_b_ex.fe_start + i,
						biपंचांगap_bh->b_data));
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	ext4_set_bits(biपंचांगap_bh->b_data, ac->ac_b_ex.fe_start,
		      ac->ac_b_ex.fe_len);
	अगर (ext4_has_group_desc_csum(sb) &&
	    (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))) अणु
		gdp->bg_flags &= cpu_to_le16(~EXT4_BG_BLOCK_UNINIT);
		ext4_मुक्त_group_clusters_set(sb, gdp,
					     ext4_मुक्त_clusters_after_init(sb,
						ac->ac_b_ex.fe_group, gdp));
	पूर्ण
	len = ext4_मुक्त_group_clusters(sb, gdp) - ac->ac_b_ex.fe_len;
	ext4_मुक्त_group_clusters_set(sb, gdp, len);
	ext4_block_biपंचांगap_csum_set(sb, ac->ac_b_ex.fe_group, gdp, biपंचांगap_bh);
	ext4_group_desc_csum_set(sb, ac->ac_b_ex.fe_group, gdp);

	ext4_unlock_group(sb, ac->ac_b_ex.fe_group);
	percpu_counter_sub(&sbi->s_मुक्तclusters_counter, ac->ac_b_ex.fe_len);
	/*
	 * Now reduce the dirty block count also. Should not go negative
	 */
	अगर (!(ac->ac_flags & EXT4_MB_DELALLOC_RESERVED))
		/* release all the reserved blocks अगर non delalloc */
		percpu_counter_sub(&sbi->s_dirtyclusters_counter,
				   reserv_clstrs);

	अगर (sbi->s_log_groups_per_flex) अणु
		ext4_group_t flex_group = ext4_flex_group(sbi,
							  ac->ac_b_ex.fe_group);
		atomic64_sub(ac->ac_b_ex.fe_len,
			     &sbi_array_rcu_deref(sbi, s_flex_groups,
						  flex_group)->मुक्त_clusters);
	पूर्ण

	err = ext4_handle_dirty_metadata(handle, शून्य, biपंचांगap_bh);
	अगर (err)
		जाओ out_err;
	err = ext4_handle_dirty_metadata(handle, शून्य, gdp_bh);

out_err:
	brअन्यथा(biपंचांगap_bh);
	वापस err;
पूर्ण

/*
 * Idempotent helper क्रम Ext4 fast commit replay path to set the state of
 * blocks in biपंचांगaps and update counters.
 */
व्योम ext4_mb_mark_bb(काष्ठा super_block *sb, ext4_fsblk_t block,
			पूर्णांक len, पूर्णांक state)
अणु
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा ext4_group_desc *gdp;
	काष्ठा buffer_head *gdp_bh;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_group_t group;
	ext4_grpblk_t blkoff;
	पूर्णांक i, clen, err;
	पूर्णांक alपढ़ोy;

	clen = EXT4_B2C(sbi, len);

	ext4_get_group_no_and_offset(sb, block, &group, &blkoff);
	biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, group);
	अगर (IS_ERR(biपंचांगap_bh)) अणु
		err = PTR_ERR(biपंचांगap_bh);
		biपंचांगap_bh = शून्य;
		जाओ out_err;
	पूर्ण

	err = -EIO;
	gdp = ext4_get_group_desc(sb, group, &gdp_bh);
	अगर (!gdp)
		जाओ out_err;

	ext4_lock_group(sb, group);
	alपढ़ोy = 0;
	क्रम (i = 0; i < clen; i++)
		अगर (!mb_test_bit(blkoff + i, biपंचांगap_bh->b_data) == !state)
			alपढ़ोy++;

	अगर (state)
		ext4_set_bits(biपंचांगap_bh->b_data, blkoff, clen);
	अन्यथा
		mb_test_and_clear_bits(biपंचांगap_bh->b_data, blkoff, clen);
	अगर (ext4_has_group_desc_csum(sb) &&
	    (gdp->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT))) अणु
		gdp->bg_flags &= cpu_to_le16(~EXT4_BG_BLOCK_UNINIT);
		ext4_मुक्त_group_clusters_set(sb, gdp,
					     ext4_मुक्त_clusters_after_init(sb,
						group, gdp));
	पूर्ण
	अगर (state)
		clen = ext4_मुक्त_group_clusters(sb, gdp) - clen + alपढ़ोy;
	अन्यथा
		clen = ext4_मुक्त_group_clusters(sb, gdp) + clen - alपढ़ोy;

	ext4_मुक्त_group_clusters_set(sb, gdp, clen);
	ext4_block_biपंचांगap_csum_set(sb, group, gdp, biपंचांगap_bh);
	ext4_group_desc_csum_set(sb, group, gdp);

	ext4_unlock_group(sb, group);

	अगर (sbi->s_log_groups_per_flex) अणु
		ext4_group_t flex_group = ext4_flex_group(sbi, group);

		atomic64_sub(len,
			     &sbi_array_rcu_deref(sbi, s_flex_groups,
						  flex_group)->मुक्त_clusters);
	पूर्ण

	err = ext4_handle_dirty_metadata(शून्य, शून्य, biपंचांगap_bh);
	अगर (err)
		जाओ out_err;
	sync_dirty_buffer(biपंचांगap_bh);
	err = ext4_handle_dirty_metadata(शून्य, शून्य, gdp_bh);
	sync_dirty_buffer(gdp_bh);

out_err:
	brअन्यथा(biपंचांगap_bh);
पूर्ण

/*
 * here we normalize request क्रम locality group
 * Group request are normalized to s_mb_group_pपुनः_स्मृति, which goes to
 * s_strip अगर we set the same via mount option.
 * s_mb_group_pपुनः_स्मृति can be configured via
 * /sys/fs/ext4/<partition>/mb_group_pपुनः_स्मृति
 *
 * XXX: should we try to pपुनः_स्मृतिate more than the group has now?
 */
अटल व्योम ext4_mb_normalize_group_request(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा super_block *sb = ac->ac_sb;
	काष्ठा ext4_locality_group *lg = ac->ac_lg;

	BUG_ON(lg == शून्य);
	ac->ac_g_ex.fe_len = EXT4_SB(sb)->s_mb_group_pपुनः_स्मृति;
	mb_debug(sb, "goal %u blocks for locality group\n", ac->ac_g_ex.fe_len);
पूर्ण

/*
 * Normalization means making request better in terms of
 * size and alignment
 */
अटल noअंतरभूत_क्रम_stack व्योम
ext4_mb_normalize_request(काष्ठा ext4_allocation_context *ac,
				काष्ठा ext4_allocation_request *ar)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);
	पूर्णांक bsbits, max;
	ext4_lblk_t end;
	loff_t size, start_off;
	loff_t orig_size __maybe_unused;
	ext4_lblk_t start;
	काष्ठा ext4_inode_info *ei = EXT4_I(ac->ac_inode);
	काष्ठा ext4_pपुनः_स्मृति_space *pa;

	/* करो normalize only data requests, metadata requests
	   करो not need pपुनः_स्मृतिation */
	अगर (!(ac->ac_flags & EXT4_MB_HINT_DATA))
		वापस;

	/* someसमय caller may want exact blocks */
	अगर (unlikely(ac->ac_flags & EXT4_MB_HINT_GOAL_ONLY))
		वापस;

	/* caller may indicate that pपुनः_स्मृतिation isn't
	 * required (it's a tail, क्रम example) */
	अगर (ac->ac_flags & EXT4_MB_HINT_NOPREALLOC)
		वापस;

	अगर (ac->ac_flags & EXT4_MB_HINT_GROUP_ALLOC) अणु
		ext4_mb_normalize_group_request(ac);
		वापस ;
	पूर्ण

	bsbits = ac->ac_sb->s_blocksize_bits;

	/* first, let's learn actual file size
	 * given current request is allocated */
	size = ac->ac_o_ex.fe_logical + EXT4_C2B(sbi, ac->ac_o_ex.fe_len);
	size = size << bsbits;
	अगर (size < i_size_पढ़ो(ac->ac_inode))
		size = i_size_पढ़ो(ac->ac_inode);
	orig_size = size;

	/* max size of मुक्त chunks */
	max = 2 << bsbits;

#घोषणा NRL_CHECK_SIZE(req, size, max, chunk_size)	\
		(req <= (size) || max <= (chunk_size))

	/* first, try to predict filesize */
	/* XXX: should this table be tunable? */
	start_off = 0;
	अगर (size <= 16 * 1024) अणु
		size = 16 * 1024;
	पूर्ण अन्यथा अगर (size <= 32 * 1024) अणु
		size = 32 * 1024;
	पूर्ण अन्यथा अगर (size <= 64 * 1024) अणु
		size = 64 * 1024;
	पूर्ण अन्यथा अगर (size <= 128 * 1024) अणु
		size = 128 * 1024;
	पूर्ण अन्यथा अगर (size <= 256 * 1024) अणु
		size = 256 * 1024;
	पूर्ण अन्यथा अगर (size <= 512 * 1024) अणु
		size = 512 * 1024;
	पूर्ण अन्यथा अगर (size <= 1024 * 1024) अणु
		size = 1024 * 1024;
	पूर्ण अन्यथा अगर (NRL_CHECK_SIZE(size, 4 * 1024 * 1024, max, 2 * 1024)) अणु
		start_off = ((loff_t)ac->ac_o_ex.fe_logical >>
						(21 - bsbits)) << 21;
		size = 2 * 1024 * 1024;
	पूर्ण अन्यथा अगर (NRL_CHECK_SIZE(size, 8 * 1024 * 1024, max, 4 * 1024)) अणु
		start_off = ((loff_t)ac->ac_o_ex.fe_logical >>
							(22 - bsbits)) << 22;
		size = 4 * 1024 * 1024;
	पूर्ण अन्यथा अगर (NRL_CHECK_SIZE(ac->ac_o_ex.fe_len,
					(8<<20)>>bsbits, max, 8 * 1024)) अणु
		start_off = ((loff_t)ac->ac_o_ex.fe_logical >>
							(23 - bsbits)) << 23;
		size = 8 * 1024 * 1024;
	पूर्ण अन्यथा अणु
		start_off = (loff_t) ac->ac_o_ex.fe_logical << bsbits;
		size	  = (loff_t) EXT4_C2B(EXT4_SB(ac->ac_sb),
					      ac->ac_o_ex.fe_len) << bsbits;
	पूर्ण
	size = size >> bsbits;
	start = start_off >> bsbits;

	/* करोn't cover alपढ़ोy allocated blocks in selected range */
	अगर (ar->pleft && start <= ar->lleft) अणु
		size -= ar->lleft + 1 - start;
		start = ar->lleft + 1;
	पूर्ण
	अगर (ar->pright && start + size - 1 >= ar->lright)
		size -= start + size - ar->lright;

	/*
	 * Trim allocation request क्रम fileप्रणालीs with artअगरicially small
	 * groups.
	 */
	अगर (size > EXT4_BLOCKS_PER_GROUP(ac->ac_sb))
		size = EXT4_BLOCKS_PER_GROUP(ac->ac_sb);

	end = start + size;

	/* check we करोn't cross alपढ़ोy pपुनः_स्मृतिated blocks */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pa, &ei->i_pपुनः_स्मृति_list, pa_inode_list) अणु
		ext4_lblk_t pa_end;

		अगर (pa->pa_deleted)
			जारी;
		spin_lock(&pa->pa_lock);
		अगर (pa->pa_deleted) अणु
			spin_unlock(&pa->pa_lock);
			जारी;
		पूर्ण

		pa_end = pa->pa_lstart + EXT4_C2B(EXT4_SB(ac->ac_sb),
						  pa->pa_len);

		/* PA must not overlap original request */
		BUG_ON(!(ac->ac_o_ex.fe_logical >= pa_end ||
			ac->ac_o_ex.fe_logical < pa->pa_lstart));

		/* skip PAs this normalized request करोesn't overlap with */
		अगर (pa->pa_lstart >= end || pa_end <= start) अणु
			spin_unlock(&pa->pa_lock);
			जारी;
		पूर्ण
		BUG_ON(pa->pa_lstart <= start && pa_end >= end);

		/* adjust start or end to be adjacent to this pa */
		अगर (pa_end <= ac->ac_o_ex.fe_logical) अणु
			BUG_ON(pa_end < start);
			start = pa_end;
		पूर्ण अन्यथा अगर (pa->pa_lstart > ac->ac_o_ex.fe_logical) अणु
			BUG_ON(pa->pa_lstart > end);
			end = pa->pa_lstart;
		पूर्ण
		spin_unlock(&pa->pa_lock);
	पूर्ण
	rcu_पढ़ो_unlock();
	size = end - start;

	/* XXX: extra loop to check we really करोn't overlap pपुनः_स्मृतिations */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pa, &ei->i_pपुनः_स्मृति_list, pa_inode_list) अणु
		ext4_lblk_t pa_end;

		spin_lock(&pa->pa_lock);
		अगर (pa->pa_deleted == 0) अणु
			pa_end = pa->pa_lstart + EXT4_C2B(EXT4_SB(ac->ac_sb),
							  pa->pa_len);
			BUG_ON(!(start >= pa_end || end <= pa->pa_lstart));
		पूर्ण
		spin_unlock(&pa->pa_lock);
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (start + size <= ac->ac_o_ex.fe_logical &&
			start > ac->ac_o_ex.fe_logical) अणु
		ext4_msg(ac->ac_sb, KERN_ERR,
			 "start %lu, size %lu, fe_logical %lu",
			 (अचिन्हित दीर्घ) start, (अचिन्हित दीर्घ) size,
			 (अचिन्हित दीर्घ) ac->ac_o_ex.fe_logical);
		BUG();
	पूर्ण
	BUG_ON(size <= 0 || size > EXT4_BLOCKS_PER_GROUP(ac->ac_sb));

	/* now prepare goal request */

	/* XXX: is it better to align blocks WRT to logical
	 * placement or satisfy big request as is */
	ac->ac_g_ex.fe_logical = start;
	ac->ac_g_ex.fe_len = EXT4_NUM_B2C(sbi, size);

	/* define goal start in order to merge */
	अगर (ar->pright && (ar->lright == (start + size))) अणु
		/* merge to the right */
		ext4_get_group_no_and_offset(ac->ac_sb, ar->pright - size,
						&ac->ac_f_ex.fe_group,
						&ac->ac_f_ex.fe_start);
		ac->ac_flags |= EXT4_MB_HINT_TRY_GOAL;
	पूर्ण
	अगर (ar->pleft && (ar->lleft + 1 == start)) अणु
		/* merge to the left */
		ext4_get_group_no_and_offset(ac->ac_sb, ar->pleft + 1,
						&ac->ac_f_ex.fe_group,
						&ac->ac_f_ex.fe_start);
		ac->ac_flags |= EXT4_MB_HINT_TRY_GOAL;
	पूर्ण

	mb_debug(ac->ac_sb, "goal: %lld(was %lld) blocks at %u\n", size,
		 orig_size, start);
पूर्ण

अटल व्योम ext4_mb_collect_stats(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);

	अगर (sbi->s_mb_stats && ac->ac_g_ex.fe_len >= 1) अणु
		atomic_inc(&sbi->s_bal_reqs);
		atomic_add(ac->ac_b_ex.fe_len, &sbi->s_bal_allocated);
		अगर (ac->ac_b_ex.fe_len >= ac->ac_o_ex.fe_len)
			atomic_inc(&sbi->s_bal_success);
		atomic_add(ac->ac_found, &sbi->s_bal_ex_scanned);
		atomic_add(ac->ac_groups_scanned, &sbi->s_bal_groups_scanned);
		अगर (ac->ac_g_ex.fe_start == ac->ac_b_ex.fe_start &&
				ac->ac_g_ex.fe_group == ac->ac_b_ex.fe_group)
			atomic_inc(&sbi->s_bal_goals);
		अगर (ac->ac_found > sbi->s_mb_max_to_scan)
			atomic_inc(&sbi->s_bal_अवरोधs);
	पूर्ण

	अगर (ac->ac_op == EXT4_MB_HISTORY_ALLOC)
		trace_ext4_mballoc_alloc(ac);
	अन्यथा
		trace_ext4_mballoc_pपुनः_स्मृति(ac);
पूर्ण

/*
 * Called on failure; मुक्त up any blocks from the inode PA क्रम this
 * context.  We करोn't need this क्रम MB_GROUP_PA because we only change
 * pa_मुक्त in ext4_mb_release_context(), but on failure, we've alपढ़ोy
 * zeroed out ac->ac_b_ex.fe_len, so group_pa->pa_मुक्त is not changed.
 */
अटल व्योम ext4_discard_allocated_blocks(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा ext4_pपुनः_स्मृति_space *pa = ac->ac_pa;
	काष्ठा ext4_buddy e4b;
	पूर्णांक err;

	अगर (pa == शून्य) अणु
		अगर (ac->ac_f_ex.fe_len == 0)
			वापस;
		err = ext4_mb_load_buddy(ac->ac_sb, ac->ac_f_ex.fe_group, &e4b);
		अगर (err) अणु
			/*
			 * This should never happen since we pin the
			 * pages in the ext4_allocation_context so
			 * ext4_mb_load_buddy() should never fail.
			 */
			WARN(1, "mb_load_buddy failed (%d)", err);
			वापस;
		पूर्ण
		ext4_lock_group(ac->ac_sb, ac->ac_f_ex.fe_group);
		mb_मुक्त_blocks(ac->ac_inode, &e4b, ac->ac_f_ex.fe_start,
			       ac->ac_f_ex.fe_len);
		ext4_unlock_group(ac->ac_sb, ac->ac_f_ex.fe_group);
		ext4_mb_unload_buddy(&e4b);
		वापस;
	पूर्ण
	अगर (pa->pa_type == MB_INODE_PA)
		pa->pa_मुक्त += ac->ac_b_ex.fe_len;
पूर्ण

/*
 * use blocks pपुनः_स्मृतिated to inode
 */
अटल व्योम ext4_mb_use_inode_pa(काष्ठा ext4_allocation_context *ac,
				काष्ठा ext4_pपुनः_स्मृति_space *pa)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);
	ext4_fsblk_t start;
	ext4_fsblk_t end;
	पूर्णांक len;

	/* found pपुनः_स्मृतिated blocks, use them */
	start = pa->pa_pstart + (ac->ac_o_ex.fe_logical - pa->pa_lstart);
	end = min(pa->pa_pstart + EXT4_C2B(sbi, pa->pa_len),
		  start + EXT4_C2B(sbi, ac->ac_o_ex.fe_len));
	len = EXT4_NUM_B2C(sbi, end - start);
	ext4_get_group_no_and_offset(ac->ac_sb, start, &ac->ac_b_ex.fe_group,
					&ac->ac_b_ex.fe_start);
	ac->ac_b_ex.fe_len = len;
	ac->ac_status = AC_STATUS_FOUND;
	ac->ac_pa = pa;

	BUG_ON(start < pa->pa_pstart);
	BUG_ON(end > pa->pa_pstart + EXT4_C2B(sbi, pa->pa_len));
	BUG_ON(pa->pa_मुक्त < len);
	pa->pa_मुक्त -= len;

	mb_debug(ac->ac_sb, "use %llu/%d from inode pa %p\n", start, len, pa);
पूर्ण

/*
 * use blocks pपुनः_स्मृतिated to locality group
 */
अटल व्योम ext4_mb_use_group_pa(काष्ठा ext4_allocation_context *ac,
				काष्ठा ext4_pपुनः_स्मृति_space *pa)
अणु
	अचिन्हित पूर्णांक len = ac->ac_o_ex.fe_len;

	ext4_get_group_no_and_offset(ac->ac_sb, pa->pa_pstart,
					&ac->ac_b_ex.fe_group,
					&ac->ac_b_ex.fe_start);
	ac->ac_b_ex.fe_len = len;
	ac->ac_status = AC_STATUS_FOUND;
	ac->ac_pa = pa;

	/* we करोn't correct pa_pstart or pa_plen here to aव्योम
	 * possible race when the group is being loaded concurrently
	 * instead we correct pa later, after blocks are marked
	 * in on-disk biपंचांगap -- see ext4_mb_release_context()
	 * Other CPUs are prevented from allocating from this pa by lg_mutex
	 */
	mb_debug(ac->ac_sb, "use %u/%u from group pa %p\n",
		 pa->pa_lstart-len, len, pa);
पूर्ण

/*
 * Return the pपुनः_स्मृति space that have minimal distance
 * from the goal block. @cpa is the pपुनः_स्मृति
 * space that is having currently known minimal distance
 * from the goal block.
 */
अटल काष्ठा ext4_pपुनः_स्मृति_space *
ext4_mb_check_group_pa(ext4_fsblk_t goal_block,
			काष्ठा ext4_pपुनः_स्मृति_space *pa,
			काष्ठा ext4_pपुनः_स्मृति_space *cpa)
अणु
	ext4_fsblk_t cur_distance, new_distance;

	अगर (cpa == शून्य) अणु
		atomic_inc(&pa->pa_count);
		वापस pa;
	पूर्ण
	cur_distance = असल(goal_block - cpa->pa_pstart);
	new_distance = असल(goal_block - pa->pa_pstart);

	अगर (cur_distance <= new_distance)
		वापस cpa;

	/* drop the previous reference */
	atomic_dec(&cpa->pa_count);
	atomic_inc(&pa->pa_count);
	वापस pa;
पूर्ण

/*
 * search goal blocks in pपुनः_स्मृतिated space
 */
अटल noअंतरभूत_क्रम_stack bool
ext4_mb_use_pपुनः_स्मृतिated(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);
	पूर्णांक order, i;
	काष्ठा ext4_inode_info *ei = EXT4_I(ac->ac_inode);
	काष्ठा ext4_locality_group *lg;
	काष्ठा ext4_pपुनः_स्मृति_space *pa, *cpa = शून्य;
	ext4_fsblk_t goal_block;

	/* only data can be pपुनः_स्मृतिated */
	अगर (!(ac->ac_flags & EXT4_MB_HINT_DATA))
		वापस false;

	/* first, try per-file pपुनः_स्मृतिation */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pa, &ei->i_pपुनः_स्मृति_list, pa_inode_list) अणु

		/* all fields in this condition करोn't change,
		 * so we can skip locking क्रम them */
		अगर (ac->ac_o_ex.fe_logical < pa->pa_lstart ||
		    ac->ac_o_ex.fe_logical >= (pa->pa_lstart +
					       EXT4_C2B(sbi, pa->pa_len)))
			जारी;

		/* non-extent files can't have physical blocks past 2^32 */
		अगर (!(ext4_test_inode_flag(ac->ac_inode, EXT4_INODE_EXTENTS)) &&
		    (pa->pa_pstart + EXT4_C2B(sbi, pa->pa_len) >
		     EXT4_MAX_BLOCK_खाता_PHYS))
			जारी;

		/* found pपुनः_स्मृतिated blocks, use them */
		spin_lock(&pa->pa_lock);
		अगर (pa->pa_deleted == 0 && pa->pa_मुक्त) अणु
			atomic_inc(&pa->pa_count);
			ext4_mb_use_inode_pa(ac, pa);
			spin_unlock(&pa->pa_lock);
			ac->ac_criteria = 10;
			rcu_पढ़ो_unlock();
			वापस true;
		पूर्ण
		spin_unlock(&pa->pa_lock);
	पूर्ण
	rcu_पढ़ो_unlock();

	/* can we use group allocation? */
	अगर (!(ac->ac_flags & EXT4_MB_HINT_GROUP_ALLOC))
		वापस false;

	/* inode may have no locality group क्रम some reason */
	lg = ac->ac_lg;
	अगर (lg == शून्य)
		वापस false;
	order  = fls(ac->ac_o_ex.fe_len) - 1;
	अगर (order > PREALLOC_TB_SIZE - 1)
		/* The max size of hash table is PREALLOC_TB_SIZE */
		order = PREALLOC_TB_SIZE - 1;

	goal_block = ext4_grp_offs_to_block(ac->ac_sb, &ac->ac_g_ex);
	/*
	 * search क्रम the pपुनः_स्मृति space that is having
	 * minimal distance from the goal block.
	 */
	क्रम (i = order; i < PREALLOC_TB_SIZE; i++) अणु
		rcu_पढ़ो_lock();
		list_क्रम_each_entry_rcu(pa, &lg->lg_pपुनः_स्मृति_list[i],
					pa_inode_list) अणु
			spin_lock(&pa->pa_lock);
			अगर (pa->pa_deleted == 0 &&
					pa->pa_मुक्त >= ac->ac_o_ex.fe_len) अणु

				cpa = ext4_mb_check_group_pa(goal_block,
								pa, cpa);
			पूर्ण
			spin_unlock(&pa->pa_lock);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	अगर (cpa) अणु
		ext4_mb_use_group_pa(ac, cpa);
		ac->ac_criteria = 20;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * the function goes through all block मुक्तd in the group
 * but not yet committed and marks them used in in-core biपंचांगap.
 * buddy must be generated from this biपंचांगap
 * Need to be called with the ext4 group lock held
 */
अटल व्योम ext4_mb_generate_from_मुक्तlist(काष्ठा super_block *sb, व्योम *biपंचांगap,
						ext4_group_t group)
अणु
	काष्ठा rb_node *n;
	काष्ठा ext4_group_info *grp;
	काष्ठा ext4_मुक्त_data *entry;

	grp = ext4_get_group_info(sb, group);
	n = rb_first(&(grp->bb_मुक्त_root));

	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा ext4_मुक्त_data, efd_node);
		ext4_set_bits(biपंचांगap, entry->efd_start_cluster, entry->efd_count);
		n = rb_next(n);
	पूर्ण
	वापस;
पूर्ण

/*
 * the function goes through all pपुनः_स्मृतिation in this group and marks them
 * used in in-core biपंचांगap. buddy must be generated from this biपंचांगap
 * Need to be called with ext4 group lock held
 */
अटल noअंतरभूत_क्रम_stack
व्योम ext4_mb_generate_from_pa(काष्ठा super_block *sb, व्योम *biपंचांगap,
					ext4_group_t group)
अणु
	काष्ठा ext4_group_info *grp = ext4_get_group_info(sb, group);
	काष्ठा ext4_pपुनः_स्मृति_space *pa;
	काष्ठा list_head *cur;
	ext4_group_t groupnr;
	ext4_grpblk_t start;
	पूर्णांक pपुनः_स्मृतिated = 0;
	पूर्णांक len;

	/* all क्रमm of pपुनः_स्मृतिation discards first load group,
	 * so the only competing code is pपुनः_स्मृतिation use.
	 * we करोn't need any locking here
	 * notice we करो NOT ignore pपुनः_स्मृतिations with pa_deleted
	 * otherwise we could leave used blocks available क्रम
	 * allocation in buddy when concurrent ext4_mb_put_pa()
	 * is dropping pपुनः_स्मृतिation
	 */
	list_क्रम_each(cur, &grp->bb_pपुनः_स्मृति_list) अणु
		pa = list_entry(cur, काष्ठा ext4_pपुनः_स्मृति_space, pa_group_list);
		spin_lock(&pa->pa_lock);
		ext4_get_group_no_and_offset(sb, pa->pa_pstart,
					     &groupnr, &start);
		len = pa->pa_len;
		spin_unlock(&pa->pa_lock);
		अगर (unlikely(len == 0))
			जारी;
		BUG_ON(groupnr != group);
		ext4_set_bits(biपंचांगap, start, len);
		pपुनः_स्मृतिated += len;
	पूर्ण
	mb_debug(sb, "preallocated %d for group %u\n", pपुनः_स्मृतिated, group);
पूर्ण

अटल व्योम ext4_mb_mark_pa_deleted(काष्ठा super_block *sb,
				    काष्ठा ext4_pपुनः_स्मृति_space *pa)
अणु
	काष्ठा ext4_inode_info *ei;

	अगर (pa->pa_deleted) अणु
		ext4_warning(sb, "deleted pa, type:%d, pblk:%llu, lblk:%u, len:%d\n",
			     pa->pa_type, pa->pa_pstart, pa->pa_lstart,
			     pa->pa_len);
		वापस;
	पूर्ण

	pa->pa_deleted = 1;

	अगर (pa->pa_type == MB_INODE_PA) अणु
		ei = EXT4_I(pa->pa_inode);
		atomic_dec(&ei->i_pपुनः_स्मृति_active);
	पूर्ण
पूर्ण

अटल व्योम ext4_mb_pa_callback(काष्ठा rcu_head *head)
अणु
	काष्ठा ext4_pपुनः_स्मृति_space *pa;
	pa = container_of(head, काष्ठा ext4_pपुनः_स्मृति_space, u.pa_rcu);

	BUG_ON(atomic_पढ़ो(&pa->pa_count));
	BUG_ON(pa->pa_deleted == 0);
	kmem_cache_मुक्त(ext4_pspace_cachep, pa);
पूर्ण

/*
 * drops a reference to pपुनः_स्मृतिated space descriptor
 * अगर this was the last reference and the space is consumed
 */
अटल व्योम ext4_mb_put_pa(काष्ठा ext4_allocation_context *ac,
			काष्ठा super_block *sb, काष्ठा ext4_pपुनः_स्मृति_space *pa)
अणु
	ext4_group_t grp;
	ext4_fsblk_t grp_blk;

	/* in this लघु winकरोw concurrent discard can set pa_deleted */
	spin_lock(&pa->pa_lock);
	अगर (!atomic_dec_and_test(&pa->pa_count) || pa->pa_मुक्त != 0) अणु
		spin_unlock(&pa->pa_lock);
		वापस;
	पूर्ण

	अगर (pa->pa_deleted == 1) अणु
		spin_unlock(&pa->pa_lock);
		वापस;
	पूर्ण

	ext4_mb_mark_pa_deleted(sb, pa);
	spin_unlock(&pa->pa_lock);

	grp_blk = pa->pa_pstart;
	/*
	 * If करोing group-based pपुनः_स्मृतिation, pa_pstart may be in the
	 * next group when pa is used up
	 */
	अगर (pa->pa_type == MB_GROUP_PA)
		grp_blk--;

	grp = ext4_get_group_number(sb, grp_blk);

	/*
	 * possible race:
	 *
	 *  P1 (buddy init)			P2 (regular allocation)
	 *					find block B in PA
	 *  copy on-disk biपंचांगap to buddy
	 *  					mark B in on-disk biपंचांगap
	 *					drop PA from group
	 *  mark all PAs in buddy
	 *
	 * thus, P1 initializes buddy with B available. to prevent this
	 * we make "copy" and "mark all PAs" atomic and serialize "drop PA"
	 * against that pair
	 */
	ext4_lock_group(sb, grp);
	list_del(&pa->pa_group_list);
	ext4_unlock_group(sb, grp);

	spin_lock(pa->pa_obj_lock);
	list_del_rcu(&pa->pa_inode_list);
	spin_unlock(pa->pa_obj_lock);

	call_rcu(&(pa)->u.pa_rcu, ext4_mb_pa_callback);
पूर्ण

/*
 * creates new pपुनः_स्मृतिated space क्रम given inode
 */
अटल noअंतरभूत_क्रम_stack व्योम
ext4_mb_new_inode_pa(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा super_block *sb = ac->ac_sb;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_pपुनः_स्मृति_space *pa;
	काष्ठा ext4_group_info *grp;
	काष्ठा ext4_inode_info *ei;

	/* pपुनः_स्मृतिate only when found space is larger then requested */
	BUG_ON(ac->ac_o_ex.fe_len >= ac->ac_b_ex.fe_len);
	BUG_ON(ac->ac_status != AC_STATUS_FOUND);
	BUG_ON(!S_ISREG(ac->ac_inode->i_mode));
	BUG_ON(ac->ac_pa == शून्य);

	pa = ac->ac_pa;

	अगर (ac->ac_b_ex.fe_len < ac->ac_g_ex.fe_len) अणु
		पूर्णांक winl;
		पूर्णांक wins;
		पूर्णांक win;
		पूर्णांक offs;

		/* we can't allocate as much as normalizer wants.
		 * so, found space must get proper lstart
		 * to cover original request */
		BUG_ON(ac->ac_g_ex.fe_logical > ac->ac_o_ex.fe_logical);
		BUG_ON(ac->ac_g_ex.fe_len < ac->ac_o_ex.fe_len);

		/* we're limited by original request in that
		 * logical block must be covered any way
		 * winl is winकरोw we can move our chunk within */
		winl = ac->ac_o_ex.fe_logical - ac->ac_g_ex.fe_logical;

		/* also, we should cover whole original request */
		wins = EXT4_C2B(sbi, ac->ac_b_ex.fe_len - ac->ac_o_ex.fe_len);

		/* the smallest one defines real winकरोw */
		win = min(winl, wins);

		offs = ac->ac_o_ex.fe_logical %
			EXT4_C2B(sbi, ac->ac_b_ex.fe_len);
		अगर (offs && offs < win)
			win = offs;

		ac->ac_b_ex.fe_logical = ac->ac_o_ex.fe_logical -
			EXT4_NUM_B2C(sbi, win);
		BUG_ON(ac->ac_o_ex.fe_logical < ac->ac_b_ex.fe_logical);
		BUG_ON(ac->ac_o_ex.fe_len > ac->ac_b_ex.fe_len);
	पूर्ण

	/* pपुनः_स्मृतिation can change ac_b_ex, thus we store actually
	 * allocated blocks क्रम history */
	ac->ac_f_ex = ac->ac_b_ex;

	pa->pa_lstart = ac->ac_b_ex.fe_logical;
	pa->pa_pstart = ext4_grp_offs_to_block(sb, &ac->ac_b_ex);
	pa->pa_len = ac->ac_b_ex.fe_len;
	pa->pa_मुक्त = pa->pa_len;
	spin_lock_init(&pa->pa_lock);
	INIT_LIST_HEAD(&pa->pa_inode_list);
	INIT_LIST_HEAD(&pa->pa_group_list);
	pa->pa_deleted = 0;
	pa->pa_type = MB_INODE_PA;

	mb_debug(sb, "new inode pa %p: %llu/%d for %u\n", pa, pa->pa_pstart,
		 pa->pa_len, pa->pa_lstart);
	trace_ext4_mb_new_inode_pa(ac, pa);

	ext4_mb_use_inode_pa(ac, pa);
	atomic_add(pa->pa_मुक्त, &sbi->s_mb_pपुनः_स्मृतिated);

	ei = EXT4_I(ac->ac_inode);
	grp = ext4_get_group_info(sb, ac->ac_b_ex.fe_group);

	pa->pa_obj_lock = &ei->i_pपुनः_स्मृति_lock;
	pa->pa_inode = ac->ac_inode;

	list_add(&pa->pa_group_list, &grp->bb_pपुनः_स्मृति_list);

	spin_lock(pa->pa_obj_lock);
	list_add_rcu(&pa->pa_inode_list, &ei->i_pपुनः_स्मृति_list);
	spin_unlock(pa->pa_obj_lock);
	atomic_inc(&ei->i_pपुनः_स्मृति_active);
पूर्ण

/*
 * creates new pपुनः_स्मृतिated space क्रम locality group inodes beदीर्घs to
 */
अटल noअंतरभूत_क्रम_stack व्योम
ext4_mb_new_group_pa(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा super_block *sb = ac->ac_sb;
	काष्ठा ext4_locality_group *lg;
	काष्ठा ext4_pपुनः_स्मृति_space *pa;
	काष्ठा ext4_group_info *grp;

	/* pपुनः_स्मृतिate only when found space is larger then requested */
	BUG_ON(ac->ac_o_ex.fe_len >= ac->ac_b_ex.fe_len);
	BUG_ON(ac->ac_status != AC_STATUS_FOUND);
	BUG_ON(!S_ISREG(ac->ac_inode->i_mode));
	BUG_ON(ac->ac_pa == शून्य);

	pa = ac->ac_pa;

	/* pपुनः_स्मृतिation can change ac_b_ex, thus we store actually
	 * allocated blocks क्रम history */
	ac->ac_f_ex = ac->ac_b_ex;

	pa->pa_pstart = ext4_grp_offs_to_block(sb, &ac->ac_b_ex);
	pa->pa_lstart = pa->pa_pstart;
	pa->pa_len = ac->ac_b_ex.fe_len;
	pa->pa_मुक्त = pa->pa_len;
	spin_lock_init(&pa->pa_lock);
	INIT_LIST_HEAD(&pa->pa_inode_list);
	INIT_LIST_HEAD(&pa->pa_group_list);
	pa->pa_deleted = 0;
	pa->pa_type = MB_GROUP_PA;

	mb_debug(sb, "new group pa %p: %llu/%d for %u\n", pa, pa->pa_pstart,
		 pa->pa_len, pa->pa_lstart);
	trace_ext4_mb_new_group_pa(ac, pa);

	ext4_mb_use_group_pa(ac, pa);
	atomic_add(pa->pa_मुक्त, &EXT4_SB(sb)->s_mb_pपुनः_स्मृतिated);

	grp = ext4_get_group_info(sb, ac->ac_b_ex.fe_group);
	lg = ac->ac_lg;
	BUG_ON(lg == शून्य);

	pa->pa_obj_lock = &lg->lg_pपुनः_स्मृति_lock;
	pa->pa_inode = शून्य;

	list_add(&pa->pa_group_list, &grp->bb_pपुनः_स्मृति_list);

	/*
	 * We will later add the new pa to the right bucket
	 * after updating the pa_मुक्त in ext4_mb_release_context
	 */
पूर्ण

अटल व्योम ext4_mb_new_pपुनः_स्मृतिation(काष्ठा ext4_allocation_context *ac)
अणु
	अगर (ac->ac_flags & EXT4_MB_HINT_GROUP_ALLOC)
		ext4_mb_new_group_pa(ac);
	अन्यथा
		ext4_mb_new_inode_pa(ac);
पूर्ण

/*
 * finds all unused blocks in on-disk biपंचांगap, मुक्तs them in
 * in-core biपंचांगap and buddy.
 * @pa must be unlinked from inode and group lists, so that
 * nobody अन्यथा can find/use it.
 * the caller MUST hold group/inode locks.
 * TODO: optimize the हाल when there are no in-core काष्ठाures yet
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक
ext4_mb_release_inode_pa(काष्ठा ext4_buddy *e4b, काष्ठा buffer_head *biपंचांगap_bh,
			काष्ठा ext4_pपुनः_स्मृति_space *pa)
अणु
	काष्ठा super_block *sb = e4b->bd_sb;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	अचिन्हित पूर्णांक end;
	अचिन्हित पूर्णांक next;
	ext4_group_t group;
	ext4_grpblk_t bit;
	अचिन्हित दीर्घ दीर्घ grp_blk_start;
	पूर्णांक मुक्त = 0;

	BUG_ON(pa->pa_deleted == 0);
	ext4_get_group_no_and_offset(sb, pa->pa_pstart, &group, &bit);
	grp_blk_start = pa->pa_pstart - EXT4_C2B(sbi, bit);
	BUG_ON(group != e4b->bd_group && pa->pa_len != 0);
	end = bit + pa->pa_len;

	जबतक (bit < end) अणु
		bit = mb_find_next_zero_bit(biपंचांगap_bh->b_data, end, bit);
		अगर (bit >= end)
			अवरोध;
		next = mb_find_next_bit(biपंचांगap_bh->b_data, end, bit);
		mb_debug(sb, "free preallocated %u/%u in group %u\n",
			 (अचिन्हित) ext4_group_first_block_no(sb, group) + bit,
			 (अचिन्हित) next - bit, (अचिन्हित) group);
		मुक्त += next - bit;

		trace_ext4_mballoc_discard(sb, शून्य, group, bit, next - bit);
		trace_ext4_mb_release_inode_pa(pa, (grp_blk_start +
						    EXT4_C2B(sbi, bit)),
					       next - bit);
		mb_मुक्त_blocks(pa->pa_inode, e4b, bit, next - bit);
		bit = next + 1;
	पूर्ण
	अगर (मुक्त != pa->pa_मुक्त) अणु
		ext4_msg(e4b->bd_sb, KERN_CRIT,
			 "pa %p: logic %lu, phys. %lu, len %d",
			 pa, (अचिन्हित दीर्घ) pa->pa_lstart,
			 (अचिन्हित दीर्घ) pa->pa_pstart,
			 pa->pa_len);
		ext4_grp_locked_error(sb, group, 0, 0, "free %u, pa_free %u",
					मुक्त, pa->pa_मुक्त);
		/*
		 * pa is alपढ़ोy deleted so we use the value obtained
		 * from the biपंचांगap and जारी.
		 */
	पूर्ण
	atomic_add(मुक्त, &sbi->s_mb_discarded);

	वापस 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ext4_mb_release_group_pa(काष्ठा ext4_buddy *e4b,
				काष्ठा ext4_pपुनः_स्मृति_space *pa)
अणु
	काष्ठा super_block *sb = e4b->bd_sb;
	ext4_group_t group;
	ext4_grpblk_t bit;

	trace_ext4_mb_release_group_pa(sb, pa);
	BUG_ON(pa->pa_deleted == 0);
	ext4_get_group_no_and_offset(sb, pa->pa_pstart, &group, &bit);
	BUG_ON(group != e4b->bd_group && pa->pa_len != 0);
	mb_मुक्त_blocks(pa->pa_inode, e4b, bit, pa->pa_len);
	atomic_add(pa->pa_len, &EXT4_SB(sb)->s_mb_discarded);
	trace_ext4_mballoc_discard(sb, शून्य, group, bit, pa->pa_len);

	वापस 0;
पूर्ण

/*
 * releases all pपुनः_स्मृतिations in given group
 *
 * first, we need to decide discard policy:
 * - when करो we discard
 *   1) ENOSPC
 * - how many करो we discard
 *   1) how many requested
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक
ext4_mb_discard_group_pपुनः_स्मृतिations(काष्ठा super_block *sb,
					ext4_group_t group, पूर्णांक needed)
अणु
	काष्ठा ext4_group_info *grp = ext4_get_group_info(sb, group);
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा ext4_pपुनः_स्मृति_space *pa, *पंचांगp;
	काष्ठा list_head list;
	काष्ठा ext4_buddy e4b;
	पूर्णांक err;
	पूर्णांक busy = 0;
	पूर्णांक मुक्त, मुक्त_total = 0;

	mb_debug(sb, "discard preallocation for group %u\n", group);
	अगर (list_empty(&grp->bb_pपुनः_स्मृति_list))
		जाओ out_dbg;

	biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, group);
	अगर (IS_ERR(biपंचांगap_bh)) अणु
		err = PTR_ERR(biपंचांगap_bh);
		ext4_error_err(sb, -err,
			       "Error %d reading block bitmap for %u",
			       err, group);
		जाओ out_dbg;
	पूर्ण

	err = ext4_mb_load_buddy(sb, group, &e4b);
	अगर (err) अणु
		ext4_warning(sb, "Error %d loading buddy information for %u",
			     err, group);
		put_bh(biपंचांगap_bh);
		जाओ out_dbg;
	पूर्ण

	अगर (needed == 0)
		needed = EXT4_CLUSTERS_PER_GROUP(sb) + 1;

	INIT_LIST_HEAD(&list);
repeat:
	मुक्त = 0;
	ext4_lock_group(sb, group);
	list_क्रम_each_entry_safe(pa, पंचांगp,
				&grp->bb_pपुनः_स्मृति_list, pa_group_list) अणु
		spin_lock(&pa->pa_lock);
		अगर (atomic_पढ़ो(&pa->pa_count)) अणु
			spin_unlock(&pa->pa_lock);
			busy = 1;
			जारी;
		पूर्ण
		अगर (pa->pa_deleted) अणु
			spin_unlock(&pa->pa_lock);
			जारी;
		पूर्ण

		/* seems this one can be मुक्तd ... */
		ext4_mb_mark_pa_deleted(sb, pa);

		अगर (!मुक्त)
			this_cpu_inc(discard_pa_seq);

		/* we can trust pa_मुक्त ... */
		मुक्त += pa->pa_मुक्त;

		spin_unlock(&pa->pa_lock);

		list_del(&pa->pa_group_list);
		list_add(&pa->u.pa_पंचांगp_list, &list);
	पूर्ण

	/* now मुक्त all selected PAs */
	list_क्रम_each_entry_safe(pa, पंचांगp, &list, u.pa_पंचांगp_list) अणु

		/* हटाओ from object (inode or locality group) */
		spin_lock(pa->pa_obj_lock);
		list_del_rcu(&pa->pa_inode_list);
		spin_unlock(pa->pa_obj_lock);

		अगर (pa->pa_type == MB_GROUP_PA)
			ext4_mb_release_group_pa(&e4b, pa);
		अन्यथा
			ext4_mb_release_inode_pa(&e4b, biपंचांगap_bh, pa);

		list_del(&pa->u.pa_पंचांगp_list);
		call_rcu(&(pa)->u.pa_rcu, ext4_mb_pa_callback);
	पूर्ण

	मुक्त_total += मुक्त;

	/* अगर we still need more blocks and some PAs were used, try again */
	अगर (मुक्त_total < needed && busy) अणु
		ext4_unlock_group(sb, group);
		cond_resched();
		busy = 0;
		जाओ repeat;
	पूर्ण
	ext4_unlock_group(sb, group);
	ext4_mb_unload_buddy(&e4b);
	put_bh(biपंचांगap_bh);
out_dbg:
	mb_debug(sb, "discarded (%d) blocks preallocated for group %u bb_free (%d)\n",
		 मुक्त_total, group, grp->bb_मुक्त);
	वापस मुक्त_total;
पूर्ण

/*
 * releases all non-used pपुनः_स्मृतिated blocks क्रम given inode
 *
 * It's important to discard pपुनः_स्मृतिations under i_data_sem
 * We करोn't want another block to be served from the pपुनः_स्मृति
 * space when we are discarding the inode pपुनः_स्मृति space.
 *
 * FIXME!! Make sure it is valid at all the call sites
 */
व्योम ext4_discard_pपुनः_स्मृतिations(काष्ठा inode *inode, अचिन्हित पूर्णांक needed)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा ext4_pपुनः_स्मृति_space *pa, *पंचांगp;
	ext4_group_t group = 0;
	काष्ठा list_head list;
	काष्ठा ext4_buddy e4b;
	पूर्णांक err;

	अगर (!S_ISREG(inode->i_mode)) अणु
		/*BUG_ON(!list_empty(&ei->i_pपुनः_स्मृति_list));*/
		वापस;
	पूर्ण

	अगर (EXT4_SB(sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस;

	mb_debug(sb, "discard preallocation for inode %lu\n",
		 inode->i_ino);
	trace_ext4_discard_pपुनः_स्मृतिations(inode,
			atomic_पढ़ो(&ei->i_pपुनः_स्मृति_active), needed);

	INIT_LIST_HEAD(&list);

	अगर (needed == 0)
		needed = अच_पूर्णांक_उच्च;

repeat:
	/* first, collect all pa's in the inode */
	spin_lock(&ei->i_pपुनः_स्मृति_lock);
	जबतक (!list_empty(&ei->i_pपुनः_स्मृति_list) && needed) अणु
		pa = list_entry(ei->i_pपुनः_स्मृति_list.prev,
				काष्ठा ext4_pपुनः_स्मृति_space, pa_inode_list);
		BUG_ON(pa->pa_obj_lock != &ei->i_pपुनः_स्मृति_lock);
		spin_lock(&pa->pa_lock);
		अगर (atomic_पढ़ो(&pa->pa_count)) अणु
			/* this shouldn't happen often - nobody should
			 * use pपुनः_स्मृतिation जबतक we're discarding it */
			spin_unlock(&pa->pa_lock);
			spin_unlock(&ei->i_pपुनः_स्मृति_lock);
			ext4_msg(sb, KERN_ERR,
				 "uh-oh! used pa while discarding");
			WARN_ON(1);
			schedule_समयout_unपूर्णांकerruptible(HZ);
			जाओ repeat;

		पूर्ण
		अगर (pa->pa_deleted == 0) अणु
			ext4_mb_mark_pa_deleted(sb, pa);
			spin_unlock(&pa->pa_lock);
			list_del_rcu(&pa->pa_inode_list);
			list_add(&pa->u.pa_पंचांगp_list, &list);
			needed--;
			जारी;
		पूर्ण

		/* someone is deleting pa right now */
		spin_unlock(&pa->pa_lock);
		spin_unlock(&ei->i_pपुनः_स्मृति_lock);

		/* we have to रुको here because pa_deleted
		 * करोesn't mean pa is alपढ़ोy unlinked from
		 * the list. as we might be called from
		 * ->clear_inode() the inode will get मुक्तd
		 * and concurrent thपढ़ो which is unlinking
		 * pa from inode's list may access alपढ़ोy
		 * मुक्तd memory, bad-bad-bad */

		/* XXX: अगर this happens too often, we can
		 * add a flag to क्रमce रुको only in हाल
		 * of ->clear_inode(), but not in हाल of
		 * regular truncate */
		schedule_समयout_unपूर्णांकerruptible(HZ);
		जाओ repeat;
	पूर्ण
	spin_unlock(&ei->i_pपुनः_स्मृति_lock);

	list_क्रम_each_entry_safe(pa, पंचांगp, &list, u.pa_पंचांगp_list) अणु
		BUG_ON(pa->pa_type != MB_INODE_PA);
		group = ext4_get_group_number(sb, pa->pa_pstart);

		err = ext4_mb_load_buddy_gfp(sb, group, &e4b,
					     GFP_NOFS|__GFP_NOFAIL);
		अगर (err) अणु
			ext4_error_err(sb, -err, "Error %d loading buddy information for %u",
				       err, group);
			जारी;
		पूर्ण

		biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, group);
		अगर (IS_ERR(biपंचांगap_bh)) अणु
			err = PTR_ERR(biपंचांगap_bh);
			ext4_error_err(sb, -err, "Error %d reading block bitmap for %u",
				       err, group);
			ext4_mb_unload_buddy(&e4b);
			जारी;
		पूर्ण

		ext4_lock_group(sb, group);
		list_del(&pa->pa_group_list);
		ext4_mb_release_inode_pa(&e4b, biपंचांगap_bh, pa);
		ext4_unlock_group(sb, group);

		ext4_mb_unload_buddy(&e4b);
		put_bh(biपंचांगap_bh);

		list_del(&pa->u.pa_पंचांगp_list);
		call_rcu(&(pa)->u.pa_rcu, ext4_mb_pa_callback);
	पूर्ण
पूर्ण

अटल पूर्णांक ext4_mb_pa_alloc(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा ext4_pपुनः_स्मृति_space *pa;

	BUG_ON(ext4_pspace_cachep == शून्य);
	pa = kmem_cache_zalloc(ext4_pspace_cachep, GFP_NOFS);
	अगर (!pa)
		वापस -ENOMEM;
	atomic_set(&pa->pa_count, 1);
	ac->ac_pa = pa;
	वापस 0;
पूर्ण

अटल व्योम ext4_mb_pa_मुक्त(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा ext4_pपुनः_स्मृति_space *pa = ac->ac_pa;

	BUG_ON(!pa);
	ac->ac_pa = शून्य;
	WARN_ON(!atomic_dec_and_test(&pa->pa_count));
	kmem_cache_मुक्त(ext4_pspace_cachep, pa);
पूर्ण

#अगर_घोषित CONFIG_EXT4_DEBUG
अटल अंतरभूत व्योम ext4_mb_show_pa(काष्ठा super_block *sb)
अणु
	ext4_group_t i, ngroups;

	अगर (ext4_test_mount_flag(sb, EXT4_MF_FS_ABORTED))
		वापस;

	ngroups = ext4_get_groups_count(sb);
	mb_debug(sb, "groups: ");
	क्रम (i = 0; i < ngroups; i++) अणु
		काष्ठा ext4_group_info *grp = ext4_get_group_info(sb, i);
		काष्ठा ext4_pपुनः_स्मृति_space *pa;
		ext4_grpblk_t start;
		काष्ठा list_head *cur;
		ext4_lock_group(sb, i);
		list_क्रम_each(cur, &grp->bb_pपुनः_स्मृति_list) अणु
			pa = list_entry(cur, काष्ठा ext4_pपुनः_स्मृति_space,
					pa_group_list);
			spin_lock(&pa->pa_lock);
			ext4_get_group_no_and_offset(sb, pa->pa_pstart,
						     शून्य, &start);
			spin_unlock(&pa->pa_lock);
			mb_debug(sb, "PA:%u:%d:%d\n", i, start,
				 pa->pa_len);
		पूर्ण
		ext4_unlock_group(sb, i);
		mb_debug(sb, "%u: %d/%d\n", i, grp->bb_मुक्त,
			 grp->bb_fragments);
	पूर्ण
पूर्ण

अटल व्योम ext4_mb_show_ac(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा super_block *sb = ac->ac_sb;

	अगर (ext4_test_mount_flag(sb, EXT4_MF_FS_ABORTED))
		वापस;

	mb_debug(sb, "Can't allocate:"
			" Allocation context details:");
	mb_debug(sb, "status %u flags 0x%x",
			ac->ac_status, ac->ac_flags);
	mb_debug(sb, "orig %lu/%lu/%lu@%lu, "
			"goal %lu/%lu/%lu@%lu, "
			"best %lu/%lu/%lu@%lu cr %d",
			(अचिन्हित दीर्घ)ac->ac_o_ex.fe_group,
			(अचिन्हित दीर्घ)ac->ac_o_ex.fe_start,
			(अचिन्हित दीर्घ)ac->ac_o_ex.fe_len,
			(अचिन्हित दीर्घ)ac->ac_o_ex.fe_logical,
			(अचिन्हित दीर्घ)ac->ac_g_ex.fe_group,
			(अचिन्हित दीर्घ)ac->ac_g_ex.fe_start,
			(अचिन्हित दीर्घ)ac->ac_g_ex.fe_len,
			(अचिन्हित दीर्घ)ac->ac_g_ex.fe_logical,
			(अचिन्हित दीर्घ)ac->ac_b_ex.fe_group,
			(अचिन्हित दीर्घ)ac->ac_b_ex.fe_start,
			(अचिन्हित दीर्घ)ac->ac_b_ex.fe_len,
			(अचिन्हित दीर्घ)ac->ac_b_ex.fe_logical,
			(पूर्णांक)ac->ac_criteria);
	mb_debug(sb, "%u found", ac->ac_found);
	ext4_mb_show_pa(sb);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ext4_mb_show_pa(काष्ठा super_block *sb)
अणु
	वापस;
पूर्ण
अटल अंतरभूत व्योम ext4_mb_show_ac(काष्ठा ext4_allocation_context *ac)
अणु
	ext4_mb_show_pa(ac->ac_sb);
	वापस;
पूर्ण
#पूर्ण_अगर

/*
 * We use locality group pपुनः_स्मृतिation क्रम small size file. The size of the
 * file is determined by the current size or the resulting size after
 * allocation which ever is larger
 *
 * One can tune this size via /sys/fs/ext4/<partition>/mb_stream_req
 */
अटल व्योम ext4_mb_group_or_file(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);
	पूर्णांक bsbits = ac->ac_sb->s_blocksize_bits;
	loff_t size, isize;

	अगर (!(ac->ac_flags & EXT4_MB_HINT_DATA))
		वापस;

	अगर (unlikely(ac->ac_flags & EXT4_MB_HINT_GOAL_ONLY))
		वापस;

	size = ac->ac_o_ex.fe_logical + EXT4_C2B(sbi, ac->ac_o_ex.fe_len);
	isize = (i_size_पढ़ो(ac->ac_inode) + ac->ac_sb->s_blocksize - 1)
		>> bsbits;

	अगर ((size == isize) && !ext4_fs_is_busy(sbi) &&
	    !inode_is_खोलो_क्रम_ग_लिखो(ac->ac_inode)) अणु
		ac->ac_flags |= EXT4_MB_HINT_NOPREALLOC;
		वापस;
	पूर्ण

	अगर (sbi->s_mb_group_pपुनः_स्मृति <= 0) अणु
		ac->ac_flags |= EXT4_MB_STREAM_ALLOC;
		वापस;
	पूर्ण

	/* करोn't use group allocation क्रम large files */
	size = max(size, isize);
	अगर (size > sbi->s_mb_stream_request) अणु
		ac->ac_flags |= EXT4_MB_STREAM_ALLOC;
		वापस;
	पूर्ण

	BUG_ON(ac->ac_lg != शून्य);
	/*
	 * locality group pपुनः_स्मृति space are per cpu. The reason क्रम having
	 * per cpu locality group is to reduce the contention between block
	 * request from multiple CPUs.
	 */
	ac->ac_lg = raw_cpu_ptr(sbi->s_locality_groups);

	/* we're going to use group allocation */
	ac->ac_flags |= EXT4_MB_HINT_GROUP_ALLOC;

	/* serialize all allocations in the group */
	mutex_lock(&ac->ac_lg->lg_mutex);
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ext4_mb_initialize_context(काष्ठा ext4_allocation_context *ac,
				काष्ठा ext4_allocation_request *ar)
अणु
	काष्ठा super_block *sb = ar->inode->i_sb;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_super_block *es = sbi->s_es;
	ext4_group_t group;
	अचिन्हित पूर्णांक len;
	ext4_fsblk_t goal;
	ext4_grpblk_t block;

	/* we can't allocate > group size */
	len = ar->len;

	/* just a dirty hack to filter too big requests  */
	अगर (len >= EXT4_CLUSTERS_PER_GROUP(sb))
		len = EXT4_CLUSTERS_PER_GROUP(sb);

	/* start searching from the goal */
	goal = ar->goal;
	अगर (goal < le32_to_cpu(es->s_first_data_block) ||
			goal >= ext4_blocks_count(es))
		goal = le32_to_cpu(es->s_first_data_block);
	ext4_get_group_no_and_offset(sb, goal, &group, &block);

	/* set up allocation goals */
	ac->ac_b_ex.fe_logical = EXT4_LBLK_CMASK(sbi, ar->logical);
	ac->ac_status = AC_STATUS_CONTINUE;
	ac->ac_sb = sb;
	ac->ac_inode = ar->inode;
	ac->ac_o_ex.fe_logical = ac->ac_b_ex.fe_logical;
	ac->ac_o_ex.fe_group = group;
	ac->ac_o_ex.fe_start = block;
	ac->ac_o_ex.fe_len = len;
	ac->ac_g_ex = ac->ac_o_ex;
	ac->ac_flags = ar->flags;

	/* we have to define context: we'll work with a file or
	 * locality group. this is a policy, actually */
	ext4_mb_group_or_file(ac);

	mb_debug(sb, "init ac: %u blocks @ %u, goal %u, flags 0x%x, 2^%d, "
			"left: %u/%u, right %u/%u to %swritable\n",
			(अचिन्हित) ar->len, (अचिन्हित) ar->logical,
			(अचिन्हित) ar->goal, ac->ac_flags, ac->ac_2order,
			(अचिन्हित) ar->lleft, (अचिन्हित) ar->pleft,
			(अचिन्हित) ar->lright, (अचिन्हित) ar->pright,
			inode_is_खोलो_क्रम_ग_लिखो(ar->inode) ? "" : "non-");
	वापस 0;

पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम
ext4_mb_discard_lg_pपुनः_स्मृतिations(काष्ठा super_block *sb,
					काष्ठा ext4_locality_group *lg,
					पूर्णांक order, पूर्णांक total_entries)
अणु
	ext4_group_t group = 0;
	काष्ठा ext4_buddy e4b;
	काष्ठा list_head discard_list;
	काष्ठा ext4_pपुनः_स्मृति_space *pa, *पंचांगp;

	mb_debug(sb, "discard locality group preallocation\n");

	INIT_LIST_HEAD(&discard_list);

	spin_lock(&lg->lg_pपुनः_स्मृति_lock);
	list_क्रम_each_entry_rcu(pa, &lg->lg_pपुनः_स्मृति_list[order],
				pa_inode_list,
				lockdep_is_held(&lg->lg_pपुनः_स्मृति_lock)) अणु
		spin_lock(&pa->pa_lock);
		अगर (atomic_पढ़ो(&pa->pa_count)) अणु
			/*
			 * This is the pa that we just used
			 * क्रम block allocation. So करोn't
			 * मुक्त that
			 */
			spin_unlock(&pa->pa_lock);
			जारी;
		पूर्ण
		अगर (pa->pa_deleted) अणु
			spin_unlock(&pa->pa_lock);
			जारी;
		पूर्ण
		/* only lg pपुनः_स्मृति space */
		BUG_ON(pa->pa_type != MB_GROUP_PA);

		/* seems this one can be मुक्तd ... */
		ext4_mb_mark_pa_deleted(sb, pa);
		spin_unlock(&pa->pa_lock);

		list_del_rcu(&pa->pa_inode_list);
		list_add(&pa->u.pa_पंचांगp_list, &discard_list);

		total_entries--;
		अगर (total_entries <= 5) अणु
			/*
			 * we want to keep only 5 entries
			 * allowing it to grow to 8. This
			 * mak sure we करोn't call discard
			 * soon क्रम this list.
			 */
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&lg->lg_pपुनः_स्मृति_lock);

	list_क्रम_each_entry_safe(pa, पंचांगp, &discard_list, u.pa_पंचांगp_list) अणु
		पूर्णांक err;

		group = ext4_get_group_number(sb, pa->pa_pstart);
		err = ext4_mb_load_buddy_gfp(sb, group, &e4b,
					     GFP_NOFS|__GFP_NOFAIL);
		अगर (err) अणु
			ext4_error_err(sb, -err, "Error %d loading buddy information for %u",
				       err, group);
			जारी;
		पूर्ण
		ext4_lock_group(sb, group);
		list_del(&pa->pa_group_list);
		ext4_mb_release_group_pa(&e4b, pa);
		ext4_unlock_group(sb, group);

		ext4_mb_unload_buddy(&e4b);
		list_del(&pa->u.pa_पंचांगp_list);
		call_rcu(&(pa)->u.pa_rcu, ext4_mb_pa_callback);
	पूर्ण
पूर्ण

/*
 * We have incremented pa_count. So it cannot be मुक्तd at this
 * poपूर्णांक. Also we hold lg_mutex. So no parallel allocation is
 * possible from this lg. That means pa_मुक्त cannot be updated.
 *
 * A parallel ext4_mb_discard_group_pपुनः_स्मृतिations is possible.
 * which can cause the lg_pपुनः_स्मृति_list to be updated.
 */

अटल व्योम ext4_mb_add_n_trim(काष्ठा ext4_allocation_context *ac)
अणु
	पूर्णांक order, added = 0, lg_pपुनः_स्मृति_count = 1;
	काष्ठा super_block *sb = ac->ac_sb;
	काष्ठा ext4_locality_group *lg = ac->ac_lg;
	काष्ठा ext4_pपुनः_स्मृति_space *पंचांगp_pa, *pa = ac->ac_pa;

	order = fls(pa->pa_मुक्त) - 1;
	अगर (order > PREALLOC_TB_SIZE - 1)
		/* The max size of hash table is PREALLOC_TB_SIZE */
		order = PREALLOC_TB_SIZE - 1;
	/* Add the pपुनः_स्मृति space to lg */
	spin_lock(&lg->lg_pपुनः_स्मृति_lock);
	list_क्रम_each_entry_rcu(पंचांगp_pa, &lg->lg_pपुनः_स्मृति_list[order],
				pa_inode_list,
				lockdep_is_held(&lg->lg_pपुनः_स्मृति_lock)) अणु
		spin_lock(&पंचांगp_pa->pa_lock);
		अगर (पंचांगp_pa->pa_deleted) अणु
			spin_unlock(&पंचांगp_pa->pa_lock);
			जारी;
		पूर्ण
		अगर (!added && pa->pa_मुक्त < पंचांगp_pa->pa_मुक्त) अणु
			/* Add to the tail of the previous entry */
			list_add_tail_rcu(&pa->pa_inode_list,
						&पंचांगp_pa->pa_inode_list);
			added = 1;
			/*
			 * we want to count the total
			 * number of entries in the list
			 */
		पूर्ण
		spin_unlock(&पंचांगp_pa->pa_lock);
		lg_pपुनः_स्मृति_count++;
	पूर्ण
	अगर (!added)
		list_add_tail_rcu(&pa->pa_inode_list,
					&lg->lg_pपुनः_स्मृति_list[order]);
	spin_unlock(&lg->lg_pपुनः_स्मृति_lock);

	/* Now trim the list to be not more than 8 elements */
	अगर (lg_pपुनः_स्मृति_count > 8) अणु
		ext4_mb_discard_lg_pपुनः_स्मृतिations(sb, lg,
						  order, lg_pपुनः_स्मृति_count);
		वापस;
	पूर्ण
	वापस ;
पूर्ण

/*
 * अगर per-inode pपुनः_स्मृति list is too दीर्घ, trim some PA
 */
अटल व्योम ext4_mb_trim_inode_pa(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	पूर्णांक count, delta;

	count = atomic_पढ़ो(&ei->i_pपुनः_स्मृति_active);
	delta = (sbi->s_mb_max_inode_pपुनः_स्मृति >> 2) + 1;
	अगर (count > sbi->s_mb_max_inode_pपुनः_स्मृति + delta) अणु
		count -= sbi->s_mb_max_inode_pपुनः_स्मृति;
		ext4_discard_pपुनः_स्मृतिations(inode, count);
	पूर्ण
पूर्ण

/*
 * release all resource we used in allocation
 */
अटल पूर्णांक ext4_mb_release_context(काष्ठा ext4_allocation_context *ac)
अणु
	काष्ठा inode *inode = ac->ac_inode;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(ac->ac_sb);
	काष्ठा ext4_pपुनः_स्मृति_space *pa = ac->ac_pa;
	अगर (pa) अणु
		अगर (pa->pa_type == MB_GROUP_PA) अणु
			/* see comment in ext4_mb_use_group_pa() */
			spin_lock(&pa->pa_lock);
			pa->pa_pstart += EXT4_C2B(sbi, ac->ac_b_ex.fe_len);
			pa->pa_lstart += EXT4_C2B(sbi, ac->ac_b_ex.fe_len);
			pa->pa_मुक्त -= ac->ac_b_ex.fe_len;
			pa->pa_len -= ac->ac_b_ex.fe_len;
			spin_unlock(&pa->pa_lock);

			/*
			 * We want to add the pa to the right bucket.
			 * Remove it from the list and जबतक adding
			 * make sure the list to which we are adding
			 * करोesn't grow big.
			 */
			अगर (likely(pa->pa_मुक्त)) अणु
				spin_lock(pa->pa_obj_lock);
				list_del_rcu(&pa->pa_inode_list);
				spin_unlock(pa->pa_obj_lock);
				ext4_mb_add_n_trim(ac);
			पूर्ण
		पूर्ण

		अगर (pa->pa_type == MB_INODE_PA) अणु
			/*
			 * treat per-inode pपुनः_स्मृति list as a lru list, then try
			 * to trim the least recently used PA.
			 */
			spin_lock(pa->pa_obj_lock);
			list_move(&pa->pa_inode_list, &ei->i_pपुनः_स्मृति_list);
			spin_unlock(pa->pa_obj_lock);
		पूर्ण

		ext4_mb_put_pa(ac, ac->ac_sb, pa);
	पूर्ण
	अगर (ac->ac_biपंचांगap_page)
		put_page(ac->ac_biपंचांगap_page);
	अगर (ac->ac_buddy_page)
		put_page(ac->ac_buddy_page);
	अगर (ac->ac_flags & EXT4_MB_HINT_GROUP_ALLOC)
		mutex_unlock(&ac->ac_lg->lg_mutex);
	ext4_mb_collect_stats(ac);
	ext4_mb_trim_inode_pa(inode);
	वापस 0;
पूर्ण

अटल पूर्णांक ext4_mb_discard_pपुनः_स्मृतिations(काष्ठा super_block *sb, पूर्णांक needed)
अणु
	ext4_group_t i, ngroups = ext4_get_groups_count(sb);
	पूर्णांक ret;
	पूर्णांक मुक्तd = 0;

	trace_ext4_mb_discard_pपुनः_स्मृतिations(sb, needed);
	क्रम (i = 0; i < ngroups && needed > 0; i++) अणु
		ret = ext4_mb_discard_group_pपुनः_स्मृतिations(sb, i, needed);
		मुक्तd += ret;
		needed -= ret;
	पूर्ण

	वापस मुक्तd;
पूर्ण

अटल bool ext4_mb_discard_pपुनः_स्मृतिations_should_retry(काष्ठा super_block *sb,
			काष्ठा ext4_allocation_context *ac, u64 *seq)
अणु
	पूर्णांक मुक्तd;
	u64 seq_retry = 0;
	bool ret = false;

	मुक्तd = ext4_mb_discard_pपुनः_स्मृतिations(sb, ac->ac_o_ex.fe_len);
	अगर (मुक्तd) अणु
		ret = true;
		जाओ out_dbg;
	पूर्ण
	seq_retry = ext4_get_discard_pa_seq_sum();
	अगर (!(ac->ac_flags & EXT4_MB_STRICT_CHECK) || seq_retry != *seq) अणु
		ac->ac_flags |= EXT4_MB_STRICT_CHECK;
		*seq = seq_retry;
		ret = true;
	पूर्ण

out_dbg:
	mb_debug(sb, "freed %d, retry ? %s\n", मुक्तd, ret ? "yes" : "no");
	वापस ret;
पूर्ण

अटल ext4_fsblk_t ext4_mb_new_blocks_simple(handle_t *handle,
				काष्ठा ext4_allocation_request *ar, पूर्णांक *errp);

/*
 * Main entry poपूर्णांक पूर्णांकo mballoc to allocate blocks
 * it tries to use pपुनः_स्मृतिation first, then falls back
 * to usual allocation
 */
ext4_fsblk_t ext4_mb_new_blocks(handle_t *handle,
				काष्ठा ext4_allocation_request *ar, पूर्णांक *errp)
अणु
	काष्ठा ext4_allocation_context *ac = शून्य;
	काष्ठा ext4_sb_info *sbi;
	काष्ठा super_block *sb;
	ext4_fsblk_t block = 0;
	अचिन्हित पूर्णांक inquota = 0;
	अचिन्हित पूर्णांक reserv_clstrs = 0;
	u64 seq;

	might_sleep();
	sb = ar->inode->i_sb;
	sbi = EXT4_SB(sb);

	trace_ext4_request_blocks(ar);
	अगर (sbi->s_mount_state & EXT4_FC_REPLAY)
		वापस ext4_mb_new_blocks_simple(handle, ar, errp);

	/* Allow to use superuser reservation क्रम quota file */
	अगर (ext4_is_quota_file(ar->inode))
		ar->flags |= EXT4_MB_USE_ROOT_BLOCKS;

	अगर ((ar->flags & EXT4_MB_DELALLOC_RESERVED) == 0) अणु
		/* Without delayed allocation we need to verअगरy
		 * there is enough मुक्त blocks to करो block allocation
		 * and verअगरy allocation करोesn't exceed the quota limits.
		 */
		जबतक (ar->len &&
			ext4_claim_मुक्त_clusters(sbi, ar->len, ar->flags)) अणु

			/* let others to मुक्त the space */
			cond_resched();
			ar->len = ar->len >> 1;
		पूर्ण
		अगर (!ar->len) अणु
			ext4_mb_show_pa(sb);
			*errp = -ENOSPC;
			वापस 0;
		पूर्ण
		reserv_clstrs = ar->len;
		अगर (ar->flags & EXT4_MB_USE_ROOT_BLOCKS) अणु
			dquot_alloc_block_nofail(ar->inode,
						 EXT4_C2B(sbi, ar->len));
		पूर्ण अन्यथा अणु
			जबतक (ar->len &&
				dquot_alloc_block(ar->inode,
						  EXT4_C2B(sbi, ar->len))) अणु

				ar->flags |= EXT4_MB_HINT_NOPREALLOC;
				ar->len--;
			पूर्ण
		पूर्ण
		inquota = ar->len;
		अगर (ar->len == 0) अणु
			*errp = -EDQUOT;
			जाओ out;
		पूर्ण
	पूर्ण

	ac = kmem_cache_zalloc(ext4_ac_cachep, GFP_NOFS);
	अगर (!ac) अणु
		ar->len = 0;
		*errp = -ENOMEM;
		जाओ out;
	पूर्ण

	*errp = ext4_mb_initialize_context(ac, ar);
	अगर (*errp) अणु
		ar->len = 0;
		जाओ out;
	पूर्ण

	ac->ac_op = EXT4_MB_HISTORY_PREALLOC;
	seq = this_cpu_पढ़ो(discard_pa_seq);
	अगर (!ext4_mb_use_pपुनः_स्मृतिated(ac)) अणु
		ac->ac_op = EXT4_MB_HISTORY_ALLOC;
		ext4_mb_normalize_request(ac, ar);

		*errp = ext4_mb_pa_alloc(ac);
		अगर (*errp)
			जाओ errout;
repeat:
		/* allocate space in core */
		*errp = ext4_mb_regular_allocator(ac);
		/*
		 * pa allocated above is added to grp->bb_pपुनः_स्मृति_list only
		 * when we were able to allocate some block i.e. when
		 * ac->ac_status == AC_STATUS_FOUND.
		 * And error from above mean ac->ac_status != AC_STATUS_FOUND
		 * So we have to मुक्त this pa here itself.
		 */
		अगर (*errp) अणु
			ext4_mb_pa_मुक्त(ac);
			ext4_discard_allocated_blocks(ac);
			जाओ errout;
		पूर्ण
		अगर (ac->ac_status == AC_STATUS_FOUND &&
			ac->ac_o_ex.fe_len >= ac->ac_f_ex.fe_len)
			ext4_mb_pa_मुक्त(ac);
	पूर्ण
	अगर (likely(ac->ac_status == AC_STATUS_FOUND)) अणु
		*errp = ext4_mb_mark_diskspace_used(ac, handle, reserv_clstrs);
		अगर (*errp) अणु
			ext4_discard_allocated_blocks(ac);
			जाओ errout;
		पूर्ण अन्यथा अणु
			block = ext4_grp_offs_to_block(sb, &ac->ac_b_ex);
			ar->len = ac->ac_b_ex.fe_len;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ext4_mb_discard_pपुनः_स्मृतिations_should_retry(sb, ac, &seq))
			जाओ repeat;
		/*
		 * If block allocation fails then the pa allocated above
		 * needs to be मुक्तd here itself.
		 */
		ext4_mb_pa_मुक्त(ac);
		*errp = -ENOSPC;
	पूर्ण

errout:
	अगर (*errp) अणु
		ac->ac_b_ex.fe_len = 0;
		ar->len = 0;
		ext4_mb_show_ac(ac);
	पूर्ण
	ext4_mb_release_context(ac);
out:
	अगर (ac)
		kmem_cache_मुक्त(ext4_ac_cachep, ac);
	अगर (inquota && ar->len < inquota)
		dquot_मुक्त_block(ar->inode, EXT4_C2B(sbi, inquota - ar->len));
	अगर (!ar->len) अणु
		अगर ((ar->flags & EXT4_MB_DELALLOC_RESERVED) == 0)
			/* release all the reserved blocks अगर non delalloc */
			percpu_counter_sub(&sbi->s_dirtyclusters_counter,
						reserv_clstrs);
	पूर्ण

	trace_ext4_allocate_blocks(ar, (अचिन्हित दीर्घ दीर्घ)block);

	वापस block;
पूर्ण

/*
 * We can merge two मुक्त data extents only अगर the physical blocks
 * are contiguous, AND the extents were मुक्तd by the same transaction,
 * AND the blocks are associated with the same group.
 */
अटल व्योम ext4_try_merge_मुक्तd_extent(काष्ठा ext4_sb_info *sbi,
					काष्ठा ext4_मुक्त_data *entry,
					काष्ठा ext4_मुक्त_data *new_entry,
					काष्ठा rb_root *entry_rb_root)
अणु
	अगर ((entry->efd_tid != new_entry->efd_tid) ||
	    (entry->efd_group != new_entry->efd_group))
		वापस;
	अगर (entry->efd_start_cluster + entry->efd_count ==
	    new_entry->efd_start_cluster) अणु
		new_entry->efd_start_cluster = entry->efd_start_cluster;
		new_entry->efd_count += entry->efd_count;
	पूर्ण अन्यथा अगर (new_entry->efd_start_cluster + new_entry->efd_count ==
		   entry->efd_start_cluster) अणु
		new_entry->efd_count += entry->efd_count;
	पूर्ण अन्यथा
		वापस;
	spin_lock(&sbi->s_md_lock);
	list_del(&entry->efd_list);
	spin_unlock(&sbi->s_md_lock);
	rb_erase(&entry->efd_node, entry_rb_root);
	kmem_cache_मुक्त(ext4_मुक्त_data_cachep, entry);
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक
ext4_mb_मुक्त_metadata(handle_t *handle, काष्ठा ext4_buddy *e4b,
		      काष्ठा ext4_मुक्त_data *new_entry)
अणु
	ext4_group_t group = e4b->bd_group;
	ext4_grpblk_t cluster;
	ext4_grpblk_t clusters = new_entry->efd_count;
	काष्ठा ext4_मुक्त_data *entry;
	काष्ठा ext4_group_info *db = e4b->bd_info;
	काष्ठा super_block *sb = e4b->bd_sb;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा rb_node **n = &db->bb_मुक्त_root.rb_node, *node;
	काष्ठा rb_node *parent = शून्य, *new_node;

	BUG_ON(!ext4_handle_valid(handle));
	BUG_ON(e4b->bd_biपंचांगap_page == शून्य);
	BUG_ON(e4b->bd_buddy_page == शून्य);

	new_node = &new_entry->efd_node;
	cluster = new_entry->efd_start_cluster;

	अगर (!*n) अणु
		/* first मुक्त block exent. We need to
		   protect buddy cache from being मुक्तd,
		 * otherwise we'll refresh it from
		 * on-disk biपंचांगap and lose not-yet-available
		 * blocks */
		get_page(e4b->bd_buddy_page);
		get_page(e4b->bd_biपंचांगap_page);
	पूर्ण
	जबतक (*n) अणु
		parent = *n;
		entry = rb_entry(parent, काष्ठा ext4_मुक्त_data, efd_node);
		अगर (cluster < entry->efd_start_cluster)
			n = &(*n)->rb_left;
		अन्यथा अगर (cluster >= (entry->efd_start_cluster + entry->efd_count))
			n = &(*n)->rb_right;
		अन्यथा अणु
			ext4_grp_locked_error(sb, group, 0,
				ext4_group_first_block_no(sb, group) +
				EXT4_C2B(sbi, cluster),
				"Block already on to-be-freed list");
			kmem_cache_मुक्त(ext4_मुक्त_data_cachep, new_entry);
			वापस 0;
		पूर्ण
	पूर्ण

	rb_link_node(new_node, parent, n);
	rb_insert_color(new_node, &db->bb_मुक्त_root);

	/* Now try to see the extent can be merged to left and right */
	node = rb_prev(new_node);
	अगर (node) अणु
		entry = rb_entry(node, काष्ठा ext4_मुक्त_data, efd_node);
		ext4_try_merge_मुक्तd_extent(sbi, entry, new_entry,
					    &(db->bb_मुक्त_root));
	पूर्ण

	node = rb_next(new_node);
	अगर (node) अणु
		entry = rb_entry(node, काष्ठा ext4_मुक्त_data, efd_node);
		ext4_try_merge_मुक्तd_extent(sbi, entry, new_entry,
					    &(db->bb_मुक्त_root));
	पूर्ण

	spin_lock(&sbi->s_md_lock);
	list_add_tail(&new_entry->efd_list, &sbi->s_मुक्तd_data_list);
	sbi->s_mb_मुक्त_pending += clusters;
	spin_unlock(&sbi->s_md_lock);
	वापस 0;
पूर्ण

/*
 * Simple allocator क्रम Ext4 fast commit replay path. It searches क्रम blocks
 * linearly starting at the goal block and also excludes the blocks which
 * are going to be in use after fast commit replay.
 */
अटल ext4_fsblk_t ext4_mb_new_blocks_simple(handle_t *handle,
				काष्ठा ext4_allocation_request *ar, पूर्णांक *errp)
अणु
	काष्ठा buffer_head *biपंचांगap_bh;
	काष्ठा super_block *sb = ar->inode->i_sb;
	ext4_group_t group;
	ext4_grpblk_t blkoff;
	पूर्णांक i = sb->s_blocksize;
	ext4_fsblk_t goal, block;
	काष्ठा ext4_super_block *es = EXT4_SB(sb)->s_es;

	goal = ar->goal;
	अगर (goal < le32_to_cpu(es->s_first_data_block) ||
			goal >= ext4_blocks_count(es))
		goal = le32_to_cpu(es->s_first_data_block);

	ar->len = 0;
	ext4_get_group_no_and_offset(sb, goal, &group, &blkoff);
	क्रम (; group < ext4_get_groups_count(sb); group++) अणु
		biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, group);
		अगर (IS_ERR(biपंचांगap_bh)) अणु
			*errp = PTR_ERR(biपंचांगap_bh);
			pr_warn("Failed to read block bitmap\n");
			वापस 0;
		पूर्ण

		ext4_get_group_no_and_offset(sb,
			max(ext4_group_first_block_no(sb, group), goal),
			शून्य, &blkoff);
		i = mb_find_next_zero_bit(biपंचांगap_bh->b_data, sb->s_blocksize,
						blkoff);
		brअन्यथा(biपंचांगap_bh);
		अगर (i >= sb->s_blocksize)
			जारी;
		अगर (ext4_fc_replay_check_excluded(sb,
			ext4_group_first_block_no(sb, group) + i))
			जारी;
		अवरोध;
	पूर्ण

	अगर (group >= ext4_get_groups_count(sb) && i >= sb->s_blocksize)
		वापस 0;

	block = ext4_group_first_block_no(sb, group) + i;
	ext4_mb_mark_bb(sb, block, 1, 1);
	ar->len = 1;

	वापस block;
पूर्ण

अटल व्योम ext4_मुक्त_blocks_simple(काष्ठा inode *inode, ext4_fsblk_t block,
					अचिन्हित दीर्घ count)
अणु
	काष्ठा buffer_head *biपंचांगap_bh;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ext4_group_desc *gdp;
	काष्ठा buffer_head *gdp_bh;
	ext4_group_t group;
	ext4_grpblk_t blkoff;
	पूर्णांक alपढ़ोy_मुक्तd = 0, err, i;

	ext4_get_group_no_and_offset(sb, block, &group, &blkoff);
	biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, group);
	अगर (IS_ERR(biपंचांगap_bh)) अणु
		err = PTR_ERR(biपंचांगap_bh);
		pr_warn("Failed to read block bitmap\n");
		वापस;
	पूर्ण
	gdp = ext4_get_group_desc(sb, group, &gdp_bh);
	अगर (!gdp)
		वापस;

	क्रम (i = 0; i < count; i++) अणु
		अगर (!mb_test_bit(blkoff + i, biपंचांगap_bh->b_data))
			alपढ़ोy_मुक्तd++;
	पूर्ण
	mb_clear_bits(biपंचांगap_bh->b_data, blkoff, count);
	err = ext4_handle_dirty_metadata(शून्य, शून्य, biपंचांगap_bh);
	अगर (err)
		वापस;
	ext4_मुक्त_group_clusters_set(
		sb, gdp, ext4_मुक्त_group_clusters(sb, gdp) +
		count - alपढ़ोy_मुक्तd);
	ext4_block_biपंचांगap_csum_set(sb, group, gdp, biपंचांगap_bh);
	ext4_group_desc_csum_set(sb, group, gdp);
	ext4_handle_dirty_metadata(शून्य, शून्य, gdp_bh);
	sync_dirty_buffer(biपंचांगap_bh);
	sync_dirty_buffer(gdp_bh);
	brअन्यथा(biपंचांगap_bh);
पूर्ण

/**
 * ext4_मुक्त_blocks() -- Free given blocks and update quota
 * @handle:		handle क्रम this transaction
 * @inode:		inode
 * @bh:			optional buffer of the block to be मुक्तd
 * @block:		starting physical block to be मुक्तd
 * @count:		number of blocks to be मुक्तd
 * @flags:		flags used by ext4_मुक्त_blocks
 */
व्योम ext4_मुक्त_blocks(handle_t *handle, काष्ठा inode *inode,
		      काष्ठा buffer_head *bh, ext4_fsblk_t block,
		      अचिन्हित दीर्घ count, पूर्णांक flags)
अणु
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ext4_group_desc *gdp;
	अचिन्हित पूर्णांक overflow;
	ext4_grpblk_t bit;
	काष्ठा buffer_head *gd_bh;
	ext4_group_t block_group;
	काष्ठा ext4_sb_info *sbi;
	काष्ठा ext4_buddy e4b;
	अचिन्हित पूर्णांक count_clusters;
	पूर्णांक err = 0;
	पूर्णांक ret;

	sbi = EXT4_SB(sb);

	अगर (sbi->s_mount_state & EXT4_FC_REPLAY) अणु
		ext4_मुक्त_blocks_simple(inode, block, count);
		वापस;
	पूर्ण

	might_sleep();
	अगर (bh) अणु
		अगर (block)
			BUG_ON(block != bh->b_blocknr);
		अन्यथा
			block = bh->b_blocknr;
	पूर्ण

	अगर (!(flags & EXT4_FREE_BLOCKS_VALIDATED) &&
	    !ext4_inode_block_valid(inode, block, count)) अणु
		ext4_error(sb, "Freeing blocks not in datazone - "
			   "block = %llu, count = %lu", block, count);
		जाओ error_वापस;
	पूर्ण

	ext4_debug("freeing block %llu\n", block);
	trace_ext4_मुक्त_blocks(inode, block, count, flags);

	अगर (bh && (flags & EXT4_FREE_BLOCKS_FORGET)) अणु
		BUG_ON(count > 1);

		ext4_क्रमget(handle, flags & EXT4_FREE_BLOCKS_METADATA,
			    inode, bh, block);
	पूर्ण

	/*
	 * If the extent to be मुक्तd करोes not begin on a cluster
	 * boundary, we need to deal with partial clusters at the
	 * beginning and end of the extent.  Normally we will मुक्त
	 * blocks at the beginning or the end unless we are explicitly
	 * requested to aव्योम करोing so.
	 */
	overflow = EXT4_PBLK_COFF(sbi, block);
	अगर (overflow) अणु
		अगर (flags & EXT4_FREE_BLOCKS_NOFREE_FIRST_CLUSTER) अणु
			overflow = sbi->s_cluster_ratio - overflow;
			block += overflow;
			अगर (count > overflow)
				count -= overflow;
			अन्यथा
				वापस;
		पूर्ण अन्यथा अणु
			block -= overflow;
			count += overflow;
		पूर्ण
	पूर्ण
	overflow = EXT4_LBLK_COFF(sbi, count);
	अगर (overflow) अणु
		अगर (flags & EXT4_FREE_BLOCKS_NOFREE_LAST_CLUSTER) अणु
			अगर (count > overflow)
				count -= overflow;
			अन्यथा
				वापस;
		पूर्ण अन्यथा
			count += sbi->s_cluster_ratio - overflow;
	पूर्ण

	अगर (!bh && (flags & EXT4_FREE_BLOCKS_FORGET)) अणु
		पूर्णांक i;
		पूर्णांक is_metadata = flags & EXT4_FREE_BLOCKS_METADATA;

		क्रम (i = 0; i < count; i++) अणु
			cond_resched();
			अगर (is_metadata)
				bh = sb_find_get_block(inode->i_sb, block + i);
			ext4_क्रमget(handle, is_metadata, inode, bh, block + i);
		पूर्ण
	पूर्ण

करो_more:
	overflow = 0;
	ext4_get_group_no_and_offset(sb, block, &block_group, &bit);

	अगर (unlikely(EXT4_MB_GRP_BBITMAP_CORRUPT(
			ext4_get_group_info(sb, block_group))))
		वापस;

	/*
	 * Check to see अगर we are मुक्तing blocks across a group
	 * boundary.
	 */
	अगर (EXT4_C2B(sbi, bit) + count > EXT4_BLOCKS_PER_GROUP(sb)) अणु
		overflow = EXT4_C2B(sbi, bit) + count -
			EXT4_BLOCKS_PER_GROUP(sb);
		count -= overflow;
	पूर्ण
	count_clusters = EXT4_NUM_B2C(sbi, count);
	biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, block_group);
	अगर (IS_ERR(biपंचांगap_bh)) अणु
		err = PTR_ERR(biपंचांगap_bh);
		biपंचांगap_bh = शून्य;
		जाओ error_वापस;
	पूर्ण
	gdp = ext4_get_group_desc(sb, block_group, &gd_bh);
	अगर (!gdp) अणु
		err = -EIO;
		जाओ error_वापस;
	पूर्ण

	अगर (in_range(ext4_block_biपंचांगap(sb, gdp), block, count) ||
	    in_range(ext4_inode_biपंचांगap(sb, gdp), block, count) ||
	    in_range(block, ext4_inode_table(sb, gdp),
		     sbi->s_itb_per_group) ||
	    in_range(block + count - 1, ext4_inode_table(sb, gdp),
		     sbi->s_itb_per_group)) अणु

		ext4_error(sb, "Freeing blocks in system zone - "
			   "Block = %llu, count = %lu", block, count);
		/* err = 0. ext4_std_error should be a no op */
		जाओ error_वापस;
	पूर्ण

	BUFFER_TRACE(biपंचांगap_bh, "getting write access");
	err = ext4_journal_get_ग_लिखो_access(handle, biपंचांगap_bh);
	अगर (err)
		जाओ error_वापस;

	/*
	 * We are about to modअगरy some metadata.  Call the journal APIs
	 * to unshare ->b_data अगर a currently-committing transaction is
	 * using it
	 */
	BUFFER_TRACE(gd_bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, gd_bh);
	अगर (err)
		जाओ error_वापस;
#अगर_घोषित AGGRESSIVE_CHECK
	अणु
		पूर्णांक i;
		क्रम (i = 0; i < count_clusters; i++)
			BUG_ON(!mb_test_bit(bit + i, biपंचांगap_bh->b_data));
	पूर्ण
#पूर्ण_अगर
	trace_ext4_mballoc_मुक्त(sb, inode, block_group, bit, count_clusters);

	/* __GFP_NOFAIL: retry infinitely, ignore TIF_MEMDIE and memcg limit. */
	err = ext4_mb_load_buddy_gfp(sb, block_group, &e4b,
				     GFP_NOFS|__GFP_NOFAIL);
	अगर (err)
		जाओ error_वापस;

	/*
	 * We need to make sure we करोn't reuse the मुक्तd block until after the
	 * transaction is committed. We make an exception अगर the inode is to be
	 * written in ग_लिखोback mode since ग_लिखोback mode has weak data
	 * consistency guarantees.
	 */
	अगर (ext4_handle_valid(handle) &&
	    ((flags & EXT4_FREE_BLOCKS_METADATA) ||
	     !ext4_should_ग_लिखोback_data(inode))) अणु
		काष्ठा ext4_मुक्त_data *new_entry;
		/*
		 * We use __GFP_NOFAIL because ext4_मुक्त_blocks() is not allowed
		 * to fail.
		 */
		new_entry = kmem_cache_alloc(ext4_मुक्त_data_cachep,
				GFP_NOFS|__GFP_NOFAIL);
		new_entry->efd_start_cluster = bit;
		new_entry->efd_group = block_group;
		new_entry->efd_count = count_clusters;
		new_entry->efd_tid = handle->h_transaction->t_tid;

		ext4_lock_group(sb, block_group);
		mb_clear_bits(biपंचांगap_bh->b_data, bit, count_clusters);
		ext4_mb_मुक्त_metadata(handle, &e4b, new_entry);
	पूर्ण अन्यथा अणु
		/* need to update group_info->bb_मुक्त and biपंचांगap
		 * with group lock held. generate_buddy look at
		 * them with group lock_held
		 */
		अगर (test_opt(sb, DISCARD)) अणु
			err = ext4_issue_discard(sb, block_group, bit, count,
						 शून्य);
			अगर (err && err != -EOPNOTSUPP)
				ext4_msg(sb, KERN_WARNING, "discard request in"
					 " group:%d block:%d count:%lu failed"
					 " with %d", block_group, bit, count,
					 err);
		पूर्ण अन्यथा
			EXT4_MB_GRP_CLEAR_TRIMMED(e4b.bd_info);

		ext4_lock_group(sb, block_group);
		mb_clear_bits(biपंचांगap_bh->b_data, bit, count_clusters);
		mb_मुक्त_blocks(inode, &e4b, bit, count_clusters);
	पूर्ण

	ret = ext4_मुक्त_group_clusters(sb, gdp) + count_clusters;
	ext4_मुक्त_group_clusters_set(sb, gdp, ret);
	ext4_block_biपंचांगap_csum_set(sb, block_group, gdp, biपंचांगap_bh);
	ext4_group_desc_csum_set(sb, block_group, gdp);
	ext4_unlock_group(sb, block_group);

	अगर (sbi->s_log_groups_per_flex) अणु
		ext4_group_t flex_group = ext4_flex_group(sbi, block_group);
		atomic64_add(count_clusters,
			     &sbi_array_rcu_deref(sbi, s_flex_groups,
						  flex_group)->मुक्त_clusters);
	पूर्ण

	/*
	 * on a bigalloc file प्रणाली, defer the s_मुक्तclusters_counter
	 * update to the caller (ext4_हटाओ_space and मित्रs) so they
	 * can determine अगर a cluster मुक्तd here should be rereserved
	 */
	अगर (!(flags & EXT4_FREE_BLOCKS_RERESERVE_CLUSTER)) अणु
		अगर (!(flags & EXT4_FREE_BLOCKS_NO_QUOT_UPDATE))
			dquot_मुक्त_block(inode, EXT4_C2B(sbi, count_clusters));
		percpu_counter_add(&sbi->s_मुक्तclusters_counter,
				   count_clusters);
	पूर्ण

	ext4_mb_unload_buddy(&e4b);

	/* We dirtied the biपंचांगap block */
	BUFFER_TRACE(biपंचांगap_bh, "dirtied bitmap block");
	err = ext4_handle_dirty_metadata(handle, शून्य, biपंचांगap_bh);

	/* And the group descriptor block */
	BUFFER_TRACE(gd_bh, "dirtied group descriptor block");
	ret = ext4_handle_dirty_metadata(handle, शून्य, gd_bh);
	अगर (!err)
		err = ret;

	अगर (overflow && !err) अणु
		block += count;
		count = overflow;
		put_bh(biपंचांगap_bh);
		जाओ करो_more;
	पूर्ण
error_वापस:
	brअन्यथा(biपंचांगap_bh);
	ext4_std_error(sb, err);
	वापस;
पूर्ण

/**
 * ext4_group_add_blocks() -- Add given blocks to an existing group
 * @handle:			handle to this transaction
 * @sb:				super block
 * @block:			start physical block to add to the block group
 * @count:			number of blocks to मुक्त
 *
 * This marks the blocks as मुक्त in the biपंचांगap and buddy.
 */
पूर्णांक ext4_group_add_blocks(handle_t *handle, काष्ठा super_block *sb,
			 ext4_fsblk_t block, अचिन्हित दीर्घ count)
अणु
	काष्ठा buffer_head *biपंचांगap_bh = शून्य;
	काष्ठा buffer_head *gd_bh;
	ext4_group_t block_group;
	ext4_grpblk_t bit;
	अचिन्हित पूर्णांक i;
	काष्ठा ext4_group_desc *desc;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_buddy e4b;
	पूर्णांक err = 0, ret, मुक्त_clusters_count;
	ext4_grpblk_t clusters_मुक्तd;
	ext4_fsblk_t first_cluster = EXT4_B2C(sbi, block);
	ext4_fsblk_t last_cluster = EXT4_B2C(sbi, block + count - 1);
	अचिन्हित दीर्घ cluster_count = last_cluster - first_cluster + 1;

	ext4_debug("Adding block(s) %llu-%llu\n", block, block + count - 1);

	अगर (count == 0)
		वापस 0;

	ext4_get_group_no_and_offset(sb, block, &block_group, &bit);
	/*
	 * Check to see अगर we are मुक्तing blocks across a group
	 * boundary.
	 */
	अगर (bit + cluster_count > EXT4_CLUSTERS_PER_GROUP(sb)) अणु
		ext4_warning(sb, "too many blocks added to group %u",
			     block_group);
		err = -EINVAL;
		जाओ error_वापस;
	पूर्ण

	biपंचांगap_bh = ext4_पढ़ो_block_biपंचांगap(sb, block_group);
	अगर (IS_ERR(biपंचांगap_bh)) अणु
		err = PTR_ERR(biपंचांगap_bh);
		biपंचांगap_bh = शून्य;
		जाओ error_वापस;
	पूर्ण

	desc = ext4_get_group_desc(sb, block_group, &gd_bh);
	अगर (!desc) अणु
		err = -EIO;
		जाओ error_वापस;
	पूर्ण

	अगर (in_range(ext4_block_biपंचांगap(sb, desc), block, count) ||
	    in_range(ext4_inode_biपंचांगap(sb, desc), block, count) ||
	    in_range(block, ext4_inode_table(sb, desc), sbi->s_itb_per_group) ||
	    in_range(block + count - 1, ext4_inode_table(sb, desc),
		     sbi->s_itb_per_group)) अणु
		ext4_error(sb, "Adding blocks in system zones - "
			   "Block = %llu, count = %lu",
			   block, count);
		err = -EINVAL;
		जाओ error_वापस;
	पूर्ण

	BUFFER_TRACE(biपंचांगap_bh, "getting write access");
	err = ext4_journal_get_ग_लिखो_access(handle, biपंचांगap_bh);
	अगर (err)
		जाओ error_वापस;

	/*
	 * We are about to modअगरy some metadata.  Call the journal APIs
	 * to unshare ->b_data अगर a currently-committing transaction is
	 * using it
	 */
	BUFFER_TRACE(gd_bh, "get_write_access");
	err = ext4_journal_get_ग_लिखो_access(handle, gd_bh);
	अगर (err)
		जाओ error_वापस;

	क्रम (i = 0, clusters_मुक्तd = 0; i < cluster_count; i++) अणु
		BUFFER_TRACE(biपंचांगap_bh, "clear bit");
		अगर (!mb_test_bit(bit + i, biपंचांगap_bh->b_data)) अणु
			ext4_error(sb, "bit already cleared for block %llu",
				   (ext4_fsblk_t)(block + i));
			BUFFER_TRACE(biपंचांगap_bh, "bit already cleared");
		पूर्ण अन्यथा अणु
			clusters_मुक्तd++;
		पूर्ण
	पूर्ण

	err = ext4_mb_load_buddy(sb, block_group, &e4b);
	अगर (err)
		जाओ error_वापस;

	/*
	 * need to update group_info->bb_मुक्त and biपंचांगap
	 * with group lock held. generate_buddy look at
	 * them with group lock_held
	 */
	ext4_lock_group(sb, block_group);
	mb_clear_bits(biपंचांगap_bh->b_data, bit, cluster_count);
	mb_मुक्त_blocks(शून्य, &e4b, bit, cluster_count);
	मुक्त_clusters_count = clusters_मुक्तd +
		ext4_मुक्त_group_clusters(sb, desc);
	ext4_मुक्त_group_clusters_set(sb, desc, मुक्त_clusters_count);
	ext4_block_biपंचांगap_csum_set(sb, block_group, desc, biपंचांगap_bh);
	ext4_group_desc_csum_set(sb, block_group, desc);
	ext4_unlock_group(sb, block_group);
	percpu_counter_add(&sbi->s_मुक्तclusters_counter,
			   clusters_मुक्तd);

	अगर (sbi->s_log_groups_per_flex) अणु
		ext4_group_t flex_group = ext4_flex_group(sbi, block_group);
		atomic64_add(clusters_मुक्तd,
			     &sbi_array_rcu_deref(sbi, s_flex_groups,
						  flex_group)->मुक्त_clusters);
	पूर्ण

	ext4_mb_unload_buddy(&e4b);

	/* We dirtied the biपंचांगap block */
	BUFFER_TRACE(biपंचांगap_bh, "dirtied bitmap block");
	err = ext4_handle_dirty_metadata(handle, शून्य, biपंचांगap_bh);

	/* And the group descriptor block */
	BUFFER_TRACE(gd_bh, "dirtied group descriptor block");
	ret = ext4_handle_dirty_metadata(handle, शून्य, gd_bh);
	अगर (!err)
		err = ret;

error_वापस:
	brअन्यथा(biपंचांगap_bh);
	ext4_std_error(sb, err);
	वापस err;
पूर्ण

/**
 * ext4_trim_extent -- function to TRIM one single मुक्त extent in the group
 * @sb:		super block क्रम the file प्रणाली
 * @start:	starting block of the मुक्त extent in the alloc. group
 * @count:	number of blocks to TRIM
 * @group:	alloc. group we are working with
 * @e4b:	ext4 buddy क्रम the group
 *
 * Trim "count" blocks starting at "start" in the "group". To assure that no
 * one will allocate those blocks, mark it as used in buddy biपंचांगap. This must
 * be called with under the group lock.
 */
अटल पूर्णांक ext4_trim_extent(काष्ठा super_block *sb, पूर्णांक start, पूर्णांक count,
			     ext4_group_t group, काष्ठा ext4_buddy *e4b)
__releases(bitlock)
__acquires(bitlock)
अणु
	काष्ठा ext4_मुक्त_extent ex;
	पूर्णांक ret = 0;

	trace_ext4_trim_extent(sb, group, start, count);

	निश्चित_spin_locked(ext4_group_lock_ptr(sb, group));

	ex.fe_start = start;
	ex.fe_group = group;
	ex.fe_len = count;

	/*
	 * Mark blocks used, so no one can reuse them जबतक
	 * being trimmed.
	 */
	mb_mark_used(e4b, &ex);
	ext4_unlock_group(sb, group);
	ret = ext4_issue_discard(sb, group, start, count, शून्य);
	ext4_lock_group(sb, group);
	mb_मुक्त_blocks(शून्य, e4b, start, ex.fe_len);
	वापस ret;
पूर्ण

/**
 * ext4_trim_all_मुक्त -- function to trim all मुक्त space in alloc. group
 * @sb:			super block क्रम file प्रणाली
 * @group:		group to be trimmed
 * @start:		first group block to examine
 * @max:		last group block to examine
 * @minblocks:		minimum extent block count
 *
 * ext4_trim_all_मुक्त walks through group's buddy biपंचांगap searching क्रम मुक्त
 * extents. When the मुक्त block is found, ext4_trim_extent is called to TRIM
 * the extent.
 *
 *
 * ext4_trim_all_मुक्त walks through group's block biपंचांगap searching क्रम मुक्त
 * extents. When the मुक्त extent is found, mark it as used in group buddy
 * biपंचांगap. Then issue a TRIM command on this extent and मुक्त the extent in
 * the group buddy biपंचांगap. This is करोne until whole group is scanned.
 */
अटल ext4_grpblk_t
ext4_trim_all_मुक्त(काष्ठा super_block *sb, ext4_group_t group,
		   ext4_grpblk_t start, ext4_grpblk_t max,
		   ext4_grpblk_t minblocks)
अणु
	व्योम *biपंचांगap;
	ext4_grpblk_t next, count = 0, मुक्त_count = 0;
	काष्ठा ext4_buddy e4b;
	पूर्णांक ret = 0;

	trace_ext4_trim_all_मुक्त(sb, group, start, max);

	ret = ext4_mb_load_buddy(sb, group, &e4b);
	अगर (ret) अणु
		ext4_warning(sb, "Error %d loading buddy information for %u",
			     ret, group);
		वापस ret;
	पूर्ण
	biपंचांगap = e4b.bd_biपंचांगap;

	ext4_lock_group(sb, group);
	अगर (EXT4_MB_GRP_WAS_TRIMMED(e4b.bd_info) &&
	    minblocks >= atomic_पढ़ो(&EXT4_SB(sb)->s_last_trim_minblks))
		जाओ out;

	start = (e4b.bd_info->bb_first_मुक्त > start) ?
		e4b.bd_info->bb_first_मुक्त : start;

	जबतक (start <= max) अणु
		start = mb_find_next_zero_bit(biपंचांगap, max + 1, start);
		अगर (start > max)
			अवरोध;
		next = mb_find_next_bit(biपंचांगap, max + 1, start);

		अगर ((next - start) >= minblocks) अणु
			ret = ext4_trim_extent(sb, start,
					       next - start, group, &e4b);
			अगर (ret && ret != -EOPNOTSUPP)
				अवरोध;
			ret = 0;
			count += next - start;
		पूर्ण
		मुक्त_count += next - start;
		start = next + 1;

		अगर (fatal_संकेत_pending(current)) अणु
			count = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		अगर (need_resched()) अणु
			ext4_unlock_group(sb, group);
			cond_resched();
			ext4_lock_group(sb, group);
		पूर्ण

		अगर ((e4b.bd_info->bb_मुक्त - मुक्त_count) < minblocks)
			अवरोध;
	पूर्ण

	अगर (!ret) अणु
		ret = count;
		EXT4_MB_GRP_SET_TRIMMED(e4b.bd_info);
	पूर्ण
out:
	ext4_unlock_group(sb, group);
	ext4_mb_unload_buddy(&e4b);

	ext4_debug("trimmed %d blocks in the group %d\n",
		count, group);

	वापस ret;
पूर्ण

/**
 * ext4_trim_fs() -- trim ioctl handle function
 * @sb:			superblock क्रम fileप्रणाली
 * @range:		fstrim_range काष्ठाure
 *
 * start:	First Byte to trim
 * len:		number of Bytes to trim from start
 * minlen:	minimum extent length in Bytes
 * ext4_trim_fs goes through all allocation groups containing Bytes from
 * start to start+len. For each such a group ext4_trim_all_मुक्त function
 * is invoked to trim all मुक्त space.
 */
पूर्णांक ext4_trim_fs(काष्ठा super_block *sb, काष्ठा fstrim_range *range)
अणु
	काष्ठा ext4_group_info *grp;
	ext4_group_t group, first_group, last_group;
	ext4_grpblk_t cnt = 0, first_cluster, last_cluster;
	uपूर्णांक64_t start, end, minlen, trimmed = 0;
	ext4_fsblk_t first_data_blk =
			le32_to_cpu(EXT4_SB(sb)->s_es->s_first_data_block);
	ext4_fsblk_t max_blks = ext4_blocks_count(EXT4_SB(sb)->s_es);
	पूर्णांक ret = 0;

	start = range->start >> sb->s_blocksize_bits;
	end = start + (range->len >> sb->s_blocksize_bits) - 1;
	minlen = EXT4_NUM_B2C(EXT4_SB(sb),
			      range->minlen >> sb->s_blocksize_bits);

	अगर (minlen > EXT4_CLUSTERS_PER_GROUP(sb) ||
	    start >= max_blks ||
	    range->len < sb->s_blocksize)
		वापस -EINVAL;
	अगर (end >= max_blks)
		end = max_blks - 1;
	अगर (end <= first_data_blk)
		जाओ out;
	अगर (start < first_data_blk)
		start = first_data_blk;

	/* Determine first and last group to examine based on start and end */
	ext4_get_group_no_and_offset(sb, (ext4_fsblk_t) start,
				     &first_group, &first_cluster);
	ext4_get_group_no_and_offset(sb, (ext4_fsblk_t) end,
				     &last_group, &last_cluster);

	/* end now represents the last cluster to discard in this group */
	end = EXT4_CLUSTERS_PER_GROUP(sb) - 1;

	क्रम (group = first_group; group <= last_group; group++) अणु
		grp = ext4_get_group_info(sb, group);
		/* We only करो this अगर the grp has never been initialized */
		अगर (unlikely(EXT4_MB_GRP_NEED_INIT(grp))) अणु
			ret = ext4_mb_init_group(sb, group, GFP_NOFS);
			अगर (ret)
				अवरोध;
		पूर्ण

		/*
		 * For all the groups except the last one, last cluster will
		 * always be EXT4_CLUSTERS_PER_GROUP(sb)-1, so we only need to
		 * change it क्रम the last group, note that last_cluster is
		 * alपढ़ोy computed earlier by ext4_get_group_no_and_offset()
		 */
		अगर (group == last_group)
			end = last_cluster;

		अगर (grp->bb_मुक्त >= minlen) अणु
			cnt = ext4_trim_all_मुक्त(sb, group, first_cluster,
						end, minlen);
			अगर (cnt < 0) अणु
				ret = cnt;
				अवरोध;
			पूर्ण
			trimmed += cnt;
		पूर्ण

		/*
		 * For every group except the first one, we are sure
		 * that the first cluster to discard will be cluster #0.
		 */
		first_cluster = 0;
	पूर्ण

	अगर (!ret)
		atomic_set(&EXT4_SB(sb)->s_last_trim_minblks, minlen);

out:
	range->len = EXT4_C2B(EXT4_SB(sb), trimmed) << sb->s_blocksize_bits;
	वापस ret;
पूर्ण

/* Iterate all the मुक्त extents in the group. */
पूर्णांक
ext4_mballoc_query_range(
	काष्ठा super_block		*sb,
	ext4_group_t			group,
	ext4_grpblk_t			start,
	ext4_grpblk_t			end,
	ext4_mballoc_query_range_fn	क्रमmatter,
	व्योम				*priv)
अणु
	व्योम				*biपंचांगap;
	ext4_grpblk_t			next;
	काष्ठा ext4_buddy		e4b;
	पूर्णांक				error;

	error = ext4_mb_load_buddy(sb, group, &e4b);
	अगर (error)
		वापस error;
	biपंचांगap = e4b.bd_biपंचांगap;

	ext4_lock_group(sb, group);

	start = (e4b.bd_info->bb_first_मुक्त > start) ?
		e4b.bd_info->bb_first_मुक्त : start;
	अगर (end >= EXT4_CLUSTERS_PER_GROUP(sb))
		end = EXT4_CLUSTERS_PER_GROUP(sb) - 1;

	जबतक (start <= end) अणु
		start = mb_find_next_zero_bit(biपंचांगap, end + 1, start);
		अगर (start > end)
			अवरोध;
		next = mb_find_next_bit(biपंचांगap, end + 1, start);

		ext4_unlock_group(sb, group);
		error = क्रमmatter(sb, group, start, next - start, priv);
		अगर (error)
			जाओ out_unload;
		ext4_lock_group(sb, group);

		start = next + 1;
	पूर्ण

	ext4_unlock_group(sb, group);
out_unload:
	ext4_mb_unload_buddy(&e4b);

	वापस error;
पूर्ण
