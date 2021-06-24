<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Texas Instruments Inc
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/रुको.h>
#समावेश <linux/समय.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/davinci/vpbe_types.h>
#समावेश <media/davinci/vpbe.h>
#समावेश <media/davinci/vpss.h>
#समावेश <media/davinci/vpbe_venc.h>

#घोषणा VPBE_DEFAULT_OUTPUT	"Composite"
#घोषणा VPBE_DEFAULT_MODE	"ntsc"

अटल अक्षर *def_output = VPBE_DEFAULT_OUTPUT;
अटल अक्षर *def_mode = VPBE_DEFAULT_MODE;
अटल पूर्णांक debug;

module_param(def_output, अक्षरp, S_IRUGO);
module_param(def_mode, अक्षरp, S_IRUGO);
module_param(debug, पूर्णांक, 0644);

MODULE_PARM_DESC(def_output, "vpbe output name (default:Composite)");
MODULE_PARM_DESC(def_mode, "vpbe output mode name (default:ntsc");
MODULE_PARM_DESC(debug, "Debug level 0-1");

MODULE_DESCRIPTION("TI DMXXX VPBE Display controller");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Texas Instruments");

/**
 * vpbe_current_encoder_info - Get config info क्रम current encoder
 * @vpbe_dev: vpbe device ptr
 *
 * Return ptr to current encoder config info
 */
अटल काष्ठा encoder_config_info*
vpbe_current_encoder_info(काष्ठा vpbe_device *vpbe_dev)
अणु
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	पूर्णांक index = vpbe_dev->current_sd_index;

	वापस ((index == 0) ? &cfg->venc :
				&cfg->ext_encoders[index-1]);
पूर्ण

/**
 * vpbe_find_encoder_sd_index - Given a name find encoder sd index
 *
 * @cfg: ptr to vpbe cfg
 * @index: index used by application
 *
 * Return sd index of the encoder
 */
अटल पूर्णांक vpbe_find_encoder_sd_index(काष्ठा vpbe_config *cfg,
			     पूर्णांक index)
अणु
	अक्षर *encoder_name = cfg->outमाला_दो[index].subdev_name;
	पूर्णांक i;

	/* Venc is always first	*/
	अगर (!म_भेद(encoder_name, cfg->venc.module_name))
		वापस 0;

	क्रम (i = 0; i < cfg->num_ext_encoders; i++) अणु
		अगर (!म_भेद(encoder_name,
		     cfg->ext_encoders[i].module_name))
			वापस i+1;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * vpbe_क्रमागत_outमाला_दो - क्रमागतerate outमाला_दो
 * @vpbe_dev: vpbe device ptr
 * @output: ptr to v4l2_output काष्ठाure
 *
 * Enumerates the outमाला_दो available at the vpbe display
 * वापसs the status, -EINVAL अगर end of output list
 */
अटल पूर्णांक vpbe_क्रमागत_outमाला_दो(काष्ठा vpbe_device *vpbe_dev,
			     काष्ठा v4l2_output *output)
अणु
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	अचिन्हित पूर्णांक temp_index = output->index;

	अगर (temp_index >= cfg->num_outमाला_दो)
		वापस -EINVAL;

	*output = cfg->outमाला_दो[temp_index].output;
	output->index = temp_index;

	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_get_mode_info(काष्ठा vpbe_device *vpbe_dev, अक्षर *mode,
			      पूर्णांक output_index)
अणु
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	काष्ठा vpbe_enc_mode_info var;
	पूर्णांक curr_output = output_index;
	पूर्णांक i;

	अगर (!mode)
		वापस -EINVAL;

	क्रम (i = 0; i < cfg->outमाला_दो[curr_output].num_modes; i++) अणु
		var = cfg->outमाला_दो[curr_output].modes[i];
		अगर (!म_भेद(mode, var.name)) अणु
			vpbe_dev->current_timings = var;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vpbe_get_current_mode_info(काष्ठा vpbe_device *vpbe_dev,
				      काष्ठा vpbe_enc_mode_info *mode_info)
