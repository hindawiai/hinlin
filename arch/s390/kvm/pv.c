<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hosting Protected Virtual Machines
 *
 * Copyright IBM Corp. 2019, 2020
 *    Author(s): Janosch Frank <frankja@linux.ibm.com>
 */
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <यंत्र/gmap.h>
#समावेश <यंत्र/uv.h>
#समावेश <यंत्र/mman.h>
#समावेश "kvm-s390.h"

पूर्णांक kvm_s390_pv_destroy_cpu(काष्ठा kvm_vcpu *vcpu, u16 *rc, u16 *rrc)
अणु
	पूर्णांक cc = 0;

	अगर (kvm_s390_pv_cpu_get_handle(vcpu)) अणु
		cc = uv_cmd_nodata(kvm_s390_pv_cpu_get_handle(vcpu),
				   UVC_CMD_DESTROY_SEC_CPU, rc, rrc);

		KVM_UV_EVENT(vcpu->kvm, 3,
			     "PROTVIRT DESTROY VCPU %d: rc %x rrc %x",
			     vcpu->vcpu_id, *rc, *rrc);
		WARN_ONCE(cc, "protvirt destroy cpu failed rc %x rrc %x",
			  *rc, *rrc);
	पूर्ण
	/* Intended memory leak क्रम something that should never happen. */
	अगर (!cc)
		मुक्त_pages(vcpu->arch.pv.stor_base,
			   get_order(uv_info.guest_cpu_stor_len));

	मुक्त_page(sida_origin(vcpu->arch.sie_block));
	vcpu->arch.sie_block->pv_handle_cpu = 0;
	vcpu->arch.sie_block->pv_handle_config = 0;
	स_रखो(&vcpu->arch.pv, 0, माप(vcpu->arch.pv));
	vcpu->arch.sie_block->sdf = 0;
	/*
	 * The sidad field (क्रम sdf == 2) is now the gbea field (क्रम sdf == 0).
	 * Use the reset value of gbea to aव्योम leaking the kernel poपूर्णांकer of
	 * the just मुक्तd sida.
	 */
	vcpu->arch.sie_block->gbea = 1;
	kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);

	वापस cc ? EIO : 0;
पूर्ण

पूर्णांक kvm_s390_pv_create_cpu(काष्ठा kvm_vcpu *vcpu, u16 *rc, u16 *rrc)
अणु
	काष्ठा uv_cb_csc uvcb = अणु
		.header.cmd = UVC_CMD_CREATE_SEC_CPU,
		.header.len = माप(uvcb),
	पूर्ण;
	पूर्णांक cc;

	अगर (kvm_s390_pv_cpu_get_handle(vcpu))
		वापस -EINVAL;

	vcpu->arch.pv.stor_base = __get_मुक्त_pages(GFP_KERNEL_ACCOUNT,
						   get_order(uv_info.guest_cpu_stor_len));
	अगर (!vcpu->arch.pv.stor_base)
		वापस -ENOMEM;

	/* Input */
	uvcb.guest_handle = kvm_s390_pv_get_handle(vcpu->kvm);
	uvcb.num = vcpu->arch.sie_block->icpua;
	uvcb.state_origin = (u64)vcpu->arch.sie_block;
	uvcb.stor_origin = (u64)vcpu->arch.pv.stor_base;

	/* Alloc Secure Inकाष्ठाion Data Area Designation */
	vcpu->arch.sie_block->sidad = __get_मुक्त_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO);
	अगर (!vcpu->arch.sie_block->sidad) अणु
		मुक्त_pages(vcpu->arch.pv.stor_base,
			   get_order(uv_info.guest_cpu_stor_len));
		वापस -ENOMEM;
	पूर्ण

	cc = uv_call(0, (u64)&uvcb);
	*rc = uvcb.header.rc;
	*rrc = uvcb.header.rrc;
	KVM_UV_EVENT(vcpu->kvm, 3,
		     "PROTVIRT CREATE VCPU: cpu %d handle %llx rc %x rrc %x",
		     vcpu->vcpu_id, uvcb.cpu_handle, uvcb.header.rc,
		     uvcb.header.rrc);

	अगर (cc) अणु
		u16 dummy;

		kvm_s390_pv_destroy_cpu(vcpu, &dummy, &dummy);
		वापस -EIO;
	पूर्ण

	/* Output */
	vcpu->arch.pv.handle = uvcb.cpu_handle;
	vcpu->arch.sie_block->pv_handle_cpu = uvcb.cpu_handle;
	vcpu->arch.sie_block->pv_handle_config = kvm_s390_pv_get_handle(vcpu->kvm);
	vcpu->arch.sie_block->sdf = 2;
	kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	वापस 0;
