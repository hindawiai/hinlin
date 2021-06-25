<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/* Copyright (c) 2016-2018, NXP Semiconductors
 * Copyright (c) 2018, Sensor-Technik Wiedemann GmbH
 * Copyright (c) 2018-2019, Vladimir Oltean <olteanv@gmail.com>
 */
#समावेश <linux/spi/spi.h>
#समावेश <linux/packing.h>
#समावेश "sja1105.h"

#घोषणा SJA1105_SIZE_RESET_CMD		4
#घोषणा SJA1105_SIZE_SPI_MSG_HEADER	4
#घोषणा SJA1105_SIZE_SPI_MSG_MAXLEN	(64 * 4)

काष्ठा sja1105_chunk अणु
	u8	*buf;
	माप_प्रकार	len;
	u64	reg_addr;
पूर्ण;

अटल व्योम
sja1105_spi_message_pack(व्योम *buf, स्थिर काष्ठा sja1105_spi_message *msg)
अणु
	स्थिर पूर्णांक size = SJA1105_SIZE_SPI_MSG_HEADER;

	स_रखो(buf, 0, size);

	sja1105_pack(buf, &msg->access,     31, 31, size);
	sja1105_pack(buf, &msg->पढ़ो_count, 30, 25, size);
	sja1105_pack(buf, &msg->address,    24,  4, size);
पूर्ण

#घोषणा sja1105_hdr_xfer(xfers, chunk) \
	((xfers) + 2 * (chunk))
#घोषणा sja1105_chunk_xfer(xfers, chunk) \
	((xfers) + 2 * (chunk) + 1)
#घोषणा sja1105_hdr_buf(hdr_bufs, chunk) \
	((hdr_bufs) + (chunk) * SJA1105_SIZE_SPI_MSG_HEADER)

/* If @rw is:
 * - SPI_WRITE: creates and sends an SPI ग_लिखो message at असलolute
 *		address reg_addr, taking @len bytes from *buf
 * - SPI_READ:  creates and sends an SPI पढ़ो message from असलolute
 *		address reg_addr, writing @len bytes पूर्णांकo *buf
 */
अटल पूर्णांक sja1105_xfer(स्थिर काष्ठा sja1105_निजी *priv,
			sja1105_spi_rw_mode_t rw, u64 reg_addr, u8 *buf,
			माप_प्रकार len, काष्ठा ptp_प्रणाली_बारtamp *ptp_sts)
