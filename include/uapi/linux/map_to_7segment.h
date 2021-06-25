<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Copyright (c) 2005 Henk Vergonet <Henk.Vergonet@gmail.com>
 */

#अगर_अघोषित MAP_TO_7SEGMENT_H
#घोषणा MAP_TO_7SEGMENT_H

/* This file provides translation primitives and tables क्रम the conversion
 * of (ASCII) अक्षरacters to a 7-segments notation.
 *
 * The 7 segment's wikipedia notation below is used as standard.
 * See: https://en.wikipedia.org/wiki/Seven_segment_display
 *
 * Notation:	+-a-+
 *		f   b
 *		+-g-+
 *		e   c
 *		+-d-+
 *
 * Usage:
 *
 *   Register a map variable, and fill it with a अक्षरacter set:
 *	अटल SEG7_DEFAULT_MAP(map_seg7);
 *
 *
 *   Then use क्रम conversion:
 *	seg7 = map_to_seg7(&map_seg7, some_अक्षर);
 *	...
 *
 * In device drivers it is recommended, अगर required, to make the अक्षर map
 * accessible via the sysfs पूर्णांकerface using the following scheme:
 *
 * अटल sमाप_प्रकार map_seg7_show(काष्ठा device *dev,
 *				काष्ठा device_attribute *attr, अक्षर *buf)
 * अणु
 *	स_नकल(buf, &map_seg7, माप(map_seg7));
 *	वापस माप(map_seg7);
 * पूर्ण
 * अटल sमाप_प्रकार map_seg7_store(काष्ठा device *dev,
 *				 काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
 *				 माप_प्रकार cnt)
 * अणु
 *	अगर(cnt != माप(map_seg7))
 *		वापस -EINVAL;
 *	स_नकल(&map_seg7, buf, cnt);
 *	वापस cnt;
 * पूर्ण
 * अटल DEVICE_ATTR_RW(map_seg7);
 *
 * History:
 * 2005-05-31	RFC linux-kernel@vger.kernel.org
 */
#समावेश <linux/त्रुटिसं.स>


#घोषणा BIT_SEG7_A		0
#घोषणा BIT_SEG7_B		1
#घोषणा BIT_SEG7_C		2
#घोषणा BIT_SEG7_D		3
#घोषणा BIT_SEG7_E		4
#घोषणा BIT_SEG7_F		5
#घोषणा BIT_SEG7_G		6
#घोषणा BIT_SEG7_RESERVED	7

काष्ठा seg7_conversion_map अणु
	अचिन्हित अक्षर	table[128];
पूर्ण;

अटल __अंतरभूत__ पूर्णांक map_to_seg7(काष्ठा seg7_conversion_map *map, पूर्णांक c)
अणु
	वापस c >= 0 && c < माप(map->table) ? map->table[c] : -EINVAL;
पूर्ण

#घोषणा SEG7_CONVERSION_MAP(_name, _map)	\
	काष्ठा seg7_conversion_map _name = अणु .table = अणु _map पूर्ण पूर्ण

/*
 * It is recommended to use a facility that allows user space to redefine
 * custom अक्षरacter sets क्रम LCD devices. Please use a sysfs पूर्णांकerface
 * as described above.
 */
#घोषणा MAP_TO_SEG7_SYSFS_खाता	"map_seg7"

/*******************************************************************************
 * ASCII conversion table
 ******************************************************************************/

#घोषणा _SEG7(l,a,b,c,d,e,f,g)	\
      (	a<<BIT_SEG7_A |	b<<BIT_SEG7_B |	c<<BIT_SEG7_C |	d<<BIT_SEG7_D |	\
	e<<BIT_SEG7_E |	f<<BIT_SEG7_F |	g<<BIT_SEG7_G )

#घोषणा _MAP_0_32_ASCII_SEG7_NON_PRINTABLE	\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,

