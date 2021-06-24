<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/ext4/extents_status.c
 *
 * Written by Yongqiang Yang <xiaoqiangnk@gmail.com>
 * Modअगरied by
 *	Allison Henderson <achender@linux.vnet.ibm.com>
 *	Hugh Dickins <hughd@google.com>
 *	Zheng Liu <wenqing.lz@taobao.com>
 *
 * Ext4 extents status tree core functions.
 */
#समावेश <linux/list_sort.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश "ext4.h"

#समावेश <trace/events/ext4.h>

/*
 * According to previous discussion in Ext4 Developer Workshop, we
 * will पूर्णांकroduce a new काष्ठाure called io tree to track all extent
 * status in order to solve some problems that we have met
 * (e.g. Reservation space warning), and provide extent-level locking.
 * Delay extent tree is the first step to achieve this goal.  It is
 * original built by Yongqiang Yang.  At that समय it is called delay
 * extent tree, whose goal is only track delayed extents in memory to
 * simplअगरy the implementation of fiemap and bigalloc, and पूर्णांकroduce
 * lseek SEEK_DATA/SEEK_HOLE support.  That is why it is still called
 * delay extent tree at the first commit.  But क्रम better understand
 * what it करोes, it has been नाम to extent status tree.
 *
 * Step1:
 * Currently the first step has been करोne.  All delayed extents are
 * tracked in the tree.  It मुख्यtains the delayed extent when a delayed
 * allocation is issued, and the delayed extent is written out or
 * invalidated.  Thereक्रमe the implementation of fiemap and bigalloc
 * are simplअगरied, and SEEK_DATA/SEEK_HOLE are पूर्णांकroduced.
 *
 * The following comment describes the implemenmtation of extent
 * status tree and future works.
 *
 * Step2:
 * In this step all extent status are tracked by extent status tree.
 * Thus, we can first try to lookup a block mapping in this tree beक्रमe
 * finding it in extent tree.  Hence, single extent cache can be हटाओd
 * because extent status tree can करो a better job.  Extents in status
 * tree are loaded on-demand.  Thereक्रमe, the extent status tree may not
 * contain all of the extents in a file.  Meanजबतक we define a shrinker
 * to reclaim memory from extent status tree because fragmented extent
 * tree will make status tree cost too much memory.  written/unwritten/-
 * hole extents in the tree will be reclaimed by this shrinker when we
 * are under high memory pressure.  Delayed extents will not be
 * reclimed because fiemap, bigalloc, and seek_data/hole need it.
 */

/*
 * Extent status tree implementation क्रम ext4.
 *
 *
 * ==========================================================================
 * Extent status tree tracks all extent status.
 *
 * 1. Why we need to implement extent status tree?
 *
 * Without extent status tree, ext4 identअगरies a delayed extent by looking
 * up page cache, this has several deficiencies - complicated, buggy,
 * and inefficient code.
 *
 * FIEMAP, SEEK_HOLE/DATA, bigalloc, and ग_लिखोout all need to know अगर a
 * block or a range of blocks are beदीर्घed to a delayed extent.
 *
 * Let us have a look at how they करो without extent status tree.
 *   --	FIEMAP
 *	FIEMAP looks up page cache to identअगरy delayed allocations from holes.
 *
 *   --	SEEK_HOLE/DATA
 *	SEEK_HOLE/DATA has the same problem as FIEMAP.
 *
 *   --	bigalloc
 *	bigalloc looks up page cache to figure out अगर a block is
 *	alपढ़ोy under delayed allocation or not to determine whether
 *	quota reserving is needed क्रम the cluster.
 *
 *   --	ग_लिखोout
 *	Writeout looks up whole page cache to see अगर a buffer is
 *	mapped, If there are not very many delayed buffers, then it is
 *	समय consuming.
 *
 * With extent status tree implementation, FIEMAP, SEEK_HOLE/DATA,
 * bigalloc and ग_लिखोout can figure out अगर a block or a range of
 * blocks is under delayed allocation(beदीर्घed to a delayed extent) or
 * not by searching the extent tree.
 *
 *
 * ==========================================================================
 * 2. Ext4 extent status tree impelmentation
 *
 *   --	extent
 *	A extent is a range of blocks which are contiguous logically and
 *	physically.  Unlike extent in extent tree, this extent in ext4 is
 *	a in-memory काष्ठा, there is no corresponding on-disk data.  There
 *	is no limit on length of extent, so an extent can contain as many
 *	blocks as they are contiguous logically and physically.
 *
 *   --	extent status tree
 *	Every inode has an extent status tree and all allocation blocks
 *	are added to the tree with dअगरferent status.  The extent in the
 *	tree are ordered by logical block no.
 *
 *   --	operations on a extent status tree
 *	There are three important operations on a delayed extent tree: find
 *	next extent, adding a extent(a range of blocks) and removing a extent.
 *
 *   --	race on a extent status tree
 *	Extent status tree is रक्षित by inode->i_es_lock.
 *
 *   --	memory consumption
 *      Fragmented extent tree will make extent status tree cost too much
 *      memory.  Hence, we will reclaim written/unwritten/hole extents from
 *      the tree under a heavy memory pressure.
 *
 *
 * ==========================================================================
 * 3. Perक्रमmance analysis
 *
 *   --	overhead
 *	1. There is a cache extent क्रम ग_लिखो access, so अगर ग_लिखोs are
 *	not very अक्रमom, adding space operaions are in O(1) समय.
 *
 *   --	gain
 *	2. Code is much simpler, more पढ़ोable, more मुख्यtainable and
 *	more efficient.
 *
 *
 * ==========================================================================
 * 4. TODO list
 *
 *   -- Refactor delayed space reservation
 *
 *   -- Extent-level locking
 */

अटल काष्ठा kmem_cache *ext4_es_cachep;
अटल काष्ठा kmem_cache *ext4_pending_cachep;

अटल पूर्णांक __es_insert_extent(काष्ठा inode *inode, काष्ठा extent_status *newes);
अटल पूर्णांक __es_हटाओ_extent(काष्ठा inode *inode, ext4_lblk_t lblk,
			      ext4_lblk_t end, पूर्णांक *reserved);
अटल पूर्णांक es_reclaim_extents(काष्ठा ext4_inode_info *ei, पूर्णांक *nr_to_scan);
अटल पूर्णांक __es_shrink(काष्ठा ext4_sb_info *sbi, पूर्णांक nr_to_scan,
		       काष्ठा ext4_inode_info *locked_ei);
अटल व्योम __revise_pending(काष्ठा inode *inode, ext4_lblk_t lblk,
			     ext4_lblk_t len);

पूर्णांक __init ext4_init_es(व्योम)
अणु
	ext4_es_cachep = kmem_cache_create("ext4_extent_status",
					   माप(काष्ठा extent_status),
					   0, (SLAB_RECLAIM_ACCOUNT), शून्य);
	अगर (ext4_es_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम ext4_निकास_es(व्योम)
अणु
	kmem_cache_destroy(ext4_es_cachep);
पूर्ण

व्योम ext4_es_init_tree(काष्ठा ext4_es_tree *tree)
अणु
	tree->root = RB_ROOT;
	tree->cache_es = शून्य;
पूर्ण

#अगर_घोषित ES_DEBUG__
अटल व्योम ext4_es_prपूर्णांक_tree(काष्ठा inode *inode)
अणु
	काष्ठा ext4_es_tree *tree;
	काष्ठा rb_node *node;

	prपूर्णांकk(KERN_DEBUG "status extents for inode %lu:", inode->i_ino);
	tree = &EXT4_I(inode)->i_es_tree;
	node = rb_first(&tree->root);
	जबतक (node) अणु
		काष्ठा extent_status *es;
		es = rb_entry(node, काष्ठा extent_status, rb_node);
		prपूर्णांकk(KERN_DEBUG " [%u/%u) %llu %x",
		       es->es_lblk, es->es_len,
		       ext4_es_pblock(es), ext4_es_status(es));
		node = rb_next(node);
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "\n");
पूर्ण
#अन्यथा
#घोषणा ext4_es_prपूर्णांक_tree(inode)
#पूर्ण_अगर

अटल अंतरभूत ext4_lblk_t ext4_es_end(काष्ठा extent_status *es)
अणु
	BUG_ON(es->es_lblk + es->es_len < es->es_lblk);
	वापस es->es_lblk + es->es_len - 1;
पूर्ण

/*
 * search through the tree क्रम an delayed extent with a given offset.  If
 * it can't be found, try to find next extent.
 */
अटल काष्ठा extent_status *__es_tree_search(काष्ठा rb_root *root,
					      ext4_lblk_t lblk)
अणु
	काष्ठा rb_node *node = root->rb_node;
	काष्ठा extent_status *es = शून्य;

	जबतक (node) अणु
		es = rb_entry(node, काष्ठा extent_status, rb_node);
		अगर (lblk < es->es_lblk)
			node = node->rb_left;
		अन्यथा अगर (lblk > ext4_es_end(es))
			node = node->rb_right;
		अन्यथा
			वापस es;
	पूर्ण

	अगर (es && lblk < es->es_lblk)
		वापस es;

	अगर (es && lblk > ext4_es_end(es)) अणु
		node = rb_next(&es->rb_node);
		वापस node ? rb_entry(node, काष्ठा extent_status, rb_node) :
			      शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * ext4_es_find_extent_range - find extent with specअगरied status within block
 *                             range or next extent following block range in
 *                             extents status tree
 *
 * @inode - file containing the range
 * @matching_fn - poपूर्णांकer to function that matches extents with desired status
 * @lblk - logical block defining start of range
 * @end - logical block defining end of range
 * @es - extent found, अगर any
 *
 * Find the first extent within the block range specअगरied by @lblk and @end
 * in the extents status tree that satisfies @matching_fn.  If a match
 * is found, it's वापसed in @es.  If not, and a matching extent is found
 * beyond the block range, it's वापसed in @es.  If no match is found, an
 * extent is वापसed in @es whose es_lblk, es_len, and es_pblk components
 * are 0.
 */
