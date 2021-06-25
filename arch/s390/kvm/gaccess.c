<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * guest access functions
 *
 * Copyright IBM Corp. 2014
 *
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/err.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/gmap.h>
#समावेश "kvm-s390.h"
#समावेश "gaccess.h"
#समावेश <यंत्र/चयन_to.h>

जोड़ asce अणु
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		अचिन्हित दीर्घ origin : 52; /* Region- or Segment-Table Origin */
		अचिन्हित दीर्घ	 : 2;
		अचिन्हित दीर्घ g  : 1; /* Subspace Group Control */
		अचिन्हित दीर्घ p  : 1; /* Private Space Control */
		अचिन्हित दीर्घ s  : 1; /* Storage-Alteration-Event Control */
		अचिन्हित दीर्घ x  : 1; /* Space-Switch-Event Control */
		अचिन्हित दीर्घ r  : 1; /* Real-Space Control */
		अचिन्हित दीर्घ	 : 1;
		अचिन्हित दीर्घ dt : 2; /* Designation-Type Control */
		अचिन्हित दीर्घ tl : 2; /* Region- or Segment-Table Length */
	पूर्ण;
पूर्ण;

क्रमागत अणु
	ASCE_TYPE_SEGMENT = 0,
	ASCE_TYPE_REGION3 = 1,
	ASCE_TYPE_REGION2 = 2,
	ASCE_TYPE_REGION1 = 3
पूर्ण;

जोड़ region1_table_entry अणु
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		अचिन्हित दीर्घ rto: 52;/* Region-Table Origin */
		अचिन्हित दीर्घ	 : 2;
		अचिन्हित दीर्घ p  : 1; /* DAT-Protection Bit */
		अचिन्हित दीर्घ	 : 1;
		अचिन्हित दीर्घ tf : 2; /* Region-Second-Table Offset */
		अचिन्हित दीर्घ i  : 1; /* Region-Invalid Bit */
		अचिन्हित दीर्घ	 : 1;
		अचिन्हित दीर्घ tt : 2; /* Table-Type Bits */
		अचिन्हित दीर्घ tl : 2; /* Region-Second-Table Length */
	पूर्ण;
पूर्ण;

जोड़ region2_table_entry अणु
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		अचिन्हित दीर्घ rto: 52;/* Region-Table Origin */
		अचिन्हित दीर्घ	 : 2;
		अचिन्हित दीर्घ p  : 1; /* DAT-Protection Bit */
		अचिन्हित दीर्घ	 : 1;
		अचिन्हित दीर्घ tf : 2; /* Region-Third-Table Offset */
		अचिन्हित दीर्घ i  : 1; /* Region-Invalid Bit */
		अचिन्हित दीर्घ	 : 1;
		अचिन्हित दीर्घ tt : 2; /* Table-Type Bits */
		अचिन्हित दीर्घ tl : 2; /* Region-Third-Table Length */
	पूर्ण;
पूर्ण;

काष्ठा region3_table_entry_fc0 अणु
	अचिन्हित दीर्घ sto: 52;/* Segment-Table Origin */
	अचिन्हित दीर्घ	 : 1;
	अचिन्हित दीर्घ fc : 1; /* Format-Control */
	अचिन्हित दीर्घ p  : 1; /* DAT-Protection Bit */
	अचिन्हित दीर्घ	 : 1;
	अचिन्हित दीर्घ tf : 2; /* Segment-Table Offset */
	अचिन्हित दीर्घ i  : 1; /* Region-Invalid Bit */
	अचिन्हित दीर्घ cr : 1; /* Common-Region Bit */
	अचिन्हित दीर्घ tt : 2; /* Table-Type Bits */
	अचिन्हित दीर्घ tl : 2; /* Segment-Table Length */
पूर्ण;

काष्ठा region3_table_entry_fc1 अणु
	अचिन्हित दीर्घ rfaa : 33; /* Region-Frame Absolute Address */
	अचिन्हित दीर्घ	 : 14;
	अचिन्हित दीर्घ av : 1; /* ACCF-Validity Control */
	अचिन्हित दीर्घ acc: 4; /* Access-Control Bits */
	अचिन्हित दीर्घ f  : 1; /* Fetch-Protection Bit */
	अचिन्हित दीर्घ fc : 1; /* Format-Control */
	अचिन्हित दीर्घ p  : 1; /* DAT-Protection Bit */
	अचिन्हित दीर्घ iep: 1; /* Inकाष्ठाion-Execution-Protection */
	अचिन्हित दीर्घ	 : 2;
	अचिन्हित दीर्घ i  : 1; /* Region-Invalid Bit */
	अचिन्हित दीर्घ cr : 1; /* Common-Region Bit */
	अचिन्हित दीर्घ tt : 2; /* Table-Type Bits */
	अचिन्हित दीर्घ	 : 2;
पूर्ण;

जोड़ region3_table_entry अणु
	अचिन्हित दीर्घ val;
	काष्ठा region3_table_entry_fc0 fc0;
	काष्ठा region3_table_entry_fc1 fc1;
	काष्ठा अणु
		अचिन्हित दीर्घ	 : 53;
		अचिन्हित दीर्घ fc : 1; /* Format-Control */
		अचिन्हित दीर्घ	 : 4;
		अचिन्हित दीर्घ i  : 1; /* Region-Invalid Bit */
		अचिन्हित दीर्घ cr : 1; /* Common-Region Bit */
		अचिन्हित दीर्घ tt : 2; /* Table-Type Bits */
		अचिन्हित दीर्घ	 : 2;
	पूर्ण;
पूर्ण;

काष्ठा segment_entry_fc0 अणु
	अचिन्हित दीर्घ pto: 53;/* Page-Table Origin */
	अचिन्हित दीर्घ fc : 1; /* Format-Control */
	अचिन्हित दीर्घ p  : 1; /* DAT-Protection Bit */
	अचिन्हित दीर्घ	 : 3;
	अचिन्हित दीर्घ i  : 1; /* Segment-Invalid Bit */
	अचिन्हित दीर्घ cs : 1; /* Common-Segment Bit */
	अचिन्हित दीर्घ tt : 2; /* Table-Type Bits */
	अचिन्हित दीर्घ	 : 2;
पूर्ण;

