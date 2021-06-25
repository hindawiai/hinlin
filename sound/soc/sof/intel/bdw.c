<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//

/*
 * Hardware पूर्णांकerface क्रम audio DSP on Broadwell
 */

#समावेश <linux/module.h>
#समावेश <sound/sof.h>
#समावेश <sound/sof/xtensa.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश <sound/पूर्णांकel-dsp-config.h>
#समावेश "../ops.h"
#समावेश "shim.h"
#समावेश "../sof-acpi-dev.h"
#समावेश "../sof-audio.h"

/* BARs */
#घोषणा BDW_DSP_BAR 0
#घोषणा BDW_PCI_BAR 1

/*
 * Debug
 */

/* DSP memories क्रम BDW */
#घोषणा IRAM_OFFSET     0xA0000
#घोषणा BDW_IRAM_SIZE       (10 * 32 * 1024)
#घोषणा DRAM_OFFSET     0x00000
#घोषणा BDW_DRAM_SIZE       (20 * 32 * 1024)
#घोषणा SHIM_OFFSET     0xFB000
#घोषणा SHIM_SIZE       0x100
#घोषणा MBOX_OFFSET     0x9E000
#घोषणा MBOX_SIZE       0x1000
#घोषणा MBOX_DUMP_SIZE 0x30
#घोषणा EXCEPT_OFFSET	0x800
#घोषणा EXCEPT_MAX_HDR_SIZE	0x400

/* DSP peripherals */
#घोषणा DMAC0_OFFSET    0xFE000
#घोषणा DMAC1_OFFSET    0xFF000
#घोषणा DMAC_SIZE       0x420
#घोषणा SSP0_OFFSET     0xFC000
#घोषणा SSP1_OFFSET     0xFD000
#घोषणा SSP_SIZE	0x100

#घोषणा BDW_STACK_DUMP_SIZE	32

#घोषणा BDW_PANIC_OFFSET(x)	((x) & 0xFFFF)

अटल स्थिर काष्ठा snd_sof_debugfs_map bdw_debugfs[] = अणु
	अणु"dmac0", BDW_DSP_BAR, DMAC0_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"dmac1", BDW_DSP_BAR, DMAC1_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp0", BDW_DSP_BAR, SSP0_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp1", BDW_DSP_BAR, SSP1_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"iram", BDW_DSP_BAR, IRAM_OFFSET, BDW_IRAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONLYपूर्ण,
	अणु"dram", BDW_DSP_BAR, DRAM_OFFSET, BDW_DRAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONLYपूर्ण,
	अणु"shim", BDW_DSP_BAR, SHIM_OFFSET, SHIM_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
पूर्ण;

अटल व्योम bdw_host_करोne(काष्ठा snd_sof_dev *sdev);
अटल व्योम bdw_dsp_करोne(काष्ठा snd_sof_dev *sdev);
अटल व्योम bdw_get_reply(काष्ठा snd_sof_dev *sdev);

/*
 * DSP Control.
 */

अटल पूर्णांक bdw_run(काष्ठा snd_sof_dev *sdev)
अणु
	/* set opportunistic mode on engine 0,1 क्रम all channels */
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAR, SHIM_HMDC,
				SHIM_HMDC_HDDA_E0_ALLCH |
				SHIM_HMDC_HDDA_E1_ALLCH, 0);

	/* set DSP to RUN */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_CSR,
					 SHIM_CSR_STALL, 0x0);

	/* वापस init core mask */
	वापस 1;
पूर्ण

अटल पूर्णांक bdw_reset(काष्ठा snd_sof_dev *sdev)
अणु
	/* put DSP पूर्णांकo reset and stall */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_CSR,
					 SHIM_CSR_RST | SHIM_CSR_STALL,
					 SHIM_CSR_RST | SHIM_CSR_STALL);

	/* keep in reset क्रम 10ms */
	mdelay(10);

	/* take DSP out of reset and keep stalled क्रम FW loading */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_CSR,
					 SHIM_CSR_RST | SHIM_CSR_STALL,
					 SHIM_CSR_STALL);

	वापस 0;
