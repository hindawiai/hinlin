<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * common eBPF ELF operations.
 *
 * Copyright (C) 2013-2015 Alexei Starovoitov <ast@kernel.org>
 * Copyright (C) 2015 Wang Nan <wangnan0@huawei.com>
 * Copyright (C) 2015 Huawei Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation;
 * version 2.1 of the License (not later!)
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License aदीर्घ with this program; अगर not,  see <http://www.gnu.org/licenses>
 */

#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <memory.h>
#समावेश <unistd.h>
#समावेश <यंत्र/unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/bpf.h>
#समावेश "bpf.h"
#समावेश "libbpf.h"
#समावेश "libbpf_internal.h"

/*
 * When building perf, unistd.h is overridden. __NR_bpf is
 * required to be defined explicitly.
 */
#अगर_अघोषित __NR_bpf
# अगर defined(__i386__)
#  define __NR_bpf 357
# elअगर defined(__x86_64__)
#  define __NR_bpf 321
# elअगर defined(__aarch64__)
#  define __NR_bpf 280
# elअगर defined(__sparc__)
#  define __NR_bpf 349
# elअगर defined(__s390__)
#  define __NR_bpf 351
# elअगर defined(__arc__)
#  define __NR_bpf 280
# अन्यथा
#  error __NR_bpf not defined. libbpf करोes not support your arch.
# endअगर
#पूर्ण_अगर

अटल अंतरभूत __u64 ptr_to_u64(स्थिर व्योम *ptr)
अणु
	वापस (__u64) (अचिन्हित दीर्घ) ptr;
पूर्ण

अटल अंतरभूत पूर्णांक sys_bpf(क्रमागत bpf_cmd cmd, जोड़ bpf_attr *attr,
			  अचिन्हित पूर्णांक size)
अणु
	वापस syscall(__NR_bpf, cmd, attr, size);
पूर्ण

अटल अंतरभूत पूर्णांक sys_bpf_prog_load(जोड़ bpf_attr *attr, अचिन्हित पूर्णांक size)
अणु
	पूर्णांक retries = 5;
	पूर्णांक fd;

	करो अणु
		fd = sys_bpf(BPF_PROG_LOAD, attr, size);
	पूर्ण जबतक (fd < 0 && त्रुटि_सं == EAGAIN && retries-- > 0);

	वापस fd;
पूर्ण

