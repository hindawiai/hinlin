<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Generic associative array implementation.
 *
 * See Documentation/core-api/assoc_array.rst क्रम inक्रमmation.
 *
 * Copyright (C) 2013 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित _LINUX_ASSOC_ARRAY_H
#घोषणा _LINUX_ASSOC_ARRAY_H

#अगर_घोषित CONFIG_ASSOCIATIVE_ARRAY

#समावेश <linux/types.h>

#घोषणा ASSOC_ARRAY_KEY_CHUNK_SIZE BITS_PER_LONG /* Key data retrieved in chunks of this size */

/*
 * Generic associative array.
 */
काष्ठा assoc_array अणु
	काष्ठा assoc_array_ptr	*root;		/* The node at the root of the tree */
	अचिन्हित दीर्घ		nr_leaves_on_tree;
पूर्ण;

/*
 * Operations on objects and index keys क्रम use by array manipulation routines.
 */
काष्ठा assoc_array_ops अणु
	/* Method to get a chunk of an index key from caller-supplied data */
	अचिन्हित दीर्घ (*get_key_chunk)(स्थिर व्योम *index_key, पूर्णांक level);

	/* Method to get a piece of an object's index key */
	अचिन्हित दीर्घ (*get_object_key_chunk)(स्थिर व्योम *object, पूर्णांक level);

	/* Is this the object we're looking क्रम? */
	bool (*compare_object)(स्थिर व्योम *object, स्थिर व्योम *index_key);

	/* How dअगरferent is an object from an index key, to a bit position in
	 * their keys? (or -1 अगर they're the same)
	 */
	पूर्णांक (*dअगरf_objects)(स्थिर व्योम *object, स्थिर व्योम *index_key);

	/* Method to मुक्त an object. */
	व्योम (*मुक्त_object)(व्योम *object);
पूर्ण;

/*
 * Access and manipulation functions.
 */
काष्ठा assoc_array_edit;

अटल अंतरभूत व्योम assoc_array_init(काष्ठा assoc_array *array)
अणु
	array->root = शून्य;
	array->nr_leaves_on_tree = 0;
पूर्ण

बाह्य पूर्णांक assoc_array_iterate(स्थिर काष्ठा assoc_array *array,
			       पूर्णांक (*iterator)(स्थिर व्योम *object,
					       व्योम *iterator_data),
			       व्योम *iterator_data);
बाह्य व्योम *assoc_array_find(स्थिर काष्ठा assoc_array *array,
			      स्थिर काष्ठा assoc_array_ops *ops,
			      स्थिर व्योम *index_key);
बाह्य व्योम assoc_array_destroy(काष्ठा assoc_array *array,
				स्थिर काष्ठा assoc_array_ops *ops);
बाह्य काष्ठा assoc_array_edit *assoc_array_insert(काष्ठा assoc_array *array,
						   स्थिर काष्ठा assoc_array_ops *ops,
						   स्थिर व्योम *index_key,
						   व्योम *object);
बाह्य व्योम assoc_array_insert_set_object(काष्ठा assoc_array_edit *edit,
					  व्योम *object);
बाह्य काष्ठा assoc_array_edit *assoc_array_delete(काष्ठा assoc_array *array,
						   स्थिर काष्ठा assoc_array_ops *ops,
						   स्थिर व्योम *index_key);
बाह्य काष्ठा assoc_array_edit *assoc_array_clear(काष्ठा assoc_array *array,
						  स्थिर काष्ठा assoc_array_ops *ops);
बाह्य व्योम assoc_array_apply_edit(काष्ठा assoc_array_edit *edit);
बाह्य व्योम assoc_array_cancel_edit(काष्ठा assoc_array_edit *edit);
बाह्य पूर्णांक assoc_array_gc(काष्ठा assoc_array *array,
			  स्थिर काष्ठा assoc_array_ops *ops,
			  bool (*iterator)(व्योम *object, व्योम *iterator_data),
			  व्योम *iterator_data);

#पूर्ण_अगर /* CONFIG_ASSOCIATIVE_ARRAY */
#पूर्ण_अगर /* _LINUX_ASSOC_ARRAY_H */
