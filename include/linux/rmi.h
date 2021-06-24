<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2016 Synaptics Incorporated
 * Copyright (c) 2011 Unixphere
 */

#अगर_अघोषित _RMI_H
#घोषणा _RMI_H
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/input.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#घोषणा NAME_BUFFER_SIZE 256

/**
 * काष्ठा rmi_2d_axis_alignment - target axis alignment
 * @swap_axes: set to TRUE अगर desired to swap x- and y-axis
 * @flip_x: set to TRUE अगर desired to flip direction on x-axis
 * @flip_y: set to TRUE अगर desired to flip direction on y-axis
 * @clip_x_low - reported X coordinates below this setting will be clipped to
 *               the specअगरied value
 * @clip_x_high - reported X coordinates above this setting will be clipped to
 *               the specअगरied value
 * @clip_y_low - reported Y coordinates below this setting will be clipped to
 *               the specअगरied value
 * @clip_y_high - reported Y coordinates above this setting will be clipped to
 *               the specअगरied value
 * @offset_x - this value will be added to all reported X coordinates
 * @offset_y - this value will be added to all reported Y coordinates
 * @rel_report_enabled - अगर set to true, the relative reporting will be
 *               स्वतःmatically enabled क्रम this sensor.
 */
काष्ठा rmi_2d_axis_alignment अणु
	bool swap_axes;
	bool flip_x;
	bool flip_y;
	u16 clip_x_low;
	u16 clip_y_low;
	u16 clip_x_high;
	u16 clip_y_high;
	u16 offset_x;
	u16 offset_y;
	u8 delta_x_threshold;
	u8 delta_y_threshold;
पूर्ण;

/** This is used to override any hपूर्णांकs an F11 2D sensor might have provided
 * as to what type of sensor it is.
 *
 * @rmi_f11_sensor_शेष - करो not override, determine from F11_2D_QUERY14 अगर
 * available.
 * @rmi_f11_sensor_touchscreen - treat the sensor as a touchscreen (direct
 * poपूर्णांकing).
 * @rmi_f11_sensor_touchpad - thपढ़ो the sensor as a touchpad (indirect
 * poपूर्णांकing).
 */
क्रमागत rmi_sensor_type अणु
	rmi_sensor_शेष = 0,
	rmi_sensor_touchscreen,
	rmi_sensor_touchpad
पूर्ण;

#घोषणा RMI_F11_DISABLE_ABS_REPORT      BIT(0)

/**
 * काष्ठा rmi_2d_sensor_data - overrides शेषs क्रम a 2D sensor.
 * @axis_align - provides axis alignment overrides (see above).
 * @sensor_type - Forces the driver to treat the sensor as an indirect
 * poपूर्णांकing device (touchpad) rather than a direct poपूर्णांकing device
 * (touchscreen).  This is useful when F11_2D_QUERY14 रेजिस्टर is not
 * available.
 * @disable_report_mask - Force data to not be reported even अगर it is supported
 * by the firware.
 * @topbuttonpad - Used with the "5 buttons touchpads" found on the Lenovo 40
 * series
 * @kernel_tracking - most moderns RMI f11 firmwares implement Multअगरinger
 * Type B protocol. However, there are some corner हालs where the user
 * triggers some jumps by tapping with two fingers on the touchpad.
 * Use this setting and dmax to filter out these jumps.
 * Also, when using an old sensor using MF Type A behavior, set to true to
 * report an actual MT protocol B.
 * @dmax - the maximum distance (in sensor units) the kernel tracking allows two
 * distincts fingers to be considered the same.
 */
काष्ठा rmi_2d_sensor_platक्रमm_data अणु
	काष्ठा rmi_2d_axis_alignment axis_align;
	क्रमागत rmi_sensor_type sensor_type;
	पूर्णांक x_mm;
	पूर्णांक y_mm;
	पूर्णांक disable_report_mask;
	u16 rezero_रुको;
	bool topbuttonpad;
	bool kernel_tracking;
	पूर्णांक dmax;
	पूर्णांक dribble;
	पूर्णांक palm_detect;
