<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook

#समावेश <मानक_निवेशt.h>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>
#समावेश <linux/bpf.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/types.h>
#समावेश <bpf/bpf_helpers.h>

प्रकार uपूर्णांक32_t pid_t;
काष्ठा task_काष्ठा अणुपूर्ण;

#घोषणा TASK_COMM_LEN 16
#घोषणा PERF_MAX_STACK_DEPTH 127

#घोषणा STROBE_TYPE_INVALID 0
#घोषणा STROBE_TYPE_INT 1
#घोषणा STROBE_TYPE_STR 2
#घोषणा STROBE_TYPE_MAP 3

#घोषणा STACK_TABLE_EPOCH_SHIFT 20
#घोषणा STROBE_MAX_STR_LEN 1
#घोषणा STROBE_MAX_CFGS 32
#घोषणा STROBE_MAX_PAYLOAD						\
	(STROBE_MAX_STRS * STROBE_MAX_STR_LEN +				\
	STROBE_MAX_MAPS * (1 + STROBE_MAX_MAP_ENTRIES * 2) * STROBE_MAX_STR_LEN)

काष्ठा strobe_value_header अणु
	/*
	 * meaning depends on type:
	 * 1. पूर्णांक: 0, अगर value not set, 1 otherwise
	 * 2. str: 1 always, whether value is set or not is determined by ptr
	 * 3. map: 1 always, poपूर्णांकer poपूर्णांकs to additional काष्ठा with number
	 *    of entries (up to STROBE_MAX_MAP_ENTRIES)
	 */
	uपूर्णांक16_t len;
	/*
	 * _reserved might be used क्रम some future fields/flags, but we always
	 * want to keep strobe_value_header to be 8 bytes, so BPF can पढ़ो 16
	 * bytes in one go and get both header and value
	 */
	uपूर्णांक8_t _reserved[6];
पूर्ण;

/*
 * strobe_value_generic is used from BPF probe only, but needs to be a जोड़
 * of strobe_value_पूर्णांक/strobe_value_str/strobe_value_map
 */
काष्ठा strobe_value_generic अणु
	काष्ठा strobe_value_header header;
	जोड़ अणु
		पूर्णांक64_t val;
		व्योम *ptr;
	पूर्ण;
पूर्ण;

काष्ठा strobe_value_पूर्णांक अणु
	काष्ठा strobe_value_header header;
	पूर्णांक64_t value;
पूर्ण;

काष्ठा strobe_value_str अणु
	काष्ठा strobe_value_header header;
	स्थिर अक्षर* value;
पूर्ण;

काष्ठा strobe_value_map अणु
	काष्ठा strobe_value_header header;
	स्थिर काष्ठा strobe_map_raw* value;
पूर्ण;

काष्ठा strobe_map_entry अणु
	स्थिर अक्षर* key;
	स्थिर अक्षर* val;
पूर्ण;

/*
 * Map of C-string key/value pairs with fixed maximum capacity. Each map has
 * corresponding पूर्णांक64 ID, which application can use (or ignore) in whatever
 * way appropriate. Map is "write-only", there is no way to get data out of
 * map. Map is पूर्णांकended to be used to provide metadata क्रम profilers and is
 * not to be used क्रम पूर्णांकernal in-app communication. All methods are
 * thपढ़ो-safe.
 */
काष्ठा strobe_map_raw अणु
	/*
	 * general purpose unique ID that's up to application to decide
	 * whether and how to use; क्रम request metadata use हाल id is unique
	 * request ID that's used to match metadata with stack traces on
	 * Strobelight backend side
	 */
	पूर्णांक64_t id;
	/* number of used entries in map */
	पूर्णांक64_t cnt;
	/*
	 * having अस्थिर करोesn't change anything on BPF side, but clang
	 * emits warnings क्रम passing `अस्थिर स्थिर अक्षर *` पूर्णांकo
	 * bpf_probe_पढ़ो_user_str that expects just `स्थिर अक्षर *`
	 */
	स्थिर अक्षर* tag;
	/*
	 * key/value entries, each consisting of 2 poपूर्णांकers to key and value
	 * C strings
	 */
	काष्ठा strobe_map_entry entries[STROBE_MAX_MAP_ENTRIES];
