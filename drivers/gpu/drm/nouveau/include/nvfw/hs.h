<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVFW_HS_H__
#घोषणा __NVFW_HS_H__
#समावेश <core/os.h>
काष्ठा nvkm_subdev;

काष्ठा nvfw_hs_header अणु
	u32 sig_dbg_offset;
	u32 sig_dbg_size;
	u32 sig_prod_offset;
	u32 sig_prod_size;
	u32 patch_loc;
	u32 patch_sig;
	u32 hdr_offset;
	u32 hdr_size;
पूर्ण;

स्थिर काष्ठा nvfw_hs_header *nvfw_hs_header(काष्ठा nvkm_subdev *, स्थिर व्योम *);

काष्ठा nvfw_hs_load_header अणु
	u32 non_sec_code_off;
	u32 non_sec_code_size;
	u32 data_dma_base;
	u32 data_size;
	u32 num_apps;
	u32 apps[0];
पूर्ण;

स्थिर काष्ठा nvfw_hs_load_header *
nvfw_hs_load_header(काष्ठा nvkm_subdev *, स्थिर व्योम *);
#पूर्ण_अगर
