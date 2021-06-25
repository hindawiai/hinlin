<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */

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
#अगर_अघोषित __LIBBPF_BPF_H
#घोषणा __LIBBPF_BPF_H

#समावेश <linux/bpf.h>
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>

#समावेश "libbpf_common.h"

#अगर_घोषित __cplusplus
बाह्य "C" अणु
#पूर्ण_अगर

काष्ठा bpf_create_map_attr अणु
	स्थिर अक्षर *name;
	क्रमागत bpf_map_type map_type;
	__u32 map_flags;
	__u32 key_size;
	__u32 value_size;
	__u32 max_entries;
	__u32 numa_node;
	__u32 btf_fd;
	__u32 btf_key_type_id;
	__u32 btf_value_type_id;
	__u32 map_अगरindex;
	जोड़ अणु
		__u32 inner_map_fd;
		__u32 btf_vmlinux_value_type_id;
	पूर्ण;
पूर्ण;

LIBBPF_API पूर्णांक
bpf_create_map_xattr(स्थिर काष्ठा bpf_create_map_attr *create_attr);
LIBBPF_API पूर्णांक bpf_create_map_node(क्रमागत bpf_map_type map_type, स्थिर अक्षर *name,
				   पूर्णांक key_size, पूर्णांक value_size,
				   पूर्णांक max_entries, __u32 map_flags, पूर्णांक node);
LIBBPF_API पूर्णांक bpf_create_map_name(क्रमागत bpf_map_type map_type, स्थिर अक्षर *name,
				   पूर्णांक key_size, पूर्णांक value_size,
				   पूर्णांक max_entries, __u32 map_flags);
LIBBPF_API पूर्णांक bpf_create_map(क्रमागत bpf_map_type map_type, पूर्णांक key_size,
			      पूर्णांक value_size, पूर्णांक max_entries, __u32 map_flags);
LIBBPF_API पूर्णांक bpf_create_map_in_map_node(क्रमागत bpf_map_type map_type,
					  स्थिर अक्षर *name, पूर्णांक key_size,
					  पूर्णांक inner_map_fd, पूर्णांक max_entries,
					  __u32 map_flags, पूर्णांक node);
LIBBPF_API पूर्णांक bpf_create_map_in_map(क्रमागत bpf_map_type map_type,
				     स्थिर अक्षर *name, पूर्णांक key_size,
				     पूर्णांक inner_map_fd, पूर्णांक max_entries,
				     __u32 map_flags);

काष्ठा bpf_load_program_attr अणु
	क्रमागत bpf_prog_type prog_type;
	क्रमागत bpf_attach_type expected_attach_type;
	स्थिर अक्षर *name;
	स्थिर काष्ठा bpf_insn *insns;
	माप_प्रकार insns_cnt;
	स्थिर अक्षर *license;
	जोड़ अणु
		__u32 kern_version;
		__u32 attach_prog_fd;
	पूर्ण;
	जोड़ अणु
		__u32 prog_अगरindex;
		__u32 attach_btf_id;
	पूर्ण;
	__u32 prog_btf_fd;
	__u32 func_info_rec_size;
	स्थिर व्योम *func_info;
	__u32 func_info_cnt;
	__u32 line_info_rec_size;
	स्थिर व्योम *line_info;
	__u32 line_info_cnt;
	__u32 log_level;
	__u32 prog_flags;
पूर्ण;

/* Flags to direct loading requirements */
#घोषणा MAPS_RELAX_COMPAT	0x01

/* Recommend log buffer size */
#घोषणा BPF_LOG_BUF_SIZE (UINT32_MAX >> 8) /* verअगरier maximum in kernels <= 5.1 */
LIBBPF_API पूर्णांक
bpf_load_program_xattr(स्थिर काष्ठा bpf_load_program_attr *load_attr,
		       अक्षर *log_buf, माप_प्रकार log_buf_sz);
LIBBPF_API पूर्णांक bpf_load_program(क्रमागत bpf_prog_type type,
				स्थिर काष्ठा bpf_insn *insns, माप_प्रकार insns_cnt,
				स्थिर अक्षर *license, __u32 kern_version,
				अक्षर *log_buf, माप_प्रकार log_buf_sz);
LIBBPF_API पूर्णांक bpf_verअगरy_program(क्रमागत bpf_prog_type type,
				  स्थिर काष्ठा bpf_insn *insns,
				  माप_प्रकार insns_cnt, __u32 prog_flags,
				  स्थिर अक्षर *license, __u32 kern_version,
				  अक्षर *log_buf, माप_प्रकार log_buf_sz,
				  पूर्णांक log_level);

LIBBPF_API पूर्णांक bpf_map_update_elem(पूर्णांक fd, स्थिर व्योम *key, स्थिर व्योम *value,
				   __u64 flags);

LIBBPF_API पूर्णांक bpf_map_lookup_elem(पूर्णांक fd, स्थिर व्योम *key, व्योम *value);
LIBBPF_API पूर्णांक bpf_map_lookup_elem_flags(पूर्णांक fd, स्थिर व्योम *key, व्योम *value,
					 __u64 flags);
