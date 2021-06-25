<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 *  Copyright (C) 2016 Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 */

#अगर_अघोषित __SOUND_AC97_CODEC2_H
#घोषणा __SOUND_AC97_CODEC2_H

#समावेश <linux/device.h>

#घोषणा AC97_ID(venकरोr_id1, venकरोr_id2) \
	((((venकरोr_id1) & 0xffff) << 16) | ((venकरोr_id2) & 0xffff))
#घोषणा AC97_DRIVER_ID(venकरोr_id1, venकरोr_id2, mask_id1, mask_id2, _data) \
	अणु .id = (((venकरोr_id1) & 0xffff) << 16) | ((venकरोr_id2) & 0xffff), \
	  .mask = (((mask_id1) & 0xffff) << 16) | ((mask_id2) & 0xffff), \
	  .data = (_data) पूर्ण

काष्ठा ac97_controller;
काष्ठा clk;

/**
 * काष्ठा ac97_id - matches a codec device and driver on an ac97 bus
 * @id: The signअगरicant bits अगर the codec venकरोr ID1 and ID2
 * @mask: Biपंचांगask specअगरying which bits of the id field are signअगरicant when
 *	  matching. A driver binds to a device when :
 *        ((venकरोrID1 << 8 | venकरोrID2) & (mask_id1 << 8 | mask_id2)) == id.
 * @data: Private data used by the driver.
 */
काष्ठा ac97_id अणु
	अचिन्हित पूर्णांक		id;
	अचिन्हित पूर्णांक		mask;
	व्योम			*data;
पूर्ण;

/**
 * ac97_codec_device - a ac97 codec
 * @dev: the core device
 * @venकरोr_id: the venकरोr_id of the codec, as sensed on the AC-link
 * @num: the codec number, 0 is primary, 1 is first slave, etc ...
 * @clk: the घड़ी BIT_CLK provided by the codec
 * @ac97_ctrl: ac97 digital controller on the same AC-link
 *
 * This is the device instantiated क्रम each codec living on a AC-link. There are
 * normally 0 to 4 codec devices per AC-link, and all of them are controlled by
 * an AC97 digital controller.
 */
काष्ठा ac97_codec_device अणु
	काष्ठा device		dev;
	अचिन्हित पूर्णांक		venकरोr_id;
	अचिन्हित पूर्णांक		num;
	काष्ठा clk		*clk;
	काष्ठा ac97_controller	*ac97_ctrl;
पूर्ण;

/**
 * ac97_codec_driver - a ac97 codec driver
 * @driver: the device driver काष्ठाure
 * @probe: the function called when a ac97_codec_device is matched
 * @हटाओ: the function called when the device is unbound/हटाओd
 * @shutकरोwn: shutकरोwn function (might be शून्य)
 * @id_table: ac97 venकरोr_id match table, अणु पूर्ण member terminated
 */
काष्ठा ac97_codec_driver अणु
	काष्ठा device_driver	driver;
	पूर्णांक			(*probe)(काष्ठा ac97_codec_device *);
	पूर्णांक			(*हटाओ)(काष्ठा ac97_codec_device *);
	व्योम			(*shutकरोwn)(काष्ठा ac97_codec_device *);
	स्थिर काष्ठा ac97_id	*id_table;
पूर्ण;

अटल अंतरभूत काष्ठा ac97_codec_device *to_ac97_device(काष्ठा device *d)
अणु
	वापस container_of(d, काष्ठा ac97_codec_device, dev);
पूर्ण

अटल अंतरभूत काष्ठा ac97_codec_driver *to_ac97_driver(काष्ठा device_driver *d)
अणु
	वापस container_of(d, काष्ठा ac97_codec_driver, driver);
पूर्ण

#अगर IS_ENABLED(CONFIG_AC97_BUS_NEW)
पूर्णांक snd_ac97_codec_driver_रेजिस्टर(काष्ठा ac97_codec_driver *drv);
व्योम snd_ac97_codec_driver_unरेजिस्टर(काष्ठा ac97_codec_driver *drv);
#अन्यथा
अटल अंतरभूत पूर्णांक
snd_ac97_codec_driver_रेजिस्टर(काष्ठा ac97_codec_driver *drv)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम
snd_ac97_codec_driver_unरेजिस्टर(काष्ठा ac97_codec_driver *drv)
अणु
पूर्ण
#पूर्ण_अगर


अटल अंतरभूत काष्ठा device *
ac97_codec_dev2dev(काष्ठा ac97_codec_device *adev)
अणु
	वापस &adev->dev;
पूर्ण

अटल अंतरभूत व्योम *ac97_get_drvdata(काष्ठा ac97_codec_device *adev)
अणु
	वापस dev_get_drvdata(ac97_codec_dev2dev(adev));
पूर्ण

अटल अंतरभूत व्योम ac97_set_drvdata(काष्ठा ac97_codec_device *adev,
				    व्योम *data)
अणु
	dev_set_drvdata(ac97_codec_dev2dev(adev), data);
पूर्ण

व्योम *snd_ac97_codec_get_platdata(स्थिर काष्ठा ac97_codec_device *adev);

#पूर्ण_अगर
