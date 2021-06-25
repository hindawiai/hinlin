<शैली गुरु>
#अगर_अघोषित _LINUX_GENERIC_RADIX_TREE_H
#घोषणा _LINUX_GENERIC_RADIX_TREE_H

/**
 * DOC: Generic radix trees/sparse arrays
 *
 * Very simple and minimalistic, supporting arbitrary size entries up to
 * PAGE_SIZE.
 *
 * A genradix is defined with the type it will store, like so:
 *
 * अटल GENRADIX(काष्ठा foo) foo_genradix;
 *
 * The मुख्य operations are:
 *
 * - genradix_init(radix) - initialize an empty genradix
 *
 * - genradix_मुक्त(radix) - मुक्त all memory owned by the genradix and
 *   reinitialize it
 *
 * - genradix_ptr(radix, idx) - माला_लो a poपूर्णांकer to the entry at idx, वापसing
 *   शून्य अगर that entry करोes not exist
 *
 * - genradix_ptr_alloc(radix, idx, gfp) - माला_लो a poपूर्णांकer to an entry,
 *   allocating it अगर necessary
 *
 * - genradix_क्रम_each(radix, iter, p) - iterate over each entry in a genradix
 *
 * The radix tree allocates one page of entries at a समय, so entries may exist
 * that were never explicitly allocated - they will be initialized to all
 * zeroes.
 *
 * Internally, a genradix is just a radix tree of pages, and indexing works in
 * terms of byte offsets. The wrappers in this header file use माप on the
 * type the radix contains to calculate a byte offset from the index - see
 * __idx_to_offset.
 */

#समावेश <यंत्र/page.h>
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>

काष्ठा genradix_root;

काष्ठा __genradix अणु
	काष्ठा genradix_root		*root;
पूर्ण;

/*
 * NOTE: currently, माप(_type) must not be larger than PAGE_SIZE:
 */

#घोषणा __GENRADIX_INITIALIZER					\
	अणु							\
		.tree = अणु					\
			.root = शून्य,				\
		पूर्ण						\
	पूर्ण

/*
 * We use a 0 size array to stash the type we're storing without taking any
 * space at runसमय - then the various accessor macros can use typeof() to get
 * to it क्रम casts/माप - we also क्रमce the alignment so that storing a type
 * with a ridiculous alignment करोesn't blow up the alignment or size of the
 * genradix.
 */

#घोषणा GENRADIX(_type)						\
काष्ठा अणु							\
	काष्ठा __genradix	tree;				\
	_type			type[0] __aligned(1);		\
पूर्ण

#घोषणा DEFINE_GENRADIX(_name, _type)				\
	GENRADIX(_type) _name = __GENRADIX_INITIALIZER

/**
 * genradix_init - initialize a genradix
 * @_radix:	genradix to initialize
 *
 * Does not fail
 */
#घोषणा genradix_init(_radix)					\
करो अणु								\
	*(_radix) = (typeof(*_radix)) __GENRADIX_INITIALIZER;	\
पूर्ण जबतक (0)

व्योम __genradix_मुक्त(काष्ठा __genradix *);

/**
 * genradix_मुक्त: मुक्त all memory owned by a genradix
 * @_radix: the genradix to मुक्त
 *
 * After मुक्तing, @_radix will be reinitialized and empty
 */
#घोषणा genradix_मुक्त(_radix)	__genradix_मुक्त(&(_radix)->tree)

अटल अंतरभूत माप_प्रकार __idx_to_offset(माप_प्रकार idx, माप_प्रकार obj_size)
अणु
	अगर (__builtin_स्थिरant_p(obj_size))
		BUILD_BUG_ON(obj_size > PAGE_SIZE);
	अन्यथा
		BUG_ON(obj_size > PAGE_SIZE);

	अगर (!is_घातer_of_2(obj_size)) अणु
		माप_प्रकार objs_per_page = PAGE_SIZE / obj_size;

		वापस (idx / objs_per_page) * PAGE_SIZE +
			(idx % objs_per_page) * obj_size;
	पूर्ण अन्यथा अणु
		वापस idx * obj_size;
	पूर्ण
पूर्ण

#घोषणा __genradix_cast(_radix)		(typeof((_radix)->type[0]) *)
#घोषणा __genradix_obj_size(_radix)	माप((_radix)->type[0])
#घोषणा __genradix_idx_to_offset(_radix, _idx)			\
	__idx_to_offset(_idx, __genradix_obj_size(_radix))

व्योम *__genradix_ptr(काष्ठा __genradix *, माप_प्रकार);

