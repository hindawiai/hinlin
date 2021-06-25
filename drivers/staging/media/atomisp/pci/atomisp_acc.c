<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Clovertrail PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2012 Intel Corporation. All Rights Reserved.
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

/*
 * This file implements loadable acceleration firmware API,
 * including ioctls to map and unmap acceleration parameters and buffers.
 */

#समावेश <linux/init.h>
#समावेश <media/v4l2-event.h>

#समावेश "hmm.h"

#समावेश "atomisp_acc.h"
#समावेश "atomisp_internal.h"
#समावेश "atomisp_compat.h"
#समावेश "atomisp_cmd.h"

#समावेश "ia_css.h"

अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक flag;
	क्रमागत ia_css_pipe_id pipe_id;
पूर्ण acc_flag_to_pipe[] = अणु
	अणु ATOMISP_ACC_FW_LOAD_FL_PREVIEW, IA_CSS_PIPE_ID_PREVIEW पूर्ण,
	अणु ATOMISP_ACC_FW_LOAD_FL_COPY, IA_CSS_PIPE_ID_COPY पूर्ण,
	अणु ATOMISP_ACC_FW_LOAD_FL_VIDEO, IA_CSS_PIPE_ID_VIDEO पूर्ण,
	अणु ATOMISP_ACC_FW_LOAD_FL_CAPTURE, IA_CSS_PIPE_ID_CAPTURE पूर्ण,
	अणु ATOMISP_ACC_FW_LOAD_FL_ACC, IA_CSS_PIPE_ID_ACC पूर्ण
पूर्ण;

/*
 * Allocate काष्ठा atomisp_acc_fw aदीर्घ with space क्रम firmware.
 * The वापसed काष्ठा atomisp_acc_fw is cleared (firmware region is not).
 */
अटल काष्ठा atomisp_acc_fw *acc_alloc_fw(अचिन्हित पूर्णांक fw_size)
अणु
	काष्ठा atomisp_acc_fw *acc_fw;

	acc_fw = kzalloc(माप(*acc_fw), GFP_KERNEL);
	अगर (!acc_fw)
		वापस शून्य;

	acc_fw->fw = vदो_स्मृति(fw_size);
	अगर (!acc_fw->fw) अणु
		kमुक्त(acc_fw);
		वापस शून्य;
	पूर्ण

	वापस acc_fw;
पूर्ण

अटल व्योम acc_मुक्त_fw(काष्ठा atomisp_acc_fw *acc_fw)
अणु
	vमुक्त(acc_fw->fw);
	kमुक्त(acc_fw);
पूर्ण

अटल काष्ठा atomisp_acc_fw *
acc_get_fw(काष्ठा atomisp_sub_device *asd, अचिन्हित पूर्णांक handle)
अणु
	काष्ठा atomisp_acc_fw *acc_fw;

	list_क्रम_each_entry(acc_fw, &asd->acc.fw, list)
	अगर (acc_fw->handle == handle)
		वापस acc_fw;

	वापस शून्य;
पूर्ण

अटल काष्ठा atomisp_map *acc_get_map(काष्ठा atomisp_sub_device *asd,
				       अचिन्हित दीर्घ css_ptr, माप_प्रकार length)
अणु
	काष्ठा atomisp_map *atomisp_map;

	list_क्रम_each_entry(atomisp_map, &asd->acc.memory_maps, list) अणु
		अगर (atomisp_map->ptr == css_ptr &&
		    atomisp_map->length == length)
			वापस atomisp_map;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक acc_stop_acceleration(काष्ठा atomisp_sub_device *asd)
अणु
	पूर्णांक ret;

	ret = atomisp_css_stop_acc_pipe(asd);
	atomisp_css_destroy_acc_pipe(asd);

	वापस ret;
पूर्ण

व्योम atomisp_acc_cleanup(काष्ठा atomisp_device *isp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < isp->num_of_streams; i++)
		ida_destroy(&isp->asd[i].acc.ida);
