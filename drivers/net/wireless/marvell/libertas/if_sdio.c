<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/net/wireless/libertas/अगर_sdio.c
 *
 *  Copyright 2007-2008 Pierre Ossman
 *
 * Inspired by अगर_cs.c, Copyright 2007 Holger Schurig
 *
 * This hardware has more or less no CMD53 support, so all रेजिस्टरs
 * must be accessed using sdio_पढ़ोb()/sdio_ग_लिखोb().
 *
 * Transfers must be in one transaction or the firmware goes bonkers.
 * This means that the transfer must either be small enough to करो a
 * byte based transfer or it must be padded to a multiple of the
 * current block size.
 *
 * As SDIO is still new to the kernel, it is unक्रमtunately common with
 * bugs in the host controllers related to that. One such bug is that
 * controllers cannot करो transfers that aren't a multiple of 4 bytes.
 * If you करोn't have समय to fix the host controller driver, you can
 * work around the problem by modअगरying अगर_sdio_host_to_card() and
 * अगर_sdio_card_to_host() to pad the data.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "host.h"
#समावेश "decl.h"
#समावेश "defs.h"
#समावेश "dev.h"
#समावेश "cmd.h"
#समावेश "if_sdio.h"

अटल व्योम अगर_sdio_पूर्णांकerrupt(काष्ठा sdio_func *func);

/* The अगर_sdio_हटाओ() callback function is called when
 * user हटाओs this module from kernel space or ejects
 * the card from the slot. The driver handles these 2 हालs
 * dअगरferently क्रम SD8688 combo chip.
 * If the user is removing the module, the FUNC_SHUTDOWN
 * command क्रम SD8688 is sent to the firmware.
 * If the card is हटाओd, there is no need to send this command.
 *
 * The variable 'user_rmmod' is used to distinguish these two
 * scenarios. This flag is initialized as FALSE in हाल the card
 * is हटाओd, and will be set to TRUE क्रम module removal when
 * module_निकास function is called.
 */
अटल u8 user_rmmod;

अटल स्थिर काष्ठा sdio_device_id अगर_sdio_ids[] = अणु
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL,
			SDIO_DEVICE_ID_MARVELL_LIBERTAS) पूर्ण,
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MARVELL,
			SDIO_DEVICE_ID_MARVELL_8688_WLAN) पूर्ण,
	अणु /* end: all zeroes */				पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(sdio, अगर_sdio_ids);

#घोषणा MODEL_8385	0x04
#घोषणा MODEL_8686	0x0b
#घोषणा MODEL_8688	0x10

अटल स्थिर काष्ठा lbs_fw_table fw_table[] = अणु
	अणु MODEL_8385, "libertas/sd8385_helper.bin", "libertas/sd8385.bin" पूर्ण,
	अणु MODEL_8385, "sd8385_helper.bin", "sd8385.bin" पूर्ण,
	अणु MODEL_8686, "libertas/sd8686_v9_helper.bin", "libertas/sd8686_v9.bin" पूर्ण,
	अणु MODEL_8686, "libertas/sd8686_v8_helper.bin", "libertas/sd8686_v8.bin" पूर्ण,
	अणु MODEL_8686, "sd8686_helper.bin", "sd8686.bin" पूर्ण,
	अणु MODEL_8688, "libertas/sd8688_helper.bin", "libertas/sd8688.bin" पूर्ण,
	अणु MODEL_8688, "sd8688_helper.bin", "sd8688.bin" पूर्ण,
	अणु 0, शून्य, शून्य पूर्ण
पूर्ण;
MODULE_FIRMWARE("libertas/sd8385_helper.bin");
MODULE_FIRMWARE("libertas/sd8385.bin");
MODULE_FIRMWARE("sd8385_helper.bin");
MODULE_FIRMWARE("sd8385.bin");
MODULE_FIRMWARE("libertas/sd8686_v9_helper.bin");
MODULE_FIRMWARE("libertas/sd8686_v9.bin");
MODULE_FIRMWARE("libertas/sd8686_v8_helper.bin");
MODULE_FIRMWARE("libertas/sd8686_v8.bin");
MODULE_FIRMWARE("sd8686_helper.bin");
MODULE_FIRMWARE("sd8686.bin");
MODULE_FIRMWARE("libertas/sd8688_helper.bin");
MODULE_FIRMWARE("libertas/sd8688.bin");
MODULE_FIRMWARE("sd8688_helper.bin");
MODULE_FIRMWARE("sd8688.bin");

काष्ठा अगर_sdio_packet अणु
	काष्ठा अगर_sdio_packet	*next;
	u16			nb;
	u8			buffer[] __aligned(4);
पूर्ण;

काष्ठा अगर_sdio_card अणु
	काष्ठा sdio_func	*func;
	काष्ठा lbs_निजी	*priv;

	पूर्णांक			model;
	अचिन्हित दीर्घ		ioport;
	अचिन्हित पूर्णांक		scratch_reg;
	bool			started;
	रुको_queue_head_t	pwron_रुकोq;

	u8			buffer[65536] __attribute__((aligned(4)));

	spinlock_t		lock;
	काष्ठा अगर_sdio_packet	*packets;

	काष्ठा workqueue_काष्ठा	*workqueue;
	काष्ठा work_काष्ठा	packet_worker;

	u8			rx_unit;
पूर्ण;

अटल व्योम अगर_sdio_finish_घातer_on(काष्ठा अगर_sdio_card *card);
अटल पूर्णांक अगर_sdio_घातer_off(काष्ठा अगर_sdio_card *card);

/********************************************************************/
/* I/O                                                              */
/********************************************************************/