पूर्ण

अटल पूर्णांक bdw_set_dsp_D0(काष्ठा snd_sof_dev *sdev)
अणु
	पूर्णांक tries = 10;
	u32 reg;

	/* Disable core घड़ी gating (VDRTCTL2.DCLCGE = 0) */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_VDRTCTL2,
					 PCI_VDRTCL2_DCLCGE |
					 PCI_VDRTCL2_DTCGE, 0);

	/* Disable D3PG (VDRTCTL0.D3PGD = 1) */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_VDRTCTL0,
					 PCI_VDRTCL0_D3PGD, PCI_VDRTCL0_D3PGD);

	/* Set D0 state */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_PMCS,
					 PCI_PMCS_PS_MASK, 0);

	/* check that ADSP shim is enabled */
	जबतक (tries--) अणु
		reg = पढ़ोl(sdev->bar[BDW_PCI_BAR] + PCI_PMCS)
			& PCI_PMCS_PS_MASK;
		अगर (reg == 0)
			जाओ finish;

		msleep(20);
	पूर्ण

	वापस -ENODEV;

finish:
	/*
	 * select SSP1 19.2MHz base घड़ी, SSP घड़ी 0,
	 * turn off Low Power Clock
	 */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_CSR,
					 SHIM_CSR_S1IOCS | SHIM_CSR_SBCS1 |
					 SHIM_CSR_LPCS, 0x0);

	/* stall DSP core, set clk to 192/96Mhz */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR,
					 SHIM_CSR, SHIM_CSR_STALL |
					 SHIM_CSR_DCS_MASK,
					 SHIM_CSR_STALL |
					 SHIM_CSR_DCS(4));

	/* Set 24MHz MCLK, prevent local घड़ी gating, enable SSP0 घड़ी */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_CLKCTL,
					 SHIM_CLKCTL_MASK |
					 SHIM_CLKCTL_DCPLCG |
					 SHIM_CLKCTL_SCOE0,
					 SHIM_CLKCTL_MASK |
					 SHIM_CLKCTL_DCPLCG |
					 SHIM_CLKCTL_SCOE0);

	/* Stall and reset core, set CSR */
	bdw_reset(sdev);

	/* Enable core घड़ी gating (VDRTCTL2.DCLCGE = 1), delay 50 us */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_VDRTCTL2,
					 PCI_VDRTCL2_DCLCGE |
					 PCI_VDRTCL2_DTCGE,
					 PCI_VDRTCL2_DCLCGE |
					 PCI_VDRTCL2_DTCGE);

	usleep_range(50, 55);

	/* चयन on audio PLL */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_VDRTCTL2,
					 PCI_VDRTCL2_APLLSE_MASK, 0);

	/*
	 * set शेष घातer gating control, enable घातer gating control क्रम
	 * all blocks. that is, can't be accessed, please enable each block
	 * beक्रमe accessing.
	 */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_PCI_BAR, PCI_VDRTCTL0,
					 0xfffffffC, 0x0);

	/* disable DMA finish function क्रम SSP0 & SSP1 */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR,  SHIM_CSR2,
					 SHIM_CSR2_SDFD_SSP1,
					 SHIM_CSR2_SDFD_SSP1);

	/* set on-demond mode on engine 0,1 क्रम all channels */
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAR, SHIM_HMDC,
				SHIM_HMDC_HDDA_E0_ALLCH |
				SHIM_HMDC_HDDA_E1_ALLCH,
				SHIM_HMDC_HDDA_E0_ALLCH |
				SHIM_HMDC_HDDA_E1_ALLCH);

	/* Enable Interrupt from both sides */
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAR, SHIM_IMRX,
				(SHIM_IMRX_BUSY | SHIM_IMRX_DONE), 0x0);
	snd_sof_dsp_update_bits(sdev, BDW_DSP_BAR, SHIM_IMRD,
				(SHIM_IMRD_DONE | SHIM_IMRD_BUSY |
				SHIM_IMRD_SSP0 | SHIM_IMRD_DMAC), 0x0);

	/* clear IPC रेजिस्टरs */
	snd_sof_dsp_ग_लिखो(sdev, BDW_DSP_BAR, SHIM_IPCX, 0x0);
	snd_sof_dsp_ग_लिखो(sdev, BDW_DSP_BAR, SHIM_IPCD, 0x0);
	snd_sof_dsp_ग_लिखो(sdev, BDW_DSP_BAR, 0x80, 0x6);
	snd_sof_dsp_ग_लिखो(sdev, BDW_DSP_BAR, 0xe0, 0x300a);

	वापस 0;
