<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 SiFive, Inc.
 */
#अगर_अघोषित __ASM_HEAD_H
#घोषणा __ASM_HEAD_H

#समावेश <linux/linkage.h>
#समावेश <linux/init.h>

बाह्य atomic_t hart_lottery;

यंत्रlinkage व्योम करो_page_fault(काष्ठा pt_regs *regs);
यंत्रlinkage व्योम __init setup_vm(uपूर्णांकptr_t dtb_pa);
#अगर_घोषित CONFIG_XIP_KERNEL
यंत्रlinkage व्योम __init __copy_data(व्योम);
#पूर्ण_अगर

बाह्य व्योम *__cpu_up_stack_poपूर्णांकer[];
बाह्य व्योम *__cpu_up_task_poपूर्णांकer[];

#पूर्ण_अगर /* __ASM_HEAD_H */
