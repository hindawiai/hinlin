<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Limited
 */
#अगर_अघोषित __ASM_VDSO_H
#घोषणा __ASM_VDSO_H

/*
 * Default link address क्रम the vDSO.
 * Since we अक्रमomise the VDSO mapping, there's little poपूर्णांक in trying
 * to prelink this.
 */
#घोषणा VDSO_LBASE	0x0

#घोषणा __VVAR_PAGES    2

#अगर_अघोषित __ASSEMBLY__

#समावेश <generated/vdso-offsets.h>
#अगर_घोषित CONFIG_COMPAT_VDSO
#समावेश <generated/vdso32-offsets.h>
#पूर्ण_अगर

#घोषणा VDSO_SYMBOL(base, name)						   \
(अणु									   \
	(व्योम *)(vdso_offset_##name - VDSO_LBASE + (अचिन्हित दीर्घ)(base)); \
पूर्ण)

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_VDSO_H */
