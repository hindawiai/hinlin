<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel-based Virtual Machine driver क्रम Linux
 *
 * Copyright 2016 Red Hat, Inc. and/or its affiliates.
 */
#समावेश <linux/kvm_host.h>
#समावेश <linux/debugfs.h>
#समावेश "lapic.h"

अटल पूर्णांक vcpu_get_समयr_advance_ns(व्योम *data, u64 *val)
अणु
	काष्ठा kvm_vcpu *vcpu = (काष्ठा kvm_vcpu *) data;
	*val = vcpu->arch.apic->lapic_समयr.समयr_advance_ns;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(vcpu_समयr_advance_ns_fops, vcpu_get_समयr_advance_ns, शून्य, "%llu\n");

अटल पूर्णांक vcpu_get_tsc_offset(व्योम *data, u64 *val)
अणु
	काष्ठा kvm_vcpu *vcpu = (काष्ठा kvm_vcpu *) data;
	*val = vcpu->arch.tsc_offset;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(vcpu_tsc_offset_fops, vcpu_get_tsc_offset, शून्य, "%lld\n");

अटल पूर्णांक vcpu_get_tsc_scaling_ratio(व्योम *data, u64 *val)
अणु
	काष्ठा kvm_vcpu *vcpu = (काष्ठा kvm_vcpu *) data;
	*val = vcpu->arch.tsc_scaling_ratio;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(vcpu_tsc_scaling_fops, vcpu_get_tsc_scaling_ratio, शून्य, "%llu\n");

अटल पूर्णांक vcpu_get_tsc_scaling_frac_bits(व्योम *data, u64 *val)
अणु
	*val = kvm_tsc_scaling_ratio_frac_bits;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(vcpu_tsc_scaling_frac_fops, vcpu_get_tsc_scaling_frac_bits, शून्य, "%llu\n");

व्योम kvm_arch_create_vcpu_debugfs(काष्ठा kvm_vcpu *vcpu, काष्ठा dentry *debugfs_dentry)
अणु
	debugfs_create_file("tsc-offset", 0444, debugfs_dentry, vcpu,
			    &vcpu_tsc_offset_fops);

	अगर (lapic_in_kernel(vcpu))
		debugfs_create_file("lapic_timer_advance_ns", 0444,
				    debugfs_dentry, vcpu,
				    &vcpu_समयr_advance_ns_fops);

	अगर (kvm_has_tsc_control) अणु
		debugfs_create_file("tsc-scaling-ratio", 0444,
				    debugfs_dentry, vcpu,
				    &vcpu_tsc_scaling_fops);
		debugfs_create_file("tsc-scaling-ratio-frac-bits", 0444,
				    debugfs_dentry, vcpu,
				    &vcpu_tsc_scaling_frac_fops);
	पूर्ण
पूर्ण