पूर्णांक bpf_create_map_xattr(स्थिर काष्ठा bpf_create_map_attr *create_attr)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, '\0', माप(attr));

	attr.map_type = create_attr->map_type;
	attr.key_size = create_attr->key_size;
	attr.value_size = create_attr->value_size;
	attr.max_entries = create_attr->max_entries;
	attr.map_flags = create_attr->map_flags;
	अगर (create_attr->name)
		स_नकल(attr.map_name, create_attr->name,
		       min(म_माप(create_attr->name), BPF_OBJ_NAME_LEN - 1));
	attr.numa_node = create_attr->numa_node;
	attr.btf_fd = create_attr->btf_fd;
	attr.btf_key_type_id = create_attr->btf_key_type_id;
	attr.btf_value_type_id = create_attr->btf_value_type_id;
	attr.map_अगरindex = create_attr->map_अगरindex;
	अगर (attr.map_type == BPF_MAP_TYPE_STRUCT_OPS)
		attr.btf_vmlinux_value_type_id =
			create_attr->btf_vmlinux_value_type_id;
	अन्यथा
		attr.inner_map_fd = create_attr->inner_map_fd;

	वापस sys_bpf(BPF_MAP_CREATE, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_create_map_node(क्रमागत bpf_map_type map_type, स्थिर अक्षर *name,
			पूर्णांक key_size, पूर्णांक value_size, पूर्णांक max_entries,
			__u32 map_flags, पूर्णांक node)
अणु
	काष्ठा bpf_create_map_attr map_attr = अणुपूर्ण;

	map_attr.name = name;
	map_attr.map_type = map_type;
	map_attr.map_flags = map_flags;
	map_attr.key_size = key_size;
	map_attr.value_size = value_size;
	map_attr.max_entries = max_entries;
	अगर (node >= 0) अणु
		map_attr.numa_node = node;
		map_attr.map_flags |= BPF_F_NUMA_NODE;
	पूर्ण

	वापस bpf_create_map_xattr(&map_attr);
पूर्ण

पूर्णांक bpf_create_map(क्रमागत bpf_map_type map_type, पूर्णांक key_size,
		   पूर्णांक value_size, पूर्णांक max_entries, __u32 map_flags)
अणु
	काष्ठा bpf_create_map_attr map_attr = अणुपूर्ण;

	map_attr.map_type = map_type;
	map_attr.map_flags = map_flags;
	map_attr.key_size = key_size;
	map_attr.value_size = value_size;
	map_attr.max_entries = max_entries;

	वापस bpf_create_map_xattr(&map_attr);
पूर्ण

पूर्णांक bpf_create_map_name(क्रमागत bpf_map_type map_type, स्थिर अक्षर *name,
			पूर्णांक key_size, पूर्णांक value_size, पूर्णांक max_entries,
			__u32 map_flags)
अणु
	काष्ठा bpf_create_map_attr map_attr = अणुपूर्ण;

	map_attr.name = name;
	map_attr.map_type = map_type;
	map_attr.map_flags = map_flags;
	map_attr.key_size = key_size;
	map_attr.value_size = value_size;
	map_attr.max_entries = max_entries;

	वापस bpf_create_map_xattr(&map_attr);
पूर्ण

पूर्णांक bpf_create_map_in_map_node(क्रमागत bpf_map_type map_type, स्थिर अक्षर *name,
			       पूर्णांक key_size, पूर्णांक inner_map_fd, पूर्णांक max_entries,
			       __u32 map_flags, पूर्णांक node)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, '\0', माप(attr));

	attr.map_type = map_type;
	attr.key_size = key_size;
	attr.value_size = 4;
	attr.inner_map_fd = inner_map_fd;
	attr.max_entries = max_entries;
	attr.map_flags = map_flags;
	अगर (name)
		स_नकल(attr.map_name, name,
		       min(म_माप(name), BPF_OBJ_NAME_LEN - 1));

	अगर (node >= 0) अणु
		attr.map_flags |= BPF_F_NUMA_NODE;
		attr.numa_node = node;
	पूर्ण

	वापस sys_bpf(BPF_MAP_CREATE, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_create_map_in_map(क्रमागत bpf_map_type map_type, स्थिर अक्षर *name,
			  पूर्णांक key_size, पूर्णांक inner_map_fd, पूर्णांक max_entries,
			  __u32 map_flags)
अणु
	वापस bpf_create_map_in_map_node(map_type, name, key_size,
					  inner_map_fd, max_entries, map_flags,
					  -1);
पूर्ण

अटल व्योम *
alloc_zero_tailing_info(स्थिर व्योम *orecord, __u32 cnt,
			__u32 actual_rec_size, __u32 expected_rec_size)
अणु
	__u64 info_len = (__u64)actual_rec_size * cnt;
	व्योम *info, *nrecord;
	पूर्णांक i;

	info = दो_स्मृति(info_len);
	अगर (!info)
		वापस शून्य;

	/* zero out bytes kernel करोes not understand */
	nrecord = info;
	क्रम (i = 0; i < cnt; i++) अणु
		स_नकल(nrecord, orecord, expected_rec_size);
		स_रखो(nrecord + expected_rec_size, 0,
		       actual_rec_size - expected_rec_size);
		orecord += actual_rec_size;
		nrecord += actual_rec_size;
	पूर्ण

	वापस info;
पूर्ण

पूर्णांक libbpf__bpf_prog_load(स्थिर काष्ठा bpf_prog_load_params *load_attr)
अणु
	व्योम *finfo = शून्य, *linfo = शून्य;
	जोड़ bpf_attr attr;
	पूर्णांक fd;

	अगर (!load_attr->log_buf != !load_attr->log_buf_sz)
		वापस -EINVAL;

	अगर (load_attr->log_level > (4 | 2 | 1) || (load_attr->log_level && !load_attr->log_buf))
		वापस -EINVAL;

	स_रखो(&attr, 0, माप(attr));
	attr.prog_type = load_attr->prog_type;
	attr.expected_attach_type = load_attr->expected_attach_type;

	अगर (load_attr->attach_prog_fd)
		attr.attach_prog_fd = load_attr->attach_prog_fd;
	अन्यथा
		attr.attach_btf_obj_fd = load_attr->attach_btf_obj_fd;
	attr.attach_btf_id = load_attr->attach_btf_id;

	attr.prog_अगरindex = load_attr->prog_अगरindex;
	attr.kern_version = load_attr->kern_version;

	attr.insn_cnt = (__u32)load_attr->insn_cnt;
	attr.insns = ptr_to_u64(load_attr->insns);
	attr.license = ptr_to_u64(load_attr->license);

	attr.log_level = load_attr->log_level;
	अगर (attr.log_level) अणु
		attr.log_buf = ptr_to_u64(load_attr->log_buf);
		attr.log_size = load_attr->log_buf_sz;
	पूर्ण

	attr.prog_btf_fd = load_attr->prog_btf_fd;
	attr.prog_flags = load_attr->prog_flags;

	attr.func_info_rec_size = load_attr->func_info_rec_size;
	attr.func_info_cnt = load_attr->func_info_cnt;
	attr.func_info = ptr_to_u64(load_attr->func_info);

	attr.line_info_rec_size = load_attr->line_info_rec_size;
	attr.line_info_cnt = load_attr->line_info_cnt;
	attr.line_info = ptr_to_u64(load_attr->line_info);

	अगर (load_attr->name)
		स_नकल(attr.prog_name, load_attr->name,
		       min(म_माप(load_attr->name), (माप_प्रकार)BPF_OBJ_NAME_LEN - 1));

	fd = sys_bpf_prog_load(&attr, माप(attr));
	अगर (fd >= 0)
		वापस fd;

	/* After bpf_prog_load, the kernel may modअगरy certain attributes
	 * to give user space a hपूर्णांक how to deal with loading failure.
	 * Check to see whether we can make some changes and load again.
	 */
	जबतक (त्रुटि_सं == E2BIG && (!finfo || !linfo)) अणु
		अगर (!finfo && attr.func_info_cnt &&
		    attr.func_info_rec_size < load_attr->func_info_rec_size) अणु
			/* try with corrected func info records */
			finfo = alloc_zero_tailing_info(load_attr->func_info,
							load_attr->func_info_cnt,
							load_attr->func_info_rec_size,
							attr.func_info_rec_size);
			अगर (!finfo)
				जाओ करोne;

			attr.func_info = ptr_to_u64(finfo);
			attr.func_info_rec_size = load_attr->func_info_rec_size;
		पूर्ण अन्यथा अगर (!linfo && attr.line_info_cnt &&
			   attr.line_info_rec_size <
			   load_attr->line_info_rec_size) अणु
			linfo = alloc_zero_tailing_info(load_attr->line_info,
							load_attr->line_info_cnt,
							load_attr->line_info_rec_size,
							attr.line_info_rec_size);
			अगर (!linfo)
				जाओ करोne;

			attr.line_info = ptr_to_u64(linfo);
			attr.line_info_rec_size = load_attr->line_info_rec_size;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण

		fd = sys_bpf_prog_load(&attr, माप(attr));
		अगर (fd >= 0)
			जाओ करोne;
	पूर्ण

	अगर (load_attr->log_level || !load_attr->log_buf)
		जाओ करोne;

	/* Try again with log */
	attr.log_buf = ptr_to_u64(load_attr->log_buf);
	attr.log_size = load_attr->log_buf_sz;
	attr.log_level = 1;
	load_attr->log_buf[0] = 0;

	fd = sys_bpf_prog_load(&attr, माप(attr));
करोne:
	मुक्त(finfo);
	मुक्त(linfo);
	वापस fd;
पूर्ण

पूर्णांक bpf_load_program_xattr(स्थिर काष्ठा bpf_load_program_attr *load_attr,
			   अक्षर *log_buf, माप_प्रकार log_buf_sz)
अणु
	काष्ठा bpf_prog_load_params p = अणुपूर्ण;

	अगर (!load_attr || !log_buf != !log_buf_sz)
		वापस -EINVAL;

	p.prog_type = load_attr->prog_type;
	p.expected_attach_type = load_attr->expected_attach_type;
	चयन (p.prog_type) अणु
	हाल BPF_PROG_TYPE_STRUCT_OPS:
	हाल BPF_PROG_TYPE_LSM:
		p.attach_btf_id = load_attr->attach_btf_id;
		अवरोध;
	हाल BPF_PROG_TYPE_TRACING:
	हाल BPF_PROG_TYPE_EXT:
		p.attach_btf_id = load_attr->attach_btf_id;
		p.attach_prog_fd = load_attr->attach_prog_fd;
		अवरोध;
	शेष:
		p.prog_अगरindex = load_attr->prog_अगरindex;
		p.kern_version = load_attr->kern_version;
	पूर्ण
	p.insn_cnt = load_attr->insns_cnt;
	p.insns = load_attr->insns;
	p.license = load_attr->license;
	p.log_level = load_attr->log_level;
	p.log_buf = log_buf;
	p.log_buf_sz = log_buf_sz;
	p.prog_btf_fd = load_attr->prog_btf_fd;
	p.func_info_rec_size = load_attr->func_info_rec_size;
	p.func_info_cnt = load_attr->func_info_cnt;
	p.func_info = load_attr->func_info;
	p.line_info_rec_size = load_attr->line_info_rec_size;
	p.line_info_cnt = load_attr->line_info_cnt;
	p.line_info = load_attr->line_info;
	p.name = load_attr->name;
	p.prog_flags = load_attr->prog_flags;

	वापस libbpf__bpf_prog_load(&p);
पूर्ण

पूर्णांक bpf_load_program(क्रमागत bpf_prog_type type, स्थिर काष्ठा bpf_insn *insns,
		     माप_प्रकार insns_cnt, स्थिर अक्षर *license,
		     __u32 kern_version, अक्षर *log_buf,
		     माप_प्रकार log_buf_sz)
अणु
	काष्ठा bpf_load_program_attr load_attr;

	स_रखो(&load_attr, 0, माप(काष्ठा bpf_load_program_attr));
	load_attr.prog_type = type;
	load_attr.expected_attach_type = 0;
	load_attr.name = शून्य;
	load_attr.insns = insns;
	load_attr.insns_cnt = insns_cnt;
	load_attr.license = license;
	load_attr.kern_version = kern_version;

	वापस bpf_load_program_xattr(&load_attr, log_buf, log_buf_sz);
पूर्ण

पूर्णांक bpf_verअगरy_program(क्रमागत bpf_prog_type type, स्थिर काष्ठा bpf_insn *insns,
		       माप_प्रकार insns_cnt, __u32 prog_flags, स्थिर अक्षर *license,
		       __u32 kern_version, अक्षर *log_buf, माप_प्रकार log_buf_sz,
		       पूर्णांक log_level)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.prog_type = type;
	attr.insn_cnt = (__u32)insns_cnt;
	attr.insns = ptr_to_u64(insns);
	attr.license = ptr_to_u64(license);
	attr.log_buf = ptr_to_u64(log_buf);
	attr.log_size = log_buf_sz;
	attr.log_level = log_level;
	log_buf[0] = 0;
	attr.kern_version = kern_version;
	attr.prog_flags = prog_flags;

	वापस sys_bpf_prog_load(&attr, माप(attr));
पूर्ण

पूर्णांक bpf_map_update_elem(पूर्णांक fd, स्थिर व्योम *key, स्थिर व्योम *value,
			__u64 flags)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.map_fd = fd;
	attr.key = ptr_to_u64(key);
	attr.value = ptr_to_u64(value);
	attr.flags = flags;

	वापस sys_bpf(BPF_MAP_UPDATE_ELEM, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_map_lookup_elem(पूर्णांक fd, स्थिर व्योम *key, व्योम *value)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.map_fd = fd;
	attr.key = ptr_to_u64(key);
	attr.value = ptr_to_u64(value);

	वापस sys_bpf(BPF_MAP_LOOKUP_ELEM, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_map_lookup_elem_flags(पूर्णांक fd, स्थिर व्योम *key, व्योम *value, __u64 flags)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.map_fd = fd;
	attr.key = ptr_to_u64(key);
	attr.value = ptr_to_u64(value);
	attr.flags = flags;

	वापस sys_bpf(BPF_MAP_LOOKUP_ELEM, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_map_lookup_and_delete_elem(पूर्णांक fd, स्थिर व्योम *key, व्योम *value)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.map_fd = fd;
	attr.key = ptr_to_u64(key);
	attr.value = ptr_to_u64(value);

	वापस sys_bpf(BPF_MAP_LOOKUP_AND_DELETE_ELEM, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_map_delete_elem(पूर्णांक fd, स्थिर व्योम *key)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.map_fd = fd;
	attr.key = ptr_to_u64(key);

	वापस sys_bpf(BPF_MAP_DELETE_ELEM, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_map_get_next_key(पूर्णांक fd, स्थिर व्योम *key, व्योम *next_key)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.map_fd = fd;
	attr.key = ptr_to_u64(key);
	attr.next_key = ptr_to_u64(next_key);

	वापस sys_bpf(BPF_MAP_GET_NEXT_KEY, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_map_मुक्तze(पूर्णांक fd)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.map_fd = fd;

	वापस sys_bpf(BPF_MAP_FREEZE, &attr, माप(attr));
पूर्ण

अटल पूर्णांक bpf_map_batch_common(पूर्णांक cmd, पूर्णांक fd, व्योम  *in_batch,
				व्योम *out_batch, व्योम *keys, व्योम *values,
				__u32 *count,
				स्थिर काष्ठा bpf_map_batch_opts *opts)
अणु
	जोड़ bpf_attr attr;
	पूर्णांक ret;

	अगर (!OPTS_VALID(opts, bpf_map_batch_opts))
		वापस -EINVAL;

	स_रखो(&attr, 0, माप(attr));
	attr.batch.map_fd = fd;
	attr.batch.in_batch = ptr_to_u64(in_batch);
	attr.batch.out_batch = ptr_to_u64(out_batch);
	attr.batch.keys = ptr_to_u64(keys);
	attr.batch.values = ptr_to_u64(values);
	attr.batch.count = *count;
	attr.batch.elem_flags  = OPTS_GET(opts, elem_flags, 0);
	attr.batch.flags = OPTS_GET(opts, flags, 0);

	ret = sys_bpf(cmd, &attr, माप(attr));
	*count = attr.batch.count;

	वापस ret;
पूर्ण

पूर्णांक bpf_map_delete_batch(पूर्णांक fd, व्योम *keys, __u32 *count,
			 स्थिर काष्ठा bpf_map_batch_opts *opts)
अणु
	वापस bpf_map_batch_common(BPF_MAP_DELETE_BATCH, fd, शून्य,
				    शून्य, keys, शून्य, count, opts);
पूर्ण

पूर्णांक bpf_map_lookup_batch(पूर्णांक fd, व्योम *in_batch, व्योम *out_batch, व्योम *keys,
			 व्योम *values, __u32 *count,
			 स्थिर काष्ठा bpf_map_batch_opts *opts)
अणु
	वापस bpf_map_batch_common(BPF_MAP_LOOKUP_BATCH, fd, in_batch,
				    out_batch, keys, values, count, opts);
पूर्ण

पूर्णांक bpf_map_lookup_and_delete_batch(पूर्णांक fd, व्योम *in_batch, व्योम *out_batch,
				    व्योम *keys, व्योम *values, __u32 *count,
				    स्थिर काष्ठा bpf_map_batch_opts *opts)
अणु
	वापस bpf_map_batch_common(BPF_MAP_LOOKUP_AND_DELETE_BATCH,
				    fd, in_batch, out_batch, keys, values,
				    count, opts);
पूर्ण

पूर्णांक bpf_map_update_batch(पूर्णांक fd, व्योम *keys, व्योम *values, __u32 *count,
			 स्थिर काष्ठा bpf_map_batch_opts *opts)
अणु
	वापस bpf_map_batch_common(BPF_MAP_UPDATE_BATCH, fd, शून्य, शून्य,
				    keys, values, count, opts);
पूर्ण

पूर्णांक bpf_obj_pin(पूर्णांक fd, स्थिर अक्षर *pathname)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.pathname = ptr_to_u64((व्योम *)pathname);
	attr.bpf_fd = fd;

	वापस sys_bpf(BPF_OBJ_PIN, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_obj_get(स्थिर अक्षर *pathname)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.pathname = ptr_to_u64((व्योम *)pathname);

	वापस sys_bpf(BPF_OBJ_GET, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_prog_attach(पूर्णांक prog_fd, पूर्णांक target_fd, क्रमागत bpf_attach_type type,
		    अचिन्हित पूर्णांक flags)
अणु
	DECLARE_LIBBPF_OPTS(bpf_prog_attach_opts, opts,
		.flags = flags,
	);

	वापस bpf_prog_attach_xattr(prog_fd, target_fd, type, &opts);
पूर्ण

पूर्णांक bpf_prog_attach_xattr(पूर्णांक prog_fd, पूर्णांक target_fd,
			  क्रमागत bpf_attach_type type,
			  स्थिर काष्ठा bpf_prog_attach_opts *opts)
अणु
	जोड़ bpf_attr attr;

	अगर (!OPTS_VALID(opts, bpf_prog_attach_opts))
		वापस -EINVAL;

	स_रखो(&attr, 0, माप(attr));
	attr.target_fd	   = target_fd;
	attr.attach_bpf_fd = prog_fd;
	attr.attach_type   = type;
	attr.attach_flags  = OPTS_GET(opts, flags, 0);
	attr.replace_bpf_fd = OPTS_GET(opts, replace_prog_fd, 0);

	वापस sys_bpf(BPF_PROG_ATTACH, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_prog_detach(पूर्णांक target_fd, क्रमागत bpf_attach_type type)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.target_fd	 = target_fd;
	attr.attach_type = type;

	वापस sys_bpf(BPF_PROG_DETACH, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_prog_detach2(पूर्णांक prog_fd, पूर्णांक target_fd, क्रमागत bpf_attach_type type)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.target_fd	 = target_fd;
	attr.attach_bpf_fd = prog_fd;
	attr.attach_type = type;

	वापस sys_bpf(BPF_PROG_DETACH, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_link_create(पूर्णांक prog_fd, पूर्णांक target_fd,
		    क्रमागत bpf_attach_type attach_type,
		    स्थिर काष्ठा bpf_link_create_opts *opts)
अणु
	__u32 target_btf_id, iter_info_len;
	जोड़ bpf_attr attr;

	अगर (!OPTS_VALID(opts, bpf_link_create_opts))
		वापस -EINVAL;

	iter_info_len = OPTS_GET(opts, iter_info_len, 0);
	target_btf_id = OPTS_GET(opts, target_btf_id, 0);

	अगर (iter_info_len && target_btf_id)
		वापस -EINVAL;

	स_रखो(&attr, 0, माप(attr));
	attr.link_create.prog_fd = prog_fd;
	attr.link_create.target_fd = target_fd;
	attr.link_create.attach_type = attach_type;
	attr.link_create.flags = OPTS_GET(opts, flags, 0);

	अगर (iter_info_len) अणु
		attr.link_create.iter_info =
			ptr_to_u64(OPTS_GET(opts, iter_info, (व्योम *)0));
		attr.link_create.iter_info_len = iter_info_len;
	पूर्ण अन्यथा अगर (target_btf_id) अणु
		attr.link_create.target_btf_id = target_btf_id;
	पूर्ण

	वापस sys_bpf(BPF_LINK_CREATE, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_link_detach(पूर्णांक link_fd)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.link_detach.link_fd = link_fd;

	वापस sys_bpf(BPF_LINK_DETACH, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_link_update(पूर्णांक link_fd, पूर्णांक new_prog_fd,
		    स्थिर काष्ठा bpf_link_update_opts *opts)
अणु
	जोड़ bpf_attr attr;

	अगर (!OPTS_VALID(opts, bpf_link_update_opts))
		वापस -EINVAL;

	स_रखो(&attr, 0, माप(attr));
	attr.link_update.link_fd = link_fd;
	attr.link_update.new_prog_fd = new_prog_fd;
	attr.link_update.flags = OPTS_GET(opts, flags, 0);
	attr.link_update.old_prog_fd = OPTS_GET(opts, old_prog_fd, 0);

	वापस sys_bpf(BPF_LINK_UPDATE, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_iter_create(पूर्णांक link_fd)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.iter_create.link_fd = link_fd;

	वापस sys_bpf(BPF_ITER_CREATE, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_prog_query(पूर्णांक target_fd, क्रमागत bpf_attach_type type, __u32 query_flags,
		   __u32 *attach_flags, __u32 *prog_ids, __u32 *prog_cnt)
अणु
	जोड़ bpf_attr attr;
	पूर्णांक ret;

	स_रखो(&attr, 0, माप(attr));
	attr.query.target_fd	= target_fd;
	attr.query.attach_type	= type;
	attr.query.query_flags	= query_flags;
	attr.query.prog_cnt	= *prog_cnt;
	attr.query.prog_ids	= ptr_to_u64(prog_ids);

	ret = sys_bpf(BPF_PROG_QUERY, &attr, माप(attr));
	अगर (attach_flags)
		*attach_flags = attr.query.attach_flags;
	*prog_cnt = attr.query.prog_cnt;
	वापस ret;
पूर्ण

पूर्णांक bpf_prog_test_run(पूर्णांक prog_fd, पूर्णांक repeat, व्योम *data, __u32 size,
		      व्योम *data_out, __u32 *size_out, __u32 *retval,
		      __u32 *duration)
अणु
	जोड़ bpf_attr attr;
	पूर्णांक ret;

	स_रखो(&attr, 0, माप(attr));
	attr.test.prog_fd = prog_fd;
	attr.test.data_in = ptr_to_u64(data);
	attr.test.data_out = ptr_to_u64(data_out);
	attr.test.data_size_in = size;
	attr.test.repeat = repeat;

	ret = sys_bpf(BPF_PROG_TEST_RUN, &attr, माप(attr));
	अगर (size_out)
		*size_out = attr.test.data_size_out;
	अगर (retval)
		*retval = attr.test.retval;
	अगर (duration)
		*duration = attr.test.duration;
	वापस ret;
पूर्ण

पूर्णांक bpf_prog_test_run_xattr(काष्ठा bpf_prog_test_run_attr *test_attr)
अणु
	जोड़ bpf_attr attr;
	पूर्णांक ret;

	अगर (!test_attr->data_out && test_attr->data_size_out > 0)
		वापस -EINVAL;

	स_रखो(&attr, 0, माप(attr));
	attr.test.prog_fd = test_attr->prog_fd;
	attr.test.data_in = ptr_to_u64(test_attr->data_in);
	attr.test.data_out = ptr_to_u64(test_attr->data_out);
	attr.test.data_size_in = test_attr->data_size_in;
	attr.test.data_size_out = test_attr->data_size_out;
	attr.test.ctx_in = ptr_to_u64(test_attr->ctx_in);
	attr.test.ctx_out = ptr_to_u64(test_attr->ctx_out);
	attr.test.ctx_size_in = test_attr->ctx_size_in;
	attr.test.ctx_size_out = test_attr->ctx_size_out;
	attr.test.repeat = test_attr->repeat;

	ret = sys_bpf(BPF_PROG_TEST_RUN, &attr, माप(attr));
	test_attr->data_size_out = attr.test.data_size_out;
	test_attr->ctx_size_out = attr.test.ctx_size_out;
	test_attr->retval = attr.test.retval;
	test_attr->duration = attr.test.duration;
	वापस ret;
पूर्ण

पूर्णांक bpf_prog_test_run_opts(पूर्णांक prog_fd, काष्ठा bpf_test_run_opts *opts)
अणु
	जोड़ bpf_attr attr;
	पूर्णांक ret;

	अगर (!OPTS_VALID(opts, bpf_test_run_opts))
		वापस -EINVAL;

	स_रखो(&attr, 0, माप(attr));
	attr.test.prog_fd = prog_fd;
	attr.test.cpu = OPTS_GET(opts, cpu, 0);
	attr.test.flags = OPTS_GET(opts, flags, 0);
	attr.test.repeat = OPTS_GET(opts, repeat, 0);
	attr.test.duration = OPTS_GET(opts, duration, 0);
	attr.test.ctx_size_in = OPTS_GET(opts, ctx_size_in, 0);
	attr.test.ctx_size_out = OPTS_GET(opts, ctx_size_out, 0);
	attr.test.data_size_in = OPTS_GET(opts, data_size_in, 0);
	attr.test.data_size_out = OPTS_GET(opts, data_size_out, 0);
	attr.test.ctx_in = ptr_to_u64(OPTS_GET(opts, ctx_in, शून्य));
	attr.test.ctx_out = ptr_to_u64(OPTS_GET(opts, ctx_out, शून्य));
	attr.test.data_in = ptr_to_u64(OPTS_GET(opts, data_in, शून्य));
	attr.test.data_out = ptr_to_u64(OPTS_GET(opts, data_out, शून्य));

	ret = sys_bpf(BPF_PROG_TEST_RUN, &attr, माप(attr));
	OPTS_SET(opts, data_size_out, attr.test.data_size_out);
	OPTS_SET(opts, ctx_size_out, attr.test.ctx_size_out);
	OPTS_SET(opts, duration, attr.test.duration);
	OPTS_SET(opts, retval, attr.test.retval);
	वापस ret;
पूर्ण

अटल पूर्णांक bpf_obj_get_next_id(__u32 start_id, __u32 *next_id, पूर्णांक cmd)
अणु
	जोड़ bpf_attr attr;
	पूर्णांक err;

	स_रखो(&attr, 0, माप(attr));
	attr.start_id = start_id;

	err = sys_bpf(cmd, &attr, माप(attr));
	अगर (!err)
		*next_id = attr.next_id;

	वापस err;
पूर्ण

पूर्णांक bpf_prog_get_next_id(__u32 start_id, __u32 *next_id)
अणु
	वापस bpf_obj_get_next_id(start_id, next_id, BPF_PROG_GET_NEXT_ID);
पूर्ण

पूर्णांक bpf_map_get_next_id(__u32 start_id, __u32 *next_id)
अणु
	वापस bpf_obj_get_next_id(start_id, next_id, BPF_MAP_GET_NEXT_ID);
पूर्ण

पूर्णांक bpf_btf_get_next_id(__u32 start_id, __u32 *next_id)
अणु
	वापस bpf_obj_get_next_id(start_id, next_id, BPF_BTF_GET_NEXT_ID);
पूर्ण

पूर्णांक bpf_link_get_next_id(__u32 start_id, __u32 *next_id)
अणु
	वापस bpf_obj_get_next_id(start_id, next_id, BPF_LINK_GET_NEXT_ID);
पूर्ण

पूर्णांक bpf_prog_get_fd_by_id(__u32 id)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.prog_id = id;

	वापस sys_bpf(BPF_PROG_GET_FD_BY_ID, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_map_get_fd_by_id(__u32 id)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.map_id = id;

	वापस sys_bpf(BPF_MAP_GET_FD_BY_ID, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_btf_get_fd_by_id(__u32 id)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.btf_id = id;

	वापस sys_bpf(BPF_BTF_GET_FD_BY_ID, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_link_get_fd_by_id(__u32 id)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.link_id = id;

	वापस sys_bpf(BPF_LINK_GET_FD_BY_ID, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_obj_get_info_by_fd(पूर्णांक bpf_fd, व्योम *info, __u32 *info_len)
अणु
	जोड़ bpf_attr attr;
	पूर्णांक err;

	स_रखो(&attr, 0, माप(attr));
	attr.info.bpf_fd = bpf_fd;
	attr.info.info_len = *info_len;
	attr.info.info = ptr_to_u64(info);

	err = sys_bpf(BPF_OBJ_GET_INFO_BY_FD, &attr, माप(attr));
	अगर (!err)
		*info_len = attr.info.info_len;

	वापस err;
पूर्ण

पूर्णांक bpf_raw_tracepoपूर्णांक_खोलो(स्थिर अक्षर *name, पूर्णांक prog_fd)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.raw_tracepoपूर्णांक.name = ptr_to_u64(name);
	attr.raw_tracepoपूर्णांक.prog_fd = prog_fd;

	वापस sys_bpf(BPF_RAW_TRACEPOINT_OPEN, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_load_btf(स्थिर व्योम *btf, __u32 btf_size, अक्षर *log_buf, __u32 log_buf_size,
		 bool करो_log)
अणु
	जोड़ bpf_attr attr = अणुपूर्ण;
	पूर्णांक fd;

	attr.btf = ptr_to_u64(btf);
	attr.btf_size = btf_size;

retry:
	अगर (करो_log && log_buf && log_buf_size) अणु
		attr.btf_log_level = 1;
		attr.btf_log_size = log_buf_size;
		attr.btf_log_buf = ptr_to_u64(log_buf);
	पूर्ण

	fd = sys_bpf(BPF_BTF_LOAD, &attr, माप(attr));
	अगर (fd == -1 && !करो_log && log_buf && log_buf_size) अणु
		करो_log = true;
		जाओ retry;
	पूर्ण

	वापस fd;
पूर्ण

पूर्णांक bpf_task_fd_query(पूर्णांक pid, पूर्णांक fd, __u32 flags, अक्षर *buf, __u32 *buf_len,
		      __u32 *prog_id, __u32 *fd_type, __u64 *probe_offset,
		      __u64 *probe_addr)
अणु
	जोड़ bpf_attr attr = अणुपूर्ण;
	पूर्णांक err;

	attr.task_fd_query.pid = pid;
	attr.task_fd_query.fd = fd;
	attr.task_fd_query.flags = flags;
	attr.task_fd_query.buf = ptr_to_u64(buf);
	attr.task_fd_query.buf_len = *buf_len;

	err = sys_bpf(BPF_TASK_FD_QUERY, &attr, माप(attr));
	*buf_len = attr.task_fd_query.buf_len;
	*prog_id = attr.task_fd_query.prog_id;
	*fd_type = attr.task_fd_query.fd_type;
	*probe_offset = attr.task_fd_query.probe_offset;
	*probe_addr = attr.task_fd_query.probe_addr;

	वापस err;
पूर्ण

पूर्णांक bpf_enable_stats(क्रमागत bpf_stats_type type)
अणु
	जोड़ bpf_attr attr;

	स_रखो(&attr, 0, माप(attr));
	attr.enable_stats.type = type;

	वापस sys_bpf(BPF_ENABLE_STATS, &attr, माप(attr));
पूर्ण

पूर्णांक bpf_prog_bind_map(पूर्णांक prog_fd, पूर्णांक map_fd,
		      स्थिर काष्ठा bpf_prog_bind_opts *opts)
अणु
	जोड़ bpf_attr attr;

	अगर (!OPTS_VALID(opts, bpf_prog_bind_opts))
		वापस -EINVAL;

	स_रखो(&attr, 0, माप(attr));
	attr.prog_bind_map.prog_fd = prog_fd;
	attr.prog_bind_map.map_fd = map_fd;
	attr.prog_bind_map.flags = OPTS_GET(opts, flags, 0);

	वापस sys_bpf(BPF_PROG_BIND_MAP, &attr, माप(attr));
पूर्ण
