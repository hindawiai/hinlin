<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_DEBUG_H_
#घोषणा _DP_DEBUG_H_

#समावेश "dp_panel.h"
#समावेश "dp_link.h"

/**
 * काष्ठा dp_debug
 * @debug_en: specअगरies whether debug mode enabled
 * @vdisplay: used to filter out vdisplay value
 * @hdisplay: used to filter out hdisplay value
 * @vrefresh: used to filter out vrefresh value
 * @tpg_state: specअगरies whether tpg feature is enabled
 */
काष्ठा dp_debug अणु
	bool debug_en;
	पूर्णांक aspect_ratio;
	पूर्णांक vdisplay;
	पूर्णांक hdisplay;
	पूर्णांक vrefresh;
पूर्ण;

#अगर defined(CONFIG_DEBUG_FS)

/**
 * dp_debug_get() - configure and get the DisplayPlot debug module data
 *
 * @dev: device instance of the caller
 * @panel: instance of panel module
 * @usbpd: instance of usbpd module
 * @link: instance of link module
 * @connector: द्विगुन poपूर्णांकer to display connector
 * @minor: poपूर्णांकer to drm minor number after device registration
 * वापस: poपूर्णांकer to allocated debug module data
 *
 * This function sets up the debug module and provides a way
 * क्रम debugfs input to be communicated with existing modules
 */
काष्ठा dp_debug *dp_debug_get(काष्ठा device *dev, काष्ठा dp_panel *panel,
		काष्ठा dp_usbpd *usbpd, काष्ठा dp_link *link,
		काष्ठा drm_connector **connector,
		काष्ठा drm_minor *minor);

/**
 * dp_debug_put()
 *
 * Cleans up dp_debug instance
 *
 * @dp_debug: instance of dp_debug
 */
व्योम dp_debug_put(काष्ठा dp_debug *dp_debug);

#अन्यथा

अटल अंतरभूत
काष्ठा dp_debug *dp_debug_get(काष्ठा device *dev, काष्ठा dp_panel *panel,
		काष्ठा dp_usbpd *usbpd, काष्ठा dp_link *link,
		काष्ठा drm_connector **connector, काष्ठा drm_minor *minor)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत व्योम dp_debug_put(काष्ठा dp_debug *dp_debug)
अणु
पूर्ण

#पूर्ण_अगर /* defined(CONFIG_DEBUG_FS) */

#पूर्ण_अगर /* _DP_DEBUG_H_ */
