<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Kernel support क्रम the ptrace() and syscall tracing पूर्णांकerfaces.
 *
 * Copyright (C) 1999-2005 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 2006 Intel Co
 *  2006-08-12	- IA64 Native Utrace implementation support added by
 *	Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 *
 * Derived from the x86 and Alpha versions.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/security.h>
#समावेश <linux/audit.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/regset.h>
#समावेश <linux/elf.h>
#समावेश <linux/tracehook.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace_offsets.h>
#समावेश <यंत्र/rse.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unwind.h>

#समावेश "entry.h"

/*
 * Bits in the PSR that we allow ptrace() to change:
 *	be, up, ac, mfl, mfh (the user mask; five bits total)
 *	db (debug अवरोधpoपूर्णांक fault; one bit)
 *	id (inकाष्ठाion debug fault disable; one bit)
 *	dd (data debug fault disable; one bit)
 *	ri (restart inकाष्ठाion; two bits)
 *	is (inकाष्ठाion set; one bit)
 */
#घोषणा IPSR_MASK (IA64_PSR_UM | IA64_PSR_DB | IA64_PSR_IS	\
		   | IA64_PSR_ID | IA64_PSR_DD | IA64_PSR_RI)

#घोषणा MASK(nbits)	((1UL << (nbits)) - 1)	/* mask with NBITS bits set */
#घोषणा PFM_MASK	MASK(38)

#घोषणा PTRACE_DEBUG	0

#अगर PTRACE_DEBUG
# define dprपूर्णांकk(क्रमmat...)	prपूर्णांकk(क्रमmat)
# define अंतरभूत
#अन्यथा
# define dprपूर्णांकk(क्रमmat...)
#पूर्ण_अगर

/* Return TRUE अगर PT was created due to kernel-entry via a प्रणाली-call.  */

अटल अंतरभूत पूर्णांक
in_syscall (काष्ठा pt_regs *pt)
अणु
	वापस (दीर्घ) pt->cr_अगरs >= 0;
पूर्ण

/*
 * Collect the NaT bits क्रम r1-r31 from scratch_unat and वापस a NaT
 * bitset where bit i is set अगरf the NaT bit of रेजिस्टर i is set.
 */
