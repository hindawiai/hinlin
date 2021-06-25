<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00usb
	Abstract: Data काष्ठाures क्रम the rt2x00usb module.
 */

#अगर_अघोषित RT2X00USB_H
#घोषणा RT2X00USB_H

#समावेश <linux/usb.h>

#घोषणा to_usb_device_पूर्णांकf(d) \
(अणु \
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(d); \
	पूर्णांकerface_to_usbdev(पूर्णांकf); \
पूर्ण)

/*
 * For USB venकरोr requests we need to pass a समयout समय in ms, क्रम this we
 * use the REGISTER_TIMEOUT, however when loading firmware or पढ़ो EEPROM
 * a higher value is required. In that हाल we use the REGISTER_TIMEOUT_FIRMWARE
 * and EEPROM_TIMEOUT.
 */
#घोषणा REGISTER_TIMEOUT		100
#घोषणा REGISTER_TIMEOUT_FIRMWARE	1000
#घोषणा EEPROM_TIMEOUT			2000

/*
 * Cache size
 */
#घोषणा CSR_CACHE_SIZE			64

/*
 * USB request types.
 */
#घोषणा USB_VENDOR_REQUEST	( USB_TYPE_VENDOR | USB_RECIP_DEVICE )
#घोषणा USB_VENDOR_REQUEST_IN	( USB_सूची_IN | USB_VENDOR_REQUEST )
#घोषणा USB_VENDOR_REQUEST_OUT	( USB_सूची_OUT | USB_VENDOR_REQUEST )

/**
 * क्रमागत rt2x00usb_venकरोr_request: USB venकरोr commands.
 */
क्रमागत rt2x00usb_venकरोr_request अणु
	USB_DEVICE_MODE = 1,
	USB_SINGLE_WRITE = 2,
	USB_SINGLE_READ = 3,
	USB_MULTI_WRITE = 6,
	USB_MULTI_READ = 7,
	USB_EEPROM_WRITE = 8,
	USB_EEPROM_READ = 9,
	USB_LED_CONTROL = 10, /* RT73USB */
	USB_RX_CONTROL = 12,
पूर्ण;

/**
 * क्रमागत rt2x00usb_mode_offset: Device modes offset.
 */
क्रमागत rt2x00usb_mode_offset अणु
	USB_MODE_RESET = 1,
	USB_MODE_UNPLUG = 2,
	USB_MODE_FUNCTION = 3,
	USB_MODE_TEST = 4,
	USB_MODE_SLEEP = 7,	/* RT73USB */
	USB_MODE_FIRMWARE = 8,	/* RT73USB */
	USB_MODE_WAKEUP = 9,	/* RT73USB */
	USB_MODE_AUTORUN = 17, /* RT2800USB */
पूर्ण;

/**
 * rt2x00usb_venकरोr_request - Send रेजिस्टर command to device
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 * @request: USB venकरोr command (See &क्रमागत rt2x00usb_venकरोr_request)
 * @requesttype: Request type &USB_VENDOR_REQUEST_*
 * @offset: Register offset to perक्रमm action on
 * @value: Value to ग_लिखो to device
 * @buffer: Buffer where inक्रमmation will be पढ़ो/written to by device
 * @buffer_length: Size of &buffer
 * @समयout: Operation समयout
 *
 * This is the मुख्य function to communicate with the device,
 * the &buffer argument _must_ either be शून्य or poपूर्णांक to
 * a buffer allocated by kदो_स्मृति. Failure to करो so can lead
 * to unexpected behavior depending on the architecture.
 */
पूर्णांक rt2x00usb_venकरोr_request(काष्ठा rt2x00_dev *rt2x00dev,
			     स्थिर u8 request, स्थिर u8 requesttype,
			     स्थिर u16 offset, स्थिर u16 value,
			     व्योम *buffer, स्थिर u16 buffer_length,
			     स्थिर पूर्णांक समयout);

/**
 * rt2x00usb_venकरोr_request_buff - Send रेजिस्टर command to device (buffered)
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 * @request: USB venकरोr command (See &क्रमागत rt2x00usb_venकरोr_request)
 * @requesttype: Request type &USB_VENDOR_REQUEST_*
 * @offset: Register offset to perक्रमm action on
 * @buffer: Buffer where inक्रमmation will be पढ़ो/written to by device
 * @buffer_length: Size of &buffer
 *
 * This function will use a previously with kदो_स्मृति allocated cache
 * to communicate with the device. The contents of the buffer poपूर्णांकer
 * will be copied to this cache when writing, or पढ़ो from the cache
 * when पढ़ोing.
 * Buffers send to &rt2x00usb_venकरोr_request _must_ be allocated with
 * kदो_स्मृति. Hence the reason क्रम using a previously allocated cache
 * which has been allocated properly.
 */
