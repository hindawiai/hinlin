<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>

/* validate @native and @pcp counter values match @expected */
#घोषणा CHECK(native, pcp, expected)                                    \
	करो अणु                                                            \
		WARN((native) != (expected),                            \
		     "raw %ld (0x%lx) != expected %lld (0x%llx)",	\
		     (native), (native),				\
		     (दीर्घ दीर्घ)(expected), (दीर्घ दीर्घ)(expected));	\
		WARN(__this_cpu_पढ़ो(pcp) != (expected),                \
		     "pcp %ld (0x%lx) != expected %lld (0x%llx)",	\
		     __this_cpu_पढ़ो(pcp), __this_cpu_पढ़ो(pcp),	\
		     (दीर्घ दीर्घ)(expected), (दीर्घ दीर्घ)(expected));	\
	पूर्ण जबतक (0)

अटल DEFINE_PER_CPU(दीर्घ, दीर्घ_counter);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, uदीर्घ_counter);

अटल पूर्णांक __init percpu_test_init(व्योम)
अणु
	/*
	 * अस्थिर prevents compiler from optimizing it uses, otherwise the
	 * +ul_one/-ul_one below would replace with inc/dec inकाष्ठाions.
	 */
	अस्थिर अचिन्हित पूर्णांक ui_one = 1;
	दीर्घ l = 0;
	अचिन्हित दीर्घ ul = 0;

	pr_info("percpu test start\n");

	preempt_disable();

	l += -1;
	__this_cpu_add(दीर्घ_counter, -1);
	CHECK(l, दीर्घ_counter, -1);

	l += 1;
	__this_cpu_add(दीर्घ_counter, 1);
	CHECK(l, दीर्घ_counter, 0);

	ul = 0;
	__this_cpu_ग_लिखो(uदीर्घ_counter, 0);

	ul += 1UL;
	__this_cpu_add(uदीर्घ_counter, 1UL);
	CHECK(ul, uदीर्घ_counter, 1);

	ul += -1UL;
	__this_cpu_add(uदीर्घ_counter, -1UL);
	CHECK(ul, uदीर्घ_counter, 0);

	ul += -(अचिन्हित दीर्घ)1;
	__this_cpu_add(uदीर्घ_counter, -(अचिन्हित दीर्घ)1);
	CHECK(ul, uदीर्घ_counter, -1);

	ul = 0;
	__this_cpu_ग_लिखो(uदीर्घ_counter, 0);

	ul -= 1;
	__this_cpu_dec(uदीर्घ_counter);
	CHECK(ul, uदीर्घ_counter, -1);
	CHECK(ul, uदीर्घ_counter, अच_दीर्घ_उच्च);

	l += -ui_one;
	__this_cpu_add(दीर्घ_counter, -ui_one);
	CHECK(l, दीर्घ_counter, 0xffffffff);

	l += ui_one;
	__this_cpu_add(दीर्घ_counter, ui_one);
	CHECK(l, दीर्घ_counter, (दीर्घ)0x100000000LL);


	l = 0;
	__this_cpu_ग_लिखो(दीर्घ_counter, 0);

	l -= ui_one;
	__this_cpu_sub(दीर्घ_counter, ui_one);
	CHECK(l, दीर्घ_counter, -1);

	l = 0;
	__this_cpu_ग_लिखो(दीर्घ_counter, 0);

	l += ui_one;
	__this_cpu_add(दीर्घ_counter, ui_one);
	CHECK(l, दीर्घ_counter, 1);

	l += -ui_one;
	__this_cpu_add(दीर्घ_counter, -ui_one);
	CHECK(l, दीर्घ_counter, (दीर्घ)0x100000000LL);

	l = 0;
	__this_cpu_ग_लिखो(दीर्घ_counter, 0);

	l -= ui_one;
	this_cpu_sub(दीर्घ_counter, ui_one);
	CHECK(l, दीर्घ_counter, -1);
	CHECK(l, दीर्घ_counter, अच_दीर्घ_उच्च);

	ul = 0;
	__this_cpu_ग_लिखो(uदीर्घ_counter, 0);

	ul += ui_one;
	__this_cpu_add(uदीर्घ_counter, ui_one);
	CHECK(ul, uदीर्घ_counter, 1);

	ul = 0;
	__this_cpu_ग_लिखो(uदीर्घ_counter, 0);

	ul -= ui_one;
	__this_cpu_sub(uदीर्घ_counter, ui_one);
	CHECK(ul, uदीर्घ_counter, -1);
	CHECK(ul, uदीर्घ_counter, अच_दीर्घ_उच्च);

	ul = 3;
	__this_cpu_ग_लिखो(uदीर्घ_counter, 3);

	ul = this_cpu_sub_वापस(uदीर्घ_counter, ui_one);
	CHECK(ul, uदीर्घ_counter, 2);

	ul = __this_cpu_sub_वापस(uदीर्घ_counter, ui_one);
	CHECK(ul, uदीर्घ_counter, 1);

	preempt_enable();

	pr_info("percpu test done\n");
	वापस -EAGAIN;  /* Fail will directly unload the module */
पूर्ण

अटल व्योम __निकास percpu_test_निकास(व्योम)
अणु
पूर्ण

module_init(percpu_test_init)
module_निकास(percpu_test_निकास)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Greg Thelen");
MODULE_DESCRIPTION("percpu operations test");
