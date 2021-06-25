<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kvm nested भवization support क्रम s390x
 *
 * Copyright IBM Corp. 2016, 2018
 *
 *    Author(s): David Hildenbअक्रम <dahi@linux.vnet.ibm.com>
 */
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/bug.h>
#समावेश <linux/list.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/gmap.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/dis.h>
#समावेश <यंत्र/fpu/api.h>
#समावेश "kvm-s390.h"
#समावेश "gaccess.h"

काष्ठा vsie_page अणु
	काष्ठा kvm_s390_sie_block scb_s;	/* 0x0000 */
	/*
	 * the backup info क्रम machine check. ensure it's at
	 * the same offset as that in काष्ठा sie_page!
	 */
	काष्ठा mcck_अस्थिर_info mcck_info;    /* 0x0200 */
	/*
	 * The pinned original scb. Be aware that other VCPUs can modअगरy
	 * it जबतक we पढ़ो from it. Values that are used क्रम conditions or
	 * are reused conditionally, should be accessed via READ_ONCE.
	 */
	काष्ठा kvm_s390_sie_block *scb_o;	/* 0x0218 */
	/* the shaकरोw gmap in use by the vsie_page */
	काष्ठा gmap *gmap;			/* 0x0220 */
	/* address of the last reported fault to guest2 */
	अचिन्हित दीर्घ fault_addr;		/* 0x0228 */
	/* calculated guest addresses of satellite control blocks */
	gpa_t sca_gpa;				/* 0x0230 */
	gpa_t itdba_gpa;			/* 0x0238 */
	gpa_t gvrd_gpa;				/* 0x0240 */
	gpa_t riccbd_gpa;			/* 0x0248 */
	gpa_t sdnx_gpa;				/* 0x0250 */
	__u8 reserved[0x0700 - 0x0258];		/* 0x0258 */
	काष्ठा kvm_s390_crypto_cb crycb;	/* 0x0700 */
	__u8 fac[S390_ARCH_FAC_LIST_SIZE_BYTE];	/* 0x0800 */
पूर्ण;

/* trigger a validity icpt क्रम the given scb */
अटल पूर्णांक set_validity_icpt(काष्ठा kvm_s390_sie_block *scb,
			     __u16 reason_code)
अणु
	scb->ipa = 0x1000;
	scb->ipb = ((__u32) reason_code) << 16;
	scb->icptcode = ICPT_VALIDITY;
	वापस 1;
पूर्ण

/* mark the prefix as unmapped, this will block the VSIE */
अटल व्योम prefix_unmapped(काष्ठा vsie_page *vsie_page)
अणु
	atomic_or(PROG_REQUEST, &vsie_page->scb_s.prog20);
पूर्ण

/* mark the prefix as unmapped and रुको until the VSIE has been left */
अटल व्योम prefix_unmapped_sync(काष्ठा vsie_page *vsie_page)
अणु
	prefix_unmapped(vsie_page);
	अगर (vsie_page->scb_s.prog0c & PROG_IN_SIE)
		atomic_or(CPUSTAT_STOP_INT, &vsie_page->scb_s.cpuflags);
	जबतक (vsie_page->scb_s.prog0c & PROG_IN_SIE)
		cpu_relax();
पूर्ण

/* mark the prefix as mapped, this will allow the VSIE to run */
अटल व्योम prefix_mapped(काष्ठा vsie_page *vsie_page)
अणु
	atomic_andnot(PROG_REQUEST, &vsie_page->scb_s.prog20);
पूर्ण

/* test अगर the prefix is mapped पूर्णांकo the gmap shaकरोw */
अटल पूर्णांक prefix_is_mapped(काष्ठा vsie_page *vsie_page)
अणु
	वापस !(atomic_पढ़ो(&vsie_page->scb_s.prog20) & PROG_REQUEST);
पूर्ण

/* copy the updated पूर्णांकervention request bits पूर्णांकo the shaकरोw scb */
अटल व्योम update_पूर्णांकervention_requests(काष्ठा vsie_page *vsie_page)
अणु
	स्थिर पूर्णांक bits = CPUSTAT_STOP_INT | CPUSTAT_IO_INT | CPUSTAT_EXT_INT;
	पूर्णांक cpuflags;

	cpuflags = atomic_पढ़ो(&vsie_page->scb_o->cpuflags);
	atomic_andnot(bits, &vsie_page->scb_s.cpuflags);
	atomic_or(cpuflags & bits, &vsie_page->scb_s.cpuflags);
पूर्ण

/* shaकरोw (filter and validate) the cpuflags  */
अटल पूर्णांक prepare_cpuflags(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	काष्ठा kvm_s390_sie_block *scb_o = vsie_page->scb_o;
	पूर्णांक newflags, cpuflags = atomic_पढ़ो(&scb_o->cpuflags);

	/* we करोn't allow ESA/390 guests */
	अगर (!(cpuflags & CPUSTAT_ZARCH))
		वापस set_validity_icpt(scb_s, 0x0001U);

	अगर (cpuflags & (CPUSTAT_RRF | CPUSTAT_MCDS))
		वापस set_validity_icpt(scb_s, 0x0001U);
	अन्यथा अगर (cpuflags & (CPUSTAT_SLSV | CPUSTAT_SLSR))
		वापस set_validity_icpt(scb_s, 0x0007U);

	/* पूर्णांकervention requests will be set later */
	newflags = CPUSTAT_ZARCH;
	अगर (cpuflags & CPUSTAT_GED && test_kvm_facility(vcpu->kvm, 8))
		newflags |= CPUSTAT_GED;
	अगर (cpuflags & CPUSTAT_GED2 && test_kvm_facility(vcpu->kvm, 78)) अणु
		अगर (cpuflags & CPUSTAT_GED)
			वापस set_validity_icpt(scb_s, 0x0001U);
		newflags |= CPUSTAT_GED2;
	पूर्ण
	अगर (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_GPERE))
		newflags |= cpuflags & CPUSTAT_P;
	अगर (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_GSLS))
		newflags |= cpuflags & CPUSTAT_SM;
	अगर (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_IBS))
		newflags |= cpuflags & CPUSTAT_IBS;
	अगर (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_KSS))
		newflags |= cpuflags & CPUSTAT_KSS;

	atomic_set(&scb_s->cpuflags, newflags);
	वापस 0;
पूर्ण
/* Copy to APCB FORMAT1 from APCB FORMAT0 */
अटल पूर्णांक setup_apcb10(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_apcb1 *apcb_s,
			अचिन्हित दीर्घ apcb_o, काष्ठा kvm_s390_apcb1 *apcb_h)
अणु
	काष्ठा kvm_s390_apcb0 पंचांगp;

	अगर (पढ़ो_guest_real(vcpu, apcb_o, &पंचांगp, माप(काष्ठा kvm_s390_apcb0)))
		वापस -EFAULT;

	apcb_s->apm[0] = apcb_h->apm[0] & पंचांगp.apm[0];
	apcb_s->aqm[0] = apcb_h->aqm[0] & पंचांगp.aqm[0] & 0xffff000000000000UL;
	apcb_s->adm[0] = apcb_h->adm[0] & पंचांगp.adm[0] & 0xffff000000000000UL;

	वापस 0;

पूर्ण

/**
 * setup_apcb00 - Copy to APCB FORMAT0 from APCB FORMAT0
 * @vcpu: poपूर्णांकer to the भव CPU
 * @apcb_s: poपूर्णांकer to start of apcb in the shaकरोw crycb
 * @apcb_o: poपूर्णांकer to start of original apcb in the guest2
 * @apcb_h: poपूर्णांकer to start of apcb in the guest1
 *
 * Returns 0 and -EFAULT on error पढ़ोing guest apcb
 */
अटल पूर्णांक setup_apcb00(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ *apcb_s,
			अचिन्हित दीर्घ apcb_o, अचिन्हित दीर्घ *apcb_h)
