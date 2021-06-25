<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009-2011, Frederic Weisbecker <fweisbec@gmail.com>
 *
 * Handle the callchains from the stream in an ad-hoc radix tree and then
 * sort them in an rbtree.
 *
 * Using a radix क्रम code path provides a fast retrieval and factorizes
 * memory use. Also that lets us use the paths in a hierarchical graph view.
 *
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <त्रुटिसं.स>
#समावेश <गणित.स>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>

#समावेश "asm/bug.h"

#समावेश "debug.h"
#समावेश "dso.h"
#समावेश "event.h"
#समावेश "hist.h"
#समावेश "sort.h"
#समावेश "machine.h"
#समावेश "map.h"
#समावेश "callchain.h"
#समावेश "branch.h"
#समावेश "symbol.h"
#समावेश "../perf.h"

#घोषणा CALLCHAIN_PARAM_DEFAULT			\
	.mode		= CHAIN_GRAPH_ABS,	\
	.min_percent	= 0.5,			\
	.order		= ORDER_CALLEE,		\
	.key		= CCKEY_FUNCTION,	\
	.value		= CCVAL_PERCENT,	\

काष्ठा callchain_param callchain_param = अणु
	CALLCHAIN_PARAM_DEFAULT
पूर्ण;

/*
 * Are there any events usind DWARF callchains?
 *
 * I.e.
 *
 * -e cycles/call-graph=dwarf/
 */
bool dwarf_callchain_users;

काष्ठा callchain_param callchain_param_शेष = अणु
	CALLCHAIN_PARAM_DEFAULT
पूर्ण;

__thपढ़ो काष्ठा callchain_cursor callchain_cursor;

पूर्णांक parse_callchain_record_opt(स्थिर अक्षर *arg, काष्ठा callchain_param *param)
अणु
	वापस parse_callchain_record(arg, param);
पूर्ण

अटल पूर्णांक parse_callchain_mode(स्थिर अक्षर *value)
अणु
	अगर (!म_भेदन(value, "graph", म_माप(value))) अणु
		callchain_param.mode = CHAIN_GRAPH_ABS;
		वापस 0;
	पूर्ण
	अगर (!म_भेदन(value, "flat", म_माप(value))) अणु
		callchain_param.mode = CHAIN_FLAT;
		वापस 0;
	पूर्ण
	अगर (!म_भेदन(value, "fractal", म_माप(value))) अणु
		callchain_param.mode = CHAIN_GRAPH_REL;
		वापस 0;
	पूर्ण
	अगर (!म_भेदन(value, "folded", म_माप(value))) अणु
		callchain_param.mode = CHAIN_FOLDED;
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक parse_callchain_order(स्थिर अक्षर *value)
अणु
	अगर (!म_भेदन(value, "caller", म_माप(value))) अणु
		callchain_param.order = ORDER_CALLER;
		callchain_param.order_set = true;
		वापस 0;
	पूर्ण
	अगर (!म_भेदन(value, "callee", म_माप(value))) अणु
		callchain_param.order = ORDER_CALLEE;
		callchain_param.order_set = true;
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक parse_callchain_sort_key(स्थिर अक्षर *value)
अणु
	अगर (!म_भेदन(value, "function", म_माप(value))) अणु
		callchain_param.key = CCKEY_FUNCTION;
		वापस 0;
	पूर्ण
	अगर (!म_भेदन(value, "address", म_माप(value))) अणु
		callchain_param.key = CCKEY_ADDRESS;
		वापस 0;
	पूर्ण
	अगर (!म_भेदन(value, "srcline", म_माप(value))) अणु
		callchain_param.key = CCKEY_SRCLINE;
		वापस 0;
	पूर्ण
	अगर (!म_भेदन(value, "branch", म_माप(value))) अणु
		callchain_param.branch_callstack = 1;
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक parse_callchain_value(स्थिर अक्षर *value)
अणु
	अगर (!म_भेदन(value, "percent", म_माप(value))) अणु
		callchain_param.value = CCVAL_PERCENT;
		वापस 0;
	पूर्ण
	अगर (!म_भेदन(value, "period", म_माप(value))) अणु
		callchain_param.value = CCVAL_PERIOD;
		वापस 0;
	पूर्ण
	अगर (!म_भेदन(value, "count", म_माप(value))) अणु
		callchain_param.value = CCVAL_COUNT;
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक get_stack_size(स्थिर अक्षर *str, अचिन्हित दीर्घ *_size)
अणु
	अक्षर *endptr;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ max_size = round_करोwn(अच_लघु_उच्च, माप(u64));

	size = म_से_अदीर्घ(str, &endptr, 0);

	करो अणु
		अगर (*endptr)
			अवरोध;

		size = round_up(size, माप(u64));
		अगर (!size || size > max_size)
			अवरोध;

		*_size = size;
		वापस 0;

	पूर्ण जबतक (0);

	pr_err("callchain: Incorrect stack dump size (max %ld): %s\n",
	       max_size, str);
	वापस -1;
पूर्ण

अटल पूर्णांक
__parse_callchain_report_opt(स्थिर अक्षर *arg, bool allow_record_opt)
अणु
	अक्षर *tok;
	अक्षर *endptr, *saveptr = शून्य;
	bool minpcnt_set = false;
	bool record_opt_set = false;
	bool try_stack_size = false;

	callchain_param.enabled = true;
	symbol_conf.use_callchain = true;

	अगर (!arg)
		वापस 0;

	जबतक ((tok = म_मोहर_r((अक्षर *)arg, ",", &saveptr)) != शून्य) अणु
		अगर (!म_भेदन(tok, "none", म_माप(tok))) अणु
			callchain_param.mode = CHAIN_NONE;
			callchain_param.enabled = false;
			symbol_conf.use_callchain = false;
			वापस 0;
		पूर्ण

		अगर (!parse_callchain_mode(tok) ||
		    !parse_callchain_order(tok) ||
		    !parse_callchain_sort_key(tok) ||
		    !parse_callchain_value(tok)) अणु
			/* parsing ok - move on to the next */
			try_stack_size = false;
			जाओ next;
		पूर्ण अन्यथा अगर (allow_record_opt && !record_opt_set) अणु
			अगर (parse_callchain_record(tok, &callchain_param))
				जाओ try_numbers;

			/* assume that number followed by 'dwarf' is stack size */
			अगर (callchain_param.record_mode == CALLCHAIN_DWARF)
				try_stack_size = true;

			record_opt_set = true;
			जाओ next;
		पूर्ण

try_numbers:
		अगर (try_stack_size) अणु
			अचिन्हित दीर्घ size = 0;

			अगर (get_stack_size(tok, &size) < 0)
				वापस -1;
			callchain_param.dump_size = size;
			try_stack_size = false;
		पूर्ण अन्यथा अगर (!minpcnt_set) अणु
			/* try to get the min percent */
			callchain_param.min_percent = म_से_भग्न(tok, &endptr);
			अगर (tok == endptr)
				वापस -1;
			minpcnt_set = true;
		पूर्ण अन्यथा अणु
			/* try prपूर्णांक limit at last */
			callchain_param.prपूर्णांक_limit = म_से_अदीर्घ(tok, &endptr, 0);
			अगर (tok == endptr)
				वापस -1;
		पूर्ण
