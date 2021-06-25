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
 *
 */

#समावेश "amdgpu.h"
#समावेश "amdgpu_discovery.h"
#समावेश "soc15_hw_ip.h"
#समावेश "discovery.h"

#घोषणा mmRCC_CONFIG_MEMSIZE	0xde3
#घोषणा mmMM_INDEX		0x0
#घोषणा mmMM_INDEX_HI		0x6
#घोषणा mmMM_DATA		0x1
#घोषणा HW_ID_MAX		300

अटल स्थिर अक्षर *hw_id_names[HW_ID_MAX] = अणु
	[MP1_HWID]		= "MP1",
	[MP2_HWID]		= "MP2",
	[THM_HWID]		= "THM",
	[SMUIO_HWID]		= "SMUIO",
	[FUSE_HWID]		= "FUSE",
	[CLKA_HWID]		= "CLKA",
	[PWR_HWID]		= "PWR",
	[GC_HWID]		= "GC",
	[UVD_HWID]		= "UVD",
	[AUDIO_AZ_HWID]		= "AUDIO_AZ",
	[ACP_HWID]		= "ACP",
	[DCI_HWID]		= "DCI",
	[DMU_HWID]		= "DMU",
	[DCO_HWID]		= "DCO",
	[DIO_HWID]		= "DIO",
	[XDMA_HWID]		= "XDMA",
	[DCEAZ_HWID]		= "DCEAZ",
	[DAZ_HWID]		= "DAZ",
	[SDPMUX_HWID]		= "SDPMUX",
	[NTB_HWID]		= "NTB",
	[IOHC_HWID]		= "IOHC",
	[L2IMU_HWID]		= "L2IMU",
	[VCE_HWID]		= "VCE",
	[MMHUB_HWID]		= "MMHUB",
	[ATHUB_HWID]		= "ATHUB",
	[DBGU_NBIO_HWID]	= "DBGU_NBIO",
	[DFX_HWID]		= "DFX",
	[DBGU0_HWID]		= "DBGU0",
	[DBGU1_HWID]		= "DBGU1",
	[OSSSYS_HWID]		= "OSSSYS",
	[HDP_HWID]		= "HDP",
	[SDMA0_HWID]		= "SDMA0",
	[SDMA1_HWID]		= "SDMA1",
	[ISP_HWID]		= "ISP",
	[DBGU_IO_HWID]		= "DBGU_IO",
	[DF_HWID]		= "DF",
	[CLKB_HWID]		= "CLKB",
	[FCH_HWID]		= "FCH",
	[DFX_DAP_HWID]		= "DFX_DAP",
	[L1IMU_PCIE_HWID]	= "L1IMU_PCIE",
	[L1IMU_NBIF_HWID]	= "L1IMU_NBIF",
	[L1IMU_IOAGR_HWID]	= "L1IMU_IOAGR",
	[L1IMU3_HWID]		= "L1IMU3",
	[L1IMU4_HWID]		= "L1IMU4",
	[L1IMU5_HWID]		= "L1IMU5",
	[L1IMU6_HWID]		= "L1IMU6",
	[L1IMU7_HWID]		= "L1IMU7",
	[L1IMU8_HWID]		= "L1IMU8",
	[L1IMU9_HWID]		= "L1IMU9",
	[L1IMU10_HWID]		= "L1IMU10",
	[L1IMU11_HWID]		= "L1IMU11",
	[L1IMU12_HWID]		= "L1IMU12",
	[L1IMU13_HWID]		= "L1IMU13",
	[L1IMU14_HWID]		= "L1IMU14",
	[L1IMU15_HWID]		= "L1IMU15",
	[WAFLC_HWID]		= "WAFLC",
	[FCH_USB_PD_HWID]	= "FCH_USB_PD",
	[PCIE_HWID]		= "PCIE",
	[PCS_HWID]		= "PCS",
	[DDCL_HWID]		= "DDCL",
	[SST_HWID]		= "SST",
	[IOAGR_HWID]		= "IOAGR",
	[NBIF_HWID]		= "NBIF",
	[IOAPIC_HWID]		= "IOAPIC",
	[SYSTEMHUB_HWID]	= "SYSTEMHUB",
	[NTBCCP_HWID]		= "NTBCCP",
	[UMC_HWID]		= "UMC",
	[SATA_HWID]		= "SATA",
	[USB_HWID]		= "USB",
	[CCXSEC_HWID]		= "CCXSEC",
	[XGMI_HWID]		= "XGMI",
	[XGBE_HWID]		= "XGBE",
	[MP0_HWID]		= "MP0",
