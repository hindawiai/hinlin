<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  hdac-ext-controller.c - HD-audio extended controller functions.
 *
 *  Copyright (C) 2014-2015 Intel Corp
 *  Author: Jeeja KP <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <sound/hda_रेजिस्टर.h>
#समावेश <sound/hdaudio_ext.h>

/*
 * maximum HDAC capablities we should parse to aव्योम endless looping:
 * currently we have 4 extended caps, so this is future proof क्रम now.
 * extend when this limit is seen meeting in real HW
 */
#घोषणा HDAC_MAX_CAPS 10

/*
 * processing pipe helpers - these helpers are useful क्रम dealing with HDA
 * new capability of processing pipelines
 */

/**
 * snd_hdac_ext_bus_ppcap_enable - enable/disable processing pipe capability
 * @bus: the poपूर्णांकer to HDAC bus object
 * @enable: flag to turn on/off the capability
 */
व्योम snd_hdac_ext_bus_ppcap_enable(काष्ठा hdac_bus *bus, bool enable)
अणु

	अगर (!bus->ppcap) अणु
		dev_err(bus->dev, "Address of PP capability is NULL");
		वापस;
	पूर्ण

	अगर (enable)
		snd_hdac_updatel(bus->ppcap, AZX_REG_PP_PPCTL,
				 AZX_PPCTL_GPROCEN, AZX_PPCTL_GPROCEN);
	अन्यथा
		snd_hdac_updatel(bus->ppcap, AZX_REG_PP_PPCTL,
				 AZX_PPCTL_GPROCEN, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_ppcap_enable);

/**
 * snd_hdac_ext_bus_ppcap_पूर्णांक_enable - ppcap पूर्णांकerrupt enable/disable
 * @bus: the poपूर्णांकer to HDAC bus object
 * @enable: flag to enable/disable पूर्णांकerrupt
 */
व्योम snd_hdac_ext_bus_ppcap_पूर्णांक_enable(काष्ठा hdac_bus *bus, bool enable)
अणु

	अगर (!bus->ppcap) अणु
		dev_err(bus->dev, "Address of PP capability is NULL\n");
		वापस;
	पूर्ण

	अगर (enable)
		snd_hdac_updatel(bus->ppcap, AZX_REG_PP_PPCTL,
				 AZX_PPCTL_PIE, AZX_PPCTL_PIE);
	अन्यथा
		snd_hdac_updatel(bus->ppcap, AZX_REG_PP_PPCTL,
				 AZX_PPCTL_PIE, 0);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_ppcap_पूर्णांक_enable);

/*
 * Multilink helpers - these helpers are useful क्रम dealing with HDA
 * new multilink capability
 */

/**
 * snd_hdac_ext_bus_get_ml_capabilities - get multilink capability
 * @bus: the poपूर्णांकer to HDAC bus object
 *
 * This will parse all links and पढ़ो the mlink capabilities and add them
 * in hlink_list of extended hdac bus
 * Note: this will be मुक्तd on bus निकास by driver
 */
पूर्णांक snd_hdac_ext_bus_get_ml_capabilities(काष्ठा hdac_bus *bus)
अणु
	पूर्णांक idx;
	u32 link_count;
	काष्ठा hdac_ext_link *hlink;

	link_count = पढ़ोl(bus->mlcap + AZX_REG_ML_MLCD) + 1;

	dev_dbg(bus->dev, "In %s Link count: %d\n", __func__, link_count);

	क्रम (idx = 0; idx < link_count; idx++) अणु
		hlink  = kzalloc(माप(*hlink), GFP_KERNEL);
		अगर (!hlink)
			वापस -ENOMEM;
		hlink->index = idx;
		hlink->bus = bus;
		hlink->ml_addr = bus->mlcap + AZX_ML_BASE +
					(AZX_ML_INTERVAL * idx);
		hlink->lcaps  = पढ़ोl(hlink->ml_addr + AZX_REG_ML_LCAP);
		hlink->lsdiid = पढ़ोw(hlink->ml_addr + AZX_REG_ML_LSDIID);

		/* since link in On, update the ref */
		hlink->ref_count = 1;

		list_add_tail(&hlink->list, &bus->hlink_list);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_get_ml_capabilities);

/**
 * snd_hdac_link_मुक्त_all- मुक्त hdac extended link objects
 *
 * @bus: the poपूर्णांकer to HDAC bus object
 */

