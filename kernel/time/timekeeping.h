<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _KERNEL_TIME_TIMEKEEPING_H
#घोषणा _KERNEL_TIME_TIMEKEEPING_H
/*
 * Internal पूर्णांकerfaces क्रम kernel/समय/
 */
बाह्य kसमय_प्रकार kसमय_get_update_offsets_now(अचिन्हित पूर्णांक *cwsseq,
					    kसमय_प्रकार *offs_real,
					    kसमय_प्रकार *offs_boot,
					    kसमय_प्रकार *offs_tai);

बाह्य पूर्णांक समयkeeping_valid_क्रम_hres(व्योम);
बाह्य u64 समयkeeping_max_deferment(व्योम);
बाह्य व्योम समयkeeping_warp_घड़ी(व्योम);
बाह्य पूर्णांक समयkeeping_suspend(व्योम);
बाह्य व्योम समयkeeping_resume(व्योम);
#अगर_घोषित CONFIG_GENERIC_SCHED_CLOCK
बाह्य पूर्णांक sched_घड़ी_suspend(व्योम);
बाह्य व्योम sched_घड़ी_resume(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक sched_घड़ी_suspend(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम sched_घड़ी_resume(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम update_process_बार(पूर्णांक user);
बाह्य व्योम करो_समयr(अचिन्हित दीर्घ ticks);
बाह्य व्योम update_wall_समय(व्योम);

बाह्य raw_spinlock_t jअगरfies_lock;
बाह्य seqcount_raw_spinlock_t jअगरfies_seq;

#घोषणा CS_NAME_LEN	32

#पूर्ण_अगर
