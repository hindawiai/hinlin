<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Azoteq IQS620A/621/622/624/625 Multi-Function Sensors
 *
 * Copyright (C) 2019 Jeff LaBundy <jeff@labundy.com>
 *
 * These devices rely on application-specअगरic रेजिस्टर settings and calibration
 * data developed in and exported from a suite of GUIs offered by the venकरोr. A
 * separate tool converts the GUIs' ASCII-based output पूर्णांकo a standard firmware
 * file parsed by the driver.
 *
 * Link to datasheets and GUIs: https://www.azoteq.com/
 *
 * Link to conversion tool: https://github.com/jlabundy/iqs62x-h2bin.git
 */

#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/iqs62x.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा IQS62X_PROD_NUM				0x00

#घोषणा IQS62X_SYS_FLAGS			0x10

#घोषणा IQS620_HALL_FLAGS			0x16
#घोषणा IQS621_HALL_FLAGS			0x19
#घोषणा IQS622_HALL_FLAGS			IQS621_HALL_FLAGS

#घोषणा IQS624_INTERVAL_NUM			0x18
#घोषणा IQS625_INTERVAL_NUM			0x12

#घोषणा IQS622_PROX_SETTINGS_4			0x48
#घोषणा IQS620_PROX_SETTINGS_4			0x50
#घोषणा IQS620_PROX_SETTINGS_4_SAR_EN		BIT(7)

#घोषणा IQS621_ALS_CAL_DIV_LUX			0x82
#घोषणा IQS621_ALS_CAL_DIV_IR			0x83

#घोषणा IQS620_TEMP_CAL_MULT			0xC2
#घोषणा IQS620_TEMP_CAL_DIV			0xC3
#घोषणा IQS620_TEMP_CAL_OFFS			0xC4

#घोषणा IQS62X_SYS_SETTINGS			0xD0
#घोषणा IQS62X_SYS_SETTINGS_ACK_RESET		BIT(6)
#घोषणा IQS62X_SYS_SETTINGS_EVENT_MODE		BIT(5)
#घोषणा IQS62X_SYS_SETTINGS_CLK_DIV		BIT(4)
#घोषणा IQS62X_SYS_SETTINGS_COMM_ATI		BIT(3)
#घोषणा IQS62X_SYS_SETTINGS_REDO_ATI		BIT(1)

#घोषणा IQS62X_PWR_SETTINGS			0xD2
#घोषणा IQS62X_PWR_SETTINGS_DIS_AUTO		BIT(5)
#घोषणा IQS62X_PWR_SETTINGS_PWR_MODE_MASK	(BIT(4) | BIT(3))
#घोषणा IQS62X_PWR_SETTINGS_PWR_MODE_HALT	(BIT(4) | BIT(3))
#घोषणा IQS62X_PWR_SETTINGS_PWR_MODE_NORM	0

#घोषणा IQS62X_OTP_CMD				0xF0
#घोषणा IQS62X_OTP_CMD_FG3			0x13
#घोषणा IQS62X_OTP_DATA				0xF1
#घोषणा IQS62X_MAX_REG				0xFF

#घोषणा IQS62X_HALL_CAL_MASK			GENMASK(3, 0)

#घोषणा IQS62X_FW_REC_TYPE_INFO			0
#घोषणा IQS62X_FW_REC_TYPE_PROD			1
#घोषणा IQS62X_FW_REC_TYPE_HALL			2
#घोषणा IQS62X_FW_REC_TYPE_MASK			3
#घोषणा IQS62X_FW_REC_TYPE_DATA			4

#घोषणा IQS62X_ATI_STARTUP_MS			350
#घोषणा IQS62X_FILT_SETTLE_MS			250

काष्ठा iqs62x_fw_rec अणु
	u8 type;
	u8 addr;
	u8 len;
	u8 data;
पूर्ण __packed;

काष्ठा iqs62x_fw_blk अणु
	काष्ठा list_head list;
	u8 addr;
	u8 mask;
	u8 len;
	u8 data[];
पूर्ण;

काष्ठा iqs62x_info अणु
	u8 prod_num;
	u8 sw_num;
	u8 hw_num;
पूर्ण __packed;

