<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// error-inject.c: Function-level error injection table
#समावेश <linux/error-injection.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

/* Whitelist of symbols that can be overridden क्रम error injection. */
अटल LIST_HEAD(error_injection_list);
अटल DEFINE_MUTEX(ei_mutex);
काष्ठा ei_entry अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ start_addr;
	अचिन्हित दीर्घ end_addr;
	पूर्णांक etype;
	व्योम *priv;
पूर्ण;

bool within_error_injection_list(अचिन्हित दीर्घ addr)
अणु
	काष्ठा ei_entry *ent;
	bool ret = false;

	mutex_lock(&ei_mutex);
	list_क्रम_each_entry(ent, &error_injection_list, list) अणु
		अगर (addr >= ent->start_addr && addr < ent->end_addr) अणु
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ei_mutex);
	वापस ret;
पूर्ण

पूर्णांक get_injectable_error_type(अचिन्हित दीर्घ addr)
अणु
	काष्ठा ei_entry *ent;

	list_क्रम_each_entry(ent, &error_injection_list, list) अणु
		अगर (addr >= ent->start_addr && addr < ent->end_addr)
			वापस ent->etype;
	पूर्ण
	वापस EI_ETYPE_NONE;
पूर्ण

/*
 * Lookup and populate the error_injection_list.
 *
 * For safety reasons we only allow certain functions to be overridden with
 * bpf_error_injection, so we need to populate the list of the symbols that have
 * been marked as safe क्रम overriding.
 */
अटल व्योम populate_error_injection_list(काष्ठा error_injection_entry *start,
					  काष्ठा error_injection_entry *end,
					  व्योम *priv)
अणु
	काष्ठा error_injection_entry *iter;
	काष्ठा ei_entry *ent;
	अचिन्हित दीर्घ entry, offset = 0, size = 0;

	mutex_lock(&ei_mutex);
	क्रम (iter = start; iter < end; iter++) अणु
		entry = arch_deref_entry_poपूर्णांक((व्योम *)iter->addr);

		अगर (!kernel_text_address(entry) ||
		    !kallsyms_lookup_size_offset(entry, &size, &offset)) अणु
			pr_err("Failed to find error inject entry at %p\n",
				(व्योम *)entry);
			जारी;
		पूर्ण

		ent = kदो_स्मृति(माप(*ent), GFP_KERNEL);
		अगर (!ent)
			अवरोध;
		ent->start_addr = entry;
		ent->end_addr = entry + size;
		ent->etype = iter->etype;
		ent->priv = priv;
		INIT_LIST_HEAD(&ent->list);
		list_add_tail(&ent->list, &error_injection_list);
	पूर्ण
	mutex_unlock(&ei_mutex);
पूर्ण

/* Markers of the _error_inject_whitelist section */
बाह्य काष्ठा error_injection_entry __start_error_injection_whitelist[];
बाह्य काष्ठा error_injection_entry __stop_error_injection_whitelist[];

अटल व्योम __init populate_kernel_ei_list(व्योम)
अणु
	populate_error_injection_list(__start_error_injection_whitelist,
				      __stop_error_injection_whitelist,
				      शून्य);
पूर्ण

#अगर_घोषित CONFIG_MODULES
अटल व्योम module_load_ei_list(काष्ठा module *mod)
अणु
	अगर (!mod->num_ei_funcs)
		वापस;

	populate_error_injection_list(mod->ei_funcs,
				      mod->ei_funcs + mod->num_ei_funcs, mod);
पूर्ण

अटल व्योम module_unload_ei_list(काष्ठा module *mod)
अणु
	काष्ठा ei_entry *ent, *n;

	अगर (!mod->num_ei_funcs)
		वापस;

	mutex_lock(&ei_mutex);
	list_क्रम_each_entry_safe(ent, n, &error_injection_list, list) अणु
		अगर (ent->priv == mod) अणु
			list_del_init(&ent->list);
			kमुक्त(ent);
		पूर्ण
	पूर्ण
	mutex_unlock(&ei_mutex);
पूर्ण

/* Module notअगरier call back, checking error injection table on the module */
अटल पूर्णांक ei_module_callback(काष्ठा notअगरier_block *nb,
			      अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा module *mod = data;

	अगर (val == MODULE_STATE_COMING)
		module_load_ei_list(mod);
	अन्यथा अगर (val == MODULE_STATE_GOING)
		module_unload_ei_list(mod);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ei_module_nb = अणु
	.notअगरier_call = ei_module_callback,
	.priority = 0
पूर्ण;

अटल __init पूर्णांक module_ei_init(व्योम)
अणु
	वापस रेजिस्टर_module_notअगरier(&ei_module_nb);
पूर्ण
#अन्यथा /* !CONFIG_MODULES */
#घोषणा module_ei_init()	(0)
#पूर्ण_अगर

/*
 * error_injection/whitelist -- shows which functions can be overridden क्रम
 * error injection.
 */
अटल व्योम *ei_seq_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	mutex_lock(&ei_mutex);
	वापस seq_list_start(&error_injection_list, *pos);
पूर्ण

अटल व्योम ei_seq_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	mutex_unlock(&ei_mutex);
पूर्ण

अटल व्योम *ei_seq_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	वापस seq_list_next(v, &error_injection_list, pos);
पूर्ण

अटल स्थिर अक्षर *error_type_string(पूर्णांक etype)
अणु
	चयन (etype) अणु
	हाल EI_ETYPE_शून्य:
		वापस "NULL";
	हाल EI_ETYPE_ERRNO:
		वापस "ERRNO";
	हाल EI_ETYPE_ERRNO_शून्य:
		वापस "ERRNO_NULL";
	हाल EI_ETYPE_TRUE:
		वापस "TRUE";
	शेष:
		वापस "(unknown)";
	पूर्ण
पूर्ण

अटल पूर्णांक ei_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा ei_entry *ent = list_entry(v, काष्ठा ei_entry, list);

	seq_म_लिखो(m, "%ps\t%s\n", (व्योम *)ent->start_addr,
		   error_type_string(ent->etype));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ei_seq_ops = अणु
	.start = ei_seq_start,
	.next  = ei_seq_next,
	.stop  = ei_seq_stop,
	.show  = ei_seq_show,
पूर्ण;

अटल पूर्णांक ei_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस seq_खोलो(filp, &ei_seq_ops);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_ei_ops = अणु
	.खोलो           = ei_खोलो,
	.पढ़ो           = seq_पढ़ो,
	.llseek         = seq_lseek,
	.release        = seq_release,
पूर्ण;

अटल पूर्णांक __init ei_debugfs_init(व्योम)
अणु
	काष्ठा dentry *dir, *file;

	dir = debugfs_create_dir("error_injection", शून्य);
	अगर (!dir)
		वापस -ENOMEM;

	file = debugfs_create_file("list", 0444, dir, शून्य, &debugfs_ei_ops);
	अगर (!file) अणु
		debugfs_हटाओ(dir);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init init_error_injection(व्योम)
अणु
	populate_kernel_ei_list();

	अगर (!module_ei_init())
		ei_debugfs_init();

	वापस 0;
पूर्ण
late_initcall(init_error_injection);