पूर्ण;

/* Following values define supported values of TLS mode */
#घोषणा TLS_NOT_SET -1
#घोषणा TLS_LOCAL_EXEC 0
#घोषणा TLS_IMM_EXEC 1
#घोषणा TLS_GENERAL_DYN 2

/*
 * काष्ठाure that universally represents TLS location (both क्रम अटल
 * executables and shared libraries)
 */
काष्ठा strobe_value_loc अणु
	/*
	 * tls_mode defines what TLS mode was used क्रम particular metavariable:
	 * - -1 (TLS_NOT_SET) - no metavariable;
	 * - 0 (TLS_LOCAL_EXEC) - Local Executable mode;
	 * - 1 (TLS_IMM_EXEC) - Immediate Executable mode;
	 * - 2 (TLS_GENERAL_DYN) - General Dynamic mode;
	 * Local Dynamic mode is not yet supported, because never seen in
	 * practice.  Mode defines how offset field is पूर्णांकerpreted. See
	 * calc_location() in below क्रम details.
	 */
	पूर्णांक64_t tls_mode;
	/*
	 * TLS_LOCAL_EXEC: offset from thपढ़ो poपूर्णांकer (fs:0 क्रम x86-64,
	 * tpidr_el0 क्रम aarch64).
	 * TLS_IMM_EXEC: असलolute address of GOT entry containing offset
	 * from thपढ़ो poपूर्णांकer;
	 * TLS_GENERAL_DYN: असलolute addres of द्विगुन GOT entry
	 * containing tls_index_t काष्ठा;
	 */
	पूर्णांक64_t offset;
पूर्ण;

काष्ठा strobemeta_cfg अणु
	पूर्णांक64_t req_meta_idx;
	काष्ठा strobe_value_loc पूर्णांक_locs[STROBE_MAX_INTS];
	काष्ठा strobe_value_loc str_locs[STROBE_MAX_STRS];
	काष्ठा strobe_value_loc map_locs[STROBE_MAX_MAPS];
पूर्ण;

काष्ठा strobe_map_descr अणु
	uपूर्णांक64_t id;
	पूर्णांक16_t tag_len;
	/*
	 * cnt <0 - map value isn't set;
	 * 0 - map has id set, but no key/value entries
	 */
	पूर्णांक16_t cnt;
	/*
	 * both key_lens[i] and val_lens[i] should be >0 क्रम present key/value
	 * entry
	 */
	uपूर्णांक16_t key_lens[STROBE_MAX_MAP_ENTRIES];
	uपूर्णांक16_t val_lens[STROBE_MAX_MAP_ENTRIES];
पूर्ण;

काष्ठा strobemeta_payload अणु
	/* req_id has valid request ID, अगर req_meta_valid == 1 */
	पूर्णांक64_t req_id;
	uपूर्णांक8_t req_meta_valid;
	/*
	 * mask has Nth bit set to 1, अगर Nth metavar was present and
	 * successfully पढ़ो
	 */
	uपूर्णांक64_t पूर्णांक_vals_set_mask;
	पूर्णांक64_t पूर्णांक_vals[STROBE_MAX_INTS];
	/* len is >0 क्रम present values */
	uपूर्णांक16_t str_lens[STROBE_MAX_STRS];
	/* अगर map_descrs[i].cnt == -1, metavar is not present/set */
	काष्ठा strobe_map_descr map_descrs[STROBE_MAX_MAPS];
	/*
	 * payload has compactly packed values of str and map variables in the
	 * क्रमm: strval1\0strval2\0map1key1\0map1val1\0map2key1\0map2val1\0
	 * (and so on); str_lens[i], key_lens[i] and val_lens[i] determines
	 * value length
	 */
	अक्षर payload[STROBE_MAX_PAYLOAD];
