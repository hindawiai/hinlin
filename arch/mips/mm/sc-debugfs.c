<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <यंत्र/bcache.h>
#समावेश <यंत्र/debug.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/init.h>

अटल sमाप_प्रकार sc_prefetch_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	bool enabled = bc_prefetch_is_enabled();
	अक्षर buf[3];

	buf[0] = enabled ? 'Y' : 'N';
	buf[1] = '\n';
	buf[2] = 0;

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण

अटल sमाप_प्रकार sc_prefetch_ग_लिखो(काष्ठा file *file,
				 स्थिर अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	bool enabled;
	पूर्णांक err;

	err = kstrtobool_from_user(user_buf, count, &enabled);
	अगर (err)
		वापस err;

	अगर (enabled)
		bc_prefetch_enable();
	अन्यथा
		bc_prefetch_disable();

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations sc_prefetch_fops = अणु
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
	.पढ़ो = sc_prefetch_पढ़ो,
	.ग_लिखो = sc_prefetch_ग_लिखो,
पूर्ण;

अटल पूर्णांक __init sc_debugfs_init(व्योम)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir("l2cache", mips_debugfs_dir);
	debugfs_create_file("prefetch", S_IRUGO | S_IWUSR, dir, शून्य,
			    &sc_prefetch_fops);
	वापस 0;
पूर्ण
late_initcall(sc_debugfs_init);