पूर्ण;

/**
 * काष्ठा rmi_gpio_data - overrides शेषs क्रम a single F30/F3A GPIOs/LED
 * chip.
 * @buttonpad - the touchpad is a buttonpad, so enable only the first actual
 * button that is found.
 * @trackstick_buttons - Set when the function 30 or 3a is handling the physical
 * buttons of the trackstick (as a PS/2 passthrough device).
 * @disable - the touchpad incorrectly reports F30/F3A and it should be ignored.
 * This is a special हाल which is due to misconfigured firmware.
 */
काष्ठा rmi_gpio_data अणु
	bool buttonpad;
	bool trackstick_buttons;
	bool disable;
पूर्ण;


/*
 * Set the state of a रेजिस्टर
 *	DEFAULT - use the शेष value set by the firmware config
 *	OFF - explicitly disable the रेजिस्टर
 *	ON - explicitly enable the रेजिस्टर
 */
क्रमागत rmi_reg_state अणु
	RMI_REG_STATE_DEFAULT = 0,
	RMI_REG_STATE_OFF = 1,
	RMI_REG_STATE_ON = 2
पूर्ण;

/**
 * काष्ठा rmi_f01_घातer_management -When non-zero, these values will be written
 * to the touch sensor to override the शेष firmware settigns.  For a
 * detailed explanation of what each field करोes, see the corresponding
 * करोcumention in the RMI4 specअगरication.
 *
 * @nosleep - specअगरies whether the device is permitted to sleep or करोze (that
 * is, enter a temporary low घातer state) when no fingers are touching the
 * sensor.
 * @wakeup_threshold - controls the capacitance threshold at which the touch
 * sensor will decide to wake up from that low घातer state.
 * @करोze_holकरोff - controls how दीर्घ the touch sensor रुकोs after the last
 * finger lअगरts beक्रमe entering the करोze state, in units of 100ms.
 * @करोze_पूर्णांकerval - controls the पूर्णांकerval between checks क्रम finger presence
 * when the touch sensor is in करोze mode, in units of 10ms.
 */
काष्ठा rmi_f01_घातer_management अणु
	क्रमागत rmi_reg_state nosleep;
	u8 wakeup_threshold;
	u8 करोze_holकरोff;
	u8 करोze_पूर्णांकerval;
पूर्ण;

/**
 * काष्ठा rmi_device_platक्रमm_data_spi - provides parameters used in SPI
 * communications.  All Synaptics SPI products support a standard SPI
 * पूर्णांकerface; some also support what is called SPI V2 mode, depending on
 * firmware and/or ASIC limitations.  In V2 mode, the touch sensor can
 * support लघुer delays during certain operations, and these are specअगरied
 * separately from the standard mode delays.
 *
 * @block_delay - क्रम standard SPI transactions consisting of both a पढ़ो and
 * ग_लिखो operation, the delay (in microseconds) between the पढ़ो and ग_लिखो
 * operations.
 * @split_पढ़ो_block_delay_us - क्रम V2 SPI transactions consisting of both a
 * पढ़ो and ग_लिखो operation, the delay (in microseconds) between the पढ़ो and
 * ग_लिखो operations.
 * @पढ़ो_delay_us - the delay between each byte of a पढ़ो operation in normal
 * SPI mode.
 * @ग_लिखो_delay_us - the delay between each byte of a ग_लिखो operation in normal
 * SPI mode.
 * @split_पढ़ो_byte_delay_us - the delay between each byte of a पढ़ो operation
 * in V2 mode.
 * @pre_delay_us - the delay beक्रमe the start of a SPI transaction.  This is
 * typically useful in conjunction with custom chip select निश्चितions (see
 * below).
 * @post_delay_us - the delay after the completion of an SPI transaction.  This
 * is typically useful in conjunction with custom chip select निश्चितions (see
 * below).
 * @cs_निश्चित - For प्रणालीs where the SPI subप्रणाली करोes not control the CS/SSB
 * line, or where such control is broken, you can provide a custom routine to
 * handle a GPIO as CS/SSB.  This routine will be called at the beginning and
 * end of each SPI transaction.  The RMI SPI implementation will रुको
 * pre_delay_us after this routine वापसs beक्रमe starting the SPI transfer;
 * and post_delay_us after completion of the SPI transfer(s) beक्रमe calling it
 * with निश्चित==FALSE.
 */
