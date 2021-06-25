<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_MMU_H
#घोषणा _ASM_MMU_H

#समावेश <यंत्र/vdso.h>

/*
 * Architecture-specअगरic state क्रम a mm_काष्ठा.
 * For the Hexagon Virtual Machine, it can be a copy
 * of the poपूर्णांकer to the page table base.
 */
काष्ठा mm_context अणु
	अचिन्हित दीर्घ दीर्घ generation;
	अचिन्हित दीर्घ ptbase;
	काष्ठा hexagon_vdso *vdso;
पूर्ण;

प्रकार काष्ठा mm_context mm_context_t;

#पूर्ण_अगर
