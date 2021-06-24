<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Range add and subtract
 */
#समावेश <linux/init.h>
#समावेश <linux/minmax.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sort.h>
#समावेश <linux/माला.स>
#समावेश <linux/range.h>

पूर्णांक add_range(काष्ठा range *range, पूर्णांक az, पूर्णांक nr_range, u64 start, u64 end)
अणु
	अगर (start >= end)
		वापस nr_range;

	/* Out of slots: */
	अगर (nr_range >= az)
		वापस nr_range;

	range[nr_range].start = start;
	range[nr_range].end = end;

	nr_range++;

	वापस nr_range;
पूर्ण

पूर्णांक add_range_with_merge(काष्ठा range *range, पूर्णांक az, पूर्णांक nr_range,
		     u64 start, u64 end)
अणु
	पूर्णांक i;

	अगर (start >= end)
		वापस nr_range;

	/* get new start/end: */
	क्रम (i = 0; i < nr_range; i++) अणु
		u64 common_start, common_end;

		अगर (!range[i].end)
			जारी;

		common_start = max(range[i].start, start);
		common_end = min(range[i].end, end);
		अगर (common_start > common_end)
			जारी;

		/* new start/end, will add it back at last */
		start = min(range[i].start, start);
		end = max(range[i].end, end);

		स_हटाओ(&range[i], &range[i + 1],
			(nr_range - (i + 1)) * माप(range[i]));
		range[nr_range - 1].start = 0;
		range[nr_range - 1].end   = 0;
		nr_range--;
		i--;
	पूर्ण

	/* Need to add it: */
	वापस add_range(range, az, nr_range, start, end);
पूर्ण

व्योम subtract_range(काष्ठा range *range, पूर्णांक az, u64 start, u64 end)
अणु
	पूर्णांक i, j;

	अगर (start >= end)
		वापस;

	क्रम (j = 0; j < az; j++) अणु
		अगर (!range[j].end)
			जारी;

		अगर (start <= range[j].start && end >= range[j].end) अणु
			range[j].start = 0;
			range[j].end = 0;
			जारी;
		पूर्ण

		अगर (start <= range[j].start && end < range[j].end &&
		    range[j].start < end) अणु
			range[j].start = end;
			जारी;
		पूर्ण


		अगर (start > range[j].start && end >= range[j].end &&
		    range[j].end > start) अणु
			range[j].end = start;
			जारी;
		पूर्ण

		अगर (start > range[j].start && end < range[j].end) अणु
			/* Find the new spare: */
			क्रम (i = 0; i < az; i++) अणु
				अगर (range[i].end == 0)
					अवरोध;
			पूर्ण
			अगर (i < az) अणु
				range[i].end = range[j].end;
				range[i].start = end;
			पूर्ण अन्यथा अणु
				pr_err("%s: run out of slot in ranges\n",
					__func__);
			पूर्ण
			range[j].end = start;
			जारी;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक cmp_range(स्थिर व्योम *x1, स्थिर व्योम *x2)
अणु
	स्थिर काष्ठा range *r1 = x1;
	स्थिर काष्ठा range *r2 = x2;

	अगर (r1->start < r2->start)
		वापस -1;
	अगर (r1->start > r2->start)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक clean_sort_range(काष्ठा range *range, पूर्णांक az)
अणु
	पूर्णांक i, j, k = az - 1, nr_range = az;

	क्रम (i = 0; i < k; i++) अणु
		अगर (range[i].end)
			जारी;
		क्रम (j = k; j > i; j--) अणु
			अगर (range[j].end) अणु
				k = j;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (j == i)
			अवरोध;
		range[i].start = range[k].start;
		range[i].end   = range[k].end;
		range[k].start = 0;
		range[k].end   = 0;
		k--;
	पूर्ण
	/* count it */
	क्रम (i = 0; i < az; i++) अणु
		अगर (!range[i].end) अणु
			nr_range = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* sort them */
	sort(range, nr_range, माप(काष्ठा range), cmp_range, शून्य);

	वापस nr_range;
पूर्ण

व्योम sort_range(काष्ठा range *range, पूर्णांक nr_range)
अणु
	/* sort them */
	sort(range, nr_range, माप(काष्ठा range), cmp_range, शून्य);
पूर्ण
