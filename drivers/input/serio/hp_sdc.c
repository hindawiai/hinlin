<शैली गुरु>
/*
 * HP i8042-based System Device Controller driver.
 *
 * Copyright (c) 2001 Brian S. Julin
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *
 * References:
 * System Device Controller Microprocessor Firmware Theory of Operation
 *      क्रम Part Number 1820-4784 Revision B.  Dwg No. A-1820-4784-2
 * Helge Deller's original hilkbd.c port क्रम PA-RISC.
 *
 *
 * Driver theory of operation:
 *
 * hp_sdc_put करोes all writing to the SDC.  ISR can run on a dअगरferent
 * CPU than hp_sdc_put, but only one CPU runs hp_sdc_put at a समय
 * (it cannot really benefit from SMP anyway.)  A tasket fit this perfectly.
 *
 * All data coming back from the SDC is sent via पूर्णांकerrupt and can be पढ़ो
 * fully in the ISR, so there are no latency/throughput problems there.
 * The problem is with output, due to the slow घड़ी speed of the SDC
 * compared to the CPU.  This should not be too horrible most of the समय,
 * but अगर used with HIL devices that support the multibyte transfer command,
 * keeping outbound throughput flowing at the 6500KBps that the HIL is
 * capable of is more than can be करोne at HZ=100.
 *
 * Busy polling क्रम IBF clear wastes CPU cycles and bus cycles.  hp_sdc.ibf
 * is set to 0 when the IBF flag in the status रेजिस्टर has cleared.  ISR
 * may करो this, and may also access the parts of queued transactions related
 * to पढ़ोing data back from the SDC, but otherwise will not touch the
 * hp_sdc state. Whenever a रेजिस्टर is written hp_sdc.ibf is set to 1.
 *
 * The i8042 ग_लिखो index and the values in the 4-byte input buffer
 * starting at 0x70 are kept track of in hp_sdc.wi, and .r7[], respectively,
 * to minimize the amount of IO needed to the SDC.  However these values
 * करो not need to be locked since they are only ever accessed by hp_sdc_put.
 *
 * A समयr task schedules the tasklet once per second just to make
 * sure it करोesn't मुक्तze up and to allow क्रम bad पढ़ोs to समय out.
 */

#समावेश <linux/hp_sdc.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/समय.स>
#समावेश <linux/semaphore.h>
#समावेश <linux/slab.h>
#समावेश <linux/hil.h>
#समावेश <यंत्र/पन.स>

/* Machine-specअगरic असलtraction */

#अगर defined(__hppa__)
# include <यंत्र/parisc-device.h>
# define sdc_पढ़ोb(p)		gsc_पढ़ोb(p)
# define sdc_ग_लिखोb(v,p)	gsc_ग_लिखोb((v),(p))
#या_अगर defined(__mc68000__)
#समावेश <linux/uaccess.h>
# define sdc_पढ़ोb(p)		in_8(p)
# define sdc_ग_लिखोb(v,p)	out_8((p),(v))
#अन्यथा
# error "HIL is not supported on this platform"
#पूर्ण_अगर

#घोषणा PREFIX "HP SDC: "

MODULE_AUTHOR("Brian S. Julin <bri@calyx.com>");
MODULE_DESCRIPTION("HP i8042-based SDC Driver");
MODULE_LICENSE("Dual BSD/GPL");

EXPORT_SYMBOL(hp_sdc_request_समयr_irq);
EXPORT_SYMBOL(hp_sdc_request_hil_irq);
EXPORT_SYMBOL(hp_sdc_request_cooked_irq);

EXPORT_SYMBOL(hp_sdc_release_समयr_irq);
EXPORT_SYMBOL(hp_sdc_release_hil_irq);
EXPORT_SYMBOL(hp_sdc_release_cooked_irq);

EXPORT_SYMBOL(__hp_sdc_enqueue_transaction);
EXPORT_SYMBOL(hp_sdc_enqueue_transaction);
EXPORT_SYMBOL(hp_sdc_dequeue_transaction);

अटल bool hp_sdc_disabled;
module_param_named(no_hpsdc, hp_sdc_disabled, bool, 0);
MODULE_PARM_DESC(no_hpsdc, "Do not enable HP SDC driver.");

अटल hp_i8042_sdc	hp_sdc;	/* All driver state is kept in here. */

/*************** primitives क्रम use in any context *********************/
अटल अंतरभूत uपूर्णांक8_t hp_sdc_status_in8(व्योम)
अणु
	uपूर्णांक8_t status;
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&hp_sdc.ibf_lock, flags);
	status = sdc_पढ़ोb(hp_sdc.status_io);
	अगर (!(status & HP_SDC_STATUS_IBF))
		hp_sdc.ibf = 0;
	ग_लिखो_unlock_irqrestore(&hp_sdc.ibf_lock, flags);

	वापस status;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t hp_sdc_data_in8(व्योम)
अणु
	वापस sdc_पढ़ोb(hp_sdc.data_io);
पूर्ण

अटल अंतरभूत व्योम hp_sdc_status_out8(uपूर्णांक8_t val)
अणु
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&hp_sdc.ibf_lock, flags);
	hp_sdc.ibf = 1;
	अगर ((val & 0xf0) == 0xe0)
		hp_sdc.wi = 0xff;
	sdc_ग_लिखोb(val, hp_sdc.status_io);
	ग_लिखो_unlock_irqrestore(&hp_sdc.ibf_lock, flags);
पूर्ण

अटल अंतरभूत व्योम hp_sdc_data_out8(uपूर्णांक8_t val)
अणु
	अचिन्हित दीर्घ flags;

	ग_लिखो_lock_irqsave(&hp_sdc.ibf_lock, flags);
	hp_sdc.ibf = 1;
	sdc_ग_लिखोb(val, hp_sdc.data_io);
	ग_लिखो_unlock_irqrestore(&hp_sdc.ibf_lock, flags);
