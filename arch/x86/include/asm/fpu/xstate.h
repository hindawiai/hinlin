<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_X86_XSAVE_H
#घोषणा __ASM_X86_XSAVE_H

#समावेश <linux/uaccess.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/user.h>

/* Bit 63 of XCR0 is reserved क्रम future expansion */
#घोषणा XFEATURE_MASK_EXTEND	(~(XFEATURE_MASK_FPSSE | (1ULL << 63)))

#घोषणा XSTATE_CPUID		0x0000000d

#घोषणा FXSAVE_SIZE	512

#घोषणा XSAVE_HDR_SIZE	    64
#घोषणा XSAVE_HDR_OFFSET    FXSAVE_SIZE

#घोषणा XSAVE_YMM_SIZE	    256
#घोषणा XSAVE_YMM_OFFSET    (XSAVE_HDR_SIZE + XSAVE_HDR_OFFSET)

#घोषणा XSAVE_ALIGNMENT     64

/* All currently supported user features */
#घोषणा XFEATURE_MASK_USER_SUPPORTED (XFEATURE_MASK_FP | \
				      XFEATURE_MASK_SSE | \
				      XFEATURE_MASK_YMM | \
				      XFEATURE_MASK_OPMASK | \
				      XFEATURE_MASK_ZMM_Hi256 | \
				      XFEATURE_MASK_Hi16_ZMM	 | \
				      XFEATURE_MASK_PKRU | \
				      XFEATURE_MASK_BNDREGS | \
				      XFEATURE_MASK_BNDCSR)

/* All currently supported supervisor features */
#घोषणा XFEATURE_MASK_SUPERVISOR_SUPPORTED (XFEATURE_MASK_PASID)

/*
 * A supervisor state component may not always contain valuable inक्रमmation,
 * and its size may be huge. Saving/restoring such supervisor state components
 * at each context चयन can cause high CPU and space overhead, which should
 * be aव्योमed. Such supervisor state components should only be saved/restored
 * on demand. The on-demand dynamic supervisor features are set in this mask.
 *
 * Unlike the existing supported supervisor features, a dynamic supervisor
 * feature करोes not allocate a buffer in task->fpu, and the corresponding
 * supervisor state component cannot be saved/restored at each context चयन.
 *
 * To support a dynamic supervisor feature, a developer should follow the
 * करोs and करोn'ts as below:
 * - Do dynamically allocate a buffer क्रम the supervisor state component.
 * - Do manually invoke the XSAVES/XRSTORS inकाष्ठाion to save/restore the
 *   state component to/from the buffer.
 * - Don't set the bit corresponding to the dynamic supervisor feature in
 *   IA32_XSS at run समय, since it has been set at boot समय.
 */
#घोषणा XFEATURE_MASK_DYNAMIC (XFEATURE_MASK_LBR)

/*
 * Unsupported supervisor features. When a supervisor feature in this mask is
 * supported in the future, move it to the supported supervisor feature mask.
 */
#घोषणा XFEATURE_MASK_SUPERVISOR_UNSUPPORTED (XFEATURE_MASK_PT)

/* All supervisor states including supported and unsupported states. */
#घोषणा XFEATURE_MASK_SUPERVISOR_ALL (XFEATURE_MASK_SUPERVISOR_SUPPORTED | \
				      XFEATURE_MASK_DYNAMIC | \
				      XFEATURE_MASK_SUPERVISOR_UNSUPPORTED)

#अगर_घोषित CONFIG_X86_64
#घोषणा REX_PREFIX	"0x48, "
#अन्यथा
#घोषणा REX_PREFIX
#पूर्ण_अगर

बाह्य u64 xfeatures_mask_all;

अटल अंतरभूत u64 xfeatures_mask_supervisor(व्योम)
अणु
	वापस xfeatures_mask_all & XFEATURE_MASK_SUPERVISOR_SUPPORTED;
पूर्ण

अटल अंतरभूत u64 xfeatures_mask_user(व्योम)
अणु
	वापस xfeatures_mask_all & XFEATURE_MASK_USER_SUPPORTED;
पूर्ण

अटल अंतरभूत u64 xfeatures_mask_dynamic(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_ARCH_LBR))
		वापस XFEATURE_MASK_DYNAMIC & ~XFEATURE_MASK_LBR;

	वापस XFEATURE_MASK_DYNAMIC;
पूर्ण

बाह्य u64 xstate_fx_sw_bytes[USER_XSTATE_FX_SW_WORDS];

बाह्य व्योम __init update_regset_xstate_info(अचिन्हित पूर्णांक size,
					     u64 xstate_mask);

व्योम *get_xsave_addr(काष्ठा xregs_state *xsave, पूर्णांक xfeature_nr);
स्थिर व्योम *get_xsave_field_ptr(पूर्णांक xfeature_nr);
पूर्णांक using_compacted_क्रमmat(व्योम);
पूर्णांक xfeature_size(पूर्णांक xfeature_nr);
काष्ठा membuf;
व्योम copy_xstate_to_kernel(काष्ठा membuf to, काष्ठा xregs_state *xsave);
पूर्णांक copy_kernel_to_xstate(काष्ठा xregs_state *xsave, स्थिर व्योम *kbuf);
पूर्णांक copy_user_to_xstate(काष्ठा xregs_state *xsave, स्थिर व्योम __user *ubuf);
व्योम copy_supervisor_to_kernel(काष्ठा xregs_state *xsave);
व्योम copy_dynamic_supervisor_to_kernel(काष्ठा xregs_state *xstate, u64 mask);
व्योम copy_kernel_to_dynamic_supervisor(काष्ठा xregs_state *xstate, u64 mask);


/* Validate an xstate header supplied by userspace (ptrace or sigवापस) */
पूर्णांक validate_user_xstate_header(स्थिर काष्ठा xstate_header *hdr);

#पूर्ण_अगर
