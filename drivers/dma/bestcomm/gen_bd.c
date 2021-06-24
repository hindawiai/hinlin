<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम MPC52xx processor BestComm General Buffer Descriptor
 *
 * Copyright (C) 2007 Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2006 AppSpec Computer Technologies Corp.
 *                    Jeff Gibbons <jeff.gibbons@appspec.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/mpc52xx.h>
#समावेश <यंत्र/mpc52xx_psc.h>

#समावेश <linux/fsl/bestcomm/bestcomm.h>
#समावेश <linux/fsl/bestcomm/bestcomm_priv.h>
#समावेश <linux/fsl/bestcomm/gen_bd.h>


/* ======================================================================== */
/* Task image/var/inc                                                       */
/* ======================================================================== */

/* gen_bd tasks images */
बाह्य u32 bcom_gen_bd_rx_task[];
बाह्य u32 bcom_gen_bd_tx_task[];

/* rx task vars that need to be set beक्रमe enabling the task */
काष्ठा bcom_gen_bd_rx_var अणु
	u32 enable;		/* (u16*) address of task's control रेजिस्टर */
	u32 fअगरo;		/* (u32*) address of gen_bd's fअगरo */
	u32 bd_base;		/* (काष्ठा bcom_bd*) beginning of ring buffer */
	u32 bd_last;		/* (काष्ठा bcom_bd*) end of ring buffer */
	u32 bd_start;		/* (काष्ठा bcom_bd*) current bd */
	u32 buffer_size;	/* size of receive buffer */
पूर्ण;

/* rx task incs that need to be set beक्रमe enabling the task */
काष्ठा bcom_gen_bd_rx_inc अणु
	u16 pad0;
	s16 incr_bytes;
	u16 pad1;
	s16 incr_dst;
पूर्ण;

/* tx task vars that need to be set beक्रमe enabling the task */
काष्ठा bcom_gen_bd_tx_var अणु
	u32 fअगरo;		/* (u32*) address of gen_bd's fअगरo */
	u32 enable;		/* (u16*) address of task's control रेजिस्टर */
	u32 bd_base;		/* (काष्ठा bcom_bd*) beginning of ring buffer */
	u32 bd_last;		/* (काष्ठा bcom_bd*) end of ring buffer */
	u32 bd_start;		/* (काष्ठा bcom_bd*) current bd */
	u32 buffer_size;	/* set by uCode क्रम each packet */
पूर्ण;

/* tx task incs that need to be set beक्रमe enabling the task */
काष्ठा bcom_gen_bd_tx_inc अणु
	u16 pad0;
	s16 incr_bytes;
	u16 pad1;
	s16 incr_src;
	u16 pad2;
	s16 incr_src_ma;
पूर्ण;

/* निजी काष्ठाure */
काष्ठा bcom_gen_bd_priv अणु
	phys_addr_t	fअगरo;
	पूर्णांक		initiator;
	पूर्णांक		ipr;
	पूर्णांक		maxbufsize;
पूर्ण;


/* ======================================================================== */
/* Task support code                                                        */
/* ======================================================================== */

काष्ठा bcom_task *
bcom_gen_bd_rx_init(पूर्णांक queue_len, phys_addr_t fअगरo,
			पूर्णांक initiator, पूर्णांक ipr, पूर्णांक maxbufsize)
अणु
	काष्ठा bcom_task *tsk;
	काष्ठा bcom_gen_bd_priv *priv;

	tsk = bcom_task_alloc(queue_len, माप(काष्ठा bcom_gen_bd),
			माप(काष्ठा bcom_gen_bd_priv));
	अगर (!tsk)
		वापस शून्य;

	tsk->flags = BCOM_FLAGS_NONE;

	priv = tsk->priv;
	priv->fअगरo	= fअगरo;
	priv->initiator	= initiator;
	priv->ipr	= ipr;
	priv->maxbufsize = maxbufsize;

	अगर (bcom_gen_bd_rx_reset(tsk)) अणु
		bcom_task_मुक्त(tsk);
		वापस शून्य;
	पूर्ण

	वापस tsk;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_gen_bd_rx_init);

