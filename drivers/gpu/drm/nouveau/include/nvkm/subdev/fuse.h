<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_FUSE_H__
#घोषणा __NVKM_FUSE_H__
#समावेश <core/subdev.h>

काष्ठा nvkm_fuse अणु
	स्थिर काष्ठा nvkm_fuse_func *func;
	काष्ठा nvkm_subdev subdev;
	spinlock_t lock;
पूर्ण;

u32 nvkm_fuse_पढ़ो(काष्ठा nvkm_fuse *, u32 addr);

पूर्णांक nv50_fuse_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fuse **);
पूर्णांक gf100_fuse_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fuse **);
पूर्णांक gm107_fuse_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_fuse **);
#पूर्ण_अगर