पूर्ण

अटल व्योम bdw_get_रेजिस्टरs(काष्ठा snd_sof_dev *sdev,
			      काष्ठा sof_ipc_dsp_oops_xtensa *xoops,
			      काष्ठा sof_ipc_panic_info *panic_info,
			      u32 *stack, माप_प्रकार stack_words)
अणु
	u32 offset = sdev->dsp_oops_offset;

	/* first पढ़ो रेजिस्टरs */
	sof_mailbox_पढ़ो(sdev, offset, xoops, माप(*xoops));

	/* note: variable AR रेजिस्टर array is not पढ़ो */

	/* then get panic info */
	अगर (xoops->arch_hdr.totalsize > EXCEPT_MAX_HDR_SIZE) अणु
		dev_err(sdev->dev, "invalid header size 0x%x. FW oops is bogus\n",
			xoops->arch_hdr.totalsize);
		वापस;
	पूर्ण
	offset += xoops->arch_hdr.totalsize;
	sof_mailbox_पढ़ो(sdev, offset, panic_info, माप(*panic_info));

	/* then get the stack */
	offset += माप(*panic_info);
	sof_mailbox_पढ़ो(sdev, offset, stack, stack_words * माप(u32));
पूर्ण

अटल व्योम bdw_dump(काष्ठा snd_sof_dev *sdev, u32 flags)
अणु
	काष्ठा sof_ipc_dsp_oops_xtensa xoops;
	काष्ठा sof_ipc_panic_info panic_info;
	u32 stack[BDW_STACK_DUMP_SIZE];
	u32 status, panic, imrx, imrd;

	/* now try generic SOF status messages */
	status = snd_sof_dsp_पढ़ो(sdev, BDW_DSP_BAR, SHIM_IPCD);
	panic = snd_sof_dsp_पढ़ो(sdev, BDW_DSP_BAR, SHIM_IPCX);
	bdw_get_रेजिस्टरs(sdev, &xoops, &panic_info, stack,
			  BDW_STACK_DUMP_SIZE);
	snd_sof_get_status(sdev, status, panic, &xoops, &panic_info, stack,
			   BDW_STACK_DUMP_SIZE);

	/* provide some context क्रम firmware debug */
	imrx = snd_sof_dsp_पढ़ो(sdev, BDW_DSP_BAR, SHIM_IMRX);
	imrd = snd_sof_dsp_पढ़ो(sdev, BDW_DSP_BAR, SHIM_IMRD);
	dev_err(sdev->dev,
		"error: ipc host -> DSP: pending %s complete %s raw 0x%8.8x\n",
		(panic & SHIM_IPCX_BUSY) ? "yes" : "no",
		(panic & SHIM_IPCX_DONE) ? "yes" : "no", panic);
	dev_err(sdev->dev,
		"error: mask host: pending %s complete %s raw 0x%8.8x\n",
		(imrx & SHIM_IMRX_BUSY) ? "yes" : "no",
		(imrx & SHIM_IMRX_DONE) ? "yes" : "no", imrx);
	dev_err(sdev->dev,
		"error: ipc DSP -> host: pending %s complete %s raw 0x%8.8x\n",
		(status & SHIM_IPCD_BUSY) ? "yes" : "no",
		(status & SHIM_IPCD_DONE) ? "yes" : "no", status);
	dev_err(sdev->dev,
		"error: mask DSP: pending %s complete %s raw 0x%8.8x\n",
		(imrd & SHIM_IMRD_BUSY) ? "yes" : "no",
		(imrd & SHIM_IMRD_DONE) ? "yes" : "no", imrd);
