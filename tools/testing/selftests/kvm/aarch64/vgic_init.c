<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * vgic init sequence tests
 *
 * Copyright (C) 2020, Red Hat, Inc.
 */
#घोषणा _GNU_SOURCE
#समावेश <linux/kernel.h>
#समावेश <sys/syscall.h>
#समावेश <यंत्र/kvm.h>
#समावेश <यंत्र/kvm_para.h>

#समावेश "test_util.h"
#समावेश "kvm_util.h"
#समावेश "processor.h"

#घोषणा NR_VCPUS		4

#घोषणा REDIST_REGION_ATTR_ADDR(count, base, flags, index) (((uपूर्णांक64_t)(count) << 52) | \
	((uपूर्णांक64_t)((base) >> 16) << 16) | ((uपूर्णांक64_t)(flags) << 12) | index)
#घोषणा REG_OFFSET(vcpu, offset) (((uपूर्णांक64_t)vcpu << 32) | offset)

#घोषणा GICR_TYPER 0x8

काष्ठा vm_gic अणु
	काष्ठा kvm_vm *vm;
	पूर्णांक gic_fd;
पूर्ण;

अटल पूर्णांक max_ipa_bits;

/* helper to access a redistributor रेजिस्टर */
अटल पूर्णांक access_redist_reg(पूर्णांक gicv3_fd, पूर्णांक vcpu, पूर्णांक offset,
			     uपूर्णांक32_t *val, bool ग_लिखो)
अणु
	uपूर्णांक64_t attr = REG_OFFSET(vcpu, offset);

	वापस _kvm_device_access(gicv3_fd, KVM_DEV_ARM_VGIC_GRP_REDIST_REGS,
				  attr, val, ग_लिखो);
पूर्ण

/* dummy guest code */
अटल व्योम guest_code(व्योम)
अणु
	GUEST_SYNC(0);
	GUEST_SYNC(1);
	GUEST_SYNC(2);
	GUEST_DONE();
पूर्ण

/* we करोn't want to निश्चित on run execution, hence that helper */
अटल पूर्णांक run_vcpu(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid)
अणु
	ucall_init(vm, शून्य);
	पूर्णांक ret = _vcpu_ioctl(vm, vcpuid, KVM_RUN, शून्य);
	अगर (ret)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

अटल काष्ठा vm_gic vm_gic_create(व्योम)
अणु
	काष्ठा vm_gic v;

	v.vm = vm_create_शेष_with_vcpus(NR_VCPUS, 0, 0, guest_code, शून्य);
	v.gic_fd = kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V3, false);

	वापस v;
पूर्ण

अटल व्योम vm_gic_destroy(काष्ठा vm_gic *v)
अणु
	बंद(v->gic_fd);
	kvm_vm_मुक्त(v->vm);
पूर्ण

/**
 * Helper routine that perक्रमms KVM device tests in general and
 * especially ARM_VGIC_V3 ones. Eventually the ARM_VGIC_V3
 * device माला_लो created, a legacy RDIST region is set at @0x0
 * and a DIST region is set @0x60000
 */
अटल व्योम subtest_dist_rdist(काष्ठा vm_gic *v)
अणु
	पूर्णांक ret;
	uपूर्णांक64_t addr;

	/* Check existing group/attributes */
	kvm_device_check_attr(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			      KVM_VGIC_V3_ADDR_TYPE_DIST);

	kvm_device_check_attr(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			      KVM_VGIC_V3_ADDR_TYPE_REDIST);

	/* check non existing attribute */
	ret = _kvm_device_check_attr(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR, 0);
	TEST_ASSERT(ret && त्रुटि_सं == ENXIO, "attribute not supported");

	/* misaligned DIST and REDIST address settings */
	addr = 0x1000;
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_DIST, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "GICv3 dist base not 64kB aligned");

	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "GICv3 redist base not 64kB aligned");

	/* out of range address */
	अगर (max_ipa_bits) अणु
		addr = 1ULL << max_ipa_bits;
		ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
					 KVM_VGIC_V3_ADDR_TYPE_DIST, &addr, true);
		TEST_ASSERT(ret && त्रुटि_सं == E2BIG, "dist address beyond IPA limit");

		ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
					 KVM_VGIC_V3_ADDR_TYPE_REDIST, &addr, true);
		TEST_ASSERT(ret && त्रुटि_सं == E2BIG, "redist address beyond IPA limit");
	पूर्ण

	/* set REDIST base address @0x0*/
	addr = 0x00000;
	kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST, &addr, true);

	/* Attempt to create a second legacy redistributor region */
	addr = 0xE0000;
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EEXIST, "GICv3 redist base set again");

	/* Attempt to mix legacy and new redistributor regions */
	addr = REDIST_REGION_ATTR_ADDR(NR_VCPUS, 0x100000, 0, 0);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "attempt to mix GICv3 REDIST and REDIST_REGION");

	/*
	 * Set overlapping DIST / REDIST, cannot be detected here. Will be detected
	 * on first vcpu run instead.
	 */
	addr = 3 * 2 * 0x10000;
	kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR, KVM_VGIC_V3_ADDR_TYPE_DIST,
			  &addr, true);
