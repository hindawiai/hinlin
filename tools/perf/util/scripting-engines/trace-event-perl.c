<शैली गुरु>
/*
 * trace-event-perl.  Feed perf script events to an embedded Perl पूर्णांकerpreter.
 *
 * Copyright (C) 2009 Tom Zanussi <tzanussi@gmail.com>
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/समय64.h>

#समावेश <stdbool.h>
/* perl needs the following define, right after including stdbool.h */
#घोषणा HAS_BOOL
#समावेश <EXTERN.h>
#समावेश <perl.h>

#समावेश "../callchain.h"
#समावेश "../dso.h"
#समावेश "../machine.h"
#समावेश "../map.h"
#समावेश "../symbol.h"
#समावेश "../thread.h"
#समावेश "../event.h"
#समावेश "../trace-event.h"
#समावेश "../evsel.h"
#समावेश "../debug.h"

व्योम boot_Perf__Trace__Context(pTHX_ CV *cv);
व्योम boot_DynaLoader(pTHX_ CV *cv);
प्रकार PerlInterpreter * INTERP;

व्योम xs_init(pTHX);

व्योम xs_init(pTHX)
अणु
	स्थिर अक्षर *file = __खाता__;
	dXSUB_SYS;

	newXS("Perf::Trace::Context::bootstrap", boot_Perf__Trace__Context,
	      file);
	newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
पूर्ण

INTERP my_perl;

#घोषणा TRACE_EVENT_TYPE_MAX				\
	((1 << (माप(अचिन्हित लघु) * 8)) - 1)

अटल DECLARE_BITMAP(events_defined, TRACE_EVENT_TYPE_MAX);

बाह्य काष्ठा scripting_context *scripting_context;

अटल अक्षर *cur_field_name;
अटल पूर्णांक zero_flag_atom;

अटल व्योम define_symbolic_value(स्थिर अक्षर *ev_name,
				  स्थिर अक्षर *field_name,
				  स्थिर अक्षर *field_value,
				  स्थिर अक्षर *field_str)
अणु
	अचिन्हित दीर्घ दीर्घ value;
	dSP;

	value = eval_flag(field_value);

	ENTER;
	SAVETMPS;
	PUSHMARK(SP);

	XPUSHs(sv_2mortal(newSVpv(ev_name, 0)));
	XPUSHs(sv_2mortal(newSVpv(field_name, 0)));
	XPUSHs(sv_2mortal(newSVuv(value)));
	XPUSHs(sv_2mortal(newSVpv(field_str, 0)));

	PUTBACK;
	अगर (get_cv("main::define_symbolic_value", 0))
		call_pv("main::define_symbolic_value", G_SCALAR);
	SPAGAIN;
	PUTBACK;
	FREETMPS;
	LEAVE;
पूर्ण

अटल व्योम define_symbolic_values(काष्ठा tep_prपूर्णांक_flag_sym *field,
				   स्थिर अक्षर *ev_name,
				   स्थिर अक्षर *field_name)
अणु
	define_symbolic_value(ev_name, field_name, field->value, field->str);
	अगर (field->next)
		define_symbolic_values(field->next, ev_name, field_name);
पूर्ण

अटल व्योम define_symbolic_field(स्थिर अक्षर *ev_name,
				  स्थिर अक्षर *field_name)
अणु
	dSP;

	ENTER;
	SAVETMPS;
	PUSHMARK(SP);

	XPUSHs(sv_2mortal(newSVpv(ev_name, 0)));
	XPUSHs(sv_2mortal(newSVpv(field_name, 0)));

	PUTBACK;
	अगर (get_cv("main::define_symbolic_field", 0))
		call_pv("main::define_symbolic_field", G_SCALAR);
	SPAGAIN;
	PUTBACK;
	FREETMPS;
	LEAVE;
पूर्ण

अटल व्योम define_flag_value(स्थिर अक्षर *ev_name,
			      स्थिर अक्षर *field_name,
			      स्थिर अक्षर *field_value,
			      स्थिर अक्षर *field_str)
