<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __USB_TYPEC_ALTMODE_H
#घोषणा __USB_TYPEC_ALTMODE_H

#समावेश <linux/mod_devicetable.h>
#समावेश <linux/usb/typec.h>
#समावेश <linux/device.h>

#घोषणा MODE_DISCOVERY_MAX	6

काष्ठा typec_alपंचांगode_ops;

/**
 * काष्ठा typec_alपंचांगode - USB Type-C alternate mode device
 * @dev: Driver model's view of this device
 * @svid: Standard or Venकरोr ID (SVID) of the alternate mode
 * @mode: Index of the Mode
 * @vकरो: VDO वापसed by Discover Modes USB PD command
 * @active: Tells has the mode been entered or not
 * @desc: Optional human पढ़ोable description of the mode
 * @ops: Operations vector from the driver
 */
काष्ठा typec_alपंचांगode अणु
	काष्ठा device			dev;
	u16				svid;
	पूर्णांक				mode;
	u32				vकरो;
	अचिन्हित पूर्णांक			active:1;

	अक्षर				*desc;
	स्थिर काष्ठा typec_alपंचांगode_ops	*ops;
पूर्ण;

#घोषणा to_typec_alपंचांगode(d) container_of(d, काष्ठा typec_alपंचांगode, dev)

अटल अंतरभूत व्योम typec_alपंचांगode_set_drvdata(काष्ठा typec_alपंचांगode *alपंचांगode,
					     व्योम *data)
अणु
	dev_set_drvdata(&alपंचांगode->dev, data);
पूर्ण

अटल अंतरभूत व्योम *typec_alपंचांगode_get_drvdata(काष्ठा typec_alपंचांगode *alपंचांगode)
अणु
	वापस dev_get_drvdata(&alपंचांगode->dev);
पूर्ण

/**
 * काष्ठा typec_alपंचांगode_ops - Alternate mode specअगरic operations vector
 * @enter: Operations to be executed with Enter Mode Command
 * @निकास: Operations to be executed with Exit Mode Command
 * @attention: Callback क्रम Attention Command
 * @vdm: Callback क्रम SVID specअगरic commands
 * @notअगरy: Communication channel क्रम platक्रमm and the alternate mode
 * @activate: User callback क्रम Enter/Exit Mode
 */
काष्ठा typec_alपंचांगode_ops अणु
	पूर्णांक (*enter)(काष्ठा typec_alपंचांगode *alपंचांगode, u32 *vकरो);
	पूर्णांक (*निकास)(काष्ठा typec_alपंचांगode *alपंचांगode);
	व्योम (*attention)(काष्ठा typec_alपंचांगode *alपंचांगode, u32 vकरो);
	पूर्णांक (*vdm)(काष्ठा typec_alपंचांगode *alपंचांगode, स्थिर u32 hdr,
		   स्थिर u32 *vकरो, पूर्णांक cnt);
	पूर्णांक (*notअगरy)(काष्ठा typec_alपंचांगode *alपंचांगode, अचिन्हित दीर्घ conf,
		      व्योम *data);
	पूर्णांक (*activate)(काष्ठा typec_alपंचांगode *alपंचांगode, पूर्णांक activate);
पूर्ण;

पूर्णांक typec_alपंचांगode_enter(काष्ठा typec_alपंचांगode *alपंचांगode, u32 *vकरो);
पूर्णांक typec_alपंचांगode_निकास(काष्ठा typec_alपंचांगode *alपंचांगode);
व्योम typec_alपंचांगode_attention(काष्ठा typec_alपंचांगode *alपंचांगode, u32 vकरो);
पूर्णांक typec_alपंचांगode_vdm(काष्ठा typec_alपंचांगode *alपंचांगode,
		      स्थिर u32 header, स्थिर u32 *vकरो, पूर्णांक count);
पूर्णांक typec_alपंचांगode_notअगरy(काष्ठा typec_alपंचांगode *alपंचांगode, अचिन्हित दीर्घ conf,
			 व्योम *data);
स्थिर काष्ठा typec_alपंचांगode *
typec_alपंचांगode_get_partner(काष्ठा typec_alपंचांगode *alपंचांगode);

/*
 * These are the connector states (USB, Safe and Alt Mode) defined in USB Type-C
 * Specअगरication. SVID specअगरic connector states are expected to follow and
 * start from the value TYPEC_STATE_MODAL.
 */
क्रमागत अणु
	TYPEC_STATE_SAFE,	/* USB Safe State */
	TYPEC_STATE_USB,	/* USB Operation */
	TYPEC_STATE_MODAL,	/* Alternate Modes */
पूर्ण;

