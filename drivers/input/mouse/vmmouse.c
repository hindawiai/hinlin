<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Virtual PS/2 Mouse on VMware and QEMU hypervisors.
 *
 * Copyright (C) 2014, VMware, Inc. All Rights Reserved.
 *
 * Twin device code is hugely inspired by the ALPS driver.
 * Authors:
 *   Dmitry Torokhov <dmitry.torokhov@gmail.com>
 *   Thomas Hellstrom <thellstrom@vmware.com>
 */

#समावेश <linux/input.h>
#समावेश <linux/serपन.स>
#समावेश <linux/libps2.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/vmware.h>

#समावेश "psmouse.h"
#समावेश "vmmouse.h"

#घोषणा VMMOUSE_PROTO_MAGIC			0x564D5868U

/*
 * Main commands supported by the vmmouse hypervisor port.
 */
#घोषणा VMMOUSE_PROTO_CMD_GETVERSION		10
#घोषणा VMMOUSE_PROTO_CMD_ABSPOINTER_DATA	39
#घोषणा VMMOUSE_PROTO_CMD_ABSPOINTER_STATUS	40
#घोषणा VMMOUSE_PROTO_CMD_ABSPOINTER_COMMAND	41
#घोषणा VMMOUSE_PROTO_CMD_ABSPOINTER_RESTRICT   86

/*
 * Subcommands क्रम VMMOUSE_PROTO_CMD_ABSPOINTER_COMMAND
 */
#घोषणा VMMOUSE_CMD_ENABLE			0x45414552U
#घोषणा VMMOUSE_CMD_DISABLE			0x000000f5U
#घोषणा VMMOUSE_CMD_REQUEST_RELATIVE		0x4c455252U
#घोषणा VMMOUSE_CMD_REQUEST_ABSOLUTE		0x53424152U

#घोषणा VMMOUSE_ERROR				0xffff0000U

#घोषणा VMMOUSE_VERSION_ID			0x3442554aU

#घोषणा VMMOUSE_RELATIVE_PACKET			0x00010000U

#घोषणा VMMOUSE_LEFT_BUTTON			0x20
#घोषणा VMMOUSE_RIGHT_BUTTON			0x10
#घोषणा VMMOUSE_MIDDLE_BUTTON			0x08

/*
 * VMMouse Restrict command
 */
#घोषणा VMMOUSE_RESTRICT_ANY                    0x00
#घोषणा VMMOUSE_RESTRICT_CPL0                   0x01
#घोषणा VMMOUSE_RESTRICT_IOPL                   0x02

#घोषणा VMMOUSE_MAX_X                           0xFFFF
#घोषणा VMMOUSE_MAX_Y                           0xFFFF

#घोषणा VMMOUSE_VENDOR "VMware"
#घोषणा VMMOUSE_NAME   "VMMouse"

/**
 * काष्ठा vmmouse_data - निजी data काष्ठाure क्रम the vmmouse driver
 *
 * @असल_dev: "Absolute" device used to report असलolute mouse movement.
 * @phys: Physical path क्रम the असलolute device.
 * @dev_name: Name attribute name क्रम the असलolute device.
 */
काष्ठा vmmouse_data अणु
	काष्ठा input_dev *असल_dev;
	अक्षर phys[32];
	अक्षर dev_name[128];
पूर्ण;

/*
 * Hypervisor-specअगरic bi-directional communication channel
 * implementing the vmmouse protocol. Should never execute on
 * bare metal hardware.
 */
