<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**************************************************************************
 * Copyright (c) 2009-2011, Intel Corporation.
 * All Rights Reserved.
 *
 * Authors:
 *    Benjamin Defnet <benjamin.r.defnet@पूर्णांकel.com>
 *    Rajesh Poornachandran <rajesh.poornachandran@पूर्णांकel.com>
 *
 **************************************************************************/

#अगर_अघोषित _PSB_IRQ_H_
#घोषणा _PSB_IRQ_H_

काष्ठा drm_crtc;
काष्ठा drm_device;

bool sysirq_init(काष्ठा drm_device *dev);
व्योम sysirq_uninit(काष्ठा drm_device *dev);

व्योम psb_irq_preinstall(काष्ठा drm_device *dev);
पूर्णांक  psb_irq_postinstall(काष्ठा drm_device *dev);
व्योम psb_irq_uninstall(काष्ठा drm_device *dev);
irqवापस_t psb_irq_handler(पूर्णांक irq, व्योम *arg);

पूर्णांक  psb_enable_vblank(काष्ठा drm_crtc *crtc);
व्योम psb_disable_vblank(काष्ठा drm_crtc *crtc);
u32  psb_get_vblank_counter(काष्ठा drm_crtc *crtc);

#पूर्ण_अगर /* _PSB_IRQ_H_ */
