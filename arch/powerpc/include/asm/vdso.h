<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_VDSO_H
#घोषणा _ASM_POWERPC_VDSO_H

/* Default map addresses क्रम 32bit vDSO */
#घोषणा VDSO32_MBASE	0x100000

#घोषणा VDSO_VERSION_STRING	LINUX_2.6.15

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_PPC64
#समावेश <generated/vdso64-offsets.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_VDSO32
#समावेश <generated/vdso32-offsets.h>
#पूर्ण_अगर

#घोषणा VDSO64_SYMBOL(base, name) ((अचिन्हित दीर्घ)(base) + (vdso64_offset_##name))

#घोषणा VDSO32_SYMBOL(base, name) ((अचिन्हित दीर्घ)(base) + (vdso32_offset_##name))

पूर्णांक vdso_अ_लोpu_init(व्योम);

#अन्यथा /* __ASSEMBLY__ */

#अगर_घोषित __VDSO64__
#घोषणा V_FUNCTION_BEGIN(name)		\
	.globl name;			\
	name:				\

#घोषणा V_FUNCTION_END(name)		\
	.size name,.-name;

#घोषणा V_LOCAL_FUNC(name) (name)
#पूर्ण_अगर /* __VDSO64__ */

#अगर_घोषित __VDSO32__

#घोषणा V_FUNCTION_BEGIN(name)		\
	.globl name;			\
	.type name,@function; 		\
	name:				\

#घोषणा V_FUNCTION_END(name)		\
	.size name,.-name;

#घोषणा V_LOCAL_FUNC(name) (name)

#पूर्ण_अगर /* __VDSO32__ */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_VDSO_H */
