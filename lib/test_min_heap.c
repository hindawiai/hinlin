<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) "min_heap_test: " fmt

/*
 * Test हालs क्रम the min max heap.
 */

#समावेश <linux/log2.h>
#समावेश <linux/min_heap.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/अक्रमom.h>

अटल __init bool less_than(स्थिर व्योम *lhs, स्थिर व्योम *rhs)
अणु
	वापस *(पूर्णांक *)lhs < *(पूर्णांक *)rhs;
पूर्ण

अटल __init bool greater_than(स्थिर व्योम *lhs, स्थिर व्योम *rhs)
अणु
	वापस *(पूर्णांक *)lhs > *(पूर्णांक *)rhs;
पूर्ण

अटल __init व्योम swap_पूर्णांकs(व्योम *lhs, व्योम *rhs)
अणु
	पूर्णांक temp = *(पूर्णांक *)lhs;

	*(पूर्णांक *)lhs = *(पूर्णांक *)rhs;
	*(पूर्णांक *)rhs = temp;
पूर्ण

अटल __init पूर्णांक pop_verअगरy_heap(bool min_heap,
				काष्ठा min_heap *heap,
				स्थिर काष्ठा min_heap_callbacks *funcs)
अणु
	पूर्णांक *values = heap->data;
	पूर्णांक err = 0;
	पूर्णांक last;

	last = values[0];
	min_heap_pop(heap, funcs);
	जबतक (heap->nr > 0) अणु
		अगर (min_heap) अणु
			अगर (last > values[0]) अणु
				pr_err("error: expected %d <= %d\n", last,
					values[0]);
				err++;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (last < values[0]) अणु
				pr_err("error: expected %d >= %d\n", last,
					values[0]);
				err++;
			पूर्ण
		पूर्ण
		last = values[0];
		min_heap_pop(heap, funcs);
	पूर्ण
	वापस err;
पूर्ण

अटल __init पूर्णांक test_heapअगरy_all(bool min_heap)
अणु
	पूर्णांक values[] = अणु 3, 1, 2, 4, 0x8000000, 0x7FFFFFF, 0,
			 -3, -1, -2, -4, 0x8000000, 0x7FFFFFF पूर्ण;
	काष्ठा min_heap heap = अणु
		.data = values,
		.nr = ARRAY_SIZE(values),
		.size =  ARRAY_SIZE(values),
	पूर्ण;
	काष्ठा min_heap_callbacks funcs = अणु
		.elem_size = माप(पूर्णांक),
		.less = min_heap ? less_than : greater_than,
		.swp = swap_पूर्णांकs,
	पूर्ण;
	पूर्णांक i, err;

	/* Test with known set of values. */
	min_heapअगरy_all(&heap, &funcs);
	err = pop_verअगरy_heap(min_heap, &heap, &funcs);


	/* Test with अक्रमomly generated values. */
	heap.nr = ARRAY_SIZE(values);
	क्रम (i = 0; i < heap.nr; i++)
		values[i] = get_अक्रमom_पूर्णांक();

	min_heapअगरy_all(&heap, &funcs);
	err += pop_verअगरy_heap(min_heap, &heap, &funcs);

	वापस err;
पूर्ण

अटल __init पूर्णांक test_heap_push(bool min_heap)
अणु
	स्थिर पूर्णांक data[] = अणु 3, 1, 2, 4, 0x80000000, 0x7FFFFFFF, 0,
			     -3, -1, -2, -4, 0x80000000, 0x7FFFFFFF पूर्ण;
	पूर्णांक values[ARRAY_SIZE(data)];
	काष्ठा min_heap heap = अणु
		.data = values,
		.nr = 0,
		.size =  ARRAY_SIZE(values),
	पूर्ण;
	काष्ठा min_heap_callbacks funcs = अणु
		.elem_size = माप(पूर्णांक),
		.less = min_heap ? less_than : greater_than,
		.swp = swap_पूर्णांकs,
	पूर्ण;
	पूर्णांक i, temp, err;

	/* Test with known set of values copied from data. */
	क्रम (i = 0; i < ARRAY_SIZE(data); i++)
		min_heap_push(&heap, &data[i], &funcs);

	err = pop_verअगरy_heap(min_heap, &heap, &funcs);

	/* Test with अक्रमomly generated values. */
	जबतक (heap.nr < heap.size) अणु
		temp = get_अक्रमom_पूर्णांक();
		min_heap_push(&heap, &temp, &funcs);
	पूर्ण
	err += pop_verअगरy_heap(min_heap, &heap, &funcs);

	वापस err;
पूर्ण

अटल __init पूर्णांक test_heap_pop_push(bool min_heap)
अणु
	स्थिर पूर्णांक data[] = अणु 3, 1, 2, 4, 0x80000000, 0x7FFFFFFF, 0,
			     -3, -1, -2, -4, 0x80000000, 0x7FFFFFFF पूर्ण;
	पूर्णांक values[ARRAY_SIZE(data)];
	काष्ठा min_heap heap = अणु
		.data = values,
		.nr = 0,
		.size =  ARRAY_SIZE(values),
	पूर्ण;
	काष्ठा min_heap_callbacks funcs = अणु
		.elem_size = माप(पूर्णांक),
		.less = min_heap ? less_than : greater_than,
		.swp = swap_पूर्णांकs,
	पूर्ण;
	पूर्णांक i, temp, err;

	/* Fill values with data to pop and replace. */
	temp = min_heap ? 0x80000000 : 0x7FFFFFFF;
	क्रम (i = 0; i < ARRAY_SIZE(data); i++)
		min_heap_push(&heap, &temp, &funcs);

	/* Test with known set of values copied from data. */
	क्रम (i = 0; i < ARRAY_SIZE(data); i++)
		min_heap_pop_push(&heap, &data[i], &funcs);

	err = pop_verअगरy_heap(min_heap, &heap, &funcs);

	heap.nr = 0;
	क्रम (i = 0; i < ARRAY_SIZE(data); i++)
		min_heap_push(&heap, &temp, &funcs);

	/* Test with अक्रमomly generated values. */
	क्रम (i = 0; i < ARRAY_SIZE(data); i++) अणु
		temp = get_अक्रमom_पूर्णांक();
		min_heap_pop_push(&heap, &temp, &funcs);
	पूर्ण
	err += pop_verअगरy_heap(min_heap, &heap, &funcs);

	वापस err;
पूर्ण

अटल पूर्णांक __init test_min_heap_init(व्योम)
अणु
	पूर्णांक err = 0;

	err += test_heapअगरy_all(true);
	err += test_heapअगरy_all(false);
	err += test_heap_push(true);
	err += test_heap_push(false);
	err += test_heap_pop_push(true);
	err += test_heap_pop_push(false);
	अगर (err) अणु
		pr_err("test failed with %d errors\n", err);
		वापस -EINVAL;
	पूर्ण
	pr_info("test passed\n");
	वापस 0;
पूर्ण
module_init(test_min_heap_init);

अटल व्योम __निकास test_min_heap_निकास(व्योम)
अणु
	/* करो nothing */
पूर्ण
module_निकास(test_min_heap_निकास);

MODULE_LICENSE("GPL");
