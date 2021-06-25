<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_psp.h"
#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_ucode.h"
#समावेश "soc15_common.h"
#समावेश "psp_v11_0.h"

#समावेश "mp/mp_11_0_offset.h"
#समावेश "mp/mp_11_0_sh_mask.h"
#समावेश "gc/gc_9_0_offset.h"
#समावेश "sdma0/sdma0_4_0_offset.h"
#समावेश "nbio/nbio_7_4_offset.h"

#समावेश "oss/osssys_4_0_offset.h"
#समावेश "oss/osssys_4_0_sh_mask.h"

MODULE_FIRMWARE("amdgpu/vega20_sos.bin");
MODULE_FIRMWARE("amdgpu/vega20_asd.bin");
MODULE_FIRMWARE("amdgpu/vega20_ta.bin");
MODULE_FIRMWARE("amdgpu/navi10_sos.bin");
MODULE_FIRMWARE("amdgpu/navi10_asd.bin");
MODULE_FIRMWARE("amdgpu/navi10_ta.bin");
MODULE_FIRMWARE("amdgpu/navi14_sos.bin");
MODULE_FIRMWARE("amdgpu/navi14_asd.bin");
MODULE_FIRMWARE("amdgpu/navi14_ta.bin");
MODULE_FIRMWARE("amdgpu/navi12_sos.bin");
MODULE_FIRMWARE("amdgpu/navi12_asd.bin");
MODULE_FIRMWARE("amdgpu/navi12_ta.bin");
MODULE_FIRMWARE("amdgpu/arcturus_sos.bin");
MODULE_FIRMWARE("amdgpu/arcturus_asd.bin");
MODULE_FIRMWARE("amdgpu/arcturus_ta.bin");
MODULE_FIRMWARE("amdgpu/sienna_cichlid_sos.bin");
MODULE_FIRMWARE("amdgpu/sienna_cichlid_ta.bin");
MODULE_FIRMWARE("amdgpu/navy_flounder_sos.bin");
MODULE_FIRMWARE("amdgpu/navy_flounder_ta.bin");
MODULE_FIRMWARE("amdgpu/vangogh_asd.bin");
MODULE_FIRMWARE("amdgpu/vangogh_toc.bin");
MODULE_FIRMWARE("amdgpu/dimgrey_cavefish_sos.bin");
MODULE_FIRMWARE("amdgpu/dimgrey_cavefish_ta.bin");

/* address block */
#घोषणा smnMP1_FIRMWARE_FLAGS		0x3010024
/* navi10 reg offset define */
#घोषणा mmRLC_GPM_UCODE_ADDR_NV10	0x5b61
#घोषणा mmRLC_GPM_UCODE_DATA_NV10	0x5b62
#घोषणा mmSDMA0_UCODE_ADDR_NV10		0x5880
#घोषणा mmSDMA0_UCODE_DATA_NV10		0x5881
/* memory training समयout define */
#घोषणा MEM_TRAIN_SEND_MSG_TIMEOUT_US	3000000

/* For large FW files the समय to complete can be very दीर्घ */
#घोषणा USBC_PD_POLLING_LIMIT_S 240

