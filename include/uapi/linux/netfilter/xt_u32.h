<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_U32_H
#घोषणा _XT_U32_H 1

#समावेश <linux/types.h>

क्रमागत xt_u32_ops अणु
	XT_U32_AND,
	XT_U32_LEFTSH,
	XT_U32_RIGHTSH,
	XT_U32_AT,
पूर्ण;

काष्ठा xt_u32_location_element अणु
	__u32 number;
	__u8 nextop;
पूर्ण;

काष्ठा xt_u32_value_element अणु
	__u32 min;
	__u32 max;
पूर्ण;

/*
 * Any way to allow क्रम an arbitrary number of elements?
 * For now, I settle with a limit of 10 each.
 */
#घोषणा XT_U32_MAXSIZE 10

काष्ठा xt_u32_test अणु
	काष्ठा xt_u32_location_element location[XT_U32_MAXSIZE+1];
	काष्ठा xt_u32_value_element value[XT_U32_MAXSIZE+1];
	__u8 nnums;
	__u8 nvalues;
पूर्ण;

काष्ठा xt_u32 अणु
	काष्ठा xt_u32_test tests[XT_U32_MAXSIZE+1];
	__u8 ntests;
	__u8 invert;
पूर्ण;

#पूर्ण_अगर /* _XT_U32_H */
