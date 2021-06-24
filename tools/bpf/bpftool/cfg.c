<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */

#समावेश <linux/list.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश "cfg.h"
#समावेश "main.h"
#समावेश "xlated_dumper.h"

काष्ठा cfg अणु
	काष्ठा list_head funcs;
	पूर्णांक func_num;
पूर्ण;

काष्ठा func_node अणु
	काष्ठा list_head l;
	काष्ठा list_head bbs;
	काष्ठा bpf_insn *start;
	काष्ठा bpf_insn *end;
	पूर्णांक idx;
	पूर्णांक bb_num;
पूर्ण;

काष्ठा bb_node अणु
	काष्ठा list_head l;
	काष्ठा list_head e_prevs;
	काष्ठा list_head e_succs;
	काष्ठा bpf_insn *head;
	काष्ठा bpf_insn *tail;
	पूर्णांक idx;
पूर्ण;

#घोषणा EDGE_FLAG_EMPTY		0x0
#घोषणा EDGE_FLAG_FALLTHROUGH	0x1
#घोषणा EDGE_FLAG_JUMP		0x2
काष्ठा edge_node अणु
	काष्ठा list_head l;
	काष्ठा bb_node *src;
	काष्ठा bb_node *dst;
	पूर्णांक flags;
पूर्ण;

#घोषणा ENTRY_BLOCK_INDEX	0
#घोषणा EXIT_BLOCK_INDEX	1
#घोषणा NUM_FIXED_BLOCKS	2
#घोषणा func_prev(func)		list_prev_entry(func, l)
#घोषणा func_next(func)		list_next_entry(func, l)
#घोषणा bb_prev(bb)		list_prev_entry(bb, l)
#घोषणा bb_next(bb)		list_next_entry(bb, l)
#घोषणा entry_bb(func)		func_first_bb(func)
#घोषणा निकास_bb(func)		func_last_bb(func)
#घोषणा cfg_first_func(cfg)	\
	list_first_entry(&cfg->funcs, काष्ठा func_node, l)
#घोषणा cfg_last_func(cfg)	\
	list_last_entry(&cfg->funcs, काष्ठा func_node, l)
#घोषणा func_first_bb(func)	\
	list_first_entry(&func->bbs, काष्ठा bb_node, l)
#घोषणा func_last_bb(func)	\
	list_last_entry(&func->bbs, काष्ठा bb_node, l)

अटल काष्ठा func_node *cfg_append_func(काष्ठा cfg *cfg, काष्ठा bpf_insn *insn)
अणु
	काष्ठा func_node *new_func, *func;

	list_क्रम_each_entry(func, &cfg->funcs, l) अणु
		अगर (func->start == insn)
			वापस func;
		अन्यथा अगर (func->start > insn)
			अवरोध;
	पूर्ण

	func = func_prev(func);
	new_func = सुस्मृति(1, माप(*new_func));
	अगर (!new_func) अणु
		p_err("OOM when allocating FUNC node");
		वापस शून्य;
	पूर्ण
	new_func->start = insn;
	new_func->idx = cfg->func_num;
	list_add(&new_func->l, &func->l);
	cfg->func_num++;

	वापस new_func;
पूर्ण

अटल काष्ठा bb_node *func_append_bb(काष्ठा func_node *func,
				      काष्ठा bpf_insn *insn)
अणु
	काष्ठा bb_node *new_bb, *bb;

	list_क्रम_each_entry(bb, &func->bbs, l) अणु
		अगर (bb->head == insn)
			वापस bb;
		अन्यथा अगर (bb->head > insn)
			अवरोध;
	पूर्ण

	bb = bb_prev(bb);
	new_bb = सुस्मृति(1, माप(*new_bb));
	अगर (!new_bb) अणु
		p_err("OOM when allocating BB node");
		वापस शून्य;
	पूर्ण
	new_bb->head = insn;
	INIT_LIST_HEAD(&new_bb->e_prevs);
	INIT_LIST_HEAD(&new_bb->e_succs);
	list_add(&new_bb->l, &bb->l);

	वापस new_bb;
