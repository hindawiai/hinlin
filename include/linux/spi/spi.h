<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later
 *
 * Copyright (C) 2005 David Brownell
 */

#अगर_अघोषित __LINUX_SPI_H
#घोषणा __LINUX_SPI_H

#समावेश <linux/bits.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/completion.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/ptp_घड़ी_kernel.h>

#समावेश <uapi/linux/spi/spi.h>

काष्ठा dma_chan;
काष्ठा software_node;
काष्ठा spi_controller;
काष्ठा spi_transfer;
काष्ठा spi_controller_mem_ops;

/*
 * INTERFACES between SPI master-side drivers and SPI slave protocol handlers,
 * and SPI infraकाष्ठाure.
 */
बाह्य काष्ठा bus_type spi_bus_type;

/**
 * काष्ठा spi_statistics - statistics क्रम spi transfers
 * @lock:          lock protecting this काष्ठाure
 *
 * @messages:      number of spi-messages handled
 * @transfers:     number of spi_transfers handled
 * @errors:        number of errors during spi_transfer
 * @समयकरोut:      number of समयouts during spi_transfer
 *
 * @spi_sync:      number of बार spi_sync is used
 * @spi_sync_immediate:
 *                 number of बार spi_sync is executed immediately
 *                 in calling context without queuing and scheduling
 * @spi_async:     number of बार spi_async is used
 *
 * @bytes:         number of bytes transferred to/from device
 * @bytes_tx:      number of bytes sent to device
 * @bytes_rx:      number of bytes received from device
 *
 * @transfer_bytes_histo:
 *                 transfer bytes histogramm
 *
 * @transfers_split_maxsize:
 *                 number of transfers that have been split because of
 *                 maxsize limit
 */
काष्ठा spi_statistics अणु
	spinlock_t		lock; /* lock क्रम the whole काष्ठाure */

	अचिन्हित दीर्घ		messages;
	अचिन्हित दीर्घ		transfers;
	अचिन्हित दीर्घ		errors;
	अचिन्हित दीर्घ		समयकरोut;

	अचिन्हित दीर्घ		spi_sync;
	अचिन्हित दीर्घ		spi_sync_immediate;
	अचिन्हित दीर्घ		spi_async;

	अचिन्हित दीर्घ दीर्घ	bytes;
	अचिन्हित दीर्घ दीर्घ	bytes_rx;
	अचिन्हित दीर्घ दीर्घ	bytes_tx;

#घोषणा SPI_STATISTICS_HISTO_SIZE 17
	अचिन्हित दीर्घ transfer_bytes_histo[SPI_STATISTICS_HISTO_SIZE];

	अचिन्हित दीर्घ transfers_split_maxsize;
पूर्ण;

व्योम spi_statistics_add_transfer_stats(काष्ठा spi_statistics *stats,
				       काष्ठा spi_transfer *xfer,
				       काष्ठा spi_controller *ctlr);

#घोषणा SPI_STATISTICS_ADD_TO_FIELD(stats, field, count)	\
	करो अणु							\
		अचिन्हित दीर्घ flags;				\
		spin_lock_irqsave(&(stats)->lock, flags);	\
		(stats)->field += count;			\
		spin_unlock_irqrestore(&(stats)->lock, flags);	\
	पूर्ण जबतक (0)

#घोषणा SPI_STATISTICS_INCREMENT_FIELD(stats, field)	\
	SPI_STATISTICS_ADD_TO_FIELD(stats, field, 1)

/**
 * काष्ठा spi_delay - SPI delay inक्रमmation
 * @value: Value क्रम the delay
 * @unit: Unit क्रम the delay
 */
काष्ठा spi_delay अणु
#घोषणा SPI_DELAY_UNIT_USECS	0
#घोषणा SPI_DELAY_UNIT_NSECS	1
#घोषणा SPI_DELAY_UNIT_SCK	2
	u16	value;
	u8	unit;
पूर्ण;

बाह्य पूर्णांक spi_delay_to_ns(काष्ठा spi_delay *_delay, काष्ठा spi_transfer *xfer);
बाह्य पूर्णांक spi_delay_exec(काष्ठा spi_delay *_delay, काष्ठा spi_transfer *xfer);

/**
 * काष्ठा spi_device - Controller side proxy क्रम an SPI slave device
 * @dev: Driver model representation of the device.
 * @controller: SPI controller used with the device.
 * @master: Copy of controller, क्रम backwards compatibility.
 * @max_speed_hz: Maximum घड़ी rate to be used with this chip
 *	(on this board); may be changed by the device's driver.
 *	The spi_transfer.speed_hz can override this क्रम each transfer.
 * @chip_select: Chipselect, distinguishing chips handled by @controller.
 * @mode: The spi mode defines how data is घड़ीed out and in.
 *	This may be changed by the device's driver.
 *	The "active low" शेष क्रम chipselect mode can be overridden
 *	(by specअगरying SPI_CS_HIGH) as can the "MSB first" शेष क्रम
 *	each word in a transfer (by specअगरying SPI_LSB_FIRST).
 * @bits_per_word: Data transfers involve one or more words; word sizes
 *	like eight or 12 bits are common.  In-memory wordsizes are
 *	घातers of two bytes (e.g. 20 bit samples use 32 bits).
 *	This may be changed by the device's driver, or left at the
 *	शेष (0) indicating protocol words are eight bit bytes.
 *	The spi_transfer.bits_per_word can override this क्रम each transfer.
 * @rt: Make the pump thपढ़ो real समय priority.
 * @irq: Negative, or the number passed to request_irq() to receive
 *	पूर्णांकerrupts from this device.
 * @controller_state: Controller's runसमय state
 * @controller_data: Board-specअगरic definitions क्रम controller, such as
 *	FIFO initialization parameters; from board_info.controller_data
 * @modalias: Name of the driver to use with this device, or an alias
 *	क्रम that name.  This appears in the sysfs "modalias" attribute
 *	क्रम driver coldplugging, and in uevents used क्रम hotplugging
 * @driver_override: If the name of a driver is written to this attribute, then
 *	the device will bind to the named driver and only the named driver.
 * @cs_gpio: LEGACY: gpio number of the chipselect line (optional, -ENOENT when
 *	not using a GPIO line) use cs_gpiod in new drivers by opting in on
 *	the spi_master.
 * @cs_gpiod: gpio descriptor of the chipselect line (optional, शून्य when
 *	not using a GPIO line)
 * @word_delay: delay to be inserted between consecutive
 *	words of a transfer
 *
 * @statistics: statistics क्रम the spi_device
 *
 * A @spi_device is used to पूर्णांकerchange data between an SPI slave
 * (usually a discrete chip) and CPU memory.
 *
 * In @dev, the platक्रमm_data is used to hold inक्रमmation about this
 * device that's meaningful to the device's protocol driver, but not
 * to its controller.  One example might be an identअगरier क्रम a chip
 * variant with slightly dअगरferent functionality; another might be
 * inक्रमmation about how this particular board wires the chip's pins.
 */
काष्ठा spi_device अणु
	काष्ठा device		dev;
	काष्ठा spi_controller	*controller;
	काष्ठा spi_controller	*master;	/* compatibility layer */
	u32			max_speed_hz;
	u8			chip_select;
	u8			bits_per_word;
	bool			rt;
#घोषणा SPI_NO_TX	BIT(31)		/* no transmit wire */
#घोषणा SPI_NO_RX	BIT(30)		/* no receive wire */
	/*
	 * All bits defined above should be covered by SPI_MODE_KERNEL_MASK.
	 * The SPI_MODE_KERNEL_MASK has the SPI_MODE_USER_MASK counterpart,
	 * which is defined in 'include/uapi/linux/spi/spi.h'.
	 * The bits defined here are from bit 31 करोwnwards, जबतक in
	 * SPI_MODE_USER_MASK are from 0 upwards.
	 * These bits must not overlap. A अटल निश्चित check should make sure of that.
	 * If adding extra bits, make sure to decrease the bit index below as well.
	 */
#घोषणा SPI_MODE_KERNEL_MASK	(~(BIT(30) - 1))
	u32			mode;
	पूर्णांक			irq;
	व्योम			*controller_state;
	व्योम			*controller_data;
	अक्षर			modalias[SPI_NAME_SIZE];
	स्थिर अक्षर		*driver_override;
	पूर्णांक			cs_gpio;	/* LEGACY: chip select gpio */
	काष्ठा gpio_desc	*cs_gpiod;	/* chip select gpio desc */
	काष्ठा spi_delay	word_delay; /* पूर्णांकer-word delay */

	/* the statistics */
	काष्ठा spi_statistics	statistics;

	/*
	 * likely need more hooks क्रम more protocol options affecting how
	 * the controller talks to each chip, like:
	 *  - memory packing (12 bit samples पूर्णांकo low bits, others zeroed)
	 *  - priority
	 *  - chipselect delays
	 *  - ...
	 */
