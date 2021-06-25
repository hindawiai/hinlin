<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sparse bit array
 *
 * Copyright (C) 2018, Google LLC.
 * Copyright (C) 2018, Red Hat, Inc. (code style cleanup and fuzzing driver)
 *
 * This library provides functions to support a memory efficient bit array,
 * with an index size of 2^64.  A sparsebit array is allocated through
 * the use sparsebit_alloc() and मुक्त'd via sparsebit_मुक्त(),
 * such as in the following:
 *
 *   काष्ठा sparsebit *s;
 *   s = sparsebit_alloc();
 *   sparsebit_मुक्त(&s);
 *
 * The काष्ठा sparsebit type resolves करोwn to a काष्ठा sparsebit.
 * Note that, sparsebit_मुक्त() takes a poपूर्णांकer to the sparsebit
 * काष्ठाure.  This is so that sparsebit_मुक्त() is able to poison
 * the poपूर्णांकer (e.g. set it to शून्य) to the काष्ठा sparsebit beक्रमe
 * वापसing to the caller.
 *
 * Between the वापस of sparsebit_alloc() and the call of
 * sparsebit_मुक्त(), there are multiple query and modअगरying operations
 * that can be perक्रमmed on the allocated sparsebit array.  All of
 * these operations take as a parameter the value वापसed from
 * sparsebit_alloc() and most also take a bit index.  Frequently
 * used routines include:
 *
 *  ---- Query Operations
 *  sparsebit_is_set(s, idx)
 *  sparsebit_is_clear(s, idx)
 *  sparsebit_any_set(s)
 *  sparsebit_first_set(s)
 *  sparsebit_next_set(s, prev_idx)
 *
 *  ---- Modअगरying Operations
 *  sparsebit_set(s, idx)
 *  sparsebit_clear(s, idx)
 *  sparsebit_set_num(s, idx, num);
 *  sparsebit_clear_num(s, idx, num);
 *
 * A common operation, is to itterate over all the bits set in a test
 * sparsebit array.  This can be करोne via code with the following काष्ठाure:
 *
 *   sparsebit_idx_t idx;
 *   अगर (sparsebit_any_set(s)) अणु
 *     idx = sparsebit_first_set(s);
 *     करो अणु
 *       ...
 *       idx = sparsebit_next_set(s, idx);
 *     पूर्ण जबतक (idx != 0);
 *   पूर्ण
 *
 * The index of the first bit set needs to be obtained via
 * sparsebit_first_set(), because sparsebit_next_set(), needs
 * the index of the previously set.  The sparsebit_idx_t type is
 * अचिन्हित, so there is no previous index beक्रमe 0 that is available.
 * Also, the call to sparsebit_first_set() is not made unless there
 * is at least 1 bit in the array set.  This is because sparsebit_first_set()
 * पातs अगर sparsebit_first_set() is called with no bits set.
 * It is the callers responsibility to assure that the
 * sparsebit array has at least a single bit set beक्रमe calling
 * sparsebit_first_set().
 *
 * ==== Implementation Overview ====
 * For the most part the पूर्णांकernal implementation of sparsebit is
 * opaque to the caller.  One important implementation detail that the
 * caller may need to be aware of is the spatial complनिकासy of the
 * implementation.  This implementation of a sparsebit array is not
 * only sparse, in that it uses memory proportional to the number of bits
 * set.  It is also efficient in memory usage when most of the bits are
 * set.
 *
 * At a high-level the state of the bit settings are मुख्यtained through
 * the use of a binary-search tree, where each node contains at least
 * the following members:
 *
 *   प्रकार uपूर्णांक64_t sparsebit_idx_t;
 *   प्रकार uपूर्णांक64_t sparsebit_num_t;
 *
 *   sparsebit_idx_t idx;
 *   uपूर्णांक32_t mask;
 *   sparsebit_num_t num_after;
 *
 * The idx member contains the bit index of the first bit described by this
 * node, जबतक the mask member stores the setting of the first 32-bits.
 * The setting of the bit at idx + n, where 0 <= n < 32, is located in the
 * mask member at 1 << n.
 *
 * Nodes are sorted by idx and the bits described by two nodes will never
 * overlap. The idx member is always aligned to the mask size, i.e. a
 * multiple of 32.
 *
 * Beyond a typical implementation, the nodes in this implementation also
 * contains a member named num_after.  The num_after member holds the
 * number of bits immediately after the mask bits that are contiguously set.
 * The use of the num_after member allows this implementation to efficiently
 * represent हालs where most bits are set.  For example, the हाल of all
 * but the last two bits set, is represented by the following two nodes:
 *
 *   node 0 - idx: 0x0 mask: 0xffffffff num_after: 0xffffffffffffffc0
 *   node 1 - idx: 0xffffffffffffffe0 mask: 0x3fffffff num_after: 0
 *
 * ==== Invariants ====
 * This implementation usses the following invariants:
 *
 *   + Node are only used to represent bits that are set.
 *     Nodes with a mask of 0 and num_after of 0 are not allowed.
 *
 *   + Sum of bits set in all the nodes is equal to the value of
 *     the काष्ठा sparsebit_pvt num_set member.
 *
 *   + The setting of at least one bit is always described in a nodes
 *     mask (mask >= 1).
 *
 *   + A node with all mask bits set only occurs when the last bit
 *     described by the previous node is not equal to this nodes
 *     starting index - 1.  All such occurences of this condition are
 *     aव्योमed by moving the setting of the nodes mask bits पूर्णांकo
 *     the previous nodes num_after setting.
 *
 *   + Node starting index is evenly भागisible by the number of bits
 *     within a nodes mask member.
 *
 *   + Nodes never represent a range of bits that wrap around the
 *     highest supported index.
 *
 *      (idx + MASK_BITS + num_after - 1) <= ((sparsebit_idx_t) 0) - 1)
 *
 *     As a consequence of the above, the num_after member of a node
 *     will always be <=:
 *
 *       maximum_index - nodes_starting_index - number_of_mask_bits
 *
 *   + Nodes within the binary search tree are sorted based on each
 *     nodes starting index.
 *
 *   + The range of bits described by any two nodes करो not overlap.  The
 *     range of bits described by a single node is:
 *
 *       start: node->idx
 *       end (inclusive): node->idx + MASK_BITS + node->num_after - 1;
 *
 * Note, at बार these invariants are temporarily violated क्रम a
 * specअगरic portion of the code.  For example, when setting a mask
 * bit, there is a small delay between when the mask bit is set and the
 * value in the काष्ठा sparsebit_pvt num_set member is updated.  Other
 * temporary violations occur when node_split() is called with a specअगरied
 * index and assures that a node where its mask represents the bit
 * at the specअगरied index exists.  At बार to करो this node_split()
 * must split an existing node पूर्णांकo two nodes or create a node that
 * has no bits set.  Such temporary violations must be corrected beक्रमe
 * वापसing to the caller.  These corrections are typically perक्रमmed
 * by the local function node_reduce().
 */

#समावेश "test_util.h"
#समावेश "sparsebit.h"
#समावेश <सीमा.स>
#समावेश <निश्चित.स>

#घोषणा DUMP_LINE_MAX 100 /* Does not include indent amount */

प्रकार uपूर्णांक32_t mask_t;
#घोषणा MASK_BITS (माप(mask_t) * अक्षर_बिट)

काष्ठा node अणु
	काष्ठा node *parent;
	काष्ठा node *left;
	काष्ठा node *right;
	sparsebit_idx_t idx; /* index of least-signअगरicant bit in mask */
	sparsebit_num_t num_after; /* num contiguously set after mask */
	mask_t mask;
पूर्ण;

काष्ठा sparsebit अणु
	/*
	 * Poपूर्णांकs to root node of the binary search
	 * tree.  Equal to शून्य when no bits are set in
	 * the entire sparsebit array.
	 */
	काष्ठा node *root;

	/*
	 * A redundant count of the total number of bits set.  Used क्रम
	 * diagnostic purposes and to change the समय complनिकासy of
	 * sparsebit_num_set() from O(n) to O(1).
	 * Note: Due to overflow, a value of 0 means none or all set.
	 */
	sparsebit_num_t num_set;
पूर्ण;

/* Returns the number of set bits described by the settings
 * of the node poपूर्णांकed to by nodep.
 */
अटल sparsebit_num_t node_num_set(काष्ठा node *nodep)
अणु
	वापस nodep->num_after + __builtin_popcount(nodep->mask);
पूर्ण

/* Returns a poपूर्णांकer to the node that describes the
 * lowest bit index.
 */
अटल काष्ठा node *node_first(काष्ठा sparsebit *s)
अणु
	काष्ठा node *nodep;

	क्रम (nodep = s->root; nodep && nodep->left; nodep = nodep->left)
		;

	वापस nodep;
पूर्ण

/* Returns a poपूर्णांकer to the node that describes the
 * lowest bit index > the index of the node poपूर्णांकed to by np.
 * Returns शून्य अगर no node with a higher index exists.
 */
