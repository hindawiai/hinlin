<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
* Filename: config.c
*
* Authors: Joshua Morris <josh.h.morris@us.ibm.com>
*	Philip Kelleher <pjk1939@linux.vnet.ibm.com>
*
* (C) Copyright 2013 IBM Corporation
*/

#समावेश <linux/types.h>
#समावेश <linux/crc32.h>
#समावेश <linux/swab.h>

#समावेश "rsxx_priv.h"
#समावेश "rsxx_cfg.h"

अटल व्योम initialize_config(काष्ठा rsxx_card_cfg *cfg)
अणु
	cfg->hdr.version = RSXX_CFG_VERSION;

	cfg->data.block_size        = RSXX_HW_BLK_SIZE;
	cfg->data.stripe_size       = RSXX_HW_BLK_SIZE;
	cfg->data.venकरोr_id         = RSXX_VENDOR_ID_IBM;
	cfg->data.cache_order       = (-1);
	cfg->data.पूर्णांकr_coal.mode    = RSXX_INTR_COAL_DISABLED;
	cfg->data.पूर्णांकr_coal.count   = 0;
	cfg->data.पूर्णांकr_coal.latency = 0;
पूर्ण

अटल u32 config_data_crc32(काष्ठा rsxx_card_cfg *cfg)
अणु
	/*
	 * Return the compliment of the CRC to ensure compatibility
	 * (i.e. this is how early rsxx drivers did it.)
	 */

	वापस ~crc32(~0, &cfg->data, माप(cfg->data));
पूर्ण


/*----------------- Config Byte Swap Functions -------------------*/
अटल व्योम config_hdr_be_to_cpu(काष्ठा card_cfg_hdr *hdr)
अणु
	hdr->version = be32_to_cpu((__क्रमce __be32) hdr->version);
	hdr->crc     = be32_to_cpu((__क्रमce __be32) hdr->crc);
पूर्ण

अटल व्योम config_hdr_cpu_to_be(काष्ठा card_cfg_hdr *hdr)
अणु
	hdr->version = (__क्रमce u32) cpu_to_be32(hdr->version);
	hdr->crc     = (__क्रमce u32) cpu_to_be32(hdr->crc);
पूर्ण

अटल व्योम config_data_swab(काष्ठा rsxx_card_cfg *cfg)
अणु
	u32 *data = (u32 *) &cfg->data;
	पूर्णांक i;

	क्रम (i = 0; i < (माप(cfg->data) / 4); i++)
		data[i] = swab32(data[i]);
पूर्ण

अटल व्योम config_data_le_to_cpu(काष्ठा rsxx_card_cfg *cfg)
अणु
	u32 *data = (u32 *) &cfg->data;
	पूर्णांक i;

	क्रम (i = 0; i < (माप(cfg->data) / 4); i++)
		data[i] = le32_to_cpu((__क्रमce __le32) data[i]);
पूर्ण

अटल व्योम config_data_cpu_to_le(काष्ठा rsxx_card_cfg *cfg)
अणु
	u32 *data = (u32 *) &cfg->data;
	पूर्णांक i;

	क्रम (i = 0; i < (माप(cfg->data) / 4); i++)
		data[i] = (__क्रमce u32) cpu_to_le32(data[i]);
पूर्ण


/*----------------- Config Operations ------------------*/
अटल पूर्णांक rsxx_save_config(काष्ठा rsxx_cardinfo *card)
अणु
	काष्ठा rsxx_card_cfg cfg;
	पूर्णांक st;

	स_नकल(&cfg, &card->config, माप(cfg));

	अगर (unlikely(cfg.hdr.version != RSXX_CFG_VERSION)) अणु
		dev_err(CARD_TO_DEV(card),
			"Cannot save config with invalid version %d\n",
			cfg.hdr.version);
		वापस -EINVAL;
	पूर्ण

	/* Convert data to little endian क्रम the CRC calculation. */
	config_data_cpu_to_le(&cfg);

	cfg.hdr.crc = config_data_crc32(&cfg);

	/*
	 * Swap the data from little endian to big endian so it can be
	 * stored.
	 */
	config_data_swab(&cfg);
	config_hdr_cpu_to_be(&cfg.hdr);

	st = rsxx_creg_ग_लिखो(card, CREG_ADD_CONFIG, माप(cfg), &cfg, 1);
	अगर (st)
		वापस st;

	वापस 0;
पूर्ण

पूर्णांक rsxx_load_config(काष्ठा rsxx_cardinfo *card)
अणु
	पूर्णांक st;
	u32 crc;

	st = rsxx_creg_पढ़ो(card, CREG_ADD_CONFIG, माप(card->config),
				&card->config, 1);
	अगर (st) अणु
		dev_err(CARD_TO_DEV(card),
			"Failed reading card config.\n");
		वापस st;
	पूर्ण

	config_hdr_be_to_cpu(&card->config.hdr);

	अगर (card->config.hdr.version == RSXX_CFG_VERSION) अणु
		/*
		 * We calculate the CRC with the data in little endian, because
		 * early drivers did not take big endian CPUs पूर्णांकo account.
		 * The data is always stored in big endian, so we need to byte
		 * swap it beक्रमe calculating the CRC.
		 */

		config_data_swab(&card->config);

		/* Check the CRC */
		crc = config_data_crc32(&card->config);
		अगर (crc != card->config.hdr.crc) अणु
			dev_err(CARD_TO_DEV(card),
				"Config corruption detected!\n");
			dev_info(CARD_TO_DEV(card),
				"CRC (sb x%08x is x%08x)\n",
				card->config.hdr.crc, crc);
			वापस -EIO;
		पूर्ण

		/* Convert the data to CPU byteorder */
		config_data_le_to_cpu(&card->config);

	पूर्ण अन्यथा अगर (card->config.hdr.version != 0) अणु
		dev_err(CARD_TO_DEV(card),
			"Invalid config version %d.\n",
			card->config.hdr.version);
		/*
		 * Config version changes require special handling from the
		 * user
		 */
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		dev_info(CARD_TO_DEV(card),
			"Initializing card configuration.\n");
		initialize_config(&card->config);
		st = rsxx_save_config(card);
		अगर (st)
			वापस st;
	पूर्ण

	card->config_valid = 1;

	dev_dbg(CARD_TO_DEV(card), "version:     x%08x\n",
		card->config.hdr.version);
	dev_dbg(CARD_TO_DEV(card), "crc:         x%08x\n",
		card->config.hdr.crc);
	dev_dbg(CARD_TO_DEV(card), "block_size:  x%08x\n",
		card->config.data.block_size);
	dev_dbg(CARD_TO_DEV(card), "stripe_size: x%08x\n",
		card->config.data.stripe_size);
	dev_dbg(CARD_TO_DEV(card), "vendor_id:   x%08x\n",
		card->config.data.venकरोr_id);
	dev_dbg(CARD_TO_DEV(card), "cache_order: x%08x\n",
		card->config.data.cache_order);
	dev_dbg(CARD_TO_DEV(card), "mode:        x%08x\n",
		card->config.data.पूर्णांकr_coal.mode);
	dev_dbg(CARD_TO_DEV(card), "count:       x%08x\n",
		card->config.data.पूर्णांकr_coal.count);
	dev_dbg(CARD_TO_DEV(card), "latency:     x%08x\n",
		 card->config.data.पूर्णांकr_coal.latency);

	वापस 0;
पूर्ण