व्योम snd_hdac_link_मुक्त_all(काष्ठा hdac_bus *bus)
अणु
	काष्ठा hdac_ext_link *l;

	जबतक (!list_empty(&bus->hlink_list)) अणु
		l = list_first_entry(&bus->hlink_list, काष्ठा hdac_ext_link, list);
		list_del(&l->list);
		kमुक्त(l);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_link_मुक्त_all);

/**
 * snd_hdac_ext_bus_get_link - get link based on codec name
 * @bus: the poपूर्णांकer to HDAC bus object
 * @codec_name: codec name
 */
काष्ठा hdac_ext_link *snd_hdac_ext_bus_get_link(काष्ठा hdac_bus *bus,
						 स्थिर अक्षर *codec_name)
अणु
	पूर्णांक i;
	काष्ठा hdac_ext_link *hlink = शून्य;
	पूर्णांक bus_idx, addr;

	अगर (माला_पूछो(codec_name, "ehdaudio%dD%d", &bus_idx, &addr) != 2)
		वापस शून्य;
	अगर (bus->idx != bus_idx)
		वापस शून्य;
	अगर (addr < 0 || addr > 31)
		वापस शून्य;

	list_क्रम_each_entry(hlink, &bus->hlink_list, list) अणु
		क्रम (i = 0; i < HDA_MAX_CODECS; i++) अणु
			अगर (hlink->lsdiid & (0x1 << addr))
				वापस hlink;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_get_link);

अटल पूर्णांक check_hdac_link_घातer_active(काष्ठा hdac_ext_link *link, bool enable)
अणु
	पूर्णांक समयout;
	u32 val;
	पूर्णांक mask = (1 << AZX_MLCTL_CPA_SHIFT);

	udelay(3);
	समयout = 150;

	करो अणु
		val = पढ़ोl(link->ml_addr + AZX_REG_ML_LCTL);
		अगर (enable) अणु
			अगर (((val & mask) >> AZX_MLCTL_CPA_SHIFT))
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (!((val & mask) >> AZX_MLCTL_CPA_SHIFT))
				वापस 0;
		पूर्ण
		udelay(3);
	पूर्ण जबतक (--समयout);

	वापस -EIO;
पूर्ण

/**
 * snd_hdac_ext_bus_link_घातer_up -घातer up hda link
 * @link: HD-audio extended link
 */
पूर्णांक snd_hdac_ext_bus_link_घातer_up(काष्ठा hdac_ext_link *link)
अणु
	snd_hdac_updatel(link->ml_addr, AZX_REG_ML_LCTL,
			 AZX_MLCTL_SPA, AZX_MLCTL_SPA);

	वापस check_hdac_link_घातer_active(link, true);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_link_घातer_up);

/**
 * snd_hdac_ext_bus_link_घातer_करोwn -घातer करोwn hda link
 * @link: HD-audio extended link
 */
पूर्णांक snd_hdac_ext_bus_link_घातer_करोwn(काष्ठा hdac_ext_link *link)
अणु
	snd_hdac_updatel(link->ml_addr, AZX_REG_ML_LCTL, AZX_MLCTL_SPA, 0);

	वापस check_hdac_link_घातer_active(link, false);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_link_घातer_करोwn);

/**
 * snd_hdac_ext_bus_link_घातer_up_all -घातer up all hda link
 * @bus: the poपूर्णांकer to HDAC bus object
 */
पूर्णांक snd_hdac_ext_bus_link_घातer_up_all(काष्ठा hdac_bus *bus)
अणु
	काष्ठा hdac_ext_link *hlink = शून्य;
	पूर्णांक ret;

	list_क्रम_each_entry(hlink, &bus->hlink_list, list) अणु
		snd_hdac_updatel(hlink->ml_addr, AZX_REG_ML_LCTL,
				 AZX_MLCTL_SPA, AZX_MLCTL_SPA);
		ret = check_hdac_link_घातer_active(hlink, true);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_link_घातer_up_all);

/**
 * snd_hdac_ext_bus_link_घातer_करोwn_all -घातer करोwn all hda link
 * @bus: the poपूर्णांकer to HDAC bus object
 */
