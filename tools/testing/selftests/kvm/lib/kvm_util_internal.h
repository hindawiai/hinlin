<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tools/testing/selftests/kvm/lib/kvm_util_पूर्णांकernal.h
 *
 * Copyright (C) 2018, Google LLC.
 */

#अगर_अघोषित SELFTEST_KVM_UTIL_INTERNAL_H
#घोषणा SELFTEST_KVM_UTIL_INTERNAL_H

#समावेश "linux/hashtable.h"
#समावेश "linux/rbtree.h"

#समावेश "sparsebit.h"

काष्ठा userspace_mem_region अणु
	काष्ठा kvm_userspace_memory_region region;
	काष्ठा sparsebit *unused_phy_pages;
	पूर्णांक fd;
	off_t offset;
	व्योम *host_mem;
	व्योम *host_alias;
	व्योम *mmap_start;
	व्योम *mmap_alias;
	माप_प्रकार mmap_size;
	काष्ठा rb_node gpa_node;
	काष्ठा rb_node hva_node;
	काष्ठा hlist_node slot_node;
पूर्ण;

काष्ठा vcpu अणु
	काष्ठा list_head list;
	uपूर्णांक32_t id;
	पूर्णांक fd;
	काष्ठा kvm_run *state;
	काष्ठा kvm_dirty_gfn *dirty_gfns;
	uपूर्णांक32_t fetch_index;
	uपूर्णांक32_t dirty_gfns_count;
पूर्ण;

काष्ठा userspace_mem_regions अणु
	काष्ठा rb_root gpa_tree;
	काष्ठा rb_root hva_tree;
	DECLARE_HASHTABLE(slot_hash, 9);
पूर्ण;

काष्ठा kvm_vm अणु
	पूर्णांक mode;
	अचिन्हित दीर्घ type;
	पूर्णांक kvm_fd;
	पूर्णांक fd;
	अचिन्हित पूर्णांक pgtable_levels;
	अचिन्हित पूर्णांक page_size;
	अचिन्हित पूर्णांक page_shअगरt;
	अचिन्हित पूर्णांक pa_bits;
	अचिन्हित पूर्णांक va_bits;
	uपूर्णांक64_t max_gfn;
	काष्ठा list_head vcpus;
	काष्ठा userspace_mem_regions regions;
	काष्ठा sparsebit *vpages_valid;
	काष्ठा sparsebit *vpages_mapped;
	bool has_irqchip;
	bool pgd_created;
	vm_paddr_t pgd;
	vm_vaddr_t gdt;
	vm_vaddr_t tss;
	vm_vaddr_t idt;
	vm_vaddr_t handlers;
	uपूर्णांक32_t dirty_ring_size;
पूर्ण;

काष्ठा vcpu *vcpu_find(काष्ठा kvm_vm *vm, uपूर्णांक32_t vcpuid);

/*
 * Virtual Translation Tables Dump
 *
 * Input Args:
 *   stream - Output खाता stream
 *   vm     - Virtual Machine
 *   indent - Left margin indent amount
 *
 * Output Args: None
 *
 * Return: None
 *
 * Dumps to the खाता stream given by @stream, the contents of all the
 * भव translation tables क्रम the VM given by @vm.
 */
व्योम virt_dump(खाता *stream, काष्ठा kvm_vm *vm, uपूर्णांक8_t indent);

/*
 * Register Dump
 *
 * Input Args:
 *   stream - Output खाता stream
 *   regs   - Registers
 *   indent - Left margin indent amount
 *
 * Output Args: None
 *
 * Return: None
 *
 * Dumps the state of the रेजिस्टरs given by @regs, to the खाता stream
 * given by @stream.
 */
व्योम regs_dump(खाता *stream, काष्ठा kvm_regs *regs, uपूर्णांक8_t indent);

/*
 * System Register Dump
 *
 * Input Args:
 *   stream - Output खाता stream
 *   sregs  - System रेजिस्टरs
 *   indent - Left margin indent amount
 *
 * Output Args: None
 *
 * Return: None
 *
 * Dumps the state of the प्रणाली रेजिस्टरs given by @sregs, to the खाता stream
 * given by @stream.
 */
व्योम sregs_dump(खाता *stream, काष्ठा kvm_sregs *sregs, uपूर्णांक8_t indent);

काष्ठा userspace_mem_region *
memslot2region(काष्ठा kvm_vm *vm, uपूर्णांक32_t memslot);

#पूर्ण_अगर /* SELFTEST_KVM_UTIL_INTERNAL_H */
