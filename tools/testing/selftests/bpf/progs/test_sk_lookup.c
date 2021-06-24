<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
// Copyright (c) 2020 Cloudflare

#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <linux/in.h>
#समावेश <sys/socket.h>

#समावेश <bpf/bpf_endian.h>
#समावेश <bpf/bpf_helpers.h>

#घोषणा IP4(a, b, c, d)					\
	bpf_htonl((((__u32)(a) & 0xffU) << 24) |	\
		  (((__u32)(b) & 0xffU) << 16) |	\
		  (((__u32)(c) & 0xffU) <<  8) |	\
		  (((__u32)(d) & 0xffU) <<  0))
#घोषणा IP6(aaaa, bbbb, cccc, dddd)			\
	अणु bpf_htonl(aaaa), bpf_htonl(bbbb), bpf_htonl(cccc), bpf_htonl(dddd) पूर्ण

/* Macros क्रम least-signअगरicant byte and word accesses. */
#अगर __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#घोषणा LSE_INDEX(index, size) (index)
#अन्यथा
#घोषणा LSE_INDEX(index, size) ((size) - (index) - 1)
#पूर्ण_अगर
#घोषणा LSB(value, index)				\
	(((__u8 *)&(value))[LSE_INDEX((index), माप(value))])
#घोषणा LSW(value, index)				\
	(((__u16 *)&(value))[LSE_INDEX((index), माप(value) / 2)])

#घोषणा MAX_SOCKS 32

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SOCKMAP);
	__uपूर्णांक(max_entries, MAX_SOCKS);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण redir_map SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 2);
	__type(key, पूर्णांक);
	__type(value, पूर्णांक);
पूर्ण run_map SEC(".maps");

क्रमागत अणु
	PROG1 = 0,
	PROG2,
पूर्ण;

क्रमागत अणु
	SERVER_A = 0,
	SERVER_B,
पूर्ण;

/* Addressable key/value स्थिरants क्रम convenience */
अटल स्थिर पूर्णांक KEY_PROG1 = PROG1;
अटल स्थिर पूर्णांक KEY_PROG2 = PROG2;
अटल स्थिर पूर्णांक PROG_DONE = 1;

अटल स्थिर __u32 KEY_SERVER_A = SERVER_A;
अटल स्थिर __u32 KEY_SERVER_B = SERVER_B;

अटल स्थिर __u16 SRC_PORT = bpf_htons(8008);
अटल स्थिर __u32 SRC_IP4 = IP4(127, 0, 0, 2);
अटल स्थिर __u32 SRC_IP6[] = IP6(0xfd000000, 0x0, 0x0, 0x00000002);

अटल स्थिर __u16 DST_PORT = 7007; /* Host byte order */
अटल स्थिर __u32 DST_IP4 = IP4(127, 0, 0, 1);
अटल स्थिर __u32 DST_IP6[] = IP6(0xfd000000, 0x0, 0x0, 0x00000001);

SEC("sk_lookup/lookup_pass")
पूर्णांक lookup_pass(काष्ठा bpf_sk_lookup *ctx)
अणु
	वापस SK_PASS;
पूर्ण

SEC("sk_lookup/lookup_drop")
पूर्णांक lookup_drop(काष्ठा bpf_sk_lookup *ctx)
अणु
	वापस SK_DROP;
पूर्ण

SEC("sk_reuseport/reuse_pass")
पूर्णांक reuseport_pass(काष्ठा sk_reuseport_md *ctx)
अणु
	वापस SK_PASS;
पूर्ण

SEC("sk_reuseport/reuse_drop")
पूर्णांक reuseport_drop(काष्ठा sk_reuseport_md *ctx)
अणु
	वापस SK_DROP;
पूर्ण

