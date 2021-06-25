<शैली गुरु>
#अगर_अघोषित __NVKM_ACR_PRIV_H__
#घोषणा __NVKM_ACR_PRIV_H__
#समावेश <subdev/acr.h>
काष्ठा lsb_header_tail;

काष्ठा nvkm_acr_fwअगर अणु
	पूर्णांक version;
	पूर्णांक (*load)(काष्ठा nvkm_acr *, पूर्णांक version,
		    स्थिर काष्ठा nvkm_acr_fwअगर *);
	स्थिर काष्ठा nvkm_acr_func *func;
पूर्ण;

पूर्णांक gm200_acr_nofw(काष्ठा nvkm_acr *, पूर्णांक, स्थिर काष्ठा nvkm_acr_fwअगर *);
पूर्णांक gm20b_acr_load(काष्ठा nvkm_acr *, पूर्णांक, स्थिर काष्ठा nvkm_acr_fwअगर *);
पूर्णांक gp102_acr_load(काष्ठा nvkm_acr *, पूर्णांक, स्थिर काष्ठा nvkm_acr_fwअगर *);

काष्ठा nvkm_acr_lsf;
काष्ठा nvkm_acr_func अणु
	स्थिर काष्ठा nvkm_acr_hsf_fwअगर *load;
	स्थिर काष्ठा nvkm_acr_hsf_fwअगर *ahesasc;
	स्थिर काष्ठा nvkm_acr_hsf_fwअगर *asb;
	स्थिर काष्ठा nvkm_acr_hsf_fwअगर *unload;
	पूर्णांक (*wpr_parse)(काष्ठा nvkm_acr *);
	u32 (*wpr_layout)(काष्ठा nvkm_acr *);
	पूर्णांक (*wpr_alloc)(काष्ठा nvkm_acr *, u32 wpr_size);
	पूर्णांक (*wpr_build)(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_lsf *rtos);
	व्योम (*wpr_patch)(काष्ठा nvkm_acr *, s64 adjust);
	व्योम (*wpr_check)(काष्ठा nvkm_acr *, u64 *start, u64 *limit);
	पूर्णांक (*init)(काष्ठा nvkm_acr *);
	व्योम (*fini)(काष्ठा nvkm_acr *);
	u64 bootstrap_falcons;
पूर्ण;

बाह्य स्थिर काष्ठा nvkm_acr_func gm200_acr;
पूर्णांक gm200_acr_wpr_parse(काष्ठा nvkm_acr *);
u32 gm200_acr_wpr_layout(काष्ठा nvkm_acr *);
पूर्णांक gm200_acr_wpr_build(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_lsf *);
व्योम gm200_acr_wpr_patch(काष्ठा nvkm_acr *, s64);
व्योम gm200_acr_wpr_check(काष्ठा nvkm_acr *, u64 *, u64 *);
व्योम gm200_acr_wpr_build_lsb_tail(काष्ठा nvkm_acr_lsfw *,
				  काष्ठा lsb_header_tail *);
पूर्णांक gm200_acr_init(काष्ठा nvkm_acr *);

पूर्णांक gm20b_acr_wpr_alloc(काष्ठा nvkm_acr *, u32 wpr_size);

पूर्णांक gp102_acr_wpr_parse(काष्ठा nvkm_acr *);
u32 gp102_acr_wpr_layout(काष्ठा nvkm_acr *);
पूर्णांक gp102_acr_wpr_alloc(काष्ठा nvkm_acr *, u32 wpr_size);
पूर्णांक gp102_acr_wpr_build(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_lsf *);
पूर्णांक gp102_acr_wpr_build_lsb(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_lsfw *);
व्योम gp102_acr_wpr_patch(काष्ठा nvkm_acr *, s64);

काष्ठा nvkm_acr_hsfw अणु
	स्थिर काष्ठा nvkm_acr_hsf_func *func;
	स्थिर अक्षर *name;
	काष्ठा list_head head;

	u32 imem_size;
	u32 imem_tag;
	u32 *imem;

	u8 *image;
	u32 image_size;
	u32 non_sec_addr;
	u32 non_sec_size;
	u32 sec_addr;
	u32 sec_size;
	u32 data_addr;
	u32 data_size;

	काष्ठा अणु
		काष्ठा अणु
			व्योम *data;
			u32 size;
		पूर्ण prod, dbg;
		u32 patch_loc;
	पूर्ण sig;