/*
 *  For SD8385/SD8686, this function पढ़ोs firmware status after
 *  the image is करोwnloaded, or पढ़ोs RX packet length when
 *  पूर्णांकerrupt (with IF_SDIO_H_INT_UPLD bit set) is received.
 *  For SD8688, this function पढ़ोs firmware status only.
 */
अटल u16 अगर_sdio_पढ़ो_scratch(काष्ठा अगर_sdio_card *card, पूर्णांक *err)
अणु
	पूर्णांक ret;
	u16 scratch;

	scratch = sdio_पढ़ोb(card->func, card->scratch_reg, &ret);
	अगर (!ret)
		scratch |= sdio_पढ़ोb(card->func, card->scratch_reg + 1,
					&ret) << 8;

	अगर (err)
		*err = ret;

	अगर (ret)
		वापस 0xffff;

	वापस scratch;
पूर्ण

अटल u8 अगर_sdio_पढ़ो_rx_unit(काष्ठा अगर_sdio_card *card)
अणु
	पूर्णांक ret;
	u8 rx_unit;

	rx_unit = sdio_पढ़ोb(card->func, IF_SDIO_RX_UNIT, &ret);

	अगर (ret)
		rx_unit = 0;

	वापस rx_unit;
पूर्ण

अटल u16 अगर_sdio_पढ़ो_rx_len(काष्ठा अगर_sdio_card *card, पूर्णांक *err)
अणु
	पूर्णांक ret;
	u16 rx_len;

	चयन (card->model) अणु
	हाल MODEL_8385:
	हाल MODEL_8686:
		rx_len = अगर_sdio_पढ़ो_scratch(card, &ret);
		अवरोध;
	हाल MODEL_8688:
	शेष: /* क्रम newer chipsets */
		rx_len = sdio_पढ़ोb(card->func, IF_SDIO_RX_LEN, &ret);
		अगर (!ret)
			rx_len <<= card->rx_unit;
		अन्यथा
			rx_len = 0xffff;	/* invalid length */

		अवरोध;
	पूर्ण

	अगर (err)
		*err = ret;

	वापस rx_len;
पूर्ण

अटल पूर्णांक अगर_sdio_handle_cmd(काष्ठा अगर_sdio_card *card,
		u8 *buffer, अचिन्हित size)
अणु
	काष्ठा lbs_निजी *priv = card->priv;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	u8 i;

	अगर (size > LBS_CMD_BUFFER_SIZE) अणु
		lbs_deb_sdio("response packet too large (%d bytes)\n",
			(पूर्णांक)size);
		ret = -E2BIG;
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&priv->driver_lock, flags);

	i = (priv->resp_idx == 0) ? 1 : 0;
	BUG_ON(priv->resp_len[i]);
	priv->resp_len[i] = size;
	स_नकल(priv->resp_buf[i], buffer, size);
	lbs_notअगरy_command_response(priv, i);

	spin_unlock_irqrestore(&priv->driver_lock, flags);

	ret = 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक अगर_sdio_handle_data(काष्ठा अगर_sdio_card *card,
		u8 *buffer, अचिन्हित size)
अणु
	पूर्णांक ret;
	काष्ठा sk_buff *skb;

	अगर (size > MRVDRV_ETH_RX_PACKET_BUFFER_SIZE) अणु
		lbs_deb_sdio("response packet too large (%d bytes)\n",
			(पूर्णांक)size);
		ret = -E2BIG;
		जाओ out;
	पूर्ण

	skb = dev_alloc_skb(MRVDRV_ETH_RX_PACKET_BUFFER_SIZE + NET_IP_ALIGN);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	skb_reserve(skb, NET_IP_ALIGN);

	skb_put_data(skb, buffer, size);

	lbs_process_rxed_packet(card->priv, skb);

	ret = 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक अगर_sdio_handle_event(काष्ठा अगर_sdio_card *card,
		u8 *buffer, अचिन्हित size)
अणु
	पूर्णांक ret;
	u32 event;

	अगर (card->model == MODEL_8385) अणु
		event = sdio_पढ़ोb(card->func, IF_SDIO_EVENT, &ret);
		अगर (ret)
			जाओ out;

		/* right shअगरt 3 bits to get the event id */
		event >>= 3;
	पूर्ण अन्यथा अणु
		अगर (size < 4) अणु
			lbs_deb_sdio("event packet too small (%d bytes)\n",
				(पूर्णांक)size);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		event = buffer[3] << 24;
		event |= buffer[2] << 16;
		event |= buffer[1] << 8;
		event |= buffer[0] << 0;
	पूर्ण

	lbs_queue_event(card->priv, event & 0xFF);
	ret = 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक अगर_sdio_रुको_status(काष्ठा अगर_sdio_card *card, स्थिर u8 condition)
अणु
	u8 status;
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret = 0;

	समयout = jअगरfies + HZ;
	जबतक (1) अणु
		status = sdio_पढ़ोb(card->func, IF_SDIO_STATUS, &ret);
		अगर (ret)
			वापस ret;
		अगर ((status & condition) == condition)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
		mdelay(1);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक अगर_sdio_card_to_host(काष्ठा अगर_sdio_card *card)
