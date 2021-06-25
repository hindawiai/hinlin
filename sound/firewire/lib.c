<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * miscellaneous helper functions
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश "lib.h"

#घोषणा ERROR_RETRY_DELAY_MS	20

/**
 * snd_fw_transaction - send a request and रुको क्रम its completion
 * @unit: the driver's unit on the target device
 * @tcode: the transaction code
 * @offset: the address in the target's address space
 * @buffer: input/output data
 * @length: length of @buffer
 * @flags: use %FW_FIXED_GENERATION and add the generation value to attempt the
 *         request only in that generation; use %FW_QUIET to suppress error
 *         messages
 *
 * Submits an asynchronous request to the target device, and रुकोs क्रम the
 * response.  The node ID and the current generation are derived from @unit.
 * On a bus reset or an error, the transaction is retried a few बार.
 * Returns zero on success, or a negative error code.
 */
पूर्णांक snd_fw_transaction(काष्ठा fw_unit *unit, पूर्णांक tcode,
		       u64 offset, व्योम *buffer, माप_प्रकार length,
		       अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fw_device *device = fw_parent_device(unit);
	पूर्णांक generation, rcode, tries = 0;

	generation = flags & FW_GENERATION_MASK;
	क्रम (;;) अणु
		अगर (!(flags & FW_FIXED_GENERATION)) अणु
			generation = device->generation;
			smp_rmb(); /* node_id vs. generation */
		पूर्ण
		rcode = fw_run_transaction(device->card, tcode,
					   device->node_id, generation,
					   device->max_speed, offset,
					   buffer, length);

		अगर (rcode == RCODE_COMPLETE)
			वापस 0;

		अगर (rcode == RCODE_GENERATION && (flags & FW_FIXED_GENERATION))
			वापस -EAGAIN;

		अगर (rcode_is_permanent_error(rcode) || ++tries >= 3) अणु
			अगर (!(flags & FW_QUIET))
				dev_err(&unit->device,
					"transaction failed: %s\n",
					fw_rcode_string(rcode));
			वापस -EIO;
		पूर्ण

		msleep(ERROR_RETRY_DELAY_MS);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_fw_transaction);

#घोषणा PROBE_DELAY_MS		(2 * MSEC_PER_SEC)

/**
 * snd_fw_schedule_registration - schedule work क्रम sound card registration
 * @unit: an instance क्रम unit on IEEE 1394 bus
 * @dwork: delayed work with callback function
 *
 * This function is not deचिन्हित क्रम general purposes. When new unit is
 * connected to IEEE 1394 bus, the bus is under bus-reset state because of
 * topological change. In this state, units tend to fail both of asynchronous
 * and isochronous communication. To aव्योम this problem, this function is used
 * to postpone sound card registration after the state. The callers must
 * set up instance of delayed work in advance.
 */
व्योम snd_fw_schedule_registration(काष्ठा fw_unit *unit,
				  काष्ठा delayed_work *dwork)
अणु
	u64 now, delay;

	now = get_jअगरfies_64();
	delay = fw_parent_device(unit)->card->reset_jअगरfies
					+ msecs_to_jअगरfies(PROBE_DELAY_MS);

	अगर (समय_after64(delay, now))
		delay -= now;
	अन्यथा
		delay = 0;

	mod_delayed_work(प्रणाली_wq, dwork, delay);
पूर्ण
EXPORT_SYMBOL(snd_fw_schedule_registration);

MODULE_DESCRIPTION("FireWire audio helper functions");
MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_LICENSE("GPL v2");
