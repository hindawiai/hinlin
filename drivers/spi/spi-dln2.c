<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Diolan DLN-2 USB-SPI adapter
 *
 * Copyright (c) 2014 Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/dln2.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <यंत्र/unaligned.h>

#घोषणा DLN2_SPI_MODULE_ID		0x02
#घोषणा DLN2_SPI_CMD(cmd)		DLN2_CMD(cmd, DLN2_SPI_MODULE_ID)

/* SPI commands */
#घोषणा DLN2_SPI_GET_PORT_COUNT			DLN2_SPI_CMD(0x00)
#घोषणा DLN2_SPI_ENABLE				DLN2_SPI_CMD(0x11)
#घोषणा DLN2_SPI_DISABLE			DLN2_SPI_CMD(0x12)
#घोषणा DLN2_SPI_IS_ENABLED			DLN2_SPI_CMD(0x13)
#घोषणा DLN2_SPI_SET_MODE			DLN2_SPI_CMD(0x14)
#घोषणा DLN2_SPI_GET_MODE			DLN2_SPI_CMD(0x15)
#घोषणा DLN2_SPI_SET_FRAME_SIZE			DLN2_SPI_CMD(0x16)
#घोषणा DLN2_SPI_GET_FRAME_SIZE			DLN2_SPI_CMD(0x17)
#घोषणा DLN2_SPI_SET_FREQUENCY			DLN2_SPI_CMD(0x18)
#घोषणा DLN2_SPI_GET_FREQUENCY			DLN2_SPI_CMD(0x19)
#घोषणा DLN2_SPI_READ_WRITE			DLN2_SPI_CMD(0x1A)
#घोषणा DLN2_SPI_READ				DLN2_SPI_CMD(0x1B)
#घोषणा DLN2_SPI_WRITE				DLN2_SPI_CMD(0x1C)
#घोषणा DLN2_SPI_SET_DELAY_BETWEEN_SS		DLN2_SPI_CMD(0x20)
#घोषणा DLN2_SPI_GET_DELAY_BETWEEN_SS		DLN2_SPI_CMD(0x21)
#घोषणा DLN2_SPI_SET_DELAY_AFTER_SS		DLN2_SPI_CMD(0x22)
#घोषणा DLN2_SPI_GET_DELAY_AFTER_SS		DLN2_SPI_CMD(0x23)
#घोषणा DLN2_SPI_SET_DELAY_BETWEEN_FRAMES	DLN2_SPI_CMD(0x24)
#घोषणा DLN2_SPI_GET_DELAY_BETWEEN_FRAMES	DLN2_SPI_CMD(0x25)
#घोषणा DLN2_SPI_SET_SS				DLN2_SPI_CMD(0x26)
#घोषणा DLN2_SPI_GET_SS				DLN2_SPI_CMD(0x27)
#घोषणा DLN2_SPI_RELEASE_SS			DLN2_SPI_CMD(0x28)
#घोषणा DLN2_SPI_SS_VARIABLE_ENABLE		DLN2_SPI_CMD(0x2B)
#घोषणा DLN2_SPI_SS_VARIABLE_DISABLE		DLN2_SPI_CMD(0x2C)
#घोषणा DLN2_SPI_SS_VARIABLE_IS_ENABLED		DLN2_SPI_CMD(0x2D)
#घोषणा DLN2_SPI_SS_AAT_ENABLE			DLN2_SPI_CMD(0x2E)
#घोषणा DLN2_SPI_SS_AAT_DISABLE			DLN2_SPI_CMD(0x2F)
#घोषणा DLN2_SPI_SS_AAT_IS_ENABLED		DLN2_SPI_CMD(0x30)
#घोषणा DLN2_SPI_SS_BETWEEN_FRAMES_ENABLE	DLN2_SPI_CMD(0x31)
#घोषणा DLN2_SPI_SS_BETWEEN_FRAMES_DISABLE	DLN2_SPI_CMD(0x32)
#घोषणा DLN2_SPI_SS_BETWEEN_FRAMES_IS_ENABLED	DLN2_SPI_CMD(0x33)
#घोषणा DLN2_SPI_SET_CPHA			DLN2_SPI_CMD(0x34)
#घोषणा DLN2_SPI_GET_CPHA			DLN2_SPI_CMD(0x35)
#घोषणा DLN2_SPI_SET_CPOL			DLN2_SPI_CMD(0x36)
#घोषणा DLN2_SPI_GET_CPOL			DLN2_SPI_CMD(0x37)
#घोषणा DLN2_SPI_SS_MULTI_ENABLE		DLN2_SPI_CMD(0x38)
#घोषणा DLN2_SPI_SS_MULTI_DISABLE		DLN2_SPI_CMD(0x39)
#घोषणा DLN2_SPI_SS_MULTI_IS_ENABLED		DLN2_SPI_CMD(0x3A)
#घोषणा DLN2_SPI_GET_SUPPORTED_MODES		DLN2_SPI_CMD(0x40)
#घोषणा DLN2_SPI_GET_SUPPORTED_CPHA_VALUES	DLN2_SPI_CMD(0x41)
#घोषणा DLN2_SPI_GET_SUPPORTED_CPOL_VALUES	DLN2_SPI_CMD(0x42)
#घोषणा DLN2_SPI_GET_SUPPORTED_FRAME_SIZES	DLN2_SPI_CMD(0x43)
#घोषणा DLN2_SPI_GET_SS_COUNT			DLN2_SPI_CMD(0x44)
#घोषणा DLN2_SPI_GET_MIN_FREQUENCY		DLN2_SPI_CMD(0x45)
#घोषणा DLN2_SPI_GET_MAX_FREQUENCY		DLN2_SPI_CMD(0x46)
#घोषणा DLN2_SPI_GET_MIN_DELAY_BETWEEN_SS	DLN2_SPI_CMD(0x47)
#घोषणा DLN2_SPI_GET_MAX_DELAY_BETWEEN_SS	DLN2_SPI_CMD(0x48)
#घोषणा DLN2_SPI_GET_MIN_DELAY_AFTER_SS		DLN2_SPI_CMD(0x49)
#घोषणा DLN2_SPI_GET_MAX_DELAY_AFTER_SS		DLN2_SPI_CMD(0x4A)
#घोषणा DLN2_SPI_GET_MIN_DELAY_BETWEEN_FRAMES	DLN2_SPI_CMD(0x4B)
#घोषणा DLN2_SPI_GET_MAX_DELAY_BETWEEN_FRAMES	DLN2_SPI_CMD(0x4C)

