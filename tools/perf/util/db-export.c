<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * db-export.c: Support क्रम exporting data suitable क्रम import to a database
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>

#समावेश "dso.h"
#समावेश "evsel.h"
#समावेश "machine.h"
#समावेश "thread.h"
#समावेश "comm.h"
#समावेश "symbol.h"
#समावेश "map.h"
#समावेश "event.h"
#समावेश "thread-stack.h"
#समावेश "callchain.h"
#समावेश "call-path.h"
#समावेश "db-export.h"
#समावेश <linux/zभाग.स>

पूर्णांक db_export__init(काष्ठा db_export *dbe)
अणु
	स_रखो(dbe, 0, माप(काष्ठा db_export));
	वापस 0;
पूर्ण

व्योम db_export__निकास(काष्ठा db_export *dbe)
अणु
	call_वापस_processor__मुक्त(dbe->crp);
	dbe->crp = शून्य;
पूर्ण

पूर्णांक db_export__evsel(काष्ठा db_export *dbe, काष्ठा evsel *evsel)
अणु
	अगर (evsel->db_id)
		वापस 0;

	evsel->db_id = ++dbe->evsel_last_db_id;

	अगर (dbe->export_evsel)
		वापस dbe->export_evsel(dbe, evsel);

	वापस 0;
पूर्ण

पूर्णांक db_export__machine(काष्ठा db_export *dbe, काष्ठा machine *machine)
अणु
	अगर (machine->db_id)
		वापस 0;

	machine->db_id = ++dbe->machine_last_db_id;

	अगर (dbe->export_machine)
		वापस dbe->export_machine(dbe, machine);

	वापस 0;
पूर्ण

पूर्णांक db_export__thपढ़ो(काष्ठा db_export *dbe, काष्ठा thपढ़ो *thपढ़ो,
		      काष्ठा machine *machine, काष्ठा thपढ़ो *मुख्य_thपढ़ो)
अणु
	u64 मुख्य_thपढ़ो_db_id = 0;

	अगर (thपढ़ो->db_id)
		वापस 0;

	thपढ़ो->db_id = ++dbe->thपढ़ो_last_db_id;

	अगर (मुख्य_thपढ़ो)
		मुख्य_thपढ़ो_db_id = मुख्य_thपढ़ो->db_id;

	अगर (dbe->export_thपढ़ो)
		वापस dbe->export_thपढ़ो(dbe, thपढ़ो, मुख्य_thपढ़ो_db_id,
					  machine);

	वापस 0;
पूर्ण

अटल पूर्णांक __db_export__comm(काष्ठा db_export *dbe, काष्ठा comm *comm,
			     काष्ठा thपढ़ो *thपढ़ो)
अणु
	comm->db_id = ++dbe->comm_last_db_id;

	अगर (dbe->export_comm)
		वापस dbe->export_comm(dbe, comm, thपढ़ो);

	वापस 0;
पूर्ण

पूर्णांक db_export__comm(काष्ठा db_export *dbe, काष्ठा comm *comm,
		    काष्ठा thपढ़ो *thपढ़ो)
अणु
	अगर (comm->db_id)
		वापस 0;

	वापस __db_export__comm(dbe, comm, thपढ़ो);
पूर्ण

/*
 * Export the "exec" comm. The "exec" comm is the program / application command
 * name at the समय it first executes. It is used to group thपढ़ोs क्रम the same
 * program. Note that the मुख्य thपढ़ो pid (or thपढ़ो group id tgid) cannot be
 * used because it करोes not change when a new program is exec'ed.
 */
पूर्णांक db_export__exec_comm(काष्ठा db_export *dbe, काष्ठा comm *comm,
			 काष्ठा thपढ़ो *मुख्य_thपढ़ो)
अणु
	पूर्णांक err;

	अगर (comm->db_id)
		वापस 0;

	err = __db_export__comm(dbe, comm, मुख्य_thपढ़ो);
	अगर (err)
		वापस err;

	/*
	 * Record the मुख्य thपढ़ो क्रम this comm. Note that the मुख्य thपढ़ो can
	 * have many "exec" comms because there will be a new one every समय it
	 * exec's. An "exec" comm however will only ever have 1 मुख्य thपढ़ो.
	 * That is dअगरferent to any other thपढ़ोs क्रम that same program because
	 * exec() will effectively समाप्त them, so the relationship between the
	 * "exec" comm and non-मुख्य thपढ़ोs is 1-to-1. That is why
	 * db_export__comm_thपढ़ो() is called here क्रम the मुख्य thपढ़ो, but it
	 * is called क्रम non-मुख्य thपढ़ोs when they are exported.
	 */
	वापस db_export__comm_thपढ़ो(dbe, comm, मुख्य_thपढ़ो);
