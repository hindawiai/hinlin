<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header file क्रम FPGA Management Engine (FME) Partial Reconfiguration Driver
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Kang Luwei <luwei.kang@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Henry Mitchel <henry.mitchel@पूर्णांकel.com>
 */

#अगर_अघोषित __DFL_FME_PR_H
#घोषणा __DFL_FME_PR_H

#समावेश <linux/platक्रमm_device.h>

/**
 * काष्ठा dfl_fme_region - FME fpga region data काष्ठाure
 *
 * @region: platक्रमm device of the FPGA region.
 * @node: used to link fme_region to a list.
 * @port_id: indicate which port this region connected to.
 */
काष्ठा dfl_fme_region अणु
	काष्ठा platक्रमm_device *region;
	काष्ठा list_head node;
	पूर्णांक port_id;
पूर्ण;

/**
 * काष्ठा dfl_fme_region_pdata - platक्रमm data क्रम FME region platक्रमm device.
 *
 * @mgr: platक्रमm device of the FPGA manager.
 * @br: platक्रमm device of the FPGA bridge.
 * @region_id: region id (same as port_id).
 */
काष्ठा dfl_fme_region_pdata अणु
	काष्ठा platक्रमm_device *mgr;
	काष्ठा platक्रमm_device *br;
	पूर्णांक region_id;
पूर्ण;

/**
 * काष्ठा dfl_fme_bridge - FME fpga bridge data काष्ठाure
 *
 * @br: platक्रमm device of the FPGA bridge.
 * @node: used to link fme_bridge to a list.
 */
काष्ठा dfl_fme_bridge अणु
	काष्ठा platक्रमm_device *br;
	काष्ठा list_head node;
पूर्ण;

/**
 * काष्ठा dfl_fme_bridge_pdata - platक्रमm data क्रम FME bridge platक्रमm device.
 *
 * @cdev: container device.
 * @port_id: port id.
 */
काष्ठा dfl_fme_br_pdata अणु
	काष्ठा dfl_fpga_cdev *cdev;
	पूर्णांक port_id;
पूर्ण;

/**
 * काष्ठा dfl_fme_mgr_pdata - platक्रमm data क्रम FME manager platक्रमm device.
 *
 * @ioaddr: mapped io address क्रम FME manager platक्रमm device.
 */
काष्ठा dfl_fme_mgr_pdata अणु
	व्योम __iomem *ioaddr;
पूर्ण;

#घोषणा DFL_FPGA_FME_MGR	"dfl-fme-mgr"
#घोषणा DFL_FPGA_FME_BRIDGE	"dfl-fme-bridge"
#घोषणा DFL_FPGA_FME_REGION	"dfl-fme-region"

#पूर्ण_अगर /* __DFL_FME_PR_H */