अणु
	काष्ठा sja1105_chunk chunk = अणु
		.len = min_t(माप_प्रकार, len, SJA1105_SIZE_SPI_MSG_MAXLEN),
		.reg_addr = reg_addr,
		.buf = buf,
	पूर्ण;
	काष्ठा spi_device *spi = priv->spidev;
	काष्ठा spi_transfer *xfers;
	पूर्णांक num_chunks;
	पूर्णांक rc, i = 0;
	u8 *hdr_bufs;

	num_chunks = DIV_ROUND_UP(len, SJA1105_SIZE_SPI_MSG_MAXLEN);

	/* One transfer क्रम each message header, one क्रम each message
	 * payload (chunk).
	 */
	xfers = kसुस्मृति(2 * num_chunks, माप(काष्ठा spi_transfer),
			GFP_KERNEL);
	अगर (!xfers)
		वापस -ENOMEM;

	/* Packed buffers क्रम the num_chunks SPI message headers,
	 * stored as a contiguous array
	 */
	hdr_bufs = kसुस्मृति(num_chunks, SJA1105_SIZE_SPI_MSG_HEADER,
			   GFP_KERNEL);
	अगर (!hdr_bufs) अणु
		kमुक्त(xfers);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < num_chunks; i++) अणु
		काष्ठा spi_transfer *chunk_xfer = sja1105_chunk_xfer(xfers, i);
		काष्ठा spi_transfer *hdr_xfer = sja1105_hdr_xfer(xfers, i);
		u8 *hdr_buf = sja1105_hdr_buf(hdr_bufs, i);
		काष्ठा spi_transfer *ptp_sts_xfer;
		काष्ठा sja1105_spi_message msg;

		/* Populate the transfer's header buffer */
		msg.address = chunk.reg_addr;
		msg.access = rw;
		अगर (rw == SPI_READ)
			msg.पढ़ो_count = chunk.len / 4;
		अन्यथा
			/* Ignored */
			msg.पढ़ो_count = 0;
		sja1105_spi_message_pack(hdr_buf, &msg);
		hdr_xfer->tx_buf = hdr_buf;
		hdr_xfer->len = SJA1105_SIZE_SPI_MSG_HEADER;

		/* Populate the transfer's data buffer */
		अगर (rw == SPI_READ)
			chunk_xfer->rx_buf = chunk.buf;
		अन्यथा
			chunk_xfer->tx_buf = chunk.buf;
		chunk_xfer->len = chunk.len;

		/* Request बारtamping क्रम the transfer. Instead of letting
		 * callers specअगरy which byte they want to बारtamp, we can
		 * make certain assumptions:
		 * - A पढ़ो operation will request a software बारtamp when
		 *   what's being पढ़ो is the PTP समय. That is snapshotted by
		 *   the चयन hardware at the end of the command portion
		 *   (hdr_xfer).
		 * - A ग_लिखो operation will request a software बारtamp on
		 *   actions that modअगरy the PTP समय. Taking घड़ी stepping as
		 *   an example, the चयन ग_लिखोs the PTP समय at the end of
		 *   the data portion (chunk_xfer).
		 */
		अगर (rw == SPI_READ)
			ptp_sts_xfer = hdr_xfer;
		अन्यथा
			ptp_sts_xfer = chunk_xfer;
		ptp_sts_xfer->ptp_sts_word_pre = ptp_sts_xfer->len - 1;
		ptp_sts_xfer->ptp_sts_word_post = ptp_sts_xfer->len - 1;
		ptp_sts_xfer->ptp_sts = ptp_sts;

		/* Calculate next chunk */
		chunk.buf += chunk.len;
		chunk.reg_addr += chunk.len / 4;
		chunk.len = min_t(माप_प्रकार, (सूचक_भेद_प्रकार)(buf + len - chunk.buf),
				  SJA1105_SIZE_SPI_MSG_MAXLEN);

		/* De-निश्चित the chip select after each chunk. */
		अगर (chunk.len)
			chunk_xfer->cs_change = 1;
	पूर्ण

	rc = spi_sync_transfer(spi, xfers, 2 * num_chunks);
	अगर (rc < 0)
		dev_err(&spi->dev, "SPI transfer failed: %d\n", rc);

	kमुक्त(hdr_bufs);
	kमुक्त(xfers);

	वापस rc;
पूर्ण

पूर्णांक sja1105_xfer_buf(स्थिर काष्ठा sja1105_निजी *priv,
		     sja1105_spi_rw_mode_t rw, u64 reg_addr,
		     u8 *buf, माप_प्रकार len)
अणु
	वापस sja1105_xfer(priv, rw, reg_addr, buf, len, शून्य);
पूर्ण

/* If @rw is:
 * - SPI_WRITE: creates and sends an SPI ग_लिखो message at असलolute
 *		address reg_addr
 * - SPI_READ:  creates and sends an SPI पढ़ो message from असलolute
 *		address reg_addr
 *
 * The u64 *value is unpacked, meaning that it's stored in the native
 * CPU endianness and directly usable by software running on the core.
 */
पूर्णांक sja1105_xfer_u64(स्थिर काष्ठा sja1105_निजी *priv,
		     sja1105_spi_rw_mode_t rw, u64 reg_addr, u64 *value,
		     काष्ठा ptp_प्रणाली_बारtamp *ptp_sts)
अणु
	u8 packed_buf[8];
	पूर्णांक rc;

	अगर (rw == SPI_WRITE)
		sja1105_pack(packed_buf, value, 63, 0, 8);

	rc = sja1105_xfer(priv, rw, reg_addr, packed_buf, 8, ptp_sts);

	अगर (rw == SPI_READ)
		sja1105_unpack(packed_buf, value, 63, 0, 8);

	वापस rc;
पूर्ण

/* Same as above, but transfers only a 4 byte word */
पूर्णांक sja1105_xfer_u32(स्थिर काष्ठा sja1105_निजी *priv,
		     sja1105_spi_rw_mode_t rw, u64 reg_addr, u32 *value,
		     काष्ठा ptp_प्रणाली_बारtamp *ptp_sts)