पूर्ण

अटल काष्ठा bb_node *func_insert_dummy_bb(काष्ठा list_head *after)
अणु
	काष्ठा bb_node *bb;

	bb = सुस्मृति(1, माप(*bb));
	अगर (!bb) अणु
		p_err("OOM when allocating BB node");
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&bb->e_prevs);
	INIT_LIST_HEAD(&bb->e_succs);
	list_add(&bb->l, after);

	वापस bb;
पूर्ण

अटल bool cfg_partition_funcs(काष्ठा cfg *cfg, काष्ठा bpf_insn *cur,
				काष्ठा bpf_insn *end)
अणु
	काष्ठा func_node *func, *last_func;

	func = cfg_append_func(cfg, cur);
	अगर (!func)
		वापस true;

	क्रम (; cur < end; cur++) अणु
		अगर (cur->code != (BPF_JMP | BPF_CALL))
			जारी;
		अगर (cur->src_reg != BPF_PSEUDO_CALL)
			जारी;
		func = cfg_append_func(cfg, cur + cur->off + 1);
		अगर (!func)
			वापस true;
	पूर्ण

	last_func = cfg_last_func(cfg);
	last_func->end = end - 1;
	func = cfg_first_func(cfg);
	list_क्रम_each_entry_from(func, &last_func->l, l) अणु
		func->end = func_next(func)->start - 1;
	पूर्ण

	वापस false;
पूर्ण

अटल bool is_jmp_insn(__u8 code)
अणु
	वापस BPF_CLASS(code) == BPF_JMP || BPF_CLASS(code) == BPF_JMP32;
पूर्ण

अटल bool func_partition_bb_head(काष्ठा func_node *func)
अणु
	काष्ठा bpf_insn *cur, *end;
	काष्ठा bb_node *bb;

	cur = func->start;
	end = func->end;
	INIT_LIST_HEAD(&func->bbs);
	bb = func_append_bb(func, cur);
	अगर (!bb)
		वापस true;

	क्रम (; cur <= end; cur++) अणु
		अगर (is_jmp_insn(cur->code)) अणु
			__u8 opcode = BPF_OP(cur->code);

			अगर (opcode == BPF_EXIT || opcode == BPF_CALL)
				जारी;

			bb = func_append_bb(func, cur + cur->off + 1);
			अगर (!bb)
				वापस true;

			अगर (opcode != BPF_JA) अणु
				bb = func_append_bb(func, cur + 1);
				अगर (!bb)
					वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम func_partition_bb_tail(काष्ठा func_node *func)
अणु
	अचिन्हित पूर्णांक bb_idx = NUM_FIXED_BLOCKS;
	काष्ठा bb_node *bb, *last;

	last = func_last_bb(func);
	last->tail = func->end;
	bb = func_first_bb(func);
	list_क्रम_each_entry_from(bb, &last->l, l) अणु
		bb->tail = bb_next(bb)->head - 1;
		bb->idx = bb_idx++;
	पूर्ण

	last->idx = bb_idx++;
	func->bb_num = bb_idx;
पूर्ण

अटल bool func_add_special_bb(काष्ठा func_node *func)
अणु
	काष्ठा bb_node *bb;

	bb = func_insert_dummy_bb(&func->bbs);
	अगर (!bb)
		वापस true;
	bb->idx = ENTRY_BLOCK_INDEX;

	bb = func_insert_dummy_bb(&func_last_bb(func)->l);
	अगर (!bb)
		वापस true;
	bb->idx = EXIT_BLOCK_INDEX;

	वापस false;
पूर्ण

अटल bool func_partition_bb(काष्ठा func_node *func)
अणु
	अगर (func_partition_bb_head(func))
		वापस true;

	func_partition_bb_tail(func);

	वापस false;
पूर्ण

अटल काष्ठा bb_node *func_search_bb_with_head(काष्ठा func_node *func,
						काष्ठा bpf_insn *insn)