#घोषणा DLN2_SPI_MAX_XFER_SIZE			256
#घोषणा DLN2_SPI_BUF_SIZE			(DLN2_SPI_MAX_XFER_SIZE + 16)
#घोषणा DLN2_SPI_ATTR_LEAVE_SS_LOW		BIT(0)
#घोषणा DLN2_TRANSFERS_WAIT_COMPLETE		1
#घोषणा DLN2_TRANSFERS_CANCEL			0
#घोषणा DLN2_RPM_AUTOSUSPEND_TIMEOUT		2000

काष्ठा dln2_spi अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा spi_master *master;
	u8 port;

	/*
	 * This buffer will be used मुख्यly क्रम पढ़ो/ग_लिखो operations. Since
	 * they're quite large, we cannot use the stack. Protection is not
	 * needed because all SPI communication is serialized by the SPI core.
	 */
	व्योम *buf;

	u8 bpw;
	u32 speed;
	u16 mode;
	u8 cs;
पूर्ण;

/*
 * Enable/Disable SPI module. The disable command will रुको क्रम transfers to
 * complete first.
 */
अटल पूर्णांक dln2_spi_enable(काष्ठा dln2_spi *dln2, bool enable)
अणु
	u16 cmd;
	काष्ठा अणु
		u8 port;
		u8 रुको_क्रम_completion;
	पूर्ण tx;
	अचिन्हित len = माप(tx);

	tx.port = dln2->port;

	अगर (enable) अणु
		cmd = DLN2_SPI_ENABLE;
		len -= माप(tx.रुको_क्रम_completion);
	पूर्ण अन्यथा अणु
		tx.रुको_क्रम_completion = DLN2_TRANSFERS_WAIT_COMPLETE;
		cmd = DLN2_SPI_DISABLE;
	पूर्ण

	वापस dln2_transfer_tx(dln2->pdev, cmd, &tx, len);
