<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <memory.h>
#समावेश "../../../util/evsel.h"
#समावेश "../../../util/kvm-stat.h"
#समावेश "arm64_exception_types.h"
#समावेश "debug.h"

define_निकास_reasons_table(arm64_निकास_reasons, kvm_arm_exception_type);
define_निकास_reasons_table(arm64_trap_निकास_reasons, kvm_arm_exception_class);

स्थिर अक्षर *kvm_trap_निकास_reason = "esr_ec";
स्थिर अक्षर *vcpu_id_str = "id";
स्थिर पूर्णांक decode_str_len = 20;
स्थिर अक्षर *kvm_निकास_reason = "ret";
स्थिर अक्षर *kvm_entry_trace = "kvm:kvm_entry";
स्थिर अक्षर *kvm_निकास_trace = "kvm:kvm_exit";

स्थिर अक्षर *kvm_events_tp[] = अणु
	"kvm:kvm_entry",
	"kvm:kvm_exit",
	शून्य,
पूर्ण;

अटल व्योम event_get_key(काष्ठा evsel *evsel,
			  काष्ठा perf_sample *sample,
			  काष्ठा event_key *key)
अणु
	key->info = 0;
	key->key = evsel__पूर्णांकval(evsel, sample, kvm_निकास_reason);
	key->निकास_reasons = arm64_निकास_reasons;

	/*
	 * TRAP exceptions carry exception class info in esr_ec field
	 * and, hence, we need to use a dअगरferent निकास_reasons table to
	 * properly decode event's est_ec.
	 */
	अगर (key->key == ARM_EXCEPTION_TRAP) अणु
		key->key = evsel__पूर्णांकval(evsel, sample, kvm_trap_निकास_reason);
		key->निकास_reasons = arm64_trap_निकास_reasons;
	पूर्ण
पूर्ण

अटल bool event_begin(काष्ठा evsel *evsel,
			काष्ठा perf_sample *sample __maybe_unused,
			काष्ठा event_key *key __maybe_unused)
अणु
	वापस !म_भेद(evsel->name, kvm_entry_trace);
पूर्ण

अटल bool event_end(काष्ठा evsel *evsel,
		      काष्ठा perf_sample *sample,
		      काष्ठा event_key *key)
अणु
	अगर (!म_भेद(evsel->name, kvm_निकास_trace)) अणु
		event_get_key(evsel, sample, key);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा kvm_events_ops निकास_events = अणु
	.is_begin_event = event_begin,
	.is_end_event	= event_end,
	.decode_key	= निकास_event_decode_key,
	.name		= "VM-EXIT"
पूर्ण;

काष्ठा kvm_reg_events_ops kvm_reg_events_ops[] = अणु
	अणु
		.name	= "vmexit",
		.ops	= &निकास_events,
	पूर्ण,
	अणु शून्य, शून्य पूर्ण,
पूर्ण;

स्थिर अक्षर * स्थिर kvm_skip_events[] = अणु
	शून्य,
पूर्ण;

पूर्णांक cpu_isa_init(काष्ठा perf_kvm_stat *kvm, स्थिर अक्षर *cpuid __maybe_unused)
अणु
	kvm->निकास_reasons_isa = "arm64";
	वापस 0;
पूर्ण
