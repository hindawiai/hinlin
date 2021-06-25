<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Private definitions क्रम the generic associative array implementation.
 *
 * See Documentation/core-api/assoc_array.rst क्रम inक्रमmation.
 *
 * Copyright (C) 2013 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_ASSOC_ARRAY_PRIV_H
#घोषणा _LINUX_ASSOC_ARRAY_PRIV_H

#अगर_घोषित CONFIG_ASSOCIATIVE_ARRAY

#समावेश <linux/assoc_array.h>

#घोषणा ASSOC_ARRAY_FAN_OUT		16	/* Number of slots per node */
#घोषणा ASSOC_ARRAY_FAN_MASK		(ASSOC_ARRAY_FAN_OUT - 1)
#घोषणा ASSOC_ARRAY_LEVEL_STEP		(ilog2(ASSOC_ARRAY_FAN_OUT))
#घोषणा ASSOC_ARRAY_LEVEL_STEP_MASK	(ASSOC_ARRAY_LEVEL_STEP - 1)
#घोषणा ASSOC_ARRAY_KEY_CHUNK_MASK	(ASSOC_ARRAY_KEY_CHUNK_SIZE - 1)
#घोषणा ASSOC_ARRAY_KEY_CHUNK_SHIFT	(ilog2(BITS_PER_LONG))

/*
 * Undefined type representing a poपूर्णांकer with type inक्रमmation in the bottom
 * two bits.
 */
काष्ठा assoc_array_ptr;

/*
 * An N-way node in the tree.
 *
 * Each slot contains one of four things:
 *
 *	(1) Nothing (शून्य).
 *
 *	(2) A leaf object (poपूर्णांकer types 0).
 *
 *	(3) A next-level node (poपूर्णांकer type 1, subtype 0).
 *
 *	(4) A लघुcut (poपूर्णांकer type 1, subtype 1).
 *
 * The tree is optimised क्रम search-by-ID, but permits reasonable iteration
 * also.
 *
 * The tree is navigated by स्थिरructing an index key consisting of an array of
 * segments, where each segment is ilog2(ASSOC_ARRAY_FAN_OUT) bits in size.
 *
 * The segments correspond to levels of the tree (the first segment is used at
 * level 0, the second at level 1, etc.).
 */
काष्ठा assoc_array_node अणु
	काष्ठा assoc_array_ptr	*back_poपूर्णांकer;
	u8			parent_slot;
	काष्ठा assoc_array_ptr	*slots[ASSOC_ARRAY_FAN_OUT];
	अचिन्हित दीर्घ		nr_leaves_on_branch;
पूर्ण;

/*
 * A लघुcut through the index space out to where a collection of nodes/leaves
 * with the same IDs live.
 */
काष्ठा assoc_array_लघुcut अणु
	काष्ठा assoc_array_ptr	*back_poपूर्णांकer;
	पूर्णांक			parent_slot;
	पूर्णांक			skip_to_level;
	काष्ठा assoc_array_ptr	*next_node;
	अचिन्हित दीर्घ		index_key[];
पूर्ण;

/*
 * Pपुनः_स्मृतिation cache.
 */
काष्ठा assoc_array_edit अणु
	काष्ठा rcu_head			rcu;
	काष्ठा assoc_array		*array;
	स्थिर काष्ठा assoc_array_ops	*ops;
	स्थिर काष्ठा assoc_array_ops	*ops_क्रम_excised_subtree;
	काष्ठा assoc_array_ptr		*leaf;
	काष्ठा assoc_array_ptr		**leaf_p;
	काष्ठा assoc_array_ptr		*dead_leaf;
	काष्ठा assoc_array_ptr		*new_meta[3];
	काष्ठा assoc_array_ptr		*excised_meta[1];
	काष्ठा assoc_array_ptr		*excised_subtree;
	काष्ठा assoc_array_ptr		**set_backpoपूर्णांकers[ASSOC_ARRAY_FAN_OUT];
	काष्ठा assoc_array_ptr		*set_backpoपूर्णांकers_to;
	काष्ठा assoc_array_node		*adjust_count_on;
	दीर्घ				adjust_count_by;
	काष्ठा अणु
		काष्ठा assoc_array_ptr	**ptr;
		काष्ठा assoc_array_ptr	*to;
	पूर्ण set[2];
	काष्ठा अणु
		u8			*p;
		u8			to;
	पूर्ण set_parent_slot[1];
	u8				segment_cache[ASSOC_ARRAY_FAN_OUT + 1];
पूर्ण;

