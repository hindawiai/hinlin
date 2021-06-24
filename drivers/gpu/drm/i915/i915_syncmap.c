<शैली गुरु>
/*
 * Copyright तऊ 2017 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश <linux/slab.h>

#समावेश "i915_syncmap.h"

#समावेश "i915_gem.h" /* GEM_BUG_ON() */
#समावेश "i915_selftest.h"

#घोषणा SHIFT ilog2(KSYNCMAP)
#घोषणा MASK (KSYNCMAP - 1)

/*
 * काष्ठा i915_syncmap is a layer of a radixtree that maps a u64 fence
 * context id to the last u32 fence seqno रुकोed upon from that context.
 * Unlike lib/radixtree it uses a parent poपूर्णांकer that allows traversal back to
 * the root. This allows us to access the whole tree via a single poपूर्णांकer
 * to the most recently used layer. We expect fence contexts to be dense
 * and most reuse to be on the same i915_gem_context but on neighbouring
 * engines (i.e. on adjacent contexts) and reuse the same leaf, a very
 * effective lookup cache. If the new lookup is not on the same leaf, we
 * expect it to be on the neighbouring branch.
 *
 * A leaf holds an array of u32 seqno, and has height 0. The biपंचांगap field
 * allows us to store whether a particular seqno is valid (i.e. allows us
 * to distinguish unset from 0).
 *
 * A branch holds an array of layer poपूर्णांकers, and has height > 0, and always
 * has at least 2 layers (either branches or leaves) below it.
 *
 * For example,
 *	क्रम x in
 *	  0 1 2 0x10 0x11 0x200 0x201
 *	  0x500000 0x500001 0x503000 0x503001
 *	  0xE<<60:
 *		i915_syncmap_set(&sync, x, lower_32_bits(x));
 * will build a tree like:
 *	0xXXXXXXXXXXXXXXXX
 *	0-> 0x0000000000XXXXXX
 *	|   0-> 0x0000000000000XXX
 *	|   |   0-> 0x00000000000000XX
 *	|   |   |   0-> 0x000000000000000X 0:0, 1:1, 2:2
 *	|   |   |   1-> 0x000000000000001X 0:10, 1:11
 *	|   |   2-> 0x000000000000020X 0:200, 1:201
 *	|   5-> 0x000000000050XXXX
 *	|       0-> 0x000000000050000X 0:500000, 1:500001
 *	|       3-> 0x000000000050300X 0:503000, 1:503001
 *	e-> 0xe00000000000000X e:e
 */

काष्ठा i915_syncmap अणु
	u64 prefix;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक biपंचांगap;
	काष्ठा i915_syncmap *parent;
	/*
	 * Following this header is an array of either seqno or child poपूर्णांकers:
	 * जोड़ अणु
	 *	u32 seqno[KSYNCMAP];
	 *	काष्ठा i915_syncmap *child[KSYNCMAP];
	 * पूर्ण;
	 */
पूर्ण;

/**
 * i915_syncmap_init -- initialise the #i915_syncmap
 * @root: poपूर्णांकer to the #i915_syncmap
 */
व्योम i915_syncmap_init(काष्ठा i915_syncmap **root)
अणु
	BUILD_BUG_ON_NOT_POWER_OF_2(KSYNCMAP);
	BUILD_BUG_ON_NOT_POWER_OF_2(SHIFT);
	BUILD_BUG_ON(KSYNCMAP > BITS_PER_TYPE((*root)->biपंचांगap));
	*root = शून्य;
पूर्ण

अटल अंतरभूत u32 *__sync_seqno(काष्ठा i915_syncmap *p)
अणु
	GEM_BUG_ON(p->height);
	वापस (u32 *)(p + 1);
पूर्ण

अटल अंतरभूत काष्ठा i915_syncmap **__sync_child(काष्ठा i915_syncmap *p)
अणु
	GEM_BUG_ON(!p->height);
	वापस (काष्ठा i915_syncmap **)(p + 1);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
__sync_branch_idx(स्थिर काष्ठा i915_syncmap *p, u64 id)
अणु
	वापस (id >> p->height) & MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
__sync_leaf_idx(स्थिर काष्ठा i915_syncmap *p, u64 id)
अणु
	GEM_BUG_ON(p->height);
	वापस id & MASK;
पूर्ण

अटल अंतरभूत u64 __sync_branch_prefix(स्थिर काष्ठा i915_syncmap *p, u64 id)
अणु
	वापस id >> p->height >> SHIFT;
पूर्ण

अटल अंतरभूत u64 __sync_leaf_prefix(स्थिर काष्ठा i915_syncmap *p, u64 id)
अणु
	GEM_BUG_ON(p->height);
	वापस id >> SHIFT;
पूर्ण

अटल अंतरभूत bool seqno_later(u32 a, u32 b)
अणु
	वापस (s32)(a - b) >= 0;
