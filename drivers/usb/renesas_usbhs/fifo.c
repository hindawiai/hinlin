<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Copyright (C) 2019 Renesas Electronics Corporation
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/scatterlist.h>
#समावेश "common.h"
#समावेश "pipe.h"

#घोषणा usbhsf_get_cfअगरo(p)	(&((p)->fअगरo_info.cfअगरo))

#घोषणा usbhsf_fअगरo_is_busy(f)	((f)->pipe) /* see usbhs_pipe_select_fअगरo */

/*
 *		packet initialize
 */
व्योम usbhs_pkt_init(काष्ठा usbhs_pkt *pkt)
अणु
	INIT_LIST_HEAD(&pkt->node);
पूर्ण

/*
 *		packet control function
 */
अटल पूर्णांक usbhsf_null_handle(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pkt->pipe);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);

	dev_err(dev, "null handler\n");

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा usbhs_pkt_handle usbhsf_null_handler = अणु
	.prepare = usbhsf_null_handle,
	.try_run = usbhsf_null_handle,
पूर्ण;

व्योम usbhs_pkt_push(काष्ठा usbhs_pipe *pipe, काष्ठा usbhs_pkt *pkt,
		    व्योम (*करोne)(काष्ठा usbhs_priv *priv,
				 काष्ठा usbhs_pkt *pkt),
		    व्योम *buf, पूर्णांक len, पूर्णांक zero, पूर्णांक sequence)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	अचिन्हित दीर्घ flags;

	अगर (!करोne) अणु
		dev_err(dev, "no done function\n");
		वापस;
	पूर्ण

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	अगर (!pipe->handler) अणु
		dev_err(dev, "no handler function\n");
		pipe->handler = &usbhsf_null_handler;
	पूर्ण

	list_move_tail(&pkt->node, &pipe->list);

	/*
	 * each pkt must hold own handler.
	 * because handler might be changed by its situation.
	 * dma handler -> pio handler.
	 */
	pkt->pipe	= pipe;
	pkt->buf	= buf;
	pkt->handler	= pipe->handler;
	pkt->length	= len;
	pkt->zero	= zero;
	pkt->actual	= 0;
	pkt->करोne	= करोne;
	pkt->sequence	= sequence;

	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/
पूर्ण

अटल व्योम __usbhsf_pkt_del(काष्ठा usbhs_pkt *pkt)
अणु
	list_del_init(&pkt->node);
पूर्ण

काष्ठा usbhs_pkt *__usbhsf_pkt_get(काष्ठा usbhs_pipe *pipe)
अणु
	वापस list_first_entry_or_null(&pipe->list, काष्ठा usbhs_pkt, node);
पूर्ण

अटल व्योम usbhsf_fअगरo_unselect(काष्ठा usbhs_pipe *pipe,
				 काष्ठा usbhs_fअगरo *fअगरo);
अटल काष्ठा dma_chan *usbhsf_dma_chan_get(काष्ठा usbhs_fअगरo *fअगरo,
					    काष्ठा usbhs_pkt *pkt);
#घोषणा usbhsf_dma_map(p)	__usbhsf_dma_map_ctrl(p, 1)
#घोषणा usbhsf_dma_unmap(p)	__usbhsf_dma_map_ctrl(p, 0)
अटल पूर्णांक __usbhsf_dma_map_ctrl(काष्ठा usbhs_pkt *pkt, पूर्णांक map);
काष्ठा usbhs_pkt *usbhs_pkt_pop(काष्ठा usbhs_pipe *pipe, काष्ठा usbhs_pkt *pkt)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_fअगरo *fअगरo = usbhs_pipe_to_fअगरo(pipe);
	अचिन्हित दीर्घ flags;

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	usbhs_pipe_disable(pipe);

	अगर (!pkt)
		pkt = __usbhsf_pkt_get(pipe);

	अगर (pkt) अणु
		काष्ठा dma_chan *chan = शून्य;

		अगर (fअगरo)
			chan = usbhsf_dma_chan_get(fअगरo, pkt);
		अगर (chan) अणु
			dmaengine_terminate_all(chan);
			usbhsf_dma_unmap(pkt);
		पूर्ण

		usbhs_pipe_clear_without_sequence(pipe, 0, 0);
		usbhs_pipe_running(pipe, 0);

		__usbhsf_pkt_del(pkt);
	पूर्ण

	अगर (fअगरo)
		usbhsf_fअगरo_unselect(pipe, fअगरo);

	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/

	वापस pkt;
पूर्ण

क्रमागत अणु
	USBHSF_PKT_PREPARE,
	USBHSF_PKT_TRY_RUN,
	USBHSF_PKT_DMA_DONE,
पूर्ण;

अटल पूर्णांक usbhsf_pkt_handler(काष्ठा usbhs_pipe *pipe, पूर्णांक type)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_pkt *pkt;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक (*func)(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	पूर्णांक is_करोne = 0;

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);

	pkt = __usbhsf_pkt_get(pipe);
	अगर (!pkt) अणु
		ret = -EINVAL;
		जाओ __usbhs_pkt_handler_end;
	पूर्ण

	चयन (type) अणु
	हाल USBHSF_PKT_PREPARE:
		func = pkt->handler->prepare;
		अवरोध;
	हाल USBHSF_PKT_TRY_RUN:
		func = pkt->handler->try_run;
		अवरोध;
	हाल USBHSF_PKT_DMA_DONE:
		func = pkt->handler->dma_करोne;
		अवरोध;
	शेष:
		dev_err(dev, "unknown pkt handler\n");
		जाओ __usbhs_pkt_handler_end;
	पूर्ण

	अगर (likely(func))
		ret = func(pkt, &is_करोne);

	अगर (is_करोne)
		__usbhsf_pkt_del(pkt);

__usbhs_pkt_handler_end:
	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/

	अगर (is_करोne) अणु
		pkt->करोne(priv, pkt);
		usbhs_pkt_start(pipe);
	पूर्ण

	वापस ret;
पूर्ण

व्योम usbhs_pkt_start(काष्ठा usbhs_pipe *pipe)
अणु
	usbhsf_pkt_handler(pipe, USBHSF_PKT_PREPARE);
पूर्ण

/*
 *		irq enable/disable function
 */