अणु
	काष्ठा bb_node *bb;

	list_क्रम_each_entry(bb, &func->bbs, l) अणु
		अगर (bb->head == insn)
			वापस bb;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा edge_node *new_edge(काष्ठा bb_node *src, काष्ठा bb_node *dst,
				  पूर्णांक flags)
अणु
	काष्ठा edge_node *e;

	e = सुस्मृति(1, माप(*e));
	अगर (!e) अणु
		p_err("OOM when allocating edge node");
		वापस शून्य;
	पूर्ण

	अगर (src)
		e->src = src;
	अगर (dst)
		e->dst = dst;

	e->flags |= flags;

	वापस e;
पूर्ण

अटल bool func_add_bb_edges(काष्ठा func_node *func)
अणु
	काष्ठा bpf_insn *insn;
	काष्ठा edge_node *e;
	काष्ठा bb_node *bb;

	bb = entry_bb(func);
	e = new_edge(bb, bb_next(bb), EDGE_FLAG_FALLTHROUGH);
	अगर (!e)
		वापस true;
	list_add_tail(&e->l, &bb->e_succs);

	bb = निकास_bb(func);
	e = new_edge(bb_prev(bb), bb, EDGE_FLAG_FALLTHROUGH);
	अगर (!e)
		वापस true;
	list_add_tail(&e->l, &bb->e_prevs);

	bb = entry_bb(func);
	bb = bb_next(bb);
	list_क्रम_each_entry_from(bb, &निकास_bb(func)->l, l) अणु
		e = new_edge(bb, शून्य, EDGE_FLAG_EMPTY);
		अगर (!e)
			वापस true;
		e->src = bb;

		insn = bb->tail;
		अगर (!is_jmp_insn(insn->code) ||
		    BPF_OP(insn->code) == BPF_EXIT) अणु
			e->dst = bb_next(bb);
			e->flags |= EDGE_FLAG_FALLTHROUGH;
			list_add_tail(&e->l, &bb->e_succs);
			जारी;
		पूर्ण अन्यथा अगर (BPF_OP(insn->code) == BPF_JA) अणु
			e->dst = func_search_bb_with_head(func,
							  insn + insn->off + 1);
			e->flags |= EDGE_FLAG_JUMP;
			list_add_tail(&e->l, &bb->e_succs);
			जारी;
		पूर्ण

		e->dst = bb_next(bb);
		e->flags |= EDGE_FLAG_FALLTHROUGH;
		list_add_tail(&e->l, &bb->e_succs);

		e = new_edge(bb, शून्य, EDGE_FLAG_JUMP);
		अगर (!e)
			वापस true;
		e->src = bb;
		e->dst = func_search_bb_with_head(func, insn + insn->off + 1);
		list_add_tail(&e->l, &bb->e_succs);
	पूर्ण

	वापस false;
पूर्ण

