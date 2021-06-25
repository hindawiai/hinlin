<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Raspberry Pi firmware based touchscreen driver
 *
 * Copyright (C) 2015, 2017 Raspberry Pi
 * Copyright (C) 2018 Nicolas Saenz Julienne <nsaenzjulienne@suse.de>
 */

#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <soc/bcm2835/raspberrypi-firmware.h>

#घोषणा RPI_TS_DEFAULT_WIDTH	800
#घोषणा RPI_TS_DEFAULT_HEIGHT	480

#घोषणा RPI_TS_MAX_SUPPORTED_POINTS	10

#घोषणा RPI_TS_FTS_TOUCH_DOWN		0
#घोषणा RPI_TS_FTS_TOUCH_CONTACT	2

#घोषणा RPI_TS_POLL_INTERVAL		17	/* 60fps */

#घोषणा RPI_TS_NPOINTS_REG_INVALIDATE	99

काष्ठा rpi_ts अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा input_dev *input;
	काष्ठा touchscreen_properties prop;

	व्योम __iomem *fw_regs_va;
	dma_addr_t fw_regs_phys;

	पूर्णांक known_ids;
पूर्ण;

काष्ठा rpi_ts_regs अणु
	u8 device_mode;
	u8 gesture_id;
	u8 num_poपूर्णांकs;
	काष्ठा rpi_ts_touch अणु
		u8 xh;
		u8 xl;
		u8 yh;
		u8 yl;
		u8 pressure; /* Not supported */
		u8 area;     /* Not supported */
	पूर्ण poपूर्णांक[RPI_TS_MAX_SUPPORTED_POINTS];
पूर्ण;

अटल व्योम rpi_ts_poll(काष्ठा input_dev *input)
अणु
	काष्ठा rpi_ts *ts = input_get_drvdata(input);
	काष्ठा rpi_ts_regs regs;
	पूर्णांक modअगरied_ids = 0;
	दीर्घ released_ids;
	पूर्णांक event_type;
	पूर्णांक touchid;
	पूर्णांक x, y;
	पूर्णांक i;

	स_नकल_fromio(&regs, ts->fw_regs_va, माप(regs));
	/*
	 * We poll the memory based रेजिस्टर copy of the touchscreen chip using
	 * the number of poपूर्णांकs रेजिस्टर to know whether the copy has been
	 * updated (we ग_लिखो 99 to the memory copy, the GPU will ग_लिखो between
	 * 0 - 10 poपूर्णांकs)
	 */
	ioग_लिखो8(RPI_TS_NPOINTS_REG_INVALIDATE,
		 ts->fw_regs_va + दुरत्व(काष्ठा rpi_ts_regs, num_poपूर्णांकs));

	अगर (regs.num_poपूर्णांकs == RPI_TS_NPOINTS_REG_INVALIDATE ||
	    (regs.num_poपूर्णांकs == 0 && ts->known_ids == 0))
		वापस;

	क्रम (i = 0; i < regs.num_poपूर्णांकs; i++) अणु
		x = (((पूर्णांक)regs.poपूर्णांक[i].xh & 0xf) << 8) + regs.poपूर्णांक[i].xl;
		y = (((पूर्णांक)regs.poपूर्णांक[i].yh & 0xf) << 8) + regs.poपूर्णांक[i].yl;
		touchid = (regs.poपूर्णांक[i].yh >> 4) & 0xf;
		event_type = (regs.poपूर्णांक[i].xh >> 6) & 0x03;

		modअगरied_ids |= BIT(touchid);

		अगर (event_type == RPI_TS_FTS_TOUCH_DOWN ||
		    event_type == RPI_TS_FTS_TOUCH_CONTACT) अणु
			input_mt_slot(input, touchid);
			input_mt_report_slot_state(input, MT_TOOL_FINGER, 1);
			touchscreen_report_pos(input, &ts->prop, x, y, true);
		पूर्ण
	पूर्ण

	released_ids = ts->known_ids & ~modअगरied_ids;
	क्रम_each_set_bit(i, &released_ids, RPI_TS_MAX_SUPPORTED_POINTS) अणु
		input_mt_slot(input, i);
		input_mt_report_slot_inactive(input);
		modअगरied_ids &= ~(BIT(i));
	पूर्ण
	ts->known_ids = modअगरied_ids;

	input_mt_sync_frame(input);
	input_sync(input);
