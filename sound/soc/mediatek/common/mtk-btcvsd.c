<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Mediatek ALSA BT SCO CVSD/MSBC Driver
//
// Copyright (c) 2019 MediaTek Inc.
// Author: KaiChieh Chuang <kaichieh.chuang@mediatek.com>

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश <sound/soc.h>

#घोषणा BTCVSD_SND_NAME "mtk-btcvsd-snd"

#घोषणा BT_CVSD_TX_NREADY	BIT(21)
#घोषणा BT_CVSD_RX_READY	BIT(22)
#घोषणा BT_CVSD_TX_UNDERFLOW	BIT(23)
#घोषणा BT_CVSD_RX_OVERFLOW	BIT(24)
#घोषणा BT_CVSD_INTERRUPT	BIT(31)

#घोषणा BT_CVSD_CLEAR \
	(BT_CVSD_TX_NREADY | BT_CVSD_RX_READY | BT_CVSD_TX_UNDERFLOW |\
	 BT_CVSD_RX_OVERFLOW | BT_CVSD_INTERRUPT)

/* TX */
#घोषणा SCO_TX_ENCODE_SIZE (60)
/* 18 = 6 * 180 / SCO_TX_ENCODE_SIZE */
#घोषणा SCO_TX_PACKER_BUF_NUM (18)

/* RX */
#घोषणा SCO_RX_PLC_SIZE (30)
#घोषणा SCO_RX_PACKER_BUF_NUM (64)
#घोषणा SCO_RX_PACKET_MASK (0x3F)

#घोषणा SCO_CVSD_PACKET_VALID_SIZE 2

#घोषणा SCO_PACKET_120 120
#घोषणा SCO_PACKET_180 180

#घोषणा BTCVSD_RX_PACKET_SIZE (SCO_RX_PLC_SIZE + SCO_CVSD_PACKET_VALID_SIZE)
#घोषणा BTCVSD_TX_PACKET_SIZE (SCO_TX_ENCODE_SIZE)

#घोषणा BTCVSD_RX_BUF_SIZE (BTCVSD_RX_PACKET_SIZE * SCO_RX_PACKER_BUF_NUM)
#घोषणा BTCVSD_TX_BUF_SIZE (BTCVSD_TX_PACKET_SIZE * SCO_TX_PACKER_BUF_NUM)

क्रमागत bt_sco_state अणु
	BT_SCO_STATE_IDLE,
	BT_SCO_STATE_RUNNING,
	BT_SCO_STATE_ENDING,
	BT_SCO_STATE_LOOPBACK,
पूर्ण;

क्रमागत bt_sco_direct अणु
	BT_SCO_सूचीECT_BT2ARM,
	BT_SCO_सूचीECT_ARM2BT,
पूर्ण;

क्रमागत bt_sco_packet_len अणु
	BT_SCO_CVSD_30 = 0,
	BT_SCO_CVSD_60,
	BT_SCO_CVSD_90,
	BT_SCO_CVSD_120,
	BT_SCO_CVSD_10,
	BT_SCO_CVSD_20,
	BT_SCO_CVSD_MAX,
पूर्ण;

क्रमागत BT_SCO_BAND अणु
	BT_SCO_NB,
	BT_SCO_WB,
पूर्ण;

काष्ठा mtk_btcvsd_snd_hw_info अणु
	अचिन्हित पूर्णांक num_valid_addr;
	अचिन्हित दीर्घ bt_sram_addr[20];
	अचिन्हित पूर्णांक packet_length;
	अचिन्हित पूर्णांक packet_num;
पूर्ण;

काष्ठा mtk_btcvsd_snd_stream अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक stream;

	क्रमागत bt_sco_state state;

	अचिन्हित पूर्णांक packet_size;
	अचिन्हित पूर्णांक buf_size;
	u8 temp_packet_buf[SCO_PACKET_180];

	पूर्णांक packet_w;
	पूर्णांक packet_r;
	snd_pcm_uframes_t prev_frame;
	पूर्णांक prev_packet_idx;

	अचिन्हित पूर्णांक xrun:1;
	अचिन्हित पूर्णांक समयout:1;
	अचिन्हित पूर्णांक mute:1;
	अचिन्हित पूर्णांक trigger_start:1;
	अचिन्हित पूर्णांक रुको_flag:1;
	अचिन्हित पूर्णांक rw_cnt;

	अचिन्हित दीर्घ दीर्घ समय_stamp;
	अचिन्हित दीर्घ दीर्घ buf_data_equivalent_समय;

	काष्ठा mtk_btcvsd_snd_hw_info buffer_info;
पूर्ण;

काष्ठा mtk_btcvsd_snd अणु
	काष्ठा device *dev;
	पूर्णांक irq_id;

	काष्ठा regmap *infra;
	व्योम __iomem *bt_pkv_base;
	व्योम __iomem *bt_sram_bank2_base;

	अचिन्हित पूर्णांक infra_misc_offset;
	अचिन्हित पूर्णांक conn_bt_cvsd_mask;
	अचिन्हित पूर्णांक cvsd_mcu_पढ़ो_offset;
	अचिन्हित पूर्णांक cvsd_mcu_ग_लिखो_offset;
	अचिन्हित पूर्णांक cvsd_packet_indicator;

	u32 *bt_reg_pkt_r;
	u32 *bt_reg_pkt_w;
	u32 *bt_reg_ctl;

	अचिन्हित पूर्णांक irq_disabled:1;

	spinlock_t tx_lock;	/* spinlock क्रम bt tx stream control */
	spinlock_t rx_lock;	/* spinlock क्रम bt rx stream control */
	रुको_queue_head_t tx_रुको;
	रुको_queue_head_t rx_रुको;

	काष्ठा mtk_btcvsd_snd_stream *tx;
	काष्ठा mtk_btcvsd_snd_stream *rx;
	u8 tx_packet_buf[BTCVSD_TX_BUF_SIZE];
	u8 rx_packet_buf[BTCVSD_RX_BUF_SIZE];

	क्रमागत BT_SCO_BAND band;
पूर्ण;

काष्ठा mtk_btcvsd_snd_समय_buffer_info अणु
	अचिन्हित दीर्घ दीर्घ data_count_equi_समय;
	अचिन्हित दीर्घ दीर्घ समय_stamp_us;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक btsco_packet_valid_mask[BT_SCO_CVSD_MAX][6] = अणु
	अणु0x1, 0x1 << 1, 0x1 << 2, 0x1 << 3, 0x1 << 4, 0x1 << 5पूर्ण,
	अणु0x1, 0x1, 0x2, 0x2, 0x4, 0x4पूर्ण,
	अणु0x1, 0x1, 0x1, 0x2, 0x2, 0x2पूर्ण,
	अणु0x1, 0x1, 0x1, 0x1, 0x0, 0x0पूर्ण,
	अणु0x7, 0x7 << 3, 0x7 << 6, 0x7 << 9, 0x7 << 12, 0x7 << 15पूर्ण,
	अणु0x3, 0x3 << 1, 0x3 << 3, 0x3 << 4, 0x3 << 6, 0x3 << 7पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक btsco_packet_info[BT_SCO_CVSD_MAX][4] = अणु
	अणु30, 6, SCO_PACKET_180 / SCO_TX_ENCODE_SIZE,
	 SCO_PACKET_180 / SCO_RX_PLC_SIZEपूर्ण,
	अणु60, 3, SCO_PACKET_180 / SCO_TX_ENCODE_SIZE,
	 SCO_PACKET_180 / SCO_RX_PLC_SIZEपूर्ण,
	अणु90, 2, SCO_PACKET_180 / SCO_TX_ENCODE_SIZE,
	 SCO_PACKET_180 / SCO_RX_PLC_SIZEपूर्ण,
	अणु120, 1, SCO_PACKET_120 / SCO_TX_ENCODE_SIZE,
	 SCO_PACKET_120 / SCO_RX_PLC_SIZEपूर्ण,
	अणु10, 18, SCO_PACKET_180 / SCO_TX_ENCODE_SIZE,
	 SCO_PACKET_180 / SCO_RX_PLC_SIZEपूर्ण,
	अणु20, 9, SCO_PACKET_180 / SCO_TX_ENCODE_SIZE,
	 SCO_PACKET_180 / SCO_RX_PLC_SIZEपूर्ण,