काष्ठा segment_entry_fc1 अणु
	अचिन्हित दीर्घ sfaa : 44; /* Segment-Frame Absolute Address */
	अचिन्हित दीर्घ	 : 3;
	अचिन्हित दीर्घ av : 1; /* ACCF-Validity Control */
	अचिन्हित दीर्घ acc: 4; /* Access-Control Bits */
	अचिन्हित दीर्घ f  : 1; /* Fetch-Protection Bit */
	अचिन्हित दीर्घ fc : 1; /* Format-Control */
	अचिन्हित दीर्घ p  : 1; /* DAT-Protection Bit */
	अचिन्हित दीर्घ iep: 1; /* Inकाष्ठाion-Execution-Protection */
	अचिन्हित दीर्घ	 : 2;
	अचिन्हित दीर्घ i  : 1; /* Segment-Invalid Bit */
	अचिन्हित दीर्घ cs : 1; /* Common-Segment Bit */
	अचिन्हित दीर्घ tt : 2; /* Table-Type Bits */
	अचिन्हित दीर्घ	 : 2;
पूर्ण;

जोड़ segment_table_entry अणु
	अचिन्हित दीर्घ val;
	काष्ठा segment_entry_fc0 fc0;
	काष्ठा segment_entry_fc1 fc1;
	काष्ठा अणु
		अचिन्हित दीर्घ	 : 53;
		अचिन्हित दीर्घ fc : 1; /* Format-Control */
		अचिन्हित दीर्घ	 : 4;
		अचिन्हित दीर्घ i  : 1; /* Segment-Invalid Bit */
		अचिन्हित दीर्घ cs : 1; /* Common-Segment Bit */
		अचिन्हित दीर्घ tt : 2; /* Table-Type Bits */
		अचिन्हित दीर्घ	 : 2;
	पूर्ण;
पूर्ण;

क्रमागत अणु
	TABLE_TYPE_SEGMENT = 0,
	TABLE_TYPE_REGION3 = 1,
	TABLE_TYPE_REGION2 = 2,
	TABLE_TYPE_REGION1 = 3
पूर्ण;

जोड़ page_table_entry अणु
	अचिन्हित दीर्घ val;
	काष्ठा अणु
		अचिन्हित दीर्घ pfra : 52; /* Page-Frame Real Address */
		अचिन्हित दीर्घ z  : 1; /* Zero Bit */
		अचिन्हित दीर्घ i  : 1; /* Page-Invalid Bit */
		अचिन्हित दीर्घ p  : 1; /* DAT-Protection Bit */
		अचिन्हित दीर्घ iep: 1; /* Inकाष्ठाion-Execution-Protection */
		अचिन्हित दीर्घ	 : 8;
	पूर्ण;
पूर्ण;

/*
 * vaddress जोड़ in order to easily decode a भव address पूर्णांकo its
 * region first index, region second index etc. parts.
 */
जोड़ vaddress अणु
	अचिन्हित दीर्घ addr;
	काष्ठा अणु
		अचिन्हित दीर्घ rfx : 11;
		अचिन्हित दीर्घ rsx : 11;
		अचिन्हित दीर्घ rtx : 11;
		अचिन्हित दीर्घ sx  : 11;
		अचिन्हित दीर्घ px  : 8;
		अचिन्हित दीर्घ bx  : 12;
	पूर्ण;
	काष्ठा अणु
		अचिन्हित दीर्घ rfx01 : 2;
		अचिन्हित दीर्घ	    : 9;
		अचिन्हित दीर्घ rsx01 : 2;
		अचिन्हित दीर्घ	    : 9;
		अचिन्हित दीर्घ rtx01 : 2;
		अचिन्हित दीर्घ	    : 9;
		अचिन्हित दीर्घ sx01  : 2;
		अचिन्हित दीर्घ	    : 29;
	पूर्ण;
पूर्ण;

/*
 * raddress जोड़ which will contain the result (real or असलolute address)
 * after a page table walk. The rfaa, sfaa and pfra members are used to
 * simply assign them the value of a region, segment or page table entry.
 */
जोड़ raddress अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ rfaa : 33; /* Region-Frame Absolute Address */
	अचिन्हित दीर्घ sfaa : 44; /* Segment-Frame Absolute Address */
	अचिन्हित दीर्घ pfra : 52; /* Page-Frame Real Address */
पूर्ण;

जोड़ alet अणु
	u32 val;
	काष्ठा अणु
		u32 reserved : 7;
		u32 p        : 1;
		u32 alesn    : 8;
		u32 alen     : 16;
	पूर्ण;
पूर्ण;

जोड़ ald अणु
	u32 val;
	काष्ठा अणु
		u32     : 1;
		u32 alo : 24;
		u32 all : 7;
	पूर्ण;
पूर्ण;

काष्ठा ale अणु
	अचिन्हित दीर्घ i      : 1; /* ALEN-Invalid Bit */
	अचिन्हित दीर्घ        : 5;
	अचिन्हित दीर्घ fo     : 1; /* Fetch-Only Bit */
	अचिन्हित दीर्घ p      : 1; /* Private Bit */
	अचिन्हित दीर्घ alesn  : 8; /* Access-List-Entry Sequence Number */
	अचिन्हित दीर्घ aleax  : 16; /* Access-List-Entry Authorization Index */
	अचिन्हित दीर्घ        : 32;
	अचिन्हित दीर्घ        : 1;
	अचिन्हित दीर्घ asteo  : 25; /* ASN-Second-Table-Entry Origin */
	अचिन्हित दीर्घ        : 6;
	अचिन्हित दीर्घ astesn : 32; /* ASTE Sequence Number */
पूर्ण;

काष्ठा aste अणु
	अचिन्हित दीर्घ i      : 1; /* ASX-Invalid Bit */
	अचिन्हित दीर्घ ato    : 29; /* Authority-Table Origin */
	अचिन्हित दीर्घ        : 1;
	अचिन्हित दीर्घ b      : 1; /* Base-Space Bit */
	अचिन्हित दीर्घ ax     : 16; /* Authorization Index */
	अचिन्हित दीर्घ atl    : 12; /* Authority-Table Length */
	अचिन्हित दीर्घ        : 2;
	अचिन्हित दीर्घ ca     : 1; /* Controlled-ASN Bit */
	अचिन्हित दीर्घ ra     : 1; /* Reusable-ASN Bit */
	अचिन्हित दीर्घ asce   : 64; /* Address-Space-Control Element */
	अचिन्हित दीर्घ ald    : 32;
	अचिन्हित दीर्घ astesn : 32;
	/* .. more fields there */
पूर्ण;

पूर्णांक ipte_lock_held(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.sie_block->eca & ECA_SII) अणु
		पूर्णांक rc;

		पढ़ो_lock(&vcpu->kvm->arch.sca_lock);
		rc = kvm_s390_get_ipte_control(vcpu->kvm)->kh != 0;
		पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);
		वापस rc;
	पूर्ण
	वापस vcpu->kvm->arch.ipte_lock_count != 0;
पूर्ण

