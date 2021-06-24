<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *****************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <linux/skbuff.h>
#समावेश <net/mac80211.h>

#समावेश "common.h"

पूर्णांक
_il_poll_bit(काष्ठा il_priv *il, u32 addr, u32 bits, u32 mask, पूर्णांक समयout)
अणु
	स्थिर पूर्णांक पूर्णांकerval = 10; /* microseconds */
	पूर्णांक t = 0;

	करो अणु
		अगर ((_il_rd(il, addr) & mask) == (bits & mask))
			वापस t;
		udelay(पूर्णांकerval);
		t += पूर्णांकerval;
	पूर्ण जबतक (t < समयout);

	वापस -ETIMEDOUT;
पूर्ण
EXPORT_SYMBOL(_il_poll_bit);

व्योम
il_set_bit(काष्ठा il_priv *p, u32 r, u32 m)
अणु
	अचिन्हित दीर्घ reg_flags;

	spin_lock_irqsave(&p->reg_lock, reg_flags);
	_il_set_bit(p, r, m);
	spin_unlock_irqrestore(&p->reg_lock, reg_flags);
पूर्ण
EXPORT_SYMBOL(il_set_bit);

व्योम
il_clear_bit(काष्ठा il_priv *p, u32 r, u32 m)
अणु
	अचिन्हित दीर्घ reg_flags;

	spin_lock_irqsave(&p->reg_lock, reg_flags);
	_il_clear_bit(p, r, m);
	spin_unlock_irqrestore(&p->reg_lock, reg_flags);
पूर्ण
EXPORT_SYMBOL(il_clear_bit);

bool
_il_grab_nic_access(काष्ठा il_priv *il)
अणु
	पूर्णांक ret;
	u32 val;

	/* this bit wakes up the NIC */
	_il_set_bit(il, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);

	/*
	 * These bits say the device is running, and should keep running क्रम
	 * at least a लघु जबतक (at least as दीर्घ as MAC_ACCESS_REQ stays 1),
	 * but they करो not indicate that embedded SRAM is restored yet;
	 * 3945 and 4965 have अस्थिर SRAM, and must save/restore contents
	 * to/from host DRAM when sleeping/waking क्रम घातer-saving.
	 * Each direction takes approximately 1/4 millisecond; with this
	 * overhead, it's a good idea to grab and hold MAC_ACCESS_REQUEST अगर a
	 * series of रेजिस्टर accesses are expected (e.g. पढ़ोing Event Log),
	 * to keep device from sleeping.
	 *
	 * CSR_UCODE_DRV_GP1 रेजिस्टर bit MAC_SLEEP == 0 indicates that
	 * SRAM is okay/restored.  We करोn't check that here because this call
	 * is just क्रम hardware रेजिस्टर access; but GP1 MAC_SLEEP check is a
	 * good idea beक्रमe accessing 3945/4965 SRAM (e.g. पढ़ोing Event Log).
	 *
	 */
	ret =
	    _il_poll_bit(il, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_VAL_MAC_ACCESS_EN,
			 (CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY |
			  CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP), 15000);
	अगर (unlikely(ret < 0)) अणु
		val = _il_rd(il, CSR_GP_CNTRL);
		WARN_ONCE(1, "Timeout waiting for ucode processor access "
			     "(CSR_GP_CNTRL 0x%08x)\n", val);
		_il_wr(il, CSR_RESET, CSR_RESET_REG_FLAG_FORCE_NMI);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(_il_grab_nic_access);

पूर्णांक
il_poll_bit(काष्ठा il_priv *il, u32 addr, u32 mask, पूर्णांक समयout)
अणु
	स्थिर पूर्णांक पूर्णांकerval = 10; /* microseconds */
	पूर्णांक t = 0;

	करो अणु
		अगर ((il_rd(il, addr) & mask) == mask)
			वापस t;
		udelay(पूर्णांकerval);
		t += पूर्णांकerval;
	पूर्ण जबतक (t < समयout);

	वापस -ETIMEDOUT;
पूर्ण
EXPORT_SYMBOL(il_poll_bit);

u32
il_rd_prph(काष्ठा il_priv *il, u32 reg)
अणु
	अचिन्हित दीर्घ reg_flags;
	u32 val;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	_il_grab_nic_access(il);
	val = _il_rd_prph(il, reg);
	_il_release_nic_access(il);
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
	वापस val;
पूर्ण
EXPORT_SYMBOL(il_rd_prph);

व्योम
il_wr_prph(काष्ठा il_priv *il, u32 addr, u32 val)
अणु
	अचिन्हित दीर्घ reg_flags;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	अगर (likely(_il_grab_nic_access(il))) अणु
		_il_wr_prph(il, addr, val);
		_il_release_nic_access(il);
	पूर्ण
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
पूर्ण
EXPORT_SYMBOL(il_wr_prph);

u32
il_पढ़ो_targ_mem(काष्ठा il_priv *il, u32 addr)
अणु
	अचिन्हित दीर्घ reg_flags;
	u32 value;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	_il_grab_nic_access(il);

	_il_wr(il, HBUS_TARG_MEM_RADDR, addr);
	value = _il_rd(il, HBUS_TARG_MEM_RDAT);

	_il_release_nic_access(il);
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
	वापस value;
पूर्ण
EXPORT_SYMBOL(il_पढ़ो_targ_mem);

व्योम
il_ग_लिखो_targ_mem(काष्ठा il_priv *il, u32 addr, u32 val)
अणु
	अचिन्हित दीर्घ reg_flags;

	spin_lock_irqsave(&il->reg_lock, reg_flags);
	अगर (likely(_il_grab_nic_access(il))) अणु
		_il_wr(il, HBUS_TARG_MEM_WADDR, addr);
		_il_wr(il, HBUS_TARG_MEM_WDAT, val);
		_il_release_nic_access(il);
	पूर्ण
	spin_unlock_irqrestore(&il->reg_lock, reg_flags);
पूर्ण
EXPORT_SYMBOL(il_ग_लिखो_targ_mem);

स्थिर अक्षर *
il_get_cmd_string(u8 cmd)
अणु
	चयन (cmd) अणु
		IL_CMD(N_ALIVE);
		IL_CMD(N_ERROR);
		IL_CMD(C_RXON);
		IL_CMD(C_RXON_ASSOC);
		IL_CMD(C_QOS_PARAM);
		IL_CMD(C_RXON_TIMING);
		IL_CMD(C_ADD_STA);
		IL_CMD(C_REM_STA);
		IL_CMD(C_WEPKEY);
		IL_CMD(N_3945_RX);
		IL_CMD(C_TX);
		IL_CMD(C_RATE_SCALE);
		IL_CMD(C_LEDS);
		IL_CMD(C_TX_LINK_QUALITY_CMD);
		IL_CMD(C_CHANNEL_SWITCH);
		IL_CMD(N_CHANNEL_SWITCH);
		IL_CMD(C_SPECTRUM_MEASUREMENT);
		IL_CMD(N_SPECTRUM_MEASUREMENT);
		IL_CMD(C_POWER_TBL);
		IL_CMD(N_PM_SLEEP);
		IL_CMD(N_PM_DEBUG_STATS);
		IL_CMD(C_SCAN);
		IL_CMD(C_SCAN_ABORT);
		IL_CMD(N_SCAN_START);
		IL_CMD(N_SCAN_RESULTS);
		IL_CMD(N_SCAN_COMPLETE);
		IL_CMD(N_BEACON);
		IL_CMD(C_TX_BEACON);
		IL_CMD(C_TX_PWR_TBL);
		IL_CMD(C_BT_CONFIG);
		IL_CMD(C_STATS);
		IL_CMD(N_STATS);
		IL_CMD(N_CARD_STATE);
		IL_CMD(N_MISSED_BEACONS);
		IL_CMD(C_CT_KILL_CONFIG);
		IL_CMD(C_SENSITIVITY);
		IL_CMD(C_PHY_CALIBRATION);
		IL_CMD(N_RX_PHY);
		IL_CMD(N_RX_MPDU);
		IL_CMD(N_RX);
		IL_CMD(N_COMPRESSED_BA);
	शेष:
		वापस "UNKNOWN";

	पूर्ण
पूर्ण
EXPORT_SYMBOL(il_get_cmd_string);

#घोषणा HOST_COMPLETE_TIMEOUT (HZ / 2)

अटल व्योम
il_generic_cmd_callback(काष्ठा il_priv *il, काष्ठा il_device_cmd *cmd,
			काष्ठा il_rx_pkt *pkt)
अणु
	अगर (pkt->hdr.flags & IL_CMD_FAILED_MSK) अणु
		IL_ERR("Bad return from %s (0x%08X)\n",
		       il_get_cmd_string(cmd->hdr.cmd), pkt->hdr.flags);
		वापस;
	पूर्ण
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	चयन (cmd->hdr.cmd) अणु
	हाल C_TX_LINK_QUALITY_CMD:
	हाल C_SENSITIVITY:
		D_HC_DUMP("back from %s (0x%08X)\n",
			  il_get_cmd_string(cmd->hdr.cmd), pkt->hdr.flags);
		अवरोध;
	शेष:
		D_HC("back from %s (0x%08X)\n", il_get_cmd_string(cmd->hdr.cmd),
		     pkt->hdr.flags);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
