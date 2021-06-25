<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Network Checksum & Copy routine
 *
 * Copyright (C) 1999, 2003-2004 Hewlett-Packard Co
 *	Stephane Eranian <eranian@hpl.hp.com>
 *
 * Most of the code has been imported from Linux/Alpha
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>

#समावेश <net/checksum.h>

/*
 * XXX Fixme: those 2 अंतरभूतs are meant क्रम debugging and will go away
 */
अटल अंतरभूत अचिन्हित
लघु from64to16(अचिन्हित दीर्घ x)
अणु
	/* add up 32-bit words क्रम 33 bits */
	x = (x & 0xffffffff) + (x >> 32);
	/* add up 16-bit and 17-bit words क्रम 17+c bits */
	x = (x & 0xffff) + (x >> 16);
	/* add up 16-bit and 2-bit क्रम 16+c bit */
	x = (x & 0xffff) + (x >> 16);
	/* add up carry.. */
	x = (x & 0xffff) + (x >> 16);
	वापस x;
पूर्ण

अटल अंतरभूत
अचिन्हित दीर्घ करो_csum_c(स्थिर अचिन्हित अक्षर * buff, पूर्णांक len, अचिन्हित पूर्णांक psum)
अणु
	पूर्णांक odd, count;
	अचिन्हित दीर्घ result = (अचिन्हित दीर्घ)psum;

	अगर (len <= 0)
		जाओ out;
	odd = 1 & (अचिन्हित दीर्घ) buff;
	अगर (odd) अणु
		result = *buff << 8;
		len--;
		buff++;
	पूर्ण
	count = len >> 1;		/* nr of 16-bit words.. */
	अगर (count) अणु
		अगर (2 & (अचिन्हित दीर्घ) buff) अणु
			result += *(अचिन्हित लघु *) buff;
			count--;
			len -= 2;
			buff += 2;
		पूर्ण
		count >>= 1;		/* nr of 32-bit words.. */
		अगर (count) अणु
			अगर (4 & (अचिन्हित दीर्घ) buff) अणु
				result += *(अचिन्हित पूर्णांक *) buff;
				count--;
				len -= 4;
				buff += 4;
			पूर्ण
			count >>= 1;	/* nr of 64-bit words.. */
			अगर (count) अणु
				अचिन्हित दीर्घ carry = 0;
				करो अणु
					अचिन्हित दीर्घ w = *(अचिन्हित दीर्घ *) buff;
					count--;
					buff += 8;
					result += carry;
					result += w;
					carry = (w > result);
				पूर्ण जबतक (count);
				result += carry;
				result = (result & 0xffffffff) + (result >> 32);
			पूर्ण
			अगर (len & 4) अणु
				result += *(अचिन्हित पूर्णांक *) buff;
				buff += 4;
			पूर्ण
		पूर्ण
		अगर (len & 2) अणु
			result += *(अचिन्हित लघु *) buff;
			buff += 2;
		पूर्ण
	पूर्ण
	अगर (len & 1)
		result += *buff;

	result = from64to16(result);

	अगर (odd)
		result = ((result >> 8) & 0xff) | ((result & 0xff) << 8);

out:
	वापस result;
पूर्ण