अटल व्योम ipte_lock_simple(काष्ठा kvm_vcpu *vcpu)
अणु
	जोड़ ipte_control old, new, *ic;

	mutex_lock(&vcpu->kvm->arch.ipte_mutex);
	vcpu->kvm->arch.ipte_lock_count++;
	अगर (vcpu->kvm->arch.ipte_lock_count > 1)
		जाओ out;
retry:
	पढ़ो_lock(&vcpu->kvm->arch.sca_lock);
	ic = kvm_s390_get_ipte_control(vcpu->kvm);
	करो अणु
		old = READ_ONCE(*ic);
		अगर (old.k) अणु
			पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);
			cond_resched();
			जाओ retry;
		पूर्ण
		new = old;
		new.k = 1;
	पूर्ण जबतक (cmpxchg(&ic->val, old.val, new.val) != old.val);
	पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);
out:
	mutex_unlock(&vcpu->kvm->arch.ipte_mutex);
पूर्ण

अटल व्योम ipte_unlock_simple(काष्ठा kvm_vcpu *vcpu)
अणु
	जोड़ ipte_control old, new, *ic;

	mutex_lock(&vcpu->kvm->arch.ipte_mutex);
	vcpu->kvm->arch.ipte_lock_count--;
	अगर (vcpu->kvm->arch.ipte_lock_count)
		जाओ out;
	पढ़ो_lock(&vcpu->kvm->arch.sca_lock);
	ic = kvm_s390_get_ipte_control(vcpu->kvm);
	करो अणु
		old = READ_ONCE(*ic);
		new = old;
		new.k = 0;
	पूर्ण जबतक (cmpxchg(&ic->val, old.val, new.val) != old.val);
	पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);
	wake_up(&vcpu->kvm->arch.ipte_wq);
out:
	mutex_unlock(&vcpu->kvm->arch.ipte_mutex);
पूर्ण

अटल व्योम ipte_lock_siअगर(काष्ठा kvm_vcpu *vcpu)
अणु
	जोड़ ipte_control old, new, *ic;

retry:
	पढ़ो_lock(&vcpu->kvm->arch.sca_lock);
	ic = kvm_s390_get_ipte_control(vcpu->kvm);
	करो अणु
		old = READ_ONCE(*ic);
		अगर (old.kg) अणु
			पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);
			cond_resched();
			जाओ retry;
		पूर्ण
		new = old;
		new.k = 1;
		new.kh++;
	पूर्ण जबतक (cmpxchg(&ic->val, old.val, new.val) != old.val);
	पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);
पूर्ण

अटल व्योम ipte_unlock_siअगर(काष्ठा kvm_vcpu *vcpu)
अणु
	जोड़ ipte_control old, new, *ic;

	पढ़ो_lock(&vcpu->kvm->arch.sca_lock);
	ic = kvm_s390_get_ipte_control(vcpu->kvm);
	करो अणु
		old = READ_ONCE(*ic);
		new = old;
		new.kh--;
		अगर (!new.kh)
			new.k = 0;
	पूर्ण जबतक (cmpxchg(&ic->val, old.val, new.val) != old.val);
	पढ़ो_unlock(&vcpu->kvm->arch.sca_lock);
	अगर (!new.kh)
		wake_up(&vcpu->kvm->arch.ipte_wq);
पूर्ण

व्योम ipte_lock(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.sie_block->eca & ECA_SII)
		ipte_lock_siअगर(vcpu);
	अन्यथा
		ipte_lock_simple(vcpu);
पूर्ण

व्योम ipte_unlock(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.sie_block->eca & ECA_SII)
		ipte_unlock_siअगर(vcpu);
	अन्यथा
		ipte_unlock_simple(vcpu);
पूर्ण

अटल पूर्णांक ar_translation(काष्ठा kvm_vcpu *vcpu, जोड़ asce *asce, u8 ar,
			  क्रमागत gacc_mode mode)
अणु
	जोड़ alet alet;
	काष्ठा ale ale;
	काष्ठा aste aste;
	अचिन्हित दीर्घ ald_addr, authority_table_addr;
	जोड़ ald ald;
	पूर्णांक eax, rc;
	u8 authority_table;

	अगर (ar >= NUM_ACRS)
		वापस -EINVAL;

	save_access_regs(vcpu->run->s.regs.acrs);
	alet.val = vcpu->run->s.regs.acrs[ar];

	अगर (ar == 0 || alet.val == 0) अणु
		asce->val = vcpu->arch.sie_block->gcr[1];
		वापस 0;
	पूर्ण अन्यथा अगर (alet.val == 1) अणु
		asce->val = vcpu->arch.sie_block->gcr[7];
		वापस 0;
	पूर्ण

	अगर (alet.reserved)
		वापस PGM_ALET_SPECIFICATION;

	अगर (alet.p)
		ald_addr = vcpu->arch.sie_block->gcr[5];
	अन्यथा
		ald_addr = vcpu->arch.sie_block->gcr[2];
	ald_addr &= 0x7fffffc0;

	rc = पढ़ो_guest_real(vcpu, ald_addr + 16, &ald.val, माप(जोड़ ald));
	अगर (rc)
		वापस rc;

	अगर (alet.alen / 8 > ald.all)
		वापस PGM_ALEN_TRANSLATION;

	अगर (0x7fffffff - ald.alo * 128 < alet.alen * 16)
		वापस PGM_ADDRESSING;

	rc = पढ़ो_guest_real(vcpu, ald.alo * 128 + alet.alen * 16, &ale,
			     माप(काष्ठा ale));
	अगर (rc)
		वापस rc;

	अगर (ale.i == 1)
		वापस PGM_ALEN_TRANSLATION;
	अगर (ale.alesn != alet.alesn)
		वापस PGM_ALE_SEQUENCE;

	rc = पढ़ो_guest_real(vcpu, ale.asteo * 64, &aste, माप(काष्ठा aste));
	अगर (rc)
		वापस rc;

	अगर (aste.i)
		वापस PGM_ASTE_VALIDITY;
	अगर (aste.astesn != ale.astesn)
		वापस PGM_ASTE_SEQUENCE;

	अगर (ale.p == 1) अणु
		eax = (vcpu->arch.sie_block->gcr[8] >> 16) & 0xffff;
		अगर (ale.aleax != eax) अणु
			अगर (eax / 16 > aste.atl)
				वापस PGM_EXTENDED_AUTHORITY;

			authority_table_addr = aste.ato * 4 + eax / 4;

			rc = पढ़ो_guest_real(vcpu, authority_table_addr,
					     &authority_table,
					     माप(u8));
			अगर (rc)
				वापस rc;

			अगर ((authority_table & (0x40 >> ((eax & 3) * 2))) == 0)
				वापस PGM_EXTENDED_AUTHORITY;
		पूर्ण
	पूर्ण

	अगर (ale.fo == 1 && mode == GACC_STORE)
		वापस PGM_PROTECTION;

	asce->val = aste.asce;
	वापस 0;
