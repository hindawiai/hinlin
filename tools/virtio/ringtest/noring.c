<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश "main.h"
#समावेश <निश्चित.स>

/* stub implementation: useful क्रम measuring overhead */
व्योम alloc_ring(व्योम)
अणु
पूर्ण

/* guest side */
पूर्णांक add_inbuf(अचिन्हित len, व्योम *buf, व्योम *datap)
अणु
	वापस 0;
पूर्ण

/*
 * skb_array API provides no way क्रम producer to find out whether a given
 * buffer was consumed.  Our tests merely require that a successful get_buf
 * implies that add_inbuf succeed in the past, and that add_inbuf will succeed,
 * fake it accordingly.
 */
व्योम *get_buf(अचिन्हित *lenp, व्योम **bufp)
अणु
	वापस "Buffer";
पूर्ण

bool used_empty()
अणु
	वापस false;
पूर्ण

व्योम disable_call()
अणु
	निश्चित(0);
पूर्ण

bool enable_call()
अणु
	निश्चित(0);
पूर्ण

व्योम kick_available(व्योम)
अणु
	निश्चित(0);
पूर्ण

/* host side */
व्योम disable_kick()
अणु
	निश्चित(0);
पूर्ण

bool enable_kick()
अणु
	निश्चित(0);
पूर्ण

bool avail_empty()
अणु
	वापस false;
पूर्ण

bool use_buf(अचिन्हित *lenp, व्योम **bufp)
अणु
	वापस true;
पूर्ण

व्योम call_used(व्योम)
अणु
	निश्चित(0);
पूर्ण