अणु
	अगर (!mode_info)
		वापस -EINVAL;

	*mode_info = vpbe_dev->current_timings;

	वापस 0;
पूर्ण

/* Get std by std id */
अटल पूर्णांक vpbe_get_std_info(काष्ठा vpbe_device *vpbe_dev,
			     v4l2_std_id std_id)
अणु
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	काष्ठा vpbe_enc_mode_info var;
	पूर्णांक curr_output = vpbe_dev->current_out_index;
	पूर्णांक i;

	क्रम (i = 0; i < vpbe_dev->cfg->outमाला_दो[curr_output].num_modes; i++) अणु
		var = cfg->outमाला_दो[curr_output].modes[i];
		अगर ((var.timings_type & VPBE_ENC_STD) &&
		  (var.std_id & std_id)) अणु
			vpbe_dev->current_timings = var;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vpbe_get_std_info_by_name(काष्ठा vpbe_device *vpbe_dev,
				अक्षर *std_name)
अणु
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	काष्ठा vpbe_enc_mode_info var;
	पूर्णांक curr_output = vpbe_dev->current_out_index;
	पूर्णांक i;

	क्रम (i = 0; i < vpbe_dev->cfg->outमाला_दो[curr_output].num_modes; i++) अणु
		var = cfg->outमाला_दो[curr_output].modes[i];
		अगर (!म_भेद(var.name, std_name)) अणु
			vpbe_dev->current_timings = var;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * vpbe_set_output - Set output
 * @vpbe_dev: vpbe device ptr
 * @index: index of output
 *
 * Set vpbe output to the output specअगरied by the index
 */
अटल पूर्णांक vpbe_set_output(काष्ठा vpbe_device *vpbe_dev, पूर्णांक index)
अणु
	काष्ठा encoder_config_info *curr_enc_info =
			vpbe_current_encoder_info(vpbe_dev);
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	काष्ठा venc_platक्रमm_data *venc_device = vpbe_dev->venc_device;
	पूर्णांक enc_out_index;
	पूर्णांक sd_index;
	पूर्णांक ret;

	अगर (index >= cfg->num_outमाला_दो)
		वापस -EINVAL;

	mutex_lock(&vpbe_dev->lock);

	sd_index = vpbe_dev->current_sd_index;
	enc_out_index = cfg->outमाला_दो[index].output.index;
	/*
	 * Currently we चयन the encoder based on output selected
	 * by the application. If media controller is implemented later
	 * there is will be an API added to setup_link between venc
	 * and बाह्यal encoder. So in that हाल below comparison always
	 * match and encoder will not be चयनed. But अगर application
	 * chose not to use media controller, then this provides current
	 * way of चयनing encoder at the venc output.
	 */
	अगर (म_भेद(curr_enc_info->module_name,
		   cfg->outमाला_दो[index].subdev_name)) अणु
		/* Need to चयन the encoder at the output */
		sd_index = vpbe_find_encoder_sd_index(cfg, index);
		अगर (sd_index < 0) अणु
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण

		ret = venc_device->setup_अगर_config(cfg->outमाला_दो[index].अगर_params);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	/* Set output at the encoder */
	ret = v4l2_subdev_call(vpbe_dev->encoders[sd_index], video,
				       s_routing, 0, enc_out_index, 0);
	अगर (ret)
		जाओ unlock;

	/*
	 * It is assumed that venc or बाह्यal encoder will set a शेष
	 * mode in the sub device. For बाह्यal encoder or LCD pannel output,
	 * we also need to set up the lcd port क्रम the required mode. So setup
	 * the lcd port क्रम the शेष mode that is configured in the board
	 * arch/arm/mach-davinci/board-dm355-evm.setup file क्रम the बाह्यal
	 * encoder.
	 */
	ret = vpbe_get_mode_info(vpbe_dev,
				 cfg->outमाला_दो[index].शेष_mode, index);
	अगर (!ret) अणु
		काष्ठा osd_state *osd_device = vpbe_dev->osd_device;

		osd_device->ops.set_left_margin(osd_device,
			vpbe_dev->current_timings.left_margin);
		osd_device->ops.set_top_margin(osd_device,
		vpbe_dev->current_timings.upper_margin);
		vpbe_dev->current_sd_index = sd_index;
		vpbe_dev->current_out_index = index;
	पूर्ण
