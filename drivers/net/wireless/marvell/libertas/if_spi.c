<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	linux/drivers/net/wireless/libertas/अगर_spi.c
 *
 *	Driver क्रम Marvell SPI WLAN cards.
 *
 *	Copyright 2008 Analog Devices Inc.
 *
 *	Authors:
 *	Andrey Yurovsky <andrey@cozybit.com>
 *	Colin McCabe <colin@cozybit.com>
 *
 *	Inspired by अगर_sdio.c, Copyright 2007-2008 Pierre Ossman
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/hardirq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/libertas_spi.h>
#समावेश <linux/spi/spi.h>

#समावेश "host.h"
#समावेश "decl.h"
#समावेश "defs.h"
#समावेश "dev.h"
#समावेश "if_spi.h"

काष्ठा अगर_spi_packet अणु
	काष्ठा list_head		list;
	u16				blen;
	u8				buffer[] __aligned(4);
पूर्ण;

काष्ठा अगर_spi_card अणु
	काष्ठा spi_device		*spi;
	काष्ठा lbs_निजी		*priv;
	काष्ठा libertas_spi_platक्रमm_data *pdata;

	/* The card ID and card revision, as reported by the hardware. */
	u16				card_id;
	u8				card_rev;

	/* The last समय that we initiated an SPU operation */
	अचिन्हित दीर्घ			prev_xfer_समय;

	पूर्णांक				use_dummy_ग_लिखोs;
	अचिन्हित दीर्घ			spu_port_delay;
	अचिन्हित दीर्घ			spu_reg_delay;

	/* Handles all SPI communication (except क्रम FW load) */
	काष्ठा workqueue_काष्ठा		*workqueue;
	काष्ठा work_काष्ठा		packet_work;
	काष्ठा work_काष्ठा		resume_work;

	u8				cmd_buffer[IF_SPI_CMD_BUF_SIZE];

	/* A buffer of incoming packets from libertas core.
	 * Since we can't sleep in hw_host_to_card, we have to buffer
	 * them. */
	काष्ठा list_head		cmd_packet_list;
	काष्ठा list_head		data_packet_list;

	/* Protects cmd_packet_list and data_packet_list */
	spinlock_t			buffer_lock;

	/* True is card suspended */
	u8				suspended;
पूर्ण;

अटल व्योम मुक्त_अगर_spi_card(काष्ठा अगर_spi_card *card)
अणु
	काष्ठा list_head *cursor, *next;
	काष्ठा अगर_spi_packet *packet;

	list_क्रम_each_safe(cursor, next, &card->cmd_packet_list) अणु
		packet = container_of(cursor, काष्ठा अगर_spi_packet, list);
		list_del(&packet->list);
		kमुक्त(packet);
	पूर्ण
	list_क्रम_each_safe(cursor, next, &card->data_packet_list) अणु
		packet = container_of(cursor, काष्ठा अगर_spi_packet, list);
		list_del(&packet->list);
		kमुक्त(packet);
	पूर्ण
	kमुक्त(card);
पूर्ण

#घोषणा MODEL_8385	0x04
#घोषणा MODEL_8686	0x0b
#घोषणा MODEL_8688	0x10

अटल स्थिर काष्ठा lbs_fw_table fw_table[] = अणु
	अणु MODEL_8385, "libertas/gspi8385_helper.bin", "libertas/gspi8385.bin" पूर्ण,
	अणु MODEL_8385, "libertas/gspi8385_hlp.bin", "libertas/gspi8385.bin" पूर्ण,
	अणु MODEL_8686, "libertas/gspi8686_v9_helper.bin", "libertas/gspi8686_v9.bin" पूर्ण,
	अणु MODEL_8686, "libertas/gspi8686_hlp.bin", "libertas/gspi8686.bin" पूर्ण,
	अणु MODEL_8688, "libertas/gspi8688_helper.bin", "libertas/gspi8688.bin" पूर्ण,
	अणु 0, शून्य, शून्य पूर्ण
पूर्ण;
MODULE_FIRMWARE("libertas/gspi8385_helper.bin");
MODULE_FIRMWARE("libertas/gspi8385_hlp.bin");
MODULE_FIRMWARE("libertas/gspi8385.bin");
MODULE_FIRMWARE("libertas/gspi8686_v9_helper.bin");
MODULE_FIRMWARE("libertas/gspi8686_v9.bin");
MODULE_FIRMWARE("libertas/gspi8686_hlp.bin");
MODULE_FIRMWARE("libertas/gspi8686.bin");
MODULE_FIRMWARE("libertas/gspi8688_helper.bin");
MODULE_FIRMWARE("libertas/gspi8688.bin");


/*
 * SPI Interface Unit Routines
 *
 * The SPU sits between the host and the WLAN module.
 * All communication with the firmware is through SPU transactions.
 *
 * First we have to put a SPU रेजिस्टर name on the bus. Then we can
 * either पढ़ो from or ग_लिखो to that रेजिस्टर.
 *
 */

अटल व्योम spu_transaction_init(काष्ठा अगर_spi_card *card)
अणु
	अगर (!समय_after(jअगरfies, card->prev_xfer_समय + 1)) अणु
		/* Unक्रमtunately, the SPU requires a delay between successive
		 * transactions. If our last transaction was more than a jअगरfy
		 * ago, we have obviously alपढ़ोy delayed enough.
		 * If not, we have to busy-रुको to be on the safe side. */
		ndelay(400);
	पूर्ण
पूर्ण

अटल व्योम spu_transaction_finish(काष्ठा अगर_spi_card *card)
अणु
	card->prev_xfer_समय = jअगरfies;
पूर्ण

/*
 * Write out a byte buffer to an SPI रेजिस्टर,
 * using a series of 16-bit transfers.
 */
