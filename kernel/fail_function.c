<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * fail_function.c: Function-based error injection
 */
#समावेश <linux/error-injection.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

अटल पूर्णांक fei_kprobe_handler(काष्ठा kprobe *kp, काष्ठा pt_regs *regs);

अटल व्योम fei_post_handler(काष्ठा kprobe *kp, काष्ठा pt_regs *regs,
			     अचिन्हित दीर्घ flags)
अणु
	/*
	 * A dummy post handler is required to prohibit optimizing, because
	 * jump optimization करोes not support execution path overriding.
	 */
पूर्ण

काष्ठा fei_attr अणु
	काष्ठा list_head list;
	काष्ठा kprobe kp;
	अचिन्हित दीर्घ retval;
पूर्ण;
अटल DEFINE_MUTEX(fei_lock);
अटल LIST_HEAD(fei_attr_list);
अटल DECLARE_FAULT_ATTR(fei_fault_attr);
अटल काष्ठा dentry *fei_debugfs_dir;

अटल अचिन्हित दीर्घ adjust_error_retval(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ retv)
अणु
	चयन (get_injectable_error_type(addr)) अणु
	हाल EI_ETYPE_शून्य:
		वापस 0;
	हाल EI_ETYPE_ERRNO:
		अगर (retv < (अचिन्हित दीर्घ)-MAX_ERRNO)
			वापस (अचिन्हित दीर्घ)-EINVAL;
		अवरोध;
	हाल EI_ETYPE_ERRNO_शून्य:
		अगर (retv != 0 && retv < (अचिन्हित दीर्घ)-MAX_ERRNO)
			वापस (अचिन्हित दीर्घ)-EINVAL;
		अवरोध;
	हाल EI_ETYPE_TRUE:
		वापस 1;
	पूर्ण

	वापस retv;
पूर्ण

अटल काष्ठा fei_attr *fei_attr_new(स्थिर अक्षर *sym, अचिन्हित दीर्घ addr)
अणु
	काष्ठा fei_attr *attr;

	attr = kzalloc(माप(*attr), GFP_KERNEL);
	अगर (attr) अणु
		attr->kp.symbol_name = kstrdup(sym, GFP_KERNEL);
		अगर (!attr->kp.symbol_name) अणु
			kमुक्त(attr);
			वापस शून्य;
		पूर्ण
		attr->kp.pre_handler = fei_kprobe_handler;
		attr->kp.post_handler = fei_post_handler;
		attr->retval = adjust_error_retval(addr, 0);
		INIT_LIST_HEAD(&attr->list);
	पूर्ण
	वापस attr;
पूर्ण

अटल व्योम fei_attr_मुक्त(काष्ठा fei_attr *attr)
अणु
	अगर (attr) अणु
		kमुक्त(attr->kp.symbol_name);
		kमुक्त(attr);
	पूर्ण
पूर्ण

अटल काष्ठा fei_attr *fei_attr_lookup(स्थिर अक्षर *sym)
अणु
	काष्ठा fei_attr *attr;

	list_क्रम_each_entry(attr, &fei_attr_list, list) अणु
		अगर (!म_भेद(attr->kp.symbol_name, sym))
			वापस attr;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool fei_attr_is_valid(काष्ठा fei_attr *_attr)
अणु
	काष्ठा fei_attr *attr;

	list_क्रम_each_entry(attr, &fei_attr_list, list) अणु
		अगर (attr == _attr)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक fei_retval_set(व्योम *data, u64 val)
अणु
	काष्ठा fei_attr *attr = data;
	अचिन्हित दीर्घ retv = (अचिन्हित दीर्घ)val;
	पूर्णांक err = 0;

	mutex_lock(&fei_lock);
	/*
	 * Since this operation can be करोne after retval file is हटाओd,
	 * It is safer to check the attr is still valid beक्रमe accessing
	 * its member.
	 */
	अगर (!fei_attr_is_valid(attr)) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	अगर (attr->kp.addr) अणु
		अगर (adjust_error_retval((अचिन्हित दीर्घ)attr->kp.addr,
					val) != retv)
			err = -EINVAL;
	पूर्ण
	अगर (!err)
		attr->retval = val;
out:
	mutex_unlock(&fei_lock);

	वापस err;
पूर्ण

अटल पूर्णांक fei_retval_get(व्योम *data, u64 *val)
अणु
	काष्ठा fei_attr *attr = data;
	पूर्णांक err = 0;

	mutex_lock(&fei_lock);
	/* Here we also validate @attr to ensure it still exists. */
	अगर (!fei_attr_is_valid(attr))
		err = -ENOENT;
	अन्यथा
		*val = attr->retval;
	mutex_unlock(&fei_lock);

	वापस err;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fei_retval_ops, fei_retval_get, fei_retval_set,
			 "%llx\n");

