<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* ip6tables module क्रम matching the Hop Limit value
 * Maciej Soltysiak <solt@dns.toxicfilms.tv>
 * Based on HW's ttl module */

#अगर_अघोषित _IP6T_HL_H
#घोषणा _IP6T_HL_H

#समावेश <linux/types.h>

क्रमागत अणु
	IP6T_HL_EQ = 0,		/* equals */
	IP6T_HL_NE,		/* not equals */
	IP6T_HL_LT,		/* less than */
	IP6T_HL_GT,		/* greater than */
पूर्ण;


काष्ठा ip6t_hl_info अणु
	__u8	mode;
	__u8	hop_limit;
पूर्ण;


#पूर्ण_अगर