पूर्णांक
bcom_gen_bd_rx_reset(काष्ठा bcom_task *tsk)
अणु
	काष्ठा bcom_gen_bd_priv *priv = tsk->priv;
	काष्ठा bcom_gen_bd_rx_var *var;
	काष्ठा bcom_gen_bd_rx_inc *inc;

	/* Shutकरोwn the task */
	bcom_disable_task(tsk->tasknum);

	/* Reset the microcode */
	var = (काष्ठा bcom_gen_bd_rx_var *) bcom_task_var(tsk->tasknum);
	inc = (काष्ठा bcom_gen_bd_rx_inc *) bcom_task_inc(tsk->tasknum);

	अगर (bcom_load_image(tsk->tasknum, bcom_gen_bd_rx_task))
		वापस -1;

	var->enable	= bcom_eng->regs_base +
				दुरत्व(काष्ठा mpc52xx_sdma, tcr[tsk->tasknum]);
	var->fअगरo	= (u32) priv->fअगरo;
	var->bd_base	= tsk->bd_pa;
	var->bd_last	= tsk->bd_pa + ((tsk->num_bd-1) * tsk->bd_size);
	var->bd_start	= tsk->bd_pa;
	var->buffer_size = priv->maxbufsize;

	inc->incr_bytes	= -(s16)माप(u32);
	inc->incr_dst	= माप(u32);

	/* Reset the BDs */
	tsk->index = 0;
	tsk->outdex = 0;

	स_रखो(tsk->bd, 0x00, tsk->num_bd * tsk->bd_size);

	/* Configure some stuff */
	bcom_set_task_pragma(tsk->tasknum, BCOM_GEN_RX_BD_PRAGMA);
	bcom_set_task_स्वतः_start(tsk->tasknum, tsk->tasknum);

	out_8(&bcom_eng->regs->ipr[priv->initiator], priv->ipr);
	bcom_set_initiator(tsk->tasknum, priv->initiator);

	out_be32(&bcom_eng->regs->IntPend, 1<<tsk->tasknum);	/* Clear पूर्णांकs */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_gen_bd_rx_reset);

व्योम
bcom_gen_bd_rx_release(काष्ठा bcom_task *tsk)
अणु
	/* Nothing special क्रम the GenBD tasks */
	bcom_task_मुक्त(tsk);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_gen_bd_rx_release);


बाह्य काष्ठा bcom_task *
bcom_gen_bd_tx_init(पूर्णांक queue_len, phys_addr_t fअगरo,
			पूर्णांक initiator, पूर्णांक ipr)
अणु
	काष्ठा bcom_task *tsk;
	काष्ठा bcom_gen_bd_priv *priv;

	tsk = bcom_task_alloc(queue_len, माप(काष्ठा bcom_gen_bd),
			माप(काष्ठा bcom_gen_bd_priv));
	अगर (!tsk)
		वापस शून्य;

	tsk->flags = BCOM_FLAGS_NONE;

	priv = tsk->priv;
	priv->fअगरo	= fअगरo;
	priv->initiator	= initiator;
	priv->ipr	= ipr;

	अगर (bcom_gen_bd_tx_reset(tsk)) अणु
		bcom_task_मुक्त(tsk);
		वापस शून्य;
	पूर्ण

	वापस tsk;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_gen_bd_tx_init);

पूर्णांक
bcom_gen_bd_tx_reset(काष्ठा bcom_task *tsk)
अणु
	काष्ठा bcom_gen_bd_priv *priv = tsk->priv;
	काष्ठा bcom_gen_bd_tx_var *var;
	काष्ठा bcom_gen_bd_tx_inc *inc;

	/* Shutकरोwn the task */
	bcom_disable_task(tsk->tasknum);

	/* Reset the microcode */
	var = (काष्ठा bcom_gen_bd_tx_var *) bcom_task_var(tsk->tasknum);
	inc = (काष्ठा bcom_gen_bd_tx_inc *) bcom_task_inc(tsk->tasknum);

	अगर (bcom_load_image(tsk->tasknum, bcom_gen_bd_tx_task))
		वापस -1;

	var->enable	= bcom_eng->regs_base +
				दुरत्व(काष्ठा mpc52xx_sdma, tcr[tsk->tasknum]);
	var->fअगरo	= (u32) priv->fअगरo;
	var->bd_base	= tsk->bd_pa;
	var->bd_last	= tsk->bd_pa + ((tsk->num_bd-1) * tsk->bd_size);
	var->bd_start	= tsk->bd_pa;

	inc->incr_bytes	= -(s16)माप(u32);
	inc->incr_src	= माप(u32);
	inc->incr_src_ma = माप(u8);

	/* Reset the BDs */
	tsk->index = 0;
	tsk->outdex = 0;

	स_रखो(tsk->bd, 0x00, tsk->num_bd * tsk->bd_size);

	/* Configure some stuff */
	bcom_set_task_pragma(tsk->tasknum, BCOM_GEN_TX_BD_PRAGMA);
	bcom_set_task_स्वतः_start(tsk->tasknum, tsk->tasknum);

	out_8(&bcom_eng->regs->ipr[priv->initiator], priv->ipr);
	bcom_set_initiator(tsk->tasknum, priv->initiator);

	out_be32(&bcom_eng->regs->IntPend, 1<<tsk->tasknum);	/* Clear पूर्णांकs */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_gen_bd_tx_reset);

व्योम
bcom_gen_bd_tx_release(काष्ठा bcom_task *tsk)
अणु
	/* Nothing special क्रम the GenBD tasks */
	bcom_task_मुक्त(tsk);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_gen_bd_tx_release);