पूर्ण

/*
 * Select/unselect multiple CS lines. The selected lines will be स्वतःmatically
 * toggled LOW/HIGH by the board firmware during transfers, provided they're
 * enabled first.
 *
 * Ex: cs_mask = 0x03 -> CS0 & CS1 will be selected and the next WR/RD operation
 *                       will toggle the lines LOW/HIGH स्वतःmatically.
 */
अटल पूर्णांक dln2_spi_cs_set(काष्ठा dln2_spi *dln2, u8 cs_mask)
अणु
	काष्ठा अणु
		u8 port;
		u8 cs;
	पूर्ण tx;

	tx.port = dln2->port;

	/*
	 * According to Diolan करोcs, "a slave device can be selected by changing
	 * the corresponding bit value to 0". The rest must be set to 1. Hence
	 * the bitwise NOT in front.
	 */
	tx.cs = ~cs_mask;

	वापस dln2_transfer_tx(dln2->pdev, DLN2_SPI_SET_SS, &tx, माप(tx));
पूर्ण

/*
 * Select one CS line. The other lines will be un-selected.
 */
अटल पूर्णांक dln2_spi_cs_set_one(काष्ठा dln2_spi *dln2, u8 cs)
अणु
	वापस dln2_spi_cs_set(dln2, BIT(cs));
पूर्ण

/*
 * Enable/disable CS lines क्रम usage. The module has to be disabled first.
 */
अटल पूर्णांक dln2_spi_cs_enable(काष्ठा dln2_spi *dln2, u8 cs_mask, bool enable)
अणु
	काष्ठा अणु
		u8 port;
		u8 cs;
	पूर्ण tx;
	u16 cmd;

	tx.port = dln2->port;
	tx.cs = cs_mask;
	cmd = enable ? DLN2_SPI_SS_MULTI_ENABLE : DLN2_SPI_SS_MULTI_DISABLE;

	वापस dln2_transfer_tx(dln2->pdev, cmd, &tx, माप(tx));
पूर्ण

अटल पूर्णांक dln2_spi_cs_enable_all(काष्ठा dln2_spi *dln2, bool enable)
अणु
	u8 cs_mask = GENMASK(dln2->master->num_chipselect - 1, 0);

	वापस dln2_spi_cs_enable(dln2, cs_mask, enable);
पूर्ण

अटल पूर्णांक dln2_spi_get_cs_num(काष्ठा dln2_spi *dln2, u16 *cs_num)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		u8 port;
	पूर्ण tx;
	काष्ठा अणु
		__le16 cs_count;
	पूर्ण rx;
	अचिन्हित rx_len = माप(rx);

	tx.port = dln2->port;
	ret = dln2_transfer(dln2->pdev, DLN2_SPI_GET_SS_COUNT, &tx, माप(tx),
			    &rx, &rx_len);
	अगर (ret < 0)
		वापस ret;
	अगर (rx_len < माप(rx))
		वापस -EPROTO;

	*cs_num = le16_to_cpu(rx.cs_count);

	dev_dbg(&dln2->pdev->dev, "cs_num = %d\n", *cs_num);

	वापस 0;
पूर्ण

अटल पूर्णांक dln2_spi_get_speed(काष्ठा dln2_spi *dln2, u16 cmd, u32 *freq)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		u8 port;
	पूर्ण tx;
	काष्ठा अणु
		__le32 speed;
	पूर्ण rx;
	अचिन्हित rx_len = माप(rx);

	tx.port = dln2->port;

	ret = dln2_transfer(dln2->pdev, cmd, &tx, माप(tx), &rx, &rx_len);
	अगर (ret < 0)
		वापस ret;
	अगर (rx_len < माप(rx))
		वापस -EPROTO;

	*freq = le32_to_cpu(rx.speed);

	वापस 0;
