<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARM_MMU_H
#घोषणा __ARM_MMU_H

#अगर_घोषित CONFIG_MMU

प्रकार काष्ठा अणु
#अगर_घोषित CONFIG_CPU_HAS_ASID
	atomic64_t	id;
#अन्यथा
	पूर्णांक		चयन_pending;
#पूर्ण_अगर
	अचिन्हित पूर्णांक	vदो_स्मृति_seq;
	अचिन्हित दीर्घ	sigpage;
#अगर_घोषित CONFIG_VDSO
	अचिन्हित दीर्घ	vdso;
#पूर्ण_अगर
#अगर_घोषित CONFIG_BINFMT_ELF_FDPIC
	अचिन्हित दीर्घ	exec_fdpic_loadmap;
	अचिन्हित दीर्घ	पूर्णांकerp_fdpic_loadmap;
#पूर्ण_अगर
पूर्ण mm_context_t;

#अगर_घोषित CONFIG_CPU_HAS_ASID
#घोषणा ASID_BITS	8
#घोषणा ASID_MASK	((~0ULL) << ASID_BITS)
#घोषणा ASID(mm)	((अचिन्हित पूर्णांक)((mm)->context.id.counter & ~ASID_MASK))
#अन्यथा
#घोषणा ASID(mm)	(0)
#पूर्ण_अगर

#अन्यथा

/*
 * From nommu.h:
 *  Copyright (C) 2002, David McCullough <davidm@snapgear.com>
 *  modअगरied क्रम 2.6 by Hyok S. Choi <hyok.choi@samsung.com>
 */
प्रकार काष्ठा अणु
	अचिन्हित दीर्घ	end_brk;
#अगर_घोषित CONFIG_BINFMT_ELF_FDPIC
	अचिन्हित दीर्घ	exec_fdpic_loadmap;
	अचिन्हित दीर्घ	पूर्णांकerp_fdpic_loadmap;
#पूर्ण_अगर
पूर्ण mm_context_t;

#पूर्ण_अगर

#पूर्ण_अगर
