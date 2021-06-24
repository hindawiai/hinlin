<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PROBE_EVENT_H
#घोषणा _PROBE_EVENT_H

#समावेश <linux/compiler.h>
#समावेश <stdbool.h>

काष्ठा पूर्णांकlist;
काष्ठा nsinfo;

/* Probe related configurations */
काष्ठा probe_conf अणु
	bool	show_ext_vars;
	bool	show_location_range;
	bool	क्रमce_add;
	bool	no_अंतरभूतs;
	bool	cache;
	पूर्णांक	max_probes;
	अचिन्हित दीर्घ	magic_num;
पूर्ण;
बाह्य काष्ठा probe_conf probe_conf;
बाह्य bool probe_event_dry_run;

#घोषणा DEFAULT_PROBE_MAGIC_NUM	0xdeade12d	/* u32: 3735937325 */

काष्ठा symbol;

/* kprobe-tracer and uprobe-tracer tracing poपूर्णांक */
काष्ठा probe_trace_poपूर्णांक अणु
	अक्षर		*realname;	/* function real name (अगर needed) */
	अक्षर		*symbol;	/* Base symbol */
	अक्षर		*module;	/* Module name */
	अचिन्हित दीर्घ	offset;		/* Offset from symbol */
	अचिन्हित दीर्घ	ref_ctr_offset;	/* SDT reference counter offset */
	अचिन्हित दीर्घ	address;	/* Actual address of the trace poपूर्णांक */
	bool		retprobe;	/* Return probe flag */
पूर्ण;

/* probe-tracer tracing argument referencing offset */
काष्ठा probe_trace_arg_ref अणु
	काष्ठा probe_trace_arg_ref	*next;	/* Next reference */
	दीर्घ				offset;	/* Offset value */
	bool				user_access;	/* User-memory access */
पूर्ण;

/* kprobe-tracer and uprobe-tracer tracing argument */
काष्ठा probe_trace_arg अणु
	अक्षर				*name;	/* Argument name */
	अक्षर				*value;	/* Base value */
	अक्षर				*type;	/* Type name */
	काष्ठा probe_trace_arg_ref	*ref;	/* Referencing offset */
पूर्ण;

/* kprobe-tracer and uprobe-tracer tracing event (poपूर्णांक + arg) */
काष्ठा probe_trace_event अणु
	अक्षर				*event;	/* Event name */
	अक्षर				*group;	/* Group name */
	काष्ठा probe_trace_poपूर्णांक	poपूर्णांक;	/* Trace poपूर्णांक */
	पूर्णांक				nargs;	/* Number of args */
	bool				uprobes;	/* uprobes only */
	काष्ठा probe_trace_arg		*args;	/* Arguments */
पूर्ण;

/* Perf probe probing poपूर्णांक */
काष्ठा perf_probe_poपूर्णांक अणु
	अक्षर		*file;		/* File path */
	अक्षर		*function;	/* Function name */
	पूर्णांक		line;		/* Line number */
	bool		retprobe;	/* Return probe flag */
	अक्षर		*lazy_line;	/* Lazy matching pattern */
	अचिन्हित दीर्घ	offset;		/* Offset from function entry */
	अचिन्हित दीर्घ	असल_address;	/* Absolute address of the poपूर्णांक */
पूर्ण;

/* Perf probe probing argument field chain */
काष्ठा perf_probe_arg_field अणु
	काष्ठा perf_probe_arg_field	*next;	/* Next field */
	अक्षर				*name;	/* Name of the field */
	दीर्घ				index;	/* Array index number */
	bool				ref;	/* Referencing flag */
पूर्ण;

/* Perf probe probing argument */
काष्ठा perf_probe_arg अणु
	अक्षर				*name;	/* Argument name */
	अक्षर				*var;	/* Variable name */
	अक्षर				*type;	/* Type name */
	काष्ठा perf_probe_arg_field	*field;	/* Structure fields */
	bool				user_access;	/* User-memory access */
पूर्ण;

/* Perf probe probing event (poपूर्णांक + arg) */
काष्ठा perf_probe_event अणु
	अक्षर			*event;	/* Event name */
	अक्षर			*group;	/* Group name */
	काष्ठा perf_probe_poपूर्णांक	poपूर्णांक;	/* Probe poपूर्णांक */
	पूर्णांक			nargs;	/* Number of arguments */
	bool			sdt;	/* SDT/cached event flag */
	bool			uprobes;	/* Uprobe event flag */
	अक्षर			*target;	/* Target binary */
	काष्ठा perf_probe_arg	*args;	/* Arguments */
	काष्ठा probe_trace_event *tevs;
	पूर्णांक			ntevs;
	काष्ठा nsinfo		*nsi;	/* Target namespace */
