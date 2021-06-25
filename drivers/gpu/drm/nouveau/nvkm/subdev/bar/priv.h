<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_BAR_PRIV_H__
#घोषणा __NVKM_BAR_PRIV_H__
#घोषणा nvkm_bar(p) container_of((p), काष्ठा nvkm_bar, subdev)
#समावेश <subdev/bar.h>

व्योम nvkm_bar_ctor(स्थिर काष्ठा nvkm_bar_func *, काष्ठा nvkm_device *,
		   क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_bar *);

काष्ठा nvkm_bar_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_bar *);
	पूर्णांक (*oneinit)(काष्ठा nvkm_bar *);
	व्योम (*init)(काष्ठा nvkm_bar *);

	काष्ठा अणु
		व्योम (*init)(काष्ठा nvkm_bar *);
		व्योम (*fini)(काष्ठा nvkm_bar *);
		व्योम (*रुको)(काष्ठा nvkm_bar *);
		काष्ठा nvkm_vmm *(*vmm)(काष्ठा nvkm_bar *);
	पूर्ण bar1, bar2;

	व्योम (*flush)(काष्ठा nvkm_bar *);
पूर्ण;

व्योम nv50_bar_bar1_fini(काष्ठा nvkm_bar *);
व्योम nv50_bar_bar2_fini(काष्ठा nvkm_bar *);

व्योम g84_bar_flush(काष्ठा nvkm_bar *);

व्योम gf100_bar_bar1_fini(काष्ठा nvkm_bar *);
व्योम gf100_bar_bar2_fini(काष्ठा nvkm_bar *);

व्योम gm107_bar_bar1_रुको(काष्ठा nvkm_bar *);
#पूर्ण_अगर
