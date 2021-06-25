<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#समावेश <media/v4l2-event.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश "atomisp_cmd.h"
#समावेश "atomisp_internal.h"
#समावेश "atomisp-regs.h"

अटल काष्ठा v4l2_mbus_framefmt *__csi2_get_क्रमmat(काष्ठा
	atomisp_mipi_csi2_device
	* csi2,
	काष्ठा
	v4l2_subdev_pad_config *cfg,
	क्रमागत
	v4l2_subdev_क्रमmat_whence
	which, अचिन्हित पूर्णांक pad) अणु
	अगर (which == V4L2_SUBDEV_FORMAT_TRY)
		वापस v4l2_subdev_get_try_क्रमmat(&csi2->subdev, cfg, pad);
	अन्यथा
		वापस &csi2->क्रमmats[pad];
पूर्ण

/*
 * csi2_क्रमागत_mbus_code - Handle pixel क्रमmat क्रमागतeration
 * @sd     : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @fh     : V4L2 subdev file handle
 * @code   : poपूर्णांकer to v4l2_subdev_pad_mbus_code_क्रमागत काष्ठाure
 * वापस -EINVAL or zero on success
*/
अटल पूर्णांक csi2_क्रमागत_mbus_code(काष्ठा v4l2_subdev *sd,
			       काष्ठा v4l2_subdev_pad_config *cfg,
			       काष्ठा v4l2_subdev_mbus_code_क्रमागत *code)
अणु
	स्थिर काष्ठा atomisp_in_fmt_conv *ic = atomisp_in_fmt_conv;
	अचिन्हित पूर्णांक i = 0;

	जबतक (ic->code) अणु
		अगर (i == code->index) अणु
			code->code = ic->code;
			वापस 0;
		पूर्ण
		i++, ic++;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * csi2_get_क्रमmat - Handle get क्रमmat by pads subdev method
 * @sd : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @fh : V4L2 subdev file handle
 * @pad: pad num
 * @fmt: poपूर्णांकer to v4l2 क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
*/
अटल पूर्णांक csi2_get_क्रमmat(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	काष्ठा atomisp_mipi_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *क्रमmat;

	क्रमmat = __csi2_get_क्रमmat(csi2, cfg, fmt->which, fmt->pad);

	fmt->क्रमmat = *क्रमmat;

	वापस 0;
पूर्ण

पूर्णांक atomisp_csi2_set_ffmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  अचिन्हित पूर्णांक which, uपूर्णांक16_t pad,
			  काष्ठा v4l2_mbus_framefmt *ffmt)
अणु
	काष्ठा atomisp_mipi_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	काष्ठा v4l2_mbus_framefmt *actual_ffmt = __csi2_get_क्रमmat(csi2, cfg, which, pad);

	अगर (pad == CSI2_PAD_SINK) अणु
		स्थिर काष्ठा atomisp_in_fmt_conv *ic;
		काष्ठा v4l2_mbus_framefmt पंचांगp_ffmt;

		ic = atomisp_find_in_fmt_conv(ffmt->code);
		अगर (ic)
			actual_ffmt->code = ic->code;
		अन्यथा
			actual_ffmt->code = atomisp_in_fmt_conv[0].code;

		actual_ffmt->width = clamp_t(
					 u32, ffmt->width, ATOM_ISP_MIN_WIDTH,
					 ATOM_ISP_MAX_WIDTH);
		actual_ffmt->height = clamp_t(
					  u32, ffmt->height, ATOM_ISP_MIN_HEIGHT,
					  ATOM_ISP_MAX_HEIGHT);

		पंचांगp_ffmt = *ffmt = *actual_ffmt;

		वापस atomisp_csi2_set_ffmt(sd, cfg, which, CSI2_PAD_SOURCE,
					     &पंचांगp_ffmt);
	पूर्ण

	/* FIXME: DPCM decompression */
	*actual_ffmt = *ffmt = *__csi2_get_क्रमmat(csi2, cfg, which, CSI2_PAD_SINK);

	वापस 0;
पूर्ण

/*
 * csi2_set_क्रमmat - Handle set क्रमmat by pads subdev method
 * @sd : poपूर्णांकer to v4l2 subdev काष्ठाure
 * @fh : V4L2 subdev file handle
 * @pad: pad num
 * @fmt: poपूर्णांकer to v4l2 क्रमmat काष्ठाure
 * वापस -EINVAL or zero on success
*/
अटल पूर्णांक csi2_set_क्रमmat(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_subdev_pad_config *cfg,
			   काष्ठा v4l2_subdev_क्रमmat *fmt)
