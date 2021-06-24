<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale MPC85xx/MPC86xx RapidIO RMU support
 *
 * Copyright 2009 Sysgo AG
 * Thomas Moll <thomas.moll@sysgo.com>
 * - fixed मुख्यtenance access routines, check क्रम aligned access
 *
 * Copyright 2009 Integrated Device Technology, Inc.
 * Alex Bounine <alexandre.bounine@idt.com>
 * - Added Port-Write message handling
 * - Added Machine Check exception handling
 *
 * Copyright (C) 2007, 2008, 2010, 2011 Freescale Semiconductor, Inc.
 * Zhang Wei <wei.zhang@मुक्तscale.com>
 * Lian Minghuan-B31939 <Minghuan.Lian@मुक्तscale.com>
 * Liu Gang <Gang.Liu@मुक्तscale.com>
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#समावेश <linux/types.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>

#समावेश "fsl_rio.h"

#घोषणा GET_RMM_HANDLE(mport) \
		(((काष्ठा rio_priv *)(mport->priv))->rmm_handle)

/* RapidIO definition irq, which पढ़ो from OF-tree */
#घोषणा IRQ_RIO_PW(m)		(((काष्ठा fsl_rio_pw *)(m))->pwirq)
#घोषणा IRQ_RIO_BELL(m) (((काष्ठा fsl_rio_dbell *)(m))->bellirq)
#घोषणा IRQ_RIO_TX(m) (((काष्ठा fsl_rmu *)(GET_RMM_HANDLE(m)))->txirq)
#घोषणा IRQ_RIO_RX(m) (((काष्ठा fsl_rmu *)(GET_RMM_HANDLE(m)))->rxirq)

#घोषणा RIO_MIN_TX_RING_SIZE	2
#घोषणा RIO_MAX_TX_RING_SIZE	2048
#घोषणा RIO_MIN_RX_RING_SIZE	2
#घोषणा RIO_MAX_RX_RING_SIZE	2048

#घोषणा RIO_IPWMR_SEN		0x00100000
#घोषणा RIO_IPWMR_QFIE		0x00000100
#घोषणा RIO_IPWMR_EIE		0x00000020
#घोषणा RIO_IPWMR_CQ		0x00000002
#घोषणा RIO_IPWMR_PWE		0x00000001

#घोषणा RIO_IPWSR_QF		0x00100000
#घोषणा RIO_IPWSR_TE		0x00000080
#घोषणा RIO_IPWSR_QFI		0x00000010
#घोषणा RIO_IPWSR_PWD		0x00000008
#घोषणा RIO_IPWSR_PWB		0x00000004

#घोषणा RIO_EPWISR		0x10010
/* EPWISR Error match value */
#घोषणा RIO_EPWISR_PINT1	0x80000000
#घोषणा RIO_EPWISR_PINT2	0x40000000
#घोषणा RIO_EPWISR_MU		0x00000002
#घोषणा RIO_EPWISR_PW		0x00000001

#घोषणा IPWSR_CLEAR		0x98
#घोषणा OMSR_CLEAR		0x1cb3
#घोषणा IMSR_CLEAR		0x491
#घोषणा IDSR_CLEAR		0x91
#घोषणा ODSR_CLEAR		0x1c00
#घोषणा LTLEECSR_ENABLE_ALL	0xFFC000FC
#घोषणा RIO_LTLEECSR		0x060c

#घोषणा RIO_IM0SR		0x64
#घोषणा RIO_IM1SR		0x164
#घोषणा RIO_OM0SR		0x4
#घोषणा RIO_OM1SR		0x104

#घोषणा RIO_DBELL_WIN_SIZE	0x1000

#घोषणा RIO_MSG_OMR_MUI		0x00000002
#घोषणा RIO_MSG_OSR_TE		0x00000080
#घोषणा RIO_MSG_OSR_QOI		0x00000020
#घोषणा RIO_MSG_OSR_QFI		0x00000010
#घोषणा RIO_MSG_OSR_MUB		0x00000004
#घोषणा RIO_MSG_OSR_EOMI	0x00000002
#घोषणा RIO_MSG_OSR_QEI		0x00000001

#घोषणा RIO_MSG_IMR_MI		0x00000002
#घोषणा RIO_MSG_ISR_TE		0x00000080
#घोषणा RIO_MSG_ISR_QFI		0x00000010
#घोषणा RIO_MSG_ISR_DIQI	0x00000001

#घोषणा RIO_MSG_DESC_SIZE	32
#घोषणा RIO_MSG_BUFFER_SIZE	4096

#घोषणा DOORBELL_DMR_DI		0x00000002
#घोषणा DOORBELL_DSR_TE		0x00000080
#घोषणा DOORBELL_DSR_QFI	0x00000010
#घोषणा DOORBELL_DSR_DIQI	0x00000001

#घोषणा DOORBELL_MESSAGE_SIZE	0x08

अटल DEFINE_SPINLOCK(fsl_rio_करोorbell_lock);

काष्ठा rio_msg_regs अणु
	u32 omr;
	u32 osr;
	u32 pad1;
	u32 odqdpar;
	u32 pad2;
	u32 osar;
	u32 odpr;
	u32 odatr;
	u32 odcr;
	u32 pad3;
	u32 odqepar;
	u32 pad4[13];
	u32 imr;
	u32 isr;
	u32 pad5;
	u32 अगरqdpar;
	u32 pad6;
	u32 अगरqepar;
पूर्ण;

काष्ठा rio_dbell_regs अणु
	u32 odmr;
	u32 odsr;
	u32 pad1[4];
	u32 oddpr;
	u32 oddatr;
	u32 pad2[3];
	u32 odretcr;
	u32 pad3[12];
	u32 dmr;
	u32 dsr;
	u32 pad4;
	u32 dqdpar;
	u32 pad5;
	u32 dqepar;
पूर्ण;

काष्ठा rio_pw_regs अणु
	u32 pwmr;
	u32 pwsr;
	u32 epwqbar;
	u32 pwqbar;
