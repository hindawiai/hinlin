<शैली गुरु>
/*
 * Copyright (c) 2004-2011 Atheros Communications Inc.
 * Copyright (c) 2011 Qualcomm Atheros, Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित HIF_OPS_H
#घोषणा HIF_OPS_H

#समावेश "hif.h"
#समावेश "debug.h"

अटल अंतरभूत पूर्णांक hअगर_पढ़ो_ग_लिखो_sync(काष्ठा ath6kl *ar, u32 addr, u8 *buf,
				      u32 len, u32 request)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF,
		   "hif %s sync addr 0x%x buf 0x%p len %d request 0x%x\n",
		   (request & HIF_WRITE) ? "write" : "read",
		   addr, buf, len, request);

	वापस ar->hअगर_ops->पढ़ो_ग_लिखो_sync(ar, addr, buf, len, request);
पूर्ण

अटल अंतरभूत पूर्णांक hअगर_ग_लिखो_async(काष्ठा ath6kl *ar, u32 address, u8 *buffer,
				  u32 length, u32 request,
				  काष्ठा htc_packet *packet)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF,
		   "hif write async addr 0x%x buf 0x%p len %d request 0x%x\n",
		   address, buffer, length, request);

	वापस ar->hअगर_ops->ग_लिखो_async(ar, address, buffer, length,
					request, packet);
पूर्ण
अटल अंतरभूत व्योम ath6kl_hअगर_irq_enable(काष्ठा ath6kl *ar)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif irq enable\n");

	वापस ar->hअगर_ops->irq_enable(ar);
पूर्ण

अटल अंतरभूत व्योम ath6kl_hअगर_irq_disable(काष्ठा ath6kl *ar)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif irq disable\n");

	वापस ar->hअगर_ops->irq_disable(ar);
पूर्ण

अटल अंतरभूत काष्ठा hअगर_scatter_req *hअगर_scatter_req_get(काष्ठा ath6kl *ar)
अणु
	वापस ar->hअगर_ops->scatter_req_get(ar);
पूर्ण

अटल अंतरभूत व्योम hअगर_scatter_req_add(काष्ठा ath6kl *ar,
				       काष्ठा hअगर_scatter_req *s_req)
अणु
	वापस ar->hअगर_ops->scatter_req_add(ar, s_req);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_hअगर_enable_scatter(काष्ठा ath6kl *ar)
अणु
	वापस ar->hअगर_ops->enable_scatter(ar);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_hअगर_scat_req_rw(काष्ठा ath6kl *ar,
					 काष्ठा hअगर_scatter_req *scat_req)
अणु
	वापस ar->hअगर_ops->scat_req_rw(ar, scat_req);
पूर्ण

अटल अंतरभूत व्योम ath6kl_hअगर_cleanup_scatter(काष्ठा ath6kl *ar)
अणु
	वापस ar->hअगर_ops->cleanup_scatter(ar);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_hअगर_suspend(काष्ठा ath6kl *ar,
				     काष्ठा cfg80211_wowlan *wow)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif suspend\n");

	वापस ar->hअगर_ops->suspend(ar, wow);
पूर्ण

/*
 * Read from the ATH6KL through its diagnostic winकरोw. No cooperation from
 * the Target is required क्रम this.
 */
अटल अंतरभूत पूर्णांक ath6kl_hअगर_diag_पढ़ो32(काष्ठा ath6kl *ar, u32 address,
					 u32 *value)
अणु
	वापस ar->hअगर_ops->diag_पढ़ो32(ar, address, value);
पूर्ण

/*
 * Write to the ATH6KL through its diagnostic winकरोw. No cooperation from
 * the Target is required क्रम this.
 */
अटल अंतरभूत पूर्णांक ath6kl_hअगर_diag_ग_लिखो32(काष्ठा ath6kl *ar, u32 address,
					  __le32 value)
अणु
	वापस ar->hअगर_ops->diag_ग_लिखो32(ar, address, value);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_hअगर_bmi_पढ़ो(काष्ठा ath6kl *ar, u8 *buf, u32 len)
अणु
	वापस ar->hअगर_ops->bmi_पढ़ो(ar, buf, len);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_hअगर_bmi_ग_लिखो(काष्ठा ath6kl *ar, u8 *buf, u32 len)
अणु
	वापस ar->hअगर_ops->bmi_ग_लिखो(ar, buf, len);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_hअगर_resume(काष्ठा ath6kl *ar)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif resume\n");

	वापस ar->hअगर_ops->resume(ar);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_hअगर_घातer_on(काष्ठा ath6kl *ar)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif power on\n");

	वापस ar->hअगर_ops->घातer_on(ar);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_hअगर_घातer_off(काष्ठा ath6kl *ar)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif power off\n");

	वापस ar->hअगर_ops->घातer_off(ar);
पूर्ण

अटल अंतरभूत व्योम ath6kl_hअगर_stop(काष्ठा ath6kl *ar)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif stop\n");

	ar->hअगर_ops->stop(ar);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_hअगर_pipe_send(काष्ठा ath6kl *ar,
				       u8 pipe, काष्ठा sk_buff *hdr_buf,
				       काष्ठा sk_buff *buf)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif pipe send\n");

	वापस ar->hअगर_ops->pipe_send(ar, pipe, hdr_buf, buf);
पूर्ण

अटल अंतरभूत व्योम ath6kl_hअगर_pipe_get_शेष(काष्ठा ath6kl *ar,
					       u8 *ul_pipe, u8 *dl_pipe)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif pipe get default\n");

	ar->hअगर_ops->pipe_get_शेष(ar, ul_pipe, dl_pipe);
पूर्ण

अटल अंतरभूत पूर्णांक ath6kl_hअगर_pipe_map_service(काष्ठा ath6kl *ar,
					      u16 service_id, u8 *ul_pipe,
					      u8 *dl_pipe)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif pipe get default\n");

	वापस ar->hअगर_ops->pipe_map_service(ar, service_id, ul_pipe, dl_pipe);
पूर्ण

अटल अंतरभूत u16 ath6kl_hअगर_pipe_get_मुक्त_queue_number(काष्ठा ath6kl *ar,
							u8 pipe)
अणु
	ath6kl_dbg(ATH6KL_DBG_HIF, "hif pipe get free queue number\n");

	वापस ar->hअगर_ops->pipe_get_मुक्त_queue_number(ar, pipe);
पूर्ण

#पूर्ण_अगर
