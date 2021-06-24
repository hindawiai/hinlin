<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_TLBEX_H
#घोषणा __ASM_TLBEX_H

#समावेश <यंत्र/uयंत्र.h>

/*
 * Write अक्रमom or indexed TLB entry, and care about the hazards from
 * the preceding mtc0 and क्रम the following eret.
 */
क्रमागत tlb_ग_लिखो_entry अणु
	tlb_अक्रमom,
	tlb_indexed
पूर्ण;

बाह्य पूर्णांक pgd_reg;

व्योम build_get_pmde64(u32 **p, काष्ठा uयंत्र_label **l, काष्ठा uयंत्र_reloc **r,
		      अचिन्हित पूर्णांक पंचांगp, अचिन्हित पूर्णांक ptr);
व्योम build_get_pgde32(u32 **p, अचिन्हित पूर्णांक पंचांगp, अचिन्हित पूर्णांक ptr);
व्योम build_get_ptep(u32 **p, अचिन्हित पूर्णांक पंचांगp, अचिन्हित पूर्णांक ptr);
व्योम build_update_entries(u32 **p, अचिन्हित पूर्णांक पंचांगp, अचिन्हित पूर्णांक ptep);
व्योम build_tlb_ग_लिखो_entry(u32 **p, काष्ठा uयंत्र_label **l,
			   काष्ठा uयंत्र_reloc **r,
			   क्रमागत tlb_ग_लिखो_entry wmode);

बाह्य व्योम handle_tlbl(व्योम);
बाह्य अक्षर handle_tlbl_end[];

बाह्य व्योम handle_tlbs(व्योम);
बाह्य अक्षर handle_tlbs_end[];

बाह्य व्योम handle_tlbm(व्योम);
बाह्य अक्षर handle_tlbm_end[];

#पूर्ण_अगर /* __ASM_TLBEX_H */
