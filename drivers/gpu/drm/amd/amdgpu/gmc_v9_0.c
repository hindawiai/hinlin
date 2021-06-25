<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_cache.h>

#समावेश "amdgpu.h"
#समावेश "gmc_v9_0.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "amdgpu_gem.h"

#समावेश "gc/gc_9_0_sh_mask.h"
#समावेश "dce/dce_12_0_offset.h"
#समावेश "dce/dce_12_0_sh_mask.h"
#समावेश "vega10_enum.h"
#समावेश "mmhub/mmhub_1_0_offset.h"
#समावेश "athub/athub_1_0_sh_mask.h"
#समावेश "athub/athub_1_0_offset.h"
#समावेश "oss/osssys_4_0_offset.h"

#समावेश "soc15.h"
#समावेश "soc15d.h"
#समावेश "soc15_common.h"
#समावेश "umc/umc_6_0_sh_mask.h"

#समावेश "gfxhub_v1_0.h"
#समावेश "mmhub_v1_0.h"
#समावेश "athub_v1_0.h"
#समावेश "gfxhub_v1_1.h"
#समावेश "mmhub_v9_4.h"
#समावेश "mmhub_v1_7.h"
#समावेश "umc_v6_1.h"
#समावेश "umc_v6_0.h"

#समावेश "ivsrcid/vmc/irqsrcs_vmc_1_0.h"

#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_xgmi.h"

/* add these here since we alपढ़ोy include dce12 headers and these are क्रम DCN */
#घोषणा mmHUBP0_DCSURF_PRI_VIEWPORT_DIMENSION                                                          0x055d
#घोषणा mmHUBP0_DCSURF_PRI_VIEWPORT_DIMENSION_BASE_IDX                                                 2
#घोषणा HUBP0_DCSURF_PRI_VIEWPORT_DIMENSION__PRI_VIEWPORT_WIDTH__SHIFT                                        0x0
#घोषणा HUBP0_DCSURF_PRI_VIEWPORT_DIMENSION__PRI_VIEWPORT_HEIGHT__SHIFT                                       0x10
#घोषणा HUBP0_DCSURF_PRI_VIEWPORT_DIMENSION__PRI_VIEWPORT_WIDTH_MASK                                          0x00003FFFL
#घोषणा HUBP0_DCSURF_PRI_VIEWPORT_DIMENSION__PRI_VIEWPORT_HEIGHT_MASK                                         0x3FFF0000L
#घोषणा mmDCHUBBUB_SDPIF_MMIO_CNTRL_0                                                                  0x049d
#घोषणा mmDCHUBBUB_SDPIF_MMIO_CNTRL_0_BASE_IDX                                                         2


अटल स्थिर अक्षर *gfxhub_client_ids[] = अणु
	"CB",
	"DB",
	"IA",
	"WD",
	"CPF",
	"CPC",
	"CPG",
	"RLC",
	"TCP",
	"SQC (inst)",
	"SQC (data)",
	"SQG",
	"PA",
पूर्ण;

अटल स्थिर अक्षर *mmhub_client_ids_raven[][2] = अणु
	[0][0] = "MP1",
	[1][0] = "MP0",
	[2][0] = "VCN",
	[3][0] = "VCNU",
	[4][0] = "HDP",
	[5][0] = "DCE",
	[13][0] = "UTCL2",
	[19][0] = "TLS",
	[26][0] = "OSS",
	[27][0] = "SDMA0",
	[0][1] = "MP1",
	[1][1] = "MP0",
	[2][1] = "VCN",
	[3][1] = "VCNU",
	[4][1] = "HDP",
	[5][1] = "XDP",
	[6][1] = "DBGU0",
	[7][1] = "DCE",
	[8][1] = "DCEDWB0",
	[9][1] = "DCEDWB1",
	[26][1] = "OSS",
	[27][1] = "SDMA0",
पूर्ण;

अटल स्थिर अक्षर *mmhub_client_ids_renoir[][2] = अणु
	[0][0] = "MP1",
	[1][0] = "MP0",
	[2][0] = "HDP",
	[4][0] = "DCEDMC",
	[5][0] = "DCEVGA",
	[13][0] = "UTCL2",
	[19][0] = "TLS",
	[26][0] = "OSS",
	[27][0] = "SDMA0",
	[28][0] = "VCN",
	[29][0] = "VCNU",
	[30][0] = "JPEG",
	[0][1] = "MP1",
	[1][1] = "MP0",
	[2][1] = "HDP",
	[3][1] = "XDP",
	[6][1] = "DBGU0",
	[7][1] = "DCEDMC",
	[8][1] = "DCEVGA",
	[9][1] = "DCEDWB",
	[26][1] = "OSS",
	[27][1] = "SDMA0",
	[28][1] = "VCN",
	[29][1] = "VCNU",
	[30][1] = "JPEG",
पूर्ण;

अटल स्थिर अक्षर *mmhub_client_ids_vega10[][2] = अणु
	[0][0] = "MP0",
	[1][0] = "UVD",
	[2][0] = "UVDU",
	[3][0] = "HDP",
	[13][0] = "UTCL2",
	[14][0] = "OSS",
	[15][0] = "SDMA1",
	[32+0][0] = "VCE0",
	[32+1][0] = "VCE0U",
	[32+2][0] = "XDMA",
	[32+3][0] = "DCE",
	[32+4][0] = "MP1",
	[32+14][0] = "SDMA0",
	[0][1] = "MP0",
	[1][1] = "UVD",
	[2][1] = "UVDU",
	[3][1] = "DBGU0",
	[4][1] = "HDP",
	[5][1] = "XDP",
	[14][1] = "OSS",
	[15][1] = "SDMA0",
	[32+0][1] = "VCE0",
	[32+1][1] = "VCE0U",
	[32+2][1] = "XDMA",
	[32+3][1] = "DCE",
	[32+4][1] = "DCEDWB",
	[32+5][1] = "MP1",
	[32+6][1] = "DBGU1",
	[32+14][1] = "SDMA1",
पूर्ण;

अटल स्थिर अक्षर *mmhub_client_ids_vega12[][2] = अणु
	[0][0] = "MP0",
	[1][0] = "VCE0",
	[2][0] = "VCE0U",
	[3][0] = "HDP",
	[13][0] = "UTCL2",
	[14][0] = "OSS",
	[15][0] = "SDMA1",
	[32+0][0] = "DCE",
	[32+1][0] = "XDMA",
	[32+2][0] = "UVD",
	[32+3][0] = "UVDU",
	[32+4][0] = "MP1",
	[32+15][0] = "SDMA0",
	[0][1] = "MP0",
	[1][1] = "VCE0",
	[2][1] = "VCE0U",
	[3][1] = "DBGU0",
	[4][1] = "HDP",
	[5][1] = "XDP",
	[14][1] = "OSS",
	[15][1] = "SDMA0",
	[32+0][1] = "DCE",
	[32+1][1] = "DCEDWB",
	[32+2][1] = "XDMA",
	[32+3][1] = "UVD",
	[32+4][1] = "UVDU",
	[32+5][1] = "MP1",
	[32+6][1] = "DBGU1",
	[32+15][1] = "SDMA1",
पूर्ण;

अटल स्थिर अक्षर *mmhub_client_ids_vega20[][2] = अणु
	[0][0] = "XDMA",
	[1][0] = "DCE",
	[2][0] = "VCE0",
	[3][0] = "VCE0U",
	[4][0] = "UVD",
	[5][0] = "UVD1U",
	[13][0] = "OSS",
	[14][0] = "HDP",
	[15][0] = "SDMA0",
	[32+0][0] = "UVD",
	[32+1][0] = "UVDU",
	[32+2][0] = "MP1",
	[32+3][0] = "MP0",
	[32+12][0] = "UTCL2",
	[32+14][0] = "SDMA1",
	[0][1] = "XDMA",
	[1][1] = "DCE",
	[2][1] = "DCEDWB",
	[3][1] = "VCE0",
	[4][1] = "VCE0U",
	[5][1] = "UVD1",
	[6][1] = "UVD1U",
	[7][1] = "DBGU0",
	[8][1] = "XDP",
	[13][1] = "OSS",
	[14][1] = "HDP",
	[15][1] = "SDMA0",
	[32+0][1] = "UVD",
	[32+1][1] = "UVDU",
	[32+2][1] = "DBGU1",
	[32+3][1] = "MP1",
	[32+4][1] = "MP0",
	[32+14][1] = "SDMA1",
पूर्ण;

