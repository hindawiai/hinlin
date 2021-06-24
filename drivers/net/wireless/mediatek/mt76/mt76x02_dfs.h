<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2016 Lorenzo Bianconi <lorenzo.bianconi83@gmail.com>
 */

#अगर_अघोषित __MT76x02_DFS_H
#घोषणा __MT76x02_DFS_H

#समावेश <linux/types.h>
#समावेश <linux/nl80211.h>

#घोषणा MT_DFS_GP_INTERVAL		(10 << 4) /* 64 us unit */
#घोषणा MT_DFS_NUM_ENGINES		4

/* bbp params */
#घोषणा MT_DFS_SYM_ROUND		0
#घोषणा MT_DFS_DELTA_DELAY		2
#घोषणा MT_DFS_VGA_MASK			0
#घोषणा MT_DFS_PWR_GAIN_OFFSET		3
#घोषणा MT_DFS_PWR_DOWN_TIME		0xf
#घोषणा MT_DFS_RX_PE_MASK		0xff
#घोषणा MT_DFS_PKT_END_MASK		0
#घोषणा MT_DFS_CH_EN			0xf

/* sw detector params */
#घोषणा MT_DFS_EVENT_LOOP		64
#घोषणा MT_DFS_SW_TIMEOUT		(HZ / 20)
#घोषणा MT_DFS_EVENT_WINDOW		(HZ / 5)
#घोषणा MT_DFS_SEQUENCE_WINDOW		(200 * (1 << 20))
#घोषणा MT_DFS_EVENT_TIME_MARGIN	2000
#घोषणा MT_DFS_PRI_MARGIN		4
#घोषणा MT_DFS_SEQUENCE_TH		6

#घोषणा MT_DFS_FCC_MAX_PRI		((28570 << 1) + 1000)
#घोषणा MT_DFS_FCC_MIN_PRI		(3000 - 2)
#घोषणा MT_DFS_JP_MAX_PRI		((80000 << 1) + 1000)
#घोषणा MT_DFS_JP_MIN_PRI		(28500 - 2)
#घोषणा MT_DFS_ETSI_MAX_PRI		(133333 + 125000 + 117647 + 1000)
#घोषणा MT_DFS_ETSI_MIN_PRI		(4500 - 20)

काष्ठा mt76x02_radar_specs अणु
	u8 mode;
	u16 avg_len;
	u16 e_low;
	u16 e_high;
	u16 w_low;
	u16 w_high;
	u16 w_margin;
	u32 t_low;
	u32 t_high;
	u16 t_margin;
	u32 b_low;
	u32 b_high;
	u32 event_expiration;
	u16 pwr_jmp;
पूर्ण;

#घोषणा MT_DFS_CHECK_EVENT(x)		((x) != GENMASK(31, 0))
#घोषणा MT_DFS_EVENT_ENGINE(x)		(((x) & BIT(31)) ? 2 : 0)
#घोषणा MT_DFS_EVENT_TIMESTAMP(x)	((x) & GENMASK(21, 0))
#घोषणा MT_DFS_EVENT_WIDTH(x)		((x) & GENMASK(11, 0))
काष्ठा mt76x02_dfs_event अणु
	अचिन्हित दीर्घ fetch_ts;
	u32 ts;
	u16 width;
	u8 engine;
पूर्ण;

#घोषणा MT_DFS_EVENT_BUFLEN		256
काष्ठा mt76x02_dfs_event_rb अणु
	काष्ठा mt76x02_dfs_event data[MT_DFS_EVENT_BUFLEN];
	पूर्णांक h_rb, t_rb;
पूर्ण;

काष्ठा mt76x02_dfs_sequence अणु
	काष्ठा list_head head;
	u32 first_ts;
	u32 last_ts;
	u32 pri;
	u16 count;
	u8 engine;
पूर्ण;

काष्ठा mt76x02_dfs_hw_pulse अणु
	u8 engine;
	u32 period;
	u32 w1;
	u32 w2;
	u32 burst;
पूर्ण;

काष्ठा mt76x02_dfs_sw_detector_params अणु
	u32 min_pri;
	u32 max_pri;
	u32 pri_margin;
पूर्ण;

काष्ठा mt76x02_dfs_engine_stats अणु
	u32 hw_pattern;
	u32 hw_pulse_discarded;
	u32 sw_pattern;
पूर्ण;

काष्ठा mt76x02_dfs_seq_stats अणु
	u32 seq_pool_len;
	u32 seq_len;
पूर्ण;

काष्ठा mt76x02_dfs_pattern_detector अणु
	u8 chirp_pulse_cnt;
	u32 chirp_pulse_ts;

	काष्ठा mt76x02_dfs_sw_detector_params sw_dpd_params;
	काष्ठा mt76x02_dfs_event_rb event_rb[2];

	काष्ठा list_head sequences;
	काष्ठा list_head seq_pool;
	काष्ठा mt76x02_dfs_seq_stats seq_stats;

	अचिन्हित दीर्घ last_sw_check;
	u32 last_event_ts;

	काष्ठा mt76x02_dfs_engine_stats stats[MT_DFS_NUM_ENGINES];
	काष्ठा tasklet_काष्ठा dfs_tasklet;
पूर्ण;

व्योम mt76x02_dfs_init_params(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_dfs_init_detector(काष्ठा mt76x02_dev *dev);
व्योम mt76x02_regd_notअगरier(काष्ठा wiphy *wiphy,
			   काष्ठा regulatory_request *request);
व्योम mt76x02_phy_dfs_adjust_agc(काष्ठा mt76x02_dev *dev);
#पूर्ण_अगर /* __MT76x02_DFS_H */
