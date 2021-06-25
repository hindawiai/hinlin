<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/acpi.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mdio/mdio-i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#समावेश "sfp.h"
#समावेश "swphy.h"

क्रमागत अणु
	GPIO_MODDEF0,
	GPIO_LOS,
	GPIO_TX_FAULT,
	GPIO_TX_DISABLE,
	GPIO_RATE_SELECT,
	GPIO_MAX,

	SFP_F_PRESENT = BIT(GPIO_MODDEF0),
	SFP_F_LOS = BIT(GPIO_LOS),
	SFP_F_TX_FAULT = BIT(GPIO_TX_FAULT),
	SFP_F_TX_DISABLE = BIT(GPIO_TX_DISABLE),
	SFP_F_RATE_SELECT = BIT(GPIO_RATE_SELECT),

	SFP_E_INSERT = 0,
	SFP_E_REMOVE,
	SFP_E_DEV_ATTACH,
	SFP_E_DEV_DETACH,
	SFP_E_DEV_DOWN,
	SFP_E_DEV_UP,
	SFP_E_TX_FAULT,
	SFP_E_TX_CLEAR,
	SFP_E_LOS_HIGH,
	SFP_E_LOS_LOW,
	SFP_E_TIMEOUT,

	SFP_MOD_EMPTY = 0,
	SFP_MOD_ERROR,
	SFP_MOD_PROBE,
	SFP_MOD_WAITDEV,
	SFP_MOD_HPOWER,
	SFP_MOD_WAITPWR,
	SFP_MOD_PRESENT,

	SFP_DEV_DETACHED = 0,
	SFP_DEV_DOWN,
	SFP_DEV_UP,

	SFP_S_DOWN = 0,
	SFP_S_FAIL,
	SFP_S_WAIT,
	SFP_S_INIT,
	SFP_S_INIT_PHY,
	SFP_S_INIT_TX_FAULT,
	SFP_S_WAIT_LOS,
	SFP_S_LINK_UP,
	SFP_S_TX_FAULT,
	SFP_S_REINIT,
	SFP_S_TX_DISABLE,
पूर्ण;

अटल स्थिर अक्षर  * स्थिर mod_state_strings[] = अणु
	[SFP_MOD_EMPTY] = "empty",
	[SFP_MOD_ERROR] = "error",
	[SFP_MOD_PROBE] = "probe",
	[SFP_MOD_WAITDEV] = "waitdev",
	[SFP_MOD_HPOWER] = "hpower",
	[SFP_MOD_WAITPWR] = "waitpwr",
	[SFP_MOD_PRESENT] = "present",
पूर्ण;

अटल स्थिर अक्षर *mod_state_to_str(अचिन्हित लघु mod_state)
अणु
	अगर (mod_state >= ARRAY_SIZE(mod_state_strings))
		वापस "Unknown module state";
	वापस mod_state_strings[mod_state];
पूर्ण

अटल स्थिर अक्षर * स्थिर dev_state_strings[] = अणु
	[SFP_DEV_DETACHED] = "detached",
	[SFP_DEV_DOWN] = "down",
	[SFP_DEV_UP] = "up",
पूर्ण;

अटल स्थिर अक्षर *dev_state_to_str(अचिन्हित लघु dev_state)
अणु
	अगर (dev_state >= ARRAY_SIZE(dev_state_strings))
		वापस "Unknown device state";
	वापस dev_state_strings[dev_state];
पूर्ण

अटल स्थिर अक्षर * स्थिर event_strings[] = अणु
	[SFP_E_INSERT] = "insert",
	[SFP_E_REMOVE] = "remove",
	[SFP_E_DEV_ATTACH] = "dev_attach",
	[SFP_E_DEV_DETACH] = "dev_detach",
	[SFP_E_DEV_DOWN] = "dev_down",
	[SFP_E_DEV_UP] = "dev_up",
	[SFP_E_TX_FAULT] = "tx_fault",
	[SFP_E_TX_CLEAR] = "tx_clear",
	[SFP_E_LOS_HIGH] = "los_high",
	[SFP_E_LOS_LOW] = "los_low",
	[SFP_E_TIMEOUT] = "timeout",
पूर्ण;

अटल स्थिर अक्षर *event_to_str(अचिन्हित लघु event)
अणु
	अगर (event >= ARRAY_SIZE(event_strings))
		वापस "Unknown event";
	वापस event_strings[event];
पूर्ण

अटल स्थिर अक्षर * स्थिर sm_state_strings[] = अणु
	[SFP_S_DOWN] = "down",
	[SFP_S_FAIL] = "fail",
	[SFP_S_WAIT] = "wait",
	[SFP_S_INIT] = "init",
	[SFP_S_INIT_PHY] = "init_phy",
	[SFP_S_INIT_TX_FAULT] = "init_tx_fault",
	[SFP_S_WAIT_LOS] = "wait_los",
	[SFP_S_LINK_UP] = "link_up",
	[SFP_S_TX_FAULT] = "tx_fault",
	[SFP_S_REINIT] = "reinit",
	[SFP_S_TX_DISABLE] = "rx_disable",
पूर्ण;

अटल स्थिर अक्षर *sm_state_to_str(अचिन्हित लघु sm_state)
अणु
	अगर (sm_state >= ARRAY_SIZE(sm_state_strings))
		वापस "Unknown state";
	वापस sm_state_strings[sm_state];
पूर्ण

अटल स्थिर अक्षर *gpio_of_names[] = अणु
	"mod-def0",
	"los",
	"tx-fault",
	"tx-disable",
	"rate-select0",
पूर्ण;

अटल स्थिर क्रमागत gpiod_flags gpio_flags[] = अणु
	GPIOD_IN,
	GPIOD_IN,
	GPIOD_IN,
	GPIOD_ASIS,
	GPIOD_ASIS,
पूर्ण;

/* t_start_up (SFF-8431) or t_init (SFF-8472) is the समय required क्रम a
 * non-cooled module to initialise its laser safety circuitry. We रुको
 * an initial T_WAIT period beक्रमe we check the tx fault to give any PHY
 * on board (क्रम a copper SFP) समय to initialise.
 */
#घोषणा T_WAIT			msecs_to_jअगरfies(50)
#घोषणा T_START_UP		msecs_to_jअगरfies(300)
#घोषणा T_START_UP_BAD_GPON	msecs_to_jअगरfies(60000)

/* t_reset is the समय required to निश्चित the TX_DISABLE संकेत to reset
 * an indicated TX_FAULT.
 */
#घोषणा T_RESET_US		10
#घोषणा T_FAULT_RECOVER		msecs_to_jअगरfies(1000)

/* N_FAULT_INIT is the number of recovery attempts at module initialisation
 * समय. If the TX_FAULT संकेत is not deनिश्चितed after this number of
 * attempts at clearing it, we decide that the module is faulty.
 * N_FAULT is the same but after the module has initialised.
 */
#घोषणा N_FAULT_INIT		5
#घोषणा N_FAULT			5

/* T_PHY_RETRY is the समय पूर्णांकerval between attempts to probe the PHY.
 * R_PHY_RETRY is the number of attempts.
 */
#घोषणा T_PHY_RETRY		msecs_to_jअगरfies(50)
#घोषणा R_PHY_RETRY		12

/* SFP module presence detection is poor: the three MOD DEF संकेतs are
 * the same length on the PCB, which means it's possible क्रम MOD DEF 0 to
 * connect beक्रमe the I2C bus on MOD DEF 1/2.
 *
 * The SFF-8472 specअगरies t_serial ("Time from घातer on until module is
 * पढ़ोy क्रम data transmission over the two wire serial bus.") as 300ms.
 */
#घोषणा T_SERIAL		msecs_to_jअगरfies(300)
#घोषणा T_HPOWER_LEVEL		msecs_to_jअगरfies(300)
#घोषणा T_PROBE_RETRY_INIT	msecs_to_jअगरfies(100)
#घोषणा R_PROBE_RETRY_INIT	10
#घोषणा T_PROBE_RETRY_SLOW	msecs_to_jअगरfies(5000)
#घोषणा R_PROBE_RETRY_SLOW	12

/* SFP modules appear to always have their PHY configured क्रम bus address
 * 0x56 (which with mdio-i2c, translates to a PHY address of 22).
 */
#घोषणा SFP_PHY_ADDR	22

काष्ठा sff_data अणु
	अचिन्हित पूर्णांक gpios;
	bool (*module_supported)(स्थिर काष्ठा sfp_eeprom_id *id);
पूर्ण;

काष्ठा sfp अणु
	काष्ठा device *dev;
	काष्ठा i2c_adapter *i2c;
	काष्ठा mii_bus *i2c_mii;
	काष्ठा sfp_bus *sfp_bus;
	काष्ठा phy_device *mod_phy;
	स्थिर काष्ठा sff_data *type;
	माप_प्रकार i2c_block_size;
	u32 max_घातer_mW;

	अचिन्हित पूर्णांक (*get_state)(काष्ठा sfp *);
	व्योम (*set_state)(काष्ठा sfp *, अचिन्हित पूर्णांक);
	पूर्णांक (*पढ़ो)(काष्ठा sfp *, bool, u8, व्योम *, माप_प्रकार);
	पूर्णांक (*ग_लिखो)(काष्ठा sfp *, bool, u8, व्योम *, माप_प्रकार);

	काष्ठा gpio_desc *gpio[GPIO_MAX];
	पूर्णांक gpio_irq[GPIO_MAX];

	bool need_poll;

	काष्ठा mutex st_mutex;			/* Protects state */
	अचिन्हित पूर्णांक state_soft_mask;
	अचिन्हित पूर्णांक state;
	काष्ठा delayed_work poll;
	काष्ठा delayed_work समयout;
	काष्ठा mutex sm_mutex;			/* Protects state machine */
	अचिन्हित अक्षर sm_mod_state;
	अचिन्हित अक्षर sm_mod_tries_init;
	अचिन्हित अक्षर sm_mod_tries;
	अचिन्हित अक्षर sm_dev_state;
	अचिन्हित लघु sm_state;
	अचिन्हित अक्षर sm_fault_retries;
	अचिन्हित अक्षर sm_phy_retries;

	काष्ठा sfp_eeprom_id id;
	अचिन्हित पूर्णांक module_घातer_mW;
	अचिन्हित पूर्णांक module_t_start_up;

#अगर IS_ENABLED(CONFIG_HWMON)
	काष्ठा sfp_diag diag;
	काष्ठा delayed_work hwmon_probe;
	अचिन्हित पूर्णांक hwmon_tries;
	काष्ठा device *hwmon_dev;
	अक्षर *hwmon_name;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
	काष्ठा dentry *debugfs_dir;
#पूर्ण_अगर
पूर्ण;

अटल bool sff_module_supported(स्थिर काष्ठा sfp_eeprom_id *id)
अणु
	वापस id->base.phys_id == SFF8024_ID_SFF_8472 &&
	       id->base.phys_ext_id == SFP_PHYS_EXT_ID_SFP;
पूर्ण

अटल स्थिर काष्ठा sff_data sff_data = अणु
	.gpios = SFP_F_LOS | SFP_F_TX_FAULT | SFP_F_TX_DISABLE,
	.module_supported = sff_module_supported,
पूर्ण;

अटल bool sfp_module_supported(स्थिर काष्ठा sfp_eeprom_id *id)
अणु
	अगर (id->base.phys_id == SFF8024_ID_SFP &&
	    id->base.phys_ext_id == SFP_PHYS_EXT_ID_SFP)
		वापस true;

	/* SFP GPON module Ubiquiti U-Fiber Instant has in its EEPROM stored
	 * phys id SFF instead of SFP. Thereक्रमe mark this module explicitly
	 * as supported based on venकरोr name and pn match.
	 */
	अगर (id->base.phys_id == SFF8024_ID_SFF_8472 &&
	    id->base.phys_ext_id == SFP_PHYS_EXT_ID_SFP &&
	    !स_भेद(id->base.venकरोr_name, "UBNT            ", 16) &&
	    !स_भेद(id->base.venकरोr_pn, "UF-INSTANT      ", 16))
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा sff_data sfp_data = अणु
	.gpios = SFP_F_PRESENT | SFP_F_LOS | SFP_F_TX_FAULT |
		 SFP_F_TX_DISABLE | SFP_F_RATE_SELECT,
	.module_supported = sfp_module_supported,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sfp_of_match[] = अणु
	अणु .compatible = "sff,sff", .data = &sff_data, पूर्ण,
	अणु .compatible = "sff,sfp", .data = &sfp_data, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sfp_of_match);