पूर्ण;

अटल स्थिर u8 table_msbc_silence[SCO_PACKET_180] = अणु
	0x01, 0x38, 0xad, 0x00, 0x00, 0xc5, 0x00, 0x00, 0x00, 0x00,
	0x77, 0x6d, 0xb6, 0xdd, 0xdb, 0x6d, 0xb7, 0x76, 0xdb, 0x6d,
	0xdd, 0xb6, 0xdb, 0x77, 0x6d, 0xb6, 0xdd, 0xdb, 0x6d, 0xb7,
	0x76, 0xdb, 0x6d, 0xdd, 0xb6, 0xdb, 0x77, 0x6d, 0xb6, 0xdd,
	0xdb, 0x6d, 0xb7, 0x76, 0xdb, 0x6d, 0xdd, 0xb6, 0xdb, 0x77,
	0x6d, 0xb6, 0xdd, 0xdb, 0x6d, 0xb7, 0x76, 0xdb, 0x6c, 0x00,
	0x01, 0xc8, 0xad, 0x00, 0x00, 0xc5, 0x00, 0x00, 0x00, 0x00,
	0x77, 0x6d, 0xb6, 0xdd, 0xdb, 0x6d, 0xb7, 0x76, 0xdb, 0x6d,
	0xdd, 0xb6, 0xdb, 0x77, 0x6d, 0xb6, 0xdd, 0xdb, 0x6d, 0xb7,
	0x76, 0xdb, 0x6d, 0xdd, 0xb6, 0xdb, 0x77, 0x6d, 0xb6, 0xdd,
	0xdb, 0x6d, 0xb7, 0x76, 0xdb, 0x6d, 0xdd, 0xb6, 0xdb, 0x77,
	0x6d, 0xb6, 0xdd, 0xdb, 0x6d, 0xb7, 0x76, 0xdb, 0x6c, 0x00,
	0x01, 0xf8, 0xad, 0x00, 0x00, 0xc5, 0x00, 0x00, 0x00, 0x00,
	0x77, 0x6d, 0xb6, 0xdd, 0xdb, 0x6d, 0xb7, 0x76, 0xdb, 0x6d,
	0xdd, 0xb6, 0xdb, 0x77, 0x6d, 0xb6, 0xdd, 0xdb, 0x6d, 0xb7,
	0x76, 0xdb, 0x6d, 0xdd, 0xb6, 0xdb, 0x77, 0x6d, 0xb6, 0xdd,
	0xdb, 0x6d, 0xb7, 0x76, 0xdb, 0x6d, 0xdd, 0xb6, 0xdb, 0x77,
	0x6d, 0xb6, 0xdd, 0xdb, 0x6d, 0xb7, 0x76, 0xdb, 0x6c, 0x00
पूर्ण;

अटल व्योम mtk_btcvsd_snd_irq_enable(काष्ठा mtk_btcvsd_snd *bt)
अणु
	regmap_update_bits(bt->infra, bt->infra_misc_offset,
			   bt->conn_bt_cvsd_mask, 0);
पूर्ण

अटल व्योम mtk_btcvsd_snd_irq_disable(काष्ठा mtk_btcvsd_snd *bt)
अणु
	regmap_update_bits(bt->infra, bt->infra_misc_offset,
			   bt->conn_bt_cvsd_mask, bt->conn_bt_cvsd_mask);
पूर्ण

अटल व्योम mtk_btcvsd_snd_set_state(काष्ठा mtk_btcvsd_snd *bt,
				     काष्ठा mtk_btcvsd_snd_stream *bt_stream,
				     पूर्णांक state)
अणु
	dev_dbg(bt->dev, "%s(), stream %d, state %d, tx->state %d, rx->state %d, irq_disabled %d\n",
		__func__,
		bt_stream->stream, state,
		bt->tx->state, bt->rx->state, bt->irq_disabled);

	bt_stream->state = state;

	अगर (bt->tx->state == BT_SCO_STATE_IDLE &&
	    bt->rx->state == BT_SCO_STATE_IDLE) अणु
		अगर (!bt->irq_disabled) अणु
			disable_irq(bt->irq_id);
			mtk_btcvsd_snd_irq_disable(bt);
			bt->irq_disabled = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bt->irq_disabled) अणु
			enable_irq(bt->irq_id);
			mtk_btcvsd_snd_irq_enable(bt);
			bt->irq_disabled = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_btcvsd_snd_tx_init(काष्ठा mtk_btcvsd_snd *bt)
अणु
	स_रखो(bt->tx, 0, माप(*bt->tx));
	स_रखो(bt->tx_packet_buf, 0, माप(bt->tx_packet_buf));

	bt->tx->packet_size = BTCVSD_TX_PACKET_SIZE;
	bt->tx->buf_size = BTCVSD_TX_BUF_SIZE;
	bt->tx->समयout = 0;
	bt->tx->rw_cnt = 0;
	bt->tx->stream = SNDRV_PCM_STREAM_PLAYBACK;
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_btcvsd_snd_rx_init(काष्ठा mtk_btcvsd_snd *bt)
अणु
	स_रखो(bt->rx, 0, माप(*bt->rx));
	स_रखो(bt->rx_packet_buf, 0, माप(bt->rx_packet_buf));

	bt->rx->packet_size = BTCVSD_RX_PACKET_SIZE;
	bt->rx->buf_size = BTCVSD_RX_BUF_SIZE;
	bt->rx->समयout = 0;
	bt->rx->rw_cnt = 0;
	bt->rx->stream = SNDRV_PCM_STREAM_CAPTURE;
	वापस 0;
पूर्ण

अटल व्योम get_tx_समय_stamp(काष्ठा mtk_btcvsd_snd *bt,
			      काष्ठा mtk_btcvsd_snd_समय_buffer_info *ts)
अणु
	ts->समय_stamp_us = bt->tx->समय_stamp;
	ts->data_count_equi_समय = bt->tx->buf_data_equivalent_समय;
पूर्ण

अटल व्योम get_rx_समय_stamp(काष्ठा mtk_btcvsd_snd *bt,
			      काष्ठा mtk_btcvsd_snd_समय_buffer_info *ts)
