<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  OMAP GPMC (General Purpose Memory Controller) defines
 */

#समावेश <linux/platक्रमm_data/gpmc-omap.h>

#घोषणा GPMC_CONFIG_WP		0x00000005

/* IRQ numbers in GPMC IRQ करोमुख्य क्रम legacy boot use */
#घोषणा GPMC_IRQ_FIFOEVENTENABLE	0
#घोषणा GPMC_IRQ_COUNT_EVENT		1

/**
 * gpmc_nand_ops - Interface between न_अंकD and GPMC
 * @nand_ग_लिखो_buffer_empty: get the न_अंकD ग_लिखो buffer empty status.
 */
काष्ठा gpmc_nand_ops अणु
	bool (*nand_ग_लिखोbuffer_empty)(व्योम);
पूर्ण;

काष्ठा gpmc_nand_regs;

काष्ठा gpmc_onenand_info अणु
	bool sync_पढ़ो;
	bool sync_ग_लिखो;
	पूर्णांक burst_len;
पूर्ण;

#अगर IS_ENABLED(CONFIG_OMAP_GPMC)
काष्ठा gpmc_nand_ops *gpmc_omap_get_nand_ops(काष्ठा gpmc_nand_regs *regs,
					     पूर्णांक cs);
/**
 * gpmc_omap_onenand_set_timings - set optimized sync timings.
 * @cs:      Chip Select Region
 * @freq:    Chip frequency
 * @latency: Burst latency cycle count
 * @info:    Structure describing parameters used
 *
 * Sets optimized timings क्रम the @cs region based on @freq and @latency.
 * Updates the @info काष्ठाure based on the GPMC settings.
 */
पूर्णांक gpmc_omap_onenand_set_timings(काष्ठा device *dev, पूर्णांक cs, पूर्णांक freq,
				  पूर्णांक latency,
				  काष्ठा gpmc_onenand_info *info);

#अन्यथा
अटल अंतरभूत काष्ठा gpmc_nand_ops *gpmc_omap_get_nand_ops(काष्ठा gpmc_nand_regs *regs,
							   पूर्णांक cs)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत
पूर्णांक gpmc_omap_onenand_set_timings(काष्ठा device *dev, पूर्णांक cs, पूर्णांक freq,
				  पूर्णांक latency,
				  काष्ठा gpmc_onenand_info *info)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_OMAP_GPMC */

बाह्य पूर्णांक gpmc_calc_timings(काष्ठा gpmc_timings *gpmc_t,
			     काष्ठा gpmc_settings *gpmc_s,
			     काष्ठा gpmc_device_timings *dev_t);

काष्ठा device_node;

बाह्य पूर्णांक gpmc_get_client_irq(अचिन्हित irq_config);

बाह्य अचिन्हित पूर्णांक gpmc_ticks_to_ns(अचिन्हित पूर्णांक ticks);

बाह्य व्योम gpmc_cs_ग_लिखो_reg(पूर्णांक cs, पूर्णांक idx, u32 val);
बाह्य पूर्णांक gpmc_calc_भागider(अचिन्हित पूर्णांक sync_clk);
बाह्य पूर्णांक gpmc_cs_set_timings(पूर्णांक cs, स्थिर काष्ठा gpmc_timings *t,
			       स्थिर काष्ठा gpmc_settings *s);
बाह्य पूर्णांक gpmc_cs_program_settings(पूर्णांक cs, काष्ठा gpmc_settings *p);
बाह्य पूर्णांक gpmc_cs_request(पूर्णांक cs, अचिन्हित दीर्घ size, अचिन्हित दीर्घ *base);
बाह्य व्योम gpmc_cs_मुक्त(पूर्णांक cs);
बाह्य पूर्णांक gpmc_configure(पूर्णांक cmd, पूर्णांक wval);
बाह्य व्योम gpmc_पढ़ो_settings_dt(काष्ठा device_node *np,
				  काष्ठा gpmc_settings *p);

बाह्य व्योम omap3_gpmc_save_context(व्योम);
बाह्य व्योम omap3_gpmc_restore_context(व्योम);

काष्ठा gpmc_timings;
काष्ठा omap_nand_platक्रमm_data;
काष्ठा omap_onenand_platक्रमm_data;

#अगर IS_ENABLED(CONFIG_MTD_ONEन_अंकD_OMAP2)
बाह्य पूर्णांक gpmc_onenand_init(काष्ठा omap_onenand_platक्रमm_data *d);
#अन्यथा
#घोषणा board_onenand_data	शून्य
अटल अंतरभूत पूर्णांक gpmc_onenand_init(काष्ठा omap_onenand_platक्रमm_data *d)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
