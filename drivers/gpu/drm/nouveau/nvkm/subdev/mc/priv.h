<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_MC_PRIV_H__
#घोषणा __NVKM_MC_PRIV_H__
#घोषणा nvkm_mc(p) container_of((p), काष्ठा nvkm_mc, subdev)
#समावेश <subdev/mc.h>

व्योम nvkm_mc_ctor(स्थिर काष्ठा nvkm_mc_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_mc *);
पूर्णांक nvkm_mc_new_(स्थिर काष्ठा nvkm_mc_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		 काष्ठा nvkm_mc **);

काष्ठा nvkm_mc_map अणु
	u32 stat;
	क्रमागत nvkm_subdev_type type;
	पूर्णांक inst;
	bool noस्वतः;
पूर्ण;

काष्ठा nvkm_mc_func अणु
	व्योम (*init)(काष्ठा nvkm_mc *);
	स्थिर काष्ठा nvkm_mc_map *पूर्णांकr;
	/* disable reporting of पूर्णांकerrupts to host */
	व्योम (*पूर्णांकr_unarm)(काष्ठा nvkm_mc *);
	/* enable reporting of पूर्णांकerrupts to host */
	व्योम (*पूर्णांकr_rearm)(काष्ठा nvkm_mc *);
	/* (un)mask delivery of specअगरic पूर्णांकerrupts */
	व्योम (*पूर्णांकr_mask)(काष्ठा nvkm_mc *, u32 mask, u32 stat);
	/* retrieve pending पूर्णांकerrupt mask (NV_PMC_INTR) */
	u32 (*पूर्णांकr_stat)(काष्ठा nvkm_mc *);
	स्थिर काष्ठा nvkm_mc_map *reset;
	व्योम (*unk260)(काष्ठा nvkm_mc *, u32);
पूर्ण;

व्योम nv04_mc_init(काष्ठा nvkm_mc *);
व्योम nv04_mc_पूर्णांकr_unarm(काष्ठा nvkm_mc *);
व्योम nv04_mc_पूर्णांकr_rearm(काष्ठा nvkm_mc *);
u32 nv04_mc_पूर्णांकr_stat(काष्ठा nvkm_mc *);
बाह्य स्थिर काष्ठा nvkm_mc_map nv04_mc_reset[];

बाह्य स्थिर काष्ठा nvkm_mc_map nv17_mc_पूर्णांकr[];
बाह्य स्थिर काष्ठा nvkm_mc_map nv17_mc_reset[];

व्योम nv44_mc_init(काष्ठा nvkm_mc *);

व्योम nv50_mc_init(काष्ठा nvkm_mc *);
व्योम gk104_mc_init(काष्ठा nvkm_mc *);

व्योम gf100_mc_पूर्णांकr_unarm(काष्ठा nvkm_mc *);
व्योम gf100_mc_पूर्णांकr_rearm(काष्ठा nvkm_mc *);
व्योम gf100_mc_पूर्णांकr_mask(काष्ठा nvkm_mc *, u32, u32);
u32 gf100_mc_पूर्णांकr_stat(काष्ठा nvkm_mc *);
व्योम gf100_mc_unk260(काष्ठा nvkm_mc *, u32);
व्योम gp100_mc_पूर्णांकr_unarm(काष्ठा nvkm_mc *);
व्योम gp100_mc_पूर्णांकr_rearm(काष्ठा nvkm_mc *);
व्योम gp100_mc_पूर्णांकr_mask(काष्ठा nvkm_mc *, u32, u32);
पूर्णांक gp100_mc_new_(स्थिर काष्ठा nvkm_mc_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_mc **);

बाह्य स्थिर काष्ठा nvkm_mc_map gk104_mc_पूर्णांकr[];
बाह्य स्थिर काष्ठा nvkm_mc_map gk104_mc_reset[];

बाह्य स्थिर काष्ठा nvkm_mc_map gp100_mc_पूर्णांकr[];
#पूर्ण_अगर
