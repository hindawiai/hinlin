<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kvm guest debug support
 *
 * Copyright IBM Corp. 2014
 *
 *    Author(s): David Hildenbअक्रम <dahi@linux.vnet.ibm.com>
 */
#समावेश <linux/kvm_host.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश "kvm-s390.h"
#समावेश "gaccess.h"

/*
 * Extends the address range given by *start and *stop to include the address
 * range starting with estart and the length len. Takes care of overflowing
 * पूर्णांकervals and tries to minimize the overall पूर्णांकerval size.
 */
अटल व्योम extend_address_range(u64 *start, u64 *stop, u64 estart, पूर्णांक len)
अणु
	u64 estop;

	अगर (len > 0)
		len--;
	अन्यथा
		len = 0;

	estop = estart + len;

	/* 0-0 range represents "not set" */
	अगर ((*start == 0) && (*stop == 0)) अणु
		*start = estart;
		*stop = estop;
	पूर्ण अन्यथा अगर (*start <= *stop) अणु
		/* increase the existing range */
		अगर (estart < *start)
			*start = estart;
		अगर (estop > *stop)
			*stop = estop;
	पूर्ण अन्यथा अणु
		/* "overflowing" पूर्णांकerval, whereby *stop > *start */
		अगर (estart <= *stop) अणु
			अगर (estop > *stop)
				*stop = estop;
		पूर्ण अन्यथा अगर (estop > *start) अणु
			अगर (estart < *start)
				*start = estart;
		पूर्ण
		/* minimize the range */
		अन्यथा अगर ((estop - *stop) < (*start - estart))
			*stop = estop;
		अन्यथा
			*start = estart;
	पूर्ण
पूर्ण

#घोषणा MAX_INST_SIZE 6