next:
		arg = शून्य;
	पूर्ण

	अगर (callchain_रेजिस्टर_param(&callchain_param) < 0) अणु
		pr_err("Can't register callchain params\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक parse_callchain_report_opt(स्थिर अक्षर *arg)
अणु
	वापस __parse_callchain_report_opt(arg, false);
पूर्ण

पूर्णांक parse_callchain_top_opt(स्थिर अक्षर *arg)
अणु
	वापस __parse_callchain_report_opt(arg, true);
पूर्ण

पूर्णांक parse_callchain_record(स्थिर अक्षर *arg, काष्ठा callchain_param *param)
अणु
	अक्षर *tok, *name, *saveptr = शून्य;
	अक्षर *buf;
	पूर्णांक ret = -1;

	/* We need buffer that we know we can ग_लिखो to. */
	buf = दो_स्मृति(म_माप(arg) + 1);
	अगर (!buf)
		वापस -ENOMEM;

	म_नकल(buf, arg);

	tok = म_मोहर_r((अक्षर *)buf, ",", &saveptr);
	name = tok ? : (अक्षर *)buf;

	करो अणु
		/* Framepoपूर्णांकer style */
		अगर (!म_भेदन(name, "fp", माप("fp"))) अणु
			अगर (!म_मोहर_r(शून्य, ",", &saveptr)) अणु
				param->record_mode = CALLCHAIN_FP;
				ret = 0;
			पूर्ण अन्यथा
				pr_err("callchain: No more arguments "
				       "needed for --call-graph fp\n");
			अवरोध;

		/* Dwarf style */
		पूर्ण अन्यथा अगर (!म_भेदन(name, "dwarf", माप("dwarf"))) अणु
			स्थिर अचिन्हित दीर्घ शेष_stack_dump_size = 8192;

			ret = 0;
			param->record_mode = CALLCHAIN_DWARF;
			param->dump_size = शेष_stack_dump_size;
			dwarf_callchain_users = true;

			tok = म_मोहर_r(शून्य, ",", &saveptr);
			अगर (tok) अणु
				अचिन्हित दीर्घ size = 0;

				ret = get_stack_size(tok, &size);
				param->dump_size = size;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेदन(name, "lbr", माप("lbr"))) अणु
			अगर (!म_मोहर_r(शून्य, ",", &saveptr)) अणु
				param->record_mode = CALLCHAIN_LBR;
				ret = 0;
			पूर्ण अन्यथा
				pr_err("callchain: No more arguments "
					"needed for --call-graph lbr\n");
			अवरोध;
		पूर्ण अन्यथा अणु
			pr_err("callchain: Unknown --call-graph option "
			       "value: %s\n", arg);
			अवरोध;
		पूर्ण

	पूर्ण जबतक (0);

	मुक्त(buf);
	वापस ret;
पूर्ण