LIBBPF_API पूर्णांक bpf_map_lookup_and_delete_elem(पूर्णांक fd, स्थिर व्योम *key,
					      व्योम *value);
LIBBPF_API पूर्णांक bpf_map_delete_elem(पूर्णांक fd, स्थिर व्योम *key);
LIBBPF_API पूर्णांक bpf_map_get_next_key(पूर्णांक fd, स्थिर व्योम *key, व्योम *next_key);
LIBBPF_API पूर्णांक bpf_map_मुक्तze(पूर्णांक fd);

काष्ठा bpf_map_batch_opts अणु
	माप_प्रकार sz; /* size of this काष्ठा क्रम क्रमward/backward compatibility */
	__u64 elem_flags;
	__u64 flags;
पूर्ण;
#घोषणा bpf_map_batch_opts__last_field flags

LIBBPF_API पूर्णांक bpf_map_delete_batch(पूर्णांक fd, व्योम *keys,
				    __u32 *count,
				    स्थिर काष्ठा bpf_map_batch_opts *opts);
LIBBPF_API पूर्णांक bpf_map_lookup_batch(पूर्णांक fd, व्योम *in_batch, व्योम *out_batch,
				    व्योम *keys, व्योम *values, __u32 *count,
				    स्थिर काष्ठा bpf_map_batch_opts *opts);
LIBBPF_API पूर्णांक bpf_map_lookup_and_delete_batch(पूर्णांक fd, व्योम *in_batch,
					व्योम *out_batch, व्योम *keys,
					व्योम *values, __u32 *count,
					स्थिर काष्ठा bpf_map_batch_opts *opts);
LIBBPF_API पूर्णांक bpf_map_update_batch(पूर्णांक fd, व्योम *keys, व्योम *values,
				    __u32 *count,
				    स्थिर काष्ठा bpf_map_batch_opts *opts);

LIBBPF_API पूर्णांक bpf_obj_pin(पूर्णांक fd, स्थिर अक्षर *pathname);
LIBBPF_API पूर्णांक bpf_obj_get(स्थिर अक्षर *pathname);

काष्ठा bpf_prog_attach_opts अणु
	माप_प्रकार sz; /* size of this काष्ठा क्रम क्रमward/backward compatibility */
	अचिन्हित पूर्णांक flags;
	पूर्णांक replace_prog_fd;
पूर्ण;
#घोषणा bpf_prog_attach_opts__last_field replace_prog_fd

LIBBPF_API पूर्णांक bpf_prog_attach(पूर्णांक prog_fd, पूर्णांक attachable_fd,
			       क्रमागत bpf_attach_type type, अचिन्हित पूर्णांक flags);
LIBBPF_API पूर्णांक bpf_prog_attach_xattr(पूर्णांक prog_fd, पूर्णांक attachable_fd,
				     क्रमागत bpf_attach_type type,
				     स्थिर काष्ठा bpf_prog_attach_opts *opts);
LIBBPF_API पूर्णांक bpf_prog_detach(पूर्णांक attachable_fd, क्रमागत bpf_attach_type type);
LIBBPF_API पूर्णांक bpf_prog_detach2(पूर्णांक prog_fd, पूर्णांक attachable_fd,
				क्रमागत bpf_attach_type type);

जोड़ bpf_iter_link_info; /* defined in up-to-date linux/bpf.h */
काष्ठा bpf_link_create_opts अणु
	माप_प्रकार sz; /* size of this काष्ठा क्रम क्रमward/backward compatibility */
	__u32 flags;
	जोड़ bpf_iter_link_info *iter_info;
	__u32 iter_info_len;
	__u32 target_btf_id;
पूर्ण;
#घोषणा bpf_link_create_opts__last_field target_btf_id

LIBBPF_API पूर्णांक bpf_link_create(पूर्णांक prog_fd, पूर्णांक target_fd,
			       क्रमागत bpf_attach_type attach_type,
			       स्थिर काष्ठा bpf_link_create_opts *opts);

LIBBPF_API पूर्णांक bpf_link_detach(पूर्णांक link_fd);

काष्ठा bpf_link_update_opts अणु
	माप_प्रकार sz; /* size of this काष्ठा क्रम क्रमward/backward compatibility */
	__u32 flags;	   /* extra flags */
	__u32 old_prog_fd; /* expected old program FD */
पूर्ण;
#घोषणा bpf_link_update_opts__last_field old_prog_fd

LIBBPF_API पूर्णांक bpf_link_update(पूर्णांक link_fd, पूर्णांक new_prog_fd,
			       स्थिर काष्ठा bpf_link_update_opts *opts);

LIBBPF_API पूर्णांक bpf_iter_create(पूर्णांक link_fd);