अटल व्योम __es_find_extent_range(काष्ठा inode *inode,
				   पूर्णांक (*matching_fn)(काष्ठा extent_status *es),
				   ext4_lblk_t lblk, ext4_lblk_t end,
				   काष्ठा extent_status *es)
अणु
	काष्ठा ext4_es_tree *tree = शून्य;
	काष्ठा extent_status *es1 = शून्य;
	काष्ठा rb_node *node;

	WARN_ON(es == शून्य);
	WARN_ON(end < lblk);

	tree = &EXT4_I(inode)->i_es_tree;

	/* see अगर the extent has been cached */
	es->es_lblk = es->es_len = es->es_pblk = 0;
	अगर (tree->cache_es) अणु
		es1 = tree->cache_es;
		अगर (in_range(lblk, es1->es_lblk, es1->es_len)) अणु
			es_debug("%u cached by [%u/%u) %llu %x\n",
				 lblk, es1->es_lblk, es1->es_len,
				 ext4_es_pblock(es1), ext4_es_status(es1));
			जाओ out;
		पूर्ण
	पूर्ण

	es1 = __es_tree_search(&tree->root, lblk);

out:
	अगर (es1 && !matching_fn(es1)) अणु
		जबतक ((node = rb_next(&es1->rb_node)) != शून्य) अणु
			es1 = rb_entry(node, काष्ठा extent_status, rb_node);
			अगर (es1->es_lblk > end) अणु
				es1 = शून्य;
				अवरोध;
			पूर्ण
			अगर (matching_fn(es1))
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (es1 && matching_fn(es1)) अणु
		tree->cache_es = es1;
		es->es_lblk = es1->es_lblk;
		es->es_len = es1->es_len;
		es->es_pblk = es1->es_pblk;
	पूर्ण

पूर्ण

/*
 * Locking क्रम __es_find_extent_range() क्रम बाह्यal use
 */
व्योम ext4_es_find_extent_range(काष्ठा inode *inode,
			       पूर्णांक (*matching_fn)(काष्ठा extent_status *es),
			       ext4_lblk_t lblk, ext4_lblk_t end,
			       काष्ठा extent_status *es)