पूर्ण

/*
 * Get bus min/max frequencies.
 */
अटल पूर्णांक dln2_spi_get_speed_range(काष्ठा dln2_spi *dln2, u32 *fmin, u32 *fmax)
अणु
	पूर्णांक ret;

	ret = dln2_spi_get_speed(dln2, DLN2_SPI_GET_MIN_FREQUENCY, fmin);
	अगर (ret < 0)
		वापस ret;

	ret = dln2_spi_get_speed(dln2, DLN2_SPI_GET_MAX_FREQUENCY, fmax);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(&dln2->pdev->dev, "freq_min = %d, freq_max = %d\n",
		*fmin, *fmax);

	वापस 0;
पूर्ण

/*
 * Set the bus speed. The module will स्वतःmatically round करोwn to the बंदst
 * available frequency and वापसs it. The module has to be disabled first.
 */
अटल पूर्णांक dln2_spi_set_speed(काष्ठा dln2_spi *dln2, u32 speed)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		u8 port;
		__le32 speed;
	पूर्ण __packed tx;
	काष्ठा अणु
		__le32 speed;
	पूर्ण rx;
	पूर्णांक rx_len = माप(rx);

	tx.port = dln2->port;
	tx.speed = cpu_to_le32(speed);

	ret = dln2_transfer(dln2->pdev, DLN2_SPI_SET_FREQUENCY, &tx, माप(tx),
			    &rx, &rx_len);
	अगर (ret < 0)
		वापस ret;
	अगर (rx_len < माप(rx))
		वापस -EPROTO;

	वापस 0;
पूर्ण

/*
 * Change CPOL & CPHA. The module has to be disabled first.
 */
अटल पूर्णांक dln2_spi_set_mode(काष्ठा dln2_spi *dln2, u8 mode)
अणु
	काष्ठा अणु
		u8 port;
		u8 mode;
	पूर्ण tx;

	tx.port = dln2->port;
	tx.mode = mode;

	वापस dln2_transfer_tx(dln2->pdev, DLN2_SPI_SET_MODE, &tx, माप(tx));
पूर्ण

/*
 * Change frame size. The module has to be disabled first.
 */
अटल पूर्णांक dln2_spi_set_bpw(काष्ठा dln2_spi *dln2, u8 bpw)
अणु
	काष्ठा अणु
		u8 port;
		u8 bpw;
	पूर्ण tx;

	tx.port = dln2->port;
	tx.bpw = bpw;

	वापस dln2_transfer_tx(dln2->pdev, DLN2_SPI_SET_FRAME_SIZE,
				&tx, माप(tx));
पूर्ण

अटल पूर्णांक dln2_spi_get_supported_frame_sizes(काष्ठा dln2_spi *dln2,
					      u32 *bpw_mask)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		u8 port;
	पूर्ण tx;
	काष्ठा अणु
		u8 count;
		u8 frame_sizes[36];
	पूर्ण *rx = dln2->buf;
	अचिन्हित rx_len = माप(*rx);
	पूर्णांक i;

	tx.port = dln2->port;

	ret = dln2_transfer(dln2->pdev, DLN2_SPI_GET_SUPPORTED_FRAME_SIZES,
			    &tx, माप(tx), rx, &rx_len);
	अगर (ret < 0)
		वापस ret;
	अगर (rx_len < माप(*rx))
		वापस -EPROTO;
	अगर (rx->count > ARRAY_SIZE(rx->frame_sizes))
		वापस -EPROTO;

	*bpw_mask = 0;
	क्रम (i = 0; i < rx->count; i++)
		*bpw_mask |= BIT(rx->frame_sizes[i] - 1);

	dev_dbg(&dln2->pdev->dev, "bpw_mask = 0x%X\n", *bpw_mask);

	वापस 0;
पूर्ण

/*
 * Copy the data to DLN2 buffer and change the byte order to LE, requested by
 * DLN2 module. SPI core makes sure that the data length is a multiple of word
 * size.
 */
