<शैली गुरु>
/*
 * Bestcomm FEC tasks driver
 *
 *
 * Copyright (C) 2006-2007 Sylvain Munaut <tnt@246tNt.com>
 * Copyright (C) 2003-2004 MontaVista, Software, Inc.
 *                         ( by Dale Farnsworth <dfarnsworth@mvista.com> )
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
#समावेश <linux/fsl/bestcomm/fec.h>


/* ======================================================================== */
/* Task image/var/inc                                                       */
/* ======================================================================== */

/* fec tasks images */
बाह्य u32 bcom_fec_rx_task[];
बाह्य u32 bcom_fec_tx_task[];

/* rx task vars that need to be set beक्रमe enabling the task */
काष्ठा bcom_fec_rx_var अणु
	u32 enable;		/* (u16*) address of task's control रेजिस्टर */
	u32 fअगरo;		/* (u32*) address of fec's fअगरo */
	u32 bd_base;		/* (काष्ठा bcom_bd*) beginning of ring buffer */
	u32 bd_last;		/* (काष्ठा bcom_bd*) end of ring buffer */
	u32 bd_start;		/* (काष्ठा bcom_bd*) current bd */
	u32 buffer_size;	/* size of receive buffer */
पूर्ण;

/* rx task incs that need to be set beक्रमe enabling the task */
काष्ठा bcom_fec_rx_inc अणु
	u16 pad0;
	s16 incr_bytes;
	u16 pad1;
	s16 incr_dst;
	u16 pad2;
	s16 incr_dst_ma;
पूर्ण;

/* tx task vars that need to be set beक्रमe enabling the task */
काष्ठा bcom_fec_tx_var अणु
	u32 DRD;		/* (u32*) address of self-modअगरied DRD */
	u32 fअगरo;		/* (u32*) address of fec's fअगरo */
	u32 enable;		/* (u16*) address of task's control रेजिस्टर */
	u32 bd_base;		/* (काष्ठा bcom_bd*) beginning of ring buffer */
	u32 bd_last;		/* (काष्ठा bcom_bd*) end of ring buffer */
	u32 bd_start;		/* (काष्ठा bcom_bd*) current bd */
	u32 buffer_size;	/* set by uCode क्रम each packet */
पूर्ण;

/* tx task incs that need to be set beक्रमe enabling the task */
काष्ठा bcom_fec_tx_inc अणु
	u16 pad0;
	s16 incr_bytes;
	u16 pad1;
	s16 incr_src;
	u16 pad2;
	s16 incr_src_ma;
पूर्ण;

/* निजी काष्ठाure in the task */
काष्ठा bcom_fec_priv अणु
	phys_addr_t	fअगरo;
	पूर्णांक		maxbufsize;
पूर्ण;


/* ======================================================================== */
/* Task support code                                                        */
/* ======================================================================== */

काष्ठा bcom_task *
bcom_fec_rx_init(पूर्णांक queue_len, phys_addr_t fअगरo, पूर्णांक maxbufsize)
अणु
	काष्ठा bcom_task *tsk;
	काष्ठा bcom_fec_priv *priv;

	tsk = bcom_task_alloc(queue_len, माप(काष्ठा bcom_fec_bd),
				माप(काष्ठा bcom_fec_priv));
	अगर (!tsk)
		वापस शून्य;

	tsk->flags = BCOM_FLAGS_NONE;

	priv = tsk->priv;
	priv->fअगरo = fअगरo;
	priv->maxbufsize = maxbufsize;

	अगर (bcom_fec_rx_reset(tsk)) अणु
		bcom_task_मुक्त(tsk);
		वापस शून्य;
	पूर्ण

	वापस tsk;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_fec_rx_init);

पूर्णांक
bcom_fec_rx_reset(काष्ठा bcom_task *tsk)
अणु
	काष्ठा bcom_fec_priv *priv = tsk->priv;
	काष्ठा bcom_fec_rx_var *var;
	काष्ठा bcom_fec_rx_inc *inc;

	/* Shutकरोwn the task */
	bcom_disable_task(tsk->tasknum);

	/* Reset the microcode */
	var = (काष्ठा bcom_fec_rx_var *) bcom_task_var(tsk->tasknum);
	inc = (काष्ठा bcom_fec_rx_inc *) bcom_task_inc(tsk->tasknum);

	अगर (bcom_load_image(tsk->tasknum, bcom_fec_rx_task))
		वापस -1;

	var->enable	= bcom_eng->regs_base +
				दुरत्व(काष्ठा mpc52xx_sdma, tcr[tsk->tasknum]);
	var->fअगरo	= (u32) priv->fअगरo;
	var->bd_base	= tsk->bd_pa;
	var->bd_last	= tsk->bd_pa + ((tsk->num_bd-1) * tsk->bd_size);
	var->bd_start	= tsk->bd_pa;
	var->buffer_size = priv->maxbufsize;

	inc->incr_bytes	= -(s16)माप(u32);	/* These should be in the   */
	inc->incr_dst	= माप(u32);		/* task image, but we stick */
	inc->incr_dst_ma= माप(u8);		/* to the official ones     */

	/* Reset the BDs */
	tsk->index = 0;
	tsk->outdex = 0;

	स_रखो(tsk->bd, 0x00, tsk->num_bd * tsk->bd_size);

	/* Configure some stuff */
	bcom_set_task_pragma(tsk->tasknum, BCOM_FEC_RX_BD_PRAGMA);
	bcom_set_task_स्वतः_start(tsk->tasknum, tsk->tasknum);

	out_8(&bcom_eng->regs->ipr[BCOM_INITIATOR_FEC_RX], BCOM_IPR_FEC_RX);

	out_be32(&bcom_eng->regs->IntPend, 1<<tsk->tasknum);	/* Clear पूर्णांकs */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_fec_rx_reset);

