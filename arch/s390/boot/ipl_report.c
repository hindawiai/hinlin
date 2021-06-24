<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/init.h>
#समावेश <linux/प्रकार.स>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/boot_data.h>
#समावेश <uapi/यंत्र/ipl.h>
#समावेश "boot.h"

पूर्णांक __bootdata_preserved(ipl_secure_flag);

अचिन्हित दीर्घ __bootdata_preserved(ipl_cert_list_addr);
अचिन्हित दीर्घ __bootdata_preserved(ipl_cert_list_size);

अचिन्हित दीर्घ __bootdata(early_ipl_comp_list_addr);
अचिन्हित दीर्घ __bootdata(early_ipl_comp_list_size);

#घोषणा क्रम_each_rb_entry(entry, rb) \
	क्रम (entry = rb->entries; \
	     (व्योम *) entry + माप(*entry) <= (व्योम *) rb + rb->len; \
	     entry++)

अटल अंतरभूत bool पूर्णांकersects(अचिन्हित दीर्घ addr0, अचिन्हित दीर्घ size0,
			      अचिन्हित दीर्घ addr1, अचिन्हित दीर्घ size1)
अणु
	वापस addr0 + size0 > addr1 && addr1 + size1 > addr0;
पूर्ण

अटल अचिन्हित दीर्घ find_bootdata_space(काष्ठा ipl_rb_components *comps,
					 काष्ठा ipl_rb_certअगरicates *certs,
					 अचिन्हित दीर्घ safe_addr)
अणु
	काष्ठा ipl_rb_certअगरicate_entry *cert;
	काष्ठा ipl_rb_component_entry *comp;
	माप_प्रकार size;

	/*
	 * Find the length क्रम the IPL report boot data
	 */
	early_ipl_comp_list_size = 0;
	क्रम_each_rb_entry(comp, comps)
		early_ipl_comp_list_size += माप(*comp);
	ipl_cert_list_size = 0;
	क्रम_each_rb_entry(cert, certs)
		ipl_cert_list_size += माप(अचिन्हित पूर्णांक) + cert->len;
	size = ipl_cert_list_size + early_ipl_comp_list_size;

	/*
	 * Start from safe_addr to find a मुक्त memory area large
	 * enough क्रम the IPL report boot data. This area is used
	 * क्रम ipl_cert_list_addr/ipl_cert_list_size and
	 * early_ipl_comp_list_addr/early_ipl_comp_list_size. It must
	 * not overlap with any component or any certअगरicate.
	 */
repeat:
	अगर (IS_ENABLED(CONFIG_BLK_DEV_INITRD) && INITRD_START && INITRD_SIZE &&
	    पूर्णांकersects(INITRD_START, INITRD_SIZE, safe_addr, size))
		safe_addr = INITRD_START + INITRD_SIZE;
	क्रम_each_rb_entry(comp, comps)
		अगर (पूर्णांकersects(safe_addr, size, comp->addr, comp->len)) अणु
			safe_addr = comp->addr + comp->len;
			जाओ repeat;
		पूर्ण
	क्रम_each_rb_entry(cert, certs)
		अगर (पूर्णांकersects(safe_addr, size, cert->addr, cert->len)) अणु
			safe_addr = cert->addr + cert->len;
			जाओ repeat;
		पूर्ण
	early_ipl_comp_list_addr = safe_addr;
	ipl_cert_list_addr = safe_addr + early_ipl_comp_list_size;

	वापस safe_addr + size;
पूर्ण

अटल व्योम copy_components_bootdata(काष्ठा ipl_rb_components *comps)
अणु
	काष्ठा ipl_rb_component_entry *comp, *ptr;

	ptr = (काष्ठा ipl_rb_component_entry *) early_ipl_comp_list_addr;
	क्रम_each_rb_entry(comp, comps)
		स_नकल(ptr++, comp, माप(*ptr));
पूर्ण

अटल व्योम copy_certअगरicates_bootdata(काष्ठा ipl_rb_certअगरicates *certs)
अणु
	काष्ठा ipl_rb_certअगरicate_entry *cert;
	व्योम *ptr;

	ptr = (व्योम *) ipl_cert_list_addr;
	क्रम_each_rb_entry(cert, certs) अणु
		*(अचिन्हित पूर्णांक *) ptr = cert->len;
		ptr += माप(अचिन्हित पूर्णांक);
		स_नकल(ptr, (व्योम *) cert->addr, cert->len);
		ptr += cert->len;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ पढ़ो_ipl_report(अचिन्हित दीर्घ safe_addr)
अणु
	काष्ठा ipl_rb_certअगरicates *certs;
	काष्ठा ipl_rb_components *comps;
	काष्ठा ipl_pl_hdr *pl_hdr;
	काष्ठा ipl_rl_hdr *rl_hdr;
	काष्ठा ipl_rb_hdr *rb_hdr;
	अचिन्हित दीर्घ पंचांगp;
	व्योम *rl_end;

	/*
	 * Check अगर there is a IPL report by looking at the copy
	 * of the IPL parameter inक्रमmation block.
	 */
	अगर (!ipl_block_valid ||
	    !(ipl_block.hdr.flags & IPL_PL_FLAG_IPLSR))
		वापस safe_addr;
	ipl_secure_flag = !!(ipl_block.hdr.flags & IPL_PL_FLAG_SIPL);
	/*
	 * There is an IPL report, to find it load the poपूर्णांकer to the
	 * IPL parameter inक्रमmation block from lowcore and skip past
	 * the IPL parameter list, then align the address to a द्विगुन
	 * word boundary.
	 */
	पंचांगp = (अचिन्हित दीर्घ) S390_lowcore.ipl_parmblock_ptr;
	pl_hdr = (काष्ठा ipl_pl_hdr *) पंचांगp;
	पंचांगp = (पंचांगp + pl_hdr->len + 7) & -8UL;
	rl_hdr = (काष्ठा ipl_rl_hdr *) पंचांगp;
	/* Walk through the IPL report blocks in the IPL Report list */
	certs = शून्य;
	comps = शून्य;
	rl_end = (व्योम *) rl_hdr + rl_hdr->len;
	rb_hdr = (व्योम *) rl_hdr + माप(*rl_hdr);
	जबतक ((व्योम *) rb_hdr + माप(*rb_hdr) < rl_end &&
	       (व्योम *) rb_hdr + rb_hdr->len <= rl_end) अणु

		चयन (rb_hdr->rbt) अणु
		हाल IPL_RBT_CERTIFICATES:
			certs = (काष्ठा ipl_rb_certअगरicates *) rb_hdr;
			अवरोध;
		हाल IPL_RBT_COMPONENTS:
			comps = (काष्ठा ipl_rb_components *) rb_hdr;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		rb_hdr = (व्योम *) rb_hdr + rb_hdr->len;
	पूर्ण

	/*
	 * With either the component list or the certअगरicate list
	 * missing the kernel will stay ignorant of secure IPL.
	 */
	अगर (!comps || !certs)
		वापस safe_addr;

	/*
	 * Copy component and certअगरicate list to a safe area
	 * where the decompressed kernel can find them.
	 */
	safe_addr = find_bootdata_space(comps, certs, safe_addr);
	copy_components_bootdata(comps);
	copy_certअगरicates_bootdata(certs);

	वापस safe_addr;
पूर्ण