पूर्ण;

/* Make sure that SPI_MODE_KERNEL_MASK & SPI_MODE_USER_MASK करोn't overlap */
अटल_निश्चित((SPI_MODE_KERNEL_MASK & SPI_MODE_USER_MASK) == 0,
	      "SPI_MODE_USER_MASK & SPI_MODE_KERNEL_MASK must not overlap");

अटल अंतरभूत काष्ठा spi_device *to_spi_device(काष्ठा device *dev)
अणु
	वापस dev ? container_of(dev, काष्ठा spi_device, dev) : शून्य;
पूर्ण

/* most drivers won't need to care about device refcounting */
अटल अंतरभूत काष्ठा spi_device *spi_dev_get(काष्ठा spi_device *spi)
अणु
	वापस (spi && get_device(&spi->dev)) ? spi : शून्य;
पूर्ण

अटल अंतरभूत व्योम spi_dev_put(काष्ठा spi_device *spi)
अणु
	अगर (spi)
		put_device(&spi->dev);
पूर्ण

/* ctldata is क्रम the bus_controller driver's runसमय state */
अटल अंतरभूत व्योम *spi_get_ctldata(काष्ठा spi_device *spi)
अणु
	वापस spi->controller_state;
पूर्ण

अटल अंतरभूत व्योम spi_set_ctldata(काष्ठा spi_device *spi, व्योम *state)
अणु
	spi->controller_state = state;
पूर्ण

/* device driver data */

अटल अंतरभूत व्योम spi_set_drvdata(काष्ठा spi_device *spi, व्योम *data)
अणु
	dev_set_drvdata(&spi->dev, data);
पूर्ण

अटल अंतरभूत व्योम *spi_get_drvdata(काष्ठा spi_device *spi)
अणु
	वापस dev_get_drvdata(&spi->dev);
पूर्ण

काष्ठा spi_message;

/**
 * काष्ठा spi_driver - Host side "protocol" driver
 * @id_table: List of SPI devices supported by this driver
 * @probe: Binds this driver to the spi device.  Drivers can verअगरy
 *	that the device is actually present, and may need to configure
 *	अक्षरacteristics (such as bits_per_word) which weren't needed क्रम
 *	the initial configuration करोne during प्रणाली setup.
 * @हटाओ: Unbinds this driver from the spi device
 * @shutकरोwn: Standard shutकरोwn callback used during प्रणाली state
 *	transitions such as घातerकरोwn/halt and kexec
 * @driver: SPI device drivers should initialize the name and owner
 *	field of this काष्ठाure.
 *
 * This represents the kind of device driver that uses SPI messages to
 * पूर्णांकeract with the hardware at the other end of a SPI link.  It's called
 * a "protocol" driver because it works through messages rather than talking
 * directly to SPI hardware (which is what the underlying SPI controller
 * driver करोes to pass those messages).  These protocols are defined in the
 * specअगरication क्रम the device(s) supported by the driver.
 *
 * As a rule, those device protocols represent the lowest level पूर्णांकerface
 * supported by a driver, and it will support upper level पूर्णांकerfaces too.
 * Examples of such upper levels include frameworks like MTD, networking,
 * MMC, RTC, fileप्रणाली अक्षरacter device nodes, and hardware monitoring.
 */
काष्ठा spi_driver अणु
	स्थिर काष्ठा spi_device_id *id_table;
	पूर्णांक			(*probe)(काष्ठा spi_device *spi);
	पूर्णांक			(*हटाओ)(काष्ठा spi_device *spi);
	व्योम			(*shutकरोwn)(काष्ठा spi_device *spi);
	काष्ठा device_driver	driver;
पूर्ण;

अटल अंतरभूत काष्ठा spi_driver *to_spi_driver(काष्ठा device_driver *drv)
अणु
	वापस drv ? container_of(drv, काष्ठा spi_driver, driver) : शून्य;
पूर्ण

बाह्य पूर्णांक __spi_रेजिस्टर_driver(काष्ठा module *owner, काष्ठा spi_driver *sdrv);

/**
 * spi_unरेजिस्टर_driver - reverse effect of spi_रेजिस्टर_driver
 * @sdrv: the driver to unरेजिस्टर
 * Context: can sleep
 */
अटल अंतरभूत व्योम spi_unरेजिस्टर_driver(काष्ठा spi_driver *sdrv)
अणु
	अगर (sdrv)
		driver_unरेजिस्टर(&sdrv->driver);
पूर्ण

/* use a define to aव्योम include chaining to get THIS_MODULE */
#घोषणा spi_रेजिस्टर_driver(driver) \
	__spi_रेजिस्टर_driver(THIS_MODULE, driver)

