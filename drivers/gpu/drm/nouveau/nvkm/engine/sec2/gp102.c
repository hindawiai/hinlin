<शैली गुरु>
/*
 * Copyright (c) 2017, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#समावेश "priv.h"

#समावेश <core/memory.h>
#समावेश <subdev/acr.h>
#समावेश <subdev/समयr.h>

#समावेश <nvfw/flcn.h>
#समावेश <nvfw/sec2.h>

पूर्णांक
gp102_sec2_nofw(काष्ठा nvkm_sec2 *sec2, पूर्णांक ver,
		स्थिर काष्ठा nvkm_sec2_fwअगर *fwअगर)
अणु
	nvkm_warn(&sec2->engine.subdev, "firmware unavailable\n");
	वापस 0;
पूर्ण

अटल पूर्णांक
gp102_sec2_acr_bootstrap_falcon_callback(व्योम *priv, काष्ठा nvfw_falcon_msg *hdr)
अणु
	काष्ठा nv_sec2_acr_bootstrap_falcon_msg *msg =
		container_of(hdr, typeof(*msg), msg.hdr);
	काष्ठा nvkm_subdev *subdev = priv;
	स्थिर अक्षर *name = nvkm_acr_lsf_id(msg->falcon_id);

	अगर (msg->error_code) अणु
		nvkm_error(subdev, "ACR_BOOTSTRAP_FALCON failed for "
				   "falcon %d [%s]: %08x\n",
			   msg->falcon_id, name, msg->error_code);
		वापस -EINVAL;
	पूर्ण

	nvkm_debug(subdev, "%s booted\n", name);
	वापस 0;
पूर्ण

अटल पूर्णांक
gp102_sec2_acr_bootstrap_falcon(काष्ठा nvkm_falcon *falcon,
			        क्रमागत nvkm_acr_lsf_id id)
अणु
	काष्ठा nvkm_sec2 *sec2 = container_of(falcon, typeof(*sec2), falcon);
	काष्ठा nv_sec2_acr_bootstrap_falcon_cmd cmd = अणु
		.cmd.hdr.unit_id = sec2->func->unit_acr,
		.cmd.hdr.size = माप(cmd),
		.cmd.cmd_type = NV_SEC2_ACR_CMD_BOOTSTRAP_FALCON,
		.flags = NV_SEC2_ACR_BOOTSTRAP_FALCON_FLAGS_RESET_YES,
		.falcon_id = id,
	पूर्ण;

	वापस nvkm_falcon_cmdq_send(sec2->cmdq, &cmd.cmd.hdr,
				     gp102_sec2_acr_bootstrap_falcon_callback,
				     &sec2->engine.subdev,
				     msecs_to_jअगरfies(1000));
पूर्ण

अटल पूर्णांक
gp102_sec2_acr_boot(काष्ठा nvkm_falcon *falcon)
अणु
	काष्ठा nv_sec2_args args = अणुपूर्ण;
	nvkm_falcon_load_dmem(falcon, &args,
			      falcon->func->emem_addr, माप(args), 0);
	nvkm_falcon_start(falcon);
	वापस 0;
पूर्ण

अटल व्योम
gp102_sec2_acr_bld_patch(काष्ठा nvkm_acr *acr, u32 bld, s64 adjust)
अणु
	काष्ठा loader_config_v1 hdr;
	nvkm_robj(acr->wpr, bld, &hdr, माप(hdr));
	hdr.code_dma_base = hdr.code_dma_base + adjust;
	hdr.data_dma_base = hdr.data_dma_base + adjust;
	hdr.overlay_dma_base = hdr.overlay_dma_base + adjust;
	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));
	loader_config_v1_dump(&acr->subdev, &hdr);
पूर्ण

अटल व्योम
gp102_sec2_acr_bld_ग_लिखो(काष्ठा nvkm_acr *acr, u32 bld,
			 काष्ठा nvkm_acr_lsfw *lsfw)
अणु
	स्थिर काष्ठा loader_config_v1 hdr = अणु
		.dma_idx = FALCON_SEC2_DMAIDX_UCODE,
		.code_dma_base = lsfw->offset.img + lsfw->app_start_offset,
		.code_माप_प्रकारotal = lsfw->app_size,
		.code_माप_प्रकारo_load = lsfw->app_resident_code_size,
		.code_entry_poपूर्णांक = lsfw->app_imem_entry,
		.data_dma_base = lsfw->offset.img + lsfw->app_start_offset +
				 lsfw->app_resident_data_offset,
		.data_size = lsfw->app_resident_data_size,
		.overlay_dma_base = lsfw->offset.img + lsfw->app_start_offset,
		.argc = 1,
		.argv = lsfw->falcon->func->emem_addr,
	पूर्ण;

	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));
पूर्ण

अटल स्थिर काष्ठा nvkm_acr_lsf_func
gp102_sec2_acr_0 = अणु
	.bld_size = माप(काष्ठा loader_config_v1),
	.bld_ग_लिखो = gp102_sec2_acr_bld_ग_लिखो,
	.bld_patch = gp102_sec2_acr_bld_patch,
	.boot = gp102_sec2_acr_boot,
	.bootstrap_falcons = BIT_ULL(NVKM_ACR_LSF_FECS) |
			     BIT_ULL(NVKM_ACR_LSF_GPCCS) |
			     BIT_ULL(NVKM_ACR_LSF_SEC2),
	.bootstrap_falcon = gp102_sec2_acr_bootstrap_falcon,
पूर्ण;

पूर्णांक
gp102_sec2_iniपंचांगsg(काष्ठा nvkm_sec2 *sec2)
अणु
	काष्ठा nv_sec2_init_msg msg;
	पूर्णांक ret, i;

	ret = nvkm_falcon_msgq_recv_iniपंचांगsg(sec2->msgq, &msg, माप(msg));
	अगर (ret)
		वापस ret;

	अगर (msg.hdr.unit_id != NV_SEC2_UNIT_INIT ||
	    msg.msg_type != NV_SEC2_INIT_MSG_INIT)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(msg.queue_info); i++) अणु
		अगर (msg.queue_info[i].id == NV_SEC2_INIT_MSG_QUEUE_ID_MSGQ) अणु
			nvkm_falcon_msgq_init(sec2->msgq,
					      msg.queue_info[i].index,
					      msg.queue_info[i].offset,
					      msg.queue_info[i].size);
		पूर्ण अन्यथा अणु
			nvkm_falcon_cmdq_init(sec2->cmdq,
					      msg.queue_info[i].index,
					      msg.queue_info[i].offset,
					      msg.queue_info[i].size);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम
gp102_sec2_पूर्णांकr(काष्ठा nvkm_sec2 *sec2)
अणु
	काष्ठा nvkm_subdev *subdev = &sec2->engine.subdev;
	काष्ठा nvkm_falcon *falcon = &sec2->falcon;
	u32 disp = nvkm_falcon_rd32(falcon, 0x01c);
	u32 पूर्णांकr = nvkm_falcon_rd32(falcon, 0x008) & disp & ~(disp >> 16);

	अगर (पूर्णांकr & 0x00000040) अणु
		schedule_work(&sec2->work);
		nvkm_falcon_wr32(falcon, 0x004, 0x00000040);
		पूर्णांकr &= ~0x00000040;
	पूर्ण

	अगर (पूर्णांकr) अणु
		nvkm_error(subdev, "unhandled intr %08x\n", पूर्णांकr);
		nvkm_falcon_wr32(falcon, 0x004, पूर्णांकr);
	पूर्ण
पूर्ण

पूर्णांक
gp102_sec2_flcn_enable(काष्ठा nvkm_falcon *falcon)
अणु
	nvkm_falcon_mask(falcon, 0x3c0, 0x00000001, 0x00000001);
	udelay(10);
	nvkm_falcon_mask(falcon, 0x3c0, 0x00000001, 0x00000000);
	वापस nvkm_falcon_v1_enable(falcon);
पूर्ण

व्योम
gp102_sec2_flcn_bind_context(काष्ठा nvkm_falcon *falcon,
			     काष्ठा nvkm_memory *ctx)
अणु
	काष्ठा nvkm_device *device = falcon->owner->device;

	nvkm_falcon_v1_bind_context(falcon, ctx);
	अगर (!ctx)
		वापस;

	/* Not sure अगर this is a WAR क्रम a HW issue, or some additional
	 * programming sequence that's needed to properly complete the
	 * context चयन we trigger above.
	 *
	 * Fixes unreliability of booting the SEC2 RTOS on Quadro P620,
	 * particularly when resuming from suspend.
	 *
	 * Also हटाओs the need क्रम an odd workaround where we needed
	 * to program SEC2's FALCON_CPUCTL_ALIAS_STARTCPU twice beक्रमe
	 * the SEC2 RTOS would begin executing.
	 */
	nvkm_msec(device, 10,
		u32 irqstat = nvkm_falcon_rd32(falcon, 0x008);
		u32 flcn0dc = nvkm_falcon_rd32(falcon, 0x0dc);
		अगर ((irqstat & 0x00000008) &&
		    (flcn0dc & 0x00007000) == 0x00005000)
			अवरोध;
	);

	nvkm_falcon_mask(falcon, 0x004, 0x00000008, 0x00000008);
	nvkm_falcon_mask(falcon, 0x058, 0x00000002, 0x00000002);

	nvkm_msec(device, 10,
		u32 flcn0dc = nvkm_falcon_rd32(falcon, 0x0dc);
		अगर ((flcn0dc & 0x00007000) == 0x00000000)
			अवरोध;
	);
