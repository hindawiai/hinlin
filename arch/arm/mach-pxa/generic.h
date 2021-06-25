<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/arch/arm/mach-pxa/generic.h
 *
 * Author:	Nicolas Pitre
 * Copyright:	MontaVista Software Inc.
 */

#समावेश <linux/reboot.h>

काष्ठा irq_data;

बाह्य अचिन्हित पूर्णांक get_clk_frequency_khz(पूर्णांक info);
बाह्य व्योम __init pxa_dt_irq_init(पूर्णांक (*fn)(काष्ठा irq_data *,
					     अचिन्हित पूर्णांक));
बाह्य व्योम __init pxa_map_io(व्योम);
बाह्य व्योम pxa_समयr_init(व्योम);

#घोषणा SET_BANK(__nr,__start,__size) \
	mi->bank[__nr].start = (__start), \
	mi->bank[__nr].size = (__size)

#घोषणा ARRAY_AND_SIZE(x)	(x), ARRAY_SIZE(x)

#घोषणा pxa25x_handle_irq icip_handle_irq
बाह्य पूर्णांक __init pxa25x_घड़ीs_init(व्योम);
बाह्य व्योम __init pxa25x_init_irq(व्योम);
बाह्य व्योम __init pxa25x_map_io(व्योम);
बाह्य व्योम __init pxa26x_init_irq(व्योम);

#घोषणा pxa27x_handle_irq ichp_handle_irq
बाह्य पूर्णांक __init pxa27x_घड़ीs_init(व्योम);
बाह्य अचिन्हित	pxa27x_get_clk_frequency_khz(पूर्णांक);
बाह्य व्योम __init pxa27x_init_irq(व्योम);
बाह्य व्योम __init pxa27x_map_io(व्योम);

#घोषणा pxa3xx_handle_irq ichp_handle_irq
बाह्य पूर्णांक __init pxa3xx_घड़ीs_init(व्योम);
बाह्य व्योम __init pxa3xx_init_irq(व्योम);
बाह्य व्योम __init pxa3xx_map_io(व्योम);

बाह्य काष्ठा syscore_ops pxa_irq_syscore_ops;
बाह्य काष्ठा syscore_ops pxa2xx_mfp_syscore_ops;
बाह्य काष्ठा syscore_ops pxa3xx_mfp_syscore_ops;

व्योम __init pxa_set_ffuart_info(व्योम *info);
व्योम __init pxa_set_btuart_info(व्योम *info);
व्योम __init pxa_set_stuart_info(व्योम *info);
व्योम __init pxa_set_hwuart_info(व्योम *info);

व्योम pxa_restart(क्रमागत reboot_mode, स्थिर अक्षर *);

#अगर defined(CONFIG_PXA25x) || defined(CONFIG_PXA27x)
बाह्य व्योम pxa2xx_clear_reset_status(अचिन्हित पूर्णांक);
#अन्यथा
अटल अंतरभूत व्योम pxa2xx_clear_reset_status(अचिन्हित पूर्णांक mask) अणुपूर्ण
#पूर्ण_अगर

/*
 * Once fully converted to the घड़ी framework, all these functions should be
 * हटाओd, and replaced with a clk_get(शून्य, "core").
 */
#अगर_घोषित CONFIG_PXA25x
बाह्य अचिन्हित pxa25x_get_clk_frequency_khz(पूर्णांक);
#अन्यथा
#घोषणा pxa25x_get_clk_frequency_khz(x)		(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PXA27x
#अन्यथा
#घोषणा pxa27x_get_clk_frequency_khz(x)		(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PXA3xx
बाह्य अचिन्हित	pxa3xx_get_clk_frequency_khz(पूर्णांक);
#अन्यथा
#घोषणा pxa3xx_get_clk_frequency_khz(x)		(0)
#पूर्ण_अगर