#घोषणा VMMOUSE_CMD(cmd, in1, out1, out2, out3, out4)	\
(अणु							\
	अचिन्हित दीर्घ __dummy1, __dummy2;		\
	__यंत्र__ __अस्थिर__ (VMWARE_HYPERCALL :	\
		"=a"(out1),				\
		"=b"(out2),				\
		"=c"(out3),				\
		"=d"(out4),				\
		"=S"(__dummy1),				\
		"=D"(__dummy2) :			\
		"a"(VMMOUSE_PROTO_MAGIC),		\
		"b"(in1),				\
		"c"(VMMOUSE_PROTO_CMD_##cmd),		\
		"d"(0) :			        \
		"memory");		                \
पूर्ण)

/**
 * vmmouse_report_button - report button state on the correct input device
 *
 * @psmouse:  Poपूर्णांकer to the psmouse काष्ठा
 * @असल_dev:  The असलolute input device
 * @rel_dev:  The relative input device
 * @pref_dev: The preferred device क्रम reporting
 * @code:     Button code
 * @value:    Button value
 *
 * Report @value and @code on @pref_dev, unless the button is alपढ़ोy
 * pressed on the other device, in which हाल the state is reported on that
 * device.
 */
अटल व्योम vmmouse_report_button(काष्ठा psmouse *psmouse,
				  काष्ठा input_dev *असल_dev,
				  काष्ठा input_dev *rel_dev,
				  काष्ठा input_dev *pref_dev,
				  अचिन्हित पूर्णांक code, पूर्णांक value)
अणु
	अगर (test_bit(code, असल_dev->key))
		pref_dev = असल_dev;
	अन्यथा अगर (test_bit(code, rel_dev->key))
		pref_dev = rel_dev;

	input_report_key(pref_dev, code, value);
पूर्ण

/**
 * vmmouse_report_events - process events on the vmmouse communications channel
 *
 * @psmouse: Poपूर्णांकer to the psmouse काष्ठा
 *
 * This function pulls events from the vmmouse communications channel and
 * reports them on the correct (असलolute or relative) input device. When the
 * communications channel is drained, or अगर we've processed more than 255
 * psmouse commands, the function वापसs PSMOUSE_FULL_PACKET. If there is a
 * host- or synchronization error, the function वापसs PSMOUSE_BAD_DATA in
 * the hope that the caller will reset the communications channel.
 */
अटल psmouse_ret_t vmmouse_report_events(काष्ठा psmouse *psmouse)
अणु
	काष्ठा input_dev *rel_dev = psmouse->dev;
	काष्ठा vmmouse_data *priv = psmouse->निजी;
	काष्ठा input_dev *असल_dev = priv->असल_dev;
	काष्ठा input_dev *pref_dev;
	u32 status, x, y, z;
	u32 dummy1, dummy2, dummy3;
	अचिन्हित पूर्णांक queue_length;
	अचिन्हित पूर्णांक count = 255;

	जबतक (count--) अणु
		/* See अगर we have motion data. */
		VMMOUSE_CMD(ABSPOINTER_STATUS, 0,
			    status, dummy1, dummy2, dummy3);
		अगर ((status & VMMOUSE_ERROR) == VMMOUSE_ERROR) अणु
			psmouse_err(psmouse, "failed to fetch status data\n");
			/*
			 * After a few attempts this will result in
			 * reconnect.
			 */
			वापस PSMOUSE_BAD_DATA;
		पूर्ण

		queue_length = status & 0xffff;
		अगर (queue_length == 0)
			अवरोध;

		अगर (queue_length % 4) अणु
			psmouse_err(psmouse, "invalid queue length\n");
			वापस PSMOUSE_BAD_DATA;
		पूर्ण

		/* Now get it */
		VMMOUSE_CMD(ABSPOINTER_DATA, 4, status, x, y, z);

		/*
		 * And report what we've got. Prefer to report button
		 * events on the same device where we report motion events.
		 * This करोesn't work well with the mouse wheel, though. See
		 * below. Ideally we would want to report that on the
		 * preferred device as well.
		 */
		अगर (status & VMMOUSE_RELATIVE_PACKET) अणु
			pref_dev = rel_dev;
			input_report_rel(rel_dev, REL_X, (s32)x);
			input_report_rel(rel_dev, REL_Y, -(s32)y);
		पूर्ण अन्यथा अणु
			pref_dev = असल_dev;
			input_report_असल(असल_dev, ABS_X, x);
			input_report_असल(असल_dev, ABS_Y, y);
		पूर्ण

		/* Xorg seems to ignore wheel events on असलolute devices */
		input_report_rel(rel_dev, REL_WHEEL, -(s8)((u8) z));

		vmmouse_report_button(psmouse, असल_dev, rel_dev,
				      pref_dev, BTN_LEFT,
				      status & VMMOUSE_LEFT_BUTTON);
		vmmouse_report_button(psmouse, असल_dev, rel_dev,
				      pref_dev, BTN_RIGHT,
				      status & VMMOUSE_RIGHT_BUTTON);
		vmmouse_report_button(psmouse, असल_dev, rel_dev,
				      pref_dev, BTN_MIDDLE,
				      status & VMMOUSE_MIDDLE_BUTTON);
		input_sync(असल_dev);
		input_sync(rel_dev);
	पूर्ण

	वापस PSMOUSE_FULL_PACKET;
पूर्ण

/**
 * vmmouse_process_byte - process data on the ps/2 channel
 *
 * @psmouse: Poपूर्णांकer to the psmouse काष्ठा
 *
 * When the ps/2 channel indicates that there is vmmouse data available,
 * call vmmouse channel processing. Otherwise, जारी to accept bytes. If
 * there is a synchronization or communication data error, वापस
 * PSMOUSE_BAD_DATA in the hope that the caller will reset the mouse.
 */
अटल psmouse_ret_t vmmouse_process_byte(काष्ठा psmouse *psmouse)
अणु
	अचिन्हित अक्षर *packet = psmouse->packet;

	चयन (psmouse->pktcnt) अणु
	हाल 1:
		वापस (packet[0] & 0x8) == 0x8 ?
			PSMOUSE_GOOD_DATA : PSMOUSE_BAD_DATA;

	हाल 2:
		वापस PSMOUSE_GOOD_DATA;

	शेष:
		वापस vmmouse_report_events(psmouse);
	पूर्ण
पूर्ण

/**
 * vmmouse_disable - Disable vmmouse
 *
 * @psmouse: Poपूर्णांकer to the psmouse काष्ठा
 *
 * Tries to disable vmmouse mode.
 */
अटल व्योम vmmouse_disable(काष्ठा psmouse *psmouse)
अणु
	u32 status;
	u32 dummy1, dummy2, dummy3, dummy4;

	VMMOUSE_CMD(ABSPOINTER_COMMAND, VMMOUSE_CMD_DISABLE,
		    dummy1, dummy2, dummy3, dummy4);

	VMMOUSE_CMD(ABSPOINTER_STATUS, 0,
		    status, dummy1, dummy2, dummy3);

	अगर ((status & VMMOUSE_ERROR) != VMMOUSE_ERROR)
		psmouse_warn(psmouse, "failed to disable vmmouse device\n");
पूर्ण

/**
 * vmmouse_enable - Enable vmmouse and request असलolute mode.
 *
 * @psmouse: Poपूर्णांकer to the psmouse काष्ठा
 *
 * Tries to enable vmmouse mode. Perक्रमms basic checks and requests
 * असलolute vmmouse mode.
 * Returns 0 on success, -ENODEV on failure.
 */
अटल पूर्णांक vmmouse_enable(काष्ठा psmouse *psmouse)
अणु
	u32 status, version;
	u32 dummy1, dummy2, dummy3, dummy4;

	/*
	 * Try enabling the device. If successful, we should be able to
	 * पढ़ो valid version ID back from it.
	 */
	VMMOUSE_CMD(ABSPOINTER_COMMAND, VMMOUSE_CMD_ENABLE,
		    dummy1, dummy2, dummy3, dummy4);

	/*
	 * See अगर version ID can be retrieved.
	 */
	VMMOUSE_CMD(ABSPOINTER_STATUS, 0, status, dummy1, dummy2, dummy3);
	अगर ((status & 0x0000ffff) == 0) अणु
		psmouse_dbg(psmouse, "empty flags - assuming no device\n");
		वापस -ENXIO;
	पूर्ण

	VMMOUSE_CMD(ABSPOINTER_DATA, 1 /* single item */,
		    version, dummy1, dummy2, dummy3);
	अगर (version != VMMOUSE_VERSION_ID) अणु
		psmouse_dbg(psmouse, "Unexpected version value: %u vs %u\n",
			    (अचिन्हित) version, VMMOUSE_VERSION_ID);
		vmmouse_disable(psmouse);
		वापस -ENXIO;
	पूर्ण

	/*
	 * Restrict ioport access, अगर possible.
	 */
	VMMOUSE_CMD(ABSPOINTER_RESTRICT, VMMOUSE_RESTRICT_CPL0,
		    dummy1, dummy2, dummy3, dummy4);

	VMMOUSE_CMD(ABSPOINTER_COMMAND, VMMOUSE_CMD_REQUEST_ABSOLUTE,
		    dummy1, dummy2, dummy3, dummy4);

	वापस 0;
पूर्ण

/*
 * Array of supported hypervisors.
 */
अटल क्रमागत x86_hypervisor_type vmmouse_supported_hypervisors[] = अणु
	X86_HYPER_VMWARE,
	X86_HYPER_KVM,
पूर्ण;

/**
 * vmmouse_check_hypervisor - Check अगर we're running on a supported hypervisor
 */
अटल bool vmmouse_check_hypervisor(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vmmouse_supported_hypervisors); i++)
		अगर (vmmouse_supported_hypervisors[i] == x86_hyper_type)
			वापस true;

	वापस false;
