<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010 - 2015 UNISYS CORPORATION
 * All rights reserved.
 */

/*
 *  This provides s-Par channel communication primitives, which are
 *  independent of the mechanism used to access the channel data.
 */

#समावेश <linux/uuid.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/visorbus.h>

#समावेश "visorbus_private.h"
#समावेश "controlvmchannel.h"

#घोषणा VISOR_DRV_NAME "visorchannel"

#घोषणा VISOR_CONSOLEVIDEO_CHANNEL_GUID \
	GUID_INIT(0x3cd6e705, 0xd6a2, 0x4aa5, \
		  0xad, 0x5c, 0x7b, 0x8, 0x88, 0x9d, 0xff, 0xe2)

अटल स्थिर guid_t visor_video_guid = VISOR_CONSOLEVIDEO_CHANNEL_GUID;

काष्ठा visorchannel अणु
	u64 physaddr;
	uदीर्घ nbytes;
	व्योम *mapped;
	bool requested;
	काष्ठा channel_header chan_hdr;
	guid_t guid;
	/*
	 * channel creator knows अगर more than one thपढ़ो will be inserting or
	 * removing
	 */
	bool needs_lock;
	/* protect head ग_लिखोs in chan_hdr */
	spinlock_t insert_lock;
	/* protect tail ग_लिखोs in chan_hdr */
	spinlock_t हटाओ_lock;
	guid_t type;
	guid_t inst;
पूर्ण;

व्योम visorchannel_destroy(काष्ठा visorchannel *channel)
अणु
	अगर (!channel)
		वापस;

	अगर (channel->mapped) अणु
		memunmap(channel->mapped);
		अगर (channel->requested)
			release_mem_region(channel->physaddr, channel->nbytes);
	पूर्ण
	kमुक्त(channel);
पूर्ण

u64 visorchannel_get_physaddr(काष्ठा visorchannel *channel)
अणु
	वापस channel->physaddr;
पूर्ण

uदीर्घ visorchannel_get_nbytes(काष्ठा visorchannel *channel)
अणु
	वापस channel->nbytes;
पूर्ण

अक्षर *visorchannel_guid_id(स्थिर guid_t *guid, अक्षर *s)
अणु
	प्र_लिखो(s, "%pUL", guid);
	वापस s;
पूर्ण

अक्षर *visorchannel_id(काष्ठा visorchannel *channel, अक्षर *s)
अणु
	वापस visorchannel_guid_id(&channel->guid, s);
पूर्ण

अक्षर *visorchannel_zoneid(काष्ठा visorchannel *channel, अक्षर *s)
अणु
	वापस visorchannel_guid_id(&channel->chan_hdr.zone_guid, s);
पूर्ण

u64 visorchannel_get_clientpartition(काष्ठा visorchannel *channel)
अणु
	वापस channel->chan_hdr.partition_handle;
पूर्ण

पूर्णांक visorchannel_set_clientpartition(काष्ठा visorchannel *channel,
				     u64 partition_handle)
अणु
	channel->chan_hdr.partition_handle = partition_handle;
	वापस 0;
पूर्ण

/**
 * visorchannel_get_guid() - queries the GUID of the designated channel
 * @channel: the channel to query
 *
 * Return: the GUID of the provided channel
 */
स्थिर guid_t *visorchannel_get_guid(काष्ठा visorchannel *channel)
अणु
	वापस &channel->guid;
पूर्ण
EXPORT_SYMBOL_GPL(visorchannel_get_guid);

पूर्णांक visorchannel_पढ़ो(काष्ठा visorchannel *channel, uदीर्घ offset, व्योम *dest,
		      uदीर्घ nbytes)
अणु
	अगर (offset + nbytes > channel->nbytes)
		वापस -EIO;

	स_नकल(dest, channel->mapped + offset, nbytes);
	वापस 0;
पूर्ण

पूर्णांक visorchannel_ग_लिखो(काष्ठा visorchannel *channel, uदीर्घ offset, व्योम *dest,
		       uदीर्घ nbytes)