पूर्ण

/* Test the new REDIST region API */
अटल व्योम subtest_redist_regions(काष्ठा vm_gic *v)
अणु
	uपूर्णांक64_t addr, expected_addr;
	पूर्णांक ret;

	ret = kvm_device_check_attr(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				     KVM_VGIC_V3_ADDR_TYPE_REDIST);
	TEST_ASSERT(!ret, "Multiple redist regions advertised");

	addr = REDIST_REGION_ATTR_ADDR(NR_VCPUS, 0x100000, 2, 0);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "redist region attr value with flags != 0");

	addr = REDIST_REGION_ATTR_ADDR(0, 0x100000, 0, 0);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "redist region attr value with count== 0");

	addr = REDIST_REGION_ATTR_ADDR(2, 0x200000, 0, 1);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL,
		    "attempt to register the first rdist region with index != 0");

	addr = REDIST_REGION_ATTR_ADDR(2, 0x201000, 0, 1);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "rdist region with misaligned address");

	addr = REDIST_REGION_ATTR_ADDR(2, 0x200000, 0, 0);
	kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);

	addr = REDIST_REGION_ATTR_ADDR(2, 0x200000, 0, 1);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "register an rdist region with already used index");

	addr = REDIST_REGION_ATTR_ADDR(1, 0x210000, 0, 2);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL,
		    "register an rdist region overlapping with another one");

	addr = REDIST_REGION_ATTR_ADDR(1, 0x240000, 0, 2);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "register redist region with index not +1");

	addr = REDIST_REGION_ATTR_ADDR(1, 0x240000, 0, 1);
	kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);

	addr = REDIST_REGION_ATTR_ADDR(1, 1ULL << max_ipa_bits, 0, 2);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == E2BIG,
		    "register redist region with base address beyond IPA range");

	addr = 0x260000;
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL,
		    "Mix KVM_VGIC_V3_ADDR_TYPE_REDIST and REDIST_REGION");

	/*
	 * Now there are 2 redist regions:
	 * region 0 @ 0x200000 2 redists
	 * region 1 @ 0x240000 1 redist
	 * Attempt to पढ़ो their अक्षरacteristics
	 */

	addr = REDIST_REGION_ATTR_ADDR(0, 0, 0, 0);
	expected_addr = REDIST_REGION_ATTR_ADDR(2, 0x200000, 0, 0);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, false);
	TEST_ASSERT(!ret && addr == expected_addr, "read characteristics of region #0");

	addr = REDIST_REGION_ATTR_ADDR(0, 0, 0, 1);
	expected_addr = REDIST_REGION_ATTR_ADDR(1, 0x240000, 0, 1);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, false);
	TEST_ASSERT(!ret && addr == expected_addr, "read characteristics of region #1");

	addr = REDIST_REGION_ATTR_ADDR(0, 0, 0, 2);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, false);
	TEST_ASSERT(ret && त्रुटि_सं == ENOENT, "read characteristics of non existing region");

	addr = 0x260000;
	kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_DIST, &addr, true);

	addr = REDIST_REGION_ATTR_ADDR(1, 0x260000, 0, 2);
	ret = _kvm_device_access(v->gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "register redist region colliding with dist");
पूर्ण

/*
 * VGIC KVM device is created and initialized beक्रमe the secondary CPUs
 * get created
 */
अटल व्योम test_vgic_then_vcpus(व्योम)
अणु
	काष्ठा vm_gic v;
	पूर्णांक ret, i;

	v.vm = vm_create_शेष(0, 0, guest_code);
	v.gic_fd = kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V3, false);

	subtest_dist_rdist(&v);

	/* Add the rest of the VCPUs */
	क्रम (i = 1; i < NR_VCPUS; ++i)
		vm_vcpu_add_शेष(v.vm, i, guest_code);

	ret = run_vcpu(v.vm, 3);
	TEST_ASSERT(ret == -EINVAL, "dist/rdist overlap detected on 1st vcpu run");

	vm_gic_destroy(&v);
पूर्ण

/* All the VCPUs are created beक्रमe the VGIC KVM device माला_लो initialized */
अटल व्योम test_vcpus_then_vgic(व्योम)
अणु
	काष्ठा vm_gic v;
	पूर्णांक ret;

	v = vm_gic_create();

	subtest_dist_rdist(&v);

	ret = run_vcpu(v.vm, 3);
	TEST_ASSERT(ret == -EINVAL, "dist/rdist overlap detected on 1st vcpu run");

	vm_gic_destroy(&v);
