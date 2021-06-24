<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020, Oracle and/or its affiliates.
 *    Author: Alan Maguire <alan.maguire@oracle.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/module.h>

#समावेश <kunit/test.h>

#समावेश "string-stream.h"

#घोषणा KUNIT_DEBUGFS_ROOT             "kunit"
#घोषणा KUNIT_DEBUGFS_RESULTS          "results"

/*
 * Create a debugfs representation of test suites:
 *
 * Path						Semantics
 * /sys/kernel/debug/kunit/<testsuite>/results	Show results of last run क्रम
 *						testsuite
 *
 */

अटल काष्ठा dentry *debugfs_rootdir;

व्योम kunit_debugfs_cleanup(व्योम)
अणु
	debugfs_हटाओ_recursive(debugfs_rootdir);
पूर्ण

व्योम kunit_debugfs_init(व्योम)
अणु
	अगर (!debugfs_rootdir)
		debugfs_rootdir = debugfs_create_dir(KUNIT_DEBUGFS_ROOT, शून्य);
पूर्ण

अटल व्योम debugfs_prपूर्णांक_result(काष्ठा seq_file *seq,
				 काष्ठा kunit_suite *suite,
				 काष्ठा kunit_हाल *test_हाल)
अणु
	अगर (!test_हाल || !test_हाल->log)
		वापस;

	seq_म_लिखो(seq, "%s", test_हाल->log);
पूर्ण

/*
 * /sys/kernel/debug/kunit/<testsuite>/results shows all results क्रम testsuite.
 */
अटल पूर्णांक debugfs_prपूर्णांक_results(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा kunit_suite *suite = (काष्ठा kunit_suite *)seq->निजी;
	bool success = kunit_suite_has_succeeded(suite);
	काष्ठा kunit_हाल *test_हाल;

	अगर (!suite || !suite->log)
		वापस 0;

	seq_म_लिखो(seq, "%s", suite->log);

	kunit_suite_क्रम_each_test_हाल(suite, test_हाल)
		debugfs_prपूर्णांक_result(seq, suite, test_हाल);

	seq_म_लिखो(seq, "%s %d - %s\n",
		   kunit_status_to_string(success), 1, suite->name);
	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_release(inode, file);
पूर्ण

अटल पूर्णांक debugfs_results_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा kunit_suite *suite;

	suite = (काष्ठा kunit_suite *)inode->i_निजी;

	वापस single_खोलो(file, debugfs_prपूर्णांक_results, suite);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_results_fops = अणु
	.खोलो = debugfs_results_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = debugfs_release,
पूर्ण;

व्योम kunit_debugfs_create_suite(काष्ठा kunit_suite *suite)
अणु
	काष्ठा kunit_हाल *test_हाल;

	/* Allocate logs beक्रमe creating debugfs representation. */
	suite->log = kzalloc(KUNIT_LOG_SIZE, GFP_KERNEL);
	kunit_suite_क्रम_each_test_हाल(suite, test_हाल)
		test_हाल->log = kzalloc(KUNIT_LOG_SIZE, GFP_KERNEL);

	suite->debugfs = debugfs_create_dir(suite->name, debugfs_rootdir);

	debugfs_create_file(KUNIT_DEBUGFS_RESULTS, S_IFREG | 0444,
			    suite->debugfs,
			    suite, &debugfs_results_fops);
पूर्ण

व्योम kunit_debugfs_destroy_suite(काष्ठा kunit_suite *suite)
अणु
	काष्ठा kunit_हाल *test_हाल;

	debugfs_हटाओ_recursive(suite->debugfs);
	kमुक्त(suite->log);
	kunit_suite_क्रम_each_test_हाल(suite, test_हाल)
		kमुक्त(test_हाल->log);
पूर्ण
