<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_NODEMASK_H
#घोषणा __LINUX_NODEMASK_H

/*
 * Nodemasks provide a biपंचांगap suitable क्रम representing the
 * set of Node's in a प्रणाली, one bit position per Node number.
 *
 * See detailed comments in the file linux/biपंचांगap.h describing the
 * data type on which these nodemasks are based.
 *
 * For details of nodemask_parse_user(), see biपंचांगap_parse_user() in
 * lib/biपंचांगap.c.  For details of nodelist_parse(), see biपंचांगap_parselist(),
 * also in biपंचांगap.c.  For details of node_remap(), see biपंचांगap_bitremap in
 * lib/biपंचांगap.c.  For details of nodes_remap(), see biपंचांगap_remap in
 * lib/biपंचांगap.c.  For details of nodes_onto(), see biपंचांगap_onto in
 * lib/biपंचांगap.c.  For details of nodes_fold(), see biपंचांगap_fold in
 * lib/biपंचांगap.c.
 *
 * The available nodemask operations are:
 *
 * व्योम node_set(node, mask)		turn on bit 'node' in mask
 * व्योम node_clear(node, mask)		turn off bit 'node' in mask
 * व्योम nodes_setall(mask)		set all bits
 * व्योम nodes_clear(mask)		clear all bits
 * पूर्णांक node_isset(node, mask)		true अगरf bit 'node' set in mask
 * पूर्णांक node_test_and_set(node, mask)	test and set bit 'node' in mask
 *
 * व्योम nodes_and(dst, src1, src2)	dst = src1 & src2  [पूर्णांकersection]
 * व्योम nodes_or(dst, src1, src2)	dst = src1 | src2  [जोड़]
 * व्योम nodes_xor(dst, src1, src2)	dst = src1 ^ src2
 * व्योम nodes_andnot(dst, src1, src2)	dst = src1 & ~src2
 * व्योम nodes_complement(dst, src)	dst = ~src
 *
 * पूर्णांक nodes_equal(mask1, mask2)	Does mask1 == mask2?
 * पूर्णांक nodes_पूर्णांकersects(mask1, mask2)	Do mask1 and mask2 पूर्णांकersect?
 * पूर्णांक nodes_subset(mask1, mask2)	Is mask1 a subset of mask2?
 * पूर्णांक nodes_empty(mask)		Is mask empty (no bits sets)?
 * पूर्णांक nodes_full(mask)			Is mask full (all bits sets)?
 * पूर्णांक nodes_weight(mask)		Hamming weight - number of set bits
 *
 * व्योम nodes_shअगरt_right(dst, src, n)	Shअगरt right
 * व्योम nodes_shअगरt_left(dst, src, n)	Shअगरt left
 *
 * पूर्णांक first_node(mask)			Number lowest set bit, or MAX_NUMNODES
 * पूर्णांक next_node(node, mask)		Next node past 'node', or MAX_NUMNODES
 * पूर्णांक next_node_in(node, mask)		Next node past 'node', or wrap to first,
 *					or MAX_NUMNODES
 * पूर्णांक first_unset_node(mask)		First node not set in mask, or 
 *					MAX_NUMNODES
 *
 * nodemask_t nodemask_of_node(node)	Return nodemask with bit 'node' set
 * NODE_MASK_ALL			Initializer - all bits set
 * NODE_MASK_NONE			Initializer - no bits set
 * अचिन्हित दीर्घ *nodes_addr(mask)	Array of अचिन्हित दीर्घ's in mask
 *
 * पूर्णांक nodemask_parse_user(ubuf, ulen, mask)	Parse ascii string as nodemask
 * पूर्णांक nodelist_parse(buf, map)		Parse ascii string as nodelist
 * पूर्णांक node_remap(oldbit, old, new)	newbit = map(old, new)(oldbit)
 * व्योम nodes_remap(dst, src, old, new)	*dst = map(old, new)(src)
 * व्योम nodes_onto(dst, orig, relmap)	*dst = orig relative to relmap
 * व्योम nodes_fold(dst, orig, sz)	dst bits = orig bits mod sz
 *
 * क्रम_each_node_mask(node, mask)	क्रम-loop node over mask
 *
 * पूर्णांक num_online_nodes()		Number of online Nodes
 * पूर्णांक num_possible_nodes()		Number of all possible Nodes
 *
 * पूर्णांक node_अक्रमom(mask)		Ranकरोm node with set bit in mask
 *
 * पूर्णांक node_online(node)		Is some node online?
 * पूर्णांक node_possible(node)		Is some node possible?
 *
 * node_set_online(node)		set bit 'node' in node_online_map
 * node_set_offline(node)		clear bit 'node' in node_online_map
 *
 * क्रम_each_node(node)			क्रम-loop node over node_possible_map
 * क्रम_each_online_node(node)		क्रम-loop node over node_online_map
 *
 * Subtlety:
 * 1) The 'type-checked' क्रमm of node_isset() causes gcc (3.3.2, anyway)
 *    to generate slightly worse code.  So use a simple one-line #घोषणा
 *    क्रम node_isset(), instead of wrapping an अंतरभूत inside a macro, the
 *    way we करो the other calls.
 *
 * NODEMASK_SCRATCH
 * When करोing above logical AND, OR, XOR, Remap operations the callers tend to
 * need temporary nodemask_t's on the stack. But अगर NODES_SHIFT is large,
 * nodemask_t's consume too much stack space.  NODEMASK_SCRATCH is a helper
 * क्रम such situations. See below and CPUMASK_ALLOC also.
 */

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/minmax.h>
#समावेश <linux/numa.h>

