<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2017 Facebook
 */
#समावेश <linux/bpf.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <net/bpf_sk_storage.h>
#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/error-injection.h>
#समावेश <linux/smp.h>
#समावेश <linux/sock_diag.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/bpf_test_run.h>

काष्ठा bpf_test_समयr अणु
	क्रमागत अणु NO_PREEMPT, NO_MIGRATE पूर्ण mode;
	u32 i;
	u64 समय_start, समय_spent;
पूर्ण;

अटल व्योम bpf_test_समयr_enter(काष्ठा bpf_test_समयr *t)
	__acquires(rcu)
अणु
	rcu_पढ़ो_lock();
	अगर (t->mode == NO_PREEMPT)
		preempt_disable();
	अन्यथा
		migrate_disable();

	t->समय_start = kसमय_get_ns();
पूर्ण

अटल व्योम bpf_test_समयr_leave(काष्ठा bpf_test_समयr *t)
	__releases(rcu)
अणु
	t->समय_start = 0;

	अगर (t->mode == NO_PREEMPT)
		preempt_enable();
	अन्यथा
		migrate_enable();
	rcu_पढ़ो_unlock();
पूर्ण

अटल bool bpf_test_समयr_जारी(काष्ठा bpf_test_समयr *t, u32 repeat, पूर्णांक *err, u32 *duration)
	__must_hold(rcu)
अणु
	t->i++;
	अगर (t->i >= repeat) अणु
		/* We're करोne. */
		t->समय_spent += kसमय_get_ns() - t->समय_start;
		करो_भाग(t->समय_spent, t->i);
		*duration = t->समय_spent > U32_MAX ? U32_MAX : (u32)t->समय_spent;
		*err = 0;
		जाओ reset;
	पूर्ण

	अगर (संकेत_pending(current)) अणु
		/* During iteration: we've been cancelled, पात. */
		*err = -EINTR;
		जाओ reset;
	पूर्ण

	अगर (need_resched()) अणु
		/* During iteration: we need to reschedule between runs. */
		t->समय_spent += kसमय_get_ns() - t->समय_start;
		bpf_test_समयr_leave(t);
		cond_resched();
		bpf_test_समयr_enter(t);
	पूर्ण

	/* Do another round. */
	वापस true;

reset:
	t->i = 0;
	वापस false;
पूर्ण

अटल पूर्णांक bpf_test_run(काष्ठा bpf_prog *prog, व्योम *ctx, u32 repeat,
			u32 *retval, u32 *समय, bool xdp)
अणु
	काष्ठा bpf_cgroup_storage *storage[MAX_BPF_CGROUP_STORAGE_TYPE] = अणु शून्य पूर्ण;
	काष्ठा bpf_test_समयr t = अणु NO_MIGRATE पूर्ण;
	क्रमागत bpf_cgroup_storage_type stype;
	पूर्णांक ret;

	क्रम_each_cgroup_storage_type(stype) अणु
		storage[stype] = bpf_cgroup_storage_alloc(prog, stype);
		अगर (IS_ERR(storage[stype])) अणु
			storage[stype] = शून्य;
			क्रम_each_cgroup_storage_type(stype)
				bpf_cgroup_storage_मुक्त(storage[stype]);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (!repeat)
		repeat = 1;

	bpf_test_समयr_enter(&t);
	करो अणु
		ret = bpf_cgroup_storage_set(storage);
		अगर (ret)
			अवरोध;

		अगर (xdp)
			*retval = bpf_prog_run_xdp(prog, ctx);
		अन्यथा
			*retval = BPF_PROG_RUN(prog, ctx);

		bpf_cgroup_storage_unset();
	पूर्ण जबतक (bpf_test_समयr_जारी(&t, repeat, &ret, समय));
	bpf_test_समयr_leave(&t);

	क्रम_each_cgroup_storage_type(stype)
		bpf_cgroup_storage_मुक्त(storage[stype]);

	वापस ret;
पूर्ण

अटल पूर्णांक bpf_test_finish(स्थिर जोड़ bpf_attr *kattr,
			   जोड़ bpf_attr __user *uattr, स्थिर व्योम *data,
			   u32 size, u32 retval, u32 duration)
