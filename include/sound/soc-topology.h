<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * linux/sound/soc-topology.h -- ALSA SoC Firmware Controls and DAPM
 *
 * Copyright (C) 2012 Texas Instruments Inc.
 * Copyright (C) 2015 Intel Corporation.
 *
 * Simple file API to load FW that includes mixers, coefficients, DAPM graphs,
 * algorithms, equalisers, DAIs, widमाला_लो, FE caps, BE caps, codec link caps etc.
 */

#अगर_अघोषित __LINUX_SND_SOC_TPLG_H
#घोषणा __LINUX_SND_SOC_TPLG_H

#समावेश <sound/asoc.h>
#समावेश <linux/list.h>

काष्ठा firmware;
काष्ठा snd_kcontrol;
काष्ठा snd_soc_tplg_pcm_be;
काष्ठा snd_ctl_elem_value;
काष्ठा snd_ctl_elem_info;
काष्ठा snd_soc_dapm_widget;
काष्ठा snd_soc_component;
काष्ठा snd_soc_tplg_pcm_fe;
काष्ठा snd_soc_dapm_context;
काष्ठा snd_soc_card;
काष्ठा snd_kcontrol_new;
काष्ठा snd_soc_dai_link;
काष्ठा snd_soc_dai_driver;
काष्ठा snd_soc_dai;
काष्ठा snd_soc_dapm_route;

/* dynamic object type */
क्रमागत snd_soc_करोbj_type अणु
	SND_SOC_DOBJ_NONE		= 0,	/* object is not dynamic */
	SND_SOC_DOBJ_MIXER,
	SND_SOC_DOBJ_BYTES,
	SND_SOC_DOBJ_ENUM,
	SND_SOC_DOBJ_GRAPH,
	SND_SOC_DOBJ_WIDGET,
	SND_SOC_DOBJ_DAI_LINK,
	SND_SOC_DOBJ_PCM,
	SND_SOC_DOBJ_CODEC_LINK,
	SND_SOC_DOBJ_BACKEND_LINK,
पूर्ण;

/* dynamic control object */
काष्ठा snd_soc_करोbj_control अणु
	काष्ठा snd_kcontrol *kcontrol;
	अक्षर **dtexts;
	अचिन्हित दीर्घ *dvalues;
पूर्ण;

/* dynamic widget object */
काष्ठा snd_soc_करोbj_widget अणु
	अचिन्हित पूर्णांक kcontrol_type;	/* kcontrol type: mixer, क्रमागत, bytes */
पूर्ण;

/* generic dynamic object - all dynamic objects beदीर्घ to this काष्ठा */
काष्ठा snd_soc_करोbj अणु
	क्रमागत snd_soc_करोbj_type type;
	अचिन्हित पूर्णांक index;	/* objects can beदीर्घ in dअगरferent groups */
	काष्ठा list_head list;
	काष्ठा snd_soc_tplg_ops *ops;
	जोड़ अणु
		काष्ठा snd_soc_करोbj_control control;
		काष्ठा snd_soc_करोbj_widget widget;
	पूर्ण;
	व्योम *निजी; /* core करोes not touch this */
पूर्ण;

/*
 * Kcontrol operations - used to map handlers onto firmware based controls.
 */
काष्ठा snd_soc_tplg_kcontrol_ops अणु
	u32 id;
	पूर्णांक (*get)(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol);
	पूर्णांक (*put)(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol);
	पूर्णांक (*info)(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo);
पूर्ण;

/* Bytes ext operations, क्रम TLV byte controls */
काष्ठा snd_soc_tplg_bytes_ext_ops अणु
	u32 id;
	पूर्णांक (*get)(काष्ठा snd_kcontrol *kcontrol, अचिन्हित पूर्णांक __user *bytes,
							अचिन्हित पूर्णांक size);
	पूर्णांक (*put)(काष्ठा snd_kcontrol *kcontrol,
			स्थिर अचिन्हित पूर्णांक __user *bytes, अचिन्हित पूर्णांक size);
पूर्ण;

/*
 * DAPM widget event handlers - used to map handlers onto widमाला_लो.
 */
काष्ठा snd_soc_tplg_widget_events अणु
	u16 type;
	पूर्णांक (*event_handler)(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *k, पूर्णांक event);
पूर्ण;

/*
 * Public API - Used by component drivers to load and unload dynamic objects
 * and their resources.
 */