अणु
	वापस atomisp_csi2_set_ffmt(sd, cfg, fmt->which, fmt->pad,
				     &fmt->क्रमmat);
पूर्ण

/*
 * csi2_set_stream - Enable/Disable streaming on the CSI2 module
 * @sd: ISP CSI2 V4L2 subdevice
 * @enable: Enable/disable stream (1/0)
 *
 * Return 0 on success or a negative error code otherwise.
*/
अटल पूर्णांक csi2_set_stream(काष्ठा v4l2_subdev *sd, पूर्णांक enable)
अणु
	वापस 0;
पूर्ण

/* subdev core operations */
अटल स्थिर काष्ठा v4l2_subdev_core_ops csi2_core_ops = अणु
पूर्ण;

/* subdev video operations */
अटल स्थिर काष्ठा v4l2_subdev_video_ops csi2_video_ops = अणु
	.s_stream = csi2_set_stream,
पूर्ण;

/* subdev pad operations */
अटल स्थिर काष्ठा v4l2_subdev_pad_ops csi2_pad_ops = अणु
	.क्रमागत_mbus_code = csi2_क्रमागत_mbus_code,
	.get_fmt = csi2_get_क्रमmat,
	.set_fmt = csi2_set_क्रमmat,
	.link_validate = v4l2_subdev_link_validate_शेष,
पूर्ण;

/* subdev operations */
अटल स्थिर काष्ठा v4l2_subdev_ops csi2_ops = अणु
	.core = &csi2_core_ops,
	.video = &csi2_video_ops,
	.pad = &csi2_pad_ops,
पूर्ण;

/*
 * csi2_link_setup - Setup CSI2 connections.
 * @entity : Poपूर्णांकer to media entity काष्ठाure
 * @local  : Poपूर्णांकer to local pad array
 * @remote : Poपूर्णांकer to remote pad array
 * @flags  : Link flags
 * वापस -EINVAL or zero on success
*/
अटल पूर्णांक csi2_link_setup(काष्ठा media_entity *entity,
			   स्थिर काष्ठा media_pad *local,
			   स्थिर काष्ठा media_pad *remote, u32 flags)
अणु
	काष्ठा v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	काष्ठा atomisp_mipi_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	u32 result = local->index | is_media_entity_v4l2_subdev(remote->entity);

	चयन (result) अणु
	हाल CSI2_PAD_SOURCE | MEDIA_ENT_F_OLD_BASE:
		/* not supported yet */
		वापस -EINVAL;

	हाल CSI2_PAD_SOURCE | MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN:
		अगर (flags & MEDIA_LNK_FL_ENABLED) अणु
			अगर (csi2->output & ~CSI2_OUTPUT_ISP_SUBDEV)
				वापस -EBUSY;
			csi2->output |= CSI2_OUTPUT_ISP_SUBDEV;
		पूर्ण अन्यथा अणु
			csi2->output &= ~CSI2_OUTPUT_ISP_SUBDEV;
		पूर्ण
		अवरोध;

	शेष:
		/* Link from camera to CSI2 is fixed... */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* media operations */
अटल स्थिर काष्ठा media_entity_operations csi2_media_ops = अणु
	.link_setup = csi2_link_setup,
	.link_validate = v4l2_subdev_link_validate,
पूर्ण;

/*
* ispcsi2_init_entities - Initialize subdev and media entity.
* @csi2: Poपूर्णांकer to ispcsi2 काष्ठाure.
* वापस -ENOMEM or zero on success
*/
अटल पूर्णांक mipi_csi2_init_entities(काष्ठा atomisp_mipi_csi2_device *csi2,
				   पूर्णांक port)