/**
 * module_spi_driver() - Helper macro क्रम रेजिस्टरing a SPI driver
 * @__spi_driver: spi_driver काष्ठा
 *
 * Helper macro क्रम SPI drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_spi_driver(__spi_driver) \
	module_driver(__spi_driver, spi_रेजिस्टर_driver, \
			spi_unरेजिस्टर_driver)

/**
 * काष्ठा spi_controller - पूर्णांकerface to SPI master or slave controller
 * @dev: device पूर्णांकerface to this driver
 * @list: link with the global spi_controller list
 * @bus_num: board-specअगरic (and often SOC-specअगरic) identअगरier क्रम a
 *	given SPI controller.
 * @num_chipselect: chipselects are used to distinguish inभागidual
 *	SPI slaves, and are numbered from zero to num_chipselects.
 *	each slave has a chipselect संकेत, but it's common that not
 *	every chipselect is connected to a slave.
 * @dma_alignment: SPI controller स्थिरraपूर्णांक on DMA buffers alignment.
 * @mode_bits: flags understood by this controller driver
 * @buswidth_override_bits: flags to override क्रम this controller driver
 * @bits_per_word_mask: A mask indicating which values of bits_per_word are
 *	supported by the driver. Bit n indicates that a bits_per_word n+1 is
 *	supported. If set, the SPI core will reject any transfer with an
 *	unsupported bits_per_word. If not set, this value is simply ignored,
 *	and it's up to the inभागidual driver to perक्रमm any validation.
 * @min_speed_hz: Lowest supported transfer speed
 * @max_speed_hz: Highest supported transfer speed
 * @flags: other स्थिरraपूर्णांकs relevant to this driver
 * @slave: indicates that this is an SPI slave controller
 * @max_transfer_size: function that वापसs the max transfer size क्रम
 *	a &spi_device; may be %शून्य, so the शेष %SIZE_MAX will be used.
 * @max_message_size: function that वापसs the max message size क्रम
 *	a &spi_device; may be %शून्य, so the शेष %SIZE_MAX will be used.
 * @io_mutex: mutex क्रम physical bus access
 * @bus_lock_spinlock: spinlock क्रम SPI bus locking
 * @bus_lock_mutex: mutex क्रम exclusion of multiple callers
 * @bus_lock_flag: indicates that the SPI bus is locked क्रम exclusive use
 * @setup: updates the device mode and घड़ीing records used by a
 *	device's SPI controller; protocol code may call this.  This
 *	must fail अगर an unrecognized or unsupported mode is requested.
 *	It's always safe to call this unless transfers are pending on
 *	the device whose settings are being modअगरied.
 * @set_cs_timing: optional hook क्रम SPI devices to request SPI master
 * controller क्रम configuring specअगरic CS setup समय, hold समय and inactive
 * delay पूर्णांकerms of घड़ी counts
 * @transfer: adds a message to the controller's transfer queue.
 * @cleanup: मुक्तs controller-specअगरic state
 * @can_dma: determine whether this controller supports DMA
 * @queued: whether this controller is providing an पूर्णांकernal message queue
 * @kworker: poपूर्णांकer to thपढ़ो काष्ठा क्रम message pump
 * @pump_messages: work काष्ठा क्रम scheduling work to the message pump
 * @queue_lock: spinlock to syncronise access to message queue
 * @queue: message queue
 * @idling: the device is entering idle state
 * @cur_msg: the currently in-flight message
 * @cur_msg_prepared: spi_prepare_message was called क्रम the currently
 *                    in-flight message
 * @cur_msg_mapped: message has been mapped क्रम DMA
 * @last_cs_enable: was enable true on the last call to set_cs.
 * @last_cs_mode_high: was (mode & SPI_CS_HIGH) true on the last call to set_cs.
 * @xfer_completion: used by core transfer_one_message()
 * @busy: message pump is busy
 * @running: message pump is running
 * @rt: whether this queue is set to run as a realसमय task
 * @स्वतः_runसमय_pm: the core should ensure a runसमय PM reference is held
 *                   जबतक the hardware is prepared, using the parent
 *                   device क्रम the spidev
 * @max_dma_len: Maximum length of a DMA transfer क्रम the device.
 * @prepare_transfer_hardware: a message will soon arrive from the queue
 *	so the subप्रणाली requests the driver to prepare the transfer hardware
 *	by issuing this call
 * @transfer_one_message: the subप्रणाली calls the driver to transfer a single
 *	message जबतक queuing transfers that arrive in the meanसमय. When the
 *	driver is finished with this message, it must call
 *	spi_finalize_current_message() so the subप्रणाली can issue the next
 *	message
 * @unprepare_transfer_hardware: there are currently no more messages on the
 *	queue so the subप्रणाली notअगरies the driver that it may relax the
 *	hardware by issuing this call
 *
 * @set_cs: set the logic level of the chip select line.  May be called
 *          from पूर्णांकerrupt context.
 * @prepare_message: set up the controller to transfer a single message,
 *                   क्रम example करोing DMA mapping.  Called from thपढ़ोed
 *                   context.
 * @transfer_one: transfer a single spi_transfer.
 *
 *                  - वापस 0 अगर the transfer is finished,
 *                  - वापस 1 अगर the transfer is still in progress. When
 *                    the driver is finished with this transfer it must
 *                    call spi_finalize_current_transfer() so the subप्रणाली
 *                    can issue the next transfer. Note: transfer_one and
 *                    transfer_one_message are mutually exclusive; when both
 *                    are set, the generic subप्रणाली करोes not call your
 *                    transfer_one callback.
 * @handle_err: the subप्रणाली calls the driver to handle an error that occurs
 *		in the generic implementation of transfer_one_message().
 * @mem_ops: optimized/dedicated operations क्रम पूर्णांकeractions with SPI memory.
 *	     This field is optional and should only be implemented अगर the
 *	     controller has native support क्रम memory like operations.
 * @unprepare_message: unकरो any work करोne by prepare_message().
 * @slave_पात: पात the ongoing transfer request on an SPI slave controller
 * @cs_setup: delay to be पूर्णांकroduced by the controller after CS is निश्चितed
 * @cs_hold: delay to be पूर्णांकroduced by the controller beक्रमe CS is deनिश्चितed
 * @cs_inactive: delay to be पूर्णांकroduced by the controller after CS is
 *	deनिश्चितed. If @cs_change_delay is used from @spi_transfer, then the
 *	two delays will be added up.
 * @cs_gpios: LEGACY: array of GPIO descs to use as chip select lines; one per
 *	CS number. Any inभागidual value may be -ENOENT क्रम CS lines that
 *	are not GPIOs (driven by the SPI controller itself). Use the cs_gpiods
 *	in new drivers.
 * @cs_gpiods: Array of GPIO descs to use as chip select lines; one per CS
 *	number. Any inभागidual value may be शून्य क्रम CS lines that
 *	are not GPIOs (driven by the SPI controller itself).
 * @use_gpio_descriptors: Turns on the code in the SPI core to parse and grab
 *	GPIO descriptors rather than using global GPIO numbers grabbed by the
 *	driver. This will fill in @cs_gpiods and @cs_gpios should not be used,
 *	and SPI devices will have the cs_gpiod asचिन्हित rather than cs_gpio.
 * @unused_native_cs: When cs_gpiods is used, spi_रेजिस्टर_controller() will
 *	fill in this field with the first unused native CS, to be used by SPI
 *	controller drivers that need to drive a native CS when using GPIO CS.
 * @max_native_cs: When cs_gpiods is used, and this field is filled in,
 *	spi_रेजिस्टर_controller() will validate all native CS (including the
 *	unused native CS) against this value.
 * @statistics: statistics क्रम the spi_controller
 * @dma_tx: DMA transmit channel
 * @dma_rx: DMA receive channel
 * @dummy_rx: dummy receive buffer क्रम full-duplex devices
 * @dummy_tx: dummy transmit buffer क्रम full-duplex devices
 * @fw_translate_cs: If the boot firmware uses dअगरferent numbering scheme
 *	what Linux expects, this optional hook can be used to translate
 *	between the two.
 * @ptp_sts_supported: If the driver sets this to true, it must provide a
 *	समय snapshot in @spi_transfer->ptp_sts as बंद as possible to the
 *	moment in समय when @spi_transfer->ptp_sts_word_pre and
 *	@spi_transfer->ptp_sts_word_post were transmitted.
 *	If the driver करोes not set this, the SPI core takes the snapshot as
 *	बंद to the driver hand-over as possible.
 * @irq_flags: Interrupt enable state during PTP प्रणाली बारtamping
 * @fallback: fallback to pio अगर dma transfer वापस failure with
 *	SPI_TRANS_FAIL_NO_START.
 *
 * Each SPI controller can communicate with one or more @spi_device
 * children.  These make a small bus, sharing MOSI, MISO and SCK संकेतs
 * but not chip select संकेतs.  Each device may be configured to use a
 * dअगरferent घड़ी rate, since those shared संकेतs are ignored unless
 * the chip is selected.
 *
 * The driver क्रम an SPI controller manages access to those devices through
 * a queue of spi_message transactions, copying data between CPU memory and
 * an SPI slave device.  For each such message it queues, it calls the
 * message's completion function when the transaction completes.
 */
काष्ठा spi_controller अणु
	काष्ठा device	dev;

	काष्ठा list_head list;

	/* other than negative (== assign one dynamically), bus_num is fully
	 * board-specअगरic.  usually that simplअगरies to being SOC-specअगरic.
	 * example:  one SOC has three SPI controllers, numbered 0..2,
	 * and one board's schematics might show it using SPI-2.  software
	 * would normally use bus_num=2 क्रम that controller.
	 */
	s16			bus_num;

	/* chipselects will be पूर्णांकegral to many controllers; some others
	 * might use board-specअगरic GPIOs.
	 */
	u16			num_chipselect;

	/* some SPI controllers pose alignment requirements on DMAable
	 * buffers; let protocol drivers know about these requirements.
	 */
	u16			dma_alignment;

	/* spi_device.mode flags understood by this controller driver */
	u32			mode_bits;

	/* spi_device.mode flags override flags क्रम this controller */
	u32			buswidth_override_bits;

	/* biपंचांगask of supported bits_per_word क्रम transfers */
	u32			bits_per_word_mask;
#घोषणा SPI_BPW_MASK(bits) BIT((bits) - 1)
#घोषणा SPI_BPW_RANGE_MASK(min, max) GENMASK((max) - 1, (min) - 1)

	/* limits on transfer speed */
	u32			min_speed_hz;
	u32			max_speed_hz;

	/* other स्थिरraपूर्णांकs relevant to this driver */
	u16			flags;
#घोषणा SPI_CONTROLLER_HALF_DUPLEX	BIT(0)	/* can't करो full duplex */
#घोषणा SPI_CONTROLLER_NO_RX		BIT(1)	/* can't करो buffer पढ़ो */
#घोषणा SPI_CONTROLLER_NO_TX		BIT(2)	/* can't करो buffer ग_लिखो */
#घोषणा SPI_CONTROLLER_MUST_RX		BIT(3)	/* requires rx */
#घोषणा SPI_CONTROLLER_MUST_TX		BIT(4)	/* requires tx */