पूर्ण

/*
 * IPC Doorbell IRQ handler and thपढ़ो.
 */

अटल irqवापस_t bdw_irq_handler(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा snd_sof_dev *sdev = context;
	u32 isr;
	पूर्णांक ret = IRQ_NONE;

	/* Interrupt arrived, check src */
	isr = snd_sof_dsp_पढ़ो(sdev, BDW_DSP_BAR, SHIM_ISRX);
	अगर (isr & (SHIM_ISRX_DONE | SHIM_ISRX_BUSY))
		ret = IRQ_WAKE_THREAD;

	वापस ret;
पूर्ण

अटल irqवापस_t bdw_irq_thपढ़ो(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा snd_sof_dev *sdev = context;
	u32 ipcx, ipcd, imrx;

	imrx = snd_sof_dsp_पढ़ो64(sdev, BDW_DSP_BAR, SHIM_IMRX);
	ipcx = snd_sof_dsp_पढ़ो(sdev, BDW_DSP_BAR, SHIM_IPCX);

	/* reply message from DSP */
	अगर (ipcx & SHIM_IPCX_DONE &&
	    !(imrx & SHIM_IMRX_DONE)) अणु
		/* Mask Done पूर्णांकerrupt beक्रमe वापस */
		snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR,
						 SHIM_IMRX, SHIM_IMRX_DONE,
						 SHIM_IMRX_DONE);

		spin_lock_irq(&sdev->ipc_lock);

		/*
		 * handle immediate reply from DSP core. If the msg is
		 * found, set करोne bit in cmd_करोne which is called at the
		 * end of message processing function, अन्यथा set it here
		 * because the करोne bit can't be set in cmd_करोne function
		 * which is triggered by msg
		 */
		bdw_get_reply(sdev);
		snd_sof_ipc_reply(sdev, ipcx);

		bdw_dsp_करोne(sdev);

		spin_unlock_irq(&sdev->ipc_lock);
	पूर्ण

	ipcd = snd_sof_dsp_पढ़ो(sdev, BDW_DSP_BAR, SHIM_IPCD);

	/* new message from DSP */
	अगर (ipcd & SHIM_IPCD_BUSY &&
	    !(imrx & SHIM_IMRX_BUSY)) अणु
		/* Mask Busy पूर्णांकerrupt beक्रमe वापस */
		snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR,
						 SHIM_IMRX, SHIM_IMRX_BUSY,
						 SHIM_IMRX_BUSY);

		/* Handle messages from DSP Core */
		अगर ((ipcd & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) अणु
			snd_sof_dsp_panic(sdev, BDW_PANIC_OFFSET(ipcx) +
					  MBOX_OFFSET);
		पूर्ण अन्यथा अणु
			snd_sof_ipc_msgs_rx(sdev);
		पूर्ण

		bdw_host_करोne(sdev);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * IPC Mailbox IO
 */

अटल पूर्णांक bdw_send_msg(काष्ठा snd_sof_dev *sdev, काष्ठा snd_sof_ipc_msg *msg)
अणु
	/* send the message */
	sof_mailbox_ग_लिखो(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	snd_sof_dsp_ग_लिखो(sdev, BDW_DSP_BAR, SHIM_IPCX, SHIM_IPCX_BUSY);

	वापस 0;
पूर्ण

अटल व्योम bdw_get_reply(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_ipc_msg *msg = sdev->msg;
	काष्ठा sof_ipc_reply reply;
	पूर्णांक ret = 0;

	/*
	 * Someबार, there is unexpected reply ipc arriving. The reply
	 * ipc beदीर्घs to none of the ipcs sent from driver.
	 * In this हाल, the driver must ignore the ipc.
	 */
	अगर (!msg) अणु
		dev_warn(sdev->dev, "unexpected ipc interrupt raised!\n");
		वापस;
	पूर्ण

	/* get reply */
	sof_mailbox_पढ़ो(sdev, sdev->host_box.offset, &reply, माप(reply));

	अगर (reply.error < 0) अणु
		स_नकल(msg->reply_data, &reply, माप(reply));
		ret = reply.error;
	पूर्ण अन्यथा अणु
		/* reply correct size ? */
		अगर (reply.hdr.size != msg->reply_size) अणु
			dev_err(sdev->dev, "error: reply expected %zu got %u bytes\n",
				msg->reply_size, reply.hdr.size);
			ret = -EINVAL;
		पूर्ण

		/* पढ़ो the message */
		अगर (msg->reply_size > 0)
			sof_mailbox_पढ़ो(sdev, sdev->host_box.offset,
					 msg->reply_data, msg->reply_size);
	पूर्ण

	msg->reply_error = ret;
पूर्ण

अटल पूर्णांक bdw_get_mailbox_offset(काष्ठा snd_sof_dev *sdev)
अणु
	वापस MBOX_OFFSET;
पूर्ण

अटल पूर्णांक bdw_get_winकरोw_offset(काष्ठा snd_sof_dev *sdev, u32 id)
अणु
	वापस MBOX_OFFSET;
पूर्ण

अटल व्योम bdw_host_करोne(काष्ठा snd_sof_dev *sdev)
अणु
	/* clear BUSY bit and set DONE bit - accept new messages */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_IPCD,
					 SHIM_IPCD_BUSY | SHIM_IPCD_DONE,
					 SHIM_IPCD_DONE);

	/* unmask busy पूर्णांकerrupt */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_IMRX,
					 SHIM_IMRX_BUSY, 0);
पूर्ण

अटल व्योम bdw_dsp_करोne(काष्ठा snd_sof_dev *sdev)
अणु
	/* clear DONE bit - tell DSP we have completed */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_IPCX,
					 SHIM_IPCX_DONE, 0);

	/* unmask Done पूर्णांकerrupt */
	snd_sof_dsp_update_bits_unlocked(sdev, BDW_DSP_BAR, SHIM_IMRX,
					 SHIM_IMRX_DONE, 0);
