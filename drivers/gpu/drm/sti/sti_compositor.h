<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          क्रम STMicroelectronics.
 */

#अगर_अघोषित _STI_COMPOSITOR_H_
#घोषणा _STI_COMPOSITOR_H_

#समावेश <linux/clk.h>
#समावेश <linux/kernel.h>

#समावेश "sti_mixer.h"
#समावेश "sti_plane.h"

#घोषणा WAIT_NEXT_VSYNC_MS      50 /*ms*/

#घोषणा STI_MAX_MIXER 2
#घोषणा STI_MAX_VID   1

क्रमागत sti_compositor_subdev_type अणु
	STI_MIXER_MAIN_SUBDEV,
	STI_MIXER_AUX_SUBDEV,
	STI_GPD_SUBDEV,
	STI_VID_SUBDEV,
	STI_CURSOR_SUBDEV,
पूर्ण;

काष्ठा sti_compositor_subdev_descriptor अणु
	क्रमागत sti_compositor_subdev_type type;
	पूर्णांक id;
	अचिन्हित पूर्णांक offset;
पूर्ण;

/**
 * STI Compositor data काष्ठाure
 *
 * @nb_subdev: number of subdevices supported by the compositor
 * @subdev_desc: subdev list description
 */
#घोषणा MAX_SUBDEV 9
काष्ठा sti_compositor_data अणु
	अचिन्हित पूर्णांक nb_subdev;
	काष्ठा sti_compositor_subdev_descriptor subdev_desc[MAX_SUBDEV];
पूर्ण;

/**
 * STI Compositor काष्ठाure
 *
 * @dev: driver device
 * @regs: रेजिस्टरs (मुख्य)
 * @data: device data
 * @clk_compo_मुख्य: घड़ी क्रम मुख्य compo
 * @clk_compo_aux: घड़ी क्रम aux compo
 * @clk_pix_मुख्य: pixel घड़ी क्रम मुख्य path
 * @clk_pix_aux: pixel घड़ी क्रम aux path
 * @rst_मुख्य: reset control of the मुख्य path
 * @rst_aux: reset control of the aux path
 * @mixer: array of mixers
 * @vid: array of vids
 * @vtg: array of vtgs
 * @vtg_vblank_nb: array of callbacks क्रम VTG VSYNC notअगरication
 */
काष्ठा sti_compositor अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा sti_compositor_data data;
	काष्ठा clk *clk_compo_मुख्य;
	काष्ठा clk *clk_compo_aux;
	काष्ठा clk *clk_pix_मुख्य;
	काष्ठा clk *clk_pix_aux;
	काष्ठा reset_control *rst_मुख्य;
	काष्ठा reset_control *rst_aux;
	काष्ठा sti_mixer *mixer[STI_MAX_MIXER];
	काष्ठा sti_vid *vid[STI_MAX_VID];
	काष्ठा sti_vtg *vtg[STI_MAX_MIXER];
	काष्ठा notअगरier_block vtg_vblank_nb[STI_MAX_MIXER];
पूर्ण;

व्योम sti_compositor_debugfs_init(काष्ठा sti_compositor *compo,
				 काष्ठा drm_minor *minor);

#पूर्ण_अगर
