<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Connection Management Procedures (IEC 61883-1) helper functions
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश "lib.h"
#समावेश "iso-resources.h"
#समावेश "cmp.h"

/* MPR common fields */
#घोषणा MPR_SPEED_MASK		0xc0000000
#घोषणा MPR_SPEED_SHIFT		30
#घोषणा MPR_XSPEED_MASK		0x00000060
#घोषणा MPR_XSPEED_SHIFT	5
#घोषणा MPR_PLUGS_MASK		0x0000001f

/* PCR common fields */
#घोषणा PCR_ONLINE		0x80000000
#घोषणा PCR_BCAST_CONN		0x40000000
#घोषणा PCR_P2P_CONN_MASK	0x3f000000
#घोषणा PCR_P2P_CONN_SHIFT	24
#घोषणा PCR_CHANNEL_MASK	0x003f0000
#घोषणा PCR_CHANNEL_SHIFT	16

/* oPCR specअगरic fields */
#घोषणा OPCR_XSPEED_MASK	0x00C00000
#घोषणा OPCR_XSPEED_SHIFT	22
#घोषणा OPCR_SPEED_MASK		0x0000C000
#घोषणा OPCR_SPEED_SHIFT	14
#घोषणा OPCR_OVERHEAD_ID_MASK	0x00003C00
#घोषणा OPCR_OVERHEAD_ID_SHIFT	10

क्रमागत bus_reset_handling अणु
	ABORT_ON_BUS_RESET,
	SUCCEED_ON_BUS_RESET,
पूर्ण;

अटल __म_लिखो(2, 3)
व्योम cmp_error(काष्ठा cmp_connection *c, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;

	बहु_शुरू(va, fmt);
	dev_err(&c->resources.unit->device, "%cPCR%u: %pV",
		(c->direction == CMP_INPUT) ? 'i' : 'o',
		c->pcr_index, &(काष्ठा va_क्रमmat)अणु fmt, &va पूर्ण);
	बहु_पूर्ण(va);
पूर्ण

अटल u64 mpr_address(काष्ठा cmp_connection *c)
अणु
	अगर (c->direction == CMP_INPUT)
		वापस CSR_REGISTER_BASE + CSR_IMPR;
	अन्यथा
		वापस CSR_REGISTER_BASE + CSR_OMPR;
पूर्ण

अटल u64 pcr_address(काष्ठा cmp_connection *c)
अणु
	अगर (c->direction == CMP_INPUT)
		वापस CSR_REGISTER_BASE + CSR_IPCR(c->pcr_index);
	अन्यथा
		वापस CSR_REGISTER_BASE + CSR_OPCR(c->pcr_index);
पूर्ण

अटल पूर्णांक pcr_modअगरy(काष्ठा cmp_connection *c,
		      __be32 (*modअगरy)(काष्ठा cmp_connection *c, __be32 old),
		      पूर्णांक (*check)(काष्ठा cmp_connection *c, __be32 pcr),
		      क्रमागत bus_reset_handling bus_reset_handling)
अणु
	__be32 old_arg, buffer[2];
	पूर्णांक err;

	buffer[0] = c->last_pcr_value;
	क्रम (;;) अणु
		old_arg = buffer[0];
		buffer[1] = modअगरy(c, buffer[0]);

		err = snd_fw_transaction(
				c->resources.unit, TCODE_LOCK_COMPARE_SWAP,
				pcr_address(c), buffer, 8,
				FW_FIXED_GENERATION | c->resources.generation);

		अगर (err < 0) अणु
			अगर (err == -EAGAIN &&
			    bus_reset_handling == SUCCEED_ON_BUS_RESET)
				err = 0;
			वापस err;
		पूर्ण

		अगर (buffer[0] == old_arg) /* success? */
			अवरोध;

		अगर (check) अणु
			err = check(c, buffer[0]);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	c->last_pcr_value = buffer[1];

	वापस 0;
पूर्ण


/**
 * cmp_connection_init - initializes a connection manager
 * @c: the connection manager to initialize
 * @unit: a unit of the target device
 * @direction: input or output
 * @pcr_index: the index of the iPCR/oPCR on the target device
 */
पूर्णांक cmp_connection_init(काष्ठा cmp_connection *c,
			काष्ठा fw_unit *unit,
			क्रमागत cmp_direction direction,
			अचिन्हित पूर्णांक pcr_index)
अणु
	__be32 mpr_be;
	u32 mpr;
	पूर्णांक err;

	c->direction = direction;
	err = snd_fw_transaction(unit, TCODE_READ_QUADLET_REQUEST,
				 mpr_address(c), &mpr_be, 4, 0);
	अगर (err < 0)
		वापस err;
	mpr = be32_to_cpu(mpr_be);

	अगर (pcr_index >= (mpr & MPR_PLUGS_MASK))
		वापस -EINVAL;

	err = fw_iso_resources_init(&c->resources, unit);
	अगर (err < 0)
		वापस err;

	c->connected = false;
	mutex_init(&c->mutex);
	c->last_pcr_value = cpu_to_be32(0x80000000);
	c->pcr_index = pcr_index;
	c->max_speed = (mpr & MPR_SPEED_MASK) >> MPR_SPEED_SHIFT;
	अगर (c->max_speed == SCODE_BETA)
		c->max_speed += (mpr & MPR_XSPEED_MASK) >> MPR_XSPEED_SHIFT;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cmp_connection_init);