अणु
	माप_प्रकार chdr_size = माप(काष्ठा channel_header);
	माप_प्रकार copy_size;

	अगर (offset + nbytes > channel->nbytes)
		वापस -EIO;

	अगर (offset < chdr_size) अणु
		copy_size = min(chdr_size - offset, nbytes);
		स_नकल(((अक्षर *)(&channel->chan_hdr)) + offset,
		       dest, copy_size);
	पूर्ण
	स_नकल(channel->mapped + offset, dest, nbytes);
	वापस 0;
पूर्ण

व्योम *visorchannel_get_header(काष्ठा visorchannel *channel)
अणु
	वापस &channel->chan_hdr;
पूर्ण

/*
 * Return offset of a specअगरic SIGNAL_QUEUE_HEADER from the beginning of a
 * channel header
 */
अटल पूर्णांक sig_queue_offset(काष्ठा channel_header *chan_hdr, पूर्णांक q)
अणु
	वापस ((chan_hdr)->ch_space_offset +
	       ((q) * माप(काष्ठा संकेत_queue_header)));
पूर्ण

/*
 * Return offset of a specअगरic queue entry (data) from the beginning of a
 * channel header
 */
अटल पूर्णांक sig_data_offset(काष्ठा channel_header *chan_hdr, पूर्णांक q,
			   काष्ठा संकेत_queue_header *sig_hdr, पूर्णांक slot)
अणु
	वापस (sig_queue_offset(chan_hdr, q) + sig_hdr->sig_base_offset +
	       (slot * sig_hdr->संकेत_size));
पूर्ण

/*
 * Write the contents of a specअगरic field within a SIGNAL_QUEUE_HEADER back पूर्णांकo
 * host memory
 */
#घोषणा SIG_WRITE_FIELD(channel, queue, sig_hdr, FIELD) \
	visorchannel_ग_लिखो(channel, \
			   sig_queue_offset(&channel->chan_hdr, queue) + \
			   दुरत्व(काष्ठा संकेत_queue_header, FIELD), \
			   &((sig_hdr)->FIELD), \
			   माप((sig_hdr)->FIELD))

अटल पूर्णांक sig_पढ़ो_header(काष्ठा visorchannel *channel, u32 queue,
			   काष्ठा संकेत_queue_header *sig_hdr)
अणु
	अगर (channel->chan_hdr.ch_space_offset < माप(काष्ठा channel_header))
		वापस -EINVAL;

	/* Read the appropriate SIGNAL_QUEUE_HEADER पूर्णांकo local memory. */
	वापस visorchannel_पढ़ो(channel,
				 sig_queue_offset(&channel->chan_hdr, queue),
				 sig_hdr, माप(काष्ठा संकेत_queue_header));
पूर्ण

अटल पूर्णांक sig_पढ़ो_data(काष्ठा visorchannel *channel, u32 queue,
			 काष्ठा संकेत_queue_header *sig_hdr, u32 slot,
			 व्योम *data)
अणु
	पूर्णांक संकेत_data_offset = sig_data_offset(&channel->chan_hdr, queue,
						 sig_hdr, slot);

	वापस visorchannel_पढ़ो(channel, संकेत_data_offset,
				 data, sig_hdr->संकेत_size);
पूर्ण

अटल पूर्णांक sig_ग_लिखो_data(काष्ठा visorchannel *channel, u32 queue,
			  काष्ठा संकेत_queue_header *sig_hdr, u32 slot,
			  व्योम *data)
अणु
	पूर्णांक संकेत_data_offset = sig_data_offset(&channel->chan_hdr, queue,
						 sig_hdr, slot);

	वापस visorchannel_ग_लिखो(channel, संकेत_data_offset,
				  data, sig_hdr->संकेत_size);
पूर्ण

अटल पूर्णांक संकेतहटाओ_inner(काष्ठा visorchannel *channel, u32 queue,
			      व्योम *msg)