प्रकार काष्ठा अणु DECLARE_BITMAP(bits, MAX_NUMNODES); पूर्ण nodemask_t;
बाह्य nodemask_t _unused_nodemask_arg_;

/**
 * nodemask_pr_args - म_लिखो args to output a nodemask
 * @maskp: nodemask to be prपूर्णांकed
 *
 * Can be used to provide arguments क्रम '%*pb[l]' when prपूर्णांकing a nodemask.
 */
#घोषणा nodemask_pr_args(maskp)	__nodemask_pr_numnodes(maskp), \
				__nodemask_pr_bits(maskp)
अटल अंतरभूत अचिन्हित पूर्णांक __nodemask_pr_numnodes(स्थिर nodemask_t *m)
अणु
	वापस m ? MAX_NUMNODES : 0;
पूर्ण
अटल अंतरभूत स्थिर अचिन्हित दीर्घ *__nodemask_pr_bits(स्थिर nodemask_t *m)
अणु
	वापस m ? m->bits : शून्य;
पूर्ण

/*
 * The अंतरभूत keyword gives the compiler room to decide to अंतरभूत, or
 * not अंतरभूत a function as it sees best.  However, as these functions
 * are called in both __init and non-__init functions, अगर they are not
 * अंतरभूतd we will end up with a section mis-match error (of the type of
 * मुक्तable items not being मुक्तd).  So we must use __always_अंतरभूत here
 * to fix the problem.  If other functions in the future also end up in
 * this situation they will also need to be annotated as __always_अंतरभूत
 */
#घोषणा node_set(node, dst) __node_set((node), &(dst))
अटल __always_अंतरभूत व्योम __node_set(पूर्णांक node, अस्थिर nodemask_t *dstp)
अणु
	set_bit(node, dstp->bits);
पूर्ण

#घोषणा node_clear(node, dst) __node_clear((node), &(dst))
अटल अंतरभूत व्योम __node_clear(पूर्णांक node, अस्थिर nodemask_t *dstp)
अणु
	clear_bit(node, dstp->bits);
पूर्ण

#घोषणा nodes_setall(dst) __nodes_setall(&(dst), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_setall(nodemask_t *dstp, अचिन्हित पूर्णांक nbits)
अणु
	biपंचांगap_fill(dstp->bits, nbits);
पूर्ण

#घोषणा nodes_clear(dst) __nodes_clear(&(dst), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_clear(nodemask_t *dstp, अचिन्हित पूर्णांक nbits)
अणु
	biपंचांगap_zero(dstp->bits, nbits);
पूर्ण

/* No अटल अंतरभूत type checking - see Subtlety (1) above. */
#घोषणा node_isset(node, nodemask) test_bit((node), (nodemask).bits)

#घोषणा node_test_and_set(node, nodemask) \
			__node_test_and_set((node), &(nodemask))
अटल अंतरभूत पूर्णांक __node_test_and_set(पूर्णांक node, nodemask_t *addr)
अणु
	वापस test_and_set_bit(node, addr->bits);
पूर्ण

