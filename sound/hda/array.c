<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * generic arrays
 */

#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/hdaudपन.स>

/**
 * snd_array_new - get a new element from the given array
 * @array: the array object
 *
 * Get a new element from the given array.  If it exceeds the
 * pre-allocated array size, re-allocate the array.
 *
 * Returns शून्य अगर allocation failed.
 */
व्योम *snd_array_new(काष्ठा snd_array *array)
अणु
	अगर (snd_BUG_ON(!array->elem_size))
		वापस शून्य;
	अगर (array->used >= array->alloced) अणु
		पूर्णांक num = array->alloced + array->alloc_align;
		पूर्णांक oldsize = array->alloced * array->elem_size;
		पूर्णांक size = (num + 1) * array->elem_size;
		व्योम *nlist;
		अगर (snd_BUG_ON(num >= 4096))
			वापस शून्य;
		nlist = kपुनः_स्मृति(array->list, size, GFP_KERNEL);
		अगर (!nlist)
			वापस शून्य;
		स_रखो(nlist + oldsize, 0, size - oldsize);
		array->list = nlist;
		array->alloced = num;
	पूर्ण
	वापस snd_array_elem(array, array->used++);
पूर्ण
EXPORT_SYMBOL_GPL(snd_array_new);

/**
 * snd_array_मुक्त - मुक्त the given array elements
 * @array: the array object
 */
व्योम snd_array_मुक्त(काष्ठा snd_array *array)
अणु
	kमुक्त(array->list);
	array->used = 0;
	array->alloced = 0;
	array->list = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_array_मुक्त);