#घोषणा _MAP_33_47_ASCII_SEG7_SYMBOL		\
 _SEG7('!',0,0,0,0,1,1,0), _SEG7('"',0,1,0,0,0,1,0), _SEG7('#',0,1,1,0,1,1,0),\
 _SEG7('$',1,0,1,1,0,1,1), _SEG7('%',0,0,1,0,0,1,0), _SEG7('&',1,0,1,1,1,1,1),\
 _SEG7('\'',0,0,0,0,0,1,0),_SEG7('(',1,0,0,1,1,1,0), _SEG7(')',1,1,1,1,0,0,0),\
 _SEG7('*',0,1,1,0,1,1,1), _SEG7('+',0,1,1,0,0,0,1), _SEG7(',',0,0,0,0,1,0,0),\
 _SEG7('-',0,0,0,0,0,0,1), _SEG7('.',0,0,0,0,1,0,0), _SEG7('/',0,1,0,0,1,0,1),

#घोषणा _MAP_48_57_ASCII_SEG7_NUMERIC		\
 _SEG7('0',1,1,1,1,1,1,0), _SEG7('1',0,1,1,0,0,0,0), _SEG7('2',1,1,0,1,1,0,1),\
 _SEG7('3',1,1,1,1,0,0,1), _SEG7('4',0,1,1,0,0,1,1), _SEG7('5',1,0,1,1,0,1,1),\
 _SEG7('6',1,0,1,1,1,1,1), _SEG7('7',1,1,1,0,0,0,0), _SEG7('8',1,1,1,1,1,1,1),\
 _SEG7('9',1,1,1,1,0,1,1),

#घोषणा _MAP_58_64_ASCII_SEG7_SYMBOL		\
 _SEG7(':',0,0,0,1,0,0,1), _SEG7(';',0,0,0,1,0,0,1), _SEG7('<',1,0,0,0,0,1,1),\
 _SEG7('=',0,0,0,1,0,0,1), _SEG7('>',1,1,0,0,0,0,1), _SEG7('?',1,1,1,0,0,1,0),\
 _SEG7('@',1,1,0,1,1,1,1),

#घोषणा _MAP_65_90_ASCII_SEG7_ALPHA_UPPR	\
 _SEG7('A',1,1,1,0,1,1,1), _SEG7('B',1,1,1,1,1,1,1), _SEG7('C',1,0,0,1,1,1,0),\
 _SEG7('D',1,1,1,1,1,1,0), _SEG7('E',1,0,0,1,1,1,1), _SEG7('F',1,0,0,0,1,1,1),\
 _SEG7('G',1,1,1,1,0,1,1), _SEG7('H',0,1,1,0,1,1,1), _SEG7('I',0,1,1,0,0,0,0),\
 _SEG7('J',0,1,1,1,0,0,0), _SEG7('K',0,1,1,0,1,1,1), _SEG7('L',0,0,0,1,1,1,0),\
 _SEG7('M',1,1,1,0,1,1,0), _SEG7('N',1,1,1,0,1,1,0), _SEG7('O',1,1,1,1,1,1,0),\
 _SEG7('P',1,1,0,0,1,1,1), _SEG7('Q',1,1,1,1,1,1,0), _SEG7('R',1,1,1,0,1,1,1),\
 _SEG7('S',1,0,1,1,0,1,1), _SEG7('T',0,0,0,1,1,1,1), _SEG7('U',0,1,1,1,1,1,0),\
 _SEG7('V',0,1,1,1,1,1,0), _SEG7('W',0,1,1,1,1,1,1), _SEG7('X',0,1,1,0,1,1,1),\
 _SEG7('Y',0,1,1,0,0,1,1), _SEG7('Z',1,1,0,1,1,0,1),

#घोषणा _MAP_91_96_ASCII_SEG7_SYMBOL		\
 _SEG7('[',1,0,0,1,1,1,0), _SEG7('\\',0,0,1,0,0,1,1),_SEG7(']',1,1,1,1,0,0,0),\
 _SEG7('^',1,1,0,0,0,1,0), _SEG7('_',0,0,0,1,0,0,0), _SEG7('`',0,1,0,0,0,0,0),

