<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * FPGA Framework
 *
 *  Copyright (C) 2013-2016 Altera Corporation
 *  Copyright (C) 2017 Intel Corporation
 */
#अगर_अघोषित _LINUX_FPGA_MGR_H
#घोषणा _LINUX_FPGA_MGR_H

#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा fpga_manager;
काष्ठा sg_table;

/**
 * क्रमागत fpga_mgr_states - fpga framework states
 * @FPGA_MGR_STATE_UNKNOWN: can't determine state
 * @FPGA_MGR_STATE_POWER_OFF: FPGA घातer is off
 * @FPGA_MGR_STATE_POWER_UP: FPGA reports घातer is up
 * @FPGA_MGR_STATE_RESET: FPGA in reset state
 * @FPGA_MGR_STATE_FIRMWARE_REQ: firmware request in progress
 * @FPGA_MGR_STATE_FIRMWARE_REQ_ERR: firmware request failed
 * @FPGA_MGR_STATE_WRITE_INIT: preparing FPGA क्रम programming
 * @FPGA_MGR_STATE_WRITE_INIT_ERR: Error during WRITE_INIT stage
 * @FPGA_MGR_STATE_WRITE: writing image to FPGA
 * @FPGA_MGR_STATE_WRITE_ERR: Error जबतक writing FPGA
 * @FPGA_MGR_STATE_WRITE_COMPLETE: Doing post programming steps
 * @FPGA_MGR_STATE_WRITE_COMPLETE_ERR: Error during WRITE_COMPLETE
 * @FPGA_MGR_STATE_OPERATING: FPGA is programmed and operating
 */
क्रमागत fpga_mgr_states अणु
	/* शेष FPGA states */
	FPGA_MGR_STATE_UNKNOWN,
	FPGA_MGR_STATE_POWER_OFF,
	FPGA_MGR_STATE_POWER_UP,
	FPGA_MGR_STATE_RESET,

	/* getting an image क्रम loading */
	FPGA_MGR_STATE_FIRMWARE_REQ,
	FPGA_MGR_STATE_FIRMWARE_REQ_ERR,

	/* ग_लिखो sequence: init, ग_लिखो, complete */
	FPGA_MGR_STATE_WRITE_INIT,
	FPGA_MGR_STATE_WRITE_INIT_ERR,
	FPGA_MGR_STATE_WRITE,
	FPGA_MGR_STATE_WRITE_ERR,
	FPGA_MGR_STATE_WRITE_COMPLETE,
	FPGA_MGR_STATE_WRITE_COMPLETE_ERR,

	/* fpga is programmed and operating */
	FPGA_MGR_STATE_OPERATING,
पूर्ण;

/**
 * DOC: FPGA Manager flags
 *
 * Flags used in the &fpga_image_info->flags field
 *
 * %FPGA_MGR_PARTIAL_RECONFIG: करो partial reconfiguration अगर supported
 *
 * %FPGA_MGR_EXTERNAL_CONFIG: FPGA has been configured prior to Linux booting
 *
 * %FPGA_MGR_ENCRYPTED_BITSTREAM: indicates bitstream is encrypted
 *
 * %FPGA_MGR_BITSTREAM_LSB_FIRST: SPI bitstream bit order is LSB first
 *
 * %FPGA_MGR_COMPRESSED_BITSTREAM: FPGA bitstream is compressed
 */
#घोषणा FPGA_MGR_PARTIAL_RECONFIG	BIT(0)
#घोषणा FPGA_MGR_EXTERNAL_CONFIG	BIT(1)
#घोषणा FPGA_MGR_ENCRYPTED_BITSTREAM	BIT(2)
#घोषणा FPGA_MGR_BITSTREAM_LSB_FIRST	BIT(3)
#घोषणा FPGA_MGR_COMPRESSED_BITSTREAM	BIT(4)

/**
 * काष्ठा fpga_image_info - inक्रमmation specअगरic to a FPGA image
 * @flags: boolean flags as defined above
 * @enable_समयout_us: maximum समय to enable traffic through bridge (uSec)
 * @disable_समयout_us: maximum समय to disable traffic through bridge (uSec)
 * @config_complete_समयout_us: maximum समय क्रम FPGA to चयन to operating
 *	   status in the ग_लिखो_complete op.
 * @firmware_name: name of FPGA image firmware file
 * @sgt: scatter/gather table containing FPGA image
 * @buf: contiguous buffer containing FPGA image
 * @count: size of buf
 * @region_id: id of target region
 * @dev: device that owns this
 * @overlay: Device Tree overlay
 */
काष्ठा fpga_image_info अणु
	u32 flags;
	u32 enable_समयout_us;
	u32 disable_समयout_us;
	u32 config_complete_समयout_us;
	अक्षर *firmware_name;
	काष्ठा sg_table *sgt;
	स्थिर अक्षर *buf;
	माप_प्रकार count;
	पूर्णांक region_id;
	काष्ठा device *dev;