/* ---------------------------------------------------------------------
 * PSC support code
 */

/**
 * bcom_psc_parameters - Bestcomm initialization value table क्रम PSC devices
 *
 * This काष्ठाure is only used पूर्णांकernally.  It is a lookup table क्रम PSC
 * specअगरic parameters to bestcomm tasks.
 */
अटल काष्ठा bcom_psc_params अणु
	पूर्णांक rx_initiator;
	पूर्णांक rx_ipr;
	पूर्णांक tx_initiator;
	पूर्णांक tx_ipr;
पूर्ण bcom_psc_params[] = अणु
	[0] = अणु
		.rx_initiator = BCOM_INITIATOR_PSC1_RX,
		.rx_ipr = BCOM_IPR_PSC1_RX,
		.tx_initiator = BCOM_INITIATOR_PSC1_TX,
		.tx_ipr = BCOM_IPR_PSC1_TX,
	पूर्ण,
	[1] = अणु
		.rx_initiator = BCOM_INITIATOR_PSC2_RX,
		.rx_ipr = BCOM_IPR_PSC2_RX,
		.tx_initiator = BCOM_INITIATOR_PSC2_TX,
		.tx_ipr = BCOM_IPR_PSC2_TX,
	पूर्ण,
	[2] = अणु
		.rx_initiator = BCOM_INITIATOR_PSC3_RX,
		.rx_ipr = BCOM_IPR_PSC3_RX,
		.tx_initiator = BCOM_INITIATOR_PSC3_TX,
		.tx_ipr = BCOM_IPR_PSC3_TX,
	पूर्ण,
	[3] = अणु
		.rx_initiator = BCOM_INITIATOR_PSC4_RX,
		.rx_ipr = BCOM_IPR_PSC4_RX,
		.tx_initiator = BCOM_INITIATOR_PSC4_TX,
		.tx_ipr = BCOM_IPR_PSC4_TX,
	पूर्ण,
	[4] = अणु
		.rx_initiator = BCOM_INITIATOR_PSC5_RX,
		.rx_ipr = BCOM_IPR_PSC5_RX,
		.tx_initiator = BCOM_INITIATOR_PSC5_TX,
		.tx_ipr = BCOM_IPR_PSC5_TX,
	पूर्ण,
	[5] = अणु
		.rx_initiator = BCOM_INITIATOR_PSC6_RX,
		.rx_ipr = BCOM_IPR_PSC6_RX,
		.tx_initiator = BCOM_INITIATOR_PSC6_TX,
		.tx_ipr = BCOM_IPR_PSC6_TX,
	पूर्ण,
पूर्ण;

/**
 * bcom_psc_gen_bd_rx_init - Allocate a receive bcom_task क्रम a PSC port
 * @psc_num:	Number of the PSC to allocate a task क्रम
 * @queue_len:	number of buffer descriptors to allocate क्रम the task
 * @fअगरo:	physical address of FIFO रेजिस्टर
 * @maxbufsize:	Maximum receive data size in bytes.
 *
 * Allocate a bestcomm task काष्ठाure क्रम receiving data from a PSC.
 */
काष्ठा bcom_task * bcom_psc_gen_bd_rx_init(अचिन्हित psc_num, पूर्णांक queue_len,
					   phys_addr_t fअगरo, पूर्णांक maxbufsize)
अणु
	अगर (psc_num >= MPC52xx_PSC_MAXNUM)
		वापस शून्य;

	वापस bcom_gen_bd_rx_init(queue_len, fअगरo,
				   bcom_psc_params[psc_num].rx_initiator,
				   bcom_psc_params[psc_num].rx_ipr,
				   maxbufsize);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_psc_gen_bd_rx_init);

/**
 * bcom_psc_gen_bd_tx_init - Allocate a transmit bcom_task क्रम a PSC port
 * @psc_num:	Number of the PSC to allocate a task क्रम
 * @queue_len:	number of buffer descriptors to allocate क्रम the task
 * @fअगरo:	physical address of FIFO रेजिस्टर
 *
 * Allocate a bestcomm task काष्ठाure क्रम transmitting data to a PSC.
 */
काष्ठा bcom_task *
bcom_psc_gen_bd_tx_init(अचिन्हित psc_num, पूर्णांक queue_len, phys_addr_t fअगरo)
अणु
	काष्ठा psc;
	वापस bcom_gen_bd_tx_init(queue_len, fअगरo,
				   bcom_psc_params[psc_num].tx_initiator,
				   bcom_psc_params[psc_num].tx_ipr);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_psc_gen_bd_tx_init);


MODULE_DESCRIPTION("BestComm General Buffer Descriptor tasks driver");
MODULE_AUTHOR("Jeff Gibbons <jeff.gibbons@appspec.com>");
MODULE_LICENSE("GPL v2");

