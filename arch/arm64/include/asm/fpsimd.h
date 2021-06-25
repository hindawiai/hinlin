<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_FP_H
#घोषणा __ASM_FP_H

#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/sigcontext.h>
#समावेश <यंत्र/sysreg.h>

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/bug.h>
#समावेश <linux/cache.h>
#समावेश <linux/init.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>

#अगर_घोषित CONFIG_COMPAT
/* Masks क्रम extracting the FPSR and FPCR from the FPSCR */
#घोषणा VFP_FPSCR_STAT_MASK	0xf800009f
#घोषणा VFP_FPSCR_CTRL_MASK	0x07f79f00
/*
 * The VFP state has 32x64-bit रेजिस्टरs and a single 32-bit
 * control/status रेजिस्टर.
 */
#घोषणा VFP_STATE_SIZE		((32 * 8) + 4)
#पूर्ण_अगर

काष्ठा task_काष्ठा;

बाह्य व्योम fpsimd_save_state(काष्ठा user_fpsimd_state *state);
बाह्य व्योम fpsimd_load_state(काष्ठा user_fpsimd_state *state);

बाह्य व्योम fpsimd_thपढ़ो_चयन(काष्ठा task_काष्ठा *next);
बाह्य व्योम fpsimd_flush_thपढ़ो(व्योम);

बाह्य व्योम fpsimd_संकेत_preserve_current_state(व्योम);
बाह्य व्योम fpsimd_preserve_current_state(व्योम);
बाह्य व्योम fpsimd_restore_current_state(व्योम);
बाह्य व्योम fpsimd_update_current_state(काष्ठा user_fpsimd_state स्थिर *state);

बाह्य व्योम fpsimd_bind_task_to_cpu(व्योम);
बाह्य व्योम fpsimd_bind_state_to_cpu(काष्ठा user_fpsimd_state *state,
				     व्योम *sve_state, अचिन्हित पूर्णांक sve_vl);

बाह्य व्योम fpsimd_flush_task_state(काष्ठा task_काष्ठा *target);
बाह्य व्योम fpsimd_save_and_flush_cpu_state(व्योम);

/* Maximum VL that SVE VL-agnostic software can transparently support */
#घोषणा SVE_VL_ARCH_MAX 0x100

/* Offset of FFR in the SVE रेजिस्टर dump */
अटल अंतरभूत माप_प्रकार sve_ffr_offset(पूर्णांक vl)
अणु
	वापस SVE_SIG_FFR_OFFSET(sve_vq_from_vl(vl)) - SVE_SIG_REGS_OFFSET;
पूर्ण

अटल अंतरभूत व्योम *sve_pffr(काष्ठा thपढ़ो_काष्ठा *thपढ़ो)
अणु
	वापस (अक्षर *)thपढ़ो->sve_state + sve_ffr_offset(thपढ़ो->sve_vl);
पूर्ण

बाह्य व्योम sve_save_state(व्योम *state, u32 *pfpsr);
बाह्य व्योम sve_load_state(व्योम स्थिर *state, u32 स्थिर *pfpsr,
			   अचिन्हित दीर्घ vq_minus_1);
बाह्य व्योम sve_flush_live(व्योम);
बाह्य व्योम sve_load_from_fpsimd_state(काष्ठा user_fpsimd_state स्थिर *state,
				       अचिन्हित दीर्घ vq_minus_1);
बाह्य अचिन्हित पूर्णांक sve_get_vl(व्योम);
बाह्य व्योम sve_set_vq(अचिन्हित दीर्घ vq_minus_1);

काष्ठा arm64_cpu_capabilities;
बाह्य व्योम sve_kernel_enable(स्थिर काष्ठा arm64_cpu_capabilities *__unused);

बाह्य u64 पढ़ो_zcr_features(व्योम);

बाह्य पूर्णांक __ro_after_init sve_max_vl;
बाह्य पूर्णांक __ro_after_init sve_max_भवisable_vl;
बाह्य __ro_after_init DECLARE_BITMAP(sve_vq_map, SVE_VQ_MAX);

/*
 * Helpers to translate bit indices in sve_vq_map to VQ values (and
 * vice versa).  This allows find_next_bit() to be used to find the
 * _maximum_ VQ not exceeding a certain value.
 */
अटल अंतरभूत अचिन्हित पूर्णांक __vq_to_bit(अचिन्हित पूर्णांक vq)
अणु
	वापस SVE_VQ_MAX - vq;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक __bit_to_vq(अचिन्हित पूर्णांक bit)