#अगर_घोषित CONFIG_OF
	काष्ठा device_node *overlay;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा fpga_manager_ops - ops क्रम low level fpga manager drivers
 * @initial_header_size: Maximum number of bytes that should be passed पूर्णांकo ग_लिखो_init
 * @state: वापसs an क्रमागत value of the FPGA's state
 * @status: वापसs status of the FPGA, including reconfiguration error code
 * @ग_लिखो_init: prepare the FPGA to receive confuration data
 * @ग_लिखो: ग_लिखो count bytes of configuration data to the FPGA
 * @ग_लिखो_sg: ग_लिखो the scatter list of configuration data to the FPGA
 * @ग_लिखो_complete: set FPGA to operating state after writing is करोne
 * @fpga_हटाओ: optional: Set FPGA पूर्णांकo a specअगरic state during driver हटाओ
 * @groups: optional attribute groups.
 *
 * fpga_manager_ops are the low level functions implemented by a specअगरic
 * fpga manager driver.  The optional ones are tested क्रम शून्य beक्रमe being
 * called, so leaving them out is fine.
 */
काष्ठा fpga_manager_ops अणु
	माप_प्रकार initial_header_size;
	क्रमागत fpga_mgr_states (*state)(काष्ठा fpga_manager *mgr);
	u64 (*status)(काष्ठा fpga_manager *mgr);
	पूर्णांक (*ग_लिखो_init)(काष्ठा fpga_manager *mgr,
			  काष्ठा fpga_image_info *info,
			  स्थिर अक्षर *buf, माप_प्रकार count);
	पूर्णांक (*ग_लिखो)(काष्ठा fpga_manager *mgr, स्थिर अक्षर *buf, माप_प्रकार count);
	पूर्णांक (*ग_लिखो_sg)(काष्ठा fpga_manager *mgr, काष्ठा sg_table *sgt);
	पूर्णांक (*ग_लिखो_complete)(काष्ठा fpga_manager *mgr,
			      काष्ठा fpga_image_info *info);
	व्योम (*fpga_हटाओ)(काष्ठा fpga_manager *mgr);
	स्थिर काष्ठा attribute_group **groups;
पूर्ण;

/* FPGA manager status: Partial/Full Reconfiguration errors */
#घोषणा FPGA_MGR_STATUS_OPERATION_ERR		BIT(0)
#घोषणा FPGA_MGR_STATUS_CRC_ERR			BIT(1)
#घोषणा FPGA_MGR_STATUS_INCOMPATIBLE_IMAGE_ERR	BIT(2)
#घोषणा FPGA_MGR_STATUS_IP_PROTOCOL_ERR		BIT(3)
#घोषणा FPGA_MGR_STATUS_FIFO_OVERFLOW_ERR	BIT(4)

/**
 * काष्ठा fpga_compat_id - id क्रम compatibility check
 *
 * @id_h: high 64bit of the compat_id
 * @id_l: low 64bit of the compat_id
 */
काष्ठा fpga_compat_id अणु
	u64 id_h;
	u64 id_l;
पूर्ण;

/**
 * काष्ठा fpga_manager - fpga manager काष्ठाure
 * @name: name of low level fpga manager
 * @dev: fpga manager device
 * @ref_mutex: only allows one reference to fpga manager
 * @state: state of fpga manager
 * @compat_id: FPGA manager id क्रम compatibility check.
 * @mops: poपूर्णांकer to काष्ठा of fpga manager ops
 * @priv: low level driver निजी date
 */
काष्ठा fpga_manager अणु
	स्थिर अक्षर *name;
	काष्ठा device dev;
	काष्ठा mutex ref_mutex;
	क्रमागत fpga_mgr_states state;
	काष्ठा fpga_compat_id *compat_id;
	स्थिर काष्ठा fpga_manager_ops *mops;
	व्योम *priv;
पूर्ण;

#घोषणा to_fpga_manager(d) container_of(d, काष्ठा fpga_manager, dev)

काष्ठा fpga_image_info *fpga_image_info_alloc(काष्ठा device *dev);

व्योम fpga_image_info_मुक्त(काष्ठा fpga_image_info *info);

पूर्णांक fpga_mgr_load(काष्ठा fpga_manager *mgr, काष्ठा fpga_image_info *info);

पूर्णांक fpga_mgr_lock(काष्ठा fpga_manager *mgr);
व्योम fpga_mgr_unlock(काष्ठा fpga_manager *mgr);

काष्ठा fpga_manager *of_fpga_mgr_get(काष्ठा device_node *node);

काष्ठा fpga_manager *fpga_mgr_get(काष्ठा device *dev);

व्योम fpga_mgr_put(काष्ठा fpga_manager *mgr);

काष्ठा fpga_manager *fpga_mgr_create(काष्ठा device *dev, स्थिर अक्षर *name,
				     स्थिर काष्ठा fpga_manager_ops *mops,
				     व्योम *priv);
व्योम fpga_mgr_मुक्त(काष्ठा fpga_manager *mgr);
पूर्णांक fpga_mgr_रेजिस्टर(काष्ठा fpga_manager *mgr);
व्योम fpga_mgr_unरेजिस्टर(काष्ठा fpga_manager *mgr);

पूर्णांक devm_fpga_mgr_रेजिस्टर(काष्ठा device *dev, काष्ठा fpga_manager *mgr);

काष्ठा fpga_manager *devm_fpga_mgr_create(काष्ठा device *dev, स्थिर अक्षर *name,
					  स्थिर काष्ठा fpga_manager_ops *mops,
					  व्योम *priv);

#पूर्ण_अगर /*_LINUX_FPGA_MGR_H */
