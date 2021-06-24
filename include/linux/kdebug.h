<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KDEBUG_H
#घोषणा _LINUX_KDEBUG_H

#समावेश <यंत्र/kdebug.h>

काष्ठा notअगरier_block;

काष्ठा die_args अणु
	काष्ठा pt_regs *regs;
	स्थिर अक्षर *str;
	दीर्घ err;
	पूर्णांक trapnr;
	पूर्णांक signr;
पूर्ण;

पूर्णांक रेजिस्टर_die_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_die_notअगरier(काष्ठा notअगरier_block *nb);

पूर्णांक notअगरy_die(क्रमागत die_val val, स्थिर अक्षर *str,
	       काष्ठा pt_regs *regs, दीर्घ err, पूर्णांक trap, पूर्णांक sig);

#पूर्ण_अगर /* _LINUX_KDEBUG_H */