/**
 * genradix_ptr - get a poपूर्णांकer to a genradix entry
 * @_radix:	genradix to access
 * @_idx:	index to fetch
 *
 * Returns a poपूर्णांकer to entry at @_idx, or शून्य अगर that entry करोes not exist.
 */
#घोषणा genradix_ptr(_radix, _idx)				\
	(__genradix_cast(_radix)				\
	 __genradix_ptr(&(_radix)->tree,			\
			__genradix_idx_to_offset(_radix, _idx)))

व्योम *__genradix_ptr_alloc(काष्ठा __genradix *, माप_प्रकार, gfp_t);

/**
 * genradix_ptr_alloc - get a poपूर्णांकer to a genradix entry, allocating it
 *			अगर necessary
 * @_radix:	genradix to access
 * @_idx:	index to fetch
 * @_gfp:	gfp mask
 *
 * Returns a poपूर्णांकer to entry at @_idx, or शून्य on allocation failure
 */
#घोषणा genradix_ptr_alloc(_radix, _idx, _gfp)			\
	(__genradix_cast(_radix)				\
	 __genradix_ptr_alloc(&(_radix)->tree,			\
			__genradix_idx_to_offset(_radix, _idx),	\
			_gfp))

काष्ठा genradix_iter अणु
	माप_प्रकार			offset;
	माप_प्रकार			pos;
पूर्ण;

/**
 * genradix_iter_init - initialize a genradix_iter
 * @_radix:	genradix that will be iterated over
 * @_idx:	index to start iterating from
 */
#घोषणा genradix_iter_init(_radix, _idx)			\
	((काष्ठा genradix_iter) अणु				\
		.pos	= (_idx),				\
		.offset	= __genradix_idx_to_offset((_radix), (_idx)),\
	पूर्ण)

व्योम *__genradix_iter_peek(काष्ठा genradix_iter *, काष्ठा __genradix *, माप_प्रकार);

/**
 * genradix_iter_peek - get first entry at or above iterator's current
 *			position
 * @_iter:	a genradix_iter
 * @_radix:	genradix being iterated over
 *
 * If no more entries exist at or above @_iter's current position, वापसs शून्य
 */
#घोषणा genradix_iter_peek(_iter, _radix)			\
	(__genradix_cast(_radix)				\
	 __genradix_iter_peek(_iter, &(_radix)->tree,		\
			      PAGE_SIZE / __genradix_obj_size(_radix)))

अटल अंतरभूत व्योम __genradix_iter_advance(काष्ठा genradix_iter *iter,
					   माप_प्रकार obj_size)
अणु
	iter->offset += obj_size;

	अगर (!is_घातer_of_2(obj_size) &&
	    (iter->offset & (PAGE_SIZE - 1)) + obj_size > PAGE_SIZE)
		iter->offset = round_up(iter->offset, PAGE_SIZE);

	iter->pos++;
पूर्ण

#घोषणा genradix_iter_advance(_iter, _radix)			\
	__genradix_iter_advance(_iter, __genradix_obj_size(_radix))

#घोषणा genradix_क्रम_each_from(_radix, _iter, _p, _start)	\
	क्रम (_iter = genradix_iter_init(_radix, _start);	\
	     (_p = genradix_iter_peek(&_iter, _radix)) != शून्य;	\
	     genradix_iter_advance(&_iter, _radix))

/**
 * genradix_क्रम_each - iterate over entry in a genradix
 * @_radix:	genradix to iterate over
 * @_iter:	a genradix_iter to track current position
 * @_p:		poपूर्णांकer to genradix entry type
 *
 * On every iteration, @_p will poपूर्णांक to the current entry, and @_iter.pos
 * will be the current entry's index.
 */
#घोषणा genradix_क्रम_each(_radix, _iter, _p)			\
	genradix_क्रम_each_from(_radix, _iter, _p, 0)

पूर्णांक __genradix_pपुनः_स्मृति(काष्ठा __genradix *, माप_प्रकार, gfp_t);

/**
 * genradix_pपुनः_स्मृति - pपुनः_स्मृतिate entries in a generic radix tree
 * @_radix:	genradix to pपुनः_स्मृतिate
 * @_nr:	number of entries to pपुनः_स्मृतिate
 * @_gfp:	gfp mask
 *
 * Returns 0 on success, -ENOMEM on failure
 */
#घोषणा genradix_pपुनः_स्मृति(_radix, _nr, _gfp)			\
	 __genradix_pपुनः_स्मृति(&(_radix)->tree,			\
			__genradix_idx_to_offset(_radix, _nr + 1),\
			_gfp)


#पूर्ण_अगर /* _LINUX_GENERIC_RADIX_TREE_H */