अणु
	u8 packed_buf[4];
	u64 पंचांगp;
	पूर्णांक rc;

	अगर (rw == SPI_WRITE) अणु
		/* The packing API only supports u64 as CPU word size,
		 * so we need to convert.
		 */
		पंचांगp = *value;
		sja1105_pack(packed_buf, &पंचांगp, 31, 0, 4);
	पूर्ण

	rc = sja1105_xfer(priv, rw, reg_addr, packed_buf, 4, ptp_sts);

	अगर (rw == SPI_READ) अणु
		sja1105_unpack(packed_buf, &पंचांगp, 31, 0, 4);
		*value = पंचांगp;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105et_reset_cmd(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u8 packed_buf[SJA1105_SIZE_RESET_CMD] = अणु0पूर्ण;
	स्थिर पूर्णांक size = SJA1105_SIZE_RESET_CMD;
	u64 cold_rst = 1;

	sja1105_pack(packed_buf, &cold_rst, 3, 3, size);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->rgu, packed_buf,
				SJA1105_SIZE_RESET_CMD);
पूर्ण

अटल पूर्णांक sja1105pqrs_reset_cmd(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u8 packed_buf[SJA1105_SIZE_RESET_CMD] = अणु0पूर्ण;
	स्थिर पूर्णांक size = SJA1105_SIZE_RESET_CMD;
	u64 cold_rst = 1;

	sja1105_pack(packed_buf, &cold_rst, 2, 2, size);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->rgu, packed_buf,
				SJA1105_SIZE_RESET_CMD);
पूर्ण

पूर्णांक sja1105_inhibit_tx(स्थिर काष्ठा sja1105_निजी *priv,
		       अचिन्हित दीर्घ port_biपंचांगap, bool tx_inhibited)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u32 inhibit_cmd;
	पूर्णांक rc;

	rc = sja1105_xfer_u32(priv, SPI_READ, regs->port_control,
			      &inhibit_cmd, शून्य);
	अगर (rc < 0)
		वापस rc;

	अगर (tx_inhibited)
		inhibit_cmd |= port_biपंचांगap;
	अन्यथा
		inhibit_cmd &= ~port_biपंचांगap;

	वापस sja1105_xfer_u32(priv, SPI_WRITE, regs->port_control,
				&inhibit_cmd, शून्य);
पूर्ण

काष्ठा sja1105_status अणु
	u64 configs;
	u64 crcchkl;
	u64 ids;
	u64 crcchkg;
पूर्ण;

/* This is not पढ़ोing the entire General Status area, which is also
 * भागergent between E/T and P/Q/R/S, but only the relevant bits क्रम
 * ensuring that the अटल config upload procedure was successful.
 */
अटल व्योम sja1105_status_unpack(व्योम *buf, काष्ठा sja1105_status *status)
अणु
	/* So that addition translates to 4 bytes */
	u32 *p = buf;

	/* device_id is missing from the buffer, but we करोn't
	 * want to भागerge from the manual definition of the
	 * रेजिस्टर addresses, so we'll back off one step with
	 * the रेजिस्टर poपूर्णांकer, and never access p[0].
	 */
	p--;
	sja1105_unpack(p + 0x1, &status->configs,   31, 31, 4);
	sja1105_unpack(p + 0x1, &status->crcchkl,   30, 30, 4);
	sja1105_unpack(p + 0x1, &status->ids,       29, 29, 4);
	sja1105_unpack(p + 0x1, &status->crcchkg,   28, 28, 4);
पूर्ण

अटल पूर्णांक sja1105_status_get(काष्ठा sja1105_निजी *priv,
			      काष्ठा sja1105_status *status)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u8 packed_buf[4];
	पूर्णांक rc;

	rc = sja1105_xfer_buf(priv, SPI_READ, regs->status, packed_buf, 4);
	अगर (rc < 0)
		वापस rc;

	sja1105_status_unpack(packed_buf, status);

	वापस 0;
पूर्ण

/* Not स्थिर because unpacking priv->अटल_config पूर्णांकo buffers and preparing
 * क्रम upload requires the recalculation of table CRCs and updating the
 * काष्ठाures with these.
 */
पूर्णांक अटल_config_buf_prepare_क्रम_upload(काष्ठा sja1105_निजी *priv,
					 व्योम *config_buf, पूर्णांक buf_len)