अणु
	व्योम __user *data_out = u64_to_user_ptr(kattr->test.data_out);
	पूर्णांक err = -EFAULT;
	u32 copy_size = size;

	/* Clamp copy अगर the user has provided a size hपूर्णांक, but copy the full
	 * buffer अगर not to retain old behaviour.
	 */
	अगर (kattr->test.data_size_out &&
	    copy_size > kattr->test.data_size_out) अणु
		copy_size = kattr->test.data_size_out;
		err = -ENOSPC;
	पूर्ण

	अगर (data_out && copy_to_user(data_out, data, copy_size))
		जाओ out;
	अगर (copy_to_user(&uattr->test.data_size_out, &size, माप(size)))
		जाओ out;
	अगर (copy_to_user(&uattr->test.retval, &retval, माप(retval)))
		जाओ out;
	अगर (copy_to_user(&uattr->test.duration, &duration, माप(duration)))
		जाओ out;
	अगर (err != -ENOSPC)
		err = 0;
out:
	trace_bpf_test_finish(&err);
	वापस err;
पूर्ण

/* Integer types of various sizes and poपूर्णांकer combinations cover variety of
 * architecture dependent calling conventions. 7+ can be supported in the
 * future.
 */
__diag_push();
__diag_ignore(GCC, 8, "-Wmissing-prototypes",
	      "Global functions as their definitions will be in vmlinux BTF");
पूर्णांक noअंतरभूत bpf_fentry_test1(पूर्णांक a)
अणु
	वापस a + 1;
पूर्ण

पूर्णांक noअंतरभूत bpf_fentry_test2(पूर्णांक a, u64 b)
अणु
	वापस a + b;
पूर्ण

पूर्णांक noअंतरभूत bpf_fentry_test3(अक्षर a, पूर्णांक b, u64 c)
अणु
	वापस a + b + c;
पूर्ण

पूर्णांक noअंतरभूत bpf_fentry_test4(व्योम *a, अक्षर b, पूर्णांक c, u64 d)
अणु
	वापस (दीर्घ)a + b + c + d;
पूर्ण

पूर्णांक noअंतरभूत bpf_fentry_test5(u64 a, व्योम *b, लघु c, पूर्णांक d, u64 e)
अणु
	वापस a + (दीर्घ)b + c + d + e;
पूर्ण

पूर्णांक noअंतरभूत bpf_fentry_test6(u64 a, व्योम *b, लघु c, पूर्णांक d, व्योम *e, u64 f)
अणु
	वापस a + (दीर्घ)b + c + d + (दीर्घ)e + f;
पूर्ण

काष्ठा bpf_fentry_test_t अणु
	काष्ठा bpf_fentry_test_t *a;
पूर्ण;

पूर्णांक noअंतरभूत bpf_fentry_test7(काष्ठा bpf_fentry_test_t *arg)
अणु
	वापस (दीर्घ)arg;
पूर्ण

पूर्णांक noअंतरभूत bpf_fentry_test8(काष्ठा bpf_fentry_test_t *arg)
अणु
	वापस (दीर्घ)arg->a;
पूर्ण

पूर्णांक noअंतरभूत bpf_modअगरy_वापस_test(पूर्णांक a, पूर्णांक *b)
अणु
	*b += 1;
	वापस a + *b;
पूर्ण

u64 noअंतरभूत bpf_kfunc_call_test1(काष्ठा sock *sk, u32 a, u64 b, u32 c, u64 d)
अणु
	वापस a + b + c + d;
पूर्ण

पूर्णांक noअंतरभूत bpf_kfunc_call_test2(काष्ठा sock *sk, u32 a, u32 b)
अणु
	वापस a + b;
पूर्ण

काष्ठा sock * noअंतरभूत bpf_kfunc_call_test3(काष्ठा sock *sk)
अणु
	वापस sk;
पूर्ण

__diag_pop();

ALLOW_ERROR_INJECTION(bpf_modअगरy_वापस_test, ERRNO);

BTF_SET_START(test_sk_kfunc_ids)
BTF_ID(func, bpf_kfunc_call_test1)
BTF_ID(func, bpf_kfunc_call_test2)
BTF_ID(func, bpf_kfunc_call_test3)
BTF_SET_END(test_sk_kfunc_ids)

