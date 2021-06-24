<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __HISILICON_CORE_H
#घोषणा __HISILICON_CORE_H

#समावेश <linux/reboot.h>

बाह्य व्योम hi3xxx_set_cpu_jump(पूर्णांक cpu, व्योम *jump_addr);
बाह्य पूर्णांक hi3xxx_get_cpu_jump(पूर्णांक cpu);
बाह्य व्योम secondary_startup(व्योम);

बाह्य व्योम hi3xxx_cpu_die(अचिन्हित पूर्णांक cpu);
बाह्य पूर्णांक hi3xxx_cpu_समाप्त(अचिन्हित पूर्णांक cpu);
बाह्य व्योम hi3xxx_set_cpu(पूर्णांक cpu, bool enable);

बाह्य व्योम hix5hd2_set_cpu(पूर्णांक cpu, bool enable);
बाह्य व्योम hix5hd2_cpu_die(अचिन्हित पूर्णांक cpu);

बाह्य व्योम hip01_set_cpu(पूर्णांक cpu, bool enable);
#पूर्ण_अगर
