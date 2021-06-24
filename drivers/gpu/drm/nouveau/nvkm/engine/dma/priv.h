<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_DMA_PRIV_H__
#घोषणा __NVKM_DMA_PRIV_H__
#घोषणा nvkm_dma(p) container_of((p), काष्ठा nvkm_dma, engine)
#समावेश <engine/dma.h>

काष्ठा nvkm_dmaobj_func अणु
	पूर्णांक (*bind)(काष्ठा nvkm_dmaobj *, काष्ठा nvkm_gpuobj *, पूर्णांक align,
		    काष्ठा nvkm_gpuobj **);
पूर्ण;

पूर्णांक nvkm_dma_new_(स्थिर काष्ठा nvkm_dma_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_dma **);

काष्ठा nvkm_dma_func अणु
	पूर्णांक (*class_new)(काष्ठा nvkm_dma *, स्थिर काष्ठा nvkm_oclass *,
			 व्योम *data, u32 size, काष्ठा nvkm_dmaobj **);
पूर्ण;
#पूर्ण_अगर