अणु
	काष्ठा sja1105_अटल_config *config = &priv->अटल_config;
	काष्ठा sja1105_table_header final_header;
	sja1105_config_valid_t valid;
	अक्षर *final_header_ptr;
	पूर्णांक crc_len;

	valid = sja1105_अटल_config_check_valid(config);
	अगर (valid != SJA1105_CONFIG_OK) अणु
		dev_err(&priv->spidev->dev,
			sja1105_अटल_config_error_msg[valid]);
		वापस -EINVAL;
	पूर्ण

	/* Write Device ID and config tables to config_buf */
	sja1105_अटल_config_pack(config_buf, config);
	/* Recalculate CRC of the last header (right now 0xDEADBEEF).
	 * Don't include the CRC field itself.
	 */
	crc_len = buf_len - 4;
	/* Read the whole table header */
	final_header_ptr = config_buf + buf_len - SJA1105_SIZE_TABLE_HEADER;
	sja1105_table_header_packing(final_header_ptr, &final_header, UNPACK);
	/* Modअगरy */
	final_header.crc = sja1105_crc32(config_buf, crc_len);
	/* Reग_लिखो */
	sja1105_table_header_packing(final_header_ptr, &final_header, PACK);

	वापस 0;
पूर्ण

#घोषणा RETRIES 10

पूर्णांक sja1105_अटल_config_upload(काष्ठा sja1105_निजी *priv)
अणु
	अचिन्हित दीर्घ port_biपंचांगap = GENMASK_ULL(SJA1105_NUM_PORTS - 1, 0);
	काष्ठा sja1105_अटल_config *config = &priv->अटल_config;
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा device *dev = &priv->spidev->dev;
	काष्ठा sja1105_status status;
	पूर्णांक rc, retries = RETRIES;
	u8 *config_buf;
	पूर्णांक buf_len;

	buf_len = sja1105_अटल_config_get_length(config);
	config_buf = kसुस्मृति(buf_len, माप(अक्षर), GFP_KERNEL);
	अगर (!config_buf)
		वापस -ENOMEM;

	rc = अटल_config_buf_prepare_क्रम_upload(priv, config_buf, buf_len);
	अगर (rc < 0) अणु
		dev_err(dev, "Invalid config, cannot upload\n");
		rc = -EINVAL;
		जाओ out;
	पूर्ण
	/* Prevent PHY jabbering during चयन reset by inhibiting
	 * Tx on all ports and रुकोing क्रम current packet to drain.
	 * Otherwise, the PHY will see an unterminated Ethernet packet.
	 */
	rc = sja1105_inhibit_tx(priv, port_biपंचांगap, true);
	अगर (rc < 0) अणु
		dev_err(dev, "Failed to inhibit Tx on ports\n");
		rc = -ENXIO;
		जाओ out;
	पूर्ण
	/* Wait क्रम an eventual egress packet to finish transmission
	 * (reach IFG). It is guaranteed that a second one will not
	 * follow, and that चयन cold reset is thus safe
	 */
	usleep_range(500, 1000);
	करो अणु
		/* Put the SJA1105 in programming mode */
		rc = priv->info->reset_cmd(priv->ds);
		अगर (rc < 0) अणु
			dev_err(dev, "Failed to reset switch, retrying...\n");
			जारी;
		पूर्ण
		/* Wait क्रम the चयन to come out of reset */
		usleep_range(1000, 5000);
		/* Upload the अटल config to the device */
		rc = sja1105_xfer_buf(priv, SPI_WRITE, regs->config,
				      config_buf, buf_len);
		अगर (rc < 0) अणु
			dev_err(dev, "Failed to upload config, retrying...\n");
			जारी;
		पूर्ण
		/* Check that SJA1105 responded well to the config upload */
		rc = sja1105_status_get(priv, &status);
		अगर (rc < 0)
			जारी;

		अगर (status.ids == 1) अणु
			dev_err(dev, "Mismatch between hardware and static config "
				"device id. Wrote 0x%llx, wants 0x%llx\n",
				config->device_id, priv->info->device_id);
			जारी;
		पूर्ण
		अगर (status.crcchkl == 1) अणु
			dev_err(dev, "Switch reported invalid local CRC on "
				"the uploaded config, retrying...\n");
			जारी;
		पूर्ण
		अगर (status.crcchkg == 1) अणु
			dev_err(dev, "Switch reported invalid global CRC on "
				"the uploaded config, retrying...\n");
			जारी;
		पूर्ण
		अगर (status.configs == 0) अणु
			dev_err(dev, "Switch reported that configuration is "
				"invalid, retrying...\n");
			जारी;
		पूर्ण
		/* Success! */
		अवरोध;
	पूर्ण जबतक (--retries);

	अगर (!retries) अणु
		rc = -EIO;
		dev_err(dev, "Failed to upload config to device, giving up\n");
		जाओ out;
	पूर्ण अन्यथा अगर (retries != RETRIES) अणु
		dev_info(dev, "Succeeded after %d tried\n", RETRIES - retries);
	पूर्ण