अटल काष्ठा node *node_next(काष्ठा sparsebit *s, काष्ठा node *np)
अणु
	काष्ठा node *nodep = np;

	/*
	 * If current node has a right child, next node is the left-most
	 * of the right child.
	 */
	अगर (nodep->right) अणु
		क्रम (nodep = nodep->right; nodep->left; nodep = nodep->left)
			;
		वापस nodep;
	पूर्ण

	/*
	 * No right child.  Go up until node is left child of a parent.
	 * That parent is then the next node.
	 */
	जबतक (nodep->parent && nodep == nodep->parent->right)
		nodep = nodep->parent;

	वापस nodep->parent;
पूर्ण

/* Searches क्रम and वापसs a poपूर्णांकer to the node that describes the
 * highest index < the index of the node poपूर्णांकed to by np.
 * Returns शून्य अगर no node with a lower index exists.
 */
अटल काष्ठा node *node_prev(काष्ठा sparsebit *s, काष्ठा node *np)
अणु
	काष्ठा node *nodep = np;

	/*
	 * If current node has a left child, next node is the right-most
	 * of the left child.
	 */
	अगर (nodep->left) अणु
		क्रम (nodep = nodep->left; nodep->right; nodep = nodep->right)
			;
		वापस (काष्ठा node *) nodep;
	पूर्ण

	/*
	 * No left child.  Go up until node is right child of a parent.
	 * That parent is then the next node.
	 */
	जबतक (nodep->parent && nodep == nodep->parent->left)
		nodep = nodep->parent;

	वापस (काष्ठा node *) nodep->parent;
पूर्ण


/* Allocates space to hold a copy of the node sub-tree poपूर्णांकed to by
 * subtree and duplicates the bit settings to the newly allocated nodes.
 * Returns the newly allocated copy of subtree.
 */
अटल काष्ठा node *node_copy_subtree(काष्ठा node *subtree)
अणु
	काष्ठा node *root;

	/* Duplicate the node at the root of the subtree */
	root = सुस्मृति(1, माप(*root));
	अगर (!root) अणु
		लिखो_त्रुटि("calloc");
		पात();
	पूर्ण

	root->idx = subtree->idx;
	root->mask = subtree->mask;
	root->num_after = subtree->num_after;

	/* As needed, recursively duplicate the left and right subtrees */
	अगर (subtree->left) अणु
		root->left = node_copy_subtree(subtree->left);
		root->left->parent = root;
	पूर्ण

	अगर (subtree->right) अणु
		root->right = node_copy_subtree(subtree->right);
		root->right->parent = root;
	पूर्ण

	वापस root;
पूर्ण

/* Searches क्रम and वापसs a poपूर्णांकer to the node that describes the setting
 * of the bit given by idx.  A node describes the setting of a bit अगर its
 * index is within the bits described by the mask bits or the number of
 * contiguous bits set after the mask.  Returns शून्य अगर there is no such node.
 */
अटल काष्ठा node *node_find(काष्ठा sparsebit *s, sparsebit_idx_t idx)
अणु
	काष्ठा node *nodep;

	/* Find the node that describes the setting of the bit at idx */
	क्रम (nodep = s->root; nodep;
	     nodep = nodep->idx > idx ? nodep->left : nodep->right) अणु
		अगर (idx >= nodep->idx &&
		    idx <= nodep->idx + MASK_BITS + nodep->num_after - 1)
			अवरोध;
	पूर्ण

	वापस nodep;
पूर्ण

/* Entry Requirements:
 *   + A node that describes the setting of idx is not alपढ़ोy present.
 *
 * Adds a new node to describe the setting of the bit at the index given
 * by idx.  Returns a poपूर्णांकer to the newly added node.
 *
 * TODO(lhuemill): Degenerate हालs causes the tree to get unbalanced.
 */
अटल काष्ठा node *node_add(काष्ठा sparsebit *s, sparsebit_idx_t idx)
अणु
	काष्ठा node *nodep, *parentp, *prev;

	/* Allocate and initialize the new node. */
	nodep = सुस्मृति(1, माप(*nodep));
	अगर (!nodep) अणु
		लिखो_त्रुटि("calloc");
		पात();
	पूर्ण

	nodep->idx = idx & -MASK_BITS;

	/* If no nodes, set it up as the root node. */
	अगर (!s->root) अणु
		s->root = nodep;
		वापस nodep;
	पूर्ण

	/*
	 * Find the parent where the new node should be attached
	 * and add the node there.
	 */
	parentp = s->root;
	जबतक (true) अणु
		अगर (idx < parentp->idx) अणु
			अगर (!parentp->left) अणु
				parentp->left = nodep;
				nodep->parent = parentp;
				अवरोध;
			पूर्ण
			parentp = parentp->left;
		पूर्ण अन्यथा अणु
			निश्चित(idx > parentp->idx + MASK_BITS + parentp->num_after - 1);
			अगर (!parentp->right) अणु
				parentp->right = nodep;
				nodep->parent = parentp;
				अवरोध;
			पूर्ण
			parentp = parentp->right;
		पूर्ण
	पूर्ण

	/*
	 * Does num_after bits of previous node overlap with the mask
	 * of the new node?  If so set the bits in the new nodes mask
	 * and reduce the previous nodes num_after.
	 */
	prev = node_prev(s, nodep);
	जबतक (prev && prev->idx + MASK_BITS + prev->num_after - 1 >= nodep->idx) अणु
		अचिन्हित पूर्णांक n1 = (prev->idx + MASK_BITS + prev->num_after - 1)
			- nodep->idx;
		निश्चित(prev->num_after > 0);
		निश्चित(n1 < MASK_BITS);
		निश्चित(!(nodep->mask & (1 << n1)));
		nodep->mask |= (1 << n1);
		prev->num_after--;
	पूर्ण

	वापस nodep;
पूर्ण

/* Returns whether all the bits in the sparsebit array are set.  */
bool sparsebit_all_set(काष्ठा sparsebit *s)
अणु
	/*
	 * If any nodes there must be at least one bit set.  Only हाल
	 * where a bit is set and total num set is 0, is when all bits
	 * are set.
	 */
	वापस s->root && s->num_set == 0;
पूर्ण

/* Clears all bits described by the node poपूर्णांकed to by nodep, then
 * हटाओs the node.
 */
अटल व्योम node_rm(काष्ठा sparsebit *s, काष्ठा node *nodep)
अणु
	काष्ठा node *पंचांगp;
	sparsebit_num_t num_set;

	num_set = node_num_set(nodep);
	निश्चित(s->num_set >= num_set || sparsebit_all_set(s));
	s->num_set -= node_num_set(nodep);

	/* Have both left and right child */
	अगर (nodep->left && nodep->right) अणु
		/*
		 * Move left children to the lefपंचांगost leaf node
		 * of the right child.
		 */
		क्रम (पंचांगp = nodep->right; पंचांगp->left; पंचांगp = पंचांगp->left)
			;
		पंचांगp->left = nodep->left;
		nodep->left = शून्य;
		पंचांगp->left->parent = पंचांगp;
	पूर्ण

	/* Left only child */
	अगर (nodep->left) अणु
		अगर (!nodep->parent) अणु
			s->root = nodep->left;
			nodep->left->parent = शून्य;
		पूर्ण अन्यथा अणु
			nodep->left->parent = nodep->parent;
			अगर (nodep == nodep->parent->left)
				nodep->parent->left = nodep->left;
			अन्यथा अणु
				निश्चित(nodep == nodep->parent->right);
				nodep->parent->right = nodep->left;
			पूर्ण
		पूर्ण

		nodep->parent = nodep->left = nodep->right = शून्य;
		मुक्त(nodep);

		वापस;
	पूर्ण


	/* Right only child */
	अगर (nodep->right) अणु
		अगर (!nodep->parent) अणु
			s->root = nodep->right;
			nodep->right->parent = शून्य;
		पूर्ण अन्यथा अणु
			nodep->right->parent = nodep->parent;
			अगर (nodep == nodep->parent->left)
				nodep->parent->left = nodep->right;
			अन्यथा अणु
				निश्चित(nodep == nodep->parent->right);
				nodep->parent->right = nodep->right;
			पूर्ण
		पूर्ण

		nodep->parent = nodep->left = nodep->right = शून्य;
		मुक्त(nodep);

		वापस;
	पूर्ण

	/* Leaf Node */
	अगर (!nodep->parent) अणु
		s->root = शून्य;
	पूर्ण अन्यथा अणु
		अगर (nodep->parent->left == nodep)
			nodep->parent->left = शून्य;
		अन्यथा अणु
			निश्चित(nodep == nodep->parent->right);
			nodep->parent->right = शून्य;
		पूर्ण
	पूर्ण

	nodep->parent = nodep->left = nodep->right = शून्य;
	मुक्त(nodep);

	वापस;
पूर्ण

/* Splits the node containing the bit at idx so that there is a node
 * that starts at the specअगरied index.  If no such node exists, a new
 * node at the specअगरied index is created.  Returns the new node.
 *
 * idx must start of a mask boundary.
 */
