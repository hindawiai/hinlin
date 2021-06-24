<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis PCI bridge driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <media/rc-core.h>
#समावेश <linux/pci.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mantis_common.h"
#समावेश "mantis_input.h"

#घोषणा MODULE_NAME "mantis_core"

व्योम mantis_input_process(काष्ठा mantis_pci *mantis, पूर्णांक scancode)
अणु
	अगर (mantis->rc)
		rc_keyकरोwn(mantis->rc, RC_PROTO_UNKNOWN, scancode, 0);
पूर्ण

पूर्णांक mantis_input_init(काष्ठा mantis_pci *mantis)
अणु
	काष्ठा rc_dev *dev;
	पूर्णांक err;

	dev = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!dev) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Remote device allocation failed");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	snम_लिखो(mantis->device_name, माप(mantis->device_name),
		 "Mantis %s IR receiver", mantis->hwconfig->model_name);
	snम_लिखो(mantis->input_phys, माप(mantis->input_phys),
		 "pci-%s/ir0", pci_name(mantis->pdev));

	dev->device_name        = mantis->device_name;
	dev->input_phys         = mantis->input_phys;
	dev->input_id.bustype   = BUS_PCI;
	dev->input_id.venकरोr    = mantis->venकरोr_id;
	dev->input_id.product   = mantis->device_id;
	dev->input_id.version   = 1;
	dev->driver_name        = MODULE_NAME;
	dev->map_name           = mantis->rc_map_name ? : RC_MAP_EMPTY;
	dev->dev.parent         = &mantis->pdev->dev;

	err = rc_रेजिस्टर_device(dev);
	अगर (err) अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "IR device registration failed, ret = %d", err);
		जाओ out_dev;
	पूर्ण

	mantis->rc = dev;
	वापस 0;

out_dev:
	rc_मुक्त_device(dev);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mantis_input_init);

व्योम mantis_input_निकास(काष्ठा mantis_pci *mantis)
अणु
	rc_unरेजिस्टर_device(mantis->rc);
पूर्ण
EXPORT_SYMBOL_GPL(mantis_input_निकास);