काष्ठा snd_soc_tplg_ops अणु

	/* बाह्यal kcontrol init - used क्रम any driver specअगरic init */
	पूर्णांक (*control_load)(काष्ठा snd_soc_component *, पूर्णांक index,
		काष्ठा snd_kcontrol_new *, काष्ठा snd_soc_tplg_ctl_hdr *);
	पूर्णांक (*control_unload)(काष्ठा snd_soc_component *,
		काष्ठा snd_soc_करोbj *);

	/* DAPM graph route element loading and unloading */
	पूर्णांक (*dapm_route_load)(काष्ठा snd_soc_component *, पूर्णांक index,
		काष्ठा snd_soc_dapm_route *route);
	पूर्णांक (*dapm_route_unload)(काष्ठा snd_soc_component *,
		काष्ठा snd_soc_करोbj *);

	/* बाह्यal widget init - used क्रम any driver specअगरic init */
	पूर्णांक (*widget_load)(काष्ठा snd_soc_component *, पूर्णांक index,
		काष्ठा snd_soc_dapm_widget *,
		काष्ठा snd_soc_tplg_dapm_widget *);
	पूर्णांक (*widget_पढ़ोy)(काष्ठा snd_soc_component *, पूर्णांक index,
		काष्ठा snd_soc_dapm_widget *,
		काष्ठा snd_soc_tplg_dapm_widget *);
	पूर्णांक (*widget_unload)(काष्ठा snd_soc_component *,
		काष्ठा snd_soc_करोbj *);

	/* FE DAI - used क्रम any driver specअगरic init */
	पूर्णांक (*dai_load)(काष्ठा snd_soc_component *, पूर्णांक index,
		काष्ठा snd_soc_dai_driver *dai_drv,
		काष्ठा snd_soc_tplg_pcm *pcm, काष्ठा snd_soc_dai *dai);

	पूर्णांक (*dai_unload)(काष्ठा snd_soc_component *,
		काष्ठा snd_soc_करोbj *);

	/* DAI link - used क्रम any driver specअगरic init */
	पूर्णांक (*link_load)(काष्ठा snd_soc_component *, पूर्णांक index,
		काष्ठा snd_soc_dai_link *link,
		काष्ठा snd_soc_tplg_link_config *cfg);
	पूर्णांक (*link_unload)(काष्ठा snd_soc_component *,
		काष्ठा snd_soc_करोbj *);

	/* callback to handle venकरोr bespoke data */
	पूर्णांक (*venकरोr_load)(काष्ठा snd_soc_component *, पूर्णांक index,
		काष्ठा snd_soc_tplg_hdr *);
	पूर्णांक (*venकरोr_unload)(काष्ठा snd_soc_component *,
		काष्ठा snd_soc_tplg_hdr *);

	/* completion - called at completion of firmware loading */
	व्योम (*complete)(काष्ठा snd_soc_component *);

	/* manअगरest - optional to inक्रमm component of manअगरest */
	पूर्णांक (*manअगरest)(काष्ठा snd_soc_component *, पूर्णांक index,
		काष्ठा snd_soc_tplg_manअगरest *);

	/* venकरोr specअगरic kcontrol handlers available क्रम binding */
	स्थिर काष्ठा snd_soc_tplg_kcontrol_ops *io_ops;
	पूर्णांक io_ops_count;

	/* venकरोr specअगरic bytes ext handlers available क्रम binding */
	स्थिर काष्ठा snd_soc_tplg_bytes_ext_ops *bytes_ext_ops;
	पूर्णांक bytes_ext_ops_count;
पूर्ण;

#अगर_घोषित CONFIG_SND_SOC_TOPOLOGY

/* माला_लो a poपूर्णांकer to data from the firmware block header */
अटल अंतरभूत स्थिर व्योम *snd_soc_tplg_get_data(काष्ठा snd_soc_tplg_hdr *hdr)
अणु
	स्थिर व्योम *ptr = hdr;

	वापस ptr + माप(*hdr);
पूर्ण

/* Dynamic Object loading and removal क्रम component drivers */
पूर्णांक snd_soc_tplg_component_load(काष्ठा snd_soc_component *comp,
	काष्ठा snd_soc_tplg_ops *ops, स्थिर काष्ठा firmware *fw);
पूर्णांक snd_soc_tplg_component_हटाओ(काष्ठा snd_soc_component *comp);

/* Binds event handlers to dynamic widमाला_लो */
पूर्णांक snd_soc_tplg_widget_bind_event(काष्ठा snd_soc_dapm_widget *w,
	स्थिर काष्ठा snd_soc_tplg_widget_events *events, पूर्णांक num_events,
	u16 event_type);

#अन्यथा

अटल अंतरभूत पूर्णांक snd_soc_tplg_component_हटाओ(काष्ठा snd_soc_component *comp,
						u32 index)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
