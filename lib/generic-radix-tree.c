<शैली गुरु>

#समावेश <linux/export.h>
#समावेश <linux/generic-radix-tree.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kmemleak.h>

#घोषणा GENRADIX_ARY		(PAGE_SIZE / माप(काष्ठा genradix_node *))
#घोषणा GENRADIX_ARY_SHIFT	ilog2(GENRADIX_ARY)

काष्ठा genradix_node अणु
	जोड़ अणु
		/* Interior node: */
		काष्ठा genradix_node	*children[GENRADIX_ARY];

		/* Leaf: */
		u8			data[PAGE_SIZE];
	पूर्ण;
पूर्ण;

अटल अंतरभूत पूर्णांक genradix_depth_shअगरt(अचिन्हित depth)
अणु
	वापस PAGE_SHIFT + GENRADIX_ARY_SHIFT * depth;
पूर्ण

/*
 * Returns size (of data, in bytes) that a tree of a given depth holds:
 */
अटल अंतरभूत माप_प्रकार genradix_depth_size(अचिन्हित depth)
अणु
	वापस 1UL << genradix_depth_shअगरt(depth);
पूर्ण

/* depth that's needed क्रम a genradix that can address up to अच_दीर्घ_उच्च: */
#घोषणा GENRADIX_MAX_DEPTH	\
	DIV_ROUND_UP(BITS_PER_LONG - PAGE_SHIFT, GENRADIX_ARY_SHIFT)

#घोषणा GENRADIX_DEPTH_MASK				\
	((अचिन्हित दीर्घ) (roundup_घात_of_two(GENRADIX_MAX_DEPTH + 1) - 1))

अटल अंतरभूत अचिन्हित genradix_root_to_depth(काष्ठा genradix_root *r)
अणु
	वापस (अचिन्हित दीर्घ) r & GENRADIX_DEPTH_MASK;
पूर्ण

अटल अंतरभूत काष्ठा genradix_node *genradix_root_to_node(काष्ठा genradix_root *r)
अणु
	वापस (व्योम *) ((अचिन्हित दीर्घ) r & ~GENRADIX_DEPTH_MASK);
पूर्ण

/*
 * Returns poपूर्णांकer to the specअगरied byte @offset within @radix, or शून्य अगर not
 * allocated
 */
व्योम *__genradix_ptr(काष्ठा __genradix *radix, माप_प्रकार offset)
अणु
	काष्ठा genradix_root *r = READ_ONCE(radix->root);
	काष्ठा genradix_node *n = genradix_root_to_node(r);
	अचिन्हित level		= genradix_root_to_depth(r);

	अगर (ilog2(offset) >= genradix_depth_shअगरt(level))
		वापस शून्य;

	जबतक (1) अणु
		अगर (!n)
			वापस शून्य;
		अगर (!level)
			अवरोध;

		level--;

		n = n->children[offset >> genradix_depth_shअगरt(level)];
		offset &= genradix_depth_size(level) - 1;
	पूर्ण

	वापस &n->data[offset];
पूर्ण
EXPORT_SYMBOL(__genradix_ptr);

अटल अंतरभूत काष्ठा genradix_node *genradix_alloc_node(gfp_t gfp_mask)
अणु
	काष्ठा genradix_node *node;

	node = (काष्ठा genradix_node *)__get_मुक्त_page(gfp_mask|__GFP_ZERO);

	/*
	 * We're using pages (not slab allocations) directly क्रम kernel data
	 * काष्ठाures, so we need to explicitly inक्रमm kmemleak of them in order
	 * to aव्योम false positive memory leak reports.
	 */
	kmemleak_alloc(node, PAGE_SIZE, 1, gfp_mask);
	वापस node;
पूर्ण

अटल अंतरभूत व्योम genradix_मुक्त_node(काष्ठा genradix_node *node)
अणु
	kmemleak_मुक्त(node);
	मुक्त_page((अचिन्हित दीर्घ)node);
पूर्ण

/*
 * Returns poपूर्णांकer to the specअगरied byte @offset within @radix, allocating it अगर
 * necessary - newly allocated slots are always zeroed out:
 */
व्योम *__genradix_ptr_alloc(काष्ठा __genradix *radix, माप_प्रकार offset,
			   gfp_t gfp_mask)
