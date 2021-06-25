<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2005-2007  Kristian Hoegsberg <krh@bitplanet.net>
 */

#समावेश <linux/bug.h>
#समावेश <linux/completion.h>
#समावेश <linux/crc-itu-t.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "core.h"

#घोषणा define_fw_prपूर्णांकk_level(func, kern_level)		\
व्योम func(स्थिर काष्ठा fw_card *card, स्थिर अक्षर *fmt, ...)	\
अणु								\
	काष्ठा va_क्रमmat vaf;					\
	बहु_सूची args;						\
								\
	बहु_शुरू(args, fmt);					\
	vaf.fmt = fmt;						\
	vaf.va = &args;						\
	prपूर्णांकk(kern_level KBUILD_MODNAME " %s: %pV",		\
	       dev_name(card->device), &vaf);			\
	बहु_पूर्ण(args);						\
पूर्ण
define_fw_prपूर्णांकk_level(fw_err, KERN_ERR);
define_fw_prपूर्णांकk_level(fw_notice, KERN_NOTICE);

पूर्णांक fw_compute_block_crc(__be32 *block)
अणु
	पूर्णांक length;
	u16 crc;

	length = (be32_to_cpu(block[0]) >> 16) & 0xff;
	crc = crc_itu_t(0, (u8 *)&block[1], length * 4);
	*block |= cpu_to_be32(crc);

	वापस length;
पूर्ण

अटल DEFINE_MUTEX(card_mutex);
अटल LIST_HEAD(card_list);

अटल LIST_HEAD(descriptor_list);
अटल पूर्णांक descriptor_count;

अटल __be32 पंचांगp_config_rom[256];
/* ROM header, bus info block, root dir header, capabilities = 7 quadlets */
अटल माप_प्रकार config_rom_length = 1 + 4 + 1 + 1;

#घोषणा BIB_CRC(v)		((v) <<  0)
#घोषणा BIB_CRC_LENGTH(v)	((v) << 16)
#घोषणा BIB_INFO_LENGTH(v)	((v) << 24)
#घोषणा BIB_BUS_NAME		0x31333934 /* "1394" */
#घोषणा BIB_LINK_SPEED(v)	((v) <<  0)
#घोषणा BIB_GENERATION(v)	((v) <<  4)
#घोषणा BIB_MAX_ROM(v)		((v) <<  8)
#घोषणा BIB_MAX_RECEIVE(v)	((v) << 12)
#घोषणा BIB_CYC_CLK_ACC(v)	((v) << 16)
#घोषणा BIB_PMC			((1) << 27)
#घोषणा BIB_BMC			((1) << 28)
#घोषणा BIB_ISC			((1) << 29)
#घोषणा BIB_CMC			((1) << 30)
#घोषणा BIB_IRMC		((1) << 31)
#घोषणा NODE_CAPABILITIES	0x0c0083c0 /* per IEEE 1394 clause 8.3.2.6.5.2 */

/*
 * IEEE-1394 specअगरies a शेष SPLIT_TIMEOUT value of 800 cycles (100 ms),
 * but we have to make it दीर्घer because there are many devices whose firmware
 * is just too slow क्रम that.
 */
#घोषणा DEFAULT_SPLIT_TIMEOUT	(2 * 8000)

#घोषणा CANON_OUI		0x000085