#घोषणा SPI_MASTER_GPIO_SS		BIT(5)	/* GPIO CS must select slave */

	/* flag indicating this is a non-devres managed controller */
	bool			devm_allocated;

	/* flag indicating this is an SPI slave controller */
	bool			slave;

	/*
	 * on some hardware transfer / message size may be स्थिरrained
	 * the limit may depend on device transfer settings
	 */
	माप_प्रकार (*max_transfer_size)(काष्ठा spi_device *spi);
	माप_प्रकार (*max_message_size)(काष्ठा spi_device *spi);

	/* I/O mutex */
	काष्ठा mutex		io_mutex;

	/* lock and mutex क्रम SPI bus locking */
	spinlock_t		bus_lock_spinlock;
	काष्ठा mutex		bus_lock_mutex;

	/* flag indicating that the SPI bus is locked क्रम exclusive use */
	bool			bus_lock_flag;

	/* Setup mode and घड़ी, etc (spi driver may call many बार).
	 *
	 * IMPORTANT:  this may be called when transfers to another
	 * device are active.  DO NOT UPDATE SHARED REGISTERS in ways
	 * which could अवरोध those transfers.
	 */
	पूर्णांक			(*setup)(काष्ठा spi_device *spi);

	/*
	 * set_cs_timing() method is क्रम SPI controllers that supports
	 * configuring CS timing.
	 *
	 * This hook allows SPI client drivers to request SPI controllers
	 * to configure specअगरic CS timing through spi_set_cs_timing() after
	 * spi_setup().
	 */
	पूर्णांक (*set_cs_timing)(काष्ठा spi_device *spi, काष्ठा spi_delay *setup,
			     काष्ठा spi_delay *hold, काष्ठा spi_delay *inactive);

	/* bidirectional bulk transfers
	 *
	 * + The transfer() method may not sleep; its मुख्य role is
	 *   just to add the message to the queue.
	 * + For now there's no हटाओ-from-queue operation, or
	 *   any other request management
	 * + To a given spi_device, message queueing is pure fअगरo
	 *
	 * + The controller's मुख्य job is to process its message queue,
	 *   selecting a chip (क्रम masters), then transferring data
	 * + If there are multiple spi_device children, the i/o queue
	 *   arbitration algorithm is unspecअगरied (round robin, fअगरo,
	 *   priority, reservations, preemption, etc)
	 *
	 * + Chipselect stays active during the entire message
	 *   (unless modअगरied by spi_transfer.cs_change != 0).
	 * + The message transfers use घड़ी and SPI mode parameters
	 *   previously established by setup() क्रम this device
	 */
	पूर्णांक			(*transfer)(काष्ठा spi_device *spi,
						काष्ठा spi_message *mesg);

	/* called on release() to मुक्त memory provided by spi_controller */
	व्योम			(*cleanup)(काष्ठा spi_device *spi);

	/*
	 * Used to enable core support क्रम DMA handling, अगर can_dma()
	 * exists and वापसs true then the transfer will be mapped
	 * prior to transfer_one() being called.  The driver should
	 * not modअगरy or store xfer and dma_tx and dma_rx must be set
	 * जबतक the device is prepared.
	 */
	bool			(*can_dma)(काष्ठा spi_controller *ctlr,
					   काष्ठा spi_device *spi,
					   काष्ठा spi_transfer *xfer);

	/*
	 * These hooks are क्रम drivers that want to use the generic
	 * controller transfer queueing mechanism. If these are used, the
	 * transfer() function above must NOT be specअगरied by the driver.
	 * Over समय we expect SPI drivers to be phased over to this API.
	 */
	bool				queued;
	काष्ठा kthपढ़ो_worker		*kworker;
	काष्ठा kthपढ़ो_work		pump_messages;
	spinlock_t			queue_lock;
	काष्ठा list_head		queue;
	काष्ठा spi_message		*cur_msg;
	bool				idling;
	bool				busy;
	bool				running;
	bool				rt;
	bool				स्वतः_runसमय_pm;
	bool                            cur_msg_prepared;
	bool				cur_msg_mapped;
	bool				last_cs_enable;
	bool				last_cs_mode_high;
	bool                            fallback;
	काष्ठा completion               xfer_completion;
	माप_प्रकार				max_dma_len;

	पूर्णांक (*prepare_transfer_hardware)(काष्ठा spi_controller *ctlr);
	पूर्णांक (*transfer_one_message)(काष्ठा spi_controller *ctlr,
				    काष्ठा spi_message *mesg);
	पूर्णांक (*unprepare_transfer_hardware)(काष्ठा spi_controller *ctlr);
	पूर्णांक (*prepare_message)(काष्ठा spi_controller *ctlr,
			       काष्ठा spi_message *message);
	पूर्णांक (*unprepare_message)(काष्ठा spi_controller *ctlr,
				 काष्ठा spi_message *message);
	पूर्णांक (*slave_पात)(काष्ठा spi_controller *ctlr);

	/*
	 * These hooks are क्रम drivers that use a generic implementation
	 * of transfer_one_message() provided by the core.
	 */
	व्योम (*set_cs)(काष्ठा spi_device *spi, bool enable);
	पूर्णांक (*transfer_one)(काष्ठा spi_controller *ctlr, काष्ठा spi_device *spi,
			    काष्ठा spi_transfer *transfer);
	व्योम (*handle_err)(काष्ठा spi_controller *ctlr,
			   काष्ठा spi_message *message);

	/* Optimized handlers क्रम SPI memory-like operations. */
	स्थिर काष्ठा spi_controller_mem_ops *mem_ops;

	/* CS delays */
	काष्ठा spi_delay	cs_setup;
	काष्ठा spi_delay	cs_hold;
	काष्ठा spi_delay	cs_inactive;

	/* gpio chip select */
	पूर्णांक			*cs_gpios;
	काष्ठा gpio_desc	**cs_gpiods;
	bool			use_gpio_descriptors;
	s8			unused_native_cs;
	s8			max_native_cs;

	/* statistics */
	काष्ठा spi_statistics	statistics;

	/* DMA channels क्रम use with core dmaengine helpers */
	काष्ठा dma_chan		*dma_tx;
	काष्ठा dma_chan		*dma_rx;

	/* dummy data क्रम full duplex devices */
	व्योम			*dummy_rx;
	व्योम			*dummy_tx;

	पूर्णांक (*fw_translate_cs)(काष्ठा spi_controller *ctlr, अचिन्हित cs);

	/*
	 * Driver sets this field to indicate it is able to snapshot SPI
	 * transfers (needed e.g. क्रम पढ़ोing the समय of POSIX घड़ीs)
	 */
	bool			ptp_sts_supported;

	/* Interrupt enable state during PTP प्रणाली बारtamping */
	अचिन्हित दीर्घ		irq_flags;
पूर्ण;

अटल अंतरभूत व्योम *spi_controller_get_devdata(काष्ठा spi_controller *ctlr)
अणु
	वापस dev_get_drvdata(&ctlr->dev);
पूर्ण

अटल अंतरभूत व्योम spi_controller_set_devdata(काष्ठा spi_controller *ctlr,
					      व्योम *data)
अणु
	dev_set_drvdata(&ctlr->dev, data);
पूर्ण

अटल अंतरभूत काष्ठा spi_controller *spi_controller_get(काष्ठा spi_controller *ctlr)
अणु
	अगर (!ctlr || !get_device(&ctlr->dev))
		वापस शून्य;
	वापस ctlr;
पूर्ण

अटल अंतरभूत व्योम spi_controller_put(काष्ठा spi_controller *ctlr)
अणु
	अगर (ctlr)
		put_device(&ctlr->dev);
पूर्ण

अटल अंतरभूत bool spi_controller_is_slave(काष्ठा spi_controller *ctlr)
अणु
	वापस IS_ENABLED(CONFIG_SPI_SLAVE) && ctlr->slave;
पूर्ण

/* PM calls that need to be issued by the driver */
बाह्य पूर्णांक spi_controller_suspend(काष्ठा spi_controller *ctlr);
बाह्य पूर्णांक spi_controller_resume(काष्ठा spi_controller *ctlr);

/* Calls the driver make to पूर्णांकeract with the message queue */
बाह्य काष्ठा spi_message *spi_get_next_queued_message(काष्ठा spi_controller *ctlr);
बाह्य व्योम spi_finalize_current_message(काष्ठा spi_controller *ctlr);
बाह्य व्योम spi_finalize_current_transfer(काष्ठा spi_controller *ctlr);

/* Helper calls क्रम driver to बारtamp transfer */
व्योम spi_take_बारtamp_pre(काष्ठा spi_controller *ctlr,
			    काष्ठा spi_transfer *xfer,
			    माप_प्रकार progress, bool irqs_off);
व्योम spi_take_बारtamp_post(काष्ठा spi_controller *ctlr,
			     काष्ठा spi_transfer *xfer,
			     माप_प्रकार progress, bool irqs_off);

/* the spi driver core manages memory क्रम the spi_controller classdev */
बाह्य काष्ठा spi_controller *__spi_alloc_controller(काष्ठा device *host,
						अचिन्हित पूर्णांक size, bool slave);

अटल अंतरभूत काष्ठा spi_controller *spi_alloc_master(काष्ठा device *host,
						      अचिन्हित पूर्णांक size)
अणु
	वापस __spi_alloc_controller(host, size, false);
पूर्ण

अटल अंतरभूत काष्ठा spi_controller *spi_alloc_slave(काष्ठा device *host,
						     अचिन्हित पूर्णांक size)
अणु
	अगर (!IS_ENABLED(CONFIG_SPI_SLAVE))
		वापस शून्य;

	वापस __spi_alloc_controller(host, size, true);
पूर्ण

काष्ठा spi_controller *__devm_spi_alloc_controller(काष्ठा device *dev,
						   अचिन्हित पूर्णांक size,
						   bool slave);