अटल पूर्णांक psp_v11_0_init_microcode(काष्ठा psp_context *psp)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[PSP_FW_NAME_LEN];
	पूर्णांक err = 0;
	स्थिर काष्ठा ta_firmware_header_v1_0 *ta_hdr;

	DRM_DEBUG("\n");

	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA20:
		chip_name = "vega20";
		अवरोध;
	हाल CHIP_NAVI10:
		chip_name = "navi10";
		अवरोध;
	हाल CHIP_NAVI14:
		chip_name = "navi14";
		अवरोध;
	हाल CHIP_NAVI12:
		chip_name = "navi12";
		अवरोध;
	हाल CHIP_ARCTURUS:
		chip_name = "arcturus";
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
		chip_name = "sienna_cichlid";
		अवरोध;
	हाल CHIP_NAVY_FLOUNDER:
		chip_name = "navy_flounder";
		अवरोध;
	हाल CHIP_VANGOGH:
		chip_name = "vangogh";
		अवरोध;
	हाल CHIP_DIMGREY_CAVEFISH:
		chip_name = "dimgrey_cavefish";
		अवरोध;
	शेष:
		BUG();
	पूर्ण


	चयन (adev->asic_type) अणु
	हाल CHIP_VEGA20:
	हाल CHIP_ARCTURUS:
		err = psp_init_sos_microcode(psp, chip_name);
		अगर (err)
			वापस err;
		err = psp_init_asd_microcode(psp, chip_name);
		अगर (err)
			वापस err;
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_ta.bin", chip_name);
		err = request_firmware(&adev->psp.ta_fw, fw_name, adev->dev);
		अगर (err) अणु
			release_firmware(adev->psp.ta_fw);
			adev->psp.ta_fw = शून्य;
			dev_info(adev->dev,
				 "psp v11.0: Failed to load firmware \"%s\"\n", fw_name);
		पूर्ण अन्यथा अणु
			err = amdgpu_ucode_validate(adev->psp.ta_fw);
			अगर (err)
				जाओ out2;

			ta_hdr = (स्थिर काष्ठा ta_firmware_header_v1_0 *)adev->psp.ta_fw->data;
			adev->psp.ta_xgmi_ucode_version = le32_to_cpu(ta_hdr->ta_xgmi_ucode_version);
			adev->psp.ta_xgmi_ucode_size = le32_to_cpu(ta_hdr->ta_xgmi_size_bytes);
			adev->psp.ta_xgmi_start_addr = (uपूर्णांक8_t *)ta_hdr +
				le32_to_cpu(ta_hdr->header.ucode_array_offset_bytes);
			adev->psp.ta_fw_version = le32_to_cpu(ta_hdr->header.ucode_version);
			adev->psp.ta_ras_ucode_version = le32_to_cpu(ta_hdr->ta_ras_ucode_version);
			adev->psp.ta_ras_ucode_size = le32_to_cpu(ta_hdr->ta_ras_size_bytes);
			adev->psp.ta_ras_start_addr = (uपूर्णांक8_t *)adev->psp.ta_xgmi_start_addr +
				le32_to_cpu(ta_hdr->ta_ras_offset_bytes);
		पूर्ण
		अवरोध;
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
		err = psp_init_sos_microcode(psp, chip_name);
		अगर (err)
			वापस err;
		err = psp_init_asd_microcode(psp, chip_name);
		अगर (err)
			वापस err;
		अगर (amdgpu_sriov_vf(adev))
			अवरोध;
		snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_ta.bin", chip_name);
		err = request_firmware(&adev->psp.ta_fw, fw_name, adev->dev);
		अगर (err) अणु
			release_firmware(adev->psp.ta_fw);
			adev->psp.ta_fw = शून्य;
			dev_info(adev->dev,
				 "psp v11.0: Failed to load firmware \"%s\"\n", fw_name);
		पूर्ण अन्यथा अणु
			err = amdgpu_ucode_validate(adev->psp.ta_fw);
			अगर (err)
				जाओ out2;

			ta_hdr = (स्थिर काष्ठा ta_firmware_header_v1_0 *)adev->psp.ta_fw->data;
			adev->psp.ta_hdcp_ucode_version = le32_to_cpu(ta_hdr->ta_hdcp_ucode_version);
			adev->psp.ta_hdcp_ucode_size = le32_to_cpu(ta_hdr->ta_hdcp_size_bytes);
			adev->psp.ta_hdcp_start_addr = (uपूर्णांक8_t *)ta_hdr +
				le32_to_cpu(ta_hdr->header.ucode_array_offset_bytes);

			adev->psp.ta_fw_version = le32_to_cpu(ta_hdr->header.ucode_version);

			adev->psp.ta_dपंचांग_ucode_version = le32_to_cpu(ta_hdr->ta_dपंचांग_ucode_version);
			adev->psp.ta_dपंचांग_ucode_size = le32_to_cpu(ta_hdr->ta_dपंचांग_size_bytes);
			adev->psp.ta_dपंचांग_start_addr = (uपूर्णांक8_t *)adev->psp.ta_hdcp_start_addr +
				le32_to_cpu(ta_hdr->ta_dपंचांग_offset_bytes);
		पूर्ण
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
		err = psp_init_sos_microcode(psp, chip_name);
		अगर (err)
			वापस err;
		err = psp_init_ta_microcode(psp, chip_name);
		अगर (err)
			वापस err;
		अवरोध;
	हाल CHIP_VANGOGH:
		err = psp_init_asd_microcode(psp, chip_name);
		अगर (err)
			वापस err;
		err = psp_init_toc_microcode(psp, chip_name);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस 0;

