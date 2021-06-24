<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * digi00x-transaction.c - a part of driver क्रम Digidesign Digi 002/003 family
 *
 * Copyright (c) 2014-2015 Takashi Sakamoto
 */

#समावेश <sound/asound.h>
#समावेश "digi00x.h"

अटल व्योम handle_unknown_message(काष्ठा snd_dg00x *dg00x,
				   अचिन्हित दीर्घ दीर्घ offset, __be32 *buf)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dg00x->lock, flags);
	dg00x->msg = be32_to_cpu(*buf);
	spin_unlock_irqrestore(&dg00x->lock, flags);

	wake_up(&dg00x->hwdep_रुको);
पूर्ण

अटल व्योम handle_message(काष्ठा fw_card *card, काष्ठा fw_request *request,
			   पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
			   पूर्णांक generation, अचिन्हित दीर्घ दीर्घ offset,
			   व्योम *data, माप_प्रकार length, व्योम *callback_data)
अणु
	काष्ठा snd_dg00x *dg00x = callback_data;
	__be32 *buf = (__be32 *)data;

	fw_send_response(card, request, RCODE_COMPLETE);

	अगर (offset == dg00x->async_handler.offset)
		handle_unknown_message(dg00x, offset, buf);
पूर्ण

पूर्णांक snd_dg00x_transaction_reरेजिस्टर(काष्ठा snd_dg00x *dg00x)
अणु
	काष्ठा fw_device *device = fw_parent_device(dg00x->unit);
	__be32 data[2];

	/* Unknown. 4bytes. */
	data[0] = cpu_to_be32((device->card->node_id << 16) |
			      (dg00x->async_handler.offset >> 32));
	data[1] = cpu_to_be32(dg00x->async_handler.offset);
	वापस snd_fw_transaction(dg00x->unit, TCODE_WRITE_BLOCK_REQUEST,
				  DG00X_ADDR_BASE + DG00X_OFFSET_MESSAGE_ADDR,
				  &data, माप(data), 0);
पूर्ण

व्योम snd_dg00x_transaction_unरेजिस्टर(काष्ठा snd_dg00x *dg00x)
अणु
	अगर (dg00x->async_handler.callback_data == शून्य)
		वापस;

	fw_core_हटाओ_address_handler(&dg00x->async_handler);

	dg00x->async_handler.callback_data = शून्य;
पूर्ण

पूर्णांक snd_dg00x_transaction_रेजिस्टर(काष्ठा snd_dg00x *dg00x)
अणु
	अटल स्थिर काष्ठा fw_address_region resp_रेजिस्टर_region = अणु
		.start	= 0xffffe0000000ull,
		.end	= 0xffffe000ffffull,
	पूर्ण;
	पूर्णांक err;

	dg00x->async_handler.length = 4;
	dg00x->async_handler.address_callback = handle_message;
	dg00x->async_handler.callback_data = dg00x;

	err = fw_core_add_address_handler(&dg00x->async_handler,
					  &resp_रेजिस्टर_region);
	अगर (err < 0)
		वापस err;

	err = snd_dg00x_transaction_reरेजिस्टर(dg00x);
	अगर (err < 0)
		snd_dg00x_transaction_unरेजिस्टर(dg00x);

	वापस err;
पूर्ण
