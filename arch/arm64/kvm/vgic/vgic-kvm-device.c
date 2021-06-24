<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VGIC: KVM DEVICE API
 *
 * Copyright (C) 2015 ARM Ltd.
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */
#समावेश <linux/kvm_host.h>
#समावेश <kvm/arm_vgic.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/cputype.h>
#समावेश "vgic.h"

/* common helpers */

पूर्णांक vgic_check_ioaddr(काष्ठा kvm *kvm, phys_addr_t *ioaddr,
		      phys_addr_t addr, phys_addr_t alignment)
अणु
	अगर (addr & ~kvm_phys_mask(kvm))
		वापस -E2BIG;

	अगर (!IS_ALIGNED(addr, alignment))
		वापस -EINVAL;

	अगर (!IS_VGIC_ADDR_UNDEF(*ioaddr))
		वापस -EEXIST;

	वापस 0;
पूर्ण

अटल पूर्णांक vgic_check_type(काष्ठा kvm *kvm, पूर्णांक type_needed)
अणु
	अगर (kvm->arch.vgic.vgic_model != type_needed)
		वापस -ENODEV;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * kvm_vgic_addr - set or get vgic VM base addresses
 * @kvm:   poपूर्णांकer to the vm काष्ठा
 * @type:  the VGIC addr type, one of KVM_VGIC_V[23]_ADDR_TYPE_XXX
 * @addr:  poपूर्णांकer to address value
 * @ग_लिखो: अगर true set the address in the VM address space, अगर false पढ़ो the
 *          address
 *
 * Set or get the vgic base addresses क्रम the distributor and the भव CPU
 * पूर्णांकerface in the VM physical address space.  These addresses are properties
 * of the emulated core/SoC and thereक्रमe user space initially knows this
 * inक्रमmation.
 * Check them क्रम sanity (alignment, द्विगुन assignment). We can't check क्रम
 * overlapping regions in हाल of a भव GICv3 here, since we करोn't know
 * the number of VCPUs yet, so we defer this check to map_resources().
 */
पूर्णांक kvm_vgic_addr(काष्ठा kvm *kvm, अचिन्हित दीर्घ type, u64 *addr, bool ग_लिखो)
अणु
	पूर्णांक r = 0;
	काष्ठा vgic_dist *vgic = &kvm->arch.vgic;
	phys_addr_t *addr_ptr, alignment;
	u64 undef_value = VGIC_ADDR_UNDEF;

	mutex_lock(&kvm->lock);
	चयन (type) अणु
	हाल KVM_VGIC_V2_ADDR_TYPE_DIST:
		r = vgic_check_type(kvm, KVM_DEV_TYPE_ARM_VGIC_V2);
		addr_ptr = &vgic->vgic_dist_base;
		alignment = SZ_4K;
		अवरोध;
	हाल KVM_VGIC_V2_ADDR_TYPE_CPU:
		r = vgic_check_type(kvm, KVM_DEV_TYPE_ARM_VGIC_V2);
		addr_ptr = &vgic->vgic_cpu_base;
		alignment = SZ_4K;
		अवरोध;
	हाल KVM_VGIC_V3_ADDR_TYPE_DIST:
		r = vgic_check_type(kvm, KVM_DEV_TYPE_ARM_VGIC_V3);
		addr_ptr = &vgic->vgic_dist_base;
		alignment = SZ_64K;
		अवरोध;
	हाल KVM_VGIC_V3_ADDR_TYPE_REDIST: अणु
		काष्ठा vgic_redist_region *rdreg;

		r = vgic_check_type(kvm, KVM_DEV_TYPE_ARM_VGIC_V3);
		अगर (r)
			अवरोध;
		अगर (ग_लिखो) अणु
			r = vgic_v3_set_redist_base(kvm, 0, *addr, 0);
			जाओ out;
		पूर्ण
		rdreg = list_first_entry_or_null(&vgic->rd_regions,
						 काष्ठा vgic_redist_region, list);
		अगर (!rdreg)
			addr_ptr = &undef_value;
		अन्यथा
			addr_ptr = &rdreg->base;
		अवरोध;
	पूर्ण
	हाल KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION:
	अणु
		काष्ठा vgic_redist_region *rdreg;
		u8 index;

		r = vgic_check_type(kvm, KVM_DEV_TYPE_ARM_VGIC_V3);
		अगर (r)
			अवरोध;

		index = *addr & KVM_VGIC_V3_RDIST_INDEX_MASK;

		अगर (ग_लिखो) अणु
			gpa_t base = *addr & KVM_VGIC_V3_RDIST_BASE_MASK;
			u32 count = (*addr & KVM_VGIC_V3_RDIST_COUNT_MASK)
					>> KVM_VGIC_V3_RDIST_COUNT_SHIFT;
			u8 flags = (*addr & KVM_VGIC_V3_RDIST_FLAGS_MASK)
					>> KVM_VGIC_V3_RDIST_FLAGS_SHIFT;

			अगर (!count || flags)
				r = -EINVAL;
			अन्यथा
				r = vgic_v3_set_redist_base(kvm, index,
							    base, count);
			जाओ out;
		पूर्ण

		rdreg = vgic_v3_rdist_region_from_index(kvm, index);
		अगर (!rdreg) अणु
			r = -ENOENT;
			जाओ out;
		पूर्ण

		*addr = index;
		*addr |= rdreg->base;
		*addr |= (u64)rdreg->count << KVM_VGIC_V3_RDIST_COUNT_SHIFT;
		जाओ out;
	पूर्ण
	शेष:
		r = -ENODEV;
	पूर्ण

	अगर (r)
		जाओ out;

	अगर (ग_लिखो) अणु
		r = vgic_check_ioaddr(kvm, addr_ptr, *addr, alignment);
		अगर (!r)
			*addr_ptr = *addr;
	पूर्ण अन्यथा अणु
		*addr = *addr_ptr;
	पूर्ण