अटल स्थिर अक्षर *mmhub_client_ids_arcturus[][2] = अणु
	[0][0] = "DBGU1",
	[1][0] = "XDP",
	[2][0] = "MP1",
	[14][0] = "HDP",
	[171][0] = "JPEG",
	[172][0] = "VCN",
	[173][0] = "VCNU",
	[203][0] = "JPEG1",
	[204][0] = "VCN1",
	[205][0] = "VCN1U",
	[256][0] = "SDMA0",
	[257][0] = "SDMA1",
	[258][0] = "SDMA2",
	[259][0] = "SDMA3",
	[260][0] = "SDMA4",
	[261][0] = "SDMA5",
	[262][0] = "SDMA6",
	[263][0] = "SDMA7",
	[384][0] = "OSS",
	[0][1] = "DBGU1",
	[1][1] = "XDP",
	[2][1] = "MP1",
	[14][1] = "HDP",
	[171][1] = "JPEG",
	[172][1] = "VCN",
	[173][1] = "VCNU",
	[203][1] = "JPEG1",
	[204][1] = "VCN1",
	[205][1] = "VCN1U",
	[256][1] = "SDMA0",
	[257][1] = "SDMA1",
	[258][1] = "SDMA2",
	[259][1] = "SDMA3",
	[260][1] = "SDMA4",
	[261][1] = "SDMA5",
	[262][1] = "SDMA6",
	[263][1] = "SDMA7",
	[384][1] = "OSS",
पूर्ण;

अटल स्थिर अक्षर *mmhub_client_ids_aldebaran[][2] = अणु
	[2][0] = "MP1",
	[3][0] = "MP0",
	[32+1][0] = "DBGU_IO0",
	[32+2][0] = "DBGU_IO2",
	[32+4][0] = "MPIO",
	[96+11][0] = "JPEG0",
	[96+12][0] = "VCN0",
	[96+13][0] = "VCNU0",
	[128+11][0] = "JPEG1",
	[128+12][0] = "VCN1",
	[128+13][0] = "VCNU1",
	[160+1][0] = "XDP",
	[160+14][0] = "HDP",
	[256+0][0] = "SDMA0",
	[256+1][0] = "SDMA1",
	[256+2][0] = "SDMA2",
	[256+3][0] = "SDMA3",
	[256+4][0] = "SDMA4",
	[384+0][0] = "OSS",
	[2][1] = "MP1",
	[3][1] = "MP0",
	[32+1][1] = "DBGU_IO0",
	[32+2][1] = "DBGU_IO2",
	[32+4][1] = "MPIO",
	[96+11][1] = "JPEG0",
	[96+12][1] = "VCN0",
	[96+13][1] = "VCNU0",
	[128+11][1] = "JPEG1",
	[128+12][1] = "VCN1",
	[128+13][1] = "VCNU1",
	[160+1][1] = "XDP",
	[160+14][1] = "HDP",
	[256+0][1] = "SDMA0",
	[256+1][1] = "SDMA1",
	[256+2][1] = "SDMA2",
	[256+3][1] = "SDMA3",
	[256+4][1] = "SDMA4",
	[384+0][1] = "OSS",
पूर्ण;

अटल स्थिर काष्ठा soc15_reg_golden golden_settings_mmhub_1_0_0[] =
अणु
	SOC15_REG_GOLDEN_VALUE(MMHUB, 0, mmDAGB1_WRCLI2, 0x00000007, 0xfe5fe0fa),
	SOC15_REG_GOLDEN_VALUE(MMHUB, 0, mmMMEA1_DRAM_WR_CLI2GRP_MAP0, 0x00000030, 0x55555565)
पूर्ण;

अटल स्थिर काष्ठा soc15_reg_golden golden_settings_athub_1_0_0[] =
अणु
	SOC15_REG_GOLDEN_VALUE(ATHUB, 0, mmRPB_ARB_CNTL, 0x0000ff00, 0x00000800),
	SOC15_REG_GOLDEN_VALUE(ATHUB, 0, mmRPB_ARB_CNTL2, 0x00ff00ff, 0x00080008)
पूर्ण;

अटल स्थिर uपूर्णांक32_t ecc_umc_mcumc_ctrl_addrs[] = अणु
	(0x000143c0 + 0x00000000),
	(0x000143c0 + 0x00000800),
	(0x000143c0 + 0x00001000),
	(0x000143c0 + 0x00001800),
	(0x000543c0 + 0x00000000),
	(0x000543c0 + 0x00000800),
	(0x000543c0 + 0x00001000),
	(0x000543c0 + 0x00001800),
	(0x000943c0 + 0x00000000),
	(0x000943c0 + 0x00000800),
	(0x000943c0 + 0x00001000),
	(0x000943c0 + 0x00001800),
	(0x000d43c0 + 0x00000000),
	(0x000d43c0 + 0x00000800),
	(0x000d43c0 + 0x00001000),
	(0x000d43c0 + 0x00001800),
	(0x001143c0 + 0x00000000),
	(0x001143c0 + 0x00000800),
	(0x001143c0 + 0x00001000),
	(0x001143c0 + 0x00001800),
	(0x001543c0 + 0x00000000),
	(0x001543c0 + 0x00000800),
	(0x001543c0 + 0x00001000),
	(0x001543c0 + 0x00001800),
	(0x001943c0 + 0x00000000),
	(0x001943c0 + 0x00000800),
	(0x001943c0 + 0x00001000),
	(0x001943c0 + 0x00001800),
	(0x001d43c0 + 0x00000000),
	(0x001d43c0 + 0x00000800),
	(0x001d43c0 + 0x00001000),
	(0x001d43c0 + 0x00001800),
पूर्ण;

अटल स्थिर uपूर्णांक32_t ecc_umc_mcumc_ctrl_mask_addrs[] = अणु
	(0x000143e0 + 0x00000000),
	(0x000143e0 + 0x00000800),
	(0x000143e0 + 0x00001000),
	(0x000143e0 + 0x00001800),
	(0x000543e0 + 0x00000000),
	(0x000543e0 + 0x00000800),
	(0x000543e0 + 0x00001000),
	(0x000543e0 + 0x00001800),
	(0x000943e0 + 0x00000000),
	(0x000943e0 + 0x00000800),
	(0x000943e0 + 0x00001000),
	(0x000943e0 + 0x00001800),
	(0x000d43e0 + 0x00000000),
	(0x000d43e0 + 0x00000800),
	(0x000d43e0 + 0x00001000),
	(0x000d43e0 + 0x00001800),
	(0x001143e0 + 0x00000000),
	(0x001143e0 + 0x00000800),
	(0x001143e0 + 0x00001000),
	(0x001143e0 + 0x00001800),
	(0x001543e0 + 0x00000000),
	(0x001543e0 + 0x00000800),
	(0x001543e0 + 0x00001000),
	(0x001543e0 + 0x00001800),
	(0x001943e0 + 0x00000000),
	(0x001943e0 + 0x00000800),
	(0x001943e0 + 0x00001000),
	(0x001943e0 + 0x00001800),
	(0x001d43e0 + 0x00000000),
	(0x001d43e0 + 0x00000800),
	(0x001d43e0 + 0x00001000),
	(0x001d43e0 + 0x00001800),
पूर्ण;