il_send_cmd_async(काष्ठा il_priv *il, काष्ठा il_host_cmd *cmd)
अणु
	पूर्णांक ret;

	BUG_ON(!(cmd->flags & CMD_ASYNC));

	/* An asynchronous command can not expect an SKB to be set. */
	BUG_ON(cmd->flags & CMD_WANT_SKB);

	/* Assign a generic callback अगर one is not provided */
	अगर (!cmd->callback)
		cmd->callback = il_generic_cmd_callback;

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस -EBUSY;

	ret = il_enqueue_hcmd(il, cmd);
	अगर (ret < 0) अणु
		IL_ERR("Error sending %s: enqueue_hcmd failed: %d\n",
		       il_get_cmd_string(cmd->id), ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
il_send_cmd_sync(काष्ठा il_priv *il, काष्ठा il_host_cmd *cmd)
अणु
	पूर्णांक cmd_idx;
	पूर्णांक ret;

	lockdep_निश्चित_held(&il->mutex);

	BUG_ON(cmd->flags & CMD_ASYNC);

	/* A synchronous command can not have a callback set. */
	BUG_ON(cmd->callback);

	D_INFO("Attempting to send sync command %s\n",
	       il_get_cmd_string(cmd->id));

	set_bit(S_HCMD_ACTIVE, &il->status);
	D_INFO("Setting HCMD_ACTIVE for command %s\n",
	       il_get_cmd_string(cmd->id));

	cmd_idx = il_enqueue_hcmd(il, cmd);
	अगर (cmd_idx < 0) अणु
		ret = cmd_idx;
		IL_ERR("Error sending %s: enqueue_hcmd failed: %d\n",
		       il_get_cmd_string(cmd->id), ret);
		जाओ out;
	पूर्ण

	ret = रुको_event_समयout(il->रुको_command_queue,
				 !test_bit(S_HCMD_ACTIVE, &il->status),
				 HOST_COMPLETE_TIMEOUT);
	अगर (!ret) अणु
		अगर (test_bit(S_HCMD_ACTIVE, &il->status)) अणु
			IL_ERR("Error sending %s: time out after %dms.\n",
			       il_get_cmd_string(cmd->id),
			       jअगरfies_to_msecs(HOST_COMPLETE_TIMEOUT));

			clear_bit(S_HCMD_ACTIVE, &il->status);
			D_INFO("Clearing HCMD_ACTIVE for command %s\n",
			       il_get_cmd_string(cmd->id));
			ret = -ETIMEDOUT;
			जाओ cancel;
		पूर्ण
	पूर्ण

	अगर (test_bit(S_RFKILL, &il->status)) अणु
		IL_ERR("Command %s aborted: RF KILL Switch\n",
		       il_get_cmd_string(cmd->id));
		ret = -ECANCELED;
		जाओ fail;
	पूर्ण
	अगर (test_bit(S_FW_ERROR, &il->status)) अणु
		IL_ERR("Command %s failed: FW Error\n",
		       il_get_cmd_string(cmd->id));
		ret = -EIO;
		जाओ fail;
	पूर्ण
	अगर ((cmd->flags & CMD_WANT_SKB) && !cmd->reply_page) अणु
		IL_ERR("Error: Response NULL in '%s'\n",
		       il_get_cmd_string(cmd->id));
		ret = -EIO;
		जाओ cancel;
	पूर्ण

	ret = 0;
	जाओ out;

cancel:
	अगर (cmd->flags & CMD_WANT_SKB) अणु
		/*
		 * Cancel the CMD_WANT_SKB flag क्रम the cmd in the
		 * TX cmd queue. Otherwise in हाल the cmd comes
		 * in later, it will possibly set an invalid
		 * address (cmd->meta.source).
		 */
		il->txq[il->cmd_queue].meta[cmd_idx].flags &= ~CMD_WANT_SKB;
	पूर्ण
fail:
	अगर (cmd->reply_page) अणु
		il_मुक्त_pages(il, cmd->reply_page);
		cmd->reply_page = 0;
	पूर्ण
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(il_send_cmd_sync);

पूर्णांक
il_send_cmd(काष्ठा il_priv *il, काष्ठा il_host_cmd *cmd)
अणु
	अगर (cmd->flags & CMD_ASYNC)
		वापस il_send_cmd_async(il, cmd);

	वापस il_send_cmd_sync(il, cmd);
पूर्ण
EXPORT_SYMBOL(il_send_cmd);

पूर्णांक
il_send_cmd_pdu(काष्ठा il_priv *il, u8 id, u16 len, स्थिर व्योम *data)
अणु
	काष्ठा il_host_cmd cmd = अणु
		.id = id,
		.len = len,
		.data = data,
	पूर्ण;

	वापस il_send_cmd_sync(il, &cmd);
पूर्ण
EXPORT_SYMBOL(il_send_cmd_pdu);

पूर्णांक
il_send_cmd_pdu_async(काष्ठा il_priv *il, u8 id, u16 len, स्थिर व्योम *data,
		      व्योम (*callback) (काष्ठा il_priv *il,
					काष्ठा il_device_cmd *cmd,
					काष्ठा il_rx_pkt *pkt))
अणु
	काष्ठा il_host_cmd cmd = अणु
		.id = id,
		.len = len,
		.data = data,
	पूर्ण;

	cmd.flags |= CMD_ASYNC;
	cmd.callback = callback;

	वापस il_send_cmd_async(il, &cmd);
पूर्ण
EXPORT_SYMBOL(il_send_cmd_pdu_async);

/* शेष: IL_LED_BLINK(0) using blinking idx table */
अटल पूर्णांक led_mode;
module_param(led_mode, पूर्णांक, 0444);
MODULE_PARM_DESC(led_mode,
		 "0=system default, " "1=On(RF On)/Off(RF Off), 2=blinking");

/* Throughput		OFF समय(ms)	ON समय (ms)
 *	>300			25		25
 *	>200 to 300		40		40
 *	>100 to 200		55		55
 *	>70 to 100		65		65
 *	>50 to 70		75		75
 *	>20 to 50		85		85
 *	>10 to 20		95		95
 *	>5 to 10		110		110
 *	>1 to 5			130		130
 *	>0 to 1			167		167
 *	<=0					SOLID ON
 */
अटल स्थिर काष्ठा ieee80211_tpt_blink il_blink[] = अणु
	अणु.throughput = 0,		.blink_समय = 334पूर्ण,
	अणु.throughput = 1 * 1024 - 1,	.blink_समय = 260पूर्ण,
	अणु.throughput = 5 * 1024 - 1,	.blink_समय = 220पूर्ण,
	अणु.throughput = 10 * 1024 - 1,	.blink_समय = 190पूर्ण,
	अणु.throughput = 20 * 1024 - 1,	.blink_समय = 170पूर्ण,
	अणु.throughput = 50 * 1024 - 1,	.blink_समय = 150पूर्ण,
	अणु.throughput = 70 * 1024 - 1,	.blink_समय = 130पूर्ण,
	अणु.throughput = 100 * 1024 - 1,	.blink_समय = 110पूर्ण,
	अणु.throughput = 200 * 1024 - 1,	.blink_समय = 80पूर्ण,
	अणु.throughput = 300 * 1024 - 1,	.blink_समय = 50पूर्ण,
पूर्ण;

/*
 * Adjust led blink rate to compensate on a MAC Clock dअगरference on every HW
 * Led blink rate analysis showed an average deviation of 0% on 3945,
 * 5% on 4965 HW.
 * Need to compensate on the led on/off समय per HW according to the deviation
 * to achieve the desired led frequency
 * The calculation is: (100-averageDeviation)/100 * blinkTime
 * For code efficiency the calculation will be:
 *     compensation = (100 - averageDeviation) * 64 / 100
 *     NewBlinkTime = (compensation * BlinkTime) / 64
 */
अटल अंतरभूत u8
il_blink_compensation(काष्ठा il_priv *il, u8 समय, u16 compensation)
अणु
	अगर (!compensation) अणु
		IL_ERR("undefined blink compensation: "
		       "use pre-defined blinking time\n");
		वापस समय;
	पूर्ण

	वापस (u8) ((समय * compensation) >> 6);
पूर्ण

/* Set led pattern command */
अटल पूर्णांक
il_led_cmd(काष्ठा il_priv *il, अचिन्हित दीर्घ on, अचिन्हित दीर्घ off)
अणु
	काष्ठा il_led_cmd led_cmd = अणु
		.id = IL_LED_LINK,
		.पूर्णांकerval = IL_DEF_LED_INTRVL
	पूर्ण;
	पूर्णांक ret;

	अगर (!test_bit(S_READY, &il->status))
		वापस -EBUSY;

	अगर (il->blink_on == on && il->blink_off == off)
		वापस 0;

	अगर (off == 0) अणु
		/* led is SOLID_ON */
		on = IL_LED_SOLID;
	पूर्ण

	D_LED("Led blink time compensation=%u\n",
	      il->cfg->led_compensation);
	led_cmd.on =
	    il_blink_compensation(il, on,
				  il->cfg->led_compensation);
	led_cmd.off =
	    il_blink_compensation(il, off,
				  il->cfg->led_compensation);

	ret = il->ops->send_led_cmd(il, &led_cmd);
	अगर (!ret) अणु
		il->blink_on = on;
		il->blink_off = off;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
il_led_brightness_set(काष्ठा led_classdev *led_cdev,
		      क्रमागत led_brightness brightness)
अणु
	काष्ठा il_priv *il = container_of(led_cdev, काष्ठा il_priv, led);
	अचिन्हित दीर्घ on = 0;

	अगर (brightness > 0)
		on = IL_LED_SOLID;

	il_led_cmd(il, on, 0);
पूर्ण

अटल पूर्णांक
il_led_blink_set(काष्ठा led_classdev *led_cdev, अचिन्हित दीर्घ *delay_on,
		 अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा il_priv *il = container_of(led_cdev, काष्ठा il_priv, led);

	वापस il_led_cmd(il, *delay_on, *delay_off);
पूर्ण

व्योम
il_leds_init(काष्ठा il_priv *il)
अणु
	पूर्णांक mode = led_mode;
	पूर्णांक ret;

	अगर (mode == IL_LED_DEFAULT)
		mode = il->cfg->led_mode;

	il->led.name =
	    kaप्र_लिखो(GFP_KERNEL, "%s-led", wiphy_name(il->hw->wiphy));
	il->led.brightness_set = il_led_brightness_set;
	il->led.blink_set = il_led_blink_set;
	il->led.max_brightness = 1;

	चयन (mode) अणु
	हाल IL_LED_DEFAULT:
		WARN_ON(1);
		अवरोध;
	हाल IL_LED_BLINK:
		il->led.शेष_trigger =
		    ieee80211_create_tpt_led_trigger(il->hw,
						     IEEE80211_TPT_LEDTRIG_FL_CONNECTED,
						     il_blink,
						     ARRAY_SIZE(il_blink));
		अवरोध;
	हाल IL_LED_RF_STATE:
		il->led.शेष_trigger = ieee80211_get_radio_led_name(il->hw);
		अवरोध;
	पूर्ण

	ret = led_classdev_रेजिस्टर(&il->pci_dev->dev, &il->led);
	अगर (ret) अणु
		kमुक्त(il->led.name);
		वापस;
	पूर्ण

	il->led_रेजिस्टरed = true;
पूर्ण
EXPORT_SYMBOL(il_leds_init);

व्योम
il_leds_निकास(काष्ठा il_priv *il)
अणु
	अगर (!il->led_रेजिस्टरed)
		वापस;

	led_classdev_unरेजिस्टर(&il->led);
	kमुक्त(il->led.name);
पूर्ण
EXPORT_SYMBOL(il_leds_निकास);

/************************** EEPROM BANDS ****************************
 *
 * The il_eeprom_band definitions below provide the mapping from the
 * EEPROM contents to the specअगरic channel number supported क्रम each
 * band.
 *
 * For example, il_priv->eeprom.band_3_channels[4] from the band_3
 * definition below maps to physical channel 42 in the 5.2GHz spectrum.
 * The specअगरic geography and calibration inक्रमmation क्रम that channel
 * is contained in the eeprom map itself.
 *
 * During init, we copy the eeprom inक्रमmation and channel map
 * inक्रमmation पूर्णांकo il->channel_info_24/52 and il->channel_map_24/52
 *
 * channel_map_24/52 provides the idx in the channel_info array क्रम a
 * given channel.  We have to have two separate maps as there is channel
 * overlap with the 2.4GHz and 5.2GHz spectrum as seen in band_1 and
 * band_2
 *
 * A value of 0xff stored in the channel_map indicates that the channel
 * is not supported by the hardware at all.
 *
 * A value of 0xfe in the channel_map indicates that the channel is not
 * valid क्रम Tx with the current hardware.  This means that
 * जबतक the प्रणाली can tune and receive on a given channel, it may not
 * be able to associate or transmit any frames on that
 * channel.  There is no corresponding channel inक्रमmation क्रम that
 * entry.
 *
 *********************************************************************/

/* 2.4 GHz */
स्थिर u8 il_eeprom_band_1[14] = अणु
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
पूर्ण;

/* 5.2 GHz bands */
अटल स्थिर u8 il_eeprom_band_2[] = अणु	/* 4915-5080MHz */
	183, 184, 185, 187, 188, 189, 192, 196, 7, 8, 11, 12, 16
पूर्ण;

अटल स्थिर u8 il_eeprom_band_3[] = अणु	/* 5170-5320MHz */
	34, 36, 38, 40, 42, 44, 46, 48, 52, 56, 60, 64
पूर्ण;

अटल स्थिर u8 il_eeprom_band_4[] = अणु	/* 5500-5700MHz */
	100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140
पूर्ण;

अटल स्थिर u8 il_eeprom_band_5[] = अणु	/* 5725-5825MHz */
	145, 149, 153, 157, 161, 165
पूर्ण;

अटल स्थिर u8 il_eeprom_band_6[] = अणु	/* 2.4 ht40 channel */
	1, 2, 3, 4, 5, 6, 7
पूर्ण;

अटल स्थिर u8 il_eeprom_band_7[] = अणु	/* 5.2 ht40 channel */
	36, 44, 52, 60, 100, 108, 116, 124, 132, 149, 157
पूर्ण;

/******************************************************************************
 *
 * EEPROM related functions
 *
******************************************************************************/

अटल पूर्णांक
il_eeprom_verअगरy_signature(काष्ठा il_priv *il)
अणु
	u32 gp = _il_rd(il, CSR_EEPROM_GP) & CSR_EEPROM_GP_VALID_MSK;
	पूर्णांक ret = 0;

	D_EEPROM("EEPROM signature=0x%08x\n", gp);
	चयन (gp) अणु
	हाल CSR_EEPROM_GP_GOOD_SIG_EEP_LESS_THAN_4K:
	हाल CSR_EEPROM_GP_GOOD_SIG_EEP_MORE_THAN_4K:
		अवरोध;
	शेष:
		IL_ERR("bad EEPROM signature," "EEPROM_GP=0x%08x\n", gp);
		ret = -ENOENT;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

स्थिर u8 *
il_eeprom_query_addr(स्थिर काष्ठा il_priv *il, माप_प्रकार offset)
अणु
	BUG_ON(offset >= il->cfg->eeprom_size);
	वापस &il->eeprom[offset];
पूर्ण
EXPORT_SYMBOL(il_eeprom_query_addr);

u16
il_eeprom_query16(स्थिर काष्ठा il_priv *il, माप_प्रकार offset)
अणु
	अगर (!il->eeprom)
		वापस 0;
	वापस (u16) il->eeprom[offset] | ((u16) il->eeprom[offset + 1] << 8);
पूर्ण
EXPORT_SYMBOL(il_eeprom_query16);

/*
 * il_eeprom_init - पढ़ो EEPROM contents
 *
 * Load the EEPROM contents from adapter पूर्णांकo il->eeprom
 *
 * NOTE:  This routine uses the non-debug IO access functions.
 */
पूर्णांक
il_eeprom_init(काष्ठा il_priv *il)
अणु
	__le16 *e;
	u32 gp = _il_rd(il, CSR_EEPROM_GP);
	पूर्णांक sz;
	पूर्णांक ret;
	पूर्णांक addr;

	/* allocate eeprom */
	sz = il->cfg->eeprom_size;
	D_EEPROM("NVM size = %d\n", sz);
	il->eeprom = kzalloc(sz, GFP_KERNEL);
	अगर (!il->eeprom)
		वापस -ENOMEM;

	e = (__le16 *) il->eeprom;

	il->ops->apm_init(il);

	ret = il_eeprom_verअगरy_signature(il);
	अगर (ret < 0) अणु
		IL_ERR("EEPROM not found, EEPROM_GP=0x%08x\n", gp);
		ret = -ENOENT;
		जाओ err;
	पूर्ण

	/* Make sure driver (instead of uCode) is allowed to पढ़ो EEPROM */
	ret = il->ops->eeprom_acquire_semaphore(il);
	अगर (ret < 0) अणु
		IL_ERR("Failed to acquire EEPROM semaphore.\n");
		ret = -ENOENT;
		जाओ err;
	पूर्ण

	/* eeprom is an array of 16bit values */
	क्रम (addr = 0; addr < sz; addr += माप(u16)) अणु
		u32 r;

		_il_wr(il, CSR_EEPROM_REG,
		       CSR_EEPROM_REG_MSK_ADDR & (addr << 1));

		ret =
		    _il_poll_bit(il, CSR_EEPROM_REG,
				 CSR_EEPROM_REG_READ_VALID_MSK,
				 CSR_EEPROM_REG_READ_VALID_MSK,
				 IL_EEPROM_ACCESS_TIMEOUT);
		अगर (ret < 0) अणु
			IL_ERR("Time out reading EEPROM[%d]\n", addr);
			जाओ करोne;
		पूर्ण
		r = _il_rd(il, CSR_EEPROM_REG);
		e[addr / 2] = cpu_to_le16(r >> 16);
	पूर्ण

	D_EEPROM("NVM Type: %s, version: 0x%x\n", "EEPROM",
		 il_eeprom_query16(il, EEPROM_VERSION));

	ret = 0;
करोne:
	il->ops->eeprom_release_semaphore(il);

err:
	अगर (ret)
		il_eeprom_मुक्त(il);
	/* Reset chip to save घातer until we load uCode during "up". */
	il_apm_stop(il);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(il_eeprom_init);

व्योम
il_eeprom_मुक्त(काष्ठा il_priv *il)
अणु
	kमुक्त(il->eeprom);
	il->eeprom = शून्य;
पूर्ण
EXPORT_SYMBOL(il_eeprom_मुक्त);

अटल व्योम
il_init_band_reference(स्थिर काष्ठा il_priv *il, पूर्णांक eep_band,
		       पूर्णांक *eeprom_ch_count,
		       स्थिर काष्ठा il_eeprom_channel **eeprom_ch_info,
		       स्थिर u8 **eeprom_ch_idx)
अणु
	u32 offset = il->cfg->regulatory_bands[eep_band - 1];

	चयन (eep_band) अणु
	हाल 1:		/* 2.4GHz band */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_1);
		*eeprom_ch_info =
		    (काष्ठा il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_1;
		अवरोध;
	हाल 2:		/* 4.9GHz band */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_2);
		*eeprom_ch_info =
		    (काष्ठा il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_2;
		अवरोध;
	हाल 3:		/* 5.2GHz band */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_3);
		*eeprom_ch_info =
		    (काष्ठा il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_3;
		अवरोध;
	हाल 4:		/* 5.5GHz band */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_4);
		*eeprom_ch_info =
		    (काष्ठा il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_4;
		अवरोध;
	हाल 5:		/* 5.7GHz band */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_5);
		*eeprom_ch_info =
		    (काष्ठा il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_5;
		अवरोध;
	हाल 6:		/* 2.4GHz ht40 channels */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_6);
		*eeprom_ch_info =
		    (काष्ठा il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_6;
		अवरोध;
	हाल 7:		/* 5 GHz ht40 channels */
		*eeprom_ch_count = ARRAY_SIZE(il_eeprom_band_7);
		*eeprom_ch_info =
		    (काष्ठा il_eeprom_channel *)il_eeprom_query_addr(il,
								     offset);
		*eeprom_ch_idx = il_eeprom_band_7;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

#घोषणा CHECK_AND_PRINT(x) ((eeprom_ch->flags & EEPROM_CHANNEL_##x) \
			    ? # x " " : "")
/*
 * il_mod_ht40_chan_info - Copy ht40 channel info पूर्णांकo driver's il.
 *
 * Does not set up a command, or touch hardware.
 */
अटल पूर्णांक
il_mod_ht40_chan_info(काष्ठा il_priv *il, क्रमागत nl80211_band band, u16 channel,
		      स्थिर काष्ठा il_eeprom_channel *eeprom_ch,
		      u8 clear_ht40_extension_channel)
अणु
	काष्ठा il_channel_info *ch_info;

	ch_info =
	    (काष्ठा il_channel_info *)il_get_channel_info(il, band, channel);

	अगर (!il_is_channel_valid(ch_info))
		वापस -1;

	D_EEPROM("HT40 Ch. %d [%sGHz] %s%s%s%s%s(0x%02x %ddBm):"
		 " Ad-Hoc %ssupported\n", ch_info->channel,
		 il_is_channel_a_band(ch_info) ? "5.2" : "2.4",
		 CHECK_AND_PRINT(IBSS), CHECK_AND_PRINT(ACTIVE),
		 CHECK_AND_PRINT(RADAR), CHECK_AND_PRINT(WIDE),
		 CHECK_AND_PRINT(DFS), eeprom_ch->flags,
		 eeprom_ch->max_घातer_avg,
		 ((eeprom_ch->flags & EEPROM_CHANNEL_IBSS) &&
		  !(eeprom_ch->flags & EEPROM_CHANNEL_RADAR)) ? "" : "not ");

	ch_info->ht40_eeprom = *eeprom_ch;
	ch_info->ht40_max_घातer_avg = eeprom_ch->max_घातer_avg;
	ch_info->ht40_flags = eeprom_ch->flags;
	अगर (eeprom_ch->flags & EEPROM_CHANNEL_VALID)
		ch_info->ht40_extension_channel &=
		    ~clear_ht40_extension_channel;

	वापस 0;
पूर्ण

#घोषणा CHECK_AND_PRINT_I(x) ((eeprom_ch_info[ch].flags & EEPROM_CHANNEL_##x) \
			    ? # x " " : "")

/*
 * il_init_channel_map - Set up driver's info क्रम all possible channels
 */
पूर्णांक
il_init_channel_map(काष्ठा il_priv *il)
अणु
	पूर्णांक eeprom_ch_count = 0;
	स्थिर u8 *eeprom_ch_idx = शून्य;
	स्थिर काष्ठा il_eeprom_channel *eeprom_ch_info = शून्य;
	पूर्णांक band, ch;
	काष्ठा il_channel_info *ch_info;

	अगर (il->channel_count) अणु
		D_EEPROM("Channel map already initialized.\n");
		वापस 0;
	पूर्ण

	D_EEPROM("Initializing regulatory info from EEPROM\n");

	il->channel_count =
	    ARRAY_SIZE(il_eeprom_band_1) + ARRAY_SIZE(il_eeprom_band_2) +
	    ARRAY_SIZE(il_eeprom_band_3) + ARRAY_SIZE(il_eeprom_band_4) +
	    ARRAY_SIZE(il_eeprom_band_5);

	D_EEPROM("Parsing data for %d channels.\n", il->channel_count);

	il->channel_info =
	    kसुस्मृति(il->channel_count, माप(काष्ठा il_channel_info),
		    GFP_KERNEL);
	अगर (!il->channel_info) अणु
		IL_ERR("Could not allocate channel_info\n");
		il->channel_count = 0;
		वापस -ENOMEM;
	पूर्ण

	ch_info = il->channel_info;

	/* Loop through the 5 EEPROM bands adding them in order to the
	 * channel map we मुख्यtain (that contains additional inक्रमmation than
	 * what just in the EEPROM) */
	क्रम (band = 1; band <= 5; band++) अणु

		il_init_band_reference(il, band, &eeprom_ch_count,
				       &eeprom_ch_info, &eeprom_ch_idx);

		/* Loop through each band adding each of the channels */
		क्रम (ch = 0; ch < eeprom_ch_count; ch++) अणु
			ch_info->channel = eeprom_ch_idx[ch];
			ch_info->band =
			    (band ==
			     1) ? NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;

			/* permanently store EEPROM's channel regulatory flags
			 *   and max घातer in channel info database. */
			ch_info->eeprom = eeprom_ch_info[ch];

			/* Copy the run-समय flags so they are there even on
			 * invalid channels */
			ch_info->flags = eeprom_ch_info[ch].flags;
			/* First ग_लिखो that ht40 is not enabled, and then enable
			 * one by one */
			ch_info->ht40_extension_channel =
			    IEEE80211_CHAN_NO_HT40;

			अगर (!(il_is_channel_valid(ch_info))) अणु
				D_EEPROM("Ch. %d Flags %x [%sGHz] - "
					 "No traffic\n", ch_info->channel,
					 ch_info->flags,
					 il_is_channel_a_band(ch_info) ? "5.2" :
					 "2.4");
				ch_info++;
				जारी;
			पूर्ण

			/* Initialize regulatory-based run-समय data */
			ch_info->max_घातer_avg = ch_info->curr_txघात =
			    eeprom_ch_info[ch].max_घातer_avg;
			ch_info->scan_घातer = eeprom_ch_info[ch].max_घातer_avg;
			ch_info->min_घातer = 0;

			D_EEPROM("Ch. %d [%sGHz] " "%s%s%s%s%s%s(0x%02x %ddBm):"
				 " Ad-Hoc %ssupported\n", ch_info->channel,
				 il_is_channel_a_band(ch_info) ? "5.2" : "2.4",
				 CHECK_AND_PRINT_I(VALID),
				 CHECK_AND_PRINT_I(IBSS),
				 CHECK_AND_PRINT_I(ACTIVE),
				 CHECK_AND_PRINT_I(RADAR),
				 CHECK_AND_PRINT_I(WIDE),
				 CHECK_AND_PRINT_I(DFS),
				 eeprom_ch_info[ch].flags,
				 eeprom_ch_info[ch].max_घातer_avg,
				 ((eeprom_ch_info[ch].
				   flags & EEPROM_CHANNEL_IBSS) &&
				  !(eeprom_ch_info[ch].
				    flags & EEPROM_CHANNEL_RADAR)) ? "" :
				 "not ");

			ch_info++;
		पूर्ण
	पूर्ण

	/* Check अगर we करो have HT40 channels */
	अगर (il->cfg->regulatory_bands[5] == EEPROM_REGULATORY_BAND_NO_HT40 &&
	    il->cfg->regulatory_bands[6] == EEPROM_REGULATORY_BAND_NO_HT40)
		वापस 0;

	/* Two additional EEPROM bands क्रम 2.4 and 5 GHz HT40 channels */
	क्रम (band = 6; band <= 7; band++) अणु
		क्रमागत nl80211_band ieeeband;

		il_init_band_reference(il, band, &eeprom_ch_count,
				       &eeprom_ch_info, &eeprom_ch_idx);

		/* EEPROM band 6 is 2.4, band 7 is 5 GHz */
		ieeeband =
		    (band == 6) ? NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;

		/* Loop through each band adding each of the channels */
		क्रम (ch = 0; ch < eeprom_ch_count; ch++) अणु
			/* Set up driver's info क्रम lower half */
			il_mod_ht40_chan_info(il, ieeeband, eeprom_ch_idx[ch],
					      &eeprom_ch_info[ch],
					      IEEE80211_CHAN_NO_HT40PLUS);

			/* Set up driver's info क्रम upper half */
			il_mod_ht40_chan_info(il, ieeeband,
					      eeprom_ch_idx[ch] + 4,
					      &eeprom_ch_info[ch],
					      IEEE80211_CHAN_NO_HT40MINUS);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(il_init_channel_map);

/*
 * il_मुक्त_channel_map - unकरो allocations in il_init_channel_map
 */
व्योम
il_मुक्त_channel_map(काष्ठा il_priv *il)
अणु
	kमुक्त(il->channel_info);
	il->channel_count = 0;
पूर्ण
EXPORT_SYMBOL(il_मुक्त_channel_map);

/*
 * il_get_channel_info - Find driver's ilate channel info
 *
 * Based on band and channel number.
 */
स्थिर काष्ठा il_channel_info *
il_get_channel_info(स्थिर काष्ठा il_priv *il, क्रमागत nl80211_band band,
		    u16 channel)
अणु
	पूर्णांक i;

	चयन (band) अणु
	हाल NL80211_BAND_5GHZ:
		क्रम (i = 14; i < il->channel_count; i++) अणु
			अगर (il->channel_info[i].channel == channel)
				वापस &il->channel_info[i];
		पूर्ण
		अवरोध;
	हाल NL80211_BAND_2GHZ:
		अगर (channel >= 1 && channel <= 14)
			वापस &il->channel_info[channel - 1];
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(il_get_channel_info);

/*
 * Setting घातer level allows the card to go to sleep when not busy.
 *
 * We calculate a sleep command based on the required latency, which
 * we get from mac80211.
 */

#घोषणा SLP_VEC(X0, X1, X2, X3, X4) अणु \
		cpu_to_le32(X0), \
		cpu_to_le32(X1), \
		cpu_to_le32(X2), \
		cpu_to_le32(X3), \
		cpu_to_le32(X4)  \
पूर्ण

अटल व्योम
il_build_घातertable_cmd(काष्ठा il_priv *il, काष्ठा il_घातertable_cmd *cmd)
अणु
	अटल स्थिर __le32 पूर्णांकerval[3][IL_POWER_VEC_SIZE] = अणु
		SLP_VEC(2, 2, 4, 6, 0xFF),
		SLP_VEC(2, 4, 7, 10, 10),
		SLP_VEC(4, 7, 10, 10, 0xFF)
	पूर्ण;
	पूर्णांक i, dtim_period, no_dtim;
	u32 max_sleep;
	bool skip;

	स_रखो(cmd, 0, माप(*cmd));

	अगर (il->घातer_data.pci_pm)
		cmd->flags |= IL_POWER_PCI_PM_MSK;

	/* अगर no Power Save, we are करोne */
	अगर (il->घातer_data.ps_disabled)
		वापस;

	cmd->flags = IL_POWER_DRIVER_ALLOW_SLEEP_MSK;
	cmd->keep_alive_seconds = 0;
	cmd->debug_flags = 0;
	cmd->rx_data_समयout = cpu_to_le32(25 * 1024);
	cmd->tx_data_समयout = cpu_to_le32(25 * 1024);
	cmd->keep_alive_beacons = 0;

	dtim_period = il->vअगर ? il->vअगर->bss_conf.dtim_period : 0;

	अगर (dtim_period <= 2) अणु
		स_नकल(cmd->sleep_पूर्णांकerval, पूर्णांकerval[0], माप(पूर्णांकerval[0]));
		no_dtim = 2;
	पूर्ण अन्यथा अगर (dtim_period <= 10) अणु
		स_नकल(cmd->sleep_पूर्णांकerval, पूर्णांकerval[1], माप(पूर्णांकerval[1]));
		no_dtim = 2;
	पूर्ण अन्यथा अणु
		स_नकल(cmd->sleep_पूर्णांकerval, पूर्णांकerval[2], माप(पूर्णांकerval[2]));
		no_dtim = 0;
	पूर्ण

	अगर (dtim_period == 0) अणु
		dtim_period = 1;
		skip = false;
	पूर्ण अन्यथा अणु
		skip = !!no_dtim;
	पूर्ण

	अगर (skip) अणु
		__le32 पंचांगp = cmd->sleep_पूर्णांकerval[IL_POWER_VEC_SIZE - 1];

		max_sleep = le32_to_cpu(पंचांगp);
		अगर (max_sleep == 0xFF)
			max_sleep = dtim_period * (skip + 1);
		अन्यथा अगर (max_sleep >  dtim_period)
			max_sleep = (max_sleep / dtim_period) * dtim_period;
		cmd->flags |= IL_POWER_SLEEP_OVER_DTIM_MSK;
	पूर्ण अन्यथा अणु
		max_sleep = dtim_period;
		cmd->flags &= ~IL_POWER_SLEEP_OVER_DTIM_MSK;
	पूर्ण

	क्रम (i = 0; i < IL_POWER_VEC_SIZE; i++)
		अगर (le32_to_cpu(cmd->sleep_पूर्णांकerval[i]) > max_sleep)
			cmd->sleep_पूर्णांकerval[i] = cpu_to_le32(max_sleep);
पूर्ण

अटल पूर्णांक
il_set_घातer(काष्ठा il_priv *il, काष्ठा il_घातertable_cmd *cmd)
अणु
	D_POWER("Sending power/sleep command\n");
	D_POWER("Flags value = 0x%08X\n", cmd->flags);
	D_POWER("Tx timeout = %u\n", le32_to_cpu(cmd->tx_data_समयout));
	D_POWER("Rx timeout = %u\n", le32_to_cpu(cmd->rx_data_समयout));
	D_POWER("Sleep interval vector = { %d , %d , %d , %d , %d }\n",
		le32_to_cpu(cmd->sleep_पूर्णांकerval[0]),
		le32_to_cpu(cmd->sleep_पूर्णांकerval[1]),
		le32_to_cpu(cmd->sleep_पूर्णांकerval[2]),
		le32_to_cpu(cmd->sleep_पूर्णांकerval[3]),
		le32_to_cpu(cmd->sleep_पूर्णांकerval[4]));

	वापस il_send_cmd_pdu(il, C_POWER_TBL,
			       माप(काष्ठा il_घातertable_cmd), cmd);
पूर्ण

अटल पूर्णांक
il_घातer_set_mode(काष्ठा il_priv *il, काष्ठा il_घातertable_cmd *cmd, bool क्रमce)
अणु
	पूर्णांक ret;
	bool update_chains;

	lockdep_निश्चित_held(&il->mutex);

	/* Don't update the RX chain when chain noise calibration is running */
	update_chains = il->chain_noise_data.state == IL_CHAIN_NOISE_DONE ||
	    il->chain_noise_data.state == IL_CHAIN_NOISE_ALIVE;

	अगर (!स_भेद(&il->घातer_data.sleep_cmd, cmd, माप(*cmd)) && !क्रमce)
		वापस 0;

	अगर (!il_is_पढ़ोy_rf(il))
		वापस -EIO;

	/* scan complete use sleep_घातer_next, need to be updated */
	स_नकल(&il->घातer_data.sleep_cmd_next, cmd, माप(*cmd));
	अगर (test_bit(S_SCANNING, &il->status) && !क्रमce) अणु
		D_INFO("Defer power set mode while scanning\n");
		वापस 0;
	पूर्ण

	अगर (cmd->flags & IL_POWER_DRIVER_ALLOW_SLEEP_MSK)
		set_bit(S_POWER_PMI, &il->status);

	ret = il_set_घातer(il, cmd);
	अगर (!ret) अणु
		अगर (!(cmd->flags & IL_POWER_DRIVER_ALLOW_SLEEP_MSK))
			clear_bit(S_POWER_PMI, &il->status);

		अगर (il->ops->update_chain_flags && update_chains)
			il->ops->update_chain_flags(il);
		अन्यथा अगर (il->ops->update_chain_flags)
			D_POWER("Cannot update the power, chain noise "
				"calibration running: %d\n",
				il->chain_noise_data.state);

		स_नकल(&il->घातer_data.sleep_cmd, cmd, माप(*cmd));
	पूर्ण अन्यथा
		IL_ERR("set power fail, ret = %d", ret);

	वापस ret;
पूर्ण

पूर्णांक
il_घातer_update_mode(काष्ठा il_priv *il, bool क्रमce)
अणु
	काष्ठा il_घातertable_cmd cmd;

	il_build_घातertable_cmd(il, &cmd);

	वापस il_घातer_set_mode(il, &cmd, क्रमce);
पूर्ण
EXPORT_SYMBOL(il_घातer_update_mode);

/* initialize to शेष */
व्योम
il_घातer_initialize(काष्ठा il_priv *il)
अणु
	u16 lctl;

	pcie_capability_पढ़ो_word(il->pci_dev, PCI_EXP_LNKCTL, &lctl);
	il->घातer_data.pci_pm = !(lctl & PCI_EXP_LNKCTL_ASPM_L0S);

	il->घातer_data.debug_sleep_level_override = -1;

	स_रखो(&il->घातer_data.sleep_cmd, 0, माप(il->घातer_data.sleep_cmd));
पूर्ण
EXPORT_SYMBOL(il_घातer_initialize);

/* For active scan, listen ACTIVE_DWELL_TIME (msec) on each channel after
 * sending probe req.  This should be set दीर्घ enough to hear probe responses
 * from more than one AP.  */
#घोषणा IL_ACTIVE_DWELL_TIME_24    (30)	/* all बार in msec */
#घोषणा IL_ACTIVE_DWELL_TIME_52    (20)

#घोषणा IL_ACTIVE_DWELL_FACTOR_24GHZ (3)
#घोषणा IL_ACTIVE_DWELL_FACTOR_52GHZ (2)

/* For passive scan, listen PASSIVE_DWELL_TIME (msec) on each channel.
 * Must be set दीर्घer than active dwell समय.
 * For the most reliable scan, set > AP beacon पूर्णांकerval (typically 100msec). */
#घोषणा IL_PASSIVE_DWELL_TIME_24   (20)	/* all बार in msec */
#घोषणा IL_PASSIVE_DWELL_TIME_52   (10)
#घोषणा IL_PASSIVE_DWELL_BASE      (100)
#घोषणा IL_CHANNEL_TUNE_TIME       5

अटल पूर्णांक
il_send_scan_पात(काष्ठा il_priv *il)
अणु
	पूर्णांक ret;
	काष्ठा il_rx_pkt *pkt;
	काष्ठा il_host_cmd cmd = अणु
		.id = C_SCAN_ABORT,
		.flags = CMD_WANT_SKB,
	पूर्ण;

	/* Exit instantly with error when device is not पढ़ोy
	 * to receive scan पात command or it करोes not perक्रमm
	 * hardware scan currently */
	अगर (!test_bit(S_READY, &il->status) ||
	    !test_bit(S_GEO_CONFIGURED, &il->status) ||
	    !test_bit(S_SCAN_HW, &il->status) ||
	    test_bit(S_FW_ERROR, &il->status) ||
	    test_bit(S_EXIT_PENDING, &il->status))
		वापस -EIO;

	ret = il_send_cmd_sync(il, &cmd);
	अगर (ret)
		वापस ret;

	pkt = (काष्ठा il_rx_pkt *)cmd.reply_page;
	अगर (pkt->u.status != CAN_ABORT_STATUS) अणु
		/* The scan पात will वापस 1 क्रम success or
		 * 2 क्रम "failure".  A failure condition can be
		 * due to simply not being in an active scan which
		 * can occur अगर we send the scan पात beक्रमe we
		 * the microcode has notअगरied us that a scan is
		 * completed. */
		D_SCAN("SCAN_ABORT ret %d.\n", pkt->u.status);
		ret = -EIO;
	पूर्ण

	il_मुक्त_pages(il, cmd.reply_page);
	वापस ret;
पूर्ण

अटल व्योम
il_complete_scan(काष्ठा il_priv *il, bool पातed)
अणु
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = पातed,
	पूर्ण;

	/* check अगर scan was requested from mac80211 */
	अगर (il->scan_request) अणु
		D_SCAN("Complete scan in mac80211\n");
		ieee80211_scan_completed(il->hw, &info);
	पूर्ण

	il->scan_vअगर = शून्य;
	il->scan_request = शून्य;
पूर्ण

व्योम
il_क्रमce_scan_end(काष्ठा il_priv *il)
अणु
	lockdep_निश्चित_held(&il->mutex);

	अगर (!test_bit(S_SCANNING, &il->status)) अणु
		D_SCAN("Forcing scan end while not scanning\n");
		वापस;
	पूर्ण

	D_SCAN("Forcing scan end\n");
	clear_bit(S_SCANNING, &il->status);
	clear_bit(S_SCAN_HW, &il->status);
	clear_bit(S_SCAN_ABORTING, &il->status);
	il_complete_scan(il, true);
पूर्ण

अटल व्योम
il_करो_scan_पात(काष्ठा il_priv *il)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&il->mutex);

	अगर (!test_bit(S_SCANNING, &il->status)) अणु
		D_SCAN("Not performing scan to abort\n");
		वापस;
	पूर्ण

	अगर (test_and_set_bit(S_SCAN_ABORTING, &il->status)) अणु
		D_SCAN("Scan abort in progress\n");
		वापस;
	पूर्ण

	ret = il_send_scan_पात(il);
	अगर (ret) अणु
		D_SCAN("Send scan abort failed %d\n", ret);
		il_क्रमce_scan_end(il);
	पूर्ण अन्यथा
		D_SCAN("Successfully send scan abort\n");
पूर्ण

/*
 * il_scan_cancel - Cancel any currently executing HW scan
 */
पूर्णांक
il_scan_cancel(काष्ठा il_priv *il)
अणु
	D_SCAN("Queuing abort scan\n");
	queue_work(il->workqueue, &il->पात_scan);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(il_scan_cancel);

/*
 * il_scan_cancel_समयout - Cancel any currently executing HW scan
 * @ms: amount of समय to रुको (in milliseconds) क्रम scan to पात
 *
 */
पूर्णांक
il_scan_cancel_समयout(काष्ठा il_priv *il, अचिन्हित दीर्घ ms)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(ms);

	lockdep_निश्चित_held(&il->mutex);

	D_SCAN("Scan cancel timeout\n");

	il_करो_scan_पात(il);

	जबतक (समय_beक्रमe_eq(jअगरfies, समयout)) अणु
		अगर (!test_bit(S_SCAN_HW, &il->status))
			अवरोध;
		msleep(20);
	पूर्ण

	वापस test_bit(S_SCAN_HW, &il->status);
पूर्ण
EXPORT_SYMBOL(il_scan_cancel_समयout);

/* Service response to C_SCAN (0x80) */
अटल व्योम
il_hdl_scan(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_scanreq_notअगरication *notअगर =
	    (काष्ठा il_scanreq_notअगरication *)pkt->u.raw;

	D_SCAN("Scan request status = 0x%x\n", notअगर->status);
#पूर्ण_अगर
पूर्ण

/* Service N_SCAN_START (0x82) */
अटल व्योम
il_hdl_scan_start(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_scanstart_notअगरication *notअगर =
	    (काष्ठा il_scanstart_notअगरication *)pkt->u.raw;
	il->scan_start_tsf = le32_to_cpu(notअगर->tsf_low);
	D_SCAN("Scan start: " "%d [802.11%s] "
	       "(TSF: 0x%08X:%08X) - %d (beacon timer %u)\n", notअगर->channel,
	       notअगर->band ? "bg" : "a", le32_to_cpu(notअगर->tsf_high),
	       le32_to_cpu(notअगर->tsf_low), notअगर->status, notअगर->beacon_समयr);
पूर्ण

/* Service N_SCAN_RESULTS (0x83) */
अटल व्योम
il_hdl_scan_results(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_scanresults_notअगरication *notअगर =
	    (काष्ठा il_scanresults_notअगरication *)pkt->u.raw;

	D_SCAN("Scan ch.res: " "%d [802.11%s] " "(TSF: 0x%08X:%08X) - %d "
	       "elapsed=%lu usec\n", notअगर->channel, notअगर->band ? "bg" : "a",
	       le32_to_cpu(notअगर->tsf_high), le32_to_cpu(notअगर->tsf_low),
	       le32_to_cpu(notअगर->stats[0]),
	       le32_to_cpu(notअगर->tsf_low) - il->scan_start_tsf);
#पूर्ण_अगर
पूर्ण

/* Service N_SCAN_COMPLETE (0x84) */
अटल व्योम
il_hdl_scan_complete(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु

	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_scancomplete_notअगरication *scan_notअगर = (व्योम *)pkt->u.raw;

	D_SCAN("Scan complete: %d channels (TSF 0x%08X:%08X) - %d\n",
	       scan_notअगर->scanned_channels, scan_notअगर->tsf_low,
	       scan_notअगर->tsf_high, scan_notअगर->status);

	/* The HW is no दीर्घer scanning */
	clear_bit(S_SCAN_HW, &il->status);

	D_SCAN("Scan on %sGHz took %dms\n",
	       (il->scan_band == NL80211_BAND_2GHZ) ? "2.4" : "5.2",
	       jअगरfies_to_msecs(jअगरfies - il->scan_start));

	queue_work(il->workqueue, &il->scan_completed);
पूर्ण

व्योम
il_setup_rx_scan_handlers(काष्ठा il_priv *il)
अणु
	/* scan handlers */
	il->handlers[C_SCAN] = il_hdl_scan;
	il->handlers[N_SCAN_START] = il_hdl_scan_start;
	il->handlers[N_SCAN_RESULTS] = il_hdl_scan_results;
	il->handlers[N_SCAN_COMPLETE] = il_hdl_scan_complete;
पूर्ण
EXPORT_SYMBOL(il_setup_rx_scan_handlers);

u16
il_get_active_dwell_समय(काष्ठा il_priv *il, क्रमागत nl80211_band band,
			 u8 n_probes)
अणु
	अगर (band == NL80211_BAND_5GHZ)
		वापस IL_ACTIVE_DWELL_TIME_52 +
		    IL_ACTIVE_DWELL_FACTOR_52GHZ * (n_probes + 1);
	अन्यथा
		वापस IL_ACTIVE_DWELL_TIME_24 +
		    IL_ACTIVE_DWELL_FACTOR_24GHZ * (n_probes + 1);
पूर्ण
EXPORT_SYMBOL(il_get_active_dwell_समय);

u16
il_get_passive_dwell_समय(काष्ठा il_priv *il, क्रमागत nl80211_band band,
			  काष्ठा ieee80211_vअगर *vअगर)
अणु
	u16 value;

	u16 passive =
	    (band ==
	     NL80211_BAND_2GHZ) ? IL_PASSIVE_DWELL_BASE +
	    IL_PASSIVE_DWELL_TIME_24 : IL_PASSIVE_DWELL_BASE +
	    IL_PASSIVE_DWELL_TIME_52;

	अगर (il_is_any_associated(il)) अणु
		/*
		 * If we're associated, we clamp the maximum passive
		 * dwell समय to be 98% of the smallest beacon पूर्णांकerval
		 * (minus 2 * channel tune समय)
		 */
		value = il->vअगर ? il->vअगर->bss_conf.beacon_पूर्णांक : 0;
		अगर (value > IL_PASSIVE_DWELL_BASE || !value)
			value = IL_PASSIVE_DWELL_BASE;
		value = (value * 98) / 100 - IL_CHANNEL_TUNE_TIME * 2;
		passive = min(value, passive);
	पूर्ण

	वापस passive;
पूर्ण
EXPORT_SYMBOL(il_get_passive_dwell_समय);

व्योम
il_init_scan_params(काष्ठा il_priv *il)
अणु
	u8 ant_idx = fls(il->hw_params.valid_tx_ant) - 1;
	अगर (!il->scan_tx_ant[NL80211_BAND_5GHZ])
		il->scan_tx_ant[NL80211_BAND_5GHZ] = ant_idx;
	अगर (!il->scan_tx_ant[NL80211_BAND_2GHZ])
		il->scan_tx_ant[NL80211_BAND_2GHZ] = ant_idx;
पूर्ण
EXPORT_SYMBOL(il_init_scan_params);

अटल पूर्णांक
il_scan_initiate(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&il->mutex);

	cancel_delayed_work(&il->scan_check);

	अगर (!il_is_पढ़ोy_rf(il)) अणु
		IL_WARN("Request scan called when driver not ready.\n");
		वापस -EIO;
	पूर्ण

	अगर (test_bit(S_SCAN_HW, &il->status)) अणु
		D_SCAN("Multiple concurrent scan requests in parallel.\n");
		वापस -EBUSY;
	पूर्ण

	अगर (test_bit(S_SCAN_ABORTING, &il->status)) अणु
		D_SCAN("Scan request while abort pending.\n");
		वापस -EBUSY;
	पूर्ण

	D_SCAN("Starting scan...\n");

	set_bit(S_SCANNING, &il->status);
	il->scan_start = jअगरfies;

	ret = il->ops->request_scan(il, vअगर);
	अगर (ret) अणु
		clear_bit(S_SCANNING, &il->status);
		वापस ret;
	पूर्ण

	queue_delayed_work(il->workqueue, &il->scan_check,
			   IL_SCAN_CHECK_WATCHDOG);

	वापस 0;
पूर्ण

पूर्णांक
il_mac_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा cfg80211_scan_request *req = &hw_req->req;
	काष्ठा il_priv *il = hw->priv;
	पूर्णांक ret;

	अगर (req->n_channels == 0) अणु
		IL_ERR("Can not scan on no channels.\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&il->mutex);
	D_MAC80211("enter\n");

	अगर (test_bit(S_SCANNING, &il->status)) अणु
		D_SCAN("Scan already in progress.\n");
		ret = -EAGAIN;
		जाओ out_unlock;
	पूर्ण

	/* mac80211 will only ask क्रम one band at a समय */
	il->scan_request = req;
	il->scan_vअगर = vअगर;
	il->scan_band = req->channels[0]->band;

	ret = il_scan_initiate(il, vअगर);

out_unlock:
	D_MAC80211("leave ret %d\n", ret);
	mutex_unlock(&il->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(il_mac_hw_scan);

अटल व्योम
il_bg_scan_check(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा il_priv *il =
	    container_of(data, काष्ठा il_priv, scan_check.work);

	D_SCAN("Scan check work\n");

	/* Since we are here firmware करोes not finish scan and
	 * most likely is in bad shape, so we करोn't bother to
	 * send पात command, just क्रमce scan complete to mac80211 */
	mutex_lock(&il->mutex);
	il_क्रमce_scan_end(il);
	mutex_unlock(&il->mutex);
पूर्ण

/*
 * il_fill_probe_req - fill in all required fields and IE क्रम probe request
 */
u16
il_fill_probe_req(काष्ठा il_priv *il, काष्ठा ieee80211_mgmt *frame,
		  स्थिर u8 *ta, स्थिर u8 *ies, पूर्णांक ie_len, पूर्णांक left)
अणु
	पूर्णांक len = 0;
	u8 *pos = शून्य;

	/* Make sure there is enough space क्रम the probe request,
	 * two mandatory IEs and the data */
	left -= 24;
	अगर (left < 0)
		वापस 0;

	frame->frame_control = cpu_to_le16(IEEE80211_STYPE_PROBE_REQ);
	eth_broadcast_addr(frame->da);
	स_नकल(frame->sa, ta, ETH_ALEN);
	eth_broadcast_addr(frame->bssid);
	frame->seq_ctrl = 0;

	len += 24;

	/* ...next IE... */
	pos = &frame->u.probe_req.variable[0];

	/* fill in our indirect SSID IE */
	left -= 2;
	अगर (left < 0)
		वापस 0;
	*pos++ = WLAN_EID_SSID;
	*pos++ = 0;

	len += 2;

	अगर (WARN_ON(left < ie_len))
		वापस len;

	अगर (ies && ie_len) अणु
		स_नकल(pos, ies, ie_len);
		len += ie_len;
	पूर्ण

	वापस (u16) len;
पूर्ण
EXPORT_SYMBOL(il_fill_probe_req);

अटल व्योम
il_bg_पात_scan(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा il_priv *il = container_of(work, काष्ठा il_priv, पात_scan);

	D_SCAN("Abort scan work\n");

	/* We keep scan_check work queued in हाल when firmware will not
	 * report back scan completed notअगरication */
	mutex_lock(&il->mutex);
	il_scan_cancel_समयout(il, 200);
	mutex_unlock(&il->mutex);
पूर्ण

अटल व्योम
il_bg_scan_completed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा il_priv *il = container_of(work, काष्ठा il_priv, scan_completed);
	bool पातed;

	D_SCAN("Completed scan.\n");

	cancel_delayed_work(&il->scan_check);

	mutex_lock(&il->mutex);

	पातed = test_and_clear_bit(S_SCAN_ABORTING, &il->status);
	अगर (पातed)
		D_SCAN("Aborted scan completed.\n");

	अगर (!test_and_clear_bit(S_SCANNING, &il->status)) अणु
		D_SCAN("Scan already completed.\n");
		जाओ out_settings;
	पूर्ण

	il_complete_scan(il, पातed);

out_settings:
	/* Can we still talk to firmware ? */
	अगर (!il_is_पढ़ोy_rf(il))
		जाओ out;

	/*
	 * We करो not commit घातer settings जबतक scan is pending,
	 * करो it now अगर the settings changed.
	 */
	il_घातer_set_mode(il, &il->घातer_data.sleep_cmd_next, false);
	il_set_tx_घातer(il, il->tx_घातer_next, false);

	il->ops->post_scan(il);

out:
	mutex_unlock(&il->mutex);
पूर्ण

व्योम
il_setup_scan_deferred_work(काष्ठा il_priv *il)
अणु
	INIT_WORK(&il->scan_completed, il_bg_scan_completed);
	INIT_WORK(&il->पात_scan, il_bg_पात_scan);
	INIT_DELAYED_WORK(&il->scan_check, il_bg_scan_check);
पूर्ण
EXPORT_SYMBOL(il_setup_scan_deferred_work);

व्योम
il_cancel_scan_deferred_work(काष्ठा il_priv *il)
अणु
	cancel_work_sync(&il->पात_scan);
	cancel_work_sync(&il->scan_completed);

	अगर (cancel_delayed_work_sync(&il->scan_check)) अणु
		mutex_lock(&il->mutex);
		il_क्रमce_scan_end(il);
		mutex_unlock(&il->mutex);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(il_cancel_scan_deferred_work);

/* il->sta_lock must be held */
अटल व्योम
il_sta_ucode_activate(काष्ठा il_priv *il, u8 sta_id)
अणु

	अगर (!(il->stations[sta_id].used & IL_STA_DRIVER_ACTIVE))
		IL_ERR("ACTIVATE a non DRIVER active station id %u addr %pM\n",
		       sta_id, il->stations[sta_id].sta.sta.addr);

	अगर (il->stations[sta_id].used & IL_STA_UCODE_ACTIVE) अणु
		D_ASSOC("STA id %u addr %pM already present"
			" in uCode (according to driver)\n", sta_id,
			il->stations[sta_id].sta.sta.addr);
	पूर्ण अन्यथा अणु
		il->stations[sta_id].used |= IL_STA_UCODE_ACTIVE;
		D_ASSOC("Added STA id %u addr %pM to uCode\n", sta_id,
			il->stations[sta_id].sta.sta.addr);
	पूर्ण
पूर्ण

अटल पूर्णांक
il_process_add_sta_resp(काष्ठा il_priv *il, काष्ठा il_addsta_cmd *addsta,
			काष्ठा il_rx_pkt *pkt, bool sync)
अणु
	u8 sta_id = addsta->sta.sta_id;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EIO;

	अगर (pkt->hdr.flags & IL_CMD_FAILED_MSK) अणु
		IL_ERR("Bad return from C_ADD_STA (0x%08X)\n", pkt->hdr.flags);
		वापस ret;
	पूर्ण

	D_INFO("Processing response for adding station %u\n", sta_id);

	spin_lock_irqsave(&il->sta_lock, flags);

	चयन (pkt->u.add_sta.status) अणु
	हाल ADD_STA_SUCCESS_MSK:
		D_INFO("C_ADD_STA PASSED\n");
		il_sta_ucode_activate(il, sta_id);
		ret = 0;
		अवरोध;
	हाल ADD_STA_NO_ROOM_IN_TBL:
		IL_ERR("Adding station %d failed, no room in table.\n", sta_id);
		अवरोध;
	हाल ADD_STA_NO_BLOCK_ACK_RESOURCE:
		IL_ERR("Adding station %d failed, no block ack resource.\n",
		       sta_id);
		अवरोध;
	हाल ADD_STA_MODIFY_NON_EXIST_STA:
		IL_ERR("Attempting to modify non-existing station %d\n",
		       sta_id);
		अवरोध;
	शेष:
		D_ASSOC("Received C_ADD_STA:(0x%08X)\n", pkt->u.add_sta.status);
		अवरोध;
	पूर्ण

	D_INFO("%s station id %u addr %pM\n",
	       il->stations[sta_id].sta.mode ==
	       STA_CONTROL_MODIFY_MSK ? "Modified" : "Added", sta_id,
	       il->stations[sta_id].sta.sta.addr);

	/*
	 * XXX: The MAC address in the command buffer is often changed from
	 * the original sent to the device. That is, the MAC address
	 * written to the command buffer often is not the same MAC address
	 * पढ़ो from the command buffer when the command वापसs. This
	 * issue has not yet been resolved and this debugging is left to
	 * observe the problem.
	 */
	D_INFO("%s station according to cmd buffer %pM\n",
	       il->stations[sta_id].sta.mode ==
	       STA_CONTROL_MODIFY_MSK ? "Modified" : "Added", addsta->sta.addr);
	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम
il_add_sta_callback(काष्ठा il_priv *il, काष्ठा il_device_cmd *cmd,
		    काष्ठा il_rx_pkt *pkt)
अणु
	काष्ठा il_addsta_cmd *addsta = (काष्ठा il_addsta_cmd *)cmd->cmd.payload;

	il_process_add_sta_resp(il, addsta, pkt, false);

पूर्ण

पूर्णांक
il_send_add_sta(काष्ठा il_priv *il, काष्ठा il_addsta_cmd *sta, u8 flags)
अणु
	काष्ठा il_rx_pkt *pkt = शून्य;
	पूर्णांक ret = 0;
	u8 data[माप(*sta)];
	काष्ठा il_host_cmd cmd = अणु
		.id = C_ADD_STA,
		.flags = flags,
		.data = data,
	पूर्ण;
	u8 sta_id __maybe_unused = sta->sta.sta_id;

	D_INFO("Adding sta %u (%pM) %ssynchronously\n", sta_id, sta->sta.addr,
	       flags & CMD_ASYNC ? "a" : "");

	अगर (flags & CMD_ASYNC)
		cmd.callback = il_add_sta_callback;
	अन्यथा अणु
		cmd.flags |= CMD_WANT_SKB;
		might_sleep();
	पूर्ण

	cmd.len = il->ops->build_addsta_hcmd(sta, data);
	ret = il_send_cmd(il, &cmd);
	अगर (ret)
		वापस ret;
	अगर (flags & CMD_ASYNC)
		वापस 0;

	pkt = (काष्ठा il_rx_pkt *)cmd.reply_page;
	ret = il_process_add_sta_resp(il, sta, pkt, true);

	il_मुक्त_pages(il, cmd.reply_page);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(il_send_add_sta);

अटल व्योम
il_set_ht_add_station(काष्ठा il_priv *il, u8 idx, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_sta_ht_cap *sta_ht_inf = &sta->ht_cap;
	__le32 sta_flags;

	अगर (!sta || !sta_ht_inf->ht_supported)
		जाओ करोne;

	D_ASSOC("spatial multiplexing power save mode: %s\n",
		(sta->smps_mode == IEEE80211_SMPS_STATIC) ? "static" :
		(sta->smps_mode == IEEE80211_SMPS_DYNAMIC) ? "dynamic" :
		"disabled");

	sta_flags = il->stations[idx].sta.station_flags;

	sta_flags &= ~(STA_FLG_RTS_MIMO_PROT_MSK | STA_FLG_MIMO_DIS_MSK);

	चयन (sta->smps_mode) अणु
	हाल IEEE80211_SMPS_STATIC:
		sta_flags |= STA_FLG_MIMO_DIS_MSK;
		अवरोध;
	हाल IEEE80211_SMPS_DYNAMIC:
		sta_flags |= STA_FLG_RTS_MIMO_PROT_MSK;
		अवरोध;
	हाल IEEE80211_SMPS_OFF:
		अवरोध;
	शेष:
		IL_WARN("Invalid MIMO PS mode %d\n", sta->smps_mode);
		अवरोध;
	पूर्ण

	sta_flags |=
	    cpu_to_le32((u32) sta_ht_inf->
			ampdu_factor << STA_FLG_MAX_AGG_SIZE_POS);

	sta_flags |=
	    cpu_to_le32((u32) sta_ht_inf->
			ampdu_density << STA_FLG_AGG_MPDU_DENSITY_POS);

	अगर (il_is_ht40_tx_allowed(il, &sta->ht_cap))
		sta_flags |= STA_FLG_HT40_EN_MSK;
	अन्यथा
		sta_flags &= ~STA_FLG_HT40_EN_MSK;

	il->stations[idx].sta.station_flags = sta_flags;
करोne:
	वापस;
पूर्ण

/*
 * il_prep_station - Prepare station inक्रमmation क्रम addition
 *
 * should be called with sta_lock held
 */
u8
il_prep_station(काष्ठा il_priv *il, स्थिर u8 *addr, bool is_ap,
		काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा il_station_entry *station;
	पूर्णांक i;
	u8 sta_id = IL_INVALID_STATION;
	u16 rate;

	अगर (is_ap)
		sta_id = IL_AP_ID;
	अन्यथा अगर (is_broadcast_ether_addr(addr))
		sta_id = il->hw_params.bcast_id;
	अन्यथा
		क्रम (i = IL_STA_ID; i < il->hw_params.max_stations; i++) अणु
			अगर (ether_addr_equal(il->stations[i].sta.sta.addr,
					     addr)) अणु
				sta_id = i;
				अवरोध;
			पूर्ण

			अगर (!il->stations[i].used &&
			    sta_id == IL_INVALID_STATION)
				sta_id = i;
		पूर्ण

	/*
	 * These two conditions have the same outcome, but keep them
	 * separate
	 */
	अगर (unlikely(sta_id == IL_INVALID_STATION))
		वापस sta_id;

	/*
	 * uCode is not able to deal with multiple requests to add a
	 * station. Keep track अगर one is in progress so that we करो not send
	 * another.
	 */
	अगर (il->stations[sta_id].used & IL_STA_UCODE_INPROGRESS) अणु
		D_INFO("STA %d already in process of being added.\n", sta_id);
		वापस sta_id;
	पूर्ण

	अगर ((il->stations[sta_id].used & IL_STA_DRIVER_ACTIVE) &&
	    (il->stations[sta_id].used & IL_STA_UCODE_ACTIVE) &&
	    ether_addr_equal(il->stations[sta_id].sta.sta.addr, addr)) अणु
		D_ASSOC("STA %d (%pM) already added, not adding again.\n",
			sta_id, addr);
		वापस sta_id;
	पूर्ण

	station = &il->stations[sta_id];
	station->used = IL_STA_DRIVER_ACTIVE;
	D_ASSOC("Add STA to driver ID %d: %pM\n", sta_id, addr);
	il->num_stations++;

	/* Set up the C_ADD_STA command to send to device */
	स_रखो(&station->sta, 0, माप(काष्ठा il_addsta_cmd));
	स_नकल(station->sta.sta.addr, addr, ETH_ALEN);
	station->sta.mode = 0;
	station->sta.sta.sta_id = sta_id;
	station->sta.station_flags = 0;

	/*
	 * OK to call unconditionally, since local stations (IBSS BSSID
	 * STA and broadcast STA) pass in a शून्य sta, and mac80211
	 * करोesn't allow HT IBSS.
	 */
	il_set_ht_add_station(il, sta_id, sta);

	/* 3945 only */
	rate = (il->band == NL80211_BAND_5GHZ) ? RATE_6M_PLCP : RATE_1M_PLCP;
	/* Turn on both antennas क्रम the station... */
	station->sta.rate_n_flags = cpu_to_le16(rate | RATE_MCS_ANT_AB_MSK);

	वापस sta_id;

पूर्ण
EXPORT_SYMBOL_GPL(il_prep_station);

#घोषणा STA_WAIT_TIMEOUT (HZ/2)

/*
 * il_add_station_common -
 */
पूर्णांक
il_add_station_common(काष्ठा il_priv *il, स्थिर u8 *addr, bool is_ap,
		      काष्ठा ieee80211_sta *sta, u8 *sta_id_r)
अणु
	अचिन्हित दीर्घ flags_spin;
	पूर्णांक ret = 0;
	u8 sta_id;
	काष्ठा il_addsta_cmd sta_cmd;

	*sta_id_r = 0;
	spin_lock_irqsave(&il->sta_lock, flags_spin);
	sta_id = il_prep_station(il, addr, is_ap, sta);
	अगर (sta_id == IL_INVALID_STATION) अणु
		IL_ERR("Unable to prepare station %pM for addition\n", addr);
		spin_unlock_irqrestore(&il->sta_lock, flags_spin);
		वापस -EINVAL;
	पूर्ण

	/*
	 * uCode is not able to deal with multiple requests to add a
	 * station. Keep track अगर one is in progress so that we करो not send
	 * another.
	 */
	अगर (il->stations[sta_id].used & IL_STA_UCODE_INPROGRESS) अणु
		D_INFO("STA %d already in process of being added.\n", sta_id);
		spin_unlock_irqrestore(&il->sta_lock, flags_spin);
		वापस -EEXIST;
	पूर्ण

	अगर ((il->stations[sta_id].used & IL_STA_DRIVER_ACTIVE) &&
	    (il->stations[sta_id].used & IL_STA_UCODE_ACTIVE)) अणु
		D_ASSOC("STA %d (%pM) already added, not adding again.\n",
			sta_id, addr);
		spin_unlock_irqrestore(&il->sta_lock, flags_spin);
		वापस -EEXIST;
	पूर्ण

	il->stations[sta_id].used |= IL_STA_UCODE_INPROGRESS;
	स_नकल(&sta_cmd, &il->stations[sta_id].sta,
	       माप(काष्ठा il_addsta_cmd));
	spin_unlock_irqrestore(&il->sta_lock, flags_spin);

	/* Add station to device's station table */
	ret = il_send_add_sta(il, &sta_cmd, CMD_SYNC);
	अगर (ret) अणु
		spin_lock_irqsave(&il->sta_lock, flags_spin);
		IL_ERR("Adding station %pM failed.\n",
		       il->stations[sta_id].sta.sta.addr);
		il->stations[sta_id].used &= ~IL_STA_DRIVER_ACTIVE;
		il->stations[sta_id].used &= ~IL_STA_UCODE_INPROGRESS;
		spin_unlock_irqrestore(&il->sta_lock, flags_spin);
	पूर्ण
	*sta_id_r = sta_id;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(il_add_station_common);

/*
 * il_sta_ucode_deactivate - deactivate ucode status क्रम a station
 *
 * il->sta_lock must be held
 */
अटल व्योम
il_sta_ucode_deactivate(काष्ठा il_priv *il, u8 sta_id)
अणु
	/* Ucode must be active and driver must be non active */
	अगर ((il->stations[sta_id].
	     used & (IL_STA_UCODE_ACTIVE | IL_STA_DRIVER_ACTIVE)) !=
	    IL_STA_UCODE_ACTIVE)
		IL_ERR("removed non active STA %u\n", sta_id);

	il->stations[sta_id].used &= ~IL_STA_UCODE_ACTIVE;

	स_रखो(&il->stations[sta_id], 0, माप(काष्ठा il_station_entry));
	D_ASSOC("Removed STA %u\n", sta_id);
पूर्ण

अटल पूर्णांक
il_send_हटाओ_station(काष्ठा il_priv *il, स्थिर u8 * addr, पूर्णांक sta_id,
		       bool temporary)
अणु
	काष्ठा il_rx_pkt *pkt;
	पूर्णांक ret;

	अचिन्हित दीर्घ flags_spin;
	काष्ठा il_rem_sta_cmd rm_sta_cmd;

	काष्ठा il_host_cmd cmd = अणु
		.id = C_REM_STA,
		.len = माप(काष्ठा il_rem_sta_cmd),
		.flags = CMD_SYNC,
		.data = &rm_sta_cmd,
	पूर्ण;

	स_रखो(&rm_sta_cmd, 0, माप(rm_sta_cmd));
	rm_sta_cmd.num_sta = 1;
	स_नकल(&rm_sta_cmd.addr, addr, ETH_ALEN);

	cmd.flags |= CMD_WANT_SKB;

	ret = il_send_cmd(il, &cmd);

	अगर (ret)
		वापस ret;

	pkt = (काष्ठा il_rx_pkt *)cmd.reply_page;
	अगर (pkt->hdr.flags & IL_CMD_FAILED_MSK) अणु
		IL_ERR("Bad return from C_REM_STA (0x%08X)\n", pkt->hdr.flags);
		ret = -EIO;
	पूर्ण

	अगर (!ret) अणु
		चयन (pkt->u.rem_sta.status) अणु
		हाल REM_STA_SUCCESS_MSK:
			अगर (!temporary) अणु
				spin_lock_irqsave(&il->sta_lock, flags_spin);
				il_sta_ucode_deactivate(il, sta_id);
				spin_unlock_irqrestore(&il->sta_lock,
						       flags_spin);
			पूर्ण
			D_ASSOC("C_REM_STA PASSED\n");
			अवरोध;
		शेष:
			ret = -EIO;
			IL_ERR("C_REM_STA failed\n");
			अवरोध;
		पूर्ण
	पूर्ण
	il_मुक्त_pages(il, cmd.reply_page);

	वापस ret;
पूर्ण

/*
 * il_हटाओ_station - Remove driver's knowledge of station.
 */
पूर्णांक
il_हटाओ_station(काष्ठा il_priv *il, स्थिर u8 sta_id, स्थिर u8 * addr)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!il_is_पढ़ोy(il)) अणु
		D_INFO("Unable to remove station %pM, device not ready.\n",
		       addr);
		/*
		 * It is typical क्रम stations to be हटाओd when we are
		 * going करोwn. Return success since device will be करोwn
		 * soon anyway
		 */
		वापस 0;
	पूर्ण

	D_ASSOC("Removing STA from driver:%d  %pM\n", sta_id, addr);

	अगर (WARN_ON(sta_id == IL_INVALID_STATION))
		वापस -EINVAL;

	spin_lock_irqsave(&il->sta_lock, flags);

	अगर (!(il->stations[sta_id].used & IL_STA_DRIVER_ACTIVE)) अणु
		D_INFO("Removing %pM but non DRIVER active\n", addr);
		जाओ out_err;
	पूर्ण

	अगर (!(il->stations[sta_id].used & IL_STA_UCODE_ACTIVE)) अणु
		D_INFO("Removing %pM but non UCODE active\n", addr);
		जाओ out_err;
	पूर्ण

	अगर (il->stations[sta_id].used & IL_STA_LOCAL) अणु
		kमुक्त(il->stations[sta_id].lq);
		il->stations[sta_id].lq = शून्य;
	पूर्ण

	il->stations[sta_id].used &= ~IL_STA_DRIVER_ACTIVE;

	il->num_stations--;

	BUG_ON(il->num_stations < 0);

	spin_unlock_irqrestore(&il->sta_lock, flags);

	वापस il_send_हटाओ_station(il, addr, sta_id, false);
out_err:
	spin_unlock_irqrestore(&il->sta_lock, flags);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(il_हटाओ_station);

/*
 * il_clear_ucode_stations - clear ucode station table bits
 *
 * This function clears all the bits in the driver indicating
 * which stations are active in the ucode. Call when something
 * other than explicit station management would cause this in
 * the ucode, e.g. unassociated RXON.
 */
व्योम
il_clear_ucode_stations(काष्ठा il_priv *il)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags_spin;
	bool cleared = false;

	D_INFO("Clearing ucode stations in driver\n");

	spin_lock_irqsave(&il->sta_lock, flags_spin);
	क्रम (i = 0; i < il->hw_params.max_stations; i++) अणु
		अगर (il->stations[i].used & IL_STA_UCODE_ACTIVE) अणु
			D_INFO("Clearing ucode active for station %d\n", i);
			il->stations[i].used &= ~IL_STA_UCODE_ACTIVE;
			cleared = true;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&il->sta_lock, flags_spin);

	अगर (!cleared)
		D_INFO("No active stations found to be cleared\n");
पूर्ण
EXPORT_SYMBOL(il_clear_ucode_stations);

/*
 * il_restore_stations() - Restore driver known stations to device
 *
 * All stations considered active by driver, but not present in ucode, is
 * restored.
 *
 * Function sleeps.
 */
व्योम
il_restore_stations(काष्ठा il_priv *il)
अणु
	काष्ठा il_addsta_cmd sta_cmd;
	काष्ठा il_link_quality_cmd lq;
	अचिन्हित दीर्घ flags_spin;
	पूर्णांक i;
	bool found = false;
	पूर्णांक ret;
	bool send_lq;

	अगर (!il_is_पढ़ोy(il)) अणु
		D_INFO("Not ready yet, not restoring any stations.\n");
		वापस;
	पूर्ण

	D_ASSOC("Restoring all known stations ... start.\n");
	spin_lock_irqsave(&il->sta_lock, flags_spin);
	क्रम (i = 0; i < il->hw_params.max_stations; i++) अणु
		अगर ((il->stations[i].used & IL_STA_DRIVER_ACTIVE) &&
		    !(il->stations[i].used & IL_STA_UCODE_ACTIVE)) अणु
			D_ASSOC("Restoring sta %pM\n",
				il->stations[i].sta.sta.addr);
			il->stations[i].sta.mode = 0;
			il->stations[i].used |= IL_STA_UCODE_INPROGRESS;
			found = true;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < il->hw_params.max_stations; i++) अणु
		अगर ((il->stations[i].used & IL_STA_UCODE_INPROGRESS)) अणु
			स_नकल(&sta_cmd, &il->stations[i].sta,
			       माप(काष्ठा il_addsta_cmd));
			send_lq = false;
			अगर (il->stations[i].lq) अणु
				स_नकल(&lq, il->stations[i].lq,
				       माप(काष्ठा il_link_quality_cmd));
				send_lq = true;
			पूर्ण
			spin_unlock_irqrestore(&il->sta_lock, flags_spin);
			ret = il_send_add_sta(il, &sta_cmd, CMD_SYNC);
			अगर (ret) अणु
				spin_lock_irqsave(&il->sta_lock, flags_spin);
				IL_ERR("Adding station %pM failed.\n",
				       il->stations[i].sta.sta.addr);
				il->stations[i].used &= ~IL_STA_DRIVER_ACTIVE;
				il->stations[i].used &=
				    ~IL_STA_UCODE_INPROGRESS;
				spin_unlock_irqrestore(&il->sta_lock,
						       flags_spin);
			पूर्ण
			/*
			 * Rate scaling has alपढ़ोy been initialized, send
			 * current LQ command
			 */
			अगर (send_lq)
				il_send_lq_cmd(il, &lq, CMD_SYNC, true);
			spin_lock_irqsave(&il->sta_lock, flags_spin);
			il->stations[i].used &= ~IL_STA_UCODE_INPROGRESS;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&il->sta_lock, flags_spin);
	अगर (!found)
		D_INFO("Restoring all known stations"
		       " .... no stations to be restored.\n");
	अन्यथा
		D_INFO("Restoring all known stations" " .... complete.\n");
पूर्ण
EXPORT_SYMBOL(il_restore_stations);

पूर्णांक
il_get_मुक्त_ucode_key_idx(काष्ठा il_priv *il)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < il->sta_key_max_num; i++)
		अगर (!test_and_set_bit(i, &il->ucode_key_table))
			वापस i;

	वापस WEP_INVALID_OFFSET;
पूर्ण
EXPORT_SYMBOL(il_get_मुक्त_ucode_key_idx);

व्योम
il_dealloc_bcast_stations(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&il->sta_lock, flags);
	क्रम (i = 0; i < il->hw_params.max_stations; i++) अणु
		अगर (!(il->stations[i].used & IL_STA_BCAST))
			जारी;

		il->stations[i].used &= ~IL_STA_UCODE_ACTIVE;
		il->num_stations--;
		BUG_ON(il->num_stations < 0);
		kमुक्त(il->stations[i].lq);
		il->stations[i].lq = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&il->sta_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(il_dealloc_bcast_stations);

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
अटल व्योम
il_dump_lq_cmd(काष्ठा il_priv *il, काष्ठा il_link_quality_cmd *lq)
अणु
	पूर्णांक i;
	D_RATE("lq station id 0x%x\n", lq->sta_id);
	D_RATE("lq ant 0x%X 0x%X\n", lq->general_params.single_stream_ant_msk,
	       lq->general_params.dual_stream_ant_msk);

	क्रम (i = 0; i < LINK_QUAL_MAX_RETRY_NUM; i++)
		D_RATE("lq idx %d 0x%X\n", i, lq->rs_table[i].rate_n_flags);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
il_dump_lq_cmd(काष्ठा il_priv *il, काष्ठा il_link_quality_cmd *lq)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * il_is_lq_table_valid() - Test one aspect of LQ cmd क्रम validity
 *
 * It someबार happens when a HT rate has been in use and we
 * loose connectivity with AP then mac80211 will first tell us that the
 * current channel is not HT anymore beक्रमe removing the station. In such a
 * scenario the RXON flags will be updated to indicate we are not
 * communicating HT anymore, but the LQ command may still contain HT rates.
 * Test क्रम this to prevent driver from sending LQ command between the समय
 * RXON flags are updated and when LQ command is updated.
 */
अटल bool
il_is_lq_table_valid(काष्ठा il_priv *il, काष्ठा il_link_quality_cmd *lq)
अणु
	पूर्णांक i;

	अगर (il->ht.enabled)
		वापस true;

	D_INFO("Channel %u is not an HT channel\n", il->active.channel);
	क्रम (i = 0; i < LINK_QUAL_MAX_RETRY_NUM; i++) अणु
		अगर (le32_to_cpu(lq->rs_table[i].rate_n_flags) & RATE_MCS_HT_MSK) अणु
			D_INFO("idx %d of LQ expects HT channel\n", i);
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

/*
 * il_send_lq_cmd() - Send link quality command
 * @init: This command is sent as part of station initialization right
 *        after station has been added.
 *
 * The link quality command is sent as the last step of station creation.
 * This is the special हाल in which init is set and we call a callback in
 * this हाल to clear the state indicating that station creation is in
 * progress.
 */
पूर्णांक
il_send_lq_cmd(काष्ठा il_priv *il, काष्ठा il_link_quality_cmd *lq,
	       u8 flags, bool init)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags_spin;

	काष्ठा il_host_cmd cmd = अणु
		.id = C_TX_LINK_QUALITY_CMD,
		.len = माप(काष्ठा il_link_quality_cmd),
		.flags = flags,
		.data = lq,
	पूर्ण;

	अगर (WARN_ON(lq->sta_id == IL_INVALID_STATION))
		वापस -EINVAL;

	spin_lock_irqsave(&il->sta_lock, flags_spin);
	अगर (!(il->stations[lq->sta_id].used & IL_STA_DRIVER_ACTIVE)) अणु
		spin_unlock_irqrestore(&il->sta_lock, flags_spin);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_irqrestore(&il->sta_lock, flags_spin);

	il_dump_lq_cmd(il, lq);
	BUG_ON(init && (cmd.flags & CMD_ASYNC));

	अगर (il_is_lq_table_valid(il, lq))
		ret = il_send_cmd(il, &cmd);
	अन्यथा
		ret = -EINVAL;

	अगर (cmd.flags & CMD_ASYNC)
		वापस ret;

	अगर (init) अणु
		D_INFO("init LQ command complete,"
		       " clearing sta addition status for sta %d\n",
		       lq->sta_id);
		spin_lock_irqsave(&il->sta_lock, flags_spin);
		il->stations[lq->sta_id].used &= ~IL_STA_UCODE_INPROGRESS;
		spin_unlock_irqrestore(&il->sta_lock, flags_spin);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(il_send_lq_cmd);

पूर्णांक
il_mac_sta_हटाओ(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा il_priv *il = hw->priv;
	काष्ठा il_station_priv_common *sta_common = (व्योम *)sta->drv_priv;
	पूर्णांक ret;

	mutex_lock(&il->mutex);
	D_MAC80211("enter station %pM\n", sta->addr);

	ret = il_हटाओ_station(il, sta_common->sta_id, sta->addr);
	अगर (ret)
		IL_ERR("Error removing station %pM\n", sta->addr);

	D_MAC80211("leave ret %d\n", ret);
	mutex_unlock(&il->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(il_mac_sta_हटाओ);

/************************** RX-FUNCTIONS ****************************/
/*
 * Rx theory of operation
 *
 * Driver allocates a circular buffer of Receive Buffer Descriptors (RBDs),
 * each of which poपूर्णांक to Receive Buffers to be filled by the NIC.  These get
 * used not only क्रम Rx frames, but क्रम any command response or notअगरication
 * from the NIC.  The driver and NIC manage the Rx buffers by means
 * of idxes पूर्णांकo the circular buffer.
 *
 * Rx Queue Indexes
 * The host/firmware share two idx रेजिस्टरs क्रम managing the Rx buffers.
 *
 * The READ idx maps to the first position that the firmware may be writing
 * to -- the driver can पढ़ो up to (but not including) this position and get
 * good data.
 * The READ idx is managed by the firmware once the card is enabled.
 *
 * The WRITE idx maps to the last position the driver has पढ़ो from -- the
 * position preceding WRITE is the last slot the firmware can place a packet.
 *
 * The queue is empty (no good data) अगर WRITE = READ - 1, and is full अगर
 * WRITE = READ.
 *
 * During initialization, the host sets up the READ queue position to the first
 * IDX position, and WRITE to the last (READ - 1 wrapped)
 *
 * When the firmware places a packet in a buffer, it will advance the READ idx
 * and fire the RX पूर्णांकerrupt.  The driver can then query the READ idx and
 * process as many packets as possible, moving the WRITE idx क्रमward as it
 * resets the Rx queue buffers with new memory.
 *
 * The management in the driver is as follows:
 * + A list of pre-allocated SKBs is stored in iwl->rxq->rx_मुक्त.  When
 *   iwl->rxq->मुक्त_count drops to or below RX_LOW_WATERMARK, work is scheduled
 *   to replenish the iwl->rxq->rx_मुक्त.
 * + In il_rx_replenish (scheduled) अगर 'processed' != 'read' then the
 *   iwl->rxq is replenished and the READ IDX is updated (updating the
 *   'processed' and 'read' driver idxes as well)
 * + A received packet is processed and handed to the kernel network stack,
 *   detached from the iwl->rxq.  The driver 'processed' idx is updated.
 * + The Host/Firmware iwl->rxq is replenished at tasklet समय from the rx_मुक्त
 *   list. If there are no allocated buffers in iwl->rxq->rx_मुक्त, the READ
 *   IDX is not incremented and iwl->status(RX_STALLED) is set.  If there
 *   were enough मुक्त buffers and RX_STALLED is set it is cleared.
 *
 *
 * Driver sequence:
 *
 * il_rx_queue_alloc()   Allocates rx_मुक्त
 * il_rx_replenish()     Replenishes rx_मुक्त list from rx_used, and calls
 *                            il_rx_queue_restock
 * il_rx_queue_restock() Moves available buffers from rx_मुक्त पूर्णांकo Rx
 *                            queue, updates firmware poपूर्णांकers, and updates
 *                            the WRITE idx.  If insufficient rx_मुक्त buffers
 *                            are available, schedules il_rx_replenish
 *
 * -- enable पूर्णांकerrupts --
 * ISR - il_rx()         Detach il_rx_bufs from pool up to the
 *                            READ IDX, detaching the SKB from the pool.
 *                            Moves the packet buffer from queue to rx_used.
 *                            Calls il_rx_queue_restock to refill any empty
 *                            slots.
 * ...
 *
 */

/*
 * il_rx_queue_space - Return number of मुक्त slots available in queue.
 */
पूर्णांक
il_rx_queue_space(स्थिर काष्ठा il_rx_queue *q)
अणु
	पूर्णांक s = q->पढ़ो - q->ग_लिखो;
	अगर (s <= 0)
		s += RX_QUEUE_SIZE;
	/* keep some buffer to not confuse full and empty queue */
	s -= 2;
	अगर (s < 0)
		s = 0;
	वापस s;
पूर्ण
EXPORT_SYMBOL(il_rx_queue_space);

/*
 * il_rx_queue_update_ग_लिखो_ptr - Update the ग_लिखो poपूर्णांकer क्रम the RX queue
 */
व्योम
il_rx_queue_update_ग_लिखो_ptr(काष्ठा il_priv *il, काष्ठा il_rx_queue *q)
अणु
	अचिन्हित दीर्घ flags;
	u32 rx_wrt_ptr_reg = il->hw_params.rx_wrt_ptr_reg;
	u32 reg;

	spin_lock_irqsave(&q->lock, flags);

	अगर (q->need_update == 0)
		जाओ निकास_unlock;

	/* If घातer-saving is in use, make sure device is awake */
	अगर (test_bit(S_POWER_PMI, &il->status)) अणु
		reg = _il_rd(il, CSR_UCODE_DRV_GP1);

		अगर (reg & CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP) अणु
			D_INFO("Rx queue requesting wakeup," " GP1 = 0x%x\n",
			       reg);
			il_set_bit(il, CSR_GP_CNTRL,
				   CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
			जाओ निकास_unlock;
		पूर्ण

		q->ग_लिखो_actual = (q->ग_लिखो & ~0x7);
		il_wr(il, rx_wrt_ptr_reg, q->ग_लिखो_actual);

		/* Else device is assumed to be awake */
	पूर्ण अन्यथा अणु
		/* Device expects a multiple of 8 */
		q->ग_लिखो_actual = (q->ग_लिखो & ~0x7);
		il_wr(il, rx_wrt_ptr_reg, q->ग_लिखो_actual);
	पूर्ण

	q->need_update = 0;

निकास_unlock:
	spin_unlock_irqrestore(&q->lock, flags);
पूर्ण
EXPORT_SYMBOL(il_rx_queue_update_ग_लिखो_ptr);

पूर्णांक
il_rx_queue_alloc(काष्ठा il_priv *il)
अणु
	काष्ठा il_rx_queue *rxq = &il->rxq;
	काष्ठा device *dev = &il->pci_dev->dev;
	पूर्णांक i;

	spin_lock_init(&rxq->lock);
	INIT_LIST_HEAD(&rxq->rx_मुक्त);
	INIT_LIST_HEAD(&rxq->rx_used);

	/* Alloc the circular buffer of Read Buffer Descriptors (RBDs) */
	rxq->bd = dma_alloc_coherent(dev, 4 * RX_QUEUE_SIZE, &rxq->bd_dma,
				     GFP_KERNEL);
	अगर (!rxq->bd)
		जाओ err_bd;

	rxq->rb_stts = dma_alloc_coherent(dev, माप(काष्ठा il_rb_status),
					  &rxq->rb_stts_dma, GFP_KERNEL);
	अगर (!rxq->rb_stts)
		जाओ err_rb;

	/* Fill the rx_used queue with _all_ of the Rx buffers */
	क्रम (i = 0; i < RX_FREE_BUFFERS + RX_QUEUE_SIZE; i++)
		list_add_tail(&rxq->pool[i].list, &rxq->rx_used);

	/* Set us so that we have processed and used all buffers, but have
	 * not restocked the Rx queue with fresh buffers */
	rxq->पढ़ो = rxq->ग_लिखो = 0;
	rxq->ग_लिखो_actual = 0;
	rxq->मुक्त_count = 0;
	rxq->need_update = 0;
	वापस 0;

err_rb:
	dma_मुक्त_coherent(&il->pci_dev->dev, 4 * RX_QUEUE_SIZE, rxq->bd,
			  rxq->bd_dma);
err_bd:
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(il_rx_queue_alloc);

व्योम
il_hdl_spectrum_measurement(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_spectrum_notअगरication *report = &(pkt->u.spectrum_notअगर);

	अगर (!report->state) अणु
		D_11H("Spectrum Measure Notification: Start\n");
		वापस;
	पूर्ण

	स_नकल(&il->measure_report, report, माप(*report));
	il->measurement_status |= MEASUREMENT_READY;
पूर्ण
EXPORT_SYMBOL(il_hdl_spectrum_measurement);

/*
 * वापसs non-zero अगर packet should be dropped
 */
पूर्णांक
il_set_decrypted_flag(काष्ठा il_priv *il, काष्ठा ieee80211_hdr *hdr,
		      u32 decrypt_res, काष्ठा ieee80211_rx_status *stats)
अणु
	u16 fc = le16_to_cpu(hdr->frame_control);

	/*
	 * All contexts have the same setting here due to it being
	 * a module parameter, so OK to check any context.
	 */
	अगर (il->active.filter_flags & RXON_FILTER_DIS_DECRYPT_MSK)
		वापस 0;

	अगर (!(fc & IEEE80211_FCTL_PROTECTED))
		वापस 0;

	D_RX("decrypt_res:0x%x\n", decrypt_res);
	चयन (decrypt_res & RX_RES_STATUS_SEC_TYPE_MSK) अणु
	हाल RX_RES_STATUS_SEC_TYPE_TKIP:
		/* The uCode has got a bad phase 1 Key, pushes the packet.
		 * Decryption will be करोne in SW. */
		अगर ((decrypt_res & RX_RES_STATUS_DECRYPT_TYPE_MSK) ==
		    RX_RES_STATUS_BAD_KEY_TTAK)
			अवरोध;
		fallthrough;

	हाल RX_RES_STATUS_SEC_TYPE_WEP:
		अगर ((decrypt_res & RX_RES_STATUS_DECRYPT_TYPE_MSK) ==
		    RX_RES_STATUS_BAD_ICV_MIC) अणु
			/* bad ICV, the packet is destroyed since the
			 * decryption is inplace, drop it */
			D_RX("Packet destroyed\n");
			वापस -1;
		पूर्ण
		fallthrough;
	हाल RX_RES_STATUS_SEC_TYPE_CCMP:
		अगर ((decrypt_res & RX_RES_STATUS_DECRYPT_TYPE_MSK) ==
		    RX_RES_STATUS_DECRYPT_OK) अणु
			D_RX("hw decrypt successfully!!!\n");
			stats->flag |= RX_FLAG_DECRYPTED;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(il_set_decrypted_flag);

/*
 * il_txq_update_ग_लिखो_ptr - Send new ग_लिखो idx to hardware
 */
व्योम
il_txq_update_ग_लिखो_ptr(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq)
अणु
	u32 reg = 0;
	पूर्णांक txq_id = txq->q.id;

	अगर (txq->need_update == 0)
		वापस;

	/* अगर we're trying to save घातer */
	अगर (test_bit(S_POWER_PMI, &il->status)) अणु
		/* wake up nic अगर it's घातered करोwn ...
		 * uCode will wake up, and पूर्णांकerrupt us again, so next
		 * समय we'll skip this part. */
		reg = _il_rd(il, CSR_UCODE_DRV_GP1);

		अगर (reg & CSR_UCODE_DRV_GP1_BIT_MAC_SLEEP) अणु
			D_INFO("Tx queue %d requesting wakeup," " GP1 = 0x%x\n",
			       txq_id, reg);
			il_set_bit(il, CSR_GP_CNTRL,
				   CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
			वापस;
		पूर्ण

		il_wr(il, HBUS_TARG_WRPTR, txq->q.ग_लिखो_ptr | (txq_id << 8));

		/*
		 * अन्यथा not in घातer-save mode,
		 * uCode will never sleep when we're
		 * trying to tx (during RFKILL, we're not trying to tx).
		 */
	पूर्ण अन्यथा
		_il_wr(il, HBUS_TARG_WRPTR, txq->q.ग_लिखो_ptr | (txq_id << 8));
	txq->need_update = 0;
पूर्ण
EXPORT_SYMBOL(il_txq_update_ग_लिखो_ptr);

/*
 * il_tx_queue_unmap -  Unmap any reमुख्यing DMA mappings and मुक्त skb's
 */
व्योम
il_tx_queue_unmap(काष्ठा il_priv *il, पूर्णांक txq_id)
अणु
	काष्ठा il_tx_queue *txq = &il->txq[txq_id];
	काष्ठा il_queue *q = &txq->q;

	अगर (q->n_bd == 0)
		वापस;

	जबतक (q->ग_लिखो_ptr != q->पढ़ो_ptr) अणु
		il->ops->txq_मुक्त_tfd(il, txq);
		q->पढ़ो_ptr = il_queue_inc_wrap(q->पढ़ो_ptr, q->n_bd);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(il_tx_queue_unmap);

/*
 * il_tx_queue_मुक्त - Deallocate DMA queue.
 * @txq: Transmit queue to deallocate.
 *
 * Empty queue by removing and destroying all BD's.
 * Free all buffers.
 * 0-fill, but करो not मुक्त "txq" descriptor काष्ठाure.
 */
व्योम
il_tx_queue_मुक्त(काष्ठा il_priv *il, पूर्णांक txq_id)
अणु
	काष्ठा il_tx_queue *txq = &il->txq[txq_id];
	काष्ठा device *dev = &il->pci_dev->dev;
	पूर्णांक i;

	il_tx_queue_unmap(il, txq_id);

	/* De-alloc array of command/tx buffers */
	अगर (txq->cmd) अणु
		क्रम (i = 0; i < TFD_TX_CMD_SLOTS; i++)
			kमुक्त(txq->cmd[i]);
	पूर्ण

	/* De-alloc circular buffer of TFDs */
	अगर (txq->q.n_bd)
		dma_मुक्त_coherent(dev, il->hw_params.tfd_size * txq->q.n_bd,
				  txq->tfds, txq->q.dma_addr);

	/* De-alloc array of per-TFD driver data */
	kमुक्त(txq->skbs);
	txq->skbs = शून्य;

	/* deallocate arrays */
	kमुक्त(txq->cmd);
	kमुक्त(txq->meta);
	txq->cmd = शून्य;
	txq->meta = शून्य;

	/* 0-fill queue descriptor काष्ठाure */
	स_रखो(txq, 0, माप(*txq));
पूर्ण
EXPORT_SYMBOL(il_tx_queue_मुक्त);

/*
 * il_cmd_queue_unmap - Unmap any reमुख्यing DMA mappings from command queue
 */
व्योम
il_cmd_queue_unmap(काष्ठा il_priv *il)
अणु
	काष्ठा il_tx_queue *txq = &il->txq[il->cmd_queue];
	काष्ठा il_queue *q = &txq->q;
	पूर्णांक i;

	अगर (q->n_bd == 0)
		वापस;

	जबतक (q->पढ़ो_ptr != q->ग_लिखो_ptr) अणु
		i = il_get_cmd_idx(q, q->पढ़ो_ptr, 0);

		अगर (txq->meta[i].flags & CMD_MAPPED) अणु
			pci_unmap_single(il->pci_dev,
					 dma_unmap_addr(&txq->meta[i], mapping),
					 dma_unmap_len(&txq->meta[i], len),
					 PCI_DMA_BIसूचीECTIONAL);
			txq->meta[i].flags = 0;
		पूर्ण

		q->पढ़ो_ptr = il_queue_inc_wrap(q->पढ़ो_ptr, q->n_bd);
	पूर्ण

	i = q->n_win;
	अगर (txq->meta[i].flags & CMD_MAPPED) अणु
		pci_unmap_single(il->pci_dev,
				 dma_unmap_addr(&txq->meta[i], mapping),
				 dma_unmap_len(&txq->meta[i], len),
				 PCI_DMA_BIसूचीECTIONAL);
		txq->meta[i].flags = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(il_cmd_queue_unmap);

/*
 * il_cmd_queue_मुक्त - Deallocate DMA queue.
 *
 * Empty queue by removing and destroying all BD's.
 * Free all buffers.
 * 0-fill, but करो not मुक्त "txq" descriptor काष्ठाure.
 */
व्योम
il_cmd_queue_मुक्त(काष्ठा il_priv *il)
अणु
	काष्ठा il_tx_queue *txq = &il->txq[il->cmd_queue];
	काष्ठा device *dev = &il->pci_dev->dev;
	पूर्णांक i;

	il_cmd_queue_unmap(il);

	/* De-alloc array of command/tx buffers */
	अगर (txq->cmd) अणु
		क्रम (i = 0; i <= TFD_CMD_SLOTS; i++)
			kमुक्त(txq->cmd[i]);
	पूर्ण

	/* De-alloc circular buffer of TFDs */
	अगर (txq->q.n_bd)
		dma_मुक्त_coherent(dev, il->hw_params.tfd_size * txq->q.n_bd,
				  txq->tfds, txq->q.dma_addr);

	/* deallocate arrays */
	kमुक्त(txq->cmd);
	kमुक्त(txq->meta);
	txq->cmd = शून्य;
	txq->meta = शून्य;

	/* 0-fill queue descriptor काष्ठाure */
	स_रखो(txq, 0, माप(*txq));
पूर्ण
EXPORT_SYMBOL(il_cmd_queue_मुक्त);

/*************** DMA-QUEUE-GENERAL-FUNCTIONS  *****
 * DMA services
 *
 * Theory of operation
 *
 * A Tx or Rx queue resides in host DRAM, and is comprised of a circular buffer
 * of buffer descriptors, each of which poपूर्णांकs to one or more data buffers क्रम
 * the device to पढ़ो from or fill.  Driver and device exchange status of each
 * queue via "read" and "write" poपूर्णांकers.  Driver keeps minimum of 2 empty
 * entries in each circular buffer, to protect against confusing empty and full
 * queue states.
 *
 * The device पढ़ोs or ग_लिखोs the data in the queues via the device's several
 * DMA/FIFO channels.  Each queue is mapped to a single DMA channel.
 *
 * For Tx queue, there are low mark and high mark limits. If, after queuing
 * the packet क्रम Tx, मुक्त space become < low mark, Tx queue stopped. When
 * reclaiming packets (on 'tx करोne IRQ), अगर मुक्त space become > high mark,
 * Tx queue resumed.
 *
 * See more detailed info in 4965.h.
 ***************************************************/

पूर्णांक
il_queue_space(स्थिर काष्ठा il_queue *q)
अणु
	पूर्णांक s = q->पढ़ो_ptr - q->ग_लिखो_ptr;

	अगर (q->पढ़ो_ptr > q->ग_लिखो_ptr)
		s -= q->n_bd;

	अगर (s <= 0)
		s += q->n_win;
	/* keep some reserve to not confuse empty and full situations */
	s -= 2;
	अगर (s < 0)
		s = 0;
	वापस s;
पूर्ण
EXPORT_SYMBOL(il_queue_space);


/*
 * il_queue_init - Initialize queue's high/low-water and पढ़ो/ग_लिखो idxes
 */
अटल पूर्णांक
il_queue_init(काष्ठा il_priv *il, काष्ठा il_queue *q, पूर्णांक slots, u32 id)
अणु
	/*
	 * TFD_QUEUE_SIZE_MAX must be घातer-of-two size, otherwise
	 * il_queue_inc_wrap and il_queue_dec_wrap are broken.
	 */
	BUILD_BUG_ON(TFD_QUEUE_SIZE_MAX & (TFD_QUEUE_SIZE_MAX - 1));
	/* FIXME: हटाओ q->n_bd */
	q->n_bd = TFD_QUEUE_SIZE_MAX;

	q->n_win = slots;
	q->id = id;

	/* slots_must be घातer-of-two size, otherwise
	 * il_get_cmd_idx is broken. */
	BUG_ON(!is_घातer_of_2(slots));

	q->low_mark = q->n_win / 4;
	अगर (q->low_mark < 4)
		q->low_mark = 4;

	q->high_mark = q->n_win / 8;
	अगर (q->high_mark < 2)
		q->high_mark = 2;

	q->ग_लिखो_ptr = q->पढ़ो_ptr = 0;

	वापस 0;
पूर्ण

/*
 * il_tx_queue_alloc - Alloc driver data and TFD CB क्रम one Tx/cmd queue
 */
अटल पूर्णांक
il_tx_queue_alloc(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq, u32 id)
अणु
	काष्ठा device *dev = &il->pci_dev->dev;
	माप_प्रकार tfd_sz = il->hw_params.tfd_size * TFD_QUEUE_SIZE_MAX;

	/* Driver ilate data, only क्रम Tx (not command) queues,
	 * not shared with device. */
	अगर (id != il->cmd_queue) अणु
		txq->skbs = kसुस्मृति(TFD_QUEUE_SIZE_MAX,
				    माप(काष्ठा sk_buff *),
				    GFP_KERNEL);
		अगर (!txq->skbs) अणु
			IL_ERR("Fail to alloc skbs\n");
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा
		txq->skbs = शून्य;

	/* Circular buffer of transmit frame descriptors (TFDs),
	 * shared with device */
	txq->tfds =
	    dma_alloc_coherent(dev, tfd_sz, &txq->q.dma_addr, GFP_KERNEL);
	अगर (!txq->tfds)
		जाओ error;

	txq->q.id = id;

	वापस 0;

error:
	kमुक्त(txq->skbs);
	txq->skbs = शून्य;

	वापस -ENOMEM;
पूर्ण

/*
 * il_tx_queue_init - Allocate and initialize one tx/cmd queue
 */
पूर्णांक
il_tx_queue_init(काष्ठा il_priv *il, u32 txq_id)
अणु
	पूर्णांक i, len, ret;
	पूर्णांक slots, actual_slots;
	काष्ठा il_tx_queue *txq = &il->txq[txq_id];

	/*
	 * Alloc buffer array क्रम commands (Tx or other types of commands).
	 * For the command queue (#4/#9), allocate command space + one big
	 * command क्रम scan, since scan command is very huge; the प्रणाली will
	 * not have two scans at the same समय, so only one is needed.
	 * For normal Tx queues (all other queues), no super-size command
	 * space is needed.
	 */
	अगर (txq_id == il->cmd_queue) अणु
		slots = TFD_CMD_SLOTS;
		actual_slots = slots + 1;
	पूर्ण अन्यथा अणु
		slots = TFD_TX_CMD_SLOTS;
		actual_slots = slots;
	पूर्ण

	txq->meta =
	    kसुस्मृति(actual_slots, माप(काष्ठा il_cmd_meta), GFP_KERNEL);
	txq->cmd =
	    kसुस्मृति(actual_slots, माप(काष्ठा il_device_cmd *), GFP_KERNEL);

	अगर (!txq->meta || !txq->cmd)
		जाओ out_मुक्त_arrays;

	len = माप(काष्ठा il_device_cmd);
	क्रम (i = 0; i < actual_slots; i++) अणु
		/* only happens क्रम cmd queue */
		अगर (i == slots)
			len = IL_MAX_CMD_SIZE;

		txq->cmd[i] = kदो_स्मृति(len, GFP_KERNEL);
		अगर (!txq->cmd[i])
			जाओ err;
	पूर्ण

	/* Alloc driver data array and TFD circular buffer */
	ret = il_tx_queue_alloc(il, txq, txq_id);
	अगर (ret)
		जाओ err;

	txq->need_update = 0;

	/*
	 * For the शेष queues 0-3, set up the swq_id
	 * alपढ़ोy -- all others need to get one later
	 * (अगर they need one at all).
	 */
	अगर (txq_id < 4)
		il_set_swq_id(txq, txq_id, txq_id);

	/* Initialize queue's high/low-water marks, and head/tail idxes */
	il_queue_init(il, &txq->q, slots, txq_id);

	/* Tell device where to find queue */
	il->ops->txq_init(il, txq);

	वापस 0;
err:
	क्रम (i = 0; i < actual_slots; i++)
		kमुक्त(txq->cmd[i]);
out_मुक्त_arrays:
	kमुक्त(txq->meta);
	txq->meta = शून्य;
	kमुक्त(txq->cmd);
	txq->cmd = शून्य;

	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(il_tx_queue_init);

व्योम
il_tx_queue_reset(काष्ठा il_priv *il, u32 txq_id)
अणु
	पूर्णांक slots, actual_slots;
	काष्ठा il_tx_queue *txq = &il->txq[txq_id];

	अगर (txq_id == il->cmd_queue) अणु
		slots = TFD_CMD_SLOTS;
		actual_slots = TFD_CMD_SLOTS + 1;
	पूर्ण अन्यथा अणु
		slots = TFD_TX_CMD_SLOTS;
		actual_slots = TFD_TX_CMD_SLOTS;
	पूर्ण

	स_रखो(txq->meta, 0, माप(काष्ठा il_cmd_meta) * actual_slots);
	txq->need_update = 0;

	/* Initialize queue's high/low-water marks, and head/tail idxes */
	il_queue_init(il, &txq->q, slots, txq_id);

	/* Tell device where to find queue */
	il->ops->txq_init(il, txq);
पूर्ण
EXPORT_SYMBOL(il_tx_queue_reset);

/*************** HOST COMMAND QUEUE FUNCTIONS   *****/

/*
 * il_enqueue_hcmd - enqueue a uCode command
 * @il: device ilate data poपूर्णांक
 * @cmd: a poपूर्णांक to the ucode command काष्ठाure
 *
 * The function वापसs < 0 values to indicate the operation is
 * failed. On success, it turns the idx (> 0) of command in the
 * command queue.
 */
पूर्णांक
il_enqueue_hcmd(काष्ठा il_priv *il, काष्ठा il_host_cmd *cmd)
अणु
	काष्ठा il_tx_queue *txq = &il->txq[il->cmd_queue];
	काष्ठा il_queue *q = &txq->q;
	काष्ठा il_device_cmd *out_cmd;
	काष्ठा il_cmd_meta *out_meta;
	dma_addr_t phys_addr;
	अचिन्हित दीर्घ flags;
	u32 idx;
	u16 fix_size;

	cmd->len = il->ops->get_hcmd_size(cmd->id, cmd->len);
	fix_size = (u16) (cmd->len + माप(out_cmd->hdr));

	/* If any of the command काष्ठाures end up being larger than
	 * the TFD_MAX_PAYLOAD_SIZE, and it sent as a 'small' command then
	 * we will need to increase the size of the TFD entries
	 * Also, check to see अगर command buffer should not exceed the size
	 * of device_cmd and max_cmd_size. */
	BUG_ON((fix_size > TFD_MAX_PAYLOAD_SIZE) &&
	       !(cmd->flags & CMD_SIZE_HUGE));
	BUG_ON(fix_size > IL_MAX_CMD_SIZE);

	अगर (il_is_rfसमाप्त(il) || il_is_ctसमाप्त(il)) अणु
		IL_WARN("Not sending command - %s KILL\n",
			il_is_rfसमाप्त(il) ? "RF" : "CT");
		वापस -EIO;
	पूर्ण

	spin_lock_irqsave(&il->hcmd_lock, flags);

	अगर (il_queue_space(q) < ((cmd->flags & CMD_ASYNC) ? 2 : 1)) अणु
		spin_unlock_irqrestore(&il->hcmd_lock, flags);

		IL_ERR("Restarting adapter due to command queue full\n");
		queue_work(il->workqueue, &il->restart);
		वापस -ENOSPC;
	पूर्ण

	idx = il_get_cmd_idx(q, q->ग_लिखो_ptr, cmd->flags & CMD_SIZE_HUGE);
	out_cmd = txq->cmd[idx];
	out_meta = &txq->meta[idx];

	अगर (WARN_ON(out_meta->flags & CMD_MAPPED)) अणु
		spin_unlock_irqrestore(&il->hcmd_lock, flags);
		वापस -ENOSPC;
	पूर्ण

	स_रखो(out_meta, 0, माप(*out_meta));	/* re-initialize to शून्य */
	out_meta->flags = cmd->flags | CMD_MAPPED;
	अगर (cmd->flags & CMD_WANT_SKB)
		out_meta->source = cmd;
	अगर (cmd->flags & CMD_ASYNC)
		out_meta->callback = cmd->callback;

	out_cmd->hdr.cmd = cmd->id;
	स_नकल(&out_cmd->cmd.payload, cmd->data, cmd->len);

	/* At this poपूर्णांक, the out_cmd now has all of the incoming cmd
	 * inक्रमmation */

	out_cmd->hdr.flags = 0;
	out_cmd->hdr.sequence =
	    cpu_to_le16(QUEUE_TO_SEQ(il->cmd_queue) | IDX_TO_SEQ(q->ग_लिखो_ptr));
	अगर (cmd->flags & CMD_SIZE_HUGE)
		out_cmd->hdr.sequence |= SEQ_HUGE_FRAME;

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	चयन (out_cmd->hdr.cmd) अणु
	हाल C_TX_LINK_QUALITY_CMD:
	हाल C_SENSITIVITY:
		D_HC_DUMP("Sending command %s (#%x), seq: 0x%04X, "
			  "%d bytes at %d[%d]:%d\n",
			  il_get_cmd_string(out_cmd->hdr.cmd), out_cmd->hdr.cmd,
			  le16_to_cpu(out_cmd->hdr.sequence), fix_size,
			  q->ग_लिखो_ptr, idx, il->cmd_queue);
		अवरोध;
	शेष:
		D_HC("Sending command %s (#%x), seq: 0x%04X, "
		     "%d bytes at %d[%d]:%d\n",
		     il_get_cmd_string(out_cmd->hdr.cmd), out_cmd->hdr.cmd,
		     le16_to_cpu(out_cmd->hdr.sequence), fix_size, q->ग_लिखो_ptr,
		     idx, il->cmd_queue);
	पूर्ण
#पूर्ण_अगर

	phys_addr =
	    pci_map_single(il->pci_dev, &out_cmd->hdr, fix_size,
			   PCI_DMA_BIसूचीECTIONAL);
	अगर (unlikely(pci_dma_mapping_error(il->pci_dev, phys_addr))) अणु
		idx = -ENOMEM;
		जाओ out;
	पूर्ण
	dma_unmap_addr_set(out_meta, mapping, phys_addr);
	dma_unmap_len_set(out_meta, len, fix_size);

	txq->need_update = 1;

	अगर (il->ops->txq_update_byte_cnt_tbl)
		/* Set up entry in queue's byte count circular buffer */
		il->ops->txq_update_byte_cnt_tbl(il, txq, 0);

	il->ops->txq_attach_buf_to_tfd(il, txq, phys_addr, fix_size, 1,
					    U32_PAD(cmd->len));

	/* Increment and update queue's ग_लिखो idx */
	q->ग_लिखो_ptr = il_queue_inc_wrap(q->ग_लिखो_ptr, q->n_bd);
	il_txq_update_ग_लिखो_ptr(il, txq);

out:
	spin_unlock_irqrestore(&il->hcmd_lock, flags);
	वापस idx;
पूर्ण

/*
 * il_hcmd_queue_reclaim - Reclaim TX command queue entries alपढ़ोy Tx'd
 *
 * When FW advances 'R' idx, all entries between old and new 'R' idx
 * need to be reclaimed. As result, some मुक्त space क्रमms.  If there is
 * enough मुक्त space (> low mark), wake the stack that feeds us.
 */
अटल व्योम
il_hcmd_queue_reclaim(काष्ठा il_priv *il, पूर्णांक txq_id, पूर्णांक idx, पूर्णांक cmd_idx)
अणु
	काष्ठा il_tx_queue *txq = &il->txq[txq_id];
	काष्ठा il_queue *q = &txq->q;
	पूर्णांक nमुक्तd = 0;

	अगर (idx >= q->n_bd || il_queue_used(q, idx) == 0) अणु
		IL_ERR("Read idx for DMA queue txq id (%d), idx %d, "
		       "is out of range [0-%d] %d %d.\n", txq_id, idx, q->n_bd,
		       q->ग_लिखो_ptr, q->पढ़ो_ptr);
		वापस;
	पूर्ण

	क्रम (idx = il_queue_inc_wrap(idx, q->n_bd); q->पढ़ो_ptr != idx;
	     q->पढ़ो_ptr = il_queue_inc_wrap(q->पढ़ो_ptr, q->n_bd)) अणु

		अगर (nमुक्तd++ > 0) अणु
			IL_ERR("HCMD skipped: idx (%d) %d %d\n", idx,
			       q->ग_लिखो_ptr, q->पढ़ो_ptr);
			queue_work(il->workqueue, &il->restart);
		पूर्ण

	पूर्ण
पूर्ण

/*
 * il_tx_cmd_complete - Pull unused buffers off the queue and reclaim them
 * @rxb: Rx buffer to reclaim
 *
 * If an Rx buffer has an async callback associated with it the callback
 * will be executed.  The attached skb (अगर present) will only be मुक्तd
 * अगर the callback वापसs 1
 */
व्योम
il_tx_cmd_complete(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	u16 sequence = le16_to_cpu(pkt->hdr.sequence);
	पूर्णांक txq_id = SEQ_TO_QUEUE(sequence);
	पूर्णांक idx = SEQ_TO_IDX(sequence);
	पूर्णांक cmd_idx;
	bool huge = !!(pkt->hdr.sequence & SEQ_HUGE_FRAME);
	काष्ठा il_device_cmd *cmd;
	काष्ठा il_cmd_meta *meta;
	काष्ठा il_tx_queue *txq = &il->txq[il->cmd_queue];
	अचिन्हित दीर्घ flags;

	/* If a Tx command is being handled and it isn't in the actual
	 * command queue then there a command routing bug has been पूर्णांकroduced
	 * in the queue management code. */
	अगर (WARN
	    (txq_id != il->cmd_queue,
	     "wrong command queue %d (should be %d), sequence 0x%X readp=%d writep=%d\n",
	     txq_id, il->cmd_queue, sequence, il->txq[il->cmd_queue].q.पढ़ो_ptr,
	     il->txq[il->cmd_queue].q.ग_लिखो_ptr)) अणु
		il_prपूर्णांक_hex_error(il, pkt, 32);
		वापस;
	पूर्ण

	cmd_idx = il_get_cmd_idx(&txq->q, idx, huge);
	cmd = txq->cmd[cmd_idx];
	meta = &txq->meta[cmd_idx];

	txq->समय_stamp = jअगरfies;

	pci_unmap_single(il->pci_dev, dma_unmap_addr(meta, mapping),
			 dma_unmap_len(meta, len), PCI_DMA_BIसूचीECTIONAL);

	/* Input error checking is करोne when commands are added to queue. */
	अगर (meta->flags & CMD_WANT_SKB) अणु
		meta->source->reply_page = (अचिन्हित दीर्घ)rxb_addr(rxb);
		rxb->page = शून्य;
	पूर्ण अन्यथा अगर (meta->callback)
		meta->callback(il, cmd, pkt);

	spin_lock_irqsave(&il->hcmd_lock, flags);

	il_hcmd_queue_reclaim(il, txq_id, idx, cmd_idx);

	अगर (!(meta->flags & CMD_ASYNC)) अणु
		clear_bit(S_HCMD_ACTIVE, &il->status);
		D_INFO("Clearing HCMD_ACTIVE for command %s\n",
		       il_get_cmd_string(cmd->hdr.cmd));
		wake_up(&il->रुको_command_queue);
	पूर्ण

	/* Mark as unmapped */
	meta->flags = 0;

	spin_unlock_irqrestore(&il->hcmd_lock, flags);
पूर्ण
EXPORT_SYMBOL(il_tx_cmd_complete);

MODULE_DESCRIPTION("iwl-legacy: common functions for 3945 and 4965");
MODULE_VERSION(IWLWIFI_VERSION);
MODULE_AUTHOR(DRV_COPYRIGHT " " DRV_AUTHOR);
MODULE_LICENSE("GPL");

/*
 * set bt_coex_active to true, uCode will करो समाप्त/defer
 * every समय the priority line is निश्चितed (BT is sending संकेतs on the
 * priority line in the PCIx).
 * set bt_coex_active to false, uCode will ignore the BT activity and
 * perक्रमm the normal operation
 *
 * User might experience transmit issue on some platक्रमm due to WiFi/BT
 * co-exist problem. The possible behaviors are:
 *   Able to scan and finding all the available AP
 *   Not able to associate with any AP
 * On those platक्रमms, WiFi communication can be restored by set
 * "bt_coex_active" module parameter to "false"
 *
 * शेष: bt_coex_active = true (BT_COEX_ENABLE)
 */
अटल bool bt_coex_active = true;
module_param(bt_coex_active, bool, 0444);
MODULE_PARM_DESC(bt_coex_active, "enable wifi/bluetooth co-exist");

u32 il_debug_level;
EXPORT_SYMBOL(il_debug_level);

स्थिर u8 il_bcast_addr[ETH_ALEN] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
EXPORT_SYMBOL(il_bcast_addr);

#घोषणा MAX_BIT_RATE_40_MHZ 150	/* Mbps */
#घोषणा MAX_BIT_RATE_20_MHZ 72	/* Mbps */
अटल व्योम
il_init_ht_hw_capab(स्थिर काष्ठा il_priv *il,
		    काष्ठा ieee80211_sta_ht_cap *ht_info,
		    क्रमागत nl80211_band band)
अणु
	u16 max_bit_rate = 0;
	u8 rx_chains_num = il->hw_params.rx_chains_num;
	u8 tx_chains_num = il->hw_params.tx_chains_num;

	ht_info->cap = 0;
	स_रखो(&ht_info->mcs, 0, माप(ht_info->mcs));

	ht_info->ht_supported = true;

	ht_info->cap |= IEEE80211_HT_CAP_SGI_20;
	max_bit_rate = MAX_BIT_RATE_20_MHZ;
	अगर (il->hw_params.ht40_channel & BIT(band)) अणु
		ht_info->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
		ht_info->cap |= IEEE80211_HT_CAP_SGI_40;
		ht_info->mcs.rx_mask[4] = 0x01;
		max_bit_rate = MAX_BIT_RATE_40_MHZ;
	पूर्ण

	अगर (il->cfg->mod_params->amsdu_size_8K)
		ht_info->cap |= IEEE80211_HT_CAP_MAX_AMSDU;

	ht_info->ampdu_factor = CFG_HT_RX_AMPDU_FACTOR_DEF;
	ht_info->ampdu_density = CFG_HT_MPDU_DENSITY_DEF;

	ht_info->mcs.rx_mask[0] = 0xFF;
	अगर (rx_chains_num >= 2)
		ht_info->mcs.rx_mask[1] = 0xFF;
	अगर (rx_chains_num >= 3)
		ht_info->mcs.rx_mask[2] = 0xFF;

	/* Highest supported Rx data rate */
	max_bit_rate *= rx_chains_num;
	WARN_ON(max_bit_rate & ~IEEE80211_HT_MCS_RX_HIGHEST_MASK);
	ht_info->mcs.rx_highest = cpu_to_le16(max_bit_rate);

	/* Tx MCS capabilities */
	ht_info->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	अगर (tx_chains_num != rx_chains_num) अणु
		ht_info->mcs.tx_params |= IEEE80211_HT_MCS_TX_RX_DIFF;
		ht_info->mcs.tx_params |=
		    ((tx_chains_num -
		      1) << IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT);
	पूर्ण
पूर्ण

/*
 * il_init_geos - Initialize mac80211's geo/channel info based from eeprom
 */
पूर्णांक
il_init_geos(काष्ठा il_priv *il)
अणु
	काष्ठा il_channel_info *ch;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *channels;
	काष्ठा ieee80211_channel *geo_ch;
	काष्ठा ieee80211_rate *rates;
	पूर्णांक i = 0;
	s8 max_tx_घातer = 0;

	अगर (il->bands[NL80211_BAND_2GHZ].n_bitrates ||
	    il->bands[NL80211_BAND_5GHZ].n_bitrates) अणु
		D_INFO("Geography modes already initialized.\n");
		set_bit(S_GEO_CONFIGURED, &il->status);
		वापस 0;
	पूर्ण

	channels =
	    kसुस्मृति(il->channel_count, माप(काष्ठा ieee80211_channel),
		    GFP_KERNEL);
	अगर (!channels)
		वापस -ENOMEM;

	rates =
	    kzalloc((माप(काष्ठा ieee80211_rate) * RATE_COUNT_LEGACY),
		    GFP_KERNEL);
	अगर (!rates) अणु
		kमुक्त(channels);
		वापस -ENOMEM;
	पूर्ण

	/* 5.2GHz channels start after the 2.4GHz channels */
	sband = &il->bands[NL80211_BAND_5GHZ];
	sband->channels = &channels[ARRAY_SIZE(il_eeprom_band_1)];
	/* just OFDM */
	sband->bitrates = &rates[IL_FIRST_OFDM_RATE];
	sband->n_bitrates = RATE_COUNT_LEGACY - IL_FIRST_OFDM_RATE;

	अगर (il->cfg->sku & IL_SKU_N)
		il_init_ht_hw_capab(il, &sband->ht_cap, NL80211_BAND_5GHZ);

	sband = &il->bands[NL80211_BAND_2GHZ];
	sband->channels = channels;
	/* OFDM & CCK */
	sband->bitrates = rates;
	sband->n_bitrates = RATE_COUNT_LEGACY;

	अगर (il->cfg->sku & IL_SKU_N)
		il_init_ht_hw_capab(il, &sband->ht_cap, NL80211_BAND_2GHZ);

	il->ieee_channels = channels;
	il->ieee_rates = rates;

	क्रम (i = 0; i < il->channel_count; i++) अणु
		ch = &il->channel_info[i];

		अगर (!il_is_channel_valid(ch))
			जारी;

		sband = &il->bands[ch->band];

		geo_ch = &sband->channels[sband->n_channels++];

		geo_ch->center_freq =
		    ieee80211_channel_to_frequency(ch->channel, ch->band);
		geo_ch->max_घातer = ch->max_घातer_avg;
		geo_ch->max_antenna_gain = 0xff;
		geo_ch->hw_value = ch->channel;

		अगर (il_is_channel_valid(ch)) अणु
			अगर (!(ch->flags & EEPROM_CHANNEL_IBSS))
				geo_ch->flags |= IEEE80211_CHAN_NO_IR;

			अगर (!(ch->flags & EEPROM_CHANNEL_ACTIVE))
				geo_ch->flags |= IEEE80211_CHAN_NO_IR;

			अगर (ch->flags & EEPROM_CHANNEL_RADAR)
				geo_ch->flags |= IEEE80211_CHAN_RADAR;

			geo_ch->flags |= ch->ht40_extension_channel;

			अगर (ch->max_घातer_avg > max_tx_घातer)
				max_tx_घातer = ch->max_घातer_avg;
		पूर्ण अन्यथा अणु
			geo_ch->flags |= IEEE80211_CHAN_DISABLED;
		पूर्ण

		D_INFO("Channel %d Freq=%d[%sGHz] %s flag=0x%X\n", ch->channel,
		       geo_ch->center_freq,
		       il_is_channel_a_band(ch) ? "5.2" : "2.4",
		       geo_ch->
		       flags & IEEE80211_CHAN_DISABLED ? "restricted" : "valid",
		       geo_ch->flags);
	पूर्ण

	il->tx_घातer_device_lmt = max_tx_घातer;
	il->tx_घातer_user_lmt = max_tx_घातer;
	il->tx_घातer_next = max_tx_घातer;

	अगर (il->bands[NL80211_BAND_5GHZ].n_channels == 0 &&
	    (il->cfg->sku & IL_SKU_A)) अणु
		IL_INFO("Incorrectly detected BG card as ABG. "
			"Please send your PCI ID 0x%04X:0x%04X to maintainer.\n",
			il->pci_dev->device, il->pci_dev->subप्रणाली_device);
		il->cfg->sku &= ~IL_SKU_A;
	पूर्ण

	IL_INFO("Tunable channels: %d 802.11bg, %d 802.11a channels\n",
		il->bands[NL80211_BAND_2GHZ].n_channels,
		il->bands[NL80211_BAND_5GHZ].n_channels);

	set_bit(S_GEO_CONFIGURED, &il->status);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(il_init_geos);

/*
 * il_मुक्त_geos - unकरो allocations in il_init_geos
 */
व्योम
il_मुक्त_geos(काष्ठा il_priv *il)
अणु
	kमुक्त(il->ieee_channels);
	kमुक्त(il->ieee_rates);
	clear_bit(S_GEO_CONFIGURED, &il->status);
पूर्ण
EXPORT_SYMBOL(il_मुक्त_geos);

अटल bool
il_is_channel_extension(काष्ठा il_priv *il, क्रमागत nl80211_band band,
			u16 channel, u8 extension_chan_offset)
अणु
	स्थिर काष्ठा il_channel_info *ch_info;

	ch_info = il_get_channel_info(il, band, channel);
	अगर (!il_is_channel_valid(ch_info))
		वापस false;

	अगर (extension_chan_offset == IEEE80211_HT_PARAM_CHA_SEC_ABOVE)
		वापस !(ch_info->
			 ht40_extension_channel & IEEE80211_CHAN_NO_HT40PLUS);
	अन्यथा अगर (extension_chan_offset == IEEE80211_HT_PARAM_CHA_SEC_BELOW)
		वापस !(ch_info->
			 ht40_extension_channel & IEEE80211_CHAN_NO_HT40MINUS);

	वापस false;
पूर्ण

bool
il_is_ht40_tx_allowed(काष्ठा il_priv *il, काष्ठा ieee80211_sta_ht_cap *ht_cap)
अणु
	अगर (!il->ht.enabled || !il->ht.is_40mhz)
		वापस false;

	/*
	 * We करो not check क्रम IEEE80211_HT_CAP_SUP_WIDTH_20_40
	 * the bit will not set अगर it is pure 40MHz हाल
	 */
	अगर (ht_cap && !ht_cap->ht_supported)
		वापस false;

#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
	अगर (il->disable_ht40)
		वापस false;
#पूर्ण_अगर

	वापस il_is_channel_extension(il, il->band,
				       le16_to_cpu(il->staging.channel),
				       il->ht.extension_chan_offset);
पूर्ण
EXPORT_SYMBOL(il_is_ht40_tx_allowed);

अटल u16 noअंतरभूत
il_adjust_beacon_पूर्णांकerval(u16 beacon_val, u16 max_beacon_val)
अणु
	u16 new_val;
	u16 beacon_factor;

	/*
	 * If mac80211 hasn't given us a beacon पूर्णांकerval, program
	 * the शेष पूर्णांकo the device.
	 */
	अगर (!beacon_val)
		वापस DEFAULT_BEACON_INTERVAL;

	/*
	 * If the beacon पूर्णांकerval we obtained from the peer
	 * is too large, we'll have to wake up more often
	 * (and in IBSS हाल, we'll beacon too much)
	 *
	 * For example, अगर max_beacon_val is 4096, and the
	 * requested beacon पूर्णांकerval is 7000, we'll have to
	 * use 3500 to be able to wake up on the beacons.
	 *
	 * This could badly influence beacon detection stats.
	 */

	beacon_factor = (beacon_val + max_beacon_val) / max_beacon_val;
	new_val = beacon_val / beacon_factor;

	अगर (!new_val)
		new_val = max_beacon_val;

	वापस new_val;
पूर्ण

पूर्णांक
il_send_rxon_timing(काष्ठा il_priv *il)
अणु
	u64 tsf;
	s32 पूर्णांकerval_पंचांग, rem;
	काष्ठा ieee80211_conf *conf = शून्य;
	u16 beacon_पूर्णांक;
	काष्ठा ieee80211_vअगर *vअगर = il->vअगर;

	conf = &il->hw->conf;

	lockdep_निश्चित_held(&il->mutex);

	स_रखो(&il->timing, 0, माप(काष्ठा il_rxon_समय_cmd));

	il->timing.बारtamp = cpu_to_le64(il->बारtamp);
	il->timing.listen_पूर्णांकerval = cpu_to_le16(conf->listen_पूर्णांकerval);

	beacon_पूर्णांक = vअगर ? vअगर->bss_conf.beacon_पूर्णांक : 0;

	/*
	 * TODO: For IBSS we need to get atim_win from mac80211,
	 *       क्रम now just always use 0
	 */
	il->timing.atim_win = 0;

	beacon_पूर्णांक =
	    il_adjust_beacon_पूर्णांकerval(beacon_पूर्णांक,
				      il->hw_params.max_beacon_itrvl *
				      TIME_UNIT);
	il->timing.beacon_पूर्णांकerval = cpu_to_le16(beacon_पूर्णांक);

	tsf = il->बारtamp;	/* tsf is modअगरed by करो_भाग: copy it */
	पूर्णांकerval_पंचांग = beacon_पूर्णांक * TIME_UNIT;
	rem = करो_भाग(tsf, पूर्णांकerval_पंचांग);
	il->timing.beacon_init_val = cpu_to_le32(पूर्णांकerval_पंचांग - rem);

	il->timing.dtim_period = vअगर ? (vअगर->bss_conf.dtim_period ? : 1) : 1;

	D_ASSOC("beacon interval %d beacon timer %d beacon tim %d\n",
		le16_to_cpu(il->timing.beacon_पूर्णांकerval),
		le32_to_cpu(il->timing.beacon_init_val),
		le16_to_cpu(il->timing.atim_win));

	वापस il_send_cmd_pdu(il, C_RXON_TIMING, माप(il->timing),
			       &il->timing);
पूर्ण
EXPORT_SYMBOL(il_send_rxon_timing);

व्योम
il_set_rxon_hwcrypto(काष्ठा il_priv *il, पूर्णांक hw_decrypt)
अणु
	काष्ठा il_rxon_cmd *rxon = &il->staging;

	अगर (hw_decrypt)
		rxon->filter_flags &= ~RXON_FILTER_DIS_DECRYPT_MSK;
	अन्यथा
		rxon->filter_flags |= RXON_FILTER_DIS_DECRYPT_MSK;

पूर्ण
EXPORT_SYMBOL(il_set_rxon_hwcrypto);

/* validate RXON काष्ठाure is valid */
पूर्णांक
il_check_rxon_cmd(काष्ठा il_priv *il)
अणु
	काष्ठा il_rxon_cmd *rxon = &il->staging;
	bool error = false;

	अगर (rxon->flags & RXON_FLG_BAND_24G_MSK) अणु
		अगर (rxon->flags & RXON_FLG_TGJ_NARROW_BAND_MSK) अणु
			IL_WARN("check 2.4G: wrong narrow\n");
			error = true;
		पूर्ण
		अगर (rxon->flags & RXON_FLG_RADAR_DETECT_MSK) अणु
			IL_WARN("check 2.4G: wrong radar\n");
			error = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(rxon->flags & RXON_FLG_SHORT_SLOT_MSK)) अणु
			IL_WARN("check 5.2G: not short slot!\n");
			error = true;
		पूर्ण
		अगर (rxon->flags & RXON_FLG_CCK_MSK) अणु
			IL_WARN("check 5.2G: CCK!\n");
			error = true;
		पूर्ण
	पूर्ण
	अगर ((rxon->node_addr[0] | rxon->bssid_addr[0]) & 0x1) अणु
		IL_WARN("mac/bssid mcast!\n");
		error = true;
	पूर्ण

	/* make sure basic rates 6Mbps and 1Mbps are supported */
	अगर ((rxon->ofdm_basic_rates & RATE_6M_MASK) == 0 &&
	    (rxon->cck_basic_rates & RATE_1M_MASK) == 0) अणु
		IL_WARN("neither 1 nor 6 are basic\n");
		error = true;
	पूर्ण

	अगर (le16_to_cpu(rxon->assoc_id) > 2007) अणु
		IL_WARN("aid > 2007\n");
		error = true;
	पूर्ण

	अगर ((rxon->flags & (RXON_FLG_CCK_MSK | RXON_FLG_SHORT_SLOT_MSK)) ==
	    (RXON_FLG_CCK_MSK | RXON_FLG_SHORT_SLOT_MSK)) अणु
		IL_WARN("CCK and short slot\n");
		error = true;
	पूर्ण

	अगर ((rxon->flags & (RXON_FLG_CCK_MSK | RXON_FLG_AUTO_DETECT_MSK)) ==
	    (RXON_FLG_CCK_MSK | RXON_FLG_AUTO_DETECT_MSK)) अणु
		IL_WARN("CCK and auto detect");
		error = true;
	पूर्ण

	अगर ((rxon->
	     flags & (RXON_FLG_AUTO_DETECT_MSK | RXON_FLG_TGG_PROTECT_MSK)) ==
	    RXON_FLG_TGG_PROTECT_MSK) अणु
		IL_WARN("TGg but no auto-detect\n");
		error = true;
	पूर्ण

	अगर (error)
		IL_WARN("Tuning to channel %d\n", le16_to_cpu(rxon->channel));

	अगर (error) अणु
		IL_ERR("Invalid RXON\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(il_check_rxon_cmd);

/*
 * il_full_rxon_required - check अगर full RXON (vs RXON_ASSOC) cmd is needed
 * @il: staging_rxon is compared to active_rxon
 *
 * If the RXON काष्ठाure is changing enough to require a new tune,
 * or is clearing the RXON_FILTER_ASSOC_MSK, then वापस 1 to indicate that
 * a new tune (full RXON command, rather than RXON_ASSOC cmd) is required.
 */
पूर्णांक
il_full_rxon_required(काष्ठा il_priv *il)
अणु
	स्थिर काष्ठा il_rxon_cmd *staging = &il->staging;
	स्थिर काष्ठा il_rxon_cmd *active = &il->active;

#घोषणा CHK(cond)							\
	अगर ((cond)) अणु							\
		D_INFO("need full RXON - " #cond "\n");	\
		वापस 1;						\
	पूर्ण

#घोषणा CHK_NEQ(c1, c2)						\
	अगर ((c1) != (c2)) अणु					\
		D_INFO("need full RXON - "	\
			       #c1 " != " #c2 " - %d != %d\n",	\
			       (c1), (c2));			\
		वापस 1;					\
	पूर्ण

	/* These items are only settable from the full RXON command */
	CHK(!il_is_associated(il));
	CHK(!ether_addr_equal_64bits(staging->bssid_addr, active->bssid_addr));
	CHK(!ether_addr_equal_64bits(staging->node_addr, active->node_addr));
	CHK(!ether_addr_equal_64bits(staging->wlap_bssid_addr,
				     active->wlap_bssid_addr));
	CHK_NEQ(staging->dev_type, active->dev_type);
	CHK_NEQ(staging->channel, active->channel);
	CHK_NEQ(staging->air_propagation, active->air_propagation);
	CHK_NEQ(staging->ofdm_ht_single_stream_basic_rates,
		active->ofdm_ht_single_stream_basic_rates);
	CHK_NEQ(staging->ofdm_ht_dual_stream_basic_rates,
		active->ofdm_ht_dual_stream_basic_rates);
	CHK_NEQ(staging->assoc_id, active->assoc_id);

	/* flags, filter_flags, ofdm_basic_rates, and cck_basic_rates can
	 * be updated with the RXON_ASSOC command -- however only some
	 * flag transitions are allowed using RXON_ASSOC */

	/* Check अगर we are not चयनing bands */
	CHK_NEQ(staging->flags & RXON_FLG_BAND_24G_MSK,
		active->flags & RXON_FLG_BAND_24G_MSK);

	/* Check अगर we are चयनing association toggle */
	CHK_NEQ(staging->filter_flags & RXON_FILTER_ASSOC_MSK,
		active->filter_flags & RXON_FILTER_ASSOC_MSK);

#अघोषित CHK
#अघोषित CHK_NEQ

	वापस 0;
पूर्ण
EXPORT_SYMBOL(il_full_rxon_required);

u8
il_get_lowest_plcp(काष्ठा il_priv *il)
अणु
	/*
	 * Assign the lowest rate -- should really get this from
	 * the beacon skb from mac80211.
	 */
	अगर (il->staging.flags & RXON_FLG_BAND_24G_MSK)
		वापस RATE_1M_PLCP;
	अन्यथा
		वापस RATE_6M_PLCP;
पूर्ण
EXPORT_SYMBOL(il_get_lowest_plcp);

अटल व्योम
_il_set_rxon_ht(काष्ठा il_priv *il, काष्ठा il_ht_config *ht_conf)
अणु
	काष्ठा il_rxon_cmd *rxon = &il->staging;

	अगर (!il->ht.enabled) अणु
		rxon->flags &=
		    ~(RXON_FLG_CHANNEL_MODE_MSK |
		      RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK | RXON_FLG_HT40_PROT_MSK
		      | RXON_FLG_HT_PROT_MSK);
		वापस;
	पूर्ण

	rxon->flags |=
	    cpu_to_le32(il->ht.protection << RXON_FLG_HT_OPERATING_MODE_POS);

	/* Set up channel bandwidth:
	 * 20 MHz only, 20/40 mixed or pure 40 अगर ht40 ok */
	/* clear the HT channel mode beक्रमe set the mode */
	rxon->flags &=
	    ~(RXON_FLG_CHANNEL_MODE_MSK | RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK);
	अगर (il_is_ht40_tx_allowed(il, शून्य)) अणु
		/* pure ht40 */
		अगर (il->ht.protection == IEEE80211_HT_OP_MODE_PROTECTION_20MHZ) अणु
			rxon->flags |= RXON_FLG_CHANNEL_MODE_PURE_40;
			/* Note: control channel is opposite of extension channel */
			चयन (il->ht.extension_chan_offset) अणु
			हाल IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
				rxon->flags &=
				    ~RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				अवरोध;
			हाल IEEE80211_HT_PARAM_CHA_SEC_BELOW:
				rxon->flags |= RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Note: control channel is opposite of extension channel */
			चयन (il->ht.extension_chan_offset) अणु
			हाल IEEE80211_HT_PARAM_CHA_SEC_ABOVE:
				rxon->flags &=
				    ~(RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK);
				rxon->flags |= RXON_FLG_CHANNEL_MODE_MIXED;
				अवरोध;
			हाल IEEE80211_HT_PARAM_CHA_SEC_BELOW:
				rxon->flags |= RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK;
				rxon->flags |= RXON_FLG_CHANNEL_MODE_MIXED;
				अवरोध;
			हाल IEEE80211_HT_PARAM_CHA_SEC_NONE:
			शेष:
				/* channel location only valid अगर in Mixed mode */
				IL_ERR("invalid extension channel offset\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rxon->flags |= RXON_FLG_CHANNEL_MODE_LEGACY;
	पूर्ण

	अगर (il->ops->set_rxon_chain)
		il->ops->set_rxon_chain(il);

	D_ASSOC("rxon flags 0x%X operation mode :0x%X "
		"extension channel offset 0x%x\n", le32_to_cpu(rxon->flags),
		il->ht.protection, il->ht.extension_chan_offset);
पूर्ण

व्योम
il_set_rxon_ht(काष्ठा il_priv *il, काष्ठा il_ht_config *ht_conf)
अणु
	_il_set_rxon_ht(il, ht_conf);
पूर्ण
EXPORT_SYMBOL(il_set_rxon_ht);

/* Return valid, unused, channel क्रम a passive scan to reset the RF */
u8
il_get_single_channel_number(काष्ठा il_priv *il, क्रमागत nl80211_band band)
अणु
	स्थिर काष्ठा il_channel_info *ch_info;
	पूर्णांक i;
	u8 channel = 0;
	u8 min, max;

	अगर (band == NL80211_BAND_5GHZ) अणु
		min = 14;
		max = il->channel_count;
	पूर्ण अन्यथा अणु
		min = 0;
		max = 14;
	पूर्ण

	क्रम (i = min; i < max; i++) अणु
		channel = il->channel_info[i].channel;
		अगर (channel == le16_to_cpu(il->staging.channel))
			जारी;

		ch_info = il_get_channel_info(il, band, channel);
		अगर (il_is_channel_valid(ch_info))
			अवरोध;
	पूर्ण

	वापस channel;
पूर्ण
EXPORT_SYMBOL(il_get_single_channel_number);

/*
 * il_set_rxon_channel - Set the band and channel values in staging RXON
 * @ch: requested channel as a poपूर्णांकer to काष्ठा ieee80211_channel

 * NOTE:  Does not commit to the hardware; it sets appropriate bit fields
 * in the staging RXON flag काष्ठाure based on the ch->band
 */
पूर्णांक
il_set_rxon_channel(काष्ठा il_priv *il, काष्ठा ieee80211_channel *ch)
अणु
	क्रमागत nl80211_band band = ch->band;
	u16 channel = ch->hw_value;

	अगर (le16_to_cpu(il->staging.channel) == channel && il->band == band)
		वापस 0;

	il->staging.channel = cpu_to_le16(channel);
	अगर (band == NL80211_BAND_5GHZ)
		il->staging.flags &= ~RXON_FLG_BAND_24G_MSK;
	अन्यथा
		il->staging.flags |= RXON_FLG_BAND_24G_MSK;

	il->band = band;

	D_INFO("Staging channel set to %d [%d]\n", channel, band);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(il_set_rxon_channel);

व्योम
il_set_flags_क्रम_band(काष्ठा il_priv *il, क्रमागत nl80211_band band,
		      काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (band == NL80211_BAND_5GHZ) अणु
		il->staging.flags &=
		    ~(RXON_FLG_BAND_24G_MSK | RXON_FLG_AUTO_DETECT_MSK |
		      RXON_FLG_CCK_MSK);
		il->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
	पूर्ण अन्यथा अणु
		/* Copied from il_post_associate() */
		अगर (vअगर && vअगर->bss_conf.use_लघु_slot)
			il->staging.flags |= RXON_FLG_SHORT_SLOT_MSK;
		अन्यथा
			il->staging.flags &= ~RXON_FLG_SHORT_SLOT_MSK;

		il->staging.flags |= RXON_FLG_BAND_24G_MSK;
		il->staging.flags |= RXON_FLG_AUTO_DETECT_MSK;
		il->staging.flags &= ~RXON_FLG_CCK_MSK;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(il_set_flags_क्रम_band);

/*
 * initialize rxon काष्ठाure with शेष values from eeprom
 */
व्योम
il_connection_init_rx_config(काष्ठा il_priv *il)
अणु
	स्थिर काष्ठा il_channel_info *ch_info;

	स_रखो(&il->staging, 0, माप(il->staging));

	चयन (il->iw_mode) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		il->staging.dev_type = RXON_DEV_TYPE_ESS;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		il->staging.dev_type = RXON_DEV_TYPE_ESS;
		il->staging.filter_flags = RXON_FILTER_ACCEPT_GRP_MSK;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		il->staging.dev_type = RXON_DEV_TYPE_IBSS;
		il->staging.flags = RXON_FLG_SHORT_PREAMBLE_MSK;
		il->staging.filter_flags =
		    RXON_FILTER_BCON_AWARE_MSK | RXON_FILTER_ACCEPT_GRP_MSK;
		अवरोध;
	शेष:
		IL_ERR("Unsupported interface type %d\n", il->vअगर->type);
		वापस;
	पूर्ण

#अगर 0
	/* TODO:  Figure out when लघु_preamble would be set and cache from
	 * that */
	अगर (!hw_to_local(il->hw)->लघु_preamble)
		il->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;
	अन्यथा
		il->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
#पूर्ण_अगर

	ch_info =
	    il_get_channel_info(il, il->band, le16_to_cpu(il->active.channel));

	अगर (!ch_info)
		ch_info = &il->channel_info[0];

	il->staging.channel = cpu_to_le16(ch_info->channel);
	il->band = ch_info->band;

	il_set_flags_क्रम_band(il, il->band, il->vअगर);

	il->staging.ofdm_basic_rates =
	    (IL_OFDM_RATES_MASK >> IL_FIRST_OFDM_RATE) & 0xFF;
	il->staging.cck_basic_rates =
	    (IL_CCK_RATES_MASK >> IL_FIRST_CCK_RATE) & 0xF;

	/* clear both MIX and PURE40 mode flag */
	il->staging.flags &=
	    ~(RXON_FLG_CHANNEL_MODE_MIXED | RXON_FLG_CHANNEL_MODE_PURE_40);
	अगर (il->vअगर)
		स_नकल(il->staging.node_addr, il->vअगर->addr, ETH_ALEN);

	il->staging.ofdm_ht_single_stream_basic_rates = 0xff;
	il->staging.ofdm_ht_dual_stream_basic_rates = 0xff;
पूर्ण
EXPORT_SYMBOL(il_connection_init_rx_config);

व्योम
il_set_rate(काष्ठा il_priv *il)
अणु
	स्थिर काष्ठा ieee80211_supported_band *hw = शून्य;
	काष्ठा ieee80211_rate *rate;
	पूर्णांक i;

	hw = il_get_hw_mode(il, il->band);
	अगर (!hw) अणु
		IL_ERR("Failed to set rate: unable to get hw mode\n");
		वापस;
	पूर्ण

	il->active_rate = 0;

	क्रम (i = 0; i < hw->n_bitrates; i++) अणु
		rate = &(hw->bitrates[i]);
		अगर (rate->hw_value < RATE_COUNT_LEGACY)
			il->active_rate |= (1 << rate->hw_value);
	पूर्ण

	D_RATE("Set active_rate = %0x\n", il->active_rate);

	il->staging.cck_basic_rates =
	    (IL_CCK_BASIC_RATES_MASK >> IL_FIRST_CCK_RATE) & 0xF;

	il->staging.ofdm_basic_rates =
	    (IL_OFDM_BASIC_RATES_MASK >> IL_FIRST_OFDM_RATE) & 0xFF;
पूर्ण
EXPORT_SYMBOL(il_set_rate);

व्योम
il_chचयन_करोne(काष्ठा il_priv *il, bool is_success)
अणु
	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	अगर (test_and_clear_bit(S_CHANNEL_SWITCH_PENDING, &il->status))
		ieee80211_chचयन_करोne(il->vअगर, is_success);
पूर्ण
EXPORT_SYMBOL(il_chचयन_करोne);

व्योम
il_hdl_csa(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_csa_notअगरication *csa = &(pkt->u.csa_notअगर);
	काष्ठा il_rxon_cmd *rxon = (व्योम *)&il->active;

	अगर (!test_bit(S_CHANNEL_SWITCH_PENDING, &il->status))
		वापस;

	अगर (!le32_to_cpu(csa->status) && csa->channel == il->चयन_channel) अणु
		rxon->channel = csa->channel;
		il->staging.channel = csa->channel;
		D_11H("CSA notif: channel %d\n", le16_to_cpu(csa->channel));
		il_chचयन_करोne(il, true);
	पूर्ण अन्यथा अणु
		IL_ERR("CSA notif (fail) : channel %d\n",
		       le16_to_cpu(csa->channel));
		il_chचयन_करोne(il, false);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(il_hdl_csa);

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
व्योम
il_prपूर्णांक_rx_config_cmd(काष्ठा il_priv *il)
अणु
	काष्ठा il_rxon_cmd *rxon = &il->staging;

	D_RADIO("RX CONFIG:\n");
	il_prपूर्णांक_hex_dump(il, IL_DL_RADIO, (u8 *) rxon, माप(*rxon));
	D_RADIO("u16 channel: 0x%x\n", le16_to_cpu(rxon->channel));
	D_RADIO("u32 flags: 0x%08X\n", le32_to_cpu(rxon->flags));
	D_RADIO("u32 filter_flags: 0x%08x\n", le32_to_cpu(rxon->filter_flags));
	D_RADIO("u8 dev_type: 0x%x\n", rxon->dev_type);
	D_RADIO("u8 ofdm_basic_rates: 0x%02x\n", rxon->ofdm_basic_rates);
	D_RADIO("u8 cck_basic_rates: 0x%02x\n", rxon->cck_basic_rates);
	D_RADIO("u8[6] node_addr: %pM\n", rxon->node_addr);
	D_RADIO("u8[6] bssid_addr: %pM\n", rxon->bssid_addr);
	D_RADIO("u16 assoc_id: 0x%x\n", le16_to_cpu(rxon->assoc_id));
पूर्ण
EXPORT_SYMBOL(il_prपूर्णांक_rx_config_cmd);
#पूर्ण_अगर
/*
 * il_irq_handle_error - called क्रम HW or SW error पूर्णांकerrupt from card
 */
व्योम
il_irq_handle_error(काष्ठा il_priv *il)
अणु
	/* Set the FW error flag -- cleared on il_करोwn */
	set_bit(S_FW_ERROR, &il->status);

	/* Cancel currently queued command. */
	clear_bit(S_HCMD_ACTIVE, &il->status);

	IL_ERR("Loaded firmware version: %s\n", il->hw->wiphy->fw_version);

	il->ops->dump_nic_error_log(il);
	अगर (il->ops->dump_fh)
		il->ops->dump_fh(il, शून्य, false);
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	अगर (il_get_debug_level(il) & IL_DL_FW_ERRORS)
		il_prपूर्णांक_rx_config_cmd(il);
#पूर्ण_अगर

	wake_up(&il->रुको_command_queue);

	/* Keep the restart process from trying to send host
	 * commands by clearing the INIT status bit */
	clear_bit(S_READY, &il->status);

	अगर (!test_bit(S_EXIT_PENDING, &il->status)) अणु
		IL_DBG(IL_DL_FW_ERRORS,
		       "Restarting adapter due to uCode error.\n");

		अगर (il->cfg->mod_params->restart_fw)
			queue_work(il->workqueue, &il->restart);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(il_irq_handle_error);

अटल पूर्णांक
_il_apm_stop_master(काष्ठा il_priv *il)
अणु
	पूर्णांक ret = 0;

	/* stop device's busmaster DMA activity */
	_il_set_bit(il, CSR_RESET, CSR_RESET_REG_FLAG_STOP_MASTER);

	ret =
	    _il_poll_bit(il, CSR_RESET, CSR_RESET_REG_FLAG_MASTER_DISABLED,
			 CSR_RESET_REG_FLAG_MASTER_DISABLED, 100);
	अगर (ret < 0)
		IL_WARN("Master Disable Timed Out, 100 usec\n");

	D_INFO("stop master\n");

	वापस ret;
पूर्ण

व्योम
_il_apm_stop(काष्ठा il_priv *il)
अणु
	lockdep_निश्चित_held(&il->reg_lock);

	D_INFO("Stop card, put in low power state\n");

	/* Stop device's DMA activity */
	_il_apm_stop_master(il);

	/* Reset the entire device */
	_il_set_bit(il, CSR_RESET, CSR_RESET_REG_FLAG_SW_RESET);

	udelay(10);

	/*
	 * Clear "initialization complete" bit to move adapter from
	 * D0A* (घातered-up Active) --> D0U* (Uninitialized) state.
	 */
	_il_clear_bit(il, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_INIT_DONE);
पूर्ण
EXPORT_SYMBOL(_il_apm_stop);

व्योम
il_apm_stop(काष्ठा il_priv *il)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&il->reg_lock, flags);
	_il_apm_stop(il);
	spin_unlock_irqrestore(&il->reg_lock, flags);
पूर्ण
EXPORT_SYMBOL(il_apm_stop);

/*
 * Start up NIC's basic functionality after it has been reset
 * (e.g. after platक्रमm boot, or shutकरोwn via il_apm_stop())
 * NOTE:  This करोes not load uCode nor start the embedded processor
 */
पूर्णांक
il_apm_init(काष्ठा il_priv *il)
अणु
	पूर्णांक ret = 0;
	u16 lctl;

	D_INFO("Init card's basic functions\n");

	/*
	 * Use "set_bit" below rather than "write", to preserve any hardware
	 * bits alपढ़ोy set by शेष after reset.
	 */

	/* Disable L0S निकास समयr (platक्रमm NMI Work/Around) */
	il_set_bit(il, CSR_GIO_CHICKEN_BITS,
		   CSR_GIO_CHICKEN_BITS_REG_BIT_DIS_L0S_EXIT_TIMER);

	/*
	 * Disable L0s without affecting L1;
	 *  करोn't रुको क्रम ICH L0s (ICH bug W/A)
	 */
	il_set_bit(il, CSR_GIO_CHICKEN_BITS,
		   CSR_GIO_CHICKEN_BITS_REG_BIT_L1A_NO_L0S_RX);

	/* Set FH रुको threshold to maximum (HW error during stress W/A) */
	il_set_bit(il, CSR_DBG_HPET_MEM_REG, CSR_DBG_HPET_MEM_REG_VAL);

	/*
	 * Enable HAP INTA (पूर्णांकerrupt from management bus) to
	 * wake device's PCI Express link L1a -> L0s
	 * NOTE:  This is no-op क्रम 3945 (non-existent bit)
	 */
	il_set_bit(il, CSR_HW_IF_CONFIG_REG,
		   CSR_HW_IF_CONFIG_REG_BIT_HAP_WAKE_L1A);

	/*
	 * HW bug W/A क्रम instability in PCIe bus L0->L0S->L1 transition.
	 * Check अगर BIOS (or OS) enabled L1-ASPM on this device.
	 * If so (likely), disable L0S, so device moves directly L0->L1;
	 *    costs negligible amount of घातer savings.
	 * If not (unlikely), enable L0S, so there is at least some
	 *    घातer savings, even without L1.
	 */
	अगर (il->cfg->set_l0s) अणु
		ret = pcie_capability_पढ़ो_word(il->pci_dev, PCI_EXP_LNKCTL, &lctl);
		अगर (!ret && (lctl & PCI_EXP_LNKCTL_ASPM_L1)) अणु
			/* L1-ASPM enabled; disable(!) L0S  */
			il_set_bit(il, CSR_GIO_REG,
				   CSR_GIO_REG_VAL_L0S_ENABLED);
			D_POWER("L1 Enabled; Disabling L0S\n");
		पूर्ण अन्यथा अणु
			/* L1-ASPM disabled; enable(!) L0S */
			il_clear_bit(il, CSR_GIO_REG,
				     CSR_GIO_REG_VAL_L0S_ENABLED);
			D_POWER("L1 Disabled; Enabling L0S\n");
		पूर्ण
	पूर्ण

	/* Configure analog phase-lock-loop beक्रमe activating to D0A */
	अगर (il->cfg->pll_cfg_val)
		il_set_bit(il, CSR_ANA_PLL_CFG,
			   il->cfg->pll_cfg_val);

	/*
	 * Set "initialization complete" bit to move adapter from
	 * D0U* --> D0A* (घातered-up active) state.
	 */
	il_set_bit(il, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_INIT_DONE);

	/*
	 * Wait क्रम घड़ी stabilization; once stabilized, access to
	 * device-पूर्णांकernal resources is supported, e.g. il_wr_prph()
	 * and accesses to uCode SRAM.
	 */
	ret =
	    _il_poll_bit(il, CSR_GP_CNTRL,
			 CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY,
			 CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY, 25000);
	अगर (ret < 0) अणु
		D_INFO("Failed to init the card\n");
		जाओ out;
	पूर्ण

	/*
	 * Enable DMA and BSM (अगर used) घड़ीs, रुको क्रम them to stabilize.
	 * BSM (Boostrap State Machine) is only in 3945 and 4965.
	 *
	 * Write to "CLK_EN_REG"; "1" bits enable घड़ीs, जबतक "0" bits
	 * करो not disable घड़ीs.  This preserves any hardware bits alपढ़ोy
	 * set by शेष in "CLK_CTRL_REG" after reset.
	 */
	अगर (il->cfg->use_bsm)
		il_wr_prph(il, APMG_CLK_EN_REG,
			   APMG_CLK_VAL_DMA_CLK_RQT | APMG_CLK_VAL_BSM_CLK_RQT);
	अन्यथा
		il_wr_prph(il, APMG_CLK_EN_REG, APMG_CLK_VAL_DMA_CLK_RQT);
	udelay(20);

	/* Disable L1-Active */
	il_set_bits_prph(il, APMG_PCIDEV_STT_REG,
			 APMG_PCIDEV_STT_VAL_L1_ACT_DIS);

out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(il_apm_init);

पूर्णांक
il_set_tx_घातer(काष्ठा il_priv *il, s8 tx_घातer, bool क्रमce)
अणु
	पूर्णांक ret;
	s8 prev_tx_घातer;
	bool defer;

	lockdep_निश्चित_held(&il->mutex);

	अगर (il->tx_घातer_user_lmt == tx_घातer && !क्रमce)
		वापस 0;

	अगर (!il->ops->send_tx_घातer)
		वापस -EOPNOTSUPP;

	/* 0 dBm mean 1 milliwatt */
	अगर (tx_घातer < 0) अणु
		IL_WARN("Requested user TXPOWER %d below 1 mW.\n", tx_घातer);
		वापस -EINVAL;
	पूर्ण

	अगर (tx_घातer > il->tx_घातer_device_lmt) अणु
		IL_WARN("Requested user TXPOWER %d above upper limit %d.\n",
			tx_घातer, il->tx_घातer_device_lmt);
		वापस -EINVAL;
	पूर्ण

	अगर (!il_is_पढ़ोy_rf(il))
		वापस -EIO;

	/* scan complete and commit_rxon use tx_घातer_next value,
	 * it always need to be updated क्रम newest request */
	il->tx_घातer_next = tx_घातer;

	/* करो not set tx घातer when scanning or channel changing */
	defer = test_bit(S_SCANNING, &il->status) ||
	    स_भेद(&il->active, &il->staging, माप(il->staging));
	अगर (defer && !क्रमce) अणु
		D_INFO("Deferring tx power set\n");
		वापस 0;
	पूर्ण

	prev_tx_घातer = il->tx_घातer_user_lmt;
	il->tx_घातer_user_lmt = tx_घातer;

	ret = il->ops->send_tx_घातer(il);

	/* अगर fail to set tx_घातer, restore the orig. tx घातer */
	अगर (ret) अणु
		il->tx_घातer_user_lmt = prev_tx_घातer;
		il->tx_घातer_next = prev_tx_घातer;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(il_set_tx_घातer);

व्योम
il_send_bt_config(काष्ठा il_priv *il)
अणु
	काष्ठा il_bt_cmd bt_cmd = अणु
		.lead_समय = BT_LEAD_TIME_DEF,
		.max_समाप्त = BT_MAX_KILL_DEF,
		.समाप्त_ack_mask = 0,
		.समाप्त_cts_mask = 0,
	पूर्ण;

	अगर (!bt_coex_active)
		bt_cmd.flags = BT_COEX_DISABLE;
	अन्यथा
		bt_cmd.flags = BT_COEX_ENABLE;

	D_INFO("BT coex %s\n",
	       (bt_cmd.flags == BT_COEX_DISABLE) ? "disable" : "active");

	अगर (il_send_cmd_pdu(il, C_BT_CONFIG, माप(काष्ठा il_bt_cmd), &bt_cmd))
		IL_ERR("failed to send BT Coex Config\n");
पूर्ण
EXPORT_SYMBOL(il_send_bt_config);

पूर्णांक
il_send_stats_request(काष्ठा il_priv *il, u8 flags, bool clear)
अणु
	काष्ठा il_stats_cmd stats_cmd = अणु
		.configuration_flags = clear ? IL_STATS_CONF_CLEAR_STATS : 0,
	पूर्ण;

	अगर (flags & CMD_ASYNC)
		वापस il_send_cmd_pdu_async(il, C_STATS, माप(काष्ठा il_stats_cmd),
					     &stats_cmd, शून्य);
	अन्यथा
		वापस il_send_cmd_pdu(il, C_STATS, माप(काष्ठा il_stats_cmd),
				       &stats_cmd);
पूर्ण
EXPORT_SYMBOL(il_send_stats_request);

व्योम
il_hdl_pm_sleep(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
#अगर_घोषित CONFIG_IWLEGACY_DEBUG
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	काष्ठा il_sleep_notअगरication *sleep = &(pkt->u.sleep_notअगर);
	D_RX("sleep mode: %d, src: %d\n",
	     sleep->pm_sleep_mode, sleep->pm_wakeup_src);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(il_hdl_pm_sleep);

व्योम
il_hdl_pm_debug_stats(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);
	u32 len = le32_to_cpu(pkt->len_n_flags) & IL_RX_FRAME_SIZE_MSK;
	D_RADIO("Dumping %d bytes of unhandled notification for %s:\n", len,
		il_get_cmd_string(pkt->hdr.cmd));
	il_prपूर्णांक_hex_dump(il, IL_DL_RADIO, pkt->u.raw, len);
पूर्ण
EXPORT_SYMBOL(il_hdl_pm_debug_stats);

व्योम
il_hdl_error(काष्ठा il_priv *il, काष्ठा il_rx_buf *rxb)
अणु
	काष्ठा il_rx_pkt *pkt = rxb_addr(rxb);

	IL_ERR("Error Reply type 0x%08X cmd %s (0x%02X) "
	       "seq 0x%04X ser 0x%08X\n",
	       le32_to_cpu(pkt->u.err_resp.error_type),
	       il_get_cmd_string(pkt->u.err_resp.cmd_id),
	       pkt->u.err_resp.cmd_id,
	       le16_to_cpu(pkt->u.err_resp.bad_cmd_seq_num),
	       le32_to_cpu(pkt->u.err_resp.error_info));
पूर्ण
EXPORT_SYMBOL(il_hdl_error);

व्योम
il_clear_isr_stats(काष्ठा il_priv *il)
अणु
	स_रखो(&il->isr_stats, 0, माप(il->isr_stats));
पूर्ण

पूर्णांक
il_mac_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर, u16 queue,
	       स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा il_priv *il = hw->priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक q;

	D_MAC80211("enter\n");

	अगर (!il_is_पढ़ोy_rf(il)) अणु
		D_MAC80211("leave - RF not ready\n");
		वापस -EIO;
	पूर्ण

	अगर (queue >= AC_NUM) अणु
		D_MAC80211("leave - queue >= AC_NUM %d\n", queue);
		वापस 0;
	पूर्ण

	q = AC_NUM - 1 - queue;

	spin_lock_irqsave(&il->lock, flags);

	il->qos_data.def_qos_parm.ac[q].cw_min =
	    cpu_to_le16(params->cw_min);
	il->qos_data.def_qos_parm.ac[q].cw_max =
	    cpu_to_le16(params->cw_max);
	il->qos_data.def_qos_parm.ac[q].aअगरsn = params->aअगरs;
	il->qos_data.def_qos_parm.ac[q].edca_txop =
	    cpu_to_le16((params->txop * 32));

	il->qos_data.def_qos_parm.ac[q].reserved1 = 0;

	spin_unlock_irqrestore(&il->lock, flags);

	D_MAC80211("leave\n");
	वापस 0;
पूर्ण
EXPORT_SYMBOL(il_mac_conf_tx);

पूर्णांक
il_mac_tx_last_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा il_priv *il = hw->priv;
	पूर्णांक ret;

	D_MAC80211("enter\n");

	ret = (il->ibss_manager == IL_IBSS_MANAGER);

	D_MAC80211("leave ret %d\n", ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(il_mac_tx_last_beacon);

अटल पूर्णांक
il_set_mode(काष्ठा il_priv *il)
अणु
	il_connection_init_rx_config(il);

	अगर (il->ops->set_rxon_chain)
		il->ops->set_rxon_chain(il);

	वापस il_commit_rxon(il);
पूर्ण

पूर्णांक
il_mac_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा il_priv *il = hw->priv;
	पूर्णांक err;
	bool reset;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: type %d, addr %pM\n", vअगर->type, vअगर->addr);

	अगर (!il_is_पढ़ोy_rf(il)) अणु
		IL_WARN("Try to add interface when device not ready\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * We करो not support multiple भव पूर्णांकerfaces, but on hardware reset
	 * we have to add the same पूर्णांकerface again.
	 */
	reset = (il->vअगर == vअगर);
	अगर (il->vअगर && !reset) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	il->vअगर = vअगर;
	il->iw_mode = vअगर->type;

	err = il_set_mode(il);
	अगर (err) अणु
		IL_WARN("Fail to set mode %d\n", vअगर->type);
		अगर (!reset) अणु
			il->vअगर = शून्य;
			il->iw_mode = NL80211_IFTYPE_STATION;
		पूर्ण
	पूर्ण

out:
	D_MAC80211("leave err %d\n", err);
	mutex_unlock(&il->mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL(il_mac_add_पूर्णांकerface);

अटल व्योम
il_tearकरोwn_पूर्णांकerface(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर)
अणु
	lockdep_निश्चित_held(&il->mutex);

	अगर (il->scan_vअगर == vअगर) अणु
		il_scan_cancel_समयout(il, 200);
		il_क्रमce_scan_end(il);
	पूर्ण

	il_set_mode(il);
पूर्ण

व्योम
il_mac_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा il_priv *il = hw->priv;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: type %d, addr %pM\n", vअगर->type, vअगर->addr);

	WARN_ON(il->vअगर != vअगर);
	il->vअगर = शून्य;
	il->iw_mode = NL80211_IFTYPE_UNSPECIFIED;
	il_tearकरोwn_पूर्णांकerface(il, vअगर);
	eth_zero_addr(il->bssid);

	D_MAC80211("leave\n");
	mutex_unlock(&il->mutex);
पूर्ण
EXPORT_SYMBOL(il_mac_हटाओ_पूर्णांकerface);

पूर्णांक
il_alloc_txq_mem(काष्ठा il_priv *il)
अणु
	अगर (!il->txq)
		il->txq =
		    kसुस्मृति(il->cfg->num_of_queues,
			    माप(काष्ठा il_tx_queue),
			    GFP_KERNEL);
	अगर (!il->txq) अणु
		IL_ERR("Not enough memory for txq\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(il_alloc_txq_mem);

व्योम
il_मुक्त_txq_mem(काष्ठा il_priv *il)
अणु
	kमुक्त(il->txq);
	il->txq = शून्य;
पूर्ण
EXPORT_SYMBOL(il_मुक्त_txq_mem);

पूर्णांक
il_क्रमce_reset(काष्ठा il_priv *il, bool बाह्यal)
अणु
	काष्ठा il_क्रमce_reset *क्रमce_reset;

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस -EINVAL;

	क्रमce_reset = &il->क्रमce_reset;
	क्रमce_reset->reset_request_count++;
	अगर (!बाह्यal) अणु
		अगर (क्रमce_reset->last_क्रमce_reset_jअगरfies &&
		    समय_after(क्रमce_reset->last_क्रमce_reset_jअगरfies +
			       क्रमce_reset->reset_duration, jअगरfies)) अणु
			D_INFO("force reset rejected\n");
			क्रमce_reset->reset_reject_count++;
			वापस -EAGAIN;
		पूर्ण
	पूर्ण
	क्रमce_reset->reset_success_count++;
	क्रमce_reset->last_क्रमce_reset_jअगरfies = jअगरfies;

	/*
	 * अगर the request is from बाह्यal(ex: debugfs),
	 * then always perक्रमm the request in regardless the module
	 * parameter setting
	 * अगर the request is from पूर्णांकernal (uCode error or driver
	 * detect failure), then fw_restart module parameter
	 * need to be check beक्रमe perक्रमming firmware reload
	 */

	अगर (!बाह्यal && !il->cfg->mod_params->restart_fw) अणु
		D_INFO("Cancel firmware reload based on "
		       "module parameter setting\n");
		वापस 0;
	पूर्ण

	IL_ERR("On demand firmware reload\n");

	/* Set the FW error flag -- cleared on il_करोwn */
	set_bit(S_FW_ERROR, &il->status);
	wake_up(&il->रुको_command_queue);
	/*
	 * Keep the restart process from trying to send host
	 * commands by clearing the INIT status bit
	 */
	clear_bit(S_READY, &il->status);
	queue_work(il->workqueue, &il->restart);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(il_क्रमce_reset);

पूर्णांक
il_mac_change_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			क्रमागत nl80211_अगरtype newtype, bool newp2p)
अणु
	काष्ठा il_priv *il = hw->priv;
	पूर्णांक err;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: type %d, addr %pM newtype %d newp2p %d\n",
		    vअगर->type, vअगर->addr, newtype, newp2p);

	अगर (newp2p) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (!il->vअगर || !il_is_पढ़ोy_rf(il)) अणु
		/*
		 * Huh? But रुको ... this can maybe happen when
		 * we're in the middle of a firmware restart!
		 */
		err = -EBUSY;
		जाओ out;
	पूर्ण

	/* success */
	vअगर->type = newtype;
	vअगर->p2p = false;
	il->iw_mode = newtype;
	il_tearकरोwn_पूर्णांकerface(il, vअगर);
	err = 0;

out:
	D_MAC80211("leave err %d\n", err);
	mutex_unlock(&il->mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL(il_mac_change_पूर्णांकerface);

व्योम il_mac_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		  u32 queues, bool drop)
अणु
	काष्ठा il_priv *il = hw->priv;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(500);
	पूर्णांक i;

	mutex_lock(&il->mutex);
	D_MAC80211("enter\n");

	अगर (il->txq == शून्य)
		जाओ out;

	क्रम (i = 0; i < il->hw_params.max_txq_num; i++) अणु
		काष्ठा il_queue *q;

		अगर (i == il->cmd_queue)
			जारी;

		q = &il->txq[i].q;
		अगर (q->पढ़ो_ptr == q->ग_लिखो_ptr)
			जारी;

		अगर (समय_after(jअगरfies, समयout)) अणु
			IL_ERR("Failed to flush queue %d\n", q->id);
			अवरोध;
		पूर्ण

		msleep(20);
	पूर्ण
out:
	D_MAC80211("leave\n");
	mutex_unlock(&il->mutex);
पूर्ण
EXPORT_SYMBOL(il_mac_flush);

/*
 * On every watchकरोg tick we check (latest) समय stamp. If it करोes not
 * change during समयout period and queue is not empty we reset firmware.
 */
अटल पूर्णांक
il_check_stuck_queue(काष्ठा il_priv *il, पूर्णांक cnt)
अणु
	काष्ठा il_tx_queue *txq = &il->txq[cnt];
	काष्ठा il_queue *q = &txq->q;
	अचिन्हित दीर्घ समयout;
	अचिन्हित दीर्घ now = jअगरfies;
	पूर्णांक ret;

	अगर (q->पढ़ो_ptr == q->ग_लिखो_ptr) अणु
		txq->समय_stamp = now;
		वापस 0;
	पूर्ण

	समयout =
	    txq->समय_stamp +
	    msecs_to_jअगरfies(il->cfg->wd_समयout);

	अगर (समय_after(now, समयout)) अणु
		IL_ERR("Queue %d stuck for %u ms.\n", q->id,
		       jअगरfies_to_msecs(now - txq->समय_stamp));
		ret = il_क्रमce_reset(il, false);
		वापस (ret == -EAGAIN) ? 0 : 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Making watchकरोg tick be a quarter of समयout assure we will
 * discover the queue hung between समयout and 1.25*समयout
 */
#घोषणा IL_WD_TICK(समयout) ((समयout) / 4)

/*
 * Watchकरोg समयr callback, we check each tx queue क्रम stuck, अगर अगर hung
 * we reset the firmware. If everything is fine just rearm the समयr.
 */
व्योम
il_bg_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा il_priv *il = from_समयr(il, t, watchकरोg);
	पूर्णांक cnt;
	अचिन्हित दीर्घ समयout;

	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	समयout = il->cfg->wd_समयout;
	अगर (समयout == 0)
		वापस;

	/* monitor and check क्रम stuck cmd queue */
	अगर (il_check_stuck_queue(il, il->cmd_queue))
		वापस;

	/* monitor and check क्रम other stuck queues */
	क्रम (cnt = 0; cnt < il->hw_params.max_txq_num; cnt++) अणु
		/* skip as we alपढ़ोy checked the command queue */
		अगर (cnt == il->cmd_queue)
			जारी;
		अगर (il_check_stuck_queue(il, cnt))
			वापस;
	पूर्ण

	mod_समयr(&il->watchकरोg,
		  jअगरfies + msecs_to_jअगरfies(IL_WD_TICK(समयout)));
पूर्ण
EXPORT_SYMBOL(il_bg_watchकरोg);

व्योम
il_setup_watchकरोg(काष्ठा il_priv *il)
अणु
	अचिन्हित पूर्णांक समयout = il->cfg->wd_समयout;

	अगर (समयout)
		mod_समयr(&il->watchकरोg,
			  jअगरfies + msecs_to_jअगरfies(IL_WD_TICK(समयout)));
	अन्यथा
		del_समयr(&il->watchकरोg);
पूर्ण
EXPORT_SYMBOL(il_setup_watchकरोg);

/*
 * extended beacon समय क्रमmat
 * समय in usec will be changed पूर्णांकo a 32-bit value in extended:पूर्णांकernal क्रमmat
 * the extended part is the beacon counts
 * the पूर्णांकernal part is the समय in usec within one beacon पूर्णांकerval
 */
u32
il_usecs_to_beacons(काष्ठा il_priv *il, u32 usec, u32 beacon_पूर्णांकerval)
अणु
	u32 quot;
	u32 rem;
	u32 पूर्णांकerval = beacon_पूर्णांकerval * TIME_UNIT;

	अगर (!पूर्णांकerval || !usec)
		वापस 0;

	quot =
	    (usec /
	     पूर्णांकerval) & (il_beacon_समय_mask_high(il,
						   il->hw_params.
						   beacon_समय_प्रकारsf_bits) >> il->
			  hw_params.beacon_समय_प्रकारsf_bits);
	rem =
	    (usec % पूर्णांकerval) & il_beacon_समय_mask_low(il,
							il->hw_params.
							beacon_समय_प्रकारsf_bits);

	वापस (quot << il->hw_params.beacon_समय_प्रकारsf_bits) + rem;
पूर्ण
EXPORT_SYMBOL(il_usecs_to_beacons);

/* base is usually what we get from ucode with each received frame,
 * the same as HW समयr counter counting करोwn
 */
__le32
il_add_beacon_समय(काष्ठा il_priv *il, u32 base, u32 adकरोn,
		   u32 beacon_पूर्णांकerval)
अणु
	u32 base_low = base & il_beacon_समय_mask_low(il,
						      il->hw_params.
						      beacon_समय_प्रकारsf_bits);
	u32 adकरोn_low = adकरोn & il_beacon_समय_mask_low(il,
							il->hw_params.
							beacon_समय_प्रकारsf_bits);
	u32 पूर्णांकerval = beacon_पूर्णांकerval * TIME_UNIT;
	u32 res = (base & il_beacon_समय_mask_high(il,
						   il->hw_params.
						   beacon_समय_प्रकारsf_bits)) +
	    (adकरोn & il_beacon_समय_mask_high(il,
					      il->hw_params.
					      beacon_समय_प्रकारsf_bits));

	अगर (base_low > adकरोn_low)
		res += base_low - adकरोn_low;
	अन्यथा अगर (base_low < adकरोn_low) अणु
		res += पूर्णांकerval + base_low - adकरोn_low;
		res += (1 << il->hw_params.beacon_समय_प्रकारsf_bits);
	पूर्ण अन्यथा
		res += (1 << il->hw_params.beacon_समय_प्रकारsf_bits);

	वापस cpu_to_le32(res);
पूर्ण
EXPORT_SYMBOL(il_add_beacon_समय);

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक
il_pci_suspend(काष्ठा device *device)
अणु
	काष्ठा il_priv *il = dev_get_drvdata(device);

	/*
	 * This function is called when प्रणाली goes पूर्णांकo suspend state
	 * mac80211 will call il_mac_stop() from the mac80211 suspend function
	 * first but since il_mac_stop() has no knowledge of who the caller is,
	 * it will not call apm_ops.stop() to stop the DMA operation.
	 * Calling apm_ops.stop here to make sure we stop the DMA.
	 */
	il_apm_stop(il);

	वापस 0;
पूर्ण

अटल पूर्णांक
il_pci_resume(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा il_priv *il = pci_get_drvdata(pdev);
	bool hw_rfसमाप्त = false;

	/*
	 * We disable the RETRY_TIMEOUT रेजिस्टर (0x41) to keep
	 * PCI Tx retries from पूर्णांकerfering with C3 CPU state.
	 */
	pci_ग_लिखो_config_byte(pdev, PCI_CFG_RETRY_TIMEOUT, 0x00);

	il_enable_पूर्णांकerrupts(il);

	अगर (!(_il_rd(il, CSR_GP_CNTRL) & CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW))
		hw_rfसमाप्त = true;

	अगर (hw_rfसमाप्त)
		set_bit(S_RFKILL, &il->status);
	अन्यथा
		clear_bit(S_RFKILL, &il->status);

	wiphy_rfसमाप्त_set_hw_state(il->hw->wiphy, hw_rfसमाप्त);

	वापस 0;
पूर्ण

SIMPLE_DEV_PM_OPS(il_pm_ops, il_pci_suspend, il_pci_resume);
EXPORT_SYMBOL(il_pm_ops);

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल व्योम
il_update_qos(काष्ठा il_priv *il)
अणु
	अगर (test_bit(S_EXIT_PENDING, &il->status))
		वापस;

	il->qos_data.def_qos_parm.qos_flags = 0;

	अगर (il->qos_data.qos_active)
		il->qos_data.def_qos_parm.qos_flags |=
		    QOS_PARAM_FLG_UPDATE_EDCA_MSK;

	अगर (il->ht.enabled)
		il->qos_data.def_qos_parm.qos_flags |= QOS_PARAM_FLG_TGN_MSK;

	D_QOS("send QoS cmd with Qos active=%d FLAGS=0x%X\n",
	      il->qos_data.qos_active, il->qos_data.def_qos_parm.qos_flags);

	il_send_cmd_pdu_async(il, C_QOS_PARAM, माप(काष्ठा il_qosparam_cmd),
			      &il->qos_data.def_qos_parm, शून्य);
पूर्ण

/*
 * il_mac_config - mac80211 config callback
 */
पूर्णांक
il_mac_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा il_priv *il = hw->priv;
	स्थिर काष्ठा il_channel_info *ch_info;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा ieee80211_channel *channel = conf->chandef.chan;
	काष्ठा il_ht_config *ht_conf = &il->current_ht_config;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret = 0;
	u16 ch;
	पूर्णांक scan_active = 0;
	bool ht_changed = false;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: channel %d changed 0x%X\n", channel->hw_value,
		   changed);

	अगर (unlikely(test_bit(S_SCANNING, &il->status))) अणु
		scan_active = 1;
		D_MAC80211("scan active\n");
	पूर्ण

	अगर (changed &
	    (IEEE80211_CONF_CHANGE_SMPS | IEEE80211_CONF_CHANGE_CHANNEL)) अणु
		/* mac80211 uses अटल क्रम non-HT which is what we want */
		il->current_ht_config.smps = conf->smps_mode;

		/*
		 * Recalculate chain counts.
		 *
		 * If monitor mode is enabled then mac80211 will
		 * set up the SM PS mode to OFF अगर an HT channel is
		 * configured.
		 */
		अगर (il->ops->set_rxon_chain)
			il->ops->set_rxon_chain(il);
	पूर्ण

	/* during scanning mac80211 will delay channel setting until
	 * scan finish with changed = 0
	 */
	अगर (!changed || (changed & IEEE80211_CONF_CHANGE_CHANNEL)) अणु

		अगर (scan_active)
			जाओ set_ch_out;

		ch = channel->hw_value;
		ch_info = il_get_channel_info(il, channel->band, ch);
		अगर (!il_is_channel_valid(ch_info)) अणु
			D_MAC80211("leave - invalid channel\n");
			ret = -EINVAL;
			जाओ set_ch_out;
		पूर्ण

		अगर (il->iw_mode == NL80211_IFTYPE_ADHOC &&
		    !il_is_channel_ibss(ch_info)) अणु
			D_MAC80211("leave - not IBSS channel\n");
			ret = -EINVAL;
			जाओ set_ch_out;
		पूर्ण

		spin_lock_irqsave(&il->lock, flags);

		/* Configure HT40 channels */
		अगर (il->ht.enabled != conf_is_ht(conf)) अणु
			il->ht.enabled = conf_is_ht(conf);
			ht_changed = true;
		पूर्ण
		अगर (il->ht.enabled) अणु
			अगर (conf_is_ht40_minus(conf)) अणु
				il->ht.extension_chan_offset =
				    IEEE80211_HT_PARAM_CHA_SEC_BELOW;
				il->ht.is_40mhz = true;
			पूर्ण अन्यथा अगर (conf_is_ht40_plus(conf)) अणु
				il->ht.extension_chan_offset =
				    IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
				il->ht.is_40mhz = true;
			पूर्ण अन्यथा अणु
				il->ht.extension_chan_offset =
				    IEEE80211_HT_PARAM_CHA_SEC_NONE;
				il->ht.is_40mhz = false;
			पूर्ण
		पूर्ण अन्यथा
			il->ht.is_40mhz = false;

		/*
		 * Default to no protection. Protection mode will
		 * later be set from BSS config in il_ht_conf
		 */
		il->ht.protection = IEEE80211_HT_OP_MODE_PROTECTION_NONE;

		/* अगर we are चयनing from ht to 2.4 clear flags
		 * from any ht related info since 2.4 करोes not
		 * support ht */
		अगर ((le16_to_cpu(il->staging.channel) != ch))
			il->staging.flags = 0;

		il_set_rxon_channel(il, channel);
		il_set_rxon_ht(il, ht_conf);

		il_set_flags_क्रम_band(il, channel->band, il->vअगर);

		spin_unlock_irqrestore(&il->lock, flags);

		अगर (il->ops->update_bcast_stations)
			ret = il->ops->update_bcast_stations(il);

set_ch_out:
		/* The list of supported rates and rate mask can be dअगरferent
		 * क्रम each band; since the band may have changed, reset
		 * the rate mask to what mac80211 lists */
		il_set_rate(il);
	पूर्ण

	अगर (changed & (IEEE80211_CONF_CHANGE_PS | IEEE80211_CONF_CHANGE_IDLE)) अणु
		il->घातer_data.ps_disabled = !(conf->flags & IEEE80211_CONF_PS);
		अगर (!il->घातer_data.ps_disabled)
			IL_WARN_ONCE("Enabling power save might cause firmware crashes\n");
		ret = il_घातer_update_mode(il, false);
		अगर (ret)
			D_MAC80211("Error setting sleep level\n");
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_POWER) अणु
		D_MAC80211("TX Power old=%d new=%d\n", il->tx_घातer_user_lmt,
			   conf->घातer_level);

		il_set_tx_घातer(il, conf->घातer_level, false);
	पूर्ण

	अगर (!il_is_पढ़ोy(il)) अणु
		D_MAC80211("leave - not ready\n");
		जाओ out;
	पूर्ण

	अगर (scan_active)
		जाओ out;

	अगर (स_भेद(&il->active, &il->staging, माप(il->staging)))
		il_commit_rxon(il);
	अन्यथा
		D_INFO("Not re-sending same RXON configuration.\n");
	अगर (ht_changed)
		il_update_qos(il);

out:
	D_MAC80211("leave ret %d\n", ret);
	mutex_unlock(&il->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(il_mac_config);

व्योम
il_mac_reset_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा il_priv *il = hw->priv;
	अचिन्हित दीर्घ flags;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: type %d, addr %pM\n", vअगर->type, vअगर->addr);

	spin_lock_irqsave(&il->lock, flags);

	स_रखो(&il->current_ht_config, 0, माप(काष्ठा il_ht_config));

	/* new association get rid of ibss beacon skb */
	dev_kमुक्त_skb(il->beacon_skb);
	il->beacon_skb = शून्य;
	il->बारtamp = 0;

	spin_unlock_irqrestore(&il->lock, flags);

	il_scan_cancel_समयout(il, 100);
	अगर (!il_is_पढ़ोy_rf(il)) अणु
		D_MAC80211("leave - not ready\n");
		mutex_unlock(&il->mutex);
		वापस;
	पूर्ण

	/* we are restarting association process */
	il->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	il_commit_rxon(il);

	il_set_rate(il);

	D_MAC80211("leave\n");
	mutex_unlock(&il->mutex);
पूर्ण
EXPORT_SYMBOL(il_mac_reset_tsf);

अटल व्योम
il_ht_conf(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा il_ht_config *ht_conf = &il->current_ht_config;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;

	D_ASSOC("enter:\n");

	अगर (!il->ht.enabled)
		वापस;

	il->ht.protection =
	    bss_conf->ht_operation_mode & IEEE80211_HT_OP_MODE_PROTECTION;
	il->ht.non_gf_sta_present =
	    !!(bss_conf->
	       ht_operation_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);

	ht_conf->single_chain_sufficient = false;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		rcu_पढ़ो_lock();
		sta = ieee80211_find_sta(vअगर, bss_conf->bssid);
		अगर (sta) अणु
			काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
			पूर्णांक maxstreams;

			maxstreams =
			    (ht_cap->mcs.
			     tx_params & IEEE80211_HT_MCS_TX_MAX_STREAMS_MASK)
			    >> IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT;
			maxstreams += 1;

			अगर (ht_cap->mcs.rx_mask[1] == 0 &&
			    ht_cap->mcs.rx_mask[2] == 0)
				ht_conf->single_chain_sufficient = true;
			अगर (maxstreams <= 1)
				ht_conf->single_chain_sufficient = true;
		पूर्ण अन्यथा अणु
			/*
			 * If at all, this can only happen through a race
			 * when the AP disconnects us जबतक we're still
			 * setting up the connection, in that हाल mac80211
			 * will soon tell us about that.
			 */
			ht_conf->single_chain_sufficient = true;
		पूर्ण
		rcu_पढ़ो_unlock();
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		ht_conf->single_chain_sufficient = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	D_ASSOC("leave\n");
पूर्ण

अटल अंतरभूत व्योम
il_set_no_assoc(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर)
अणु
	/*
	 * inक्रमm the ucode that there is no दीर्घer an
	 * association and that no more packets should be
	 * sent
	 */
	il->staging.filter_flags &= ~RXON_FILTER_ASSOC_MSK;
	il->staging.assoc_id = 0;
	il_commit_rxon(il);
पूर्ण

अटल व्योम
il_beacon_update(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा il_priv *il = hw->priv;
	अचिन्हित दीर्घ flags;
	__le64 बारtamp;
	काष्ठा sk_buff *skb = ieee80211_beacon_get(hw, vअगर);

	अगर (!skb)
		वापस;

	D_MAC80211("enter\n");

	lockdep_निश्चित_held(&il->mutex);

	अगर (!il->beacon_enabled) अणु
		IL_ERR("update beacon with no beaconing enabled\n");
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	spin_lock_irqsave(&il->lock, flags);
	dev_kमुक्त_skb(il->beacon_skb);
	il->beacon_skb = skb;

	बारtamp = ((काष्ठा ieee80211_mgmt *)skb->data)->u.beacon.बारtamp;
	il->बारtamp = le64_to_cpu(बारtamp);

	D_MAC80211("leave\n");
	spin_unlock_irqrestore(&il->lock, flags);

	अगर (!il_is_पढ़ोy_rf(il)) अणु
		D_MAC80211("leave - RF not ready\n");
		वापस;
	पूर्ण

	il->ops->post_associate(il);
पूर्ण

व्योम
il_mac_bss_info_changed(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_bss_conf *bss_conf, u32 changes)
अणु
	काष्ठा il_priv *il = hw->priv;
	पूर्णांक ret;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: changes 0x%x\n", changes);

	अगर (!il_is_alive(il)) अणु
		D_MAC80211("leave - not alive\n");
		mutex_unlock(&il->mutex);
		वापस;
	पूर्ण

	अगर (changes & BSS_CHANGED_QOS) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&il->lock, flags);
		il->qos_data.qos_active = bss_conf->qos;
		il_update_qos(il);
		spin_unlock_irqrestore(&il->lock, flags);
	पूर्ण

	अगर (changes & BSS_CHANGED_BEACON_ENABLED) अणु
		/* FIXME: can we हटाओ beacon_enabled ? */
		अगर (vअगर->bss_conf.enable_beacon)
			il->beacon_enabled = true;
		अन्यथा
			il->beacon_enabled = false;
	पूर्ण

	अगर (changes & BSS_CHANGED_BSSID) अणु
		D_MAC80211("BSSID %pM\n", bss_conf->bssid);

		/*
		 * On passive channel we रुको with blocked queues to see अगर
		 * there is traffic on that channel. If no frame will be
		 * received (what is very unlikely since scan detects AP on
		 * that channel, but theoretically possible), mac80211 associate
		 * procedure will समय out and mac80211 will call us with शून्य
		 * bssid. We have to unblock queues on such condition.
		 */
		अगर (is_zero_ether_addr(bss_conf->bssid))
			il_wake_queues_by_reason(il, IL_STOP_REASON_PASSIVE);

		/*
		 * If there is currently a HW scan going on in the background,
		 * then we need to cancel it, otherwise someबार we are not
		 * able to authenticate (FIXME: why ?)
		 */
		अगर (il_scan_cancel_समयout(il, 100)) अणु
			D_MAC80211("leave - scan abort failed\n");
			mutex_unlock(&il->mutex);
			वापस;
		पूर्ण

		/* mac80211 only sets assoc when in STATION mode */
		स_नकल(il->staging.bssid_addr, bss_conf->bssid, ETH_ALEN);

		/* FIXME: currently needed in a few places */
		स_नकल(il->bssid, bss_conf->bssid, ETH_ALEN);
	पूर्ण

	/*
	 * This needs to be after setting the BSSID in हाल
	 * mac80211 decides to करो both changes at once because
	 * it will invoke post_associate.
	 */
	अगर (vअगर->type == NL80211_IFTYPE_ADHOC && (changes & BSS_CHANGED_BEACON))
		il_beacon_update(hw, vअगर);

	अगर (changes & BSS_CHANGED_ERP_PREAMBLE) अणु
		D_MAC80211("ERP_PREAMBLE %d\n", bss_conf->use_लघु_preamble);
		अगर (bss_conf->use_लघु_preamble)
			il->staging.flags |= RXON_FLG_SHORT_PREAMBLE_MSK;
		अन्यथा
			il->staging.flags &= ~RXON_FLG_SHORT_PREAMBLE_MSK;
	पूर्ण

	अगर (changes & BSS_CHANGED_ERP_CTS_PROT) अणु
		D_MAC80211("ERP_CTS %d\n", bss_conf->use_cts_prot);
		अगर (bss_conf->use_cts_prot && il->band != NL80211_BAND_5GHZ)
			il->staging.flags |= RXON_FLG_TGG_PROTECT_MSK;
		अन्यथा
			il->staging.flags &= ~RXON_FLG_TGG_PROTECT_MSK;
		अगर (bss_conf->use_cts_prot)
			il->staging.flags |= RXON_FLG_SELF_CTS_EN;
		अन्यथा
			il->staging.flags &= ~RXON_FLG_SELF_CTS_EN;
	पूर्ण

	अगर (changes & BSS_CHANGED_BASIC_RATES) अणु
		/* XXX use this inक्रमmation
		 *
		 * To करो that, हटाओ code from il_set_rate() and put something
		 * like this here:
		 *
		 अगर (A-band)
		 il->staging.ofdm_basic_rates =
		 bss_conf->basic_rates;
		 अन्यथा
		 il->staging.ofdm_basic_rates =
		 bss_conf->basic_rates >> 4;
		 il->staging.cck_basic_rates =
		 bss_conf->basic_rates & 0xF;
		 */
	पूर्ण

	अगर (changes & BSS_CHANGED_HT) अणु
		il_ht_conf(il, vअगर);

		अगर (il->ops->set_rxon_chain)
			il->ops->set_rxon_chain(il);
	पूर्ण

	अगर (changes & BSS_CHANGED_ASSOC) अणु
		D_MAC80211("ASSOC %d\n", bss_conf->assoc);
		अगर (bss_conf->assoc) अणु
			il->बारtamp = bss_conf->sync_tsf;

			अगर (!il_is_rfसमाप्त(il))
				il->ops->post_associate(il);
		पूर्ण अन्यथा
			il_set_no_assoc(il, vअगर);
	पूर्ण

	अगर (changes && il_is_associated(il) && bss_conf->aid) अणु
		D_MAC80211("Changes (%#x) while associated\n", changes);
		ret = il_send_rxon_assoc(il);
		अगर (!ret) अणु
			/* Sync active_rxon with latest change. */
			स_नकल((व्योम *)&il->active, &il->staging,
			       माप(काष्ठा il_rxon_cmd));
		पूर्ण
	पूर्ण

	अगर (changes & BSS_CHANGED_BEACON_ENABLED) अणु
		अगर (vअगर->bss_conf.enable_beacon) अणु
			स_नकल(il->staging.bssid_addr, bss_conf->bssid,
			       ETH_ALEN);
			स_नकल(il->bssid, bss_conf->bssid, ETH_ALEN);
			il->ops->config_ap(il);
		पूर्ण अन्यथा
			il_set_no_assoc(il, vअगर);
	पूर्ण

	अगर (changes & BSS_CHANGED_IBSS) अणु
		ret = il->ops->manage_ibss_station(il, vअगर,
						   bss_conf->ibss_joined);
		अगर (ret)
			IL_ERR("failed to %s IBSS station %pM\n",
			       bss_conf->ibss_joined ? "add" : "remove",
			       bss_conf->bssid);
	पूर्ण

	D_MAC80211("leave\n");
	mutex_unlock(&il->mutex);
पूर्ण
EXPORT_SYMBOL(il_mac_bss_info_changed);

irqवापस_t
il_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा il_priv *il = data;
	u32 पूर्णांकa, पूर्णांकa_mask;
	u32 पूर्णांकa_fh;
	अचिन्हित दीर्घ flags;
	अगर (!il)
		वापस IRQ_NONE;

	spin_lock_irqsave(&il->lock, flags);

	/* Disable (but करोn't clear!) पूर्णांकerrupts here to aव्योम
	 *    back-to-back ISRs and sporadic पूर्णांकerrupts from our NIC.
	 * If we have something to service, the tasklet will re-enable पूर्णांकs.
	 * If we *करोn't* have something, we'll re-enable beक्रमe leaving here. */
	पूर्णांकa_mask = _il_rd(il, CSR_INT_MASK);	/* just क्रम debug */
	_il_wr(il, CSR_INT_MASK, 0x00000000);

	/* Discover which पूर्णांकerrupts are active/pending */
	पूर्णांकa = _il_rd(il, CSR_INT);
	पूर्णांकa_fh = _il_rd(il, CSR_FH_INT_STATUS);

	/* Ignore पूर्णांकerrupt अगर there's nothing in NIC to service.
	 * This may be due to IRQ shared with another device,
	 * or due to sporadic पूर्णांकerrupts thrown from our NIC. */
	अगर (!पूर्णांकa && !पूर्णांकa_fh) अणु
		D_ISR("Ignore interrupt, inta == 0, inta_fh == 0\n");
		जाओ none;
	पूर्ण

	अगर (पूर्णांकa == 0xFFFFFFFF || (पूर्णांकa & 0xFFFFFFF0) == 0xa5a5a5a0) अणु
		/* Hardware disappeared. It might have alपढ़ोy उठाओd
		 * an पूर्णांकerrupt */
		IL_WARN("HARDWARE GONE?? INTA == 0x%08x\n", पूर्णांकa);
		जाओ unplugged;
	पूर्ण

	D_ISR("ISR inta 0x%08x, enabled 0x%08x, fh 0x%08x\n", पूर्णांकa, पूर्णांकa_mask,
	      पूर्णांकa_fh);

	पूर्णांकa &= ~CSR_INT_BIT_SCD;

	/* il_irq_tasklet() will service पूर्णांकerrupts and re-enable them */
	अगर (likely(पूर्णांकa || पूर्णांकa_fh))
		tasklet_schedule(&il->irq_tasklet);

unplugged:
	spin_unlock_irqrestore(&il->lock, flags);
	वापस IRQ_HANDLED;

none:
	/* re-enable पूर्णांकerrupts here since we करोn't have anything to service. */
	/* only Re-enable अगर disabled by irq */
	अगर (test_bit(S_INT_ENABLED, &il->status))
		il_enable_पूर्णांकerrupts(il);
	spin_unlock_irqrestore(&il->lock, flags);
	वापस IRQ_NONE;
पूर्ण
EXPORT_SYMBOL(il_isr);

/*
 *  il_tx_cmd_protection: Set rts/cts. 3945 and 4965 only share this
 *  function.
 */
व्योम
il_tx_cmd_protection(काष्ठा il_priv *il, काष्ठा ieee80211_tx_info *info,
		     __le16 fc, __le32 *tx_flags)
अणु
	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS) अणु
		*tx_flags |= TX_CMD_FLG_RTS_MSK;
		*tx_flags &= ~TX_CMD_FLG_CTS_MSK;
		*tx_flags |= TX_CMD_FLG_FULL_TXOP_PROT_MSK;

		अगर (!ieee80211_is_mgmt(fc))
			वापस;

		चयन (fc & cpu_to_le16(IEEE80211_FCTL_STYPE)) अणु
		हाल cpu_to_le16(IEEE80211_STYPE_AUTH):
		हाल cpu_to_le16(IEEE80211_STYPE_DEAUTH):
		हाल cpu_to_le16(IEEE80211_STYPE_ASSOC_REQ):
		हाल cpu_to_le16(IEEE80211_STYPE_REASSOC_REQ):
			*tx_flags &= ~TX_CMD_FLG_RTS_MSK;
			*tx_flags |= TX_CMD_FLG_CTS_MSK;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (info->control.rates[0].
		   flags & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
		*tx_flags &= ~TX_CMD_FLG_RTS_MSK;
		*tx_flags |= TX_CMD_FLG_CTS_MSK;
		*tx_flags |= TX_CMD_FLG_FULL_TXOP_PROT_MSK;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(il_tx_cmd_protection);
