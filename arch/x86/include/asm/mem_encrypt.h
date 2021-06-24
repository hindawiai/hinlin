<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AMD Memory Encryption Support
 *
 * Copyright (C) 2016 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 */

#अगर_अघोषित __X86_MEM_ENCRYPT_H__
#घोषणा __X86_MEM_ENCRYPT_H__

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/init.h>

#समावेश <यंत्र/bootparam.h>

#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT

बाह्य u64 sme_me_mask;
बाह्य u64 sev_status;

व्योम sme_encrypt_execute(अचिन्हित दीर्घ encrypted_kernel_vaddr,
			 अचिन्हित दीर्घ decrypted_kernel_vaddr,
			 अचिन्हित दीर्घ kernel_len,
			 अचिन्हित दीर्घ encryption_wa,
			 अचिन्हित दीर्घ encryption_pgd);

व्योम __init sme_early_encrypt(resource_माप_प्रकार paddr,
			      अचिन्हित दीर्घ size);
व्योम __init sme_early_decrypt(resource_माप_प्रकार paddr,
			      अचिन्हित दीर्घ size);

व्योम __init sme_map_bootdata(अक्षर *real_mode_data);
व्योम __init sme_unmap_bootdata(अक्षर *real_mode_data);

व्योम __init sme_early_init(व्योम);
व्योम __init sev_setup_arch(व्योम);

व्योम __init sme_encrypt_kernel(काष्ठा boot_params *bp);
व्योम __init sme_enable(काष्ठा boot_params *bp);

पूर्णांक __init early_set_memory_decrypted(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size);
पूर्णांक __init early_set_memory_encrypted(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size);

व्योम __init mem_encrypt_मुक्त_decrypted_mem(व्योम);

/* Architecture __weak replacement functions */
व्योम __init mem_encrypt_init(व्योम);

व्योम __init sev_es_init_vc_handling(व्योम);
bool sme_active(व्योम);
bool sev_active(व्योम);
bool sev_es_active(व्योम);

#घोषणा __bss_decrypted __section(".bss..decrypted")

#अन्यथा	/* !CONFIG_AMD_MEM_ENCRYPT */

#घोषणा sme_me_mask	0ULL

अटल अंतरभूत व्योम __init sme_early_encrypt(resource_माप_प्रकार paddr,
					    अचिन्हित दीर्घ size) अणु पूर्ण
अटल अंतरभूत व्योम __init sme_early_decrypt(resource_माप_प्रकार paddr,
					    अचिन्हित दीर्घ size) अणु पूर्ण

अटल अंतरभूत व्योम __init sme_map_bootdata(अक्षर *real_mode_data) अणु पूर्ण
अटल अंतरभूत व्योम __init sme_unmap_bootdata(अक्षर *real_mode_data) अणु पूर्ण

अटल अंतरभूत व्योम __init sme_early_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम __init sev_setup_arch(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम __init sme_encrypt_kernel(काष्ठा boot_params *bp) अणु पूर्ण
अटल अंतरभूत व्योम __init sme_enable(काष्ठा boot_params *bp) अणु पूर्ण

अटल अंतरभूत व्योम sev_es_init_vc_handling(व्योम) अणु पूर्ण
अटल अंतरभूत bool sme_active(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool sev_active(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool sev_es_active(व्योम) अणु वापस false; पूर्ण

अटल अंतरभूत पूर्णांक __init
early_set_memory_decrypted(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक __init
early_set_memory_encrypted(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size) अणु वापस 0; पूर्ण

अटल अंतरभूत व्योम mem_encrypt_मुक्त_decrypted_mem(व्योम) अणु पूर्ण

#घोषणा __bss_decrypted

#पूर्ण_अगर	/* CONFIG_AMD_MEM_ENCRYPT */

/*
 * The __sme_pa() and __sme_pa_nodebug() macros are meant क्रम use when
 * writing to or comparing values from the cr3 रेजिस्टर.  Having the
 * encryption mask set in cr3 enables the PGD entry to be encrypted and
 * aव्योम special हाल handling of PGD allocations.
 */
#घोषणा __sme_pa(x)		(__pa(x) | sme_me_mask)
#घोषणा __sme_pa_nodebug(x)	(__pa_nodebug(x) | sme_me_mask)

बाह्य अक्षर __start_bss_decrypted[], __end_bss_decrypted[], __start_bss_decrypted_unused[];

अटल अंतरभूत bool mem_encrypt_active(व्योम)
अणु
	वापस sme_me_mask;
पूर्ण

अटल अंतरभूत u64 sme_get_me_mask(व्योम)
अणु
	वापस sme_me_mask;
पूर्ण

#पूर्ण_अगर	/* __ASSEMBLY__ */

#पूर्ण_अगर	/* __X86_MEM_ENCRYPT_H__ */
