<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SPECCTRL_H_
#घोषणा _ASM_X86_SPECCTRL_H_

#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/nospec-branch.h>

/*
 * On VMENTER we must preserve whatever view of the SPEC_CTRL MSR
 * the guest has, जबतक on VMEXIT we restore the host view. This
 * would be easier अगर SPEC_CTRL were architecturally maskable or
 * shaकरोwable क्रम guests but this is not (currently) the हाल.
 * Takes the guest view of SPEC_CTRL MSR as a parameter and also
 * the guest's version of VIRT_SPEC_CTRL, अगर emulated.
 */
बाह्य व्योम x86_virt_spec_ctrl(u64 guest_spec_ctrl, u64 guest_virt_spec_ctrl, bool guest);

/**
 * x86_spec_ctrl_set_guest - Set speculation control रेजिस्टरs क्रम the guest
 * @guest_spec_ctrl:		The guest content of MSR_SPEC_CTRL
 * @guest_virt_spec_ctrl:	The guest controlled bits of MSR_VIRT_SPEC_CTRL
 *				(may get translated to MSR_AMD64_LS_CFG bits)
 *
 * Aव्योमs writing to the MSR अगर the content/bits are the same
 */
अटल अंतरभूत
व्योम x86_spec_ctrl_set_guest(u64 guest_spec_ctrl, u64 guest_virt_spec_ctrl)
अणु
	x86_virt_spec_ctrl(guest_spec_ctrl, guest_virt_spec_ctrl, true);
पूर्ण

/**
 * x86_spec_ctrl_restore_host - Restore host speculation control रेजिस्टरs
 * @guest_spec_ctrl:		The guest content of MSR_SPEC_CTRL
 * @guest_virt_spec_ctrl:	The guest controlled bits of MSR_VIRT_SPEC_CTRL
 *				(may get translated to MSR_AMD64_LS_CFG bits)
 *
 * Aव्योमs writing to the MSR अगर the content/bits are the same
 */
अटल अंतरभूत
व्योम x86_spec_ctrl_restore_host(u64 guest_spec_ctrl, u64 guest_virt_spec_ctrl)
अणु
	x86_virt_spec_ctrl(guest_spec_ctrl, guest_virt_spec_ctrl, false);
पूर्ण

/* AMD specअगरic Speculative Store Bypass MSR data */
बाह्य u64 x86_amd_ls_cfg_base;
बाह्य u64 x86_amd_ls_cfg_ssbd_mask;

अटल अंतरभूत u64 ssbd_tअगर_to_spec_ctrl(u64 tअगरn)
अणु
	BUILD_BUG_ON(TIF_SSBD < SPEC_CTRL_SSBD_SHIFT);
	वापस (tअगरn & _TIF_SSBD) >> (TIF_SSBD - SPEC_CTRL_SSBD_SHIFT);
पूर्ण

अटल अंतरभूत u64 stibp_tअगर_to_spec_ctrl(u64 tअगरn)
अणु
	BUILD_BUG_ON(TIF_SPEC_IB < SPEC_CTRL_STIBP_SHIFT);
	वापस (tअगरn & _TIF_SPEC_IB) >> (TIF_SPEC_IB - SPEC_CTRL_STIBP_SHIFT);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ssbd_spec_ctrl_to_tअगर(u64 spec_ctrl)
अणु
	BUILD_BUG_ON(TIF_SSBD < SPEC_CTRL_SSBD_SHIFT);
	वापस (spec_ctrl & SPEC_CTRL_SSBD) << (TIF_SSBD - SPEC_CTRL_SSBD_SHIFT);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ stibp_spec_ctrl_to_tअगर(u64 spec_ctrl)
अणु
	BUILD_BUG_ON(TIF_SPEC_IB < SPEC_CTRL_STIBP_SHIFT);
	वापस (spec_ctrl & SPEC_CTRL_STIBP) << (TIF_SPEC_IB - SPEC_CTRL_STIBP_SHIFT);
पूर्ण

अटल अंतरभूत u64 ssbd_tअगर_to_amd_ls_cfg(u64 tअगरn)
अणु
	वापस (tअगरn & _TIF_SSBD) ? x86_amd_ls_cfg_ssbd_mask : 0ULL;
पूर्ण

#अगर_घोषित CONFIG_SMP
बाह्य व्योम speculative_store_bypass_ht_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम speculative_store_bypass_ht_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य व्योम speculation_ctrl_update(अचिन्हित दीर्घ tअगर);
बाह्य व्योम speculation_ctrl_update_current(व्योम);

#पूर्ण_अगर