अचिन्हित दीर्घ
ia64_get_scratch_nat_bits (काष्ठा pt_regs *pt, अचिन्हित दीर्घ scratch_unat)
अणु
#	define GET_BITS(first, last, unat)				\
	(अणु								\
		अचिन्हित दीर्घ bit = ia64_unat_pos(&pt->r##first);	\
		अचिन्हित दीर्घ nbits = (last - first + 1);		\
		अचिन्हित दीर्घ mask = MASK(nbits) << first;		\
		अचिन्हित दीर्घ dist;					\
		अगर (bit < first)					\
			dist = 64 + bit - first;			\
		अन्यथा							\
			dist = bit - first;				\
		ia64_rotr(unat, dist) & mask;				\
	पूर्ण)
	अचिन्हित दीर्घ val;

	/*
	 * Registers that are stored consecutively in काष्ठा pt_regs
	 * can be handled in parallel.  If the रेजिस्टर order in
	 * काष्ठा_pt_regs changes, this code MUST be updated.
	 */
	val  = GET_BITS( 1,  1, scratch_unat);
	val |= GET_BITS( 2,  3, scratch_unat);
	val |= GET_BITS(12, 13, scratch_unat);
	val |= GET_BITS(14, 14, scratch_unat);
	val |= GET_BITS(15, 15, scratch_unat);
	val |= GET_BITS( 8, 11, scratch_unat);
	val |= GET_BITS(16, 31, scratch_unat);
	वापस val;

#	undef GET_BITS
पूर्ण

/*
 * Set the NaT bits क्रम the scratch रेजिस्टरs according to NAT and
 * वापस the resulting unat (assuming the scratch रेजिस्टरs are
 * stored in PT).
 */
अचिन्हित दीर्घ
ia64_put_scratch_nat_bits (काष्ठा pt_regs *pt, अचिन्हित दीर्घ nat)
अणु
#	define PUT_BITS(first, last, nat)				\
	(अणु								\
		अचिन्हित दीर्घ bit = ia64_unat_pos(&pt->r##first);	\
		अचिन्हित दीर्घ nbits = (last - first + 1);		\
		अचिन्हित दीर्घ mask = MASK(nbits) << first;		\
		दीर्घ dist;						\
		अगर (bit < first)					\
			dist = 64 + bit - first;			\
		अन्यथा							\
			dist = bit - first;				\
		ia64_rotl(nat & mask, dist);				\
	पूर्ण)
	अचिन्हित दीर्घ scratch_unat;

	/*
	 * Registers that are stored consecutively in काष्ठा pt_regs
	 * can be handled in parallel.  If the रेजिस्टर order in
	 * काष्ठा_pt_regs changes, this code MUST be updated.
	 */
	scratch_unat  = PUT_BITS( 1,  1, nat);
	scratch_unat |= PUT_BITS( 2,  3, nat);
	scratch_unat |= PUT_BITS(12, 13, nat);
	scratch_unat |= PUT_BITS(14, 14, nat);
	scratch_unat |= PUT_BITS(15, 15, nat);
	scratch_unat |= PUT_BITS( 8, 11, nat);
	scratch_unat |= PUT_BITS(16, 31, nat);

	वापस scratch_unat;

#	undef PUT_BITS
पूर्ण

#घोषणा IA64_MLX_TEMPLATE	0x2
#घोषणा IA64_MOVL_OPCODE	6

व्योम
ia64_increment_ip (काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ w0, ri = ia64_psr(regs)->ri + 1;

	अगर (ri > 2) अणु
		ri = 0;
		regs->cr_iip += 16;
	पूर्ण अन्यथा अगर (ri == 2) अणु
		get_user(w0, (अक्षर __user *) regs->cr_iip + 0);
		अगर (((w0 >> 1) & 0xf) == IA64_MLX_TEMPLATE) अणु
			/*
			 * rfi'ing to slot 2 of an MLX bundle causes
			 * an illegal operation fault.  We करोn't want
			 * that to happen...
			 */
			ri = 0;
			regs->cr_iip += 16;
		पूर्ण
	पूर्ण
	ia64_psr(regs)->ri = ri;
पूर्ण

व्योम
ia64_decrement_ip (काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ w0, ri = ia64_psr(regs)->ri - 1;

	अगर (ia64_psr(regs)->ri == 0) अणु
		regs->cr_iip -= 16;
		ri = 2;
		get_user(w0, (अक्षर __user *) regs->cr_iip + 0);
		अगर (((w0 >> 1) & 0xf) == IA64_MLX_TEMPLATE) अणु
			/*
			 * rfi'ing to slot 2 of an MLX bundle causes
			 * an illegal operation fault.  We करोn't want
			 * that to happen...
			 */
			ri = 1;
		पूर्ण
	पूर्ण
	ia64_psr(regs)->ri = ri;
पूर्ण

/*
 * This routine is used to पढ़ो an rnat bits that are stored on the
 * kernel backing store.  Since, in general, the alignment of the user
 * and kernel are dअगरferent, this is not completely trivial.  In
 * essence, we need to स्थिरruct the user RNAT based on up to two
 * kernel RNAT values and/or the RNAT value saved in the child's
 * pt_regs.
 *
 * user rbs
 *
 * +--------+ <-- lowest address
 * | slot62 |
 * +--------+
 * |  rnat  | 0x....1f8
 * +--------+
 * | slot00 | \
 * +--------+ |
 * | slot01 | > child_regs->ar_rnat
 * +--------+ |
 * | slot02 | /				kernel rbs
 * +--------+				+--------+
 *	    <- child_regs->ar_bspstore	| slot61 | <-- krbs
 * +- - - - +				+--------+
 *					| slot62 |
 * +- - - - +				+--------+
 *					|  rnat	 |
 * +- - - - +				+--------+
 *   vrnat				| slot00 |
 * +- - - - +				+--------+
 *					=	 =
 *					+--------+
 *					| slot00 | \
 *					+--------+ |
 *					| slot01 | > child_stack->ar_rnat
 *					+--------+ |
 *					| slot02 | /
 *					+--------+
 *						  <--- child_stack->ar_bspstore
 *
 * The way to think of this code is as follows: bit 0 in the user rnat
 * corresponds to some bit N (0 <= N <= 62) in one of the kernel rnat
 * value.  The kernel rnat value holding this bit is stored in
 * variable rnat0.  rnat1 is loaded with the kernel rnat value that
 * क्रमm the upper bits of the user rnat value.
 *
 * Boundary हालs:
 *
 * o when पढ़ोing the rnat "below" the first rnat slot on the kernel
 *   backing store, rnat0/rnat1 are set to 0 and the low order bits are
 *   merged in from pt->ar_rnat.
 *
 * o when पढ़ोing the rnat "above" the last rnat slot on the kernel
 *   backing store, rnat0/rnat1 माला_लो its value from sw->ar_rnat.
 */
अटल अचिन्हित दीर्घ
get_rnat (काष्ठा task_काष्ठा *task, काष्ठा चयन_stack *sw,
	  अचिन्हित दीर्घ *krbs, अचिन्हित दीर्घ *urnat_addr,
	  अचिन्हित दीर्घ *urbs_end)
अणु
	अचिन्हित दीर्घ rnat0 = 0, rnat1 = 0, urnat = 0, *slot0_kaddr;
	अचिन्हित दीर्घ umask = 0, mask, m;
	अचिन्हित दीर्घ *kbsp, *ubspstore, *rnat0_kaddr, *rnat1_kaddr, shअगरt;
	दीर्घ num_regs, nbits;
	काष्ठा pt_regs *pt;

	pt = task_pt_regs(task);
	kbsp = (अचिन्हित दीर्घ *) sw->ar_bspstore;
	ubspstore = (अचिन्हित दीर्घ *) pt->ar_bspstore;

	अगर (urbs_end < urnat_addr)
		nbits = ia64_rse_num_regs(urnat_addr - 63, urbs_end);
	अन्यथा
		nbits = 63;
	mask = MASK(nbits);
	/*
	 * First, figure out which bit number slot 0 in user-land maps
	 * to in the kernel rnat.  Do this by figuring out how many
	 * रेजिस्टर slots we're beyond the user's backingstore and
	 * then computing the equivalent address in kernel space.
	 */
	num_regs = ia64_rse_num_regs(ubspstore, urnat_addr + 1);
	slot0_kaddr = ia64_rse_skip_regs(krbs, num_regs);
	shअगरt = ia64_rse_slot_num(slot0_kaddr);
	rnat1_kaddr = ia64_rse_rnat_addr(slot0_kaddr);
	rnat0_kaddr = rnat1_kaddr - 64;

	अगर (ubspstore + 63 > urnat_addr) अणु
		/* some bits need to be merged in from pt->ar_rnat */
		umask = MASK(ia64_rse_slot_num(ubspstore)) & mask;
		urnat = (pt->ar_rnat & umask);
		mask &= ~umask;
		अगर (!mask)
			वापस urnat;
	पूर्ण

	m = mask << shअगरt;
	अगर (rnat0_kaddr >= kbsp)
		rnat0 = sw->ar_rnat;
	अन्यथा अगर (rnat0_kaddr > krbs)
		rnat0 = *rnat0_kaddr;
	urnat |= (rnat0 & m) >> shअगरt;

	m = mask >> (63 - shअगरt);
	अगर (rnat1_kaddr >= kbsp)
		rnat1 = sw->ar_rnat;
	अन्यथा अगर (rnat1_kaddr > krbs)
		rnat1 = *rnat1_kaddr;
	urnat |= (rnat1 & m) << (63 - shअगरt);
	वापस urnat;
पूर्ण

/*
 * The reverse of get_rnat.
 */
अटल व्योम
put_rnat (काष्ठा task_काष्ठा *task, काष्ठा चयन_stack *sw,
	  अचिन्हित दीर्घ *krbs, अचिन्हित दीर्घ *urnat_addr, अचिन्हित दीर्घ urnat,
	  अचिन्हित दीर्घ *urbs_end)
अणु
	अचिन्हित दीर्घ rnat0 = 0, rnat1 = 0, *slot0_kaddr, umask = 0, mask, m;
	अचिन्हित दीर्घ *kbsp, *ubspstore, *rnat0_kaddr, *rnat1_kaddr, shअगरt;
	दीर्घ num_regs, nbits;
	काष्ठा pt_regs *pt;
	अचिन्हित दीर्घ cfm, *urbs_kargs;

	pt = task_pt_regs(task);
	kbsp = (अचिन्हित दीर्घ *) sw->ar_bspstore;
	ubspstore = (अचिन्हित दीर्घ *) pt->ar_bspstore;

	urbs_kargs = urbs_end;
	अगर (in_syscall(pt)) अणु
		/*
		 * If entered via syscall, करोn't allow user to set rnat bits
		 * क्रम syscall args.
		 */
		cfm = pt->cr_अगरs;
		urbs_kargs = ia64_rse_skip_regs(urbs_end, -(cfm & 0x7f));
	पूर्ण

	अगर (urbs_kargs >= urnat_addr)
		nbits = 63;
	अन्यथा अणु
		अगर ((urnat_addr - 63) >= urbs_kargs)
			वापस;
		nbits = ia64_rse_num_regs(urnat_addr - 63, urbs_kargs);
	पूर्ण
	mask = MASK(nbits);

	/*
	 * First, figure out which bit number slot 0 in user-land maps
	 * to in the kernel rnat.  Do this by figuring out how many
	 * रेजिस्टर slots we're beyond the user's backingstore and
	 * then computing the equivalent address in kernel space.
	 */
	num_regs = ia64_rse_num_regs(ubspstore, urnat_addr + 1);
	slot0_kaddr = ia64_rse_skip_regs(krbs, num_regs);
	shअगरt = ia64_rse_slot_num(slot0_kaddr);
	rnat1_kaddr = ia64_rse_rnat_addr(slot0_kaddr);
	rnat0_kaddr = rnat1_kaddr - 64;

	अगर (ubspstore + 63 > urnat_addr) अणु
		/* some bits need to be place in pt->ar_rnat: */
		umask = MASK(ia64_rse_slot_num(ubspstore)) & mask;
		pt->ar_rnat = (pt->ar_rnat & ~umask) | (urnat & umask);
		mask &= ~umask;
		अगर (!mask)
			वापस;
	पूर्ण
	/*
	 * Note: Section 11.1 of the EAS guarantees that bit 63 of an
	 * rnat slot is ignored. so we करोn't have to clear it here.
	 */
	rnat0 = (urnat << shअगरt);
	m = mask << shअगरt;
	अगर (rnat0_kaddr >= kbsp)
		sw->ar_rnat = (sw->ar_rnat & ~m) | (rnat0 & m);
	अन्यथा अगर (rnat0_kaddr > krbs)
		*rnat0_kaddr = ((*rnat0_kaddr & ~m) | (rnat0 & m));

	rnat1 = (urnat >> (63 - shअगरt));
	m = mask >> (63 - shअगरt);
	अगर (rnat1_kaddr >= kbsp)
		sw->ar_rnat = (sw->ar_rnat & ~m) | (rnat1 & m);
	अन्यथा अगर (rnat1_kaddr > krbs)
		*rnat1_kaddr = ((*rnat1_kaddr & ~m) | (rnat1 & m));
पूर्ण

अटल अंतरभूत पूर्णांक
on_kernel_rbs (अचिन्हित दीर्घ addr, अचिन्हित दीर्घ bspstore,
	       अचिन्हित दीर्घ urbs_end)
अणु
	अचिन्हित दीर्घ *rnat_addr = ia64_rse_rnat_addr((अचिन्हित दीर्घ *)
						      urbs_end);
	वापस (addr >= bspstore && addr <= (अचिन्हित दीर्घ) rnat_addr);
पूर्ण

/*
 * Read a word from the user-level backing store of task CHILD.  ADDR
 * is the user-level address to पढ़ो the word from, VAL a poपूर्णांकer to
 * the वापस value, and USER_BSP gives the end of the user-level
 * backing store (i.e., it's the address that would be in ar.bsp after
 * the user executed a "cover" inकाष्ठाion).
 *
 * This routine takes care of accessing the kernel रेजिस्टर backing
 * store क्रम those रेजिस्टरs that got spilled there.  It also takes
 * care of calculating the appropriate RNaT collection words.
 */
दीर्घ
ia64_peek (काष्ठा task_काष्ठा *child, काष्ठा चयन_stack *child_stack,
	   अचिन्हित दीर्घ user_rbs_end, अचिन्हित दीर्घ addr, दीर्घ *val)
अणु
	अचिन्हित दीर्घ *bspstore, *krbs, regnum, *laddr, *urbs_end, *rnat_addr;
	काष्ठा pt_regs *child_regs;
	माप_प्रकार copied;
	दीर्घ ret;

	urbs_end = (दीर्घ *) user_rbs_end;
	laddr = (अचिन्हित दीर्घ *) addr;
	child_regs = task_pt_regs(child);
	bspstore = (अचिन्हित दीर्घ *) child_regs->ar_bspstore;
	krbs = (अचिन्हित दीर्घ *) child + IA64_RBS_OFFSET/8;
	अगर (on_kernel_rbs(addr, (अचिन्हित दीर्घ) bspstore,
			  (अचिन्हित दीर्घ) urbs_end))
	अणु
		/*
		 * Attempt to पढ़ो the RBS in an area that's actually
		 * on the kernel RBS => पढ़ो the corresponding bits in
		 * the kernel RBS.
		 */
		rnat_addr = ia64_rse_rnat_addr(laddr);
		ret = get_rnat(child, child_stack, krbs, rnat_addr, urbs_end);

		अगर (laddr == rnat_addr) अणु
			/* वापस NaT collection word itself */
			*val = ret;
			वापस 0;
		पूर्ण

		अगर (((1UL << ia64_rse_slot_num(laddr)) & ret) != 0) अणु
			/*
			 * It is implementation dependent whether the
			 * data portion of a NaT value माला_लो saved on a
			 * st8.spill or RSE spill (e.g., see EAS 2.6,
			 * 4.4.4.6 Register Spill and Fill).  To get
			 * consistent behavior across all possible
			 * IA-64 implementations, we वापस zero in
			 * this हाल.
			 */
			*val = 0;
			वापस 0;
		पूर्ण

		अगर (laddr < urbs_end) अणु
			/*
			 * The desired word is on the kernel RBS and
			 * is not a NaT.
			 */
			regnum = ia64_rse_num_regs(bspstore, laddr);
			*val = *ia64_rse_skip_regs(krbs, regnum);
			वापस 0;
		पूर्ण
	पूर्ण
	copied = access_process_vm(child, addr, &ret, माप(ret), FOLL_FORCE);
	अगर (copied != माप(ret))
		वापस -EIO;
	*val = ret;
	वापस 0;
पूर्ण

दीर्घ
ia64_poke (काष्ठा task_काष्ठा *child, काष्ठा चयन_stack *child_stack,
	   अचिन्हित दीर्घ user_rbs_end, अचिन्हित दीर्घ addr, दीर्घ val)
अणु
	अचिन्हित दीर्घ *bspstore, *krbs, regnum, *laddr;
	अचिन्हित दीर्घ *urbs_end = (दीर्घ *) user_rbs_end;
	काष्ठा pt_regs *child_regs;

	laddr = (अचिन्हित दीर्घ *) addr;
	child_regs = task_pt_regs(child);
	bspstore = (अचिन्हित दीर्घ *) child_regs->ar_bspstore;
	krbs = (अचिन्हित दीर्घ *) child + IA64_RBS_OFFSET/8;
	अगर (on_kernel_rbs(addr, (अचिन्हित दीर्घ) bspstore,
			  (अचिन्हित दीर्घ) urbs_end))
	अणु
		/*
		 * Attempt to ग_लिखो the RBS in an area that's actually
		 * on the kernel RBS => ग_लिखो the corresponding bits
		 * in the kernel RBS.
		 */
		अगर (ia64_rse_is_rnat_slot(laddr))
			put_rnat(child, child_stack, krbs, laddr, val,
				 urbs_end);
		अन्यथा अणु
			अगर (laddr < urbs_end) अणु
				regnum = ia64_rse_num_regs(bspstore, laddr);
				*ia64_rse_skip_regs(krbs, regnum) = val;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (access_process_vm(child, addr, &val, माप(val),
				FOLL_FORCE | FOLL_WRITE)
		   != माप(val))
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * Calculate the address of the end of the user-level रेजिस्टर backing
 * store.  This is the address that would have been stored in ar.bsp
 * अगर the user had executed a "cover" inकाष्ठाion right beक्रमe
 * entering the kernel.  If CFMP is not शून्य, it is used to वापस the
 * "current frame mask" that was active at the समय the kernel was
 * entered.
 */
अचिन्हित दीर्घ
ia64_get_user_rbs_end (काष्ठा task_काष्ठा *child, काष्ठा pt_regs *pt,
		       अचिन्हित दीर्घ *cfmp)
अणु
	अचिन्हित दीर्घ *krbs, *bspstore, cfm = pt->cr_अगरs;
	दीर्घ ndirty;

	krbs = (अचिन्हित दीर्घ *) child + IA64_RBS_OFFSET/8;
	bspstore = (अचिन्हित दीर्घ *) pt->ar_bspstore;
	ndirty = ia64_rse_num_regs(krbs, krbs + (pt->loadrs >> 19));

	अगर (in_syscall(pt))
		ndirty += (cfm & 0x7f);
	अन्यथा
		cfm &= ~(1UL << 63);	/* clear valid bit */

	अगर (cfmp)
		*cfmp = cfm;
	वापस (अचिन्हित दीर्घ) ia64_rse_skip_regs(bspstore, ndirty);
पूर्ण

/*
 * Synchronize (i.e, ग_लिखो) the RSE backing store living in kernel
 * space to the VM of the CHILD task.  SW and PT are the poपूर्णांकers to
 * the चयन_stack and pt_regs काष्ठाures, respectively.
 * USER_RBS_END is the user-level address at which the backing store
 * ends.
 */
दीर्घ
ia64_sync_user_rbs (काष्ठा task_काष्ठा *child, काष्ठा चयन_stack *sw,
		    अचिन्हित दीर्घ user_rbs_start, अचिन्हित दीर्घ user_rbs_end)
अणु
	अचिन्हित दीर्घ addr, val;
	दीर्घ ret;

	/* now copy word क्रम word from kernel rbs to user rbs: */
	क्रम (addr = user_rbs_start; addr < user_rbs_end; addr += 8) अणु
		ret = ia64_peek(child, sw, user_rbs_end, addr, &val);
		अगर (ret < 0)
			वापस ret;
		अगर (access_process_vm(child, addr, &val, माप(val),
				FOLL_FORCE | FOLL_WRITE)
		    != माप(val))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल दीर्घ
ia64_sync_kernel_rbs (काष्ठा task_काष्ठा *child, काष्ठा चयन_stack *sw,
		अचिन्हित दीर्घ user_rbs_start, अचिन्हित दीर्घ user_rbs_end)
अणु
	अचिन्हित दीर्घ addr, val;
	दीर्घ ret;

	/* now copy word क्रम word from user rbs to kernel rbs: */
	क्रम (addr = user_rbs_start; addr < user_rbs_end; addr += 8) अणु
		अगर (access_process_vm(child, addr, &val, माप(val),
				FOLL_FORCE)
				!= माप(val))
			वापस -EIO;

		ret = ia64_poke(child, sw, user_rbs_end, addr, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

प्रकार दीर्घ (*syncfunc_t)(काष्ठा task_काष्ठा *, काष्ठा चयन_stack *,
			    अचिन्हित दीर्घ, अचिन्हित दीर्घ);

अटल व्योम करो_sync_rbs(काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	काष्ठा pt_regs *pt;
	अचिन्हित दीर्घ urbs_end;
	syncfunc_t fn = arg;

	अगर (unw_unwind_to_user(info) < 0)
		वापस;
	pt = task_pt_regs(info->task);
	urbs_end = ia64_get_user_rbs_end(info->task, pt, शून्य);

	fn(info->task, info->sw, pt->ar_bspstore, urbs_end);
पूर्ण

/*
 * when a thपढ़ो is stopped (ptraced), debugger might change thपढ़ो's user
 * stack (change memory directly), and we must aव्योम the RSE stored in kernel
 * to override user stack (user space's RSE is newer than kernel's in the
 * हाल). To workaround the issue, we copy kernel RSE to user RSE beक्रमe the
 * task is stopped, so user RSE has updated data.  we then copy user RSE to
 * kernel after the task is resummed from traced stop and kernel will use the
 * newer RSE to वापस to user. TIF_RESTORE_RSE is the flag to indicate we need
 * synchronize user RSE to kernel.
 */
व्योम ia64_ptrace_stop(व्योम)
अणु
	अगर (test_and_set_tsk_thपढ़ो_flag(current, TIF_RESTORE_RSE))
		वापस;
	set_notअगरy_resume(current);
	unw_init_running(करो_sync_rbs, ia64_sync_user_rbs);
पूर्ण

/*
 * This is called to पढ़ो back the रेजिस्टर backing store.
 */
व्योम ia64_sync_krbs(व्योम)
अणु
	clear_tsk_thपढ़ो_flag(current, TIF_RESTORE_RSE);

	unw_init_running(करो_sync_rbs, ia64_sync_kernel_rbs);
पूर्ण

/*
 * After PTRACE_ATTACH, a thपढ़ो's रेजिस्टर backing store area in user
 * space is assumed to contain correct data whenever the thपढ़ो is
 * stopped.  arch_ptrace_stop takes care of this on tracing stops.
 * But अगर the child was alपढ़ोy stopped क्रम job control when we attach
 * to it, then it might not ever get पूर्णांकo ptrace_stop by the समय we
 * want to examine the user memory containing the RBS.
 */
व्योम
ptrace_attach_sync_user_rbs (काष्ठा task_काष्ठा *child)
अणु
	पूर्णांक stopped = 0;
	काष्ठा unw_frame_info info;

	/*
	 * If the child is in TASK_STOPPED, we need to change that to
	 * TASK_TRACED momentarily जबतक we operate on it.  This ensures
	 * that the child won't be woken up and वापस to user mode जबतक
	 * we are करोing the sync.  (It can only be woken up क्रम SIGKILL.)
	 */

	पढ़ो_lock(&tasklist_lock);
	अगर (child->sighand) अणु
		spin_lock_irq(&child->sighand->siglock);
		अगर (child->state == TASK_STOPPED &&
		    !test_and_set_tsk_thपढ़ो_flag(child, TIF_RESTORE_RSE)) अणु
			set_notअगरy_resume(child);

			child->state = TASK_TRACED;
			stopped = 1;
		पूर्ण
		spin_unlock_irq(&child->sighand->siglock);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);

	अगर (!stopped)
		वापस;

	unw_init_from_blocked_task(&info, child);
	करो_sync_rbs(&info, ia64_sync_user_rbs);

	/*
	 * Now move the child back पूर्णांकo TASK_STOPPED अगर it should be in a
	 * job control stop, so that SIGCONT can be used to wake it up.
	 */
	पढ़ो_lock(&tasklist_lock);
	अगर (child->sighand) अणु
		spin_lock_irq(&child->sighand->siglock);
		अगर (child->state == TASK_TRACED &&
		    (child->संकेत->flags & SIGNAL_STOP_STOPPED)) अणु
			child->state = TASK_STOPPED;
		पूर्ण
		spin_unlock_irq(&child->sighand->siglock);
	पूर्ण
	पढ़ो_unlock(&tasklist_lock);
पूर्ण

/*
 * Write f32-f127 back to task->thपढ़ो.fph अगर it has been modअगरied.
 */
अंतरभूत व्योम
ia64_flush_fph (काष्ठा task_काष्ठा *task)
अणु
	काष्ठा ia64_psr *psr = ia64_psr(task_pt_regs(task));

	/*
	 * Prevent migrating this task जबतक
	 * we're fiddling with the FPU state
	 */
	preempt_disable();
	अगर (ia64_is_local_fpu_owner(task) && psr->mfh) अणु
		psr->mfh = 0;
		task->thपढ़ो.flags |= IA64_THREAD_FPH_VALID;
		ia64_save_fpu(&task->thपढ़ो.fph[0]);
	पूर्ण
	preempt_enable();
पूर्ण

/*
 * Sync the fph state of the task so that it can be manipulated
 * through thपढ़ो.fph.  If necessary, f32-f127 are written back to
 * thपढ़ो.fph or, अगर the fph state hasn't been used beक्रमe, thपढ़ो.fph
 * is cleared to zeroes.  Also, access to f32-f127 is disabled to
 * ensure that the task picks up the state from thपढ़ो.fph when it
 * executes again.
 */
व्योम
ia64_sync_fph (काष्ठा task_काष्ठा *task)
अणु
	काष्ठा ia64_psr *psr = ia64_psr(task_pt_regs(task));

	ia64_flush_fph(task);
	अगर (!(task->thपढ़ो.flags & IA64_THREAD_FPH_VALID)) अणु
		task->thपढ़ो.flags |= IA64_THREAD_FPH_VALID;
		स_रखो(&task->thपढ़ो.fph, 0, माप(task->thपढ़ो.fph));
	पूर्ण
	ia64_drop_fpu(task);
	psr->dfh = 1;
पूर्ण

/*
 * Change the machine-state of CHILD such that it will वापस via the normal
 * kernel निकास-path, rather than the syscall-निकास path.
 */
अटल व्योम
convert_to_non_syscall (काष्ठा task_काष्ठा *child, काष्ठा pt_regs  *pt,
			अचिन्हित दीर्घ cfm)
अणु
	काष्ठा unw_frame_info info, prev_info;
	अचिन्हित दीर्घ ip, sp, pr;

	unw_init_from_blocked_task(&info, child);
	जबतक (1) अणु
		prev_info = info;
		अगर (unw_unwind(&info) < 0)
			वापस;

		unw_get_sp(&info, &sp);
		अगर ((दीर्घ)((अचिन्हित दीर्घ)child + IA64_STK_OFFSET - sp)
		    < IA64_PT_REGS_SIZE) अणु
			dprपूर्णांकk("ptrace.%s: ran off the top of the kernel "
				"stack\n", __func__);
			वापस;
		पूर्ण
		अगर (unw_get_pr (&prev_info, &pr) < 0) अणु
			unw_get_rp(&prev_info, &ip);
			dprपूर्णांकk("ptrace.%s: failed to read "
				"predicate register (ip=0x%lx)\n",
				__func__, ip);
			वापस;
		पूर्ण
		अगर (unw_is_पूर्णांकr_frame(&info)
		    && (pr & (1UL << PRED_USER_STACK)))
			अवरोध;
	पूर्ण

	/*
	 * Note: at the समय of this call, the target task is blocked
	 * in notअगरy_resume_user() and by clearling PRED_LEAVE_SYSCALL
	 * (aka, "pLvSys") we redirect execution from
	 * .work_pending_syscall_end to .work_processed_kernel.
	 */
	unw_get_pr(&prev_info, &pr);
	pr &= ~((1UL << PRED_SYSCALL) | (1UL << PRED_LEAVE_SYSCALL));
	pr |=  (1UL << PRED_NON_SYSCALL);
	unw_set_pr(&prev_info, pr);

	pt->cr_अगरs = (1UL << 63) | cfm;
	/*
	 * Clear the memory that is NOT written on syscall-entry to
	 * ensure we करो not leak kernel-state to user when execution
	 * resumes.
	 */
	pt->r2 = 0;
	pt->r3 = 0;
	pt->r14 = 0;
	स_रखो(&pt->r16, 0, 16*8);	/* clear r16-r31 */
	स_रखो(&pt->f6, 0, 6*16);	/* clear f6-f11 */
	pt->b7 = 0;
	pt->ar_ccv = 0;
	pt->ar_csd = 0;
	pt->ar_ssd = 0;
पूर्ण

अटल पूर्णांक
access_nat_bits (काष्ठा task_काष्ठा *child, काष्ठा pt_regs *pt,
		 काष्ठा unw_frame_info *info,
		 अचिन्हित दीर्घ *data, पूर्णांक ग_लिखो_access)
अणु
	अचिन्हित दीर्घ regnum, nat_bits, scratch_unat, dummy = 0;
	अक्षर nat = 0;

	अगर (ग_लिखो_access) अणु
		nat_bits = *data;
		scratch_unat = ia64_put_scratch_nat_bits(pt, nat_bits);
		अगर (unw_set_ar(info, UNW_AR_UNAT, scratch_unat) < 0) अणु
			dprपूर्णांकk("ptrace: failed to set ar.unat\n");
			वापस -1;
		पूर्ण
		क्रम (regnum = 4; regnum <= 7; ++regnum) अणु
			unw_get_gr(info, regnum, &dummy, &nat);
			unw_set_gr(info, regnum, dummy,
				   (nat_bits >> regnum) & 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unw_get_ar(info, UNW_AR_UNAT, &scratch_unat) < 0) अणु
			dprपूर्णांकk("ptrace: failed to read ar.unat\n");
			वापस -1;
		पूर्ण
		nat_bits = ia64_get_scratch_nat_bits(pt, scratch_unat);
		क्रम (regnum = 4; regnum <= 7; ++regnum) अणु
			unw_get_gr(info, regnum, &dummy, &nat);
			nat_bits |= (nat != 0) << regnum;
		पूर्ण
		*data = nat_bits;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
access_elf_reg(काष्ठा task_काष्ठा *target, काष्ठा unw_frame_info *info,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *data, पूर्णांक ग_लिखो_access);

अटल दीर्घ
ptrace_getregs (काष्ठा task_काष्ठा *child, काष्ठा pt_all_user_regs __user *ppr)
अणु
	अचिन्हित दीर्घ psr, ec, lc, rnat, bsp, cfm, nat_bits, val;
	काष्ठा unw_frame_info info;
	काष्ठा ia64_fpreg fpval;
	काष्ठा चयन_stack *sw;
	काष्ठा pt_regs *pt;
	दीर्घ ret, retval = 0;
	अक्षर nat = 0;
	पूर्णांक i;

	अगर (!access_ok(ppr, माप(काष्ठा pt_all_user_regs)))
		वापस -EIO;

	pt = task_pt_regs(child);
	sw = (काष्ठा चयन_stack *) (child->thपढ़ो.ksp + 16);
	unw_init_from_blocked_task(&info, child);
	अगर (unw_unwind_to_user(&info) < 0) अणु
		वापस -EIO;
	पूर्ण

	अगर (((अचिन्हित दीर्घ) ppr & 0x7) != 0) अणु
		dprपूर्णांकk("ptrace:unaligned register address %p\n", ppr);
		वापस -EIO;
	पूर्ण

	अगर (access_elf_reg(child, &info, ELF_CR_IPSR_OFFSET, &psr, 0) < 0 ||
	    access_elf_reg(child, &info, ELF_AR_EC_OFFSET, &ec, 0) < 0 ||
	    access_elf_reg(child, &info, ELF_AR_LC_OFFSET, &lc, 0) < 0 ||
	    access_elf_reg(child, &info, ELF_AR_RNAT_OFFSET, &rnat, 0) < 0 ||
	    access_elf_reg(child, &info, ELF_AR_BSP_OFFSET, &bsp, 0) < 0 ||
	    access_elf_reg(child, &info, ELF_CFM_OFFSET, &cfm, 0) < 0 ||
	    access_elf_reg(child, &info, ELF_NAT_OFFSET, &nat_bits, 0) < 0)
		वापस -EIO;

	/* control regs */

	retval |= __put_user(pt->cr_iip, &ppr->cr_iip);
	retval |= __put_user(psr, &ppr->cr_ipsr);

	/* app regs */

	retval |= __put_user(pt->ar_pfs, &ppr->ar[PT_AUR_PFS]);
	retval |= __put_user(pt->ar_rsc, &ppr->ar[PT_AUR_RSC]);
	retval |= __put_user(pt->ar_bspstore, &ppr->ar[PT_AUR_BSPSTORE]);
	retval |= __put_user(pt->ar_unat, &ppr->ar[PT_AUR_UNAT]);
	retval |= __put_user(pt->ar_ccv, &ppr->ar[PT_AUR_CCV]);
	retval |= __put_user(pt->ar_fpsr, &ppr->ar[PT_AUR_FPSR]);

	retval |= __put_user(ec, &ppr->ar[PT_AUR_EC]);
	retval |= __put_user(lc, &ppr->ar[PT_AUR_LC]);
	retval |= __put_user(rnat, &ppr->ar[PT_AUR_RNAT]);
	retval |= __put_user(bsp, &ppr->ar[PT_AUR_BSP]);
	retval |= __put_user(cfm, &ppr->cfm);

	/* gr1-gr3 */

	retval |= __copy_to_user(&ppr->gr[1], &pt->r1, माप(दीर्घ));
	retval |= __copy_to_user(&ppr->gr[2], &pt->r2, माप(दीर्घ) *2);

	/* gr4-gr7 */

	क्रम (i = 4; i < 8; i++) अणु
		अगर (unw_access_gr(&info, i, &val, &nat, 0) < 0)
			वापस -EIO;
		retval |= __put_user(val, &ppr->gr[i]);
	पूर्ण

	/* gr8-gr11 */

	retval |= __copy_to_user(&ppr->gr[8], &pt->r8, माप(दीर्घ) * 4);

	/* gr12-gr15 */

	retval |= __copy_to_user(&ppr->gr[12], &pt->r12, माप(दीर्घ) * 2);
	retval |= __copy_to_user(&ppr->gr[14], &pt->r14, माप(दीर्घ));
	retval |= __copy_to_user(&ppr->gr[15], &pt->r15, माप(दीर्घ));

	/* gr16-gr31 */

	retval |= __copy_to_user(&ppr->gr[16], &pt->r16, माप(दीर्घ) * 16);

	/* b0 */

	retval |= __put_user(pt->b0, &ppr->br[0]);

	/* b1-b5 */

	क्रम (i = 1; i < 6; i++) अणु
		अगर (unw_access_br(&info, i, &val, 0) < 0)
			वापस -EIO;
		__put_user(val, &ppr->br[i]);
	पूर्ण

	/* b6-b7 */

	retval |= __put_user(pt->b6, &ppr->br[6]);
	retval |= __put_user(pt->b7, &ppr->br[7]);

	/* fr2-fr5 */

	क्रम (i = 2; i < 6; i++) अणु
		अगर (unw_get_fr(&info, i, &fpval) < 0)
			वापस -EIO;
		retval |= __copy_to_user(&ppr->fr[i], &fpval, माप (fpval));
	पूर्ण

	/* fr6-fr11 */

	retval |= __copy_to_user(&ppr->fr[6], &pt->f6,
				 माप(काष्ठा ia64_fpreg) * 6);

	/* fp scratch regs(12-15) */

	retval |= __copy_to_user(&ppr->fr[12], &sw->f12,
				 माप(काष्ठा ia64_fpreg) * 4);

	/* fr16-fr31 */

	क्रम (i = 16; i < 32; i++) अणु
		अगर (unw_get_fr(&info, i, &fpval) < 0)
			वापस -EIO;
		retval |= __copy_to_user(&ppr->fr[i], &fpval, माप (fpval));
	पूर्ण

	/* fph */

	ia64_flush_fph(child);
	retval |= __copy_to_user(&ppr->fr[32], &child->thपढ़ो.fph,
				 माप(ppr->fr[32]) * 96);

	/*  preds */

	retval |= __put_user(pt->pr, &ppr->pr);

	/* nat bits */

	retval |= __put_user(nat_bits, &ppr->nat);

	ret = retval ? -EIO : 0;
	वापस ret;
पूर्ण

अटल दीर्घ
ptrace_setregs (काष्ठा task_काष्ठा *child, काष्ठा pt_all_user_regs __user *ppr)
अणु
	अचिन्हित दीर्घ psr, rsc, ec, lc, rnat, bsp, cfm, nat_bits, val = 0;
	काष्ठा unw_frame_info info;
	काष्ठा चयन_stack *sw;
	काष्ठा ia64_fpreg fpval;
	काष्ठा pt_regs *pt;
	दीर्घ retval = 0;
	पूर्णांक i;

	स_रखो(&fpval, 0, माप(fpval));

	अगर (!access_ok(ppr, माप(काष्ठा pt_all_user_regs)))
		वापस -EIO;

	pt = task_pt_regs(child);
	sw = (काष्ठा चयन_stack *) (child->thपढ़ो.ksp + 16);
	unw_init_from_blocked_task(&info, child);
	अगर (unw_unwind_to_user(&info) < 0) अणु
		वापस -EIO;
	पूर्ण

	अगर (((अचिन्हित दीर्घ) ppr & 0x7) != 0) अणु
		dprपूर्णांकk("ptrace:unaligned register address %p\n", ppr);
		वापस -EIO;
	पूर्ण

	/* control regs */

	retval |= __get_user(pt->cr_iip, &ppr->cr_iip);
	retval |= __get_user(psr, &ppr->cr_ipsr);

	/* app regs */

	retval |= __get_user(pt->ar_pfs, &ppr->ar[PT_AUR_PFS]);
	retval |= __get_user(rsc, &ppr->ar[PT_AUR_RSC]);
	retval |= __get_user(pt->ar_bspstore, &ppr->ar[PT_AUR_BSPSTORE]);
	retval |= __get_user(pt->ar_unat, &ppr->ar[PT_AUR_UNAT]);
	retval |= __get_user(pt->ar_ccv, &ppr->ar[PT_AUR_CCV]);
	retval |= __get_user(pt->ar_fpsr, &ppr->ar[PT_AUR_FPSR]);

	retval |= __get_user(ec, &ppr->ar[PT_AUR_EC]);
	retval |= __get_user(lc, &ppr->ar[PT_AUR_LC]);
	retval |= __get_user(rnat, &ppr->ar[PT_AUR_RNAT]);
	retval |= __get_user(bsp, &ppr->ar[PT_AUR_BSP]);
	retval |= __get_user(cfm, &ppr->cfm);

	/* gr1-gr3 */

	retval |= __copy_from_user(&pt->r1, &ppr->gr[1], माप(दीर्घ));
	retval |= __copy_from_user(&pt->r2, &ppr->gr[2], माप(दीर्घ) * 2);

	/* gr4-gr7 */

	क्रम (i = 4; i < 8; i++) अणु
		retval |= __get_user(val, &ppr->gr[i]);
		/* NaT bit will be set via PT_NAT_BITS: */
		अगर (unw_set_gr(&info, i, val, 0) < 0)
			वापस -EIO;
	पूर्ण

	/* gr8-gr11 */

	retval |= __copy_from_user(&pt->r8, &ppr->gr[8], माप(दीर्घ) * 4);

	/* gr12-gr15 */

	retval |= __copy_from_user(&pt->r12, &ppr->gr[12], माप(दीर्घ) * 2);
	retval |= __copy_from_user(&pt->r14, &ppr->gr[14], माप(दीर्घ));
	retval |= __copy_from_user(&pt->r15, &ppr->gr[15], माप(दीर्घ));

	/* gr16-gr31 */

	retval |= __copy_from_user(&pt->r16, &ppr->gr[16], माप(दीर्घ) * 16);

	/* b0 */

	retval |= __get_user(pt->b0, &ppr->br[0]);

	/* b1-b5 */

	क्रम (i = 1; i < 6; i++) अणु
		retval |= __get_user(val, &ppr->br[i]);
		unw_set_br(&info, i, val);
	पूर्ण

	/* b6-b7 */

	retval |= __get_user(pt->b6, &ppr->br[6]);
	retval |= __get_user(pt->b7, &ppr->br[7]);

	/* fr2-fr5 */

	क्रम (i = 2; i < 6; i++) अणु
		retval |= __copy_from_user(&fpval, &ppr->fr[i], माप(fpval));
		अगर (unw_set_fr(&info, i, fpval) < 0)
			वापस -EIO;
	पूर्ण

	/* fr6-fr11 */

	retval |= __copy_from_user(&pt->f6, &ppr->fr[6],
				   माप(ppr->fr[6]) * 6);

	/* fp scratch regs(12-15) */

	retval |= __copy_from_user(&sw->f12, &ppr->fr[12],
				   माप(ppr->fr[12]) * 4);

	/* fr16-fr31 */

	क्रम (i = 16; i < 32; i++) अणु
		retval |= __copy_from_user(&fpval, &ppr->fr[i],
					   माप(fpval));
		अगर (unw_set_fr(&info, i, fpval) < 0)
			वापस -EIO;
	पूर्ण

	/* fph */

	ia64_sync_fph(child);
	retval |= __copy_from_user(&child->thपढ़ो.fph, &ppr->fr[32],
				   माप(ppr->fr[32]) * 96);

	/* preds */

	retval |= __get_user(pt->pr, &ppr->pr);

	/* nat bits */

	retval |= __get_user(nat_bits, &ppr->nat);

	retval |= access_elf_reg(child, &info, ELF_CR_IPSR_OFFSET, &psr, 1);
	retval |= access_elf_reg(child, &info, ELF_AR_RSC_OFFSET, &rsc, 1);
	retval |= access_elf_reg(child, &info, ELF_AR_EC_OFFSET, &ec, 1);
	retval |= access_elf_reg(child, &info, ELF_AR_LC_OFFSET, &lc, 1);
	retval |= access_elf_reg(child, &info, ELF_AR_RNAT_OFFSET, &rnat, 1);
	retval |= access_elf_reg(child, &info, ELF_AR_BSP_OFFSET, &bsp, 1);
	retval |= access_elf_reg(child, &info, ELF_CFM_OFFSET, &cfm, 1);
	retval |= access_elf_reg(child, &info, ELF_NAT_OFFSET, &nat_bits, 1);

	वापस retval ? -EIO : 0;
पूर्ण

व्योम
user_enable_single_step (काष्ठा task_काष्ठा *child)
अणु
	काष्ठा ia64_psr *child_psr = ia64_psr(task_pt_regs(child));

	set_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);
	child_psr->ss = 1;
पूर्ण

व्योम
user_enable_block_step (काष्ठा task_काष्ठा *child)
अणु
	काष्ठा ia64_psr *child_psr = ia64_psr(task_pt_regs(child));

	set_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);
	child_psr->tb = 1;
पूर्ण

व्योम
user_disable_single_step (काष्ठा task_काष्ठा *child)
अणु
	काष्ठा ia64_psr *child_psr = ia64_psr(task_pt_regs(child));

	/* make sure the single step/taken-branch trap bits are not set: */
	clear_tsk_thपढ़ो_flag(child, TIF_SINGLESTEP);
	child_psr->ss = 0;
	child_psr->tb = 0;
पूर्ण

/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Make sure the single step bit is not set.
 */
व्योम
ptrace_disable (काष्ठा task_काष्ठा *child)
अणु
	user_disable_single_step(child);
पूर्ण

अटल पूर्णांक
access_uarea (काष्ठा task_काष्ठा *child, अचिन्हित दीर्घ addr,
	      अचिन्हित दीर्घ *data, पूर्णांक ग_लिखो_access);

दीर्घ
arch_ptrace (काष्ठा task_काष्ठा *child, दीर्घ request,
	     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	चयन (request) अणु
	हाल PTRACE_PEEKTEXT:
	हाल PTRACE_PEEKDATA:
		/* पढ़ो word at location addr */
		अगर (ptrace_access_vm(child, addr, &data, माप(data),
				FOLL_FORCE)
		    != माप(data))
			वापस -EIO;
		/* ensure वापस value is not mistaken क्रम error code */
		क्रमce_successful_syscall_वापस();
		वापस data;

	/* PTRACE_POKETEXT and PTRACE_POKEDATA is handled
	 * by the generic ptrace_request().
	 */

	हाल PTRACE_PEEKUSR:
		/* पढ़ो the word at addr in the USER area */
		अगर (access_uarea(child, addr, &data, 0) < 0)
			वापस -EIO;
		/* ensure वापस value is not mistaken क्रम error code */
		क्रमce_successful_syscall_वापस();
		वापस data;

	हाल PTRACE_POKEUSR:
		/* ग_लिखो the word at addr in the USER area */
		अगर (access_uarea(child, addr, &data, 1) < 0)
			वापस -EIO;
		वापस 0;

	हाल PTRACE_OLD_GETSIGINFO:
		/* क्रम backwards-compatibility */
		वापस ptrace_request(child, PTRACE_GETSIGINFO, addr, data);

	हाल PTRACE_OLD_SETSIGINFO:
		/* क्रम backwards-compatibility */
		वापस ptrace_request(child, PTRACE_SETSIGINFO, addr, data);

	हाल PTRACE_GETREGS:
		वापस ptrace_getregs(child,
				      (काष्ठा pt_all_user_regs __user *) data);

	हाल PTRACE_SETREGS:
		वापस ptrace_setregs(child,
				      (काष्ठा pt_all_user_regs __user *) data);

	शेष:
		वापस ptrace_request(child, request, addr, data);
	पूर्ण
पूर्ण


/* "asmlinkage" so the input arguments are preserved... */

यंत्रlinkage दीर्घ
syscall_trace_enter (दीर्घ arg0, दीर्घ arg1, दीर्घ arg2, दीर्घ arg3,
		     दीर्घ arg4, दीर्घ arg5, दीर्घ arg6, दीर्घ arg7,
		     काष्ठा pt_regs regs)
अणु
	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		अगर (tracehook_report_syscall_entry(&regs))
			वापस -ENOSYS;

	/* copy user rbs to kernel rbs */
	अगर (test_thपढ़ो_flag(TIF_RESTORE_RSE))
		ia64_sync_krbs();


	audit_syscall_entry(regs.r15, arg0, arg1, arg2, arg3);

	वापस 0;
पूर्ण

/* "asmlinkage" so the input arguments are preserved... */

यंत्रlinkage व्योम
syscall_trace_leave (दीर्घ arg0, दीर्घ arg1, दीर्घ arg2, दीर्घ arg3,
		     दीर्घ arg4, दीर्घ arg5, दीर्घ arg6, दीर्घ arg7,
		     काष्ठा pt_regs regs)
अणु
	पूर्णांक step;

	audit_syscall_निकास(&regs);

	step = test_thपढ़ो_flag(TIF_SINGLESTEP);
	अगर (step || test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(&regs, step);

	/* copy user rbs to kernel rbs */
	अगर (test_thपढ़ो_flag(TIF_RESTORE_RSE))
		ia64_sync_krbs();
पूर्ण

/* Utrace implementation starts here */
काष्ठा regset_get अणु
	व्योम *kbuf;
	व्योम __user *ubuf;
पूर्ण;

काष्ठा regset_set अणु
	स्थिर व्योम *kbuf;
	स्थिर व्योम __user *ubuf;
पूर्ण;

काष्ठा regset_माला_लोet अणु
	काष्ठा task_काष्ठा *target;
	स्थिर काष्ठा user_regset *regset;
	जोड़ अणु
		काष्ठा regset_get get;
		काष्ठा regset_set set;
	पूर्ण u;
	अचिन्हित पूर्णांक pos;
	अचिन्हित पूर्णांक count;
	पूर्णांक ret;
पूर्ण;

अटल स्थिर सूचक_भेद_प्रकार pt_offsets[32] =
अणु
#घोषणा R(n) दुरत्व(काष्ठा pt_regs, r##n)
	[0] = -1, R(1), R(2), R(3),
	[4] = -1, [5] = -1, [6] = -1, [7] = -1,
	R(8), R(9), R(10), R(11), R(12), R(13), R(14), R(15),
	R(16), R(17), R(18), R(19), R(20), R(21), R(22), R(23),
	R(24), R(25), R(26), R(27), R(28), R(29), R(30), R(31),
#अघोषित R
पूर्ण;

अटल पूर्णांक
access_elf_gpreg(काष्ठा task_काष्ठा *target, काष्ठा unw_frame_info *info,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *data, पूर्णांक ग_लिखो_access)
अणु
	काष्ठा pt_regs *pt = task_pt_regs(target);
	अचिन्हित reg = addr / माप(अचिन्हित दीर्घ);
	सूचक_भेद_प्रकार d = pt_offsets[reg];

	अगर (d >= 0) अणु
		अचिन्हित दीर्घ *ptr = (व्योम *)pt + d;
		अगर (ग_लिखो_access)
			*ptr = *data;
		अन्यथा
			*data = *ptr;
		वापस 0;
	पूर्ण अन्यथा अणु
		अक्षर nat = 0;
		अगर (ग_लिखो_access) अणु
			/* पढ़ो NaT bit first: */
			अचिन्हित दीर्घ dummy;
			पूर्णांक ret = unw_get_gr(info, reg, &dummy, &nat);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		वापस unw_access_gr(info, reg, data, &nat, ग_लिखो_access);
	पूर्ण
पूर्ण

अटल पूर्णांक
access_elf_breg(काष्ठा task_काष्ठा *target, काष्ठा unw_frame_info *info,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *data, पूर्णांक ग_लिखो_access)
अणु
	काष्ठा pt_regs *pt;
	अचिन्हित दीर्घ *ptr = शून्य;

	pt = task_pt_regs(target);
	चयन (addr) अणु
	हाल ELF_BR_OFFSET(0):
		ptr = &pt->b0;
		अवरोध;
	हाल ELF_BR_OFFSET(1) ... ELF_BR_OFFSET(5):
		वापस unw_access_br(info, (addr - ELF_BR_OFFSET(0))/8,
				     data, ग_लिखो_access);
	हाल ELF_BR_OFFSET(6):
		ptr = &pt->b6;
		अवरोध;
	हाल ELF_BR_OFFSET(7):
		ptr = &pt->b7;
	पूर्ण
	अगर (ग_लिखो_access)
		*ptr = *data;
	अन्यथा
		*data = *ptr;
	वापस 0;
पूर्ण

अटल पूर्णांक
access_elf_areg(काष्ठा task_काष्ठा *target, काष्ठा unw_frame_info *info,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *data, पूर्णांक ग_लिखो_access)
अणु
	काष्ठा pt_regs *pt;
	अचिन्हित दीर्घ cfm, urbs_end;
	अचिन्हित दीर्घ *ptr = शून्य;

	pt = task_pt_regs(target);
	अगर (addr >= ELF_AR_RSC_OFFSET && addr <= ELF_AR_SSD_OFFSET) अणु
		चयन (addr) अणु
		हाल ELF_AR_RSC_OFFSET:
			/* क्रमce PL3 */
			अगर (ग_लिखो_access)
				pt->ar_rsc = *data | (3 << 2);
			अन्यथा
				*data = pt->ar_rsc;
			वापस 0;
		हाल ELF_AR_BSP_OFFSET:
			/*
			 * By convention, we use PT_AR_BSP to refer to
			 * the end of the user-level backing store.
			 * Use ia64_rse_skip_regs(PT_AR_BSP, -CFM.sof)
			 * to get the real value of ar.bsp at the समय
			 * the kernel was entered.
			 *
			 * Furthermore, when changing the contents of
			 * PT_AR_BSP (or PT_CFM) जबतक the task is
			 * blocked in a प्रणाली call, convert the state
			 * so that the non-प्रणाली-call निकास
			 * path is used.  This ensures that the proper
			 * state will be picked up when resuming
			 * execution.  However, it *also* means that
			 * once we ग_लिखो PT_AR_BSP/PT_CFM, it won't be
			 * possible to modअगरy the syscall arguments of
			 * the pending प्रणाली call any दीर्घer.  This
			 * shouldn't be an issue because modअगरying
			 * PT_AR_BSP/PT_CFM generally implies that
			 * we're either abanकरोning the pending प्रणाली
			 * call or that we defer it's re-execution
			 * (e.g., due to GDB करोing an inferior
			 * function call).
			 */
			urbs_end = ia64_get_user_rbs_end(target, pt, &cfm);
			अगर (ग_लिखो_access) अणु
				अगर (*data != urbs_end) अणु
					अगर (in_syscall(pt))
						convert_to_non_syscall(target,
								       pt,
								       cfm);
					/*
					 * Simulate user-level ग_लिखो
					 * of ar.bsp:
					 */
					pt->loadrs = 0;
					pt->ar_bspstore = *data;
				पूर्ण
			पूर्ण अन्यथा
				*data = urbs_end;
			वापस 0;
		हाल ELF_AR_BSPSTORE_OFFSET:
			ptr = &pt->ar_bspstore;
			अवरोध;
		हाल ELF_AR_RNAT_OFFSET:
			ptr = &pt->ar_rnat;
			अवरोध;
		हाल ELF_AR_CCV_OFFSET:
			ptr = &pt->ar_ccv;
			अवरोध;
		हाल ELF_AR_UNAT_OFFSET:
			ptr = &pt->ar_unat;
			अवरोध;
		हाल ELF_AR_FPSR_OFFSET:
			ptr = &pt->ar_fpsr;
			अवरोध;
		हाल ELF_AR_PFS_OFFSET:
			ptr = &pt->ar_pfs;
			अवरोध;
		हाल ELF_AR_LC_OFFSET:
			वापस unw_access_ar(info, UNW_AR_LC, data,
					     ग_लिखो_access);
		हाल ELF_AR_EC_OFFSET:
			वापस unw_access_ar(info, UNW_AR_EC, data,
					     ग_लिखो_access);
		हाल ELF_AR_CSD_OFFSET:
			ptr = &pt->ar_csd;
			अवरोध;
		हाल ELF_AR_SSD_OFFSET:
			ptr = &pt->ar_ssd;
		पूर्ण
	पूर्ण अन्यथा अगर (addr >= ELF_CR_IIP_OFFSET && addr <= ELF_CR_IPSR_OFFSET) अणु
		चयन (addr) अणु
		हाल ELF_CR_IIP_OFFSET:
			ptr = &pt->cr_iip;
			अवरोध;
		हाल ELF_CFM_OFFSET:
			urbs_end = ia64_get_user_rbs_end(target, pt, &cfm);
			अगर (ग_लिखो_access) अणु
				अगर (((cfm ^ *data) & PFM_MASK) != 0) अणु
					अगर (in_syscall(pt))
						convert_to_non_syscall(target,
								       pt,
								       cfm);
					pt->cr_अगरs = ((pt->cr_अगरs & ~PFM_MASK)
						      | (*data & PFM_MASK));
				पूर्ण
			पूर्ण अन्यथा
				*data = cfm;
			वापस 0;
		हाल ELF_CR_IPSR_OFFSET:
			अगर (ग_लिखो_access) अणु
				अचिन्हित दीर्घ पंचांगp = *data;
				/* psr.ri==3 is a reserved value: SDM 2:25 */
				अगर ((पंचांगp & IA64_PSR_RI) == IA64_PSR_RI)
					पंचांगp &= ~IA64_PSR_RI;
				pt->cr_ipsr = ((पंचांगp & IPSR_MASK)
					       | (pt->cr_ipsr & ~IPSR_MASK));
			पूर्ण अन्यथा
				*data = (pt->cr_ipsr & IPSR_MASK);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (addr == ELF_NAT_OFFSET)
		वापस access_nat_bits(target, pt, info,
				       data, ग_लिखो_access);
	अन्यथा अगर (addr == ELF_PR_OFFSET)
		ptr = &pt->pr;
	अन्यथा
		वापस -1;

	अगर (ग_लिखो_access)
		*ptr = *data;
	अन्यथा
		*data = *ptr;

	वापस 0;
पूर्ण

अटल पूर्णांक
access_elf_reg(काष्ठा task_काष्ठा *target, काष्ठा unw_frame_info *info,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *data, पूर्णांक ग_लिखो_access)
अणु
	अगर (addr >= ELF_GR_OFFSET(1) && addr <= ELF_GR_OFFSET(31))
		वापस access_elf_gpreg(target, info, addr, data, ग_लिखो_access);
	अन्यथा अगर (addr >= ELF_BR_OFFSET(0) && addr <= ELF_BR_OFFSET(7))
		वापस access_elf_breg(target, info, addr, data, ग_लिखो_access);
	अन्यथा
		वापस access_elf_areg(target, info, addr, data, ग_लिखो_access);
पूर्ण

काष्ठा regset_membuf अणु
	काष्ठा membuf to;
	पूर्णांक ret;
पूर्ण;

अटल व्योम करो_gpregs_get(काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	काष्ठा regset_membuf *dst = arg;
	काष्ठा membuf to = dst->to;
	अचिन्हित पूर्णांक n;
	elf_greg_t reg;

	अगर (unw_unwind_to_user(info) < 0)
		वापस;

	/*
	 * coredump क्रमmat:
	 *      r0-r31
	 *      NaT bits (क्रम r0-r31; bit N == 1 अगरf rN is a NaT)
	 *      predicate रेजिस्टरs (p0-p63)
	 *      b0-b7
	 *      ip cfm user-mask
	 *      ar.rsc ar.bsp ar.bspstore ar.rnat
	 *      ar.ccv ar.unat ar.fpsr ar.pfs ar.lc ar.ec
	 */


	/* Skip r0 */
	membuf_zero(&to, 8);
	क्रम (n = 8; to.left && n < ELF_AR_END_OFFSET; n += 8) अणु
		अगर (access_elf_reg(info->task, info, n, &reg, 0) < 0) अणु
			dst->ret = -EIO;
			वापस;
		पूर्ण
		membuf_store(&to, reg);
	पूर्ण
पूर्ण

अटल व्योम करो_gpregs_set(काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	काष्ठा regset_माला_लोet *dst = arg;

	अगर (unw_unwind_to_user(info) < 0)
		वापस;

	अगर (!dst->count)
		वापस;
	/* Skip r0 */
	अगर (dst->pos < ELF_GR_OFFSET(1)) अणु
		dst->ret = user_regset_copyin_ignore(&dst->pos, &dst->count,
						       &dst->u.set.kbuf,
						       &dst->u.set.ubuf,
						       0, ELF_GR_OFFSET(1));
		अगर (dst->ret)
			वापस;
	पूर्ण

	जबतक (dst->count && dst->pos < ELF_AR_END_OFFSET) अणु
		अचिन्हित पूर्णांक n, from, to;
		elf_greg_t पंचांगp[16];

		from = dst->pos;
		to = from + माप(पंचांगp);
		अगर (to > ELF_AR_END_OFFSET)
			to = ELF_AR_END_OFFSET;
		/* get up to 16 values */
		dst->ret = user_regset_copyin(&dst->pos, &dst->count,
				&dst->u.set.kbuf, &dst->u.set.ubuf, पंचांगp,
				from, to);
		अगर (dst->ret)
			वापस;
		/* now copy them पूर्णांकo रेजिस्टरs */
		क्रम (n = 0; from < dst->pos; from += माप(elf_greg_t), n++)
			अगर (access_elf_reg(dst->target, info, from,
						&पंचांगp[n], 1) < 0) अणु
				dst->ret = -EIO;
				वापस;
			पूर्ण
	पूर्ण
पूर्ण

#घोषणा ELF_FP_OFFSET(i)	(i * माप(elf_fpreg_t))

अटल व्योम करो_fpregs_get(काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	काष्ठा task_काष्ठा *task = info->task;
	काष्ठा regset_membuf *dst = arg;
	काष्ठा membuf to = dst->to;
	elf_fpreg_t reg;
	अचिन्हित पूर्णांक n;

	अगर (unw_unwind_to_user(info) < 0)
		वापस;

	/* Skip pos 0 and 1 */
	membuf_zero(&to, 2 * माप(elf_fpreg_t));

	/* fr2-fr31 */
	क्रम (n = 2; to.left && n < 32; n++) अणु
		अगर (unw_get_fr(info, n, &reg)) अणु
			dst->ret = -EIO;
			वापस;
		पूर्ण
		membuf_ग_लिखो(&to, &reg, माप(reg));
	पूर्ण

	/* fph */
	अगर (!to.left)
		वापस;

	ia64_flush_fph(task);
	अगर (task->thपढ़ो.flags & IA64_THREAD_FPH_VALID)
		membuf_ग_लिखो(&to, &task->thपढ़ो.fph, 96 * माप(reg));
	अन्यथा
		membuf_zero(&to, 96 * माप(reg));
पूर्ण

अटल व्योम करो_fpregs_set(काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	काष्ठा regset_माला_लोet *dst = arg;
	elf_fpreg_t fpreg, पंचांगp[30];
	पूर्णांक index, start, end;

	अगर (unw_unwind_to_user(info) < 0)
		वापस;

	/* Skip pos 0 and 1 */
	अगर (dst->count > 0 && dst->pos < ELF_FP_OFFSET(2)) अणु
		dst->ret = user_regset_copyin_ignore(&dst->pos, &dst->count,
						       &dst->u.set.kbuf,
						       &dst->u.set.ubuf,
						       0, ELF_FP_OFFSET(2));
		अगर (dst->count == 0 || dst->ret)
			वापस;
	पूर्ण

	/* fr2-fr31 */
	अगर (dst->count > 0 && dst->pos < ELF_FP_OFFSET(32)) अणु
		start = dst->pos;
		end = min(((अचिन्हित पूर्णांक)ELF_FP_OFFSET(32)),
			 dst->pos + dst->count);
		dst->ret = user_regset_copyin(&dst->pos, &dst->count,
				&dst->u.set.kbuf, &dst->u.set.ubuf, पंचांगp,
				ELF_FP_OFFSET(2), ELF_FP_OFFSET(32));
		अगर (dst->ret)
			वापस;

		अगर (start & 0xF) अणु /* only ग_लिखो high part */
			अगर (unw_get_fr(info, start / माप(elf_fpreg_t),
					 &fpreg)) अणु
				dst->ret = -EIO;
				वापस;
			पूर्ण
			पंचांगp[start / माप(elf_fpreg_t) - 2].u.bits[0]
				= fpreg.u.bits[0];
			start &= ~0xFUL;
		पूर्ण
		अगर (end & 0xF) अणु /* only ग_लिखो low part */
			अगर (unw_get_fr(info, end / माप(elf_fpreg_t),
					&fpreg)) अणु
				dst->ret = -EIO;
				वापस;
			पूर्ण
			पंचांगp[end / माप(elf_fpreg_t) - 2].u.bits[1]
				= fpreg.u.bits[1];
			end = (end + 0xF) & ~0xFUL;
		पूर्ण

		क्रम ( ;	start < end ; start += माप(elf_fpreg_t)) अणु
			index = start / माप(elf_fpreg_t);
			अगर (unw_set_fr(info, index, पंचांगp[index - 2])) अणु
				dst->ret = -EIO;
				वापस;
			पूर्ण
		पूर्ण
		अगर (dst->ret || dst->count == 0)
			वापस;
	पूर्ण

	/* fph */
	अगर (dst->count > 0 && dst->pos < ELF_FP_OFFSET(128)) अणु
		ia64_sync_fph(dst->target);
		dst->ret = user_regset_copyin(&dst->pos, &dst->count,
						&dst->u.set.kbuf,
						&dst->u.set.ubuf,
						&dst->target->thपढ़ो.fph,
						ELF_FP_OFFSET(32), -1);
	पूर्ण
पूर्ण

अटल व्योम
unwind_and_call(व्योम (*call)(काष्ठा unw_frame_info *, व्योम *),
	       काष्ठा task_काष्ठा *target, व्योम *data)
अणु
	अगर (target == current)
		unw_init_running(call, data);
	अन्यथा अणु
		काष्ठा unw_frame_info info;
		स_रखो(&info, 0, माप(info));
		unw_init_from_blocked_task(&info, target);
		(*call)(&info, data);
	पूर्ण
पूर्ण

अटल पूर्णांक
करो_regset_call(व्योम (*call)(काष्ठा unw_frame_info *, व्योम *),
	       काष्ठा task_काष्ठा *target,
	       स्थिर काष्ठा user_regset *regset,
	       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
	       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा regset_माला_लोet info = अणु .target = target, .regset = regset,
				 .pos = pos, .count = count,
				 .u.set = अणु .kbuf = kbuf, .ubuf = ubuf पूर्ण,
				 .ret = 0 पूर्ण;
	unwind_and_call(call, target, &info);
	वापस info.ret;
पूर्ण

अटल पूर्णांक
gpregs_get(काष्ठा task_काष्ठा *target,
	   स्थिर काष्ठा user_regset *regset,
	   काष्ठा membuf to)
अणु
	काष्ठा regset_membuf info = अणु.to = toपूर्ण;
	unwind_and_call(करो_gpregs_get, target, &info);
	वापस info.ret;
पूर्ण

अटल पूर्णांक gpregs_set(काष्ठा task_काष्ठा *target,
		स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	वापस करो_regset_call(करो_gpregs_set, target, regset, pos, count,
		kbuf, ubuf);
पूर्ण

अटल व्योम करो_gpregs_ग_लिखोback(काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	करो_sync_rbs(info, ia64_sync_user_rbs);
पूर्ण

/*
 * This is called to ग_लिखो back the रेजिस्टर backing store.
 * ptrace करोes this beक्रमe it stops, so that a tracer पढ़ोing the user
 * memory after the thपढ़ो stops will get the current रेजिस्टर data.
 */
अटल पूर्णांक
gpregs_ग_लिखोback(काष्ठा task_काष्ठा *target,
		 स्थिर काष्ठा user_regset *regset,
		 पूर्णांक now)
अणु
	अगर (test_and_set_tsk_thपढ़ो_flag(target, TIF_RESTORE_RSE))
		वापस 0;
	set_notअगरy_resume(target);
	वापस करो_regset_call(करो_gpregs_ग_लिखोback, target, regset, 0, 0,
		शून्य, शून्य);
पूर्ण

अटल पूर्णांक
fpregs_active(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset)
अणु
	वापस (target->thपढ़ो.flags & IA64_THREAD_FPH_VALID) ? 128 : 32;
पूर्ण

अटल पूर्णांक fpregs_get(काष्ठा task_काष्ठा *target,
		स्थिर काष्ठा user_regset *regset,
		काष्ठा membuf to)
अणु
	काष्ठा regset_membuf info = अणु.to = toपूर्ण;
	unwind_and_call(करो_fpregs_get, target, &info);
	वापस info.ret;
पूर्ण

अटल पूर्णांक fpregs_set(काष्ठा task_काष्ठा *target,
		स्थिर काष्ठा user_regset *regset,
		अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	वापस करो_regset_call(करो_fpregs_set, target, regset, pos, count,
		kbuf, ubuf);
पूर्ण

अटल पूर्णांक
access_uarea(काष्ठा task_काष्ठा *child, अचिन्हित दीर्घ addr,
	      अचिन्हित दीर्घ *data, पूर्णांक ग_लिखो_access)
अणु
	अचिन्हित पूर्णांक pos = -1; /* an invalid value */
	अचिन्हित दीर्घ *ptr, regnum;

	अगर ((addr & 0x7) != 0) अणु
		dprपूर्णांकk("ptrace: unaligned register address 0x%lx\n", addr);
		वापस -1;
	पूर्ण
	अगर ((addr >= PT_NAT_BITS + 8 && addr < PT_F2) ||
		(addr >= PT_R7 + 8 && addr < PT_B1) ||
		(addr >= PT_AR_LC + 8 && addr < PT_CR_IPSR) ||
		(addr >= PT_AR_SSD + 8 && addr < PT_DBR)) अणु
		dprपूर्णांकk("ptrace: rejecting access to register "
					"address 0x%lx\n", addr);
		वापस -1;
	पूर्ण

	चयन (addr) अणु
	हाल PT_F32 ... (PT_F127 + 15):
		pos = addr - PT_F32 + ELF_FP_OFFSET(32);
		अवरोध;
	हाल PT_F2 ... (PT_F5 + 15):
		pos = addr - PT_F2 + ELF_FP_OFFSET(2);
		अवरोध;
	हाल PT_F10 ... (PT_F31 + 15):
		pos = addr - PT_F10 + ELF_FP_OFFSET(10);
		अवरोध;
	हाल PT_F6 ... (PT_F9 + 15):
		pos = addr - PT_F6 + ELF_FP_OFFSET(6);
		अवरोध;
	पूर्ण

	अगर (pos != -1) अणु
		अचिन्हित reg = pos / माप(elf_fpreg_t);
		पूर्णांक which_half = (pos / माप(अचिन्हित दीर्घ)) & 1;

		अगर (reg < 32) अणु /* fr2-fr31 */
			काष्ठा unw_frame_info info;
			elf_fpreg_t fpreg;

			स_रखो(&info, 0, माप(info));
			unw_init_from_blocked_task(&info, child);
			अगर (unw_unwind_to_user(&info) < 0)
				वापस 0;

			अगर (unw_get_fr(&info, reg, &fpreg))
				वापस -1;
			अगर (ग_लिखो_access) अणु
				fpreg.u.bits[which_half] = *data;
				अगर (unw_set_fr(&info, reg, fpreg))
					वापस -1;
			पूर्ण अन्यथा अणु
				*data = fpreg.u.bits[which_half];
			पूर्ण
		पूर्ण अन्यथा अणु /* fph */
			elf_fpreg_t *p = &child->thपढ़ो.fph[reg - 32];
			अचिन्हित दीर्घ *bits = &p->u.bits[which_half];

			ia64_sync_fph(child);
			अगर (ग_लिखो_access)
				*bits = *data;
			अन्यथा अगर (child->thपढ़ो.flags & IA64_THREAD_FPH_VALID)
				*data = *bits;
			अन्यथा
				*data = 0;
		पूर्ण
		वापस 0;
	पूर्ण

	चयन (addr) अणु
	हाल PT_NAT_BITS:
		pos = ELF_NAT_OFFSET;
		अवरोध;
	हाल PT_R4 ... PT_R7:
		pos = addr - PT_R4 + ELF_GR_OFFSET(4);
		अवरोध;
	हाल PT_B1 ... PT_B5:
		pos = addr - PT_B1 + ELF_BR_OFFSET(1);
		अवरोध;
	हाल PT_AR_EC:
		pos = ELF_AR_EC_OFFSET;
		अवरोध;
	हाल PT_AR_LC:
		pos = ELF_AR_LC_OFFSET;
		अवरोध;
	हाल PT_CR_IPSR:
		pos = ELF_CR_IPSR_OFFSET;
		अवरोध;
	हाल PT_CR_IIP:
		pos = ELF_CR_IIP_OFFSET;
		अवरोध;
	हाल PT_CFM:
		pos = ELF_CFM_OFFSET;
		अवरोध;
	हाल PT_AR_UNAT:
		pos = ELF_AR_UNAT_OFFSET;
		अवरोध;
	हाल PT_AR_PFS:
		pos = ELF_AR_PFS_OFFSET;
		अवरोध;
	हाल PT_AR_RSC:
		pos = ELF_AR_RSC_OFFSET;
		अवरोध;
	हाल PT_AR_RNAT:
		pos = ELF_AR_RNAT_OFFSET;
		अवरोध;
	हाल PT_AR_BSPSTORE:
		pos = ELF_AR_BSPSTORE_OFFSET;
		अवरोध;
	हाल PT_PR:
		pos = ELF_PR_OFFSET;
		अवरोध;
	हाल PT_B6:
		pos = ELF_BR_OFFSET(6);
		अवरोध;
	हाल PT_AR_BSP:
		pos = ELF_AR_BSP_OFFSET;
		अवरोध;
	हाल PT_R1 ... PT_R3:
		pos = addr - PT_R1 + ELF_GR_OFFSET(1);
		अवरोध;
	हाल PT_R12 ... PT_R15:
		pos = addr - PT_R12 + ELF_GR_OFFSET(12);
		अवरोध;
	हाल PT_R8 ... PT_R11:
		pos = addr - PT_R8 + ELF_GR_OFFSET(8);
		अवरोध;
	हाल PT_R16 ... PT_R31:
		pos = addr - PT_R16 + ELF_GR_OFFSET(16);
		अवरोध;
	हाल PT_AR_CCV:
		pos = ELF_AR_CCV_OFFSET;
		अवरोध;
	हाल PT_AR_FPSR:
		pos = ELF_AR_FPSR_OFFSET;
		अवरोध;
	हाल PT_B0:
		pos = ELF_BR_OFFSET(0);
		अवरोध;
	हाल PT_B7:
		pos = ELF_BR_OFFSET(7);
		अवरोध;
	हाल PT_AR_CSD:
		pos = ELF_AR_CSD_OFFSET;
		अवरोध;
	हाल PT_AR_SSD:
		pos = ELF_AR_SSD_OFFSET;
		अवरोध;
	पूर्ण

	अगर (pos != -1) अणु
		काष्ठा unw_frame_info info;

		स_रखो(&info, 0, माप(info));
		unw_init_from_blocked_task(&info, child);
		अगर (unw_unwind_to_user(&info) < 0)
			वापस 0;

		वापस access_elf_reg(child, &info, pos, data, ग_लिखो_access);
	पूर्ण

	/* access debug रेजिस्टरs */
	अगर (addr >= PT_IBR) अणु
		regnum = (addr - PT_IBR) >> 3;
		ptr = &child->thपढ़ो.ibr[0];
	पूर्ण अन्यथा अणु
		regnum = (addr - PT_DBR) >> 3;
		ptr = &child->thपढ़ो.dbr[0];
	पूर्ण

	अगर (regnum >= 8) अणु
		dprपूर्णांकk("ptrace: rejecting access to register "
				"address 0x%lx\n", addr);
		वापस -1;
	पूर्ण

	अगर (!(child->thपढ़ो.flags & IA64_THREAD_DBG_VALID)) अणु
		child->thपढ़ो.flags |= IA64_THREAD_DBG_VALID;
		स_रखो(child->thपढ़ो.dbr, 0,
				माप(child->thपढ़ो.dbr));
		स_रखो(child->thपढ़ो.ibr, 0,
				माप(child->thपढ़ो.ibr));
	पूर्ण

	ptr += regnum;

	अगर ((regnum & 1) && ग_लिखो_access) अणु
		/* करोn't let the user set kernel-level अवरोधpoपूर्णांकs: */
		*ptr = *data & ~(7UL << 56);
		वापस 0;
	पूर्ण
	अगर (ग_लिखो_access)
		*ptr = *data;
	अन्यथा
		*data = *ptr;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा user_regset native_regsets[] = अणु
	अणु
		.core_note_type = NT_PRSTATUS,
		.n = ELF_NGREG,
		.size = माप(elf_greg_t), .align = माप(elf_greg_t),
		.regset_get = gpregs_get, .set = gpregs_set,
		.ग_लिखोback = gpregs_ग_लिखोback
	पूर्ण,
	अणु
		.core_note_type = NT_PRFPREG,
		.n = ELF_NFPREG,
		.size = माप(elf_fpreg_t), .align = माप(elf_fpreg_t),
		.regset_get = fpregs_get, .set = fpregs_set, .active = fpregs_active
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_ia64_view = अणु
	.name = "ia64",
	.e_machine = EM_IA_64,
	.regsets = native_regsets, .n = ARRAY_SIZE(native_regsets)
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *tsk)
अणु
	वापस &user_ia64_view;
पूर्ण

काष्ठा syscall_get_set_args अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक n;
	अचिन्हित दीर्घ *args;
	काष्ठा pt_regs *regs;
	पूर्णांक rw;
पूर्ण;

अटल व्योम syscall_get_set_args_cb(काष्ठा unw_frame_info *info, व्योम *data)
अणु
	काष्ठा syscall_get_set_args *args = data;
	काष्ठा pt_regs *pt = args->regs;
	अचिन्हित दीर्घ *krbs, cfm, ndirty, nlocals, nouts;
	पूर्णांक i, count;

	अगर (unw_unwind_to_user(info) < 0)
		वापस;

	/*
	 * We get here via a few paths:
	 * - अवरोध inकाष्ठाion: cfm is shared with caller.
	 *   syscall args are in out= regs, locals are non-empty.
	 * - epsinकाष्ठाion: cfm is set by br.call
	 *   locals करोn't exist.
	 *
	 * For both हालs argguments are reachable in cfm.sof - cfm.sol.
	 * CFM: [ ... | sor: 17..14 | sol : 13..7 | sof : 6..0 ]
	 */
	cfm = pt->cr_अगरs;
	nlocals = (cfm >> 7) & 0x7f; /* aka sol */
	nouts = (cfm & 0x7f) - nlocals; /* aka sof - sol */
	krbs = (अचिन्हित दीर्घ *)info->task + IA64_RBS_OFFSET/8;
	ndirty = ia64_rse_num_regs(krbs, krbs + (pt->loadrs >> 19));

	count = 0;
	अगर (in_syscall(pt))
		count = min_t(पूर्णांक, args->n, nouts);

	/* Iterate over outs. */
	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक j = ndirty + nlocals + i + args->i;
		अगर (args->rw)
			*ia64_rse_skip_regs(krbs, j) = args->args[i];
		अन्यथा
			args->args[i] = *ia64_rse_skip_regs(krbs, j);
	पूर्ण

	अगर (!args->rw) अणु
		जबतक (i < args->n) अणु
			args->args[i] = 0;
			i++;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ia64_syscall_get_set_arguments(काष्ठा task_काष्ठा *task,
	काष्ठा pt_regs *regs, अचिन्हित दीर्घ *args, पूर्णांक rw)
अणु
	काष्ठा syscall_get_set_args data = अणु
		.i = 0,
		.n = 6,
		.args = args,
		.regs = regs,
		.rw = rw,
	पूर्ण;

	अगर (task == current)
		unw_init_running(syscall_get_set_args_cb, &data);
	अन्यथा अणु
		काष्ठा unw_frame_info ufi;
		स_रखो(&ufi, 0, माप(ufi));
		unw_init_from_blocked_task(&ufi, task);
		syscall_get_set_args_cb(&ufi, &data);
	पूर्ण
पूर्ण
