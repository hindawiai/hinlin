<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A fast, small, non-recursive O(n log n) sort क्रम the Linux kernel
 *
 * This perक्रमms n*log2(n) + 0.37*n + o(n) comparisons on average,
 * and 1.5*n*log2(n) + O(n) in the (very contrived) worst हाल.
 *
 * Glibc क्विक() manages n*log2(n) - 1.26*n क्रम अक्रमom inमाला_दो (1.63*n
 * better) at the expense of stack usage and much larger code to aव्योम
 * quicksort's O(n^2) worst हाल.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/sort.h>

/**
 * is_aligned - is this poपूर्णांकer & size okay क्रम word-wide copying?
 * @base: poपूर्णांकer to data
 * @size: size of each element
 * @align: required alignment (typically 4 or 8)
 *
 * Returns true अगर elements can be copied using word loads and stores.
 * The size must be a multiple of the alignment, and the base address must
 * be अगर we करो not have CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS.
 *
 * For some reason, gcc करोesn't know to optimize "if (a & mask || b & mask)"
 * to "if ((a | b) & mask)", so we करो that by hand.
 */
__attribute_स्थिर__ __always_अंतरभूत
अटल bool is_aligned(स्थिर व्योम *base, माप_प्रकार size, अचिन्हित अक्षर align)
अणु
	अचिन्हित अक्षर lsbits = (अचिन्हित अक्षर)size;

	(व्योम)base;
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	lsbits |= (अचिन्हित अक्षर)(uपूर्णांकptr_t)base;
#पूर्ण_अगर
	वापस (lsbits & (align - 1)) == 0;
पूर्ण

/**
 * swap_words_32 - swap two elements in 32-bit chunks
 * @a: poपूर्णांकer to the first element to swap
 * @b: poपूर्णांकer to the second element to swap
 * @n: element size (must be a multiple of 4)
 *
 * Exchange the two objects in memory.  This exploits base+index addressing,
 * which basically all CPUs have, to minimize loop overhead computations.
 *
 * For some reason, on x86 gcc 7.3.0 adds a redundant test of n at the
 * bottom of the loop, even though the zero flag is stil valid from the
 * subtract (since the पूर्णांकervening mov inकाष्ठाions करोn't alter the flags).
 * Gcc 8.1.0 करोesn't have that problem.
 */
अटल व्योम swap_words_32(व्योम *a, व्योम *b, माप_प्रकार n)
अणु
	करो अणु
		u32 t = *(u32 *)(a + (n -= 4));
		*(u32 *)(a + n) = *(u32 *)(b + n);
		*(u32 *)(b + n) = t;
	पूर्ण जबतक (n);
पूर्ण

/**
 * swap_words_64 - swap two elements in 64-bit chunks
 * @a: poपूर्णांकer to the first element to swap
 * @b: poपूर्णांकer to the second element to swap
 * @n: element size (must be a multiple of 8)
 *
 * Exchange the two objects in memory.  This exploits base+index
 * addressing, which basically all CPUs have, to minimize loop overhead
 * computations.
 *
 * We'd like to use 64-bit loads if possible.  If they're not, emulating
 * one requires base+index+4 addressing which x86 has but most other
 * processors करो not.  If CONFIG_64BIT, we definitely have 64-bit loads,
 * but it's possible to have 64-bit loads without 64-bit poपूर्णांकers (e.g.
 * x32 ABI).  Are there any हालs the kernel needs to worry about?
 */
अटल व्योम swap_words_64(व्योम *a, व्योम *b, माप_प्रकार n)
अणु
	करो अणु
#अगर_घोषित CONFIG_64BIT
		u64 t = *(u64 *)(a + (n -= 8));
		*(u64 *)(a + n) = *(u64 *)(b + n);
		*(u64 *)(b + n) = t;
