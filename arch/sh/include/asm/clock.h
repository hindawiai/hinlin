<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_CLOCK_H
#घोषणा __ASM_SH_CLOCK_H

#समावेश <linux/sh_clk.h>

/* Should be defined by processor-specअगरic code */
व्योम __deprecated arch_init_clk_ops(काष्ठा sh_clk_ops **, पूर्णांक type);
पूर्णांक __init arch_clk_init(व्योम);

/* arch/sh/kernel/cpu/घड़ी-cpg.c */
पूर्णांक __init __deprecated cpg_clk_init(व्योम);

/* arch/sh/kernel/cpu/घड़ी.c */
पूर्णांक clk_init(व्योम);

#पूर्ण_अगर /* __ASM_SH_CLOCK_H */
