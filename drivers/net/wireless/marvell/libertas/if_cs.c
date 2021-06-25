<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Driver क्रम the Marvell 8385 based compact flash WLAN cards.

  (C) 2007 by Holger Schurig <hs4233@mail.mn-solutions.de>


*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/firmware.h>
#समावेश <linux/netdevice.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

#समावेश <linux/पन.स>

#घोषणा DRV_NAME "libertas_cs"

#समावेश "decl.h"
#समावेश "defs.h"
#समावेश "dev.h"


/********************************************************************/
/* Module stuff                                                     */
/********************************************************************/

MODULE_AUTHOR("Holger Schurig <hs4233@mail.mn-solutions.de>");
MODULE_DESCRIPTION("Driver for Marvell 83xx compact flash WLAN cards");
MODULE_LICENSE("GPL");



/********************************************************************/
/* Data काष्ठाures                                                  */
/********************************************************************/

काष्ठा अगर_cs_card अणु
	काष्ठा pcmcia_device *p_dev;
	काष्ठा lbs_निजी *priv;
	व्योम __iomem *iobase;
	bool align_regs;
	u32 model;
पूर्ण;


क्रमागत अणु
	MODEL_UNKNOWN = 0x00,
	MODEL_8305 = 0x01,
	MODEL_8381 = 0x02,
	MODEL_8385 = 0x03
पूर्ण;

अटल स्थिर काष्ठा lbs_fw_table fw_table[] = अणु
	अणु MODEL_8305, "libertas/cf8305.bin", शून्य पूर्ण,
	अणु MODEL_8305, "libertas_cs_helper.fw", शून्य पूर्ण,
	अणु MODEL_8381, "libertas/cf8381_helper.bin", "libertas/cf8381.bin" पूर्ण,
	अणु MODEL_8381, "libertas_cs_helper.fw", "libertas_cs.fw" पूर्ण,
	अणु MODEL_8385, "libertas/cf8385_helper.bin", "libertas/cf8385.bin" पूर्ण,
	अणु MODEL_8385, "libertas_cs_helper.fw", "libertas_cs.fw" पूर्ण,
	अणु 0, शून्य, शून्य पूर्ण
पूर्ण;
MODULE_FIRMWARE("libertas/cf8305.bin");
MODULE_FIRMWARE("libertas/cf8381_helper.bin");
MODULE_FIRMWARE("libertas/cf8381.bin");
MODULE_FIRMWARE("libertas/cf8385_helper.bin");
MODULE_FIRMWARE("libertas/cf8385.bin");
MODULE_FIRMWARE("libertas_cs_helper.fw");
MODULE_FIRMWARE("libertas_cs.fw");


/********************************************************************/
/* Hardware access                                                  */
/********************************************************************/

/* This define enables wrapper functions which allow you
   to dump all रेजिस्टर accesses. You normally won't this,
   except क्रम development */
/* #घोषणा DEBUG_IO */

#अगर_घोषित DEBUG_IO
अटल पूर्णांक debug_output = 0;
#अन्यथा
/* This way the compiler optimizes the prपूर्णांकk's away */
#घोषणा debug_output 0
#पूर्ण_अगर

अटल अंतरभूत अचिन्हित पूर्णांक अगर_cs_पढ़ो8(काष्ठा अगर_cs_card *card, uपूर्णांक reg)
अणु
	अचिन्हित पूर्णांक val = ioपढ़ो8(card->iobase + reg);
	अगर (debug_output)
		prपूर्णांकk(KERN_INFO "inb %08x<%02x\n", reg, val);
	वापस val;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक अगर_cs_पढ़ो16(काष्ठा अगर_cs_card *card, uपूर्णांक reg)
अणु
	अचिन्हित पूर्णांक val = ioपढ़ो16(card->iobase + reg);
	अगर (debug_output)
		prपूर्णांकk(KERN_INFO "inw %08x<%04x\n", reg, val);
	वापस val;
पूर्ण
अटल अंतरभूत व्योम अगर_cs_पढ़ो16_rep(
	काष्ठा अगर_cs_card *card,
	uपूर्णांक reg,
	व्योम *buf,
	अचिन्हित दीर्घ count)
अणु
	अगर (debug_output)
		prपूर्णांकk(KERN_INFO "insw %08x<(0x%lx words)\n",
			reg, count);
	ioपढ़ो16_rep(card->iobase + reg, buf, count);
पूर्ण