/**
 * cmp_connection_check_used - check connection is alपढ़ोy esablished or not
 * @c: the connection manager to be checked
 * @used: the poपूर्णांकer to store the result of checking the connection
 */
पूर्णांक cmp_connection_check_used(काष्ठा cmp_connection *c, bool *used)
अणु
	__be32 pcr;
	पूर्णांक err;

	err = snd_fw_transaction(
			c->resources.unit, TCODE_READ_QUADLET_REQUEST,
			pcr_address(c), &pcr, 4, 0);
	अगर (err >= 0)
		*used = !!(pcr & cpu_to_be32(PCR_BCAST_CONN |
					     PCR_P2P_CONN_MASK));

	वापस err;
पूर्ण
EXPORT_SYMBOL(cmp_connection_check_used);

/**
 * cmp_connection_destroy - मुक्त connection manager resources
 * @c: the connection manager
 */
व्योम cmp_connection_destroy(काष्ठा cmp_connection *c)
अणु
	WARN_ON(c->connected);
	mutex_destroy(&c->mutex);
	fw_iso_resources_destroy(&c->resources);
पूर्ण
EXPORT_SYMBOL(cmp_connection_destroy);

पूर्णांक cmp_connection_reserve(काष्ठा cmp_connection *c,
			   अचिन्हित पूर्णांक max_payload_bytes)
अणु
	पूर्णांक err;

	mutex_lock(&c->mutex);

	अगर (WARN_ON(c->resources.allocated)) अणु
		err = -EBUSY;
		जाओ end;
	पूर्ण

	c->speed = min(c->max_speed,
		       fw_parent_device(c->resources.unit)->max_speed);

	err = fw_iso_resources_allocate(&c->resources, max_payload_bytes,
					c->speed);
