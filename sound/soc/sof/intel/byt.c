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
 * Hardware पूर्णांकerface क्रम audio DSP on Baytrail, Braswell and Cherrytrail.
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
#समावेश "../../intel/common/soc-intel-quirks.h"

/* DSP memories */
#घोषणा IRAM_OFFSET		0x0C0000
#घोषणा IRAM_SIZE		(80 * 1024)
#घोषणा DRAM_OFFSET		0x100000
#घोषणा DRAM_SIZE		(160 * 1024)
#घोषणा SHIM_OFFSET		0x140000
#घोषणा SHIM_SIZE_BYT		0x100
#घोषणा SHIM_SIZE_CHT		0x118
#घोषणा MBOX_OFFSET		0x144000
#घोषणा MBOX_SIZE		0x1000
#घोषणा EXCEPT_OFFSET		0x800
#घोषणा EXCEPT_MAX_HDR_SIZE	0x400

/* DSP peripherals */
#घोषणा DMAC0_OFFSET		0x098000
#घोषणा DMAC1_OFFSET		0x09c000
#घोषणा DMAC2_OFFSET		0x094000
#घोषणा DMAC_SIZE		0x420
#घोषणा SSP0_OFFSET		0x0a0000
#घोषणा SSP1_OFFSET		0x0a1000
#घोषणा SSP2_OFFSET		0x0a2000
#घोषणा SSP3_OFFSET		0x0a4000
#घोषणा SSP4_OFFSET		0x0a5000
#घोषणा SSP5_OFFSET		0x0a6000
#घोषणा SSP_SIZE		0x100

#घोषणा BYT_STACK_DUMP_SIZE	32

#घोषणा BYT_PCI_BAR_SIZE	0x200000

#घोषणा BYT_PANIC_OFFSET(x)	(((x) & GENMASK_ULL(47, 32)) >> 32)

/*
 * Debug
 */

#घोषणा MBOX_DUMP_SIZE	0x30

/* BARs */
#घोषणा BYT_DSP_BAR		0
#घोषणा BYT_PCI_BAR		1
#घोषणा BYT_IMR_BAR		2

अटल स्थिर काष्ठा snd_sof_debugfs_map byt_debugfs[] = अणु
	अणु"dmac0", BYT_DSP_BAR, DMAC0_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"dmac1", BYT_DSP_BAR,  DMAC1_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp0",  BYT_DSP_BAR, SSP0_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp1", BYT_DSP_BAR, SSP1_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp2", BYT_DSP_BAR, SSP2_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"iram", BYT_DSP_BAR, IRAM_OFFSET, IRAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONLYपूर्ण,
	अणु"dram", BYT_DSP_BAR, DRAM_OFFSET, DRAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONLYपूर्ण,
	अणु"shim", BYT_DSP_BAR, SHIM_OFFSET, SHIM_SIZE_BYT,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
पूर्ण;

अटल व्योम byt_host_करोne(काष्ठा snd_sof_dev *sdev);
अटल व्योम byt_dsp_करोne(काष्ठा snd_sof_dev *sdev);
अटल व्योम byt_get_reply(काष्ठा snd_sof_dev *sdev);

/*
 * Debug
 */

अटल व्योम byt_get_रेजिस्टरs(काष्ठा snd_sof_dev *sdev,
			      काष्ठा sof_ipc_dsp_oops_xtensa *xoops,
			      काष्ठा sof_ipc_panic_info *panic_info,
			      u32 *stack, माप_प्रकार stack_words)
अणु
	u32 offset = sdev->dsp_oops_offset;

	/* first पढ़ो regsisters */
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

