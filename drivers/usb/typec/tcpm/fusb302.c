<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2016-2017 Google, Inc
 *
 * Fairchild FUSB302 Type-C Chip Driver
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/extcon.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/typec.h>
#समावेश <linux/usb/tcpm.h>
#समावेश <linux/usb/pd.h>
#समावेश <linux/workqueue.h>

#समावेश "fusb302_reg.h"

/*
 * When the device is SNK, BC_LVL पूर्णांकerrupt is used to monitor cc pins
 * क्रम the current capability offered by the SRC. As FUSB302 chip fires
 * the BC_LVL पूर्णांकerrupt on PD संकेतings, cc lvl should be handled after
 * a delay to aव्योम measuring on PD activities. The delay is slightly
 * दीर्घer than PD_T_PD_DEBPUNCE (10-20ms).
 */
#घोषणा T_BC_LVL_DEBOUNCE_DELAY_MS 30

क्रमागत toggling_mode अणु
	TOGGLING_MODE_OFF,
	TOGGLING_MODE_DRP,
	TOGGLING_MODE_SNK,
	TOGGLING_MODE_SRC,
पूर्ण;

क्रमागत src_current_status अणु
	SRC_CURRENT_DEFAULT,
	SRC_CURRENT_MEDIUM,
	SRC_CURRENT_HIGH,
पूर्ण;

अटल स्थिर u8 ra_mda_value[] = अणु
	[SRC_CURRENT_DEFAULT] = 4,	/* 210mV */
	[SRC_CURRENT_MEDIUM] = 9,	/* 420mV */
	[SRC_CURRENT_HIGH] = 18,	/* 798mV */
पूर्ण;

अटल स्थिर u8 rd_mda_value[] = अणु
	[SRC_CURRENT_DEFAULT] = 38,	/* 1638mV */
	[SRC_CURRENT_MEDIUM] = 38,	/* 1638mV */
	[SRC_CURRENT_HIGH] = 61,	/* 2604mV */
पूर्ण;

#घोषणा LOG_BUFFER_ENTRIES	1024
#घोषणा LOG_BUFFER_ENTRY_SIZE	128

काष्ठा fusb302_chip अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c_client;
	काष्ठा tcpm_port *tcpm_port;
	काष्ठा tcpc_dev tcpc_dev;

	काष्ठा regulator *vbus;

	spinlock_t irq_lock;
	काष्ठा work_काष्ठा irq_work;
	bool irq_suspended;
	bool irq_जबतक_suspended;
	काष्ठा gpio_desc *gpio_पूर्णांक_n;
	पूर्णांक gpio_पूर्णांक_n_irq;
	काष्ठा extcon_dev *extcon;

	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा delayed_work bc_lvl_handler;

	/* lock क्रम sharing chip states */
	काष्ठा mutex lock;

	/* chip status */
	क्रमागत toggling_mode toggling_mode;
	क्रमागत src_current_status src_current_status;
	bool पूर्णांकr_togकरोne;
	bool पूर्णांकr_bc_lvl;
	bool पूर्णांकr_comp_chng;

	/* port status */
	bool vconn_on;
	bool vbus_on;
	bool अक्षरge_on;
	bool vbus_present;
	क्रमागत typec_cc_polarity cc_polarity;
	क्रमागत typec_cc_status cc1;
	क्रमागत typec_cc_status cc2;
	u32 snk_pकरो[PDO_MAX_OBJECTS];

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dentry;
	/* lock क्रम log buffer access */
	काष्ठा mutex logbuffer_lock;
	पूर्णांक logbuffer_head;
	पूर्णांक logbuffer_tail;
	u8 *logbuffer[LOG_BUFFER_ENTRIES];
#पूर्ण_अगर
पूर्ण;

/*
 * Logging
 */

#अगर_घोषित CONFIG_DEBUG_FS
अटल bool fusb302_log_full(काष्ठा fusb302_chip *chip)
अणु
	वापस chip->logbuffer_tail ==
		(chip->logbuffer_head + 1) % LOG_BUFFER_ENTRIES;
पूर्ण

__म_लिखो(2, 0)
अटल व्योम _fusb302_log(काष्ठा fusb302_chip *chip, स्थिर अक्षर *fmt,
			 बहु_सूची args)
अणु
	अक्षर पंचांगpbuffer[LOG_BUFFER_ENTRY_SIZE];
	u64 ts_nsec = local_घड़ी();
	अचिन्हित दीर्घ rem_nsec;

	अगर (!chip->logbuffer[chip->logbuffer_head]) अणु
		chip->logbuffer[chip->logbuffer_head] =
				kzalloc(LOG_BUFFER_ENTRY_SIZE, GFP_KERNEL);
		अगर (!chip->logbuffer[chip->logbuffer_head])
			वापस;
	पूर्ण

	vsnम_लिखो(पंचांगpbuffer, माप(पंचांगpbuffer), fmt, args);

	mutex_lock(&chip->logbuffer_lock);

	अगर (fusb302_log_full(chip)) अणु
		chip->logbuffer_head = max(chip->logbuffer_head - 1, 0);
		strlcpy(पंचांगpbuffer, "overflow", माप(पंचांगpbuffer));
	पूर्ण

	अगर (chip->logbuffer_head < 0 ||
	    chip->logbuffer_head >= LOG_BUFFER_ENTRIES) अणु
		dev_warn(chip->dev,
			 "Bad log buffer index %d\n", chip->logbuffer_head);
		जाओ पात;
	पूर्ण

	अगर (!chip->logbuffer[chip->logbuffer_head]) अणु
		dev_warn(chip->dev,
			 "Log buffer index %d is NULL\n", chip->logbuffer_head);
		जाओ पात;
	पूर्ण

	rem_nsec = करो_भाग(ts_nsec, 1000000000);
	scnम_लिखो(chip->logbuffer[chip->logbuffer_head],
		  LOG_BUFFER_ENTRY_SIZE, "[%5lu.%06lu] %s",
		  (अचिन्हित दीर्घ)ts_nsec, rem_nsec / 1000,
		  पंचांगpbuffer);
	chip->logbuffer_head = (chip->logbuffer_head + 1) % LOG_BUFFER_ENTRIES;

पात:
	mutex_unlock(&chip->logbuffer_lock);
पूर्ण

