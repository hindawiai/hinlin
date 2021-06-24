<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/* Copyright (c) 2019 Mellanox Technologies. All rights reserved */

#अगर_अघोषित _MLXSW_SPECTRUM_PTP_H
#घोषणा _MLXSW_SPECTRUM_PTP_H

#समावेश <linux/device.h>
#समावेश <linux/rhashtable.h>

काष्ठा mlxsw_sp;
काष्ठा mlxsw_sp_port;
काष्ठा mlxsw_sp_ptp_घड़ी;

अटल अंतरभूत पूर्णांक mlxsw_sp_ptp_get_ts_info_noptp(काष्ठा ethtool_ts_info *info)
अणु
	info->so_बारtamping = SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE;
	info->phc_index = -1;
	वापस 0;
पूर्ण

#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)

काष्ठा mlxsw_sp_ptp_घड़ी *
mlxsw_sp1_ptp_घड़ी_init(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा device *dev);

व्योम mlxsw_sp1_ptp_घड़ी_fini(काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी);

काष्ठा mlxsw_sp_ptp_state *mlxsw_sp1_ptp_init(काष्ठा mlxsw_sp *mlxsw_sp);

व्योम mlxsw_sp1_ptp_fini(काष्ठा mlxsw_sp_ptp_state *ptp_state);

व्योम mlxsw_sp1_ptp_receive(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा sk_buff *skb,
			   u8 local_port);

व्योम mlxsw_sp1_ptp_transmitted(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा sk_buff *skb, u8 local_port);

व्योम mlxsw_sp1_ptp_got_बारtamp(काष्ठा mlxsw_sp *mlxsw_sp, bool ingress,
				 u8 local_port, u8 message_type,
				 u8 करोमुख्य_number, u16 sequence_id,
				 u64 बारtamp);

पूर्णांक mlxsw_sp1_ptp_hwtstamp_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       काष्ठा hwtstamp_config *config);

पूर्णांक mlxsw_sp1_ptp_hwtstamp_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       काष्ठा hwtstamp_config *config);

व्योम mlxsw_sp1_ptp_shaper_work(काष्ठा work_काष्ठा *work);

पूर्णांक mlxsw_sp1_ptp_get_ts_info(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा ethtool_ts_info *info);

पूर्णांक mlxsw_sp1_get_stats_count(व्योम);
व्योम mlxsw_sp1_get_stats_strings(u8 **p);
व्योम mlxsw_sp1_get_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			 u64 *data, पूर्णांक data_index);

#अन्यथा

अटल अंतरभूत काष्ठा mlxsw_sp_ptp_घड़ी *
mlxsw_sp1_ptp_घड़ी_init(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp1_ptp_घड़ी_fini(काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी)
अणु
पूर्ण

अटल अंतरभूत काष्ठा mlxsw_sp_ptp_state *
mlxsw_sp1_ptp_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp1_ptp_fini(काष्ठा mlxsw_sp_ptp_state *ptp_state)
अणु
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp1_ptp_receive(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा sk_buff *skb, u8 local_port)
अणु
	mlxsw_sp_rx_listener_no_mark_func(skb, local_port, mlxsw_sp);
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp1_ptp_transmitted(काष्ठा mlxsw_sp *mlxsw_sp,
					     काष्ठा sk_buff *skb, u8 local_port)
अणु
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_sp1_ptp_got_बारtamp(काष्ठा mlxsw_sp *mlxsw_sp, bool ingress,
			    u8 local_port, u8 message_type,
			    u8 करोमुख्य_number,
			    u16 sequence_id, u64 बारtamp)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक
mlxsw_sp1_ptp_hwtstamp_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा hwtstamp_config *config)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
mlxsw_sp1_ptp_hwtstamp_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा hwtstamp_config *config)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp1_ptp_shaper_work(काष्ठा work_काष्ठा *work)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_sp1_ptp_get_ts_info(काष्ठा mlxsw_sp *mlxsw_sp,
					    काष्ठा ethtool_ts_info *info)
अणु
	वापस mlxsw_sp_ptp_get_ts_info_noptp(info);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_sp1_get_stats_count(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp1_get_stats_strings(u8 **p)
अणु
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp1_get_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				       u64 *data, पूर्णांक data_index)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा mlxsw_sp_ptp_घड़ी *
mlxsw_sp2_ptp_घड़ी_init(काष्ठा mlxsw_sp *mlxsw_sp, काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp2_ptp_घड़ी_fini(काष्ठा mlxsw_sp_ptp_घड़ी *घड़ी)
अणु
पूर्ण

अटल अंतरभूत काष्ठा mlxsw_sp_ptp_state *
mlxsw_sp2_ptp_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp2_ptp_fini(काष्ठा mlxsw_sp_ptp_state *ptp_state)
अणु
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp2_ptp_receive(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा sk_buff *skb, u8 local_port)
अणु
	mlxsw_sp_rx_listener_no_mark_func(skb, local_port, mlxsw_sp);
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp2_ptp_transmitted(काष्ठा mlxsw_sp *mlxsw_sp,
					     काष्ठा sk_buff *skb, u8 local_port)
अणु
	dev_kमुक्त_skb_any(skb);
पूर्ण

अटल अंतरभूत पूर्णांक
mlxsw_sp2_ptp_hwtstamp_get(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा hwtstamp_config *config)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
mlxsw_sp2_ptp_hwtstamp_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   काष्ठा hwtstamp_config *config)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp2_ptp_shaper_work(काष्ठा work_काष्ठा *work)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_sp2_ptp_get_ts_info(काष्ठा mlxsw_sp *mlxsw_sp,
					    काष्ठा ethtool_ts_info *info)
अणु
	वापस mlxsw_sp_ptp_get_ts_info_noptp(info);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_sp2_get_stats_count(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp2_get_stats_strings(u8 **p)
अणु
पूर्ण

अटल अंतरभूत व्योम mlxsw_sp2_get_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				       u64 *data, पूर्णांक data_index)
अणु
पूर्ण

#पूर्ण_अगर
