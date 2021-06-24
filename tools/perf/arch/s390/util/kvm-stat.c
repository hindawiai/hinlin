<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Arch specअगरic functions क्रम perf kvm stat.
 *
 * Copyright 2014 IBM Corp.
 * Author(s): Alexander Yarygin <yarygin@linux.vnet.ibm.com>
 */

#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश "../../util/kvm-stat.h"
#समावेश "../../util/evsel.h"
#समावेश <यंत्र/sie.h>

define_निकास_reasons_table(sie_निकास_reasons, sie_पूर्णांकercept_code);
define_निकास_reasons_table(sie_icpt_insn_codes, icpt_insn_codes);
define_निकास_reasons_table(sie_sigp_order_codes, sigp_order_codes);
define_निकास_reasons_table(sie_diagnose_codes, diagnose_codes);
define_निकास_reasons_table(sie_icpt_prog_codes, icpt_prog_codes);

स्थिर अक्षर *vcpu_id_str = "id";
स्थिर पूर्णांक decode_str_len = 40;
स्थिर अक्षर *kvm_निकास_reason = "icptcode";
स्थिर अक्षर *kvm_entry_trace = "kvm:kvm_s390_sie_enter";
स्थिर अक्षर *kvm_निकास_trace = "kvm:kvm_s390_sie_exit";

अटल व्योम event_icpt_insn_get_key(काष्ठा evsel *evsel,
				    काष्ठा perf_sample *sample,
				    काष्ठा event_key *key)
अणु
	अचिन्हित दीर्घ insn;

	insn = evsel__पूर्णांकval(evsel, sample, "instruction");
	key->key = icpt_insn_decoder(insn);
	key->निकास_reasons = sie_icpt_insn_codes;
पूर्ण

अटल व्योम event_sigp_get_key(काष्ठा evsel *evsel,
			       काष्ठा perf_sample *sample,
			       काष्ठा event_key *key)
अणु
	key->key = evsel__पूर्णांकval(evsel, sample, "order_code");
	key->निकास_reasons = sie_sigp_order_codes;
पूर्ण

अटल व्योम event_diag_get_key(काष्ठा evsel *evsel,
			       काष्ठा perf_sample *sample,
			       काष्ठा event_key *key)
अणु
	key->key = evsel__पूर्णांकval(evsel, sample, "code");
	key->निकास_reasons = sie_diagnose_codes;
पूर्ण

अटल व्योम event_icpt_prog_get_key(काष्ठा evsel *evsel,
				    काष्ठा perf_sample *sample,
				    काष्ठा event_key *key)
अणु
	key->key = evsel__पूर्णांकval(evsel, sample, "code");
	key->निकास_reasons = sie_icpt_prog_codes;
पूर्ण

अटल काष्ठा child_event_ops child_events[] = अणु
	अणु .name = "kvm:kvm_s390_intercept_instruction",
	  .get_key = event_icpt_insn_get_key पूर्ण,
	अणु .name = "kvm:kvm_s390_handle_sigp",
	  .get_key = event_sigp_get_key पूर्ण,
	अणु .name = "kvm:kvm_s390_handle_diag",
	  .get_key = event_diag_get_key पूर्ण,
	अणु .name = "kvm:kvm_s390_intercept_prog",
	  .get_key = event_icpt_prog_get_key पूर्ण,
	अणु शून्य, शून्य पूर्ण,
पूर्ण;

अटल काष्ठा kvm_events_ops निकास_events = अणु
	.is_begin_event = निकास_event_begin,
	.is_end_event = निकास_event_end,
	.child_ops = child_events,
	.decode_key = निकास_event_decode_key,
	.name = "VM-EXIT"
पूर्ण;

स्थिर अक्षर *kvm_events_tp[] = अणु
	"kvm:kvm_s390_sie_enter",
	"kvm:kvm_s390_sie_exit",
	"kvm:kvm_s390_intercept_instruction",
	"kvm:kvm_s390_handle_sigp",
	"kvm:kvm_s390_handle_diag",
	"kvm:kvm_s390_intercept_prog",
	शून्य,
पूर्ण;

काष्ठा kvm_reg_events_ops kvm_reg_events_ops[] = अणु
	अणु .name = "vmexit", .ops = &निकास_events पूर्ण,
	अणु शून्य, शून्य पूर्ण,
पूर्ण;

स्थिर अक्षर * स्थिर kvm_skip_events[] = अणु
	"Wait state",
	शून्य,
पूर्ण;

पूर्णांक cpu_isa_init(काष्ठा perf_kvm_stat *kvm, स्थिर अक्षर *cpuid)
अणु
	अगर (म_माला(cpuid, "IBM")) अणु
		kvm->निकास_reasons = sie_निकास_reasons;
		kvm->निकास_reasons_isa = "SIE";
	पूर्ण अन्यथा
		वापस -ENOTSUP;

	वापस 0;
पूर्ण