अटल पूर्णांक gmc_v9_0_ecc_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
		काष्ठा amdgpu_irq_src *src,
		अचिन्हित type,
		क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 bits, i, पंचांगp, reg;

	/* Devices newer then VEGA10/12 shall have these programming
	     sequences perक्रमmed by PSP BL */
	अगर (adev->asic_type >= CHIP_VEGA20)
		वापस 0;

	bits = 0x7f;

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		क्रम (i = 0; i < ARRAY_SIZE(ecc_umc_mcumc_ctrl_addrs); i++) अणु
			reg = ecc_umc_mcumc_ctrl_addrs[i];
			पंचांगp = RREG32(reg);
			पंचांगp &= ~bits;
			WREG32(reg, पंचांगp);
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(ecc_umc_mcumc_ctrl_mask_addrs); i++) अणु
			reg = ecc_umc_mcumc_ctrl_mask_addrs[i];
			पंचांगp = RREG32(reg);
			पंचांगp &= ~bits;
			WREG32(reg, पंचांगp);
		पूर्ण
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		क्रम (i = 0; i < ARRAY_SIZE(ecc_umc_mcumc_ctrl_addrs); i++) अणु
			reg = ecc_umc_mcumc_ctrl_addrs[i];
			पंचांगp = RREG32(reg);
			पंचांगp |= bits;
			WREG32(reg, पंचांगp);
		पूर्ण
		क्रम (i = 0; i < ARRAY_SIZE(ecc_umc_mcumc_ctrl_mask_addrs); i++) अणु
			reg = ecc_umc_mcumc_ctrl_mask_addrs[i];
			पंचांगp = RREG32(reg);
			पंचांगp |= bits;
			WREG32(reg, पंचांगp);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v9_0_vm_fault_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *src,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	काष्ठा amdgpu_vmhub *hub;
	u32 पंचांगp, reg, bits, i, j;

	bits = VM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		VM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		VM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		VM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		VM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		VM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK |
		VM_CONTEXT1_CNTL__EXECUTE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK;

	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		क्रम (j = 0; j < adev->num_vmhubs; j++) अणु
			hub = &adev->vmhub[j];
			क्रम (i = 0; i < 16; i++) अणु
				reg = hub->vm_context0_cntl + i;
				पंचांगp = RREG32(reg);
				पंचांगp &= ~bits;
				WREG32(reg, पंचांगp);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		क्रम (j = 0; j < adev->num_vmhubs; j++) अणु
			hub = &adev->vmhub[j];
			क्रम (i = 0; i < 16; i++) अणु
				reg = hub->vm_context0_cntl + i;
				पंचांगp = RREG32(reg);
				पंचांगp |= bits;
				WREG32(reg, पंचांगp);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v9_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	bool retry_fault = !!(entry->src_data[1] & 0x80);
	uपूर्णांक32_t status = 0, cid = 0, rw = 0;
	काष्ठा amdgpu_task_info task_info;
	काष्ठा amdgpu_vmhub *hub;
	स्थिर अक्षर *mmhub_cid;
	स्थिर अक्षर *hub_name;
	u64 addr;

	addr = (u64)entry->src_data[0] << 12;
	addr |= ((u64)entry->src_data[1] & 0xf) << 44;

	अगर (retry_fault) अणु
		/* Returning 1 here also prevents sending the IV to the KFD */

		/* Process it onyl अगर it's the first fault क्रम this address */
		अगर (entry->ih != &adev->irq.ih_soft &&
		    amdgpu_gmc_filter_faults(adev, addr, entry->pasid,
					     entry->बारtamp))
			वापस 1;

		/* Delegate it to a dअगरferent ring अगर the hardware hasn't
		 * alपढ़ोy करोne it.
		 */
		अगर (entry->ih == &adev->irq.ih) अणु
			amdgpu_irq_delegate(adev, entry, 8);
			वापस 1;
		पूर्ण

		/* Try to handle the recoverable page faults by filling page
		 * tables
		 */
		अगर (amdgpu_vm_handle_fault(adev, entry->pasid, addr))
			वापस 1;
	पूर्ण

	अगर (!prपूर्णांकk_ratelimit())
		वापस 0;

	अगर (entry->client_id == SOC15_IH_CLIENTID_VMC) अणु
		hub_name = "mmhub0";
		hub = &adev->vmhub[AMDGPU_MMHUB_0];
	पूर्ण अन्यथा अगर (entry->client_id == SOC15_IH_CLIENTID_VMC1) अणु
		hub_name = "mmhub1";
		hub = &adev->vmhub[AMDGPU_MMHUB_1];
	पूर्ण अन्यथा अणु
		hub_name = "gfxhub0";
		hub = &adev->vmhub[AMDGPU_GFXHUB_0];
	पूर्ण

	स_रखो(&task_info, 0, माप(काष्ठा amdgpu_task_info));
	amdgpu_vm_get_task_info(adev, entry->pasid, &task_info);

	dev_err(adev->dev,
		"[%s] %s page fault (src_id:%u ring:%u vmid:%u "
		"pasid:%u, for process %s pid %d thread %s pid %d)\n",
		hub_name, retry_fault ? "retry" : "no-retry",
		entry->src_id, entry->ring_id, entry->vmid,
		entry->pasid, task_info.process_name, task_info.tgid,
		task_info.task_name, task_info.pid);
	dev_err(adev->dev, "  in page starting at address 0x%016llx from IH client 0x%x (%s)\n",
		addr, entry->client_id,
		soc15_ih_clientid_name[entry->client_id]);

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	/*
	 * Issue a dummy पढ़ो to रुको क्रम the status रेजिस्टर to
	 * be updated to aव्योम पढ़ोing an incorrect value due to
	 * the new fast GRBM पूर्णांकerface.
	 */
	अगर ((entry->vmid_src == AMDGPU_GFXHUB_0) &&
	    (adev->asic_type < CHIP_ALDEBARAN))
		RREG32(hub->vm_l2_pro_fault_status);

	status = RREG32(hub->vm_l2_pro_fault_status);
	cid = REG_GET_FIELD(status, VM_L2_PROTECTION_FAULT_STATUS, CID);
	rw = REG_GET_FIELD(status, VM_L2_PROTECTION_FAULT_STATUS, RW);
	WREG32_P(hub->vm_l2_pro_fault_cntl, 1, ~1);


	dev_err(adev->dev,
		"VM_L2_PROTECTION_FAULT_STATUS:0x%08X\n",
		status);
	अगर (hub == &adev->vmhub[AMDGPU_GFXHUB_0]) अणु
		dev_err(adev->dev, "\t Faulty UTCL2 client ID: %s (0x%x)\n",
			cid >= ARRAY_SIZE(gfxhub_client_ids) ? "unknown" :
			gfxhub_client_ids[cid],
			cid);
	पूर्ण अन्यथा अणु
		चयन (adev->asic_type) अणु
		हाल CHIP_VEGA10:
			mmhub_cid = mmhub_client_ids_vega10[cid][rw];
			अवरोध;
		हाल CHIP_VEGA12:
			mmhub_cid = mmhub_client_ids_vega12[cid][rw];
			अवरोध;
		हाल CHIP_VEGA20:
			mmhub_cid = mmhub_client_ids_vega20[cid][rw];
			अवरोध;
		हाल CHIP_ARCTURUS:
			mmhub_cid = mmhub_client_ids_arcturus[cid][rw];
			अवरोध;
		हाल CHIP_RAVEN:
			mmhub_cid = mmhub_client_ids_raven[cid][rw];
			अवरोध;
		हाल CHIP_RENOIR:
			mmhub_cid = mmhub_client_ids_renoir[cid][rw];
			अवरोध;
		हाल CHIP_ALDEBARAN:
			mmhub_cid = mmhub_client_ids_aldebaran[cid][rw];
			अवरोध;
		शेष:
			mmhub_cid = शून्य;
			अवरोध;
		पूर्ण
		dev_err(adev->dev, "\t Faulty UTCL2 client ID: %s (0x%x)\n",
			mmhub_cid ? mmhub_cid : "unknown", cid);
	पूर्ण
	dev_err(adev->dev, "\t MORE_FAULTS: 0x%lx\n",
		REG_GET_FIELD(status,
		VM_L2_PROTECTION_FAULT_STATUS, MORE_FAULTS));
	dev_err(adev->dev, "\t WALKER_ERROR: 0x%lx\n",
		REG_GET_FIELD(status,
		VM_L2_PROTECTION_FAULT_STATUS, WALKER_ERROR));
	dev_err(adev->dev, "\t PERMISSION_FAULTS: 0x%lx\n",
		REG_GET_FIELD(status,
		VM_L2_PROTECTION_FAULT_STATUS, PERMISSION_FAULTS));
	dev_err(adev->dev, "\t MAPPING_ERROR: 0x%lx\n",
		REG_GET_FIELD(status,
		VM_L2_PROTECTION_FAULT_STATUS, MAPPING_ERROR));
	dev_err(adev->dev, "\t RW: 0x%x\n", rw);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gmc_v9_0_irq_funcs = अणु
	.set = gmc_v9_0_vm_fault_पूर्णांकerrupt_state,
	.process = gmc_v9_0_process_पूर्णांकerrupt,
पूर्ण;


अटल स्थिर काष्ठा amdgpu_irq_src_funcs gmc_v9_0_ecc_funcs = अणु
	.set = gmc_v9_0_ecc_पूर्णांकerrupt_state,
	.process = amdgpu_umc_process_ecc_irq,
पूर्ण;

अटल व्योम gmc_v9_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gmc.vm_fault.num_types = 1;
	adev->gmc.vm_fault.funcs = &gmc_v9_0_irq_funcs;

	अगर (!amdgpu_sriov_vf(adev) &&
	    !adev->gmc.xgmi.connected_to_cpu) अणु
		adev->gmc.ecc_irq.num_types = 1;
		adev->gmc.ecc_irq.funcs = &gmc_v9_0_ecc_funcs;
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t gmc_v9_0_get_invalidate_req(अचिन्हित पूर्णांक vmid,
					uपूर्णांक32_t flush_type)
अणु
	u32 req = 0;

	req = REG_SET_FIELD(req, VM_INVALIDATE_ENG0_REQ,
			    PER_VMID_INVALIDATE_REQ, 1 << vmid);
	req = REG_SET_FIELD(req, VM_INVALIDATE_ENG0_REQ, FLUSH_TYPE, flush_type);
	req = REG_SET_FIELD(req, VM_INVALIDATE_ENG0_REQ, INVALIDATE_L2_PTES, 1);
	req = REG_SET_FIELD(req, VM_INVALIDATE_ENG0_REQ, INVALIDATE_L2_PDE0, 1);
	req = REG_SET_FIELD(req, VM_INVALIDATE_ENG0_REQ, INVALIDATE_L2_PDE1, 1);
	req = REG_SET_FIELD(req, VM_INVALIDATE_ENG0_REQ, INVALIDATE_L2_PDE2, 1);
	req = REG_SET_FIELD(req, VM_INVALIDATE_ENG0_REQ, INVALIDATE_L1_PTES, 1);
	req = REG_SET_FIELD(req, VM_INVALIDATE_ENG0_REQ,
			    CLEAR_PROTECTION_FAULT_STATUS_ADDR,	0);

	वापस req;
