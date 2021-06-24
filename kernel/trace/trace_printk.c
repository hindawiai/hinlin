<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace binary prपूर्णांकk
 *
 * Copyright (C) 2008 Lai Jiangshan <laijs@cn.fujitsu.com>
 *
 */
#समावेश <linux/seq_file.h>
#समावेश <linux/security.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश "trace.h"

#अगर_घोषित CONFIG_MODULES

/*
 * modules trace_prपूर्णांकk()'s क्रमmats are स्वतःsaved in काष्ठा trace_bprपूर्णांकk_fmt
 * which are queued on trace_bprपूर्णांकk_fmt_list.
 */
अटल LIST_HEAD(trace_bprपूर्णांकk_fmt_list);

/* serialize accesses to trace_bprपूर्णांकk_fmt_list */
अटल DEFINE_MUTEX(btrace_mutex);

काष्ठा trace_bprपूर्णांकk_fmt अणु
	काष्ठा list_head list;
	स्थिर अक्षर *fmt;
पूर्ण;

अटल अंतरभूत काष्ठा trace_bprपूर्णांकk_fmt *lookup_क्रमmat(स्थिर अक्षर *fmt)
अणु
	काष्ठा trace_bprपूर्णांकk_fmt *pos;

	अगर (!fmt)
		वापस ERR_PTR(-EINVAL);

	list_क्रम_each_entry(pos, &trace_bprपूर्णांकk_fmt_list, list) अणु
		अगर (!म_भेद(pos->fmt, fmt))
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल
व्योम hold_module_trace_bprपूर्णांकk_क्रमmat(स्थिर अक्षर **start, स्थिर अक्षर **end)
अणु
	स्थिर अक्षर **iter;
	अक्षर *fmt;

	/* allocate the trace_prपूर्णांकk per cpu buffers */
	अगर (start != end)
		trace_prपूर्णांकk_init_buffers();

	mutex_lock(&btrace_mutex);
	क्रम (iter = start; iter < end; iter++) अणु
		काष्ठा trace_bprपूर्णांकk_fmt *tb_fmt = lookup_क्रमmat(*iter);
		अगर (tb_fmt) अणु
			अगर (!IS_ERR(tb_fmt))
				*iter = tb_fmt->fmt;
			जारी;
		पूर्ण

		fmt = शून्य;
		tb_fmt = kदो_स्मृति(माप(*tb_fmt), GFP_KERNEL);
		अगर (tb_fmt) अणु
			fmt = kदो_स्मृति(म_माप(*iter) + 1, GFP_KERNEL);
			अगर (fmt) अणु
				list_add_tail(&tb_fmt->list, &trace_bprपूर्णांकk_fmt_list);
				म_नकल(fmt, *iter);
				tb_fmt->fmt = fmt;
			पूर्ण अन्यथा
				kमुक्त(tb_fmt);
		पूर्ण
		*iter = fmt;

	पूर्ण
	mutex_unlock(&btrace_mutex);
पूर्ण