out2:
	release_firmware(adev->psp.ta_fw);
	adev->psp.ta_fw = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक psp_v11_0_रुको_क्रम_bootloader(काष्ठा psp_context *psp)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;

	पूर्णांक ret;
	पूर्णांक retry_loop;

	क्रम (retry_loop = 0; retry_loop < 10; retry_loop++) अणु
		/* Wait क्रम bootloader to signअगरy that is
		    पढ़ोy having bit 31 of C2PMSG_35 set to 1 */
		ret = psp_रुको_क्रम(psp,
				   SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
				   0x80000000,
				   0x80000000,
				   false);

		अगर (ret == 0)
			वापस 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool psp_v11_0_is_sos_alive(काष्ठा psp_context *psp)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	uपूर्णांक32_t sol_reg;

	sol_reg = RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81);

	वापस sol_reg != 0x0;
पूर्ण

अटल पूर्णांक psp_v11_0_bootloader_load_kdb(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t psp_gfxdrv_command_reg = 0;
	काष्ठा amdgpu_device *adev = psp->adev;

	/* Check tOS sign of lअगरe रेजिस्टर to confirm sys driver and sOS
	 * are alपढ़ोy been loaded.
	 */
	अगर (psp_v11_0_is_sos_alive(psp))
		वापस 0;

	ret = psp_v11_0_रुको_क्रम_bootloader(psp);
	अगर (ret)
		वापस ret;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);

	/* Copy PSP KDB binary to memory */
	स_नकल(psp->fw_pri_buf, psp->kdb_start_addr, psp->kdb_bin_size);

	/* Provide the PSP KDB to bootloader */
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36,
	       (uपूर्णांक32_t)(psp->fw_pri_mc_addr >> 20));
	psp_gfxdrv_command_reg = PSP_BL__LOAD_KEY_DATABASE;
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35,
	       psp_gfxdrv_command_reg);

	ret = psp_v11_0_रुको_क्रम_bootloader(psp);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_v11_0_bootloader_load_spl(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t psp_gfxdrv_command_reg = 0;
	काष्ठा amdgpu_device *adev = psp->adev;

	/* Check tOS sign of lअगरe रेजिस्टर to confirm sys driver and sOS
	 * are alपढ़ोy been loaded.
	 */
	अगर (psp_v11_0_is_sos_alive(psp))
		वापस 0;

	ret = psp_v11_0_रुको_क्रम_bootloader(psp);
	अगर (ret)
		वापस ret;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);

	/* Copy PSP SPL binary to memory */
	स_नकल(psp->fw_pri_buf, psp->spl_start_addr, psp->spl_bin_size);

	/* Provide the PSP SPL to bootloader */
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36,
	       (uपूर्णांक32_t)(psp->fw_pri_mc_addr >> 20));
	psp_gfxdrv_command_reg = PSP_BL__LOAD_TOS_SPL_TABLE;
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35,
	       psp_gfxdrv_command_reg);

	ret = psp_v11_0_रुको_क्रम_bootloader(psp);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_v11_0_bootloader_load_sysdrv(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t psp_gfxdrv_command_reg = 0;
	काष्ठा amdgpu_device *adev = psp->adev;

	/* Check sOS sign of lअगरe रेजिस्टर to confirm sys driver and sOS
	 * are alपढ़ोy been loaded.
	 */
	अगर (psp_v11_0_is_sos_alive(psp))
		वापस 0;

	ret = psp_v11_0_रुको_क्रम_bootloader(psp);
	अगर (ret)
		वापस ret;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);

	/* Copy PSP System Driver binary to memory */
	स_नकल(psp->fw_pri_buf, psp->sys_start_addr, psp->sys_bin_size);

	/* Provide the sys driver to bootloader */
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36,
	       (uपूर्णांक32_t)(psp->fw_pri_mc_addr >> 20));
	psp_gfxdrv_command_reg = PSP_BL__LOAD_SYSDRV;
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35,
	       psp_gfxdrv_command_reg);

	/* there might be handshake issue with hardware which needs delay */
	mdelay(20);

	ret = psp_v11_0_रुको_क्रम_bootloader(psp);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_v11_0_bootloader_load_sos(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक psp_gfxdrv_command_reg = 0;
	काष्ठा amdgpu_device *adev = psp->adev;

	/* Check sOS sign of lअगरe रेजिस्टर to confirm sys driver and sOS
	 * are alपढ़ोy been loaded.
	 */
	अगर (psp_v11_0_is_sos_alive(psp))
		वापस 0;

	ret = psp_v11_0_रुको_क्रम_bootloader(psp);
	अगर (ret)
		वापस ret;

	स_रखो(psp->fw_pri_buf, 0, PSP_1_MEG);

	/* Copy Secure OS binary to PSP memory */
	स_नकल(psp->fw_pri_buf, psp->sos_start_addr, psp->sos_bin_size);

	/* Provide the PSP secure OS to bootloader */
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36,
	       (uपूर्णांक32_t)(psp->fw_pri_mc_addr >> 20));
	psp_gfxdrv_command_reg = PSP_BL__LOAD_SOSDRV;
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35,
	       psp_gfxdrv_command_reg);

	/* there might be handshake issue with hardware which needs delay */
	mdelay(20);
	ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_81),
			   RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_81),
			   0, true);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_v11_0_ring_init(काष्ठा psp_context *psp,
			      क्रमागत psp_ring_type ring_type)