अणु
	काष्ठा v4l2_subdev *sd = &csi2->subdev;
	काष्ठा media_pad *pads = csi2->pads;
	काष्ठा media_entity *me = &sd->entity;
	पूर्णांक ret;

	v4l2_subdev_init(sd, &csi2_ops);
	snम_लिखो(sd->name, माप(sd->name), "ATOM ISP CSI2-port%d", port);

	v4l2_set_subdevdata(sd, csi2);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[CSI2_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	pads[CSI2_PAD_SINK].flags = MEDIA_PAD_FL_SINK;

	me->ops = &csi2_media_ops;
	me->function = MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN;
	ret = media_entity_pads_init(me, CSI2_PADS_NUM, pads);
	अगर (ret < 0)
		वापस ret;

	csi2->क्रमmats[CSI2_PAD_SINK].code =
	    csi2->क्रमmats[CSI2_PAD_SOURCE].code =
		atomisp_in_fmt_conv[0].code;

	वापस 0;
पूर्ण

व्योम
atomisp_mipi_csi2_unरेजिस्टर_entities(काष्ठा atomisp_mipi_csi2_device *csi2)
अणु
	media_entity_cleanup(&csi2->subdev.entity);
	v4l2_device_unरेजिस्टर_subdev(&csi2->subdev);
पूर्ण

पूर्णांक atomisp_mipi_csi2_रेजिस्टर_entities(काष्ठा atomisp_mipi_csi2_device *csi2,
					काष्ठा v4l2_device *vdev)
अणु
	पूर्णांक ret;

	/* Register the subdev and video nodes. */
	ret = v4l2_device_रेजिस्टर_subdev(vdev, &csi2->subdev);
	अगर (ret < 0)
		जाओ error;

	वापस 0;

error:
	atomisp_mipi_csi2_unरेजिस्टर_entities(csi2);
	वापस ret;
पूर्ण

अटल स्थिर पूर्णांक LIMIT_SHIFT = 6;	/* Limit numeric range पूर्णांकo 31 bits */

अटल पूर्णांक
atomisp_csi2_configure_calc(स्थिर लघु पूर्णांक coeffs[2], पूर्णांक mipi_freq, पूर्णांक def)
अणु
	/* Delay counter accuracy, 1/0.0625 क्रम ANN/CHT, 1/0.125 क्रम BXT */
	अटल स्थिर पूर्णांक accinv = 16;		/* 1 / COUNT_ACC */
	पूर्णांक r;

	अगर (mipi_freq >> LIMIT_SHIFT <= 0)
		वापस def;

	r = accinv * coeffs[1] * (500000000 >> LIMIT_SHIFT);
	r /= mipi_freq >> LIMIT_SHIFT;
	r += accinv * coeffs[0];

	वापस r;
पूर्ण

अटल व्योम atomisp_csi2_configure_isp2401(काष्ठा atomisp_sub_device *asd)
अणु
	/*
	 * The ISP2401 new input प्रणाली CSI2+ receiver has several
	 * parameters affecting the receiver timings. These depend
	 * on the MIPI bus frequency F in Hz (sensor transmitter rate)
	 * as follows:
	 *	रेजिस्टर value = (A/1e9 + B * UI) / COUNT_ACC
	 * where
	 *	UI = 1 / (2 * F) in seconds
	 *	COUNT_ACC = counter accuracy in seconds
	 *	For ANN and CHV, COUNT_ACC = 0.0625 ns
	 *	For BXT,  COUNT_ACC = 0.125 ns
	 * A and B are coefficients from the table below,
	 * depending whether the रेजिस्टर minimum or maximum value is
	 * calculated.
	 *				       Minimum     Maximum
	 * Clock lane			       A     B     A     B
	 * reg_rx_csi_dly_cnt_termen_clane     0     0    38     0
	 * reg_rx_csi_dly_cnt_settle_clane    95    -8   300   -16
	 * Data lanes
	 * reg_rx_csi_dly_cnt_termen_dlane0    0     0    35     4
	 * reg_rx_csi_dly_cnt_settle_dlane0   85    -2   145    -6
	 * reg_rx_csi_dly_cnt_termen_dlane1    0     0    35     4
	 * reg_rx_csi_dly_cnt_settle_dlane1   85    -2   145    -6
	 * reg_rx_csi_dly_cnt_termen_dlane2    0     0    35     4
	 * reg_rx_csi_dly_cnt_settle_dlane2   85    -2   145    -6
	 * reg_rx_csi_dly_cnt_termen_dlane3    0     0    35     4
	 * reg_rx_csi_dly_cnt_settle_dlane3   85    -2   145    -6
	 *
	 * We use the minimum values in the calculations below.
	 */
	अटल स्थिर लघु पूर्णांक coeff_clk_termen[] = अणु 0, 0 पूर्ण;
	अटल स्थिर लघु पूर्णांक coeff_clk_settle[] = अणु 95, -8 पूर्ण;
	अटल स्थिर लघु पूर्णांक coeff_dat_termen[] = अणु 0, 0 पूर्ण;
	अटल स्थिर लघु पूर्णांक coeff_dat_settle[] = अणु 85, -2 पूर्ण;
	अटल स्थिर पूर्णांक TERMEN_DEFAULT		  = 0 * 0;
	अटल स्थिर पूर्णांक SETTLE_DEFAULT		  = 0x480;

	अटल स्थिर hrt_address csi2_port_base[] = अणु
		[ATOMISP_CAMERA_PORT_PRIMARY]     = CSI2_PORT_A_BASE,
		[ATOMISP_CAMERA_PORT_SECONDARY]   = CSI2_PORT_B_BASE,
		[ATOMISP_CAMERA_PORT_TERTIARY]    = CSI2_PORT_C_BASE,
	पूर्ण;
	/* Number of lanes on each port, excluding घड़ी lane */
	अटल स्थिर अचिन्हित अक्षर csi2_port_lanes[] = अणु
		[ATOMISP_CAMERA_PORT_PRIMARY]     = 4,
		[ATOMISP_CAMERA_PORT_SECONDARY]   = 2,
		[ATOMISP_CAMERA_PORT_TERTIARY]    = 2,
	पूर्ण;
	अटल स्थिर hrt_address csi2_lane_base[] = अणु
		CSI2_LANE_CL_BASE,
		CSI2_LANE_D0_BASE,
		CSI2_LANE_D1_BASE,
		CSI2_LANE_D2_BASE,
		CSI2_LANE_D3_BASE,
	पूर्ण;

	पूर्णांक clk_termen;
	पूर्णांक clk_settle;
	पूर्णांक dat_termen;
	पूर्णांक dat_settle;

	काष्ठा v4l2_control ctrl;
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा camera_mipi_info *mipi_info;
	पूर्णांक mipi_freq = 0;
	क्रमागत atomisp_camera_port port;

	पूर्णांक n;

	mipi_info = atomisp_to_sensor_mipi_info(
			isp->inमाला_दो[asd->input_curr].camera);
	port = mipi_info->port;

	ctrl.id = V4L2_CID_LINK_FREQ;
	अगर (v4l2_g_ctrl
	    (isp->inमाला_दो[asd->input_curr].camera->ctrl_handler, &ctrl) == 0)
		mipi_freq = ctrl.value;

	clk_termen = atomisp_csi2_configure_calc(coeff_clk_termen,
		     mipi_freq, TERMEN_DEFAULT);
	clk_settle = atomisp_csi2_configure_calc(coeff_clk_settle,
		     mipi_freq, SETTLE_DEFAULT);
	dat_termen = atomisp_csi2_configure_calc(coeff_dat_termen,
		     mipi_freq, TERMEN_DEFAULT);
	dat_settle = atomisp_csi2_configure_calc(coeff_dat_settle,
		     mipi_freq, SETTLE_DEFAULT);
	क्रम (n = 0; n < csi2_port_lanes[port] + 1; n++) अणु
		hrt_address base = csi2_port_base[port] + csi2_lane_base[n];

		atomisp_css2_hw_store_32(base + CSI2_REG_RX_CSI_DLY_CNT_TERMEN,
				     n == 0 ? clk_termen : dat_termen);
		atomisp_css2_hw_store_32(base + CSI2_REG_RX_CSI_DLY_CNT_SETTLE,
				     n == 0 ? clk_settle : dat_settle);
	पूर्ण
पूर्ण

व्योम atomisp_csi2_configure(काष्ठा atomisp_sub_device *asd)
अणु
	अगर (IS_HWREVISION(asd->isp, ATOMISP_HW_REVISION_ISP2401))
		atomisp_csi2_configure_isp2401(asd);
पूर्ण

/*
 * atomisp_mipi_csi2_cleanup - Routine क्रम module driver cleanup
*/
व्योम atomisp_mipi_csi2_cleanup(काष्ठा atomisp_device *isp)
अणु
पूर्ण

पूर्णांक atomisp_mipi_csi2_init(काष्ठा atomisp_device *isp)
अणु
	काष्ठा atomisp_mipi_csi2_device *csi2_port;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ATOMISP_CAMERA_NR_PORTS; i++) अणु
		csi2_port = &isp->csi2_port[i];
		csi2_port->isp = isp;
		ret = mipi_csi2_init_entities(csi2_port, i);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	वापस 0;

fail:
	atomisp_mipi_csi2_cleanup(isp);
	वापस ret;
पूर्ण