#घोषणा usbhsf_irq_empty_ctrl(p, e) usbhsf_irq_callback_ctrl(p, irq_bempsts, e)
#घोषणा usbhsf_irq_पढ़ोy_ctrl(p, e) usbhsf_irq_callback_ctrl(p, irq_brdysts, e)
#घोषणा usbhsf_irq_callback_ctrl(pipe, status, enable)			\
	(अणु								\
		काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);	\
		काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);	\
		u16 status = (1 << usbhs_pipe_number(pipe));		\
		अगर (!mod)						\
			वापस;						\
		अगर (enable)						\
			mod->status |= status;				\
		अन्यथा							\
			mod->status &= ~status;				\
		usbhs_irq_callback_update(priv, mod);			\
	पूर्ण)

अटल व्योम usbhsf_tx_irq_ctrl(काष्ठा usbhs_pipe *pipe, पूर्णांक enable)
अणु
	/*
	 * And DCP pipe can NOT use "ready interrupt" क्रम "send"
	 * it should use "empty" पूर्णांकerrupt.
	 * see
	 *   "Operation" - "Interrupt Function" - "BRDY Interrupt"
	 *
	 * on the other hand, normal pipe can use "ready interrupt" क्रम "send"
	 * even though it is single/द्विगुन buffer
	 */
	अगर (usbhs_pipe_is_dcp(pipe))
		usbhsf_irq_empty_ctrl(pipe, enable);
	अन्यथा
		usbhsf_irq_पढ़ोy_ctrl(pipe, enable);
पूर्ण

अटल व्योम usbhsf_rx_irq_ctrl(काष्ठा usbhs_pipe *pipe, पूर्णांक enable)
अणु
	usbhsf_irq_पढ़ोy_ctrl(pipe, enable);
पूर्ण

/*
 *		FIFO ctrl
 */
अटल व्योम usbhsf_send_terminator(काष्ठा usbhs_pipe *pipe,
				   काष्ठा usbhs_fअगरo *fअगरo)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	usbhs_bset(priv, fअगरo->ctr, BVAL, BVAL);
पूर्ण

अटल पूर्णांक usbhsf_fअगरo_barrier(काष्ठा usbhs_priv *priv,
			       काष्ठा usbhs_fअगरo *fअगरo)
अणु
	/* The FIFO port is accessible */
	अगर (usbhs_पढ़ो(priv, fअगरo->ctr) & FRDY)
		वापस 0;

	वापस -EBUSY;
पूर्ण

अटल व्योम usbhsf_fअगरo_clear(काष्ठा usbhs_pipe *pipe,
			      काष्ठा usbhs_fअगरo *fअगरo)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	पूर्णांक ret = 0;

	अगर (!usbhs_pipe_is_dcp(pipe)) अणु
		/*
		 * This driver checks the pipe condition first to aव्योम -EBUSY
		 * from usbhsf_fअगरo_barrier() अगर the pipe is RX direction and
		 * empty.
		 */
		अगर (usbhs_pipe_is_dir_in(pipe))
			ret = usbhs_pipe_is_accessible(pipe);
		अगर (!ret)
			ret = usbhsf_fअगरo_barrier(priv, fअगरo);
	पूर्ण

	/*
	 * अगर non-DCP pipe, this driver should set BCLR when
	 * usbhsf_fअगरo_barrier() वापसs 0.
	 */
	अगर (!ret)
		usbhs_ग_लिखो(priv, fअगरo->ctr, BCLR);
पूर्ण

अटल पूर्णांक usbhsf_fअगरo_rcv_len(काष्ठा usbhs_priv *priv,
			       काष्ठा usbhs_fअगरo *fअगरo)
अणु
	वापस usbhs_पढ़ो(priv, fअगरo->ctr) & DTLN_MASK;
पूर्ण

अटल व्योम usbhsf_fअगरo_unselect(काष्ठा usbhs_pipe *pipe,
				 काष्ठा usbhs_fअगरo *fअगरo)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	usbhs_pipe_select_fअगरo(pipe, शून्य);
	usbhs_ग_लिखो(priv, fअगरo->sel, 0);
पूर्ण

अटल पूर्णांक usbhsf_fअगरo_select(काष्ठा usbhs_pipe *pipe,
			      काष्ठा usbhs_fअगरo *fअगरo,
			      पूर्णांक ग_लिखो)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक समयout = 1024;
	u16 mask = ((1 << 5) | 0xF);		/* mask of ISEL | CURPIPE */
	u16 base = usbhs_pipe_number(pipe);	/* CURPIPE */

	अगर (usbhs_pipe_is_busy(pipe) ||
	    usbhsf_fअगरo_is_busy(fअगरo))
		वापस -EBUSY;

	अगर (usbhs_pipe_is_dcp(pipe)) अणु
		base |= (1 == ग_लिखो) << 5;	/* ISEL */

		अगर (usbhs_mod_is_host(priv))
			usbhs_dcp_dir_क्रम_host(pipe, ग_लिखो);
	पूर्ण

	/* "base" will be used below  */
	usbhs_ग_लिखो(priv, fअगरo->sel, base | MBW_32);

	/* check ISEL and CURPIPE value */
	जबतक (समयout--) अणु
		अगर (base == (mask & usbhs_पढ़ो(priv, fअगरo->sel))) अणु
			usbhs_pipe_select_fअगरo(pipe, fअगरo);
			वापस 0;
		पूर्ण
		udelay(10);
	पूर्ण

	dev_err(dev, "fifo select error\n");

	वापस -EIO;
पूर्ण

/*
 *		DCP status stage
 */