end:
	mutex_unlock(&c->mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL(cmp_connection_reserve);

व्योम cmp_connection_release(काष्ठा cmp_connection *c)
अणु
	mutex_lock(&c->mutex);
	fw_iso_resources_मुक्त(&c->resources);
	mutex_unlock(&c->mutex);
पूर्ण
EXPORT_SYMBOL(cmp_connection_release);

अटल __be32 ipcr_set_modअगरy(काष्ठा cmp_connection *c, __be32 ipcr)
अणु
	ipcr &= ~cpu_to_be32(PCR_BCAST_CONN |
			     PCR_P2P_CONN_MASK |
			     PCR_CHANNEL_MASK);
	ipcr |= cpu_to_be32(1 << PCR_P2P_CONN_SHIFT);
	ipcr |= cpu_to_be32(c->resources.channel << PCR_CHANNEL_SHIFT);

	वापस ipcr;
पूर्ण

अटल पूर्णांक get_overhead_id(काष्ठा cmp_connection *c)
अणु
	पूर्णांक id;

	/*
	 * apply "oPCR overhead ID encoding"
	 * the encoding table can convert up to 512.
	 * here the value over 512 is converted as the same way as 512.
	 */
	क्रम (id = 1; id < 16; id++) अणु
		अगर (c->resources.bandwidth_overhead < (id << 5))
			अवरोध;
	पूर्ण
	अगर (id == 16)
		id = 0;

	वापस id;
पूर्ण

अटल __be32 opcr_set_modअगरy(काष्ठा cmp_connection *c, __be32 opcr)
अणु
	अचिन्हित पूर्णांक spd, xspd;

	/* generate speed and extended speed field value */
	अगर (c->speed > SCODE_400) अणु
		spd  = SCODE_800;
		xspd = c->speed - SCODE_800;
	पूर्ण अन्यथा अणु
		spd = c->speed;
		xspd = 0;
	पूर्ण

	opcr &= ~cpu_to_be32(PCR_BCAST_CONN |
			     PCR_P2P_CONN_MASK |
			     OPCR_XSPEED_MASK |
			     PCR_CHANNEL_MASK |
			     OPCR_SPEED_MASK |
			     OPCR_OVERHEAD_ID_MASK);
	opcr |= cpu_to_be32(1 << PCR_P2P_CONN_SHIFT);
	opcr |= cpu_to_be32(xspd << OPCR_XSPEED_SHIFT);
	opcr |= cpu_to_be32(c->resources.channel << PCR_CHANNEL_SHIFT);
	opcr |= cpu_to_be32(spd << OPCR_SPEED_SHIFT);
	opcr |= cpu_to_be32(get_overhead_id(c) << OPCR_OVERHEAD_ID_SHIFT);

	वापस opcr;
पूर्ण

अटल पूर्णांक pcr_set_check(काष्ठा cmp_connection *c, __be32 pcr)
अणु
	अगर (pcr & cpu_to_be32(PCR_BCAST_CONN |
			      PCR_P2P_CONN_MASK)) अणु
		cmp_error(c, "plug is already in use\n");
		वापस -EBUSY;
	पूर्ण
	अगर (!(pcr & cpu_to_be32(PCR_ONLINE))) अणु
		cmp_error(c, "plug is not on-line\n");
		वापस -ECONNREFUSED;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cmp_connection_establish - establish a connection to the target
 * @c: the connection manager
 *
 * This function establishes a poपूर्णांक-to-poपूर्णांक connection from the local
 * computer to the target by allocating isochronous resources (channel and
 * bandwidth) and setting the target's input/output plug control रेजिस्टर.
 * When this function succeeds, the caller is responsible क्रम starting
 * transmitting packets.
 */
पूर्णांक cmp_connection_establish(काष्ठा cmp_connection *c)
अणु
	पूर्णांक err;

	mutex_lock(&c->mutex);

	अगर (WARN_ON(c->connected)) अणु
		mutex_unlock(&c->mutex);
		वापस -EISCONN;
	पूर्ण

retry_after_bus_reset:
	अगर (c->direction == CMP_OUTPUT)
		err = pcr_modअगरy(c, opcr_set_modअगरy, pcr_set_check,
				 ABORT_ON_BUS_RESET);
	अन्यथा
		err = pcr_modअगरy(c, ipcr_set_modअगरy, pcr_set_check,
				 ABORT_ON_BUS_RESET);

	अगर (err == -EAGAIN) अणु
		err = fw_iso_resources_update(&c->resources);
		अगर (err >= 0)
			जाओ retry_after_bus_reset;
	पूर्ण
	अगर (err >= 0)
		c->connected = true;

	mutex_unlock(&c->mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL(cmp_connection_establish);

/**
 * cmp_connection_update - update the connection after a bus reset
 * @c: the connection manager
 *
 * This function must be called from the driver's .update handler to
 * reestablish any connection that might have been active.
 *
 * Returns zero on success, or a negative error code.  On an error, the
 * connection is broken and the caller must stop transmitting iso packets.
 */
पूर्णांक cmp_connection_update(काष्ठा cmp_connection *c)
अणु
	पूर्णांक err;

	mutex_lock(&c->mutex);

	अगर (!c->connected) अणु
		mutex_unlock(&c->mutex);
		वापस 0;
	पूर्ण

	err = fw_iso_resources_update(&c->resources);
	अगर (err < 0)
		जाओ err_unconnect;

	अगर (c->direction == CMP_OUTPUT)
		err = pcr_modअगरy(c, opcr_set_modअगरy, pcr_set_check,
				 SUCCEED_ON_BUS_RESET);
	अन्यथा
		err = pcr_modअगरy(c, ipcr_set_modअगरy, pcr_set_check,
				 SUCCEED_ON_BUS_RESET);

	अगर (err < 0)
		जाओ err_unconnect;

	mutex_unlock(&c->mutex);

	वापस 0;

err_unconnect:
	c->connected = false;
	mutex_unlock(&c->mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL(cmp_connection_update);

अटल __be32 pcr_अवरोध_modअगरy(काष्ठा cmp_connection *c, __be32 pcr)
अणु
	वापस pcr & ~cpu_to_be32(PCR_BCAST_CONN | PCR_P2P_CONN_MASK);
पूर्ण

/**
 * cmp_connection_अवरोध - अवरोध the connection to the target
 * @c: the connection manager
 *
 * This function deactives the connection in the target's input/output plug
 * control रेजिस्टर, and मुक्तs the isochronous resources of the connection.
 * Beक्रमe calling this function, the caller should cease transmitting packets.
 */
व्योम cmp_connection_अवरोध(काष्ठा cmp_connection *c)
अणु
	पूर्णांक err;

	mutex_lock(&c->mutex);

	अगर (!c->connected) अणु
		mutex_unlock(&c->mutex);
		वापस;
	पूर्ण

	err = pcr_modअगरy(c, pcr_अवरोध_modअगरy, शून्य, SUCCEED_ON_BUS_RESET);
	अगर (err < 0)
		cmp_error(c, "plug is still connected\n");

	c->connected = false;

	mutex_unlock(&c->mutex);
पूर्ण
EXPORT_SYMBOL(cmp_connection_अवरोध);
