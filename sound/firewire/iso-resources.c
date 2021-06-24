<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * isochronous resources helper functions
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/export.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश "iso-resources.h"

/**
 * fw_iso_resources_init - initializes a &काष्ठा fw_iso_resources
 * @r: the resource manager to initialize
 * @unit: the device unit क्रम which the resources will be needed
 *
 * If the device करोes not support all channel numbers, change @r->channels_mask
 * after calling this function.
 */
पूर्णांक fw_iso_resources_init(काष्ठा fw_iso_resources *r, काष्ठा fw_unit *unit)
अणु
	r->channels_mask = ~0uLL;
	r->unit = unit;
	mutex_init(&r->mutex);
	r->allocated = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fw_iso_resources_init);

/**
 * fw_iso_resources_destroy - destroy a resource manager
 * @r: the resource manager that is no दीर्घer needed
 */
व्योम fw_iso_resources_destroy(काष्ठा fw_iso_resources *r)
अणु
	WARN_ON(r->allocated);
	mutex_destroy(&r->mutex);
पूर्ण
EXPORT_SYMBOL(fw_iso_resources_destroy);

अटल अचिन्हित पूर्णांक packet_bandwidth(अचिन्हित पूर्णांक max_payload_bytes, पूर्णांक speed)
अणु
	अचिन्हित पूर्णांक bytes, s400_bytes;

	/* iso packets have three header quadlets and quadlet-aligned payload */
	bytes = 3 * 4 + ALIGN(max_payload_bytes, 4);

	/* convert to bandwidth units (quadlets at S1600 = bytes at S400) */
	अगर (speed <= SCODE_400)
		s400_bytes = bytes * (1 << (SCODE_400 - speed));
	अन्यथा
		s400_bytes = DIV_ROUND_UP(bytes, 1 << (speed - SCODE_400));

	वापस s400_bytes;
पूर्ण

अटल पूर्णांक current_bandwidth_overhead(काष्ठा fw_card *card)
अणु
	/*
	 * Under the usual pessimistic assumption (cable length 4.5 m), the
	 * isochronous overhead क्रम N cables is 1.797 तगs + N * 0.494 तगs, or
	 * 88.3 + N * 24.3 in bandwidth units.
	 *
	 * The calculation below tries to deduce N from the current gap count.
	 * If the gap count has been optimized by measuring the actual packet
	 * transmission समय, this derived overhead should be near the actual
	 * overhead as well.
	 */
	वापस card->gap_count < 63 ? card->gap_count * 97 / 10 + 89 : 512;
पूर्ण

अटल पूर्णांक रुको_isoch_resource_delay_after_bus_reset(काष्ठा fw_card *card)
अणु
	क्रम (;;) अणु
		s64 delay = (card->reset_jअगरfies + HZ) - get_jअगरfies_64();
		अगर (delay <= 0)
			वापस 0;
		अगर (schedule_समयout_पूर्णांकerruptible(delay) > 0)
			वापस -ERESTARTSYS;
	पूर्ण
पूर्ण

/**
 * fw_iso_resources_allocate - allocate isochronous channel and bandwidth
 * @r: the resource manager
 * @max_payload_bytes: the amount of data (including CIP headers) per packet
 * @speed: the speed (e.g., SCODE_400) at which the packets will be sent
 *
 * This function allocates one isochronous channel and enough bandwidth क्रम the
 * specअगरied packet size.
 *
 * Returns the channel number that the caller must use क्रम streaming, or
 * a negative error code.  Due to potentionally दीर्घ delays, this function is
 * पूर्णांकerruptible and can वापस -ERESTARTSYS.  On success, the caller is
 * responsible क्रम calling fw_iso_resources_update() on bus resets, and
 * fw_iso_resources_मुक्त() when the resources are not दीर्घer needed.
 */
पूर्णांक fw_iso_resources_allocate(काष्ठा fw_iso_resources *r,
			      अचिन्हित पूर्णांक max_payload_bytes, पूर्णांक speed)
अणु
	काष्ठा fw_card *card = fw_parent_device(r->unit)->card;
	पूर्णांक bandwidth, channel, err;

	अगर (WARN_ON(r->allocated))
		वापस -EBADFD;

	r->bandwidth = packet_bandwidth(max_payload_bytes, speed);

