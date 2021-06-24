<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश "dmub/dmub_srv_stat.h"
#समावेश "dmub/inc/dmub_cmd.h"

/**
 * DOC: DMUB_SRV STAT Interface
 *
 * These पूर्णांकerfaces are called without acquiring DAL and DC locks.
 * Hence, there is limitations on whese पूर्णांकerfaces can access. Only
 * variables exclusively defined क्रम these पूर्णांकerfaces can be modअगरied.
 */

/**
 *****************************************************************************
 *  Function: dmub_srv_stat_get_notअगरication
 *
 *  @brief
 *		Retrieves a dmub outbox notअगरication, set up dmub notअगरication
 *		काष्ठाure with message inक्रमmation. Also a pending bit अगर queue
 *		is having more notअगरications
 *
 *  @param [in] dmub: dmub srv काष्ठाure
 *  @param [out] pnotअगरy: dmub notअगरication काष्ठाure to be filled up
 *
 *  @वापस
 *     dmub_status
 *****************************************************************************
 */
क्रमागत dmub_status dmub_srv_stat_get_notअगरication(काष्ठा dmub_srv *dmub,
						काष्ठा dmub_notअगरication *notअगरy)
अणु
	/**
	 * This function is called without dal and dc locks, so
	 * we shall not modअगरy any dmub variables, only dmub->outbox1_rb
	 * is exempted as it is exclusively accessed by this function
	 */
	जोड़ dmub_rb_out_cmd cmd = अणु0पूर्ण;

	अगर (!dmub->hw_init) अणु
		notअगरy->type = DMUB_NOTIFICATION_NO_DATA;
		notअगरy->pending_notअगरication = false;
		वापस DMUB_STATUS_INVALID;
	पूर्ण

	/* Get ग_लिखो poपूर्णांकer which is updated by dmub */
	dmub->outbox1_rb.wrpt = dmub->hw_funcs.get_outbox1_wptr(dmub);

	अगर (!dmub_rb_out_front(&dmub->outbox1_rb, &cmd)) अणु
		notअगरy->type = DMUB_NOTIFICATION_NO_DATA;
		notअगरy->pending_notअगरication = false;
		वापस DMUB_STATUS_OK;
	पूर्ण

	चयन (cmd.cmd_common.header.type) अणु
	हाल DMUB_OUT_CMD__DP_AUX_REPLY:
		notअगरy->type = DMUB_NOTIFICATION_AUX_REPLY;
		notअगरy->link_index = cmd.dp_aux_reply.control.instance;
		notअगरy->result = cmd.dp_aux_reply.control.result;
		dmub_स_नकल((व्योम *)&notअगरy->aux_reply,
			(व्योम *)&cmd.dp_aux_reply.reply_data, माप(काष्ठा aux_reply_data));
		अवरोध;
	शेष:
		notअगरy->type = DMUB_NOTIFICATION_NO_DATA;
		अवरोध;
	पूर्ण

	/* Pop outbox1 ringbuffer and update पढ़ो poपूर्णांकer */
	dmub_rb_pop_front(&dmub->outbox1_rb);
	dmub->hw_funcs.set_outbox1_rptr(dmub, dmub->outbox1_rb.rptr);

	/**
	 * Notअगरy dc whether dmub has a pending outbox message,
	 * this is to aव्योम one more call to dmub_srv_stat_get_notअगरication
	 */
	अगर (dmub_rb_empty(&dmub->outbox1_rb))
		notअगरy->pending_notअगरication = false;
	अन्यथा
		notअगरy->pending_notअगरication = true;

	वापस DMUB_STATUS_OK;
पूर्ण