काष्ठा bpf_prog_test_run_attr अणु
	पूर्णांक prog_fd;
	पूर्णांक repeat;
	स्थिर व्योम *data_in;
	__u32 data_size_in;
	व्योम *data_out;      /* optional */
	__u32 data_size_out; /* in: max length of data_out
			      * out: length of data_out */
	__u32 retval;        /* out: वापस code of the BPF program */
	__u32 duration;      /* out: average per repetition in ns */
	स्थिर व्योम *ctx_in; /* optional */
	__u32 ctx_size_in;
	व्योम *ctx_out;      /* optional */
	__u32 ctx_size_out; /* in: max length of ctx_out
			     * out: length of cxt_out */
पूर्ण;

LIBBPF_API पूर्णांक bpf_prog_test_run_xattr(काष्ठा bpf_prog_test_run_attr *test_attr);

/*
 * bpf_prog_test_run करोes not check that data_out is large enough. Consider
 * using bpf_prog_test_run_xattr instead.
 */
LIBBPF_API पूर्णांक bpf_prog_test_run(पूर्णांक prog_fd, पूर्णांक repeat, व्योम *data,
				 __u32 size, व्योम *data_out, __u32 *size_out,
				 __u32 *retval, __u32 *duration);
LIBBPF_API पूर्णांक bpf_prog_get_next_id(__u32 start_id, __u32 *next_id);
LIBBPF_API पूर्णांक bpf_map_get_next_id(__u32 start_id, __u32 *next_id);
LIBBPF_API पूर्णांक bpf_btf_get_next_id(__u32 start_id, __u32 *next_id);
LIBBPF_API पूर्णांक bpf_link_get_next_id(__u32 start_id, __u32 *next_id);
LIBBPF_API पूर्णांक bpf_prog_get_fd_by_id(__u32 id);
LIBBPF_API पूर्णांक bpf_map_get_fd_by_id(__u32 id);
LIBBPF_API पूर्णांक bpf_btf_get_fd_by_id(__u32 id);
LIBBPF_API पूर्णांक bpf_link_get_fd_by_id(__u32 id);
LIBBPF_API पूर्णांक bpf_obj_get_info_by_fd(पूर्णांक bpf_fd, व्योम *info, __u32 *info_len);
LIBBPF_API पूर्णांक bpf_prog_query(पूर्णांक target_fd, क्रमागत bpf_attach_type type,
			      __u32 query_flags, __u32 *attach_flags,
			      __u32 *prog_ids, __u32 *prog_cnt);
LIBBPF_API पूर्णांक bpf_raw_tracepoपूर्णांक_खोलो(स्थिर अक्षर *name, पूर्णांक prog_fd);
LIBBPF_API पूर्णांक bpf_load_btf(स्थिर व्योम *btf, __u32 btf_size, अक्षर *log_buf,
			    __u32 log_buf_size, bool करो_log);
LIBBPF_API पूर्णांक bpf_task_fd_query(पूर्णांक pid, पूर्णांक fd, __u32 flags, अक्षर *buf,
				 __u32 *buf_len, __u32 *prog_id, __u32 *fd_type,
				 __u64 *probe_offset, __u64 *probe_addr);

क्रमागत bpf_stats_type; /* defined in up-to-date linux/bpf.h */
LIBBPF_API पूर्णांक bpf_enable_stats(क्रमागत bpf_stats_type type);

काष्ठा bpf_prog_bind_opts अणु
	माप_प्रकार sz; /* size of this काष्ठा क्रम क्रमward/backward compatibility */
	__u32 flags;
पूर्ण;
#घोषणा bpf_prog_bind_opts__last_field flags

LIBBPF_API पूर्णांक bpf_prog_bind_map(पूर्णांक prog_fd, पूर्णांक map_fd,
				 स्थिर काष्ठा bpf_prog_bind_opts *opts);

काष्ठा bpf_test_run_opts अणु
	माप_प्रकार sz; /* size of this काष्ठा क्रम क्रमward/backward compatibility */
	स्थिर व्योम *data_in; /* optional */
	व्योम *data_out;      /* optional */
	__u32 data_size_in;
	__u32 data_size_out; /* in: max length of data_out
			      * out: length of data_out
			      */
	स्थिर व्योम *ctx_in; /* optional */
	व्योम *ctx_out;      /* optional */
	__u32 ctx_size_in;
	__u32 ctx_size_out; /* in: max length of ctx_out
			     * out: length of cxt_out
			     */
	__u32 retval;        /* out: वापस code of the BPF program */
	पूर्णांक repeat;
	__u32 duration;      /* out: average per repetition in ns */
	__u32 flags;
	__u32 cpu;
पूर्ण;
#घोषणा bpf_test_run_opts__last_field cpu

LIBBPF_API पूर्णांक bpf_prog_test_run_opts(पूर्णांक prog_fd,
				      काष्ठा bpf_test_run_opts *opts);

#अगर_घोषित __cplusplus
पूर्ण /* बाह्य "C" */
#पूर्ण_अगर

#पूर्ण_अगर /* __LIBBPF_BPF_H */
