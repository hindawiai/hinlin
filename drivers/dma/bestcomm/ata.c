<शैली गुरु>
/*
 * Bestcomm ATA task driver
 *
 *
 * Patterned after bestcomm/fec.c by Dale Farnsworth <dfarnsworth@mvista.com>
 *                                   2003-2004 (c) MontaVista, Software, Inc.
 *
 * Copyright (C) 2006-2007 Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2006      Freescale - John Rigby
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/पन.स>

#समावेश <linux/fsl/bestcomm/bestcomm.h>
#समावेश <linux/fsl/bestcomm/bestcomm_priv.h>
#समावेश <linux/fsl/bestcomm/ata.h>


/* ======================================================================== */
/* Task image/var/inc                                                       */
/* ======================================================================== */

/* ata task image */
बाह्य u32 bcom_ata_task[];

/* ata task vars that need to be set beक्रमe enabling the task */
काष्ठा bcom_ata_var अणु
	u32 enable;		/* (u16*) address of task's control रेजिस्टर */
	u32 bd_base;		/* (काष्ठा bcom_bd*) beginning of ring buffer */
	u32 bd_last;		/* (काष्ठा bcom_bd*) end of ring buffer */
	u32 bd_start;		/* (काष्ठा bcom_bd*) current bd */
	u32 buffer_size;	/* size of receive buffer */
पूर्ण;

/* ata task incs that need to be set beक्रमe enabling the task */
काष्ठा bcom_ata_inc अणु
	u16 pad0;
	s16 incr_bytes;
	u16 pad1;
	s16 incr_dst;
	u16 pad2;
	s16 incr_src;
पूर्ण;


/* ======================================================================== */
/* Task support code                                                        */
/* ======================================================================== */

काष्ठा bcom_task *
bcom_ata_init(पूर्णांक queue_len, पूर्णांक maxbufsize)
अणु
	काष्ठा bcom_task *tsk;
	काष्ठा bcom_ata_var *var;
	काष्ठा bcom_ata_inc *inc;

	/* Prefetch अवरोधs ATA DMA.  Turn it off क्रम ATA DMA */
	bcom_disable_prefetch();

	tsk = bcom_task_alloc(queue_len, माप(काष्ठा bcom_ata_bd), 0);
	अगर (!tsk)
		वापस शून्य;

	tsk->flags = BCOM_FLAGS_NONE;

	bcom_ata_reset_bd(tsk);

	var = (काष्ठा bcom_ata_var *) bcom_task_var(tsk->tasknum);
	inc = (काष्ठा bcom_ata_inc *) bcom_task_inc(tsk->tasknum);

	अगर (bcom_load_image(tsk->tasknum, bcom_ata_task)) अणु
		bcom_task_मुक्त(tsk);
		वापस शून्य;
	पूर्ण

	var->enable	= bcom_eng->regs_base +
				दुरत्व(काष्ठा mpc52xx_sdma, tcr[tsk->tasknum]);
	var->bd_base	= tsk->bd_pa;
	var->bd_last	= tsk->bd_pa + ((tsk->num_bd-1) * tsk->bd_size);
	var->bd_start	= tsk->bd_pa;
	var->buffer_size = maxbufsize;

	/* Configure some stuff */
	bcom_set_task_pragma(tsk->tasknum, BCOM_ATA_PRAGMA);
	bcom_set_task_स्वतः_start(tsk->tasknum, tsk->tasknum);

	out_8(&bcom_eng->regs->ipr[BCOM_INITIATOR_ATA_RX], BCOM_IPR_ATA_RX);
	out_8(&bcom_eng->regs->ipr[BCOM_INITIATOR_ATA_TX], BCOM_IPR_ATA_TX);

	out_be32(&bcom_eng->regs->IntPend, 1<<tsk->tasknum); /* Clear पूर्णांकs */

	वापस tsk;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_ata_init);

व्योम bcom_ata_rx_prepare(काष्ठा bcom_task *tsk)
अणु
	काष्ठा bcom_ata_inc *inc;

	inc = (काष्ठा bcom_ata_inc *) bcom_task_inc(tsk->tasknum);

	inc->incr_bytes	= -(s16)माप(u32);
	inc->incr_src	= 0;
	inc->incr_dst	= माप(u32);

	bcom_set_initiator(tsk->tasknum, BCOM_INITIATOR_ATA_RX);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_ata_rx_prepare);

व्योम bcom_ata_tx_prepare(काष्ठा bcom_task *tsk)
अणु
	काष्ठा bcom_ata_inc *inc;

	inc = (काष्ठा bcom_ata_inc *) bcom_task_inc(tsk->tasknum);

	inc->incr_bytes	= -(s16)माप(u32);
	inc->incr_src	= माप(u32);
	inc->incr_dst	= 0;

	bcom_set_initiator(tsk->tasknum, BCOM_INITIATOR_ATA_TX);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_ata_tx_prepare);

व्योम bcom_ata_reset_bd(काष्ठा bcom_task *tsk)
अणु
	काष्ठा bcom_ata_var *var;

	/* Reset all BD */
	स_रखो(tsk->bd, 0x00, tsk->num_bd * tsk->bd_size);

	tsk->index = 0;
	tsk->outdex = 0;

	var = (काष्ठा bcom_ata_var *) bcom_task_var(tsk->tasknum);
	var->bd_start = var->bd_base;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_ata_reset_bd);

व्योम bcom_ata_release(काष्ठा bcom_task *tsk)
अणु
	/* Nothing special क्रम the ATA tasks */
	bcom_task_मुक्त(tsk);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_ata_release);


MODULE_DESCRIPTION("BestComm ATA task driver");
MODULE_AUTHOR("John Rigby");
MODULE_LICENSE("GPL v2");