अटल व्योम generate_config_rom(काष्ठा fw_card *card, __be32 *config_rom)
अणु
	काष्ठा fw_descriptor *desc;
	पूर्णांक i, j, k, length;

	/*
	 * Initialize contents of config rom buffer.  On the OHCI
	 * controller, block पढ़ोs to the config rom accesses the host
	 * memory, but quadlet पढ़ो access the hardware bus info block
	 * रेजिस्टरs.  That's just crack, but it means we should make
	 * sure the contents of bus info block in host memory matches
	 * the version stored in the OHCI रेजिस्टरs.
	 */

	config_rom[0] = cpu_to_be32(
		BIB_CRC_LENGTH(4) | BIB_INFO_LENGTH(4) | BIB_CRC(0));
	config_rom[1] = cpu_to_be32(BIB_BUS_NAME);
	config_rom[2] = cpu_to_be32(
		BIB_LINK_SPEED(card->link_speed) |
		BIB_GENERATION(card->config_rom_generation++ % 14 + 2) |
		BIB_MAX_ROM(2) |
		BIB_MAX_RECEIVE(card->max_receive) |
		BIB_BMC | BIB_ISC | BIB_CMC | BIB_IRMC);
	config_rom[3] = cpu_to_be32(card->guid >> 32);
	config_rom[4] = cpu_to_be32(card->guid);

	/* Generate root directory. */
	config_rom[6] = cpu_to_be32(NODE_CAPABILITIES);
	i = 7;
	j = 7 + descriptor_count;

	/* Generate root directory entries क्रम descriptors. */
	list_क्रम_each_entry (desc, &descriptor_list, link) अणु
		अगर (desc->immediate > 0)
			config_rom[i++] = cpu_to_be32(desc->immediate);
		config_rom[i] = cpu_to_be32(desc->key | (j - i));
		i++;
		j += desc->length;
	पूर्ण

	/* Update root directory length. */
	config_rom[5] = cpu_to_be32((i - 5 - 1) << 16);

	/* End of root directory, now copy in descriptors. */
	list_क्रम_each_entry (desc, &descriptor_list, link) अणु
		क्रम (k = 0; k < desc->length; k++)
			config_rom[i + k] = cpu_to_be32(desc->data[k]);
		i += desc->length;
	पूर्ण

	/* Calculate CRCs क्रम all blocks in the config rom.  This
	 * assumes that CRC length and info length are identical क्रम
	 * the bus info block, which is always the हाल क्रम this
	 * implementation. */
	क्रम (i = 0; i < j; i += length + 1)
		length = fw_compute_block_crc(config_rom + i);

	WARN_ON(j != config_rom_length);
पूर्ण

अटल व्योम update_config_roms(व्योम)
अणु
	काष्ठा fw_card *card;

	list_क्रम_each_entry (card, &card_list, link) अणु
		generate_config_rom(card, पंचांगp_config_rom);
		card->driver->set_config_rom(card, पंचांगp_config_rom,
					     config_rom_length);
	पूर्ण
पूर्ण

अटल माप_प्रकार required_space(काष्ठा fw_descriptor *desc)
अणु
	/* descriptor + entry पूर्णांकo root dir + optional immediate entry */
	वापस desc->length + 1 + (desc->immediate > 0 ? 1 : 0);
पूर्ण

पूर्णांक fw_core_add_descriptor(काष्ठा fw_descriptor *desc)
अणु
	माप_प्रकार i;
	पूर्णांक ret;

	/*
	 * Check descriptor is valid; the length of all blocks in the
	 * descriptor has to add up to exactly the length of the
	 * block.
	 */
	i = 0;
	जबतक (i < desc->length)
		i += (desc->data[i] >> 16) + 1;

	अगर (i != desc->length)
		वापस -EINVAL;

	mutex_lock(&card_mutex);

	अगर (config_rom_length + required_space(desc) > 256) अणु
		ret = -EBUSY;
	पूर्ण अन्यथा अणु
		list_add_tail(&desc->link, &descriptor_list);
		config_rom_length += required_space(desc);
		descriptor_count++;
		अगर (desc->immediate > 0)
			descriptor_count++;
		update_config_roms();
		ret = 0;
	पूर्ण

	mutex_unlock(&card_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fw_core_add_descriptor);

व्योम fw_core_हटाओ_descriptor(काष्ठा fw_descriptor *desc)
अणु
	mutex_lock(&card_mutex);

	list_del(&desc->link);
	config_rom_length -= required_space(desc);
	descriptor_count--;
	अगर (desc->immediate > 0)
		descriptor_count--;
	update_config_roms();

	mutex_unlock(&card_mutex);
पूर्ण
EXPORT_SYMBOL(fw_core_हटाओ_descriptor);

अटल पूर्णांक reset_bus(काष्ठा fw_card *card, bool लघु_reset)
अणु
	पूर्णांक reg = लघु_reset ? 5 : 1;
	पूर्णांक bit = लघु_reset ? PHY_BUS_SHORT_RESET : PHY_BUS_RESET;

	वापस card->driver->update_phy_reg(card, reg, 0, bit);
पूर्ण

व्योम fw_schedule_bus_reset(काष्ठा fw_card *card, bool delayed, bool लघु_reset)
अणु
	/* We करोn't try hard to sort out requests of दीर्घ vs. लघु resets. */
	card->br_लघु = लघु_reset;

	/* Use an arbitrary लघु delay to combine multiple reset requests. */
	fw_card_get(card);
	अगर (!queue_delayed_work(fw_workqueue, &card->br_work,
				delayed ? DIV_ROUND_UP(HZ, 100) : 0))
		fw_card_put(card);
