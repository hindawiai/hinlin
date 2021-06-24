<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SMI PCIe driver क्रम DVBSky cards.
 *
 * Copyright (C) 2014 Max nibble <nibble.max@gmail.com>
 */

#समावेश "smipcie.h"

#घोषणा SMI_SAMPLE_PERIOD 83
#घोषणा SMI_SAMPLE_IDLEMIN (10000 / SMI_SAMPLE_PERIOD)

अटल व्योम smi_ir_enableInterrupt(काष्ठा smi_rc *ir)
अणु
	काष्ठा smi_dev *dev = ir->dev;

	smi_ग_लिखो(MSI_INT_ENA_SET, IR_X_INT);
पूर्ण

अटल व्योम smi_ir_disableInterrupt(काष्ठा smi_rc *ir)
अणु
	काष्ठा smi_dev *dev = ir->dev;

	smi_ग_लिखो(MSI_INT_ENA_CLR, IR_X_INT);
पूर्ण

अटल व्योम smi_ir_clearInterrupt(काष्ठा smi_rc *ir)
अणु
	काष्ठा smi_dev *dev = ir->dev;

	smi_ग_लिखो(MSI_INT_STATUS_CLR, IR_X_INT);
पूर्ण

अटल व्योम smi_ir_stop(काष्ठा smi_rc *ir)
अणु
	काष्ठा smi_dev *dev = ir->dev;

	smi_ir_disableInterrupt(ir);
	smi_clear(IR_Init_Reg, rbIRen);
पूर्ण

अटल व्योम smi_raw_process(काष्ठा rc_dev *rc_dev, स्थिर u8 *buffer,
			    स्थिर u8 length)
अणु
	काष्ठा ir_raw_event rawir = अणुपूर्ण;
	पूर्णांक cnt;

	क्रम (cnt = 0; cnt < length; cnt++) अणु
		अगर (buffer[cnt] & 0x7f) अणु
			rawir.pulse = (buffer[cnt] & 0x80) == 0;
			rawir.duration = ((buffer[cnt] & 0x7f) +
					 (rawir.pulse ? 0 : -1)) *
					 rc_dev->rx_resolution;
			ir_raw_event_store_with_filter(rc_dev, &rawir);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम smi_ir_decode(काष्ठा smi_rc *ir)
अणु
	काष्ठा smi_dev *dev = ir->dev;
	काष्ठा rc_dev *rc_dev = ir->rc_dev;
	u32 control, data;
	u8 index, ir_count, पढ़ो_loop;

	control = smi_पढ़ो(IR_Init_Reg);

	dev_dbg(&rc_dev->dev, "ircontrol: 0x%08x\n", control);

	अगर (control & rbIRVld) अणु
		ir_count = (u8)smi_पढ़ो(IR_Data_Cnt);

		dev_dbg(&rc_dev->dev, "ircount %d\n", ir_count);

		पढ़ो_loop = ir_count / 4;
		अगर (ir_count % 4)
			पढ़ो_loop += 1;
		क्रम (index = 0; index < पढ़ो_loop; index++) अणु
			data = smi_पढ़ो(IR_DATA_BUFFER_BASE + (index * 4));
			dev_dbg(&rc_dev->dev, "IRData 0x%08x\n", data);

			ir->irData[index * 4 + 0] = (u8)(data);
			ir->irData[index * 4 + 1] = (u8)(data >> 8);
			ir->irData[index * 4 + 2] = (u8)(data >> 16);
			ir->irData[index * 4 + 3] = (u8)(data >> 24);
		पूर्ण
		smi_raw_process(rc_dev, ir->irData, ir_count);
	पूर्ण

	अगर (control & rbIRhighidle) अणु
		काष्ठा ir_raw_event rawir = अणुपूर्ण;

		dev_dbg(&rc_dev->dev, "high idle\n");

		rawir.pulse = 0;
		rawir.duration = SMI_SAMPLE_PERIOD * SMI_SAMPLE_IDLEMIN;
		ir_raw_event_store_with_filter(rc_dev, &rawir);
	पूर्ण

	smi_set(IR_Init_Reg, rbIRVld);
	ir_raw_event_handle(rc_dev);
पूर्ण

/* ir functions call by मुख्य driver.*/
पूर्णांक smi_ir_irq(काष्ठा smi_rc *ir, u32 पूर्णांक_status)
अणु
	पूर्णांक handled = 0;

	अगर (पूर्णांक_status & IR_X_INT) अणु
		smi_ir_disableInterrupt(ir);
		smi_ir_clearInterrupt(ir);
		smi_ir_decode(ir);
		smi_ir_enableInterrupt(ir);
		handled = 1;
	पूर्ण
	वापस handled;
पूर्ण

व्योम smi_ir_start(काष्ठा smi_rc *ir)
अणु
	काष्ठा smi_dev *dev = ir->dev;

	smi_ग_लिखो(IR_Idle_Cnt_Low,
		  (((SMI_SAMPLE_PERIOD - 1) & 0xFFFF) << 16) |
		  (SMI_SAMPLE_IDLEMIN & 0xFFFF));
	msleep(20);
	smi_set(IR_Init_Reg, rbIRen | rbIRhighidle);

	smi_ir_enableInterrupt(ir);
पूर्ण

पूर्णांक smi_ir_init(काष्ठा smi_dev *dev)
अणु
	पूर्णांक ret;
	काष्ठा rc_dev *rc_dev;
	काष्ठा smi_rc *ir = &dev->ir;

	rc_dev = rc_allocate_device(RC_DRIVER_IR_RAW);
	अगर (!rc_dev)
		वापस -ENOMEM;

	/* init input device */
	snम_लिखो(ir->device_name, माप(ir->device_name), "IR (%s)",
		 dev->info->name);
	snम_लिखो(ir->input_phys, माप(ir->input_phys), "pci-%s/ir0",
		 pci_name(dev->pci_dev));

	rc_dev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rc_dev->driver_name = "SMI_PCIe";
	rc_dev->input_phys = ir->input_phys;
	rc_dev->device_name = ir->device_name;
	rc_dev->input_id.bustype = BUS_PCI;
	rc_dev->input_id.version = 1;
	rc_dev->input_id.venकरोr = dev->pci_dev->subप्रणाली_venकरोr;
	rc_dev->input_id.product = dev->pci_dev->subप्रणाली_device;
	rc_dev->dev.parent = &dev->pci_dev->dev;

	rc_dev->map_name = dev->info->rc_map;
	rc_dev->समयout = SMI_SAMPLE_PERIOD * SMI_SAMPLE_IDLEMIN;
	rc_dev->rx_resolution = SMI_SAMPLE_PERIOD;

	ir->rc_dev = rc_dev;
	ir->dev = dev;

	smi_ir_disableInterrupt(ir);

	ret = rc_रेजिस्टर_device(rc_dev);
	अगर (ret)
		जाओ ir_err;

	वापस 0;
ir_err:
	rc_मुक्त_device(rc_dev);
	वापस ret;
पूर्ण

व्योम smi_ir_निकास(काष्ठा smi_dev *dev)
अणु
	काष्ठा smi_rc *ir = &dev->ir;
	काष्ठा rc_dev *rc_dev = ir->rc_dev;

	rc_unरेजिस्टर_device(rc_dev);
	smi_ir_stop(ir);
	ir->rc_dev = शून्य;
पूर्ण
