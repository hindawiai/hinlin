<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
//

#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश "core.h"
#समावेश "registers.h"

/* FW load (200ms) plus operational delays */
#घोषणा FW_READY_TIMEOUT_MS	250

#घोषणा FW_SIGNATURE		"$SST"
#घोषणा FW_SIGNATURE_SIZE	4

काष्ठा catpt_fw_hdr अणु
	अक्षर signature[FW_SIGNATURE_SIZE];
	u32 file_size;
	u32 modules;
	u32 file_क्रमmat;
	u32 reserved[4];
पूर्ण __packed;

काष्ठा catpt_fw_mod_hdr अणु
	अक्षर signature[FW_SIGNATURE_SIZE];
	u32 mod_size;
	u32 blocks;
	u16 slot;
	u16 module_id;
	u32 entry_poपूर्णांक;
	u32 persistent_size;
	u32 scratch_size;
पूर्ण __packed;

क्रमागत catpt_ram_type अणु
	CATPT_RAM_TYPE_IRAM = 1,
	CATPT_RAM_TYPE_DRAM = 2,
	/* DRAM with module's initial state */
	CATPT_RAM_TYPE_INSTANCE = 3,
पूर्ण;

काष्ठा catpt_fw_block_hdr अणु
	u32 ram_type;
	u32 size;
	u32 ram_offset;
	u32 rsvd;
पूर्ण __packed;

व्योम catpt_sram_init(काष्ठा resource *sram, u32 start, u32 size)
अणु
	sram->start = start;
	sram->end = start + size - 1;
पूर्ण

व्योम catpt_sram_मुक्त(काष्ठा resource *sram)
अणु
	काष्ठा resource *res, *save;

	क्रम (res = sram->child; res;) अणु
		save = res->sibling;
		release_resource(res);
		kमुक्त(res);
		res = save;
	पूर्ण
पूर्ण

काष्ठा resource *
catpt_request_region(काष्ठा resource *root, resource_माप_प्रकार size)
अणु
	काष्ठा resource *res = root->child;
	resource_माप_प्रकार addr = root->start;

	क्रम (;;) अणु
		अगर (res->start - addr >= size)
			अवरोध;
		addr = res->end + 1;
		res = res->sibling;
		अगर (!res)
			वापस शून्य;
	पूर्ण

	वापस __request_region(root, addr, size, शून्य, 0);
पूर्ण

