<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_TIMEX_H
#घोषणा _ASM_TIMEX_H

#समावेश <यंत्र-generic/समयx.h>
#समावेश <यंत्र/समयr-regs.h>
#समावेश <यंत्र/hexagon_vm.h>

/* Using TCX0 as our घड़ी.  CLOCK_TICK_RATE scheduled to be हटाओd. */
#घोषणा CLOCK_TICK_RATE              TCX0_CLK_RATE

#घोषणा ARCH_HAS_READ_CURRENT_TIMER

अटल अंतरभूत पूर्णांक पढ़ो_current_समयr(अचिन्हित दीर्घ *समयr_val)
अणु
	*समयr_val = __vmसमय_लो();
	वापस 0;
पूर्ण

#पूर्ण_अगर