#अन्यथा
		/* Use two 32-bit transfers to aव्योम base+index+4 addressing */
		u32 t = *(u32 *)(a + (n -= 4));
		*(u32 *)(a + n) = *(u32 *)(b + n);
		*(u32 *)(b + n) = t;

		t = *(u32 *)(a + (n -= 4));
		*(u32 *)(a + n) = *(u32 *)(b + n);
		*(u32 *)(b + n) = t;
#पूर्ण_अगर
	पूर्ण जबतक (n);
पूर्ण

/**
 * swap_bytes - swap two elements a byte at a समय
 * @a: poपूर्णांकer to the first element to swap
 * @b: poपूर्णांकer to the second element to swap
 * @n: element size
 *
 * This is the fallback अगर alignment करोesn't allow using larger chunks.
 */
अटल व्योम swap_bytes(व्योम *a, व्योम *b, माप_प्रकार n)
अणु
	करो अणु
		अक्षर t = ((अक्षर *)a)[--n];
		((अक्षर *)a)[n] = ((अक्षर *)b)[n];
		((अक्षर *)b)[n] = t;
	पूर्ण जबतक (n);
पूर्ण

/*
 * The values are arbitrary as दीर्घ as they can't be confused with
 * a poपूर्णांकer, but small पूर्णांकegers make क्रम the smallest compare
 * inकाष्ठाions.
 */
#घोषणा SWAP_WORDS_64 (swap_func_t)0
#घोषणा SWAP_WORDS_32 (swap_func_t)1
#घोषणा SWAP_BYTES    (swap_func_t)2

/*
 * The function poपूर्णांकer is last to make tail calls most efficient अगर the
 * compiler decides not to अंतरभूत this function.
 */
अटल व्योम करो_swap(व्योम *a, व्योम *b, माप_प्रकार size, swap_func_t swap_func)
अणु
	अगर (swap_func == SWAP_WORDS_64)
		swap_words_64(a, b, size);
	अन्यथा अगर (swap_func == SWAP_WORDS_32)
		swap_words_32(a, b, size);
	अन्यथा अगर (swap_func == SWAP_BYTES)
		swap_bytes(a, b, size);
	अन्यथा
		swap_func(a, b, (पूर्णांक)size);
पूर्ण

#घोषणा _CMP_WRAPPER ((cmp_r_func_t)0L)

अटल पूर्णांक करो_cmp(स्थिर व्योम *a, स्थिर व्योम *b, cmp_r_func_t cmp, स्थिर व्योम *priv)
अणु
	अगर (cmp == _CMP_WRAPPER)
		वापस ((cmp_func_t)(priv))(a, b);
	वापस cmp(a, b, priv);
पूर्ण

/**
 * parent - given the offset of the child, find the offset of the parent.
 * @i: the offset of the heap element whose parent is sought.  Non-zero.
 * @lsbit: a precomputed 1-bit mask, equal to "size & -size"
 * @size: size of each element
 *
 * In terms of array indexes, the parent of element j = @i/@size is simply
 * (j-1)/2.  But when working in byte offsets, we can't use implicit
 * truncation of पूर्णांकeger भागides.
 *
 * Fortunately, we only need one bit of the quotient, not the full भागide.
 * @size has a least signअगरicant bit.  That bit will be clear अगर @i is
 * an even multiple of @size, and set अगर it's an odd multiple.
 *
 * Logically, we're करोing "if (i & lsbit) i -= size;", but since the
 * branch is unpredictable, it's करोne with a bit of clever branch-मुक्त
 * code instead.
 */
__attribute_स्थिर__ __always_अंतरभूत
अटल माप_प्रकार parent(माप_प्रकार i, अचिन्हित पूर्णांक lsbit, माप_प्रकार size)
अणु
	i -= size;
	i -= size & -(i & lsbit);
	वापस i / 2;
पूर्ण

