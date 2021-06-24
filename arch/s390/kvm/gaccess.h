<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * access guest memory
 *
 * Copyright IBM Corp. 2008, 2014
 *
 *    Author(s): Carsten Otte <cotte@de.ibm.com>
 */

#अगर_अघोषित __KVM_S390_GACCESS_H
#घोषणा __KVM_S390_GACCESS_H

#समावेश <linux/compiler.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ptrace.h>
#समावेश "kvm-s390.h"

/**
 * kvm_s390_real_to_असल - convert guest real address to guest असलolute address
 * @prefix - guest prefix
 * @gra - guest real address
 *
 * Returns the guest असलolute address that corresponds to the passed guest real
 * address @gra of by applying the given prefix.
 */
अटल अंतरभूत अचिन्हित दीर्घ _kvm_s390_real_to_असल(u32 prefix, अचिन्हित दीर्घ gra)
अणु
	अगर (gra < 2 * PAGE_SIZE)
		gra += prefix;
	अन्यथा अगर (gra >= prefix && gra < prefix + 2 * PAGE_SIZE)
		gra -= prefix;
	वापस gra;
पूर्ण

/**
 * kvm_s390_real_to_असल - convert guest real address to guest असलolute address
 * @vcpu - guest भव cpu
 * @gra - guest real address
 *
 * Returns the guest असलolute address that corresponds to the passed guest real
 * address @gra of a भव guest cpu by applying its prefix.
 */
अटल अंतरभूत अचिन्हित दीर्घ kvm_s390_real_to_असल(काष्ठा kvm_vcpu *vcpu,
						 अचिन्हित दीर्घ gra)
अणु
	वापस _kvm_s390_real_to_असल(kvm_s390_get_prefix(vcpu), gra);
पूर्ण

/**
 * _kvm_s390_logical_to_effective - convert guest logical to effective address
 * @psw: psw of the guest
 * @ga: guest logical address
 *
 * Convert a guest logical address to an effective address by applying the
 * rules of the addressing mode defined by bits 31 and 32 of the given PSW
 * (extendended/basic addressing mode).
 *
 * Depending on the addressing mode, the upper 40 bits (24 bit addressing
 * mode), 33 bits (31 bit addressing mode) or no bits (64 bit addressing
 * mode) of @ga will be zeroed and the reमुख्यing bits will be वापसed.
 */
अटल अंतरभूत अचिन्हित दीर्घ _kvm_s390_logical_to_effective(psw_t *psw,
							   अचिन्हित दीर्घ ga)
अणु
	अगर (psw_bits(*psw).eaba == PSW_BITS_AMODE_64BIT)
		वापस ga;
	अगर (psw_bits(*psw).eaba == PSW_BITS_AMODE_31BIT)
		वापस ga & ((1UL << 31) - 1);
	वापस ga & ((1UL << 24) - 1);
पूर्ण

/**
 * kvm_s390_logical_to_effective - convert guest logical to effective address
 * @vcpu: guest भव cpu
 * @ga: guest logical address
 *
 * Convert a guest vcpu logical address to a guest vcpu effective address by
 * applying the rules of the vcpu's addressing mode defined by PSW bits 31
 * and 32 (extendended/basic addressing mode).
 *
 * Depending on the vcpu's addressing mode the upper 40 bits (24 bit addressing
 * mode), 33 bits (31 bit addressing mode) or no bits (64 bit addressing mode)
 * of @ga will be zeroed and the reमुख्यing bits will be वापसed.
 */
अटल अंतरभूत अचिन्हित दीर्घ kvm_s390_logical_to_effective(काष्ठा kvm_vcpu *vcpu,
							  अचिन्हित दीर्घ ga)
अणु
	वापस _kvm_s390_logical_to_effective(&vcpu->arch.sie_block->gpsw, ga);
पूर्ण

/*
 * put_guest_lc, पढ़ो_guest_lc and ग_लिखो_guest_lc are guest access functions
 * which shall only be used to access the lowcore of a vcpu.
 * These functions should be used क्रम e.g. पूर्णांकerrupt handlers where no
 * guest memory access protection facilities, like key or low address
 * protection, are applicable.
 * At a later poपूर्णांक guest vcpu lowcore access should happen via pinned
 * prefix pages, so that these pages can be accessed directly via the
 * kernel mapping. All of these *_lc functions can be हटाओd then.
 */