पूर्ण

/**
 * gmc_v9_0_use_invalidate_semaphore - judge whether to use semaphore
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vmhub: vmhub type
 *
 */
अटल bool gmc_v9_0_use_invalidate_semaphore(काष्ठा amdgpu_device *adev,
				       uपूर्णांक32_t vmhub)
अणु
	अगर (adev->asic_type == CHIP_ALDEBARAN)
		वापस false;

	वापस ((vmhub == AMDGPU_MMHUB_0 ||
		 vmhub == AMDGPU_MMHUB_1) &&
		(!amdgpu_sriov_vf(adev)) &&
		(!(!(adev->apu_flags & AMD_APU_IS_RAVEN2) &&
		   (adev->apu_flags & AMD_APU_IS_PICASSO))));
पूर्ण

अटल bool gmc_v9_0_get_atc_vmid_pasid_mapping_info(काष्ठा amdgpu_device *adev,
					uपूर्णांक8_t vmid, uपूर्णांक16_t *p_pasid)
अणु
	uपूर्णांक32_t value;

	value = RREG32(SOC15_REG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING)
		     + vmid);
	*p_pasid = value & ATC_VMID0_PASID_MAPPING__PASID_MASK;

	वापस !!(value & ATC_VMID0_PASID_MAPPING__VALID_MASK);
पूर्ण

/*
 * GART
 * VMID 0 is the physical GPU addresses as used by the kernel.
 * VMIDs 1-15 are used क्रम userspace clients and are handled
 * by the amdgpu vm/hsa code.
 */

/**
 * gmc_v9_0_flush_gpu_tlb - tlb flush with certain type
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vmid: vm instance to flush
 * @vmhub: which hub to flush
 * @flush_type: the flush type
 *
 * Flush the TLB क्रम the requested page table using certain type.
 */
अटल व्योम gmc_v9_0_flush_gpu_tlb(काष्ठा amdgpu_device *adev, uपूर्णांक32_t vmid,
					uपूर्णांक32_t vmhub, uपूर्णांक32_t flush_type)
अणु
	bool use_semaphore = gmc_v9_0_use_invalidate_semaphore(adev, vmhub);
	स्थिर अचिन्हित eng = 17;
	u32 j, inv_req, inv_req2, पंचांगp;
	काष्ठा amdgpu_vmhub *hub;

	BUG_ON(vmhub >= adev->num_vmhubs);

	hub = &adev->vmhub[vmhub];
	अगर (adev->gmc.xgmi.num_physical_nodes &&
	    adev->asic_type == CHIP_VEGA20) अणु
		/* Vega20+XGMI caches PTEs in TC and TLB. Add a
		 * heavy-weight TLB flush (type 2), which flushes
		 * both. Due to a race condition with concurrent
		 * memory accesses using the same TLB cache line, we
		 * still need a second TLB flush after this.
		 */
		inv_req = gmc_v9_0_get_invalidate_req(vmid, 2);
		inv_req2 = gmc_v9_0_get_invalidate_req(vmid, flush_type);
	पूर्ण अन्यथा अणु
		inv_req = gmc_v9_0_get_invalidate_req(vmid, flush_type);
		inv_req2 = 0;
	पूर्ण

	/* This is necessary क्रम a HW workaround under SRIOV as well
	 * as GFXOFF under bare metal
	 */
	अगर (adev->gfx.kiq.ring.sched.पढ़ोy &&
	    (amdgpu_sriov_runसमय(adev) || !amdgpu_sriov_vf(adev)) &&
	    करोwn_पढ़ो_trylock(&adev->reset_sem)) अणु
		uपूर्णांक32_t req = hub->vm_inv_eng0_req + hub->eng_distance * eng;
		uपूर्णांक32_t ack = hub->vm_inv_eng0_ack + hub->eng_distance * eng;

		amdgpu_virt_kiq_reg_ग_लिखो_reg_रुको(adev, req, ack, inv_req,
						   1 << vmid);
		up_पढ़ो(&adev->reset_sem);
		वापस;
	पूर्ण

	spin_lock(&adev->gmc.invalidate_lock);

	/*
	 * It may lose gpuvm invalidate acknowldege state across घातer-gating
	 * off cycle, add semaphore acquire beक्रमe invalidation and semaphore
	 * release after invalidation to aव्योम entering घातer gated state
	 * to WA the Issue
	 */

	/* TODO: It needs to जारी working on debugging with semaphore क्रम GFXHUB as well. */
	अगर (use_semaphore) अणु
		क्रम (j = 0; j < adev->usec_समयout; j++) अणु
			/* a पढ़ो वापस value of 1 means semaphore acuqire */
			पंचांगp = RREG32_NO_KIQ(hub->vm_inv_eng0_sem +
					    hub->eng_distance * eng);
			अगर (पंचांगp & 0x1)
				अवरोध;
			udelay(1);
		पूर्ण

		अगर (j >= adev->usec_समयout)
			DRM_ERROR("Timeout waiting for sem acquire in VM flush!\n");
	पूर्ण

	करो अणु
		WREG32_NO_KIQ(hub->vm_inv_eng0_req +
			      hub->eng_distance * eng, inv_req);

		/*
		 * Issue a dummy पढ़ो to रुको क्रम the ACK रेजिस्टर to
		 * be cleared to aव्योम a false ACK due to the new fast
		 * GRBM पूर्णांकerface.
		 */
		अगर ((vmhub == AMDGPU_GFXHUB_0) &&
		    (adev->asic_type < CHIP_ALDEBARAN))
			RREG32_NO_KIQ(hub->vm_inv_eng0_req +
				      hub->eng_distance * eng);

		क्रम (j = 0; j < adev->usec_समयout; j++) अणु
			पंचांगp = RREG32_NO_KIQ(hub->vm_inv_eng0_ack +
					    hub->eng_distance * eng);
			अगर (पंचांगp & (1 << vmid))
				अवरोध;
			udelay(1);
		पूर्ण

		inv_req = inv_req2;
		inv_req2 = 0;
	पूर्ण जबतक (inv_req);

	/* TODO: It needs to जारी working on debugging with semaphore क्रम GFXHUB as well. */
	अगर (use_semaphore)
		/*
		 * add semaphore release after invalidation,
		 * ग_लिखो with 0 means semaphore release
		 */
		WREG32_NO_KIQ(hub->vm_inv_eng0_sem +
			      hub->eng_distance * eng, 0);

	spin_unlock(&adev->gmc.invalidate_lock);

	अगर (j < adev->usec_समयout)
		वापस;

	DRM_ERROR("Timeout waiting for VM flush ACK!\n");
पूर्ण

/**
 * gmc_v9_0_flush_gpu_tlb_pasid - tlb flush via pasid
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @pasid: pasid to be flush
 * @flush_type: the flush type
 * @all_hub: flush all hubs
 *
 * Flush the TLB क्रम the requested pasid.
 */
अटल पूर्णांक gmc_v9_0_flush_gpu_tlb_pasid(काष्ठा amdgpu_device *adev,
					uपूर्णांक16_t pasid, uपूर्णांक32_t flush_type,
					bool all_hub)
अणु
	पूर्णांक vmid, i;
	चिन्हित दीर्घ r;
	uपूर्णांक32_t seq;
	uपूर्णांक16_t queried_pasid;
	bool ret;
	काष्ठा amdgpu_ring *ring = &adev->gfx.kiq.ring;
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;

	अगर (amdgpu_in_reset(adev))
		वापस -EIO;

	अगर (ring->sched.पढ़ोy && करोwn_पढ़ो_trylock(&adev->reset_sem)) अणु
		/* Vega20+XGMI caches PTEs in TC and TLB. Add a
		 * heavy-weight TLB flush (type 2), which flushes
		 * both. Due to a race condition with concurrent
		 * memory accesses using the same TLB cache line, we
		 * still need a second TLB flush after this.
		 */
		bool vega20_xgmi_wa = (adev->gmc.xgmi.num_physical_nodes &&
				       adev->asic_type == CHIP_VEGA20);
		/* 2 dwords flush + 8 dwords fence */
		अचिन्हित पूर्णांक ndw = kiq->pmf->invalidate_tlbs_size + 8;

		अगर (vega20_xgmi_wa)
			ndw += kiq->pmf->invalidate_tlbs_size;

		spin_lock(&adev->gfx.kiq.ring_lock);
		/* 2 dwords flush + 8 dwords fence */
		amdgpu_ring_alloc(ring, ndw);
		अगर (vega20_xgmi_wa)
			kiq->pmf->kiq_invalidate_tlbs(ring,
						      pasid, 2, all_hub);
		kiq->pmf->kiq_invalidate_tlbs(ring,
					pasid, flush_type, all_hub);
		r = amdgpu_fence_emit_polling(ring, &seq, MAX_KIQ_REG_WAIT);
		अगर (r) अणु
			amdgpu_ring_unकरो(ring);
			spin_unlock(&adev->gfx.kiq.ring_lock);
			up_पढ़ो(&adev->reset_sem);
			वापस -ETIME;
		पूर्ण

		amdgpu_ring_commit(ring);
		spin_unlock(&adev->gfx.kiq.ring_lock);
		r = amdgpu_fence_रुको_polling(ring, seq, adev->usec_समयout);
		अगर (r < 1) अणु
			dev_err(adev->dev, "wait for kiq fence error: %ld.\n", r);
			up_पढ़ो(&adev->reset_sem);
			वापस -ETIME;
		पूर्ण
		up_पढ़ो(&adev->reset_sem);
		वापस 0;
	पूर्ण

	क्रम (vmid = 1; vmid < 16; vmid++) अणु

		ret = gmc_v9_0_get_atc_vmid_pasid_mapping_info(adev, vmid,
				&queried_pasid);
		अगर (ret && queried_pasid == pasid) अणु
			अगर (all_hub) अणु
				क्रम (i = 0; i < adev->num_vmhubs; i++)
					gmc_v9_0_flush_gpu_tlb(adev, vmid,
							i, flush_type);
			पूर्ण अन्यथा अणु
				gmc_v9_0_flush_gpu_tlb(adev, vmid,
						AMDGPU_GFXHUB_0, flush_type);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;

