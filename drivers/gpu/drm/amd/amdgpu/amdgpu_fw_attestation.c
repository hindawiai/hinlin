<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#समावेश <linux/debugfs.h>
#समावेश <linux/firmware.h>
#समावेश <linux/dma-mapping.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_fw_attestation.h"
#समावेश "amdgpu_psp.h"
#समावेश "amdgpu_ucode.h"
#समावेश "soc15_common.h"

#घोषणा FW_ATTESTATION_DB_COOKIE        0x143b6a37
#घोषणा FW_ATTESTATION_RECORD_VALID  	1
#घोषणा FW_ATTESTATION_MAX_SIZE		4096

प्रकार काष्ठा FW_ATT_DB_HEADER
अणु
	uपूर्णांक32_t AttDbVersion;           /* version of the fwar feature */
	uपूर्णांक32_t AttDbCookie;            /* cookie as an extra check क्रम corrupt data */
पूर्ण FW_ATT_DB_HEADER;

प्रकार काष्ठा FW_ATT_RECORD
अणु
	uपूर्णांक16_t AttFwIdV1;              /* Legacy FW Type field */
	uपूर्णांक16_t AttFwIdV2;              /* V2 FW ID field */
	uपूर्णांक32_t AttFWVersion;           /* FW Version */
	uपूर्णांक16_t AttFWActiveFunctionID;  /* The VF ID (only in VF Attestation Table) */
	uपूर्णांक8_t  AttSource;              /* FW source indicator */
	uपूर्णांक8_t  RecordValid;            /* Indicates whether the record is a valid entry */
	uपूर्णांक32_t AttFwTaId;              /* Ta ID (only in TA Attestation Table) */
पूर्ण FW_ATT_RECORD;

अटल sमाप_प्रकार amdgpu_fw_attestation_debugfs_पढ़ो(काष्ठा file *f,
						  अक्षर __user *buf,
						  माप_प्रकार size,
						  loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)file_inode(f)->i_निजी;
	uपूर्णांक64_t records_addr = 0;
	uपूर्णांक64_t vram_pos = 0;
	FW_ATT_DB_HEADER fw_att_hdr = अणु0पूर्ण;
	FW_ATT_RECORD fw_att_record = अणु0पूर्ण;

	अगर (size < माप(FW_ATT_RECORD)) अणु
		DRM_WARN("FW attestation input buffer not enough memory");
		वापस -EINVAL;
	पूर्ण

	अगर ((*pos + माप(FW_ATT_DB_HEADER)) >= FW_ATTESTATION_MAX_SIZE) अणु
		DRM_WARN("FW attestation out of bounds");
		वापस 0;
	पूर्ण

	अगर (psp_get_fw_attestation_records_addr(&adev->psp, &records_addr)) अणु
		DRM_WARN("Failed to get FW attestation record address");
		वापस -EINVAL;
	पूर्ण

	vram_pos =  records_addr - adev->gmc.vram_start;

	अगर (*pos == 0) अणु
		amdgpu_device_vram_access(adev,
					  vram_pos,
					  (uपूर्णांक32_t*)&fw_att_hdr,
					  माप(FW_ATT_DB_HEADER),
					  false);

		अगर (fw_att_hdr.AttDbCookie != FW_ATTESTATION_DB_COOKIE) अणु
			DRM_WARN("Invalid FW attestation cookie");
			वापस -EINVAL;
		पूर्ण

		DRM_INFO("FW attestation version = 0x%X", fw_att_hdr.AttDbVersion);
	पूर्ण

	amdgpu_device_vram_access(adev,
				  vram_pos + माप(FW_ATT_DB_HEADER) + *pos,
				  (uपूर्णांक32_t*)&fw_att_record,
				  माप(FW_ATT_RECORD),
				  false);

	अगर (fw_att_record.RecordValid != FW_ATTESTATION_RECORD_VALID)
		वापस 0;

	अगर (copy_to_user(buf, (व्योम*)&fw_att_record, माप(FW_ATT_RECORD)))
		वापस -EINVAL;

	*pos += माप(FW_ATT_RECORD);

	वापस माप(FW_ATT_RECORD);
पूर्ण

अटल स्थिर काष्ठा file_operations amdgpu_fw_attestation_debugfs_ops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_fw_attestation_debugfs_पढ़ो,
	.ग_लिखो = शून्य,
	.llseek = शेष_llseek
पूर्ण;

अटल पूर्णांक amdgpu_is_fw_attestation_supported(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->asic_type >= CHIP_SIENNA_CICHLID)
		वापस 1;

	वापस 0;
पूर्ण

व्योम amdgpu_fw_attestation_debugfs_init(काष्ठा amdgpu_device *adev)
अणु
	अगर (!amdgpu_is_fw_attestation_supported(adev))
		वापस;

	debugfs_create_file("amdgpu_fw_attestation",
			    S_IRUSR,
			    adev_to_drm(adev)->primary->debugfs_root,
			    adev,
			    &amdgpu_fw_attestation_debugfs_ops);
पूर्ण