अटल काष्ठा node *node_split(काष्ठा sparsebit *s, sparsebit_idx_t idx)
अणु
	काष्ठा node *nodep1, *nodep2;
	sparsebit_idx_t offset;
	sparsebit_num_t orig_num_after;

	निश्चित(!(idx % MASK_BITS));

	/*
	 * Is there a node that describes the setting of idx?
	 * If not, add it.
	 */
	nodep1 = node_find(s, idx);
	अगर (!nodep1)
		वापस node_add(s, idx);

	/*
	 * All करोne अगर the starting index of the node is where the
	 * split should occur.
	 */
	अगर (nodep1->idx == idx)
		वापस nodep1;

	/*
	 * Split poपूर्णांक not at start of mask, so it must be part of
	 * bits described by num_after.
	 */

	/*
	 * Calculate offset within num_after क्रम where the split is
	 * to occur.
	 */
	offset = idx - (nodep1->idx + MASK_BITS);
	orig_num_after = nodep1->num_after;

	/*
	 * Add a new node to describe the bits starting at
	 * the split poपूर्णांक.
	 */
	nodep1->num_after = offset;
	nodep2 = node_add(s, idx);

	/* Move bits after the split poपूर्णांक पूर्णांकo the new node */
	nodep2->num_after = orig_num_after - offset;
	अगर (nodep2->num_after >= MASK_BITS) अणु
		nodep2->mask = ~(mask_t) 0;
		nodep2->num_after -= MASK_BITS;
	पूर्ण अन्यथा अणु
		nodep2->mask = (1 << nodep2->num_after) - 1;
		nodep2->num_after = 0;
	पूर्ण

	वापस nodep2;
पूर्ण

/* Iteratively reduces the node poपूर्णांकed to by nodep and its adjacent
 * nodes पूर्णांकo a more compact क्रमm.  For example, a node with a mask with
 * all bits set adjacent to a previous node, will get combined पूर्णांकo a
 * single node with an increased num_after setting.
 *
 * After each reduction, a further check is made to see अगर additional
 * reductions are possible with the new previous and next nodes.  Note,
 * a search क्रम a reduction is only करोne across the nodes nearest nodep
 * and those that became part of a reduction.  Reductions beyond nodep
 * and the adjacent nodes that are reduced are not discovered.  It is the
 * responsibility of the caller to pass a nodep that is within one node
 * of each possible reduction.
 *
 * This function करोes not fix the temporary violation of all invariants.
 * For example it करोes not fix the हाल where the bit settings described
 * by two or more nodes overlap.  Such a violation पूर्णांकroduces the potential
 * complication of a bit setting क्रम a specअगरic index having dअगरferent settings
 * in dअगरferent nodes.  This would then पूर्णांकroduce the further complication
 * of which node has the correct setting of the bit and thus such conditions
 * are not allowed.
 *
 * This function is deचिन्हित to fix invariant violations that are पूर्णांकroduced
 * by node_split() and by changes to the nodes mask or num_after members.
 * For example, when setting a bit within a nodes mask, the function that
 * sets the bit करोesn't have to worry about whether the setting of that
 * bit caused the mask to have leading only or trailing only bits set.
 * Instead, the function can call node_reduce(), with nodep equal to the
 * node address that it set a mask bit in, and node_reduce() will notice
 * the हालs of leading or trailing only bits and that there is an
 * adjacent node that the bit settings could be merged पूर्णांकo.
 *
 * This implementation specअगरically detects and corrects violation of the
 * following invariants:
 *
 *   + Node are only used to represent bits that are set.
 *     Nodes with a mask of 0 and num_after of 0 are not allowed.
 *
 *   + The setting of at least one bit is always described in a nodes
 *     mask (mask >= 1).
 *
 *   + A node with all mask bits set only occurs when the last bit
 *     described by the previous node is not equal to this nodes
 *     starting index - 1.  All such occurences of this condition are
 *     aव्योमed by moving the setting of the nodes mask bits पूर्णांकo
 *     the previous nodes num_after setting.
 */
अटल व्योम node_reduce(काष्ठा sparsebit *s, काष्ठा node *nodep)
अणु
	bool reduction_perक्रमmed;

	करो अणु
		reduction_perक्रमmed = false;
		काष्ठा node *prev, *next, *पंचांगp;

		/* 1) Potential reductions within the current node. */

		/* Nodes with all bits cleared may be हटाओd. */
		अगर (nodep->mask == 0 && nodep->num_after == 0) अणु
			/*
			 * About to हटाओ the node poपूर्णांकed to by
			 * nodep, which normally would cause a problem
			 * क्रम the next pass through the reduction loop,
			 * because the node at the starting poपूर्णांक no दीर्घer
			 * exists.  This potential problem is handled
			 * by first remembering the location of the next
			 * or previous nodes.  Doesn't matter which, because
			 * once the node at nodep is हटाओd, there will be
			 * no other nodes between prev and next.
			 *
			 * Note, the checks perक्रमmed on nodep against both
			 * both prev and next both check क्रम an adjacent
			 * node that can be reduced पूर्णांकo a single node.  As
			 * such, after removing the node at nodep, करोesn't
			 * matter whether the nodep क्रम the next pass
			 * through the loop is equal to the previous pass
			 * prev or next node.  Either way, on the next pass
			 * the one not selected will become either the
			 * prev or next node.
			 */
			पंचांगp = node_next(s, nodep);
			अगर (!पंचांगp)
				पंचांगp = node_prev(s, nodep);

			node_rm(s, nodep);
			nodep = शून्य;

			nodep = पंचांगp;
			reduction_perक्रमmed = true;
			जारी;
		पूर्ण

		/*
		 * When the mask is 0, can reduce the amount of num_after
		 * bits by moving the initial num_after bits पूर्णांकo the mask.
		 */
		अगर (nodep->mask == 0) अणु
			निश्चित(nodep->num_after != 0);
			निश्चित(nodep->idx + MASK_BITS > nodep->idx);

			nodep->idx += MASK_BITS;

			अगर (nodep->num_after >= MASK_BITS) अणु
				nodep->mask = ~0;
				nodep->num_after -= MASK_BITS;
			पूर्ण अन्यथा अणु
				nodep->mask = (1u << nodep->num_after) - 1;
				nodep->num_after = 0;
			पूर्ण

			reduction_perक्रमmed = true;
			जारी;
		पूर्ण

		/*
		 * 2) Potential reductions between the current and
		 * previous nodes.
		 */
		prev = node_prev(s, nodep);
		अगर (prev) अणु
			sparsebit_idx_t prev_highest_bit;

			/* Nodes with no bits set can be हटाओd. */
			अगर (prev->mask == 0 && prev->num_after == 0) अणु
				node_rm(s, prev);

				reduction_perक्रमmed = true;
				जारी;
			पूर्ण

			/*
			 * All mask bits set and previous node has
			 * adjacent index.
			 */
			अगर (nodep->mask + 1 == 0 &&
			    prev->idx + MASK_BITS == nodep->idx) अणु
				prev->num_after += MASK_BITS + nodep->num_after;
				nodep->mask = 0;
				nodep->num_after = 0;

				reduction_perक्रमmed = true;
				जारी;
			पूर्ण

			/*
			 * Is node adjacent to previous node and the node
			 * contains a single contiguous range of bits
			 * starting from the beginning of the mask?
			 */
			prev_highest_bit = prev->idx + MASK_BITS - 1 + prev->num_after;
			अगर (prev_highest_bit + 1 == nodep->idx &&
			    (nodep->mask | (nodep->mask >> 1)) == nodep->mask) अणु
				/*
				 * How many contiguous bits are there?
				 * Is equal to the total number of set
				 * bits, due to an earlier check that
				 * there is a single contiguous range of
				 * set bits.
				 */
				अचिन्हित पूर्णांक num_contiguous
					= __builtin_popcount(nodep->mask);
				निश्चित((num_contiguous > 0) &&
				       ((1ULL << num_contiguous) - 1) == nodep->mask);

				prev->num_after += num_contiguous;
				nodep->mask = 0;

				/*
				 * For predictable perक्रमmance, handle special
				 * हाल where all mask bits are set and there
				 * is a non-zero num_after setting.  This code
				 * is functionally correct without the following
				 * conditionalized statements, but without them
				 * the value of num_after is only reduced by
				 * the number of mask bits per pass.  There are
				 * हालs where num_after can be बंद to 2^64.
				 * Without this code it could take nearly
				 * (2^64) / 32 passes to perक्रमm the full
				 * reduction.
				 */
				अगर (num_contiguous == MASK_BITS) अणु
					prev->num_after += nodep->num_after;
					nodep->num_after = 0;
				पूर्ण

				reduction_perक्रमmed = true;
				जारी;
			पूर्ण
		पूर्ण

		/*
		 * 3) Potential reductions between the current and
		 * next nodes.
		 */
		next = node_next(s, nodep);
		अगर (next) अणु
			/* Nodes with no bits set can be हटाओd. */
			अगर (next->mask == 0 && next->num_after == 0) अणु
				node_rm(s, next);
				reduction_perक्रमmed = true;
				जारी;
			पूर्ण

			/*
			 * Is next node index adjacent to current node
			 * and has a mask with all bits set?
			 */
			अगर (next->idx == nodep->idx + MASK_BITS + nodep->num_after &&
			    next->mask == ~(mask_t) 0) अणु
				nodep->num_after += MASK_BITS;
				next->mask = 0;
				nodep->num_after += next->num_after;
				next->num_after = 0;

				node_rm(s, next);
				next = शून्य;

				reduction_perक्रमmed = true;
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (nodep && reduction_perक्रमmed);
पूर्ण

/* Returns whether the bit at the index given by idx, within the
 * sparsebit array is set or not.
 */
