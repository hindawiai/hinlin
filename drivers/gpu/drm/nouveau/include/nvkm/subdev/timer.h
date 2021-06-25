<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_TIMER_H__
#घोषणा __NVKM_TIMER_H__
#समावेश <core/subdev.h>

काष्ठा nvkm_alarm अणु
	काष्ठा list_head head;
	काष्ठा list_head exec;
	u64 बारtamp;
	व्योम (*func)(काष्ठा nvkm_alarm *);
पूर्ण;

अटल अंतरभूत व्योम
nvkm_alarm_init(काष्ठा nvkm_alarm *alarm, व्योम (*func)(काष्ठा nvkm_alarm *))
अणु
	INIT_LIST_HEAD(&alarm->head);
	alarm->func = func;
पूर्ण

काष्ठा nvkm_समयr अणु
	स्थिर काष्ठा nvkm_समयr_func *func;
	काष्ठा nvkm_subdev subdev;

	काष्ठा list_head alarms;
	spinlock_t lock;
पूर्ण;

u64 nvkm_समयr_पढ़ो(काष्ठा nvkm_समयr *);
व्योम nvkm_समयr_alarm(काष्ठा nvkm_समयr *, u32 nsec, काष्ठा nvkm_alarm *);

काष्ठा nvkm_समयr_रुको अणु
	काष्ठा nvkm_समयr *पंचांगr;
	u64 limit;
	u64 समय0;
	u64 समय1;
	पूर्णांक पढ़ोs;
पूर्ण;

व्योम nvkm_समयr_रुको_init(काष्ठा nvkm_device *, u64 nsec,
			  काष्ठा nvkm_समयr_रुको *);
s64 nvkm_समयr_रुको_test(काष्ठा nvkm_समयr_रुको *);

/* Delay based on GPU समय (ie. PTIMER).
 *
 * Will वापस -ETIMEDOUT unless the loop was terminated with 'break',
 * where it will वापस the number of nanoseconds taken instead.
 *
 * NVKM_DELAY can be passed क्रम 'cond' to disable the समयout warning,
 * which is useful क्रम unconditional delay loops.
 */
#घोषणा NVKM_DELAY _warn = false;
#घोषणा nvkm_nsec(d,n,cond...) (अणु                                              \
	काष्ठा nvkm_समयr_रुको _रुको;                                          \
	bool _warn = true;                                                     \
	s64 _taken = 0;                                                        \
                                                                               \
	nvkm_समयr_रुको_init((d), (n), &_रुको);                                \
	करो अणु                                                                   \
		cond                                                           \
	पूर्ण जबतक ((_taken = nvkm_समयr_रुको_test(&_रुको)) >= 0);                \
                                                                               \
	अगर (_warn && _taken < 0)                                               \
		dev_WARN(_रुको.पंचांगr->subdev.device->dev, "timeout\n");          \
	_taken;                                                                \
पूर्ण)
#घोषणा nvkm_usec(d, u, cond...) nvkm_nsec((d), (u) * 1000ULL, ##cond)
#घोषणा nvkm_msec(d, m, cond...) nvkm_usec((d), (m) * 1000ULL, ##cond)

#घोषणा nvkm_रुको_nsec(d,n,addr,mask,data)                                     \
	nvkm_nsec(d, n,                                                        \
		अगर ((nvkm_rd32(d, (addr)) & (mask)) == (data))                 \
			अवरोध;                                                 \
		)
#घोषणा nvkm_रुको_usec(d,u,addr,mask,data)                                     \
	nvkm_रुको_nsec((d), (u) * 1000, (addr), (mask), (data))
#घोषणा nvkm_रुको_msec(d,m,addr,mask,data)                                     \
	nvkm_रुको_usec((d), (m) * 1000, (addr), (mask), (data))

पूर्णांक nv04_समयr_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_समयr **);
पूर्णांक nv40_समयr_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_समयr **);
पूर्णांक nv41_समयr_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_समयr **);
पूर्णांक gk20a_समयr_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_समयr **);
#पूर्ण_अगर