पूर्ण;

काष्ठा strobelight_bpf_sample अणु
	uपूर्णांक64_t kसमय;
	अक्षर comm[TASK_COMM_LEN];
	pid_t pid;
	पूर्णांक user_stack_id;
	पूर्णांक kernel_stack_id;
	पूर्णांक has_meta;
	काष्ठा strobemeta_payload metadata;
	/*
	 * makes it possible to pass (<real payload size> + 1) as data size to
	 * perf_submit() to aव्योम perf_submit's paranoia about passing zero as
	 * size, as it deduces that <real payload size> might be
	 * **theoretically** zero
	 */
	अक्षर dummy_safeguard;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERF_EVENT_ARRAY);
	__uपूर्णांक(max_entries, 32);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण samples SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_STACK_TRACE);
	__uपूर्णांक(max_entries, 16);
	__uपूर्णांक(key_size, माप(uपूर्णांक32_t));
	__uपूर्णांक(value_size, माप(uपूर्णांक64_t) * PERF_MAX_STACK_DEPTH);
पूर्ण stacks_0 SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_STACK_TRACE);
	__uपूर्णांक(max_entries, 16);
	__uपूर्णांक(key_size, माप(uपूर्णांक32_t));
	__uपूर्णांक(value_size, माप(uपूर्णांक64_t) * PERF_MAX_STACK_DEPTH);
पूर्ण stacks_1 SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, 1);
	__type(key, uपूर्णांक32_t);
	__type(value, काष्ठा strobelight_bpf_sample);
पूर्ण sample_heap SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PERCPU_ARRAY);
	__uपूर्णांक(max_entries, STROBE_MAX_CFGS);
	__type(key, pid_t);
	__type(value, काष्ठा strobemeta_cfg);
पूर्ण strobemeta_cfgs SEC(".maps");

/* Type क्रम the dtv.  */
/* https://github.com/lattera/glibc/blob/master/nptl/sysdeps/x86_64/tls.h#L34 */
प्रकार जोड़ dtv अणु
	माप_प्रकार counter;
	काष्ठा अणु
		व्योम* val;
		bool is_अटल;
	पूर्ण poपूर्णांकer;
पूर्ण dtv_t;

/* Partial definition क्रम tcbhead_t */
/* https://github.com/bminor/glibc/blob/master/sysdeps/x86_64/nptl/tls.h#L42 */
काष्ठा tcbhead अणु
	व्योम* tcb;
	dtv_t* dtv;
पूर्ण;

/*
 * TLS module/offset inक्रमmation क्रम shared library हाल.
 * For x86-64, this is mapped onto two entries in GOT.
 * For aarch64, this is poपूर्णांकed to by second GOT entry.
 */
काष्ठा tls_index अणु
	uपूर्णांक64_t module;
	uपूर्णांक64_t offset;
पूर्ण;

