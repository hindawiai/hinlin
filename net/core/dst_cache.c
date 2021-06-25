<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/core/dst_cache.c - dst entry cache
 *
 * Copyright (c) 2016 Paolo Abeni <pabeni@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <net/dst_cache.h>
#समावेश <net/route.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ip6_fib.h>
#पूर्ण_अगर
#समावेश <uapi/linux/in.h>

काष्ठा dst_cache_pcpu अणु
	अचिन्हित दीर्घ refresh_ts;
	काष्ठा dst_entry *dst;
	u32 cookie;
	जोड़ अणु
		काष्ठा in_addr in_saddr;
		काष्ठा in6_addr in6_saddr;
	पूर्ण;
पूर्ण;

अटल व्योम dst_cache_per_cpu_dst_set(काष्ठा dst_cache_pcpu *dst_cache,
				      काष्ठा dst_entry *dst, u32 cookie)
अणु
	dst_release(dst_cache->dst);
	अगर (dst)
		dst_hold(dst);

	dst_cache->cookie = cookie;
	dst_cache->dst = dst;
पूर्ण

अटल काष्ठा dst_entry *dst_cache_per_cpu_get(काष्ठा dst_cache *dst_cache,
					       काष्ठा dst_cache_pcpu *idst)
अणु
	काष्ठा dst_entry *dst;

	dst = idst->dst;
	अगर (!dst)
		जाओ fail;

	/* the cache alपढ़ोy hold a dst reference; it can't go away */
	dst_hold(dst);

	अगर (unlikely(!समय_after(idst->refresh_ts, dst_cache->reset_ts) ||
		     (dst->obsolete && !dst->ops->check(dst, idst->cookie)))) अणु
		dst_cache_per_cpu_dst_set(idst, शून्य, 0);
		dst_release(dst);
		जाओ fail;
	पूर्ण
	वापस dst;

fail:
	idst->refresh_ts = jअगरfies;
	वापस शून्य;
पूर्ण

काष्ठा dst_entry *dst_cache_get(काष्ठा dst_cache *dst_cache)
अणु
	अगर (!dst_cache->cache)
		वापस शून्य;

	वापस dst_cache_per_cpu_get(dst_cache, this_cpu_ptr(dst_cache->cache));
पूर्ण
EXPORT_SYMBOL_GPL(dst_cache_get);

काष्ठा rtable *dst_cache_get_ip4(काष्ठा dst_cache *dst_cache, __be32 *saddr)
अणु
	काष्ठा dst_cache_pcpu *idst;
	काष्ठा dst_entry *dst;

	अगर (!dst_cache->cache)
		वापस शून्य;

	idst = this_cpu_ptr(dst_cache->cache);
	dst = dst_cache_per_cpu_get(dst_cache, idst);
	अगर (!dst)
		वापस शून्य;

	*saddr = idst->in_saddr.s_addr;
	वापस container_of(dst, काष्ठा rtable, dst);
पूर्ण
EXPORT_SYMBOL_GPL(dst_cache_get_ip4);

व्योम dst_cache_set_ip4(काष्ठा dst_cache *dst_cache, काष्ठा dst_entry *dst,
		       __be32 saddr)
अणु
	काष्ठा dst_cache_pcpu *idst;

	अगर (!dst_cache->cache)
		वापस;

	idst = this_cpu_ptr(dst_cache->cache);
	dst_cache_per_cpu_dst_set(idst, dst, 0);
	idst->in_saddr.s_addr = saddr;
पूर्ण
EXPORT_SYMBOL_GPL(dst_cache_set_ip4);

#अगर IS_ENABLED(CONFIG_IPV6)
व्योम dst_cache_set_ip6(काष्ठा dst_cache *dst_cache, काष्ठा dst_entry *dst,
		       स्थिर काष्ठा in6_addr *saddr)
अणु
	काष्ठा dst_cache_pcpu *idst;

	अगर (!dst_cache->cache)
		वापस;

	idst = this_cpu_ptr(dst_cache->cache);
	dst_cache_per_cpu_dst_set(this_cpu_ptr(dst_cache->cache), dst,
				  rt6_get_cookie((काष्ठा rt6_info *)dst));
	idst->in6_saddr = *saddr;
पूर्ण
EXPORT_SYMBOL_GPL(dst_cache_set_ip6);

काष्ठा dst_entry *dst_cache_get_ip6(काष्ठा dst_cache *dst_cache,
				    काष्ठा in6_addr *saddr)
अणु
	काष्ठा dst_cache_pcpu *idst;
	काष्ठा dst_entry *dst;

	अगर (!dst_cache->cache)
		वापस शून्य;

	idst = this_cpu_ptr(dst_cache->cache);
	dst = dst_cache_per_cpu_get(dst_cache, idst);
	अगर (!dst)
		वापस शून्य;

	*saddr = idst->in6_saddr;
	वापस dst;
पूर्ण
EXPORT_SYMBOL_GPL(dst_cache_get_ip6);
#पूर्ण_अगर

पूर्णांक dst_cache_init(काष्ठा dst_cache *dst_cache, gfp_t gfp)
अणु
	dst_cache->cache = alloc_percpu_gfp(काष्ठा dst_cache_pcpu,
					    gfp | __GFP_ZERO);
	अगर (!dst_cache->cache)
		वापस -ENOMEM;

	dst_cache_reset(dst_cache);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dst_cache_init);

व्योम dst_cache_destroy(काष्ठा dst_cache *dst_cache)
अणु
	पूर्णांक i;

	अगर (!dst_cache->cache)
		वापस;

	क्रम_each_possible_cpu(i)
		dst_release(per_cpu_ptr(dst_cache->cache, i)->dst);

	मुक्त_percpu(dst_cache->cache);
पूर्ण
EXPORT_SYMBOL_GPL(dst_cache_destroy);
