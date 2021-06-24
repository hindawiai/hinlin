<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019 Facebook  */

#समावेश <linux/types.h>
#समावेश <linux/bpf_verअगरier.h>
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/filter.h>
#समावेश <net/tcp.h>
#समावेश <net/bpf_sk_storage.h>

अटल u32 optional_ops[] = अणु
	दुरत्व(काष्ठा tcp_congestion_ops, init),
	दुरत्व(काष्ठा tcp_congestion_ops, release),
	दुरत्व(काष्ठा tcp_congestion_ops, set_state),
	दुरत्व(काष्ठा tcp_congestion_ops, cwnd_event),
	दुरत्व(काष्ठा tcp_congestion_ops, in_ack_event),
	दुरत्व(काष्ठा tcp_congestion_ops, pkts_acked),
	दुरत्व(काष्ठा tcp_congestion_ops, min_tso_segs),
	दुरत्व(काष्ठा tcp_congestion_ops, sndbuf_expand),
	दुरत्व(काष्ठा tcp_congestion_ops, cong_control),
पूर्ण;

अटल u32 unsupported_ops[] = अणु
	दुरत्व(काष्ठा tcp_congestion_ops, get_info),
पूर्ण;

अटल स्थिर काष्ठा btf_type *tcp_sock_type;
अटल u32 tcp_sock_id, sock_id;

अटल पूर्णांक bpf_tcp_ca_init(काष्ठा btf *btf)
अणु
	s32 type_id;

	type_id = btf_find_by_name_kind(btf, "sock", BTF_KIND_STRUCT);
	अगर (type_id < 0)
		वापस -EINVAL;
	sock_id = type_id;

	type_id = btf_find_by_name_kind(btf, "tcp_sock", BTF_KIND_STRUCT);
	अगर (type_id < 0)
		वापस -EINVAL;
	tcp_sock_id = type_id;
	tcp_sock_type = btf_type_by_id(btf, tcp_sock_id);

	वापस 0;
पूर्ण

अटल bool is_optional(u32 member_offset)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(optional_ops); i++) अणु
		अगर (member_offset == optional_ops[i])
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool is_unsupported(u32 member_offset)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(unsupported_ops); i++) अणु
		अगर (member_offset == unsupported_ops[i])
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

बाह्य काष्ठा btf *btf_vmlinux;

अटल bool bpf_tcp_ca_is_valid_access(पूर्णांक off, पूर्णांक size,
				       क्रमागत bpf_access_type type,
				       स्थिर काष्ठा bpf_prog *prog,
				       काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (off < 0 || off >= माप(__u64) * MAX_BPF_FUNC_ARGS)
		वापस false;
	अगर (type != BPF_READ)
		वापस false;
	अगर (off % size != 0)
		वापस false;

	अगर (!btf_ctx_access(off, size, type, prog, info))
		वापस false;

	अगर (info->reg_type == PTR_TO_BTF_ID && info->btf_id == sock_id)
		/* promote it to tcp_sock */
		info->btf_id = tcp_sock_id;

	वापस true;
पूर्ण

अटल पूर्णांक bpf_tcp_ca_btf_काष्ठा_access(काष्ठा bpf_verअगरier_log *log,
					स्थिर काष्ठा btf *btf,
					स्थिर काष्ठा btf_type *t, पूर्णांक off,
					पूर्णांक size, क्रमागत bpf_access_type atype,
					u32 *next_btf_id)
अणु
	माप_प्रकार end;

	अगर (atype == BPF_READ)
		वापस btf_काष्ठा_access(log, btf, t, off, size, atype, next_btf_id);

	अगर (t != tcp_sock_type) अणु
		bpf_log(log, "only read is supported\n");
		वापस -EACCES;
	पूर्ण

	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा inet_connection_sock, icsk_ca_priv):
		end = दुरत्वend(काष्ठा inet_connection_sock, icsk_ca_priv);
		अवरोध;
	हाल दुरत्व(काष्ठा inet_connection_sock, icsk_ack.pending):
		end = दुरत्वend(काष्ठा inet_connection_sock,
				  icsk_ack.pending);
		अवरोध;
	हाल दुरत्व(काष्ठा tcp_sock, snd_cwnd):
		end = दुरत्वend(काष्ठा tcp_sock, snd_cwnd);
		अवरोध;
	हाल दुरत्व(काष्ठा tcp_sock, snd_cwnd_cnt):
		end = दुरत्वend(काष्ठा tcp_sock, snd_cwnd_cnt);
		अवरोध;
	हाल दुरत्व(काष्ठा tcp_sock, snd_ssthresh):
		end = दुरत्वend(काष्ठा tcp_sock, snd_ssthresh);
		अवरोध;
	हाल दुरत्व(काष्ठा tcp_sock, ecn_flags):
		end = दुरत्वend(काष्ठा tcp_sock, ecn_flags);
		अवरोध;
	शेष:
		bpf_log(log, "no write support to tcp_sock at off %d\n", off);
		वापस -EACCES;
	पूर्ण

	अगर (off + size > end) अणु
		bpf_log(log,
			"write access at off %d with size %d beyond the member of tcp_sock ended at %zu\n",
			off, size, end);
		वापस -EACCES;
	पूर्ण

	वापस NOT_INIT;
