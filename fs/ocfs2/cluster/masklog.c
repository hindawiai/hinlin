<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2004, 2005 Oracle.  All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>

#समावेश "masklog.h"

काष्ठा mlog_bits mlog_and_bits = MLOG_BITS_RHS(MLOG_INITIAL_AND_MASK);
EXPORT_SYMBOL_GPL(mlog_and_bits);
काष्ठा mlog_bits mlog_not_bits = MLOG_BITS_RHS(0);
EXPORT_SYMBOL_GPL(mlog_not_bits);

अटल sमाप_प्रकार mlog_mask_show(u64 mask, अक्षर *buf)
अणु
	अक्षर *state;

	अगर (__mlog_test_u64(mask, mlog_and_bits))
		state = "allow";
	अन्यथा अगर (__mlog_test_u64(mask, mlog_not_bits))
		state = "deny";
	अन्यथा
		state = "off";

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", state);
पूर्ण

अटल sमाप_प्रकार mlog_mask_store(u64 mask, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (!strnहालcmp(buf, "allow", 5)) अणु
		__mlog_set_u64(mask, mlog_and_bits);
		__mlog_clear_u64(mask, mlog_not_bits);
	पूर्ण अन्यथा अगर (!strnहालcmp(buf, "deny", 4)) अणु
		__mlog_set_u64(mask, mlog_not_bits);
		__mlog_clear_u64(mask, mlog_and_bits);
	पूर्ण अन्यथा अगर (!strnहालcmp(buf, "off", 3)) अणु
		__mlog_clear_u64(mask, mlog_not_bits);
		__mlog_clear_u64(mask, mlog_and_bits);
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

व्योम __mlog_prपूर्णांकk(स्थिर u64 *mask, स्थिर अक्षर *func, पूर्णांक line,
		   स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	स्थिर अक्षर *level;
	स्थिर अक्षर *prefix = "";

	अगर (!__mlog_test_u64(*mask, mlog_and_bits) ||
	    __mlog_test_u64(*mask, mlog_not_bits))
		वापस;

	अगर (*mask & ML_ERROR) अणु
		level = KERN_ERR;
		prefix = "ERROR: ";
	पूर्ण अन्यथा अगर (*mask & ML_NOTICE) अणु
		level = KERN_NOTICE;
	पूर्ण अन्यथा अणु
		level = KERN_INFO;
	पूर्ण

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk("%s(%s,%u,%u):%s:%d %s%pV",
	       level, current->comm, task_pid_nr(current),
	       raw_smp_processor_id(), func, line, prefix, &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(__mlog_prपूर्णांकk);

काष्ठा mlog_attribute अणु
	काष्ठा attribute attr;
	u64 mask;
पूर्ण;

#घोषणा to_mlog_attr(_attr) container_of(_attr, काष्ठा mlog_attribute, attr)

#घोषणा define_mask(_name) अणु			\
	.attr = अणु				\
		.name = #_name,			\
		.mode = S_IRUGO | S_IWUSR,	\
	पूर्ण,					\
	.mask = ML_##_name,			\
पूर्ण

अटल काष्ठा mlog_attribute mlog_attrs[MLOG_MAX_BITS] = अणु
	define_mask(TCP),
	define_mask(MSG),
	define_mask(SOCKET),
	define_mask(HEARTBEAT),
	define_mask(HB_BIO),
	define_mask(DLMFS),
	define_mask(DLM),
	define_mask(DLM_DOMAIN),
	define_mask(DLM_THREAD),
	define_mask(DLM_MASTER),
	define_mask(DLM_RECOVERY),
	define_mask(DLM_GLUE),
	define_mask(VOTE),
	define_mask(CONN),
	define_mask(QUORUM),
	define_mask(BASTS),
	define_mask(CLUSTER),
	define_mask(ERROR),
	define_mask(NOTICE),
	define_mask(KTHREAD),
पूर्ण;

अटल काष्ठा attribute *mlog_attr_ptrs[MLOG_MAX_BITS] = अणुशून्य, पूर्ण;

अटल sमाप_प्रकार mlog_show(काष्ठा kobject *obj, काष्ठा attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा mlog_attribute *mlog_attr = to_mlog_attr(attr);

	वापस mlog_mask_show(mlog_attr->mask, buf);
पूर्ण

अटल sमाप_प्रकार mlog_store(काष्ठा kobject *obj, काष्ठा attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mlog_attribute *mlog_attr = to_mlog_attr(attr);

	वापस mlog_mask_store(mlog_attr->mask, buf, count);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops mlog_attr_ops = अणु
	.show  = mlog_show,
	.store = mlog_store,
पूर्ण;

अटल काष्ठा kobj_type mlog_ktype = अणु
	.शेष_attrs = mlog_attr_ptrs,
	.sysfs_ops     = &mlog_attr_ops,
पूर्ण;

अटल काष्ठा kset mlog_kset = अणु
	.kobj   = अणु.ktype = &mlog_ktypeपूर्ण,
पूर्ण;

पूर्णांक mlog_sys_init(काष्ठा kset *o2cb_kset)
अणु
	पूर्णांक i = 0;

	जबतक (mlog_attrs[i].attr.mode) अणु
		mlog_attr_ptrs[i] = &mlog_attrs[i].attr;
		i++;
	पूर्ण
	mlog_attr_ptrs[i] = शून्य;

	kobject_set_name(&mlog_kset.kobj, "logmask");
	mlog_kset.kobj.kset = o2cb_kset;
	वापस kset_रेजिस्टर(&mlog_kset);
पूर्ण

व्योम mlog_sys_shutकरोwn(व्योम)
अणु
	kset_unरेजिस्टर(&mlog_kset);
पूर्ण
