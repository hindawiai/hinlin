<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MIPI DSI Bus
 *
 * Copyright (C) 2012-2013, Samsung Electronics, Co., Ltd.
 * Andrzej Hajda <a.hajda@samsung.com>
 */

#अगर_अघोषित __DRM_MIPI_DSI_H__
#घोषणा __DRM_MIPI_DSI_H__

#समावेश <linux/device.h>

काष्ठा mipi_dsi_host;
काष्ठा mipi_dsi_device;
काष्ठा drm_dsc_picture_parameter_set;

/* request ACK from peripheral */
#घोषणा MIPI_DSI_MSG_REQ_ACK	BIT(0)
/* use Low Power Mode to transmit message */
#घोषणा MIPI_DSI_MSG_USE_LPM	BIT(1)

/**
 * काष्ठा mipi_dsi_msg - पढ़ो/ग_लिखो DSI buffer
 * @channel: भव channel id
 * @type: payload data type
 * @flags: flags controlling this message transmission
 * @tx_len: length of @tx_buf
 * @tx_buf: data to be written
 * @rx_len: length of @rx_buf
 * @rx_buf: data to be पढ़ो, or शून्य
 */
काष्ठा mipi_dsi_msg अणु
	u8 channel;
	u8 type;
	u16 flags;

	माप_प्रकार tx_len;
	स्थिर व्योम *tx_buf;

	माप_प्रकार rx_len;
	व्योम *rx_buf;
पूर्ण;

bool mipi_dsi_packet_क्रमmat_is_लघु(u8 type);
bool mipi_dsi_packet_क्रमmat_is_दीर्घ(u8 type);

/**
 * काष्ठा mipi_dsi_packet - represents a MIPI DSI packet in protocol क्रमmat
 * @size: size (in bytes) of the packet
 * @header: the four bytes that make up the header (Data ID, Word Count or
 *     Packet Data, and ECC)
 * @payload_length: number of bytes in the payload
 * @payload: a poपूर्णांकer to a buffer containing the payload, अगर any
 */
काष्ठा mipi_dsi_packet अणु
	माप_प्रकार size;
	u8 header[4];
	माप_प्रकार payload_length;
	स्थिर u8 *payload;
पूर्ण;

पूर्णांक mipi_dsi_create_packet(काष्ठा mipi_dsi_packet *packet,
			   स्थिर काष्ठा mipi_dsi_msg *msg);

/**
 * काष्ठा mipi_dsi_host_ops - DSI bus operations
 * @attach: attach DSI device to DSI host
 * @detach: detach DSI device from DSI host
 * @transfer: transmit a DSI packet
 *
 * DSI packets transmitted by .transfer() are passed in as mipi_dsi_msg
 * काष्ठाures. This काष्ठाure contains inक्रमmation about the type of packet
 * being transmitted as well as the transmit and receive buffers. When an
 * error is encountered during transmission, this function will वापस a
 * negative error code. On success it shall वापस the number of bytes
 * transmitted क्रम ग_लिखो packets or the number of bytes received क्रम पढ़ो
 * packets.
 *
 * Note that typically DSI packet transmission is atomic, so the .transfer()
 * function will selकरोmly वापस anything other than the number of bytes
 * contained in the transmit buffer on success.
 */
काष्ठा mipi_dsi_host_ops अणु
	पूर्णांक (*attach)(काष्ठा mipi_dsi_host *host,
		      काष्ठा mipi_dsi_device *dsi);
	पूर्णांक (*detach)(काष्ठा mipi_dsi_host *host,
		      काष्ठा mipi_dsi_device *dsi);
	sमाप_प्रकार (*transfer)(काष्ठा mipi_dsi_host *host,
			    स्थिर काष्ठा mipi_dsi_msg *msg);
पूर्ण;

/**
 * काष्ठा mipi_dsi_host - DSI host device
 * @dev: driver model device node क्रम this DSI host
 * @ops: DSI host operations
 * @list: list management
 */
काष्ठा mipi_dsi_host अणु
	काष्ठा device *dev;
	स्थिर काष्ठा mipi_dsi_host_ops *ops;
	काष्ठा list_head list;
