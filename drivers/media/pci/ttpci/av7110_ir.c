<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the remote control of SAA7146 based AV7110 cards
 *
 * Copyright (C) 1999-2003 Holger Waechtler <holger@convergence.de>
 * Copyright (C) 2003-2007 Oliver Endriss <o.endriss@gmx.de>
 * Copyright (C) 2019 Sean Young <sean@mess.org>
 */

#समावेश <linux/kernel.h>
#समावेश <media/rc-core.h>

#समावेश "av7110.h"
#समावेश "av7110_hw.h"

#घोषणा IR_RC5		0
#घोषणा IR_RCMM		1
#घोषणा IR_RC5_EXT	2 /* पूर्णांकernal only */

/* पूर्णांकerrupt handler */
व्योम av7110_ir_handler(काष्ठा av7110 *av7110, u32 ircom)
अणु
	काष्ठा rc_dev *rcdev = av7110->ir.rcdev;
	क्रमागत rc_proto proto;
	u32 command, addr, scancode;
	u32 toggle;

	dprपूर्णांकk(4, "ir command = %08x\n", ircom);

	अगर (rcdev) अणु
		चयन (av7110->ir.ir_config) अणु
		हाल IR_RC5: /* RC5: 5 bits device address, 6 bits command */
			command = ircom & 0x3f;
			addr = (ircom >> 6) & 0x1f;
			scancode = RC_SCANCODE_RC5(addr, command);
			toggle = ircom & 0x0800;
			proto = RC_PROTO_RC5;
			अवरोध;

		हाल IR_RCMM: /* RCMM: 32 bits scancode */
			scancode = ircom & ~0x8000;
			toggle = ircom & 0x8000;
			proto = RC_PROTO_RCMM32;
			अवरोध;

		हाल IR_RC5_EXT:
			/*
			 * extended RC5: 5 bits device address, 7 bits command
			 *
			 * Extended RC5 uses only one start bit. The second
			 * start bit is re-asचिन्हित bit 6 of the command bit.
			 */
			command = ircom & 0x3f;
			addr = (ircom >> 6) & 0x1f;
			अगर (!(ircom & 0x1000))
				command |= 0x40;
			scancode = RC_SCANCODE_RC5(addr, command);
			toggle = ircom & 0x0800;
			proto = RC_PROTO_RC5;
			अवरोध;
		शेष:
			dprपूर्णांकk(2, "unknown ir config %d\n",
				av7110->ir.ir_config);
			वापस;
		पूर्ण

		rc_keyकरोwn(rcdev, proto, scancode, toggle != 0);
	पूर्ण
पूर्ण

पूर्णांक av7110_set_ir_config(काष्ठा av7110 *av7110)
अणु
	dprपूर्णांकk(4, "ir config = %08x\n", av7110->ir.ir_config);

	वापस av7110_fw_cmd(av7110, COMTYPE_PIDFILTER, SetIR, 1,
			     av7110->ir.ir_config);
पूर्ण

अटल पूर्णांक change_protocol(काष्ठा rc_dev *rcdev, u64 *rc_type)
अणु
	काष्ठा av7110 *av7110 = rcdev->priv;
	u32 ir_config;

	अगर (*rc_type & RC_PROTO_BIT_RCMM32) अणु
		ir_config = IR_RCMM;
		*rc_type = RC_PROTO_BIT_RCMM32;
	पूर्ण अन्यथा अगर (*rc_type & RC_PROTO_BIT_RC5) अणु
		अगर (FW_VERSION(av7110->arm_app) >= 0x2620)
			ir_config = IR_RC5_EXT;
		अन्यथा
			ir_config = IR_RC5;
		*rc_type = RC_PROTO_BIT_RC5;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (ir_config == av7110->ir.ir_config)
		वापस 0;

	av7110->ir.ir_config = ir_config;

	वापस av7110_set_ir_config(av7110);
पूर्ण

पूर्णांक av7110_ir_init(काष्ठा av7110 *av7110)
अणु
	काष्ठा rc_dev *rcdev;
	काष्ठा pci_dev *pci;
	पूर्णांक ret;

	rcdev = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!rcdev)
		वापस -ENOMEM;

	pci = av7110->dev->pci;

	snम_लिखो(av7110->ir.input_phys, माप(av7110->ir.input_phys),
		 "pci-%s/ir0", pci_name(pci));

	rcdev->device_name = av7110->card_name;
	rcdev->driver_name = KBUILD_MODNAME;
	rcdev->input_phys = av7110->ir.input_phys;
	rcdev->input_id.bustype = BUS_PCI;
	rcdev->input_id.version = 2;
	अगर (pci->subप्रणाली_venकरोr) अणु
		rcdev->input_id.venकरोr	= pci->subप्रणाली_venकरोr;
		rcdev->input_id.product = pci->subप्रणाली_device;
	पूर्ण अन्यथा अणु
		rcdev->input_id.venकरोr	= pci->venकरोr;
		rcdev->input_id.product = pci->device;
	पूर्ण

	rcdev->dev.parent = &pci->dev;
	rcdev->allowed_protocols = RC_PROTO_BIT_RC5 | RC_PROTO_BIT_RCMM32;
	rcdev->change_protocol = change_protocol;
	rcdev->map_name = RC_MAP_HAUPPAUGE;
	rcdev->priv = av7110;

	av7110->ir.rcdev = rcdev;
	av7110->ir.ir_config = IR_RC5;
	av7110_set_ir_config(av7110);

	ret = rc_रेजिस्टर_device(rcdev);
	अगर (ret) अणु
		av7110->ir.rcdev = शून्य;
		rc_मुक्त_device(rcdev);
	पूर्ण

	वापस ret;
पूर्ण

व्योम av7110_ir_निकास(काष्ठा av7110 *av7110)
अणु
	rc_unरेजिस्टर_device(av7110->ir.rcdev);
पूर्ण

//MODULE_AUTHOR("Holger Waechtler <holger@convergence.de>, Oliver Endriss <o.endriss@gmx.de>");
//MODULE_LICENSE("GPL");
