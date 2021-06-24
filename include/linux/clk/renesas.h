<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+
 *
 * Copyright 2013 Ideas On Board SPRL
 * Copyright 2013, 2014 Horms Solutions Ltd.
 *
 * Contact: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 * Contact: Simon Horman <horms@verge.net.au>
 */

#अगर_अघोषित __LINUX_CLK_RENESAS_H_
#घोषणा __LINUX_CLK_RENESAS_H_

#समावेश <linux/types.h>

काष्ठा device;
काष्ठा device_node;
काष्ठा generic_pm_करोमुख्य;

व्योम cpg_mstp_add_clk_करोमुख्य(काष्ठा device_node *np);
#अगर_घोषित CONFIG_CLK_RENESAS_CPG_MSTP
पूर्णांक cpg_mstp_attach_dev(काष्ठा generic_pm_करोमुख्य *unused, काष्ठा device *dev);
व्योम cpg_mstp_detach_dev(काष्ठा generic_pm_करोमुख्य *unused, काष्ठा device *dev);
#अन्यथा
#घोषणा cpg_mstp_attach_dev	शून्य
#घोषणा cpg_mstp_detach_dev	शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_CLK_RENESAS_CPG_MSSR
पूर्णांक cpg_mssr_attach_dev(काष्ठा generic_pm_करोमुख्य *unused, काष्ठा device *dev);
व्योम cpg_mssr_detach_dev(काष्ठा generic_pm_करोमुख्य *unused, काष्ठा device *dev);
#अन्यथा
#घोषणा cpg_mssr_attach_dev	शून्य
#घोषणा cpg_mssr_detach_dev	शून्य
#पूर्ण_अगर
#पूर्ण_अगर
