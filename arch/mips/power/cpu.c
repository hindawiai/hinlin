<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Suspend support specअगरic क्रम mips.
 *
 * Copyright (C) 2009 Lemote Inc.
 * Author: Hu Hongbing <huhb@lemote.com>
 *	   Wu Zhangjin <wuzhangjin@gmail.com>
 */
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/dsp.h>

अटल u32 saved_status;
काष्ठा pt_regs saved_regs;

व्योम save_processor_state(व्योम)
अणु
	saved_status = पढ़ो_c0_status();

	अगर (is_fpu_owner())
		save_fp(current);

	save_dsp(current);
पूर्ण

व्योम restore_processor_state(व्योम)
अणु
	ग_लिखो_c0_status(saved_status);

	अगर (is_fpu_owner())
		restore_fp(current);

	restore_dsp(current);
पूर्ण

पूर्णांक pfn_is_nosave(अचिन्हित दीर्घ pfn)
अणु
	अचिन्हित दीर्घ nosave_begin_pfn = PFN_DOWN(__pa(&__nosave_begin));
	अचिन्हित दीर्घ nosave_end_pfn = PFN_UP(__pa(&__nosave_end));

	वापस	(pfn >= nosave_begin_pfn) && (pfn < nosave_end_pfn);
पूर्ण
