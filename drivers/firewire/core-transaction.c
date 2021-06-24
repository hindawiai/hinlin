<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Core IEEE1394 transaction logic
 *
 * Copyright (C) 2004-2006 Kristian Hoegsberg <krh@bitplanet.net>
 */

#समावेश <linux/bug.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/idr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/rculist.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "core.h"

#घोषणा HEADER_PRI(pri)			((pri) << 0)
#घोषणा HEADER_TCODE(tcode)		((tcode) << 4)
#घोषणा HEADER_RETRY(retry)		((retry) << 8)
#घोषणा HEADER_TLABEL(tlabel)		((tlabel) << 10)
#घोषणा HEADER_DESTINATION(destination)	((destination) << 16)
#घोषणा HEADER_SOURCE(source)		((source) << 16)
#घोषणा HEADER_RCODE(rcode)		((rcode) << 12)
#घोषणा HEADER_OFFSET_HIGH(offset_high)	((offset_high) << 0)
#घोषणा HEADER_DATA_LENGTH(length)	((length) << 16)
#घोषणा HEADER_EXTENDED_TCODE(tcode)	((tcode) << 0)

#घोषणा HEADER_GET_TCODE(q)		(((q) >> 4) & 0x0f)
#घोषणा HEADER_GET_TLABEL(q)		(((q) >> 10) & 0x3f)
#घोषणा HEADER_GET_RCODE(q)		(((q) >> 12) & 0x0f)
#घोषणा HEADER_GET_DESTINATION(q)	(((q) >> 16) & 0xffff)
#घोषणा HEADER_GET_SOURCE(q)		(((q) >> 16) & 0xffff)
#घोषणा HEADER_GET_OFFSET_HIGH(q)	(((q) >> 0) & 0xffff)
#घोषणा HEADER_GET_DATA_LENGTH(q)	(((q) >> 16) & 0xffff)
#घोषणा HEADER_GET_EXTENDED_TCODE(q)	(((q) >> 0) & 0xffff)

#घोषणा HEADER_DESTINATION_IS_BROADCAST(q) \
	(((q) & HEADER_DESTINATION(0x3f)) == HEADER_DESTINATION(0x3f))

#घोषणा PHY_PACKET_CONFIG	0x0
#घोषणा PHY_PACKET_LINK_ON	0x1
#घोषणा PHY_PACKET_SELF_ID	0x2

#घोषणा PHY_CONFIG_GAP_COUNT(gap_count)	(((gap_count) << 16) | (1 << 22))
#घोषणा PHY_CONFIG_ROOT_ID(node_id)	((((node_id) & 0x3f) << 24) | (1 << 23))
#घोषणा PHY_IDENTIFIER(id)		((id) << 30)

/* वापसs 0 अगर the split समयout handler is alपढ़ोy running */
अटल पूर्णांक try_cancel_split_समयout(काष्ठा fw_transaction *t)
अणु
	अगर (t->is_split_transaction)
		वापस del_समयr(&t->split_समयout_समयr);
	अन्यथा
		वापस 1;
पूर्ण

अटल पूर्णांक बंद_transaction(काष्ठा fw_transaction *transaction,
			     काष्ठा fw_card *card, पूर्णांक rcode)
अणु
	काष्ठा fw_transaction *t;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->lock, flags);
	list_क्रम_each_entry(t, &card->transaction_list, link) अणु
		अगर (t == transaction) अणु
			अगर (!try_cancel_split_समयout(t)) अणु
				spin_unlock_irqrestore(&card->lock, flags);
				जाओ समयd_out;
			पूर्ण
			list_del_init(&t->link);
			card->tlabel_mask &= ~(1ULL << t->tlabel);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&card->lock, flags);

	अगर (&t->link != &card->transaction_list) अणु
		t->callback(card, rcode, शून्य, 0, t->callback_data);
		वापस 0;
	पूर्ण

 समयd_out:
	वापस -ENOENT;
पूर्ण

/*
 * Only valid क्रम transactions that are potentially pending (ie have
 * been sent).
 */
पूर्णांक fw_cancel_transaction(काष्ठा fw_card *card,
			  काष्ठा fw_transaction *transaction)
अणु
	/*
	 * Cancel the packet transmission अगर it's still queued.  That
	 * will call the packet transmission callback which cancels
	 * the transaction.
	 */

	अगर (card->driver->cancel_packet(card, &transaction->packet) == 0)
		वापस 0;

	/*
	 * If the request packet has alपढ़ोy been sent, we need to see
	 * अगर the transaction is still pending and हटाओ it in that हाल.
	 */

	वापस बंद_transaction(transaction, card, RCODE_CANCELLED);
पूर्ण
EXPORT_SYMBOL(fw_cancel_transaction);

अटल व्योम split_transaction_समयout_callback(काष्ठा समयr_list *समयr)
अणु
	काष्ठा fw_transaction *t = from_समयr(t, समयr, split_समयout_समयr);
	काष्ठा fw_card *card = t->card;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->lock, flags);
	अगर (list_empty(&t->link)) अणु
		spin_unlock_irqrestore(&card->lock, flags);
		वापस;
	पूर्ण
	list_del(&t->link);
	card->tlabel_mask &= ~(1ULL << t->tlabel);
	spin_unlock_irqrestore(&card->lock, flags);

	t->callback(card, RCODE_CANCELLED, शून्य, 0, t->callback_data);
पूर्ण

अटल व्योम start_split_transaction_समयout(काष्ठा fw_transaction *t,
					    काष्ठा fw_card *card)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->lock, flags);

	अगर (list_empty(&t->link) || WARN_ON(t->is_split_transaction)) अणु
		spin_unlock_irqrestore(&card->lock, flags);
		वापस;
	पूर्ण

	t->is_split_transaction = true;
	mod_समयr(&t->split_समयout_समयr,
		  jअगरfies + card->split_समयout_jअगरfies);

	spin_unlock_irqrestore(&card->lock, flags);
पूर्ण

अटल व्योम transmit_complete_callback(काष्ठा fw_packet *packet,
				       काष्ठा fw_card *card, पूर्णांक status)