अणु
	पूर्णांक ret = 0;
	काष्ठा psp_ring *ring;
	काष्ठा amdgpu_device *adev = psp->adev;

	ring = &psp->km_ring;

	ring->ring_type = ring_type;

	/* allocate 4k Page of Local Frame Buffer memory क्रम ring */
	ring->ring_size = 0x1000;
	ret = amdgpu_bo_create_kernel(adev, ring->ring_size, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &adev->firmware.rbuf,
				      &ring->ring_mem_mc_addr,
				      (व्योम **)&ring->ring_mem);
	अगर (ret) अणु
		ring->ring_size = 0;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_v11_0_ring_stop(काष्ठा psp_context *psp,
			      क्रमागत psp_ring_type ring_type)
अणु
	पूर्णांक ret = 0;
	काष्ठा amdgpu_device *adev = psp->adev;

	/* Write the ring destroy command*/
	अगर (amdgpu_sriov_vf(adev))
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101,
				     GFX_CTRL_CMD_ID_DESTROY_GPCOM_RING);
	अन्यथा
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64,
				     GFX_CTRL_CMD_ID_DESTROY_RINGS);

	/* there might be handshake issue with hardware which needs delay */
	mdelay(20);

	/* Wait क्रम response flag (bit 31) */
	अगर (amdgpu_sriov_vf(adev))
		ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_101),
				   0x80000000, 0x80000000, false);
	अन्यथा
		ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, false);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_v11_0_ring_create(काष्ठा psp_context *psp,
				क्रमागत psp_ring_type ring_type)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक psp_ring_reg = 0;
	काष्ठा psp_ring *ring = &psp->km_ring;
	काष्ठा amdgpu_device *adev = psp->adev;

	अगर (amdgpu_sriov_vf(adev)) अणु
		ret = psp_v11_0_ring_stop(psp, ring_type);
		अगर (ret) अणु
			DRM_ERROR("psp_v11_0_ring_stop_sriov failed!\n");
			वापस ret;
		पूर्ण

		/* Write low address of the ring to C2PMSG_102 */
		psp_ring_reg = lower_32_bits(ring->ring_mem_mc_addr);
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_102, psp_ring_reg);
		/* Write high address of the ring to C2PMSG_103 */
		psp_ring_reg = upper_32_bits(ring->ring_mem_mc_addr);
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_103, psp_ring_reg);

		/* Write the ring initialization command to C2PMSG_101 */
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101,
					     GFX_CTRL_CMD_ID_INIT_GPCOM_RING);

		/* there might be handshake issue with hardware which needs delay */
		mdelay(20);

		/* Wait क्रम response flag (bit 31) in C2PMSG_101 */
		ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_101),
				   0x80000000, 0x8000FFFF, false);

	पूर्ण अन्यथा अणु
		/* Wait क्रम sOS पढ़ोy क्रम ring creation */
		ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x80000000, false);
		अगर (ret) अणु
			DRM_ERROR("Failed to wait for sOS ready for ring creation\n");
			वापस ret;
		पूर्ण

		/* Write low address of the ring to C2PMSG_69 */
		psp_ring_reg = lower_32_bits(ring->ring_mem_mc_addr);
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_69, psp_ring_reg);
		/* Write high address of the ring to C2PMSG_70 */
		psp_ring_reg = upper_32_bits(ring->ring_mem_mc_addr);
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_70, psp_ring_reg);
		/* Write size of ring to C2PMSG_71 */
		psp_ring_reg = ring->ring_size;
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_71, psp_ring_reg);
		/* Write the ring initialization command to C2PMSG_64 */
		psp_ring_reg = ring_type;
		psp_ring_reg = psp_ring_reg << 16;
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64, psp_ring_reg);

		/* there might be handshake issue with hardware which needs delay */
		mdelay(20);

		/* Wait क्रम response flag (bit 31) in C2PMSG_64 */
		ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x8000FFFF, false);
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक psp_v11_0_ring_destroy(काष्ठा psp_context *psp,
				 क्रमागत psp_ring_type ring_type)
