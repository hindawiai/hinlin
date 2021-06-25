<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015, Wang Nan <wangnan0@huawei.com>
 * Copyright (C) 2015, Huawei Inc.
 */
#अगर_अघोषित __LLVM_UTILS_H
#घोषणा __LLVM_UTILS_H

#समावेश <stdbool.h>

काष्ठा llvm_param अणु
	/* Path of clang executable */
	स्थिर अक्षर *clang_path;
	/* Path of llc executable */
	स्थिर अक्षर *llc_path;
	/*
	 * Template of clang bpf compiling. 5 env variables
	 * can be used:
	 *   $CLANG_EXEC:		Path to clang.
	 *   $CLANG_OPTIONS:		Extra options to clang.
	 *   $KERNEL_INC_OPTIONS:	Kernel include directories.
	 *   $WORKING_सूची:		Kernel source directory.
	 *   $CLANG_SOURCE:		Source file to be compiled.
	 */
	स्थिर अक्षर *clang_bpf_cmd_ढाँचा;
	/* Will be filled in $CLANG_OPTIONS */
	स्थिर अक्षर *clang_opt;
	/*
	 * If present it'll add -emit-llvm to $CLANG_OPTIONS to pipe
	 * the clang output to llc, useful क्रम new llvm options not
	 * yet selectable via 'clang -mllvm option', such as -mattr=dwarfris
	 * in clang 6.0/llvm 7
	 */
	स्थिर अक्षर *opts;
	/* Where to find kbuild प्रणाली */
	स्थिर अक्षर *kbuild_dir;
	/*
	 * Arguments passed to make, like 'ARCH=arm' अगर करोing cross
	 * compiling. Should not be used क्रम dynamic compiling.
	 */
	स्थिर अक्षर *kbuild_opts;
	/*
	 * Default is false. If set to true, ग_लिखो compiling result
	 * to object file.
	 */
	bool dump_obj;
	/*
	 * Default is false. If one of the above fields is set by user
	 * explicitly then user_set_llvm is set to true. This is used
	 * क्रम perf test. If user करोesn't set anything in .perfconfig
	 * and clang is not found, करोn't trigger llvm test.
	 */
	bool user_set_param;
पूर्ण;

बाह्य काष्ठा llvm_param llvm_param;
पूर्णांक perf_llvm_config(स्थिर अक्षर *var, स्थिर अक्षर *value);

पूर्णांक llvm__compile_bpf(स्थिर अक्षर *path, व्योम **p_obj_buf, माप_प्रकार *p_obj_buf_sz);

/* This function is क्रम test__llvm() use only */
पूर्णांक llvm__search_clang(व्योम);

/* Following functions are reused by builtin clang support */
व्योम llvm__get_kbuild_opts(अक्षर **kbuild_dir, अक्षर **kbuild_include_opts);
पूर्णांक llvm__get_nr_cpus(व्योम);

व्योम llvm__dump_obj(स्थिर अक्षर *path, व्योम *obj_buf, माप_प्रकार size);
#पूर्ण_अगर