पूर्ण

BPF_CALL_2(bpf_tcp_send_ack, काष्ठा tcp_sock *, tp, u32, rcv_nxt)
अणु
	/* bpf_tcp_ca prog cannot have शून्य tp */
	__tcp_send_ack((काष्ठा sock *)tp, rcv_nxt);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_tcp_send_ack_proto = अणु
	.func		= bpf_tcp_send_ack,
	.gpl_only	= false,
	/* In हाल we want to report error later */
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &tcp_sock_id,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
bpf_tcp_ca_get_func_proto(क्रमागत bpf_func_id func_id,
			  स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_tcp_send_ack:
		वापस &bpf_tcp_send_ack_proto;
	हाल BPF_FUNC_sk_storage_get:
		वापस &bpf_sk_storage_get_proto;
	हाल BPF_FUNC_sk_storage_delete:
		वापस &bpf_sk_storage_delete_proto;
	शेष:
		वापस bpf_base_func_proto(func_id);
	पूर्ण
पूर्ण

BTF_SET_START(bpf_tcp_ca_kfunc_ids)
BTF_ID(func, tcp_reno_ssthresh)
BTF_ID(func, tcp_reno_cong_aव्योम)
BTF_ID(func, tcp_reno_unकरो_cwnd)
BTF_ID(func, tcp_slow_start)
BTF_ID(func, tcp_cong_aव्योम_ai)
#अगर_घोषित CONFIG_X86
#अगर_घोषित CONFIG_DYNAMIC_FTRACE
#अगर IS_BUILTIN(CONFIG_TCP_CONG_CUBIC)
BTF_ID(func, cubictcp_init)
BTF_ID(func, cubictcp_recalc_ssthresh)
BTF_ID(func, cubictcp_cong_aव्योम)
BTF_ID(func, cubictcp_state)
BTF_ID(func, cubictcp_cwnd_event)
BTF_ID(func, cubictcp_acked)
#पूर्ण_अगर
#अगर IS_BUILTIN(CONFIG_TCP_CONG_DCTCP)
BTF_ID(func, dctcp_init)
BTF_ID(func, dctcp_update_alpha)
BTF_ID(func, dctcp_cwnd_event)
BTF_ID(func, dctcp_ssthresh)
BTF_ID(func, dctcp_cwnd_unकरो)
BTF_ID(func, dctcp_state)
#पूर्ण_अगर
#अगर IS_BUILTIN(CONFIG_TCP_CONG_BBR)
BTF_ID(func, bbr_init)
BTF_ID(func, bbr_मुख्य)
BTF_ID(func, bbr_sndbuf_expand)
BTF_ID(func, bbr_unकरो_cwnd)
BTF_ID(func, bbr_cwnd_event)
BTF_ID(func, bbr_ssthresh)
BTF_ID(func, bbr_min_tso_segs)
BTF_ID(func, bbr_set_state)
#पूर्ण_अगर
#पूर्ण_अगर  /* CONFIG_DYNAMIC_FTRACE */
#पूर्ण_अगर	/* CONFIG_X86 */
BTF_SET_END(bpf_tcp_ca_kfunc_ids)

अटल bool bpf_tcp_ca_check_kfunc_call(u32 kfunc_btf_id)
अणु
	वापस btf_id_set_contains(&bpf_tcp_ca_kfunc_ids, kfunc_btf_id);
पूर्ण

अटल स्थिर काष्ठा bpf_verअगरier_ops bpf_tcp_ca_verअगरier_ops = अणु
	.get_func_proto		= bpf_tcp_ca_get_func_proto,
	.is_valid_access	= bpf_tcp_ca_is_valid_access,
	.btf_काष्ठा_access	= bpf_tcp_ca_btf_काष्ठा_access,
	.check_kfunc_call	= bpf_tcp_ca_check_kfunc_call,
पूर्ण;

अटल पूर्णांक bpf_tcp_ca_init_member(स्थिर काष्ठा btf_type *t,
				  स्थिर काष्ठा btf_member *member,
				  व्योम *kdata, स्थिर व्योम *udata)
अणु
	स्थिर काष्ठा tcp_congestion_ops *utcp_ca;
	काष्ठा tcp_congestion_ops *tcp_ca;
	पूर्णांक prog_fd;
	u32 moff;

	utcp_ca = (स्थिर काष्ठा tcp_congestion_ops *)udata;
	tcp_ca = (काष्ठा tcp_congestion_ops *)kdata;

	moff = btf_member_bit_offset(t, member) / 8;
	चयन (moff) अणु
	हाल दुरत्व(काष्ठा tcp_congestion_ops, flags):
		अगर (utcp_ca->flags & ~TCP_CONG_MASK)
			वापस -EINVAL;
		tcp_ca->flags = utcp_ca->flags;
		वापस 1;
	हाल दुरत्व(काष्ठा tcp_congestion_ops, name):
		अगर (bpf_obj_name_cpy(tcp_ca->name, utcp_ca->name,
				     माप(tcp_ca->name)) <= 0)
			वापस -EINVAL;
		अगर (tcp_ca_find(utcp_ca->name))
			वापस -EEXIST;
		वापस 1;
	पूर्ण

	अगर (!btf_type_resolve_func_ptr(btf_vmlinux, member->type, शून्य))
		वापस 0;

	/* Ensure bpf_prog is provided क्रम compulsory func ptr */
	prog_fd = (पूर्णांक)(*(अचिन्हित दीर्घ *)(udata + moff));
	अगर (!prog_fd && !is_optional(moff) && !is_unsupported(moff))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_tcp_ca_check_member(स्थिर काष्ठा btf_type *t,
				   स्थिर काष्ठा btf_member *member)
अणु
	अगर (is_unsupported(btf_member_bit_offset(t, member) / 8))
		वापस -ENOTSUPP;
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_tcp_ca_reg(व्योम *kdata)
अणु
	वापस tcp_रेजिस्टर_congestion_control(kdata);
पूर्ण

अटल व्योम bpf_tcp_ca_unreg(व्योम *kdata)
अणु
	tcp_unरेजिस्टर_congestion_control(kdata);
पूर्ण

/* Aव्योम sparse warning.  It is only used in bpf_काष्ठा_ops.c. */
बाह्य काष्ठा bpf_काष्ठा_ops bpf_tcp_congestion_ops;

काष्ठा bpf_काष्ठा_ops bpf_tcp_congestion_ops = अणु
	.verअगरier_ops = &bpf_tcp_ca_verअगरier_ops,
	.reg = bpf_tcp_ca_reg,
	.unreg = bpf_tcp_ca_unreg,
	.check_member = bpf_tcp_ca_check_member,
	.init_member = bpf_tcp_ca_init_member,
	.init = bpf_tcp_ca_init,
	.name = "tcp_congestion_ops",
पूर्ण;
