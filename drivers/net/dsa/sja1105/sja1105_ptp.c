<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Vladimir Oltean <olteanv@gmail.com>
 */
#समावेश <linux/spi/spi.h>
#समावेश "sja1105.h"

/* The adjfine API clamps ppb between [-32,768,000, 32,768,000], and
 * thereक्रमe scaled_ppm between [-2,147,483,648, 2,147,483,647].
 * Set the maximum supported ppb to a round value smaller than the maximum.
 *
 * Percentually speaking, this is a +/- 0.032x adjusपंचांगent of the
 * मुक्त-running counter (0.968x to 1.032x).
 */
#घोषणा SJA1105_MAX_ADJ_PPB		32000000
#घोषणा SJA1105_SIZE_PTP_CMD		4

/* PTPSYNCTS has no पूर्णांकerrupt or update mechanism, because the पूर्णांकended
 * hardware use हाल is क्रम the बारtamp to be collected synchronously,
 * immediately after the CAS_MASTER SJA1105 चयन has perक्रमmed a CASSYNC
 * one-shot toggle (no वापस to level) on the PTP_CLK pin. When used as a
 * generic extts source, the PTPSYNCTS रेजिस्टर needs polling and a comparison
 * with the old value. The polling पूर्णांकerval is configured as the Nyquist rate
 * of a संकेत with 50% duty cycle and 1Hz frequency, which is sadly all that
 * this hardware can करो (but may be enough क्रम some setups). Anything of higher
 * frequency than 1 Hz will be lost, since there is no बारtamp FIFO.
 */
#घोषणा SJA1105_EXTTS_INTERVAL		(HZ / 6)

/*            This range is actually +/- SJA1105_MAX_ADJ_PPB
 *            भागided by 1000 (ppb -> ppm) and with a 16-bit
 *            "fractional" part (actually fixed poपूर्णांक).
 *                                    |
 *                                    v
 * Convert scaled_ppm from the +/- ((10^6) << 16) range
 * पूर्णांकo the +/- (1 << 31) range.
 *
 * This क्रमgoes a "ppb" numeric representation (up to NSEC_PER_SEC)
 * and defines the scaling factor between scaled_ppm and the actual
 * frequency adjusपंचांगents of the PHC.
 *
 *   ptpclkrate = scaled_ppm * 2^31 / (10^6 * 2^16)
 *   simplअगरies to
 *   ptpclkrate = scaled_ppm * 2^9 / 5^6
 */
#घोषणा SJA1105_CC_MULT_NUM		(1 << 9)
#घोषणा SJA1105_CC_MULT_DEM		15625
#घोषणा SJA1105_CC_MULT			0x80000000

क्रमागत sja1105_ptp_clk_mode अणु
	PTP_ADD_MODE = 1,
	PTP_SET_MODE = 0,
पूर्ण;

#घोषणा extts_to_data(t) \
		container_of((t), काष्ठा sja1105_ptp_data, extts_समयr)
#घोषणा ptp_caps_to_data(d) \
		container_of((d), काष्ठा sja1105_ptp_data, caps)
#घोषणा ptp_data_to_sja1105(d) \
		container_of((d), काष्ठा sja1105_निजी, ptp_data)

/* Must be called only with priv->tagger_data.state bit
 * SJA1105_HWTS_RX_EN cleared
 */
अटल पूर्णांक sja1105_change_rxtstamping(काष्ठा sja1105_निजी *priv,
				      bool on)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;
	काष्ठा sja1105_general_params_entry *general_params;
	काष्ठा sja1105_table *table;

	table = &priv->अटल_config.tables[BLK_IDX_GENERAL_PARAMS];
	general_params = table->entries;
	general_params->send_meta1 = on;
	general_params->send_meta0 = on;

	/* Initialize the meta state machine to a known state */
	अगर (priv->tagger_data.stampable_skb) अणु
		kमुक्त_skb(priv->tagger_data.stampable_skb);
		priv->tagger_data.stampable_skb = शून्य;
	पूर्ण
	ptp_cancel_worker_sync(ptp_data->घड़ी);
	skb_queue_purge(&ptp_data->skb_rxtstamp_queue);

	वापस sja1105_अटल_config_reload(priv, SJA1105_RX_HWTSTAMPING);
पूर्ण

