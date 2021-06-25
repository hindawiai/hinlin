<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश <sys/socket.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक get_set_sk_priority(व्योम *ctx)
अणु
	पूर्णांक prio;

	/* Verअगरy that context allows calling bpf_माला_लोockopt and
	 * bpf_setsockopt by पढ़ोing and writing back socket
	 * priority.
	 */

	अगर (bpf_माला_लोockopt(ctx, SOL_SOCKET, SO_PRIORITY, &prio, माप(prio)))
		वापस 0;
	अगर (bpf_setsockopt(ctx, SOL_SOCKET, SO_PRIORITY, &prio, माप(prio)))
		वापस 0;

	वापस 1;
पूर्ण