#घोषणा nodes_and(dst, src1, src2) \
			__nodes_and(&(dst), &(src1), &(src2), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_and(nodemask_t *dstp, स्थिर nodemask_t *src1p,
					स्थिर nodemask_t *src2p, अचिन्हित पूर्णांक nbits)
अणु
	biपंचांगap_and(dstp->bits, src1p->bits, src2p->bits, nbits);
पूर्ण

#घोषणा nodes_or(dst, src1, src2) \
			__nodes_or(&(dst), &(src1), &(src2), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_or(nodemask_t *dstp, स्थिर nodemask_t *src1p,
					स्थिर nodemask_t *src2p, अचिन्हित पूर्णांक nbits)
अणु
	biपंचांगap_or(dstp->bits, src1p->bits, src2p->bits, nbits);
पूर्ण

#घोषणा nodes_xor(dst, src1, src2) \
			__nodes_xor(&(dst), &(src1), &(src2), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_xor(nodemask_t *dstp, स्थिर nodemask_t *src1p,
					स्थिर nodemask_t *src2p, अचिन्हित पूर्णांक nbits)
अणु
	biपंचांगap_xor(dstp->bits, src1p->bits, src2p->bits, nbits);
पूर्ण

#घोषणा nodes_andnot(dst, src1, src2) \
			__nodes_andnot(&(dst), &(src1), &(src2), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_andnot(nodemask_t *dstp, स्थिर nodemask_t *src1p,
					स्थिर nodemask_t *src2p, अचिन्हित पूर्णांक nbits)
अणु
	biपंचांगap_andnot(dstp->bits, src1p->bits, src2p->bits, nbits);
पूर्ण

#घोषणा nodes_complement(dst, src) \
			__nodes_complement(&(dst), &(src), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_complement(nodemask_t *dstp,
					स्थिर nodemask_t *srcp, अचिन्हित पूर्णांक nbits)
अणु
	biपंचांगap_complement(dstp->bits, srcp->bits, nbits);
पूर्ण

#घोषणा nodes_equal(src1, src2) \
			__nodes_equal(&(src1), &(src2), MAX_NUMNODES)
अटल अंतरभूत पूर्णांक __nodes_equal(स्थिर nodemask_t *src1p,
					स्थिर nodemask_t *src2p, अचिन्हित पूर्णांक nbits)
अणु
	वापस biपंचांगap_equal(src1p->bits, src2p->bits, nbits);
पूर्ण

#घोषणा nodes_पूर्णांकersects(src1, src2) \
			__nodes_पूर्णांकersects(&(src1), &(src2), MAX_NUMNODES)
अटल अंतरभूत पूर्णांक __nodes_पूर्णांकersects(स्थिर nodemask_t *src1p,
					स्थिर nodemask_t *src2p, अचिन्हित पूर्णांक nbits)
अणु
	वापस biपंचांगap_पूर्णांकersects(src1p->bits, src2p->bits, nbits);
पूर्ण

#घोषणा nodes_subset(src1, src2) \
			__nodes_subset(&(src1), &(src2), MAX_NUMNODES)
अटल अंतरभूत पूर्णांक __nodes_subset(स्थिर nodemask_t *src1p,
					स्थिर nodemask_t *src2p, अचिन्हित पूर्णांक nbits)
अणु
	वापस biपंचांगap_subset(src1p->bits, src2p->bits, nbits);
पूर्ण

#घोषणा nodes_empty(src) __nodes_empty(&(src), MAX_NUMNODES)
अटल अंतरभूत पूर्णांक __nodes_empty(स्थिर nodemask_t *srcp, अचिन्हित पूर्णांक nbits)
अणु
	वापस biपंचांगap_empty(srcp->bits, nbits);
पूर्ण

#घोषणा nodes_full(nodemask) __nodes_full(&(nodemask), MAX_NUMNODES)
अटल अंतरभूत पूर्णांक __nodes_full(स्थिर nodemask_t *srcp, अचिन्हित पूर्णांक nbits)
अणु
	वापस biपंचांगap_full(srcp->bits, nbits);
पूर्ण

#घोषणा nodes_weight(nodemask) __nodes_weight(&(nodemask), MAX_NUMNODES)
अटल अंतरभूत पूर्णांक __nodes_weight(स्थिर nodemask_t *srcp, अचिन्हित पूर्णांक nbits)
अणु
	वापस biपंचांगap_weight(srcp->bits, nbits);
पूर्ण

#घोषणा nodes_shअगरt_right(dst, src, n) \
			__nodes_shअगरt_right(&(dst), &(src), (n), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_shअगरt_right(nodemask_t *dstp,
					स्थिर nodemask_t *srcp, पूर्णांक n, पूर्णांक nbits)
अणु
	biपंचांगap_shअगरt_right(dstp->bits, srcp->bits, n, nbits);
पूर्ण

#घोषणा nodes_shअगरt_left(dst, src, n) \
			__nodes_shअगरt_left(&(dst), &(src), (n), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_shअगरt_left(nodemask_t *dstp,
					स्थिर nodemask_t *srcp, पूर्णांक n, पूर्णांक nbits)
अणु
	biपंचांगap_shअगरt_left(dstp->bits, srcp->bits, n, nbits);
पूर्ण

/* FIXME: better would be to fix all architectures to never वापस
          > MAX_NUMNODES, then the silly min_ts could be dropped. */

#घोषणा first_node(src) __first_node(&(src))
अटल अंतरभूत पूर्णांक __first_node(स्थिर nodemask_t *srcp)
अणु
	वापस min_t(पूर्णांक, MAX_NUMNODES, find_first_bit(srcp->bits, MAX_NUMNODES));
पूर्ण

#घोषणा next_node(n, src) __next_node((n), &(src))
अटल अंतरभूत पूर्णांक __next_node(पूर्णांक n, स्थिर nodemask_t *srcp)
अणु
	वापस min_t(पूर्णांक,MAX_NUMNODES,find_next_bit(srcp->bits, MAX_NUMNODES, n+1));
पूर्ण

/*
 * Find the next present node in src, starting after node n, wrapping around to
 * the first node in src अगर needed.  Returns MAX_NUMNODES अगर src is empty.
 */
#घोषणा next_node_in(n, src) __next_node_in((n), &(src))
पूर्णांक __next_node_in(पूर्णांक node, स्थिर nodemask_t *srcp);

अटल अंतरभूत व्योम init_nodemask_of_node(nodemask_t *mask, पूर्णांक node)
अणु
	nodes_clear(*mask);
	node_set(node, *mask);
पूर्ण

#घोषणा nodemask_of_node(node)						\
(अणु									\
	typeof(_unused_nodemask_arg_) m;				\
	अगर (माप(m) == माप(अचिन्हित दीर्घ)) अणु			\
		m.bits[0] = 1UL << (node);				\
	पूर्ण अन्यथा अणु							\
		init_nodemask_of_node(&m, (node));			\
	पूर्ण								\
	m;								\
पूर्ण)

#घोषणा first_unset_node(mask) __first_unset_node(&(mask))
अटल अंतरभूत पूर्णांक __first_unset_node(स्थिर nodemask_t *maskp)
अणु
	वापस min_t(पूर्णांक,MAX_NUMNODES,
			find_first_zero_bit(maskp->bits, MAX_NUMNODES));
पूर्ण

#घोषणा NODE_MASK_LAST_WORD BITMAP_LAST_WORD_MASK(MAX_NUMNODES)

#अगर MAX_NUMNODES <= BITS_PER_LONG

#घोषणा NODE_MASK_ALL							\
((nodemask_t) अणु अणु							\
	[BITS_TO_LONGS(MAX_NUMNODES)-1] = NODE_MASK_LAST_WORD		\
पूर्ण पूर्ण)

#अन्यथा

#घोषणा NODE_MASK_ALL							\
((nodemask_t) अणु अणु							\
	[0 ... BITS_TO_LONGS(MAX_NUMNODES)-2] = ~0UL,			\
	[BITS_TO_LONGS(MAX_NUMNODES)-1] = NODE_MASK_LAST_WORD		\
पूर्ण पूर्ण)

#पूर्ण_अगर

#घोषणा NODE_MASK_NONE							\
((nodemask_t) अणु अणु							\
	[0 ... BITS_TO_LONGS(MAX_NUMNODES)-1] =  0UL			\
पूर्ण पूर्ण)

#घोषणा nodes_addr(src) ((src).bits)

#घोषणा nodemask_parse_user(ubuf, ulen, dst) \
		__nodemask_parse_user((ubuf), (ulen), &(dst), MAX_NUMNODES)
अटल अंतरभूत पूर्णांक __nodemask_parse_user(स्थिर अक्षर __user *buf, पूर्णांक len,
					nodemask_t *dstp, पूर्णांक nbits)
अणु
	वापस biपंचांगap_parse_user(buf, len, dstp->bits, nbits);
पूर्ण

#घोषणा nodelist_parse(buf, dst) __nodelist_parse((buf), &(dst), MAX_NUMNODES)
अटल अंतरभूत पूर्णांक __nodelist_parse(स्थिर अक्षर *buf, nodemask_t *dstp, पूर्णांक nbits)
अणु
	वापस biपंचांगap_parselist(buf, dstp->bits, nbits);
पूर्ण

#घोषणा node_remap(oldbit, old, new) \
		__node_remap((oldbit), &(old), &(new), MAX_NUMNODES)
अटल अंतरभूत पूर्णांक __node_remap(पूर्णांक oldbit,
		स्थिर nodemask_t *oldp, स्थिर nodemask_t *newp, पूर्णांक nbits)
अणु
	वापस biपंचांगap_bitremap(oldbit, oldp->bits, newp->bits, nbits);
पूर्ण

#घोषणा nodes_remap(dst, src, old, new) \
		__nodes_remap(&(dst), &(src), &(old), &(new), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_remap(nodemask_t *dstp, स्थिर nodemask_t *srcp,
		स्थिर nodemask_t *oldp, स्थिर nodemask_t *newp, पूर्णांक nbits)
अणु
	biपंचांगap_remap(dstp->bits, srcp->bits, oldp->bits, newp->bits, nbits);
पूर्ण

#घोषणा nodes_onto(dst, orig, relmap) \
		__nodes_onto(&(dst), &(orig), &(relmap), MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_onto(nodemask_t *dstp, स्थिर nodemask_t *origp,
		स्थिर nodemask_t *relmapp, पूर्णांक nbits)
अणु
	biपंचांगap_onto(dstp->bits, origp->bits, relmapp->bits, nbits);
पूर्ण

#घोषणा nodes_fold(dst, orig, sz) \
		__nodes_fold(&(dst), &(orig), sz, MAX_NUMNODES)
अटल अंतरभूत व्योम __nodes_fold(nodemask_t *dstp, स्थिर nodemask_t *origp,
		पूर्णांक sz, पूर्णांक nbits)
अणु
	biपंचांगap_fold(dstp->bits, origp->bits, sz, nbits);
पूर्ण

#अगर MAX_NUMNODES > 1
#घोषणा क्रम_each_node_mask(node, mask)			\
	क्रम ((node) = first_node(mask);			\
		(node) < MAX_NUMNODES;			\
		(node) = next_node((node), (mask)))
#अन्यथा /* MAX_NUMNODES == 1 */
#घोषणा क्रम_each_node_mask(node, mask)			\
	अगर (!nodes_empty(mask))				\
		क्रम ((node) = 0; (node) < 1; (node)++)
#पूर्ण_अगर /* MAX_NUMNODES */

/*
 * Biपंचांगasks that are kept क्रम all the nodes.
 */
क्रमागत node_states अणु
	N_POSSIBLE,		/* The node could become online at some poपूर्णांक */
	N_ONLINE,		/* The node is online */
	N_NORMAL_MEMORY,	/* The node has regular memory */
#अगर_घोषित CONFIG_HIGHMEM
	N_HIGH_MEMORY,		/* The node has regular or high memory */
#अन्यथा
	N_HIGH_MEMORY = N_NORMAL_MEMORY,
#पूर्ण_अगर
	N_MEMORY,		/* The node has memory(regular, high, movable) */
	N_CPU,		/* The node has one or more cpus */
	N_GENERIC_INITIATOR,	/* The node has one or more Generic Initiators */
	NR_NODE_STATES
पूर्ण;

/*
 * The following particular प्रणाली nodemasks and operations
 * on them manage all possible and online nodes.
 */

बाह्य nodemask_t node_states[NR_NODE_STATES];

#अगर MAX_NUMNODES > 1
अटल अंतरभूत पूर्णांक node_state(पूर्णांक node, क्रमागत node_states state)
अणु
	वापस node_isset(node, node_states[state]);
पूर्ण

अटल अंतरभूत व्योम node_set_state(पूर्णांक node, क्रमागत node_states state)
अणु
	__node_set(node, &node_states[state]);
पूर्ण

अटल अंतरभूत व्योम node_clear_state(पूर्णांक node, क्रमागत node_states state)
अणु
	__node_clear(node, &node_states[state]);
पूर्ण

अटल अंतरभूत पूर्णांक num_node_state(क्रमागत node_states state)
अणु
	वापस nodes_weight(node_states[state]);
पूर्ण

#घोषणा क्रम_each_node_state(__node, __state) \
	क्रम_each_node_mask((__node), node_states[__state])

#घोषणा first_online_node	first_node(node_states[N_ONLINE])
#घोषणा first_memory_node	first_node(node_states[N_MEMORY])
अटल अंतरभूत पूर्णांक next_online_node(पूर्णांक nid)
अणु
	वापस next_node(nid, node_states[N_ONLINE]);
पूर्ण
अटल अंतरभूत पूर्णांक next_memory_node(पूर्णांक nid)
अणु
	वापस next_node(nid, node_states[N_MEMORY]);
पूर्ण

बाह्य अचिन्हित पूर्णांक nr_node_ids;
बाह्य अचिन्हित पूर्णांक nr_online_nodes;

अटल अंतरभूत व्योम node_set_online(पूर्णांक nid)
अणु
	node_set_state(nid, N_ONLINE);
	nr_online_nodes = num_node_state(N_ONLINE);
पूर्ण

अटल अंतरभूत व्योम node_set_offline(पूर्णांक nid)
अणु
	node_clear_state(nid, N_ONLINE);
	nr_online_nodes = num_node_state(N_ONLINE);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक node_state(पूर्णांक node, क्रमागत node_states state)
अणु
	वापस node == 0;
पूर्ण

अटल अंतरभूत व्योम node_set_state(पूर्णांक node, क्रमागत node_states state)
अणु
पूर्ण

अटल अंतरभूत व्योम node_clear_state(पूर्णांक node, क्रमागत node_states state)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक num_node_state(क्रमागत node_states state)
अणु
	वापस 1;
पूर्ण

#घोषणा क्रम_each_node_state(node, __state) \
	क्रम ( (node) = 0; (node) == 0; (node) = 1)

#घोषणा first_online_node	0
#घोषणा first_memory_node	0
#घोषणा next_online_node(nid)	(MAX_NUMNODES)
#घोषणा nr_node_ids		1U
#घोषणा nr_online_nodes		1U

#घोषणा node_set_online(node)	   node_set_state((node), N_ONLINE)
#घोषणा node_set_offline(node)	   node_clear_state((node), N_ONLINE)

#पूर्ण_अगर

#अगर defined(CONFIG_NUMA) && (MAX_NUMNODES > 1)
बाह्य पूर्णांक node_अक्रमom(स्थिर nodemask_t *maskp);
#अन्यथा
अटल अंतरभूत पूर्णांक node_अक्रमom(स्थिर nodemask_t *mask)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा node_online_map 	node_states[N_ONLINE]
#घोषणा node_possible_map 	node_states[N_POSSIBLE]

#घोषणा num_online_nodes()	num_node_state(N_ONLINE)
#घोषणा num_possible_nodes()	num_node_state(N_POSSIBLE)
#घोषणा node_online(node)	node_state((node), N_ONLINE)
#घोषणा node_possible(node)	node_state((node), N_POSSIBLE)

#घोषणा क्रम_each_node(node)	   क्रम_each_node_state(node, N_POSSIBLE)
#घोषणा क्रम_each_online_node(node) क्रम_each_node_state(node, N_ONLINE)

/*
 * For nodemask scrach area.
 * NODEMASK_ALLOC(type, name) allocates an object with a specअगरied type and
 * name.
 */
#अगर NODES_SHIFT > 8 /* nodemask_t > 32 bytes */
#घोषणा NODEMASK_ALLOC(type, name, gfp_flags)	\
			type *name = kदो_स्मृति(माप(*name), gfp_flags)
#घोषणा NODEMASK_FREE(m)			kमुक्त(m)
#अन्यथा
#घोषणा NODEMASK_ALLOC(type, name, gfp_flags)	type _##name, *name = &_##name
#घोषणा NODEMASK_FREE(m)			करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

/* A example struture क्रम using NODEMASK_ALLOC, used in mempolicy. */
काष्ठा nodemask_scratch अणु
	nodemask_t	mask1;
	nodemask_t	mask2;
पूर्ण;

#घोषणा NODEMASK_SCRATCH(x)						\
			NODEMASK_ALLOC(काष्ठा nodemask_scratch, x,	\
					GFP_KERNEL | __GFP_NORETRY)
#घोषणा NODEMASK_SCRATCH_FREE(x)	NODEMASK_FREE(x)


#पूर्ण_अगर /* __LINUX_NODEMASK_H */