पूर्ण;

अटल पूर्णांक hw_id_map[MAX_HWIP] = अणु
	[GC_HWIP]	= GC_HWID,
	[HDP_HWIP]	= HDP_HWID,
	[SDMA0_HWIP]	= SDMA0_HWID,
	[SDMA1_HWIP]	= SDMA1_HWID,
	[MMHUB_HWIP]	= MMHUB_HWID,
	[ATHUB_HWIP]	= ATHUB_HWID,
	[NBIO_HWIP]	= NBIF_HWID,
	[MP0_HWIP]	= MP0_HWID,
	[MP1_HWIP]	= MP1_HWID,
	[UVD_HWIP]	= UVD_HWID,
	[VCE_HWIP]	= VCE_HWID,
	[DF_HWIP]	= DF_HWID,
	[DCE_HWIP]	= DMU_HWID,
	[OSSSYS_HWIP]	= OSSSYS_HWID,
	[SMUIO_HWIP]	= SMUIO_HWID,
	[PWR_HWIP]	= PWR_HWID,
	[NBIF_HWIP]	= NBIF_HWID,
	[THM_HWIP]	= THM_HWID,
	[CLK_HWIP]	= CLKA_HWID,
	[UMC_HWIP]	= UMC_HWID,
पूर्ण;

अटल पूर्णांक amdgpu_discovery_पढ़ो_binary(काष्ठा amdgpu_device *adev, uपूर्णांक8_t *binary)
अणु
	uपूर्णांक64_t vram_size = (uपूर्णांक64_t)RREG32(mmRCC_CONFIG_MEMSIZE) << 20;
	uपूर्णांक64_t pos = vram_size - DISCOVERY_TMR_OFFSET;

	amdgpu_device_vram_access(adev, pos, (uपूर्णांक32_t *)binary,
				  adev->mman.discovery_पंचांगr_size, false);
	वापस 0;
पूर्ण

अटल uपूर्णांक16_t amdgpu_discovery_calculate_checksum(uपूर्णांक8_t *data, uपूर्णांक32_t size)
अणु
	uपूर्णांक16_t checksum = 0;
	पूर्णांक i;

	क्रम (i = 0; i < size; i++)
		checksum += data[i];

	वापस checksum;
पूर्ण

अटल अंतरभूत bool amdgpu_discovery_verअगरy_checksum(uपूर्णांक8_t *data, uपूर्णांक32_t size,
						    uपूर्णांक16_t expected)
अणु
	वापस !!(amdgpu_discovery_calculate_checksum(data, size) == expected);
पूर्ण