अणु
	काष्ठा fw_transaction *t =
	    container_of(packet, काष्ठा fw_transaction, packet);

	चयन (status) अणु
	हाल ACK_COMPLETE:
		बंद_transaction(t, card, RCODE_COMPLETE);
		अवरोध;
	हाल ACK_PENDING:
		start_split_transaction_समयout(t, card);
		अवरोध;
	हाल ACK_BUSY_X:
	हाल ACK_BUSY_A:
	हाल ACK_BUSY_B:
		बंद_transaction(t, card, RCODE_BUSY);
		अवरोध;
	हाल ACK_DATA_ERROR:
		बंद_transaction(t, card, RCODE_DATA_ERROR);
		अवरोध;
	हाल ACK_TYPE_ERROR:
		बंद_transaction(t, card, RCODE_TYPE_ERROR);
		अवरोध;
	शेष:
		/*
		 * In this हाल the ack is really a juju specअगरic
		 * rcode, so just क्रमward that to the callback.
		 */
		बंद_transaction(t, card, status);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fw_fill_request(काष्ठा fw_packet *packet, पूर्णांक tcode, पूर्णांक tlabel,
		पूर्णांक destination_id, पूर्णांक source_id, पूर्णांक generation, पूर्णांक speed,
		अचिन्हित दीर्घ दीर्घ offset, व्योम *payload, माप_प्रकार length)
