<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * tracing_map - lock-मुक्त map क्रम tracing
 *
 * Copyright (C) 2015 Tom Zanussi <tom.zanussi@linux.पूर्णांकel.com>
 *
 * tracing_map implementation inspired by lock-मुक्त map algorithms
 * originated by Dr. Clअगरf Click:
 *
 * http://www.azulप्रणालीs.com/blog/clअगरf/2007-03-26-non-blocking-hashtable
 * http://www.azulप्रणालीs.com/events/javaone_2007/2007_LockFreeHash.pdf
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/jhash.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>

#समावेश "tracing_map.h"
#समावेश "trace.h"

/*
 * NOTE: For a detailed description of the data काष्ठाures used by
 * these functions (such as tracing_map_elt) please see the overview
 * of tracing_map data काष्ठाures at the beginning of tracing_map.h.
 */

/**
 * tracing_map_update_sum - Add a value to a tracing_map_elt's sum field
 * @elt: The tracing_map_elt
 * @i: The index of the given sum associated with the tracing_map_elt
 * @n: The value to add to the sum
 *
 * Add n to sum i associated with the specअगरied tracing_map_elt
 * instance.  The index i is the index वापसed by the call to
 * tracing_map_add_sum_field() when the tracing map was set up.
 */
व्योम tracing_map_update_sum(काष्ठा tracing_map_elt *elt, अचिन्हित पूर्णांक i, u64 n)
अणु
	atomic64_add(n, &elt->fields[i].sum);
पूर्ण

/**
 * tracing_map_पढ़ो_sum - Return the value of a tracing_map_elt's sum field
 * @elt: The tracing_map_elt
 * @i: The index of the given sum associated with the tracing_map_elt
 *
 * Retrieve the value of the sum i associated with the specअगरied
 * tracing_map_elt instance.  The index i is the index वापसed by the
 * call to tracing_map_add_sum_field() when the tracing map was set
 * up.
 *
 * Return: The sum associated with field i क्रम elt.
 */
u64 tracing_map_पढ़ो_sum(काष्ठा tracing_map_elt *elt, अचिन्हित पूर्णांक i)
अणु
	वापस (u64)atomic64_पढ़ो(&elt->fields[i].sum);
पूर्ण

/**
 * tracing_map_set_var - Assign a tracing_map_elt's variable field
 * @elt: The tracing_map_elt
 * @i: The index of the given variable associated with the tracing_map_elt
 * @n: The value to assign
 *
 * Assign n to variable i associated with the specअगरied tracing_map_elt
 * instance.  The index i is the index वापसed by the call to
 * tracing_map_add_var() when the tracing map was set up.
 */
व्योम tracing_map_set_var(काष्ठा tracing_map_elt *elt, अचिन्हित पूर्णांक i, u64 n)
अणु
	atomic64_set(&elt->vars[i], n);
	elt->var_set[i] = true;
पूर्ण

/**
 * tracing_map_var_set - Return whether or not a variable has been set
 * @elt: The tracing_map_elt
 * @i: The index of the given variable associated with the tracing_map_elt
 *
 * Return true अगर the variable has been set, false otherwise.  The
 * index i is the index वापसed by the call to tracing_map_add_var()
 * when the tracing map was set up.
 */
bool tracing_map_var_set(काष्ठा tracing_map_elt *elt, अचिन्हित पूर्णांक i)
अणु
	वापस elt->var_set[i];
पूर्ण

/**
 * tracing_map_पढ़ो_var - Return the value of a tracing_map_elt's variable field
 * @elt: The tracing_map_elt
 * @i: The index of the given variable associated with the tracing_map_elt
 *
 * Retrieve the value of the variable i associated with the specअगरied
 * tracing_map_elt instance.  The index i is the index वापसed by the
 * call to tracing_map_add_var() when the tracing map was set
 * up.
 *
 * Return: The variable value associated with field i क्रम elt.
 */
u64 tracing_map_पढ़ो_var(काष्ठा tracing_map_elt *elt, अचिन्हित पूर्णांक i)
अणु
	वापस (u64)atomic64_पढ़ो(&elt->vars[i]);
पूर्ण

/**
 * tracing_map_पढ़ो_var_once - Return and reset a tracing_map_elt's variable field
 * @elt: The tracing_map_elt
 * @i: The index of the given variable associated with the tracing_map_elt
 *
 * Retrieve the value of the variable i associated with the specअगरied
 * tracing_map_elt instance, and reset the variable to the 'not set'
 * state.  The index i is the index वापसed by the call to
 * tracing_map_add_var() when the tracing map was set up.  The reset
 * essentially makes the variable a पढ़ो-once variable अगर it's only
 * accessed using this function.
 *
 * Return: The variable value associated with field i क्रम elt.
 */
u64 tracing_map_पढ़ो_var_once(काष्ठा tracing_map_elt *elt, अचिन्हित पूर्णांक i)
अणु
	elt->var_set[i] = false;
	वापस (u64)atomic64_पढ़ो(&elt->vars[i]);
पूर्ण

पूर्णांक tracing_map_cmp_string(व्योम *val_a, व्योम *val_b)
अणु
	अक्षर *a = val_a;
	अक्षर *b = val_b;

	वापस म_भेद(a, b);