अटल अंतरभूत काष्ठा spi_controller *devm_spi_alloc_master(काष्ठा device *dev,
							   अचिन्हित पूर्णांक size)
अणु
	वापस __devm_spi_alloc_controller(dev, size, false);
पूर्ण

अटल अंतरभूत काष्ठा spi_controller *devm_spi_alloc_slave(काष्ठा device *dev,
							  अचिन्हित पूर्णांक size)
अणु
	अगर (!IS_ENABLED(CONFIG_SPI_SLAVE))
		वापस शून्य;

	वापस __devm_spi_alloc_controller(dev, size, true);
पूर्ण

बाह्य पूर्णांक spi_रेजिस्टर_controller(काष्ठा spi_controller *ctlr);
बाह्य पूर्णांक devm_spi_रेजिस्टर_controller(काष्ठा device *dev,
					काष्ठा spi_controller *ctlr);
बाह्य व्योम spi_unरेजिस्टर_controller(काष्ठा spi_controller *ctlr);

बाह्य काष्ठा spi_controller *spi_busnum_to_master(u16 busnum);

/*
 * SPI resource management जबतक processing a SPI message
 */

प्रकार व्योम (*spi_res_release_t)(काष्ठा spi_controller *ctlr,
				  काष्ठा spi_message *msg,
				  व्योम *res);

/**
 * काष्ठा spi_res - spi resource management काष्ठाure
 * @entry:   list entry
 * @release: release code called prior to मुक्तing this resource
 * @data:    extra data allocated क्रम the specअगरic use-हाल
 *
 * this is based on ideas from devres, but focused on lअगरe-cycle
 * management during spi_message processing
 */
काष्ठा spi_res अणु
	काष्ठा list_head        entry;
	spi_res_release_t       release;
	अचिन्हित दीर्घ दीर्घ      data[]; /* guarantee ull alignment */
पूर्ण;

बाह्य व्योम *spi_res_alloc(काष्ठा spi_device *spi,
			   spi_res_release_t release,
			   माप_प्रकार size, gfp_t gfp);
बाह्य व्योम spi_res_add(काष्ठा spi_message *message, व्योम *res);
बाह्य व्योम spi_res_मुक्त(व्योम *res);

बाह्य व्योम spi_res_release(काष्ठा spi_controller *ctlr,
			    काष्ठा spi_message *message);

/*---------------------------------------------------------------------------*/

/*
 * I/O INTERFACE between SPI controller and protocol drivers
 *
 * Protocol drivers use a queue of spi_messages, each transferring data
 * between the controller and memory buffers.
 *
 * The spi_messages themselves consist of a series of पढ़ो+ग_लिखो transfer
 * segments.  Those segments always पढ़ो the same number of bits as they
 * ग_लिखो; but one or the other is easily ignored by passing a null buffer
 * poपूर्णांकer.  (This is unlike most types of I/O API, because SPI hardware
 * is full duplex.)
 *
 * NOTE:  Allocation of spi_transfer and spi_message memory is entirely
 * up to the protocol driver, which guarantees the पूर्णांकegrity of both (as
 * well as the data buffers) क्रम as दीर्घ as the message is queued.
 */

/**
 * काष्ठा spi_transfer - a पढ़ो/ग_लिखो buffer pair
 * @tx_buf: data to be written (dma-safe memory), or शून्य
 * @rx_buf: data to be पढ़ो (dma-safe memory), or शून्य
 * @tx_dma: DMA address of tx_buf, अगर @spi_message.is_dma_mapped
 * @rx_dma: DMA address of rx_buf, अगर @spi_message.is_dma_mapped
 * @tx_nbits: number of bits used क्रम writing. If 0 the शेष
 *      (SPI_NBITS_SINGLE) is used.
 * @rx_nbits: number of bits used क्रम पढ़ोing. If 0 the शेष
 *      (SPI_NBITS_SINGLE) is used.
 * @len: size of rx and tx buffers (in bytes)
 * @speed_hz: Select a speed other than the device शेष क्रम this
 *      transfer. If 0 the शेष (from @spi_device) is used.
 * @bits_per_word: select a bits_per_word other than the device शेष
 *      क्रम this transfer. If 0 the शेष (from @spi_device) is used.
 * @dummy_data: indicates transfer is dummy bytes transfer.
 * @cs_change: affects chipselect after this transfer completes
 * @cs_change_delay: delay between cs deनिश्चित and निश्चित when
 *      @cs_change is set and @spi_transfer is not the last in @spi_message
 * @delay: delay to be पूर्णांकroduced after this transfer beक्रमe
 *	(optionally) changing the chipselect status, then starting
 *	the next transfer or completing this @spi_message.
 * @word_delay: पूर्णांकer word delay to be पूर्णांकroduced after each word size
 *	(set by bits_per_word) transmission.
 * @effective_speed_hz: the effective SCK-speed that was used to
 *      transfer this transfer. Set to 0 अगर the spi bus driver करोes
 *      not support it.
 * @transfer_list: transfers are sequenced through @spi_message.transfers
 * @tx_sg: Scatterlist क्रम transmit, currently not क्रम client use
 * @rx_sg: Scatterlist क्रम receive, currently not क्रम client use
 * @ptp_sts_word_pre: The word (subject to bits_per_word semantics) offset
 *	within @tx_buf क्रम which the SPI device is requesting that the समय
 *	snapshot क्रम this transfer begins. Upon completing the SPI transfer,
 *	this value may have changed compared to what was requested, depending
 *	on the available snapshotting resolution (DMA transfer,
 *	@ptp_sts_supported is false, etc).
 * @ptp_sts_word_post: See @ptp_sts_word_post. The two can be equal (meaning
 *	that a single byte should be snapshotted).
 *	If the core takes care of the बारtamp (अगर @ptp_sts_supported is false
 *	क्रम this controller), it will set @ptp_sts_word_pre to 0, and
 *	@ptp_sts_word_post to the length of the transfer. This is करोne
 *	purposefully (instead of setting to spi_transfer->len - 1) to denote
 *	that a transfer-level snapshot taken from within the driver may still
 *	be of higher quality.
 * @ptp_sts: Poपूर्णांकer to a memory location held by the SPI slave device where a
 *	PTP प्रणाली बारtamp काष्ठाure may lie. If drivers use PIO or their
 *	hardware has some sort of assist क्रम retrieving exact transfer timing,
 *	they can (and should) निश्चित @ptp_sts_supported and populate this
 *	काष्ठाure using the ptp_पढ़ो_प्रणाली_*ts helper functions.
 *	The बारtamp must represent the समय at which the SPI slave device has
 *	processed the word, i.e. the "pre" बारtamp should be taken beक्रमe
 *	transmitting the "pre" word, and the "post" बारtamp after receiving
 *	transmit confirmation from the controller क्रम the "post" word.
 * @बारtamped: true अगर the transfer has been बारtamped
 * @error: Error status logged by spi controller driver.
 *
 * SPI transfers always ग_लिखो the same number of bytes as they पढ़ो.
 * Protocol drivers should always provide @rx_buf and/or @tx_buf.
 * In some हालs, they may also want to provide DMA addresses क्रम
 * the data being transferred; that may reduce overhead, when the
 * underlying driver uses dma.
 *
 * If the transmit buffer is null, zeroes will be shअगरted out
 * जबतक filling @rx_buf.  If the receive buffer is null, the data
 * shअगरted in will be discarded.  Only "len" bytes shअगरt out (or in).
 * It's an error to try to shअगरt out a partial word.  (For example, by
 * shअगरting out three bytes with word size of sixteen or twenty bits;
 * the क्रमmer uses two bytes per word, the latter uses four bytes.)
 *
 * In-memory data values are always in native CPU byte order, translated
 * from the wire byte order (big-endian except with SPI_LSB_FIRST).  So
 * क्रम example when bits_per_word is sixteen, buffers are 2N bytes दीर्घ
 * (@len = 2N) and hold N sixteen bit words in CPU byte order.
 *
 * When the word size of the SPI transfer is not a घातer-of-two multiple
 * of eight bits, those in-memory words include extra bits.  In-memory
 * words are always seen by protocol drivers as right-justअगरied, so the
 * undefined (rx) or unused (tx) bits are always the most signअगरicant bits.
 *
 * All SPI transfers start with the relevant chipselect active.  Normally
 * it stays selected until after the last transfer in a message.  Drivers
 * can affect the chipselect संकेत using cs_change.
 *
 * (i) If the transfer isn't the last one in the message, this flag is
 * used to make the chipselect briefly go inactive in the middle of the
 * message.  Toggling chipselect in this way may be needed to terminate
 * a chip command, letting a single spi_message perक्रमm all of group of
 * chip transactions together.
 *
 * (ii) When the transfer is the last one in the message, the chip may
 * stay selected until the next transfer.  On multi-device SPI busses
 * with nothing blocking messages going to other devices, this is just
 * a perक्रमmance hपूर्णांक; starting a message to another device deselects
 * this one.  But in other हालs, this can be used to ensure correctness.
 * Some devices need protocol transactions to be built from a series of
 * spi_message submissions, where the content of one message is determined
 * by the results of previous messages and where the whole transaction
 * ends when the chipselect goes पूर्णांकactive.
 *
 * When SPI can transfer in 1x,2x or 4x. It can get this transfer inक्रमmation
 * from device through @tx_nbits and @rx_nbits. In Bi-direction, these
 * two should both be set. User can set transfer mode with SPI_NBITS_SINGLE(1x)
 * SPI_NBITS_DUAL(2x) and SPI_NBITS_QUAD(4x) to support these three transfer.
 *
 * The code that submits an spi_message (and its spi_transfers)
 * to the lower layers is responsible क्रम managing its memory.
 * Zero-initialize every field you करोn't set up explicitly, to
 * insulate against future API updates.  After you submit a message
 * and its transfers, ignore them until its completion callback.
 */