अटल व्योम byt_dump(काष्ठा snd_sof_dev *sdev, u32 flags)
अणु
	काष्ठा sof_ipc_dsp_oops_xtensa xoops;
	काष्ठा sof_ipc_panic_info panic_info;
	u32 stack[BYT_STACK_DUMP_SIZE];
	u64 status, panic, imrd, imrx;

	/* now try generic SOF status messages */
	status = snd_sof_dsp_पढ़ो64(sdev, BYT_DSP_BAR, SHIM_IPCD);
	panic = snd_sof_dsp_पढ़ो64(sdev, BYT_DSP_BAR, SHIM_IPCX);
	byt_get_रेजिस्टरs(sdev, &xoops, &panic_info, stack,
			  BYT_STACK_DUMP_SIZE);
	snd_sof_get_status(sdev, status, panic, &xoops, &panic_info, stack,
			   BYT_STACK_DUMP_SIZE);

	/* provide some context क्रम firmware debug */
	imrx = snd_sof_dsp_पढ़ो64(sdev, BYT_DSP_BAR, SHIM_IMRX);
	imrd = snd_sof_dsp_पढ़ो64(sdev, BYT_DSP_BAR, SHIM_IMRD);
	dev_err(sdev->dev,
		"error: ipc host -> DSP: pending %s complete %s raw 0x%llx\n",
		(panic & SHIM_IPCX_BUSY) ? "yes" : "no",
		(panic & SHIM_IPCX_DONE) ? "yes" : "no", panic);
	dev_err(sdev->dev,
		"error: mask host: pending %s complete %s raw 0x%llx\n",
		(imrx & SHIM_IMRX_BUSY) ? "yes" : "no",
		(imrx & SHIM_IMRX_DONE) ? "yes" : "no", imrx);
	dev_err(sdev->dev,
		"error: ipc DSP -> host: pending %s complete %s raw 0x%llx\n",
		(status & SHIM_IPCD_BUSY) ? "yes" : "no",
		(status & SHIM_IPCD_DONE) ? "yes" : "no", status);
	dev_err(sdev->dev,
		"error: mask DSP: pending %s complete %s raw 0x%llx\n",
		(imrd & SHIM_IMRD_BUSY) ? "yes" : "no",
		(imrd & SHIM_IMRD_DONE) ? "yes" : "no", imrd);

पूर्ण

/*
 * IPC Doorbell IRQ handler and thपढ़ो.
 */

अटल irqवापस_t byt_irq_handler(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा snd_sof_dev *sdev = context;
	u64 ipcx, ipcd;
	पूर्णांक ret = IRQ_NONE;

	ipcx = snd_sof_dsp_पढ़ो64(sdev, BYT_DSP_BAR, SHIM_IPCX);
	ipcd = snd_sof_dsp_पढ़ो64(sdev, BYT_DSP_BAR, SHIM_IPCD);

	अगर (ipcx & SHIM_BYT_IPCX_DONE) अणु

		/* reply message from DSP, Mask Done पूर्णांकerrupt first */
		snd_sof_dsp_update_bits64_unlocked(sdev, BYT_DSP_BAR,
						   SHIM_IMRX,
						   SHIM_IMRX_DONE,
						   SHIM_IMRX_DONE);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	अगर (ipcd & SHIM_BYT_IPCD_BUSY) अणु

		/* new message from DSP, Mask Busy पूर्णांकerrupt first */
		snd_sof_dsp_update_bits64_unlocked(sdev, BYT_DSP_BAR,
						   SHIM_IMRX,
						   SHIM_IMRX_BUSY,
						   SHIM_IMRX_BUSY);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t byt_irq_thपढ़ो(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा snd_sof_dev *sdev = context;
	u64 ipcx, ipcd;

	ipcx = snd_sof_dsp_पढ़ो64(sdev, BYT_DSP_BAR, SHIM_IPCX);
	ipcd = snd_sof_dsp_पढ़ो64(sdev, BYT_DSP_BAR, SHIM_IPCD);

	/* reply message from DSP */
	अगर (ipcx & SHIM_BYT_IPCX_DONE) अणु

		spin_lock_irq(&sdev->ipc_lock);

		/*
		 * handle immediate reply from DSP core. If the msg is
		 * found, set करोne bit in cmd_करोne which is called at the
		 * end of message processing function, अन्यथा set it here
		 * because the करोne bit can't be set in cmd_करोne function
		 * which is triggered by msg
		 */
		byt_get_reply(sdev);
		snd_sof_ipc_reply(sdev, ipcx);

		byt_dsp_करोne(sdev);

		spin_unlock_irq(&sdev->ipc_lock);
	पूर्ण

	/* new message from DSP */
	अगर (ipcd & SHIM_BYT_IPCD_BUSY) अणु

		/* Handle messages from DSP Core */
		अगर ((ipcd & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) अणु
			snd_sof_dsp_panic(sdev, BYT_PANIC_OFFSET(ipcd) +
					  MBOX_OFFSET);
		पूर्ण अन्यथा अणु
			snd_sof_ipc_msgs_rx(sdev);
		पूर्ण

		byt_host_करोne(sdev);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक byt_send_msg(काष्ठा snd_sof_dev *sdev, काष्ठा snd_sof_ipc_msg *msg)
अणु
	/* unmask and prepare to receive Done पूर्णांकerrupt */
	snd_sof_dsp_update_bits64_unlocked(sdev, BYT_DSP_BAR, SHIM_IMRX,
					   SHIM_IMRX_DONE, 0);

	/* send the message */
	sof_mailbox_ग_लिखो(sdev, sdev->host_box.offset, msg->msg_data,
			  msg->msg_size);
	snd_sof_dsp_ग_लिखो64(sdev, BYT_DSP_BAR, SHIM_IPCX, SHIM_BYT_IPCX_BUSY);

	वापस 0;
पूर्ण

अटल व्योम byt_get_reply(काष्ठा snd_sof_dev *sdev)
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

अटल पूर्णांक byt_get_mailbox_offset(काष्ठा snd_sof_dev *sdev)
अणु
	वापस MBOX_OFFSET;
पूर्ण

अटल पूर्णांक byt_get_winकरोw_offset(काष्ठा snd_sof_dev *sdev, u32 id)
अणु
	वापस MBOX_OFFSET;
पूर्ण

अटल व्योम byt_host_करोne(काष्ठा snd_sof_dev *sdev)
अणु
	/* clear BUSY bit and set DONE bit - accept new messages */
	snd_sof_dsp_update_bits64_unlocked(sdev, BYT_DSP_BAR, SHIM_IPCD,
					   SHIM_BYT_IPCD_BUSY |
					   SHIM_BYT_IPCD_DONE,
					   SHIM_BYT_IPCD_DONE);

	/* unmask and prepare to receive next new message */
	snd_sof_dsp_update_bits64_unlocked(sdev, BYT_DSP_BAR, SHIM_IMRX,
					   SHIM_IMRX_BUSY, 0);
पूर्ण

अटल व्योम byt_dsp_करोne(काष्ठा snd_sof_dev *sdev)
अणु
	/* clear DONE bit - tell DSP we have completed */
	snd_sof_dsp_update_bits64_unlocked(sdev, BYT_DSP_BAR, SHIM_IPCX,
					   SHIM_BYT_IPCX_DONE, 0);
पूर्ण

/*
 * DSP control.
 */

अटल पूर्णांक byt_run(काष्ठा snd_sof_dev *sdev)
अणु
	पूर्णांक tries = 10;

	/* release stall and रुको to unstall */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_CSR,
				  SHIM_BYT_CSR_STALL, 0x0);
	जबतक (tries--) अणु
		अगर (!(snd_sof_dsp_पढ़ो64(sdev, BYT_DSP_BAR, SHIM_CSR) &
		      SHIM_BYT_CSR_PWAITMODE))
			अवरोध;
		msleep(100);
	पूर्ण
	अगर (tries < 0) अणु
		dev_err(sdev->dev, "error:  unable to run DSP firmware\n");
		byt_dump(sdev, SOF_DBG_DUMP_REGS | SOF_DBG_DUMP_MBOX);
		वापस -ENODEV;
	पूर्ण

	/* वापस init core mask */
	वापस 1;
पूर्ण

अटल पूर्णांक byt_reset(काष्ठा snd_sof_dev *sdev)
अणु
	/* put DSP पूर्णांकo reset, set reset vector and stall */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_CSR,
				  SHIM_BYT_CSR_RST | SHIM_BYT_CSR_VECTOR_SEL |
				  SHIM_BYT_CSR_STALL,
				  SHIM_BYT_CSR_RST | SHIM_BYT_CSR_VECTOR_SEL |
				  SHIM_BYT_CSR_STALL);

	usleep_range(10, 15);

	/* take DSP out of reset and keep stalled क्रम FW loading */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_CSR,
				  SHIM_BYT_CSR_RST, 0);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *fixup_tplg_name(काष्ठा snd_sof_dev *sdev,
				   स्थिर अक्षर *sof_tplg_filename,
				   स्थिर अक्षर *ssp_str)
