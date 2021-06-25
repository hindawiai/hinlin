<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885/7/8 PCIe bridge
 *
 *  Infrared remote control input device
 *
 *  Most of this file is
 *
 *  Copyright (C) 2009  Andy Walls <awalls@md.metrocast.net>
 *
 *  However, the cx23885_input_अणुinit,finiपूर्ण functions contained herein are
 *  derived from Linux kernel files linux/media/video/.../...-input.c marked as:
 *
 *  Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>
 *  Copyright (C) 2005 Luकरोvico Caveकरोn <caveकरोn@sssup.it>
 *		       Markus Rechberger <mrechberger@gmail.com>
 *		       Mauro Carvalho Chehab <mchehab@kernel.org>
 *		       Sascha Sommer <saschasommer@मुक्तnet.de>
 *  Copyright (C) 2004, 2005 Chris Pascoe
 *  Copyright (C) 2003, 2004 Gerd Knorr
 *  Copyright (C) 2003 Pavel Machek
 */

#समावेश "cx23885.h"
#समावेश "cx23885-input.h"

#समावेश <linux/slab.h>
#समावेश <media/rc-core.h>
#समावेश <media/v4l2-subdev.h>

#घोषणा MODULE_NAME "cx23885"

अटल व्योम cx23885_input_process_measurements(काष्ठा cx23885_dev *dev,
					       bool overrun)
अणु
	काष्ठा cx23885_kernel_ir *kernel_ir = dev->kernel_ir;

	sमाप_प्रकार num;
	पूर्णांक count, i;
	bool handle = false;
	काष्ठा ir_raw_event ir_core_event[64];

	करो अणु
		num = 0;
		v4l2_subdev_call(dev->sd_ir, ir, rx_पढ़ो, (u8 *) ir_core_event,
				 माप(ir_core_event), &num);

		count = num / माप(काष्ठा ir_raw_event);

		क्रम (i = 0; i < count; i++) अणु
			ir_raw_event_store(kernel_ir->rc,
					   &ir_core_event[i]);
			handle = true;
		पूर्ण
	पूर्ण जबतक (num != 0);

	अगर (overrun)
		ir_raw_event_reset(kernel_ir->rc);
	अन्यथा अगर (handle)
		ir_raw_event_handle(kernel_ir->rc);
पूर्ण

व्योम cx23885_input_rx_work_handler(काष्ठा cx23885_dev *dev, u32 events)
अणु
	काष्ठा v4l2_subdev_ir_parameters params;
	पूर्णांक overrun, data_available;

	अगर (dev->sd_ir == शून्य || events == 0)
		वापस;

	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
	हाल CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
	हाल CX23885_BOARD_TEVII_S470:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
	हाल CX23885_BOARD_MYGICA_X8507:
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_DVBSKY_S950C:
	हाल CX23885_BOARD_TT_CT2_4500_CI:
	हाल CX23885_BOARD_DVBSKY_S950:
	हाल CX23885_BOARD_DVBSKY_S952:
	हाल CX23885_BOARD_DVBSKY_T982:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
		/*
		 * The only boards we handle right now.  However other boards
		 * using the CX2388x पूर्णांकegrated IR controller should be similar
		 */
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	overrun = events & (V4L2_SUBDEV_IR_RX_SW_FIFO_OVERRUN |
			    V4L2_SUBDEV_IR_RX_HW_FIFO_OVERRUN);

	data_available = events & (V4L2_SUBDEV_IR_RX_END_OF_RX_DETECTED |
				   V4L2_SUBDEV_IR_RX_FIFO_SERVICE_REQ);

	अगर (overrun) अणु
		/* If there was a FIFO overrun, stop the device */
		v4l2_subdev_call(dev->sd_ir, ir, rx_g_parameters, &params);
		params.enable = false;
		/* Mitigate race with cx23885_input_ir_stop() */
		params.shutकरोwn = atomic_पढ़ो(&dev->ir_input_stopping);
		v4l2_subdev_call(dev->sd_ir, ir, rx_s_parameters, &params);
	पूर्ण

	अगर (data_available)
		cx23885_input_process_measurements(dev, overrun);

	अगर (overrun) अणु
		/* If there was a FIFO overrun, clear & restart the device */
		params.enable = true;
		/* Mitigate race with cx23885_input_ir_stop() */
		params.shutकरोwn = atomic_पढ़ो(&dev->ir_input_stopping);
		v4l2_subdev_call(dev->sd_ir, ir, rx_s_parameters, &params);
	पूर्ण
पूर्ण