#अगर_घोषित SUBPROGS
__noअंतरभूत
#अन्यथा
__always_अंतरभूत
#पूर्ण_अगर
अटल व्योम *calc_location(काष्ठा strobe_value_loc *loc, व्योम *tls_base)
अणु
	/*
	 * tls_mode value is:
	 * - -1 (TLS_NOT_SET), अगर no metavar is present;
	 * - 0 (TLS_LOCAL_EXEC), अगर metavar uses Local Executable mode of TLS
	 * (offset from fs:0 क्रम x86-64 or tpidr_el0 क्रम aarch64);
	 * - 1 (TLS_IMM_EXEC), अगर metavar uses Immediate Executable mode of TLS;
	 * - 2 (TLS_GENERAL_DYN), अगर metavar uses General Dynamic mode of TLS;
	 * This schema allows to use something like:
	 * (tls_mode + 1) * (tls_base + offset)
	 * to get शून्य क्रम "no metavar" location, or correct poपूर्णांकer क्रम local
	 * executable mode without करोing extra अगरs.
	 */
	अगर (loc->tls_mode <= TLS_LOCAL_EXEC) अणु
		/* अटल executable is simple, we just have offset from
		 * tls_base */
		व्योम *addr = tls_base + loc->offset;
		/* multiply by (tls_mode + 1) to get शून्य, अगर we have no
		 * metavar in this slot */
		वापस (व्योम *)((loc->tls_mode + 1) * (पूर्णांक64_t)addr);
	पूर्ण
	/*
	 * Other modes are more complicated, we need to jump through few hoops.
	 *
	 * For immediate executable mode (currently supported only क्रम aarch64):
	 *  - loc->offset is poपूर्णांकing to a GOT entry containing fixed offset
	 *  relative to tls_base;
	 *
	 * For general dynamic mode:
	 *  - loc->offset is poपूर्णांकing to a beginning of द्विगुन GOT entries;
	 *  - (क्रम aarch64 only) second entry poपूर्णांकs to tls_index_t काष्ठा;
	 *  - (क्रम x86-64 only) two GOT entries are alपढ़ोy tls_index_t;
	 *  - tls_index_t->module is used to find start of TLS section in
	 *  which variable resides;
	 *  - tls_index_t->offset provides offset within that TLS section,
	 *  poपूर्णांकing to value of variable.
	 */
	काष्ठा tls_index tls_index;
	dtv_t *dtv;
	व्योम *tls_ptr;

	bpf_probe_पढ़ो_user(&tls_index, माप(काष्ठा tls_index),
			    (व्योम *)loc->offset);
	/* valid module index is always positive */
	अगर (tls_index.module > 0) अणु
		/* dtv = ((काष्ठा tcbhead *)tls_base)->dtv[tls_index.module] */
		bpf_probe_पढ़ो_user(&dtv, माप(dtv),
				    &((काष्ठा tcbhead *)tls_base)->dtv);
		dtv += tls_index.module;
	पूर्ण अन्यथा अणु
		dtv = शून्य;
	पूर्ण
	bpf_probe_पढ़ो_user(&tls_ptr, माप(व्योम *), dtv);
	/* अगर poपूर्णांकer has (व्योम *)-1 value, then TLS wasn't initialized yet */
	वापस tls_ptr && tls_ptr != (व्योम *)-1
		? tls_ptr + tls_index.offset
		: शून्य;
पूर्ण

#अगर_घोषित SUBPROGS
__noअंतरभूत
#अन्यथा
__always_अंतरभूत
#पूर्ण_अगर
अटल व्योम पढ़ो_पूर्णांक_var(काष्ठा strobemeta_cfg *cfg,
			 माप_प्रकार idx, व्योम *tls_base,
			 काष्ठा strobe_value_generic *value,
			 काष्ठा strobemeta_payload *data)
अणु
	व्योम *location = calc_location(&cfg->पूर्णांक_locs[idx], tls_base);
	अगर (!location)
		वापस;

	bpf_probe_पढ़ो_user(value, माप(काष्ठा strobe_value_generic), location);
	data->पूर्णांक_vals[idx] = value->val;
	अगर (value->header.len)
		data->पूर्णांक_vals_set_mask |= (1 << idx);
पूर्ण

अटल __always_अंतरभूत uपूर्णांक64_t पढ़ो_str_var(काष्ठा strobemeta_cfg *cfg,
					     माप_प्रकार idx, व्योम *tls_base,
					     काष्ठा strobe_value_generic *value,
					     काष्ठा strobemeta_payload *data,
					     व्योम *payload)
