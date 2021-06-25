<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_SEC2_PRIV_H__
#घोषणा __NVKM_SEC2_PRIV_H__
#समावेश <engine/sec2.h>

काष्ठा nvkm_sec2_func अणु
	स्थिर काष्ठा nvkm_falcon_func *flcn;
	u8 unit_acr;
	व्योम (*पूर्णांकr)(काष्ठा nvkm_sec2 *);
	पूर्णांक (*iniपंचांगsg)(काष्ठा nvkm_sec2 *);
पूर्ण;

व्योम gp102_sec2_पूर्णांकr(काष्ठा nvkm_sec2 *);
पूर्णांक gp102_sec2_iniपंचांगsg(काष्ठा nvkm_sec2 *);

काष्ठा nvkm_sec2_fwअगर अणु
	पूर्णांक version;
	पूर्णांक (*load)(काष्ठा nvkm_sec2 *, पूर्णांक ver, स्थिर काष्ठा nvkm_sec2_fwअगर *);
	स्थिर काष्ठा nvkm_sec2_func *func;
	स्थिर काष्ठा nvkm_acr_lsf_func *acr;
पूर्ण;

पूर्णांक gp102_sec2_nofw(काष्ठा nvkm_sec2 *, पूर्णांक, स्थिर काष्ठा nvkm_sec2_fwअगर *);
पूर्णांक gp102_sec2_load(काष्ठा nvkm_sec2 *, पूर्णांक, स्थिर काष्ठा nvkm_sec2_fwअगर *);
बाह्य स्थिर काष्ठा nvkm_sec2_func gp102_sec2;
बाह्य स्थिर काष्ठा nvkm_acr_lsf_func gp102_sec2_acr_1;

पूर्णांक nvkm_sec2_new_(स्थिर काष्ठा nvkm_sec2_fwअगर *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type,
		   पूर्णांक, u32 addr, काष्ठा nvkm_sec2 **);
#पूर्ण_अगर