__म_लिखो(2, 3)
अटल व्योम fusb302_log(काष्ठा fusb302_chip *chip, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	_fusb302_log(chip, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

अटल पूर्णांक fusb302_debug_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा fusb302_chip *chip = (काष्ठा fusb302_chip *)s->निजी;
	पूर्णांक tail;

	mutex_lock(&chip->logbuffer_lock);
	tail = chip->logbuffer_tail;
	जबतक (tail != chip->logbuffer_head) अणु
		seq_म_लिखो(s, "%s\n", chip->logbuffer[tail]);
		tail = (tail + 1) % LOG_BUFFER_ENTRIES;
	पूर्ण
	अगर (!seq_has_overflowed(s))
		chip->logbuffer_tail = tail;
	mutex_unlock(&chip->logbuffer_lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(fusb302_debug);

अटल व्योम fusb302_debugfs_init(काष्ठा fusb302_chip *chip)
अणु
	अक्षर name[NAME_MAX];

	mutex_init(&chip->logbuffer_lock);
	snम_लिखो(name, NAME_MAX, "fusb302-%s", dev_name(chip->dev));
	chip->dentry = debugfs_create_dir(name, usb_debug_root);
	debugfs_create_file("log", S_IFREG | 0444, chip->dentry, chip,
			    &fusb302_debug_fops);
पूर्ण

अटल व्योम fusb302_debugfs_निकास(काष्ठा fusb302_chip *chip)
अणु
	debugfs_हटाओ(chip->dentry);
पूर्ण

#अन्यथा

अटल व्योम fusb302_log(स्थिर काष्ठा fusb302_chip *chip,
			स्थिर अक्षर *fmt, ...) अणु पूर्ण
अटल व्योम fusb302_debugfs_init(स्थिर काष्ठा fusb302_chip *chip) अणु पूर्ण
अटल व्योम fusb302_debugfs_निकास(स्थिर काष्ठा fusb302_chip *chip) अणु पूर्ण

#पूर्ण_अगर

अटल पूर्णांक fusb302_i2c_ग_लिखो(काष्ठा fusb302_chip *chip,
			     u8 address, u8 data)
अणु
	पूर्णांक ret = 0;

	ret = i2c_smbus_ग_लिखो_byte_data(chip->i2c_client, address, data);
	अगर (ret < 0)
		fusb302_log(chip, "cannot write 0x%02x to 0x%02x, ret=%d",
			    data, address, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_i2c_block_ग_लिखो(काष्ठा fusb302_chip *chip, u8 address,
				   u8 length, स्थिर u8 *data)
अणु
	पूर्णांक ret = 0;

	अगर (length <= 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_i2c_block_data(chip->i2c_client, address,
					     length, data);
	अगर (ret < 0)
		fusb302_log(chip, "cannot block write 0x%02x, len=%d, ret=%d",
			    address, length, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_i2c_पढ़ो(काष्ठा fusb302_chip *chip,
			    u8 address, u8 *data)
अणु
	पूर्णांक ret = 0;

	ret = i2c_smbus_पढ़ो_byte_data(chip->i2c_client, address);
	*data = (u8)ret;
	अगर (ret < 0)
		fusb302_log(chip, "cannot read %02x, ret=%d", address, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_i2c_block_पढ़ो(काष्ठा fusb302_chip *chip, u8 address,
				  u8 length, u8 *data)
अणु
	पूर्णांक ret = 0;

	अगर (length <= 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(chip->i2c_client, address,
					    length, data);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot block read 0x%02x, len=%d, ret=%d",
			    address, length, ret);
		जाओ करोne;
	पूर्ण
	अगर (ret != length) अणु
		fusb302_log(chip, "only read %d/%d bytes from 0x%02x",
			    ret, length, address);
		ret = -EIO;
	पूर्ण

करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_i2c_mask_ग_लिखो(काष्ठा fusb302_chip *chip, u8 address,
				  u8 mask, u8 value)
अणु
	पूर्णांक ret = 0;
	u8 data;

	ret = fusb302_i2c_पढ़ो(chip, address, &data);
	अगर (ret < 0)
		वापस ret;
	data &= ~mask;
	data |= value;
	ret = fusb302_i2c_ग_लिखो(chip, address, data);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_i2c_set_bits(काष्ठा fusb302_chip *chip, u8 address,
				u8 set_bits)
अणु
	वापस fusb302_i2c_mask_ग_लिखो(chip, address, 0x00, set_bits);
पूर्ण

अटल पूर्णांक fusb302_i2c_clear_bits(काष्ठा fusb302_chip *chip, u8 address,
				  u8 clear_bits)
अणु
	वापस fusb302_i2c_mask_ग_लिखो(chip, address, clear_bits, 0x00);
पूर्ण

अटल पूर्णांक fusb302_sw_reset(काष्ठा fusb302_chip *chip)
अणु
	पूर्णांक ret = 0;

	ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_RESET,
				FUSB_REG_RESET_SW_RESET);
	अगर (ret < 0)
		fusb302_log(chip, "cannot sw reset the chip, ret=%d", ret);
	अन्यथा
		fusb302_log(chip, "sw reset");

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_enable_tx_स्वतः_retries(काष्ठा fusb302_chip *chip, u8 retry_count)
अणु
	पूर्णांक ret = 0;

	ret = fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL3, retry_count |
				   FUSB_REG_CONTROL3_AUTO_RETRY);

	वापस ret;
पूर्ण

/*
 * initialize पूर्णांकerrupt on the chip
 * - unmasked पूर्णांकerrupt: VBUS_OK
 */
अटल पूर्णांक fusb302_init_पूर्णांकerrupt(काष्ठा fusb302_chip *chip)
अणु
	पूर्णांक ret = 0;

	ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_MASK,
				0xFF & ~FUSB_REG_MASK_VBUSOK);
	अगर (ret < 0)
		वापस ret;
	ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_MASKA, 0xFF);
	अगर (ret < 0)
		वापस ret;
	ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_MASKB, 0xFF);
	अगर (ret < 0)
		वापस ret;
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_CONTROL0,
				     FUSB_REG_CONTROL0_INT_MASK);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_set_घातer_mode(काष्ठा fusb302_chip *chip, u8 घातer_mode)
अणु
	पूर्णांक ret = 0;

	ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_POWER, घातer_mode);

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_init(काष्ठा tcpc_dev *dev)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);
	पूर्णांक ret = 0;
	u8 data;

	ret = fusb302_sw_reset(chip);
	अगर (ret < 0)
		वापस ret;
	ret = fusb302_enable_tx_स्वतः_retries(chip, FUSB_REG_CONTROL3_N_RETRIES_3);
	अगर (ret < 0)
		वापस ret;
	ret = fusb302_init_पूर्णांकerrupt(chip);
	अगर (ret < 0)
		वापस ret;
	ret = fusb302_set_घातer_mode(chip, FUSB_REG_POWER_PWR_ALL);
	अगर (ret < 0)
		वापस ret;
	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_STATUS0, &data);
	अगर (ret < 0)
		वापस ret;
	chip->vbus_present = !!(data & FUSB_REG_STATUS0_VBUSOK);
	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_DEVICE_ID, &data);
	अगर (ret < 0)
		वापस ret;
	fusb302_log(chip, "fusb302 device ID: 0x%02x", data);

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_get_vbus(काष्ठा tcpc_dev *dev)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);
	पूर्णांक ret = 0;

	mutex_lock(&chip->lock);
	ret = chip->vbus_present ? 1 : 0;
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_get_current_limit(काष्ठा tcpc_dev *dev)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);
	पूर्णांक current_limit = 0;
	अचिन्हित दीर्घ समयout;

	अगर (!chip->extcon)
		वापस 0;

	/*
	 * USB2 Charger detection may still be in progress when we get here,
	 * this can take upto 600ms, रुको 800ms max.
	 */
	समयout = jअगरfies + msecs_to_jअगरfies(800);
	करो अणु
		अगर (extcon_get_state(chip->extcon, EXTCON_CHG_USB_SDP) == 1)
			current_limit = 500;

		अगर (extcon_get_state(chip->extcon, EXTCON_CHG_USB_CDP) == 1 ||
		    extcon_get_state(chip->extcon, EXTCON_CHG_USB_ACA) == 1)
			current_limit = 1500;

		अगर (extcon_get_state(chip->extcon, EXTCON_CHG_USB_DCP) == 1)
			current_limit = 2000;

		msleep(50);
	पूर्ण जबतक (current_limit == 0 && समय_beक्रमe(jअगरfies, समयout));

	वापस current_limit;
पूर्ण

अटल पूर्णांक fusb302_set_src_current(काष्ठा fusb302_chip *chip,
				   क्रमागत src_current_status status)
अणु
	पूर्णांक ret = 0;

	chip->src_current_status = status;
	चयन (status) अणु
	हाल SRC_CURRENT_DEFAULT:
		ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_CONTROL0,
					     FUSB_REG_CONTROL0_HOST_CUR_MASK,
					     FUSB_REG_CONTROL0_HOST_CUR_DEF);
		अवरोध;
	हाल SRC_CURRENT_MEDIUM:
		ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_CONTROL0,
					     FUSB_REG_CONTROL0_HOST_CUR_MASK,
					     FUSB_REG_CONTROL0_HOST_CUR_MED);
		अवरोध;
	हाल SRC_CURRENT_HIGH:
		ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_CONTROL0,
					     FUSB_REG_CONTROL0_HOST_CUR_MASK,
					     FUSB_REG_CONTROL0_HOST_CUR_HIGH);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_set_toggling(काष्ठा fusb302_chip *chip,
				क्रमागत toggling_mode mode)
अणु
	पूर्णांक ret = 0;

	/* first disable toggling */
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_CONTROL2,
				     FUSB_REG_CONTROL2_TOGGLE);
	अगर (ret < 0)
		वापस ret;
	/* mask पूर्णांकerrupts क्रम SRC or SNK */
	ret = fusb302_i2c_set_bits(chip, FUSB_REG_MASK,
				   FUSB_REG_MASK_BC_LVL |
				   FUSB_REG_MASK_COMP_CHNG);
	अगर (ret < 0)
		वापस ret;
	chip->पूर्णांकr_bc_lvl = false;
	chip->पूर्णांकr_comp_chng = false;
	/* configure toggling mode: none/snk/src/drp */
	चयन (mode) अणु
	हाल TOGGLING_MODE_OFF:
		ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_NONE);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल TOGGLING_MODE_SNK:
		ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_UFP);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल TOGGLING_MODE_SRC:
		ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_DFP);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल TOGGLING_MODE_DRP:
		ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_DRP);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (mode == TOGGLING_MODE_OFF) अणु
		/* mask TOGDONE पूर्णांकerrupt */
		ret = fusb302_i2c_set_bits(chip, FUSB_REG_MASKA,
					   FUSB_REG_MASKA_TOGDONE);
		अगर (ret < 0)
			वापस ret;
		chip->पूर्णांकr_togकरोne = false;
	पूर्ण अन्यथा अणु
		/* Datasheet says vconn MUST be off when toggling */
		WARN(chip->vconn_on, "Vconn is on during toggle start");
		/* unmask TOGDONE पूर्णांकerrupt */
		ret = fusb302_i2c_clear_bits(chip, FUSB_REG_MASKA,
					     FUSB_REG_MASKA_TOGDONE);
		अगर (ret < 0)
			वापस ret;
		chip->पूर्णांकr_togकरोne = true;
		/* start toggling */
		ret = fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL2,
					   FUSB_REG_CONTROL2_TOGGLE);
		अगर (ret < 0)
			वापस ret;
		/* during toggling, consider cc as Open */
		chip->cc1 = TYPEC_CC_OPEN;
		chip->cc2 = TYPEC_CC_OPEN;
	पूर्ण
	chip->toggling_mode = mode;

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर typec_cc_status_name[] = अणु
	[TYPEC_CC_OPEN]		= "Open",
	[TYPEC_CC_RA]		= "Ra",
	[TYPEC_CC_RD]		= "Rd",
	[TYPEC_CC_RP_DEF]	= "Rp-def",
	[TYPEC_CC_RP_1_5]	= "Rp-1.5",
	[TYPEC_CC_RP_3_0]	= "Rp-3.0",
