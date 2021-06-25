<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/ecard.c
 *
 *  Copyright 1995-2001 Russell King
 *
 *  Find all installed expansion cards, and handle पूर्णांकerrupts from them.
 *
 *  Created from inक्रमmation from Acorns RiscOS3 PRMs
 *
 *  08-Dec-1996	RMK	Added code क्रम the 9'th expansion card - the ether
 *			podule slot.
 *  06-May-1997	RMK	Added blacklist क्रम cards whose loader करोesn't work.
 *  12-Sep-1997	RMK	Created new handling of पूर्णांकerrupt enables/disables
 *			- cards can now रेजिस्टर their own routine to control
 *			पूर्णांकerrupts (recommended).
 *  29-Sep-1997	RMK	Expansion card पूर्णांकerrupt hardware not being re-enabled
 *			on reset from Linux. (Caused cards not to respond
 *			under RiscOS without hard reset).
 *  15-Feb-1998	RMK	Added DMA support
 *  12-Sep-1998	RMK	Added EASI support
 *  10-Jan-1999	RMK	Run loaders in a simulated RISC OS environment.
 *  17-Apr-1999	RMK	Support क्रम EASI Type C cycles.
 */
#घोषणा ECARD_C

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/reboot.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/ecard.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "ecard.h"

काष्ठा ecard_request अणु
	व्योम		(*fn)(काष्ठा ecard_request *);
	ecard_t		*ec;
	अचिन्हित पूर्णांक	address;
	अचिन्हित पूर्णांक	length;
	अचिन्हित पूर्णांक	use_loader;
	व्योम		*buffer;
	काष्ठा completion *complete;
पूर्ण;

काष्ठा expcard_quirklist अणु
	अचिन्हित लघु	 manufacturer;
	अचिन्हित लघु	 product;
	स्थिर अक्षर	*type;
	व्योम (*init)(ecard_t *ec);
पूर्ण;

अटल ecard_t *cards;
अटल ecard_t *slot_to_expcard[MAX_ECARDS];
अटल अचिन्हित पूर्णांक ectcr;

अटल व्योम atomwide_3p_quirk(ecard_t *ec);

/* List of descriptions of cards which करोn't have an extended
 * identअगरication, or chunk directories containing a description.
 */
अटल काष्ठा expcard_quirklist quirklist[] __initdata = अणु
	अणु MANU_ACORN, PROD_ACORN_ETHER1, "Acorn Ether1" पूर्ण,
	अणु MANU_ATOMWIDE, PROD_ATOMWIDE_3PSERIAL, शून्य, atomwide_3p_quirk पूर्ण,
पूर्ण;

यंत्रlinkage बाह्य पूर्णांक
ecard_loader_reset(अचिन्हित दीर्घ base, loader_t loader);
यंत्रlinkage बाह्य पूर्णांक
ecard_loader_पढ़ो(पूर्णांक off, अचिन्हित दीर्घ base, loader_t loader);

अटल अंतरभूत अचिन्हित लघु ecard_getu16(अचिन्हित अक्षर *v)
अणु
	वापस v[0] | v[1] << 8;
पूर्ण

अटल अंतरभूत चिन्हित दीर्घ ecard_माला_लो24(अचिन्हित अक्षर *v)
अणु
	वापस v[0] | v[1] << 8 | v[2] << 16 | ((v[2] & 0x80) ? 0xff000000 : 0);
पूर्ण

अटल अंतरभूत ecard_t *slot_to_ecard(अचिन्हित पूर्णांक slot)
अणु
	वापस slot < MAX_ECARDS ? slot_to_expcard[slot] : शून्य;
पूर्ण

/* ===================== Expansion card daemon ======================== */
/*
 * Since the loader programs on the expansion cards need to be run
 * in a specअगरic environment, create a separate task with this
 * environment up, and pass requests to this task as and when we
 * need to.
 *
 * This should allow 99% of loaders to be called from Linux.
 *
 * From a security standpoपूर्णांक, we trust the card venकरोrs.  This
 * may be a misplaced trust.
 */
अटल व्योम ecard_task_reset(काष्ठा ecard_request *req)
अणु
	काष्ठा expansion_card *ec = req->ec;
	काष्ठा resource *res;

	res = ec->slot_no == 8
		? &ec->resource[ECARD_RES_MEMC]
		: ec->easi
		  ? &ec->resource[ECARD_RES_EASI]
		  : &ec->resource[ECARD_RES_IOCSYNC];

	ecard_loader_reset(res->start, ec->loader);
पूर्ण

