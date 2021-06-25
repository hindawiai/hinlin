<शैली गुरु>
/*
 *   Copyright (c) 2010 Wang Lei
 *   Author(s): Wang Lei (wang840925@gmail.com). All Rights Reserved.
 *
 *   Internal DNS Rsolver stuff
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, see <http://www.gnu.org/licenses/>.
 */

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>

/*
 * Layout of key payload words.
 */
क्रमागत अणु
	dns_key_data,
	dns_key_error,
पूर्ण;

/*
 * dns_key.c
 */
बाह्य स्थिर काष्ठा cred *dns_resolver_cache;

/*
 * debug tracing
 */
बाह्य अचिन्हित पूर्णांक dns_resolver_debug;

#घोषणा	kdebug(FMT, ...)				\
करो अणु							\
	अगर (unlikely(dns_resolver_debug))		\
		prपूर्णांकk(KERN_DEBUG "[%-6.6s] "FMT"\n",	\
		       current->comm, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा kenter(FMT, ...) kdebug("==> %s("FMT")", __func__, ##__VA_ARGS__)
#घोषणा kleave(FMT, ...) kdebug("<== %s()"FMT"", __func__, ##__VA_ARGS__)