पूर्ण
EXPORT_SYMBOL(fw_schedule_bus_reset);

अटल व्योम br_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_card *card = container_of(work, काष्ठा fw_card, br_work.work);

	/* Delay क्रम 2s after last reset per IEEE 1394 clause 8.2.1. */
	अगर (card->reset_jअगरfies != 0 &&
	    समय_beक्रमe64(get_jअगरfies_64(), card->reset_jअगरfies + 2 * HZ)) अणु
		अगर (!queue_delayed_work(fw_workqueue, &card->br_work, 2 * HZ))
			fw_card_put(card);
		वापस;
	पूर्ण

	fw_send_phy_config(card, FW_PHY_CONFIG_NO_NODE_ID, card->generation,
			   FW_PHY_CONFIG_CURRENT_GAP_COUNT);
	reset_bus(card, card->br_लघु);
	fw_card_put(card);
पूर्ण

अटल व्योम allocate_broadcast_channel(काष्ठा fw_card *card, पूर्णांक generation)
अणु
	पूर्णांक channel, bandwidth = 0;

	अगर (!card->broadcast_channel_allocated) अणु
		fw_iso_resource_manage(card, generation, 1ULL << 31,
				       &channel, &bandwidth, true);
		अगर (channel != 31) अणु
			fw_notice(card, "failed to allocate broadcast channel\n");
			वापस;
		पूर्ण
		card->broadcast_channel_allocated = true;
	पूर्ण

	device_क्रम_each_child(card->device, (व्योम *)(दीर्घ)generation,
			      fw_device_set_broadcast_channel);
पूर्ण

अटल स्थिर अक्षर gap_count_table[] = अणु
	63, 5, 7, 8, 10, 13, 16, 18, 21, 24, 26, 29, 32, 35, 37, 40
पूर्ण;

व्योम fw_schedule_bm_work(काष्ठा fw_card *card, अचिन्हित दीर्घ delay)
अणु
	fw_card_get(card);
	अगर (!schedule_delayed_work(&card->bm_work, delay))
		fw_card_put(card);
पूर्ण