अटल व्योम ecard_task_पढ़ोbytes(काष्ठा ecard_request *req)
अणु
	काष्ठा expansion_card *ec = req->ec;
	अचिन्हित अक्षर *buf = req->buffer;
	अचिन्हित पूर्णांक len = req->length;
	अचिन्हित पूर्णांक off = req->address;

	अगर (ec->slot_no == 8) अणु
		व्योम __iomem *base = (व्योम __iomem *)
				ec->resource[ECARD_RES_MEMC].start;

		/*
		 * The card मुख्यtains an index which increments the address
		 * पूर्णांकo a 4096-byte page on each access.  We need to keep
		 * track of the counter.
		 */
		अटल अचिन्हित पूर्णांक index;
		अचिन्हित पूर्णांक page;

		page = (off >> 12) * 4;
		अगर (page > 256 * 4)
			वापस;

		off &= 4095;

		/*
		 * If we are पढ़ोing offset 0, or our current index is
		 * greater than the offset, reset the hardware index counter.
		 */
		अगर (off == 0 || index > off) अणु
			ग_लिखोb(0, base);
			index = 0;
		पूर्ण

		/*
		 * Increment the hardware index counter until we get to the
		 * required offset.  The पढ़ो bytes are discarded.
		 */
		जबतक (index < off) अणु
			पढ़ोb(base + page);
			index += 1;
		पूर्ण

		जबतक (len--) अणु
			*buf++ = पढ़ोb(base + page);
			index += 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ base = (ec->easi
			 ? &ec->resource[ECARD_RES_EASI]
			 : &ec->resource[ECARD_RES_IOCSYNC])->start;
		व्योम __iomem *pbase = (व्योम __iomem *)base;

		अगर (!req->use_loader || !ec->loader) अणु
			off *= 4;
			जबतक (len--) अणु
				*buf++ = पढ़ोb(pbase + off);
				off += 4;
			पूर्ण
		पूर्ण अन्यथा अणु
			जबतक(len--) अणु
				/*
				 * The following is required by some
				 * expansion card loader programs.
				 */
				*(अचिन्हित दीर्घ *)0x108 = 0;
				*buf++ = ecard_loader_पढ़ो(off++, base,
							   ec->loader);
			पूर्ण
		पूर्ण
	पूर्ण

पूर्ण

अटल DECLARE_WAIT_QUEUE_HEAD(ecard_रुको);
अटल काष्ठा ecard_request *ecard_req;
अटल DEFINE_MUTEX(ecard_mutex);

/*
 * Set up the expansion card daemon's page tables.
 */
