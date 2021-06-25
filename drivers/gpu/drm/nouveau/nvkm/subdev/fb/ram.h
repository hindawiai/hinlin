<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FB_RAM_PRIV_H__
#घोषणा __NVKM_FB_RAM_PRIV_H__
#समावेश "priv.h"

पूर्णांक  nvkm_ram_ctor(स्थिर काष्ठा nvkm_ram_func *, काष्ठा nvkm_fb *,
		   क्रमागत nvkm_ram_type, u64 size, काष्ठा nvkm_ram *);
पूर्णांक  nvkm_ram_new_(स्थिर काष्ठा nvkm_ram_func *, काष्ठा nvkm_fb *,
		   क्रमागत nvkm_ram_type, u64 size, काष्ठा nvkm_ram **);
व्योम nvkm_ram_del(काष्ठा nvkm_ram **);
पूर्णांक  nvkm_ram_init(काष्ठा nvkm_ram *);

बाह्य स्थिर काष्ठा nvkm_ram_func nv04_ram_func;

पूर्णांक  nv50_ram_ctor(स्थिर काष्ठा nvkm_ram_func *, काष्ठा nvkm_fb *,
		   काष्ठा nvkm_ram *);

पूर्णांक gf100_ram_new_(स्थिर काष्ठा nvkm_ram_func *, काष्ठा nvkm_fb *,
		   काष्ठा nvkm_ram **);
पूर्णांक  gf100_ram_ctor(स्थिर काष्ठा nvkm_ram_func *, काष्ठा nvkm_fb *,
		    काष्ठा nvkm_ram *);
u32  gf100_ram_probe_fbp(स्थिर काष्ठा nvkm_ram_func *,
			 काष्ठा nvkm_device *, पूर्णांक, पूर्णांक *);
u32  gf100_ram_probe_fbp_amount(स्थिर काष्ठा nvkm_ram_func *, u32,
				काष्ठा nvkm_device *, पूर्णांक, पूर्णांक *);
u32  gf100_ram_probe_fbpa_amount(काष्ठा nvkm_device *, पूर्णांक);
पूर्णांक gf100_ram_init(काष्ठा nvkm_ram *);
पूर्णांक gf100_ram_calc(काष्ठा nvkm_ram *, u32);
पूर्णांक gf100_ram_prog(काष्ठा nvkm_ram *);
व्योम gf100_ram_tidy(काष्ठा nvkm_ram *);

u32 gf108_ram_probe_fbp_amount(स्थिर काष्ठा nvkm_ram_func *, u32,
			       काष्ठा nvkm_device *, पूर्णांक, पूर्णांक *);

पूर्णांक gk104_ram_new_(स्थिर काष्ठा nvkm_ram_func *, काष्ठा nvkm_fb *,
		   काष्ठा nvkm_ram **);
व्योम *gk104_ram_dtor(काष्ठा nvkm_ram *);
पूर्णांक gk104_ram_init(काष्ठा nvkm_ram *);
पूर्णांक gk104_ram_calc(काष्ठा nvkm_ram *, u32);
पूर्णांक gk104_ram_prog(काष्ठा nvkm_ram *);
व्योम gk104_ram_tidy(काष्ठा nvkm_ram *);

u32 gm107_ram_probe_fbp(स्थिर काष्ठा nvkm_ram_func *,
			काष्ठा nvkm_device *, पूर्णांक, पूर्णांक *);

u32 gm200_ram_probe_fbp_amount(स्थिर काष्ठा nvkm_ram_func *, u32,
			       काष्ठा nvkm_device *, पूर्णांक, पूर्णांक *);

/* RAM type-specअगरic MR calculation routines */
पूर्णांक nvkm_sddr2_calc(काष्ठा nvkm_ram *);
पूर्णांक nvkm_sddr3_calc(काष्ठा nvkm_ram *);
पूर्णांक nvkm_gddr3_calc(काष्ठा nvkm_ram *);
पूर्णांक nvkm_gddr5_calc(काष्ठा nvkm_ram *, bool nuts);

पूर्णांक nv04_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक nv10_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक nv1a_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक nv20_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक nv40_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक nv41_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक nv44_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक nv49_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक nv4e_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक nv50_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक gt215_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक mcp77_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक gf100_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक gf108_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक gk104_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक gm107_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक gm200_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक gp100_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
पूर्णांक ga102_ram_new(काष्ठा nvkm_fb *, काष्ठा nvkm_ram **);
#पूर्ण_अगर
