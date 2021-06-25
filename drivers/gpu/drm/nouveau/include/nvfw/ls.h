<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVFW_LS_H__
#घोषणा __NVFW_LS_H__
#समावेश <core/os.h>
काष्ठा nvkm_subdev;

काष्ठा nvfw_ls_desc_head अणु
	u32 descriptor_size;
	u32 image_size;
	u32 tools_version;
	u32 app_version;
	अक्षर date[64];
	u32 bootloader_start_offset;
	u32 bootloader_size;
	u32 bootloader_imem_offset;
	u32 bootloader_entry_poपूर्णांक;
	u32 app_start_offset;
	u32 app_size;
	u32 app_imem_offset;
	u32 app_imem_entry;
	u32 app_dmem_offset;
	u32 app_resident_code_offset;
	u32 app_resident_code_size;
	u32 app_resident_data_offset;
	u32 app_resident_data_size;
पूर्ण;

काष्ठा nvfw_ls_desc अणु
	काष्ठा nvfw_ls_desc_head head;
	u32 nb_overlays;
	काष्ठा अणु
		u32 start;
		u32 size;
	पूर्ण load_ovl[64];
	u32 compressed;
पूर्ण;

स्थिर काष्ठा nvfw_ls_desc *nvfw_ls_desc(काष्ठा nvkm_subdev *, स्थिर व्योम *);

काष्ठा nvfw_ls_desc_v1 अणु
	काष्ठा nvfw_ls_desc_head head;
	u32 nb_imem_overlays;
	u32 nb_dmem_overlays;
	काष्ठा अणु
		u32 start;
		u32 size;
	पूर्ण load_ovl[64];
	u32 compressed;
पूर्ण;

स्थिर काष्ठा nvfw_ls_desc_v1 *
nvfw_ls_desc_v1(काष्ठा nvkm_subdev *, स्थिर व्योम *);
#पूर्ण_अगर