पूर्ण

काष्ठा trans_exc_code_bits अणु
	अचिन्हित दीर्घ addr : 52; /* Translation-exception Address */
	अचिन्हित दीर्घ fsi  : 2;  /* Access Exception Fetch/Store Indication */
	अचिन्हित दीर्घ	   : 2;
	अचिन्हित दीर्घ b56  : 1;
	अचिन्हित दीर्घ	   : 3;
	अचिन्हित दीर्घ b60  : 1;
	अचिन्हित दीर्घ b61  : 1;
	अचिन्हित दीर्घ as   : 2;  /* ASCE Identअगरier */
पूर्ण;

क्रमागत अणु
	FSI_UNKNOWN = 0, /* Unknown wether fetch or store */
	FSI_STORE   = 1, /* Exception was due to store operation */
	FSI_FETCH   = 2  /* Exception was due to fetch operation */
पूर्ण;

क्रमागत prot_type अणु
	PROT_TYPE_LA   = 0,
	PROT_TYPE_KEYC = 1,
	PROT_TYPE_ALC  = 2,
	PROT_TYPE_DAT  = 3,
	PROT_TYPE_IEP  = 4,
पूर्ण;

अटल पूर्णांक trans_exc(काष्ठा kvm_vcpu *vcpu, पूर्णांक code, अचिन्हित दीर्घ gva,
		     u8 ar, क्रमागत gacc_mode mode, क्रमागत prot_type prot)
अणु
	काष्ठा kvm_s390_pgm_info *pgm = &vcpu->arch.pgm;
	काष्ठा trans_exc_code_bits *tec;

	स_रखो(pgm, 0, माप(*pgm));
	pgm->code = code;
	tec = (काष्ठा trans_exc_code_bits *)&pgm->trans_exc_code;

	चयन (code) अणु
	हाल PGM_PROTECTION:
		चयन (prot) अणु
		हाल PROT_TYPE_IEP:
			tec->b61 = 1;
			fallthrough;
		हाल PROT_TYPE_LA:
			tec->b56 = 1;
			अवरोध;
		हाल PROT_TYPE_KEYC:
			tec->b60 = 1;
			अवरोध;
		हाल PROT_TYPE_ALC:
			tec->b60 = 1;
			fallthrough;
		हाल PROT_TYPE_DAT:
			tec->b61 = 1;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल PGM_ASCE_TYPE:
	हाल PGM_PAGE_TRANSLATION:
	हाल PGM_REGION_FIRST_TRANS:
	हाल PGM_REGION_SECOND_TRANS:
	हाल PGM_REGION_THIRD_TRANS:
	हाल PGM_SEGMENT_TRANSLATION:
		/*
		 * op_access_id only applies to MOVE_PAGE -> set bit 61
		 * exc_access_id has to be set to 0 क्रम some inकाष्ठाions. Both
		 * हालs have to be handled by the caller.
		 */
		tec->addr = gva >> PAGE_SHIFT;
		tec->fsi = mode == GACC_STORE ? FSI_STORE : FSI_FETCH;
		tec->as = psw_bits(vcpu->arch.sie_block->gpsw).as;
		fallthrough;
	हाल PGM_ALEN_TRANSLATION:
	हाल PGM_ALE_SEQUENCE:
	हाल PGM_ASTE_VALIDITY:
	हाल PGM_ASTE_SEQUENCE:
	हाल PGM_EXTENDED_AUTHORITY:
		/*
		 * We can always store exc_access_id, as it is
		 * undefined क्रम non-ar हालs. It is undefined क्रम
		 * most DAT protection exceptions.
		 */
		pgm->exc_access_id = ar;
		अवरोध;
	पूर्ण
	वापस code;
पूर्ण

अटल पूर्णांक get_vcpu_asce(काष्ठा kvm_vcpu *vcpu, जोड़ asce *asce,
			 अचिन्हित दीर्घ ga, u8 ar, क्रमागत gacc_mode mode)
अणु
	पूर्णांक rc;
	काष्ठा psw_bits psw = psw_bits(vcpu->arch.sie_block->gpsw);

	अगर (!psw.dat) अणु
		asce->val = 0;
		asce->r = 1;
		वापस 0;
	पूर्ण

	अगर ((mode == GACC_IFETCH) && (psw.as != PSW_BITS_AS_HOME))
		psw.as = PSW_BITS_AS_PRIMARY;

	चयन (psw.as) अणु
	हाल PSW_BITS_AS_PRIMARY:
		asce->val = vcpu->arch.sie_block->gcr[1];
		वापस 0;
	हाल PSW_BITS_AS_SECONDARY:
		asce->val = vcpu->arch.sie_block->gcr[7];
		वापस 0;
	हाल PSW_BITS_AS_HOME:
		asce->val = vcpu->arch.sie_block->gcr[13];
		वापस 0;
	हाल PSW_BITS_AS_ACCREG:
		rc = ar_translation(vcpu, asce, ar, mode);
		अगर (rc > 0)
			वापस trans_exc(vcpu, rc, ga, ar, mode, PROT_TYPE_ALC);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक deref_table(काष्ठा kvm *kvm, अचिन्हित दीर्घ gpa, अचिन्हित दीर्घ *val)
अणु
	वापस kvm_पढ़ो_guest(kvm, gpa, val, माप(*val));
पूर्ण

/**
 * guest_translate - translate a guest भव पूर्णांकo a guest असलolute address
 * @vcpu: भव cpu
 * @gva: guest भव address
 * @gpa: poपूर्णांकs to where guest physical (असलolute) address should be stored
 * @asce: effective asce
 * @mode: indicates the access mode to be used
 * @prot: वापसs the type क्रम protection exceptions
 *
 * Translate a guest भव address पूर्णांकo a guest असलolute address by means
 * of dynamic address translation as specअगरied by the architecture.
 * If the resulting असलolute address is not available in the configuration
 * an addressing exception is indicated and @gpa will not be changed.
 *
 * Returns: - zero on success; @gpa contains the resulting असलolute address
 *	    - a negative value अगर guest access failed due to e.g. broken
 *	      guest mapping
 *	    - a positve value अगर an access exception happened. In this हाल
 *	      the वापसed value is the program पूर्णांकerruption code as defined
 *	      by the architecture
 */
अटल अचिन्हित दीर्घ guest_translate(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva,
				     अचिन्हित दीर्घ *gpa, स्थिर जोड़ asce asce,
				     क्रमागत gacc_mode mode, क्रमागत prot_type *prot)
