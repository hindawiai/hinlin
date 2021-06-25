<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>

व्योम *स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	व्योम *xdest = dest;
	माप_प्रकार temp;

	अगर (!n)
		वापस xdest;

	अगर (dest < src) अणु
		अगर ((दीर्घ)dest & 1) अणु
			अक्षर *cdest = dest;
			स्थिर अक्षर *csrc = src;
			*cdest++ = *csrc++;
			dest = cdest;
			src = csrc;
			n--;
		पूर्ण
		अगर (n > 2 && (दीर्घ)dest & 2) अणु
			लघु *sdest = dest;
			स्थिर लघु *ssrc = src;
			*sdest++ = *ssrc++;
			dest = sdest;
			src = ssrc;
			n -= 2;
		पूर्ण
		temp = n >> 2;
		अगर (temp) अणु
			दीर्घ *ldest = dest;
			स्थिर दीर्घ *lsrc = src;
			temp--;
			करो
				*ldest++ = *lsrc++;
			जबतक (temp--);
			dest = ldest;
			src = lsrc;
		पूर्ण
		अगर (n & 2) अणु
			लघु *sdest = dest;
			स्थिर लघु *ssrc = src;
			*sdest++ = *ssrc++;
			dest = sdest;
			src = ssrc;
		पूर्ण
		अगर (n & 1) अणु
			अक्षर *cdest = dest;
			स्थिर अक्षर *csrc = src;
			*cdest = *csrc;
		पूर्ण
	पूर्ण अन्यथा अणु
		dest = (अक्षर *)dest + n;
		src = (स्थिर अक्षर *)src + n;
		अगर ((दीर्घ)dest & 1) अणु
			अक्षर *cdest = dest;
			स्थिर अक्षर *csrc = src;
			*--cdest = *--csrc;
			dest = cdest;
			src = csrc;
			n--;
		पूर्ण
		अगर (n > 2 && (दीर्घ)dest & 2) अणु
			लघु *sdest = dest;
			स्थिर लघु *ssrc = src;
			*--sdest = *--ssrc;
			dest = sdest;
			src = ssrc;
			n -= 2;
		पूर्ण
		temp = n >> 2;
		अगर (temp) अणु
			दीर्घ *ldest = dest;
			स्थिर दीर्घ *lsrc = src;
			temp--;
			करो
				*--ldest = *--lsrc;
			जबतक (temp--);
			dest = ldest;
			src = lsrc;
		पूर्ण
		अगर (n & 2) अणु
			लघु *sdest = dest;
			स्थिर लघु *ssrc = src;
			*--sdest = *--ssrc;
			dest = sdest;
			src = ssrc;
		पूर्ण
		अगर (n & 1) अणु
			अक्षर *cdest = dest;
			स्थिर अक्षर *csrc = src;
			*--cdest = *--csrc;
		पूर्ण
	पूर्ण
	वापस xdest;
पूर्ण
EXPORT_SYMBOL(स_हटाओ);
