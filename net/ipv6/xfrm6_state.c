<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xfrm6_state.c: based on xfrm4_state.c
 *
 * Authors:
 *	Mitsuru KANDA @USAGI
 *	Kazunori MIYAZAWA @USAGI
 *	Kunihiro Ishiguro <kunihiro@ipinfusion.com>
 *		IPv6 support
 *	YOSHIFUJI Hideaki @USAGI
 *		Split up af-specअगरic portion
 *
 */

#समावेश <net/xfrm.h>

अटल काष्ठा xfrm_state_afinfo xfrm6_state_afinfo = अणु
	.family			= AF_INET6,
	.proto			= IPPROTO_IPV6,
	.output			= xfrm6_output,
	.transport_finish	= xfrm6_transport_finish,
	.local_error		= xfrm6_local_error,
पूर्ण;

पूर्णांक __init xfrm6_state_init(व्योम)
अणु
	वापस xfrm_state_रेजिस्टर_afinfo(&xfrm6_state_afinfo);
पूर्ण

व्योम xfrm6_state_fini(व्योम)
अणु
	xfrm_state_unरेजिस्टर_afinfo(&xfrm6_state_afinfo);
पूर्ण
