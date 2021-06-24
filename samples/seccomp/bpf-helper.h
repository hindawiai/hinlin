<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Example wrapper around BPF macros.
 *
 * Copyright (c) 2012 The Chromium OS Authors <chromium-os-dev@chromium.org>
 * Author: Will Drewry <wad@chromium.org>
 *
 * The code may be used by anyone क्रम any purpose,
 * and can serve as a starting poपूर्णांक क्रम developing
 * applications using prctl(PR_SET_SECCOMP, 2, ...).
 *
 * No guarantees are provided with respect to the correctness
 * or functionality of this code.
 */
#अगर_अघोषित __BPF_HELPER_H__
#घोषणा __BPF_HELPER_H__

#समावेश <यंत्र/bitsperदीर्घ.h>	/* क्रम __BITS_PER_LONG */
#समावेश <endian.h>
#समावेश <linux/filter.h>
#समावेश <linux/seccomp.h>	/* क्रम seccomp_data */
#समावेश <linux/types.h>
#समावेश <linux/unistd.h>
#समावेश <मानकघोष.स>

#घोषणा BPF_LABELS_MAX 256
काष्ठा bpf_labels अणु
	पूर्णांक count;
	काष्ठा __bpf_label अणु
		स्थिर अक्षर *label;
		__u32 location;
	पूर्ण labels[BPF_LABELS_MAX];
पूर्ण;

पूर्णांक bpf_resolve_jumps(काष्ठा bpf_labels *labels,
		      काष्ठा sock_filter *filter, माप_प्रकार count);
__u32 seccomp_bpf_label(काष्ठा bpf_labels *labels, स्थिर अक्षर *label);
व्योम seccomp_bpf_prपूर्णांक(काष्ठा sock_filter *filter, माप_प्रकार count);

#घोषणा JUMP_JT 0xff
#घोषणा JUMP_JF 0xff
#घोषणा LABEL_JT 0xfe
#घोषणा LABEL_JF 0xfe

#घोषणा ALLOW \
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)
#घोषणा DENY \
	BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL)
#घोषणा JUMP(labels, label) \
	BPF_JUMP(BPF_JMP+BPF_JA, FIND_LABEL((labels), (label)), \
		 JUMP_JT, JUMP_JF)
#घोषणा LABEL(labels, label) \
	BPF_JUMP(BPF_JMP+BPF_JA, FIND_LABEL((labels), (label)), \
		 LABEL_JT, LABEL_JF)
#घोषणा SYSCALL(nr, jt) \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (nr), 0, 1), \
	jt

/* Lame, but just an example */
#घोषणा FIND_LABEL(labels, label) seccomp_bpf_label((labels), #label)

#घोषणा EXPAND(...) __VA_ARGS__

/* Ensure that we load the logically correct offset. */
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
#घोषणा LO_ARG(idx) दुरत्व(काष्ठा seccomp_data, args[(idx)])
#या_अगर __BYTE_ORDER == __BIG_ENDIAN
#घोषणा LO_ARG(idx) दुरत्व(काष्ठा seccomp_data, args[(idx)]) + माप(__u32)
#अन्यथा
#त्रुटि "Unknown endianness"
#पूर्ण_अगर

/* Map all width-sensitive operations */
#अगर __BITS_PER_LONG == 32

#घोषणा JEQ(x, jt) JEQ32(x, EXPAND(jt))
#घोषणा JNE(x, jt) JNE32(x, EXPAND(jt))
#घोषणा JGT(x, jt) JGT32(x, EXPAND(jt))
#घोषणा JLT(x, jt) JLT32(x, EXPAND(jt))
#घोषणा JGE(x, jt) JGE32(x, EXPAND(jt))
#घोषणा JLE(x, jt) JLE32(x, EXPAND(jt))
#घोषणा JA(x, jt) JA32(x, EXPAND(jt))
#घोषणा ARG(i) ARG_32(i)

#या_अगर __BITS_PER_LONG == 64

/* Ensure that we load the logically correct offset. */
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
#घोषणा ENDIAN(_lo, _hi) _lo, _hi
#घोषणा HI_ARG(idx) दुरत्व(काष्ठा seccomp_data, args[(idx)]) + माप(__u32)
#या_अगर __BYTE_ORDER == __BIG_ENDIAN
#घोषणा ENDIAN(_lo, _hi) _hi, _lo
#घोषणा HI_ARG(idx) दुरत्व(काष्ठा seccomp_data, args[(idx)])
#पूर्ण_अगर

जोड़ arg64 अणु
	काष्ठा अणु
		__u32 ENDIAN(lo32, hi32);
	पूर्ण;
	__u64 u64;
पूर्ण;

#घोषणा JEQ(x, jt) \
	JEQ64(((जोड़ arg64)अणु.u64 = (x)पूर्ण).lo32, \
	      ((जोड़ arg64)अणु.u64 = (x)पूर्ण).hi32, \
	      EXPAND(jt))
#घोषणा JGT(x, jt) \
	JGT64(((जोड़ arg64)अणु.u64 = (x)पूर्ण).lo32, \
	      ((जोड़ arg64)अणु.u64 = (x)पूर्ण).hi32, \
	      EXPAND(jt))
#घोषणा JGE(x, jt) \
	JGE64(((जोड़ arg64)अणु.u64 = (x)पूर्ण).lo32, \
	      ((जोड़ arg64)अणु.u64 = (x)पूर्ण).hi32, \
	      EXPAND(jt))
#घोषणा JNE(x, jt) \
	JNE64(((जोड़ arg64)अणु.u64 = (x)पूर्ण).lo32, \
	      ((जोड़ arg64)अणु.u64 = (x)पूर्ण).hi32, \
	      EXPAND(jt))
