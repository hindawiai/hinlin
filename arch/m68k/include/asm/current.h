<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_CURRENT_H
#घोषणा _M68K_CURRENT_H

#अगर_घोषित CONFIG_MMU

रेजिस्टर काष्ठा task_काष्ठा *current __यंत्र__("%a2");

#अन्यथा

/*
 *	Rather than dedicate a रेजिस्टर (as the m68k source करोes), we
 *	just keep a global,  we should probably just change it all to be
 *	current and lose _current_task.
 */
#समावेश <linux/thपढ़ो_info.h>

काष्ठा task_काष्ठा;

अटल अंतरभूत काष्ठा task_काष्ठा *get_current(व्योम)
अणु
	वापस(current_thपढ़ो_info()->task);
पूर्ण

#घोषणा	current	get_current()

#पूर्ण_अगर /* CONFNIG_MMU */

#पूर्ण_अगर /* !(_M68K_CURRENT_H) */