out:
	kमुक्त(config_buf);
	वापस rc;
पूर्ण

अटल काष्ठा sja1105_regs sja1105et_regs = अणु
	.device_id = 0x0,
	.prod_id = 0x100BC3,
	.status = 0x1,
	.port_control = 0x11,
	.vl_status = 0x10000,
	.config = 0x020000,
	.rgu = 0x100440,
	/* UM10944.pdf, Table 86, ACU Register overview */
	.pad_mii_tx = अणु0x100800, 0x100802, 0x100804, 0x100806, 0x100808पूर्ण,
	.pad_mii_rx = अणु0x100801, 0x100803, 0x100805, 0x100807, 0x100809पूर्ण,
	.rmii_pll1 = 0x10000A,
	.cgu_iभाग = अणु0x10000B, 0x10000C, 0x10000D, 0x10000E, 0x10000Fपूर्ण,
	.mac = अणु0x200, 0x202, 0x204, 0x206, 0x208पूर्ण,
	.mac_hl1 = अणु0x400, 0x410, 0x420, 0x430, 0x440पूर्ण,
	.mac_hl2 = अणु0x600, 0x610, 0x620, 0x630, 0x640पूर्ण,
	/* UM10944.pdf, Table 78, CGU Register overview */
	.mii_tx_clk = अणु0x100013, 0x10001A, 0x100021, 0x100028, 0x10002Fपूर्ण,
	.mii_rx_clk = अणु0x100014, 0x10001B, 0x100022, 0x100029, 0x100030पूर्ण,
	.mii_ext_tx_clk = अणु0x100018, 0x10001F, 0x100026, 0x10002D, 0x100034पूर्ण,
	.mii_ext_rx_clk = अणु0x100019, 0x100020, 0x100027, 0x10002E, 0x100035पूर्ण,
	.rgmii_tx_clk = अणु0x100016, 0x10001D, 0x100024, 0x10002B, 0x100032पूर्ण,
	.rmii_ref_clk = अणु0x100015, 0x10001C, 0x100023, 0x10002A, 0x100031पूर्ण,
	.rmii_ext_tx_clk = अणु0x100018, 0x10001F, 0x100026, 0x10002D, 0x100034पूर्ण,
	.ptpegr_ts = अणु0xC0, 0xC2, 0xC4, 0xC6, 0xC8पूर्ण,
	.ptpschपंचांग = 0x12, /* Spans 0x12 to 0x13 */
	.ptppinst = 0x14,
	.ptppindur = 0x16,
	.ptp_control = 0x17,
	.ptpclkval = 0x18, /* Spans 0x18 to 0x19 */
	.ptpclkrate = 0x1A,
	.ptpclkcorp = 0x1D,
पूर्ण;

