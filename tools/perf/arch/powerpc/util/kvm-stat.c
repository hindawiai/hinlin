<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश "util/kvm-stat.h"
#समावेश "util/parse-events.h"
#समावेश "util/debug.h"
#समावेश "util/evsel.h"
#समावेश "util/evlist.h"
#समावेश "util/pmu.h"

#समावेश "book3s_hv_exits.h"
#समावेश "book3s_hcalls.h"
#समावेश <subcmd/parse-options.h>

#घोषणा NR_TPS 4

स्थिर अक्षर *vcpu_id_str = "vcpu_id";
स्थिर पूर्णांक decode_str_len = 40;
स्थिर अक्षर *kvm_entry_trace = "kvm_hv:kvm_guest_enter";
स्थिर अक्षर *kvm_निकास_trace = "kvm_hv:kvm_guest_exit";

define_निकास_reasons_table(hv_निकास_reasons, kvm_trace_symbol_निकास);
define_निकास_reasons_table(hcall_reasons, kvm_trace_symbol_hcall);

/* Tracepoपूर्णांकs specअगरic to ppc_book3s_hv */
स्थिर अक्षर *ppc_book3s_hv_kvm_tp[] = अणु
	"kvm_hv:kvm_guest_enter",
	"kvm_hv:kvm_guest_exit",
	"kvm_hv:kvm_hcall_enter",
	"kvm_hv:kvm_hcall_exit",
	शून्य,
पूर्ण;

/* 1 extra placeholder क्रम शून्य */
स्थिर अक्षर *kvm_events_tp[NR_TPS + 1];
स्थिर अक्षर *kvm_निकास_reason;

अटल व्योम hcall_event_get_key(काष्ठा evsel *evsel,
				काष्ठा perf_sample *sample,
				काष्ठा event_key *key)
अणु
	key->info = 0;
	key->key = evsel__पूर्णांकval(evsel, sample, "req");
पूर्ण

अटल स्थिर अक्षर *get_hcall_निकास_reason(u64 निकास_code)
अणु
	काष्ठा निकास_reasons_table *tbl = hcall_reasons;

	जबतक (tbl->reason != शून्य) अणु
		अगर (tbl->निकास_code == निकास_code)
			वापस tbl->reason;
		tbl++;
	पूर्ण

	pr_debug("Unknown hcall code: %lld\n",
	       (अचिन्हित दीर्घ दीर्घ)निकास_code);
	वापस "UNKNOWN";
पूर्ण

अटल bool hcall_event_end(काष्ठा evsel *evsel,
			    काष्ठा perf_sample *sample __maybe_unused,
			    काष्ठा event_key *key __maybe_unused)
अणु
	वापस (!म_भेद(evsel->name, kvm_events_tp[3]));
पूर्ण

अटल bool hcall_event_begin(काष्ठा evsel *evsel,
			      काष्ठा perf_sample *sample, काष्ठा event_key *key)
अणु
	अगर (!म_भेद(evsel->name, kvm_events_tp[2])) अणु
		hcall_event_get_key(evsel, sample, key);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
अटल व्योम hcall_event_decode_key(काष्ठा perf_kvm_stat *kvm __maybe_unused,
				   काष्ठा event_key *key,
				   अक्षर *decode)
अणु
	स्थिर अक्षर *hcall_reason = get_hcall_निकास_reason(key->key);

	scnम_लिखो(decode, decode_str_len, "%s", hcall_reason);
पूर्ण

अटल काष्ठा kvm_events_ops hcall_events = अणु
	.is_begin_event = hcall_event_begin,
	.is_end_event = hcall_event_end,
	.decode_key = hcall_event_decode_key,
	.name = "HCALL-EVENT",
पूर्ण;

अटल काष्ठा kvm_events_ops निकास_events = अणु
	.is_begin_event = निकास_event_begin,
	.is_end_event = निकास_event_end,
	.decode_key = निकास_event_decode_key,
	.name = "VM-EXIT"
पूर्ण;

काष्ठा kvm_reg_events_ops kvm_reg_events_ops[] = अणु
	अणु .name = "vmexit", .ops = &निकास_events पूर्ण,
	अणु .name = "hcall", .ops = &hcall_events पूर्ण,
	अणु शून्य, शून्य पूर्ण,
