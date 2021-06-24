<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Marvell OcteonTx2 PTP support क्रम ethernet driver */

#अगर_अघोषित OTX2_PTP_H
#घोषणा OTX2_PTP_H

पूर्णांक otx2_ptp_init(काष्ठा otx2_nic *pfvf);
व्योम otx2_ptp_destroy(काष्ठा otx2_nic *pfvf);

पूर्णांक otx2_ptp_घड़ी_index(काष्ठा otx2_nic *pfvf);
पूर्णांक otx2_ptp_tstamp2समय(काष्ठा otx2_nic *pfvf, u64 tstamp, u64 *tsns);

#पूर्ण_अगर