पूर्ण

अटल व्योम rpi_ts_dma_cleanup(व्योम *data)
अणु
	काष्ठा rpi_ts *ts = data;
	काष्ठा device *dev = &ts->pdev->dev;

	dma_मुक्त_coherent(dev, PAGE_SIZE, ts->fw_regs_va, ts->fw_regs_phys);
पूर्ण

अटल पूर्णांक rpi_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा input_dev *input;
	काष्ठा device_node *fw_node;
	काष्ठा rpi_firmware *fw;
	काष्ठा rpi_ts *ts;
	u32 touchbuf;
	पूर्णांक error;

	fw_node = of_get_parent(np);
	अगर (!fw_node) अणु
		dev_err(dev, "Missing firmware node\n");
		वापस -ENOENT;
	पूर्ण

	fw = rpi_firmware_get(fw_node);
	of_node_put(fw_node);
	अगर (!fw)
		वापस -EPROBE_DEFER;

	ts = devm_kzalloc(dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;
	ts->pdev = pdev;

	ts->fw_regs_va = dma_alloc_coherent(dev, PAGE_SIZE, &ts->fw_regs_phys,
					    GFP_KERNEL);
	अगर (!ts->fw_regs_va) अणु
		dev_err(dev, "failed to dma_alloc_coherent\n");
		वापस -ENOMEM;
	पूर्ण

	error = devm_add_action_or_reset(dev, rpi_ts_dma_cleanup, ts);
	अगर (error) अणु
		dev_err(dev, "failed to devm_add_action_or_reset, %d\n", error);
		वापस error;
	पूर्ण

	touchbuf = (u32)ts->fw_regs_phys;
	error = rpi_firmware_property(fw, RPI_FIRMWARE_FRAMEBUFFER_SET_TOUCHBUF,
				      &touchbuf, माप(touchbuf));
	rpi_firmware_put(fw);
	अगर (error || touchbuf != 0) अणु
		dev_warn(dev, "Failed to set touchbuf, %d\n", error);
		वापस error;
	पूर्ण

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	ts->input = input;
	input_set_drvdata(input, ts);

	input->name = "raspberrypi-ts";
	input->id.bustype = BUS_HOST;

	input_set_असल_params(input, ABS_MT_POSITION_X, 0,
			     RPI_TS_DEFAULT_WIDTH, 0, 0);
	input_set_असल_params(input, ABS_MT_POSITION_Y, 0,
			     RPI_TS_DEFAULT_HEIGHT, 0, 0);
	touchscreen_parse_properties(input, true, &ts->prop);

	error = input_mt_init_slots(input, RPI_TS_MAX_SUPPORTED_POINTS,
				    INPUT_MT_सूचीECT);
	अगर (error) अणु
		dev_err(dev, "could not init mt slots, %d\n", error);
		वापस error;
	पूर्ण

	error = input_setup_polling(input, rpi_ts_poll);
	अगर (error) अणु
		dev_err(dev, "could not set up polling mode, %d\n", error);
		वापस error;
	पूर्ण

	input_set_poll_पूर्णांकerval(input, RPI_TS_POLL_INTERVAL);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "could not register input device, %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rpi_ts_match[] = अणु
	अणु .compatible = "raspberrypi,firmware-ts", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rpi_ts_match);

अटल काष्ठा platक्रमm_driver rpi_ts_driver = अणु
	.driver = अणु
		.name = "raspberrypi-ts",
		.of_match_table = rpi_ts_match,
	पूर्ण,
	.probe = rpi_ts_probe,
पूर्ण;
module_platक्रमm_driver(rpi_ts_driver);

MODULE_AUTHOR("Gordon Hollingworth");
MODULE_AUTHOR("Nicolas Saenz Julienne <nsaenzjulienne@suse.de>");
MODULE_DESCRIPTION("Raspberry Pi firmware based touchscreen driver");
MODULE_LICENSE("GPL v2");