अटल पूर्णांक dln2_spi_copy_to_buf(u8 *dln2_buf, स्थिर u8 *src, u16 len, u8 bpw)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	स_नकल(dln2_buf, src, len);
#अन्यथा
	अगर (bpw <= 8) अणु
		स_नकल(dln2_buf, src, len);
	पूर्ण अन्यथा अगर (bpw <= 16) अणु
		__le16 *d = (__le16 *)dln2_buf;
		u16 *s = (u16 *)src;

		len = len / 2;
		जबतक (len--)
			*d++ = cpu_to_le16p(s++);
	पूर्ण अन्यथा अणु
		__le32 *d = (__le32 *)dln2_buf;
		u32 *s = (u32 *)src;

		len = len / 4;
		जबतक (len--)
			*d++ = cpu_to_le32p(s++);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * Copy the data from DLN2 buffer and convert to CPU byte order since the DLN2
 * buffer is LE ordered. SPI core makes sure that the data length is a multiple
 * of word size. The RX dln2_buf is 2 byte aligned so, क्रम BE, we have to make
 * sure we aव्योम unaligned accesses क्रम 32 bit हाल.
 */
अटल पूर्णांक dln2_spi_copy_from_buf(u8 *dest, स्थिर u8 *dln2_buf, u16 len, u8 bpw)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	स_नकल(dest, dln2_buf, len);
#अन्यथा
	अगर (bpw <= 8) अणु
		स_नकल(dest, dln2_buf, len);
	पूर्ण अन्यथा अगर (bpw <= 16) अणु
		u16 *d = (u16 *)dest;
		__le16 *s = (__le16 *)dln2_buf;

		len = len / 2;
		जबतक (len--)
			*d++ = le16_to_cpup(s++);
	पूर्ण अन्यथा अणु
		u32 *d = (u32 *)dest;
		__le32 *s = (__le32 *)dln2_buf;

		len = len / 4;
		जबतक (len--)
			*d++ = get_unaligned_le32(s++);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * Perक्रमm one ग_लिखो operation.
 */
अटल पूर्णांक dln2_spi_ग_लिखो_one(काष्ठा dln2_spi *dln2, स्थिर u8 *data,
			      u16 data_len, u8 attr)
अणु
	काष्ठा अणु
		u8 port;
		__le16 size;
		u8 attr;
		u8 buf[DLN2_SPI_MAX_XFER_SIZE];
	पूर्ण __packed *tx = dln2->buf;
	अचिन्हित tx_len;

	BUILD_BUG_ON(माप(*tx) > DLN2_SPI_BUF_SIZE);

	अगर (data_len > DLN2_SPI_MAX_XFER_SIZE)
		वापस -EINVAL;

	tx->port = dln2->port;
	tx->size = cpu_to_le16(data_len);
	tx->attr = attr;

	dln2_spi_copy_to_buf(tx->buf, data, data_len, dln2->bpw);

	tx_len = माप(*tx) + data_len - DLN2_SPI_MAX_XFER_SIZE;
	वापस dln2_transfer_tx(dln2->pdev, DLN2_SPI_WRITE, tx, tx_len);
पूर्ण

/*
 * Perक्रमm one पढ़ो operation.
 */
अटल पूर्णांक dln2_spi_पढ़ो_one(काष्ठा dln2_spi *dln2, u8 *data,
			     u16 data_len, u8 attr)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		u8 port;
		__le16 size;
		u8 attr;
	पूर्ण __packed tx;
	काष्ठा अणु
		__le16 size;
		u8 buf[DLN2_SPI_MAX_XFER_SIZE];
	पूर्ण __packed *rx = dln2->buf;
	अचिन्हित rx_len = माप(*rx);

	BUILD_BUG_ON(माप(*rx) > DLN2_SPI_BUF_SIZE);

	अगर (data_len > DLN2_SPI_MAX_XFER_SIZE)
		वापस -EINVAL;

	tx.port = dln2->port;
	tx.size = cpu_to_le16(data_len);
	tx.attr = attr;

	ret = dln2_transfer(dln2->pdev, DLN2_SPI_READ, &tx, माप(tx),
			    rx, &rx_len);
	अगर (ret < 0)
		वापस ret;
	अगर (rx_len < माप(rx->size) + data_len)
		वापस -EPROTO;
	अगर (le16_to_cpu(rx->size) != data_len)
		वापस -EPROTO;

	dln2_spi_copy_from_buf(data, rx->buf, data_len, dln2->bpw);

	वापस 0;