अणु
	अचिन्हित दीर्घ दीर्घ value;
	dSP;

	value = eval_flag(field_value);

	ENTER;
	SAVETMPS;
	PUSHMARK(SP);

	XPUSHs(sv_2mortal(newSVpv(ev_name, 0)));
	XPUSHs(sv_2mortal(newSVpv(field_name, 0)));
	XPUSHs(sv_2mortal(newSVuv(value)));
	XPUSHs(sv_2mortal(newSVpv(field_str, 0)));

	PUTBACK;
	अगर (get_cv("main::define_flag_value", 0))
		call_pv("main::define_flag_value", G_SCALAR);
	SPAGAIN;
	PUTBACK;
	FREETMPS;
	LEAVE;
पूर्ण

अटल व्योम define_flag_values(काष्ठा tep_prपूर्णांक_flag_sym *field,
			       स्थिर अक्षर *ev_name,
			       स्थिर अक्षर *field_name)
अणु
	define_flag_value(ev_name, field_name, field->value, field->str);
	अगर (field->next)
		define_flag_values(field->next, ev_name, field_name);
पूर्ण

अटल व्योम define_flag_field(स्थिर अक्षर *ev_name,
			      स्थिर अक्षर *field_name,
			      स्थिर अक्षर *delim)
अणु
	dSP;

	ENTER;
	SAVETMPS;
	PUSHMARK(SP);

	XPUSHs(sv_2mortal(newSVpv(ev_name, 0)));
	XPUSHs(sv_2mortal(newSVpv(field_name, 0)));
	XPUSHs(sv_2mortal(newSVpv(delim, 0)));

	PUTBACK;
	अगर (get_cv("main::define_flag_field", 0))
		call_pv("main::define_flag_field", G_SCALAR);
	SPAGAIN;
	PUTBACK;
	FREETMPS;
	LEAVE;
पूर्ण

अटल व्योम define_event_symbols(काष्ठा tep_event *event,
				 स्थिर अक्षर *ev_name,
				 काष्ठा tep_prपूर्णांक_arg *args)
अणु
	अगर (args == शून्य)
		वापस;

	चयन (args->type) अणु
	हाल TEP_PRINT_शून्य:
		अवरोध;
	हाल TEP_PRINT_ATOM:
		define_flag_value(ev_name, cur_field_name, "0",
				  args->atom.atom);
		zero_flag_atom = 0;
		अवरोध;
	हाल TEP_PRINT_FIELD:
		मुक्त(cur_field_name);
		cur_field_name = strdup(args->field.name);
		अवरोध;
	हाल TEP_PRINT_FLAGS:
		define_event_symbols(event, ev_name, args->flags.field);
		define_flag_field(ev_name, cur_field_name, args->flags.delim);
		define_flag_values(args->flags.flags, ev_name, cur_field_name);
		अवरोध;
	हाल TEP_PRINT_SYMBOL:
		define_event_symbols(event, ev_name, args->symbol.field);
		define_symbolic_field(ev_name, cur_field_name);
		define_symbolic_values(args->symbol.symbols, ev_name,
				       cur_field_name);
		अवरोध;
	हाल TEP_PRINT_HEX:
	हाल TEP_PRINT_HEX_STR:
		define_event_symbols(event, ev_name, args->hex.field);
		define_event_symbols(event, ev_name, args->hex.size);
		अवरोध;
	हाल TEP_PRINT_INT_ARRAY:
		define_event_symbols(event, ev_name, args->पूर्णांक_array.field);
		define_event_symbols(event, ev_name, args->पूर्णांक_array.count);
		define_event_symbols(event, ev_name, args->पूर्णांक_array.el_size);
		अवरोध;
	हाल TEP_PRINT_BSTRING:
	हाल TEP_PRINT_DYNAMIC_ARRAY:
	हाल TEP_PRINT_DYNAMIC_ARRAY_LEN:
	हाल TEP_PRINT_STRING:
	हाल TEP_PRINT_BITMASK:
		अवरोध;
	हाल TEP_PRINT_TYPE:
		define_event_symbols(event, ev_name, args->typecast.item);
		अवरोध;
	हाल TEP_PRINT_OP:
		अगर (म_भेद(args->op.op, ":") == 0)
			zero_flag_atom = 1;
		define_event_symbols(event, ev_name, args->op.left);
		define_event_symbols(event, ev_name, args->op.right);
		अवरोध;
	हाल TEP_PRINT_FUNC:
	शेष:
		pr_err("Unsupported print arg type\n");
		/* we should warn... */
		वापस;
	पूर्ण

	अगर (args->next)
		define_event_symbols(event, ev_name, args->next);