काष्ठा spi_transfer अणु
	/* it's ok अगर tx_buf == rx_buf (right?)
	 * क्रम MicroWire, one buffer must be null
	 * buffers must work with dma_*map_single() calls, unless
	 *   spi_message.is_dma_mapped reports a pre-existing mapping
	 */
	स्थिर व्योम	*tx_buf;
	व्योम		*rx_buf;
	अचिन्हित	len;

	dma_addr_t	tx_dma;
	dma_addr_t	rx_dma;
	काष्ठा sg_table tx_sg;
	काष्ठा sg_table rx_sg;

	अचिन्हित	dummy_data:1;
	अचिन्हित	cs_change:1;
	अचिन्हित	tx_nbits:3;
	अचिन्हित	rx_nbits:3;
#घोषणा	SPI_NBITS_SINGLE	0x01 /* 1bit transfer */
#घोषणा	SPI_NBITS_DUAL		0x02 /* 2bits transfer */
#घोषणा	SPI_NBITS_QUAD		0x04 /* 4bits transfer */
	u8		bits_per_word;
	काष्ठा spi_delay	delay;
	काष्ठा spi_delay	cs_change_delay;
	काष्ठा spi_delay	word_delay;
	u32		speed_hz;

	u32		effective_speed_hz;

	अचिन्हित पूर्णांक	ptp_sts_word_pre;
	अचिन्हित पूर्णांक	ptp_sts_word_post;

	काष्ठा ptp_प्रणाली_बारtamp *ptp_sts;

	bool		बारtamped;

	काष्ठा list_head transfer_list;

#घोषणा SPI_TRANS_FAIL_NO_START	BIT(0)
	u16		error;
पूर्ण;

/**
 * काष्ठा spi_message - one multi-segment SPI transaction
 * @transfers: list of transfer segments in this transaction
 * @spi: SPI device to which the transaction is queued
 * @is_dma_mapped: अगर true, the caller provided both dma and cpu भव
 *	addresses क्रम each transfer buffer
 * @complete: called to report transaction completions
 * @context: the argument to complete() when it's called
 * @frame_length: the total number of bytes in the message
 * @actual_length: the total number of bytes that were transferred in all
 *	successful segments
 * @status: zero क्रम success, अन्यथा negative त्रुटि_सं
 * @queue: क्रम use by whichever driver currently owns the message
 * @state: क्रम use by whichever driver currently owns the message
 * @resources: क्रम resource management when the spi message is processed
 *
 * A @spi_message is used to execute an atomic sequence of data transfers,
 * each represented by a काष्ठा spi_transfer.  The sequence is "atomic"
 * in the sense that no other spi_message may use that SPI bus until that
 * sequence completes.  On some प्रणालीs, many such sequences can execute as
 * a single programmed DMA transfer.  On all प्रणालीs, these messages are
 * queued, and might complete after transactions to other devices.  Messages
 * sent to a given spi_device are always executed in FIFO order.
 *
 * The code that submits an spi_message (and its spi_transfers)
 * to the lower layers is responsible क्रम managing its memory.
 * Zero-initialize every field you करोn't set up explicitly, to
 * insulate against future API updates.  After you submit a message
 * and its transfers, ignore them until its completion callback.
 */
काष्ठा spi_message अणु
	काष्ठा list_head	transfers;

	काष्ठा spi_device	*spi;

	अचिन्हित		is_dma_mapped:1;

	/* REVISIT:  we might want a flag affecting the behavior of the
	 * last transfer ... allowing things like "read 16 bit length L"
	 * immediately followed by "read L bytes".  Basically imposing
	 * a specअगरic message scheduling algorithm.
	 *
	 * Some controller drivers (message-at-a-समय queue processing)
	 * could provide that as their शेष scheduling algorithm.  But
	 * others (with multi-message pipelines) could need a flag to
	 * tell them about such special हालs.
	 */

	/* completion is reported through a callback */
	व्योम			(*complete)(व्योम *context);
	व्योम			*context;
	अचिन्हित		frame_length;
	अचिन्हित		actual_length;
	पूर्णांक			status;

	/* क्रम optional use by whatever driver currently owns the
	 * spi_message ...  between calls to spi_async and then later
	 * complete(), that's the spi_controller controller driver.
	 */
	काष्ठा list_head	queue;
	व्योम			*state;

	/* list of spi_res reources when the spi message is processed */
	काष्ठा list_head        resources;
पूर्ण;

अटल अंतरभूत व्योम spi_message_init_no_स_रखो(काष्ठा spi_message *m)
अणु
	INIT_LIST_HEAD(&m->transfers);
	INIT_LIST_HEAD(&m->resources);
पूर्ण

अटल अंतरभूत व्योम spi_message_init(काष्ठा spi_message *m)
अणु
	स_रखो(m, 0, माप *m);
	spi_message_init_no_स_रखो(m);
पूर्ण

अटल अंतरभूत व्योम
spi_message_add_tail(काष्ठा spi_transfer *t, काष्ठा spi_message *m)
अणु
	list_add_tail(&t->transfer_list, &m->transfers);
पूर्ण

अटल अंतरभूत व्योम
spi_transfer_del(काष्ठा spi_transfer *t)
अणु
	list_del(&t->transfer_list);
पूर्ण

अटल अंतरभूत पूर्णांक
spi_transfer_delay_exec(काष्ठा spi_transfer *t)
अणु
	वापस spi_delay_exec(&t->delay, t);
पूर्ण

/**
 * spi_message_init_with_transfers - Initialize spi_message and append transfers
 * @m: spi_message to be initialized
 * @xfers: An array of spi transfers
 * @num_xfers: Number of items in the xfer array
 *
 * This function initializes the given spi_message and adds each spi_transfer in
 * the given array to the message.
 */
अटल अंतरभूत व्योम
spi_message_init_with_transfers(काष्ठा spi_message *m,
काष्ठा spi_transfer *xfers, अचिन्हित पूर्णांक num_xfers)
अणु
	अचिन्हित पूर्णांक i;

	spi_message_init(m);
	क्रम (i = 0; i < num_xfers; ++i)
		spi_message_add_tail(&xfers[i], m);
पूर्ण

/* It's fine to embed message and transaction काष्ठाures in other data
 * काष्ठाures so दीर्घ as you करोn't free them while they're in use.
 */

अटल अंतरभूत काष्ठा spi_message *spi_message_alloc(अचिन्हित ntrans, gfp_t flags)
अणु
	काष्ठा spi_message *m;

	m = kzalloc(माप(काष्ठा spi_message)
			+ ntrans * माप(काष्ठा spi_transfer),
			flags);
	अगर (m) अणु
		अचिन्हित i;
		काष्ठा spi_transfer *t = (काष्ठा spi_transfer *)(m + 1);

		spi_message_init_no_स_रखो(m);
		क्रम (i = 0; i < ntrans; i++, t++)
			spi_message_add_tail(t, m);
	पूर्ण
	वापस m;
पूर्ण

अटल अंतरभूत व्योम spi_message_मुक्त(काष्ठा spi_message *m)
अणु
	kमुक्त(m);
पूर्ण

बाह्य पूर्णांक spi_set_cs_timing(काष्ठा spi_device *spi,
			     काष्ठा spi_delay *setup,
			     काष्ठा spi_delay *hold,
			     काष्ठा spi_delay *inactive);