अटल व्योम bm_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fw_card *card = container_of(work, काष्ठा fw_card, bm_work.work);
	काष्ठा fw_device *root_device, *irm_device;
	काष्ठा fw_node *root_node;
	पूर्णांक root_id, new_root_id, irm_id, bm_id, local_id;
	पूर्णांक gap_count, generation, grace, rcode;
	bool करो_reset = false;
	bool root_device_is_running;
	bool root_device_is_cmc;
	bool irm_is_1394_1995_only;
	bool keep_this_irm;
	__be32 transaction_data[2];

	spin_lock_irq(&card->lock);

	अगर (card->local_node == शून्य) अणु
		spin_unlock_irq(&card->lock);
		जाओ out_put_card;
	पूर्ण

	generation = card->generation;

	root_node = card->root_node;
	fw_node_get(root_node);
	root_device = root_node->data;
	root_device_is_running = root_device &&
			atomic_पढ़ो(&root_device->state) == FW_DEVICE_RUNNING;
	root_device_is_cmc = root_device && root_device->cmc;

	irm_device = card->irm_node->data;
	irm_is_1394_1995_only = irm_device && irm_device->config_rom &&
			(irm_device->config_rom[2] & 0x000000f0) == 0;

	/* Canon MV5i works unreliably अगर it is not root node. */
	keep_this_irm = irm_device && irm_device->config_rom &&
			irm_device->config_rom[3] >> 8 == CANON_OUI;

	root_id  = root_node->node_id;
	irm_id   = card->irm_node->node_id;
	local_id = card->local_node->node_id;

	grace = समय_after64(get_jअगरfies_64(),
			     card->reset_jअगरfies + DIV_ROUND_UP(HZ, 8));

	अगर ((is_next_generation(generation, card->bm_generation) &&
	     !card->bm_abdicate) ||
	    (card->bm_generation != generation && grace)) अणु
		/*
		 * This first step is to figure out who is IRM and
		 * then try to become bus manager.  If the IRM is not
		 * well defined (e.g. करोes not have an active link
		 * layer or करोes not responds to our lock request, we
		 * will have to करो a little vigilante bus management.
		 * In that हाल, we करो a जाओ पूर्णांकo the gap count logic
		 * so that when we करो the reset, we still optimize the
		 * gap count.  That could well save a reset in the
		 * next generation.
		 */

		अगर (!card->irm_node->link_on) अणु
			new_root_id = local_id;
			fw_notice(card, "%s, making local node (%02x) root\n",
				  "IRM has link off", new_root_id);
			जाओ pick_me;
		पूर्ण

		अगर (irm_is_1394_1995_only && !keep_this_irm) अणु
			new_root_id = local_id;
			fw_notice(card, "%s, making local node (%02x) root\n",
				  "IRM is not 1394a compliant", new_root_id);
			जाओ pick_me;
		पूर्ण

		transaction_data[0] = cpu_to_be32(0x3f);
		transaction_data[1] = cpu_to_be32(local_id);

		spin_unlock_irq(&card->lock);

		rcode = fw_run_transaction(card, TCODE_LOCK_COMPARE_SWAP,
				irm_id, generation, SCODE_100,
				CSR_REGISTER_BASE + CSR_BUS_MANAGER_ID,
				transaction_data, 8);

		अगर (rcode == RCODE_GENERATION)
			/* Another bus reset, BM work has been rescheduled. */
			जाओ out;

		bm_id = be32_to_cpu(transaction_data[0]);

		spin_lock_irq(&card->lock);
		अगर (rcode == RCODE_COMPLETE && generation == card->generation)
			card->bm_node_id =
			    bm_id == 0x3f ? local_id : 0xffc0 | bm_id;
		spin_unlock_irq(&card->lock);

		अगर (rcode == RCODE_COMPLETE && bm_id != 0x3f) अणु
			/* Somebody अन्यथा is BM.  Only act as IRM. */
			अगर (local_id == irm_id)
				allocate_broadcast_channel(card, generation);

			जाओ out;
		पूर्ण

		अगर (rcode == RCODE_SEND_ERROR) अणु
			/*
			 * We have been unable to send the lock request due to
			 * some local problem.  Let's try again later and hope
			 * that the problem has gone away by then.
			 */
			fw_schedule_bm_work(card, DIV_ROUND_UP(HZ, 8));
			जाओ out;
		पूर्ण

		spin_lock_irq(&card->lock);

		अगर (rcode != RCODE_COMPLETE && !keep_this_irm) अणु
			/*
			 * The lock request failed, maybe the IRM
			 * isn't really IRM capable after all. Let's
			 * करो a bus reset and pick the local node as
			 * root, and thus, IRM.
			 */
			new_root_id = local_id;
			fw_notice(card, "BM lock failed (%s), making local node (%02x) root\n",
				  fw_rcode_string(rcode), new_root_id);
			जाओ pick_me;
		पूर्ण
	पूर्ण अन्यथा अगर (card->bm_generation != generation) अणु
		/*
		 * We weren't BM in the last generation, and the last
		 * bus reset is less than 125ms ago.  Reschedule this job.
		 */
		spin_unlock_irq(&card->lock);
		fw_schedule_bm_work(card, DIV_ROUND_UP(HZ, 8));
		जाओ out;
	पूर्ण

	/*
	 * We're bus manager क्रम this generation, so next step is to
	 * make sure we have an active cycle master and करो gap count
	 * optimization.
	 */
	card->bm_generation = generation;

	अगर (root_device == शून्य) अणु
		/*
		 * Either link_on is false, or we failed to पढ़ो the
		 * config rom.  In either हाल, pick another root.
		 */
		new_root_id = local_id;
	पूर्ण अन्यथा अगर (!root_device_is_running) अणु
		/*
		 * If we haven't probed this device yet, bail out now
		 * and let's try again once that's करोne.
		 */
		spin_unlock_irq(&card->lock);
		जाओ out;
	पूर्ण अन्यथा अगर (root_device_is_cmc) अणु
		/*
		 * We will send out a क्रमce root packet क्रम this
		 * node as part of the gap count optimization.
		 */
		new_root_id = root_id;
	पूर्ण अन्यथा अणु
		/*
		 * Current root has an active link layer and we
		 * successfully पढ़ो the config rom, but it's not
		 * cycle master capable.
		 */
		new_root_id = local_id;
	पूर्ण

 pick_me:
	/*
	 * Pick a gap count from 1394a table E-1.  The table करोesn't cover
	 * the typically much larger 1394b beta repeater delays though.
	 */
	अगर (!card->beta_repeaters_present &&
	    root_node->max_hops < ARRAY_SIZE(gap_count_table))
		gap_count = gap_count_table[root_node->max_hops];
	अन्यथा
		gap_count = 63;

	/*
	 * Finally, figure out अगर we should करो a reset or not.  If we have
	 * करोne less than 5 resets with the same physical topology and we
	 * have either a new root or a new gap count setting, let's करो it.
	 */

	अगर (card->bm_retries++ < 5 &&
	    (card->gap_count != gap_count || new_root_id != root_id))
		करो_reset = true;

	spin_unlock_irq(&card->lock);

	अगर (करो_reset) अणु
		fw_notice(card, "phy config: new root=%x, gap_count=%d\n",
			  new_root_id, gap_count);
		fw_send_phy_config(card, new_root_id, generation, gap_count);
		reset_bus(card, true);
		/* Will allocate broadcast channel after the reset. */
		जाओ out;
	पूर्ण

	अगर (root_device_is_cmc) अणु
		/*
		 * Make sure that the cycle master sends cycle start packets.
		 */
		transaction_data[0] = cpu_to_be32(CSR_STATE_BIT_CMSTR);
		rcode = fw_run_transaction(card, TCODE_WRITE_QUADLET_REQUEST,
				root_id, generation, SCODE_100,
				CSR_REGISTER_BASE + CSR_STATE_SET,
				transaction_data, 4);
		अगर (rcode == RCODE_GENERATION)
			जाओ out;
	पूर्ण

	अगर (local_id == irm_id)
		allocate_broadcast_channel(card, generation);

 out:
	fw_node_put(root_node);
 out_put_card:
	fw_card_put(card);