अटल अंतरभूत व्योम अगर_cs_ग_लिखो8(काष्ठा अगर_cs_card *card, uपूर्णांक reg, u8 val)
अणु
	अगर (debug_output)
		prपूर्णांकk(KERN_INFO "outb %08x>%02x\n", reg, val);
	ioग_लिखो8(val, card->iobase + reg);
पूर्ण

अटल अंतरभूत व्योम अगर_cs_ग_लिखो16(काष्ठा अगर_cs_card *card, uपूर्णांक reg, u16 val)
अणु
	अगर (debug_output)
		prपूर्णांकk(KERN_INFO "outw %08x>%04x\n", reg, val);
	ioग_लिखो16(val, card->iobase + reg);
पूर्ण

अटल अंतरभूत व्योम अगर_cs_ग_लिखो16_rep(
	काष्ठा अगर_cs_card *card,
	uपूर्णांक reg,
	स्थिर व्योम *buf,
	अचिन्हित दीर्घ count)
अणु
	अगर (debug_output)
		prपूर्णांकk(KERN_INFO "outsw %08x>(0x%lx words)\n",
			reg, count);
	ioग_लिखो16_rep(card->iobase + reg, buf, count);
पूर्ण


/*
 * I know that polling/delaying is frowned upon. However, this procedure
 * with polling is needed जबतक करोwnloading the firmware. At this stage,
 * the hardware करोes unक्रमtunately not create any पूर्णांकerrupts.
 *
 * Fortunately, this function is never used once the firmware is in
 * the card. :-)
 *
 * As a reference, see the "Firmware Specification v5.1", page 18
 * and 19. I did not follow their suggested timing to the word,
 * but this works nice & fast anyway.
 */
अटल पूर्णांक अगर_cs_poll_जबतक_fw_करोwnload(काष्ठा अगर_cs_card *card, uपूर्णांक addr, u8 reg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 100000; i++) अणु
		u8 val = अगर_cs_पढ़ो8(card, addr);
		अगर (val == reg)
			वापस 0;
		udelay(5);
	पूर्ण
	वापस -ETIME;
पूर्ण



/*
 * First the biपंचांगasks क्रम the host/card पूर्णांकerrupt/status रेजिस्टरs:
 */
#घोषणा IF_CS_BIT_TX			0x0001
#घोषणा IF_CS_BIT_RX			0x0002
#घोषणा IF_CS_BIT_COMMAND		0x0004
#घोषणा IF_CS_BIT_RESP			0x0008
#घोषणा IF_CS_BIT_EVENT			0x0010
#घोषणा	IF_CS_BIT_MASK			0x001f



/*
 * It's not really clear to me what the host status रेजिस्टर is क्रम. It
 * needs to be set almost in जोड़ with "host int cause". The following
 * bits from above are used:
 *
 *   IF_CS_BIT_TX         driver करोwnloaded a data packet
 *   IF_CS_BIT_RX         driver got a data packet
 *   IF_CS_BIT_COMMAND    driver करोwnloaded a command
 *   IF_CS_BIT_RESP       not used (has some meaning with घातerकरोwn)
 *   IF_CS_BIT_EVENT      driver पढ़ो a host event
 */
#घोषणा IF_CS_HOST_STATUS		0x00000000

/*
 * With the host पूर्णांक cause रेजिस्टर can the host (that is, Linux) cause
 * an पूर्णांकerrupt in the firmware, to tell the firmware about those events:
 *
 *   IF_CS_BIT_TX         a data packet has been करोwnloaded
 *   IF_CS_BIT_RX         a received data packet has retrieved
 *   IF_CS_BIT_COMMAND    a firmware block or a command has been करोwnloaded
 *   IF_CS_BIT_RESP       not used (has some meaning with घातerकरोwn)
 *   IF_CS_BIT_EVENT      a host event (link lost etc) has been retrieved
 */
#घोषणा IF_CS_HOST_INT_CAUSE		0x00000002

/*
 * The host पूर्णांक mask रेजिस्टर is used to enable/disable पूर्णांकerrupt.  However,
 * I have the suspicion that disabled पूर्णांकerrupts are lost.
 */
#घोषणा IF_CS_HOST_INT_MASK		0x00000004

/*
 * Used to send or receive data packets:
 */
#घोषणा IF_CS_WRITE			0x00000016
#घोषणा IF_CS_WRITE_LEN			0x00000014
#घोषणा IF_CS_READ			0x00000010
#घोषणा IF_CS_READ_LEN			0x00000024

/*
 * Used to send commands (and to send firmware block) and to
 * receive command responses:
 */
#घोषणा IF_CS_CMD			0x0000001A
#घोषणा IF_CS_CMD_LEN			0x00000018
#घोषणा IF_CS_RESP			0x00000012
#घोषणा IF_CS_RESP_LEN			0x00000030

