<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित __TRACING_MAP_H
#घोषणा __TRACING_MAP_H

#घोषणा TRACING_MAP_BITS_DEFAULT	11
#घोषणा TRACING_MAP_BITS_MAX		17
#घोषणा TRACING_MAP_BITS_MIN		7

#घोषणा TRACING_MAP_KEYS_MAX		3
#घोषणा TRACING_MAP_VALS_MAX		3
#घोषणा TRACING_MAP_FIELDS_MAX		(TRACING_MAP_KEYS_MAX + \
					 TRACING_MAP_VALS_MAX)
#घोषणा TRACING_MAP_VARS_MAX		16
#घोषणा TRACING_MAP_SORT_KEYS_MAX	2

प्रकार पूर्णांक (*tracing_map_cmp_fn_t) (व्योम *val_a, व्योम *val_b);

/*
 * This is an overview of the tracing_map data काष्ठाures and how they
 * relate to the tracing_map API.  The details of the algorithms
 * aren't discussed here - this is just a general overview of the data
 * काष्ठाures and how they पूर्णांकeract with the API.
 *
 * The central data काष्ठाure of the tracing_map is an initially
 * zeroed array of काष्ठा tracing_map_entry (stored in the map field
 * of काष्ठा tracing_map).  tracing_map_entry is a very simple data
 * काष्ठाure containing only two fields: a 32-bit अचिन्हित 'key'
 * variable and a poपूर्णांकer named 'val'.  This array of काष्ठा
 * tracing_map_entry is essentially a hash table which will be
 * modअगरied by a single function, tracing_map_insert(), but which can
 * be traversed and पढ़ो by a user at any समय (though the user करोes
 * this indirectly via an array of tracing_map_sort_entry - see the
 * explanation of that data काष्ठाure in the discussion of the
 * sorting-related data काष्ठाures below).
 *
 * The central function of the tracing_map API is
 * tracing_map_insert().  tracing_map_insert() hashes the
 * arbitrarily-sized key passed पूर्णांकo it पूर्णांकo a 32-bit अचिन्हित key.
 * It then uses this key, truncated to the array size, as an index
 * पूर्णांकo the array of tracing_map_entries.  If the value of the 'key'
 * field of the tracing_map_entry found at that location is 0, then
 * that entry is considered to be मुक्त and can be claimed, by
 * replacing the 0 in the 'key' field of the tracing_map_entry with
 * the new 32-bit hashed key.  Once claimed, that tracing_map_entry's
 * 'val' field is then used to store a unique element which will be
 * क्रमever associated with that 32-bit hashed key in the
 * tracing_map_entry.
 *
 * That unique element now in the tracing_map_entry's 'val' field is
 * an instance of tracing_map_elt, where 'elt' in the latter part of
 * that variable name is लघु क्रम 'element'.  The purpose of a
 * tracing_map_elt is to hold values specअगरic to the particular
 * 32-bit hashed key it's associated with.  Things such as the unique
 * set of aggregated sums associated with the 32-bit hashed key, aदीर्घ
 * with a copy of the full key associated with the entry, and which
 * was used to produce the 32-bit hashed key.
 *
 * When tracing_map_create() is called to create the tracing map, the
 * user specअगरies (indirectly via the map_bits param, the details are
 * unimportant क्रम this discussion) the maximum number of elements
 * that the map can hold (stored in the max_elts field of काष्ठा
 * tracing_map).  This is the maximum possible number of
 * tracing_map_entries in the tracing_map_entry array which can be
 * 'claimed' as described in the above discussion, and thereक्रमe is
 * also the maximum number of tracing_map_elts that can be associated
 * with the tracing_map_entry array in the tracing_map.  Because of
 * the way the insertion algorithm works, the size of the allocated
 * tracing_map_entry array is always twice the maximum number of
 * elements (2 * max_elts).  This value is stored in the map_size
 * field of काष्ठा tracing_map.
 *
 * Because tracing_map_insert() needs to work from any context,
 * including from within the memory allocation functions themselves,
 * both the tracing_map_entry array and a pool of max_elts
 * tracing_map_elts are pre-allocated beक्रमe any call is made to
 * tracing_map_insert().
 *
 * The tracing_map_entry array is allocated as a single block by
 * tracing_map_create().
 *
 * Because the tracing_map_elts are much larger objects and can't
 * generally be allocated together as a single large array without
 * failure, they're allocated inभागidually, by tracing_map_init().
 *
 * The pool of tracing_map_elts are allocated by tracing_map_init()
 * rather than by tracing_map_create() because at the समय
 * tracing_map_create() is called, there isn't enough inक्रमmation to
 * create the tracing_map_elts.  Specअगरically,the user first needs to
 * tell the tracing_map implementation how many fields the
 * tracing_map_elts contain, and which types of fields they are (key
 * or sum).  The user करोes this via the tracing_map_add_sum_field()
 * and tracing_map_add_key_field() functions, following which the user
 * calls tracing_map_init() to finish up the tracing map setup.  The
 * array holding the poपूर्णांकers which make up the pre-allocated pool of
 * tracing_map_elts is allocated as a single block and is stored in
 * the elts field of काष्ठा tracing_map.
 *
 * There is also a set of काष्ठाures used क्रम sorting that might
 * benefit from some minimal explanation.
 *
 * काष्ठा tracing_map_sort_key is used to drive the sort at any given
 * समय.  By 'any given time' we mean that a dअगरferent
 * tracing_map_sort_key will be used at dअगरferent बार depending on
 * whether the sort currently being perक्रमmed is a primary or a
 * secondary sort.
 *
 * The sort key is very simple, consisting of the field index of the
 * tracing_map_elt field to sort on (which the user saved when adding
 * the field), and whether the sort should be करोne in an ascending or
 * descending order.
 *
 * For the convenience of the sorting code, a tracing_map_sort_entry
 * is created क्रम each tracing_map_elt, again inभागidually allocated
 * to aव्योम failures that might be expected अगर allocated as a single
 * large array of काष्ठा tracing_map_sort_entry.
 * tracing_map_sort_entry instances are the objects expected by the
 * various पूर्णांकernal sorting functions, and are also what the user
 * ultimately receives after calling tracing_map_sort_entries().
 * Because it करोesn't make sense क्रम users to access an unordered and
 * sparsely populated tracing_map directly, the
 * tracing_map_sort_entries() function is provided so that users can
 * retrieve a sorted list of all existing elements.  In addition to
 * the associated tracing_map_elt 'elt' field contained within the
 * tracing_map_sort_entry, which is the object of पूर्णांकerest to the
 * user, tracing_map_sort_entry objects contain a number of additional
 * fields which are used क्रम caching and पूर्णांकernal purposes and can
 * safely be ignored.
*/