पूर्णांक rt2x00usb_venकरोr_request_buff(काष्ठा rt2x00_dev *rt2x00dev,
				  स्थिर u8 request, स्थिर u8 requesttype,
				  स्थिर u16 offset, व्योम *buffer,
				  स्थिर u16 buffer_length);

/**
 * rt2x00usb_venकरोr_request_buff - Send रेजिस्टर command to device (buffered)
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 * @request: USB venकरोr command (See &क्रमागत rt2x00usb_venकरोr_request)
 * @requesttype: Request type &USB_VENDOR_REQUEST_*
 * @offset: Register offset to perक्रमm action on
 * @buffer: Buffer where inक्रमmation will be पढ़ो/written to by device
 * @buffer_length: Size of &buffer
 * @समयout: Operation समयout
 *
 * A version of &rt2x00usb_venकरोr_request_buff which must be called
 * अगर the usb_cache_mutex is alपढ़ोy held.
 */
पूर्णांक rt2x00usb_venकरोr_req_buff_lock(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर u8 request, स्थिर u8 requesttype,
				   स्थिर u16 offset, व्योम *buffer,
				   स्थिर u16 buffer_length, स्थिर पूर्णांक समयout);

/**
 * rt2x00usb_venकरोr_request_sw - Send single रेजिस्टर command to device
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 * @request: USB venकरोr command (See &क्रमागत rt2x00usb_venकरोr_request)
 * @offset: Register offset to perक्रमm action on
 * @value: Value to ग_लिखो to device
 * @समयout: Operation समयout
 *
 * Simple wrapper around rt2x00usb_venकरोr_request to ग_लिखो a single
 * command to the device. Since we करोn't use the buffer argument we
 * करोn't have to worry about kदो_स्मृति here.
 */
अटल अंतरभूत पूर्णांक rt2x00usb_venकरोr_request_sw(काष्ठा rt2x00_dev *rt2x00dev,
					      स्थिर u8 request,
					      स्थिर u16 offset,
					      स्थिर u16 value,
					      स्थिर पूर्णांक समयout)
अणु
	वापस rt2x00usb_venकरोr_request(rt2x00dev, request,
					USB_VENDOR_REQUEST_OUT, offset,
					value, शून्य, 0, समयout);
पूर्ण

/**
 * rt2x00usb_eeprom_पढ़ो - Read eeprom from device
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 * @eeprom: Poपूर्णांकer to eeprom array to store the inक्रमmation in
 * @length: Number of bytes to पढ़ो from the eeprom
 *
 * Simple wrapper around rt2x00usb_venकरोr_request to पढ़ो the eeprom
 * from the device. Note that the eeprom argument _must_ be allocated using
 * kदो_स्मृति क्रम correct handling inside the kernel USB layer.
 */
अटल अंतरभूत पूर्णांक rt2x00usb_eeprom_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
					__le16 *eeprom, स्थिर u16 length)
अणु
	वापस rt2x00usb_venकरोr_request(rt2x00dev, USB_EEPROM_READ,
					USB_VENDOR_REQUEST_IN, 0, 0,
					eeprom, length, EEPROM_TIMEOUT);
पूर्ण

/**
 * rt2x00usb_रेजिस्टर_पढ़ो - Read 32bit रेजिस्टर word
 * @rt2x00dev: Device poपूर्णांकer, see &काष्ठा rt2x00_dev.
 * @offset: Register offset
 *
 * This function is a simple wrapper क्रम 32bit रेजिस्टर access
 * through rt2x00usb_venकरोr_request_buff().
 */
अटल अंतरभूत u32 rt2x00usb_रेजिस्टर_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
					  स्थिर अचिन्हित पूर्णांक offset)
अणु
	__le32 reg = 0;
	rt2x00usb_venकरोr_request_buff(rt2x00dev, USB_MULTI_READ,
				      USB_VENDOR_REQUEST_IN, offset,
				      &reg, माप(reg));
	वापस le32_to_cpu(reg);
पूर्ण

/**
 * rt2x00usb_रेजिस्टर_पढ़ो_lock - Read 32bit रेजिस्टर word
 * @rt2x00dev: Device poपूर्णांकer, see &काष्ठा rt2x00_dev.
 * @offset: Register offset
 *
 * This function is a simple wrapper क्रम 32bit रेजिस्टर access
 * through rt2x00usb_venकरोr_req_buff_lock().
 */
अटल अंतरभूत u32 rt2x00usb_रेजिस्टर_पढ़ो_lock(काष्ठा rt2x00_dev *rt2x00dev,
					       स्थिर अचिन्हित पूर्णांक offset)
