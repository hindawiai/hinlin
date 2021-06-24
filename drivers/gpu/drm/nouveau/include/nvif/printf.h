<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_PRINTF_H__
#घोषणा __NVIF_PRINTF_H__
#समावेश <nvअगर/client.h>
#समावेश <nvअगर/parent.h>

#घोषणा NVIF_PRINT(l,o,f,a...) करो अणु                                                                \
	काष्ठा nvअगर_object *_o = (o);                                                              \
	काष्ठा nvअगर_parent *_p = _o->parent;                                                       \
	_p->func->l(_o, "[%s/%08x:%s] "f"\n", _o->client->object.name, _o->handle, _o->name, ##a); \
पूर्ण जबतक(0)

#अगर_अघोषित NVIF_DEBUG_PRINT_DISABLE
#घोषणा NVIF_DEBUG(o,f,a...) NVIF_PRINT(debugf, (o), f, ##a)
#अन्यथा
#घोषणा NVIF_DEBUG(o,f,a...)
#पूर्ण_अगर

#घोषणा NVIF_ERROR(o,f,a...) NVIF_PRINT(errorf, (o), f, ##a)
#पूर्ण_अगर