पूर्ण;


काष्ठा rio_tx_desc अणु
	u32 pad1;
	u32 saddr;
	u32 dport;
	u32 dattr;
	u32 pad2;
	u32 pad3;
	u32 dwcnt;
	u32 pad4;
पूर्ण;

काष्ठा rio_msg_tx_ring अणु
	व्योम *virt;
	dma_addr_t phys;
	व्योम *virt_buffer[RIO_MAX_TX_RING_SIZE];
	dma_addr_t phys_buffer[RIO_MAX_TX_RING_SIZE];
	पूर्णांक tx_slot;
	पूर्णांक size;
	व्योम *dev_id;
पूर्ण;

काष्ठा rio_msg_rx_ring अणु
	व्योम *virt;
	dma_addr_t phys;
	व्योम *virt_buffer[RIO_MAX_RX_RING_SIZE];
	पूर्णांक rx_slot;
	पूर्णांक size;
	व्योम *dev_id;
पूर्ण;

काष्ठा fsl_rmu अणु
	काष्ठा rio_msg_regs __iomem *msg_regs;
	काष्ठा rio_msg_tx_ring msg_tx_ring;
	काष्ठा rio_msg_rx_ring msg_rx_ring;
	पूर्णांक txirq;
	पूर्णांक rxirq;
पूर्ण;

काष्ठा rio_dbell_msg अणु
	u16 pad1;
	u16 tid;
	u16 sid;
	u16 info;
पूर्ण;

/**
 * fsl_rio_tx_handler - MPC85xx outbound message पूर्णांकerrupt handler
 * @irq: Linux पूर्णांकerrupt number
 * @dev_instance: Poपूर्णांकer to पूर्णांकerrupt-specअगरic data
 *
 * Handles outbound message पूर्णांकerrupts. Executes a रेजिस्टर outbound
 * mailbox event handler and acks the पूर्णांकerrupt occurrence.
 */
अटल irqवापस_t
fsl_rio_tx_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	पूर्णांक osr;
	काष्ठा rio_mport *port = (काष्ठा rio_mport *)dev_instance;
	काष्ठा fsl_rmu *rmu = GET_RMM_HANDLE(port);

	osr = in_be32(&rmu->msg_regs->osr);

	अगर (osr & RIO_MSG_OSR_TE) अणु
		pr_info("RIO: outbound message transmission error\n");
		out_be32(&rmu->msg_regs->osr, RIO_MSG_OSR_TE);
		जाओ out;
	पूर्ण

	अगर (osr & RIO_MSG_OSR_QOI) अणु
		pr_info("RIO: outbound message queue overflow\n");
		out_be32(&rmu->msg_regs->osr, RIO_MSG_OSR_QOI);
		जाओ out;
	पूर्ण

	अगर (osr & RIO_MSG_OSR_EOMI) अणु
		u32 dqp = in_be32(&rmu->msg_regs->odqdpar);
		पूर्णांक slot = (dqp - rmu->msg_tx_ring.phys) >> 5;
		अगर (port->outb_msg[0].mcback != शून्य) अणु
			port->outb_msg[0].mcback(port, rmu->msg_tx_ring.dev_id,
					-1,
					slot);
		पूर्ण
		/* Ack the end-of-message पूर्णांकerrupt */
		out_be32(&rmu->msg_regs->osr, RIO_MSG_OSR_EOMI);
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

/**
 * fsl_rio_rx_handler - MPC85xx inbound message पूर्णांकerrupt handler
 * @irq: Linux पूर्णांकerrupt number
 * @dev_instance: Poपूर्णांकer to पूर्णांकerrupt-specअगरic data
 *
 * Handles inbound message पूर्णांकerrupts. Executes a रेजिस्टरed inbound
 * mailbox event handler and acks the पूर्णांकerrupt occurrence.
 */
अटल irqवापस_t
fsl_rio_rx_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	पूर्णांक isr;
	काष्ठा rio_mport *port = (काष्ठा rio_mport *)dev_instance;
	काष्ठा fsl_rmu *rmu = GET_RMM_HANDLE(port);

	isr = in_be32(&rmu->msg_regs->isr);

	अगर (isr & RIO_MSG_ISR_TE) अणु
		pr_info("RIO: inbound message reception error\n");
		out_be32((व्योम *)&rmu->msg_regs->isr, RIO_MSG_ISR_TE);
		जाओ out;
	पूर्ण

	/* XXX Need to check/dispatch until queue empty */
	अगर (isr & RIO_MSG_ISR_DIQI) अणु
		/*
		* Can receive messages क्रम any mailbox/letter to that
		* mailbox destination. So, make the callback with an
		* unknown/invalid mailbox number argument.
		*/
		अगर (port->inb_msg[0].mcback != शून्य)
			port->inb_msg[0].mcback(port, rmu->msg_rx_ring.dev_id,
				-1,
				-1);

		/* Ack the queueing पूर्णांकerrupt */
		out_be32(&rmu->msg_regs->isr, RIO_MSG_ISR_DIQI);
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

/**
 * fsl_rio_dbell_handler - MPC85xx करोorbell पूर्णांकerrupt handler
 * @irq: Linux पूर्णांकerrupt number
 * @dev_instance: Poपूर्णांकer to पूर्णांकerrupt-specअगरic data
 *
 * Handles करोorbell पूर्णांकerrupts. Parses a list of रेजिस्टरed
 * करोorbell event handlers and executes a matching event handler.
 */
