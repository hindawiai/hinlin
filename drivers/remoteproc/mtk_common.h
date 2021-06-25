<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 */

#अगर_अघोषित __RPROC_MTK_COMMON_H
#घोषणा __RPROC_MTK_COMMON_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/remoteproc/mtk_scp.h>

#घोषणा MT8183_SW_RSTN			0x0
#घोषणा MT8183_SW_RSTN_BIT		BIT(0)
#घोषणा MT8183_SCP_TO_HOST		0x1C
#घोषणा MT8183_SCP_IPC_INT_BIT		BIT(0)
#घोषणा MT8183_SCP_WDT_INT_BIT		BIT(8)
#घोषणा MT8183_HOST_TO_SCP		0x28
#घोषणा MT8183_HOST_IPC_INT_BIT		BIT(0)
#घोषणा MT8183_WDT_CFG			0x84
#घोषणा MT8183_SCP_CLK_SW_SEL		0x4000
#घोषणा MT8183_SCP_CLK_DIV_SEL		0x4024
#घोषणा MT8183_SCP_SRAM_PDN		0x402C
#घोषणा MT8183_SCP_L1_SRAM_PD		0x4080
#घोषणा MT8183_SCP_TCM_TAIL_SRAM_PD	0x4094

#घोषणा MT8183_SCP_CACHE_SEL(x)		(0x14000 + (x) * 0x3000)
#घोषणा MT8183_SCP_CACHE_CON		MT8183_SCP_CACHE_SEL(0)
#घोषणा MT8183_SCP_DCACHE_CON		MT8183_SCP_CACHE_SEL(1)
#घोषणा MT8183_SCP_CACHESIZE_8KB	BIT(8)
#घोषणा MT8183_SCP_CACHE_CON_WAYEN	BIT(10)

#घोषणा MT8192_L2TCM_SRAM_PD_0		0x10C0
#घोषणा MT8192_L2TCM_SRAM_PD_1		0x10C4
#घोषणा MT8192_L2TCM_SRAM_PD_2		0x10C8
#घोषणा MT8192_L1TCM_SRAM_PDN		0x102C
#घोषणा MT8192_CPU0_SRAM_PD		0x1080

#घोषणा MT8192_SCP2APMCU_IPC_SET	0x4080
#घोषणा MT8192_SCP2APMCU_IPC_CLR	0x4084
#घोषणा MT8192_SCP_IPC_INT_BIT		BIT(0)
#घोषणा MT8192_SCP2SPM_IPC_CLR		0x4094
#घोषणा MT8192_GIPC_IN_SET		0x4098
#घोषणा MT8192_HOST_IPC_INT_BIT		BIT(0)

#घोषणा MT8192_CORE0_SW_RSTN_CLR	0x10000
#घोषणा MT8192_CORE0_SW_RSTN_SET	0x10004
#घोषणा MT8192_CORE0_MEM_ATT_PREDEF	0x10008
#घोषणा MT8192_CORE0_WDT_IRQ		0x10030
#घोषणा MT8192_CORE0_WDT_CFG		0x10034

#घोषणा SCP_FW_VER_LEN			32
#घोषणा SCP_SHARE_BUFFER_SIZE		288

काष्ठा scp_run अणु
	u32 संकेतed;
	s8 fw_ver[SCP_FW_VER_LEN];
	u32 dec_capability;
	u32 enc_capability;
	रुको_queue_head_t wq;
पूर्ण;

काष्ठा scp_ipi_desc अणु
	/* For protecting handler. */
	काष्ठा mutex lock;
	scp_ipi_handler_t handler;
	व्योम *priv;
पूर्ण;

काष्ठा mtk_scp;

काष्ठा mtk_scp_of_data अणु
	पूर्णांक (*scp_beक्रमe_load)(काष्ठा mtk_scp *scp);
	व्योम (*scp_irq_handler)(काष्ठा mtk_scp *scp);
	व्योम (*scp_reset_निश्चित)(काष्ठा mtk_scp *scp);
	व्योम (*scp_reset_deनिश्चित)(काष्ठा mtk_scp *scp);
	व्योम (*scp_stop)(काष्ठा mtk_scp *scp);
	व्योम *(*scp_da_to_va)(काष्ठा mtk_scp *scp, u64 da, माप_प्रकार len);

	u32 host_to_scp_reg;
	u32 host_to_scp_पूर्णांक_bit;

	माप_प्रकार ipi_buf_offset;
पूर्ण;

काष्ठा mtk_scp अणु
	काष्ठा device *dev;
	काष्ठा rproc *rproc;
	काष्ठा clk *clk;
	व्योम __iomem *reg_base;
	व्योम __iomem *sram_base;
	माप_प्रकार sram_size;
	phys_addr_t sram_phys;
	व्योम __iomem *l1tcm_base;
	माप_प्रकार l1tcm_size;
	phys_addr_t l1tcm_phys;

	स्थिर काष्ठा mtk_scp_of_data *data;

	काष्ठा mtk_share_obj __iomem *recv_buf;
	काष्ठा mtk_share_obj __iomem *send_buf;
	काष्ठा scp_run run;
	/* To prevent multiple ipi_send run concurrently. */
	काष्ठा mutex send_lock;
	काष्ठा scp_ipi_desc ipi_desc[SCP_IPI_MAX];
	bool ipi_id_ack[SCP_IPI_MAX];
	रुको_queue_head_t ack_wq;

	व्योम *cpu_addr;
	dma_addr_t dma_addr;
	माप_प्रकार dram_size;

	काष्ठा rproc_subdev *rpmsg_subdev;
पूर्ण;

/**
 * काष्ठा mtk_share_obj - SRAM buffer shared with AP and SCP
 *
 * @id:		IPI id
 * @len:	share buffer length
 * @share_buf:	share buffer data
 */
काष्ठा mtk_share_obj अणु
	u32 id;
	u32 len;
	u8 share_buf[SCP_SHARE_BUFFER_SIZE];
पूर्ण;

व्योम scp_स_नकल_aligned(व्योम __iomem *dst, स्थिर व्योम *src, अचिन्हित पूर्णांक len);
व्योम scp_ipi_lock(काष्ठा mtk_scp *scp, u32 id);
व्योम scp_ipi_unlock(काष्ठा mtk_scp *scp, u32 id);

#पूर्ण_अगर