व्योम
bcom_fec_rx_release(काष्ठा bcom_task *tsk)
अणु
	/* Nothing special क्रम the FEC tasks */
	bcom_task_मुक्त(tsk);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_fec_rx_release);



	/* Return 2nd to last DRD */
	/* This is an ugly hack, but at least it's only करोne
	   once at initialization */
अटल u32 *self_modअगरied_drd(पूर्णांक tasknum)
अणु
	u32 *desc;
	पूर्णांक num_descs;
	पूर्णांक drd_count;
	पूर्णांक i;

	num_descs = bcom_task_num_descs(tasknum);
	desc = bcom_task_desc(tasknum) + num_descs - 1;
	drd_count = 0;
	क्रम (i=0; i<num_descs; i++, desc--)
		अगर (bcom_desc_is_drd(*desc) && ++drd_count == 3)
			अवरोध;
	वापस desc;
पूर्ण

काष्ठा bcom_task *
bcom_fec_tx_init(पूर्णांक queue_len, phys_addr_t fअगरo)
अणु
	काष्ठा bcom_task *tsk;
	काष्ठा bcom_fec_priv *priv;

	tsk = bcom_task_alloc(queue_len, माप(काष्ठा bcom_fec_bd),
				माप(काष्ठा bcom_fec_priv));
	अगर (!tsk)
		वापस शून्य;

	tsk->flags = BCOM_FLAGS_ENABLE_TASK;

	priv = tsk->priv;
	priv->fअगरo = fअगरo;

	अगर (bcom_fec_tx_reset(tsk)) अणु
		bcom_task_मुक्त(tsk);
		वापस शून्य;
	पूर्ण

	वापस tsk;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_fec_tx_init);

पूर्णांक
bcom_fec_tx_reset(काष्ठा bcom_task *tsk)
अणु
	काष्ठा bcom_fec_priv *priv = tsk->priv;
	काष्ठा bcom_fec_tx_var *var;
	काष्ठा bcom_fec_tx_inc *inc;

	/* Shutकरोwn the task */
	bcom_disable_task(tsk->tasknum);

	/* Reset the microcode */
	var = (काष्ठा bcom_fec_tx_var *) bcom_task_var(tsk->tasknum);
	inc = (काष्ठा bcom_fec_tx_inc *) bcom_task_inc(tsk->tasknum);

	अगर (bcom_load_image(tsk->tasknum, bcom_fec_tx_task))
		वापस -1;

	var->enable	= bcom_eng->regs_base +
				दुरत्व(काष्ठा mpc52xx_sdma, tcr[tsk->tasknum]);
	var->fअगरo	= (u32) priv->fअगरo;
	var->DRD	= bcom_sram_va2pa(self_modअगरied_drd(tsk->tasknum));
	var->bd_base	= tsk->bd_pa;
	var->bd_last	= tsk->bd_pa + ((tsk->num_bd-1) * tsk->bd_size);
	var->bd_start	= tsk->bd_pa;

	inc->incr_bytes	= -(s16)माप(u32);	/* These should be in the   */
	inc->incr_src	= माप(u32);		/* task image, but we stick */
	inc->incr_src_ma= माप(u8);		/* to the official ones     */

	/* Reset the BDs */
	tsk->index = 0;
	tsk->outdex = 0;

	स_रखो(tsk->bd, 0x00, tsk->num_bd * tsk->bd_size);

	/* Configure some stuff */
	bcom_set_task_pragma(tsk->tasknum, BCOM_FEC_TX_BD_PRAGMA);
	bcom_set_task_स्वतः_start(tsk->tasknum, tsk->tasknum);

	out_8(&bcom_eng->regs->ipr[BCOM_INITIATOR_FEC_TX], BCOM_IPR_FEC_TX);

	out_be32(&bcom_eng->regs->IntPend, 1<<tsk->tasknum);	/* Clear पूर्णांकs */

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bcom_fec_tx_reset);

व्योम
bcom_fec_tx_release(काष्ठा bcom_task *tsk)
अणु
	/* Nothing special क्रम the FEC tasks */
	bcom_task_मुक्त(tsk);
पूर्ण
EXPORT_SYMBOL_GPL(bcom_fec_tx_release);


MODULE_DESCRIPTION("BestComm FEC tasks driver");
MODULE_AUTHOR("Dale Farnsworth <dfarnsworth@mvista.com>");
MODULE_LICENSE("GPL v2");