अणु
	काष्ठा संकेत_queue_header sig_hdr;
	पूर्णांक error;

	error = sig_पढ़ो_header(channel, queue, &sig_hdr);
	अगर (error)
		वापस error;
	/* No संकेतs to हटाओ; have caller try again. */
	अगर (sig_hdr.head == sig_hdr.tail)
		वापस -EAGAIN;
	sig_hdr.tail = (sig_hdr.tail + 1) % sig_hdr.max_slots;
	error = sig_पढ़ो_data(channel, queue, &sig_hdr, sig_hdr.tail, msg);
	अगर (error)
		वापस error;
	sig_hdr.num_received++;
	/*
	 * For each data field in SIGNAL_QUEUE_HEADER that was modअगरied, update
	 * host memory. Required क्रम channel sync.
	 */
	mb();
	error = SIG_WRITE_FIELD(channel, queue, &sig_hdr, tail);
	अगर (error)
		वापस error;
	error = SIG_WRITE_FIELD(channel, queue, &sig_hdr, num_received);
	अगर (error)
		वापस error;
	वापस 0;
पूर्ण

/**
 * visorchannel_संकेतहटाओ() - हटाओs a message from the designated
 *                               channel/queue
 * @channel: the channel the message will be हटाओd from
 * @queue:   the queue the message will be हटाओd from
 * @msg:     the message to हटाओ
 *
 * Return: पूर्णांकeger error code indicating the status of the removal
 */
पूर्णांक visorchannel_संकेतहटाओ(काष्ठा visorchannel *channel, u32 queue,
			      व्योम *msg)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	अगर (channel->needs_lock) अणु
		spin_lock_irqsave(&channel->हटाओ_lock, flags);
		rc = संकेतहटाओ_inner(channel, queue, msg);
		spin_unlock_irqrestore(&channel->हटाओ_lock, flags);
	पूर्ण अन्यथा अणु
		rc = संकेतहटाओ_inner(channel, queue, msg);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(visorchannel_संकेतहटाओ);

अटल bool queue_empty(काष्ठा visorchannel *channel, u32 queue)
अणु
	काष्ठा संकेत_queue_header sig_hdr;

	अगर (sig_पढ़ो_header(channel, queue, &sig_hdr))
		वापस true;
	वापस (sig_hdr.head == sig_hdr.tail);
पूर्ण

/**
 * visorchannel_संकेतempty() - checks अगर the designated channel/queue contains
 *				any messages
 * @channel: the channel to query
 * @queue:   the queue in the channel to query
 *
 * Return: boolean indicating whether any messages in the designated
 *         channel/queue are present
 */
bool visorchannel_संकेतempty(काष्ठा visorchannel *channel, u32 queue)
अणु
	bool rc;
	अचिन्हित दीर्घ flags;

	अगर (!channel->needs_lock)
		वापस queue_empty(channel, queue);
	spin_lock_irqsave(&channel->हटाओ_lock, flags);
	rc = queue_empty(channel, queue);
	spin_unlock_irqrestore(&channel->हटाओ_lock, flags);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(visorchannel_संकेतempty);

अटल पूर्णांक संकेतinsert_inner(काष्ठा visorchannel *channel, u32 queue,
			      व्योम *msg)
अणु
	काष्ठा संकेत_queue_header sig_hdr;
	पूर्णांक err;

	err = sig_पढ़ो_header(channel, queue, &sig_hdr);
	अगर (err)
		वापस err;
	sig_hdr.head = (sig_hdr.head + 1) % sig_hdr.max_slots;
	अगर (sig_hdr.head == sig_hdr.tail) अणु
		sig_hdr.num_overflows++;
		err = SIG_WRITE_FIELD(channel, queue, &sig_hdr, num_overflows);
		अगर (err)
			वापस err;
		वापस -EIO;
	पूर्ण
	err = sig_ग_लिखो_data(channel, queue, &sig_hdr, sig_hdr.head, msg);
	अगर (err)
		वापस err;
	sig_hdr.num_sent++;
	/*
	 * For each data field in SIGNAL_QUEUE_HEADER that was modअगरied, update
	 * host memory. Required क्रम channel sync.
	 */
	mb();
	err = SIG_WRITE_FIELD(channel, queue, &sig_hdr, head);
	अगर (err)
		वापस err;
	err = SIG_WRITE_FIELD(channel, queue, &sig_hdr, num_sent);
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

