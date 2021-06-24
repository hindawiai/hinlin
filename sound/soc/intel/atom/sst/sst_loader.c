<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  sst_dsp.c - Intel SST Driver क्रम audio engine
 *
 *  Copyright (C) 2008-14	Intel Corp
 *  Authors:	Vinod Koul <vinod.koul@पूर्णांकel.com>
 *		Harsha Priya <priya.harsha@पूर्णांकel.com>
 *		Dharageswari R <dharageswari.r@पूर्णांकel.com>
 *		KP Jeeja <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This file contains all dsp controlling functions like firmware करोwnload,
 * setting/resetting dsp cores, etc
 */
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/firmware.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_qos.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/compress_driver.h>
#समावेश <यंत्र/platक्रमm_sst_audपन.स>
#समावेश "../sst-mfld-platform.h"
#समावेश "sst.h"

व्योम स_नकल32_toio(व्योम __iomem *dst, स्थिर व्योम *src, पूर्णांक count)
अणु
	/* __ioग_लिखो32_copy uses 32-bit count values so भागide by 4 क्रम
	 * right count in words
	 */
	__ioग_लिखो32_copy(dst, src, count / 4);
पूर्ण

व्योम स_नकल32_fromio(व्योम *dst, स्थिर व्योम __iomem *src, पूर्णांक count)
अणु
	/* __ioपढ़ो32_copy uses 32-bit count values so भागide by 4 क्रम
	 * right count in words
	 */
	__ioपढ़ो32_copy(dst, src, count / 4);
पूर्ण

/**
 * पूर्णांकel_sst_reset_dsp_mrfld - Resetting SST DSP
 * @sst_drv_ctx: पूर्णांकel_sst_drv context poपूर्णांकer
 *
 * This resets DSP in हाल of MRFLD platfroms
 */
पूर्णांक पूर्णांकel_sst_reset_dsp_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx)
अणु
	जोड़ config_status_reg_mrfld csr;

	dev_dbg(sst_drv_ctx->dev, "sst: Resetting the DSP in mrfld\n");
	csr.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_CSR);

	dev_dbg(sst_drv_ctx->dev, "value:0x%llx\n", csr.full);

	csr.full |= 0x7;
	sst_shim_ग_लिखो64(sst_drv_ctx->shim, SST_CSR, csr.full);
	csr.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_CSR);

	dev_dbg(sst_drv_ctx->dev, "value:0x%llx\n", csr.full);

	csr.full &= ~(0x1);
	sst_shim_ग_लिखो64(sst_drv_ctx->shim, SST_CSR, csr.full);

	csr.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_CSR);
	dev_dbg(sst_drv_ctx->dev, "value:0x%llx\n", csr.full);
	वापस 0;
पूर्ण

/**
 * sst_start_mrfld - Start the SST DSP processor
 * @sst_drv_ctx: पूर्णांकel_sst_drv context poपूर्णांकer
 *
 * This starts the DSP in MERRIFIELD platfroms
 */
पूर्णांक sst_start_mrfld(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx)
अणु
	जोड़ config_status_reg_mrfld csr;

	dev_dbg(sst_drv_ctx->dev, "sst: Starting the DSP in mrfld LALALALA\n");
	csr.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_CSR);
	dev_dbg(sst_drv_ctx->dev, "value:0x%llx\n", csr.full);

	csr.full |= 0x7;
	sst_shim_ग_लिखो64(sst_drv_ctx->shim, SST_CSR, csr.full);

	csr.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_CSR);
	dev_dbg(sst_drv_ctx->dev, "value:0x%llx\n", csr.full);

	csr.part.xt_snoop = 1;
	csr.full &= ~(0x5);
	sst_shim_ग_लिखो64(sst_drv_ctx->shim, SST_CSR, csr.full);

	csr.full = sst_shim_पढ़ो64(sst_drv_ctx->shim, SST_CSR);
	dev_dbg(sst_drv_ctx->dev, "sst: Starting the DSP_merrifield:%llx\n",
			csr.full);
	वापस 0;
पूर्ण

अटल पूर्णांक sst_validate_fw_image(काष्ठा पूर्णांकel_sst_drv *ctx, अचिन्हित दीर्घ size,
		काष्ठा fw_module_header **module, u32 *num_modules)
