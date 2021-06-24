<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008
 * Guennadi Liakhovetski, DENX Software Engineering, <lg@denx.de>
 *
 * Copyright (C) 2005-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#अगर_अघोषित _IPU_INTERN_H_
#घोषणा _IPU_INTERN_H_

#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>

/* IPU Common रेजिस्टरs */
#घोषणा IPU_CONF		0x00
#घोषणा IPU_CHA_BUF0_RDY	0x04
#घोषणा IPU_CHA_BUF1_RDY	0x08
#घोषणा IPU_CHA_DB_MODE_SEL	0x0C
#घोषणा IPU_CHA_CUR_BUF		0x10
#घोषणा IPU_FS_PROC_FLOW	0x14
#घोषणा IPU_FS_DISP_FLOW	0x18
#घोषणा IPU_TASKS_STAT		0x1C
#घोषणा IPU_IMA_ADDR		0x20
#घोषणा IPU_IMA_DATA		0x24
#घोषणा IPU_INT_CTRL_1		0x28
#घोषणा IPU_INT_CTRL_2		0x2C
#घोषणा IPU_INT_CTRL_3		0x30
#घोषणा IPU_INT_CTRL_4		0x34
#घोषणा IPU_INT_CTRL_5		0x38
#घोषणा IPU_INT_STAT_1		0x3C
#घोषणा IPU_INT_STAT_2		0x40
#घोषणा IPU_INT_STAT_3		0x44
#घोषणा IPU_INT_STAT_4		0x48
#घोषणा IPU_INT_STAT_5		0x4C
#घोषणा IPU_BRK_CTRL_1		0x50
#घोषणा IPU_BRK_CTRL_2		0x54
#घोषणा IPU_BRK_STAT		0x58
#घोषणा IPU_DIAGB_CTRL		0x5C

/* IPU_CONF Register bits */
#घोषणा IPU_CONF_CSI_EN		0x00000001
#घोषणा IPU_CONF_IC_EN		0x00000002
#घोषणा IPU_CONF_ROT_EN		0x00000004
#घोषणा IPU_CONF_PF_EN		0x00000008
#घोषणा IPU_CONF_SDC_EN		0x00000010
#घोषणा IPU_CONF_ADC_EN		0x00000020
#घोषणा IPU_CONF_DI_EN		0x00000040
#घोषणा IPU_CONF_DU_EN		0x00000080
#घोषणा IPU_CONF_PXL_ENDIAN	0x00000100

/* Image Converter Registers */
#घोषणा IC_CONF			0x88
#घोषणा IC_PRP_ENC_RSC		0x8C
#घोषणा IC_PRP_VF_RSC		0x90
#घोषणा IC_PP_RSC		0x94
#घोषणा IC_CMBP_1		0x98
#घोषणा IC_CMBP_2		0x9C
#घोषणा PF_CONF			0xA0
#घोषणा IDMAC_CONF		0xA4
#घोषणा IDMAC_CHA_EN		0xA8
#घोषणा IDMAC_CHA_PRI		0xAC
#घोषणा IDMAC_CHA_BUSY		0xB0

/* Image Converter Register bits */
#घोषणा IC_CONF_PRPENC_EN	0x00000001
#घोषणा IC_CONF_PRPENC_CSC1	0x00000002
#घोषणा IC_CONF_PRPENC_ROT_EN	0x00000004
#घोषणा IC_CONF_PRPVF_EN	0x00000100
#घोषणा IC_CONF_PRPVF_CSC1	0x00000200
#घोषणा IC_CONF_PRPVF_CSC2	0x00000400
#घोषणा IC_CONF_PRPVF_CMB	0x00000800
#घोषणा IC_CONF_PRPVF_ROT_EN	0x00001000
#घोषणा IC_CONF_PP_EN		0x00010000
#घोषणा IC_CONF_PP_CSC1		0x00020000
#घोषणा IC_CONF_PP_CSC2		0x00040000
#घोषणा IC_CONF_PP_CMB		0x00080000
#घोषणा IC_CONF_PP_ROT_EN	0x00100000
#घोषणा IC_CONF_IC_GLB_LOC_A	0x10000000
#घोषणा IC_CONF_KEY_COLOR_EN	0x20000000
#घोषणा IC_CONF_RWS_EN		0x40000000
#घोषणा IC_CONF_CSI_MEM_WR_EN	0x80000000

