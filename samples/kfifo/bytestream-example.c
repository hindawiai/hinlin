<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sample kfअगरo byte stream implementation
 *
 * Copyright (C) 2010 Stefani Seibold <stefani@seibold.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kfअगरo.h>

/*
 * This module shows how to create a byte stream fअगरo.
 */

/* fअगरo size in elements (bytes) */
#घोषणा FIFO_SIZE	32

/* name of the proc entry */
#घोषणा	PROC_FIFO	"bytestream-fifo"

/* lock क्रम procfs पढ़ो access */
अटल DEFINE_MUTEX(पढ़ो_lock);

/* lock क्रम procfs ग_लिखो access */
अटल DEFINE_MUTEX(ग_लिखो_lock);

/*
 * define DYNAMIC in this example क्रम a dynamically allocated fअगरo.
 *
 * Otherwise the fअगरo storage will be a part of the fअगरo काष्ठाure.
 */
#अगर 0
#घोषणा DYNAMIC
#पूर्ण_अगर

#अगर_घोषित DYNAMIC
अटल काष्ठा kfअगरo test;
#अन्यथा
अटल DECLARE_KFIFO(test, अचिन्हित अक्षर, FIFO_SIZE);
#पूर्ण_अगर

अटल स्थिर अचिन्हित अक्षर expected_result[FIFO_SIZE] = अणु
	 3,  4,  5,  6,  7,  8,  9,  0,
	 1, 20, 21, 22, 23, 24, 25, 26,
	27, 28, 29, 30, 31, 32, 33, 34,
	35, 36, 37, 38, 39, 40, 41, 42,
पूर्ण;

अटल पूर्णांक __init testfunc(व्योम)
अणु
	अचिन्हित अक्षर	buf[6];
	अचिन्हित अक्षर	i, j;
	अचिन्हित पूर्णांक	ret;

	prपूर्णांकk(KERN_INFO "byte stream fifo test start\n");

	/* put string पूर्णांकo the fअगरo */
	kfअगरo_in(&test, "hello", 5);

	/* put values पूर्णांकo the fअगरo */
	क्रम (i = 0; i != 10; i++)
		kfअगरo_put(&test, i);

	/* show the number of used elements */
	prपूर्णांकk(KERN_INFO "fifo len: %u\n", kfअगरo_len(&test));

	/* get max of 5 bytes from the fअगरo */
	i = kfअगरo_out(&test, buf, 5);
	prपूर्णांकk(KERN_INFO "buf: %.*s\n", i, buf);

	/* get max of 2 elements from the fअगरo */
	ret = kfअगरo_out(&test, buf, 2);
	prपूर्णांकk(KERN_INFO "ret: %d\n", ret);
	/* and put it back to the end of the fअगरo */
	ret = kfअगरo_in(&test, buf, ret);
	prपूर्णांकk(KERN_INFO "ret: %d\n", ret);

	/* skip first element of the fअगरo */
	prपूर्णांकk(KERN_INFO "skip 1st element\n");
	kfअगरo_skip(&test);

	/* put values पूर्णांकo the fअगरo until is full */
	क्रम (i = 20; kfअगरo_put(&test, i); i++)
		;

	prपूर्णांकk(KERN_INFO "queue len: %u\n", kfअगरo_len(&test));

	/* show the first value without removing from the fअगरo */
	अगर (kfअगरo_peek(&test, &i))
		prपूर्णांकk(KERN_INFO "%d\n", i);

	/* check the correctness of all values in the fअगरo */
	j = 0;
	जबतक (kfअगरo_get(&test, &i)) अणु
		prपूर्णांकk(KERN_INFO "item = %d\n", i);
		अगर (i != expected_result[j++]) अणु
			prपूर्णांकk(KERN_WARNING "value mismatch: test failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण
	अगर (j != ARRAY_SIZE(expected_result)) अणु
		prपूर्णांकk(KERN_WARNING "size mismatch: test failed\n");
		वापस -EIO;
	पूर्ण
	prपूर्णांकk(KERN_INFO "test passed\n");

	वापस 0;
पूर्ण

अटल sमाप_प्रकार fअगरo_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक copied;

	अगर (mutex_lock_पूर्णांकerruptible(&ग_लिखो_lock))
		वापस -ERESTARTSYS;

	ret = kfअगरo_from_user(&test, buf, count, &copied);

	mutex_unlock(&ग_लिखो_lock);
	अगर (ret)
		वापस ret;

	वापस copied;
पूर्ण

अटल sमाप_प्रकार fअगरo_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
						माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक copied;

	अगर (mutex_lock_पूर्णांकerruptible(&पढ़ो_lock))
		वापस -ERESTARTSYS;

	ret = kfअगरo_to_user(&test, buf, count, &copied);

	mutex_unlock(&पढ़ो_lock);
	अगर (ret)
		वापस ret;

	वापस copied;
पूर्ण

अटल स्थिर काष्ठा proc_ops fअगरo_proc_ops = अणु
	.proc_पढ़ो	= fअगरo_पढ़ो,
	.proc_ग_लिखो	= fअगरo_ग_लिखो,
	.proc_lseek	= noop_llseek,
पूर्ण;

अटल पूर्णांक __init example_init(व्योम)
अणु
#अगर_घोषित DYNAMIC
	पूर्णांक ret;

	ret = kfअगरo_alloc(&test, FIFO_SIZE, GFP_KERNEL);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "error kfifo_alloc\n");
		वापस ret;
	पूर्ण
#अन्यथा
	INIT_KFIFO(test);
#पूर्ण_अगर
	अगर (testfunc() < 0) अणु
#अगर_घोषित DYNAMIC
		kfअगरo_मुक्त(&test);
#पूर्ण_अगर
		वापस -EIO;
	पूर्ण

	अगर (proc_create(PROC_FIFO, 0, शून्य, &fअगरo_proc_ops) == शून्य) अणु
#अगर_घोषित DYNAMIC
		kfअगरo_मुक्त(&test);
#पूर्ण_अगर
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास example_निकास(व्योम)
अणु
	हटाओ_proc_entry(PROC_FIFO, शून्य);
#अगर_घोषित DYNAMIC
	kfअगरo_मुक्त(&test);
#पूर्ण_अगर
पूर्ण

module_init(example_init);
module_निकास(example_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stefani Seibold <stefani@seibold.net>");