अटल अचिन्हित दीर्घ poll_jअगरfies;

अटल अचिन्हित पूर्णांक sfp_gpio_get_state(काष्ठा sfp *sfp)
अणु
	अचिन्हित पूर्णांक i, state, v;

	क्रम (i = state = 0; i < GPIO_MAX; i++) अणु
		अगर (gpio_flags[i] != GPIOD_IN || !sfp->gpio[i])
			जारी;

		v = gpiod_get_value_cansleep(sfp->gpio[i]);
		अगर (v)
			state |= BIT(i);
	पूर्ण

	वापस state;
पूर्ण

अटल अचिन्हित पूर्णांक sff_gpio_get_state(काष्ठा sfp *sfp)
अणु
	वापस sfp_gpio_get_state(sfp) | SFP_F_PRESENT;
पूर्ण

अटल व्योम sfp_gpio_set_state(काष्ठा sfp *sfp, अचिन्हित पूर्णांक state)
अणु
	अगर (state & SFP_F_PRESENT) अणु
		/* If the module is present, drive the संकेतs */
		अगर (sfp->gpio[GPIO_TX_DISABLE])
			gpiod_direction_output(sfp->gpio[GPIO_TX_DISABLE],
					       state & SFP_F_TX_DISABLE);
		अगर (state & SFP_F_RATE_SELECT)
			gpiod_direction_output(sfp->gpio[GPIO_RATE_SELECT],
					       state & SFP_F_RATE_SELECT);
	पूर्ण अन्यथा अणु
		/* Otherwise, let them भग्न to the pull-ups */
		अगर (sfp->gpio[GPIO_TX_DISABLE])
			gpiod_direction_input(sfp->gpio[GPIO_TX_DISABLE]);
		अगर (state & SFP_F_RATE_SELECT)
			gpiod_direction_input(sfp->gpio[GPIO_RATE_SELECT]);
	पूर्ण
पूर्ण

अटल पूर्णांक sfp_i2c_पढ़ो(काष्ठा sfp *sfp, bool a2, u8 dev_addr, व्योम *buf,
			माप_प्रकार len)
अणु
	काष्ठा i2c_msg msgs[2];
	u8 bus_addr = a2 ? 0x51 : 0x50;
	माप_प्रकार block_size = sfp->i2c_block_size;
	माप_प्रकार this_len;
	पूर्णांक ret;

	msgs[0].addr = bus_addr;
	msgs[0].flags = 0;
	msgs[0].len = 1;
	msgs[0].buf = &dev_addr;
	msgs[1].addr = bus_addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = len;
	msgs[1].buf = buf;

	जबतक (len) अणु
		this_len = len;
		अगर (this_len > block_size)
			this_len = block_size;

		msgs[1].len = this_len;

		ret = i2c_transfer(sfp->i2c, msgs, ARRAY_SIZE(msgs));
		अगर (ret < 0)
			वापस ret;

		अगर (ret != ARRAY_SIZE(msgs))
			अवरोध;

		msgs[1].buf += this_len;
		dev_addr += this_len;
		len -= this_len;
	पूर्ण

	वापस msgs[1].buf - (u8 *)buf;
पूर्ण

अटल पूर्णांक sfp_i2c_ग_लिखो(काष्ठा sfp *sfp, bool a2, u8 dev_addr, व्योम *buf,
	माप_प्रकार len)
अणु
	काष्ठा i2c_msg msgs[1];
	u8 bus_addr = a2 ? 0x51 : 0x50;
	पूर्णांक ret;

	msgs[0].addr = bus_addr;
	msgs[0].flags = 0;
	msgs[0].len = 1 + len;
	msgs[0].buf = kदो_स्मृति(1 + len, GFP_KERNEL);
	अगर (!msgs[0].buf)
		वापस -ENOMEM;

	msgs[0].buf[0] = dev_addr;
	स_नकल(&msgs[0].buf[1], buf, len);

	ret = i2c_transfer(sfp->i2c, msgs, ARRAY_SIZE(msgs));

	kमुक्त(msgs[0].buf);

	अगर (ret < 0)
		वापस ret;

	वापस ret == ARRAY_SIZE(msgs) ? len : 0;
पूर्ण

अटल पूर्णांक sfp_i2c_configure(काष्ठा sfp *sfp, काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा mii_bus *i2c_mii;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(i2c, I2C_FUNC_I2C))
		वापस -EINVAL;

	sfp->i2c = i2c;
	sfp->पढ़ो = sfp_i2c_पढ़ो;
	sfp->ग_लिखो = sfp_i2c_ग_लिखो;

	i2c_mii = mdio_i2c_alloc(sfp->dev, i2c);
	अगर (IS_ERR(i2c_mii))
		वापस PTR_ERR(i2c_mii);

	i2c_mii->name = "SFP I2C Bus";
	i2c_mii->phy_mask = ~0;

	ret = mdiobus_रेजिस्टर(i2c_mii);
	अगर (ret < 0) अणु
		mdiobus_मुक्त(i2c_mii);
		वापस ret;
	पूर्ण

	sfp->i2c_mii = i2c_mii;

	वापस 0;
पूर्ण

/* Interface */
अटल पूर्णांक sfp_पढ़ो(काष्ठा sfp *sfp, bool a2, u8 addr, व्योम *buf, माप_प्रकार len)
अणु
	वापस sfp->पढ़ो(sfp, a2, addr, buf, len);
पूर्ण

अटल पूर्णांक sfp_ग_लिखो(काष्ठा sfp *sfp, bool a2, u8 addr, व्योम *buf, माप_प्रकार len)
अणु
	वापस sfp->ग_लिखो(sfp, a2, addr, buf, len);
पूर्ण

अटल अचिन्हित पूर्णांक sfp_soft_get_state(काष्ठा sfp *sfp)
अणु
	अचिन्हित पूर्णांक state = 0;
	u8 status;
	पूर्णांक ret;

	ret = sfp_पढ़ो(sfp, true, SFP_STATUS, &status, माप(status));
	अगर (ret == माप(status)) अणु
		अगर (status & SFP_STATUS_RX_LOS)
			state |= SFP_F_LOS;
		अगर (status & SFP_STATUS_TX_FAULT)
			state |= SFP_F_TX_FAULT;
	पूर्ण अन्यथा अणु
		dev_err_ratelimited(sfp->dev,
				    "failed to read SFP soft status: %d\n",
				    ret);
		/* Preserve the current state */
		state = sfp->state;
	पूर्ण

	वापस state & sfp->state_soft_mask;
पूर्ण

अटल व्योम sfp_soft_set_state(काष्ठा sfp *sfp, अचिन्हित पूर्णांक state)
अणु
	u8 status;

	अगर (sfp_पढ़ो(sfp, true, SFP_STATUS, &status, माप(status)) ==
		     माप(status)) अणु
		अगर (state & SFP_F_TX_DISABLE)
			status |= SFP_STATUS_TX_DISABLE_FORCE;
		अन्यथा
			status &= ~SFP_STATUS_TX_DISABLE_FORCE;

		sfp_ग_लिखो(sfp, true, SFP_STATUS, &status, माप(status));
	पूर्ण
पूर्ण

अटल व्योम sfp_soft_start_poll(काष्ठा sfp *sfp)
अणु
	स्थिर काष्ठा sfp_eeprom_id *id = &sfp->id;

	sfp->state_soft_mask = 0;
	अगर (id->ext.enhopts & SFP_ENHOPTS_SOFT_TX_DISABLE &&
	    !sfp->gpio[GPIO_TX_DISABLE])
		sfp->state_soft_mask |= SFP_F_TX_DISABLE;
	अगर (id->ext.enhopts & SFP_ENHOPTS_SOFT_TX_FAULT &&
	    !sfp->gpio[GPIO_TX_FAULT])
		sfp->state_soft_mask |= SFP_F_TX_FAULT;
	अगर (id->ext.enhopts & SFP_ENHOPTS_SOFT_RX_LOS &&
	    !sfp->gpio[GPIO_LOS])
		sfp->state_soft_mask |= SFP_F_LOS;

	अगर (sfp->state_soft_mask & (SFP_F_LOS | SFP_F_TX_FAULT) &&
	    !sfp->need_poll)
		mod_delayed_work(प्रणाली_wq, &sfp->poll, poll_jअगरfies);
पूर्ण

अटल व्योम sfp_soft_stop_poll(काष्ठा sfp *sfp)
अणु
	sfp->state_soft_mask = 0;
पूर्ण

अटल अचिन्हित पूर्णांक sfp_get_state(काष्ठा sfp *sfp)
अणु
	अचिन्हित पूर्णांक state = sfp->get_state(sfp);

	अगर (state & SFP_F_PRESENT &&
	    sfp->state_soft_mask & (SFP_F_LOS | SFP_F_TX_FAULT))
		state |= sfp_soft_get_state(sfp);

	वापस state;
पूर्ण

अटल व्योम sfp_set_state(काष्ठा sfp *sfp, अचिन्हित पूर्णांक state)
अणु
	sfp->set_state(sfp, state);

	अगर (state & SFP_F_PRESENT &&
	    sfp->state_soft_mask & SFP_F_TX_DISABLE)
		sfp_soft_set_state(sfp, state);
पूर्ण

अटल अचिन्हित पूर्णांक sfp_check(व्योम *buf, माप_प्रकार len)
अणु
	u8 *p, check;

	क्रम (p = buf, check = 0; len; p++, len--)
		check += *p;

	वापस check;
पूर्ण

