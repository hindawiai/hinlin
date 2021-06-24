<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <यंत्र/bug.h>
#समावेश <linux/rbtree_augmented.h>
#समावेश "drbd_interval.h"

/*
 * पूर्णांकerval_end  -  वापस end of @node
 */
अटल अंतरभूत
sector_t पूर्णांकerval_end(काष्ठा rb_node *node)
अणु
	काष्ठा drbd_पूर्णांकerval *this = rb_entry(node, काष्ठा drbd_पूर्णांकerval, rb);
	वापस this->end;
पूर्ण

#घोषणा NODE_END(node) ((node)->sector + ((node)->size >> 9))

RB_DECLARE_CALLBACKS_MAX(अटल, augment_callbacks,
			 काष्ठा drbd_पूर्णांकerval, rb, sector_t, end, NODE_END);

/*
 * drbd_insert_पूर्णांकerval  -  insert a new पूर्णांकerval पूर्णांकo a tree
 */
bool
drbd_insert_पूर्णांकerval(काष्ठा rb_root *root, काष्ठा drbd_पूर्णांकerval *this)
अणु
	काष्ठा rb_node **new = &root->rb_node, *parent = शून्य;
	sector_t this_end = this->sector + (this->size >> 9);

	BUG_ON(!IS_ALIGNED(this->size, 512));

	जबतक (*new) अणु
		काष्ठा drbd_पूर्णांकerval *here =
			rb_entry(*new, काष्ठा drbd_पूर्णांकerval, rb);

		parent = *new;
		अगर (here->end < this_end)
			here->end = this_end;
		अगर (this->sector < here->sector)
			new = &(*new)->rb_left;
		अन्यथा अगर (this->sector > here->sector)
			new = &(*new)->rb_right;
		अन्यथा अगर (this < here)
			new = &(*new)->rb_left;
		अन्यथा अगर (this > here)
			new = &(*new)->rb_right;
		अन्यथा
			वापस false;
	पूर्ण

	this->end = this_end;
	rb_link_node(&this->rb, parent, new);
	rb_insert_augmented(&this->rb, root, &augment_callbacks);
	वापस true;
पूर्ण

/**
 * drbd_contains_पूर्णांकerval  -  check अगर a tree contains a given पूर्णांकerval
 * @root:	red black tree root
 * @sector:	start sector of @पूर्णांकerval
 * @पूर्णांकerval:	may not be a valid poपूर्णांकer
 *
 * Returns अगर the tree contains the node @पूर्णांकerval with start sector @start.
 * Does not dereference @पूर्णांकerval until @पूर्णांकerval is known to be a valid object
 * in @tree.  Returns %false अगर @पूर्णांकerval is in the tree but with a dअगरferent
 * sector number.
 */
bool
drbd_contains_पूर्णांकerval(काष्ठा rb_root *root, sector_t sector,
		       काष्ठा drbd_पूर्णांकerval *पूर्णांकerval)
अणु
	काष्ठा rb_node *node = root->rb_node;

	जबतक (node) अणु
		काष्ठा drbd_पूर्णांकerval *here =
			rb_entry(node, काष्ठा drbd_पूर्णांकerval, rb);

		अगर (sector < here->sector)
			node = node->rb_left;
		अन्यथा अगर (sector > here->sector)
			node = node->rb_right;
		अन्यथा अगर (पूर्णांकerval < here)
			node = node->rb_left;
		अन्यथा अगर (पूर्णांकerval > here)
			node = node->rb_right;
		अन्यथा
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/*
 * drbd_हटाओ_पूर्णांकerval  -  हटाओ an पूर्णांकerval from a tree
 */
व्योम
drbd_हटाओ_पूर्णांकerval(काष्ठा rb_root *root, काष्ठा drbd_पूर्णांकerval *this)
अणु
	rb_erase_augmented(&this->rb, root, &augment_callbacks);
पूर्ण

/**
 * drbd_find_overlap  - search क्रम an पूर्णांकerval overlapping with [sector, sector + size)
 * @root:	red black tree root
 * @sector:	start sector
 * @size:	size, aligned to 512 bytes
 *
 * Returns an पूर्णांकerval overlapping with [sector, sector + size), or शून्य अगर
 * there is none.  When there is more than one overlapping पूर्णांकerval in the
 * tree, the पूर्णांकerval with the lowest start sector is वापसed, and all other
 * overlapping पूर्णांकervals will be on the right side of the tree, reachable with
 * rb_next().
 */
काष्ठा drbd_पूर्णांकerval *
drbd_find_overlap(काष्ठा rb_root *root, sector_t sector, अचिन्हित पूर्णांक size)
अणु
	काष्ठा rb_node *node = root->rb_node;
	काष्ठा drbd_पूर्णांकerval *overlap = शून्य;
	sector_t end = sector + (size >> 9);

	BUG_ON(!IS_ALIGNED(size, 512));

	जबतक (node) अणु
		काष्ठा drbd_पूर्णांकerval *here =
			rb_entry(node, काष्ठा drbd_पूर्णांकerval, rb);

		अगर (node->rb_left &&
		    sector < पूर्णांकerval_end(node->rb_left)) अणु
			/* Overlap अगर any must be on left side */
			node = node->rb_left;
		पूर्ण अन्यथा अगर (here->sector < end &&
			   sector < here->sector + (here->size >> 9)) अणु
			overlap = here;
			अवरोध;
		पूर्ण अन्यथा अगर (sector >= here->sector) अणु
			/* Overlap अगर any must be on right side */
			node = node->rb_right;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
	वापस overlap;
पूर्ण

काष्ठा drbd_पूर्णांकerval *
drbd_next_overlap(काष्ठा drbd_पूर्णांकerval *i, sector_t sector, अचिन्हित पूर्णांक size)
अणु
	sector_t end = sector + (size >> 9);
	काष्ठा rb_node *node;

	क्रम (;;) अणु
		node = rb_next(&i->rb);
		अगर (!node)
			वापस शून्य;
		i = rb_entry(node, काष्ठा drbd_पूर्णांकerval, rb);
		अगर (i->sector >= end)
			वापस शून्य;
		अगर (sector < i->sector + (i->size >> 9))
			वापस i;
	पूर्ण
पूर्ण
