<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Unअगरied handling of special अक्षरs.
 *
 *    Copyright IBM Corp. 2001
 *    Author(s): Fritz Elfert <felfert@millenux.com> <elfert@de.ibm.com>
 *
 */

#समावेश <linux/tty.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/workqueue.h>

बाह्य अचिन्हित पूर्णांक
ctrlअक्षर_handle(स्थिर अचिन्हित अक्षर *buf, पूर्णांक len, काष्ठा tty_काष्ठा *tty);


#घोषणा CTRLCHAR_NONE  (1 << 8)
#घोषणा CTRLCHAR_CTRL  (2 << 8)
#घोषणा CTRLCHAR_SYSRQ (3 << 8)

#घोषणा CTRLCHAR_MASK (~0xffu)


#अगर_घोषित CONFIG_MAGIC_SYSRQ
काष्ठा sysrq_work अणु
	पूर्णांक key;
	काष्ठा work_काष्ठा work;
पूर्ण;

व्योम schedule_sysrq_work(काष्ठा sysrq_work *sw);
#पूर्ण_अगर