अटल पूर्णांक cx23885_input_ir_start(काष्ठा cx23885_dev *dev)
अणु
	काष्ठा v4l2_subdev_ir_parameters params;

	अगर (dev->sd_ir == शून्य)
		वापस -ENODEV;

	atomic_set(&dev->ir_input_stopping, 0);

	v4l2_subdev_call(dev->sd_ir, ir, rx_g_parameters, &params);
	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
	हाल CX23885_BOARD_MYGICA_X8507:
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_DVBSKY_S950C:
	हाल CX23885_BOARD_TT_CT2_4500_CI:
	हाल CX23885_BOARD_DVBSKY_S950:
	हाल CX23885_BOARD_DVBSKY_S952:
	हाल CX23885_BOARD_DVBSKY_T982:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
		/*
		 * The IR controller on this board only वापसs pulse widths.
		 * Any other mode setting will fail to set up the device.
		*/
		params.mode = V4L2_SUBDEV_IR_MODE_PULSE_WIDTH;
		params.enable = true;
		params.पूर्णांकerrupt_enable = true;
		params.shutकरोwn = false;

		/* Setup क्रम baseband compatible with both RC-5 and RC-6A */
		params.modulation = false;
		/* RC-5:  2,222,222 ns = 1/36 kHz * 32 cycles * 2 marks * 1.25*/
		/* RC-6A: 3,333,333 ns = 1/36 kHz * 16 cycles * 6 marks * 1.25*/
		params.max_pulse_width = 3333333; /* ns */
		/* RC-5:    666,667 ns = 1/36 kHz * 32 cycles * 1 mark * 0.75 */
		/* RC-6A:   333,333 ns = 1/36 kHz * 16 cycles * 1 mark * 0.75 */
		params.noise_filter_min_width = 333333; /* ns */
		/*
		 * This board has inverted receive sense:
		 * mark is received as low logic level;
		 * falling edges are detected as rising edges; etc.
		 */
		params.invert_level = true;
		अवरोध;
	हाल CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
	हाल CX23885_BOARD_TEVII_S470:
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
		/*
		 * The IR controller on this board only वापसs pulse widths.
		 * Any other mode setting will fail to set up the device.
		 */
		params.mode = V4L2_SUBDEV_IR_MODE_PULSE_WIDTH;
		params.enable = true;
		params.पूर्णांकerrupt_enable = true;
		params.shutकरोwn = false;

		/* Setup क्रम a standard NEC protocol */
		params.carrier_freq = 37917; /* Hz, 455 kHz/12 क्रम NEC */
		params.carrier_range_lower = 33000; /* Hz */
		params.carrier_range_upper = 43000; /* Hz */
		params.duty_cycle = 33; /* percent, 33 percent क्रम NEC */

		/*
		 * NEC max pulse width: (64/3)/(455 kHz/12) * 16 nec_units
		 * (64/3)/(455 kHz/12) * 16 nec_units * 1.375 = 12378022 ns
		 */
		params.max_pulse_width = 12378022; /* ns */

		/*
		 * NEC noise filter min width: (64/3)/(455 kHz/12) * 1 nec_unit
		 * (64/3)/(455 kHz/12) * 1 nec_units * 0.625 = 351648 ns
		 */
		params.noise_filter_min_width = 351648; /* ns */

		params.modulation = false;
		params.invert_level = true;
		अवरोध;
	पूर्ण
	v4l2_subdev_call(dev->sd_ir, ir, rx_s_parameters, &params);
	वापस 0;
पूर्ण

अटल पूर्णांक cx23885_input_ir_खोलो(काष्ठा rc_dev *rc)
अणु
	काष्ठा cx23885_kernel_ir *kernel_ir = rc->priv;

	अगर (kernel_ir->cx == शून्य)
		वापस -ENODEV;

	वापस cx23885_input_ir_start(kernel_ir->cx);
पूर्ण

अटल व्योम cx23885_input_ir_stop(काष्ठा cx23885_dev *dev)
अणु
	काष्ठा v4l2_subdev_ir_parameters params;

	अगर (dev->sd_ir == शून्य)
		वापस;

	/*
	 * Stop the sd_ir subdevice from generating notअगरications and
	 * scheduling work.
	 * It is shutकरोwn this way in order to mitigate a race with
	 * cx23885_input_rx_work_handler() in the overrun हाल, which could
	 * re-enable the subdevice.
	 */
	atomic_set(&dev->ir_input_stopping, 1);
	v4l2_subdev_call(dev->sd_ir, ir, rx_g_parameters, &params);
	जबतक (params.shutकरोwn == false) अणु
		params.enable = false;
		params.पूर्णांकerrupt_enable = false;
		params.shutकरोwn = true;
		v4l2_subdev_call(dev->sd_ir, ir, rx_s_parameters, &params);
		v4l2_subdev_call(dev->sd_ir, ir, rx_g_parameters, &params);
	पूर्ण
	flush_work(&dev->cx25840_work);
	flush_work(&dev->ir_rx_work);
	flush_work(&dev->ir_tx_work);
पूर्ण

अटल व्योम cx23885_input_ir_बंद(काष्ठा rc_dev *rc)
अणु
	काष्ठा cx23885_kernel_ir *kernel_ir = rc->priv;

	अगर (kernel_ir->cx != शून्य)
		cx23885_input_ir_stop(kernel_ir->cx);
पूर्ण