अटल व्योम ecard_init_pgtables(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा vm_area_काष्ठा vma = TLB_FLUSH_VMA(mm, VM_EXEC);

	/* We want to set up the page tables क्रम the following mapping:
	 *  Virtual	Physical
	 *  0x03000000	0x03000000
	 *  0x03010000	unmapped
	 *  0x03210000	0x03210000
	 *  0x03400000	unmapped
	 *  0x08000000	0x08000000
	 *  0x10000000	unmapped
	 *
	 * FIXME: we करोn't follow this 100% yet.
	 */
	pgd_t *src_pgd, *dst_pgd;

	src_pgd = pgd_offset(mm, (अचिन्हित दीर्घ)IO_BASE);
	dst_pgd = pgd_offset(mm, IO_START);

	स_नकल(dst_pgd, src_pgd, माप(pgd_t) * (IO_SIZE / PGसूची_SIZE));

	src_pgd = pgd_offset(mm, (अचिन्हित दीर्घ)EASI_BASE);
	dst_pgd = pgd_offset(mm, EASI_START);

	स_नकल(dst_pgd, src_pgd, माप(pgd_t) * (EASI_SIZE / PGसूची_SIZE));

	flush_tlb_range(&vma, IO_START, IO_START + IO_SIZE);
	flush_tlb_range(&vma, EASI_START, EASI_START + EASI_SIZE);
पूर्ण

अटल पूर्णांक ecard_init_mm(व्योम)
अणु
	काष्ठा mm_काष्ठा * mm = mm_alloc();
	काष्ठा mm_काष्ठा *active_mm = current->active_mm;

	अगर (!mm)
		वापस -ENOMEM;

	current->mm = mm;
	current->active_mm = mm;
	activate_mm(active_mm, mm);
	mmdrop(active_mm);
	ecard_init_pgtables(mm);
	वापस 0;
पूर्ण

अटल पूर्णांक
ecard_task(व्योम * unused)
अणु
	/*
	 * Allocate a mm.  We're not a lazy-TLB kernel task since we need
	 * to set page table entries where the user space would be.  Note
	 * that this also creates the page tables.  Failure is not an
	 * option here.
	 */
	अगर (ecard_init_mm())
		panic("kecardd: unable to alloc mm\n");

	जबतक (1) अणु
		काष्ठा ecard_request *req;

		रुको_event_पूर्णांकerruptible(ecard_रुको, ecard_req != शून्य);

		req = xchg(&ecard_req, शून्य);
		अगर (req != शून्य) अणु
			req->fn(req);
			complete(req->complete);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Wake the expansion card daemon to action our request.
 *
 * FIXME: The test here is not sufficient to detect अगर the
 * kcardd is running.
 */
अटल व्योम ecard_call(काष्ठा ecard_request *req)
अणु
	DECLARE_COMPLETION_ONSTACK(completion);

	req->complete = &completion;

	mutex_lock(&ecard_mutex);
	ecard_req = req;
	wake_up(&ecard_रुको);

	/*
	 * Now रुको क्रम kecardd to run.
	 */
	रुको_क्रम_completion(&completion);
	mutex_unlock(&ecard_mutex);
पूर्ण

/* ======================= Mid-level card control ===================== */

अटल व्योम
ecard_पढ़ोbytes(व्योम *addr, ecard_t *ec, पूर्णांक off, पूर्णांक len, पूर्णांक useld)
अणु
	काष्ठा ecard_request req;

	req.fn		= ecard_task_पढ़ोbytes;
	req.ec		= ec;
	req.address	= off;
	req.length	= len;
	req.use_loader	= useld;
	req.buffer	= addr;

	ecard_call(&req);
पूर्ण

पूर्णांक ecard_पढ़ोchunk(काष्ठा in_chunk_dir *cd, ecard_t *ec, पूर्णांक id, पूर्णांक num)
अणु
	काष्ठा ex_chunk_dir excd;
	पूर्णांक index = 16;
	पूर्णांक useld = 0;

	अगर (!ec->cid.cd)
		वापस 0;

	जबतक(1) अणु
		ecard_पढ़ोbytes(&excd, ec, index, 8, useld);
		index += 8;
		अगर (c_id(&excd) == 0) अणु
			अगर (!useld && ec->loader) अणु
				useld = 1;
				index = 0;
				जारी;
			पूर्ण
			वापस 0;
		पूर्ण
		अगर (c_id(&excd) == 0xf0) अणु /* link */
			index = c_start(&excd);
			जारी;
		पूर्ण
		अगर (c_id(&excd) == 0x80) अणु /* loader */
			अगर (!ec->loader) अणु
				ec->loader = kदो_स्मृति(c_len(&excd),
							       GFP_KERNEL);
				अगर (ec->loader)
					ecard_पढ़ोbytes(ec->loader, ec,
							(पूर्णांक)c_start(&excd),
							c_len(&excd), useld);
				अन्यथा
					वापस 0;
			पूर्ण
			जारी;
		पूर्ण
		अगर (c_id(&excd) == id && num-- == 0)
			अवरोध;
	पूर्ण

	अगर (c_id(&excd) & 0x80) अणु
		चयन (c_id(&excd) & 0x70) अणु
		हाल 0x70:
			ecard_पढ़ोbytes((अचिन्हित अक्षर *)excd.d.string, ec,
					(पूर्णांक)c_start(&excd), c_len(&excd),
					useld);
			अवरोध;
		हाल 0x00:
			अवरोध;
		पूर्ण
	पूर्ण
	cd->start_offset = c_start(&excd);
	स_नकल(cd->d.string, excd.d.string, 256);
	वापस 1;
पूर्ण

/* ======================= Interrupt control ============================ */

अटल व्योम ecard_def_irq_enable(ecard_t *ec, पूर्णांक irqnr)
अणु
पूर्ण

अटल व्योम ecard_def_irq_disable(ecard_t *ec, पूर्णांक irqnr)
अणु
पूर्ण

अटल पूर्णांक ecard_def_irq_pending(ecard_t *ec)
अणु
	वापस !ec->irqmask || पढ़ोb(ec->irqaddr) & ec->irqmask;
पूर्ण

अटल व्योम ecard_def_fiq_enable(ecard_t *ec, पूर्णांक fiqnr)
अणु
	panic("ecard_def_fiq_enable called - impossible");
पूर्ण

अटल व्योम ecard_def_fiq_disable(ecard_t *ec, पूर्णांक fiqnr)
अणु
	panic("ecard_def_fiq_disable called - impossible");
पूर्ण

अटल पूर्णांक ecard_def_fiq_pending(ecard_t *ec)
अणु
	वापस !ec->fiqmask || पढ़ोb(ec->fiqaddr) & ec->fiqmask;
पूर्ण

अटल expansioncard_ops_t ecard_शेष_ops = अणु
	ecard_def_irq_enable,
	ecard_def_irq_disable,
	ecard_def_irq_pending,
	ecard_def_fiq_enable,
	ecard_def_fiq_disable,
	ecard_def_fiq_pending
पूर्ण;

/*
 * Enable and disable पूर्णांकerrupts from expansion cards.
 * (पूर्णांकerrupts are disabled क्रम these functions).
 *
 * They are not meant to be called directly, but via enable/disable_irq.
 */
अटल व्योम ecard_irq_unmask(काष्ठा irq_data *d)
अणु
	ecard_t *ec = irq_data_get_irq_chip_data(d);

	अगर (ec) अणु
		अगर (!ec->ops)
			ec->ops = &ecard_शेष_ops;

		अगर (ec->claimed && ec->ops->irqenable)
			ec->ops->irqenable(ec, d->irq);
		अन्यथा
			prपूर्णांकk(KERN_ERR "ecard: rejecting request to "
				"enable IRQs for %d\n", d->irq);
	पूर्ण
पूर्ण

अटल व्योम ecard_irq_mask(काष्ठा irq_data *d)
अणु
	ecard_t *ec = irq_data_get_irq_chip_data(d);

	अगर (ec) अणु
		अगर (!ec->ops)
			ec->ops = &ecard_शेष_ops;

		अगर (ec->ops && ec->ops->irqdisable)
			ec->ops->irqdisable(ec, d->irq);
	पूर्ण
पूर्ण

अटल काष्ठा irq_chip ecard_chip = अणु
	.name		= "ECARD",
	.irq_ack	= ecard_irq_mask,
	.irq_mask	= ecard_irq_mask,
	.irq_unmask	= ecard_irq_unmask,
पूर्ण;

व्योम ecard_enablefiq(अचिन्हित पूर्णांक fiqnr)
अणु
	ecard_t *ec = slot_to_ecard(fiqnr);

	अगर (ec) अणु
		अगर (!ec->ops)
			ec->ops = &ecard_शेष_ops;

		अगर (ec->claimed && ec->ops->fiqenable)
			ec->ops->fiqenable(ec, fiqnr);
		अन्यथा
			prपूर्णांकk(KERN_ERR "ecard: rejecting request to "
				"enable FIQs for %d\n", fiqnr);
	पूर्ण
पूर्ण

व्योम ecard_disablefiq(अचिन्हित पूर्णांक fiqnr)
अणु
	ecard_t *ec = slot_to_ecard(fiqnr);

	अगर (ec) अणु
		अगर (!ec->ops)
			ec->ops = &ecard_शेष_ops;

		अगर (ec->ops->fiqdisable)
			ec->ops->fiqdisable(ec, fiqnr);
	पूर्ण
पूर्ण

अटल व्योम ecard_dump_irq_state(व्योम)
अणु
	ecard_t *ec;

	prपूर्णांकk("Expansion card IRQ state:\n");

	क्रम (ec = cards; ec; ec = ec->next) अणु
		स्थिर अक्षर *claimed;

		अगर (ec->slot_no == 8)
			जारी;

		claimed = ec->claimed ? "" : "not ";

		अगर (ec->ops && ec->ops->irqpending &&
		    ec->ops != &ecard_शेष_ops)
			prपूर्णांकk("  %d: %sclaimed irq %spending\n",
			       ec->slot_no, claimed,
			       ec->ops->irqpending(ec) ? "" : "not ");
		अन्यथा
			prपूर्णांकk("  %d: %sclaimed irqaddr %p, mask = %02X, status = %02X\n",
			       ec->slot_no, claimed,
			       ec->irqaddr, ec->irqmask, पढ़ोb(ec->irqaddr));
	पूर्ण
पूर्ण

अटल व्योम ecard_check_lockup(काष्ठा irq_desc *desc)
अणु
	अटल अचिन्हित दीर्घ last;
	अटल पूर्णांक lockup;

	/*
	 * If the समयr पूर्णांकerrupt has not run since the last million
	 * unrecognised expansion card पूर्णांकerrupts, then there is
	 * something seriously wrong.  Disable the expansion card
	 * पूर्णांकerrupts so at least we can जारी.
	 *
	 * Maybe we ought to start a समयr to re-enable them some समय
	 * later?
	 */
	अगर (last == jअगरfies) अणु
		lockup += 1;
		अगर (lockup > 1000000) अणु
			prपूर्णांकk(KERN_ERR "\nInterrupt lockup detected - "
			       "disabling all expansion card interrupts\n");

			desc->irq_data.chip->irq_mask(&desc->irq_data);
			ecard_dump_irq_state();
		पूर्ण
	पूर्ण अन्यथा
		lockup = 0;

	/*
	 * If we did not recognise the source of this पूर्णांकerrupt,
	 * warn the user, but करोn't flood the user with these messages.
	 */
	अगर (!last || समय_after(jअगरfies, last + 5*HZ)) अणु
		last = jअगरfies;
		prपूर्णांकk(KERN_WARNING "Unrecognised interrupt from backplane\n");
		ecard_dump_irq_state();
	पूर्ण
पूर्ण

अटल व्योम ecard_irq_handler(काष्ठा irq_desc *desc)
अणु
	ecard_t *ec;
	पूर्णांक called = 0;

	desc->irq_data.chip->irq_mask(&desc->irq_data);
	क्रम (ec = cards; ec; ec = ec->next) अणु
		पूर्णांक pending;

		अगर (!ec->claimed || !ec->irq || ec->slot_no == 8)
			जारी;

		अगर (ec->ops && ec->ops->irqpending)
			pending = ec->ops->irqpending(ec);
		अन्यथा
			pending = ecard_शेष_ops.irqpending(ec);

		अगर (pending) अणु
			generic_handle_irq(ec->irq);
			called ++;
		पूर्ण
	पूर्ण
	desc->irq_data.chip->irq_unmask(&desc->irq_data);

	अगर (called == 0)
		ecard_check_lockup(desc);
पूर्ण

अटल व्योम __iomem *__ecard_address(ecard_t *ec, card_type_t type, card_speed_t speed)
अणु
	व्योम __iomem *address = शून्य;
	पूर्णांक slot = ec->slot_no;

	अगर (ec->slot_no == 8)
		वापस ECARD_MEMC8_BASE;

	ectcr &= ~(1 << slot);

	चयन (type) अणु
	हाल ECARD_MEMC:
		अगर (slot < 4)
			address = ECARD_MEMC_BASE + (slot << 14);
		अवरोध;

	हाल ECARD_IOC:
		अगर (slot < 4)
			address = ECARD_IOC_BASE + (slot << 14);
		अन्यथा
			address = ECARD_IOC4_BASE + ((slot - 4) << 14);
		अगर (address)
			address += speed << 19;
		अवरोध;

	हाल ECARD_EASI:
		address = ECARD_EASI_BASE + (slot << 24);
		अगर (speed == ECARD_FAST)
			ectcr |= 1 << slot;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

#अगर_घोषित IOMD_ECTCR
	iomd_ग_लिखोb(ectcr, IOMD_ECTCR);
#पूर्ण_अगर
	वापस address;
पूर्ण

अटल पूर्णांक ecard_prपूर्णांकs(काष्ठा seq_file *m, ecard_t *ec)
अणु
	seq_म_लिखो(m, "  %d: %s ", ec->slot_no, ec->easi ? "EASI" : "    ");

	अगर (ec->cid.id == 0) अणु
		काष्ठा in_chunk_dir incd;

		seq_म_लिखो(m, "[%04X:%04X] ",
			ec->cid.manufacturer, ec->cid.product);

		अगर (!ec->card_desc && ec->cid.cd &&
		    ecard_पढ़ोchunk(&incd, ec, 0xf5, 0)) अणु
			ec->card_desc = kदो_स्मृति(म_माप(incd.d.string)+1, GFP_KERNEL);

			अगर (ec->card_desc)
				म_नकल((अक्षर *)ec->card_desc, incd.d.string);
		पूर्ण

		seq_म_लिखो(m, "%s\n", ec->card_desc ? ec->card_desc : "*unknown*");
	पूर्ण अन्यथा
		seq_म_लिखो(m, "Simple card %d\n", ec->cid.id);

	वापस 0;
पूर्ण

अटल पूर्णांक ecard_devices_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	ecard_t *ec = cards;

	जबतक (ec) अणु
		ecard_prपूर्णांकs(m, ec);
		ec = ec->next;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा proc_dir_entry *proc_bus_ecard_dir = शून्य;

अटल व्योम ecard_proc_init(व्योम)
अणु
	proc_bus_ecard_dir = proc_सूची_गढ़ो("bus/ecard", शून्य);
	proc_create_single("devices", 0, proc_bus_ecard_dir,
			ecard_devices_proc_show);
पूर्ण

#घोषणा ec_set_resource(ec,nr,st,sz)				\
	करो अणु							\
		(ec)->resource[nr].name = dev_name(&ec->dev);	\
		(ec)->resource[nr].start = st;			\
		(ec)->resource[nr].end = (st) + (sz) - 1;	\
		(ec)->resource[nr].flags = IORESOURCE_MEM;	\
	पूर्ण जबतक (0)

अटल व्योम __init ecard_मुक्त_card(काष्ठा expansion_card *ec)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ECARD_NUM_RESOURCES; i++)
		अगर (ec->resource[i].flags)
			release_resource(&ec->resource[i]);

	kमुक्त(ec);
