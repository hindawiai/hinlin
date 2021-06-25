<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *  Copyright (C) 2010 John Crispin <john@phrozen.org>
 */

#समावेश <linux/cpu.h>
#समावेश <lantiq_soc.h>
#समावेश <यंत्र/setup.h>

#घोषणा ASC_BUF		1024
#घोषणा LTQ_ASC_FSTAT	((u32 *)(LTQ_EARLY_ASC + 0x0048))
#अगर_घोषित __BIG_ENDIAN
#घोषणा LTQ_ASC_TBUF	((u32 *)(LTQ_EARLY_ASC + 0x0020 + 3))
#अन्यथा
#घोषणा LTQ_ASC_TBUF	((u32 *)(LTQ_EARLY_ASC + 0x0020))
#पूर्ण_अगर
#घोषणा TXMASK		0x3F00
#घोषणा TXOFFSET	8

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	करो अणु पूर्ण जबतक ((ltq_r32(LTQ_ASC_FSTAT) & TXMASK) >> TXOFFSET);
	अगर (c == '\n')
		ltq_w8('\r', LTQ_ASC_TBUF);
	ltq_w8(c, LTQ_ASC_TBUF);
	local_irq_restore(flags);
पूर्ण