अणु
	पूर्णांक ret;
	u16 size, type, chunk;

	size = अगर_sdio_पढ़ो_rx_len(card, &ret);
	अगर (ret)
		जाओ out;

	अगर (size < 4) अणु
		lbs_deb_sdio("invalid packet size (%d bytes) from firmware\n",
			(पूर्णांक)size);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = अगर_sdio_रुको_status(card, IF_SDIO_IO_RDY);
	अगर (ret)
		जाओ out;

	/*
	 * The transfer must be in one transaction or the firmware
	 * goes suicidal. There's no way to guarantee that क्रम all
	 * controllers, but we can at least try.
	 */
	chunk = sdio_align_size(card->func, size);

	ret = sdio_पढ़ोsb(card->func, card->buffer, card->ioport, chunk);
	अगर (ret)
		जाओ out;

	chunk = card->buffer[0] | (card->buffer[1] << 8);
	type = card->buffer[2] | (card->buffer[3] << 8);

	lbs_deb_sdio("packet of type %d and size %d bytes\n",
		(पूर्णांक)type, (पूर्णांक)chunk);

	अगर (chunk > size) अणु
		lbs_deb_sdio("packet fragment (%d > %d)\n",
			(पूर्णांक)chunk, (पूर्णांक)size);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (chunk < size) अणु
		lbs_deb_sdio("packet fragment (%d < %d)\n",
			(पूर्णांक)chunk, (पूर्णांक)size);
	पूर्ण

	चयन (type) अणु
	हाल MVMS_CMD:
		ret = अगर_sdio_handle_cmd(card, card->buffer + 4, chunk - 4);
		अगर (ret)
			जाओ out;
		अवरोध;
	हाल MVMS_DAT:
		ret = अगर_sdio_handle_data(card, card->buffer + 4, chunk - 4);
		अगर (ret)
			जाओ out;
		अवरोध;
	हाल MVMS_EVENT:
		ret = अगर_sdio_handle_event(card, card->buffer + 4, chunk - 4);
		अगर (ret)
			जाओ out;
		अवरोध;
	शेष:
		lbs_deb_sdio("invalid type (%d) from firmware\n",
				(पूर्णांक)type);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

out:
	अगर (ret)
		pr_err("problem fetching packet from firmware\n");

	वापस ret;
पूर्ण

अटल व्योम अगर_sdio_host_to_card_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा अगर_sdio_card *card;
	काष्ठा अगर_sdio_packet *packet;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	card = container_of(work, काष्ठा अगर_sdio_card, packet_worker);

	जबतक (1) अणु
		spin_lock_irqsave(&card->lock, flags);
		packet = card->packets;
		अगर (packet)
			card->packets = packet->next;
		spin_unlock_irqrestore(&card->lock, flags);

		अगर (!packet)
			अवरोध;

		sdio_claim_host(card->func);

		ret = अगर_sdio_रुको_status(card, IF_SDIO_IO_RDY);
		अगर (ret == 0) अणु
			ret = sdio_ग_लिखोsb(card->func, card->ioport,
					   packet->buffer, packet->nb);
		पूर्ण

		अगर (ret)
			pr_err("error %d sending packet to firmware\n", ret);

		sdio_release_host(card->func);

		kमुक्त(packet);
	पूर्ण
पूर्ण

/********************************************************************/
/* Firmware                                                         */
/********************************************************************/

#घोषणा FW_DL_READY_STATUS (IF_SDIO_IO_RDY | IF_SDIO_DL_RDY)

