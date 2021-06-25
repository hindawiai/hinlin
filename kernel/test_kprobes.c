<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * test_kprobes.c - simple sanity test क्रम *probes
 *
 * Copyright IBM Corp. 2008
 */

#घोषणा pr_fmt(fmt) "Kprobe smoke test: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/अक्रमom.h>

#घोषणा भाग_factor 3

अटल u32 अक्रम1, preh_val, posth_val;
अटल पूर्णांक errors, handler_errors, num_tests;
अटल u32 (*target)(u32 value);
अटल u32 (*target2)(u32 value);

अटल noअंतरभूत u32 kprobe_target(u32 value)
अणु
	वापस (value / भाग_factor);
पूर्ण

अटल पूर्णांक kp_pre_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	अगर (preemptible()) अणु
		handler_errors++;
		pr_err("pre-handler is preemptible\n");
	पूर्ण
	preh_val = (अक्रम1 / भाग_factor);
	वापस 0;
पूर्ण

अटल व्योम kp_post_handler(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
		अचिन्हित दीर्घ flags)
अणु
	अगर (preemptible()) अणु
		handler_errors++;
		pr_err("post-handler is preemptible\n");
	पूर्ण
	अगर (preh_val != (अक्रम1 / भाग_factor)) अणु
		handler_errors++;
		pr_err("incorrect value in post_handler\n");
	पूर्ण
	posth_val = preh_val + भाग_factor;
पूर्ण

अटल काष्ठा kprobe kp = अणु
	.symbol_name = "kprobe_target",
	.pre_handler = kp_pre_handler,
	.post_handler = kp_post_handler
पूर्ण;

