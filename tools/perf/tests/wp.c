<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/kernel.h>
#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "event.h"
#समावेश "cloexec.h"
#समावेश "../perf-sys.h"

#घोषणा WP_TEST_ASSERT_VAL(fd, text, val)       \
करो अणु                                            \
	दीर्घ दीर्घ count;                        \
	wp_पढ़ो(fd, &count, माप(दीर्घ दीर्घ)); \
	TEST_ASSERT_VAL(text, count == val);    \
पूर्ण जबतक (0)

अस्थिर u64 data1;
अस्थिर u8 data2[3];

अटल पूर्णांक wp_पढ़ो(पूर्णांक fd, दीर्घ दीर्घ *count, पूर्णांक size)
अणु
	पूर्णांक ret = पढ़ो(fd, count, size);

	अगर (ret != size) अणु
		pr_debug("failed to read: %d\n", ret);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम get__perf_event_attr(काष्ठा perf_event_attr *attr, पूर्णांक wp_type,
				 व्योम *wp_addr, अचिन्हित दीर्घ wp_len)
अणु
	स_रखो(attr, 0, माप(काष्ठा perf_event_attr));
	attr->type           = PERF_TYPE_BREAKPOINT;
	attr->size           = माप(काष्ठा perf_event_attr);
	attr->config         = 0;
	attr->bp_type        = wp_type;
	attr->bp_addr        = (अचिन्हित दीर्घ)wp_addr;
	attr->bp_len         = wp_len;
	attr->sample_period  = 1;
	attr->sample_type    = PERF_SAMPLE_IP;
	attr->exclude_kernel = 1;
	attr->exclude_hv     = 1;
पूर्ण

अटल पूर्णांक __event(पूर्णांक wp_type, व्योम *wp_addr, अचिन्हित दीर्घ wp_len)
अणु
	पूर्णांक fd;
	काष्ठा perf_event_attr attr;

	get__perf_event_attr(&attr, wp_type, wp_addr, wp_len);
	fd = sys_perf_event_खोलो(&attr, 0, -1, -1,
				 perf_event_खोलो_cloexec_flag());
	अगर (fd < 0)
		pr_debug("failed opening event %x\n", attr.bp_type);

	वापस fd;
पूर्ण

अटल पूर्णांक wp_ro_test(व्योम)
अणु
	पूर्णांक fd;
	अचिन्हित दीर्घ पंचांगp, पंचांगp1 = अक्रम();

	fd = __event(HW_BREAKPOINT_R, (व्योम *)&data1, माप(data1));
	अगर (fd < 0)
		वापस -1;

	पंचांगp = data1;
	WP_TEST_ASSERT_VAL(fd, "RO watchpoint", 1);

	data1 = पंचांगp1 + पंचांगp;
	WP_TEST_ASSERT_VAL(fd, "RO watchpoint", 1);

	बंद(fd);
	वापस 0;
पूर्ण

अटल पूर्णांक wp_wo_test(व्योम)
अणु
	पूर्णांक fd;
	अचिन्हित दीर्घ पंचांगp, पंचांगp1 = अक्रम();

	fd = __event(HW_BREAKPOINT_W, (व्योम *)&data1, माप(data1));
	अगर (fd < 0)
		वापस -1;

	पंचांगp = data1;
	WP_TEST_ASSERT_VAL(fd, "WO watchpoint", 0);

	data1 = पंचांगp1 + पंचांगp;
	WP_TEST_ASSERT_VAL(fd, "WO watchpoint", 1);

	बंद(fd);
	वापस 0;
पूर्ण

अटल पूर्णांक wp_rw_test(व्योम)
अणु
	पूर्णांक fd;
	अचिन्हित दीर्घ पंचांगp, पंचांगp1 = अक्रम();

	fd = __event(HW_BREAKPOINT_R | HW_BREAKPOINT_W, (व्योम *)&data1,
		     माप(data1));
	अगर (fd < 0)
		वापस -1;

	पंचांगp = data1;
	WP_TEST_ASSERT_VAL(fd, "RW watchpoint", 1);

	data1 = पंचांगp1 + पंचांगp;
	WP_TEST_ASSERT_VAL(fd, "RW watchpoint", 2);

	बंद(fd);
	वापस 0;
पूर्ण

