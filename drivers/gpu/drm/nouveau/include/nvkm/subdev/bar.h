<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_BAR_H__
#घोषणा __NVKM_BAR_H__
#समावेश <core/subdev.h>
काष्ठा nvkm_vma;

काष्ठा nvkm_bar अणु
	स्थिर काष्ठा nvkm_bar_func *func;
	काष्ठा nvkm_subdev subdev;

	spinlock_t lock;
	bool bar2;

	/* whether the BAR supports to be ioremapped WC or should be uncached */
	bool iomap_uncached;
पूर्ण;

काष्ठा nvkm_vmm *nvkm_bar_bar1_vmm(काष्ठा nvkm_device *);
व्योम nvkm_bar_bar1_reset(काष्ठा nvkm_device *);
व्योम nvkm_bar_bar2_init(काष्ठा nvkm_device *);
व्योम nvkm_bar_bar2_fini(काष्ठा nvkm_device *);
व्योम nvkm_bar_bar2_reset(काष्ठा nvkm_device *);
काष्ठा nvkm_vmm *nvkm_bar_bar2_vmm(काष्ठा nvkm_device *);
व्योम nvkm_bar_flush(काष्ठा nvkm_bar *);

पूर्णांक nv50_bar_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bar **);
पूर्णांक g84_bar_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bar **);
पूर्णांक gf100_bar_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bar **);
पूर्णांक gk20a_bar_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bar **);
पूर्णांक gm107_bar_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bar **);
पूर्णांक gm20b_bar_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bar **);
पूर्णांक tu102_bar_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_bar **);
#पूर्ण_अगर