/* Redirect packets destined क्रम port DST_PORT to socket at redir_map[0]. */
SEC("sk_lookup/redir_port")
पूर्णांक redir_port(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk;
	पूर्णांक err;

	अगर (ctx->local_port != DST_PORT)
		वापस SK_PASS;

	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_A);
	अगर (!sk)
		वापस SK_PASS;

	err = bpf_sk_assign(ctx, sk, 0);
	bpf_sk_release(sk);
	वापस err ? SK_DROP : SK_PASS;
पूर्ण

/* Redirect packets destined क्रम DST_IP4 address to socket at redir_map[0]. */
SEC("sk_lookup/redir_ip4")
पूर्णांक redir_ip4(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk;
	पूर्णांक err;

	अगर (ctx->family != AF_INET)
		वापस SK_PASS;
	अगर (ctx->local_port != DST_PORT)
		वापस SK_PASS;
	अगर (ctx->local_ip4 != DST_IP4)
		वापस SK_PASS;

	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_A);
	अगर (!sk)
		वापस SK_PASS;

	err = bpf_sk_assign(ctx, sk, 0);
	bpf_sk_release(sk);
	वापस err ? SK_DROP : SK_PASS;
पूर्ण

/* Redirect packets destined क्रम DST_IP6 address to socket at redir_map[0]. */
SEC("sk_lookup/redir_ip6")
पूर्णांक redir_ip6(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk;
	पूर्णांक err;

	अगर (ctx->family != AF_INET6)
		वापस SK_PASS;
	अगर (ctx->local_port != DST_PORT)
		वापस SK_PASS;
	अगर (ctx->local_ip6[0] != DST_IP6[0] ||
	    ctx->local_ip6[1] != DST_IP6[1] ||
	    ctx->local_ip6[2] != DST_IP6[2] ||
	    ctx->local_ip6[3] != DST_IP6[3])
		वापस SK_PASS;

	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_A);
	अगर (!sk)
		वापस SK_PASS;

	err = bpf_sk_assign(ctx, sk, 0);
	bpf_sk_release(sk);
	वापस err ? SK_DROP : SK_PASS;
पूर्ण

SEC("sk_lookup/select_sock_a")
पूर्णांक select_sock_a(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk;
	पूर्णांक err;

	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_A);
	अगर (!sk)
		वापस SK_PASS;

	err = bpf_sk_assign(ctx, sk, 0);
	bpf_sk_release(sk);
	वापस err ? SK_DROP : SK_PASS;
पूर्ण

SEC("sk_lookup/select_sock_a_no_reuseport")
पूर्णांक select_sock_a_no_reuseport(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk;
	पूर्णांक err;

	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_A);
	अगर (!sk)
		वापस SK_DROP;

	err = bpf_sk_assign(ctx, sk, BPF_SK_LOOKUP_F_NO_REUSEPORT);
	bpf_sk_release(sk);
	वापस err ? SK_DROP : SK_PASS;
पूर्ण

SEC("sk_reuseport/select_sock_b")
पूर्णांक select_sock_b(काष्ठा sk_reuseport_md *ctx)
अणु
	__u32 key = KEY_SERVER_B;
	पूर्णांक err;

	err = bpf_sk_select_reuseport(ctx, &redir_map, &key, 0);
	वापस err ? SK_DROP : SK_PASS;
पूर्ण

/* Check that bpf_sk_assign() वापसs -EEXIST अगर socket alपढ़ोy selected. */
SEC("sk_lookup/sk_assign_eexist")
पूर्णांक sk_assign_eexist(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk;
	पूर्णांक err, ret;

	ret = SK_DROP;
	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_B);
	अगर (!sk)
		जाओ out;
	err = bpf_sk_assign(ctx, sk, 0);
	अगर (err)
		जाओ out;
	bpf_sk_release(sk);

	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_A);
	अगर (!sk)
		जाओ out;
	err = bpf_sk_assign(ctx, sk, 0);
	अगर (err != -EEXIST) अणु
		bpf_prपूर्णांकk("sk_assign returned %d, expected %d\n",
			   err, -EEXIST);
		जाओ out;
	पूर्ण

	ret = SK_PASS; /* Success, redirect to KEY_SERVER_B */