पूर्ण

/*
 * Probe and हटाओ.
 */
अटल पूर्णांक bdw_probe(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *pdata = sdev->pdata;
	स्थिर काष्ठा sof_dev_desc *desc = pdata->desc;
	काष्ठा platक्रमm_device *pdev =
		container_of(sdev->dev, काष्ठा platक्रमm_device, dev);
	काष्ठा resource *mmio;
	u32 base, size;
	पूर्णांक ret;

	/* LPE base */
	mmio = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				     desc->resindex_lpe_base);
	अगर (mmio) अणु
		base = mmio->start;
		size = resource_size(mmio);
	पूर्ण अन्यथा अणु
		dev_err(sdev->dev, "error: failed to get LPE base at idx %d\n",
			desc->resindex_lpe_base);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(sdev->dev, "LPE PHY base at 0x%x size 0x%x", base, size);
	sdev->bar[BDW_DSP_BAR] = devm_ioremap(sdev->dev, base, size);
	अगर (!sdev->bar[BDW_DSP_BAR]) अणु
		dev_err(sdev->dev,
			"error: failed to ioremap LPE base 0x%x size 0x%x\n",
			base, size);
		वापस -ENODEV;
	पूर्ण
	dev_dbg(sdev->dev, "LPE VADDR %p\n", sdev->bar[BDW_DSP_BAR]);

	/* TODO: add offsets */
	sdev->mmio_bar = BDW_DSP_BAR;
	sdev->mailbox_bar = BDW_DSP_BAR;
	sdev->dsp_oops_offset = MBOX_OFFSET;

	/* PCI base */
	mmio = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				     desc->resindex_pcicfg_base);
	अगर (mmio) अणु
		base = mmio->start;
		size = resource_size(mmio);
	पूर्ण अन्यथा अणु
		dev_err(sdev->dev, "error: failed to get PCI base at idx %d\n",
			desc->resindex_pcicfg_base);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(sdev->dev, "PCI base at 0x%x size 0x%x", base, size);
	sdev->bar[BDW_PCI_BAR] = devm_ioremap(sdev->dev, base, size);
	अगर (!sdev->bar[BDW_PCI_BAR]) अणु
		dev_err(sdev->dev,
			"error: failed to ioremap PCI base 0x%x size 0x%x\n",
			base, size);
		वापस -ENODEV;
	पूर्ण
	dev_dbg(sdev->dev, "PCI VADDR %p\n", sdev->bar[BDW_PCI_BAR]);

	/* रेजिस्टर our IRQ */
	sdev->ipc_irq = platक्रमm_get_irq(pdev, desc->irqindex_host_ipc);
	अगर (sdev->ipc_irq < 0)
		वापस sdev->ipc_irq;

	dev_dbg(sdev->dev, "using IRQ %d\n", sdev->ipc_irq);
	ret = devm_request_thपढ़ोed_irq(sdev->dev, sdev->ipc_irq,
					bdw_irq_handler, bdw_irq_thपढ़ो,
					IRQF_SHARED, "AudioDSP", sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to register IRQ %d\n",
			sdev->ipc_irq);
		वापस ret;
	पूर्ण

	/* enable the DSP SHIM */
	ret = bdw_set_dsp_D0(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to set DSP D0\n");
		वापस ret;
	पूर्ण

	/* DSP DMA can only access low 31 bits of host memory */
	ret = dma_coerce_mask_and_coherent(sdev->dev, DMA_BIT_MASK(31));
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to set DMA mask %d\n", ret);
		वापस ret;
	पूर्ण

	/* set शेष mailbox */
	snd_sof_dsp_mailbox_init(sdev, MBOX_OFFSET, MBOX_SIZE, 0, 0);

	वापस ret;
पूर्ण

अटल व्योम bdw_machine_select(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *sof_pdata = sdev->pdata;
	स्थिर काष्ठा sof_dev_desc *desc = sof_pdata->desc;
	काष्ठा snd_soc_acpi_mach *mach;

	mach = snd_soc_acpi_find_machine(desc->machines);
	अगर (!mach) अणु
		dev_warn(sdev->dev, "warning: No matching ASoC machine driver found\n");
		वापस;
	पूर्ण

	sof_pdata->tplg_filename = mach->sof_tplg_filename;
	mach->mach_params.acpi_ipc_irq_index = desc->irqindex_host_ipc;
	sof_pdata->machine = mach;
पूर्ण

अटल व्योम bdw_set_mach_params(स्थिर काष्ठा snd_soc_acpi_mach *mach,
				काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *pdata = sdev->pdata;
	स्थिर काष्ठा sof_dev_desc *desc = pdata->desc;
	काष्ठा snd_soc_acpi_mach_params *mach_params;

	mach_params = (काष्ठा snd_soc_acpi_mach_params *)&mach->mach_params;
	mach_params->platक्रमm = dev_name(sdev->dev);
	mach_params->num_dai_drivers = desc->ops->num_drv;
	mach_params->dai_drivers = desc->ops->drv;
पूर्ण

/* Broadwell DAIs */
अटल काष्ठा snd_soc_dai_driver bdw_dai[] = अणु
अणु
	.name = "ssp0-port",
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "ssp1-port",
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
पूर्ण;

/* broadwell ops */
अटल स्थिर काष्ठा snd_sof_dsp_ops sof_bdw_ops = अणु
	/*Device init */
	.probe          = bdw_probe,

	/* DSP Core Control */
	.run            = bdw_run,
	.reset          = bdw_reset,

	/* Register IO */
	.ग_लिखो		= sof_io_ग_लिखो,
	.पढ़ो		= sof_io_पढ़ो,
	.ग_लिखो64	= sof_io_ग_लिखो64,
	.पढ़ो64		= sof_io_पढ़ो64,

	/* Block IO */
	.block_पढ़ो	= sof_block_पढ़ो,
	.block_ग_लिखो	= sof_block_ग_लिखो,

	/* ipc */
	.send_msg	= bdw_send_msg,
	.fw_पढ़ोy	= sof_fw_पढ़ोy,
	.get_mailbox_offset = bdw_get_mailbox_offset,
	.get_winकरोw_offset = bdw_get_winकरोw_offset,

	.ipc_msg_data	= पूर्णांकel_ipc_msg_data,
	.ipc_pcm_params	= पूर्णांकel_ipc_pcm_params,

	/* machine driver */
	.machine_select = bdw_machine_select,
	.machine_रेजिस्टर = sof_machine_रेजिस्टर,
	.machine_unरेजिस्टर = sof_machine_unरेजिस्टर,
	.set_mach_params = bdw_set_mach_params,

	/* debug */
	.debug_map  = bdw_debugfs,
	.debug_map_count    = ARRAY_SIZE(bdw_debugfs),
	.dbg_dump   = bdw_dump,

	/* stream callbacks */
	.pcm_खोलो	= पूर्णांकel_pcm_खोलो,
	.pcm_बंद	= पूर्णांकel_pcm_बंद,

	/* Module loading */
	.load_module    = snd_sof_parse_module_स_नकल,

	/*Firmware loading */
	.load_firmware	= snd_sof_load_firmware_स_नकल,

	/* DAI drivers */
	.drv = bdw_dai,
	.num_drv = ARRAY_SIZE(bdw_dai),

	/* ALSA HW info flags */
	.hw_info =	SNDRV_PCM_INFO_MMAP |
			SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_INTERLEAVED |
			SNDRV_PCM_INFO_PAUSE |
			SNDRV_PCM_INFO_BATCH,

	.arch_ops = &sof_xtensa_arch_ops,
पूर्ण;

अटल स्थिर काष्ठा sof_पूर्णांकel_dsp_desc bdw_chip_info = अणु
	.cores_num = 1,
	.host_managed_cores_mask = 1,
पूर्ण;

अटल स्थिर काष्ठा sof_dev_desc sof_acpi_broadwell_desc = अणु
	.machines = snd_soc_acpi_पूर्णांकel_broadwell_machines,
	.resindex_lpe_base = 0,
	.resindex_pcicfg_base = 1,
	.resindex_imr_base = -1,
	.irqindex_host_ipc = 0,
	.chip_info = &bdw_chip_info,
	.शेष_fw_path = "intel/sof",
	.शेष_tplg_path = "intel/sof-tplg",
	.शेष_fw_filename = "sof-bdw.ri",
	.nocodec_tplg_filename = "sof-bdw-nocodec.tplg",
	.ops = &sof_bdw_ops,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id sof_broadwell_match[] = अणु
	अणु "INT3438", (अचिन्हित दीर्घ)&sof_acpi_broadwell_desc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sof_broadwell_match);

अटल पूर्णांक sof_broadwell_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा acpi_device_id *id;
	स्थिर काष्ठा sof_dev_desc *desc;
	पूर्णांक ret;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस -ENODEV;

	ret = snd_पूर्णांकel_acpi_dsp_driver_probe(dev, id->id);
	अगर (ret != SND_INTEL_DSP_DRIVER_ANY && ret != SND_INTEL_DSP_DRIVER_SOF) अणु
		dev_dbg(dev, "SOF ACPI driver not selected, aborting probe\n");
		वापस -ENODEV;
	पूर्ण

	desc = device_get_match_data(dev);
	अगर (!desc)
		वापस -ENODEV;

	वापस sof_acpi_probe(pdev, device_get_match_data(dev));
पूर्ण

/* acpi_driver definition */
अटल काष्ठा platक्रमm_driver snd_sof_acpi_पूर्णांकel_bdw_driver = अणु
	.probe = sof_broadwell_probe,
	.हटाओ = sof_acpi_हटाओ,
	.driver = अणु
		.name = "sof-audio-acpi-intel-bdw",
		.pm = &sof_acpi_pm,
		.acpi_match_table = sof_broadwell_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(snd_sof_acpi_पूर्णांकel_bdw_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_IMPORT_NS(SND_SOC_SOF_INTEL_HIFI_EP_IPC);
MODULE_IMPORT_NS(SND_SOC_SOF_XTENSA);
MODULE_IMPORT_NS(SND_SOC_SOF_ACPI_DEV);
