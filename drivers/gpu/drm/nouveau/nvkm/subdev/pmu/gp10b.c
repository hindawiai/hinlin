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

#समावेश <subdev/acr.h>

#समावेश <nvfw/flcn.h>
#समावेश <nvfw/pmu.h>

अटल पूर्णांक
gp10b_pmu_acr_bootstrap_multiple_falcons_cb(व्योम *priv,
					    काष्ठा nvfw_falcon_msg *hdr)
अणु
	काष्ठा nv_pmu_acr_bootstrap_multiple_falcons_msg *msg =
		container_of(hdr, typeof(*msg), msg.hdr);
	वापस msg->falcon_mask;
पूर्ण
अटल पूर्णांक
gp10b_pmu_acr_bootstrap_multiple_falcons(काष्ठा nvkm_falcon *falcon, u32 mask)
अणु
	काष्ठा nvkm_pmu *pmu = container_of(falcon, typeof(*pmu), falcon);
	काष्ठा nv_pmu_acr_bootstrap_multiple_falcons_cmd cmd = अणु
		.cmd.hdr.unit_id = NV_PMU_UNIT_ACR,
		.cmd.hdr.size = माप(cmd),
		.cmd.cmd_type = NV_PMU_ACR_CMD_BOOTSTRAP_MULTIPLE_FALCONS,
		.flags = NV_PMU_ACR_BOOTSTRAP_MULTIPLE_FALCONS_FLAGS_RESET_YES,
		.falcon_mask = mask,
		.wpr_lo = 0, /*XXX*/
		.wpr_hi = 0, /*XXX*/
	पूर्ण;
	पूर्णांक ret;

	ret = nvkm_falcon_cmdq_send(pmu->hpq, &cmd.cmd.hdr,
				    gp10b_pmu_acr_bootstrap_multiple_falcons_cb,
				    &pmu->subdev, msecs_to_jअगरfies(1000));
	अगर (ret >= 0) अणु
		अगर (ret != cmd.falcon_mask)
			ret = -EIO;
		अन्यथा
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_acr_lsf_func
gp10b_pmu_acr = अणु
	.flags = NVKM_ACR_LSF_DMACTL_REQ_CTX,
	.bld_size = माप(काष्ठा loader_config),
	.bld_ग_लिखो = gm20b_pmu_acr_bld_ग_लिखो,
	.bld_patch = gm20b_pmu_acr_bld_patch,
	.boot = gm20b_pmu_acr_boot,
	.bootstrap_falcons = BIT_ULL(NVKM_ACR_LSF_PMU) |
			     BIT_ULL(NVKM_ACR_LSF_FECS) |
			     BIT_ULL(NVKM_ACR_LSF_GPCCS),
	.bootstrap_falcon = gm20b_pmu_acr_bootstrap_falcon,
	.bootstrap_multiple_falcons = gp10b_pmu_acr_bootstrap_multiple_falcons,
पूर्ण;

अटल स्थिर काष्ठा nvkm_pmu_func
gp10b_pmu = अणु
	.flcn = &gt215_pmu_flcn,
	.enabled = gf100_pmu_enabled,
	.पूर्णांकr = gt215_pmu_पूर्णांकr,
	.recv = gm20b_pmu_recv,
	.iniपंचांगsg = gm20b_pmu_iniपंचांगsg,
पूर्ण;

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_210_SOC)
MODULE_FIRMWARE("nvidia/gp10b/pmu/desc.bin");
MODULE_FIRMWARE("nvidia/gp10b/pmu/image.bin");
MODULE_FIRMWARE("nvidia/gp10b/pmu/sig.bin");
#पूर्ण_अगर

अटल स्थिर काष्ठा nvkm_pmu_fwअगर
gp10b_pmu_fwअगर[] = अणु
	अणु  0, gm20b_pmu_load, &gp10b_pmu, &gp10b_pmu_acr पूर्ण,
	अणु -1, gm200_pmu_nofw, &gp10b_pmu पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp10b_pmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pmu **ppmu)
अणु
	वापस nvkm_pmu_new_(gp10b_pmu_fwअगर, device, type, inst, ppmu);
पूर्ण