पूर्ण

अटल uपूर्णांक64_t gmc_v9_0_emit_flush_gpu_tlb(काष्ठा amdgpu_ring *ring,
					    अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	bool use_semaphore = gmc_v9_0_use_invalidate_semaphore(ring->adev, ring->funcs->vmhub);
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[ring->funcs->vmhub];
	uपूर्णांक32_t req = gmc_v9_0_get_invalidate_req(vmid, 0);
	अचिन्हित eng = ring->vm_inv_eng;

	/*
	 * It may lose gpuvm invalidate acknowldege state across घातer-gating
	 * off cycle, add semaphore acquire beक्रमe invalidation and semaphore
	 * release after invalidation to aव्योम entering घातer gated state
	 * to WA the Issue
	 */

	/* TODO: It needs to जारी working on debugging with semaphore क्रम GFXHUB as well. */
	अगर (use_semaphore)
		/* a पढ़ो वापस value of 1 means semaphore acuqire */
		amdgpu_ring_emit_reg_रुको(ring,
					  hub->vm_inv_eng0_sem +
					  hub->eng_distance * eng, 0x1, 0x1);

	amdgpu_ring_emit_wreg(ring, hub->ctx0_ptb_addr_lo32 +
			      (hub->ctx_addr_distance * vmid),
			      lower_32_bits(pd_addr));

	amdgpu_ring_emit_wreg(ring, hub->ctx0_ptb_addr_hi32 +
			      (hub->ctx_addr_distance * vmid),
			      upper_32_bits(pd_addr));

	amdgpu_ring_emit_reg_ग_लिखो_reg_रुको(ring, hub->vm_inv_eng0_req +
					    hub->eng_distance * eng,
					    hub->vm_inv_eng0_ack +
					    hub->eng_distance * eng,
					    req, 1 << vmid);

	/* TODO: It needs to जारी working on debugging with semaphore क्रम GFXHUB as well. */
	अगर (use_semaphore)
		/*
		 * add semaphore release after invalidation,
		 * ग_लिखो with 0 means semaphore release
		 */
		amdgpu_ring_emit_wreg(ring, hub->vm_inv_eng0_sem +
				      hub->eng_distance * eng, 0);

	वापस pd_addr;
पूर्ण

अटल व्योम gmc_v9_0_emit_pasid_mapping(काष्ठा amdgpu_ring *ring, अचिन्हित vmid,
					अचिन्हित pasid)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t reg;

	/* Do nothing because there's no lut रेजिस्टर क्रम mmhub1. */
	अगर (ring->funcs->vmhub == AMDGPU_MMHUB_1)
		वापस;

	अगर (ring->funcs->vmhub == AMDGPU_GFXHUB_0)
		reg = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_VMID_0_LUT) + vmid;
	अन्यथा
		reg = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_VMID_0_LUT_MM) + vmid;

	amdgpu_ring_emit_wreg(ring, reg, pasid);
पूर्ण

/*
 * PTE क्रमmat on VEGA 10:
 * 63:59 reserved
 * 58:57 mtype
 * 56 F
 * 55 L
 * 54 P
 * 53 SW
 * 52 T
 * 50:48 reserved
 * 47:12 4k physical page base address
 * 11:7 fragment
 * 6 ग_लिखो
 * 5 पढ़ो
 * 4 exe
 * 3 Z
 * 2 snooped
 * 1 प्रणाली
 * 0 valid
 *
 * PDE क्रमmat on VEGA 10:
 * 63:59 block fragment size
 * 58:55 reserved
 * 54 P
 * 53:48 reserved
 * 47:6 physical base address of PD or PTE
 * 5:3 reserved
 * 2 C
 * 1 प्रणाली
 * 0 valid
 */

अटल uपूर्णांक64_t gmc_v9_0_map_mtype(काष्ठा amdgpu_device *adev, uपूर्णांक32_t flags)

अणु
	चयन (flags) अणु
	हाल AMDGPU_VM_MTYPE_DEFAULT:
		वापस AMDGPU_PTE_MTYPE_VG10(MTYPE_NC);
	हाल AMDGPU_VM_MTYPE_NC:
		वापस AMDGPU_PTE_MTYPE_VG10(MTYPE_NC);
	हाल AMDGPU_VM_MTYPE_WC:
		वापस AMDGPU_PTE_MTYPE_VG10(MTYPE_WC);
	हाल AMDGPU_VM_MTYPE_RW:
		वापस AMDGPU_PTE_MTYPE_VG10(MTYPE_RW);
	हाल AMDGPU_VM_MTYPE_CC:
		वापस AMDGPU_PTE_MTYPE_VG10(MTYPE_CC);
	हाल AMDGPU_VM_MTYPE_UC:
		वापस AMDGPU_PTE_MTYPE_VG10(MTYPE_UC);
	शेष:
		वापस AMDGPU_PTE_MTYPE_VG10(MTYPE_NC);
	पूर्ण
पूर्ण

अटल व्योम gmc_v9_0_get_vm_pde(काष्ठा amdgpu_device *adev, पूर्णांक level,
				uपूर्णांक64_t *addr, uपूर्णांक64_t *flags)
अणु
	अगर (!(*flags & AMDGPU_PDE_PTE) && !(*flags & AMDGPU_PTE_SYSTEM))
		*addr = amdgpu_gmc_vram_mc2pa(adev, *addr);
	BUG_ON(*addr & 0xFFFF00000000003FULL);

	अगर (!adev->gmc.translate_further)
		वापस;

	अगर (level == AMDGPU_VM_PDB1) अणु
		/* Set the block fragment size */
		अगर (!(*flags & AMDGPU_PDE_PTE))
			*flags |= AMDGPU_PDE_BFS(0x9);

	पूर्ण अन्यथा अगर (level == AMDGPU_VM_PDB0) अणु
		अगर (*flags & AMDGPU_PDE_PTE)
			*flags &= ~AMDGPU_PDE_PTE;
		अन्यथा
			*flags |= AMDGPU_PTE_TF;
	पूर्ण
पूर्ण

अटल व्योम gmc_v9_0_get_vm_pte(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_bo_va_mapping *mapping,
				uपूर्णांक64_t *flags)
अणु
	*flags &= ~AMDGPU_PTE_EXECUTABLE;
	*flags |= mapping->flags & AMDGPU_PTE_EXECUTABLE;

	*flags &= ~AMDGPU_PTE_MTYPE_VG10_MASK;
	*flags |= mapping->flags & AMDGPU_PTE_MTYPE_VG10_MASK;

	अगर (mapping->flags & AMDGPU_PTE_PRT) अणु
		*flags |= AMDGPU_PTE_PRT;
		*flags &= ~AMDGPU_PTE_VALID;
	पूर्ण

	अगर ((adev->asic_type == CHIP_ARCTURUS ||
	    adev->asic_type == CHIP_ALDEBARAN) &&
	    !(*flags & AMDGPU_PTE_SYSTEM) &&
	    mapping->bo_va->is_xgmi)
		*flags |= AMDGPU_PTE_SNOOPED;

	अगर (adev->asic_type == CHIP_ALDEBARAN)
		*flags |= mapping->flags & AMDGPU_PTE_SNOOPED;
पूर्ण