bool sparsebit_is_set(काष्ठा sparsebit *s, sparsebit_idx_t idx)
अणु
	काष्ठा node *nodep;

	/* Find the node that describes the setting of the bit at idx */
	क्रम (nodep = s->root; nodep;
	     nodep = nodep->idx > idx ? nodep->left : nodep->right)
		अगर (idx >= nodep->idx &&
		    idx <= nodep->idx + MASK_BITS + nodep->num_after - 1)
			जाओ have_node;

	वापस false;

have_node:
	/* Bit is set अगर it is any of the bits described by num_after */
	अगर (nodep->num_after && idx >= nodep->idx + MASK_BITS)
		वापस true;

	/* Is the corresponding mask bit set */
	निश्चित(idx >= nodep->idx && idx - nodep->idx < MASK_BITS);
	वापस !!(nodep->mask & (1 << (idx - nodep->idx)));
पूर्ण

/* Within the sparsebit array poपूर्णांकed to by s, sets the bit
 * at the index given by idx.
 */
अटल व्योम bit_set(काष्ठा sparsebit *s, sparsebit_idx_t idx)
अणु
	काष्ठा node *nodep;

	/* Skip bits that are alपढ़ोy set */
	अगर (sparsebit_is_set(s, idx))
		वापस;

	/*
	 * Get a node where the bit at idx is described by the mask.
	 * The node_split will also create a node, अगर there isn't
	 * alपढ़ोy a node that describes the setting of bit.
	 */
	nodep = node_split(s, idx & -MASK_BITS);

	/* Set the bit within the nodes mask */
	निश्चित(idx >= nodep->idx && idx <= nodep->idx + MASK_BITS - 1);
	निश्चित(!(nodep->mask & (1 << (idx - nodep->idx))));
	nodep->mask |= 1 << (idx - nodep->idx);
	s->num_set++;

	node_reduce(s, nodep);
पूर्ण

/* Within the sparsebit array poपूर्णांकed to by s, clears the bit
 * at the index given by idx.
 */
अटल व्योम bit_clear(काष्ठा sparsebit *s, sparsebit_idx_t idx)
अणु
	काष्ठा node *nodep;

	/* Skip bits that are alपढ़ोy cleared */
	अगर (!sparsebit_is_set(s, idx))
		वापस;

	/* Is there a node that describes the setting of this bit? */
	nodep = node_find(s, idx);
	अगर (!nodep)
		वापस;

	/*
	 * If a num_after bit, split the node, so that the bit is
	 * part of a node mask.
	 */
	अगर (idx >= nodep->idx + MASK_BITS)
		nodep = node_split(s, idx & -MASK_BITS);

	/*
	 * After node_split above, bit at idx should be within the mask.
	 * Clear that bit.
	 */
	निश्चित(idx >= nodep->idx && idx <= nodep->idx + MASK_BITS - 1);
	निश्चित(nodep->mask & (1 << (idx - nodep->idx)));
	nodep->mask &= ~(1 << (idx - nodep->idx));
	निश्चित(s->num_set > 0 || sparsebit_all_set(s));
	s->num_set--;

	node_reduce(s, nodep);
पूर्ण

/* Recursively dumps to the खाता stream given by stream the contents
 * of the sub-tree of nodes poपूर्णांकed to by nodep.  Each line of output
 * is prefixed by the number of spaces given by indent.  On each
 * recursion, the indent amount is increased by 2.  This causes nodes
 * at each level deeper पूर्णांकo the binary search tree to be displayed
 * with a greater indent.
 */
अटल व्योम dump_nodes(खाता *stream, काष्ठा node *nodep,
	अचिन्हित पूर्णांक indent)
अणु
	अक्षर *node_type;

	/* Dump contents of node */
	अगर (!nodep->parent)
		node_type = "root";
	अन्यथा अगर (nodep == nodep->parent->left)
		node_type = "left";
	अन्यथा अणु
		निश्चित(nodep == nodep->parent->right);
		node_type = "right";
	पूर्ण
	ख_लिखो(stream, "%*s---- %s nodep: %p\n", indent, "", node_type, nodep);
	ख_लिखो(stream, "%*s  parent: %p left: %p right: %p\n", indent, "",
		nodep->parent, nodep->left, nodep->right);
	ख_लिखो(stream, "%*s  idx: 0x%lx mask: 0x%x num_after: 0x%lx\n",
		indent, "", nodep->idx, nodep->mask, nodep->num_after);

	/* If present, dump contents of left child nodes */
	अगर (nodep->left)
		dump_nodes(stream, nodep->left, indent + 2);

	/* If present, dump contents of right child nodes */
	अगर (nodep->right)
		dump_nodes(stream, nodep->right, indent + 2);
पूर्ण

अटल अंतरभूत sparsebit_idx_t node_first_set(काष्ठा node *nodep, पूर्णांक start)
अणु
	mask_t leading = (mask_t)1 << start;
	पूर्णांक n1 = __builtin_ctz(nodep->mask & -leading);

	वापस nodep->idx + n1;
पूर्ण

अटल अंतरभूत sparsebit_idx_t node_first_clear(काष्ठा node *nodep, पूर्णांक start)
अणु
	mask_t leading = (mask_t)1 << start;
	पूर्णांक n1 = __builtin_ctz(~nodep->mask & -leading);

	वापस nodep->idx + n1;
पूर्ण

/* Dumps to the खाता stream specअगरied by stream, the implementation dependent
 * पूर्णांकernal state of s.  Each line of output is prefixed with the number
 * of spaces given by indent.  The output is completely implementation
 * dependent and subject to change.  Output from this function should only
 * be used क्रम diagnostic purposes.  For example, this function can be
 * used by test हालs after they detect an unexpected condition, as a means
 * to capture diagnostic inक्रमmation.
 */
अटल व्योम sparsebit_dump_पूर्णांकernal(खाता *stream, काष्ठा sparsebit *s,
	अचिन्हित पूर्णांक indent)
अणु
	/* Dump the contents of s */
	ख_लिखो(stream, "%*sroot: %p\n", indent, "", s->root);
	ख_लिखो(stream, "%*snum_set: 0x%lx\n", indent, "", s->num_set);

	अगर (s->root)
		dump_nodes(stream, s->root, indent);
पूर्ण

/* Allocates and वापसs a new sparsebit array. The initial state
 * of the newly allocated sparsebit array has all bits cleared.
 */
काष्ठा sparsebit *sparsebit_alloc(व्योम)
अणु
	काष्ठा sparsebit *s;

	/* Allocate top level काष्ठाure. */
	s = सुस्मृति(1, माप(*s));
	अगर (!s) अणु
		लिखो_त्रुटि("calloc");
		पात();
	पूर्ण

	वापस s;
पूर्ण

/* Frees the implementation dependent data क्रम the sparsebit array
 * poपूर्णांकed to by s and poisons the poपूर्णांकer to that data.
 */
व्योम sparsebit_मुक्त(काष्ठा sparsebit **sbitp)
अणु
	काष्ठा sparsebit *s = *sbitp;

	अगर (!s)
		वापस;

	sparsebit_clear_all(s);
	मुक्त(s);
	*sbitp = शून्य;
पूर्ण

/* Makes a copy of the sparsebit array given by s, to the sparsebit
 * array given by d.  Note, d must have alपढ़ोy been allocated via
 * sparsebit_alloc().  It can though alपढ़ोy have bits set, which
 * अगर dअगरferent from src will be cleared.
 */
व्योम sparsebit_copy(काष्ठा sparsebit *d, काष्ठा sparsebit *s)
अणु
	/* First clear any bits alपढ़ोy set in the destination */
	sparsebit_clear_all(d);

	अगर (s->root) अणु
		d->root = node_copy_subtree(s->root);
		d->num_set = s->num_set;
	पूर्ण
पूर्ण

/* Returns whether num consecutive bits starting at idx are all set.  */
bool sparsebit_is_set_num(काष्ठा sparsebit *s,
	sparsebit_idx_t idx, sparsebit_num_t num)
अणु
	sparsebit_idx_t next_cleared;

	निश्चित(num > 0);
	निश्चित(idx + num - 1 >= idx);

	/* With num > 0, the first bit must be set. */
	अगर (!sparsebit_is_set(s, idx))
		वापस false;

	/* Find the next cleared bit */
	next_cleared = sparsebit_next_clear(s, idx);

	/*
	 * If no cleared bits beyond idx, then there are at least num
	 * set bits. idx + num करोesn't wrap.  Otherwise check अगर
	 * there are enough set bits between idx and the next cleared bit.
	 */
	वापस next_cleared == 0 || next_cleared - idx >= num;
पूर्ण

/* Returns whether the bit at the index given by idx.  */
bool sparsebit_is_clear(काष्ठा sparsebit *s,
	sparsebit_idx_t idx)
अणु
	वापस !sparsebit_is_set(s, idx);
पूर्ण

/* Returns whether num consecutive bits starting at idx are all cleared.  */
bool sparsebit_is_clear_num(काष्ठा sparsebit *s,
	sparsebit_idx_t idx, sparsebit_num_t num)