अटल irqवापस_t
fsl_rio_dbell_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	पूर्णांक dsr;
	काष्ठा fsl_rio_dbell *fsl_dbell = (काष्ठा fsl_rio_dbell *)dev_instance;
	पूर्णांक i;

	dsr = in_be32(&fsl_dbell->dbell_regs->dsr);

	अगर (dsr & DOORBELL_DSR_TE) अणु
		pr_info("RIO: doorbell reception error\n");
		out_be32(&fsl_dbell->dbell_regs->dsr, DOORBELL_DSR_TE);
		जाओ out;
	पूर्ण

	अगर (dsr & DOORBELL_DSR_QFI) अणु
		pr_info("RIO: doorbell queue full\n");
		out_be32(&fsl_dbell->dbell_regs->dsr, DOORBELL_DSR_QFI);
	पूर्ण

	/* XXX Need to check/dispatch until queue empty */
	अगर (dsr & DOORBELL_DSR_DIQI) अणु
		काष्ठा rio_dbell_msg *dmsg =
			fsl_dbell->dbell_ring.virt +
			(in_be32(&fsl_dbell->dbell_regs->dqdpar) & 0xfff);
		काष्ठा rio_dbell *dbell;
		पूर्णांक found = 0;

		pr_debug
			("RIO: processing doorbell,"
			" sid %2.2x tid %2.2x info %4.4x\n",
			dmsg->sid, dmsg->tid, dmsg->info);

		क्रम (i = 0; i < MAX_PORT_NUM; i++) अणु
			अगर (fsl_dbell->mport[i]) अणु
				list_क्रम_each_entry(dbell,
					&fsl_dbell->mport[i]->dbells, node) अणु
					अगर ((dbell->res->start
						<= dmsg->info)
						&& (dbell->res->end
						>= dmsg->info)) अणु
						found = 1;
						अवरोध;
					पूर्ण
				पूर्ण
				अगर (found && dbell->dinb) अणु
					dbell->dinb(fsl_dbell->mport[i],
						dbell->dev_id, dmsg->sid,
						dmsg->tid,
						dmsg->info);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			pr_debug
				("RIO: spurious doorbell,"
				" sid %2.2x tid %2.2x info %4.4x\n",
				dmsg->sid, dmsg->tid,
				dmsg->info);
		पूर्ण
		setbits32(&fsl_dbell->dbell_regs->dmr, DOORBELL_DMR_DI);
		out_be32(&fsl_dbell->dbell_regs->dsr, DOORBELL_DSR_DIQI);
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

व्योम msg_unit_error_handler(व्योम)
अणु

	/*XXX: Error recovery is not implemented, we just clear errors */
	out_be32((u32 *)(rio_regs_win + RIO_LTLEDCSR), 0);

	out_be32((u32 *)(rmu_regs_win + RIO_IM0SR), IMSR_CLEAR);
	out_be32((u32 *)(rmu_regs_win + RIO_IM1SR), IMSR_CLEAR);
	out_be32((u32 *)(rmu_regs_win + RIO_OM0SR), OMSR_CLEAR);
	out_be32((u32 *)(rmu_regs_win + RIO_OM1SR), OMSR_CLEAR);

	out_be32(&dbell->dbell_regs->odsr, ODSR_CLEAR);
	out_be32(&dbell->dbell_regs->dsr, IDSR_CLEAR);

	out_be32(&pw->pw_regs->pwsr, IPWSR_CLEAR);
पूर्ण

/**
 * fsl_rio_port_ग_लिखो_handler - MPC85xx port ग_लिखो पूर्णांकerrupt handler
 * @irq: Linux पूर्णांकerrupt number
 * @dev_instance: Poपूर्णांकer to पूर्णांकerrupt-specअगरic data
 *
 * Handles port ग_लिखो पूर्णांकerrupts. Parses a list of रेजिस्टरed
 * port ग_लिखो event handlers and executes a matching event handler.
 */
अटल irqवापस_t
fsl_rio_port_ग_लिखो_handler(पूर्णांक irq, व्योम *dev_instance)
अणु
	u32 ipwmr, ipwsr;
	काष्ठा fsl_rio_pw *pw = (काष्ठा fsl_rio_pw *)dev_instance;
	u32 epwisr, पंचांगp;

	epwisr = in_be32(rio_regs_win + RIO_EPWISR);
	अगर (!(epwisr & RIO_EPWISR_PW))
		जाओ pw_करोne;

	ipwmr = in_be32(&pw->pw_regs->pwmr);
	ipwsr = in_be32(&pw->pw_regs->pwsr);

#अगर_घोषित DEBUG_PW
	pr_debug("PW Int->IPWMR: 0x%08x IPWSR: 0x%08x (", ipwmr, ipwsr);
	अगर (ipwsr & RIO_IPWSR_QF)
		pr_debug(" QF");
	अगर (ipwsr & RIO_IPWSR_TE)
		pr_debug(" TE");
	अगर (ipwsr & RIO_IPWSR_QFI)
		pr_debug(" QFI");
	अगर (ipwsr & RIO_IPWSR_PWD)
		pr_debug(" PWD");
	अगर (ipwsr & RIO_IPWSR_PWB)
		pr_debug(" PWB");
	pr_debug(" )\n");
#पूर्ण_अगर
	/* Schedule deferred processing अगर PW was received */
	अगर (ipwsr & RIO_IPWSR_QFI) अणु
		/* Save PW message (अगर there is room in FIFO),
		 * otherwise discard it.
		 */
		अगर (kfअगरo_avail(&pw->pw_fअगरo) >= RIO_PW_MSG_SIZE) अणु
			pw->port_ग_लिखो_msg.msg_count++;
			kfअगरo_in(&pw->pw_fअगरo, pw->port_ग_लिखो_msg.virt,
				 RIO_PW_MSG_SIZE);
		पूर्ण अन्यथा अणु
			pw->port_ग_लिखो_msg.discard_count++;
			pr_debug("RIO: ISR Discarded Port-Write Msg(s) (%d)\n",
				 pw->port_ग_लिखो_msg.discard_count);
		पूर्ण
		/* Clear पूर्णांकerrupt and issue Clear Queue command. This allows
		 * another port-ग_लिखो to be received.
		 */
		out_be32(&pw->pw_regs->pwsr,	RIO_IPWSR_QFI);
		out_be32(&pw->pw_regs->pwmr, ipwmr | RIO_IPWMR_CQ);

		schedule_work(&pw->pw_work);
	पूर्ण

	अगर ((ipwmr & RIO_IPWMR_EIE) && (ipwsr & RIO_IPWSR_TE)) अणु
		pw->port_ग_लिखो_msg.err_count++;
		pr_debug("RIO: Port-Write Transaction Err (%d)\n",
			 pw->port_ग_लिखो_msg.err_count);
		/* Clear Transaction Error: port-ग_लिखो controller should be
		 * disabled when clearing this error
		 */
		out_be32(&pw->pw_regs->pwmr, ipwmr & ~RIO_IPWMR_PWE);
		out_be32(&pw->pw_regs->pwsr,	RIO_IPWSR_TE);
		out_be32(&pw->pw_regs->pwmr, ipwmr);
	पूर्ण

	अगर (ipwsr & RIO_IPWSR_PWD) अणु
		pw->port_ग_लिखो_msg.discard_count++;
		pr_debug("RIO: Port Discarded Port-Write Msg(s) (%d)\n",
			 pw->port_ग_लिखो_msg.discard_count);
		out_be32(&pw->pw_regs->pwsr, RIO_IPWSR_PWD);
	पूर्ण