पूर्ण

/**
 * vmmouse_detect - Probe whether vmmouse is available
 *
 * @psmouse: Poपूर्णांकer to the psmouse काष्ठा
 * @set_properties: Whether to set psmouse name and venकरोr
 *
 * Returns 0 अगर vmmouse channel is available. Negative error code अगर not.
 */
पूर्णांक vmmouse_detect(काष्ठा psmouse *psmouse, bool set_properties)
अणु
	u32 response, version, dummy1, dummy2;

	अगर (!vmmouse_check_hypervisor()) अणु
		psmouse_dbg(psmouse,
			    "VMMouse not running on supported hypervisor.\n");
		वापस -ENXIO;
	पूर्ण

	/* Check अगर the device is present */
	response = ~VMMOUSE_PROTO_MAGIC;
	VMMOUSE_CMD(GETVERSION, 0, version, response, dummy1, dummy2);
	अगर (response != VMMOUSE_PROTO_MAGIC || version == 0xffffffffU)
		वापस -ENXIO;

	अगर (set_properties) अणु
		psmouse->venकरोr = VMMOUSE_VENDOR;
		psmouse->name = VMMOUSE_NAME;
		psmouse->model = version;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmmouse_disconnect - Take करोwn vmmouse driver
 *
 * @psmouse: Poपूर्णांकer to the psmouse काष्ठा
 *
 * Takes करोwn vmmouse driver and मुक्तs resources set up in vmmouse_init().
 */