अणु
	अगर (पढ़ो_guest_real(vcpu, apcb_o, apcb_s,
			    माप(काष्ठा kvm_s390_apcb0)))
		वापस -EFAULT;

	biपंचांगap_and(apcb_s, apcb_s, apcb_h, माप(काष्ठा kvm_s390_apcb0));

	वापस 0;
पूर्ण

/**
 * setup_apcb11 - Copy the FORMAT1 APCB from the guest to the shaकरोw CRYCB
 * @vcpu: poपूर्णांकer to the भव CPU
 * @apcb_s: poपूर्णांकer to start of apcb in the shaकरोw crycb
 * @apcb_o: poपूर्णांकer to start of original guest apcb
 * @apcb_h: poपूर्णांकer to start of apcb in the host
 *
 * Returns 0 and -EFAULT on error पढ़ोing guest apcb
 */
अटल पूर्णांक setup_apcb11(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ *apcb_s,
			अचिन्हित दीर्घ apcb_o,
			अचिन्हित दीर्घ *apcb_h)
अणु
	अगर (पढ़ो_guest_real(vcpu, apcb_o, apcb_s,
			    माप(काष्ठा kvm_s390_apcb1)))
		वापस -EFAULT;

	biपंचांगap_and(apcb_s, apcb_s, apcb_h, माप(काष्ठा kvm_s390_apcb1));

	वापस 0;
पूर्ण

/**
 * setup_apcb - Create a shaकरोw copy of the apcb.
 * @vcpu: poपूर्णांकer to the भव CPU
 * @crycb_s: poपूर्णांकer to shaकरोw crycb
 * @crycb_o: poपूर्णांकer to original guest crycb
 * @crycb_h: poपूर्णांकer to the host crycb
 * @fmt_o: क्रमmat of the original guest crycb.
 * @fmt_h: क्रमmat of the host crycb.
 *
 * Checks the compatibility between the guest and host crycb and calls the
 * appropriate copy function.
 *
 * Return 0 or an error number अगर the guest and host crycb are incompatible.
 */
अटल पूर्णांक setup_apcb(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_s390_crypto_cb *crycb_s,
	       स्थिर u32 crycb_o,
	       काष्ठा kvm_s390_crypto_cb *crycb_h,
	       पूर्णांक fmt_o, पूर्णांक fmt_h)
अणु
	काष्ठा kvm_s390_crypto_cb *crycb;

	crycb = (काष्ठा kvm_s390_crypto_cb *) (अचिन्हित दीर्घ)crycb_o;

	चयन (fmt_o) अणु
	हाल CRYCB_FORMAT2:
		अगर ((crycb_o & PAGE_MASK) != ((crycb_o + 256) & PAGE_MASK))
			वापस -EACCES;
		अगर (fmt_h != CRYCB_FORMAT2)
			वापस -EINVAL;
		वापस setup_apcb11(vcpu, (अचिन्हित दीर्घ *)&crycb_s->apcb1,
				    (अचिन्हित दीर्घ) &crycb->apcb1,
				    (अचिन्हित दीर्घ *)&crycb_h->apcb1);
	हाल CRYCB_FORMAT1:
		चयन (fmt_h) अणु
		हाल CRYCB_FORMAT2:
			वापस setup_apcb10(vcpu, &crycb_s->apcb1,
					    (अचिन्हित दीर्घ) &crycb->apcb0,
					    &crycb_h->apcb1);
		हाल CRYCB_FORMAT1:
			वापस setup_apcb00(vcpu,
					    (अचिन्हित दीर्घ *) &crycb_s->apcb0,
					    (अचिन्हित दीर्घ) &crycb->apcb0,
					    (अचिन्हित दीर्घ *) &crycb_h->apcb0);
		पूर्ण
		अवरोध;
	हाल CRYCB_FORMAT0:
		अगर ((crycb_o & PAGE_MASK) != ((crycb_o + 32) & PAGE_MASK))
			वापस -EACCES;

		चयन (fmt_h) अणु
		हाल CRYCB_FORMAT2:
			वापस setup_apcb10(vcpu, &crycb_s->apcb1,
					    (अचिन्हित दीर्घ) &crycb->apcb0,
					    &crycb_h->apcb1);
		हाल CRYCB_FORMAT1:
		हाल CRYCB_FORMAT0:
			वापस setup_apcb00(vcpu,
					    (अचिन्हित दीर्घ *) &crycb_s->apcb0,
					    (अचिन्हित दीर्घ) &crycb->apcb0,
					    (अचिन्हित दीर्घ *) &crycb_h->apcb0);
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * shaकरोw_crycb - Create a shaकरोw copy of the crycb block
 * @vcpu: a poपूर्णांकer to the भव CPU
 * @vsie_page: a poपूर्णांकer to पूर्णांकernal date used क्रम the vSIE
 *
 * Create a shaकरोw copy of the crycb block and setup key wrapping, अगर
 * requested क्रम guest 3 and enabled क्रम guest 2.
 *
 * We accept क्रमmat-1 or क्रमmat-2, but we convert क्रमmat-1 पूर्णांकo क्रमmat-2
 * in the shaकरोw CRYCB.
 * Using क्रमmat-2 enables the firmware to choose the right क्रमmat when
 * scheduling the SIE.
 * There is nothing to करो क्रम क्रमmat-0.
 *
 * This function centralize the issuing of set_validity_icpt() क्रम all
 * the subfunctions working on the crycb.
 *
 * Returns: - 0 अगर shaकरोwed or nothing to करो
 *          - > 0 अगर control has to be given to guest 2
 */
