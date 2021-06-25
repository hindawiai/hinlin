<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AMD Encrypted Register State Support
 *
 * Author: Joerg Roedel <jroedel@suse.de>
 */

/*
 * misc.h needs to be first because it knows how to include the other kernel
 * headers in the pre-decompression code in a way that करोes not अवरोध
 * compilation.
 */
#समावेश "misc.h"

#समावेश <यंत्र/pgtable_types.h>
#समावेश <यंत्र/sev.h>
#समावेश <यंत्र/trapnr.h>
#समावेश <यंत्र/trap_pf.h>
#समावेश <यंत्र/msr-index.h>
#समावेश <यंत्र/fpu/xcr.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/svm.h>

#समावेश "error.h"

काष्ठा ghcb boot_ghcb_page __aligned(PAGE_SIZE);
काष्ठा ghcb *boot_ghcb;

/*
 * Copy a version of this function here - insn-eval.c can't be used in
 * pre-decompression code.
 */
अटल bool insn_has_rep_prefix(काष्ठा insn *insn)
अणु
	insn_byte_t p;
	पूर्णांक i;

	insn_get_prefixes(insn);

	क्रम_each_insn_prefix(insn, i, p) अणु
		अगर (p == 0xf2 || p == 0xf3)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Only a dummy क्रम insn_get_seg_base() - Early boot-code is 64bit only and
 * करोesn't use segments.
 */
अटल अचिन्हित दीर्घ insn_get_seg_base(काष्ठा pt_regs *regs, पूर्णांक seg_reg_idx)
अणु
	वापस 0UL;
पूर्ण

अटल अंतरभूत u64 sev_es_rd_ghcb_msr(व्योम)
अणु
	अचिन्हित दीर्घ low, high;

	यंत्र अस्थिर("rdmsr" : "=a" (low), "=d" (high) :
			"c" (MSR_AMD64_SEV_ES_GHCB));

	वापस ((high << 32) | low);
पूर्ण

अटल अंतरभूत व्योम sev_es_wr_ghcb_msr(u64 val)
अणु
	u32 low, high;

	low  = val & 0xffffffffUL;
	high = val >> 32;

	यंत्र अस्थिर("wrmsr" : : "c" (MSR_AMD64_SEV_ES_GHCB),
			"a"(low), "d" (high) : "memory");
पूर्ण

अटल क्रमागत es_result vc_decode_insn(काष्ठा es_em_ctxt *ctxt)
अणु
	अक्षर buffer[MAX_INSN_SIZE];
	पूर्णांक ret;

	स_नकल(buffer, (अचिन्हित अक्षर *)ctxt->regs->ip, MAX_INSN_SIZE);

	ret = insn_decode(&ctxt->insn, buffer, MAX_INSN_SIZE, INSN_MODE_64);
	अगर (ret < 0)
		वापस ES_DECODE_FAILED;

	वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_ग_लिखो_mem(काष्ठा es_em_ctxt *ctxt,
				   व्योम *dst, अक्षर *buf, माप_प्रकार size)
अणु
	स_नकल(dst, buf, size);

	वापस ES_OK;
पूर्ण

अटल क्रमागत es_result vc_पढ़ो_mem(काष्ठा es_em_ctxt *ctxt,
				  व्योम *src, अक्षर *buf, माप_प्रकार size)
अणु
	स_नकल(buf, src, size);

	वापस ES_OK;
पूर्ण

#अघोषित __init
#अघोषित __pa
#घोषणा __init
#घोषणा __pa(x)	((अचिन्हित दीर्घ)(x))

#घोषणा __BOOT_COMPRESSED

/* Basic inकाष्ठाion decoding support needed */
#समावेश "../../lib/inat.c"
#समावेश "../../lib/insn.c"

/* Include code क्रम early handlers */
#समावेश "../../kernel/sev-shared.c"

अटल bool early_setup_sev_es(व्योम)
अणु
	अगर (!sev_es_negotiate_protocol())
		sev_es_terminate(GHCB_SEV_ES_REASON_PROTOCOL_UNSUPPORTED);

	अगर (set_page_decrypted((अचिन्हित दीर्घ)&boot_ghcb_page))
		वापस false;

	/* Page is now mapped decrypted, clear it */
	स_रखो(&boot_ghcb_page, 0, माप(boot_ghcb_page));

	boot_ghcb = &boot_ghcb_page;

	/* Initialize lookup tables क्रम the inकाष्ठाion decoder */
	inat_init_tables();

	वापस true;
पूर्ण

व्योम sev_es_shutकरोwn_ghcb(व्योम)
अणु
	अगर (!boot_ghcb)
		वापस;

	अगर (!sev_es_check_cpu_features())
		error("SEV-ES CPU Features missing.");

	/*
	 * GHCB Page must be flushed from the cache and mapped encrypted again.
	 * Otherwise the running kernel will see strange cache effects when
	 * trying to use that page.
	 */
	अगर (set_page_encrypted((अचिन्हित दीर्घ)&boot_ghcb_page))
		error("Can't map GHCB page encrypted");

	/*
	 * GHCB page is mapped encrypted again and flushed from the cache.
	 * Mark it non-present now to catch bugs when #VC exceptions trigger
	 * after this poपूर्णांक.
	 */
	अगर (set_page_non_present((अचिन्हित दीर्घ)&boot_ghcb_page))
		error("Can't unmap GHCB page");
पूर्ण

bool sev_es_check_ghcb_fault(अचिन्हित दीर्घ address)
अणु
	/* Check whether the fault was on the GHCB page */
	वापस ((address & PAGE_MASK) == (अचिन्हित दीर्घ)&boot_ghcb_page);
पूर्ण

व्योम करो_boot_stage2_vc(काष्ठा pt_regs *regs, अचिन्हित दीर्घ निकास_code)
अणु
	काष्ठा es_em_ctxt ctxt;
	क्रमागत es_result result;

	अगर (!boot_ghcb && !early_setup_sev_es())
		sev_es_terminate(GHCB_SEV_ES_REASON_GENERAL_REQUEST);

	vc_ghcb_invalidate(boot_ghcb);
	result = vc_init_em_ctxt(&ctxt, regs, निकास_code);
	अगर (result != ES_OK)
		जाओ finish;

	चयन (निकास_code) अणु
	हाल SVM_EXIT_RDTSC:
	हाल SVM_EXIT_RDTSCP:
		result = vc_handle_rdtsc(boot_ghcb, &ctxt, निकास_code);
		अवरोध;
	हाल SVM_EXIT_IOIO:
		result = vc_handle_ioio(boot_ghcb, &ctxt);
		अवरोध;
	हाल SVM_EXIT_CPUID:
		result = vc_handle_cpuid(boot_ghcb, &ctxt);
		अवरोध;
	शेष:
		result = ES_UNSUPPORTED;
		अवरोध;
	पूर्ण

finish:
	अगर (result == ES_OK)
		vc_finish_insn(&ctxt);
	अन्यथा अगर (result != ES_RETRY)
		sev_es_terminate(GHCB_SEV_ES_REASON_GENERAL_REQUEST);
पूर्ण