अणु
	पूर्णांक ext_tcode;

	अगर (tcode == TCODE_STREAM_DATA) अणु
		packet->header[0] =
			HEADER_DATA_LENGTH(length) |
			destination_id |
			HEADER_TCODE(TCODE_STREAM_DATA);
		packet->header_length = 4;
		packet->payload = payload;
		packet->payload_length = length;

		जाओ common;
	पूर्ण

	अगर (tcode > 0x10) अणु
		ext_tcode = tcode & ~0x10;
		tcode = TCODE_LOCK_REQUEST;
	पूर्ण अन्यथा
		ext_tcode = 0;

	packet->header[0] =
		HEADER_RETRY(RETRY_X) |
		HEADER_TLABEL(tlabel) |
		HEADER_TCODE(tcode) |
		HEADER_DESTINATION(destination_id);
	packet->header[1] =
		HEADER_OFFSET_HIGH(offset >> 32) | HEADER_SOURCE(source_id);
	packet->header[2] =
		offset;

	चयन (tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
		packet->header[3] = *(u32 *)payload;
		packet->header_length = 16;
		packet->payload_length = 0;
		अवरोध;

	हाल TCODE_LOCK_REQUEST:
	हाल TCODE_WRITE_BLOCK_REQUEST:
		packet->header[3] =
			HEADER_DATA_LENGTH(length) |
			HEADER_EXTENDED_TCODE(ext_tcode);
		packet->header_length = 16;
		packet->payload = payload;
		packet->payload_length = length;
		अवरोध;

	हाल TCODE_READ_QUADLET_REQUEST:
		packet->header_length = 12;
		packet->payload_length = 0;
		अवरोध;

	हाल TCODE_READ_BLOCK_REQUEST:
		packet->header[3] =
			HEADER_DATA_LENGTH(length) |
			HEADER_EXTENDED_TCODE(ext_tcode);
		packet->header_length = 16;
		packet->payload_length = 0;
		अवरोध;

	शेष:
		WARN(1, "wrong tcode %d\n", tcode);
	पूर्ण
 common:
	packet->speed = speed;
	packet->generation = generation;
	packet->ack = 0;
	packet->payload_mapped = false;
पूर्ण

अटल पूर्णांक allocate_tlabel(काष्ठा fw_card *card)
अणु
	पूर्णांक tlabel;

	tlabel = card->current_tlabel;
	जबतक (card->tlabel_mask & (1ULL << tlabel)) अणु
		tlabel = (tlabel + 1) & 0x3f;
		अगर (tlabel == card->current_tlabel)
			वापस -EBUSY;
	पूर्ण

	card->current_tlabel = (tlabel + 1) & 0x3f;
	card->tlabel_mask |= 1ULL << tlabel;

	वापस tlabel;
पूर्ण

/**
 * fw_send_request() - submit a request packet क्रम transmission
 * @card:		पूर्णांकerface to send the request at
 * @t:			transaction instance to which the request beदीर्घs
 * @tcode:		transaction code
 * @destination_id:	destination node ID, consisting of bus_ID and phy_ID
 * @generation:		bus generation in which request and response are valid
 * @speed:		transmission speed
 * @offset:		48bit wide offset पूर्णांकo destination's address space
 * @payload:		data payload क्रम the request subaction
 * @length:		length of the payload, in bytes
 * @callback:		function to be called when the transaction is completed
 * @callback_data:	data to be passed to the transaction completion callback
 *
 * Submit a request packet पूर्णांकo the asynchronous request transmission queue.
 * Can be called from atomic context.  If you prefer a blocking API, use
 * fw_run_transaction() in a context that can sleep.
 *
 * In हाल of lock requests, specअगरy one of the firewire-core specअगरic %TCODE_
 * स्थिरants instead of %TCODE_LOCK_REQUEST in @tcode.
 *
 * Make sure that the value in @destination_id is not older than the one in
 * @generation.  Otherwise the request is in danger to be sent to a wrong node.
 *
 * In हाल of asynchronous stream packets i.e. %TCODE_STREAM_DATA, the caller
 * needs to synthesize @destination_id with fw_stream_packet_destination_id().
 * It will contain tag, channel, and sy data instead of a node ID then.
 *
 * The payload buffer at @data is going to be DMA-mapped except in हाल of
 * @length <= 8 or of local (loopback) requests.  Hence make sure that the
 * buffer complies with the restrictions of the streaming DMA mapping API.
 * @payload must not be मुक्तd beक्रमe the @callback is called.
 *
 * In हाल of request types without payload, @data is शून्य and @length is 0.
 *
 * After the transaction is completed successfully or unsuccessfully, the
 * @callback will be called.  Among its parameters is the response code which
 * is either one of the rcodes per IEEE 1394 or, in हाल of पूर्णांकernal errors,
 * the firewire-core specअगरic %RCODE_SEND_ERROR.  The other firewire-core
 * specअगरic rcodes (%RCODE_CANCELLED, %RCODE_BUSY, %RCODE_GENERATION,
 * %RCODE_NO_ACK) denote transaction समयout, busy responder, stale request
 * generation, or missing ACK respectively.
 *
 * Note some timing corner हालs:  fw_send_request() may complete much earlier
 * than when the request packet actually hits the wire.  On the other hand,
 * transaction completion and hence execution of @callback may happen even
 * beक्रमe fw_send_request() वापसs.
 */
व्योम fw_send_request(काष्ठा fw_card *card, काष्ठा fw_transaction *t, पूर्णांक tcode,
		     पूर्णांक destination_id, पूर्णांक generation, पूर्णांक speed,
		     अचिन्हित दीर्घ दीर्घ offset, व्योम *payload, माप_प्रकार length,
		     fw_transaction_callback_t callback, व्योम *callback_data)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक tlabel;

	/*
	 * Allocate tlabel from the biपंचांगap and put the transaction on
	 * the list जबतक holding the card spinlock.
	 */

	spin_lock_irqsave(&card->lock, flags);

	tlabel = allocate_tlabel(card);
	अगर (tlabel < 0) अणु
		spin_unlock_irqrestore(&card->lock, flags);
		callback(card, RCODE_SEND_ERROR, शून्य, 0, callback_data);
		वापस;
	पूर्ण

	t->node_id = destination_id;
	t->tlabel = tlabel;
	t->card = card;
	t->is_split_transaction = false;
	समयr_setup(&t->split_समयout_समयr,
		    split_transaction_समयout_callback, 0);
	t->callback = callback;
	t->callback_data = callback_data;

	fw_fill_request(&t->packet, tcode, t->tlabel,
			destination_id, card->node_id, generation,
			speed, offset, payload, length);
	t->packet.callback = transmit_complete_callback;

	list_add_tail(&t->link, &card->transaction_list);

	spin_unlock_irqrestore(&card->lock, flags);

	card->driver->send_request(card, &t->packet);
पूर्ण
EXPORT_SYMBOL(fw_send_request);

काष्ठा transaction_callback_data अणु
	काष्ठा completion करोne;
	व्योम *payload;
	पूर्णांक rcode;
पूर्ण;

अटल व्योम transaction_callback(काष्ठा fw_card *card, पूर्णांक rcode,
				 व्योम *payload, माप_प्रकार length, व्योम *data)
अणु
	काष्ठा transaction_callback_data *d = data;

	अगर (rcode == RCODE_COMPLETE)
		स_नकल(d->payload, payload, length);
	d->rcode = rcode;
	complete(&d->करोne);
पूर्ण

/**
 * fw_run_transaction() - send request and sleep until transaction is completed
 * @card:		card पूर्णांकerface क्रम this request
 * @tcode:		transaction code
 * @destination_id:	destination node ID, consisting of bus_ID and phy_ID
 * @generation:		bus generation in which request and response are valid
 * @speed:		transmission speed
 * @offset:		48bit wide offset पूर्णांकo destination's address space
 * @payload:		data payload क्रम the request subaction
 * @length:		length of the payload, in bytes
 *
 * Returns the RCODE.  See fw_send_request() क्रम parameter करोcumentation.
 * Unlike fw_send_request(), @data poपूर्णांकs to the payload of the request or/and
 * to the payload of the response.  DMA mapping restrictions apply to outbound
 * request payloads of >= 8 bytes but not to inbound response payloads.
 */
पूर्णांक fw_run_transaction(काष्ठा fw_card *card, पूर्णांक tcode, पूर्णांक destination_id,
		       पूर्णांक generation, पूर्णांक speed, अचिन्हित दीर्घ दीर्घ offset,
		       व्योम *payload, माप_प्रकार length)
अणु
	काष्ठा transaction_callback_data d;
	काष्ठा fw_transaction t;

	समयr_setup_on_stack(&t.split_समयout_समयr, शून्य, 0);
	init_completion(&d.करोne);
	d.payload = payload;
	fw_send_request(card, &t, tcode, destination_id, generation, speed,
			offset, payload, length, transaction_callback, &d);
	रुको_क्रम_completion(&d.करोne);
	destroy_समयr_on_stack(&t.split_समयout_समयr);

	वापस d.rcode;
पूर्ण
EXPORT_SYMBOL(fw_run_transaction);

अटल DEFINE_MUTEX(phy_config_mutex);
अटल DECLARE_COMPLETION(phy_config_करोne);

अटल व्योम transmit_phy_packet_callback(काष्ठा fw_packet *packet,
					 काष्ठा fw_card *card, पूर्णांक status)
अणु
	complete(&phy_config_करोne);
पूर्ण

अटल काष्ठा fw_packet phy_config_packet = अणु
	.header_length	= 12,
	.header[0]	= TCODE_LINK_INTERNAL << 4,
	.payload_length	= 0,
	.speed		= SCODE_100,
	.callback	= transmit_phy_packet_callback,
पूर्ण;

व्योम fw_send_phy_config(काष्ठा fw_card *card,
			पूर्णांक node_id, पूर्णांक generation, पूर्णांक gap_count)
अणु
	दीर्घ समयout = DIV_ROUND_UP(HZ, 10);
	u32 data = PHY_IDENTIFIER(PHY_PACKET_CONFIG);

	अगर (node_id != FW_PHY_CONFIG_NO_NODE_ID)
		data |= PHY_CONFIG_ROOT_ID(node_id);

	अगर (gap_count == FW_PHY_CONFIG_CURRENT_GAP_COUNT) अणु
		gap_count = card->driver->पढ़ो_phy_reg(card, 1);
		अगर (gap_count < 0)
			वापस;

		gap_count &= 63;
		अगर (gap_count == 63)
			वापस;
	पूर्ण
	data |= PHY_CONFIG_GAP_COUNT(gap_count);

	mutex_lock(&phy_config_mutex);

	phy_config_packet.header[1] = data;
	phy_config_packet.header[2] = ~data;
	phy_config_packet.generation = generation;
	reinit_completion(&phy_config_करोne);

	card->driver->send_request(card, &phy_config_packet);
	रुको_क्रम_completion_समयout(&phy_config_करोne, समयout);

	mutex_unlock(&phy_config_mutex);
पूर्ण

अटल काष्ठा fw_address_handler *lookup_overlapping_address_handler(
	काष्ठा list_head *list, अचिन्हित दीर्घ दीर्घ offset, माप_प्रकार length)
अणु
	काष्ठा fw_address_handler *handler;

	list_क्रम_each_entry_rcu(handler, list, link) अणु
		अगर (handler->offset < offset + length &&
		    offset < handler->offset + handler->length)
			वापस handler;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool is_enclosing_handler(काष्ठा fw_address_handler *handler,
				 अचिन्हित दीर्घ दीर्घ offset, माप_प्रकार length)
अणु
	वापस handler->offset <= offset &&
		offset + length <= handler->offset + handler->length;
पूर्ण

अटल काष्ठा fw_address_handler *lookup_enclosing_address_handler(
	काष्ठा list_head *list, अचिन्हित दीर्घ दीर्घ offset, माप_प्रकार length)
अणु
	काष्ठा fw_address_handler *handler;

	list_क्रम_each_entry_rcu(handler, list, link) अणु
		अगर (is_enclosing_handler(handler, offset, length))
			वापस handler;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल DEFINE_SPINLOCK(address_handler_list_lock);
अटल LIST_HEAD(address_handler_list);

स्थिर काष्ठा fw_address_region fw_high_memory_region =
	अणु .start = FW_MAX_PHYSICAL_RANGE, .end = 0xffffe0000000ULL, पूर्ण;
EXPORT_SYMBOL(fw_high_memory_region);

अटल स्थिर काष्ठा fw_address_region low_memory_region =
	अणु .start = 0x000000000000ULL, .end = FW_MAX_PHYSICAL_RANGE, पूर्ण;

#अगर 0
स्थिर काष्ठा fw_address_region fw_निजी_region =
	अणु .start = 0xffffe0000000ULL, .end = 0xfffff0000000ULL,  पूर्ण;
स्थिर काष्ठा fw_address_region fw_csr_region =
	अणु .start = CSR_REGISTER_BASE,
	  .end   = CSR_REGISTER_BASE | CSR_CONFIG_ROM_END,  पूर्ण;
स्थिर काष्ठा fw_address_region fw_unit_space_region =
	अणु .start = 0xfffff0000900ULL, .end = 0x1000000000000ULL, पूर्ण;
#पूर्ण_अगर  /*  0  */

अटल bool is_in_fcp_region(u64 offset, माप_प्रकार length)
अणु
	वापस offset >= (CSR_REGISTER_BASE | CSR_FCP_COMMAND) &&
		offset + length <= (CSR_REGISTER_BASE | CSR_FCP_END);
पूर्ण

/**
 * fw_core_add_address_handler() - रेजिस्टर क्रम incoming requests
 * @handler:	callback
 * @region:	region in the IEEE 1212 node space address range
 *
 * region->start, ->end, and handler->length have to be quadlet-aligned.
 *
 * When a request is received that falls within the specअगरied address range,
 * the specअगरied callback is invoked.  The parameters passed to the callback
 * give the details of the particular request.
 *
 * To be called in process context.
 * Return value:  0 on success, non-zero otherwise.
 *
 * The start offset of the handler's address region is determined by
 * fw_core_add_address_handler() and is वापसed in handler->offset.
 *
 * Address allocations are exclusive, except क्रम the FCP रेजिस्टरs.
 */
पूर्णांक fw_core_add_address_handler(काष्ठा fw_address_handler *handler,
				स्थिर काष्ठा fw_address_region *region)
अणु
	काष्ठा fw_address_handler *other;
	पूर्णांक ret = -EBUSY;

	अगर (region->start & 0xffff000000000003ULL ||
	    region->start >= region->end ||
	    region->end   > 0x0001000000000000ULL ||
	    handler->length & 3 ||
	    handler->length == 0)
		वापस -EINVAL;

	spin_lock(&address_handler_list_lock);

	handler->offset = region->start;
	जबतक (handler->offset + handler->length <= region->end) अणु
		अगर (is_in_fcp_region(handler->offset, handler->length))
			other = शून्य;
		अन्यथा
			other = lookup_overlapping_address_handler
					(&address_handler_list,
					 handler->offset, handler->length);
		अगर (other != शून्य) अणु
			handler->offset += other->length;
		पूर्ण अन्यथा अणु
			list_add_tail_rcu(&handler->link, &address_handler_list);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&address_handler_list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fw_core_add_address_handler);