पूर्ण

पूर्णांक db_export__comm_thपढ़ो(काष्ठा db_export *dbe, काष्ठा comm *comm,
			   काष्ठा thपढ़ो *thपढ़ो)
अणु
	u64 db_id;

	db_id = ++dbe->comm_thपढ़ो_last_db_id;

	अगर (dbe->export_comm_thपढ़ो)
		वापस dbe->export_comm_thपढ़ो(dbe, db_id, comm, thपढ़ो);

	वापस 0;
पूर्ण

पूर्णांक db_export__dso(काष्ठा db_export *dbe, काष्ठा dso *dso,
		   काष्ठा machine *machine)
अणु
	अगर (dso->db_id)
		वापस 0;

	dso->db_id = ++dbe->dso_last_db_id;

	अगर (dbe->export_dso)
		वापस dbe->export_dso(dbe, dso, machine);

	वापस 0;
पूर्ण

पूर्णांक db_export__symbol(काष्ठा db_export *dbe, काष्ठा symbol *sym,
		      काष्ठा dso *dso)
अणु
	u64 *sym_db_id = symbol__priv(sym);

	अगर (*sym_db_id)
		वापस 0;

	*sym_db_id = ++dbe->symbol_last_db_id;

	अगर (dbe->export_symbol)
		वापस dbe->export_symbol(dbe, sym, dso);

	वापस 0;
पूर्ण

अटल पूर्णांक db_ids_from_al(काष्ठा db_export *dbe, काष्ठा addr_location *al,
			  u64 *dso_db_id, u64 *sym_db_id, u64 *offset)
अणु
	पूर्णांक err;

	अगर (al->map) अणु
		काष्ठा dso *dso = al->map->dso;

		err = db_export__dso(dbe, dso, al->maps->machine);
		अगर (err)
			वापस err;
		*dso_db_id = dso->db_id;

		अगर (!al->sym) अणु
			al->sym = symbol__new(al->addr, 0, 0, 0, "unknown");
			अगर (al->sym)
				dso__insert_symbol(dso, al->sym);
		पूर्ण

		अगर (al->sym) अणु
			u64 *db_id = symbol__priv(al->sym);

			err = db_export__symbol(dbe, al->sym, dso);
			अगर (err)
				वापस err;
			*sym_db_id = *db_id;
			*offset = al->addr - al->sym->start;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा call_path *call_path_from_sample(काष्ठा db_export *dbe,
					       काष्ठा machine *machine,
					       काष्ठा thपढ़ो *thपढ़ो,
					       काष्ठा perf_sample *sample,
					       काष्ठा evsel *evsel)
अणु
	u64 kernel_start = machine__kernel_start(machine);
	काष्ठा call_path *current = &dbe->cpr->call_path;
	क्रमागत chain_order saved_order = callchain_param.order;
	पूर्णांक err;

	अगर (!symbol_conf.use_callchain || !sample->callchain)
		वापस शून्य;

	/*
	 * Since the call path tree must be built starting with the root, we
	 * must use ORDER_CALL क्रम call chain resolution, in order to process
	 * the callchain starting with the root node and ending with the leaf.
	 */
	callchain_param.order = ORDER_CALLER;
	err = thपढ़ो__resolve_callchain(thपढ़ो, &callchain_cursor, evsel,
					sample, शून्य, शून्य, PERF_MAX_STACK_DEPTH);
	अगर (err) अणु
		callchain_param.order = saved_order;
		वापस शून्य;
	पूर्ण
	callchain_cursor_commit(&callchain_cursor);

	जबतक (1) अणु
		काष्ठा callchain_cursor_node *node;
		काष्ठा addr_location al;
		u64 dso_db_id = 0, sym_db_id = 0, offset = 0;

		स_रखो(&al, 0, माप(al));

		node = callchain_cursor_current(&callchain_cursor);
		अगर (!node)
			अवरोध;
		/*
		 * Handle export of symbol and dso क्रम this node by
		 * स्थिरructing an addr_location काष्ठा and then passing it to
		 * db_ids_from_al() to perक्रमm the export.
		 */
		al.sym = node->ms.sym;
		al.map = node->ms.map;
		al.maps = thपढ़ो->maps;
		al.addr = node->ip;

		अगर (al.map && !al.sym)
			al.sym = dso__find_symbol(al.map->dso, al.addr);

		db_ids_from_al(dbe, &al, &dso_db_id, &sym_db_id, &offset);

		/* add node to the call path tree अगर it करोesn't exist */
		current = call_path__findnew(dbe->cpr, current,
					     al.sym, node->ip,
					     kernel_start);

		callchain_cursor_advance(&callchain_cursor);
	पूर्ण

	/* Reset the callchain order to its prior value. */
	callchain_param.order = saved_order;

	अगर (current == &dbe->cpr->call_path) अणु
		/* Bail because the callchain was empty. */
		वापस शून्य;
	पूर्ण

	वापस current;