अटल पूर्णांक usbhs_dcp_dir_चयन_to_ग_लिखो(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_fअगरo *fअगरo = usbhsf_get_cfअगरo(priv); /* CFIFO */
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक ret;

	usbhs_pipe_disable(pipe);

	ret = usbhsf_fअगरo_select(pipe, fअगरo, 1);
	अगर (ret < 0) अणु
		dev_err(dev, "%s() faile\n", __func__);
		वापस ret;
	पूर्ण

	usbhs_pipe_sequence_data1(pipe); /* DATA1 */

	usbhsf_fअगरo_clear(pipe, fअगरo);
	usbhsf_send_terminator(pipe, fअगरo);

	usbhsf_fअगरo_unselect(pipe, fअगरo);

	usbhsf_tx_irq_ctrl(pipe, 1);
	usbhs_pipe_enable(pipe);

	वापस ret;
पूर्ण

अटल पूर्णांक usbhs_dcp_dir_चयन_to_पढ़ो(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_fअगरo *fअगरo = usbhsf_get_cfअगरo(priv); /* CFIFO */
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक ret;

	usbhs_pipe_disable(pipe);

	ret = usbhsf_fअगरo_select(pipe, fअगरo, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "%s() fail\n", __func__);
		वापस ret;
	पूर्ण

	usbhs_pipe_sequence_data1(pipe); /* DATA1 */
	usbhsf_fअगरo_clear(pipe, fअगरo);

	usbhsf_fअगरo_unselect(pipe, fअगरo);

	usbhsf_rx_irq_ctrl(pipe, 1);
	usbhs_pipe_enable(pipe);

	वापस ret;

पूर्ण

अटल पूर्णांक usbhs_dcp_dir_चयन_करोne(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;

	अगर (pkt->handler == &usbhs_dcp_status_stage_in_handler)
		usbhsf_tx_irq_ctrl(pipe, 0);
	अन्यथा
		usbhsf_rx_irq_ctrl(pipe, 0);

	pkt->actual = pkt->length;
	*is_करोne = 1;

	वापस 0;
पूर्ण

स्थिर काष्ठा usbhs_pkt_handle usbhs_dcp_status_stage_in_handler = अणु
	.prepare = usbhs_dcp_dir_चयन_to_ग_लिखो,
	.try_run = usbhs_dcp_dir_चयन_करोne,
पूर्ण;

स्थिर काष्ठा usbhs_pkt_handle usbhs_dcp_status_stage_out_handler = अणु
	.prepare = usbhs_dcp_dir_चयन_to_पढ़ो,
	.try_run = usbhs_dcp_dir_चयन_करोne,
पूर्ण;

/*
 *		DCP data stage (push)
 */
अटल पूर्णांक usbhsf_dcp_data_stage_try_push(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;

	usbhs_pipe_sequence_data1(pipe); /* DATA1 */

	/*
	 * change handler to PIO push
	 */
	pkt->handler = &usbhs_fअगरo_pio_push_handler;

	वापस pkt->handler->prepare(pkt, is_करोne);
पूर्ण

स्थिर काष्ठा usbhs_pkt_handle usbhs_dcp_data_stage_out_handler = अणु
	.prepare = usbhsf_dcp_data_stage_try_push,
पूर्ण;

/*
 *		DCP data stage (pop)
 */
अटल पूर्णांक usbhsf_dcp_data_stage_prepare_pop(काष्ठा usbhs_pkt *pkt,
					     पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_fअगरo *fअगरo = usbhsf_get_cfअगरo(priv);

	अगर (usbhs_pipe_is_busy(pipe))
		वापस 0;

	/*
	 * prepare pop क्रम DCP should
	 *  - change DCP direction,
	 *  - clear fअगरo
	 *  - DATA1
	 */
	usbhs_pipe_disable(pipe);

	usbhs_pipe_sequence_data1(pipe); /* DATA1 */

	usbhsf_fअगरo_select(pipe, fअगरo, 0);
	usbhsf_fअगरo_clear(pipe, fअगरo);
	usbhsf_fअगरo_unselect(pipe, fअगरo);

	/*
	 * change handler to PIO pop
	 */
	pkt->handler = &usbhs_fअगरo_pio_pop_handler;

	वापस pkt->handler->prepare(pkt, is_करोne);
पूर्ण

स्थिर काष्ठा usbhs_pkt_handle usbhs_dcp_data_stage_in_handler = अणु
	.prepare = usbhsf_dcp_data_stage_prepare_pop,
पूर्ण;

/*
 *		PIO push handler
 */
अटल पूर्णांक usbhsf_pio_try_push(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	काष्ठा usbhs_fअगरo *fअगरo = usbhsf_get_cfअगरo(priv); /* CFIFO */
	व्योम __iomem *addr = priv->base + fअगरo->port;
	u8 *buf;
	पूर्णांक maxp = usbhs_pipe_get_maxpacket(pipe);
	पूर्णांक total_len;
	पूर्णांक i, ret, len;
	पूर्णांक is_लघु;

	usbhs_pipe_data_sequence(pipe, pkt->sequence);
	pkt->sequence = -1; /* -1 sequence will be ignored */

	usbhs_pipe_set_trans_count_अगर_bulk(pipe, pkt->length);

	ret = usbhsf_fअगरo_select(pipe, fअगरo, 1);
	अगर (ret < 0)
		वापस 0;

	ret = usbhs_pipe_is_accessible(pipe);
	अगर (ret < 0) अणु
		/* inaccessible pipe is not an error */
		ret = 0;
		जाओ usbhs_fअगरo_ग_लिखो_busy;
	पूर्ण

	ret = usbhsf_fअगरo_barrier(priv, fअगरo);
	अगर (ret < 0)
		जाओ usbhs_fअगरo_ग_लिखो_busy;

	buf		= pkt->buf    + pkt->actual;
	len		= pkt->length - pkt->actual;
	len		= min(len, maxp);
	total_len	= len;
	is_लघु	= total_len < maxp;

	/*
	 * FIXME
	 *
	 * 32-bit access only
	 */
	अगर (len >= 4 && !((अचिन्हित दीर्घ)buf & 0x03)) अणु
		ioग_लिखो32_rep(addr, buf, len / 4);
		len %= 4;
		buf += total_len - len;
	पूर्ण

	/* the rest operation */
	अगर (usbhs_get_dparam(priv, cfअगरo_byte_addr)) अणु
		क्रम (i = 0; i < len; i++)
			ioग_लिखो8(buf[i], addr + (i & 0x03));
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < len; i++)
			ioग_लिखो8(buf[i], addr + (0x03 - (i & 0x03)));
	पूर्ण

	/*
	 * variable update
	 */
	pkt->actual += total_len;

	अगर (pkt->actual < pkt->length)
		*is_करोne = 0;		/* there are reमुख्यder data */
	अन्यथा अगर (is_लघु)
		*is_करोne = 1;		/* लघु packet */
	अन्यथा
		*is_करोne = !pkt->zero;	/* send zero packet ? */

	/*
	 * pipe/irq handling
	 */
	अगर (is_लघु)
		usbhsf_send_terminator(pipe, fअगरo);

	usbhsf_tx_irq_ctrl(pipe, !*is_करोne);
	usbhs_pipe_running(pipe, !*is_करोne);
	usbhs_pipe_enable(pipe);

	dev_dbg(dev, "  send %d (%d/ %d/ %d/ %d)\n",
		usbhs_pipe_number(pipe),
		pkt->length, pkt->actual, *is_करोne, pkt->zero);

	usbhsf_fअगरo_unselect(pipe, fअगरo);

	वापस 0;

usbhs_fअगरo_ग_लिखो_busy:
	usbhsf_fअगरo_unselect(pipe, fअगरo);

	/*
	 * pipe is busy.
	 * retry in पूर्णांकerrupt
	 */
	usbhsf_tx_irq_ctrl(pipe, 1);
	usbhs_pipe_running(pipe, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक usbhsf_pio_prepare_push(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	अगर (usbhs_pipe_is_running(pkt->pipe))
		वापस 0;

	वापस usbhsf_pio_try_push(pkt, is_करोne);
पूर्ण

स्थिर काष्ठा usbhs_pkt_handle usbhs_fअगरo_pio_push_handler = अणु
	.prepare = usbhsf_pio_prepare_push,
	.try_run = usbhsf_pio_try_push,
पूर्ण;

/*
 *		PIO pop handler
 */
अटल पूर्णांक usbhsf_prepare_pop(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_fअगरo *fअगरo = usbhsf_get_cfअगरo(priv);

	अगर (usbhs_pipe_is_busy(pipe))
		वापस 0;

	अगर (usbhs_pipe_is_running(pipe))
		वापस 0;

	/*
	 * pipe enable to prepare packet receive
	 */
	usbhs_pipe_data_sequence(pipe, pkt->sequence);
	pkt->sequence = -1; /* -1 sequence will be ignored */

	अगर (usbhs_pipe_is_dcp(pipe))
		usbhsf_fअगरo_clear(pipe, fअगरo);

	usbhs_pipe_set_trans_count_अगर_bulk(pipe, pkt->length);
	usbhs_pipe_enable(pipe);
	usbhs_pipe_running(pipe, 1);
	usbhsf_rx_irq_ctrl(pipe, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsf_pio_try_pop(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	काष्ठा usbhs_fअगरo *fअगरo = usbhsf_get_cfअगरo(priv); /* CFIFO */
	व्योम __iomem *addr = priv->base + fअगरo->port;
	u8 *buf;
	u32 data = 0;
	पूर्णांक maxp = usbhs_pipe_get_maxpacket(pipe);
	पूर्णांक rcv_len, len;
	पूर्णांक i, ret;
	पूर्णांक total_len = 0;

	ret = usbhsf_fअगरo_select(pipe, fअगरo, 0);
	अगर (ret < 0)
		वापस 0;

	ret = usbhsf_fअगरo_barrier(priv, fअगरo);
	अगर (ret < 0)
		जाओ usbhs_fअगरo_पढ़ो_busy;

	rcv_len = usbhsf_fअगरo_rcv_len(priv, fअगरo);

	buf		= pkt->buf    + pkt->actual;
	len		= pkt->length - pkt->actual;
	len		= min(len, rcv_len);
	total_len	= len;

	/*
	 * update actual length first here to decide disable pipe.
	 * अगर this pipe keeps BUF status and all data were popped,
	 * then, next पूर्णांकerrupt/token will be issued again
	 */
	pkt->actual += total_len;

	अगर ((pkt->actual == pkt->length) ||	/* receive all data */
	    (total_len < maxp)) अणु		/* लघु packet */
		*is_करोne = 1;
		usbhsf_rx_irq_ctrl(pipe, 0);
		usbhs_pipe_running(pipe, 0);
		/*
		 * If function mode, since this controller is possible to enter
		 * Control Write status stage at this timing, this driver
		 * should not disable the pipe. If such a हाल happens, this
		 * controller is not able to complete the status stage.
		 */
		अगर (!usbhs_mod_is_host(priv) && !usbhs_pipe_is_dcp(pipe))
			usbhs_pipe_disable(pipe);	/* disable pipe first */
	पूर्ण

	/*
	 * Buffer clear अगर Zero-Length packet
	 *
	 * see
	 * "Operation" - "FIFO Buffer Memory" - "FIFO Port Function"
	 */
	अगर (0 == rcv_len) अणु
		pkt->zero = 1;
		usbhsf_fअगरo_clear(pipe, fअगरo);
		जाओ usbhs_fअगरo_पढ़ो_end;
	पूर्ण

	/*
	 * FIXME
	 *
	 * 32-bit access only
	 */
	अगर (len >= 4 && !((अचिन्हित दीर्घ)buf & 0x03)) अणु
		ioपढ़ो32_rep(addr, buf, len / 4);
		len %= 4;
		buf += total_len - len;
	पूर्ण

	/* the rest operation */
	क्रम (i = 0; i < len; i++) अणु
		अगर (!(i & 0x03))
			data = ioपढ़ो32(addr);

		buf[i] = (data >> ((i & 0x03) * 8)) & 0xff;
	पूर्ण

usbhs_fअगरo_पढ़ो_end:
	dev_dbg(dev, "  recv %d (%d/ %d/ %d/ %d)\n",
		usbhs_pipe_number(pipe),
		pkt->length, pkt->actual, *is_करोne, pkt->zero);

usbhs_fअगरo_पढ़ो_busy:
	usbhsf_fअगरo_unselect(pipe, fअगरo);

	वापस ret;
पूर्ण

स्थिर काष्ठा usbhs_pkt_handle usbhs_fअगरo_pio_pop_handler = अणु
	.prepare = usbhsf_prepare_pop,
	.try_run = usbhsf_pio_try_pop,
पूर्ण;

/*
 *		DCP ctrol statge handler
 */
अटल पूर्णांक usbhsf_ctrl_stage_end(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	usbhs_dcp_control_transfer_करोne(pkt->pipe);

	*is_करोne = 1;

	वापस 0;
पूर्ण

स्थिर काष्ठा usbhs_pkt_handle usbhs_ctrl_stage_end_handler = अणु
	.prepare = usbhsf_ctrl_stage_end,
	.try_run = usbhsf_ctrl_stage_end,
पूर्ण;

/*
 *		DMA fअगरo functions
 */
अटल काष्ठा dma_chan *usbhsf_dma_chan_get(काष्ठा usbhs_fअगरo *fअगरo,
					    काष्ठा usbhs_pkt *pkt)
अणु
	अगर (&usbhs_fअगरo_dma_push_handler == pkt->handler)
		वापस fअगरo->tx_chan;

	अगर (&usbhs_fअगरo_dma_pop_handler == pkt->handler)
		वापस fअगरo->rx_chan;

	वापस शून्य;
पूर्ण

अटल काष्ठा usbhs_fअगरo *usbhsf_get_dma_fअगरo(काष्ठा usbhs_priv *priv,
					      काष्ठा usbhs_pkt *pkt)
अणु
	काष्ठा usbhs_fअगरo *fअगरo;
	पूर्णांक i;

	usbhs_क्रम_each_dfअगरo(priv, fअगरo, i) अणु
		अगर (usbhsf_dma_chan_get(fअगरo, pkt) &&
		    !usbhsf_fअगरo_is_busy(fअगरo))
			वापस fअगरo;
	पूर्ण

	वापस शून्य;
पूर्ण

#घोषणा usbhsf_dma_start(p, f)	__usbhsf_dma_ctrl(p, f, DREQE)
#घोषणा usbhsf_dma_stop(p, f)	__usbhsf_dma_ctrl(p, f, 0)
अटल व्योम __usbhsf_dma_ctrl(काष्ठा usbhs_pipe *pipe,
			      काष्ठा usbhs_fअगरo *fअगरo,
			      u16 dreqe)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);

	usbhs_bset(priv, fअगरo->sel, DREQE, dreqe);
पूर्ण

अटल पूर्णांक __usbhsf_dma_map_ctrl(काष्ठा usbhs_pkt *pkt, पूर्णांक map)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_pipe_info *info = usbhs_priv_to_pipeinfo(priv);
	काष्ठा usbhs_fअगरo *fअगरo = usbhs_pipe_to_fअगरo(pipe);
	काष्ठा dma_chan *chan = usbhsf_dma_chan_get(fअगरo, pkt);

	वापस info->dma_map_ctrl(chan->device->dev, pkt, map);
पूर्ण

अटल व्योम usbhsf_dma_complete(व्योम *arg,
				स्थिर काष्ठा dmaengine_result *result);
अटल व्योम usbhsf_dma_xfer_preparing(काष्ठा usbhs_pkt *pkt)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_fअगरo *fअगरo;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_chan *chan;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	क्रमागत dma_transfer_direction dir;
	dma_cookie_t cookie;

	fअगरo = usbhs_pipe_to_fअगरo(pipe);
	अगर (!fअगरo)
		वापस;

	chan = usbhsf_dma_chan_get(fअगरo, pkt);
	dir = usbhs_pipe_is_dir_in(pipe) ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV;

	desc = dmaengine_prep_slave_single(chan, pkt->dma + pkt->actual,
					pkt->trans, dir,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!desc)
		वापस;

	desc->callback_result	= usbhsf_dma_complete;
	desc->callback_param	= pkt;

	cookie = dmaengine_submit(desc);
	अगर (cookie < 0) अणु
		dev_err(dev, "Failed to submit dma descriptor\n");
		वापस;
	पूर्ण

	dev_dbg(dev, "  %s %d (%d/ %d)\n",
		fअगरo->name, usbhs_pipe_number(pipe), pkt->length, pkt->zero);

	usbhs_pipe_running(pipe, 1);
	usbhs_pipe_set_trans_count_अगर_bulk(pipe, pkt->trans);
	dma_async_issue_pending(chan);
	usbhsf_dma_start(pipe, fअगरo);
	usbhs_pipe_enable(pipe);
पूर्ण

अटल व्योम xfer_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usbhs_pkt *pkt = container_of(work, काष्ठा usbhs_pkt, work);
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	अचिन्हित दीर्घ flags;

	usbhs_lock(priv, flags);
	usbhsf_dma_xfer_preparing(pkt);
	usbhs_unlock(priv, flags);
पूर्ण

/*
 *		DMA push handler
 */
अटल पूर्णांक usbhsf_dma_prepare_push(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_fअगरo *fअगरo;
	पूर्णांक len = pkt->length - pkt->actual;
	पूर्णांक ret;
	uपूर्णांकptr_t align_mask;

	अगर (usbhs_pipe_is_busy(pipe))
		वापस 0;

	/* use PIO अगर packet is less than pio_dma_border or pipe is DCP */
	अगर ((len < usbhs_get_dparam(priv, pio_dma_border)) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_ISOC))
		जाओ usbhsf_pio_prepare_push;

	/* check data length अगर this driver करोn't use USB-DMAC */
	अगर (!usbhs_get_dparam(priv, has_usb_dmac) && len & 0x7)
		जाओ usbhsf_pio_prepare_push;

	/* check buffer alignment */
	align_mask = usbhs_get_dparam(priv, has_usb_dmac) ?
					USBHS_USB_DMAC_XFER_SIZE - 1 : 0x7;
	अगर ((uपूर्णांकptr_t)(pkt->buf + pkt->actual) & align_mask)
		जाओ usbhsf_pio_prepare_push;

	/* वापस at this समय अगर the pipe is running */
	अगर (usbhs_pipe_is_running(pipe))
		वापस 0;

	/* get enable DMA fअगरo */
	fअगरo = usbhsf_get_dma_fअगरo(priv, pkt);
	अगर (!fअगरo)
		जाओ usbhsf_pio_prepare_push;

	ret = usbhsf_fअगरo_select(pipe, fअगरo, 0);
	अगर (ret < 0)
		जाओ usbhsf_pio_prepare_push;

	अगर (usbhsf_dma_map(pkt) < 0)
		जाओ usbhsf_pio_prepare_push_unselect;

	pkt->trans = len;

	usbhsf_tx_irq_ctrl(pipe, 0);
	/* FIXME: Workaound क्रम usb dmac that driver can be used in atomic */
	अगर (usbhs_get_dparam(priv, has_usb_dmac)) अणु
		usbhsf_dma_xfer_preparing(pkt);
	पूर्ण अन्यथा अणु
		INIT_WORK(&pkt->work, xfer_work);
		schedule_work(&pkt->work);
	पूर्ण

	वापस 0;

usbhsf_pio_prepare_push_unselect:
	usbhsf_fअगरo_unselect(pipe, fअगरo);
usbhsf_pio_prepare_push:
	/*
	 * change handler to PIO
	 */
	pkt->handler = &usbhs_fअगरo_pio_push_handler;

	वापस pkt->handler->prepare(pkt, is_करोne);
पूर्ण

अटल पूर्णांक usbhsf_dma_push_करोne(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	पूर्णांक is_लघु = pkt->trans % usbhs_pipe_get_maxpacket(pipe);

	pkt->actual += pkt->trans;

	अगर (pkt->actual < pkt->length)
		*is_करोne = 0;		/* there are reमुख्यder data */
	अन्यथा अगर (is_लघु)
		*is_करोne = 1;		/* लघु packet */
	अन्यथा
		*is_करोne = !pkt->zero;	/* send zero packet? */

	usbhs_pipe_running(pipe, !*is_करोne);

	usbhsf_dma_stop(pipe, pipe->fअगरo);
	usbhsf_dma_unmap(pkt);
	usbhsf_fअगरo_unselect(pipe, pipe->fअगरo);

	अगर (!*is_करोne) अणु
		/* change handler to PIO */
		pkt->handler = &usbhs_fअगरo_pio_push_handler;
		वापस pkt->handler->try_run(pkt, is_करोne);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा usbhs_pkt_handle usbhs_fअगरo_dma_push_handler = अणु
	.prepare	= usbhsf_dma_prepare_push,
	.dma_करोne	= usbhsf_dma_push_करोne,
पूर्ण;

/*
 *		DMA pop handler
 */

अटल पूर्णांक usbhsf_dma_prepare_pop_with_rx_irq(काष्ठा usbhs_pkt *pkt,
					      पूर्णांक *is_करोne)
अणु
	वापस usbhsf_prepare_pop(pkt, is_करोne);
पूर्ण

अटल पूर्णांक usbhsf_dma_prepare_pop_with_usb_dmac(काष्ठा usbhs_pkt *pkt,
						पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_fअगरo *fअगरo;
	पूर्णांक ret;

	अगर (usbhs_pipe_is_busy(pipe))
		वापस 0;

	/* use PIO अगर packet is less than pio_dma_border or pipe is DCP */
	अगर ((pkt->length < usbhs_get_dparam(priv, pio_dma_border)) ||
	    usbhs_pipe_type_is(pipe, USB_ENDPOINT_XFER_ISOC))
		जाओ usbhsf_pio_prepare_pop;

	fअगरo = usbhsf_get_dma_fअगरo(priv, pkt);
	अगर (!fअगरo)
		जाओ usbhsf_pio_prepare_pop;

	अगर ((uपूर्णांकptr_t)pkt->buf & (USBHS_USB_DMAC_XFER_SIZE - 1))
		जाओ usbhsf_pio_prepare_pop;

	/* वापस at this समय अगर the pipe is running */
	अगर (usbhs_pipe_is_running(pipe))
		वापस 0;

	usbhs_pipe_config_change_bfre(pipe, 1);

	ret = usbhsf_fअगरo_select(pipe, fअगरo, 0);
	अगर (ret < 0)
		जाओ usbhsf_pio_prepare_pop;

	अगर (usbhsf_dma_map(pkt) < 0)
		जाओ usbhsf_pio_prepare_pop_unselect;

	/* DMA */

	/*
	 * usbhs_fअगरo_dma_pop_handler :: prepare
	 * enabled irq to come here.
	 * but it is no दीर्घer needed क्रम DMA. disable it.
	 */
	usbhsf_rx_irq_ctrl(pipe, 0);

	pkt->trans = pkt->length;

	usbhsf_dma_xfer_preparing(pkt);

	वापस 0;

usbhsf_pio_prepare_pop_unselect:
	usbhsf_fअगरo_unselect(pipe, fअगरo);
usbhsf_pio_prepare_pop:

	/*
	 * change handler to PIO
	 */
	pkt->handler = &usbhs_fअगरo_pio_pop_handler;
	usbhs_pipe_config_change_bfre(pipe, 0);

	वापस pkt->handler->prepare(pkt, is_करोne);
पूर्ण

अटल पूर्णांक usbhsf_dma_prepare_pop(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pkt->pipe);

	अगर (usbhs_get_dparam(priv, has_usb_dmac))
		वापस usbhsf_dma_prepare_pop_with_usb_dmac(pkt, is_करोne);
	अन्यथा
		वापस usbhsf_dma_prepare_pop_with_rx_irq(pkt, is_करोne);
पूर्ण

अटल पूर्णांक usbhsf_dma_try_pop_with_rx_irq(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_fअगरo *fअगरo;
	पूर्णांक len, ret;

	अगर (usbhs_pipe_is_busy(pipe))
		वापस 0;

	अगर (usbhs_pipe_is_dcp(pipe))
		जाओ usbhsf_pio_prepare_pop;

	/* get enable DMA fअगरo */
	fअगरo = usbhsf_get_dma_fअगरo(priv, pkt);
	अगर (!fअगरo)
		जाओ usbhsf_pio_prepare_pop;

	अगर ((uपूर्णांकptr_t)(pkt->buf + pkt->actual) & 0x7) /* 8byte alignment */
		जाओ usbhsf_pio_prepare_pop;

	ret = usbhsf_fअगरo_select(pipe, fअगरo, 0);
	अगर (ret < 0)
		जाओ usbhsf_pio_prepare_pop;

	/* use PIO अगर packet is less than pio_dma_border */
	len = usbhsf_fअगरo_rcv_len(priv, fअगरo);
	len = min(pkt->length - pkt->actual, len);
	अगर (len & 0x7) /* 8byte alignment */
		जाओ usbhsf_pio_prepare_pop_unselect;

	अगर (len < usbhs_get_dparam(priv, pio_dma_border))
		जाओ usbhsf_pio_prepare_pop_unselect;

	ret = usbhsf_fअगरo_barrier(priv, fअगरo);
	अगर (ret < 0)
		जाओ usbhsf_pio_prepare_pop_unselect;

	अगर (usbhsf_dma_map(pkt) < 0)
		जाओ usbhsf_pio_prepare_pop_unselect;

	/* DMA */

	/*
	 * usbhs_fअगरo_dma_pop_handler :: prepare
	 * enabled irq to come here.
	 * but it is no दीर्घer needed क्रम DMA. disable it.
	 */
	usbhsf_rx_irq_ctrl(pipe, 0);

	pkt->trans = len;

	INIT_WORK(&pkt->work, xfer_work);
	schedule_work(&pkt->work);

	वापस 0;

usbhsf_pio_prepare_pop_unselect:
	usbhsf_fअगरo_unselect(pipe, fअगरo);
usbhsf_pio_prepare_pop:

	/*
	 * change handler to PIO
	 */
	pkt->handler = &usbhs_fअगरo_pio_pop_handler;

	वापस pkt->handler->try_run(pkt, is_करोne);
पूर्ण

अटल पूर्णांक usbhsf_dma_try_pop(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pkt->pipe);

	BUG_ON(usbhs_get_dparam(priv, has_usb_dmac));

	वापस usbhsf_dma_try_pop_with_rx_irq(pkt, is_करोne);
पूर्ण

अटल पूर्णांक usbhsf_dma_pop_करोne_with_rx_irq(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	पूर्णांक maxp = usbhs_pipe_get_maxpacket(pipe);

	usbhsf_dma_stop(pipe, pipe->fअगरo);
	usbhsf_dma_unmap(pkt);
	usbhsf_fअगरo_unselect(pipe, pipe->fअगरo);

	pkt->actual += pkt->trans;

	अगर ((pkt->actual == pkt->length) ||	/* receive all data */
	    (pkt->trans < maxp)) अणु		/* लघु packet */
		*is_करोne = 1;
		usbhs_pipe_running(pipe, 0);
	पूर्ण अन्यथा अणु
		/* re-enable */
		usbhs_pipe_running(pipe, 0);
		usbhsf_prepare_pop(pkt, is_करोne);
	पूर्ण

	वापस 0;
पूर्ण

अटल माप_प्रकार usbhs_dma_calc_received_size(काष्ठा usbhs_pkt *pkt,
					   काष्ठा dma_chan *chan, पूर्णांक dtln)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	माप_प्रकार received_size;
	पूर्णांक maxp = usbhs_pipe_get_maxpacket(pipe);

	received_size = pkt->length - pkt->dma_result->residue;

	अगर (dtln) अणु
		received_size -= USBHS_USB_DMAC_XFER_SIZE;
		received_size &= ~(maxp - 1);
		received_size += dtln;
	पूर्ण

	वापस received_size;
पूर्ण

अटल पूर्णांक usbhsf_dma_pop_करोne_with_usb_dmac(काष्ठा usbhs_pkt *pkt,
					     पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_fअगरo *fअगरo = usbhs_pipe_to_fअगरo(pipe);
	काष्ठा dma_chan *chan = usbhsf_dma_chan_get(fअगरo, pkt);
	पूर्णांक rcv_len;

	/*
	 * Since the driver disables rx_irq in DMA mode, the पूर्णांकerrupt handler
	 * cannot the BRDYSTS. So, the function clears it here because the
	 * driver may use PIO mode next समय.
	 */
	usbhs_xxxsts_clear(priv, BRDYSTS, usbhs_pipe_number(pipe));

	rcv_len = usbhsf_fअगरo_rcv_len(priv, fअगरo);
	usbhsf_fअगरo_clear(pipe, fअगरo);
	pkt->actual = usbhs_dma_calc_received_size(pkt, chan, rcv_len);

	usbhs_pipe_running(pipe, 0);
	usbhsf_dma_stop(pipe, fअगरo);
	usbhsf_dma_unmap(pkt);
	usbhsf_fअगरo_unselect(pipe, pipe->fअगरo);

	/* The driver can assume the rx transaction is always "done" */
	*is_करोne = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsf_dma_pop_करोne(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pkt->pipe);

	अगर (usbhs_get_dparam(priv, has_usb_dmac))
		वापस usbhsf_dma_pop_करोne_with_usb_dmac(pkt, is_करोne);
	अन्यथा
		वापस usbhsf_dma_pop_करोne_with_rx_irq(pkt, is_करोne);
पूर्ण

स्थिर काष्ठा usbhs_pkt_handle usbhs_fअगरo_dma_pop_handler = अणु
	.prepare	= usbhsf_dma_prepare_pop,
	.try_run	= usbhsf_dma_try_pop,
	.dma_करोne	= usbhsf_dma_pop_करोne
पूर्ण;

/*
 *		DMA setting
 */
अटल bool usbhsf_dma_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा sh_dmae_slave *slave = param;

	/*
	 * FIXME
	 *
	 * usbhs करोesn't recognize id = 0 as valid DMA
	 */
	अगर (0 == slave->shdma_slave.slave_id)
		वापस false;

	chan->निजी = slave;

	वापस true;
पूर्ण

अटल व्योम usbhsf_dma_quit(काष्ठा usbhs_priv *priv, काष्ठा usbhs_fअगरo *fअगरo)
अणु
	अगर (fअगरo->tx_chan)
		dma_release_channel(fअगरo->tx_chan);
	अगर (fअगरo->rx_chan)
		dma_release_channel(fअगरo->rx_chan);

	fअगरo->tx_chan = शून्य;
	fअगरo->rx_chan = शून्य;
पूर्ण

अटल व्योम usbhsf_dma_init_pdev(काष्ठा usbhs_fअगरo *fअगरo)
अणु
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	fअगरo->tx_chan = dma_request_channel(mask, usbhsf_dma_filter,
					    &fअगरo->tx_slave);

	dma_cap_zero(mask);
	dma_cap_set(DMA_SLAVE, mask);
	fअगरo->rx_chan = dma_request_channel(mask, usbhsf_dma_filter,
					    &fअगरo->rx_slave);
पूर्ण

अटल व्योम usbhsf_dma_init_dt(काष्ठा device *dev, काष्ठा usbhs_fअगरo *fअगरo,
			       पूर्णांक channel)
अणु
	अक्षर name[16];

	/*
	 * To aव्योम complex handing क्रम DnFIFOs, the driver uses each
	 * DnFIFO as TX or RX direction (not bi-direction).
	 * So, the driver uses odd channels क्रम TX, even channels क्रम RX.
	 */
	snम_लिखो(name, माप(name), "ch%d", channel);
	अगर (channel & 1) अणु
		fअगरo->tx_chan = dma_request_chan(dev, name);
		अगर (IS_ERR(fअगरo->tx_chan))
			fअगरo->tx_chan = शून्य;
	पूर्ण अन्यथा अणु
		fअगरo->rx_chan = dma_request_chan(dev, name);
		अगर (IS_ERR(fअगरo->rx_chan))
			fअगरo->rx_chan = शून्य;
	पूर्ण
पूर्ण

अटल व्योम usbhsf_dma_init(काष्ठा usbhs_priv *priv, काष्ठा usbhs_fअगरo *fअगरo,
			    पूर्णांक channel)
अणु
	काष्ठा device *dev = usbhs_priv_to_dev(priv);

	अगर (dev_of_node(dev))
		usbhsf_dma_init_dt(dev, fअगरo, channel);
	अन्यथा
		usbhsf_dma_init_pdev(fअगरo);

	अगर (fअगरo->tx_chan || fअगरo->rx_chan)
		dev_dbg(dev, "enable DMAEngine (%s%s%s)\n",
			 fअगरo->name,
			 fअगरo->tx_chan ? "[TX]" : "    ",
			 fअगरo->rx_chan ? "[RX]" : "    ");
पूर्ण

/*
 *		irq functions
 */
अटल पूर्णांक usbhsf_irq_empty(काष्ठा usbhs_priv *priv,
			    काष्ठा usbhs_irq_state *irq_state)
अणु
	काष्ठा usbhs_pipe *pipe;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक i, ret;

	अगर (!irq_state->bempsts) अणु
		dev_err(dev, "debug %s !!\n", __func__);
		वापस -EIO;
	पूर्ण

	dev_dbg(dev, "irq empty [0x%04x]\n", irq_state->bempsts);

	/*
	 * search पूर्णांकerrupted "pipe"
	 * not "uep".
	 */
	usbhs_क्रम_each_pipe_with_dcp(pipe, priv, i) अणु
		अगर (!(irq_state->bempsts & (1 << i)))
			जारी;

		ret = usbhsf_pkt_handler(pipe, USBHSF_PKT_TRY_RUN);
		अगर (ret < 0)
			dev_err(dev, "irq_empty run_error %d : %d\n", i, ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usbhsf_irq_पढ़ोy(काष्ठा usbhs_priv *priv,
			    काष्ठा usbhs_irq_state *irq_state)
अणु
	काष्ठा usbhs_pipe *pipe;
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक i, ret;

	अगर (!irq_state->brdysts) अणु
		dev_err(dev, "debug %s !!\n", __func__);
		वापस -EIO;
	पूर्ण

	dev_dbg(dev, "irq ready [0x%04x]\n", irq_state->brdysts);

	/*
	 * search पूर्णांकerrupted "pipe"
	 * not "uep".
	 */
	usbhs_क्रम_each_pipe_with_dcp(pipe, priv, i) अणु
		अगर (!(irq_state->brdysts & (1 << i)))
			जारी;

		ret = usbhsf_pkt_handler(pipe, USBHSF_PKT_TRY_RUN);
		अगर (ret < 0)
			dev_err(dev, "irq_ready run_error %d : %d\n", i, ret);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम usbhsf_dma_complete(व्योम *arg,
				स्थिर काष्ठा dmaengine_result *result)
अणु
	काष्ठा usbhs_pkt *pkt = arg;
	काष्ठा usbhs_pipe *pipe = pkt->pipe;
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक ret;

	pkt->dma_result = result;
	ret = usbhsf_pkt_handler(pipe, USBHSF_PKT_DMA_DONE);
	अगर (ret < 0)
		dev_err(dev, "dma_complete run_error %d : %d\n",
			usbhs_pipe_number(pipe), ret);
पूर्ण

व्योम usbhs_fअगरo_clear_dcp(काष्ठा usbhs_pipe *pipe)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pipe_to_priv(pipe);
	काष्ठा usbhs_fअगरo *fअगरo = usbhsf_get_cfअगरo(priv); /* CFIFO */

	/* clear DCP FIFO of transmission */
	अगर (usbhsf_fअगरo_select(pipe, fअगरo, 1) < 0)
		वापस;
	usbhsf_fअगरo_clear(pipe, fअगरo);
	usbhsf_fअगरo_unselect(pipe, fअगरo);

	/* clear DCP FIFO of reception */
	अगर (usbhsf_fअगरo_select(pipe, fअगरo, 0) < 0)
		वापस;
	usbhsf_fअगरo_clear(pipe, fअगरo);
	usbhsf_fअगरo_unselect(pipe, fअगरo);
पूर्ण

/*
 *		fअगरo init
 */
व्योम usbhs_fअगरo_init(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);
	काष्ठा usbhs_fअगरo *cfअगरo = usbhsf_get_cfअगरo(priv);
	काष्ठा usbhs_fअगरo *dfअगरo;
	पूर्णांक i;

	mod->irq_empty		= usbhsf_irq_empty;
	mod->irq_पढ़ोy		= usbhsf_irq_पढ़ोy;
	mod->irq_bempsts	= 0;
	mod->irq_brdysts	= 0;

	cfअगरo->pipe	= शून्य;
	usbhs_क्रम_each_dfअगरo(priv, dfअगरo, i)
		dfअगरo->pipe	= शून्य;
पूर्ण

व्योम usbhs_fअगरo_quit(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);

	mod->irq_empty		= शून्य;
	mod->irq_पढ़ोy		= शून्य;
	mod->irq_bempsts	= 0;
	mod->irq_brdysts	= 0;
पूर्ण

#घोषणा __USBHS_DFIFO_INIT(priv, fअगरo, channel, fअगरo_port)		\
करो अणु									\
	fअगरo = usbhsf_get_dnfअगरo(priv, channel);			\
	fअगरo->name	= "D"#channel"FIFO";				\
	fअगरo->port	= fअगरo_port;					\
	fअगरo->sel	= D##channel##FIFOSEL;				\
	fअगरo->ctr	= D##channel##FIFOCTR;				\
	fअगरo->tx_slave.shdma_slave.slave_id =				\
			usbhs_get_dparam(priv, d##channel##_tx_id);	\
	fअगरo->rx_slave.shdma_slave.slave_id =				\
			usbhs_get_dparam(priv, d##channel##_rx_id);	\
	usbhsf_dma_init(priv, fअगरo, channel);				\
पूर्ण जबतक (0)

#घोषणा USBHS_DFIFO_INIT(priv, fअगरo, channel)				\
		__USBHS_DFIFO_INIT(priv, fअगरo, channel, D##channel##FIFO)
#घोषणा USBHS_DFIFO_INIT_NO_PORT(priv, fअगरo, channel)			\
		__USBHS_DFIFO_INIT(priv, fअगरo, channel, 0)

पूर्णांक usbhs_fअगरo_probe(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_fअगरo *fअगरo;

	/* CFIFO */
	fअगरo = usbhsf_get_cfअगरo(priv);
	fअगरo->name	= "CFIFO";
	fअगरo->port	= CFIFO;
	fअगरo->sel	= CFIFOSEL;
	fअगरo->ctr	= CFIFOCTR;

	/* DFIFO */
	USBHS_DFIFO_INIT(priv, fअगरo, 0);
	USBHS_DFIFO_INIT(priv, fअगरo, 1);
	USBHS_DFIFO_INIT_NO_PORT(priv, fअगरo, 2);
	USBHS_DFIFO_INIT_NO_PORT(priv, fअगरo, 3);

	वापस 0;
पूर्ण

व्योम usbhs_fअगरo_हटाओ(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_fअगरo *fअगरo;
	पूर्णांक i;

	usbhs_क्रम_each_dfअगरo(priv, fअगरo, i)
		usbhsf_dma_quit(priv, fअगरo);
पूर्ण
