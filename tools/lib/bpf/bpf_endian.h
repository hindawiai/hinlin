<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */
#अगर_अघोषित __BPF_ENDIAN__
#घोषणा __BPF_ENDIAN__

/*
 * Isolate byte #n and put it पूर्णांकo byte #m, क्रम __u##b type.
 * E.g., moving byte #6 (nnnnnnnn) पूर्णांकo byte #1 (mmmmmmmm) क्रम __u64:
 * 1) xxxxxxxx nnnnnnnn xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx mmmmmmmm xxxxxxxx
 * 2) nnnnnnnn xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx mmmmmmmm xxxxxxxx 00000000
 * 3) 00000000 00000000 00000000 00000000 00000000 00000000 00000000 nnnnnnnn
 * 4) 00000000 00000000 00000000 00000000 00000000 00000000 nnnnnnnn 00000000
 */
#घोषणा ___bpf_mvb(x, b, n, m) ((__u##b)(x) << (b-(n+1)*8) >> (b-8) << (m*8))

#घोषणा ___bpf_swab16(x) ((__u16)(			\
			  ___bpf_mvb(x, 16, 0, 1) |	\
			  ___bpf_mvb(x, 16, 1, 0)))

#घोषणा ___bpf_swab32(x) ((__u32)(			\
			  ___bpf_mvb(x, 32, 0, 3) |	\
			  ___bpf_mvb(x, 32, 1, 2) |	\
			  ___bpf_mvb(x, 32, 2, 1) |	\
			  ___bpf_mvb(x, 32, 3, 0)))

#घोषणा ___bpf_swab64(x) ((__u64)(			\
			  ___bpf_mvb(x, 64, 0, 7) |	\
			  ___bpf_mvb(x, 64, 1, 6) |	\
			  ___bpf_mvb(x, 64, 2, 5) |	\
			  ___bpf_mvb(x, 64, 3, 4) |	\
			  ___bpf_mvb(x, 64, 4, 3) |	\
			  ___bpf_mvb(x, 64, 5, 2) |	\
			  ___bpf_mvb(x, 64, 6, 1) |	\
			  ___bpf_mvb(x, 64, 7, 0)))

/* LLVM's BPF target selects the endianness of the CPU
 * it compiles on, or the user specअगरies (bpfel/bpfeb),
 * respectively. The used __BYTE_ORDER__ is defined by
 * the compiler, we cannot rely on __BYTE_ORDER from
 * libc headers, since it करोesn't reflect the actual
 * requested byte order.
 *
 * Note, LLVM's BPF target has dअगरferent __builtin_bswapX()
 * semantics. It करोes map to BPF_ALU | BPF_END | BPF_TO_BE
 * in bpfel and bpfeb हाल, which means below, that we map
 * to cpu_to_be16(). We could use it unconditionally in BPF
 * हाल, but better not rely on it, so that this header here
 * can be used from application and BPF program side, which
 * use dअगरferent tarमाला_लो.
 */
#अगर __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
# define __bpf_ntohs(x)			__builtin_bswap16(x)
# define __bpf_htons(x)			__builtin_bswap16(x)
# define __bpf_स्थिरant_ntohs(x)	___bpf_swab16(x)
# define __bpf_स्थिरant_htons(x)	___bpf_swab16(x)
# define __bpf_ntohl(x)			__builtin_bswap32(x)
# define __bpf_htonl(x)			__builtin_bswap32(x)
# define __bpf_स्थिरant_ntohl(x)	___bpf_swab32(x)
# define __bpf_स्थिरant_htonl(x)	___bpf_swab32(x)
# define __bpf_be64_to_cpu(x)		__builtin_bswap64(x)
# define __bpf_cpu_to_be64(x)		__builtin_bswap64(x)
# define __bpf_स्थिरant_be64_to_cpu(x)	___bpf_swab64(x)
# define __bpf_स्थिरant_cpu_to_be64(x)	___bpf_swab64(x)
#या_अगर __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
# define __bpf_ntohs(x)			(x)
# define __bpf_htons(x)			(x)
# define __bpf_स्थिरant_ntohs(x)	(x)
# define __bpf_स्थिरant_htons(x)	(x)
# define __bpf_ntohl(x)			(x)
# define __bpf_htonl(x)			(x)
# define __bpf_स्थिरant_ntohl(x)	(x)
# define __bpf_स्थिरant_htonl(x)	(x)
# define __bpf_be64_to_cpu(x)		(x)
# define __bpf_cpu_to_be64(x)		(x)
# define __bpf_स्थिरant_be64_to_cpu(x)  (x)
# define __bpf_स्थिरant_cpu_to_be64(x)  (x)
#अन्यथा
# error "Fix your compiler's __BYTE_ORDER__?!"
#पूर्ण_अगर

#घोषणा bpf_htons(x)				\
	(__builtin_स्थिरant_p(x) ?		\
	 __bpf_स्थिरant_htons(x) : __bpf_htons(x))
#घोषणा bpf_ntohs(x)				\
	(__builtin_स्थिरant_p(x) ?		\
	 __bpf_स्थिरant_ntohs(x) : __bpf_ntohs(x))
#घोषणा bpf_htonl(x)				\
	(__builtin_स्थिरant_p(x) ?		\
	 __bpf_स्थिरant_htonl(x) : __bpf_htonl(x))
#घोषणा bpf_ntohl(x)				\
	(__builtin_स्थिरant_p(x) ?		\
	 __bpf_स्थिरant_ntohl(x) : __bpf_ntohl(x))
#घोषणा bpf_cpu_to_be64(x)			\
	(__builtin_स्थिरant_p(x) ?		\
	 __bpf_स्थिरant_cpu_to_be64(x) : __bpf_cpu_to_be64(x))
#घोषणा bpf_be64_to_cpu(x)			\
	(__builtin_स्थिरant_p(x) ?		\
	 __bpf_स्थिरant_be64_to_cpu(x) : __bpf_be64_to_cpu(x))

#पूर्ण_अगर /* __BPF_ENDIAN__ */