/**
 * fw_core_हटाओ_address_handler() - unरेजिस्टर an address handler
 * @handler: callback
 *
 * To be called in process context.
 *
 * When fw_core_हटाओ_address_handler() वापसs, @handler->callback() is
 * guaranteed to not run on any CPU anymore.
 */
व्योम fw_core_हटाओ_address_handler(काष्ठा fw_address_handler *handler)
अणु
	spin_lock(&address_handler_list_lock);
	list_del_rcu(&handler->link);
	spin_unlock(&address_handler_list_lock);
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL(fw_core_हटाओ_address_handler);

काष्ठा fw_request अणु
	काष्ठा fw_packet response;
	u32 request_header[4];
	पूर्णांक ack;
	u32 length;
	u32 data[];
पूर्ण;

अटल व्योम मुक्त_response_callback(काष्ठा fw_packet *packet,
				   काष्ठा fw_card *card, पूर्णांक status)
अणु
	काष्ठा fw_request *request;

	request = container_of(packet, काष्ठा fw_request, response);
	kमुक्त(request);
पूर्ण

पूर्णांक fw_get_response_length(काष्ठा fw_request *r)
अणु
	पूर्णांक tcode, ext_tcode, data_length;

	tcode = HEADER_GET_TCODE(r->request_header[0]);

	चयन (tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
	हाल TCODE_WRITE_BLOCK_REQUEST:
		वापस 0;

	हाल TCODE_READ_QUADLET_REQUEST:
		वापस 4;

	हाल TCODE_READ_BLOCK_REQUEST:
		data_length = HEADER_GET_DATA_LENGTH(r->request_header[3]);
		वापस data_length;

	हाल TCODE_LOCK_REQUEST:
		ext_tcode = HEADER_GET_EXTENDED_TCODE(r->request_header[3]);
		data_length = HEADER_GET_DATA_LENGTH(r->request_header[3]);
		चयन (ext_tcode) अणु
		हाल EXTCODE_FETCH_ADD:
		हाल EXTCODE_LITTLE_ADD:
			वापस data_length;
		शेष:
			वापस data_length / 2;
		पूर्ण

	शेष:
		WARN(1, "wrong tcode %d\n", tcode);
		वापस 0;
	पूर्ण
पूर्ण

व्योम fw_fill_response(काष्ठा fw_packet *response, u32 *request_header,
		      पूर्णांक rcode, व्योम *payload, माप_प्रकार length)
अणु
	पूर्णांक tcode, tlabel, extended_tcode, source, destination;

	tcode          = HEADER_GET_TCODE(request_header[0]);
	tlabel         = HEADER_GET_TLABEL(request_header[0]);
	source         = HEADER_GET_DESTINATION(request_header[0]);
	destination    = HEADER_GET_SOURCE(request_header[1]);
	extended_tcode = HEADER_GET_EXTENDED_TCODE(request_header[3]);

	response->header[0] =
		HEADER_RETRY(RETRY_1) |
		HEADER_TLABEL(tlabel) |
		HEADER_DESTINATION(destination);
	response->header[1] =
		HEADER_SOURCE(source) |
		HEADER_RCODE(rcode);
	response->header[2] = 0;

	चयन (tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
	हाल TCODE_WRITE_BLOCK_REQUEST:
		response->header[0] |= HEADER_TCODE(TCODE_WRITE_RESPONSE);
		response->header_length = 12;
		response->payload_length = 0;
		अवरोध;

	हाल TCODE_READ_QUADLET_REQUEST:
		response->header[0] |=
			HEADER_TCODE(TCODE_READ_QUADLET_RESPONSE);
		अगर (payload != शून्य)
			response->header[3] = *(u32 *)payload;
		अन्यथा
			response->header[3] = 0;
		response->header_length = 16;
		response->payload_length = 0;
		अवरोध;

	हाल TCODE_READ_BLOCK_REQUEST:
	हाल TCODE_LOCK_REQUEST:
		response->header[0] |= HEADER_TCODE(tcode + 2);
		response->header[3] =
			HEADER_DATA_LENGTH(length) |
			HEADER_EXTENDED_TCODE(extended_tcode);
		response->header_length = 16;
		response->payload = payload;
		response->payload_length = length;
		अवरोध;

	शेष:
		WARN(1, "wrong tcode %d\n", tcode);
	पूर्ण

	response->payload_mapped = false;
पूर्ण
EXPORT_SYMBOL(fw_fill_response);

अटल u32 compute_split_समयout_बारtamp(काष्ठा fw_card *card,
					   u32 request_बारtamp)
अणु
	अचिन्हित पूर्णांक cycles;
	u32 बारtamp;

	cycles = card->split_समयout_cycles;
	cycles += request_बारtamp & 0x1fff;

	बारtamp = request_बारtamp & ~0x1fff;
	बारtamp += (cycles / 8000) << 13;
	बारtamp |= cycles % 8000;

	वापस बारtamp;
पूर्ण

अटल काष्ठा fw_request *allocate_request(काष्ठा fw_card *card,
					   काष्ठा fw_packet *p)
अणु
	काष्ठा fw_request *request;
	u32 *data, length;
	पूर्णांक request_tcode;

	request_tcode = HEADER_GET_TCODE(p->header[0]);
	चयन (request_tcode) अणु
	हाल TCODE_WRITE_QUADLET_REQUEST:
		data = &p->header[3];
		length = 4;
		अवरोध;

	हाल TCODE_WRITE_BLOCK_REQUEST:
	हाल TCODE_LOCK_REQUEST:
		data = p->payload;
		length = HEADER_GET_DATA_LENGTH(p->header[3]);
		अवरोध;

	हाल TCODE_READ_QUADLET_REQUEST:
		data = शून्य;
		length = 4;
		अवरोध;

	हाल TCODE_READ_BLOCK_REQUEST:
		data = शून्य;
		length = HEADER_GET_DATA_LENGTH(p->header[3]);
		अवरोध;

	शेष:
		fw_notice(card, "ERROR - corrupt request received - %08x %08x %08x\n",
			 p->header[0], p->header[1], p->header[2]);
		वापस शून्य;
	पूर्ण

	request = kदो_स्मृति(माप(*request) + length, GFP_ATOMIC);
	अगर (request == शून्य)
		वापस शून्य;

	request->response.speed = p->speed;
	request->response.बारtamp =
			compute_split_समयout_बारtamp(card, p->बारtamp);
	request->response.generation = p->generation;
	request->response.ack = 0;
	request->response.callback = मुक्त_response_callback;
	request->ack = p->ack;
	request->length = length;
	अगर (data)
		स_नकल(request->data, data, length);

	स_नकल(request->request_header, p->header, माप(p->header));

	वापस request;
पूर्ण

व्योम fw_send_response(काष्ठा fw_card *card,
		      काष्ठा fw_request *request, पूर्णांक rcode)
अणु
	अगर (WARN_ONCE(!request, "invalid for FCP address handlers"))
		वापस;

	/* unअगरied transaction or broadcast transaction: करोn't respond */
	अगर (request->ack != ACK_PENDING ||
	    HEADER_DESTINATION_IS_BROADCAST(request->request_header[0])) अणु
		kमुक्त(request);
		वापस;
	पूर्ण

	अगर (rcode == RCODE_COMPLETE)
		fw_fill_response(&request->response, request->request_header,
				 rcode, request->data,
				 fw_get_response_length(request));
	अन्यथा
		fw_fill_response(&request->response, request->request_header,
				 rcode, शून्य, 0);

	card->driver->send_response(card, &request->response);
पूर्ण
EXPORT_SYMBOL(fw_send_response);

/**
 * fw_get_request_speed() - वापसs speed at which the @request was received
 * @request: firewire request data
 */
पूर्णांक fw_get_request_speed(काष्ठा fw_request *request)
अणु
	वापस request->response.speed;
पूर्ण
EXPORT_SYMBOL(fw_get_request_speed);

अटल व्योम handle_exclusive_region_request(काष्ठा fw_card *card,
					    काष्ठा fw_packet *p,
					    काष्ठा fw_request *request,
					    अचिन्हित दीर्घ दीर्घ offset)
अणु
	काष्ठा fw_address_handler *handler;
	पूर्णांक tcode, destination, source;

	destination = HEADER_GET_DESTINATION(p->header[0]);
	source      = HEADER_GET_SOURCE(p->header[1]);
	tcode       = HEADER_GET_TCODE(p->header[0]);
	अगर (tcode == TCODE_LOCK_REQUEST)
		tcode = 0x10 + HEADER_GET_EXTENDED_TCODE(p->header[3]);

	rcu_पढ़ो_lock();
	handler = lookup_enclosing_address_handler(&address_handler_list,
						   offset, request->length);
	अगर (handler)
		handler->address_callback(card, request,
					  tcode, destination, source,
					  p->generation, offset,
					  request->data, request->length,
					  handler->callback_data);
	rcu_पढ़ो_unlock();

	अगर (!handler)
		fw_send_response(card, request, RCODE_ADDRESS_ERROR);
पूर्ण

अटल व्योम handle_fcp_region_request(काष्ठा fw_card *card,
				      काष्ठा fw_packet *p,
				      काष्ठा fw_request *request,
				      अचिन्हित दीर्घ दीर्घ offset)
अणु
	काष्ठा fw_address_handler *handler;
	पूर्णांक tcode, destination, source;

	अगर ((offset != (CSR_REGISTER_BASE | CSR_FCP_COMMAND) &&
	     offset != (CSR_REGISTER_BASE | CSR_FCP_RESPONSE)) ||
	    request->length > 0x200) अणु
		fw_send_response(card, request, RCODE_ADDRESS_ERROR);

		वापस;
	पूर्ण

	tcode       = HEADER_GET_TCODE(p->header[0]);
	destination = HEADER_GET_DESTINATION(p->header[0]);
	source      = HEADER_GET_SOURCE(p->header[1]);

	अगर (tcode != TCODE_WRITE_QUADLET_REQUEST &&
	    tcode != TCODE_WRITE_BLOCK_REQUEST) अणु
		fw_send_response(card, request, RCODE_TYPE_ERROR);

		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(handler, &address_handler_list, link) अणु
		अगर (is_enclosing_handler(handler, offset, request->length))
			handler->address_callback(card, शून्य, tcode,
						  destination, source,
						  p->generation, offset,
						  request->data,
						  request->length,
						  handler->callback_data);
	पूर्ण
	rcu_पढ़ो_unlock();

	fw_send_response(card, request, RCODE_COMPLETE);
पूर्ण

व्योम fw_core_handle_request(काष्ठा fw_card *card, काष्ठा fw_packet *p)
अणु
	काष्ठा fw_request *request;
	अचिन्हित दीर्घ दीर्घ offset;

	अगर (p->ack != ACK_PENDING && p->ack != ACK_COMPLETE)
		वापस;

	अगर (TCODE_IS_LINK_INTERNAL(HEADER_GET_TCODE(p->header[0]))) अणु
		fw_cdev_handle_phy_packet(card, p);
		वापस;
	पूर्ण

	request = allocate_request(card, p);
	अगर (request == शून्य) अणु
		/* FIXME: send अटलally allocated busy packet. */
		वापस;
	पूर्ण

	offset = ((u64)HEADER_GET_OFFSET_HIGH(p->header[1]) << 32) |
		p->header[2];

	अगर (!is_in_fcp_region(offset, request->length))
		handle_exclusive_region_request(card, p, request, offset);
	अन्यथा
		handle_fcp_region_request(card, p, request, offset);

पूर्ण
EXPORT_SYMBOL(fw_core_handle_request);

व्योम fw_core_handle_response(काष्ठा fw_card *card, काष्ठा fw_packet *p)
अणु
	काष्ठा fw_transaction *t;
	अचिन्हित दीर्घ flags;
	u32 *data;
	माप_प्रकार data_length;
	पूर्णांक tcode, tlabel, source, rcode;

	tcode	= HEADER_GET_TCODE(p->header[0]);
	tlabel	= HEADER_GET_TLABEL(p->header[0]);
	source	= HEADER_GET_SOURCE(p->header[1]);
	rcode	= HEADER_GET_RCODE(p->header[1]);

	spin_lock_irqsave(&card->lock, flags);
	list_क्रम_each_entry(t, &card->transaction_list, link) अणु
		अगर (t->node_id == source && t->tlabel == tlabel) अणु
			अगर (!try_cancel_split_समयout(t)) अणु
				spin_unlock_irqrestore(&card->lock, flags);
				जाओ समयd_out;
			पूर्ण
			list_del_init(&t->link);
			card->tlabel_mask &= ~(1ULL << t->tlabel);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&card->lock, flags);

	अगर (&t->link == &card->transaction_list) अणु
 समयd_out:
		fw_notice(card, "unsolicited response (source %x, tlabel %x)\n",
			  source, tlabel);
		वापस;
	पूर्ण

	/*
	 * FIXME: sanity check packet, is length correct, करोes tcodes
	 * and addresses match.
	 */

	चयन (tcode) अणु
	हाल TCODE_READ_QUADLET_RESPONSE:
		data = (u32 *) &p->header[3];
		data_length = 4;
		अवरोध;

	हाल TCODE_WRITE_RESPONSE:
		data = शून्य;
		data_length = 0;
		अवरोध;

	हाल TCODE_READ_BLOCK_RESPONSE:
	हाल TCODE_LOCK_RESPONSE:
		data = p->payload;
		data_length = HEADER_GET_DATA_LENGTH(p->header[3]);
		अवरोध;

	शेष:
		/* Should never happen, this is just to shut up gcc. */
		data = शून्य;
		data_length = 0;
		अवरोध;
	पूर्ण

	/*
	 * The response handler may be executed जबतक the request handler
	 * is still pending.  Cancel the request handler.
	 */
	card->driver->cancel_packet(card, &t->packet);

	t->callback(card, rcode, data, data_length, t->callback_data);
पूर्ण
EXPORT_SYMBOL(fw_core_handle_response);

/**
 * fw_rcode_string - convert a firewire result code to an error description
 * @rcode: the result code
 */
स्थिर अक्षर *fw_rcode_string(पूर्णांक rcode)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		[RCODE_COMPLETE]       = "no error",
		[RCODE_CONFLICT_ERROR] = "conflict error",
		[RCODE_DATA_ERROR]     = "data error",
		[RCODE_TYPE_ERROR]     = "type error",
		[RCODE_ADDRESS_ERROR]  = "address error",
		[RCODE_SEND_ERROR]     = "send error",
		[RCODE_CANCELLED]      = "timeout",
		[RCODE_BUSY]           = "busy",
		[RCODE_GENERATION]     = "bus reset",
		[RCODE_NO_ACK]         = "no ack",
	पूर्ण;

	अगर ((अचिन्हित पूर्णांक)rcode < ARRAY_SIZE(names) && names[rcode])
		वापस names[rcode];
	अन्यथा
		वापस "unknown";
पूर्ण
EXPORT_SYMBOL(fw_rcode_string);

अटल स्थिर काष्ठा fw_address_region topology_map_region =
	अणु .start = CSR_REGISTER_BASE | CSR_TOPOLOGY_MAP,
	  .end   = CSR_REGISTER_BASE | CSR_TOPOLOGY_MAP_END, पूर्ण;

अटल व्योम handle_topology_map(काष्ठा fw_card *card, काष्ठा fw_request *request,
		पूर्णांक tcode, पूर्णांक destination, पूर्णांक source, पूर्णांक generation,
		अचिन्हित दीर्घ दीर्घ offset, व्योम *payload, माप_प्रकार length,
		व्योम *callback_data)
अणु
	पूर्णांक start;

	अगर (!TCODE_IS_READ_REQUEST(tcode)) अणु
		fw_send_response(card, request, RCODE_TYPE_ERROR);
		वापस;
	पूर्ण

	अगर ((offset & 3) > 0 || (length & 3) > 0) अणु
		fw_send_response(card, request, RCODE_ADDRESS_ERROR);
		वापस;
	पूर्ण

	start = (offset - topology_map_region.start) / 4;
	स_नकल(payload, &card->topology_map[start], length);

	fw_send_response(card, request, RCODE_COMPLETE);
पूर्ण

अटल काष्ठा fw_address_handler topology_map = अणु
	.length			= 0x400,
	.address_callback	= handle_topology_map,
पूर्ण;

अटल स्थिर काष्ठा fw_address_region रेजिस्टरs_region =
	अणु .start = CSR_REGISTER_BASE,
	  .end   = CSR_REGISTER_BASE | CSR_CONFIG_ROM, पूर्ण;

अटल व्योम update_split_समयout(काष्ठा fw_card *card)
अणु
	अचिन्हित पूर्णांक cycles;

	cycles = card->split_समयout_hi * 8000 + (card->split_समयout_lo >> 19);

	/* minimum per IEEE 1394, maximum which करोesn't overflow OHCI */
	cycles = clamp(cycles, 800u, 3u * 8000u);

	card->split_समयout_cycles = cycles;
	card->split_समयout_jअगरfies = DIV_ROUND_UP(cycles * HZ, 8000);
पूर्ण

अटल व्योम handle_रेजिस्टरs(काष्ठा fw_card *card, काष्ठा fw_request *request,
		पूर्णांक tcode, पूर्णांक destination, पूर्णांक source, पूर्णांक generation,
		अचिन्हित दीर्घ दीर्घ offset, व्योम *payload, माप_प्रकार length,
		व्योम *callback_data)
अणु
	पूर्णांक reg = offset & ~CSR_REGISTER_BASE;
	__be32 *data = payload;
	पूर्णांक rcode = RCODE_COMPLETE;
	अचिन्हित दीर्घ flags;

	चयन (reg) अणु
	हाल CSR_PRIORITY_BUDGET:
		अगर (!card->priority_budget_implemented) अणु
			rcode = RCODE_ADDRESS_ERROR;
			अवरोध;
		पूर्ण
		fallthrough;

	हाल CSR_NODE_IDS:
		/*
		 * per IEEE 1394-2008 8.3.22.3, not IEEE 1394.1-2004 3.2.8
		 * and 9.6, but पूर्णांकeroperable with IEEE 1394.1-2004 bridges
		 */
		fallthrough;

	हाल CSR_STATE_CLEAR:
	हाल CSR_STATE_SET:
	हाल CSR_CYCLE_TIME:
	हाल CSR_BUS_TIME:
	हाल CSR_BUSY_TIMEOUT:
		अगर (tcode == TCODE_READ_QUADLET_REQUEST)
			*data = cpu_to_be32(card->driver->पढ़ो_csr(card, reg));
		अन्यथा अगर (tcode == TCODE_WRITE_QUADLET_REQUEST)
			card->driver->ग_लिखो_csr(card, reg, be32_to_cpu(*data));
		अन्यथा
			rcode = RCODE_TYPE_ERROR;
		अवरोध;

	हाल CSR_RESET_START:
		अगर (tcode == TCODE_WRITE_QUADLET_REQUEST)
			card->driver->ग_लिखो_csr(card, CSR_STATE_CLEAR,
						CSR_STATE_BIT_ABDICATE);
		अन्यथा
			rcode = RCODE_TYPE_ERROR;
		अवरोध;

	हाल CSR_SPLIT_TIMEOUT_HI:
		अगर (tcode == TCODE_READ_QUADLET_REQUEST) अणु
			*data = cpu_to_be32(card->split_समयout_hi);
		पूर्ण अन्यथा अगर (tcode == TCODE_WRITE_QUADLET_REQUEST) अणु
			spin_lock_irqsave(&card->lock, flags);
			card->split_समयout_hi = be32_to_cpu(*data) & 7;
			update_split_समयout(card);
			spin_unlock_irqrestore(&card->lock, flags);
		पूर्ण अन्यथा अणु
			rcode = RCODE_TYPE_ERROR;
		पूर्ण
		अवरोध;

	हाल CSR_SPLIT_TIMEOUT_LO:
		अगर (tcode == TCODE_READ_QUADLET_REQUEST) अणु
			*data = cpu_to_be32(card->split_समयout_lo);
		पूर्ण अन्यथा अगर (tcode == TCODE_WRITE_QUADLET_REQUEST) अणु
			spin_lock_irqsave(&card->lock, flags);
			card->split_समयout_lo =
					be32_to_cpu(*data) & 0xfff80000;
			update_split_समयout(card);
			spin_unlock_irqrestore(&card->lock, flags);
		पूर्ण अन्यथा अणु
			rcode = RCODE_TYPE_ERROR;
		पूर्ण
		अवरोध;

	हाल CSR_MAINT_UTILITY:
		अगर (tcode == TCODE_READ_QUADLET_REQUEST)
			*data = card->मुख्यt_utility_रेजिस्टर;
		अन्यथा अगर (tcode == TCODE_WRITE_QUADLET_REQUEST)
			card->मुख्यt_utility_रेजिस्टर = *data;
		अन्यथा
			rcode = RCODE_TYPE_ERROR;
		अवरोध;

	हाल CSR_BROADCAST_CHANNEL:
		अगर (tcode == TCODE_READ_QUADLET_REQUEST)
			*data = cpu_to_be32(card->broadcast_channel);
		अन्यथा अगर (tcode == TCODE_WRITE_QUADLET_REQUEST)
			card->broadcast_channel =
			    (be32_to_cpu(*data) & BROADCAST_CHANNEL_VALID) |
			    BROADCAST_CHANNEL_INITIAL;
		अन्यथा
			rcode = RCODE_TYPE_ERROR;
		अवरोध;

	हाल CSR_BUS_MANAGER_ID:
	हाल CSR_BANDWIDTH_AVAILABLE:
	हाल CSR_CHANNELS_AVAILABLE_HI:
	हाल CSR_CHANNELS_AVAILABLE_LO:
		/*
		 * FIXME: these are handled by the OHCI hardware and
		 * the stack never sees these request. If we add
		 * support क्रम a new type of controller that करोesn't
		 * handle this in hardware we need to deal with these
		 * transactions.
		 */
		BUG();
		अवरोध;

	शेष:
		rcode = RCODE_ADDRESS_ERROR;
		अवरोध;
	पूर्ण

	fw_send_response(card, request, rcode);
पूर्ण

अटल काष्ठा fw_address_handler रेजिस्टरs = अणु
	.length			= 0x400,
	.address_callback	= handle_रेजिस्टरs,
पूर्ण;

अटल व्योम handle_low_memory(काष्ठा fw_card *card, काष्ठा fw_request *request,
		पूर्णांक tcode, पूर्णांक destination, पूर्णांक source, पूर्णांक generation,
		अचिन्हित दीर्घ दीर्घ offset, व्योम *payload, माप_प्रकार length,
		व्योम *callback_data)
अणु
	/*
	 * This catches requests not handled by the physical DMA unit,
	 * i.e., wrong transaction types or unauthorized source nodes.
	 */
	fw_send_response(card, request, RCODE_TYPE_ERROR);
पूर्ण

अटल काष्ठा fw_address_handler low_memory = अणु
	.length			= FW_MAX_PHYSICAL_RANGE,
	.address_callback	= handle_low_memory,
पूर्ण;

MODULE_AUTHOR("Kristian Hoegsberg <krh@bitplanet.net>");
MODULE_DESCRIPTION("Core IEEE1394 transaction logic");
MODULE_LICENSE("GPL");

अटल स्थिर u32 venकरोr_textual_descriptor[] = अणु
	/* textual descriptor leaf () */
	0x00060000,
	0x00000000,
	0x00000000,
	0x4c696e75,		/* L i n u */
	0x78204669,		/* x   F i */
	0x72657769,		/* r e w i */
	0x72650000,		/* r e     */
पूर्ण;

अटल स्थिर u32 model_textual_descriptor[] = अणु
	/* model descriptor leaf () */
	0x00030000,
	0x00000000,
	0x00000000,
	0x4a756a75,		/* J u j u */
पूर्ण;

अटल काष्ठा fw_descriptor venकरोr_id_descriptor = अणु
	.length = ARRAY_SIZE(venकरोr_textual_descriptor),
	.immediate = 0x03001f11,
	.key = 0x81000000,
	.data = venकरोr_textual_descriptor,
पूर्ण;

अटल काष्ठा fw_descriptor model_id_descriptor = अणु
	.length = ARRAY_SIZE(model_textual_descriptor),
	.immediate = 0x17023901,
	.key = 0x81000000,
	.data = model_textual_descriptor,
पूर्ण;

अटल पूर्णांक __init fw_core_init(व्योम)
अणु
	पूर्णांक ret;

	fw_workqueue = alloc_workqueue("firewire", WQ_MEM_RECLAIM, 0);
	अगर (!fw_workqueue)
		वापस -ENOMEM;

	ret = bus_रेजिस्टर(&fw_bus_type);
	अगर (ret < 0) अणु
		destroy_workqueue(fw_workqueue);
		वापस ret;
	पूर्ण

	fw_cdev_major = रेजिस्टर_chrdev(0, "firewire", &fw_device_ops);
	अगर (fw_cdev_major < 0) अणु
		bus_unरेजिस्टर(&fw_bus_type);
		destroy_workqueue(fw_workqueue);
		वापस fw_cdev_major;
	पूर्ण

	fw_core_add_address_handler(&topology_map, &topology_map_region);
	fw_core_add_address_handler(&रेजिस्टरs, &रेजिस्टरs_region);
	fw_core_add_address_handler(&low_memory, &low_memory_region);
	fw_core_add_descriptor(&venकरोr_id_descriptor);
	fw_core_add_descriptor(&model_id_descriptor);

	वापस 0;
पूर्ण

अटल व्योम __निकास fw_core_cleanup(व्योम)
अणु
	unरेजिस्टर_chrdev(fw_cdev_major, "firewire");
	bus_unरेजिस्टर(&fw_bus_type);
	destroy_workqueue(fw_workqueue);
	idr_destroy(&fw_device_idr);
पूर्ण

module_init(fw_core_init);
module_निकास(fw_core_cleanup);
