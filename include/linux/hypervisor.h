<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_HYPEVISOR_H
#घोषणा __LINUX_HYPEVISOR_H

/*
 *	Generic Hypervisor support
 *		Juergen Gross <jgross@suse.com>
 */

#अगर_घोषित CONFIG_X86

#समावेश <यंत्र/jailhouse_para.h>
#समावेश <यंत्र/x86_init.h>

अटल अंतरभूत व्योम hypervisor_pin_vcpu(पूर्णांक cpu)
अणु
	x86_platक्रमm.hyper.pin_vcpu(cpu);
पूर्ण

#अन्यथा /* !CONFIG_X86 */

#समावेश <linux/of.h>

अटल अंतरभूत व्योम hypervisor_pin_vcpu(पूर्णांक cpu)
अणु
पूर्ण

अटल अंतरभूत bool jailhouse_paravirt(व्योम)
अणु
	वापस of_find_compatible_node(शून्य, शून्य, "jailhouse,cell");
पूर्ण

#पूर्ण_अगर /* !CONFIG_X86 */

#पूर्ण_अगर /* __LINUX_HYPEVISOR_H */