अणु
	काष्ठा sst_fw_header *header;
	स्थिर व्योम *sst_fw_in_mem = ctx->fw_in_mem;

	dev_dbg(ctx->dev, "Enter\n");

	/* Read the header inक्रमmation from the data poपूर्णांकer */
	header = (काष्ठा sst_fw_header *)sst_fw_in_mem;
	dev_dbg(ctx->dev,
		"header sign=%s size=%x modules=%x fmt=%x size=%zx\n",
		header->signature, header->file_size, header->modules,
		header->file_क्रमmat, माप(*header));

	/* verअगरy FW */
	अगर ((म_भेदन(header->signature, SST_FW_SIGN, 4) != 0) ||
		(size != header->file_size + माप(*header))) अणु
		/* Invalid FW signature */
		dev_err(ctx->dev, "InvalidFW sign/filesize mismatch\n");
		वापस -EINVAL;
	पूर्ण
	*num_modules = header->modules;
	*module = (व्योम *)sst_fw_in_mem + माप(*header);

	वापस 0;
पूर्ण

/*
 * sst_fill_स_नकल_list - Fill the स_नकल list
 *
 * @स_नकल_list: List to be filled
 * @destn: Destination addr to be filled in the list
 * @src: Source addr to be filled in the list
 * @size: Size to be filled in the list
 *
 * Adds the node to the list after required fields
 * are populated in the node
 */
अटल पूर्णांक sst_fill_स_नकल_list(काष्ठा list_head *स_नकल_list,
			व्योम *destn, स्थिर व्योम *src, u32 size, bool is_io)
अणु
	काष्ठा sst_स_नकल_list *listnode;

	listnode = kzalloc(माप(*listnode), GFP_KERNEL);
	अगर (listnode == शून्य)
		वापस -ENOMEM;
	listnode->dstn = destn;
	listnode->src = src;
	listnode->size = size;
	listnode->is_io = is_io;
	list_add_tail(&listnode->स_नकलlist, स_नकल_list);

	वापस 0;
पूर्ण

/**
 * sst_parse_module_स_नकल - Parse audio FW modules and populate the स_नकल list
 *
 * @sst_drv_ctx		: driver context
 * @module		: FW module header
 * @स_नकल_list	: Poपूर्णांकer to the list to be populated
 * Create the स_नकल list as the number of block to be copied
 * वापसs error or 0 अगर module sizes are proper
 */
अटल पूर्णांक sst_parse_module_स_नकल(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx,
		काष्ठा fw_module_header *module, काष्ठा list_head *स_नकल_list)
अणु
	काष्ठा fw_block_info *block;
	u32 count;
	पूर्णांक ret_val = 0;
	व्योम __iomem *ram_iomem;

	dev_dbg(sst_drv_ctx->dev, "module sign %s size %x blocks %x type %x\n",
			module->signature, module->mod_size,
			module->blocks, module->type);
	dev_dbg(sst_drv_ctx->dev, "module entrypoint 0x%x\n", module->entry_poपूर्णांक);

	block = (व्योम *)module + माप(*module);

	क्रम (count = 0; count < module->blocks; count++) अणु
		अगर (block->size <= 0) अणु
			dev_err(sst_drv_ctx->dev, "block size invalid\n");
			वापस -EINVAL;
		पूर्ण
		चयन (block->type) अणु
		हाल SST_IRAM:
			ram_iomem = sst_drv_ctx->iram;
			अवरोध;
		हाल SST_DRAM:
			ram_iomem = sst_drv_ctx->dram;
			अवरोध;
		हाल SST_DDR:
			ram_iomem = sst_drv_ctx->ddr;
			अवरोध;
		हाल SST_CUSTOM_INFO:
			block = (व्योम *)block + माप(*block) + block->size;
			जारी;
		शेष:
			dev_err(sst_drv_ctx->dev, "wrong ram type0x%x in block0x%x\n",
					block->type, count);
			वापस -EINVAL;
		पूर्ण

		ret_val = sst_fill_स_नकल_list(स_नकल_list,
				ram_iomem + block->ram_offset,
				(व्योम *)block + माप(*block), block->size, 1);
		अगर (ret_val)
			वापस ret_val;

		block = (व्योम *)block + माप(*block) + block->size;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * sst_parse_fw_स_नकल - parse the firmware image & populate the list क्रम स_नकल
 *
 * @ctx			: poपूर्णांकer to drv context
 * @size		: size of the firmware
 * @fw_list		: poपूर्णांकer to list_head to be populated
 * This function parses the FW image and saves the parsed image in the list
 * क्रम स_नकल
 */
