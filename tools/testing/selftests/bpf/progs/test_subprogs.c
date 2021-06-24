<शैली गुरु>
#समावेश "vmlinux.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

स्थिर अक्षर LICENSE[] SEC("license") = "GPL";

__noअंतरभूत पूर्णांक sub1(पूर्णांक x)
अणु
	वापस x + 1;
पूर्ण

अटल __noअंतरभूत पूर्णांक sub5(पूर्णांक v);

__noअंतरभूत पूर्णांक sub2(पूर्णांक y)
अणु
	वापस sub5(y + 2);
पूर्ण

अटल __noअंतरभूत पूर्णांक sub3(पूर्णांक z)
अणु
	वापस z + 3 + sub1(4);
पूर्ण

अटल __noअंतरभूत पूर्णांक sub4(पूर्णांक w)
अणु
	वापस w + sub3(5) + sub1(6);
पूर्ण

/* sub5() is an identitअगरy function, just to test weirder functions layout and
 * call patterns
 */
अटल __noअंतरभूत पूर्णांक sub5(पूर्णांक v)
अणु
	वापस sub1(v) - 1; /* compensates sub1()'s + 1 */
पूर्ण

/* unक्रमtunately verअगरier rejects `काष्ठा task_काष्ठा *t` as an unkown poपूर्णांकer
 * type, so we need to accept poपूर्णांकer as पूर्णांकeger and then cast it inside the
 * function
 */
__noअंतरभूत पूर्णांक get_task_tgid(uपूर्णांकptr_t t)
अणु
	/* this ensures that CO-RE relocs work in multi-subprogs .text */
	वापस BPF_CORE_READ((काष्ठा task_काष्ठा *)(व्योम *)t, tgid);
पूर्ण

पूर्णांक res1 = 0;
पूर्णांक res2 = 0;
पूर्णांक res3 = 0;
पूर्णांक res4 = 0;

SEC("raw_tp/sys_enter")
पूर्णांक prog1(व्योम *ctx)
अणु
	/* perक्रमm some CO-RE relocations to ensure they work with multi-prog
	 * sections correctly
	 */
	काष्ठा task_काष्ठा *t = (व्योम *)bpf_get_current_task();

	अगर (!BPF_CORE_READ(t, pid) || !get_task_tgid((uपूर्णांकptr_t)t))
		वापस 1;

	res1 = sub1(1) + sub3(2); /* (1 + 1) + (2 + 3 + (4 + 1)) = 12 */
	वापस 0;
पूर्ण

SEC("raw_tp/sys_exit")
पूर्णांक prog2(व्योम *ctx)
अणु
	काष्ठा task_काष्ठा *t = (व्योम *)bpf_get_current_task();

	अगर (!BPF_CORE_READ(t, pid) || !get_task_tgid((uपूर्णांकptr_t)t))
		वापस 1;

	res2 = sub2(3) + sub3(4); /* (3 + 2) + (4 + 3 + (4 + 1)) = 17 */
	वापस 0;
पूर्ण

/* prog3 has the same section name as prog1 */
SEC("raw_tp/sys_enter")
पूर्णांक prog3(व्योम *ctx)
अणु
	काष्ठा task_काष्ठा *t = (व्योम *)bpf_get_current_task();

	अगर (!BPF_CORE_READ(t, pid) || !get_task_tgid((uपूर्णांकptr_t)t))
		वापस 1;

	res3 = sub3(5) + 6; /* (5 + 3 + (4 + 1)) + 6 = 19 */
	वापस 0;
पूर्ण

/* prog4 has the same section name as prog2 */
SEC("raw_tp/sys_exit")
पूर्णांक prog4(व्योम *ctx)
अणु
	काष्ठा task_काष्ठा *t = (व्योम *)bpf_get_current_task();

	अगर (!BPF_CORE_READ(t, pid) || !get_task_tgid((uपूर्णांकptr_t)t))
		वापस 1;

	res4 = sub4(7) + sub1(8); /* (7 + (5 + 3 + (4 + 1)) + (6 + 1)) + (8 + 1) = 36 */
	वापस 0;
पूर्ण