पूर्ण;

अटल स्थिर क्रमागत src_current_status cc_src_current[] = अणु
	[TYPEC_CC_OPEN]		= SRC_CURRENT_DEFAULT,
	[TYPEC_CC_RA]		= SRC_CURRENT_DEFAULT,
	[TYPEC_CC_RD]		= SRC_CURRENT_DEFAULT,
	[TYPEC_CC_RP_DEF]	= SRC_CURRENT_DEFAULT,
	[TYPEC_CC_RP_1_5]	= SRC_CURRENT_MEDIUM,
	[TYPEC_CC_RP_3_0]	= SRC_CURRENT_HIGH,
पूर्ण;

अटल पूर्णांक tcpm_set_cc(काष्ठा tcpc_dev *dev, क्रमागत typec_cc_status cc)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);
	u8 चयनes0_mask = FUSB_REG_SWITCHES0_CC1_PU_EN |
			    FUSB_REG_SWITCHES0_CC2_PU_EN |
			    FUSB_REG_SWITCHES0_CC1_PD_EN |
			    FUSB_REG_SWITCHES0_CC2_PD_EN;
	u8 rd_mda, चयनes0_data = 0x00;
	पूर्णांक ret = 0;

	mutex_lock(&chip->lock);
	चयन (cc) अणु
	हाल TYPEC_CC_OPEN:
		अवरोध;
	हाल TYPEC_CC_RD:
		चयनes0_data |= FUSB_REG_SWITCHES0_CC1_PD_EN |
				  FUSB_REG_SWITCHES0_CC2_PD_EN;
		अवरोध;
	हाल TYPEC_CC_RP_DEF:
	हाल TYPEC_CC_RP_1_5:
	हाल TYPEC_CC_RP_3_0:
		चयनes0_data |= (chip->cc_polarity == TYPEC_POLARITY_CC1) ?
				  FUSB_REG_SWITCHES0_CC1_PU_EN :
				  FUSB_REG_SWITCHES0_CC2_PU_EN;
		अवरोध;
	शेष:
		fusb302_log(chip, "unsupported cc value %s",
			    typec_cc_status_name[cc]);
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	fusb302_log(chip, "cc := %s", typec_cc_status_name[cc]);

	ret = fusb302_set_toggling(chip, TOGGLING_MODE_OFF);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot set toggling mode, ret=%d", ret);
		जाओ करोne;
	पूर्ण

	ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_SWITCHES0,
				     चयनes0_mask, चयनes0_data);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot set pull-up/-down, ret = %d", ret);
		जाओ करोne;
	पूर्ण
	/* reset the cc status */
	chip->cc1 = TYPEC_CC_OPEN;
	chip->cc2 = TYPEC_CC_OPEN;

	/* adjust current क्रम SRC */
	ret = fusb302_set_src_current(chip, cc_src_current[cc]);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot set src current %s, ret=%d",
			    typec_cc_status_name[cc], ret);
		जाओ करोne;
	पूर्ण

	/* enable/disable पूर्णांकerrupts, BC_LVL क्रम SNK and COMP_CHNG क्रम SRC */
	चयन (cc) अणु
	हाल TYPEC_CC_RP_DEF:
	हाल TYPEC_CC_RP_1_5:
	हाल TYPEC_CC_RP_3_0:
		rd_mda = rd_mda_value[cc_src_current[cc]];
		ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_MEASURE, rd_mda);
		अगर (ret < 0) अणु
			fusb302_log(chip,
				    "cannot set SRC measure value, ret=%d",
				    ret);
			जाओ करोne;
		पूर्ण
		ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_MASK,
					     FUSB_REG_MASK_BC_LVL |
					     FUSB_REG_MASK_COMP_CHNG,
					     FUSB_REG_MASK_COMP_CHNG);
		अगर (ret < 0) अणु
			fusb302_log(chip, "cannot set SRC interrupt, ret=%d",
				    ret);
			जाओ करोne;
		पूर्ण
		chip->पूर्णांकr_comp_chng = true;
		अवरोध;
	हाल TYPEC_CC_RD:
		ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_MASK,
					     FUSB_REG_MASK_BC_LVL |
					     FUSB_REG_MASK_COMP_CHNG,
					     FUSB_REG_MASK_BC_LVL);
		अगर (ret < 0) अणु
			fusb302_log(chip, "cannot set SRC interrupt, ret=%d",
				    ret);
			जाओ करोne;
		पूर्ण
		chip->पूर्णांकr_bc_lvl = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
करोne:
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_get_cc(काष्ठा tcpc_dev *dev, क्रमागत typec_cc_status *cc1,
		       क्रमागत typec_cc_status *cc2)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);

	mutex_lock(&chip->lock);
	*cc1 = chip->cc1;
	*cc2 = chip->cc2;
	fusb302_log(chip, "cc1=%s, cc2=%s", typec_cc_status_name[*cc1],
		    typec_cc_status_name[*cc2]);
	mutex_unlock(&chip->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_set_polarity(काष्ठा tcpc_dev *dev,
			     क्रमागत typec_cc_polarity polarity)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tcpm_set_vconn(काष्ठा tcpc_dev *dev, bool on)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);
	पूर्णांक ret = 0;
	u8 चयनes0_data = 0x00;
	u8 चयनes0_mask = FUSB_REG_SWITCHES0_VCONN_CC1 |
			    FUSB_REG_SWITCHES0_VCONN_CC2;

	mutex_lock(&chip->lock);
	अगर (chip->vconn_on == on) अणु
		fusb302_log(chip, "vconn is already %s", on ? "On" : "Off");
		जाओ करोne;
	पूर्ण
	अगर (on) अणु
		चयनes0_data = (chip->cc_polarity == TYPEC_POLARITY_CC1) ?
				 FUSB_REG_SWITCHES0_VCONN_CC2 :
				 FUSB_REG_SWITCHES0_VCONN_CC1;
	पूर्ण
	ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_SWITCHES0,
				     चयनes0_mask, चयनes0_data);
	अगर (ret < 0)
		जाओ करोne;
	chip->vconn_on = on;
	fusb302_log(chip, "vconn := %s", on ? "On" : "Off");
करोne:
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_set_vbus(काष्ठा tcpc_dev *dev, bool on, bool अक्षरge)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);
	पूर्णांक ret = 0;

	mutex_lock(&chip->lock);
	अगर (chip->vbus_on == on) अणु
		fusb302_log(chip, "vbus is already %s", on ? "On" : "Off");
	पूर्ण अन्यथा अणु
		अगर (on)
			ret = regulator_enable(chip->vbus);
		अन्यथा
			ret = regulator_disable(chip->vbus);
		अगर (ret < 0) अणु
			fusb302_log(chip, "cannot %s vbus regulator, ret=%d",
				    on ? "enable" : "disable", ret);
			जाओ करोne;
		पूर्ण
		chip->vbus_on = on;
		fusb302_log(chip, "vbus := %s", on ? "On" : "Off");
	पूर्ण
	अगर (chip->अक्षरge_on == अक्षरge)
		fusb302_log(chip, "charge is already %s",
			    अक्षरge ? "On" : "Off");
	अन्यथा
		chip->अक्षरge_on = अक्षरge;

करोne:
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_pd_tx_flush(काष्ठा fusb302_chip *chip)
अणु
	वापस fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL0,
				    FUSB_REG_CONTROL0_TX_FLUSH);
पूर्ण

अटल पूर्णांक fusb302_pd_rx_flush(काष्ठा fusb302_chip *chip)
अणु
	वापस fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL1,
				    FUSB_REG_CONTROL1_RX_FLUSH);
पूर्ण

अटल पूर्णांक fusb302_pd_set_स्वतः_goodcrc(काष्ठा fusb302_chip *chip, bool on)
अणु
	अगर (on)
		वापस fusb302_i2c_set_bits(chip, FUSB_REG_SWITCHES1,
					    FUSB_REG_SWITCHES1_AUTO_GCRC);
	वापस fusb302_i2c_clear_bits(chip, FUSB_REG_SWITCHES1,
					    FUSB_REG_SWITCHES1_AUTO_GCRC);
