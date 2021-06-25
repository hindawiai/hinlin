<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_ACR_H__
#घोषणा __NVKM_ACR_H__
#घोषणा nvkm_acr(p) container_of((p), काष्ठा nvkm_acr, subdev)
#समावेश <core/subdev.h>
#समावेश <core/falcon.h>

क्रमागत nvkm_acr_lsf_id अणु
	NVKM_ACR_LSF_PMU = 0,
	NVKM_ACR_LSF_GSPLITE = 1,
	NVKM_ACR_LSF_FECS = 2,
	NVKM_ACR_LSF_GPCCS = 3,
	NVKM_ACR_LSF_NVDEC = 4,
	NVKM_ACR_LSF_SEC2 = 7,
	NVKM_ACR_LSF_MINION = 10,
	NVKM_ACR_LSF_NUM
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *
nvkm_acr_lsf_id(क्रमागत nvkm_acr_lsf_id id)
अणु
	चयन (id) अणु
	हाल NVKM_ACR_LSF_PMU    : वापस "pmu";
	हाल NVKM_ACR_LSF_GSPLITE: वापस "gsplite";
	हाल NVKM_ACR_LSF_FECS   : वापस "fecs";
	हाल NVKM_ACR_LSF_GPCCS  : वापस "gpccs";
	हाल NVKM_ACR_LSF_NVDEC  : वापस "nvdec";
	हाल NVKM_ACR_LSF_SEC2   : वापस "sec2";
	हाल NVKM_ACR_LSF_MINION : वापस "minion";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

काष्ठा nvkm_acr अणु
	स्थिर काष्ठा nvkm_acr_func *func;
	काष्ठा nvkm_subdev subdev;

	काष्ठा list_head hsfw, hsf;
	काष्ठा list_head lsfw, lsf;

	u64 managed_falcons;

	काष्ठा nvkm_memory *wpr;
	u64 wpr_start;
	u64 wpr_end;
	u64 shaकरोw_start;

	काष्ठा nvkm_memory *inst;
	काष्ठा nvkm_vmm *vmm;

	bool करोne;

	स्थिर काष्ठा firmware *wpr_fw;
	bool wpr_comp;
	u64 wpr_prev;
पूर्ण;

bool nvkm_acr_managed_falcon(काष्ठा nvkm_device *, क्रमागत nvkm_acr_lsf_id);
पूर्णांक nvkm_acr_bootstrap_falcons(काष्ठा nvkm_device *, अचिन्हित दीर्घ mask);

पूर्णांक gm200_acr_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_acr **);
पूर्णांक gm20b_acr_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_acr **);
पूर्णांक gp102_acr_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_acr **);
पूर्णांक gp108_acr_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_acr **);
पूर्णांक gp10b_acr_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_acr **);
पूर्णांक tu102_acr_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_acr **);

काष्ठा nvkm_acr_lsfw अणु
	स्थिर काष्ठा nvkm_acr_lsf_func *func;
	काष्ठा nvkm_falcon *falcon;
	क्रमागत nvkm_acr_lsf_id id;

	काष्ठा list_head head;

	काष्ठा nvkm_blob img;

	स्थिर काष्ठा firmware *sig;

	u32 bootloader_size;
	u32 bootloader_imem_offset;

	u32 app_size;
	u32 app_start_offset;
	u32 app_imem_entry;
	u32 app_resident_code_offset;
	u32 app_resident_code_size;
	u32 app_resident_data_offset;
	u32 app_resident_data_size;

	u32 ucode_size;
	u32 data_size;

	काष्ठा अणु
		u32 lsb;
		u32 img;
		u32 bld;
	पूर्ण offset;
	u32 bl_data_size;
पूर्ण;

काष्ठा nvkm_acr_lsf_func अणु
/* The (currently) map directly to LSB header flags. */
#घोषणा NVKM_ACR_LSF_LOAD_CODE_AT_0                                  0x00000001
#घोषणा NVKM_ACR_LSF_DMACTL_REQ_CTX                                  0x00000004
#घोषणा NVKM_ACR_LSF_FORCE_PRIV_LOAD                                 0x00000008
	u32 flags;
	u32 bld_size;
	व्योम (*bld_ग_लिखो)(काष्ठा nvkm_acr *, u32 bld, काष्ठा nvkm_acr_lsfw *);
	व्योम (*bld_patch)(काष्ठा nvkm_acr *, u32 bld, s64 adjust);
	पूर्णांक (*boot)(काष्ठा nvkm_falcon *);
	u64 bootstrap_falcons;
	पूर्णांक (*bootstrap_falcon)(काष्ठा nvkm_falcon *, क्रमागत nvkm_acr_lsf_id);
	पूर्णांक (*bootstrap_multiple_falcons)(काष्ठा nvkm_falcon *, u32 mask);
पूर्ण;

पूर्णांक
nvkm_acr_lsfw_load_sig_image_desc(काष्ठा nvkm_subdev *, काष्ठा nvkm_falcon *,
				  क्रमागत nvkm_acr_lsf_id, स्थिर अक्षर *path,
				  पूर्णांक ver, स्थिर काष्ठा nvkm_acr_lsf_func *);
पूर्णांक
nvkm_acr_lsfw_load_sig_image_desc_v1(काष्ठा nvkm_subdev *, काष्ठा nvkm_falcon *,
				     क्रमागत nvkm_acr_lsf_id, स्थिर अक्षर *path,
				     पूर्णांक ver, स्थिर काष्ठा nvkm_acr_lsf_func *);
पूर्णांक
nvkm_acr_lsfw_load_bl_inst_data_sig(काष्ठा nvkm_subdev *, काष्ठा nvkm_falcon *,
				    क्रमागत nvkm_acr_lsf_id, स्थिर अक्षर *path,
				    पूर्णांक ver, स्थिर काष्ठा nvkm_acr_lsf_func *);
#पूर्ण_अगर
