<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/arch/arm/mach-sa1100/generic.h
 *
 * Author: Nicolas Pitre
 */
#समावेश <linux/cpufreq.h>
#समावेश <linux/reboot.h>

बाह्य व्योम sa1100_समयr_init(व्योम);
बाह्य व्योम __init sa1100_map_io(व्योम);
बाह्य व्योम __init sa1100_init_irq(व्योम);
बाह्य व्योम __init sa1100_init_gpio(व्योम);
बाह्य व्योम sa11x0_restart(क्रमागत reboot_mode, स्थिर अक्षर *);
बाह्य व्योम sa11x0_init_late(व्योम);

#घोषणा SET_BANK(__nr,__start,__size) \
	mi->bank[__nr].start = (__start), \
	mi->bank[__nr].size = (__size)

बाह्य व्योम sa1110_mb_enable(व्योम);
बाह्य व्योम sa1110_mb_disable(व्योम);

बाह्य काष्ठा cpufreq_frequency_table sa11x0_freq_table[];
बाह्य अचिन्हित पूर्णांक sa11x0_माला_लोpeed(अचिन्हित पूर्णांक cpu);

काष्ठा flash_platक्रमm_data;
काष्ठा resource;

व्योम sa11x0_रेजिस्टर_mtd(काष्ठा flash_platक्रमm_data *flash,
			 काष्ठा resource *res, पूर्णांक nr);

काष्ठा irda_platक्रमm_data;
व्योम sa11x0_रेजिस्टर_irda(काष्ठा irda_platक्रमm_data *irda);

काष्ठा mcp_plat_data;
व्योम sa11x0_ppc_configure_mcp(व्योम);
व्योम sa11x0_रेजिस्टर_mcp(काष्ठा mcp_plat_data *data);

काष्ठा sa1100fb_mach_info;
व्योम sa11x0_रेजिस्टर_lcd(काष्ठा sa1100fb_mach_info *inf);

#अगर_घोषित CONFIG_PM
पूर्णांक sa11x0_pm_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक sa11x0_pm_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

पूर्णांक sa11xx_clk_init(व्योम);

काष्ठा gpiod_lookup_table;
व्योम sa11x0_रेजिस्टर_pcmcia(पूर्णांक socket, काष्ठा gpiod_lookup_table *);

काष्ठा fixed_voltage_config;
काष्ठा regulator_consumer_supply;
पूर्णांक sa11x0_रेजिस्टर_fixed_regulator(पूर्णांक n, काष्ठा fixed_voltage_config *cfg,
	काष्ठा regulator_consumer_supply *supplies, अचिन्हित num_supplies,
	bool uses_gpio);