/**
 * put_guest_lc - ग_लिखो a simple variable to a guest vcpu's lowcore
 * @vcpu: भव cpu
 * @x: value to copy to guest
 * @gra: vcpu's destination guest real address
 *
 * Copies a simple value from kernel space to a guest vcpu's lowcore.
 * The size of the variable may be 1, 2, 4 or 8 bytes. The destination
 * must be located in the vcpu's lowcore. Otherwise the result is undefined.
 *
 * Returns zero on success or -EFAULT on error.
 *
 * Note: an error indicates that either the kernel is out of memory or
 *	 the guest memory mapping is broken. In any हाल the best solution
 *	 would be to terminate the guest.
 *	 It is wrong to inject a guest exception.
 */
#घोषणा put_guest_lc(vcpu, x, gra)				\
(अणु								\
	काष्ठा kvm_vcpu *__vcpu = (vcpu);			\
	__typeof__(*(gra)) __x = (x);				\
	अचिन्हित दीर्घ __gpa;					\
								\
	__gpa = (अचिन्हित दीर्घ)(gra);				\
	__gpa += kvm_s390_get_prefix(__vcpu);			\
	kvm_ग_लिखो_guest(__vcpu->kvm, __gpa, &__x, माप(__x));	\
पूर्ण)

/**
 * ग_लिखो_guest_lc - copy data from kernel space to guest vcpu's lowcore
 * @vcpu: भव cpu
 * @gra: vcpu's source guest real address
 * @data: source address in kernel space
 * @len: number of bytes to copy
 *
 * Copy data from kernel space to guest vcpu's lowcore. The entire range must
 * be located within the vcpu's lowcore, otherwise the result is undefined.
 *
 * Returns zero on success or -EFAULT on error.
 *
 * Note: an error indicates that either the kernel is out of memory or
 *	 the guest memory mapping is broken. In any हाल the best solution
 *	 would be to terminate the guest.
 *	 It is wrong to inject a guest exception.
 */