पूर्ण

व्योम fw_card_initialize(काष्ठा fw_card *card,
			स्थिर काष्ठा fw_card_driver *driver,
			काष्ठा device *device)
अणु
	अटल atomic_t index = ATOMIC_INIT(-1);

	card->index = atomic_inc_वापस(&index);
	card->driver = driver;
	card->device = device;
	card->current_tlabel = 0;
	card->tlabel_mask = 0;
	card->split_समयout_hi = DEFAULT_SPLIT_TIMEOUT / 8000;
	card->split_समयout_lo = (DEFAULT_SPLIT_TIMEOUT % 8000) << 19;
	card->split_समयout_cycles = DEFAULT_SPLIT_TIMEOUT;
	card->split_समयout_jअगरfies =
			DIV_ROUND_UP(DEFAULT_SPLIT_TIMEOUT * HZ, 8000);
	card->color = 0;
	card->broadcast_channel = BROADCAST_CHANNEL_INITIAL;

	kref_init(&card->kref);
	init_completion(&card->करोne);
	INIT_LIST_HEAD(&card->transaction_list);
	INIT_LIST_HEAD(&card->phy_receiver_list);
	spin_lock_init(&card->lock);

	card->local_node = शून्य;

	INIT_DELAYED_WORK(&card->br_work, br_work);
	INIT_DELAYED_WORK(&card->bm_work, bm_work);
पूर्ण
EXPORT_SYMBOL(fw_card_initialize);

पूर्णांक fw_card_add(काष्ठा fw_card *card,
		u32 max_receive, u32 link_speed, u64 guid)
अणु
	पूर्णांक ret;

	card->max_receive = max_receive;
	card->link_speed = link_speed;
	card->guid = guid;

	mutex_lock(&card_mutex);

	generate_config_rom(card, पंचांगp_config_rom);
	ret = card->driver->enable(card, पंचांगp_config_rom, config_rom_length);
	अगर (ret == 0)
		list_add_tail(&card->link, &card_list);

	mutex_unlock(&card_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fw_card_add);

/*
 * The next few functions implement a dummy driver that is used once a card
 * driver shuts करोwn an fw_card.  This allows the driver to cleanly unload,
 * as all IO to the card will be handled (and failed) by the dummy driver
 * instead of calling पूर्णांकo the module.  Only functions क्रम iso context
 * shutकरोwn still need to be provided by the card driver.
 *
 * .पढ़ो/ग_लिखो_csr() should never be called anymore after the dummy driver
 * was bound since they are only used within request handler context.
 * .set_config_rom() is never called since the card is taken out of card_list
 * beक्रमe चयनing to the dummy driver.
 */

