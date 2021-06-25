<शैली गुरु>
/*
 * Header क्रम code common to all DaVinci machines.
 *
 * Author: Kevin Hilman, MontaVista Software, Inc. <source@mvista.com>
 *
 * 2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 */

#अगर_अघोषित __ARCH_ARM_MACH_DAVINCI_COMMON_H
#घोषणा __ARCH_ARM_MACH_DAVINCI_COMMON_H

#समावेश <linux/clk.h>
#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/reboot.h>

#समावेश <यंत्र/irq.h>

#घोषणा DAVINCI_INTC_START		NR_IRQS
#घोषणा DAVINCI_INTC_IRQ(_irqnum)	(DAVINCI_INTC_START + (_irqnum))

काष्ठा davinci_gpio_controller;

/*
 * SoC info passed पूर्णांकo common davinci modules.
 *
 * Base addresses in this काष्ठाure should be physical and not भव.
 * Modules that take such base addresses, should पूर्णांकernally ioremap() them to
 * use.
 */
काष्ठा davinci_soc_info अणु
	काष्ठा map_desc			*io_desc;
	अचिन्हित दीर्घ			io_desc_num;
	u32				cpu_id;
	u32				jtag_id;
	u32				jtag_id_reg;
	काष्ठा davinci_id		*ids;
	अचिन्हित दीर्घ			ids_num;
	u32				pinmux_base;
	स्थिर काष्ठा mux_config		*pinmux_pins;
	अचिन्हित दीर्घ			pinmux_pins_num;
	पूर्णांक				gpio_type;
	u32				gpio_base;
	अचिन्हित			gpio_num;
	अचिन्हित			gpio_irq;
	अचिन्हित			gpio_unbanked;
	काष्ठा davinci_gpio_controller	*gpio_ctlrs;
	पूर्णांक				gpio_ctlrs_num;
	काष्ठा emac_platक्रमm_data	*emac_pdata;
	dma_addr_t			sram_dma;
	अचिन्हित			sram_len;
पूर्ण;

बाह्य काष्ठा davinci_soc_info davinci_soc_info;

बाह्य व्योम davinci_common_init(स्थिर काष्ठा davinci_soc_info *soc_info);
बाह्य व्योम davinci_init_ide(व्योम);
व्योम davinci_init_late(व्योम);

#अगर_घोषित CONFIG_CPU_FREQ
पूर्णांक davinci_cpufreq_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक davinci_cpufreq_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SUSPEND
पूर्णांक davinci_pm_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक davinci_pm_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

व्योम __init pdata_quirks_init(व्योम);

#घोषणा SRAM_SIZE	SZ_128K

#पूर्ण_अगर /* __ARCH_ARM_MACH_DAVINCI_COMMON_H */