पूर्ण;

काष्ठा nvkm_acr_hsf_fwअगर अणु
	पूर्णांक version;
	पूर्णांक (*load)(काष्ठा nvkm_acr *, स्थिर अक्षर *bl, स्थिर अक्षर *fw,
		    स्थिर अक्षर *name, पूर्णांक version,
		    स्थिर काष्ठा nvkm_acr_hsf_fwअगर *);
	स्थिर काष्ठा nvkm_acr_hsf_func *func;
पूर्ण;

पूर्णांक nvkm_acr_hsfw_load(काष्ठा nvkm_acr *, स्थिर अक्षर *, स्थिर अक्षर *,
		       स्थिर अक्षर *, पूर्णांक, स्थिर काष्ठा nvkm_acr_hsf_fwअगर *);
व्योम nvkm_acr_hsfw_del_all(काष्ठा nvkm_acr *);

काष्ठा nvkm_acr_hsf अणु
	स्थिर काष्ठा nvkm_acr_hsf_func *func;
	स्थिर अक्षर *name;
	काष्ठा list_head head;

	u32 imem_size;
	u32 imem_tag;
	u32 *imem;

	u32 non_sec_addr;
	u32 non_sec_size;
	u32 sec_addr;
	u32 sec_size;
	u32 data_addr;
	u32 data_size;

	काष्ठा nvkm_memory *ucode;
	काष्ठा nvkm_vma *vma;
	काष्ठा nvkm_falcon *falcon;
पूर्ण;

काष्ठा nvkm_acr_hsf_func अणु
	पूर्णांक (*load)(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsfw *);
	पूर्णांक (*boot)(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsf *);
	व्योम (*bld)(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsf *);
पूर्ण;

पूर्णांक gm200_acr_hsfw_load(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsfw *,
			काष्ठा nvkm_falcon *);
पूर्णांक gm200_acr_hsfw_boot(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsf *,
			u32 clear_पूर्णांकr, u32 mbox0_ok);

पूर्णांक gm200_acr_load_boot(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsf *);

बाह्य स्थिर काष्ठा nvkm_acr_hsf_func gm200_acr_unload_0;
पूर्णांक gm200_acr_unload_load(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsfw *);
पूर्णांक gm200_acr_unload_boot(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsf *);
व्योम gm200_acr_hsfw_bld(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsf *);

बाह्य स्थिर काष्ठा nvkm_acr_hsf_func gm20b_acr_load_0;

पूर्णांक gp102_acr_load_load(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsfw *);

बाह्य स्थिर काष्ठा nvkm_acr_hsf_func gp108_acr_unload_0;
व्योम gp108_acr_hsfw_bld(काष्ठा nvkm_acr *, काष्ठा nvkm_acr_hsf *);

पूर्णांक nvkm_acr_new_(स्थिर काष्ठा nvkm_acr_fwअगर *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type,
		  पूर्णांक inst, काष्ठा nvkm_acr **);
पूर्णांक nvkm_acr_hsf_boot(काष्ठा nvkm_acr *, स्थिर अक्षर *name);

काष्ठा nvkm_acr_lsf अणु
	स्थिर काष्ठा nvkm_acr_lsf_func *func;
	काष्ठा nvkm_falcon *falcon;
	क्रमागत nvkm_acr_lsf_id id;
	काष्ठा list_head head;
पूर्ण;

काष्ठा nvkm_acr_lsfw *nvkm_acr_lsfw_add(स्थिर काष्ठा nvkm_acr_lsf_func *,
					काष्ठा nvkm_acr *, काष्ठा nvkm_falcon *,
					क्रमागत nvkm_acr_lsf_id);
व्योम nvkm_acr_lsfw_del(काष्ठा nvkm_acr_lsfw *);
व्योम nvkm_acr_lsfw_del_all(काष्ठा nvkm_acr *);
#पूर्ण_अगर