pw_करोne:
	अगर (epwisr & RIO_EPWISR_PINT1) अणु
		पंचांगp = in_be32(rio_regs_win + RIO_LTLEDCSR);
		pr_debug("RIO_LTLEDCSR = 0x%x\n", पंचांगp);
		fsl_rio_port_error_handler(0);
	पूर्ण

	अगर (epwisr & RIO_EPWISR_PINT2) अणु
		पंचांगp = in_be32(rio_regs_win + RIO_LTLEDCSR);
		pr_debug("RIO_LTLEDCSR = 0x%x\n", पंचांगp);
		fsl_rio_port_error_handler(1);
	पूर्ण

	अगर (epwisr & RIO_EPWISR_MU) अणु
		पंचांगp = in_be32(rio_regs_win + RIO_LTLEDCSR);
		pr_debug("RIO_LTLEDCSR = 0x%x\n", पंचांगp);
		msg_unit_error_handler();
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम fsl_pw_dpc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fsl_rio_pw *pw = container_of(work, काष्ठा fsl_rio_pw, pw_work);
	जोड़ rio_pw_msg msg_buffer;
	पूर्णांक i;

	/*
	 * Process port-ग_लिखो messages
	 */
	जबतक (kfअगरo_out_spinlocked(&pw->pw_fअगरo, (अचिन्हित अक्षर *)&msg_buffer,
			 RIO_PW_MSG_SIZE, &pw->pw_fअगरo_lock)) अणु
#अगर_घोषित DEBUG_PW
		अणु
		u32 i;
		pr_debug("%s : Port-Write Message:", __func__);
		क्रम (i = 0; i < RIO_PW_MSG_SIZE/माप(u32); i++) अणु
			अगर ((i%4) == 0)
				pr_debug("\n0x%02x: 0x%08x", i*4,
					 msg_buffer.raw[i]);
			अन्यथा
				pr_debug(" 0x%08x", msg_buffer.raw[i]);
		पूर्ण
		pr_debug("\n");
		पूर्ण
#पूर्ण_अगर
		/* Pass the port-ग_लिखो message to RIO core क्रम processing */
		क्रम (i = 0; i < MAX_PORT_NUM; i++) अणु
			अगर (pw->mport[i])
				rio_inb_pग_लिखो_handler(pw->mport[i],
						       &msg_buffer);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * fsl_rio_pw_enable - enable/disable port-ग_लिखो पूर्णांकerface init
 * @mport: Master port implementing the port ग_लिखो unit
 * @enable:    1=enable; 0=disable port-ग_लिखो message handling
 */
पूर्णांक fsl_rio_pw_enable(काष्ठा rio_mport *mport, पूर्णांक enable)
अणु
	u32 rval;

	rval = in_be32(&pw->pw_regs->pwmr);

	अगर (enable)
		rval |= RIO_IPWMR_PWE;
	अन्यथा
		rval &= ~RIO_IPWMR_PWE;

	out_be32(&pw->pw_regs->pwmr, rval);

	वापस 0;
पूर्ण

/**
 * fsl_rio_port_ग_लिखो_init - MPC85xx port ग_लिखो पूर्णांकerface init
 * @mport: Master port implementing the port ग_लिखो unit
 *
 * Initializes port ग_लिखो unit hardware and DMA buffer
 * ring. Called from fsl_rio_setup(). Returns %0 on success
 * or %-ENOMEM on failure.
 */