पूर्ण

/*
 * Perक्रमm one ग_लिखो & पढ़ो operation.
 */
अटल पूर्णांक dln2_spi_पढ़ो_ग_लिखो_one(काष्ठा dln2_spi *dln2, स्थिर u8 *tx_data,
				   u8 *rx_data, u16 data_len, u8 attr)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		u8 port;
		__le16 size;
		u8 attr;
		u8 buf[DLN2_SPI_MAX_XFER_SIZE];
	पूर्ण __packed *tx;
	काष्ठा अणु
		__le16 size;
		u8 buf[DLN2_SPI_MAX_XFER_SIZE];
	पूर्ण __packed *rx;
	अचिन्हित tx_len, rx_len;

	BUILD_BUG_ON(माप(*tx) > DLN2_SPI_BUF_SIZE ||
		     माप(*rx) > DLN2_SPI_BUF_SIZE);

	अगर (data_len > DLN2_SPI_MAX_XFER_SIZE)
		वापस -EINVAL;

	/*
	 * Since this is a pseuकरो full-duplex communication, we're perfectly
	 * safe to use the same buffer क्रम both tx and rx. When DLN2 sends the
	 * response back, with the rx data, we करोn't need the tx buffer anymore.
	 */
	tx = dln2->buf;
	rx = dln2->buf;

	tx->port = dln2->port;
	tx->size = cpu_to_le16(data_len);
	tx->attr = attr;

	dln2_spi_copy_to_buf(tx->buf, tx_data, data_len, dln2->bpw);

	tx_len = माप(*tx) + data_len - DLN2_SPI_MAX_XFER_SIZE;
	rx_len = माप(*rx);

	ret = dln2_transfer(dln2->pdev, DLN2_SPI_READ_WRITE, tx, tx_len,
			    rx, &rx_len);
	अगर (ret < 0)
		वापस ret;
	अगर (rx_len < माप(rx->size) + data_len)
		वापस -EPROTO;
	अगर (le16_to_cpu(rx->size) != data_len)
		वापस -EPROTO;

	dln2_spi_copy_from_buf(rx_data, rx->buf, data_len, dln2->bpw);

	वापस 0;
पूर्ण

/*
 * Read/Write wrapper. It will स्वतःmatically split an operation पूर्णांकo multiple
 * single ones due to device buffer स्थिरraपूर्णांकs.
 */
अटल पूर्णांक dln2_spi_rdwr(काष्ठा dln2_spi *dln2, स्थिर u8 *tx_data,
			 u8 *rx_data, u16 data_len, u8 attr)
अणु
	पूर्णांक ret;
	u16 len;
	u8 temp_attr;
	u16 reमुख्यing = data_len;
	u16 offset;

	करो अणु
		अगर (reमुख्यing > DLN2_SPI_MAX_XFER_SIZE) अणु
			len = DLN2_SPI_MAX_XFER_SIZE;
			temp_attr = DLN2_SPI_ATTR_LEAVE_SS_LOW;
		पूर्ण अन्यथा अणु
			len = reमुख्यing;
			temp_attr = attr;
		पूर्ण

		offset = data_len - reमुख्यing;

		अगर (tx_data && rx_data) अणु
			ret = dln2_spi_पढ़ो_ग_लिखो_one(dln2,
						      tx_data + offset,
						      rx_data + offset,
						      len, temp_attr);
		पूर्ण अन्यथा अगर (tx_data) अणु
			ret = dln2_spi_ग_लिखो_one(dln2,
						 tx_data + offset,
						 len, temp_attr);
		पूर्ण अन्यथा अगर (rx_data) अणु
			ret = dln2_spi_पढ़ो_one(dln2,
						rx_data + offset,
						len, temp_attr);
		 पूर्ण अन्यथा अणु
			वापस -EINVAL;
		 पूर्ण

		अगर (ret < 0)
			वापस ret;

		reमुख्यing -= len;
	पूर्ण जबतक (reमुख्यing);

	वापस 0;