अणु
	स्थिर अक्षर *tplg_filename = शून्य;
	अक्षर *filename;
	अक्षर *split_ext;

	filename = devm_kstrdup(sdev->dev, sof_tplg_filename, GFP_KERNEL);
	अगर (!filename)
		वापस शून्य;

	/* this assumes a .tplg extension */
	split_ext = strsep(&filename, ".");
	अगर (split_ext) अणु
		tplg_filename = devm_kaप्र_लिखो(sdev->dev, GFP_KERNEL,
					       "%s-%s.tplg",
					       split_ext, ssp_str);
		अगर (!tplg_filename)
			वापस शून्य;
	पूर्ण
	वापस tplg_filename;
पूर्ण

अटल व्योम byt_machine_select(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *sof_pdata = sdev->pdata;
	स्थिर काष्ठा sof_dev_desc *desc = sof_pdata->desc;
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा platक्रमm_device *pdev;
	स्थिर अक्षर *tplg_filename;

	mach = snd_soc_acpi_find_machine(desc->machines);
	अगर (!mach) अणु
		dev_warn(sdev->dev, "warning: No matching ASoC machine driver found\n");
		वापस;
	पूर्ण

	pdev = to_platक्रमm_device(sdev->dev);
	अगर (soc_पूर्णांकel_is_byt_cr(pdev)) अणु
		dev_dbg(sdev->dev,
			"BYT-CR detected, SSP0 used instead of SSP2\n");

		tplg_filename = fixup_tplg_name(sdev,
						mach->sof_tplg_filename,
						"ssp0");
	पूर्ण अन्यथा अणु
		tplg_filename = mach->sof_tplg_filename;
	पूर्ण

	अगर (!tplg_filename) अणु
		dev_dbg(sdev->dev,
			"error: no topology filename\n");
		वापस;
	पूर्ण

	sof_pdata->tplg_filename = tplg_filename;
	mach->mach_params.acpi_ipc_irq_index = desc->irqindex_host_ipc;
	sof_pdata->machine = mach;
पूर्ण

/* Baytrail DAIs */
अटल काष्ठा snd_soc_dai_driver byt_dai[] = अणु
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
अणु
	.name = "ssp2-port",
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण
पूर्ण,
अणु
	.name = "ssp3-port",
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
	.name = "ssp4-port",
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
	.name = "ssp5-port",
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

अटल व्योम byt_set_mach_params(स्थिर काष्ठा snd_soc_acpi_mach *mach,
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

/*
 * Probe and हटाओ.
 */

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_MERRIFIELD)

अटल पूर्णांक tangier_pci_probe(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *pdata = sdev->pdata;
	स्थिर काष्ठा sof_dev_desc *desc = pdata->desc;
	काष्ठा pci_dev *pci = to_pci_dev(sdev->dev);
	u32 base, size;
	पूर्णांक ret;

	/* DSP DMA can only access low 31 bits of host memory */
	ret = dma_coerce_mask_and_coherent(&pci->dev, DMA_BIT_MASK(31));
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to set DMA mask %d\n", ret);
		वापस ret;
	पूर्ण

	/* LPE base */
	base = pci_resource_start(pci, desc->resindex_lpe_base) - IRAM_OFFSET;
	size = BYT_PCI_BAR_SIZE;

	dev_dbg(sdev->dev, "LPE PHY base at 0x%x size 0x%x", base, size);
	sdev->bar[BYT_DSP_BAR] = devm_ioremap(sdev->dev, base, size);
	अगर (!sdev->bar[BYT_DSP_BAR]) अणु
		dev_err(sdev->dev, "error: failed to ioremap LPE base 0x%x size 0x%x\n",
			base, size);
		वापस -ENODEV;
	पूर्ण
	dev_dbg(sdev->dev, "LPE VADDR %p\n", sdev->bar[BYT_DSP_BAR]);

	/* IMR base - optional */
	अगर (desc->resindex_imr_base == -1)
		जाओ irq;

	base = pci_resource_start(pci, desc->resindex_imr_base);
	size = pci_resource_len(pci, desc->resindex_imr_base);

	/* some BIOSes करोn't map IMR */
	अगर (base == 0x55aa55aa || base == 0x0) अणु
		dev_info(sdev->dev, "IMR not set by BIOS. Ignoring\n");
		जाओ irq;
	पूर्ण

	dev_dbg(sdev->dev, "IMR base at 0x%x size 0x%x", base, size);
	sdev->bar[BYT_IMR_BAR] = devm_ioremap(sdev->dev, base, size);
	अगर (!sdev->bar[BYT_IMR_BAR]) अणु
		dev_err(sdev->dev, "error: failed to ioremap IMR base 0x%x size 0x%x\n",
			base, size);
		वापस -ENODEV;
	पूर्ण
	dev_dbg(sdev->dev, "IMR VADDR %p\n", sdev->bar[BYT_IMR_BAR]);

irq:
	/* रेजिस्टर our IRQ */
	sdev->ipc_irq = pci->irq;
	dev_dbg(sdev->dev, "using IRQ %d\n", sdev->ipc_irq);
	ret = devm_request_thपढ़ोed_irq(sdev->dev, sdev->ipc_irq,
					byt_irq_handler, byt_irq_thपढ़ो,
					0, "AudioDSP", sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to register IRQ %d\n",
			sdev->ipc_irq);
		वापस ret;
	पूर्ण

	/* enable BUSY and disable DONE Interrupt by शेष */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_IMRX,
				  SHIM_IMRX_BUSY | SHIM_IMRX_DONE,
				  SHIM_IMRX_DONE);

	/* set शेष mailbox offset क्रम FW पढ़ोy message */
	sdev->dsp_box.offset = MBOX_OFFSET;

	वापस ret;
पूर्ण

स्थिर काष्ठा snd_sof_dsp_ops sof_tng_ops = अणु
	/* device init */
	.probe		= tangier_pci_probe,

	/* DSP core boot / reset */
	.run		= byt_run,
	.reset		= byt_reset,

	/* Register IO */
	.ग_लिखो		= sof_io_ग_लिखो,
	.पढ़ो		= sof_io_पढ़ो,
	.ग_लिखो64	= sof_io_ग_लिखो64,
	.पढ़ो64		= sof_io_पढ़ो64,

	/* Block IO */
	.block_पढ़ो	= sof_block_पढ़ो,
	.block_ग_लिखो	= sof_block_ग_लिखो,

	/* करोorbell */
	.irq_handler	= byt_irq_handler,
	.irq_thपढ़ो	= byt_irq_thपढ़ो,

	/* ipc */
	.send_msg	= byt_send_msg,
	.fw_पढ़ोy	= sof_fw_पढ़ोy,
	.get_mailbox_offset = byt_get_mailbox_offset,
	.get_winकरोw_offset = byt_get_winकरोw_offset,

	.ipc_msg_data	= पूर्णांकel_ipc_msg_data,
	.ipc_pcm_params	= पूर्णांकel_ipc_pcm_params,

	/* machine driver */
	.machine_select = byt_machine_select,
	.machine_रेजिस्टर = sof_machine_रेजिस्टर,
	.machine_unरेजिस्टर = sof_machine_unरेजिस्टर,
	.set_mach_params = byt_set_mach_params,

	/* debug */
	.debug_map	= byt_debugfs,
	.debug_map_count	= ARRAY_SIZE(byt_debugfs),
	.dbg_dump	= byt_dump,

	/* stream callbacks */
	.pcm_खोलो	= पूर्णांकel_pcm_खोलो,
	.pcm_बंद	= पूर्णांकel_pcm_बंद,

	/* module loading */
	.load_module	= snd_sof_parse_module_स_नकल,

	/*Firmware loading */
	.load_firmware	= snd_sof_load_firmware_स_नकल,

	/* DAI drivers */
	.drv = byt_dai,
	.num_drv = 3, /* we have only 3 SSPs on byt*/

	/* ALSA HW info flags */
	.hw_info =	SNDRV_PCM_INFO_MMAP |
			SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_INTERLEAVED |
			SNDRV_PCM_INFO_PAUSE |
			SNDRV_PCM_INFO_BATCH,

	.arch_ops = &sof_xtensa_arch_ops,
पूर्ण;
EXPORT_SYMBOL_NS(sof_tng_ops, SND_SOC_SOF_MERRIFIELD);

स्थिर काष्ठा sof_पूर्णांकel_dsp_desc tng_chip_info = अणु
	.cores_num = 1,
	.host_managed_cores_mask = 1,
पूर्ण;
EXPORT_SYMBOL_NS(tng_chip_info, SND_SOC_SOF_MERRIFIELD);

#पूर्ण_अगर /* CONFIG_SND_SOC_SOF_MERRIFIELD */

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_BAYTRAIL)