/*
 * Internal tree member poपूर्णांकers are marked in the bottom one or two bits to
 * indicate what type they are so that we करोn't have to look behind every
 * poपूर्णांकer to see what it poपूर्णांकs to.
 *
 * We provide functions to test type annotations and to create and translate
 * the annotated poपूर्णांकers.
 */
#घोषणा ASSOC_ARRAY_PTR_TYPE_MASK 0x1UL
#घोषणा ASSOC_ARRAY_PTR_LEAF_TYPE 0x0UL	/* Poपूर्णांकs to leaf (or nowhere) */
#घोषणा ASSOC_ARRAY_PTR_META_TYPE 0x1UL	/* Poपूर्णांकs to node or लघुcut */
#घोषणा ASSOC_ARRAY_PTR_SUBTYPE_MASK	0x2UL
#घोषणा ASSOC_ARRAY_PTR_NODE_SUBTYPE	0x0UL
#घोषणा ASSOC_ARRAY_PTR_SHORTCUT_SUBTYPE 0x2UL

अटल अंतरभूत bool assoc_array_ptr_is_meta(स्थिर काष्ठा assoc_array_ptr *x)
अणु
	वापस (अचिन्हित दीर्घ)x & ASSOC_ARRAY_PTR_TYPE_MASK;
पूर्ण
अटल अंतरभूत bool assoc_array_ptr_is_leaf(स्थिर काष्ठा assoc_array_ptr *x)
अणु
	वापस !assoc_array_ptr_is_meta(x);
पूर्ण
अटल अंतरभूत bool assoc_array_ptr_is_लघुcut(स्थिर काष्ठा assoc_array_ptr *x)
अणु
	वापस (अचिन्हित दीर्घ)x & ASSOC_ARRAY_PTR_SUBTYPE_MASK;
पूर्ण
अटल अंतरभूत bool assoc_array_ptr_is_node(स्थिर काष्ठा assoc_array_ptr *x)
अणु
	वापस !assoc_array_ptr_is_लघुcut(x);
पूर्ण

अटल अंतरभूत व्योम *assoc_array_ptr_to_leaf(स्थिर काष्ठा assoc_array_ptr *x)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)x & ~ASSOC_ARRAY_PTR_TYPE_MASK);
पूर्ण

अटल अंतरभूत
अचिन्हित दीर्घ __assoc_array_ptr_to_meta(स्थिर काष्ठा assoc_array_ptr *x)
अणु
	वापस (अचिन्हित दीर्घ)x &
		~(ASSOC_ARRAY_PTR_SUBTYPE_MASK | ASSOC_ARRAY_PTR_TYPE_MASK);
पूर्ण
अटल अंतरभूत
काष्ठा assoc_array_node *assoc_array_ptr_to_node(स्थिर काष्ठा assoc_array_ptr *x)
अणु
	वापस (काष्ठा assoc_array_node *)__assoc_array_ptr_to_meta(x);
पूर्ण
अटल अंतरभूत
काष्ठा assoc_array_लघुcut *assoc_array_ptr_to_लघुcut(स्थिर काष्ठा assoc_array_ptr *x)
अणु
	वापस (काष्ठा assoc_array_लघुcut *)__assoc_array_ptr_to_meta(x);
पूर्ण

अटल अंतरभूत
काष्ठा assoc_array_ptr *__assoc_array_x_to_ptr(स्थिर व्योम *p, अचिन्हित दीर्घ t)
अणु
	वापस (काष्ठा assoc_array_ptr *)((अचिन्हित दीर्घ)p | t);
पूर्ण
अटल अंतरभूत
काष्ठा assoc_array_ptr *assoc_array_leaf_to_ptr(स्थिर व्योम *p)
अणु
	वापस __assoc_array_x_to_ptr(p, ASSOC_ARRAY_PTR_LEAF_TYPE);
पूर्ण
अटल अंतरभूत
काष्ठा assoc_array_ptr *assoc_array_node_to_ptr(स्थिर काष्ठा assoc_array_node *p)
अणु
	वापस __assoc_array_x_to_ptr(
		p, ASSOC_ARRAY_PTR_META_TYPE | ASSOC_ARRAY_PTR_NODE_SUBTYPE);
पूर्ण
अटल अंतरभूत
काष्ठा assoc_array_ptr *assoc_array_लघुcut_to_ptr(स्थिर काष्ठा assoc_array_लघुcut *p)
अणु
	वापस __assoc_array_x_to_ptr(
		p, ASSOC_ARRAY_PTR_META_TYPE | ASSOC_ARRAY_PTR_SHORTCUT_SUBTYPE);
पूर्ण

#पूर्ण_अगर /* CONFIG_ASSOCIATIVE_ARRAY */
#पूर्ण_अगर /* _LINUX_ASSOC_ARRAY_PRIV_H */