पूर्ण

पूर्णांक tracing_map_cmp_none(व्योम *val_a, व्योम *val_b)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tracing_map_cmp_atomic64(व्योम *val_a, व्योम *val_b)
अणु
	u64 a = atomic64_पढ़ो((atomic64_t *)val_a);
	u64 b = atomic64_पढ़ो((atomic64_t *)val_b);

	वापस (a > b) ? 1 : ((a < b) ? -1 : 0);
पूर्ण

#घोषणा DEFINE_TRACING_MAP_CMP_FN(type)					\
अटल पूर्णांक tracing_map_cmp_##type(व्योम *val_a, व्योम *val_b)		\
अणु									\
	type a = (type)(*(u64 *)val_a);					\
	type b = (type)(*(u64 *)val_b);					\
									\
	वापस (a > b) ? 1 : ((a < b) ? -1 : 0);			\
पूर्ण

DEFINE_TRACING_MAP_CMP_FN(s64);
DEFINE_TRACING_MAP_CMP_FN(u64);
DEFINE_TRACING_MAP_CMP_FN(s32);
DEFINE_TRACING_MAP_CMP_FN(u32);
DEFINE_TRACING_MAP_CMP_FN(s16);
DEFINE_TRACING_MAP_CMP_FN(u16);
DEFINE_TRACING_MAP_CMP_FN(s8);
DEFINE_TRACING_MAP_CMP_FN(u8);

tracing_map_cmp_fn_t tracing_map_cmp_num(पूर्णांक field_size,
					 पूर्णांक field_is_चिन्हित)
अणु
	tracing_map_cmp_fn_t fn = tracing_map_cmp_none;

	चयन (field_size) अणु
	हाल 8:
		अगर (field_is_चिन्हित)
			fn = tracing_map_cmp_s64;
		अन्यथा
			fn = tracing_map_cmp_u64;
		अवरोध;
	हाल 4:
		अगर (field_is_चिन्हित)
			fn = tracing_map_cmp_s32;
		अन्यथा
			fn = tracing_map_cmp_u32;
		अवरोध;
	हाल 2:
		अगर (field_is_चिन्हित)
			fn = tracing_map_cmp_s16;
		अन्यथा
			fn = tracing_map_cmp_u16;
		अवरोध;
	हाल 1:
		अगर (field_is_चिन्हित)
			fn = tracing_map_cmp_s8;
		अन्यथा
			fn = tracing_map_cmp_u8;
		अवरोध;
	पूर्ण

	वापस fn;
पूर्ण

अटल पूर्णांक tracing_map_add_field(काष्ठा tracing_map *map,
				 tracing_map_cmp_fn_t cmp_fn)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (map->n_fields < TRACING_MAP_FIELDS_MAX) अणु
		ret = map->n_fields;
		map->fields[map->n_fields++].cmp_fn = cmp_fn;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * tracing_map_add_sum_field - Add a field describing a tracing_map sum
 * @map: The tracing_map
 *
 * Add a sum field to the key and वापस the index identअगरying it in
 * the map and associated tracing_map_elts.  This is the index used
 * क्रम instance to update a sum क्रम a particular tracing_map_elt using
 * tracing_map_update_sum() or पढ़ोing it via tracing_map_पढ़ो_sum().
 *
 * Return: The index identअगरying the field in the map and associated
 * tracing_map_elts, or -EINVAL on error.
 */
पूर्णांक tracing_map_add_sum_field(काष्ठा tracing_map *map)
अणु
	वापस tracing_map_add_field(map, tracing_map_cmp_atomic64);
पूर्ण

/**
 * tracing_map_add_var - Add a field describing a tracing_map var
 * @map: The tracing_map
 *
 * Add a var to the map and वापस the index identअगरying it in the map
 * and associated tracing_map_elts.  This is the index used क्रम
 * instance to update a var क्रम a particular tracing_map_elt using
 * tracing_map_update_var() or पढ़ोing it via tracing_map_पढ़ो_var().
 *
 * Return: The index identअगरying the var in the map and associated
 * tracing_map_elts, or -EINVAL on error.
 */
पूर्णांक tracing_map_add_var(काष्ठा tracing_map *map)
अणु
	पूर्णांक ret = -EINVAL;

	अगर (map->n_vars < TRACING_MAP_VARS_MAX)
		ret = map->n_vars++;

	वापस ret;
पूर्ण

/**
 * tracing_map_add_key_field - Add a field describing a tracing_map key
 * @map: The tracing_map
 * @offset: The offset within the key
 * @cmp_fn: The comparison function that will be used to sort on the key
 *
 * Let the map know there is a key and that अगर it's used as a sort key
 * to use cmp_fn.
 *
 * A key can be a subset of a compound key; क्रम that purpose, the
 * offset param is used to describe where within the compound key
 * the key referenced by this key field resides.
 *
 * Return: The index identअगरying the field in the map and associated
 * tracing_map_elts, or -EINVAL on error.
 */