out:
	अगर (sk)
		bpf_sk_release(sk);
	वापस ret;
पूर्ण

/* Check that bpf_sk_assign(BPF_SK_LOOKUP_F_REPLACE) can override selection. */
SEC("sk_lookup/sk_assign_replace_flag")
पूर्णांक sk_assign_replace_flag(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk;
	पूर्णांक err, ret;

	ret = SK_DROP;
	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_A);
	अगर (!sk)
		जाओ out;
	err = bpf_sk_assign(ctx, sk, 0);
	अगर (err)
		जाओ out;
	bpf_sk_release(sk);

	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_B);
	अगर (!sk)
		जाओ out;
	err = bpf_sk_assign(ctx, sk, BPF_SK_LOOKUP_F_REPLACE);
	अगर (err) अणु
		bpf_prपूर्णांकk("sk_assign returned %d, expected 0\n", err);
		जाओ out;
	पूर्ण

	ret = SK_PASS; /* Success, redirect to KEY_SERVER_B */
out:
	अगर (sk)
		bpf_sk_release(sk);
	वापस ret;
पूर्ण

/* Check that bpf_sk_assign(sk=शून्य) is accepted. */
SEC("sk_lookup/sk_assign_null")
पूर्णांक sk_assign_null(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk = शून्य;
	पूर्णांक err, ret;

	ret = SK_DROP;

	err = bpf_sk_assign(ctx, शून्य, 0);
	अगर (err) अणु
		bpf_prपूर्णांकk("sk_assign returned %d, expected 0\n", err);
		जाओ out;
	पूर्ण

	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_B);
	अगर (!sk)
		जाओ out;
	err = bpf_sk_assign(ctx, sk, BPF_SK_LOOKUP_F_REPLACE);
	अगर (err) अणु
		bpf_prपूर्णांकk("sk_assign returned %d, expected 0\n", err);
		जाओ out;
	पूर्ण

	अगर (ctx->sk != sk)
		जाओ out;
	err = bpf_sk_assign(ctx, शून्य, 0);
	अगर (err != -EEXIST)
		जाओ out;
	err = bpf_sk_assign(ctx, शून्य, BPF_SK_LOOKUP_F_REPLACE);
	अगर (err)
		जाओ out;
	err = bpf_sk_assign(ctx, sk, BPF_SK_LOOKUP_F_REPLACE);
	अगर (err)
		जाओ out;

	ret = SK_PASS; /* Success, redirect to KEY_SERVER_B */
out:
	अगर (sk)
		bpf_sk_release(sk);
	वापस ret;
पूर्ण

/* Check that selected sk is accessible through context. */
SEC("sk_lookup/access_ctx_sk")
पूर्णांक access_ctx_sk(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk1 = शून्य, *sk2 = शून्य;
	पूर्णांक err, ret;

	ret = SK_DROP;

	/* Try accessing unasचिन्हित (शून्य) ctx->sk field */
	अगर (ctx->sk && ctx->sk->family != AF_INET)
		जाओ out;

	/* Assign a value to ctx->sk */
	sk1 = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_A);
	अगर (!sk1)
		जाओ out;
	err = bpf_sk_assign(ctx, sk1, 0);
	अगर (err)
		जाओ out;
	अगर (ctx->sk != sk1)
		जाओ out;

	/* Access ctx->sk fields */
	अगर (ctx->sk->family != AF_INET ||
	    ctx->sk->type != SOCK_STREAM ||
	    ctx->sk->state != BPF_TCP_LISTEN)
		जाओ out;

	/* Reset selection */
	err = bpf_sk_assign(ctx, शून्य, BPF_SK_LOOKUP_F_REPLACE);
	अगर (err)
		जाओ out;
	अगर (ctx->sk)
		जाओ out;

	/* Assign another socket */
	sk2 = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_B);
	अगर (!sk2)
		जाओ out;
	err = bpf_sk_assign(ctx, sk2, BPF_SK_LOOKUP_F_REPLACE);
	अगर (err)
		जाओ out;
	अगर (ctx->sk != sk2)
		जाओ out;

	/* Access reasचिन्हित ctx->sk fields */
	अगर (ctx->sk->family != AF_INET ||
	    ctx->sk->type != SOCK_STREAM ||
	    ctx->sk->state != BPF_TCP_LISTEN)
		जाओ out;

	ret = SK_PASS; /* Success, redirect to KEY_SERVER_B */
