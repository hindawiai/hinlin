<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HD-audio bus
 */
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/export.h>
#समावेश <sound/hdaudपन.स>

MODULE_DESCRIPTION("HD-audio bus");
MODULE_LICENSE("GPL");

/**
 * hdac_get_device_id - माला_लो the hdac device id entry
 * @hdev: HD-audio core device
 * @drv: HD-audio codec driver
 *
 * Compares the hdac device venकरोr_id and revision_id to the hdac_device
 * driver id_table and वापसs the matching device id entry.
 */
स्थिर काष्ठा hda_device_id *
hdac_get_device_id(काष्ठा hdac_device *hdev, काष्ठा hdac_driver *drv)
अणु
	अगर (drv->id_table) अणु
		स्थिर काष्ठा hda_device_id *id  = drv->id_table;

		जबतक (id->venकरोr_id) अणु
			अगर (hdev->venकरोr_id == id->venकरोr_id &&
				(!id->rev_id || id->rev_id == hdev->revision_id))
				वापस id;
			id++;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(hdac_get_device_id);

अटल पूर्णांक hdac_codec_match(काष्ठा hdac_device *dev, काष्ठा hdac_driver *drv)
अणु
	अगर (hdac_get_device_id(dev, drv))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक hda_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा hdac_device *hdev = dev_to_hdac_dev(dev);
	काष्ठा hdac_driver *hdrv = drv_to_hdac_driver(drv);

	अगर (hdev->type != hdrv->type)
		वापस 0;

	/*
	 * अगर driver provided a match function use that otherwise we will
	 * use hdac_codec_match function
	 */
	अगर (hdrv->match)
		वापस hdrv->match(hdev, hdrv);
	अन्यथा
		वापस hdac_codec_match(hdev, hdrv);
	वापस 1;
पूर्ण

अटल पूर्णांक hda_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	अक्षर modalias[32];

	snd_hdac_codec_modalias(dev_to_hdac_dev(dev), modalias,
				माप(modalias));
	अगर (add_uevent_var(env, "MODALIAS=%s", modalias))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

काष्ठा bus_type snd_hda_bus_type = अणु
	.name = "hdaudio",
	.match = hda_bus_match,
	.uevent = hda_uevent,
पूर्ण;
EXPORT_SYMBOL_GPL(snd_hda_bus_type);

अटल पूर्णांक __init hda_bus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&snd_hda_bus_type);
पूर्ण

अटल व्योम __निकास hda_bus_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&snd_hda_bus_type);
पूर्ण

subsys_initcall(hda_bus_init);
module_निकास(hda_bus_निकास);