अटल पूर्णांक iqs62x_dev_init(काष्ठा iqs62x_core *iqs62x)
अणु
	काष्ठा iqs62x_fw_blk *fw_blk;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	list_क्रम_each_entry(fw_blk, &iqs62x->fw_blk_head, list) अणु
		/*
		 * In हाल ATI is in progress, रुको क्रम it to complete beक्रमe
		 * lowering the core घड़ी frequency.
		 */
		अगर (fw_blk->addr == IQS62X_SYS_SETTINGS &&
		    *fw_blk->data & IQS62X_SYS_SETTINGS_CLK_DIV)
			msleep(IQS62X_ATI_STARTUP_MS);

		अगर (fw_blk->mask)
			ret = regmap_update_bits(iqs62x->regmap, fw_blk->addr,
						 fw_blk->mask, *fw_blk->data);
		अन्यथा
			ret = regmap_raw_ग_लिखो(iqs62x->regmap, fw_blk->addr,
					       fw_blk->data, fw_blk->len);
		अगर (ret)
			वापस ret;
	पूर्ण

	चयन (iqs62x->dev_desc->prod_num) अणु
	हाल IQS620_PROD_NUM:
	हाल IQS622_PROD_NUM:
		ret = regmap_पढ़ो(iqs62x->regmap,
				  iqs62x->dev_desc->prox_settings, &val);
		अगर (ret)
			वापस ret;

		अगर (val & IQS620_PROX_SETTINGS_4_SAR_EN)
			iqs62x->ui_sel = IQS62X_UI_SAR1;
		fallthrough;

	हाल IQS621_PROD_NUM:
		ret = regmap_ग_लिखो(iqs62x->regmap, IQS620_GLBL_EVENT_MASK,
				   IQS620_GLBL_EVENT_MASK_PMU |
				   iqs62x->dev_desc->prox_mask |
				   iqs62x->dev_desc->sar_mask |
				   iqs62x->dev_desc->hall_mask |
				   iqs62x->dev_desc->hyst_mask |
				   iqs62x->dev_desc->temp_mask |
				   iqs62x->dev_desc->als_mask |
				   iqs62x->dev_desc->ir_mask);
		अगर (ret)
			वापस ret;
		अवरोध;

	शेष:
		ret = regmap_ग_लिखो(iqs62x->regmap, IQS624_HALL_UI,
				   IQS624_HALL_UI_WHL_EVENT |
				   IQS624_HALL_UI_INT_EVENT |
				   IQS624_HALL_UI_AUTO_CAL);
		अगर (ret)
			वापस ret;

		/*
		 * The IQS625 शेष पूर्णांकerval भागider is below the minimum
		 * permissible value, and the datasheet mandates that it is
		 * corrected during initialization (unless an updated value
		 * has alपढ़ोy been provided by firmware).
		 *
		 * To protect against an unacceptably low user-entered value
		 * stored in the firmware, the same check is extended to the
		 * IQS624 as well.
		 */
		ret = regmap_पढ़ो(iqs62x->regmap, IQS624_INTERVAL_DIV, &val);
		अगर (ret)
			वापस ret;

		अगर (val >= iqs62x->dev_desc->पूर्णांकerval_भाग)
			अवरोध;

		ret = regmap_ग_लिखो(iqs62x->regmap, IQS624_INTERVAL_DIV,
				   iqs62x->dev_desc->पूर्णांकerval_भाग);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Place the device in streaming mode at first so as not to miss the
	 * limited number of पूर्णांकerrupts that would otherwise occur after ATI
	 * completes. The device is subsequently placed in event mode by the
	 * पूर्णांकerrupt handler.
	 *
	 * In the meanसमय, mask पूर्णांकerrupts during ATI to prevent the device
	 * from soliciting I2C traffic until the noise-sensitive ATI process
	 * is complete.
	 */
	ret = regmap_update_bits(iqs62x->regmap, IQS62X_SYS_SETTINGS,
				 IQS62X_SYS_SETTINGS_ACK_RESET |
				 IQS62X_SYS_SETTINGS_EVENT_MODE |
				 IQS62X_SYS_SETTINGS_COMM_ATI |
				 IQS62X_SYS_SETTINGS_REDO_ATI,
				 IQS62X_SYS_SETTINGS_ACK_RESET |
				 IQS62X_SYS_SETTINGS_REDO_ATI);
	अगर (ret)
		वापस ret;

	/*
	 * The following delay gives the device समय to deनिश्चित its RDY output
	 * in हाल a communication winकरोw was खोलो जबतक the REDO_ATI field was
	 * written. This prevents an पूर्णांकerrupt from being serviced prematurely.
	 */
	usleep_range(5000, 5100);

	वापस 0;
पूर्ण

