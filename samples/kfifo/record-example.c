<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sample dynamic sized record fअगरo implementation
 *
 * Copyright (C) 2010 Stefani Seibold <stefani@seibold.net>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kfअगरo.h>

/*
 * This module shows how to create a variable sized record fअगरo.
 */

/* fअगरo size in elements (bytes) */
#घोषणा FIFO_SIZE	128

/* name of the proc entry */
#घोषणा	PROC_FIFO	"record-fifo"

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

/*
 * काष्ठा kfअगरo_rec_ptr_1 and  STRUCT_KFIFO_REC_1 can handle records of a
 * length between 0 and 255 bytes.
 *
 * काष्ठा kfअगरo_rec_ptr_2 and  STRUCT_KFIFO_REC_2 can handle records of a
 * length between 0 and 65535 bytes.
 */

#अगर_घोषित DYNAMIC
काष्ठा kfअगरo_rec_ptr_1 test;

#अन्यथा
प्रकार STRUCT_KFIFO_REC_1(FIFO_SIZE) mytest;

अटल mytest test;
#पूर्ण_अगर

अटल स्थिर अक्षर *expected_result[] = अणु
	"a",
	"bb",
	"ccc",
	"dddd",
	"eeeee",
	"ffffff",
	"ggggggg",
	"hhhhhhhh",
	"iiiiiiiii",
	"jjjjjjjjjj",
पूर्ण;

अटल पूर्णांक __init testfunc(व्योम)
अणु
	अक्षर		buf[100];
	अचिन्हित पूर्णांक	i;
	अचिन्हित पूर्णांक	ret;
	काष्ठा अणु अचिन्हित अक्षर buf[6]; पूर्ण hello = अणु "hello" पूर्ण;

	prपूर्णांकk(KERN_INFO "record fifo test start\n");

	kfअगरo_in(&test, &hello, माप(hello));

	/* show the size of the next record in the fअगरo */
	prपूर्णांकk(KERN_INFO "fifo peek len: %u\n", kfअगरo_peek_len(&test));

	/* put in variable length data */
	क्रम (i = 0; i < 10; i++) अणु
		स_रखो(buf, 'a' + i, i + 1);
		kfअगरo_in(&test, buf, i + 1);
	पूर्ण

	/* skip first element of the fअगरo */
	prपूर्णांकk(KERN_INFO "skip 1st element\n");
	kfअगरo_skip(&test);

	prपूर्णांकk(KERN_INFO "fifo len: %u\n", kfअगरo_len(&test));

	/* show the first record without removing from the fअगरo */
	ret = kfअगरo_out_peek(&test, buf, माप(buf));
	अगर (ret)
		prपूर्णांकk(KERN_INFO "%.*s\n", ret, buf);

	/* check the correctness of all values in the fअगरo */
	i = 0;
	जबतक (!kfअगरo_is_empty(&test)) अणु
		ret = kfअगरo_out(&test, buf, माप(buf));
		buf[ret] = '\0';
		prपूर्णांकk(KERN_INFO "item = %.*s\n", ret, buf);
		अगर (म_भेद(buf, expected_result[i++])) अणु
			prपूर्णांकk(KERN_WARNING "value mismatch: test failed\n");
			वापस -EIO;
		पूर्ण
	पूर्ण
	अगर (i != ARRAY_SIZE(expected_result)) अणु
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
