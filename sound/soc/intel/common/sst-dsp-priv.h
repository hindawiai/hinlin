<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel Smart Sound Technology
 *
 * Copyright (C) 2013, Intel Corporation. All rights reserved.
 */

#अगर_अघोषित __SOUND_SOC_SST_DSP_PRIV_H
#घोषणा __SOUND_SOC_SST_DSP_PRIV_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/firmware.h>

#समावेश "../skylake/skl-sst-dsp.h"

/*
 * DSP Operations exported by platक्रमm Audio DSP driver.
 */
काष्ठा sst_ops अणु
	/* Shim IO */
	व्योम (*ग_लिखो)(व्योम __iomem *addr, u32 offset, u32 value);
	u32 (*पढ़ो)(व्योम __iomem *addr, u32 offset);

	/* IRQ handlers */
	irqवापस_t (*irq_handler)(पूर्णांक irq, व्योम *context);

	/* SST init and मुक्त */
	पूर्णांक (*init)(काष्ठा sst_dsp *sst);
	व्योम (*मुक्त)(काष्ठा sst_dsp *sst);
पूर्ण;

/*
 * Audio DSP memory offsets and addresses.
 */
काष्ठा sst_addr अणु
	u32 sram0_base;
	u32 sram1_base;
	u32 w0_stat_sz;
	u32 w0_up_sz;
	व्योम __iomem *lpe;
	व्योम __iomem *shim;
पूर्ण;

/*
 * Audio DSP Mailbox configuration.
 */
काष्ठा sst_mailbox अणु
	व्योम __iomem *in_base;
	व्योम __iomem *out_base;
	माप_प्रकार in_size;
	माप_प्रकार out_size;
पूर्ण;

/*
 * Generic SST Shim Interface.
 */
काष्ठा sst_dsp अणु

	/* Shared क्रम all platक्रमms */

	/* runसमय */
	काष्ठा sst_dsp_device *sst_dev;
	spinlock_t spinlock;	/* IPC locking */
	काष्ठा mutex mutex;	/* DSP FW lock */
	काष्ठा device *dev;
	व्योम *thपढ़ो_context;
	पूर्णांक irq;
	u32 id;

	/* operations */
	काष्ठा sst_ops *ops;

	/* debug FS */
	काष्ठा dentry *debugfs_root;

	/* base addresses */
	काष्ठा sst_addr addr;

	/* mailbox */
	काष्ठा sst_mailbox mailbox;

	/* SST FW files loaded and their modules */
	काष्ठा list_head module_list;

	/* SKL data */

	स्थिर अक्षर *fw_name;

	/* To allocate CL dma buffers */
	काष्ठा skl_dsp_loader_ops dsp_ops;
	काष्ठा skl_dsp_fw_ops fw_ops;
	पूर्णांक sst_state;
	काष्ठा skl_cl_dev cl_dev;
	u32 पूर्णांकr_status;
	स्थिर काष्ठा firmware *fw;
	काष्ठा snd_dma_buffer dmab;
पूर्ण;

#पूर्ण_अगर
