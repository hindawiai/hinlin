<शैली गुरु>
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>

व्योम *स_हटाओ(व्योम *d, स्थिर व्योम *s, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ dst, src;

	अगर (!count)
		वापस d;

	अगर (d < s) अणु
		dst = (अचिन्हित दीर्घ) d;
		src = (अचिन्हित दीर्घ) s;

		अगर ((count < 8) || ((dst ^ src) & 3))
			जाओ restup;

		अगर (dst & 1) अणु
			*(अक्षर *)dst++ = *(अक्षर *)src++;
			count--;
		पूर्ण
		अगर (dst & 2) अणु
			*(लघु *)dst = *(लघु *)src;
			src += 2;
			dst += 2;
			count -= 2;
		पूर्ण
		जबतक (count > 3) अणु
			*(दीर्घ *)dst = *(दीर्घ *)src;
			src += 4;
			dst += 4;
			count -= 4;
		पूर्ण
restup:
		जबतक (count--)
			*(अक्षर *)dst++ = *(अक्षर *)src++;
	पूर्ण अन्यथा अणु
		dst = (अचिन्हित दीर्घ) d + count;
		src = (अचिन्हित दीर्घ) s + count;

		अगर ((count < 8) || ((dst ^ src) & 3))
			जाओ restकरोwn;

		अगर (dst & 1) अणु
			src--;
			dst--;
			count--;
			*(अक्षर *)dst = *(अक्षर *)src;
		पूर्ण
		अगर (dst & 2) अणु
			src -= 2;
			dst -= 2;
			count -= 2;
			*(लघु *)dst = *(लघु *)src;
		पूर्ण
		जबतक (count > 3) अणु
			src -= 4;
			dst -= 4;
			count -= 4;
			*(दीर्घ *)dst = *(दीर्घ *)src;
		पूर्ण
restकरोwn:
		जबतक (count--) अणु
			src--;
			dst--;
			*(अक्षर *)dst = *(अक्षर *)src;
		पूर्ण
	पूर्ण

	वापस d;
पूर्ण