पूर्ण

अटल व्योम test_new_redist_regions(व्योम)
अणु
	व्योम *dummy = शून्य;
	काष्ठा vm_gic v;
	uपूर्णांक64_t addr;
	पूर्णांक ret;

	v = vm_gic_create();
	subtest_redist_regions(&v);
	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_CTRL,
			  KVM_DEV_ARM_VGIC_CTRL_INIT, शून्य, true);

	ret = run_vcpu(v.vm, 3);
	TEST_ASSERT(ret == -ENXIO, "running without sufficient number of rdists");
	vm_gic_destroy(&v);

	/* step2 */

	v = vm_gic_create();
	subtest_redist_regions(&v);

	addr = REDIST_REGION_ATTR_ADDR(1, 0x280000, 0, 2);
	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);

	ret = run_vcpu(v.vm, 3);
	TEST_ASSERT(ret == -EBUSY, "running without vgic explicit init");

	vm_gic_destroy(&v);

	/* step 3 */

	v = vm_gic_create();
	subtest_redist_regions(&v);

	_kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, dummy, true);
	TEST_ASSERT(ret && त्रुटि_सं == EFAULT,
		    "register a third region allowing to cover the 4 vcpus");

	addr = REDIST_REGION_ATTR_ADDR(1, 0x280000, 0, 2);
	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);

	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_CTRL,
			  KVM_DEV_ARM_VGIC_CTRL_INIT, शून्य, true);

	ret = run_vcpu(v.vm, 3);
	TEST_ASSERT(!ret, "vcpu run");

	vm_gic_destroy(&v);
पूर्ण

अटल व्योम test_typer_accesses(व्योम)
अणु
	काष्ठा vm_gic v;
	uपूर्णांक64_t addr;
	uपूर्णांक32_t val;
	पूर्णांक ret, i;

	v.vm = vm_create_शेष(0, 0, guest_code);

	v.gic_fd = kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V3, false);

	vm_vcpu_add_शेष(v.vm, 3, guest_code);

	ret = access_redist_reg(v.gic_fd, 1, GICR_TYPER, &val, false);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "attempting to read GICR_TYPER of non created vcpu");

	vm_vcpu_add_शेष(v.vm, 1, guest_code);

	ret = access_redist_reg(v.gic_fd, 1, GICR_TYPER, &val, false);
	TEST_ASSERT(ret && त्रुटि_सं == EBUSY, "read GICR_TYPER before GIC initialized");

	vm_vcpu_add_शेष(v.vm, 2, guest_code);

	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_CTRL,
			  KVM_DEV_ARM_VGIC_CTRL_INIT, शून्य, true);

	क्रम (i = 0; i < NR_VCPUS ; i++) अणु
		ret = access_redist_reg(v.gic_fd, 0, GICR_TYPER, &val, false);
		TEST_ASSERT(!ret && !val, "read GICR_TYPER before rdist region setting");
	पूर्ण

	addr = REDIST_REGION_ATTR_ADDR(2, 0x200000, 0, 0);
	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);

	/* The 2 first rdists should be put there (vcpu 0 and 3) */
	ret = access_redist_reg(v.gic_fd, 0, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && !val, "read typer of rdist #0");

	ret = access_redist_reg(v.gic_fd, 3, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x310, "read typer of rdist #1");

	addr = REDIST_REGION_ATTR_ADDR(10, 0x100000, 0, 1);
	ret = _kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
				 KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);
	TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "collision with previous rdist region");

	ret = access_redist_reg(v.gic_fd, 1, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x100,
		    "no redist region attached to vcpu #1 yet, last cannot be returned");

	ret = access_redist_reg(v.gic_fd, 2, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x200,
		    "no redist region attached to vcpu #2, last cannot be returned");

	addr = REDIST_REGION_ATTR_ADDR(10, 0x20000, 0, 1);
	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);

	ret = access_redist_reg(v.gic_fd, 1, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x100, "read typer of rdist #1");

	ret = access_redist_reg(v.gic_fd, 2, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x210,
		    "read typer of rdist #1, last properly returned");

	vm_gic_destroy(&v);
पूर्ण

/**
 * Test GICR_TYPER last bit with new redist regions
 * rdist regions #1 and #2 are contiguous
 * rdist region #0 @0x100000 2 rdist capacity
 *     rdists: 0, 3 (Last)
 * rdist region #1 @0x240000 2 rdist capacity
 *     rdists:  5, 4 (Last)
 * rdist region #2 @0x200000 2 rdist capacity
 *     rdists: 1, 2
 */