#घोषणा _MAP_97_122_ASCII_SEG7_ALPHA_LOWER	\
 _SEG7('A',1,1,1,0,1,1,1), _SEG7('b',0,0,1,1,1,1,1), _SEG7('c',0,0,0,1,1,0,1),\
 _SEG7('d',0,1,1,1,1,0,1), _SEG7('E',1,0,0,1,1,1,1), _SEG7('F',1,0,0,0,1,1,1),\
 _SEG7('G',1,1,1,1,0,1,1), _SEG7('h',0,0,1,0,1,1,1), _SEG7('i',0,0,1,0,0,0,0),\
 _SEG7('j',0,0,1,1,0,0,0), _SEG7('k',0,0,1,0,1,1,1), _SEG7('L',0,0,0,1,1,1,0),\
 _SEG7('M',1,1,1,0,1,1,0), _SEG7('n',0,0,1,0,1,0,1), _SEG7('o',0,0,1,1,1,0,1),\
 _SEG7('P',1,1,0,0,1,1,1), _SEG7('q',1,1,1,0,0,1,1), _SEG7('r',0,0,0,0,1,0,1),\
 _SEG7('S',1,0,1,1,0,1,1), _SEG7('T',0,0,0,1,1,1,1), _SEG7('u',0,0,1,1,1,0,0),\
 _SEG7('v',0,0,1,1,1,0,0), _SEG7('W',0,1,1,1,1,1,1), _SEG7('X',0,1,1,0,1,1,1),\
 _SEG7('y',0,1,1,1,0,1,1), _SEG7('Z',1,1,0,1,1,0,1),

#घोषणा _MAP_123_126_ASCII_SEG7_SYMBOL		\
 _SEG7('{',1,0,0,1,1,1,0), _SEG7('|',0,0,0,0,1,1,0), _SEG7('}',1,1,1,1,0,0,0),\
 _SEG7('~',1,0,0,0,0,0,0),

/* Maps */

/* This set tries to map as बंद as possible to the visible अक्षरacteristics
 * of the ASCII symbol, lowerहाल and upperहाल letters may dअगरfer in
 * presentation on the display.
 */
#घोषणा MAP_ASCII7SEG_ALPHANUM			\
	_MAP_0_32_ASCII_SEG7_NON_PRINTABLE	\
	_MAP_33_47_ASCII_SEG7_SYMBOL		\
	_MAP_48_57_ASCII_SEG7_NUMERIC		\
	_MAP_58_64_ASCII_SEG7_SYMBOL		\
	_MAP_65_90_ASCII_SEG7_ALPHA_UPPR	\
	_MAP_91_96_ASCII_SEG7_SYMBOL		\
	_MAP_97_122_ASCII_SEG7_ALPHA_LOWER	\
	_MAP_123_126_ASCII_SEG7_SYMBOL

/* This set tries to map as बंद as possible to the symbolic अक्षरacteristics
 * of the ASCII अक्षरacter क्रम maximum discrimination.
 * For now this means all alpha अक्षरs are in lower हाल representations.
 * (This क्रम example facilitates the use of hex numbers with upperहाल input.)
 */
#घोषणा MAP_ASCII7SEG_ALPHANUM_LC			\
	_MAP_0_32_ASCII_SEG7_NON_PRINTABLE	\
	_MAP_33_47_ASCII_SEG7_SYMBOL		\
	_MAP_48_57_ASCII_SEG7_NUMERIC		\
	_MAP_58_64_ASCII_SEG7_SYMBOL		\
	_MAP_97_122_ASCII_SEG7_ALPHA_LOWER	\
	_MAP_91_96_ASCII_SEG7_SYMBOL		\
	_MAP_97_122_ASCII_SEG7_ALPHA_LOWER	\
	_MAP_123_126_ASCII_SEG7_SYMBOL

#घोषणा SEG7_DEFAULT_MAP(_name)		\
	SEG7_CONVERSION_MAP(_name,MAP_ASCII7SEG_ALPHANUM)

#पूर्ण_अगर	/* MAP_TO_7SEGMENT_H */