पूर्ण

अटल पूर्णांक fusb302_pd_set_पूर्णांकerrupts(काष्ठा fusb302_chip *chip, bool on)
अणु
	पूर्णांक ret = 0;
	u8 mask_पूर्णांकerrupts = FUSB_REG_MASK_COLLISION;
	u8 maska_पूर्णांकerrupts = FUSB_REG_MASKA_RETRYFAIL |
			      FUSB_REG_MASKA_HARDSENT |
			      FUSB_REG_MASKA_TX_SUCCESS |
			      FUSB_REG_MASKA_HARDRESET;
	u8 maskb_पूर्णांकerrupts = FUSB_REG_MASKB_GCRCSENT;

	ret = on ?
		fusb302_i2c_clear_bits(chip, FUSB_REG_MASK, mask_पूर्णांकerrupts) :
		fusb302_i2c_set_bits(chip, FUSB_REG_MASK, mask_पूर्णांकerrupts);
	अगर (ret < 0)
		वापस ret;
	ret = on ?
		fusb302_i2c_clear_bits(chip, FUSB_REG_MASKA, maska_पूर्णांकerrupts) :
		fusb302_i2c_set_bits(chip, FUSB_REG_MASKA, maska_पूर्णांकerrupts);
	अगर (ret < 0)
		वापस ret;
	ret = on ?
		fusb302_i2c_clear_bits(chip, FUSB_REG_MASKB, maskb_पूर्णांकerrupts) :
		fusb302_i2c_set_bits(chip, FUSB_REG_MASKB, maskb_पूर्णांकerrupts);
	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_set_pd_rx(काष्ठा tcpc_dev *dev, bool on)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);
	पूर्णांक ret = 0;

	mutex_lock(&chip->lock);
	ret = fusb302_pd_rx_flush(chip);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot flush pd rx buffer, ret=%d", ret);
		जाओ करोne;
	पूर्ण
	ret = fusb302_pd_tx_flush(chip);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot flush pd tx buffer, ret=%d", ret);
		जाओ करोne;
	पूर्ण
	ret = fusb302_pd_set_स्वतः_goodcrc(chip, on);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot turn %s auto GCRC, ret=%d",
			    on ? "on" : "off", ret);
		जाओ करोne;
	पूर्ण
	ret = fusb302_pd_set_पूर्णांकerrupts(chip, on);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot turn %s pd interrupts, ret=%d",
			    on ? "on" : "off", ret);
		जाओ करोne;
	पूर्ण
	fusb302_log(chip, "pd := %s", on ? "on" : "off");
करोne:
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर typec_role_name[] = अणु
	[TYPEC_SINK]		= "Sink",
	[TYPEC_SOURCE]		= "Source",
पूर्ण;

अटल स्थिर अक्षर * स्थिर typec_data_role_name[] = अणु
	[TYPEC_DEVICE]		= "Device",
	[TYPEC_HOST]		= "Host",
पूर्ण;

अटल पूर्णांक tcpm_set_roles(काष्ठा tcpc_dev *dev, bool attached,
			  क्रमागत typec_role pwr, क्रमागत typec_data_role data)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);
	पूर्णांक ret = 0;
	u8 चयनes1_mask = FUSB_REG_SWITCHES1_POWERROLE |
			    FUSB_REG_SWITCHES1_DATAROLE;
	u8 चयनes1_data = 0x00;

	mutex_lock(&chip->lock);
	अगर (pwr == TYPEC_SOURCE)
		चयनes1_data |= FUSB_REG_SWITCHES1_POWERROLE;
	अगर (data == TYPEC_HOST)
		चयनes1_data |= FUSB_REG_SWITCHES1_DATAROLE;
	ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_SWITCHES1,
				     चयनes1_mask, चयनes1_data);
	अगर (ret < 0) अणु
		fusb302_log(chip, "unable to set pd header %s, %s, ret=%d",
			    typec_role_name[pwr], typec_data_role_name[data],
			    ret);
		जाओ करोne;
	पूर्ण
	fusb302_log(chip, "pd header := %s, %s", typec_role_name[pwr],
		    typec_data_role_name[data]);
करोne:
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक tcpm_start_toggling(काष्ठा tcpc_dev *dev,
			       क्रमागत typec_port_type port_type,
			       क्रमागत typec_cc_status cc)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);
	क्रमागत toggling_mode mode = TOGGLING_MODE_OFF;
	पूर्णांक ret = 0;

	चयन (port_type) अणु
	हाल TYPEC_PORT_SRC:
		mode = TOGGLING_MODE_SRC;
		अवरोध;
	हाल TYPEC_PORT_SNK:
		mode = TOGGLING_MODE_SNK;
		अवरोध;
	हाल TYPEC_PORT_DRP:
		mode = TOGGLING_MODE_DRP;
		अवरोध;
	पूर्ण

	mutex_lock(&chip->lock);
	ret = fusb302_set_src_current(chip, cc_src_current[cc]);
	अगर (ret < 0) अणु
		fusb302_log(chip, "unable to set src current %s, ret=%d",
			    typec_cc_status_name[cc], ret);
		जाओ करोne;
	पूर्ण
	ret = fusb302_set_toggling(chip, mode);
	अगर (ret < 0) अणु
		fusb302_log(chip,
			    "unable to start drp toggling, ret=%d", ret);
		जाओ करोne;
	पूर्ण
	fusb302_log(chip, "start drp toggling");
करोne:
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_pd_send_message(काष्ठा fusb302_chip *chip,
				   स्थिर काष्ठा pd_message *msg)
अणु
	पूर्णांक ret = 0;
	u8 buf[40];
	u8 pos = 0;
	पूर्णांक len;

	/* SOP tokens */
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC2;

	len = pd_header_cnt_le(msg->header) * 4;
	/* plug 2 क्रम header */
	len += 2;
	अगर (len > 0x1F) अणु
		fusb302_log(chip,
			    "PD message too long %d (incl. header)", len);
		वापस -EINVAL;
	पूर्ण
	/* packsym tells the FUSB302 chip that the next X bytes are payload */
	buf[pos++] = FUSB302_TKN_PACKSYM | (len & 0x1F);
	स_नकल(&buf[pos], &msg->header, माप(msg->header));
	pos += माप(msg->header);

	len -= 2;
	स_नकल(&buf[pos], msg->payload, len);
	pos += len;

	/* CRC */
	buf[pos++] = FUSB302_TKN_JAMCRC;
	/* EOP */
	buf[pos++] = FUSB302_TKN_EOP;
	/* turn tx off after sending message */
	buf[pos++] = FUSB302_TKN_TXOFF;
	/* start transmission */
	buf[pos++] = FUSB302_TKN_TXON;

	ret = fusb302_i2c_block_ग_लिखो(chip, FUSB_REG_FIFOS, pos, buf);
	अगर (ret < 0)
		वापस ret;
	fusb302_log(chip, "sending PD message header: %x", msg->header);
	fusb302_log(chip, "sending PD message len: %d", len);

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_pd_send_hardreset(काष्ठा fusb302_chip *chip)
अणु
	वापस fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL3,
				    FUSB_REG_CONTROL3_SEND_HARDRESET);
पूर्ण

अटल स्थिर अक्षर * स्थिर transmit_type_name[] = अणु
	[TCPC_TX_SOP]			= "SOP",
	[TCPC_TX_SOP_PRIME]		= "SOP'",
	[TCPC_TX_SOP_PRIME_PRIME]	= "SOP''",
	[TCPC_TX_SOP_DEBUG_PRIME]	= "DEBUG'",
	[TCPC_TX_SOP_DEBUG_PRIME_PRIME]	= "DEBUG''",
	[TCPC_TX_HARD_RESET]		= "HARD_RESET",
	[TCPC_TX_CABLE_RESET]		= "CABLE_RESET",
	[TCPC_TX_BIST_MODE_2]		= "BIST_MODE_2",
पूर्ण;

अटल पूर्णांक tcpm_pd_transmit(काष्ठा tcpc_dev *dev, क्रमागत tcpm_transmit_type type,
			    स्थिर काष्ठा pd_message *msg, अचिन्हित पूर्णांक negotiated_rev)