पूर्णांक sja1105_hwtstamp_set(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा hwtstamp_config config;
	bool rx_on;
	पूर्णांक rc;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		priv->ports[port].hwts_tx_en = false;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		priv->ports[port].hwts_tx_en = true;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		rx_on = false;
		अवरोध;
	शेष:
		rx_on = true;
		अवरोध;
	पूर्ण

	अगर (rx_on != test_bit(SJA1105_HWTS_RX_EN, &priv->tagger_data.state)) अणु
		clear_bit(SJA1105_HWTS_RX_EN, &priv->tagger_data.state);

		rc = sja1105_change_rxtstamping(priv, rx_on);
		अगर (rc < 0) अणु
			dev_err(ds->dev,
				"Failed to change RX timestamping: %d\n", rc);
			वापस rc;
		पूर्ण
		अगर (rx_on)
			set_bit(SJA1105_HWTS_RX_EN, &priv->tagger_data.state);
	पूर्ण

	अगर (copy_to_user(अगरr->अगरr_data, &config, माप(config)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

पूर्णांक sja1105_hwtstamp_get(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा hwtstamp_config config;

	config.flags = 0;
	अगर (priv->ports[port].hwts_tx_en)
		config.tx_type = HWTSTAMP_TX_ON;
	अन्यथा
		config.tx_type = HWTSTAMP_TX_OFF;
	अगर (test_bit(SJA1105_HWTS_RX_EN, &priv->tagger_data.state))
		config.rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
	अन्यथा
		config.rx_filter = HWTSTAMP_FILTER_NONE;

	वापस copy_to_user(अगरr->अगरr_data, &config, माप(config)) ?
		-EFAULT : 0;
पूर्ण

पूर्णांक sja1105_get_ts_info(काष्ठा dsa_चयन *ds, पूर्णांक port,
			काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;

	/* Called during cleanup */
	अगर (!ptp_data->घड़ी)
		वापस -ENODEV;

	info->so_बारtamping = SOF_TIMESTAMPING_TX_HARDWARE |
				SOF_TIMESTAMPING_RX_HARDWARE |
				SOF_TIMESTAMPING_RAW_HARDWARE;
	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON);
	info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
			   (1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT);
	info->phc_index = ptp_घड़ी_index(ptp_data->घड़ी);
	वापस 0;
पूर्ण

व्योम sja1105et_ptp_cmd_packing(u8 *buf, काष्ठा sja1105_ptp_cmd *cmd,
			       क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = SJA1105_SIZE_PTP_CMD;
	/* No need to keep this as part of the काष्ठाure */
	u64 valid = 1;

	sja1105_packing(buf, &valid,           31, 31, size, op);
	sja1105_packing(buf, &cmd->ptpstrtsch, 30, 30, size, op);
	sja1105_packing(buf, &cmd->ptpstopsch, 29, 29, size, op);
	sja1105_packing(buf, &cmd->startptpcp, 28, 28, size, op);
	sja1105_packing(buf, &cmd->stopptpcp,  27, 27, size, op);
	sja1105_packing(buf, &cmd->resptp,      2,  2, size, op);
	sja1105_packing(buf, &cmd->corrclk4ts,  1,  1, size, op);
	sja1105_packing(buf, &cmd->ptpclkadd,   0,  0, size, op);
पूर्ण

व्योम sja1105pqrs_ptp_cmd_packing(u8 *buf, काष्ठा sja1105_ptp_cmd *cmd,
				 क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = SJA1105_SIZE_PTP_CMD;
	/* No need to keep this as part of the काष्ठाure */
	u64 valid = 1;

	sja1105_packing(buf, &valid,           31, 31, size, op);
	sja1105_packing(buf, &cmd->ptpstrtsch, 30, 30, size, op);
	sja1105_packing(buf, &cmd->ptpstopsch, 29, 29, size, op);
	sja1105_packing(buf, &cmd->startptpcp, 28, 28, size, op);
	sja1105_packing(buf, &cmd->stopptpcp,  27, 27, size, op);
	sja1105_packing(buf, &cmd->resptp,      3,  3, size, op);
	sja1105_packing(buf, &cmd->corrclk4ts,  2,  2, size, op);
	sja1105_packing(buf, &cmd->ptpclkadd,   0,  0, size, op);
पूर्ण

पूर्णांक sja1105_ptp_commit(काष्ठा dsa_चयन *ds, काष्ठा sja1105_ptp_cmd *cmd,
		       sja1105_spi_rw_mode_t rw)
अणु
	स्थिर काष्ठा sja1105_निजी *priv = ds->priv;
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u8 buf[SJA1105_SIZE_PTP_CMD] = अणु0पूर्ण;
	पूर्णांक rc;

	अगर (rw == SPI_WRITE)
		priv->info->ptp_cmd_packing(buf, cmd, PACK);

	rc = sja1105_xfer_buf(priv, rw, regs->ptp_control, buf,
			      SJA1105_SIZE_PTP_CMD);

	अगर (rw == SPI_READ)
		priv->info->ptp_cmd_packing(buf, cmd, UNPACK);

	वापस rc;
पूर्ण

/* The चयन वापसs partial बारtamps (24 bits क्रम SJA1105 E/T, which wrap
 * around in 0.135 seconds, and 32 bits क्रम P/Q/R/S, wrapping around in 34.35
 * seconds).
 *
 * This receives the RX or TX MAC बारtamps, provided by hardware as
 * the lower bits of the cycle counter, sampled at the समय the बारtamp was
 * collected.
 *
 * To reस्थिरruct पूर्णांकo a full 64-bit-wide बारtamp, the cycle counter is
 * पढ़ो and the high-order bits are filled in.
 *
 * Must be called within one wraparound period of the partial बारtamp since
 * it was generated by the MAC.
 */
अटल u64 sja1105_tstamp_reस्थिरruct(काष्ठा dsa_चयन *ds, u64 now,
				      u64 ts_partial)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	u64 partial_tstamp_mask = CYCLECOUNTER_MASK(priv->info->ptp_ts_bits);
	u64 ts_reस्थिरructed;

	ts_reस्थिरructed = (now & ~partial_tstamp_mask) | ts_partial;

	/* Check lower bits of current cycle counter against the बारtamp.
	 * If the current cycle counter is lower than the partial बारtamp,
	 * then wraparound surely occurred and must be accounted क्रम.
	 */
	अगर ((now & partial_tstamp_mask) <= ts_partial)
		ts_reस्थिरructed -= (partial_tstamp_mask + 1);

	वापस ts_reस्थिरructed;
पूर्ण

/* Reads the SPI पूर्णांकerface क्रम an egress बारtamp generated by the चयन
 * क्रम frames sent using management routes.
 *
 * SJA1105 E/T layout of the 4-byte SPI payload:
 *
 * 31    23    15    7     0
 * |     |     |     |     |
 * +-----+-----+-----+     ^
 *          ^              |
 *          |              |
 *  24-bit बारtamp   Update bit
 *
 *
 * SJA1105 P/Q/R/S layout of the 8-byte SPI payload:
 *
 * 31    23    15    7     0     63    55    47    39    32
 * |     |     |     |     |     |     |     |     |     |
 *                         ^     +-----+-----+-----+-----+
 *                         |                 ^
 *                         |                 |
 *                    Update bit    32-bit बारtamp
 *
 * Notice that the update bit is in the same place.
 * To have common code क्रम E/T and P/Q/R/S क्रम पढ़ोing the बारtamp,
 * we need to juggle with the offset and the bit indices.
 */
अटल पूर्णांक sja1105_ptpegr_ts_poll(काष्ठा dsa_चयन *ds, पूर्णांक port, u64 *ts)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	पूर्णांक tstamp_bit_start, tstamp_bit_end;
	पूर्णांक समयout = 10;
	u8 packed_buf[8];
	u64 update;
	पूर्णांक rc;

	करो अणु
		rc = sja1105_xfer_buf(priv, SPI_READ, regs->ptpegr_ts[port],
				      packed_buf, priv->info->ptpegr_ts_bytes);
		अगर (rc < 0)
			वापस rc;

		sja1105_unpack(packed_buf, &update, 0, 0,
			       priv->info->ptpegr_ts_bytes);
		अगर (update)
			अवरोध;

		usleep_range(10, 50);
	पूर्ण जबतक (--समयout);

	अगर (!समयout)
		वापस -ETIMEDOUT;

	/* Poपूर्णांक the end bit to the second 32-bit word on P/Q/R/S,
	 * no-op on E/T.
	 */
	tstamp_bit_end = (priv->info->ptpegr_ts_bytes - 4) * 8;
	/* Shअगरt the 24-bit बारtamp on E/T to be collected from 31:8.
	 * No-op on P/Q/R/S.
	 */
	tstamp_bit_end += 32 - priv->info->ptp_ts_bits;
	tstamp_bit_start = tstamp_bit_end + priv->info->ptp_ts_bits - 1;

	*ts = 0;

	sja1105_unpack(packed_buf, ts, tstamp_bit_start, tstamp_bit_end,
		       priv->info->ptpegr_ts_bytes);

	वापस 0;
पूर्ण

/* Caller must hold ptp_data->lock */
अटल पूर्णांक sja1105_ptpclkval_पढ़ो(काष्ठा sja1105_निजी *priv, u64 *ticks,
				  काष्ठा ptp_प्रणाली_बारtamp *ptp_sts)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;

	वापस sja1105_xfer_u64(priv, SPI_READ, regs->ptpclkval, ticks,
				ptp_sts);
पूर्ण

/* Caller must hold ptp_data->lock */
अटल पूर्णांक sja1105_ptpclkval_ग_लिखो(काष्ठा sja1105_निजी *priv, u64 ticks,
				   काष्ठा ptp_प्रणाली_बारtamp *ptp_sts)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;

	वापस sja1105_xfer_u64(priv, SPI_WRITE, regs->ptpclkval, &ticks,
				ptp_sts);
पूर्ण

अटल व्योम sja1105_extts_poll(काष्ठा sja1105_निजी *priv)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा ptp_घड़ी_event event;
	u64 ptpsyncts = 0;
	पूर्णांक rc;

	rc = sja1105_xfer_u64(priv, SPI_READ, regs->ptpsyncts, &ptpsyncts,
			      शून्य);
	अगर (rc < 0)
		dev_err_ratelimited(priv->ds->dev,
				    "Failed to read PTPSYNCTS: %d\n", rc);

	अगर (ptpsyncts && ptp_data->ptpsyncts != ptpsyncts) अणु
		event.index = 0;
		event.type = PTP_CLOCK_EXTTS;
		event.बारtamp = ns_to_kसमय(sja1105_ticks_to_ns(ptpsyncts));
		ptp_घड़ी_event(ptp_data->घड़ी, &event);

		ptp_data->ptpsyncts = ptpsyncts;
	पूर्ण
पूर्ण

अटल दीर्घ sja1105_rxtstamp_work(काष्ठा ptp_घड़ी_info *ptp)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	काष्ठा sja1105_निजी *priv = ptp_data_to_sja1105(ptp_data);
	काष्ठा dsa_चयन *ds = priv->ds;
	काष्ठा sk_buff *skb;

	mutex_lock(&ptp_data->lock);

	जबतक ((skb = skb_dequeue(&ptp_data->skb_rxtstamp_queue)) != शून्य) अणु
		काष्ठा skb_shared_hwtstamps *shwt = skb_hwtstamps(skb);
		u64 ticks, ts;
		पूर्णांक rc;

		rc = sja1105_ptpclkval_पढ़ो(priv, &ticks, शून्य);
		अगर (rc < 0) अणु
			dev_err(ds->dev, "Failed to read PTP clock: %d\n", rc);
			kमुक्त_skb(skb);
			जारी;
		पूर्ण

		*shwt = (काष्ठा skb_shared_hwtstamps) अणु0पूर्ण;

		ts = SJA1105_SKB_CB(skb)->meta_tstamp;
		ts = sja1105_tstamp_reस्थिरruct(ds, ticks, ts);

		shwt->hwtstamp = ns_to_kसमय(sja1105_ticks_to_ns(ts));
		netअगर_rx_ni(skb);
	पूर्ण

	अगर (ptp_data->extts_enabled)
		sja1105_extts_poll(priv);

	mutex_unlock(&ptp_data->lock);

	/* Don't restart */
	वापस -1;
पूर्ण

/* Called from dsa_skb_defer_rx_बारtamp */
bool sja1105_port_rxtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा sk_buff *skb, अचिन्हित पूर्णांक type)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;

	अगर (!test_bit(SJA1105_HWTS_RX_EN, &priv->tagger_data.state))
		वापस false;

	/* We need to पढ़ो the full PTP घड़ी to reस्थिरruct the Rx
	 * बारtamp. For that we need a sleepable context.
	 */
	skb_queue_tail(&ptp_data->skb_rxtstamp_queue, skb);
	ptp_schedule_worker(ptp_data->घड़ी, 0);
	वापस true;
पूर्ण

/* Called from dsa_skb_tx_बारtamp. This callback is just to clone
 * the skb and have it available in SJA1105_SKB_CB in the .port_deferred_xmit
 * callback, where we will बारtamp it synchronously.
 */
व्योम sja1105_port_txtstamp(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा sk_buff *skb)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_port *sp = &priv->ports[port];
	काष्ठा sk_buff *clone;

	अगर (!sp->hwts_tx_en)
		वापस;

	clone = skb_clone_sk(skb);
	अगर (!clone)
		वापस;

	SJA1105_SKB_CB(skb)->clone = clone;
पूर्ण

अटल पूर्णांक sja1105_ptp_reset(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;
	काष्ठा sja1105_ptp_cmd cmd = ptp_data->cmd;
	पूर्णांक rc;

	mutex_lock(&ptp_data->lock);

	cmd.resptp = 1;

	dev_dbg(ds->dev, "Resetting PTP clock\n");
	rc = sja1105_ptp_commit(ds, &cmd, SPI_WRITE);

	sja1105_tas_घड़ीstep(priv->ds);

	mutex_unlock(&ptp_data->lock);

	वापस rc;
पूर्ण

/* Caller must hold ptp_data->lock */
पूर्णांक __sja1105_ptp_समय_लोx(काष्ठा dsa_चयन *ds, u64 *ns,
			   काष्ठा ptp_प्रणाली_बारtamp *ptp_sts)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	u64 ticks;
	पूर्णांक rc;

	rc = sja1105_ptpclkval_पढ़ो(priv, &ticks, ptp_sts);
	अगर (rc < 0) अणु
		dev_err(ds->dev, "Failed to read PTP clock: %d\n", rc);
		वापस rc;
	पूर्ण

	*ns = sja1105_ticks_to_ns(ticks);

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_ptp_समय_लोx(काष्ठा ptp_घड़ी_info *ptp,
				काष्ठा बारpec64 *ts,
				काष्ठा ptp_प्रणाली_बारtamp *ptp_sts)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	काष्ठा sja1105_निजी *priv = ptp_data_to_sja1105(ptp_data);
	u64 now = 0;
	पूर्णांक rc;

	mutex_lock(&ptp_data->lock);

	rc = __sja1105_ptp_समय_लोx(priv->ds, &now, ptp_sts);
	*ts = ns_to_बारpec64(now);

	mutex_unlock(&ptp_data->lock);

	वापस rc;
पूर्ण

/* Caller must hold ptp_data->lock */
अटल पूर्णांक sja1105_ptp_mode_set(काष्ठा sja1105_निजी *priv,
				क्रमागत sja1105_ptp_clk_mode mode)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;

	अगर (ptp_data->cmd.ptpclkadd == mode)
		वापस 0;

	ptp_data->cmd.ptpclkadd = mode;

	वापस sja1105_ptp_commit(priv->ds, &ptp_data->cmd, SPI_WRITE);
पूर्ण

/* Write to PTPCLKVAL जबतक PTPCLKADD is 0 */
पूर्णांक __sja1105_ptp_समय_रखो(काष्ठा dsa_चयन *ds, u64 ns,
			  काष्ठा ptp_प्रणाली_बारtamp *ptp_sts)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	u64 ticks = ns_to_sja1105_ticks(ns);
	पूर्णांक rc;

	rc = sja1105_ptp_mode_set(priv, PTP_SET_MODE);
	अगर (rc < 0) अणु
		dev_err(priv->ds->dev, "Failed to put PTPCLK in set mode\n");
		वापस rc;
	पूर्ण

	rc = sja1105_ptpclkval_ग_लिखो(priv, ticks, ptp_sts);

	sja1105_tas_घड़ीstep(priv->ds);

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_ptp_समय_रखो(काष्ठा ptp_घड़ी_info *ptp,
			       स्थिर काष्ठा बारpec64 *ts)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	काष्ठा sja1105_निजी *priv = ptp_data_to_sja1105(ptp_data);
	u64 ns = बारpec64_to_ns(ts);
	पूर्णांक rc;

	mutex_lock(&ptp_data->lock);

	rc = __sja1105_ptp_समय_रखो(priv->ds, ns, शून्य);

	mutex_unlock(&ptp_data->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_ptp_adjfine(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	काष्ठा sja1105_निजी *priv = ptp_data_to_sja1105(ptp_data);
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u32 clkrate32;
	s64 clkrate;
	पूर्णांक rc;

	clkrate = (s64)scaled_ppm * SJA1105_CC_MULT_NUM;
	clkrate = भाग_s64(clkrate, SJA1105_CC_MULT_DEM);

	/* Take a +/- value and re-center it around 2^31. */
	clkrate = SJA1105_CC_MULT + clkrate;
	WARN_ON(असल(clkrate) >= GENMASK_ULL(31, 0));
	clkrate32 = clkrate;

	mutex_lock(&ptp_data->lock);

	rc = sja1105_xfer_u32(priv, SPI_WRITE, regs->ptpclkrate, &clkrate32,
			      शून्य);

	sja1105_tas_adjfreq(priv->ds);

	mutex_unlock(&ptp_data->lock);

	वापस rc;
पूर्ण

/* Write to PTPCLKVAL जबतक PTPCLKADD is 1 */
पूर्णांक __sja1105_ptp_adjसमय(काष्ठा dsa_चयन *ds, s64 delta)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	s64 ticks = ns_to_sja1105_ticks(delta);
	पूर्णांक rc;

	rc = sja1105_ptp_mode_set(priv, PTP_ADD_MODE);
	अगर (rc < 0) अणु
		dev_err(priv->ds->dev, "Failed to put PTPCLK in add mode\n");
		वापस rc;
	पूर्ण

	rc = sja1105_ptpclkval_ग_लिखो(priv, ticks, शून्य);

	sja1105_tas_घड़ीstep(priv->ds);

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_ptp_adjसमय(काष्ठा ptp_घड़ी_info *ptp, s64 delta)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	काष्ठा sja1105_निजी *priv = ptp_data_to_sja1105(ptp_data);
	पूर्णांक rc;

	mutex_lock(&ptp_data->lock);

	rc = __sja1105_ptp_adjसमय(priv->ds, delta);

	mutex_unlock(&ptp_data->lock);

	वापस rc;
पूर्ण

अटल व्योम sja1105_ptp_extts_setup_समयr(काष्ठा sja1105_ptp_data *ptp_data)
अणु
	अचिन्हित दीर्घ expires = ((jअगरfies / SJA1105_EXTTS_INTERVAL) + 1) *
				SJA1105_EXTTS_INTERVAL;

	mod_समयr(&ptp_data->extts_समयr, expires);
पूर्ण

अटल व्योम sja1105_ptp_extts_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = extts_to_data(t);

	ptp_schedule_worker(ptp_data->घड़ी, 0);

	sja1105_ptp_extts_setup_समयr(ptp_data);
पूर्ण

अटल पूर्णांक sja1105_change_ptp_clk_pin_func(काष्ठा sja1105_निजी *priv,
					   क्रमागत ptp_pin_function func)
अणु
	काष्ठा sja1105_avb_params_entry *avb;
	क्रमागत ptp_pin_function old_func;

	avb = priv->अटल_config.tables[BLK_IDX_AVB_PARAMS].entries;

	अगर (priv->info->device_id == SJA1105E_DEVICE_ID ||
	    priv->info->device_id == SJA1105T_DEVICE_ID ||
	    avb->cas_master)
		old_func = PTP_PF_PEROUT;
	अन्यथा
		old_func = PTP_PF_EXTTS;

	अगर (func == old_func)
		वापस 0;

	avb->cas_master = (func == PTP_PF_PEROUT);

	वापस sja1105_dynamic_config_ग_लिखो(priv, BLK_IDX_AVB_PARAMS, 0, avb,
					    true);
पूर्ण

/* The PTP_CLK pin may be configured to toggle with a 50% duty cycle and a
 * frequency f:
 *
 *           NSEC_PER_SEC
 * f = ----------------------
 *     (PTPPINDUR * 8 ns) * 2
 */
अटल पूर्णांक sja1105_per_out_enable(काष्ठा sja1105_निजी *priv,
				  काष्ठा ptp_perout_request *perout,
				  bool on)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_ptp_cmd cmd = ptp_data->cmd;
	पूर्णांक rc;

	/* We only support one channel */
	अगर (perout->index != 0)
		वापस -EOPNOTSUPP;

	/* Reject requests with unsupported flags */
	अगर (perout->flags)
		वापस -EOPNOTSUPP;

	mutex_lock(&ptp_data->lock);

	rc = sja1105_change_ptp_clk_pin_func(priv, PTP_PF_PEROUT);
	अगर (rc)
		जाओ out;

	अगर (on) अणु
		काष्ठा बारpec64 pin_duration_ts = अणु
			.tv_sec = perout->period.sec,
			.tv_nsec = perout->period.nsec,
		पूर्ण;
		काष्ठा बारpec64 pin_start_ts = अणु
			.tv_sec = perout->start.sec,
			.tv_nsec = perout->start.nsec,
		पूर्ण;
		u64 pin_duration = बारpec64_to_ns(&pin_duration_ts);
		u64 pin_start = बारpec64_to_ns(&pin_start_ts);
		u32 pin_duration32;
		u64 now;

		/* ptppindur: 32 bit रेजिस्टर which holds the पूर्णांकerval between
		 * 2 edges on PTP_CLK. So check क्रम truncation which happens
		 * at periods larger than around 68.7 seconds.
		 */
		pin_duration = ns_to_sja1105_ticks(pin_duration / 2);
		अगर (pin_duration > U32_MAX) अणु
			rc = -दुस्फल;
			जाओ out;
		पूर्ण
		pin_duration32 = pin_duration;

		/* ptppins: 64 bit रेजिस्टर which needs to hold a PTP समय
		 * larger than the current समय, otherwise the startptpcp
		 * command won't करो anything. So advance the current समय
		 * by a number of periods in a way that won't alter the
		 * phase offset.
		 */
		rc = __sja1105_ptp_समय_लोx(priv->ds, &now, शून्य);
		अगर (rc < 0)
			जाओ out;

		pin_start = future_base_समय(pin_start, pin_duration,
					     now + 1ull * NSEC_PER_SEC);
		pin_start = ns_to_sja1105_ticks(pin_start);

		rc = sja1105_xfer_u64(priv, SPI_WRITE, regs->ptppinst,
				      &pin_start, शून्य);
		अगर (rc < 0)
			जाओ out;

		rc = sja1105_xfer_u32(priv, SPI_WRITE, regs->ptppindur,
				      &pin_duration32, शून्य);
		अगर (rc < 0)
			जाओ out;
	पूर्ण

	अगर (on)
		cmd.startptpcp = true;
	अन्यथा
		cmd.stopptpcp = true;

	rc = sja1105_ptp_commit(priv->ds, &cmd, SPI_WRITE);

out:
	mutex_unlock(&ptp_data->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_extts_enable(काष्ठा sja1105_निजी *priv,
				काष्ठा ptp_extts_request *extts,
				bool on)
अणु
	पूर्णांक rc;

	/* We only support one channel */
	अगर (extts->index != 0)
		वापस -EOPNOTSUPP;

	/* Reject requests with unsupported flags */
	अगर (extts->flags & ~(PTP_ENABLE_FEATURE |
			     PTP_RISING_EDGE |
			     PTP_FALLING_EDGE |
			     PTP_STRICT_FLAGS))
		वापस -EOPNOTSUPP;

	/* We can only enable समय stamping on both edges, sadly. */
	अगर ((extts->flags & PTP_STRICT_FLAGS) &&
	    (extts->flags & PTP_ENABLE_FEATURE) &&
	    (extts->flags & PTP_EXTTS_EDGES) != PTP_EXTTS_EDGES)
		वापस -EOPNOTSUPP;

	rc = sja1105_change_ptp_clk_pin_func(priv, PTP_PF_EXTTS);
	अगर (rc)
		वापस rc;

	priv->ptp_data.extts_enabled = on;

	अगर (on)
		sja1105_ptp_extts_setup_समयr(&priv->ptp_data);
	अन्यथा
		del_समयr_sync(&priv->ptp_data.extts_समयr);

	वापस 0;
पूर्ण

अटल पूर्णांक sja1105_ptp_enable(काष्ठा ptp_घड़ी_info *ptp,
			      काष्ठा ptp_घड़ी_request *req, पूर्णांक on)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	काष्ठा sja1105_निजी *priv = ptp_data_to_sja1105(ptp_data);
	पूर्णांक rc = -EOPNOTSUPP;

	अगर (req->type == PTP_CLK_REQ_PEROUT)
		rc = sja1105_per_out_enable(priv, &req->perout, on);
	अन्यथा अगर (req->type == PTP_CLK_REQ_EXTTS)
		rc = sja1105_extts_enable(priv, &req->extts, on);

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_ptp_verअगरy_pin(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
				  क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	काष्ठा sja1105_निजी *priv = ptp_data_to_sja1105(ptp_data);

	अगर (chan != 0 || pin != 0)
		वापस -1;

	चयन (func) अणु
	हाल PTP_PF_NONE:
	हाल PTP_PF_PEROUT:
		अवरोध;
	हाल PTP_PF_EXTTS:
		अगर (priv->info->device_id == SJA1105E_DEVICE_ID ||
		    priv->info->device_id == SJA1105T_DEVICE_ID)
			वापस -1;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ptp_pin_desc sja1105_ptp_pin = अणु
	.name = "ptp_clk",
	.index = 0,
	.func = PTP_PF_NONE,
पूर्ण;

पूर्णांक sja1105_ptp_घड़ी_रेजिस्टर(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_tagger_data *tagger_data = &priv->tagger_data;
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;

	ptp_data->caps = (काष्ठा ptp_घड़ी_info) अणु
		.owner		= THIS_MODULE,
		.name		= "SJA1105 PHC",
		.adjfine	= sja1105_ptp_adjfine,
		.adjसमय	= sja1105_ptp_adjसमय,
		.समय_लोx64	= sja1105_ptp_समय_लोx,
		.समय_रखो64	= sja1105_ptp_समय_रखो,
		.enable		= sja1105_ptp_enable,
		.verअगरy		= sja1105_ptp_verअगरy_pin,
		.करो_aux_work	= sja1105_rxtstamp_work,
		.max_adj	= SJA1105_MAX_ADJ_PPB,
		.pin_config	= &sja1105_ptp_pin,
		.n_pins		= 1,
		.n_ext_ts	= 1,
		.n_per_out	= 1,
	पूर्ण;

	skb_queue_head_init(&ptp_data->skb_rxtstamp_queue);
	spin_lock_init(&tagger_data->meta_lock);

	ptp_data->घड़ी = ptp_घड़ी_रेजिस्टर(&ptp_data->caps, ds->dev);
	अगर (IS_ERR_OR_शून्य(ptp_data->घड़ी))
		वापस PTR_ERR(ptp_data->घड़ी);

	ptp_data->cmd.corrclk4ts = true;
	ptp_data->cmd.ptpclkadd = PTP_SET_MODE;

	समयr_setup(&ptp_data->extts_समयr, sja1105_ptp_extts_समयr, 0);

	वापस sja1105_ptp_reset(ds);
पूर्ण

व्योम sja1105_ptp_घड़ी_unरेजिस्टर(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;

	अगर (IS_ERR_OR_शून्य(ptp_data->घड़ी))
		वापस;

	del_समयr_sync(&ptp_data->extts_समयr);
	ptp_cancel_worker_sync(ptp_data->घड़ी);
	skb_queue_purge(&ptp_data->skb_rxtstamp_queue);
	ptp_घड़ी_unरेजिस्टर(ptp_data->घड़ी);
	ptp_data->घड़ी = शून्य;
पूर्ण

व्योम sja1105_ptp_txtstamp_skb(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_ptp_data *ptp_data = &priv->ptp_data;
	काष्ठा skb_shared_hwtstamps shwt = अणु0पूर्ण;
	u64 ticks, ts;
	पूर्णांक rc;

	skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

	mutex_lock(&ptp_data->lock);

	rc = sja1105_ptpegr_ts_poll(ds, port, &ts);
	अगर (rc < 0) अणु
		dev_err(ds->dev, "timed out polling for tstamp\n");
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	rc = sja1105_ptpclkval_पढ़ो(priv, &ticks, शून्य);
	अगर (rc < 0) अणु
		dev_err(ds->dev, "Failed to read PTP clock: %d\n", rc);
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	ts = sja1105_tstamp_reस्थिरruct(ds, ticks, ts);

	shwt.hwtstamp = ns_to_kसमय(sja1105_ticks_to_ns(ts));
	skb_complete_tx_बारtamp(skb, &shwt);

out:
	mutex_unlock(&ptp_data->lock);
पूर्ण