अटल व्योम test_last_bit_redist_regions(व्योम)
अणु
	uपूर्णांक32_t vcpuids[] = अणु 0, 3, 5, 4, 1, 2 पूर्ण;
	काष्ठा vm_gic v;
	uपूर्णांक64_t addr;
	uपूर्णांक32_t val;
	पूर्णांक ret;

	v.vm = vm_create_शेष_with_vcpus(6, 0, 0, guest_code, vcpuids);

	v.gic_fd = kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V3, false);

	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_CTRL,
			  KVM_DEV_ARM_VGIC_CTRL_INIT, शून्य, true);

	addr = REDIST_REGION_ATTR_ADDR(2, 0x100000, 0, 0);
	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);

	addr = REDIST_REGION_ATTR_ADDR(2, 0x240000, 0, 1);
	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);

	addr = REDIST_REGION_ATTR_ADDR(2, 0x200000, 0, 2);
	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION, &addr, true);

	ret = access_redist_reg(v.gic_fd, 0, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x000, "read typer of rdist #0");

	ret = access_redist_reg(v.gic_fd, 1, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x100, "read typer of rdist #1");

	ret = access_redist_reg(v.gic_fd, 2, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x200, "read typer of rdist #2");

	ret = access_redist_reg(v.gic_fd, 3, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x310, "read typer of rdist #3");

	ret = access_redist_reg(v.gic_fd, 5, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x500, "read typer of rdist #5");

	ret = access_redist_reg(v.gic_fd, 4, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x410, "read typer of rdist #4");

	vm_gic_destroy(&v);
पूर्ण

/* Test last bit with legacy region */
अटल व्योम test_last_bit_single_rdist(व्योम)
अणु
	uपूर्णांक32_t vcpuids[] = अणु 0, 3, 5, 4, 1, 2 पूर्ण;
	काष्ठा vm_gic v;
	uपूर्णांक64_t addr;
	uपूर्णांक32_t val;
	पूर्णांक ret;

	v.vm = vm_create_शेष_with_vcpus(6, 0, 0, guest_code, vcpuids);

	v.gic_fd = kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V3, false);

	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_CTRL,
			  KVM_DEV_ARM_VGIC_CTRL_INIT, शून्य, true);

	addr = 0x10000;
	kvm_device_access(v.gic_fd, KVM_DEV_ARM_VGIC_GRP_ADDR,
			  KVM_VGIC_V3_ADDR_TYPE_REDIST, &addr, true);

	ret = access_redist_reg(v.gic_fd, 0, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x000, "read typer of rdist #0");

	ret = access_redist_reg(v.gic_fd, 3, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x300, "read typer of rdist #1");

	ret = access_redist_reg(v.gic_fd, 5, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x500, "read typer of rdist #2");

	ret = access_redist_reg(v.gic_fd, 1, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x100, "read typer of rdist #3");

	ret = access_redist_reg(v.gic_fd, 2, GICR_TYPER, &val, false);
	TEST_ASSERT(!ret && val == 0x210, "read typer of rdist #3");

	vm_gic_destroy(&v);
पूर्ण

व्योम test_kvm_device(व्योम)
अणु
	काष्ठा vm_gic v;
	पूर्णांक ret, fd;

	v.vm = vm_create_शेष_with_vcpus(NR_VCPUS, 0, 0, guest_code, शून्य);

	/* try to create a non existing KVM device */
	ret = _kvm_create_device(v.vm, 0, true, &fd);
	TEST_ASSERT(ret && त्रुटि_सं == ENODEV, "unsupported device");

	/* trial mode with VGIC_V3 device */
	ret = _kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V3, true, &fd);
	अगर (ret) अणु
		prपूर्णांक_skip("GICv3 not supported");
		निकास(KSFT_SKIP);
	पूर्ण
	v.gic_fd = kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V3, false);

	ret = _kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V3, false, &fd);
	TEST_ASSERT(ret && त्रुटि_सं == EEXIST, "create GICv3 device twice");

	kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V3, true);

	अगर (!_kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V2, true, &fd)) अणु
		ret = _kvm_create_device(v.vm, KVM_DEV_TYPE_ARM_VGIC_V2, false, &fd);
		TEST_ASSERT(ret && त्रुटि_सं == EINVAL, "create GICv2 while v3 exists");
	पूर्ण

	vm_gic_destroy(&v);
पूर्ण

पूर्णांक मुख्य(पूर्णांक ac, अक्षर **av)
अणु
	max_ipa_bits = kvm_check_cap(KVM_CAP_ARM_VM_IPA_SIZE);

	test_kvm_device();
	test_vcpus_then_vgic();
	test_vgic_then_vcpus();
	test_new_redist_regions();
	test_typer_accesses();
	test_last_bit_redist_regions();
	test_last_bit_single_rdist();

	वापस 0;
पूर्ण