अटल पूर्णांक wp_modअगरy_test(व्योम)
अणु
	पूर्णांक fd, ret;
	अचिन्हित दीर्घ पंचांगp = अक्रम();
	काष्ठा perf_event_attr new_attr;

	fd = __event(HW_BREAKPOINT_W, (व्योम *)&data1, माप(data1));
	अगर (fd < 0)
		वापस -1;

	data1 = पंचांगp;
	WP_TEST_ASSERT_VAL(fd, "Modify watchpoint", 1);

	/* Modअगरy watchpoपूर्णांक with disabled = 1 */
	get__perf_event_attr(&new_attr, HW_BREAKPOINT_W, (व्योम *)&data2[0],
			     माप(u8) * 2);
	new_attr.disabled = 1;
	ret = ioctl(fd, PERF_EVENT_IOC_MODIFY_ATTRIBUTES, &new_attr);
	अगर (ret < 0) अणु
		pr_debug("ioctl(PERF_EVENT_IOC_MODIFY_ATTRIBUTES) failed\n");
		बंद(fd);
		वापस ret;
	पूर्ण

	data2[1] = पंचांगp; /* Not Counted */
	WP_TEST_ASSERT_VAL(fd, "Modify watchpoint", 1);

	/* Enable the event */
	ioctl(fd, PERF_EVENT_IOC_ENABLE, 0);
	अगर (ret < 0) अणु
		pr_debug("Failed to enable event\n");
		बंद(fd);
		वापस ret;
	पूर्ण

	data2[1] = पंचांगp; /* Counted */
	WP_TEST_ASSERT_VAL(fd, "Modify watchpoint", 2);

	data2[2] = पंचांगp; /* Not Counted */
	WP_TEST_ASSERT_VAL(fd, "Modify watchpoint", 2);

	बंद(fd);
	वापस 0;
पूर्ण

अटल bool wp_ro_supported(व्योम)
अणु
#अगर defined (__x86_64__) || defined (__i386__)
	वापस false;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण

अटल स्थिर अक्षर *wp_ro_skip_msg(व्योम)
अणु
#अगर defined (__x86_64__) || defined (__i386__)
	वापस "missing hardware support";
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा अणु
	स्थिर अक्षर *desc;
	पूर्णांक (*target_func)(व्योम);
	bool (*is_supported)(व्योम);
	स्थिर अक्षर *(*skip_msg)(व्योम);
पूर्ण wp_testहाल_table[] = अणु
	अणु
		.desc = "Read Only Watchpoint",
		.target_func = &wp_ro_test,
		.is_supported = &wp_ro_supported,
		.skip_msg = &wp_ro_skip_msg,
	पूर्ण,
	अणु
		.desc = "Write Only Watchpoint",
		.target_func = &wp_wo_test,
	पूर्ण,
	अणु
		.desc = "Read / Write Watchpoint",
		.target_func = &wp_rw_test,
	पूर्ण,
	अणु
		.desc = "Modify Watchpoint",
		.target_func = &wp_modअगरy_test,
	पूर्ण,
पूर्ण;

पूर्णांक test__wp_subtest_get_nr(व्योम)
अणु
	वापस (पूर्णांक)ARRAY_SIZE(wp_testहाल_table);
पूर्ण

स्थिर अक्षर *test__wp_subtest_get_desc(पूर्णांक i)
अणु
	अगर (i < 0 || i >= (पूर्णांक)ARRAY_SIZE(wp_testहाल_table))
		वापस शून्य;
	वापस wp_testहाल_table[i].desc;
पूर्ण

स्थिर अक्षर *test__wp_subtest_skip_reason(पूर्णांक i)
अणु
	अगर (i < 0 || i >= (पूर्णांक)ARRAY_SIZE(wp_testहाल_table))
		वापस शून्य;
	अगर (!wp_testहाल_table[i].skip_msg)
		वापस शून्य;
	वापस wp_testहाल_table[i].skip_msg();
पूर्ण

पूर्णांक test__wp(काष्ठा test *test __maybe_unused, पूर्णांक i)
अणु
	अगर (i < 0 || i >= (पूर्णांक)ARRAY_SIZE(wp_testहाल_table))
		वापस TEST_FAIL;

	अगर (wp_testहाल_table[i].is_supported &&
	    !wp_testहाल_table[i].is_supported())
		वापस TEST_SKIP;

	वापस !wp_testहाल_table[i].target_func() ? TEST_OK : TEST_FAIL;
पूर्ण

/* The s390 so far करोes not have support क्रम
 * inकाष्ठाion अवरोधpoपूर्णांक using the perf_event_खोलो() प्रणाली call.
 */
bool test__wp_is_supported(व्योम)
अणु
#अगर defined(__s390x__)
	वापस false;
#अन्यथा
	वापस true;
#पूर्ण_अगर
पूर्ण
