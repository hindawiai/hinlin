<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * motu-transaction.c - a part of driver क्रम MOTU FireWire series
 *
 * Copyright (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */


#समावेश "motu.h"

#घोषणा SND_MOTU_ADDR_BASE	0xfffff0000000ULL
#घोषणा ASYNC_ADDR_HI  0x0b04
#घोषणा ASYNC_ADDR_LO  0x0b08

पूर्णांक snd_motu_transaction_पढ़ो(काष्ठा snd_motu *motu, u32 offset, __be32 *reg,
			      माप_प्रकार size)
अणु
	पूर्णांक tcode;

	अगर (size % माप(__be32) > 0 || size <= 0)
		वापस -EINVAL;
	अगर (size == माप(__be32))
		tcode = TCODE_READ_QUADLET_REQUEST;
	अन्यथा
		tcode = TCODE_READ_BLOCK_REQUEST;

	वापस snd_fw_transaction(motu->unit, tcode,
				  SND_MOTU_ADDR_BASE + offset, reg, size, 0);
पूर्ण

पूर्णांक snd_motu_transaction_ग_लिखो(काष्ठा snd_motu *motu, u32 offset, __be32 *reg,
			       माप_प्रकार size)
अणु
	पूर्णांक tcode;

	अगर (size % माप(__be32) > 0 || size <= 0)
		वापस -EINVAL;
	अगर (size == माप(__be32))
		tcode = TCODE_WRITE_QUADLET_REQUEST;
	अन्यथा
		tcode = TCODE_WRITE_BLOCK_REQUEST;

	वापस snd_fw_transaction(motu->unit, tcode,
				  SND_MOTU_ADDR_BASE + offset, reg, size, 0);
पूर्ण

अटल व्योम handle_message(काष्ठा fw_card *card, काष्ठा fw_request *request,
			   पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
			   पूर्णांक generation, अचिन्हित दीर्घ दीर्घ offset,
			   व्योम *data, माप_प्रकार length, व्योम *callback_data)
अणु
	काष्ठा snd_motu *motu = callback_data;
	__be32 *buf = (__be32 *)data;
	अचिन्हित दीर्घ flags;

	अगर (tcode != TCODE_WRITE_QUADLET_REQUEST) अणु
		fw_send_response(card, request, RCODE_COMPLETE);
		वापस;
	पूर्ण

	अगर (offset != motu->async_handler.offset || length != 4) अणु
		fw_send_response(card, request, RCODE_ADDRESS_ERROR);
		वापस;
	पूर्ण

	spin_lock_irqsave(&motu->lock, flags);
	motu->msg = be32_to_cpu(*buf);
	spin_unlock_irqrestore(&motu->lock, flags);

	fw_send_response(card, request, RCODE_COMPLETE);

	wake_up(&motu->hwdep_रुको);
पूर्ण

पूर्णांक snd_motu_transaction_reरेजिस्टर(काष्ठा snd_motu *motu)
अणु
	काष्ठा fw_device *device = fw_parent_device(motu->unit);
	__be32 data;
	पूर्णांक err;

	अगर (motu->async_handler.callback_data == शून्य)
		वापस -EINVAL;

	/* Register messaging address. Block transaction is not allowed. */
	data = cpu_to_be32((device->card->node_id << 16) |
			   (motu->async_handler.offset >> 32));
	err = snd_motu_transaction_ग_लिखो(motu, ASYNC_ADDR_HI, &data,
					 माप(data));
	अगर (err < 0)
		वापस err;

	data = cpu_to_be32(motu->async_handler.offset);
	वापस snd_motu_transaction_ग_लिखो(motu, ASYNC_ADDR_LO, &data,
					  माप(data));
पूर्ण

पूर्णांक snd_motu_transaction_रेजिस्टर(काष्ठा snd_motu *motu)
अणु
	अटल स्थिर काष्ठा fw_address_region resp_रेजिस्टर_region = अणु
		.start	= 0xffffe0000000ull,
		.end	= 0xffffe000ffffull,
	पूर्ण;
	पूर्णांक err;

	/* Perhaps, 4 byte messages are transferred. */
	motu->async_handler.length = 4;
	motu->async_handler.address_callback = handle_message;
	motu->async_handler.callback_data = motu;

	err = fw_core_add_address_handler(&motu->async_handler,
					  &resp_रेजिस्टर_region);
	अगर (err < 0)
		वापस err;

	err = snd_motu_transaction_reरेजिस्टर(motu);
	अगर (err < 0) अणु
		fw_core_हटाओ_address_handler(&motu->async_handler);
		motu->async_handler.address_callback = शून्य;
	पूर्ण

	वापस err;
पूर्ण

व्योम snd_motu_transaction_unरेजिस्टर(काष्ठा snd_motu *motu)
अणु
	__be32 data;

	अगर (motu->async_handler.address_callback != शून्य)
		fw_core_हटाओ_address_handler(&motu->async_handler);
	motu->async_handler.address_callback = शून्य;

	/* Unरेजिस्टर the address. */
	data = cpu_to_be32(0x00000000);
	snd_motu_transaction_ग_लिखो(motu, ASYNC_ADDR_HI, &data, माप(data));
	snd_motu_transaction_ग_लिखो(motu, ASYNC_ADDR_LO, &data, माप(data));
पूर्ण
