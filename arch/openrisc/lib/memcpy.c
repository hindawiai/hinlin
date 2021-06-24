<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/खोलोrisc/lib/स_नकल.c
 *
 * Optimized memory copy routines क्रम खोलोrisc.  These are mostly copied
 * from ohter sources but slightly entended based on ideas discuassed in
 * #खोलोrisc.
 *
 * The word unroll implementation is an extension to the arm byte
 * unrolled implementation, but using word copies (अगर things are
 * properly aligned)
 *
 * The great arm loop unroll algorithm can be found at:
 *  arch/arm/boot/compressed/string.c
 */

#समावेश <linux/export.h>

#समावेश <linux/माला.स>

#अगर_घोषित CONFIG_OR1K_1200
/*
 * Do स_नकल with word copies and loop unrolling. This gives the
 * best perक्रमmance on the OR1200 and MOR1KX archirectures
 */
व्योम *स_नकल(व्योम *dest, __स्थिर व्योम *src, __kernel_माप_प्रकार n)
अणु
	पूर्णांक i = 0;
	अचिन्हित अक्षर *d, *s;
	uपूर्णांक32_t *dest_w = (uपूर्णांक32_t *)dest, *src_w = (uपूर्णांक32_t *)src;

	/* If both source and dest are word aligned copy words */
	अगर (!((अचिन्हित पूर्णांक)dest_w & 3) && !((अचिन्हित पूर्णांक)src_w & 3)) अणु
		/* Copy 32 bytes per loop */
		क्रम (i = n >> 5; i > 0; i--) अणु
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
		पूर्ण

		अगर (n & 1 << 4) अणु
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
		पूर्ण

		अगर (n & 1 << 3) अणु
			*dest_w++ = *src_w++;
			*dest_w++ = *src_w++;
		पूर्ण

		अगर (n & 1 << 2)
			*dest_w++ = *src_w++;

		d = (अचिन्हित अक्षर *)dest_w;
		s = (अचिन्हित अक्षर *)src_w;

	पूर्ण अन्यथा अणु
		d = (अचिन्हित अक्षर *)dest_w;
		s = (अचिन्हित अक्षर *)src_w;

		क्रम (i = n >> 3; i > 0; i--) अणु
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
		पूर्ण

		अगर (n & 1 << 2) अणु
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
			*d++ = *s++;
		पूर्ण
	पूर्ण

	अगर (n & 1 << 1) अणु
		*d++ = *s++;
		*d++ = *s++;
	पूर्ण

	अगर (n & 1)
		*d++ = *s++;

	वापस dest;
पूर्ण
#अन्यथा
/*
 * Use word copies but no loop unrolling as we cannot assume there
 * will be benefits on the archirecture
 */
व्योम *स_नकल(व्योम *dest, __स्थिर व्योम *src, __kernel_माप_प्रकार n)
अणु
	अचिन्हित अक्षर *d = (अचिन्हित अक्षर *)dest, *s = (अचिन्हित अक्षर *)src;
	uपूर्णांक32_t *dest_w = (uपूर्णांक32_t *)dest, *src_w = (uपूर्णांक32_t *)src;

	/* If both source and dest are word aligned copy words */
	अगर (!((अचिन्हित पूर्णांक)dest_w & 3) && !((अचिन्हित पूर्णांक)src_w & 3)) अणु
		क्रम (; n >= 4; n -= 4)
			*dest_w++ = *src_w++;
	पूर्ण

	d = (अचिन्हित अक्षर *)dest_w;
	s = (अचिन्हित अक्षर *)src_w;

	/* For reमुख्यing or अगर not aligned, copy bytes */
	क्रम (; n >= 1; n -= 1)
		*d++ = *s++;

	वापस dest;

पूर्ण
#पूर्ण_अगर

EXPORT_SYMBOL(स_नकल);
