<शैली गुरु>
/*
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
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

#समावेश <nvfw/flcn.h>
#समावेश <nvfw/pmu.h>

अटल पूर्णांक
gm20b_pmu_acr_bootstrap_falcon_cb(व्योम *priv, काष्ठा nvfw_falcon_msg *hdr)
अणु
	काष्ठा nv_pmu_acr_bootstrap_falcon_msg *msg =
		container_of(hdr, typeof(*msg), msg.hdr);
	वापस msg->falcon_id;
पूर्ण

पूर्णांक
gm20b_pmu_acr_bootstrap_falcon(काष्ठा nvkm_falcon *falcon,
			       क्रमागत nvkm_acr_lsf_id id)
अणु
	काष्ठा nvkm_pmu *pmu = container_of(falcon, typeof(*pmu), falcon);
	काष्ठा nv_pmu_acr_bootstrap_falcon_cmd cmd = अणु
		.cmd.hdr.unit_id = NV_PMU_UNIT_ACR,
		.cmd.hdr.size = माप(cmd),
		.cmd.cmd_type = NV_PMU_ACR_CMD_BOOTSTRAP_FALCON,
		.flags = NV_PMU_ACR_BOOTSTRAP_FALCON_FLAGS_RESET_YES,
		.falcon_id = id,
	पूर्ण;
	पूर्णांक ret;

	ret = nvkm_falcon_cmdq_send(pmu->hpq, &cmd.cmd.hdr,
				    gm20b_pmu_acr_bootstrap_falcon_cb,
				    &pmu->subdev, msecs_to_jअगरfies(1000));
	अगर (ret >= 0) अणु
		अगर (ret != cmd.falcon_id)
			ret = -EIO;
		अन्यथा
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
gm20b_pmu_acr_boot(काष्ठा nvkm_falcon *falcon)
अणु
	काष्ठा nv_pmu_args args = अणु .secure_mode = true पूर्ण;
	स्थिर u32 addr_args = falcon->data.limit - माप(काष्ठा nv_pmu_args);
	nvkm_falcon_load_dmem(falcon, &args, addr_args, माप(args), 0);
	nvkm_falcon_start(falcon);
	वापस 0;
पूर्ण

व्योम
gm20b_pmu_acr_bld_patch(काष्ठा nvkm_acr *acr, u32 bld, s64 adjust)
अणु
	काष्ठा loader_config hdr;
	u64 addr;

	nvkm_robj(acr->wpr, bld, &hdr, माप(hdr));
	addr = ((u64)hdr.code_dma_base1 << 40 | hdr.code_dma_base << 8);
	hdr.code_dma_base  = lower_32_bits((addr + adjust) >> 8);
	hdr.code_dma_base1 = upper_32_bits((addr + adjust) >> 8);
	addr = ((u64)hdr.data_dma_base1 << 40 | hdr.data_dma_base << 8);
	hdr.data_dma_base  = lower_32_bits((addr + adjust) >> 8);
	hdr.data_dma_base1 = upper_32_bits((addr + adjust) >> 8);
	addr = ((u64)hdr.overlay_dma_base1 << 40 | hdr.overlay_dma_base << 8);
	hdr.overlay_dma_base  = lower_32_bits((addr + adjust) << 8);
	hdr.overlay_dma_base1 = upper_32_bits((addr + adjust) << 8);
	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));

	loader_config_dump(&acr->subdev, &hdr);
पूर्ण

व्योम
gm20b_pmu_acr_bld_ग_लिखो(काष्ठा nvkm_acr *acr, u32 bld,
			काष्ठा nvkm_acr_lsfw *lsfw)
अणु
	स्थिर u64 base = lsfw->offset.img + lsfw->app_start_offset;
	स्थिर u64 code = (base + lsfw->app_resident_code_offset) >> 8;
	स्थिर u64 data = (base + lsfw->app_resident_data_offset) >> 8;
	स्थिर काष्ठा loader_config hdr = अणु
		.dma_idx = FALCON_DMAIDX_UCODE,
		.code_dma_base = lower_32_bits(code),
		.code_माप_प्रकारotal = lsfw->app_size,
		.code_माप_प्रकारo_load = lsfw->app_resident_code_size,
		.code_entry_poपूर्णांक = lsfw->app_imem_entry,
		.data_dma_base = lower_32_bits(data),
		.data_size = lsfw->app_resident_data_size,
		.overlay_dma_base = lower_32_bits(code),
		.argc = 1,
		.argv = lsfw->falcon->data.limit - माप(काष्ठा nv_pmu_args),
		.code_dma_base1 = upper_32_bits(code),
		.data_dma_base1 = upper_32_bits(data),
		.overlay_dma_base1 = upper_32_bits(code),
	पूर्ण;

	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));
पूर्ण

अटल स्थिर काष्ठा nvkm_acr_lsf_func
gm20b_pmu_acr = अणु
	.flags = NVKM_ACR_LSF_DMACTL_REQ_CTX,
	.bld_size = माप(काष्ठा loader_config),
	.bld_ग_लिखो = gm20b_pmu_acr_bld_ग_लिखो,
	.bld_patch = gm20b_pmu_acr_bld_patch,
	.boot = gm20b_pmu_acr_boot,
	.bootstrap_falcons = BIT_ULL(NVKM_ACR_LSF_PMU) |
			     BIT_ULL(NVKM_ACR_LSF_FECS) |
			     BIT_ULL(NVKM_ACR_LSF_GPCCS),
	.bootstrap_falcon = gm20b_pmu_acr_bootstrap_falcon,
पूर्ण;

अटल पूर्णांक
gm20b_pmu_acr_init_wpr_callback(व्योम *priv, काष्ठा nvfw_falcon_msg *hdr)
अणु
	काष्ठा nv_pmu_acr_init_wpr_region_msg *msg =
		container_of(hdr, typeof(*msg), msg.hdr);
	काष्ठा nvkm_pmu *pmu = priv;
	काष्ठा nvkm_subdev *subdev = &pmu->subdev;

	अगर (msg->error_code) अणु
		nvkm_error(subdev, "ACR WPR init failure: %d\n",
			   msg->error_code);
		वापस -EINVAL;
	पूर्ण

	nvkm_debug(subdev, "ACR WPR init complete\n");
	complete_all(&pmu->wpr_पढ़ोy);
	वापस 0;
पूर्ण

अटल पूर्णांक
gm20b_pmu_acr_init_wpr(काष्ठा nvkm_pmu *pmu)
अणु
	काष्ठा nv_pmu_acr_init_wpr_region_cmd cmd = अणु
		.cmd.hdr.unit_id = NV_PMU_UNIT_ACR,
		.cmd.hdr.size = माप(cmd),
		.cmd.cmd_type = NV_PMU_ACR_CMD_INIT_WPR_REGION,
		.region_id = 1,
		.wpr_offset = 0,
	पूर्ण;

	वापस nvkm_falcon_cmdq_send(pmu->hpq, &cmd.cmd.hdr,
				     gm20b_pmu_acr_init_wpr_callback, pmu, 0);
पूर्ण

पूर्णांक
gm20b_pmu_iniपंचांगsg(काष्ठा nvkm_pmu *pmu)
अणु
	काष्ठा nv_pmu_init_msg msg;
	पूर्णांक ret;

	ret = nvkm_falcon_msgq_recv_iniपंचांगsg(pmu->msgq, &msg, माप(msg));
	अगर (ret)
		वापस ret;

	अगर (msg.hdr.unit_id != NV_PMU_UNIT_INIT ||
	    msg.msg_type != NV_PMU_INIT_MSG_INIT)
		वापस -EINVAL;

	nvkm_falcon_cmdq_init(pmu->hpq, msg.queue_info[0].index,
					msg.queue_info[0].offset,
					msg.queue_info[0].size);
	nvkm_falcon_cmdq_init(pmu->lpq, msg.queue_info[1].index,
					msg.queue_info[1].offset,
					msg.queue_info[1].size);
	nvkm_falcon_msgq_init(pmu->msgq, msg.queue_info[4].index,
					 msg.queue_info[4].offset,
					 msg.queue_info[4].size);
	वापस gm20b_pmu_acr_init_wpr(pmu);
पूर्ण

व्योम
gm20b_pmu_recv(काष्ठा nvkm_pmu *pmu)
अणु
	अगर (!pmu->iniपंचांगsg_received) अणु
		पूर्णांक ret = pmu->func->iniपंचांगsg(pmu);
		अगर (ret) अणु
			nvkm_error(&pmu->subdev,
				   "error parsing init message: %d\n", ret);
			वापस;
		पूर्ण

		pmu->iniपंचांगsg_received = true;
	पूर्ण

	nvkm_falcon_msgq_recv(pmu->msgq);
पूर्ण

अटल स्थिर काष्ठा nvkm_pmu_func
gm20b_pmu = अणु
	.flcn = &gt215_pmu_flcn,
	.enabled = gf100_pmu_enabled,
	.पूर्णांकr = gt215_pmu_पूर्णांकr,
	.recv = gm20b_pmu_recv,
	.iniपंचांगsg = gm20b_pmu_iniपंचांगsg,
पूर्ण;

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_210_SOC)
MODULE_FIRMWARE("nvidia/gm20b/pmu/desc.bin");
MODULE_FIRMWARE("nvidia/gm20b/pmu/image.bin");
MODULE_FIRMWARE("nvidia/gm20b/pmu/sig.bin");
#पूर्ण_अगर

पूर्णांक
gm20b_pmu_load(काष्ठा nvkm_pmu *pmu, पूर्णांक ver, स्थिर काष्ठा nvkm_pmu_fwअगर *fwअगर)
अणु
	वापस nvkm_acr_lsfw_load_sig_image_desc(&pmu->subdev, &pmu->falcon,
						 NVKM_ACR_LSF_PMU, "pmu/",
						 ver, fwअगर->acr);
पूर्ण

अटल स्थिर काष्ठा nvkm_pmu_fwअगर
gm20b_pmu_fwअगर[] = अणु
	अणु  0, gm20b_pmu_load, &gm20b_pmu, &gm20b_pmu_acr पूर्ण,
	अणु -1, gm200_pmu_nofw, &gm20b_pmu पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gm20b_pmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pmu **ppmu)
अणु
	वापस nvkm_pmu_new_(gm20b_pmu_fwअगर, device, type, inst, ppmu);
पूर्ण