अटल अचिन्हित gmc_v9_0_get_vbios_fb_size(काष्ठा amdgpu_device *adev)
अणु
	u32 d1vga_control = RREG32_SOC15(DCE, 0, mmD1VGA_CONTROL);
	अचिन्हित size;

	अगर (REG_GET_FIELD(d1vga_control, D1VGA_CONTROL, D1VGA_MODE_ENABLE)) अणु
		size = AMDGPU_VBIOS_VGA_ALLOCATION;
	पूर्ण अन्यथा अणु
		u32 viewport;

		चयन (adev->asic_type) अणु
		हाल CHIP_RAVEN:
		हाल CHIP_RENOIR:
			viewport = RREG32_SOC15(DCE, 0, mmHUBP0_DCSURF_PRI_VIEWPORT_DIMENSION);
			size = (REG_GET_FIELD(viewport,
					      HUBP0_DCSURF_PRI_VIEWPORT_DIMENSION, PRI_VIEWPORT_HEIGHT) *
				REG_GET_FIELD(viewport,
					      HUBP0_DCSURF_PRI_VIEWPORT_DIMENSION, PRI_VIEWPORT_WIDTH) *
				4);
			अवरोध;
		हाल CHIP_VEGA10:
		हाल CHIP_VEGA12:
		हाल CHIP_VEGA20:
		शेष:
			viewport = RREG32_SOC15(DCE, 0, mmSCL0_VIEWPORT_SIZE);
			size = (REG_GET_FIELD(viewport, SCL0_VIEWPORT_SIZE, VIEWPORT_HEIGHT) *
				REG_GET_FIELD(viewport, SCL0_VIEWPORT_SIZE, VIEWPORT_WIDTH) *
				4);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस size;
पूर्ण

अटल स्थिर काष्ठा amdgpu_gmc_funcs gmc_v9_0_gmc_funcs = अणु
	.flush_gpu_tlb = gmc_v9_0_flush_gpu_tlb,
	.flush_gpu_tlb_pasid = gmc_v9_0_flush_gpu_tlb_pasid,
	.emit_flush_gpu_tlb = gmc_v9_0_emit_flush_gpu_tlb,
	.emit_pasid_mapping = gmc_v9_0_emit_pasid_mapping,
	.map_mtype = gmc_v9_0_map_mtype,
	.get_vm_pde = gmc_v9_0_get_vm_pde,
	.get_vm_pte = gmc_v9_0_get_vm_pte,
	.get_vbios_fb_size = gmc_v9_0_get_vbios_fb_size,
पूर्ण;

अटल व्योम gmc_v9_0_set_gmc_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gmc.gmc_funcs = &gmc_v9_0_gmc_funcs;
पूर्ण

अटल व्योम gmc_v9_0_set_umc_funcs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA10:
		adev->umc.funcs = &umc_v6_0_funcs;
		अवरोध;
	हाल CHIP_VEGA20:
		adev->umc.max_ras_err_cnt_per_query = UMC_V6_1_TOTAL_CHANNEL_NUM;
		adev->umc.channel_inst_num = UMC_V6_1_CHANNEL_INSTANCE_NUM;
		adev->umc.umc_inst_num = UMC_V6_1_UMC_INSTANCE_NUM;
		adev->umc.channel_offs = UMC_V6_1_PER_CHANNEL_OFFSET_VG20;
		adev->umc.channel_idx_tbl = &umc_v6_1_channel_idx_tbl[0][0];
		adev->umc.ras_funcs = &umc_v6_1_ras_funcs;
		अवरोध;
	हाल CHIP_ARCTURUS:
		adev->umc.max_ras_err_cnt_per_query = UMC_V6_1_TOTAL_CHANNEL_NUM;
		adev->umc.channel_inst_num = UMC_V6_1_CHANNEL_INSTANCE_NUM;
		adev->umc.umc_inst_num = UMC_V6_1_UMC_INSTANCE_NUM;
		adev->umc.channel_offs = UMC_V6_1_PER_CHANNEL_OFFSET_ARCT;
		adev->umc.channel_idx_tbl = &umc_v6_1_channel_idx_tbl[0][0];
		adev->umc.ras_funcs = &umc_v6_1_ras_funcs;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gmc_v9_0_set_mmhub_funcs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_ARCTURUS:
		adev->mmhub.funcs = &mmhub_v9_4_funcs;
		अवरोध;
	हाल CHIP_ALDEBARAN:
		adev->mmhub.funcs = &mmhub_v1_7_funcs;
		अवरोध;
	शेष:
		adev->mmhub.funcs = &mmhub_v1_0_funcs;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gmc_v9_0_set_mmhub_ras_funcs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA20:
		adev->mmhub.ras_funcs = &mmhub_v1_0_ras_funcs;
		अवरोध;
	हाल CHIP_ARCTURUS:
		adev->mmhub.ras_funcs = &mmhub_v9_4_ras_funcs;
		अवरोध;
	हाल CHIP_ALDEBARAN:
		adev->mmhub.ras_funcs = &mmhub_v1_7_ras_funcs;
		अवरोध;
	शेष:
		/* mmhub ras is not available */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gmc_v9_0_set_gfxhub_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gfxhub.funcs = &gfxhub_v1_0_funcs;
पूर्ण

अटल पूर्णांक gmc_v9_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->asic_type == CHIP_VEGA20 ||
	    adev->asic_type == CHIP_ARCTURUS)
		adev->gmc.xgmi.supported = true;

	अगर (adev->asic_type == CHIP_ALDEBARAN) अणु
		adev->gmc.xgmi.supported = true;
		adev->gmc.xgmi.connected_to_cpu =
			adev->smuio.funcs->is_host_gpu_xgmi_supported(adev);
	पूर्ण

	gmc_v9_0_set_gmc_funcs(adev);
	gmc_v9_0_set_irq_funcs(adev);
	gmc_v9_0_set_umc_funcs(adev);
	gmc_v9_0_set_mmhub_funcs(adev);
	gmc_v9_0_set_mmhub_ras_funcs(adev);
	gmc_v9_0_set_gfxhub_funcs(adev);

	adev->gmc.shared_aperture_start = 0x2000000000000000ULL;
	adev->gmc.shared_aperture_end =
		adev->gmc.shared_aperture_start + (4ULL << 30) - 1;
	adev->gmc.निजी_aperture_start = 0x1000000000000000ULL;
	adev->gmc.निजी_aperture_end =
		adev->gmc.निजी_aperture_start + (4ULL << 30) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v9_0_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = amdgpu_gmc_allocate_vm_inv_eng(adev);
	अगर (r)
		वापस r;

	/*
	 * Workaround perक्रमmance drop issue with VBIOS enables partial
	 * ग_लिखोs, जबतक disables HBM ECC क्रम vega10.
	 */
	अगर (!amdgpu_sriov_vf(adev) && (adev->asic_type == CHIP_VEGA10)) अणु
		अगर (!(adev->ras_features & (1 << AMDGPU_RAS_BLOCK__UMC))) अणु
			अगर (adev->df.funcs->enable_ecc_क्रमce_par_wr_rmw)
				adev->df.funcs->enable_ecc_क्रमce_par_wr_rmw(adev, false);
		पूर्ण
	पूर्ण

	अगर (adev->mmhub.ras_funcs &&
	    adev->mmhub.ras_funcs->reset_ras_error_count)
		adev->mmhub.ras_funcs->reset_ras_error_count(adev);

	r = amdgpu_gmc_ras_late_init(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_irq_get(adev, &adev->gmc.vm_fault, 0);
पूर्ण

अटल व्योम gmc_v9_0_vram_gtt_location(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_gmc *mc)
अणु
	u64 base = 0;

	अगर (!amdgpu_sriov_vf(adev))
		base = adev->mmhub.funcs->get_fb_location(adev);

	/* add the xgmi offset of the physical node */
	base += adev->gmc.xgmi.physical_node_id * adev->gmc.xgmi.node_segment_size;
	अगर (adev->gmc.xgmi.connected_to_cpu) अणु
		amdgpu_gmc_sysvm_location(adev, mc);
	पूर्ण अन्यथा अणु
		amdgpu_gmc_vram_location(adev, mc, base);
		amdgpu_gmc_gart_location(adev, mc);
		amdgpu_gmc_agp_location(adev, mc);
	पूर्ण
	/* base offset of vram pages */
	adev->vm_manager.vram_base_offset = adev->gfxhub.funcs->get_mc_fb_offset(adev);

	/* XXX: add the xgmi offset of the physical node? */
	adev->vm_manager.vram_base_offset +=
		adev->gmc.xgmi.physical_node_id * adev->gmc.xgmi.node_segment_size;
पूर्ण

/**
 * gmc_v9_0_mc_init - initialize the memory controller driver params
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Look up the amount of vram, vram width, and decide how to place
 * vram and gart within the GPU's physical address space.
 * Returns 0 क्रम success.
 */
अटल पूर्णांक gmc_v9_0_mc_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	/* size in MB on si */
	adev->gmc.mc_vram_size =
		adev->nbio.funcs->get_memsize(adev) * 1024ULL * 1024ULL;
	adev->gmc.real_vram_size = adev->gmc.mc_vram_size;

	अगर (!(adev->flags & AMD_IS_APU) &&
	    !adev->gmc.xgmi.connected_to_cpu) अणु
		r = amdgpu_device_resize_fb_bar(adev);
		अगर (r)
			वापस r;
	पूर्ण
	adev->gmc.aper_base = pci_resource_start(adev->pdev, 0);
	adev->gmc.aper_size = pci_resource_len(adev->pdev, 0);

#अगर_घोषित CONFIG_X86_64
	/*
	 * AMD Accelerated Processing Platक्रमm (APP) supporting GPU-HOST xgmi
	 * पूर्णांकerface can use VRAM through here as it appears प्रणाली reserved
	 * memory in host address space.
	 *
	 * For APUs, VRAM is just the stolen प्रणाली memory and can be accessed
	 * directly.
	 *
	 * Otherwise, use the legacy Host Data Path (HDP) through PCIe BAR.
	 */

	/* check whether both host-gpu and gpu-gpu xgmi links exist */
	अगर ((adev->flags & AMD_IS_APU) ||
	    (adev->gmc.xgmi.supported &&
	     adev->gmc.xgmi.connected_to_cpu)) अणु
		adev->gmc.aper_base =
			adev->gfxhub.funcs->get_mc_fb_offset(adev) +
			adev->gmc.xgmi.physical_node_id *
			adev->gmc.xgmi.node_segment_size;
		adev->gmc.aper_size = adev->gmc.real_vram_size;
	पूर्ण

#पूर्ण_अगर
	/* In हाल the PCI BAR is larger than the actual amount of vram */
	adev->gmc.visible_vram_size = adev->gmc.aper_size;
	अगर (adev->gmc.visible_vram_size > adev->gmc.real_vram_size)
		adev->gmc.visible_vram_size = adev->gmc.real_vram_size;

	/* set the gart size */
	अगर (amdgpu_gart_size == -1) अणु
		चयन (adev->asic_type) अणु
		हाल CHIP_VEGA10:  /* all engines support GPUVM */
		हाल CHIP_VEGA12:  /* all engines support GPUVM */
		हाल CHIP_VEGA20:
		हाल CHIP_ARCTURUS:
		हाल CHIP_ALDEBARAN:
		शेष:
			adev->gmc.gart_size = 512ULL << 20;
			अवरोध;
		हाल CHIP_RAVEN:   /* DCE SG support */
		हाल CHIP_RENOIR:
			adev->gmc.gart_size = 1024ULL << 20;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		adev->gmc.gart_size = (u64)amdgpu_gart_size << 20;
	पूर्ण

	adev->gmc.gart_size += adev->pm.smu_prv_buffer_size;

	gmc_v9_0_vram_gtt_location(adev, &adev->gmc);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v9_0_gart_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->gart.bo) अणु
		WARN(1, "VEGA10 PCIE GART already initialized\n");
		वापस 0;
	पूर्ण

	अगर (adev->gmc.xgmi.connected_to_cpu) अणु
		adev->gmc.vmid0_page_table_depth = 1;
		adev->gmc.vmid0_page_table_block_size = 12;
	पूर्ण अन्यथा अणु
		adev->gmc.vmid0_page_table_depth = 0;
		adev->gmc.vmid0_page_table_block_size = 0;
	पूर्ण

	/* Initialize common gart काष्ठाure */
	r = amdgpu_gart_init(adev);
	अगर (r)
		वापस r;
	adev->gart.table_size = adev->gart.num_gpu_pages * 8;
	adev->gart.gart_pte_flags = AMDGPU_PTE_MTYPE_VG10(MTYPE_UC) |
				 AMDGPU_PTE_EXECUTABLE;

	r = amdgpu_gart_table_vram_alloc(adev);
	अगर (r)
		वापस r;

	अगर (adev->gmc.xgmi.connected_to_cpu) अणु
		r = amdgpu_gmc_pdb0_alloc(adev);
	पूर्ण

	वापस r;
