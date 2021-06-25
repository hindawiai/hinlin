<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register map access API - SPI AVMM support
//
// Copyright (C) 2018-2020 Intel Corporation. All rights reserved.

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

/*
 * This driver implements the regmap operations क्रम a generic SPI
 * master to access the रेजिस्टरs of the spi slave chip which has an
 * Avalone bus in it.
 *
 * The "SPI slave to Avalon Master Bridge" (spi-avmm) IP should be पूर्णांकegrated
 * in the spi slave chip. The IP acts as a bridge to convert encoded streams of
 * bytes from the host to the पूर्णांकernal रेजिस्टर पढ़ो/ग_लिखो on Avalon bus. In
 * order to issue रेजिस्टर access requests to the slave chip, the host should
 * send क्रमmatted bytes that conक्रमm to the transfer protocol.
 * The transfer protocol contains 3 layers: transaction layer, packet layer
 * and physical layer.
 *
 * Reference Documents could be found at:
 * https://www.पूर्णांकel.com/content/www/us/en/programmable/करोcumentation/sfo1400787952932.hपंचांगl
 *
 * Chapter "SPI Slave/JTAG to Avalon Master Bridge Cores" is a general
 * पूर्णांकroduction to the protocol.
 *
 * Chapter "Avalon Packets to Transactions Converter Core" describes
 * the transaction layer.
 *
 * Chapter "Avalon-ST Bytes to Packets and Packets to Bytes Converter Cores"
 * describes the packet layer.
 *
 * Chapter "Avalon-ST Serial Peripheral Interface Core" describes the
 * physical layer.
 *
 *
 * When host issues a regmap पढ़ो/ग_लिखो, the driver will transक्रमm the request
 * to byte stream layer by layer. It क्रमmats the रेजिस्टर addr, value and
 * length to the transaction layer request, then converts the request to packet
 * layer bytes stream and then to physical layer bytes stream. Finally the
 * driver sends the क्रमmatted byte stream over SPI bus to the slave chip.
 *
 * The spi-avmm IP on the slave chip decodes the byte stream and initiates
 * रेजिस्टर पढ़ो/ग_लिखो on its पूर्णांकernal Avalon bus, and then encodes the
 * response to byte stream and sends back to host.
 *
 * The driver receives the byte stream, reverses the 3 layers transक्रमmation,
 * and finally माला_लो the response value (पढ़ो out data क्रम रेजिस्टर पढ़ो,
 * successful written size क्रम रेजिस्टर ग_लिखो).
 */

#घोषणा PKT_SOP			0x7a
#घोषणा PKT_EOP			0x7b
#घोषणा PKT_CHANNEL		0x7c
#घोषणा PKT_ESC			0x7d

#घोषणा PHY_IDLE		0x4a
#घोषणा PHY_ESC			0x4d

#घोषणा TRANS_CODE_WRITE	0x0
#घोषणा TRANS_CODE_SEQ_WRITE	0x4
#घोषणा TRANS_CODE_READ		0x10
#घोषणा TRANS_CODE_SEQ_READ	0x14
#घोषणा TRANS_CODE_NO_TRANS	0x7f

#घोषणा SPI_AVMM_XFER_TIMEOUT	(msecs_to_jअगरfies(200))

/* slave's रेजिस्टर addr is 32 bits */
#घोषणा SPI_AVMM_REG_SIZE		4UL
/* slave's रेजिस्टर value is 32 bits */
#घोषणा SPI_AVMM_VAL_SIZE		4UL

/*
 * max rx size could be larger. But considering the buffer consuming,
 * it is proper that we limit 1KB xfer at max.
 */
#घोषणा MAX_READ_CNT		256UL
#घोषणा MAX_WRITE_CNT		1UL

काष्ठा trans_req_header अणु
	u8 code;
	u8 rsvd;
	__be16 size;
	__be32 addr;
पूर्ण __packed;

काष्ठा trans_resp_header अणु
	u8 r_code;
	u8 rsvd;
	__be16 size;