अटल पूर्णांक iqs62x_firmware_parse(काष्ठा iqs62x_core *iqs62x,
				 स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा i2c_client *client = iqs62x->client;
	काष्ठा iqs62x_fw_rec *fw_rec;
	काष्ठा iqs62x_fw_blk *fw_blk;
	अचिन्हित पूर्णांक val;
	माप_प्रकार pos = 0;
	पूर्णांक ret = 0;
	u8 mask, len, *data;
	u8 hall_cal_index = 0;

	जबतक (pos < fw->size) अणु
		अगर (pos + माप(*fw_rec) > fw->size) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		fw_rec = (काष्ठा iqs62x_fw_rec *)(fw->data + pos);
		pos += माप(*fw_rec);

		अगर (pos + fw_rec->len - 1 > fw->size) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		pos += fw_rec->len - 1;

		चयन (fw_rec->type) अणु
		हाल IQS62X_FW_REC_TYPE_INFO:
			जारी;

		हाल IQS62X_FW_REC_TYPE_PROD:
			अगर (fw_rec->data == iqs62x->dev_desc->prod_num)
				जारी;

			dev_err(&client->dev,
				"Incompatible product number: 0x%02X\n",
				fw_rec->data);
			ret = -EINVAL;
			अवरोध;

		हाल IQS62X_FW_REC_TYPE_HALL:
			अगर (!hall_cal_index) अणु
				ret = regmap_ग_लिखो(iqs62x->regmap,
						   IQS62X_OTP_CMD,
						   IQS62X_OTP_CMD_FG3);
				अगर (ret)
					अवरोध;

				ret = regmap_पढ़ो(iqs62x->regmap,
						  IQS62X_OTP_DATA, &val);
				अगर (ret)
					अवरोध;

				hall_cal_index = val & IQS62X_HALL_CAL_MASK;
				अगर (!hall_cal_index) अणु
					dev_err(&client->dev,
						"Uncalibrated device\n");
					ret = -ENODATA;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (hall_cal_index > fw_rec->len) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			mask = 0;
			data = &fw_rec->data + hall_cal_index - 1;
			len = माप(*data);
			अवरोध;

		हाल IQS62X_FW_REC_TYPE_MASK:
			अगर (fw_rec->len < (माप(mask) + माप(*data))) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			mask = fw_rec->data;
			data = &fw_rec->data + माप(mask);
			len = माप(*data);
			अवरोध;

		हाल IQS62X_FW_REC_TYPE_DATA:
			mask = 0;
			data = &fw_rec->data;
			len = fw_rec->len;
			अवरोध;

		शेष:
			dev_err(&client->dev,
				"Unrecognized record type: 0x%02X\n",
				fw_rec->type);
			ret = -EINVAL;
		पूर्ण

		अगर (ret)
			अवरोध;

		fw_blk = devm_kzalloc(&client->dev,
				      काष्ठा_size(fw_blk, data, len),
				      GFP_KERNEL);
		अगर (!fw_blk) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		fw_blk->addr = fw_rec->addr;
		fw_blk->mask = mask;
		fw_blk->len = len;
		स_नकल(fw_blk->data, data, len);

		list_add(&fw_blk->list, &iqs62x->fw_blk_head);
	पूर्ण

	release_firmware(fw);

	वापस ret;
पूर्ण

स्थिर काष्ठा iqs62x_event_desc iqs62x_events[IQS62X_NUM_EVENTS] = अणु
	[IQS62X_EVENT_PROX_CH0_T] = अणु
		.reg	= IQS62X_EVENT_PROX,
		.mask	= BIT(4),
		.val	= BIT(4),
	पूर्ण,
	[IQS62X_EVENT_PROX_CH0_P] = अणु
		.reg	= IQS62X_EVENT_PROX,
		.mask	= BIT(0),
		.val	= BIT(0),
	पूर्ण,
	[IQS62X_EVENT_PROX_CH1_T] = अणु
		.reg	= IQS62X_EVENT_PROX,
		.mask	= BIT(5),
		.val	= BIT(5),
	पूर्ण,
	[IQS62X_EVENT_PROX_CH1_P] = अणु
		.reg	= IQS62X_EVENT_PROX,
		.mask	= BIT(1),
		.val	= BIT(1),
	पूर्ण,
	[IQS62X_EVENT_PROX_CH2_T] = अणु
		.reg	= IQS62X_EVENT_PROX,
		.mask	= BIT(6),
		.val	= BIT(6),
	पूर्ण,
	[IQS62X_EVENT_PROX_CH2_P] = अणु
		.reg	= IQS62X_EVENT_PROX,
		.mask	= BIT(2),
		.val	= BIT(2),
	पूर्ण,
	[IQS62X_EVENT_HYST_POS_T] = अणु
		.reg	= IQS62X_EVENT_HYST,
		.mask	= BIT(6) | BIT(7),
		.val	= BIT(6),
	पूर्ण,
	[IQS62X_EVENT_HYST_POS_P] = अणु
		.reg	= IQS62X_EVENT_HYST,
		.mask	= BIT(5) | BIT(7),
		.val	= BIT(5),
	पूर्ण,
	[IQS62X_EVENT_HYST_NEG_T] = अणु
		.reg	= IQS62X_EVENT_HYST,
		.mask	= BIT(6) | BIT(7),
		.val	= BIT(6) | BIT(7),
	पूर्ण,
	[IQS62X_EVENT_HYST_NEG_P] = अणु
		.reg	= IQS62X_EVENT_HYST,
		.mask	= BIT(5) | BIT(7),
		.val	= BIT(5) | BIT(7),
	पूर्ण,
	[IQS62X_EVENT_SAR1_ACT] = अणु
		.reg	= IQS62X_EVENT_HYST,
		.mask	= BIT(4),
		.val	= BIT(4),
	पूर्ण,
	[IQS62X_EVENT_SAR1_QRD] = अणु
		.reg	= IQS62X_EVENT_HYST,
		.mask	= BIT(2),
		.val	= BIT(2),
	पूर्ण,
	[IQS62X_EVENT_SAR1_MOVE] = अणु
		.reg	= IQS62X_EVENT_HYST,
		.mask	= BIT(1),
		.val	= BIT(1),
	पूर्ण,
	[IQS62X_EVENT_SAR1_HALT] = अणु
		.reg	= IQS62X_EVENT_HYST,
		.mask	= BIT(0),
		.val	= BIT(0),
	पूर्ण,
	[IQS62X_EVENT_WHEEL_UP] = अणु
		.reg	= IQS62X_EVENT_WHEEL,
		.mask	= BIT(7) | BIT(6),
		.val	= BIT(7),
	पूर्ण,
	[IQS62X_EVENT_WHEEL_DN] = अणु
		.reg	= IQS62X_EVENT_WHEEL,
		.mask	= BIT(7) | BIT(6),
		.val	= BIT(7) | BIT(6),
	पूर्ण,
	[IQS62X_EVENT_HALL_N_T] = अणु
		.reg	= IQS62X_EVENT_HALL,
		.mask	= BIT(2) | BIT(0),
		.val	= BIT(2),
	पूर्ण,
	[IQS62X_EVENT_HALL_N_P] = अणु
		.reg	= IQS62X_EVENT_HALL,
		.mask	= BIT(1) | BIT(0),
		.val	= BIT(1),
	पूर्ण,
	[IQS62X_EVENT_HALL_S_T] = अणु
		.reg	= IQS62X_EVENT_HALL,
		.mask	= BIT(2) | BIT(0),
		.val	= BIT(2) | BIT(0),
	पूर्ण,
	[IQS62X_EVENT_HALL_S_P] = अणु
		.reg	= IQS62X_EVENT_HALL,
		.mask	= BIT(1) | BIT(0),
		.val	= BIT(1) | BIT(0),
	पूर्ण,
	[IQS62X_EVENT_SYS_RESET] = अणु
		.reg	= IQS62X_EVENT_SYS,
		.mask	= BIT(7),
		.val	= BIT(7),
	पूर्ण,
	[IQS62X_EVENT_SYS_ATI] = अणु
		.reg	= IQS62X_EVENT_SYS,
		.mask	= BIT(2),
		.val	= BIT(2),
	पूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(iqs62x_events);

अटल irqवापस_t iqs62x_irq(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा iqs62x_core *iqs62x = context;
	काष्ठा i2c_client *client = iqs62x->client;
	काष्ठा iqs62x_event_data event_data;
	काष्ठा iqs62x_event_desc event_desc;
	क्रमागत iqs62x_event_reg event_reg;
	अचिन्हित दीर्घ event_flags = 0;
	पूर्णांक ret, i, j;
	u8 event_map[IQS62X_EVENT_SIZE];

	/*
	 * The device निश्चितs the RDY output to संकेत the beginning of a
	 * communication winकरोw, which is बंदd by an I2C stop condition.
	 * As such, all पूर्णांकerrupt status is captured in a single पढ़ो and
	 * broadcast to any पूर्णांकerested sub-device drivers.
	 */
	ret = regmap_raw_पढ़ो(iqs62x->regmap, IQS62X_SYS_FLAGS, event_map,
			      माप(event_map));
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to read device status: %d\n",
			ret);
		वापस IRQ_NONE;
	पूर्ण

	क्रम (i = 0; i < माप(event_map); i++) अणु
		event_reg = iqs62x->dev_desc->event_regs[iqs62x->ui_sel][i];

		चयन (event_reg) अणु
		हाल IQS62X_EVENT_UI_LO:
			event_data.ui_data = get_unaligned_le16(&event_map[i]);
			fallthrough;

		हाल IQS62X_EVENT_UI_HI:
		हाल IQS62X_EVENT_NONE:
			जारी;

		हाल IQS62X_EVENT_ALS:
			event_data.als_flags = event_map[i];
			जारी;

		हाल IQS62X_EVENT_IR:
			event_data.ir_flags = event_map[i];
			जारी;

		हाल IQS62X_EVENT_INTER:
			event_data.पूर्णांकerval = event_map[i];
			जारी;

		हाल IQS62X_EVENT_HYST:
			event_map[i] <<= iqs62x->dev_desc->hyst_shअगरt;
			fallthrough;

		हाल IQS62X_EVENT_WHEEL:
		हाल IQS62X_EVENT_HALL:
		हाल IQS62X_EVENT_PROX:
		हाल IQS62X_EVENT_SYS:
			अवरोध;
		पूर्ण

		क्रम (j = 0; j < IQS62X_NUM_EVENTS; j++) अणु
			event_desc = iqs62x_events[j];

			अगर (event_desc.reg != event_reg)
				जारी;

			अगर ((event_map[i] & event_desc.mask) == event_desc.val)
				event_flags |= BIT(j);
		पूर्ण
	पूर्ण

	/*
	 * The device resets itself in response to the I2C master stalling
	 * communication past a fixed समयout. In this हाल, all रेजिस्टरs
	 * are restored and any पूर्णांकerested sub-device drivers are notअगरied.
	 */
	अगर (event_flags & BIT(IQS62X_EVENT_SYS_RESET)) अणु
		dev_err(&client->dev, "Unexpected device reset\n");

		ret = iqs62x_dev_init(iqs62x);
		अगर (ret) अणु
			dev_err(&client->dev,
				"Failed to re-initialize device: %d\n", ret);
			वापस IRQ_NONE;
		पूर्ण

		iqs62x->event_cache |= BIT(IQS62X_EVENT_SYS_RESET);
		reinit_completion(&iqs62x->ati_करोne);
	पूर्ण अन्यथा अगर (event_flags & BIT(IQS62X_EVENT_SYS_ATI)) अणु
		iqs62x->event_cache |= BIT(IQS62X_EVENT_SYS_ATI);
		reinit_completion(&iqs62x->ati_करोne);
	पूर्ण अन्यथा अगर (!completion_करोne(&iqs62x->ati_करोne)) अणु
		ret = regmap_update_bits(iqs62x->regmap, IQS62X_SYS_SETTINGS,
					 IQS62X_SYS_SETTINGS_EVENT_MODE, 0xFF);
		अगर (ret) अणु
			dev_err(&client->dev,
				"Failed to enable event mode: %d\n", ret);
			वापस IRQ_NONE;
		पूर्ण

		msleep(IQS62X_FILT_SETTLE_MS);
		complete_all(&iqs62x->ati_करोne);
	पूर्ण

	/*
	 * Reset and ATI events are not broadcast to the sub-device drivers
	 * until ATI has completed. Any other events that may have occurred
	 * during ATI are ignored.
	 */
	अगर (completion_करोne(&iqs62x->ati_करोne)) अणु
		event_flags |= iqs62x->event_cache;
		ret = blocking_notअगरier_call_chain(&iqs62x->nh, event_flags,
						   &event_data);
		अगर (ret & NOTIFY_STOP_MASK)
			वापस IRQ_NONE;

		iqs62x->event_cache = 0;
	पूर्ण

	/*
	 * Once the communication winकरोw is बंदd, a small delay is added to
	 * ensure the device's RDY output has been deनिश्चितed by the समय the
	 * पूर्णांकerrupt handler वापसs.
	 */
	usleep_range(150, 200);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम iqs62x_firmware_load(स्थिर काष्ठा firmware *fw, व्योम *context)
अणु
	काष्ठा iqs62x_core *iqs62x = context;
	काष्ठा i2c_client *client = iqs62x->client;
	पूर्णांक ret;

	अगर (fw) अणु
		ret = iqs62x_firmware_parse(iqs62x, fw);
		अगर (ret) अणु
			dev_err(&client->dev, "Failed to parse firmware: %d\n",
				ret);
			जाओ err_out;
		पूर्ण
	पूर्ण

	ret = iqs62x_dev_init(iqs62x);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to initialize device: %d\n", ret);
		जाओ err_out;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, iqs62x_irq, IRQF_ONESHOT,
					client->name, iqs62x);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to request IRQ: %d\n", ret);
		जाओ err_out;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&iqs62x->ati_करोne,
					 msecs_to_jअगरfies(2000))) अणु
		dev_err(&client->dev, "Failed to complete ATI\n");
		जाओ err_out;
	पूर्ण

	ret = devm_mfd_add_devices(&client->dev, PLATFORM_DEVID_NONE,
				   iqs62x->dev_desc->sub_devs,
				   iqs62x->dev_desc->num_sub_devs,
				   शून्य, 0, शून्य);
	अगर (ret)
		dev_err(&client->dev, "Failed to add sub-devices: %d\n", ret);

