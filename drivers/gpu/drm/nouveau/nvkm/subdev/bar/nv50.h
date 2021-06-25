<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV50_BAR_H__
#घोषणा __NV50_BAR_H__
#घोषणा nv50_bar(p) container_of((p), काष्ठा nv50_bar, base)
#समावेश "priv.h"

काष्ठा nv50_bar अणु
	काष्ठा nvkm_bar base;
	u32 pgd_addr;
	काष्ठा nvkm_gpuobj *mem;
	काष्ठा nvkm_gpuobj *pad;
	काष्ठा nvkm_gpuobj *pgd;
	काष्ठा nvkm_vmm *bar1_vmm;
	काष्ठा nvkm_gpuobj *bar1;
	काष्ठा nvkm_vmm *bar2_vmm;
	काष्ठा nvkm_gpuobj *bar2;
पूर्ण;

पूर्णांक nv50_bar_new_(स्थिर काष्ठा nvkm_bar_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type,
		  पूर्णांक, u32 pgd_addr, काष्ठा nvkm_bar **);
व्योम *nv50_bar_dtor(काष्ठा nvkm_bar *);
पूर्णांक nv50_bar_oneinit(काष्ठा nvkm_bar *);
व्योम nv50_bar_init(काष्ठा nvkm_bar *);
व्योम nv50_bar_bar1_init(काष्ठा nvkm_bar *);
व्योम nv50_bar_bar1_रुको(काष्ठा nvkm_bar *);
काष्ठा nvkm_vmm *nv50_bar_bar1_vmm(काष्ठा nvkm_bar *);
व्योम nv50_bar_bar2_init(काष्ठा nvkm_bar *);
काष्ठा nvkm_vmm *nv50_bar_bar2_vmm(काष्ठा nvkm_bar *);
#पूर्ण_अगर
