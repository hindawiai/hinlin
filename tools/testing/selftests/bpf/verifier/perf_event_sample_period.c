<शैली गुरु>
अणु
	"check bpf_perf_event_data->sample_period byte load permitted",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_0, 0),
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा bpf_perf_event_data, sample_period)),
#अन्यथा
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा bpf_perf_event_data, sample_period) + 7),
#पूर्ण_अगर
	BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_PERF_EVENT,
पूर्ण,
अणु
	"check bpf_perf_event_data->sample_period half load permitted",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_0, 0),
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
	BPF_LDX_MEM(BPF_H, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा bpf_perf_event_data, sample_period)),
#अन्यथा
	BPF_LDX_MEM(BPF_H, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा bpf_perf_event_data, sample_period) + 6),
#पूर्ण_अगर
	BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_PERF_EVENT,
पूर्ण,
अणु
	"check bpf_perf_event_data->sample_period word load permitted",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_0, 0),
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा bpf_perf_event_data, sample_period)),
#अन्यथा
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा bpf_perf_event_data, sample_period) + 4),
#पूर्ण_अगर
	BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_PERF_EVENT,
पूर्ण,
अणु
	"check bpf_perf_event_data->sample_period dword load permitted",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा bpf_perf_event_data, sample_period)),
	BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_PERF_EVENT,
पूर्ण,