अटल व्योम fei_debugfs_add_attr(काष्ठा fei_attr *attr)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir(attr->kp.symbol_name, fei_debugfs_dir);

	debugfs_create_file("retval", 0600, dir, attr, &fei_retval_ops);
पूर्ण

अटल व्योम fei_debugfs_हटाओ_attr(काष्ठा fei_attr *attr)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_lookup(attr->kp.symbol_name, fei_debugfs_dir);
	debugfs_हटाओ_recursive(dir);
पूर्ण

अटल पूर्णांक fei_kprobe_handler(काष्ठा kprobe *kp, काष्ठा pt_regs *regs)
अणु
	काष्ठा fei_attr *attr = container_of(kp, काष्ठा fei_attr, kp);

	अगर (should_fail(&fei_fault_attr, 1)) अणु
		regs_set_वापस_value(regs, attr->retval);
		override_function_with_वापस(regs);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(fei_kprobe_handler)

अटल व्योम *fei_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	mutex_lock(&fei_lock);
	वापस seq_list_start(&fei_attr_list, *pos);
पूर्ण

अटल व्योम fei_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	mutex_unlock(&fei_lock);
पूर्ण

अटल व्योम *fei_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &fei_attr_list, pos);
पूर्ण

अटल पूर्णांक fei_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा fei_attr *attr = list_entry(v, काष्ठा fei_attr, list);

	seq_म_लिखो(m, "%ps\n", attr->kp.addr);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations fei_seq_ops = अणु
	.start	= fei_seq_start,
	.next	= fei_seq_next,
	.stop	= fei_seq_stop,
	.show	= fei_seq_show,
पूर्ण;

अटल पूर्णांक fei_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो(file, &fei_seq_ops);
पूर्ण

अटल व्योम fei_attr_हटाओ(काष्ठा fei_attr *attr)
अणु
	fei_debugfs_हटाओ_attr(attr);
	unरेजिस्टर_kprobe(&attr->kp);
	list_del(&attr->list);
	fei_attr_मुक्त(attr);
पूर्ण

अटल व्योम fei_attr_हटाओ_all(व्योम)
अणु
	काष्ठा fei_attr *attr, *n;

	list_क्रम_each_entry_safe(attr, n, &fei_attr_list, list) अणु
		fei_attr_हटाओ(attr);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार fei_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा fei_attr *attr;
	अचिन्हित दीर्घ addr;
	अक्षर *buf, *sym;
	पूर्णांक ret;

	/* cut off अगर it is too दीर्घ */
	अगर (count > KSYM_NAME_LEN)
		count = KSYM_NAME_LEN;
	buf = kदो_स्मृति(count + 1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (copy_from_user(buf, buffer, count)) अणु
		ret = -EFAULT;
		जाओ out_मुक्त;
	पूर्ण
	buf[count] = '\0';
	sym = म_मालाip(buf);

	mutex_lock(&fei_lock);

	/* Writing just spaces will हटाओ all injection poपूर्णांकs */
	अगर (sym[0] == '\0') अणु
		fei_attr_हटाओ_all();
		ret = count;
		जाओ out;
	पूर्ण
	/* Writing !function will हटाओ one injection poपूर्णांक */
	अगर (sym[0] == '!') अणु
		attr = fei_attr_lookup(sym + 1);
		अगर (!attr) अणु
			ret = -ENOENT;
			जाओ out;
		पूर्ण
		fei_attr_हटाओ(attr);
		ret = count;
		जाओ out;
	पूर्ण

	addr = kallsyms_lookup_name(sym);
	अगर (!addr) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (!within_error_injection_list(addr)) अणु
		ret = -दुस्फल;
		जाओ out;
	पूर्ण
	अगर (fei_attr_lookup(sym)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	attr = fei_attr_new(sym, addr);
	अगर (!attr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = रेजिस्टर_kprobe(&attr->kp);
	अगर (!ret)
		fei_debugfs_add_attr(attr);
	अगर (ret < 0)
		fei_attr_हटाओ(attr);
	अन्यथा अणु
		list_add_tail(&attr->list, &fei_attr_list);
		ret = count;
	पूर्ण
out:
	mutex_unlock(&fei_lock);
out_मुक्त:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fei_ops = अणु
	.खोलो =		fei_खोलो,
	.पढ़ो =		seq_पढ़ो,
	.ग_लिखो =	fei_ग_लिखो,
	.llseek =	seq_lseek,
	.release =	seq_release,
पूर्ण;

अटल पूर्णांक __init fei_debugfs_init(व्योम)
अणु
	काष्ठा dentry *dir;

	dir = fault_create_debugfs_attr("fail_function", शून्य,
					&fei_fault_attr);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	/* injectable attribute is just a symlink of error_inject/list */
	debugfs_create_symlink("injectable", dir, "../error_injection/list");

	debugfs_create_file("inject", 0600, dir, शून्य, &fei_ops);

	fei_debugfs_dir = dir;

	वापस 0;
पूर्ण

late_initcall(fei_debugfs_init);