#घोषणा IDMA_CHAN_INVALID	0x000000FF
#घोषणा IDMA_IC_0		0x00000001
#घोषणा IDMA_IC_1		0x00000002
#घोषणा IDMA_IC_2		0x00000004
#घोषणा IDMA_IC_3		0x00000008
#घोषणा IDMA_IC_4		0x00000010
#घोषणा IDMA_IC_5		0x00000020
#घोषणा IDMA_IC_6		0x00000040
#घोषणा IDMA_IC_7		0x00000080
#घोषणा IDMA_IC_8		0x00000100
#घोषणा IDMA_IC_9		0x00000200
#घोषणा IDMA_IC_10		0x00000400
#घोषणा IDMA_IC_11		0x00000800
#घोषणा IDMA_IC_12		0x00001000
#घोषणा IDMA_IC_13		0x00002000
#घोषणा IDMA_SDC_BG		0x00004000
#घोषणा IDMA_SDC_FG		0x00008000
#घोषणा IDMA_SDC_MASK		0x00010000
#घोषणा IDMA_SDC_PARTIAL	0x00020000
#घोषणा IDMA_ADC_SYS1_WR	0x00040000
#घोषणा IDMA_ADC_SYS2_WR	0x00080000
#घोषणा IDMA_ADC_SYS1_CMD	0x00100000
#घोषणा IDMA_ADC_SYS2_CMD	0x00200000
#घोषणा IDMA_ADC_SYS1_RD	0x00400000
#घोषणा IDMA_ADC_SYS2_RD	0x00800000
#घोषणा IDMA_PF_QP		0x01000000
#घोषणा IDMA_PF_BSP		0x02000000
#घोषणा IDMA_PF_Y_IN		0x04000000
#घोषणा IDMA_PF_U_IN		0x08000000
#घोषणा IDMA_PF_V_IN		0x10000000
#घोषणा IDMA_PF_Y_OUT		0x20000000
#घोषणा IDMA_PF_U_OUT		0x40000000
#घोषणा IDMA_PF_V_OUT		0x80000000

#घोषणा TSTAT_PF_H264_PAUSE	0x00000001
#घोषणा TSTAT_CSI2MEM_MASK	0x0000000C
#घोषणा TSTAT_CSI2MEM_OFFSET	2
#घोषणा TSTAT_VF_MASK		0x00000600
#घोषणा TSTAT_VF_OFFSET		9
#घोषणा TSTAT_VF_ROT_MASK	0x000C0000
#घोषणा TSTAT_VF_ROT_OFFSET	18
#घोषणा TSTAT_ENC_MASK		0x00000180
#घोषणा TSTAT_ENC_OFFSET	7
#घोषणा TSTAT_ENC_ROT_MASK	0x00030000
#घोषणा TSTAT_ENC_ROT_OFFSET	16
#घोषणा TSTAT_PP_MASK		0x00001800
#घोषणा TSTAT_PP_OFFSET		11
#घोषणा TSTAT_PP_ROT_MASK	0x00300000
#घोषणा TSTAT_PP_ROT_OFFSET	20
#घोषणा TSTAT_PF_MASK		0x00C00000
#घोषणा TSTAT_PF_OFFSET		22
#घोषणा TSTAT_ADCSYS1_MASK	0x03000000
#घोषणा TSTAT_ADCSYS1_OFFSET	24
#घोषणा TSTAT_ADCSYS2_MASK	0x0C000000
#घोषणा TSTAT_ADCSYS2_OFFSET	26

#घोषणा TASK_STAT_IDLE		0
#घोषणा TASK_STAT_ACTIVE	1
#घोषणा TASK_STAT_WAIT4READY	2

काष्ठा idmac अणु
	काष्ठा dma_device	dma;
पूर्ण;

काष्ठा ipu अणु
	व्योम __iomem		*reg_ipu;
	व्योम __iomem		*reg_ic;
	अचिन्हित पूर्णांक		irq_fn;		/* IPU Function IRQ to the CPU */
	अचिन्हित पूर्णांक		irq_err;	/* IPU Error IRQ to the CPU */
	अचिन्हित पूर्णांक		irq_base;	/* Beginning of the IPU IRQ range */
	अचिन्हित दीर्घ		channel_init_mask;
	spinlock_t		lock;
	काष्ठा clk		*ipu_clk;
	काष्ठा device		*dev;
	काष्ठा idmac		idmac;
	काष्ठा idmac_channel	channel[IPU_CHANNELS_NUM];
	काष्ठा tasklet_काष्ठा	tasklet;
पूर्ण;

#घोषणा to_idmac(d) container_of(d, काष्ठा idmac, dma)

बाह्य पूर्णांक ipu_irq_attach_irq(काष्ठा ipu *ipu, काष्ठा platक्रमm_device *dev);
बाह्य व्योम ipu_irq_detach_irq(काष्ठा ipu *ipu, काष्ठा platक्रमm_device *dev);

बाह्य bool ipu_irq_status(uपूर्णांक32_t irq);
बाह्य पूर्णांक ipu_irq_map(अचिन्हित पूर्णांक source);
बाह्य पूर्णांक ipu_irq_unmap(अचिन्हित पूर्णांक source);

#पूर्ण_अगर