अटल अंतरभूत __must_check
पूर्णांक ग_लिखो_guest_lc(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gra, व्योम *data,
		   अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ gpa = gra + kvm_s390_get_prefix(vcpu);

	वापस kvm_ग_लिखो_guest(vcpu->kvm, gpa, data, len);
पूर्ण

/**
 * पढ़ो_guest_lc - copy data from guest vcpu's lowcore to kernel space
 * @vcpu: भव cpu
 * @gra: vcpu's source guest real address
 * @data: destination address in kernel space
 * @len: number of bytes to copy
 *
 * Copy data from guest vcpu's lowcore to kernel space. The entire range must
 * be located within the vcpu's lowcore, otherwise the result is undefined.
 *
 * Returns zero on success or -EFAULT on error.
 *
 * Note: an error indicates that either the kernel is out of memory or
 *	 the guest memory mapping is broken. In any हाल the best solution
 *	 would be to terminate the guest.
 *	 It is wrong to inject a guest exception.
 */
अटल अंतरभूत __must_check
पूर्णांक पढ़ो_guest_lc(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gra, व्योम *data,
		  अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ gpa = gra + kvm_s390_get_prefix(vcpu);

	वापस kvm_पढ़ो_guest(vcpu->kvm, gpa, data, len);
पूर्ण

क्रमागत gacc_mode अणु
	GACC_FETCH,
	GACC_STORE,
	GACC_IFETCH,
पूर्ण;

पूर्णांक guest_translate_address(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva,
			    u8 ar, अचिन्हित दीर्घ *gpa, क्रमागत gacc_mode mode);
पूर्णांक check_gva_range(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva, u8 ar,
		    अचिन्हित दीर्घ length, क्रमागत gacc_mode mode);

पूर्णांक access_guest(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ ga, u8 ar, व्योम *data,
		 अचिन्हित दीर्घ len, क्रमागत gacc_mode mode);

पूर्णांक access_guest_real(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gra,
		      व्योम *data, अचिन्हित दीर्घ len, क्रमागत gacc_mode mode);

/**
 * ग_लिखो_guest - copy data from kernel space to guest space
 * @vcpu: भव cpu
 * @ga: guest address
 * @ar: access रेजिस्टर
 * @data: source address in kernel space
 * @len: number of bytes to copy
 *
 * Copy @len bytes from @data (kernel space) to @ga (guest address).
 * In order to copy data to guest space the PSW of the vcpu is inspected:
 * If DAT is off data will be copied to guest real or असलolute memory.
 * If DAT is on data will be copied to the address space as specअगरied by
 * the address space bits of the PSW:
 * Primary, secondary, home space or access रेजिस्टर mode.
 * The addressing mode of the PSW is also inspected, so that address wrap
 * around is taken पूर्णांकo account क्रम 24-, 31- and 64-bit addressing mode,
 * अगर the to be copied data crosses page boundaries in guest address space.
 * In addition also low address and DAT protection are inspected beक्रमe
 * copying any data (key protection is currently not implemented).
 *
 * This function modअगरies the 'struct kvm_s390_pgm_info pgm' member of @vcpu.
 * In हाल of an access exception (e.g. protection exception) pgm will contain
 * all data necessary so that a subsequent call to 'kvm_s390_inject_prog_vcpu()'
 * will inject a correct exception पूर्णांकo the guest.
 * If no access exception happened, the contents of pgm are undefined when
 * this function वापसs.
 *
 * Returns:  - zero on success
 *	     - a negative value अगर e.g. the guest mapping is broken or in
 *	       हाल of out-of-memory. In this हाल the contents of pgm are
 *	       undefined. Also parts of @data may have been copied to guest
 *	       space.
 *	     - a positive value अगर an access exception happened. In this हाल
 *	       the वापसed value is the program पूर्णांकerruption code and the
 *	       contents of pgm may be used to inject an exception पूर्णांकo the
 *	       guest. No data has been copied to guest space.
 *
 * Note: in हाल an access exception is recognized no data has been copied to
 *	 guest space (this is also true, अगर the to be copied data would cross
 *	 one or more page boundaries in guest space).
 *	 Thereक्रमe this function may be used क्रम nullअगरying and suppressing
 *	 inकाष्ठाion emulation.
 *	 It may also be used क्रम terminating inकाष्ठाions, अगर it is undefined
 *	 अगर data has been changed in guest space in हाल of an exception.
 */
अटल अंतरभूत __must_check
पूर्णांक ग_लिखो_guest(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ ga, u8 ar, व्योम *data,
		अचिन्हित दीर्घ len)
अणु
	वापस access_guest(vcpu, ga, ar, data, len, GACC_STORE);
पूर्ण

/**
 * पढ़ो_guest - copy data from guest space to kernel space
 * @vcpu: भव cpu
 * @ga: guest address
 * @ar: access रेजिस्टर
 * @data: destination address in kernel space
 * @len: number of bytes to copy
 *
 * Copy @len bytes from @ga (guest address) to @data (kernel space).
 *
 * The behaviour of पढ़ो_guest is identical to ग_लिखो_guest, except that
 * data will be copied from guest space to kernel space.
 */
अटल अंतरभूत __must_check
पूर्णांक पढ़ो_guest(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ ga, u8 ar, व्योम *data,
	       अचिन्हित दीर्घ len)
अणु
	वापस access_guest(vcpu, ga, ar, data, len, GACC_FETCH);
पूर्ण

/**
 * पढ़ो_guest_instr - copy inकाष्ठाion data from guest space to kernel space
 * @vcpu: भव cpu
 * @ga: guest address
 * @data: destination address in kernel space
 * @len: number of bytes to copy
 *
 * Copy @len bytes from the given address (guest space) to @data (kernel
 * space).
 *
 * The behaviour of पढ़ो_guest_instr is identical to पढ़ो_guest, except that
 * inकाष्ठाion data will be पढ़ो from primary space when in home-space or
 * address-space mode.
 */
अटल अंतरभूत __must_check
पूर्णांक पढ़ो_guest_instr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ ga, व्योम *data,
		     अचिन्हित दीर्घ len)
अणु
	वापस access_guest(vcpu, ga, 0, data, len, GACC_IFETCH);
पूर्ण

/**
 * ग_लिखो_guest_असल - copy data from kernel space to guest space असलolute
 * @vcpu: भव cpu
 * @gpa: guest physical (असलolute) address
 * @data: source address in kernel space
 * @len: number of bytes to copy
 *
 * Copy @len bytes from @data (kernel space) to @gpa (guest असलolute address).
 * It is up to the caller to ensure that the entire guest memory range is
 * valid memory beक्रमe calling this function.
 * Guest low address and key protection are not checked.
 *
 * Returns zero on success or -EFAULT on error.
 *
 * If an error occurs data may have been copied partially to guest memory.
 */
अटल अंतरभूत __must_check
पूर्णांक ग_लिखो_guest_असल(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gpa, व्योम *data,
		    अचिन्हित दीर्घ len)
अणु
	वापस kvm_ग_लिखो_guest(vcpu->kvm, gpa, data, len);
पूर्ण

/**
 * पढ़ो_guest_असल - copy data from guest space असलolute to kernel space
 * @vcpu: भव cpu
 * @gpa: guest physical (असलolute) address
 * @data: destination address in kernel space
 * @len: number of bytes to copy
 *
 * Copy @len bytes from @gpa (guest असलolute address) to @data (kernel space).
 * It is up to the caller to ensure that the entire guest memory range is
 * valid memory beक्रमe calling this function.
 * Guest key protection is not checked.
 *
 * Returns zero on success or -EFAULT on error.
 *
 * If an error occurs data may have been copied partially to kernel space.
 */
अटल अंतरभूत __must_check
पूर्णांक पढ़ो_guest_असल(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gpa, व्योम *data,
		   अचिन्हित दीर्घ len)
अणु
	वापस kvm_पढ़ो_guest(vcpu->kvm, gpa, data, len);
पूर्ण

/**
 * ग_लिखो_guest_real - copy data from kernel space to guest space real
 * @vcpu: भव cpu
 * @gra: guest real address
 * @data: source address in kernel space
 * @len: number of bytes to copy
 *
 * Copy @len bytes from @data (kernel space) to @gra (guest real address).
 * It is up to the caller to ensure that the entire guest memory range is
 * valid memory beक्रमe calling this function.
 * Guest low address and key protection are not checked.
 *
 * Returns zero on success or -EFAULT on error.
 *
 * If an error occurs data may have been copied partially to guest memory.
 */
अटल अंतरभूत __must_check
पूर्णांक ग_लिखो_guest_real(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gra, व्योम *data,
		     अचिन्हित दीर्घ len)
अणु
	वापस access_guest_real(vcpu, gra, data, len, 1);
पूर्ण

/**
 * पढ़ो_guest_real - copy data from guest space real to kernel space
 * @vcpu: भव cpu
 * @gra: guest real address
 * @data: destination address in kernel space
 * @len: number of bytes to copy
 *
 * Copy @len bytes from @gra (guest real address) to @data (kernel space).
 * It is up to the caller to ensure that the entire guest memory range is
 * valid memory beक्रमe calling this function.
 * Guest key protection is not checked.
 *
 * Returns zero on success or -EFAULT on error.
 *
 * If an error occurs data may have been copied partially to kernel space.
 */
अटल अंतरभूत __must_check
पूर्णांक पढ़ो_guest_real(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gra, व्योम *data,
		    अचिन्हित दीर्घ len)
अणु
	वापस access_guest_real(vcpu, gra, data, len, 0);
पूर्ण

व्योम ipte_lock(काष्ठा kvm_vcpu *vcpu);
व्योम ipte_unlock(काष्ठा kvm_vcpu *vcpu);
पूर्णांक ipte_lock_held(काष्ठा kvm_vcpu *vcpu);
पूर्णांक kvm_s390_check_low_addr_prot_real(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gra);

/* MVPG PEI indication bits */
#घोषणा PEI_DAT_PROT 2
#घोषणा PEI_NOT_PTE 4

पूर्णांक kvm_s390_shaकरोw_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा gmap *shaकरोw,
			  अचिन्हित दीर्घ saddr, अचिन्हित दीर्घ *datptr);

#पूर्ण_अगर /* __KVM_S390_GACCESS_H */