पूर्ण

पूर्णांक db_export__branch_type(काष्ठा db_export *dbe, u32 branch_type,
			   स्थिर अक्षर *name)
अणु
	अगर (dbe->export_branch_type)
		वापस dbe->export_branch_type(dbe, branch_type, name);

	वापस 0;
पूर्ण

अटल पूर्णांक db_export__thपढ़ोs(काष्ठा db_export *dbe, काष्ठा thपढ़ो *thपढ़ो,
			      काष्ठा thपढ़ो *मुख्य_thपढ़ो,
			      काष्ठा machine *machine, काष्ठा comm **comm_ptr)
अणु
	काष्ठा comm *comm = शून्य;
	काष्ठा comm *curr_comm;
	पूर्णांक err;

	अगर (मुख्य_thपढ़ो) अणु
		/*
		 * A thपढ़ो has a reference to the मुख्य thपढ़ो, so export the
		 * मुख्य thपढ़ो first.
		 */
		err = db_export__thपढ़ो(dbe, मुख्य_thपढ़ो, machine, मुख्य_thपढ़ो);
		अगर (err)
			वापस err;
		/*
		 * Export comm beक्रमe exporting the non-मुख्य thपढ़ो because
		 * db_export__comm_thपढ़ो() can be called further below.
		 */
		comm = machine__thपढ़ो_exec_comm(machine, मुख्य_thपढ़ो);
		अगर (comm) अणु
			err = db_export__exec_comm(dbe, comm, मुख्य_thपढ़ो);
			अगर (err)
				वापस err;
			*comm_ptr = comm;
		पूर्ण
	पूर्ण

	अगर (thपढ़ो != मुख्य_thपढ़ो) अणु
		/*
		 * For a non-मुख्य thपढ़ो, db_export__comm_thपढ़ो() must be
		 * called only अगर thपढ़ो has not previously been exported.
		 */
		bool export_comm_thपढ़ो = comm && !thपढ़ो->db_id;

		err = db_export__thपढ़ो(dbe, thपढ़ो, machine, मुख्य_thपढ़ो);
		अगर (err)
			वापस err;

		अगर (export_comm_thपढ़ो) अणु
			err = db_export__comm_thपढ़ो(dbe, comm, thपढ़ो);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	curr_comm = thपढ़ो__comm(thपढ़ो);
	अगर (curr_comm)
		वापस db_export__comm(dbe, curr_comm, thपढ़ो);

	वापस 0;
पूर्ण

पूर्णांक db_export__sample(काष्ठा db_export *dbe, जोड़ perf_event *event,
		      काष्ठा perf_sample *sample, काष्ठा evsel *evsel,
		      काष्ठा addr_location *al)
