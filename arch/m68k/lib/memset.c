<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>

व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार count)
अणु
	व्योम *xs = s;
	माप_प्रकार temp;

	अगर (!count)
		वापस xs;
	c &= 0xff;
	c |= c << 8;
	c |= c << 16;
	अगर ((दीर्घ)s & 1) अणु
		अक्षर *cs = s;
		*cs++ = c;
		s = cs;
		count--;
	पूर्ण
	अगर (count > 2 && (दीर्घ)s & 2) अणु
		लघु *ss = s;
		*ss++ = c;
		s = ss;
		count -= 2;
	पूर्ण
	temp = count >> 2;
	अगर (temp) अणु
		दीर्घ *ls = s;
#अगर defined(CONFIG_M68000) || defined(CONFIG_COLDFIRE)
		क्रम (; temp; temp--)
			*ls++ = c;
#अन्यथा
		माप_प्रकार temp1;
		यंत्र अस्थिर (
			"	movel %1,%2\n"
			"	andw  #7,%2\n"
			"	lsrl  #3,%1\n"
			"	negw  %2\n"
			"	jmp   %%pc@(2f,%2:w:2)\n"
			"1:	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"	movel %3,%0@+\n"
			"2:	dbra  %1,1b\n"
			"	clrw  %1\n"
			"	subql #1,%1\n"
			"	jpl   1b"
			: "=a" (ls), "=d" (temp), "=&d" (temp1)
			: "d" (c), "0" (ls), "1" (temp));
#पूर्ण_अगर
		s = ls;
	पूर्ण
	अगर (count & 2) अणु
		लघु *ss = s;
		*ss++ = c;
		s = ss;
	पूर्ण
	अगर (count & 1) अणु
		अक्षर *cs = s;
		*cs = c;
	पूर्ण
	वापस xs;
पूर्ण
EXPORT_SYMBOL(स_रखो);