पूर्णांक perf_callchain_config(स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	अक्षर *endptr;

	अगर (!strstarts(var, "call-graph."))
		वापस 0;
	var += माप("call-graph.") - 1;

	अगर (!म_भेद(var, "record-mode"))
		वापस parse_callchain_record_opt(value, &callchain_param);
	अगर (!म_भेद(var, "dump-size")) अणु
		अचिन्हित दीर्घ size = 0;
		पूर्णांक ret;

		ret = get_stack_size(value, &size);
		callchain_param.dump_size = size;

		वापस ret;
	पूर्ण
	अगर (!म_भेद(var, "print-type"))अणु
		पूर्णांक ret;
		ret = parse_callchain_mode(value);
		अगर (ret == -1)
			pr_err("Invalid callchain mode: %s\n", value);
		वापस ret;
	पूर्ण
	अगर (!म_भेद(var, "order"))अणु
		पूर्णांक ret;
		ret = parse_callchain_order(value);
		अगर (ret == -1)
			pr_err("Invalid callchain order: %s\n", value);
		वापस ret;
	पूर्ण
	अगर (!म_भेद(var, "sort-key"))अणु
		पूर्णांक ret;
		ret = parse_callchain_sort_key(value);
		अगर (ret == -1)
			pr_err("Invalid callchain sort key: %s\n", value);
		वापस ret;
	पूर्ण
	अगर (!म_भेद(var, "threshold")) अणु
		callchain_param.min_percent = म_से_भग्न(value, &endptr);
		अगर (value == endptr) अणु
			pr_err("Invalid callchain threshold: %s\n", value);
			वापस -1;
		पूर्ण
	पूर्ण
	अगर (!म_भेद(var, "print-limit")) अणु
		callchain_param.prपूर्णांक_limit = म_से_भग्न(value, &endptr);
		अगर (value == endptr) अणु
			pr_err("Invalid callchain print limit: %s\n", value);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
rb_insert_callchain(काष्ठा rb_root *root, काष्ठा callchain_node *chain,
		    क्रमागत chain_mode mode)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा callchain_node *rnode;
	u64 chain_cumul = callchain_cumul_hits(chain);

	जबतक (*p) अणु
		u64 rnode_cumul;

		parent = *p;
		rnode = rb_entry(parent, काष्ठा callchain_node, rb_node);
		rnode_cumul = callchain_cumul_hits(rnode);

		चयन (mode) अणु
		हाल CHAIN_FLAT:
		हाल CHAIN_FOLDED:
			अगर (rnode->hit < chain->hit)
				p = &(*p)->rb_left;
			अन्यथा
				p = &(*p)->rb_right;
			अवरोध;
		हाल CHAIN_GRAPH_ABS: /* Fallकरोwn */
		हाल CHAIN_GRAPH_REL:
			अगर (rnode_cumul < chain_cumul)
				p = &(*p)->rb_left;
			अन्यथा
				p = &(*p)->rb_right;
			अवरोध;
		हाल CHAIN_NONE:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	rb_link_node(&chain->rb_node, parent, p);
	rb_insert_color(&chain->rb_node, root);
पूर्ण

अटल व्योम
__sort_chain_flat(काष्ठा rb_root *rb_root, काष्ठा callchain_node *node,
		  u64 min_hit)
अणु
	काष्ठा rb_node *n;
	काष्ठा callchain_node *child;

	n = rb_first(&node->rb_root_in);
	जबतक (n) अणु
		child = rb_entry(n, काष्ठा callchain_node, rb_node_in);
		n = rb_next(n);

		__sort_chain_flat(rb_root, child, min_hit);
	पूर्ण

	अगर (node->hit && node->hit >= min_hit)
		rb_insert_callchain(rb_root, node, CHAIN_FLAT);
पूर्ण

/*
 * Once we get every callchains from the stream, we can now
 * sort them by hit
 */
अटल व्योम
sort_chain_flat(काष्ठा rb_root *rb_root, काष्ठा callchain_root *root,
		u64 min_hit, काष्ठा callchain_param *param __maybe_unused)
अणु
	*rb_root = RB_ROOT;
	__sort_chain_flat(rb_root, &root->node, min_hit);
पूर्ण

अटल व्योम __sort_chain_graph_असल(काष्ठा callchain_node *node,
				   u64 min_hit)
अणु
	काष्ठा rb_node *n;
	काष्ठा callchain_node *child;

	node->rb_root = RB_ROOT;
	n = rb_first(&node->rb_root_in);

	जबतक (n) अणु
		child = rb_entry(n, काष्ठा callchain_node, rb_node_in);
		n = rb_next(n);

		__sort_chain_graph_असल(child, min_hit);
		अगर (callchain_cumul_hits(child) >= min_hit)
			rb_insert_callchain(&node->rb_root, child,
					    CHAIN_GRAPH_ABS);
	पूर्ण
पूर्ण

अटल व्योम
sort_chain_graph_असल(काष्ठा rb_root *rb_root, काष्ठा callchain_root *chain_root,
		     u64 min_hit, काष्ठा callchain_param *param __maybe_unused)
अणु
	__sort_chain_graph_असल(&chain_root->node, min_hit);
	rb_root->rb_node = chain_root->node.rb_root.rb_node;
पूर्ण

अटल व्योम __sort_chain_graph_rel(काष्ठा callchain_node *node,
				   द्विगुन min_percent)
अणु
	काष्ठा rb_node *n;
	काष्ठा callchain_node *child;
	u64 min_hit;

	node->rb_root = RB_ROOT;
	min_hit = उच्चमान(node->children_hit * min_percent);

	n = rb_first(&node->rb_root_in);
	जबतक (n) अणु
		child = rb_entry(n, काष्ठा callchain_node, rb_node_in);
		n = rb_next(n);

		__sort_chain_graph_rel(child, min_percent);
		अगर (callchain_cumul_hits(child) >= min_hit)
			rb_insert_callchain(&node->rb_root, child,
					    CHAIN_GRAPH_REL);
	पूर्ण
पूर्ण

अटल व्योम
sort_chain_graph_rel(काष्ठा rb_root *rb_root, काष्ठा callchain_root *chain_root,
		     u64 min_hit __maybe_unused, काष्ठा callchain_param *param)
अणु
	__sort_chain_graph_rel(&chain_root->node, param->min_percent / 100.0);
	rb_root->rb_node = chain_root->node.rb_root.rb_node;
पूर्ण

पूर्णांक callchain_रेजिस्टर_param(काष्ठा callchain_param *param)
अणु
	चयन (param->mode) अणु
	हाल CHAIN_GRAPH_ABS:
		param->sort = sort_chain_graph_असल;
		अवरोध;
	हाल CHAIN_GRAPH_REL:
		param->sort = sort_chain_graph_rel;
		अवरोध;
	हाल CHAIN_FLAT:
	हाल CHAIN_FOLDED:
		param->sort = sort_chain_flat;
		अवरोध;
	हाल CHAIN_NONE:
	शेष:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Create a child क्रम a parent. If inherit_children, then the new child
 * will become the new parent of it's parent children
 */
अटल काष्ठा callchain_node *
create_child(काष्ठा callchain_node *parent, bool inherit_children)
अणु
	काष्ठा callchain_node *new;

	new = zalloc(माप(*new));
	अगर (!new) अणु
		लिखो_त्रुटि("not enough memory to create child for code path tree");
		वापस शून्य;
	पूर्ण
	new->parent = parent;
	INIT_LIST_HEAD(&new->val);
	INIT_LIST_HEAD(&new->parent_val);

	अगर (inherit_children) अणु
		काष्ठा rb_node *n;
		काष्ठा callchain_node *child;

		new->rb_root_in = parent->rb_root_in;
		parent->rb_root_in = RB_ROOT;

		n = rb_first(&new->rb_root_in);
		जबतक (n) अणु
			child = rb_entry(n, काष्ठा callchain_node, rb_node_in);
			child->parent = new;
			n = rb_next(n);
		पूर्ण

		/* make it the first child */
		rb_link_node(&new->rb_node_in, शून्य, &parent->rb_root_in.rb_node);
		rb_insert_color(&new->rb_node_in, &parent->rb_root_in);
	पूर्ण

	वापस new;
पूर्ण


/*
 * Fill the node with callchain values
 */
अटल पूर्णांक
fill_node(काष्ठा callchain_node *node, काष्ठा callchain_cursor *cursor)
अणु
	काष्ठा callchain_cursor_node *cursor_node;

	node->val_nr = cursor->nr - cursor->pos;
	अगर (!node->val_nr)
		pr_warning("Warning: empty node in callchain tree\n");

	cursor_node = callchain_cursor_current(cursor);

	जबतक (cursor_node) अणु
		काष्ठा callchain_list *call;

		call = zalloc(माप(*call));
		अगर (!call) अणु
			लिखो_त्रुटि("not enough memory for the code path tree");
			वापस -1;
		पूर्ण
		call->ip = cursor_node->ip;
		call->ms = cursor_node->ms;
		map__get(call->ms.map);
		call->srcline = cursor_node->srcline;

		अगर (cursor_node->branch) अणु
			call->branch_count = 1;

			अगर (cursor_node->branch_from) अणु
				/*
				 * branch_from is set with value somewhere अन्यथा
				 * to imply it's "to" of a branch.
				 */
				call->brtype_stat.branch_to = true;

				अगर (cursor_node->branch_flags.predicted)
					call->predicted_count = 1;

				अगर (cursor_node->branch_flags.पात)
					call->पात_count = 1;

				branch_type_count(&call->brtype_stat,
						  &cursor_node->branch_flags,
						  cursor_node->branch_from,
						  cursor_node->ip);
			पूर्ण अन्यथा अणु
				/*
				 * It's "from" of a branch
				 */
				call->brtype_stat.branch_to = false;
				call->cycles_count =
					cursor_node->branch_flags.cycles;
				call->iter_count = cursor_node->nr_loop_iter;
				call->iter_cycles = cursor_node->iter_cycles;
			पूर्ण
		पूर्ण

		list_add_tail(&call->list, &node->val);

		callchain_cursor_advance(cursor);
		cursor_node = callchain_cursor_current(cursor);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा callchain_node *
add_child(काष्ठा callchain_node *parent,
	  काष्ठा callchain_cursor *cursor,
	  u64 period)
अणु
	काष्ठा callchain_node *new;

	new = create_child(parent, false);
	अगर (new == शून्य)
		वापस शून्य;

	अगर (fill_node(new, cursor) < 0) अणु
		काष्ठा callchain_list *call, *पंचांगp;

		list_क्रम_each_entry_safe(call, पंचांगp, &new->val, list) अणु
			list_del_init(&call->list);
			map__zput(call->ms.map);
			मुक्त(call);
		पूर्ण
		मुक्त(new);
		वापस शून्य;
	पूर्ण

	new->children_hit = 0;
	new->hit = period;
	new->children_count = 0;
	new->count = 1;
	वापस new;
पूर्ण

क्रमागत match_result अणु
	MATCH_ERROR  = -1,
	MATCH_EQ,
	MATCH_LT,
	MATCH_GT,
पूर्ण;

अटल क्रमागत match_result match_chain_strings(स्थिर अक्षर *left,
					     स्थिर अक्षर *right)
अणु
	क्रमागत match_result ret = MATCH_EQ;
	पूर्णांक cmp;

	अगर (left && right)
		cmp = म_भेद(left, right);
	अन्यथा अगर (!left && right)
		cmp = 1;
	अन्यथा अगर (left && !right)
		cmp = -1;
	अन्यथा
		वापस MATCH_ERROR;

	अगर (cmp != 0)
		ret = cmp < 0 ? MATCH_LT : MATCH_GT;

	वापस ret;
पूर्ण

/*
 * We need to always use relative addresses because we're aggregating
 * callchains from multiple thपढ़ोs, i.e. dअगरferent address spaces, so
 * comparing असलolute addresses make no sense as a symbol in a DSO may end up
 * in a dअगरferent address when used in a dअगरferent binary or even the same
 * binary but with some sort of address अक्रमomization technique, thus we need
 * to compare just relative addresses. -acme
 */
अटल क्रमागत match_result match_chain_dso_addresses(काष्ठा map *left_map, u64 left_ip,
						   काष्ठा map *right_map, u64 right_ip)
अणु
	काष्ठा dso *left_dso = left_map ? left_map->dso : शून्य;
	काष्ठा dso *right_dso = right_map ? right_map->dso : शून्य;

	अगर (left_dso != right_dso)
		वापस left_dso < right_dso ? MATCH_LT : MATCH_GT;

	अगर (left_ip != right_ip)
 		वापस left_ip < right_ip ? MATCH_LT : MATCH_GT;

	वापस MATCH_EQ;
पूर्ण

अटल क्रमागत match_result match_chain(काष्ठा callchain_cursor_node *node,
				     काष्ठा callchain_list *cnode)
अणु
	क्रमागत match_result match = MATCH_ERROR;

	चयन (callchain_param.key) अणु
	हाल CCKEY_SRCLINE:
		match = match_chain_strings(cnode->srcline, node->srcline);
		अगर (match != MATCH_ERROR)
			अवरोध;
		/* otherwise fall-back to symbol-based comparison below */
		__fallthrough;
	हाल CCKEY_FUNCTION:
		अगर (node->ms.sym && cnode->ms.sym) अणु
			/*
			 * Compare अंतरभूतd frames based on their symbol name
			 * because dअगरferent अंतरभूतd frames will have the same
			 * symbol start. Otherwise करो a faster comparison based
			 * on the symbol start address.
			 */
			अगर (cnode->ms.sym->अंतरभूतd || node->ms.sym->अंतरभूतd) अणु
				match = match_chain_strings(cnode->ms.sym->name,
							    node->ms.sym->name);
				अगर (match != MATCH_ERROR)
					अवरोध;
			पूर्ण अन्यथा अणु
				match = match_chain_dso_addresses(cnode->ms.map, cnode->ms.sym->start,
								  node->ms.map, node->ms.sym->start);
				अवरोध;
			पूर्ण
		पूर्ण
		/* otherwise fall-back to IP-based comparison below */
		__fallthrough;
	हाल CCKEY_ADDRESS:
	शेष:
		match = match_chain_dso_addresses(cnode->ms.map, cnode->ip, node->ms.map, node->ip);
		अवरोध;
	पूर्ण

	अगर (match == MATCH_EQ && node->branch) अणु
		cnode->branch_count++;

		अगर (node->branch_from) अणु
			/*
			 * It's "to" of a branch
			 */
			cnode->brtype_stat.branch_to = true;

			अगर (node->branch_flags.predicted)
				cnode->predicted_count++;

			अगर (node->branch_flags.पात)
				cnode->पात_count++;

			branch_type_count(&cnode->brtype_stat,
					  &node->branch_flags,
					  node->branch_from,
					  node->ip);
		पूर्ण अन्यथा अणु
			/*
			 * It's "from" of a branch
			 */
			cnode->brtype_stat.branch_to = false;
			cnode->cycles_count += node->branch_flags.cycles;
			cnode->iter_count += node->nr_loop_iter;
			cnode->iter_cycles += node->iter_cycles;
			cnode->from_count++;
		पूर्ण
	पूर्ण

	वापस match;
पूर्ण

/*
 * Split the parent in two parts (a new child is created) and
 * give a part of its callchain to the created child.
 * Then create another child to host the given callchain of new branch
 */
अटल पूर्णांक
split_add_child(काष्ठा callchain_node *parent,
		काष्ठा callchain_cursor *cursor,
		काष्ठा callchain_list *to_split,
		u64 idx_parents, u64 idx_local, u64 period)
अणु
	काष्ठा callchain_node *new;
	काष्ठा list_head *old_tail;
	अचिन्हित पूर्णांक idx_total = idx_parents + idx_local;

	/* split */
	new = create_child(parent, true);
	अगर (new == शून्य)
		वापस -1;

	/* split the callchain and move a part to the new child */
	old_tail = parent->val.prev;
	list_del_range(&to_split->list, old_tail);
	new->val.next = &to_split->list;
	new->val.prev = old_tail;
	to_split->list.prev = &new->val;
	old_tail->next = &new->val;

	/* split the hits */
	new->hit = parent->hit;
	new->children_hit = parent->children_hit;
	parent->children_hit = callchain_cumul_hits(new);
	new->val_nr = parent->val_nr - idx_local;
	parent->val_nr = idx_local;
	new->count = parent->count;
	new->children_count = parent->children_count;
	parent->children_count = callchain_cumul_counts(new);

	/* create a new child क्रम the new branch अगर any */
	अगर (idx_total < cursor->nr) अणु
		काष्ठा callchain_node *first;
		काष्ठा callchain_list *cnode;
		काष्ठा callchain_cursor_node *node;
		काष्ठा rb_node *p, **pp;

		parent->hit = 0;
		parent->children_hit += period;
		parent->count = 0;
		parent->children_count += 1;

		node = callchain_cursor_current(cursor);
		new = add_child(parent, cursor, period);
		अगर (new == शून्य)
			वापस -1;

		/*
		 * This is second child since we moved parent's children
		 * to new (first) child above.
		 */
		p = parent->rb_root_in.rb_node;
		first = rb_entry(p, काष्ठा callchain_node, rb_node_in);
		cnode = list_first_entry(&first->val, काष्ठा callchain_list,
					 list);

		अगर (match_chain(node, cnode) == MATCH_LT)
			pp = &p->rb_left;
		अन्यथा
			pp = &p->rb_right;

		rb_link_node(&new->rb_node_in, p, pp);
		rb_insert_color(&new->rb_node_in, &parent->rb_root_in);
	पूर्ण अन्यथा अणु
		parent->hit = period;
		parent->count = 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल क्रमागत match_result
append_chain(काष्ठा callchain_node *root,
	     काष्ठा callchain_cursor *cursor,
	     u64 period);

अटल पूर्णांक
append_chain_children(काष्ठा callchain_node *root,
		      काष्ठा callchain_cursor *cursor,
		      u64 period)
अणु
	काष्ठा callchain_node *rnode;
	काष्ठा callchain_cursor_node *node;
	काष्ठा rb_node **p = &root->rb_root_in.rb_node;
	काष्ठा rb_node *parent = शून्य;

	node = callchain_cursor_current(cursor);
	अगर (!node)
		वापस -1;

	/* lookup in children */
	जबतक (*p) अणु
		क्रमागत match_result ret;

		parent = *p;
		rnode = rb_entry(parent, काष्ठा callchain_node, rb_node_in);

		/* If at least first entry matches, rely to children */
		ret = append_chain(rnode, cursor, period);
		अगर (ret == MATCH_EQ)
			जाओ inc_children_hit;
		अगर (ret == MATCH_ERROR)
			वापस -1;

		अगर (ret == MATCH_LT)
			p = &parent->rb_left;
		अन्यथा
			p = &parent->rb_right;
	पूर्ण
	/* nothing in children, add to the current node */
	rnode = add_child(root, cursor, period);
	अगर (rnode == शून्य)
		वापस -1;

	rb_link_node(&rnode->rb_node_in, parent, p);
	rb_insert_color(&rnode->rb_node_in, &root->rb_root_in);

inc_children_hit:
	root->children_hit += period;
	root->children_count++;
	वापस 0;
पूर्ण

अटल क्रमागत match_result
append_chain(काष्ठा callchain_node *root,
	     काष्ठा callchain_cursor *cursor,
	     u64 period)
अणु
	काष्ठा callchain_list *cnode;
	u64 start = cursor->pos;
	bool found = false;
	u64 matches;
	क्रमागत match_result cmp = MATCH_ERROR;

	/*
	 * Lookup in the current node
	 * If we have a symbol, then compare the start to match
	 * anywhere inside a function, unless function
	 * mode is disabled.
	 */
	list_क्रम_each_entry(cnode, &root->val, list) अणु
		काष्ठा callchain_cursor_node *node;

		node = callchain_cursor_current(cursor);
		अगर (!node)
			अवरोध;

		cmp = match_chain(node, cnode);
		अगर (cmp != MATCH_EQ)
			अवरोध;

		found = true;

		callchain_cursor_advance(cursor);
	पूर्ण

	/* matches not, relay no the parent */
	अगर (!found) अणु
		WARN_ONCE(cmp == MATCH_ERROR, "Chain comparison error\n");
		वापस cmp;
	पूर्ण

	matches = cursor->pos - start;

	/* we match only a part of the node. Split it and add the new chain */
	अगर (matches < root->val_nr) अणु
		अगर (split_add_child(root, cursor, cnode, start, matches,
				    period) < 0)
			वापस MATCH_ERROR;

		वापस MATCH_EQ;
	पूर्ण

	/* we match 100% of the path, increment the hit */
	अगर (matches == root->val_nr && cursor->pos == cursor->nr) अणु
		root->hit += period;
		root->count++;
		वापस MATCH_EQ;
	पूर्ण

	/* We match the node and still have a part reमुख्यing */
	अगर (append_chain_children(root, cursor, period) < 0)
		वापस MATCH_ERROR;

	वापस MATCH_EQ;
पूर्ण

पूर्णांक callchain_append(काष्ठा callchain_root *root,
		     काष्ठा callchain_cursor *cursor,
		     u64 period)
अणु
	अगर (!cursor->nr)
		वापस 0;

	callchain_cursor_commit(cursor);

	अगर (append_chain_children(&root->node, cursor, period) < 0)
		वापस -1;

	अगर (cursor->nr > root->max_depth)
		root->max_depth = cursor->nr;

	वापस 0;
पूर्ण

अटल पूर्णांक
merge_chain_branch(काष्ठा callchain_cursor *cursor,
		   काष्ठा callchain_node *dst, काष्ठा callchain_node *src)
अणु
	काष्ठा callchain_cursor_node **old_last = cursor->last;
	काष्ठा callchain_node *child;
	काष्ठा callchain_list *list, *next_list;
	काष्ठा rb_node *n;
	पूर्णांक old_pos = cursor->nr;
	पूर्णांक err = 0;

	list_क्रम_each_entry_safe(list, next_list, &src->val, list) अणु
		callchain_cursor_append(cursor, list->ip, &list->ms,
					false, शून्य, 0, 0, 0, list->srcline);
		list_del_init(&list->list);
		map__zput(list->ms.map);
		मुक्त(list);
	पूर्ण

	अगर (src->hit) अणु
		callchain_cursor_commit(cursor);
		अगर (append_chain_children(dst, cursor, src->hit) < 0)
			वापस -1;
	पूर्ण

	n = rb_first(&src->rb_root_in);
	जबतक (n) अणु
		child = container_of(n, काष्ठा callchain_node, rb_node_in);
		n = rb_next(n);
		rb_erase(&child->rb_node_in, &src->rb_root_in);

		err = merge_chain_branch(cursor, dst, child);
		अगर (err)
			अवरोध;

		मुक्त(child);
	पूर्ण

	cursor->nr = old_pos;
	cursor->last = old_last;

	वापस err;
पूर्ण

पूर्णांक callchain_merge(काष्ठा callchain_cursor *cursor,
		    काष्ठा callchain_root *dst, काष्ठा callchain_root *src)
अणु
	वापस merge_chain_branch(cursor, &dst->node, &src->node);
पूर्ण

पूर्णांक callchain_cursor_append(काष्ठा callchain_cursor *cursor,
			    u64 ip, काष्ठा map_symbol *ms,
			    bool branch, काष्ठा branch_flags *flags,
			    पूर्णांक nr_loop_iter, u64 iter_cycles, u64 branch_from,
			    स्थिर अक्षर *srcline)
अणु
	काष्ठा callchain_cursor_node *node = *cursor->last;

	अगर (!node) अणु
		node = सुस्मृति(1, माप(*node));
		अगर (!node)
			वापस -ENOMEM;

		*cursor->last = node;
	पूर्ण

	node->ip = ip;
	map__zput(node->ms.map);
	node->ms = *ms;
	map__get(node->ms.map);
	node->branch = branch;
	node->nr_loop_iter = nr_loop_iter;
	node->iter_cycles = iter_cycles;
	node->srcline = srcline;

	अगर (flags)
		स_नकल(&node->branch_flags, flags,
			माप(काष्ठा branch_flags));

	node->branch_from = branch_from;
	cursor->nr++;

	cursor->last = &node->next;

	वापस 0;
पूर्ण

पूर्णांक sample__resolve_callchain(काष्ठा perf_sample *sample,
			      काष्ठा callchain_cursor *cursor, काष्ठा symbol **parent,
			      काष्ठा evsel *evsel, काष्ठा addr_location *al,
			      पूर्णांक max_stack)
अणु
	अगर (sample->callchain == शून्य && !symbol_conf.show_branchflag_count)
		वापस 0;

	अगर (symbol_conf.use_callchain || symbol_conf.cumulate_callchain ||
	    perf_hpp_list.parent || symbol_conf.show_branchflag_count) अणु
		वापस thपढ़ो__resolve_callchain(al->thपढ़ो, cursor, evsel, sample,
						 parent, al, max_stack);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक hist_entry__append_callchain(काष्ठा hist_entry *he, काष्ठा perf_sample *sample)
अणु
	अगर ((!symbol_conf.use_callchain || sample->callchain == शून्य) &&
		!symbol_conf.show_branchflag_count)
		वापस 0;
	वापस callchain_append(he->callchain, &callchain_cursor, sample->period);
पूर्ण

पूर्णांक fill_callchain_info(काष्ठा addr_location *al, काष्ठा callchain_cursor_node *node,
			bool hide_unresolved)
अणु
	al->maps = node->ms.maps;
	al->map = node->ms.map;
	al->sym = node->ms.sym;
	al->srcline = node->srcline;
	al->addr = node->ip;

	अगर (al->sym == शून्य) अणु
		अगर (hide_unresolved)
			वापस 0;
		अगर (al->map == शून्य)
			जाओ out;
	पूर्ण

	अगर (al->maps == &al->maps->machine->kmaps) अणु
		अगर (machine__is_host(al->maps->machine)) अणु
			al->cpumode = PERF_RECORD_MISC_KERNEL;
			al->level = 'k';
		पूर्ण अन्यथा अणु
			al->cpumode = PERF_RECORD_MISC_GUEST_KERNEL;
			al->level = 'g';
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (machine__is_host(al->maps->machine)) अणु
			al->cpumode = PERF_RECORD_MISC_USER;
			al->level = '.';
		पूर्ण अन्यथा अगर (perf_guest) अणु
			al->cpumode = PERF_RECORD_MISC_GUEST_USER;
			al->level = 'u';
		पूर्ण अन्यथा अणु
			al->cpumode = PERF_RECORD_MISC_HYPERVISOR;
			al->level = 'H';
		पूर्ण
	पूर्ण

out:
	वापस 1;
पूर्ण

अक्षर *callchain_list__sym_name(काष्ठा callchain_list *cl,
			       अक्षर *bf, माप_प्रकार bfsize, bool show_dso)
अणु
	bool show_addr = callchain_param.key == CCKEY_ADDRESS;
	bool show_srcline = show_addr || callchain_param.key == CCKEY_SRCLINE;
	पूर्णांक prपूर्णांकed;

	अगर (cl->ms.sym) अणु
		स्थिर अक्षर *अंतरभूतd = cl->ms.sym->अंतरभूतd ? " (inlined)" : "";

		अगर (show_srcline && cl->srcline)
			prपूर्णांकed = scnम_लिखो(bf, bfsize, "%s %s%s",
					    cl->ms.sym->name, cl->srcline,
					    अंतरभूतd);
		अन्यथा
			prपूर्णांकed = scnम_लिखो(bf, bfsize, "%s%s",
					    cl->ms.sym->name, अंतरभूतd);
	पूर्ण अन्यथा
		prपूर्णांकed = scnम_लिखो(bf, bfsize, "%#" PRIx64, cl->ip);

	अगर (show_dso)
		scnम_लिखो(bf + prपूर्णांकed, bfsize - prपूर्णांकed, " %s",
			  cl->ms.map ?
			  cl->ms.map->dso->लघु_name :
			  "unknown");

	वापस bf;
पूर्ण

अक्षर *callchain_node__scnम_लिखो_value(काष्ठा callchain_node *node,
				      अक्षर *bf, माप_प्रकार bfsize, u64 total)
अणु
	द्विगुन percent = 0.0;
	u64 period = callchain_cumul_hits(node);
	अचिन्हित count = callchain_cumul_counts(node);

	अगर (callchain_param.mode == CHAIN_FOLDED) अणु
		period = node->hit;
		count = node->count;
	पूर्ण

	चयन (callchain_param.value) अणु
	हाल CCVAL_PERIOD:
		scnम_लिखो(bf, bfsize, "%"PRIu64, period);
		अवरोध;
	हाल CCVAL_COUNT:
		scnम_लिखो(bf, bfsize, "%u", count);
		अवरोध;
	हाल CCVAL_PERCENT:
	शेष:
		अगर (total)
			percent = period * 100.0 / total;
		scnम_लिखो(bf, bfsize, "%.2f%%", percent);
		अवरोध;
	पूर्ण
	वापस bf;
पूर्ण

पूर्णांक callchain_node__ख_लिखो_value(काष्ठा callchain_node *node,
				 खाता *fp, u64 total)
अणु
	द्विगुन percent = 0.0;
	u64 period = callchain_cumul_hits(node);
	अचिन्हित count = callchain_cumul_counts(node);

	अगर (callchain_param.mode == CHAIN_FOLDED) अणु
		period = node->hit;
		count = node->count;
	पूर्ण

	चयन (callchain_param.value) अणु
	हाल CCVAL_PERIOD:
		वापस ख_लिखो(fp, "%"PRIu64, period);
	हाल CCVAL_COUNT:
		वापस ख_लिखो(fp, "%u", count);
	हाल CCVAL_PERCENT:
	शेष:
		अगर (total)
			percent = period * 100.0 / total;
		वापस percent_color_ख_लिखो(fp, "%.2f%%", percent);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम callchain_counts_value(काष्ठा callchain_node *node,
				   u64 *branch_count, u64 *predicted_count,
				   u64 *पात_count, u64 *cycles_count)
अणु
	काष्ठा callchain_list *clist;

	list_क्रम_each_entry(clist, &node->val, list) अणु
		अगर (branch_count)
			*branch_count += clist->branch_count;

		अगर (predicted_count)
			*predicted_count += clist->predicted_count;

		अगर (पात_count)
			*पात_count += clist->पात_count;

		अगर (cycles_count)
			*cycles_count += clist->cycles_count;
	पूर्ण
पूर्ण

अटल पूर्णांक callchain_node_branch_counts_cumul(काष्ठा callchain_node *node,
					      u64 *branch_count,
					      u64 *predicted_count,
					      u64 *पात_count,
					      u64 *cycles_count)
अणु
	काष्ठा callchain_node *child;
	काष्ठा rb_node *n;

	n = rb_first(&node->rb_root_in);
	जबतक (n) अणु
		child = rb_entry(n, काष्ठा callchain_node, rb_node_in);
		n = rb_next(n);

		callchain_node_branch_counts_cumul(child, branch_count,
						   predicted_count,
						   पात_count,
						   cycles_count);

		callchain_counts_value(child, branch_count,
				       predicted_count, पात_count,
				       cycles_count);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक callchain_branch_counts(काष्ठा callchain_root *root,
			    u64 *branch_count, u64 *predicted_count,
			    u64 *पात_count, u64 *cycles_count)
अणु
	अगर (branch_count)
		*branch_count = 0;

	अगर (predicted_count)
		*predicted_count = 0;

	अगर (पात_count)
		*पात_count = 0;

	अगर (cycles_count)
		*cycles_count = 0;

	वापस callchain_node_branch_counts_cumul(&root->node,
						  branch_count,
						  predicted_count,
						  पात_count,
						  cycles_count);
पूर्ण

अटल पूर्णांक count_pri64_म_लिखो(पूर्णांक idx, स्थिर अक्षर *str, u64 value, अक्षर *bf, पूर्णांक bfsize)
अणु
	पूर्णांक prपूर्णांकed;

	prपूर्णांकed = scnम_लिखो(bf, bfsize, "%s%s:%" PRId64 "", (idx) ? " " : " (", str, value);

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक count_भग्न_म_लिखो(पूर्णांक idx, स्थिर अक्षर *str, भग्न value,
			      अक्षर *bf, पूर्णांक bfsize, भग्न threshold)
अणु
	पूर्णांक prपूर्णांकed;

	अगर (threshold != 0.0 && value < threshold)
		वापस 0;

	prपूर्णांकed = scnम_लिखो(bf, bfsize, "%s%s:%.1f%%", (idx) ? " " : " (", str, value);

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक branch_to_str(अक्षर *bf, पूर्णांक bfsize,
			 u64 branch_count, u64 predicted_count,
			 u64 पात_count,
			 काष्ठा branch_type_stat *brtype_stat)
अणु
	पूर्णांक prपूर्णांकed, i = 0;

	prपूर्णांकed = branch_type_str(brtype_stat, bf, bfsize);
	अगर (prपूर्णांकed)
		i++;

	अगर (predicted_count < branch_count) अणु
		prपूर्णांकed += count_भग्न_म_लिखो(i++, "predicted",
				predicted_count * 100.0 / branch_count,
				bf + prपूर्णांकed, bfsize - prपूर्णांकed, 0.0);
	पूर्ण

	अगर (पात_count) अणु
		prपूर्णांकed += count_भग्न_म_लिखो(i++, "abort",
				पात_count * 100.0 / branch_count,
				bf + prपूर्णांकed, bfsize - prपूर्णांकed, 0.1);
	पूर्ण

	अगर (i)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, bfsize - prपूर्णांकed, ")");

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक branch_from_str(अक्षर *bf, पूर्णांक bfsize,
			   u64 branch_count,
			   u64 cycles_count, u64 iter_count,
			   u64 iter_cycles, u64 from_count)