अणु
	जोड़ vaddress vaddr = अणु.addr = gvaपूर्ण;
	जोड़ raddress raddr = अणु.addr = gvaपूर्ण;
	जोड़ page_table_entry pte;
	पूर्णांक dat_protection = 0;
	पूर्णांक iep_protection = 0;
	जोड़ ctlreg0 ctlreg0;
	अचिन्हित दीर्घ ptr;
	पूर्णांक edat1, edat2, iep;

	ctlreg0.val = vcpu->arch.sie_block->gcr[0];
	edat1 = ctlreg0.edat && test_kvm_facility(vcpu->kvm, 8);
	edat2 = edat1 && test_kvm_facility(vcpu->kvm, 78);
	iep = ctlreg0.iep && test_kvm_facility(vcpu->kvm, 130);
	अगर (asce.r)
		जाओ real_address;
	ptr = asce.origin * PAGE_SIZE;
	चयन (asce.dt) अणु
	हाल ASCE_TYPE_REGION1:
		अगर (vaddr.rfx01 > asce.tl)
			वापस PGM_REGION_FIRST_TRANS;
		ptr += vaddr.rfx * 8;
		अवरोध;
	हाल ASCE_TYPE_REGION2:
		अगर (vaddr.rfx)
			वापस PGM_ASCE_TYPE;
		अगर (vaddr.rsx01 > asce.tl)
			वापस PGM_REGION_SECOND_TRANS;
		ptr += vaddr.rsx * 8;
		अवरोध;
	हाल ASCE_TYPE_REGION3:
		अगर (vaddr.rfx || vaddr.rsx)
			वापस PGM_ASCE_TYPE;
		अगर (vaddr.rtx01 > asce.tl)
			वापस PGM_REGION_THIRD_TRANS;
		ptr += vaddr.rtx * 8;
		अवरोध;
	हाल ASCE_TYPE_SEGMENT:
		अगर (vaddr.rfx || vaddr.rsx || vaddr.rtx)
			वापस PGM_ASCE_TYPE;
		अगर (vaddr.sx01 > asce.tl)
			वापस PGM_SEGMENT_TRANSLATION;
		ptr += vaddr.sx * 8;
		अवरोध;
	पूर्ण
	चयन (asce.dt) अणु
	हाल ASCE_TYPE_REGION1:	अणु
		जोड़ region1_table_entry rfte;

		अगर (kvm_is_error_gpa(vcpu->kvm, ptr))
			वापस PGM_ADDRESSING;
		अगर (deref_table(vcpu->kvm, ptr, &rfte.val))
			वापस -EFAULT;
		अगर (rfte.i)
			वापस PGM_REGION_FIRST_TRANS;
		अगर (rfte.tt != TABLE_TYPE_REGION1)
			वापस PGM_TRANSLATION_SPEC;
		अगर (vaddr.rsx01 < rfte.tf || vaddr.rsx01 > rfte.tl)
			वापस PGM_REGION_SECOND_TRANS;
		अगर (edat1)
			dat_protection |= rfte.p;
		ptr = rfte.rto * PAGE_SIZE + vaddr.rsx * 8;
	पूर्ण
		fallthrough;
	हाल ASCE_TYPE_REGION2: अणु
		जोड़ region2_table_entry rste;

		अगर (kvm_is_error_gpa(vcpu->kvm, ptr))
			वापस PGM_ADDRESSING;
		अगर (deref_table(vcpu->kvm, ptr, &rste.val))
			वापस -EFAULT;
		अगर (rste.i)
			वापस PGM_REGION_SECOND_TRANS;
		अगर (rste.tt != TABLE_TYPE_REGION2)
			वापस PGM_TRANSLATION_SPEC;
		अगर (vaddr.rtx01 < rste.tf || vaddr.rtx01 > rste.tl)
			वापस PGM_REGION_THIRD_TRANS;
		अगर (edat1)
			dat_protection |= rste.p;
		ptr = rste.rto * PAGE_SIZE + vaddr.rtx * 8;
	पूर्ण
		fallthrough;
	हाल ASCE_TYPE_REGION3: अणु
		जोड़ region3_table_entry rtte;

		अगर (kvm_is_error_gpa(vcpu->kvm, ptr))
			वापस PGM_ADDRESSING;
		अगर (deref_table(vcpu->kvm, ptr, &rtte.val))
			वापस -EFAULT;
		अगर (rtte.i)
			वापस PGM_REGION_THIRD_TRANS;
		अगर (rtte.tt != TABLE_TYPE_REGION3)
			वापस PGM_TRANSLATION_SPEC;
		अगर (rtte.cr && asce.p && edat2)
			वापस PGM_TRANSLATION_SPEC;
		अगर (rtte.fc && edat2) अणु
			dat_protection |= rtte.fc1.p;
			iep_protection = rtte.fc1.iep;
			raddr.rfaa = rtte.fc1.rfaa;
			जाओ असलolute_address;
		पूर्ण
		अगर (vaddr.sx01 < rtte.fc0.tf)
			वापस PGM_SEGMENT_TRANSLATION;
		अगर (vaddr.sx01 > rtte.fc0.tl)
			वापस PGM_SEGMENT_TRANSLATION;
		अगर (edat1)
			dat_protection |= rtte.fc0.p;
		ptr = rtte.fc0.sto * PAGE_SIZE + vaddr.sx * 8;
	पूर्ण
		fallthrough;
	हाल ASCE_TYPE_SEGMENT: अणु
		जोड़ segment_table_entry ste;

		अगर (kvm_is_error_gpa(vcpu->kvm, ptr))
			वापस PGM_ADDRESSING;
		अगर (deref_table(vcpu->kvm, ptr, &ste.val))
			वापस -EFAULT;
		अगर (ste.i)
			वापस PGM_SEGMENT_TRANSLATION;
		अगर (ste.tt != TABLE_TYPE_SEGMENT)
			वापस PGM_TRANSLATION_SPEC;
		अगर (ste.cs && asce.p)
			वापस PGM_TRANSLATION_SPEC;
		अगर (ste.fc && edat1) अणु
			dat_protection |= ste.fc1.p;
			iep_protection = ste.fc1.iep;
			raddr.sfaa = ste.fc1.sfaa;
			जाओ असलolute_address;
		पूर्ण
		dat_protection |= ste.fc0.p;
		ptr = ste.fc0.pto * (PAGE_SIZE / 2) + vaddr.px * 8;
	पूर्ण
	पूर्ण
	अगर (kvm_is_error_gpa(vcpu->kvm, ptr))
		वापस PGM_ADDRESSING;
	अगर (deref_table(vcpu->kvm, ptr, &pte.val))
		वापस -EFAULT;
	अगर (pte.i)
		वापस PGM_PAGE_TRANSLATION;
	अगर (pte.z)
		वापस PGM_TRANSLATION_SPEC;
	dat_protection |= pte.p;
	iep_protection = pte.iep;
	raddr.pfra = pte.pfra;