पूर्ण

अटल SV *perl_process_callchain(काष्ठा perf_sample *sample,
				  काष्ठा evsel *evsel,
				  काष्ठा addr_location *al)
अणु
	AV *list;

	list = newAV();
	अगर (!list)
		जाओ निकास;

	अगर (!symbol_conf.use_callchain || !sample->callchain)
		जाओ निकास;

	अगर (thपढ़ो__resolve_callchain(al->thपढ़ो, &callchain_cursor, evsel,
				      sample, शून्य, शून्य, scripting_max_stack) != 0) अणु
		pr_err("Failed to resolve callchain. Skipping\n");
		जाओ निकास;
	पूर्ण
	callchain_cursor_commit(&callchain_cursor);


	जबतक (1) अणु
		HV *elem;
		काष्ठा callchain_cursor_node *node;
		node = callchain_cursor_current(&callchain_cursor);
		अगर (!node)
			अवरोध;

		elem = newHV();
		अगर (!elem)
			जाओ निकास;

		अगर (!hv_stores(elem, "ip", newSVuv(node->ip))) अणु
			hv_undef(elem);
			जाओ निकास;
		पूर्ण

		अगर (node->ms.sym) अणु
			HV *sym = newHV();
			अगर (!sym) अणु
				hv_undef(elem);
				जाओ निकास;
			पूर्ण
			अगर (!hv_stores(sym, "start",   newSVuv(node->ms.sym->start)) ||
			    !hv_stores(sym, "end",     newSVuv(node->ms.sym->end)) ||
			    !hv_stores(sym, "binding", newSVuv(node->ms.sym->binding)) ||
			    !hv_stores(sym, "name",    newSVpvn(node->ms.sym->name,
								node->ms.sym->namelen)) ||
			    !hv_stores(elem, "sym",    newRV_noinc((SV*)sym))) अणु
				hv_undef(sym);
				hv_undef(elem);
				जाओ निकास;
			पूर्ण
		पूर्ण

		अगर (node->ms.map) अणु
			काष्ठा map *map = node->ms.map;
			स्थिर अक्षर *dsoname = "[unknown]";
			अगर (map && map->dso) अणु
				अगर (symbol_conf.show_kernel_path && map->dso->दीर्घ_name)
					dsoname = map->dso->दीर्घ_name;
				अन्यथा
					dsoname = map->dso->name;
			पूर्ण
			अगर (!hv_stores(elem, "dso", newSVpv(dsoname,0))) अणु
				hv_undef(elem);
				जाओ निकास;
			पूर्ण
		पूर्ण

		callchain_cursor_advance(&callchain_cursor);
		av_push(list, newRV_noinc((SV*)elem));
	पूर्ण

निकास:
	वापस newRV_noinc((SV*)list);
पूर्ण

अटल व्योम perl_process_tracepoपूर्णांक(काष्ठा perf_sample *sample,
				    काष्ठा evsel *evsel,
				    काष्ठा addr_location *al)