पूर्ण;

स्थिर अक्षर * स्थिर kvm_skip_events[] = अणु
	शून्य,
पूर्ण;


अटल पूर्णांक is_tracepoपूर्णांक_available(स्थिर अक्षर *str, काष्ठा evlist *evlist)
अणु
	काष्ठा parse_events_error err;
	पूर्णांक ret;

	bzero(&err, माप(err));
	ret = parse_events(evlist, str, &err);
	अगर (err.str)
		parse_events_prपूर्णांक_error(&err, "tracepoint");
	वापस ret;
पूर्ण

अटल पूर्णांक ppc__setup_book3s_hv(काष्ठा perf_kvm_stat *kvm,
				काष्ठा evlist *evlist)
अणु
	स्थिर अक्षर **events_ptr;
	पूर्णांक i, nr_tp = 0, err = -1;

	/* Check क्रम book3s_hv tracepoपूर्णांकs */
	क्रम (events_ptr = ppc_book3s_hv_kvm_tp; *events_ptr; events_ptr++) अणु
		err = is_tracepoपूर्णांक_available(*events_ptr, evlist);
		अगर (err)
			वापस -1;
		nr_tp++;
	पूर्ण

	क्रम (i = 0; i < nr_tp; i++)
		kvm_events_tp[i] = ppc_book3s_hv_kvm_tp[i];

	kvm_events_tp[i] = शून्य;
	kvm_निकास_reason = "trap";
	kvm->निकास_reasons = hv_निकास_reasons;
	kvm->निकास_reasons_isa = "HV";

	वापस 0;
पूर्ण

/* Wrapper to setup kvm tracepoपूर्णांकs */
अटल पूर्णांक ppc__setup_kvm_tp(काष्ठा perf_kvm_stat *kvm)
अणु
	काष्ठा evlist *evlist = evlist__new();

	अगर (evlist == शून्य)
		वापस -ENOMEM;

	/* Right now, only supported on book3s_hv */
	वापस ppc__setup_book3s_hv(kvm, evlist);
पूर्ण

पूर्णांक setup_kvm_events_tp(काष्ठा perf_kvm_stat *kvm)
अणु
	वापस ppc__setup_kvm_tp(kvm);
पूर्ण

पूर्णांक cpu_isa_init(काष्ठा perf_kvm_stat *kvm, स्थिर अक्षर *cpuid __maybe_unused)
अणु
	पूर्णांक ret;

	ret = ppc__setup_kvm_tp(kvm);
	अगर (ret) अणु
		kvm->निकास_reasons = शून्य;
		kvm->निकास_reasons_isa = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * In हाल of घातerpc architecture, pmu रेजिस्टरs are programmable
 * by guest kernel. So monitoring guest via host may not provide
 * valid samples with शेष 'cycles' event. It is better to use
 * 'trace_imc/trace_cycles' event क्रम guest profiling, since it
 * can track the guest inकाष्ठाion poपूर्णांकer in the trace-record.
 *
 * Function to parse the arguments and वापस appropriate values.
 */
पूर्णांक kvm_add_शेष_arch_event(पूर्णांक *argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर **पंचांगp;
	bool event = false;
	पूर्णांक i, j = *argc;

	स्थिर काष्ठा option event_options[] = अणु
		OPT_BOOLEAN('e', "event", &event, शून्य),
		OPT_END()
	पूर्ण;

	पंचांगp = सुस्मृति(j + 1, माप(अक्षर *));
	अगर (!पंचांगp)
		वापस -EINVAL;

	क्रम (i = 0; i < j; i++)
		पंचांगp[i] = argv[i];

	parse_options(j, पंचांगp, event_options, शून्य, PARSE_OPT_KEEP_UNKNOWN);
	अगर (!event) अणु
		अगर (pmu_have_event("trace_imc", "trace_cycles")) अणु
			argv[j++] = strdup("-e");
			argv[j++] = strdup("trace_imc/trace_cycles/");
			*argc += 2;
		पूर्ण अन्यथा अणु
			मुक्त(पंचांगp);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	मुक्त(पंचांगp);
	वापस 0;
पूर्ण