काष्ठा rmi_device_platक्रमm_data_spi अणु
	u32 block_delay_us;
	u32 split_पढ़ो_block_delay_us;
	u32 पढ़ो_delay_us;
	u32 ग_लिखो_delay_us;
	u32 split_पढ़ो_byte_delay_us;
	u32 pre_delay_us;
	u32 post_delay_us;
	u8 bits_per_word;
	u16 mode;

	व्योम *cs_निश्चित_data;
	पूर्णांक (*cs_निश्चित)(स्थिर व्योम *cs_निश्चित_data, स्थिर bool निश्चित);
पूर्ण;

/**
 * काष्ठा rmi_device_platक्रमm_data - प्रणाली specअगरic configuration info.
 *
 * @reset_delay_ms - after issuing a reset command to the touch sensor, the
 * driver रुकोs a few milliseconds to give the firmware a chance to
 * re-initialize.  You can override the शेष रुको period here.
 * @irq: irq associated with the attn gpio line, or negative
 */
काष्ठा rmi_device_platक्रमm_data अणु
	पूर्णांक reset_delay_ms;
	पूर्णांक irq;

	काष्ठा rmi_device_platक्रमm_data_spi spi_data;

	/* function handler pdata */
	काष्ठा rmi_2d_sensor_platक्रमm_data sensor_pdata;
	काष्ठा rmi_f01_घातer_management घातer_management;
	काष्ठा rmi_gpio_data gpio_data;
पूर्ण;

/**
 * काष्ठा rmi_function_descriptor - RMI function base addresses
 *
 * @query_base_addr: The RMI Query base address
 * @command_base_addr: The RMI Command base address
 * @control_base_addr: The RMI Control base address
 * @data_base_addr: The RMI Data base address
 * @पूर्णांकerrupt_source_count: The number of irqs this RMI function needs
 * @function_number: The RMI function number
 *
 * This काष्ठा is used when iterating the Page Description Table. The addresses
 * are 16-bit values to include the current page address.
 *
 */
काष्ठा rmi_function_descriptor अणु
	u16 query_base_addr;
	u16 command_base_addr;
	u16 control_base_addr;
	u16 data_base_addr;
	u8 पूर्णांकerrupt_source_count;
	u8 function_number;
	u8 function_version;
पूर्ण;

काष्ठा rmi_device;

/**
 * काष्ठा rmi_transport_dev - represent an RMI transport device
 *
 * @dev: Poपूर्णांकer to the communication device, e.g. i2c or spi
 * @rmi_dev: Poपूर्णांकer to the RMI device
 * @proto_name: name of the transport protocol (SPI, i2c, etc)
 * @ops: poपूर्णांकer to transport operations implementation
 *
 * The RMI transport device implements the glue between dअगरferent communication
 * buses such as I2C and SPI.
 *
 */
काष्ठा rmi_transport_dev अणु
	काष्ठा device *dev;
	काष्ठा rmi_device *rmi_dev;

	स्थिर अक्षर *proto_name;
	स्थिर काष्ठा rmi_transport_ops *ops;

	काष्ठा rmi_device_platक्रमm_data pdata;

	काष्ठा input_dev *input;
पूर्ण;

/**
 * काष्ठा rmi_transport_ops - defines transport protocol operations.
 *
 * @ग_लिखो_block: Writing a block of data to the specअगरied address
 * @पढ़ो_block: Read a block of data from the specअगरied address.
 */
काष्ठा rmi_transport_ops अणु
	पूर्णांक (*ग_लिखो_block)(काष्ठा rmi_transport_dev *xport, u16 addr,
			   स्थिर व्योम *buf, माप_प्रकार len);
	पूर्णांक (*पढ़ो_block)(काष्ठा rmi_transport_dev *xport, u16 addr,
			  व्योम *buf, माप_प्रकार len);
	पूर्णांक (*reset)(काष्ठा rmi_transport_dev *xport, u16 reset_addr);