बाह्य पूर्णांक spi_setup(काष्ठा spi_device *spi);
बाह्य पूर्णांक spi_async(काष्ठा spi_device *spi, काष्ठा spi_message *message);
बाह्य पूर्णांक spi_async_locked(काष्ठा spi_device *spi,
			    काष्ठा spi_message *message);
बाह्य पूर्णांक spi_slave_पात(काष्ठा spi_device *spi);

अटल अंतरभूत माप_प्रकार
spi_max_message_size(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;

	अगर (!ctlr->max_message_size)
		वापस SIZE_MAX;
	वापस ctlr->max_message_size(spi);
पूर्ण

अटल अंतरभूत माप_प्रकार
spi_max_transfer_size(काष्ठा spi_device *spi)
अणु
	काष्ठा spi_controller *ctlr = spi->controller;
	माप_प्रकार tr_max = SIZE_MAX;
	माप_प्रकार msg_max = spi_max_message_size(spi);

	अगर (ctlr->max_transfer_size)
		tr_max = ctlr->max_transfer_size(spi);

	/* transfer size limit must not be greater than messsage size limit */
	वापस min(tr_max, msg_max);
पूर्ण

/**
 * spi_is_bpw_supported - Check अगर bits per word is supported
 * @spi: SPI device
 * @bpw: Bits per word
 *
 * This function checks to see अगर the SPI controller supports @bpw.
 *
 * Returns:
 * True अगर @bpw is supported, false otherwise.
 */
अटल अंतरभूत bool spi_is_bpw_supported(काष्ठा spi_device *spi, u32 bpw)
अणु
	u32 bpw_mask = spi->master->bits_per_word_mask;

	अगर (bpw == 8 || (bpw <= 32 && bpw_mask & SPI_BPW_MASK(bpw)))
		वापस true;

	वापस false;
पूर्ण

/*---------------------------------------------------------------------------*/

/* SPI transfer replacement methods which make use of spi_res */

काष्ठा spi_replaced_transfers;
प्रकार व्योम (*spi_replaced_release_t)(काष्ठा spi_controller *ctlr,
				       काष्ठा spi_message *msg,
				       काष्ठा spi_replaced_transfers *res);
/**
 * काष्ठा spi_replaced_transfers - काष्ठाure describing the spi_transfer
 *                                 replacements that have occurred
 *                                 so that they can get reverted
 * @release:            some extra release code to get executed prior to
 *                      relasing this काष्ठाure
 * @extradata:          poपूर्णांकer to some extra data अगर requested or शून्य
 * @replaced_transfers: transfers that have been replaced and which need
 *                      to get restored
 * @replaced_after:     the transfer after which the @replaced_transfers
 *                      are to get re-inserted
 * @inserted:           number of transfers inserted
 * @inserted_transfers: array of spi_transfers of array-size @inserted,
 *                      that have been replacing replaced_transfers
 *
 * note: that @extradata will poपूर्णांक to @inserted_transfers[@inserted]
 * अगर some extra allocation is requested, so alignment will be the same
 * as क्रम spi_transfers
 */
काष्ठा spi_replaced_transfers अणु
	spi_replaced_release_t release;
	व्योम *extradata;
	काष्ठा list_head replaced_transfers;
	काष्ठा list_head *replaced_after;
	माप_प्रकार inserted;
	काष्ठा spi_transfer inserted_transfers[];
पूर्ण;

बाह्य काष्ठा spi_replaced_transfers *spi_replace_transfers(
	काष्ठा spi_message *msg,
	काष्ठा spi_transfer *xfer_first,
	माप_प्रकार हटाओ,
	माप_प्रकार insert,
	spi_replaced_release_t release,
	माप_प्रकार extradatasize,
	gfp_t gfp);

/*---------------------------------------------------------------------------*/

/* SPI transfer transक्रमmation methods */

बाह्य पूर्णांक spi_split_transfers_maxsize(काष्ठा spi_controller *ctlr,
				       काष्ठा spi_message *msg,
				       माप_प्रकार maxsize,
				       gfp_t gfp);

/*---------------------------------------------------------------------------*/

/* All these synchronous SPI transfer routines are utilities layered
 * over the core async transfer primitive.  Here, "synchronous" means
 * they will sleep unपूर्णांकerruptibly until the async transfer completes.
 */

बाह्य पूर्णांक spi_sync(काष्ठा spi_device *spi, काष्ठा spi_message *message);
बाह्य पूर्णांक spi_sync_locked(काष्ठा spi_device *spi, काष्ठा spi_message *message);
बाह्य पूर्णांक spi_bus_lock(काष्ठा spi_controller *ctlr);
बाह्य पूर्णांक spi_bus_unlock(काष्ठा spi_controller *ctlr);

/**
 * spi_sync_transfer - synchronous SPI data transfer
 * @spi: device with which data will be exchanged
 * @xfers: An array of spi_transfers
 * @num_xfers: Number of items in the xfer array
 * Context: can sleep
 *
 * Does a synchronous SPI data transfer of the given spi_transfer array.
 *
 * For more specअगरic semantics see spi_sync().
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
अटल अंतरभूत पूर्णांक
spi_sync_transfer(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfers,
	अचिन्हित पूर्णांक num_xfers)
अणु
	काष्ठा spi_message msg;

	spi_message_init_with_transfers(&msg, xfers, num_xfers);

	वापस spi_sync(spi, &msg);
पूर्ण

/**
 * spi_ग_लिखो - SPI synchronous ग_लिखो
 * @spi: device to which data will be written
 * @buf: data buffer
 * @len: data buffer size
 * Context: can sleep
 *
 * This function ग_लिखोs the buffer @buf.
 * Callable only from contexts that can sleep.
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
अटल अंतरभूत पूर्णांक
spi_ग_लिखो(काष्ठा spi_device *spi, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spi_transfer	t = अणु
			.tx_buf		= buf,
			.len		= len,
		पूर्ण;

	वापस spi_sync_transfer(spi, &t, 1);
पूर्ण

/**
 * spi_पढ़ो - SPI synchronous पढ़ो
 * @spi: device from which data will be पढ़ो
 * @buf: data buffer
 * @len: data buffer size
 * Context: can sleep
 *
 * This function पढ़ोs the buffer @buf.
 * Callable only from contexts that can sleep.
 *
 * Return: zero on success, अन्यथा a negative error code.
 */
अटल अंतरभूत पूर्णांक
spi_पढ़ो(काष्ठा spi_device *spi, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spi_transfer	t = अणु
			.rx_buf		= buf,
			.len		= len,
		पूर्ण;

	वापस spi_sync_transfer(spi, &t, 1);
पूर्ण

/* this copies txbuf and rxbuf data; क्रम small transfers only! */
बाह्य पूर्णांक spi_ग_लिखो_then_पढ़ो(काष्ठा spi_device *spi,
		स्थिर व्योम *txbuf, अचिन्हित n_tx,
		व्योम *rxbuf, अचिन्हित n_rx);

/**
 * spi_w8r8 - SPI synchronous 8 bit ग_लिखो followed by 8 bit पढ़ो
 * @spi: device with which data will be exchanged
 * @cmd: command to be written beक्रमe data is पढ़ो back
 * Context: can sleep
 *
 * Callable only from contexts that can sleep.
 *
 * Return: the (अचिन्हित) eight bit number वापसed by the
 * device, or अन्यथा a negative error code.
 */
अटल अंतरभूत sमाप_प्रकार spi_w8r8(काष्ठा spi_device *spi, u8 cmd)
अणु
	sमाप_प्रकार			status;
	u8			result;

	status = spi_ग_लिखो_then_पढ़ो(spi, &cmd, 1, &result, 1);

	/* वापस negative त्रुटि_सं or अचिन्हित value */
	वापस (status < 0) ? status : result;
पूर्ण

/**
 * spi_w8r16 - SPI synchronous 8 bit ग_लिखो followed by 16 bit पढ़ो
 * @spi: device with which data will be exchanged
 * @cmd: command to be written beक्रमe data is पढ़ो back
 * Context: can sleep
 *
 * The number is वापसed in wire-order, which is at least someबार
 * big-endian.
 *
 * Callable only from contexts that can sleep.
 *
 * Return: the (अचिन्हित) sixteen bit number वापसed by the
 * device, or अन्यथा a negative error code.
 */
अटल अंतरभूत sमाप_प्रकार spi_w8r16(काष्ठा spi_device *spi, u8 cmd)
अणु
	sमाप_प्रकार			status;
	u16			result;

	status = spi_ग_लिखो_then_पढ़ो(spi, &cmd, 1, &result, 2);

	/* वापस negative त्रुटि_सं or अचिन्हित value */
	वापस (status < 0) ? status : result;
पूर्ण

/**
 * spi_w8r16be - SPI synchronous 8 bit ग_लिखो followed by 16 bit big-endian पढ़ो
 * @spi: device with which data will be exchanged
 * @cmd: command to be written beक्रमe data is पढ़ो back
 * Context: can sleep
 *
 * This function is similar to spi_w8r16, with the exception that it will
 * convert the पढ़ो 16 bit data word from big-endian to native endianness.
 *
 * Callable only from contexts that can sleep.
 *
 * Return: the (अचिन्हित) sixteen bit number वापसed by the device in cpu
 * endianness, or अन्यथा a negative error code.
 */
अटल अंतरभूत sमाप_प्रकार spi_w8r16be(काष्ठा spi_device *spi, u8 cmd)

अणु
	sमाप_प्रकार status;
	__be16 result;

	status = spi_ग_लिखो_then_पढ़ो(spi, &cmd, 1, &result, 2);
	अगर (status < 0)
		वापस status;

	वापस be16_to_cpu(result);
पूर्ण

/*---------------------------------------------------------------------------*/

/*
 * INTERFACE between board init code and SPI infraकाष्ठाure.
 *
 * No SPI driver ever sees these SPI device table segments, but
 * it's how the SPI core (or adapters that get hotplugged) grows
 * the driver model tree.
 *
 * As a rule, SPI devices can't be probed.  Instead, board init code
 * provides a table listing the devices which are present, with enough
 * inक्रमmation to bind and set up the device's driver.  There's basic
 * support क्रम nonअटल configurations too; enough to handle adding
 * parport adapters, or microcontrollers acting as USB-to-SPI bridges.
 */

/**
 * काष्ठा spi_board_info - board-specअगरic ढाँचा क्रम a SPI device
 * @modalias: Initializes spi_device.modalias; identअगरies the driver.
 * @platक्रमm_data: Initializes spi_device.platक्रमm_data; the particular
 *	data stored there is driver-specअगरic.
 * @swnode: Software node क्रम the device.
 * @controller_data: Initializes spi_device.controller_data; some
 *	controllers need hपूर्णांकs about hardware setup, e.g. क्रम DMA.
 * @irq: Initializes spi_device.irq; depends on how the board is wired.
 * @max_speed_hz: Initializes spi_device.max_speed_hz; based on limits
 *	from the chip datasheet and board-specअगरic संकेत quality issues.
 * @bus_num: Identअगरies which spi_controller parents the spi_device; unused
 *	by spi_new_device(), and otherwise depends on board wiring.
 * @chip_select: Initializes spi_device.chip_select; depends on how
 *	the board is wired.
 * @mode: Initializes spi_device.mode; based on the chip datasheet, board
 *	wiring (some devices support both 3WIRE and standard modes), and
 *	possibly presence of an inverter in the chipselect path.
 *
 * When adding new SPI devices to the device tree, these काष्ठाures serve
 * as a partial device ढाँचा.  They hold inक्रमmation which can't always
 * be determined by drivers.  Inक्रमmation that probe() can establish (such
 * as the शेष transfer wordsize) is not included here.
 *
 * These काष्ठाures are used in two places.  Their primary role is to
 * be stored in tables of board-specअगरic device descriptors, which are
 * declared early in board initialization and then used (much later) to
 * populate a controller's device tree after the that controller's driver
 * initializes.  A secondary (and atypical) role is as a parameter to
 * spi_new_device() call, which happens after those controller drivers
 * are active in some dynamic board configuration models.
 */
काष्ठा spi_board_info अणु
	/* the device name and module name are coupled, like platक्रमm_bus;
	 * "modalias" is normally the driver name.
	 *
	 * platक्रमm_data goes to spi_device.dev.platक्रमm_data,
	 * controller_data goes to spi_device.controller_data,
	 * irq is copied too
	 */
	अक्षर		modalias[SPI_NAME_SIZE];
	स्थिर व्योम	*platक्रमm_data;
	स्थिर काष्ठा software_node *swnode;
	व्योम		*controller_data;
	पूर्णांक		irq;

	/* slower संकेतing on noisy or low voltage boards */
	u32		max_speed_hz;


	/* bus_num is board specअगरic and matches the bus_num of some
	 * spi_controller that will probably be रेजिस्टरed later.
	 *
	 * chip_select reflects how this chip is wired to that master;
	 * it's less than num_chipselect.
	 */
	u16		bus_num;
	u16		chip_select;

	/* mode becomes spi_device.mode, and is essential क्रम chips
	 * where the शेष of SPI_CS_HIGH = 0 is wrong.
	 */
	u32		mode;

	/* ... may need additional spi_device chip config data here.
	 * aव्योम stuff protocol drivers can set; but include stuff
	 * needed to behave without being bound to a driver:
	 *  - quirks like घड़ी rate mattering when not selected
	 */
पूर्ण;

#अगर_घोषित	CONFIG_SPI
बाह्य पूर्णांक
spi_रेजिस्टर_board_info(काष्ठा spi_board_info स्थिर *info, अचिन्हित n);
#अन्यथा
/* board init code may ignore whether SPI is configured or not */
अटल अंतरभूत पूर्णांक
spi_रेजिस्टर_board_info(काष्ठा spi_board_info स्थिर *info, अचिन्हित n)
	अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* If you're hotplugging an adapter with devices (parport, usb, etc)
 * use spi_new_device() to describe each device.  You can also call
 * spi_unरेजिस्टर_device() to start making that device vanish, but
 * normally that would be handled by spi_unरेजिस्टर_controller().
 *
 * You can also use spi_alloc_device() and spi_add_device() to use a two
 * stage registration sequence क्रम each spi_device.  This gives the caller
 * some more control over the spi_device काष्ठाure beक्रमe it is रेजिस्टरed,
 * but requires that caller to initialize fields that would otherwise
 * be defined using the board info.
 */
बाह्य काष्ठा spi_device *
spi_alloc_device(काष्ठा spi_controller *ctlr);

बाह्य पूर्णांक
spi_add_device(काष्ठा spi_device *spi);

बाह्य काष्ठा spi_device *
spi_new_device(काष्ठा spi_controller *, काष्ठा spi_board_info *);

बाह्य व्योम spi_unरेजिस्टर_device(काष्ठा spi_device *spi);

बाह्य स्थिर काष्ठा spi_device_id *
spi_get_device_id(स्थिर काष्ठा spi_device *sdev);

अटल अंतरभूत bool
spi_transfer_is_last(काष्ठा spi_controller *ctlr, काष्ठा spi_transfer *xfer)
अणु
	वापस list_is_last(&xfer->transfer_list, &ctlr->cur_msg->transfers);
पूर्ण

/* OF support code */
#अगर IS_ENABLED(CONFIG_OF)

/* must call put_device() when करोne with वापसed spi_device device */
बाह्य काष्ठा spi_device *
of_find_spi_device_by_node(काष्ठा device_node *node);

#अन्यथा

अटल अंतरभूत काष्ठा spi_device *
of_find_spi_device_by_node(काष्ठा device_node *node)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* IS_ENABLED(CONFIG_OF) */

/* Compatibility layer */
#घोषणा spi_master			spi_controller

#घोषणा SPI_MASTER_HALF_DUPLEX		SPI_CONTROLLER_HALF_DUPLEX
#घोषणा SPI_MASTER_NO_RX		SPI_CONTROLLER_NO_RX
#घोषणा SPI_MASTER_NO_TX		SPI_CONTROLLER_NO_TX
#घोषणा SPI_MASTER_MUST_RX		SPI_CONTROLLER_MUST_RX
#घोषणा SPI_MASTER_MUST_TX		SPI_CONTROLLER_MUST_TX

#घोषणा spi_master_get_devdata(_ctlr)	spi_controller_get_devdata(_ctlr)
#घोषणा spi_master_set_devdata(_ctlr, _data)	\
	spi_controller_set_devdata(_ctlr, _data)
#घोषणा spi_master_get(_ctlr)		spi_controller_get(_ctlr)
#घोषणा spi_master_put(_ctlr)		spi_controller_put(_ctlr)
#घोषणा spi_master_suspend(_ctlr)	spi_controller_suspend(_ctlr)
#घोषणा spi_master_resume(_ctlr)	spi_controller_resume(_ctlr)

#घोषणा spi_रेजिस्टर_master(_ctlr)	spi_रेजिस्टर_controller(_ctlr)
#घोषणा devm_spi_रेजिस्टर_master(_dev, _ctlr) \
	devm_spi_रेजिस्टर_controller(_dev, _ctlr)
#घोषणा spi_unरेजिस्टर_master(_ctlr)	spi_unरेजिस्टर_controller(_ctlr)

#पूर्ण_अगर /* __LINUX_SPI_H */
