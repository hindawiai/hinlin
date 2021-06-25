<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित BTRFS_MISC_H
#घोषणा BTRFS_MISC_H

#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <linux/rbtree.h>

#घोषणा in_range(b, first, len) ((b) >= (first) && (b) < (first) + (len))

अटल अंतरभूत व्योम cond_wake_up(काष्ठा रुको_queue_head *wq)
अणु
	/*
	 * This implies a full smp_mb barrier, see comments क्रम
	 * रुकोqueue_active why.
	 */
	अगर (wq_has_sleeper(wq))
		wake_up(wq);
पूर्ण

अटल अंतरभूत व्योम cond_wake_up_nomb(काष्ठा रुको_queue_head *wq)
अणु
	/*
	 * Special हाल क्रम conditional wakeup where the barrier required क्रम
	 * रुकोqueue_active is implied by some of the preceding code. Eg. one
	 * of such atomic operations (atomic_dec_and_वापस, ...), or a
	 * unlock/lock sequence, etc.
	 */
	अगर (रुकोqueue_active(wq))
		wake_up(wq);
पूर्ण

अटल अंतरभूत u64 भाग_factor(u64 num, पूर्णांक factor)
अणु
	अगर (factor == 10)
		वापस num;
	num *= factor;
	वापस भाग_u64(num, 10);
पूर्ण

अटल अंतरभूत u64 भाग_factor_fine(u64 num, पूर्णांक factor)
अणु
	अगर (factor == 100)
		वापस num;
	num *= factor;
	वापस भाग_u64(num, 100);
पूर्ण

/* Copy of is_घातer_of_two that is 64bit safe */
अटल अंतरभूत bool is_घातer_of_two_u64(u64 n)
अणु
	वापस n != 0 && (n & (n - 1)) == 0;
पूर्ण

अटल अंतरभूत bool has_single_bit_set(u64 n)
अणु
	वापस is_घातer_of_two_u64(n);
पूर्ण

/*
 * Simple bytenr based rb_tree relate काष्ठाures
 *
 * Any काष्ठाure wants to use bytenr as single search index should have their
 * काष्ठाure start with these members.
 */
काष्ठा rb_simple_node अणु
	काष्ठा rb_node rb_node;
	u64 bytenr;
पूर्ण;

अटल अंतरभूत काष्ठा rb_node *rb_simple_search(काष्ठा rb_root *root, u64 bytenr)
अणु
	काष्ठा rb_node *node = root->rb_node;
	काष्ठा rb_simple_node *entry;

	जबतक (node) अणु
		entry = rb_entry(node, काष्ठा rb_simple_node, rb_node);

		अगर (bytenr < entry->bytenr)
			node = node->rb_left;
		अन्यथा अगर (bytenr > entry->bytenr)
			node = node->rb_right;
		अन्यथा
			वापस node;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rb_node *rb_simple_insert(काष्ठा rb_root *root, u64 bytenr,
					       काष्ठा rb_node *node)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rb_simple_node *entry;

	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा rb_simple_node, rb_node);

		अगर (bytenr < entry->bytenr)
			p = &(*p)->rb_left;
		अन्यथा अगर (bytenr > entry->bytenr)
			p = &(*p)->rb_right;
		अन्यथा
			वापस parent;
	पूर्ण

	rb_link_node(node, parent, p);
	rb_insert_color(node, root);
	वापस शून्य;
पूर्ण

#पूर्ण_अगर
