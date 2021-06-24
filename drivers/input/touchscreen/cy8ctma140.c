<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Cypress CY8CTMA140 (TMA140) touchscreen
 * (C) 2020 Linus Walleij <linus.walleij@linaro.org>
 * (C) 2007 Cypress
 * (C) 2007 Google, Inc.
 *
 * Inspired by the पंचांगa140_skomer.c driver in the Samsung GT-S7710 code
 * drop. The GT-S7710 is codenamed "Skomer", the code also indicates
 * that the same touchscreen was used in a product called "Lucas".
 *
 * The code drop क्रम GT-S7710 also contains a firmware करोwnloader and
 * 15 (!) versions of the firmware drop from Cypress. But here we assume
 * the firmware got करोwnloaded to the touchscreen flash successfully and
 * just use it to पढ़ो the fingers. The shipped venकरोr driver करोes the
 * same.
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/input.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/input/mt.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/delay.h>

#घोषणा CY8CTMA140_NAME			"cy8ctma140"

#घोषणा CY8CTMA140_MAX_FINGERS		4

#घोषणा CY8CTMA140_GET_FINGERS		0x00
#घोषणा CY8CTMA140_GET_FW_INFO		0x19

/* This message also fits some bytes क्रम touchkeys, अगर used */
#घोषणा CY8CTMA140_PACKET_SIZE		31

#घोषणा CY8CTMA140_INVALID_BUFFER_BIT	5

काष्ठा cy8cपंचांगa140 अणु
	काष्ठा input_dev *input;
	काष्ठा touchscreen_properties props;
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा regulator_bulk_data regulators[2];
	u8 prev_fingers;
	u8 prev_f1id;
	u8 prev_f2id;
पूर्ण;

अटल व्योम cy8cपंचांगa140_report(काष्ठा cy8cपंचांगa140 *ts, u8 *data, पूर्णांक n_fingers)
अणु
	अटल स्थिर u8 contact_offsets[] = अणु 0x03, 0x09, 0x10, 0x16 पूर्ण;
	u8 *buf;
	u16 x, y;
	u8 w;
	u8 id;
	पूर्णांक slot;
	पूर्णांक i;

	क्रम (i = 0; i < n_fingers; i++) अणु
		buf = &data[contact_offsets[i]];

		/*
		 * Odd contacts have contact ID in the lower nibble of
		 * the preceding byte, whereas even contacts have it in
		 * the upper nibble of the following byte.
		 */
		id = i % 2 ? buf[-1] & 0x0f : buf[5] >> 4;
		slot = input_mt_get_slot_by_key(ts->input, id);
		अगर (slot < 0)
			जारी;

		x = get_unaligned_be16(buf);
		y = get_unaligned_be16(buf + 2);
		w = buf[4];

		dev_dbg(ts->dev, "finger %d: ID %02x (%d, %d) w: %d\n",
			slot, id, x, y, w);

		input_mt_slot(ts->input, slot);
		input_mt_report_slot_state(ts->input, MT_TOOL_FINGER, true);
		touchscreen_report_pos(ts->input, &ts->props, x, y, true);
		input_report_असल(ts->input, ABS_MT_TOUCH_MAJOR, w);
	पूर्ण

	input_mt_sync_frame(ts->input);
	input_sync(ts->input);
पूर्ण