पूर्ण

/**
 * i915_syncmap_is_later -- compare against the last know sync poपूर्णांक
 * @root: poपूर्णांकer to the #i915_syncmap
 * @id: the context id (other समयline) we are synchronising to
 * @seqno: the sequence number aदीर्घ the other समयline
 *
 * If we have alपढ़ोy synchronised this @root समयline with another (@id) then
 * we can omit any repeated or earlier synchronisation requests. If the two
 * समयlines are alपढ़ोy coupled, we can also omit the dependency between the
 * two as that is alपढ़ोy known via the समयline.
 *
 * Returns true अगर the two समयlines are alपढ़ोy synchronised wrt to @seqno,
 * false अगर not and the synchronisation must be emitted.
 */
bool i915_syncmap_is_later(काष्ठा i915_syncmap **root, u64 id, u32 seqno)
अणु
	काष्ठा i915_syncmap *p;
	अचिन्हित पूर्णांक idx;

	p = *root;
	अगर (!p)
		वापस false;

	अगर (likely(__sync_leaf_prefix(p, id) == p->prefix))
		जाओ found;

	/* First climb the tree back to a parent branch */
	करो अणु
		p = p->parent;
		अगर (!p)
			वापस false;

		अगर (__sync_branch_prefix(p, id) == p->prefix)
			अवरोध;
	पूर्ण जबतक (1);

	/* And then descend again until we find our leaf */
	करो अणु
		अगर (!p->height)
			अवरोध;

		p = __sync_child(p)[__sync_branch_idx(p, id)];
		अगर (!p)
			वापस false;

		अगर (__sync_branch_prefix(p, id) != p->prefix)
			वापस false;
	पूर्ण जबतक (1);

	*root = p;
found:
	idx = __sync_leaf_idx(p, id);
	अगर (!(p->biपंचांगap & BIT(idx)))
		वापस false;

	वापस seqno_later(__sync_seqno(p)[idx], seqno);
पूर्ण

अटल काष्ठा i915_syncmap *
__sync_alloc_leaf(काष्ठा i915_syncmap *parent, u64 id)
अणु
	काष्ठा i915_syncmap *p;

	p = kदो_स्मृति(माप(*p) + KSYNCMAP * माप(u32), GFP_KERNEL);
	अगर (unlikely(!p))
		वापस शून्य;

	p->parent = parent;
	p->height = 0;
	p->biपंचांगap = 0;
	p->prefix = __sync_leaf_prefix(p, id);
	वापस p;
पूर्ण

अटल अंतरभूत व्योम __sync_set_seqno(काष्ठा i915_syncmap *p, u64 id, u32 seqno)
अणु
	अचिन्हित पूर्णांक idx = __sync_leaf_idx(p, id);

	p->biपंचांगap |= BIT(idx);
	__sync_seqno(p)[idx] = seqno;
पूर्ण

अटल अंतरभूत व्योम __sync_set_child(काष्ठा i915_syncmap *p,
				    अचिन्हित पूर्णांक idx,
				    काष्ठा i915_syncmap *child)
अणु
	p->biपंचांगap |= BIT(idx);
	__sync_child(p)[idx] = child;
पूर्ण

