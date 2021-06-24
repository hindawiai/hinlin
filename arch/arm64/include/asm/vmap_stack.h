<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2017 Arm Ltd.
#अगर_अघोषित __ASM_VMAP_STACK_H
#घोषणा __ASM_VMAP_STACK_H

#समावेश <linux/bug.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/thपढ़ो_info.h>

/*
 * To ensure that VMAP'd stack overflow detection works correctly, all VMAP'd
 * stacks need to have the same alignment.
 */
अटल अंतरभूत अचिन्हित दीर्घ *arch_alloc_vmap_stack(माप_प्रकार stack_size, पूर्णांक node)
अणु
	BUILD_BUG_ON(!IS_ENABLED(CONFIG_VMAP_STACK));

	वापस __vदो_स्मृति_node(stack_size, THREAD_ALIGN, THREADINFO_GFP, node,
			__builtin_वापस_address(0));
पूर्ण

#पूर्ण_अगर /* __ASM_VMAP_STACK_H */