पूर्ण

/* only मुक्त resources when the destroy was successful */
अटल व्योम kvm_s390_pv_dealloc_vm(काष्ठा kvm *kvm)
अणु
	vमुक्त(kvm->arch.pv.stor_var);
	मुक्त_pages(kvm->arch.pv.stor_base,
		   get_order(uv_info.guest_base_stor_len));
	स_रखो(&kvm->arch.pv, 0, माप(kvm->arch.pv));
पूर्ण

अटल पूर्णांक kvm_s390_pv_alloc_vm(काष्ठा kvm *kvm)
अणु
	अचिन्हित दीर्घ base = uv_info.guest_base_stor_len;
	अचिन्हित दीर्घ virt = uv_info.guest_virt_var_stor_len;
	अचिन्हित दीर्घ npages = 0, vlen = 0;
	काष्ठा kvm_memory_slot *memslot;

	kvm->arch.pv.stor_var = शून्य;
	kvm->arch.pv.stor_base = __get_मुक्त_pages(GFP_KERNEL_ACCOUNT, get_order(base));
	अगर (!kvm->arch.pv.stor_base)
		वापस -ENOMEM;

	/*
	 * Calculate current guest storage क्रम allocation of the
	 * variable storage, which is based on the length in MB.
	 *
	 * Slots are sorted by GFN
	 */
	mutex_lock(&kvm->slots_lock);
	memslot = kvm_memslots(kvm)->memslots;
	npages = memslot->base_gfn + memslot->npages;
	mutex_unlock(&kvm->slots_lock);

	kvm->arch.pv.guest_len = npages * PAGE_SIZE;

	/* Allocate variable storage */
	vlen = ALIGN(virt * ((npages * PAGE_SIZE) / HPAGE_SIZE), PAGE_SIZE);
	vlen += uv_info.guest_virt_base_stor_len;
	kvm->arch.pv.stor_var = vzalloc(vlen);
	अगर (!kvm->arch.pv.stor_var)
		जाओ out_err;
	वापस 0;

out_err:
	kvm_s390_pv_dealloc_vm(kvm);
	वापस -ENOMEM;
पूर्ण

/* this should not fail, but अगर it करोes, we must not मुक्त the करोnated memory */
पूर्णांक kvm_s390_pv_deinit_vm(काष्ठा kvm *kvm, u16 *rc, u16 *rrc)
अणु
	पूर्णांक cc;

	/* make all pages accessible beक्रमe destroying the guest */
	s390_reset_acc(kvm->mm);

	cc = uv_cmd_nodata(kvm_s390_pv_get_handle(kvm),
			   UVC_CMD_DESTROY_SEC_CONF, rc, rrc);
	WRITE_ONCE(kvm->arch.gmap->guest_handle, 0);
	atomic_set(&kvm->mm->context.is_रक्षित, 0);
	KVM_UV_EVENT(kvm, 3, "PROTVIRT DESTROY VM: rc %x rrc %x", *rc, *rrc);
	WARN_ONCE(cc, "protvirt destroy vm failed rc %x rrc %x", *rc, *rrc);
	/* Inteded memory leak on "impossible" error */
	अगर (!cc)
		kvm_s390_pv_dealloc_vm(kvm);
	वापस cc ? -EIO : 0;
पूर्ण

पूर्णांक kvm_s390_pv_init_vm(काष्ठा kvm *kvm, u16 *rc, u16 *rrc)
अणु
	काष्ठा uv_cb_cgc uvcb = अणु
		.header.cmd = UVC_CMD_CREATE_SEC_CONF,
		.header.len = माप(uvcb)
	पूर्ण;
	पूर्णांक cc, ret;
	u16 dummy;

	ret = kvm_s390_pv_alloc_vm(kvm);
	अगर (ret)
		वापस ret;

	/* Inमाला_दो */
	uvcb.guest_stor_origin = 0; /* MSO is 0 क्रम KVM */
	uvcb.guest_stor_len = kvm->arch.pv.guest_len;
	uvcb.guest_asce = kvm->arch.gmap->asce;
	uvcb.guest_sca = (अचिन्हित दीर्घ)kvm->arch.sca;
	uvcb.conf_base_stor_origin = (u64)kvm->arch.pv.stor_base;
	uvcb.conf_virt_stor_origin = (u64)kvm->arch.pv.stor_var;

	cc = uv_call(0, (u64)&uvcb);
	*rc = uvcb.header.rc;
	*rrc = uvcb.header.rrc;
	KVM_UV_EVENT(kvm, 3, "PROTVIRT CREATE VM: handle %llx len %llx rc %x rrc %x",
		     uvcb.guest_handle, uvcb.guest_stor_len, *rc, *rrc);

	/* Outमाला_दो */
	kvm->arch.pv.handle = uvcb.guest_handle;

	अगर (cc) अणु
		अगर (uvcb.header.rc & UVC_RC_NEED_DESTROY)
			kvm_s390_pv_deinit_vm(kvm, &dummy, &dummy);
		अन्यथा
			kvm_s390_pv_dealloc_vm(kvm);
		वापस -EIO;
	पूर्ण
	kvm->arch.gmap->guest_handle = uvcb.guest_handle;
	वापस 0;