अणु
	काष्ठा thपढ़ो *thपढ़ो = al->thपढ़ो;
	काष्ठा tep_event *event = evsel->tp_क्रमmat;
	काष्ठा tep_क्रमmat_field *field;
	अटल अक्षर handler[256];
	अचिन्हित दीर्घ दीर्घ val;
	अचिन्हित दीर्घ s, ns;
	पूर्णांक pid;
	पूर्णांक cpu = sample->cpu;
	व्योम *data = sample->raw_data;
	अचिन्हित दीर्घ दीर्घ nsecs = sample->समय;
	स्थिर अक्षर *comm = thपढ़ो__comm_str(thपढ़ो);

	dSP;

	अगर (evsel->core.attr.type != PERF_TYPE_TRACEPOINT)
		वापस;

	अगर (!event) अणु
		pr_debug("ug! no event found for type %" PRIu64, (u64)evsel->core.attr.config);
		वापस;
	पूर्ण

	pid = raw_field_value(event, "common_pid", data);

	प्र_लिखो(handler, "%s::%s", event->प्रणाली, event->name);

	अगर (!test_and_set_bit(event->id, events_defined))
		define_event_symbols(event, handler, event->prपूर्णांक_fmt.args);

	s = nsecs / NSEC_PER_SEC;
	ns = nsecs - s * NSEC_PER_SEC;

	scripting_context->event_data = data;
	scripting_context->pevent = evsel->tp_क्रमmat->tep;

	ENTER;
	SAVETMPS;
	PUSHMARK(SP);

	XPUSHs(sv_2mortal(newSVpv(handler, 0)));
	XPUSHs(sv_2mortal(newSViv(PTR2IV(scripting_context))));
	XPUSHs(sv_2mortal(newSVuv(cpu)));
	XPUSHs(sv_2mortal(newSVuv(s)));
	XPUSHs(sv_2mortal(newSVuv(ns)));
	XPUSHs(sv_2mortal(newSViv(pid)));
	XPUSHs(sv_2mortal(newSVpv(comm, 0)));
	XPUSHs(sv_2mortal(perl_process_callchain(sample, evsel, al)));

	/* common fields other than pid can be accessed via xsub fns */

	क्रम (field = event->क्रमmat.fields; field; field = field->next) अणु
		अगर (field->flags & TEP_FIELD_IS_STRING) अणु
			पूर्णांक offset;
			अगर (field->flags & TEP_FIELD_IS_DYNAMIC) अणु
				offset = *(पूर्णांक *)(data + field->offset);
				offset &= 0xffff;
			पूर्ण अन्यथा
				offset = field->offset;
			XPUSHs(sv_2mortal(newSVpv((अक्षर *)data + offset, 0)));
		पूर्ण अन्यथा अणु /* FIELD_IS_NUMERIC */
			val = पढ़ो_size(event, data + field->offset,
					field->size);
			अगर (field->flags & TEP_FIELD_IS_SIGNED) अणु
				XPUSHs(sv_2mortal(newSViv(val)));
			पूर्ण अन्यथा अणु
				XPUSHs(sv_2mortal(newSVuv(val)));
			पूर्ण
		पूर्ण
	पूर्ण

	PUTBACK;

	अगर (get_cv(handler, 0))
		call_pv(handler, G_SCALAR);
	अन्यथा अगर (get_cv("main::trace_unhandled", 0)) अणु
		XPUSHs(sv_2mortal(newSVpv(handler, 0)));
		XPUSHs(sv_2mortal(newSViv(PTR2IV(scripting_context))));
		XPUSHs(sv_2mortal(newSVuv(cpu)));
		XPUSHs(sv_2mortal(newSVuv(nsecs)));
		XPUSHs(sv_2mortal(newSViv(pid)));
		XPUSHs(sv_2mortal(newSVpv(comm, 0)));
		XPUSHs(sv_2mortal(perl_process_callchain(sample, evsel, al)));
		call_pv("main::trace_unhandled", G_SCALAR);
	पूर्ण
	SPAGAIN;
	PUTBACK;
	FREETMPS;
	LEAVE;
पूर्ण

अटल व्योम perl_process_event_generic(जोड़ perf_event *event,
				       काष्ठा perf_sample *sample,
				       काष्ठा evsel *evsel)
अणु
	dSP;

	अगर (!get_cv("process_event", 0))
		वापस;

	ENTER;
	SAVETMPS;
	PUSHMARK(SP);
	XPUSHs(sv_2mortal(newSVpvn((स्थिर अक्षर *)event, event->header.size)));
	XPUSHs(sv_2mortal(newSVpvn((स्थिर अक्षर *)&evsel->core.attr, माप(evsel->core.attr))));
	XPUSHs(sv_2mortal(newSVpvn((स्थिर अक्षर *)sample, माप(*sample))));
	XPUSHs(sv_2mortal(newSVpvn((स्थिर अक्षर *)sample->raw_data, sample->raw_size)));
	PUTBACK;
	call_pv("process_event", G_SCALAR);
	SPAGAIN;
	PUTBACK;
	FREETMPS;
	LEAVE;
