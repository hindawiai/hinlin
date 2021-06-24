<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com
 */

#अगर_अघोषित K3_PSIL_PRIV_H_
#घोषणा K3_PSIL_PRIV_H_

#समावेश <linux/dma/k3-psil.h>

काष्ठा psil_ep अणु
	u32 thपढ़ो_id;
	काष्ठा psil_endpoपूर्णांक_config ep_config;
पूर्ण;

/**
 * काष्ठा psil_ep_map - PSI-L thपढ़ो ID configuration maps
 * @name:	Name of the map, set it to the name of the SoC
 * @src:	Array of source PSI-L thपढ़ो configurations
 * @src_count:	Number of entries in the src array
 * @dst:	Array of destination PSI-L thपढ़ो configurations
 * @dst_count:	Number of entries in the dst array
 *
 * In हाल of symmetric configuration क्रम a matching src/dst thपढ़ो (क्रम example
 * 0x4400 and 0xc400) only the src configuration can be present. If no dst
 * configuration found the code will look क्रम (dst_thपढ़ो_id & ~0x8000) to find
 * the symmetric match.
 */
काष्ठा psil_ep_map अणु
	अक्षर *name;
	काष्ठा psil_ep	*src;
	पूर्णांक src_count;
	काष्ठा psil_ep	*dst;
	पूर्णांक dst_count;
पूर्ण;

काष्ठा psil_endpoपूर्णांक_config *psil_get_ep_config(u32 thपढ़ो_id);

/* SoC PSI-L endpoपूर्णांक maps */
बाह्य काष्ठा psil_ep_map am654_ep_map;
बाह्य काष्ठा psil_ep_map j721e_ep_map;
बाह्य काष्ठा psil_ep_map j7200_ep_map;
बाह्य काष्ठा psil_ep_map am64_ep_map;

#पूर्ण_अगर /* K3_PSIL_PRIV_H_ */