अटल व्योम byt_reset_dsp_disable_पूर्णांक(काष्ठा snd_sof_dev *sdev)
अणु
	/* Disable Interrupt from both sides */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_IMRX, 0x3, 0x3);
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_IMRD, 0x3, 0x3);

	/* Put DSP पूर्णांकo reset, set reset vector */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_CSR,
				  SHIM_BYT_CSR_RST | SHIM_BYT_CSR_VECTOR_SEL,
				  SHIM_BYT_CSR_RST | SHIM_BYT_CSR_VECTOR_SEL);
पूर्ण

अटल पूर्णांक byt_suspend(काष्ठा snd_sof_dev *sdev, u32 target_state)
अणु
	byt_reset_dsp_disable_पूर्णांक(sdev);

	वापस 0;
पूर्ण

अटल पूर्णांक byt_resume(काष्ठा snd_sof_dev *sdev)
अणु
	/* enable BUSY and disable DONE Interrupt by शेष */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_IMRX,
				  SHIM_IMRX_BUSY | SHIM_IMRX_DONE,
				  SHIM_IMRX_DONE);

	वापस 0;
पूर्ण

अटल पूर्णांक byt_हटाओ(काष्ठा snd_sof_dev *sdev)
अणु
	byt_reset_dsp_disable_पूर्णांक(sdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_sof_debugfs_map cht_debugfs[] = अणु
	अणु"dmac0", BYT_DSP_BAR, DMAC0_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"dmac1", BYT_DSP_BAR,  DMAC1_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"dmac2", BYT_DSP_BAR,  DMAC2_OFFSET, DMAC_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp0",  BYT_DSP_BAR, SSP0_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp1", BYT_DSP_BAR, SSP1_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp2", BYT_DSP_BAR, SSP2_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp3", BYT_DSP_BAR, SSP3_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp4", BYT_DSP_BAR, SSP4_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"ssp5", BYT_DSP_BAR, SSP5_OFFSET, SSP_SIZE,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
	अणु"iram", BYT_DSP_BAR, IRAM_OFFSET, IRAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONLYपूर्ण,
	अणु"dram", BYT_DSP_BAR, DRAM_OFFSET, DRAM_SIZE,
	 SOF_DEBUGFS_ACCESS_D0_ONLYपूर्ण,
	अणु"shim", BYT_DSP_BAR, SHIM_OFFSET, SHIM_SIZE_CHT,
	 SOF_DEBUGFS_ACCESS_ALWAYSपूर्ण,
पूर्ण;

अटल पूर्णांक byt_acpi_probe(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा snd_sof_pdata *pdata = sdev->pdata;
	स्थिर काष्ठा sof_dev_desc *desc = pdata->desc;
	काष्ठा platक्रमm_device *pdev =
		container_of(sdev->dev, काष्ठा platक्रमm_device, dev);
	काष्ठा resource *mmio;
	u32 base, size;
	पूर्णांक ret;

	/* DSP DMA can only access low 31 bits of host memory */
	ret = dma_coerce_mask_and_coherent(sdev->dev, DMA_BIT_MASK(31));
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to set DMA mask %d\n", ret);
		वापस ret;
	पूर्ण

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
	sdev->bar[BYT_DSP_BAR] = devm_ioremap(sdev->dev, base, size);
	अगर (!sdev->bar[BYT_DSP_BAR]) अणु
		dev_err(sdev->dev, "error: failed to ioremap LPE base 0x%x size 0x%x\n",
			base, size);
		वापस -ENODEV;
	पूर्ण
	dev_dbg(sdev->dev, "LPE VADDR %p\n", sdev->bar[BYT_DSP_BAR]);

	/* TODO: add offsets */
	sdev->mmio_bar = BYT_DSP_BAR;
	sdev->mailbox_bar = BYT_DSP_BAR;

	/* IMR base - optional */
	अगर (desc->resindex_imr_base == -1)
		जाओ irq;

	mmio = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
				     desc->resindex_imr_base);
	अगर (mmio) अणु
		base = mmio->start;
		size = resource_size(mmio);
	पूर्ण अन्यथा अणु
		dev_err(sdev->dev, "error: failed to get IMR base at idx %d\n",
			desc->resindex_imr_base);
		वापस -ENODEV;
	पूर्ण

	/* some BIOSes करोn't map IMR */
	अगर (base == 0x55aa55aa || base == 0x0) अणु
		dev_info(sdev->dev, "IMR not set by BIOS. Ignoring\n");
		जाओ irq;
	पूर्ण

	dev_dbg(sdev->dev, "IMR base at 0x%x size 0x%x", base, size);
	sdev->bar[BYT_IMR_BAR] = devm_ioremap(sdev->dev, base, size);
	अगर (!sdev->bar[BYT_IMR_BAR]) अणु
		dev_err(sdev->dev, "error: failed to ioremap IMR base 0x%x size 0x%x\n",
			base, size);
		वापस -ENODEV;
	पूर्ण
	dev_dbg(sdev->dev, "IMR VADDR %p\n", sdev->bar[BYT_IMR_BAR]);

irq:
	/* रेजिस्टर our IRQ */
	sdev->ipc_irq = platक्रमm_get_irq(pdev, desc->irqindex_host_ipc);
	अगर (sdev->ipc_irq < 0)
		वापस sdev->ipc_irq;

	dev_dbg(sdev->dev, "using IRQ %d\n", sdev->ipc_irq);
	ret = devm_request_thपढ़ोed_irq(sdev->dev, sdev->ipc_irq,
					byt_irq_handler, byt_irq_thपढ़ो,
					IRQF_SHARED, "AudioDSP", sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: failed to register IRQ %d\n",
			sdev->ipc_irq);
		वापस ret;
	पूर्ण

	/* enable BUSY and disable DONE Interrupt by शेष */
	snd_sof_dsp_update_bits64(sdev, BYT_DSP_BAR, SHIM_IMRX,
				  SHIM_IMRX_BUSY | SHIM_IMRX_DONE,
				  SHIM_IMRX_DONE);

	/* set शेष mailbox offset क्रम FW पढ़ोy message */
	sdev->dsp_box.offset = MBOX_OFFSET;

	वापस ret;
पूर्ण

/* baytrail ops */
अटल स्थिर काष्ठा snd_sof_dsp_ops sof_byt_ops = अणु
	/* device init */
	.probe		= byt_acpi_probe,
	.हटाओ		= byt_हटाओ,

	/* DSP core boot / reset */
	.run		= byt_run,
	.reset		= byt_reset,

	/* Register IO */
	.ग_लिखो		= sof_io_ग_लिखो,
	.पढ़ो		= sof_io_पढ़ो,
	.ग_लिखो64	= sof_io_ग_लिखो64,
	.पढ़ो64		= sof_io_पढ़ो64,

	/* Block IO */
	.block_पढ़ो	= sof_block_पढ़ो,
	.block_ग_लिखो	= sof_block_ग_लिखो,

	/* करोorbell */
	.irq_handler	= byt_irq_handler,
	.irq_thपढ़ो	= byt_irq_thपढ़ो,

	/* ipc */
	.send_msg	= byt_send_msg,
	.fw_पढ़ोy	= sof_fw_पढ़ोy,
	.get_mailbox_offset = byt_get_mailbox_offset,
	.get_winकरोw_offset = byt_get_winकरोw_offset,

	.ipc_msg_data	= पूर्णांकel_ipc_msg_data,
	.ipc_pcm_params	= पूर्णांकel_ipc_pcm_params,

	/* machine driver */
	.machine_select = byt_machine_select,
	.machine_रेजिस्टर = sof_machine_रेजिस्टर,
	.machine_unरेजिस्टर = sof_machine_unरेजिस्टर,
	.set_mach_params = byt_set_mach_params,

	/* debug */
	.debug_map	= byt_debugfs,
	.debug_map_count	= ARRAY_SIZE(byt_debugfs),
	.dbg_dump	= byt_dump,

	/* stream callbacks */
	.pcm_खोलो	= पूर्णांकel_pcm_खोलो,
	.pcm_बंद	= पूर्णांकel_pcm_बंद,

	/* module loading */
	.load_module	= snd_sof_parse_module_स_नकल,

	/*Firmware loading */
	.load_firmware	= snd_sof_load_firmware_स_नकल,

	/* PM */
	.suspend = byt_suspend,
	.resume = byt_resume,

	/* DAI drivers */
	.drv = byt_dai,
	.num_drv = 3, /* we have only 3 SSPs on byt*/

	/* ALSA HW info flags */
	.hw_info =	SNDRV_PCM_INFO_MMAP |
			SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_INTERLEAVED |
			SNDRV_PCM_INFO_PAUSE |
			SNDRV_PCM_INFO_BATCH,

	.arch_ops = &sof_xtensa_arch_ops,
पूर्ण;

अटल स्थिर काष्ठा sof_पूर्णांकel_dsp_desc byt_chip_info = अणु
	.cores_num = 1,
	.host_managed_cores_mask = 1,
पूर्ण;

/* cherrytrail and braswell ops */
अटल स्थिर काष्ठा snd_sof_dsp_ops sof_cht_ops = अणु
	/* device init */
	.probe		= byt_acpi_probe,
	.हटाओ		= byt_हटाओ,

	/* DSP core boot / reset */
	.run		= byt_run,
	.reset		= byt_reset,

	/* Register IO */
	.ग_लिखो		= sof_io_ग_लिखो,
	.पढ़ो		= sof_io_पढ़ो,
	.ग_लिखो64	= sof_io_ग_लिखो64,
	.पढ़ो64		= sof_io_पढ़ो64,

	/* Block IO */
	.block_पढ़ो	= sof_block_पढ़ो,
	.block_ग_लिखो	= sof_block_ग_लिखो,

	/* करोorbell */
	.irq_handler	= byt_irq_handler,
	.irq_thपढ़ो	= byt_irq_thपढ़ो,

	/* ipc */
	.send_msg	= byt_send_msg,
	.fw_पढ़ोy	= sof_fw_पढ़ोy,
	.get_mailbox_offset = byt_get_mailbox_offset,
	.get_winकरोw_offset = byt_get_winकरोw_offset,

	.ipc_msg_data	= पूर्णांकel_ipc_msg_data,
	.ipc_pcm_params	= पूर्णांकel_ipc_pcm_params,

	/* machine driver */
	.machine_select = byt_machine_select,
	.machine_रेजिस्टर = sof_machine_रेजिस्टर,
	.machine_unरेजिस्टर = sof_machine_unरेजिस्टर,
	.set_mach_params = byt_set_mach_params,

	/* debug */
	.debug_map	= cht_debugfs,
	.debug_map_count	= ARRAY_SIZE(cht_debugfs),
	.dbg_dump	= byt_dump,

	/* stream callbacks */
	.pcm_खोलो	= पूर्णांकel_pcm_खोलो,
	.pcm_बंद	= पूर्णांकel_pcm_बंद,

	/* module loading */
	.load_module	= snd_sof_parse_module_स_नकल,

	/*Firmware loading */
	.load_firmware	= snd_sof_load_firmware_स_नकल,

	/* PM */
	.suspend = byt_suspend,
	.resume = byt_resume,

	/* DAI drivers */
	.drv = byt_dai,
	/* all 6 SSPs may be available क्रम cherrytrail */
	.num_drv = ARRAY_SIZE(byt_dai),

	/* ALSA HW info flags */
	.hw_info =	SNDRV_PCM_INFO_MMAP |
			SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_INTERLEAVED |
			SNDRV_PCM_INFO_PAUSE |
			SNDRV_PCM_INFO_BATCH,

	.arch_ops = &sof_xtensa_arch_ops,
पूर्ण;

अटल स्थिर काष्ठा sof_पूर्णांकel_dsp_desc cht_chip_info = अणु
	.cores_num = 1,
	.host_managed_cores_mask = 1,
पूर्ण;

/* BYTCR uses dअगरferent IRQ index */
अटल स्थिर काष्ठा sof_dev_desc sof_acpi_baytrailcr_desc = अणु
	.machines = snd_soc_acpi_पूर्णांकel_baytrail_machines,
	.resindex_lpe_base = 0,
	.resindex_pcicfg_base = 1,
	.resindex_imr_base = 2,
	.irqindex_host_ipc = 0,
	.chip_info = &byt_chip_info,
	.शेष_fw_path = "intel/sof",
	.शेष_tplg_path = "intel/sof-tplg",
	.शेष_fw_filename = "sof-byt.ri",
	.nocodec_tplg_filename = "sof-byt-nocodec.tplg",
	.ops = &sof_byt_ops,
पूर्ण;

अटल स्थिर काष्ठा sof_dev_desc sof_acpi_baytrail_desc = अणु
	.machines = snd_soc_acpi_पूर्णांकel_baytrail_machines,
	.resindex_lpe_base = 0,
	.resindex_pcicfg_base = 1,
	.resindex_imr_base = 2,
	.irqindex_host_ipc = 5,
	.chip_info = &byt_chip_info,
	.शेष_fw_path = "intel/sof",
	.शेष_tplg_path = "intel/sof-tplg",
	.शेष_fw_filename = "sof-byt.ri",
	.nocodec_tplg_filename = "sof-byt-nocodec.tplg",
	.ops = &sof_byt_ops,
पूर्ण;

अटल स्थिर काष्ठा sof_dev_desc sof_acpi_cherrytrail_desc = अणु
	.machines = snd_soc_acpi_पूर्णांकel_cherrytrail_machines,
	.resindex_lpe_base = 0,
	.resindex_pcicfg_base = 1,
	.resindex_imr_base = 2,
	.irqindex_host_ipc = 5,
	.chip_info = &cht_chip_info,
	.शेष_fw_path = "intel/sof",
	.शेष_tplg_path = "intel/sof-tplg",
	.शेष_fw_filename = "sof-cht.ri",
	.nocodec_tplg_filename = "sof-cht-nocodec.tplg",
	.ops = &sof_cht_ops,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id sof_baytrail_match[] = अणु
	अणु "80860F28", (अचिन्हित दीर्घ)&sof_acpi_baytrail_desc पूर्ण,
	अणु "808622A8", (अचिन्हित दीर्घ)&sof_acpi_cherrytrail_desc पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, sof_baytrail_match);

