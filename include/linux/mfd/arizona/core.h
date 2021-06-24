<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Arizona MFD पूर्णांकernals
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित _WM_ARIZONA_CORE_H
#घोषणा _WM_ARIZONA_CORE_H

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mfd/arizona/pdata.h>

#घोषणा ARIZONA_MAX_CORE_SUPPLIES 2

क्रमागत अणु
	ARIZONA_MCLK1,
	ARIZONA_MCLK2,
	ARIZONA_NUM_MCLK
पूर्ण;

क्रमागत arizona_type अणु
	WM5102 = 1,
	WM5110 = 2,
	WM8997 = 3,
	WM8280 = 4,
	WM8998 = 5,
	WM1814 = 6,
	WM1831 = 7,
	CS47L24 = 8,
पूर्ण;

#घोषणा ARIZONA_IRQ_GP1                    0
#घोषणा ARIZONA_IRQ_GP2                    1
#घोषणा ARIZONA_IRQ_GP3                    2
#घोषणा ARIZONA_IRQ_GP4                    3
#घोषणा ARIZONA_IRQ_GP5_FALL               4
#घोषणा ARIZONA_IRQ_GP5_RISE               5
#घोषणा ARIZONA_IRQ_JD_FALL                6
#घोषणा ARIZONA_IRQ_JD_RISE                7
#घोषणा ARIZONA_IRQ_DSP1_RAM_RDY           8
#घोषणा ARIZONA_IRQ_DSP2_RAM_RDY           9
#घोषणा ARIZONA_IRQ_DSP3_RAM_RDY          10
#घोषणा ARIZONA_IRQ_DSP4_RAM_RDY          11
#घोषणा ARIZONA_IRQ_DSP_IRQ1              12
#घोषणा ARIZONA_IRQ_DSP_IRQ2              13
#घोषणा ARIZONA_IRQ_DSP_IRQ3              14
#घोषणा ARIZONA_IRQ_DSP_IRQ4              15
#घोषणा ARIZONA_IRQ_DSP_IRQ5              16
#घोषणा ARIZONA_IRQ_DSP_IRQ6              17
#घोषणा ARIZONA_IRQ_DSP_IRQ7              18
#घोषणा ARIZONA_IRQ_DSP_IRQ8              19
#घोषणा ARIZONA_IRQ_SPK_OVERHEAT_WARN     20
#घोषणा ARIZONA_IRQ_SPK_OVERHEAT          21
#घोषणा ARIZONA_IRQ_MICDET                22
#घोषणा ARIZONA_IRQ_HPDET                 23
#घोषणा ARIZONA_IRQ_WSEQ_DONE             24
#घोषणा ARIZONA_IRQ_DRC2_SIG_DET          25
#घोषणा ARIZONA_IRQ_DRC1_SIG_DET          26
#घोषणा ARIZONA_IRQ_ASRC2_LOCK            27
#घोषणा ARIZONA_IRQ_ASRC1_LOCK            28
#घोषणा ARIZONA_IRQ_UNDERCLOCKED          29
#घोषणा ARIZONA_IRQ_OVERCLOCKED           30
#घोषणा ARIZONA_IRQ_FLL2_LOCK             31
#घोषणा ARIZONA_IRQ_FLL1_LOCK             32
#घोषणा ARIZONA_IRQ_CLKGEN_ERR            33
#घोषणा ARIZONA_IRQ_CLKGEN_ERR_ASYNC      34
#घोषणा ARIZONA_IRQ_ASRC_CFG_ERR          35
#घोषणा ARIZONA_IRQ_AIF3_ERR              36
#घोषणा ARIZONA_IRQ_AIF2_ERR              37
#घोषणा ARIZONA_IRQ_AIF1_ERR              38
#घोषणा ARIZONA_IRQ_CTRLIF_ERR            39
#घोषणा ARIZONA_IRQ_MIXER_DROPPED_SAMPLES 40
#घोषणा ARIZONA_IRQ_ASYNC_CLK_ENA_LOW     41
#घोषणा ARIZONA_IRQ_SYSCLK_ENA_LOW        42
#घोषणा ARIZONA_IRQ_ISRC1_CFG_ERR         43
#घोषणा ARIZONA_IRQ_ISRC2_CFG_ERR         44
#घोषणा ARIZONA_IRQ_BOOT_DONE             45
#घोषणा ARIZONA_IRQ_DCS_DAC_DONE          46
#घोषणा ARIZONA_IRQ_DCS_HP_DONE           47
#घोषणा ARIZONA_IRQ_FLL2_CLOCK_OK         48
#घोषणा ARIZONA_IRQ_FLL1_CLOCK_OK         49
#घोषणा ARIZONA_IRQ_MICD_CLAMP_RISE	  50
#घोषणा ARIZONA_IRQ_MICD_CLAMP_FALL	  51
#घोषणा ARIZONA_IRQ_HP3R_DONE             52
#घोषणा ARIZONA_IRQ_HP3L_DONE             53
#घोषणा ARIZONA_IRQ_HP2R_DONE             54
#घोषणा ARIZONA_IRQ_HP2L_DONE             55
#घोषणा ARIZONA_IRQ_HP1R_DONE             56
#घोषणा ARIZONA_IRQ_HP1L_DONE             57
#घोषणा ARIZONA_IRQ_ISRC3_CFG_ERR         58
#घोषणा ARIZONA_IRQ_DSP_SHARED_WR_COLL    59
#घोषणा ARIZONA_IRQ_SPK_SHUTDOWN          60
#घोषणा ARIZONA_IRQ_SPK1R_SHORT           61
#घोषणा ARIZONA_IRQ_SPK1L_SHORT           62
#घोषणा ARIZONA_IRQ_HP3R_SC_NEG           63
#घोषणा ARIZONA_IRQ_HP3R_SC_POS           64
#घोषणा ARIZONA_IRQ_HP3L_SC_NEG           65
#घोषणा ARIZONA_IRQ_HP3L_SC_POS           66
#घोषणा ARIZONA_IRQ_HP2R_SC_NEG           67
#घोषणा ARIZONA_IRQ_HP2R_SC_POS           68
#घोषणा ARIZONA_IRQ_HP2L_SC_NEG           69
#घोषणा ARIZONA_IRQ_HP2L_SC_POS           70
#घोषणा ARIZONA_IRQ_HP1R_SC_NEG           71
#घोषणा ARIZONA_IRQ_HP1R_SC_POS           72
#घोषणा ARIZONA_IRQ_HP1L_SC_NEG           73
#घोषणा ARIZONA_IRQ_HP1L_SC_POS           74