अटल पूर्णांक sst_parse_fw_स_नकल(काष्ठा पूर्णांकel_sst_drv *ctx, अचिन्हित दीर्घ size,
				काष्ठा list_head *fw_list)
अणु
	काष्ठा fw_module_header *module;
	u32 count, num_modules;
	पूर्णांक ret_val;

	ret_val = sst_validate_fw_image(ctx, size, &module, &num_modules);
	अगर (ret_val)
		वापस ret_val;

	क्रम (count = 0; count < num_modules; count++) अणु
		ret_val = sst_parse_module_स_नकल(ctx, module, fw_list);
		अगर (ret_val)
			वापस ret_val;
		module = (व्योम *)module + माप(*module) + module->mod_size;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sst_करो_स_नकल - function initiates the स_नकल
 *
 * @स_नकल_list: Pter to स_नकल list on which the स_नकल needs to be initiated
 *
 * Triggers the स_नकल
 */
अटल व्योम sst_करो_स_नकल(काष्ठा list_head *स_नकल_list)
अणु
	काष्ठा sst_स_नकल_list *listnode;

	list_क्रम_each_entry(listnode, स_नकल_list, स_नकलlist) अणु
		अगर (listnode->is_io)
			स_नकल32_toio((व्योम __iomem *)listnode->dstn,
					listnode->src, listnode->size);
		अन्यथा
			स_नकल(listnode->dstn, listnode->src, listnode->size);
	पूर्ण
पूर्ण

व्योम sst_स_नकल_मुक्त_resources(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx)
अणु
	काष्ठा sst_स_नकल_list *listnode, *पंचांगplistnode;

	/* Free the list */
	list_क्रम_each_entry_safe(listnode, पंचांगplistnode,
				 &sst_drv_ctx->स_नकल_list, स_नकलlist) अणु
		list_del(&listnode->स_नकलlist);
		kमुक्त(listnode);
	पूर्ण
पूर्ण