bool bpf_prog_test_check_kfunc_call(u32 kfunc_id)
अणु
	वापस btf_id_set_contains(&test_sk_kfunc_ids, kfunc_id);
पूर्ण

अटल व्योम *bpf_test_init(स्थिर जोड़ bpf_attr *kattr, u32 size,
			   u32 headroom, u32 tailroom)
अणु
	व्योम __user *data_in = u64_to_user_ptr(kattr->test.data_in);
	u32 user_size = kattr->test.data_size_in;
	व्योम *data;

	अगर (size < ETH_HLEN || size > PAGE_SIZE - headroom - tailroom)
		वापस ERR_PTR(-EINVAL);

	अगर (user_size > size)
		वापस ERR_PTR(-EMSGSIZE);

	data = kzalloc(size + headroom + tailroom, GFP_USER);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	अगर (copy_from_user(data + headroom, data_in, user_size)) अणु
		kमुक्त(data);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	वापस data;
पूर्ण

पूर्णांक bpf_prog_test_run_tracing(काष्ठा bpf_prog *prog,
			      स्थिर जोड़ bpf_attr *kattr,
			      जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा bpf_fentry_test_t arg = अणुपूर्ण;
	u16 side_effect = 0, ret = 0;
	पूर्णांक b = 2, err = -EFAULT;
	u32 retval = 0;

	अगर (kattr->test.flags || kattr->test.cpu)
		वापस -EINVAL;

	चयन (prog->expected_attach_type) अणु
	हाल BPF_TRACE_FENTRY:
	हाल BPF_TRACE_FEXIT:
		अगर (bpf_fentry_test1(1) != 2 ||
		    bpf_fentry_test2(2, 3) != 5 ||
		    bpf_fentry_test3(4, 5, 6) != 15 ||
		    bpf_fentry_test4((व्योम *)7, 8, 9, 10) != 34 ||
		    bpf_fentry_test5(11, (व्योम *)12, 13, 14, 15) != 65 ||
		    bpf_fentry_test6(16, (व्योम *)17, 18, 19, (व्योम *)20, 21) != 111 ||
		    bpf_fentry_test7((काष्ठा bpf_fentry_test_t *)0) != 0 ||
		    bpf_fentry_test8(&arg) != 0)
			जाओ out;
		अवरोध;
	हाल BPF_MODIFY_RETURN:
		ret = bpf_modअगरy_वापस_test(1, &b);
		अगर (b != 2)
			side_effect = 1;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	retval = ((u32)side_effect << 16) | ret;
	अगर (copy_to_user(&uattr->test.retval, &retval, माप(retval)))
		जाओ out;

	err = 0;
out:
	trace_bpf_test_finish(&err);
	वापस err;
पूर्ण

काष्ठा bpf_raw_tp_test_run_info अणु
	काष्ठा bpf_prog *prog;
	व्योम *ctx;
	u32 retval;
पूर्ण;

अटल व्योम
__bpf_prog_test_run_raw_tp(व्योम *data)
अणु
	काष्ठा bpf_raw_tp_test_run_info *info = data;

	rcu_पढ़ो_lock();
	info->retval = BPF_PROG_RUN(info->prog, info->ctx);
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक bpf_prog_test_run_raw_tp(काष्ठा bpf_prog *prog,
			     स्थिर जोड़ bpf_attr *kattr,
			     जोड़ bpf_attr __user *uattr)
अणु
	व्योम __user *ctx_in = u64_to_user_ptr(kattr->test.ctx_in);
	__u32 ctx_size_in = kattr->test.ctx_size_in;
	काष्ठा bpf_raw_tp_test_run_info info;
	पूर्णांक cpu = kattr->test.cpu, err = 0;
	पूर्णांक current_cpu;

	/* करोesn't support data_in/out, ctx_out, duration, or repeat */
	अगर (kattr->test.data_in || kattr->test.data_out ||
	    kattr->test.ctx_out || kattr->test.duration ||
	    kattr->test.repeat)
		वापस -EINVAL;

	अगर (ctx_size_in < prog->aux->max_ctx_offset ||
	    ctx_size_in > MAX_BPF_FUNC_ARGS * माप(u64))
		वापस -EINVAL;

	अगर ((kattr->test.flags & BPF_F_TEST_RUN_ON_CPU) == 0 && cpu != 0)
		वापस -EINVAL;

	अगर (ctx_size_in) अणु
		info.ctx = kzalloc(ctx_size_in, GFP_USER);
		अगर (!info.ctx)
			वापस -ENOMEM;
		अगर (copy_from_user(info.ctx, ctx_in, ctx_size_in)) अणु
			err = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		info.ctx = शून्य;
	पूर्ण

	info.prog = prog;

	current_cpu = get_cpu();
	अगर ((kattr->test.flags & BPF_F_TEST_RUN_ON_CPU) == 0 ||
	    cpu == current_cpu) अणु
		__bpf_prog_test_run_raw_tp(&info);
	पूर्ण अन्यथा अगर (cpu >= nr_cpu_ids || !cpu_online(cpu)) अणु
		/* smp_call_function_single() also checks cpu_online()
		 * after csd_lock(). However, since cpu is from user
		 * space, let's करो an extra quick check to filter out
		 * invalid value beक्रमe smp_call_function_single().
		 */
		err = -ENXIO;
	पूर्ण अन्यथा अणु
		err = smp_call_function_single(cpu, __bpf_prog_test_run_raw_tp,
					       &info, 1);
	पूर्ण
	put_cpu();

	अगर (!err &&
	    copy_to_user(&uattr->test.retval, &info.retval, माप(u32)))
		err = -EFAULT;

out:
	kमुक्त(info.ctx);
	वापस err;
पूर्ण

अटल व्योम *bpf_ctx_init(स्थिर जोड़ bpf_attr *kattr, u32 max_size)
अणु
	व्योम __user *data_in = u64_to_user_ptr(kattr->test.ctx_in);
	व्योम __user *data_out = u64_to_user_ptr(kattr->test.ctx_out);
	u32 size = kattr->test.ctx_size_in;
	व्योम *data;
	पूर्णांक err;

	अगर (!data_in && !data_out)
		वापस शून्य;

	data = kzalloc(max_size, GFP_USER);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	अगर (data_in) अणु
		err = bpf_check_uarg_tail_zero(data_in, max_size, size);
		अगर (err) अणु
			kमुक्त(data);
			वापस ERR_PTR(err);
		पूर्ण

		size = min_t(u32, max_size, size);
		अगर (copy_from_user(data, data_in, size)) अणु
			kमुक्त(data);
			वापस ERR_PTR(-EFAULT);
		पूर्ण
	पूर्ण
	वापस data;
पूर्ण

अटल पूर्णांक bpf_ctx_finish(स्थिर जोड़ bpf_attr *kattr,
			  जोड़ bpf_attr __user *uattr, स्थिर व्योम *data,
			  u32 size)
अणु
	व्योम __user *data_out = u64_to_user_ptr(kattr->test.ctx_out);
	पूर्णांक err = -EFAULT;
	u32 copy_size = size;

	अगर (!data || !data_out)
		वापस 0;

	अगर (copy_size > kattr->test.ctx_size_out) अणु
		copy_size = kattr->test.ctx_size_out;
		err = -ENOSPC;
	पूर्ण

	अगर (copy_to_user(data_out, data, copy_size))
		जाओ out;
	अगर (copy_to_user(&uattr->test.ctx_size_out, &size, माप(size)))
		जाओ out;
	अगर (err != -ENOSPC)
		err = 0;
out:
	वापस err;
पूर्ण

/**
 * range_is_zero - test whether buffer is initialized
 * @buf: buffer to check
 * @from: check from this position
 * @to: check up until (excluding) this position
 *
 * This function वापसs true अगर the there is a non-zero byte
 * in the buf in the range [from,to).
 */
अटल अंतरभूत bool range_is_zero(व्योम *buf, माप_प्रकार from, माप_प्रकार to)
अणु
	वापस !स_प्रथम_inv((u8 *)buf + from, 0, to - from);
पूर्ण

अटल पूर्णांक convert___skb_to_skb(काष्ठा sk_buff *skb, काष्ठा __sk_buff *__skb)
अणु
	काष्ठा qdisc_skb_cb *cb = (काष्ठा qdisc_skb_cb *)skb->cb;

	अगर (!__skb)
		वापस 0;

	/* make sure the fields we करोn't use are zeroed */
	अगर (!range_is_zero(__skb, 0, दुरत्व(काष्ठा __sk_buff, mark)))
		वापस -EINVAL;

	/* mark is allowed */

	अगर (!range_is_zero(__skb, दुरत्वend(काष्ठा __sk_buff, mark),
			   दुरत्व(काष्ठा __sk_buff, priority)))
		वापस -EINVAL;

	/* priority is allowed */

	अगर (!range_is_zero(__skb, दुरत्वend(काष्ठा __sk_buff, priority),
			   दुरत्व(काष्ठा __sk_buff, अगरindex)))
		वापस -EINVAL;

	/* अगरindex is allowed */

	अगर (!range_is_zero(__skb, दुरत्वend(काष्ठा __sk_buff, अगरindex),
			   दुरत्व(काष्ठा __sk_buff, cb)))
		वापस -EINVAL;

	/* cb is allowed */

	अगर (!range_is_zero(__skb, दुरत्वend(काष्ठा __sk_buff, cb),
			   दुरत्व(काष्ठा __sk_buff, tstamp)))
		वापस -EINVAL;

	/* tstamp is allowed */
	/* wire_len is allowed */
	/* gso_segs is allowed */

	अगर (!range_is_zero(__skb, दुरत्वend(काष्ठा __sk_buff, gso_segs),
			   दुरत्व(काष्ठा __sk_buff, gso_size)))
		वापस -EINVAL;

	/* gso_size is allowed */

	अगर (!range_is_zero(__skb, दुरत्वend(काष्ठा __sk_buff, gso_size),
			   माप(काष्ठा __sk_buff)))
		वापस -EINVAL;

	skb->mark = __skb->mark;
	skb->priority = __skb->priority;
	skb->tstamp = __skb->tstamp;
	स_नकल(&cb->data, __skb->cb, QDISC_CB_PRIV_LEN);

	अगर (__skb->wire_len == 0) अणु
		cb->pkt_len = skb->len;
	पूर्ण अन्यथा अणु
		अगर (__skb->wire_len < skb->len ||
		    __skb->wire_len > GSO_MAX_SIZE)
			वापस -EINVAL;
		cb->pkt_len = __skb->wire_len;
	पूर्ण

	अगर (__skb->gso_segs > GSO_MAX_SEGS)
		वापस -EINVAL;
	skb_shinfo(skb)->gso_segs = __skb->gso_segs;
	skb_shinfo(skb)->gso_size = __skb->gso_size;

	वापस 0;
पूर्ण

अटल व्योम convert_skb_to___skb(काष्ठा sk_buff *skb, काष्ठा __sk_buff *__skb)
अणु
	काष्ठा qdisc_skb_cb *cb = (काष्ठा qdisc_skb_cb *)skb->cb;

	अगर (!__skb)
		वापस;

	__skb->mark = skb->mark;
	__skb->priority = skb->priority;
	__skb->अगरindex = skb->dev->अगरindex;
	__skb->tstamp = skb->tstamp;
	स_नकल(__skb->cb, &cb->data, QDISC_CB_PRIV_LEN);
	__skb->wire_len = cb->pkt_len;
	__skb->gso_segs = skb_shinfo(skb)->gso_segs;
पूर्ण

पूर्णांक bpf_prog_test_run_skb(काष्ठा bpf_prog *prog, स्थिर जोड़ bpf_attr *kattr,
			  जोड़ bpf_attr __user *uattr)
अणु
	bool is_l2 = false, is_direct_pkt_access = false;
	काष्ठा net *net = current->nsproxy->net_ns;
	काष्ठा net_device *dev = net->loopback_dev;
	u32 size = kattr->test.data_size_in;
	u32 repeat = kattr->test.repeat;
	काष्ठा __sk_buff *ctx = शून्य;
	u32 retval, duration;
	पूर्णांक hh_len = ETH_HLEN;
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk;
	व्योम *data;
	पूर्णांक ret;

	अगर (kattr->test.flags || kattr->test.cpu)
		वापस -EINVAL;

	data = bpf_test_init(kattr, size, NET_SKB_PAD + NET_IP_ALIGN,
			     SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)));
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	ctx = bpf_ctx_init(kattr, माप(काष्ठा __sk_buff));
	अगर (IS_ERR(ctx)) अणु
		kमुक्त(data);
		वापस PTR_ERR(ctx);
	पूर्ण

	चयन (prog->type) अणु
	हाल BPF_PROG_TYPE_SCHED_CLS:
	हाल BPF_PROG_TYPE_SCHED_ACT:
		is_l2 = true;
		fallthrough;
	हाल BPF_PROG_TYPE_LWT_IN:
	हाल BPF_PROG_TYPE_LWT_OUT:
	हाल BPF_PROG_TYPE_LWT_XMIT:
		is_direct_pkt_access = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	sk = kzalloc(माप(काष्ठा sock), GFP_USER);
	अगर (!sk) अणु
		kमुक्त(data);
		kमुक्त(ctx);
		वापस -ENOMEM;
	पूर्ण
	sock_net_set(sk, net);
	sock_init_data(शून्य, sk);

	skb = build_skb(data, 0);
	अगर (!skb) अणु
		kमुक्त(data);
		kमुक्त(ctx);
		kमुक्त(sk);
		वापस -ENOMEM;
	पूर्ण
	skb->sk = sk;

	skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN);
	__skb_put(skb, size);
	अगर (ctx && ctx->अगरindex > 1) अणु
		dev = dev_get_by_index(net, ctx->अगरindex);
		अगर (!dev) अणु
			ret = -ENODEV;
			जाओ out;
		पूर्ण
	पूर्ण
	skb->protocol = eth_type_trans(skb, dev);
	skb_reset_network_header(skb);

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		sk->sk_family = AF_INET;
		अगर (माप(काष्ठा iphdr) <= skb_headlen(skb)) अणु
			sk->sk_rcv_saddr = ip_hdr(skb)->saddr;
			sk->sk_daddr = ip_hdr(skb)->daddr;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल htons(ETH_P_IPV6):
		sk->sk_family = AF_INET6;
		अगर (माप(काष्ठा ipv6hdr) <= skb_headlen(skb)) अणु
			sk->sk_v6_rcv_saddr = ipv6_hdr(skb)->saddr;
			sk->sk_v6_daddr = ipv6_hdr(skb)->daddr;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		अवरोध;
	पूर्ण

	अगर (is_l2)
		__skb_push(skb, hh_len);
	अगर (is_direct_pkt_access)
		bpf_compute_data_poपूर्णांकers(skb);
	ret = convert___skb_to_skb(skb, ctx);
	अगर (ret)
		जाओ out;
	ret = bpf_test_run(prog, skb, repeat, &retval, &duration, false);
	अगर (ret)
		जाओ out;
	अगर (!is_l2) अणु
		अगर (skb_headroom(skb) < hh_len) अणु
			पूर्णांक nhead = HH_DATA_ALIGN(hh_len - skb_headroom(skb));

			अगर (pskb_expand_head(skb, nhead, 0, GFP_USER)) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण
		स_रखो(__skb_push(skb, hh_len), 0, hh_len);
	पूर्ण
	convert_skb_to___skb(skb, ctx);

	size = skb->len;
	/* bpf program can never convert linear skb to non-linear */
	अगर (WARN_ON_ONCE(skb_is_nonlinear(skb)))
		size = skb_headlen(skb);
	ret = bpf_test_finish(kattr, uattr, skb->data, size, retval, duration);
	अगर (!ret)
		ret = bpf_ctx_finish(kattr, uattr, ctx,
				     माप(काष्ठा __sk_buff));