out:
	अगर (sk1)
		bpf_sk_release(sk1);
	अगर (sk2)
		bpf_sk_release(sk2);
	वापस ret;
पूर्ण

/* Check narrow loads from ctx fields that support them.
 *
 * Narrow loads of size >= target field size from a non-zero offset
 * are not covered because they give bogus results, that is the
 * verअगरier ignores the offset.
 */
SEC("sk_lookup/ctx_narrow_access")
पूर्णांक ctx_narrow_access(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk;
	पूर्णांक err, family;
	bool v4;

	v4 = (ctx->family == AF_INET);

	/* Narrow loads from family field */
	अगर (LSB(ctx->family, 0) != (v4 ? AF_INET : AF_INET6) ||
	    LSB(ctx->family, 1) != 0 || LSB(ctx->family, 2) != 0 || LSB(ctx->family, 3) != 0)
		वापस SK_DROP;
	अगर (LSW(ctx->family, 0) != (v4 ? AF_INET : AF_INET6))
		वापस SK_DROP;

	/* Narrow loads from protocol field */
	अगर (LSB(ctx->protocol, 0) != IPPROTO_TCP ||
	    LSB(ctx->protocol, 1) != 0 || LSB(ctx->protocol, 2) != 0 || LSB(ctx->protocol, 3) != 0)
		वापस SK_DROP;
	अगर (LSW(ctx->protocol, 0) != IPPROTO_TCP)
		वापस SK_DROP;

	/* Narrow loads from remote_port field. Expect SRC_PORT. */
	अगर (LSB(ctx->remote_port, 0) != ((SRC_PORT >> 0) & 0xff) ||
	    LSB(ctx->remote_port, 1) != ((SRC_PORT >> 8) & 0xff) ||
	    LSB(ctx->remote_port, 2) != 0 || LSB(ctx->remote_port, 3) != 0)
		वापस SK_DROP;
	अगर (LSW(ctx->remote_port, 0) != SRC_PORT)
		वापस SK_DROP;

	/* Narrow loads from local_port field. Expect DST_PORT. */
	अगर (LSB(ctx->local_port, 0) != ((DST_PORT >> 0) & 0xff) ||
	    LSB(ctx->local_port, 1) != ((DST_PORT >> 8) & 0xff) ||
	    LSB(ctx->local_port, 2) != 0 || LSB(ctx->local_port, 3) != 0)
		वापस SK_DROP;
	अगर (LSW(ctx->local_port, 0) != DST_PORT)
		वापस SK_DROP;

	/* Narrow loads from IPv4 fields */
	अगर (v4) अणु
		/* Expect SRC_IP4 in remote_ip4 */
		अगर (LSB(ctx->remote_ip4, 0) != ((SRC_IP4 >> 0) & 0xff) ||
		    LSB(ctx->remote_ip4, 1) != ((SRC_IP4 >> 8) & 0xff) ||
		    LSB(ctx->remote_ip4, 2) != ((SRC_IP4 >> 16) & 0xff) ||
		    LSB(ctx->remote_ip4, 3) != ((SRC_IP4 >> 24) & 0xff))
			वापस SK_DROP;
		अगर (LSW(ctx->remote_ip4, 0) != ((SRC_IP4 >> 0) & 0xffff) ||
		    LSW(ctx->remote_ip4, 1) != ((SRC_IP4 >> 16) & 0xffff))
			वापस SK_DROP;

		/* Expect DST_IP4 in local_ip4 */
		अगर (LSB(ctx->local_ip4, 0) != ((DST_IP4 >> 0) & 0xff) ||
		    LSB(ctx->local_ip4, 1) != ((DST_IP4 >> 8) & 0xff) ||
		    LSB(ctx->local_ip4, 2) != ((DST_IP4 >> 16) & 0xff) ||
		    LSB(ctx->local_ip4, 3) != ((DST_IP4 >> 24) & 0xff))
			वापस SK_DROP;
		अगर (LSW(ctx->local_ip4, 0) != ((DST_IP4 >> 0) & 0xffff) ||
		    LSW(ctx->local_ip4, 1) != ((DST_IP4 >> 16) & 0xffff))
			वापस SK_DROP;
	पूर्ण अन्यथा अणु
		/* Expect 0.0.0.0 IPs when family != AF_INET */
		अगर (LSB(ctx->remote_ip4, 0) != 0 || LSB(ctx->remote_ip4, 1) != 0 ||
		    LSB(ctx->remote_ip4, 2) != 0 || LSB(ctx->remote_ip4, 3) != 0)
			वापस SK_DROP;
		अगर (LSW(ctx->remote_ip4, 0) != 0 || LSW(ctx->remote_ip4, 1) != 0)
			वापस SK_DROP;

		अगर (LSB(ctx->local_ip4, 0) != 0 || LSB(ctx->local_ip4, 1) != 0 ||
		    LSB(ctx->local_ip4, 2) != 0 || LSB(ctx->local_ip4, 3) != 0)
			वापस SK_DROP;
		अगर (LSW(ctx->local_ip4, 0) != 0 || LSW(ctx->local_ip4, 1) != 0)
			वापस SK_DROP;
	पूर्ण

	/* Narrow loads from IPv6 fields */
	अगर (!v4) अणु
		/* Expect SRC_IP6 in remote_ip6 */
		अगर (LSB(ctx->remote_ip6[0], 0) != ((SRC_IP6[0] >> 0) & 0xff) ||
		    LSB(ctx->remote_ip6[0], 1) != ((SRC_IP6[0] >> 8) & 0xff) ||
		    LSB(ctx->remote_ip6[0], 2) != ((SRC_IP6[0] >> 16) & 0xff) ||
		    LSB(ctx->remote_ip6[0], 3) != ((SRC_IP6[0] >> 24) & 0xff) ||
		    LSB(ctx->remote_ip6[1], 0) != ((SRC_IP6[1] >> 0) & 0xff) ||
		    LSB(ctx->remote_ip6[1], 1) != ((SRC_IP6[1] >> 8) & 0xff) ||
		    LSB(ctx->remote_ip6[1], 2) != ((SRC_IP6[1] >> 16) & 0xff) ||
		    LSB(ctx->remote_ip6[1], 3) != ((SRC_IP6[1] >> 24) & 0xff) ||
		    LSB(ctx->remote_ip6[2], 0) != ((SRC_IP6[2] >> 0) & 0xff) ||
		    LSB(ctx->remote_ip6[2], 1) != ((SRC_IP6[2] >> 8) & 0xff) ||
		    LSB(ctx->remote_ip6[2], 2) != ((SRC_IP6[2] >> 16) & 0xff) ||
		    LSB(ctx->remote_ip6[2], 3) != ((SRC_IP6[2] >> 24) & 0xff) ||
		    LSB(ctx->remote_ip6[3], 0) != ((SRC_IP6[3] >> 0) & 0xff) ||
		    LSB(ctx->remote_ip6[3], 1) != ((SRC_IP6[3] >> 8) & 0xff) ||
		    LSB(ctx->remote_ip6[3], 2) != ((SRC_IP6[3] >> 16) & 0xff) ||
		    LSB(ctx->remote_ip6[3], 3) != ((SRC_IP6[3] >> 24) & 0xff))
			वापस SK_DROP;
		अगर (LSW(ctx->remote_ip6[0], 0) != ((SRC_IP6[0] >> 0) & 0xffff) ||
		    LSW(ctx->remote_ip6[0], 1) != ((SRC_IP6[0] >> 16) & 0xffff) ||
		    LSW(ctx->remote_ip6[1], 0) != ((SRC_IP6[1] >> 0) & 0xffff) ||
		    LSW(ctx->remote_ip6[1], 1) != ((SRC_IP6[1] >> 16) & 0xffff) ||
		    LSW(ctx->remote_ip6[2], 0) != ((SRC_IP6[2] >> 0) & 0xffff) ||
		    LSW(ctx->remote_ip6[2], 1) != ((SRC_IP6[2] >> 16) & 0xffff) ||
		    LSW(ctx->remote_ip6[3], 0) != ((SRC_IP6[3] >> 0) & 0xffff) ||
		    LSW(ctx->remote_ip6[3], 1) != ((SRC_IP6[3] >> 16) & 0xffff))
			वापस SK_DROP;
		/* Expect DST_IP6 in local_ip6 */
		अगर (LSB(ctx->local_ip6[0], 0) != ((DST_IP6[0] >> 0) & 0xff) ||
		    LSB(ctx->local_ip6[0], 1) != ((DST_IP6[0] >> 8) & 0xff) ||
		    LSB(ctx->local_ip6[0], 2) != ((DST_IP6[0] >> 16) & 0xff) ||
		    LSB(ctx->local_ip6[0], 3) != ((DST_IP6[0] >> 24) & 0xff) ||
		    LSB(ctx->local_ip6[1], 0) != ((DST_IP6[1] >> 0) & 0xff) ||
		    LSB(ctx->local_ip6[1], 1) != ((DST_IP6[1] >> 8) & 0xff) ||
		    LSB(ctx->local_ip6[1], 2) != ((DST_IP6[1] >> 16) & 0xff) ||
		    LSB(ctx->local_ip6[1], 3) != ((DST_IP6[1] >> 24) & 0xff) ||
		    LSB(ctx->local_ip6[2], 0) != ((DST_IP6[2] >> 0) & 0xff) ||
		    LSB(ctx->local_ip6[2], 1) != ((DST_IP6[2] >> 8) & 0xff) ||
		    LSB(ctx->local_ip6[2], 2) != ((DST_IP6[2] >> 16) & 0xff) ||
		    LSB(ctx->local_ip6[2], 3) != ((DST_IP6[2] >> 24) & 0xff) ||
		    LSB(ctx->local_ip6[3], 0) != ((DST_IP6[3] >> 0) & 0xff) ||
		    LSB(ctx->local_ip6[3], 1) != ((DST_IP6[3] >> 8) & 0xff) ||
		    LSB(ctx->local_ip6[3], 2) != ((DST_IP6[3] >> 16) & 0xff) ||
		    LSB(ctx->local_ip6[3], 3) != ((DST_IP6[3] >> 24) & 0xff))
			वापस SK_DROP;
		अगर (LSW(ctx->local_ip6[0], 0) != ((DST_IP6[0] >> 0) & 0xffff) ||
		    LSW(ctx->local_ip6[0], 1) != ((DST_IP6[0] >> 16) & 0xffff) ||
		    LSW(ctx->local_ip6[1], 0) != ((DST_IP6[1] >> 0) & 0xffff) ||
		    LSW(ctx->local_ip6[1], 1) != ((DST_IP6[1] >> 16) & 0xffff) ||
		    LSW(ctx->local_ip6[2], 0) != ((DST_IP6[2] >> 0) & 0xffff) ||
		    LSW(ctx->local_ip6[2], 1) != ((DST_IP6[2] >> 16) & 0xffff) ||
		    LSW(ctx->local_ip6[3], 0) != ((DST_IP6[3] >> 0) & 0xffff) ||
		    LSW(ctx->local_ip6[3], 1) != ((DST_IP6[3] >> 16) & 0xffff))
			वापस SK_DROP;
	पूर्ण अन्यथा अणु
		/* Expect :: IPs when family != AF_INET6 */
		अगर (LSB(ctx->remote_ip6[0], 0) != 0 || LSB(ctx->remote_ip6[0], 1) != 0 ||
		    LSB(ctx->remote_ip6[0], 2) != 0 || LSB(ctx->remote_ip6[0], 3) != 0 ||
		    LSB(ctx->remote_ip6[1], 0) != 0 || LSB(ctx->remote_ip6[1], 1) != 0 ||
		    LSB(ctx->remote_ip6[1], 2) != 0 || LSB(ctx->remote_ip6[1], 3) != 0 ||
		    LSB(ctx->remote_ip6[2], 0) != 0 || LSB(ctx->remote_ip6[2], 1) != 0 ||
		    LSB(ctx->remote_ip6[2], 2) != 0 || LSB(ctx->remote_ip6[2], 3) != 0 ||
		    LSB(ctx->remote_ip6[3], 0) != 0 || LSB(ctx->remote_ip6[3], 1) != 0 ||
		    LSB(ctx->remote_ip6[3], 2) != 0 || LSB(ctx->remote_ip6[3], 3) != 0)
			वापस SK_DROP;
		अगर (LSW(ctx->remote_ip6[0], 0) != 0 || LSW(ctx->remote_ip6[0], 1) != 0 ||
		    LSW(ctx->remote_ip6[1], 0) != 0 || LSW(ctx->remote_ip6[1], 1) != 0 ||
		    LSW(ctx->remote_ip6[2], 0) != 0 || LSW(ctx->remote_ip6[2], 1) != 0 ||
		    LSW(ctx->remote_ip6[3], 0) != 0 || LSW(ctx->remote_ip6[3], 1) != 0)
			वापस SK_DROP;

		अगर (LSB(ctx->local_ip6[0], 0) != 0 || LSB(ctx->local_ip6[0], 1) != 0 ||
		    LSB(ctx->local_ip6[0], 2) != 0 || LSB(ctx->local_ip6[0], 3) != 0 ||
		    LSB(ctx->local_ip6[1], 0) != 0 || LSB(ctx->local_ip6[1], 1) != 0 ||
		    LSB(ctx->local_ip6[1], 2) != 0 || LSB(ctx->local_ip6[1], 3) != 0 ||
		    LSB(ctx->local_ip6[2], 0) != 0 || LSB(ctx->local_ip6[2], 1) != 0 ||
		    LSB(ctx->local_ip6[2], 2) != 0 || LSB(ctx->local_ip6[2], 3) != 0 ||
		    LSB(ctx->local_ip6[3], 0) != 0 || LSB(ctx->local_ip6[3], 1) != 0 ||
		    LSB(ctx->local_ip6[3], 2) != 0 || LSB(ctx->local_ip6[3], 3) != 0)
			वापस SK_DROP;
		अगर (LSW(ctx->remote_ip6[0], 0) != 0 || LSW(ctx->remote_ip6[0], 1) != 0 ||
		    LSW(ctx->remote_ip6[1], 0) != 0 || LSW(ctx->remote_ip6[1], 1) != 0 ||
		    LSW(ctx->remote_ip6[2], 0) != 0 || LSW(ctx->remote_ip6[2], 1) != 0 ||
		    LSW(ctx->remote_ip6[3], 0) != 0 || LSW(ctx->remote_ip6[3], 1) != 0)
			वापस SK_DROP;
	पूर्ण

	/* Success, redirect to KEY_SERVER_B */
	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_B);
	अगर (sk) अणु
		bpf_sk_assign(ctx, sk, 0);
		bpf_sk_release(sk);
	पूर्ण
	वापस SK_PASS;