अटल पूर्णांक sst_cache_and_parse_fw(काष्ठा पूर्णांकel_sst_drv *sst,
		स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक retval = 0;

	sst->fw_in_mem = kzalloc(fw->size, GFP_KERNEL);
	अगर (!sst->fw_in_mem) अणु
		retval = -ENOMEM;
		जाओ end_release;
	पूर्ण
	dev_dbg(sst->dev, "copied fw to %p", sst->fw_in_mem);
	dev_dbg(sst->dev, "phys: %lx", (अचिन्हित दीर्घ)virt_to_phys(sst->fw_in_mem));
	स_नकल(sst->fw_in_mem, fw->data, fw->size);
	retval = sst_parse_fw_स_नकल(sst, fw->size, &sst->स_नकल_list);
	अगर (retval) अणु
		dev_err(sst->dev, "Failed to parse fw\n");
		kमुक्त(sst->fw_in_mem);
		sst->fw_in_mem = शून्य;
	पूर्ण

end_release:
	release_firmware(fw);
	वापस retval;

पूर्ण

व्योम sst_firmware_load_cb(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = context;

	dev_dbg(ctx->dev, "Enter\n");

	अगर (fw == शून्य) अणु
		dev_err(ctx->dev, "request fw failed\n");
		वापस;
	पूर्ण

	mutex_lock(&ctx->sst_lock);

	अगर (ctx->sst_state != SST_RESET ||
			ctx->fw_in_mem != शून्य) अणु
		release_firmware(fw);
		mutex_unlock(&ctx->sst_lock);
		वापस;
	पूर्ण

	dev_dbg(ctx->dev, "Request Fw completed\n");
	sst_cache_and_parse_fw(ctx, fw);
	mutex_unlock(&ctx->sst_lock);
पूर्ण

/*
 * sst_request_fw - requests audio fw from kernel and saves a copy
 *
 * This function requests the SST FW from the kernel, parses it and
 * saves a copy in the driver context
 */
अटल पूर्णांक sst_request_fw(काष्ठा पूर्णांकel_sst_drv *sst)
अणु
	पूर्णांक retval = 0;
	स्थिर काष्ठा firmware *fw;

	retval = request_firmware(&fw, sst->firmware_name, sst->dev);
	अगर (retval) अणु
		dev_err(sst->dev, "request fw failed %d\n", retval);
		वापस retval;
	पूर्ण
	अगर (fw == शून्य) अणु
		dev_err(sst->dev, "fw is returning as null\n");
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&sst->sst_lock);
	retval = sst_cache_and_parse_fw(sst, fw);
	mutex_unlock(&sst->sst_lock);

	वापस retval;
पूर्ण

/*
 * Writing the DDR physical base to DCCM offset
 * so that FW can use it to setup TLB
 */
अटल व्योम sst_dccm_config_ग_लिखो(व्योम __iomem *dram_base,
		अचिन्हित पूर्णांक ddr_base)
अणु
	व्योम __iomem *addr;
	u32 bss_reset = 0;

	addr = (व्योम __iomem *)(dram_base + MRFLD_FW_DDR_BASE_OFFSET);
	स_नकल32_toio(addr, (व्योम *)&ddr_base, माप(u32));
	bss_reset |= (1 << MRFLD_FW_BSS_RESET_BIT);
	addr = (व्योम __iomem *)(dram_base + MRFLD_FW_FEATURE_BASE_OFFSET);
	स_नकल32_toio(addr, &bss_reset, माप(u32));

पूर्ण

व्योम sst_post_करोwnload_mrfld(काष्ठा पूर्णांकel_sst_drv *ctx)
अणु
	sst_dccm_config_ग_लिखो(ctx->dram, ctx->ddr_base);
	dev_dbg(ctx->dev, "config written to DCCM\n");
पूर्ण

/**
 * sst_load_fw - function to load FW पूर्णांकo DSP
 * @sst_drv_ctx: पूर्णांकel_sst_drv context poपूर्णांकer
 *
 * Transfers the FW to DSP using dma/स_नकल
 */
पूर्णांक sst_load_fw(काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx)
अणु
	पूर्णांक ret_val = 0;
	काष्ठा sst_block *block;

	dev_dbg(sst_drv_ctx->dev, "sst_load_fw\n");

	अगर (sst_drv_ctx->sst_state !=  SST_RESET)
		वापस -EAGAIN;

	अगर (!sst_drv_ctx->fw_in_mem) अणु
		dev_dbg(sst_drv_ctx->dev, "sst: FW not in memory retry to download\n");
		ret_val = sst_request_fw(sst_drv_ctx);
		अगर (ret_val)
			वापस ret_val;
	पूर्ण

	block = sst_create_block(sst_drv_ctx, 0, FW_DWNL_ID);
	अगर (block == शून्य)
		वापस -ENOMEM;

	/* Prevent C-states beyond C6 */
	cpu_latency_qos_update_request(sst_drv_ctx->qos, 0);

	sst_drv_ctx->sst_state = SST_FW_LOADING;

	ret_val = sst_drv_ctx->ops->reset(sst_drv_ctx);
	अगर (ret_val)
		जाओ restore;

	sst_करो_स_नकल(&sst_drv_ctx->स_नकल_list);

	/* Write the DRAM/DCCM config beक्रमe enabling FW */
	अगर (sst_drv_ctx->ops->post_करोwnload)
		sst_drv_ctx->ops->post_करोwnload(sst_drv_ctx);

	/* bring sst out of reset */
	ret_val = sst_drv_ctx->ops->start(sst_drv_ctx);
	अगर (ret_val)
		जाओ restore;

	ret_val = sst_रुको_समयout(sst_drv_ctx, block);
	अगर (ret_val) अणु
		dev_err(sst_drv_ctx->dev, "fw download failed %d\n" , ret_val);
		/* FW करोwnload failed due to समयout */
		ret_val = -EBUSY;

	पूर्ण


restore:
	/* Re-enable Deeper C-states beyond C6 */
	cpu_latency_qos_update_request(sst_drv_ctx->qos, PM_QOS_DEFAULT_VALUE);
	sst_मुक्त_block(sst_drv_ctx, block);
	dev_dbg(sst_drv_ctx->dev, "fw load successful!!!\n");

	अगर (sst_drv_ctx->ops->restore_dsp_context)
		sst_drv_ctx->ops->restore_dsp_context();
	sst_drv_ctx->sst_state = SST_FW_RUNNING;
	वापस ret_val;
पूर्ण