पूर्ण

अटल स्थिर काष्ठा nvkm_falcon_func
gp102_sec2_flcn = अणु
	.debug = 0x408,
	.fbअगर = 0x600,
	.load_imem = nvkm_falcon_v1_load_imem,
	.load_dmem = nvkm_falcon_v1_load_dmem,
	.पढ़ो_dmem = nvkm_falcon_v1_पढ़ो_dmem,
	.emem_addr = 0x01000000,
	.bind_context = gp102_sec2_flcn_bind_context,
	.रुको_क्रम_halt = nvkm_falcon_v1_रुको_क्रम_halt,
	.clear_पूर्णांकerrupt = nvkm_falcon_v1_clear_पूर्णांकerrupt,
	.set_start_addr = nvkm_falcon_v1_set_start_addr,
	.start = nvkm_falcon_v1_start,
	.enable = gp102_sec2_flcn_enable,
	.disable = nvkm_falcon_v1_disable,
	.cmdq = अणु 0xa00, 0xa04, 8 पूर्ण,
	.msgq = अणु 0xa30, 0xa34, 8 पूर्ण,
पूर्ण;

स्थिर काष्ठा nvkm_sec2_func
gp102_sec2 = अणु
	.flcn = &gp102_sec2_flcn,
	.unit_acr = NV_SEC2_UNIT_ACR,
	.पूर्णांकr = gp102_sec2_पूर्णांकr,
	.iniपंचांगsg = gp102_sec2_iniपंचांगsg,
