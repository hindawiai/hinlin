<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/of_device.h>

क्रमागत ams_irq अणु
	AMS_IRQ_FREEFALL = 0x01,
	AMS_IRQ_SHOCK = 0x02,
	AMS_IRQ_GLOBAL = 0x04,
	AMS_IRQ_ALL =
		AMS_IRQ_FREEFALL |
		AMS_IRQ_SHOCK |
		AMS_IRQ_GLOBAL,
पूर्ण;

काष्ठा ams अणु
	/* Locks */
	spinlock_t irq_lock;
	काष्ठा mutex lock;

	/* General properties */
	काष्ठा device_node *of_node;
	काष्ठा platक्रमm_device *of_dev;
	अक्षर has_device;
	अक्षर vflag;
	u32 orient1;
	u32 orient2;

	/* Interrupt worker */
	काष्ठा work_काष्ठा worker;
	u8 worker_irqs;

	/* Implementation
	 *
	 * Only call these functions with the मुख्य lock held.
	 */
	व्योम (*निकास)(व्योम);

	व्योम (*get_xyz)(s8 *x, s8 *y, s8 *z);
	u8 (*get_venकरोr)(व्योम);

	व्योम (*clear_irq)(क्रमागत ams_irq reg);

#अगर_घोषित CONFIG_SENSORS_AMS_I2C
	/* I2C properties */
	काष्ठा i2c_client *i2c_client;
#पूर्ण_अगर

	/* Joystick emulation */
	काष्ठा input_dev *idev;
	__u16 bustype;

	/* calibrated null values */
	पूर्णांक xcalib, ycalib, zcalib;
पूर्ण;

बाह्य काष्ठा ams ams_info;

बाह्य व्योम ams_sensors(s8 *x, s8 *y, s8 *z);
बाह्य पूर्णांक ams_sensor_attach(व्योम);
बाह्य व्योम ams_sensor_detach(व्योम);

बाह्य पूर्णांक ams_pmu_init(काष्ठा device_node *np);
बाह्य पूर्णांक ams_i2c_init(काष्ठा device_node *np);

बाह्य पूर्णांक ams_input_init(व्योम);
बाह्य व्योम ams_input_निकास(व्योम);