पूर्ण

पूर्णांक kvm_s390_pv_set_sec_parms(काष्ठा kvm *kvm, व्योम *hdr, u64 length, u16 *rc,
			      u16 *rrc)
अणु
	काष्ठा uv_cb_ssc uvcb = अणु
		.header.cmd = UVC_CMD_SET_SEC_CONF_PARAMS,
		.header.len = माप(uvcb),
		.sec_header_origin = (u64)hdr,
		.sec_header_len = length,
		.guest_handle = kvm_s390_pv_get_handle(kvm),
	पूर्ण;
	पूर्णांक cc = uv_call(0, (u64)&uvcb);

	*rc = uvcb.header.rc;
	*rrc = uvcb.header.rrc;
	KVM_UV_EVENT(kvm, 3, "PROTVIRT VM SET PARMS: rc %x rrc %x",
		     *rc, *rrc);
	अगर (!cc)
		atomic_set(&kvm->mm->context.is_रक्षित, 1);
	वापस cc ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक unpack_one(काष्ठा kvm *kvm, अचिन्हित दीर्घ addr, u64 tweak,
		      u64 offset, u16 *rc, u16 *rrc)
अणु
	काष्ठा uv_cb_unp uvcb = अणु
		.header.cmd = UVC_CMD_UNPACK_IMG,
		.header.len = माप(uvcb),
		.guest_handle = kvm_s390_pv_get_handle(kvm),
		.gaddr = addr,
		.tweak[0] = tweak,
		.tweak[1] = offset,
	पूर्ण;
	पूर्णांक ret = gmap_make_secure(kvm->arch.gmap, addr, &uvcb);

	*rc = uvcb.header.rc;
	*rrc = uvcb.header.rrc;

	अगर (ret && ret != -EAGAIN)
		KVM_UV_EVENT(kvm, 3, "PROTVIRT VM UNPACK: failed addr %llx with rc %x rrc %x",
			     uvcb.gaddr, *rc, *rrc);
	वापस ret;
पूर्ण

पूर्णांक kvm_s390_pv_unpack(काष्ठा kvm *kvm, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size,
		       अचिन्हित दीर्घ tweak, u16 *rc, u16 *rrc)
अणु
	u64 offset = 0;
	पूर्णांक ret = 0;

	अगर (addr & ~PAGE_MASK || !size || size & ~PAGE_MASK)
		वापस -EINVAL;

	KVM_UV_EVENT(kvm, 3, "PROTVIRT VM UNPACK: start addr %lx size %lx",
		     addr, size);

	जबतक (offset < size) अणु
		ret = unpack_one(kvm, addr, tweak, offset, rc, rrc);
		अगर (ret == -EAGAIN) अणु
			cond_resched();
			अगर (fatal_संकेत_pending(current))
				अवरोध;
			जारी;
		पूर्ण
		अगर (ret)
			अवरोध;
		addr += PAGE_SIZE;
		offset += PAGE_SIZE;
	पूर्ण
	अगर (!ret)
		KVM_UV_EVENT(kvm, 3, "%s", "PROTVIRT VM UNPACK: successful");
	वापस ret;
पूर्ण

पूर्णांक kvm_s390_pv_set_cpu_state(काष्ठा kvm_vcpu *vcpu, u8 state)
अणु
	काष्ठा uv_cb_cpu_set_state uvcb = अणु
		.header.cmd	= UVC_CMD_CPU_SET_STATE,
		.header.len	= माप(uvcb),
		.cpu_handle	= kvm_s390_pv_cpu_get_handle(vcpu),
		.state		= state,
	पूर्ण;
	पूर्णांक cc;

	cc = uv_call(0, (u64)&uvcb);
	KVM_UV_EVENT(vcpu->kvm, 3, "PROTVIRT SET CPU %d STATE %d rc %x rrc %x",
		     vcpu->vcpu_id, state, uvcb.header.rc, uvcb.header.rrc);
	अगर (cc)
		वापस -EINVAL;
	वापस 0;
पूर्ण