अणु
	व्योम *location;
	uपूर्णांक32_t len;

	data->str_lens[idx] = 0;
	location = calc_location(&cfg->str_locs[idx], tls_base);
	अगर (!location)
		वापस 0;

	bpf_probe_पढ़ो_user(value, माप(काष्ठा strobe_value_generic), location);
	len = bpf_probe_पढ़ो_user_str(payload, STROBE_MAX_STR_LEN, value->ptr);
	/*
	 * अगर bpf_probe_पढ़ो_user_str वापसs error (<0), due to casting to
	 * unsinged पूर्णांक, it will become big number, so next check is
	 * sufficient to check क्रम errors AND prove to BPF verअगरier, that
	 * bpf_probe_पढ़ो_user_str won't वापस anything bigger than
	 * STROBE_MAX_STR_LEN
	 */
	अगर (len > STROBE_MAX_STR_LEN)
		वापस 0;

	data->str_lens[idx] = len;
	वापस len;
पूर्ण

अटल __always_अंतरभूत व्योम *पढ़ो_map_var(काष्ठा strobemeta_cfg *cfg,
					  माप_प्रकार idx, व्योम *tls_base,
					  काष्ठा strobe_value_generic *value,
					  काष्ठा strobemeta_payload *data,
					  व्योम *payload)
अणु
	काष्ठा strobe_map_descr* descr = &data->map_descrs[idx];
	काष्ठा strobe_map_raw map;
	व्योम *location;
	uपूर्णांक32_t len;
	पूर्णांक i;

	descr->tag_len = 0; /* presume no tag is set */
	descr->cnt = -1; /* presume no value is set */

	location = calc_location(&cfg->map_locs[idx], tls_base);
	अगर (!location)
		वापस payload;

	bpf_probe_पढ़ो_user(value, माप(काष्ठा strobe_value_generic), location);
	अगर (bpf_probe_पढ़ो_user(&map, माप(काष्ठा strobe_map_raw), value->ptr))
		वापस payload;

	descr->id = map.id;
	descr->cnt = map.cnt;
	अगर (cfg->req_meta_idx == idx) अणु
		data->req_id = map.id;
		data->req_meta_valid = 1;
	पूर्ण

	len = bpf_probe_पढ़ो_user_str(payload, STROBE_MAX_STR_LEN, map.tag);
	अगर (len <= STROBE_MAX_STR_LEN) अणु
		descr->tag_len = len;
		payload += len;
	पूर्ण

#अगर_घोषित NO_UNROLL
#आशय clang loop unroll(disable)
#अन्यथा
#आशय unroll
#पूर्ण_अगर
	क्रम (पूर्णांक i = 0; i < STROBE_MAX_MAP_ENTRIES; ++i) अणु
		अगर (i >= map.cnt)
			अवरोध;

		descr->key_lens[i] = 0;
		len = bpf_probe_पढ़ो_user_str(payload, STROBE_MAX_STR_LEN,
					      map.entries[i].key);
		अगर (len <= STROBE_MAX_STR_LEN) अणु
			descr->key_lens[i] = len;
			payload += len;
		पूर्ण
		descr->val_lens[i] = 0;
		len = bpf_probe_पढ़ो_user_str(payload, STROBE_MAX_STR_LEN,
					      map.entries[i].val);
		अगर (len <= STROBE_MAX_STR_LEN) अणु
			descr->val_lens[i] = len;
			payload += len;
		पूर्ण
	पूर्ण

	वापस payload;
पूर्ण

/*
 * पढ़ो_strobe_meta वापसs शून्य, अगर no metadata was पढ़ो; otherwise वापसs
 * poपूर्णांकer to *right after* payload ends
 */
#अगर_घोषित SUBPROGS
__noअंतरभूत
#अन्यथा
__always_अंतरभूत
#पूर्ण_अगर
अटल व्योम *पढ़ो_strobe_meta(काष्ठा task_काष्ठा *task,
			      काष्ठा strobemeta_payload *data)
