<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_NVDEC_PRIV_H__
#घोषणा __NVKM_NVDEC_PRIV_H__
#समावेश <engine/nvdec.h>

काष्ठा nvkm_nvdec_func अणु
	स्थिर काष्ठा nvkm_falcon_func *flcn;
पूर्ण;

काष्ठा nvkm_nvdec_fwअगर अणु
	पूर्णांक version;
	पूर्णांक (*load)(काष्ठा nvkm_nvdec *, पूर्णांक ver,
		    स्थिर काष्ठा nvkm_nvdec_fwअगर *);
	स्थिर काष्ठा nvkm_nvdec_func *func;
पूर्ण;

पूर्णांक nvkm_nvdec_new_(स्थिर काष्ठा nvkm_nvdec_fwअगर *fwअगर, काष्ठा nvkm_device *,
		    क्रमागत nvkm_subdev_type, पूर्णांक, काष्ठा nvkm_nvdec **);
#पूर्ण_अगर