err_out:
	complete_all(&iqs62x->fw_करोne);
पूर्ण

अटल स्थिर काष्ठा mfd_cell iqs620at_sub_devs[] = अणु
	अणु
		.name = "iqs62x-keys",
		.of_compatible = "azoteq,iqs620a-keys",
	पूर्ण,
	अणु
		.name = "iqs620a-pwm",
		.of_compatible = "azoteq,iqs620a-pwm",
	पूर्ण,
	अणु .name = "iqs620at-temp", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell iqs620a_sub_devs[] = अणु
	अणु
		.name = "iqs62x-keys",
		.of_compatible = "azoteq,iqs620a-keys",
	पूर्ण,
	अणु
		.name = "iqs620a-pwm",
		.of_compatible = "azoteq,iqs620a-pwm",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell iqs621_sub_devs[] = अणु
	अणु
		.name = "iqs62x-keys",
		.of_compatible = "azoteq,iqs621-keys",
	पूर्ण,
	अणु .name = "iqs621-als", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell iqs622_sub_devs[] = अणु
	अणु
		.name = "iqs62x-keys",
		.of_compatible = "azoteq,iqs622-keys",
	पूर्ण,
	अणु .name = "iqs621-als", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell iqs624_sub_devs[] = अणु
	अणु
		.name = "iqs62x-keys",
		.of_compatible = "azoteq,iqs624-keys",
	पूर्ण,
	अणु .name = "iqs624-pos", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell iqs625_sub_devs[] = अणु
	अणु
		.name = "iqs62x-keys",
		.of_compatible = "azoteq,iqs625-keys",
	पूर्ण,
	अणु .name = "iqs624-pos", पूर्ण,