अणु
	sparsebit_idx_t next_set;

	निश्चित(num > 0);
	निश्चित(idx + num - 1 >= idx);

	/* With num > 0, the first bit must be cleared. */
	अगर (!sparsebit_is_clear(s, idx))
		वापस false;

	/* Find the next set bit */
	next_set = sparsebit_next_set(s, idx);

	/*
	 * If no set bits beyond idx, then there are at least num
	 * cleared bits. idx + num करोesn't wrap.  Otherwise check अगर
	 * there are enough cleared bits between idx and the next set bit.
	 */
	वापस next_set == 0 || next_set - idx >= num;
पूर्ण

/* Returns the total number of bits set.  Note: 0 is also वापसed क्रम
 * the हाल of all bits set.  This is because with all bits set, there
 * is 1 additional bit set beyond what can be represented in the वापस
 * value.  Use sparsebit_any_set(), instead of sparsebit_num_set() > 0,
 * to determine अगर the sparsebit array has any bits set.
 */
sparsebit_num_t sparsebit_num_set(काष्ठा sparsebit *s)
अणु
	वापस s->num_set;
पूर्ण

/* Returns whether any bit is set in the sparsebit array.  */
bool sparsebit_any_set(काष्ठा sparsebit *s)
अणु
	/*
	 * Nodes only describe set bits.  If any nodes then there
	 * is at least 1 bit set.
	 */
	अगर (!s->root)
		वापस false;

	/*
	 * Every node should have a non-zero mask.  For now will
	 * just assure that the root node has a non-zero mask,
	 * which is a quick check that at least 1 bit is set.
	 */
	निश्चित(s->root->mask != 0);
	निश्चित(s->num_set > 0 ||
	       (s->root->num_after == ((sparsebit_num_t) 0) - MASK_BITS &&
		s->root->mask == ~(mask_t) 0));

	वापस true;
पूर्ण

/* Returns whether all the bits in the sparsebit array are cleared.  */
bool sparsebit_all_clear(काष्ठा sparsebit *s)
अणु
	वापस !sparsebit_any_set(s);
पूर्ण

/* Returns whether all the bits in the sparsebit array are set.  */
bool sparsebit_any_clear(काष्ठा sparsebit *s)
अणु
	वापस !sparsebit_all_set(s);
पूर्ण

/* Returns the index of the first set bit.  Abort अगर no bits are set.
 */
sparsebit_idx_t sparsebit_first_set(काष्ठा sparsebit *s)
अणु
	काष्ठा node *nodep;

	/* Validate at least 1 bit is set */
	निश्चित(sparsebit_any_set(s));

	nodep = node_first(s);
	वापस node_first_set(nodep, 0);
पूर्ण

/* Returns the index of the first cleared bit.  Abort अगर
 * no bits are cleared.
 */
sparsebit_idx_t sparsebit_first_clear(काष्ठा sparsebit *s)
अणु
	काष्ठा node *nodep1, *nodep2;

	/* Validate at least 1 bit is cleared. */
	निश्चित(sparsebit_any_clear(s));

	/* If no nodes or first node index > 0 then lowest cleared is 0 */
	nodep1 = node_first(s);
	अगर (!nodep1 || nodep1->idx > 0)
		वापस 0;

	/* Does the mask in the first node contain any cleared bits. */
	अगर (nodep1->mask != ~(mask_t) 0)
		वापस node_first_clear(nodep1, 0);

	/*
	 * All mask bits set in first node.  If there isn't a second node
	 * then the first cleared bit is the first bit after the bits
	 * described by the first node.
	 */
	nodep2 = node_next(s, nodep1);
	अगर (!nodep2) अणु
		/*
		 * No second node.  First cleared bit is first bit beyond
		 * bits described by first node.
		 */
		निश्चित(nodep1->mask == ~(mask_t) 0);
		निश्चित(nodep1->idx + MASK_BITS + nodep1->num_after != (sparsebit_idx_t) 0);
		वापस nodep1->idx + MASK_BITS + nodep1->num_after;
	पूर्ण

	/*
	 * There is a second node.
	 * If it is not adjacent to the first node, then there is a gap
	 * of cleared bits between the nodes, and the first cleared bit
	 * is the first bit within the gap.
	 */
	अगर (nodep1->idx + MASK_BITS + nodep1->num_after != nodep2->idx)
		वापस nodep1->idx + MASK_BITS + nodep1->num_after;

	/*
	 * Second node is adjacent to the first node.
	 * Because it is adjacent, its mask should be non-zero.  If all
	 * its mask bits are set, then with it being adjacent, it should
	 * have had the mask bits moved पूर्णांकo the num_after setting of the
	 * previous node.
	 */
	वापस node_first_clear(nodep2, 0);
पूर्ण

/* Returns index of next bit set within s after the index given by prev.
 * Returns 0 अगर there are no bits after prev that are set.
 */
sparsebit_idx_t sparsebit_next_set(काष्ठा sparsebit *s,
	sparsebit_idx_t prev)
अणु
	sparsebit_idx_t lowest_possible = prev + 1;
	sparsebit_idx_t start;
	काष्ठा node *nodep;

	/* A bit after the highest index can't be set. */
	अगर (lowest_possible == 0)
		वापस 0;

	/*
	 * Find the lefपंचांगost 'candidate' overlapping or to the right
	 * of lowest_possible.
	 */
	काष्ठा node *candidate = शून्य;

	/* True अगरf lowest_possible is within candidate */
	bool contains = false;

	/*
	 * Find node that describes setting of bit at lowest_possible.
	 * If such a node करोesn't exist, find the node with the lowest
	 * starting index that is > lowest_possible.
	 */
	क्रम (nodep = s->root; nodep;) अणु
		अगर ((nodep->idx + MASK_BITS + nodep->num_after - 1)
			>= lowest_possible) अणु
			candidate = nodep;
			अगर (candidate->idx <= lowest_possible) अणु
				contains = true;
				अवरोध;
			पूर्ण
			nodep = nodep->left;
		पूर्ण अन्यथा अणु
			nodep = nodep->right;
		पूर्ण
	पूर्ण
	अगर (!candidate)
		वापस 0;

	निश्चित(candidate->mask != 0);

	/* Does the candidate node describe the setting of lowest_possible? */
	अगर (!contains) अणु
		/*
		 * Candidate करोesn't describe setting of bit at lowest_possible.
		 * Candidate poपूर्णांकs to the first node with a starting index
		 * > lowest_possible.
		 */
		निश्चित(candidate->idx > lowest_possible);

		वापस node_first_set(candidate, 0);
	पूर्ण

	/*
	 * Candidate describes setting of bit at lowest_possible.
	 * Note: although the node describes the setting of the bit
	 * at lowest_possible, its possible that its setting and the
	 * setting of all latter bits described by this node are 0.
	 * For now, just handle the हालs where this node describes
	 * a bit at or after an index of lowest_possible that is set.
	 */
	start = lowest_possible - candidate->idx;

	अगर (start < MASK_BITS && candidate->mask >= (1 << start))
		वापस node_first_set(candidate, start);

	अगर (candidate->num_after) अणु
		sparsebit_idx_t first_num_after_idx = candidate->idx + MASK_BITS;

		वापस lowest_possible < first_num_after_idx
			? first_num_after_idx : lowest_possible;
	पूर्ण

	/*
	 * Although candidate node describes setting of bit at
	 * the index of lowest_possible, all bits at that index and
	 * latter that are described by candidate are cleared.  With
	 * this, the next bit is the first bit in the next node, अगर
	 * such a node exists.  If a next node करोesn't exist, then
	 * there is no next set bit.
	 */
	candidate = node_next(s, candidate);
	अगर (!candidate)
		वापस 0;

	वापस node_first_set(candidate, 0);
पूर्ण

/* Returns index of next bit cleared within s after the index given by prev.
 * Returns 0 अगर there are no bits after prev that are cleared.
 */
sparsebit_idx_t sparsebit_next_clear(काष्ठा sparsebit *s,
	sparsebit_idx_t prev)
अणु
	sparsebit_idx_t lowest_possible = prev + 1;
	sparsebit_idx_t idx;
	काष्ठा node *nodep1, *nodep2;

	/* A bit after the highest index can't be set. */
	अगर (lowest_possible == 0)
		वापस 0;

	/*
	 * Does a node describing the setting of lowest_possible exist?
	 * If not, the bit at lowest_possible is cleared.
	 */
	nodep1 = node_find(s, lowest_possible);
	अगर (!nodep1)
		वापस lowest_possible;

	/* Does a mask bit in node 1 describe the next cleared bit. */
	क्रम (idx = lowest_possible - nodep1->idx; idx < MASK_BITS; idx++)
		अगर (!(nodep1->mask & (1 << idx)))
			वापस nodep1->idx + idx;

	/*
	 * Next cleared bit is not described by node 1.  If there
	 * isn't a next node, then next cleared bit is described
	 * by bit after the bits described by the first node.
	 */
	nodep2 = node_next(s, nodep1);
	अगर (!nodep2)
		वापस nodep1->idx + MASK_BITS + nodep1->num_after;

	/*
	 * There is a second node.
	 * If it is not adjacent to the first node, then there is a gap
	 * of cleared bits between the nodes, and the next cleared bit
	 * is the first bit within the gap.
	 */
	अगर (nodep1->idx + MASK_BITS + nodep1->num_after != nodep2->idx)
		वापस nodep1->idx + MASK_BITS + nodep1->num_after;

	/*
	 * Second node is adjacent to the first node.
	 * Because it is adjacent, its mask should be non-zero.  If all
	 * its mask bits are set, then with it being adjacent, it should
	 * have had the mask bits moved पूर्णांकo the num_after setting of the
	 * previous node.
	 */
	वापस node_first_clear(nodep2, 0);