अटल पूर्णांक shaकरोw_crycb(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	काष्ठा kvm_s390_sie_block *scb_o = vsie_page->scb_o;
	स्थिर uपूर्णांक32_t crycbd_o = READ_ONCE(scb_o->crycbd);
	स्थिर u32 crycb_addr = crycbd_o & 0x7ffffff8U;
	अचिन्हित दीर्घ *b1, *b2;
	u8 ecb3_flags;
	u32 ecd_flags;
	पूर्णांक apie_h;
	पूर्णांक apie_s;
	पूर्णांक key_msk = test_kvm_facility(vcpu->kvm, 76);
	पूर्णांक fmt_o = crycbd_o & CRYCB_FORMAT_MASK;
	पूर्णांक fmt_h = vcpu->arch.sie_block->crycbd & CRYCB_FORMAT_MASK;
	पूर्णांक ret = 0;

	scb_s->crycbd = 0;

	apie_h = vcpu->arch.sie_block->eca & ECA_APIE;
	apie_s = apie_h & scb_o->eca;
	अगर (!apie_s && (!key_msk || (fmt_o == CRYCB_FORMAT0)))
		वापस 0;

	अगर (!crycb_addr)
		वापस set_validity_icpt(scb_s, 0x0039U);

	अगर (fmt_o == CRYCB_FORMAT1)
		अगर ((crycb_addr & PAGE_MASK) !=
		    ((crycb_addr + 128) & PAGE_MASK))
			वापस set_validity_icpt(scb_s, 0x003CU);

	अगर (apie_s) अणु
		ret = setup_apcb(vcpu, &vsie_page->crycb, crycb_addr,
				 vcpu->kvm->arch.crypto.crycb,
				 fmt_o, fmt_h);
		अगर (ret)
			जाओ end;
		scb_s->eca |= scb_o->eca & ECA_APIE;
	पूर्ण

	/* we may only allow it अगर enabled क्रम guest 2 */
	ecb3_flags = scb_o->ecb3 & vcpu->arch.sie_block->ecb3 &
		     (ECB3_AES | ECB3_DEA);
	ecd_flags = scb_o->ecd & vcpu->arch.sie_block->ecd & ECD_ECC;
	अगर (!ecb3_flags && !ecd_flags)
		जाओ end;

	/* copy only the wrapping keys */
	अगर (पढ़ो_guest_real(vcpu, crycb_addr + 72,
			    vsie_page->crycb.dea_wrapping_key_mask, 56))
		वापस set_validity_icpt(scb_s, 0x0035U);

	scb_s->ecb3 |= ecb3_flags;
	scb_s->ecd |= ecd_flags;

	/* xor both blocks in one run */
	b1 = (अचिन्हित दीर्घ *) vsie_page->crycb.dea_wrapping_key_mask;
	b2 = (अचिन्हित दीर्घ *)
			    vcpu->kvm->arch.crypto.crycb->dea_wrapping_key_mask;
	/* as 56%8 == 0, biपंचांगap_xor won't overग_लिखो any data */
	biपंचांगap_xor(b1, b1, b2, BITS_PER_BYTE * 56);
end:
	चयन (ret) अणु
	हाल -EINVAL:
		वापस set_validity_icpt(scb_s, 0x0022U);
	हाल -EFAULT:
		वापस set_validity_icpt(scb_s, 0x0035U);
	हाल -EACCES:
		वापस set_validity_icpt(scb_s, 0x003CU);
	पूर्ण
	scb_s->crycbd = ((__u32)(__u64) &vsie_page->crycb) | CRYCB_FORMAT2;
	वापस 0;
पूर्ण

/* shaकरोw (round up/करोwn) the ibc to aव्योम validity icpt */
अटल व्योम prepare_ibc(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	काष्ठा kvm_s390_sie_block *scb_o = vsie_page->scb_o;
	/* READ_ONCE करोes not work on bitfields - use a temporary variable */
	स्थिर uपूर्णांक32_t __new_ibc = scb_o->ibc;
	स्थिर uपूर्णांक32_t new_ibc = READ_ONCE(__new_ibc) & 0x0fffU;
	__u64 min_ibc = (sclp.ibc >> 16) & 0x0fffU;

	scb_s->ibc = 0;
	/* ibc installed in g2 and requested क्रम g3 */
	अगर (vcpu->kvm->arch.model.ibc && new_ibc) अणु
		scb_s->ibc = new_ibc;
		/* takte care of the minimum ibc level of the machine */
		अगर (scb_s->ibc < min_ibc)
			scb_s->ibc = min_ibc;
		/* take care of the maximum ibc level set क्रम the guest */
		अगर (scb_s->ibc > vcpu->kvm->arch.model.ibc)
			scb_s->ibc = vcpu->kvm->arch.model.ibc;
	पूर्ण
पूर्ण

/* unshaकरोw the scb, copying parameters back to the real scb */
अटल व्योम unshaकरोw_scb(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	काष्ठा kvm_s390_sie_block *scb_o = vsie_page->scb_o;

	/* पूर्णांकerception */
	scb_o->icptcode = scb_s->icptcode;
	scb_o->icptstatus = scb_s->icptstatus;
	scb_o->ipa = scb_s->ipa;
	scb_o->ipb = scb_s->ipb;
	scb_o->gbea = scb_s->gbea;

	/* समयr */
	scb_o->cpuपंचांग = scb_s->cpuपंचांग;
	scb_o->ckc = scb_s->ckc;
	scb_o->todpr = scb_s->todpr;

	/* guest state */
	scb_o->gpsw = scb_s->gpsw;
	scb_o->gg14 = scb_s->gg14;
	scb_o->gg15 = scb_s->gg15;
	स_नकल(scb_o->gcr, scb_s->gcr, 128);
	scb_o->pp = scb_s->pp;

	/* branch prediction */
	अगर (test_kvm_facility(vcpu->kvm, 82)) अणु
		scb_o->fpf &= ~FPF_BPBC;
		scb_o->fpf |= scb_s->fpf & FPF_BPBC;
	पूर्ण

	/* पूर्णांकerrupt पूर्णांकercept */
	चयन (scb_s->icptcode) अणु
	हाल ICPT_PROGI:
	हाल ICPT_INSTPROGI:
	हाल ICPT_EXTINT:
		स_नकल((व्योम *)((u64)scb_o + 0xc0),
		       (व्योम *)((u64)scb_s + 0xc0), 0xf0 - 0xc0);
		अवरोध;
	पूर्ण

	अगर (scb_s->ihcpu != 0xffffU)
		scb_o->ihcpu = scb_s->ihcpu;
पूर्ण

/*
 * Setup the shaकरोw scb by copying and checking the relevant parts of the g2
 * provided scb.
 *
 * Returns: - 0 अगर the scb has been shaकरोwed
 *          - > 0 अगर control has to be given to guest 2
 */
अटल पूर्णांक shaकरोw_scb(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_o = vsie_page->scb_o;
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	/* READ_ONCE करोes not work on bitfields - use a temporary variable */
	स्थिर uपूर्णांक32_t __new_prefix = scb_o->prefix;
	स्थिर uपूर्णांक32_t new_prefix = READ_ONCE(__new_prefix);
	स्थिर bool wants_tx = READ_ONCE(scb_o->ecb) & ECB_TE;
	bool had_tx = scb_s->ecb & ECB_TE;
	अचिन्हित दीर्घ new_mso = 0;
	पूर्णांक rc;

	/* make sure we करोn't have any leftovers when reusing the scb */
	scb_s->icptcode = 0;
	scb_s->eca = 0;
	scb_s->ecb = 0;
	scb_s->ecb2 = 0;
	scb_s->ecb3 = 0;
	scb_s->ecd = 0;
	scb_s->fac = 0;
	scb_s->fpf = 0;

	rc = prepare_cpuflags(vcpu, vsie_page);
	अगर (rc)
		जाओ out;

	/* समयr */
	scb_s->cpuपंचांग = scb_o->cpuपंचांग;
	scb_s->ckc = scb_o->ckc;
	scb_s->todpr = scb_o->todpr;
	scb_s->epoch = scb_o->epoch;

	/* guest state */
	scb_s->gpsw = scb_o->gpsw;
	scb_s->gg14 = scb_o->gg14;
	scb_s->gg15 = scb_o->gg15;
	स_नकल(scb_s->gcr, scb_o->gcr, 128);
	scb_s->pp = scb_o->pp;

	/* पूर्णांकerception / execution handling */
	scb_s->gbea = scb_o->gbea;
	scb_s->lctl = scb_o->lctl;
	scb_s->svcc = scb_o->svcc;
	scb_s->ictl = scb_o->ictl;
	/*
	 * SKEY handling functions can't deal with false setting of PTE invalid
	 * bits. Thereक्रमe we cannot provide पूर्णांकerpretation and would later
	 * have to provide own emulation handlers.
	 */
	अगर (!(atomic_पढ़ो(&scb_s->cpuflags) & CPUSTAT_KSS))
		scb_s->ictl |= ICTL_ISKE | ICTL_SSKE | ICTL_RRBE;

	scb_s->icpua = scb_o->icpua;

	अगर (!(atomic_पढ़ो(&scb_s->cpuflags) & CPUSTAT_SM))
		new_mso = READ_ONCE(scb_o->mso) & 0xfffffffffff00000UL;
	/* अगर the hva of the prefix changes, we have to remap the prefix */
	अगर (scb_s->mso != new_mso || scb_s->prefix != new_prefix)
		prefix_unmapped(vsie_page);
	 /* SIE will करो mso/msl validity and exception checks क्रम us */
	scb_s->msl = scb_o->msl & 0xfffffffffff00000UL;
	scb_s->mso = new_mso;
	scb_s->prefix = new_prefix;

	/* We have to definetly flush the tlb अगर this scb never ran */
	अगर (scb_s->ihcpu != 0xffffU)
		scb_s->ihcpu = scb_o->ihcpu;

	/* MVPG and Protection Exception Interpretation are always available */
	scb_s->eca |= scb_o->eca & (ECA_MVPGI | ECA_PROTEXCI);
	/* Host-protection-पूर्णांकerruption पूर्णांकroduced with ESOP */
	अगर (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_ESOP))
		scb_s->ecb |= scb_o->ecb & ECB_HOSTPROTINT;
	/* transactional execution */
	अगर (test_kvm_facility(vcpu->kvm, 73) && wants_tx) अणु
		/* remap the prefix is tx is toggled on */
		अगर (!had_tx)
			prefix_unmapped(vsie_page);
		scb_s->ecb |= ECB_TE;
	पूर्ण
	/* branch prediction */
	अगर (test_kvm_facility(vcpu->kvm, 82))
		scb_s->fpf |= scb_o->fpf & FPF_BPBC;
	/* SIMD */
	अगर (test_kvm_facility(vcpu->kvm, 129)) अणु
		scb_s->eca |= scb_o->eca & ECA_VX;
		scb_s->ecd |= scb_o->ecd & ECD_HOSTREGMGMT;
	पूर्ण
	/* Run-समय-Instrumentation */
	अगर (test_kvm_facility(vcpu->kvm, 64))
		scb_s->ecb3 |= scb_o->ecb3 & ECB3_RI;
	/* Inकाष्ठाion Execution Prevention */
	अगर (test_kvm_facility(vcpu->kvm, 130))
		scb_s->ecb2 |= scb_o->ecb2 & ECB2_IEP;
	/* Guarded Storage */
	अगर (test_kvm_facility(vcpu->kvm, 133)) अणु
		scb_s->ecb |= scb_o->ecb & ECB_GS;
		scb_s->ecd |= scb_o->ecd & ECD_HOSTREGMGMT;
	पूर्ण
	अगर (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_SIIF))
		scb_s->eca |= scb_o->eca & ECA_SII;
	अगर (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_IB))
		scb_s->eca |= scb_o->eca & ECA_IB;
	अगर (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_CEI))
		scb_s->eca |= scb_o->eca & ECA_CEI;
	/* Epoch Extension */
	अगर (test_kvm_facility(vcpu->kvm, 139))
		scb_s->ecd |= scb_o->ecd & ECD_MEF;

	/* etoken */
	अगर (test_kvm_facility(vcpu->kvm, 156))
		scb_s->ecd |= scb_o->ecd & ECD_ETOKENF;

	scb_s->hpid = HPID_VSIE;
	scb_s->cpnc = scb_o->cpnc;

	prepare_ibc(vcpu, vsie_page);
	rc = shaकरोw_crycb(vcpu, vsie_page);