out:
	mutex_unlock(&kvm->lock);
	वापस r;
पूर्ण

अटल पूर्णांक vgic_set_common_attr(काष्ठा kvm_device *dev,
				काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक r;

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_ADDR: अणु
		u64 __user *uaddr = (u64 __user *)(दीर्घ)attr->addr;
		u64 addr;
		अचिन्हित दीर्घ type = (अचिन्हित दीर्घ)attr->attr;

		अगर (copy_from_user(&addr, uaddr, माप(addr)))
			वापस -EFAULT;

		r = kvm_vgic_addr(dev->kvm, type, &addr, true);
		वापस (r == -ENODEV) ? -ENXIO : r;
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_NR_IRQS: अणु
		u32 __user *uaddr = (u32 __user *)(दीर्घ)attr->addr;
		u32 val;
		पूर्णांक ret = 0;

		अगर (get_user(val, uaddr))
			वापस -EFAULT;

		/*
		 * We require:
		 * - at least 32 SPIs on top of the 16 SGIs and 16 PPIs
		 * - at most 1024 पूर्णांकerrupts
		 * - a multiple of 32 पूर्णांकerrupts
		 */
		अगर (val < (VGIC_NR_PRIVATE_IRQS + 32) ||
		    val > VGIC_MAX_RESERVED ||
		    (val & 31))
			वापस -EINVAL;

		mutex_lock(&dev->kvm->lock);

		अगर (vgic_पढ़ोy(dev->kvm) || dev->kvm->arch.vgic.nr_spis)
			ret = -EBUSY;
		अन्यथा
			dev->kvm->arch.vgic.nr_spis =
				val - VGIC_NR_PRIVATE_IRQS;

		mutex_unlock(&dev->kvm->lock);

		वापस ret;
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_CTRL: अणु
		चयन (attr->attr) अणु
		हाल KVM_DEV_ARM_VGIC_CTRL_INIT:
			mutex_lock(&dev->kvm->lock);
			r = vgic_init(dev->kvm);
			mutex_unlock(&dev->kvm->lock);
			वापस r;
		पूर्ण
		अवरोध;
	पूर्ण
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक vgic_get_common_attr(काष्ठा kvm_device *dev,
				काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक r = -ENXIO;

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_ADDR: अणु
		u64 __user *uaddr = (u64 __user *)(दीर्घ)attr->addr;
		u64 addr;
		अचिन्हित दीर्घ type = (अचिन्हित दीर्घ)attr->attr;

		अगर (copy_from_user(&addr, uaddr, माप(addr)))
			वापस -EFAULT;

		r = kvm_vgic_addr(dev->kvm, type, &addr, false);
		अगर (r)
			वापस (r == -ENODEV) ? -ENXIO : r;

		अगर (copy_to_user(uaddr, &addr, माप(addr)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_NR_IRQS: अणु
		u32 __user *uaddr = (u32 __user *)(दीर्घ)attr->addr;

		r = put_user(dev->kvm->arch.vgic.nr_spis +
			     VGIC_NR_PRIVATE_IRQS, uaddr);
		अवरोध;
	पूर्ण
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक vgic_create(काष्ठा kvm_device *dev, u32 type)
अणु
	वापस kvm_vgic_create(dev->kvm, type);
पूर्ण

अटल व्योम vgic_destroy(काष्ठा kvm_device *dev)
अणु
	kमुक्त(dev);
पूर्ण

पूर्णांक kvm_रेजिस्टर_vgic_device(अचिन्हित दीर्घ type)
अणु
	पूर्णांक ret = -ENODEV;

	चयन (type) अणु
	हाल KVM_DEV_TYPE_ARM_VGIC_V2:
		ret = kvm_रेजिस्टर_device_ops(&kvm_arm_vgic_v2_ops,
					      KVM_DEV_TYPE_ARM_VGIC_V2);
		अवरोध;
	हाल KVM_DEV_TYPE_ARM_VGIC_V3:
		ret = kvm_रेजिस्टर_device_ops(&kvm_arm_vgic_v3_ops,
					      KVM_DEV_TYPE_ARM_VGIC_V3);

		अगर (ret)
			अवरोध;
		ret = kvm_vgic_रेजिस्टर_its_device();
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक vgic_v2_parse_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr,
		       काष्ठा vgic_reg_attr *reg_attr)
अणु
	पूर्णांक cpuid;

	cpuid = (attr->attr & KVM_DEV_ARM_VGIC_CPUID_MASK) >>
		 KVM_DEV_ARM_VGIC_CPUID_SHIFT;

	अगर (cpuid >= atomic_पढ़ो(&dev->kvm->online_vcpus))
		वापस -EINVAL;

	reg_attr->vcpu = kvm_get_vcpu(dev->kvm, cpuid);
	reg_attr->addr = attr->attr & KVM_DEV_ARM_VGIC_OFFSET_MASK;

	वापस 0;
पूर्ण

/* unlocks vcpus from @vcpu_lock_idx and smaller */
अटल व्योम unlock_vcpus(काष्ठा kvm *kvm, पूर्णांक vcpu_lock_idx)
अणु
	काष्ठा kvm_vcpu *पंचांगp_vcpu;

	क्रम (; vcpu_lock_idx >= 0; vcpu_lock_idx--) अणु
		पंचांगp_vcpu = kvm_get_vcpu(kvm, vcpu_lock_idx);
		mutex_unlock(&पंचांगp_vcpu->mutex);
	पूर्ण
पूर्ण

व्योम unlock_all_vcpus(काष्ठा kvm *kvm)
अणु
	unlock_vcpus(kvm, atomic_पढ़ो(&kvm->online_vcpus) - 1);
पूर्ण

/* Returns true अगर all vcpus were locked, false otherwise */
bool lock_all_vcpus(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_vcpu *पंचांगp_vcpu;
	पूर्णांक c;

	/*
	 * Any समय a vcpu is run, vcpu_load is called which tries to grab the
	 * vcpu->mutex.  By grabbing the vcpu->mutex of all VCPUs we ensure
	 * that no other VCPUs are run and fiddle with the vgic state जबतक we
	 * access it.
	 */
	kvm_क्रम_each_vcpu(c, पंचांगp_vcpu, kvm) अणु
		अगर (!mutex_trylock(&पंचांगp_vcpu->mutex)) अणु
			unlock_vcpus(kvm, c - 1);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/**
 * vgic_v2_attr_regs_access - allows user space to access VGIC v2 state
 *
 * @dev:      kvm device handle
 * @attr:     kvm device attribute
 * @reg:      address the value is पढ़ो or written
 * @is_ग_लिखो: true अगर userspace is writing a रेजिस्टर
 */
अटल पूर्णांक vgic_v2_attr_regs_access(काष्ठा kvm_device *dev,
				    काष्ठा kvm_device_attr *attr,
				    u32 *reg, bool is_ग_लिखो)
अणु
	काष्ठा vgic_reg_attr reg_attr;
	gpa_t addr;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक ret;

	ret = vgic_v2_parse_attr(dev, attr, &reg_attr);
	अगर (ret)
		वापस ret;

	vcpu = reg_attr.vcpu;
	addr = reg_attr.addr;

	mutex_lock(&dev->kvm->lock);

	ret = vgic_init(dev->kvm);
	अगर (ret)
		जाओ out;

	अगर (!lock_all_vcpus(dev->kvm)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_CPU_REGS:
		ret = vgic_v2_cpuअगर_uaccess(vcpu, is_ग_लिखो, addr, reg);
		अवरोध;
	हाल KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
		ret = vgic_v2_dist_uaccess(vcpu, is_ग_लिखो, addr, reg);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	unlock_all_vcpus(dev->kvm);
out:
	mutex_unlock(&dev->kvm->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vgic_v2_set_attr(काष्ठा kvm_device *dev,
			    काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	ret = vgic_set_common_attr(dev, attr);
	अगर (ret != -ENXIO)
		वापस ret;

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
	हाल KVM_DEV_ARM_VGIC_GRP_CPU_REGS: अणु
		u32 __user *uaddr = (u32 __user *)(दीर्घ)attr->addr;
		u32 reg;

		अगर (get_user(reg, uaddr))
			वापस -EFAULT;

		वापस vgic_v2_attr_regs_access(dev, attr, &reg, true);
	पूर्ण
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक vgic_v2_get_attr(काष्ठा kvm_device *dev,
			    काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	ret = vgic_get_common_attr(dev, attr);
	अगर (ret != -ENXIO)
		वापस ret;

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
	हाल KVM_DEV_ARM_VGIC_GRP_CPU_REGS: अणु
		u32 __user *uaddr = (u32 __user *)(दीर्घ)attr->addr;
		u32 reg = 0;

		ret = vgic_v2_attr_regs_access(dev, attr, &reg, false);
		अगर (ret)
			वापस ret;
		वापस put_user(reg, uaddr);
	पूर्ण
	पूर्ण

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक vgic_v2_has_attr(काष्ठा kvm_device *dev,
			    काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_ADDR:
		चयन (attr->attr) अणु
		हाल KVM_VGIC_V2_ADDR_TYPE_DIST:
		हाल KVM_VGIC_V2_ADDR_TYPE_CPU:
			वापस 0;
		पूर्ण
		अवरोध;
	हाल KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
	हाल KVM_DEV_ARM_VGIC_GRP_CPU_REGS:
		वापस vgic_v2_has_attr_regs(dev, attr);
	हाल KVM_DEV_ARM_VGIC_GRP_NR_IRQS:
		वापस 0;
	हाल KVM_DEV_ARM_VGIC_GRP_CTRL:
		चयन (attr->attr) अणु
		हाल KVM_DEV_ARM_VGIC_CTRL_INIT:
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENXIO;
पूर्ण

काष्ठा kvm_device_ops kvm_arm_vgic_v2_ops = अणु
	.name = "kvm-arm-vgic-v2",
	.create = vgic_create,
	.destroy = vgic_destroy,
	.set_attr = vgic_v2_set_attr,
	.get_attr = vgic_v2_get_attr,
	.has_attr = vgic_v2_has_attr,
पूर्ण;

पूर्णांक vgic_v3_parse_attr(काष्ठा kvm_device *dev, काष्ठा kvm_device_attr *attr,
		       काष्ठा vgic_reg_attr *reg_attr)
अणु
	अचिन्हित दीर्घ vgic_mpidr, mpidr_reg;

	/*
	 * For KVM_DEV_ARM_VGIC_GRP_DIST_REGS group,
	 * attr might not hold MPIDR. Hence assume vcpu0.
	 */
	अगर (attr->group != KVM_DEV_ARM_VGIC_GRP_DIST_REGS) अणु
		vgic_mpidr = (attr->attr & KVM_DEV_ARM_VGIC_V3_MPIDR_MASK) >>
			      KVM_DEV_ARM_VGIC_V3_MPIDR_SHIFT;

		mpidr_reg = VGIC_TO_MPIDR(vgic_mpidr);
		reg_attr->vcpu = kvm_mpidr_to_vcpu(dev->kvm, mpidr_reg);
	पूर्ण अन्यथा अणु
		reg_attr->vcpu = kvm_get_vcpu(dev->kvm, 0);
	पूर्ण

	अगर (!reg_attr->vcpu)
		वापस -EINVAL;

	reg_attr->addr = attr->attr & KVM_DEV_ARM_VGIC_OFFSET_MASK;

	वापस 0;
पूर्ण

/*
 * vgic_v3_attr_regs_access - allows user space to access VGIC v3 state
 *
 * @dev:      kvm device handle
 * @attr:     kvm device attribute
 * @reg:      address the value is पढ़ो or written
 * @is_ग_लिखो: true अगर userspace is writing a रेजिस्टर
 */
अटल पूर्णांक vgic_v3_attr_regs_access(काष्ठा kvm_device *dev,
				    काष्ठा kvm_device_attr *attr,
				    u64 *reg, bool is_ग_लिखो)
अणु
	काष्ठा vgic_reg_attr reg_attr;
	gpa_t addr;
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक ret;
	u32 पंचांगp32;

	ret = vgic_v3_parse_attr(dev, attr, &reg_attr);
	अगर (ret)
		वापस ret;

	vcpu = reg_attr.vcpu;
	addr = reg_attr.addr;

	mutex_lock(&dev->kvm->lock);

	अगर (unlikely(!vgic_initialized(dev->kvm))) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (!lock_all_vcpus(dev->kvm)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
		अगर (is_ग_लिखो)
			पंचांगp32 = *reg;

		ret = vgic_v3_dist_uaccess(vcpu, is_ग_लिखो, addr, &पंचांगp32);
		अगर (!is_ग_लिखो)
			*reg = पंचांगp32;
		अवरोध;
	हाल KVM_DEV_ARM_VGIC_GRP_REDIST_REGS:
		अगर (is_ग_लिखो)
			पंचांगp32 = *reg;

		ret = vgic_v3_redist_uaccess(vcpu, is_ग_लिखो, addr, &पंचांगp32);
		अगर (!is_ग_लिखो)
			*reg = पंचांगp32;
		अवरोध;
	हाल KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS: अणु
		u64 regid;

		regid = (attr->attr & KVM_DEV_ARM_VGIC_SYSREG_INSTR_MASK);
		ret = vgic_v3_cpu_sysregs_uaccess(vcpu, is_ग_लिखो,
						  regid, reg);
		अवरोध;
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_LEVEL_INFO: अणु
		अचिन्हित पूर्णांक info, पूर्णांकid;

		info = (attr->attr & KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_MASK) >>
			KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_SHIFT;
		अगर (info == VGIC_LEVEL_INFO_LINE_LEVEL) अणु
			पूर्णांकid = attr->attr &
				KVM_DEV_ARM_VGIC_LINE_LEVEL_INTID_MASK;
			ret = vgic_v3_line_level_info_uaccess(vcpu, is_ग_लिखो,
							      पूर्णांकid, reg);
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	unlock_all_vcpus(dev->kvm);
out:
	mutex_unlock(&dev->kvm->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vgic_v3_set_attr(काष्ठा kvm_device *dev,
			    काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	ret = vgic_set_common_attr(dev, attr);
	अगर (ret != -ENXIO)
		वापस ret;

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
	हाल KVM_DEV_ARM_VGIC_GRP_REDIST_REGS: अणु
		u32 __user *uaddr = (u32 __user *)(दीर्घ)attr->addr;
		u32 पंचांगp32;
		u64 reg;

		अगर (get_user(पंचांगp32, uaddr))
			वापस -EFAULT;

		reg = पंचांगp32;
		वापस vgic_v3_attr_regs_access(dev, attr, &reg, true);
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS: अणु
		u64 __user *uaddr = (u64 __user *)(दीर्घ)attr->addr;
		u64 reg;

		अगर (get_user(reg, uaddr))
			वापस -EFAULT;

		वापस vgic_v3_attr_regs_access(dev, attr, &reg, true);
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_LEVEL_INFO: अणु
		u32 __user *uaddr = (u32 __user *)(दीर्घ)attr->addr;
		u64 reg;
		u32 पंचांगp32;

		अगर (get_user(पंचांगp32, uaddr))
			वापस -EFAULT;

		reg = पंचांगp32;
		वापस vgic_v3_attr_regs_access(dev, attr, &reg, true);
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_CTRL: अणु
		पूर्णांक ret;

		चयन (attr->attr) अणु
		हाल KVM_DEV_ARM_VGIC_SAVE_PENDING_TABLES:
			mutex_lock(&dev->kvm->lock);

			अगर (!lock_all_vcpus(dev->kvm)) अणु
				mutex_unlock(&dev->kvm->lock);
				वापस -EBUSY;
			पूर्ण
			ret = vgic_v3_save_pending_tables(dev->kvm);
			unlock_all_vcpus(dev->kvm);
			mutex_unlock(&dev->kvm->lock);
			वापस ret;
		पूर्ण
		अवरोध;
	पूर्ण
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक vgic_v3_get_attr(काष्ठा kvm_device *dev,
			    काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret;

	ret = vgic_get_common_attr(dev, attr);
	अगर (ret != -ENXIO)
		वापस ret;

	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
	हाल KVM_DEV_ARM_VGIC_GRP_REDIST_REGS: अणु
		u32 __user *uaddr = (u32 __user *)(दीर्घ)attr->addr;
		u64 reg;
		u32 पंचांगp32;

		ret = vgic_v3_attr_regs_access(dev, attr, &reg, false);
		अगर (ret)
			वापस ret;
		पंचांगp32 = reg;
		वापस put_user(पंचांगp32, uaddr);
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS: अणु
		u64 __user *uaddr = (u64 __user *)(दीर्घ)attr->addr;
		u64 reg;

		ret = vgic_v3_attr_regs_access(dev, attr, &reg, false);
		अगर (ret)
			वापस ret;
		वापस put_user(reg, uaddr);
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_LEVEL_INFO: अणु
		u32 __user *uaddr = (u32 __user *)(दीर्घ)attr->addr;
		u64 reg;
		u32 पंचांगp32;

		ret = vgic_v3_attr_regs_access(dev, attr, &reg, false);
		अगर (ret)
			वापस ret;
		पंचांगp32 = reg;
		वापस put_user(पंचांगp32, uaddr);
	पूर्ण
	पूर्ण
	वापस -ENXIO;
पूर्ण

अटल पूर्णांक vgic_v3_has_attr(काष्ठा kvm_device *dev,
			    काष्ठा kvm_device_attr *attr)
अणु
	चयन (attr->group) अणु
	हाल KVM_DEV_ARM_VGIC_GRP_ADDR:
		चयन (attr->attr) अणु
		हाल KVM_VGIC_V3_ADDR_TYPE_DIST:
		हाल KVM_VGIC_V3_ADDR_TYPE_REDIST:
		हाल KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION:
			वापस 0;
		पूर्ण
		अवरोध;
	हाल KVM_DEV_ARM_VGIC_GRP_DIST_REGS:
	हाल KVM_DEV_ARM_VGIC_GRP_REDIST_REGS:
	हाल KVM_DEV_ARM_VGIC_GRP_CPU_SYSREGS:
		वापस vgic_v3_has_attr_regs(dev, attr);
	हाल KVM_DEV_ARM_VGIC_GRP_NR_IRQS:
		वापस 0;
	हाल KVM_DEV_ARM_VGIC_GRP_LEVEL_INFO: अणु
		अगर (((attr->attr & KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_MASK) >>
		      KVM_DEV_ARM_VGIC_LINE_LEVEL_INFO_SHIFT) ==
		      VGIC_LEVEL_INFO_LINE_LEVEL)
			वापस 0;
		अवरोध;
	पूर्ण
	हाल KVM_DEV_ARM_VGIC_GRP_CTRL:
		चयन (attr->attr) अणु
		हाल KVM_DEV_ARM_VGIC_CTRL_INIT:
			वापस 0;
		हाल KVM_DEV_ARM_VGIC_SAVE_PENDING_TABLES:
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENXIO;
पूर्ण

काष्ठा kvm_device_ops kvm_arm_vgic_v3_ops = अणु
	.name = "kvm-arm-vgic-v3",
	.create = vgic_create,
	.destroy = vgic_destroy,
	.set_attr = vgic_v3_set_attr,
	.get_attr = vgic_v3_get_attr,
	.has_attr = vgic_v3_has_attr,
पूर्ण;