पूर्ण

/* Starting with the index 1 greater than the index given by start, finds
 * and वापसs the index of the first sequence of num consecutively set
 * bits.  Returns a value of 0 of no such sequence exists.
 */
sparsebit_idx_t sparsebit_next_set_num(काष्ठा sparsebit *s,
	sparsebit_idx_t start, sparsebit_num_t num)
अणु
	sparsebit_idx_t idx;

	निश्चित(num >= 1);

	क्रम (idx = sparsebit_next_set(s, start);
		idx != 0 && idx + num - 1 >= idx;
		idx = sparsebit_next_set(s, idx)) अणु
		निश्चित(sparsebit_is_set(s, idx));

		/*
		 * Does the sequence of bits starting at idx consist of
		 * num set bits?
		 */
		अगर (sparsebit_is_set_num(s, idx, num))
			वापस idx;

		/*
		 * Sequence of set bits at idx isn't large enough.
		 * Skip this entire sequence of set bits.
		 */
		idx = sparsebit_next_clear(s, idx);
		अगर (idx == 0)
			वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/* Starting with the index 1 greater than the index given by start, finds
 * and वापसs the index of the first sequence of num consecutively cleared
 * bits.  Returns a value of 0 of no such sequence exists.
 */
sparsebit_idx_t sparsebit_next_clear_num(काष्ठा sparsebit *s,
	sparsebit_idx_t start, sparsebit_num_t num)
अणु
	sparsebit_idx_t idx;

	निश्चित(num >= 1);

	क्रम (idx = sparsebit_next_clear(s, start);
		idx != 0 && idx + num - 1 >= idx;
		idx = sparsebit_next_clear(s, idx)) अणु
		निश्चित(sparsebit_is_clear(s, idx));

		/*
		 * Does the sequence of bits starting at idx consist of
		 * num cleared bits?
		 */
		अगर (sparsebit_is_clear_num(s, idx, num))
			वापस idx;

		/*
		 * Sequence of cleared bits at idx isn't large enough.
		 * Skip this entire sequence of cleared bits.
		 */
		idx = sparsebit_next_set(s, idx);
		अगर (idx == 0)
			वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

/* Sets the bits * in the inclusive range idx through idx + num - 1.  */
व्योम sparsebit_set_num(काष्ठा sparsebit *s,
	sparsebit_idx_t start, sparsebit_num_t num)
अणु
	काष्ठा node *nodep, *next;
	अचिन्हित पूर्णांक n1;
	sparsebit_idx_t idx;
	sparsebit_num_t n;
	sparsebit_idx_t middle_start, middle_end;

	निश्चित(num > 0);
	निश्चित(start + num - 1 >= start);

	/*
	 * Leading - bits beक्रमe first mask boundary.
	 *
	 * TODO(lhuemill): With some efक्रमt it may be possible to
	 *   replace the following loop with a sequential sequence
	 *   of statements.  High level sequence would be:
	 *
	 *     1. Use node_split() to क्रमce node that describes setting
	 *        of idx to be within the mask portion of a node.
	 *     2. Form mask of bits to be set.
	 *     3. Determine number of mask bits alपढ़ोy set in the node
	 *        and store in a local variable named num_alपढ़ोy_set.
	 *     4. Set the appropriate mask bits within the node.
	 *     5. Increment काष्ठा sparsebit_pvt num_set member
	 *        by the number of bits that were actually set.
	 *        Exclude from the counts bits that were alपढ़ोy set.
	 *     6. Beक्रमe वापसing to the caller, use node_reduce() to
	 *        handle the multiple corner हालs that this method
	 *        पूर्णांकroduces.
	 */
	क्रम (idx = start, n = num; n > 0 && idx % MASK_BITS != 0; idx++, n--)
		bit_set(s, idx);

	/* Middle - bits spanning one or more entire mask */
	middle_start = idx;
	middle_end = middle_start + (n & -MASK_BITS) - 1;
	अगर (n >= MASK_BITS) अणु
		nodep = node_split(s, middle_start);

		/*
		 * As needed, split just after end of middle bits.
		 * No split needed अगर end of middle bits is at highest
		 * supported bit index.
		 */
		अगर (middle_end + 1 > middle_end)
			(व्योम) node_split(s, middle_end + 1);

		/* Delete nodes that only describe bits within the middle. */
		क्रम (next = node_next(s, nodep);
			next && (next->idx < middle_end);
			next = node_next(s, nodep)) अणु
			निश्चित(next->idx + MASK_BITS + next->num_after - 1 <= middle_end);
			node_rm(s, next);
			next = शून्य;
		पूर्ण

		/* As needed set each of the mask bits */
		क्रम (n1 = 0; n1 < MASK_BITS; n1++) अणु
			अगर (!(nodep->mask & (1 << n1))) अणु
				nodep->mask |= 1 << n1;
				s->num_set++;
			पूर्ण
		पूर्ण

		s->num_set -= nodep->num_after;
		nodep->num_after = middle_end - middle_start + 1 - MASK_BITS;
		s->num_set += nodep->num_after;

		node_reduce(s, nodep);
	पूर्ण
	idx = middle_end + 1;
	n -= middle_end - middle_start + 1;

	/* Trailing - bits at and beyond last mask boundary */
	निश्चित(n < MASK_BITS);
	क्रम (; n > 0; idx++, n--)
		bit_set(s, idx);
पूर्ण

/* Clears the bits * in the inclusive range idx through idx + num - 1.  */
व्योम sparsebit_clear_num(काष्ठा sparsebit *s,
	sparsebit_idx_t start, sparsebit_num_t num)
अणु
	काष्ठा node *nodep, *next;
	अचिन्हित पूर्णांक n1;
	sparsebit_idx_t idx;
	sparsebit_num_t n;
	sparsebit_idx_t middle_start, middle_end;

	निश्चित(num > 0);
	निश्चित(start + num - 1 >= start);

	/* Leading - bits beक्रमe first mask boundary */
	क्रम (idx = start, n = num; n > 0 && idx % MASK_BITS != 0; idx++, n--)
		bit_clear(s, idx);

	/* Middle - bits spanning one or more entire mask */
	middle_start = idx;
	middle_end = middle_start + (n & -MASK_BITS) - 1;
	अगर (n >= MASK_BITS) अणु
		nodep = node_split(s, middle_start);

		/*
		 * As needed, split just after end of middle bits.
		 * No split needed अगर end of middle bits is at highest
		 * supported bit index.
		 */
		अगर (middle_end + 1 > middle_end)
			(व्योम) node_split(s, middle_end + 1);

		/* Delete nodes that only describe bits within the middle. */
		क्रम (next = node_next(s, nodep);
			next && (next->idx < middle_end);
			next = node_next(s, nodep)) अणु
			निश्चित(next->idx + MASK_BITS + next->num_after - 1 <= middle_end);
			node_rm(s, next);
			next = शून्य;
		पूर्ण

		/* As needed clear each of the mask bits */
		क्रम (n1 = 0; n1 < MASK_BITS; n1++) अणु
			अगर (nodep->mask & (1 << n1)) अणु
				nodep->mask &= ~(1 << n1);
				s->num_set--;
			पूर्ण
		पूर्ण

		/* Clear any bits described by num_after */
		s->num_set -= nodep->num_after;
		nodep->num_after = 0;

		/*
		 * Delete the node that describes the beginning of
		 * the middle bits and perक्रमm any allowed reductions
		 * with the nodes prev or next of nodep.
		 */
		node_reduce(s, nodep);
		nodep = शून्य;
	पूर्ण
	idx = middle_end + 1;
	n -= middle_end - middle_start + 1;

	/* Trailing - bits at and beyond last mask boundary */
	निश्चित(n < MASK_BITS);
	क्रम (; n > 0; idx++, n--)
		bit_clear(s, idx);
पूर्ण

/* Sets the bit at the index given by idx.  */
व्योम sparsebit_set(काष्ठा sparsebit *s, sparsebit_idx_t idx)
अणु
	sparsebit_set_num(s, idx, 1);
पूर्ण

/* Clears the bit at the index given by idx.  */
व्योम sparsebit_clear(काष्ठा sparsebit *s, sparsebit_idx_t idx)
अणु
	sparsebit_clear_num(s, idx, 1);
पूर्ण

/* Sets the bits in the entire addressable range of the sparsebit array.  */
व्योम sparsebit_set_all(काष्ठा sparsebit *s)
अणु
	sparsebit_set(s, 0);
	sparsebit_set_num(s, 1, ~(sparsebit_idx_t) 0);
	निश्चित(sparsebit_all_set(s));
पूर्ण

/* Clears the bits in the entire addressable range of the sparsebit array.  */
व्योम sparsebit_clear_all(काष्ठा sparsebit *s)
अणु
	sparsebit_clear(s, 0);
	sparsebit_clear_num(s, 1, ~(sparsebit_idx_t) 0);
	निश्चित(!sparsebit_any_set(s));