/*
 * The card status रेजिस्टरs shows what the card/firmware actually
 * accepts:
 *
 *   IF_CS_BIT_TX        you may send a data packet
 *   IF_CS_BIT_RX        you may retrieve a data packet
 *   IF_CS_BIT_COMMAND   you may send a command
 *   IF_CS_BIT_RESP      you may retrieve a command response
 *   IF_CS_BIT_EVENT     the card has a event क्रम use (link lost, snr low etc)
 *
 * When पढ़ोing this रेजिस्टर several बार, you will get back the same
 * results --- with one exception: the IF_CS_BIT_EVENT clear itself
 * स्वतःmatically.
 *
 * Not that we करोn't rely on BIT_RX,_BIT_RESP or BIT_EVENT because
 * we handle this via the card पूर्णांक cause रेजिस्टर.
 */
#घोषणा IF_CS_CARD_STATUS		0x00000020
#घोषणा IF_CS_CARD_STATUS_MASK		0x7f00

/*
 * The card पूर्णांक cause रेजिस्टर is used by the card/firmware to notअगरy us
 * about the following events:
 *
 *   IF_CS_BIT_TX        a data packet has successfully been sentx
 *   IF_CS_BIT_RX        a data packet has been received and can be retrieved
 *   IF_CS_BIT_COMMAND   not used
 *   IF_CS_BIT_RESP      the firmware has a command response क्रम us
 *   IF_CS_BIT_EVENT     the card has a event क्रम use (link lost, snr low etc)
 */
#घोषणा IF_CS_CARD_INT_CAUSE		0x00000022

/*
 * This is used to क्रम handshaking with the card's bootloader/helper image
 * to synchronize करोwnloading of firmware blocks.
 */
#घोषणा IF_CS_SQ_READ_LOW		0x00000028
#घोषणा IF_CS_SQ_HELPER_OK		0x10

/*
 * The scratch रेजिस्टर tells us ...
 *
 * IF_CS_SCRATCH_BOOT_OK     the bootloader runs
 * IF_CS_SCRATCH_HELPER_OK   the helper firmware alपढ़ोy runs
 */
#घोषणा IF_CS_SCRATCH			0x0000003F
#घोषणा IF_CS_SCRATCH_BOOT_OK		0x00
#घोषणा IF_CS_SCRATCH_HELPER_OK		0x5a

/*
 * Used to detect ancient chips:
 */
#घोषणा IF_CS_PRODUCT_ID		0x0000001C
#घोषणा IF_CS_CF8385_B1_REV		0x12
#घोषणा IF_CS_CF8381_B3_REV		0x04
#घोषणा IF_CS_CF8305_B1_REV		0x03

/*
 * Used to detect other cards than CF8385 since their revisions of silicon
 * करोesn't match those from CF8385, eg. CF8381 B3 works with this driver.
 */
#घोषणा CF8305_MANFID		0x02db
#घोषणा CF8305_CARDID		0x8103
#घोषणा CF8381_MANFID		0x02db
#घोषणा CF8381_CARDID		0x6064
#घोषणा CF8385_MANFID		0x02df
#घोषणा CF8385_CARDID		0x8103

/*
 * FIXME: just use the 'driver_info' field of 'struct pcmcia_device_id' when
 * that माला_लो fixed.  Currently there's no way to access it from the probe hook.
 */
अटल अंतरभूत u32 get_model(u16 manf_id, u16 card_id)
अणु
	/* NOTE: keep in sync with अगर_cs_ids */
	अगर (manf_id == CF8305_MANFID && card_id == CF8305_CARDID)
		वापस MODEL_8305;
	अन्यथा अगर (manf_id == CF8381_MANFID && card_id == CF8381_CARDID)
		वापस MODEL_8381;
	अन्यथा अगर (manf_id == CF8385_MANFID && card_id == CF8385_CARDID)
		वापस MODEL_8385;
	वापस MODEL_UNKNOWN;
पूर्ण

/********************************************************************/
/* I/O and पूर्णांकerrupt handling                                       */
/********************************************************************/

अटल अंतरभूत व्योम अगर_cs_enable_पूर्णांकs(काष्ठा अगर_cs_card *card)
अणु
	अगर_cs_ग_लिखो16(card, IF_CS_HOST_INT_MASK, 0);
पूर्ण

अटल अंतरभूत व्योम अगर_cs_disable_पूर्णांकs(काष्ठा अगर_cs_card *card)
अणु
	अगर_cs_ग_लिखो16(card, IF_CS_HOST_INT_MASK, IF_CS_BIT_MASK);
