<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>

व्योम *स_नकल(व्योम *to, स्थिर व्योम *from, माप_प्रकार n)
अणु
	व्योम *xto = to;
	माप_प्रकार temp;

	अगर (!n)
		वापस xto;
	अगर ((दीर्घ)to & 1) अणु
		अक्षर *cto = to;
		स्थिर अक्षर *cfrom = from;
		*cto++ = *cfrom++;
		to = cto;
		from = cfrom;
		n--;
	पूर्ण
#अगर defined(CONFIG_M68000)
	अगर ((दीर्घ)from & 1) अणु
		अक्षर *cto = to;
		स्थिर अक्षर *cfrom = from;
		क्रम (; n; n--)
			*cto++ = *cfrom++;
		वापस xto;
	पूर्ण
#पूर्ण_अगर
	अगर (n > 2 && (दीर्घ)to & 2) अणु
		लघु *sto = to;
		स्थिर लघु *sfrom = from;
		*sto++ = *sfrom++;
		to = sto;
		from = sfrom;
		n -= 2;
	पूर्ण
	temp = n >> 2;
	अगर (temp) अणु
		दीर्घ *lto = to;
		स्थिर दीर्घ *lfrom = from;
#अगर defined(CONFIG_M68000) || defined(CONFIG_COLDFIRE)
		क्रम (; temp; temp--)
			*lto++ = *lfrom++;
#अन्यथा
		माप_प्रकार temp1;
		यंत्र अस्थिर (
			"	movel %2,%3\n"
			"	andw  #7,%3\n"
			"	lsrl  #3,%2\n"
			"	negw  %3\n"
			"	jmp   %%pc@(1f,%3:w:2)\n"
			"4:	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"	movel %0@+,%1@+\n"
			"1:	dbra  %2,4b\n"
			"	clrw  %2\n"
			"	subql #1,%2\n"
			"	jpl   4b"
			: "=a" (lfrom), "=a" (lto), "=d" (temp), "=&d" (temp1)
			: "0" (lfrom), "1" (lto), "2" (temp));
#पूर्ण_अगर
		to = lto;
		from = lfrom;
	पूर्ण
	अगर (n & 2) अणु
		लघु *sto = to;
		स्थिर लघु *sfrom = from;
		*sto++ = *sfrom++;
		to = sto;
		from = sfrom;
	पूर्ण
	अगर (n & 1) अणु
		अक्षर *cto = to;
		स्थिर अक्षर *cfrom = from;
		*cto = *cfrom;
	पूर्ण
	वापस xto;
पूर्ण
EXPORT_SYMBOL(स_नकल);