पूर्ण

/**
 * gmc_v9_0_save_रेजिस्टरs - saves regs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * This saves potential रेजिस्टर values that should be
 * restored upon resume
 */
अटल व्योम gmc_v9_0_save_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->asic_type == CHIP_RAVEN)
		adev->gmc.sdpअगर_रेजिस्टर = RREG32_SOC15(DCE, 0, mmDCHUBBUB_SDPIF_MMIO_CNTRL_0);
पूर्ण

अटल पूर्णांक gmc_v9_0_sw_init(व्योम *handle)
अणु
	पूर्णांक r, vram_width = 0, vram_type = 0, vram_venकरोr = 0;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->gfxhub.funcs->init(adev);

	adev->mmhub.funcs->init(adev);

	spin_lock_init(&adev->gmc.invalidate_lock);

	r = amdgpu_atomfirmware_get_vram_info(adev,
		&vram_width, &vram_type, &vram_venकरोr);
	अगर (amdgpu_sriov_vf(adev))
		/* For Vega10 SR-IOV, vram_width can't be पढ़ो from ATOM as RAVEN,
		 * and DF related रेजिस्टरs is not पढ़ोable, seems hardcord is the
		 * only way to set the correct vram_width
		 */
		adev->gmc.vram_width = 2048;
	अन्यथा अगर (amdgpu_emu_mode != 1)
		adev->gmc.vram_width = vram_width;

	अगर (!adev->gmc.vram_width) अणु
		पूर्णांक chansize, numchan;

		/* hbm memory channel size */
		अगर (adev->flags & AMD_IS_APU)
			chansize = 64;
		अन्यथा
			chansize = 128;

		numchan = adev->df.funcs->get_hbm_channel_number(adev);
		adev->gmc.vram_width = numchan * chansize;
	पूर्ण

	adev->gmc.vram_type = vram_type;
	adev->gmc.vram_venकरोr = vram_venकरोr;
	चयन (adev->asic_type) अणु
	हाल CHIP_RAVEN:
		adev->num_vmhubs = 2;

		अगर (adev->rev_id == 0x0 || adev->rev_id == 0x1) अणु
			amdgpu_vm_adjust_size(adev, 256 * 1024, 9, 3, 48);
		पूर्ण अन्यथा अणु
			/* vm_size is 128TB + 512GB क्रम legacy 3-level page support */
			amdgpu_vm_adjust_size(adev, 128 * 1024 + 512, 9, 2, 48);
			adev->gmc.translate_further =
				adev->vm_manager.num_level > 1;
		पूर्ण
		अवरोध;
	हाल CHIP_VEGA10:
	हाल CHIP_VEGA12:
	हाल CHIP_VEGA20:
	हाल CHIP_RENOIR:
	हाल CHIP_ALDEBARAN:
		adev->num_vmhubs = 2;


		/*
		 * To fulfill 4-level page support,
		 * vm size is 256TB (48bit), maximum size of Vega10,
		 * block size 512 (9bit)
		 */
		/* sriov restrict max_pfn below AMDGPU_GMC_HOLE */
		अगर (amdgpu_sriov_vf(adev))
			amdgpu_vm_adjust_size(adev, 256 * 1024, 9, 3, 47);
		अन्यथा
			amdgpu_vm_adjust_size(adev, 256 * 1024, 9, 3, 48);
		अवरोध;
	हाल CHIP_ARCTURUS:
		adev->num_vmhubs = 3;

		/* Keep the vm size same with Vega20 */
		amdgpu_vm_adjust_size(adev, 256 * 1024, 9, 3, 48);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* This पूर्णांकerrupt is VMC page fault.*/
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VMC, VMC_1_0__SRCID__VM_FAULT,
				&adev->gmc.vm_fault);
	अगर (r)
		वापस r;

	अगर (adev->asic_type == CHIP_ARCTURUS) अणु
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VMC1, VMC_1_0__SRCID__VM_FAULT,
					&adev->gmc.vm_fault);
		अगर (r)
			वापस r;
	पूर्ण

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_UTCL2, UTCL2_1_0__SRCID__FAULT,
				&adev->gmc.vm_fault);

	अगर (r)
		वापस r;

	अगर (!amdgpu_sriov_vf(adev) &&
	    !adev->gmc.xgmi.connected_to_cpu) अणु
		/* पूर्णांकerrupt sent to DF. */
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_DF, 0,
				      &adev->gmc.ecc_irq);
		अगर (r)
			वापस r;
	पूर्ण

	/* Set the पूर्णांकernal MC address mask
	 * This is the max address of the GPU's
	 * पूर्णांकernal address space.
	 */
	adev->gmc.mc_mask = 0xffffffffffffULL; /* 48 bit MC */

	r = dma_set_mask_and_coherent(adev->dev, DMA_BIT_MASK(44));
	अगर (r) अणु
		prपूर्णांकk(KERN_WARNING "amdgpu: No suitable DMA available.\n");
		वापस r;
	पूर्ण
	adev->need_swiotlb = drm_need_swiotlb(44);

	अगर (adev->gmc.xgmi.supported) अणु
		r = adev->gfxhub.funcs->get_xgmi_info(adev);
		अगर (r)
			वापस r;
	पूर्ण

	r = gmc_v9_0_mc_init(adev);
	अगर (r)
		वापस r;

	amdgpu_gmc_get_vbios_allocations(adev);

	/* Memory manager */
	r = amdgpu_bo_init(adev);
	अगर (r)
		वापस r;

	r = gmc_v9_0_gart_init(adev);
	अगर (r)
		वापस r;

	/*
	 * number of VMs
	 * VMID 0 is reserved क्रम System
	 * amdgpu graphics/compute will use VMIDs 1..n-1
	 * amdkfd will use VMIDs n..15
	 *
	 * The first KFD VMID is 8 क्रम GPUs with graphics, 3 क्रम
	 * compute-only GPUs. On compute-only GPUs that leaves 2 VMIDs
	 * क्रम video processing.
	 */
	adev->vm_manager.first_kfd_vmid =
		(adev->asic_type == CHIP_ARCTURUS ||
		 adev->asic_type == CHIP_ALDEBARAN) ? 3 : 8;

	amdgpu_vm_manager_init(adev);

	gmc_v9_0_save_रेजिस्टरs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v9_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_gmc_ras_fini(adev);
	amdgpu_gem_क्रमce_release(adev);
	amdgpu_vm_manager_fini(adev);
	amdgpu_gart_table_vram_मुक्त(adev);
	amdgpu_bo_unref(&adev->gmc.pdb0_bo);
	amdgpu_bo_fini(adev);
	amdgpu_gart_fini(adev);

	वापस 0;
