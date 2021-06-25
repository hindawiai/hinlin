<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SYNC_CORE_H
#घोषणा _LINUX_SYNC_CORE_H

#अगर_घोषित CONFIG_ARCH_HAS_SYNC_CORE_BEFORE_USERMODE
#समावेश <यंत्र/sync_core.h>
#अन्यथा
/*
 * This is a dummy sync_core_beक्रमe_usermode() implementation that can be used
 * on all architectures which वापस to user-space through core serializing
 * inकाष्ठाions.
 * If your architecture वापसs to user-space through non-core-serializing
 * inकाष्ठाions, you need to ग_लिखो your own functions.
 */
अटल अंतरभूत व्योम sync_core_beक्रमe_usermode(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SYNC_CORE_H */