पूर्ण

/* Check that sk_assign rejects SERVER_A socket with -ESOCKNOSUPPORT */
SEC("sk_lookup/sk_assign_esocknosupport")
पूर्णांक sk_assign_esocknosupport(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk;
	पूर्णांक err, ret;

	ret = SK_DROP;
	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_A);
	अगर (!sk)
		जाओ out;

	err = bpf_sk_assign(ctx, sk, 0);
	अगर (err != -ESOCKTNOSUPPORT) अणु
		bpf_prपूर्णांकk("sk_assign returned %d, expected %d\n",
			   err, -ESOCKTNOSUPPORT);
		जाओ out;
	पूर्ण

	ret = SK_PASS; /* Success, pass to regular lookup */
out:
	अगर (sk)
		bpf_sk_release(sk);
	वापस ret;
पूर्ण

SEC("sk_lookup/multi_prog_pass1")
पूर्णांक multi_prog_pass1(काष्ठा bpf_sk_lookup *ctx)
अणु
	bpf_map_update_elem(&run_map, &KEY_PROG1, &PROG_DONE, BPF_ANY);
	वापस SK_PASS;
पूर्ण

SEC("sk_lookup/multi_prog_pass2")
पूर्णांक multi_prog_pass2(काष्ठा bpf_sk_lookup *ctx)
अणु
	bpf_map_update_elem(&run_map, &KEY_PROG2, &PROG_DONE, BPF_ANY);
	वापस SK_PASS;
