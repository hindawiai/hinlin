<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SKC_LINUX_BUG_H
#घोषणा _SKC_LINUX_BUG_H

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#घोषणा WARN_ON(cond)	\
	((cond) ? म_लिखो("Internal warning(%s:%d, %s): %s\n",	\
			__खाता__, __LINE__, __func__, #cond) : 0)

#पूर्ण_अगर
