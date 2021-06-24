<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2016-20 Intel Corporation.
 */

#अगर_अघोषित MAIN_H
#घोषणा MAIN_H

काष्ठा encl_segment अणु
	off_t offset;
	माप_प्रकार size;
	अचिन्हित पूर्णांक prot;
	अचिन्हित पूर्णांक flags;
पूर्ण;

काष्ठा encl अणु
	पूर्णांक fd;
	व्योम *bin;
	off_t bin_size;
	व्योम *src;
	माप_प्रकार src_size;
	माप_प्रकार encl_size;
	off_t encl_base;
	अचिन्हित पूर्णांक nr_segments;
	काष्ठा encl_segment *segment_tbl;
	काष्ठा sgx_secs secs;
	काष्ठा sgx_sigकाष्ठा sigकाष्ठा;
पूर्ण;

बाह्य अचिन्हित अक्षर sign_key[];
बाह्य अचिन्हित अक्षर sign_key_end[];

व्योम encl_delete(काष्ठा encl *ctx);
bool encl_load(स्थिर अक्षर *path, काष्ठा encl *encl);
bool encl_measure(काष्ठा encl *encl);
bool encl_build(काष्ठा encl *encl);

पूर्णांक sgx_call_vdso(व्योम *rdi, व्योम *rsi, दीर्घ rdx, u32 function, व्योम *r8, व्योम *r9,
		  काष्ठा sgx_enclave_run *run);

#पूर्ण_अगर /* MAIN_H */
