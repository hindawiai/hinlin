<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 David Daney
 */
#अगर_अघोषित _ASM_WATCH_H
#घोषणा _ASM_WATCH_H

#समावेश <linux/bitops.h>

#समावेश <यंत्र/mipsregs.h>

व्योम mips_install_watch_रेजिस्टरs(काष्ठा task_काष्ठा *t);
व्योम mips_पढ़ो_watch_रेजिस्टरs(व्योम);
व्योम mips_clear_watch_रेजिस्टरs(व्योम);
व्योम mips_probe_watch_रेजिस्टरs(काष्ठा cpuinfo_mips *c);

#अगर_घोषित CONFIG_HARDWARE_WATCHPOINTS
#घोषणा __restore_watch(task) करो अणु					\
	अगर (unlikely(test_bit(TIF_LOAD_WATCH,				\
			      &task_thपढ़ो_info(task)->flags))) अणु	\
		mips_install_watch_रेजिस्टरs(task);			\
	पूर्ण								\
पूर्ण जबतक (0)

#अन्यथा
#घोषणा __restore_watch(task) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_WATCH_H */
