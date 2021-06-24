<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ */
/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#अगर_अघोषित RENESAS_USB_FIFO_H
#घोषणा RENESAS_USB_FIFO_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sh_dma.h>
#समावेश <linux/workqueue.h>
#समावेश <यंत्र/dma.h>
#समावेश "pipe.h"

काष्ठा usbhs_fअगरo अणु
	अक्षर *name;
	u32 port;	/* xFIFO */
	u32 sel;	/* xFIFOSEL */
	u32 ctr;	/* xFIFOCTR */

	काष्ठा usbhs_pipe	*pipe;

	काष्ठा dma_chan		*tx_chan;
	काष्ठा dma_chan		*rx_chan;

	काष्ठा sh_dmae_slave	tx_slave;
	काष्ठा sh_dmae_slave	rx_slave;
पूर्ण;

#घोषणा USBHS_MAX_NUM_DFIFO	4
काष्ठा usbhs_fअगरo_info अणु
	काष्ठा usbhs_fअगरo cfअगरo;
	काष्ठा usbhs_fअगरo dfअगरo[USBHS_MAX_NUM_DFIFO];
पूर्ण;
#घोषणा usbhsf_get_dnfअगरo(p, n)	(&((p)->fअगरo_info.dfअगरo[n]))
#घोषणा usbhs_क्रम_each_dfअगरo(priv, dfअगरo, i)			\
	क्रम ((i) = 0;						\
	     ((i) < USBHS_MAX_NUM_DFIFO) &&			\
		     ((dfअगरo) = usbhsf_get_dnfअगरo(priv, (i)));	\
	     (i)++)

काष्ठा usbhs_pkt_handle;
काष्ठा usbhs_pkt अणु
	काष्ठा list_head node;
	काष्ठा usbhs_pipe *pipe;
	स्थिर काष्ठा usbhs_pkt_handle *handler;
	व्योम (*करोne)(काष्ठा usbhs_priv *priv,
		     काष्ठा usbhs_pkt *pkt);
	काष्ठा work_काष्ठा work;
	dma_addr_t dma;
	स्थिर काष्ठा dmaengine_result *dma_result;
	व्योम *buf;
	पूर्णांक length;
	पूर्णांक trans;
	पूर्णांक actual;
	पूर्णांक zero;
	पूर्णांक sequence;
पूर्ण;

काष्ठा usbhs_pkt_handle अणु
	पूर्णांक (*prepare)(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne);
	पूर्णांक (*try_run)(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne);
	पूर्णांक (*dma_करोne)(काष्ठा usbhs_pkt *pkt, पूर्णांक *is_करोne);
पूर्ण;

/*
 * fअगरo
 */
पूर्णांक usbhs_fअगरo_probe(काष्ठा usbhs_priv *priv);
व्योम usbhs_fअगरo_हटाओ(काष्ठा usbhs_priv *priv);
व्योम usbhs_fअगरo_init(काष्ठा usbhs_priv *priv);
व्योम usbhs_fअगरo_quit(काष्ठा usbhs_priv *priv);
व्योम usbhs_fअगरo_clear_dcp(काष्ठा usbhs_pipe *pipe);

/*
 * packet info
 */
बाह्य स्थिर काष्ठा usbhs_pkt_handle usbhs_fअगरo_pio_push_handler;
बाह्य स्थिर काष्ठा usbhs_pkt_handle usbhs_fअगरo_pio_pop_handler;
बाह्य स्थिर काष्ठा usbhs_pkt_handle usbhs_ctrl_stage_end_handler;

बाह्य स्थिर काष्ठा usbhs_pkt_handle usbhs_fअगरo_dma_push_handler;
बाह्य स्थिर काष्ठा usbhs_pkt_handle usbhs_fअगरo_dma_pop_handler;

बाह्य स्थिर काष्ठा usbhs_pkt_handle usbhs_dcp_status_stage_in_handler;
बाह्य स्थिर काष्ठा usbhs_pkt_handle usbhs_dcp_status_stage_out_handler;

बाह्य स्थिर काष्ठा usbhs_pkt_handle usbhs_dcp_data_stage_in_handler;
बाह्य स्थिर काष्ठा usbhs_pkt_handle usbhs_dcp_data_stage_out_handler;

व्योम usbhs_pkt_init(काष्ठा usbhs_pkt *pkt);
व्योम usbhs_pkt_push(काष्ठा usbhs_pipe *pipe, काष्ठा usbhs_pkt *pkt,
		    व्योम (*करोne)(काष्ठा usbhs_priv *priv,
				 काष्ठा usbhs_pkt *pkt),
		    व्योम *buf, पूर्णांक len, पूर्णांक zero, पूर्णांक sequence);
काष्ठा usbhs_pkt *usbhs_pkt_pop(काष्ठा usbhs_pipe *pipe, काष्ठा usbhs_pkt *pkt);
व्योम usbhs_pkt_start(काष्ठा usbhs_pipe *pipe);
काष्ठा usbhs_pkt *__usbhsf_pkt_get(काष्ठा usbhs_pipe *pipe);

#पूर्ण_अगर /* RENESAS_USB_FIFO_H */