अटल पूर्णांक sof_baytrail_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा sof_dev_desc *desc;
	स्थिर काष्ठा acpi_device_id *id;
	पूर्णांक ret;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस -ENODEV;

	ret = snd_पूर्णांकel_acpi_dsp_driver_probe(dev, id->id);
	अगर (ret != SND_INTEL_DSP_DRIVER_ANY && ret != SND_INTEL_DSP_DRIVER_SOF) अणु
		dev_dbg(dev, "SOF ACPI driver not selected, aborting probe\n");
		वापस -ENODEV;
	पूर्ण

	desc = device_get_match_data(&pdev->dev);
	अगर (!desc)
		वापस -ENODEV;

	अगर (desc == &sof_acpi_baytrail_desc && soc_पूर्णांकel_is_byt_cr(pdev))
		desc = &sof_acpi_baytrailcr_desc;

	वापस sof_acpi_probe(pdev, desc);
पूर्ण

/* acpi_driver definition */
अटल काष्ठा platक्रमm_driver snd_sof_acpi_पूर्णांकel_byt_driver = अणु
	.probe = sof_baytrail_probe,
	.हटाओ = sof_acpi_हटाओ,
	.driver = अणु
		.name = "sof-audio-acpi-intel-byt",
		.pm = &sof_acpi_pm,
		.acpi_match_table = sof_baytrail_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(snd_sof_acpi_पूर्णांकel_byt_driver);

#पूर्ण_अगर /* CONFIG_SND_SOC_SOF_BAYTRAIL */

MODULE_LICENSE("Dual BSD/GPL");
MODULE_IMPORT_NS(SND_SOC_SOF_INTEL_HIFI_EP_IPC);
MODULE_IMPORT_NS(SND_SOC_SOF_XTENSA);
MODULE_IMPORT_NS(SND_SOC_SOF_ACPI_DEV);
