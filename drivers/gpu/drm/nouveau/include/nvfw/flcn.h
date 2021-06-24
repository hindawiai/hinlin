<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVFW_FLCN_H__
#घोषणा __NVFW_FLCN_H__
#समावेश <core/os.h>
काष्ठा nvkm_subdev;

काष्ठा loader_config अणु
	u32 dma_idx;
	u32 code_dma_base;
	u32 code_माप_प्रकारotal;
	u32 code_माप_प्रकारo_load;
	u32 code_entry_poपूर्णांक;
	u32 data_dma_base;
	u32 data_size;
	u32 overlay_dma_base;
	u32 argc;
	u32 argv;
	u32 code_dma_base1;
	u32 data_dma_base1;
	u32 overlay_dma_base1;
पूर्ण;

व्योम
loader_config_dump(काष्ठा nvkm_subdev *, स्थिर काष्ठा loader_config *);

काष्ठा loader_config_v1 अणु
	u32 reserved;
	u32 dma_idx;
	u64 code_dma_base;
	u32 code_माप_प्रकारotal;
	u32 code_माप_प्रकारo_load;
	u32 code_entry_poपूर्णांक;
	u64 data_dma_base;
	u32 data_size;
	u64 overlay_dma_base;
	u32 argc;
	u32 argv;
पूर्ण __packed;

व्योम
loader_config_v1_dump(काष्ठा nvkm_subdev *, स्थिर काष्ठा loader_config_v1 *);

काष्ठा flcn_bl_dmem_desc अणु
	u32 reserved[4];
	u32 signature[4];
	u32 ctx_dma;
	u32 code_dma_base;
	u32 non_sec_code_off;
	u32 non_sec_code_size;
	u32 sec_code_off;
	u32 sec_code_size;
	u32 code_entry_poपूर्णांक;
	u32 data_dma_base;
	u32 data_size;
	u32 code_dma_base1;
	u32 data_dma_base1;
पूर्ण;

व्योम
flcn_bl_dmem_desc_dump(काष्ठा nvkm_subdev *, स्थिर काष्ठा flcn_bl_dmem_desc *);

काष्ठा flcn_bl_dmem_desc_v1 अणु
	u32 reserved[4];
	u32 signature[4];
	u32 ctx_dma;
	u64 code_dma_base;
	u32 non_sec_code_off;
	u32 non_sec_code_size;
	u32 sec_code_off;
	u32 sec_code_size;
	u32 code_entry_poपूर्णांक;
	u64 data_dma_base;
	u32 data_size;
पूर्ण __packed;

व्योम flcn_bl_dmem_desc_v1_dump(काष्ठा nvkm_subdev *,
			       स्थिर काष्ठा flcn_bl_dmem_desc_v1 *);

काष्ठा flcn_bl_dmem_desc_v2 अणु
	u32 reserved[4];
	u32 signature[4];
	u32 ctx_dma;
	u64 code_dma_base;
	u32 non_sec_code_off;
	u32 non_sec_code_size;
	u32 sec_code_off;
	u32 sec_code_size;
	u32 code_entry_poपूर्णांक;
	u64 data_dma_base;
	u32 data_size;
	u32 argc;
	u32 argv;
पूर्ण __packed;

व्योम flcn_bl_dmem_desc_v2_dump(काष्ठा nvkm_subdev *,
			       स्थिर काष्ठा flcn_bl_dmem_desc_v2 *);
#पूर्ण_अगर