अटल पूर्णांक module_trace_bprपूर्णांकk_क्रमmat_notअगरy(काष्ठा notअगरier_block *self,
		अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा module *mod = data;
	अगर (mod->num_trace_bprपूर्णांकk_fmt) अणु
		स्थिर अक्षर **start = mod->trace_bprपूर्णांकk_fmt_start;
		स्थिर अक्षर **end = start + mod->num_trace_bprपूर्णांकk_fmt;

		अगर (val == MODULE_STATE_COMING)
			hold_module_trace_bprपूर्णांकk_क्रमmat(start, end);
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

/*
 * The debugfs/tracing/prपूर्णांकk_क्रमmats file maps the addresses with
 * the ASCII क्रमmats that are used in the bprपूर्णांकk events in the
 * buffer. For userspace tools to be able to decode the events from
 * the buffer, they need to be able to map the address with the क्रमmat.
 *
 * The addresses of the bprपूर्णांकk क्रमmats are in their own section
 * __trace_prपूर्णांकk_fmt. But क्रम modules we copy them पूर्णांकo a link list.
 * The code to prपूर्णांक the क्रमmats and their addresses passes around the
 * address of the fmt string. If the fmt address passed पूर्णांकo the seq
 * functions is within the kernel core __trace_prपूर्णांकk_fmt section, then
 * it simply uses the next poपूर्णांकer in the list.
 *
 * When the fmt poपूर्णांकer is outside the kernel core __trace_prपूर्णांकk_fmt
 * section, then we need to पढ़ो the link list poपूर्णांकers. The trick is
 * we pass the address of the string to the seq function just like
 * we करो क्रम the kernel core क्रमmats. To get back the काष्ठाure that
 * holds the क्रमmat, we simply use container_of() and then go to the
 * next क्रमmat in the list.
 */
अटल स्थिर अक्षर **
find_next_mod_क्रमmat(पूर्णांक start_index, व्योम *v, स्थिर अक्षर **fmt, loff_t *pos)
अणु
	काष्ठा trace_bprपूर्णांकk_fmt *mod_fmt;

	अगर (list_empty(&trace_bprपूर्णांकk_fmt_list))
		वापस शून्य;

	/*
	 * v will poपूर्णांक to the address of the fmt record from t_next
	 * v will be शून्य from t_start.
	 * If this is the first poपूर्णांकer or called from start
	 * then we need to walk the list.
	 */
	अगर (!v || start_index == *pos) अणु
		काष्ठा trace_bprपूर्णांकk_fmt *p;

		/* search the module list */
		list_क्रम_each_entry(p, &trace_bprपूर्णांकk_fmt_list, list) अणु
			अगर (start_index == *pos)
				वापस &p->fmt;
			start_index++;
		पूर्ण
		/* pos > index */
		वापस शून्य;
	पूर्ण

	/*
	 * v poपूर्णांकs to the address of the fmt field in the mod list
	 * काष्ठाure that holds the module prपूर्णांक क्रमmat.
	 */
	mod_fmt = container_of(v, typeof(*mod_fmt), fmt);
	अगर (mod_fmt->list.next == &trace_bprपूर्णांकk_fmt_list)
		वापस शून्य;

	mod_fmt = container_of(mod_fmt->list.next, typeof(*mod_fmt), list);

	वापस &mod_fmt->fmt;
पूर्ण

अटल व्योम क्रमmat_mod_start(व्योम)
अणु
	mutex_lock(&btrace_mutex);
पूर्ण

अटल व्योम क्रमmat_mod_stop(व्योम)
अणु
	mutex_unlock(&btrace_mutex);
पूर्ण

#अन्यथा /* !CONFIG_MODULES */
__init अटल पूर्णांक
module_trace_bprपूर्णांकk_क्रमmat_notअगरy(काष्ठा notअगरier_block *self,
		अचिन्हित दीर्घ val, व्योम *data)
अणु
	वापस NOTIFY_OK;
पूर्ण
अटल अंतरभूत स्थिर अक्षर **
find_next_mod_क्रमmat(पूर्णांक start_index, व्योम *v, स्थिर अक्षर **fmt, loff_t *pos)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम क्रमmat_mod_start(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम क्रमmat_mod_stop(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_MODULES */

अटल bool __पढ़ो_mostly trace_prपूर्णांकk_enabled = true;

व्योम trace_prपूर्णांकk_control(bool enabled)
अणु
	trace_prपूर्णांकk_enabled = enabled;
पूर्ण

__initdata_or_module अटल
काष्ठा notअगरier_block module_trace_bprपूर्णांकk_क्रमmat_nb = अणु
	.notअगरier_call = module_trace_bprपूर्णांकk_क्रमmat_notअगरy,
पूर्ण;

पूर्णांक __trace_bprपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक ret;
	बहु_सूची ap;

	अगर (unlikely(!fmt))
		वापस 0;

	अगर (!trace_prपूर्णांकk_enabled)
		वापस 0;

	बहु_शुरू(ap, fmt);
	ret = trace_vbprपूर्णांकk(ip, fmt, ap);
	बहु_पूर्ण(ap);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__trace_bprपूर्णांकk);

पूर्णांक __ftrace_vbprपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	अगर (unlikely(!fmt))
		वापस 0;

	अगर (!trace_prपूर्णांकk_enabled)
		वापस 0;

	वापस trace_vbprपूर्णांकk(ip, fmt, ap);
पूर्ण
EXPORT_SYMBOL_GPL(__ftrace_vbprपूर्णांकk);

पूर्णांक __trace_prपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक ret;
	बहु_सूची ap;

	अगर (!trace_prपूर्णांकk_enabled)
		वापस 0;

	बहु_शुरू(ap, fmt);
	ret = trace_vprपूर्णांकk(ip, fmt, ap);
	बहु_पूर्ण(ap);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__trace_prपूर्णांकk);

पूर्णांक __ftrace_vprपूर्णांकk(अचिन्हित दीर्घ ip, स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	अगर (!trace_prपूर्णांकk_enabled)
		वापस 0;

	वापस trace_vprपूर्णांकk(ip, fmt, ap);
पूर्ण
EXPORT_SYMBOL_GPL(__ftrace_vprपूर्णांकk);

bool trace_is_tracepoपूर्णांक_string(स्थिर अक्षर *str)
अणु
	स्थिर अक्षर **ptr = __start___tracepoपूर्णांक_str;

	क्रम (ptr = __start___tracepoपूर्णांक_str; ptr < __stop___tracepoपूर्णांक_str; ptr++) अणु
		अगर (str == *ptr)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर अक्षर **find_next(व्योम *v, loff_t *pos)
अणु
	स्थिर अक्षर **fmt = v;
	पूर्णांक start_index;
	पूर्णांक last_index;

	start_index = __stop___trace_bprपूर्णांकk_fmt - __start___trace_bprपूर्णांकk_fmt;

	अगर (*pos < start_index)
		वापस __start___trace_bprपूर्णांकk_fmt + *pos;

	/*
	 * The __tracepoपूर्णांक_str section is treated the same as the
	 * __trace_prपूर्णांकk_fmt section. The dअगरference is that the
	 * __trace_prपूर्णांकk_fmt section should only be used by trace_prपूर्णांकk()
	 * in a debugging environment, as अगर anything exists in that section
	 * the trace_prink() helper buffers are allocated, which would just
	 * waste space in a production environment.
	 *
	 * The __tracepoपूर्णांक_str sections on the other hand are used by
	 * tracepoपूर्णांकs which need to map poपूर्णांकers to their strings to
	 * the ASCII text क्रम userspace.
	 */
	last_index = start_index;
	start_index = __stop___tracepoपूर्णांक_str - __start___tracepoपूर्णांक_str;

	अगर (*pos < last_index + start_index)
		वापस __start___tracepoपूर्णांक_str + (*pos - last_index);

	start_index += last_index;
	वापस find_next_mod_क्रमmat(start_index, v, fmt, pos);
पूर्ण

अटल व्योम *
t_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	क्रमmat_mod_start();
	वापस find_next(शून्य, pos);
पूर्ण

अटल व्योम *t_next(काष्ठा seq_file *m, व्योम * v, loff_t *pos)
अणु
	(*pos)++;
	वापस find_next(v, pos);
पूर्ण

अटल पूर्णांक t_show(काष्ठा seq_file *m, व्योम *v)
अणु
	स्थिर अक्षर **fmt = v;
	स्थिर अक्षर *str = *fmt;
	पूर्णांक i;

	अगर (!*fmt)
		वापस 0;

	seq_म_लिखो(m, "0x%lx : \"", *(अचिन्हित दीर्घ *)fmt);

	/*
	 * Tअसल and new lines need to be converted.
	 */
	क्रम (i = 0; str[i]; i++) अणु
		चयन (str[i]) अणु
		हाल '\n':
			seq_माला_दो(m, "\\n");
			अवरोध;
		हाल '\t':
			seq_माला_दो(m, "\\t");
			अवरोध;
		हाल '\\':
			seq_अ_दो(m, '\\');
			अवरोध;
		हाल '"':
			seq_माला_दो(m, "\\\"");
			अवरोध;
		शेष:
			seq_अ_दो(m, str[i]);
		पूर्ण
	पूर्ण
	seq_माला_दो(m, "\"\n");

	वापस 0;
पूर्ण

अटल व्योम t_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	क्रमmat_mod_stop();
पूर्ण

अटल स्थिर काष्ठा seq_operations show_क्रमmat_seq_ops = अणु
	.start = t_start,
	.next = t_next,
	.show = t_show,
	.stop = t_stop,
पूर्ण;

अटल पूर्णांक
ftrace_क्रमmats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	वापस seq_खोलो(file, &show_क्रमmat_seq_ops);
पूर्ण

अटल स्थिर काष्ठा file_operations ftrace_क्रमmats_fops = अणु
	.खोलो = ftrace_क्रमmats_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release,
पूर्ण;

अटल __init पूर्णांक init_trace_prपूर्णांकk_function_export(व्योम)
अणु
	पूर्णांक ret;

	ret = tracing_init_dentry();
	अगर (ret)
		वापस 0;

	trace_create_file("printk_formats", 0444, शून्य,
				    शून्य, &ftrace_क्रमmats_fops);

	वापस 0;
पूर्ण

fs_initcall(init_trace_prपूर्णांकk_function_export);

अटल __init पूर्णांक init_trace_prपूर्णांकk(व्योम)
अणु
	वापस रेजिस्टर_module_notअगरier(&module_trace_bprपूर्णांकk_क्रमmat_nb);
पूर्ण

early_initcall(init_trace_prपूर्णांकk);