पूर्ण

/*	Care must be taken to only invoke hp_sdc_spin_ibf when
 *	असलolutely needed, or in rarely invoked subroutines.
 *	Not only करोes it waste CPU cycles, it also wastes bus cycles.
 */
अटल अंतरभूत व्योम hp_sdc_spin_ibf(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	rwlock_t *lock;

	lock = &hp_sdc.ibf_lock;

	पढ़ो_lock_irqsave(lock, flags);
	अगर (!hp_sdc.ibf) अणु
		पढ़ो_unlock_irqrestore(lock, flags);
		वापस;
	पूर्ण
	पढ़ो_unlock(lock);
	ग_लिखो_lock(lock);
	जबतक (sdc_पढ़ोb(hp_sdc.status_io) & HP_SDC_STATUS_IBF)
		अणु पूर्ण
	hp_sdc.ibf = 0;
	ग_लिखो_unlock_irqrestore(lock, flags);
पूर्ण


/************************ Interrupt context functions ************************/
अटल व्योम hp_sdc_take(पूर्णांक irq, व्योम *dev_id, uपूर्णांक8_t status, uपूर्णांक8_t data)
अणु
	hp_sdc_transaction *curr;

	पढ़ो_lock(&hp_sdc.rtq_lock);
	अगर (hp_sdc.rcurr < 0) अणु
		पढ़ो_unlock(&hp_sdc.rtq_lock);
		वापस;
	पूर्ण
	curr = hp_sdc.tq[hp_sdc.rcurr];
	पढ़ो_unlock(&hp_sdc.rtq_lock);

	curr->seq[curr->idx++] = status;
	curr->seq[curr->idx++] = data;
	hp_sdc.rqty -= 2;
	hp_sdc.rसमय = kसमय_get();

	अगर (hp_sdc.rqty <= 0) अणु
		/* All data has been gathered. */
		अगर (curr->seq[curr->actidx] & HP_SDC_ACT_SEMAPHORE)
			अगर (curr->act.semaphore)
				up(curr->act.semaphore);

		अगर (curr->seq[curr->actidx] & HP_SDC_ACT_CALLBACK)
			अगर (curr->act.irqhook)
				curr->act.irqhook(irq, dev_id, status, data);

		curr->actidx = curr->idx;
		curr->idx++;
		/* Return control of this transaction */
		ग_लिखो_lock(&hp_sdc.rtq_lock);
		hp_sdc.rcurr = -1;
		hp_sdc.rqty = 0;
		ग_लिखो_unlock(&hp_sdc.rtq_lock);
		tasklet_schedule(&hp_sdc.task);
	पूर्ण
पूर्ण

अटल irqवापस_t hp_sdc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	uपूर्णांक8_t status, data;

	status = hp_sdc_status_in8();
	/* Read data unconditionally to advance i8042. */
	data =   hp_sdc_data_in8();

	/* For now we are ignoring these until we get the SDC to behave. */
	अगर (((status & 0xf1) == 0x51) && data == 0x82)
		वापस IRQ_HANDLED;

	चयन (status & HP_SDC_STATUS_IRQMASK) अणु
	हाल 0: /* This हाल is not करोcumented. */
		अवरोध;

	हाल HP_SDC_STATUS_USERTIMER:
	हाल HP_SDC_STATUS_PERIODIC:
	हाल HP_SDC_STATUS_TIMER:
		पढ़ो_lock(&hp_sdc.hook_lock);
		अगर (hp_sdc.समयr != शून्य)
			hp_sdc.समयr(irq, dev_id, status, data);
		पढ़ो_unlock(&hp_sdc.hook_lock);
		अवरोध;

	हाल HP_SDC_STATUS_REG:
		hp_sdc_take(irq, dev_id, status, data);
		अवरोध;

	हाल HP_SDC_STATUS_HILCMD:
	हाल HP_SDC_STATUS_HILDATA:
		पढ़ो_lock(&hp_sdc.hook_lock);
		अगर (hp_sdc.hil != शून्य)
			hp_sdc.hil(irq, dev_id, status, data);
		पढ़ो_unlock(&hp_sdc.hook_lock);
		अवरोध;

	हाल HP_SDC_STATUS_PUP:
		पढ़ो_lock(&hp_sdc.hook_lock);
		अगर (hp_sdc.pup != शून्य)
			hp_sdc.pup(irq, dev_id, status, data);
		अन्यथा
			prपूर्णांकk(KERN_INFO PREFIX "HP SDC reports successful PUP.\n");
		पढ़ो_unlock(&hp_sdc.hook_lock);
		अवरोध;

	शेष:
		पढ़ो_lock(&hp_sdc.hook_lock);
		अगर (hp_sdc.cooked != शून्य)
			hp_sdc.cooked(irq, dev_id, status, data);
		पढ़ो_unlock(&hp_sdc.hook_lock);
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण


अटल irqवापस_t hp_sdc_nmisr(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक status;

	status = hp_sdc_status_in8();
	prपूर्णांकk(KERN_WARNING PREFIX "NMI !\n");

#अगर 0
	अगर (status & HP_SDC_NMISTATUS_FHS) अणु
		पढ़ो_lock(&hp_sdc.hook_lock);
		अगर (hp_sdc.समयr != शून्य)
			hp_sdc.समयr(irq, dev_id, status, 0);
		पढ़ो_unlock(&hp_sdc.hook_lock);
	पूर्ण अन्यथा अणु
		/* TODO: pass this on to the HIL handler, or करो SAK here? */
		prपूर्णांकk(KERN_WARNING PREFIX "HIL NMI\n");
	पूर्ण
#पूर्ण_अगर

	वापस IRQ_HANDLED;
पूर्ण


/***************** Kernel (tasklet) context functions ****************/

अचिन्हित दीर्घ hp_sdc_put(व्योम);

अटल व्योम hp_sdc_tasklet(अचिन्हित दीर्घ foo)
अणु
	ग_लिखो_lock_irq(&hp_sdc.rtq_lock);

	अगर (hp_sdc.rcurr >= 0) अणु
		kसमय_प्रकार now = kसमय_get();

		अगर (kसमय_after(now, kसमय_add_us(hp_sdc.rसमय,
						  HP_SDC_MAX_REG_DELAY))) अणु
			hp_sdc_transaction *curr;
			uपूर्णांक8_t पंचांगp;

			curr = hp_sdc.tq[hp_sdc.rcurr];
			/* If this turns out to be a normal failure mode
			 * we'll need to figure out a way to communicate
			 * it back to the application. and be less verbose.
			 */
			prपूर्णांकk(KERN_WARNING PREFIX "read timeout (%lldus)!\n",
			       kसमय_us_delta(now, hp_sdc.rसमय));
			curr->idx += hp_sdc.rqty;
			hp_sdc.rqty = 0;
			पंचांगp = curr->seq[curr->actidx];
			curr->seq[curr->actidx] |= HP_SDC_ACT_DEAD;
			अगर (पंचांगp & HP_SDC_ACT_SEMAPHORE)
				अगर (curr->act.semaphore)
					up(curr->act.semaphore);

			अगर (पंचांगp & HP_SDC_ACT_CALLBACK) अणु
				/* Note this means that irqhooks may be called
				 * in tasklet/bh context.
				 */
				अगर (curr->act.irqhook)
					curr->act.irqhook(0, शून्य, 0, 0);
			पूर्ण

			curr->actidx = curr->idx;
			curr->idx++;
			hp_sdc.rcurr = -1;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock_irq(&hp_sdc.rtq_lock);
	hp_sdc_put();
पूर्ण

अचिन्हित दीर्घ hp_sdc_put(व्योम)
अणु
	hp_sdc_transaction *curr;
	uपूर्णांक8_t act;
	पूर्णांक idx, curridx;

	पूर्णांक limit = 0;

	ग_लिखो_lock(&hp_sdc.lock);

	/* If i8042 buffers are full, we cannot करो anything that
	   requires output, so we skip to the administrativa. */
	अगर (hp_sdc.ibf) अणु
		hp_sdc_status_in8();
		अगर (hp_sdc.ibf)
			जाओ finish;
	पूर्ण

 anew:
	/* See अगर we are in the middle of a sequence. */
	अगर (hp_sdc.wcurr < 0)
		hp_sdc.wcurr = 0;
	पढ़ो_lock_irq(&hp_sdc.rtq_lock);
	अगर (hp_sdc.rcurr == hp_sdc.wcurr)
		hp_sdc.wcurr++;
	पढ़ो_unlock_irq(&hp_sdc.rtq_lock);
	अगर (hp_sdc.wcurr >= HP_SDC_QUEUE_LEN)
		hp_sdc.wcurr = 0;
	curridx = hp_sdc.wcurr;

	अगर (hp_sdc.tq[curridx] != शून्य)
		जाओ start;

	जबतक (++curridx != hp_sdc.wcurr) अणु
		अगर (curridx >= HP_SDC_QUEUE_LEN) अणु
			curridx = -1; /* Wrap to top */
			जारी;
		पूर्ण
		पढ़ो_lock_irq(&hp_sdc.rtq_lock);
		अगर (hp_sdc.rcurr == curridx) अणु
			पढ़ो_unlock_irq(&hp_sdc.rtq_lock);
			जारी;
		पूर्ण
		पढ़ो_unlock_irq(&hp_sdc.rtq_lock);
		अगर (hp_sdc.tq[curridx] != शून्य)
			अवरोध; /* Found one. */
	पूर्ण
	अगर (curridx == hp_sdc.wcurr) अणु /* There's nothing queued to करो. */
		curridx = -1;
	पूर्ण
	hp_sdc.wcurr = curridx;

 start:

	/* Check to see अगर the पूर्णांकerrupt mask needs to be set. */
	अगर (hp_sdc.set_im) अणु
		hp_sdc_status_out8(hp_sdc.im | HP_SDC_CMD_SET_IM);
		hp_sdc.set_im = 0;
		जाओ finish;
	पूर्ण

	अगर (hp_sdc.wcurr == -1)
		जाओ करोne;

	curr = hp_sdc.tq[curridx];
	idx = curr->actidx;

	अगर (curr->actidx >= curr->endidx) अणु
		hp_sdc.tq[curridx] = शून्य;
		/* Interleave outbound data between the transactions. */
		hp_sdc.wcurr++;
		अगर (hp_sdc.wcurr >= HP_SDC_QUEUE_LEN)
			hp_sdc.wcurr = 0;
		जाओ finish;
	पूर्ण

	act = curr->seq[idx];
	idx++;

	अगर (curr->idx >= curr->endidx) अणु
		अगर (act & HP_SDC_ACT_DEALLOC)
			kमुक्त(curr);
		hp_sdc.tq[curridx] = शून्य;
		/* Interleave outbound data between the transactions. */
		hp_sdc.wcurr++;
		अगर (hp_sdc.wcurr >= HP_SDC_QUEUE_LEN)
			hp_sdc.wcurr = 0;
		जाओ finish;
	पूर्ण

	जबतक (act & HP_SDC_ACT_PRECMD) अणु
		अगर (curr->idx != idx) अणु
			idx++;
			act &= ~HP_SDC_ACT_PRECMD;
			अवरोध;
		पूर्ण
		hp_sdc_status_out8(curr->seq[idx]);
		curr->idx++;
		/* act finished? */
		अगर ((act & HP_SDC_ACT_DURING) == HP_SDC_ACT_PRECMD)
			जाओ actकरोne;
		/* skip quantity field अगर data-out sequence follows. */
		अगर (act & HP_SDC_ACT_DATAOUT)
			curr->idx++;
		जाओ finish;
	पूर्ण
	अगर (act & HP_SDC_ACT_DATAOUT) अणु
		पूर्णांक qty;

		qty = curr->seq[idx];
		idx++;
		अगर (curr->idx - idx < qty) अणु
			hp_sdc_data_out8(curr->seq[curr->idx]);
			curr->idx++;
			/* act finished? */
			अगर (curr->idx - idx >= qty &&
			    (act & HP_SDC_ACT_DURING) == HP_SDC_ACT_DATAOUT)
				जाओ actकरोne;
			जाओ finish;
		पूर्ण
		idx += qty;
		act &= ~HP_SDC_ACT_DATAOUT;
	पूर्ण अन्यथा
	    जबतक (act & HP_SDC_ACT_DATAREG) अणु
		पूर्णांक mask;
		uपूर्णांक8_t w7[4];

		mask = curr->seq[idx];
		अगर (idx != curr->idx) अणु
			idx++;
			idx += !!(mask & 1);
			idx += !!(mask & 2);
			idx += !!(mask & 4);
			idx += !!(mask & 8);
			act &= ~HP_SDC_ACT_DATAREG;
			अवरोध;
		पूर्ण

		w7[0] = (mask & 1) ? curr->seq[++idx] : hp_sdc.r7[0];
		w7[1] = (mask & 2) ? curr->seq[++idx] : hp_sdc.r7[1];
		w7[2] = (mask & 4) ? curr->seq[++idx] : hp_sdc.r7[2];
		w7[3] = (mask & 8) ? curr->seq[++idx] : hp_sdc.r7[3];

		अगर (hp_sdc.wi > 0x73 || hp_sdc.wi < 0x70 ||
		    w7[hp_sdc.wi - 0x70] == hp_sdc.r7[hp_sdc.wi - 0x70]) अणु
			पूर्णांक i = 0;

			/* Need to poपूर्णांक the ग_लिखो index रेजिस्टर */
			जबतक (i < 4 && w7[i] == hp_sdc.r7[i])
				i++;

			अगर (i < 4) अणु
				hp_sdc_status_out8(HP_SDC_CMD_SET_D0 + i);
				hp_sdc.wi = 0x70 + i;
				जाओ finish;
			पूर्ण

			idx++;
			अगर ((act & HP_SDC_ACT_DURING) == HP_SDC_ACT_DATAREG)
				जाओ actकरोne;

			curr->idx = idx;
			act &= ~HP_SDC_ACT_DATAREG;
			अवरोध;
		पूर्ण

		hp_sdc_data_out8(w7[hp_sdc.wi - 0x70]);
		hp_sdc.r7[hp_sdc.wi - 0x70] = w7[hp_sdc.wi - 0x70];
		hp_sdc.wi++; /* ग_लिखो index रेजिस्टर स्वतःincrements */
		अणु
			पूर्णांक i = 0;

			जबतक ((i < 4) && w7[i] == hp_sdc.r7[i])
				i++;
			अगर (i >= 4) अणु
				curr->idx = idx + 1;
				अगर ((act & HP_SDC_ACT_DURING) ==
				    HP_SDC_ACT_DATAREG)
					जाओ actकरोne;
			पूर्ण
		पूर्ण
		जाओ finish;
	पूर्ण
	/* We करोn't go any further in the command अगर there is a pending पढ़ो,
	   because we करोn't want पूर्णांकerleaved results. */
	पढ़ो_lock_irq(&hp_sdc.rtq_lock);
	अगर (hp_sdc.rcurr >= 0) अणु
		पढ़ो_unlock_irq(&hp_sdc.rtq_lock);
		जाओ finish;
	पूर्ण
	पढ़ो_unlock_irq(&hp_sdc.rtq_lock);


	अगर (act & HP_SDC_ACT_POSTCMD) अणु
		uपूर्णांक8_t postcmd;

		/* curr->idx should == idx at this poपूर्णांक. */
		postcmd = curr->seq[idx];
		curr->idx++;
		अगर (act & HP_SDC_ACT_DATAIN) अणु

			/* Start a new पढ़ो */
			hp_sdc.rqty = curr->seq[curr->idx];
			hp_sdc.rसमय = kसमय_get();
			curr->idx++;
			/* Still need to lock here in हाल of spurious irq. */
			ग_लिखो_lock_irq(&hp_sdc.rtq_lock);
			hp_sdc.rcurr = curridx;
			ग_लिखो_unlock_irq(&hp_sdc.rtq_lock);
			hp_sdc_status_out8(postcmd);
			जाओ finish;
		पूर्ण
		hp_sdc_status_out8(postcmd);
		जाओ actकरोne;
	पूर्ण

 actकरोne:
	अगर (act & HP_SDC_ACT_SEMAPHORE)
		up(curr->act.semaphore);
	अन्यथा अगर (act & HP_SDC_ACT_CALLBACK)
		curr->act.irqhook(0,शून्य,0,0);

	अगर (curr->idx >= curr->endidx) अणु /* This transaction is over. */
		अगर (act & HP_SDC_ACT_DEALLOC)
			kमुक्त(curr);
		hp_sdc.tq[curridx] = शून्य;
	पूर्ण अन्यथा अणु
		curr->actidx = idx + 1;
		curr->idx = idx + 2;
	पूर्ण
	/* Interleave outbound data between the transactions. */
	hp_sdc.wcurr++;
	अगर (hp_sdc.wcurr >= HP_SDC_QUEUE_LEN)
		hp_sdc.wcurr = 0;

 finish:
	/* If by some quirk IBF has cleared and our ISR has run to
	   see that that has happened, करो it all again. */
	अगर (!hp_sdc.ibf && limit++ < 20)
		जाओ anew;

 करोne:
	अगर (hp_sdc.wcurr >= 0)
		tasklet_schedule(&hp_sdc.task);
	ग_लिखो_unlock(&hp_sdc.lock);

	वापस 0;
पूर्ण

/******* Functions called in either user or kernel context ****/
पूर्णांक __hp_sdc_enqueue_transaction(hp_sdc_transaction *this)
अणु
	पूर्णांक i;

	अगर (this == शून्य) अणु
		BUG();
		वापस -EINVAL;
	पूर्ण

	/* Can't have same transaction on queue twice */
	क्रम (i = 0; i < HP_SDC_QUEUE_LEN; i++)
		अगर (hp_sdc.tq[i] == this)
			जाओ fail;

	this->actidx = 0;
	this->idx = 1;

	/* Search क्रम empty slot */
	क्रम (i = 0; i < HP_SDC_QUEUE_LEN; i++)
		अगर (hp_sdc.tq[i] == शून्य) अणु
			hp_sdc.tq[i] = this;
			tasklet_schedule(&hp_sdc.task);
			वापस 0;
		पूर्ण

	prपूर्णांकk(KERN_WARNING PREFIX "No free slot to add transaction.\n");
	वापस -EBUSY;

 fail:
	prपूर्णांकk(KERN_WARNING PREFIX "Transaction add failed: transaction already queued?\n");
	वापस -EINVAL;
पूर्ण

पूर्णांक hp_sdc_enqueue_transaction(hp_sdc_transaction *this) अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ग_लिखो_lock_irqsave(&hp_sdc.lock, flags);
	ret = __hp_sdc_enqueue_transaction(this);
	ग_लिखो_unlock_irqrestore(&hp_sdc.lock,flags);

	वापस ret;
पूर्ण

पूर्णांक hp_sdc_dequeue_transaction(hp_sdc_transaction *this)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	ग_लिखो_lock_irqsave(&hp_sdc.lock, flags);

	/* TODO: करोn't remove it if it's not करोne. */

	क्रम (i = 0; i < HP_SDC_QUEUE_LEN; i++)
		अगर (hp_sdc.tq[i] == this)
			hp_sdc.tq[i] = शून्य;

	ग_लिखो_unlock_irqrestore(&hp_sdc.lock, flags);
	वापस 0;
पूर्ण



/********************** User context functions **************************/
पूर्णांक hp_sdc_request_समयr_irq(hp_sdc_irqhook *callback)
अणु
	अगर (callback == शून्य || hp_sdc.dev == शून्य)
		वापस -EINVAL;

	ग_लिखो_lock_irq(&hp_sdc.hook_lock);
	अगर (hp_sdc.समयr != शून्य) अणु
		ग_लिखो_unlock_irq(&hp_sdc.hook_lock);
		वापस -EBUSY;
	पूर्ण

	hp_sdc.समयr = callback;
	/* Enable पूर्णांकerrupts from the समयrs */
	hp_sdc.im &= ~HP_SDC_IM_FH;
        hp_sdc.im &= ~HP_SDC_IM_PT;
	hp_sdc.im &= ~HP_SDC_IM_TIMERS;
	hp_sdc.set_im = 1;
	ग_लिखो_unlock_irq(&hp_sdc.hook_lock);

	tasklet_schedule(&hp_sdc.task);

	वापस 0;
पूर्ण

पूर्णांक hp_sdc_request_hil_irq(hp_sdc_irqhook *callback)
अणु
	अगर (callback == शून्य || hp_sdc.dev == शून्य)
		वापस -EINVAL;

	ग_लिखो_lock_irq(&hp_sdc.hook_lock);
	अगर (hp_sdc.hil != शून्य) अणु
		ग_लिखो_unlock_irq(&hp_sdc.hook_lock);
		वापस -EBUSY;
	पूर्ण

	hp_sdc.hil = callback;
	hp_sdc.im &= ~(HP_SDC_IM_HIL | HP_SDC_IM_RESET);
	hp_sdc.set_im = 1;
	ग_लिखो_unlock_irq(&hp_sdc.hook_lock);

	tasklet_schedule(&hp_sdc.task);

	वापस 0;
पूर्ण

पूर्णांक hp_sdc_request_cooked_irq(hp_sdc_irqhook *callback)
अणु
	अगर (callback == शून्य || hp_sdc.dev == शून्य)
		वापस -EINVAL;

	ग_लिखो_lock_irq(&hp_sdc.hook_lock);
	अगर (hp_sdc.cooked != शून्य) अणु
		ग_लिखो_unlock_irq(&hp_sdc.hook_lock);
		वापस -EBUSY;
	पूर्ण

	/* Enable पूर्णांकerrupts from the HIL MLC */
	hp_sdc.cooked = callback;
	hp_sdc.im &= ~(HP_SDC_IM_HIL | HP_SDC_IM_RESET);
	hp_sdc.set_im = 1;
	ग_लिखो_unlock_irq(&hp_sdc.hook_lock);

	tasklet_schedule(&hp_sdc.task);

	वापस 0;
पूर्ण

पूर्णांक hp_sdc_release_समयr_irq(hp_sdc_irqhook *callback)
अणु
	ग_लिखो_lock_irq(&hp_sdc.hook_lock);
	अगर ((callback != hp_sdc.समयr) ||
	    (hp_sdc.समयr == शून्य)) अणु
		ग_लिखो_unlock_irq(&hp_sdc.hook_lock);
		वापस -EINVAL;
	पूर्ण

	/* Disable पूर्णांकerrupts from the समयrs */
	hp_sdc.समयr = शून्य;
	hp_sdc.im |= HP_SDC_IM_TIMERS;
	hp_sdc.im |= HP_SDC_IM_FH;
	hp_sdc.im |= HP_SDC_IM_PT;
	hp_sdc.set_im = 1;
	ग_लिखो_unlock_irq(&hp_sdc.hook_lock);
	tasklet_schedule(&hp_sdc.task);

	वापस 0;
पूर्ण

पूर्णांक hp_sdc_release_hil_irq(hp_sdc_irqhook *callback)
अणु
	ग_लिखो_lock_irq(&hp_sdc.hook_lock);
	अगर ((callback != hp_sdc.hil) ||
	    (hp_sdc.hil == शून्य)) अणु
		ग_लिखो_unlock_irq(&hp_sdc.hook_lock);
		वापस -EINVAL;
	पूर्ण

	hp_sdc.hil = शून्य;
	/* Disable पूर्णांकerrupts from HIL only अगर there is no cooked driver. */
	अगर(hp_sdc.cooked == शून्य) अणु
		hp_sdc.im |= (HP_SDC_IM_HIL | HP_SDC_IM_RESET);
		hp_sdc.set_im = 1;
	पूर्ण
	ग_लिखो_unlock_irq(&hp_sdc.hook_lock);
	tasklet_schedule(&hp_sdc.task);

	वापस 0;
पूर्ण

पूर्णांक hp_sdc_release_cooked_irq(hp_sdc_irqhook *callback)
अणु
	ग_लिखो_lock_irq(&hp_sdc.hook_lock);
	अगर ((callback != hp_sdc.cooked) ||
	    (hp_sdc.cooked == शून्य)) अणु
		ग_लिखो_unlock_irq(&hp_sdc.hook_lock);
		वापस -EINVAL;
	पूर्ण

	hp_sdc.cooked = शून्य;
	/* Disable पूर्णांकerrupts from HIL only अगर there is no raw HIL driver. */
	अगर(hp_sdc.hil == शून्य) अणु
		hp_sdc.im |= (HP_SDC_IM_HIL | HP_SDC_IM_RESET);
		hp_sdc.set_im = 1;
	पूर्ण
	ग_लिखो_unlock_irq(&hp_sdc.hook_lock);
	tasklet_schedule(&hp_sdc.task);

	वापस 0;
पूर्ण

/************************* Keepalive समयr task *********************/

अटल व्योम hp_sdc_kicker(काष्ठा समयr_list *unused)
अणु
	tasklet_schedule(&hp_sdc.task);
	/* Re-insert the periodic task. */
	mod_समयr(&hp_sdc.kicker, jअगरfies + HZ);
पूर्ण

/************************** Module Initialization ***************************/

#अगर defined(__hppa__)

अटल स्थिर काष्ठा parisc_device_id hp_sdc_tbl[] __initस्थिर = अणु
	अणु
		.hw_type =	HPHW_FIO,
		.hversion_rev =	HVERSION_REV_ANY_ID,
		.hversion =	HVERSION_ANY_ID,
		.sversion =	0x73,
	 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(parisc, hp_sdc_tbl);

अटल पूर्णांक __init hp_sdc_init_hppa(काष्ठा parisc_device *d);
अटल काष्ठा delayed_work moduleloader_work;

अटल काष्ठा parisc_driver hp_sdc_driver __refdata = अणु
	.name =		"hp_sdc",
	.id_table =	hp_sdc_tbl,
	.probe =	hp_sdc_init_hppa,
पूर्ण;

#पूर्ण_अगर /* __hppa__ */

अटल पूर्णांक __init hp_sdc_init(व्योम)
अणु
	अक्षर *errstr;
	hp_sdc_transaction t_sync;
	uपूर्णांक8_t ts_sync[6];
	काष्ठा semaphore s_sync;

	rwlock_init(&hp_sdc.lock);
	rwlock_init(&hp_sdc.ibf_lock);
	rwlock_init(&hp_sdc.rtq_lock);
	rwlock_init(&hp_sdc.hook_lock);

	hp_sdc.समयr		= शून्य;
	hp_sdc.hil		= शून्य;
	hp_sdc.pup		= शून्य;
	hp_sdc.cooked		= शून्य;
	hp_sdc.im		= HP_SDC_IM_MASK;  /* Mask maskable irqs */
	hp_sdc.set_im		= 1;
	hp_sdc.wi		= 0xff;
	hp_sdc.r7[0]		= 0xff;
	hp_sdc.r7[1]		= 0xff;
	hp_sdc.r7[2]		= 0xff;
	hp_sdc.r7[3]		= 0xff;
	hp_sdc.ibf		= 1;

	स_रखो(&hp_sdc.tq, 0, माप(hp_sdc.tq));

	hp_sdc.wcurr		= -1;
        hp_sdc.rcurr		= -1;
	hp_sdc.rqty		= 0;

	hp_sdc.dev_err = -ENODEV;

	errstr = "IO not found for";
	अगर (!hp_sdc.base_io)
		जाओ err0;

	errstr = "IRQ not found for";
	अगर (!hp_sdc.irq)
		जाओ err0;

	hp_sdc.dev_err = -EBUSY;

#अगर defined(__hppa__)
	errstr = "IO not available for";
        अगर (request_region(hp_sdc.data_io, 2, hp_sdc_driver.name))
		जाओ err0;
#पूर्ण_अगर

	errstr = "IRQ not available for";
	अगर (request_irq(hp_sdc.irq, &hp_sdc_isr, IRQF_SHARED,
			"HP SDC", &hp_sdc))
		जाओ err1;

	errstr = "NMI not available for";
	अगर (request_irq(hp_sdc.nmi, &hp_sdc_nmisr, IRQF_SHARED,
			"HP SDC NMI", &hp_sdc))
		जाओ err2;

	pr_info(PREFIX "HP SDC at 0x%08lx, IRQ %d (NMI IRQ %d)\n",
	       hp_sdc.base_io, hp_sdc.irq, hp_sdc.nmi);

	hp_sdc_status_in8();
	hp_sdc_data_in8();

	tasklet_init(&hp_sdc.task, hp_sdc_tasklet, 0);

	/* Sync the output buffer रेजिस्टरs, thus scheduling hp_sdc_tasklet. */
	t_sync.actidx	= 0;
	t_sync.idx	= 1;
	t_sync.endidx	= 6;
	t_sync.seq	= ts_sync;
	ts_sync[0]	= HP_SDC_ACT_DATAREG | HP_SDC_ACT_SEMAPHORE;
	ts_sync[1]	= 0x0f;
	ts_sync[2] = ts_sync[3]	= ts_sync[4] = ts_sync[5] = 0;
	t_sync.act.semaphore = &s_sync;
	sema_init(&s_sync, 0);
	hp_sdc_enqueue_transaction(&t_sync);
	करोwn(&s_sync); /* Wait क्रम t_sync to complete */

	/* Create the keepalive task */
	समयr_setup(&hp_sdc.kicker, hp_sdc_kicker, 0);
	hp_sdc.kicker.expires = jअगरfies + HZ;
	add_समयr(&hp_sdc.kicker);

	hp_sdc.dev_err = 0;
	वापस 0;
 err2:
	मुक्त_irq(hp_sdc.irq, &hp_sdc);
 err1:
	release_region(hp_sdc.data_io, 2);
 err0:
	prपूर्णांकk(KERN_WARNING PREFIX ": %s SDC IO=0x%p IRQ=0x%x NMI=0x%x\n",
		errstr, (व्योम *)hp_sdc.base_io, hp_sdc.irq, hp_sdc.nmi);
	hp_sdc.dev = शून्य;

	वापस hp_sdc.dev_err;
पूर्ण

#अगर defined(__hppa__)

अटल व्योम request_module_delayed(काष्ठा work_काष्ठा *work)
अणु
	request_module("hp_sdc_mlc");
पूर्ण

अटल पूर्णांक __init hp_sdc_init_hppa(काष्ठा parisc_device *d)
अणु
	पूर्णांक ret;

	अगर (!d)
		वापस 1;
	अगर (hp_sdc.dev != शून्य)
		वापस 1;	/* We only expect one SDC */

	hp_sdc.dev		= d;
	hp_sdc.irq		= d->irq;
	hp_sdc.nmi		= d->aux_irq;
	hp_sdc.base_io		= d->hpa.start;
	hp_sdc.data_io		= d->hpa.start + 0x800;
	hp_sdc.status_io	= d->hpa.start + 0x801;

	INIT_DELAYED_WORK(&moduleloader_work, request_module_delayed);

	ret = hp_sdc_init();
	/* after successful initialization give SDC some समय to settle
	 * and then load the hp_sdc_mlc upper layer driver */
	अगर (!ret)
		schedule_delayed_work(&moduleloader_work,
			msecs_to_jअगरfies(2000));

	वापस ret;
पूर्ण

#पूर्ण_अगर /* __hppa__ */

अटल व्योम hp_sdc_निकास(व्योम)
अणु
	/* करो nothing अगर we करोn't have a SDC */
	अगर (!hp_sdc.dev)
		वापस;

	ग_लिखो_lock_irq(&hp_sdc.lock);

	/* Turn off all maskable "sub-function" irq's. */
	hp_sdc_spin_ibf();
	sdc_ग_लिखोb(HP_SDC_CMD_SET_IM | HP_SDC_IM_MASK, hp_sdc.status_io);

	/* Wait until we know this has been processed by the i8042 */
	hp_sdc_spin_ibf();

	मुक्त_irq(hp_sdc.nmi, &hp_sdc);
	मुक्त_irq(hp_sdc.irq, &hp_sdc);
	ग_लिखो_unlock_irq(&hp_sdc.lock);

	del_समयr_sync(&hp_sdc.kicker);

	tasklet_समाप्त(&hp_sdc.task);

#अगर defined(__hppa__)
	cancel_delayed_work_sync(&moduleloader_work);
	अगर (unरेजिस्टर_parisc_driver(&hp_sdc_driver))
		prपूर्णांकk(KERN_WARNING PREFIX "Error unregistering HP SDC");
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init hp_sdc_रेजिस्टर(व्योम)
अणु
	hp_sdc_transaction tq_init;
	uपूर्णांक8_t tq_init_seq[5];
	काष्ठा semaphore tq_init_sem;
#अगर defined(__mc68000__)
	अचिन्हित अक्षर i;
#पूर्ण_अगर

	अगर (hp_sdc_disabled) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "HP SDC driver disabled by no_hpsdc=1.\n");
		वापस -ENODEV;
	पूर्ण

	hp_sdc.dev = शून्य;
	hp_sdc.dev_err = 0;
#अगर defined(__hppa__)
	अगर (रेजिस्टर_parisc_driver(&hp_sdc_driver)) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "Error registering SDC with system bus tree.\n");
		वापस -ENODEV;
	पूर्ण
