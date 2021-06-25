<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#अगर_अघोषित _IONIC_STATS_H_
#घोषणा _IONIC_STATS_H_

#घोषणा IONIC_STAT_TO_OFFSET(type, stat_name) (दुरत्व(type, stat_name))

#घोषणा IONIC_STAT_DESC(type, stat_name) अणु \
	.name = #stat_name, \
	.offset = IONIC_STAT_TO_OFFSET(type, stat_name) \
पूर्ण

#घोषणा IONIC_PORT_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(काष्ठा ionic_port_stats, stat_name)

#घोषणा IONIC_LIF_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(काष्ठा ionic_lअगर_sw_stats, stat_name)

#घोषणा IONIC_TX_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(काष्ठा ionic_tx_stats, stat_name)

#घोषणा IONIC_RX_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(काष्ठा ionic_rx_stats, stat_name)

#घोषणा IONIC_TX_Q_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(काष्ठा ionic_queue, stat_name)

#घोषणा IONIC_CQ_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(काष्ठा ionic_cq, stat_name)

#घोषणा IONIC_INTR_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(काष्ठा ionic_पूर्णांकr_info, stat_name)

#घोषणा IONIC_NAPI_STAT_DESC(stat_name) \
	IONIC_STAT_DESC(काष्ठा ionic_napi_stats, stat_name)

/* Interface काष्ठाure क्रम a particalar stats group */
काष्ठा ionic_stats_group_पूर्णांकf अणु
	व्योम (*get_strings)(काष्ठा ionic_lअगर *lअगर, u8 **buf);
	व्योम (*get_values)(काष्ठा ionic_lअगर *lअगर, u64 **buf);
	u64 (*get_count)(काष्ठा ionic_lअगर *lअगर);
पूर्ण;

बाह्य स्थिर काष्ठा ionic_stats_group_पूर्णांकf ionic_stats_groups[];
बाह्य स्थिर पूर्णांक ionic_num_stats_grps;

#घोषणा IONIC_READ_STAT64(base_ptr, desc_ptr) \
	(*((u64 *)(((u8 *)(base_ptr)) + (desc_ptr)->offset)))

#घोषणा IONIC_READ_STAT_LE64(base_ptr, desc_ptr) \
	__le64_to_cpu(*((__le64 *)(((u8 *)(base_ptr)) + (desc_ptr)->offset)))

काष्ठा ionic_stat_desc अणु
	अक्षर name[ETH_GSTRING_LEN];
	u64 offset;
पूर्ण;

#पूर्ण_अगर /* _IONIC_STATS_H_ */