पूर्ण;

MODULE_FIRMWARE("nvidia/gp102/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/gp102/sec2/image.bin");
MODULE_FIRMWARE("nvidia/gp102/sec2/sig.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/image.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/sig.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/image.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/sig.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/desc.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/image.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/sig.bin");

अटल व्योम
gp102_sec2_acr_bld_patch_1(काष्ठा nvkm_acr *acr, u32 bld, s64 adjust)
अणु
	काष्ठा flcn_bl_dmem_desc_v2 hdr;
	nvkm_robj(acr->wpr, bld, &hdr, माप(hdr));
	hdr.code_dma_base = hdr.code_dma_base + adjust;
	hdr.data_dma_base = hdr.data_dma_base + adjust;
	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));
	flcn_bl_dmem_desc_v2_dump(&acr->subdev, &hdr);
पूर्ण

अटल व्योम
gp102_sec2_acr_bld_ग_लिखो_1(काष्ठा nvkm_acr *acr, u32 bld,
			   काष्ठा nvkm_acr_lsfw *lsfw)
अणु
	स्थिर काष्ठा flcn_bl_dmem_desc_v2 hdr = अणु
		.ctx_dma = FALCON_SEC2_DMAIDX_UCODE,
		.code_dma_base = lsfw->offset.img + lsfw->app_start_offset,
		.non_sec_code_off = lsfw->app_resident_code_offset,
		.non_sec_code_size = lsfw->app_resident_code_size,
		.code_entry_poपूर्णांक = lsfw->app_imem_entry,
		.data_dma_base = lsfw->offset.img + lsfw->app_start_offset +
				 lsfw->app_resident_data_offset,
		.data_size = lsfw->app_resident_data_size,
		.argc = 1,
		.argv = lsfw->falcon->func->emem_addr,
	पूर्ण;

	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));