अटल व्योम enable_all_hw_bp(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ start, len;
	u64 *cr9 = &vcpu->arch.sie_block->gcr[9];
	u64 *cr10 = &vcpu->arch.sie_block->gcr[10];
	u64 *cr11 = &vcpu->arch.sie_block->gcr[11];
	पूर्णांक i;

	अगर (vcpu->arch.guestdbg.nr_hw_bp <= 0 ||
	    vcpu->arch.guestdbg.hw_bp_info == शून्य)
		वापस;

	/*
	 * If the guest is not पूर्णांकerested in branching events, we can safely
	 * limit them to the PER address range.
	 */
	अगर (!(*cr9 & PER_EVENT_BRANCH))
		*cr9 |= PER_CONTROL_BRANCH_ADDRESS;
	*cr9 |= PER_EVENT_IFETCH | PER_EVENT_BRANCH;

	क्रम (i = 0; i < vcpu->arch.guestdbg.nr_hw_bp; i++) अणु
		start = vcpu->arch.guestdbg.hw_bp_info[i].addr;
		len = vcpu->arch.guestdbg.hw_bp_info[i].len;

		/*
		 * The inकाष्ठाion in front of the desired bp has to
		 * report inकाष्ठाion-fetching events
		 */
		अगर (start < MAX_INST_SIZE) अणु
			len += start;
			start = 0;
		पूर्ण अन्यथा अणु
			start -= MAX_INST_SIZE;
			len += MAX_INST_SIZE;
		पूर्ण

		extend_address_range(cr10, cr11, start, len);
	पूर्ण
पूर्ण

अटल व्योम enable_all_hw_wp(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ start, len;
	u64 *cr9 = &vcpu->arch.sie_block->gcr[9];
	u64 *cr10 = &vcpu->arch.sie_block->gcr[10];
	u64 *cr11 = &vcpu->arch.sie_block->gcr[11];
	पूर्णांक i;

	अगर (vcpu->arch.guestdbg.nr_hw_wp <= 0 ||
	    vcpu->arch.guestdbg.hw_wp_info == शून्य)
		वापस;

	/* अगर host uses storage alternation क्रम special address
	 * spaces, enable all events and give all to the guest */
	अगर (*cr9 & PER_EVENT_STORE && *cr9 & PER_CONTROL_ALTERATION) अणु
		*cr9 &= ~PER_CONTROL_ALTERATION;
		*cr10 = 0;
		*cr11 = -1UL;
	पूर्ण अन्यथा अणु
		*cr9 &= ~PER_CONTROL_ALTERATION;
		*cr9 |= PER_EVENT_STORE;

		क्रम (i = 0; i < vcpu->arch.guestdbg.nr_hw_wp; i++) अणु
			start = vcpu->arch.guestdbg.hw_wp_info[i].addr;
			len = vcpu->arch.guestdbg.hw_wp_info[i].len;

			extend_address_range(cr10, cr11, start, len);
		पूर्ण
	पूर्ण
पूर्ण

व्योम kvm_s390_backup_guest_per_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.guestdbg.cr0 = vcpu->arch.sie_block->gcr[0];
	vcpu->arch.guestdbg.cr9 = vcpu->arch.sie_block->gcr[9];
	vcpu->arch.guestdbg.cr10 = vcpu->arch.sie_block->gcr[10];
	vcpu->arch.guestdbg.cr11 = vcpu->arch.sie_block->gcr[11];
पूर्ण

व्योम kvm_s390_restore_guest_per_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.sie_block->gcr[0] = vcpu->arch.guestdbg.cr0;
	vcpu->arch.sie_block->gcr[9] = vcpu->arch.guestdbg.cr9;
	vcpu->arch.sie_block->gcr[10] = vcpu->arch.guestdbg.cr10;
	vcpu->arch.sie_block->gcr[11] = vcpu->arch.guestdbg.cr11;
पूर्ण

व्योम kvm_s390_patch_guest_per_regs(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * TODO: अगर guest psw has per enabled, otherwise 0s!
	 * This reduces the amount of reported events.
	 * Need to पूर्णांकercept all psw changes!
	 */

	अगर (guestdbg_sstep_enabled(vcpu)) अणु
		/* disable समयr (घड़ी-comparator) पूर्णांकerrupts */
		vcpu->arch.sie_block->gcr[0] &= ~CR0_CLOCK_COMPARATOR_SUBMASK;
		vcpu->arch.sie_block->gcr[9] |= PER_EVENT_IFETCH;
		vcpu->arch.sie_block->gcr[10] = 0;
		vcpu->arch.sie_block->gcr[11] = -1UL;
	पूर्ण

	अगर (guestdbg_hw_bp_enabled(vcpu)) अणु
		enable_all_hw_bp(vcpu);
		enable_all_hw_wp(vcpu);
	पूर्ण

	/* TODO: Inकाष्ठाion-fetching-nullअगरication not allowed क्रम now */
	अगर (vcpu->arch.sie_block->gcr[9] & PER_EVENT_शून्यIFICATION)
		vcpu->arch.sie_block->gcr[9] &= ~PER_EVENT_शून्यIFICATION;
पूर्ण

#घोषणा MAX_WP_SIZE 100

अटल पूर्णांक __import_wp_info(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_hw_अवरोधpoपूर्णांक *bp_data,
			    काष्ठा kvm_hw_wp_info_arch *wp_info)
अणु
	पूर्णांक ret = 0;
	wp_info->len = bp_data->len;
	wp_info->addr = bp_data->addr;
	wp_info->phys_addr = bp_data->phys_addr;
	wp_info->old_data = शून्य;

	अगर (wp_info->len < 0 || wp_info->len > MAX_WP_SIZE)
		वापस -EINVAL;

	wp_info->old_data = kदो_स्मृति(bp_data->len, GFP_KERNEL_ACCOUNT);
	अगर (!wp_info->old_data)
		वापस -ENOMEM;
	/* try to backup the original value */
	ret = पढ़ो_guest_असल(vcpu, wp_info->phys_addr, wp_info->old_data,
			     wp_info->len);
	अगर (ret) अणु
		kमुक्त(wp_info->old_data);
		wp_info->old_data = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा MAX_BP_COUNT 50

पूर्णांक kvm_s390_import_bp_data(काष्ठा kvm_vcpu *vcpu,
			    काष्ठा kvm_guest_debug *dbg)
अणु
	पूर्णांक ret = 0, nr_wp = 0, nr_bp = 0, i;
	काष्ठा kvm_hw_अवरोधpoपूर्णांक *bp_data = शून्य;
	काष्ठा kvm_hw_wp_info_arch *wp_info = शून्य;
	काष्ठा kvm_hw_bp_info_arch *bp_info = शून्य;

	अगर (dbg->arch.nr_hw_bp <= 0 || !dbg->arch.hw_bp)
		वापस 0;
	अन्यथा अगर (dbg->arch.nr_hw_bp > MAX_BP_COUNT)
		वापस -EINVAL;

	bp_data = memdup_user(dbg->arch.hw_bp,
			      माप(*bp_data) * dbg->arch.nr_hw_bp);
	अगर (IS_ERR(bp_data))
		वापस PTR_ERR(bp_data);

	क्रम (i = 0; i < dbg->arch.nr_hw_bp; i++) अणु
		चयन (bp_data[i].type) अणु
		हाल KVM_HW_WP_WRITE:
			nr_wp++;
			अवरोध;
		हाल KVM_HW_BP:
			nr_bp++;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nr_wp > 0) अणु
		wp_info = kदो_स्मृति_array(nr_wp,
					माप(*wp_info),
					GFP_KERNEL_ACCOUNT);
		अगर (!wp_info) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण
	अगर (nr_bp > 0) अणु
		bp_info = kदो_स्मृति_array(nr_bp,
					माप(*bp_info),
					GFP_KERNEL_ACCOUNT);
		अगर (!bp_info) अणु
			ret = -ENOMEM;
			जाओ error;
		पूर्ण
	पूर्ण

	क्रम (nr_wp = 0, nr_bp = 0, i = 0; i < dbg->arch.nr_hw_bp; i++) अणु
		चयन (bp_data[i].type) अणु
		हाल KVM_HW_WP_WRITE:
			ret = __import_wp_info(vcpu, &bp_data[i],
					       &wp_info[nr_wp]);
			अगर (ret)
				जाओ error;
			nr_wp++;
			अवरोध;
		हाल KVM_HW_BP:
			bp_info[nr_bp].len = bp_data[i].len;
			bp_info[nr_bp].addr = bp_data[i].addr;
			nr_bp++;
			अवरोध;
		पूर्ण
	पूर्ण

	vcpu->arch.guestdbg.nr_hw_bp = nr_bp;
	vcpu->arch.guestdbg.hw_bp_info = bp_info;
	vcpu->arch.guestdbg.nr_hw_wp = nr_wp;
	vcpu->arch.guestdbg.hw_wp_info = wp_info;
	वापस 0;
error:
	kमुक्त(bp_data);
	kमुक्त(wp_info);
	kमुक्त(bp_info);
	वापस ret;
पूर्ण

व्योम kvm_s390_clear_bp_data(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	काष्ठा kvm_hw_wp_info_arch *hw_wp_info = शून्य;

	क्रम (i = 0; i < vcpu->arch.guestdbg.nr_hw_wp; i++) अणु
		hw_wp_info = &vcpu->arch.guestdbg.hw_wp_info[i];
		kमुक्त(hw_wp_info->old_data);
		hw_wp_info->old_data = शून्य;
	पूर्ण
	kमुक्त(vcpu->arch.guestdbg.hw_wp_info);
	vcpu->arch.guestdbg.hw_wp_info = शून्य;

	kमुक्त(vcpu->arch.guestdbg.hw_bp_info);
	vcpu->arch.guestdbg.hw_bp_info = शून्य;

	vcpu->arch.guestdbg.nr_hw_wp = 0;
	vcpu->arch.guestdbg.nr_hw_bp = 0;
पूर्ण

अटल अंतरभूत पूर्णांक in_addr_range(u64 addr, u64 a, u64 b)
अणु
	अगर (a <= b)
		वापस (addr >= a) && (addr <= b);
	अन्यथा
		/* "overflowing" पूर्णांकerval */
		वापस (addr >= a) || (addr <= b);
पूर्ण

#घोषणा end_of_range(bp_info) (bp_info->addr + bp_info->len - 1)

अटल काष्ठा kvm_hw_bp_info_arch *find_hw_bp(काष्ठा kvm_vcpu *vcpu,
					      अचिन्हित दीर्घ addr)
अणु
	काष्ठा kvm_hw_bp_info_arch *bp_info = vcpu->arch.guestdbg.hw_bp_info;
	पूर्णांक i;

	अगर (vcpu->arch.guestdbg.nr_hw_bp == 0)
		वापस शून्य;

	क्रम (i = 0; i < vcpu->arch.guestdbg.nr_hw_bp; i++) अणु
		/* addr is directly the start or in the range of a bp */
		अगर (addr == bp_info->addr)
			जाओ found;
		अगर (bp_info->len > 0 &&
		    in_addr_range(addr, bp_info->addr, end_of_range(bp_info)))
			जाओ found;

		bp_info++;
	पूर्ण

	वापस शून्य;
found:
	वापस bp_info;
पूर्ण

अटल काष्ठा kvm_hw_wp_info_arch *any_wp_changed(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक i;
	काष्ठा kvm_hw_wp_info_arch *wp_info = शून्य;
	व्योम *temp = शून्य;

	अगर (vcpu->arch.guestdbg.nr_hw_wp == 0)
		वापस शून्य;

	क्रम (i = 0; i < vcpu->arch.guestdbg.nr_hw_wp; i++) अणु
		wp_info = &vcpu->arch.guestdbg.hw_wp_info[i];
		अगर (!wp_info || !wp_info->old_data || wp_info->len <= 0)
			जारी;

		temp = kदो_स्मृति(wp_info->len, GFP_KERNEL_ACCOUNT);
		अगर (!temp)
			जारी;

		/* refetch the wp data and compare it to the old value */
		अगर (!पढ़ो_guest_असल(vcpu, wp_info->phys_addr, temp,
				    wp_info->len)) अणु
			अगर (स_भेद(temp, wp_info->old_data, wp_info->len)) अणु
				kमुक्त(temp);
				वापस wp_info;
			पूर्ण
		पूर्ण
		kमुक्त(temp);
		temp = शून्य;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम kvm_s390_prepare_debug_निकास(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->run->निकास_reason = KVM_EXIT_DEBUG;
	vcpu->guest_debug &= ~KVM_GUESTDBG_EXIT_PENDING;
पूर्ण

#घोषणा PER_CODE_MASK		(PER_EVENT_MASK >> 24)
#घोषणा PER_CODE_BRANCH		(PER_EVENT_BRANCH >> 24)
#घोषणा PER_CODE_IFETCH		(PER_EVENT_IFETCH >> 24)
#घोषणा PER_CODE_STORE		(PER_EVENT_STORE >> 24)
#घोषणा PER_CODE_STORE_REAL	(PER_EVENT_STORE_REAL >> 24)

#घोषणा per_bp_event(code) \
			(code & (PER_CODE_IFETCH | PER_CODE_BRANCH))
#घोषणा per_ग_लिखो_wp_event(code) \
			(code & (PER_CODE_STORE | PER_CODE_STORE_REAL))

अटल पूर्णांक debug_निकास_required(काष्ठा kvm_vcpu *vcpu, u8 perc,
			       अचिन्हित दीर्घ peraddr)
अणु
	काष्ठा kvm_debug_निकास_arch *debug_निकास = &vcpu->run->debug.arch;
	काष्ठा kvm_hw_wp_info_arch *wp_info = शून्य;
	काष्ठा kvm_hw_bp_info_arch *bp_info = शून्य;
	अचिन्हित दीर्घ addr = vcpu->arch.sie_block->gpsw.addr;

	अगर (guestdbg_hw_bp_enabled(vcpu)) अणु
		अगर (per_ग_लिखो_wp_event(perc) &&
		    vcpu->arch.guestdbg.nr_hw_wp > 0) अणु
			wp_info = any_wp_changed(vcpu);
			अगर (wp_info) अणु
				debug_निकास->addr = wp_info->addr;
				debug_निकास->type = KVM_HW_WP_WRITE;
				जाओ निकास_required;
			पूर्ण
		पूर्ण
		अगर (per_bp_event(perc) &&
			 vcpu->arch.guestdbg.nr_hw_bp > 0) अणु
			bp_info = find_hw_bp(vcpu, addr);
			/* हटाओ duplicate events अगर PC==PER address */
			अगर (bp_info && (addr != peraddr)) अणु
				debug_निकास->addr = addr;
				debug_निकास->type = KVM_HW_BP;
				vcpu->arch.guestdbg.last_bp = addr;
				जाओ निकास_required;
			पूर्ण
			/* अवरोधpoपूर्णांक missed */
			bp_info = find_hw_bp(vcpu, peraddr);
			अगर (bp_info && vcpu->arch.guestdbg.last_bp != peraddr) अणु
				debug_निकास->addr = peraddr;
				debug_निकास->type = KVM_HW_BP;
				जाओ निकास_required;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (guestdbg_sstep_enabled(vcpu) && per_bp_event(perc)) अणु
		debug_निकास->addr = addr;
		debug_निकास->type = KVM_SINGLESTEP;
		जाओ निकास_required;
	पूर्ण

	वापस 0;
निकास_required:
	वापस 1;
पूर्ण

अटल पूर्णांक per_fetched_addr(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ *addr)
अणु
	u8 exec_ilen = 0;
	u16 opcode[3];
	पूर्णांक rc;

	अगर (vcpu->arch.sie_block->icptcode == ICPT_PROGI) अणु
		/* PER address references the fetched or the execute instr */
		*addr = vcpu->arch.sie_block->peraddr;
		/*
		 * Manually detect अगर we have an EXECUTE inकाष्ठाion. As
		 * inकाष्ठाions are always 2 byte aligned we can पढ़ो the
		 * first two bytes unconditionally
		 */
		rc = पढ़ो_guest_instr(vcpu, *addr, &opcode, 2);
		अगर (rc)
			वापस rc;
		अगर (opcode[0] >> 8 == 0x44)
			exec_ilen = 4;
		अगर ((opcode[0] & 0xff0f) == 0xc600)
			exec_ilen = 6;
	पूर्ण अन्यथा अणु
		/* instr was suppressed, calculate the responsible instr */
		*addr = __शुरुआत_psw(vcpu->arch.sie_block->gpsw,
				     kvm_s390_get_ilen(vcpu));
		अगर (vcpu->arch.sie_block->icptstatus & 0x01) अणु
			exec_ilen = (vcpu->arch.sie_block->icptstatus & 0x60) >> 4;
			अगर (!exec_ilen)
				exec_ilen = 4;
		पूर्ण
	पूर्ण

	अगर (exec_ilen) अणु
		/* पढ़ो the complete EXECUTE instr to detect the fetched addr */
		rc = पढ़ो_guest_instr(vcpu, *addr, &opcode, exec_ilen);
		अगर (rc)
			वापस rc;
		अगर (exec_ilen == 6) अणु
			/* EXECUTE RELATIVE LONG - RIL-b क्रमmat */
			s32 rl = *((s32 *) (opcode + 1));

			/* rl is a _चिन्हित_ 32 bit value specअगरying halfwords */
			*addr += (u64)(s64) rl * 2;
		पूर्ण अन्यथा अणु
			/* EXECUTE - RX-a क्रमmat */
			u32 base = (opcode[1] & 0xf000) >> 12;
			u32 disp = opcode[1] & 0x0fff;
			u32 index = opcode[0] & 0x000f;

			*addr = base ? vcpu->run->s.regs.gprs[base] : 0;
			*addr += index ? vcpu->run->s.regs.gprs[index] : 0;
			*addr += disp;
		पूर्ण
		*addr = kvm_s390_logical_to_effective(vcpu, *addr);
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा guest_per_enabled(vcpu) \
			     (vcpu->arch.sie_block->gpsw.mask & PSW_MASK_PER)

पूर्णांक kvm_s390_handle_per_अगरetch_icpt(काष्ठा kvm_vcpu *vcpu)
अणु
	स्थिर u64 cr10 = vcpu->arch.sie_block->gcr[10];
	स्थिर u64 cr11 = vcpu->arch.sie_block->gcr[11];
	स्थिर u8 ilen = kvm_s390_get_ilen(vcpu);
	काष्ठा kvm_s390_pgm_info pgm_info = अणु
		.code = PGM_PER,
		.per_code = PER_CODE_IFETCH,
		.per_address = __शुरुआत_psw(vcpu->arch.sie_block->gpsw, ilen),
	पूर्ण;
	अचिन्हित दीर्घ fetched_addr;
	पूर्णांक rc;

	/*
	 * The PSW poपूर्णांकs to the next inकाष्ठाion, thereक्रमe the पूर्णांकercepted
	 * inकाष्ठाion generated a PER i-fetch event. PER address thereक्रमe
	 * poपूर्णांकs at the previous PSW address (could be an EXECUTE function).
	 */
	अगर (!guestdbg_enabled(vcpu))
		वापस kvm_s390_inject_prog_irq(vcpu, &pgm_info);

	अगर (debug_निकास_required(vcpu, pgm_info.per_code, pgm_info.per_address))
		vcpu->guest_debug |= KVM_GUESTDBG_EXIT_PENDING;

	अगर (!guest_per_enabled(vcpu) ||
	    !(vcpu->arch.sie_block->gcr[9] & PER_EVENT_IFETCH))
		वापस 0;

	rc = per_fetched_addr(vcpu, &fetched_addr);
	अगर (rc < 0)
		वापस rc;
	अगर (rc)
		/* inकाष्ठाion-fetching exceptions */
		वापस kvm_s390_inject_program_पूर्णांक(vcpu, PGM_ADDRESSING);

	अगर (in_addr_range(fetched_addr, cr10, cr11))
		वापस kvm_s390_inject_prog_irq(vcpu, &pgm_info);
	वापस 0;
पूर्ण

अटल पूर्णांक filter_guest_per_event(काष्ठा kvm_vcpu *vcpu)
अणु
	स्थिर u8 perc = vcpu->arch.sie_block->perc;
	u64 addr = vcpu->arch.sie_block->gpsw.addr;
	u64 cr9 = vcpu->arch.sie_block->gcr[9];
	u64 cr10 = vcpu->arch.sie_block->gcr[10];
	u64 cr11 = vcpu->arch.sie_block->gcr[11];
	/* filter all events, demanded by the guest */
	u8 guest_perc = perc & (cr9 >> 24) & PER_CODE_MASK;
	अचिन्हित दीर्घ fetched_addr;
	पूर्णांक rc;

	अगर (!guest_per_enabled(vcpu))
		guest_perc = 0;

	/* filter "successful-branching" events */
	अगर (guest_perc & PER_CODE_BRANCH &&
	    cr9 & PER_CONTROL_BRANCH_ADDRESS &&
	    !in_addr_range(addr, cr10, cr11))
		guest_perc &= ~PER_CODE_BRANCH;

	/* filter "instruction-fetching" events */
	अगर (guest_perc & PER_CODE_IFETCH) अणु
		rc = per_fetched_addr(vcpu, &fetched_addr);
		अगर (rc < 0)
			वापस rc;
		/*
		 * Don't inject an irq on exceptions. This would make handling
		 * on icpt code 8 very complex (as PSW was alपढ़ोy rewound).
		 */
		अगर (rc || !in_addr_range(fetched_addr, cr10, cr11))
			guest_perc &= ~PER_CODE_IFETCH;
	पूर्ण

	/* All other PER events will be given to the guest */
	/* TODO: Check altered address/address space */

	vcpu->arch.sie_block->perc = guest_perc;

	अगर (!guest_perc)
		vcpu->arch.sie_block->iprcc &= ~PGM_PER;
	वापस 0;
पूर्ण

#घोषणा pssec(vcpu) (vcpu->arch.sie_block->gcr[1] & _ASCE_SPACE_SWITCH)
#घोषणा hssec(vcpu) (vcpu->arch.sie_block->gcr[13] & _ASCE_SPACE_SWITCH)
#घोषणा old_ssec(vcpu) ((vcpu->arch.sie_block->tecmc >> 31) & 0x1)
#घोषणा old_as_is_home(vcpu) !(vcpu->arch.sie_block->tecmc & 0xffff)

पूर्णांक kvm_s390_handle_per_event(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक rc, new_as;

	अगर (debug_निकास_required(vcpu, vcpu->arch.sie_block->perc,
				vcpu->arch.sie_block->peraddr))
		vcpu->guest_debug |= KVM_GUESTDBG_EXIT_PENDING;

	rc = filter_guest_per_event(vcpu);
	अगर (rc)
		वापस rc;

	/*
	 * Only RP, SAC, SACF, PT, PTI, PR, PC inकाष्ठाions can trigger
	 * a space-चयन event. PER events enक्रमce space-चयन events
	 * क्रम these inकाष्ठाions. So अगर no PER event क्रम the guest is left,
	 * we might have to filter the space-चयन element out, too.
	 */
	अगर (vcpu->arch.sie_block->iprcc == PGM_SPACE_SWITCH) अणु
		vcpu->arch.sie_block->iprcc = 0;
		new_as = psw_bits(vcpu->arch.sie_block->gpsw).as;

		/*
		 * If the AS changed from / to home, we had RP, SAC or SACF
		 * inकाष्ठाion. Check primary and home space-चयन-event
		 * controls. (theoretically home -> home produced no event)
		 */
		अगर (((new_as == PSW_BITS_AS_HOME) ^ old_as_is_home(vcpu)) &&
		    (pssec(vcpu) || hssec(vcpu)))
			vcpu->arch.sie_block->iprcc = PGM_SPACE_SWITCH;

		/*
		 * PT, PTI, PR, PC inकाष्ठाion operate on primary AS only. Check
		 * अगर the primary-space-चयन-event control was or got set.
		 */
		अगर (new_as == PSW_BITS_AS_PRIMARY && !old_as_is_home(vcpu) &&
		    (pssec(vcpu) || old_ssec(vcpu)))
			vcpu->arch.sie_block->iprcc = PGM_SPACE_SWITCH;
	पूर्ण
	वापस 0;
पूर्ण