पूर्णांक tracing_map_add_key_field(काष्ठा tracing_map *map,
			      अचिन्हित पूर्णांक offset,
			      tracing_map_cmp_fn_t cmp_fn)

अणु
	पूर्णांक idx = tracing_map_add_field(map, cmp_fn);

	अगर (idx < 0)
		वापस idx;

	map->fields[idx].offset = offset;

	map->key_idx[map->n_keys++] = idx;

	वापस idx;
पूर्ण

अटल व्योम tracing_map_array_clear(काष्ठा tracing_map_array *a)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!a->pages)
		वापस;

	क्रम (i = 0; i < a->n_pages; i++)
		स_रखो(a->pages[i], 0, PAGE_SIZE);
पूर्ण

अटल व्योम tracing_map_array_मुक्त(काष्ठा tracing_map_array *a)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!a)
		वापस;

	अगर (!a->pages)
		जाओ मुक्त;

	क्रम (i = 0; i < a->n_pages; i++) अणु
		अगर (!a->pages[i])
			अवरोध;
		मुक्त_page((अचिन्हित दीर्घ)a->pages[i]);
	पूर्ण

	kमुक्त(a->pages);

 मुक्त:
	kमुक्त(a);
पूर्ण

अटल काष्ठा tracing_map_array *tracing_map_array_alloc(अचिन्हित पूर्णांक n_elts,
						  अचिन्हित पूर्णांक entry_size)
अणु
	काष्ठा tracing_map_array *a;
	अचिन्हित पूर्णांक i;

	a = kzalloc(माप(*a), GFP_KERNEL);
	अगर (!a)
		वापस शून्य;

	a->entry_size_shअगरt = fls(roundup_घात_of_two(entry_size) - 1);
	a->entries_per_page = PAGE_SIZE / (1 << a->entry_size_shअगरt);
	a->n_pages = n_elts / a->entries_per_page;
	अगर (!a->n_pages)
		a->n_pages = 1;
	a->entry_shअगरt = fls(a->entries_per_page) - 1;
	a->entry_mask = (1 << a->entry_shअगरt) - 1;

	a->pages = kसुस्मृति(a->n_pages, माप(व्योम *), GFP_KERNEL);
	अगर (!a->pages)
		जाओ मुक्त;

	क्रम (i = 0; i < a->n_pages; i++) अणु
		a->pages[i] = (व्योम *)get_zeroed_page(GFP_KERNEL);
		अगर (!a->pages[i])
			जाओ मुक्त;
	पूर्ण
 out:
	वापस a;
 मुक्त:
	tracing_map_array_मुक्त(a);
	a = शून्य;

	जाओ out;
पूर्ण

अटल व्योम tracing_map_elt_clear(काष्ठा tracing_map_elt *elt)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < elt->map->n_fields; i++)
		अगर (elt->fields[i].cmp_fn == tracing_map_cmp_atomic64)
			atomic64_set(&elt->fields[i].sum, 0);

	क्रम (i = 0; i < elt->map->n_vars; i++) अणु
		atomic64_set(&elt->vars[i], 0);
		elt->var_set[i] = false;
	पूर्ण

	अगर (elt->map->ops && elt->map->ops->elt_clear)
		elt->map->ops->elt_clear(elt);
पूर्ण

अटल व्योम tracing_map_elt_init_fields(काष्ठा tracing_map_elt *elt)
अणु
	अचिन्हित पूर्णांक i;

	tracing_map_elt_clear(elt);

	क्रम (i = 0; i < elt->map->n_fields; i++) अणु
		elt->fields[i].cmp_fn = elt->map->fields[i].cmp_fn;

		अगर (elt->fields[i].cmp_fn != tracing_map_cmp_atomic64)
			elt->fields[i].offset = elt->map->fields[i].offset;
	पूर्ण
पूर्ण

अटल व्योम tracing_map_elt_मुक्त(काष्ठा tracing_map_elt *elt)
अणु
	अगर (!elt)
		वापस;

	अगर (elt->map->ops && elt->map->ops->elt_मुक्त)
		elt->map->ops->elt_मुक्त(elt);
	kमुक्त(elt->fields);
	kमुक्त(elt->vars);
	kमुक्त(elt->var_set);
	kमुक्त(elt->key);
	kमुक्त(elt);
पूर्ण

अटल काष्ठा tracing_map_elt *tracing_map_elt_alloc(काष्ठा tracing_map *map)
अणु
	काष्ठा tracing_map_elt *elt;
	पूर्णांक err = 0;

	elt = kzalloc(माप(*elt), GFP_KERNEL);
	अगर (!elt)
		वापस ERR_PTR(-ENOMEM);

	elt->map = map;

	elt->key = kzalloc(map->key_size, GFP_KERNEL);
	अगर (!elt->key) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	elt->fields = kसुस्मृति(map->n_fields, माप(*elt->fields), GFP_KERNEL);
	अगर (!elt->fields) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	elt->vars = kसुस्मृति(map->n_vars, माप(*elt->vars), GFP_KERNEL);
	अगर (!elt->vars) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	elt->var_set = kसुस्मृति(map->n_vars, माप(*elt->var_set), GFP_KERNEL);
	अगर (!elt->var_set) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	tracing_map_elt_init_fields(elt);

	अगर (map->ops && map->ops->elt_alloc) अणु
		err = map->ops->elt_alloc(elt);
		अगर (err)
			जाओ मुक्त;
	पूर्ण
	वापस elt;
 मुक्त:
	tracing_map_elt_मुक्त(elt);

	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा tracing_map_elt *get_मुक्त_elt(काष्ठा tracing_map *map)