पूर्ण;

/**
 * काष्ठा rmi_driver - driver क्रम an RMI4 sensor on the RMI bus.
 *
 * @driver: Device driver model driver
 * @reset_handler: Called when a reset is detected.
 * @clear_irq_bits: Clear the specअगरied bits in the current पूर्णांकerrupt mask.
 * @set_irq_bist: Set the specअगरied bits in the current पूर्णांकerrupt mask.
 * @store_productid: Callback क्रम cache product id from function 01
 * @data: Private data poपूर्णांकer
 *
 */
काष्ठा rmi_driver अणु
	काष्ठा device_driver driver;

	पूर्णांक (*reset_handler)(काष्ठा rmi_device *rmi_dev);
	पूर्णांक (*clear_irq_bits)(काष्ठा rmi_device *rmi_dev, अचिन्हित दीर्घ *mask);
	पूर्णांक (*set_irq_bits)(काष्ठा rmi_device *rmi_dev, अचिन्हित दीर्घ *mask);
	पूर्णांक (*store_productid)(काष्ठा rmi_device *rmi_dev);
	पूर्णांक (*set_input_params)(काष्ठा rmi_device *rmi_dev,
			काष्ठा input_dev *input);
	व्योम *data;
पूर्ण;

/**
 * काष्ठा rmi_device - represents an RMI4 sensor device on the RMI bus.
 *
 * @dev: The device created क्रम the RMI bus
 * @number: Unique number क्रम the device on the bus.
 * @driver: Poपूर्णांकer to associated driver
 * @xport: Poपूर्णांकer to the transport पूर्णांकerface
 *
 */
काष्ठा rmi_device अणु
	काष्ठा device dev;
	पूर्णांक number;

	काष्ठा rmi_driver *driver;
	काष्ठा rmi_transport_dev *xport;

पूर्ण;

काष्ठा rmi4_attn_data अणु
	अचिन्हित दीर्घ irq_status;
	माप_प्रकार size;
	व्योम *data;
पूर्ण;

काष्ठा rmi_driver_data अणु
	काष्ठा list_head function_list;

	काष्ठा rmi_device *rmi_dev;

	काष्ठा rmi_function *f01_container;
	काष्ठा rmi_function *f34_container;
	bool bootloader_mode;

	पूर्णांक num_of_irq_regs;
	पूर्णांक irq_count;
	व्योम *irq_memory;
	अचिन्हित दीर्घ *irq_status;
	अचिन्हित दीर्घ *fn_irq_bits;
	अचिन्हित दीर्घ *current_irq_mask;
	अचिन्हित दीर्घ *new_irq_mask;
	काष्ठा mutex irq_mutex;
	काष्ठा input_dev *input;

	काष्ठा irq_करोमुख्य *irqकरोमुख्य;

	u8 pdt_props;

	u8 num_rx_electrodes;
	u8 num_tx_electrodes;

	bool enabled;
	काष्ठा mutex enabled_mutex;

	काष्ठा rmi4_attn_data attn_data;
	DECLARE_KFIFO(attn_fअगरo, काष्ठा rmi4_attn_data, 16);
पूर्ण;

पूर्णांक rmi_रेजिस्टर_transport_device(काष्ठा rmi_transport_dev *xport);
व्योम rmi_unरेजिस्टर_transport_device(काष्ठा rmi_transport_dev *xport);

व्योम rmi_set_attn_data(काष्ठा rmi_device *rmi_dev, अचिन्हित दीर्घ irq_status,
		       व्योम *data, माप_प्रकार size);

पूर्णांक rmi_driver_suspend(काष्ठा rmi_device *rmi_dev, bool enable_wake);
पूर्णांक rmi_driver_resume(काष्ठा rmi_device *rmi_dev, bool clear_wake);
#पूर्ण_अगर
