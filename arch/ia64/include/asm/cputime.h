<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Definitions क्रम measuring cpuसमय on ia64 machines.
 *
 * Based on <यंत्र-घातerpc/cpuसमय.स>.
 *
 * Copyright (C) 2007 FUJITSU LIMITED
 * Copyright (C) 2007 Hidetoshi Seto <seto.hidetoshi@jp.fujitsu.com>
 *
 * If we have CONFIG_VIRT_CPU_ACCOUNTING_NATIVE, we measure cpu समय in nsec.
 * Otherwise we measure cpu समय in jअगरfies using the generic definitions.
 */

#अगर_अघोषित __IA64_CPUTIME_H
#घोषणा __IA64_CPUTIME_H

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
बाह्य व्योम arch_vसमय_प्रकारask_चयन(काष्ठा task_काष्ठा *tsk);
#पूर्ण_अगर /* CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */

#पूर्ण_अगर /* __IA64_CPUTIME_H */
