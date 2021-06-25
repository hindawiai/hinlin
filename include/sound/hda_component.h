<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// HD-Audio helpers to sync with DRM driver

#अगर_अघोषित __SOUND_HDA_COMPONENT_H
#घोषणा __SOUND_HDA_COMPONENT_H

#समावेश <drm/drm_audio_component.h>
#समावेश <sound/hdaudपन.स>

/* भव idx क्रम controller */
#घोषणा HDA_CODEC_IDX_CONTROLLER	HDA_MAX_CODECS

#अगर_घोषित CONFIG_SND_HDA_COMPONENT
पूर्णांक snd_hdac_set_codec_wakeup(काष्ठा hdac_bus *bus, bool enable);
व्योम snd_hdac_display_घातer(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक idx,
			    bool enable);
पूर्णांक snd_hdac_sync_audio_rate(काष्ठा hdac_device *codec, hda_nid_t nid,
			     पूर्णांक dev_id, पूर्णांक rate);
पूर्णांक snd_hdac_acomp_get_eld(काष्ठा hdac_device *codec, hda_nid_t nid, पूर्णांक dev_id,
			   bool *audio_enabled, अक्षर *buffer, पूर्णांक max_bytes);
पूर्णांक snd_hdac_acomp_init(काष्ठा hdac_bus *bus,
			स्थिर काष्ठा drm_audio_component_audio_ops *aops,
			पूर्णांक (*match_master)(काष्ठा device *, पूर्णांक, व्योम *),
			माप_प्रकार extra_size);
पूर्णांक snd_hdac_acomp_निकास(काष्ठा hdac_bus *bus);
पूर्णांक snd_hdac_acomp_रेजिस्टर_notअगरier(काष्ठा hdac_bus *bus,
				    स्थिर काष्ठा drm_audio_component_audio_ops *ops);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_hdac_set_codec_wakeup(काष्ठा hdac_bus *bus, bool enable)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम snd_hdac_display_घातer(काष्ठा hdac_bus *bus,
					  अचिन्हित पूर्णांक idx, bool enable)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक snd_hdac_sync_audio_rate(काष्ठा hdac_device *codec,
					   hda_nid_t nid, पूर्णांक dev_id, पूर्णांक rate)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक snd_hdac_acomp_get_eld(काष्ठा hdac_device *codec, hda_nid_t nid,
					 पूर्णांक dev_id, bool *audio_enabled,
					 अक्षर *buffer, पूर्णांक max_bytes)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक snd_hdac_acomp_init(काष्ठा hdac_bus *bus,
				      स्थिर काष्ठा drm_audio_component_audio_ops *aops,
				      पूर्णांक (*match_master)(काष्ठा device *,
							  पूर्णांक, व्योम *),
				      माप_प्रकार extra_size)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक snd_hdac_acomp_निकास(काष्ठा hdac_bus *bus)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक snd_hdac_acomp_रेजिस्टर_notअगरier(काष्ठा hdac_bus *bus,
						  स्थिर काष्ठा drm_audio_component_audio_ops *ops)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_HDA_COMPONENT_H */