#घोषणा ARIZONA_NUM_IRQ                   75

काष्ठा snd_soc_dapm_context;

काष्ठा arizona अणु
	काष्ठा regmap *regmap;
	काष्ठा device *dev;

	क्रमागत arizona_type type;
	अचिन्हित पूर्णांक rev;

	पूर्णांक num_core_supplies;
	काष्ठा regulator_bulk_data core_supplies[ARIZONA_MAX_CORE_SUPPLIES];
	काष्ठा regulator *dcvdd;
	bool has_fully_घातered_off;

	काष्ठा arizona_pdata pdata;

	अचिन्हित पूर्णांक बाह्यal_dcvdd:1;

	पूर्णांक irq;
	काष्ठा irq_करोमुख्य *virq;
	काष्ठा regmap_irq_chip_data *aod_irq_chip;
	काष्ठा regmap_irq_chip_data *irq_chip;

	bool hpdet_clamp;
	अचिन्हित पूर्णांक hp_ena;

	काष्ठा mutex clk_lock;
	पूर्णांक clk32k_ref;

	काष्ठा clk *mclk[ARIZONA_NUM_MCLK];

	bool ctrlअगर_error;

	काष्ठा snd_soc_dapm_context *dapm;

	पूर्णांक tdm_width[ARIZONA_MAX_AIF];
	पूर्णांक tdm_slots[ARIZONA_MAX_AIF];

	uपूर्णांक16_t dac_comp_coeff;
	uपूर्णांक8_t dac_comp_enabled;
	काष्ठा mutex dac_comp_lock;

	काष्ठा blocking_notअगरier_head notअगरier;
पूर्ण;

अटल अंतरभूत पूर्णांक arizona_call_notअगरiers(काष्ठा arizona *arizona,
					 अचिन्हित दीर्घ event,
					 व्योम *data)
अणु
	वापस blocking_notअगरier_call_chain(&arizona->notअगरier, event, data);
पूर्ण

पूर्णांक arizona_clk32k_enable(काष्ठा arizona *arizona);
पूर्णांक arizona_clk32k_disable(काष्ठा arizona *arizona);

पूर्णांक arizona_request_irq(काष्ठा arizona *arizona, पूर्णांक irq, अक्षर *name,
			irq_handler_t handler, व्योम *data);
व्योम arizona_मुक्त_irq(काष्ठा arizona *arizona, पूर्णांक irq, व्योम *data);
पूर्णांक arizona_set_irq_wake(काष्ठा arizona *arizona, पूर्णांक irq, पूर्णांक on);

#अगर_घोषित CONFIG_MFD_WM5102
पूर्णांक wm5102_patch(काष्ठा arizona *arizona);
#अन्यथा
अटल अंतरभूत पूर्णांक wm5102_patch(काष्ठा arizona *arizona)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक wm5110_patch(काष्ठा arizona *arizona);
पूर्णांक cs47l24_patch(काष्ठा arizona *arizona);
पूर्णांक wm8997_patch(काष्ठा arizona *arizona);
पूर्णांक wm8998_patch(काष्ठा arizona *arizona);

#पूर्ण_अगर