अणु
	पूर्णांक ret = 0;
	काष्ठा psp_ring *ring = &psp->km_ring;
	काष्ठा amdgpu_device *adev = psp->adev;

	ret = psp_v11_0_ring_stop(psp, ring_type);
	अगर (ret)
		DRM_ERROR("Fail to stop psp ring\n");

	amdgpu_bo_मुक्त_kernel(&adev->firmware.rbuf,
			      &ring->ring_mem_mc_addr,
			      (व्योम **)&ring->ring_mem);

	वापस ret;
पूर्ण

अटल पूर्णांक psp_v11_0_mode1_reset(काष्ठा psp_context *psp)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t offset;
	काष्ठा amdgpu_device *adev = psp->adev;

	offset = SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64);

	ret = psp_रुको_क्रम(psp, offset, 0x80000000, 0x8000FFFF, false);

	अगर (ret) अणु
		DRM_INFO("psp is not working correctly before mode1 reset!\n");
		वापस -EINVAL;
	पूर्ण

	/*send the mode 1 reset command*/
	WREG32(offset, GFX_CTRL_CMD_ID_MODE1_RST);

	msleep(500);

	offset = SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_33);

	ret = psp_रुको_क्रम(psp, offset, 0x80000000, 0x80000000, false);

	अगर (ret) अणु
		DRM_INFO("psp mode 1 reset failed!\n");
		वापस -EINVAL;
	पूर्ण

	DRM_INFO("psp mode1 reset succeed \n");

	वापस 0;
