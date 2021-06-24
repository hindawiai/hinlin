<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Authors: Keyon Jie <yang.jie@linux.पूर्णांकel.com>

#समावेश <linux/पन.स>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_i915.h>
#समावेश "../sof-priv.h"
#समावेश "hda.h"

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)
#समावेश "../../codecs/hdac_hda.h"
#घोषणा sof_hda_ext_ops	snd_soc_hdac_hda_get_ops()
#अन्यथा
#घोषणा sof_hda_ext_ops	शून्य
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
अटल व्योम sof_hda_bus_link_घातer(काष्ठा hdac_device *codec, bool enable)
अणु
	काष्ठा hdac_bus *bus = codec->bus;
	bool oldstate = test_bit(codec->addr, &bus->codec_घातered);

	snd_hdac_ext_bus_link_घातer(codec, enable);

	अगर (enable == oldstate)
		वापस;

	/*
	 * Both codec driver and controller can hold references to
	 * display घातer. To aव्योम unnecessary घातer-up/करोwn cycles,
	 * controller करोesn't immediately release its reference.
	 *
	 * If the codec driver घातers करोwn the link, release
	 * the controller reference as well.
	 */
	अगर (codec->addr == HDA_IDISP_ADDR && !enable)
		snd_hdac_display_घातer(bus, HDA_CODEC_IDX_CONTROLLER, false);
पूर्ण

अटल स्थिर काष्ठा hdac_bus_ops bus_core_ops = अणु
	.command = snd_hdac_bus_send_cmd,
	.get_response = snd_hdac_bus_get_response,
	.link_घातer = sof_hda_bus_link_घातer,
पूर्ण;
#पूर्ण_अगर

/*
 * This can be used क्रम both with/without hda link support.
 */
व्योम sof_hda_bus_init(काष्ठा hdac_bus *bus, काष्ठा device *dev)
अणु
#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA)
	snd_hdac_ext_bus_init(bus, dev, &bus_core_ops, sof_hda_ext_ops);
#अन्यथा /* CONFIG_SND_SOC_SOF_HDA */
	स_रखो(bus, 0, माप(*bus));
	bus->dev = dev;

	INIT_LIST_HEAD(&bus->stream_list);

	bus->irq = -1;

	/*
	 * There is only one HDA bus aपंचांग. keep the index as 0.
	 * Need to fix when there are more than one HDA bus.
	 */
	bus->idx = 0;

	spin_lock_init(&bus->reg_lock);
#पूर्ण_अगर /* CONFIG_SND_SOC_SOF_HDA */
पूर्ण
