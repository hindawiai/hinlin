<शैली गुरु>
#अगर_अघोषित __NVFW_ACR_H__
#घोषणा __NVFW_ACR_H__

काष्ठा wpr_header अणु
#घोषणा WPR_HEADER_V0_FALCON_ID_INVALID                              0xffffffff
	u32 falcon_id;
	u32 lsb_offset;
	u32 bootstrap_owner;
	u32 lazy_bootstrap;
#घोषणा WPR_HEADER_V0_STATUS_NONE                                             0
#घोषणा WPR_HEADER_V0_STATUS_COPY                                             1
#घोषणा WPR_HEADER_V0_STATUS_VALIDATION_CODE_FAILED                           2
#घोषणा WPR_HEADER_V0_STATUS_VALIDATION_DATA_FAILED                           3
#घोषणा WPR_HEADER_V0_STATUS_VALIDATION_DONE                                  4
#घोषणा WPR_HEADER_V0_STATUS_VALIDATION_SKIPPED                               5
#घोषणा WPR_HEADER_V0_STATUS_BOOTSTRAP_READY                                  6
	u32 status;
पूर्ण;

व्योम wpr_header_dump(काष्ठा nvkm_subdev *, स्थिर काष्ठा wpr_header *);

काष्ठा wpr_header_v1 अणु
#घोषणा WPR_HEADER_V1_FALCON_ID_INVALID                              0xffffffff
	u32 falcon_id;
	u32 lsb_offset;
	u32 bootstrap_owner;
	u32 lazy_bootstrap;
	u32 bin_version;
#घोषणा WPR_HEADER_V1_STATUS_NONE                                             0
#घोषणा WPR_HEADER_V1_STATUS_COPY                                             1
#घोषणा WPR_HEADER_V1_STATUS_VALIDATION_CODE_FAILED                           2
#घोषणा WPR_HEADER_V1_STATUS_VALIDATION_DATA_FAILED                           3
#घोषणा WPR_HEADER_V1_STATUS_VALIDATION_DONE                                  4
#घोषणा WPR_HEADER_V1_STATUS_VALIDATION_SKIPPED                               5
#घोषणा WPR_HEADER_V1_STATUS_BOOTSTRAP_READY                                  6
#घोषणा WPR_HEADER_V1_STATUS_REVOCATION_CHECK_FAILED                          7
	u32 status;
पूर्ण;

व्योम wpr_header_v1_dump(काष्ठा nvkm_subdev *, स्थिर काष्ठा wpr_header_v1 *);

काष्ठा lsf_signature अणु
	u8 prd_keys[2][16];
	u8 dbg_keys[2][16];
	u32 b_prd_present;
	u32 b_dbg_present;
	u32 falcon_id;
पूर्ण;

काष्ठा lsf_signature_v1 अणु
	u8 prd_keys[2][16];
	u8 dbg_keys[2][16];
	u32 b_prd_present;
	u32 b_dbg_present;
	u32 falcon_id;
	u32 supports_versioning;
	u32 version;
	u32 depmap_count;
	u8 depmap[11/*LSF_LSB_DEPMAP_SIZE*/ * 2 * 4];
	u8 kdf[16];
पूर्ण;

काष्ठा lsb_header_tail अणु
	u32 ucode_off;
	u32 ucode_size;
	u32 data_size;
	u32 bl_code_size;
	u32 bl_imem_off;
	u32 bl_data_off;
	u32 bl_data_size;
	u32 app_code_off;
	u32 app_code_size;
	u32 app_data_off;
	u32 app_data_size;
	u32 flags;
पूर्ण;

काष्ठा lsb_header अणु
	काष्ठा lsf_signature signature;
	काष्ठा lsb_header_tail tail;
पूर्ण;

व्योम lsb_header_dump(काष्ठा nvkm_subdev *, काष्ठा lsb_header *);

काष्ठा lsb_header_v1 अणु
	काष्ठा lsf_signature_v1 signature;
	काष्ठा lsb_header_tail tail;
पूर्ण;

व्योम lsb_header_v1_dump(काष्ठा nvkm_subdev *, काष्ठा lsb_header_v1 *);

काष्ठा flcn_acr_desc अणु
	जोड़ अणु
		u8 reserved_dmem[0x200];
		u32 signatures[4];
	पूर्ण ucode_reserved_space;
	u32 wpr_region_id;
	u32 wpr_offset;
	u32 mmu_mem_range;
	काष्ठा अणु
		u32 no_regions;
		काष्ठा अणु
			u32 start_addr;
			u32 end_addr;
			u32 region_id;
			u32 पढ़ो_mask;
			u32 ग_लिखो_mask;
			u32 client_mask;
		पूर्ण region_props[2];
	पूर्ण regions;
	u32 ucode_blob_size;
	u64 ucode_blob_base __aligned(8);
	काष्ठा अणु
		u32 vpr_enabled;
		u32 vpr_start;
		u32 vpr_end;
		u32 hdcp_policies;
	पूर्ण vpr_desc;
पूर्ण;

व्योम flcn_acr_desc_dump(काष्ठा nvkm_subdev *, काष्ठा flcn_acr_desc *);

काष्ठा flcn_acr_desc_v1 अणु
	u8 reserved_dmem[0x200];
	u32 signatures[4];
	u32 wpr_region_id;
	u32 wpr_offset;
	u32 mmu_memory_range;
	काष्ठा अणु
		u32 no_regions;
		काष्ठा अणु
			u32 start_addr;
			u32 end_addr;
			u32 region_id;
			u32 पढ़ो_mask;
			u32 ग_लिखो_mask;
			u32 client_mask;
			u32 shaकरोw_mem_start_addr;
		पूर्ण region_props[2];
	पूर्ण regions;
	u32 ucode_blob_size;
	u64 ucode_blob_base __aligned(8);
	काष्ठा अणु
		u32 vpr_enabled;
		u32 vpr_start;
		u32 vpr_end;
		u32 hdcp_policies;
	पूर्ण vpr_desc;
पूर्ण;

व्योम flcn_acr_desc_v1_dump(काष्ठा nvkm_subdev *, काष्ठा flcn_acr_desc_v1 *);
#पूर्ण_अगर