पूर्ण

अटल काष्ठा expansion_card *__init ecard_alloc_card(पूर्णांक type, पूर्णांक slot)
अणु
	काष्ठा expansion_card *ec;
	अचिन्हित दीर्घ base;
	पूर्णांक i;

	ec = kzalloc(माप(ecard_t), GFP_KERNEL);
	अगर (!ec) अणु
		ec = ERR_PTR(-ENOMEM);
		जाओ nomem;
	पूर्ण

	ec->slot_no = slot;
	ec->easi = type == ECARD_EASI;
	ec->irq = 0;
	ec->fiq = 0;
	ec->dma = NO_DMA;
	ec->ops = &ecard_शेष_ops;

	dev_set_name(&ec->dev, "ecard%d", slot);
	ec->dev.parent = शून्य;
	ec->dev.bus = &ecard_bus_type;
	ec->dev.dma_mask = &ec->dma_mask;
	ec->dma_mask = (u64)0xffffffff;
	ec->dev.coherent_dma_mask = ec->dma_mask;

	अगर (slot < 4) अणु
		ec_set_resource(ec, ECARD_RES_MEMC,
				PODSLOT_MEMC_BASE + (slot << 14),
				PODSLOT_MEMC_SIZE);
		base = PODSLOT_IOC0_BASE + (slot << 14);
	पूर्ण अन्यथा
		base = PODSLOT_IOC4_BASE + ((slot - 4) << 14);

