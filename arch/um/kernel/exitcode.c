<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

/*
 * If पढ़ो and ग_लिखो race, the पढ़ो will still atomically पढ़ो a valid
 * value.
 */
पूर्णांक uml_निकासcode = 0;

अटल पूर्णांक निकासcode_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	पूर्णांक val;

	/*
	 * Save uml_निकासcode in a local so that we करोn't need to guarantee
	 * that प्र_लिखो accesses it atomically.
	 */
	val = uml_निकासcode;
	seq_म_लिखो(m, "%d\n", val);
	वापस 0;
पूर्ण

अटल पूर्णांक निकासcode_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, निकासcode_proc_show, शून्य);
पूर्ण

अटल sमाप_प्रकार निकासcode_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	अक्षर *end, buf[माप("nnnnn\0")];
	माप_प्रकार size;
	पूर्णांक पंचांगp;

	size = min(count, माप(buf));
	अगर (copy_from_user(buf, buffer, size))
		वापस -EFAULT;

	पंचांगp = simple_म_से_दीर्घ(buf, &end, 0);
	अगर ((*end != '\0') && !है_खाली(*end))
		वापस -EINVAL;

	uml_निकासcode = पंचांगp;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops निकासcode_proc_ops = अणु
	.proc_खोलो	= निकासcode_proc_खोलो,
	.proc_पढ़ो	= seq_पढ़ो,
	.proc_lseek	= seq_lseek,
	.proc_release	= single_release,
	.proc_ग_लिखो	= निकासcode_proc_ग_लिखो,
पूर्ण;

अटल पूर्णांक make_proc_निकासcode(व्योम)
अणु
	काष्ठा proc_dir_entry *ent;

	ent = proc_create("exitcode", 0600, शून्य, &निकासcode_proc_ops);
	अगर (ent == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "make_proc_exitcode : Failed to register "
		       "/proc/exitcode\n");
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

__initcall(make_proc_निकासcode);
