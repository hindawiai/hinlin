<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2012 Thomas Langer <thomas.langer@lantiq.com>
 * Copyright (C) 2012 John Crispin <john@phrozen.org>
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/पन.स>

#समावेश <lantiq_soc.h>

#समावेश "../prom.h"

#घोषणा SOC_FALCON	"Falcon"
#घोषणा SOC_FALCON_D	"Falcon-D"
#घोषणा SOC_FALCON_V	"Falcon-V"
#घोषणा SOC_FALCON_M	"Falcon-M"

#घोषणा COMP_FALCON	"lantiq,falcon"

#घोषणा PART_SHIFT	12
#घोषणा PART_MASK	0x0FFFF000
#घोषणा REV_SHIFT	28
#घोषणा REV_MASK	0xF0000000
#घोषणा SREV_SHIFT	22
#घोषणा SREV_MASK	0x03C00000
#घोषणा TYPE_SHIFT	26
#घोषणा TYPE_MASK	0x3C000000

/* reset, nmi and ejtag exception vectors */
#घोषणा BOOT_REG_BASE	(KSEG1 | 0x1F200000)
#घोषणा BOOT_RVEC	(BOOT_REG_BASE | 0x00)
#घोषणा BOOT_NVEC	(BOOT_REG_BASE | 0x04)
#घोषणा BOOT_EVEC	(BOOT_REG_BASE | 0x08)

व्योम __init ltq_soc_nmi_setup(व्योम)
अणु
	बाह्य व्योम (*nmi_handler)(व्योम);

	ltq_w32((अचिन्हित दीर्घ)&nmi_handler, (व्योम *)BOOT_NVEC);
पूर्ण

व्योम __init ltq_soc_ejtag_setup(व्योम)
अणु
	बाह्य व्योम (*ejtag_debug_handler)(व्योम);

	ltq_w32((अचिन्हित दीर्घ)&ejtag_debug_handler, (व्योम *)BOOT_EVEC);
पूर्ण

व्योम __init ltq_soc_detect(काष्ठा ltq_soc_info *i)
अणु
	u32 type;
	i->partnum = (ltq_r32(FALCON_CHIPID) & PART_MASK) >> PART_SHIFT;
	i->rev = (ltq_r32(FALCON_CHIPID) & REV_MASK) >> REV_SHIFT;
	i->srev = ((ltq_r32(FALCON_CHIPCONF) & SREV_MASK) >> SREV_SHIFT);
	i->compatible = COMP_FALCON;
	i->type = SOC_TYPE_FALCON;
	प्र_लिखो(i->rev_type, "%c%d%d", (i->srev & 0x4) ? ('B') : ('A'),
		i->rev & 0x7, (i->srev & 0x3) + 1);

	चयन (i->partnum) अणु
	हाल SOC_ID_FALCON:
		type = (ltq_r32(FALCON_CHIPTYPE) & TYPE_MASK) >> TYPE_SHIFT;
		चयन (type) अणु
		हाल 0:
			i->name = SOC_FALCON_D;
			अवरोध;
		हाल 1:
			i->name = SOC_FALCON_V;
			अवरोध;
		हाल 2:
			i->name = SOC_FALCON_M;
			अवरोध;
		शेष:
			i->name = SOC_FALCON;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		unreachable();
		अवरोध;
	पूर्ण

	board_nmi_handler_setup = ltq_soc_nmi_setup;
	board_ejtag_handler_setup = ltq_soc_ejtag_setup;
पूर्ण
