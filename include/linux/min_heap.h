<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MIN_HEAP_H
#घोषणा _LINUX_MIN_HEAP_H

#समावेश <linux/bug.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

/**
 * काष्ठा min_heap - Data काष्ठाure to hold a min-heap.
 * @data: Start of array holding the heap elements.
 * @nr: Number of elements currently in the heap.
 * @size: Maximum number of elements that can be held in current storage.
 */
काष्ठा min_heap अणु
	व्योम *data;
	पूर्णांक nr;
	पूर्णांक size;
पूर्ण;

/**
 * काष्ठा min_heap_callbacks - Data/functions to customise the min_heap.
 * @elem_size: The nr of each element in bytes.
 * @less: Partial order function क्रम this heap.
 * @swp: Swap elements function.
 */
काष्ठा min_heap_callbacks अणु
	पूर्णांक elem_size;
	bool (*less)(स्थिर व्योम *lhs, स्थिर व्योम *rhs);
	व्योम (*swp)(व्योम *lhs, व्योम *rhs);
पूर्ण;

/* Sअगरt the element at pos करोwn the heap. */
अटल __always_अंतरभूत
व्योम min_heapअगरy(काष्ठा min_heap *heap, पूर्णांक pos,
		स्थिर काष्ठा min_heap_callbacks *func)
अणु
	व्योम *left, *right, *parent, *smallest;
	व्योम *data = heap->data;

	क्रम (;;) अणु
		अगर (pos * 2 + 1 >= heap->nr)
			अवरोध;

		left = data + ((pos * 2 + 1) * func->elem_size);
		parent = data + (pos * func->elem_size);
		smallest = parent;
		अगर (func->less(left, smallest))
			smallest = left;

		अगर (pos * 2 + 2 < heap->nr) अणु
			right = data + ((pos * 2 + 2) * func->elem_size);
			अगर (func->less(right, smallest))
				smallest = right;
		पूर्ण
		अगर (smallest == parent)
			अवरोध;
		func->swp(smallest, parent);
		अगर (smallest == left)
			pos = (pos * 2) + 1;
		अन्यथा
			pos = (pos * 2) + 2;
	पूर्ण
पूर्ण

/* Floyd's approach to heapअगरication that is O(nr). */
अटल __always_अंतरभूत
व्योम min_heapअगरy_all(काष्ठा min_heap *heap,
		स्थिर काष्ठा min_heap_callbacks *func)
अणु
	पूर्णांक i;

	क्रम (i = heap->nr / 2; i >= 0; i--)
		min_heapअगरy(heap, i, func);
पूर्ण

/* Remove minimum element from the heap, O(log2(nr)). */
अटल __always_अंतरभूत
व्योम min_heap_pop(काष्ठा min_heap *heap,
		स्थिर काष्ठा min_heap_callbacks *func)
अणु
	व्योम *data = heap->data;

	अगर (WARN_ONCE(heap->nr <= 0, "Popping an empty heap"))
		वापस;

	/* Place last element at the root (position 0) and then sअगरt करोwn. */
	heap->nr--;
	स_नकल(data, data + (heap->nr * func->elem_size), func->elem_size);
	min_heapअगरy(heap, 0, func);
पूर्ण

/*
 * Remove the minimum element and then push the given element. The
 * implementation perक्रमms 1 sअगरt (O(log2(nr))) and is thereक्रमe more
 * efficient than a pop followed by a push that करोes 2.
 */
अटल __always_अंतरभूत
व्योम min_heap_pop_push(काष्ठा min_heap *heap,
		स्थिर व्योम *element,
		स्थिर काष्ठा min_heap_callbacks *func)
अणु
	स_नकल(heap->data, element, func->elem_size);
	min_heapअगरy(heap, 0, func);
पूर्ण

/* Push an element on to the heap, O(log2(nr)). */
अटल __always_अंतरभूत
व्योम min_heap_push(काष्ठा min_heap *heap, स्थिर व्योम *element,
		स्थिर काष्ठा min_heap_callbacks *func)
अणु
	व्योम *data = heap->data;
	व्योम *child, *parent;
	पूर्णांक pos;

	अगर (WARN_ONCE(heap->nr >= heap->size, "Pushing on a full heap"))
		वापस;

	/* Place at the end of data. */
	pos = heap->nr;
	स_नकल(data + (pos * func->elem_size), element, func->elem_size);
	heap->nr++;

	/* Sअगरt child at pos up. */
	क्रम (; pos > 0; pos = (pos - 1) / 2) अणु
		child = data + (pos * func->elem_size);
		parent = data + ((pos - 1) / 2) * func->elem_size;
		अगर (func->less(parent, child))
			अवरोध;
		func->swp(parent, child);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* _LINUX_MIN_HEAP_H */