पूर्ण;

अटल स्थिर u8 iqs620at_cal_regs[] = अणु
	IQS620_TEMP_CAL_MULT,
	IQS620_TEMP_CAL_DIV,
	IQS620_TEMP_CAL_OFFS,
पूर्ण;

अटल स्थिर u8 iqs621_cal_regs[] = अणु
	IQS621_ALS_CAL_DIV_LUX,
	IQS621_ALS_CAL_DIV_IR,
पूर्ण;

अटल स्थिर क्रमागत iqs62x_event_reg iqs620a_event_regs[][IQS62X_EVENT_SIZE] = अणु
	[IQS62X_UI_PROX] = अणु
		IQS62X_EVENT_SYS,	/* 0x10 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_PROX,	/* 0x12 */
		IQS62X_EVENT_HYST,	/* 0x13 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_HALL,	/* 0x16 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
	पूर्ण,
	[IQS62X_UI_SAR1] = अणु
		IQS62X_EVENT_SYS,	/* 0x10 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_HYST,	/* 0x13 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_HALL,	/* 0x16 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
	पूर्ण,
पूर्ण;

अटल स्थिर क्रमागत iqs62x_event_reg iqs621_event_regs[][IQS62X_EVENT_SIZE] = अणु
	[IQS62X_UI_PROX] = अणु
		IQS62X_EVENT_SYS,	/* 0x10 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_PROX,	/* 0x12 */
		IQS62X_EVENT_HYST,	/* 0x13 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_ALS,	/* 0x16 */
		IQS62X_EVENT_UI_LO,	/* 0x17 */
		IQS62X_EVENT_UI_HI,	/* 0x18 */
		IQS62X_EVENT_HALL,	/* 0x19 */
	पूर्ण,
