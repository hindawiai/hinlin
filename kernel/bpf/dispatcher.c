<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright(c) 2019 Intel Corporation. */

#समावेश <linux/hash.h>
#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>

/* The BPF dispatcher is a multiway branch code generator. The
 * dispatcher is a mechanism to aव्योम the perक्रमmance penalty of an
 * indirect call, which is expensive when retpolines are enabled. A
 * dispatch client रेजिस्टरs a BPF program पूर्णांकo the dispatcher, and अगर
 * there is available room in the dispatcher a direct call to the BPF
 * program will be generated. All calls to the BPF programs called via
 * the dispatcher will then be a direct call, instead of an
 * indirect. The dispatcher hijacks a trampoline function it via the
 * __fentry__ of the trampoline. The trampoline function has the
 * following signature:
 *
 * अचिन्हित पूर्णांक trampoline(स्थिर व्योम *ctx, स्थिर काष्ठा bpf_insn *insnsi,
 *                         अचिन्हित पूर्णांक (*bpf_func)(स्थिर व्योम *,
 *                                                  स्थिर काष्ठा bpf_insn *));
 */

अटल काष्ठा bpf_dispatcher_prog *bpf_dispatcher_find_prog(
	काष्ठा bpf_dispatcher *d, काष्ठा bpf_prog *prog)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BPF_DISPATCHER_MAX; i++) अणु
		अगर (prog == d->progs[i].prog)
			वापस &d->progs[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा bpf_dispatcher_prog *bpf_dispatcher_find_मुक्त(
	काष्ठा bpf_dispatcher *d)
अणु
	वापस bpf_dispatcher_find_prog(d, शून्य);
पूर्ण

अटल bool bpf_dispatcher_add_prog(काष्ठा bpf_dispatcher *d,
				    काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_dispatcher_prog *entry;

	अगर (!prog)
		वापस false;

	entry = bpf_dispatcher_find_prog(d, prog);
	अगर (entry) अणु
		refcount_inc(&entry->users);
		वापस false;
	पूर्ण

	entry = bpf_dispatcher_find_मुक्त(d);
	अगर (!entry)
		वापस false;

	bpf_prog_inc(prog);
	entry->prog = prog;
	refcount_set(&entry->users, 1);
	d->num_progs++;
	वापस true;
पूर्ण

अटल bool bpf_dispatcher_हटाओ_prog(काष्ठा bpf_dispatcher *d,
				       काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_dispatcher_prog *entry;

	अगर (!prog)
		वापस false;

	entry = bpf_dispatcher_find_prog(d, prog);
	अगर (!entry)
		वापस false;

	अगर (refcount_dec_and_test(&entry->users)) अणु
		entry->prog = शून्य;
		bpf_prog_put(prog);
		d->num_progs--;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक __weak arch_prepare_bpf_dispatcher(व्योम *image, s64 *funcs, पूर्णांक num_funcs)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक bpf_dispatcher_prepare(काष्ठा bpf_dispatcher *d, व्योम *image)
अणु
	s64 ips[BPF_DISPATCHER_MAX] = अणुपूर्ण, *ipsp = &ips[0];
	पूर्णांक i;

	क्रम (i = 0; i < BPF_DISPATCHER_MAX; i++) अणु
		अगर (d->progs[i].prog)
			*ipsp++ = (s64)(uपूर्णांकptr_t)d->progs[i].prog->bpf_func;
	पूर्ण
	वापस arch_prepare_bpf_dispatcher(image, &ips[0], d->num_progs);
पूर्ण

अटल व्योम bpf_dispatcher_update(काष्ठा bpf_dispatcher *d, पूर्णांक prev_num_progs)
अणु
	व्योम *old, *new;
	u32 noff;
	पूर्णांक err;

	अगर (!prev_num_progs) अणु
		old = शून्य;
		noff = 0;
	पूर्ण अन्यथा अणु
		old = d->image + d->image_off;
		noff = d->image_off ^ (PAGE_SIZE / 2);
	पूर्ण

	new = d->num_progs ? d->image + noff : शून्य;
	अगर (new) अणु
		अगर (bpf_dispatcher_prepare(d, new))
			वापस;
	पूर्ण

	err = bpf_arch_text_poke(d->func, BPF_MOD_JUMP, old, new);
	अगर (err || !new)
		वापस;

	d->image_off = noff;
पूर्ण

व्योम bpf_dispatcher_change_prog(काष्ठा bpf_dispatcher *d, काष्ठा bpf_prog *from,
				काष्ठा bpf_prog *to)
अणु
	bool changed = false;
	पूर्णांक prev_num_progs;

	अगर (from == to)
		वापस;

	mutex_lock(&d->mutex);
	अगर (!d->image) अणु
		d->image = bpf_jit_alloc_exec_page();
		अगर (!d->image)
			जाओ out;
		bpf_image_ksym_add(d->image, &d->ksym);
	पूर्ण

	prev_num_progs = d->num_progs;
	changed |= bpf_dispatcher_हटाओ_prog(d, from);
	changed |= bpf_dispatcher_add_prog(d, to);

	अगर (!changed)
		जाओ out;

	bpf_dispatcher_update(d, prev_num_progs);
out:
	mutex_unlock(&d->mutex);
पूर्ण
