<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * virtio-snd: Virtio sound device
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#समावेश <linux/virtio_config.h>
#समावेश <sound/jack.h>
#समावेश <sound/hda_verbs.h>

#समावेश "virtio_card.h"

/**
 * DOC: Implementation Status
 *
 * At the moment jacks have a simple implementation and can only be used to
 * receive notअगरications about a plugged in/out device.
 *
 * VIRTIO_SND_R_JACK_REMAP
 *   is not supported
 */

/**
 * काष्ठा virtio_jack - VirtIO jack.
 * @jack: Kernel jack control.
 * @nid: Functional group node identअगरier.
 * @features: Jack virtio feature bit map (1 << VIRTIO_SND_JACK_F_XXX).
 * @defconf: Pin शेष configuration value.
 * @caps: Pin capabilities value.
 * @connected: Current jack connection status.
 * @type: Kernel jack type (SND_JACK_XXX).
 */
काष्ठा virtio_jack अणु
	काष्ठा snd_jack *jack;
	u32 nid;
	u32 features;
	u32 defconf;
	u32 caps;
	bool connected;
	पूर्णांक type;
पूर्ण;

/**
 * virtsnd_jack_get_label() - Get the name string क्रम the jack.
 * @vjack: VirtIO jack.
 *
 * Returns the jack name based on the शेष pin configuration value (see HDA
 * specअगरication).
 *
 * Context: Any context.
 * Return: Name string.
 */
अटल स्थिर अक्षर *virtsnd_jack_get_label(काष्ठा virtio_jack *vjack)
अणु
	अचिन्हित पूर्णांक defconf = vjack->defconf;
	अचिन्हित पूर्णांक device =
		(defconf & AC_DEFCFG_DEVICE) >> AC_DEFCFG_DEVICE_SHIFT;
	अचिन्हित पूर्णांक location =
		(defconf & AC_DEFCFG_LOCATION) >> AC_DEFCFG_LOCATION_SHIFT;

	चयन (device) अणु
	हाल AC_JACK_LINE_OUT:
		वापस "Line Out";
	हाल AC_JACK_SPEAKER:
		वापस "Speaker";
	हाल AC_JACK_HP_OUT:
		वापस "Headphone";
	हाल AC_JACK_CD:
		वापस "CD";
	हाल AC_JACK_SPDIF_OUT:
	हाल AC_JACK_DIG_OTHER_OUT:
		अगर (location == AC_JACK_LOC_HDMI)
			वापस "HDMI Out";
		अन्यथा
			वापस "SPDIF Out";
	हाल AC_JACK_LINE_IN:
		वापस "Line";
	हाल AC_JACK_AUX:
		वापस "Aux";
	हाल AC_JACK_MIC_IN:
		वापस "Mic";
	हाल AC_JACK_SPDIF_IN:
		वापस "SPDIF In";
	हाल AC_JACK_DIG_OTHER_IN:
		वापस "Digital In";
	शेष:
		वापस "Misc";
	पूर्ण
पूर्ण

/**
 * virtsnd_jack_get_type() - Get the type क्रम the jack.
 * @vjack: VirtIO jack.
 *
 * Returns the jack type based on the शेष pin configuration value (see HDA
 * specअगरication).
 *
 * Context: Any context.
 * Return: SND_JACK_XXX value.
 */
अटल पूर्णांक virtsnd_jack_get_type(काष्ठा virtio_jack *vjack)
अणु
	अचिन्हित पूर्णांक defconf = vjack->defconf;
	अचिन्हित पूर्णांक device =
		(defconf & AC_DEFCFG_DEVICE) >> AC_DEFCFG_DEVICE_SHIFT;

	चयन (device) अणु
	हाल AC_JACK_LINE_OUT:
	हाल AC_JACK_SPEAKER:
		वापस SND_JACK_LINEOUT;
	हाल AC_JACK_HP_OUT:
		वापस SND_JACK_HEADPHONE;
	हाल AC_JACK_SPDIF_OUT:
	हाल AC_JACK_DIG_OTHER_OUT:
		वापस SND_JACK_AVOUT;
	हाल AC_JACK_MIC_IN:
		वापस SND_JACK_MICROPHONE;
	शेष:
		वापस SND_JACK_LINEIN;
	पूर्ण
