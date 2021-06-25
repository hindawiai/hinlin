<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_USTACK_H
#घोषणा _ASM_IA64_USTACK_H

#समावेश <यंत्र/page.h>
#समावेश <uapi/यंत्र/ustack.h>

/* The असलolute hard limit क्रम stack size is 1/2 of the mappable space in the region */
#घोषणा MAX_USER_STACK_SIZE	(RGN_MAP_LIMIT/2)
#घोषणा STACK_TOP		(0x6000000000000000UL + RGN_MAP_LIMIT)
#घोषणा STACK_TOP_MAX		STACK_TOP
#पूर्ण_अगर /* _ASM_IA64_USTACK_H */