पूर्ण

SEC("sk_lookup/multi_prog_drop1")
पूर्णांक multi_prog_drop1(काष्ठा bpf_sk_lookup *ctx)
अणु
	bpf_map_update_elem(&run_map, &KEY_PROG1, &PROG_DONE, BPF_ANY);
	वापस SK_DROP;
पूर्ण

SEC("sk_lookup/multi_prog_drop2")
पूर्णांक multi_prog_drop2(काष्ठा bpf_sk_lookup *ctx)
अणु
	bpf_map_update_elem(&run_map, &KEY_PROG2, &PROG_DONE, BPF_ANY);
	वापस SK_DROP;
पूर्ण

अटल __always_अंतरभूत पूर्णांक select_server_a(काष्ठा bpf_sk_lookup *ctx)
अणु
	काष्ठा bpf_sock *sk;
	पूर्णांक err;

	sk = bpf_map_lookup_elem(&redir_map, &KEY_SERVER_A);
	अगर (!sk)
		वापस SK_DROP;

	err = bpf_sk_assign(ctx, sk, 0);
	bpf_sk_release(sk);
	अगर (err)
		वापस SK_DROP;

	वापस SK_PASS;
पूर्ण

SEC("sk_lookup/multi_prog_redir1")
पूर्णांक multi_prog_redir1(काष्ठा bpf_sk_lookup *ctx)
अणु
	पूर्णांक ret;

	ret = select_server_a(ctx);
	bpf_map_update_elem(&run_map, &KEY_PROG1, &PROG_DONE, BPF_ANY);
	वापस SK_PASS;
पूर्ण

SEC("sk_lookup/multi_prog_redir2")
पूर्णांक multi_prog_redir2(काष्ठा bpf_sk_lookup *ctx)
अणु
	पूर्णांक ret;

	ret = select_server_a(ctx);
	bpf_map_update_elem(&run_map, &KEY_PROG2, &PROG_DONE, BPF_ANY);
	वापस SK_PASS;
पूर्ण

अक्षर _license[] SEC("license") = "Dual BSD/GPL";
__u32 _version SEC("version") = 1;