पूर्ण

अटल पूर्णांक dln2_spi_prepare_message(काष्ठा spi_master *master,
				    काष्ठा spi_message *message)
अणु
	पूर्णांक ret;
	काष्ठा dln2_spi *dln2 = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = message->spi;

	अगर (dln2->cs != spi->chip_select) अणु
		ret = dln2_spi_cs_set_one(dln2, spi->chip_select);
		अगर (ret < 0)
			वापस ret;

		dln2->cs = spi->chip_select;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dln2_spi_transfer_setup(काष्ठा dln2_spi *dln2, u32 speed,
				   u8 bpw, u8 mode)
अणु
	पूर्णांक ret;
	bool bus_setup_change;

	bus_setup_change = dln2->speed != speed || dln2->mode != mode ||
			   dln2->bpw != bpw;

	अगर (!bus_setup_change)
		वापस 0;

	ret = dln2_spi_enable(dln2, false);
	अगर (ret < 0)
		वापस ret;

	अगर (dln2->speed != speed) अणु
		ret = dln2_spi_set_speed(dln2, speed);
		अगर (ret < 0)
			वापस ret;

		dln2->speed = speed;
	पूर्ण

	अगर (dln2->mode != mode) अणु
		ret = dln2_spi_set_mode(dln2, mode & 0x3);
		अगर (ret < 0)
			वापस ret;

		dln2->mode = mode;
	पूर्ण

	अगर (dln2->bpw != bpw) अणु
		ret = dln2_spi_set_bpw(dln2, bpw);
		अगर (ret < 0)
			वापस ret;

		dln2->bpw = bpw;
	पूर्ण

	वापस dln2_spi_enable(dln2, true);
पूर्ण

अटल पूर्णांक dln2_spi_transfer_one(काष्ठा spi_master *master,
				 काष्ठा spi_device *spi,
				 काष्ठा spi_transfer *xfer)
अणु
	काष्ठा dln2_spi *dln2 = spi_master_get_devdata(master);
	पूर्णांक status;
	u8 attr = 0;

	status = dln2_spi_transfer_setup(dln2, xfer->speed_hz,
					 xfer->bits_per_word,
					 spi->mode);
	अगर (status < 0) अणु
		dev_err(&dln2->pdev->dev, "Cannot setup transfer\n");
		वापस status;
	पूर्ण

	अगर (!xfer->cs_change && !spi_transfer_is_last(master, xfer))
		attr = DLN2_SPI_ATTR_LEAVE_SS_LOW;

	status = dln2_spi_rdwr(dln2, xfer->tx_buf, xfer->rx_buf,
			       xfer->len, attr);
	अगर (status < 0)
		dev_err(&dln2->pdev->dev, "write/read failed!\n");

	वापस status;
पूर्ण

