<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __GF100_BAR_H__
#घोषणा __GF100_BAR_H__
#घोषणा gf100_bar(p) container_of((p), काष्ठा gf100_bar, base)
#समावेश "priv.h"

काष्ठा gf100_barN अणु
	काष्ठा nvkm_memory *inst;
	काष्ठा nvkm_vmm *vmm;
पूर्ण;

काष्ठा gf100_bar अणु
	काष्ठा nvkm_bar base;
	bool bar2_halve;
	काष्ठा gf100_barN bar[2];
पूर्ण;

पूर्णांक gf100_bar_new_(स्थिर काष्ठा nvkm_bar_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type,
		   पूर्णांक, काष्ठा nvkm_bar **);
व्योम *gf100_bar_dtor(काष्ठा nvkm_bar *);
पूर्णांक gf100_bar_oneinit(काष्ठा nvkm_bar *);
व्योम gf100_bar_bar1_init(काष्ठा nvkm_bar *);
व्योम gf100_bar_bar1_रुको(काष्ठा nvkm_bar *);
काष्ठा nvkm_vmm *gf100_bar_bar1_vmm(काष्ठा nvkm_bar *);
व्योम gf100_bar_bar2_init(काष्ठा nvkm_bar *);
काष्ठा nvkm_vmm *gf100_bar_bar2_vmm(काष्ठा nvkm_bar *);
#पूर्ण_अगर
