<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_FAULT_INJECT_USERCOPY_H__
#घोषणा __LINUX_FAULT_INJECT_USERCOPY_H__

/*
 * This header provides a wrapper क्रम injecting failures to user space memory
 * access functions.
 */

#समावेश <linux/types.h>

#अगर_घोषित CONFIG_FAULT_INJECTION_USERCOPY

bool should_fail_usercopy(व्योम);

#अन्यथा

अटल अंतरभूत bool should_fail_usercopy(व्योम) अणु वापस false; पूर्ण

#पूर्ण_अगर /* CONFIG_FAULT_INJECTION_USERCOPY */

#पूर्ण_अगर /* __LINUX_FAULT_INJECT_USERCOPY_H__ */
