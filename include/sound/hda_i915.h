<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * HD-Audio helpers to sync with i915 driver
 */
#अगर_अघोषित __SOUND_HDA_I915_H
#घोषणा __SOUND_HDA_I915_H

#समावेश "hda_component.h"

#अगर_घोषित CONFIG_SND_HDA_I915
व्योम snd_hdac_i915_set_bclk(काष्ठा hdac_bus *bus);
पूर्णांक snd_hdac_i915_init(काष्ठा hdac_bus *bus);
#अन्यथा
अटल अंतरभूत व्योम snd_hdac_i915_set_bclk(काष्ठा hdac_bus *bus)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक snd_hdac_i915_init(काष्ठा hdac_bus *bus)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर
अटल अंतरभूत पूर्णांक snd_hdac_i915_निकास(काष्ठा hdac_bus *bus)
अणु
	वापस snd_hdac_acomp_निकास(bus);
पूर्ण

#पूर्ण_अगर /* __SOUND_HDA_I915_H */