अटल bool cfg_build(काष्ठा cfg *cfg, काष्ठा bpf_insn *insn, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक cnt = len / माप(*insn);
	काष्ठा func_node *func;

	INIT_LIST_HEAD(&cfg->funcs);

	अगर (cfg_partition_funcs(cfg, insn, insn + cnt))
		वापस true;

	list_क्रम_each_entry(func, &cfg->funcs, l) अणु
		अगर (func_partition_bb(func) || func_add_special_bb(func))
			वापस true;

		अगर (func_add_bb_edges(func))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम cfg_destroy(काष्ठा cfg *cfg)
अणु
	काष्ठा func_node *func, *func2;

	list_क्रम_each_entry_safe(func, func2, &cfg->funcs, l) अणु
		काष्ठा bb_node *bb, *bb2;

		list_क्रम_each_entry_safe(bb, bb2, &func->bbs, l) अणु
			काष्ठा edge_node *e, *e2;

			list_क्रम_each_entry_safe(e, e2, &bb->e_prevs, l) अणु
				list_del(&e->l);
				मुक्त(e);
			पूर्ण

			list_क्रम_each_entry_safe(e, e2, &bb->e_succs, l) अणु
				list_del(&e->l);
				मुक्त(e);
			पूर्ण

			list_del(&bb->l);
			मुक्त(bb);
		पूर्ण

		list_del(&func->l);
		मुक्त(func);
	पूर्ण
पूर्ण

अटल व्योम draw_bb_node(काष्ठा func_node *func, काष्ठा bb_node *bb)
अणु
	स्थिर अक्षर *shape;

	अगर (bb->idx == ENTRY_BLOCK_INDEX || bb->idx == EXIT_BLOCK_INDEX)
		shape = "Mdiamond";
	अन्यथा
		shape = "record";

	म_लिखो("\tfn_%d_bb_%d [shape=%s,style=filled,label=\"",
	       func->idx, bb->idx, shape);

	अगर (bb->idx == ENTRY_BLOCK_INDEX) अणु
		म_लिखो("ENTRY");
	पूर्ण अन्यथा अगर (bb->idx == EXIT_BLOCK_INDEX) अणु
		म_लिखो("EXIT");
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक start_idx;
		काष्ठा dump_data dd = अणुपूर्ण;

		म_लिखो("{");
		kernel_syms_load(&dd);
		start_idx = bb->head - func->start;
		dump_xlated_क्रम_graph(&dd, bb->head, bb->tail, start_idx);
		kernel_syms_destroy(&dd);
		म_लिखो("}");
	पूर्ण

	म_लिखो("\"];\n\n");
पूर्ण

अटल व्योम draw_bb_succ_edges(काष्ठा func_node *func, काष्ठा bb_node *bb)
अणु
	स्थिर अक्षर *style = "\"solid,bold\"";
	स्थिर अक्षर *color = "black";
	पूर्णांक func_idx = func->idx;
	काष्ठा edge_node *e;
	पूर्णांक weight = 10;

	अगर (list_empty(&bb->e_succs))
		वापस;

	list_क्रम_each_entry(e, &bb->e_succs, l) अणु
		म_लिखो("\tfn_%d_bb_%d:s -> fn_%d_bb_%d:n [style=%s, color=%s, weight=%d, constraint=true",
		       func_idx, e->src->idx, func_idx, e->dst->idx,
		       style, color, weight);
		म_लिखो("];\n");
	पूर्ण
पूर्ण

अटल व्योम func_output_bb_def(काष्ठा func_node *func)
अणु
	काष्ठा bb_node *bb;

	list_क्रम_each_entry(bb, &func->bbs, l) अणु
		draw_bb_node(func, bb);
	पूर्ण
पूर्ण

अटल व्योम func_output_edges(काष्ठा func_node *func)
अणु
	पूर्णांक func_idx = func->idx;
	काष्ठा bb_node *bb;

	list_क्रम_each_entry(bb, &func->bbs, l) अणु
		draw_bb_succ_edges(func, bb);
	पूर्ण

	/* Add an invisible edge from ENTRY to EXIT, this is to
	 * improve the graph layout.
	 */
	म_लिखो("\tfn_%d_bb_%d:s -> fn_%d_bb_%d:n [style=\"invis\", constraint=true];\n",
	       func_idx, ENTRY_BLOCK_INDEX, func_idx, EXIT_BLOCK_INDEX);
पूर्ण

अटल व्योम cfg_dump(काष्ठा cfg *cfg)
अणु
	काष्ठा func_node *func;

	म_लिखो("digraph \"DOT graph for eBPF program\" {\n");
	list_क्रम_each_entry(func, &cfg->funcs, l) अणु
		म_लिखो("subgraph \"cluster_%d\" {\n\tstyle=\"dashed\";\n\tcolor=\"black\";\n\tlabel=\"func_%d ()\";\n",
		       func->idx, func->idx);
		func_output_bb_def(func);
		func_output_edges(func);
		म_लिखो("}\n");
	पूर्ण
	म_लिखो("}\n");
पूर्ण

व्योम dump_xlated_cfg(व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा bpf_insn *insn = buf;
	काष्ठा cfg cfg;

	स_रखो(&cfg, 0, माप(cfg));
	अगर (cfg_build(&cfg, insn, len))
		वापस;

	cfg_dump(&cfg);

	cfg_destroy(&cfg);
पूर्ण
