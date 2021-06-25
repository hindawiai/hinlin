<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2017 Arm Ltd.
#अगर_अघोषित __ASM_SDEI_H
#घोषणा __ASM_SDEI_H

/* Values क्रम sdei_निकास_mode */
#घोषणा SDEI_EXIT_HVC  0
#घोषणा SDEI_EXIT_SMC  1

#घोषणा SDEI_STACK_SIZE		IRQ_STACK_SIZE

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/linkage.h>
#समावेश <linux/preempt.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/virt.h>

बाह्य अचिन्हित दीर्घ sdei_निकास_mode;

/* Software Delegated Exception entry poपूर्णांक from firmware*/
यंत्रlinkage व्योम __sdei_यंत्र_handler(अचिन्हित दीर्घ event_num, अचिन्हित दीर्घ arg,
				   अचिन्हित दीर्घ pc, अचिन्हित दीर्घ pstate);

/* and its CONFIG_UNMAP_KERNEL_AT_EL0 trampoline */
यंत्रlinkage व्योम __sdei_यंत्र_entry_trampoline(अचिन्हित दीर्घ event_num,
						   अचिन्हित दीर्घ arg,
						   अचिन्हित दीर्घ pc,
						   अचिन्हित दीर्घ pstate);

/*
 * The above entry poपूर्णांक करोes the minimum to call C code. This function करोes
 * anything अन्यथा, beक्रमe calling the driver.
 */
काष्ठा sdei_रेजिस्टरed_event;
यंत्रlinkage अचिन्हित दीर्घ __sdei_handler(काष्ठा pt_regs *regs,
					काष्ठा sdei_रेजिस्टरed_event *arg);

अचिन्हित दीर्घ sdei_arch_get_entry_poपूर्णांक(पूर्णांक conduit);
#घोषणा sdei_arch_get_entry_poपूर्णांक(x)	sdei_arch_get_entry_poपूर्णांक(x)

काष्ठा stack_info;

bool _on_sdei_stack(अचिन्हित दीर्घ sp, काष्ठा stack_info *info);
अटल अंतरभूत bool on_sdei_stack(अचिन्हित दीर्घ sp,
				काष्ठा stack_info *info)
अणु
	अगर (!IS_ENABLED(CONFIG_VMAP_STACK))
		वापस false;
	अगर (!IS_ENABLED(CONFIG_ARM_SDE_INTERFACE))
		वापस false;
	अगर (in_nmi())
		वापस _on_sdei_stack(sp, info);

	वापस false;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर	/* __ASM_SDEI_H */