अटल noअंतरभूत पूर्णांक __sync_set(काष्ठा i915_syncmap **root, u64 id, u32 seqno)
अणु
	काष्ठा i915_syncmap *p = *root;
	अचिन्हित पूर्णांक idx;

	अगर (!p) अणु
		p = __sync_alloc_leaf(शून्य, id);
		अगर (unlikely(!p))
			वापस -ENOMEM;

		जाओ found;
	पूर्ण

	/* Caller handled the likely cached हाल */
	GEM_BUG_ON(__sync_leaf_prefix(p, id) == p->prefix);

	/* Climb back up the tree until we find a common prefix */
	करो अणु
		अगर (!p->parent)
			अवरोध;

		p = p->parent;

		अगर (__sync_branch_prefix(p, id) == p->prefix)
			अवरोध;
	पूर्ण जबतक (1);

	/*
	 * No लघुcut, we have to descend the tree to find the right layer
	 * containing this fence.
	 *
	 * Each layer in the tree holds 16 (KSYNCMAP) poपूर्णांकers, either fences
	 * or lower layers. Leaf nodes (height = 0) contain the fences, all
	 * other nodes (height > 0) are पूर्णांकernal layers that poपूर्णांक to a lower
	 * node. Each पूर्णांकernal layer has at least 2 descendents.
	 *
	 * Starting at the top, we check whether the current prefix matches. If
	 * it करोesn't, we have gone past our target and need to insert a join
	 * पूर्णांकo the tree, and a new leaf node क्रम the target as a descendent
	 * of the join, as well as the original layer.
	 *
	 * The matching prefix means we are still following the right branch
	 * of the tree. If it has height 0, we have found our leaf and just
	 * need to replace the fence slot with ourselves. If the height is
	 * not zero, our slot contains the next layer in the tree (unless
	 * it is empty, in which हाल we can add ourselves as a new leaf).
	 * As descend the tree the prefix grows (and height decreases).
	 */
	करो अणु
		काष्ठा i915_syncmap *next;

		अगर (__sync_branch_prefix(p, id) != p->prefix) अणु
			अचिन्हित पूर्णांक above;

			/* Insert a join above the current layer */
			next = kzalloc(माप(*next) + KSYNCMAP * माप(next),
				       GFP_KERNEL);
			अगर (unlikely(!next))
				वापस -ENOMEM;

			/* Compute the height at which these two भागerge */
			above = fls64(__sync_branch_prefix(p, id) ^ p->prefix);
			above = round_up(above, SHIFT);
			next->height = above + p->height;
			next->prefix = __sync_branch_prefix(next, id);

			/* Insert the join पूर्णांकo the parent */
			अगर (p->parent) अणु
				idx = __sync_branch_idx(p->parent, id);
				__sync_child(p->parent)[idx] = next;
				GEM_BUG_ON(!(p->parent->biपंचांगap & BIT(idx)));
			पूर्ण
			next->parent = p->parent;

			/* Compute the idx of the other branch, not our id! */
			idx = p->prefix >> (above - SHIFT) & MASK;
			__sync_set_child(next, idx, p);
			p->parent = next;

			/* Ascend to the join */
			p = next;
		पूर्ण अन्यथा अणु
			अगर (!p->height)
				अवरोध;
		पूर्ण

		/* Descend पूर्णांकo the next layer */
		GEM_BUG_ON(!p->height);
		idx = __sync_branch_idx(p, id);
		next = __sync_child(p)[idx];
		अगर (!next) अणु
			next = __sync_alloc_leaf(p, id);
			अगर (unlikely(!next))
				वापस -ENOMEM;

			__sync_set_child(p, idx, next);
			p = next;
			अवरोध;
		पूर्ण

		p = next;
	पूर्ण जबतक (1);

found:
	GEM_BUG_ON(p->prefix != __sync_leaf_prefix(p, id));
	__sync_set_seqno(p, id, seqno);
	*root = p;
	वापस 0;
पूर्ण

/**
 * i915_syncmap_set -- mark the most recent syncpoपूर्णांक between contexts
 * @root: poपूर्णांकer to the #i915_syncmap
 * @id: the context id (other समयline) we have synchronised to
 * @seqno: the sequence number aदीर्घ the other समयline
 *
 * When we synchronise this @root समयline with another (@id), we also know
 * that we have synchronized with all previous seqno aदीर्घ that समयline. If
 * we then have a request to synchronise with the same seqno or older, we can
 * omit it, see i915_syncmap_is_later()
 *
 * Returns 0 on success, or a negative error code.
 */
पूर्णांक i915_syncmap_set(काष्ठा i915_syncmap **root, u64 id, u32 seqno)
अणु
	काष्ठा i915_syncmap *p = *root;

	/*
	 * We expect to be called in sequence following is_later(id), which
	 * should have preloaded the root क्रम us.
	 */
	अगर (likely(p && __sync_leaf_prefix(p, id) == p->prefix)) अणु
		__sync_set_seqno(p, id, seqno);
		वापस 0;
	पूर्ण

	वापस __sync_set(root, id, seqno);
पूर्ण

अटल व्योम __sync_मुक्त(काष्ठा i915_syncmap *p)
अणु
	अगर (p->height) अणु
		अचिन्हित पूर्णांक i;

		जबतक ((i = ffs(p->biपंचांगap))) अणु
			p->biपंचांगap &= ~0u << i;
			__sync_मुक्त(__sync_child(p)[i - 1]);
		पूर्ण
	पूर्ण

	kमुक्त(p);
पूर्ण

/**
 * i915_syncmap_मुक्त -- मुक्त all memory associated with the syncmap
 * @root: poपूर्णांकer to the #i915_syncmap
 *
 * Either when the समयline is to be मुक्तd and we no दीर्घer need the sync
 * poपूर्णांक tracking, or when the fences are all known to be संकेतed and the
 * sync poपूर्णांक tracking is redundant, we can मुक्त the #i915_syncmap to recover
 * its allocations.
 *
 * Will reinitialise the @root poपूर्णांकer so that the #i915_syncmap is पढ़ोy क्रम
 * reuse.
 */
व्योम i915_syncmap_मुक्त(काष्ठा i915_syncmap **root)
अणु
	काष्ठा i915_syncmap *p;

	p = *root;
	अगर (!p)
		वापस;

	जबतक (p->parent)
		p = p->parent;

	__sync_मुक्त(p);
	*root = शून्य;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_syncmap.c"
#पूर्ण_अगर
