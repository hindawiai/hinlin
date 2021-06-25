<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Cannonlake SST DSP Support
 *
 * Copyright (C) 2016-17, Intel Corporation.
 */

#अगर_अघोषित __CNL_SST_DSP_H__
#घोषणा __CNL_SST_DSP_H__

काष्ठा sst_dsp;
काष्ठा sst_dsp_device;
काष्ठा sst_generic_ipc;

/* Intel HD Audio General DSP Registers */
#घोषणा CNL_ADSP_GEN_BASE		0x0
#घोषणा CNL_ADSP_REG_ADSPCS		(CNL_ADSP_GEN_BASE + 0x04)
#घोषणा CNL_ADSP_REG_ADSPIC		(CNL_ADSP_GEN_BASE + 0x08)
#घोषणा CNL_ADSP_REG_ADSPIS		(CNL_ADSP_GEN_BASE + 0x0c)

/* Intel HD Audio Inter-Processor Communication Registers */
#घोषणा CNL_ADSP_IPC_BASE               0xc0
#घोषणा CNL_ADSP_REG_HIPCTDR            (CNL_ADSP_IPC_BASE + 0x00)
#घोषणा CNL_ADSP_REG_HIPCTDA            (CNL_ADSP_IPC_BASE + 0x04)
#घोषणा CNL_ADSP_REG_HIPCTDD            (CNL_ADSP_IPC_BASE + 0x08)
#घोषणा CNL_ADSP_REG_HIPCIDR            (CNL_ADSP_IPC_BASE + 0x10)
#घोषणा CNL_ADSP_REG_HIPCIDA            (CNL_ADSP_IPC_BASE + 0x14)
#घोषणा CNL_ADSP_REG_HIPCIDD            (CNL_ADSP_IPC_BASE + 0x18)
#घोषणा CNL_ADSP_REG_HIPCCTL            (CNL_ADSP_IPC_BASE + 0x28)

/* HIPCTDR */
#घोषणा CNL_ADSP_REG_HIPCTDR_BUSY	BIT(31)

/* HIPCTDA */
#घोषणा CNL_ADSP_REG_HIPCTDA_DONE	BIT(31)

/* HIPCIDR */
#घोषणा CNL_ADSP_REG_HIPCIDR_BUSY	BIT(31)

/* HIPCIDA */
#घोषणा CNL_ADSP_REG_HIPCIDA_DONE	BIT(31)

/* CNL HIPCCTL */
#घोषणा CNL_ADSP_REG_HIPCCTL_DONE	BIT(1)
#घोषणा CNL_ADSP_REG_HIPCCTL_BUSY	BIT(0)

/* CNL HIPCT */
#घोषणा CNL_ADSP_REG_HIPCT_BUSY		BIT(31)

/* Intel HD Audio SRAM Winकरोw 1 */
#घोषणा CNL_ADSP_SRAM1_BASE		0xa0000

#घोषणा CNL_ADSP_MMIO_LEN		0x10000

#घोषणा CNL_ADSP_W0_STAT_SZ		0x1000

#घोषणा CNL_ADSP_W0_UP_SZ		0x1000

#घोषणा CNL_ADSP_W1_SZ			0x1000

#घोषणा CNL_FW_STS_MASK			0xf

#घोषणा CNL_ADSPIC_IPC			0x1
#घोषणा CNL_ADSPIS_IPC			0x1

#घोषणा CNL_DSP_CORES		4
#घोषणा CNL_DSP_CORES_MASK	((1 << CNL_DSP_CORES) - 1)

/* core reset - निश्चितed high */
#घोषणा CNL_ADSPCS_CRST_SHIFT	0
#घोषणा CNL_ADSPCS_CRST(x)	(x << CNL_ADSPCS_CRST_SHIFT)

/* core run/stall - when set to 1 core is stalled */
#घोषणा CNL_ADSPCS_CSTALL_SHIFT	8
#घोषणा CNL_ADSPCS_CSTALL(x)	(x << CNL_ADSPCS_CSTALL_SHIFT)

/* set घातer active - when set to 1 turn core on */
#घोषणा CNL_ADSPCS_SPA_SHIFT	16
#घोषणा CNL_ADSPCS_SPA(x)	(x << CNL_ADSPCS_SPA_SHIFT)

/* current घातer active - घातer status of cores, set by hardware */
#घोषणा CNL_ADSPCS_CPA_SHIFT	24
#घोषणा CNL_ADSPCS_CPA(x)	(x << CNL_ADSPCS_CPA_SHIFT)

पूर्णांक cnl_dsp_enable_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask);
पूर्णांक cnl_dsp_disable_core(काष्ठा sst_dsp *ctx, अचिन्हित पूर्णांक core_mask);
irqवापस_t cnl_dsp_sst_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
व्योम cnl_dsp_मुक्त(काष्ठा sst_dsp *dsp);

व्योम cnl_ipc_पूर्णांक_enable(काष्ठा sst_dsp *ctx);
व्योम cnl_ipc_पूर्णांक_disable(काष्ठा sst_dsp *ctx);
व्योम cnl_ipc_op_पूर्णांक_enable(काष्ठा sst_dsp *ctx);
व्योम cnl_ipc_op_पूर्णांक_disable(काष्ठा sst_dsp *ctx);
bool cnl_ipc_पूर्णांक_status(काष्ठा sst_dsp *ctx);
व्योम cnl_ipc_मुक्त(काष्ठा sst_generic_ipc *ipc);

पूर्णांक cnl_sst_dsp_init(काष्ठा device *dev, व्योम __iomem *mmio_base, पूर्णांक irq,
		     स्थिर अक्षर *fw_name, काष्ठा skl_dsp_loader_ops dsp_ops,
		     काष्ठा skl_dev **dsp);
पूर्णांक cnl_sst_init_fw(काष्ठा device *dev, काष्ठा skl_dev *skl);
व्योम cnl_sst_dsp_cleanup(काष्ठा device *dev, काष्ठा skl_dev *skl);

#पूर्ण_अगर /*__CNL_SST_DSP_H__*/
