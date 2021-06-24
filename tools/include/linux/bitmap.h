<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_BITOPS_H
#घोषणा _PERF_BITOPS_H

#समावेश <माला.स>
#समावेश <linux/bitops.h>
#समावेश <मानककोष.स>
#समावेश <linux/kernel.h>

#घोषणा DECLARE_BITMAP(name,bits) \
	अचिन्हित दीर्घ name[BITS_TO_LONGS(bits)]

पूर्णांक __biपंचांगap_weight(स्थिर अचिन्हित दीर्घ *biपंचांगap, पूर्णांक bits);
व्योम __biपंचांगap_or(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		 स्थिर अचिन्हित दीर्घ *biपंचांगap2, पूर्णांक bits);
पूर्णांक __biपंचांगap_and(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		 स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits);
पूर्णांक __biपंचांगap_equal(स्थिर अचिन्हित दीर्घ *biपंचांगap1,
		   स्थिर अचिन्हित दीर्घ *biपंचांगap2, अचिन्हित पूर्णांक bits);
व्योम biपंचांगap_clear(अचिन्हित दीर्घ *map, अचिन्हित पूर्णांक start, पूर्णांक len);

#घोषणा BITMAP_FIRST_WORD_MASK(start) (~0UL << ((start) & (BITS_PER_LONG - 1)))
#घोषणा BITMAP_LAST_WORD_MASK(nbits) (~0UL >> (-(nbits) & (BITS_PER_LONG - 1)))

अटल अंतरभूत व्योम biपंचांगap_zero(अचिन्हित दीर्घ *dst, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		*dst = 0UL;
	अन्यथा अणु
		पूर्णांक len = BITS_TO_LONGS(nbits) * माप(अचिन्हित दीर्घ);
		स_रखो(dst, 0, len);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_fill(अचिन्हित दीर्घ *dst, अचिन्हित पूर्णांक nbits)
अणु
	अचिन्हित पूर्णांक nदीर्घs = BITS_TO_LONGS(nbits);
	अगर (!small_स्थिर_nbits(nbits)) अणु
		अचिन्हित पूर्णांक len = (nदीर्घs - 1) * माप(अचिन्हित दीर्घ);
		स_रखो(dst, 0xff,  len);
	पूर्ण
	dst[nदीर्घs - 1] = BITMAP_LAST_WORD_MASK(nbits);
पूर्ण

अटल अंतरभूत पूर्णांक biपंचांगap_empty(स्थिर अचिन्हित दीर्घ *src, अचिन्हित nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस ! (*src & BITMAP_LAST_WORD_MASK(nbits));

	वापस find_first_bit(src, nbits) == nbits;
पूर्ण

अटल अंतरभूत पूर्णांक biपंचांगap_full(स्थिर अचिन्हित दीर्घ *src, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस ! (~(*src) & BITMAP_LAST_WORD_MASK(nbits));

	वापस find_first_zero_bit(src, nbits) == nbits;
पूर्ण

अटल अंतरभूत पूर्णांक biपंचांगap_weight(स्थिर अचिन्हित दीर्घ *src, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस hweight_दीर्घ(*src & BITMAP_LAST_WORD_MASK(nbits));
	वापस __biपंचांगap_weight(src, nbits);
पूर्ण

अटल अंतरभूत व्योम biपंचांगap_or(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src1,
			     स्थिर अचिन्हित दीर्घ *src2, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		*dst = *src1 | *src2;
	अन्यथा
		__biपंचांगap_or(dst, src1, src2, nbits);
पूर्ण

/**
 * test_and_set_bit - Set a bit and वापस its old value
 * @nr: Bit to set
 * @addr: Address to count from
 */
अटल अंतरभूत पूर्णांक test_and_set_bit(पूर्णांक nr, अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ old;

	old = *p;
	*p = old | mask;

	वापस (old & mask) != 0;
पूर्ण

/**
 * test_and_clear_bit - Clear a bit and वापस its old value
 * @nr: Bit to clear
 * @addr: Address to count from
 */
अटल अंतरभूत पूर्णांक test_and_clear_bit(पूर्णांक nr, अचिन्हित दीर्घ *addr)
अणु
	अचिन्हित दीर्घ mask = BIT_MASK(nr);
	अचिन्हित दीर्घ *p = ((अचिन्हित दीर्घ *)addr) + BIT_WORD(nr);
	अचिन्हित दीर्घ old;

	old = *p;
	*p = old & ~mask;

	वापस (old & mask) != 0;
पूर्ण

/**
 * biपंचांगap_alloc - Allocate biपंचांगap
 * @nbits: Number of bits
 */
अटल अंतरभूत अचिन्हित दीर्घ *biपंचांगap_alloc(पूर्णांक nbits)
अणु
	वापस सुस्मृति(1, BITS_TO_LONGS(nbits) * माप(अचिन्हित दीर्घ));
पूर्ण

/*
 * biपंचांगap_मुक्त - Free biपंचांगap
 * @biपंचांगap: poपूर्णांकer to biपंचांगap
 */
अटल अंतरभूत व्योम biपंचांगap_मुक्त(अचिन्हित दीर्घ *biपंचांगap)
अणु
	मुक्त(biपंचांगap);
पूर्ण

/*
 * biपंचांगap_scnम_लिखो - prपूर्णांक biपंचांगap list पूर्णांकo buffer
 * @biपंचांगap: biपंचांगap
 * @nbits: size of biपंचांगap
 * @buf: buffer to store output
 * @size: size of @buf
 */
माप_प्रकार biपंचांगap_scnम_लिखो(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक nbits,
			अक्षर *buf, माप_प्रकार size);

/**
 * biपंचांगap_and - Do logical and on biपंचांगaps
 * @dst: resulting biपंचांगap
 * @src1: opeअक्रम 1
 * @src2: opeअक्रम 2
 * @nbits: size of biपंचांगap
 */
अटल अंतरभूत पूर्णांक biपंचांगap_and(अचिन्हित दीर्घ *dst, स्थिर अचिन्हित दीर्घ *src1,
			     स्थिर अचिन्हित दीर्घ *src2, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस (*dst = *src1 & *src2 & BITMAP_LAST_WORD_MASK(nbits)) != 0;
	वापस __biपंचांगap_and(dst, src1, src2, nbits);
पूर्ण

#अगर_घोषित __LITTLE_ENDIAN
#घोषणा BITMAP_MEM_ALIGNMENT 8
#अन्यथा
#घोषणा BITMAP_MEM_ALIGNMENT (8 * माप(अचिन्हित दीर्घ))
#पूर्ण_अगर
#घोषणा BITMAP_MEM_MASK (BITMAP_MEM_ALIGNMENT - 1)
#घोषणा IS_ALIGNED(x, a) (((x) & ((typeof(x))(a) - 1)) == 0)

अटल अंतरभूत पूर्णांक biपंचांगap_equal(स्थिर अचिन्हित दीर्घ *src1,
			स्थिर अचिन्हित दीर्घ *src2, अचिन्हित पूर्णांक nbits)
अणु
	अगर (small_स्थिर_nbits(nbits))
		वापस !((*src1 ^ *src2) & BITMAP_LAST_WORD_MASK(nbits));
	अगर (__builtin_स्थिरant_p(nbits & BITMAP_MEM_MASK) &&
	    IS_ALIGNED(nbits, BITMAP_MEM_ALIGNMENT))
		वापस !स_भेद(src1, src2, nbits / 8);
	वापस __biपंचांगap_equal(src1, src2, nbits);
पूर्ण

#पूर्ण_अगर /* _PERF_BITOPS_H */