अटल काष्ठा sja1105_regs sja1105pqrs_regs = अणु
	.device_id = 0x0,
	.prod_id = 0x100BC3,
	.status = 0x1,
	.port_control = 0x12,
	.vl_status = 0x10000,
	.config = 0x020000,
	.rgu = 0x100440,
	/* UM10944.pdf, Table 86, ACU Register overview */
	.pad_mii_tx = अणु0x100800, 0x100802, 0x100804, 0x100806, 0x100808पूर्ण,
	.pad_mii_rx = अणु0x100801, 0x100803, 0x100805, 0x100807, 0x100809पूर्ण,
	.pad_mii_id = अणु0x100810, 0x100811, 0x100812, 0x100813, 0x100814पूर्ण,
	.sgmii = 0x1F0000,
	.rmii_pll1 = 0x10000A,
	.cgu_iभाग = अणु0x10000B, 0x10000C, 0x10000D, 0x10000E, 0x10000Fपूर्ण,
	.mac = अणु0x200, 0x202, 0x204, 0x206, 0x208पूर्ण,
	.mac_hl1 = अणु0x400, 0x410, 0x420, 0x430, 0x440पूर्ण,
	.mac_hl2 = अणु0x600, 0x610, 0x620, 0x630, 0x640पूर्ण,
	.ether_stats = अणु0x1400, 0x1418, 0x1430, 0x1448, 0x1460पूर्ण,
	/* UM11040.pdf, Table 114 */
	.mii_tx_clk = अणु0x100013, 0x100019, 0x10001F, 0x100025, 0x10002Bपूर्ण,
	.mii_rx_clk = अणु0x100014, 0x10001A, 0x100020, 0x100026, 0x10002Cपूर्ण,
	.mii_ext_tx_clk = अणु0x100017, 0x10001D, 0x100023, 0x100029, 0x10002Fपूर्ण,
	.mii_ext_rx_clk = अणु0x100018, 0x10001E, 0x100024, 0x10002A, 0x100030पूर्ण,
	.rgmii_tx_clk = अणु0x100016, 0x10001C, 0x100022, 0x100028, 0x10002Eपूर्ण,
	.rmii_ref_clk = अणु0x100015, 0x10001B, 0x100021, 0x100027, 0x10002Dपूर्ण,
	.rmii_ext_tx_clk = अणु0x100017, 0x10001D, 0x100023, 0x100029, 0x10002Fपूर्ण,
	.qlevel = अणु0x604, 0x614, 0x624, 0x634, 0x644पूर्ण,
	.ptpegr_ts = अणु0xC0, 0xC4, 0xC8, 0xCC, 0xD0पूर्ण,
	.ptpschपंचांग = 0x13, /* Spans 0x13 to 0x14 */
	.ptppinst = 0x15,
	.ptppindur = 0x17,
	.ptp_control = 0x18,
	.ptpclkval = 0x19,
	.ptpclkrate = 0x1B,
	.ptpclkcorp = 0x1E,
	.ptpsyncts = 0x1F,
पूर्ण;

स्थिर काष्ठा sja1105_info sja1105e_info = अणु
	.device_id		= SJA1105E_DEVICE_ID,
	.part_no		= SJA1105ET_PART_NO,
	.अटल_ops		= sja1105e_table_ops,
	.dyn_ops		= sja1105et_dyn_ops,
	.qinq_tpid		= ETH_P_8021Q,
	.can_limit_mcast_flood	= false,
	.ptp_ts_bits		= 24,
	.ptpegr_ts_bytes	= 4,
	.num_cbs_shapers	= SJA1105ET_MAX_CBS_COUNT,
	.reset_cmd		= sja1105et_reset_cmd,
	.fdb_add_cmd		= sja1105et_fdb_add,
	.fdb_del_cmd		= sja1105et_fdb_del,
	.ptp_cmd_packing	= sja1105et_ptp_cmd_packing,
	.regs			= &sja1105et_regs,
	.name			= "SJA1105E",
पूर्ण;

स्थिर काष्ठा sja1105_info sja1105t_info = अणु
	.device_id		= SJA1105T_DEVICE_ID,
	.part_no		= SJA1105ET_PART_NO,
	.अटल_ops		= sja1105t_table_ops,
	.dyn_ops		= sja1105et_dyn_ops,
	.qinq_tpid		= ETH_P_8021Q,
	.can_limit_mcast_flood	= false,
	.ptp_ts_bits		= 24,
	.ptpegr_ts_bytes	= 4,
	.num_cbs_shapers	= SJA1105ET_MAX_CBS_COUNT,
	.reset_cmd		= sja1105et_reset_cmd,
	.fdb_add_cmd		= sja1105et_fdb_add,
	.fdb_del_cmd		= sja1105et_fdb_del,
	.ptp_cmd_packing	= sja1105et_ptp_cmd_packing,
	.regs			= &sja1105et_regs,
	.name			= "SJA1105T",
पूर्ण;