पूर्ण;

अटल स्थिर क्रमागत iqs62x_event_reg iqs622_event_regs[][IQS62X_EVENT_SIZE] = अणु
	[IQS62X_UI_PROX] = अणु
		IQS62X_EVENT_SYS,	/* 0x10 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_PROX,	/* 0x12 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_ALS,	/* 0x14 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_IR,	/* 0x16 */
		IQS62X_EVENT_UI_LO,	/* 0x17 */
		IQS62X_EVENT_UI_HI,	/* 0x18 */
		IQS62X_EVENT_HALL,	/* 0x19 */
	पूर्ण,
	[IQS62X_UI_SAR1] = अणु
		IQS62X_EVENT_SYS,	/* 0x10 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_HYST,	/* 0x13 */
		IQS62X_EVENT_ALS,	/* 0x14 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_IR,	/* 0x16 */
		IQS62X_EVENT_UI_LO,	/* 0x17 */
		IQS62X_EVENT_UI_HI,	/* 0x18 */
		IQS62X_EVENT_HALL,	/* 0x19 */
	पूर्ण,
पूर्ण;

अटल स्थिर क्रमागत iqs62x_event_reg iqs624_event_regs[][IQS62X_EVENT_SIZE] = अणु
	[IQS62X_UI_PROX] = अणु
		IQS62X_EVENT_SYS,	/* 0x10 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_PROX,	/* 0x12 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_WHEEL,	/* 0x14 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_UI_LO,	/* 0x16 */
		IQS62X_EVENT_UI_HI,	/* 0x17 */
		IQS62X_EVENT_INTER,	/* 0x18 */
		IQS62X_EVENT_NONE,
	पूर्ण,
पूर्ण;

