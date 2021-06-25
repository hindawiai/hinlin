<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rcar_du_crtc.h  --  R-Car Display Unit CRTCs
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __RCAR_DU_CRTC_H__
#घोषणा __RCAR_DU_CRTC_H__

#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_ग_लिखोback.h>

#समावेश <media/vsp1.h>

काष्ठा rcar_du_group;
काष्ठा rcar_du_vsp;

/**
 * काष्ठा rcar_du_crtc - the CRTC, representing a DU superposition processor
 * @crtc: base DRM CRTC
 * @dev: the DU device
 * @घड़ी: the CRTC functional घड़ी
 * @extघड़ी: बाह्यal pixel करोt घड़ी (optional)
 * @mmio_offset: offset of the CRTC रेजिस्टरs in the DU MMIO block
 * @index: CRTC hardware index
 * @initialized: whether the CRTC has been initialized and घड़ीs enabled
 * @dsysr: cached value of the DSYSR रेजिस्टर
 * @vblank_enable: whether vblank events are enabled on this CRTC
 * @event: event to post when the pending page flip completes
 * @flip_रुको: रुको queue used to संकेत page flip completion
 * @vblank_lock: protects vblank_रुको and vblank_count
 * @vblank_रुको: रुको queue used to संकेत vertical blanking
 * @vblank_count: number of vertical blanking पूर्णांकerrupts to रुको क्रम
 * @group: CRTC group this CRTC beदीर्घs to
 * @cmm: CMM associated with this CRTC
 * @vsp: VSP feeding video to this CRTC
 * @vsp_pipe: index of the VSP pipeline feeding video to this CRTC
 * @ग_लिखोback: the ग_लिखोback connector
 */
काष्ठा rcar_du_crtc अणु
	काष्ठा drm_crtc crtc;

	काष्ठा rcar_du_device *dev;
	काष्ठा clk *घड़ी;
	काष्ठा clk *extघड़ी;
	अचिन्हित पूर्णांक mmio_offset;
	अचिन्हित पूर्णांक index;
	bool initialized;

	u32 dsysr;

	bool vblank_enable;
	काष्ठा drm_pending_vblank_event *event;
	रुको_queue_head_t flip_रुको;

	spinlock_t vblank_lock;
	रुको_queue_head_t vblank_रुको;
	अचिन्हित पूर्णांक vblank_count;

	काष्ठा rcar_du_group *group;
	काष्ठा platक्रमm_device *cmm;
	काष्ठा rcar_du_vsp *vsp;
	अचिन्हित पूर्णांक vsp_pipe;

	स्थिर अक्षर *स्थिर *sources;
	अचिन्हित पूर्णांक sources_count;

	काष्ठा drm_ग_लिखोback_connector ग_लिखोback;
पूर्ण;

#घोषणा to_rcar_crtc(c)		container_of(c, काष्ठा rcar_du_crtc, crtc)
#घोषणा wb_to_rcar_crtc(c)	container_of(c, काष्ठा rcar_du_crtc, ग_लिखोback)

/**
 * काष्ठा rcar_du_crtc_state - Driver-specअगरic CRTC state
 * @state: base DRM CRTC state
 * @crc: CRC computation configuration
 * @outमाला_दो: biपंचांगask of the outमाला_दो (क्रमागत rcar_du_output) driven by this CRTC
 */
काष्ठा rcar_du_crtc_state अणु
	काष्ठा drm_crtc_state state;

	काष्ठा vsp1_du_crc_config crc;
	अचिन्हित पूर्णांक outमाला_दो;
पूर्ण;

#घोषणा to_rcar_crtc_state(s) container_of(s, काष्ठा rcar_du_crtc_state, state)

क्रमागत rcar_du_output अणु
	RCAR_DU_OUTPUT_DPAD0,
	RCAR_DU_OUTPUT_DPAD1,
	RCAR_DU_OUTPUT_LVDS0,
	RCAR_DU_OUTPUT_LVDS1,
	RCAR_DU_OUTPUT_HDMI0,
	RCAR_DU_OUTPUT_HDMI1,
	RCAR_DU_OUTPUT_TCON,
	RCAR_DU_OUTPUT_MAX,
पूर्ण;

पूर्णांक rcar_du_crtc_create(काष्ठा rcar_du_group *rgrp, अचिन्हित पूर्णांक swindex,
			अचिन्हित पूर्णांक hwindex);

व्योम rcar_du_crtc_finish_page_flip(काष्ठा rcar_du_crtc *rcrtc);

व्योम rcar_du_crtc_dsysr_clr_set(काष्ठा rcar_du_crtc *rcrtc, u32 clr, u32 set);

#पूर्ण_अगर /* __RCAR_DU_CRTC_H__ */