पूर्ण

अटल माप_प्रकार display_range(खाता *stream, sparsebit_idx_t low,
	sparsebit_idx_t high, bool prepend_comma_space)
अणु
	अक्षर *fmt_str;
	माप_प्रकार sz;

	/* Determine the म_लिखो क्रमmat string */
	अगर (low == high)
		fmt_str = prepend_comma_space ? ", 0x%lx" : "0x%lx";
	अन्यथा
		fmt_str = prepend_comma_space ? ", 0x%lx:0x%lx" : "0x%lx:0x%lx";

	/*
	 * When stream is शून्य, just determine the size of what would
	 * have been prपूर्णांकed, अन्यथा prपूर्णांक the range.
	 */
	अगर (!stream)
		sz = snम_लिखो(शून्य, 0, fmt_str, low, high);
	अन्यथा
		sz = ख_लिखो(stream, fmt_str, low, high);

	वापस sz;
पूर्ण


/* Dumps to the खाता stream given by stream, the bit settings
 * of s.  Each line of output is prefixed with the number of
 * spaces given by indent.  The length of each line is implementation
 * dependent and करोes not depend on the indent amount.  The following
 * is an example output of a sparsebit array that has bits:
 *
 *   0x5, 0x8, 0xa:0xe, 0x12
 *
 * This corresponds to a sparsebit whose bits 5, 8, 10, 11, 12, 13, 14, 18
 * are set.  Note that a ':', instead of a '-' is used to specअगरy a range of
 * contiguous bits.  This is करोne because '-' is used to specअगरy command-line
 * options, and someबार ranges are specअगरied as command-line arguments.
 */
व्योम sparsebit_dump(खाता *stream, काष्ठा sparsebit *s,
	अचिन्हित पूर्णांक indent)
अणु
	माप_प्रकार current_line_len = 0;
	माप_प्रकार sz;
	काष्ठा node *nodep;

	अगर (!sparsebit_any_set(s))
		वापस;

	/* Display initial indent */
	ख_लिखो(stream, "%*s", indent, "");

	/* For each node */
	क्रम (nodep = node_first(s); nodep; nodep = node_next(s, nodep)) अणु
		अचिन्हित पूर्णांक n1;
		sparsebit_idx_t low, high;

		/* For each group of bits in the mask */
		क्रम (n1 = 0; n1 < MASK_BITS; n1++) अणु
			अगर (nodep->mask & (1 << n1)) अणु
				low = high = nodep->idx + n1;

				क्रम (; n1 < MASK_BITS; n1++) अणु
					अगर (nodep->mask & (1 << n1))
						high = nodep->idx + n1;
					अन्यथा
						अवरोध;
				पूर्ण

				अगर ((n1 == MASK_BITS) && nodep->num_after)
					high += nodep->num_after;

				/*
				 * How much room will it take to display
				 * this range.
				 */
				sz = display_range(शून्य, low, high,
					current_line_len != 0);

				/*
				 * If there is not enough room, display
				 * a newline plus the indent of the next
				 * line.
				 */
				अगर (current_line_len + sz > DUMP_LINE_MAX) अणु
					ख_माला_दो("\n", stream);
					ख_लिखो(stream, "%*s", indent, "");
					current_line_len = 0;
				पूर्ण

				/* Display the range */
				sz = display_range(stream, low, high,
					current_line_len != 0);
				current_line_len += sz;
			पूर्ण
		पूर्ण

		/*
		 * If num_after and most signअगरicant-bit of mask is not
		 * set, then still need to display a range क्रम the bits
		 * described by num_after.
		 */
		अगर (!(nodep->mask & (1 << (MASK_BITS - 1))) && nodep->num_after) अणु
			low = nodep->idx + MASK_BITS;
			high = nodep->idx + MASK_BITS + nodep->num_after - 1;

			/*
			 * How much room will it take to display
			 * this range.
			 */
			sz = display_range(शून्य, low, high,
				current_line_len != 0);

			/*
			 * If there is not enough room, display
			 * a newline plus the indent of the next
			 * line.
			 */
			अगर (current_line_len + sz > DUMP_LINE_MAX) अणु
				ख_माला_दो("\n", stream);
				ख_लिखो(stream, "%*s", indent, "");
				current_line_len = 0;
			पूर्ण

			/* Display the range */
			sz = display_range(stream, low, high,
				current_line_len != 0);
			current_line_len += sz;
		पूर्ण
	पूर्ण
	ख_माला_दो("\n", stream);
पूर्ण

/* Validates the पूर्णांकernal state of the sparsebit array given by
 * s.  On error, diagnostic inक्रमmation is prपूर्णांकed to मानक_त्रुटि and
 * पात is called.
 */
व्योम sparsebit_validate_पूर्णांकernal(काष्ठा sparsebit *s)
अणु
	bool error_detected = false;
	काष्ठा node *nodep, *prev = शून्य;
	sparsebit_num_t total_bits_set = 0;
	अचिन्हित पूर्णांक n1;

	/* For each node */
	क्रम (nodep = node_first(s); nodep;
		prev = nodep, nodep = node_next(s, nodep)) अणु

		/*
		 * Increase total bits set by the number of bits set
		 * in this node.
		 */
		क्रम (n1 = 0; n1 < MASK_BITS; n1++)
			अगर (nodep->mask & (1 << n1))
				total_bits_set++;

		total_bits_set += nodep->num_after;

		/*
		 * Arbitrary choice as to whether a mask of 0 is allowed
		 * or not.  For diagnostic purposes it is beneficial to
		 * have only one valid means to represent a set of bits.
		 * To support this an arbitrary choice has been made
		 * to not allow a mask of zero.
		 */
		अगर (nodep->mask == 0) अणु
			ख_लिखो(मानक_त्रुटि, "Node mask of zero, "
				"nodep: %p nodep->mask: 0x%x",
				nodep, nodep->mask);
			error_detected = true;
			अवरोध;
		पूर्ण

		/*
		 * Validate num_after is not greater than the max index
		 * - the number of mask bits.  The num_after member
		 * uses 0-based indexing and thus has no value that
		 * represents all bits set.  This limitation is handled
		 * by requiring a non-zero mask.  With a non-zero mask,
		 * MASK_BITS worth of bits are described by the mask,
		 * which makes the largest needed num_after equal to:
		 *
		 *    (~(sparsebit_num_t) 0) - MASK_BITS + 1
		 */
		अगर (nodep->num_after
			> (~(sparsebit_num_t) 0) - MASK_BITS + 1) अणु
			ख_लिखो(मानक_त्रुटि, "num_after too large, "
				"nodep: %p nodep->num_after: 0x%lx",
				nodep, nodep->num_after);
			error_detected = true;
			अवरोध;
		पूर्ण

		/* Validate node index is भागisible by the mask size */
		अगर (nodep->idx % MASK_BITS) अणु
			ख_लिखो(मानक_त्रुटि, "Node index not divisible by "
				"mask size,\n"
				"  nodep: %p nodep->idx: 0x%lx "
				"MASK_BITS: %lu\n",
				nodep, nodep->idx, MASK_BITS);
			error_detected = true;
			अवरोध;
		पूर्ण

		/*
		 * Validate bits described by node करोn't wrap beyond the
		 * highest supported index.
		 */
		अगर ((nodep->idx + MASK_BITS + nodep->num_after - 1) < nodep->idx) अणु
			ख_लिखो(मानक_त्रुटि, "Bits described by node wrap "
				"beyond highest supported index,\n"
				"  nodep: %p nodep->idx: 0x%lx\n"
				"  MASK_BITS: %lu nodep->num_after: 0x%lx",
				nodep, nodep->idx, MASK_BITS, nodep->num_after);
			error_detected = true;
			अवरोध;
		पूर्ण

		/* Check parent poपूर्णांकers. */
		अगर (nodep->left) अणु
			अगर (nodep->left->parent != nodep) अणु
				ख_लिखो(मानक_त्रुटि, "Left child parent pointer "
					"doesn't point to this node,\n"
					"  nodep: %p nodep->left: %p "
					"nodep->left->parent: %p",
					nodep, nodep->left,
					nodep->left->parent);
				error_detected = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (nodep->right) अणु
			अगर (nodep->right->parent != nodep) अणु
				ख_लिखो(मानक_त्रुटि, "Right child parent pointer "
					"doesn't point to this node,\n"
					"  nodep: %p nodep->right: %p "
					"nodep->right->parent: %p",
					nodep, nodep->right,
					nodep->right->parent);
				error_detected = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!nodep->parent) अणु
			अगर (s->root != nodep) अणु
				ख_लिखो(मानक_त्रुटि, "Unexpected root node, "
					"s->root: %p nodep: %p",
					s->root, nodep);
				error_detected = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (prev) अणु
			/*
			 * Is index of previous node beक्रमe index of
			 * current node?
			 */
			अगर (prev->idx >= nodep->idx) अणु
				ख_लिखो(मानक_त्रुटि, "Previous node index "
					">= current node index,\n"
					"  prev: %p prev->idx: 0x%lx\n"
					"  nodep: %p nodep->idx: 0x%lx",
					prev, prev->idx, nodep, nodep->idx);
				error_detected = true;
				अवरोध;
			पूर्ण

			/*
			 * Nodes occur in asscending order, based on each
			 * nodes starting index.
			 */
			अगर ((prev->idx + MASK_BITS + prev->num_after - 1)
				>= nodep->idx) अणु
				ख_लिखो(मानक_त्रुटि, "Previous node bit range "
					"overlap with current node bit range,\n"
					"  prev: %p prev->idx: 0x%lx "
					"prev->num_after: 0x%lx\n"
					"  nodep: %p nodep->idx: 0x%lx "
					"nodep->num_after: 0x%lx\n"
					"  MASK_BITS: %lu",
					prev, prev->idx, prev->num_after,
					nodep, nodep->idx, nodep->num_after,
					MASK_BITS);
				error_detected = true;
				अवरोध;
			पूर्ण

			/*
			 * When the node has all mask bits set, it shouldn't
			 * be adjacent to the last bit described by the
			 * previous node.
			 */
			अगर (nodep->mask == ~(mask_t) 0 &&
			    prev->idx + MASK_BITS + prev->num_after == nodep->idx) अणु
				ख_लिखो(मानक_त्रुटि, "Current node has mask with "
					"all bits set and is adjacent to the "
					"previous node,\n"
					"  prev: %p prev->idx: 0x%lx "
					"prev->num_after: 0x%lx\n"
					"  nodep: %p nodep->idx: 0x%lx "
					"nodep->num_after: 0x%lx\n"
					"  MASK_BITS: %lu",
					prev, prev->idx, prev->num_after,
					nodep, nodep->idx, nodep->num_after,
					MASK_BITS);

				error_detected = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!error_detected) अणु
		/*
		 * Is sum of bits set in each node equal to the count
		 * of total bits set.
		 */
		अगर (s->num_set != total_bits_set) अणु
			ख_लिखो(मानक_त्रुटि, "Number of bits set missmatch,\n"
				"  s->num_set: 0x%lx total_bits_set: 0x%lx",
				s->num_set, total_bits_set);

			error_detected = true;
		पूर्ण
	पूर्ण

	अगर (error_detected) अणु
		ख_माला_दो("  dump_internal:\n", मानक_त्रुटि);
		sparsebit_dump_पूर्णांकernal(मानक_त्रुटि, s, 4);
		पात();
	पूर्ण