retry_after_bus_reset:
	spin_lock_irq(&card->lock);
	r->generation = card->generation;
	r->bandwidth_overhead = current_bandwidth_overhead(card);
	spin_unlock_irq(&card->lock);

	err = रुको_isoch_resource_delay_after_bus_reset(card);
	अगर (err < 0)
		वापस err;

	mutex_lock(&r->mutex);

	bandwidth = r->bandwidth + r->bandwidth_overhead;
	fw_iso_resource_manage(card, r->generation, r->channels_mask,
			       &channel, &bandwidth, true);
	अगर (channel == -EAGAIN) अणु
		mutex_unlock(&r->mutex);
		जाओ retry_after_bus_reset;
	पूर्ण
	अगर (channel >= 0) अणु
		r->channel = channel;
		r->allocated = true;
	पूर्ण अन्यथा अणु
		अगर (channel == -EBUSY)
			dev_err(&r->unit->device,
				"isochronous resources exhausted\n");
		अन्यथा
			dev_err(&r->unit->device,
				"isochronous resource allocation failed\n");
	पूर्ण

	mutex_unlock(&r->mutex);

	वापस channel;
पूर्ण
EXPORT_SYMBOL(fw_iso_resources_allocate);

/**
 * fw_iso_resources_update - update resource allocations after a bus reset
 * @r: the resource manager
 *
 * This function must be called from the driver's .update handler to पुनः_स्मृतिate
 * any resources that were allocated beक्रमe the bus reset.  It is safe to call
 * this function अगर no resources are currently allocated.
 *
 * Returns a negative error code on failure.  If this happens, the caller must
 * stop streaming.
 */
पूर्णांक fw_iso_resources_update(काष्ठा fw_iso_resources *r)
अणु
	काष्ठा fw_card *card = fw_parent_device(r->unit)->card;
	पूर्णांक bandwidth, channel;

	mutex_lock(&r->mutex);

	अगर (!r->allocated) अणु
		mutex_unlock(&r->mutex);
		वापस 0;
	पूर्ण

	spin_lock_irq(&card->lock);
	r->generation = card->generation;
	r->bandwidth_overhead = current_bandwidth_overhead(card);
	spin_unlock_irq(&card->lock);

	bandwidth = r->bandwidth + r->bandwidth_overhead;

	fw_iso_resource_manage(card, r->generation, 1uLL << r->channel,
			       &channel, &bandwidth, true);
	/*
	 * When another bus reset happens, pretend that the allocation
	 * succeeded; we will try again क्रम the new generation later.
	 */
	अगर (channel < 0 && channel != -EAGAIN) अणु
		r->allocated = false;
		अगर (channel == -EBUSY)
			dev_err(&r->unit->device,
				"isochronous resources exhausted\n");
		अन्यथा
			dev_err(&r->unit->device,
				"isochronous resource allocation failed\n");
	पूर्ण

	mutex_unlock(&r->mutex);

	वापस channel;
पूर्ण
EXPORT_SYMBOL(fw_iso_resources_update);

/**
 * fw_iso_resources_मुक्त - मुक्तs allocated resources
 * @r: the resource manager
 *
 * This function deallocates the channel and bandwidth, अगर allocated.
 */
व्योम fw_iso_resources_मुक्त(काष्ठा fw_iso_resources *r)
अणु
	काष्ठा fw_card *card;
	पूर्णांक bandwidth, channel;

	/* Not initialized. */
	अगर (r->unit == शून्य)
		वापस;
	card = fw_parent_device(r->unit)->card;

	mutex_lock(&r->mutex);

	अगर (r->allocated) अणु
		bandwidth = r->bandwidth + r->bandwidth_overhead;
		fw_iso_resource_manage(card, r->generation, 1uLL << r->channel,
				       &channel, &bandwidth, false);
		अगर (channel < 0)
			dev_err(&r->unit->device,
				"isochronous resource deallocation failed\n");

		r->allocated = false;
	पूर्ण

	mutex_unlock(&r->mutex);
पूर्ण
EXPORT_SYMBOL(fw_iso_resources_मुक्त);
