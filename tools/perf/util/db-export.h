<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * db-export.h: Support क्रम exporting data suitable क्रम import to a database
 * Copyright (c) 2014, Intel Corporation.
 */

#अगर_अघोषित __PERF_DB_EXPORT_H
#घोषणा __PERF_DB_EXPORT_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>

काष्ठा evsel;
काष्ठा machine;
काष्ठा thपढ़ो;
काष्ठा comm;
काष्ठा dso;
काष्ठा perf_sample;
काष्ठा addr_location;
काष्ठा call_वापस_processor;
काष्ठा call_path_root;
काष्ठा call_path;
काष्ठा call_वापस;

काष्ठा export_sample अणु
	जोड़ perf_event	*event;
	काष्ठा perf_sample	*sample;
	काष्ठा evsel		*evsel;
	काष्ठा addr_location	*al;
	u64			db_id;
	u64			comm_db_id;
	u64			dso_db_id;
	u64			sym_db_id;
	u64			offset; /* ip offset from symbol start */
	u64			addr_dso_db_id;
	u64			addr_sym_db_id;
	u64			addr_offset; /* addr offset from symbol start */
	u64			call_path_id;
पूर्ण;

काष्ठा db_export अणु
	पूर्णांक (*export_evsel)(काष्ठा db_export *dbe, काष्ठा evsel *evsel);
	पूर्णांक (*export_machine)(काष्ठा db_export *dbe, काष्ठा machine *machine);
	पूर्णांक (*export_thपढ़ो)(काष्ठा db_export *dbe, काष्ठा thपढ़ो *thपढ़ो,
			     u64 मुख्य_thपढ़ो_db_id, काष्ठा machine *machine);
	पूर्णांक (*export_comm)(काष्ठा db_export *dbe, काष्ठा comm *comm,
			   काष्ठा thपढ़ो *thपढ़ो);
	पूर्णांक (*export_comm_thपढ़ो)(काष्ठा db_export *dbe, u64 db_id,
				  काष्ठा comm *comm, काष्ठा thपढ़ो *thपढ़ो);
	पूर्णांक (*export_dso)(काष्ठा db_export *dbe, काष्ठा dso *dso,
			  काष्ठा machine *machine);
	पूर्णांक (*export_symbol)(काष्ठा db_export *dbe, काष्ठा symbol *sym,
			     काष्ठा dso *dso);
	पूर्णांक (*export_branch_type)(काष्ठा db_export *dbe, u32 branch_type,
				  स्थिर अक्षर *name);
	पूर्णांक (*export_sample)(काष्ठा db_export *dbe, काष्ठा export_sample *es);
	पूर्णांक (*export_call_path)(काष्ठा db_export *dbe, काष्ठा call_path *cp);
	पूर्णांक (*export_call_वापस)(काष्ठा db_export *dbe,
				  काष्ठा call_वापस *cr);
	पूर्णांक (*export_context_चयन)(काष्ठा db_export *dbe, u64 db_id,
				     काष्ठा machine *machine,
				     काष्ठा perf_sample *sample,
				     u64 th_out_id, u64 comm_out_id,
				     u64 th_in_id, u64 comm_in_id, पूर्णांक flags);
	काष्ठा call_वापस_processor *crp;
	काष्ठा call_path_root *cpr;
	u64 evsel_last_db_id;
	u64 machine_last_db_id;
	u64 thपढ़ो_last_db_id;
	u64 comm_last_db_id;
	u64 comm_thपढ़ो_last_db_id;
	u64 dso_last_db_id;
	u64 symbol_last_db_id;
	u64 sample_last_db_id;
	u64 call_path_last_db_id;
	u64 call_वापस_last_db_id;
	u64 context_चयन_last_db_id;
पूर्ण;

पूर्णांक db_export__init(काष्ठा db_export *dbe);
व्योम db_export__निकास(काष्ठा db_export *dbe);
पूर्णांक db_export__evsel(काष्ठा db_export *dbe, काष्ठा evsel *evsel);
पूर्णांक db_export__machine(काष्ठा db_export *dbe, काष्ठा machine *machine);
पूर्णांक db_export__thपढ़ो(काष्ठा db_export *dbe, काष्ठा thपढ़ो *thपढ़ो,
		      काष्ठा machine *machine, काष्ठा thपढ़ो *मुख्य_thपढ़ो);
पूर्णांक db_export__comm(काष्ठा db_export *dbe, काष्ठा comm *comm,
		    काष्ठा thपढ़ो *thपढ़ो);
पूर्णांक db_export__exec_comm(काष्ठा db_export *dbe, काष्ठा comm *comm,
			 काष्ठा thपढ़ो *मुख्य_thपढ़ो);
पूर्णांक db_export__comm_thपढ़ो(काष्ठा db_export *dbe, काष्ठा comm *comm,
			   काष्ठा thपढ़ो *thपढ़ो);
पूर्णांक db_export__dso(काष्ठा db_export *dbe, काष्ठा dso *dso,
		   काष्ठा machine *machine);
पूर्णांक db_export__symbol(काष्ठा db_export *dbe, काष्ठा symbol *sym,
		      काष्ठा dso *dso);
पूर्णांक db_export__branch_type(काष्ठा db_export *dbe, u32 branch_type,
			   स्थिर अक्षर *name);
पूर्णांक db_export__sample(काष्ठा db_export *dbe, जोड़ perf_event *event,
		      काष्ठा perf_sample *sample, काष्ठा evsel *evsel,
		      काष्ठा addr_location *al);

पूर्णांक db_export__branch_types(काष्ठा db_export *dbe);

पूर्णांक db_export__call_path(काष्ठा db_export *dbe, काष्ठा call_path *cp);
पूर्णांक db_export__call_वापस(काष्ठा db_export *dbe, काष्ठा call_वापस *cr,
			   u64 *parent_db_id);
पूर्णांक db_export__चयन(काष्ठा db_export *dbe, जोड़ perf_event *event,
		      काष्ठा perf_sample *sample, काष्ठा machine *machine);

#पूर्ण_अगर
