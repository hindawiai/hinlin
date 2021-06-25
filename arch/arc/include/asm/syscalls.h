<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित _ASM_ARC_SYSCALLS_H
#घोषणा _ASM_ARC_SYSCALLS_H  1

#समावेश <linux/compiler.h>
#समावेश <linux/linkage.h>
#समावेश <linux/types.h>

पूर्णांक sys_clone_wrapper(पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक, पूर्णांक);
पूर्णांक sys_clone3_wrapper(व्योम *, माप_प्रकार);
पूर्णांक sys_cacheflush(uपूर्णांक32_t, uपूर्णांक32_t uपूर्णांक32_t);
पूर्णांक sys_arc_settls(व्योम *);
पूर्णांक sys_arc_gettls(व्योम);
पूर्णांक sys_arc_usr_cmpxchg(पूर्णांक *, पूर्णांक, पूर्णांक);

#समावेश <यंत्र-generic/syscalls.h>

#पूर्ण_अगर
