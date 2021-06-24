<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_TIMER_PRIV_H__
#घोषणा __NVKM_TIMER_PRIV_H__
#घोषणा nvkm_समयr(p) container_of((p), काष्ठा nvkm_समयr, subdev)
#समावेश <subdev/समयr.h>

पूर्णांक nvkm_समयr_new_(स्थिर काष्ठा nvkm_समयr_func *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type,
		    पूर्णांक, काष्ठा nvkm_समयr **);

काष्ठा nvkm_समयr_func अणु
	व्योम (*init)(काष्ठा nvkm_समयr *);
	व्योम (*पूर्णांकr)(काष्ठा nvkm_समयr *);
	u64 (*पढ़ो)(काष्ठा nvkm_समयr *);
	व्योम (*समय)(काष्ठा nvkm_समयr *, u64 समय);
	व्योम (*alarm_init)(काष्ठा nvkm_समयr *, u32 समय);
	व्योम (*alarm_fini)(काष्ठा nvkm_समयr *);
पूर्ण;

व्योम nvkm_समयr_alarm_trigger(काष्ठा nvkm_समयr *);

व्योम nv04_समयr_fini(काष्ठा nvkm_समयr *);
व्योम nv04_समयr_पूर्णांकr(काष्ठा nvkm_समयr *);
व्योम nv04_समयr_समय(काष्ठा nvkm_समयr *, u64);
u64 nv04_समयr_पढ़ो(काष्ठा nvkm_समयr *);
व्योम nv04_समयr_alarm_init(काष्ठा nvkm_समयr *, u32);
व्योम nv04_समयr_alarm_fini(काष्ठा nvkm_समयr *);
#पूर्ण_अगर
