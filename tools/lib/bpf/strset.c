<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2021 Facebook */
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश "hashmap.h"
#समावेश "libbpf_internal.h"
#समावेश "strset.h"

काष्ठा strset अणु
	व्योम *strs_data;
	माप_प्रकार strs_data_len;
	माप_प्रकार strs_data_cap;
	माप_प्रकार strs_data_max_len;

	/* lookup index क्रम each unique string in strings set */
	काष्ठा hashmap *strs_hash;
पूर्ण;

अटल माप_प्रकार strset_hash_fn(स्थिर व्योम *key, व्योम *ctx)
अणु
	स्थिर काष्ठा strset *s = ctx;
	स्थिर अक्षर *str = s->strs_data + (दीर्घ)key;

	वापस str_hash(str);
पूर्ण

अटल bool strset_equal_fn(स्थिर व्योम *key1, स्थिर व्योम *key2, व्योम *ctx)
अणु
	स्थिर काष्ठा strset *s = ctx;
	स्थिर अक्षर *str1 = s->strs_data + (दीर्घ)key1;
	स्थिर अक्षर *str2 = s->strs_data + (दीर्घ)key2;

	वापस म_भेद(str1, str2) == 0;
पूर्ण

काष्ठा strset *strset__new(माप_प्रकार max_data_sz, स्थिर अक्षर *init_data, माप_प्रकार init_data_sz)
अणु
	काष्ठा strset *set = सुस्मृति(1, माप(*set));
	काष्ठा hashmap *hash;
	पूर्णांक err = -ENOMEM;

	अगर (!set)
		वापस ERR_PTR(-ENOMEM);

	hash = hashmap__new(strset_hash_fn, strset_equal_fn, set);
	अगर (IS_ERR(hash))
		जाओ err_out;

	set->strs_data_max_len = max_data_sz;
	set->strs_hash = hash;

	अगर (init_data) अणु
		दीर्घ off;

		set->strs_data = दो_स्मृति(init_data_sz);
		अगर (!set->strs_data)
			जाओ err_out;

		स_नकल(set->strs_data, init_data, init_data_sz);
		set->strs_data_len = init_data_sz;
		set->strs_data_cap = init_data_sz;

		क्रम (off = 0; off < set->strs_data_len; off += म_माप(set->strs_data + off) + 1) अणु
			/* hashmap__add() वापसs EEXIST अगर string with the same
			 * content alपढ़ोy is in the hash map
			 */
			err = hashmap__add(hash, (व्योम *)off, (व्योम *)off);
			अगर (err == -EEXIST)
				जारी; /* duplicate */
			अगर (err)
				जाओ err_out;
		पूर्ण
	पूर्ण

	वापस set;
err_out:
	strset__मुक्त(set);
	वापस ERR_PTR(err);
पूर्ण

व्योम strset__मुक्त(काष्ठा strset *set)
अणु
	अगर (IS_ERR_OR_शून्य(set))
		वापस;

	hashmap__मुक्त(set->strs_hash);
	मुक्त(set->strs_data);
पूर्ण

माप_प्रकार strset__data_size(स्थिर काष्ठा strset *set)
अणु
	वापस set->strs_data_len;
पूर्ण

स्थिर अक्षर *strset__data(स्थिर काष्ठा strset *set)
अणु
	वापस set->strs_data;
पूर्ण

अटल व्योम *strset_add_str_mem(काष्ठा strset *set, माप_प्रकार add_sz)
अणु
	वापस libbpf_add_mem(&set->strs_data, &set->strs_data_cap, 1,
			      set->strs_data_len, set->strs_data_max_len, add_sz);
पूर्ण

/* Find string offset that corresponds to a given string *s*.
 * Returns:
 *   - >0 offset पूर्णांकo string data, अगर string is found;
 *   - -ENOENT, अगर string is not in the string data;
 *   - <0, on any other error.
 */
पूर्णांक strset__find_str(काष्ठा strset *set, स्थिर अक्षर *s)
अणु
	दीर्घ old_off, new_off, len;
	व्योम *p;

	/* see strset__add_str() क्रम why we करो this */
	len = म_माप(s) + 1;
	p = strset_add_str_mem(set, len);
	अगर (!p)
		वापस -ENOMEM;

	new_off = set->strs_data_len;
	स_नकल(p, s, len);

	अगर (hashmap__find(set->strs_hash, (व्योम *)new_off, (व्योम **)&old_off))
		वापस old_off;

	वापस -ENOENT;
पूर्ण

/* Add a string s to the string data. If the string alपढ़ोy exists, वापस its
 * offset within string data.
 * Returns:
 *   - > 0 offset पूर्णांकo string data, on success;
 *   - < 0, on error.
 */
पूर्णांक strset__add_str(काष्ठा strset *set, स्थिर अक्षर *s)
अणु
	दीर्घ old_off, new_off, len;
	व्योम *p;
	पूर्णांक err;

	/* Hashmap keys are always offsets within set->strs_data, so to even
	 * look up some string from the "outside", we need to first append it
	 * at the end, so that it can be addressed with an offset. Luckily,
	 * until set->strs_data_len is incremented, that string is just a piece
	 * of garbage क्रम the rest of the code, so no harm, no foul. On the
	 * other hand, अगर the string is unique, it's alपढ़ोy appended and
	 * पढ़ोy to be used, only a simple set->strs_data_len increment away.
	 */
	len = म_माप(s) + 1;
	p = strset_add_str_mem(set, len);
	अगर (!p)
		वापस -ENOMEM;

	new_off = set->strs_data_len;
	स_नकल(p, s, len);

	/* Now attempt to add the string, but only अगर the string with the same
	 * contents करोesn't exist alपढ़ोy (HASHMAP_ADD strategy). If such
	 * string exists, we'll get its offset in old_off (that's old_key).
	 */
	err = hashmap__insert(set->strs_hash, (व्योम *)new_off, (व्योम *)new_off,
			      HASHMAP_ADD, (स्थिर व्योम **)&old_off, शून्य);
	अगर (err == -EEXIST)
		वापस old_off; /* duplicated string, वापस existing offset */
	अगर (err)
		वापस err;

	set->strs_data_len += len; /* new unique string, adjust data length */
	वापस new_off;
पूर्ण
