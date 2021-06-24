<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NET_DST_CACHE_H
#घोषणा _NET_DST_CACHE_H

#समावेश <linux/jअगरfies.h>
#समावेश <net/dst.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ip6_fib.h>
#पूर्ण_अगर

काष्ठा dst_cache अणु
	काष्ठा dst_cache_pcpu __percpu *cache;
	अचिन्हित दीर्घ reset_ts;
पूर्ण;

/**
 *	dst_cache_get - perक्रमm cache lookup
 *	@dst_cache: the cache
 *
 *	The caller should use dst_cache_get_ip4() अगर it need to retrieve the
 *	source address to be used when xmitting to the cached dst.
 *	local BH must be disabled.
 */
काष्ठा dst_entry *dst_cache_get(काष्ठा dst_cache *dst_cache);

/**
 *	dst_cache_get_ip4 - perक्रमm cache lookup and fetch ipv4 source address
 *	@dst_cache: the cache
 *	@saddr: वापस value क्रम the retrieved source address
 *
 *	local BH must be disabled.
 */
काष्ठा rtable *dst_cache_get_ip4(काष्ठा dst_cache *dst_cache, __be32 *saddr);

/**
 *	dst_cache_set_ip4 - store the ipv4 dst पूर्णांकo the cache
 *	@dst_cache: the cache
 *	@dst: the entry to be cached
 *	@saddr: the source address to be stored inside the cache
 *
 *	local BH must be disabled.
 */
व्योम dst_cache_set_ip4(काष्ठा dst_cache *dst_cache, काष्ठा dst_entry *dst,
		       __be32 saddr);

#अगर IS_ENABLED(CONFIG_IPV6)

/**
 *	dst_cache_set_ip6 - store the ipv6 dst पूर्णांकo the cache
 *	@dst_cache: the cache
 *	@dst: the entry to be cached
 *	@saddr: the source address to be stored inside the cache
 *
 *	local BH must be disabled.
 */
व्योम dst_cache_set_ip6(काष्ठा dst_cache *dst_cache, काष्ठा dst_entry *dst,
		       स्थिर काष्ठा in6_addr *saddr);

/**
 *	dst_cache_get_ip6 - perक्रमm cache lookup and fetch ipv6 source address
 *	@dst_cache: the cache
 *	@saddr: वापस value क्रम the retrieved source address
 *
 *	local BH must be disabled.
 */
काष्ठा dst_entry *dst_cache_get_ip6(काष्ठा dst_cache *dst_cache,
				    काष्ठा in6_addr *saddr);
#पूर्ण_अगर

/**
 *	dst_cache_reset - invalidate the cache contents
 *	@dst_cache: the cache
 *
 *	This करोes not मुक्त the cached dst to aव्योम races and contentions.
 *	the dst will be मुक्तd on later cache lookup.
 */
अटल अंतरभूत व्योम dst_cache_reset(काष्ठा dst_cache *dst_cache)
अणु
	dst_cache->reset_ts = jअगरfies;
पूर्ण

/**
 *	dst_cache_init - initialize the cache, allocating the required storage
 *	@dst_cache: the cache
 *	@gfp: allocation flags
 */
पूर्णांक dst_cache_init(काष्ठा dst_cache *dst_cache, gfp_t gfp);

/**
 *	dst_cache_destroy - empty the cache and मुक्त the allocated storage
 *	@dst_cache: the cache
 *
 *	No synchronization is enक्रमced: it must be called only when the cache
 *	is unsed.
 */
व्योम dst_cache_destroy(काष्ठा dst_cache *dst_cache);

#पूर्ण_अगर
