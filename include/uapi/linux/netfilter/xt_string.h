<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_STRING_H
#घोषणा _XT_STRING_H

#समावेश <linux/types.h>

#घोषणा XT_STRING_MAX_PATTERN_SIZE 128
#घोषणा XT_STRING_MAX_ALGO_NAME_SIZE 16

क्रमागत अणु
	XT_STRING_FLAG_INVERT		= 0x01,
	XT_STRING_FLAG_IGNORECASE	= 0x02
पूर्ण;

काष्ठा xt_string_info अणु
	__u16 from_offset;
	__u16 to_offset;
	अक्षर	  algo[XT_STRING_MAX_ALGO_NAME_SIZE];
	अक्षर 	  pattern[XT_STRING_MAX_PATTERN_SIZE];
	__u8  patlen;
	जोड़ अणु
		काष्ठा अणु
			__u8  invert;
		पूर्ण v0;

		काष्ठा अणु
			__u8  flags;
		पूर्ण v1;
	पूर्ण u;

	/* Used पूर्णांकernally by the kernel */
	काष्ठा ts_config __attribute__((aligned(8))) *config;
पूर्ण;

#पूर्ण_अगर /*_XT_STRING_H*/
