<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Author: Hugues Fruchet <hugues.fruchet@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित DELTA_IPC_H
#घोषणा DELTA_IPC_H

पूर्णांक delta_ipc_init(काष्ठा delta_dev *delta);
व्योम delta_ipc_निकास(काष्ठा delta_dev *delta);

/*
 * delta_ipc_खोलो - खोलो a decoding instance on firmware side
 * @ctx:		(in) delta context
 * @name:		(in) name of decoder to be used
 * @param:		(in) खोलो command parameters specअगरic to decoder
 *  @param.size:		(in) size of parameter
 *  @param.data:		(in) भव address of parameter
 * @ipc_buf_size:	(in) size of IPC shared buffer between host
 *			     and copro used to share command data.
 *			     Client have to set here the size of the biggest
 *			     command parameters (+ status अगर any).
 *			     Allocation will be करोne in this function which
 *			     will give back to client in @ipc_buf the भव
 *			     & physical addresses & size of shared IPC buffer.
 *			     All the further command data (parameters + status)
 *			     have to be written in this shared IPC buffer
 *			     भव memory. This is करोne to aव्योम
 *			     unnecessary copies of command data.
 * @ipc_buf:		(out) allocated IPC shared buffer
 *  @ipc_buf.size:		(out) allocated size
 *  @ipc_buf.vaddr:		(out) भव address where to copy
 *				      further command data
 * @hdl:		(out) handle of decoding instance.
 */

पूर्णांक delta_ipc_खोलो(काष्ठा delta_ctx *ctx, स्थिर अक्षर *name,
		   काष्ठा delta_ipc_param *param, u32 ipc_buf_size,
		   काष्ठा delta_buf **ipc_buf, व्योम **hdl);

/*
 * delta_ipc_set_stream - set inक्रमmation about stream to decoder
 * @hdl:		(in) handle of decoding instance.
 * @param:		(in) set stream command parameters specअगरic to decoder
 *  @param.size:		(in) size of parameter
 *  @param.data:		(in) भव address of parameter. Must be
 *				     within IPC shared buffer range
 */
पूर्णांक delta_ipc_set_stream(व्योम *hdl, काष्ठा delta_ipc_param *param);

/*
 * delta_ipc_decode - frame decoding synchronous request, वापसs only
 *		      after decoding completion on firmware side.
 * @hdl:		(in) handle of decoding instance.
 * @param:		(in) decode command parameters specअगरic to decoder
 *  @param.size:		(in) size of parameter
 *  @param.data:		(in) भव address of parameter. Must be
 *				     within IPC shared buffer range
 * @status:		(in/out) decode command status specअगरic to decoder
 *  @status.size:		(in) size of status
 *  @status.data:		(in/out) भव address of status. Must be
 *					 within IPC shared buffer range.
 *					 Status is filled by decoding instance
 *					 after decoding completion.
 */
पूर्णांक delta_ipc_decode(व्योम *hdl, काष्ठा delta_ipc_param *param,
		     काष्ठा delta_ipc_param *status);

/*
 * delta_ipc_बंद - बंद decoding instance
 * @hdl:		(in) handle of decoding instance to बंद.
 */
व्योम delta_ipc_बंद(व्योम *hdl);

#पूर्ण_अगर /* DELTA_IPC_H */