अणु
	काष्ठा tracing_map_elt *elt = शून्य;
	पूर्णांक idx;

	idx = atomic_inc_वापस(&map->next_elt);
	अगर (idx < map->max_elts) अणु
		elt = *(TRACING_MAP_ELT(map->elts, idx));
		अगर (map->ops && map->ops->elt_init)
			map->ops->elt_init(elt);
	पूर्ण

	वापस elt;
पूर्ण

अटल व्योम tracing_map_मुक्त_elts(काष्ठा tracing_map *map)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!map->elts)
		वापस;

	क्रम (i = 0; i < map->max_elts; i++) अणु
		tracing_map_elt_मुक्त(*(TRACING_MAP_ELT(map->elts, i)));
		*(TRACING_MAP_ELT(map->elts, i)) = शून्य;
	पूर्ण

	tracing_map_array_मुक्त(map->elts);
	map->elts = शून्य;
पूर्ण

अटल पूर्णांक tracing_map_alloc_elts(काष्ठा tracing_map *map)
अणु
	अचिन्हित पूर्णांक i;

	map->elts = tracing_map_array_alloc(map->max_elts,
					    माप(काष्ठा tracing_map_elt *));
	अगर (!map->elts)
		वापस -ENOMEM;

	क्रम (i = 0; i < map->max_elts; i++) अणु
		*(TRACING_MAP_ELT(map->elts, i)) = tracing_map_elt_alloc(map);
		अगर (IS_ERR(*(TRACING_MAP_ELT(map->elts, i)))) अणु
			*(TRACING_MAP_ELT(map->elts, i)) = शून्य;
			tracing_map_मुक्त_elts(map);

			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool keys_match(व्योम *key, व्योम *test_key, अचिन्हित key_size)
अणु
	bool match = true;

	अगर (स_भेद(key, test_key, key_size))
		match = false;

	वापस match;
पूर्ण

अटल अंतरभूत काष्ठा tracing_map_elt *
__tracing_map_insert(काष्ठा tracing_map *map, व्योम *key, bool lookup_only)
अणु
	u32 idx, key_hash, test_key;
	पूर्णांक dup_try = 0;
	काष्ठा tracing_map_entry *entry;
	काष्ठा tracing_map_elt *val;

	key_hash = jhash(key, map->key_size, 0);
	अगर (key_hash == 0)
		key_hash = 1;
	idx = key_hash >> (32 - (map->map_bits + 1));

	जबतक (1) अणु
		idx &= (map->map_size - 1);
		entry = TRACING_MAP_ENTRY(map->map, idx);
		test_key = entry->key;

		अगर (test_key && test_key == key_hash) अणु
			val = READ_ONCE(entry->val);
			अगर (val &&
			    keys_match(key, val->key, map->key_size)) अणु
				अगर (!lookup_only)
					atomic64_inc(&map->hits);
				वापस val;
			पूर्ण अन्यथा अगर (unlikely(!val)) अणु
				/*
				 * The key is present. But, val (poपूर्णांकer to elt
				 * काष्ठा) is still शून्य. which means some other
				 * thपढ़ो is in the process of inserting an
				 * element.
				 *
				 * On top of that, it's key_hash is same as the
				 * one being inserted right now. So, it's
				 * possible that the element has the same
				 * key as well.
				 */

				dup_try++;
				अगर (dup_try > map->map_size) अणु
					atomic64_inc(&map->drops);
					अवरोध;
				पूर्ण
				जारी;
			पूर्ण
		पूर्ण

		अगर (!test_key) अणु
			अगर (lookup_only)
				अवरोध;

			अगर (!cmpxchg(&entry->key, 0, key_hash)) अणु
				काष्ठा tracing_map_elt *elt;

				elt = get_मुक्त_elt(map);
				अगर (!elt) अणु
					atomic64_inc(&map->drops);
					entry->key = 0;
					अवरोध;
				पूर्ण

				स_नकल(elt->key, key, map->key_size);
				entry->val = elt;
				atomic64_inc(&map->hits);

				वापस entry->val;
			पूर्ण अन्यथा अणु
				/*
				 * cmpxchg() failed. Loop around once
				 * more to check what key was inserted.
				 */
				dup_try++;
				जारी;
			पूर्ण
		पूर्ण

		idx++;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * tracing_map_insert - Insert key and/or retrieve val from a tracing_map
 * @map: The tracing_map to insert पूर्णांकo
 * @key: The key to insert
 *
 * Inserts a key पूर्णांकo a tracing_map and creates and वापसs a new
 * tracing_map_elt क्रम it, or अगर the key has alपढ़ोy been inserted by
 * a previous call, वापसs the tracing_map_elt alपढ़ोy associated
 * with it.  When the map was created, the number of elements to be
 * allocated क्रम the map was specअगरied (पूर्णांकernally मुख्यtained as
 * 'max_elts' in काष्ठा tracing_map), and that number of
 * tracing_map_elts was created by tracing_map_init().  This is the
 * pre-allocated pool of tracing_map_elts that tracing_map_insert()
 * will allocate from when adding new keys.  Once that pool is
 * exhausted, tracing_map_insert() is useless and will वापस शून्य to
 * संकेत that state.  There are two user-visible tracing_map
 * variables, 'hits' and 'drops', which are updated by this function.
 * Every समय an element is either successfully inserted or retrieved,
 * the 'hits' value is incremented.  Every समय an element insertion
 * fails, the 'drops' value is incremented.
 *
 * This is a lock-मुक्त tracing map insertion function implementing a
 * modअगरied क्रमm of Clअगरf Click's basic insertion algorithm.  It
 * requires the table size be a घातer of two.  To prevent any
 * possibility of an infinite loop we always make the पूर्णांकernal table
 * size द्विगुन the size of the requested table size (max_elts * 2).
 * Likewise, we never reuse a slot or resize or delete elements - when
 * we've reached max_elts entries, we simply return NULL once we've
 * run out of entries.  Readers can at any poपूर्णांक in समय traverse the
 * tracing map and safely access the key/val pairs.
 *
 * Return: the tracing_map_elt poपूर्णांकer val associated with the key.
 * If this was a newly inserted key, the val will be a newly allocated
 * and associated tracing_map_elt poपूर्णांकer val.  If the key wasn't
 * found and the pool of tracing_map_elts has been exhausted, शून्य is
 * वापसed and no further insertions will succeed.
 */
