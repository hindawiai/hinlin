<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* IP tables module क्रम matching the value of the TTL
 * (C) 2000 by Harald Welte <laक्रमge@gnumonks.org> */

#अगर_अघोषित _IPT_TTL_H
#घोषणा _IPT_TTL_H

#समावेश <linux/types.h>

क्रमागत अणु
	IPT_TTL_EQ = 0,		/* equals */
	IPT_TTL_NE,		/* not equals */
	IPT_TTL_LT,		/* less than */
	IPT_TTL_GT,		/* greater than */
पूर्ण;


काष्ठा ipt_ttl_info अणु
	__u8	mode;
	__u8	ttl;
पूर्ण;


#पूर्ण_अगर