अटल पूर्णांक amdgpu_discovery_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा table_info *info;
	काष्ठा binary_header *bhdr;
	काष्ठा ip_discovery_header *ihdr;
	काष्ठा gpu_info_header *ghdr;
	uपूर्णांक16_t offset;
	uपूर्णांक16_t size;
	uपूर्णांक16_t checksum;
	पूर्णांक r;

	adev->mman.discovery_पंचांगr_size = DISCOVERY_TMR_SIZE;
	adev->mman.discovery_bin = kzalloc(adev->mman.discovery_पंचांगr_size, GFP_KERNEL);
	अगर (!adev->mman.discovery_bin)
		वापस -ENOMEM;

	r = amdgpu_discovery_पढ़ो_binary(adev, adev->mman.discovery_bin);
	अगर (r) अणु
		DRM_ERROR("failed to read ip discovery binary\n");
		जाओ out;
	पूर्ण

	bhdr = (काष्ठा binary_header *)adev->mman.discovery_bin;

	अगर (le32_to_cpu(bhdr->binary_signature) != BINARY_SIGNATURE) अणु
		DRM_ERROR("invalid ip discovery binary signature\n");
		r = -EINVAL;
		जाओ out;
	पूर्ण

	offset = दुरत्व(काष्ठा binary_header, binary_checksum) +
		माप(bhdr->binary_checksum);
	size = bhdr->binary_size - offset;
	checksum = bhdr->binary_checksum;

	अगर (!amdgpu_discovery_verअगरy_checksum(adev->mman.discovery_bin + offset,
					      size, checksum)) अणु
		DRM_ERROR("invalid ip discovery binary checksum\n");
		r = -EINVAL;
		जाओ out;
	पूर्ण

	info = &bhdr->table_list[IP_DISCOVERY];
	offset = le16_to_cpu(info->offset);
	checksum = le16_to_cpu(info->checksum);
	ihdr = (काष्ठा ip_discovery_header *)(adev->mman.discovery_bin + offset);

	अगर (le32_to_cpu(ihdr->signature) != DISCOVERY_TABLE_SIGNATURE) अणु
		DRM_ERROR("invalid ip discovery data table signature\n");
		r = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!amdgpu_discovery_verअगरy_checksum(adev->mman.discovery_bin + offset,
					      ihdr->size, checksum)) अणु
		DRM_ERROR("invalid ip discovery data table checksum\n");
		r = -EINVAL;
		जाओ out;
	पूर्ण

	info = &bhdr->table_list[GC];
	offset = le16_to_cpu(info->offset);
	checksum = le16_to_cpu(info->checksum);
	ghdr = (काष्ठा gpu_info_header *)(adev->mman.discovery_bin + offset);

	अगर (!amdgpu_discovery_verअगरy_checksum(adev->mman.discovery_bin + offset,
				              ghdr->size, checksum)) अणु
		DRM_ERROR("invalid gc data table checksum\n");
		r = -EINVAL;
		जाओ out;
	पूर्ण

	वापस 0;

out:
	kमुक्त(adev->mman.discovery_bin);
	adev->mman.discovery_bin = शून्य;

	वापस r;
पूर्ण

व्योम amdgpu_discovery_fini(काष्ठा amdgpu_device *adev)
अणु
	kमुक्त(adev->mman.discovery_bin);
	adev->mman.discovery_bin = शून्य;
पूर्ण