पूर्णांक snd_hdac_ext_bus_link_घातer_करोwn_all(काष्ठा hdac_bus *bus)
अणु
	काष्ठा hdac_ext_link *hlink = शून्य;
	पूर्णांक ret;

	list_क्रम_each_entry(hlink, &bus->hlink_list, list) अणु
		snd_hdac_updatel(hlink->ml_addr, AZX_REG_ML_LCTL,
				 AZX_MLCTL_SPA, 0);
		ret = check_hdac_link_घातer_active(hlink, false);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_link_घातer_करोwn_all);

पूर्णांक snd_hdac_ext_bus_link_get(काष्ठा hdac_bus *bus,
				काष्ठा hdac_ext_link *link)
अणु
	अचिन्हित दीर्घ codec_mask;
	पूर्णांक ret = 0;

	mutex_lock(&bus->lock);

	/*
	 * अगर we move from 0 to 1, count will be 1 so घातer up this link
	 * as well, also check the dma status and trigger that
	 */
	अगर (++link->ref_count == 1) अणु
		अगर (!bus->cmd_dma_state) अणु
			snd_hdac_bus_init_cmd_io(bus);
			bus->cmd_dma_state = true;
		पूर्ण

		ret = snd_hdac_ext_bus_link_घातer_up(link);

		/*
		 * clear the रेजिस्टर to invalidate all the output streams
		 */
		snd_hdac_updatew(link->ml_addr, AZX_REG_ML_LOSIDV,
				 ML_LOSIDV_STREAM_MASK, 0);
		/*
		 *  रुको क्रम 521usec क्रम codec to report status
		 *  HDA spec section 4.3 - Codec Discovery
		 */
		udelay(521);
		codec_mask = snd_hdac_chip_पढ़ोw(bus, STATESTS);
		dev_dbg(bus->dev, "codec_mask = 0x%lx\n", codec_mask);
		snd_hdac_chip_ग_लिखोw(bus, STATESTS, codec_mask);
		अगर (!bus->codec_mask)
			bus->codec_mask = codec_mask;
	पूर्ण

	mutex_unlock(&bus->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_link_get);

पूर्णांक snd_hdac_ext_bus_link_put(काष्ठा hdac_bus *bus,
				काष्ठा hdac_ext_link *link)
अणु
	पूर्णांक ret = 0;
	काष्ठा hdac_ext_link *hlink;
	bool link_up = false;

	mutex_lock(&bus->lock);

	/*
	 * अगर we move from 1 to 0, count will be 0
	 * so घातer करोwn this link as well
	 */
	अगर (--link->ref_count == 0) अणु
		ret = snd_hdac_ext_bus_link_घातer_करोwn(link);

		/*
		 * now check अगर all links are off, अगर so turn off
		 * cmd dma as well
		 */
		list_क्रम_each_entry(hlink, &bus->hlink_list, list) अणु
			अगर (hlink->ref_count) अणु
				link_up = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!link_up) अणु
			snd_hdac_bus_stop_cmd_io(bus);
			bus->cmd_dma_state = false;
		पूर्ण
	पूर्ण

	mutex_unlock(&bus->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_link_put);

अटल व्योम hdac_ext_codec_link_up(काष्ठा hdac_device *codec)
अणु
	स्थिर अक्षर *devname = dev_name(&codec->dev);
	काष्ठा hdac_ext_link *hlink =
		snd_hdac_ext_bus_get_link(codec->bus, devname);

	अगर (hlink)
		snd_hdac_ext_bus_link_get(codec->bus, hlink);
पूर्ण

अटल व्योम hdac_ext_codec_link_करोwn(काष्ठा hdac_device *codec)
अणु
	स्थिर अक्षर *devname = dev_name(&codec->dev);
	काष्ठा hdac_ext_link *hlink =
		snd_hdac_ext_bus_get_link(codec->bus, devname);

	अगर (hlink)
		snd_hdac_ext_bus_link_put(codec->bus, hlink);
पूर्ण

व्योम snd_hdac_ext_bus_link_घातer(काष्ठा hdac_device *codec, bool enable)
अणु
	काष्ठा hdac_bus *bus = codec->bus;
	bool oldstate = test_bit(codec->addr, &bus->codec_घातered);

	अगर (enable == oldstate)
		वापस;

	snd_hdac_bus_link_घातer(codec, enable);

	अगर (enable)
		hdac_ext_codec_link_up(codec);
	अन्यथा
		hdac_ext_codec_link_करोwn(codec);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_ext_bus_link_घातer);