/*
 * For the muxes there is no dअगरference between Accessory Modes and Alternate
 * Modes, so the Accessory Modes are supplied with specअगरic modal state values
 * here. Unlike with Alternate Modes, where the mux will be linked with the
 * alternate mode device, the mux क्रम Accessory Modes will be linked with the
 * port device instead.
 *
 * Port drivers can use TYPEC_MODE_AUDIO and TYPEC_MODE_DEBUG as the mode
 * value क्रम typec_set_mode() when accessory modes are supported.
 *
 * USB4 also requires that the pins on the connector are repurposed, just like
 * Alternate Modes. USB4 mode is however not entered with the Enter Mode Command
 * like the Alternate Modes are, but instead with a special Enter_USB Message.
 * The Enter_USB Message can also be used क्रम setting to connector to operate in
 * USB 3.2 or in USB 2.0 mode instead of USB4.
 *
 * The Enter_USB specअगरic "USB Modes" are also supplied here as special modal
 * state values, just like the Accessory Modes.
 */
क्रमागत अणु
	TYPEC_MODE_USB2 = TYPEC_STATE_MODAL,	/* USB 2.0 mode */
	TYPEC_MODE_USB3,			/* USB 3.2 mode */
	TYPEC_MODE_USB4,			/* USB4 mode */
	TYPEC_MODE_AUDIO,			/* Audio Accessory */
	TYPEC_MODE_DEBUG,			/* Debug Accessory */
पूर्ण;

#घोषणा TYPEC_MODAL_STATE(_state_)	((_state_) + TYPEC_STATE_MODAL)

काष्ठा typec_alपंचांगode *typec_alपंचांगode_get_plug(काष्ठा typec_alपंचांगode *alपंचांगode,
					     क्रमागत typec_plug_index index);
व्योम typec_alपंचांगode_put_plug(काष्ठा typec_alपंचांगode *plug);

काष्ठा typec_alपंचांगode *typec_match_alपंचांगode(काष्ठा typec_alपंचांगode **alपंचांगodes,
					  माप_प्रकार n, u16 svid, u8 mode);

/**
 * typec_alपंचांगode_get_orientation - Get cable plug orientation
 * alपंचांगode: Handle to the alternate mode
 */
अटल अंतरभूत क्रमागत typec_orientation
typec_alपंचांगode_get_orientation(काष्ठा typec_alपंचांगode *alपंचांगode)
अणु
	वापस typec_get_orientation(typec_alपंचांगode2port(alपंचांगode));
पूर्ण

/**
 * typec_alपंचांगode_get_svdm_version - Get negotiated SVDM version
 * @alपंचांगode: Handle to the alternate mode
 */
अटल अंतरभूत पूर्णांक
typec_alपंचांगode_get_svdm_version(काष्ठा typec_alपंचांगode *alपंचांगode)
अणु
	वापस typec_get_negotiated_svdm_version(typec_alपंचांगode2port(alपंचांगode));
पूर्ण

/**
 * काष्ठा typec_alपंचांगode_driver - USB Type-C alternate mode device driver
 * @id_table: Null terminated array of SVIDs
 * @probe: Callback क्रम device binding
 * @हटाओ: Callback क्रम device unbinding
 * @driver: Device driver model driver
 *
 * These drivers will be bind to the partner alternate mode devices. They will
 * handle all SVID specअगरic communication.
 */
काष्ठा typec_alपंचांगode_driver अणु
	स्थिर काष्ठा typec_device_id *id_table;
	पूर्णांक (*probe)(काष्ठा typec_alपंचांगode *alपंचांगode);
	व्योम (*हटाओ)(काष्ठा typec_alपंचांगode *alपंचांगode);
	काष्ठा device_driver driver;
पूर्ण;

#घोषणा to_alपंचांगode_driver(d) container_of(d, काष्ठा typec_alपंचांगode_driver, \
					  driver)

/**
 * typec_alपंचांगode_रेजिस्टर_driver - रेजिस्टरs a USB Type-C alternate mode
 * 				   device driver
 * @drv: poपूर्णांकer to काष्ठा typec_alपंचांगode_driver
 *
 * These drivers will be bind to the partner alternate mode devices. They will
 * handle all SVID specअगरic communication.
 */
#घोषणा typec_alपंचांगode_रेजिस्टर_driver(drv) \
		__typec_alपंचांगode_रेजिस्टर_driver(drv, THIS_MODULE)
पूर्णांक __typec_alपंचांगode_रेजिस्टर_driver(काष्ठा typec_alपंचांगode_driver *drv,
				    काष्ठा module *module);
/**
 * typec_alपंचांगode_unरेजिस्टर_driver - unरेजिस्टरs a USB Type-C alternate mode
 * 				     device driver
 * @drv: poपूर्णांकer to काष्ठा typec_alपंचांगode_driver
 *
 * These drivers will be bind to the partner alternate mode devices. They will
 * handle all SVID specअगरic communication.
 */
व्योम typec_alपंचांगode_unरेजिस्टर_driver(काष्ठा typec_alपंचांगode_driver *drv);

#घोषणा module_typec_alपंचांगode_driver(__typec_alपंचांगode_driver) \
	module_driver(__typec_alपंचांगode_driver, typec_alपंचांगode_रेजिस्टर_driver, \
		      typec_alपंचांगode_unरेजिस्टर_driver)

#पूर्ण_अगर /* __USB_TYPEC_ALTMODE_H */