real_address:
	raddr.addr = kvm_s390_real_to_असल(vcpu, raddr.addr);
असलolute_address:
	अगर (mode == GACC_STORE && dat_protection) अणु
		*prot = PROT_TYPE_DAT;
		वापस PGM_PROTECTION;
	पूर्ण
	अगर (mode == GACC_IFETCH && iep_protection && iep) अणु
		*prot = PROT_TYPE_IEP;
		वापस PGM_PROTECTION;
	पूर्ण
	अगर (kvm_is_error_gpa(vcpu->kvm, raddr.addr))
		वापस PGM_ADDRESSING;
	*gpa = raddr.addr;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_low_address(अचिन्हित दीर्घ ga)
अणु
	/* Check क्रम address ranges 0..511 and 4096..4607 */
	वापस (ga & ~0x11fful) == 0;
पूर्ण

अटल पूर्णांक low_address_protection_enabled(काष्ठा kvm_vcpu *vcpu,
					  स्थिर जोड़ asce asce)
अणु
	जोड़ ctlreg0 ctlreg0 = अणु.val = vcpu->arch.sie_block->gcr[0]पूर्ण;
	psw_t *psw = &vcpu->arch.sie_block->gpsw;

	अगर (!ctlreg0.lap)
		वापस 0;
	अगर (psw_bits(*psw).dat && asce.p)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक guest_page_range(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ ga, u8 ar,
			    अचिन्हित दीर्घ *pages, अचिन्हित दीर्घ nr_pages,
			    स्थिर जोड़ asce asce, क्रमागत gacc_mode mode)
अणु
	psw_t *psw = &vcpu->arch.sie_block->gpsw;
	पूर्णांक lap_enabled, rc = 0;
	क्रमागत prot_type prot;

	lap_enabled = low_address_protection_enabled(vcpu, asce);
	जबतक (nr_pages) अणु
		ga = kvm_s390_logical_to_effective(vcpu, ga);
		अगर (mode == GACC_STORE && lap_enabled && is_low_address(ga))
			वापस trans_exc(vcpu, PGM_PROTECTION, ga, ar, mode,
					 PROT_TYPE_LA);
		ga &= PAGE_MASK;
		अगर (psw_bits(*psw).dat) अणु
			rc = guest_translate(vcpu, ga, pages, asce, mode, &prot);
			अगर (rc < 0)
				वापस rc;
		पूर्ण अन्यथा अणु
			*pages = kvm_s390_real_to_असल(vcpu, ga);
			अगर (kvm_is_error_gpa(vcpu->kvm, *pages))
				rc = PGM_ADDRESSING;
		पूर्ण
		अगर (rc)
			वापस trans_exc(vcpu, rc, ga, ar, mode, prot);
		ga += PAGE_SIZE;
		pages++;
		nr_pages--;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक access_guest(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ ga, u8 ar, व्योम *data,
		 अचिन्हित दीर्घ len, क्रमागत gacc_mode mode)
अणु
	psw_t *psw = &vcpu->arch.sie_block->gpsw;
	अचिन्हित दीर्घ _len, nr_pages, gpa, idx;
	अचिन्हित दीर्घ pages_array[2];
	अचिन्हित दीर्घ *pages;
	पूर्णांक need_ipte_lock;
	जोड़ asce asce;
	पूर्णांक rc;

	अगर (!len)
		वापस 0;
	ga = kvm_s390_logical_to_effective(vcpu, ga);
	rc = get_vcpu_asce(vcpu, &asce, ga, ar, mode);
	अगर (rc)
		वापस rc;
	nr_pages = (((ga & ~PAGE_MASK) + len - 1) >> PAGE_SHIFT) + 1;
	pages = pages_array;
	अगर (nr_pages > ARRAY_SIZE(pages_array))
		pages = vदो_स्मृति(array_size(nr_pages, माप(अचिन्हित दीर्घ)));
	अगर (!pages)
		वापस -ENOMEM;
	need_ipte_lock = psw_bits(*psw).dat && !asce.r;
	अगर (need_ipte_lock)
		ipte_lock(vcpu);
	rc = guest_page_range(vcpu, ga, ar, pages, nr_pages, asce, mode);
	क्रम (idx = 0; idx < nr_pages && !rc; idx++) अणु
		gpa = *(pages + idx) + (ga & ~PAGE_MASK);
		_len = min(PAGE_SIZE - (gpa & ~PAGE_MASK), len);
		अगर (mode == GACC_STORE)
			rc = kvm_ग_लिखो_guest(vcpu->kvm, gpa, data, _len);
		अन्यथा
			rc = kvm_पढ़ो_guest(vcpu->kvm, gpa, data, _len);
		len -= _len;
		ga += _len;
		data += _len;
	पूर्ण
	अगर (need_ipte_lock)
		ipte_unlock(vcpu);
	अगर (nr_pages > ARRAY_SIZE(pages_array))
		vमुक्त(pages);
	वापस rc;
पूर्ण

पूर्णांक access_guest_real(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gra,
		      व्योम *data, अचिन्हित दीर्घ len, क्रमागत gacc_mode mode)
अणु
	अचिन्हित दीर्घ _len, gpa;
	पूर्णांक rc = 0;

	जबतक (len && !rc) अणु
		gpa = kvm_s390_real_to_असल(vcpu, gra);
		_len = min(PAGE_SIZE - (gpa & ~PAGE_MASK), len);
		अगर (mode)
			rc = ग_लिखो_guest_असल(vcpu, gpa, data, _len);
		अन्यथा
			rc = पढ़ो_guest_असल(vcpu, gpa, data, _len);
		len -= _len;
		gra += _len;
		data += _len;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * guest_translate_address - translate guest logical पूर्णांकo guest असलolute address
 *
 * Parameter semantics are the same as the ones from guest_translate.
 * The memory contents at the guest address are not changed.
 *
 * Note: The IPTE lock is not taken during this function, so the caller
 * has to take care of this.
 */
पूर्णांक guest_translate_address(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva, u8 ar,
			    अचिन्हित दीर्घ *gpa, क्रमागत gacc_mode mode)
