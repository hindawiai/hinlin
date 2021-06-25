<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVFW_FW_H__
#घोषणा __NVFW_FW_H__
#समावेश <core/os.h>
काष्ठा nvkm_subdev;

काष्ठा nvfw_bin_hdr अणु
	u32 bin_magic;
	u32 bin_ver;
	u32 bin_size;
	u32 header_offset;
	u32 data_offset;
	u32 data_size;
पूर्ण;

स्थिर काष्ठा nvfw_bin_hdr *nvfw_bin_hdr(काष्ठा nvkm_subdev *, स्थिर व्योम *);

काष्ठा nvfw_bl_desc अणु
	u32 start_tag;
	u32 dmem_load_off;
	u32 code_off;
	u32 code_size;
	u32 data_off;
	u32 data_size;
पूर्ण;

स्थिर काष्ठा nvfw_bl_desc *nvfw_bl_desc(काष्ठा nvkm_subdev *, स्थिर व्योम *);
#पूर्ण_अगर
