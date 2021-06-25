<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Interface क्रम functions that need to be run in पूर्णांकernal SRAM
 */

#अगर_अघोषित __ASSEMBLY__
#समावेश <plat/sram.h>

बाह्य व्योम omap2_sram_ddr_init(u32 *slow_dll_ctrl, u32 fast_dll_ctrl,
				u32 base_cs, u32 क्रमce_unlock);
बाह्य व्योम omap2_sram_reprogram_sdrc(u32 perf_level, u32 dll_val,
				      u32 mem_type);
बाह्य u32 omap2_set_prcm(u32 dpll_ctrl_val, u32 sdrc_rfr_val, पूर्णांक bypass);

बाह्य व्योम omap3_sram_restore_context(व्योम);

/* Do not use these */
बाह्य व्योम omap24xx_sram_reprogram_घड़ी(u32 ckctl, u32 dpllctl);
बाह्य अचिन्हित दीर्घ omap24xx_sram_reprogram_घड़ी_sz;

बाह्य व्योम omap242x_sram_ddr_init(u32 *slow_dll_ctrl, u32 fast_dll_ctrl,
						u32 base_cs, u32 क्रमce_unlock);
बाह्य अचिन्हित दीर्घ omap242x_sram_ddr_init_sz;

बाह्य u32 omap242x_sram_set_prcm(u32 dpll_ctrl_val, u32 sdrc_rfr_val,
						पूर्णांक bypass);
बाह्य अचिन्हित दीर्घ omap242x_sram_set_prcm_sz;

बाह्य व्योम omap242x_sram_reprogram_sdrc(u32 perf_level, u32 dll_val,
						u32 mem_type);
बाह्य अचिन्हित दीर्घ omap242x_sram_reprogram_sdrc_sz;


बाह्य व्योम omap243x_sram_ddr_init(u32 *slow_dll_ctrl, u32 fast_dll_ctrl,
						u32 base_cs, u32 क्रमce_unlock);
बाह्य अचिन्हित दीर्घ omap243x_sram_ddr_init_sz;

बाह्य u32 omap243x_sram_set_prcm(u32 dpll_ctrl_val, u32 sdrc_rfr_val,
						पूर्णांक bypass);
बाह्य अचिन्हित दीर्घ omap243x_sram_set_prcm_sz;

बाह्य व्योम omap243x_sram_reprogram_sdrc(u32 perf_level, u32 dll_val,
						u32 mem_type);
बाह्य अचिन्हित दीर्घ omap243x_sram_reprogram_sdrc_sz;

#अगर_घोषित CONFIG_PM
बाह्य व्योम omap_push_sram_idle(व्योम);
#अन्यथा
अटल अंतरभूत व्योम omap_push_sram_idle(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PM */

#पूर्ण_अगर /* __ASSEMBLY__ */

/*
 * OMAP2+: define the SRAM PA addresses.
 * Used by the SRAM management code and the idle sleep code.
 */
#घोषणा OMAP2_SRAM_PA		0x40200000
#घोषणा OMAP3_SRAM_PA           0x40200000