out:
	अगर (dev && dev != net->loopback_dev)
		dev_put(dev);
	kमुक्त_skb(skb);
	bpf_sk_storage_मुक्त(sk);
	kमुक्त(sk);
	kमुक्त(ctx);
	वापस ret;
पूर्ण

पूर्णांक bpf_prog_test_run_xdp(काष्ठा bpf_prog *prog, स्थिर जोड़ bpf_attr *kattr,
			  जोड़ bpf_attr __user *uattr)
अणु
	u32 tailroom = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	u32 headroom = XDP_PACKET_HEADROOM;
	u32 size = kattr->test.data_size_in;
	u32 repeat = kattr->test.repeat;
	काष्ठा netdev_rx_queue *rxqueue;
	काष्ठा xdp_buff xdp = अणुपूर्ण;
	u32 retval, duration;
	u32 max_data_sz;
	व्योम *data;
	पूर्णांक ret;

	अगर (kattr->test.ctx_in || kattr->test.ctx_out)
		वापस -EINVAL;

	/* XDP have extra tailroom as (most) drivers use full page */
	max_data_sz = 4096 - headroom - tailroom;

	data = bpf_test_init(kattr, max_data_sz, headroom, tailroom);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	rxqueue = __netअगर_get_rx_queue(current->nsproxy->net_ns->loopback_dev, 0);
	xdp_init_buff(&xdp, headroom + max_data_sz + tailroom,
		      &rxqueue->xdp_rxq);
	xdp_prepare_buff(&xdp, data, headroom, size, true);

	bpf_prog_change_xdp(शून्य, prog);
	ret = bpf_test_run(prog, &xdp, repeat, &retval, &duration, true);
	अगर (ret)
		जाओ out;
	अगर (xdp.data != data + headroom || xdp.data_end != xdp.data + size)
		size = xdp.data_end - xdp.data;
	ret = bpf_test_finish(kattr, uattr, xdp.data, size, retval, duration);
