<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * udelay() test kernel module
 *
 * Test is executed by writing and पढ़ोing to /sys/kernel/debug/udelay_test
 * Tests are configured by writing: USECS ITERATIONS
 * Tests are executed by पढ़ोing from the same file.
 * Specअगरying usecs of 0 or negative values will run multiples tests.
 *
 * Copyright (C) 2014 Google, Inc.
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>

#घोषणा DEFAULT_ITERATIONS 100

#घोषणा DEBUGFS_खाताNAME "udelay_test"

अटल DEFINE_MUTEX(udelay_test_lock);
अटल पूर्णांक udelay_test_usecs;
अटल पूर्णांक udelay_test_iterations = DEFAULT_ITERATIONS;

अटल पूर्णांक udelay_test_single(काष्ठा seq_file *s, पूर्णांक usecs, uपूर्णांक32_t iters)
अणु
	पूर्णांक min = 0, max = 0, fail_count = 0;
	uपूर्णांक64_t sum = 0;
	uपूर्णांक64_t avg;
	पूर्णांक i;
	/* Allow udelay to be up to 0.5% fast */
	पूर्णांक allowed_error_ns = usecs * 5;

	क्रम (i = 0; i < iters; ++i) अणु
		s64 kt1, kt2;
		पूर्णांक समय_passed;

		kt1 = kसमय_get_ns();
		udelay(usecs);
		kt2 = kसमय_get_ns();
		समय_passed = kt2 - kt1;

		अगर (i == 0 || समय_passed < min)
			min = समय_passed;
		अगर (i == 0 || समय_passed > max)
			max = समय_passed;
		अगर ((समय_passed + allowed_error_ns) / 1000 < usecs)
			++fail_count;
		WARN_ON(समय_passed < 0);
		sum += समय_passed;
	पूर्ण

	avg = sum;
	करो_भाग(avg, iters);
	seq_म_लिखो(s, "%d usecs x %d: exp=%d allowed=%d min=%d avg=%lld max=%d",
			usecs, iters, usecs * 1000,
			(usecs * 1000) - allowed_error_ns, min, avg, max);
	अगर (fail_count)
		seq_म_लिखो(s, " FAIL=%d", fail_count);
	seq_माला_दो(s, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक udelay_test_show(काष्ठा seq_file *s, व्योम *v)
अणु
	पूर्णांक usecs;
	पूर्णांक iters;
	पूर्णांक ret = 0;

	mutex_lock(&udelay_test_lock);
	usecs = udelay_test_usecs;
	iters = udelay_test_iterations;
	mutex_unlock(&udelay_test_lock);

	अगर (usecs > 0 && iters > 0) अणु
		वापस udelay_test_single(s, usecs, iters);
	पूर्ण अन्यथा अगर (usecs == 0) अणु
		काष्ठा बारpec64 ts;

		kसमय_get_ts64(&ts);
		seq_म_लिखो(s, "udelay() test (lpj=%ld kt=%lld.%09ld)\n",
				loops_per_jअगरfy, (s64)ts.tv_sec, ts.tv_nsec);
		seq_माला_दो(s, "usage:\n");
		seq_माला_दो(s, "echo USECS [ITERS] > " DEBUGFS_खाताNAME "\n");
		seq_माला_दो(s, "cat " DEBUGFS_खाताNAME "\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक udelay_test_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, udelay_test_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार udelay_test_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *pos)
अणु
	अक्षर lbuf[32];
	पूर्णांक ret;
	पूर्णांक usecs;
	पूर्णांक iters;

	अगर (count >= माप(lbuf))
		वापस -EINVAL;

	अगर (copy_from_user(lbuf, buf, count))
		वापस -EFAULT;
	lbuf[count] = '\0';

	ret = माला_पूछो(lbuf, "%d %d", &usecs, &iters);
	अगर (ret < 1)
		वापस -EINVAL;
	अन्यथा अगर (ret < 2)
		iters = DEFAULT_ITERATIONS;

	mutex_lock(&udelay_test_lock);
	udelay_test_usecs = usecs;
	udelay_test_iterations = iters;
	mutex_unlock(&udelay_test_lock);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations udelay_test_debugfs_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = udelay_test_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = udelay_test_ग_लिखो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल पूर्णांक __init udelay_test_init(व्योम)
अणु
	mutex_lock(&udelay_test_lock);
	debugfs_create_file(DEBUGFS_खाताNAME, S_IRUSR, शून्य, शून्य,
			    &udelay_test_debugfs_ops);
	mutex_unlock(&udelay_test_lock);

	वापस 0;
पूर्ण

module_init(udelay_test_init);

अटल व्योम __निकास udelay_test_निकास(व्योम)
अणु
	mutex_lock(&udelay_test_lock);
	debugfs_हटाओ(debugfs_lookup(DEBUGFS_खाताNAME, शून्य));
	mutex_unlock(&udelay_test_lock);
पूर्ण

module_निकास(udelay_test_निकास);

MODULE_AUTHOR("David Riley <davidriley@chromium.org>");
MODULE_LICENSE("GPL");