पूर्ण

अटल पूर्णांक psp_v11_0_memory_training_send_msg(काष्ठा psp_context *psp, पूर्णांक msg)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	uपूर्णांक32_t data_32;
	पूर्णांक max_रुको;
	काष्ठा amdgpu_device *adev = psp->adev;

	data_32 = (psp->mem_train_ctx.c2p_train_data_offset >> 20);
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36, data_32);
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35, msg);

	max_रुको = MEM_TRAIN_SEND_MSG_TIMEOUT_US / adev->usec_समयout;
	क्रम (i = 0; i < max_रुको; i++) अणु
		ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
				   0x80000000, 0x80000000, false);
		अगर (ret == 0)
			अवरोध;
	पूर्ण
	अगर (i < max_रुको)
		ret = 0;
	अन्यथा
		ret = -ETIME;

	DRM_DEBUG("training %s %s, cost %d @ %d ms\n",
		  (msg == PSP_BL__DRAM_SHORT_TRAIN) ? "short" : "long",
		  (ret == 0) ? "succeed" : "failed",
		  i, adev->usec_समयout/1000);
	वापस ret;
पूर्ण

/*
 * save and restore process
 */
अटल पूर्णांक psp_v11_0_memory_training(काष्ठा psp_context *psp, uपूर्णांक32_t ops)
अणु
	काष्ठा psp_memory_training_context *ctx = &psp->mem_train_ctx;
	uपूर्णांक32_t *pcache = (uपूर्णांक32_t *)ctx->sys_cache;
	काष्ठा amdgpu_device *adev = psp->adev;
	uपूर्णांक32_t p2c_header[4];
	uपूर्णांक32_t sz;
	व्योम *buf;
	पूर्णांक ret;

	अगर (ctx->init == PSP_MEM_TRAIN_NOT_SUPPORT) अणु
		DRM_DEBUG("Memory training is not supported.\n");
		वापस 0;
	पूर्ण अन्यथा अगर (ctx->init != PSP_MEM_TRAIN_INIT_SUCCESS) अणु
		DRM_ERROR("Memory training initialization failure.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (psp_v11_0_is_sos_alive(psp)) अणु
		DRM_DEBUG("SOS is alive, skip memory training.\n");
		वापस 0;
	पूर्ण

	amdgpu_device_vram_access(adev, ctx->p2c_train_data_offset, p2c_header, माप(p2c_header), false);
	DRM_DEBUG("sys_cache[%08x,%08x,%08x,%08x] p2c_header[%08x,%08x,%08x,%08x]\n",
		  pcache[0], pcache[1], pcache[2], pcache[3],
		  p2c_header[0], p2c_header[1], p2c_header[2], p2c_header[3]);

	अगर (ops & PSP_MEM_TRAIN_SEND_SHORT_MSG) अणु
		DRM_DEBUG("Short training depends on restore.\n");
		ops |= PSP_MEM_TRAIN_RESTORE;
	पूर्ण

	अगर ((ops & PSP_MEM_TRAIN_RESTORE) &&
	    pcache[0] != MEM_TRAIN_SYSTEM_SIGNATURE) अणु
		DRM_DEBUG("sys_cache[0] is invalid, restore depends on save.\n");
		ops |= PSP_MEM_TRAIN_SAVE;
	पूर्ण

	अगर (p2c_header[0] == MEM_TRAIN_SYSTEM_SIGNATURE &&
	    !(pcache[0] == MEM_TRAIN_SYSTEM_SIGNATURE &&
	      pcache[3] == p2c_header[3])) अणु
		DRM_DEBUG("sys_cache is invalid or out-of-date, need save training data to sys_cache.\n");
		ops |= PSP_MEM_TRAIN_SAVE;
	पूर्ण

	अगर ((ops & PSP_MEM_TRAIN_SAVE) &&
	    p2c_header[0] != MEM_TRAIN_SYSTEM_SIGNATURE) अणु
		DRM_DEBUG("p2c_header[0] is invalid, save depends on long training.\n");
		ops |= PSP_MEM_TRAIN_SEND_LONG_MSG;
	पूर्ण

	अगर (ops & PSP_MEM_TRAIN_SEND_LONG_MSG) अणु
		ops &= ~PSP_MEM_TRAIN_SEND_SHORT_MSG;
		ops |= PSP_MEM_TRAIN_SAVE;
	पूर्ण

	DRM_DEBUG("Memory training ops:%x.\n", ops);

	अगर (ops & PSP_MEM_TRAIN_SEND_LONG_MSG) अणु
		/*
		 * Long training will encroach a certain amount on the bottom of VRAM;
		 * save the content from the bottom of VRAM to प्रणाली memory
		 * beक्रमe training, and restore it after training to aव्योम
		 * VRAM corruption.
		 */
		sz = GDDR6_MEM_TRAINING_ENCROACHED_SIZE;

		अगर (adev->gmc.visible_vram_size < sz || !adev->mman.aper_base_kaddr) अणु
			DRM_ERROR("visible_vram_size %llx or aper_base_kaddr %p is not initialized.\n",
				  adev->gmc.visible_vram_size,
				  adev->mman.aper_base_kaddr);
			वापस -EINVAL;
		पूर्ण

		buf = vदो_स्मृति(sz);
		अगर (!buf) अणु
			DRM_ERROR("failed to allocate system memory.\n");
			वापस -ENOMEM;
		पूर्ण

		स_नकल_fromio(buf, adev->mman.aper_base_kaddr, sz);
		ret = psp_v11_0_memory_training_send_msg(psp, PSP_BL__DRAM_LONG_TRAIN);
		अगर (ret) अणु
			DRM_ERROR("Send long training msg failed.\n");
			vमुक्त(buf);
			वापस ret;
		पूर्ण

		स_नकल_toio(adev->mman.aper_base_kaddr, buf, sz);
		adev->hdp.funcs->flush_hdp(adev, शून्य);
		vमुक्त(buf);
	पूर्ण

	अगर (ops & PSP_MEM_TRAIN_SAVE) अणु
		amdgpu_device_vram_access(psp->adev, ctx->p2c_train_data_offset, ctx->sys_cache, ctx->train_data_size, false);
	पूर्ण

	अगर (ops & PSP_MEM_TRAIN_RESTORE) अणु
		amdgpu_device_vram_access(psp->adev, ctx->c2p_train_data_offset, ctx->sys_cache, ctx->train_data_size, true);
	पूर्ण

	अगर (ops & PSP_MEM_TRAIN_SEND_SHORT_MSG) अणु
		ret = psp_v11_0_memory_training_send_msg(psp, (amdgpu_क्रमce_दीर्घ_training > 0) ?
							 PSP_BL__DRAM_LONG_TRAIN : PSP_BL__DRAM_SHORT_TRAIN);
		अगर (ret) अणु
			DRM_ERROR("send training msg failed.\n");
			वापस ret;
		पूर्ण
	पूर्ण
	ctx->training_cnt++;
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t psp_v11_0_ring_get_wptr(काष्ठा psp_context *psp)
अणु
	uपूर्णांक32_t data;
	काष्ठा amdgpu_device *adev = psp->adev;

	अगर (amdgpu_sriov_vf(adev))
		data = psp->km_ring.ring_wptr;
	अन्यथा
		data = RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67);

	वापस data;