out:
	bpf_prog_change_xdp(prog, शून्य);
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल पूर्णांक verअगरy_user_bpf_flow_keys(काष्ठा bpf_flow_keys *ctx)
अणु
	/* make sure the fields we करोn't use are zeroed */
	अगर (!range_is_zero(ctx, 0, दुरत्व(काष्ठा bpf_flow_keys, flags)))
		वापस -EINVAL;

	/* flags is allowed */

	अगर (!range_is_zero(ctx, दुरत्वend(काष्ठा bpf_flow_keys, flags),
			   माप(काष्ठा bpf_flow_keys)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक bpf_prog_test_run_flow_dissector(काष्ठा bpf_prog *prog,
				     स्थिर जोड़ bpf_attr *kattr,
				     जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा bpf_test_समयr t = अणु NO_PREEMPT पूर्ण;
	u32 size = kattr->test.data_size_in;
	काष्ठा bpf_flow_dissector ctx = अणुपूर्ण;
	u32 repeat = kattr->test.repeat;
	काष्ठा bpf_flow_keys *user_ctx;
	काष्ठा bpf_flow_keys flow_keys;
	स्थिर काष्ठा ethhdr *eth;
	अचिन्हित पूर्णांक flags = 0;
	u32 retval, duration;
	व्योम *data;
	पूर्णांक ret;

	अगर (prog->type != BPF_PROG_TYPE_FLOW_DISSECTOR)
		वापस -EINVAL;

	अगर (kattr->test.flags || kattr->test.cpu)
		वापस -EINVAL;

	अगर (size < ETH_HLEN)
		वापस -EINVAL;

	data = bpf_test_init(kattr, size, 0, 0);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	eth = (काष्ठा ethhdr *)data;

	अगर (!repeat)
		repeat = 1;

	user_ctx = bpf_ctx_init(kattr, माप(काष्ठा bpf_flow_keys));
	अगर (IS_ERR(user_ctx)) अणु
		kमुक्त(data);
		वापस PTR_ERR(user_ctx);
	पूर्ण
	अगर (user_ctx) अणु
		ret = verअगरy_user_bpf_flow_keys(user_ctx);
		अगर (ret)
			जाओ out;
		flags = user_ctx->flags;
	पूर्ण

	ctx.flow_keys = &flow_keys;
	ctx.data = data;
	ctx.data_end = (__u8 *)data + size;

	bpf_test_समयr_enter(&t);
	करो अणु
		retval = bpf_flow_dissect(prog, &ctx, eth->h_proto, ETH_HLEN,
					  size, flags);
	पूर्ण जबतक (bpf_test_समयr_जारी(&t, repeat, &ret, &duration));
	bpf_test_समयr_leave(&t);

	अगर (ret < 0)
		जाओ out;

	ret = bpf_test_finish(kattr, uattr, &flow_keys, माप(flow_keys),
			      retval, duration);
	अगर (!ret)
		ret = bpf_ctx_finish(kattr, uattr, user_ctx,
				     माप(काष्ठा bpf_flow_keys));

out:
	kमुक्त(user_ctx);
	kमुक्त(data);
	वापस ret;
पूर्ण

पूर्णांक bpf_prog_test_run_sk_lookup(काष्ठा bpf_prog *prog, स्थिर जोड़ bpf_attr *kattr,
				जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा bpf_test_समयr t = अणु NO_PREEMPT पूर्ण;
	काष्ठा bpf_prog_array *progs = शून्य;
	काष्ठा bpf_sk_lookup_kern ctx = अणुपूर्ण;
	u32 repeat = kattr->test.repeat;
	काष्ठा bpf_sk_lookup *user_ctx;
	u32 retval, duration;
	पूर्णांक ret = -EINVAL;

	अगर (prog->type != BPF_PROG_TYPE_SK_LOOKUP)
		वापस -EINVAL;

	अगर (kattr->test.flags || kattr->test.cpu)
		वापस -EINVAL;

	अगर (kattr->test.data_in || kattr->test.data_size_in || kattr->test.data_out ||
	    kattr->test.data_size_out)
		वापस -EINVAL;

	अगर (!repeat)
		repeat = 1;

	user_ctx = bpf_ctx_init(kattr, माप(*user_ctx));
	अगर (IS_ERR(user_ctx))
		वापस PTR_ERR(user_ctx);

	अगर (!user_ctx)
		वापस -EINVAL;

	अगर (user_ctx->sk)
		जाओ out;

	अगर (!range_is_zero(user_ctx, दुरत्वend(typeof(*user_ctx), local_port), माप(*user_ctx)))
		जाओ out;

	अगर (user_ctx->local_port > U16_MAX || user_ctx->remote_port > U16_MAX) अणु
		ret = -दुस्फल;
		जाओ out;
	पूर्ण

	ctx.family = (u16)user_ctx->family;
	ctx.protocol = (u16)user_ctx->protocol;
	ctx.dport = (u16)user_ctx->local_port;
	ctx.sport = (__क्रमce __be16)user_ctx->remote_port;

	चयन (ctx.family) अणु
	हाल AF_INET:
		ctx.v4.daddr = (__क्रमce __be32)user_ctx->local_ip4;
		ctx.v4.saddr = (__क्रमce __be32)user_ctx->remote_ip4;
		अवरोध;

#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		ctx.v6.daddr = (काष्ठा in6_addr *)user_ctx->local_ip6;
		ctx.v6.saddr = (काष्ठा in6_addr *)user_ctx->remote_ip6;
		अवरोध;
#पूर्ण_अगर

	शेष:
		ret = -EAFNOSUPPORT;
		जाओ out;
	पूर्ण

	progs = bpf_prog_array_alloc(1, GFP_KERNEL);
	अगर (!progs) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	progs->items[0].prog = prog;

	bpf_test_समयr_enter(&t);
	करो अणु
		ctx.selected_sk = शून्य;
		retval = BPF_PROG_SK_LOOKUP_RUN_ARRAY(progs, ctx, BPF_PROG_RUN);
	पूर्ण जबतक (bpf_test_समयr_जारी(&t, repeat, &ret, &duration));
	bpf_test_समयr_leave(&t);

	अगर (ret < 0)
		जाओ out;

	user_ctx->cookie = 0;
	अगर (ctx.selected_sk) अणु
		अगर (ctx.selected_sk->sk_reuseport && !ctx.no_reuseport) अणु
			ret = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		user_ctx->cookie = sock_gen_cookie(ctx.selected_sk);
	पूर्ण

	ret = bpf_test_finish(kattr, uattr, शून्य, 0, retval, duration);
	अगर (!ret)
		ret = bpf_ctx_finish(kattr, uattr, user_ctx, माप(*user_ctx));

out:
	bpf_prog_array_मुक्त(progs);
	kमुक्त(user_ctx);
	वापस ret;
पूर्ण
