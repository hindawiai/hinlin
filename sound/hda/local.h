<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Local helper macros and functions क्रम HD-audio core drivers
 */

#अगर_अघोषित __HDAC_LOCAL_H
#घोषणा __HDAC_LOCAL_H

#घोषणा get_wcaps(codec, nid) \
	snd_hdac_पढ़ो_parm(codec, nid, AC_PAR_AUDIO_WIDGET_CAP)

/* get the widget type from widget capability bits */
अटल अंतरभूत पूर्णांक get_wcaps_type(अचिन्हित पूर्णांक wcaps)
अणु
	अगर (!wcaps)
		वापस -1; /* invalid type */
	वापस (wcaps & AC_WCAP_TYPE) >> AC_WCAP_TYPE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_wcaps_channels(u32 wcaps)
अणु
	अचिन्हित पूर्णांक chans;

	chans = (wcaps & AC_WCAP_CHAN_CNT_EXT) >> 13;
	chans = (chans + 1) * 2;

	वापस chans;
पूर्ण

बाह्य स्थिर काष्ठा attribute_group *hdac_dev_attr_groups[];
पूर्णांक hda_widget_sysfs_init(काष्ठा hdac_device *codec);
पूर्णांक hda_widget_sysfs_reinit(काष्ठा hdac_device *codec, hda_nid_t start_nid,
			    पूर्णांक num_nodes);
व्योम hda_widget_sysfs_निकास(काष्ठा hdac_device *codec);

पूर्णांक snd_hdac_bus_add_device(काष्ठा hdac_bus *bus, काष्ठा hdac_device *codec);
व्योम snd_hdac_bus_हटाओ_device(काष्ठा hdac_bus *bus,
				काष्ठा hdac_device *codec);
व्योम snd_hdac_bus_queue_event(काष्ठा hdac_bus *bus, u32 res, u32 res_ex);
पूर्णांक snd_hdac_bus_exec_verb(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr,
			   अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक *res);

पूर्णांक snd_hdac_exec_verb(काष्ठा hdac_device *codec, अचिन्हित पूर्णांक cmd,
		       अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक *res);

#पूर्ण_अगर /* __HDAC_LOCAL_H */