पूर्णांक catpt_store_streams_context(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan)
अणु
	काष्ठा catpt_stream_runसमय *stream;

	list_क्रम_each_entry(stream, &cdev->stream_list, node) अणु
		u32 off, size;
		पूर्णांक ret;

		off = stream->persistent->start;
		size = resource_size(stream->persistent);
		dev_dbg(cdev->dev, "storing stream %d ctx: off 0x%08x size %d\n",
			stream->info.stream_hw_id, off, size);

		ret = catpt_dma_स_नकल_fromdsp(cdev, chan,
					       cdev->dxbuf_paddr + off,
					       cdev->lpe_base + off,
					       ALIGN(size, 4));
		अगर (ret) अणु
			dev_err(cdev->dev, "memcpy fromdsp failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक catpt_store_module_states(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cdev->modules); i++) अणु
		काष्ठा catpt_module_type *type;
		u32 off;
		पूर्णांक ret;

		type = &cdev->modules[i];
		अगर (!type->loaded || !type->state_size)
			जारी;

		off = type->state_offset;
		dev_dbg(cdev->dev, "storing mod %d state: off 0x%08x size %d\n",
			i, off, type->state_size);

		ret = catpt_dma_स_नकल_fromdsp(cdev, chan,
					       cdev->dxbuf_paddr + off,
					       cdev->lpe_base + off,
					       ALIGN(type->state_size, 4));
		अगर (ret) अणु
			dev_err(cdev->dev, "memcpy fromdsp failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक catpt_store_memdumps(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cdev->dx_ctx.num_meminfo; i++) अणु
		काष्ठा catpt_save_meminfo *info;
		u32 off;
		पूर्णांक ret;

		info = &cdev->dx_ctx.meminfo[i];
		अगर (info->source != CATPT_DX_TYPE_MEMORY_DUMP)
			जारी;

		off = catpt_to_host_offset(info->offset);
		अगर (off < cdev->dram.start || off > cdev->dram.end)
			जारी;

		dev_dbg(cdev->dev, "storing memdump: off 0x%08x size %d\n",
			off, info->size);

		ret = catpt_dma_स_नकल_fromdsp(cdev, chan,
					       cdev->dxbuf_paddr + off,
					       cdev->lpe_base + off,
					       ALIGN(info->size, 4));
		अगर (ret) अणु
			dev_err(cdev->dev, "memcpy fromdsp failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
catpt_restore_streams_context(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan)
अणु
	काष्ठा catpt_stream_runसमय *stream;

	list_क्रम_each_entry(stream, &cdev->stream_list, node) अणु
		u32 off, size;
		पूर्णांक ret;

		off = stream->persistent->start;
		size = resource_size(stream->persistent);
		dev_dbg(cdev->dev, "restoring stream %d ctx: off 0x%08x size %d\n",
			stream->info.stream_hw_id, off, size);

		ret = catpt_dma_स_नकल_todsp(cdev, chan,
					     cdev->lpe_base + off,
					     cdev->dxbuf_paddr + off,
					     ALIGN(size, 4));
		अगर (ret) अणु
			dev_err(cdev->dev, "memcpy fromdsp failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक catpt_restore_memdumps(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cdev->dx_ctx.num_meminfo; i++) अणु
		काष्ठा catpt_save_meminfo *info;
		u32 off;
		पूर्णांक ret;

		info = &cdev->dx_ctx.meminfo[i];
		अगर (info->source != CATPT_DX_TYPE_MEMORY_DUMP)
			जारी;

		off = catpt_to_host_offset(info->offset);
		अगर (off < cdev->dram.start || off > cdev->dram.end)
			जारी;

		dev_dbg(cdev->dev, "restoring memdump: off 0x%08x size %d\n",
			off, info->size);

		ret = catpt_dma_स_नकल_todsp(cdev, chan,
					     cdev->lpe_base + off,
					     cdev->dxbuf_paddr + off,
					     ALIGN(info->size, 4));
		अगर (ret) अणु
			dev_err(cdev->dev, "restore block failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक catpt_restore_fwimage(काष्ठा catpt_dev *cdev,
				 काष्ठा dma_chan *chan, dma_addr_t paddr,
				 काष्ठा catpt_fw_block_hdr *blk)
अणु
	काष्ठा resource r1, r2, common;
	पूर्णांक i;

	prपूर्णांक_hex_dump_debug(__func__, DUMP_PREFIX_OFFSET, 8, 4,
			     blk, माप(*blk), false);

	r1.start = cdev->dram.start + blk->ram_offset;
	r1.end = r1.start + blk->size - 1;
	/* advance to data area */
	paddr += माप(*blk);

	क्रम (i = 0; i < cdev->dx_ctx.num_meminfo; i++) अणु
		काष्ठा catpt_save_meminfo *info;
		u32 off;
		पूर्णांक ret;

		info = &cdev->dx_ctx.meminfo[i];

		अगर (info->source != CATPT_DX_TYPE_FW_IMAGE)
			जारी;

		off = catpt_to_host_offset(info->offset);
		अगर (off < cdev->dram.start || off > cdev->dram.end)
			जारी;

		r2.start = off;
		r2.end = r2.start + info->size - 1;

		अगर (!resource_पूर्णांकersection(&r2, &r1, &common))
			जारी;
		/* calculate start offset of common data area */
		off = common.start - r1.start;

		dev_dbg(cdev->dev, "restoring fwimage: %pr\n", &common);

		ret = catpt_dma_स_नकल_todsp(cdev, chan, common.start,
					     paddr + off,
					     resource_size(&common));
		अगर (ret) अणु
			dev_err(cdev->dev, "memcpy todsp failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक catpt_load_block(काष्ठा catpt_dev *cdev,
			    काष्ठा dma_chan *chan, dma_addr_t paddr,
			    काष्ठा catpt_fw_block_hdr *blk, bool alloc)
अणु
	काष्ठा resource *sram, *res;
	dma_addr_t dst_addr;
	पूर्णांक ret;

	prपूर्णांक_hex_dump_debug(__func__, DUMP_PREFIX_OFFSET, 8, 4,
			     blk, माप(*blk), false);

	चयन (blk->ram_type) अणु
	हाल CATPT_RAM_TYPE_IRAM:
		sram = &cdev->iram;
		अवरोध;
	शेष:
		sram = &cdev->dram;
		अवरोध;
	पूर्ण

	dst_addr = sram->start + blk->ram_offset;
	अगर (alloc) अणु
		res = __request_region(sram, dst_addr, blk->size, शून्य, 0);
		अगर (!res)
			वापस -EBUSY;
	पूर्ण

	/* advance to data area */
	paddr += माप(*blk);

	ret = catpt_dma_स_नकल_todsp(cdev, chan, dst_addr, paddr, blk->size);
	अगर (ret) अणु
		dev_err(cdev->dev, "memcpy error: %d\n", ret);
		__release_region(sram, dst_addr, blk->size);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक catpt_restore_basefw(काष्ठा catpt_dev *cdev,
				काष्ठा dma_chan *chan, dma_addr_t paddr,
				काष्ठा catpt_fw_mod_hdr *basefw)
अणु
	u32 offset = माप(*basefw);
	पूर्णांक ret, i;

	prपूर्णांक_hex_dump_debug(__func__, DUMP_PREFIX_OFFSET, 8, 4,
			     basefw, माप(*basefw), false);

	/* restore basefw image */
	क्रम (i = 0; i < basefw->blocks; i++) अणु
		काष्ठा catpt_fw_block_hdr *blk;

		blk = (काष्ठा catpt_fw_block_hdr *)((u8 *)basefw + offset);

		चयन (blk->ram_type) अणु
		हाल CATPT_RAM_TYPE_IRAM:
			ret = catpt_load_block(cdev, chan, paddr + offset,
					       blk, false);
			अवरोध;
		शेष:
			ret = catpt_restore_fwimage(cdev, chan, paddr + offset,
						    blk);
			अवरोध;
		पूर्ण

		अगर (ret) अणु
			dev_err(cdev->dev, "restore block failed: %d\n", ret);
			वापस ret;
		पूर्ण

		offset += माप(*blk) + blk->size;
	पूर्ण

	/* then proceed with memory dumps */
	ret = catpt_restore_memdumps(cdev, chan);
	अगर (ret)
		dev_err(cdev->dev, "restore memdumps failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक catpt_restore_module(काष्ठा catpt_dev *cdev,
				काष्ठा dma_chan *chan, dma_addr_t paddr,
				काष्ठा catpt_fw_mod_hdr *mod)
अणु
	u32 offset = माप(*mod);
	पूर्णांक i;

	prपूर्णांक_hex_dump_debug(__func__, DUMP_PREFIX_OFFSET, 8, 4,
			     mod, माप(*mod), false);

	क्रम (i = 0; i < mod->blocks; i++) अणु
		काष्ठा catpt_fw_block_hdr *blk;
		पूर्णांक ret;

		blk = (काष्ठा catpt_fw_block_hdr *)((u8 *)mod + offset);

		चयन (blk->ram_type) अणु
		हाल CATPT_RAM_TYPE_INSTANCE:
			/* restore module state */
			ret = catpt_dma_स_नकल_todsp(cdev, chan,
					cdev->lpe_base + blk->ram_offset,
					cdev->dxbuf_paddr + blk->ram_offset,
					ALIGN(blk->size, 4));
			अवरोध;
		शेष:
			ret = catpt_load_block(cdev, chan, paddr + offset,
					       blk, false);
			अवरोध;
		पूर्ण

		अगर (ret) अणु
			dev_err(cdev->dev, "restore block failed: %d\n", ret);
			वापस ret;
		पूर्ण

		offset += माप(*blk) + blk->size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक catpt_load_module(काष्ठा catpt_dev *cdev,
			     काष्ठा dma_chan *chan, dma_addr_t paddr,
			     काष्ठा catpt_fw_mod_hdr *mod)
अणु
	काष्ठा catpt_module_type *type;
	u32 offset = माप(*mod);
	पूर्णांक i;

	prपूर्णांक_hex_dump_debug(__func__, DUMP_PREFIX_OFFSET, 8, 4,
			     mod, माप(*mod), false);

	type = &cdev->modules[mod->module_id];

	क्रम (i = 0; i < mod->blocks; i++) अणु
		काष्ठा catpt_fw_block_hdr *blk;
		पूर्णांक ret;

		blk = (काष्ठा catpt_fw_block_hdr *)((u8 *)mod + offset);

		ret = catpt_load_block(cdev, chan, paddr + offset, blk, true);
		अगर (ret) अणु
			dev_err(cdev->dev, "load block failed: %d\n", ret);
			वापस ret;
		पूर्ण

		/*
		 * Save state winकरोw coordinates - these will be
		 * used to capture module state on D0 निकास.
		 */
		अगर (blk->ram_type == CATPT_RAM_TYPE_INSTANCE) अणु
			type->state_offset = blk->ram_offset;
			type->state_size = blk->size;
		पूर्ण

		offset += माप(*blk) + blk->size;
	पूर्ण

	/* init module type अटल info */
	type->loaded = true;
	/* DSP expects address from module header substracted by 4 */
	type->entry_poपूर्णांक = mod->entry_poपूर्णांक - 4;
	type->persistent_size = mod->persistent_size;
	type->scratch_size = mod->scratch_size;

	वापस 0;
पूर्ण

अटल पूर्णांक catpt_restore_firmware(काष्ठा catpt_dev *cdev,
				  काष्ठा dma_chan *chan, dma_addr_t paddr,
				  काष्ठा catpt_fw_hdr *fw)
अणु
	u32 offset = माप(*fw);
	पूर्णांक i;

	prपूर्णांक_hex_dump_debug(__func__, DUMP_PREFIX_OFFSET, 8, 4,
			     fw, माप(*fw), false);

	क्रम (i = 0; i < fw->modules; i++) अणु
		काष्ठा catpt_fw_mod_hdr *mod;
		पूर्णांक ret;

		mod = (काष्ठा catpt_fw_mod_hdr *)((u8 *)fw + offset);
		अगर (म_भेदन(fw->signature, mod->signature,
			    FW_SIGNATURE_SIZE)) अणु
			dev_err(cdev->dev, "module signature mismatch\n");
			वापस -EINVAL;
		पूर्ण

		अगर (mod->module_id > CATPT_MODID_LAST)
			वापस -EINVAL;

		चयन (mod->module_id) अणु
		हाल CATPT_MODID_BASE_FW:
			ret = catpt_restore_basefw(cdev, chan, paddr + offset,
						   mod);
			अवरोध;
		शेष:
			ret = catpt_restore_module(cdev, chan, paddr + offset,
						   mod);
			अवरोध;
		पूर्ण

		अगर (ret) अणु
			dev_err(cdev->dev, "restore module failed: %d\n", ret);
			वापस ret;
		पूर्ण

		offset += माप(*mod) + mod->mod_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक catpt_load_firmware(काष्ठा catpt_dev *cdev,
			       काष्ठा dma_chan *chan, dma_addr_t paddr,
			       काष्ठा catpt_fw_hdr *fw)
अणु
	u32 offset = माप(*fw);
	पूर्णांक i;

	prपूर्णांक_hex_dump_debug(__func__, DUMP_PREFIX_OFFSET, 8, 4,
			     fw, माप(*fw), false);

	क्रम (i = 0; i < fw->modules; i++) अणु
		काष्ठा catpt_fw_mod_hdr *mod;
		पूर्णांक ret;

		mod = (काष्ठा catpt_fw_mod_hdr *)((u8 *)fw + offset);
		अगर (म_भेदन(fw->signature, mod->signature,
			    FW_SIGNATURE_SIZE)) अणु
			dev_err(cdev->dev, "module signature mismatch\n");
			वापस -EINVAL;
		पूर्ण

		अगर (mod->module_id > CATPT_MODID_LAST)
			वापस -EINVAL;

		ret = catpt_load_module(cdev, chan, paddr + offset, mod);
		अगर (ret) अणु
			dev_err(cdev->dev, "load module failed: %d\n", ret);
			वापस ret;
		पूर्ण

		offset += माप(*mod) + mod->mod_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक catpt_load_image(काष्ठा catpt_dev *cdev, काष्ठा dma_chan *chan,
			    स्थिर अक्षर *name, स्थिर अक्षर *signature,
			    bool restore)
अणु
	काष्ठा catpt_fw_hdr *fw;
	काष्ठा firmware *img;
	dma_addr_t paddr;
	व्योम *vaddr;
	पूर्णांक ret;

	ret = request_firmware((स्थिर काष्ठा firmware **)&img, name, cdev->dev);
	अगर (ret)
		वापस ret;

	fw = (काष्ठा catpt_fw_hdr *)img->data;
	अगर (म_भेदन(fw->signature, signature, FW_SIGNATURE_SIZE)) अणु
		dev_err(cdev->dev, "firmware signature mismatch\n");
		ret = -EINVAL;
		जाओ release_fw;
	पूर्ण

	vaddr = dma_alloc_coherent(cdev->dev, img->size, &paddr, GFP_KERNEL);
	अगर (!vaddr) अणु
		ret = -ENOMEM;
		जाओ release_fw;
	पूर्ण

	स_नकल(vaddr, img->data, img->size);
	fw = (काष्ठा catpt_fw_hdr *)vaddr;
	अगर (restore)
		ret = catpt_restore_firmware(cdev, chan, paddr, fw);
	अन्यथा
		ret = catpt_load_firmware(cdev, chan, paddr, fw);

	dma_मुक्त_coherent(cdev->dev, img->size, vaddr, paddr);
release_fw:
	release_firmware(img);
	वापस ret;
पूर्ण

अटल पूर्णांक catpt_load_images(काष्ठा catpt_dev *cdev, bool restore)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		"intel/IntcSST1.bin",
		"intel/IntcSST2.bin",
	पूर्ण;
	काष्ठा dma_chan *chan;
	पूर्णांक ret;

	chan = catpt_dma_request_config_chan(cdev);
	अगर (IS_ERR(chan))
		वापस PTR_ERR(chan);

	ret = catpt_load_image(cdev, chan, names[cdev->spec->core_id - 1],
			       FW_SIGNATURE, restore);
	अगर (ret)
		जाओ release_dma_chan;

	अगर (!restore)
		जाओ release_dma_chan;
	ret = catpt_restore_streams_context(cdev, chan);
	अगर (ret)
		dev_err(cdev->dev, "restore streams ctx failed: %d\n", ret);
release_dma_chan:
	dma_release_channel(chan);
	वापस ret;
पूर्ण

पूर्णांक catpt_boot_firmware(काष्ठा catpt_dev *cdev, bool restore)
अणु
	पूर्णांक ret;

	catpt_dsp_stall(cdev, true);

	ret = catpt_load_images(cdev, restore);
	अगर (ret) अणु
		dev_err(cdev->dev, "load binaries failed: %d\n", ret);
		वापस ret;
	पूर्ण

	reinit_completion(&cdev->fw_पढ़ोy);
	catpt_dsp_stall(cdev, false);

	ret = रुको_क्रम_completion_समयout(&cdev->fw_पढ़ोy,
			msecs_to_jअगरfies(FW_READY_TIMEOUT_MS));
	अगर (!ret) अणु
		dev_err(cdev->dev, "firmware ready timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	/* update sram pg & घड़ी once करोne booting */
	catpt_dsp_update_srampge(cdev, &cdev->dram, cdev->spec->dram_mask);
	catpt_dsp_update_srampge(cdev, &cdev->iram, cdev->spec->iram_mask);

	वापस catpt_dsp_update_lpघड़ी(cdev);
पूर्ण

पूर्णांक catpt_first_boot_firmware(काष्ठा catpt_dev *cdev)
अणु
	काष्ठा resource *res;
	पूर्णांक ret;

	ret = catpt_boot_firmware(cdev, false);
	अगर (ret) अणु
		dev_err(cdev->dev, "basefw boot failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* restrict FW Core dump area */
	__request_region(&cdev->dram, 0, 0x200, शून्य, 0);
	/* restrict entire area following BASE_FW - highest offset in DRAM */
	क्रम (res = cdev->dram.child; res->sibling; res = res->sibling)
		;
	__request_region(&cdev->dram, res->end + 1,
			 cdev->dram.end - res->end, शून्य, 0);

	ret = catpt_ipc_get_mixer_stream_info(cdev, &cdev->mixer);
	अगर (ret)
		वापस CATPT_IPC_ERROR(ret);

	ret = catpt_arm_stream_ढाँचाs(cdev);
	अगर (ret) अणु
		dev_err(cdev->dev, "arm templates failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* update dram pg क्रम scratch and restricted regions */
	catpt_dsp_update_srampge(cdev, &cdev->dram, cdev->spec->dram_mask);

	वापस 0;
पूर्ण
