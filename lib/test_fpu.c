<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Test हालs क्रम using भग्नing poपूर्णांक operations inside a kernel module.
 *
 * This tests kernel_fpu_begin() and kernel_fpu_end() functions, especially
 * when userland has modअगरied the भग्नing poपूर्णांक control रेजिस्टरs. The kernel
 * state might depend on the state set by the userland thपढ़ो that was active
 * beक्रमe a syscall.
 *
 * To facilitate the test, this module रेजिस्टरs file
 * /sys/kernel/debug/selftest_helpers/test_fpu, which when पढ़ो causes a
 * sequence of भग्नing poपूर्णांक operations. If the operations fail, either the
 * पढ़ो वापसs error status or the kernel crashes.
 * If the operations succeed, the पढ़ो वापसs "1\n".
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/debugfs.h>
#समावेश <यंत्र/fpu/api.h>

अटल पूर्णांक test_fpu(व्योम)
अणु
	/*
	 * This sequence of operations tests that rounding mode is
	 * to nearest and that denormal numbers are supported.
	 * Volatile variables are used to aव्योम compiler optimizing
	 * the calculations away.
	 */
	अस्थिर द्विगुन a, b, c, d, e, f, g;

	a = 4.0;
	b = 1e-15;
	c = 1e-310;

	/* Sets precision flag */
	d = a + b;

	/* Result depends on rounding mode */
	e = a + b / 2;

	/* Denormal and very large values */
	f = b / c;

	/* Depends on denormal support */
	g = a + c * f;

	अगर (d > a && e > a && g > a)
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक test_fpu_get(व्योम *data, u64 *val)
अणु
	पूर्णांक status = -EINVAL;

	kernel_fpu_begin();
	status = test_fpu();
	kernel_fpu_end();

	*val = 1;
	वापस status;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(test_fpu_fops, test_fpu_get, शून्य, "%lld\n");
अटल काष्ठा dentry *selftest_dir;

अटल पूर्णांक __init test_fpu_init(व्योम)
अणु
	selftest_dir = debugfs_create_dir("selftest_helpers", शून्य);
	अगर (!selftest_dir)
		वापस -ENOMEM;

	debugfs_create_file_unsafe("test_fpu", 0444, selftest_dir, शून्य,
				   &test_fpu_fops);

	वापस 0;
पूर्ण

अटल व्योम __निकास test_fpu_निकास(व्योम)
अणु
	debugfs_हटाओ(selftest_dir);
पूर्ण

module_init(test_fpu_init);
module_निकास(test_fpu_निकास);

MODULE_LICENSE("GPL");