अटल irqवापस_t cy8cपंचांगa140_irq_thपढ़ो(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा cy8cपंचांगa140 *ts = d;
	u8 cmdbuf[] = अणु CY8CTMA140_GET_FINGERS पूर्ण;
	u8 buf[CY8CTMA140_PACKET_SIZE];
	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = ts->client->addr,
			.flags = 0,
			.len = माप(cmdbuf),
			.buf = cmdbuf,
		पूर्ण, अणु
			.addr = ts->client->addr,
			.flags = I2C_M_RD,
			.len = माप(buf),
			.buf = buf,
		पूर्ण,
	पूर्ण;
	u8 n_fingers;
	पूर्णांक ret;

	ret = i2c_transfer(ts->client->adapter, msg, ARRAY_SIZE(msg));
	अगर (ret != ARRAY_SIZE(msg)) अणु
		अगर (ret < 0)
			dev_err(ts->dev, "error reading message: %d\n", ret);
		अन्यथा
			dev_err(ts->dev, "wrong number of messages\n");
		जाओ out;
	पूर्ण

	अगर (buf[1] & BIT(CY8CTMA140_INVALID_BUFFER_BIT)) अणु
		dev_dbg(ts->dev, "invalid event\n");
		जाओ out;
	पूर्ण

	n_fingers = buf[2] & 0x0f;
	अगर (n_fingers > CY8CTMA140_MAX_FINGERS) अणु
		dev_err(ts->dev, "unexpected number of fingers: %d\n",
			n_fingers);
		जाओ out;
	पूर्ण

	cy8cपंचांगa140_report(ts, buf, n_fingers);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cy8cपंचांगa140_init(काष्ठा cy8cपंचांगa140 *ts)
अणु
	u8 addr[1];
	u8 buf[5];
	पूर्णांक ret;

	addr[0] = CY8CTMA140_GET_FW_INFO;
	ret = i2c_master_send(ts->client, addr, 1);
	अगर (ret < 0) अणु
		dev_err(ts->dev, "error sending FW info message\n");
		वापस ret;
	पूर्ण
	ret = i2c_master_recv(ts->client, buf, 5);
	अगर (ret < 0) अणु
		dev_err(ts->dev, "error receiving FW info message\n");
		वापस ret;
	पूर्ण
	अगर (ret != 5) अणु
		dev_err(ts->dev, "got only %d bytes\n", ret);
		वापस -EIO;
	पूर्ण

	dev_dbg(ts->dev, "vendor %c%c, HW ID %.2d, FW ver %.4d\n",
		buf[0], buf[1], buf[3], buf[4]);

	वापस 0;
पूर्ण

अटल पूर्णांक cy8cपंचांगa140_घातer_up(काष्ठा cy8cपंचांगa140 *ts)
अणु
	पूर्णांक error;

	error = regulator_bulk_enable(ARRAY_SIZE(ts->regulators),
				      ts->regulators);
	अगर (error) अणु
		dev_err(ts->dev, "failed to enable regulators\n");
		वापस error;
	पूर्ण

	msleep(250);

	वापस 0;
पूर्ण

अटल व्योम cy8cपंचांगa140_घातer_करोwn(काष्ठा cy8cपंचांगa140 *ts)
अणु
	regulator_bulk_disable(ARRAY_SIZE(ts->regulators),
			       ts->regulators);
पूर्ण

/* Called from the रेजिस्टरed devm action */
अटल व्योम cy8cपंचांगa140_घातer_off_action(व्योम *d)
अणु
	काष्ठा cy8cपंचांगa140 *ts = d;

	cy8cपंचांगa140_घातer_करोwn(ts);
पूर्ण

अटल पूर्णांक cy8cपंचांगa140_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cy8cपंचांगa140 *ts;
	काष्ठा input_dev *input;
	काष्ठा device *dev = &client->dev;
	पूर्णांक error;

	ts = devm_kzalloc(dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	ts->dev = dev;
	ts->client = client;
	ts->input = input;

	input_set_capability(input, EV_ABS, ABS_MT_POSITION_X);
	input_set_capability(input, EV_ABS, ABS_MT_POSITION_Y);
	/* One byte क्रम width 0..255 so this is the limit */
	input_set_असल_params(input, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
	/*
	 * This sets up event max/min capabilities and fuzz.
	 * Some DT properties are compulsory so we करो not need
	 * to provide शेषs क्रम X/Y max or pressure max.
	 *
	 * We just initialize a very simple MT touchscreen here,
	 * some devices use the capability of this touchscreen to
	 * provide touchkeys, and in that हाल this needs to be
	 * extended to handle touchkey input.
	 *
	 * The firmware takes care of finger tracking and dropping
	 * invalid ranges.
	 */
	touchscreen_parse_properties(input, true, &ts->props);
	input_असल_set_fuzz(input, ABS_MT_POSITION_X, 0);
	input_असल_set_fuzz(input, ABS_MT_POSITION_Y, 0);

	error = input_mt_init_slots(input, CY8CTMA140_MAX_FINGERS,
				  INPUT_MT_सूचीECT | INPUT_MT_DROP_UNUSED);
	अगर (error)
		वापस error;

	input->name = CY8CTMA140_NAME;
	input->id.bustype = BUS_I2C;
	input_set_drvdata(input, ts);

	/*
	 * VCPIN is the analog voltage supply
	 * VDD is the digital voltage supply
	 * since the voltage range of VDD overlaps that of VCPIN,
	 * many designs to just supply both with a single voltage
	 * source of ~3.3 V.
	 */
	ts->regulators[0].supply = "vcpin";
	ts->regulators[1].supply = "vdd";
	error = devm_regulator_bulk_get(dev, ARRAY_SIZE(ts->regulators),
				      ts->regulators);
	अगर (error) अणु
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "Failed to get regulators %d\n",
				error);
		वापस error;
	पूर्ण

	error = cy8cपंचांगa140_घातer_up(ts);
	अगर (error)
		वापस error;

	error = devm_add_action_or_reset(dev, cy8cपंचांगa140_घातer_off_action, ts);
	अगर (error) अणु
		dev_err(dev, "failed to install power off handler\n");
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, client->irq,
					  शून्य, cy8cपंचांगa140_irq_thपढ़ो,
					  IRQF_ONESHOT, CY8CTMA140_NAME, ts);
	अगर (error) अणु
		dev_err(dev, "irq %d busy? error %d\n", client->irq, error);
		वापस error;
	पूर्ण

	error = cy8cपंचांगa140_init(ts);
	अगर (error)
		वापस error;

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	i2c_set_clientdata(client, ts);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cy8cपंचांगa140_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cy8cपंचांगa140 *ts = i2c_get_clientdata(client);

	अगर (!device_may_wakeup(&client->dev))
		cy8cपंचांगa140_घातer_करोwn(ts);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cy8cपंचांगa140_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cy8cपंचांगa140 *ts = i2c_get_clientdata(client);
	पूर्णांक error;

	अगर (!device_may_wakeup(&client->dev)) अणु
		error = cy8cपंचांगa140_घातer_up(ts);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cy8cपंचांगa140_pm, cy8cपंचांगa140_suspend, cy8cपंचांगa140_resume);

अटल स्थिर काष्ठा i2c_device_id cy8cपंचांगa140_idtable[] = अणु
	अणु CY8CTMA140_NAME, 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cy8cपंचांगa140_idtable);

अटल स्थिर काष्ठा of_device_id cy8cपंचांगa140_of_match[] = अणु
	अणु .compatible = "cypress,cy8ctma140", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cy8cपंचांगa140_of_match);

अटल काष्ठा i2c_driver cy8cपंचांगa140_driver = अणु
	.driver		= अणु
		.name	= CY8CTMA140_NAME,
		.pm	= &cy8cपंचांगa140_pm,
		.of_match_table = cy8cपंचांगa140_of_match,
	पूर्ण,
	.id_table	= cy8cपंचांगa140_idtable,
	.probe		= cy8cपंचांगa140_probe,
पूर्ण;
module_i2c_driver(cy8cपंचांगa140_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("CY8CTMA140 TouchScreen Driver");
MODULE_LICENSE("GPL v2");
