<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-1.0+ */
/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#अगर_अघोषित RENESAS_USB_PIPE_H
#घोषणा RENESAS_USB_PIPE_H

#समावेश "common.h"
#समावेश "fifo.h"

/*
 *	काष्ठा
 */
काष्ठा usbhs_pipe अणु
	u32 pipe_type;	/* USB_ENDPOINT_XFER_xxx */

	काष्ठा usbhs_priv *priv;
	काष्ठा usbhs_fअगरo *fअगरo;
	काष्ठा list_head list;

	पूर्णांक maxp;

	u32 flags;
#घोषणा USBHS_PIPE_FLAGS_IS_USED		(1 << 0)
#घोषणा USBHS_PIPE_FLAGS_IS_सूची_IN		(1 << 1)
#घोषणा USBHS_PIPE_FLAGS_IS_सूची_HOST		(1 << 2)
#घोषणा USBHS_PIPE_FLAGS_IS_RUNNING		(1 << 3)

	स्थिर काष्ठा usbhs_pkt_handle *handler;

	व्योम *mod_निजी;
पूर्ण;

काष्ठा usbhs_pipe_info अणु
	काष्ठा usbhs_pipe *pipe;
	पूर्णांक size;	/* array size of "pipe" */

	पूर्णांक (*dma_map_ctrl)(काष्ठा device *dma_dev, काष्ठा usbhs_pkt *pkt,
			    पूर्णांक map);
पूर्ण;

/*
 * pipe list
 */
#घोषणा __usbhs_क्रम_each_pipe(start, pos, info, i)	\
	क्रम ((i) = start;						\
	     ((i) < (info)->size) && ((pos) = (info)->pipe + (i));	\
	     (i)++)

#घोषणा usbhs_क्रम_each_pipe(pos, priv, i)			\
	__usbhs_क्रम_each_pipe(1, pos, &((priv)->pipe_info), i)

#घोषणा usbhs_क्रम_each_pipe_with_dcp(pos, priv, i)		\
	__usbhs_क्रम_each_pipe(0, pos, &((priv)->pipe_info), i)

/*
 * data
 */
#घोषणा usbhs_priv_to_pipeinfo(pr)	(&(pr)->pipe_info)

/*
 * pipe control
 */
अक्षर *usbhs_pipe_name(काष्ठा usbhs_pipe *pipe);
काष्ठा usbhs_pipe
*usbhs_pipe_दो_स्मृति(काष्ठा usbhs_priv *priv, पूर्णांक endpoपूर्णांक_type, पूर्णांक dir_in);
व्योम usbhs_pipe_मुक्त(काष्ठा usbhs_pipe *pipe);
पूर्णांक usbhs_pipe_probe(काष्ठा usbhs_priv *priv);
व्योम usbhs_pipe_हटाओ(काष्ठा usbhs_priv *priv);
पूर्णांक usbhs_pipe_is_dir_in(काष्ठा usbhs_pipe *pipe);
पूर्णांक usbhs_pipe_is_dir_host(काष्ठा usbhs_pipe *pipe);
पूर्णांक usbhs_pipe_is_running(काष्ठा usbhs_pipe *pipe);
व्योम usbhs_pipe_running(काष्ठा usbhs_pipe *pipe, पूर्णांक running);

व्योम usbhs_pipe_init(काष्ठा usbhs_priv *priv,
		     पूर्णांक (*dma_map_ctrl)(काष्ठा device *dma_dev,
					 काष्ठा usbhs_pkt *pkt, पूर्णांक map));
पूर्णांक usbhs_pipe_get_maxpacket(काष्ठा usbhs_pipe *pipe);
व्योम usbhs_pipe_clear(काष्ठा usbhs_pipe *pipe);
व्योम usbhs_pipe_clear_without_sequence(काष्ठा usbhs_pipe *pipe,
				       पूर्णांक needs_bfre, पूर्णांक bfre_enable);
पूर्णांक usbhs_pipe_is_accessible(काष्ठा usbhs_pipe *pipe);
bool usbhs_pipe_contains_transmittable_data(काष्ठा usbhs_pipe *pipe);
व्योम usbhs_pipe_enable(काष्ठा usbhs_pipe *pipe);
व्योम usbhs_pipe_disable(काष्ठा usbhs_pipe *pipe);
व्योम usbhs_pipe_stall(काष्ठा usbhs_pipe *pipe);
पूर्णांक usbhs_pipe_is_stall(काष्ठा usbhs_pipe *pipe);
व्योम usbhs_pipe_set_trans_count_अगर_bulk(काष्ठा usbhs_pipe *pipe, पूर्णांक len);
व्योम usbhs_pipe_select_fअगरo(काष्ठा usbhs_pipe *pipe, काष्ठा usbhs_fअगरo *fअगरo);
व्योम usbhs_pipe_config_update(काष्ठा usbhs_pipe *pipe, u16 devsel,
			      u16 epnum, u16 maxp);
व्योम usbhs_pipe_config_change_bfre(काष्ठा usbhs_pipe *pipe, पूर्णांक enable);

#घोषणा usbhs_pipe_sequence_data0(pipe)	usbhs_pipe_data_sequence(pipe, 0)
#घोषणा usbhs_pipe_sequence_data1(pipe)	usbhs_pipe_data_sequence(pipe, 1)
व्योम usbhs_pipe_data_sequence(काष्ठा usbhs_pipe *pipe, पूर्णांक data);

#घोषणा usbhs_pipe_to_priv(p)	((p)->priv)
#घोषणा usbhs_pipe_number(p)	(पूर्णांक)((p) - (p)->priv->pipe_info.pipe)
#घोषणा usbhs_pipe_is_dcp(p)	((p)->priv->pipe_info.pipe == (p))
#घोषणा usbhs_pipe_to_fअगरo(p)	((p)->fअगरo)
#घोषणा usbhs_pipe_is_busy(p)	usbhs_pipe_to_fअगरo(p)

#घोषणा usbhs_pipe_type(p)		((p)->pipe_type)
#घोषणा usbhs_pipe_type_is(p, t)	((p)->pipe_type == t)

/*
 * dcp control
 */
काष्ठा usbhs_pipe *usbhs_dcp_दो_स्मृति(काष्ठा usbhs_priv *priv);
व्योम usbhs_dcp_control_transfer_करोne(काष्ठा usbhs_pipe *pipe);
व्योम usbhs_dcp_dir_क्रम_host(काष्ठा usbhs_pipe *pipe, पूर्णांक dir_out);

#पूर्ण_अगर /* RENESAS_USB_PIPE_H */