अणु
	ts->समय_stamp_us = bt->rx->समय_stamp;
	ts->data_count_equi_समय = bt->rx->buf_data_equivalent_समय;
पूर्ण

अटल पूर्णांक btcvsd_bytes_to_frame(काष्ठा snd_pcm_substream *substream,
				 पूर्णांक bytes)
अणु
	पूर्णांक count = bytes;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (runसमय->क्रमmat == SNDRV_PCM_FORMAT_S32_LE ||
	    runसमय->क्रमmat == SNDRV_PCM_FORMAT_U32_LE)
		count = count >> 2;
	अन्यथा
		count = count >> 1;

	count = count / runसमय->channels;
	वापस count;
पूर्ण

अटल व्योम mtk_btcvsd_snd_data_transfer(क्रमागत bt_sco_direct dir,
					 u8 *src, u8 *dst,
					 अचिन्हित पूर्णांक blk_size,
					 अचिन्हित पूर्णांक blk_num)
अणु
	अचिन्हित पूर्णांक i, j;

	अगर (blk_size == 60 || blk_size == 120 || blk_size == 20) अणु
		u32 *src_32 = (u32 *)src;
		u32 *dst_32 = (u32 *)dst;

		क्रम (i = 0; i < (blk_size * blk_num / 4); i++)
			*dst_32++ = *src_32++;
	पूर्ण अन्यथा अणु
		u16 *src_16 = (u16 *)src;
		u16 *dst_16 = (u16 *)dst;

		क्रम (j = 0; j < blk_num; j++) अणु
			क्रम (i = 0; i < (blk_size / 2); i++)
				*dst_16++ = *src_16++;

			अगर (dir == BT_SCO_सूचीECT_BT2ARM)
				src_16++;
			अन्यथा
				dst_16++;
		पूर्ण
	पूर्ण
पूर्ण