अणु
	वापस SVE_VQ_MAX - bit;
पूर्ण

/* Ensure vq >= SVE_VQ_MIN && vq <= SVE_VQ_MAX beक्रमe calling this function */
अटल अंतरभूत bool sve_vq_available(अचिन्हित पूर्णांक vq)
अणु
	वापस test_bit(__vq_to_bit(vq), sve_vq_map);
पूर्ण

#अगर_घोषित CONFIG_ARM64_SVE

बाह्य माप_प्रकार sve_state_size(काष्ठा task_काष्ठा स्थिर *task);

बाह्य व्योम sve_alloc(काष्ठा task_काष्ठा *task);
बाह्य व्योम fpsimd_release_task(काष्ठा task_काष्ठा *task);
बाह्य व्योम fpsimd_sync_to_sve(काष्ठा task_काष्ठा *task);
बाह्य व्योम sve_sync_to_fpsimd(काष्ठा task_काष्ठा *task);
बाह्य व्योम sve_sync_from_fpsimd_zeropad(काष्ठा task_काष्ठा *task);

बाह्य पूर्णांक sve_set_vector_length(काष्ठा task_काष्ठा *task,
				 अचिन्हित दीर्घ vl, अचिन्हित दीर्घ flags);

बाह्य पूर्णांक sve_set_current_vl(अचिन्हित दीर्घ arg);
बाह्य पूर्णांक sve_get_current_vl(व्योम);

अटल अंतरभूत व्योम sve_user_disable(व्योम)
अणु
	sysreg_clear_set(cpacr_el1, CPACR_EL1_ZEN_EL0EN, 0);
पूर्ण

अटल अंतरभूत व्योम sve_user_enable(व्योम)
अणु
	sysreg_clear_set(cpacr_el1, 0, CPACR_EL1_ZEN_EL0EN);
पूर्ण

#घोषणा sve_cond_update_zcr_vq(val, reg)		\
	करो अणु						\
		u64 __zcr = पढ़ो_sysreg_s((reg));	\
		u64 __new = __zcr & ~ZCR_ELx_LEN_MASK;	\
		__new |= (val) & ZCR_ELx_LEN_MASK;	\
		अगर (__zcr != __new)			\
			ग_लिखो_sysreg_s(__new, (reg));	\
	पूर्ण जबतक (0)

/*
 * Probing and setup functions.
 * Calls to these functions must be serialised with one another.
 */
बाह्य व्योम __init sve_init_vq_map(व्योम);
बाह्य व्योम sve_update_vq_map(व्योम);
बाह्य पूर्णांक sve_verअगरy_vq_map(व्योम);
बाह्य व्योम __init sve_setup(व्योम);

#अन्यथा /* ! CONFIG_ARM64_SVE */

अटल अंतरभूत व्योम sve_alloc(काष्ठा task_काष्ठा *task) अणु पूर्ण
अटल अंतरभूत व्योम fpsimd_release_task(काष्ठा task_काष्ठा *task) अणु पूर्ण
अटल अंतरभूत व्योम sve_sync_to_fpsimd(काष्ठा task_काष्ठा *task) अणु पूर्ण
अटल अंतरभूत व्योम sve_sync_from_fpsimd_zeropad(काष्ठा task_काष्ठा *task) अणु पूर्ण

अटल अंतरभूत पूर्णांक sve_set_current_vl(अचिन्हित दीर्घ arg)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक sve_get_current_vl(व्योम)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम sve_user_disable(व्योम) अणु BUILD_BUG(); पूर्ण
अटल अंतरभूत व्योम sve_user_enable(व्योम) अणु BUILD_BUG(); पूर्ण

#घोषणा sve_cond_update_zcr_vq(val, reg) करो अणु पूर्ण जबतक (0)

अटल अंतरभूत व्योम sve_init_vq_map(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम sve_update_vq_map(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक sve_verअगरy_vq_map(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम sve_setup(व्योम) अणु पूर्ण

#पूर्ण_अगर /* ! CONFIG_ARM64_SVE */

/* For use by EFI runसमय services calls only */
बाह्य व्योम __efi_fpsimd_begin(व्योम);
बाह्य व्योम __efi_fpsimd_end(व्योम);

#पूर्ण_अगर

#पूर्ण_अगर