#अगर_घोषित CONFIG_ARCH_RPC
	अगर (slot < 8) अणु
		ec_set_resource(ec, ECARD_RES_EASI,
				PODSLOT_EASI_BASE + (slot << 24),
				PODSLOT_EASI_SIZE);
	पूर्ण

	अगर (slot == 8) अणु
		ec_set_resource(ec, ECARD_RES_MEMC, NETSLOT_BASE, NETSLOT_SIZE);
	पूर्ण अन्यथा
#पूर्ण_अगर

	क्रम (i = 0; i <= ECARD_RES_IOCSYNC - ECARD_RES_IOCSLOW; i++)
		ec_set_resource(ec, i + ECARD_RES_IOCSLOW,
				base + (i << 19), PODSLOT_IOC_SIZE);

	क्रम (i = 0; i < ECARD_NUM_RESOURCES; i++) अणु
		अगर (ec->resource[i].flags &&
		    request_resource(&iomem_resource, &ec->resource[i])) अणु
			dev_err(&ec->dev, "resource(s) not available\n");
			ec->resource[i].end -= ec->resource[i].start;
			ec->resource[i].start = 0;
			ec->resource[i].flags = 0;
		पूर्ण
	पूर्ण

 nomem:
	वापस ec;
पूर्ण

अटल sमाप_प्रकार irq_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	वापस प्र_लिखो(buf, "%u\n", ec->irq);
पूर्ण
अटल DEVICE_ATTR_RO(irq);