अटल स्थिर क्रमागत iqs62x_event_reg iqs625_event_regs[][IQS62X_EVENT_SIZE] = अणु
	[IQS62X_UI_PROX] = अणु
		IQS62X_EVENT_SYS,	/* 0x10 */
		IQS62X_EVENT_PROX,	/* 0x11 */
		IQS62X_EVENT_INTER,	/* 0x12 */
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
		IQS62X_EVENT_NONE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iqs62x_dev_desc iqs62x_devs[] = अणु
	अणु
		.dev_name	= "iqs620at",
		.sub_devs	= iqs620at_sub_devs,
		.num_sub_devs	= ARRAY_SIZE(iqs620at_sub_devs),
		.prod_num	= IQS620_PROD_NUM,
		.sw_num		= 0x08,
		.cal_regs	= iqs620at_cal_regs,
		.num_cal_regs	= ARRAY_SIZE(iqs620at_cal_regs),
		.prox_mask	= BIT(0),
		.sar_mask	= BIT(1) | BIT(7),
		.hall_mask	= BIT(2),
		.hyst_mask	= BIT(3),
		.temp_mask	= BIT(4),
		.prox_settings	= IQS620_PROX_SETTINGS_4,
		.hall_flags	= IQS620_HALL_FLAGS,
		.fw_name	= "iqs620a.bin",
		.event_regs	= &iqs620a_event_regs[IQS62X_UI_PROX],
	पूर्ण,
	अणु
		.dev_name	= "iqs620a",
		.sub_devs	= iqs620a_sub_devs,
		.num_sub_devs	= ARRAY_SIZE(iqs620a_sub_devs),
		.prod_num	= IQS620_PROD_NUM,
		.sw_num		= 0x08,
		.prox_mask	= BIT(0),
		.sar_mask	= BIT(1) | BIT(7),
		.hall_mask	= BIT(2),
		.hyst_mask	= BIT(3),
		.temp_mask	= BIT(4),
		.prox_settings	= IQS620_PROX_SETTINGS_4,
		.hall_flags	= IQS620_HALL_FLAGS,
		.fw_name	= "iqs620a.bin",
		.event_regs	= &iqs620a_event_regs[IQS62X_UI_PROX],
	पूर्ण,
	अणु
		.dev_name	= "iqs621",
		.sub_devs	= iqs621_sub_devs,
		.num_sub_devs	= ARRAY_SIZE(iqs621_sub_devs),
		.prod_num	= IQS621_PROD_NUM,
		.sw_num		= 0x09,
		.cal_regs	= iqs621_cal_regs,
		.num_cal_regs	= ARRAY_SIZE(iqs621_cal_regs),
		.prox_mask	= BIT(0),
		.hall_mask	= BIT(1),
		.als_mask	= BIT(2),
		.hyst_mask	= BIT(3),
		.temp_mask	= BIT(4),
		.als_flags	= IQS621_ALS_FLAGS,
		.hall_flags	= IQS621_HALL_FLAGS,
		.hyst_shअगरt	= 5,
		.fw_name	= "iqs621.bin",
		.event_regs	= &iqs621_event_regs[IQS62X_UI_PROX],
	पूर्ण,
	अणु
		.dev_name	= "iqs622",
		.sub_devs	= iqs622_sub_devs,
		.num_sub_devs	= ARRAY_SIZE(iqs622_sub_devs),
		.prod_num	= IQS622_PROD_NUM,
		.sw_num		= 0x06,
		.prox_mask	= BIT(0),
		.sar_mask	= BIT(1),
		.hall_mask	= BIT(2),
		.als_mask	= BIT(3),
		.ir_mask	= BIT(4),
		.prox_settings	= IQS622_PROX_SETTINGS_4,
		.als_flags	= IQS622_ALS_FLAGS,
		.hall_flags	= IQS622_HALL_FLAGS,
		.fw_name	= "iqs622.bin",
		.event_regs	= &iqs622_event_regs[IQS62X_UI_PROX],
	पूर्ण,
	अणु
		.dev_name	= "iqs624",
		.sub_devs	= iqs624_sub_devs,
		.num_sub_devs	= ARRAY_SIZE(iqs624_sub_devs),
		.prod_num	= IQS624_PROD_NUM,
		.sw_num		= 0x0B,
		.पूर्णांकerval	= IQS624_INTERVAL_NUM,
		.पूर्णांकerval_भाग	= 3,
		.fw_name	= "iqs624.bin",
		.event_regs	= &iqs624_event_regs[IQS62X_UI_PROX],
	पूर्ण,
	अणु
		.dev_name	= "iqs625",
		.sub_devs	= iqs625_sub_devs,
		.num_sub_devs	= ARRAY_SIZE(iqs625_sub_devs),
		.prod_num	= IQS625_PROD_NUM,
		.sw_num		= 0x0B,
		.पूर्णांकerval	= IQS625_INTERVAL_NUM,
		.पूर्णांकerval_भाग	= 10,
		.fw_name	= "iqs625.bin",
		.event_regs	= &iqs625_event_regs[IQS62X_UI_PROX],
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config iqs62x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = IQS62X_MAX_REG,
पूर्ण;