अटल पूर्णांक अगर_sdio_prog_helper(काष्ठा अगर_sdio_card *card,
				स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;
	u8 *chunk_buffer;
	u32 chunk_size;
	स्थिर u8 *firmware;
	माप_प्रकार size;

	chunk_buffer = kzalloc(64, GFP_KERNEL);
	अगर (!chunk_buffer) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	sdio_claim_host(card->func);

	ret = sdio_set_block_size(card->func, 32);
	अगर (ret)
		जाओ release;

	firmware = fw->data;
	size = fw->size;

	जबतक (size) अणु
		ret = अगर_sdio_रुको_status(card, FW_DL_READY_STATUS);
		अगर (ret)
			जाओ release;

		/* On some platक्रमms (like Davinci) the chip needs more समय
		 * between helper blocks.
		 */
		mdelay(2);

		chunk_size = min_t(माप_प्रकार, size, 60);

		*((__le32*)chunk_buffer) = cpu_to_le32(chunk_size);
		स_नकल(chunk_buffer + 4, firmware, chunk_size);
/*
		lbs_deb_sdio("sending %d bytes chunk\n", chunk_size);
*/
		ret = sdio_ग_लिखोsb(card->func, card->ioport,
				chunk_buffer, 64);
		अगर (ret)
			जाओ release;

		firmware += chunk_size;
		size -= chunk_size;
	पूर्ण

	/* an empty block marks the end of the transfer */
	स_रखो(chunk_buffer, 0, 4);
	ret = sdio_ग_लिखोsb(card->func, card->ioport, chunk_buffer, 64);
	अगर (ret)
		जाओ release;

	lbs_deb_sdio("waiting for helper to boot...\n");

	/* रुको क्रम the helper to boot by looking at the size रेजिस्टर */
	समयout = jअगरfies + HZ;
	जबतक (1) अणु
		u16 req_size;

		req_size = sdio_पढ़ोb(card->func, IF_SDIO_RD_BASE, &ret);
		अगर (ret)
			जाओ release;

		req_size |= sdio_पढ़ोb(card->func, IF_SDIO_RD_BASE + 1, &ret) << 8;
		अगर (ret)
			जाओ release;

		अगर (req_size != 0)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			ret = -ETIMEDOUT;
			जाओ release;
		पूर्ण

		msleep(10);
	पूर्ण

	ret = 0;

release:
	sdio_release_host(card->func);
	kमुक्त(chunk_buffer);

out:
	अगर (ret)
		pr_err("failed to load helper firmware\n");

	वापस ret;
पूर्ण

अटल पूर्णांक अगर_sdio_prog_real(काष्ठा अगर_sdio_card *card,
				स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;
	u8 *chunk_buffer;
	u32 chunk_size;
	स्थिर u8 *firmware;
	माप_प्रकार size, req_size;

	chunk_buffer = kzalloc(512, GFP_KERNEL);
	अगर (!chunk_buffer) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	sdio_claim_host(card->func);

	ret = sdio_set_block_size(card->func, 32);
	अगर (ret)
		जाओ release;

	firmware = fw->data;
	size = fw->size;

	जबतक (size) अणु
		समयout = jअगरfies + HZ;
		जबतक (1) अणु
			ret = अगर_sdio_रुको_status(card, FW_DL_READY_STATUS);
			अगर (ret)
				जाओ release;

			req_size = sdio_पढ़ोb(card->func, IF_SDIO_RD_BASE,
					&ret);
			अगर (ret)
				जाओ release;

			req_size |= sdio_पढ़ोb(card->func, IF_SDIO_RD_BASE + 1,
					&ret) << 8;
			अगर (ret)
				जाओ release;

			/*
			 * For SD8688 रुको until the length is not 0, 1 or 2
			 * beक्रमe करोwnloading the first FW block,
			 * since BOOT code ग_लिखोs the रेजिस्टर to indicate the
			 * helper/FW करोwnload winner,
			 * the value could be 1 or 2 (Func1 or Func2).
			 */
			अगर ((size != fw->size) || (req_size > 2))
				अवरोध;
			अगर (समय_after(jअगरfies, समयout)) अणु
				ret = -ETIMEDOUT;
				जाओ release;
			पूर्ण
			mdelay(1);
		पूर्ण

/*
		lbs_deb_sdio("firmware wants %d bytes\n", (पूर्णांक)req_size);
*/
		अगर (req_size == 0) अणु
			lbs_deb_sdio("firmware helper gave up early\n");
			ret = -EIO;
			जाओ release;
		पूर्ण

		अगर (req_size & 0x01) अणु
			lbs_deb_sdio("firmware helper signalled error\n");
			ret = -EIO;
			जाओ release;
		पूर्ण

		अगर (req_size > size)
			req_size = size;

		जबतक (req_size) अणु
			chunk_size = min_t(माप_प्रकार, req_size, 512);

			स_नकल(chunk_buffer, firmware, chunk_size);
/*
			lbs_deb_sdio("sending %d bytes (%d bytes) chunk\n",
				chunk_size, (chunk_size + 31) / 32 * 32);
*/
			ret = sdio_ग_लिखोsb(card->func, card->ioport,
				chunk_buffer, roundup(chunk_size, 32));
			अगर (ret)
				जाओ release;

			firmware += chunk_size;
			size -= chunk_size;
			req_size -= chunk_size;
		पूर्ण
	पूर्ण

	ret = 0;

	lbs_deb_sdio("waiting for firmware to boot...\n");

	/* रुको क्रम the firmware to boot */
	समयout = jअगरfies + HZ;
	जबतक (1) अणु
		u16 scratch;

		scratch = अगर_sdio_पढ़ो_scratch(card, &ret);
		अगर (ret)
			जाओ release;

		अगर (scratch == IF_SDIO_FIRMWARE_OK)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			ret = -ETIMEDOUT;
			जाओ release;
		पूर्ण

		msleep(10);
	पूर्ण

	ret = 0;

release:
	sdio_release_host(card->func);
	kमुक्त(chunk_buffer);

out:
	अगर (ret)
		pr_err("failed to load firmware\n");

	वापस ret;
पूर्ण

अटल व्योम अगर_sdio_करो_prog_firmware(काष्ठा lbs_निजी *priv, पूर्णांक ret,
				     स्थिर काष्ठा firmware *helper,
				     स्थिर काष्ठा firmware *मुख्यfw)
अणु
	काष्ठा अगर_sdio_card *card = priv->card;

	अगर (ret) अणु
		pr_err("failed to find firmware (%d)\n", ret);
		वापस;
	पूर्ण

	ret = अगर_sdio_prog_helper(card, helper);
	अगर (ret)
		वापस;

	lbs_deb_sdio("Helper firmware loaded\n");

	ret = अगर_sdio_prog_real(card, मुख्यfw);
	अगर (ret)
		वापस;

	lbs_deb_sdio("Firmware loaded\n");
	अगर_sdio_finish_घातer_on(card);
पूर्ण

अटल पूर्णांक अगर_sdio_prog_firmware(काष्ठा अगर_sdio_card *card)
अणु
	पूर्णांक ret;
	u16 scratch;

	/*
	 * Disable पूर्णांकerrupts
	 */
	sdio_claim_host(card->func);
	sdio_ग_लिखोb(card->func, 0x00, IF_SDIO_H_INT_MASK, &ret);
	sdio_release_host(card->func);

	sdio_claim_host(card->func);
	scratch = अगर_sdio_पढ़ो_scratch(card, &ret);
	sdio_release_host(card->func);

	lbs_deb_sdio("firmware status = %#x\n", scratch);
	lbs_deb_sdio("scratch ret = %d\n", ret);

	अगर (ret)
		जाओ out;


	/*
	 * The manual clearly describes that FEDC is the right code to use
	 * to detect firmware presence, but क्रम SD8686 it is not that simple.
	 * Scratch is also used to store the RX packet length, so we lose
	 * the FEDC value early on. So we use a non-zero check in order
	 * to validate firmware presence.
	 * Additionally, the SD8686 in the Gumstix always has the high scratch
	 * bit set, even when the firmware is not loaded. So we have to
	 * exclude that from the test.
	 */
	अगर (scratch == IF_SDIO_FIRMWARE_OK) अणु
		lbs_deb_sdio("firmware already loaded\n");
		अगर_sdio_finish_घातer_on(card);
		वापस 0;
	पूर्ण अन्यथा अगर ((card->model == MODEL_8686) && (scratch & 0x7fff)) अणु
		lbs_deb_sdio("firmware may be running\n");
		अगर_sdio_finish_घातer_on(card);
		वापस 0;
	पूर्ण

	ret = lbs_get_firmware_async(card->priv, &card->func->dev, card->model,
				     fw_table, अगर_sdio_करो_prog_firmware);

out:
	वापस ret;
पूर्ण

/********************************************************************/
/* Power management                                                 */
/********************************************************************/

/* Finish घातer on sequence (after firmware is loaded) */
अटल व्योम अगर_sdio_finish_घातer_on(काष्ठा अगर_sdio_card *card)
अणु
	काष्ठा sdio_func *func = card->func;
	काष्ठा lbs_निजी *priv = card->priv;
	पूर्णांक ret;

	sdio_claim_host(func);
	sdio_set_block_size(card->func, IF_SDIO_BLOCK_SIZE);

	/*
	 * Get rx_unit अगर the chip is SD8688 or newer.
	 * SD8385 & SD8686 करो not have rx_unit.
	 */
	अगर ((card->model != MODEL_8385)
			&& (card->model != MODEL_8686))
		card->rx_unit = अगर_sdio_पढ़ो_rx_unit(card);
	अन्यथा
		card->rx_unit = 0;

	/*
	 * Set up the पूर्णांकerrupt handler late.
	 *
	 * If we set it up earlier, the (buggy) hardware generates a spurious
	 * पूर्णांकerrupt, even beक्रमe the पूर्णांकerrupt has been enabled, with
	 * CCCR_INTx = 0.
	 *
	 * We रेजिस्टर the पूर्णांकerrupt handler late so that we can handle any
	 * spurious पूर्णांकerrupts, and also to aव्योम generation of that known
	 * spurious पूर्णांकerrupt in the first place.
	 */
	ret = sdio_claim_irq(func, अगर_sdio_पूर्णांकerrupt);
	अगर (ret)
		जाओ release;

	/*
	 * Enable पूर्णांकerrupts now that everything is set up
	 */
	sdio_ग_लिखोb(func, 0x0f, IF_SDIO_H_INT_MASK, &ret);
	अगर (ret)
		जाओ release_irq;

	sdio_release_host(func);

	/* Set fw_पढ़ोy beक्रमe queuing any commands so that
	 * lbs_thपढ़ो won't block from sending them to firmware.
	 */
	priv->fw_पढ़ोy = 1;

	/*
	 * FUNC_INIT is required क्रम SD8688 WLAN/BT multiple functions
	 */
	अगर (card->model == MODEL_8688) अणु
		काष्ठा cmd_header cmd;

		स_रखो(&cmd, 0, माप(cmd));

		lbs_deb_sdio("send function INIT command\n");
		अगर (__lbs_cmd(priv, CMD_FUNC_INIT, &cmd, माप(cmd),
				lbs_cmd_copyback, (अचिन्हित दीर्घ) &cmd))
			netdev_alert(priv->dev, "CMD_FUNC_INIT cmd failed\n");
	पूर्ण

	wake_up(&card->pwron_रुकोq);

	अगर (!card->started) अणु
		ret = lbs_start_card(priv);
		अगर_sdio_घातer_off(card);
		अगर (ret == 0) अणु
			card->started = true;
			/* Tell PM core that we करोn't need the card to be
			 * घातered now */
			pm_runसमय_put(&func->dev);
		पूर्ण
	पूर्ण

	वापस;

release_irq:
	sdio_release_irq(func);
release:
	sdio_release_host(func);
पूर्ण

अटल पूर्णांक अगर_sdio_घातer_on(काष्ठा अगर_sdio_card *card)
अणु
	काष्ठा sdio_func *func = card->func;
	काष्ठा mmc_host *host = func->card->host;
	पूर्णांक ret;

	sdio_claim_host(func);

	ret = sdio_enable_func(func);
	अगर (ret)
		जाओ release;

	/* For 1-bit transfers to the 8686 model, we need to enable the
	 * पूर्णांकerrupt flag in the CCCR रेजिस्टर. Set the MMC_QUIRK_LENIENT_FN0
	 * bit to allow access to non-venकरोr रेजिस्टरs. */
	अगर ((card->model == MODEL_8686) &&
	    (host->caps & MMC_CAP_SDIO_IRQ) &&
	    (host->ios.bus_width == MMC_BUS_WIDTH_1)) अणु
		u8 reg;

		func->card->quirks |= MMC_QUIRK_LENIENT_FN0;
		reg = sdio_f0_पढ़ोb(func, SDIO_CCCR_IF, &ret);
		अगर (ret)
			जाओ disable;

		reg |= SDIO_BUS_ECSI;
		sdio_f0_ग_लिखोb(func, reg, SDIO_CCCR_IF, &ret);
		अगर (ret)
			जाओ disable;
	पूर्ण

	card->ioport = sdio_पढ़ोb(func, IF_SDIO_IOPORT, &ret);
	अगर (ret)
		जाओ disable;

	card->ioport |= sdio_पढ़ोb(func, IF_SDIO_IOPORT + 1, &ret) << 8;
	अगर (ret)
		जाओ disable;

	card->ioport |= sdio_पढ़ोb(func, IF_SDIO_IOPORT + 2, &ret) << 16;
	अगर (ret)
		जाओ disable;

	sdio_release_host(func);
	ret = अगर_sdio_prog_firmware(card);
	अगर (ret) अणु
		sdio_claim_host(func);
		जाओ disable;
	पूर्ण

	वापस 0;

disable:
	sdio_disable_func(func);
release:
	sdio_release_host(func);
	वापस ret;
पूर्ण

अटल पूर्णांक अगर_sdio_घातer_off(काष्ठा अगर_sdio_card *card)
अणु
	काष्ठा sdio_func *func = card->func;
	काष्ठा lbs_निजी *priv = card->priv;

	priv->fw_पढ़ोy = 0;

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);
	वापस 0;
पूर्ण


/*******************************************************************/
/* Libertas callbacks                                              */
/*******************************************************************/

अटल पूर्णांक अगर_sdio_host_to_card(काष्ठा lbs_निजी *priv,
		u8 type, u8 *buf, u16 nb)
अणु
	पूर्णांक ret;
	काष्ठा अगर_sdio_card *card;
	काष्ठा अगर_sdio_packet *packet, *cur;
	u16 size;
	अचिन्हित दीर्घ flags;

	card = priv->card;

	अगर (nb > (65536 - माप(काष्ठा अगर_sdio_packet) - 4)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * The transfer must be in one transaction or the firmware
	 * goes suicidal. There's no way to guarantee that क्रम all
	 * controllers, but we can at least try.
	 */
	size = sdio_align_size(card->func, nb + 4);

	packet = kzalloc(माप(काष्ठा अगर_sdio_packet) + size,
			GFP_ATOMIC);
	अगर (!packet) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	packet->next = शून्य;
	packet->nb = size;

	/*
	 * SDIO specअगरic header.
	 */
	packet->buffer[0] = (nb + 4) & 0xff;
	packet->buffer[1] = ((nb + 4) >> 8) & 0xff;
	packet->buffer[2] = type;
	packet->buffer[3] = 0;

	स_नकल(packet->buffer + 4, buf, nb);

	spin_lock_irqsave(&card->lock, flags);

	अगर (!card->packets)
		card->packets = packet;
	अन्यथा अणु
		cur = card->packets;
		जबतक (cur->next)
			cur = cur->next;
		cur->next = packet;
	पूर्ण

	चयन (type) अणु
	हाल MVMS_CMD:
		priv->dnld_sent = DNLD_CMD_SENT;
		अवरोध;
	हाल MVMS_DAT:
		priv->dnld_sent = DNLD_DATA_SENT;
		अवरोध;
	शेष:
		lbs_deb_sdio("unknown packet type %d\n", (पूर्णांक)type);
	पूर्ण

	spin_unlock_irqrestore(&card->lock, flags);

	queue_work(card->workqueue, &card->packet_worker);

	ret = 0;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक अगर_sdio_enter_deep_sleep(काष्ठा lbs_निजी *priv)
अणु
	पूर्णांक ret;
	काष्ठा cmd_header cmd;

	स_रखो(&cmd, 0, माप(cmd));

	lbs_deb_sdio("send DEEP_SLEEP command\n");
	ret = __lbs_cmd(priv, CMD_802_11_DEEP_SLEEP, &cmd, माप(cmd),
			lbs_cmd_copyback, (अचिन्हित दीर्घ) &cmd);
	अगर (ret)
		netdev_err(priv->dev, "DEEP_SLEEP cmd failed\n");

	mdelay(200);
	वापस ret;
पूर्ण

अटल पूर्णांक अगर_sdio_निकास_deep_sleep(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा अगर_sdio_card *card = priv->card;
	पूर्णांक ret = -1;

	sdio_claim_host(card->func);

	sdio_ग_लिखोb(card->func, HOST_POWER_UP, CONFIGURATION_REG, &ret);
	अगर (ret)
		netdev_err(priv->dev, "sdio_writeb failed!\n");

	sdio_release_host(card->func);

	वापस ret;
पूर्ण

अटल पूर्णांक अगर_sdio_reset_deep_sleep_wakeup(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा अगर_sdio_card *card = priv->card;
	पूर्णांक ret = -1;

	sdio_claim_host(card->func);

	sdio_ग_लिखोb(card->func, 0, CONFIGURATION_REG, &ret);
	अगर (ret)
		netdev_err(priv->dev, "sdio_writeb failed!\n");

	sdio_release_host(card->func);

	वापस ret;

पूर्ण

अटल काष्ठा mmc_host *reset_host;

अटल व्योम अगर_sdio_reset_card_worker(काष्ठा work_काष्ठा *work)
अणु
	/*
	 * The actual reset operation must be run outside of lbs_thपढ़ो. This
	 * is because mmc_हटाओ_host() will cause the device to be instantly
	 * destroyed, and the libertas driver then needs to end lbs_thपढ़ो,
	 * leading to a deadlock.
	 *
	 * We run it in a workqueue totally independent from the अगर_sdio_card
	 * instance क्रम that reason.
	 */

	pr_info("Resetting card...");
	mmc_हटाओ_host(reset_host);
	mmc_add_host(reset_host);
पूर्ण
अटल DECLARE_WORK(card_reset_work, अगर_sdio_reset_card_worker);

अटल व्योम अगर_sdio_reset_card(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा अगर_sdio_card *card = priv->card;

	अगर (work_pending(&card_reset_work))
		वापस;

	reset_host = card->func->card->host;
	schedule_work(&card_reset_work);
पूर्ण

अटल पूर्णांक अगर_sdio_घातer_save(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा अगर_sdio_card *card = priv->card;
	पूर्णांक ret;

	flush_workqueue(card->workqueue);

	ret = अगर_sdio_घातer_off(card);

	/* Let runसमय PM know the card is घातered off */
	pm_runसमय_put_sync(&card->func->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक अगर_sdio_घातer_restore(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा अगर_sdio_card *card = priv->card;
	पूर्णांक r;

	/* Make sure the card will not be घातered off by runसमय PM */
	pm_runसमय_get_sync(&card->func->dev);

	r = अगर_sdio_घातer_on(card);
	अगर (r)
		वापस r;

	रुको_event(card->pwron_रुकोq, priv->fw_पढ़ोy);
	वापस 0;
पूर्ण


/*******************************************************************/
/* SDIO callbacks                                                  */
/*******************************************************************/

अटल व्योम अगर_sdio_पूर्णांकerrupt(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;
	काष्ठा अगर_sdio_card *card;
	u8 cause;

	card = sdio_get_drvdata(func);

	cause = sdio_पढ़ोb(card->func, IF_SDIO_H_INT_STATUS, &ret);
	अगर (ret || !cause)
		वापस;

	lbs_deb_sdio("interrupt: 0x%X\n", (अचिन्हित)cause);

	sdio_ग_लिखोb(card->func, ~cause, IF_SDIO_H_INT_STATUS, &ret);
	अगर (ret)
		वापस;

	/*
	 * Ignore the define name, this really means the card has
	 * successfully received the command.
	 */
	card->priv->is_activity_detected = 1;
	अगर (cause & IF_SDIO_H_INT_DNLD)
		lbs_host_to_card_करोne(card->priv);


	अगर (cause & IF_SDIO_H_INT_UPLD) अणु
		ret = अगर_sdio_card_to_host(card);
		अगर (ret)
			वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक अगर_sdio_probe(काष्ठा sdio_func *func,
		स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा अगर_sdio_card *card;
	काष्ठा lbs_निजी *priv;
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक model;
	काष्ठा अगर_sdio_packet *packet;

	क्रम (i = 0;i < func->card->num_info;i++) अणु
		अगर (माला_पूछो(func->card->info[i],
				"802.11 SDIO ID: %x", &model) == 1)
			अवरोध;
		अगर (माला_पूछो(func->card->info[i],
				"ID: %x", &model) == 1)
			अवरोध;
		अगर (!म_भेद(func->card->info[i], "IBIS Wireless SDIO Card")) अणु
			model = MODEL_8385;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == func->card->num_info) अणु
		pr_err("unable to identify card model\n");
		वापस -ENODEV;
	पूर्ण

	card = kzalloc(माप(काष्ठा अगर_sdio_card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	card->func = func;
	card->model = model;

	चयन (card->model) अणु
	हाल MODEL_8385:
		card->scratch_reg = IF_SDIO_SCRATCH_OLD;
		अवरोध;
	हाल MODEL_8686:
		card->scratch_reg = IF_SDIO_SCRATCH;
		अवरोध;
	हाल MODEL_8688:
	शेष: /* क्रम newer chipsets */
		card->scratch_reg = IF_SDIO_FW_STATUS;
		अवरोध;
	पूर्ण

	spin_lock_init(&card->lock);
	card->workqueue = alloc_workqueue("libertas_sdio", WQ_MEM_RECLAIM, 0);
	अगर (unlikely(!card->workqueue)) अणु
		ret = -ENOMEM;
		जाओ err_queue;
	पूर्ण
	INIT_WORK(&card->packet_worker, अगर_sdio_host_to_card_worker);
	init_रुकोqueue_head(&card->pwron_रुकोq);

	/* Check अगर we support this card */
	क्रम (i = 0; i < ARRAY_SIZE(fw_table); i++) अणु
		अगर (card->model == fw_table[i].model)
			अवरोध;
	पूर्ण
	अगर (i == ARRAY_SIZE(fw_table)) अणु
		pr_err("unknown card model 0x%x\n", card->model);
		ret = -ENODEV;
		जाओ मुक्त;
	पूर्ण

	sdio_set_drvdata(func, card);

	lbs_deb_sdio("class = 0x%X, vendor = 0x%X, "
			"device = 0x%X, model = 0x%X, ioport = 0x%X\n",
			func->class, func->venकरोr, func->device,
			model, (अचिन्हित)card->ioport);


	priv = lbs_add_card(card, &func->dev);
	अगर (IS_ERR(priv)) अणु
		ret = PTR_ERR(priv);
		जाओ मुक्त;
	पूर्ण

	card->priv = priv;

	priv->card = card;
	priv->hw_host_to_card = अगर_sdio_host_to_card;
	priv->enter_deep_sleep = अगर_sdio_enter_deep_sleep;
	priv->निकास_deep_sleep = अगर_sdio_निकास_deep_sleep;
	priv->reset_deep_sleep_wakeup = अगर_sdio_reset_deep_sleep_wakeup;
	priv->reset_card = अगर_sdio_reset_card;
	priv->घातer_save = अगर_sdio_घातer_save;
	priv->घातer_restore = अगर_sdio_घातer_restore;
	priv->is_polling = !(func->card->host->caps & MMC_CAP_SDIO_IRQ);
	ret = अगर_sdio_घातer_on(card);
	अगर (ret)
		जाओ err_activate_card;

out:
	वापस ret;

err_activate_card:
	flush_workqueue(card->workqueue);
	lbs_हटाओ_card(priv);
मुक्त:
	destroy_workqueue(card->workqueue);
err_queue:
	जबतक (card->packets) अणु
		packet = card->packets;
		card->packets = card->packets->next;
		kमुक्त(packet);
	पूर्ण

	kमुक्त(card);

	जाओ out;
पूर्ण

अटल व्योम अगर_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा अगर_sdio_card *card;
	काष्ठा अगर_sdio_packet *packet;

	card = sdio_get_drvdata(func);

	/* Unकरो decrement करोne above in अगर_sdio_probe */
	pm_runसमय_get_noresume(&func->dev);

	अगर (user_rmmod && (card->model == MODEL_8688)) अणु
		/*
		 * FUNC_SHUTDOWN is required क्रम SD8688 WLAN/BT
		 * multiple functions
		 */
		काष्ठा cmd_header cmd;

		स_रखो(&cmd, 0, माप(cmd));

		lbs_deb_sdio("send function SHUTDOWN command\n");
		अगर (__lbs_cmd(card->priv, CMD_FUNC_SHUTDOWN,
				&cmd, माप(cmd), lbs_cmd_copyback,
				(अचिन्हित दीर्घ) &cmd))
			pr_alert("CMD_FUNC_SHUTDOWN cmd failed\n");
	पूर्ण


	lbs_deb_sdio("call remove card\n");
	lbs_stop_card(card->priv);
	lbs_हटाओ_card(card->priv);

	destroy_workqueue(card->workqueue);

	जबतक (card->packets) अणु
		packet = card->packets;
		card->packets = card->packets->next;
		kमुक्त(packet);
	पूर्ण

	kमुक्त(card);
पूर्ण

अटल पूर्णांक अगर_sdio_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा अगर_sdio_card *card = sdio_get_drvdata(func);
	काष्ठा lbs_निजी *priv = card->priv;
	पूर्णांक ret;

	mmc_pm_flag_t flags = sdio_get_host_pm_caps(func);
	priv->घातer_up_on_resume = false;

	/* If we're घातered off anyway, just let the mmc layer हटाओ the
	 * card. */
	अगर (!lbs_अगरace_active(priv)) अणु
		अगर (priv->fw_पढ़ोy) अणु
			priv->घातer_up_on_resume = true;
			अगर_sdio_घातer_off(card);
		पूर्ण

		वापस 0;
	पूर्ण

	dev_info(dev, "%s: suspend: PM flags = 0x%x\n",
		 sdio_func_id(func), flags);

	/* If we aren't being asked to wake on anything, we should bail out
	 * and let the SD stack घातer करोwn the card.
	 */
	अगर (priv->wol_criteria == EHS_REMOVE_WAKEUP) अणु
		dev_info(dev, "Suspend without wake params -- powering down card\n");
		अगर (priv->fw_पढ़ोy) अणु
			ret = lbs_suspend(priv);
			अगर (ret)
				वापस ret;

			priv->घातer_up_on_resume = true;
			अगर_sdio_घातer_off(card);
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (!(flags & MMC_PM_KEEP_POWER)) अणु
		dev_err(dev, "%s: cannot remain alive while host is suspended\n",
			sdio_func_id(func));
		वापस -ENOSYS;
	पूर्ण

	ret = sdio_set_host_pm_flags(func, MMC_PM_KEEP_POWER);
	अगर (ret)
		वापस ret;

	ret = lbs_suspend(priv);
	अगर (ret)
		वापस ret;

	वापस sdio_set_host_pm_flags(func, MMC_PM_WAKE_SDIO_IRQ);
पूर्ण

अटल पूर्णांक अगर_sdio_resume(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा अगर_sdio_card *card = sdio_get_drvdata(func);
	पूर्णांक ret;

	dev_info(dev, "%s: resume: we're back\n", sdio_func_id(func));

	अगर (card->priv->घातer_up_on_resume) अणु
		अगर_sdio_घातer_on(card);
		रुको_event(card->pwron_रुकोq, card->priv->fw_पढ़ोy);
	पूर्ण

	ret = lbs_resume(card->priv);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops अगर_sdio_pm_ops = अणु
	.suspend	= अगर_sdio_suspend,
	.resume		= अगर_sdio_resume,
पूर्ण;

अटल काष्ठा sdio_driver अगर_sdio_driver = अणु
	.name		= "libertas_sdio",
	.id_table	= अगर_sdio_ids,
	.probe		= अगर_sdio_probe,
	.हटाओ		= अगर_sdio_हटाओ,
	.drv = अणु
		.pm = &अगर_sdio_pm_ops,
	पूर्ण,
पूर्ण;

/*******************************************************************/
/* Module functions                                                */
/*******************************************************************/

अटल पूर्णांक __init अगर_sdio_init_module(व्योम)
अणु
	पूर्णांक ret = 0;

	prपूर्णांकk(KERN_INFO "libertas_sdio: Libertas SDIO driver\n");
	prपूर्णांकk(KERN_INFO "libertas_sdio: Copyright Pierre Ossman\n");

	ret = sdio_रेजिस्टर_driver(&अगर_sdio_driver);

	/* Clear the flag in हाल user हटाओs the card. */
	user_rmmod = 0;

	वापस ret;
पूर्ण

अटल व्योम __निकास अगर_sdio_निकास_module(व्योम)
अणु
	/* Set the flag as user is removing this module. */
	user_rmmod = 1;

	cancel_work_sync(&card_reset_work);

	sdio_unरेजिस्टर_driver(&अगर_sdio_driver);
पूर्ण

module_init(अगर_sdio_init_module);
module_निकास(अगर_sdio_निकास_module);

MODULE_DESCRIPTION("Libertas SDIO WLAN Driver");
MODULE_AUTHOR("Pierre Ossman");
MODULE_LICENSE("GPL");