काष्ठा tracing_map_field अणु
	tracing_map_cmp_fn_t		cmp_fn;
	जोड़ अणु
		atomic64_t			sum;
		अचिन्हित पूर्णांक			offset;
	पूर्ण;
पूर्ण;

काष्ठा tracing_map_elt अणु
	काष्ठा tracing_map		*map;
	काष्ठा tracing_map_field	*fields;
	atomic64_t			*vars;
	bool				*var_set;
	व्योम				*key;
	व्योम				*निजी_data;
पूर्ण;

काष्ठा tracing_map_entry अणु
	u32				key;
	काष्ठा tracing_map_elt		*val;
पूर्ण;

काष्ठा tracing_map_sort_key अणु
	अचिन्हित पूर्णांक			field_idx;
	bool				descending;
पूर्ण;

काष्ठा tracing_map_sort_entry अणु
	व्योम				*key;
	काष्ठा tracing_map_elt		*elt;
	bool				elt_copied;
	bool				dup;
पूर्ण;

काष्ठा tracing_map_array अणु
	अचिन्हित पूर्णांक entries_per_page;
	अचिन्हित पूर्णांक entry_size_shअगरt;
	अचिन्हित पूर्णांक entry_shअगरt;
	अचिन्हित पूर्णांक entry_mask;
	अचिन्हित पूर्णांक n_pages;
	व्योम **pages;
पूर्ण;

#घोषणा TRACING_MAP_ARRAY_ELT(array, idx)				\
	(array->pages[idx >> array->entry_shअगरt] +			\
	 ((idx & array->entry_mask) << array->entry_size_shअगरt))

#घोषणा TRACING_MAP_ENTRY(array, idx)					\
	((काष्ठा tracing_map_entry *)TRACING_MAP_ARRAY_ELT(array, idx))

#घोषणा TRACING_MAP_ELT(array, idx)					\
	((काष्ठा tracing_map_elt **)TRACING_MAP_ARRAY_ELT(array, idx))

काष्ठा tracing_map अणु
	अचिन्हित पूर्णांक			key_size;
	अचिन्हित पूर्णांक			map_bits;
	अचिन्हित पूर्णांक			map_size;
	अचिन्हित पूर्णांक			max_elts;
	atomic_t			next_elt;
	काष्ठा tracing_map_array	*elts;
	काष्ठा tracing_map_array	*map;
	स्थिर काष्ठा tracing_map_ops	*ops;
	व्योम				*निजी_data;
	काष्ठा tracing_map_field	fields[TRACING_MAP_FIELDS_MAX];
	अचिन्हित पूर्णांक			n_fields;
	पूर्णांक				key_idx[TRACING_MAP_KEYS_MAX];
	अचिन्हित पूर्णांक			n_keys;
	काष्ठा tracing_map_sort_key	sort_key;
	अचिन्हित पूर्णांक			n_vars;
	atomic64_t			hits;
	atomic64_t			drops;
पूर्ण;