पूर्ण

स्थिर काष्ठा nvkm_acr_lsf_func
gp102_sec2_acr_1 = अणु
	.bld_size = माप(काष्ठा flcn_bl_dmem_desc_v2),
	.bld_ग_लिखो = gp102_sec2_acr_bld_ग_लिखो_1,
	.bld_patch = gp102_sec2_acr_bld_patch_1,
	.boot = gp102_sec2_acr_boot,
	.bootstrap_falcons = BIT_ULL(NVKM_ACR_LSF_FECS) |
			     BIT_ULL(NVKM_ACR_LSF_GPCCS) |
			     BIT_ULL(NVKM_ACR_LSF_SEC2),
	.bootstrap_falcon = gp102_sec2_acr_bootstrap_falcon,
पूर्ण;

पूर्णांक
gp102_sec2_load(काष्ठा nvkm_sec2 *sec2, पूर्णांक ver,
		स्थिर काष्ठा nvkm_sec2_fwअगर *fwअगर)
अणु
	वापस nvkm_acr_lsfw_load_sig_image_desc_v1(&sec2->engine.subdev,
						    &sec2->falcon,
						    NVKM_ACR_LSF_SEC2, "sec2/",
						    ver, fwअगर->acr);
पूर्ण

MODULE_FIRMWARE("nvidia/gp102/sec2/desc-1.bin");
MODULE_FIRMWARE("nvidia/gp102/sec2/image-1.bin");
MODULE_FIRMWARE("nvidia/gp102/sec2/sig-1.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/desc-1.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/image-1.bin");
MODULE_FIRMWARE("nvidia/gp104/sec2/sig-1.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/desc-1.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/image-1.bin");
MODULE_FIRMWARE("nvidia/gp106/sec2/sig-1.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/desc-1.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/image-1.bin");
MODULE_FIRMWARE("nvidia/gp107/sec2/sig-1.bin");

अटल स्थिर काष्ठा nvkm_sec2_fwअगर
gp102_sec2_fwअगर[] = अणु
	अणु  1, gp102_sec2_load, &gp102_sec2, &gp102_sec2_acr_1 पूर्ण,
	अणु  0, gp102_sec2_load, &gp102_sec2, &gp102_sec2_acr_0 पूर्ण,
	अणु -1, gp102_sec2_nofw, &gp102_sec2 पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp102_sec2_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_sec2 **psec2)
अणु
	वापस nvkm_sec2_new_(gp102_sec2_fwअगर, device, type, inst, 0, psec2);
पूर्ण