पूर्ण;

/* Line range */
काष्ठा line_range अणु
	अक्षर			*file;		/* File name */
	अक्षर			*function;	/* Function name */
	पूर्णांक			start;		/* Start line number */
	पूर्णांक			end;		/* End line number */
	पूर्णांक			offset;		/* Start line offset */
	अक्षर			*path;		/* Real path name */
	अक्षर			*comp_dir;	/* Compile directory */
	काष्ठा पूर्णांकlist		*line_list;	/* Visible lines */
पूर्ण;

काष्ठा strlist;

/* List of variables */
काष्ठा variable_list अणु
	काष्ठा probe_trace_poपूर्णांक	poपूर्णांक;	/* Actual probepoपूर्णांक */
	काष्ठा strlist			*vars;	/* Available variables */
पूर्ण;

काष्ठा map;
पूर्णांक init_probe_symbol_maps(bool user_only);
व्योम निकास_probe_symbol_maps(व्योम);

/* Command string to events */
पूर्णांक parse_perf_probe_command(स्थिर अक्षर *cmd, काष्ठा perf_probe_event *pev);
पूर्णांक parse_probe_trace_command(स्थिर अक्षर *cmd, काष्ठा probe_trace_event *tev);

/* Events to command string */
अक्षर *synthesize_perf_probe_command(काष्ठा perf_probe_event *pev);
अक्षर *synthesize_probe_trace_command(काष्ठा probe_trace_event *tev);
अक्षर *synthesize_perf_probe_arg(काष्ठा perf_probe_arg *pa);
अक्षर *synthesize_perf_probe_poपूर्णांक(काष्ठा perf_probe_poपूर्णांक *pp);

पूर्णांक perf_probe_event__copy(काष्ठा perf_probe_event *dst,
			   काष्ठा perf_probe_event *src);

bool perf_probe_with_var(काष्ठा perf_probe_event *pev);

/* Check the perf_probe_event needs debuginfo */
bool perf_probe_event_need_dwarf(काष्ठा perf_probe_event *pev);

/* Release event contents */
व्योम clear_perf_probe_event(काष्ठा perf_probe_event *pev);
व्योम clear_probe_trace_event(काष्ठा probe_trace_event *tev);

/* Command string to line-range */
पूर्णांक parse_line_range_desc(स्थिर अक्षर *cmd, काष्ठा line_range *lr);

/* Release line range members */
व्योम line_range__clear(काष्ठा line_range *lr);

/* Initialize line range */
पूर्णांक line_range__init(काष्ठा line_range *lr);

पूर्णांक add_perf_probe_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs);
पूर्णांक convert_perf_probe_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs);
पूर्णांक apply_perf_probe_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs);
पूर्णांक show_probe_trace_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs);
व्योम cleanup_perf_probe_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs);

काष्ठा strfilter;

पूर्णांक del_perf_probe_events(काष्ठा strfilter *filter);

पूर्णांक show_perf_probe_event(स्थिर अक्षर *group, स्थिर अक्षर *event,
			  काष्ठा perf_probe_event *pev,
			  स्थिर अक्षर *module, bool use_मानक_निकास);
पूर्णांक show_perf_probe_events(काष्ठा strfilter *filter);
पूर्णांक show_line_range(काष्ठा line_range *lr, स्थिर अक्षर *module,
		    काष्ठा nsinfo *nsi, bool user);
पूर्णांक show_available_vars(काष्ठा perf_probe_event *pevs, पूर्णांक npevs,
			काष्ठा strfilter *filter);
पूर्णांक show_available_funcs(स्थिर अक्षर *module, काष्ठा nsinfo *nsi,
			 काष्ठा strfilter *filter, bool user);
व्योम arch__fix_tev_from_maps(काष्ठा perf_probe_event *pev,
			     काष्ठा probe_trace_event *tev, काष्ठा map *map,
			     काष्ठा symbol *sym);

/* If there is no space to ग_लिखो, वापसs -E2BIG. */
पूर्णांक e_snम_लिखो(अक्षर *str, माप_प्रकार size, स्थिर अक्षर *क्रमmat, ...) __म_लिखो(3, 4);

/* Maximum index number of event-name postfix */
#घोषणा MAX_EVENT_INDEX	1024

पूर्णांक copy_to_probe_trace_arg(काष्ठा probe_trace_arg *tvar,
			    काष्ठा perf_probe_arg *pvar);

काष्ठा map *get_target_map(स्थिर अक्षर *target, काष्ठा nsinfo *nsi, bool user);

व्योम arch__post_process_probe_trace_events(काष्ठा perf_probe_event *pev,
					   पूर्णांक ntevs);

#पूर्ण_अगर /*_PROBE_EVENT_H */
