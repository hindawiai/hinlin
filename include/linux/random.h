<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/अक्रमom.h
 *
 * Include file क्रम the अक्रमom number generator.
 */
#अगर_अघोषित _LINUX_RANDOM_H
#घोषणा _LINUX_RANDOM_H

#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/once.h>

#समावेश <uapi/linux/अक्रमom.h>

काष्ठा अक्रमom_पढ़ोy_callback अणु
	काष्ठा list_head list;
	व्योम (*func)(काष्ठा अक्रमom_पढ़ोy_callback *rdy);
	काष्ठा module *owner;
पूर्ण;

बाह्य व्योम add_device_अक्रमomness(स्थिर व्योम *, अचिन्हित पूर्णांक);
बाह्य व्योम add_bootloader_अक्रमomness(स्थिर व्योम *, अचिन्हित पूर्णांक);

#अगर defined(LATENT_ENTROPY_PLUGIN) && !defined(__CHECKER__)
अटल अंतरभूत व्योम add_latent_entropy(व्योम)
अणु
	add_device_अक्रमomness((स्थिर व्योम *)&latent_entropy,
			      माप(latent_entropy));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम add_latent_entropy(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य व्योम add_input_अक्रमomness(अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक code,
				 अचिन्हित पूर्णांक value) __latent_entropy;
बाह्य व्योम add_पूर्णांकerrupt_अक्रमomness(पूर्णांक irq, पूर्णांक irq_flags) __latent_entropy;

बाह्य व्योम get_अक्रमom_bytes(व्योम *buf, पूर्णांक nbytes);
बाह्य पूर्णांक रुको_क्रम_अक्रमom_bytes(व्योम);
बाह्य पूर्णांक __init अक्रम_initialize(व्योम);
बाह्य bool rng_is_initialized(व्योम);
बाह्य पूर्णांक add_अक्रमom_पढ़ोy_callback(काष्ठा अक्रमom_पढ़ोy_callback *rdy);
बाह्य व्योम del_अक्रमom_पढ़ोy_callback(काष्ठा अक्रमom_पढ़ोy_callback *rdy);
बाह्य पूर्णांक __must_check get_अक्रमom_bytes_arch(व्योम *buf, पूर्णांक nbytes);

#अगर_अघोषित MODULE
बाह्य स्थिर काष्ठा file_operations अक्रमom_fops, uअक्रमom_fops;
#पूर्ण_अगर

u32 get_अक्रमom_u32(व्योम);
u64 get_अक्रमom_u64(व्योम);
अटल अंतरभूत अचिन्हित पूर्णांक get_अक्रमom_पूर्णांक(व्योम)
अणु
	वापस get_अक्रमom_u32();
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ get_अक्रमom_दीर्घ(व्योम)
अणु
#अगर BITS_PER_LONG == 64
	वापस get_अक्रमom_u64();
#अन्यथा
	वापस get_अक्रमom_u32();
#पूर्ण_अगर
पूर्ण

/*
 * On 64-bit architectures, protect against non-terminated C string overflows
 * by zeroing out the first byte of the canary; this leaves 56 bits of entropy.
 */
#अगर_घोषित CONFIG_64BIT
# अगरdef __LITTLE_ENDIAN
#  define CANARY_MASK 0xffffffffffffff00UL
# अन्यथा /* big endian, 64 bits: */
#  define CANARY_MASK 0x00ffffffffffffffUL
# endअगर
#अन्यथा /* 32 bits: */
# define CANARY_MASK 0xffffffffUL
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित दीर्घ get_अक्रमom_canary(व्योम)
अणु
	अचिन्हित दीर्घ val = get_अक्रमom_दीर्घ();

	वापस val & CANARY_MASK;
पूर्ण

/* Calls रुको_क्रम_अक्रमom_bytes() and then calls get_अक्रमom_bytes(buf, nbytes).
 * Returns the result of the call to रुको_क्रम_अक्रमom_bytes. */
अटल अंतरभूत पूर्णांक get_अक्रमom_bytes_रुको(व्योम *buf, पूर्णांक nbytes)
अणु
	पूर्णांक ret = रुको_क्रम_अक्रमom_bytes();
	get_अक्रमom_bytes(buf, nbytes);
	वापस ret;
पूर्ण

#घोषणा declare_get_अक्रमom_var_रुको(var) \
	अटल अंतरभूत पूर्णांक get_अक्रमom_ ## var ## _रुको(var *out) अणु \
		पूर्णांक ret = रुको_क्रम_अक्रमom_bytes(); \
		अगर (unlikely(ret)) \
			वापस ret; \
		*out = get_अक्रमom_ ## var(); \
		वापस 0; \
	पूर्ण
declare_get_अक्रमom_var_रुको(u32)
declare_get_अक्रमom_var_रुको(u64)
declare_get_अक्रमom_var_रुको(पूर्णांक)
declare_get_अक्रमom_var_रुको(दीर्घ)
#अघोषित declare_get_अक्रमom_var

अचिन्हित दीर्घ अक्रमomize_page(अचिन्हित दीर्घ start, अचिन्हित दीर्घ range);

/*
 * This is deचिन्हित to be standalone क्रम just pअक्रमom
 * users, but क्रम now we include it from <linux/अक्रमom.h>
 * क्रम legacy reasons.
 */
#समावेश <linux/pअक्रमom.h>

#अगर_घोषित CONFIG_ARCH_RANDOM
# include <यंत्र/archअक्रमom.h>
#अन्यथा
अटल अंतरभूत bool __must_check arch_get_अक्रमom_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool __must_check arch_get_अक्रमom_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool __must_check arch_get_अक्रमom_seed_दीर्घ(अचिन्हित दीर्घ *v)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool __must_check arch_get_अक्रमom_seed_पूर्णांक(अचिन्हित पूर्णांक *v)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/*
 * Called from the boot CPU during startup; not valid to call once
 * secondary CPUs are up and preemption is possible.
 */
#अगर_अघोषित arch_get_अक्रमom_seed_दीर्घ_early
अटल अंतरभूत bool __init arch_get_अक्रमom_seed_दीर्घ_early(अचिन्हित दीर्घ *v)
अणु
	WARN_ON(प्रणाली_state != SYSTEM_BOOTING);
	वापस arch_get_अक्रमom_seed_दीर्घ(v);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_get_अक्रमom_दीर्घ_early
अटल अंतरभूत bool __init arch_get_अक्रमom_दीर्घ_early(अचिन्हित दीर्घ *v)
अणु
	WARN_ON(प्रणाली_state != SYSTEM_BOOTING);
	वापस arch_get_अक्रमom_दीर्घ(v);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_RANDOM_H */