पूर्णांक cx23885_input_init(काष्ठा cx23885_dev *dev)
अणु
	काष्ठा cx23885_kernel_ir *kernel_ir;
	काष्ठा rc_dev *rc;
	अक्षर *rc_map;
	u64 allowed_protos;

	पूर्णांक ret;

	/*
	 * If the IR device (hardware रेजिस्टरs, chip, GPIO lines, etc.) isn't
	 * encapsulated in a v4l2_subdev, then I'm not going to deal with it.
	 */
	अगर (dev->sd_ir == शून्य)
		वापस -ENODEV;

	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
		/* Integrated CX2388[58] IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		/* The grey Hauppauge RC-5 remote */
		rc_map = RC_MAP_HAUPPAUGE;
		अवरोध;
	हाल CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		/* The grey Terratec remote with orange buttons */
		rc_map = RC_MAP_NEC_TERRATEC_CINERGY_XS;
		अवरोध;
	हाल CX23885_BOARD_TEVII_S470:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		/* A guess at the remote */
		rc_map = RC_MAP_TEVII_NEC;
		अवरोध;
	हाल CX23885_BOARD_MYGICA_X8507:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		/* A guess at the remote */
		rc_map = RC_MAP_TOTAL_MEDIA_IN_HAND_02;
		अवरोध;
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		/* A guess at the remote */
		rc_map = RC_MAP_TBS_NEC;
		अवरोध;
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_DVBSKY_S950C:
	हाल CX23885_BOARD_DVBSKY_S950:
	हाल CX23885_BOARD_DVBSKY_S952:
	हाल CX23885_BOARD_DVBSKY_T982:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		rc_map = RC_MAP_DVBSKY;
		अवरोध;
	हाल CX23885_BOARD_TT_CT2_4500_CI:
		/* Integrated CX23885 IR controller */
		allowed_protos = RC_PROTO_BIT_ALL_IR_DECODER;
		rc_map = RC_MAP_TT_1500;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	/* cx23885 board instance kernel IR state */
	kernel_ir = kzalloc(माप(काष्ठा cx23885_kernel_ir), GFP_KERNEL);
	अगर (kernel_ir == शून्य)
		वापस -ENOMEM;

	kernel_ir->cx = dev;
	kernel_ir->name = kaप्र_लिखो(GFP_KERNEL, "cx23885 IR (%s)",
				    cx23885_boards[dev->board].name);
	अगर (!kernel_ir->name) अणु
		ret = -ENOMEM;
		जाओ err_out_मुक्त;
	पूर्ण

	kernel_ir->phys = kaप्र_लिखो(GFP_KERNEL, "pci-%s/ir0",
				    pci_name(dev->pci));
	अगर (!kernel_ir->phys) अणु
		ret = -ENOMEM;
		जाओ err_out_मुक्त_name;
	पूर्ण

	/* input device */
	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rc) अणु
		ret = -ENOMEM;
		जाओ err_out_मुक्त_phys;
	पूर्ण

	kernel_ir->rc = rc;
	rc->device_name = kernel_ir->name;
	rc->input_phys = kernel_ir->phys;
	rc->input_id.bustype = BUS_PCI;
	rc->input_id.version = 1;
	अगर (dev->pci->subप्रणाली_venकरोr) अणु
		rc->input_id.venकरोr  = dev->pci->subप्रणाली_venकरोr;
		rc->input_id.product = dev->pci->subप्रणाली_device;
	पूर्ण अन्यथा अणु
		rc->input_id.venकरोr  = dev->pci->venकरोr;
		rc->input_id.product = dev->pci->device;
	पूर्ण
	rc->dev.parent = &dev->pci->dev;
	rc->allowed_protocols = allowed_protos;
	rc->priv = kernel_ir;
	rc->खोलो = cx23885_input_ir_खोलो;
	rc->बंद = cx23885_input_ir_बंद;
	rc->map_name = rc_map;
	rc->driver_name = MODULE_NAME;

	/* Go */
	dev->kernel_ir = kernel_ir;
	ret = rc_रेजिस्टर_device(rc);
	अगर (ret)
		जाओ err_out_stop;

	वापस 0;

err_out_stop:
	cx23885_input_ir_stop(dev);
	dev->kernel_ir = शून्य;
	rc_मुक्त_device(rc);
err_out_मुक्त_phys:
	kमुक्त(kernel_ir->phys);
err_out_मुक्त_name:
	kमुक्त(kernel_ir->name);
err_out_मुक्त:
	kमुक्त(kernel_ir);
	वापस ret;
पूर्ण

व्योम cx23885_input_fini(काष्ठा cx23885_dev *dev)
अणु
	/* Always stop the IR hardware from generating पूर्णांकerrupts */
	cx23885_input_ir_stop(dev);

	अगर (dev->kernel_ir == शून्य)
		वापस;
	rc_unरेजिस्टर_device(dev->kernel_ir->rc);
	kमुक्त(dev->kernel_ir->phys);
	kमुक्त(dev->kernel_ir->name);
	kमुक्त(dev->kernel_ir);
	dev->kernel_ir = शून्य;
पूर्ण