पूर्ण __packed;

#घोषणा TRANS_REQ_HD_SIZE	(माप(काष्ठा trans_req_header))
#घोषणा TRANS_RESP_HD_SIZE	(माप(काष्ठा trans_resp_header))

/*
 * In transaction layer,
 * the ग_लिखो request क्रमmat is: Transaction request header + data
 * the पढ़ो request क्रमmat is: Transaction request header
 * the ग_लिखो response क्रमmat is: Transaction response header
 * the पढ़ो response क्रमmat is: pure data, no Transaction response header
 */
#घोषणा TRANS_WR_TX_SIZE(n)	(TRANS_REQ_HD_SIZE + SPI_AVMM_VAL_SIZE * (n))
#घोषणा TRANS_RD_TX_SIZE	TRANS_REQ_HD_SIZE
#घोषणा TRANS_TX_MAX		TRANS_WR_TX_SIZE(MAX_WRITE_CNT)

#घोषणा TRANS_RD_RX_SIZE(n)	(SPI_AVMM_VAL_SIZE * (n))
#घोषणा TRANS_WR_RX_SIZE	TRANS_RESP_HD_SIZE
#घोषणा TRANS_RX_MAX		TRANS_RD_RX_SIZE(MAX_READ_CNT)

/* tx & rx share one transaction layer buffer */
#घोषणा TRANS_BUF_SIZE		((TRANS_TX_MAX > TRANS_RX_MAX) ?	\
				 TRANS_TX_MAX : TRANS_RX_MAX)

/*
 * In tx phase, the host prepares all the phy layer bytes of a request in the
 * phy buffer and sends them in a batch.
 *
 * The packet layer and physical layer defines several special अक्षरs क्रम
 * various purpose, when a transaction layer byte hits one of these special
 * अक्षरs, it should be escaped. The escape rule is, "Escape अक्षर first,
 * following the byte XOR'ed with 0x20".
 *
 * This macro defines the max possible length of the phy data. In the worst
 * हाल, all transaction layer bytes need to be escaped (so the data length
 * द्विगुनs), plus 4 special अक्षरs (SOP, CHANNEL, CHANNEL_NUM, EOP). Finally
 * we should make sure the length is aligned to SPI BPW.
 */
#घोषणा PHY_TX_MAX		ALIGN(2 * TRANS_TX_MAX + 4, 4)

/*
 * Unlike tx, phy rx is affected by possible PHY_IDLE bytes from slave, the max
 * length of the rx bit stream is unpredictable. So the driver पढ़ोs the words
 * one by one, and parses each word immediately पूर्णांकo transaction layer buffer.
 * Only one word length of phy buffer is used क्रम rx.
 */
#घोषणा PHY_BUF_SIZE		PHY_TX_MAX

/**
 * काष्ठा spi_avmm_bridge - SPI slave to AVMM bus master bridge
 *
 * @spi: spi slave associated with this bridge.
 * @word_len: bytes of word क्रम spi transfer.
 * @trans_len: length of valid data in trans_buf.
 * @phy_len: length of valid data in phy_buf.
 * @trans_buf: the bridge buffer क्रम transaction layer data.
 * @phy_buf: the bridge buffer क्रम physical layer data.
 * @swap_words: the word swapping cb क्रम phy data. शून्य अगर not needed.
 *
 * As a device's रेजिस्टरs are implemented on the AVMM bus address space, it
 * requires the driver to issue क्रमmatted requests to spi slave to AVMM bus
 * master bridge to perक्रमm रेजिस्टर access.
 */
काष्ठा spi_avmm_bridge अणु
	काष्ठा spi_device *spi;
	अचिन्हित अक्षर word_len;
	अचिन्हित पूर्णांक trans_len;
	अचिन्हित पूर्णांक phy_len;
	/* bridge buffer used in translation between protocol layers */
	अक्षर trans_buf[TRANS_BUF_SIZE];
	अक्षर phy_buf[PHY_BUF_SIZE];
	व्योम (*swap_words)(अक्षर *buf, अचिन्हित पूर्णांक len);
