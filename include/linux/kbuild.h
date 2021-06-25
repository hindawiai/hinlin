<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_KBUILD_H
#घोषणा __LINUX_KBUILD_H

#घोषणा DEFINE(sym, val) \
	यंत्र अस्थिर("\n.ascii \"->" #sym " %0 " #val "\"" : : "i" (val))

#घोषणा BLANK() यंत्र अस्थिर("\n.ascii \"->\"" : : )

#घोषणा OFFSET(sym, str, mem) \
	DEFINE(sym, दुरत्व(काष्ठा str, mem))

#घोषणा COMMENT(x) \
	यंत्र अस्थिर("\n.ascii \"->#" x "\"")

#पूर्ण_अगर