अटल पूर्णांक spu_ग_लिखो(काष्ठा अगर_spi_card *card, u16 reg, स्थिर u8 *buf, पूर्णांक len)
अणु
	पूर्णांक err = 0;
	__le16 reg_out = cpu_to_le16(reg | IF_SPI_WRITE_OPERATION_MASK);
	काष्ठा spi_message m;
	काष्ठा spi_transfer reg_trans;
	काष्ठा spi_transfer data_trans;

	spi_message_init(&m);
	स_रखो(&reg_trans, 0, माप(reg_trans));
	स_रखो(&data_trans, 0, माप(data_trans));

	/* You must give an even number of bytes to the SPU, even अगर it
	 * करोesn't care about the last one.  */
	BUG_ON(len & 0x1);

	spu_transaction_init(card);

	/* ग_लिखो SPU रेजिस्टर index */
	reg_trans.tx_buf = &reg_out;
	reg_trans.len = माप(reg_out);

	data_trans.tx_buf = buf;
	data_trans.len = len;

	spi_message_add_tail(&reg_trans, &m);
	spi_message_add_tail(&data_trans, &m);

	err = spi_sync(card->spi, &m);
	spu_transaction_finish(card);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक spu_ग_लिखो_u16(काष्ठा अगर_spi_card *card, u16 reg, u16 val)
अणु
	__le16 buff;

	buff = cpu_to_le16(val);
	वापस spu_ग_लिखो(card, reg, (u8 *)&buff, माप(u16));
पूर्ण

अटल अंतरभूत पूर्णांक spu_reg_is_port_reg(u16 reg)
अणु
	चयन (reg) अणु
	हाल IF_SPI_IO_RDWRPORT_REG:
	हाल IF_SPI_CMD_RDWRPORT_REG:
	हाल IF_SPI_DATA_RDWRPORT_REG:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक spu_पढ़ो(काष्ठा अगर_spi_card *card, u16 reg, u8 *buf, पूर्णांक len)
अणु
	अचिन्हित पूर्णांक delay;
	पूर्णांक err = 0;
	__le16 reg_out = cpu_to_le16(reg | IF_SPI_READ_OPERATION_MASK);
	काष्ठा spi_message m;
	काष्ठा spi_transfer reg_trans;
	काष्ठा spi_transfer dummy_trans;
	काष्ठा spi_transfer data_trans;

	/*
	 * You must take an even number of bytes from the SPU, even अगर you
	 * करोn't care about the last one.
	 */
	BUG_ON(len & 0x1);

	spu_transaction_init(card);

	spi_message_init(&m);
	स_रखो(&reg_trans, 0, माप(reg_trans));
	स_रखो(&dummy_trans, 0, माप(dummy_trans));
	स_रखो(&data_trans, 0, माप(data_trans));

	/* ग_लिखो SPU रेजिस्टर index */
	reg_trans.tx_buf = &reg_out;
	reg_trans.len = माप(reg_out);
	spi_message_add_tail(&reg_trans, &m);

	delay = spu_reg_is_port_reg(reg) ? card->spu_port_delay :
						card->spu_reg_delay;
	अगर (card->use_dummy_ग_लिखोs) अणु
		/* Clock in dummy cycles जबतक the SPU fills the FIFO */
		dummy_trans.len = delay / 8;
		spi_message_add_tail(&dummy_trans, &m);
	पूर्ण अन्यथा अणु
		/* Busy-रुको जबतक the SPU fills the FIFO */
		reg_trans.delay.value =
			DIV_ROUND_UP((100 + (delay * 10)), 1000);
		reg_trans.delay.unit = SPI_DELAY_UNIT_USECS;
	पूर्ण

	/* पढ़ो in data */
	data_trans.rx_buf = buf;
	data_trans.len = len;
	spi_message_add_tail(&data_trans, &m);

	err = spi_sync(card->spi, &m);
	spu_transaction_finish(card);
	वापस err;
पूर्ण

/* Read 16 bits from an SPI रेजिस्टर */
अटल अंतरभूत पूर्णांक spu_पढ़ो_u16(काष्ठा अगर_spi_card *card, u16 reg, u16 *val)
अणु
	__le16 buf;
	पूर्णांक ret;

	ret = spu_पढ़ो(card, reg, (u8 *)&buf, माप(buf));
	अगर (ret == 0)
		*val = le16_to_cpup(&buf);
	वापस ret;
पूर्ण

/*
 * Read 32 bits from an SPI रेजिस्टर.
 * The low 16 bits are पढ़ो first.
 */
अटल पूर्णांक spu_पढ़ो_u32(काष्ठा अगर_spi_card *card, u16 reg, u32 *val)
अणु
	__le32 buf;
	पूर्णांक err;

	err = spu_पढ़ो(card, reg, (u8 *)&buf, माप(buf));
	अगर (!err)
		*val = le32_to_cpup(&buf);
	वापस err;
पूर्ण

/*
 * Keep पढ़ोing 16 bits from an SPI रेजिस्टर until you get the correct result.
 *
 * If mask = 0, the correct result is any non-zero number.
 * If mask != 0, the correct result is any number where
 * number & target_mask == target
 *
 * Returns -ETIMEDOUT अगर a second passes without the correct result.
 */
अटल पूर्णांक spu_रुको_क्रम_u16(काष्ठा अगर_spi_card *card, u16 reg,
			u16 target_mask, u16 target)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ समयout = jअगरfies + 5*HZ;
	जबतक (1) अणु
		u16 val;
		err = spu_पढ़ो_u16(card, reg, &val);
		अगर (err)
			वापस err;
		अगर (target_mask) अणु
			अगर ((val & target_mask) == target)
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (val)
				वापस 0;
		पूर्ण
		udelay(100);
		अगर (समय_after(jअगरfies, समयout)) अणु
			pr_err("%s: timeout with val=%02x, target_mask=%02x, target=%02x\n",
			       __func__, val, target_mask, target);
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Read 16 bits from an SPI रेजिस्टर until you receive a specअगरic value.
 * Returns -ETIMEDOUT अगर a 4 tries pass without success.
 */