अणु
	काष्ठा fusb302_chip *chip = container_of(dev, काष्ठा fusb302_chip,
						 tcpc_dev);
	पूर्णांक ret = 0;

	mutex_lock(&chip->lock);
	चयन (type) अणु
	हाल TCPC_TX_SOP:
		/* nRetryCount 3 in P2.0 spec, whereas 2 in PD3.0 spec */
		ret = fusb302_enable_tx_स्वतः_retries(chip, negotiated_rev > PD_REV20 ?
						     FUSB_REG_CONTROL3_N_RETRIES_2 :
						     FUSB_REG_CONTROL3_N_RETRIES_3);
		अगर (ret < 0)
			fusb302_log(chip, "Cannot update retry count ret=%d", ret);

		ret = fusb302_pd_send_message(chip, msg);
		अगर (ret < 0)
			fusb302_log(chip,
				    "cannot send PD message, ret=%d", ret);
		अवरोध;
	हाल TCPC_TX_HARD_RESET:
		ret = fusb302_pd_send_hardreset(chip);
		अगर (ret < 0)
			fusb302_log(chip,
				    "cannot send hardreset, ret=%d", ret);
		अवरोध;
	शेष:
		fusb302_log(chip, "type %s not supported",
			    transmit_type_name[type]);
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल क्रमागत typec_cc_status fusb302_bc_lvl_to_cc(u8 bc_lvl)
अणु
	अगर (bc_lvl == FUSB_REG_STATUS0_BC_LVL_1230_MAX)
		वापस TYPEC_CC_RP_3_0;
	अगर (bc_lvl == FUSB_REG_STATUS0_BC_LVL_600_1230)
		वापस TYPEC_CC_RP_1_5;
	अगर (bc_lvl == FUSB_REG_STATUS0_BC_LVL_200_600)
		वापस TYPEC_CC_RP_DEF;
	वापस TYPEC_CC_OPEN;
पूर्ण

अटल व्योम fusb302_bc_lvl_handler_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fusb302_chip *chip = container_of(work, काष्ठा fusb302_chip,
						 bc_lvl_handler.work);
	पूर्णांक ret = 0;
	u8 status0;
	u8 bc_lvl;
	क्रमागत typec_cc_status cc_status;

	mutex_lock(&chip->lock);
	अगर (!chip->पूर्णांकr_bc_lvl) अणु
		fusb302_log(chip, "BC_LVL interrupt is turned off, abort");
		जाओ करोne;
	पूर्ण
	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_STATUS0, &status0);
	अगर (ret < 0)
		जाओ करोne;
	fusb302_log(chip, "BC_LVL handler, status0=0x%02x", status0);
	अगर (status0 & FUSB_REG_STATUS0_ACTIVITY) अणु
		fusb302_log(chip, "CC activities detected, delay handling");
		mod_delayed_work(chip->wq, &chip->bc_lvl_handler,
				 msecs_to_jअगरfies(T_BC_LVL_DEBOUNCE_DELAY_MS));
		जाओ करोne;
	पूर्ण
	bc_lvl = status0 & FUSB_REG_STATUS0_BC_LVL_MASK;
	cc_status = fusb302_bc_lvl_to_cc(bc_lvl);
	अगर (chip->cc_polarity == TYPEC_POLARITY_CC1) अणु
		अगर (chip->cc1 != cc_status) अणु
			fusb302_log(chip, "cc1: %s -> %s",
				    typec_cc_status_name[chip->cc1],
				    typec_cc_status_name[cc_status]);
			chip->cc1 = cc_status;
			tcpm_cc_change(chip->tcpm_port);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->cc2 != cc_status) अणु
			fusb302_log(chip, "cc2: %s -> %s",
				    typec_cc_status_name[chip->cc2],
				    typec_cc_status_name[cc_status]);
			chip->cc2 = cc_status;
			tcpm_cc_change(chip->tcpm_port);
		पूर्ण
	पूर्ण

करोne:
	mutex_unlock(&chip->lock);
पूर्ण

अटल व्योम init_tcpc_dev(काष्ठा tcpc_dev *fusb302_tcpc_dev)
अणु
	fusb302_tcpc_dev->init = tcpm_init;
	fusb302_tcpc_dev->get_vbus = tcpm_get_vbus;
	fusb302_tcpc_dev->get_current_limit = tcpm_get_current_limit;
	fusb302_tcpc_dev->set_cc = tcpm_set_cc;
	fusb302_tcpc_dev->get_cc = tcpm_get_cc;
	fusb302_tcpc_dev->set_polarity = tcpm_set_polarity;
	fusb302_tcpc_dev->set_vconn = tcpm_set_vconn;
	fusb302_tcpc_dev->set_vbus = tcpm_set_vbus;
	fusb302_tcpc_dev->set_pd_rx = tcpm_set_pd_rx;
	fusb302_tcpc_dev->set_roles = tcpm_set_roles;
	fusb302_tcpc_dev->start_toggling = tcpm_start_toggling;
	fusb302_tcpc_dev->pd_transmit = tcpm_pd_transmit;
पूर्ण

अटल स्थिर अक्षर * स्थिर cc_polarity_name[] = अणु
	[TYPEC_POLARITY_CC1]	= "Polarity_CC1",
	[TYPEC_POLARITY_CC2]	= "Polarity_CC2",
पूर्ण;

अटल पूर्णांक fusb302_set_cc_polarity_and_pull(काष्ठा fusb302_chip *chip,
					    क्रमागत typec_cc_polarity cc_polarity,
					    bool pull_up, bool pull_करोwn)
अणु
	पूर्णांक ret = 0;
	u8 चयनes0_data = 0x00;
	u8 चयनes1_mask = FUSB_REG_SWITCHES1_TXCC1_EN |
			    FUSB_REG_SWITCHES1_TXCC2_EN;
	u8 चयनes1_data = 0x00;

	अगर (pull_करोwn)
		चयनes0_data |= FUSB_REG_SWITCHES0_CC1_PD_EN |
				  FUSB_REG_SWITCHES0_CC2_PD_EN;

	अगर (cc_polarity == TYPEC_POLARITY_CC1) अणु
		चयनes0_data |= FUSB_REG_SWITCHES0_MEAS_CC1;
		अगर (chip->vconn_on)
			चयनes0_data |= FUSB_REG_SWITCHES0_VCONN_CC2;
		अगर (pull_up)
			चयनes0_data |= FUSB_REG_SWITCHES0_CC1_PU_EN;
		चयनes1_data = FUSB_REG_SWITCHES1_TXCC1_EN;
	पूर्ण अन्यथा अणु
		चयनes0_data |= FUSB_REG_SWITCHES0_MEAS_CC2;
		अगर (chip->vconn_on)
			चयनes0_data |= FUSB_REG_SWITCHES0_VCONN_CC1;
		अगर (pull_up)
			चयनes0_data |= FUSB_REG_SWITCHES0_CC2_PU_EN;
		चयनes1_data = FUSB_REG_SWITCHES1_TXCC2_EN;
	पूर्ण
	ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_SWITCHES0, चयनes0_data);
	अगर (ret < 0)
		वापस ret;
	ret = fusb302_i2c_mask_ग_लिखो(chip, FUSB_REG_SWITCHES1,
				     चयनes1_mask, चयनes1_data);
	अगर (ret < 0)
		वापस ret;
	chip->cc_polarity = cc_polarity;

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_handle_togकरोne_snk(काष्ठा fusb302_chip *chip,
				      u8 togकरोne_result)
अणु
	पूर्णांक ret = 0;
	u8 status0;
	u8 bc_lvl;
	क्रमागत typec_cc_polarity cc_polarity;
	क्रमागत typec_cc_status cc_status_active, cc1, cc2;

	/* set polarity and pull_up, pull_करोwn */
	cc_polarity = (togकरोne_result == FUSB_REG_STATUS1A_TOGSS_SNK1) ?
		      TYPEC_POLARITY_CC1 : TYPEC_POLARITY_CC2;
	ret = fusb302_set_cc_polarity_and_pull(chip, cc_polarity, false, true);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot set cc polarity %s, ret=%d",
			    cc_polarity_name[cc_polarity], ret);
		वापस ret;
	पूर्ण
	/* fusb302_set_cc_polarity() has set the correct measure block */
	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_STATUS0, &status0);
	अगर (ret < 0)
		वापस ret;
	bc_lvl = status0 & FUSB_REG_STATUS0_BC_LVL_MASK;
	cc_status_active = fusb302_bc_lvl_to_cc(bc_lvl);
	/* restart toggling अगर the cc status on the active line is OPEN */
	अगर (cc_status_active == TYPEC_CC_OPEN) अणु
		fusb302_log(chip, "restart toggling as CC_OPEN detected");
		ret = fusb302_set_toggling(chip, chip->toggling_mode);
		वापस ret;
	पूर्ण
	/* update tcpm with the new cc value */
	cc1 = (cc_polarity == TYPEC_POLARITY_CC1) ?
	      cc_status_active : TYPEC_CC_OPEN;
	cc2 = (cc_polarity == TYPEC_POLARITY_CC2) ?
	      cc_status_active : TYPEC_CC_OPEN;
	अगर ((chip->cc1 != cc1) || (chip->cc2 != cc2)) अणु
		chip->cc1 = cc1;
		chip->cc2 = cc2;
		tcpm_cc_change(chip->tcpm_port);
	पूर्ण
	/* turn off toggling */
	ret = fusb302_set_toggling(chip, TOGGLING_MODE_OFF);
	अगर (ret < 0) अणु
		fusb302_log(chip,
			    "cannot set toggling mode off, ret=%d", ret);
		वापस ret;
	पूर्ण
	/* unmask bc_lvl पूर्णांकerrupt */
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_MASK, FUSB_REG_MASK_BC_LVL);
	अगर (ret < 0) अणु
		fusb302_log(chip,
			    "cannot unmask bc_lcl interrupt, ret=%d", ret);
		वापस ret;
	पूर्ण
	chip->पूर्णांकr_bc_lvl = true;
	fusb302_log(chip, "detected cc1=%s, cc2=%s",
		    typec_cc_status_name[cc1],
		    typec_cc_status_name[cc2]);

	वापस ret;