अणु
	पूर्णांक prपूर्णांकed = 0, i = 0;
	u64 cycles, v = 0;

	cycles = cycles_count / branch_count;
	अगर (cycles) अणु
		prपूर्णांकed += count_pri64_म_लिखो(i++, "cycles",
				cycles,
				bf + prपूर्णांकed, bfsize - prपूर्णांकed);
	पूर्ण

	अगर (iter_count && from_count) अणु
		v = iter_count / from_count;
		अगर (v) अणु
			prपूर्णांकed += count_pri64_म_लिखो(i++, "iter",
					v, bf + prपूर्णांकed, bfsize - prपूर्णांकed);

			prपूर्णांकed += count_pri64_म_लिखो(i++, "avg_cycles",
					iter_cycles / iter_count,
					bf + prपूर्णांकed, bfsize - prपूर्णांकed);
		पूर्ण
	पूर्ण

	अगर (i)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, bfsize - prपूर्णांकed, ")");

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक counts_str_build(अक्षर *bf, पूर्णांक bfsize,
			     u64 branch_count, u64 predicted_count,
			     u64 पात_count, u64 cycles_count,
			     u64 iter_count, u64 iter_cycles,
			     u64 from_count,
			     काष्ठा branch_type_stat *brtype_stat)
अणु
	पूर्णांक prपूर्णांकed;

	अगर (branch_count == 0)
		वापस scnम_लिखो(bf, bfsize, " (calltrace)");

	अगर (brtype_stat->branch_to) अणु
		prपूर्णांकed = branch_to_str(bf, bfsize, branch_count,
				predicted_count, पात_count, brtype_stat);
	पूर्ण अन्यथा अणु
		prपूर्णांकed = branch_from_str(bf, bfsize, branch_count,
				cycles_count, iter_count, iter_cycles,
				from_count);
	पूर्ण

	अगर (!prपूर्णांकed)
		bf[0] = 0;

	वापस prपूर्णांकed;
