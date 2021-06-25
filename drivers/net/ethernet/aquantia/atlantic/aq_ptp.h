<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_ptp.h: Declaration of PTP functions.
 */
#अगर_अघोषित AQ_PTP_H
#घोषणा AQ_PTP_H

#समावेश <linux/net_tstamp.h>

#समावेश "aq_ring.h"

#घोषणा PTP_8TC_RING_IDX             8
#घोषणा PTP_4TC_RING_IDX            16
#घोषणा PTP_HWST_RING_IDX           31

/* Index must to be 8 (8 TCs) or 16 (4 TCs).
 * It depends from Traffic Class mode.
 */
अटल अंतरभूत अचिन्हित पूर्णांक aq_ptp_ring_idx(स्थिर क्रमागत aq_tc_mode tc_mode)
अणु
	अगर (tc_mode == AQ_TC_MODE_8TCS)
		वापस PTP_8TC_RING_IDX;

	वापस PTP_4TC_RING_IDX;
पूर्ण

#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)

/* Common functions */
पूर्णांक aq_ptp_init(काष्ठा aq_nic_s *aq_nic, अचिन्हित पूर्णांक idx_vec);

व्योम aq_ptp_unरेजिस्टर(काष्ठा aq_nic_s *aq_nic);
व्योम aq_ptp_मुक्त(काष्ठा aq_nic_s *aq_nic);

पूर्णांक aq_ptp_irq_alloc(काष्ठा aq_nic_s *aq_nic);
व्योम aq_ptp_irq_मुक्त(काष्ठा aq_nic_s *aq_nic);

पूर्णांक aq_ptp_ring_alloc(काष्ठा aq_nic_s *aq_nic);
व्योम aq_ptp_ring_मुक्त(काष्ठा aq_nic_s *aq_nic);

पूर्णांक aq_ptp_ring_init(काष्ठा aq_nic_s *aq_nic);
पूर्णांक aq_ptp_ring_start(काष्ठा aq_nic_s *aq_nic);
व्योम aq_ptp_ring_stop(काष्ठा aq_nic_s *aq_nic);
व्योम aq_ptp_ring_deinit(काष्ठा aq_nic_s *aq_nic);

व्योम aq_ptp_service_task(काष्ठा aq_nic_s *aq_nic);

व्योम aq_ptp_पंचांग_offset_set(काष्ठा aq_nic_s *aq_nic, अचिन्हित पूर्णांक mbps);

व्योम aq_ptp_घड़ी_init(काष्ठा aq_nic_s *aq_nic);

/* Traffic processing functions */
पूर्णांक aq_ptp_xmit(काष्ठा aq_nic_s *aq_nic, काष्ठा sk_buff *skb);
व्योम aq_ptp_tx_hwtstamp(काष्ठा aq_nic_s *aq_nic, u64 बारtamp);

/* Must be to check available of PTP beक्रमe call */
व्योम aq_ptp_hwtstamp_config_get(काष्ठा aq_ptp_s *aq_ptp,
				काष्ठा hwtstamp_config *config);
पूर्णांक aq_ptp_hwtstamp_config_set(काष्ठा aq_ptp_s *aq_ptp,
			       काष्ठा hwtstamp_config *config);

/* Return either ring is beदीर्घ to PTP or not*/
bool aq_ptp_ring(काष्ठा aq_nic_s *aq_nic, काष्ठा aq_ring_s *ring);

u16 aq_ptp_extract_ts(काष्ठा aq_nic_s *aq_nic, काष्ठा sk_buff *skb, u8 *p,
		      अचिन्हित पूर्णांक len);

काष्ठा ptp_घड़ी *aq_ptp_get_ptp_घड़ी(काष्ठा aq_ptp_s *aq_ptp);

पूर्णांक aq_ptp_link_change(काष्ठा aq_nic_s *aq_nic);

/* PTP ring statistics */
पूर्णांक aq_ptp_get_ring_cnt(काष्ठा aq_nic_s *aq_nic, स्थिर क्रमागत atl_ring_type ring_type);
u64 *aq_ptp_get_stats(काष्ठा aq_nic_s *aq_nic, u64 *data);

#अन्यथा

अटल अंतरभूत पूर्णांक aq_ptp_init(काष्ठा aq_nic_s *aq_nic, अचिन्हित पूर्णांक idx_vec)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम aq_ptp_unरेजिस्टर(काष्ठा aq_nic_s *aq_nic) अणुपूर्ण

अटल अंतरभूत व्योम aq_ptp_मुक्त(काष्ठा aq_nic_s *aq_nic)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक aq_ptp_irq_alloc(काष्ठा aq_nic_s *aq_nic)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम aq_ptp_irq_मुक्त(काष्ठा aq_nic_s *aq_nic)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक aq_ptp_ring_alloc(काष्ठा aq_nic_s *aq_nic)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम aq_ptp_ring_मुक्त(काष्ठा aq_nic_s *aq_nic) अणुपूर्ण

अटल अंतरभूत पूर्णांक aq_ptp_ring_init(काष्ठा aq_nic_s *aq_nic)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक aq_ptp_ring_start(काष्ठा aq_nic_s *aq_nic)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम aq_ptp_ring_stop(काष्ठा aq_nic_s *aq_nic) अणुपूर्ण
अटल अंतरभूत व्योम aq_ptp_ring_deinit(काष्ठा aq_nic_s *aq_nic) अणुपूर्ण
अटल अंतरभूत व्योम aq_ptp_service_task(काष्ठा aq_nic_s *aq_nic) अणुपूर्ण
अटल अंतरभूत व्योम aq_ptp_पंचांग_offset_set(काष्ठा aq_nic_s *aq_nic,
					अचिन्हित पूर्णांक mbps) अणुपूर्ण
अटल अंतरभूत व्योम aq_ptp_घड़ी_init(काष्ठा aq_nic_s *aq_nic) अणुपूर्ण
अटल अंतरभूत पूर्णांक aq_ptp_xmit(काष्ठा aq_nic_s *aq_nic, काष्ठा sk_buff *skb)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम aq_ptp_tx_hwtstamp(काष्ठा aq_nic_s *aq_nic, u64 बारtamp) अणुपूर्ण
अटल अंतरभूत व्योम aq_ptp_hwtstamp_config_get(काष्ठा aq_ptp_s *aq_ptp,
					      काष्ठा hwtstamp_config *config) अणुपूर्ण
अटल अंतरभूत पूर्णांक aq_ptp_hwtstamp_config_set(काष्ठा aq_ptp_s *aq_ptp,
					     काष्ठा hwtstamp_config *config)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool aq_ptp_ring(काष्ठा aq_nic_s *aq_nic, काष्ठा aq_ring_s *ring)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u16 aq_ptp_extract_ts(काष्ठा aq_nic_s *aq_nic,
				    काष्ठा sk_buff *skb, u8 *p,
				    अचिन्हित पूर्णांक len)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा ptp_घड़ी *aq_ptp_get_ptp_घड़ी(काष्ठा aq_ptp_s *aq_ptp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक aq_ptp_link_change(काष्ठा aq_nic_s *aq_nic)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* AQ_PTP_H */