/**
 * sort_r - sort an array of elements
 * @base: poपूर्णांकer to data to sort
 * @num: number of elements
 * @size: size of each element
 * @cmp_func: poपूर्णांकer to comparison function
 * @swap_func: poपूर्णांकer to swap function or शून्य
 * @priv: third argument passed to comparison function
 *
 * This function करोes a heapsort on the given array.  You may provide
 * a swap_func function अगर you need to करो something more than a memory
 * copy (e.g. fix up poपूर्णांकers or auxiliary data), but the built-in swap
 * aव्योमs a slow retpoline and so is signअगरicantly faster.
 *
 * Sorting समय is O(n log n) both on average and worst-हाल. While
 * quicksort is slightly faster on average, it suffers from exploitable
 * O(n*n) worst-हाल behavior and extra memory requirements that make
 * it less suitable क्रम kernel use.
 */
व्योम sort_r(व्योम *base, माप_प्रकार num, माप_प्रकार size,
	    cmp_r_func_t cmp_func,
	    swap_func_t swap_func,
	    स्थिर व्योम *priv)
अणु
	/* pre-scale counters क्रम perक्रमmance */
	माप_प्रकार n = num * size, a = (num/2) * size;
	स्थिर अचिन्हित पूर्णांक lsbit = size & -size;  /* Used to find parent */

	अगर (!a)		/* num < 2 || size == 0 */
		वापस;

	अगर (!swap_func) अणु
		अगर (is_aligned(base, size, 8))
			swap_func = SWAP_WORDS_64;
		अन्यथा अगर (is_aligned(base, size, 4))
			swap_func = SWAP_WORDS_32;
		अन्यथा
			swap_func = SWAP_BYTES;
	पूर्ण

	/*
	 * Loop invariants:
	 * 1. elements [a,n) satisfy the heap property (compare greater than
	 *    all of their children),
	 * 2. elements [n,num*size) are sorted, and
	 * 3. a <= b <= c <= d <= n (whenever they are valid).
	 */
	क्रम (;;) अणु
		माप_प्रकार b, c, d;

		अगर (a)			/* Building heap: sअगरt करोwn --a */
			a -= size;
		अन्यथा अगर (n -= size)	/* Sorting: Extract root to --n */
			करो_swap(base, base + n, size, swap_func);
		अन्यथा			/* Sort complete */
			अवरोध;

		/*
		 * Sअगरt element at "a" करोwn पूर्णांकo heap.  This is the
		 * "bottom-up" variant, which signअगरicantly reduces
		 * calls to cmp_func(): we find the sअगरt-करोwn path all
		 * the way to the leaves (one compare per level), then
		 * backtrack to find where to insert the target element.
		 *
		 * Because elements tend to sअगरt करोwn बंद to the leaves,
		 * this uses fewer compares than करोing two per level
		 * on the way करोwn.  (A bit more than half as many on
		 * average, 3/4 worst-हाल.)
		 */
		क्रम (b = a; c = 2*b + size, (d = c + size) < n;)
			b = करो_cmp(base + c, base + d, cmp_func, priv) >= 0 ? c : d;
		अगर (d == n)	/* Special हाल last leaf with no sibling */
			b = c;

		/* Now backtrack from "b" to the correct location क्रम "a" */
		जबतक (b != a && करो_cmp(base + a, base + b, cmp_func, priv) >= 0)
			b = parent(b, lsbit, size);
		c = b;			/* Where "a" beदीर्घs */
		जबतक (b != a) अणु	/* Shअगरt it पूर्णांकo place */
			b = parent(b, lsbit, size);
			करो_swap(base + b, base + c, size, swap_func);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(sort_r);

व्योम sort(व्योम *base, माप_प्रकार num, माप_प्रकार size,
	  cmp_func_t cmp_func,
	  swap_func_t swap_func)
अणु
	वापस sort_r(base, num, size, _CMP_WRAPPER, swap_func, cmp_func);
पूर्ण
EXPORT_SYMBOL(sort);
