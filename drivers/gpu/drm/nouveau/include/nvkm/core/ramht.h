<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_RAMHT_H__
#घोषणा __NVKM_RAMHT_H__
#समावेश <core/gpuobj.h>
काष्ठा nvkm_object;

काष्ठा nvkm_ramht_data अणु
	काष्ठा nvkm_gpuobj *inst;
	पूर्णांक chid;
	u32 handle;
पूर्ण;

काष्ठा nvkm_ramht अणु
	काष्ठा nvkm_device *device;
	काष्ठा nvkm_gpuobj *parent;
	काष्ठा nvkm_gpuobj *gpuobj;
	पूर्णांक size;
	पूर्णांक bits;
	काष्ठा nvkm_ramht_data data[];
पूर्ण;

पूर्णांक  nvkm_ramht_new(काष्ठा nvkm_device *, u32 size, u32 align,
		    काष्ठा nvkm_gpuobj *, काष्ठा nvkm_ramht **);
व्योम nvkm_ramht_del(काष्ठा nvkm_ramht **);
पूर्णांक  nvkm_ramht_insert(काष्ठा nvkm_ramht *, काष्ठा nvkm_object *,
		       पूर्णांक chid, पूर्णांक addr, u32 handle, u32 context);
व्योम nvkm_ramht_हटाओ(काष्ठा nvkm_ramht *, पूर्णांक cookie);
काष्ठा nvkm_gpuobj *
nvkm_ramht_search(काष्ठा nvkm_ramht *, पूर्णांक chid, u32 handle);
#पूर्ण_अगर