अणु
	काष्ठा thपढ़ो *thपढ़ो = al->thपढ़ो;
	काष्ठा export_sample es = अणु
		.event = event,
		.sample = sample,
		.evsel = evsel,
		.al = al,
	पूर्ण;
	काष्ठा thपढ़ो *मुख्य_thपढ़ो;
	काष्ठा comm *comm = शून्य;
	पूर्णांक err;

	err = db_export__evsel(dbe, evsel);
	अगर (err)
		वापस err;

	err = db_export__machine(dbe, al->maps->machine);
	अगर (err)
		वापस err;

	मुख्य_thपढ़ो = thपढ़ो__मुख्य_thपढ़ो(al->maps->machine, thपढ़ो);

	err = db_export__thपढ़ोs(dbe, thपढ़ो, मुख्य_thपढ़ो, al->maps->machine, &comm);
	अगर (err)
		जाओ out_put;

	अगर (comm)
		es.comm_db_id = comm->db_id;

	es.db_id = ++dbe->sample_last_db_id;

	err = db_ids_from_al(dbe, al, &es.dso_db_id, &es.sym_db_id, &es.offset);
	अगर (err)
		जाओ out_put;

	अगर (dbe->cpr) अणु
		काष्ठा call_path *cp = call_path_from_sample(dbe, al->maps->machine,
							     thपढ़ो, sample,
							     evsel);
		अगर (cp) अणु
			db_export__call_path(dbe, cp);
			es.call_path_id = cp->db_id;
		पूर्ण
	पूर्ण

	अगर ((evsel->core.attr.sample_type & PERF_SAMPLE_ADDR) &&
	    sample_addr_correlates_sym(&evsel->core.attr)) अणु
		काष्ठा addr_location addr_al;

		thपढ़ो__resolve(thपढ़ो, &addr_al, sample);
		err = db_ids_from_al(dbe, &addr_al, &es.addr_dso_db_id,
				     &es.addr_sym_db_id, &es.addr_offset);
		अगर (err)
			जाओ out_put;
		अगर (dbe->crp) अणु
			err = thपढ़ो_stack__process(thपढ़ो, comm, sample, al,
						    &addr_al, es.db_id,
						    dbe->crp);
			अगर (err)
				जाओ out_put;
		पूर्ण
	पूर्ण

	अगर (dbe->export_sample)
		err = dbe->export_sample(dbe, &es);

out_put:
	thपढ़ो__put(मुख्य_thपढ़ो);
	वापस err;
पूर्ण

अटल काष्ठा अणु
	u32 branch_type;
	स्थिर अक्षर *name;
पूर्ण branch_types[] = अणु
	अणु0, "no branch"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL, "call"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN, "return"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CONDITIONAL, "conditional jump"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH, "unconditional jump"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL | PERF_IP_FLAG_INTERRUPT,
	 "software interrupt"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN | PERF_IP_FLAG_INTERRUPT,
	 "return from interrupt"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL | PERF_IP_FLAG_SYSCALLRET,
	 "system call"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_RETURN | PERF_IP_FLAG_SYSCALLRET,
	 "return from system call"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_ASYNC, "asynchronous branch"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL | PERF_IP_FLAG_ASYNC |
	 PERF_IP_FLAG_INTERRUPT, "hardware interrupt"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_TX_ABORT, "transaction abort"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_TRACE_BEGIN, "trace begin"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_TRACE_END, "trace end"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL | PERF_IP_FLAG_VMENTRY, "vm entry"पूर्ण,
	अणुPERF_IP_FLAG_BRANCH | PERF_IP_FLAG_CALL | PERF_IP_FLAG_VMEXIT, "vm exit"पूर्ण,
	अणु0, शून्यपूर्ण
पूर्ण;

पूर्णांक db_export__branch_types(काष्ठा db_export *dbe)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; branch_types[i].name ; i++) अणु
		err = db_export__branch_type(dbe, branch_types[i].branch_type,
					     branch_types[i].name);
		अगर (err)
			अवरोध;
	पूर्ण

	/* Add trace begin / end variants */
	क्रम (i = 0; branch_types[i].name ; i++) अणु
		स्थिर अक्षर *name = branch_types[i].name;
		u32 type = branch_types[i].branch_type;
		अक्षर buf[64];

		अगर (type == PERF_IP_FLAG_BRANCH ||
		    (type & (PERF_IP_FLAG_TRACE_BEGIN | PERF_IP_FLAG_TRACE_END)))
			जारी;

		snम_लिखो(buf, माप(buf), "trace begin / %s", name);
		err = db_export__branch_type(dbe, type | PERF_IP_FLAG_TRACE_BEGIN, buf);
		अगर (err)
			अवरोध;

		snम_लिखो(buf, माप(buf), "%s / trace end", name);
		err = db_export__branch_type(dbe, type | PERF_IP_FLAG_TRACE_END, buf);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक db_export__call_path(काष्ठा db_export *dbe, काष्ठा call_path *cp)
अणु
	पूर्णांक err;

	अगर (cp->db_id)
		वापस 0;

	अगर (cp->parent) अणु
		err = db_export__call_path(dbe, cp->parent);
		अगर (err)
			वापस err;
	पूर्ण

	cp->db_id = ++dbe->call_path_last_db_id;

	अगर (dbe->export_call_path)
		वापस dbe->export_call_path(dbe, cp);

	वापस 0;