पूर्ण

/*
 * Called from अगर_cs_host_to_card to send a command to the hardware
 */
अटल पूर्णांक अगर_cs_send_cmd(काष्ठा lbs_निजी *priv, u8 *buf, u16 nb)
अणु
	काष्ठा अगर_cs_card *card = (काष्ठा अगर_cs_card *)priv->card;
	पूर्णांक ret = -1;
	पूर्णांक loops = 0;

	अगर_cs_disable_पूर्णांकs(card);

	/* Is hardware पढ़ोy? */
	जबतक (1) अणु
		u16 status = अगर_cs_पढ़ो16(card, IF_CS_CARD_STATUS);
		अगर (status & IF_CS_BIT_COMMAND)
			अवरोध;
		अगर (++loops > 100) अणु
			netdev_err(priv->dev, "card not ready for commands\n");
			जाओ करोne;
		पूर्ण
		mdelay(1);
	पूर्ण

	अगर_cs_ग_लिखो16(card, IF_CS_CMD_LEN, nb);

	अगर_cs_ग_लिखो16_rep(card, IF_CS_CMD, buf, nb / 2);
	/* Are we supposed to transfer an odd amount of bytes? */
	अगर (nb & 1)
		अगर_cs_ग_लिखो8(card, IF_CS_CMD, buf[nb-1]);

	/* "Assert the करोwnload over पूर्णांकerrupt command in the Host
	 * status रेजिस्टर" */
	अगर_cs_ग_लिखो16(card, IF_CS_HOST_STATUS, IF_CS_BIT_COMMAND);

	/* "Assert the करोwnload over पूर्णांकerrupt command in the Card
	 * पूर्णांकerrupt हाल रेजिस्टर" */
	अगर_cs_ग_लिखो16(card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_COMMAND);
	ret = 0;

करोne:
	अगर_cs_enable_पूर्णांकs(card);
	वापस ret;
पूर्ण

/*
 * Called from अगर_cs_host_to_card to send a data to the hardware
 */
अटल व्योम अगर_cs_send_data(काष्ठा lbs_निजी *priv, u8 *buf, u16 nb)
अणु
	काष्ठा अगर_cs_card *card = (काष्ठा अगर_cs_card *)priv->card;
	u16 status;

	अगर_cs_disable_पूर्णांकs(card);

	status = अगर_cs_पढ़ो16(card, IF_CS_CARD_STATUS);
	BUG_ON((status & IF_CS_BIT_TX) == 0);

	अगर_cs_ग_लिखो16(card, IF_CS_WRITE_LEN, nb);

	/* ग_लिखो even number of bytes, then odd byte अगर necessary */
	अगर_cs_ग_लिखो16_rep(card, IF_CS_WRITE, buf, nb / 2);
	अगर (nb & 1)
		अगर_cs_ग_लिखो8(card, IF_CS_WRITE, buf[nb-1]);

	अगर_cs_ग_लिखो16(card, IF_CS_HOST_STATUS, IF_CS_BIT_TX);
	अगर_cs_ग_लिखो16(card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_TX);
	अगर_cs_enable_पूर्णांकs(card);
पूर्ण

/*
 * Get the command result out of the card.
 */
अटल पूर्णांक अगर_cs_receive_cmdres(काष्ठा lbs_निजी *priv, u8 *data, u32 *len)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -1;
	u16 status;

	/* is hardware पढ़ोy? */
	status = अगर_cs_पढ़ो16(priv->card, IF_CS_CARD_STATUS);
	अगर ((status & IF_CS_BIT_RESP) == 0) अणु
		netdev_err(priv->dev, "no cmd response in card\n");
		*len = 0;
		जाओ out;
	पूर्ण

	*len = अगर_cs_पढ़ो16(priv->card, IF_CS_RESP_LEN);
	अगर ((*len == 0) || (*len > LBS_CMD_BUFFER_SIZE)) अणु
		netdev_err(priv->dev,
			   "card cmd buffer has invalid # of bytes (%d)\n",
			   *len);
		जाओ out;
	पूर्ण

	/* पढ़ो even number of bytes, then odd byte अगर necessary */
	अगर_cs_पढ़ो16_rep(priv->card, IF_CS_RESP, data, *len/माप(u16));
	अगर (*len & 1)
		data[*len-1] = अगर_cs_पढ़ो8(priv->card, IF_CS_RESP);

	/* This is a workaround क्रम a firmware that reports too much
	 * bytes */
	*len -= 8;
	ret = 0;

	/* Clear this flag again */
	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->dnld_sent = DNLD_RES_RECEIVED;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