पूर्ण

अटल पूर्णांक callchain_counts_म_लिखो(खाता *fp, अक्षर *bf, पूर्णांक bfsize,
				   u64 branch_count, u64 predicted_count,
				   u64 पात_count, u64 cycles_count,
				   u64 iter_count, u64 iter_cycles,
				   u64 from_count,
				   काष्ठा branch_type_stat *brtype_stat)
अणु
	अक्षर str[256];

	counts_str_build(str, माप(str), branch_count,
			 predicted_count, पात_count, cycles_count,
			 iter_count, iter_cycles, from_count, brtype_stat);

	अगर (fp)
		वापस ख_लिखो(fp, "%s", str);

	वापस scnम_लिखो(bf, bfsize, "%s", str);
पूर्ण

पूर्णांक callchain_list_counts__म_लिखो_value(काष्ठा callchain_list *clist,
					खाता *fp, अक्षर *bf, पूर्णांक bfsize)
अणु
	u64 branch_count, predicted_count;
	u64 पात_count, cycles_count;
	u64 iter_count, iter_cycles;
	u64 from_count;

	branch_count = clist->branch_count;
	predicted_count = clist->predicted_count;
	पात_count = clist->पात_count;
	cycles_count = clist->cycles_count;
	iter_count = clist->iter_count;
	iter_cycles = clist->iter_cycles;
	from_count = clist->from_count;

	वापस callchain_counts_म_लिखो(fp, bf, bfsize, branch_count,
				       predicted_count, पात_count,
				       cycles_count, iter_count, iter_cycles,
				       from_count, &clist->brtype_stat);