अणु
	psw_t *psw = &vcpu->arch.sie_block->gpsw;
	क्रमागत prot_type prot;
	जोड़ asce asce;
	पूर्णांक rc;

	gva = kvm_s390_logical_to_effective(vcpu, gva);
	rc = get_vcpu_asce(vcpu, &asce, gva, ar, mode);
	अगर (rc)
		वापस rc;
	अगर (is_low_address(gva) && low_address_protection_enabled(vcpu, asce)) अणु
		अगर (mode == GACC_STORE)
			वापस trans_exc(vcpu, PGM_PROTECTION, gva, 0,
					 mode, PROT_TYPE_LA);
	पूर्ण

	अगर (psw_bits(*psw).dat && !asce.r) अणु	/* Use DAT? */
		rc = guest_translate(vcpu, gva, gpa, asce, mode, &prot);
		अगर (rc > 0)
			वापस trans_exc(vcpu, rc, gva, 0, mode, prot);
	पूर्ण अन्यथा अणु
		*gpa = kvm_s390_real_to_असल(vcpu, gva);
		अगर (kvm_is_error_gpa(vcpu->kvm, *gpa))
			वापस trans_exc(vcpu, rc, gva, PGM_ADDRESSING, mode, 0);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * check_gva_range - test a range of guest भव addresses क्रम accessibility
 */
पूर्णांक check_gva_range(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gva, u8 ar,
		    अचिन्हित दीर्घ length, क्रमागत gacc_mode mode)
अणु
	अचिन्हित दीर्घ gpa;
	अचिन्हित दीर्घ currlen;
	पूर्णांक rc = 0;

	ipte_lock(vcpu);
	जबतक (length > 0 && !rc) अणु
		currlen = min(length, PAGE_SIZE - (gva % PAGE_SIZE));
		rc = guest_translate_address(vcpu, gva, ar, &gpa, mode);
		gva += currlen;
		length -= currlen;
	पूर्ण
	ipte_unlock(vcpu);

	वापस rc;
पूर्ण

/**
 * kvm_s390_check_low_addr_prot_real - check क्रम low-address protection
 * @gra: Guest real address
 *
 * Checks whether an address is subject to low-address protection and set
 * up vcpu->arch.pgm accordingly अगर necessary.
 *
 * Return: 0 अगर no protection exception, or PGM_PROTECTION अगर रक्षित.
 */
पूर्णांक kvm_s390_check_low_addr_prot_real(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ gra)
अणु
	जोड़ ctlreg0 ctlreg0 = अणु.val = vcpu->arch.sie_block->gcr[0]पूर्ण;

	अगर (!ctlreg0.lap || !is_low_address(gra))
		वापस 0;
	वापस trans_exc(vcpu, PGM_PROTECTION, gra, 0, GACC_STORE, PROT_TYPE_LA);
पूर्ण

/**
 * kvm_s390_shaकरोw_tables - walk the guest page table and create shaकरोw tables
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @saddr: faulting address in the shaकरोw gmap
 * @pgt: poपूर्णांकer to the beginning of the page table क्रम the given address अगर
 *	 successful (वापस value 0), or to the first invalid DAT entry in
 *	 हाल of exceptions (वापस value > 0)
 * @fake: pgt references contiguous guest memory block, not a pgtable
 */
अटल पूर्णांक kvm_s390_shaकरोw_tables(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr,
				  अचिन्हित दीर्घ *pgt, पूर्णांक *dat_protection,
				  पूर्णांक *fake)
अणु
	काष्ठा gmap *parent;
	जोड़ asce asce;
	जोड़ vaddress vaddr;
	अचिन्हित दीर्घ ptr;
	पूर्णांक rc;

	*fake = 0;
	*dat_protection = 0;
	parent = sg->parent;
	vaddr.addr = saddr;
	asce.val = sg->orig_asce;
	ptr = asce.origin * PAGE_SIZE;
	अगर (asce.r) अणु
		*fake = 1;
		ptr = 0;
		asce.dt = ASCE_TYPE_REGION1;
	पूर्ण
	चयन (asce.dt) अणु
	हाल ASCE_TYPE_REGION1:
		अगर (vaddr.rfx01 > asce.tl && !*fake)
			वापस PGM_REGION_FIRST_TRANS;
		अवरोध;
	हाल ASCE_TYPE_REGION2:
		अगर (vaddr.rfx)
			वापस PGM_ASCE_TYPE;
		अगर (vaddr.rsx01 > asce.tl)
			वापस PGM_REGION_SECOND_TRANS;
		अवरोध;
	हाल ASCE_TYPE_REGION3:
		अगर (vaddr.rfx || vaddr.rsx)
			वापस PGM_ASCE_TYPE;
		अगर (vaddr.rtx01 > asce.tl)
			वापस PGM_REGION_THIRD_TRANS;
		अवरोध;
	हाल ASCE_TYPE_SEGMENT:
		अगर (vaddr.rfx || vaddr.rsx || vaddr.rtx)
			वापस PGM_ASCE_TYPE;
		अगर (vaddr.sx01 > asce.tl)
			वापस PGM_SEGMENT_TRANSLATION;
		अवरोध;
	पूर्ण

	चयन (asce.dt) अणु
	हाल ASCE_TYPE_REGION1: अणु
		जोड़ region1_table_entry rfte;

		अगर (*fake) अणु
			ptr += vaddr.rfx * _REGION1_SIZE;
			rfte.val = ptr;
			जाओ shaकरोw_r2t;
		पूर्ण
		*pgt = ptr + vaddr.rfx * 8;
		rc = gmap_पढ़ो_table(parent, ptr + vaddr.rfx * 8, &rfte.val);
		अगर (rc)
			वापस rc;
		अगर (rfte.i)
			वापस PGM_REGION_FIRST_TRANS;
		अगर (rfte.tt != TABLE_TYPE_REGION1)
			वापस PGM_TRANSLATION_SPEC;
		अगर (vaddr.rsx01 < rfte.tf || vaddr.rsx01 > rfte.tl)
			वापस PGM_REGION_SECOND_TRANS;
		अगर (sg->edat_level >= 1)
			*dat_protection |= rfte.p;
		ptr = rfte.rto * PAGE_SIZE;
shaकरोw_r2t:
		rc = gmap_shaकरोw_r2t(sg, saddr, rfte.val, *fake);
		अगर (rc)
			वापस rc;
	पूर्ण
		fallthrough;
	हाल ASCE_TYPE_REGION2: अणु
		जोड़ region2_table_entry rste;

		अगर (*fake) अणु
			ptr += vaddr.rsx * _REGION2_SIZE;
			rste.val = ptr;
			जाओ shaकरोw_r3t;
		पूर्ण
		*pgt = ptr + vaddr.rsx * 8;
		rc = gmap_पढ़ो_table(parent, ptr + vaddr.rsx * 8, &rste.val);
		अगर (rc)
			वापस rc;
		अगर (rste.i)
			वापस PGM_REGION_SECOND_TRANS;
		अगर (rste.tt != TABLE_TYPE_REGION2)
			वापस PGM_TRANSLATION_SPEC;
		अगर (vaddr.rtx01 < rste.tf || vaddr.rtx01 > rste.tl)
			वापस PGM_REGION_THIRD_TRANS;
		अगर (sg->edat_level >= 1)
			*dat_protection |= rste.p;
		ptr = rste.rto * PAGE_SIZE;