/*
 * visorchannel_create() - creates the काष्ठा visorchannel असलtraction क्रम a
 *                         data area in memory, but करोes NOT modअगरy this data
 *                         area
 * @physaddr:      physical address of start of channel
 * @gfp:           gfp_t to use when allocating memory क्रम the data काष्ठा
 * @guid:          GUID that identअगरies channel type;
 * @needs_lock:    must specअगरy true अगर you have multiple thपढ़ोs of execution
 *                 that will be calling visorchannel methods of this
 *                 visorchannel at the same समय
 *
 * Return: poपूर्णांकer to visorchannel that was created अगर successful,
 *         otherwise शून्य
 */
काष्ठा visorchannel *visorchannel_create(u64 physaddr, gfp_t gfp,
					 स्थिर guid_t *guid, bool needs_lock)
अणु
	काष्ठा visorchannel *channel;
	पूर्णांक err;
	माप_प्रकार size = माप(काष्ठा channel_header);

	अगर (physaddr == 0)
		वापस शून्य;

	channel = kzalloc(माप(*channel), gfp);
	अगर (!channel)
		वापस शून्य;
	channel->needs_lock = needs_lock;
	spin_lock_init(&channel->insert_lock);
	spin_lock_init(&channel->हटाओ_lock);
	/*
	 * Video driver स्थिरains the efi framebuffer so it will get a conflict
	 * resource when requesting its full mem region. Since we are only
	 * using the efi framebuffer क्रम video we can ignore this. Remember that
	 * we haven't requested it so we don't try to release later on.
	 */
	channel->requested = request_mem_region(physaddr, size, VISOR_DRV_NAME);
	अगर (!channel->requested && !guid_equal(guid, &visor_video_guid))
		/* we only care about errors अगर this is not the video channel */
		जाओ err_destroy_channel;
	channel->mapped = memremap(physaddr, size, MEMREMAP_WB);
	अगर (!channel->mapped) अणु
		release_mem_region(physaddr, size);
		जाओ err_destroy_channel;
	पूर्ण
	channel->physaddr = physaddr;
	channel->nbytes = size;
	err = visorchannel_पढ़ो(channel, 0, &channel->chan_hdr, size);
	अगर (err)
		जाओ err_destroy_channel;
	size = (uदीर्घ)channel->chan_hdr.size;
	memunmap(channel->mapped);
	अगर (channel->requested)
		release_mem_region(channel->physaddr, channel->nbytes);
	channel->mapped = शून्य;
	channel->requested = request_mem_region(channel->physaddr, size,
						VISOR_DRV_NAME);
	अगर (!channel->requested && !guid_equal(guid, &visor_video_guid))
		/* we only care about errors अगर this is not the video channel */
		जाओ err_destroy_channel;
	channel->mapped = memremap(channel->physaddr, size, MEMREMAP_WB);
	अगर (!channel->mapped) अणु
		release_mem_region(channel->physaddr, size);
		जाओ err_destroy_channel;
	पूर्ण
	channel->nbytes = size;
	guid_copy(&channel->guid, guid);
	वापस channel;

err_destroy_channel:
	visorchannel_destroy(channel);
	वापस शून्य;
पूर्ण

/**
 * visorchannel_संकेतinsert() - inserts a message पूर्णांकo the designated
 *                               channel/queue
 * @channel: the channel the message will be added to
 * @queue:   the queue the message will be added to
 * @msg:     the message to insert
 *
 * Return: पूर्णांकeger error code indicating the status of the insertion
 */
पूर्णांक visorchannel_संकेतinsert(काष्ठा visorchannel *channel, u32 queue,
			      व्योम *msg)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	अगर (channel->needs_lock) अणु
		spin_lock_irqsave(&channel->insert_lock, flags);
		rc = संकेतinsert_inner(channel, queue, msg);
		spin_unlock_irqrestore(&channel->insert_lock, flags);
	पूर्ण अन्यथा अणु
		rc = संकेतinsert_inner(channel, queue, msg);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(visorchannel_संकेतinsert);