out:
	अगर (rc)
		unshaकरोw_scb(vcpu, vsie_page);
	वापस rc;
पूर्ण

व्योम kvm_s390_vsie_gmap_notअगरier(काष्ठा gmap *gmap, अचिन्हित दीर्घ start,
				 अचिन्हित दीर्घ end)
अणु
	काष्ठा kvm *kvm = gmap->निजी;
	काष्ठा vsie_page *cur;
	अचिन्हित दीर्घ prefix;
	काष्ठा page *page;
	पूर्णांक i;

	अगर (!gmap_is_shaकरोw(gmap))
		वापस;
	अगर (start >= 1UL << 31)
		/* We are only पूर्णांकerested in prefix pages */
		वापस;

	/*
	 * Only new shaकरोw blocks are added to the list during runसमय,
	 * thereक्रमe we can safely reference them all the समय.
	 */
	क्रम (i = 0; i < kvm->arch.vsie.page_count; i++) अणु
		page = READ_ONCE(kvm->arch.vsie.pages[i]);
		अगर (!page)
			जारी;
		cur = page_to_virt(page);
		अगर (READ_ONCE(cur->gmap) != gmap)
			जारी;
		prefix = cur->scb_s.prefix << GUEST_PREFIX_SHIFT;
		/* with mso/msl, the prefix lies at an offset */
		prefix += cur->scb_s.mso;
		अगर (prefix <= end && start <= prefix + 2 * PAGE_SIZE - 1)
			prefix_unmapped_sync(cur);
	पूर्ण
पूर्ण

/*
 * Map the first prefix page and अगर tx is enabled also the second prefix page.
 *
 * The prefix will be रक्षित, a gmap notअगरier will inक्रमm about unmaps.
 * The shaकरोw scb must not be executed until the prefix is remapped, this is
 * guaranteed by properly handling PROG_REQUEST.
 *
 * Returns: - 0 on अगर successfully mapped or alपढ़ोy mapped
 *          - > 0 अगर control has to be given to guest 2
 *          - -EAGAIN अगर the caller can retry immediately
 *          - -ENOMEM अगर out of memory
 */
