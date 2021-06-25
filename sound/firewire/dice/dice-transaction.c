<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * dice_transaction.c - a part of driver क्रम Dice based devices
 *
 * Copyright (c) Clemens Ladisch
 * Copyright (c) 2014 Takashi Sakamoto
 */

#समावेश "dice.h"

अटल u64 get_subaddr(काष्ठा snd_dice *dice, क्रमागत snd_dice_addr_type type,
		       u64 offset)
अणु
	चयन (type) अणु
	हाल SND_DICE_ADDR_TYPE_TX:
		offset += dice->tx_offset;
		अवरोध;
	हाल SND_DICE_ADDR_TYPE_RX:
		offset += dice->rx_offset;
		अवरोध;
	हाल SND_DICE_ADDR_TYPE_SYNC:
		offset += dice->sync_offset;
		अवरोध;
	हाल SND_DICE_ADDR_TYPE_RSRV:
		offset += dice->rsrv_offset;
		अवरोध;
	हाल SND_DICE_ADDR_TYPE_GLOBAL:
	शेष:
		offset += dice->global_offset;
		अवरोध;
	पूर्ण
	offset += DICE_PRIVATE_SPACE;
	वापस offset;
पूर्ण

पूर्णांक snd_dice_transaction_ग_लिखो(काष्ठा snd_dice *dice,
			       क्रमागत snd_dice_addr_type type,
			       अचिन्हित पूर्णांक offset, व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस snd_fw_transaction(dice->unit,
				  (len == 4) ? TCODE_WRITE_QUADLET_REQUEST :
					       TCODE_WRITE_BLOCK_REQUEST,
				  get_subaddr(dice, type, offset), buf, len, 0);
पूर्ण

पूर्णांक snd_dice_transaction_पढ़ो(काष्ठा snd_dice *dice,
			      क्रमागत snd_dice_addr_type type, अचिन्हित पूर्णांक offset,
			      व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस snd_fw_transaction(dice->unit,
				  (len == 4) ? TCODE_READ_QUADLET_REQUEST :
					       TCODE_READ_BLOCK_REQUEST,
				  get_subaddr(dice, type, offset), buf, len, 0);
पूर्ण

अटल अचिन्हित पूर्णांक get_घड़ी_info(काष्ठा snd_dice *dice, __be32 *info)
अणु
	वापस snd_dice_transaction_पढ़ो_global(dice, GLOBAL_CLOCK_SELECT,
						info, 4);
पूर्ण

पूर्णांक snd_dice_transaction_get_घड़ी_source(काष्ठा snd_dice *dice,
					  अचिन्हित पूर्णांक *source)
अणु
	__be32 info;
	पूर्णांक err;

	err = get_घड़ी_info(dice, &info);
	अगर (err >= 0)
		*source = be32_to_cpu(info) & CLOCK_SOURCE_MASK;

	वापस err;
पूर्ण

पूर्णांक snd_dice_transaction_get_rate(काष्ठा snd_dice *dice, अचिन्हित पूर्णांक *rate)
अणु
	__be32 info;
	अचिन्हित पूर्णांक index;
	पूर्णांक err;

	err = get_घड़ी_info(dice, &info);
	अगर (err < 0)
		जाओ end;

	index = (be32_to_cpu(info) & CLOCK_RATE_MASK) >> CLOCK_RATE_SHIFT;
	अगर (index >= SND_DICE_RATES_COUNT) अणु
		err = -ENOSYS;
		जाओ end;
	पूर्ण

	*rate = snd_dice_rates[index];
end:
	वापस err;
पूर्ण

पूर्णांक snd_dice_transaction_set_enable(काष्ठा snd_dice *dice)
अणु
	__be32 value;
	पूर्णांक err = 0;

	अगर (dice->global_enabled)
		जाओ end;

	value = cpu_to_be32(1);
	err = snd_fw_transaction(dice->unit, TCODE_WRITE_QUADLET_REQUEST,
				 get_subaddr(dice, SND_DICE_ADDR_TYPE_GLOBAL,
					     GLOBAL_ENABLE),
				 &value, 4,
				 FW_FIXED_GENERATION | dice->owner_generation);
	अगर (err < 0)
		जाओ end;

	dice->global_enabled = true;
end:
	वापस err;
पूर्ण

व्योम snd_dice_transaction_clear_enable(काष्ठा snd_dice *dice)
अणु
	__be32 value;

	value = 0;
	snd_fw_transaction(dice->unit, TCODE_WRITE_QUADLET_REQUEST,
			   get_subaddr(dice, SND_DICE_ADDR_TYPE_GLOBAL,
				       GLOBAL_ENABLE),
			   &value, 4, FW_QUIET |
			   FW_FIXED_GENERATION | dice->owner_generation);

	dice->global_enabled = false;
पूर्ण

अटल व्योम dice_notअगरication(काष्ठा fw_card *card, काष्ठा fw_request *request,
			      पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
			      पूर्णांक generation, अचिन्हित दीर्घ दीर्घ offset,
			      व्योम *data, माप_प्रकार length, व्योम *callback_data)
अणु
	काष्ठा snd_dice *dice = callback_data;
	u32 bits;
	अचिन्हित दीर्घ flags;

	अगर (tcode != TCODE_WRITE_QUADLET_REQUEST) अणु
		fw_send_response(card, request, RCODE_TYPE_ERROR);
		वापस;
	पूर्ण
	अगर ((offset & 3) != 0) अणु
		fw_send_response(card, request, RCODE_ADDRESS_ERROR);
		वापस;
	पूर्ण

	bits = be32_to_cpup(data);

	spin_lock_irqsave(&dice->lock, flags);
	dice->notअगरication_bits |= bits;
	spin_unlock_irqrestore(&dice->lock, flags);

	fw_send_response(card, request, RCODE_COMPLETE);

	अगर (bits & NOTIFY_LOCK_CHG)
		complete(&dice->घड़ी_accepted);
	wake_up(&dice->hwdep_रुको);
पूर्ण

अटल पूर्णांक रेजिस्टर_notअगरication_address(काष्ठा snd_dice *dice, bool retry)
अणु
	काष्ठा fw_device *device = fw_parent_device(dice->unit);
	__be64 *buffer;
	अचिन्हित पूर्णांक retries;
	पूर्णांक err;

	retries = (retry) ? 3 : 0;

	buffer = kदो_स्मृति(2 * 8, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	क्रम (;;) अणु
		buffer[0] = cpu_to_be64(OWNER_NO_OWNER);
		buffer[1] = cpu_to_be64(
			((u64)device->card->node_id << OWNER_NODE_SHIFT) |
			dice->notअगरication_handler.offset);

		dice->owner_generation = device->generation;
		smp_rmb(); /* node_id vs. generation */
		err = snd_fw_transaction(dice->unit, TCODE_LOCK_COMPARE_SWAP,
					 get_subaddr(dice,
						     SND_DICE_ADDR_TYPE_GLOBAL,
						     GLOBAL_OWNER),
					 buffer, 2 * 8,
					 FW_FIXED_GENERATION |
							dice->owner_generation);
		अगर (err == 0) अणु
			/* success */
			अगर (buffer[0] == cpu_to_be64(OWNER_NO_OWNER))
				अवरोध;
			/* The address seems to be alपढ़ोy रेजिस्टरed. */
			अगर (buffer[0] == buffer[1])
				अवरोध;

			dev_err(&dice->unit->device,
				"device is already in use\n");
			err = -EBUSY;
		पूर्ण
		अगर (err != -EAGAIN || retries-- > 0)
			अवरोध;

		msleep(20);
	पूर्ण

	kमुक्त(buffer);

	अगर (err < 0)
		dice->owner_generation = -1;

	वापस err;
पूर्ण

अटल व्योम unरेजिस्टर_notअगरication_address(काष्ठा snd_dice *dice)
अणु
	काष्ठा fw_device *device = fw_parent_device(dice->unit);
	__be64 *buffer;

	buffer = kदो_स्मृति(2 * 8, GFP_KERNEL);
	अगर (buffer == शून्य)
		वापस;

	buffer[0] = cpu_to_be64(
		((u64)device->card->node_id << OWNER_NODE_SHIFT) |
		dice->notअगरication_handler.offset);
	buffer[1] = cpu_to_be64(OWNER_NO_OWNER);
	snd_fw_transaction(dice->unit, TCODE_LOCK_COMPARE_SWAP,
			   get_subaddr(dice, SND_DICE_ADDR_TYPE_GLOBAL,
				       GLOBAL_OWNER),
			   buffer, 2 * 8, FW_QUIET |
			   FW_FIXED_GENERATION | dice->owner_generation);

	kमुक्त(buffer);

	dice->owner_generation = -1;
पूर्ण

व्योम snd_dice_transaction_destroy(काष्ठा snd_dice *dice)
अणु
	काष्ठा fw_address_handler *handler = &dice->notअगरication_handler;

	अगर (handler->callback_data == शून्य)
		वापस;

	unरेजिस्टर_notअगरication_address(dice);

	fw_core_हटाओ_address_handler(handler);
	handler->callback_data = शून्य;
पूर्ण

पूर्णांक snd_dice_transaction_reinit(काष्ठा snd_dice *dice)
अणु
	काष्ठा fw_address_handler *handler = &dice->notअगरication_handler;

	अगर (handler->callback_data == शून्य)
		वापस -EINVAL;

	वापस रेजिस्टर_notअगरication_address(dice, false);
पूर्ण

अटल पूर्णांक get_subaddrs(काष्ठा snd_dice *dice)
अणु
	अटल स्थिर पूर्णांक min_values[10] = अणु
		10, 0x60 / 4,
		10, 0x18 / 4,
		10, 0x18 / 4,
		0, 0,
		0, 0,
	पूर्ण;
	__be32 *poपूर्णांकers;
	__be32 version;
	u32 data;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	poपूर्णांकers = kदो_स्मृति_array(ARRAY_SIZE(min_values), माप(__be32),
				 GFP_KERNEL);
	अगर (poपूर्णांकers == शून्य)
		वापस -ENOMEM;

	/*
	 * Check that the sub address spaces exist and are located inside the
	 * निजी address space.  The minimum values are chosen so that all
	 * minimally required रेजिस्टरs are included.
	 */
	err = snd_fw_transaction(dice->unit, TCODE_READ_BLOCK_REQUEST,
				 DICE_PRIVATE_SPACE, poपूर्णांकers,
				 माप(__be32) * ARRAY_SIZE(min_values), 0);
	अगर (err < 0)
		जाओ end;

	क्रम (i = 0; i < ARRAY_SIZE(min_values); ++i) अणु
		data = be32_to_cpu(poपूर्णांकers[i]);
		अगर (data < min_values[i] || data >= 0x40000) अणु
			err = -ENODEV;
			जाओ end;
		पूर्ण
	पूर्ण

	अगर (be32_to_cpu(poपूर्णांकers[1]) > 0x18) अणु
		/*
		 * Check that the implemented DICE driver specअगरication major
		 * version number matches.
		 */
		err = snd_fw_transaction(dice->unit, TCODE_READ_QUADLET_REQUEST,
				DICE_PRIVATE_SPACE +
				be32_to_cpu(poपूर्णांकers[0]) * 4 + GLOBAL_VERSION,
				&version, माप(version), 0);
		अगर (err < 0)
			जाओ end;

		अगर ((version & cpu_to_be32(0xff000000)) !=
						cpu_to_be32(0x01000000)) अणु
			dev_err(&dice->unit->device,
				"unknown DICE version: 0x%08x\n",
				be32_to_cpu(version));
			err = -ENODEV;
			जाओ end;
		पूर्ण

		/* Set up later. */
		dice->घड़ी_caps = 1;
	पूर्ण

	dice->global_offset = be32_to_cpu(poपूर्णांकers[0]) * 4;
	dice->tx_offset = be32_to_cpu(poपूर्णांकers[2]) * 4;
	dice->rx_offset = be32_to_cpu(poपूर्णांकers[4]) * 4;

	/* Old firmware करोesn't support these fields. */
	अगर (poपूर्णांकers[7])
		dice->sync_offset = be32_to_cpu(poपूर्णांकers[6]) * 4;
	अगर (poपूर्णांकers[9])
		dice->rsrv_offset = be32_to_cpu(poपूर्णांकers[8]) * 4;
end:
	kमुक्त(poपूर्णांकers);
	वापस err;
पूर्ण

पूर्णांक snd_dice_transaction_init(काष्ठा snd_dice *dice)
अणु
	काष्ठा fw_address_handler *handler = &dice->notअगरication_handler;
	पूर्णांक err;

	err = get_subaddrs(dice);
	अगर (err < 0)
		वापस err;

	/* Allocation callback in address space over host controller */
	handler->length = 4;
	handler->address_callback = dice_notअगरication;
	handler->callback_data = dice;
	err = fw_core_add_address_handler(handler, &fw_high_memory_region);
	अगर (err < 0) अणु
		handler->callback_data = शून्य;
		वापस err;
	पूर्ण

	/* Register the address space */
	err = रेजिस्टर_notअगरication_address(dice, true);
	अगर (err < 0) अणु
		fw_core_हटाओ_address_handler(handler);
		handler->callback_data = शून्य;
	पूर्ण

	वापस err;
पूर्ण