पूर्ण

अटल व्योम gmc_v9_0_init_golden_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु

	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA10:
		अगर (amdgpu_sriov_vf(adev))
			अवरोध;
		fallthrough;
	हाल CHIP_VEGA20:
		soc15_program_रेजिस्टर_sequence(adev,
						golden_settings_mmhub_1_0_0,
						ARRAY_SIZE(golden_settings_mmhub_1_0_0));
		soc15_program_रेजिस्टर_sequence(adev,
						golden_settings_athub_1_0_0,
						ARRAY_SIZE(golden_settings_athub_1_0_0));
		अवरोध;
	हाल CHIP_VEGA12:
		अवरोध;
	हाल CHIP_RAVEN:
		/* TODO क्रम renoir */
		soc15_program_रेजिस्टर_sequence(adev,
						golden_settings_athub_1_0_0,
						ARRAY_SIZE(golden_settings_athub_1_0_0));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * gmc_v9_0_restore_रेजिस्टरs - restores regs
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * This restores रेजिस्टर values, saved at suspend.
 */
व्योम gmc_v9_0_restore_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->asic_type == CHIP_RAVEN) अणु
		WREG32_SOC15(DCE, 0, mmDCHUBBUB_SDPIF_MMIO_CNTRL_0, adev->gmc.sdpअगर_रेजिस्टर);
		WARN_ON(adev->gmc.sdpअगर_रेजिस्टर !=
			RREG32_SOC15(DCE, 0, mmDCHUBBUB_SDPIF_MMIO_CNTRL_0));
	पूर्ण
पूर्ण

/**
 * gmc_v9_0_gart_enable - gart enable
 *
 * @adev: amdgpu_device poपूर्णांकer
 */
अटल पूर्णांक gmc_v9_0_gart_enable(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->gmc.xgmi.connected_to_cpu)
		amdgpu_gmc_init_pdb0(adev);

	अगर (adev->gart.bo == शून्य) अणु
		dev_err(adev->dev, "No VRAM object for PCIE GART.\n");
		वापस -EINVAL;
	पूर्ण

	r = amdgpu_gart_table_vram_pin(adev);
	अगर (r)
		वापस r;

	r = adev->gfxhub.funcs->gart_enable(adev);
	अगर (r)
		वापस r;

	r = adev->mmhub.funcs->gart_enable(adev);
	अगर (r)
		वापस r;

	DRM_INFO("PCIE GART of %uM enabled.\n",
		 (अचिन्हित)(adev->gmc.gart_size >> 20));
	अगर (adev->gmc.pdb0_bo)
		DRM_INFO("PDB0 located at 0x%016llX\n",
				(अचिन्हित दीर्घ दीर्घ)amdgpu_bo_gpu_offset(adev->gmc.pdb0_bo));
	DRM_INFO("PTB located at 0x%016llX\n",
			(अचिन्हित दीर्घ दीर्घ)amdgpu_bo_gpu_offset(adev->gart.bo));

	adev->gart.पढ़ोy = true;
	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v9_0_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool value;
	पूर्णांक r, i;

	/* The sequence of these two function calls matters.*/
	gmc_v9_0_init_golden_रेजिस्टरs(adev);

	अगर (adev->mode_info.num_crtc) अणु
		/* Lockout access through VGA aperture*/
		WREG32_FIELD15(DCE, 0, VGA_HDP_CONTROL, VGA_MEMORY_DISABLE, 1);
		/* disable VGA render */
		WREG32_FIELD15(DCE, 0, VGA_RENDER_CONTROL, VGA_VSTATUS_CNTL, 0);
	पूर्ण

	अगर (adev->mmhub.funcs->update_घातer_gating)
		adev->mmhub.funcs->update_घातer_gating(adev, true);

	adev->hdp.funcs->init_रेजिस्टरs(adev);

	/* After HDP is initialized, flush HDP.*/
	adev->hdp.funcs->flush_hdp(adev, शून्य);

	अगर (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_ALWAYS)
		value = false;
	अन्यथा
		value = true;

	अगर (!amdgpu_sriov_vf(adev)) अणु
		adev->gfxhub.funcs->set_fault_enable_शेष(adev, value);
		adev->mmhub.funcs->set_fault_enable_शेष(adev, value);
	पूर्ण
	क्रम (i = 0; i < adev->num_vmhubs; ++i)
		gmc_v9_0_flush_gpu_tlb(adev, 0, i, 0);

	अगर (adev->umc.funcs && adev->umc.funcs->init_रेजिस्टरs)
		adev->umc.funcs->init_रेजिस्टरs(adev);

	r = gmc_v9_0_gart_enable(adev);

	वापस r;
पूर्ण

/**
 * gmc_v9_0_gart_disable - gart disable
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * This disables all VM page table.
 */
अटल व्योम gmc_v9_0_gart_disable(काष्ठा amdgpu_device *adev)
अणु
	adev->gfxhub.funcs->gart_disable(adev);
	adev->mmhub.funcs->gart_disable(adev);
	amdgpu_gart_table_vram_unpin(adev);
पूर्ण

अटल पूर्णांक gmc_v9_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev)) अणु
		/* full access mode, so करोn't touch any GMC रेजिस्टर */
		DRM_DEBUG("For SRIOV client, shouldn't do anything.\n");
		वापस 0;
	पूर्ण

	amdgpu_irq_put(adev, &adev->gmc.ecc_irq, 0);
	amdgpu_irq_put(adev, &adev->gmc.vm_fault, 0);
	gmc_v9_0_gart_disable(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v9_0_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस gmc_v9_0_hw_fini(adev);
पूर्ण

अटल पूर्णांक gmc_v9_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = gmc_v9_0_hw_init(adev);
	अगर (r)
		वापस r;

	amdgpu_vmid_reset_all(adev);

	वापस 0;
पूर्ण

अटल bool gmc_v9_0_is_idle(व्योम *handle)
अणु
	/* MC is always पढ़ोy in GMC v9.*/
	वापस true;
पूर्ण

अटल पूर्णांक gmc_v9_0_रुको_क्रम_idle(व्योम *handle)
अणु
	/* There is no need to रुको क्रम MC idle in GMC v9.*/
	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v9_0_soft_reset(व्योम *handle)
अणु
	/* XXX क्रम emulation.*/
	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v9_0_set_घड़ीgating_state(व्योम *handle,
					क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->mmhub.funcs->set_घड़ीgating(adev, state);

	athub_v1_0_set_घड़ीgating(adev, state);

	वापस 0;
पूर्ण

अटल व्योम gmc_v9_0_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->mmhub.funcs->get_घड़ीgating(adev, flags);

	athub_v1_0_get_घड़ीgating(adev, flags);
पूर्ण

अटल पूर्णांक gmc_v9_0_set_घातergating_state(व्योम *handle,
					क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

स्थिर काष्ठा amd_ip_funcs gmc_v9_0_ip_funcs = अणु
	.name = "gmc_v9_0",
	.early_init = gmc_v9_0_early_init,
	.late_init = gmc_v9_0_late_init,
	.sw_init = gmc_v9_0_sw_init,
	.sw_fini = gmc_v9_0_sw_fini,
	.hw_init = gmc_v9_0_hw_init,
	.hw_fini = gmc_v9_0_hw_fini,
	.suspend = gmc_v9_0_suspend,
	.resume = gmc_v9_0_resume,
	.is_idle = gmc_v9_0_is_idle,
	.रुको_क्रम_idle = gmc_v9_0_रुको_क्रम_idle,
	.soft_reset = gmc_v9_0_soft_reset,
	.set_घड़ीgating_state = gmc_v9_0_set_घड़ीgating_state,
	.set_घातergating_state = gmc_v9_0_set_घातergating_state,
	.get_घड़ीgating_state = gmc_v9_0_get_घड़ीgating_state,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version gmc_v9_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GMC,
	.major = 9,
	.minor = 0,
	.rev = 0,
	.funcs = &gmc_v9_0_ip_funcs,
पूर्ण;