पूर्ण;

पूर्णांक mipi_dsi_host_रेजिस्टर(काष्ठा mipi_dsi_host *host);
व्योम mipi_dsi_host_unरेजिस्टर(काष्ठा mipi_dsi_host *host);
काष्ठा mipi_dsi_host *of_find_mipi_dsi_host_by_node(काष्ठा device_node *node);

/* DSI mode flags */

/* video mode */
#घोषणा MIPI_DSI_MODE_VIDEO		BIT(0)
/* video burst mode */
#घोषणा MIPI_DSI_MODE_VIDEO_BURST	BIT(1)
/* video pulse mode */
#घोषणा MIPI_DSI_MODE_VIDEO_SYNC_PULSE	BIT(2)
/* enable स्वतः vertical count mode */
#घोषणा MIPI_DSI_MODE_VIDEO_AUTO_VERT	BIT(3)
/* enable hsync-end packets in vsync-pulse and v-porch area */
#घोषणा MIPI_DSI_MODE_VIDEO_HSE		BIT(4)
/* disable hfront-porch area */
#घोषणा MIPI_DSI_MODE_VIDEO_HFP		BIT(5)
/* disable hback-porch area */
#घोषणा MIPI_DSI_MODE_VIDEO_HBP		BIT(6)
/* disable hsync-active area */
#घोषणा MIPI_DSI_MODE_VIDEO_HSA		BIT(7)
/* flush display FIFO on vsync pulse */
#घोषणा MIPI_DSI_MODE_VSYNC_FLUSH	BIT(8)
/* disable EoT packets in HS mode */
#घोषणा MIPI_DSI_MODE_EOT_PACKET	BIT(9)
/* device supports non-continuous घड़ी behavior (DSI spec 5.6.1) */
#घोषणा MIPI_DSI_CLOCK_NON_CONTINUOUS	BIT(10)
/* transmit data in low घातer */
#घोषणा MIPI_DSI_MODE_LPM		BIT(11)

क्रमागत mipi_dsi_pixel_क्रमmat अणु
	MIPI_DSI_FMT_RGB888,
	MIPI_DSI_FMT_RGB666,
	MIPI_DSI_FMT_RGB666_PACKED,
	MIPI_DSI_FMT_RGB565,
पूर्ण;

#घोषणा DSI_DEV_NAME_SIZE		20

/**
 * काष्ठा mipi_dsi_device_info - ढाँचा क्रम creating a mipi_dsi_device
 * @type: DSI peripheral chip type
 * @channel: DSI भव channel asचिन्हित to peripheral
 * @node: poपूर्णांकer to OF device node or शून्य
 *
 * This is populated and passed to mipi_dsi_device_new to create a new
 * DSI device
 */
काष्ठा mipi_dsi_device_info अणु
	अक्षर type[DSI_DEV_NAME_SIZE];
	u32 channel;
	काष्ठा device_node *node;
पूर्ण;

/**
 * काष्ठा mipi_dsi_device - DSI peripheral device
 * @host: DSI host क्रम this peripheral
 * @dev: driver model device node क्रम this peripheral
 * @name: DSI peripheral chip type
 * @channel: भव channel asचिन्हित to the peripheral
 * @क्रमmat: pixel क्रमmat क्रम video mode
 * @lanes: number of active data lanes
 * @mode_flags: DSI operation mode related flags
 * @hs_rate: maximum lane frequency क्रम high speed mode in hertz, this should
 * be set to the real limits of the hardware, zero is only accepted क्रम
 * legacy drivers
 * @lp_rate: maximum lane frequency क्रम low घातer mode in hertz, this should
 * be set to the real limits of the hardware, zero is only accepted क्रम
 * legacy drivers
 */
काष्ठा mipi_dsi_device अणु
	काष्ठा mipi_dsi_host *host;
	काष्ठा device dev;

	अक्षर name[DSI_DEV_NAME_SIZE];
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक lanes;
	क्रमागत mipi_dsi_pixel_क्रमmat क्रमmat;
	अचिन्हित दीर्घ mode_flags;
	अचिन्हित दीर्घ hs_rate;
	अचिन्हित दीर्घ lp_rate;
