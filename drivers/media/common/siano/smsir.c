<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Siano Mobile Silicon, Inc.
// MDTV receiver kernel modules.
// Copyright (C) 2006-2009, Uri Shkolnik
//
// Copyright (c) 2010 - Mauro Carvalho Chehab
//	- Ported the driver to use rc-core
//	- IR raw event decoding is now करोne at rc-core
//	- Code almost re-written


#समावेश "smscoreapi.h"

#समावेश <linux/types.h>
#समावेश <linux/input.h>

#समावेश "smsir.h"
#समावेश "sms-cards.h"

#घोषणा MODULE_NAME "smsmdtv"

व्योम sms_ir_event(काष्ठा smscore_device_t *coredev, स्थिर अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक i;
	स्थिर s32 *samples = (स्थिर व्योम *)buf;

	क्रम (i = 0; i < len >> 2; i++) अणु
		काष्ठा ir_raw_event ev = अणु
			.duration = असल(samples[i]),
			.pulse = (samples[i] > 0) ? false : true
		पूर्ण;

		ir_raw_event_store(coredev->ir.dev, &ev);
	पूर्ण
	ir_raw_event_handle(coredev->ir.dev);
पूर्ण

पूर्णांक sms_ir_init(काष्ठा smscore_device_t *coredev)
अणु
	पूर्णांक err;
	पूर्णांक board_id = smscore_get_board_id(coredev);
	काष्ठा rc_dev *dev;

	pr_debug("Allocating rc device\n");
	dev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!dev)
		वापस -ENOMEM;

	coredev->ir.controller = 0;	/* Toकरो: vega/nova SPI number */
	coredev->ir.समयout = US_TO_NS(IR_DEFAULT_TIMEOUT);
	pr_debug("IR port %d, timeout %d ms\n",
			coredev->ir.controller, coredev->ir.समयout);

	snम_लिखो(coredev->ir.name, माप(coredev->ir.name),
		 "SMS IR (%s)", sms_get_board(board_id)->name);

	strscpy(coredev->ir.phys, coredev->devpath, माप(coredev->ir.phys));
	strlcat(coredev->ir.phys, "/ir0", माप(coredev->ir.phys));

	dev->device_name = coredev->ir.name;
	dev->input_phys = coredev->ir.phys;
	dev->dev.parent = coredev->device;

#अगर 0
	/* TODO: properly initialize the parameters below */
	dev->input_id.bustype = BUS_USB;
	dev->input_id.version = 1;
	dev->input_id.venकरोr = le16_to_cpu(dev->udev->descriptor.idVenकरोr);
	dev->input_id.product = le16_to_cpu(dev->udev->descriptor.idProduct);
#पूर्ण_अगर

	dev->priv = coredev;
	dev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	dev->map_name = sms_get_board(board_id)->rc_codes;
	dev->driver_name = MODULE_NAME;

	pr_debug("Input device (IR) %s is set for key events\n",
		 dev->device_name);

	err = rc_रेजिस्टर_device(dev);
	अगर (err < 0) अणु
		pr_err("Failed to register device\n");
		rc_मुक्त_device(dev);
		वापस err;
	पूर्ण

	coredev->ir.dev = dev;
	वापस 0;
पूर्ण

व्योम sms_ir_निकास(काष्ठा smscore_device_t *coredev)
अणु
	rc_unरेजिस्टर_device(coredev->ir.dev);

	pr_debug("\n");
पूर्ण
