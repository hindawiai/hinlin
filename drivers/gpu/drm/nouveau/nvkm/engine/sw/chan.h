<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_SW_CHAN_H__
#घोषणा __NVKM_SW_CHAN_H__
#घोषणा nvkm_sw_chan(p) container_of((p), काष्ठा nvkm_sw_chan, object)
#समावेश <core/object.h>
#समावेश <core/event.h>

#समावेश "priv.h"

काष्ठा nvkm_sw_chan अणु
	स्थिर काष्ठा nvkm_sw_chan_func *func;
	काष्ठा nvkm_object object;
	काष्ठा nvkm_sw *sw;
	काष्ठा nvkm_fअगरo_chan *fअगरo;
	काष्ठा list_head head;

	काष्ठा nvkm_event event;
पूर्ण;

काष्ठा nvkm_sw_chan_func अणु
	व्योम *(*dtor)(काष्ठा nvkm_sw_chan *);
	bool (*mthd)(काष्ठा nvkm_sw_chan *, पूर्णांक subc, u32 mthd, u32 data);
पूर्ण;

पूर्णांक nvkm_sw_chan_ctor(स्थिर काष्ठा nvkm_sw_chan_func *, काष्ठा nvkm_sw *,
		      काष्ठा nvkm_fअगरo_chan *, स्थिर काष्ठा nvkm_oclass *,
		      काष्ठा nvkm_sw_chan *);
bool nvkm_sw_chan_mthd(काष्ठा nvkm_sw_chan *, पूर्णांक subc, u32 mthd, u32 data);
#पूर्ण_अगर