/* hwmon */
#अगर IS_ENABLED(CONFIG_HWMON)
अटल umode_t sfp_hwmon_is_visible(स्थिर व्योम *data,
				    क्रमागत hwmon_sensor_types type,
				    u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा sfp *sfp = data;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_min_alarm:
		हाल hwmon_temp_max_alarm:
		हाल hwmon_temp_lcrit_alarm:
		हाल hwmon_temp_crit_alarm:
		हाल hwmon_temp_min:
		हाल hwmon_temp_max:
		हाल hwmon_temp_lcrit:
		हाल hwmon_temp_crit:
			अगर (!(sfp->id.ext.enhopts & SFP_ENHOPTS_ALARMWARN))
				वापस 0;
			fallthrough;
		हाल hwmon_temp_input:
		हाल hwmon_temp_label:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_min_alarm:
		हाल hwmon_in_max_alarm:
		हाल hwmon_in_lcrit_alarm:
		हाल hwmon_in_crit_alarm:
		हाल hwmon_in_min:
		हाल hwmon_in_max:
		हाल hwmon_in_lcrit:
		हाल hwmon_in_crit:
			अगर (!(sfp->id.ext.enhopts & SFP_ENHOPTS_ALARMWARN))
				वापस 0;
			fallthrough;
		हाल hwmon_in_input:
		हाल hwmon_in_label:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_min_alarm:
		हाल hwmon_curr_max_alarm:
		हाल hwmon_curr_lcrit_alarm:
		हाल hwmon_curr_crit_alarm:
		हाल hwmon_curr_min:
		हाल hwmon_curr_max:
		हाल hwmon_curr_lcrit:
		हाल hwmon_curr_crit:
			अगर (!(sfp->id.ext.enhopts & SFP_ENHOPTS_ALARMWARN))
				वापस 0;
			fallthrough;
		हाल hwmon_curr_input:
		हाल hwmon_curr_label:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_घातer:
		/* External calibration of receive घातer requires
		 * भग्नing poपूर्णांक arithmetic. Doing that in the kernel
		 * is not easy, so just skip it. If the module करोes
		 * not require बाह्यal calibration, we can however
		 * show receiver घातer, since FP is then not needed.
		 */
		अगर (sfp->id.ext.diagmon & SFP_DIAGMON_EXT_CAL &&
		    channel == 1)
			वापस 0;
		चयन (attr) अणु
		हाल hwmon_घातer_min_alarm:
		हाल hwmon_घातer_max_alarm:
		हाल hwmon_घातer_lcrit_alarm:
		हाल hwmon_घातer_crit_alarm:
		हाल hwmon_घातer_min:
		हाल hwmon_घातer_max:
		हाल hwmon_घातer_lcrit:
		हाल hwmon_घातer_crit:
			अगर (!(sfp->id.ext.enhopts & SFP_ENHOPTS_ALARMWARN))
				वापस 0;
			fallthrough;
		हाल hwmon_घातer_input:
		हाल hwmon_घातer_label:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक sfp_hwmon_पढ़ो_sensor(काष्ठा sfp *sfp, पूर्णांक reg, दीर्घ *value)
अणु
	__be16 val;
	पूर्णांक err;

	err = sfp_पढ़ो(sfp, true, reg, &val, माप(val));
	अगर (err < 0)
		वापस err;

	*value = be16_to_cpu(val);

	वापस 0;
पूर्ण

अटल व्योम sfp_hwmon_to_rx_घातer(दीर्घ *value)
अणु
	*value = DIV_ROUND_CLOSEST(*value, 10);
पूर्ण

अटल व्योम sfp_hwmon_calibrate(काष्ठा sfp *sfp, अचिन्हित पूर्णांक slope, पूर्णांक offset,
				दीर्घ *value)
अणु
	अगर (sfp->id.ext.diagmon & SFP_DIAGMON_EXT_CAL)
		*value = DIV_ROUND_CLOSEST(*value * slope, 256) + offset;
पूर्ण

अटल व्योम sfp_hwmon_calibrate_temp(काष्ठा sfp *sfp, दीर्घ *value)
अणु
	sfp_hwmon_calibrate(sfp, be16_to_cpu(sfp->diag.cal_t_slope),
			    be16_to_cpu(sfp->diag.cal_t_offset), value);

	अगर (*value >= 0x8000)
		*value -= 0x10000;

	*value = DIV_ROUND_CLOSEST(*value * 1000, 256);
पूर्ण

अटल व्योम sfp_hwmon_calibrate_vcc(काष्ठा sfp *sfp, दीर्घ *value)
अणु
	sfp_hwmon_calibrate(sfp, be16_to_cpu(sfp->diag.cal_v_slope),
			    be16_to_cpu(sfp->diag.cal_v_offset), value);

	*value = DIV_ROUND_CLOSEST(*value, 10);
पूर्ण

अटल व्योम sfp_hwmon_calibrate_bias(काष्ठा sfp *sfp, दीर्घ *value)
अणु
	sfp_hwmon_calibrate(sfp, be16_to_cpu(sfp->diag.cal_txi_slope),
			    be16_to_cpu(sfp->diag.cal_txi_offset), value);

	*value = DIV_ROUND_CLOSEST(*value, 500);
पूर्ण

अटल व्योम sfp_hwmon_calibrate_tx_घातer(काष्ठा sfp *sfp, दीर्घ *value)
अणु
	sfp_hwmon_calibrate(sfp, be16_to_cpu(sfp->diag.cal_txpwr_slope),
			    be16_to_cpu(sfp->diag.cal_txpwr_offset), value);

	*value = DIV_ROUND_CLOSEST(*value, 10);
पूर्ण

अटल पूर्णांक sfp_hwmon_पढ़ो_temp(काष्ठा sfp *sfp, पूर्णांक reg, दीर्घ *value)
अणु
	पूर्णांक err;

	err = sfp_hwmon_पढ़ो_sensor(sfp, reg, value);
	अगर (err < 0)
		वापस err;

	sfp_hwmon_calibrate_temp(sfp, value);

	वापस 0;
पूर्ण

अटल पूर्णांक sfp_hwmon_पढ़ो_vcc(काष्ठा sfp *sfp, पूर्णांक reg, दीर्घ *value)
अणु
	पूर्णांक err;

	err = sfp_hwmon_पढ़ो_sensor(sfp, reg, value);
	अगर (err < 0)
		वापस err;

	sfp_hwmon_calibrate_vcc(sfp, value);

	वापस 0;
पूर्ण

अटल पूर्णांक sfp_hwmon_पढ़ो_bias(काष्ठा sfp *sfp, पूर्णांक reg, दीर्घ *value)
अणु
	पूर्णांक err;

	err = sfp_hwmon_पढ़ो_sensor(sfp, reg, value);
	अगर (err < 0)
		वापस err;

	sfp_hwmon_calibrate_bias(sfp, value);

	वापस 0;
पूर्ण

अटल पूर्णांक sfp_hwmon_पढ़ो_tx_घातer(काष्ठा sfp *sfp, पूर्णांक reg, दीर्घ *value)
अणु
	पूर्णांक err;

	err = sfp_hwmon_पढ़ो_sensor(sfp, reg, value);
	अगर (err < 0)
		वापस err;

	sfp_hwmon_calibrate_tx_घातer(sfp, value);

	वापस 0;
पूर्ण

अटल पूर्णांक sfp_hwmon_पढ़ो_rx_घातer(काष्ठा sfp *sfp, पूर्णांक reg, दीर्घ *value)
अणु
	पूर्णांक err;

	err = sfp_hwmon_पढ़ो_sensor(sfp, reg, value);
	अगर (err < 0)
		वापस err;

	sfp_hwmon_to_rx_घातer(value);

	वापस 0;
पूर्ण

अटल पूर्णांक sfp_hwmon_temp(काष्ठा sfp *sfp, u32 attr, दीर्घ *value)
अणु
	u8 status;
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		वापस sfp_hwmon_पढ़ो_temp(sfp, SFP_TEMP, value);

	हाल hwmon_temp_lcrit:
		*value = be16_to_cpu(sfp->diag.temp_low_alarm);
		sfp_hwmon_calibrate_temp(sfp, value);
		वापस 0;

	हाल hwmon_temp_min:
		*value = be16_to_cpu(sfp->diag.temp_low_warn);
		sfp_hwmon_calibrate_temp(sfp, value);
		वापस 0;
	हाल hwmon_temp_max:
		*value = be16_to_cpu(sfp->diag.temp_high_warn);
		sfp_hwmon_calibrate_temp(sfp, value);
		वापस 0;

	हाल hwmon_temp_crit:
		*value = be16_to_cpu(sfp->diag.temp_high_alarm);
		sfp_hwmon_calibrate_temp(sfp, value);
		वापस 0;

	हाल hwmon_temp_lcrit_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_ALARM0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_ALARM0_TEMP_LOW);
		वापस 0;

	हाल hwmon_temp_min_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_WARN0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_WARN0_TEMP_LOW);
		वापस 0;

	हाल hwmon_temp_max_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_WARN0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_WARN0_TEMP_HIGH);
		वापस 0;

	हाल hwmon_temp_crit_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_ALARM0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_ALARM0_TEMP_HIGH);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक sfp_hwmon_vcc(काष्ठा sfp *sfp, u32 attr, दीर्घ *value)
अणु
	u8 status;
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_in_input:
		वापस sfp_hwmon_पढ़ो_vcc(sfp, SFP_VCC, value);

	हाल hwmon_in_lcrit:
		*value = be16_to_cpu(sfp->diag.volt_low_alarm);
		sfp_hwmon_calibrate_vcc(sfp, value);
		वापस 0;

	हाल hwmon_in_min:
		*value = be16_to_cpu(sfp->diag.volt_low_warn);
		sfp_hwmon_calibrate_vcc(sfp, value);
		वापस 0;

	हाल hwmon_in_max:
		*value = be16_to_cpu(sfp->diag.volt_high_warn);
		sfp_hwmon_calibrate_vcc(sfp, value);
		वापस 0;

	हाल hwmon_in_crit:
		*value = be16_to_cpu(sfp->diag.volt_high_alarm);
		sfp_hwmon_calibrate_vcc(sfp, value);
		वापस 0;

	हाल hwmon_in_lcrit_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_ALARM0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_ALARM0_VCC_LOW);
		वापस 0;

	हाल hwmon_in_min_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_WARN0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_WARN0_VCC_LOW);
		वापस 0;

	हाल hwmon_in_max_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_WARN0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_WARN0_VCC_HIGH);
		वापस 0;

	हाल hwmon_in_crit_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_ALARM0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_ALARM0_VCC_HIGH);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक sfp_hwmon_bias(काष्ठा sfp *sfp, u32 attr, दीर्घ *value)
अणु
	u8 status;
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_curr_input:
		वापस sfp_hwmon_पढ़ो_bias(sfp, SFP_TX_BIAS, value);

	हाल hwmon_curr_lcrit:
		*value = be16_to_cpu(sfp->diag.bias_low_alarm);
		sfp_hwmon_calibrate_bias(sfp, value);
		वापस 0;

	हाल hwmon_curr_min:
		*value = be16_to_cpu(sfp->diag.bias_low_warn);
		sfp_hwmon_calibrate_bias(sfp, value);
		वापस 0;

	हाल hwmon_curr_max:
		*value = be16_to_cpu(sfp->diag.bias_high_warn);
		sfp_hwmon_calibrate_bias(sfp, value);
		वापस 0;

	हाल hwmon_curr_crit:
		*value = be16_to_cpu(sfp->diag.bias_high_alarm);
		sfp_hwmon_calibrate_bias(sfp, value);
		वापस 0;

	हाल hwmon_curr_lcrit_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_ALARM0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_ALARM0_TX_BIAS_LOW);
		वापस 0;

	हाल hwmon_curr_min_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_WARN0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_WARN0_TX_BIAS_LOW);
		वापस 0;

	हाल hwmon_curr_max_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_WARN0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_WARN0_TX_BIAS_HIGH);
		वापस 0;

	हाल hwmon_curr_crit_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_ALARM0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_ALARM0_TX_BIAS_HIGH);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक sfp_hwmon_tx_घातer(काष्ठा sfp *sfp, u32 attr, दीर्घ *value)
अणु
	u8 status;
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_घातer_input:
		वापस sfp_hwmon_पढ़ो_tx_घातer(sfp, SFP_TX_POWER, value);

	हाल hwmon_घातer_lcrit:
		*value = be16_to_cpu(sfp->diag.txpwr_low_alarm);
		sfp_hwmon_calibrate_tx_घातer(sfp, value);
		वापस 0;

	हाल hwmon_घातer_min:
		*value = be16_to_cpu(sfp->diag.txpwr_low_warn);
		sfp_hwmon_calibrate_tx_घातer(sfp, value);
		वापस 0;

	हाल hwmon_घातer_max:
		*value = be16_to_cpu(sfp->diag.txpwr_high_warn);
		sfp_hwmon_calibrate_tx_घातer(sfp, value);
		वापस 0;

	हाल hwmon_घातer_crit:
		*value = be16_to_cpu(sfp->diag.txpwr_high_alarm);
		sfp_hwmon_calibrate_tx_घातer(sfp, value);
		वापस 0;

	हाल hwmon_घातer_lcrit_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_ALARM0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_ALARM0_TXPWR_LOW);
		वापस 0;

	हाल hwmon_घातer_min_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_WARN0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_WARN0_TXPWR_LOW);
		वापस 0;

	हाल hwmon_घातer_max_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_WARN0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_WARN0_TXPWR_HIGH);
		वापस 0;

	हाल hwmon_घातer_crit_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_ALARM0, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_ALARM0_TXPWR_HIGH);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक sfp_hwmon_rx_घातer(काष्ठा sfp *sfp, u32 attr, दीर्घ *value)
अणु
	u8 status;
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_घातer_input:
		वापस sfp_hwmon_पढ़ो_rx_घातer(sfp, SFP_RX_POWER, value);

	हाल hwmon_घातer_lcrit:
		*value = be16_to_cpu(sfp->diag.rxpwr_low_alarm);
		sfp_hwmon_to_rx_घातer(value);
		वापस 0;

	हाल hwmon_घातer_min:
		*value = be16_to_cpu(sfp->diag.rxpwr_low_warn);
		sfp_hwmon_to_rx_घातer(value);
		वापस 0;

	हाल hwmon_घातer_max:
		*value = be16_to_cpu(sfp->diag.rxpwr_high_warn);
		sfp_hwmon_to_rx_घातer(value);
		वापस 0;

	हाल hwmon_घातer_crit:
		*value = be16_to_cpu(sfp->diag.rxpwr_high_alarm);
		sfp_hwmon_to_rx_घातer(value);
		वापस 0;

	हाल hwmon_घातer_lcrit_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_ALARM1, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_ALARM1_RXPWR_LOW);
		वापस 0;

	हाल hwmon_घातer_min_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_WARN1, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_WARN1_RXPWR_LOW);
		वापस 0;

	हाल hwmon_घातer_max_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_WARN1, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_WARN1_RXPWR_HIGH);
		वापस 0;

	हाल hwmon_घातer_crit_alarm:
		err = sfp_पढ़ो(sfp, true, SFP_ALARM1, &status, माप(status));
		अगर (err < 0)
			वापस err;

		*value = !!(status & SFP_ALARM1_RXPWR_HIGH);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक sfp_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			  u32 attr, पूर्णांक channel, दीर्घ *value)