out:
	वापस ret;
पूर्ण

अटल काष्ठा sk_buff *अगर_cs_receive_data(काष्ठा lbs_निजी *priv)
अणु
	काष्ठा sk_buff *skb = शून्य;
	u16 len;
	u8 *data;

	len = अगर_cs_पढ़ो16(priv->card, IF_CS_READ_LEN);
	अगर (len == 0 || len > MRVDRV_ETH_RX_PACKET_BUFFER_SIZE) अणु
		netdev_err(priv->dev,
			   "card data buffer has invalid # of bytes (%d)\n",
			   len);
		priv->dev->stats.rx_dropped++;
		जाओ dat_err;
	पूर्ण

	skb = dev_alloc_skb(MRVDRV_ETH_RX_PACKET_BUFFER_SIZE + 2);
	अगर (!skb)
		जाओ out;
	skb_put(skb, len);
	skb_reserve(skb, 2);/* 16 byte align */
	data = skb->data;

	/* पढ़ो even number of bytes, then odd byte अगर necessary */
	अगर_cs_पढ़ो16_rep(priv->card, IF_CS_READ, data, len/माप(u16));
	अगर (len & 1)
		data[len-1] = अगर_cs_पढ़ो8(priv->card, IF_CS_READ);

dat_err:
	अगर_cs_ग_लिखो16(priv->card, IF_CS_HOST_STATUS, IF_CS_BIT_RX);
	अगर_cs_ग_लिखो16(priv->card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_RX);

out:
	वापस skb;
पूर्ण

अटल irqवापस_t अगर_cs_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा अगर_cs_card *card = data;
	काष्ठा lbs_निजी *priv = card->priv;
	u16 cause;

	/* Ask card पूर्णांकerrupt cause रेजिस्टर अगर there is something क्रम us */
	cause = अगर_cs_पढ़ो16(card, IF_CS_CARD_INT_CAUSE);
	lbs_deb_cs("cause 0x%04x\n", cause);

	अगर (cause == 0) अणु
		/* Not क्रम us */
		वापस IRQ_NONE;
	पूर्ण

	अगर (cause == 0xffff) अणु
		/* Read in junk, the card has probably been हटाओd */
		card->priv->surpriseहटाओd = 1;
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (cause & IF_CS_BIT_RX) अणु
		काष्ठा sk_buff *skb;
		lbs_deb_cs("rx packet\n");
		skb = अगर_cs_receive_data(priv);
		अगर (skb)
			lbs_process_rxed_packet(priv, skb);
	पूर्ण

	अगर (cause & IF_CS_BIT_TX) अणु
		lbs_deb_cs("tx done\n");
		lbs_host_to_card_करोne(priv);
	पूर्ण

	अगर (cause & IF_CS_BIT_RESP) अणु
		अचिन्हित दीर्घ flags;
		u8 i;

		lbs_deb_cs("cmd resp\n");
		spin_lock_irqsave(&priv->driver_lock, flags);
		i = (priv->resp_idx == 0) ? 1 : 0;
		spin_unlock_irqrestore(&priv->driver_lock, flags);

		BUG_ON(priv->resp_len[i]);
		अगर_cs_receive_cmdres(priv, priv->resp_buf[i],
			&priv->resp_len[i]);

		spin_lock_irqsave(&priv->driver_lock, flags);
		lbs_notअगरy_command_response(priv, i);
		spin_unlock_irqrestore(&priv->driver_lock, flags);
	पूर्ण

	अगर (cause & IF_CS_BIT_EVENT) अणु
		u16 status = अगर_cs_पढ़ो16(priv->card, IF_CS_CARD_STATUS);
		अगर_cs_ग_लिखो16(priv->card, IF_CS_HOST_INT_CAUSE,
			IF_CS_BIT_EVENT);
		lbs_queue_event(priv, (status & IF_CS_CARD_STATUS_MASK) >> 8);
	पूर्ण

	/* Clear पूर्णांकerrupt cause */
	अगर_cs_ग_लिखो16(card, IF_CS_CARD_INT_CAUSE, cause & IF_CS_BIT_MASK);

	वापस IRQ_HANDLED;
पूर्ण




/********************************************************************/
/* Firmware                                                         */
/********************************************************************/

/*
 * Tries to program the helper firmware.
 *
 * Return 0 on success
 */