अणु
	__le32 reg = 0;
	rt2x00usb_venकरोr_req_buff_lock(rt2x00dev, USB_MULTI_READ,
				       USB_VENDOR_REQUEST_IN, offset,
				       &reg, माप(reg), REGISTER_TIMEOUT);
	वापस le32_to_cpu(reg);
पूर्ण

/**
 * rt2x00usb_रेजिस्टर_multiपढ़ो - Read 32bit रेजिस्टर words
 * @rt2x00dev: Device poपूर्णांकer, see &काष्ठा rt2x00_dev.
 * @offset: Register offset
 * @value: Poपूर्णांकer to where रेजिस्टर contents should be stored
 * @length: Length of the data
 *
 * This function is a simple wrapper क्रम 32bit रेजिस्टर access
 * through rt2x00usb_venकरोr_request_buff().
 */
अटल अंतरभूत व्योम rt2x00usb_रेजिस्टर_multiपढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
						स्थिर अचिन्हित पूर्णांक offset,
						व्योम *value, स्थिर u32 length)
अणु
	rt2x00usb_venकरोr_request_buff(rt2x00dev, USB_MULTI_READ,
				      USB_VENDOR_REQUEST_IN, offset,
				      value, length);
पूर्ण

/**
 * rt2x00usb_रेजिस्टर_ग_लिखो - Write 32bit रेजिस्टर word
 * @rt2x00dev: Device poपूर्णांकer, see &काष्ठा rt2x00_dev.
 * @offset: Register offset
 * @value: Data which should be written
 *
 * This function is a simple wrapper क्रम 32bit रेजिस्टर access
 * through rt2x00usb_venकरोr_request_buff().
 */
अटल अंतरभूत व्योम rt2x00usb_रेजिस्टर_ग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
					    स्थिर अचिन्हित पूर्णांक offset,
					    u32 value)
अणु
	__le32 reg = cpu_to_le32(value);
	rt2x00usb_venकरोr_request_buff(rt2x00dev, USB_MULTI_WRITE,
				      USB_VENDOR_REQUEST_OUT, offset,
				      &reg, माप(reg));
पूर्ण

/**
 * rt2x00usb_रेजिस्टर_ग_लिखो_lock - Write 32bit रेजिस्टर word
 * @rt2x00dev: Device poपूर्णांकer, see &काष्ठा rt2x00_dev.
 * @offset: Register offset
 * @value: Data which should be written
 *
 * This function is a simple wrapper क्रम 32bit रेजिस्टर access
 * through rt2x00usb_venकरोr_req_buff_lock().
 */
अटल अंतरभूत व्योम rt2x00usb_रेजिस्टर_ग_लिखो_lock(काष्ठा rt2x00_dev *rt2x00dev,
						 स्थिर अचिन्हित पूर्णांक offset,
						 u32 value)
अणु
	__le32 reg = cpu_to_le32(value);
	rt2x00usb_venकरोr_req_buff_lock(rt2x00dev, USB_MULTI_WRITE,
				       USB_VENDOR_REQUEST_OUT, offset,
				       &reg, माप(reg), REGISTER_TIMEOUT);
पूर्ण

/**
 * rt2x00usb_रेजिस्टर_multiग_लिखो - Write 32bit रेजिस्टर words
 * @rt2x00dev: Device poपूर्णांकer, see &काष्ठा rt2x00_dev.
 * @offset: Register offset
 * @value: Data which should be written
 * @length: Length of the data
 *
 * This function is a simple wrapper क्रम 32bit रेजिस्टर access
 * through rt2x00usb_venकरोr_request_buff().
 */
अटल अंतरभूत व्योम rt2x00usb_रेजिस्टर_multiग_लिखो(काष्ठा rt2x00_dev *rt2x00dev,
						 स्थिर अचिन्हित पूर्णांक offset,
						 स्थिर व्योम *value,
						 स्थिर u32 length)
अणु
	rt2x00usb_venकरोr_request_buff(rt2x00dev, USB_MULTI_WRITE,
				      USB_VENDOR_REQUEST_OUT, offset,
				      (व्योम *)value, length);
पूर्ण

/**
 * rt2x00usb_regbusy_पढ़ो - Read from रेजिस्टर with busy check
 * @rt2x00dev: Device poपूर्णांकer, see &काष्ठा rt2x00_dev.
 * @offset: Register offset
 * @field: Field to check अगर रेजिस्टर is busy
 * @reg: Poपूर्णांकer to where रेजिस्टर contents should be stored
 *
 * This function will पढ़ो the given रेजिस्टर, and checks अगर the
 * रेजिस्टर is busy. If it is, it will sleep क्रम a couple of
 * microseconds beक्रमe पढ़ोing the रेजिस्टर again. If the रेजिस्टर
 * is not पढ़ो after a certain समयout, this function will वापस
 * FALSE.
 */