अटल व्योम vmmouse_disconnect(काष्ठा psmouse *psmouse)
अणु
	काष्ठा vmmouse_data *priv = psmouse->निजी;

	vmmouse_disable(psmouse);
	psmouse_reset(psmouse);
	input_unरेजिस्टर_device(priv->असल_dev);
	kमुक्त(priv);
पूर्ण

/**
 * vmmouse_reconnect - Reset the ps/2 - and vmmouse connections
 *
 * @psmouse: Poपूर्णांकer to the psmouse काष्ठा
 *
 * Attempts to reset the mouse connections. Returns 0 on success and
 * -1 on failure.
 */
अटल पूर्णांक vmmouse_reconnect(काष्ठा psmouse *psmouse)
अणु
	पूर्णांक error;

	psmouse_reset(psmouse);
	vmmouse_disable(psmouse);
	error = vmmouse_enable(psmouse);
	अगर (error) अणु
		psmouse_err(psmouse,
			    "Unable to re-enable mouse when reconnecting, err: %d\n",
			    error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmmouse_init - Initialize the vmmouse driver
 *
 * @psmouse: Poपूर्णांकer to the psmouse काष्ठा
 *
 * Requests the device and tries to enable vmmouse mode.
 * If successful, sets up the input device क्रम relative movement events.
 * It also allocates another input device and sets it up क्रम असलolute motion
 * events. Returns 0 on success and -1 on failure.
 */
पूर्णांक vmmouse_init(काष्ठा psmouse *psmouse)
अणु
	काष्ठा vmmouse_data *priv;
	काष्ठा input_dev *rel_dev = psmouse->dev, *असल_dev;
	पूर्णांक error;

	psmouse_reset(psmouse);
	error = vmmouse_enable(psmouse);
	अगर (error)
		वापस error;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	असल_dev = input_allocate_device();
	अगर (!priv || !असल_dev) अणु
		error = -ENOMEM;
		जाओ init_fail;
	पूर्ण

	priv->असल_dev = असल_dev;
	psmouse->निजी = priv;

	/* Set up and रेजिस्टर असलolute device */
	snम_लिखो(priv->phys, माप(priv->phys), "%s/input1",
		 psmouse->ps2dev.serio->phys);

	/* Mimic name setup क्रम relative device in psmouse-base.c */
	snम_लिखो(priv->dev_name, माप(priv->dev_name), "%s %s %s",
		 VMMOUSE_PSNAME, VMMOUSE_VENDOR, VMMOUSE_NAME);
	असल_dev->phys = priv->phys;
	असल_dev->name = priv->dev_name;
	असल_dev->id.bustype = BUS_I8042;
	असल_dev->id.venकरोr = 0x0002;
	असल_dev->id.product = PSMOUSE_VMMOUSE;
	असल_dev->id.version = psmouse->model;
	असल_dev->dev.parent = &psmouse->ps2dev.serio->dev;

	/* Set असलolute device capabilities */
	input_set_capability(असल_dev, EV_KEY, BTN_LEFT);
	input_set_capability(असल_dev, EV_KEY, BTN_RIGHT);
	input_set_capability(असल_dev, EV_KEY, BTN_MIDDLE);
	input_set_capability(असल_dev, EV_ABS, ABS_X);
	input_set_capability(असल_dev, EV_ABS, ABS_Y);
	input_set_असल_params(असल_dev, ABS_X, 0, VMMOUSE_MAX_X, 0, 0);
	input_set_असल_params(असल_dev, ABS_Y, 0, VMMOUSE_MAX_Y, 0, 0);

	error = input_रेजिस्टर_device(priv->असल_dev);
	अगर (error)
		जाओ init_fail;

	/* Add wheel capability to the relative device */
	input_set_capability(rel_dev, EV_REL, REL_WHEEL);

	psmouse->protocol_handler = vmmouse_process_byte;
	psmouse->disconnect = vmmouse_disconnect;
	psmouse->reconnect = vmmouse_reconnect;

	वापस 0;

init_fail:
	vmmouse_disable(psmouse);
	psmouse_reset(psmouse);
	input_मुक्त_device(असल_dev);
	kमुक्त(priv);
	psmouse->निजी = शून्य;

	वापस error;
पूर्ण