अटल पूर्णांक map_prefix(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	u64 prefix = scb_s->prefix << GUEST_PREFIX_SHIFT;
	पूर्णांक rc;

	अगर (prefix_is_mapped(vsie_page))
		वापस 0;

	/* mark it as mapped so we can catch any concurrent unmappers */
	prefix_mapped(vsie_page);

	/* with mso/msl, the prefix lies at offset *mso* */
	prefix += scb_s->mso;

	rc = kvm_s390_shaकरोw_fault(vcpu, vsie_page->gmap, prefix, शून्य);
	अगर (!rc && (scb_s->ecb & ECB_TE))
		rc = kvm_s390_shaकरोw_fault(vcpu, vsie_page->gmap,
					   prefix + PAGE_SIZE, शून्य);
	/*
	 * We करोn't have to mprotect, we will be called क्रम all unshaकरोws.
	 * SIE will detect अगर protection applies and trigger a validity.
	 */
	अगर (rc)
		prefix_unmapped(vsie_page);
	अगर (rc > 0 || rc == -EFAULT)
		rc = set_validity_icpt(scb_s, 0x0037U);
	वापस rc;
पूर्ण

/*
 * Pin the guest page given by gpa and set hpa to the pinned host address.
 * Will always be pinned writable.
 *
 * Returns: - 0 on success
 *          - -EINVAL अगर the gpa is not valid guest storage
 */
अटल पूर्णांक pin_guest_page(काष्ठा kvm *kvm, gpa_t gpa, hpa_t *hpa)
अणु
	काष्ठा page *page;

	page = gfn_to_page(kvm, gpa_to_gfn(gpa));
	अगर (is_error_page(page))
		वापस -EINVAL;
	*hpa = (hpa_t) page_to_virt(page) + (gpa & ~PAGE_MASK);
	वापस 0;
पूर्ण

/* Unpins a page previously pinned via pin_guest_page, marking it as dirty. */
अटल व्योम unpin_guest_page(काष्ठा kvm *kvm, gpa_t gpa, hpa_t hpa)
अणु
	kvm_release_pfn_dirty(hpa >> PAGE_SHIFT);
	/* mark the page always as dirty क्रम migration */
	mark_page_dirty(kvm, gpa_to_gfn(gpa));
पूर्ण

/* unpin all blocks previously pinned by pin_blocks(), marking them dirty */
अटल व्योम unpin_blocks(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	hpa_t hpa;

	hpa = (u64) scb_s->scaoh << 32 | scb_s->scaol;
	अगर (hpa) अणु
		unpin_guest_page(vcpu->kvm, vsie_page->sca_gpa, hpa);
		vsie_page->sca_gpa = 0;
		scb_s->scaol = 0;
		scb_s->scaoh = 0;
	पूर्ण

	hpa = scb_s->itdba;
	अगर (hpa) अणु
		unpin_guest_page(vcpu->kvm, vsie_page->itdba_gpa, hpa);
		vsie_page->itdba_gpa = 0;
		scb_s->itdba = 0;
	पूर्ण

	hpa = scb_s->gvrd;
	अगर (hpa) अणु
		unpin_guest_page(vcpu->kvm, vsie_page->gvrd_gpa, hpa);
		vsie_page->gvrd_gpa = 0;
		scb_s->gvrd = 0;
	पूर्ण

	hpa = scb_s->riccbd;
	अगर (hpa) अणु
		unpin_guest_page(vcpu->kvm, vsie_page->riccbd_gpa, hpa);
		vsie_page->riccbd_gpa = 0;
		scb_s->riccbd = 0;
	पूर्ण

	hpa = scb_s->sdnxo;
	अगर (hpa) अणु
		unpin_guest_page(vcpu->kvm, vsie_page->sdnx_gpa, hpa);
		vsie_page->sdnx_gpa = 0;
		scb_s->sdnxo = 0;
	पूर्ण
पूर्ण

/*
 * Instead of shaकरोwing some blocks, we can simply क्रमward them because the
 * addresses in the scb are 64 bit दीर्घ.
 *
 * This works as दीर्घ as the data lies in one page. If blocks ever exceed one
 * page, we have to fall back to shaकरोwing.
 *
 * As we reuse the sca, the vcpu poपूर्णांकers contained in it are invalid. We must
 * thereक्रमe not enable any facilities that access these poपूर्णांकers (e.g. SIGPIF).
 *
 * Returns: - 0 अगर all blocks were pinned.
 *          - > 0 अगर control has to be given to guest 2
 *          - -ENOMEM अगर out of memory
 */
अटल पूर्णांक pin_blocks(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_o = vsie_page->scb_o;
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	hpa_t hpa;
	gpa_t gpa;
	पूर्णांक rc = 0;

	gpa = READ_ONCE(scb_o->scaol) & ~0xfUL;
	अगर (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_64BSCAO))
		gpa |= (u64) READ_ONCE(scb_o->scaoh) << 32;
	अगर (gpa) अणु
		अगर (gpa < 2 * PAGE_SIZE)
			rc = set_validity_icpt(scb_s, 0x0038U);
		अन्यथा अगर ((gpa & ~0x1fffUL) == kvm_s390_get_prefix(vcpu))
			rc = set_validity_icpt(scb_s, 0x0011U);
		अन्यथा अगर ((gpa & PAGE_MASK) !=
			 ((gpa + माप(काष्ठा bsca_block) - 1) & PAGE_MASK))
			rc = set_validity_icpt(scb_s, 0x003bU);
		अगर (!rc) अणु
			rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
			अगर (rc)
				rc = set_validity_icpt(scb_s, 0x0034U);
		पूर्ण
		अगर (rc)
			जाओ unpin;
		vsie_page->sca_gpa = gpa;
		scb_s->scaoh = (u32)((u64)hpa >> 32);
		scb_s->scaol = (u32)(u64)hpa;
	पूर्ण

	gpa = READ_ONCE(scb_o->itdba) & ~0xffUL;
	अगर (gpa && (scb_s->ecb & ECB_TE)) अणु
		अगर (gpa < 2 * PAGE_SIZE) अणु
			rc = set_validity_icpt(scb_s, 0x0080U);
			जाओ unpin;
		पूर्ण
		/* 256 bytes cannot cross page boundaries */
		rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		अगर (rc) अणु
			rc = set_validity_icpt(scb_s, 0x0080U);
			जाओ unpin;
		पूर्ण
		vsie_page->itdba_gpa = gpa;
		scb_s->itdba = hpa;
	पूर्ण

	gpa = READ_ONCE(scb_o->gvrd) & ~0x1ffUL;
	अगर (gpa && (scb_s->eca & ECA_VX) && !(scb_s->ecd & ECD_HOSTREGMGMT)) अणु
		अगर (gpa < 2 * PAGE_SIZE) अणु
			rc = set_validity_icpt(scb_s, 0x1310U);
			जाओ unpin;
		पूर्ण
		/*
		 * 512 bytes vector रेजिस्टरs cannot cross page boundaries
		 * अगर this block माला_लो bigger, we have to shaकरोw it.
		 */
		rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		अगर (rc) अणु
			rc = set_validity_icpt(scb_s, 0x1310U);
			जाओ unpin;
		पूर्ण
		vsie_page->gvrd_gpa = gpa;
		scb_s->gvrd = hpa;
	पूर्ण

	gpa = READ_ONCE(scb_o->riccbd) & ~0x3fUL;
	अगर (gpa && (scb_s->ecb3 & ECB3_RI)) अणु
		अगर (gpa < 2 * PAGE_SIZE) अणु
			rc = set_validity_icpt(scb_s, 0x0043U);
			जाओ unpin;
		पूर्ण
		/* 64 bytes cannot cross page boundaries */
		rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		अगर (rc) अणु
			rc = set_validity_icpt(scb_s, 0x0043U);
			जाओ unpin;
		पूर्ण
		/* Validity 0x0044 will be checked by SIE */
		vsie_page->riccbd_gpa = gpa;
		scb_s->riccbd = hpa;
	पूर्ण
	अगर (((scb_s->ecb & ECB_GS) && !(scb_s->ecd & ECD_HOSTREGMGMT)) ||
	    (scb_s->ecd & ECD_ETOKENF)) अणु
		अचिन्हित दीर्घ sdnxc;

		gpa = READ_ONCE(scb_o->sdnxo) & ~0xfUL;
		sdnxc = READ_ONCE(scb_o->sdnxo) & 0xfUL;
		अगर (!gpa || gpa < 2 * PAGE_SIZE) अणु
			rc = set_validity_icpt(scb_s, 0x10b0U);
			जाओ unpin;
		पूर्ण
		अगर (sdnxc < 6 || sdnxc > 12) अणु
			rc = set_validity_icpt(scb_s, 0x10b1U);
			जाओ unpin;
		पूर्ण
		अगर (gpa & ((1 << sdnxc) - 1)) अणु
			rc = set_validity_icpt(scb_s, 0x10b2U);
			जाओ unpin;
		पूर्ण
		/* Due to alignment rules (checked above) this cannot
		 * cross page boundaries
		 */
		rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
		अगर (rc) अणु
			rc = set_validity_icpt(scb_s, 0x10b0U);
			जाओ unpin;
		पूर्ण
		vsie_page->sdnx_gpa = gpa;
		scb_s->sdnxo = hpa | sdnxc;
	पूर्ण
	वापस 0;
unpin:
	unpin_blocks(vcpu, vsie_page);
	वापस rc;
पूर्ण

/* unpin the scb provided by guest 2, marking it as dirty */
अटल व्योम unpin_scb(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page,
		      gpa_t gpa)
अणु
	hpa_t hpa = (hpa_t) vsie_page->scb_o;

	अगर (hpa)
		unpin_guest_page(vcpu->kvm, gpa, hpa);
	vsie_page->scb_o = शून्य;
पूर्ण

/*
 * Pin the scb at gpa provided by guest 2 at vsie_page->scb_o.
 *
 * Returns: - 0 अगर the scb was pinned.
 *          - > 0 अगर control has to be given to guest 2
 */
अटल पूर्णांक pin_scb(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page,
		   gpa_t gpa)
अणु
	hpa_t hpa;
	पूर्णांक rc;

	rc = pin_guest_page(vcpu->kvm, gpa, &hpa);
	अगर (rc) अणु
		rc = kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);
		WARN_ON_ONCE(rc);
		वापस 1;
	पूर्ण
	vsie_page->scb_o = (काष्ठा kvm_s390_sie_block *) hpa;
	वापस 0;
पूर्ण

/*
 * Inject a fault पूर्णांकo guest 2.
 *
 * Returns: - > 0 अगर control has to be given to guest 2
 *            < 0 अगर an error occurred during injection.
 */
अटल पूर्णांक inject_fault(काष्ठा kvm_vcpu *vcpu, __u16 code, __u64 vaddr,
			bool ग_लिखो_flag)
अणु
	काष्ठा kvm_s390_pgm_info pgm = अणु
		.code = code,
		.trans_exc_code =
			/* 0-51: भव address */
			(vaddr & 0xfffffffffffff000UL) |
			/* 52-53: store / fetch */
			(((अचिन्हित पूर्णांक) !ग_लिखो_flag) + 1) << 10,
			/* 62-63: asce id (alway primary == 0) */
		.exc_access_id = 0, /* always primary */
		.op_access_id = 0, /* not MVPG */
	पूर्ण;
	पूर्णांक rc;

	अगर (code == PGM_PROTECTION)
		pgm.trans_exc_code |= 0x4UL;

	rc = kvm_s390_inject_prog_irq(vcpu, &pgm);
	वापस rc ? rc : 1;
पूर्ण

/*
 * Handle a fault during vsie execution on a gmap shaकरोw.
 *
 * Returns: - 0 अगर the fault was resolved
 *          - > 0 अगर control has to be given to guest 2
 *          - < 0 अगर an error occurred
 */
अटल पूर्णांक handle_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	पूर्णांक rc;

	अगर (current->thपढ़ो.gmap_पूर्णांक_code == PGM_PROTECTION)
		/* we can directly क्रमward all protection exceptions */
		वापस inject_fault(vcpu, PGM_PROTECTION,
				    current->thपढ़ो.gmap_addr, 1);

	rc = kvm_s390_shaकरोw_fault(vcpu, vsie_page->gmap,
				   current->thपढ़ो.gmap_addr, शून्य);
	अगर (rc > 0) अणु
		rc = inject_fault(vcpu, rc,
				  current->thपढ़ो.gmap_addr,
				  current->thपढ़ो.gmap_ग_लिखो_flag);
		अगर (rc >= 0)
			vsie_page->fault_addr = current->thपढ़ो.gmap_addr;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Retry the previous fault that required guest 2 पूर्णांकervention. This aव्योमs
 * one superfluous SIE re-entry and direct निकास.
 *
 * Will ignore any errors. The next SIE fault will करो proper fault handling.
 */
अटल व्योम handle_last_fault(काष्ठा kvm_vcpu *vcpu,
			      काष्ठा vsie_page *vsie_page)
अणु
	अगर (vsie_page->fault_addr)
		kvm_s390_shaकरोw_fault(vcpu, vsie_page->gmap,
				      vsie_page->fault_addr, शून्य);
	vsie_page->fault_addr = 0;
पूर्ण

अटल अंतरभूत व्योम clear_vsie_icpt(काष्ठा vsie_page *vsie_page)
अणु
	vsie_page->scb_s.icptcode = 0;
पूर्ण

/* शुरुआत the psw and clear the vsie icpt, so we can retry execution */
अटल व्योम retry_vsie_icpt(काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	पूर्णांक ilen = insn_length(scb_s->ipa >> 8);

	/* take care of EXECUTE inकाष्ठाions */
	अगर (scb_s->icptstatus & 1) अणु
		ilen = (scb_s->icptstatus >> 4) & 0x6;
		अगर (!ilen)
			ilen = 4;
	पूर्ण
	scb_s->gpsw.addr = __शुरुआत_psw(scb_s->gpsw, ilen);
	clear_vsie_icpt(vsie_page);
पूर्ण

/*
 * Try to shaकरोw + enable the guest 2 provided facility list.
 * Retry inकाष्ठाion execution अगर enabled क्रम and provided by guest 2.
 *
 * Returns: - 0 अगर handled (retry or guest 2 icpt)
 *          - > 0 अगर control has to be given to guest 2
 */
अटल पूर्णांक handle_stfle(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	__u32 fac = READ_ONCE(vsie_page->scb_o->fac) & 0x7ffffff8U;

	अगर (fac && test_kvm_facility(vcpu->kvm, 7)) अणु
		retry_vsie_icpt(vsie_page);
		अगर (पढ़ो_guest_real(vcpu, fac, &vsie_page->fac,
				    माप(vsie_page->fac)))
			वापस set_validity_icpt(scb_s, 0x1090U);
		scb_s->fac = (__u32)(__u64) &vsie_page->fac;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Get a रेजिस्टर क्रम a nested guest.
 * @vcpu the vcpu of the guest
 * @vsie_page the vsie_page क्रम the nested guest
 * @reg the रेजिस्टर number, the upper 4 bits are ignored.
 * वापसs: the value of the रेजिस्टर.
 */
अटल u64 vsie_get_रेजिस्टर(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page, u8 reg)
अणु
	/* no need to validate the parameter and/or perक्रमm error handling */
	reg &= 0xf;
	चयन (reg) अणु
	हाल 15:
		वापस vsie_page->scb_s.gg15;
	हाल 14:
		वापस vsie_page->scb_s.gg14;
	शेष:
		वापस vcpu->run->s.regs.gprs[reg];
	पूर्ण
पूर्ण

अटल पूर्णांक vsie_handle_mvpg(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	अचिन्हित दीर्घ pei_dest, pei_src, src, dest, mask, prefix;
	u64 *pei_block = &vsie_page->scb_o->mcic;
	पूर्णांक edat, rc_dest, rc_src;
	जोड़ ctlreg0 cr0;

	cr0.val = vcpu->arch.sie_block->gcr[0];
	edat = cr0.edat && test_kvm_facility(vcpu->kvm, 8);
	mask = _kvm_s390_logical_to_effective(&scb_s->gpsw, PAGE_MASK);
	prefix = scb_s->prefix << GUEST_PREFIX_SHIFT;

	dest = vsie_get_रेजिस्टर(vcpu, vsie_page, scb_s->ipb >> 20) & mask;
	dest = _kvm_s390_real_to_असल(prefix, dest) + scb_s->mso;
	src = vsie_get_रेजिस्टर(vcpu, vsie_page, scb_s->ipb >> 16) & mask;
	src = _kvm_s390_real_to_असल(prefix, src) + scb_s->mso;

	rc_dest = kvm_s390_shaकरोw_fault(vcpu, vsie_page->gmap, dest, &pei_dest);
	rc_src = kvm_s390_shaकरोw_fault(vcpu, vsie_page->gmap, src, &pei_src);
	/*
	 * Either everything went well, or something non-critical went wrong
	 * e.g. because of a race. In either हाल, simply retry.
	 */
	अगर (rc_dest == -EAGAIN || rc_src == -EAGAIN || (!rc_dest && !rc_src)) अणु
		retry_vsie_icpt(vsie_page);
		वापस -EAGAIN;
	पूर्ण
	/* Something more serious went wrong, propagate the error */
	अगर (rc_dest < 0)
		वापस rc_dest;
	अगर (rc_src < 0)
		वापस rc_src;

	/* The only possible suppressing exception: just deliver it */
	अगर (rc_dest == PGM_TRANSLATION_SPEC || rc_src == PGM_TRANSLATION_SPEC) अणु
		clear_vsie_icpt(vsie_page);
		rc_dest = kvm_s390_inject_program_पूर्णांक(vcpu, PGM_TRANSLATION_SPEC);
		WARN_ON_ONCE(rc_dest);
		वापस 1;
	पूर्ण

	/*
	 * Forward the PEI पूर्णांकercept to the guest अगर it was a page fault, or
	 * also क्रम segment and region table faults अगर EDAT applies.
	 */
	अगर (edat) अणु
		rc_dest = rc_dest == PGM_ASCE_TYPE ? rc_dest : 0;
		rc_src = rc_src == PGM_ASCE_TYPE ? rc_src : 0;
	पूर्ण अन्यथा अणु
		rc_dest = rc_dest != PGM_PAGE_TRANSLATION ? rc_dest : 0;
		rc_src = rc_src != PGM_PAGE_TRANSLATION ? rc_src : 0;
	पूर्ण
	अगर (!rc_dest && !rc_src) अणु
		pei_block[0] = pei_dest;
		pei_block[1] = pei_src;
		वापस 1;
	पूर्ण

	retry_vsie_icpt(vsie_page);

	/*
	 * The host has edat, and the guest करोes not, or it was an ASCE type
	 * exception. The host needs to inject the appropriate DAT पूर्णांकerrupts
	 * पूर्णांकo the guest.
	 */
	अगर (rc_dest)
		वापस inject_fault(vcpu, rc_dest, dest, 1);
	वापस inject_fault(vcpu, rc_src, src, 0);
पूर्ण

/*
 * Run the vsie on a shaकरोw scb and a shaकरोw gmap, without any further
 * sanity checks, handling SIE faults.
 *
 * Returns: - 0 everything went fine
 *          - > 0 अगर control has to be given to guest 2
 *          - < 0 अगर an error occurred
 */
अटल पूर्णांक करो_vsie_run(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
	__releases(vcpu->kvm->srcu)
	__acquires(vcpu->kvm->srcu)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	काष्ठा kvm_s390_sie_block *scb_o = vsie_page->scb_o;
	पूर्णांक guest_bp_isolation;
	पूर्णांक rc = 0;

	handle_last_fault(vcpu, vsie_page);

	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);

	/* save current guest state of bp isolation override */
	guest_bp_isolation = test_thपढ़ो_flag(TIF_ISOLATE_BP_GUEST);

	/*
	 * The guest is running with BPBC, so we have to क्रमce it on क्रम our
	 * nested guest. This is करोne by enabling BPBC globally, so the BPBC
	 * control in the SCB (which the nested guest can modअगरy) is simply
	 * ignored.
	 */
	अगर (test_kvm_facility(vcpu->kvm, 82) &&
	    vcpu->arch.sie_block->fpf & FPF_BPBC)
		set_thपढ़ो_flag(TIF_ISOLATE_BP_GUEST);

	local_irq_disable();
	guest_enter_irqoff();
	local_irq_enable();

	/*
	 * Simulate a SIE entry of the VCPU (see sie64a), so VCPU blocking
	 * and VCPU requests also hinder the vSIE from running and lead
	 * to an immediate निकास. kvm_s390_vsie_kick() has to be used to
	 * also kick the vSIE.
	 */
	vcpu->arch.sie_block->prog0c |= PROG_IN_SIE;
	barrier();
	अगर (test_cpu_flag(CIF_FPU))
		load_fpu_regs();
	अगर (!kvm_s390_vcpu_sie_inhibited(vcpu))
		rc = sie64a(scb_s, vcpu->run->s.regs.gprs);
	barrier();
	vcpu->arch.sie_block->prog0c &= ~PROG_IN_SIE;

	local_irq_disable();
	guest_निकास_irqoff();
	local_irq_enable();

	/* restore guest state क्रम bp isolation override */
	अगर (!guest_bp_isolation)
		clear_thपढ़ो_flag(TIF_ISOLATE_BP_GUEST);

	vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	अगर (rc == -EINTR) अणु
		VCPU_EVENT(vcpu, 3, "%s", "machine check");
		kvm_s390_reinject_machine_check(vcpu, &vsie_page->mcck_info);
		वापस 0;
	पूर्ण

	अगर (rc > 0)
		rc = 0; /* we could still have an icpt */
	अन्यथा अगर (rc == -EFAULT)
		वापस handle_fault(vcpu, vsie_page);

	चयन (scb_s->icptcode) अणु
	हाल ICPT_INST:
		अगर (scb_s->ipa == 0xb2b0)
			rc = handle_stfle(vcpu, vsie_page);
		अवरोध;
	हाल ICPT_STOP:
		/* stop not requested by g2 - must have been a kick */
		अगर (!(atomic_पढ़ो(&scb_o->cpuflags) & CPUSTAT_STOP_INT))
			clear_vsie_icpt(vsie_page);
		अवरोध;
	हाल ICPT_VALIDITY:
		अगर ((scb_s->ipa & 0xf000) != 0xf000)
			scb_s->ipa += 0x1000;
		अवरोध;
	हाल ICPT_PARTEXEC:
		अगर (scb_s->ipa == 0xb254)
			rc = vsie_handle_mvpg(vcpu, vsie_page);
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम release_gmap_shaकरोw(काष्ठा vsie_page *vsie_page)
अणु
	अगर (vsie_page->gmap)
		gmap_put(vsie_page->gmap);
	WRITE_ONCE(vsie_page->gmap, शून्य);
	prefix_unmapped(vsie_page);
पूर्ण

अटल पूर्णांक acquire_gmap_shaकरोw(काष्ठा kvm_vcpu *vcpu,
			       काष्ठा vsie_page *vsie_page)
अणु
	अचिन्हित दीर्घ asce;
	जोड़ ctlreg0 cr0;
	काष्ठा gmap *gmap;
	पूर्णांक edat;

	asce = vcpu->arch.sie_block->gcr[1];
	cr0.val = vcpu->arch.sie_block->gcr[0];
	edat = cr0.edat && test_kvm_facility(vcpu->kvm, 8);
	edat += edat && test_kvm_facility(vcpu->kvm, 78);

	/*
	 * ASCE or EDAT could have changed since last icpt, or the gmap
	 * we're holding has been unshaकरोwed. If the gmap is still valid,
	 * we can safely reuse it.
	 */
	अगर (vsie_page->gmap && gmap_shaकरोw_valid(vsie_page->gmap, asce, edat))
		वापस 0;

	/* release the old shaकरोw - अगर any, and mark the prefix as unmapped */
	release_gmap_shaकरोw(vsie_page);
	gmap = gmap_shaकरोw(vcpu->arch.gmap, asce, edat);
	अगर (IS_ERR(gmap))
		वापस PTR_ERR(gmap);
	gmap->निजी = vcpu->kvm;
	WRITE_ONCE(vsie_page->gmap, gmap);
	वापस 0;
पूर्ण

/*
 * Register the shaकरोw scb at the VCPU, e.g. क्रम kicking out of vsie.
 */
अटल व्योम रेजिस्टर_shaकरोw_scb(काष्ठा kvm_vcpu *vcpu,
				काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;

	WRITE_ONCE(vcpu->arch.vsie_block, &vsie_page->scb_s);
	/*
	 * External calls have to lead to a kick of the vcpu and
	 * thereक्रमe the vsie -> Simulate Wait state.
	 */
	kvm_s390_set_cpuflags(vcpu, CPUSTAT_WAIT);
	/*
	 * We have to adjust the g3 epoch by the g2 epoch. The epoch will
	 * स्वतःmatically be adjusted on tod घड़ी changes via kvm_sync_घड़ी.
	 */
	preempt_disable();
	scb_s->epoch += vcpu->kvm->arch.epoch;

	अगर (scb_s->ecd & ECD_MEF) अणु
		scb_s->epdx += vcpu->kvm->arch.epdx;
		अगर (scb_s->epoch < vcpu->kvm->arch.epoch)
			scb_s->epdx += 1;
	पूर्ण

	preempt_enable();
पूर्ण

/*
 * Unरेजिस्टर a shaकरोw scb from a VCPU.
 */
अटल व्योम unरेजिस्टर_shaकरोw_scb(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_s390_clear_cpuflags(vcpu, CPUSTAT_WAIT);
	WRITE_ONCE(vcpu->arch.vsie_block, शून्य);
पूर्ण

/*
 * Run the vsie on a shaकरोwed scb, managing the gmap shaकरोw, handling
 * prefix pages and faults.
 *
 * Returns: - 0 अगर no errors occurred
 *          - > 0 अगर control has to be given to guest 2
 *          - -ENOMEM अगर out of memory
 */
अटल पूर्णांक vsie_run(काष्ठा kvm_vcpu *vcpu, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	पूर्णांक rc = 0;

	जबतक (1) अणु
		rc = acquire_gmap_shaकरोw(vcpu, vsie_page);
		अगर (!rc)
			rc = map_prefix(vcpu, vsie_page);
		अगर (!rc) अणु
			gmap_enable(vsie_page->gmap);
			update_पूर्णांकervention_requests(vsie_page);
			rc = करो_vsie_run(vcpu, vsie_page);
			gmap_enable(vcpu->arch.gmap);
		पूर्ण
		atomic_andnot(PROG_BLOCK_SIE, &scb_s->prog20);

		अगर (rc == -EAGAIN)
			rc = 0;
		अगर (rc || scb_s->icptcode || संकेत_pending(current) ||
		    kvm_s390_vcpu_has_irq(vcpu, 0) ||
		    kvm_s390_vcpu_sie_inhibited(vcpu))
			अवरोध;
		cond_resched();
	पूर्ण

	अगर (rc == -EFAULT) अणु
		/*
		 * Addressing exceptions are always presentes as पूर्णांकercepts.
		 * As addressing exceptions are suppressing and our guest 3 PSW
		 * poपूर्णांकs at the responsible inकाष्ठाion, we have to
		 * क्रमward the PSW and set the ilc. If we can't पढ़ो guest 3
		 * inकाष्ठाion, we can use an arbitrary ilc. Let's always use
		 * ilen = 4 क्रम now, so we can aव्योम पढ़ोing in guest 3 भव
		 * memory. (we could also fake the shaकरोw so the hardware
		 * handles it).
		 */
		scb_s->icptcode = ICPT_PROGI;
		scb_s->iprcc = PGM_ADDRESSING;
		scb_s->pgmilc = 4;
		scb_s->gpsw.addr = __शुरुआत_psw(scb_s->gpsw, 4);
		rc = 1;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * Get or create a vsie page क्रम a scb address.
 *
 * Returns: - address of a vsie page (cached or new one)
 *          - शून्य अगर the same scb address is alपढ़ोy used by another VCPU
 *          - ERR_PTR(-ENOMEM) अगर out of memory
 */
अटल काष्ठा vsie_page *get_vsie_page(काष्ठा kvm *kvm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा vsie_page *vsie_page;
	काष्ठा page *page;
	पूर्णांक nr_vcpus;

	rcu_पढ़ो_lock();
	page = radix_tree_lookup(&kvm->arch.vsie.addr_to_page, addr >> 9);
	rcu_पढ़ो_unlock();
	अगर (page) अणु
		अगर (page_ref_inc_वापस(page) == 2)
			वापस page_to_virt(page);
		page_ref_dec(page);
	पूर्ण

	/*
	 * We want at least #online_vcpus shaकरोws, so every VCPU can execute
	 * the VSIE in parallel.
	 */
	nr_vcpus = atomic_पढ़ो(&kvm->online_vcpus);

	mutex_lock(&kvm->arch.vsie.mutex);
	अगर (kvm->arch.vsie.page_count < nr_vcpus) अणु
		page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_ZERO | GFP_DMA);
		अगर (!page) अणु
			mutex_unlock(&kvm->arch.vsie.mutex);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		page_ref_inc(page);
		kvm->arch.vsie.pages[kvm->arch.vsie.page_count] = page;
		kvm->arch.vsie.page_count++;
	पूर्ण अन्यथा अणु
		/* reuse an existing entry that beदीर्घs to nobody */
		जबतक (true) अणु
			page = kvm->arch.vsie.pages[kvm->arch.vsie.next];
			अगर (page_ref_inc_वापस(page) == 2)
				अवरोध;
			page_ref_dec(page);
			kvm->arch.vsie.next++;
			kvm->arch.vsie.next %= nr_vcpus;
		पूर्ण
		radix_tree_delete(&kvm->arch.vsie.addr_to_page, page->index >> 9);
	पूर्ण
	page->index = addr;
	/* द्विगुन use of the same address */
	अगर (radix_tree_insert(&kvm->arch.vsie.addr_to_page, addr >> 9, page)) अणु
		page_ref_dec(page);
		mutex_unlock(&kvm->arch.vsie.mutex);
		वापस शून्य;
	पूर्ण
	mutex_unlock(&kvm->arch.vsie.mutex);

	vsie_page = page_to_virt(page);
	स_रखो(&vsie_page->scb_s, 0, माप(काष्ठा kvm_s390_sie_block));
	release_gmap_shaकरोw(vsie_page);
	vsie_page->fault_addr = 0;
	vsie_page->scb_s.ihcpu = 0xffffU;
	वापस vsie_page;
पूर्ण

/* put a vsie page acquired via get_vsie_page */
अटल व्योम put_vsie_page(काष्ठा kvm *kvm, काष्ठा vsie_page *vsie_page)
अणु
	काष्ठा page *page = pfn_to_page(__pa(vsie_page) >> PAGE_SHIFT);

	page_ref_dec(page);
पूर्ण

पूर्णांक kvm_s390_handle_vsie(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा vsie_page *vsie_page;
	अचिन्हित दीर्घ scb_addr;
	पूर्णांक rc;

	vcpu->stat.inकाष्ठाion_sie++;
	अगर (!test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_SIEF2))
		वापस -EOPNOTSUPP;
	अगर (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PSTATE)
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_PRIVILEGED_OP);

	BUILD_BUG_ON(माप(काष्ठा vsie_page) != PAGE_SIZE);
	scb_addr = kvm_s390_get_base_disp_s(vcpu, शून्य);

	/* 512 byte alignment */
	अगर (unlikely(scb_addr & 0x1ffUL))
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_SPECIFICATION);

	अगर (संकेत_pending(current) || kvm_s390_vcpu_has_irq(vcpu, 0) ||
	    kvm_s390_vcpu_sie_inhibited(vcpu))
		वापस 0;

	vsie_page = get_vsie_page(vcpu->kvm, scb_addr);
	अगर (IS_ERR(vsie_page))
		वापस PTR_ERR(vsie_page);
	अन्यथा अगर (!vsie_page)
		/* द्विगुन use of sie control block - simply करो nothing */
		वापस 0;

	rc = pin_scb(vcpu, vsie_page, scb_addr);
	अगर (rc)
		जाओ out_put;
	rc = shaकरोw_scb(vcpu, vsie_page);
	अगर (rc)
		जाओ out_unpin_scb;
	rc = pin_blocks(vcpu, vsie_page);
	अगर (rc)
		जाओ out_unshaकरोw;
	रेजिस्टर_shaकरोw_scb(vcpu, vsie_page);
	rc = vsie_run(vcpu, vsie_page);
	unरेजिस्टर_shaकरोw_scb(vcpu);
	unpin_blocks(vcpu, vsie_page);
out_unshaकरोw:
	unshaकरोw_scb(vcpu, vsie_page);
out_unpin_scb:
	unpin_scb(vcpu, vsie_page, scb_addr);
out_put:
	put_vsie_page(vcpu->kvm, vsie_page);

	वापस rc < 0 ? rc : 0;
पूर्ण

/* Init the vsie data काष्ठाures. To be called when a vm is initialized. */
व्योम kvm_s390_vsie_init(काष्ठा kvm *kvm)
अणु
	mutex_init(&kvm->arch.vsie.mutex);
	INIT_RADIX_TREE(&kvm->arch.vsie.addr_to_page, GFP_KERNEL_ACCOUNT);
पूर्ण

/* Destroy the vsie data काष्ठाures. To be called when a vm is destroyed. */
व्योम kvm_s390_vsie_destroy(काष्ठा kvm *kvm)
अणु
	काष्ठा vsie_page *vsie_page;
	काष्ठा page *page;
	पूर्णांक i;

	mutex_lock(&kvm->arch.vsie.mutex);
	क्रम (i = 0; i < kvm->arch.vsie.page_count; i++) अणु
		page = kvm->arch.vsie.pages[i];
		kvm->arch.vsie.pages[i] = शून्य;
		vsie_page = page_to_virt(page);
		release_gmap_shaकरोw(vsie_page);
		/* मुक्त the radix tree entry */
		radix_tree_delete(&kvm->arch.vsie.addr_to_page, page->index >> 9);
		__मुक्त_page(page);
	पूर्ण
	kvm->arch.vsie.page_count = 0;
	mutex_unlock(&kvm->arch.vsie.mutex);
पूर्ण

व्योम kvm_s390_vsie_kick(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_s390_sie_block *scb = READ_ONCE(vcpu->arch.vsie_block);

	/*
	 * Even अगर the VCPU lets go of the shaकरोw sie block reference, it is
	 * still valid in the cache. So we can safely kick it.
	 */
	अगर (scb) अणु
		atomic_or(PROG_BLOCK_SIE, &scb->prog20);
		अगर (scb->prog0c & PROG_IN_SIE)
			atomic_or(CPUSTAT_STOP_INT, &scb->cpuflags);
	पूर्ण
पूर्ण
