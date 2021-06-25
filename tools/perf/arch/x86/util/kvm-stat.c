<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश "../../../util/kvm-stat.h"
#समावेश "../../../util/evsel.h"
#समावेश <यंत्र/svm.h>
#समावेश <यंत्र/vmx.h>
#समावेश <यंत्र/kvm.h>

define_निकास_reasons_table(vmx_निकास_reasons, VMX_EXIT_REASONS);
define_निकास_reasons_table(svm_निकास_reasons, SVM_EXIT_REASONS);

अटल काष्ठा kvm_events_ops निकास_events = अणु
	.is_begin_event = निकास_event_begin,
	.is_end_event = निकास_event_end,
	.decode_key = निकास_event_decode_key,
	.name = "VM-EXIT"
पूर्ण;

स्थिर अक्षर *vcpu_id_str = "vcpu_id";
स्थिर पूर्णांक decode_str_len = 20;
स्थिर अक्षर *kvm_निकास_reason = "exit_reason";
स्थिर अक्षर *kvm_entry_trace = "kvm:kvm_entry";
स्थिर अक्षर *kvm_निकास_trace = "kvm:kvm_exit";

/*
 * For the mmio events, we treat:
 * the समय of MMIO ग_लिखो: kvm_mmio(KVM_TRACE_MMIO_WRITE...) -> kvm_entry
 * the समय of MMIO पढ़ो: kvm_निकास -> kvm_mmio(KVM_TRACE_MMIO_READ...).
 */
अटल व्योम mmio_event_get_key(काष्ठा evsel *evsel, काष्ठा perf_sample *sample,
			       काष्ठा event_key *key)
अणु
	key->key  = evsel__पूर्णांकval(evsel, sample, "gpa");
	key->info = evsel__पूर्णांकval(evsel, sample, "type");
पूर्ण

#घोषणा KVM_TRACE_MMIO_READ_UNSATISFIED 0
#घोषणा KVM_TRACE_MMIO_READ 1
#घोषणा KVM_TRACE_MMIO_WRITE 2

अटल bool mmio_event_begin(काष्ठा evsel *evsel,
			     काष्ठा perf_sample *sample, काष्ठा event_key *key)
अणु
	/* MMIO पढ़ो begin event in kernel. */
	अगर (kvm_निकास_event(evsel))
		वापस true;

	/* MMIO ग_लिखो begin event in kernel. */
	अगर (!म_भेद(evsel->name, "kvm:kvm_mmio") &&
	    evsel__पूर्णांकval(evsel, sample, "type") == KVM_TRACE_MMIO_WRITE) अणु
		mmio_event_get_key(evsel, sample, key);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool mmio_event_end(काष्ठा evsel *evsel, काष्ठा perf_sample *sample,
			   काष्ठा event_key *key)
अणु
	/* MMIO ग_लिखो end event in kernel. */
	अगर (kvm_entry_event(evsel))
		वापस true;

	/* MMIO पढ़ो end event in kernel.*/
	अगर (!म_भेद(evsel->name, "kvm:kvm_mmio") &&
	    evsel__पूर्णांकval(evsel, sample, "type") == KVM_TRACE_MMIO_READ) अणु
		mmio_event_get_key(evsel, sample, key);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम mmio_event_decode_key(काष्ठा perf_kvm_stat *kvm __maybe_unused,
				  काष्ठा event_key *key,
				  अक्षर *decode)
अणु
	scnम_लिखो(decode, decode_str_len, "%#lx:%s",
		  (अचिन्हित दीर्घ)key->key,
		  key->info == KVM_TRACE_MMIO_WRITE ? "W" : "R");
पूर्ण

अटल काष्ठा kvm_events_ops mmio_events = अणु
	.is_begin_event = mmio_event_begin,
	.is_end_event = mmio_event_end,
	.decode_key = mmio_event_decode_key,
	.name = "MMIO Access"
पूर्ण;

 /* The समय of emulation pio access is from kvm_pio to kvm_entry. */
अटल व्योम ioport_event_get_key(काष्ठा evsel *evsel,
				 काष्ठा perf_sample *sample,
				 काष्ठा event_key *key)
अणु
	key->key  = evsel__पूर्णांकval(evsel, sample, "port");
	key->info = evsel__पूर्णांकval(evsel, sample, "rw");
पूर्ण

अटल bool ioport_event_begin(काष्ठा evsel *evsel,
			       काष्ठा perf_sample *sample,
			       काष्ठा event_key *key)
अणु
	अगर (!म_भेद(evsel->name, "kvm:kvm_pio")) अणु
		ioport_event_get_key(evsel, sample, key);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool ioport_event_end(काष्ठा evsel *evsel,
			     काष्ठा perf_sample *sample __maybe_unused,
			     काष्ठा event_key *key __maybe_unused)
अणु
	वापस kvm_entry_event(evsel);
पूर्ण

अटल व्योम ioport_event_decode_key(काष्ठा perf_kvm_stat *kvm __maybe_unused,
				    काष्ठा event_key *key,
				    अक्षर *decode)
अणु
	scnम_लिखो(decode, decode_str_len, "%#llx:%s",
		  (अचिन्हित दीर्घ दीर्घ)key->key,
		  key->info ? "POUT" : "PIN");
पूर्ण

अटल काष्ठा kvm_events_ops ioport_events = अणु
	.is_begin_event = ioport_event_begin,
	.is_end_event = ioport_event_end,
	.decode_key = ioport_event_decode_key,
	.name = "IO Port Access"
पूर्ण;

स्थिर अक्षर *kvm_events_tp[] = अणु
	"kvm:kvm_entry",
	"kvm:kvm_exit",
	"kvm:kvm_mmio",
	"kvm:kvm_pio",
	शून्य,
पूर्ण;

काष्ठा kvm_reg_events_ops kvm_reg_events_ops[] = अणु
	अणु .name = "vmexit", .ops = &निकास_events पूर्ण,
	अणु .name = "mmio", .ops = &mmio_events पूर्ण,
	अणु .name = "ioport", .ops = &ioport_events पूर्ण,
	अणु शून्य, शून्य पूर्ण,
पूर्ण;

स्थिर अक्षर * स्थिर kvm_skip_events[] = अणु
	"HLT",
	शून्य,
पूर्ण;

पूर्णांक cpu_isa_init(काष्ठा perf_kvm_stat *kvm, स्थिर अक्षर *cpuid)
अणु
	अगर (म_माला(cpuid, "Intel")) अणु
		kvm->निकास_reasons = vmx_निकास_reasons;
		kvm->निकास_reasons_isa = "VMX";
	पूर्ण अन्यथा अगर (म_माला(cpuid, "AMD") || म_माला(cpuid, "Hygon")) अणु
		kvm->निकास_reasons = svm_निकास_reasons;
		kvm->निकास_reasons_isa = "SVM";
	पूर्ण अन्यथा
		वापस -ENOTSUP;

	वापस 0;
पूर्ण
