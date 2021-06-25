<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2016 Qualcomm Atheros, Inc. All rights reserved.
 * Copyright (c) 2015 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _AHB_H_
#घोषणा _AHB_H_

#समावेश <linux/platक्रमm_device.h>

काष्ठा ath10k_ahb अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *mem;
	अचिन्हित दीर्घ mem_len;
	व्योम __iomem *gcc_mem;
	व्योम __iomem *tcsr_mem;

	पूर्णांक irq;

	काष्ठा clk *cmd_clk;
	काष्ठा clk *ref_clk;
	काष्ठा clk *rtc_clk;

	काष्ठा reset_control *core_cold_rst;
	काष्ठा reset_control *radio_cold_rst;
	काष्ठा reset_control *radio_warm_rst;
	काष्ठा reset_control *radio_srअगर_rst;
	काष्ठा reset_control *cpu_init_rst;
पूर्ण;

#अगर_घोषित CONFIG_ATH10K_AHB

#घोषणा ATH10K_GCC_REG_BASE                  0x1800000
#घोषणा ATH10K_GCC_REG_SIZE                  0x60000

#घोषणा ATH10K_TCSR_REG_BASE                 0x1900000
#घोषणा ATH10K_TCSR_REG_SIZE                 0x80000

#घोषणा ATH10K_AHB_GCC_FEPLL_PLL_DIV         0x2f020
#घोषणा ATH10K_AHB_WIFI_SCRATCH_5_REG        0x4f014

#घोषणा ATH10K_AHB_WLAN_CORE_ID_REG          0x82030

#घोषणा ATH10K_AHB_TCSR_WIFI0_GLB_CFG        0x49000
#घोषणा ATH10K_AHB_TCSR_WIFI1_GLB_CFG        0x49004
#घोषणा TCSR_WIFIX_GLB_CFG_DISABLE_CORE_CLK  BIT(25)

#घोषणा ATH10K_AHB_TCSR_WCSS0_HALTREQ        0x52000
#घोषणा ATH10K_AHB_TCSR_WCSS1_HALTREQ        0x52010
#घोषणा ATH10K_AHB_TCSR_WCSS0_HALTACK        0x52004
#घोषणा ATH10K_AHB_TCSR_WCSS1_HALTACK        0x52014

#घोषणा ATH10K_AHB_AXI_BUS_HALT_TIMEOUT      10 /* msec */
#घोषणा AHB_AXI_BUS_HALT_REQ                 1
#घोषणा AHB_AXI_BUS_HALT_ACK                 1

#घोषणा ATH10K_AHB_CORE_CTRL_CPU_INTR_MASK   1

पूर्णांक ath10k_ahb_init(व्योम);
व्योम ath10k_ahb_निकास(व्योम);

#अन्यथा /* CONFIG_ATH10K_AHB */

अटल अंतरभूत पूर्णांक ath10k_ahb_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath10k_ahb_निकास(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH10K_AHB */

#पूर्ण_अगर /* _AHB_H_ */