अटल पूर्णांक iqs62x_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा iqs62x_core *iqs62x;
	काष्ठा iqs62x_info info;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, i, j;
	u8 sw_num = 0;
	स्थिर अक्षर *fw_name = शून्य;

	iqs62x = devm_kzalloc(&client->dev, माप(*iqs62x), GFP_KERNEL);
	अगर (!iqs62x)
		वापस -ENOMEM;

	i2c_set_clientdata(client, iqs62x);
	iqs62x->client = client;

	BLOCKING_INIT_NOTIFIER_HEAD(&iqs62x->nh);
	INIT_LIST_HEAD(&iqs62x->fw_blk_head);

	init_completion(&iqs62x->ati_करोne);
	init_completion(&iqs62x->fw_करोne);

	iqs62x->regmap = devm_regmap_init_i2c(client, &iqs62x_regmap_config);
	अगर (IS_ERR(iqs62x->regmap)) अणु
		ret = PTR_ERR(iqs62x->regmap);
		dev_err(&client->dev, "Failed to initialize register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = regmap_raw_पढ़ो(iqs62x->regmap, IQS62X_PROD_NUM, &info,
			      माप(info));
	अगर (ret)
		वापस ret;

	/*
	 * The following sequence validates the device's product and software
	 * numbers. It then determines अगर the device is factory-calibrated by
	 * checking क्रम nonzero values in the device's designated calibration
	 * रेजिस्टरs (अगर applicable). Depending on the device, the असलence of
	 * calibration data indicates a reduced feature set or invalid device.
	 *
	 * For devices given in both calibrated and uncalibrated versions, the
	 * calibrated version (e.g. IQS620AT) appears first in the iqs62x_devs
	 * array. The uncalibrated version (e.g. IQS620A) appears next and has
	 * the same product and software numbers, but no calibration रेजिस्टरs
	 * are specअगरied.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(iqs62x_devs); i++) अणु
		अगर (info.prod_num != iqs62x_devs[i].prod_num)
			जारी;

		iqs62x->dev_desc = &iqs62x_devs[i];

		अगर (info.sw_num < iqs62x->dev_desc->sw_num)
			जारी;

		sw_num = info.sw_num;

		/*
		 * Read each of the device's designated calibration रेजिस्टरs,
		 * अगर any, and निकास from the inner loop early अगर any are equal
		 * to zero (indicating the device is uncalibrated). This could
		 * be acceptable depending on the device (e.g. IQS620A instead
		 * of IQS620AT).
		 */
		क्रम (j = 0; j < iqs62x->dev_desc->num_cal_regs; j++) अणु
			ret = regmap_पढ़ो(iqs62x->regmap,
					  iqs62x->dev_desc->cal_regs[j], &val);
			अगर (ret)
				वापस ret;

			अगर (!val)
				अवरोध;
		पूर्ण

		/*
		 * If the number of nonzero values पढ़ो from the device equals
		 * the number of designated calibration रेजिस्टरs (which could
		 * be zero), निकास from the outer loop early to संकेत that the
		 * device's product and software numbers match a known device,
		 * and the device is calibrated (अगर applicable).
		 */
		अगर (j == iqs62x->dev_desc->num_cal_regs)
			अवरोध;
	पूर्ण

	अगर (!iqs62x->dev_desc) अणु
		dev_err(&client->dev, "Unrecognized product number: 0x%02X\n",
			info.prod_num);
		वापस -EINVAL;
	पूर्ण

	अगर (!sw_num) अणु
		dev_err(&client->dev, "Unrecognized software number: 0x%02X\n",
			info.sw_num);
		वापस -EINVAL;
	पूर्ण

	अगर (i == ARRAY_SIZE(iqs62x_devs)) अणु
		dev_err(&client->dev, "Uncalibrated device\n");
		वापस -ENODATA;
	पूर्ण

	device_property_पढ़ो_string(&client->dev, "firmware-name", &fw_name);

	ret = request_firmware_noरुको(THIS_MODULE, FW_ACTION_HOTPLUG,
				      fw_name ? : iqs62x->dev_desc->fw_name,
				      &client->dev, GFP_KERNEL, iqs62x,
				      iqs62x_firmware_load);
	अगर (ret)
		dev_err(&client->dev, "Failed to request firmware: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक iqs62x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iqs62x_core *iqs62x = i2c_get_clientdata(client);

	रुको_क्रम_completion(&iqs62x->fw_करोne);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused iqs62x_suspend(काष्ठा device *dev)
अणु
	काष्ठा iqs62x_core *iqs62x = dev_get_drvdata(dev);
	पूर्णांक ret;

	रुको_क्रम_completion(&iqs62x->fw_करोne);

	/*
	 * As per the datasheet, स्वतःmatic mode चयनing must be disabled
	 * beक्रमe the device is placed in or taken out of halt mode.
	 */
	ret = regmap_update_bits(iqs62x->regmap, IQS62X_PWR_SETTINGS,
				 IQS62X_PWR_SETTINGS_DIS_AUTO, 0xFF);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(iqs62x->regmap, IQS62X_PWR_SETTINGS,
				  IQS62X_PWR_SETTINGS_PWR_MODE_MASK,
				  IQS62X_PWR_SETTINGS_PWR_MODE_HALT);
पूर्ण

अटल पूर्णांक __maybe_unused iqs62x_resume(काष्ठा device *dev)
अणु
	काष्ठा iqs62x_core *iqs62x = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(iqs62x->regmap, IQS62X_PWR_SETTINGS,
				 IQS62X_PWR_SETTINGS_PWR_MODE_MASK,
				 IQS62X_PWR_SETTINGS_PWR_MODE_NORM);
	अगर (ret)
		वापस ret;

	वापस regmap_update_bits(iqs62x->regmap, IQS62X_PWR_SETTINGS,
				  IQS62X_PWR_SETTINGS_DIS_AUTO, 0);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(iqs62x_pm, iqs62x_suspend, iqs62x_resume);

अटल स्थिर काष्ठा of_device_id iqs62x_of_match[] = अणु
	अणु .compatible = "azoteq,iqs620a" पूर्ण,
	अणु .compatible = "azoteq,iqs621" पूर्ण,
	अणु .compatible = "azoteq,iqs622" पूर्ण,
	अणु .compatible = "azoteq,iqs624" पूर्ण,
	अणु .compatible = "azoteq,iqs625" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, iqs62x_of_match);

अटल काष्ठा i2c_driver iqs62x_i2c_driver = अणु
	.driver = अणु
		.name = "iqs62x",
		.of_match_table = iqs62x_of_match,
		.pm = &iqs62x_pm,
	पूर्ण,
	.probe_new = iqs62x_probe,
	.हटाओ = iqs62x_हटाओ,
पूर्ण;
module_i2c_driver(iqs62x_i2c_driver);

MODULE_AUTHOR("Jeff LaBundy <jeff@labundy.com>");
MODULE_DESCRIPTION("Azoteq IQS620A/621/622/624/625 Multi-Function Sensors");
MODULE_LICENSE("GPL");