अटल sमाप_प्रकार dma_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	वापस प्र_लिखो(buf, "%u\n", ec->dma);
पूर्ण
अटल DEVICE_ATTR_RO(dma);

अटल sमाप_प्रकार resource_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	अक्षर *str = buf;
	पूर्णांक i;

	क्रम (i = 0; i < ECARD_NUM_RESOURCES; i++)
		str += प्र_लिखो(str, "%08x %08x %08lx\n",
				ec->resource[i].start,
				ec->resource[i].end,
				ec->resource[i].flags);

	वापस str - buf;
पूर्ण
अटल DEVICE_ATTR_RO(resource);

अटल sमाप_प्रकार venकरोr_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	वापस प्र_लिखो(buf, "%u\n", ec->cid.manufacturer);
पूर्ण
अटल DEVICE_ATTR_RO(venकरोr);

अटल sमाप_प्रकार device_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	वापस प्र_लिखो(buf, "%u\n", ec->cid.product);
पूर्ण
अटल DEVICE_ATTR_RO(device);

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	वापस प्र_लिखो(buf, "%s\n", ec->easi ? "EASI" : "IOC");
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल काष्ठा attribute *ecard_dev_attrs[] = अणु
	&dev_attr_device.attr,
	&dev_attr_dma.attr,
	&dev_attr_irq.attr,
	&dev_attr_resource.attr,
	&dev_attr_type.attr,
	&dev_attr_venकरोr.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ecard_dev);

पूर्णांक ecard_request_resources(काष्ठा expansion_card *ec)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < ECARD_NUM_RESOURCES; i++) अणु
		अगर (ecard_resource_end(ec, i) &&
		    !request_mem_region(ecard_resource_start(ec, i),
					ecard_resource_len(ec, i),
					ec->dev.driver->name)) अणु
			err = -EBUSY;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (err) अणु
		जबतक (i--)
			अगर (ecard_resource_end(ec, i))
				release_mem_region(ecard_resource_start(ec, i),
						   ecard_resource_len(ec, i));
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(ecard_request_resources);

व्योम ecard_release_resources(काष्ठा expansion_card *ec)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ECARD_NUM_RESOURCES; i++)
		अगर (ecard_resource_end(ec, i))
			release_mem_region(ecard_resource_start(ec, i),
					   ecard_resource_len(ec, i));
पूर्ण
EXPORT_SYMBOL(ecard_release_resources);

व्योम ecard_setirq(काष्ठा expansion_card *ec, स्थिर काष्ठा expansion_card_ops *ops, व्योम *irq_data)
अणु
	ec->irq_data = irq_data;
	barrier();
	ec->ops = ops;
पूर्ण
EXPORT_SYMBOL(ecard_setirq);

