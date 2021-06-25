<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Michael Ellerman, IBM Corporation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/kvm.h>
#समावेश <linux/err.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/xive.h>

#अगर_घोषित CONFIG_KVM_XICS
अटल व्योम kvm_rtas_set_xive(काष्ठा kvm_vcpu *vcpu, काष्ठा rtas_args *args)
अणु
	u32 irq, server, priority;
	पूर्णांक rc;

	अगर (be32_to_cpu(args->nargs) != 3 || be32_to_cpu(args->nret) != 1) अणु
		rc = -3;
		जाओ out;
	पूर्ण

	irq = be32_to_cpu(args->args[0]);
	server = be32_to_cpu(args->args[1]);
	priority = be32_to_cpu(args->args[2]);

	अगर (xics_on_xive())
		rc = kvmppc_xive_set_xive(vcpu->kvm, irq, server, priority);
	अन्यथा
		rc = kvmppc_xics_set_xive(vcpu->kvm, irq, server, priority);
	अगर (rc)
		rc = -3;
out:
	args->rets[0] = cpu_to_be32(rc);
पूर्ण

अटल व्योम kvm_rtas_get_xive(काष्ठा kvm_vcpu *vcpu, काष्ठा rtas_args *args)
अणु
	u32 irq, server, priority;
	पूर्णांक rc;

	अगर (be32_to_cpu(args->nargs) != 1 || be32_to_cpu(args->nret) != 3) अणु
		rc = -3;
		जाओ out;
	पूर्ण

	irq = be32_to_cpu(args->args[0]);

	server = priority = 0;
	अगर (xics_on_xive())
		rc = kvmppc_xive_get_xive(vcpu->kvm, irq, &server, &priority);
	अन्यथा
		rc = kvmppc_xics_get_xive(vcpu->kvm, irq, &server, &priority);
	अगर (rc) अणु
		rc = -3;
		जाओ out;
	पूर्ण

	args->rets[1] = cpu_to_be32(server);
	args->rets[2] = cpu_to_be32(priority);
out:
	args->rets[0] = cpu_to_be32(rc);
पूर्ण

अटल व्योम kvm_rtas_पूर्णांक_off(काष्ठा kvm_vcpu *vcpu, काष्ठा rtas_args *args)
अणु
	u32 irq;
	पूर्णांक rc;

	अगर (be32_to_cpu(args->nargs) != 1 || be32_to_cpu(args->nret) != 1) अणु
		rc = -3;
		जाओ out;
	पूर्ण

	irq = be32_to_cpu(args->args[0]);

	अगर (xics_on_xive())
		rc = kvmppc_xive_पूर्णांक_off(vcpu->kvm, irq);
	अन्यथा
		rc = kvmppc_xics_पूर्णांक_off(vcpu->kvm, irq);
	अगर (rc)
		rc = -3;
out:
	args->rets[0] = cpu_to_be32(rc);
पूर्ण

अटल व्योम kvm_rtas_पूर्णांक_on(काष्ठा kvm_vcpu *vcpu, काष्ठा rtas_args *args)
अणु
	u32 irq;
	पूर्णांक rc;

	अगर (be32_to_cpu(args->nargs) != 1 || be32_to_cpu(args->nret) != 1) अणु
		rc = -3;
		जाओ out;
	पूर्ण

	irq = be32_to_cpu(args->args[0]);

	अगर (xics_on_xive())
		rc = kvmppc_xive_पूर्णांक_on(vcpu->kvm, irq);
	अन्यथा
		rc = kvmppc_xics_पूर्णांक_on(vcpu->kvm, irq);
	अगर (rc)
		rc = -3;
out:
	args->rets[0] = cpu_to_be32(rc);
पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_XICS */

काष्ठा rtas_handler अणु
	व्योम (*handler)(काष्ठा kvm_vcpu *vcpu, काष्ठा rtas_args *args);
	अक्षर *name;
पूर्ण;

अटल काष्ठा rtas_handler rtas_handlers[] = अणु
#अगर_घोषित CONFIG_KVM_XICS
	अणु .name = "ibm,set-xive", .handler = kvm_rtas_set_xive पूर्ण,
	अणु .name = "ibm,get-xive", .handler = kvm_rtas_get_xive पूर्ण,
	अणु .name = "ibm,int-off",  .handler = kvm_rtas_पूर्णांक_off पूर्ण,
	अणु .name = "ibm,int-on",   .handler = kvm_rtas_पूर्णांक_on पूर्ण,
#पूर्ण_अगर
पूर्ण;

काष्ठा rtas_token_definition अणु
	काष्ठा list_head list;
	काष्ठा rtas_handler *handler;
	u64 token;
पूर्ण;

