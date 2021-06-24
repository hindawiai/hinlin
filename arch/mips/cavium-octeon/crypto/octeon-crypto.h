<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012-2013 Cavium Inc., All Rights Reserved.
 *
 * MD5/SHA1/SHA256/SHA512 inकाष्ठाion definitions added by
 * Aaro Koskinen <aaro.koskinen@iki.fi>.
 *
 */
#अगर_अघोषित __LINUX_OCTEON_CRYPTO_H
#घोषणा __LINUX_OCTEON_CRYPTO_H

#समावेश <linux/sched.h>
#समावेश <यंत्र/mipsregs.h>

#घोषणा OCTEON_CR_OPCODE_PRIORITY 300

बाह्य अचिन्हित दीर्घ octeon_crypto_enable(काष्ठा octeon_cop2_state *state);
बाह्य व्योम octeon_crypto_disable(काष्ठा octeon_cop2_state *state,
				  अचिन्हित दीर्घ flags);

/*
 * Macros needed to implement MD5/SHA1/SHA256:
 */

/*
 * The index can be 0-1 (MD5) or 0-2 (SHA1), 0-3 (SHA256).
 */
#घोषणा ग_लिखो_octeon_64bit_hash_dword(value, index)	\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x0048+" STR(index)		\
	:						\
	: [rt] "d" (cpu_to_be64(value)));		\
पूर्ण जबतक (0)

/*
 * The index can be 0-1 (MD5) or 0-2 (SHA1), 0-3 (SHA256).
 */
#घोषणा पढ़ो_octeon_64bit_hash_dword(index)		\
(अणु							\
	__be64 __value;					\
							\
	__यंत्र__ __अस्थिर__ (				\
	"dmfc2 %[rt],0x0048+" STR(index)		\
	: [rt] "=d" (__value)				\
	: );						\
							\
	be64_to_cpu(__value);				\
पूर्ण)

/*
 * The index can be 0-6.
 */
#घोषणा ग_लिखो_octeon_64bit_block_dword(value, index)	\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x0040+" STR(index)		\
	:						\
	: [rt] "d" (cpu_to_be64(value)));		\
पूर्ण जबतक (0)

/*
 * The value is the final block dword (64-bit).
 */
#घोषणा octeon_md5_start(value)				\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x4047"				\
	:						\
	: [rt] "d" (cpu_to_be64(value)));		\
पूर्ण जबतक (0)

/*
 * The value is the final block dword (64-bit).
 */
#घोषणा octeon_sha1_start(value)			\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x4057"				\
	:						\
	: [rt] "d" (value));				\
पूर्ण जबतक (0)

/*
 * The value is the final block dword (64-bit).
 */
#घोषणा octeon_sha256_start(value)			\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x404f"				\
	:						\
	: [rt] "d" (value));				\
पूर्ण जबतक (0)

/*
 * Macros needed to implement SHA512:
 */

/*
 * The index can be 0-7.
 */
#घोषणा ग_लिखो_octeon_64bit_hash_sha512(value, index)	\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x0250+" STR(index)		\
	:						\
	: [rt] "d" (value));				\
पूर्ण जबतक (0)

/*
 * The index can be 0-7.
 */
#घोषणा पढ़ो_octeon_64bit_hash_sha512(index)		\
(अणु							\
	u64 __value;					\
							\
	__यंत्र__ __अस्थिर__ (				\
	"dmfc2 %[rt],0x0250+" STR(index)		\
	: [rt] "=d" (__value)				\
	: );						\
							\
	__value;					\
पूर्ण)

/*
 * The index can be 0-14.
 */
#घोषणा ग_लिखो_octeon_64bit_block_sha512(value, index)	\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x0240+" STR(index)		\
	:						\
	: [rt] "d" (value));				\
पूर्ण जबतक (0)

/*
 * The value is the final block word (64-bit).
 */
#घोषणा octeon_sha512_start(value)			\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x424f"				\
	:						\
	: [rt] "d" (value));				\
पूर्ण जबतक (0)

/*
 * The value is the final block dword (64-bit).
 */
#घोषणा octeon_sha1_start(value)			\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x4057"				\
	:						\
	: [rt] "d" (value));				\
पूर्ण जबतक (0)

/*
 * The value is the final block dword (64-bit).
 */
#घोषणा octeon_sha256_start(value)			\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x404f"				\
	:						\
	: [rt] "d" (value));				\
पूर्ण जबतक (0)

/*
 * Macros needed to implement SHA512:
 */

/*
 * The index can be 0-7.
 */
#घोषणा ग_लिखो_octeon_64bit_hash_sha512(value, index)	\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x0250+" STR(index)		\
	:						\
	: [rt] "d" (value));				\
पूर्ण जबतक (0)

/*
 * The index can be 0-7.
 */
#घोषणा पढ़ो_octeon_64bit_hash_sha512(index)		\
(अणु							\
	u64 __value;					\
							\
	__यंत्र__ __अस्थिर__ (				\
	"dmfc2 %[rt],0x0250+" STR(index)		\
	: [rt] "=d" (__value)				\
	: );						\
							\
	__value;					\
पूर्ण)

/*
 * The index can be 0-14.
 */
#घोषणा ग_लिखो_octeon_64bit_block_sha512(value, index)	\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x0240+" STR(index)		\
	:						\
	: [rt] "d" (value));				\
पूर्ण जबतक (0)

/*
 * The value is the final block word (64-bit).
 */
#घोषणा octeon_sha512_start(value)			\
करो अणु							\
	__यंत्र__ __अस्थिर__ (				\
	"dmtc2 %[rt],0x424f"				\
	:						\
	: [rt] "d" (value));				\
पूर्ण जबतक (0)

#पूर्ण_अगर /* __LINUX_OCTEON_CRYPTO_H */