पूर्ण;

#घोषणा MIPI_DSI_MODULE_PREFIX "mipi-dsi:"

अटल अंतरभूत काष्ठा mipi_dsi_device *to_mipi_dsi_device(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा mipi_dsi_device, dev);
पूर्ण

/**
 * mipi_dsi_pixel_क्रमmat_to_bpp - obtain the number of bits per pixel क्रम any
 *                                given pixel क्रमmat defined by the MIPI DSI
 *                                specअगरication
 * @fmt: MIPI DSI pixel क्रमmat
 *
 * Returns: The number of bits per pixel of the given pixel क्रमmat.
 */
अटल अंतरभूत पूर्णांक mipi_dsi_pixel_क्रमmat_to_bpp(क्रमागत mipi_dsi_pixel_क्रमmat fmt)
अणु
	चयन (fmt) अणु
	हाल MIPI_DSI_FMT_RGB888:
	हाल MIPI_DSI_FMT_RGB666:
		वापस 24;

	हाल MIPI_DSI_FMT_RGB666_PACKED:
		वापस 18;

	हाल MIPI_DSI_FMT_RGB565:
		वापस 16;
	पूर्ण

	वापस -EINVAL;
पूर्ण

काष्ठा mipi_dsi_device *
mipi_dsi_device_रेजिस्टर_full(काष्ठा mipi_dsi_host *host,
			      स्थिर काष्ठा mipi_dsi_device_info *info);
