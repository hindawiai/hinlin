<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2019 Netronome Systems, Inc. */

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>
#समावेश <माला.स>

पूर्णांक extra_prog_load_log_flags = 0;

पूर्णांक bpf_prog_test_load(स्थिर अक्षर *file, क्रमागत bpf_prog_type type,
		       काष्ठा bpf_object **pobj, पूर्णांक *prog_fd)
अणु
	काष्ठा bpf_prog_load_attr attr;

	स_रखो(&attr, 0, माप(काष्ठा bpf_prog_load_attr));
	attr.file = file;
	attr.prog_type = type;
	attr.expected_attach_type = 0;
	attr.prog_flags = BPF_F_TEST_RND_HI32;
	attr.log_level = extra_prog_load_log_flags;

	वापस bpf_prog_load_xattr(&attr, pobj, prog_fd);
पूर्ण

पूर्णांक bpf_test_load_program(क्रमागत bpf_prog_type type, स्थिर काष्ठा bpf_insn *insns,
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
	load_attr.prog_flags = BPF_F_TEST_RND_HI32;
	load_attr.log_level = extra_prog_load_log_flags;

	वापस bpf_load_program_xattr(&load_attr, log_buf, log_buf_sz);
पूर्ण