अटल पूर्णांक dln2_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master;
	काष्ठा dln2_spi *dln2;
	काष्ठा dln2_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	master = spi_alloc_master(&pdev->dev, माप(*dln2));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);

	dln2 = spi_master_get_devdata(master);

	dln2->buf = devm_kदो_स्मृति(&pdev->dev, DLN2_SPI_BUF_SIZE, GFP_KERNEL);
	अगर (!dln2->buf) अणु
		ret = -ENOMEM;
		जाओ निकास_मुक्त_master;
	पूर्ण

	dln2->master = master;
	dln2->master->dev.of_node = dev->of_node;
	dln2->pdev = pdev;
	dln2->port = pdata->port;
	/* cs/mode can never be 0xff, so the first transfer will set them */
	dln2->cs = 0xff;
	dln2->mode = 0xff;

	/* disable SPI module beक्रमe continuing with the setup */
	ret = dln2_spi_enable(dln2, false);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to disable SPI module\n");
		जाओ निकास_मुक्त_master;
	पूर्ण

	ret = dln2_spi_get_cs_num(dln2, &master->num_chipselect);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get number of CS pins\n");
		जाओ निकास_मुक्त_master;
	पूर्ण

	ret = dln2_spi_get_speed_range(dln2,
				       &master->min_speed_hz,
				       &master->max_speed_hz);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to read bus min/max freqs\n");
		जाओ निकास_मुक्त_master;
	पूर्ण

	ret = dln2_spi_get_supported_frame_sizes(dln2,
						 &master->bits_per_word_mask);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to read supported frame sizes\n");
		जाओ निकास_मुक्त_master;
	पूर्ण

	ret = dln2_spi_cs_enable_all(dln2, true);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to enable CS pins\n");
		जाओ निकास_मुक्त_master;
	पूर्ण

	master->bus_num = -1;
	master->mode_bits = SPI_CPOL | SPI_CPHA;
	master->prepare_message = dln2_spi_prepare_message;
	master->transfer_one = dln2_spi_transfer_one;
	master->स्वतः_runसमय_pm = true;

	/* enable SPI module, we're good to go */
	ret = dln2_spi_enable(dln2, true);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to enable SPI module\n");
		जाओ निकास_मुक्त_master;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev,
					 DLN2_RPM_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register master\n");
		जाओ निकास_रेजिस्टर;
	पूर्ण

	वापस ret;

निकास_रेजिस्टर:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);

	अगर (dln2_spi_enable(dln2, false) < 0)
		dev_err(&pdev->dev, "Failed to disable SPI module\n");
निकास_मुक्त_master:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक dln2_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा dln2_spi *dln2 = spi_master_get_devdata(master);

	pm_runसमय_disable(&pdev->dev);

	अगर (dln2_spi_enable(dln2, false) < 0)
		dev_err(&pdev->dev, "Failed to disable SPI module\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dln2_spi_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा dln2_spi *dln2 = spi_master_get_devdata(master);

	ret = spi_master_suspend(master);
	अगर (ret < 0)
		वापस ret;

	अगर (!pm_runसमय_suspended(dev)) अणु
		ret = dln2_spi_enable(dln2, false);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/*
	 * USB घातer may be cut off during sleep. Resetting the following
	 * parameters will क्रमce the board to be set up beक्रमe first transfer.
	 */
	dln2->cs = 0xff;
	dln2->speed = 0;
	dln2->bpw = 0;
	dln2->mode = 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक dln2_spi_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा dln2_spi *dln2 = spi_master_get_devdata(master);

	अगर (!pm_runसमय_suspended(dev)) अणु
		ret = dln2_spi_cs_enable_all(dln2, true);
		अगर (ret < 0)
			वापस ret;

		ret = dln2_spi_enable(dln2, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस spi_master_resume(master);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
अटल पूर्णांक dln2_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा dln2_spi *dln2 = spi_master_get_devdata(master);

	वापस dln2_spi_enable(dln2, false);
पूर्ण

अटल पूर्णांक dln2_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा dln2_spi *dln2 = spi_master_get_devdata(master);

	वापस  dln2_spi_enable(dln2, true);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops dln2_spi_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dln2_spi_suspend, dln2_spi_resume)
	SET_RUNTIME_PM_OPS(dln2_spi_runसमय_suspend,
			   dln2_spi_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver spi_dln2_driver = अणु
	.driver = अणु
		.name	= "dln2-spi",
		.pm	= &dln2_spi_pm,
	पूर्ण,
	.probe		= dln2_spi_probe,
	.हटाओ		= dln2_spi_हटाओ,
पूर्ण;
module_platक्रमm_driver(spi_dln2_driver);

MODULE_DESCRIPTION("Driver for the Diolan DLN2 SPI master interface");
MODULE_AUTHOR("Laurentiu Palcu <laurentiu.palcu@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:dln2-spi");
