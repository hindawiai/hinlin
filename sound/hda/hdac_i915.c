<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  hdac_i915.c - routines क्रम sync between HD-A core and i915 display driver
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <sound/core.h>
#समावेश <sound/hdaudपन.स>
#समावेश <sound/hda_i915.h>
#समावेश <sound/hda_रेजिस्टर.h>

#घोषणा IS_HSW_CONTROLLER(pci) (((pci)->device == 0x0a0c) || \
				((pci)->device == 0x0c0c) || \
				((pci)->device == 0x0d0c) || \
				((pci)->device == 0x160c))

/**
 * snd_hdac_i915_set_bclk - Reprogram BCLK क्रम HSW/BDW
 * @bus: HDA core bus
 *
 * Intel HSW/BDW display HDA controller is in GPU. Both its घातer and link BCLK
 * depends on GPU. Two Extended Mode रेजिस्टरs EM4 (M value) and EM5 (N Value)
 * are used to convert CDClk (Core Display Clock) to 24MHz BCLK:
 * BCLK = CDCLK * M / N
 * The values will be lost when the display घातer well is disabled and need to
 * be restored to aव्योम abnormal playback speed.
 *
 * Call this function at initializing and changing घातer well, as well as
 * at ELD notअगरier क्रम the hotplug.
 */
व्योम snd_hdac_i915_set_bclk(काष्ठा hdac_bus *bus)
अणु
	काष्ठा drm_audio_component *acomp = bus->audio_component;
	काष्ठा pci_dev *pci = to_pci_dev(bus->dev);
	पूर्णांक cdclk_freq;
	अचिन्हित पूर्णांक bclk_m, bclk_n;

	अगर (!acomp || !acomp->ops || !acomp->ops->get_cdclk_freq)
		वापस; /* only क्रम i915 binding */
	अगर (!IS_HSW_CONTROLLER(pci))
		वापस; /* only HSW/BDW */

	cdclk_freq = acomp->ops->get_cdclk_freq(acomp->dev);
	चयन (cdclk_freq) अणु
	हाल 337500:
		bclk_m = 16;
		bclk_n = 225;
		अवरोध;

	हाल 450000:
	शेष: /* शेष CDCLK 450MHz */
		bclk_m = 4;
		bclk_n = 75;
		अवरोध;

	हाल 540000:
		bclk_m = 4;
		bclk_n = 90;
		अवरोध;

	हाल 675000:
		bclk_m = 8;
		bclk_n = 225;
		अवरोध;
	पूर्ण

	snd_hdac_chip_ग_लिखोw(bus, HSW_EM4, bclk_m);
	snd_hdac_chip_ग_लिखोw(bus, HSW_EM5, bclk_n);
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_i915_set_bclk);

/* वापसs true अगर the devices can be connected क्रम audio */
अटल bool connectivity_check(काष्ठा pci_dev *i915, काष्ठा pci_dev *hdac)
अणु
	काष्ठा pci_bus *bus_a = i915->bus, *bus_b = hdac->bus;

	/* directly connected on the same bus */
	अगर (bus_a == bus_b)
		वापस true;

	/*
	 * on i915 discrete GPUs with embedded HDA audio, the two
	 * devices are connected via 2nd level PCI bridge
	 */
	bus_a = bus_a->parent;
	bus_b = bus_b->parent;
	अगर (!bus_a || !bus_b)
		वापस false;
	bus_a = bus_a->parent;
	bus_b = bus_b->parent;
	अगर (bus_a && bus_a == bus_b)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक i915_component_master_match(काष्ठा device *dev, पूर्णांक subcomponent,
				       व्योम *data)
अणु
	काष्ठा pci_dev *hdac_pci, *i915_pci;
	काष्ठा hdac_bus *bus = data;

	अगर (!dev_is_pci(dev))
		वापस 0;

	hdac_pci = to_pci_dev(bus->dev);
	i915_pci = to_pci_dev(dev);

	अगर (!म_भेद(dev->driver->name, "i915") &&
	    subcomponent == I915_COMPONENT_AUDIO &&
	    connectivity_check(i915_pci, hdac_pci))
		वापस 1;

	वापस 0;
पूर्ण

/* check whether पूर्णांकel graphics is present */
अटल bool i915_gfx_present(व्योम)
अणु
	अटल स्थिर काष्ठा pci_device_id ids[] = अणु
		अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_ANY_ID),
		  .class = PCI_BASE_CLASS_DISPLAY << 16,
		  .class_mask = 0xff << 16 पूर्ण,
		अणुपूर्ण
	पूर्ण;
	वापस pci_dev_present(ids);
पूर्ण

/**
 * snd_hdac_i915_init - Initialize i915 audio component
 * @bus: HDA core bus
 *
 * This function is supposed to be used only by a HD-audio controller
 * driver that needs the पूर्णांकeraction with i915 graphics.
 *
 * This function initializes and sets up the audio component to communicate
 * with i915 graphics driver.
 *
 * Returns zero क्रम success or a negative error code.
 */
पूर्णांक snd_hdac_i915_init(काष्ठा hdac_bus *bus)
अणु
	काष्ठा drm_audio_component *acomp;
	पूर्णांक err;

	अगर (!i915_gfx_present())
		वापस -ENODEV;

	err = snd_hdac_acomp_init(bus, शून्य,
				  i915_component_master_match,
				  माप(काष्ठा i915_audio_component) - माप(*acomp));
	अगर (err < 0)
		वापस err;
	acomp = bus->audio_component;
	अगर (!acomp)
		वापस -ENODEV;
	अगर (!acomp->ops) अणु
		अगर (!IS_ENABLED(CONFIG_MODULES) ||
		    !request_module("i915")) अणु
			/* 60s समयout */
			रुको_क्रम_completion_समयout(&acomp->master_bind_complete,
						    msecs_to_jअगरfies(60 * 1000));
		पूर्ण
	पूर्ण
	अगर (!acomp->ops) अणु
		dev_info(bus->dev, "couldn't bind with audio component\n");
		snd_hdac_acomp_निकास(bus);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_hdac_i915_init);
