<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_EVENT_H__
#घोषणा __NVKM_EVENT_H__
#समावेश <core/os.h>
काष्ठा nvkm_notअगरy;
काष्ठा nvkm_object;

काष्ठा nvkm_event अणु
	स्थिर काष्ठा nvkm_event_func *func;

	पूर्णांक types_nr;
	पूर्णांक index_nr;

	spinlock_t refs_lock;
	spinlock_t list_lock;
	काष्ठा list_head list;
	पूर्णांक *refs;
पूर्ण;

काष्ठा nvkm_event_func अणु
	पूर्णांक  (*ctor)(काष्ठा nvkm_object *, व्योम *data, u32 size,
		     काष्ठा nvkm_notअगरy *);
	व्योम (*send)(व्योम *data, u32 size, काष्ठा nvkm_notअगरy *);
	व्योम (*init)(काष्ठा nvkm_event *, पूर्णांक type, पूर्णांक index);
	व्योम (*fini)(काष्ठा nvkm_event *, पूर्णांक type, पूर्णांक index);
पूर्ण;

पूर्णांक  nvkm_event_init(स्थिर काष्ठा nvkm_event_func *func, पूर्णांक types_nr,
		     पूर्णांक index_nr, काष्ठा nvkm_event *);
व्योम nvkm_event_fini(काष्ठा nvkm_event *);
व्योम nvkm_event_get(काष्ठा nvkm_event *, u32 types, पूर्णांक index);
व्योम nvkm_event_put(काष्ठा nvkm_event *, u32 types, पूर्णांक index);
व्योम nvkm_event_send(काष्ठा nvkm_event *, u32 types, पूर्णांक index,
		     व्योम *data, u32 size);
#पूर्ण_अगर