पूर्ण

पूर्णांक db_export__call_वापस(काष्ठा db_export *dbe, काष्ठा call_वापस *cr,
			   u64 *parent_db_id)
अणु
	पूर्णांक err;

	err = db_export__call_path(dbe, cr->cp);
	अगर (err)
		वापस err;

	अगर (!cr->db_id)
		cr->db_id = ++dbe->call_वापस_last_db_id;

	अगर (parent_db_id) अणु
		अगर (!*parent_db_id)
			*parent_db_id = ++dbe->call_वापस_last_db_id;
		cr->parent_db_id = *parent_db_id;
	पूर्ण

	अगर (dbe->export_call_वापस)
		वापस dbe->export_call_वापस(dbe, cr);

	वापस 0;
पूर्ण

अटल पूर्णांक db_export__pid_tid(काष्ठा db_export *dbe, काष्ठा machine *machine,
			      pid_t pid, pid_t tid, u64 *db_id,
			      काष्ठा comm **comm_ptr, bool *is_idle)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__find_thपढ़ो(machine, pid, tid);
	काष्ठा thपढ़ो *मुख्य_thपढ़ो;
	पूर्णांक err = 0;

	अगर (!thपढ़ो || !thपढ़ो->comm_set)
		जाओ out_put;

	*is_idle = !thपढ़ो->pid_ && !thपढ़ो->tid;

	मुख्य_thपढ़ो = thपढ़ो__मुख्य_thपढ़ो(machine, thपढ़ो);

	err = db_export__thपढ़ोs(dbe, thपढ़ो, मुख्य_thपढ़ो, machine, comm_ptr);

	*db_id = thपढ़ो->db_id;

	thपढ़ो__put(मुख्य_thपढ़ो);
out_put:
	thपढ़ो__put(thपढ़ो);

	वापस err;
पूर्ण

पूर्णांक db_export__चयन(काष्ठा db_export *dbe, जोड़ perf_event *event,
		      काष्ठा perf_sample *sample, काष्ठा machine *machine)
अणु
	bool out = event->header.misc & PERF_RECORD_MISC_SWITCH_OUT;
	bool out_preempt = out &&
		(event->header.misc & PERF_RECORD_MISC_SWITCH_OUT_PREEMPT);
	पूर्णांक flags = out | (out_preempt << 1);
	bool is_idle_a = false, is_idle_b = false;
	u64 th_a_id = 0, th_b_id = 0;
	u64 comm_out_id, comm_in_id;
	काष्ठा comm *comm_a = शून्य;
	काष्ठा comm *comm_b = शून्य;
	u64 th_out_id, th_in_id;
	u64 db_id;
	पूर्णांक err;

	err = db_export__machine(dbe, machine);
	अगर (err)
		वापस err;

	err = db_export__pid_tid(dbe, machine, sample->pid, sample->tid,
				 &th_a_id, &comm_a, &is_idle_a);
	अगर (err)
		वापस err;

	अगर (event->header.type == PERF_RECORD_SWITCH_CPU_WIDE) अणु
		pid_t pid = event->context_चयन.next_prev_pid;
		pid_t tid = event->context_चयन.next_prev_tid;

		err = db_export__pid_tid(dbe, machine, pid, tid, &th_b_id,
					 &comm_b, &is_idle_b);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Do not export अगर both thपढ़ोs are unknown (i.e. not being traced),
	 * or one is unknown and the other is the idle task.
	 */
	अगर ((!th_a_id || is_idle_a) && (!th_b_id || is_idle_b))
		वापस 0;

	db_id = ++dbe->context_चयन_last_db_id;

	अगर (out) अणु
		th_out_id   = th_a_id;
		th_in_id    = th_b_id;
		comm_out_id = comm_a ? comm_a->db_id : 0;
		comm_in_id  = comm_b ? comm_b->db_id : 0;
	पूर्ण अन्यथा अणु
		th_out_id   = th_b_id;
		th_in_id    = th_a_id;
		comm_out_id = comm_b ? comm_b->db_id : 0;
		comm_in_id  = comm_a ? comm_a->db_id : 0;
	पूर्ण

	अगर (dbe->export_context_चयन)
		वापस dbe->export_context_चयन(dbe, db_id, machine, sample,
						  th_out_id, comm_out_id,
						  th_in_id, comm_in_id, flags);
	वापस 0;
पूर्ण