पूर्ण;

अटल व्योम br_swap_words_32(अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	u32 *p = (u32 *)buf;
	अचिन्हित पूर्णांक count;

	count = len / 4;
	जबतक (count--) अणु
		*p = swab32p(p);
		p++;
	पूर्ण
पूर्ण

/*
 * Format transaction layer data in br->trans_buf according to the रेजिस्टर
 * access request, Store valid transaction layer data length in br->trans_len.
 */
अटल पूर्णांक br_trans_tx_prepare(काष्ठा spi_avmm_bridge *br, bool is_पढ़ो, u32 reg,
			       u32 *wr_val, u32 count)
अणु
	काष्ठा trans_req_header *header;
	अचिन्हित पूर्णांक trans_len;
	u8 code;
	__le32 *data;
	पूर्णांक i;

	अगर (is_पढ़ो) अणु
		अगर (count == 1)
			code = TRANS_CODE_READ;
		अन्यथा
			code = TRANS_CODE_SEQ_READ;
	पूर्ण अन्यथा अणु
		अगर (count == 1)
			code = TRANS_CODE_WRITE;
		अन्यथा
			code = TRANS_CODE_SEQ_WRITE;
	पूर्ण

	header = (काष्ठा trans_req_header *)br->trans_buf;
	header->code = code;
	header->rsvd = 0;
	header->size = cpu_to_be16((u16)count * SPI_AVMM_VAL_SIZE);
	header->addr = cpu_to_be32(reg);

	trans_len = TRANS_REQ_HD_SIZE;

	अगर (!is_पढ़ो) अणु
		trans_len += SPI_AVMM_VAL_SIZE * count;
		अगर (trans_len > माप(br->trans_buf))
			वापस -ENOMEM;

		data = (__le32 *)(br->trans_buf + TRANS_REQ_HD_SIZE);

		क्रम (i = 0; i < count; i++)
			*data++ = cpu_to_le32(*wr_val++);
	पूर्ण

	/* Store valid trans data length क्रम next layer */
	br->trans_len = trans_len;

	वापस 0;
पूर्ण

/*
 * Convert transaction layer data (in br->trans_buf) to phy layer data, store
 * them in br->phy_buf. Pad the phy_buf aligned with SPI's BPW. Store valid phy
 * layer data length in br->phy_len.
 *
 * phy_buf len should be aligned with SPI's BPW. Spare bytes should be padded
 * with PHY_IDLE, then the slave will just drop them.
 *
 * The driver will not simply pad 4a at the tail. The concern is that driver
 * will not store MISO data during tx phase, अगर the driver pads 4a at the tail,
 * it is possible that अगर the slave is fast enough to response at the padding
 * समय. As a result these rx bytes are lost. In the following हाल, 7a,7c,00
 * will lost.
 * MOSI ...|7a|7c|00|10| |00|00|04|02| |4b|7d|5a|7b| |40|4a|4a|4a| |XX|XX|...
 * MISO ...|4a|4a|4a|4a| |4a|4a|4a|4a| |4a|4a|4a|4a| |4a|7a|7c|00| |78|56|...
 *
 * So the driver moves EOP and bytes after EOP to the end of the aligned size,
 * then fill the hole with PHY_IDLE. As following:
 * beक्रमe pad ...|7a|7c|00|10| |00|00|04|02| |4b|7d|5a|7b| |40|
 * after pad  ...|7a|7c|00|10| |00|00|04|02| |4b|7d|5a|4a| |4a|4a|7b|40|
 * Then अगर the slave will not get the entire packet beक्रमe the tx phase is
 * over, it can't responsed to anything either.
 */
अटल पूर्णांक br_pkt_phy_tx_prepare(काष्ठा spi_avmm_bridge *br)
अणु
	अक्षर *tb, *tb_end, *pb, *pb_limit, *pb_eop = शून्य;
	अचिन्हित पूर्णांक aligned_phy_len, move_size;
	bool need_esc = false;

	tb = br->trans_buf;
	tb_end = tb + br->trans_len;
	pb = br->phy_buf;
	pb_limit = pb + ARRAY_SIZE(br->phy_buf);

	*pb++ = PKT_SOP;

	/*
	 * The driver करोesn't support multiple channels so the channel number
	 * is always 0.
	 */
	*pb++ = PKT_CHANNEL;
	*pb++ = 0x0;

	क्रम (; pb < pb_limit && tb < tb_end; pb++) अणु
		अगर (need_esc) अणु
			*pb = *tb++ ^ 0x20;
			need_esc = false;
			जारी;
		पूर्ण

		/* EOP should be inserted beक्रमe the last valid अक्षर */
		अगर (tb == tb_end - 1 && !pb_eop) अणु
			*pb = PKT_EOP;
			pb_eop = pb;
			जारी;
		पूर्ण

		/*
		 * insert an ESCAPE अक्षर अगर the data value equals any special
		 * अक्षर.
		 */
		चयन (*tb) अणु
		हाल PKT_SOP:
		हाल PKT_EOP:
		हाल PKT_CHANNEL:
		हाल PKT_ESC:
			*pb = PKT_ESC;
			need_esc = true;
			अवरोध;
		हाल PHY_IDLE:
		हाल PHY_ESC:
			*pb = PHY_ESC;
			need_esc = true;
			अवरोध;
		शेष:
			*pb = *tb++;
			अवरोध;
		पूर्ण
	पूर्ण

	/* The phy buffer is used out but transaction layer data reमुख्यs */
	अगर (tb < tb_end)
		वापस -ENOMEM;

	/* Store valid phy data length क्रम spi transfer */
	br->phy_len = pb - br->phy_buf;

	अगर (br->word_len == 1)
		वापस 0;

	/* Do phy buf padding अगर word_len > 1 byte. */
	aligned_phy_len = ALIGN(br->phy_len, br->word_len);
	अगर (aligned_phy_len > माप(br->phy_buf))
		वापस -ENOMEM;

	अगर (aligned_phy_len == br->phy_len)
		वापस 0;

	/* move EOP and bytes after EOP to the end of aligned size */
	move_size = pb - pb_eop;
	स_हटाओ(&br->phy_buf[aligned_phy_len - move_size], pb_eop, move_size);

	/* fill the hole with PHY_IDLEs */
	स_रखो(pb_eop, PHY_IDLE, aligned_phy_len - br->phy_len);

	/* update the phy data length */
	br->phy_len = aligned_phy_len;

	वापस 0;
पूर्ण

/*
 * In tx phase, the slave only वापसs PHY_IDLE (0x4a). So the driver will
 * ignore rx in tx phase.
 */
अटल पूर्णांक br_करो_tx(काष्ठा spi_avmm_bridge *br)
अणु
	/* reorder words क्रम spi transfer */
	अगर (br->swap_words)
		br->swap_words(br->phy_buf, br->phy_len);

	/* send all data in phy_buf  */
	वापस spi_ग_लिखो(br->spi, br->phy_buf, br->phy_len);
पूर्ण

/*
 * This function पढ़ो the rx byte stream from SPI word by word and convert
 * them to transaction layer data in br->trans_buf. It also stores the length
 * of rx transaction layer data in br->trans_len
 *
 * The slave may send an unknown number of PHY_IDLEs in rx phase, so we cannot
 * prepare a fixed length buffer to receive all of the rx data in a batch. We
 * have to पढ़ो word by word and convert them to transaction layer data at
 * once.
 */
अटल पूर्णांक br_करो_rx_and_pkt_phy_parse(काष्ठा spi_avmm_bridge *br)
अणु
	bool eop_found = false, channel_found = false, esc_found = false;
	bool valid_word = false, last_try = false;
	काष्ठा device *dev = &br->spi->dev;
	अक्षर *pb, *tb_limit, *tb = शून्य;
	अचिन्हित दीर्घ poll_समयout;
	पूर्णांक ret, i;

	tb_limit = br->trans_buf + ARRAY_SIZE(br->trans_buf);
	pb = br->phy_buf;
	poll_समयout = jअगरfies + SPI_AVMM_XFER_TIMEOUT;
	जबतक (tb < tb_limit) अणु
		ret = spi_पढ़ो(br->spi, pb, br->word_len);
		अगर (ret)
			वापस ret;

		/* reorder the word back */
		अगर (br->swap_words)
			br->swap_words(pb, br->word_len);

		valid_word = false;
		क्रम (i = 0; i < br->word_len; i++) अणु
			/* drop everything beक्रमe first SOP */
			अगर (!tb && pb[i] != PKT_SOP)
				जारी;

			/* drop PHY_IDLE */
			अगर (pb[i] == PHY_IDLE)
				जारी;

			valid_word = true;

			/*
			 * We करोn't support multiple channels, so error out अगर
			 * a non-zero channel number is found.
			 */
			अगर (channel_found) अणु
				अगर (pb[i] != 0) अणु
					dev_err(dev, "%s channel num != 0\n",
						__func__);
					वापस -EFAULT;
				पूर्ण

				channel_found = false;
				जारी;
			पूर्ण

			चयन (pb[i]) अणु
			हाल PKT_SOP:
				/*
				 * reset the parsing अगर a second SOP appears.
				 */
				tb = br->trans_buf;
				eop_found = false;
				channel_found = false;
				esc_found = false;
				अवरोध;
			हाल PKT_EOP:
				/*
				 * No special अक्षर is expected after ESC अक्षर.
				 * No special अक्षर (except ESC & PHY_IDLE) is
				 * expected after EOP अक्षर.
				 *
				 * The special अक्षरs are all dropped.
				 */
				अगर (esc_found || eop_found)
					वापस -EFAULT;

				eop_found = true;
				अवरोध;
			हाल PKT_CHANNEL:
				अगर (esc_found || eop_found)
					वापस -EFAULT;

				channel_found = true;
				अवरोध;
			हाल PKT_ESC:
			हाल PHY_ESC:
				अगर (esc_found)
					वापस -EFAULT;

				esc_found = true;
				अवरोध;
			शेष:
				/* Record the normal byte in trans_buf. */
				अगर (esc_found) अणु
					*tb++ = pb[i] ^ 0x20;
					esc_found = false;
				पूर्ण अन्यथा अणु
					*tb++ = pb[i];
				पूर्ण

				/*
				 * We get the last normal byte after EOP, it is
				 * समय we finish. Normally the function should
				 * वापस here.
				 */
				अगर (eop_found) अणु
					br->trans_len = tb - br->trans_buf;
					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (valid_word) अणु
			/* update poll समयout when we get valid word */
			poll_समयout = jअगरfies + SPI_AVMM_XFER_TIMEOUT;
			last_try = false;
		पूर्ण अन्यथा अणु
			/*
			 * We समयout when rx keeps invalid क्रम some समय. But
			 * it is possible we are scheduled out क्रम दीर्घ समय
			 * after a spi_पढ़ो. So when we are scheduled in, a SW
			 * समयout happens. But actually HW may have worked fine and
			 * has been पढ़ोy दीर्घ समय ago. So we need to करो an extra
			 * पढ़ो, अगर we get a valid word then we could जारी rx,
			 * otherwise real a HW issue happens.
			 */
			अगर (last_try)
				वापस -ETIMEDOUT;

			अगर (समय_after(jअगरfies, poll_समयout))
				last_try = true;
		पूर्ण
	पूर्ण

	/*
	 * We have used out all transfer layer buffer but cannot find the end
	 * of the byte stream.
	 */
	dev_err(dev, "%s transfer buffer is full but rx doesn't end\n",
		__func__);

	वापस -EFAULT;
पूर्ण

/*
 * For पढ़ो transactions, the avmm bus will directly वापस रेजिस्टर values
 * without transaction response header.
 */
अटल पूर्णांक br_rd_trans_rx_parse(काष्ठा spi_avmm_bridge *br,
				u32 *val, अचिन्हित पूर्णांक expected_count)
अणु
	अचिन्हित पूर्णांक i, trans_len = br->trans_len;
	__le32 *data;

	अगर (expected_count * SPI_AVMM_VAL_SIZE != trans_len)
		वापस -EFAULT;

	data = (__le32 *)br->trans_buf;
	क्रम (i = 0; i < expected_count; i++)
		*val++ = le32_to_cpu(*data++);

	वापस 0;
पूर्ण

/*
 * For ग_लिखो transactions, the slave will वापस a transaction response
 * header.
 */
अटल पूर्णांक br_wr_trans_rx_parse(काष्ठा spi_avmm_bridge *br,
				अचिन्हित पूर्णांक expected_count)
अणु
	अचिन्हित पूर्णांक trans_len = br->trans_len;
	काष्ठा trans_resp_header *resp;
	u8 code;
	u16 val_len;

	अगर (trans_len != TRANS_RESP_HD_SIZE)
		वापस -EFAULT;

	resp = (काष्ठा trans_resp_header *)br->trans_buf;

	code = resp->r_code ^ 0x80;
	val_len = be16_to_cpu(resp->size);
	अगर (!val_len || val_len != expected_count * SPI_AVMM_VAL_SIZE)
		वापस -EFAULT;

	/* error out अगर the trans code करोesn't align with the val size */
	अगर ((val_len == SPI_AVMM_VAL_SIZE && code != TRANS_CODE_WRITE) ||
	    (val_len > SPI_AVMM_VAL_SIZE && code != TRANS_CODE_SEQ_WRITE))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक करो_reg_access(व्योम *context, bool is_पढ़ो, अचिन्हित पूर्णांक reg,
			 अचिन्हित पूर्णांक *value, अचिन्हित पूर्णांक count)
अणु
	काष्ठा spi_avmm_bridge *br = context;
	पूर्णांक ret;

	/* invalidate bridge buffers first */
	br->trans_len = 0;
	br->phy_len = 0;

	ret = br_trans_tx_prepare(br, is_पढ़ो, reg, value, count);
	अगर (ret)
		वापस ret;

	ret = br_pkt_phy_tx_prepare(br);
	अगर (ret)
		वापस ret;

	ret = br_करो_tx(br);
	अगर (ret)
		वापस ret;

	ret = br_करो_rx_and_pkt_phy_parse(br);
	अगर (ret)
		वापस ret;

	अगर (is_पढ़ो)
		वापस br_rd_trans_rx_parse(br, value, count);
	अन्यथा
		वापस br_wr_trans_rx_parse(br, count);
पूर्ण

अटल पूर्णांक regmap_spi_avmm_gather_ग_लिखो(व्योम *context,
					स्थिर व्योम *reg_buf, माप_प्रकार reg_len,
					स्थिर व्योम *val_buf, माप_प्रकार val_len)
अणु
	अगर (reg_len != SPI_AVMM_REG_SIZE)
		वापस -EINVAL;

	अगर (!IS_ALIGNED(val_len, SPI_AVMM_VAL_SIZE))
		वापस -EINVAL;

	वापस करो_reg_access(context, false, *(u32 *)reg_buf, (u32 *)val_buf,
			     val_len / SPI_AVMM_VAL_SIZE);
पूर्ण

अटल पूर्णांक regmap_spi_avmm_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार bytes)
अणु
	अगर (bytes < SPI_AVMM_REG_SIZE + SPI_AVMM_VAL_SIZE)
		वापस -EINVAL;

	वापस regmap_spi_avmm_gather_ग_लिखो(context, data, SPI_AVMM_REG_SIZE,
					    data + SPI_AVMM_REG_SIZE,
					    bytes - SPI_AVMM_REG_SIZE);