पूर्णांक rt2x00usb_regbusy_पढ़ो(काष्ठा rt2x00_dev *rt2x00dev,
			   स्थिर अचिन्हित पूर्णांक offset,
			   स्थिर काष्ठा rt2x00_field32 field,
			   u32 *reg);

/**
 * rt2x00usb_रेजिस्टर_पढ़ो_async - Asynchronously पढ़ो 32bit रेजिस्टर word
 * @rt2x00dev: Device poपूर्णांकer, see &काष्ठा rt2x00_dev.
 * @offset: Register offset
 * @callback: Functon to call when पढ़ो completes.
 *
 * Submit a control URB to पढ़ो a 32bit रेजिस्टर. This safe to
 * be called from atomic context.  The callback will be called
 * when the URB completes. Otherwise the function is similar
 * to rt2x00usb_रेजिस्टर_पढ़ो().
 * When the callback function वापसs false, the memory will be cleaned up,
 * when it वापसs true, the urb will be fired again.
 */
व्योम rt2x00usb_रेजिस्टर_पढ़ो_async(काष्ठा rt2x00_dev *rt2x00dev,
				   स्थिर अचिन्हित पूर्णांक offset,
				   bool (*callback)(काष्ठा rt2x00_dev*, पूर्णांक, u32));

/*
 * Radio handlers
 */
व्योम rt2x00usb_disable_radio(काष्ठा rt2x00_dev *rt2x00dev);

/**
 * काष्ठा queue_entry_priv_usb: Per entry USB specअगरic inक्रमmation
 *
 * @urb: Urb काष्ठाure used क्रम device communication.
 */
काष्ठा queue_entry_priv_usb अणु
	काष्ठा urb *urb;
पूर्ण;

/**
 * काष्ठा queue_entry_priv_usb_bcn: Per TX entry USB specअगरic inक्रमmation
 *
 * The first section should match &काष्ठा queue_entry_priv_usb exactly.
 * rt2500usb can use this काष्ठाure to send a guardian byte when working
 * with beacons.
 *
 * @urb: Urb काष्ठाure used क्रम device communication.
 * @guardian_data: Set to 0, used क्रम sending the guardian data.
 * @guardian_urb: Urb काष्ठाure used to send the guardian data.
 */
काष्ठा queue_entry_priv_usb_bcn अणु
	काष्ठा urb *urb;

	अचिन्हित पूर्णांक guardian_data;
	काष्ठा urb *guardian_urb;
पूर्ण;

/**
 * rt2x00usb_kick_queue - Kick data queue
 * @queue: Data queue to kick
 *
 * This will walk through all entries of the queue and push all pending
 * frames to the hardware as a single burst.
 */
व्योम rt2x00usb_kick_queue(काष्ठा data_queue *queue);

/**
 * rt2x00usb_flush_queue - Flush data queue
 * @queue: Data queue to stop
 * @drop: True to drop all pending frames.
 *
 * This will walk through all entries of the queue and will optionally
 * समाप्त all URB's which were send to the device, or at least रुको until
 * they have been वापसed from the device..
 */
व्योम rt2x00usb_flush_queue(काष्ठा data_queue *queue, bool drop);

/**
 * rt2x00usb_watchकरोg - Watchकरोg क्रम USB communication
 * @rt2x00dev: Poपूर्णांकer to &काष्ठा rt2x00_dev
 *
 * Check the health of the USB communication and determine
 * अगर समयouts have occurred. If this is the हाल, this function
 * will reset all communication to restore functionality again.
 */
व्योम rt2x00usb_watchकरोg(काष्ठा rt2x00_dev *rt2x00dev);

/*
 * Device initialization handlers.
 */
व्योम rt2x00usb_clear_entry(काष्ठा queue_entry *entry);
पूर्णांक rt2x00usb_initialize(काष्ठा rt2x00_dev *rt2x00dev);
व्योम rt2x00usb_uninitialize(काष्ठा rt2x00_dev *rt2x00dev);

/*
 * USB driver handlers.
 */
पूर्णांक rt2x00usb_probe(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf,
		    स्थिर काष्ठा rt2x00_ops *ops);
व्योम rt2x00usb_disconnect(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf);
#अगर_घोषित CONFIG_PM
पूर्णांक rt2x00usb_suspend(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf, pm_message_t state);
पूर्णांक rt2x00usb_resume(काष्ठा usb_पूर्णांकerface *usb_पूर्णांकf);
#अन्यथा
#घोषणा rt2x00usb_suspend	शून्य
#घोषणा rt2x00usb_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

#पूर्ण_अगर /* RT2X00USB_H */