काष्ठा tracing_map_elt *tracing_map_insert(काष्ठा tracing_map *map, व्योम *key)
अणु
	वापस __tracing_map_insert(map, key, false);
पूर्ण

/**
 * tracing_map_lookup - Retrieve val from a tracing_map
 * @map: The tracing_map to perक्रमm the lookup on
 * @key: The key to look up
 *
 * Looks up key in tracing_map and अगर found वापसs the matching
 * tracing_map_elt.  This is a lock-मुक्त lookup; see
 * tracing_map_insert() क्रम details on tracing_map and how it works.
 * Every समय an element is retrieved, the 'hits' value is
 * incremented.  There is one user-visible tracing_map variable,
 * 'hits', which is updated by this function.  Every समय an element
 * is successfully retrieved, the 'hits' value is incremented.  The
 * 'drops' value is never updated by this function.
 *
 * Return: the tracing_map_elt poपूर्णांकer val associated with the key.
 * If the key wasn't found, शून्य is वापसed.
 */
काष्ठा tracing_map_elt *tracing_map_lookup(काष्ठा tracing_map *map, व्योम *key)
अणु
	वापस __tracing_map_insert(map, key, true);
पूर्ण

/**
 * tracing_map_destroy - Destroy a tracing_map
 * @map: The tracing_map to destroy
 *
 * Frees a tracing_map aदीर्घ with its associated array of
 * tracing_map_elts.
 *
 * Callers should make sure there are no पढ़ोers or ग_लिखोrs actively
 * पढ़ोing or inserting पूर्णांकo the map beक्रमe calling this.
 */
व्योम tracing_map_destroy(काष्ठा tracing_map *map)
अणु
	अगर (!map)
		वापस;

	tracing_map_मुक्त_elts(map);

	tracing_map_array_मुक्त(map->map);
	kमुक्त(map);
पूर्ण

/**
 * tracing_map_clear - Clear a tracing_map
 * @map: The tracing_map to clear
 *
 * Resets the tracing map to a cleared or initial state.  The
 * tracing_map_elts are all cleared, and the array of काष्ठा
 * tracing_map_entry is reset to an initialized state.
 *
 * Callers should make sure there are no ग_लिखोrs actively inserting
 * पूर्णांकo the map beक्रमe calling this.
 */
व्योम tracing_map_clear(काष्ठा tracing_map *map)
अणु
	अचिन्हित पूर्णांक i;

	atomic_set(&map->next_elt, -1);
	atomic64_set(&map->hits, 0);
	atomic64_set(&map->drops, 0);

	tracing_map_array_clear(map->map);

	क्रम (i = 0; i < map->max_elts; i++)
		tracing_map_elt_clear(*(TRACING_MAP_ELT(map->elts, i)));
पूर्ण

अटल व्योम set_sort_key(काष्ठा tracing_map *map,
			 काष्ठा tracing_map_sort_key *sort_key)
अणु
	map->sort_key = *sort_key;
पूर्ण