व्योम __iomem *ecardm_iomap(काष्ठा expansion_card *ec, अचिन्हित पूर्णांक res,
			   अचिन्हित दीर्घ offset, अचिन्हित दीर्घ maxsize)
अणु
	अचिन्हित दीर्घ start = ecard_resource_start(ec, res);
	अचिन्हित दीर्घ end = ecard_resource_end(ec, res);

	अगर (offset > (end - start))
		वापस शून्य;

	start += offset;
	अगर (maxsize && end - start > maxsize)
		end = start + maxsize;
	
	वापस devm_ioremap(&ec->dev, start, end - start);
पूर्ण
EXPORT_SYMBOL(ecardm_iomap);

अटल व्योम atomwide_3p_quirk(ecard_t *ec)
अणु
	व्योम __iomem *addr = __ecard_address(ec, ECARD_IOC, ECARD_SYNC);
	अचिन्हित पूर्णांक i;

	/* Disable पूर्णांकerrupts on each port */
	क्रम (i = 0x2000; i <= 0x2800; i += 0x0400)
		ग_लिखोb(0, addr + i + 4);	
पूर्ण

/*
 * Probe क्रम an expansion card.
 *
 * If bit 1 of the first byte of the card is set, then the
 * card करोes not exist.
 */
अटल पूर्णांक __init ecard_probe(पूर्णांक slot, अचिन्हित irq, card_type_t type)
अणु
	ecard_t **ecp;
	ecard_t *ec;
	काष्ठा ex_ecid cid;
	व्योम __iomem *addr;
	पूर्णांक i, rc;

	ec = ecard_alloc_card(type, slot);
	अगर (IS_ERR(ec)) अणु
		rc = PTR_ERR(ec);
		जाओ nomem;
	पूर्ण

	rc = -ENODEV;
	अगर ((addr = __ecard_address(ec, type, ECARD_SYNC)) == शून्य)
		जाओ nodev;

	cid.r_zero = 1;
	ecard_पढ़ोbytes(&cid, ec, 0, 16, 0);
	अगर (cid.r_zero)
		जाओ nodev;

	ec->cid.id	= cid.r_id;
	ec->cid.cd	= cid.r_cd;
	ec->cid.is	= cid.r_is;
	ec->cid.w	= cid.r_w;
	ec->cid.manufacturer = ecard_getu16(cid.r_manu);
	ec->cid.product = ecard_getu16(cid.r_prod);
	ec->cid.country = cid.r_country;
	ec->cid.irqmask = cid.r_irqmask;
	ec->cid.irqoff  = ecard_माला_लो24(cid.r_irqoff);
	ec->cid.fiqmask = cid.r_fiqmask;
	ec->cid.fiqoff  = ecard_माला_लो24(cid.r_fiqoff);
	ec->fiqaddr	=
	ec->irqaddr	= addr;

	अगर (ec->cid.is) अणु
		ec->irqmask = ec->cid.irqmask;
		ec->irqaddr += ec->cid.irqoff;
		ec->fiqmask = ec->cid.fiqmask;
		ec->fiqaddr += ec->cid.fiqoff;
	पूर्ण अन्यथा अणु
		ec->irqmask = 1;
		ec->fiqmask = 4;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(quirklist); i++)
		अगर (quirklist[i].manufacturer == ec->cid.manufacturer &&
		    quirklist[i].product == ec->cid.product) अणु
			अगर (quirklist[i].type)
				ec->card_desc = quirklist[i].type;
			अगर (quirklist[i].init)
				quirklist[i].init(ec);
			अवरोध;
		पूर्ण

	ec->irq = irq;

	/*
	 * hook the पूर्णांकerrupt handlers
	 */
	अगर (slot < 8) अणु
		irq_set_chip_and_handler(ec->irq, &ecard_chip,
					 handle_level_irq);
		irq_set_chip_data(ec->irq, ec);
		irq_clear_status_flags(ec->irq, IRQ_NOREQUEST);
	पूर्ण

#अगर_घोषित CONFIG_ARCH_RPC
	/* On RiscPC, only first two slots have DMA capability */
	अगर (slot < 2)
		ec->dma = 2 + slot;
#पूर्ण_अगर

	क्रम (ecp = &cards; *ecp; ecp = &(*ecp)->next);

	*ecp = ec;
	slot_to_expcard[slot] = ec;

	rc = device_रेजिस्टर(&ec->dev);
	अगर (rc)
		जाओ nodev;

	वापस 0;

 nodev:
	ecard_मुक्त_card(ec);
 nomem:
	वापस rc;
पूर्ण

/*
 * Initialise the expansion card प्रणाली.
 * Locate all hardware - पूर्णांकerrupt management and
 * actual cards.
 */