अणु
	अगर (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस;

	trace_ext4_es_find_extent_range_enter(inode, lblk);

	पढ़ो_lock(&EXT4_I(inode)->i_es_lock);
	__es_find_extent_range(inode, matching_fn, lblk, end, es);
	पढ़ो_unlock(&EXT4_I(inode)->i_es_lock);

	trace_ext4_es_find_extent_range_निकास(inode, es);
पूर्ण

/*
 * __es_scan_range - search block range क्रम block with specअगरied status
 *                   in extents status tree
 *
 * @inode - file containing the range
 * @matching_fn - poपूर्णांकer to function that matches extents with desired status
 * @lblk - logical block defining start of range
 * @end - logical block defining end of range
 *
 * Returns true अगर at least one block in the specअगरied block range satisfies
 * the criterion specअगरied by @matching_fn, and false अगर not.  If at least
 * one extent has the specअगरied status, then there is at least one block
 * in the cluster with that status.  Should only be called by code that has
 * taken i_es_lock.
 */
अटल bool __es_scan_range(काष्ठा inode *inode,
			    पूर्णांक (*matching_fn)(काष्ठा extent_status *es),
			    ext4_lblk_t start, ext4_lblk_t end)
अणु
	काष्ठा extent_status es;

	__es_find_extent_range(inode, matching_fn, start, end, &es);
	अगर (es.es_len == 0)
		वापस false;   /* no matching extent in the tree */
	अन्यथा अगर (es.es_lblk <= start &&
		 start < es.es_lblk + es.es_len)
		वापस true;
	अन्यथा अगर (start <= es.es_lblk && es.es_lblk <= end)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण
/*
 * Locking क्रम __es_scan_range() क्रम बाह्यal use
 */
bool ext4_es_scan_range(काष्ठा inode *inode,
			पूर्णांक (*matching_fn)(काष्ठा extent_status *es),
			ext4_lblk_t lblk, ext4_lblk_t end)
अणु
	bool ret;

	अगर (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस false;

	पढ़ो_lock(&EXT4_I(inode)->i_es_lock);
	ret = __es_scan_range(inode, matching_fn, lblk, end);
	पढ़ो_unlock(&EXT4_I(inode)->i_es_lock);

	वापस ret;
पूर्ण

/*
 * __es_scan_clu - search cluster क्रम block with specअगरied status in
 *                 extents status tree
 *
 * @inode - file containing the cluster
 * @matching_fn - poपूर्णांकer to function that matches extents with desired status
 * @lblk - logical block in cluster to be searched
 *
 * Returns true अगर at least one extent in the cluster containing @lblk
 * satisfies the criterion specअगरied by @matching_fn, and false अगर not.  If at
 * least one extent has the specअगरied status, then there is at least one block
 * in the cluster with that status.  Should only be called by code that has
 * taken i_es_lock.
 */
अटल bool __es_scan_clu(काष्ठा inode *inode,
			  पूर्णांक (*matching_fn)(काष्ठा extent_status *es),
			  ext4_lblk_t lblk)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	ext4_lblk_t lblk_start, lblk_end;

	lblk_start = EXT4_LBLK_CMASK(sbi, lblk);
	lblk_end = lblk_start + sbi->s_cluster_ratio - 1;

	वापस __es_scan_range(inode, matching_fn, lblk_start, lblk_end);
पूर्ण

/*
 * Locking क्रम __es_scan_clu() क्रम बाह्यal use
 */
bool ext4_es_scan_clu(काष्ठा inode *inode,
		      पूर्णांक (*matching_fn)(काष्ठा extent_status *es),
		      ext4_lblk_t lblk)
अणु
	bool ret;

	अगर (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस false;

	पढ़ो_lock(&EXT4_I(inode)->i_es_lock);
	ret = __es_scan_clu(inode, matching_fn, lblk);
	पढ़ो_unlock(&EXT4_I(inode)->i_es_lock);

	वापस ret;
पूर्ण

अटल व्योम ext4_es_list_add(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	अगर (!list_empty(&ei->i_es_list))
		वापस;

	spin_lock(&sbi->s_es_lock);
	अगर (list_empty(&ei->i_es_list)) अणु
		list_add_tail(&ei->i_es_list, &sbi->s_es_list);
		sbi->s_es_nr_inode++;
	पूर्ण
	spin_unlock(&sbi->s_es_lock);
पूर्ण

अटल व्योम ext4_es_list_del(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	spin_lock(&sbi->s_es_lock);
	अगर (!list_empty(&ei->i_es_list)) अणु
		list_del_init(&ei->i_es_list);
		sbi->s_es_nr_inode--;
		WARN_ON_ONCE(sbi->s_es_nr_inode < 0);
	पूर्ण
	spin_unlock(&sbi->s_es_lock);
पूर्ण

अटल काष्ठा extent_status *
ext4_es_alloc_extent(काष्ठा inode *inode, ext4_lblk_t lblk, ext4_lblk_t len,
		     ext4_fsblk_t pblk)
अणु
	काष्ठा extent_status *es;
	es = kmem_cache_alloc(ext4_es_cachep, GFP_ATOMIC);
	अगर (es == शून्य)
		वापस शून्य;
	es->es_lblk = lblk;
	es->es_len = len;
	es->es_pblk = pblk;

	/*
	 * We करोn't count delayed extent because we never try to reclaim them
	 */
	अगर (!ext4_es_is_delayed(es)) अणु
		अगर (!EXT4_I(inode)->i_es_shk_nr++)
			ext4_es_list_add(inode);
		percpu_counter_inc(&EXT4_SB(inode->i_sb)->
					s_es_stats.es_stats_shk_cnt);
	पूर्ण

	EXT4_I(inode)->i_es_all_nr++;
	percpu_counter_inc(&EXT4_SB(inode->i_sb)->s_es_stats.es_stats_all_cnt);

	वापस es;
पूर्ण

अटल व्योम ext4_es_मुक्त_extent(काष्ठा inode *inode, काष्ठा extent_status *es)
अणु
	EXT4_I(inode)->i_es_all_nr--;
	percpu_counter_dec(&EXT4_SB(inode->i_sb)->s_es_stats.es_stats_all_cnt);

	/* Decrease the shrink counter when this es is not delayed */
	अगर (!ext4_es_is_delayed(es)) अणु
		BUG_ON(EXT4_I(inode)->i_es_shk_nr == 0);
		अगर (!--EXT4_I(inode)->i_es_shk_nr)
			ext4_es_list_del(inode);
		percpu_counter_dec(&EXT4_SB(inode->i_sb)->
					s_es_stats.es_stats_shk_cnt);
	पूर्ण

	kmem_cache_मुक्त(ext4_es_cachep, es);
पूर्ण

/*
 * Check whether or not two extents can be merged
 * Condition:
 *  - logical block number is contiguous
 *  - physical block number is contiguous
 *  - status is equal
 */
अटल पूर्णांक ext4_es_can_be_merged(काष्ठा extent_status *es1,
				 काष्ठा extent_status *es2)
अणु
	अगर (ext4_es_type(es1) != ext4_es_type(es2))
		वापस 0;

	अगर (((__u64) es1->es_len) + es2->es_len > EXT_MAX_BLOCKS) अणु
		pr_warn("ES assertion failed when merging extents. "
			"The sum of lengths of es1 (%d) and es2 (%d) "
			"is bigger than allowed file size (%d)\n",
			es1->es_len, es2->es_len, EXT_MAX_BLOCKS);
		WARN_ON(1);
		वापस 0;
	पूर्ण

	अगर (((__u64) es1->es_lblk) + es1->es_len != es2->es_lblk)
		वापस 0;

	अगर ((ext4_es_is_written(es1) || ext4_es_is_unwritten(es1)) &&
	    (ext4_es_pblock(es1) + es1->es_len == ext4_es_pblock(es2)))
		वापस 1;

	अगर (ext4_es_is_hole(es1))
		वापस 1;

	/* we need to check delayed extent is without unwritten status */
	अगर (ext4_es_is_delayed(es1) && !ext4_es_is_unwritten(es1))
		वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा extent_status *
ext4_es_try_to_merge_left(काष्ठा inode *inode, काष्ठा extent_status *es)
अणु
	काष्ठा ext4_es_tree *tree = &EXT4_I(inode)->i_es_tree;
	काष्ठा extent_status *es1;
	काष्ठा rb_node *node;

	node = rb_prev(&es->rb_node);
	अगर (!node)
		वापस es;

	es1 = rb_entry(node, काष्ठा extent_status, rb_node);
	अगर (ext4_es_can_be_merged(es1, es)) अणु
		es1->es_len += es->es_len;
		अगर (ext4_es_is_referenced(es))
			ext4_es_set_referenced(es1);
		rb_erase(&es->rb_node, &tree->root);
		ext4_es_मुक्त_extent(inode, es);
		es = es1;
	पूर्ण

	वापस es;
पूर्ण

अटल काष्ठा extent_status *
ext4_es_try_to_merge_right(काष्ठा inode *inode, काष्ठा extent_status *es)
अणु
	काष्ठा ext4_es_tree *tree = &EXT4_I(inode)->i_es_tree;
	काष्ठा extent_status *es1;
	काष्ठा rb_node *node;

	node = rb_next(&es->rb_node);
	अगर (!node)
		वापस es;

	es1 = rb_entry(node, काष्ठा extent_status, rb_node);
	अगर (ext4_es_can_be_merged(es, es1)) अणु
		es->es_len += es1->es_len;
		अगर (ext4_es_is_referenced(es1))
			ext4_es_set_referenced(es);
		rb_erase(node, &tree->root);
		ext4_es_मुक्त_extent(inode, es1);
	पूर्ण

	वापस es;
पूर्ण

#अगर_घोषित ES_AGGRESSIVE_TEST
#समावेश "ext4_extents.h"	/* Needed when ES_AGGRESSIVE_TEST is defined */

अटल व्योम ext4_es_insert_extent_ext_check(काष्ठा inode *inode,
					    काष्ठा extent_status *es)
अणु
	काष्ठा ext4_ext_path *path = शून्य;
	काष्ठा ext4_extent *ex;
	ext4_lblk_t ee_block;
	ext4_fsblk_t ee_start;
	अचिन्हित लघु ee_len;
	पूर्णांक depth, ee_status, es_status;

	path = ext4_find_extent(inode, es->es_lblk, शून्य, EXT4_EX_NOCACHE);
	अगर (IS_ERR(path))
		वापस;

	depth = ext_depth(inode);
	ex = path[depth].p_ext;

	अगर (ex) अणु

		ee_block = le32_to_cpu(ex->ee_block);
		ee_start = ext4_ext_pblock(ex);
		ee_len = ext4_ext_get_actual_len(ex);

		ee_status = ext4_ext_is_unwritten(ex) ? 1 : 0;
		es_status = ext4_es_is_unwritten(es) ? 1 : 0;

		/*
		 * Make sure ex and es are not overlap when we try to insert
		 * a delayed/hole extent.
		 */
		अगर (!ext4_es_is_written(es) && !ext4_es_is_unwritten(es)) अणु
			अगर (in_range(es->es_lblk, ee_block, ee_len)) अणु
				pr_warn("ES insert assertion failed for "
					"inode: %lu we can find an extent "
					"at block [%d/%d/%llu/%c], but we "
					"want to add a delayed/hole extent "
					"[%d/%d/%llu/%x]\n",
					inode->i_ino, ee_block, ee_len,
					ee_start, ee_status ? 'u' : 'w',
					es->es_lblk, es->es_len,
					ext4_es_pblock(es), ext4_es_status(es));
			पूर्ण
			जाओ out;
		पूर्ण

		/*
		 * We करोn't check ee_block == es->es_lblk, etc. because es
		 * might be a part of whole extent, vice versa.
		 */
		अगर (es->es_lblk < ee_block ||
		    ext4_es_pblock(es) != ee_start + es->es_lblk - ee_block) अणु
			pr_warn("ES insert assertion failed for inode: %lu "
				"ex_status [%d/%d/%llu/%c] != "
				"es_status [%d/%d/%llu/%c]\n", inode->i_ino,
				ee_block, ee_len, ee_start,
				ee_status ? 'u' : 'w', es->es_lblk, es->es_len,
				ext4_es_pblock(es), es_status ? 'u' : 'w');
			जाओ out;
		पूर्ण

		अगर (ee_status ^ es_status) अणु
			pr_warn("ES insert assertion failed for inode: %lu "
				"ex_status [%d/%d/%llu/%c] != "
				"es_status [%d/%d/%llu/%c]\n", inode->i_ino,
				ee_block, ee_len, ee_start,
				ee_status ? 'u' : 'w', es->es_lblk, es->es_len,
				ext4_es_pblock(es), es_status ? 'u' : 'w');
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We can't find an extent on disk.  So we need to make sure
		 * that we करोn't want to add an written/unwritten extent.
		 */
		अगर (!ext4_es_is_delayed(es) && !ext4_es_is_hole(es)) अणु
			pr_warn("ES insert assertion failed for inode: %lu "
				"can't find an extent at block %d but we want "
				"to add a written/unwritten extent "
				"[%d/%d/%llu/%x]\n", inode->i_ino,
				es->es_lblk, es->es_lblk, es->es_len,
				ext4_es_pblock(es), ext4_es_status(es));
		पूर्ण
	पूर्ण
out:
	ext4_ext_drop_refs(path);
	kमुक्त(path);
पूर्ण

अटल व्योम ext4_es_insert_extent_ind_check(काष्ठा inode *inode,
					    काष्ठा extent_status *es)
अणु
	काष्ठा ext4_map_blocks map;
	पूर्णांक retval;

	/*
	 * Here we call ext4_ind_map_blocks to lookup a block mapping because
	 * 'Indirect' structure is defined in indirect.c.  So we couldn't
	 * access direct/indirect tree from outside.  It is too dirty to define
	 * this function in indirect.c file.
	 */

	map.m_lblk = es->es_lblk;
	map.m_len = es->es_len;

	retval = ext4_ind_map_blocks(शून्य, inode, &map, 0);
	अगर (retval > 0) अणु
		अगर (ext4_es_is_delayed(es) || ext4_es_is_hole(es)) अणु
			/*
			 * We want to add a delayed/hole extent but this
			 * block has been allocated.
			 */
			pr_warn("ES insert assertion failed for inode: %lu "
				"We can find blocks but we want to add a "
				"delayed/hole extent [%d/%d/%llu/%x]\n",
				inode->i_ino, es->es_lblk, es->es_len,
				ext4_es_pblock(es), ext4_es_status(es));
			वापस;
		पूर्ण अन्यथा अगर (ext4_es_is_written(es)) अणु
			अगर (retval != es->es_len) अणु
				pr_warn("ES insert assertion failed for "
					"inode: %lu retval %d != es_len %d\n",
					inode->i_ino, retval, es->es_len);
				वापस;
			पूर्ण
			अगर (map.m_pblk != ext4_es_pblock(es)) अणु
				pr_warn("ES insert assertion failed for "
					"inode: %lu m_pblk %llu != "
					"es_pblk %llu\n",
					inode->i_ino, map.m_pblk,
					ext4_es_pblock(es));
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * We करोn't need to check unwritten extent because
			 * indirect-based file करोesn't have it.
			 */
			BUG();
		पूर्ण
	पूर्ण अन्यथा अगर (retval == 0) अणु
		अगर (ext4_es_is_written(es)) अणु
			pr_warn("ES insert assertion failed for inode: %lu "
				"We can't find the block but we want to add "
				"a written extent [%d/%d/%llu/%x]\n",
				inode->i_ino, es->es_lblk, es->es_len,
				ext4_es_pblock(es), ext4_es_status(es));
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम ext4_es_insert_extent_check(काष्ठा inode *inode,
					       काष्ठा extent_status *es)
अणु
	/*
	 * We करोn't need to worry about the race condition because
	 * caller takes i_data_sem locking.
	 */
	BUG_ON(!rwsem_is_locked(&EXT4_I(inode)->i_data_sem));
	अगर (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))
		ext4_es_insert_extent_ext_check(inode, es);
	अन्यथा
		ext4_es_insert_extent_ind_check(inode, es);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ext4_es_insert_extent_check(काष्ठा inode *inode,
					       काष्ठा extent_status *es)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __es_insert_extent(काष्ठा inode *inode, काष्ठा extent_status *newes)
अणु
	काष्ठा ext4_es_tree *tree = &EXT4_I(inode)->i_es_tree;
	काष्ठा rb_node **p = &tree->root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा extent_status *es;

	जबतक (*p) अणु
		parent = *p;
		es = rb_entry(parent, काष्ठा extent_status, rb_node);

		अगर (newes->es_lblk < es->es_lblk) अणु
			अगर (ext4_es_can_be_merged(newes, es)) अणु
				/*
				 * Here we can modअगरy es_lblk directly
				 * because it isn't overlapped.
				 */
				es->es_lblk = newes->es_lblk;
				es->es_len += newes->es_len;
				अगर (ext4_es_is_written(es) ||
				    ext4_es_is_unwritten(es))
					ext4_es_store_pblock(es,
							     newes->es_pblk);
				es = ext4_es_try_to_merge_left(inode, es);
				जाओ out;
			पूर्ण
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (newes->es_lblk > ext4_es_end(es)) अणु
			अगर (ext4_es_can_be_merged(es, newes)) अणु
				es->es_len += newes->es_len;
				es = ext4_es_try_to_merge_right(inode, es);
				जाओ out;
			पूर्ण
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			BUG();
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	es = ext4_es_alloc_extent(inode, newes->es_lblk, newes->es_len,
				  newes->es_pblk);
	अगर (!es)
		वापस -ENOMEM;
	rb_link_node(&es->rb_node, parent, p);
	rb_insert_color(&es->rb_node, &tree->root);

out:
	tree->cache_es = es;
	वापस 0;
पूर्ण

/*
 * ext4_es_insert_extent() adds inक्रमmation to an inode's extent
 * status tree.
 *
 * Return 0 on success, error code on failure.
 */
पूर्णांक ext4_es_insert_extent(काष्ठा inode *inode, ext4_lblk_t lblk,
			  ext4_lblk_t len, ext4_fsblk_t pblk,
			  अचिन्हित पूर्णांक status)
अणु
	काष्ठा extent_status newes;
	ext4_lblk_t end = lblk + len - 1;
	पूर्णांक err = 0;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	अगर (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस 0;

	es_debug("add [%u/%u) %llu %x to extent status tree of inode %lu\n",
		 lblk, len, pblk, status, inode->i_ino);

	अगर (!len)
		वापस 0;

	BUG_ON(end < lblk);

	अगर ((status & EXTENT_STATUS_DELAYED) &&
	    (status & EXTENT_STATUS_WRITTEN)) अणु
		ext4_warning(inode->i_sb, "Inserting extent [%u/%u] as "
				" delayed and written which can potentially "
				" cause data loss.", lblk, len);
		WARN_ON(1);
	पूर्ण

	newes.es_lblk = lblk;
	newes.es_len = len;
	ext4_es_store_pblock_status(&newes, pblk, status);
	trace_ext4_es_insert_extent(inode, &newes);

	ext4_es_insert_extent_check(inode, &newes);

	ग_लिखो_lock(&EXT4_I(inode)->i_es_lock);
	err = __es_हटाओ_extent(inode, lblk, end, शून्य);
	अगर (err != 0)
		जाओ error;
retry:
	err = __es_insert_extent(inode, &newes);
	अगर (err == -ENOMEM && __es_shrink(EXT4_SB(inode->i_sb),
					  128, EXT4_I(inode)))
		जाओ retry;
	अगर (err == -ENOMEM && !ext4_es_is_delayed(&newes))
		err = 0;

	अगर (sbi->s_cluster_ratio > 1 && test_opt(inode->i_sb, DELALLOC) &&
	    (status & EXTENT_STATUS_WRITTEN ||
	     status & EXTENT_STATUS_UNWRITTEN))
		__revise_pending(inode, lblk, len);

error:
	ग_लिखो_unlock(&EXT4_I(inode)->i_es_lock);

	ext4_es_prपूर्णांक_tree(inode);

	वापस err;
पूर्ण

/*
 * ext4_es_cache_extent() inserts inक्रमmation पूर्णांकo the extent status
 * tree अगर and only अगर there isn't inक्रमmation about the range in
 * question alपढ़ोy.
 */
व्योम ext4_es_cache_extent(काष्ठा inode *inode, ext4_lblk_t lblk,
			  ext4_lblk_t len, ext4_fsblk_t pblk,
			  अचिन्हित पूर्णांक status)
अणु
	काष्ठा extent_status *es;
	काष्ठा extent_status newes;
	ext4_lblk_t end = lblk + len - 1;

	अगर (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस;

	newes.es_lblk = lblk;
	newes.es_len = len;
	ext4_es_store_pblock_status(&newes, pblk, status);
	trace_ext4_es_cache_extent(inode, &newes);

	अगर (!len)
		वापस;

	BUG_ON(end < lblk);

	ग_लिखो_lock(&EXT4_I(inode)->i_es_lock);

	es = __es_tree_search(&EXT4_I(inode)->i_es_tree.root, lblk);
	अगर (!es || es->es_lblk > end)
		__es_insert_extent(inode, &newes);
	ग_लिखो_unlock(&EXT4_I(inode)->i_es_lock);
पूर्ण

/*
 * ext4_es_lookup_extent() looks up an extent in extent status tree.
 *
 * ext4_es_lookup_extent is called by ext4_map_blocks/ext4_da_map_blocks.
 *
 * Return: 1 on found, 0 on not
 */
पूर्णांक ext4_es_lookup_extent(काष्ठा inode *inode, ext4_lblk_t lblk,
			  ext4_lblk_t *next_lblk,
			  काष्ठा extent_status *es)
अणु
	काष्ठा ext4_es_tree *tree;
	काष्ठा ext4_es_stats *stats;
	काष्ठा extent_status *es1 = शून्य;
	काष्ठा rb_node *node;
	पूर्णांक found = 0;

	अगर (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस 0;

	trace_ext4_es_lookup_extent_enter(inode, lblk);
	es_debug("lookup extent in block %u\n", lblk);

	tree = &EXT4_I(inode)->i_es_tree;
	पढ़ो_lock(&EXT4_I(inode)->i_es_lock);

	/* find extent in cache firstly */
	es->es_lblk = es->es_len = es->es_pblk = 0;
	अगर (tree->cache_es) अणु
		es1 = tree->cache_es;
		अगर (in_range(lblk, es1->es_lblk, es1->es_len)) अणु
			es_debug("%u cached by [%u/%u)\n",
				 lblk, es1->es_lblk, es1->es_len);
			found = 1;
			जाओ out;
		पूर्ण
	पूर्ण

	node = tree->root.rb_node;
	जबतक (node) अणु
		es1 = rb_entry(node, काष्ठा extent_status, rb_node);
		अगर (lblk < es1->es_lblk)
			node = node->rb_left;
		अन्यथा अगर (lblk > ext4_es_end(es1))
			node = node->rb_right;
		अन्यथा अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	stats = &EXT4_SB(inode->i_sb)->s_es_stats;
	अगर (found) अणु
		BUG_ON(!es1);
		es->es_lblk = es1->es_lblk;
		es->es_len = es1->es_len;
		es->es_pblk = es1->es_pblk;
		अगर (!ext4_es_is_referenced(es1))
			ext4_es_set_referenced(es1);
		percpu_counter_inc(&stats->es_stats_cache_hits);
		अगर (next_lblk) अणु
			node = rb_next(&es1->rb_node);
			अगर (node) अणु
				es1 = rb_entry(node, काष्ठा extent_status,
					       rb_node);
				*next_lblk = es1->es_lblk;
			पूर्ण अन्यथा
				*next_lblk = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		percpu_counter_inc(&stats->es_stats_cache_misses);
	पूर्ण

	पढ़ो_unlock(&EXT4_I(inode)->i_es_lock);

	trace_ext4_es_lookup_extent_निकास(inode, es, found);
	वापस found;
पूर्ण

काष्ठा rsvd_count अणु
	पूर्णांक ndelonly;
	bool first_करो_lblk_found;
	ext4_lblk_t first_करो_lblk;
	ext4_lblk_t last_करो_lblk;
	काष्ठा extent_status *left_es;
	bool partial;
	ext4_lblk_t lclu;
पूर्ण;

/*
 * init_rsvd - initialize reserved count data beक्रमe removing block range
 *	       in file from extent status tree
 *
 * @inode - file containing range
 * @lblk - first block in range
 * @es - poपूर्णांकer to first extent in range
 * @rc - poपूर्णांकer to reserved count data
 *
 * Assumes es is not शून्य
 */
अटल व्योम init_rsvd(काष्ठा inode *inode, ext4_lblk_t lblk,
		      काष्ठा extent_status *es, काष्ठा rsvd_count *rc)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा rb_node *node;

	rc->ndelonly = 0;

	/*
	 * क्रम bigalloc, note the first delonly block in the range has not
	 * been found, record the extent containing the block to the left of
	 * the region to be हटाओd, अगर any, and note that there's no partial
	 * cluster to track
	 */
	अगर (sbi->s_cluster_ratio > 1) अणु
		rc->first_करो_lblk_found = false;
		अगर (lblk > es->es_lblk) अणु
			rc->left_es = es;
		पूर्ण अन्यथा अणु
			node = rb_prev(&es->rb_node);
			rc->left_es = node ? rb_entry(node,
						      काष्ठा extent_status,
						      rb_node) : शून्य;
		पूर्ण
		rc->partial = false;
	पूर्ण
पूर्ण

/*
 * count_rsvd - count the clusters containing delayed and not unwritten
 *		(delonly) blocks in a range within an extent and add to
 *	        the running tally in rsvd_count
 *
 * @inode - file containing extent
 * @lblk - first block in range
 * @len - length of range in blocks
 * @es - poपूर्णांकer to extent containing clusters to be counted
 * @rc - poपूर्णांकer to reserved count data
 *
 * Tracks partial clusters found at the beginning and end of extents so
 * they aren't overcounted when they span adjacent extents
 */
अटल व्योम count_rsvd(काष्ठा inode *inode, ext4_lblk_t lblk, दीर्घ len,
		       काष्ठा extent_status *es, काष्ठा rsvd_count *rc)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	ext4_lblk_t i, end, nclu;

	अगर (!ext4_es_is_delonly(es))
		वापस;

	WARN_ON(len <= 0);

	अगर (sbi->s_cluster_ratio == 1) अणु
		rc->ndelonly += (पूर्णांक) len;
		वापस;
	पूर्ण

	/* bigalloc */

	i = (lblk < es->es_lblk) ? es->es_lblk : lblk;
	end = lblk + (ext4_lblk_t) len - 1;
	end = (end > ext4_es_end(es)) ? ext4_es_end(es) : end;

	/* record the first block of the first delonly extent seen */
	अगर (!rc->first_करो_lblk_found) अणु
		rc->first_करो_lblk = i;
		rc->first_करो_lblk_found = true;
	पूर्ण

	/* update the last lblk in the region seen so far */
	rc->last_करो_lblk = end;

	/*
	 * अगर we're tracking a partial cluster and the current extent
	 * करोesn't start with it, count it and stop tracking
	 */
	अगर (rc->partial && (rc->lclu != EXT4_B2C(sbi, i))) अणु
		rc->ndelonly++;
		rc->partial = false;
	पूर्ण

	/*
	 * अगर the first cluster करोesn't start on a cluster boundary but
	 * ends on one, count it
	 */
	अगर (EXT4_LBLK_COFF(sbi, i) != 0) अणु
		अगर (end >= EXT4_LBLK_CFILL(sbi, i)) अणु
			rc->ndelonly++;
			rc->partial = false;
			i = EXT4_LBLK_CFILL(sbi, i) + 1;
		पूर्ण
	पूर्ण

	/*
	 * अगर the current cluster starts on a cluster boundary, count the
	 * number of whole delonly clusters in the extent
	 */
	अगर ((i + sbi->s_cluster_ratio - 1) <= end) अणु
		nclu = (end - i + 1) >> sbi->s_cluster_bits;
		rc->ndelonly += nclu;
		i += nclu << sbi->s_cluster_bits;
	पूर्ण

	/*
	 * start tracking a partial cluster अगर there's a partial at the end
	 * of the current extent and we're not alपढ़ोy tracking one
	 */
	अगर (!rc->partial && i <= end) अणु
		rc->partial = true;
		rc->lclu = EXT4_B2C(sbi, i);
	पूर्ण
पूर्ण

/*
 * __pr_tree_search - search क्रम a pending cluster reservation
 *
 * @root - root of pending reservation tree
 * @lclu - logical cluster to search क्रम
 *
 * Returns the pending reservation क्रम the cluster identअगरied by @lclu
 * अगर found.  If not, वापसs a reservation क्रम the next cluster अगर any,
 * and अगर not, वापसs शून्य.
 */
अटल काष्ठा pending_reservation *__pr_tree_search(काष्ठा rb_root *root,
						    ext4_lblk_t lclu)
अणु
	काष्ठा rb_node *node = root->rb_node;
	काष्ठा pending_reservation *pr = शून्य;

	जबतक (node) अणु
		pr = rb_entry(node, काष्ठा pending_reservation, rb_node);
		अगर (lclu < pr->lclu)
			node = node->rb_left;
		अन्यथा अगर (lclu > pr->lclu)
			node = node->rb_right;
		अन्यथा
			वापस pr;
	पूर्ण
	अगर (pr && lclu < pr->lclu)
		वापस pr;
	अगर (pr && lclu > pr->lclu) अणु
		node = rb_next(&pr->rb_node);
		वापस node ? rb_entry(node, काष्ठा pending_reservation,
				       rb_node) : शून्य;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * get_rsvd - calculates and वापसs the number of cluster reservations to be
 *	      released when removing a block range from the extent status tree
 *	      and releases any pending reservations within the range
 *
 * @inode - file containing block range
 * @end - last block in range
 * @right_es - poपूर्णांकer to extent containing next block beyond end or शून्य
 * @rc - poपूर्णांकer to reserved count data
 *
 * The number of reservations to be released is equal to the number of
 * clusters containing delayed and not unwritten (delonly) blocks within
 * the range, minus the number of clusters still containing delonly blocks
 * at the ends of the range, and minus the number of pending reservations
 * within the range.
 */
अटल अचिन्हित पूर्णांक get_rsvd(काष्ठा inode *inode, ext4_lblk_t end,
			     काष्ठा extent_status *right_es,
			     काष्ठा rsvd_count *rc)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा pending_reservation *pr;
	काष्ठा ext4_pending_tree *tree = &EXT4_I(inode)->i_pending_tree;
	काष्ठा rb_node *node;
	ext4_lblk_t first_lclu, last_lclu;
	bool left_delonly, right_delonly, count_pending;
	काष्ठा extent_status *es;

	अगर (sbi->s_cluster_ratio > 1) अणु
		/* count any reमुख्यing partial cluster */
		अगर (rc->partial)
			rc->ndelonly++;

		अगर (rc->ndelonly == 0)
			वापस 0;

		first_lclu = EXT4_B2C(sbi, rc->first_करो_lblk);
		last_lclu = EXT4_B2C(sbi, rc->last_करो_lblk);

		/*
		 * decrease the delonly count by the number of clusters at the
		 * ends of the range that still contain delonly blocks -
		 * these clusters still need to be reserved
		 */
		left_delonly = right_delonly = false;

		es = rc->left_es;
		जबतक (es && ext4_es_end(es) >=
		       EXT4_LBLK_CMASK(sbi, rc->first_करो_lblk)) अणु
			अगर (ext4_es_is_delonly(es)) अणु
				rc->ndelonly--;
				left_delonly = true;
				अवरोध;
			पूर्ण
			node = rb_prev(&es->rb_node);
			अगर (!node)
				अवरोध;
			es = rb_entry(node, काष्ठा extent_status, rb_node);
		पूर्ण
		अगर (right_es && (!left_delonly || first_lclu != last_lclu)) अणु
			अगर (end < ext4_es_end(right_es)) अणु
				es = right_es;
			पूर्ण अन्यथा अणु
				node = rb_next(&right_es->rb_node);
				es = node ? rb_entry(node, काष्ठा extent_status,
						     rb_node) : शून्य;
			पूर्ण
			जबतक (es && es->es_lblk <=
			       EXT4_LBLK_CFILL(sbi, rc->last_करो_lblk)) अणु
				अगर (ext4_es_is_delonly(es)) अणु
					rc->ndelonly--;
					right_delonly = true;
					अवरोध;
				पूर्ण
				node = rb_next(&es->rb_node);
				अगर (!node)
					अवरोध;
				es = rb_entry(node, काष्ठा extent_status,
					      rb_node);
			पूर्ण
		पूर्ण

		/*
		 * Determine the block range that should be searched क्रम
		 * pending reservations, अगर any.  Clusters on the ends of the
		 * original हटाओd range containing delonly blocks are
		 * excluded.  They've already been accounted for and it's not
		 * possible to determine अगर an associated pending reservation
		 * should be released with the inक्रमmation available in the
		 * extents status tree.
		 */
		अगर (first_lclu == last_lclu) अणु
			अगर (left_delonly | right_delonly)
				count_pending = false;
			अन्यथा
				count_pending = true;
		पूर्ण अन्यथा अणु
			अगर (left_delonly)
				first_lclu++;
			अगर (right_delonly)
				last_lclu--;
			अगर (first_lclu <= last_lclu)
				count_pending = true;
			अन्यथा
				count_pending = false;
		पूर्ण

		/*
		 * a pending reservation found between first_lclu and last_lclu
		 * represents an allocated cluster that contained at least one
		 * delonly block, so the delonly total must be reduced by one
		 * क्रम each pending reservation found and released
		 */
		अगर (count_pending) अणु
			pr = __pr_tree_search(&tree->root, first_lclu);
			जबतक (pr && pr->lclu <= last_lclu) अणु
				rc->ndelonly--;
				node = rb_next(&pr->rb_node);
				rb_erase(&pr->rb_node, &tree->root);
				kmem_cache_मुक्त(ext4_pending_cachep, pr);
				अगर (!node)
					अवरोध;
				pr = rb_entry(node, काष्ठा pending_reservation,
					      rb_node);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस rc->ndelonly;
पूर्ण


/*
 * __es_हटाओ_extent - हटाओs block range from extent status tree
 *
 * @inode - file containing range
 * @lblk - first block in range
 * @end - last block in range
 * @reserved - number of cluster reservations released
 *
 * If @reserved is not शून्य and delayed allocation is enabled, counts
 * block/cluster reservations मुक्तd by removing range and अगर bigalloc
 * enabled cancels pending reservations as needed. Returns 0 on success,
 * error code on failure.
 */
अटल पूर्णांक __es_हटाओ_extent(काष्ठा inode *inode, ext4_lblk_t lblk,
			      ext4_lblk_t end, पूर्णांक *reserved)
अणु
	काष्ठा ext4_es_tree *tree = &EXT4_I(inode)->i_es_tree;
	काष्ठा rb_node *node;
	काष्ठा extent_status *es;
	काष्ठा extent_status orig_es;
	ext4_lblk_t len1, len2;
	ext4_fsblk_t block;
	पूर्णांक err;
	bool count_reserved = true;
	काष्ठा rsvd_count rc;

	अगर (reserved == शून्य || !test_opt(inode->i_sb, DELALLOC))
		count_reserved = false;
retry:
	err = 0;

	es = __es_tree_search(&tree->root, lblk);
	अगर (!es)
		जाओ out;
	अगर (es->es_lblk > end)
		जाओ out;

	/* Simply invalidate cache_es. */
	tree->cache_es = शून्य;
	अगर (count_reserved)
		init_rsvd(inode, lblk, es, &rc);

	orig_es.es_lblk = es->es_lblk;
	orig_es.es_len = es->es_len;
	orig_es.es_pblk = es->es_pblk;

	len1 = lblk > es->es_lblk ? lblk - es->es_lblk : 0;
	len2 = ext4_es_end(es) > end ? ext4_es_end(es) - end : 0;
	अगर (len1 > 0)
		es->es_len = len1;
	अगर (len2 > 0) अणु
		अगर (len1 > 0) अणु
			काष्ठा extent_status newes;

			newes.es_lblk = end + 1;
			newes.es_len = len2;
			block = 0x7FDEADBEEFULL;
			अगर (ext4_es_is_written(&orig_es) ||
			    ext4_es_is_unwritten(&orig_es))
				block = ext4_es_pblock(&orig_es) +
					orig_es.es_len - len2;
			ext4_es_store_pblock_status(&newes, block,
						    ext4_es_status(&orig_es));
			err = __es_insert_extent(inode, &newes);
			अगर (err) अणु
				es->es_lblk = orig_es.es_lblk;
				es->es_len = orig_es.es_len;
				अगर ((err == -ENOMEM) &&
				    __es_shrink(EXT4_SB(inode->i_sb),
							128, EXT4_I(inode)))
					जाओ retry;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			es->es_lblk = end + 1;
			es->es_len = len2;
			अगर (ext4_es_is_written(es) ||
			    ext4_es_is_unwritten(es)) अणु
				block = orig_es.es_pblk + orig_es.es_len - len2;
				ext4_es_store_pblock(es, block);
			पूर्ण
		पूर्ण
		अगर (count_reserved)
			count_rsvd(inode, lblk, orig_es.es_len - len1 - len2,
				   &orig_es, &rc);
		जाओ out;
	पूर्ण

	अगर (len1 > 0) अणु
		अगर (count_reserved)
			count_rsvd(inode, lblk, orig_es.es_len - len1,
				   &orig_es, &rc);
		node = rb_next(&es->rb_node);
		अगर (node)
			es = rb_entry(node, काष्ठा extent_status, rb_node);
		अन्यथा
			es = शून्य;
	पूर्ण

	जबतक (es && ext4_es_end(es) <= end) अणु
		अगर (count_reserved)
			count_rsvd(inode, es->es_lblk, es->es_len, es, &rc);
		node = rb_next(&es->rb_node);
		rb_erase(&es->rb_node, &tree->root);
		ext4_es_मुक्त_extent(inode, es);
		अगर (!node) अणु
			es = शून्य;
			अवरोध;
		पूर्ण
		es = rb_entry(node, काष्ठा extent_status, rb_node);
	पूर्ण

	अगर (es && es->es_lblk < end + 1) अणु
		ext4_lblk_t orig_len = es->es_len;

		len1 = ext4_es_end(es) - end;
		अगर (count_reserved)
			count_rsvd(inode, es->es_lblk, orig_len - len1,
				   es, &rc);
		es->es_lblk = end + 1;
		es->es_len = len1;
		अगर (ext4_es_is_written(es) || ext4_es_is_unwritten(es)) अणु
			block = es->es_pblk + orig_len - len1;
			ext4_es_store_pblock(es, block);
		पूर्ण
	पूर्ण

	अगर (count_reserved)
		*reserved = get_rsvd(inode, end, es, &rc);
out:
	वापस err;
पूर्ण

/*
 * ext4_es_हटाओ_extent - हटाओs block range from extent status tree
 *
 * @inode - file containing range
 * @lblk - first block in range
 * @len - number of blocks to हटाओ
 *
 * Reduces block/cluster reservation count and क्रम bigalloc cancels pending
 * reservations as needed. Returns 0 on success, error code on failure.
 */
पूर्णांक ext4_es_हटाओ_extent(काष्ठा inode *inode, ext4_lblk_t lblk,
			  ext4_lblk_t len)
अणु
	ext4_lblk_t end;
	पूर्णांक err = 0;
	पूर्णांक reserved = 0;

	अगर (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस 0;

	trace_ext4_es_हटाओ_extent(inode, lblk, len);
	es_debug("remove [%u/%u) from extent status tree of inode %lu\n",
		 lblk, len, inode->i_ino);

	अगर (!len)
		वापस err;

	end = lblk + len - 1;
	BUG_ON(end < lblk);

	/*
	 * ext4_clear_inode() depends on us taking i_es_lock unconditionally
	 * so that we are sure __es_shrink() is करोne with the inode beक्रमe it
	 * is reclaimed.
	 */
	ग_लिखो_lock(&EXT4_I(inode)->i_es_lock);
	err = __es_हटाओ_extent(inode, lblk, end, &reserved);
	ग_लिखो_unlock(&EXT4_I(inode)->i_es_lock);
	ext4_es_prपूर्णांक_tree(inode);
	ext4_da_release_space(inode, reserved);
	वापस err;
पूर्ण

अटल पूर्णांक __es_shrink(काष्ठा ext4_sb_info *sbi, पूर्णांक nr_to_scan,
		       काष्ठा ext4_inode_info *locked_ei)
अणु
	काष्ठा ext4_inode_info *ei;
	काष्ठा ext4_es_stats *es_stats;
	kसमय_प्रकार start_समय;
	u64 scan_समय;
	पूर्णांक nr_to_walk;
	पूर्णांक nr_shrunk = 0;
	पूर्णांक retried = 0, nr_skipped = 0;

	es_stats = &sbi->s_es_stats;
	start_समय = kसमय_get();

retry:
	spin_lock(&sbi->s_es_lock);
	nr_to_walk = sbi->s_es_nr_inode;
	जबतक (nr_to_walk-- > 0) अणु
		अगर (list_empty(&sbi->s_es_list)) अणु
			spin_unlock(&sbi->s_es_lock);
			जाओ out;
		पूर्ण
		ei = list_first_entry(&sbi->s_es_list, काष्ठा ext4_inode_info,
				      i_es_list);
		/* Move the inode to the tail */
		list_move_tail(&ei->i_es_list, &sbi->s_es_list);

		/*
		 * Normally we try hard to aव्योम shrinking precached inodes,
		 * but we will as a last resort.
		 */
		अगर (!retried && ext4_test_inode_state(&ei->vfs_inode,
						EXT4_STATE_EXT_PRECACHED)) अणु
			nr_skipped++;
			जारी;
		पूर्ण

		अगर (ei == locked_ei || !ग_लिखो_trylock(&ei->i_es_lock)) अणु
			nr_skipped++;
			जारी;
		पूर्ण
		/*
		 * Now we hold i_es_lock which protects us from inode reclaim
		 * मुक्तing inode under us
		 */
		spin_unlock(&sbi->s_es_lock);

		nr_shrunk += es_reclaim_extents(ei, &nr_to_scan);
		ग_लिखो_unlock(&ei->i_es_lock);

		अगर (nr_to_scan <= 0)
			जाओ out;
		spin_lock(&sbi->s_es_lock);
	पूर्ण
	spin_unlock(&sbi->s_es_lock);

	/*
	 * If we skipped any inodes, and we weren't able to make any
	 * क्रमward progress, try again to scan precached inodes.
	 */
	अगर ((nr_shrunk == 0) && nr_skipped && !retried) अणु
		retried++;
		जाओ retry;
	पूर्ण

	अगर (locked_ei && nr_shrunk == 0)
		nr_shrunk = es_reclaim_extents(locked_ei, &nr_to_scan);

out:
	scan_समय = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), start_समय));
	अगर (likely(es_stats->es_stats_scan_समय))
		es_stats->es_stats_scan_समय = (scan_समय +
				es_stats->es_stats_scan_समय*3) / 4;
	अन्यथा
		es_stats->es_stats_scan_समय = scan_समय;
	अगर (scan_समय > es_stats->es_stats_max_scan_समय)
		es_stats->es_stats_max_scan_समय = scan_समय;
	अगर (likely(es_stats->es_stats_shrunk))
		es_stats->es_stats_shrunk = (nr_shrunk +
				es_stats->es_stats_shrunk*3) / 4;
	अन्यथा
		es_stats->es_stats_shrunk = nr_shrunk;

	trace_ext4_es_shrink(sbi->s_sb, nr_shrunk, scan_समय,
			     nr_skipped, retried);
	वापस nr_shrunk;
पूर्ण

अटल अचिन्हित दीर्घ ext4_es_count(काष्ठा shrinker *shrink,
				   काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ nr;
	काष्ठा ext4_sb_info *sbi;

	sbi = container_of(shrink, काष्ठा ext4_sb_info, s_es_shrinker);
	nr = percpu_counter_पढ़ो_positive(&sbi->s_es_stats.es_stats_shk_cnt);
	trace_ext4_es_shrink_count(sbi->s_sb, sc->nr_to_scan, nr);
	वापस nr;
पूर्ण

अटल अचिन्हित दीर्घ ext4_es_scan(काष्ठा shrinker *shrink,
				  काष्ठा shrink_control *sc)
अणु
	काष्ठा ext4_sb_info *sbi = container_of(shrink,
					काष्ठा ext4_sb_info, s_es_shrinker);
	पूर्णांक nr_to_scan = sc->nr_to_scan;
	पूर्णांक ret, nr_shrunk;

	ret = percpu_counter_पढ़ो_positive(&sbi->s_es_stats.es_stats_shk_cnt);
	trace_ext4_es_shrink_scan_enter(sbi->s_sb, nr_to_scan, ret);

	अगर (!nr_to_scan)
		वापस ret;

	nr_shrunk = __es_shrink(sbi, nr_to_scan, शून्य);

	trace_ext4_es_shrink_scan_निकास(sbi->s_sb, nr_shrunk, ret);
	वापस nr_shrunk;
पूर्ण

पूर्णांक ext4_seq_es_shrinker_info_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB((काष्ठा super_block *) seq->निजी);
	काष्ठा ext4_es_stats *es_stats = &sbi->s_es_stats;
	काष्ठा ext4_inode_info *ei, *max = शून्य;
	अचिन्हित पूर्णांक inode_cnt = 0;

	अगर (v != SEQ_START_TOKEN)
		वापस 0;

	/* here we just find an inode that has the max nr. of objects */
	spin_lock(&sbi->s_es_lock);
	list_क्रम_each_entry(ei, &sbi->s_es_list, i_es_list) अणु
		inode_cnt++;
		अगर (max && max->i_es_all_nr < ei->i_es_all_nr)
			max = ei;
		अन्यथा अगर (!max)
			max = ei;
	पूर्ण
	spin_unlock(&sbi->s_es_lock);

	seq_म_लिखो(seq, "stats:\n  %lld objects\n  %lld reclaimable objects\n",
		   percpu_counter_sum_positive(&es_stats->es_stats_all_cnt),
		   percpu_counter_sum_positive(&es_stats->es_stats_shk_cnt));
	seq_म_लिखो(seq, "  %lld/%lld cache hits/misses\n",
		   percpu_counter_sum_positive(&es_stats->es_stats_cache_hits),
		   percpu_counter_sum_positive(&es_stats->es_stats_cache_misses));
	अगर (inode_cnt)
		seq_म_लिखो(seq, "  %d inodes on list\n", inode_cnt);

	seq_म_लिखो(seq, "average:\n  %llu us scan time\n",
	    भाग_u64(es_stats->es_stats_scan_समय, 1000));
	seq_म_लिखो(seq, "  %lu shrunk objects\n", es_stats->es_stats_shrunk);
	अगर (inode_cnt)
		seq_म_लिखो(seq,
		    "maximum:\n  %lu inode (%u objects, %u reclaimable)\n"
		    "  %llu us max scan time\n",
		    max->vfs_inode.i_ino, max->i_es_all_nr, max->i_es_shk_nr,
		    भाग_u64(es_stats->es_stats_max_scan_समय, 1000));

	वापस 0;
पूर्ण

पूर्णांक ext4_es_रेजिस्टर_shrinker(काष्ठा ext4_sb_info *sbi)
अणु
	पूर्णांक err;

	/* Make sure we have enough bits क्रम physical block number */
	BUILD_BUG_ON(ES_SHIFT < 48);
	INIT_LIST_HEAD(&sbi->s_es_list);
	sbi->s_es_nr_inode = 0;
	spin_lock_init(&sbi->s_es_lock);
	sbi->s_es_stats.es_stats_shrunk = 0;
	err = percpu_counter_init(&sbi->s_es_stats.es_stats_cache_hits, 0,
				  GFP_KERNEL);
	अगर (err)
		वापस err;
	err = percpu_counter_init(&sbi->s_es_stats.es_stats_cache_misses, 0,
				  GFP_KERNEL);
	अगर (err)
		जाओ err1;
	sbi->s_es_stats.es_stats_scan_समय = 0;
	sbi->s_es_stats.es_stats_max_scan_समय = 0;
	err = percpu_counter_init(&sbi->s_es_stats.es_stats_all_cnt, 0, GFP_KERNEL);
	अगर (err)
		जाओ err2;
	err = percpu_counter_init(&sbi->s_es_stats.es_stats_shk_cnt, 0, GFP_KERNEL);
	अगर (err)
		जाओ err3;

	sbi->s_es_shrinker.scan_objects = ext4_es_scan;
	sbi->s_es_shrinker.count_objects = ext4_es_count;
	sbi->s_es_shrinker.seeks = DEFAULT_SEEKS;
	err = रेजिस्टर_shrinker(&sbi->s_es_shrinker);
	अगर (err)
		जाओ err4;

	वापस 0;
err4:
	percpu_counter_destroy(&sbi->s_es_stats.es_stats_shk_cnt);
err3:
	percpu_counter_destroy(&sbi->s_es_stats.es_stats_all_cnt);
err2:
	percpu_counter_destroy(&sbi->s_es_stats.es_stats_cache_misses);
err1:
	percpu_counter_destroy(&sbi->s_es_stats.es_stats_cache_hits);
	वापस err;
पूर्ण

व्योम ext4_es_unरेजिस्टर_shrinker(काष्ठा ext4_sb_info *sbi)
अणु
	percpu_counter_destroy(&sbi->s_es_stats.es_stats_cache_hits);
	percpu_counter_destroy(&sbi->s_es_stats.es_stats_cache_misses);
	percpu_counter_destroy(&sbi->s_es_stats.es_stats_all_cnt);
	percpu_counter_destroy(&sbi->s_es_stats.es_stats_shk_cnt);
	unरेजिस्टर_shrinker(&sbi->s_es_shrinker);
पूर्ण

/*
 * Shrink extents in given inode from ei->i_es_shrink_lblk till end. Scan at
 * most *nr_to_scan extents, update *nr_to_scan accordingly.
 *
 * Return 0 अगर we hit end of tree / पूर्णांकerval, 1 अगर we exhausted nr_to_scan.
 * Increment *nr_shrunk by the number of reclaimed extents. Also update
 * ei->i_es_shrink_lblk to where we should जारी scanning.
 */
अटल पूर्णांक es_करो_reclaim_extents(काष्ठा ext4_inode_info *ei, ext4_lblk_t end,
				 पूर्णांक *nr_to_scan, पूर्णांक *nr_shrunk)
अणु
	काष्ठा inode *inode = &ei->vfs_inode;
	काष्ठा ext4_es_tree *tree = &ei->i_es_tree;
	काष्ठा extent_status *es;
	काष्ठा rb_node *node;

	es = __es_tree_search(&tree->root, ei->i_es_shrink_lblk);
	अगर (!es)
		जाओ out_wrap;

	जबतक (*nr_to_scan > 0) अणु
		अगर (es->es_lblk > end) अणु
			ei->i_es_shrink_lblk = end + 1;
			वापस 0;
		पूर्ण

		(*nr_to_scan)--;
		node = rb_next(&es->rb_node);
		/*
		 * We can't reclaim delayed extent from status tree because
		 * fiemap, bigallic, and seek_data/hole need to use it.
		 */
		अगर (ext4_es_is_delayed(es))
			जाओ next;
		अगर (ext4_es_is_referenced(es)) अणु
			ext4_es_clear_referenced(es);
			जाओ next;
		पूर्ण

		rb_erase(&es->rb_node, &tree->root);
		ext4_es_मुक्त_extent(inode, es);
		(*nr_shrunk)++;
next:
		अगर (!node)
			जाओ out_wrap;
		es = rb_entry(node, काष्ठा extent_status, rb_node);
	पूर्ण
	ei->i_es_shrink_lblk = es->es_lblk;
	वापस 1;
out_wrap:
	ei->i_es_shrink_lblk = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक es_reclaim_extents(काष्ठा ext4_inode_info *ei, पूर्णांक *nr_to_scan)
अणु
	काष्ठा inode *inode = &ei->vfs_inode;
	पूर्णांक nr_shrunk = 0;
	ext4_lblk_t start = ei->i_es_shrink_lblk;
	अटल DEFINE_RATELIMIT_STATE(_rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);

	अगर (ei->i_es_shk_nr == 0)
		वापस 0;

	अगर (ext4_test_inode_state(inode, EXT4_STATE_EXT_PRECACHED) &&
	    __ratelimit(&_rs))
		ext4_warning(inode->i_sb, "forced shrink of precached extents");

	अगर (!es_करो_reclaim_extents(ei, EXT_MAX_BLOCKS, nr_to_scan, &nr_shrunk) &&
	    start != 0)
		es_करो_reclaim_extents(ei, start - 1, nr_to_scan, &nr_shrunk);

	ei->i_es_tree.cache_es = शून्य;
	वापस nr_shrunk;
पूर्ण

/*
 * Called to support EXT4_IOC_CLEAR_ES_CACHE.  We can only हटाओ
 * discretionary entries from the extent status cache.  (Some entries
 * must be present क्रम proper operations.)
 */
व्योम ext4_clear_inode_es(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा extent_status *es;
	काष्ठा ext4_es_tree *tree;
	काष्ठा rb_node *node;

	ग_लिखो_lock(&ei->i_es_lock);
	tree = &EXT4_I(inode)->i_es_tree;
	tree->cache_es = शून्य;
	node = rb_first(&tree->root);
	जबतक (node) अणु
		es = rb_entry(node, काष्ठा extent_status, rb_node);
		node = rb_next(node);
		अगर (!ext4_es_is_delayed(es)) अणु
			rb_erase(&es->rb_node, &tree->root);
			ext4_es_मुक्त_extent(inode, es);
		पूर्ण
	पूर्ण
	ext4_clear_inode_state(inode, EXT4_STATE_EXT_PRECACHED);
	ग_लिखो_unlock(&ei->i_es_lock);
पूर्ण

#अगर_घोषित ES_DEBUG__
अटल व्योम ext4_prपूर्णांक_pending_tree(काष्ठा inode *inode)
अणु
	काष्ठा ext4_pending_tree *tree;
	काष्ठा rb_node *node;
	काष्ठा pending_reservation *pr;

	prपूर्णांकk(KERN_DEBUG "pending reservations for inode %lu:", inode->i_ino);
	tree = &EXT4_I(inode)->i_pending_tree;
	node = rb_first(&tree->root);
	जबतक (node) अणु
		pr = rb_entry(node, काष्ठा pending_reservation, rb_node);
		prपूर्णांकk(KERN_DEBUG " %u", pr->lclu);
		node = rb_next(node);
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "\n");
पूर्ण
#अन्यथा
#घोषणा ext4_prपूर्णांक_pending_tree(inode)
#पूर्ण_अगर

पूर्णांक __init ext4_init_pending(व्योम)
अणु
	ext4_pending_cachep = kmem_cache_create("ext4_pending_reservation",
					   माप(काष्ठा pending_reservation),
					   0, (SLAB_RECLAIM_ACCOUNT), शून्य);
	अगर (ext4_pending_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम ext4_निकास_pending(व्योम)
अणु
	kmem_cache_destroy(ext4_pending_cachep);
पूर्ण

व्योम ext4_init_pending_tree(काष्ठा ext4_pending_tree *tree)
अणु
	tree->root = RB_ROOT;
पूर्ण

/*
 * __get_pending - retrieve a poपूर्णांकer to a pending reservation
 *
 * @inode - file containing the pending cluster reservation
 * @lclu - logical cluster of पूर्णांकerest
 *
 * Returns a poपूर्णांकer to a pending reservation अगर it's a member of
 * the set, and शून्य अगर not.  Must be called holding i_es_lock.
 */
अटल काष्ठा pending_reservation *__get_pending(काष्ठा inode *inode,
						 ext4_lblk_t lclu)
अणु
	काष्ठा ext4_pending_tree *tree;
	काष्ठा rb_node *node;
	काष्ठा pending_reservation *pr = शून्य;

	tree = &EXT4_I(inode)->i_pending_tree;
	node = (&tree->root)->rb_node;

	जबतक (node) अणु
		pr = rb_entry(node, काष्ठा pending_reservation, rb_node);
		अगर (lclu < pr->lclu)
			node = node->rb_left;
		अन्यथा अगर (lclu > pr->lclu)
			node = node->rb_right;
		अन्यथा अगर (lclu == pr->lclu)
			वापस pr;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * __insert_pending - adds a pending cluster reservation to the set of
 *                    pending reservations
 *
 * @inode - file containing the cluster
 * @lblk - logical block in the cluster to be added
 *
 * Returns 0 on successful insertion and -ENOMEM on failure.  If the
 * pending reservation is alपढ़ोy in the set, वापसs successfully.
 */
अटल पूर्णांक __insert_pending(काष्ठा inode *inode, ext4_lblk_t lblk)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_pending_tree *tree = &EXT4_I(inode)->i_pending_tree;
	काष्ठा rb_node **p = &tree->root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा pending_reservation *pr;
	ext4_lblk_t lclu;
	पूर्णांक ret = 0;

	lclu = EXT4_B2C(sbi, lblk);
	/* search to find parent क्रम insertion */
	जबतक (*p) अणु
		parent = *p;
		pr = rb_entry(parent, काष्ठा pending_reservation, rb_node);

		अगर (lclu < pr->lclu) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (lclu > pr->lclu) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			/* pending reservation alपढ़ोy inserted */
			जाओ out;
		पूर्ण
	पूर्ण

	pr = kmem_cache_alloc(ext4_pending_cachep, GFP_ATOMIC);
	अगर (pr == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	pr->lclu = lclu;

	rb_link_node(&pr->rb_node, parent, p);
	rb_insert_color(&pr->rb_node, &tree->root);

out:
	वापस ret;
पूर्ण

/*
 * __हटाओ_pending - हटाओs a pending cluster reservation from the set
 *                    of pending reservations
 *
 * @inode - file containing the cluster
 * @lblk - logical block in the pending cluster reservation to be हटाओd
 *
 * Returns successfully अगर pending reservation is not a member of the set.
 */
अटल व्योम __हटाओ_pending(काष्ठा inode *inode, ext4_lblk_t lblk)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा pending_reservation *pr;
	काष्ठा ext4_pending_tree *tree;

	pr = __get_pending(inode, EXT4_B2C(sbi, lblk));
	अगर (pr != शून्य) अणु
		tree = &EXT4_I(inode)->i_pending_tree;
		rb_erase(&pr->rb_node, &tree->root);
		kmem_cache_मुक्त(ext4_pending_cachep, pr);
	पूर्ण
पूर्ण

/*
 * ext4_हटाओ_pending - हटाओs a pending cluster reservation from the set
 *                       of pending reservations
 *
 * @inode - file containing the cluster
 * @lblk - logical block in the pending cluster reservation to be हटाओd
 *
 * Locking क्रम बाह्यal use of __हटाओ_pending.
 */
व्योम ext4_हटाओ_pending(काष्ठा inode *inode, ext4_lblk_t lblk)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	ग_लिखो_lock(&ei->i_es_lock);
	__हटाओ_pending(inode, lblk);
	ग_लिखो_unlock(&ei->i_es_lock);
पूर्ण

/*
 * ext4_is_pending - determine whether a cluster has a pending reservation
 *                   on it
 *
 * @inode - file containing the cluster
 * @lblk - logical block in the cluster
 *
 * Returns true अगर there's a pending reservation क्रम the cluster in the
 * set of pending reservations, and false अगर not.
 */
bool ext4_is_pending(काष्ठा inode *inode, ext4_lblk_t lblk)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	bool ret;

	पढ़ो_lock(&ei->i_es_lock);
	ret = (bool)(__get_pending(inode, EXT4_B2C(sbi, lblk)) != शून्य);
	पढ़ो_unlock(&ei->i_es_lock);

	वापस ret;
पूर्ण

/*
 * ext4_es_insert_delayed_block - adds a delayed block to the extents status
 *                                tree, adding a pending reservation where
 *                                needed
 *
 * @inode - file containing the newly added block
 * @lblk - logical block to be added
 * @allocated - indicates whether a physical cluster has been allocated क्रम
 *              the logical cluster that contains the block
 *
 * Returns 0 on success, negative error code on failure.
 */
पूर्णांक ext4_es_insert_delayed_block(काष्ठा inode *inode, ext4_lblk_t lblk,
				 bool allocated)
अणु
	काष्ठा extent_status newes;
	पूर्णांक err = 0;

	अगर (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY)
		वापस 0;

	es_debug("add [%u/1) delayed to extent status tree of inode %lu\n",
		 lblk, inode->i_ino);

	newes.es_lblk = lblk;
	newes.es_len = 1;
	ext4_es_store_pblock_status(&newes, ~0, EXTENT_STATUS_DELAYED);
	trace_ext4_es_insert_delayed_block(inode, &newes, allocated);

	ext4_es_insert_extent_check(inode, &newes);

	ग_लिखो_lock(&EXT4_I(inode)->i_es_lock);

	err = __es_हटाओ_extent(inode, lblk, lblk, शून्य);
	अगर (err != 0)
		जाओ error;
retry:
	err = __es_insert_extent(inode, &newes);
	अगर (err == -ENOMEM && __es_shrink(EXT4_SB(inode->i_sb),
					  128, EXT4_I(inode)))
		जाओ retry;
	अगर (err != 0)
		जाओ error;

	अगर (allocated)
		__insert_pending(inode, lblk);

error:
	ग_लिखो_unlock(&EXT4_I(inode)->i_es_lock);

	ext4_es_prपूर्णांक_tree(inode);
	ext4_prपूर्णांक_pending_tree(inode);

	वापस err;
पूर्ण

/*
 * __es_delayed_clu - count number of clusters containing blocks that
 *                    are delayed only
 *
 * @inode - file containing block range
 * @start - logical block defining start of range
 * @end - logical block defining end of range
 *
 * Returns the number of clusters containing only delayed (not delayed
 * and unwritten) blocks in the range specअगरied by @start and @end.  Any
 * cluster or part of a cluster within the range and containing a delayed
 * and not unwritten block within the range is counted as a whole cluster.
 */
अटल अचिन्हित पूर्णांक __es_delayed_clu(काष्ठा inode *inode, ext4_lblk_t start,
				     ext4_lblk_t end)
अणु
	काष्ठा ext4_es_tree *tree = &EXT4_I(inode)->i_es_tree;
	काष्ठा extent_status *es;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	काष्ठा rb_node *node;
	ext4_lblk_t first_lclu, last_lclu;
	अचिन्हित दीर्घ दीर्घ last_counted_lclu;
	अचिन्हित पूर्णांक n = 0;

	/* guaranteed to be unequal to any ext4_lblk_t value */
	last_counted_lclu = ~0ULL;

	es = __es_tree_search(&tree->root, start);

	जबतक (es && (es->es_lblk <= end)) अणु
		अगर (ext4_es_is_delonly(es)) अणु
			अगर (es->es_lblk <= start)
				first_lclu = EXT4_B2C(sbi, start);
			अन्यथा
				first_lclu = EXT4_B2C(sbi, es->es_lblk);

			अगर (ext4_es_end(es) >= end)
				last_lclu = EXT4_B2C(sbi, end);
			अन्यथा
				last_lclu = EXT4_B2C(sbi, ext4_es_end(es));

			अगर (first_lclu == last_counted_lclu)
				n += last_lclu - first_lclu;
			अन्यथा
				n += last_lclu - first_lclu + 1;
			last_counted_lclu = last_lclu;
		पूर्ण
		node = rb_next(&es->rb_node);
		अगर (!node)
			अवरोध;
		es = rb_entry(node, काष्ठा extent_status, rb_node);
	पूर्ण

	वापस n;
पूर्ण

/*
 * ext4_es_delayed_clu - count number of clusters containing blocks that
 *                       are both delayed and unwritten
 *
 * @inode - file containing block range
 * @lblk - logical block defining start of range
 * @len - number of blocks in range
 *
 * Locking क्रम बाह्यal use of __es_delayed_clu().
 */
अचिन्हित पूर्णांक ext4_es_delayed_clu(काष्ठा inode *inode, ext4_lblk_t lblk,
				 ext4_lblk_t len)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	ext4_lblk_t end;
	अचिन्हित पूर्णांक n;

	अगर (len == 0)
		वापस 0;

	end = lblk + len - 1;
	WARN_ON(end < lblk);

	पढ़ो_lock(&ei->i_es_lock);

	n = __es_delayed_clu(inode, lblk, end);

	पढ़ो_unlock(&ei->i_es_lock);

	वापस n;
पूर्ण

/*
 * __revise_pending - makes, cancels, or leaves unchanged pending cluster
 *                    reservations क्रम a specअगरied block range depending
 *                    upon the presence or असलence of delayed blocks
 *                    outside the range within clusters at the ends of the
 *                    range
 *
 * @inode - file containing the range
 * @lblk - logical block defining the start of range
 * @len  - length of range in blocks
 *
 * Used after a newly allocated extent is added to the extents status tree.
 * Requires that the extents in the range have either written or unwritten
 * status.  Must be called जबतक holding i_es_lock.
 */
अटल व्योम __revise_pending(काष्ठा inode *inode, ext4_lblk_t lblk,
			     ext4_lblk_t len)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	ext4_lblk_t end = lblk + len - 1;
	ext4_lblk_t first, last;
	bool f_del = false, l_del = false;

	अगर (len == 0)
		वापस;

	/*
	 * Two हालs - block range within single cluster and block range
	 * spanning two or more clusters.  Note that a cluster beदीर्घing
	 * to a range starting and/or ending on a cluster boundary is treated
	 * as अगर it करोes not contain a delayed extent.  The new range may
	 * have allocated space क्रम previously delayed blocks out to the
	 * cluster boundary, requiring that any pre-existing pending
	 * reservation be canceled.  Because this code only looks at blocks
	 * outside the range, it should revise pending reservations
	 * correctly even अगर the extent represented by the range can't be
	 * inserted in the extents status tree due to ENOSPC.
	 */

	अगर (EXT4_B2C(sbi, lblk) == EXT4_B2C(sbi, end)) अणु
		first = EXT4_LBLK_CMASK(sbi, lblk);
		अगर (first != lblk)
			f_del = __es_scan_range(inode, &ext4_es_is_delonly,
						first, lblk - 1);
		अगर (f_del) अणु
			__insert_pending(inode, first);
		पूर्ण अन्यथा अणु
			last = EXT4_LBLK_CMASK(sbi, end) +
			       sbi->s_cluster_ratio - 1;
			अगर (last != end)
				l_del = __es_scan_range(inode,
							&ext4_es_is_delonly,
							end + 1, last);
			अगर (l_del)
				__insert_pending(inode, last);
			अन्यथा
				__हटाओ_pending(inode, last);
		पूर्ण
	पूर्ण अन्यथा अणु
		first = EXT4_LBLK_CMASK(sbi, lblk);
		अगर (first != lblk)
			f_del = __es_scan_range(inode, &ext4_es_is_delonly,
						first, lblk - 1);
		अगर (f_del)
			__insert_pending(inode, first);
		अन्यथा
			__हटाओ_pending(inode, first);

		last = EXT4_LBLK_CMASK(sbi, end) + sbi->s_cluster_ratio - 1;
		अगर (last != end)
			l_del = __es_scan_range(inode, &ext4_es_is_delonly,
						end + 1, last);
		अगर (l_del)
			__insert_pending(inode, last);
		अन्यथा
			__हटाओ_pending(inode, last);
	पूर्ण
पूर्ण
