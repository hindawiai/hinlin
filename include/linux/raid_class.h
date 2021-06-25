<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * raid_class.h - a generic raid visualisation class
 *
 * Copyright (c) 2005 - James Bottomley <James.Bottomley@steeleye.com>
 */
#समावेश <linux/transport_class.h>

काष्ठा raid_ढाँचा अणु
	काष्ठा transport_container raid_attrs;
पूर्ण;

काष्ठा raid_function_ढाँचा अणु
	व्योम *cookie;
	पूर्णांक (*is_raid)(काष्ठा device *);
	व्योम (*get_resync)(काष्ठा device *);
	व्योम (*get_state)(काष्ठा device *);
पूर्ण;

क्रमागत raid_state अणु
	RAID_STATE_UNKNOWN = 0,
	RAID_STATE_ACTIVE,
	RAID_STATE_DEGRADED,
	RAID_STATE_RESYNCING,
	RAID_STATE_OFFLINE,
पूर्ण;

क्रमागत raid_level अणु
	RAID_LEVEL_UNKNOWN = 0,
	RAID_LEVEL_LINEAR,
	RAID_LEVEL_0,
	RAID_LEVEL_1,
	RAID_LEVEL_10,
	RAID_LEVEL_1E,
	RAID_LEVEL_3,
	RAID_LEVEL_4,
	RAID_LEVEL_5,
	RAID_LEVEL_50,
	RAID_LEVEL_6,
	RAID_LEVEL_JBOD,
पूर्ण;

काष्ठा raid_data अणु
	काष्ठा list_head component_list;
	पूर्णांक component_count;
	क्रमागत raid_level level;
	क्रमागत raid_state state;
	पूर्णांक resync;
पूर्ण;

/* resync complete goes from 0 to this */
#घोषणा RAID_MAX_RESYNC		(10000)

#घोषणा DEFINE_RAID_ATTRIBUTE(type, attr)				      \
अटल अंतरभूत व्योम							      \
raid_set_##attr(काष्ठा raid_ढाँचा *r, काष्ठा device *dev, type value) अणु    \
	काष्ठा device *device =						      \
		attribute_container_find_class_device(&r->raid_attrs.ac, dev);\
	काष्ठा raid_data *rd;						      \
	BUG_ON(!device);						      \
	rd = dev_get_drvdata(device);					      \
	rd->attr = value;						      \
पूर्ण									      \
अटल अंतरभूत type							      \
raid_get_##attr(काष्ठा raid_ढाँचा *r, काष्ठा device *dev) अणु		      \
	काष्ठा device *device =						      \
		attribute_container_find_class_device(&r->raid_attrs.ac, dev);\
	काष्ठा raid_data *rd;						      \
	BUG_ON(!device);						      \
	rd = dev_get_drvdata(device);					      \
	वापस rd->attr;						      \
पूर्ण

DEFINE_RAID_ATTRIBUTE(क्रमागत raid_level, level)
DEFINE_RAID_ATTRIBUTE(पूर्णांक, resync)
DEFINE_RAID_ATTRIBUTE(क्रमागत raid_state, state)
	
काष्ठा raid_ढाँचा *raid_class_attach(काष्ठा raid_function_ढाँचा *);
व्योम raid_class_release(काष्ठा raid_ढाँचा *);

पूर्णांक __must_check raid_component_add(काष्ठा raid_ढाँचा *, काष्ठा device *,
				    काष्ठा device *);