/**
 * tracing_map_create - Create a lock-मुक्त map and element pool
 * @map_bits: The size of the map (2 ** map_bits)
 * @key_size: The size of the key क्रम the map in bytes
 * @ops: Optional client-defined tracing_map_ops instance
 * @निजी_data: Client data associated with the map
 *
 * Creates and sets up a map to contain 2 ** map_bits number of
 * elements (पूर्णांकernally मुख्यtained as 'max_elts' in काष्ठा
 * tracing_map).  Beक्रमe using, map fields should be added to the map
 * with tracing_map_add_sum_field() and tracing_map_add_key_field().
 * tracing_map_init() should then be called to allocate the array of
 * tracing_map_elts, in order to aव्योम allocating anything in the map
 * insertion path.  The user-specअगरied map size reflects the maximum
 * number of elements that can be contained in the table requested by
 * the user - पूर्णांकernally we द्विगुन that in order to keep the table
 * sparse and keep collisions manageable.
 *
 * A tracing_map is a special-purpose map deचिन्हित to aggregate or
 * 'sum' one or more values associated with a specअगरic object of type
 * tracing_map_elt, which is attached by the map to a given key.
 *
 * tracing_map_create() sets up the map itself, and provides
 * operations क्रम inserting tracing_map_elts, but करोesn't allocate the
 * tracing_map_elts themselves, or provide a means क्रम describing the
 * keys or sums associated with the tracing_map_elts.  All
 * tracing_map_elts क्रम a given map have the same set of sums and
 * keys, which are defined by the client using the functions
 * tracing_map_add_key_field() and tracing_map_add_sum_field().  Once
 * the fields are defined, the pool of elements allocated क्रम the map
 * can be created, which occurs when the client code calls
 * tracing_map_init().
 *
 * When tracing_map_init() वापसs, tracing_map_elt elements can be
 * inserted पूर्णांकo the map using tracing_map_insert().  When called,
 * tracing_map_insert() grअसल a मुक्त tracing_map_elt from the pool, or
 * finds an existing match in the map and in either हाल वापसs it.
 * The client can then use tracing_map_update_sum() and
 * tracing_map_पढ़ो_sum() to update or पढ़ो a given sum field क्रम the
 * tracing_map_elt.
 *
 * The client can at any poपूर्णांक retrieve and traverse the current set
 * of inserted tracing_map_elts in a tracing_map, via
 * tracing_map_sort_entries().  Sorting can be करोne on any field,
 * including keys.
 *
 * See tracing_map.h क्रम a description of tracing_map_ops.
 *
 * Return: the tracing_map poपूर्णांकer अगर successful, ERR_PTR अगर not.
 */
काष्ठा tracing_map *tracing_map_create(अचिन्हित पूर्णांक map_bits,
				       अचिन्हित पूर्णांक key_size,
				       स्थिर काष्ठा tracing_map_ops *ops,
				       व्योम *निजी_data)
अणु
	काष्ठा tracing_map *map;
	अचिन्हित पूर्णांक i;

	अगर (map_bits < TRACING_MAP_BITS_MIN ||
	    map_bits > TRACING_MAP_BITS_MAX)
		वापस ERR_PTR(-EINVAL);

	map = kzalloc(माप(*map), GFP_KERNEL);
	अगर (!map)
		वापस ERR_PTR(-ENOMEM);

	map->map_bits = map_bits;
	map->max_elts = (1 << map_bits);
	atomic_set(&map->next_elt, -1);

	map->map_size = (1 << (map_bits + 1));
	map->ops = ops;

	map->निजी_data = निजी_data;

	map->map = tracing_map_array_alloc(map->map_size,
					   माप(काष्ठा tracing_map_entry));
	अगर (!map->map)
		जाओ मुक्त;

	map->key_size = key_size;
	क्रम (i = 0; i < TRACING_MAP_KEYS_MAX; i++)
		map->key_idx[i] = -1;
 out:
	वापस map;
 मुक्त:
	tracing_map_destroy(map);
	map = ERR_PTR(-ENOMEM);

	जाओ out;
पूर्ण

/**
 * tracing_map_init - Allocate and clear a map's tracing_map_elts
 * @map: The tracing_map to initialize
 *
 * Allocates a clears a pool of tracing_map_elts equal to the
 * user-specअगरied size of 2 ** map_bits (पूर्णांकernally मुख्यtained as
 * 'max_elts' in काष्ठा tracing_map).  Beक्रमe using, the map fields
 * should be added to the map with tracing_map_add_sum_field() and
 * tracing_map_add_key_field().  tracing_map_init() should then be
 * called to allocate the array of tracing_map_elts, in order to aव्योम
 * allocating anything in the map insertion path.  The user-specअगरied
 * map size reflects the max number of elements requested by the user
 * - पूर्णांकernally we द्विगुन that in order to keep the table sparse and
 * keep collisions manageable.
 *
 * See tracing_map.h क्रम a description of tracing_map_ops.
 *
 * Return: the tracing_map poपूर्णांकer अगर successful, ERR_PTR अगर not.
 */
पूर्णांक tracing_map_init(काष्ठा tracing_map *map)
अणु
	पूर्णांक err;

	अगर (map->n_fields < 2)
		वापस -EINVAL; /* need at least 1 key and 1 val */

	err = tracing_map_alloc_elts(map);
	अगर (err)
		वापस err;

	tracing_map_clear(map);

	वापस err;
पूर्ण

अटल पूर्णांक cmp_entries_dup(स्थिर काष्ठा tracing_map_sort_entry **a,
			   स्थिर काष्ठा tracing_map_sort_entry **b)
