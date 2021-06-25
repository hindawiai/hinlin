<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus bundles
 *
 * Copyright 2014 Google Inc.
 * Copyright 2014 Linaro Ltd.
 */

#अगर_अघोषित __BUNDLE_H
#घोषणा __BUNDLE_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/device.h>

#घोषणा	BUNDLE_ID_NONE	U8_MAX

/* Greybus "public" definitions" */
काष्ठा gb_bundle अणु
	काष्ठा device		dev;
	काष्ठा gb_पूर्णांकerface	*पूर्णांकf;

	u8			id;
	u8			class;
	u8			class_major;
	u8			class_minor;

	माप_प्रकार			num_cports;
	काष्ठा greybus_descriptor_cport *cport_desc;

	काष्ठा list_head	connections;
	u8			*state;

	काष्ठा list_head	links;	/* पूर्णांकerface->bundles */
पूर्ण;
#घोषणा to_gb_bundle(d) container_of(d, काष्ठा gb_bundle, dev)

/* Greybus "private" definitions" */
काष्ठा gb_bundle *gb_bundle_create(काष्ठा gb_पूर्णांकerface *पूर्णांकf, u8 bundle_id,
				   u8 class);
पूर्णांक gb_bundle_add(काष्ठा gb_bundle *bundle);
व्योम gb_bundle_destroy(काष्ठा gb_bundle *bundle);

/* Bundle Runसमय PM wrappers */
#अगर_घोषित CONFIG_PM
अटल अंतरभूत पूर्णांक gb_pm_runसमय_get_sync(काष्ठा gb_bundle *bundle)
अणु
	पूर्णांक retval;

	retval = pm_runसमय_get_sync(&bundle->dev);
	अगर (retval < 0) अणु
		dev_err(&bundle->dev,
			"pm_runtime_get_sync failed: %d\n", retval);
		pm_runसमय_put_noidle(&bundle->dev);
		वापस retval;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक gb_pm_runसमय_put_स्वतःsuspend(काष्ठा gb_bundle *bundle)
अणु
	पूर्णांक retval;

	pm_runसमय_mark_last_busy(&bundle->dev);
	retval = pm_runसमय_put_स्वतःsuspend(&bundle->dev);

	वापस retval;
पूर्ण

अटल अंतरभूत व्योम gb_pm_runसमय_get_noresume(काष्ठा gb_bundle *bundle)
अणु
	pm_runसमय_get_noresume(&bundle->dev);
पूर्ण

अटल अंतरभूत व्योम gb_pm_runसमय_put_noidle(काष्ठा gb_bundle *bundle)
अणु
	pm_runसमय_put_noidle(&bundle->dev);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक gb_pm_runसमय_get_sync(काष्ठा gb_bundle *bundle)
अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक gb_pm_runसमय_put_स्वतःsuspend(काष्ठा gb_bundle *bundle)
अणु वापस 0; पूर्ण

अटल अंतरभूत व्योम gb_pm_runसमय_get_noresume(काष्ठा gb_bundle *bundle) अणुपूर्ण
अटल अंतरभूत व्योम gb_pm_runसमय_put_noidle(काष्ठा gb_bundle *bundle) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __BUNDLE_H */