पूर्ण

/**
 * virtsnd_jack_parse_cfg() - Parse the jack configuration.
 * @snd: VirtIO sound device.
 *
 * This function is called during initial device initialization.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक virtsnd_jack_parse_cfg(काष्ठा virtio_snd *snd)
अणु
	काष्ठा virtio_device *vdev = snd->vdev;
	काष्ठा virtio_snd_jack_info *info;
	u32 i;
	पूर्णांक rc;

	virtio_cपढ़ो_le(vdev, काष्ठा virtio_snd_config, jacks, &snd->njacks);
	अगर (!snd->njacks)
		वापस 0;

	snd->jacks = devm_kसुस्मृति(&vdev->dev, snd->njacks, माप(*snd->jacks),
				  GFP_KERNEL);
	अगर (!snd->jacks)
		वापस -ENOMEM;

	info = kसुस्मृति(snd->njacks, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	rc = virtsnd_ctl_query_info(snd, VIRTIO_SND_R_JACK_INFO, 0, snd->njacks,
				    माप(*info), info);
	अगर (rc)
		जाओ on_निकास;

	क्रम (i = 0; i < snd->njacks; ++i) अणु
		काष्ठा virtio_jack *vjack = &snd->jacks[i];

		vjack->nid = le32_to_cpu(info[i].hdr.hda_fn_nid);
		vjack->features = le32_to_cpu(info[i].features);
		vjack->defconf = le32_to_cpu(info[i].hda_reg_defconf);
		vjack->caps = le32_to_cpu(info[i].hda_reg_caps);
		vjack->connected = info[i].connected;
	पूर्ण

on_निकास:
	kमुक्त(info);

	वापस rc;
पूर्ण

/**
 * virtsnd_jack_build_devs() - Build ALSA controls क्रम jacks.
 * @snd: VirtIO sound device.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक virtsnd_jack_build_devs(काष्ठा virtio_snd *snd)
अणु
	u32 i;
	पूर्णांक rc;

	क्रम (i = 0; i < snd->njacks; ++i) अणु
		काष्ठा virtio_jack *vjack = &snd->jacks[i];

		vjack->type = virtsnd_jack_get_type(vjack);

		rc = snd_jack_new(snd->card, virtsnd_jack_get_label(vjack),
				  vjack->type, &vjack->jack, true, true);
		अगर (rc)
			वापस rc;

		अगर (vjack->jack)
			vjack->jack->निजी_data = vjack;

		snd_jack_report(vjack->jack,
				vjack->connected ? vjack->type : 0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * virtsnd_jack_event() - Handle the jack event notअगरication.
 * @snd: VirtIO sound device.
 * @event: VirtIO sound event.
 *
 * Context: Interrupt context.
 */
व्योम virtsnd_jack_event(काष्ठा virtio_snd *snd, काष्ठा virtio_snd_event *event)
अणु
	u32 jack_id = le32_to_cpu(event->data);
	काष्ठा virtio_jack *vjack;

	अगर (jack_id >= snd->njacks)
		वापस;

	vjack = &snd->jacks[jack_id];

	चयन (le32_to_cpu(event->hdr.code)) अणु
	हाल VIRTIO_SND_EVT_JACK_CONNECTED:
		vjack->connected = true;
		अवरोध;
	हाल VIRTIO_SND_EVT_JACK_DISCONNECTED:
		vjack->connected = false;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	snd_jack_report(vjack->jack, vjack->connected ? vjack->type : 0);
पूर्ण
