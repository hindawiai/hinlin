<शैली गुरु>
#अगर_अघोषित __NVIF_TIMER_H__
#घोषणा __NVIF_TIMER_H__
#समावेश <nvअगर/os.h>

काष्ठा nvअगर_समयr_रुको अणु
	काष्ठा nvअगर_device *device;
	u64 limit;
	u64 समय0;
	u64 समय1;
	पूर्णांक पढ़ोs;
पूर्ण;

व्योम nvअगर_समयr_रुको_init(काष्ठा nvअगर_device *, u64 nsec,
			  काष्ठा nvअगर_समयr_रुको *);
s64 nvअगर_समयr_रुको_test(काष्ठा nvअगर_समयr_रुको *);

/* Delay based on GPU समय (ie. PTIMER).
 *
 * Will वापस -ETIMEDOUT unless the loop was terminated with 'break',
 * where it will वापस the number of nanoseconds taken instead.
 */
#घोषणा nvअगर_nsec(d,n,cond...) (अणु                                              \
	काष्ठा nvअगर_समयr_रुको _रुको;                                          \
	s64 _taken = 0;                                                        \
                                                                               \
	nvअगर_समयr_रुको_init((d), (n), &_रुको);                                \
	करो अणु                                                                   \
		cond                                                           \
	पूर्ण जबतक ((_taken = nvअगर_समयr_रुको_test(&_रुको)) >= 0);                \
                                                                               \
	_taken;                                                                \
पूर्ण)
#घोषणा nvअगर_usec(d,u,cond...) nvअगर_nsec((d), (u) * 1000, ##cond)
#घोषणा nvअगर_msec(d,m,cond...) nvअगर_usec((d), (m) * 1000, ##cond)
#पूर्ण_अगर
