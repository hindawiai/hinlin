<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * Guest OS पूर्णांकerface to ARM Xen.
 *
 * Stefano Stabellini <stefano.stabellini@eu.citrix.com>, Citrix, 2012
 */

#अगर_अघोषित _ASM_ARM_XEN_INTERFACE_H
#घोषणा _ASM_ARM_XEN_INTERFACE_H

#समावेश <linux/types.h>

#घोषणा uपूर्णांक64_aligned_t uपूर्णांक64_t __attribute__((aligned(8)))

#घोषणा __DEFINE_GUEST_HANDLE(name, type) \
	प्रकार काष्ठा अणु जोड़ अणु type *p; uपूर्णांक64_aligned_t q; पूर्ण; पूर्ण  \
        __guest_handle_ ## name

#घोषणा DEFINE_GUEST_HANDLE_STRUCT(name) \
	__DEFINE_GUEST_HANDLE(name, काष्ठा name)
#घोषणा DEFINE_GUEST_HANDLE(name) __DEFINE_GUEST_HANDLE(name, name)
#घोषणा GUEST_HANDLE(name)        __guest_handle_ ## name

#घोषणा set_xen_guest_handle(hnd, val)			\
	करो अणु						\
		अगर (माप(hnd) == 8)			\
			*(uपूर्णांक64_t *)&(hnd) = 0;	\
		(hnd).p = val;				\
	पूर्ण जबतक (0)

#घोषणा __HYPERVISOR_platक्रमm_op_raw __HYPERVISOR_platक्रमm_op

#अगर_अघोषित __ASSEMBLY__
/* Explicitly size पूर्णांकegers that represent pfns in the पूर्णांकerface with
 * Xen so that we can have one ABI that works क्रम 32 and 64 bit guests.
 * Note that this means that the xen_pfn_t type may be capable of
 * representing pfn's which the guest cannot represent in its own pfn
 * type. However since pfn space is controlled by the guest this is
 * fine since it simply wouldn't be able to create any sure pfns in
 * the first place.
 */
प्रकार uपूर्णांक64_t xen_pfn_t;
#घोषणा PRI_xen_pfn "llx"
प्रकार uपूर्णांक64_t xen_uदीर्घ_t;
#घोषणा PRI_xen_uदीर्घ "llx"
प्रकार पूर्णांक64_t xen_दीर्घ_t;
#घोषणा PRI_xen_दीर्घ "llx"
/* Guest handles क्रम primitive C types. */
__DEFINE_GUEST_HANDLE(uअक्षर, अचिन्हित अक्षर);
__DEFINE_GUEST_HANDLE(uपूर्णांक,  अचिन्हित पूर्णांक);
DEFINE_GUEST_HANDLE(अक्षर);
DEFINE_GUEST_HANDLE(पूर्णांक);
DEFINE_GUEST_HANDLE(व्योम);
DEFINE_GUEST_HANDLE(uपूर्णांक64_t);
DEFINE_GUEST_HANDLE(uपूर्णांक32_t);
DEFINE_GUEST_HANDLE(xen_pfn_t);
DEFINE_GUEST_HANDLE(xen_uदीर्घ_t);

/* Maximum number of भव CPUs in multi-processor guests. */
#घोषणा MAX_VIRT_CPUS 1

काष्ठा arch_vcpu_info अणु पूर्ण;
काष्ठा arch_shared_info अणु पूर्ण;

/* TODO: Move pvघड़ी definitions some place arch independent */
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

/* It is OK to have a 12 bytes काष्ठा with no padding because it is packed */
काष्ठा pvघड़ी_wall_घड़ी अणु
	u32   version;
	u32   sec;
	u32   nsec;
	u32   sec_hi;
पूर्ण __attribute__((__packed__));
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_ARM_XEN_INTERFACE_H */