अटल पूर्णांक rtas_name_matches(अक्षर *s1, अक्षर *s2)
अणु
	काष्ठा kvm_rtas_token_args args;
	वापस !म_भेदन(s1, s2, माप(args.name));
पूर्ण

अटल पूर्णांक rtas_token_undefine(काष्ठा kvm *kvm, अक्षर *name)
अणु
	काष्ठा rtas_token_definition *d, *पंचांगp;

	lockdep_निश्चित_held(&kvm->arch.rtas_token_lock);

	list_क्रम_each_entry_safe(d, पंचांगp, &kvm->arch.rtas_tokens, list) अणु
		अगर (rtas_name_matches(d->handler->name, name)) अणु
			list_del(&d->list);
			kमुक्त(d);
			वापस 0;
		पूर्ण
	पूर्ण

	/* It's not an error to undefine an undefined token */
	वापस 0;
पूर्ण

अटल पूर्णांक rtas_token_define(काष्ठा kvm *kvm, अक्षर *name, u64 token)
अणु
	काष्ठा rtas_token_definition *d;
	काष्ठा rtas_handler *h = शून्य;
	bool found;
	पूर्णांक i;

	lockdep_निश्चित_held(&kvm->arch.rtas_token_lock);

	list_क्रम_each_entry(d, &kvm->arch.rtas_tokens, list) अणु
		अगर (d->token == token)
			वापस -EEXIST;
	पूर्ण

	found = false;
	क्रम (i = 0; i < ARRAY_SIZE(rtas_handlers); i++) अणु
		h = &rtas_handlers[i];
		अगर (rtas_name_matches(h->name, name)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस -ENOENT;

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	d->handler = h;
	d->token = token;

	list_add_tail(&d->list, &kvm->arch.rtas_tokens);

	वापस 0;
पूर्ण

पूर्णांक kvm_vm_ioctl_rtas_define_token(काष्ठा kvm *kvm, व्योम __user *argp)
अणु
	काष्ठा kvm_rtas_token_args args;
	पूर्णांक rc;

	अगर (copy_from_user(&args, argp, माप(args)))
		वापस -EFAULT;

	mutex_lock(&kvm->arch.rtas_token_lock);

	अगर (args.token)
		rc = rtas_token_define(kvm, args.name, args.token);
	अन्यथा
		rc = rtas_token_undefine(kvm, args.name);

	mutex_unlock(&kvm->arch.rtas_token_lock);

	वापस rc;
पूर्ण

पूर्णांक kvmppc_rtas_hcall(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा rtas_token_definition *d;
	काष्ठा rtas_args args;
	rtas_arg_t *orig_rets;
	gpa_t args_phys;
	पूर्णांक rc;

	/*
	 * r4 contains the guest physical address of the RTAS args
	 * Mask off the top 4 bits since this is a guest real address
	 */
	args_phys = kvmppc_get_gpr(vcpu, 4) & KVM_PAM;

	vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	rc = kvm_पढ़ो_guest(vcpu->kvm, args_phys, &args, माप(args));
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
	अगर (rc)
		जाओ fail;

	/*
	 * args->rets is a poपूर्णांकer पूर्णांकo args->args. Now that we've
	 * copied args we need to fix it up to poपूर्णांक पूर्णांकo our copy,
	 * not the guest args. We also need to save the original
	 * value so we can restore it on the way out.
	 */
	orig_rets = args.rets;
	args.rets = &args.args[be32_to_cpu(args.nargs)];

	mutex_lock(&vcpu->kvm->arch.rtas_token_lock);

	rc = -ENOENT;
	list_क्रम_each_entry(d, &vcpu->kvm->arch.rtas_tokens, list) अणु
		अगर (d->token == be32_to_cpu(args.token)) अणु
			d->handler->handler(vcpu, &args);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&vcpu->kvm->arch.rtas_token_lock);

	अगर (rc == 0) अणु
		args.rets = orig_rets;
		rc = kvm_ग_लिखो_guest(vcpu->kvm, args_phys, &args, माप(args));
		अगर (rc)
			जाओ fail;
	पूर्ण

	वापस rc;

fail:
	/*
	 * We only get here अगर the guest has called RTAS with a bogus
	 * args poपूर्णांकer. That means we can't get to the args, and so we
	 * can't fail the RTAS call. So fail right out to userspace,
	 * which should समाप्त the guest.
	 */
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_rtas_hcall);

व्योम kvmppc_rtas_tokens_मुक्त(काष्ठा kvm *kvm)
अणु
	काष्ठा rtas_token_definition *d, *पंचांगp;

	list_क्रम_each_entry_safe(d, पंचांगp, &kvm->arch.rtas_tokens, list) अणु
		list_del(&d->list);
		kमुक्त(d);
	पूर्ण
पूर्ण
