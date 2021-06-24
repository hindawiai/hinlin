<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* TTL modअगरication module क्रम IP tables
 * (C) 2000 by Harald Welte <laक्रमge@netfilter.org> */

#अगर_अघोषित _IPT_TTL_H
#घोषणा _IPT_TTL_H

#समावेश <linux/types.h>

क्रमागत अणु
	IPT_TTL_SET = 0,
	IPT_TTL_INC,
	IPT_TTL_DEC
पूर्ण;

#घोषणा IPT_TTL_MAXMODE	IPT_TTL_DEC

काष्ठा ipt_TTL_info अणु
	__u8	mode;
	__u8	ttl;
पूर्ण;


#पूर्ण_अगर