अणु
	pid_t pid = bpf_get_current_pid_tgid() >> 32;
	काष्ठा strobe_value_generic value = अणु0पूर्ण;
	काष्ठा strobemeta_cfg *cfg;
	व्योम *tls_base, *payload;

	cfg = bpf_map_lookup_elem(&strobemeta_cfgs, &pid);
	अगर (!cfg)
		वापस शून्य;

	data->पूर्णांक_vals_set_mask = 0;
	data->req_meta_valid = 0;
	payload = data->payload;
	/*
	 * we करोn't have काष्ठा task_काष्ठा definition, it should be:
	 * tls_base = (व्योम *)task->thपढ़ो.fsbase;
	 */
	tls_base = (व्योम *)task;

#अगर_घोषित NO_UNROLL
#आशय clang loop unroll(disable)
#अन्यथा
#आशय unroll
#पूर्ण_अगर
	क्रम (पूर्णांक i = 0; i < STROBE_MAX_INTS; ++i) अणु
		पढ़ो_पूर्णांक_var(cfg, i, tls_base, &value, data);
	पूर्ण
#अगर_घोषित NO_UNROLL
#आशय clang loop unroll(disable)
#अन्यथा
#आशय unroll
#पूर्ण_अगर
	क्रम (पूर्णांक i = 0; i < STROBE_MAX_STRS; ++i) अणु
		payload += पढ़ो_str_var(cfg, i, tls_base, &value, data, payload);
	पूर्ण
#अगर_घोषित NO_UNROLL
#आशय clang loop unroll(disable)
#अन्यथा
#आशय unroll
#पूर्ण_अगर
	क्रम (पूर्णांक i = 0; i < STROBE_MAX_MAPS; ++i) अणु
		payload = पढ़ो_map_var(cfg, i, tls_base, &value, data, payload);
	पूर्ण
	/*
	 * वापस poपूर्णांकer right after end of payload, so it's possible to
	 * calculate exact amount of useful data that needs to be sent
	 */
	वापस payload;
पूर्ण

SEC("raw_tracepoint/kfree_skb")
पूर्णांक on_event(काष्ठा pt_regs *ctx) अणु
	pid_t pid =  bpf_get_current_pid_tgid() >> 32;
	काष्ठा strobelight_bpf_sample* sample;
	काष्ठा task_काष्ठा *task;
	uपूर्णांक32_t zero = 0;
	uपूर्णांक64_t kसमय_ns;
	व्योम *sample_end;

	sample = bpf_map_lookup_elem(&sample_heap, &zero);
	अगर (!sample)
		वापस 0; /* this will never happen */

	sample->pid = pid;
	bpf_get_current_comm(&sample->comm, TASK_COMM_LEN);
	kसमय_ns = bpf_kसमय_get_ns();
	sample->kसमय = kसमय_ns;

	task = (काष्ठा task_काष्ठा *)bpf_get_current_task();
	sample_end = पढ़ो_strobe_meta(task, &sample->metadata);
	sample->has_meta = sample_end != शून्य;
	sample_end = sample_end ? : &sample->metadata;

	अगर ((kसमय_ns >> STACK_TABLE_EPOCH_SHIFT) & 1) अणु
		sample->kernel_stack_id = bpf_get_stackid(ctx, &stacks_1, 0);
		sample->user_stack_id = bpf_get_stackid(ctx, &stacks_1, BPF_F_USER_STACK);
	पूर्ण अन्यथा अणु
		sample->kernel_stack_id = bpf_get_stackid(ctx, &stacks_0, 0);
		sample->user_stack_id = bpf_get_stackid(ctx, &stacks_0, BPF_F_USER_STACK);
	पूर्ण

	uपूर्णांक64_t sample_size = sample_end - (व्योम *)sample;
	/* should always be true */
	अगर (sample_size < माप(काष्ठा strobelight_bpf_sample))
		bpf_perf_event_output(ctx, &samples, 0, sample, 1 + sample_size);
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