अटल पूर्णांक dummy_पढ़ो_phy_reg(काष्ठा fw_card *card, पूर्णांक address)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक dummy_update_phy_reg(काष्ठा fw_card *card, पूर्णांक address,
				पूर्णांक clear_bits, पूर्णांक set_bits)
अणु
	वापस -ENODEV;
पूर्ण

अटल व्योम dummy_send_request(काष्ठा fw_card *card, काष्ठा fw_packet *packet)
अणु
	packet->callback(packet, card, RCODE_CANCELLED);
पूर्ण

अटल व्योम dummy_send_response(काष्ठा fw_card *card, काष्ठा fw_packet *packet)
अणु
	packet->callback(packet, card, RCODE_CANCELLED);
पूर्ण

अटल पूर्णांक dummy_cancel_packet(काष्ठा fw_card *card, काष्ठा fw_packet *packet)
अणु
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक dummy_enable_phys_dma(काष्ठा fw_card *card,
				 पूर्णांक node_id, पूर्णांक generation)
अणु
	वापस -ENODEV;
पूर्ण

अटल काष्ठा fw_iso_context *dummy_allocate_iso_context(काष्ठा fw_card *card,
				पूर्णांक type, पूर्णांक channel, माप_प्रकार header_size)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल पूर्णांक dummy_start_iso(काष्ठा fw_iso_context *ctx,
			   s32 cycle, u32 sync, u32 tags)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक dummy_set_iso_channels(काष्ठा fw_iso_context *ctx, u64 *channels)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक dummy_queue_iso(काष्ठा fw_iso_context *ctx, काष्ठा fw_iso_packet *p,
			   काष्ठा fw_iso_buffer *buffer, अचिन्हित दीर्घ payload)
अणु
	वापस -ENODEV;
पूर्ण

अटल व्योम dummy_flush_queue_iso(काष्ठा fw_iso_context *ctx)
अणु
पूर्ण

अटल पूर्णांक dummy_flush_iso_completions(काष्ठा fw_iso_context *ctx)
अणु
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा fw_card_driver dummy_driver_ढाँचा = अणु
	.पढ़ो_phy_reg		= dummy_पढ़ो_phy_reg,
	.update_phy_reg		= dummy_update_phy_reg,
	.send_request		= dummy_send_request,
	.send_response		= dummy_send_response,
	.cancel_packet		= dummy_cancel_packet,
	.enable_phys_dma	= dummy_enable_phys_dma,
	.allocate_iso_context	= dummy_allocate_iso_context,
	.start_iso		= dummy_start_iso,
	.set_iso_channels	= dummy_set_iso_channels,
	.queue_iso		= dummy_queue_iso,
	.flush_queue_iso	= dummy_flush_queue_iso,
	.flush_iso_completions	= dummy_flush_iso_completions,
पूर्ण;

व्योम fw_card_release(काष्ठा kref *kref)
अणु
	काष्ठा fw_card *card = container_of(kref, काष्ठा fw_card, kref);

	complete(&card->करोne);
पूर्ण
EXPORT_SYMBOL_GPL(fw_card_release);

व्योम fw_core_हटाओ_card(काष्ठा fw_card *card)
अणु
	काष्ठा fw_card_driver dummy_driver = dummy_driver_ढाँचा;

	card->driver->update_phy_reg(card, 4,
				     PHY_LINK_ACTIVE | PHY_CONTENDER, 0);
	fw_schedule_bus_reset(card, false, true);

	mutex_lock(&card_mutex);
	list_del_init(&card->link);
	mutex_unlock(&card_mutex);

	/* Switch off most of the card driver पूर्णांकerface. */
	dummy_driver.मुक्त_iso_context	= card->driver->मुक्त_iso_context;
	dummy_driver.stop_iso		= card->driver->stop_iso;
	card->driver = &dummy_driver;

	fw_destroy_nodes(card);

	/* Wait क्रम all users, especially device workqueue jobs, to finish. */
	fw_card_put(card);
	रुको_क्रम_completion(&card->करोne);

	WARN_ON(!list_empty(&card->transaction_list));
पूर्ण
EXPORT_SYMBOL(fw_core_हटाओ_card);
