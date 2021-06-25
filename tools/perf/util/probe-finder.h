<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PROBE_FINDER_H
#घोषणा _PROBE_FINDER_H

#समावेश <stdbool.h>
#समावेश "intlist.h"
#समावेश "build-id.h"
#समावेश "probe-event.h"
#समावेश <linux/प्रकार.स>

#घोषणा MAX_PROBE_BUFFER	1024
#घोषणा MAX_PROBES		 128
#घोषणा MAX_PROBE_ARGS		 128

#घोषणा PROBE_ARG_VARS		"$vars"
#घोषणा PROBE_ARG_PARAMS	"$params"

अटल अंतरभूत पूर्णांक is_c_varname(स्थिर अक्षर *name)
अणु
	/* TODO */
	वापस है_अक्षर(name[0]) || name[0] == '_';
पूर्ण

#अगर_घोषित HAVE_DWARF_SUPPORT

#समावेश "dwarf-aux.h"

/* TODO: export debuginfo data काष्ठाure even अगर no dwarf support */

/* debug inक्रमmation काष्ठाure */
काष्ठा debuginfo अणु
	Dwarf		*dbg;
	Dwfl_Module	*mod;
	Dwfl		*dwfl;
	Dwarf_Addr	bias;
	स्थिर अचिन्हित अक्षर	*build_id;
पूर्ण;

/* This also tries to खोलो distro debuginfo */
काष्ठा debuginfo *debuginfo__new(स्थिर अक्षर *path);
व्योम debuginfo__delete(काष्ठा debuginfo *dbg);

/* Find probe_trace_events specअगरied by perf_probe_event from debuginfo */
पूर्णांक debuginfo__find_trace_events(काष्ठा debuginfo *dbg,
				 काष्ठा perf_probe_event *pev,
				 काष्ठा probe_trace_event **tevs);

/* Find a perf_probe_poपूर्णांक from debuginfo */
पूर्णांक debuginfo__find_probe_poपूर्णांक(काष्ठा debuginfo *dbg, अचिन्हित दीर्घ addr,
				काष्ठा perf_probe_poपूर्णांक *ppt);

पूर्णांक debuginfo__get_text_offset(काष्ठा debuginfo *dbg, Dwarf_Addr *offs,
			       bool adjust_offset);

/* Find a line range */
पूर्णांक debuginfo__find_line_range(काष्ठा debuginfo *dbg, काष्ठा line_range *lr);

/* Find available variables */
पूर्णांक debuginfo__find_available_vars_at(काष्ठा debuginfo *dbg,
				      काष्ठा perf_probe_event *pev,
				      काष्ठा variable_list **vls);

/* Find a src file from a DWARF tag path */
पूर्णांक find_source_path(स्थिर अक्षर *raw_path, स्थिर अक्षर *sbuild_id,
		     स्थिर अक्षर *comp_dir, अक्षर **new_path);

काष्ठा probe_finder अणु
	काष्ठा perf_probe_event	*pev;		/* Target probe event */
	काष्ठा debuginfo	*dbg;

	/* Callback when a probe poपूर्णांक is found */
	पूर्णांक (*callback)(Dwarf_Die *sc_die, काष्ठा probe_finder *pf);

	/* For function searching */
	पूर्णांक			lno;		/* Line number */
	Dwarf_Addr		addr;		/* Address */
	स्थिर अक्षर		*fname;		/* Real file name */
	Dwarf_Die		cu_die;		/* Current CU */
	Dwarf_Die		sp_die;
	काष्ठा पूर्णांकlist		*lcache;	/* Line cache क्रम lazy match */

	/* For variable searching */
#अगर _ELFUTILS_PREREQ(0, 142)
	/* Call Frame Inक्रमmation from .eh_frame */
	Dwarf_CFI		*cfi_eh;
	/* Call Frame Inक्रमmation from .debug_frame */
	Dwarf_CFI		*cfi_dbg;
#पूर्ण_अगर
	Dwarf_Op		*fb_ops;	/* Frame base attribute */
	अचिन्हित पूर्णांक		machine;	/* Target machine arch */
	काष्ठा perf_probe_arg	*pvar;		/* Current target variable */
	काष्ठा probe_trace_arg	*tvar;		/* Current result variable */
	bool			skip_empty_arg;	/* Skip non-exist args */
पूर्ण;

काष्ठा trace_event_finder अणु
	काष्ठा probe_finder	pf;
	Dwfl_Module		*mod;		/* For solving symbols */
	काष्ठा probe_trace_event *tevs;		/* Found trace events */
	पूर्णांक			ntevs;		/* Number of trace events */
	पूर्णांक			max_tevs;	/* Max number of trace events */
पूर्ण;

काष्ठा available_var_finder अणु
	काष्ठा probe_finder	pf;
	Dwfl_Module		*mod;		/* For solving symbols */
	काष्ठा variable_list	*vls;		/* Found variable lists */
	पूर्णांक			nvls;		/* Number of variable lists */
	पूर्णांक			max_vls;	/* Max no. of variable lists */
	bool			child;		/* Search child scopes */
पूर्ण;

काष्ठा line_finder अणु
	काष्ठा line_range	*lr;		/* Target line range */

	स्थिर अक्षर		*fname;		/* File name */
	पूर्णांक			lno_s;		/* Start line number */
	पूर्णांक			lno_e;		/* End line number */
	Dwarf_Die		cu_die;		/* Current CU */
	Dwarf_Die		sp_die;
	पूर्णांक			found;
पूर्ण;

#पूर्ण_अगर /* HAVE_DWARF_SUPPORT */

#पूर्ण_अगर /*_PROBE_FINDER_H */
