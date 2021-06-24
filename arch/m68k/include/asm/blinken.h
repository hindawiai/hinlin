<शैली गुरु>
/*
** यंत्र/blinken.h -- m68k blinkenlights support (currently hp300 only)
**
** (c) 1998 Phil Blundell <philb@gnu.org>
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
**
*/

#अगर_अघोषित _M68K_BLINKEN_H
#घोषणा _M68K_BLINKEN_H

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/पन.स>

#घोषणा HP300_LEDS		0xf001ffff

बाह्य अचिन्हित अक्षर hp300_ledstate;

अटल __अंतरभूत__ व्योम blinken_leds(पूर्णांक on, पूर्णांक off)
अणु
	अगर (MACH_IS_HP300)
	अणु
		hp300_ledstate |= on;
		hp300_ledstate &= ~off;
		out_8(HP300_LEDS, ~hp300_ledstate);
	पूर्ण
पूर्ण

#पूर्ण_अगर