अटल पूर्णांक test_kprobe(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_kprobe(&kp);
	अगर (ret < 0) अणु
		pr_err("register_kprobe returned %d\n", ret);
		वापस ret;
	पूर्ण

	ret = target(अक्रम1);
	unरेजिस्टर_kprobe(&kp);

	अगर (preh_val == 0) अणु
		pr_err("kprobe pre_handler not called\n");
		handler_errors++;
	पूर्ण

	अगर (posth_val == 0) अणु
		pr_err("kprobe post_handler not called\n");
		handler_errors++;
	पूर्ण

	वापस 0;
पूर्ण

अटल noअंतरभूत u32 kprobe_target2(u32 value)
अणु
	वापस (value / भाग_factor) + 1;
पूर्ण

अटल पूर्णांक kp_pre_handler2(काष्ठा kprobe *p, काष्ठा pt_regs *regs)
अणु
	preh_val = (अक्रम1 / भाग_factor) + 1;
	वापस 0;
पूर्ण

अटल व्योम kp_post_handler2(काष्ठा kprobe *p, काष्ठा pt_regs *regs,
		अचिन्हित दीर्घ flags)
अणु
	अगर (preh_val != (अक्रम1 / भाग_factor) + 1) अणु
		handler_errors++;
		pr_err("incorrect value in post_handler2\n");
	पूर्ण
	posth_val = preh_val + भाग_factor;
पूर्ण

अटल काष्ठा kprobe kp2 = अणु
	.symbol_name = "kprobe_target2",
	.pre_handler = kp_pre_handler2,
	.post_handler = kp_post_handler2
पूर्ण;

अटल पूर्णांक test_kprobes(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा kprobe *kps[2] = अणु&kp, &kp2पूर्ण;

	/* addr and flags should be cleard क्रम reusing kprobe. */
	kp.addr = शून्य;
	kp.flags = 0;
	ret = रेजिस्टर_kprobes(kps, 2);
	अगर (ret < 0) अणु
		pr_err("register_kprobes returned %d\n", ret);
		वापस ret;
	पूर्ण

	preh_val = 0;
	posth_val = 0;
	ret = target(अक्रम1);

	अगर (preh_val == 0) अणु
		pr_err("kprobe pre_handler not called\n");
		handler_errors++;
	पूर्ण

	अगर (posth_val == 0) अणु
		pr_err("kprobe post_handler not called\n");
		handler_errors++;
	पूर्ण

	preh_val = 0;
	posth_val = 0;
	ret = target2(अक्रम1);

	अगर (preh_val == 0) अणु
		pr_err("kprobe pre_handler2 not called\n");
		handler_errors++;
	पूर्ण

	अगर (posth_val == 0) अणु
		pr_err("kprobe post_handler2 not called\n");
		handler_errors++;
	पूर्ण

	unरेजिस्टर_kprobes(kps, 2);
	वापस 0;

पूर्ण

#अगर_घोषित CONFIG_KRETPROBES
अटल u32 krph_val;

अटल पूर्णांक entry_handler(काष्ठा kretprobe_instance *ri, काष्ठा pt_regs *regs)
अणु
	अगर (preemptible()) अणु
		handler_errors++;
		pr_err("kretprobe entry handler is preemptible\n");
	पूर्ण
	krph_val = (अक्रम1 / भाग_factor);
	वापस 0;
पूर्ण

अटल पूर्णांक वापस_handler(काष्ठा kretprobe_instance *ri, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ret = regs_वापस_value(regs);

	अगर (preemptible()) अणु
		handler_errors++;
		pr_err("kretprobe return handler is preemptible\n");
	पूर्ण
	अगर (ret != (अक्रम1 / भाग_factor)) अणु
		handler_errors++;
		pr_err("incorrect value in kretprobe handler\n");
	पूर्ण
	अगर (krph_val == 0) अणु
		handler_errors++;
		pr_err("call to kretprobe entry handler failed\n");
	पूर्ण

	krph_val = अक्रम1;
	वापस 0;
पूर्ण

अटल काष्ठा kretprobe rp = अणु
	.handler	= वापस_handler,
	.entry_handler  = entry_handler,
	.kp.symbol_name = "kprobe_target"
पूर्ण;

अटल पूर्णांक test_kretprobe(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_kretprobe(&rp);
	अगर (ret < 0) अणु
		pr_err("register_kretprobe returned %d\n", ret);
		वापस ret;
	पूर्ण

	ret = target(अक्रम1);
	unरेजिस्टर_kretprobe(&rp);
	अगर (krph_val != अक्रम1) अणु
		pr_err("kretprobe handler not called\n");
		handler_errors++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक वापस_handler2(काष्ठा kretprobe_instance *ri, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ret = regs_वापस_value(regs);

	अगर (ret != (अक्रम1 / भाग_factor) + 1) अणु
		handler_errors++;
		pr_err("incorrect value in kretprobe handler2\n");
	पूर्ण
	अगर (krph_val == 0) अणु
		handler_errors++;
		pr_err("call to kretprobe entry handler failed\n");
	पूर्ण

	krph_val = अक्रम1;
	वापस 0;
पूर्ण

अटल काष्ठा kretprobe rp2 = अणु
	.handler	= वापस_handler2,
	.entry_handler  = entry_handler,
	.kp.symbol_name = "kprobe_target2"
पूर्ण;

अटल पूर्णांक test_kretprobes(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा kretprobe *rps[2] = अणु&rp, &rp2पूर्ण;

	/* addr and flags should be cleard क्रम reusing kprobe. */
	rp.kp.addr = शून्य;
	rp.kp.flags = 0;
	ret = रेजिस्टर_kretprobes(rps, 2);
	अगर (ret < 0) अणु
		pr_err("register_kretprobe returned %d\n", ret);
		वापस ret;
	पूर्ण

	krph_val = 0;
	ret = target(अक्रम1);
	अगर (krph_val != अक्रम1) अणु
		pr_err("kretprobe handler not called\n");
		handler_errors++;
	पूर्ण

	krph_val = 0;
	ret = target2(अक्रम1);
	अगर (krph_val != अक्रम1) अणु
		pr_err("kretprobe handler2 not called\n");
		handler_errors++;
	पूर्ण
	unरेजिस्टर_kretprobes(rps, 2);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_KRETPROBES */

पूर्णांक init_test_probes(व्योम)
अणु
	पूर्णांक ret;

	target = kprobe_target;
	target2 = kprobe_target2;

	करो अणु
		अक्रम1 = pअक्रमom_u32();
	पूर्ण जबतक (अक्रम1 <= भाग_factor);

	pr_info("started\n");
	num_tests++;
	ret = test_kprobe();
	अगर (ret < 0)
		errors++;

	num_tests++;
	ret = test_kprobes();
	अगर (ret < 0)
		errors++;

#अगर_घोषित CONFIG_KRETPROBES
	num_tests++;
	ret = test_kretprobe();
	अगर (ret < 0)
		errors++;

	num_tests++;
	ret = test_kretprobes();
	अगर (ret < 0)
		errors++;
#पूर्ण_अगर /* CONFIG_KRETPROBES */

	अगर (errors)
		pr_err("BUG: %d out of %d tests failed\n", errors, num_tests);
	अन्यथा अगर (handler_errors)
		pr_err("BUG: %d error(s) running handlers\n", handler_errors);
	अन्यथा
		pr_info("passed successfully\n");

	वापस 0;
पूर्ण
