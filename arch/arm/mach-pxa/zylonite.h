<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_ZYLONITE_H
#घोषणा __ASM_ARCH_ZYLONITE_H

#घोषणा ZYLONITE_ETH_PHYS	0x14000000

#घोषणा EXT_GPIO(x)		(128 + (x))

#घोषणा ZYLONITE_NR_IRQS	(IRQ_BOARD_START + 32)

/* the following variables are processor specअगरic and initialized
 * by the corresponding zylonite_pxa3xx_init()
 */
बाह्य पूर्णांक gpio_eth_irq;
बाह्य पूर्णांक gpio_debug_led1;
बाह्य पूर्णांक gpio_debug_led2;

बाह्य पूर्णांक wm9713_irq;

बाह्य पूर्णांक lcd_id;
बाह्य पूर्णांक lcd_orientation;

#अगर_घोषित CONFIG_MACH_ZYLONITE300
बाह्य व्योम zylonite_pxa300_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम zylonite_pxa300_init(व्योम)
अणु
	अगर (cpu_is_pxa300() || cpu_is_pxa310())
		panic("%s: PXA300/PXA310 not supported\n", __func__);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_ZYLONITE320
बाह्य व्योम zylonite_pxa320_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम zylonite_pxa320_init(व्योम)
अणु
	अगर (cpu_is_pxa320())
		panic("%s: PXA320 not supported\n", __func__);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_ARCH_ZYLONITE_H */
