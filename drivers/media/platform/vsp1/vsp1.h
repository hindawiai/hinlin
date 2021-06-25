<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1.h  --  R-Car VSP1 Driver
 *
 * Copyright (C) 2013-2014 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_H__
#घोषणा __VSP1_H__

#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>

#समावेश <media/media-device.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-subdev.h>

#समावेश "vsp1_regs.h"

काष्ठा clk;
काष्ठा device;
काष्ठा rcar_fcp_device;

काष्ठा vsp1_drm;
काष्ठा vsp1_entity;
काष्ठा vsp1_platक्रमm_data;
काष्ठा vsp1_brx;
काष्ठा vsp1_clu;
काष्ठा vsp1_hgo;
काष्ठा vsp1_hgt;
काष्ठा vsp1_hsit;
काष्ठा vsp1_lअगर;
काष्ठा vsp1_lut;
काष्ठा vsp1_rwpf;
काष्ठा vsp1_sru;
काष्ठा vsp1_uds;
काष्ठा vsp1_uअगर;

#घोषणा VSP1_MAX_LIF		2
#घोषणा VSP1_MAX_RPF		5
#घोषणा VSP1_MAX_UDS		3
#घोषणा VSP1_MAX_UIF		2
#घोषणा VSP1_MAX_WPF		4

#घोषणा VSP1_HAS_LUT		BIT(1)
#घोषणा VSP1_HAS_SRU		BIT(2)
#घोषणा VSP1_HAS_BRU		BIT(3)
#घोषणा VSP1_HAS_CLU		BIT(4)
#घोषणा VSP1_HAS_WPF_VFLIP	BIT(5)
#घोषणा VSP1_HAS_WPF_HFLIP	BIT(6)
#घोषणा VSP1_HAS_HGO		BIT(7)
#घोषणा VSP1_HAS_HGT		BIT(8)
#घोषणा VSP1_HAS_BRS		BIT(9)
#घोषणा VSP1_HAS_EXT_DL		BIT(10)

काष्ठा vsp1_device_info अणु
	u32 version;
	स्थिर अक्षर *model;
	अचिन्हित पूर्णांक gen;
	अचिन्हित पूर्णांक features;
	अचिन्हित पूर्णांक lअगर_count;
	अचिन्हित पूर्णांक rpf_count;
	अचिन्हित पूर्णांक uds_count;
	अचिन्हित पूर्णांक uअगर_count;
	अचिन्हित पूर्णांक wpf_count;
	अचिन्हित पूर्णांक num_bru_inमाला_दो;
	bool uapi;
पूर्ण;

#घोषणा vsp1_feature(vsp1, f) ((vsp1)->info->features & (f))

काष्ठा vsp1_device अणु
	काष्ठा device *dev;
	स्थिर काष्ठा vsp1_device_info *info;
	u32 version;

	व्योम __iomem *mmio;
	काष्ठा rcar_fcp_device *fcp;
	काष्ठा device *bus_master;

	काष्ठा vsp1_brx *brs;
	काष्ठा vsp1_brx *bru;
	काष्ठा vsp1_clu *clu;
	काष्ठा vsp1_hgo *hgo;
	काष्ठा vsp1_hgt *hgt;
	काष्ठा vsp1_hsit *hsi;
	काष्ठा vsp1_hsit *hst;
	काष्ठा vsp1_lअगर *lअगर[VSP1_MAX_LIF];
	काष्ठा vsp1_lut *lut;
	काष्ठा vsp1_rwpf *rpf[VSP1_MAX_RPF];
	काष्ठा vsp1_sru *sru;
	काष्ठा vsp1_uds *uds[VSP1_MAX_UDS];
	काष्ठा vsp1_uअगर *uअगर[VSP1_MAX_UIF];
	काष्ठा vsp1_rwpf *wpf[VSP1_MAX_WPF];

	काष्ठा list_head entities;
	काष्ठा list_head videos;

	काष्ठा v4l2_device v4l2_dev;
	काष्ठा media_device media_dev;
	काष्ठा media_entity_operations media_ops;

	काष्ठा vsp1_drm *drm;
पूर्ण;

पूर्णांक vsp1_device_get(काष्ठा vsp1_device *vsp1);
व्योम vsp1_device_put(काष्ठा vsp1_device *vsp1);

पूर्णांक vsp1_reset_wpf(काष्ठा vsp1_device *vsp1, अचिन्हित पूर्णांक index);

अटल अंतरभूत u32 vsp1_पढ़ो(काष्ठा vsp1_device *vsp1, u32 reg)
अणु
	वापस ioपढ़ो32(vsp1->mmio + reg);
पूर्ण

अटल अंतरभूत व्योम vsp1_ग_लिखो(काष्ठा vsp1_device *vsp1, u32 reg, u32 data)
अणु
	ioग_लिखो32(data, vsp1->mmio + reg);
पूर्ण

#पूर्ण_अगर /* __VSP1_H__ */