पूर्णांक fsl_rio_port_ग_लिखो_init(काष्ठा fsl_rio_pw *pw)
अणु
	पूर्णांक rc = 0;

	/* Following configurations require a disabled port ग_लिखो controller */
	out_be32(&pw->pw_regs->pwmr,
		 in_be32(&pw->pw_regs->pwmr) & ~RIO_IPWMR_PWE);

	/* Initialize port ग_लिखो */
	pw->port_ग_लिखो_msg.virt = dma_alloc_coherent(pw->dev,
					RIO_PW_MSG_SIZE,
					&pw->port_ग_लिखो_msg.phys, GFP_KERNEL);
	अगर (!pw->port_ग_लिखो_msg.virt) अणु
		pr_err("RIO: unable allocate port write queue\n");
		वापस -ENOMEM;
	पूर्ण

	pw->port_ग_लिखो_msg.err_count = 0;
	pw->port_ग_लिखो_msg.discard_count = 0;

	/* Poपूर्णांक dequeue/enqueue poपूर्णांकers at first entry */
	out_be32(&pw->pw_regs->epwqbar, 0);
	out_be32(&pw->pw_regs->pwqbar, (u32) pw->port_ग_लिखो_msg.phys);

	pr_debug("EIPWQBAR: 0x%08x IPWQBAR: 0x%08x\n",
		 in_be32(&pw->pw_regs->epwqbar),
		 in_be32(&pw->pw_regs->pwqbar));

	/* Clear पूर्णांकerrupt status IPWSR */
	out_be32(&pw->pw_regs->pwsr,
		 (RIO_IPWSR_TE | RIO_IPWSR_QFI | RIO_IPWSR_PWD));

	/* Configure port ग_लिखो controller क्रम snooping enable all reporting,
	   clear queue full */
	out_be32(&pw->pw_regs->pwmr,
		 RIO_IPWMR_SEN | RIO_IPWMR_QFIE | RIO_IPWMR_EIE | RIO_IPWMR_CQ);


	/* Hook up port-ग_लिखो handler */
	rc = request_irq(IRQ_RIO_PW(pw), fsl_rio_port_ग_लिखो_handler,
			IRQF_SHARED, "port-write", (व्योम *)pw);
	अगर (rc < 0) अणु
		pr_err("MPC85xx RIO: unable to request inbound doorbell irq");
		जाओ err_out;
	पूर्ण
	/* Enable Error Interrupt */
	out_be32((u32 *)(rio_regs_win + RIO_LTLEECSR), LTLEECSR_ENABLE_ALL);

	INIT_WORK(&pw->pw_work, fsl_pw_dpc);
	spin_lock_init(&pw->pw_fअगरo_lock);
	अगर (kfअगरo_alloc(&pw->pw_fअगरo, RIO_PW_MSG_SIZE * 32, GFP_KERNEL)) अणु
		pr_err("FIFO allocation failed\n");
		rc = -ENOMEM;
		जाओ err_out_irq;
	पूर्ण

	pr_debug("IPWMR: 0x%08x IPWSR: 0x%08x\n",
		 in_be32(&pw->pw_regs->pwmr),
		 in_be32(&pw->pw_regs->pwsr));

	वापस rc;

err_out_irq:
	मुक्त_irq(IRQ_RIO_PW(pw), (व्योम *)pw);
err_out:
	dma_मुक्त_coherent(pw->dev, RIO_PW_MSG_SIZE,
		pw->port_ग_लिखो_msg.virt,
		pw->port_ग_लिखो_msg.phys);
	वापस rc;
पूर्ण

/**
 * fsl_rio_करोorbell_send - Send a MPC85xx करोorbell message
 * @mport: RapidIO master port info
 * @index: ID of RapidIO पूर्णांकerface
 * @destid: Destination ID of target device
 * @data: 16-bit info field of RapidIO करोorbell message
 *
 * Sends a MPC85xx करोorbell message. Returns %0 on success or
 * %-EINVAL on failure.
 */
पूर्णांक fsl_rio_करोorbell_send(काष्ठा rio_mport *mport,
				पूर्णांक index, u16 destid, u16 data)
अणु
	अचिन्हित दीर्घ flags;

	pr_debug("fsl_doorbell_send: index %d destid %4.4x data %4.4x\n",
		 index, destid, data);

	spin_lock_irqsave(&fsl_rio_करोorbell_lock, flags);

	/* In the serial version silicons, such as MPC8548, MPC8641,
	 * below operations is must be.
	 */
	out_be32(&dbell->dbell_regs->odmr, 0x00000000);
	out_be32(&dbell->dbell_regs->odretcr, 0x00000004);
	out_be32(&dbell->dbell_regs->oddpr, destid << 16);
	out_be32(&dbell->dbell_regs->oddatr, (index << 20) | data);
	out_be32(&dbell->dbell_regs->odmr, 0x00000001);

	spin_unlock_irqrestore(&fsl_rio_करोorbell_lock, flags);

	वापस 0;
पूर्ण

/**
 * fsl_add_outb_message - Add message to the MPC85xx outbound message queue
 * @mport: Master port with outbound message queue
 * @rdev: Target of outbound message
 * @mbox: Outbound mailbox
 * @buffer: Message to add to outbound queue
 * @len: Length of message
 *
 * Adds the @buffer message to the MPC85xx outbound message queue. Returns
 * %0 on success or %-EINVAL on failure.
 */
पूर्णांक
fsl_add_outb_message(काष्ठा rio_mport *mport, काष्ठा rio_dev *rdev, पूर्णांक mbox,
			व्योम *buffer, माप_प्रकार len)