पूर्ण

अटल पूर्णांक regmap_spi_avmm_पढ़ो(व्योम *context,
				स्थिर व्योम *reg_buf, माप_प्रकार reg_len,
				व्योम *val_buf, माप_प्रकार val_len)
अणु
	अगर (reg_len != SPI_AVMM_REG_SIZE)
		वापस -EINVAL;

	अगर (!IS_ALIGNED(val_len, SPI_AVMM_VAL_SIZE))
		वापस -EINVAL;

	वापस करो_reg_access(context, true, *(u32 *)reg_buf, val_buf,
			     (val_len / SPI_AVMM_VAL_SIZE));
पूर्ण

अटल काष्ठा spi_avmm_bridge *
spi_avmm_bridge_ctx_gen(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_avmm_bridge *br;

	अगर (!spi)
		वापस ERR_PTR(-ENODEV);

	/* Only support BPW == 8 or 32 now. Try 32 BPW first. */
	spi->mode = SPI_MODE_1;
	spi->bits_per_word = 32;
	अगर (spi_setup(spi)) अणु
		spi->bits_per_word = 8;
		अगर (spi_setup(spi))
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	br = kzalloc(माप(*br), GFP_KERNEL);
	अगर (!br)
		वापस ERR_PTR(-ENOMEM);

	br->spi = spi;
	br->word_len = spi->bits_per_word / 8;
	अगर (br->word_len == 4) अणु
		/*
		 * The protocol requires little endian byte order but MSB
		 * first. So driver needs to swap the byte order word by word
		 * अगर word length > 1.
		 */
		br->swap_words = br_swap_words_32;
	पूर्ण

	वापस br;
पूर्ण

अटल व्योम spi_avmm_bridge_ctx_मुक्त(व्योम *context)
अणु
	kमुक्त(context);
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_spi_avmm_bus = अणु
	.ग_लिखो = regmap_spi_avmm_ग_लिखो,
	.gather_ग_लिखो = regmap_spi_avmm_gather_ग_लिखो,
	.पढ़ो = regmap_spi_avmm_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
	.max_raw_पढ़ो = SPI_AVMM_VAL_SIZE * MAX_READ_CNT,
	.max_raw_ग_लिखो = SPI_AVMM_VAL_SIZE * MAX_WRITE_CNT,
	.मुक्त_context = spi_avmm_bridge_ctx_मुक्त,
पूर्ण;

काष्ठा regmap *__regmap_init_spi_avmm(काष्ठा spi_device *spi,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name)
अणु
	काष्ठा spi_avmm_bridge *bridge;
	काष्ठा regmap *map;

	bridge = spi_avmm_bridge_ctx_gen(spi);
	अगर (IS_ERR(bridge))
		वापस ERR_CAST(bridge);

	map = __regmap_init(&spi->dev, &regmap_spi_avmm_bus,
			    bridge, config, lock_key, lock_name);
	अगर (IS_ERR(map)) अणु
		spi_avmm_bridge_ctx_मुक्त(bridge);
		वापस ERR_CAST(map);
	पूर्ण

	वापस map;
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_spi_avmm);

काष्ठा regmap *__devm_regmap_init_spi_avmm(काष्ठा spi_device *spi,
					   स्थिर काष्ठा regmap_config *config,
					   काष्ठा lock_class_key *lock_key,
					   स्थिर अक्षर *lock_name)
अणु
	काष्ठा spi_avmm_bridge *bridge;
	काष्ठा regmap *map;

	bridge = spi_avmm_bridge_ctx_gen(spi);
	अगर (IS_ERR(bridge))
		वापस ERR_CAST(bridge);

	map = __devm_regmap_init(&spi->dev, &regmap_spi_avmm_bus,
				 bridge, config, lock_key, lock_name);
	अगर (IS_ERR(map)) अणु
		spi_avmm_bridge_ctx_मुक्त(bridge);
		वापस ERR_CAST(map);
	पूर्ण

	वापस map;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_spi_avmm);

MODULE_LICENSE("GPL v2");