पूर्ण


#अगर_घोषित FUZZ
/* A simple but effective fuzzing driver.  Look क्रम bugs with the help
 * of some invariants and of a trivial representation of sparsebit.
 * Just use 512 bytes of /dev/zero and /dev/uअक्रमom as inमाला_दो, and let
 * afl-fuzz करो the magic. :)
 */

#समावेश <मानककोष.स>

काष्ठा range अणु
	sparsebit_idx_t first, last;
	bool set;
पूर्ण;

काष्ठा sparsebit *s;
काष्ठा range ranges[1000];
पूर्णांक num_ranges;

अटल bool get_value(sparsebit_idx_t idx)
अणु
	पूर्णांक i;

	क्रम (i = num_ranges; --i >= 0; )
		अगर (ranges[i].first <= idx && idx <= ranges[i].last)
			वापस ranges[i].set;

	वापस false;
पूर्ण

अटल व्योम operate(पूर्णांक code, sparsebit_idx_t first, sparsebit_idx_t last)
अणु
	sparsebit_num_t num;
	sparsebit_idx_t next;

	अगर (first < last) अणु
		num = last - first + 1;
	पूर्ण अन्यथा अणु
		num = first - last + 1;
		first = last;
		last = first + num - 1;
	पूर्ण

	चयन (code) अणु
	हाल 0:
		sparsebit_set(s, first);
		निश्चित(sparsebit_is_set(s, first));
		निश्चित(!sparsebit_is_clear(s, first));
		निश्चित(sparsebit_any_set(s));
		निश्चित(!sparsebit_all_clear(s));
		अगर (get_value(first))
			वापस;
		अगर (num_ranges == 1000)
			निकास(0);
		ranges[num_ranges++] = (काष्ठा range)
			अणु .first = first, .last = first, .set = true पूर्ण;
		अवरोध;
	हाल 1:
		sparsebit_clear(s, first);
		निश्चित(!sparsebit_is_set(s, first));
		निश्चित(sparsebit_is_clear(s, first));
		निश्चित(sparsebit_any_clear(s));
		निश्चित(!sparsebit_all_set(s));
		अगर (!get_value(first))
			वापस;
		अगर (num_ranges == 1000)
			निकास(0);
		ranges[num_ranges++] = (काष्ठा range)
			अणु .first = first, .last = first, .set = false पूर्ण;
		अवरोध;
	हाल 2:
		निश्चित(sparsebit_is_set(s, first) == get_value(first));
		निश्चित(sparsebit_is_clear(s, first) == !get_value(first));
		अवरोध;
	हाल 3:
		अगर (sparsebit_any_set(s))
			निश्चित(get_value(sparsebit_first_set(s)));
		अगर (sparsebit_any_clear(s))
			निश्चित(!get_value(sparsebit_first_clear(s)));
		sparsebit_set_all(s);
		निश्चित(!sparsebit_any_clear(s));
		निश्चित(sparsebit_all_set(s));
		num_ranges = 0;
		ranges[num_ranges++] = (काष्ठा range)
			अणु .first = 0, .last = ~(sparsebit_idx_t)0, .set = true पूर्ण;
		अवरोध;
	हाल 4:
		अगर (sparsebit_any_set(s))
			निश्चित(get_value(sparsebit_first_set(s)));
		अगर (sparsebit_any_clear(s))
			निश्चित(!get_value(sparsebit_first_clear(s)));
		sparsebit_clear_all(s);
		निश्चित(!sparsebit_any_set(s));
		निश्चित(sparsebit_all_clear(s));
		num_ranges = 0;
		अवरोध;
	हाल 5:
		next = sparsebit_next_set(s, first);
		निश्चित(next == 0 || next > first);
		निश्चित(next == 0 || get_value(next));
		अवरोध;
	हाल 6:
		next = sparsebit_next_clear(s, first);
		निश्चित(next == 0 || next > first);
		निश्चित(next == 0 || !get_value(next));
		अवरोध;
	हाल 7:
		next = sparsebit_next_clear(s, first);
		अगर (sparsebit_is_set_num(s, first, num)) अणु
			निश्चित(next == 0 || next > last);
			अगर (first)
				next = sparsebit_next_set(s, first - 1);
			अन्यथा अगर (sparsebit_any_set(s))
				next = sparsebit_first_set(s);
			अन्यथा
				वापस;
			निश्चित(next == first);
		पूर्ण अन्यथा अणु
			निश्चित(sparsebit_is_clear(s, first) || next <= last);
		पूर्ण
		अवरोध;
	हाल 8:
		next = sparsebit_next_set(s, first);
		अगर (sparsebit_is_clear_num(s, first, num)) अणु
			निश्चित(next == 0 || next > last);
			अगर (first)
				next = sparsebit_next_clear(s, first - 1);
			अन्यथा अगर (sparsebit_any_clear(s))
				next = sparsebit_first_clear(s);
			अन्यथा
				वापस;
			निश्चित(next == first);
		पूर्ण अन्यथा अणु
			निश्चित(sparsebit_is_set(s, first) || next <= last);
		पूर्ण
		अवरोध;
	हाल 9:
		sparsebit_set_num(s, first, num);
		निश्चित(sparsebit_is_set_num(s, first, num));
		निश्चित(!sparsebit_is_clear_num(s, first, num));
		निश्चित(sparsebit_any_set(s));
		निश्चित(!sparsebit_all_clear(s));
		अगर (num_ranges == 1000)
			निकास(0);
		ranges[num_ranges++] = (काष्ठा range)
			अणु .first = first, .last = last, .set = true पूर्ण;
		अवरोध;
	हाल 10:
		sparsebit_clear_num(s, first, num);
		निश्चित(!sparsebit_is_set_num(s, first, num));
		निश्चित(sparsebit_is_clear_num(s, first, num));
		निश्चित(sparsebit_any_clear(s));
		निश्चित(!sparsebit_all_set(s));
		अगर (num_ranges == 1000)
			निकास(0);
		ranges[num_ranges++] = (काष्ठा range)
			अणु .first = first, .last = last, .set = false पूर्ण;
		अवरोध;
	हाल 11:
		sparsebit_validate_पूर्णांकernal(s);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अचिन्हित अक्षर get8(व्योम)
अणु
	पूर्णांक ch;

	ch = अक्षर_लो();
	अगर (ch == खातापूर्ण)
		निकास(0);
	वापस ch;
पूर्ण

uपूर्णांक64_t get64(व्योम)
अणु
	uपूर्णांक64_t x;

	x = get8();
	x = (x << 8) | get8();
	x = (x << 8) | get8();
	x = (x << 8) | get8();
	x = (x << 8) | get8();
	x = (x << 8) | get8();
	x = (x << 8) | get8();
	वापस (x << 8) | get8();
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	s = sparsebit_alloc();
	क्रम (;;) अणु
		uपूर्णांक8_t op = get8() & 0xf;
		uपूर्णांक64_t first = get64();
		uपूर्णांक64_t last = get64();

		operate(op, first, last);
	पूर्ण
पूर्ण
#पूर्ण_अगर