अणु
	काष्ठा genradix_root *v = READ_ONCE(radix->root);
	काष्ठा genradix_node *n, *new_node = शून्य;
	अचिन्हित level;

	/* Increase tree depth अगर necessary: */
	जबतक (1) अणु
		काष्ठा genradix_root *r = v, *new_root;

		n	= genradix_root_to_node(r);
		level	= genradix_root_to_depth(r);

		अगर (n && ilog2(offset) < genradix_depth_shअगरt(level))
			अवरोध;

		अगर (!new_node) अणु
			new_node = genradix_alloc_node(gfp_mask);
			अगर (!new_node)
				वापस शून्य;
		पूर्ण

		new_node->children[0] = n;
		new_root = ((काष्ठा genradix_root *)
			    ((अचिन्हित दीर्घ) new_node | (n ? level + 1 : 0)));

		अगर ((v = cmpxchg_release(&radix->root, r, new_root)) == r) अणु
			v = new_root;
			new_node = शून्य;
		पूर्ण
	पूर्ण

	जबतक (level--) अणु
		काष्ठा genradix_node **p =
			&n->children[offset >> genradix_depth_shअगरt(level)];
		offset &= genradix_depth_size(level) - 1;

		n = READ_ONCE(*p);
		अगर (!n) अणु
			अगर (!new_node) अणु
				new_node = genradix_alloc_node(gfp_mask);
				अगर (!new_node)
					वापस शून्य;
			पूर्ण

			अगर (!(n = cmpxchg_release(p, शून्य, new_node)))
				swap(n, new_node);
		पूर्ण
	पूर्ण

	अगर (new_node)
		genradix_मुक्त_node(new_node);

	वापस &n->data[offset];
पूर्ण
EXPORT_SYMBOL(__genradix_ptr_alloc);

व्योम *__genradix_iter_peek(काष्ठा genradix_iter *iter,
			   काष्ठा __genradix *radix,
			   माप_प्रकार objs_per_page)
अणु
	काष्ठा genradix_root *r;
	काष्ठा genradix_node *n;
	अचिन्हित level, i;
restart:
	r = READ_ONCE(radix->root);
	अगर (!r)
		वापस शून्य;

	n	= genradix_root_to_node(r);
	level	= genradix_root_to_depth(r);

	अगर (ilog2(iter->offset) >= genradix_depth_shअगरt(level))
		वापस शून्य;

	जबतक (level) अणु
		level--;

		i = (iter->offset >> genradix_depth_shअगरt(level)) &
			(GENRADIX_ARY - 1);

		जबतक (!n->children[i]) अणु
			i++;
			iter->offset = round_करोwn(iter->offset +
					   genradix_depth_size(level),
					   genradix_depth_size(level));
			iter->pos = (iter->offset >> PAGE_SHIFT) *
				objs_per_page;
			अगर (i == GENRADIX_ARY)
				जाओ restart;
		पूर्ण

		n = n->children[i];
	पूर्ण

	वापस &n->data[iter->offset & (PAGE_SIZE - 1)];
पूर्ण
EXPORT_SYMBOL(__genradix_iter_peek);

अटल व्योम genradix_मुक्त_recurse(काष्ठा genradix_node *n, अचिन्हित level)
अणु
	अगर (level) अणु
		अचिन्हित i;

		क्रम (i = 0; i < GENRADIX_ARY; i++)
			अगर (n->children[i])
				genradix_मुक्त_recurse(n->children[i], level - 1);
	पूर्ण

	genradix_मुक्त_node(n);
पूर्ण

पूर्णांक __genradix_pपुनः_स्मृति(काष्ठा __genradix *radix, माप_प्रकार size,
			gfp_t gfp_mask)
अणु
	माप_प्रकार offset;

	क्रम (offset = 0; offset < size; offset += PAGE_SIZE)
		अगर (!__genradix_ptr_alloc(radix, offset, gfp_mask))
			वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(__genradix_pपुनः_स्मृति);

व्योम __genradix_मुक्त(काष्ठा __genradix *radix)
अणु
	काष्ठा genradix_root *r = xchg(&radix->root, शून्य);

	genradix_मुक्त_recurse(genradix_root_to_node(r),
			      genradix_root_to_depth(r));
पूर्ण
EXPORT_SYMBOL(__genradix_मुक्त);