अणु
	काष्ठा sfp *sfp = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_temp:
		वापस sfp_hwmon_temp(sfp, attr, value);
	हाल hwmon_in:
		वापस sfp_hwmon_vcc(sfp, attr, value);
	हाल hwmon_curr:
		वापस sfp_hwmon_bias(sfp, attr, value);
	हाल hwmon_घातer:
		चयन (channel) अणु
		हाल 0:
			वापस sfp_hwmon_tx_घातer(sfp, attr, value);
		हाल 1:
			वापस sfp_hwmon_rx_घातer(sfp, attr, value);
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *स्थिर sfp_hwmon_घातer_labels[] = अणु
	"TX_power",
	"RX_power",
पूर्ण;

अटल पूर्णांक sfp_hwmon_पढ़ो_string(काष्ठा device *dev,
				 क्रमागत hwmon_sensor_types type,
				 u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_label:
			*str = "bias";
			वापस 0;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_label:
			*str = "temperature";
			वापस 0;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_label:
			*str = "VCC";
			वापस 0;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल hwmon_घातer:
		चयन (attr) अणु
		हाल hwmon_घातer_label:
			*str = sfp_hwmon_घातer_labels[channel];
			वापस 0;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops sfp_hwmon_ops = अणु
	.is_visible = sfp_hwmon_is_visible,
	.पढ़ो = sfp_hwmon_पढ़ो,
	.पढ़ो_string = sfp_hwmon_पढ़ो_string,
पूर्ण;

अटल u32 sfp_hwmon_chip_config[] = अणु
	HWMON_C_REGISTER_TZ,
	0,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info sfp_hwmon_chip = अणु
	.type = hwmon_chip,
	.config = sfp_hwmon_chip_config,
पूर्ण;

अटल u32 sfp_hwmon_temp_config[] = अणु
	HWMON_T_INPUT |
	HWMON_T_MAX | HWMON_T_MIN |
	HWMON_T_MAX_ALARM | HWMON_T_MIN_ALARM |
	HWMON_T_CRIT | HWMON_T_LCRIT |
	HWMON_T_CRIT_ALARM | HWMON_T_LCRIT_ALARM |
	HWMON_T_LABEL,
	0,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info sfp_hwmon_temp_channel_info = अणु
	.type = hwmon_temp,
	.config = sfp_hwmon_temp_config,
पूर्ण;

अटल u32 sfp_hwmon_vcc_config[] = अणु
	HWMON_I_INPUT |
	HWMON_I_MAX | HWMON_I_MIN |
	HWMON_I_MAX_ALARM | HWMON_I_MIN_ALARM |
	HWMON_I_CRIT | HWMON_I_LCRIT |
	HWMON_I_CRIT_ALARM | HWMON_I_LCRIT_ALARM |
	HWMON_I_LABEL,
	0,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info sfp_hwmon_vcc_channel_info = अणु
	.type = hwmon_in,
	.config = sfp_hwmon_vcc_config,
पूर्ण;

अटल u32 sfp_hwmon_bias_config[] = अणु
	HWMON_C_INPUT |
	HWMON_C_MAX | HWMON_C_MIN |
	HWMON_C_MAX_ALARM | HWMON_C_MIN_ALARM |
	HWMON_C_CRIT | HWMON_C_LCRIT |
	HWMON_C_CRIT_ALARM | HWMON_C_LCRIT_ALARM |
	HWMON_C_LABEL,
	0,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info sfp_hwmon_bias_channel_info = अणु
	.type = hwmon_curr,
	.config = sfp_hwmon_bias_config,
पूर्ण;

अटल u32 sfp_hwmon_घातer_config[] = अणु
	/* Transmit घातer */
	HWMON_P_INPUT |
	HWMON_P_MAX | HWMON_P_MIN |
	HWMON_P_MAX_ALARM | HWMON_P_MIN_ALARM |
	HWMON_P_CRIT | HWMON_P_LCRIT |
	HWMON_P_CRIT_ALARM | HWMON_P_LCRIT_ALARM |
	HWMON_P_LABEL,
	/* Receive घातer */
	HWMON_P_INPUT |
	HWMON_P_MAX | HWMON_P_MIN |
	HWMON_P_MAX_ALARM | HWMON_P_MIN_ALARM |
	HWMON_P_CRIT | HWMON_P_LCRIT |
	HWMON_P_CRIT_ALARM | HWMON_P_LCRIT_ALARM |
	HWMON_P_LABEL,
	0,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info sfp_hwmon_घातer_channel_info = अणु
	.type = hwmon_घातer,
	.config = sfp_hwmon_घातer_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *sfp_hwmon_info[] = अणु
	&sfp_hwmon_chip,
	&sfp_hwmon_vcc_channel_info,
	&sfp_hwmon_temp_channel_info,
	&sfp_hwmon_bias_channel_info,
	&sfp_hwmon_घातer_channel_info,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info sfp_hwmon_chip_info = अणु
	.ops = &sfp_hwmon_ops,
	.info = sfp_hwmon_info,
पूर्ण;

अटल व्योम sfp_hwmon_probe(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sfp *sfp = container_of(work, काष्ठा sfp, hwmon_probe.work);
	पूर्णांक err, i;

	/* hwmon पूर्णांकerface needs to access 16bit रेजिस्टरs in atomic way to
	 * guarantee coherency of the diagnostic monitoring data. If it is not
	 * possible to guarantee coherency because EEPROM is broken in such way
	 * that करोes not support atomic 16bit पढ़ो operation then we have to
	 * skip registration of hwmon device.
	 */
	अगर (sfp->i2c_block_size < 2) अणु
		dev_info(sfp->dev,
			 "skipping hwmon device registration due to broken EEPROM\n");
		dev_info(sfp->dev,
			 "diagnostic EEPROM area cannot be read atomically to guarantee data coherency\n");
		वापस;
	पूर्ण

	err = sfp_पढ़ो(sfp, true, 0, &sfp->diag, माप(sfp->diag));
	अगर (err < 0) अणु
		अगर (sfp->hwmon_tries--) अणु
			mod_delayed_work(प्रणाली_wq, &sfp->hwmon_probe,
					 T_PROBE_RETRY_SLOW);
		पूर्ण अन्यथा अणु
			dev_warn(sfp->dev, "hwmon probe failed: %d\n", err);
		पूर्ण
		वापस;
	पूर्ण

	sfp->hwmon_name = kstrdup(dev_name(sfp->dev), GFP_KERNEL);
	अगर (!sfp->hwmon_name) अणु
		dev_err(sfp->dev, "out of memory for hwmon name\n");
		वापस;
	पूर्ण

	क्रम (i = 0; sfp->hwmon_name[i]; i++)
		अगर (hwmon_is_bad_अक्षर(sfp->hwmon_name[i]))
			sfp->hwmon_name[i] = '_';

	sfp->hwmon_dev = hwmon_device_रेजिस्टर_with_info(sfp->dev,
							 sfp->hwmon_name, sfp,
							 &sfp_hwmon_chip_info,
							 शून्य);
	अगर (IS_ERR(sfp->hwmon_dev))
		dev_err(sfp->dev, "failed to register hwmon device: %ld\n",
			PTR_ERR(sfp->hwmon_dev));
पूर्ण

अटल पूर्णांक sfp_hwmon_insert(काष्ठा sfp *sfp)
अणु
	अगर (sfp->id.ext.sff8472_compliance == SFP_SFF8472_COMPLIANCE_NONE)
		वापस 0;

	अगर (!(sfp->id.ext.diagmon & SFP_DIAGMON_DDM))
		वापस 0;

	अगर (sfp->id.ext.diagmon & SFP_DIAGMON_ADDRMODE)
		/* This driver in general करोes not support address
		 * change.
		 */
		वापस 0;

	mod_delayed_work(प्रणाली_wq, &sfp->hwmon_probe, 1);
	sfp->hwmon_tries = R_PROBE_RETRY_SLOW;

	वापस 0;
पूर्ण

अटल व्योम sfp_hwmon_हटाओ(काष्ठा sfp *sfp)
अणु
	cancel_delayed_work_sync(&sfp->hwmon_probe);
	अगर (!IS_ERR_OR_शून्य(sfp->hwmon_dev)) अणु
		hwmon_device_unरेजिस्टर(sfp->hwmon_dev);
		sfp->hwmon_dev = शून्य;
		kमुक्त(sfp->hwmon_name);
	पूर्ण
पूर्ण

अटल पूर्णांक sfp_hwmon_init(काष्ठा sfp *sfp)
अणु
	INIT_DELAYED_WORK(&sfp->hwmon_probe, sfp_hwmon_probe);

	वापस 0;
पूर्ण

अटल व्योम sfp_hwmon_निकास(काष्ठा sfp *sfp)
अणु
	cancel_delayed_work_sync(&sfp->hwmon_probe);
पूर्ण
#अन्यथा
अटल पूर्णांक sfp_hwmon_insert(काष्ठा sfp *sfp)
अणु
	वापस 0;
पूर्ण

अटल व्योम sfp_hwmon_हटाओ(काष्ठा sfp *sfp)
अणु
पूर्ण

अटल पूर्णांक sfp_hwmon_init(काष्ठा sfp *sfp)
अणु
	वापस 0;
पूर्ण

अटल व्योम sfp_hwmon_निकास(काष्ठा sfp *sfp)
अणु
पूर्ण
#पूर्ण_अगर

/* Helpers */
अटल व्योम sfp_module_tx_disable(काष्ठा sfp *sfp)
अणु
	dev_dbg(sfp->dev, "tx disable %u -> %u\n",
		sfp->state & SFP_F_TX_DISABLE ? 1 : 0, 1);
	sfp->state |= SFP_F_TX_DISABLE;
	sfp_set_state(sfp, sfp->state);
पूर्ण

अटल व्योम sfp_module_tx_enable(काष्ठा sfp *sfp)
अणु
	dev_dbg(sfp->dev, "tx disable %u -> %u\n",
		sfp->state & SFP_F_TX_DISABLE ? 1 : 0, 0);
	sfp->state &= ~SFP_F_TX_DISABLE;
	sfp_set_state(sfp, sfp->state);
पूर्ण

#अगर IS_ENABLED(CONFIG_DEBUG_FS)
अटल पूर्णांक sfp_debug_state_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा sfp *sfp = s->निजी;

	seq_म_लिखो(s, "Module state: %s\n",
		   mod_state_to_str(sfp->sm_mod_state));
	seq_म_लिखो(s, "Module probe attempts: %d %d\n",
		   R_PROBE_RETRY_INIT - sfp->sm_mod_tries_init,
		   R_PROBE_RETRY_SLOW - sfp->sm_mod_tries);
	seq_म_लिखो(s, "Device state: %s\n",
		   dev_state_to_str(sfp->sm_dev_state));
	seq_म_लिखो(s, "Main state: %s\n",
		   sm_state_to_str(sfp->sm_state));
	seq_म_लिखो(s, "Fault recovery remaining retries: %d\n",
		   sfp->sm_fault_retries);
	seq_म_लिखो(s, "PHY probe remaining retries: %d\n",
		   sfp->sm_phy_retries);
	seq_म_लिखो(s, "moddef0: %d\n", !!(sfp->state & SFP_F_PRESENT));
	seq_म_लिखो(s, "rx_los: %d\n", !!(sfp->state & SFP_F_LOS));
	seq_म_लिखो(s, "tx_fault: %d\n", !!(sfp->state & SFP_F_TX_FAULT));
	seq_म_लिखो(s, "tx_disable: %d\n", !!(sfp->state & SFP_F_TX_DISABLE));
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(sfp_debug_state);

अटल व्योम sfp_debugfs_init(काष्ठा sfp *sfp)
अणु
	sfp->debugfs_dir = debugfs_create_dir(dev_name(sfp->dev), शून्य);

	debugfs_create_file("state", 0600, sfp->debugfs_dir, sfp,
			    &sfp_debug_state_fops);
पूर्ण

अटल व्योम sfp_debugfs_निकास(काष्ठा sfp *sfp)
अणु
	debugfs_हटाओ_recursive(sfp->debugfs_dir);
पूर्ण
#अन्यथा
अटल व्योम sfp_debugfs_init(काष्ठा sfp *sfp)
अणु
पूर्ण

अटल व्योम sfp_debugfs_निकास(काष्ठा sfp *sfp)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम sfp_module_tx_fault_reset(काष्ठा sfp *sfp)
अणु
	अचिन्हित पूर्णांक state = sfp->state;

	अगर (state & SFP_F_TX_DISABLE)
		वापस;

	sfp_set_state(sfp, state | SFP_F_TX_DISABLE);

	udelay(T_RESET_US);

	sfp_set_state(sfp, state);
पूर्ण

/* SFP state machine */
अटल व्योम sfp_sm_set_समयr(काष्ठा sfp *sfp, अचिन्हित पूर्णांक समयout)
अणु
	अगर (समयout)
		mod_delayed_work(प्रणाली_घातer_efficient_wq, &sfp->समयout,
				 समयout);
	अन्यथा
		cancel_delayed_work(&sfp->समयout);
पूर्ण

अटल व्योम sfp_sm_next(काष्ठा sfp *sfp, अचिन्हित पूर्णांक state,
			अचिन्हित पूर्णांक समयout)
अणु
	sfp->sm_state = state;
	sfp_sm_set_समयr(sfp, समयout);
पूर्ण

अटल व्योम sfp_sm_mod_next(काष्ठा sfp *sfp, अचिन्हित पूर्णांक state,
			    अचिन्हित पूर्णांक समयout)
अणु
	sfp->sm_mod_state = state;
	sfp_sm_set_समयr(sfp, समयout);
पूर्ण

अटल व्योम sfp_sm_phy_detach(काष्ठा sfp *sfp)
अणु
	sfp_हटाओ_phy(sfp->sfp_bus);
	phy_device_हटाओ(sfp->mod_phy);
	phy_device_मुक्त(sfp->mod_phy);
	sfp->mod_phy = शून्य;
पूर्ण

अटल पूर्णांक sfp_sm_probe_phy(काष्ठा sfp *sfp, bool is_c45)
अणु
	काष्ठा phy_device *phy;
	पूर्णांक err;

	phy = get_phy_device(sfp->i2c_mii, SFP_PHY_ADDR, is_c45);
	अगर (phy == ERR_PTR(-ENODEV))
		वापस PTR_ERR(phy);
	अगर (IS_ERR(phy)) अणु
		dev_err(sfp->dev, "mdiobus scan returned %ld\n", PTR_ERR(phy));
		वापस PTR_ERR(phy);
	पूर्ण

	err = phy_device_रेजिस्टर(phy);
	अगर (err) अणु
		phy_device_मुक्त(phy);
		dev_err(sfp->dev, "phy_device_register failed: %d\n", err);
		वापस err;
	पूर्ण

	err = sfp_add_phy(sfp->sfp_bus, phy);
	अगर (err) अणु
		phy_device_हटाओ(phy);
		phy_device_मुक्त(phy);
		dev_err(sfp->dev, "sfp_add_phy failed: %d\n", err);
		वापस err;
	पूर्ण

	sfp->mod_phy = phy;

	वापस 0;
पूर्ण

अटल व्योम sfp_sm_link_up(काष्ठा sfp *sfp)
अणु
	sfp_link_up(sfp->sfp_bus);
	sfp_sm_next(sfp, SFP_S_LINK_UP, 0);
पूर्ण

अटल व्योम sfp_sm_link_करोwn(काष्ठा sfp *sfp)
अणु
	sfp_link_करोwn(sfp->sfp_bus);
पूर्ण

अटल व्योम sfp_sm_link_check_los(काष्ठा sfp *sfp)
अणु
	स्थिर __be16 los_inverted = cpu_to_be16(SFP_OPTIONS_LOS_INVERTED);
	स्थिर __be16 los_normal = cpu_to_be16(SFP_OPTIONS_LOS_NORMAL);
	__be16 los_options = sfp->id.ext.options & (los_inverted | los_normal);
	bool los = false;

	/* If neither SFP_OPTIONS_LOS_INVERTED nor SFP_OPTIONS_LOS_NORMAL
	 * are set, we assume that no LOS संकेत is available. If both are
	 * set, we assume LOS is not implemented (and is meaningless.)
	 */
	अगर (los_options == los_inverted)
		los = !(sfp->state & SFP_F_LOS);
	अन्यथा अगर (los_options == los_normal)
		los = !!(sfp->state & SFP_F_LOS);

	अगर (los)
		sfp_sm_next(sfp, SFP_S_WAIT_LOS, 0);
	अन्यथा
		sfp_sm_link_up(sfp);
पूर्ण

अटल bool sfp_los_event_active(काष्ठा sfp *sfp, अचिन्हित पूर्णांक event)
अणु
	स्थिर __be16 los_inverted = cpu_to_be16(SFP_OPTIONS_LOS_INVERTED);
	स्थिर __be16 los_normal = cpu_to_be16(SFP_OPTIONS_LOS_NORMAL);
	__be16 los_options = sfp->id.ext.options & (los_inverted | los_normal);

	वापस (los_options == los_inverted && event == SFP_E_LOS_LOW) ||
	       (los_options == los_normal && event == SFP_E_LOS_HIGH);
पूर्ण

अटल bool sfp_los_event_inactive(काष्ठा sfp *sfp, अचिन्हित पूर्णांक event)
अणु
	स्थिर __be16 los_inverted = cpu_to_be16(SFP_OPTIONS_LOS_INVERTED);
	स्थिर __be16 los_normal = cpu_to_be16(SFP_OPTIONS_LOS_NORMAL);
	__be16 los_options = sfp->id.ext.options & (los_inverted | los_normal);

	वापस (los_options == los_inverted && event == SFP_E_LOS_HIGH) ||
	       (los_options == los_normal && event == SFP_E_LOS_LOW);
पूर्ण

अटल व्योम sfp_sm_fault(काष्ठा sfp *sfp, अचिन्हित पूर्णांक next_state, bool warn)
अणु
	अगर (sfp->sm_fault_retries && !--sfp->sm_fault_retries) अणु
		dev_err(sfp->dev,
			"module persistently indicates fault, disabling\n");
		sfp_sm_next(sfp, SFP_S_TX_DISABLE, 0);
	पूर्ण अन्यथा अणु
		अगर (warn)
			dev_err(sfp->dev, "module transmit fault indicated\n");

		sfp_sm_next(sfp, next_state, T_FAULT_RECOVER);
	पूर्ण
पूर्ण

/* Probe a SFP क्रम a PHY device अगर the module supports copper - the PHY
 * normally sits at I2C bus address 0x56, and may either be a clause 22
 * or clause 45 PHY.
 *
 * Clause 22 copper SFP modules normally operate in Cisco SGMII mode with
 * negotiation enabled, but some may be in 1000base-X - which is क्रम the
 * PHY driver to determine.
 *
 * Clause 45 copper SFP+ modules (10G) appear to चयन their पूर्णांकerface
 * mode according to the negotiated line speed.
 */
अटल पूर्णांक sfp_sm_probe_क्रम_phy(काष्ठा sfp *sfp)
अणु
	पूर्णांक err = 0;

	चयन (sfp->id.base.extended_cc) अणु
	हाल SFF8024_ECC_10GBASE_T_SFI:
	हाल SFF8024_ECC_10GBASE_T_SR:
	हाल SFF8024_ECC_5GBASE_T:
	हाल SFF8024_ECC_2_5GBASE_T:
		err = sfp_sm_probe_phy(sfp, true);
		अवरोध;

	शेष:
		अगर (sfp->id.base.e1000_base_t)
			err = sfp_sm_probe_phy(sfp, false);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक sfp_module_parse_घातer(काष्ठा sfp *sfp)
अणु
	u32 घातer_mW = 1000;

	अगर (sfp->id.ext.options & cpu_to_be16(SFP_OPTIONS_POWER_DECL))
		घातer_mW = 1500;
	अगर (sfp->id.ext.options & cpu_to_be16(SFP_OPTIONS_HIGH_POWER_LEVEL))
		घातer_mW = 2000;

	अगर (घातer_mW > sfp->max_घातer_mW) अणु
		/* Module घातer specअगरication exceeds the allowed maximum. */
		अगर (sfp->id.ext.sff8472_compliance ==
			SFP_SFF8472_COMPLIANCE_NONE &&
		    !(sfp->id.ext.diagmon & SFP_DIAGMON_DDM)) अणु
			/* The module appears not to implement bus address
			 * 0xa2, so assume that the module घातers up in the
			 * indicated mode.
			 */
			dev_err(sfp->dev,
				"Host does not support %u.%uW modules\n",
				घातer_mW / 1000, (घातer_mW / 100) % 10);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			dev_warn(sfp->dev,
				 "Host does not support %u.%uW modules, module left in power mode 1\n",
				 घातer_mW / 1000, (घातer_mW / 100) % 10);
			वापस 0;
		पूर्ण
	पूर्ण

	/* If the module requires a higher घातer mode, but also requires
	 * an address change sequence, warn the user that the module may
	 * not be functional.
	 */
	अगर (sfp->id.ext.diagmon & SFP_DIAGMON_ADDRMODE && घातer_mW > 1000) अणु
		dev_warn(sfp->dev,
			 "Address Change Sequence not supported but module requires %u.%uW, module may not be functional\n",
			 घातer_mW / 1000, (घातer_mW / 100) % 10);
		वापस 0;
	पूर्ण

	sfp->module_घातer_mW = घातer_mW;

	वापस 0;
पूर्ण

अटल पूर्णांक sfp_sm_mod_hघातer(काष्ठा sfp *sfp, bool enable)
अणु
	u8 val;
	पूर्णांक err;

	err = sfp_पढ़ो(sfp, true, SFP_EXT_STATUS, &val, माप(val));
	अगर (err != माप(val)) अणु
		dev_err(sfp->dev, "Failed to read EEPROM: %d\n", err);
		वापस -EAGAIN;
	पूर्ण

	/* DM7052 reports as a high घातer module, responds to पढ़ोs (with
	 * all bytes 0xff) at 0x51 but करोes not accept ग_लिखोs.  In any हाल,
	 * अगर the bit is alपढ़ोy set, we're alपढ़ोy in high घातer mode.
	 */
	अगर (!!(val & BIT(0)) == enable)
		वापस 0;

	अगर (enable)
		val |= BIT(0);
	अन्यथा
		val &= ~BIT(0);

	err = sfp_ग_लिखो(sfp, true, SFP_EXT_STATUS, &val, माप(val));
	अगर (err != माप(val)) अणु
		dev_err(sfp->dev, "Failed to write EEPROM: %d\n", err);
		वापस -EAGAIN;
	पूर्ण

	अगर (enable)
		dev_info(sfp->dev, "Module switched to %u.%uW power level\n",
			 sfp->module_घातer_mW / 1000,
			 (sfp->module_घातer_mW / 100) % 10);

	वापस 0;
पूर्ण

/* GPON modules based on Realtek RTL8672 and RTL9601C chips (e.g. V-SOL
 * V2801F, CarlitoxxPro CPGOS03-0490, Ubiquiti U-Fiber Instant, ...) करो
 * not support multibyte पढ़ोs from the EEPROM. Each multi-byte पढ़ो
 * operation वापसs just one byte of EEPROM followed by zeros. There is
 * no way to identअगरy which modules are using Realtek RTL8672 and RTL9601C
 * chips. Moreover every OEM of V-SOL V2801F module माला_दो its own venकरोr
 * name and venकरोr id पूर्णांकo EEPROM, so there is even no way to detect अगर
 * module is V-SOL V2801F. Thereक्रमe check क्रम those zeros in the पढ़ो
 * data and then based on check चयन to पढ़ोing EEPROM to one byte
 * at a समय.
 */
अटल bool sfp_id_needs_byte_io(काष्ठा sfp *sfp, व्योम *buf, माप_प्रकार len)
अणु
	माप_प्रकार i, block_size = sfp->i2c_block_size;

	/* Alपढ़ोy using byte IO */
	अगर (block_size == 1)
		वापस false;

	क्रम (i = 1; i < len; i += block_size) अणु
		अगर (स_प्रथम_inv(buf + i, '\0', min(block_size - 1, len - i)))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक sfp_cotsworks_fixup_check(काष्ठा sfp *sfp, काष्ठा sfp_eeprom_id *id)
अणु
	u8 check;
	पूर्णांक err;

	अगर (id->base.phys_id != SFF8024_ID_SFF_8472 ||
	    id->base.phys_ext_id != SFP_PHYS_EXT_ID_SFP ||
	    id->base.connector != SFF8024_CONNECTOR_LC) अणु
		dev_warn(sfp->dev, "Rewriting fiber module EEPROM with corrected values\n");
		id->base.phys_id = SFF8024_ID_SFF_8472;
		id->base.phys_ext_id = SFP_PHYS_EXT_ID_SFP;
		id->base.connector = SFF8024_CONNECTOR_LC;
		err = sfp_ग_लिखो(sfp, false, SFP_PHYS_ID, &id->base, 3);
		अगर (err != 3) अणु
			dev_err(sfp->dev, "Failed to rewrite module EEPROM: %d\n", err);
			वापस err;
		पूर्ण

		/* Cotsworks modules have been found to require a delay between ग_लिखो operations. */
		mdelay(50);

		/* Update base काष्ठाure checksum */
		check = sfp_check(&id->base, माप(id->base) - 1);
		err = sfp_ग_लिखो(sfp, false, SFP_CC_BASE, &check, 1);
		अगर (err != 1) अणु
			dev_err(sfp->dev, "Failed to update base structure checksum in fiber module EEPROM: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sfp_sm_mod_probe(काष्ठा sfp *sfp, bool report)
अणु
	/* SFP module inserted - पढ़ो I2C data */
	काष्ठा sfp_eeprom_id id;
	bool cotsworks_sfbg;
	bool cotsworks;
	u8 check;
	पूर्णांक ret;

	/* Some SFP modules and also some Linux I2C drivers करो not like पढ़ोs
	 * दीर्घer than 16 bytes, so पढ़ो the EEPROM in chunks of 16 bytes at
	 * a समय.
	 */
	sfp->i2c_block_size = 16;

	ret = sfp_पढ़ो(sfp, false, 0, &id.base, माप(id.base));
	अगर (ret < 0) अणु
		अगर (report)
			dev_err(sfp->dev, "failed to read EEPROM: %d\n", ret);
		वापस -EAGAIN;
	पूर्ण

	अगर (ret != माप(id.base)) अणु
		dev_err(sfp->dev, "EEPROM short read: %d\n", ret);
		वापस -EAGAIN;
	पूर्ण

	/* Some SFP modules (e.g. Nokia 3FE46541AA) lock up अगर पढ़ो from
	 * address 0x51 is just one byte at a समय. Also SFF-8472 requires
	 * that EEPROM supports atomic 16bit पढ़ो operation क्रम diagnostic
	 * fields, so करो not चयन to one byte पढ़ोing at a समय unless it
	 * is really required and we have no other option.
	 */
	अगर (sfp_id_needs_byte_io(sfp, &id.base, माप(id.base))) अणु
		dev_info(sfp->dev,
			 "Detected broken RTL8672/RTL9601C emulated EEPROM\n");
		dev_info(sfp->dev,
			 "Switching to reading EEPROM to one byte at a time\n");
		sfp->i2c_block_size = 1;

		ret = sfp_पढ़ो(sfp, false, 0, &id.base, माप(id.base));
		अगर (ret < 0) अणु
			अगर (report)
				dev_err(sfp->dev, "failed to read EEPROM: %d\n",
					ret);
			वापस -EAGAIN;
		पूर्ण

		अगर (ret != माप(id.base)) अणु
			dev_err(sfp->dev, "EEPROM short read: %d\n", ret);
			वापस -EAGAIN;
		पूर्ण
	पूर्ण

	/* Cotsworks करो not seem to update the checksums when they
	 * करो the final programming with the final module part number,
	 * serial number and date code.
	 */
	cotsworks = !स_भेद(id.base.venकरोr_name, "COTSWORKS       ", 16);
	cotsworks_sfbg = !स_भेद(id.base.venकरोr_pn, "SFBG", 4);

	/* Cotsworks SFF module EEPROM करो not always have valid phys_id,
	 * phys_ext_id, and connector bytes.  Reग_लिखो SFF EEPROM bytes अगर
	 * Cotsworks PN matches and bytes are not correct.
	 */
	अगर (cotsworks && cotsworks_sfbg) अणु
		ret = sfp_cotsworks_fixup_check(sfp, &id);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Validate the checksum over the base काष्ठाure */
	check = sfp_check(&id.base, माप(id.base) - 1);
	अगर (check != id.base.cc_base) अणु
		अगर (cotsworks) अणु
			dev_warn(sfp->dev,
				 "EEPROM base structure checksum failure (0x%02x != 0x%02x)\n",
				 check, id.base.cc_base);
		पूर्ण अन्यथा अणु
			dev_err(sfp->dev,
				"EEPROM base structure checksum failure: 0x%02x != 0x%02x\n",
				check, id.base.cc_base);
			prपूर्णांक_hex_dump(KERN_ERR, "sfp EE: ", DUMP_PREFIX_OFFSET,
				       16, 1, &id, माप(id), true);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = sfp_पढ़ो(sfp, false, SFP_CC_BASE + 1, &id.ext, माप(id.ext));
	अगर (ret < 0) अणु
		अगर (report)
			dev_err(sfp->dev, "failed to read EEPROM: %d\n", ret);
		वापस -EAGAIN;
	पूर्ण

	अगर (ret != माप(id.ext)) अणु
		dev_err(sfp->dev, "EEPROM short read: %d\n", ret);
		वापस -EAGAIN;
	पूर्ण

	check = sfp_check(&id.ext, माप(id.ext) - 1);
	अगर (check != id.ext.cc_ext) अणु
		अगर (cotsworks) अणु
			dev_warn(sfp->dev,
				 "EEPROM extended structure checksum failure (0x%02x != 0x%02x)\n",
				 check, id.ext.cc_ext);
		पूर्ण अन्यथा अणु
			dev_err(sfp->dev,
				"EEPROM extended structure checksum failure: 0x%02x != 0x%02x\n",
				check, id.ext.cc_ext);
			prपूर्णांक_hex_dump(KERN_ERR, "sfp EE: ", DUMP_PREFIX_OFFSET,
				       16, 1, &id, माप(id), true);
			स_रखो(&id.ext, 0, माप(id.ext));
		पूर्ण
	पूर्ण

	sfp->id = id;

	dev_info(sfp->dev, "module %.*s %.*s rev %.*s sn %.*s dc %.*s\n",
		 (पूर्णांक)माप(id.base.venकरोr_name), id.base.venकरोr_name,
		 (पूर्णांक)माप(id.base.venकरोr_pn), id.base.venकरोr_pn,
		 (पूर्णांक)माप(id.base.venकरोr_rev), id.base.venकरोr_rev,
		 (पूर्णांक)माप(id.ext.venकरोr_sn), id.ext.venकरोr_sn,
		 (पूर्णांक)माप(id.ext.datecode), id.ext.datecode);

	/* Check whether we support this module */
	अगर (!sfp->type->module_supported(&id)) अणु
		dev_err(sfp->dev,
			"module is not supported - phys id 0x%02x 0x%02x\n",
			sfp->id.base.phys_id, sfp->id.base.phys_ext_id);
		वापस -EINVAL;
	पूर्ण

	/* If the module requires address swap mode, warn about it */
	अगर (sfp->id.ext.diagmon & SFP_DIAGMON_ADDRMODE)
		dev_warn(sfp->dev,
			 "module address swap to access page 0xA2 is not supported.\n");

	/* Parse the module घातer requirement */
	ret = sfp_module_parse_घातer(sfp);
	अगर (ret < 0)
		वापस ret;

	अगर (!स_भेद(id.base.venकरोr_name, "ALCATELLUCENT   ", 16) &&
	    !स_भेद(id.base.venकरोr_pn, "3FE46541AA      ", 16))
		sfp->module_t_start_up = T_START_UP_BAD_GPON;
	अन्यथा
		sfp->module_t_start_up = T_START_UP;

	वापस 0;
पूर्ण

अटल व्योम sfp_sm_mod_हटाओ(काष्ठा sfp *sfp)
अणु
	अगर (sfp->sm_mod_state > SFP_MOD_WAITDEV)
		sfp_module_हटाओ(sfp->sfp_bus);

	sfp_hwmon_हटाओ(sfp);

	स_रखो(&sfp->id, 0, माप(sfp->id));
	sfp->module_घातer_mW = 0;

	dev_info(sfp->dev, "module removed\n");
पूर्ण

/* This state machine tracks the upstream's state */
अटल व्योम sfp_sm_device(काष्ठा sfp *sfp, अचिन्हित पूर्णांक event)
अणु
	चयन (sfp->sm_dev_state) अणु
	शेष:
		अगर (event == SFP_E_DEV_ATTACH)
			sfp->sm_dev_state = SFP_DEV_DOWN;
		अवरोध;

	हाल SFP_DEV_DOWN:
		अगर (event == SFP_E_DEV_DETACH)
			sfp->sm_dev_state = SFP_DEV_DETACHED;
		अन्यथा अगर (event == SFP_E_DEV_UP)
			sfp->sm_dev_state = SFP_DEV_UP;
		अवरोध;

	हाल SFP_DEV_UP:
		अगर (event == SFP_E_DEV_DETACH)
			sfp->sm_dev_state = SFP_DEV_DETACHED;
		अन्यथा अगर (event == SFP_E_DEV_DOWN)
			sfp->sm_dev_state = SFP_DEV_DOWN;
		अवरोध;
	पूर्ण
पूर्ण

/* This state machine tracks the insert/हटाओ state of the module, probes
 * the on-board EEPROM, and sets up the घातer level.
 */
अटल व्योम sfp_sm_module(काष्ठा sfp *sfp, अचिन्हित पूर्णांक event)
अणु
	पूर्णांक err;

	/* Handle हटाओ event globally, it resets this state machine */
	अगर (event == SFP_E_REMOVE) अणु
		अगर (sfp->sm_mod_state > SFP_MOD_PROBE)
			sfp_sm_mod_हटाओ(sfp);
		sfp_sm_mod_next(sfp, SFP_MOD_EMPTY, 0);
		वापस;
	पूर्ण

	/* Handle device detach globally */
	अगर (sfp->sm_dev_state < SFP_DEV_DOWN &&
	    sfp->sm_mod_state > SFP_MOD_WAITDEV) अणु
		अगर (sfp->module_घातer_mW > 1000 &&
		    sfp->sm_mod_state > SFP_MOD_HPOWER)
			sfp_sm_mod_hघातer(sfp, false);
		sfp_sm_mod_next(sfp, SFP_MOD_WAITDEV, 0);
		वापस;
	पूर्ण

	चयन (sfp->sm_mod_state) अणु
	शेष:
		अगर (event == SFP_E_INSERT) अणु
			sfp_sm_mod_next(sfp, SFP_MOD_PROBE, T_SERIAL);
			sfp->sm_mod_tries_init = R_PROBE_RETRY_INIT;
			sfp->sm_mod_tries = R_PROBE_RETRY_SLOW;
		पूर्ण
		अवरोध;

	हाल SFP_MOD_PROBE:
		/* Wait क्रम T_PROBE_INIT to समय out */
		अगर (event != SFP_E_TIMEOUT)
			अवरोध;

		err = sfp_sm_mod_probe(sfp, sfp->sm_mod_tries == 1);
		अगर (err == -EAGAIN) अणु
			अगर (sfp->sm_mod_tries_init &&
			   --sfp->sm_mod_tries_init) अणु
				sfp_sm_set_समयr(sfp, T_PROBE_RETRY_INIT);
				अवरोध;
			पूर्ण अन्यथा अगर (sfp->sm_mod_tries && --sfp->sm_mod_tries) अणु
				अगर (sfp->sm_mod_tries == R_PROBE_RETRY_SLOW - 1)
					dev_warn(sfp->dev,
						 "please wait, module slow to respond\n");
				sfp_sm_set_समयr(sfp, T_PROBE_RETRY_SLOW);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (err < 0) अणु
			sfp_sm_mod_next(sfp, SFP_MOD_ERROR, 0);
			अवरोध;
		पूर्ण

		err = sfp_hwmon_insert(sfp);
		अगर (err)
			dev_warn(sfp->dev, "hwmon probe failed: %d\n", err);

		sfp_sm_mod_next(sfp, SFP_MOD_WAITDEV, 0);
		fallthrough;
	हाल SFP_MOD_WAITDEV:
		/* Ensure that the device is attached beक्रमe proceeding */
		अगर (sfp->sm_dev_state < SFP_DEV_DOWN)
			अवरोध;

		/* Report the module insertion to the upstream device */
		err = sfp_module_insert(sfp->sfp_bus, &sfp->id);
		अगर (err < 0) अणु
			sfp_sm_mod_next(sfp, SFP_MOD_ERROR, 0);
			अवरोध;
		पूर्ण

		/* If this is a घातer level 1 module, we are करोne */
		अगर (sfp->module_घातer_mW <= 1000)
			जाओ insert;

		sfp_sm_mod_next(sfp, SFP_MOD_HPOWER, 0);
		fallthrough;
	हाल SFP_MOD_HPOWER:
		/* Enable high घातer mode */
		err = sfp_sm_mod_hघातer(sfp, true);
		अगर (err < 0) अणु
			अगर (err != -EAGAIN) अणु
				sfp_module_हटाओ(sfp->sfp_bus);
				sfp_sm_mod_next(sfp, SFP_MOD_ERROR, 0);
			पूर्ण अन्यथा अणु
				sfp_sm_set_समयr(sfp, T_PROBE_RETRY_INIT);
			पूर्ण
			अवरोध;
		पूर्ण

		sfp_sm_mod_next(sfp, SFP_MOD_WAITPWR, T_HPOWER_LEVEL);
		अवरोध;

	हाल SFP_MOD_WAITPWR:
		/* Wait क्रम T_HPOWER_LEVEL to समय out */
		अगर (event != SFP_E_TIMEOUT)
			अवरोध;

	insert:
		sfp_sm_mod_next(sfp, SFP_MOD_PRESENT, 0);
		अवरोध;

	हाल SFP_MOD_PRESENT:
	हाल SFP_MOD_ERROR:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sfp_sm_मुख्य(काष्ठा sfp *sfp, अचिन्हित पूर्णांक event)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	/* Some events are global */
	अगर (sfp->sm_state != SFP_S_DOWN &&
	    (sfp->sm_mod_state != SFP_MOD_PRESENT ||
	     sfp->sm_dev_state != SFP_DEV_UP)) अणु
		अगर (sfp->sm_state == SFP_S_LINK_UP &&
		    sfp->sm_dev_state == SFP_DEV_UP)
			sfp_sm_link_करोwn(sfp);
		अगर (sfp->sm_state > SFP_S_INIT)
			sfp_module_stop(sfp->sfp_bus);
		अगर (sfp->mod_phy)
			sfp_sm_phy_detach(sfp);
		sfp_module_tx_disable(sfp);
		sfp_soft_stop_poll(sfp);
		sfp_sm_next(sfp, SFP_S_DOWN, 0);
		वापस;
	पूर्ण

	/* The मुख्य state machine */
	चयन (sfp->sm_state) अणु
	हाल SFP_S_DOWN:
		अगर (sfp->sm_mod_state != SFP_MOD_PRESENT ||
		    sfp->sm_dev_state != SFP_DEV_UP)
			अवरोध;

		अगर (!(sfp->id.ext.diagmon & SFP_DIAGMON_ADDRMODE))
			sfp_soft_start_poll(sfp);

		sfp_module_tx_enable(sfp);

		/* Initialise the fault clearance retries */
		sfp->sm_fault_retries = N_FAULT_INIT;

		/* We need to check the TX_FAULT state, which is not defined
		 * जबतक TX_DISABLE is निश्चितed. The earliest we want to करो
		 * anything (such as probe क्रम a PHY) is 50ms.
		 */
		sfp_sm_next(sfp, SFP_S_WAIT, T_WAIT);
		अवरोध;

	हाल SFP_S_WAIT:
		अगर (event != SFP_E_TIMEOUT)
			अवरोध;

		अगर (sfp->state & SFP_F_TX_FAULT) अणु
			/* Wait up to t_init (SFF-8472) or t_start_up (SFF-8431)
			 * from the TX_DISABLE deनिश्चितion क्रम the module to
			 * initialise, which is indicated by TX_FAULT
			 * deनिश्चितing.
			 */
			समयout = sfp->module_t_start_up;
			अगर (समयout > T_WAIT)
				समयout -= T_WAIT;
			अन्यथा
				समयout = 1;

			sfp_sm_next(sfp, SFP_S_INIT, समयout);
		पूर्ण अन्यथा अणु
			/* TX_FAULT is not निश्चितed, assume the module has
			 * finished initialising.
			 */
			जाओ init_करोne;
		पूर्ण
		अवरोध;

	हाल SFP_S_INIT:
		अगर (event == SFP_E_TIMEOUT && sfp->state & SFP_F_TX_FAULT) अणु
			/* TX_FAULT is still निश्चितed after t_init or
			 * or t_start_up, so assume there is a fault.
			 */
			sfp_sm_fault(sfp, SFP_S_INIT_TX_FAULT,
				     sfp->sm_fault_retries == N_FAULT_INIT);
		पूर्ण अन्यथा अगर (event == SFP_E_TIMEOUT || event == SFP_E_TX_CLEAR) अणु
	init_करोne:
			sfp->sm_phy_retries = R_PHY_RETRY;
			जाओ phy_probe;
		पूर्ण
		अवरोध;

	हाल SFP_S_INIT_PHY:
		अगर (event != SFP_E_TIMEOUT)
			अवरोध;
	phy_probe:
		/* TX_FAULT deनिश्चितed or we समयd out with TX_FAULT
		 * clear.  Probe क्रम the PHY and check the LOS state.
		 */
		ret = sfp_sm_probe_क्रम_phy(sfp);
		अगर (ret == -ENODEV) अणु
			अगर (--sfp->sm_phy_retries) अणु
				sfp_sm_next(sfp, SFP_S_INIT_PHY, T_PHY_RETRY);
				अवरोध;
			पूर्ण अन्यथा अणु
				dev_info(sfp->dev, "no PHY detected\n");
			पूर्ण
		पूर्ण अन्यथा अगर (ret) अणु
			sfp_sm_next(sfp, SFP_S_FAIL, 0);
			अवरोध;
		पूर्ण
		अगर (sfp_module_start(sfp->sfp_bus)) अणु
			sfp_sm_next(sfp, SFP_S_FAIL, 0);
			अवरोध;
		पूर्ण
		sfp_sm_link_check_los(sfp);

		/* Reset the fault retry count */
		sfp->sm_fault_retries = N_FAULT;
		अवरोध;

	हाल SFP_S_INIT_TX_FAULT:
		अगर (event == SFP_E_TIMEOUT) अणु
			sfp_module_tx_fault_reset(sfp);
			sfp_sm_next(sfp, SFP_S_INIT, sfp->module_t_start_up);
		पूर्ण
		अवरोध;

	हाल SFP_S_WAIT_LOS:
		अगर (event == SFP_E_TX_FAULT)
			sfp_sm_fault(sfp, SFP_S_TX_FAULT, true);
		अन्यथा अगर (sfp_los_event_inactive(sfp, event))
			sfp_sm_link_up(sfp);
		अवरोध;

	हाल SFP_S_LINK_UP:
		अगर (event == SFP_E_TX_FAULT) अणु
			sfp_sm_link_करोwn(sfp);
			sfp_sm_fault(sfp, SFP_S_TX_FAULT, true);
		पूर्ण अन्यथा अगर (sfp_los_event_active(sfp, event)) अणु
			sfp_sm_link_करोwn(sfp);
			sfp_sm_next(sfp, SFP_S_WAIT_LOS, 0);
		पूर्ण
		अवरोध;

	हाल SFP_S_TX_FAULT:
		अगर (event == SFP_E_TIMEOUT) अणु
			sfp_module_tx_fault_reset(sfp);
			sfp_sm_next(sfp, SFP_S_REINIT, sfp->module_t_start_up);
		पूर्ण
		अवरोध;

	हाल SFP_S_REINIT:
		अगर (event == SFP_E_TIMEOUT && sfp->state & SFP_F_TX_FAULT) अणु
			sfp_sm_fault(sfp, SFP_S_TX_FAULT, false);
		पूर्ण अन्यथा अगर (event == SFP_E_TIMEOUT || event == SFP_E_TX_CLEAR) अणु
			dev_info(sfp->dev, "module transmit fault recovered\n");
			sfp_sm_link_check_los(sfp);
		पूर्ण
		अवरोध;

	हाल SFP_S_TX_DISABLE:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sfp_sm_event(काष्ठा sfp *sfp, अचिन्हित पूर्णांक event)
अणु
	mutex_lock(&sfp->sm_mutex);

	dev_dbg(sfp->dev, "SM: enter %s:%s:%s event %s\n",
		mod_state_to_str(sfp->sm_mod_state),
		dev_state_to_str(sfp->sm_dev_state),
		sm_state_to_str(sfp->sm_state),
		event_to_str(event));

	sfp_sm_device(sfp, event);
	sfp_sm_module(sfp, event);
	sfp_sm_मुख्य(sfp, event);

	dev_dbg(sfp->dev, "SM: exit %s:%s:%s\n",
		mod_state_to_str(sfp->sm_mod_state),
		dev_state_to_str(sfp->sm_dev_state),
		sm_state_to_str(sfp->sm_state));

	mutex_unlock(&sfp->sm_mutex);
पूर्ण

अटल व्योम sfp_attach(काष्ठा sfp *sfp)
अणु
	sfp_sm_event(sfp, SFP_E_DEV_ATTACH);
पूर्ण

अटल व्योम sfp_detach(काष्ठा sfp *sfp)
अणु
	sfp_sm_event(sfp, SFP_E_DEV_DETACH);
पूर्ण

अटल व्योम sfp_start(काष्ठा sfp *sfp)
अणु
	sfp_sm_event(sfp, SFP_E_DEV_UP);
पूर्ण

अटल व्योम sfp_stop(काष्ठा sfp *sfp)
अणु
	sfp_sm_event(sfp, SFP_E_DEV_DOWN);
पूर्ण

अटल पूर्णांक sfp_module_info(काष्ठा sfp *sfp, काष्ठा ethtool_modinfo *modinfo)
अणु
	/* locking... and check module is present */

	अगर (sfp->id.ext.sff8472_compliance &&
	    !(sfp->id.ext.diagmon & SFP_DIAGMON_ADDRMODE)) अणु
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
	पूर्ण अन्यथा अणु
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sfp_module_eeprom(काष्ठा sfp *sfp, काष्ठा ethtool_eeprom *ee,
			     u8 *data)
अणु
	अचिन्हित पूर्णांक first, last, len;
	पूर्णांक ret;

	अगर (ee->len == 0)
		वापस -EINVAL;

	first = ee->offset;
	last = ee->offset + ee->len;
	अगर (first < ETH_MODULE_SFF_8079_LEN) अणु
		len = min_t(अचिन्हित पूर्णांक, last, ETH_MODULE_SFF_8079_LEN);
		len -= first;

		ret = sfp_पढ़ो(sfp, false, first, data, len);
		अगर (ret < 0)
			वापस ret;

		first += len;
		data += len;
	पूर्ण
	अगर (first < ETH_MODULE_SFF_8472_LEN && last > ETH_MODULE_SFF_8079_LEN) अणु
		len = min_t(अचिन्हित पूर्णांक, last, ETH_MODULE_SFF_8472_LEN);
		len -= first;
		first -= ETH_MODULE_SFF_8079_LEN;

		ret = sfp_पढ़ो(sfp, true, first, data, len);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sfp_module_eeprom_by_page(काष्ठा sfp *sfp,
				     स्थिर काष्ठा ethtool_module_eeprom *page,
				     काष्ठा netlink_ext_ack *extack)
अणु
	अगर (page->bank) अणु
		NL_SET_ERR_MSG(extack, "Banks not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (page->page) अणु
		NL_SET_ERR_MSG(extack, "Only page 0 supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (page->i2c_address != 0x50 &&
	    page->i2c_address != 0x51) अणु
		NL_SET_ERR_MSG(extack, "Only address 0x50 and 0x51 supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस sfp_पढ़ो(sfp, page->i2c_address == 0x51, page->offset,
			page->data, page->length);
पूर्ण;

अटल स्थिर काष्ठा sfp_socket_ops sfp_module_ops = अणु
	.attach = sfp_attach,
	.detach = sfp_detach,
	.start = sfp_start,
	.stop = sfp_stop,
	.module_info = sfp_module_info,
	.module_eeprom = sfp_module_eeprom,
	.module_eeprom_by_page = sfp_module_eeprom_by_page,
पूर्ण;

अटल व्योम sfp_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sfp *sfp = container_of(work, काष्ठा sfp, समयout.work);

	rtnl_lock();
	sfp_sm_event(sfp, SFP_E_TIMEOUT);
	rtnl_unlock();
पूर्ण

अटल व्योम sfp_check_state(काष्ठा sfp *sfp)
अणु
	अचिन्हित पूर्णांक state, i, changed;

	mutex_lock(&sfp->st_mutex);
	state = sfp_get_state(sfp);
	changed = state ^ sfp->state;
	changed &= SFP_F_PRESENT | SFP_F_LOS | SFP_F_TX_FAULT;

	क्रम (i = 0; i < GPIO_MAX; i++)
		अगर (changed & BIT(i))
			dev_dbg(sfp->dev, "%s %u -> %u\n", gpio_of_names[i],
				!!(sfp->state & BIT(i)), !!(state & BIT(i)));

	state |= sfp->state & (SFP_F_TX_DISABLE | SFP_F_RATE_SELECT);
	sfp->state = state;

	rtnl_lock();
	अगर (changed & SFP_F_PRESENT)
		sfp_sm_event(sfp, state & SFP_F_PRESENT ?
				SFP_E_INSERT : SFP_E_REMOVE);

	अगर (changed & SFP_F_TX_FAULT)
		sfp_sm_event(sfp, state & SFP_F_TX_FAULT ?
				SFP_E_TX_FAULT : SFP_E_TX_CLEAR);

	अगर (changed & SFP_F_LOS)
		sfp_sm_event(sfp, state & SFP_F_LOS ?
				SFP_E_LOS_HIGH : SFP_E_LOS_LOW);
	rtnl_unlock();
	mutex_unlock(&sfp->st_mutex);
पूर्ण

अटल irqवापस_t sfp_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sfp *sfp = data;

	sfp_check_state(sfp);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sfp_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sfp *sfp = container_of(work, काष्ठा sfp, poll.work);

	sfp_check_state(sfp);

	अगर (sfp->state_soft_mask & (SFP_F_LOS | SFP_F_TX_FAULT) ||
	    sfp->need_poll)
		mod_delayed_work(प्रणाली_wq, &sfp->poll, poll_jअगरfies);
पूर्ण

अटल काष्ठा sfp *sfp_alloc(काष्ठा device *dev)
अणु
	काष्ठा sfp *sfp;

	sfp = kzalloc(माप(*sfp), GFP_KERNEL);
	अगर (!sfp)
		वापस ERR_PTR(-ENOMEM);

	sfp->dev = dev;

	mutex_init(&sfp->sm_mutex);
	mutex_init(&sfp->st_mutex);
	INIT_DELAYED_WORK(&sfp->poll, sfp_poll);
	INIT_DELAYED_WORK(&sfp->समयout, sfp_समयout);

	sfp_hwmon_init(sfp);

	वापस sfp;
पूर्ण

अटल व्योम sfp_cleanup(व्योम *data)
अणु
	काष्ठा sfp *sfp = data;

	sfp_hwmon_निकास(sfp);

	cancel_delayed_work_sync(&sfp->poll);
	cancel_delayed_work_sync(&sfp->समयout);
	अगर (sfp->i2c_mii) अणु
		mdiobus_unरेजिस्टर(sfp->i2c_mii);
		mdiobus_मुक्त(sfp->i2c_mii);
	पूर्ण
	अगर (sfp->i2c)
		i2c_put_adapter(sfp->i2c);
	kमुक्त(sfp);
पूर्ण

अटल पूर्णांक sfp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा sff_data *sff;
	काष्ठा i2c_adapter *i2c;
	अक्षर *sfp_irq_name;
	काष्ठा sfp *sfp;
	पूर्णांक err, i;

	sfp = sfp_alloc(&pdev->dev);
	अगर (IS_ERR(sfp))
		वापस PTR_ERR(sfp);

	platक्रमm_set_drvdata(pdev, sfp);

	err = devm_add_action(sfp->dev, sfp_cleanup, sfp);
	अगर (err < 0)
		वापस err;

	sff = sfp->type = &sfp_data;

	अगर (pdev->dev.of_node) अणु
		काष्ठा device_node *node = pdev->dev.of_node;
		स्थिर काष्ठा of_device_id *id;
		काष्ठा device_node *np;

		id = of_match_node(sfp_of_match, node);
		अगर (WARN_ON(!id))
			वापस -EINVAL;

		sff = sfp->type = id->data;

		np = of_parse_phandle(node, "i2c-bus", 0);
		अगर (!np) अणु
			dev_err(sfp->dev, "missing 'i2c-bus' property\n");
			वापस -ENODEV;
		पूर्ण

		i2c = of_find_i2c_adapter_by_node(np);
		of_node_put(np);
	पूर्ण अन्यथा अगर (has_acpi_companion(&pdev->dev)) अणु
		काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);
		काष्ठा fwnode_handle *fw = acpi_fwnode_handle(adev);
		काष्ठा fwnode_reference_args args;
		काष्ठा acpi_handle *acpi_handle;
		पूर्णांक ret;

		ret = acpi_node_get_property_reference(fw, "i2c-bus", 0, &args);
		अगर (ret || !is_acpi_device_node(args.fwnode)) अणु
			dev_err(&pdev->dev, "missing 'i2c-bus' property\n");
			वापस -ENODEV;
		पूर्ण

		acpi_handle = ACPI_HANDLE_FWNODE(args.fwnode);
		i2c = i2c_acpi_find_adapter_by_handle(acpi_handle);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (!i2c)
		वापस -EPROBE_DEFER;

	err = sfp_i2c_configure(sfp, i2c);
	अगर (err < 0) अणु
		i2c_put_adapter(i2c);
		वापस err;
	पूर्ण

	क्रम (i = 0; i < GPIO_MAX; i++)
		अगर (sff->gpios & BIT(i)) अणु
			sfp->gpio[i] = devm_gpiod_get_optional(sfp->dev,
					   gpio_of_names[i], gpio_flags[i]);
			अगर (IS_ERR(sfp->gpio[i]))
				वापस PTR_ERR(sfp->gpio[i]);
		पूर्ण

	sfp->get_state = sfp_gpio_get_state;
	sfp->set_state = sfp_gpio_set_state;

	/* Modules that have no detect संकेत are always present */
	अगर (!(sfp->gpio[GPIO_MODDEF0]))
		sfp->get_state = sff_gpio_get_state;

	device_property_पढ़ो_u32(&pdev->dev, "maximum-power-milliwatt",
				 &sfp->max_घातer_mW);
	अगर (!sfp->max_घातer_mW)
		sfp->max_घातer_mW = 1000;

	dev_info(sfp->dev, "Host maximum power %u.%uW\n",
		 sfp->max_घातer_mW / 1000, (sfp->max_घातer_mW / 100) % 10);

	/* Get the initial state, and always संकेत TX disable,
	 * since the network पूर्णांकerface will not be up.
	 */
	sfp->state = sfp_get_state(sfp) | SFP_F_TX_DISABLE;

	अगर (sfp->gpio[GPIO_RATE_SELECT] &&
	    gpiod_get_value_cansleep(sfp->gpio[GPIO_RATE_SELECT]))
		sfp->state |= SFP_F_RATE_SELECT;
	sfp_set_state(sfp, sfp->state);
	sfp_module_tx_disable(sfp);
	अगर (sfp->state & SFP_F_PRESENT) अणु
		rtnl_lock();
		sfp_sm_event(sfp, SFP_E_INSERT);
		rtnl_unlock();
	पूर्ण

	क्रम (i = 0; i < GPIO_MAX; i++) अणु
		अगर (gpio_flags[i] != GPIOD_IN || !sfp->gpio[i])
			जारी;

		sfp->gpio_irq[i] = gpiod_to_irq(sfp->gpio[i]);
		अगर (sfp->gpio_irq[i] < 0) अणु
			sfp->gpio_irq[i] = 0;
			sfp->need_poll = true;
			जारी;
		पूर्ण

		sfp_irq_name = devm_kaप्र_लिखो(sfp->dev, GFP_KERNEL,
					      "%s-%s", dev_name(sfp->dev),
					      gpio_of_names[i]);

		अगर (!sfp_irq_name)
			वापस -ENOMEM;

		err = devm_request_thपढ़ोed_irq(sfp->dev, sfp->gpio_irq[i],
						शून्य, sfp_irq,
						IRQF_ONESHOT |
						IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING,
						sfp_irq_name, sfp);
		अगर (err) अणु
			sfp->gpio_irq[i] = 0;
			sfp->need_poll = true;
		पूर्ण
	पूर्ण

	अगर (sfp->need_poll)
		mod_delayed_work(प्रणाली_wq, &sfp->poll, poll_jअगरfies);

	/* We could have an issue in हालs no Tx disable pin is available or
	 * wired as modules using a laser as their light source will जारी to
	 * be active when the fiber is हटाओd. This could be a safety issue and
	 * we should at least warn the user about that.
	 */
	अगर (!sfp->gpio[GPIO_TX_DISABLE])
		dev_warn(sfp->dev,
			 "No tx_disable pin: SFP modules will always be emitting.\n");

	sfp->sfp_bus = sfp_रेजिस्टर_socket(sfp->dev, sfp, &sfp_module_ops);
	अगर (!sfp->sfp_bus)
		वापस -ENOMEM;

	sfp_debugfs_init(sfp);

	वापस 0;
पूर्ण

अटल पूर्णांक sfp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sfp *sfp = platक्रमm_get_drvdata(pdev);

	sfp_debugfs_निकास(sfp);
	sfp_unरेजिस्टर_socket(sfp->sfp_bus);

	rtnl_lock();
	sfp_sm_event(sfp, SFP_E_REMOVE);
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल व्योम sfp_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sfp *sfp = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < GPIO_MAX; i++) अणु
		अगर (!sfp->gpio_irq[i])
			जारी;

		devm_मुक्त_irq(sfp->dev, sfp->gpio_irq[i], sfp);
	पूर्ण

	cancel_delayed_work_sync(&sfp->poll);
	cancel_delayed_work_sync(&sfp->समयout);
पूर्ण

अटल काष्ठा platक्रमm_driver sfp_driver = अणु
	.probe = sfp_probe,
	.हटाओ = sfp_हटाओ,
	.shutकरोwn = sfp_shutकरोwn,
	.driver = अणु
		.name = "sfp",
		.of_match_table = sfp_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sfp_init(व्योम)
अणु
	poll_jअगरfies = msecs_to_jअगरfies(100);

	वापस platक्रमm_driver_रेजिस्टर(&sfp_driver);
पूर्ण
module_init(sfp_init);

अटल व्योम sfp_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sfp_driver);
पूर्ण
module_निकास(sfp_निकास);

MODULE_ALIAS("platform:sfp");
MODULE_AUTHOR("Russell King");
MODULE_LICENSE("GPL v2");
