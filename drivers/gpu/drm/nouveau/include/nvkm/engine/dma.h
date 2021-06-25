<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DMA_H__
#घोषणा __NVKM_DMA_H__
#समावेश <core/engine.h>
#समावेश <core/object.h>
काष्ठा nvkm_client;

काष्ठा nvkm_dmaobj अणु
	स्थिर काष्ठा nvkm_dmaobj_func *func;
	काष्ठा nvkm_dma *dma;

	काष्ठा nvkm_object object;
	u32 target;
	u32 access;
	u64 start;
	u64 limit;
पूर्ण;

काष्ठा nvkm_dma अणु
	स्थिर काष्ठा nvkm_dma_func *func;
	काष्ठा nvkm_engine engine;
पूर्ण;

काष्ठा nvkm_dmaobj *nvkm_dmaobj_search(काष्ठा nvkm_client *, u64 object);

पूर्णांक nv04_dma_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_dma **);
पूर्णांक nv50_dma_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_dma **);
पूर्णांक gf100_dma_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_dma **);
पूर्णांक gf119_dma_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_dma **);
पूर्णांक gv100_dma_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_dma **);
#पूर्ण_अगर
