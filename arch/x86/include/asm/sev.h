<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * AMD Encrypted Register State Support
 *
 * Author: Joerg Roedel <jroedel@suse.de>
 */

#अगर_अघोषित __ASM_ENCRYPTED_STATE_H
#घोषणा __ASM_ENCRYPTED_STATE_H

#समावेश <linux/types.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/sev-common.h>

#घोषणा GHCB_PROTO_OUR		0x0001UL
#घोषणा GHCB_PROTOCOL_MAX	1ULL
#घोषणा GHCB_DEFAULT_USAGE	0ULL

#घोषणा	VMGEXIT()			अणु यंत्र अस्थिर("rep; vmmcall\n\r"); पूर्ण

क्रमागत es_result अणु
	ES_OK,			/* All good */
	ES_UNSUPPORTED,		/* Requested operation not supported */
	ES_VMM_ERROR,		/* Unexpected state from the VMM */
	ES_DECODE_FAILED,	/* Inकाष्ठाion decoding failed */
	ES_EXCEPTION,		/* Inकाष्ठाion caused exception */
	ES_RETRY,		/* Retry inकाष्ठाion emulation */
पूर्ण;

काष्ठा es_fault_info अणु
	अचिन्हित दीर्घ vector;
	अचिन्हित दीर्घ error_code;
	अचिन्हित दीर्घ cr2;
पूर्ण;

काष्ठा pt_regs;

/* ES inकाष्ठाion emulation context */
काष्ठा es_em_ctxt अणु
	काष्ठा pt_regs *regs;
	काष्ठा insn insn;
	काष्ठा es_fault_info fi;
पूर्ण;

व्योम करो_vc_no_ghcb(काष्ठा pt_regs *regs, अचिन्हित दीर्घ निकास_code);

अटल अंतरभूत u64 lower_bits(u64 val, अचिन्हित पूर्णांक bits)
अणु
	u64 mask = (1ULL << bits) - 1;

	वापस (val & mask);
पूर्ण

काष्ठा real_mode_header;
क्रमागत stack_type;

/* Early IDT entry poपूर्णांकs क्रम #VC handler */
बाह्य व्योम vc_no_ghcb(व्योम);
बाह्य व्योम vc_boot_ghcb(व्योम);
बाह्य bool handle_vc_boot_ghcb(काष्ठा pt_regs *regs);

#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
बाह्य काष्ठा अटल_key_false sev_es_enable_key;
बाह्य व्योम __sev_es_ist_enter(काष्ठा pt_regs *regs);
बाह्य व्योम __sev_es_ist_निकास(व्योम);
अटल __always_अंतरभूत व्योम sev_es_ist_enter(काष्ठा pt_regs *regs)
अणु
	अगर (अटल_branch_unlikely(&sev_es_enable_key))
		__sev_es_ist_enter(regs);
पूर्ण
अटल __always_अंतरभूत व्योम sev_es_ist_निकास(व्योम)
अणु
	अगर (अटल_branch_unlikely(&sev_es_enable_key))
		__sev_es_ist_निकास();
पूर्ण
बाह्य पूर्णांक sev_es_setup_ap_jump_table(काष्ठा real_mode_header *rmh);
बाह्य व्योम __sev_es_nmi_complete(व्योम);
अटल __always_अंतरभूत व्योम sev_es_nmi_complete(व्योम)
अणु
	अगर (अटल_branch_unlikely(&sev_es_enable_key))
		__sev_es_nmi_complete();
पूर्ण
बाह्य पूर्णांक __init sev_es_efi_map_ghcbs(pgd_t *pgd);
#अन्यथा
अटल अंतरभूत व्योम sev_es_ist_enter(काष्ठा pt_regs *regs) अणु पूर्ण
अटल अंतरभूत व्योम sev_es_ist_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक sev_es_setup_ap_jump_table(काष्ठा real_mode_header *rmh) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम sev_es_nmi_complete(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक sev_es_efi_map_ghcbs(pgd_t *pgd) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