unlock:
	mutex_unlock(&vpbe_dev->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vpbe_set_शेष_output(काष्ठा vpbe_device *vpbe_dev)
अणु
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	पूर्णांक i;

	क्रम (i = 0; i < cfg->num_outमाला_दो; i++) अणु
		अगर (!म_भेद(def_output,
			    cfg->outमाला_दो[i].output.name)) अणु
			पूर्णांक ret = vpbe_set_output(vpbe_dev, i);

			अगर (!ret)
				vpbe_dev->current_out_index = i;
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * vpbe_get_output - Get output
 * @vpbe_dev: vpbe device ptr
 *
 * वापस current vpbe output to the the index
 */
अटल अचिन्हित पूर्णांक vpbe_get_output(काष्ठा vpbe_device *vpbe_dev)
अणु
	वापस vpbe_dev->current_out_index;
पूर्ण

/*
 * vpbe_s_dv_timings - Set the given preset timings in the encoder
 *
 * Sets the timings अगर supported by the current encoder. Return the status.
 * 0 - success & -EINVAL on error
 */
अटल पूर्णांक vpbe_s_dv_timings(काष्ठा vpbe_device *vpbe_dev,
		    काष्ठा v4l2_dv_timings *dv_timings)
अणु
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	पूर्णांक out_index = vpbe_dev->current_out_index;
	काष्ठा vpbe_output *output = &cfg->outमाला_दो[out_index];
	पूर्णांक sd_index = vpbe_dev->current_sd_index;
	पूर्णांक ret, i;


	अगर (!(cfg->outमाला_दो[out_index].output.capabilities &
	    V4L2_OUT_CAP_DV_TIMINGS))
		वापस -ENODATA;

	क्रम (i = 0; i < output->num_modes; i++) अणु
		अगर (output->modes[i].timings_type == VPBE_ENC_DV_TIMINGS &&
		    !स_भेद(&output->modes[i].dv_timings,
				dv_timings, माप(*dv_timings)))
			अवरोध;
	पूर्ण
	अगर (i >= output->num_modes)
		वापस -EINVAL;
	vpbe_dev->current_timings = output->modes[i];
	mutex_lock(&vpbe_dev->lock);

	ret = v4l2_subdev_call(vpbe_dev->encoders[sd_index], video,
					s_dv_timings, dv_timings);
	अगर (!ret && vpbe_dev->amp) अणु
		/* Call amplअगरier subdevice */
		ret = v4l2_subdev_call(vpbe_dev->amp, video,
				s_dv_timings, dv_timings);
	पूर्ण
	/* set the lcd controller output क्रम the given mode */
	अगर (!ret) अणु
		काष्ठा osd_state *osd_device = vpbe_dev->osd_device;

		osd_device->ops.set_left_margin(osd_device,
		vpbe_dev->current_timings.left_margin);
		osd_device->ops.set_top_margin(osd_device,
		vpbe_dev->current_timings.upper_margin);
	पूर्ण
	mutex_unlock(&vpbe_dev->lock);

	वापस ret;
पूर्ण

/*
 * vpbe_g_dv_timings - Get the timings in the current encoder
 *
 * Get the timings in the current encoder. Return the status. 0 - success
 * -EINVAL on error
 */
अटल पूर्णांक vpbe_g_dv_timings(काष्ठा vpbe_device *vpbe_dev,
		     काष्ठा v4l2_dv_timings *dv_timings)
अणु
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	पूर्णांक out_index = vpbe_dev->current_out_index;

	अगर (!(cfg->outमाला_दो[out_index].output.capabilities &
		V4L2_OUT_CAP_DV_TIMINGS))
		वापस -ENODATA;

	अगर (vpbe_dev->current_timings.timings_type &
	  VPBE_ENC_DV_TIMINGS) अणु
		*dv_timings = vpbe_dev->current_timings.dv_timings;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * vpbe_क्रमागत_dv_timings - Enumerate the dv timings in the current encoder
 *
 * Get the timings in the current encoder. Return the status. 0 - success
 * -EINVAL on error
 */
अटल पूर्णांक vpbe_क्रमागत_dv_timings(काष्ठा vpbe_device *vpbe_dev,
			 काष्ठा v4l2_क्रमागत_dv_timings *timings)
अणु
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	पूर्णांक out_index = vpbe_dev->current_out_index;
	काष्ठा vpbe_output *output = &cfg->outमाला_दो[out_index];
	पूर्णांक j = 0;
	पूर्णांक i;

	अगर (!(output->output.capabilities & V4L2_OUT_CAP_DV_TIMINGS))
		वापस -ENODATA;

	क्रम (i = 0; i < output->num_modes; i++) अणु
		अगर (output->modes[i].timings_type == VPBE_ENC_DV_TIMINGS) अणु
			अगर (j == timings->index)
				अवरोध;
			j++;
		पूर्ण
	पूर्ण

	अगर (i == output->num_modes)
		वापस -EINVAL;
	timings->timings = output->modes[i].dv_timings;
	वापस 0;
पूर्ण

/*
 * vpbe_s_std - Set the given standard in the encoder
 *
 * Sets the standard अगर supported by the current encoder. Return the status.
 * 0 - success & -EINVAL on error
 */
अटल पूर्णांक vpbe_s_std(काष्ठा vpbe_device *vpbe_dev, v4l2_std_id std_id)
अणु
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	पूर्णांक out_index = vpbe_dev->current_out_index;
	पूर्णांक sd_index = vpbe_dev->current_sd_index;
	पूर्णांक ret;

	अगर (!(cfg->outमाला_दो[out_index].output.capabilities &
		V4L2_OUT_CAP_STD))
		वापस -ENODATA;

	ret = vpbe_get_std_info(vpbe_dev, std_id);
	अगर (ret)
		वापस ret;

	mutex_lock(&vpbe_dev->lock);

	ret = v4l2_subdev_call(vpbe_dev->encoders[sd_index], video,
			       s_std_output, std_id);
	/* set the lcd controller output क्रम the given mode */
	अगर (!ret) अणु
		काष्ठा osd_state *osd_device = vpbe_dev->osd_device;

		osd_device->ops.set_left_margin(osd_device,
		vpbe_dev->current_timings.left_margin);
		osd_device->ops.set_top_margin(osd_device,
		vpbe_dev->current_timings.upper_margin);
	पूर्ण
	mutex_unlock(&vpbe_dev->lock);

	वापस ret;
पूर्ण

/*
 * vpbe_g_std - Get the standard in the current encoder
 *
 * Get the standard in the current encoder. Return the status. 0 - success
 * -EINVAL on error
 */
अटल पूर्णांक vpbe_g_std(काष्ठा vpbe_device *vpbe_dev, v4l2_std_id *std_id)
अणु
	काष्ठा vpbe_enc_mode_info *cur_timings = &vpbe_dev->current_timings;
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	पूर्णांक out_index = vpbe_dev->current_out_index;

	अगर (!(cfg->outमाला_दो[out_index].output.capabilities & V4L2_OUT_CAP_STD))
		वापस -ENODATA;

	अगर (cur_timings->timings_type & VPBE_ENC_STD) अणु
		*std_id = cur_timings->std_id;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * vpbe_set_mode - Set mode in the current encoder using mode info
 *
 * Use the mode string to decide what timings to set in the encoder
 * This is typically useful when fbset command is used to change the current
 * timings by specअगरying a string to indicate the timings.
 */
अटल पूर्णांक vpbe_set_mode(काष्ठा vpbe_device *vpbe_dev,
			 काष्ठा vpbe_enc_mode_info *mode_info)
अणु
	काष्ठा vpbe_enc_mode_info *preset_mode = शून्य;
	काष्ठा vpbe_config *cfg = vpbe_dev->cfg;
	काष्ठा v4l2_dv_timings dv_timings;
	काष्ठा osd_state *osd_device;
	पूर्णांक out_index = vpbe_dev->current_out_index;
	पूर्णांक i;

	अगर (!mode_info || !mode_info->name)
		वापस -EINVAL;

	क्रम (i = 0; i < cfg->outमाला_दो[out_index].num_modes; i++) अणु
		अगर (!म_भेद(mode_info->name,
		     cfg->outमाला_दो[out_index].modes[i].name)) अणु
			preset_mode = &cfg->outमाला_दो[out_index].modes[i];
			/*
			 * it may be one of the 3 timings type. Check and
			 * invoke right API
			 */
			अगर (preset_mode->timings_type & VPBE_ENC_STD)
				वापस vpbe_s_std(vpbe_dev,
						 preset_mode->std_id);
			अगर (preset_mode->timings_type &
						VPBE_ENC_DV_TIMINGS) अणु
				dv_timings =
					preset_mode->dv_timings;
				वापस vpbe_s_dv_timings(vpbe_dev, &dv_timings);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Only custom timing should reach here */
	अगर (!preset_mode)
		वापस -EINVAL;

	mutex_lock(&vpbe_dev->lock);

	osd_device = vpbe_dev->osd_device;
	vpbe_dev->current_timings = *preset_mode;
	osd_device->ops.set_left_margin(osd_device,
		vpbe_dev->current_timings.left_margin);
	osd_device->ops.set_top_margin(osd_device,
		vpbe_dev->current_timings.upper_margin);

	mutex_unlock(&vpbe_dev->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_set_शेष_mode(काष्ठा vpbe_device *vpbe_dev)
अणु
	पूर्णांक ret;

	ret = vpbe_get_std_info_by_name(vpbe_dev, def_mode);
	अगर (ret)
		वापस ret;

	/* set the शेष mode in the encoder */
	वापस vpbe_set_mode(vpbe_dev, &vpbe_dev->current_timings);
पूर्ण

अटल पूर्णांक platक्रमm_device_get(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा vpbe_device *vpbe_dev = data;

	अगर (म_माला(pdev->name, "vpbe-osd"))
		vpbe_dev->osd_device = platक्रमm_get_drvdata(pdev);
	अगर (म_माला(pdev->name, "vpbe-venc"))
		vpbe_dev->venc_device = dev_get_platdata(&pdev->dev);

	वापस 0;
पूर्ण

/**
 * vpbe_initialize() - Initialize the vpbe display controller
 * @dev: Master and slave device ptr
 * @vpbe_dev: vpbe device ptr
 *
 * Master frame buffer device drivers calls this to initialize vpbe
 * display controller. This will then रेजिस्टरs v4l2 device and the sub
 * devices and sets a current encoder sub device क्रम display. v4l2 display
 * device driver is the master and frame buffer display device driver is
 * the slave. Frame buffer display driver checks the initialized during
 * probe and निकास अगर not initialized. Returns status.
 */
अटल पूर्णांक vpbe_initialize(काष्ठा device *dev, काष्ठा vpbe_device *vpbe_dev)
अणु
	काष्ठा encoder_config_info *enc_info;
	काष्ठा amp_config_info *amp_info;
	काष्ठा v4l2_subdev **enc_subdev;
	काष्ठा osd_state *osd_device;
	काष्ठा i2c_adapter *i2c_adap;
	पूर्णांक num_encoders;
	पूर्णांक ret = 0;
	पूर्णांक err;
	पूर्णांक i;

	/*
	 * v4l2 abd FBDev frame buffer devices will get the vpbe_dev poपूर्णांकer
	 * from the platक्रमm device by iteration of platक्रमm drivers and
	 * matching with device name
	 */
	अगर (!vpbe_dev || !dev) अणु
		prपूर्णांकk(KERN_ERR "Null device pointers.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (vpbe_dev->initialized)
		वापस 0;

	mutex_lock(&vpbe_dev->lock);

	अगर (म_भेद(vpbe_dev->cfg->module_name, "dm644x-vpbe-display") != 0) अणु
		/* We have dac घड़ी available क्रम platक्रमm */
		vpbe_dev->dac_clk = clk_get(vpbe_dev->pdev, "vpss_dac");
		अगर (IS_ERR(vpbe_dev->dac_clk)) अणु
			ret =  PTR_ERR(vpbe_dev->dac_clk);
			जाओ fail_mutex_unlock;
		पूर्ण
		अगर (clk_prepare_enable(vpbe_dev->dac_clk)) अणु
			ret =  -ENODEV;
			clk_put(vpbe_dev->dac_clk);
			जाओ fail_mutex_unlock;
		पूर्ण
	पूर्ण

	/* first enable vpss घड़ीs */
	vpss_enable_घड़ी(VPSS_VPBE_CLOCK, 1);

	/* First रेजिस्टर a v4l2 device */
	ret = v4l2_device_रेजिस्टर(dev, &vpbe_dev->v4l2_dev);
	अगर (ret) अणु
		v4l2_err(dev->driver,
			"Unable to register v4l2 device.\n");
		जाओ fail_clk_put;
	पूर्ण
	v4l2_info(&vpbe_dev->v4l2_dev, "vpbe v4l2 device registered\n");

	err = bus_क्रम_each_dev(&platक्रमm_bus_type, शून्य, vpbe_dev,
			       platक्रमm_device_get);
	अगर (err < 0) अणु
		ret = err;
		जाओ fail_dev_unरेजिस्टर;
	पूर्ण

	vpbe_dev->venc = venc_sub_dev_init(&vpbe_dev->v4l2_dev,
					   vpbe_dev->cfg->venc.module_name);
	/* रेजिस्टर venc sub device */
	अगर (!vpbe_dev->venc) अणु
		v4l2_err(&vpbe_dev->v4l2_dev,
			"vpbe unable to init venc sub device\n");
		ret = -ENODEV;
		जाओ fail_dev_unरेजिस्टर;
	पूर्ण
	/* initialize osd device */
	osd_device = vpbe_dev->osd_device;
	अगर (osd_device->ops.initialize) अणु
		err = osd_device->ops.initialize(osd_device);
		अगर (err) अणु
			v4l2_err(&vpbe_dev->v4l2_dev,
				 "unable to initialize the OSD device");
			ret = -ENOMEM;
			जाओ fail_dev_unरेजिस्टर;
		पूर्ण
	पूर्ण

	/*
	 * Register any बाह्यal encoders that are configured. At index 0 we
	 * store venc sd index.
	 */
	num_encoders = vpbe_dev->cfg->num_ext_encoders + 1;
	vpbe_dev->encoders = kदो_स्मृति_array(num_encoders,
					   माप(*vpbe_dev->encoders),
					   GFP_KERNEL);
	अगर (!vpbe_dev->encoders) अणु
		ret = -ENOMEM;
		जाओ fail_dev_unरेजिस्टर;
	पूर्ण

	i2c_adap = i2c_get_adapter(vpbe_dev->cfg->i2c_adapter_id);
	क्रम (i = 0; i < (vpbe_dev->cfg->num_ext_encoders + 1); i++) अणु
		अगर (i == 0) अणु
			/* venc is at index 0 */
			enc_subdev = &vpbe_dev->encoders[i];
			*enc_subdev = vpbe_dev->venc;
			जारी;
		पूर्ण
		enc_info = &vpbe_dev->cfg->ext_encoders[i];
		अगर (enc_info->is_i2c) अणु
			enc_subdev = &vpbe_dev->encoders[i];
			*enc_subdev = v4l2_i2c_new_subdev_board(
						&vpbe_dev->v4l2_dev, i2c_adap,
						&enc_info->board_info, शून्य);
			अगर (*enc_subdev)
				v4l2_info(&vpbe_dev->v4l2_dev,
					  "v4l2 sub device %s registered\n",
					  enc_info->module_name);
			अन्यथा अणु
				v4l2_err(&vpbe_dev->v4l2_dev, "encoder %s failed to register",
					 enc_info->module_name);
				ret = -ENODEV;
				जाओ fail_kमुक्त_encoders;
			पूर्ण
		पूर्ण अन्यथा
			v4l2_warn(&vpbe_dev->v4l2_dev, "non-i2c encoders currently not supported");
	पूर्ण
	/* Add amplअगरier subdevice क्रम dm365 */
	अगर ((म_भेद(vpbe_dev->cfg->module_name, "dm365-vpbe-display") == 0) &&
	   vpbe_dev->cfg->amp) अणु
		amp_info = vpbe_dev->cfg->amp;
		अगर (amp_info->is_i2c) अणु
			vpbe_dev->amp = v4l2_i2c_new_subdev_board(
			&vpbe_dev->v4l2_dev, i2c_adap,
			&amp_info->board_info, शून्य);
			अगर (!vpbe_dev->amp) अणु
				v4l2_err(&vpbe_dev->v4l2_dev,
					 "amplifier %s failed to register",
					 amp_info->module_name);
				ret = -ENODEV;
				जाओ fail_kमुक्त_encoders;
			पूर्ण
			v4l2_info(&vpbe_dev->v4l2_dev,
					  "v4l2 sub device %s registered\n",
					  amp_info->module_name);
		पूर्ण अन्यथा अणु
			    vpbe_dev->amp = शून्य;
			    v4l2_warn(&vpbe_dev->v4l2_dev, "non-i2c amplifiers currently not supported");
		पूर्ण
	पूर्ण अन्यथा अणु
	    vpbe_dev->amp = शून्य;
	पूर्ण

	/* set the current encoder and output to that of venc by शेष */
	vpbe_dev->current_sd_index = 0;
	vpbe_dev->current_out_index = 0;

	mutex_unlock(&vpbe_dev->lock);

	prपूर्णांकk(KERN_NOTICE "Setting default output to %s\n", def_output);
	ret = vpbe_set_शेष_output(vpbe_dev);
	अगर (ret) अणु
		v4l2_err(&vpbe_dev->v4l2_dev, "Failed to set default output %s",
			 def_output);
		जाओ fail_kमुक्त_amp;
	पूर्ण

	prपूर्णांकk(KERN_NOTICE "Setting default mode to %s\n", def_mode);
	ret = vpbe_set_शेष_mode(vpbe_dev);
	अगर (ret) अणु
		v4l2_err(&vpbe_dev->v4l2_dev, "Failed to set default mode %s",
			 def_mode);
		जाओ fail_kमुक्त_amp;
	पूर्ण
	vpbe_dev->initialized = 1;
	/* TBD handling of bootargs क्रम शेष output and mode */
	वापस 0;

fail_kमुक्त_amp:
	mutex_lock(&vpbe_dev->lock);
	kमुक्त(vpbe_dev->amp);
fail_kमुक्त_encoders:
	kमुक्त(vpbe_dev->encoders);
fail_dev_unरेजिस्टर:
	v4l2_device_unरेजिस्टर(&vpbe_dev->v4l2_dev);
fail_clk_put:
	अगर (म_भेद(vpbe_dev->cfg->module_name, "dm644x-vpbe-display") != 0) अणु
		clk_disable_unprepare(vpbe_dev->dac_clk);
		clk_put(vpbe_dev->dac_clk);
	पूर्ण
fail_mutex_unlock:
	mutex_unlock(&vpbe_dev->lock);
	वापस ret;
पूर्ण

/**
 * vpbe_deinitialize() - de-initialize the vpbe display controller
 * @dev: Master and slave device ptr
 * @vpbe_dev: vpbe device ptr
 *
 * vpbe_master and slave frame buffer devices calls this to de-initialize
 * the display controller. It is called when master and slave device
 * driver modules are हटाओd and no दीर्घer requires the display controller.
 */
अटल व्योम vpbe_deinitialize(काष्ठा device *dev, काष्ठा vpbe_device *vpbe_dev)
अणु
	v4l2_device_unरेजिस्टर(&vpbe_dev->v4l2_dev);
	अगर (म_भेद(vpbe_dev->cfg->module_name, "dm644x-vpbe-display") != 0) अणु
		clk_disable_unprepare(vpbe_dev->dac_clk);
		clk_put(vpbe_dev->dac_clk);
	पूर्ण

	kमुक्त(vpbe_dev->amp);
	kमुक्त(vpbe_dev->encoders);
	vpbe_dev->initialized = 0;
	/* disable vpss घड़ीs */
	vpss_enable_घड़ी(VPSS_VPBE_CLOCK, 0);
पूर्ण

अटल स्थिर काष्ठा vpbe_device_ops vpbe_dev_ops = अणु
	.क्रमागत_outमाला_दो = vpbe_क्रमागत_outमाला_दो,
	.set_output = vpbe_set_output,
	.get_output = vpbe_get_output,
	.s_dv_timings = vpbe_s_dv_timings,
	.g_dv_timings = vpbe_g_dv_timings,
	.क्रमागत_dv_timings = vpbe_क्रमागत_dv_timings,
	.s_std = vpbe_s_std,
	.g_std = vpbe_g_std,
	.initialize = vpbe_initialize,
	.deinitialize = vpbe_deinitialize,
	.get_mode_info = vpbe_get_current_mode_info,
	.set_mode = vpbe_set_mode,
पूर्ण;

अटल पूर्णांक vpbe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vpbe_device *vpbe_dev;
	काष्ठा vpbe_config *cfg;

	अगर (!pdev->dev.platक्रमm_data) अणु
		v4l2_err(pdev->dev.driver, "No platform data\n");
		वापस -ENODEV;
	पूर्ण
	cfg = pdev->dev.platक्रमm_data;

	अगर (!cfg->module_name[0] ||
	    !cfg->osd.module_name[0] ||
	    !cfg->venc.module_name[0]) अणु
		v4l2_err(pdev->dev.driver, "vpbe display module names not defined\n");
		वापस -EINVAL;
	पूर्ण

	vpbe_dev = kzalloc(माप(*vpbe_dev), GFP_KERNEL);
	अगर (!vpbe_dev)
		वापस -ENOMEM;

	vpbe_dev->cfg = cfg;
	vpbe_dev->ops = vpbe_dev_ops;
	vpbe_dev->pdev = &pdev->dev;

	अगर (cfg->outमाला_दो->num_modes > 0)
		vpbe_dev->current_timings = vpbe_dev->cfg->outमाला_दो[0].modes[0];
	अन्यथा अणु
		kमुक्त(vpbe_dev);
		वापस -ENODEV;
	पूर्ण

	/* set the driver data in platक्रमm device */
	platक्रमm_set_drvdata(pdev, vpbe_dev);
	mutex_init(&vpbe_dev->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vpbe_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा vpbe_device *vpbe_dev = platक्रमm_get_drvdata(device);

	kमुक्त(vpbe_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver vpbe_driver = अणु
	.driver	= अणु
		.name	= "vpbe_controller",
	पूर्ण,
	.probe = vpbe_probe,
	.हटाओ = vpbe_हटाओ,
पूर्ण;

module_platक्रमm_driver(vpbe_driver);