अणु
	पूर्णांक ret = 0;

	अगर (स_भेद((*a)->key, (*b)->key, (*a)->elt->map->key_size))
		ret = 1;

	वापस ret;
पूर्ण

अटल पूर्णांक cmp_entries_sum(स्थिर काष्ठा tracing_map_sort_entry **a,
			   स्थिर काष्ठा tracing_map_sort_entry **b)
अणु
	स्थिर काष्ठा tracing_map_elt *elt_a, *elt_b;
	काष्ठा tracing_map_sort_key *sort_key;
	काष्ठा tracing_map_field *field;
	tracing_map_cmp_fn_t cmp_fn;
	व्योम *val_a, *val_b;
	पूर्णांक ret = 0;

	elt_a = (*a)->elt;
	elt_b = (*b)->elt;

	sort_key = &elt_a->map->sort_key;

	field = &elt_a->fields[sort_key->field_idx];
	cmp_fn = field->cmp_fn;

	val_a = &elt_a->fields[sort_key->field_idx].sum;
	val_b = &elt_b->fields[sort_key->field_idx].sum;

	ret = cmp_fn(val_a, val_b);
	अगर (sort_key->descending)
		ret = -ret;

	वापस ret;
पूर्ण

अटल पूर्णांक cmp_entries_key(स्थिर काष्ठा tracing_map_sort_entry **a,
			   स्थिर काष्ठा tracing_map_sort_entry **b)
अणु
	स्थिर काष्ठा tracing_map_elt *elt_a, *elt_b;
	काष्ठा tracing_map_sort_key *sort_key;
	काष्ठा tracing_map_field *field;
	tracing_map_cmp_fn_t cmp_fn;
	व्योम *val_a, *val_b;
	पूर्णांक ret = 0;

	elt_a = (*a)->elt;
	elt_b = (*b)->elt;

	sort_key = &elt_a->map->sort_key;

	field = &elt_a->fields[sort_key->field_idx];

	cmp_fn = field->cmp_fn;

	val_a = elt_a->key + field->offset;
	val_b = elt_b->key + field->offset;

	ret = cmp_fn(val_a, val_b);
	अगर (sort_key->descending)
		ret = -ret;

	वापस ret;
पूर्ण

अटल व्योम destroy_sort_entry(काष्ठा tracing_map_sort_entry *entry)
अणु
	अगर (!entry)
		वापस;

	अगर (entry->elt_copied)
		tracing_map_elt_मुक्त(entry->elt);

	kमुक्त(entry);
पूर्ण

/**
 * tracing_map_destroy_sort_entries - Destroy an array of sort entries
 * @entries: The entries to destroy
 * @n_entries: The number of entries in the array
 *
 * Destroy the elements वापसed by a tracing_map_sort_entries() call.
 */
व्योम tracing_map_destroy_sort_entries(काष्ठा tracing_map_sort_entry **entries,
				      अचिन्हित पूर्णांक n_entries)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < n_entries; i++)
		destroy_sort_entry(entries[i]);

	vमुक्त(entries);
पूर्ण

अटल काष्ठा tracing_map_sort_entry *
create_sort_entry(व्योम *key, काष्ठा tracing_map_elt *elt)
अणु
	काष्ठा tracing_map_sort_entry *sort_entry;

	sort_entry = kzalloc(माप(*sort_entry), GFP_KERNEL);
	अगर (!sort_entry)
		वापस शून्य;

	sort_entry->key = key;
	sort_entry->elt = elt;

	वापस sort_entry;
पूर्ण

अटल व्योम detect_dups(काष्ठा tracing_map_sort_entry **sort_entries,
		      पूर्णांक n_entries, अचिन्हित पूर्णांक key_size)
अणु
	अचिन्हित पूर्णांक dups = 0, total_dups = 0;
	पूर्णांक i;
	व्योम *key;

	अगर (n_entries < 2)
		वापस;

	sort(sort_entries, n_entries, माप(काष्ठा tracing_map_sort_entry *),
	     (पूर्णांक (*)(स्थिर व्योम *, स्थिर व्योम *))cmp_entries_dup, शून्य);

	key = sort_entries[0]->key;
	क्रम (i = 1; i < n_entries; i++) अणु
		अगर (!स_भेद(sort_entries[i]->key, key, key_size)) अणु
			dups++; total_dups++;
			जारी;
		पूर्ण
		key = sort_entries[i]->key;
		dups = 0;
	पूर्ण

	WARN_ONCE(total_dups > 0,
		  "Duplicates detected: %d\n", total_dups);
पूर्ण

अटल bool is_key(काष्ठा tracing_map *map, अचिन्हित पूर्णांक field_idx)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < map->n_keys; i++)
		अगर (map->key_idx[i] == field_idx)
			वापस true;
	वापस false;
पूर्ण

अटल व्योम sort_secondary(काष्ठा tracing_map *map,
			   स्थिर काष्ठा tracing_map_sort_entry **entries,
			   अचिन्हित पूर्णांक n_entries,
			   काष्ठा tracing_map_sort_key *primary_key,
			   काष्ठा tracing_map_sort_key *secondary_key)