/* ग_लिखो encoded mute data to bt sram */
अटल पूर्णांक btcvsd_tx_clean_buffer(काष्ठा mtk_btcvsd_snd *bt)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक num_valid_addr;
	अचिन्हित दीर्घ flags;
	क्रमागत BT_SCO_BAND band = bt->band;

	/* prepare encoded mute data */
	अगर (band == BT_SCO_NB)
		स_रखो(bt->tx->temp_packet_buf, 170, SCO_PACKET_180);
	अन्यथा
		स_नकल(bt->tx->temp_packet_buf,
		       table_msbc_silence, SCO_PACKET_180);

	/* ग_लिखो mute data to bt tx sram buffer */
	spin_lock_irqsave(&bt->tx_lock, flags);
	num_valid_addr = bt->tx->buffer_info.num_valid_addr;

	dev_info(bt->dev, "%s(), band %d, num_valid_addr %u\n",
		 __func__, band, num_valid_addr);

	क्रम (i = 0; i < num_valid_addr; i++) अणु
		व्योम *dst;

		dev_info(bt->dev, "%s(), clean addr 0x%lx\n", __func__,
			 bt->tx->buffer_info.bt_sram_addr[i]);

		dst = (व्योम *)bt->tx->buffer_info.bt_sram_addr[i];

		mtk_btcvsd_snd_data_transfer(BT_SCO_सूचीECT_ARM2BT,
					     bt->tx->temp_packet_buf, dst,
					     bt->tx->buffer_info.packet_length,
					     bt->tx->buffer_info.packet_num);
	पूर्ण
	spin_unlock_irqrestore(&bt->tx_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_btcvsd_पढ़ो_from_bt(काष्ठा mtk_btcvsd_snd *bt,
				   क्रमागत bt_sco_packet_len packet_type,
				   अचिन्हित पूर्णांक packet_length,
				   अचिन्हित पूर्णांक packet_num,
				   अचिन्हित पूर्णांक blk_size,
				   अचिन्हित पूर्णांक control)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक pv;
	u8 *src;
	अचिन्हित पूर्णांक packet_buf_ofs;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ connsys_addr_rx, ap_addr_rx;

	connsys_addr_rx = *bt->bt_reg_pkt_r;
	ap_addr_rx = (अचिन्हित दीर्घ)bt->bt_sram_bank2_base +
		     (connsys_addr_rx & 0xFFFF);

	अगर (connsys_addr_rx == 0xdeadfeed) अणु
		/* bt वापस 0xdeadfeed अगर पढ़ो रेजिस्टर during bt sleep */
		dev_warn(bt->dev, "%s(), connsys_addr_rx == 0xdeadfeed",
			 __func__);
		वापस -EIO;
	पूर्ण

	src = (u8 *)ap_addr_rx;

	mtk_btcvsd_snd_data_transfer(BT_SCO_सूचीECT_BT2ARM, src,
				     bt->rx->temp_packet_buf, packet_length,
				     packet_num);

	spin_lock_irqsave(&bt->rx_lock, flags);
	क्रम (i = 0; i < blk_size; i++) अणु
		packet_buf_ofs = (bt->rx->packet_w & SCO_RX_PACKET_MASK) *
				 bt->rx->packet_size;
		स_नकल(bt->rx_packet_buf + packet_buf_ofs,
		       bt->rx->temp_packet_buf + (SCO_RX_PLC_SIZE * i),
		       SCO_RX_PLC_SIZE);
		अगर ((control & btsco_packet_valid_mask[packet_type][i]) ==
		    btsco_packet_valid_mask[packet_type][i])
			pv = 1;
		अन्यथा
			pv = 0;

		packet_buf_ofs += SCO_RX_PLC_SIZE;
		स_नकल(bt->rx_packet_buf + packet_buf_ofs, (व्योम *)&pv,
		       SCO_CVSD_PACKET_VALID_SIZE);
		bt->rx->packet_w++;
	पूर्ण
	spin_unlock_irqrestore(&bt->rx_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_btcvsd_ग_लिखो_to_bt(काष्ठा mtk_btcvsd_snd *bt,
				  क्रमागत bt_sco_packet_len packet_type,
				  अचिन्हित पूर्णांक packet_length,
				  अचिन्हित पूर्णांक packet_num,
				  अचिन्हित पूर्णांक blk_size)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;
	u8 *dst;
	अचिन्हित दीर्घ connsys_addr_tx, ap_addr_tx;
	bool new_ap_addr_tx = true;

	connsys_addr_tx = *bt->bt_reg_pkt_w;
	ap_addr_tx = (अचिन्हित दीर्घ)bt->bt_sram_bank2_base +
		     (connsys_addr_tx & 0xFFFF);

	अगर (connsys_addr_tx == 0xdeadfeed) अणु
		/* bt वापस 0xdeadfeed अगर पढ़ो रेजिस्टर during bt sleep */
		dev_warn(bt->dev, "%s(), connsys_addr_tx == 0xdeadfeed\n",
			 __func__);
		वापस -EIO;
	पूर्ण

	spin_lock_irqsave(&bt->tx_lock, flags);
	क्रम (i = 0; i < blk_size; i++) अणु
		स_नकल(bt->tx->temp_packet_buf + (bt->tx->packet_size * i),
		       (bt->tx_packet_buf +
			(bt->tx->packet_r % SCO_TX_PACKER_BUF_NUM) *
			bt->tx->packet_size),
		       bt->tx->packet_size);

		bt->tx->packet_r++;
	पूर्ण
	spin_unlock_irqrestore(&bt->tx_lock, flags);

	dst = (u8 *)ap_addr_tx;

	अगर (!bt->tx->mute) अणु
		mtk_btcvsd_snd_data_transfer(BT_SCO_सूचीECT_ARM2BT,
					     bt->tx->temp_packet_buf, dst,
					     packet_length, packet_num);
	पूर्ण

	/* store bt tx buffer sram info */
	bt->tx->buffer_info.packet_length = packet_length;
	bt->tx->buffer_info.packet_num = packet_num;
	क्रम (i = 0; i < bt->tx->buffer_info.num_valid_addr; i++) अणु
		अगर (bt->tx->buffer_info.bt_sram_addr[i] == ap_addr_tx) अणु
			new_ap_addr_tx = false;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (new_ap_addr_tx) अणु
		अचिन्हित पूर्णांक next_idx;

		spin_lock_irqsave(&bt->tx_lock, flags);
		bt->tx->buffer_info.num_valid_addr++;
		next_idx = bt->tx->buffer_info.num_valid_addr - 1;
		bt->tx->buffer_info.bt_sram_addr[next_idx] = ap_addr_tx;
		spin_unlock_irqrestore(&bt->tx_lock, flags);
		dev_info(bt->dev, "%s(), new ap_addr_tx = 0x%lx, num_valid_addr %d\n",
			 __func__, ap_addr_tx,
			 bt->tx->buffer_info.num_valid_addr);
	पूर्ण

	अगर (bt->tx->mute)
		btcvsd_tx_clean_buffer(bt);

	वापस 0;
पूर्ण

अटल irqवापस_t mtk_btcvsd_snd_irq_handler(पूर्णांक irq_id, व्योम *dev)
अणु
	काष्ठा mtk_btcvsd_snd *bt = dev;
	अचिन्हित पूर्णांक packet_type, packet_num, packet_length;
	अचिन्हित पूर्णांक buf_cnt_tx, buf_cnt_rx, control;

	अगर (bt->rx->state != BT_SCO_STATE_RUNNING &&
	    bt->rx->state != BT_SCO_STATE_ENDING &&
	    bt->tx->state != BT_SCO_STATE_RUNNING &&
	    bt->tx->state != BT_SCO_STATE_ENDING &&
	    bt->tx->state != BT_SCO_STATE_LOOPBACK) अणु
		dev_warn(bt->dev, "%s(), in idle state: rx->state: %d, tx->state: %d\n",
			 __func__, bt->rx->state, bt->tx->state);
		जाओ irq_handler_निकास;
	पूर्ण

	control = *bt->bt_reg_ctl;
	packet_type = (control >> 18) & 0x7;

	अगर (((control >> 31) & 1) == 0) अणु
		dev_warn(bt->dev, "%s(), ((control >> 31) & 1) == 0, control 0x%x\n",
			 __func__, control);
		जाओ irq_handler_निकास;
	पूर्ण

	अगर (packet_type >= BT_SCO_CVSD_MAX) अणु
		dev_warn(bt->dev, "%s(), invalid packet_type %u, exit\n",
			 __func__, packet_type);
		जाओ irq_handler_निकास;
	पूर्ण

	packet_length = btsco_packet_info[packet_type][0];
	packet_num = btsco_packet_info[packet_type][1];
	buf_cnt_tx = btsco_packet_info[packet_type][2];
	buf_cnt_rx = btsco_packet_info[packet_type][3];

	अगर (bt->tx->state == BT_SCO_STATE_LOOPBACK) अणु
		u8 *src, *dst;
		अचिन्हित दीर्घ connsys_addr_rx, ap_addr_rx;
		अचिन्हित दीर्घ connsys_addr_tx, ap_addr_tx;

		connsys_addr_rx = *bt->bt_reg_pkt_r;
		ap_addr_rx = (अचिन्हित दीर्घ)bt->bt_sram_bank2_base +
			     (connsys_addr_rx & 0xFFFF);

		connsys_addr_tx = *bt->bt_reg_pkt_w;
		ap_addr_tx = (अचिन्हित दीर्घ)bt->bt_sram_bank2_base +
			     (connsys_addr_tx & 0xFFFF);

		अगर (connsys_addr_tx == 0xdeadfeed ||
		    connsys_addr_rx == 0xdeadfeed) अणु
			/* bt वापस 0xdeadfeed अगर पढ़ो reg during bt sleep */
			dev_warn(bt->dev, "%s(), connsys_addr_tx == 0xdeadfeed\n",
				 __func__);
			जाओ irq_handler_निकास;
		पूर्ण

		src = (u8 *)ap_addr_rx;
		dst = (u8 *)ap_addr_tx;

		mtk_btcvsd_snd_data_transfer(BT_SCO_सूचीECT_BT2ARM, src,
					     bt->tx->temp_packet_buf,
					     packet_length,
					     packet_num);
		mtk_btcvsd_snd_data_transfer(BT_SCO_सूचीECT_ARM2BT,
					     bt->tx->temp_packet_buf, dst,
					     packet_length,
					     packet_num);
		bt->rx->rw_cnt++;
		bt->tx->rw_cnt++;
	पूर्ण

	अगर (bt->rx->state == BT_SCO_STATE_RUNNING ||
	    bt->rx->state == BT_SCO_STATE_ENDING) अणु
		अगर (bt->rx->xrun) अणु
			अगर (bt->rx->packet_w - bt->rx->packet_r <=
			    SCO_RX_PACKER_BUF_NUM - 2 * buf_cnt_rx) अणु
				/*
				 * मुक्त space is larger then
				 * twice पूर्णांकerrupt rx data size
				 */
				bt->rx->xrun = 0;
				dev_warn(bt->dev, "%s(), rx->xrun 0!\n",
					 __func__);
			पूर्ण
		पूर्ण

		अगर (!bt->rx->xrun &&
		    (bt->rx->packet_w - bt->rx->packet_r <=
		     SCO_RX_PACKER_BUF_NUM - buf_cnt_rx)) अणु
			mtk_btcvsd_पढ़ो_from_bt(bt,
						packet_type,
						packet_length,
						packet_num,
						buf_cnt_rx,
						control);
			bt->rx->rw_cnt++;
		पूर्ण अन्यथा अणु
			bt->rx->xrun = 1;
			dev_warn(bt->dev, "%s(), rx->xrun 1\n", __func__);
		पूर्ण
	पूर्ण

	/* tx */
	bt->tx->समयout = 0;
	अगर ((bt->tx->state == BT_SCO_STATE_RUNNING ||
	     bt->tx->state == BT_SCO_STATE_ENDING) &&
	    bt->tx->trigger_start) अणु
		अगर (bt->tx->xrun) अणु
			/* prepared data is larger then twice
			 * पूर्णांकerrupt tx data size
			 */
			अगर (bt->tx->packet_w - bt->tx->packet_r >=
			    2 * buf_cnt_tx) अणु
				bt->tx->xrun = 0;
				dev_warn(bt->dev, "%s(), tx->xrun 0\n",
					 __func__);
			पूर्ण
		पूर्ण

		अगर ((!bt->tx->xrun &&
		     (bt->tx->packet_w - bt->tx->packet_r >= buf_cnt_tx)) ||
		    bt->tx->state == BT_SCO_STATE_ENDING) अणु
			mtk_btcvsd_ग_लिखो_to_bt(bt,
					       packet_type,
					       packet_length,
					       packet_num,
					       buf_cnt_tx);
			bt->tx->rw_cnt++;
		पूर्ण अन्यथा अणु
			bt->tx->xrun = 1;
			dev_warn(bt->dev, "%s(), tx->xrun 1\n", __func__);
		पूर्ण
	पूर्ण

	*bt->bt_reg_ctl &= ~BT_CVSD_CLEAR;

	अगर (bt->rx->state == BT_SCO_STATE_RUNNING ||
	    bt->rx->state == BT_SCO_STATE_ENDING) अणु
		bt->rx->रुको_flag = 1;
		wake_up_पूर्णांकerruptible(&bt->rx_रुको);
		snd_pcm_period_elapsed(bt->rx->substream);
	पूर्ण
	अगर (bt->tx->state == BT_SCO_STATE_RUNNING ||
	    bt->tx->state == BT_SCO_STATE_ENDING) अणु
		bt->tx->रुको_flag = 1;
		wake_up_पूर्णांकerruptible(&bt->tx_रुको);
		snd_pcm_period_elapsed(bt->tx->substream);
	पूर्ण

	वापस IRQ_HANDLED;
irq_handler_निकास:
	*bt->bt_reg_ctl &= ~BT_CVSD_CLEAR;
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक रुको_क्रम_bt_irq(काष्ठा mtk_btcvsd_snd *bt,
			   काष्ठा mtk_btcvsd_snd_stream *bt_stream)
अणु
	अचिन्हित दीर्घ दीर्घ t1, t2;
	/* one पूर्णांकerrupt period = 22.5ms */
	अचिन्हित दीर्घ दीर्घ समयout_limit = 22500000;
	पूर्णांक max_समयout_trial = 2;
	पूर्णांक ret;

	bt_stream->रुको_flag = 0;

	जबतक (max_समयout_trial && !bt_stream->रुको_flag) अणु
		t1 = sched_घड़ी();
		अगर (bt_stream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			ret = रुको_event_पूर्णांकerruptible_समयout(bt->tx_रुको,
				bt_stream->रुको_flag,
				nsecs_to_jअगरfies(समयout_limit));
		पूर्ण अन्यथा अणु
			ret = रुको_event_पूर्णांकerruptible_समयout(bt->rx_रुको,
				bt_stream->रुको_flag,
				nsecs_to_jअगरfies(समयout_limit));
		पूर्ण

		t2 = sched_घड़ी();
		t2 = t2 - t1; /* in ns (10^9) */

		अगर (t2 > समयout_limit) अणु
			dev_warn(bt->dev, "%s(), stream %d, timeout %llu, limit %llu, ret %d, flag %d\n",
				 __func__, bt_stream->stream,
				 t2, समयout_limit, ret,
				 bt_stream->रुको_flag);
		पूर्ण

		अगर (ret < 0) अणु
			/*
			 * error, -ERESTARTSYS अगर it was पूर्णांकerrupted by
			 * a संकेत
			 */
			dev_warn(bt->dev, "%s(), stream %d, error, trial left %d\n",
				 __func__,
				 bt_stream->stream, max_समयout_trial);

			bt_stream->समयout = 1;
			वापस ret;
		पूर्ण अन्यथा अगर (ret == 0) अणु
			/* conidtion is false after समयout */
			max_समयout_trial--;
			dev_warn(bt->dev, "%s(), stream %d, error, timeout, condition is false, trial left %d\n",
				 __func__,
				 bt_stream->stream, max_समयout_trial);

			अगर (max_समयout_trial <= 0) अणु
				bt_stream->समयout = 1;
				वापस -ETIME;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mtk_btcvsd_snd_पढ़ो(काष्ठा mtk_btcvsd_snd *bt,
				   अक्षर __user *buf,
				   माप_प्रकार count)
अणु
	sमाप_प्रकार पढ़ो_size = 0, पढ़ो_count = 0, cur_पढ़ो_idx, cont;
	अचिन्हित पूर्णांक cur_buf_ofs = 0;
	अचिन्हित दीर्घ avail;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक packet_size = bt->rx->packet_size;

	जबतक (count) अणु
		spin_lock_irqsave(&bt->rx_lock, flags);
		/* available data in RX packet buffer */
		avail = (bt->rx->packet_w - bt->rx->packet_r) * packet_size;

		cur_पढ़ो_idx = (bt->rx->packet_r & SCO_RX_PACKET_MASK) *
			       packet_size;
		spin_unlock_irqrestore(&bt->rx_lock, flags);

		अगर (!avail) अणु
			पूर्णांक ret = रुको_क्रम_bt_irq(bt, bt->rx);

			अगर (ret)
				वापस पढ़ो_count;

			जारी;
		पूर्ण

		/* count must be multiple of packet_size */
		अगर (count % packet_size != 0 ||
		    avail % packet_size != 0) अणु
			dev_warn(bt->dev, "%s(), count %zu or d %lu is not multiple of packet_size %dd\n",
				 __func__, count, avail, packet_size);

			count -= count % packet_size;
			avail -= avail % packet_size;
		पूर्ण

		अगर (count > avail)
			पढ़ो_size = avail;
		अन्यथा
			पढ़ो_size = count;

		/* calculate जारी space */
		cont = bt->rx->buf_size - cur_पढ़ो_idx;
		अगर (पढ़ो_size > cont)
			पढ़ो_size = cont;

		अगर (copy_to_user(buf + cur_buf_ofs,
				 bt->rx_packet_buf + cur_पढ़ो_idx,
				 पढ़ो_size)) अणु
			dev_warn(bt->dev, "%s(), copy_to_user fail\n",
				 __func__);
			वापस -EFAULT;
		पूर्ण

		spin_lock_irqsave(&bt->rx_lock, flags);
		bt->rx->packet_r += पढ़ो_size / packet_size;
		spin_unlock_irqrestore(&bt->rx_lock, flags);

		पढ़ो_count += पढ़ो_size;
		cur_buf_ofs += पढ़ो_size;
		count -= पढ़ो_size;
	पूर्ण

	/*
	 * save current बारtamp & buffer समय in बार_tamp and
	 * buf_data_equivalent_समय
	 */
	bt->rx->समय_stamp = sched_घड़ी();
	bt->rx->buf_data_equivalent_समय =
		(अचिन्हित दीर्घ दीर्घ)(bt->rx->packet_w - bt->rx->packet_r) *
		SCO_RX_PLC_SIZE * 16 * 1000 / 2 / 64;
	bt->rx->buf_data_equivalent_समय += पढ़ो_count * SCO_RX_PLC_SIZE *
					    16 * 1000 / packet_size / 2 / 64;
	/* वापस equivalent समय(us) to data count */
	bt->rx->buf_data_equivalent_समय *= 1000;

	वापस पढ़ो_count;
पूर्ण

अटल sमाप_प्रकार mtk_btcvsd_snd_ग_लिखो(काष्ठा mtk_btcvsd_snd *bt,
				    अक्षर __user *buf,
				    माप_प्रकार count)
अणु
	पूर्णांक written_size = count, avail, cur_ग_लिखो_idx, ग_लिखो_size, cont;
	अचिन्हित पूर्णांक cur_buf_ofs = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक packet_size = bt->tx->packet_size;

	/*
	 * save current बारtamp & buffer समय in समय_stamp and
	 * buf_data_equivalent_समय
	 */
	bt->tx->समय_stamp = sched_घड़ी();
	bt->tx->buf_data_equivalent_समय =
		(अचिन्हित दीर्घ दीर्घ)(bt->tx->packet_w - bt->tx->packet_r) *
		packet_size * 16 * 1000 / 2 / 64;

	/* वापस equivalent समय(us) to data count */
	bt->tx->buf_data_equivalent_समय *= 1000;

	जबतक (count) अणु
		spin_lock_irqsave(&bt->tx_lock, flags);
		/* मुक्त space of TX packet buffer */
		avail = bt->tx->buf_size -
			(bt->tx->packet_w - bt->tx->packet_r) * packet_size;

		cur_ग_लिखो_idx = (bt->tx->packet_w % SCO_TX_PACKER_BUF_NUM) *
				packet_size;
		spin_unlock_irqrestore(&bt->tx_lock, flags);

		अगर (!avail) अणु
			पूर्णांक ret = रुको_क्रम_bt_irq(bt, bt->tx);

			अगर (ret)
				वापस written_size;

			जारी;
		पूर्ण

		/* count must be multiple of bt->tx->packet_size */
		अगर (count % packet_size != 0 ||
		    avail % packet_size != 0) अणु
			dev_warn(bt->dev, "%s(), count %zu or avail %d is not multiple of packet_size %d\n",
				 __func__, count, avail, packet_size);
			count -= count % packet_size;
			avail -= avail % packet_size;
		पूर्ण

		अगर (count > avail)
			ग_लिखो_size = avail;
		अन्यथा
			ग_लिखो_size = count;

		/* calculate जारी space */
		cont = bt->tx->buf_size - cur_ग_लिखो_idx;
		अगर (ग_लिखो_size > cont)
			ग_लिखो_size = cont;

		अगर (copy_from_user(bt->tx_packet_buf +
				   cur_ग_लिखो_idx,
				   buf + cur_buf_ofs,
				   ग_लिखो_size)) अणु
			dev_warn(bt->dev, "%s(), copy_from_user fail\n",
				 __func__);
			वापस -EFAULT;
		पूर्ण

		spin_lock_irqsave(&bt->tx_lock, flags);
		bt->tx->packet_w += ग_लिखो_size / packet_size;
		spin_unlock_irqrestore(&bt->tx_lock, flags);
		cur_buf_ofs += ग_लिखो_size;
		count -= ग_लिखो_size;
	पूर्ण

	वापस written_size;
पूर्ण

अटल काष्ठा mtk_btcvsd_snd_stream *get_bt_stream
	(काष्ठा mtk_btcvsd_snd *bt, काष्ठा snd_pcm_substream *substream)
अणु
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस bt->tx;
	अन्यथा
		वापस bt->rx;
पूर्ण

/* pcm ops */
अटल स्थिर काष्ठा snd_pcm_hardware mtk_btcvsd_hardware = अणु
	.info = (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_RESUME),
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.buffer_bytes_max = 24 * 1024,
	.period_bytes_max = 24 * 1024,
	.periods_min = 2,
	.periods_max = 16,
	.fअगरo_size = 0,
पूर्ण;

अटल पूर्णांक mtk_pcm_btcvsd_खोलो(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	dev_dbg(bt->dev, "%s(), stream %d, substream %p\n",
		__func__, substream->stream, substream);

	snd_soc_set_runसमय_hwparams(substream, &mtk_btcvsd_hardware);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ret = mtk_btcvsd_snd_tx_init(bt);
		bt->tx->substream = substream;
	पूर्ण अन्यथा अणु
		ret = mtk_btcvsd_snd_rx_init(bt);
		bt->rx->substream = substream;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_pcm_btcvsd_बंद(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(component);
	काष्ठा mtk_btcvsd_snd_stream *bt_stream = get_bt_stream(bt, substream);

	dev_dbg(bt->dev, "%s(), stream %d\n", __func__, substream->stream);

	mtk_btcvsd_snd_set_state(bt, bt_stream, BT_SCO_STATE_IDLE);
	bt_stream->substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pcm_btcvsd_hw_params(काष्ठा snd_soc_component *component,
				    काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(component);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
	    params_buffer_bytes(hw_params) % bt->tx->packet_size != 0) अणु
		dev_warn(bt->dev, "%s(), error, buffer size %d not valid\n",
			 __func__,
			 params_buffer_bytes(hw_params));
		वापस -EINVAL;
	पूर्ण

	substream->runसमय->dma_bytes = params_buffer_bytes(hw_params);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pcm_btcvsd_hw_मुक्त(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(component);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		btcvsd_tx_clean_buffer(bt);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pcm_btcvsd_prepare(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(component);
	काष्ठा mtk_btcvsd_snd_stream *bt_stream = get_bt_stream(bt, substream);

	dev_dbg(bt->dev, "%s(), stream %d\n", __func__, substream->stream);

	mtk_btcvsd_snd_set_state(bt, bt_stream, BT_SCO_STATE_RUNNING);
	वापस 0;
पूर्ण

अटल पूर्णांक mtk_pcm_btcvsd_trigger(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(component);
	काष्ठा mtk_btcvsd_snd_stream *bt_stream = get_bt_stream(bt, substream);
	पूर्णांक stream = substream->stream;
	पूर्णांक hw_packet_ptr;

	dev_dbg(bt->dev, "%s(), stream %d, cmd %d\n",
		__func__, substream->stream, cmd);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		hw_packet_ptr = stream == SNDRV_PCM_STREAM_PLAYBACK ?
				bt_stream->packet_r : bt_stream->packet_w;
		bt_stream->prev_packet_idx = hw_packet_ptr;
		bt_stream->prev_frame = 0;
		bt_stream->trigger_start = 1;
		वापस 0;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		bt_stream->trigger_start = 0;
		mtk_btcvsd_snd_set_state(bt, bt_stream, BT_SCO_STATE_ENDING);
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल snd_pcm_uframes_t mtk_pcm_btcvsd_poपूर्णांकer(
	काष्ठा snd_soc_component *component,
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(component);
	काष्ठा mtk_btcvsd_snd_stream *bt_stream;
	snd_pcm_uframes_t frame = 0;
	पूर्णांक byte = 0;
	पूर्णांक hw_packet_ptr;
	पूर्णांक packet_dअगरf;
	spinlock_t *lock;	/* spinlock क्रम bt stream control */
	अचिन्हित दीर्घ flags;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		lock = &bt->tx_lock;
		bt_stream = bt->tx;
	पूर्ण अन्यथा अणु
		lock = &bt->rx_lock;
		bt_stream = bt->rx;
	पूर्ण

	spin_lock_irqsave(lock, flags);
	hw_packet_ptr = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ?
			bt->tx->packet_r : bt->rx->packet_w;

	/* get packet dअगरf from last समय */
	अगर (hw_packet_ptr >= bt_stream->prev_packet_idx) अणु
		packet_dअगरf = hw_packet_ptr - bt_stream->prev_packet_idx;
	पूर्ण अन्यथा अणु
		/* पूर्णांकeger overflow */
		packet_dअगरf = (पूर्णांक_उच्च - bt_stream->prev_packet_idx) +
			      (hw_packet_ptr - पूर्णांक_न्यून) + 1;
	पूर्ण
	bt_stream->prev_packet_idx = hw_packet_ptr;

	/* increased bytes */
	byte = packet_dअगरf * bt_stream->packet_size;

	frame = btcvsd_bytes_to_frame(substream, byte);
	frame += bt_stream->prev_frame;
	frame %= substream->runसमय->buffer_size;

	bt_stream->prev_frame = frame;

	spin_unlock_irqrestore(lock, flags);

	वापस frame;
पूर्ण

अटल पूर्णांक mtk_pcm_btcvsd_copy(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream,
			       पूर्णांक channel, अचिन्हित दीर्घ pos,
			       व्योम __user *buf, अचिन्हित दीर्घ count)
अणु
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(component);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		mtk_btcvsd_snd_ग_लिखो(bt, buf, count);
	अन्यथा
		mtk_btcvsd_snd_पढ़ो(bt, buf, count);

	वापस 0;
पूर्ण

/* kcontrol */
अटल स्थिर अक्षर *स्थिर btsco_band_str[] = अणु"NB", "WB"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत btcvsd_क्रमागत[] = अणु
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(btsco_band_str), btsco_band_str),
पूर्ण;

अटल पूर्णांक btcvsd_band_get(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);

	ucontrol->value.पूर्णांकeger.value[0] = bt->band;
	वापस 0;
पूर्ण

अटल पूर्णांक btcvsd_band_set(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;

	अगर (ucontrol->value.क्रमागतerated.item[0] >= e->items)
		वापस -EINVAL;

	bt->band = ucontrol->value.पूर्णांकeger.value[0];
	dev_dbg(bt->dev, "%s(), band %d\n", __func__, bt->band);
	वापस 0;
पूर्ण

अटल पूर्णांक btcvsd_loopback_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);
	bool lpbk_en = bt->tx->state == BT_SCO_STATE_LOOPBACK;

	ucontrol->value.पूर्णांकeger.value[0] = lpbk_en;
	वापस 0;
पूर्ण

अटल पूर्णांक btcvsd_loopback_set(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);

	अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
		mtk_btcvsd_snd_set_state(bt, bt->tx, BT_SCO_STATE_LOOPBACK);
		mtk_btcvsd_snd_set_state(bt, bt->rx, BT_SCO_STATE_LOOPBACK);
	पूर्ण अन्यथा अणु
		mtk_btcvsd_snd_set_state(bt, bt->tx, BT_SCO_STATE_RUNNING);
		mtk_btcvsd_snd_set_state(bt, bt->rx, BT_SCO_STATE_RUNNING);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक btcvsd_tx_mute_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);

	अगर (!bt->tx) अणु
		ucontrol->value.पूर्णांकeger.value[0] = 0;
		वापस 0;
	पूर्ण

	ucontrol->value.पूर्णांकeger.value[0] = bt->tx->mute;
	वापस 0;
पूर्ण

अटल पूर्णांक btcvsd_tx_mute_set(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);

	अगर (!bt->tx)
		वापस 0;

	bt->tx->mute = ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक btcvsd_rx_irq_received_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);

	अगर (!bt->rx)
		वापस 0;

	ucontrol->value.पूर्णांकeger.value[0] = bt->rx->rw_cnt ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक btcvsd_rx_समयout_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);

	अगर (!bt->rx)
		वापस 0;

	ucontrol->value.पूर्णांकeger.value[0] = bt->rx->समयout;
	bt->rx->समयout = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक btcvsd_rx_बारtamp_get(काष्ठा snd_kcontrol *kcontrol,
				   अचिन्हित पूर्णांक __user *data, अचिन्हित पूर्णांक size)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);
	पूर्णांक ret = 0;
	काष्ठा mtk_btcvsd_snd_समय_buffer_info समय_buffer_info_rx;

	अगर (size > माप(काष्ठा mtk_btcvsd_snd_समय_buffer_info))
		वापस -EINVAL;

	get_rx_समय_stamp(bt, &समय_buffer_info_rx);

	dev_dbg(bt->dev, "%s(), time_stamp_us %llu, data_count_equi_time %llu",
		__func__,
		समय_buffer_info_rx.समय_stamp_us,
		समय_buffer_info_rx.data_count_equi_समय);

	अगर (copy_to_user(data, &समय_buffer_info_rx,
			 माप(काष्ठा mtk_btcvsd_snd_समय_buffer_info))) अणु
		dev_warn(bt->dev, "%s(), copy_to_user fail", __func__);
		ret = -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक btcvsd_tx_irq_received_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);

	अगर (!bt->tx)
		वापस 0;

	ucontrol->value.पूर्णांकeger.value[0] = bt->tx->rw_cnt ? 1 : 0;
	वापस 0;
पूर्ण

अटल पूर्णांक btcvsd_tx_समयout_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);

	ucontrol->value.पूर्णांकeger.value[0] = bt->tx->समयout;
	वापस 0;
पूर्ण

अटल पूर्णांक btcvsd_tx_बारtamp_get(काष्ठा snd_kcontrol *kcontrol,
				   अचिन्हित पूर्णांक __user *data, अचिन्हित पूर्णांक size)
अणु
	काष्ठा snd_soc_component *cmpnt = snd_soc_kcontrol_component(kcontrol);
	काष्ठा mtk_btcvsd_snd *bt = snd_soc_component_get_drvdata(cmpnt);
	पूर्णांक ret = 0;
	काष्ठा mtk_btcvsd_snd_समय_buffer_info समय_buffer_info_tx;

	अगर (size > माप(काष्ठा mtk_btcvsd_snd_समय_buffer_info))
		वापस -EINVAL;

	get_tx_समय_stamp(bt, &समय_buffer_info_tx);

	dev_dbg(bt->dev, "%s(), time_stamp_us %llu, data_count_equi_time %llu",
		__func__,
		समय_buffer_info_tx.समय_stamp_us,
		समय_buffer_info_tx.data_count_equi_समय);

	अगर (copy_to_user(data, &समय_buffer_info_tx,
			 माप(काष्ठा mtk_btcvsd_snd_समय_buffer_info))) अणु
		dev_warn(bt->dev, "%s(), copy_to_user fail", __func__);
		ret = -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mtk_btcvsd_snd_controls[] = अणु
	SOC_ENUM_EXT("BTCVSD Band", btcvsd_क्रमागत[0],
		     btcvsd_band_get, btcvsd_band_set),
	SOC_SINGLE_BOOL_EXT("BTCVSD Loopback Switch", 0,
			    btcvsd_loopback_get, btcvsd_loopback_set),
	SOC_SINGLE_BOOL_EXT("BTCVSD Tx Mute Switch", 0,
			    btcvsd_tx_mute_get, btcvsd_tx_mute_set),
	SOC_SINGLE_BOOL_EXT("BTCVSD Tx Irq Received Switch", 0,
			    btcvsd_tx_irq_received_get, शून्य),
	SOC_SINGLE_BOOL_EXT("BTCVSD Tx Timeout Switch", 0,
			    btcvsd_tx_समयout_get, शून्य),
	SOC_SINGLE_BOOL_EXT("BTCVSD Rx Irq Received Switch", 0,
			    btcvsd_rx_irq_received_get, शून्य),
	SOC_SINGLE_BOOL_EXT("BTCVSD Rx Timeout Switch", 0,
			    btcvsd_rx_समयout_get, शून्य),
	SND_SOC_BYTES_TLV("BTCVSD Rx Timestamp",
			  माप(काष्ठा mtk_btcvsd_snd_समय_buffer_info),
			  btcvsd_rx_बारtamp_get, शून्य),
	SND_SOC_BYTES_TLV("BTCVSD Tx Timestamp",
			  माप(काष्ठा mtk_btcvsd_snd_समय_buffer_info),
			  btcvsd_tx_बारtamp_get, शून्य),
पूर्ण;

अटल पूर्णांक mtk_btcvsd_snd_component_probe(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_add_component_controls(component,
		mtk_btcvsd_snd_controls,
		ARRAY_SIZE(mtk_btcvsd_snd_controls));
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver mtk_btcvsd_snd_platक्रमm = अणु
	.name		= BTCVSD_SND_NAME,
	.probe		= mtk_btcvsd_snd_component_probe,
	.खोलो		= mtk_pcm_btcvsd_खोलो,
	.बंद		= mtk_pcm_btcvsd_बंद,
	.hw_params	= mtk_pcm_btcvsd_hw_params,
	.hw_मुक्त	= mtk_pcm_btcvsd_hw_मुक्त,
	.prepare	= mtk_pcm_btcvsd_prepare,
	.trigger	= mtk_pcm_btcvsd_trigger,
	.poपूर्णांकer	= mtk_pcm_btcvsd_poपूर्णांकer,
	.copy_user	= mtk_pcm_btcvsd_copy,
पूर्ण;

अटल पूर्णांक mtk_btcvsd_snd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक irq_id;
	u32 offset[5] = अणु0, 0, 0, 0, 0पूर्ण;
	काष्ठा mtk_btcvsd_snd *btcvsd;
	काष्ठा device *dev = &pdev->dev;

	/* init btcvsd निजी data */
	btcvsd = devm_kzalloc(dev, माप(*btcvsd), GFP_KERNEL);
	अगर (!btcvsd)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, btcvsd);
	btcvsd->dev = dev;

	/* init tx/rx */
	btcvsd->rx = devm_kzalloc(btcvsd->dev, माप(*btcvsd->rx), GFP_KERNEL);
	अगर (!btcvsd->rx)
		वापस -ENOMEM;

	btcvsd->tx = devm_kzalloc(btcvsd->dev, माप(*btcvsd->tx), GFP_KERNEL);
	अगर (!btcvsd->tx)
		वापस -ENOMEM;

	spin_lock_init(&btcvsd->tx_lock);
	spin_lock_init(&btcvsd->rx_lock);

	init_रुकोqueue_head(&btcvsd->tx_रुको);
	init_रुकोqueue_head(&btcvsd->rx_रुको);

	mtk_btcvsd_snd_tx_init(btcvsd);
	mtk_btcvsd_snd_rx_init(btcvsd);

	/* irq */
	irq_id = platक्रमm_get_irq(pdev, 0);
	अगर (irq_id <= 0)
		वापस irq_id < 0 ? irq_id : -ENXIO;

	ret = devm_request_irq(dev, irq_id, mtk_btcvsd_snd_irq_handler,
			       IRQF_TRIGGER_LOW, "BTCVSD_ISR_Handle",
			       (व्योम *)btcvsd);
	अगर (ret) अणु
		dev_err(dev, "could not request_irq for BTCVSD_ISR_Handle\n");
		वापस ret;
	पूर्ण

	btcvsd->irq_id = irq_id;

	/* iomap */
	btcvsd->bt_pkv_base = of_iomap(dev->of_node, 0);
	अगर (!btcvsd->bt_pkv_base) अणु
		dev_err(dev, "iomap bt_pkv_base fail\n");
		वापस -EIO;
	पूर्ण

	btcvsd->bt_sram_bank2_base = of_iomap(dev->of_node, 1);
	अगर (!btcvsd->bt_sram_bank2_base) अणु
		dev_err(dev, "iomap bt_sram_bank2_base fail\n");
		वापस -EIO;
	पूर्ण

	btcvsd->infra = syscon_regmap_lookup_by_phandle(dev->of_node,
							"mediatek,infracfg");
	अगर (IS_ERR(btcvsd->infra)) अणु
		dev_err(dev, "cannot find infra controller: %ld\n",
			PTR_ERR(btcvsd->infra));
		वापस PTR_ERR(btcvsd->infra);
	पूर्ण

	/* get offset */
	ret = of_property_पढ़ो_u32_array(dev->of_node, "mediatek,offset",
					 offset,
					 ARRAY_SIZE(offset));
	अगर (ret) अणु
		dev_warn(dev, "%s(), get offset fail, ret %d\n", __func__, ret);
		वापस ret;
	पूर्ण
	btcvsd->infra_misc_offset = offset[0];
	btcvsd->conn_bt_cvsd_mask = offset[1];
	btcvsd->cvsd_mcu_पढ़ो_offset = offset[2];
	btcvsd->cvsd_mcu_ग_लिखो_offset = offset[3];
	btcvsd->cvsd_packet_indicator = offset[4];

	btcvsd->bt_reg_pkt_r = btcvsd->bt_pkv_base +
			       btcvsd->cvsd_mcu_पढ़ो_offset;
	btcvsd->bt_reg_pkt_w = btcvsd->bt_pkv_base +
			       btcvsd->cvsd_mcu_ग_लिखो_offset;
	btcvsd->bt_reg_ctl = btcvsd->bt_pkv_base +
			     btcvsd->cvsd_packet_indicator;

	/* init state */
	mtk_btcvsd_snd_set_state(btcvsd, btcvsd->tx, BT_SCO_STATE_IDLE);
	mtk_btcvsd_snd_set_state(btcvsd, btcvsd->rx, BT_SCO_STATE_IDLE);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &mtk_btcvsd_snd_platक्रमm,
					       शून्य, 0);
पूर्ण

अटल पूर्णांक mtk_btcvsd_snd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_btcvsd_snd *btcvsd = dev_get_drvdata(&pdev->dev);

	iounmap(btcvsd->bt_pkv_base);
	iounmap(btcvsd->bt_sram_bank2_base);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_btcvsd_snd_dt_match[] = अणु
	अणु .compatible = "mediatek,mtk-btcvsd-snd", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_btcvsd_snd_dt_match);

अटल काष्ठा platक्रमm_driver mtk_btcvsd_snd_driver = अणु
	.driver = अणु
		.name = "mtk-btcvsd-snd",
		.of_match_table = mtk_btcvsd_snd_dt_match,
	पूर्ण,
	.probe = mtk_btcvsd_snd_probe,
	.हटाओ = mtk_btcvsd_snd_हटाओ,
पूर्ण;

module_platक्रमm_driver(mtk_btcvsd_snd_driver);

MODULE_DESCRIPTION("Mediatek ALSA BT SCO CVSD/MSBC Driver");
MODULE_AUTHOR("KaiChieh Chuang <kaichieh.chuang@mediatek.com>");
MODULE_LICENSE("GPL v2");