पूर्ण

/* On error वापसs < 0, otherwise a typec_cc_status value */
अटल पूर्णांक fusb302_get_src_cc_status(काष्ठा fusb302_chip *chip,
				     क्रमागत typec_cc_polarity cc_polarity,
				     क्रमागत typec_cc_status *cc)
अणु
	u8 ra_mda = ra_mda_value[chip->src_current_status];
	u8 rd_mda = rd_mda_value[chip->src_current_status];
	u8 चयनes0_data, status0;
	पूर्णांक ret;

	/* Step 1: Set चयनes so that we measure the right CC pin */
	चयनes0_data = (cc_polarity == TYPEC_POLARITY_CC1) ?
		FUSB_REG_SWITCHES0_CC1_PU_EN | FUSB_REG_SWITCHES0_MEAS_CC1 :
		FUSB_REG_SWITCHES0_CC2_PU_EN | FUSB_REG_SWITCHES0_MEAS_CC2;
	ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_SWITCHES0, चयनes0_data);
	अगर (ret < 0)
		वापस ret;

	fusb302_i2c_पढ़ो(chip, FUSB_REG_SWITCHES0, &status0);
	fusb302_log(chip, "get_src_cc_status switches: 0x%0x", status0);

	/* Step 2: Set compararator volt to dअगरferentiate between Open and Rd */
	ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_MEASURE, rd_mda);
	अगर (ret < 0)
		वापस ret;

	usleep_range(50, 100);
	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_STATUS0, &status0);
	अगर (ret < 0)
		वापस ret;

	fusb302_log(chip, "get_src_cc_status rd_mda status0: 0x%0x", status0);
	अगर (status0 & FUSB_REG_STATUS0_COMP) अणु
		*cc = TYPEC_CC_OPEN;
		वापस 0;
	पूर्ण

	/* Step 3: Set compararator input to dअगरferentiate between Rd and Ra. */
	ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_MEASURE, ra_mda);
	अगर (ret < 0)
		वापस ret;

	usleep_range(50, 100);
	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_STATUS0, &status0);
	अगर (ret < 0)
		वापस ret;

	fusb302_log(chip, "get_src_cc_status ra_mda status0: 0x%0x", status0);
	अगर (status0 & FUSB_REG_STATUS0_COMP)
		*cc = TYPEC_CC_RD;
	अन्यथा
		*cc = TYPEC_CC_RA;

	वापस 0;
पूर्ण

अटल पूर्णांक fusb302_handle_togकरोne_src(काष्ठा fusb302_chip *chip,
				      u8 togकरोne_result)
अणु
	/*
	 * - set polarity (measure cc, vconn, tx)
	 * - set pull_up, pull_करोwn
	 * - set cc1, cc2, and update to tcpm_port
	 * - set I_COMP पूर्णांकerrupt on
	 */
	पूर्णांक ret = 0;
	u8 rd_mda = rd_mda_value[chip->src_current_status];
	क्रमागत toggling_mode toggling_mode = chip->toggling_mode;
	क्रमागत typec_cc_polarity cc_polarity;
	क्रमागत typec_cc_status cc1, cc2;

	/*
	 * The toggle-engine will stop in a src state अगर it sees either Ra or
	 * Rd. Determine the status क्रम both CC pins, starting with the one
	 * where toggling stopped, as that is where the चयनes poपूर्णांक now.
	 */
	अगर (togकरोne_result == FUSB_REG_STATUS1A_TOGSS_SRC1)
		ret = fusb302_get_src_cc_status(chip, TYPEC_POLARITY_CC1, &cc1);
	अन्यथा
		ret = fusb302_get_src_cc_status(chip, TYPEC_POLARITY_CC2, &cc2);
	अगर (ret < 0)
		वापस ret;
	/* we must turn off toggling beक्रमe we can measure the other pin */
	ret = fusb302_set_toggling(chip, TOGGLING_MODE_OFF);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot set toggling mode off, ret=%d", ret);
		वापस ret;
	पूर्ण
	/* get the status of the other pin */
	अगर (togकरोne_result == FUSB_REG_STATUS1A_TOGSS_SRC1)
		ret = fusb302_get_src_cc_status(chip, TYPEC_POLARITY_CC2, &cc2);
	अन्यथा
		ret = fusb302_get_src_cc_status(chip, TYPEC_POLARITY_CC1, &cc1);
	अगर (ret < 0)
		वापस ret;

	/* determine polarity based on the status of both pins */
	अगर (cc1 == TYPEC_CC_RD &&
			(cc2 == TYPEC_CC_OPEN || cc2 == TYPEC_CC_RA)) अणु
		cc_polarity = TYPEC_POLARITY_CC1;
	पूर्ण अन्यथा अगर (cc2 == TYPEC_CC_RD &&
		    (cc1 == TYPEC_CC_OPEN || cc1 == TYPEC_CC_RA)) अणु
		cc_polarity = TYPEC_POLARITY_CC2;
	पूर्ण अन्यथा अणु
		fusb302_log(chip, "unexpected CC status cc1=%s, cc2=%s, restarting toggling",
			    typec_cc_status_name[cc1],
			    typec_cc_status_name[cc2]);
		वापस fusb302_set_toggling(chip, toggling_mode);
	पूर्ण
	/* set polarity and pull_up, pull_करोwn */
	ret = fusb302_set_cc_polarity_and_pull(chip, cc_polarity, true, false);
	अगर (ret < 0) अणु
		fusb302_log(chip, "cannot set cc polarity %s, ret=%d",
			    cc_polarity_name[cc_polarity], ret);
		वापस ret;
	पूर्ण
	/* update tcpm with the new cc value */
	अगर ((chip->cc1 != cc1) || (chip->cc2 != cc2)) अणु
		chip->cc1 = cc1;
		chip->cc2 = cc2;
		tcpm_cc_change(chip->tcpm_port);
	पूर्ण
	/* set MDAC to Rd threshold, and unmask I_COMP क्रम unplug detection */
	ret = fusb302_i2c_ग_लिखो(chip, FUSB_REG_MEASURE, rd_mda);
	अगर (ret < 0)
		वापस ret;
	/* unmask comp_chng पूर्णांकerrupt */
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_MASK,
				     FUSB_REG_MASK_COMP_CHNG);
	अगर (ret < 0) अणु
		fusb302_log(chip,
			    "cannot unmask comp_chng interrupt, ret=%d", ret);
		वापस ret;
	पूर्ण
	chip->पूर्णांकr_comp_chng = true;
	fusb302_log(chip, "detected cc1=%s, cc2=%s",
		    typec_cc_status_name[cc1],
		    typec_cc_status_name[cc2]);

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_handle_togकरोne(काष्ठा fusb302_chip *chip)
अणु
	पूर्णांक ret = 0;
	u8 status1a;
	u8 togकरोne_result;

	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_STATUS1A, &status1a);
	अगर (ret < 0)
		वापस ret;
	togकरोne_result = (status1a >> FUSB_REG_STATUS1A_TOGSS_POS) &
			 FUSB_REG_STATUS1A_TOGSS_MASK;
	चयन (togकरोne_result) अणु
	हाल FUSB_REG_STATUS1A_TOGSS_SNK1:
	हाल FUSB_REG_STATUS1A_TOGSS_SNK2:
		वापस fusb302_handle_togकरोne_snk(chip, togकरोne_result);
	हाल FUSB_REG_STATUS1A_TOGSS_SRC1:
	हाल FUSB_REG_STATUS1A_TOGSS_SRC2:
		वापस fusb302_handle_togकरोne_src(chip, togकरोne_result);
	हाल FUSB_REG_STATUS1A_TOGSS_AA:
		/* करोesn't support */
		fusb302_log(chip, "AudioAccessory not supported");
		fusb302_set_toggling(chip, chip->toggling_mode);
		अवरोध;
	शेष:
		fusb302_log(chip, "TOGDONE with an invalid state: %d",
			    togकरोne_result);
		fusb302_set_toggling(chip, chip->toggling_mode);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_pd_reset(काष्ठा fusb302_chip *chip)