#या_अगर defined(__mc68000__)
	अगर (!MACH_IS_HP300)
	    वापस -ENODEV;

	hp_sdc.irq	 = 1;
	hp_sdc.nmi	 = 7;
	hp_sdc.base_io	 = (अचिन्हित दीर्घ) 0xf0428000;
	hp_sdc.data_io	 = (अचिन्हित दीर्घ) hp_sdc.base_io + 1;
	hp_sdc.status_io = (अचिन्हित दीर्घ) hp_sdc.base_io + 3;
	अगर (!copy_from_kernel_nofault(&i, (अचिन्हित अक्षर *)hp_sdc.data_io, 1))
		hp_sdc.dev = (व्योम *)1;
	hp_sdc.dev_err   = hp_sdc_init();
#पूर्ण_अगर
	अगर (hp_sdc.dev == शून्य) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "No SDC found.\n");
		वापस hp_sdc.dev_err;
	पूर्ण

	sema_init(&tq_init_sem, 0);

	tq_init.actidx		= 0;
	tq_init.idx		= 1;
	tq_init.endidx		= 5;
	tq_init.seq		= tq_init_seq;
	tq_init.act.semaphore	= &tq_init_sem;

	tq_init_seq[0] =
		HP_SDC_ACT_POSTCMD | HP_SDC_ACT_DATAIN | HP_SDC_ACT_SEMAPHORE;
	tq_init_seq[1] = HP_SDC_CMD_READ_KCC;
	tq_init_seq[2] = 1;
	tq_init_seq[3] = 0;
	tq_init_seq[4] = 0;

	hp_sdc_enqueue_transaction(&tq_init);

	करोwn(&tq_init_sem);
	up(&tq_init_sem);

	अगर ((tq_init_seq[0] & HP_SDC_ACT_DEAD) == HP_SDC_ACT_DEAD) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "Error reading config byte.\n");
		hp_sdc_निकास();
		वापस -ENODEV;
	पूर्ण
	hp_sdc.r11 = tq_init_seq[4];
	अगर (hp_sdc.r11 & HP_SDC_CFG_NEW) अणु
		स्थिर अक्षर *str;
		prपूर्णांकk(KERN_INFO PREFIX "New style SDC\n");
		tq_init_seq[1] = HP_SDC_CMD_READ_XTD;
		tq_init.actidx		= 0;
		tq_init.idx		= 1;
		करोwn(&tq_init_sem);
		hp_sdc_enqueue_transaction(&tq_init);
		करोwn(&tq_init_sem);
		up(&tq_init_sem);
		अगर ((tq_init_seq[0] & HP_SDC_ACT_DEAD) == HP_SDC_ACT_DEAD) अणु
			prपूर्णांकk(KERN_WARNING PREFIX "Error reading extended config byte.\n");
			वापस -ENODEV;
		पूर्ण
		hp_sdc.r7e = tq_init_seq[4];
		HP_SDC_XTD_REV_STRINGS(hp_sdc.r7e & HP_SDC_XTD_REV, str)
		prपूर्णांकk(KERN_INFO PREFIX "Revision: %s\n", str);
		अगर (hp_sdc.r7e & HP_SDC_XTD_BEEPER)
			prपूर्णांकk(KERN_INFO PREFIX "TI SN76494 beeper present\n");
		अगर (hp_sdc.r7e & HP_SDC_XTD_BBRTC)
			prपूर्णांकk(KERN_INFO PREFIX "OKI MSM-58321 BBRTC present\n");
		prपूर्णांकk(KERN_INFO PREFIX "Spunking the self test register to force PUP "
		       "on next firmware reset.\n");
		tq_init_seq[0] = HP_SDC_ACT_PRECMD |
			HP_SDC_ACT_DATAOUT | HP_SDC_ACT_SEMAPHORE;
		tq_init_seq[1] = HP_SDC_CMD_SET_STR;
		tq_init_seq[2] = 1;
		tq_init_seq[3] = 0;
		tq_init.actidx		= 0;
		tq_init.idx		= 1;
		tq_init.endidx		= 4;
		करोwn(&tq_init_sem);
		hp_sdc_enqueue_transaction(&tq_init);
		करोwn(&tq_init_sem);
		up(&tq_init_sem);
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO PREFIX "Old style SDC (1820-%s).\n",
		       (hp_sdc.r11 & HP_SDC_CFG_REV) ? "3300" : "2564/3087");

        वापस 0;
