<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* Hop Limit modअगरication module क्रम ip6tables
 * Maciej Soltysiak <solt@dns.toxicfilms.tv>
 * Based on HW's TTL module */

#अगर_अघोषित _IP6T_HL_H
#घोषणा _IP6T_HL_H

#समावेश <linux/types.h>

क्रमागत अणु
	IP6T_HL_SET = 0,
	IP6T_HL_INC,
	IP6T_HL_DEC
पूर्ण;

#घोषणा IP6T_HL_MAXMODE	IP6T_HL_DEC

काष्ठा ip6t_HL_info अणु
	__u8	mode;
	__u8	hop_limit;
पूर्ण;


#पूर्ण_अगर