अणु
	पूर्णांक (*primary_fn)(स्थिर काष्ठा tracing_map_sort_entry **,
			  स्थिर काष्ठा tracing_map_sort_entry **);
	पूर्णांक (*secondary_fn)(स्थिर काष्ठा tracing_map_sort_entry **,
			    स्थिर काष्ठा tracing_map_sort_entry **);
	अचिन्हित i, start = 0, n_sub = 1;

	अगर (is_key(map, primary_key->field_idx))
		primary_fn = cmp_entries_key;
	अन्यथा
		primary_fn = cmp_entries_sum;

	अगर (is_key(map, secondary_key->field_idx))
		secondary_fn = cmp_entries_key;
	अन्यथा
		secondary_fn = cmp_entries_sum;

	क्रम (i = 0; i < n_entries - 1; i++) अणु
		स्थिर काष्ठा tracing_map_sort_entry **a = &entries[i];
		स्थिर काष्ठा tracing_map_sort_entry **b = &entries[i + 1];

		अगर (primary_fn(a, b) == 0) अणु
			n_sub++;
			अगर (i < n_entries - 2)
				जारी;
		पूर्ण

		अगर (n_sub < 2) अणु
			start = i + 1;
			n_sub = 1;
			जारी;
		पूर्ण

		set_sort_key(map, secondary_key);
		sort(&entries[start], n_sub,
		     माप(काष्ठा tracing_map_sort_entry *),
		     (पूर्णांक (*)(स्थिर व्योम *, स्थिर व्योम *))secondary_fn, शून्य);
		set_sort_key(map, primary_key);

		start = i + 1;
		n_sub = 1;
	पूर्ण
पूर्ण

/**
 * tracing_map_sort_entries - Sort the current set of tracing_map_elts in a map
 * @map: The tracing_map
 * @sort_key: The sort key to use क्रम sorting
 * @sort_entries: outval: poपूर्णांकer to allocated and sorted array of entries
 *
 * tracing_map_sort_entries() sorts the current set of entries in the
 * map and वापसs the list of tracing_map_sort_entries containing
 * them to the client in the sort_entries param.  The client can
 * access the काष्ठा tracing_map_elt element of पूर्णांकerest directly as
 * the 'elt' field of a वापसed काष्ठा tracing_map_sort_entry object.
 *
 * The sort_key has only two fields: idx and descending.  'idx' refers
 * to the index of the field added via tracing_map_add_sum_field() or
 * tracing_map_add_key_field() when the tracing_map was initialized.
 * 'descending' is a flag that अगर set reverses the sort order, which
 * by शेष is ascending.
 *
 * The client should not hold on to the वापसed array but should use
 * it and call tracing_map_destroy_sort_entries() when करोne.
 *
 * Return: the number of sort_entries in the काष्ठा tracing_map_sort_entry
 * array, negative on error
 */
पूर्णांक tracing_map_sort_entries(काष्ठा tracing_map *map,
			     काष्ठा tracing_map_sort_key *sort_keys,
			     अचिन्हित पूर्णांक n_sort_keys,
			     काष्ठा tracing_map_sort_entry ***sort_entries)
अणु
	पूर्णांक (*cmp_entries_fn)(स्थिर काष्ठा tracing_map_sort_entry **,
			      स्थिर काष्ठा tracing_map_sort_entry **);
	काष्ठा tracing_map_sort_entry *sort_entry, **entries;
	पूर्णांक i, n_entries, ret;

	entries = vदो_स्मृति(array_size(माप(sort_entry), map->max_elts));
	अगर (!entries)
		वापस -ENOMEM;

	क्रम (i = 0, n_entries = 0; i < map->map_size; i++) अणु
		काष्ठा tracing_map_entry *entry;

		entry = TRACING_MAP_ENTRY(map->map, i);

		अगर (!entry->key || !entry->val)
			जारी;

		entries[n_entries] = create_sort_entry(entry->val->key,
						       entry->val);
		अगर (!entries[n_entries++]) अणु
			ret = -ENOMEM;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	अगर (n_entries == 0) अणु
		ret = 0;
		जाओ मुक्त;
	पूर्ण

	अगर (n_entries == 1) अणु
		*sort_entries = entries;
		वापस 1;
	पूर्ण

	detect_dups(entries, n_entries, map->key_size);

	अगर (is_key(map, sort_keys[0].field_idx))
		cmp_entries_fn = cmp_entries_key;
	अन्यथा
		cmp_entries_fn = cmp_entries_sum;

	set_sort_key(map, &sort_keys[0]);

	sort(entries, n_entries, माप(काष्ठा tracing_map_sort_entry *),
	     (पूर्णांक (*)(स्थिर व्योम *, स्थिर व्योम *))cmp_entries_fn, शून्य);

	अगर (n_sort_keys > 1)
		sort_secondary(map,
			       (स्थिर काष्ठा tracing_map_sort_entry **)entries,
			       n_entries,
			       &sort_keys[0],
			       &sort_keys[1]);

	*sort_entries = entries;

	वापस n_entries;
 मुक्त:
	tracing_map_destroy_sort_entries(entries, n_entries);

	वापस ret;
पूर्ण