पूर्ण

अटल व्योम मुक्त_callchain_node(काष्ठा callchain_node *node)
अणु
	काष्ठा callchain_list *list, *पंचांगp;
	काष्ठा callchain_node *child;
	काष्ठा rb_node *n;

	list_क्रम_each_entry_safe(list, पंचांगp, &node->parent_val, list) अणु
		list_del_init(&list->list);
		map__zput(list->ms.map);
		मुक्त(list);
	पूर्ण

	list_क्रम_each_entry_safe(list, पंचांगp, &node->val, list) अणु
		list_del_init(&list->list);
		map__zput(list->ms.map);
		मुक्त(list);
	पूर्ण

	n = rb_first(&node->rb_root_in);
	जबतक (n) अणु
		child = container_of(n, काष्ठा callchain_node, rb_node_in);
		n = rb_next(n);
		rb_erase(&child->rb_node_in, &node->rb_root_in);

		मुक्त_callchain_node(child);
		मुक्त(child);
	पूर्ण
पूर्ण

व्योम मुक्त_callchain(काष्ठा callchain_root *root)
अणु
	अगर (!symbol_conf.use_callchain)
		वापस;

	मुक्त_callchain_node(&root->node);
पूर्ण

अटल u64 decay_callchain_node(काष्ठा callchain_node *node)
अणु
	काष्ठा callchain_node *child;
	काष्ठा rb_node *n;
	u64 child_hits = 0;

	n = rb_first(&node->rb_root_in);
	जबतक (n) अणु
		child = container_of(n, काष्ठा callchain_node, rb_node_in);

		child_hits += decay_callchain_node(child);
		n = rb_next(n);
	पूर्ण

	node->hit = (node->hit * 7) / 8;
	node->children_hit = child_hits;

	वापस node->hit;
