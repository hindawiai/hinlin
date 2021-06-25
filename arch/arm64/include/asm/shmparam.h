<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_SHMPARAM_H
#घोषणा __ASM_SHMPARAM_H

/*
 * For IPC syscalls from compat tasks, we need to use the legacy 16k
 * alignment value. Since we करोn't have aliasing D-caches, the rest of
 * the समय we can safely use PAGE_SIZE.
 */
#घोषणा COMPAT_SHMLBA	(4 * PAGE_SIZE)

#समावेश <यंत्र-generic/shmparam.h>

#पूर्ण_अगर /* __ASM_SHMPARAM_H */