पूर्ण

module_init(hp_sdc_रेजिस्टर);
module_निकास(hp_sdc_निकास);

/* Timing notes:  These measurements taken on my 64MHz 7100-LC (715/64)
 *                                              cycles cycles-adj    समय
 * between two consecutive mfctl(16)'s:              4        n/a    63ns
 * hp_sdc_spin_ibf when idle:                      119        115   1.7us
 * gsc_ग_लिखोb status रेजिस्टर:                      83         79   1.2us
 * IBF to clear after sending SET_IM:             6204       6006    93us
 * IBF to clear after sending LOAD_RT:            4467       4352    68us
 * IBF to clear after sending two LOAD_RTs:      18974      18859   295us
 * READ_T1, पढ़ो status/data, IRQ, call handler: 35564        n/a   556us
 * cmd to ~IBF READ_T1 2nd समय right after:   5158403        n/a    81ms
 * between IRQ received and ~IBF क्रम above:    2578877        n/a    40ms
 *
 * Perक्रमmance stats after a run of this module configuring HIL and
 * receiving a few mouse events:
 *
 * status in8  282508 cycles 7128 calls
 * status out8   8404 cycles  341 calls
 * data out8     1734 cycles   78 calls
 * isr         174324 cycles  617 calls (includes take)
 * take          1241 cycles    2 calls
 * put        1411504 cycles 6937 calls
 * task       1655209 cycles 6937 calls (includes put)
 *
 */