पूर्ण

अटल व्योम psp_v11_0_ring_set_wptr(काष्ठा psp_context *psp, uपूर्णांक32_t value)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;

	अगर (amdgpu_sriov_vf(adev)) अणु
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_102, value);
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101, GFX_CTRL_CMD_ID_CONSUME_CMD);
		psp->km_ring.ring_wptr = value;
	पूर्ण अन्यथा
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_67, value);
पूर्ण

अटल पूर्णांक psp_v11_0_load_usbc_pd_fw(काष्ठा psp_context *psp, dma_addr_t dma_addr)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	uपूर्णांक32_t reg_status;
	पूर्णांक ret, i = 0;

	/* Write lower 32-bit address of the PD Controller FW */
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36, lower_32_bits(dma_addr));
	ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
			     0x80000000, 0x80000000, false);
	अगर (ret)
		वापस ret;

	/* Fireup पूर्णांकerrupt so PSP can pick up the lower address */
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35, 0x800000);
	ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
			     0x80000000, 0x80000000, false);
	अगर (ret)
		वापस ret;

	reg_status = RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35);

	अगर ((reg_status & 0xFFFF) != 0) अणु
		DRM_ERROR("Lower address load failed - MP0_SMN_C2PMSG_35.Bits [15:0] = %02x...\n",
				reg_status & 0xFFFF);
		वापस -EIO;
	पूर्ण

	/* Write upper 32-bit address of the PD Controller FW */
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36, upper_32_bits(dma_addr));

	ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
			     0x80000000, 0x80000000, false);
	अगर (ret)
		वापस ret;

	/* Fireup पूर्णांकerrupt so PSP can pick up the upper address */
	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35, 0x4000000);

	/* FW load takes very दीर्घ समय */
	करो अणु
		msleep(1000);
		reg_status = RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35);

		अगर (reg_status & 0x80000000)
			जाओ करोne;

	पूर्ण जबतक (++i < USBC_PD_POLLING_LIMIT_S);

	वापस -ETIME;