#घोषणा JLT(x, jt) \
	JLT64(((जोड़ arg64)अणु.u64 = (x)पूर्ण).lo32, \
	      ((जोड़ arg64)अणु.u64 = (x)पूर्ण).hi32, \
	      EXPAND(jt))
#घोषणा JLE(x, jt) \
	JLE64(((जोड़ arg64)अणु.u64 = (x)पूर्ण).lo32, \
	      ((जोड़ arg64)अणु.u64 = (x)पूर्ण).hi32, \
	      EXPAND(jt))

#घोषणा JA(x, jt) \
	JA64(((जोड़ arg64)अणु.u64 = (x)पूर्ण).lo32, \
	       ((जोड़ arg64)अणु.u64 = (x)पूर्ण).hi32, \
	       EXPAND(jt))
#घोषणा ARG(i) ARG_64(i)

#अन्यथा
#त्रुटि __BITS_PER_LONG value unusable.
#पूर्ण_अगर

/* Loads the arg पूर्णांकo A */
#घोषणा ARG_32(idx) \
	BPF_STMT(BPF_LD+BPF_W+BPF_ABS, LO_ARG(idx))

/* Loads lo पूर्णांकo M[0] and hi पूर्णांकo M[1] and A */
#घोषणा ARG_64(idx) \
	BPF_STMT(BPF_LD+BPF_W+BPF_ABS, LO_ARG(idx)), \
	BPF_STMT(BPF_ST, 0), /* lo -> M[0] */ \
	BPF_STMT(BPF_LD+BPF_W+BPF_ABS, HI_ARG(idx)), \
	BPF_STMT(BPF_ST, 1) /* hi -> M[1] */

#घोषणा JEQ32(value, jt) \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (value), 0, 1), \
	jt

#घोषणा JNE32(value, jt) \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (value), 1, 0), \
	jt

#घोषणा JA32(value, jt) \
	BPF_JUMP(BPF_JMP+BPF_JSET+BPF_K, (value), 0, 1), \
	jt

#घोषणा JGE32(value, jt) \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (value), 0, 1), \
	jt

#घोषणा JGT32(value, jt) \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (value), 0, 1), \
	jt

#घोषणा JLE32(value, jt) \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (value), 1, 0), \
	jt

#घोषणा JLT32(value, jt) \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (value), 1, 0), \
	jt

/*
 * All the JXX64 checks assume lo is saved in M[0] and hi is saved in both
 * A and M[1]. This invariant is kept by restoring A अगर necessary.
 */
#घोषणा JEQ64(lo, hi, jt) \
	/* अगर (hi != arg.hi) जाओ NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 5), \
	BPF_STMT(BPF_LD+BPF_MEM, 0), /* swap in lo */ \
	/* अगर (lo != arg.lo) जाओ NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (lo), 0, 2), \
	BPF_STMT(BPF_LD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_LD+BPF_MEM, 1)

#घोषणा JNE64(lo, hi, jt) \
	/* अगर (hi != arg.hi) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 3), \
	BPF_STMT(BPF_LD+BPF_MEM, 0), \
	/* अगर (lo != arg.lo) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (lo), 2, 0), \
	BPF_STMT(BPF_LD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_LD+BPF_MEM, 1)

#घोषणा JA64(lo, hi, jt) \
	/* अगर (hi & arg.hi) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JSET+BPF_K, (hi), 3, 0), \
	BPF_STMT(BPF_LD+BPF_MEM, 0), \
	/* अगर (lo & arg.lo) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JSET+BPF_K, (lo), 0, 2), \
	BPF_STMT(BPF_LD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_LD+BPF_MEM, 1)

#घोषणा JGE64(lo, hi, jt) \
	/* अगर (hi > arg.hi) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (hi), 4, 0), \
	/* अगर (hi != arg.hi) जाओ NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 5), \
	BPF_STMT(BPF_LD+BPF_MEM, 0), \
	/* अगर (lo >= arg.lo) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (lo), 0, 2), \
	BPF_STMT(BPF_LD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_LD+BPF_MEM, 1)

#घोषणा JGT64(lo, hi, jt) \
	/* अगर (hi > arg.hi) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (hi), 4, 0), \
	/* अगर (hi != arg.hi) जाओ NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 5), \
	BPF_STMT(BPF_LD+BPF_MEM, 0), \
	/* अगर (lo > arg.lo) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (lo), 0, 2), \
	BPF_STMT(BPF_LD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_LD+BPF_MEM, 1)

#घोषणा JLE64(lo, hi, jt) \
	/* अगर (hi < arg.hi) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (hi), 0, 4), \
	/* अगर (hi != arg.hi) जाओ NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 5), \
	BPF_STMT(BPF_LD+BPF_MEM, 0), \
	/* अगर (lo <= arg.lo) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGT+BPF_K, (lo), 2, 0), \
	BPF_STMT(BPF_LD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_LD+BPF_MEM, 1)

#घोषणा JLT64(lo, hi, jt) \
	/* अगर (hi < arg.hi) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (hi), 0, 4), \
	/* अगर (hi != arg.hi) जाओ NOMATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, (hi), 0, 5), \
	BPF_STMT(BPF_LD+BPF_MEM, 0), \
	/* अगर (lo < arg.lo) जाओ MATCH; */ \
	BPF_JUMP(BPF_JMP+BPF_JGE+BPF_K, (lo), 2, 0), \
	BPF_STMT(BPF_LD+BPF_MEM, 1), \
	jt, \
	BPF_STMT(BPF_LD+BPF_MEM, 1)

#घोषणा LOAD_SYSCALL_NR \
	BPF_STMT(BPF_LD+BPF_W+BPF_ABS, \
		 दुरत्व(काष्ठा seccomp_data, nr))

#पूर्ण_अगर  /* __BPF_HELPER_H__ */