अटल पूर्णांक अगर_cs_prog_helper(काष्ठा अगर_cs_card *card, स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक ret = 0;
	पूर्णांक sent = 0;
	u8  scratch;

	/*
	 * This is the only place where an unaligned रेजिस्टर access happens on
	 * the CF8305 card, thereक्रमe क्रम the sake of speed of the driver, we करो
	 * the alignment correction here.
	 */
	अगर (card->align_regs)
		scratch = अगर_cs_पढ़ो16(card, IF_CS_SCRATCH) >> 8;
	अन्यथा
		scratch = अगर_cs_पढ़ो8(card, IF_CS_SCRATCH);

	/* "If the value is 0x5a, the firmware is alपढ़ोy
	 * करोwnloaded successfully"
	 */
	अगर (scratch == IF_CS_SCRATCH_HELPER_OK)
		जाओ करोne;

	/* "If the value is != 00, it is invalid value of रेजिस्टर */
	अगर (scratch != IF_CS_SCRATCH_BOOT_OK) अणु
		ret = -ENODEV;
		जाओ करोne;
	पूर्ण

	lbs_deb_cs("helper size %td\n", fw->size);

	/* "Set the 5 bytes of the helper image to 0" */
	/* Not needed, this contains an ARM branch inकाष्ठाion */

	क्रम (;;) अणु
		/* "the number of bytes to send is 256" */
		पूर्णांक count = 256;
		पूर्णांक reमुख्य = fw->size - sent;

		अगर (reमुख्य < count)
			count = reमुख्य;

		/*
		 * "ग_लिखो the number of bytes to be sent to the I/O Command
		 * ग_लिखो length रेजिस्टर"
		 */
		अगर_cs_ग_लिखो16(card, IF_CS_CMD_LEN, count);

		/* "ग_लिखो this to I/O Command port रेजिस्टर as 16 bit ग_लिखोs */
		अगर (count)
			अगर_cs_ग_लिखो16_rep(card, IF_CS_CMD,
				&fw->data[sent],
				count >> 1);

		/*
		 * "Assert the करोwnload over पूर्णांकerrupt command in the Host
		 * status रेजिस्टर"
		 */
		अगर_cs_ग_लिखो8(card, IF_CS_HOST_STATUS, IF_CS_BIT_COMMAND);

		/*
		 * "Assert the करोwnload over पूर्णांकerrupt command in the Card
		 * पूर्णांकerrupt हाल रेजिस्टर"
		 */
		अगर_cs_ग_लिखो16(card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_COMMAND);

		/*
		 * "The host polls the Card Status रेजिस्टर ... क्रम 50 ms beक्रमe
		 * declaring a failure"
		 */
		ret = अगर_cs_poll_जबतक_fw_करोwnload(card, IF_CS_CARD_STATUS,
			IF_CS_BIT_COMMAND);
		अगर (ret < 0) अणु
			pr_err("can't download helper at 0x%x, ret %d\n",
			       sent, ret);
			जाओ करोne;
		पूर्ण

		अगर (count == 0)
			अवरोध;

		sent += count;
	पूर्ण

करोne:
	वापस ret;
पूर्ण


अटल पूर्णांक अगर_cs_prog_real(काष्ठा अगर_cs_card *card, स्थिर काष्ठा firmware *fw)
अणु
	पूर्णांक ret = 0;
	पूर्णांक retry = 0;
	पूर्णांक len = 0;
	पूर्णांक sent;

	lbs_deb_cs("fw size %td\n", fw->size);

	ret = अगर_cs_poll_जबतक_fw_करोwnload(card, IF_CS_SQ_READ_LOW,
		IF_CS_SQ_HELPER_OK);
	अगर (ret < 0) अणु
		pr_err("helper firmware doesn't answer\n");
		जाओ करोne;
	पूर्ण

	क्रम (sent = 0; sent < fw->size; sent += len) अणु
		len = अगर_cs_पढ़ो16(card, IF_CS_SQ_READ_LOW);
		अगर (len & 1) अणु
			retry++;
			pr_info("odd, need to retry this firmware block\n");
		पूर्ण अन्यथा अणु
			retry = 0;
		पूर्ण

		अगर (retry > 20) अणु
			pr_err("could not download firmware\n");
			ret = -ENODEV;
			जाओ करोne;
		पूर्ण
		अगर (retry) अणु
			sent -= len;
		पूर्ण


		अगर_cs_ग_लिखो16(card, IF_CS_CMD_LEN, len);

		अगर_cs_ग_लिखो16_rep(card, IF_CS_CMD,
			&fw->data[sent],
			(len+1) >> 1);
		अगर_cs_ग_लिखो8(card, IF_CS_HOST_STATUS, IF_CS_BIT_COMMAND);
		अगर_cs_ग_लिखो16(card, IF_CS_HOST_INT_CAUSE, IF_CS_BIT_COMMAND);

		ret = अगर_cs_poll_जबतक_fw_करोwnload(card, IF_CS_CARD_STATUS,
			IF_CS_BIT_COMMAND);
		अगर (ret < 0) अणु
			pr_err("can't download firmware at 0x%x\n", sent);
			जाओ करोne;
		पूर्ण
	पूर्ण

	ret = अगर_cs_poll_जबतक_fw_करोwnload(card, IF_CS_SCRATCH, 0x5a);
	अगर (ret < 0)
		pr_err("firmware download failed\n");

करोne:
	वापस ret;
पूर्ण

अटल व्योम अगर_cs_prog_firmware(काष्ठा lbs_निजी *priv, पूर्णांक ret,
				 स्थिर काष्ठा firmware *helper,
				 स्थिर काष्ठा firmware *मुख्यfw)
अणु
	काष्ठा अगर_cs_card *card = priv->card;

	अगर (ret) अणु
		pr_err("failed to find firmware (%d)\n", ret);
		वापस;
	पूर्ण

	/* Load the firmware */
	ret = अगर_cs_prog_helper(card, helper);
	अगर (ret == 0 && (card->model != MODEL_8305))
		ret = अगर_cs_prog_real(card, मुख्यfw);
	अगर (ret)
		वापस;

	/* Now actually get the IRQ */
	ret = request_irq(card->p_dev->irq, अगर_cs_पूर्णांकerrupt,
		IRQF_SHARED, DRV_NAME, card);
	अगर (ret) अणु
		pr_err("error in request_irq\n");
		वापस;
	पूर्ण

	/*
	 * Clear any पूर्णांकerrupt cause that happened जबतक sending
	 * firmware/initializing card
	 */
	अगर_cs_ग_लिखो16(card, IF_CS_CARD_INT_CAUSE, IF_CS_BIT_MASK);
	अगर_cs_enable_पूर्णांकs(card);

	/* And finally bring the card up */
	priv->fw_पढ़ोy = 1;
	अगर (lbs_start_card(priv) != 0) अणु
		pr_err("could not activate card\n");
		मुक्त_irq(card->p_dev->irq, card);
	पूर्ण
पूर्ण


/********************************************************************/
/* Callback functions क्रम libertas.ko                               */
/********************************************************************/

/* Send commands or data packets to the card */
अटल पूर्णांक अगर_cs_host_to_card(काष्ठा lbs_निजी *priv,
	u8 type,
	u8 *buf,
	u16 nb)
अणु
	पूर्णांक ret = -1;

	चयन (type) अणु
	हाल MVMS_DAT:
		priv->dnld_sent = DNLD_DATA_SENT;
		अगर_cs_send_data(priv, buf, nb);
		ret = 0;
		अवरोध;
	हाल MVMS_CMD:
		priv->dnld_sent = DNLD_CMD_SENT;
		ret = अगर_cs_send_cmd(priv, buf, nb);
		अवरोध;
	शेष:
		netdev_err(priv->dev, "%s: unsupported type %d\n",
			   __func__, type);
	पूर्ण

	वापस ret;
पूर्ण


अटल व्योम अगर_cs_release(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा अगर_cs_card *card = p_dev->priv;

	मुक्त_irq(p_dev->irq, card);
	pcmcia_disable_device(p_dev);
	अगर (card->iobase)
		ioport_unmap(card->iobase);
पूर्ण


अटल पूर्णांक अगर_cs_ioprobe(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;

	अगर (p_dev->resource[1]->end) अणु
		pr_err("wrong CIS (check number of IO windows)\n");
		वापस -ENODEV;
	पूर्ण

	/* This reserves IO space but करोesn't actually enable it */
	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक अगर_cs_probe(काष्ठा pcmcia_device *p_dev)
अणु
	पूर्णांक ret = -ENOMEM;
	अचिन्हित पूर्णांक prod_id;
	काष्ठा lbs_निजी *priv;
	काष्ठा अगर_cs_card *card;

	card = kzalloc(माप(काष्ठा अगर_cs_card), GFP_KERNEL);
	अगर (!card)
		जाओ out;

	card->p_dev = p_dev;
	p_dev->priv = card;

	p_dev->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	अगर (pcmcia_loop_config(p_dev, अगर_cs_ioprobe, शून्य)) अणु
		pr_err("error in pcmcia_loop_config\n");
		जाओ out1;
	पूर्ण

	/*
	 * Allocate an पूर्णांकerrupt line.  Note that this करोes not assign
	 * a handler to the पूर्णांकerrupt, unless the 'Handler' member of
	 * the irq काष्ठाure is initialized.
	 */
	अगर (!p_dev->irq)
		जाओ out1;

	/* Initialize io access */
	card->iobase = ioport_map(p_dev->resource[0]->start,
				resource_size(p_dev->resource[0]));
	अगर (!card->iobase) अणु
		pr_err("error in ioport_map\n");
		ret = -EIO;
		जाओ out1;
	पूर्ण

	ret = pcmcia_enable_device(p_dev);
	अगर (ret) अणु
		pr_err("error in pcmcia_enable_device\n");
		जाओ out2;
	पूर्ण

	/* Finally, report what we've करोne */
	lbs_deb_cs("irq %d, io %pR", p_dev->irq, p_dev->resource[0]);

	/*
	 * Most of the libertas cards can करो unaligned रेजिस्टर access, but some
	 * weird ones cannot. That's especially true क्रम the CF8305 card.
	 */
	card->align_regs = false;

	card->model = get_model(p_dev->manf_id, p_dev->card_id);
	अगर (card->model == MODEL_UNKNOWN) अणु
		pr_err("unsupported manf_id 0x%04x / card_id 0x%04x\n",
		       p_dev->manf_id, p_dev->card_id);
		ret = -ENODEV;
		जाओ out2;
	पूर्ण

	/* Check अगर we have a current silicon */
	prod_id = अगर_cs_पढ़ो8(card, IF_CS_PRODUCT_ID);
	अगर (card->model == MODEL_8305) अणु
		card->align_regs = true;
		अगर (prod_id < IF_CS_CF8305_B1_REV) अणु
			pr_err("8305 rev B0 and older are not supported\n");
			ret = -ENODEV;
			जाओ out2;
		पूर्ण
	पूर्ण

	अगर ((card->model == MODEL_8381) && prod_id < IF_CS_CF8381_B3_REV) अणु
		pr_err("8381 rev B2 and older are not supported\n");
		ret = -ENODEV;
		जाओ out2;
	पूर्ण

	अगर ((card->model == MODEL_8385) && prod_id < IF_CS_CF8385_B1_REV) अणु
		pr_err("8385 rev B0 and older are not supported\n");
		ret = -ENODEV;
		जाओ out2;
	पूर्ण

	/* Make this card known to the libertas driver */
	priv = lbs_add_card(card, &p_dev->dev);
	अगर (IS_ERR(priv)) अणु
		ret = PTR_ERR(priv);
		जाओ out2;
	पूर्ण

	/* Set up fields in lbs_निजी */
	card->priv = priv;
	priv->card = card;
	priv->hw_host_to_card = अगर_cs_host_to_card;
	priv->enter_deep_sleep = शून्य;
	priv->निकास_deep_sleep = शून्य;
	priv->reset_deep_sleep_wakeup = शून्य;

	/* Get firmware */
	ret = lbs_get_firmware_async(priv, &p_dev->dev, card->model, fw_table,
				     अगर_cs_prog_firmware);
	अगर (ret) अणु
		pr_err("failed to find firmware (%d)\n", ret);
		जाओ out3;
	पूर्ण

	जाओ out;

out3:
	lbs_हटाओ_card(priv);
out2:
	ioport_unmap(card->iobase);
out1:
	pcmcia_disable_device(p_dev);
out:
	वापस ret;
पूर्ण


अटल व्योम अगर_cs_detach(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा अगर_cs_card *card = p_dev->priv;

	lbs_stop_card(card->priv);
	lbs_हटाओ_card(card->priv);
	अगर_cs_disable_पूर्णांकs(card);
	अगर_cs_release(p_dev);
	kमुक्त(card);
पूर्ण



/********************************************************************/
/* Module initialization                                            */
/********************************************************************/

अटल स्थिर काष्ठा pcmcia_device_id अगर_cs_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(CF8305_MANFID, CF8305_CARDID),
	PCMCIA_DEVICE_MANF_CARD(CF8381_MANFID, CF8381_CARDID),
	PCMCIA_DEVICE_MANF_CARD(CF8385_MANFID, CF8385_CARDID),
	/* NOTE: keep in sync with get_model() */
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, अगर_cs_ids);

अटल काष्ठा pcmcia_driver lbs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= DRV_NAME,
	.probe		= अगर_cs_probe,
	.हटाओ		= अगर_cs_detach,
	.id_table       = अगर_cs_ids,
पूर्ण;
module_pcmcia_driver(lbs_driver);
