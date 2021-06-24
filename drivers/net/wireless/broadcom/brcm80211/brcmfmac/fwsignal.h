<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012 Broadcom Corporation
 */

#अगर_अघोषित FWSIGNAL_H_
#घोषणा FWSIGNAL_H_

/**
 * क्रमागत brcmf_fws_fअगरo - fअगरo indices used by करोngle firmware.
 *
 * @BRCMF_FWS_FIFO_FIRST: first fअगरo, ie. background.
 * @BRCMF_FWS_FIFO_AC_BK: fअगरo क्रम background traffic.
 * @BRCMF_FWS_FIFO_AC_BE: fअगरo क्रम best-efक्रमt traffic.
 * @BRCMF_FWS_FIFO_AC_VI: fअगरo क्रम video traffic.
 * @BRCMF_FWS_FIFO_AC_VO: fअगरo क्रम voice traffic.
 * @BRCMF_FWS_FIFO_BCMC: fअगरo क्रम broadcast/multicast (AP only).
 * @BRCMF_FWS_FIFO_ATIM: fअगरo क्रम ATIM (AP only).
 * @BRCMF_FWS_FIFO_COUNT: number of fअगरos.
 */
क्रमागत brcmf_fws_fअगरo अणु
	BRCMF_FWS_FIFO_FIRST,
	BRCMF_FWS_FIFO_AC_BK = BRCMF_FWS_FIFO_FIRST,
	BRCMF_FWS_FIFO_AC_BE,
	BRCMF_FWS_FIFO_AC_VI,
	BRCMF_FWS_FIFO_AC_VO,
	BRCMF_FWS_FIFO_BCMC,
	BRCMF_FWS_FIFO_ATIM,
	BRCMF_FWS_FIFO_COUNT
पूर्ण;

काष्ठा brcmf_fws_info *brcmf_fws_attach(काष्ठा brcmf_pub *drvr);
व्योम brcmf_fws_detach(काष्ठा brcmf_fws_info *fws);
व्योम brcmf_fws_debugfs_create(काष्ठा brcmf_pub *drvr);
bool brcmf_fws_queue_skbs(काष्ठा brcmf_fws_info *fws);
bool brcmf_fws_fc_active(काष्ठा brcmf_fws_info *fws);
व्योम brcmf_fws_hdrpull(काष्ठा brcmf_अगर *अगरp, s16 siglen, काष्ठा sk_buff *skb);
पूर्णांक brcmf_fws_process_skb(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *skb);

व्योम brcmf_fws_reset_पूर्णांकerface(काष्ठा brcmf_अगर *अगरp);
व्योम brcmf_fws_add_पूर्णांकerface(काष्ठा brcmf_अगर *अगरp);
व्योम brcmf_fws_del_पूर्णांकerface(काष्ठा brcmf_अगर *अगरp);
व्योम brcmf_fws_bustxfail(काष्ठा brcmf_fws_info *fws, काष्ठा sk_buff *skb);
व्योम brcmf_fws_bus_blocked(काष्ठा brcmf_pub *drvr, bool flow_blocked);
व्योम brcmf_fws_rxreorder(काष्ठा brcmf_अगर *अगरp, काष्ठा sk_buff *skb, bool inirq);

#पूर्ण_अगर /* FWSIGNAL_H_ */
