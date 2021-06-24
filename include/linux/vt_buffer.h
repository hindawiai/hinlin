<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	include/linux/vt_buffer.h -- Access to VT screen buffer
 *
 *	(c) 1998 Martin Mares <mj@ucw.cz>
 *
 *	This is a set of macros and functions which are used in the
 *	console driver and related code to access the screen buffer.
 *	In most हालs the console works with simple in-memory buffer,
 *	but when handling hardware text mode consoles, we store
 *	the क्रमeground console directly in video memory.
 */

#अगर_अघोषित _LINUX_VT_BUFFER_H_
#घोषणा _LINUX_VT_BUFFER_H_

#समावेश <linux/माला.स>

#अगर defined(CONFIG_VGA_CONSOLE) || defined(CONFIG_MDA_CONSOLE)
#समावेश <यंत्र/vga.h>
#पूर्ण_अगर

#अगर_अघोषित VT_BUF_HAVE_RW
#घोषणा scr_ग_लिखोw(val, addr) (*(addr) = (val))
#घोषणा scr_पढ़ोw(addr) (*(addr))
#पूर्ण_अगर

#अगर_अघोषित VT_BUF_HAVE_MEMSETW
अटल अंतरभूत व्योम scr_स_रखोw(u16 *s, u16 c, अचिन्हित पूर्णांक count)
अणु
#अगर_घोषित VT_BUF_HAVE_RW
	count /= 2;
	जबतक (count--)
		scr_ग_लिखोw(c, s++);
#अन्यथा
	स_रखो16(s, c, count / 2);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित VT_BUF_HAVE_MEMCPYW
अटल अंतरभूत व्योम scr_स_नकलw(u16 *d, स्थिर u16 *s, अचिन्हित पूर्णांक count)
अणु
#अगर_घोषित VT_BUF_HAVE_RW
	count /= 2;
	जबतक (count--)
		scr_ग_लिखोw(scr_पढ़ोw(s++), d++);
#अन्यथा
	स_नकल(d, s, count);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित VT_BUF_HAVE_MEMMOVEW
अटल अंतरभूत व्योम scr_स_हटाओw(u16 *d, स्थिर u16 *s, अचिन्हित पूर्णांक count)
अणु
#अगर_घोषित VT_BUF_HAVE_RW
	अगर (d < s)
		scr_स_नकलw(d, s, count);
	अन्यथा अणु
		count /= 2;
		d += count;
		s += count;
		जबतक (count--)
			scr_ग_लिखोw(scr_पढ़ोw(--s), --d);
	पूर्ण
#अन्यथा
	स_हटाओ(d, s, count);
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