पूर्ण

व्योम decay_callchain(काष्ठा callchain_root *root)
अणु
	अगर (!symbol_conf.use_callchain)
		वापस;

	decay_callchain_node(&root->node);
पूर्ण

पूर्णांक callchain_node__make_parent_list(काष्ठा callchain_node *node)
अणु
	काष्ठा callchain_node *parent = node->parent;
	काष्ठा callchain_list *chain, *new;
	LIST_HEAD(head);

	जबतक (parent) अणु
		list_क्रम_each_entry_reverse(chain, &parent->val, list) अणु
			new = दो_स्मृति(माप(*new));
			अगर (new == शून्य)
				जाओ out;
			*new = *chain;
			new->has_children = false;
			map__get(new->ms.map);
			list_add_tail(&new->list, &head);
		पूर्ण
		parent = parent->parent;
	पूर्ण

	list_क्रम_each_entry_safe_reverse(chain, new, &head, list)
		list_move_tail(&chain->list, &node->parent_val);

	अगर (!list_empty(&node->parent_val)) अणु
		chain = list_first_entry(&node->parent_val, काष्ठा callchain_list, list);
		chain->has_children = rb_prev(&node->rb_node) || rb_next(&node->rb_node);

		chain = list_first_entry(&node->val, काष्ठा callchain_list, list);
		chain->has_children = false;
	पूर्ण
	वापस 0;

