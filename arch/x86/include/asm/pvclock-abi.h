<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PVCLOCK_ABI_H
#घोषणा _ASM_X86_PVCLOCK_ABI_H
#अगर_अघोषित __ASSEMBLY__

/*
 * These काष्ठाs MUST NOT be changed.
 * They are the ABI between hypervisor and guest OS.
 * Both Xen and KVM are using this.
 *
 * pvघड़ी_vcpu_समय_info holds the प्रणाली समय and the tsc बारtamp
 * of the last update. So the guest can use the tsc delta to get a
 * more precise प्रणाली समय.  There is one per भव cpu.
 *
 * pvघड़ी_wall_घड़ी references the poपूर्णांक in समय when the प्रणाली
 * समय was zero (usually boot समय), thus the guest calculates the
 * current wall घड़ी by adding the प्रणाली समय.
 *
 * Protocol क्रम the "version" fields is: hypervisor उठाओs it (making
 * it uneven) beक्रमe it starts updating the fields and उठाओs it again
 * (making it even) when it is करोne.  Thus the guest can make sure the
 * समय values it got are consistent by checking the version beक्रमe
 * and after पढ़ोing them.
 */

काष्ठा pvघड़ी_vcpu_समय_info अणु
	u32   version;
	u32   pad0;
	u64   tsc_बारtamp;
	u64   प्रणाली_समय;
	u32   tsc_to_प्रणाली_mul;
	s8    tsc_shअगरt;
	u8    flags;
	u8    pad[2];
पूर्ण __attribute__((__packed__)); /* 32 bytes */

काष्ठा pvघड़ी_wall_घड़ी अणु
	u32   version;
	u32   sec;
	u32   nsec;
पूर्ण __attribute__((__packed__));

#घोषणा PVCLOCK_TSC_STABLE_BIT	(1 << 0)
#घोषणा PVCLOCK_GUEST_STOPPED	(1 << 1)
/* PVCLOCK_COUNTS_FROM_ZERO broke ABI and can't be used anymore. */
#घोषणा PVCLOCK_COUNTS_FROM_ZERO (1 << 2)
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_PVCLOCK_ABI_H */
