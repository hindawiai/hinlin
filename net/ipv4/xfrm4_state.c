<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xfrm4_state.c
 *
 * Changes:
 * 	YOSHIFUJI Hideaki @USAGI
 * 		Split up af-specअगरic portion
 *
 */

#समावेश <net/xfrm.h>

अटल काष्ठा xfrm_state_afinfo xfrm4_state_afinfo = अणु
	.family			= AF_INET,
	.proto			= IPPROTO_IPIP,
	.output			= xfrm4_output,
	.transport_finish	= xfrm4_transport_finish,
	.local_error		= xfrm4_local_error,
पूर्ण;

व्योम __init xfrm4_state_init(व्योम)
अणु
	xfrm_state_रेजिस्टर_afinfo(&xfrm4_state_afinfo);
पूर्ण