अणु
	वापस fusb302_i2c_set_bits(chip, FUSB_REG_RESET,
				    FUSB_REG_RESET_PD_RESET);
पूर्ण

अटल पूर्णांक fusb302_pd_पढ़ो_message(काष्ठा fusb302_chip *chip,
				   काष्ठा pd_message *msg)
अणु
	पूर्णांक ret = 0;
	u8 token;
	u8 crc[4];
	पूर्णांक len;

	/* first SOP token */
	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_FIFOS, &token);
	अगर (ret < 0)
		वापस ret;
	ret = fusb302_i2c_block_पढ़ो(chip, FUSB_REG_FIFOS, 2,
				     (u8 *)&msg->header);
	अगर (ret < 0)
		वापस ret;
	len = pd_header_cnt_le(msg->header) * 4;
	/* add 4 to length to include the CRC */
	अगर (len > PD_MAX_PAYLOAD * 4) अणु
		fusb302_log(chip, "PD message too long %d", len);
		वापस -EINVAL;
	पूर्ण
	अगर (len > 0) अणु
		ret = fusb302_i2c_block_पढ़ो(chip, FUSB_REG_FIFOS, len,
					     (u8 *)msg->payload);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	/* another 4 bytes to पढ़ो CRC out */
	ret = fusb302_i2c_block_पढ़ो(chip, FUSB_REG_FIFOS, 4, crc);
	अगर (ret < 0)
		वापस ret;
	fusb302_log(chip, "PD message header: %x", msg->header);
	fusb302_log(chip, "PD message len: %d", len);

	/*
	 * Check अगर we've पढ़ो off a GoodCRC message. If so then indicate to
	 * TCPM that the previous transmission has completed. Otherwise we pass
	 * the received message over to TCPM क्रम processing.
	 *
	 * We make this check here instead of basing the reporting decision on
	 * the IRQ event type, as it's possible क्रम the chip to report the
	 * TX_SUCCESS and GCRCSENT events out of order on occasion, so we need
	 * to check the message type to ensure correct reporting to TCPM.
	 */
	अगर ((!len) && (pd_header_type_le(msg->header) == PD_CTRL_GOOD_CRC))
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_SUCCESS);
	अन्यथा
		tcpm_pd_receive(chip->tcpm_port, msg);

	वापस ret;
पूर्ण

अटल irqवापस_t fusb302_irq_पूर्णांकn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fusb302_chip *chip = dev_id;
	अचिन्हित दीर्घ flags;

	/* Disable our level triggered IRQ until our irq_work has cleared it */
	disable_irq_nosync(chip->gpio_पूर्णांक_n_irq);

	spin_lock_irqsave(&chip->irq_lock, flags);
	अगर (chip->irq_suspended)
		chip->irq_जबतक_suspended = true;
	अन्यथा
		schedule_work(&chip->irq_work);
	spin_unlock_irqrestore(&chip->irq_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम fusb302_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fusb302_chip *chip = container_of(work, काष्ठा fusb302_chip,
						 irq_work);
	पूर्णांक ret = 0;
	u8 पूर्णांकerrupt;
	u8 पूर्णांकerrupta;
	u8 पूर्णांकerruptb;
	u8 status0;
	bool vbus_present;
	bool comp_result;
	bool पूर्णांकr_togकरोne;
	bool पूर्णांकr_bc_lvl;
	bool पूर्णांकr_comp_chng;
	काष्ठा pd_message pd_msg;

	mutex_lock(&chip->lock);
	/* grab a snapshot of पूर्णांकr flags */
	पूर्णांकr_togकरोne = chip->पूर्णांकr_togकरोne;
	पूर्णांकr_bc_lvl = chip->पूर्णांकr_bc_lvl;
	पूर्णांकr_comp_chng = chip->पूर्णांकr_comp_chng;

	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_INTERRUPT, &पूर्णांकerrupt);
	अगर (ret < 0)
		जाओ करोne;
	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_INTERRUPTA, &पूर्णांकerrupta);
	अगर (ret < 0)
		जाओ करोne;
	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_INTERRUPTB, &पूर्णांकerruptb);
	अगर (ret < 0)
		जाओ करोne;
	ret = fusb302_i2c_पढ़ो(chip, FUSB_REG_STATUS0, &status0);
	अगर (ret < 0)
		जाओ करोne;
	fusb302_log(chip,
		    "IRQ: 0x%02x, a: 0x%02x, b: 0x%02x, status0: 0x%02x",
		    पूर्णांकerrupt, पूर्णांकerrupta, पूर्णांकerruptb, status0);

	अगर (पूर्णांकerrupt & FUSB_REG_INTERRUPT_VBUSOK) अणु
		vbus_present = !!(status0 & FUSB_REG_STATUS0_VBUSOK);
		fusb302_log(chip, "IRQ: VBUS_OK, vbus=%s",
			    vbus_present ? "On" : "Off");
		अगर (vbus_present != chip->vbus_present) अणु
			chip->vbus_present = vbus_present;
			tcpm_vbus_change(chip->tcpm_port);
		पूर्ण
	पूर्ण

	अगर ((पूर्णांकerrupta & FUSB_REG_INTERRUPTA_TOGDONE) && पूर्णांकr_togकरोne) अणु
		fusb302_log(chip, "IRQ: TOGDONE");
		ret = fusb302_handle_togकरोne(chip);
		अगर (ret < 0) अणु
			fusb302_log(chip,
				    "handle togdone error, ret=%d", ret);
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर ((पूर्णांकerrupt & FUSB_REG_INTERRUPT_BC_LVL) && पूर्णांकr_bc_lvl) अणु
		fusb302_log(chip, "IRQ: BC_LVL, handler pending");
		/*
		 * as BC_LVL पूर्णांकerrupt can be affected by PD activity,
		 * apply delay to क्रम the handler to रुको क्रम the PD
		 * संकेतing to finish.
		 */
		mod_delayed_work(chip->wq, &chip->bc_lvl_handler,
				 msecs_to_jअगरfies(T_BC_LVL_DEBOUNCE_DELAY_MS));
	पूर्ण

	अगर ((पूर्णांकerrupt & FUSB_REG_INTERRUPT_COMP_CHNG) && पूर्णांकr_comp_chng) अणु
		comp_result = !!(status0 & FUSB_REG_STATUS0_COMP);
		fusb302_log(chip, "IRQ: COMP_CHNG, comp=%s",
			    comp_result ? "true" : "false");
		अगर (comp_result) अणु
			/* cc level > Rd_threshold, detach */
			chip->cc1 = TYPEC_CC_OPEN;
			chip->cc2 = TYPEC_CC_OPEN;
			tcpm_cc_change(chip->tcpm_port);
		पूर्ण
	पूर्ण

	अगर (पूर्णांकerrupt & FUSB_REG_INTERRUPT_COLLISION) अणु
		fusb302_log(chip, "IRQ: PD collision");
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_FAILED);
	पूर्ण

	अगर (पूर्णांकerrupta & FUSB_REG_INTERRUPTA_RETRYFAIL) अणु
		fusb302_log(chip, "IRQ: PD retry failed");
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_FAILED);
	पूर्ण

	अगर (पूर्णांकerrupta & FUSB_REG_INTERRUPTA_HARDSENT) अणु
		fusb302_log(chip, "IRQ: PD hardreset sent");
		ret = fusb302_pd_reset(chip);
		अगर (ret < 0) अणु
			fusb302_log(chip, "cannot PD reset, ret=%d", ret);
			जाओ करोne;
		पूर्ण
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_SUCCESS);
	पूर्ण

	अगर (पूर्णांकerrupta & FUSB_REG_INTERRUPTA_TX_SUCCESS) अणु
		fusb302_log(chip, "IRQ: PD tx success");
		ret = fusb302_pd_पढ़ो_message(chip, &pd_msg);
		अगर (ret < 0) अणु
			fusb302_log(chip,
				    "cannot read in PD message, ret=%d", ret);
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकerrupta & FUSB_REG_INTERRUPTA_HARDRESET) अणु
		fusb302_log(chip, "IRQ: PD received hardreset");
		ret = fusb302_pd_reset(chip);
		अगर (ret < 0) अणु
			fusb302_log(chip, "cannot PD reset, ret=%d", ret);
			जाओ करोne;
		पूर्ण
		tcpm_pd_hard_reset(chip->tcpm_port);
	पूर्ण

	अगर (पूर्णांकerruptb & FUSB_REG_INTERRUPTB_GCRCSENT) अणु
		fusb302_log(chip, "IRQ: PD sent good CRC");
		ret = fusb302_pd_पढ़ो_message(chip, &pd_msg);
		अगर (ret < 0) अणु
			fusb302_log(chip,
				    "cannot read in PD message, ret=%d", ret);
			जाओ करोne;
		पूर्ण
	पूर्ण
