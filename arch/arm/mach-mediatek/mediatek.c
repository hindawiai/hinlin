<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device Tree support क्रम Mediatek SoCs
 *
 * Copyright (c) 2014 MunकरोReader S.L.
 * Author: Matthias Brugger <matthias.bgg@gmail.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/mach/arch.h>
#समावेश <linux/of.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/घड़ीsource.h>


#घोषणा GPT6_CON_MT65xx 0x10008060
#घोषणा GPT_ENABLE      0x31

अटल व्योम __init mediatek_समयr_init(व्योम)
अणु
	व्योम __iomem *gpt_base;

	अगर (of_machine_is_compatible("mediatek,mt6589") ||
	    of_machine_is_compatible("mediatek,mt7623") ||
	    of_machine_is_compatible("mediatek,mt8135") ||
	    of_machine_is_compatible("mediatek,mt8127")) अणु
		/* turn on GPT6 which ungates arch समयr घड़ीs */
		gpt_base = ioremap(GPT6_CON_MT65xx, 0x04);

		/* enable घड़ी and set to मुक्त-run */
		ग_लिखोl(GPT_ENABLE, gpt_base);
		iounmap(gpt_base);
	पूर्ण

	of_clk_init(शून्य);
	समयr_probe();
पूर्ण;

अटल स्थिर अक्षर * स्थिर mediatek_board_dt_compat[] = अणु
	"mediatek,mt2701",
	"mediatek,mt6589",
	"mediatek,mt6592",
	"mediatek,mt7623",
	"mediatek,mt7629",
	"mediatek,mt8127",
	"mediatek,mt8135",
	शून्य,
पूर्ण;

DT_MACHINE_START(MEDIATEK_DT, "Mediatek Cortex-A7 (Device Tree)")
	.dt_compat	= mediatek_board_dt_compat,
	.init_समय	= mediatek_समयr_init,
MACHINE_END