अणु
	काष्ठा fsl_rmu *rmu = GET_RMM_HANDLE(mport);
	u32 omr;
	काष्ठा rio_tx_desc *desc = (काष्ठा rio_tx_desc *)rmu->msg_tx_ring.virt
					+ rmu->msg_tx_ring.tx_slot;
	पूर्णांक ret = 0;

	pr_debug("RIO: fsl_add_outb_message(): destid %4.4x mbox %d buffer " \
		 "%p len %8.8zx\n", rdev->destid, mbox, buffer, len);
	अगर ((len < 8) || (len > RIO_MAX_MSG_SIZE)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* Copy and clear rest of buffer */
	स_नकल(rmu->msg_tx_ring.virt_buffer[rmu->msg_tx_ring.tx_slot], buffer,
			len);
	अगर (len < (RIO_MAX_MSG_SIZE - 4))
		स_रखो(rmu->msg_tx_ring.virt_buffer[rmu->msg_tx_ring.tx_slot]
				+ len, 0, RIO_MAX_MSG_SIZE - len);

	/* Set mbox field क्रम message, and set destid */
	desc->dport = (rdev->destid << 16) | (mbox & 0x3);

	/* Enable EOMI पूर्णांकerrupt and priority */
	desc->dattr = 0x28000000 | ((mport->index) << 20);

	/* Set transfer size aligned to next घातer of 2 (in द्विगुन words) */
	desc->dwcnt = is_घातer_of_2(len) ? len : 1 << get_biपंचांगask_order(len);

	/* Set snooping and source buffer address */
	desc->saddr = 0x00000004
		| rmu->msg_tx_ring.phys_buffer[rmu->msg_tx_ring.tx_slot];

	/* Increment enqueue poपूर्णांकer */
	omr = in_be32(&rmu->msg_regs->omr);
	out_be32(&rmu->msg_regs->omr, omr | RIO_MSG_OMR_MUI);

	/* Go to next descriptor */
	अगर (++rmu->msg_tx_ring.tx_slot == rmu->msg_tx_ring.size)
		rmu->msg_tx_ring.tx_slot = 0;

out:
	वापस ret;
पूर्ण

/**
 * fsl_खोलो_outb_mbox - Initialize MPC85xx outbound mailbox
 * @mport: Master port implementing the outbound message unit
 * @dev_id: Device specअगरic poपूर्णांकer to pass on event
 * @mbox: Mailbox to खोलो
 * @entries: Number of entries in the outbound mailbox ring
 *
 * Initializes buffer ring, request the outbound message पूर्णांकerrupt,
 * and enables the outbound message unit. Returns %0 on success and
 * %-EINVAL or %-ENOMEM on failure.
 */
पूर्णांक
fsl_खोलो_outb_mbox(काष्ठा rio_mport *mport, व्योम *dev_id, पूर्णांक mbox, पूर्णांक entries)
अणु
	पूर्णांक i, j, rc = 0;
	काष्ठा rio_priv *priv = mport->priv;
	काष्ठा fsl_rmu *rmu = GET_RMM_HANDLE(mport);

	अगर ((entries < RIO_MIN_TX_RING_SIZE) ||
		(entries > RIO_MAX_TX_RING_SIZE) || (!is_घातer_of_2(entries))) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* Initialize shaकरोw copy ring */
	rmu->msg_tx_ring.dev_id = dev_id;
	rmu->msg_tx_ring.size = entries;

	क्रम (i = 0; i < rmu->msg_tx_ring.size; i++) अणु
		rmu->msg_tx_ring.virt_buffer[i] =
			dma_alloc_coherent(priv->dev, RIO_MSG_BUFFER_SIZE,
				&rmu->msg_tx_ring.phys_buffer[i], GFP_KERNEL);
		अगर (!rmu->msg_tx_ring.virt_buffer[i]) अणु
			rc = -ENOMEM;
			क्रम (j = 0; j < rmu->msg_tx_ring.size; j++)
				अगर (rmu->msg_tx_ring.virt_buffer[j])
					dma_मुक्त_coherent(priv->dev,
							RIO_MSG_BUFFER_SIZE,
							rmu->msg_tx_ring.
							virt_buffer[j],
							rmu->msg_tx_ring.
							phys_buffer[j]);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Initialize outbound message descriptor ring */
	rmu->msg_tx_ring.virt = dma_alloc_coherent(priv->dev,
						   rmu->msg_tx_ring.size * RIO_MSG_DESC_SIZE,
						   &rmu->msg_tx_ring.phys,
						   GFP_KERNEL);
	अगर (!rmu->msg_tx_ring.virt) अणु
		rc = -ENOMEM;
		जाओ out_dma;
	पूर्ण
	rmu->msg_tx_ring.tx_slot = 0;

	/* Poपूर्णांक dequeue/enqueue poपूर्णांकers at first entry in ring */
	out_be32(&rmu->msg_regs->odqdpar, rmu->msg_tx_ring.phys);
	out_be32(&rmu->msg_regs->odqepar, rmu->msg_tx_ring.phys);

	/* Configure क्रम snooping */
	out_be32(&rmu->msg_regs->osar, 0x00000004);

	/* Clear पूर्णांकerrupt status */
	out_be32(&rmu->msg_regs->osr, 0x000000b3);

	/* Hook up outbound message handler */
	rc = request_irq(IRQ_RIO_TX(mport), fsl_rio_tx_handler, 0,
			 "msg_tx", (व्योम *)mport);
	अगर (rc < 0)
		जाओ out_irq;

	/*
	 * Configure outbound message unit
	 *      Snooping
	 *      Interrupts (all enabled, except QEIE)
	 *      Chaining mode
	 *      Disable
	 */
	out_be32(&rmu->msg_regs->omr, 0x00100220);

	/* Set number of entries */
	out_be32(&rmu->msg_regs->omr,
		 in_be32(&rmu->msg_regs->omr) |
		 ((get_biपंचांगask_order(entries) - 2) << 12));

	/* Now enable the unit */
	out_be32(&rmu->msg_regs->omr, in_be32(&rmu->msg_regs->omr) | 0x1);

out:
	वापस rc;

out_irq:
	dma_मुक्त_coherent(priv->dev,
		rmu->msg_tx_ring.size * RIO_MSG_DESC_SIZE,
		rmu->msg_tx_ring.virt, rmu->msg_tx_ring.phys);

out_dma:
	क्रम (i = 0; i < rmu->msg_tx_ring.size; i++)
		dma_मुक्त_coherent(priv->dev, RIO_MSG_BUFFER_SIZE,
		rmu->msg_tx_ring.virt_buffer[i],
		rmu->msg_tx_ring.phys_buffer[i]);

	वापस rc;
पूर्ण

/**
 * fsl_बंद_outb_mbox - Shut करोwn MPC85xx outbound mailbox
 * @mport: Master port implementing the outbound message unit
 * @mbox: Mailbox to बंद
 *
 * Disables the outbound message unit, मुक्त all buffers, and
 * मुक्तs the outbound message पूर्णांकerrupt.
 */
व्योम fsl_बंद_outb_mbox(काष्ठा rio_mport *mport, पूर्णांक mbox)
अणु
	काष्ठा rio_priv *priv = mport->priv;
	काष्ठा fsl_rmu *rmu = GET_RMM_HANDLE(mport);

	/* Disable inbound message unit */
	out_be32(&rmu->msg_regs->omr, 0);

	/* Free ring */
	dma_मुक्त_coherent(priv->dev,
	rmu->msg_tx_ring.size * RIO_MSG_DESC_SIZE,
	rmu->msg_tx_ring.virt, rmu->msg_tx_ring.phys);

	/* Free पूर्णांकerrupt */
	मुक्त_irq(IRQ_RIO_TX(mport), (व्योम *)mport);
पूर्ण

/**
 * fsl_खोलो_inb_mbox - Initialize MPC85xx inbound mailbox
 * @mport: Master port implementing the inbound message unit
 * @dev_id: Device specअगरic poपूर्णांकer to pass on event
 * @mbox: Mailbox to खोलो
 * @entries: Number of entries in the inbound mailbox ring
 *
 * Initializes buffer ring, request the inbound message पूर्णांकerrupt,
 * and enables the inbound message unit. Returns %0 on success
 * and %-EINVAL or %-ENOMEM on failure.
 */
पूर्णांक
fsl_खोलो_inb_mbox(काष्ठा rio_mport *mport, व्योम *dev_id, पूर्णांक mbox, पूर्णांक entries)
अणु
	पूर्णांक i, rc = 0;
	काष्ठा rio_priv *priv = mport->priv;
	काष्ठा fsl_rmu *rmu = GET_RMM_HANDLE(mport);

	अगर ((entries < RIO_MIN_RX_RING_SIZE) ||
		(entries > RIO_MAX_RX_RING_SIZE) || (!is_घातer_of_2(entries))) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	/* Initialize client buffer ring */
	rmu->msg_rx_ring.dev_id = dev_id;
	rmu->msg_rx_ring.size = entries;
	rmu->msg_rx_ring.rx_slot = 0;
	क्रम (i = 0; i < rmu->msg_rx_ring.size; i++)
		rmu->msg_rx_ring.virt_buffer[i] = शून्य;

	/* Initialize inbound message ring */
	rmu->msg_rx_ring.virt = dma_alloc_coherent(priv->dev,
				rmu->msg_rx_ring.size * RIO_MAX_MSG_SIZE,
				&rmu->msg_rx_ring.phys, GFP_KERNEL);
	अगर (!rmu->msg_rx_ring.virt) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Poपूर्णांक dequeue/enqueue poपूर्णांकers at first entry in ring */
	out_be32(&rmu->msg_regs->अगरqdpar, (u32) rmu->msg_rx_ring.phys);
	out_be32(&rmu->msg_regs->अगरqepar, (u32) rmu->msg_rx_ring.phys);

	/* Clear पूर्णांकerrupt status */
	out_be32(&rmu->msg_regs->isr, 0x00000091);

	/* Hook up inbound message handler */
	rc = request_irq(IRQ_RIO_RX(mport), fsl_rio_rx_handler, 0,
			 "msg_rx", (व्योम *)mport);
	अगर (rc < 0) अणु
		dma_मुक्त_coherent(priv->dev,
			rmu->msg_rx_ring.size * RIO_MAX_MSG_SIZE,
			rmu->msg_rx_ring.virt, rmu->msg_rx_ring.phys);
		जाओ out;
	पूर्ण

	/*
	 * Configure inbound message unit:
	 *      Snooping
	 *      4KB max message size
	 *      Unmask all पूर्णांकerrupt sources
	 *      Disable
	 */
	out_be32(&rmu->msg_regs->imr, 0x001b0060);

	/* Set number of queue entries */
	setbits32(&rmu->msg_regs->imr, (get_biपंचांगask_order(entries) - 2) << 12);

	/* Now enable the unit */
	setbits32(&rmu->msg_regs->imr, 0x1);

out:
	वापस rc;
पूर्ण

/**
 * fsl_बंद_inb_mbox - Shut करोwn MPC85xx inbound mailbox
 * @mport: Master port implementing the inbound message unit
 * @mbox: Mailbox to बंद
 *
 * Disables the inbound message unit, मुक्त all buffers, and
 * मुक्तs the inbound message पूर्णांकerrupt.
 */
व्योम fsl_बंद_inb_mbox(काष्ठा rio_mport *mport, पूर्णांक mbox)
अणु
	काष्ठा rio_priv *priv = mport->priv;
	काष्ठा fsl_rmu *rmu = GET_RMM_HANDLE(mport);

	/* Disable inbound message unit */
	out_be32(&rmu->msg_regs->imr, 0);

	/* Free ring */
	dma_मुक्त_coherent(priv->dev, rmu->msg_rx_ring.size * RIO_MAX_MSG_SIZE,
	rmu->msg_rx_ring.virt, rmu->msg_rx_ring.phys);

	/* Free पूर्णांकerrupt */
	मुक्त_irq(IRQ_RIO_RX(mport), (व्योम *)mport);
पूर्ण

/**
 * fsl_add_inb_buffer - Add buffer to the MPC85xx inbound message queue
 * @mport: Master port implementing the inbound message unit
 * @mbox: Inbound mailbox number
 * @buf: Buffer to add to inbound queue
 *
 * Adds the @buf buffer to the MPC85xx inbound message queue. Returns
 * %0 on success or %-EINVAL on failure.
 */
पूर्णांक fsl_add_inb_buffer(काष्ठा rio_mport *mport, पूर्णांक mbox, व्योम *buf)
अणु
	पूर्णांक rc = 0;
	काष्ठा fsl_rmu *rmu = GET_RMM_HANDLE(mport);

	pr_debug("RIO: fsl_add_inb_buffer(), msg_rx_ring.rx_slot %d\n",
		 rmu->msg_rx_ring.rx_slot);

	अगर (rmu->msg_rx_ring.virt_buffer[rmu->msg_rx_ring.rx_slot]) अणु
		prपूर्णांकk(KERN_ERR
			"RIO: error adding inbound buffer %d, buffer exists\n",
			rmu->msg_rx_ring.rx_slot);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	rmu->msg_rx_ring.virt_buffer[rmu->msg_rx_ring.rx_slot] = buf;
	अगर (++rmu->msg_rx_ring.rx_slot == rmu->msg_rx_ring.size)
		rmu->msg_rx_ring.rx_slot = 0;

out:
	वापस rc;
पूर्ण

/**
 * fsl_get_inb_message - Fetch inbound message from the MPC85xx message unit
 * @mport: Master port implementing the inbound message unit
 * @mbox: Inbound mailbox number
 *
 * Gets the next available inbound message from the inbound message queue.
 * A poपूर्णांकer to the message is वापसed on success or शून्य on failure.
 */
व्योम *fsl_get_inb_message(काष्ठा rio_mport *mport, पूर्णांक mbox)
अणु
	काष्ठा fsl_rmu *rmu = GET_RMM_HANDLE(mport);
	u32 phys_buf;
	व्योम *virt_buf;
	व्योम *buf = शून्य;
	पूर्णांक buf_idx;

	phys_buf = in_be32(&rmu->msg_regs->अगरqdpar);

	/* If no more messages, then bail out */
	अगर (phys_buf == in_be32(&rmu->msg_regs->अगरqepar))
		जाओ out2;

	virt_buf = rmu->msg_rx_ring.virt + (phys_buf
						- rmu->msg_rx_ring.phys);
	buf_idx = (phys_buf - rmu->msg_rx_ring.phys) / RIO_MAX_MSG_SIZE;
	buf = rmu->msg_rx_ring.virt_buffer[buf_idx];

	अगर (!buf) अणु
		prपूर्णांकk(KERN_ERR
			"RIO: inbound message copy failed, no buffers\n");
		जाओ out1;
	पूर्ण

	/* Copy max message size, caller is expected to allocate that big */
	स_नकल(buf, virt_buf, RIO_MAX_MSG_SIZE);

	/* Clear the available buffer */
	rmu->msg_rx_ring.virt_buffer[buf_idx] = शून्य;

out1:
	setbits32(&rmu->msg_regs->imr, RIO_MSG_IMR_MI);

out2:
	वापस buf;
पूर्ण

/**
 * fsl_rio_करोorbell_init - MPC85xx करोorbell पूर्णांकerface init
 * @mport: Master port implementing the inbound करोorbell unit
 *
 * Initializes करोorbell unit hardware and inbound DMA buffer
 * ring. Called from fsl_rio_setup(). Returns %0 on success
 * or %-ENOMEM on failure.
 */
पूर्णांक fsl_rio_करोorbell_init(काष्ठा fsl_rio_dbell *dbell)
अणु
	पूर्णांक rc = 0;

	/* Initialize inbound करोorbells */
	dbell->dbell_ring.virt = dma_alloc_coherent(dbell->dev, 512 *
		DOORBELL_MESSAGE_SIZE, &dbell->dbell_ring.phys, GFP_KERNEL);
	अगर (!dbell->dbell_ring.virt) अणु
		prपूर्णांकk(KERN_ERR "RIO: unable allocate inbound doorbell ring\n");
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Poपूर्णांक dequeue/enqueue poपूर्णांकers at first entry in ring */
	out_be32(&dbell->dbell_regs->dqdpar, (u32) dbell->dbell_ring.phys);
	out_be32(&dbell->dbell_regs->dqepar, (u32) dbell->dbell_ring.phys);

	/* Clear पूर्णांकerrupt status */
	out_be32(&dbell->dbell_regs->dsr, 0x00000091);

	/* Hook up करोorbell handler */
	rc = request_irq(IRQ_RIO_BELL(dbell), fsl_rio_dbell_handler, 0,
			 "dbell_rx", (व्योम *)dbell);
	अगर (rc < 0) अणु
		dma_मुक्त_coherent(dbell->dev, 512 * DOORBELL_MESSAGE_SIZE,
			 dbell->dbell_ring.virt, dbell->dbell_ring.phys);
		prपूर्णांकk(KERN_ERR
			"MPC85xx RIO: unable to request inbound doorbell irq");
		जाओ out;
	पूर्ण

	/* Configure करोorbells क्रम snooping, 512 entries, and enable */
	out_be32(&dbell->dbell_regs->dmr, 0x00108161);

out:
	वापस rc;
पूर्ण

पूर्णांक fsl_rio_setup_rmu(काष्ठा rio_mport *mport, काष्ठा device_node *node)
अणु
	काष्ठा rio_priv *priv;
	काष्ठा fsl_rmu *rmu;
	u64 msg_start;
	स्थिर u32 *msg_addr;
	पूर्णांक mlen;
	पूर्णांक aw;

	अगर (!mport || !mport->priv)
		वापस -EINVAL;

	priv = mport->priv;

	अगर (!node) अणु
		dev_warn(priv->dev, "Can't get %pOF property 'fsl,rmu'\n",
			priv->dev->of_node);
		वापस -EINVAL;
	पूर्ण

	rmu = kzalloc(माप(काष्ठा fsl_rmu), GFP_KERNEL);
	अगर (!rmu)
		वापस -ENOMEM;

	aw = of_n_addr_cells(node);
	msg_addr = of_get_property(node, "reg", &mlen);
	अगर (!msg_addr) अणु
		pr_err("%pOF: unable to find 'reg' property of message-unit\n",
			node);
		kमुक्त(rmu);
		वापस -ENOMEM;
	पूर्ण
	msg_start = of_पढ़ो_number(msg_addr, aw);

	rmu->msg_regs = (काष्ठा rio_msg_regs *)
			(rmu_regs_win + (u32)msg_start);

	rmu->txirq = irq_of_parse_and_map(node, 0);
	rmu->rxirq = irq_of_parse_and_map(node, 1);
	prपूर्णांकk(KERN_INFO "%pOF: txirq: %d, rxirq %d\n",
		node, rmu->txirq, rmu->rxirq);

	priv->rmm_handle = rmu;

	rio_init_dbell_res(&mport->riores[RIO_DOORBELL_RESOURCE], 0, 0xffff);
	rio_init_mbox_res(&mport->riores[RIO_INB_MBOX_RESOURCE], 0, 0);
	rio_init_mbox_res(&mport->riores[RIO_OUTB_MBOX_RESOURCE], 0, 0);

	वापस 0;
पूर्ण