अटल पूर्णांक spu_रुको_क्रम_u32(काष्ठा अगर_spi_card *card, u32 reg, u32 target)
अणु
	पूर्णांक err, try;
	क्रम (try = 0; try < 4; ++try) अणु
		u32 val = 0;
		err = spu_पढ़ो_u32(card, reg, &val);
		अगर (err)
			वापस err;
		अगर (val == target)
			वापस 0;
		mdelay(100);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक spu_set_पूर्णांकerrupt_mode(काष्ठा अगर_spi_card *card,
			   पूर्णांक suppress_host_पूर्णांक,
			   पूर्णांक स्वतः_पूर्णांक)
अणु
	पूर्णांक err = 0;

	/*
	 * We can suppress a host पूर्णांकerrupt by clearing the appropriate
	 * bit in the "host interrupt status mask" रेजिस्टर
	 */
	अगर (suppress_host_पूर्णांक) अणु
		err = spu_ग_लिखो_u16(card, IF_SPI_HOST_INT_STATUS_MASK_REG, 0);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		err = spu_ग_लिखो_u16(card, IF_SPI_HOST_INT_STATUS_MASK_REG,
			      IF_SPI_HISM_TX_DOWNLOAD_RDY |
			      IF_SPI_HISM_RX_UPLOAD_RDY |
			      IF_SPI_HISM_CMD_DOWNLOAD_RDY |
			      IF_SPI_HISM_CARDEVENT |
			      IF_SPI_HISM_CMD_UPLOAD_RDY);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * If स्वतः-पूर्णांकerrupts are on, the completion of certain transactions
	 * will trigger an पूर्णांकerrupt स्वतःmatically. If स्वतः-पूर्णांकerrupts
	 * are off, we need to set the "Card Interrupt Cause" रेजिस्टर to
	 * trigger a card पूर्णांकerrupt.
	 */
	अगर (स्वतः_पूर्णांक) अणु
		err = spu_ग_लिखो_u16(card, IF_SPI_HOST_INT_CTRL_REG,
				IF_SPI_HICT_TX_DOWNLOAD_OVER_AUTO |
				IF_SPI_HICT_RX_UPLOAD_OVER_AUTO |
				IF_SPI_HICT_CMD_DOWNLOAD_OVER_AUTO |
				IF_SPI_HICT_CMD_UPLOAD_OVER_AUTO);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		err = spu_ग_लिखो_u16(card, IF_SPI_HOST_INT_STATUS_MASK_REG, 0);
		अगर (err)
			वापस err;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक spu_get_chip_revision(काष्ठा अगर_spi_card *card,
				  u16 *card_id, u8 *card_rev)
अणु
	पूर्णांक err = 0;
	u32 dev_ctrl;
	err = spu_पढ़ो_u32(card, IF_SPI_DEVICEID_CTRL_REG, &dev_ctrl);
	अगर (err)
		वापस err;
	*card_id = IF_SPI_DEVICEID_CTRL_REG_TO_CARD_ID(dev_ctrl);
	*card_rev = IF_SPI_DEVICEID_CTRL_REG_TO_CARD_REV(dev_ctrl);
	वापस err;
पूर्ण