out:
	list_क्रम_each_entry_safe(chain, new, &head, list) अणु
		list_del_init(&chain->list);
		map__zput(chain->ms.map);
		मुक्त(chain);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

पूर्णांक callchain_cursor__copy(काष्ठा callchain_cursor *dst,
			   काष्ठा callchain_cursor *src)
अणु
	पूर्णांक rc = 0;

	callchain_cursor_reset(dst);
	callchain_cursor_commit(src);

	जबतक (true) अणु
		काष्ठा callchain_cursor_node *node;

		node = callchain_cursor_current(src);
		अगर (node == शून्य)
			अवरोध;

		rc = callchain_cursor_append(dst, node->ip, &node->ms,
					     node->branch, &node->branch_flags,
					     node->nr_loop_iter,
					     node->iter_cycles,
					     node->branch_from, node->srcline);
		अगर (rc)
			अवरोध;

		callchain_cursor_advance(src);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * Initialize a cursor beक्रमe adding entries inside, but keep
 * the previously allocated entries as a cache.
 */
व्योम callchain_cursor_reset(काष्ठा callchain_cursor *cursor)
अणु
	काष्ठा callchain_cursor_node *node;

	cursor->nr = 0;
	cursor->last = &cursor->first;

	क्रम (node = cursor->first; node != शून्य; node = node->next)
		map__zput(node->ms.map);
पूर्ण

व्योम callchain_param_setup(u64 sample_type)
अणु
	अगर (symbol_conf.use_callchain || symbol_conf.cumulate_callchain) अणु
		अगर ((sample_type & PERF_SAMPLE_REGS_USER) &&
		    (sample_type & PERF_SAMPLE_STACK_USER)) अणु
			callchain_param.record_mode = CALLCHAIN_DWARF;
			dwarf_callchain_users = true;
		पूर्ण अन्यथा अगर (sample_type & PERF_SAMPLE_BRANCH_STACK)
			callchain_param.record_mode = CALLCHAIN_LBR;
		अन्यथा
			callchain_param.record_mode = CALLCHAIN_FP;
	पूर्ण
पूर्ण

अटल bool chain_match(काष्ठा callchain_list *base_chain,
			काष्ठा callchain_list *pair_chain)
अणु
	क्रमागत match_result match;

	match = match_chain_strings(base_chain->srcline,
				    pair_chain->srcline);
	अगर (match != MATCH_ERROR)
		वापस match == MATCH_EQ;

	match = match_chain_dso_addresses(base_chain->ms.map,
					  base_chain->ip,
					  pair_chain->ms.map,
					  pair_chain->ip);

	वापस match == MATCH_EQ;
पूर्ण

bool callchain_cnode_matched(काष्ठा callchain_node *base_cnode,
			     काष्ठा callchain_node *pair_cnode)
अणु
	काष्ठा callchain_list *base_chain, *pair_chain;
	bool match = false;

	pair_chain = list_first_entry(&pair_cnode->val,
				      काष्ठा callchain_list,
				      list);

	list_क्रम_each_entry(base_chain, &base_cnode->val, list) अणु
		अगर (&pair_chain->list == &pair_cnode->val)
			वापस false;

		अगर (!base_chain->srcline || !pair_chain->srcline) अणु
			pair_chain = list_next_entry(pair_chain, list);
			जारी;
		पूर्ण

		match = chain_match(base_chain, pair_chain);
		अगर (!match)
			वापस false;

		pair_chain = list_next_entry(pair_chain, list);
	पूर्ण

	/*
	 * Say chain1 is ABC, chain2 is ABCD, we consider they are
	 * not fully matched.
	 */
	अगर (pair_chain && (&pair_chain->list != &pair_cnode->val))
		वापस false;

	वापस match;
पूर्ण

अटल u64 count_callchain_hits(काष्ठा hist_entry *he)
अणु
	काष्ठा rb_root *root = &he->sorted_chain;
	काष्ठा rb_node *rb_node = rb_first(root);
	काष्ठा callchain_node *node;
	u64 chain_hits = 0;

	जबतक (rb_node) अणु
		node = rb_entry(rb_node, काष्ठा callchain_node, rb_node);
		chain_hits += node->hit;
		rb_node = rb_next(rb_node);
	पूर्ण

	वापस chain_hits;
पूर्ण

u64 callchain_total_hits(काष्ठा hists *hists)
अणु
	काष्ठा rb_node *next = rb_first_cached(&hists->entries);
	u64 chain_hits = 0;

	जबतक (next) अणु
		काष्ठा hist_entry *he = rb_entry(next, काष्ठा hist_entry,
						 rb_node);

		chain_hits += count_callchain_hits(he);
		next = rb_next(&he->rb_node);
	पूर्ण

	वापस chain_hits;
पूर्ण

s64 callchain_avg_cycles(काष्ठा callchain_node *cnode)
अणु
	काष्ठा callchain_list *chain;
	s64 cycles = 0;

	list_क्रम_each_entry(chain, &cnode->val, list) अणु
		अगर (chain->srcline && chain->branch_count)
			cycles += chain->cycles_count / chain->branch_count;
	पूर्ण

	वापस cycles;
पूर्ण