/**
 * काष्ठा tracing_map_ops - callbacks क्रम tracing_map
 *
 * The methods in this काष्ठाure define callback functions क्रम various
 * operations on a tracing_map or objects related to a tracing_map.
 *
 * For a detailed description of tracing_map_elt objects please see
 * the overview of tracing_map data काष्ठाures at the beginning of
 * this file.
 *
 * All the methods below are optional.
 *
 * @elt_alloc: When a tracing_map_elt is allocated, this function, अगर
 *	defined, will be called and gives clients the opportunity to
 *	allocate additional data and attach it to the element
 *	(tracing_map_elt->निजी_data is meant क्रम that purpose).
 *	Element allocation occurs beक्रमe tracing begins, when the
 *	tracing_map_init() call is made by client code.
 *
 * @elt_मुक्त: When a tracing_map_elt is मुक्तd, this function is called
 *	and allows client-allocated per-element data to be मुक्तd.
 *
 * @elt_clear: This callback allows per-element client-defined data to
 *	be cleared, अगर applicable.
 *
 * @elt_init: This callback allows per-element client-defined data to
 *	be initialized when used i.e. when the element is actually
 *	claimed by tracing_map_insert() in the context of the map
 *	insertion.
 */
काष्ठा tracing_map_ops अणु
	पूर्णांक			(*elt_alloc)(काष्ठा tracing_map_elt *elt);
	व्योम			(*elt_मुक्त)(काष्ठा tracing_map_elt *elt);
	व्योम			(*elt_clear)(काष्ठा tracing_map_elt *elt);
	व्योम			(*elt_init)(काष्ठा tracing_map_elt *elt);
पूर्ण;

बाह्य काष्ठा tracing_map *
tracing_map_create(अचिन्हित पूर्णांक map_bits,
		   अचिन्हित पूर्णांक key_size,
		   स्थिर काष्ठा tracing_map_ops *ops,
		   व्योम *निजी_data);
बाह्य पूर्णांक tracing_map_init(काष्ठा tracing_map *map);

बाह्य पूर्णांक tracing_map_add_sum_field(काष्ठा tracing_map *map);
बाह्य पूर्णांक tracing_map_add_var(काष्ठा tracing_map *map);
बाह्य पूर्णांक tracing_map_add_key_field(काष्ठा tracing_map *map,
				     अचिन्हित पूर्णांक offset,
				     tracing_map_cmp_fn_t cmp_fn);

बाह्य व्योम tracing_map_destroy(काष्ठा tracing_map *map);
बाह्य व्योम tracing_map_clear(काष्ठा tracing_map *map);

बाह्य काष्ठा tracing_map_elt *
tracing_map_insert(काष्ठा tracing_map *map, व्योम *key);
बाह्य काष्ठा tracing_map_elt *
tracing_map_lookup(काष्ठा tracing_map *map, व्योम *key);

बाह्य tracing_map_cmp_fn_t tracing_map_cmp_num(पूर्णांक field_size,
						पूर्णांक field_is_चिन्हित);
बाह्य पूर्णांक tracing_map_cmp_string(व्योम *val_a, व्योम *val_b);
बाह्य पूर्णांक tracing_map_cmp_none(व्योम *val_a, व्योम *val_b);

बाह्य व्योम tracing_map_update_sum(काष्ठा tracing_map_elt *elt,
				   अचिन्हित पूर्णांक i, u64 n);
बाह्य व्योम tracing_map_set_var(काष्ठा tracing_map_elt *elt,
				अचिन्हित पूर्णांक i, u64 n);
बाह्य bool tracing_map_var_set(काष्ठा tracing_map_elt *elt, अचिन्हित पूर्णांक i);
बाह्य u64 tracing_map_पढ़ो_sum(काष्ठा tracing_map_elt *elt, अचिन्हित पूर्णांक i);
बाह्य u64 tracing_map_पढ़ो_var(काष्ठा tracing_map_elt *elt, अचिन्हित पूर्णांक i);
बाह्य u64 tracing_map_पढ़ो_var_once(काष्ठा tracing_map_elt *elt, अचिन्हित पूर्णांक i);

बाह्य व्योम tracing_map_set_field_descr(काष्ठा tracing_map *map,
					अचिन्हित पूर्णांक i,
					अचिन्हित पूर्णांक key_offset,
					tracing_map_cmp_fn_t cmp_fn);
बाह्य पूर्णांक
tracing_map_sort_entries(काष्ठा tracing_map *map,
			 काष्ठा tracing_map_sort_key *sort_keys,
			 अचिन्हित पूर्णांक n_sort_keys,
			 काष्ठा tracing_map_sort_entry ***sort_entries);

बाह्य व्योम
tracing_map_destroy_sort_entries(काष्ठा tracing_map_sort_entry **entries,
				 अचिन्हित पूर्णांक n_entries);
#पूर्ण_अगर /* __TRACING_MAP_H */