व्योम mipi_dsi_device_unरेजिस्टर(काष्ठा mipi_dsi_device *dsi);
काष्ठा mipi_dsi_device *of_find_mipi_dsi_device_by_node(काष्ठा device_node *np);
पूर्णांक mipi_dsi_attach(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_detach(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_shutकरोwn_peripheral(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_turn_on_peripheral(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_set_maximum_वापस_packet_size(काष्ठा mipi_dsi_device *dsi,
					    u16 value);
sमाप_प्रकार mipi_dsi_compression_mode(काष्ठा mipi_dsi_device *dsi, bool enable);
sमाप_प्रकार mipi_dsi_picture_parameter_set(काष्ठा mipi_dsi_device *dsi,
				       स्थिर काष्ठा drm_dsc_picture_parameter_set *pps);

sमाप_प्रकार mipi_dsi_generic_ग_लिखो(काष्ठा mipi_dsi_device *dsi, स्थिर व्योम *payload,
			       माप_प्रकार size);
sमाप_प्रकार mipi_dsi_generic_पढ़ो(काष्ठा mipi_dsi_device *dsi, स्थिर व्योम *params,
			      माप_प्रकार num_params, व्योम *data, माप_प्रकार size);

/**
 * क्रमागत mipi_dsi_dcs_tear_mode - Tearing Effect Output Line mode
 * @MIPI_DSI_DCS_TEAR_MODE_VBLANK: the TE output line consists of V-Blanking
 *    inक्रमmation only
 * @MIPI_DSI_DCS_TEAR_MODE_VHBLANK : the TE output line consists of both
 *    V-Blanking and H-Blanking inक्रमmation
 */
क्रमागत mipi_dsi_dcs_tear_mode अणु
	MIPI_DSI_DCS_TEAR_MODE_VBLANK,
	MIPI_DSI_DCS_TEAR_MODE_VHBLANK,
पूर्ण;

#घोषणा MIPI_DSI_DCS_POWER_MODE_DISPLAY (1 << 2)
#घोषणा MIPI_DSI_DCS_POWER_MODE_NORMAL  (1 << 3)
#घोषणा MIPI_DSI_DCS_POWER_MODE_SLEEP   (1 << 4)
#घोषणा MIPI_DSI_DCS_POWER_MODE_PARTIAL (1 << 5)
#घोषणा MIPI_DSI_DCS_POWER_MODE_IDLE    (1 << 6)

sमाप_प्रकार mipi_dsi_dcs_ग_लिखो_buffer(काष्ठा mipi_dsi_device *dsi,
				  स्थिर व्योम *data, माप_प्रकार len);
sमाप_प्रकार mipi_dsi_dcs_ग_लिखो(काष्ठा mipi_dsi_device *dsi, u8 cmd,
			   स्थिर व्योम *data, माप_प्रकार len);
sमाप_प्रकार mipi_dsi_dcs_पढ़ो(काष्ठा mipi_dsi_device *dsi, u8 cmd, व्योम *data,
			  माप_प्रकार len);
पूर्णांक mipi_dsi_dcs_nop(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_dcs_soft_reset(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_dcs_get_घातer_mode(काष्ठा mipi_dsi_device *dsi, u8 *mode);
पूर्णांक mipi_dsi_dcs_get_pixel_क्रमmat(काष्ठा mipi_dsi_device *dsi, u8 *क्रमmat);
पूर्णांक mipi_dsi_dcs_enter_sleep_mode(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_dcs_निकास_sleep_mode(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_dcs_set_display_off(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_dcs_set_display_on(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_dcs_set_column_address(काष्ठा mipi_dsi_device *dsi, u16 start,
				    u16 end);
पूर्णांक mipi_dsi_dcs_set_page_address(काष्ठा mipi_dsi_device *dsi, u16 start,
				  u16 end);
पूर्णांक mipi_dsi_dcs_set_tear_off(काष्ठा mipi_dsi_device *dsi);
पूर्णांक mipi_dsi_dcs_set_tear_on(काष्ठा mipi_dsi_device *dsi,
			     क्रमागत mipi_dsi_dcs_tear_mode mode);
पूर्णांक mipi_dsi_dcs_set_pixel_क्रमmat(काष्ठा mipi_dsi_device *dsi, u8 क्रमmat);
पूर्णांक mipi_dsi_dcs_set_tear_scanline(काष्ठा mipi_dsi_device *dsi, u16 scanline);
पूर्णांक mipi_dsi_dcs_set_display_brightness(काष्ठा mipi_dsi_device *dsi,
					u16 brightness);
पूर्णांक mipi_dsi_dcs_get_display_brightness(काष्ठा mipi_dsi_device *dsi,
					u16 *brightness);

/**
 * काष्ठा mipi_dsi_driver - DSI driver
 * @driver: device driver model driver
 * @probe: callback क्रम device binding
 * @हटाओ: callback क्रम device unbinding
 * @shutकरोwn: called at shutकरोwn समय to quiesce the device
 */
काष्ठा mipi_dsi_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक(*probe)(काष्ठा mipi_dsi_device *dsi);
	पूर्णांक(*हटाओ)(काष्ठा mipi_dsi_device *dsi);
	व्योम (*shutकरोwn)(काष्ठा mipi_dsi_device *dsi);
पूर्ण;

अटल अंतरभूत काष्ठा mipi_dsi_driver *
to_mipi_dsi_driver(काष्ठा device_driver *driver)
अणु
	वापस container_of(driver, काष्ठा mipi_dsi_driver, driver);
पूर्ण

अटल अंतरभूत व्योम *mipi_dsi_get_drvdata(स्थिर काष्ठा mipi_dsi_device *dsi)
अणु
	वापस dev_get_drvdata(&dsi->dev);
पूर्ण

अटल अंतरभूत व्योम mipi_dsi_set_drvdata(काष्ठा mipi_dsi_device *dsi, व्योम *data)
अणु
	dev_set_drvdata(&dsi->dev, data);
पूर्ण

पूर्णांक mipi_dsi_driver_रेजिस्टर_full(काष्ठा mipi_dsi_driver *driver,
				  काष्ठा module *owner);
व्योम mipi_dsi_driver_unरेजिस्टर(काष्ठा mipi_dsi_driver *driver);

#घोषणा mipi_dsi_driver_रेजिस्टर(driver) \
	mipi_dsi_driver_रेजिस्टर_full(driver, THIS_MODULE)

#घोषणा module_mipi_dsi_driver(__mipi_dsi_driver) \
	module_driver(__mipi_dsi_driver, mipi_dsi_driver_रेजिस्टर, \
			mipi_dsi_driver_unरेजिस्टर)

#पूर्ण_अगर /* __DRM_MIPI_DSI__ */
