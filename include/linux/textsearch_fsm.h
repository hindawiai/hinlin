<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_TEXTSEARCH_FSM_H
#घोषणा __LINUX_TEXTSEARCH_FSM_H

#समावेश <linux/types.h>

क्रमागत अणु
	TS_FSM_SPECIFIC,	/* specअगरic अक्षरacter */
	TS_FSM_WILDCARD,	/* any अक्षरacter */
	TS_FSM_DIGIT,		/* है_अंक() */
	TS_FSM_XDIGIT,		/* है_षष्ठादशक() */
	TS_FSM_PRINT,		/* है_छाप() */
	TS_FSM_ALPHA,		/* है_अक्षर() */
	TS_FSM_ALNUM,		/* है_अक्षर_अंक() */
	TS_FSM_ASCII,		/* isascii() */
	TS_FSM_CNTRL,		/* है_नियंत्रण() */
	TS_FSM_GRAPH,		/* है_चित्र() */
	TS_FSM_LOWER,		/* है_छोटा() */
	TS_FSM_UPPER,		/* है_बड़ा() */
	TS_FSM_PUNCT,		/* है_विराम() */
	TS_FSM_SPACE,		/* है_खाली() */
	__TS_FSM_TYPE_MAX,
पूर्ण;
#घोषणा TS_FSM_TYPE_MAX (__TS_FSM_TYPE_MAX - 1)

क्रमागत अणु
	TS_FSM_SINGLE,		/* 1 occurrence */
	TS_FSM_PERHAPS,		/* 1 or 0 occurrence */
	TS_FSM_ANY,		/* 0..n occurrences */
	TS_FSM_MULTI,		/* 1..n occurrences */
	TS_FSM_HEAD_IGNORE,	/* 0..n ignored occurrences at head */
	__TS_FSM_RECUR_MAX,
पूर्ण;
#घोषणा TS_FSM_RECUR_MAX (__TS_FSM_RECUR_MAX - 1)

/**
 * काष्ठा ts_fsm_token - state machine token (state)
 * @type: type of token
 * @recur: number of recurrences
 * @value: अक्षरacter value क्रम TS_FSM_SPECIFIC
 */
काष्ठा ts_fsm_token
अणु
	__u16		type;
	__u8		recur;
	__u8		value;
पूर्ण;

#पूर्ण_अगर