करोne:
	mutex_unlock(&chip->lock);
	enable_irq(chip->gpio_पूर्णांक_n_irq);
पूर्ण

अटल पूर्णांक init_gpio(काष्ठा fusb302_chip *chip)
अणु
	काष्ठा device *dev = chip->dev;
	पूर्णांक ret = 0;

	chip->gpio_पूर्णांक_n = devm_gpiod_get(dev, "fcs,int_n", GPIOD_IN);
	अगर (IS_ERR(chip->gpio_पूर्णांक_n)) अणु
		dev_err(dev, "failed to request gpio_int_n\n");
		वापस PTR_ERR(chip->gpio_पूर्णांक_n);
	पूर्ण
	ret = gpiod_to_irq(chip->gpio_पूर्णांक_n);
	अगर (ret < 0) अणु
		dev_err(dev,
			"cannot request IRQ for GPIO Int_N, ret=%d", ret);
		वापस ret;
	पूर्ण
	chip->gpio_पूर्णांक_n_irq = ret;
	वापस 0;
पूर्ण

#घोषणा PDO_FIXED_FLAGS \
	(PDO_FIXED_DUAL_ROLE | PDO_FIXED_DATA_SWAP | PDO_FIXED_USB_COMM)

अटल स्थिर u32 src_pकरो[] = अणु
	PDO_FIXED(5000, 400, PDO_FIXED_FLAGS)
पूर्ण;

अटल स्थिर u32 snk_pकरो[] = अणु
	PDO_FIXED(5000, 400, PDO_FIXED_FLAGS)
पूर्ण;

अटल स्थिर काष्ठा property_entry port_props[] = अणु
	PROPERTY_ENTRY_STRING("data-role", "dual"),
	PROPERTY_ENTRY_STRING("power-role", "dual"),
	PROPERTY_ENTRY_STRING("try-power-role", "sink"),
	PROPERTY_ENTRY_U32_ARRAY("source-pdos", src_pकरो),
	PROPERTY_ENTRY_U32_ARRAY("sink-pdos", snk_pकरो),
	PROPERTY_ENTRY_U32("op-sink-microwatt", 2500000),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा fwnode_handle *fusb302_fwnode_get(काष्ठा device *dev)
अणु
	काष्ठा fwnode_handle *fwnode;

	fwnode = device_get_named_child_node(dev, "connector");
	अगर (!fwnode)
		fwnode = fwnode_create_software_node(port_props, शून्य);

	वापस fwnode;
पूर्ण

अटल पूर्णांक fusb302_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा fusb302_chip *chip;
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	स्थिर अक्षर *name;
	पूर्णांक ret = 0;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_I2C_BLOCK)) अणु
		dev_err(&client->dev,
			"I2C/SMBus block functionality not supported!\n");
		वापस -ENODEV;
	पूर्ण
	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->i2c_client = client;
	chip->dev = &client->dev;
	mutex_init(&chip->lock);

	/*
	 * Devicetree platक्रमms should get extcon via phandle (not yet
	 * supported). On ACPI platक्रमms, we get the name from a device prop.
	 * This device prop is क्रम kernel पूर्णांकernal use only and is expected
	 * to be set by the platक्रमm code which also रेजिस्टरs the i2c client
	 * क्रम the fusb302.
	 */
	अगर (device_property_पढ़ो_string(dev, "linux,extcon-name", &name) == 0) अणु
		chip->extcon = extcon_get_extcon_dev(name);
		अगर (!chip->extcon)
			वापस -EPROBE_DEFER;
	पूर्ण

	chip->vbus = devm_regulator_get(chip->dev, "vbus");
	अगर (IS_ERR(chip->vbus))
		वापस PTR_ERR(chip->vbus);

	chip->wq = create_singlethपढ़ो_workqueue(dev_name(chip->dev));
	अगर (!chip->wq)
		वापस -ENOMEM;

	spin_lock_init(&chip->irq_lock);
	INIT_WORK(&chip->irq_work, fusb302_irq_work);
	INIT_DELAYED_WORK(&chip->bc_lvl_handler, fusb302_bc_lvl_handler_work);
	init_tcpc_dev(&chip->tcpc_dev);
	fusb302_debugfs_init(chip);

	अगर (client->irq) अणु
		chip->gpio_पूर्णांक_n_irq = client->irq;
	पूर्ण अन्यथा अणु
		ret = init_gpio(chip);
		अगर (ret < 0)
			जाओ destroy_workqueue;
	पूर्ण

	chip->tcpc_dev.fwnode = fusb302_fwnode_get(dev);
	अगर (IS_ERR(chip->tcpc_dev.fwnode)) अणु
		ret = PTR_ERR(chip->tcpc_dev.fwnode);
		जाओ destroy_workqueue;
	पूर्ण

	chip->tcpm_port = tcpm_रेजिस्टर_port(&client->dev, &chip->tcpc_dev);
	अगर (IS_ERR(chip->tcpm_port)) अणु
		fwnode_handle_put(chip->tcpc_dev.fwnode);
		ret = PTR_ERR(chip->tcpm_port);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "cannot register tcpm port, ret=%d", ret);
		जाओ destroy_workqueue;
	पूर्ण

	ret = request_irq(chip->gpio_पूर्णांक_n_irq, fusb302_irq_पूर्णांकn,
			  IRQF_ONESHOT | IRQF_TRIGGER_LOW,
			  "fsc_interrupt_int_n", chip);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot request IRQ for GPIO Int_N, ret=%d", ret);
		जाओ tcpm_unरेजिस्टर_port;
	पूर्ण
	enable_irq_wake(chip->gpio_पूर्णांक_n_irq);
	i2c_set_clientdata(client, chip);

	वापस ret;

tcpm_unरेजिस्टर_port:
	tcpm_unरेजिस्टर_port(chip->tcpm_port);
	fwnode_handle_put(chip->tcpc_dev.fwnode);
destroy_workqueue:
	fusb302_debugfs_निकास(chip);
	destroy_workqueue(chip->wq);

	वापस ret;
पूर्ण

अटल पूर्णांक fusb302_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा fusb302_chip *chip = i2c_get_clientdata(client);

	disable_irq_wake(chip->gpio_पूर्णांक_n_irq);
	मुक्त_irq(chip->gpio_पूर्णांक_n_irq, chip);
	cancel_work_sync(&chip->irq_work);
	cancel_delayed_work_sync(&chip->bc_lvl_handler);
	tcpm_unरेजिस्टर_port(chip->tcpm_port);
	fwnode_handle_put(chip->tcpc_dev.fwnode);
	destroy_workqueue(chip->wq);
	fusb302_debugfs_निकास(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक fusb302_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा fusb302_chip *chip = dev->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->irq_lock, flags);
	chip->irq_suspended = true;
	spin_unlock_irqrestore(&chip->irq_lock, flags);

	/* Make sure any pending irq_work is finished beक्रमe the bus suspends */
	flush_work(&chip->irq_work);
	वापस 0;
पूर्ण

अटल पूर्णांक fusb302_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा fusb302_chip *chip = dev->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->irq_lock, flags);
	अगर (chip->irq_जबतक_suspended) अणु
		schedule_work(&chip->irq_work);
		chip->irq_जबतक_suspended = false;
	पूर्ण
	chip->irq_suspended = false;
	spin_unlock_irqrestore(&chip->irq_lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fusb302_dt_match[] = अणु
	अणु.compatible = "fcs,fusb302"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fusb302_dt_match);

अटल स्थिर काष्ठा i2c_device_id fusb302_i2c_device_id[] = अणु
	अणु"typec_fusb302", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, fusb302_i2c_device_id);

अटल स्थिर काष्ठा dev_pm_ops fusb302_pm_ops = अणु
	.suspend = fusb302_pm_suspend,
	.resume = fusb302_pm_resume,
पूर्ण;

अटल काष्ठा i2c_driver fusb302_driver = अणु
	.driver = अणु
		   .name = "typec_fusb302",
		   .pm = &fusb302_pm_ops,
		   .of_match_table = of_match_ptr(fusb302_dt_match),
		   पूर्ण,
	.probe = fusb302_probe,
	.हटाओ = fusb302_हटाओ,
	.id_table = fusb302_i2c_device_id,
पूर्ण;
module_i2c_driver(fusb302_driver);

MODULE_AUTHOR("Yueyao Zhu <yueyao.zhu@gmail.com>");
MODULE_DESCRIPTION("Fairchild FUSB302 Type-C Chip Driver");
MODULE_LICENSE("GPL");