पूर्णांक amdgpu_discovery_reg_base_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा binary_header *bhdr;
	काष्ठा ip_discovery_header *ihdr;
	काष्ठा die_header *dhdr;
	काष्ठा ip *ip;
	uपूर्णांक16_t die_offset;
	uपूर्णांक16_t ip_offset;
	uपूर्णांक16_t num_dies;
	uपूर्णांक16_t num_ips;
	uपूर्णांक8_t num_base_address;
	पूर्णांक hw_ip;
	पूर्णांक i, j, k;
	पूर्णांक r;

	r = amdgpu_discovery_init(adev);
	अगर (r) अणु
		DRM_ERROR("amdgpu_discovery_init failed\n");
		वापस r;
	पूर्ण

	bhdr = (काष्ठा binary_header *)adev->mman.discovery_bin;
	ihdr = (काष्ठा ip_discovery_header *)(adev->mman.discovery_bin +
			le16_to_cpu(bhdr->table_list[IP_DISCOVERY].offset));
	num_dies = le16_to_cpu(ihdr->num_dies);

	DRM_DEBUG("number of dies: %d\n", num_dies);

	क्रम (i = 0; i < num_dies; i++) अणु
		die_offset = le16_to_cpu(ihdr->die_info[i].die_offset);
		dhdr = (काष्ठा die_header *)(adev->mman.discovery_bin + die_offset);
		num_ips = le16_to_cpu(dhdr->num_ips);
		ip_offset = die_offset + माप(*dhdr);

		अगर (le16_to_cpu(dhdr->die_id) != i) अणु
			DRM_ERROR("invalid die id %d, expected %d\n",
					le16_to_cpu(dhdr->die_id), i);
			वापस -EINVAL;
		पूर्ण

		DRM_DEBUG("number of hardware IPs on die%d: %d\n",
				le16_to_cpu(dhdr->die_id), num_ips);

		क्रम (j = 0; j < num_ips; j++) अणु
			ip = (काष्ठा ip *)(adev->mman.discovery_bin + ip_offset);
			num_base_address = ip->num_base_address;

			DRM_DEBUG("%s(%d) #%d v%d.%d.%d:\n",
				  hw_id_names[le16_to_cpu(ip->hw_id)],
				  le16_to_cpu(ip->hw_id),
				  ip->number_instance,
				  ip->major, ip->minor,
				  ip->revision);

			क्रम (k = 0; k < num_base_address; k++) अणु
				/*
				 * convert the endianness of base addresses in place,
				 * so that we करोn't need to convert them when accessing adev->reg_offset.
				 */
				ip->base_address[k] = le32_to_cpu(ip->base_address[k]);
				DRM_DEBUG("\t0x%08x\n", ip->base_address[k]);
			पूर्ण

			क्रम (hw_ip = 0; hw_ip < MAX_HWIP; hw_ip++) अणु
				अगर (hw_id_map[hw_ip] == le16_to_cpu(ip->hw_id)) अणु
					DRM_DEBUG("set register base offset for %s\n",
							hw_id_names[le16_to_cpu(ip->hw_id)]);
					adev->reg_offset[hw_ip][ip->number_instance] =
						ip->base_address;
				पूर्ण

			पूर्ण

			ip_offset += माप(*ip) + 4 * (ip->num_base_address - 1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक amdgpu_discovery_get_ip_version(काष्ठा amdgpu_device *adev, पूर्णांक hw_id,
				    पूर्णांक *major, पूर्णांक *minor, पूर्णांक *revision)
अणु
	काष्ठा binary_header *bhdr;
	काष्ठा ip_discovery_header *ihdr;
	काष्ठा die_header *dhdr;
	काष्ठा ip *ip;
	uपूर्णांक16_t die_offset;
	uपूर्णांक16_t ip_offset;
	uपूर्णांक16_t num_dies;
	uपूर्णांक16_t num_ips;
	पूर्णांक i, j;

	अगर (!adev->mman.discovery_bin) अणु
		DRM_ERROR("ip discovery uninitialized\n");
		वापस -EINVAL;
	पूर्ण

	bhdr = (काष्ठा binary_header *)adev->mman.discovery_bin;
	ihdr = (काष्ठा ip_discovery_header *)(adev->mman.discovery_bin +
			le16_to_cpu(bhdr->table_list[IP_DISCOVERY].offset));
	num_dies = le16_to_cpu(ihdr->num_dies);

	क्रम (i = 0; i < num_dies; i++) अणु
		die_offset = le16_to_cpu(ihdr->die_info[i].die_offset);
		dhdr = (काष्ठा die_header *)(adev->mman.discovery_bin + die_offset);
		num_ips = le16_to_cpu(dhdr->num_ips);
		ip_offset = die_offset + माप(*dhdr);

		क्रम (j = 0; j < num_ips; j++) अणु
			ip = (काष्ठा ip *)(adev->mman.discovery_bin + ip_offset);

			अगर (le16_to_cpu(ip->hw_id) == hw_id) अणु
				अगर (major)
					*major = ip->major;
				अगर (minor)
					*minor = ip->minor;
				अगर (revision)
					*revision = ip->revision;
				वापस 0;
			पूर्ण
			ip_offset += माप(*ip) + 4 * (ip->num_base_address - 1);
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

व्योम amdgpu_discovery_harvest_ip(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा binary_header *bhdr;
	काष्ठा harvest_table *harvest_info;
	पूर्णांक i;

	bhdr = (काष्ठा binary_header *)adev->mman.discovery_bin;
	harvest_info = (काष्ठा harvest_table *)(adev->mman.discovery_bin +
			le16_to_cpu(bhdr->table_list[HARVEST_INFO].offset));

	क्रम (i = 0; i < 32; i++) अणु
		अगर (le32_to_cpu(harvest_info->list[i].hw_id) == 0)
			अवरोध;

		चयन (le32_to_cpu(harvest_info->list[i].hw_id)) अणु
		हाल VCN_HWID:
			adev->harvest_ip_mask |= AMD_HARVEST_IP_VCN_MASK;
			adev->harvest_ip_mask |= AMD_HARVEST_IP_JPEG_MASK;
			अवरोध;
		हाल DMU_HWID:
			adev->harvest_ip_mask |= AMD_HARVEST_IP_DMU_MASK;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक amdgpu_discovery_get_gfx_info(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा binary_header *bhdr;
	काष्ठा gc_info_v1_0 *gc_info;

	अगर (!adev->mman.discovery_bin) अणु
		DRM_ERROR("ip discovery uninitialized\n");
		वापस -EINVAL;
	पूर्ण

	bhdr = (काष्ठा binary_header *)adev->mman.discovery_bin;
	gc_info = (काष्ठा gc_info_v1_0 *)(adev->mman.discovery_bin +
			le16_to_cpu(bhdr->table_list[GC].offset));

	adev->gfx.config.max_shader_engines = le32_to_cpu(gc_info->gc_num_se);
	adev->gfx.config.max_cu_per_sh = 2 * (le32_to_cpu(gc_info->gc_num_wgp0_per_sa) +
					      le32_to_cpu(gc_info->gc_num_wgp1_per_sa));
	adev->gfx.config.max_sh_per_se = le32_to_cpu(gc_info->gc_num_sa_per_se);
	adev->gfx.config.max_backends_per_se = le32_to_cpu(gc_info->gc_num_rb_per_se);
	adev->gfx.config.max_texture_channel_caches = le32_to_cpu(gc_info->gc_num_gl2c);
	adev->gfx.config.max_gprs = le32_to_cpu(gc_info->gc_num_gprs);
	adev->gfx.config.max_gs_thपढ़ोs = le32_to_cpu(gc_info->gc_num_max_gs_thds);
	adev->gfx.config.gs_vgt_table_depth = le32_to_cpu(gc_info->gc_gs_table_depth);
	adev->gfx.config.gs_prim_buffer_depth = le32_to_cpu(gc_info->gc_gsprim_buff_depth);
	adev->gfx.config.द्विगुन_offchip_lds_buf = le32_to_cpu(gc_info->gc_द्विगुन_offchip_lds_buffer);
	adev->gfx.cu_info.wave_front_size = le32_to_cpu(gc_info->gc_wave_size);
	adev->gfx.cu_info.max_waves_per_simd = le32_to_cpu(gc_info->gc_max_waves_per_simd);
	adev->gfx.cu_info.max_scratch_slots_per_cu = le32_to_cpu(gc_info->gc_max_scratch_slots_per_cu);
	adev->gfx.cu_info.lds_size = le32_to_cpu(gc_info->gc_lds_size);
	adev->gfx.config.num_sc_per_sh = le32_to_cpu(gc_info->gc_num_sc_per_se) /
					 le32_to_cpu(gc_info->gc_num_sa_per_se);
	adev->gfx.config.num_packer_per_sc = le32_to_cpu(gc_info->gc_num_packer_per_sc);

	वापस 0;
पूर्ण