पूर्ण

अटल व्योम perl_process_event(जोड़ perf_event *event,
			       काष्ठा perf_sample *sample,
			       काष्ठा evsel *evsel,
			       काष्ठा addr_location *al)
अणु
	perl_process_tracepoपूर्णांक(sample, evsel, al);
	perl_process_event_generic(event, sample, evsel);
पूर्ण

अटल व्योम run_start_sub(व्योम)
अणु
	dSP; /* access to Perl stack */
	PUSHMARK(SP);

	अगर (get_cv("main::trace_begin", 0))
		call_pv("main::trace_begin", G_DISCARD | G_NOARGS);
पूर्ण

/*
 * Start trace script
 */
अटल पूर्णांक perl_start_script(स्थिर अक्षर *script, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर **command_line;
	पूर्णांक i, err = 0;

	command_line = दो_स्मृति((argc + 2) * माप(स्थिर अक्षर *));
	command_line[0] = "";
	command_line[1] = script;
	क्रम (i = 2; i < argc + 2; i++)
		command_line[i] = argv[i - 2];

	my_perl = perl_alloc();
	perl_स्थिरruct(my_perl);

	अगर (perl_parse(my_perl, xs_init, argc + 2, (अक्षर **)command_line,
		       (अक्षर **)शून्य)) अणु
		err = -1;
		जाओ error;
	पूर्ण

	अगर (perl_run(my_perl)) अणु
		err = -1;
		जाओ error;
	पूर्ण

	अगर (SvTRUE(ERRSV)) अणु
		err = -1;
		जाओ error;
	पूर्ण

	run_start_sub();

	मुक्त(command_line);
	वापस 0;
error:
	perl_मुक्त(my_perl);
	मुक्त(command_line);

	वापस err;
पूर्ण

अटल पूर्णांक perl_flush_script(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * Stop trace script
 */
अटल पूर्णांक perl_stop_script(व्योम)
अणु
	dSP; /* access to Perl stack */
	PUSHMARK(SP);

	अगर (get_cv("main::trace_end", 0))
		call_pv("main::trace_end", G_DISCARD | G_NOARGS);

	perl_deकाष्ठा(my_perl);
	perl_मुक्त(my_perl);

	वापस 0;
पूर्ण

अटल पूर्णांक perl_generate_script(काष्ठा tep_handle *pevent, स्थिर अक्षर *outfile)
अणु
	पूर्णांक i, not_first, count, nr_events;
	काष्ठा tep_event **all_events;
	काष्ठा tep_event *event = शून्य;
	काष्ठा tep_क्रमmat_field *f;
	अक्षर fname[PATH_MAX];
	खाता *ofp;

	प्र_लिखो(fname, "%s.pl", outfile);
	ofp = ख_खोलो(fname, "w");
	अगर (ofp == शून्य) अणु
		ख_लिखो(मानक_त्रुटि, "couldn't open %s\n", fname);
		वापस -1;
	पूर्ण

	ख_लिखो(ofp, "# perf script event handlers, "
		"generated by perf script -g perl\n");

	ख_लिखो(ofp, "# Licensed under the terms of the GNU GPL"
		" License version 2\n\n");

	ख_लिखो(ofp, "# The common_* event handler fields are the most useful "
		"fields common to\n");

	ख_लिखो(ofp, "# all events.  They don't necessarily correspond to "
		"the 'common_*' fields\n");

	ख_लिखो(ofp, "# in the format files.  Those fields not available as "
		"handler params can\n");

	ख_लिखो(ofp, "# be retrieved using Perl functions of the form "
		"common_*($context).\n");

	ख_लिखो(ofp, "# See Context.pm for the list of available "
		"functions.\n\n");

	ख_लिखो(ofp, "use lib \"$ENV{'PERF_EXEC_PATH'}/scripts/perl/"
		"Perf-Trace-Util/lib\";\n");

	ख_लिखो(ofp, "use lib \"./Perf-Trace-Util/lib\";\n");
	ख_लिखो(ofp, "use Perf::Trace::Core;\n");
	ख_लिखो(ofp, "use Perf::Trace::Context;\n");
	ख_लिखो(ofp, "use Perf::Trace::Util;\n\n");

	ख_लिखो(ofp, "sub trace_begin\n{\n\t# optional\n}\n\n");
	ख_लिखो(ofp, "sub trace_end\n{\n\t# optional\n}\n");


	ख_लिखो(ofp, "\न\
sub prपूर्णांक_backtrace\न\
अणु\न\
	my $callchain = shअगरt;\न\
	क्रम my $node (@$callchain)\न\
	अणु\न\
		अगर(exists $node->अणुsymपूर्ण)\न\
		अणु\न\
			म_लिखो( \"\\t[\\%%x] \\%%s\\n\", $node->अणुipपूर्ण, $node->अणुsymपूर्णअणुnameपूर्ण);\न\
		पूर्ण\न\
		अन्यथा\न\
		अणु\न\
			म_लिखो( \"\\t[\\%%x]\\n\", $nodeअणुipपूर्ण);\न\
		पूर्ण\न\
	पूर्ण\न\
पूर्ण\न\न\
");

	nr_events = tep_get_events_count(pevent);
	all_events = tep_list_events(pevent, TEP_EVENT_SORT_ID);

	क्रम (i = 0; all_events && i < nr_events; i++) अणु
		event = all_events[i];
		ख_लिखो(ofp, "sub %s::%s\n{\n", event->प्रणाली, event->name);
		ख_लिखो(ofp, "\tmy (");

		ख_लिखो(ofp, "$event_name, ");
		ख_लिखो(ofp, "$context, ");
		ख_लिखो(ofp, "$common_cpu, ");
		ख_लिखो(ofp, "$common_secs, ");
		ख_लिखो(ofp, "$common_nsecs,\n");
		ख_लिखो(ofp, "\t    $common_pid, ");
		ख_लिखो(ofp, "$common_comm, ");
		ख_लिखो(ofp, "$common_callchain,\n\t    ");

		not_first = 0;
		count = 0;

		क्रम (f = event->क्रमmat.fields; f; f = f->next) अणु
			अगर (not_first++)
				ख_लिखो(ofp, ", ");
			अगर (++count % 5 == 0)
				ख_लिखो(ofp, "\n\t    ");

			ख_लिखो(ofp, "$%s", f->name);
		पूर्ण
		ख_लिखो(ofp, ") = @_;\n\n");

		ख_लिखो(ofp, "\tprint_header($event_name, $common_cpu, "
			"$common_secs, $common_nsecs,\n\t             "
			"$common_pid, $common_comm, $common_callchain);\n\n");

		ख_लिखो(ofp, "\tprintf(\"");

		not_first = 0;
		count = 0;

		क्रम (f = event->क्रमmat.fields; f; f = f->next) अणु
			अगर (not_first++)
				ख_लिखो(ofp, ", ");
			अगर (count && count % 4 == 0) अणु
				ख_लिखो(ofp, "\".\n\t       \"");
			पूर्ण
			count++;

			ख_लिखो(ofp, "%s=", f->name);
			अगर (f->flags & TEP_FIELD_IS_STRING ||
			    f->flags & TEP_FIELD_IS_FLAG ||
			    f->flags & TEP_FIELD_IS_SYMBOLIC)
				ख_लिखो(ofp, "%%s");
			अन्यथा अगर (f->flags & TEP_FIELD_IS_SIGNED)
				ख_लिखो(ofp, "%%d");
			अन्यथा
				ख_लिखो(ofp, "%%u");
		पूर्ण

		ख_लिखो(ofp, "\\n\",\n\t       ");

		not_first = 0;
		count = 0;

		क्रम (f = event->क्रमmat.fields; f; f = f->next) अणु
			अगर (not_first++)
				ख_लिखो(ofp, ", ");

			अगर (++count % 5 == 0)
				ख_लिखो(ofp, "\n\t       ");

			अगर (f->flags & TEP_FIELD_IS_FLAG) अणु
				अगर ((count - 1) % 5 != 0) अणु
					ख_लिखो(ofp, "\n\t       ");
					count = 4;
				पूर्ण
				ख_लिखो(ofp, "flag_str(\"");
				ख_लिखो(ofp, "%s::%s\", ", event->प्रणाली,
					event->name);
				ख_लिखो(ofp, "\"%s\", $%s)", f->name,
					f->name);
			पूर्ण अन्यथा अगर (f->flags & TEP_FIELD_IS_SYMBOLIC) अणु
				अगर ((count - 1) % 5 != 0) अणु
					ख_लिखो(ofp, "\n\t       ");
					count = 4;
				पूर्ण
				ख_लिखो(ofp, "symbol_str(\"");
				ख_लिखो(ofp, "%s::%s\", ", event->प्रणाली,
					event->name);
				ख_लिखो(ofp, "\"%s\", $%s)", f->name,
					f->name);
			पूर्ण अन्यथा
				ख_लिखो(ofp, "$%s", f->name);
		पूर्ण

		ख_लिखो(ofp, ");\n\n");

		ख_लिखो(ofp, "\tprint_backtrace($common_callchain);\n");

		ख_लिखो(ofp, "}\n\n");
	पूर्ण

	ख_लिखो(ofp, "sub trace_unhandled\n{\n\tmy ($event_name, $context, "
		"$common_cpu, $common_secs, $common_nsecs,\n\t    "
		"$common_pid, $common_comm, $common_callchain) = @_;\n\n");

	ख_लिखो(ofp, "\tprint_header($event_name, $common_cpu, "
		"$common_secs, $common_nsecs,\n\t             $common_pid, "
		"$common_comm, $common_callchain);\n");
	ख_लिखो(ofp, "\tprint_backtrace($common_callchain);\n");
	ख_लिखो(ofp, "}\n\n");

	ख_लिखो(ofp, "sub print_header\n{\n"
		"\tmy ($event_name, $cpu, $secs, $nsecs, $pid, $comm) = @_;\n\n"
		"\tprintf(\"%%-20s %%5u %%05u.%%09u %%8u %%-20s \",\n\t       "
		"$event_name, $cpu, $secs, $nsecs, $pid, $comm);\n}\n");

	ख_लिखो(ofp,
		"\n# Packed byte string args of process_event():\n"
		"#\n"
		"# $event:\tunion perf_event\tutil/event.h\n"
		"# $attr:\tstruct perf_event_attr\tlinux/perf_event.h\n"
		"# $sample:\tstruct perf_sample\tutil/event.h\n"
		"# $raw_data:\tperf_sample->raw_data\tutil/event.h\n"
		"\n"
		"sub process_event\n"
		"{\n"
		"\tmy ($event, $attr, $sample, $raw_data) = @_;\n"
		"\n"
		"\tmy @event\t= unpack(\"LSS\", $event);\n"
		"\tmy @attr\t= unpack(\"LLQQQQQLLQQ\", $attr);\n"
		"\tmy @sample\t= unpack(\"QLLQQQQQLL\", $sample);\n"
		"\tmy @raw_data\t= unpack(\"C*\", $raw_data);\n"
		"\n"
		"\tuse Data::Dumper;\n"
		"\tprint Dumper \\@event, \\@attr, \\@sample, \\@raw_data;\n"
		"}\n");

	ख_बंद(ofp);

	ख_लिखो(मानक_त्रुटि, "generated Perl script: %s\n", fname);

	वापस 0;
पूर्ण

काष्ठा scripting_ops perl_scripting_ops = अणु
	.name = "Perl",
	.start_script = perl_start_script,
	.flush_script = perl_flush_script,
	.stop_script = perl_stop_script,
	.process_event = perl_process_event,
	.generate_script = perl_generate_script,
पूर्ण;