स्थिर काष्ठा sja1105_info sja1105p_info = अणु
	.device_id		= SJA1105PR_DEVICE_ID,
	.part_no		= SJA1105P_PART_NO,
	.अटल_ops		= sja1105p_table_ops,
	.dyn_ops		= sja1105pqrs_dyn_ops,
	.qinq_tpid		= ETH_P_8021AD,
	.can_limit_mcast_flood	= true,
	.ptp_ts_bits		= 32,
	.ptpegr_ts_bytes	= 8,
	.num_cbs_shapers	= SJA1105PQRS_MAX_CBS_COUNT,
	.setup_rgmii_delay	= sja1105pqrs_setup_rgmii_delay,
	.reset_cmd		= sja1105pqrs_reset_cmd,
	.fdb_add_cmd		= sja1105pqrs_fdb_add,
	.fdb_del_cmd		= sja1105pqrs_fdb_del,
	.ptp_cmd_packing	= sja1105pqrs_ptp_cmd_packing,
	.regs			= &sja1105pqrs_regs,
	.name			= "SJA1105P",
पूर्ण;

स्थिर काष्ठा sja1105_info sja1105q_info = अणु
	.device_id		= SJA1105QS_DEVICE_ID,
	.part_no		= SJA1105Q_PART_NO,
	.अटल_ops		= sja1105q_table_ops,
	.dyn_ops		= sja1105pqrs_dyn_ops,
	.qinq_tpid		= ETH_P_8021AD,
	.can_limit_mcast_flood	= true,
	.ptp_ts_bits		= 32,
	.ptpegr_ts_bytes	= 8,
	.num_cbs_shapers	= SJA1105PQRS_MAX_CBS_COUNT,
	.setup_rgmii_delay	= sja1105pqrs_setup_rgmii_delay,
	.reset_cmd		= sja1105pqrs_reset_cmd,
	.fdb_add_cmd		= sja1105pqrs_fdb_add,
	.fdb_del_cmd		= sja1105pqrs_fdb_del,
	.ptp_cmd_packing	= sja1105pqrs_ptp_cmd_packing,
	.regs			= &sja1105pqrs_regs,
	.name			= "SJA1105Q",
पूर्ण;

स्थिर काष्ठा sja1105_info sja1105r_info = अणु
	.device_id		= SJA1105PR_DEVICE_ID,
	.part_no		= SJA1105R_PART_NO,
	.अटल_ops		= sja1105r_table_ops,
	.dyn_ops		= sja1105pqrs_dyn_ops,
	.qinq_tpid		= ETH_P_8021AD,
	.can_limit_mcast_flood	= true,
	.ptp_ts_bits		= 32,
	.ptpegr_ts_bytes	= 8,
	.num_cbs_shapers	= SJA1105PQRS_MAX_CBS_COUNT,
	.setup_rgmii_delay	= sja1105pqrs_setup_rgmii_delay,
	.reset_cmd		= sja1105pqrs_reset_cmd,
	.fdb_add_cmd		= sja1105pqrs_fdb_add,
	.fdb_del_cmd		= sja1105pqrs_fdb_del,
	.ptp_cmd_packing	= sja1105pqrs_ptp_cmd_packing,
	.regs			= &sja1105pqrs_regs,
	.name			= "SJA1105R",
पूर्ण;

स्थिर काष्ठा sja1105_info sja1105s_info = अणु
	.device_id		= SJA1105QS_DEVICE_ID,
	.part_no		= SJA1105S_PART_NO,
	.अटल_ops		= sja1105s_table_ops,
	.dyn_ops		= sja1105pqrs_dyn_ops,
	.regs			= &sja1105pqrs_regs,
	.qinq_tpid		= ETH_P_8021AD,
	.can_limit_mcast_flood	= true,
	.ptp_ts_bits		= 32,
	.ptpegr_ts_bytes	= 8,
	.num_cbs_shapers	= SJA1105PQRS_MAX_CBS_COUNT,
	.setup_rgmii_delay	= sja1105pqrs_setup_rgmii_delay,
	.reset_cmd		= sja1105pqrs_reset_cmd,
	.fdb_add_cmd		= sja1105pqrs_fdb_add,
	.fdb_del_cmd		= sja1105pqrs_fdb_del,
	.ptp_cmd_packing	= sja1105pqrs_ptp_cmd_packing,
	.name			= "SJA1105S",
पूर्ण;