अटल पूर्णांक spu_set_bus_mode(काष्ठा अगर_spi_card *card, u16 mode)
अणु
	पूर्णांक err = 0;
	u16 rval;
	/* set bus mode */
	err = spu_ग_लिखो_u16(card, IF_SPI_SPU_BUS_MODE_REG, mode);
	अगर (err)
		वापस err;
	/* Check that we were able to पढ़ो back what we just wrote. */
	err = spu_पढ़ो_u16(card, IF_SPI_SPU_BUS_MODE_REG, &rval);
	अगर (err)
		वापस err;
	अगर ((rval & 0xF) != mode) अणु
		pr_err("Can't read bus mode register\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक spu_init(काष्ठा अगर_spi_card *card, पूर्णांक use_dummy_ग_लिखोs)
अणु
	पूर्णांक err = 0;
	u32 delay;

	/*
	 * We have to start up in समयd delay mode so that we can safely
	 * पढ़ो the Delay Read Register.
	 */
	card->use_dummy_ग_लिखोs = 0;
	err = spu_set_bus_mode(card,
				IF_SPI_BUS_MODE_SPI_CLOCK_PHASE_RISING |
				IF_SPI_BUS_MODE_DELAY_METHOD_TIMED |
				IF_SPI_BUS_MODE_16_BIT_ADDRESS_16_BIT_DATA);
	अगर (err)
		वापस err;
	card->spu_port_delay = 1000;
	card->spu_reg_delay = 1000;
	err = spu_पढ़ो_u32(card, IF_SPI_DELAY_READ_REG, &delay);
	अगर (err)
		वापस err;
	card->spu_port_delay = delay & 0x0000ffff;
	card->spu_reg_delay = (delay & 0xffff0000) >> 16;

	/* If dummy घड़ी delay mode has been requested, चयन to it now */
	अगर (use_dummy_ग_लिखोs) अणु
		card->use_dummy_ग_लिखोs = 1;
		err = spu_set_bus_mode(card,
				IF_SPI_BUS_MODE_SPI_CLOCK_PHASE_RISING |
				IF_SPI_BUS_MODE_DELAY_METHOD_DUMMY_CLOCK |
				IF_SPI_BUS_MODE_16_BIT_ADDRESS_16_BIT_DATA);
		अगर (err)
			वापस err;
	पूर्ण

	lbs_deb_spi("Initialized SPU unit. "
		    "spu_port_delay=0x%04lx, spu_reg_delay=0x%04lx\n",
		    card->spu_port_delay, card->spu_reg_delay);
	वापस err;
पूर्ण

/*
 * Firmware Loading
 */

अटल पूर्णांक अगर_spi_prog_helper_firmware(काष्ठा अगर_spi_card *card,
					स्थिर काष्ठा firmware *firmware)
अणु
	पूर्णांक err = 0;
	पूर्णांक bytes_reमुख्यing;
	स्थिर u8 *fw;
	u8 temp[HELPER_FW_LOAD_CHUNK_SZ];

	err = spu_set_पूर्णांकerrupt_mode(card, 1, 0);
	अगर (err)
		जाओ out;

	bytes_reमुख्यing = firmware->size;
	fw = firmware->data;

	/* Load helper firmware image */
	जबतक (bytes_reमुख्यing > 0) अणु
		/*
		 * Scratch pad 1 should contain the number of bytes we
		 * want to करोwnload to the firmware
		 */
		err = spu_ग_लिखो_u16(card, IF_SPI_SCRATCH_1_REG,
					HELPER_FW_LOAD_CHUNK_SZ);
		अगर (err)
			जाओ out;

		err = spu_रुको_क्रम_u16(card, IF_SPI_HOST_INT_STATUS_REG,
					IF_SPI_HIST_CMD_DOWNLOAD_RDY,
					IF_SPI_HIST_CMD_DOWNLOAD_RDY);
		अगर (err)
			जाओ out;

		/*
		 * Feed the data पूर्णांकo the command पढ़ो/ग_लिखो port reg
		 * in chunks of 64 bytes
		 */
		स_रखो(temp, 0, माप(temp));
		स_नकल(temp, fw,
		       min(bytes_reमुख्यing, HELPER_FW_LOAD_CHUNK_SZ));
		mdelay(10);
		err = spu_ग_लिखो(card, IF_SPI_CMD_RDWRPORT_REG,
					temp, HELPER_FW_LOAD_CHUNK_SZ);
		अगर (err)
			जाओ out;

		/* Interrupt the boot code */
		err = spu_ग_लिखो_u16(card, IF_SPI_HOST_INT_STATUS_REG, 0);
		अगर (err)
			जाओ out;
		err = spu_ग_लिखो_u16(card, IF_SPI_CARD_INT_CAUSE_REG,
				       IF_SPI_CIC_CMD_DOWNLOAD_OVER);
		अगर (err)
			जाओ out;
		bytes_reमुख्यing -= HELPER_FW_LOAD_CHUNK_SZ;
		fw += HELPER_FW_LOAD_CHUNK_SZ;
	पूर्ण

	/*
	 * Once the helper / single stage firmware करोwnload is complete,
	 * ग_लिखो 0 to scratch pad 1 and पूर्णांकerrupt the
	 * bootloader. This completes the helper करोwnload.
	 */
	err = spu_ग_लिखो_u16(card, IF_SPI_SCRATCH_1_REG, FIRMWARE_DNLD_OK);
	अगर (err)
		जाओ out;
	err = spu_ग_लिखो_u16(card, IF_SPI_HOST_INT_STATUS_REG, 0);
	अगर (err)
		जाओ out;
	err = spu_ग_लिखो_u16(card, IF_SPI_CARD_INT_CAUSE_REG,
				IF_SPI_CIC_CMD_DOWNLOAD_OVER);
out:
	अगर (err)
		pr_err("failed to load helper firmware (err=%d)\n", err);

	वापस err;
पूर्ण

/*
 * Returns the length of the next packet the firmware expects us to send.
 * Sets crc_err अगर the previous transfer had a CRC error.
 */
अटल पूर्णांक अगर_spi_prog_मुख्य_firmware_check_len(काष्ठा अगर_spi_card *card,
						पूर्णांक *crc_err)
अणु
	u16 len;
	पूर्णांक err = 0;

	/*
	 * रुको until the host पूर्णांकerrupt status रेजिस्टर indicates
	 * that we are पढ़ोy to करोwnload
	 */
	err = spu_रुको_क्रम_u16(card, IF_SPI_HOST_INT_STATUS_REG,
				IF_SPI_HIST_CMD_DOWNLOAD_RDY,
				IF_SPI_HIST_CMD_DOWNLOAD_RDY);
	अगर (err) अणु
		pr_err("timed out waiting for host_int_status\n");
		वापस err;
	पूर्ण

	/* Ask the device how many bytes of firmware it wants. */
	err = spu_पढ़ो_u16(card, IF_SPI_SCRATCH_1_REG, &len);
	अगर (err)
		वापस err;

	अगर (len > IF_SPI_CMD_BUF_SIZE) अणु
		pr_err("firmware load device requested a larger transfer than we are prepared to handle (len = %d)\n",
		       len);
		वापस -EIO;
	पूर्ण
	अगर (len & 0x1) अणु
		lbs_deb_spi("%s: crc error\n", __func__);
		len &= ~0x1;
		*crc_err = 1;
	पूर्ण अन्यथा
		*crc_err = 0;

	वापस len;
पूर्ण

अटल पूर्णांक अगर_spi_prog_मुख्य_firmware(काष्ठा अगर_spi_card *card,
					स्थिर काष्ठा firmware *firmware)
अणु
	काष्ठा lbs_निजी *priv = card->priv;
	पूर्णांक len, prev_len;
	पूर्णांक bytes, crc_err = 0, err = 0;
	स्थिर u8 *fw;
	u16 num_crc_errs;

	err = spu_set_पूर्णांकerrupt_mode(card, 1, 0);
	अगर (err)
		जाओ out;

	err = spu_रुको_क्रम_u16(card, IF_SPI_SCRATCH_1_REG, 0, 0);
	अगर (err) अणु
		netdev_err(priv->dev,
			   "%s: timed out waiting for initial scratch reg = 0\n",
			   __func__);
		जाओ out;
	पूर्ण

	num_crc_errs = 0;
	prev_len = 0;
	bytes = firmware->size;
	fw = firmware->data;
	जबतक ((len = अगर_spi_prog_मुख्य_firmware_check_len(card, &crc_err))) अणु
		अगर (len < 0) अणु
			err = len;
			जाओ out;
		पूर्ण
		अगर (bytes < 0) अणु
			/*
			 * If there are no more bytes left, we would normally
			 * expect to have terminated with len = 0
			 */
			netdev_err(priv->dev,
				   "Firmware load wants more bytes than we have to offer.\n");
			अवरोध;
		पूर्ण
		अगर (crc_err) अणु
			/* Previous transfer failed. */
			अगर (++num_crc_errs > MAX_MAIN_FW_LOAD_CRC_ERR) अणु
				pr_err("Too many CRC errors encountered in firmware load.\n");
				err = -EIO;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Previous transfer succeeded. Advance counters. */
			bytes -= prev_len;
			fw += prev_len;
		पूर्ण
		अगर (bytes < len) अणु
			स_रखो(card->cmd_buffer, 0, len);
			स_नकल(card->cmd_buffer, fw, bytes);
		पूर्ण अन्यथा
			स_नकल(card->cmd_buffer, fw, len);

		err = spu_ग_लिखो_u16(card, IF_SPI_HOST_INT_STATUS_REG, 0);
		अगर (err)
			जाओ out;
		err = spu_ग_लिखो(card, IF_SPI_CMD_RDWRPORT_REG,
				card->cmd_buffer, len);
		अगर (err)
			जाओ out;
		err = spu_ग_लिखो_u16(card, IF_SPI_CARD_INT_CAUSE_REG ,
					IF_SPI_CIC_CMD_DOWNLOAD_OVER);
		अगर (err)
			जाओ out;
		prev_len = len;
	पूर्ण
	अगर (bytes > prev_len) अणु
		pr_err("firmware load wants fewer bytes than we have to offer\n");
	पूर्ण

	/* Confirm firmware करोwnload */
	err = spu_रुको_क्रम_u32(card, IF_SPI_SCRATCH_4_REG,
					SUCCESSFUL_FW_DOWNLOAD_MAGIC);
	अगर (err) अणु
		pr_err("failed to confirm the firmware download\n");
		जाओ out;
	पूर्ण

out:
	अगर (err)
		pr_err("failed to load firmware (err=%d)\n", err);

	वापस err;
पूर्ण

/*
 * SPI Transfer Thपढ़ो
 *
 * The SPI worker handles all SPI transfers, so there is no need क्रम a lock.
 */

/* Move a command from the card to the host */
अटल पूर्णांक अगर_spi_c2h_cmd(काष्ठा अगर_spi_card *card)
अणु
	काष्ठा lbs_निजी *priv = card->priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;
	u16 len;
	u8 i;

	/*
	 * We need a buffer big enough to handle whatever people send to
	 * hw_host_to_card
	 */
	BUILD_BUG_ON(IF_SPI_CMD_BUF_SIZE < LBS_CMD_BUFFER_SIZE);
	BUILD_BUG_ON(IF_SPI_CMD_BUF_SIZE < LBS_UPLD_SIZE);

	/*
	 * It's just annoying if the buffer size isn't a multiple of 4, because
	 * then we might have len < IF_SPI_CMD_BUF_SIZE but
	 * ALIGN(len, 4) > IF_SPI_CMD_BUF_SIZE
	 */
	BUILD_BUG_ON(IF_SPI_CMD_BUF_SIZE % 4 != 0);

	/* How many bytes are there to पढ़ो? */
	err = spu_पढ़ो_u16(card, IF_SPI_SCRATCH_2_REG, &len);
	अगर (err)
		जाओ out;
	अगर (!len) अणु
		netdev_err(priv->dev, "%s: error: card has no data for host\n",
			   __func__);
		err = -EINVAL;
		जाओ out;
	पूर्ण अन्यथा अगर (len > IF_SPI_CMD_BUF_SIZE) अणु
		netdev_err(priv->dev,
			   "%s: error: response packet too large: %d bytes, but maximum is %d\n",
			   __func__, len, IF_SPI_CMD_BUF_SIZE);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Read the data from the WLAN module पूर्णांकo our command buffer */
	err = spu_पढ़ो(card, IF_SPI_CMD_RDWRPORT_REG,
				card->cmd_buffer, ALIGN(len, 4));
	अगर (err)
		जाओ out;

	spin_lock_irqsave(&priv->driver_lock, flags);
	i = (priv->resp_idx == 0) ? 1 : 0;
	BUG_ON(priv->resp_len[i]);
	priv->resp_len[i] = len;
	स_नकल(priv->resp_buf[i], card->cmd_buffer, len);
	lbs_notअगरy_command_response(priv, i);
	spin_unlock_irqrestore(&priv->driver_lock, flags);

out:
	अगर (err)
		netdev_err(priv->dev, "%s: err=%d\n", __func__, err);

	वापस err;
पूर्ण

/* Move data from the card to the host */
अटल पूर्णांक अगर_spi_c2h_data(काष्ठा अगर_spi_card *card)
अणु
	काष्ठा lbs_निजी *priv = card->priv;
	काष्ठा sk_buff *skb;
	अक्षर *data;
	u16 len;
	पूर्णांक err = 0;

	/* How many bytes are there to पढ़ो? */
	err = spu_पढ़ो_u16(card, IF_SPI_SCRATCH_1_REG, &len);
	अगर (err)
		जाओ out;
	अगर (!len) अणु
		netdev_err(priv->dev, "%s: error: card has no data for host\n",
			   __func__);
		err = -EINVAL;
		जाओ out;
	पूर्ण अन्यथा अगर (len > MRVDRV_ETH_RX_PACKET_BUFFER_SIZE) अणु
		netdev_err(priv->dev,
			   "%s: error: card has %d bytes of data, but our maximum skb size is %zu\n",
			   __func__, len, MRVDRV_ETH_RX_PACKET_BUFFER_SIZE);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* TODO: should we allocate a smaller skb अगर we have less data? */
	skb = dev_alloc_skb(MRVDRV_ETH_RX_PACKET_BUFFER_SIZE);
	अगर (!skb) अणु
		err = -ENOBUFS;
		जाओ out;
	पूर्ण
	skb_reserve(skb, IPFIELD_ALIGN_OFFSET);
	data = skb_put(skb, len);

	/* Read the data from the WLAN module पूर्णांकo our skb... */
	err = spu_पढ़ो(card, IF_SPI_DATA_RDWRPORT_REG, data, ALIGN(len, 4));
	अगर (err) अणु
		dev_kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	/* pass the SKB to libertas */
	err = lbs_process_rxed_packet(card->priv, skb);
	/* lbs_process_rxed_packet() consumes the skb */

out:
	अगर (err)
		netdev_err(priv->dev, "%s: err=%d\n", __func__, err);

	वापस err;
पूर्ण

/* Move data or a command from the host to the card. */
अटल व्योम अगर_spi_h2c(काष्ठा अगर_spi_card *card,
			काष्ठा अगर_spi_packet *packet, पूर्णांक type)
अणु
	काष्ठा lbs_निजी *priv = card->priv;
	पूर्णांक err = 0;
	u16 port_reg;

	चयन (type) अणु
	हाल MVMS_DAT:
		port_reg = IF_SPI_DATA_RDWRPORT_REG;
		अवरोध;
	हाल MVMS_CMD:
		port_reg = IF_SPI_CMD_RDWRPORT_REG;
		अवरोध;
	शेष:
		netdev_err(priv->dev, "can't transfer buffer of type %d\n",
			   type);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Write the data to the card */
	err = spu_ग_लिखो(card, port_reg, packet->buffer, packet->blen);
	अगर (err)
		जाओ out;

out:
	kमुक्त(packet);

	अगर (err)
		netdev_err(priv->dev, "%s: error %d\n", __func__, err);
पूर्ण

/* Inक्रमm the host about a card event */
अटल व्योम अगर_spi_e2h(काष्ठा अगर_spi_card *card)
अणु
	पूर्णांक err = 0;
	u32 cause;
	काष्ठा lbs_निजी *priv = card->priv;

	err = spu_पढ़ो_u32(card, IF_SPI_SCRATCH_3_REG, &cause);
	अगर (err)
		जाओ out;

	/* re-enable the card event पूर्णांकerrupt */
	spu_ग_लिखो_u16(card, IF_SPI_HOST_INT_STATUS_REG,
			~IF_SPI_HICU_CARD_EVENT);

	/* generate a card पूर्णांकerrupt */
	spu_ग_लिखो_u16(card, IF_SPI_CARD_INT_CAUSE_REG, IF_SPI_CIC_HOST_EVENT);

	lbs_queue_event(priv, cause & 0xff);
out:
	अगर (err)
		netdev_err(priv->dev, "%s: error %d\n", __func__, err);
पूर्ण

अटल व्योम अगर_spi_host_to_card_worker(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक err;
	काष्ठा अगर_spi_card *card;
	u16 hiStatus;
	अचिन्हित दीर्घ flags;
	काष्ठा अगर_spi_packet *packet;
	काष्ठा lbs_निजी *priv;

	card = container_of(work, काष्ठा अगर_spi_card, packet_work);
	priv = card->priv;

	/*
	 * Read the host पूर्णांकerrupt status रेजिस्टर to see what we
	 * can करो.
	 */
	err = spu_पढ़ो_u16(card, IF_SPI_HOST_INT_STATUS_REG,
				&hiStatus);
	अगर (err) अणु
		netdev_err(priv->dev, "I/O error\n");
		जाओ err;
	पूर्ण

	अगर (hiStatus & IF_SPI_HIST_CMD_UPLOAD_RDY) अणु
		err = अगर_spi_c2h_cmd(card);
		अगर (err)
			जाओ err;
	पूर्ण
	अगर (hiStatus & IF_SPI_HIST_RX_UPLOAD_RDY) अणु
		err = अगर_spi_c2h_data(card);
		अगर (err)
			जाओ err;
	पूर्ण

	/*
	 * workaround: in PS mode, the card करोes not set the Command
	 * Download Ready bit, but it sets TX Download Ready.
	 */
	अगर (hiStatus & IF_SPI_HIST_CMD_DOWNLOAD_RDY ||
	   (card->priv->psstate != PS_STATE_FULL_POWER &&
	    (hiStatus & IF_SPI_HIST_TX_DOWNLOAD_RDY))) अणु
		/*
		 * This means two things. First of all,
		 * अगर there was a previous command sent, the card has
		 * successfully received it.
		 * Secondly, it is now पढ़ोy to करोwnload another
		 * command.
		 */
		lbs_host_to_card_करोne(card->priv);

		/* Do we have any command packets from the host to send? */
		packet = शून्य;
		spin_lock_irqsave(&card->buffer_lock, flags);
		अगर (!list_empty(&card->cmd_packet_list)) अणु
			packet = (काष्ठा अगर_spi_packet *)(card->
					cmd_packet_list.next);
			list_del(&packet->list);
		पूर्ण
		spin_unlock_irqrestore(&card->buffer_lock, flags);

		अगर (packet)
			अगर_spi_h2c(card, packet, MVMS_CMD);
	पूर्ण
	अगर (hiStatus & IF_SPI_HIST_TX_DOWNLOAD_RDY) अणु
		/* Do we have any data packets from the host to send? */
		packet = शून्य;
		spin_lock_irqsave(&card->buffer_lock, flags);
		अगर (!list_empty(&card->data_packet_list)) अणु
			packet = (काष्ठा अगर_spi_packet *)(card->
					data_packet_list.next);
			list_del(&packet->list);
		पूर्ण
		spin_unlock_irqrestore(&card->buffer_lock, flags);

		अगर (packet)
			अगर_spi_h2c(card, packet, MVMS_DAT);
	पूर्ण
	अगर (hiStatus & IF_SPI_HIST_CARD_EVENT)
		अगर_spi_e2h(card);

err:
	अगर (err)
		netdev_err(priv->dev, "%s: got error %d\n", __func__, err);
पूर्ण

/*
 * Host to Card
 *
 * Called from Libertas to transfer some data to the WLAN device
 * We can't sleep here.
 */
अटल पूर्णांक अगर_spi_host_to_card(काष्ठा lbs_निजी *priv,
				u8 type, u8 *buf, u16 nb)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा अगर_spi_card *card = priv->card;
	काष्ठा अगर_spi_packet *packet;
	u16 blen;

	अगर (nb == 0) अणु
		netdev_err(priv->dev, "%s: invalid size requested: %d\n",
			   __func__, nb);
		err = -EINVAL;
		जाओ out;
	पूर्ण
	blen = ALIGN(nb, 4);
	packet = kzalloc(माप(काष्ठा अगर_spi_packet) + blen, GFP_ATOMIC);
	अगर (!packet) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण
	packet->blen = blen;
	स_नकल(packet->buffer, buf, nb);
	स_रखो(packet->buffer + nb, 0, blen - nb);

	चयन (type) अणु
	हाल MVMS_CMD:
		priv->dnld_sent = DNLD_CMD_SENT;
		spin_lock_irqsave(&card->buffer_lock, flags);
		list_add_tail(&packet->list, &card->cmd_packet_list);
		spin_unlock_irqrestore(&card->buffer_lock, flags);
		अवरोध;
	हाल MVMS_DAT:
		priv->dnld_sent = DNLD_DATA_SENT;
		spin_lock_irqsave(&card->buffer_lock, flags);
		list_add_tail(&packet->list, &card->data_packet_list);
		spin_unlock_irqrestore(&card->buffer_lock, flags);
		अवरोध;
	शेष:
		kमुक्त(packet);
		netdev_err(priv->dev, "can't transfer buffer of type %d\n",
			   type);
		err = -EINVAL;
		अवरोध;
	पूर्ण

	/* Queue spi xfer work */
	queue_work(card->workqueue, &card->packet_work);
out:
	वापस err;
पूर्ण

/*
 * Host Interrupts
 *
 * Service incoming पूर्णांकerrupts from the WLAN device. We can't sleep here, so
 * करोn't try to talk on the SPI bus, just queue the SPI xfer work.
 */
अटल irqवापस_t अगर_spi_host_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा अगर_spi_card *card = dev_id;

	queue_work(card->workqueue, &card->packet_work);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * SPI callbacks
 */

अटल पूर्णांक अगर_spi_init_card(काष्ठा अगर_spi_card *card)
अणु
	काष्ठा lbs_निजी *priv = card->priv;
	पूर्णांक err, i;
	u32 scratch;
	स्थिर काष्ठा firmware *helper = शून्य;
	स्थिर काष्ठा firmware *मुख्यfw = शून्य;

	err = spu_init(card, card->pdata->use_dummy_ग_लिखोs);
	अगर (err)
		जाओ out;
	err = spu_get_chip_revision(card, &card->card_id, &card->card_rev);
	अगर (err)
		जाओ out;

	err = spu_पढ़ो_u32(card, IF_SPI_SCRATCH_4_REG, &scratch);
	अगर (err)
		जाओ out;
	अगर (scratch == SUCCESSFUL_FW_DOWNLOAD_MAGIC)
		lbs_deb_spi("Firmware is already loaded for "
			    "Marvell WLAN 802.11 adapter\n");
	अन्यथा अणु
		/* Check अगर we support this card */
		क्रम (i = 0; i < ARRAY_SIZE(fw_table); i++) अणु
			अगर (card->card_id == fw_table[i].model)
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(fw_table)) अणु
			netdev_err(priv->dev, "Unsupported chip_id: 0x%02x\n",
				   card->card_id);
			err = -ENODEV;
			जाओ out;
		पूर्ण

		err = lbs_get_firmware(&card->spi->dev, card->card_id,
					&fw_table[0], &helper, &मुख्यfw);
		अगर (err) अणु
			netdev_err(priv->dev, "failed to find firmware (%d)\n",
				   err);
			जाओ out;
		पूर्ण

		lbs_deb_spi("Initializing FW for Marvell WLAN 802.11 adapter "
				"(chip_id = 0x%04x, chip_rev = 0x%02x) "
				"attached to SPI bus_num %d, chip_select %d. "
				"spi->max_speed_hz=%d\n",
				card->card_id, card->card_rev,
				card->spi->master->bus_num,
				card->spi->chip_select,
				card->spi->max_speed_hz);
		err = अगर_spi_prog_helper_firmware(card, helper);
		अगर (err)
			जाओ out;
		err = अगर_spi_prog_मुख्य_firmware(card, मुख्यfw);
		अगर (err)
			जाओ out;
		lbs_deb_spi("loaded FW for Marvell WLAN 802.11 adapter\n");
	पूर्ण

	err = spu_set_पूर्णांकerrupt_mode(card, 0, 1);
	अगर (err)
		जाओ out;

out:
	वापस err;
पूर्ण

अटल व्योम अगर_spi_resume_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा अगर_spi_card *card;

	card = container_of(work, काष्ठा अगर_spi_card, resume_work);

	अगर (card->suspended) अणु
		अगर (card->pdata->setup)
			card->pdata->setup(card->spi);

		/* Init card ... */
		अगर_spi_init_card(card);

		enable_irq(card->spi->irq);

		/* And resume it ... */
		lbs_resume(card->priv);

		card->suspended = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक अगर_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा अगर_spi_card *card;
	काष्ठा lbs_निजी *priv = शून्य;
	काष्ठा libertas_spi_platक्रमm_data *pdata = dev_get_platdata(&spi->dev);
	पूर्णांक err = 0;

	अगर (!pdata) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (pdata->setup) अणु
		err = pdata->setup(spi);
		अगर (err)
			जाओ out;
	पूर्ण

	/* Allocate card काष्ठाure to represent this specअगरic device */
	card = kzalloc(माप(काष्ठा अगर_spi_card), GFP_KERNEL);
	अगर (!card) अणु
		err = -ENOMEM;
		जाओ tearकरोwn;
	पूर्ण
	spi_set_drvdata(spi, card);
	card->pdata = pdata;
	card->spi = spi;
	card->prev_xfer_समय = jअगरfies;

	INIT_LIST_HEAD(&card->cmd_packet_list);
	INIT_LIST_HEAD(&card->data_packet_list);
	spin_lock_init(&card->buffer_lock);

	/* Initialize the SPI Interface Unit */

	/* Firmware load */
	err = अगर_spi_init_card(card);
	अगर (err)
		जाओ मुक्त_card;

	/*
	 * Register our card with libertas.
	 * This will call alloc_etherdev.
	 */
	priv = lbs_add_card(card, &spi->dev);
	अगर (IS_ERR(priv)) अणु
		err = PTR_ERR(priv);
		जाओ मुक्त_card;
	पूर्ण
	card->priv = priv;
	priv->setup_fw_on_resume = 1;
	priv->card = card;
	priv->hw_host_to_card = अगर_spi_host_to_card;
	priv->enter_deep_sleep = शून्य;
	priv->निकास_deep_sleep = शून्य;
	priv->reset_deep_sleep_wakeup = शून्य;
	priv->fw_पढ़ोy = 1;

	/* Initialize पूर्णांकerrupt handling stuff. */
	card->workqueue = alloc_workqueue("libertas_spi", WQ_MEM_RECLAIM, 0);
	अगर (!card->workqueue) अणु
		err = -ENOMEM;
		जाओ हटाओ_card;
	पूर्ण
	INIT_WORK(&card->packet_work, अगर_spi_host_to_card_worker);
	INIT_WORK(&card->resume_work, अगर_spi_resume_worker);

	err = request_irq(spi->irq, अगर_spi_host_पूर्णांकerrupt,
			IRQF_TRIGGER_FALLING, "libertas_spi", card);
	अगर (err) अणु
		pr_err("can't get host irq line-- request_irq failed\n");
		जाओ terminate_workqueue;
	पूर्ण

	/*
	 * Start the card.
	 * This will call रेजिस्टर_netdev, and we'll start
	 * getting पूर्णांकerrupts...
	 */
	err = lbs_start_card(priv);
	अगर (err)
		जाओ release_irq;

	lbs_deb_spi("Finished initializing WLAN module.\n");

	/* successful निकास */
	जाओ out;

release_irq:
	मुक्त_irq(spi->irq, card);
terminate_workqueue:
	destroy_workqueue(card->workqueue);
हटाओ_card:
	lbs_हटाओ_card(priv); /* will call मुक्त_netdev */
मुक्त_card:
	मुक्त_अगर_spi_card(card);
tearकरोwn:
	अगर (pdata->tearकरोwn)
		pdata->tearकरोwn(spi);
out:
	वापस err;
पूर्ण

अटल पूर्णांक libertas_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा अगर_spi_card *card = spi_get_drvdata(spi);
	काष्ठा lbs_निजी *priv = card->priv;

	lbs_deb_spi("libertas_spi_remove\n");

	cancel_work_sync(&card->resume_work);

	lbs_stop_card(priv);
	lbs_हटाओ_card(priv); /* will call मुक्त_netdev */

	मुक्त_irq(spi->irq, card);
	destroy_workqueue(card->workqueue);
	अगर (card->pdata->tearकरोwn)
		card->pdata->tearकरोwn(spi);
	मुक्त_अगर_spi_card(card);

	वापस 0;
पूर्ण

अटल पूर्णांक अगर_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा अगर_spi_card *card = spi_get_drvdata(spi);

	अगर (!card->suspended) अणु
		lbs_suspend(card->priv);
		flush_workqueue(card->workqueue);
		disable_irq(spi->irq);

		अगर (card->pdata->tearकरोwn)
			card->pdata->tearकरोwn(spi);
		card->suspended = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक अगर_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा अगर_spi_card *card = spi_get_drvdata(spi);

	/* Schedule delayed work */
	schedule_work(&card->resume_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops अगर_spi_pm_ops = अणु
	.suspend	= अगर_spi_suspend,
	.resume		= अगर_spi_resume,
पूर्ण;

अटल काष्ठा spi_driver libertas_spi_driver = अणु
	.probe	= अगर_spi_probe,
	.हटाओ = libertas_spi_हटाओ,
	.driver = अणु
		.name	= "libertas_spi",
		.pm	= &अगर_spi_pm_ops,
	पूर्ण,
पूर्ण;

/*
 * Module functions
 */

अटल पूर्णांक __init अगर_spi_init_module(व्योम)
अणु
	पूर्णांक ret = 0;

	prपूर्णांकk(KERN_INFO "libertas_spi: Libertas SPI driver\n");
	ret = spi_रेजिस्टर_driver(&libertas_spi_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास अगर_spi_निकास_module(व्योम)
अणु
	spi_unरेजिस्टर_driver(&libertas_spi_driver);
पूर्ण

module_init(अगर_spi_init_module);
module_निकास(अगर_spi_निकास_module);

MODULE_DESCRIPTION("Libertas SPI WLAN Driver");
MODULE_AUTHOR("Andrey Yurovsky <andrey@cozybit.com>, "
	      "Colin McCabe <colin@cozybit.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:libertas_spi");