करोne:

	अगर ((reg_status & 0xFFFF) != 0) अणु
		DRM_ERROR("Upper address load failed - MP0_SMN_C2PMSG_35.Bits [15:0] = x%04x\n",
				reg_status & 0xFFFF);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psp_v11_0_पढ़ो_usbc_pd_fw(काष्ठा psp_context *psp, uपूर्णांक32_t *fw_ver)
अणु
	काष्ठा amdgpu_device *adev = psp->adev;
	पूर्णांक ret;

	WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_35, C2PMSG_CMD_GFX_USB_PD_FW_VER);

	ret = psp_रुको_क्रम(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_35),
				     0x80000000, 0x80000000, false);
	अगर (!ret)
		*fw_ver = RREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_36);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा psp_funcs psp_v11_0_funcs = अणु
	.init_microcode = psp_v11_0_init_microcode,
	.bootloader_load_kdb = psp_v11_0_bootloader_load_kdb,
	.bootloader_load_spl = psp_v11_0_bootloader_load_spl,
	.bootloader_load_sysdrv = psp_v11_0_bootloader_load_sysdrv,
	.bootloader_load_sos = psp_v11_0_bootloader_load_sos,
	.ring_init = psp_v11_0_ring_init,
	.ring_create = psp_v11_0_ring_create,
	.ring_stop = psp_v11_0_ring_stop,
	.ring_destroy = psp_v11_0_ring_destroy,
	.mode1_reset = psp_v11_0_mode1_reset,
	.mem_training = psp_v11_0_memory_training,
	.ring_get_wptr = psp_v11_0_ring_get_wptr,
	.ring_set_wptr = psp_v11_0_ring_set_wptr,
	.load_usbc_pd_fw = psp_v11_0_load_usbc_pd_fw,
	.पढ़ो_usbc_pd_fw = psp_v11_0_पढ़ो_usbc_pd_fw
पूर्ण;

व्योम psp_v11_0_set_psp_funcs(काष्ठा psp_context *psp)
अणु
	psp->funcs = &psp_v11_0_funcs;
पूर्ण