पूर्ण

व्योम atomisp_acc_release(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_acc_fw *acc_fw, *ta;
	काष्ठा atomisp_map *atomisp_map, *पंचांग;

	/* Stop acceleration अगर alपढ़ोy running */
	अगर (asd->acc.pipeline)
		acc_stop_acceleration(asd);

	/* Unload all loaded acceleration binaries */
	list_क्रम_each_entry_safe(acc_fw, ta, &asd->acc.fw, list) अणु
		list_del(&acc_fw->list);
		ida_मुक्त(&asd->acc.ida, acc_fw->handle);
		acc_मुक्त_fw(acc_fw);
	पूर्ण

	/* Free all mapped memory blocks */
	list_क्रम_each_entry_safe(atomisp_map, पंचांग, &asd->acc.memory_maps, list) अणु
		list_del(&atomisp_map->list);
		hmm_मुक्त(atomisp_map->ptr);
		kमुक्त(atomisp_map);
	पूर्ण
पूर्ण

पूर्णांक atomisp_acc_load_to_pipe(काष्ठा atomisp_sub_device *asd,
			     काष्ठा atomisp_acc_fw_load_to_pipe *user_fw)
अणु
	अटल स्थिर अचिन्हित पूर्णांक pipeline_flags =
	    ATOMISP_ACC_FW_LOAD_FL_PREVIEW | ATOMISP_ACC_FW_LOAD_FL_COPY |
	    ATOMISP_ACC_FW_LOAD_FL_VIDEO |
	    ATOMISP_ACC_FW_LOAD_FL_CAPTURE | ATOMISP_ACC_FW_LOAD_FL_ACC;

	काष्ठा atomisp_acc_fw *acc_fw;
	पूर्णांक handle;

	अगर (!user_fw->data || user_fw->size < माप(*acc_fw->fw))
		वापस -EINVAL;

	/* Binary has to be enabled at least क्रम one pipeline */
	अगर (!(user_fw->flags & pipeline_flags))
		वापस -EINVAL;

	/* We करो not support other flags yet */
	अगर (user_fw->flags & ~pipeline_flags)
		वापस -EINVAL;

	अगर (user_fw->type < ATOMISP_ACC_FW_LOAD_TYPE_OUTPUT ||
	    user_fw->type > ATOMISP_ACC_FW_LOAD_TYPE_STANDALONE)
		वापस -EINVAL;

	अगर (asd->acc.pipeline || asd->acc.extension_mode)
		वापस -EBUSY;

	acc_fw = acc_alloc_fw(user_fw->size);
	अगर (!acc_fw)
		वापस -ENOMEM;

	अगर (copy_from_user(acc_fw->fw, user_fw->data, user_fw->size)) अणु
		acc_मुक्त_fw(acc_fw);
		वापस -EFAULT;
	पूर्ण

	handle = ida_alloc(&asd->acc.ida, GFP_KERNEL);
	अगर (handle < 0) अणु
		acc_मुक्त_fw(acc_fw);
		वापस -ENOSPC;
	पूर्ण

	user_fw->fw_handle = handle;
	acc_fw->handle = handle;
	acc_fw->flags = user_fw->flags;
	acc_fw->type = user_fw->type;
	acc_fw->fw->handle = handle;

	/*
	 * correct isp firmware type in order ISP firmware can be appended
	 * to correct pipe properly
	 */
	अगर (acc_fw->fw->type == ia_css_isp_firmware) अणु
		अटल स्थिर पूर्णांक type_to_css[] = अणु
			[ATOMISP_ACC_FW_LOAD_TYPE_OUTPUT] =
			IA_CSS_ACC_OUTPUT,
			[ATOMISP_ACC_FW_LOAD_TYPE_VIEWFINDER] =
			IA_CSS_ACC_VIEWFINDER,
			[ATOMISP_ACC_FW_LOAD_TYPE_STANDALONE] =
			IA_CSS_ACC_STANDALONE,
		पूर्ण;
		acc_fw->fw->info.isp.type = type_to_css[acc_fw->type];
	पूर्ण

	list_add_tail(&acc_fw->list, &asd->acc.fw);
	वापस 0;
पूर्ण

पूर्णांक atomisp_acc_load(काष्ठा atomisp_sub_device *asd,
		     काष्ठा atomisp_acc_fw_load *user_fw)
अणु
	काष्ठा atomisp_acc_fw_load_to_pipe ltp = अणु0पूर्ण;
	पूर्णांक r;

	ltp.flags = ATOMISP_ACC_FW_LOAD_FL_ACC;
	ltp.type = ATOMISP_ACC_FW_LOAD_TYPE_STANDALONE;
	ltp.size = user_fw->size;
	ltp.data = user_fw->data;
	r = atomisp_acc_load_to_pipe(asd, &ltp);
	user_fw->fw_handle = ltp.fw_handle;
	वापस r;
पूर्ण

पूर्णांक atomisp_acc_unload(काष्ठा atomisp_sub_device *asd, अचिन्हित पूर्णांक *handle)
अणु
	काष्ठा atomisp_acc_fw *acc_fw;

	अगर (asd->acc.pipeline || asd->acc.extension_mode)
		वापस -EBUSY;

	acc_fw = acc_get_fw(asd, *handle);
	अगर (!acc_fw)
		वापस -EINVAL;

	list_del(&acc_fw->list);
	ida_मुक्त(&asd->acc.ida, acc_fw->handle);
	acc_मुक्त_fw(acc_fw);

	वापस 0;
पूर्ण

पूर्णांक atomisp_acc_start(काष्ठा atomisp_sub_device *asd, अचिन्हित पूर्णांक *handle)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	काष्ठा atomisp_acc_fw *acc_fw;
	पूर्णांक ret;
	अचिन्हित पूर्णांक nbin;

	अगर (asd->acc.pipeline || asd->acc.extension_mode)
		वापस -EBUSY;

	/* Invalidate caches. FIXME: should flush only necessary buffers */
	wbinvd();

	ret = atomisp_css_create_acc_pipe(asd);
	अगर (ret)
		वापस ret;

	nbin = 0;
	list_क्रम_each_entry(acc_fw, &asd->acc.fw, list) अणु
		अगर (*handle != 0 && *handle != acc_fw->handle)
			जारी;

		अगर (acc_fw->type != ATOMISP_ACC_FW_LOAD_TYPE_STANDALONE)
			जारी;

		/* Add the binary पूर्णांकo the pipeline */
		ret = atomisp_css_load_acc_binary(asd, acc_fw->fw, nbin);
		अगर (ret < 0) अणु
			dev_err(isp->dev, "acc_load_binary failed\n");
			जाओ err_stage;
		पूर्ण

		ret = atomisp_css_set_acc_parameters(acc_fw);
		अगर (ret < 0) अणु
			dev_err(isp->dev, "acc_set_parameters failed\n");
			जाओ err_stage;
		पूर्ण
		nbin++;
	पूर्ण
	अगर (nbin < 1) अणु
		/* Refuse creating pipelines with no binaries */
		dev_err(isp->dev, "%s: no acc binary available\n", __func__);
		ret = -EINVAL;
		जाओ err_stage;
	पूर्ण

	ret = atomisp_css_start_acc_pipe(asd);
	अगर (ret) अणु
		dev_err(isp->dev, "%s: atomisp_acc_start_acc_pipe failed\n",
			__func__);
		जाओ err_stage;
	पूर्ण

	वापस 0;

err_stage:
	atomisp_css_destroy_acc_pipe(asd);
	वापस ret;
पूर्ण

पूर्णांक atomisp_acc_रुको(काष्ठा atomisp_sub_device *asd, अचिन्हित पूर्णांक *handle)
अणु
	काष्ठा atomisp_device *isp = asd->isp;
	पूर्णांक ret;

	अगर (!asd->acc.pipeline)
		वापस -ENOENT;

	अगर (*handle && !acc_get_fw(asd, *handle))
		वापस -EINVAL;

	ret = atomisp_css_रुको_acc_finish(asd);
	अगर (acc_stop_acceleration(asd) == -EIO) अणु
		atomisp_reset(isp);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

व्योम atomisp_acc_करोne(काष्ठा atomisp_sub_device *asd, अचिन्हित पूर्णांक handle)
अणु
	काष्ठा v4l2_event event = अणु 0 पूर्ण;

	event.type = V4L2_EVENT_ATOMISP_ACC_COMPLETE;
	event.u.frame_sync.frame_sequence = atomic_पढ़ो(&asd->sequence);
	event.id = handle;

	v4l2_event_queue(asd->subdev.devnode, &event);
पूर्ण

पूर्णांक atomisp_acc_map(काष्ठा atomisp_sub_device *asd, काष्ठा atomisp_acc_map *map)
अणु
	काष्ठा atomisp_map *atomisp_map;
	ia_css_ptr cssptr;
	पूर्णांक pgnr;

	अगर (map->css_ptr)
		वापस -EINVAL;

	अगर (asd->acc.pipeline)
		वापस -EBUSY;

	अगर (map->user_ptr) अणु
		/* Buffer to map must be page-aligned */
		अगर ((अचिन्हित दीर्घ)map->user_ptr & ~PAGE_MASK) अणु
			dev_err(asd->isp->dev,
				"%s: mapped buffer address %p is not page aligned\n",
				__func__, map->user_ptr);
			वापस -EINVAL;
		पूर्ण

		pgnr = DIV_ROUND_UP(map->length, PAGE_SIZE);
		अगर (pgnr < ((PAGE_ALIGN(map->length)) >> PAGE_SHIFT)) अणु
			dev_err(asd->isp->dev,
				"user space memory size is less than the expected size..\n");
			वापस -ENOMEM;
		पूर्ण अन्यथा अगर (pgnr > ((PAGE_ALIGN(map->length)) >> PAGE_SHIFT)) अणु
			dev_err(asd->isp->dev,
				"user space memory size is large than the expected size..\n");
			वापस -ENOMEM;
		पूर्ण

		cssptr = hmm_alloc(map->length, HMM_BO_USER, 0, map->user_ptr,
				   map->flags & ATOMISP_MAP_FLAG_CACHED);

	पूर्ण अन्यथा अणु
		/* Allocate निजी buffer. */
		cssptr = hmm_alloc(map->length, HMM_BO_PRIVATE, 0, शून्य,
				   map->flags & ATOMISP_MAP_FLAG_CACHED);
	पूर्ण

	अगर (!cssptr)
		वापस -ENOMEM;

	atomisp_map = kदो_स्मृति(माप(*atomisp_map), GFP_KERNEL);
	अगर (!atomisp_map) अणु
		hmm_मुक्त(cssptr);
		वापस -ENOMEM;
	पूर्ण
	atomisp_map->ptr = cssptr;
	atomisp_map->length = map->length;
	list_add(&atomisp_map->list, &asd->acc.memory_maps);

	dev_dbg(asd->isp->dev, "%s: userptr %p, css_address 0x%x, size %d\n",
		__func__, map->user_ptr, cssptr, map->length);
	map->css_ptr = cssptr;
	वापस 0;
पूर्ण

पूर्णांक atomisp_acc_unmap(काष्ठा atomisp_sub_device *asd,
		      काष्ठा atomisp_acc_map *map)
अणु
	काष्ठा atomisp_map *atomisp_map;

	अगर (asd->acc.pipeline)
		वापस -EBUSY;

	atomisp_map = acc_get_map(asd, map->css_ptr, map->length);
	अगर (!atomisp_map)
		वापस -EINVAL;

	list_del(&atomisp_map->list);
	hmm_मुक्त(atomisp_map->ptr);
	kमुक्त(atomisp_map);
	वापस 0;
पूर्ण

पूर्णांक atomisp_acc_s_mapped_arg(काष्ठा atomisp_sub_device *asd,
			     काष्ठा atomisp_acc_s_mapped_arg *arg)
अणु
	काष्ठा atomisp_acc_fw *acc_fw;

	अगर (arg->memory >= ATOMISP_ACC_NR_MEMORY)
		वापस -EINVAL;

	अगर (asd->acc.pipeline)
		वापस -EBUSY;

	acc_fw = acc_get_fw(asd, arg->fw_handle);
	अगर (!acc_fw)
		वापस -EINVAL;

	अगर (arg->css_ptr != 0 || arg->length != 0) अणु
		/* Unless the parameter is cleared, check that it exists */
		अगर (!acc_get_map(asd, arg->css_ptr, arg->length))
			वापस -EINVAL;
	पूर्ण

	acc_fw->args[arg->memory].length = arg->length;
	acc_fw->args[arg->memory].css_ptr = arg->css_ptr;

	dev_dbg(asd->isp->dev, "%s: mem %d, address %p, size %ld\n",
		__func__, arg->memory, (व्योम *)arg->css_ptr,
		(अचिन्हित दीर्घ)arg->length);
	वापस 0;
पूर्ण

/*
 * Appends the loaded acceleration binary extensions to the
 * current ISP mode. Must be called just beक्रमe sh_css_start().
 */
पूर्णांक atomisp_acc_load_extensions(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_acc_fw *acc_fw;
	bool ext_loaded = false;
	bool continuous = asd->continuous_mode->val &&
			  asd->run_mode->val == ATOMISP_RUN_MODE_PREVIEW;
	पूर्णांक ret = 0, i = -1;
	काष्ठा atomisp_device *isp = asd->isp;

	अगर (asd->acc.pipeline || asd->acc.extension_mode)
		वापस -EBUSY;

	/* Invalidate caches. FIXME: should flush only necessary buffers */
	wbinvd();

	list_क्रम_each_entry(acc_fw, &asd->acc.fw, list) अणु
		अगर (acc_fw->type != ATOMISP_ACC_FW_LOAD_TYPE_OUTPUT &&
		    acc_fw->type != ATOMISP_ACC_FW_LOAD_TYPE_VIEWFINDER)
			जारी;

		क्रम (i = 0; i < ARRAY_SIZE(acc_flag_to_pipe); i++) अणु
			/* QoS (ACC pipe) acceleration stages are currently
			 * allowed only in continuous mode. Skip them क्रम
			 * all other modes. */
			अगर (!continuous &&
			    acc_flag_to_pipe[i].flag ==
			    ATOMISP_ACC_FW_LOAD_FL_ACC)
				जारी;

			अगर (acc_fw->flags & acc_flag_to_pipe[i].flag) अणु
				ret = atomisp_css_load_acc_extension(asd,
								     acc_fw->fw,
								     acc_flag_to_pipe[i].pipe_id,
								     acc_fw->type);
				अगर (ret)
					जाओ error;

				ext_loaded = true;
			पूर्ण
		पूर्ण

		ret = atomisp_css_set_acc_parameters(acc_fw);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	अगर (!ext_loaded)
		वापस ret;

	ret = atomisp_css_update_stream(asd);
	अगर (ret) अणु
		dev_err(isp->dev, "%s: update stream failed.\n", __func__);
		जाओ error;
	पूर्ण

	asd->acc.extension_mode = true;
	वापस 0;

error:
	जबतक (--i >= 0) अणु
		अगर (acc_fw->flags & acc_flag_to_pipe[i].flag) अणु
			atomisp_css_unload_acc_extension(asd, acc_fw->fw,
							 acc_flag_to_pipe[i].pipe_id);
		पूर्ण
	पूर्ण

	list_क्रम_each_entry_जारी_reverse(acc_fw, &asd->acc.fw, list) अणु
		अगर (acc_fw->type != ATOMISP_ACC_FW_LOAD_TYPE_OUTPUT &&
		    acc_fw->type != ATOMISP_ACC_FW_LOAD_TYPE_VIEWFINDER)
			जारी;

		क्रम (i = ARRAY_SIZE(acc_flag_to_pipe) - 1; i >= 0; i--) अणु
			अगर (!continuous &&
			    acc_flag_to_pipe[i].flag ==
			    ATOMISP_ACC_FW_LOAD_FL_ACC)
				जारी;
			अगर (acc_fw->flags & acc_flag_to_pipe[i].flag) अणु
				atomisp_css_unload_acc_extension(asd,
								 acc_fw->fw,
								 acc_flag_to_pipe[i].pipe_id);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

व्योम atomisp_acc_unload_extensions(काष्ठा atomisp_sub_device *asd)
अणु
	काष्ठा atomisp_acc_fw *acc_fw;
	पूर्णांक i;

	अगर (!asd->acc.extension_mode)
		वापस;

	list_क्रम_each_entry_reverse(acc_fw, &asd->acc.fw, list) अणु
		अगर (acc_fw->type != ATOMISP_ACC_FW_LOAD_TYPE_OUTPUT &&
		    acc_fw->type != ATOMISP_ACC_FW_LOAD_TYPE_VIEWFINDER)
			जारी;

		क्रम (i = ARRAY_SIZE(acc_flag_to_pipe) - 1; i >= 0; i--) अणु
			अगर (acc_fw->flags & acc_flag_to_pipe[i].flag) अणु
				atomisp_css_unload_acc_extension(asd,
								 acc_fw->fw,
								 acc_flag_to_pipe[i].pipe_id);
			पूर्ण
		पूर्ण
	पूर्ण

	asd->acc.extension_mode = false;
पूर्ण

पूर्णांक atomisp_acc_set_state(काष्ठा atomisp_sub_device *asd,
			  काष्ठा atomisp_acc_state *arg)
अणु
	काष्ठा atomisp_acc_fw *acc_fw;
	bool enable = (arg->flags & ATOMISP_STATE_FLAG_ENABLE) != 0;
	काष्ठा ia_css_pipe *pipe;
	पूर्णांक r;
	पूर्णांक i;

	अगर (!asd->acc.extension_mode)
		वापस -EBUSY;

	अगर (arg->flags & ~ATOMISP_STATE_FLAG_ENABLE)
		वापस -EINVAL;

	acc_fw = acc_get_fw(asd, arg->fw_handle);
	अगर (!acc_fw)
		वापस -EINVAL;

	अगर (enable)
		wbinvd();

	क्रम (i = 0; i < ARRAY_SIZE(acc_flag_to_pipe); i++) अणु
		अगर (acc_fw->flags & acc_flag_to_pipe[i].flag) अणु
			pipe = asd->stream_env[ATOMISP_INPUT_STREAM_GENERAL].
			       pipes[acc_flag_to_pipe[i].pipe_id];
			r = ia_css_pipe_set_qos_ext_state(pipe, acc_fw->handle,
							  enable);
			अगर (r)
				वापस -EBADRQC;
		पूर्ण
	पूर्ण

	अगर (enable)
		acc_fw->flags |= ATOMISP_ACC_FW_LOAD_FL_ENABLE;
	अन्यथा
		acc_fw->flags &= ~ATOMISP_ACC_FW_LOAD_FL_ENABLE;

	वापस 0;
पूर्ण

पूर्णांक atomisp_acc_get_state(काष्ठा atomisp_sub_device *asd,
			  काष्ठा atomisp_acc_state *arg)
अणु
	काष्ठा atomisp_acc_fw *acc_fw;

	अगर (!asd->acc.extension_mode)
		वापस -EBUSY;

	acc_fw = acc_get_fw(asd, arg->fw_handle);
	अगर (!acc_fw)
		वापस -EINVAL;

	arg->flags = acc_fw->flags;

	वापस 0;
पूर्ण
