<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <माला.स>

#घोषणा VDSO__MAP_NAME "[vdso]"

/*
 * Include definition of find_map() also used in util/vdso.c क्रम
 * building perf.
 */
#समावेश "util/find-map.c"

पूर्णांक मुख्य(व्योम)
अणु
	व्योम *start, *end;
	माप_प्रकार size, written;

	अगर (find_map(&start, &end, VDSO__MAP_NAME))
		वापस 1;

	size = end - start;

	जबतक (size) अणु
		written = ख_डालो(start, 1, size, मानक_निकास);
		अगर (!written)
			वापस 1;
		start += written;
		size -= written;
	पूर्ण

	अगर (ख_साफ(मानक_निकास))
		वापस 1;

	वापस 0;
पूर्ण