अटल पूर्णांक __init ecard_init(व्योम)
अणु
	काष्ठा task_काष्ठा *task;
	पूर्णांक slot, irqbase;

	irqbase = irq_alloc_descs(-1, 0, 8, -1);
	अगर (irqbase < 0)
		वापस irqbase;

	task = kthपढ़ो_run(ecard_task, शून्य, "kecardd");
	अगर (IS_ERR(task)) अणु
		prपूर्णांकk(KERN_ERR "Ecard: unable to create kernel thread: %ld\n",
		       PTR_ERR(task));
		irq_मुक्त_descs(irqbase, 8);
		वापस PTR_ERR(task);
	पूर्ण

	prपूर्णांकk("Probing expansion cards\n");

	क्रम (slot = 0; slot < 8; slot ++) अणु
		अगर (ecard_probe(slot, irqbase + slot, ECARD_EASI) == -ENODEV)
			ecard_probe(slot, irqbase + slot, ECARD_IOC);
	पूर्ण

	ecard_probe(8, 11, ECARD_IOC);

	irq_set_chained_handler(IRQ_EXPANSIONCARD, ecard_irq_handler);

	ecard_proc_init();

	वापस 0;
पूर्ण

subsys_initcall(ecard_init);

/*
 *	ECARD "bus"
 */
अटल स्थिर काष्ठा ecard_id *
ecard_match_device(स्थिर काष्ठा ecard_id *ids, काष्ठा expansion_card *ec)
अणु
	पूर्णांक i;

	क्रम (i = 0; ids[i].manufacturer != 65535; i++)
		अगर (ec->cid.manufacturer == ids[i].manufacturer &&
		    ec->cid.product == ids[i].product)
			वापस ids + i;

	वापस शून्य;
पूर्ण

अटल पूर्णांक ecard_drv_probe(काष्ठा device *dev)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	काष्ठा ecard_driver *drv = ECARD_DRV(dev->driver);
	स्थिर काष्ठा ecard_id *id;
	पूर्णांक ret;

	id = ecard_match_device(drv->id_table, ec);

	ec->claimed = 1;
	ret = drv->probe(ec, id);
	अगर (ret)
		ec->claimed = 0;
	वापस ret;
पूर्ण

अटल पूर्णांक ecard_drv_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	काष्ठा ecard_driver *drv = ECARD_DRV(dev->driver);

	drv->हटाओ(ec);
	ec->claimed = 0;

	/*
	 * Restore the शेष operations.  We ensure that the
	 * ops are set beक्रमe we change the data.
	 */
	ec->ops = &ecard_शेष_ops;
	barrier();
	ec->irq_data = शून्य;

	वापस 0;
पूर्ण

/*
 * Beक्रमe rebooting, we must make sure that the expansion card is in a
 * sensible state, so it can be re-detected.  This means that the first
 * page of the ROM must be visible.  We call the expansion cards reset
 * handler, अगर any.
 */
अटल व्योम ecard_drv_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(dev);
	काष्ठा ecard_driver *drv = ECARD_DRV(dev->driver);
	काष्ठा ecard_request req;

	अगर (dev->driver) अणु
		अगर (drv->shutकरोwn)
			drv->shutकरोwn(ec);
		ec->claimed = 0;
	पूर्ण

	/*
	 * If this card has a loader, call the reset handler.
	 */
	अगर (ec->loader) अणु
		req.fn = ecard_task_reset;
		req.ec = ec;
		ecard_call(&req);
	पूर्ण
पूर्ण

पूर्णांक ecard_रेजिस्टर_driver(काष्ठा ecard_driver *drv)
अणु
	drv->drv.bus = &ecard_bus_type;

	वापस driver_रेजिस्टर(&drv->drv);
पूर्ण

व्योम ecard_हटाओ_driver(काष्ठा ecard_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->drv);
पूर्ण

अटल पूर्णांक ecard_match(काष्ठा device *_dev, काष्ठा device_driver *_drv)
अणु
	काष्ठा expansion_card *ec = ECARD_DEV(_dev);
	काष्ठा ecard_driver *drv = ECARD_DRV(_drv);
	पूर्णांक ret;

	अगर (drv->id_table) अणु
		ret = ecard_match_device(drv->id_table, ec) != शून्य;
	पूर्ण अन्यथा अणु
		ret = ec->cid.id == drv->id;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा bus_type ecard_bus_type = अणु
	.name		= "ecard",
	.dev_groups	= ecard_dev_groups,
	.match		= ecard_match,
	.probe		= ecard_drv_probe,
	.हटाओ		= ecard_drv_हटाओ,
	.shutकरोwn	= ecard_drv_shutकरोwn,
पूर्ण;

अटल पूर्णांक ecard_bus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&ecard_bus_type);
पूर्ण

postcore_initcall(ecard_bus_init);

EXPORT_SYMBOL(ecard_पढ़ोchunk);
EXPORT_SYMBOL(ecard_रेजिस्टर_driver);
EXPORT_SYMBOL(ecard_हटाओ_driver);
EXPORT_SYMBOL(ecard_bus_type);