shaकरोw_r3t:
		rste.p |= *dat_protection;
		rc = gmap_shaकरोw_r3t(sg, saddr, rste.val, *fake);
		अगर (rc)
			वापस rc;
	पूर्ण
		fallthrough;
	हाल ASCE_TYPE_REGION3: अणु
		जोड़ region3_table_entry rtte;

		अगर (*fake) अणु
			ptr += vaddr.rtx * _REGION3_SIZE;
			rtte.val = ptr;
			जाओ shaकरोw_sgt;
		पूर्ण
		*pgt = ptr + vaddr.rtx * 8;
		rc = gmap_पढ़ो_table(parent, ptr + vaddr.rtx * 8, &rtte.val);
		अगर (rc)
			वापस rc;
		अगर (rtte.i)
			वापस PGM_REGION_THIRD_TRANS;
		अगर (rtte.tt != TABLE_TYPE_REGION3)
			वापस PGM_TRANSLATION_SPEC;
		अगर (rtte.cr && asce.p && sg->edat_level >= 2)
			वापस PGM_TRANSLATION_SPEC;
		अगर (rtte.fc && sg->edat_level >= 2) अणु
			*dat_protection |= rtte.fc0.p;
			*fake = 1;
			ptr = rtte.fc1.rfaa * _REGION3_SIZE;
			rtte.val = ptr;
			जाओ shaकरोw_sgt;
		पूर्ण
		अगर (vaddr.sx01 < rtte.fc0.tf || vaddr.sx01 > rtte.fc0.tl)
			वापस PGM_SEGMENT_TRANSLATION;
		अगर (sg->edat_level >= 1)
			*dat_protection |= rtte.fc0.p;
		ptr = rtte.fc0.sto * PAGE_SIZE;
shaकरोw_sgt:
		rtte.fc0.p |= *dat_protection;
		rc = gmap_shaकरोw_sgt(sg, saddr, rtte.val, *fake);
		अगर (rc)
			वापस rc;
	पूर्ण
		fallthrough;
	हाल ASCE_TYPE_SEGMENT: अणु
		जोड़ segment_table_entry ste;

		अगर (*fake) अणु
			ptr += vaddr.sx * _SEGMENT_SIZE;
			ste.val = ptr;
			जाओ shaकरोw_pgt;
		पूर्ण
		*pgt = ptr + vaddr.sx * 8;
		rc = gmap_पढ़ो_table(parent, ptr + vaddr.sx * 8, &ste.val);
		अगर (rc)
			वापस rc;
		अगर (ste.i)
			वापस PGM_SEGMENT_TRANSLATION;
		अगर (ste.tt != TABLE_TYPE_SEGMENT)
			वापस PGM_TRANSLATION_SPEC;
		अगर (ste.cs && asce.p)
			वापस PGM_TRANSLATION_SPEC;
		*dat_protection |= ste.fc0.p;
		अगर (ste.fc && sg->edat_level >= 1) अणु
			*fake = 1;
			ptr = ste.fc1.sfaa * _SEGMENT_SIZE;
			ste.val = ptr;
			जाओ shaकरोw_pgt;
		पूर्ण
		ptr = ste.fc0.pto * (PAGE_SIZE / 2);
shaकरोw_pgt:
		ste.fc0.p |= *dat_protection;
		rc = gmap_shaकरोw_pgt(sg, saddr, ste.val, *fake);
		अगर (rc)
			वापस rc;
	पूर्ण
	पूर्ण
	/* Return the parent address of the page table */
	*pgt = ptr;
	वापस 0;
पूर्ण

/**
 * kvm_s390_shaकरोw_fault - handle fault on a shaकरोw page table
 * @vcpu: भव cpu
 * @sg: poपूर्णांकer to the shaकरोw guest address space काष्ठाure
 * @saddr: faulting address in the shaकरोw gmap
 * @datptr: will contain the address of the faulting DAT table entry, or of
 *	    the valid leaf, plus some flags
 *
 * Returns: - 0 अगर the shaकरोw fault was successfully resolved
 *	    - > 0 (pgm exception code) on exceptions जबतक faulting
 *	    - -EAGAIN अगर the caller can retry immediately
 *	    - -EFAULT when accessing invalid guest addresses
 *	    - -ENOMEM अगर out of memory
 */
पूर्णांक kvm_s390_shaकरोw_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा gmap *sg,
			  अचिन्हित दीर्घ saddr, अचिन्हित दीर्घ *datptr)
अणु
	जोड़ vaddress vaddr;
	जोड़ page_table_entry pte;
	अचिन्हित दीर्घ pgt = 0;
	पूर्णांक dat_protection, fake;
	पूर्णांक rc;

	mmap_पढ़ो_lock(sg->mm);
	/*
	 * We करोn't want any guest-2 tables to change - so the parent
	 * tables/poपूर्णांकers we पढ़ो stay valid - unshaकरोwing is however
	 * always possible - only guest_table_lock protects us.
	 */
	ipte_lock(vcpu);

	rc = gmap_shaकरोw_pgt_lookup(sg, saddr, &pgt, &dat_protection, &fake);
	अगर (rc)
		rc = kvm_s390_shaकरोw_tables(sg, saddr, &pgt, &dat_protection,
					    &fake);

	vaddr.addr = saddr;
	अगर (fake) अणु
		pte.val = pgt + vaddr.px * PAGE_SIZE;
		जाओ shaकरोw_page;
	पूर्ण

	चयन (rc) अणु
	हाल PGM_SEGMENT_TRANSLATION:
	हाल PGM_REGION_THIRD_TRANS:
	हाल PGM_REGION_SECOND_TRANS:
	हाल PGM_REGION_FIRST_TRANS:
		pgt |= PEI_NOT_PTE;
		अवरोध;
	हाल 0:
		pgt += vaddr.px * 8;
		rc = gmap_पढ़ो_table(sg->parent, pgt, &pte.val);
	पूर्ण
	अगर (datptr)
		*datptr = pgt | dat_protection * PEI_DAT_PROT;
	अगर (!rc && pte.i)
		rc = PGM_PAGE_TRANSLATION;
	अगर (!rc && pte.z)
		rc = PGM_TRANSLATION_SPEC;
shaकरोw_page:
	pte.p |= dat_protection;
	अगर (!rc)
		rc = gmap_shaकरोw_page(sg, saddr, __pte(pte.val));
	ipte_unlock(vcpu);
	mmap_पढ़ो_unlock(sg->mm);
	वापस rc;
पूर्ण
