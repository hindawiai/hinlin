<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * uprobes-based tracing events
 *
 * Copyright (C) IBM Corporation, 2010-2012
 * Author:	Srikar Dronamraju <srikar@linux.vnet.ibm.com>
 */
#घोषणा pr_fmt(fmt)	"trace_uprobe: " fmt

#समावेश <linux/security.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/uprobes.h>
#समावेश <linux/namei.h>
#समावेश <linux/माला.स>
#समावेश <linux/rculist.h>

#समावेश "trace_dynevent.h"
#समावेश "trace_probe.h"
#समावेश "trace_probe_tmpl.h"

#घोषणा UPROBE_EVENT_SYSTEM	"uprobes"

काष्ठा uprobe_trace_entry_head अणु
	काष्ठा trace_entry	ent;
	अचिन्हित दीर्घ		vaddr[];
पूर्ण;

#घोषणा SIZखातापूर्ण_TRACE_ENTRY(is_वापस)			\
	(माप(काष्ठा uprobe_trace_entry_head) +	\
	 माप(अचिन्हित दीर्घ) * (is_वापस ? 2 : 1))

#घोषणा DATAOF_TRACE_ENTRY(entry, is_वापस)		\
	((व्योम*)(entry) + SIZखातापूर्ण_TRACE_ENTRY(is_वापस))

अटल पूर्णांक trace_uprobe_create(स्थिर अक्षर *raw_command);
अटल पूर्णांक trace_uprobe_show(काष्ठा seq_file *m, काष्ठा dyn_event *ev);
अटल पूर्णांक trace_uprobe_release(काष्ठा dyn_event *ev);
अटल bool trace_uprobe_is_busy(काष्ठा dyn_event *ev);
अटल bool trace_uprobe_match(स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event,
			पूर्णांक argc, स्थिर अक्षर **argv, काष्ठा dyn_event *ev);

अटल काष्ठा dyn_event_operations trace_uprobe_ops = अणु
	.create = trace_uprobe_create,
	.show = trace_uprobe_show,
	.is_busy = trace_uprobe_is_busy,
	.मुक्त = trace_uprobe_release,
	.match = trace_uprobe_match,
पूर्ण;

/*
 * uprobe event core functions
 */
काष्ठा trace_uprobe अणु
	काष्ठा dyn_event		devent;
	काष्ठा uprobe_consumer		consumer;
	काष्ठा path			path;
	काष्ठा inode			*inode;
	अक्षर				*filename;
	अचिन्हित दीर्घ			offset;
	अचिन्हित दीर्घ			ref_ctr_offset;
	अचिन्हित दीर्घ			nhit;
	काष्ठा trace_probe		tp;
पूर्ण;

अटल bool is_trace_uprobe(काष्ठा dyn_event *ev)
अणु
	वापस ev->ops == &trace_uprobe_ops;
पूर्ण

अटल काष्ठा trace_uprobe *to_trace_uprobe(काष्ठा dyn_event *ev)
अणु
	वापस container_of(ev, काष्ठा trace_uprobe, devent);
पूर्ण

/**
 * क्रम_each_trace_uprobe - iterate over the trace_uprobe list
 * @pos:	the काष्ठा trace_uprobe * क्रम each entry
 * @dpos:	the काष्ठा dyn_event * to use as a loop cursor
 */
#घोषणा क्रम_each_trace_uprobe(pos, dpos)	\
	क्रम_each_dyn_event(dpos)		\
		अगर (is_trace_uprobe(dpos) && (pos = to_trace_uprobe(dpos)))

#घोषणा SIZखातापूर्ण_TRACE_UPROBE(n)				\
	(दुरत्व(काष्ठा trace_uprobe, tp.args) +	\
	(माप(काष्ठा probe_arg) * (n)))

अटल पूर्णांक रेजिस्टर_uprobe_event(काष्ठा trace_uprobe *tu);
अटल पूर्णांक unरेजिस्टर_uprobe_event(काष्ठा trace_uprobe *tu);

काष्ठा uprobe_dispatch_data अणु
	काष्ठा trace_uprobe	*tu;
	अचिन्हित दीर्घ		bp_addr;
पूर्ण;

अटल पूर्णांक uprobe_dispatcher(काष्ठा uprobe_consumer *con, काष्ठा pt_regs *regs);
अटल पूर्णांक uretprobe_dispatcher(काष्ठा uprobe_consumer *con,
				अचिन्हित दीर्घ func, काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_STACK_GROWSUP
अटल अचिन्हित दीर्घ adjust_stack_addr(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक n)
अणु
	वापस addr - (n * माप(दीर्घ));
पूर्ण
#अन्यथा
अटल अचिन्हित दीर्घ adjust_stack_addr(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक n)
अणु
	वापस addr + (n * माप(दीर्घ));
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित दीर्घ get_user_stack_nth(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ ret;
	अचिन्हित दीर्घ addr = user_stack_poपूर्णांकer(regs);

	addr = adjust_stack_addr(addr, n);

	अगर (copy_from_user(&ret, (व्योम __क्रमce __user *) addr, माप(ret)))
		वापस 0;

	वापस ret;
पूर्ण

/*
 * Uprobes-specअगरic fetch functions
 */
अटल nokprobe_अंतरभूत पूर्णांक
probe_mem_पढ़ो(व्योम *dest, व्योम *src, माप_प्रकार size)
अणु
	व्योम __user *vaddr = (व्योम __क्रमce __user *)src;

	वापस copy_from_user(dest, vaddr, size) ? -EFAULT : 0;
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक
probe_mem_पढ़ो_user(व्योम *dest, व्योम *src, माप_प्रकार size)
अणु
	वापस probe_mem_पढ़ो(dest, src, size);
पूर्ण

/*
 * Fetch a null-terminated string. Caller MUST set *(u32 *)dest with max
 * length and relative data location.
 */
अटल nokprobe_अंतरभूत पूर्णांक
fetch_store_string(अचिन्हित दीर्घ addr, व्योम *dest, व्योम *base)
अणु
	दीर्घ ret;
	u32 loc = *(u32 *)dest;
	पूर्णांक maxlen  = get_loc_len(loc);
	u8 *dst = get_loc_data(dest, base);
	व्योम __user *src = (व्योम __क्रमce __user *) addr;

	अगर (unlikely(!maxlen))
		वापस -ENOMEM;

	अगर (addr == FETCH_TOKEN_COMM)
		ret = strlcpy(dst, current->comm, maxlen);
	अन्यथा
		ret = म_नकलन_from_user(dst, src, maxlen);
	अगर (ret >= 0) अणु
		अगर (ret == maxlen)
			dst[ret - 1] = '\0';
		अन्यथा
			/*
			 * Include the terminating null byte. In this हाल it
			 * was copied by म_नकलन_from_user but not accounted
			 * क्रम in ret.
			 */
			ret++;
		*(u32 *)dest = make_data_loc(ret, (व्योम *)dst - base);
	पूर्ण

	वापस ret;
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक
fetch_store_string_user(अचिन्हित दीर्घ addr, व्योम *dest, व्योम *base)
अणु
	वापस fetch_store_string(addr, dest, base);
पूर्ण

/* Return the length of string -- including null terminal byte */
अटल nokprobe_अंतरभूत पूर्णांक
fetch_store_म_माप(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक len;
	व्योम __user *vaddr = (व्योम __क्रमce __user *) addr;

	अगर (addr == FETCH_TOKEN_COMM)
		len = म_माप(current->comm) + 1;
	अन्यथा
		len = strnlen_user(vaddr, MAX_STRING_SIZE);

	वापस (len > MAX_STRING_SIZE) ? 0 : len;
पूर्ण

अटल nokprobe_अंतरभूत पूर्णांक
fetch_store_म_माप_user(अचिन्हित दीर्घ addr)
अणु
	वापस fetch_store_म_माप(addr);
पूर्ण

अटल अचिन्हित दीर्घ translate_user_vaddr(अचिन्हित दीर्घ file_offset)
अणु
	अचिन्हित दीर्घ base_addr;
	काष्ठा uprobe_dispatch_data *udd;

	udd = (व्योम *) current->utask->vaddr;

	base_addr = udd->bp_addr - udd->tu->offset;
	वापस base_addr + file_offset;
पूर्ण

/* Note that we करोn't verअगरy it, since the code करोes not come from user space */
अटल पूर्णांक
process_fetch_insn(काष्ठा fetch_insn *code, काष्ठा pt_regs *regs, व्योम *dest,
		   व्योम *base)
अणु
	अचिन्हित दीर्घ val;

	/* 1st stage: get value from context */
	चयन (code->op) अणु
	हाल FETCH_OP_REG:
		val = regs_get_रेजिस्टर(regs, code->param);
		अवरोध;
	हाल FETCH_OP_STACK:
		val = get_user_stack_nth(regs, code->param);
		अवरोध;
	हाल FETCH_OP_STACKP:
		val = user_stack_poपूर्णांकer(regs);
		अवरोध;
	हाल FETCH_OP_RETVAL:
		val = regs_वापस_value(regs);
		अवरोध;
	हाल FETCH_OP_IMM:
		val = code->immediate;
		अवरोध;
	हाल FETCH_OP_COMM:
		val = FETCH_TOKEN_COMM;
		अवरोध;
	हाल FETCH_OP_DATA:
		val = (अचिन्हित दीर्घ)code->data;
		अवरोध;
	हाल FETCH_OP_FOFFS:
		val = translate_user_vaddr(code->immediate);
		अवरोध;
	शेष:
		वापस -EILSEQ;
	पूर्ण
	code++;

	वापस process_fetch_insn_bottom(code, val, dest, base);
पूर्ण
NOKPROBE_SYMBOL(process_fetch_insn)

अटल अंतरभूत व्योम init_trace_uprobe_filter(काष्ठा trace_uprobe_filter *filter)
अणु
	rwlock_init(&filter->rwlock);
	filter->nr_प्रणालीwide = 0;
	INIT_LIST_HEAD(&filter->perf_events);
पूर्ण

अटल अंतरभूत bool uprobe_filter_is_empty(काष्ठा trace_uprobe_filter *filter)
अणु
	वापस !filter->nr_प्रणालीwide && list_empty(&filter->perf_events);
पूर्ण

अटल अंतरभूत bool is_ret_probe(काष्ठा trace_uprobe *tu)
अणु
	वापस tu->consumer.ret_handler != शून्य;
पूर्ण

अटल bool trace_uprobe_is_busy(काष्ठा dyn_event *ev)
अणु
	काष्ठा trace_uprobe *tu = to_trace_uprobe(ev);

	वापस trace_probe_is_enabled(&tu->tp);
पूर्ण

अटल bool trace_uprobe_match_command_head(काष्ठा trace_uprobe *tu,
					    पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अक्षर buf[MAX_ARGSTR_LEN + 1];
	पूर्णांक len;

	अगर (!argc)
		वापस true;

	len = म_माप(tu->filename);
	अगर (म_भेदन(tu->filename, argv[0], len) || argv[0][len] != ':')
		वापस false;

	अगर (tu->ref_ctr_offset == 0)
		snम_लिखो(buf, माप(buf), "0x%0*lx",
				(पूर्णांक)(माप(व्योम *) * 2), tu->offset);
	अन्यथा
		snम_लिखो(buf, माप(buf), "0x%0*lx(0x%lx)",
				(पूर्णांक)(माप(व्योम *) * 2), tu->offset,
				tu->ref_ctr_offset);
	अगर (म_भेद(buf, &argv[0][len + 1]))
		वापस false;

	argc--; argv++;

	वापस trace_probe_match_command_args(&tu->tp, argc, argv);
पूर्ण

अटल bool trace_uprobe_match(स्थिर अक्षर *प्रणाली, स्थिर अक्षर *event,
			पूर्णांक argc, स्थिर अक्षर **argv, काष्ठा dyn_event *ev)
अणु
	काष्ठा trace_uprobe *tu = to_trace_uprobe(ev);

	वापस म_भेद(trace_probe_name(&tu->tp), event) == 0 &&
	   (!प्रणाली || म_भेद(trace_probe_group_name(&tu->tp), प्रणाली) == 0) &&
	   trace_uprobe_match_command_head(tu, argc, argv);
पूर्ण

अटल nokprobe_अंतरभूत काष्ठा trace_uprobe *
trace_uprobe_primary_from_call(काष्ठा trace_event_call *call)
अणु
	काष्ठा trace_probe *tp;

	tp = trace_probe_primary_from_call(call);
	अगर (WARN_ON_ONCE(!tp))
		वापस शून्य;

	वापस container_of(tp, काष्ठा trace_uprobe, tp);
पूर्ण

/*
 * Allocate new trace_uprobe and initialize it (including uprobes).
 */
अटल काष्ठा trace_uprobe *
alloc_trace_uprobe(स्थिर अक्षर *group, स्थिर अक्षर *event, पूर्णांक nargs, bool is_ret)
अणु
	काष्ठा trace_uprobe *tu;
	पूर्णांक ret;

	tu = kzalloc(SIZखातापूर्ण_TRACE_UPROBE(nargs), GFP_KERNEL);
	अगर (!tu)
		वापस ERR_PTR(-ENOMEM);

	ret = trace_probe_init(&tu->tp, event, group, true);
	अगर (ret < 0)
		जाओ error;

	dyn_event_init(&tu->devent, &trace_uprobe_ops);
	tu->consumer.handler = uprobe_dispatcher;
	अगर (is_ret)
		tu->consumer.ret_handler = uretprobe_dispatcher;
	init_trace_uprobe_filter(tu->tp.event->filter);
	वापस tu;

error:
	kमुक्त(tu);

	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम मुक्त_trace_uprobe(काष्ठा trace_uprobe *tu)
अणु
	अगर (!tu)
		वापस;

	path_put(&tu->path);
	trace_probe_cleanup(&tu->tp);
	kमुक्त(tu->filename);
	kमुक्त(tu);
पूर्ण

अटल काष्ठा trace_uprobe *find_probe_event(स्थिर अक्षर *event, स्थिर अक्षर *group)
अणु
	काष्ठा dyn_event *pos;
	काष्ठा trace_uprobe *tu;

	क्रम_each_trace_uprobe(tu, pos)
		अगर (म_भेद(trace_probe_name(&tu->tp), event) == 0 &&
		    म_भेद(trace_probe_group_name(&tu->tp), group) == 0)
			वापस tu;

	वापस शून्य;
पूर्ण

/* Unरेजिस्टर a trace_uprobe and probe_event */
अटल पूर्णांक unरेजिस्टर_trace_uprobe(काष्ठा trace_uprobe *tu)
अणु
	पूर्णांक ret;

	अगर (trace_probe_has_sibling(&tu->tp))
		जाओ unreg;

	ret = unरेजिस्टर_uprobe_event(tu);
	अगर (ret)
		वापस ret;

unreg:
	dyn_event_हटाओ(&tu->devent);
	trace_probe_unlink(&tu->tp);
	मुक्त_trace_uprobe(tu);
	वापस 0;
पूर्ण

अटल bool trace_uprobe_has_same_uprobe(काष्ठा trace_uprobe *orig,
					 काष्ठा trace_uprobe *comp)
अणु
	काष्ठा trace_probe_event *tpe = orig->tp.event;
	काष्ठा trace_probe *pos;
	काष्ठा inode *comp_inode = d_real_inode(comp->path.dentry);
	पूर्णांक i;

	list_क्रम_each_entry(pos, &tpe->probes, list) अणु
		orig = container_of(pos, काष्ठा trace_uprobe, tp);
		अगर (comp_inode != d_real_inode(orig->path.dentry) ||
		    comp->offset != orig->offset)
			जारी;

		/*
		 * trace_probe_compare_arg_type() ensured that nr_args and
		 * each argument name and type are same. Let's compare comm.
		 */
		क्रम (i = 0; i < orig->tp.nr_args; i++) अणु
			अगर (म_भेद(orig->tp.args[i].comm,
				   comp->tp.args[i].comm))
				अवरोध;
		पूर्ण

		अगर (i == orig->tp.nr_args)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक append_trace_uprobe(काष्ठा trace_uprobe *tu, काष्ठा trace_uprobe *to)
अणु
	पूर्णांक ret;

	ret = trace_probe_compare_arg_type(&tu->tp, &to->tp);
	अगर (ret) अणु
		/* Note that argument starts index = 2 */
		trace_probe_log_set_index(ret + 1);
		trace_probe_log_err(0, DIFF_ARG_TYPE);
		वापस -EEXIST;
	पूर्ण
	अगर (trace_uprobe_has_same_uprobe(to, tu)) अणु
		trace_probe_log_set_index(0);
		trace_probe_log_err(0, SAME_PROBE);
		वापस -EEXIST;
	पूर्ण

	/* Append to existing event */
	ret = trace_probe_append(&tu->tp, &to->tp);
	अगर (!ret)
		dyn_event_add(&tu->devent);

	वापस ret;
पूर्ण

/*
 * Uprobe with multiple reference counter is not allowed. i.e.
 * If inode and offset matches, reference counter offset *must*
 * match as well. Though, there is one exception: If user is
 * replacing old trace_uprobe with new one(same group/event),
 * then we allow same uprobe with new reference counter as far
 * as the new one करोes not conflict with any other existing
 * ones.
 */
अटल पूर्णांक validate_ref_ctr_offset(काष्ठा trace_uprobe *new)
अणु
	काष्ठा dyn_event *pos;
	काष्ठा trace_uprobe *पंचांगp;
	काष्ठा inode *new_inode = d_real_inode(new->path.dentry);

	क्रम_each_trace_uprobe(पंचांगp, pos) अणु
		अगर (new_inode == d_real_inode(पंचांगp->path.dentry) &&
		    new->offset == पंचांगp->offset &&
		    new->ref_ctr_offset != पंचांगp->ref_ctr_offset) अणु
			pr_warn("Reference counter offset mismatch.");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Register a trace_uprobe and probe_event */
अटल पूर्णांक रेजिस्टर_trace_uprobe(काष्ठा trace_uprobe *tu)
अणु
	काष्ठा trace_uprobe *old_tu;
	पूर्णांक ret;

	mutex_lock(&event_mutex);

	ret = validate_ref_ctr_offset(tu);
	अगर (ret)
		जाओ end;

	/* रेजिस्टर as an event */
	old_tu = find_probe_event(trace_probe_name(&tu->tp),
				  trace_probe_group_name(&tu->tp));
	अगर (old_tu) अणु
		अगर (is_ret_probe(tu) != is_ret_probe(old_tu)) अणु
			trace_probe_log_set_index(0);
			trace_probe_log_err(0, DIFF_PROBE_TYPE);
			ret = -EEXIST;
		पूर्ण अन्यथा अणु
			ret = append_trace_uprobe(tu, old_tu);
		पूर्ण
		जाओ end;
	पूर्ण

	ret = रेजिस्टर_uprobe_event(tu);
	अगर (ret) अणु
		pr_warn("Failed to register probe event(%d)\n", ret);
		जाओ end;
	पूर्ण

	dyn_event_add(&tu->devent);

end:
	mutex_unlock(&event_mutex);

	वापस ret;
पूर्ण

/*
 * Argument syntax:
 *  - Add uprobe: p|r[:[GRP/]EVENT] PATH:OFFSET[%वापस][(REF)] [FETCHARGS]
 */
अटल पूर्णांक __trace_uprobe_create(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा trace_uprobe *tu;
	स्थिर अक्षर *event = शून्य, *group = UPROBE_EVENT_SYSTEM;
	अक्षर *arg, *filename, *rctr, *rctr_end, *पंचांगp;
	अक्षर buf[MAX_EVENT_NAME_LEN];
	काष्ठा path path;
	अचिन्हित दीर्घ offset, ref_ctr_offset;
	bool is_वापस = false;
	पूर्णांक i, ret;

	ret = 0;
	ref_ctr_offset = 0;

	चयन (argv[0][0]) अणु
	हाल 'r':
		is_वापस = true;
		अवरोध;
	हाल 'p':
		अवरोध;
	शेष:
		वापस -ECANCELED;
	पूर्ण

	अगर (argc < 2)
		वापस -ECANCELED;

	अगर (argv[0][1] == ':')
		event = &argv[0][2];

	अगर (!म_अक्षर(argv[1], '/'))
		वापस -ECANCELED;

	filename = kstrdup(argv[1], GFP_KERNEL);
	अगर (!filename)
		वापस -ENOMEM;

	/* Find the last occurrence, in हाल the path contains ':' too. */
	arg = म_खोजप(filename, ':');
	अगर (!arg || !है_अंक(arg[1])) अणु
		kमुक्त(filename);
		वापस -ECANCELED;
	पूर्ण

	trace_probe_log_init("trace_uprobe", argc, argv);
	trace_probe_log_set_index(1);	/* filename is the 2nd argument */

	*arg++ = '\0';
	ret = kern_path(filename, LOOKUP_FOLLOW, &path);
	अगर (ret) अणु
		trace_probe_log_err(0, खाता_NOT_FOUND);
		kमुक्त(filename);
		trace_probe_log_clear();
		वापस ret;
	पूर्ण
	अगर (!d_is_reg(path.dentry)) अणु
		trace_probe_log_err(0, NO_REGULAR_खाता);
		ret = -EINVAL;
		जाओ fail_address_parse;
	पूर्ण

	/* Parse reference counter offset अगर specअगरied. */
	rctr = म_अक्षर(arg, '(');
	अगर (rctr) अणु
		rctr_end = म_अक्षर(rctr, ')');
		अगर (!rctr_end) अणु
			ret = -EINVAL;
			rctr_end = rctr + म_माप(rctr);
			trace_probe_log_err(rctr_end - filename,
					    REFCNT_OPEN_BRACE);
			जाओ fail_address_parse;
		पूर्ण अन्यथा अगर (rctr_end[1] != '\0') अणु
			ret = -EINVAL;
			trace_probe_log_err(rctr_end + 1 - filename,
					    BAD_REFCNT_SUFFIX);
			जाओ fail_address_parse;
		पूर्ण

		*rctr++ = '\0';
		*rctr_end = '\0';
		ret = kम_से_अदीर्घ(rctr, 0, &ref_ctr_offset);
		अगर (ret) अणु
			trace_probe_log_err(rctr - filename, BAD_REFCNT);
			जाओ fail_address_parse;
		पूर्ण
	पूर्ण

	/* Check अगर there is %वापस suffix */
	पंचांगp = म_अक्षर(arg, '%');
	अगर (पंचांगp) अणु
		अगर (!म_भेद(पंचांगp, "%return")) अणु
			*पंचांगp = '\0';
			is_वापस = true;
		पूर्ण अन्यथा अणु
			trace_probe_log_err(पंचांगp - filename, BAD_ADDR_SUFFIX);
			ret = -EINVAL;
			जाओ fail_address_parse;
		पूर्ण
	पूर्ण

	/* Parse uprobe offset. */
	ret = kम_से_अदीर्घ(arg, 0, &offset);
	अगर (ret) अणु
		trace_probe_log_err(arg - filename, BAD_UPROBE_OFFS);
		जाओ fail_address_parse;
	पूर्ण

	/* setup a probe */
	trace_probe_log_set_index(0);
	अगर (event) अणु
		ret = traceprobe_parse_event_name(&event, &group, buf,
						  event - argv[0]);
		अगर (ret)
			जाओ fail_address_parse;
	पूर्ण अन्यथा अणु
		अक्षर *tail;
		अक्षर *ptr;

		tail = kstrdup(kbasename(filename), GFP_KERNEL);
		अगर (!tail) अणु
			ret = -ENOMEM;
			जाओ fail_address_parse;
		पूर्ण

		ptr = strpbrk(tail, ".-_");
		अगर (ptr)
			*ptr = '\0';

		snम_लिखो(buf, MAX_EVENT_NAME_LEN, "%c_%s_0x%lx", 'p', tail, offset);
		event = buf;
		kमुक्त(tail);
	पूर्ण

	argc -= 2;
	argv += 2;

	tu = alloc_trace_uprobe(group, event, argc, is_वापस);
	अगर (IS_ERR(tu)) अणु
		ret = PTR_ERR(tu);
		/* This must वापस -ENOMEM otherwise there is a bug */
		WARN_ON_ONCE(ret != -ENOMEM);
		जाओ fail_address_parse;
	पूर्ण
	tu->offset = offset;
	tu->ref_ctr_offset = ref_ctr_offset;
	tu->path = path;
	tu->filename = filename;

	/* parse arguments */
	क्रम (i = 0; i < argc && i < MAX_TRACE_ARGS; i++) अणु
		पंचांगp = kstrdup(argv[i], GFP_KERNEL);
		अगर (!पंचांगp) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण

		trace_probe_log_set_index(i + 2);
		ret = traceprobe_parse_probe_arg(&tu->tp, i, पंचांगp,
					is_वापस ? TPARG_FL_RETURN : 0);
		kमुक्त(पंचांगp);
		अगर (ret)
			जाओ error;
	पूर्ण

	ret = traceprobe_set_prपूर्णांक_fmt(&tu->tp, is_ret_probe(tu));
	अगर (ret < 0)
		जाओ error;

	ret = रेजिस्टर_trace_uprobe(tu);
	अगर (!ret)
		जाओ out;

error:
	मुक्त_trace_uprobe(tu);
out:
	trace_probe_log_clear();
	वापस ret;

fail_address_parse:
	trace_probe_log_clear();
	path_put(&path);
	kमुक्त(filename);

	वापस ret;
पूर्ण

पूर्णांक trace_uprobe_create(स्थिर अक्षर *raw_command)
अणु
	वापस trace_probe_create(raw_command, __trace_uprobe_create);
पूर्ण

अटल पूर्णांक create_or_delete_trace_uprobe(स्थिर अक्षर *raw_command)
अणु
	पूर्णांक ret;

	अगर (raw_command[0] == '-')
		वापस dyn_event_release(raw_command, &trace_uprobe_ops);

	ret = trace_uprobe_create(raw_command);
	वापस ret == -ECANCELED ? -EINVAL : ret;
पूर्ण

अटल पूर्णांक trace_uprobe_release(काष्ठा dyn_event *ev)
अणु
	काष्ठा trace_uprobe *tu = to_trace_uprobe(ev);

	वापस unरेजिस्टर_trace_uprobe(tu);
पूर्ण

/* Probes listing पूर्णांकerfaces */
अटल पूर्णांक trace_uprobe_show(काष्ठा seq_file *m, काष्ठा dyn_event *ev)
अणु
	काष्ठा trace_uprobe *tu = to_trace_uprobe(ev);
	अक्षर c = is_ret_probe(tu) ? 'r' : 'p';
	पूर्णांक i;

	seq_म_लिखो(m, "%c:%s/%s %s:0x%0*lx", c, trace_probe_group_name(&tu->tp),
			trace_probe_name(&tu->tp), tu->filename,
			(पूर्णांक)(माप(व्योम *) * 2), tu->offset);

	अगर (tu->ref_ctr_offset)
		seq_म_लिखो(m, "(0x%lx)", tu->ref_ctr_offset);

	क्रम (i = 0; i < tu->tp.nr_args; i++)
		seq_म_लिखो(m, " %s=%s", tu->tp.args[i].name, tu->tp.args[i].comm);

	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक probes_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dyn_event *ev = v;

	अगर (!is_trace_uprobe(ev))
		वापस 0;

	वापस trace_uprobe_show(m, ev);
पूर्ण

अटल स्थिर काष्ठा seq_operations probes_seq_op = अणु
	.start  = dyn_event_seq_start,
	.next   = dyn_event_seq_next,
	.stop   = dyn_event_seq_stop,
	.show   = probes_seq_show
पूर्ण;

अटल पूर्णांक probes_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	अगर ((file->f_mode & FMODE_WRITE) && (file->f_flags & O_TRUNC)) अणु
		ret = dyn_events_release_all(&trace_uprobe_ops);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस seq_खोलो(file, &probes_seq_op);
पूर्ण

अटल sमाप_प्रकार probes_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buffer,
			    माप_प्रकार count, loff_t *ppos)
अणु
	वापस trace_parse_run_command(file, buffer, count, ppos,
					create_or_delete_trace_uprobe);
पूर्ण

अटल स्थिर काष्ठा file_operations uprobe_events_ops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= probes_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release,
	.ग_लिखो		= probes_ग_लिखो,
पूर्ण;

/* Probes profiling पूर्णांकerfaces */
अटल पूर्णांक probes_profile_seq_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा dyn_event *ev = v;
	काष्ठा trace_uprobe *tu;

	अगर (!is_trace_uprobe(ev))
		वापस 0;

	tu = to_trace_uprobe(ev);
	seq_म_लिखो(m, "  %s %-44s %15lu\n", tu->filename,
			trace_probe_name(&tu->tp), tu->nhit);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations profile_seq_op = अणु
	.start  = dyn_event_seq_start,
	.next   = dyn_event_seq_next,
	.stop   = dyn_event_seq_stop,
	.show	= probes_profile_seq_show
पूर्ण;

अटल पूर्णांक profile_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	वापस seq_खोलो(file, &profile_seq_op);
पूर्ण

अटल स्थिर काष्ठा file_operations uprobe_profile_ops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= profile_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= seq_release,
पूर्ण;

काष्ठा uprobe_cpu_buffer अणु
	काष्ठा mutex mutex;
	व्योम *buf;
पूर्ण;
अटल काष्ठा uprobe_cpu_buffer __percpu *uprobe_cpu_buffer;
अटल पूर्णांक uprobe_buffer_refcnt;

अटल पूर्णांक uprobe_buffer_init(व्योम)
अणु
	पूर्णांक cpu, err_cpu;

	uprobe_cpu_buffer = alloc_percpu(काष्ठा uprobe_cpu_buffer);
	अगर (uprobe_cpu_buffer == शून्य)
		वापस -ENOMEM;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा page *p = alloc_pages_node(cpu_to_node(cpu),
						  GFP_KERNEL, 0);
		अगर (p == शून्य) अणु
			err_cpu = cpu;
			जाओ err;
		पूर्ण
		per_cpu_ptr(uprobe_cpu_buffer, cpu)->buf = page_address(p);
		mutex_init(&per_cpu_ptr(uprobe_cpu_buffer, cpu)->mutex);
	पूर्ण

	वापस 0;

err:
	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu == err_cpu)
			अवरोध;
		मुक्त_page((अचिन्हित दीर्घ)per_cpu_ptr(uprobe_cpu_buffer, cpu)->buf);
	पूर्ण

	मुक्त_percpu(uprobe_cpu_buffer);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक uprobe_buffer_enable(व्योम)
अणु
	पूर्णांक ret = 0;

	BUG_ON(!mutex_is_locked(&event_mutex));

	अगर (uprobe_buffer_refcnt++ == 0) अणु
		ret = uprobe_buffer_init();
		अगर (ret < 0)
			uprobe_buffer_refcnt--;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम uprobe_buffer_disable(व्योम)
अणु
	पूर्णांक cpu;

	BUG_ON(!mutex_is_locked(&event_mutex));

	अगर (--uprobe_buffer_refcnt == 0) अणु
		क्रम_each_possible_cpu(cpu)
			मुक्त_page((अचिन्हित दीर्घ)per_cpu_ptr(uprobe_cpu_buffer,
							     cpu)->buf);

		मुक्त_percpu(uprobe_cpu_buffer);
		uprobe_cpu_buffer = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा uprobe_cpu_buffer *uprobe_buffer_get(व्योम)
अणु
	काष्ठा uprobe_cpu_buffer *ucb;
	पूर्णांक cpu;

	cpu = raw_smp_processor_id();
	ucb = per_cpu_ptr(uprobe_cpu_buffer, cpu);

	/*
	 * Use per-cpu buffers क्रम fastest access, but we might migrate
	 * so the mutex makes sure we have sole access to it.
	 */
	mutex_lock(&ucb->mutex);

	वापस ucb;
पूर्ण

अटल व्योम uprobe_buffer_put(काष्ठा uprobe_cpu_buffer *ucb)
अणु
	mutex_unlock(&ucb->mutex);
पूर्ण

अटल व्योम __uprobe_trace_func(काष्ठा trace_uprobe *tu,
				अचिन्हित दीर्घ func, काष्ठा pt_regs *regs,
				काष्ठा uprobe_cpu_buffer *ucb, पूर्णांक dsize,
				काष्ठा trace_event_file *trace_file)
अणु
	काष्ठा uprobe_trace_entry_head *entry;
	काष्ठा trace_buffer *buffer;
	काष्ठा ring_buffer_event *event;
	व्योम *data;
	पूर्णांक size, esize;
	काष्ठा trace_event_call *call = trace_probe_event_call(&tu->tp);

	WARN_ON(call != trace_file->event_call);

	अगर (WARN_ON_ONCE(tu->tp.size + dsize > PAGE_SIZE))
		वापस;

	अगर (trace_trigger_soft_disabled(trace_file))
		वापस;

	esize = SIZखातापूर्ण_TRACE_ENTRY(is_ret_probe(tu));
	size = esize + tu->tp.size + dsize;
	event = trace_event_buffer_lock_reserve(&buffer, trace_file,
						call->event.type, size, 0);
	अगर (!event)
		वापस;

	entry = ring_buffer_event_data(event);
	अगर (is_ret_probe(tu)) अणु
		entry->vaddr[0] = func;
		entry->vaddr[1] = inकाष्ठाion_poपूर्णांकer(regs);
		data = DATAOF_TRACE_ENTRY(entry, true);
	पूर्ण अन्यथा अणु
		entry->vaddr[0] = inकाष्ठाion_poपूर्णांकer(regs);
		data = DATAOF_TRACE_ENTRY(entry, false);
	पूर्ण

	स_नकल(data, ucb->buf, tu->tp.size + dsize);

	event_trigger_unlock_commit(trace_file, buffer, event, entry, 0);
पूर्ण

/* uprobe handler */
अटल पूर्णांक uprobe_trace_func(काष्ठा trace_uprobe *tu, काष्ठा pt_regs *regs,
			     काष्ठा uprobe_cpu_buffer *ucb, पूर्णांक dsize)
अणु
	काष्ठा event_file_link *link;

	अगर (is_ret_probe(tu))
		वापस 0;

	rcu_पढ़ो_lock();
	trace_probe_क्रम_each_link_rcu(link, &tu->tp)
		__uprobe_trace_func(tu, 0, regs, ucb, dsize, link->file);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल व्योम uretprobe_trace_func(काष्ठा trace_uprobe *tu, अचिन्हित दीर्घ func,
				 काष्ठा pt_regs *regs,
				 काष्ठा uprobe_cpu_buffer *ucb, पूर्णांक dsize)
अणु
	काष्ठा event_file_link *link;

	rcu_पढ़ो_lock();
	trace_probe_क्रम_each_link_rcu(link, &tu->tp)
		__uprobe_trace_func(tu, func, regs, ucb, dsize, link->file);
	rcu_पढ़ो_unlock();
पूर्ण

/* Event entry prपूर्णांकers */
अटल क्रमागत prपूर्णांक_line_t
prपूर्णांक_uprobe_event(काष्ठा trace_iterator *iter, पूर्णांक flags, काष्ठा trace_event *event)
अणु
	काष्ठा uprobe_trace_entry_head *entry;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_uprobe *tu;
	u8 *data;

	entry = (काष्ठा uprobe_trace_entry_head *)iter->ent;
	tu = trace_uprobe_primary_from_call(
		container_of(event, काष्ठा trace_event_call, event));
	अगर (unlikely(!tu))
		जाओ out;

	अगर (is_ret_probe(tu)) अणु
		trace_seq_म_लिखो(s, "%s: (0x%lx <- 0x%lx)",
				 trace_probe_name(&tu->tp),
				 entry->vaddr[1], entry->vaddr[0]);
		data = DATAOF_TRACE_ENTRY(entry, true);
	पूर्ण अन्यथा अणु
		trace_seq_म_लिखो(s, "%s: (0x%lx)",
				 trace_probe_name(&tu->tp),
				 entry->vaddr[0]);
		data = DATAOF_TRACE_ENTRY(entry, false);
	पूर्ण

	अगर (prपूर्णांक_probe_args(s, tu->tp.args, tu->tp.nr_args, data, entry) < 0)
		जाओ out;

	trace_seq_अ_दो(s, '\n');

 out:
	वापस trace_handle_वापस(s);
पूर्ण

प्रकार bool (*filter_func_t)(काष्ठा uprobe_consumer *self,
				क्रमागत uprobe_filter_ctx ctx,
				काष्ठा mm_काष्ठा *mm);

अटल पूर्णांक trace_uprobe_enable(काष्ठा trace_uprobe *tu, filter_func_t filter)
अणु
	पूर्णांक ret;

	tu->consumer.filter = filter;
	tu->inode = d_real_inode(tu->path.dentry);

	अगर (tu->ref_ctr_offset)
		ret = uprobe_रेजिस्टर_refctr(tu->inode, tu->offset,
				tu->ref_ctr_offset, &tu->consumer);
	अन्यथा
		ret = uprobe_रेजिस्टर(tu->inode, tu->offset, &tu->consumer);

	अगर (ret)
		tu->inode = शून्य;

	वापस ret;
पूर्ण

अटल व्योम __probe_event_disable(काष्ठा trace_probe *tp)
अणु
	काष्ठा trace_probe *pos;
	काष्ठा trace_uprobe *tu;

	tu = container_of(tp, काष्ठा trace_uprobe, tp);
	WARN_ON(!uprobe_filter_is_empty(tu->tp.event->filter));

	list_क्रम_each_entry(pos, trace_probe_probe_list(tp), list) अणु
		tu = container_of(pos, काष्ठा trace_uprobe, tp);
		अगर (!tu->inode)
			जारी;

		uprobe_unरेजिस्टर(tu->inode, tu->offset, &tu->consumer);
		tu->inode = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक probe_event_enable(काष्ठा trace_event_call *call,
			काष्ठा trace_event_file *file, filter_func_t filter)
अणु
	काष्ठा trace_probe *pos, *tp;
	काष्ठा trace_uprobe *tu;
	bool enabled;
	पूर्णांक ret;

	tp = trace_probe_primary_from_call(call);
	अगर (WARN_ON_ONCE(!tp))
		वापस -ENODEV;
	enabled = trace_probe_is_enabled(tp);

	/* This may also change "enabled" state */
	अगर (file) अणु
		अगर (trace_probe_test_flag(tp, TP_FLAG_PROखाता))
			वापस -EINTR;

		ret = trace_probe_add_file(tp, file);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		अगर (trace_probe_test_flag(tp, TP_FLAG_TRACE))
			वापस -EINTR;

		trace_probe_set_flag(tp, TP_FLAG_PROखाता);
	पूर्ण

	tu = container_of(tp, काष्ठा trace_uprobe, tp);
	WARN_ON(!uprobe_filter_is_empty(tu->tp.event->filter));

	अगर (enabled)
		वापस 0;

	ret = uprobe_buffer_enable();
	अगर (ret)
		जाओ err_flags;

	list_क्रम_each_entry(pos, trace_probe_probe_list(tp), list) अणु
		tu = container_of(pos, काष्ठा trace_uprobe, tp);
		ret = trace_uprobe_enable(tu, filter);
		अगर (ret) अणु
			__probe_event_disable(tp);
			जाओ err_buffer;
		पूर्ण
	पूर्ण

	वापस 0;

 err_buffer:
	uprobe_buffer_disable();

 err_flags:
	अगर (file)
		trace_probe_हटाओ_file(tp, file);
	अन्यथा
		trace_probe_clear_flag(tp, TP_FLAG_PROखाता);

	वापस ret;
पूर्ण

अटल व्योम probe_event_disable(काष्ठा trace_event_call *call,
				काष्ठा trace_event_file *file)
अणु
	काष्ठा trace_probe *tp;

	tp = trace_probe_primary_from_call(call);
	अगर (WARN_ON_ONCE(!tp))
		वापस;

	अगर (!trace_probe_is_enabled(tp))
		वापस;

	अगर (file) अणु
		अगर (trace_probe_हटाओ_file(tp, file) < 0)
			वापस;

		अगर (trace_probe_is_enabled(tp))
			वापस;
	पूर्ण अन्यथा
		trace_probe_clear_flag(tp, TP_FLAG_PROखाता);

	__probe_event_disable(tp);
	uprobe_buffer_disable();
पूर्ण

अटल पूर्णांक uprobe_event_define_fields(काष्ठा trace_event_call *event_call)
अणु
	पूर्णांक ret, size;
	काष्ठा uprobe_trace_entry_head field;
	काष्ठा trace_uprobe *tu;

	tu = trace_uprobe_primary_from_call(event_call);
	अगर (unlikely(!tu))
		वापस -ENODEV;

	अगर (is_ret_probe(tu)) अणु
		DEFINE_FIELD(अचिन्हित दीर्घ, vaddr[0], FIELD_STRING_FUNC, 0);
		DEFINE_FIELD(अचिन्हित दीर्घ, vaddr[1], FIELD_STRING_RETIP, 0);
		size = SIZखातापूर्ण_TRACE_ENTRY(true);
	पूर्ण अन्यथा अणु
		DEFINE_FIELD(अचिन्हित दीर्घ, vaddr[0], FIELD_STRING_IP, 0);
		size = SIZखातापूर्ण_TRACE_ENTRY(false);
	पूर्ण

	वापस traceprobe_define_arg_fields(event_call, size, &tu->tp);
पूर्ण

#अगर_घोषित CONFIG_PERF_EVENTS
अटल bool
__uprobe_perf_filter(काष्ठा trace_uprobe_filter *filter, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा perf_event *event;

	अगर (filter->nr_प्रणालीwide)
		वापस true;

	list_क्रम_each_entry(event, &filter->perf_events, hw.tp_list) अणु
		अगर (event->hw.target->mm == mm)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत bool
trace_uprobe_filter_event(काष्ठा trace_uprobe_filter *filter,
			  काष्ठा perf_event *event)
अणु
	वापस __uprobe_perf_filter(filter, event->hw.target->mm);
पूर्ण

अटल bool trace_uprobe_filter_हटाओ(काष्ठा trace_uprobe_filter *filter,
				       काष्ठा perf_event *event)
अणु
	bool करोne;

	ग_लिखो_lock(&filter->rwlock);
	अगर (event->hw.target) अणु
		list_del(&event->hw.tp_list);
		करोne = filter->nr_प्रणालीwide ||
			(event->hw.target->flags & PF_EXITING) ||
			trace_uprobe_filter_event(filter, event);
	पूर्ण अन्यथा अणु
		filter->nr_प्रणालीwide--;
		करोne = filter->nr_प्रणालीwide;
	पूर्ण
	ग_लिखो_unlock(&filter->rwlock);

	वापस करोne;
पूर्ण

/* This वापसs true अगर the filter always covers target mm */
अटल bool trace_uprobe_filter_add(काष्ठा trace_uprobe_filter *filter,
				    काष्ठा perf_event *event)
अणु
	bool करोne;

	ग_लिखो_lock(&filter->rwlock);
	अगर (event->hw.target) अणु
		/*
		 * event->parent != शून्य means copy_process(), we can aव्योम
		 * uprobe_apply(). current->mm must be probed and we can rely
		 * on dup_mmap() which preserves the alपढ़ोy installed bp's.
		 *
		 * attr.enable_on_exec means that exec/mmap will install the
		 * अवरोधpoपूर्णांकs we need.
		 */
		करोne = filter->nr_प्रणालीwide ||
			event->parent || event->attr.enable_on_exec ||
			trace_uprobe_filter_event(filter, event);
		list_add(&event->hw.tp_list, &filter->perf_events);
	पूर्ण अन्यथा अणु
		करोne = filter->nr_प्रणालीwide;
		filter->nr_प्रणालीwide++;
	पूर्ण
	ग_लिखो_unlock(&filter->rwlock);

	वापस करोne;
पूर्ण

अटल पूर्णांक uprobe_perf_बंद(काष्ठा trace_event_call *call,
			     काष्ठा perf_event *event)
अणु
	काष्ठा trace_probe *pos, *tp;
	काष्ठा trace_uprobe *tu;
	पूर्णांक ret = 0;

	tp = trace_probe_primary_from_call(call);
	अगर (WARN_ON_ONCE(!tp))
		वापस -ENODEV;

	tu = container_of(tp, काष्ठा trace_uprobe, tp);
	अगर (trace_uprobe_filter_हटाओ(tu->tp.event->filter, event))
		वापस 0;

	list_क्रम_each_entry(pos, trace_probe_probe_list(tp), list) अणु
		tu = container_of(pos, काष्ठा trace_uprobe, tp);
		ret = uprobe_apply(tu->inode, tu->offset, &tu->consumer, false);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक uprobe_perf_खोलो(काष्ठा trace_event_call *call,
			    काष्ठा perf_event *event)
अणु
	काष्ठा trace_probe *pos, *tp;
	काष्ठा trace_uprobe *tu;
	पूर्णांक err = 0;

	tp = trace_probe_primary_from_call(call);
	अगर (WARN_ON_ONCE(!tp))
		वापस -ENODEV;

	tu = container_of(tp, काष्ठा trace_uprobe, tp);
	अगर (trace_uprobe_filter_add(tu->tp.event->filter, event))
		वापस 0;

	list_क्रम_each_entry(pos, trace_probe_probe_list(tp), list) अणु
		err = uprobe_apply(tu->inode, tu->offset, &tu->consumer, true);
		अगर (err) अणु
			uprobe_perf_बंद(call, event);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल bool uprobe_perf_filter(काष्ठा uprobe_consumer *uc,
				क्रमागत uprobe_filter_ctx ctx, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा trace_uprobe_filter *filter;
	काष्ठा trace_uprobe *tu;
	पूर्णांक ret;

	tu = container_of(uc, काष्ठा trace_uprobe, consumer);
	filter = tu->tp.event->filter;

	पढ़ो_lock(&filter->rwlock);
	ret = __uprobe_perf_filter(filter, mm);
	पढ़ो_unlock(&filter->rwlock);

	वापस ret;
पूर्ण

अटल व्योम __uprobe_perf_func(काष्ठा trace_uprobe *tu,
			       अचिन्हित दीर्घ func, काष्ठा pt_regs *regs,
			       काष्ठा uprobe_cpu_buffer *ucb, पूर्णांक dsize)
अणु
	काष्ठा trace_event_call *call = trace_probe_event_call(&tu->tp);
	काष्ठा uprobe_trace_entry_head *entry;
	काष्ठा hlist_head *head;
	व्योम *data;
	पूर्णांक size, esize;
	पूर्णांक rctx;

	अगर (bpf_prog_array_valid(call)) अणु
		u32 ret;

		preempt_disable();
		ret = trace_call_bpf(call, regs);
		preempt_enable();
		अगर (!ret)
			वापस;
	पूर्ण

	esize = SIZखातापूर्ण_TRACE_ENTRY(is_ret_probe(tu));

	size = esize + tu->tp.size + dsize;
	size = ALIGN(size + माप(u32), माप(u64)) - माप(u32);
	अगर (WARN_ONCE(size > PERF_MAX_TRACE_SIZE, "profile buffer not large enough"))
		वापस;

	preempt_disable();
	head = this_cpu_ptr(call->perf_events);
	अगर (hlist_empty(head))
		जाओ out;

	entry = perf_trace_buf_alloc(size, शून्य, &rctx);
	अगर (!entry)
		जाओ out;

	अगर (is_ret_probe(tu)) अणु
		entry->vaddr[0] = func;
		entry->vaddr[1] = inकाष्ठाion_poपूर्णांकer(regs);
		data = DATAOF_TRACE_ENTRY(entry, true);
	पूर्ण अन्यथा अणु
		entry->vaddr[0] = inकाष्ठाion_poपूर्णांकer(regs);
		data = DATAOF_TRACE_ENTRY(entry, false);
	पूर्ण

	स_नकल(data, ucb->buf, tu->tp.size + dsize);

	अगर (size - esize > tu->tp.size + dsize) अणु
		पूर्णांक len = tu->tp.size + dsize;

		स_रखो(data + len, 0, size - esize - len);
	पूर्ण

	perf_trace_buf_submit(entry, size, rctx, call->event.type, 1, regs,
			      head, शून्य);
 out:
	preempt_enable();
पूर्ण

/* uprobe profile handler */
अटल पूर्णांक uprobe_perf_func(काष्ठा trace_uprobe *tu, काष्ठा pt_regs *regs,
			    काष्ठा uprobe_cpu_buffer *ucb, पूर्णांक dsize)
अणु
	अगर (!uprobe_perf_filter(&tu->consumer, 0, current->mm))
		वापस UPROBE_HANDLER_REMOVE;

	अगर (!is_ret_probe(tu))
		__uprobe_perf_func(tu, 0, regs, ucb, dsize);
	वापस 0;
पूर्ण

अटल व्योम uretprobe_perf_func(काष्ठा trace_uprobe *tu, अचिन्हित दीर्घ func,
				काष्ठा pt_regs *regs,
				काष्ठा uprobe_cpu_buffer *ucb, पूर्णांक dsize)
अणु
	__uprobe_perf_func(tu, func, regs, ucb, dsize);
पूर्ण

पूर्णांक bpf_get_uprobe_info(स्थिर काष्ठा perf_event *event, u32 *fd_type,
			स्थिर अक्षर **filename, u64 *probe_offset,
			bool perf_type_tracepoपूर्णांक)
अणु
	स्थिर अक्षर *pevent = trace_event_name(event->tp_event);
	स्थिर अक्षर *group = event->tp_event->class->प्रणाली;
	काष्ठा trace_uprobe *tu;

	अगर (perf_type_tracepoपूर्णांक)
		tu = find_probe_event(pevent, group);
	अन्यथा
		tu = trace_uprobe_primary_from_call(event->tp_event);
	अगर (!tu)
		वापस -EINVAL;

	*fd_type = is_ret_probe(tu) ? BPF_FD_TYPE_URETPROBE
				    : BPF_FD_TYPE_UPROBE;
	*filename = tu->filename;
	*probe_offset = tu->offset;
	वापस 0;
पूर्ण
#पूर्ण_अगर	/* CONFIG_PERF_EVENTS */

अटल पूर्णांक
trace_uprobe_रेजिस्टर(काष्ठा trace_event_call *event, क्रमागत trace_reg type,
		      व्योम *data)
अणु
	काष्ठा trace_event_file *file = data;

	चयन (type) अणु
	हाल TRACE_REG_REGISTER:
		वापस probe_event_enable(event, file, शून्य);

	हाल TRACE_REG_UNREGISTER:
		probe_event_disable(event, file);
		वापस 0;

#अगर_घोषित CONFIG_PERF_EVENTS
	हाल TRACE_REG_PERF_REGISTER:
		वापस probe_event_enable(event, शून्य, uprobe_perf_filter);

	हाल TRACE_REG_PERF_UNREGISTER:
		probe_event_disable(event, शून्य);
		वापस 0;

	हाल TRACE_REG_PERF_OPEN:
		वापस uprobe_perf_खोलो(event, data);

	हाल TRACE_REG_PERF_CLOSE:
		वापस uprobe_perf_बंद(event, data);

#पूर्ण_अगर
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक uprobe_dispatcher(काष्ठा uprobe_consumer *con, काष्ठा pt_regs *regs)
अणु
	काष्ठा trace_uprobe *tu;
	काष्ठा uprobe_dispatch_data udd;
	काष्ठा uprobe_cpu_buffer *ucb;
	पूर्णांक dsize, esize;
	पूर्णांक ret = 0;


	tu = container_of(con, काष्ठा trace_uprobe, consumer);
	tu->nhit++;

	udd.tu = tu;
	udd.bp_addr = inकाष्ठाion_poपूर्णांकer(regs);

	current->utask->vaddr = (अचिन्हित दीर्घ) &udd;

	अगर (WARN_ON_ONCE(!uprobe_cpu_buffer))
		वापस 0;

	dsize = __get_data_size(&tu->tp, regs);
	esize = SIZखातापूर्ण_TRACE_ENTRY(is_ret_probe(tu));

	ucb = uprobe_buffer_get();
	store_trace_args(ucb->buf, &tu->tp, regs, esize, dsize);

	अगर (trace_probe_test_flag(&tu->tp, TP_FLAG_TRACE))
		ret |= uprobe_trace_func(tu, regs, ucb, dsize);

#अगर_घोषित CONFIG_PERF_EVENTS
	अगर (trace_probe_test_flag(&tu->tp, TP_FLAG_PROखाता))
		ret |= uprobe_perf_func(tu, regs, ucb, dsize);
#पूर्ण_अगर
	uprobe_buffer_put(ucb);
	वापस ret;
पूर्ण

अटल पूर्णांक uretprobe_dispatcher(काष्ठा uprobe_consumer *con,
				अचिन्हित दीर्घ func, काष्ठा pt_regs *regs)
अणु
	काष्ठा trace_uprobe *tu;
	काष्ठा uprobe_dispatch_data udd;
	काष्ठा uprobe_cpu_buffer *ucb;
	पूर्णांक dsize, esize;

	tu = container_of(con, काष्ठा trace_uprobe, consumer);

	udd.tu = tu;
	udd.bp_addr = func;

	current->utask->vaddr = (अचिन्हित दीर्घ) &udd;

	अगर (WARN_ON_ONCE(!uprobe_cpu_buffer))
		वापस 0;

	dsize = __get_data_size(&tu->tp, regs);
	esize = SIZखातापूर्ण_TRACE_ENTRY(is_ret_probe(tu));

	ucb = uprobe_buffer_get();
	store_trace_args(ucb->buf, &tu->tp, regs, esize, dsize);

	अगर (trace_probe_test_flag(&tu->tp, TP_FLAG_TRACE))
		uretprobe_trace_func(tu, func, regs, ucb, dsize);

#अगर_घोषित CONFIG_PERF_EVENTS
	अगर (trace_probe_test_flag(&tu->tp, TP_FLAG_PROखाता))
		uretprobe_perf_func(tu, func, regs, ucb, dsize);
#पूर्ण_अगर
	uprobe_buffer_put(ucb);
	वापस 0;
पूर्ण

अटल काष्ठा trace_event_functions uprobe_funcs = अणु
	.trace		= prपूर्णांक_uprobe_event
पूर्ण;

अटल काष्ठा trace_event_fields uprobe_fields_array[] = अणु
	अणु .type = TRACE_FUNCTION_TYPE,
	  .define_fields = uprobe_event_define_fields पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल अंतरभूत व्योम init_trace_event_call(काष्ठा trace_uprobe *tu)
अणु
	काष्ठा trace_event_call *call = trace_probe_event_call(&tu->tp);
	call->event.funcs = &uprobe_funcs;
	call->class->fields_array = uprobe_fields_array;

	call->flags = TRACE_EVENT_FL_UPROBE | TRACE_EVENT_FL_CAP_ANY;
	call->class->reg = trace_uprobe_रेजिस्टर;
पूर्ण

अटल पूर्णांक रेजिस्टर_uprobe_event(काष्ठा trace_uprobe *tu)
अणु
	init_trace_event_call(tu);

	वापस trace_probe_रेजिस्टर_event_call(&tu->tp);
पूर्ण

अटल पूर्णांक unरेजिस्टर_uprobe_event(काष्ठा trace_uprobe *tu)
अणु
	वापस trace_probe_unरेजिस्टर_event_call(&tu->tp);
पूर्ण

#अगर_घोषित CONFIG_PERF_EVENTS
काष्ठा trace_event_call *
create_local_trace_uprobe(अक्षर *name, अचिन्हित दीर्घ offs,
			  अचिन्हित दीर्घ ref_ctr_offset, bool is_वापस)
अणु
	काष्ठा trace_uprobe *tu;
	काष्ठा path path;
	पूर्णांक ret;

	ret = kern_path(name, LOOKUP_FOLLOW, &path);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (!d_is_reg(path.dentry)) अणु
		path_put(&path);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/*
	 * local trace_kprobes are not added to dyn_event, so they are never
	 * searched in find_trace_kprobe(). Thereक्रमe, there is no concern of
	 * duplicated name "DUMMY_EVENT" here.
	 */
	tu = alloc_trace_uprobe(UPROBE_EVENT_SYSTEM, "DUMMY_EVENT", 0,
				is_वापस);

	अगर (IS_ERR(tu)) अणु
		pr_info("Failed to allocate trace_uprobe.(%d)\n",
			(पूर्णांक)PTR_ERR(tu));
		path_put(&path);
		वापस ERR_CAST(tu);
	पूर्ण

	tu->offset = offs;
	tu->path = path;
	tu->ref_ctr_offset = ref_ctr_offset;
	tu->filename = kstrdup(name, GFP_KERNEL);
	init_trace_event_call(tu);

	अगर (traceprobe_set_prपूर्णांक_fmt(&tu->tp, is_ret_probe(tu)) < 0) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	वापस trace_probe_event_call(&tu->tp);
error:
	मुक्त_trace_uprobe(tu);
	वापस ERR_PTR(ret);
पूर्ण

व्योम destroy_local_trace_uprobe(काष्ठा trace_event_call *event_call)
अणु
	काष्ठा trace_uprobe *tu;

	tu = trace_uprobe_primary_from_call(event_call);

	मुक्त_trace_uprobe(tu);
पूर्ण
#पूर्ण_अगर /* CONFIG_PERF_EVENTS */

/* Make a trace पूर्णांकerface क्रम controlling probe poपूर्णांकs */
अटल __init पूर्णांक init_uprobe_trace(व्योम)
अणु
	पूर्णांक ret;

	ret = dyn_event_रेजिस्टर(&trace_uprobe_ops);
	अगर (ret)
		वापस ret;

	ret = tracing_init_dentry();
	अगर (ret)
		वापस 0;

	trace_create_file("uprobe_events", 0644, शून्य,
				    शून्य, &uprobe_events_ops);
	/* Profile पूर्णांकerface */
	trace_create_file("uprobe_profile", 0444, शून्य,
				    शून्य, &uprobe_profile_ops);
	वापस 0;
पूर्ण

fs_initcall(init_uprobe_trace);
