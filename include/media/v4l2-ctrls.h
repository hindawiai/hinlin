<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  V4L2 controls support header.
 *
 *  Copyright (C) 2010  Hans Verkuil <hverkuil@xs4all.nl>
 */

#अगर_अघोषित _V4L2_CTRLS_H
#घोषणा _V4L2_CTRLS_H

#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/videodev2.h>
#समावेश <media/media-request.h>

/*
 * Include the stateless codec compound control definitions.
 * This will move to the खुला headers once this API is fully stable.
 */
#समावेश <media/mpeg2-ctrls.h>
#समावेश <media/hevc-ctrls.h>

/* क्रमward references */
काष्ठा file;
काष्ठा poll_table_काष्ठा;
काष्ठा v4l2_ctrl;
काष्ठा v4l2_ctrl_handler;
काष्ठा v4l2_ctrl_helper;
काष्ठा v4l2_fh;
काष्ठा v4l2_fwnode_device_properties;
काष्ठा v4l2_subdev;
काष्ठा v4l2_subscribed_event;
काष्ठा video_device;

/**
 * जोड़ v4l2_ctrl_ptr - A poपूर्णांकer to a control value.
 * @p_s32:			Poपूर्णांकer to a 32-bit चिन्हित value.
 * @p_s64:			Poपूर्णांकer to a 64-bit चिन्हित value.
 * @p_u8:			Poपूर्णांकer to a 8-bit अचिन्हित value.
 * @p_u16:			Poपूर्णांकer to a 16-bit अचिन्हित value.
 * @p_u32:			Poपूर्णांकer to a 32-bit अचिन्हित value.
 * @p_अक्षर:			Poपूर्णांकer to a string.
 * @p_mpeg2_slice_params:	Poपूर्णांकer to a MPEG2 slice parameters काष्ठाure.
 * @p_mpeg2_quantization:	Poपूर्णांकer to a MPEG2 quantization data काष्ठाure.
 * @p_fwht_params:		Poपूर्णांकer to a FWHT stateless parameters काष्ठाure.
 * @p_h264_sps:			Poपूर्णांकer to a काष्ठा v4l2_ctrl_h264_sps.
 * @p_h264_pps:			Poपूर्णांकer to a काष्ठा v4l2_ctrl_h264_pps.
 * @p_h264_scaling_matrix:	Poपूर्णांकer to a काष्ठा v4l2_ctrl_h264_scaling_matrix.
 * @p_h264_slice_params:	Poपूर्णांकer to a काष्ठा v4l2_ctrl_h264_slice_params.
 * @p_h264_decode_params:	Poपूर्णांकer to a काष्ठा v4l2_ctrl_h264_decode_params.
 * @p_h264_pred_weights:	Poपूर्णांकer to a काष्ठा v4l2_ctrl_h264_pred_weights.
 * @p_vp8_frame:		Poपूर्णांकer to a VP8 frame params काष्ठाure.
 * @p_hevc_sps:			Poपूर्णांकer to an HEVC sequence parameter set काष्ठाure.
 * @p_hevc_pps:			Poपूर्णांकer to an HEVC picture parameter set काष्ठाure.
 * @p_hevc_slice_params:	Poपूर्णांकer to an HEVC slice parameters काष्ठाure.
 * @p_hdr10_cll:		Poपूर्णांकer to an HDR10 Content Light Level काष्ठाure.
 * @p_hdr10_mastering:		Poपूर्णांकer to an HDR10 Mastering Display काष्ठाure.
 * @p_area:			Poपूर्णांकer to an area.
 * @p:				Poपूर्णांकer to a compound value.
 * @p_स्थिर:			Poपूर्णांकer to a स्थिरant compound value.
 */
जोड़ v4l2_ctrl_ptr अणु
	s32 *p_s32;
	s64 *p_s64;
	u8 *p_u8;
	u16 *p_u16;
	u32 *p_u32;
	अक्षर *p_अक्षर;
	काष्ठा v4l2_ctrl_mpeg2_slice_params *p_mpeg2_slice_params;
	काष्ठा v4l2_ctrl_mpeg2_quantization *p_mpeg2_quantization;
	काष्ठा v4l2_ctrl_fwht_params *p_fwht_params;
	काष्ठा v4l2_ctrl_h264_sps *p_h264_sps;
	काष्ठा v4l2_ctrl_h264_pps *p_h264_pps;
	काष्ठा v4l2_ctrl_h264_scaling_matrix *p_h264_scaling_matrix;
	काष्ठा v4l2_ctrl_h264_slice_params *p_h264_slice_params;
	काष्ठा v4l2_ctrl_h264_decode_params *p_h264_decode_params;
	काष्ठा v4l2_ctrl_h264_pred_weights *p_h264_pred_weights;
	काष्ठा v4l2_ctrl_vp8_frame *p_vp8_frame;
	काष्ठा v4l2_ctrl_hevc_sps *p_hevc_sps;
	काष्ठा v4l2_ctrl_hevc_pps *p_hevc_pps;
	काष्ठा v4l2_ctrl_hevc_slice_params *p_hevc_slice_params;
	काष्ठा v4l2_ctrl_hdr10_cll_info *p_hdr10_cll;
	काष्ठा v4l2_ctrl_hdr10_mastering_display *p_hdr10_mastering;
	काष्ठा v4l2_area *p_area;
	व्योम *p;
	स्थिर व्योम *p_स्थिर;
पूर्ण;

/**
 * v4l2_ctrl_ptr_create() - Helper function to वापस a v4l2_ctrl_ptr from a
 * व्योम poपूर्णांकer
 * @ptr:	The व्योम poपूर्णांकer
 */
अटल अंतरभूत जोड़ v4l2_ctrl_ptr v4l2_ctrl_ptr_create(व्योम *ptr)
अणु
	जोड़ v4l2_ctrl_ptr p = अणु .p = ptr पूर्ण;

	वापस p;
पूर्ण

/**
 * काष्ठा v4l2_ctrl_ops - The control operations that the driver has to provide.
 *
 * @g_अस्थिर_ctrl: Get a new value क्रम this control. Generally only relevant
 *		क्रम अस्थिर (and usually पढ़ो-only) controls such as a control
 *		that वापसs the current संकेत strength which changes
 *		continuously.
 *		If not set, then the currently cached value will be वापसed.
 * @try_ctrl:	Test whether the control's value is valid. Only relevant when
 *		the usual min/max/step checks are not sufficient.
 * @s_ctrl:	Actually set the new control value. s_ctrl is compulsory. The
 *		ctrl->handler->lock is held when these ops are called, so no
 *		one अन्यथा can access controls owned by that handler.
 */
काष्ठा v4l2_ctrl_ops अणु
	पूर्णांक (*g_अस्थिर_ctrl)(काष्ठा v4l2_ctrl *ctrl);
	पूर्णांक (*try_ctrl)(काष्ठा v4l2_ctrl *ctrl);
	पूर्णांक (*s_ctrl)(काष्ठा v4l2_ctrl *ctrl);
पूर्ण;

/**
 * काष्ठा v4l2_ctrl_type_ops - The control type operations that the driver
 *			       has to provide.
 *
 * @equal: वापस true अगर both values are equal.
 * @init: initialize the value.
 * @log: log the value.
 * @validate: validate the value. Return 0 on success and a negative value
 *	otherwise.
 */
काष्ठा v4l2_ctrl_type_ops अणु
	bool (*equal)(स्थिर काष्ठा v4l2_ctrl *ctrl, u32 idx,
		      जोड़ v4l2_ctrl_ptr ptr1,
		      जोड़ v4l2_ctrl_ptr ptr2);
	व्योम (*init)(स्थिर काष्ठा v4l2_ctrl *ctrl, u32 idx,
		     जोड़ v4l2_ctrl_ptr ptr);
	व्योम (*log)(स्थिर काष्ठा v4l2_ctrl *ctrl);
	पूर्णांक (*validate)(स्थिर काष्ठा v4l2_ctrl *ctrl, u32 idx,
			जोड़ v4l2_ctrl_ptr ptr);
पूर्ण;

/**
 * प्रकार v4l2_ctrl_notअगरy_fnc - प्रकार क्रम a notअगरy argument with a function
 *	that should be called when a control value has changed.
 *
 * @ctrl: poपूर्णांकer to काष्ठा &v4l2_ctrl
 * @priv: control निजी data
 *
 * This प्रकार definition is used as an argument to v4l2_ctrl_notअगरy()
 * and as an argument at काष्ठा &v4l2_ctrl_handler.
 */
प्रकार व्योम (*v4l2_ctrl_notअगरy_fnc)(काष्ठा v4l2_ctrl *ctrl, व्योम *priv);

/**
 * काष्ठा v4l2_ctrl - The control काष्ठाure.
 *
 * @node:	The list node.
 * @ev_subs:	The list of control event subscriptions.
 * @handler:	The handler that owns the control.
 * @cluster:	Poपूर्णांक to start of cluster array.
 * @ncontrols:	Number of controls in cluster array.
 * @करोne:	Internal flag: set क्रम each processed control.
 * @is_new:	Set when the user specअगरied a new value क्रम this control. It
 *		is also set when called from v4l2_ctrl_handler_setup(). Drivers
 *		should never set this flag.
 * @has_changed: Set when the current value dअगरfers from the new value. Drivers
 *		should never use this flag.
 * @is_निजी: If set, then this control is निजी to its handler and it
 *		will not be added to any other handlers. Drivers can set
 *		this flag.
 * @is_स्वतः:   If set, then this control selects whether the other cluster
 *		members are in 'automatic' mode or 'manual' mode. This is
 *		used क्रम स्वतःgain/gain type clusters. Drivers should never
 *		set this flag directly.
 * @is_पूर्णांक:    If set, then this control has a simple पूर्णांकeger value (i.e. it
 *		uses ctrl->val).
 * @is_string: If set, then this control has type %V4L2_CTRL_TYPE_STRING.
 * @is_ptr:	If set, then this control is an array and/or has type >=
 *		%V4L2_CTRL_COMPOUND_TYPES
 *		and/or has type %V4L2_CTRL_TYPE_STRING. In other words, &काष्ठा
 *		v4l2_ext_control uses field p to poपूर्णांक to the data.
 * @is_array: If set, then this control contains an N-dimensional array.
 * @has_अस्थिरs: If set, then one or more members of the cluster are अस्थिर.
 *		Drivers should never touch this flag.
 * @call_notअगरy: If set, then call the handler's notअगरy function whenever the
 *		control's value changes.
 * @manual_mode_value: If the is_स्वतः flag is set, then this is the value
 *		of the स्वतः control that determines अगर that control is in
 *		manual mode. So अगर the value of the स्वतः control equals this
 *		value, then the whole cluster is in manual mode. Drivers should
 *		never set this flag directly.
 * @ops:	The control ops.
 * @type_ops:	The control type ops.
 * @id:	The control ID.
 * @name:	The control name.
 * @type:	The control type.
 * @minimum:	The control's minimum value.
 * @maximum:	The control's maximum value.
 * @शेष_value: The control's शेष value.
 * @step:	The control's step value क्रम non-menu controls.
 * @elems:	The number of elements in the N-dimensional array.
 * @elem_size:	The size in bytes of the control.
 * @dims:	The size of each dimension.
 * @nr_of_dims:The number of dimensions in @dims.
 * @menu_skip_mask: The control's skip mask क्रम menu controls. This makes it
 *		easy to skip menu items that are not valid. If bit X is set,
 *		then menu item X is skipped. Of course, this only works क्रम
 *		menus with <= 32 menu items. There are no menus that come
 *		बंद to that number, so this is OK. Should we ever need more,
 *		then this will have to be extended to a u64 or a bit array.
 * @qmenu:	A स्थिर अक्षर * array क्रम all menu items. Array entries that are
 *		empty strings ("") correspond to non-existing menu items (this
 *		is in addition to the menu_skip_mask above). The last entry
 *		must be शून्य.
 *		Used only अगर the @type is %V4L2_CTRL_TYPE_MENU.
 * @qmenu_पूर्णांक:	A 64-bit पूर्णांकeger array क्रम with पूर्णांकeger menu items.
 *		The size of array must be equal to the menu size, e. g.:
 *		:math:`उच्चमान(\पracअणुmaximum - minimumपूर्णअणुstepपूर्ण) + 1`.
 *		Used only अगर the @type is %V4L2_CTRL_TYPE_INTEGER_MENU.
 * @flags:	The control's flags.
 * @cur:	Structure to store the current value.
 * @cur.val:	The control's current value, अगर the @type is represented via
 *		a u32 पूर्णांकeger (see &क्रमागत v4l2_ctrl_type).
 * @val:	The control's new s32 value.
 * @priv:	The control's निजी poपूर्णांकer. For use by the driver. It is
 *		untouched by the control framework. Note that this poपूर्णांकer is
 *		not मुक्तd when the control is deleted. Should this be needed
 *		then a new पूर्णांकernal bitfield can be added to tell the framework
 *		to मुक्त this poपूर्णांकer.
 * @p_def:	The control's शेष value represented via a जोड़ which
 *		provides a standard way of accessing control types
 *		through a poपूर्णांकer (क्रम compound controls only).
 * @p_cur:	The control's current value represented via a जोड़ which
 *		provides a standard way of accessing control types
 *		through a poपूर्णांकer.
 * @p_new:	The control's new value represented via a जोड़ which provides
 *		a standard way of accessing control types
 *		through a poपूर्णांकer.
 */
काष्ठा v4l2_ctrl अणु
	/* Administrative fields */
	काष्ठा list_head node;
	काष्ठा list_head ev_subs;
	काष्ठा v4l2_ctrl_handler *handler;
	काष्ठा v4l2_ctrl **cluster;
	अचिन्हित पूर्णांक ncontrols;

	अचिन्हित पूर्णांक करोne:1;

	अचिन्हित पूर्णांक is_new:1;
	अचिन्हित पूर्णांक has_changed:1;
	अचिन्हित पूर्णांक is_निजी:1;
	अचिन्हित पूर्णांक is_स्वतः:1;
	अचिन्हित पूर्णांक is_पूर्णांक:1;
	अचिन्हित पूर्णांक is_string:1;
	अचिन्हित पूर्णांक is_ptr:1;
	अचिन्हित पूर्णांक is_array:1;
	अचिन्हित पूर्णांक has_अस्थिरs:1;
	अचिन्हित पूर्णांक call_notअगरy:1;
	अचिन्हित पूर्णांक manual_mode_value:8;

	स्थिर काष्ठा v4l2_ctrl_ops *ops;
	स्थिर काष्ठा v4l2_ctrl_type_ops *type_ops;
	u32 id;
	स्थिर अक्षर *name;
	क्रमागत v4l2_ctrl_type type;
	s64 minimum, maximum, शेष_value;
	u32 elems;
	u32 elem_size;
	u32 dims[V4L2_CTRL_MAX_DIMS];
	u32 nr_of_dims;
	जोड़ अणु
		u64 step;
		u64 menu_skip_mask;
	पूर्ण;
	जोड़ अणु
		स्थिर अक्षर * स्थिर *qmenu;
		स्थिर s64 *qmenu_पूर्णांक;
	पूर्ण;
	अचिन्हित दीर्घ flags;
	व्योम *priv;
	s32 val;
	काष्ठा अणु
		s32 val;
	पूर्ण cur;

	जोड़ v4l2_ctrl_ptr p_def;
	जोड़ v4l2_ctrl_ptr p_new;
	जोड़ v4l2_ctrl_ptr p_cur;
पूर्ण;

/**
 * काष्ठा v4l2_ctrl_ref - The control reference.
 *
 * @node:	List node क्रम the sorted list.
 * @next:	Single-link list node क्रम the hash.
 * @ctrl:	The actual control inक्रमmation.
 * @helper:	Poपूर्णांकer to helper काष्ठा. Used पूर्णांकernally in
 *		``prepare_ext_ctrls`` function at ``v4l2-ctrl.c``.
 * @from_other_dev: If true, then @ctrl was defined in another
 *		device than the &काष्ठा v4l2_ctrl_handler.
 * @req_करोne:	Internal flag: अगर the control handler containing this control
 *		reference is bound to a media request, then this is set when
 *		the control has been applied. This prevents applying controls
 *		from a cluster with multiple controls twice (when the first
 *		control of a cluster is applied, they all are).
 * @valid_p_req: If set, then p_req contains the control value क्रम the request.
 * @p_req:	If the control handler containing this control reference
 *		is bound to a media request, then this poपूर्णांकs to the
 *		value of the control that must be applied when the request
 *		is executed, or to the value of the control at the समय
 *		that the request was completed. If @valid_p_req is false,
 *		then this control was never set क्रम this request and the
 *		control will not be updated when this request is applied.
 *
 * Each control handler has a list of these refs. The list_head is used to
 * keep a sorted-by-control-ID list of all controls, जबतक the next poपूर्णांकer
 * is used to link the control in the hash's bucket.
 */
काष्ठा v4l2_ctrl_ref अणु
	काष्ठा list_head node;
	काष्ठा v4l2_ctrl_ref *next;
	काष्ठा v4l2_ctrl *ctrl;
	काष्ठा v4l2_ctrl_helper *helper;
	bool from_other_dev;
	bool req_करोne;
	bool valid_p_req;
	जोड़ v4l2_ctrl_ptr p_req;
पूर्ण;

/**
 * काष्ठा v4l2_ctrl_handler - The control handler keeps track of all the
 *	controls: both the controls owned by the handler and those inherited
 *	from other handlers.
 *
 * @_lock:	Default क्रम "lock".
 * @lock:	Lock to control access to this handler and its controls.
 *		May be replaced by the user right after init.
 * @ctrls:	The list of controls owned by this handler.
 * @ctrl_refs:	The list of control references.
 * @cached:	The last found control reference. It is common that the same
 *		control is needed multiple बार, so this is a simple
 *		optimization.
 * @buckets:	Buckets क्रम the hashing. Allows क्रम quick control lookup.
 * @notअगरy:	A notअगरy callback that is called whenever the control changes
 *		value.
 *		Note that the handler's lock is held when the notअगरy function
 *		is called!
 * @notअगरy_priv: Passed as argument to the v4l2_ctrl notअगरy callback.
 * @nr_of_buckets: Total number of buckets in the array.
 * @error:	The error code of the first failed control addition.
 * @request_is_queued: True अगर the request was queued.
 * @requests:	List to keep track of खोलो control handler request objects.
 *		For the parent control handler (@req_obj.ops == शून्य) this
 *		is the list header. When the parent control handler is
 *		हटाओd, it has to unbind and put all these requests since
 *		they refer to the parent.
 * @requests_queued: List of the queued requests. This determines the order
 *		in which these controls are applied. Once the request is
 *		completed it is हटाओd from this list.
 * @req_obj:	The &काष्ठा media_request_object, used to link पूर्णांकo a
 *		&काष्ठा media_request. This request object has a refcount.
 */
काष्ठा v4l2_ctrl_handler अणु
	काष्ठा mutex _lock;
	काष्ठा mutex *lock;
	काष्ठा list_head ctrls;
	काष्ठा list_head ctrl_refs;
	काष्ठा v4l2_ctrl_ref *cached;
	काष्ठा v4l2_ctrl_ref **buckets;
	v4l2_ctrl_notअगरy_fnc notअगरy;
	व्योम *notअगरy_priv;
	u16 nr_of_buckets;
	पूर्णांक error;
	bool request_is_queued;
	काष्ठा list_head requests;
	काष्ठा list_head requests_queued;
	काष्ठा media_request_object req_obj;
पूर्ण;

/**
 * काष्ठा v4l2_ctrl_config - Control configuration काष्ठाure.
 *
 * @ops:	The control ops.
 * @type_ops:	The control type ops. Only needed क्रम compound controls.
 * @id:	The control ID.
 * @name:	The control name.
 * @type:	The control type.
 * @min:	The control's minimum value.
 * @max:	The control's maximum value.
 * @step:	The control's step value क्रम non-menu controls.
 * @def:	The control's शेष value.
 * @p_def:	The control's शेष value क्रम compound controls.
 * @dims:	The size of each dimension.
 * @elem_size:	The size in bytes of the control.
 * @flags:	The control's flags.
 * @menu_skip_mask: The control's skip mask क्रम menu controls. This makes it
 *		easy to skip menu items that are not valid. If bit X is set,
 *		then menu item X is skipped. Of course, this only works क्रम
 *		menus with <= 64 menu items. There are no menus that come
 *		बंद to that number, so this is OK. Should we ever need more,
 *		then this will have to be extended to a bit array.
 * @qmenu:	A स्थिर अक्षर * array क्रम all menu items. Array entries that are
 *		empty strings ("") correspond to non-existing menu items (this
 *		is in addition to the menu_skip_mask above). The last entry
 *		must be शून्य.
 * @qmenu_पूर्णांक:	A स्थिर s64 पूर्णांकeger array क्रम all menu items of the type
 *		V4L2_CTRL_TYPE_INTEGER_MENU.
 * @is_निजी: If set, then this control is निजी to its handler and it
 *		will not be added to any other handlers.
 */
काष्ठा v4l2_ctrl_config अणु
	स्थिर काष्ठा v4l2_ctrl_ops *ops;
	स्थिर काष्ठा v4l2_ctrl_type_ops *type_ops;
	u32 id;
	स्थिर अक्षर *name;
	क्रमागत v4l2_ctrl_type type;
	s64 min;
	s64 max;
	u64 step;
	s64 def;
	जोड़ v4l2_ctrl_ptr p_def;
	u32 dims[V4L2_CTRL_MAX_DIMS];
	u32 elem_size;
	u32 flags;
	u64 menu_skip_mask;
	स्थिर अक्षर * स्थिर *qmenu;
	स्थिर s64 *qmenu_पूर्णांक;
	अचिन्हित पूर्णांक is_निजी:1;
पूर्ण;

/**
 * v4l2_ctrl_fill - Fill in the control fields based on the control ID.
 *
 * @id: ID of the control
 * @name: poपूर्णांकer to be filled with a string with the name of the control
 * @type: poपूर्णांकer क्रम storing the type of the control
 * @min: poपूर्णांकer क्रम storing the minimum value क्रम the control
 * @max: poपूर्णांकer क्रम storing the maximum value क्रम the control
 * @step: poपूर्णांकer क्रम storing the control step
 * @def: poपूर्णांकer क्रम storing the शेष value क्रम the control
 * @flags: poपूर्णांकer क्रम storing the flags to be used on the control
 *
 * This works क्रम all standard V4L2 controls.
 * For non-standard controls it will only fill in the given arguments
 * and @name content will be set to %शून्य.
 *
 * This function will overग_लिखो the contents of @name, @type and @flags.
 * The contents of @min, @max, @step and @def may be modअगरied depending on
 * the type.
 *
 * .. note::
 *
 *    Do not use in drivers! It is used पूर्णांकernally क्रम backwards compatibility
 *    control handling only. Once all drivers are converted to use the new
 *    control framework this function will no दीर्घer be exported.
 */
व्योम v4l2_ctrl_fill(u32 id, स्थिर अक्षर **name, क्रमागत v4l2_ctrl_type *type,
		    s64 *min, s64 *max, u64 *step, s64 *def, u32 *flags);


/**
 * v4l2_ctrl_handler_init_class() - Initialize the control handler.
 * @hdl:	The control handler.
 * @nr_of_controls_hपूर्णांक: A hपूर्णांक of how many controls this handler is
 *		expected to refer to. This is the total number, so including
 *		any inherited controls. It करोesn't have to be precise, but अगर
 *		it is way off, then you either waste memory (too many buckets
 *		are allocated) or the control lookup becomes slower (not enough
 *		buckets are allocated, so there are more slow list lookups).
 *		It will always work, though.
 * @key:	Used by the lock validator अगर CONFIG_LOCKDEP is set.
 * @name:	Used by the lock validator अगर CONFIG_LOCKDEP is set.
 *
 * .. attention::
 *
 *    Never use this call directly, always use the v4l2_ctrl_handler_init()
 *    macro that hides the @key and @name arguments.
 *
 * Return: वापसs an error अगर the buckets could not be allocated. This
 * error will also be stored in @hdl->error.
 */
पूर्णांक v4l2_ctrl_handler_init_class(काष्ठा v4l2_ctrl_handler *hdl,
				 अचिन्हित पूर्णांक nr_of_controls_hपूर्णांक,
				 काष्ठा lock_class_key *key, स्थिर अक्षर *name);

#अगर_घोषित CONFIG_LOCKDEP

/**
 * v4l2_ctrl_handler_init - helper function to create a अटल काष्ठा
 *	 &lock_class_key and calls v4l2_ctrl_handler_init_class()
 *
 * @hdl:	The control handler.
 * @nr_of_controls_hपूर्णांक: A hपूर्णांक of how many controls this handler is
 *		expected to refer to. This is the total number, so including
 *		any inherited controls. It करोesn't have to be precise, but अगर
 *		it is way off, then you either waste memory (too many buckets
 *		are allocated) or the control lookup becomes slower (not enough
 *		buckets are allocated, so there are more slow list lookups).
 *		It will always work, though.
 *
 * This helper function creates a अटल काष्ठा &lock_class_key and
 * calls v4l2_ctrl_handler_init_class(), providing a proper name क्रम the lock
 * validaकरोr.
 *
 * Use this helper function to initialize a control handler.
 */
#घोषणा v4l2_ctrl_handler_init(hdl, nr_of_controls_hपूर्णांक)		\
(									\
	(अणु								\
		अटल काष्ठा lock_class_key _key;			\
		v4l2_ctrl_handler_init_class(hdl, nr_of_controls_hपूर्णांक,	\
					&_key,				\
					KBUILD_BASENAME ":"		\
					__stringअगरy(__LINE__) ":"	\
					"(" #hdl ")->_lock");		\
	पूर्ण)								\
)
#अन्यथा
#घोषणा v4l2_ctrl_handler_init(hdl, nr_of_controls_hपूर्णांक)		\
	v4l2_ctrl_handler_init_class(hdl, nr_of_controls_hपूर्णांक, शून्य, शून्य)
#पूर्ण_अगर

/**
 * v4l2_ctrl_handler_मुक्त() - Free all controls owned by the handler and मुक्त
 * the control list.
 * @hdl:	The control handler.
 *
 * Does nothing अगर @hdl == शून्य.
 */
व्योम v4l2_ctrl_handler_मुक्त(काष्ठा v4l2_ctrl_handler *hdl);

/**
 * v4l2_ctrl_lock() - Helper function to lock the handler
 * associated with the control.
 * @ctrl:	The control to lock.
 */
अटल अंतरभूत व्योम v4l2_ctrl_lock(काष्ठा v4l2_ctrl *ctrl)
अणु
	mutex_lock(ctrl->handler->lock);
पूर्ण

/**
 * v4l2_ctrl_unlock() - Helper function to unlock the handler
 * associated with the control.
 * @ctrl:	The control to unlock.
 */
अटल अंतरभूत व्योम v4l2_ctrl_unlock(काष्ठा v4l2_ctrl *ctrl)
अणु
	mutex_unlock(ctrl->handler->lock);
पूर्ण

/**
 * __v4l2_ctrl_handler_setup() - Call the s_ctrl op क्रम all controls beदीर्घing
 * to the handler to initialize the hardware to the current control values. The
 * caller is responsible क्रम acquiring the control handler mutex on behalf of
 * __v4l2_ctrl_handler_setup().
 * @hdl:	The control handler.
 *
 * Button controls will be skipped, as are पढ़ो-only controls.
 *
 * If @hdl == शून्य, then this just वापसs 0.
 */
पूर्णांक __v4l2_ctrl_handler_setup(काष्ठा v4l2_ctrl_handler *hdl);

/**
 * v4l2_ctrl_handler_setup() - Call the s_ctrl op क्रम all controls beदीर्घing
 * to the handler to initialize the hardware to the current control values.
 * @hdl:	The control handler.
 *
 * Button controls will be skipped, as are पढ़ो-only controls.
 *
 * If @hdl == शून्य, then this just वापसs 0.
 */
पूर्णांक v4l2_ctrl_handler_setup(काष्ठा v4l2_ctrl_handler *hdl);

/**
 * v4l2_ctrl_handler_log_status() - Log all controls owned by the handler.
 * @hdl:	The control handler.
 * @prefix:	The prefix to use when logging the control values. If the
 *		prefix करोes not end with a space, then ": " will be added
 *		after the prefix. If @prefix == शून्य, then no prefix will be
 *		used.
 *
 * For use with VIDIOC_LOG_STATUS.
 *
 * Does nothing अगर @hdl == शून्य.
 */
व्योम v4l2_ctrl_handler_log_status(काष्ठा v4l2_ctrl_handler *hdl,
				  स्थिर अक्षर *prefix);

/**
 * v4l2_ctrl_new_custom() - Allocate and initialize a new custom V4L2
 *	control.
 *
 * @hdl:	The control handler.
 * @cfg:	The control's configuration data.
 * @priv:	The control's driver-specअगरic निजी data.
 *
 * If the &v4l2_ctrl काष्ठा could not be allocated then शून्य is वापसed
 * and @hdl->error is set to the error code (अगर it wasn't set alपढ़ोy).
 */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_custom(काष्ठा v4l2_ctrl_handler *hdl,
				       स्थिर काष्ठा v4l2_ctrl_config *cfg,
				       व्योम *priv);

/**
 * v4l2_ctrl_new_std() - Allocate and initialize a new standard V4L2 non-menu
 *	control.
 *
 * @hdl:	The control handler.
 * @ops:	The control ops.
 * @id:		The control ID.
 * @min:	The control's minimum value.
 * @max:	The control's maximum value.
 * @step:	The control's step value
 * @def:	The control's शेष value.
 *
 * If the &v4l2_ctrl काष्ठा could not be allocated, or the control
 * ID is not known, then शून्य is वापसed and @hdl->error is set to the
 * appropriate error code (अगर it wasn't set alपढ़ोy).
 *
 * If @id refers to a menu control, then this function will वापस शून्य.
 *
 * Use v4l2_ctrl_new_std_menu() when adding menu controls.
 */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_std(काष्ठा v4l2_ctrl_handler *hdl,
				    स्थिर काष्ठा v4l2_ctrl_ops *ops,
				    u32 id, s64 min, s64 max, u64 step,
				    s64 def);

/**
 * v4l2_ctrl_new_std_menu() - Allocate and initialize a new standard V4L2
 *	menu control.
 *
 * @hdl:	The control handler.
 * @ops:	The control ops.
 * @id:		The control ID.
 * @max:	The control's maximum value.
 * @mask:	The control's skip mask क्रम menu controls. This makes it
 *		easy to skip menu items that are not valid. If bit X is set,
 *		then menu item X is skipped. Of course, this only works क्रम
 *		menus with <= 64 menu items. There are no menus that come
 *		बंद to that number, so this is OK. Should we ever need more,
 *		then this will have to be extended to a bit array.
 * @def:	The control's शेष value.
 *
 * Same as v4l2_ctrl_new_std(), but @min is set to 0 and the @mask value
 * determines which menu items are to be skipped.
 *
 * If @id refers to a non-menu control, then this function will वापस शून्य.
 */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_std_menu(काष्ठा v4l2_ctrl_handler *hdl,
					 स्थिर काष्ठा v4l2_ctrl_ops *ops,
					 u32 id, u8 max, u64 mask, u8 def);

/**
 * v4l2_ctrl_new_std_menu_items() - Create a new standard V4L2 menu control
 *	with driver specअगरic menu.
 *
 * @hdl:	The control handler.
 * @ops:	The control ops.
 * @id:	The control ID.
 * @max:	The control's maximum value.
 * @mask:	The control's skip mask क्रम menu controls. This makes it
 *		easy to skip menu items that are not valid. If bit X is set,
 *		then menu item X is skipped. Of course, this only works क्रम
 *		menus with <= 64 menu items. There are no menus that come
 *		बंद to that number, so this is OK. Should we ever need more,
 *		then this will have to be extended to a bit array.
 * @def:	The control's शेष value.
 * @qmenu:	The new menu.
 *
 * Same as v4l2_ctrl_new_std_menu(), but @qmenu will be the driver specअगरic
 * menu of this control.
 *
 */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_std_menu_items(काष्ठा v4l2_ctrl_handler *hdl,
					       स्थिर काष्ठा v4l2_ctrl_ops *ops,
					       u32 id, u8 max,
					       u64 mask, u8 def,
					       स्थिर अक्षर * स्थिर *qmenu);

/**
 * v4l2_ctrl_new_std_compound() - Allocate and initialize a new standard V4L2
 *      compound control.
 *
 * @hdl:       The control handler.
 * @ops:       The control ops.
 * @id:        The control ID.
 * @p_def:     The control's शेष value.
 *
 * Sames as v4l2_ctrl_new_std(), but with support to compound controls, thanks
 * to the @p_def field. Use v4l2_ctrl_ptr_create() to create @p_def from a
 * poपूर्णांकer. Use v4l2_ctrl_ptr_create(शून्य) अगर the शेष value of the
 * compound control should be all zeroes.
 *
 */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_std_compound(काष्ठा v4l2_ctrl_handler *hdl,
					     स्थिर काष्ठा v4l2_ctrl_ops *ops,
					     u32 id,
					     स्थिर जोड़ v4l2_ctrl_ptr p_def);

/**
 * v4l2_ctrl_new_पूर्णांक_menu() - Create a new standard V4L2 पूर्णांकeger menu control.
 *
 * @hdl:	The control handler.
 * @ops:	The control ops.
 * @id:	The control ID.
 * @max:	The control's maximum value.
 * @def:	The control's शेष value.
 * @qmenu_पूर्णांक:	The control's menu entries.
 *
 * Same as v4l2_ctrl_new_std_menu(), but @mask is set to 0 and it additionally
 * takes as an argument an array of पूर्णांकegers determining the menu items.
 *
 * If @id refers to a non-पूर्णांकeger-menu control, then this function will
 * वापस %शून्य.
 */
काष्ठा v4l2_ctrl *v4l2_ctrl_new_पूर्णांक_menu(काष्ठा v4l2_ctrl_handler *hdl,
					 स्थिर काष्ठा v4l2_ctrl_ops *ops,
					 u32 id, u8 max, u8 def,
					 स्थिर s64 *qmenu_पूर्णांक);

/**
 * प्रकार v4l2_ctrl_filter - Typedef to define the filter function to be
 *	used when adding a control handler.
 *
 * @ctrl: poपूर्णांकer to काष्ठा &v4l2_ctrl.
 */

प्रकार bool (*v4l2_ctrl_filter)(स्थिर काष्ठा v4l2_ctrl *ctrl);

/**
 * v4l2_ctrl_add_handler() - Add all controls from handler @add to
 *	handler @hdl.
 *
 * @hdl:	The control handler.
 * @add:	The control handler whose controls you want to add to
 *		the @hdl control handler.
 * @filter:	This function will filter which controls should be added.
 * @from_other_dev: If true, then the controls in @add were defined in another
 *		device than @hdl.
 *
 * Does nothing अगर either of the two handlers is a शून्य poपूर्णांकer.
 * If @filter is शून्य, then all controls are added. Otherwise only those
 * controls क्रम which @filter वापसs true will be added.
 * In हाल of an error @hdl->error will be set to the error code (अगर it
 * wasn't set alपढ़ोy).
 */
पूर्णांक v4l2_ctrl_add_handler(काष्ठा v4l2_ctrl_handler *hdl,
			  काष्ठा v4l2_ctrl_handler *add,
			  v4l2_ctrl_filter filter,
			  bool from_other_dev);

/**
 * v4l2_ctrl_radio_filter() - Standard filter क्रम radio controls.
 *
 * @ctrl:	The control that is filtered.
 *
 * This will वापस true क्रम any controls that are valid क्रम radio device
 * nodes. Those are all of the V4L2_CID_AUDIO_* user controls and all FM
 * transmitter class controls.
 *
 * This function is to be used with v4l2_ctrl_add_handler().
 */
bool v4l2_ctrl_radio_filter(स्थिर काष्ठा v4l2_ctrl *ctrl);

/**
 * v4l2_ctrl_cluster() - Mark all controls in the cluster as beदीर्घing
 *	to that cluster.
 *
 * @ncontrols:	The number of controls in this cluster.
 * @controls:	The cluster control array of size @ncontrols.
 */
व्योम v4l2_ctrl_cluster(अचिन्हित पूर्णांक ncontrols, काष्ठा v4l2_ctrl **controls);


/**
 * v4l2_ctrl_स्वतः_cluster() - Mark all controls in the cluster as beदीर्घing
 *	to that cluster and set it up क्रम स्वतःfoo/foo-type handling.
 *
 * @ncontrols:	The number of controls in this cluster.
 * @controls:	The cluster control array of size @ncontrols. The first control
 *		must be the 'auto' control (e.g. स्वतःgain, स्वतःexposure, etc.)
 * @manual_val: The value क्रम the first control in the cluster that equals the
 *		manual setting.
 * @set_अस्थिर: If true, then all controls except the first स्वतः control will
 *		be अस्थिर.
 *
 * Use क्रम control groups where one control selects some स्वतःmatic feature and
 * the other controls are only active whenever the स्वतःmatic feature is turned
 * off (manual mode). Typical examples: स्वतःgain vs gain, स्वतः-whitebalance vs
 * red and blue balance, etc.
 *
 * The behavior of such controls is as follows:
 *
 * When the स्वतःfoo control is set to स्वतःmatic, then any manual controls
 * are set to inactive and any पढ़ोs will call g_अस्थिर_ctrl (अगर the control
 * was marked अस्थिर).
 *
 * When the स्वतःfoo control is set to manual, then any manual controls will
 * be marked active, and any पढ़ोs will just वापस the current value without
 * going through g_अस्थिर_ctrl.
 *
 * In addition, this function will set the %V4L2_CTRL_FLAG_UPDATE flag
 * on the स्वतःfoo control and %V4L2_CTRL_FLAG_INACTIVE on the foo control(s)
 * अगर स्वतःfoo is in स्वतः mode.
 */
व्योम v4l2_ctrl_स्वतः_cluster(अचिन्हित पूर्णांक ncontrols,
			    काष्ठा v4l2_ctrl **controls,
			    u8 manual_val, bool set_अस्थिर);


/**
 * v4l2_ctrl_find() - Find a control with the given ID.
 *
 * @hdl:	The control handler.
 * @id:	The control ID to find.
 *
 * If @hdl == शून्य this will वापस शून्य as well. Will lock the handler so
 * करो not use from inside &v4l2_ctrl_ops.
 */
काष्ठा v4l2_ctrl *v4l2_ctrl_find(काष्ठा v4l2_ctrl_handler *hdl, u32 id);

/**
 * v4l2_ctrl_activate() - Make the control active or inactive.
 * @ctrl:	The control to (de)activate.
 * @active:	True अगर the control should become active.
 *
 * This sets or clears the V4L2_CTRL_FLAG_INACTIVE flag atomically.
 * Does nothing अगर @ctrl == शून्य.
 * This will usually be called from within the s_ctrl op.
 * The V4L2_EVENT_CTRL event will be generated afterwards.
 *
 * This function assumes that the control handler is locked.
 */
व्योम v4l2_ctrl_activate(काष्ठा v4l2_ctrl *ctrl, bool active);

/**
 * __v4l2_ctrl_grab() - Unlocked variant of v4l2_ctrl_grab.
 *
 * @ctrl:	The control to (de)activate.
 * @grabbed:	True अगर the control should become grabbed.
 *
 * This sets or clears the V4L2_CTRL_FLAG_GRABBED flag atomically.
 * Does nothing अगर @ctrl == शून्य.
 * The V4L2_EVENT_CTRL event will be generated afterwards.
 * This will usually be called when starting or stopping streaming in the
 * driver.
 *
 * This function assumes that the control handler is locked by the caller.
 */
व्योम __v4l2_ctrl_grab(काष्ठा v4l2_ctrl *ctrl, bool grabbed);

/**
 * v4l2_ctrl_grab() - Mark the control as grabbed or not grabbed.
 *
 * @ctrl:	The control to (de)activate.
 * @grabbed:	True अगर the control should become grabbed.
 *
 * This sets or clears the V4L2_CTRL_FLAG_GRABBED flag atomically.
 * Does nothing अगर @ctrl == शून्य.
 * The V4L2_EVENT_CTRL event will be generated afterwards.
 * This will usually be called when starting or stopping streaming in the
 * driver.
 *
 * This function assumes that the control handler is not locked and will
 * take the lock itself.
 */
अटल अंतरभूत व्योम v4l2_ctrl_grab(काष्ठा v4l2_ctrl *ctrl, bool grabbed)
अणु
	अगर (!ctrl)
		वापस;

	v4l2_ctrl_lock(ctrl);
	__v4l2_ctrl_grab(ctrl, grabbed);
	v4l2_ctrl_unlock(ctrl);
पूर्ण

/**
 *__v4l2_ctrl_modअगरy_range() - Unlocked variant of v4l2_ctrl_modअगरy_range()
 *
 * @ctrl:	The control to update.
 * @min:	The control's minimum value.
 * @max:	The control's maximum value.
 * @step:	The control's step value
 * @def:	The control's शेष value.
 *
 * Update the range of a control on the fly. This works क्रम control types
 * INTEGER, BOOLEAN, MENU, INTEGER MENU and BITMASK. For menu controls the
 * @step value is पूर्णांकerpreted as a menu_skip_mask.
 *
 * An error is वापसed अगर one of the range arguments is invalid क्रम this
 * control type.
 *
 * The caller is responsible क्रम acquiring the control handler mutex on behalf
 * of __v4l2_ctrl_modअगरy_range().
 */
पूर्णांक __v4l2_ctrl_modअगरy_range(काष्ठा v4l2_ctrl *ctrl,
			     s64 min, s64 max, u64 step, s64 def);

/**
 * v4l2_ctrl_modअगरy_range() - Update the range of a control.
 *
 * @ctrl:	The control to update.
 * @min:	The control's minimum value.
 * @max:	The control's maximum value.
 * @step:	The control's step value
 * @def:	The control's शेष value.
 *
 * Update the range of a control on the fly. This works क्रम control types
 * INTEGER, BOOLEAN, MENU, INTEGER MENU and BITMASK. For menu controls the
 * @step value is पूर्णांकerpreted as a menu_skip_mask.
 *
 * An error is वापसed अगर one of the range arguments is invalid क्रम this
 * control type.
 *
 * This function assumes that the control handler is not locked and will
 * take the lock itself.
 */
अटल अंतरभूत पूर्णांक v4l2_ctrl_modअगरy_range(काष्ठा v4l2_ctrl *ctrl,
					 s64 min, s64 max, u64 step, s64 def)
अणु
	पूर्णांक rval;

	v4l2_ctrl_lock(ctrl);
	rval = __v4l2_ctrl_modअगरy_range(ctrl, min, max, step, def);
	v4l2_ctrl_unlock(ctrl);

	वापस rval;
पूर्ण

/**
 * v4l2_ctrl_notअगरy() - Function to set a notअगरy callback क्रम a control.
 *
 * @ctrl:	The control.
 * @notअगरy:	The callback function.
 * @priv:	The callback निजी handle, passed as argument to the callback.
 *
 * This function sets a callback function क्रम the control. If @ctrl is शून्य,
 * then it will करो nothing. If @notअगरy is शून्य, then the notअगरy callback will
 * be हटाओd.
 *
 * There can be only one notअगरy. If another alपढ़ोy exists, then a WARN_ON
 * will be issued and the function will करो nothing.
 */
व्योम v4l2_ctrl_notअगरy(काष्ठा v4l2_ctrl *ctrl, v4l2_ctrl_notअगरy_fnc notअगरy,
		      व्योम *priv);

/**
 * v4l2_ctrl_get_name() - Get the name of the control
 *
 * @id:		The control ID.
 *
 * This function वापसs the name of the given control ID or शून्य अगर it isn't
 * a known control.
 */
स्थिर अक्षर *v4l2_ctrl_get_name(u32 id);

/**
 * v4l2_ctrl_get_menu() - Get the menu string array of the control
 *
 * @id:		The control ID.
 *
 * This function वापसs the शून्य-terminated menu string array name of the
 * given control ID or शून्य अगर it isn't a known menu control.
 */
स्थिर अक्षर * स्थिर *v4l2_ctrl_get_menu(u32 id);

/**
 * v4l2_ctrl_get_पूर्णांक_menu() - Get the पूर्णांकeger menu array of the control
 *
 * @id:		The control ID.
 * @len:	The size of the पूर्णांकeger array.
 *
 * This function वापसs the पूर्णांकeger array of the given control ID or शून्य अगर it
 * अगर it isn't a known पूर्णांकeger menu control.
 */
स्थिर s64 *v4l2_ctrl_get_पूर्णांक_menu(u32 id, u32 *len);

/**
 * v4l2_ctrl_g_ctrl() - Helper function to get the control's value from
 *	within a driver.
 *
 * @ctrl:	The control.
 *
 * This वापसs the control's value safely by going through the control
 * framework. This function will lock the control's handler, so it cannot be
 * used from within the &v4l2_ctrl_ops functions.
 *
 * This function is क्रम पूर्णांकeger type controls only.
 */
s32 v4l2_ctrl_g_ctrl(काष्ठा v4l2_ctrl *ctrl);

/**
 * __v4l2_ctrl_s_ctrl() - Unlocked variant of v4l2_ctrl_s_ctrl().
 *
 * @ctrl:	The control.
 * @val:	The new value.
 *
 * This sets the control's new value safely by going through the control
 * framework. This function assumes the control's handler is alपढ़ोy locked,
 * allowing it to be used from within the &v4l2_ctrl_ops functions.
 *
 * This function is क्रम पूर्णांकeger type controls only.
 */
पूर्णांक __v4l2_ctrl_s_ctrl(काष्ठा v4l2_ctrl *ctrl, s32 val);

/**
 * v4l2_ctrl_s_ctrl() - Helper function to set the control's value from
 *	within a driver.
 * @ctrl:	The control.
 * @val:	The new value.
 *
 * This sets the control's new value safely by going through the control
 * framework. This function will lock the control's handler, so it cannot be
 * used from within the &v4l2_ctrl_ops functions.
 *
 * This function is क्रम पूर्णांकeger type controls only.
 */
अटल अंतरभूत पूर्णांक v4l2_ctrl_s_ctrl(काष्ठा v4l2_ctrl *ctrl, s32 val)
अणु
	पूर्णांक rval;

	v4l2_ctrl_lock(ctrl);
	rval = __v4l2_ctrl_s_ctrl(ctrl, val);
	v4l2_ctrl_unlock(ctrl);

	वापस rval;
पूर्ण

/**
 * v4l2_ctrl_g_ctrl_पूर्णांक64() - Helper function to get a 64-bit control's value
 *	from within a driver.
 *
 * @ctrl:	The control.
 *
 * This वापसs the control's value safely by going through the control
 * framework. This function will lock the control's handler, so it cannot be
 * used from within the &v4l2_ctrl_ops functions.
 *
 * This function is क्रम 64-bit पूर्णांकeger type controls only.
 */
s64 v4l2_ctrl_g_ctrl_पूर्णांक64(काष्ठा v4l2_ctrl *ctrl);

/**
 * __v4l2_ctrl_s_ctrl_पूर्णांक64() - Unlocked variant of v4l2_ctrl_s_ctrl_पूर्णांक64().
 *
 * @ctrl:	The control.
 * @val:	The new value.
 *
 * This sets the control's new value safely by going through the control
 * framework. This function assumes the control's handler is alपढ़ोy locked,
 * allowing it to be used from within the &v4l2_ctrl_ops functions.
 *
 * This function is क्रम 64-bit पूर्णांकeger type controls only.
 */
पूर्णांक __v4l2_ctrl_s_ctrl_पूर्णांक64(काष्ठा v4l2_ctrl *ctrl, s64 val);

/**
 * v4l2_ctrl_s_ctrl_पूर्णांक64() - Helper function to set a 64-bit control's value
 *	from within a driver.
 *
 * @ctrl:	The control.
 * @val:	The new value.
 *
 * This sets the control's new value safely by going through the control
 * framework. This function will lock the control's handler, so it cannot be
 * used from within the &v4l2_ctrl_ops functions.
 *
 * This function is क्रम 64-bit पूर्णांकeger type controls only.
 */
अटल अंतरभूत पूर्णांक v4l2_ctrl_s_ctrl_पूर्णांक64(काष्ठा v4l2_ctrl *ctrl, s64 val)
अणु
	पूर्णांक rval;

	v4l2_ctrl_lock(ctrl);
	rval = __v4l2_ctrl_s_ctrl_पूर्णांक64(ctrl, val);
	v4l2_ctrl_unlock(ctrl);

	वापस rval;
पूर्ण

/**
 * __v4l2_ctrl_s_ctrl_string() - Unlocked variant of v4l2_ctrl_s_ctrl_string().
 *
 * @ctrl:	The control.
 * @s:		The new string.
 *
 * This sets the control's new string safely by going through the control
 * framework. This function assumes the control's handler is alपढ़ोy locked,
 * allowing it to be used from within the &v4l2_ctrl_ops functions.
 *
 * This function is क्रम string type controls only.
 */
पूर्णांक __v4l2_ctrl_s_ctrl_string(काष्ठा v4l2_ctrl *ctrl, स्थिर अक्षर *s);

/**
 * v4l2_ctrl_s_ctrl_string() - Helper function to set a control's string value
 *	 from within a driver.
 *
 * @ctrl:	The control.
 * @s:		The new string.
 *
 * This sets the control's new string safely by going through the control
 * framework. This function will lock the control's handler, so it cannot be
 * used from within the &v4l2_ctrl_ops functions.
 *
 * This function is क्रम string type controls only.
 */
अटल अंतरभूत पूर्णांक v4l2_ctrl_s_ctrl_string(काष्ठा v4l2_ctrl *ctrl, स्थिर अक्षर *s)
अणु
	पूर्णांक rval;

	v4l2_ctrl_lock(ctrl);
	rval = __v4l2_ctrl_s_ctrl_string(ctrl, s);
	v4l2_ctrl_unlock(ctrl);

	वापस rval;
पूर्ण

/**
 * __v4l2_ctrl_s_ctrl_compound() - Unlocked variant to set a compound control
 *
 * @ctrl: The control.
 * @type: The type of the data.
 * @p:    The new compound payload.
 *
 * This sets the control's new compound payload safely by going through the
 * control framework. This function assumes the control's handler is alपढ़ोy
 * locked, allowing it to be used from within the &v4l2_ctrl_ops functions.
 *
 * This function is क्रम compound type controls only.
 */
पूर्णांक __v4l2_ctrl_s_ctrl_compound(काष्ठा v4l2_ctrl *ctrl,
				क्रमागत v4l2_ctrl_type type, स्थिर व्योम *p);

/**
 * v4l2_ctrl_s_ctrl_compound() - Helper function to set a compound control
 *	from within a driver.
 *
 * @ctrl: The control.
 * @type: The type of the data.
 * @p:    The new compound payload.
 *
 * This sets the control's new compound payload safely by going through the
 * control framework. This function will lock the control's handler, so it
 * cannot be used from within the &v4l2_ctrl_ops functions.
 *
 * This function is क्रम compound type controls only.
 */
अटल अंतरभूत पूर्णांक v4l2_ctrl_s_ctrl_compound(काष्ठा v4l2_ctrl *ctrl,
					    क्रमागत v4l2_ctrl_type type,
					    स्थिर व्योम *p)
अणु
	पूर्णांक rval;

	v4l2_ctrl_lock(ctrl);
	rval = __v4l2_ctrl_s_ctrl_compound(ctrl, type, p);
	v4l2_ctrl_unlock(ctrl);

	वापस rval;
पूर्ण

/* Helper defines क्रम area type controls */
#घोषणा __v4l2_ctrl_s_ctrl_area(ctrl, area) \
	__v4l2_ctrl_s_ctrl_compound((ctrl), V4L2_CTRL_TYPE_AREA, (area))
#घोषणा v4l2_ctrl_s_ctrl_area(ctrl, area) \
	v4l2_ctrl_s_ctrl_compound((ctrl), V4L2_CTRL_TYPE_AREA, (area))

/* Internal helper functions that deal with control events. */
बाह्य स्थिर काष्ठा v4l2_subscribed_event_ops v4l2_ctrl_sub_ev_ops;

/**
 * v4l2_ctrl_replace - Function to be used as a callback to
 *	&काष्ठा v4l2_subscribed_event_ops replace\(\)
 *
 * @old: poपूर्णांकer to काष्ठा &v4l2_event with the reported
 *	 event;
 * @new: poपूर्णांकer to काष्ठा &v4l2_event with the modअगरied
 *	 event;
 */
व्योम v4l2_ctrl_replace(काष्ठा v4l2_event *old, स्थिर काष्ठा v4l2_event *new);

/**
 * v4l2_ctrl_merge - Function to be used as a callback to
 *	&काष्ठा v4l2_subscribed_event_ops merge(\)
 *
 * @old: poपूर्णांकer to काष्ठा &v4l2_event with the reported
 *	 event;
 * @new: poपूर्णांकer to काष्ठा &v4l2_event with the merged
 *	 event;
 */
व्योम v4l2_ctrl_merge(स्थिर काष्ठा v4l2_event *old, काष्ठा v4l2_event *new);

/**
 * v4l2_ctrl_log_status - helper function to implement %VIDIOC_LOG_STATUS ioctl
 *
 * @file: poपूर्णांकer to काष्ठा file
 * @fh: unused. Kept just to be compatible to the arguments expected by
 *	&काष्ठा v4l2_ioctl_ops.vidioc_log_status.
 *
 * Can be used as a vidioc_log_status function that just dumps all controls
 * associated with the filehandle.
 */
पूर्णांक v4l2_ctrl_log_status(काष्ठा file *file, व्योम *fh);

/**
 * v4l2_ctrl_subscribe_event - Subscribes to an event
 *
 *
 * @fh: poपूर्णांकer to काष्ठा v4l2_fh
 * @sub: poपूर्णांकer to &काष्ठा v4l2_event_subscription
 *
 * Can be used as a vidioc_subscribe_event function that just subscribes
 * control events.
 */
पूर्णांक v4l2_ctrl_subscribe_event(काष्ठा v4l2_fh *fh,
				स्थिर काष्ठा v4l2_event_subscription *sub);

/**
 * v4l2_ctrl_poll - function to be used as a callback to the poll()
 *	That just polls क्रम control events.
 *
 * @file: poपूर्णांकer to काष्ठा file
 * @रुको: poपूर्णांकer to काष्ठा poll_table_काष्ठा
 */
__poll_t v4l2_ctrl_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको);

/**
 * v4l2_ctrl_request_setup - helper function to apply control values in a request
 *
 * @req: The request
 * @parent: The parent control handler ('priv' in media_request_object_find())
 *
 * This is a helper function to call the control handler's s_ctrl callback with
 * the control values contained in the request. Do note that this approach of
 * applying control values in a request is only applicable to memory-to-memory
 * devices.
 */
पूर्णांक v4l2_ctrl_request_setup(काष्ठा media_request *req,
			     काष्ठा v4l2_ctrl_handler *parent);

/**
 * v4l2_ctrl_request_complete - Complete a control handler request object
 *
 * @req: The request
 * @parent: The parent control handler ('priv' in media_request_object_find())
 *
 * This function is to be called on each control handler that may have had a
 * request object associated with it, i.e. control handlers of a driver that
 * supports requests.
 *
 * The function first obtains the values of any अस्थिर controls in the control
 * handler and attach them to the request. Then, the function completes the
 * request object.
 */
व्योम v4l2_ctrl_request_complete(काष्ठा media_request *req,
				काष्ठा v4l2_ctrl_handler *parent);

/**
 * v4l2_ctrl_request_hdl_find - Find the control handler in the request
 *
 * @req: The request
 * @parent: The parent control handler ('priv' in media_request_object_find())
 *
 * This function finds the control handler in the request. It may वापस
 * शून्य अगर not found. When करोne, you must call v4l2_ctrl_request_put_hdl()
 * with the वापसed handler poपूर्णांकer.
 *
 * If the request is not in state VALIDATING or QUEUED, then this function
 * will always वापस शून्य.
 *
 * Note that in state VALIDATING the req_queue_mutex is held, so
 * no objects can be added or deleted from the request.
 *
 * In state QUEUED it is the driver that will have to ensure this.
 */
काष्ठा v4l2_ctrl_handler *v4l2_ctrl_request_hdl_find(काष्ठा media_request *req,
					काष्ठा v4l2_ctrl_handler *parent);

/**
 * v4l2_ctrl_request_hdl_put - Put the control handler
 *
 * @hdl: Put this control handler
 *
 * This function released the control handler previously obtained from'
 * v4l2_ctrl_request_hdl_find().
 */
अटल अंतरभूत व्योम v4l2_ctrl_request_hdl_put(काष्ठा v4l2_ctrl_handler *hdl)
अणु
	अगर (hdl)
		media_request_object_put(&hdl->req_obj);
पूर्ण

/**
 * v4l2_ctrl_request_hdl_ctrl_find() - Find a control with the given ID.
 *
 * @hdl: The control handler from the request.
 * @id: The ID of the control to find.
 *
 * This function वापसs a poपूर्णांकer to the control अगर this control is
 * part of the request or शून्य otherwise.
 */
काष्ठा v4l2_ctrl *
v4l2_ctrl_request_hdl_ctrl_find(काष्ठा v4l2_ctrl_handler *hdl, u32 id);

/* Helpers क्रम ioctl_ops */

/**
 * v4l2_queryctrl - Helper function to implement
 *	:ref:`VIDIOC_QUERYCTRL <vidioc_queryctrl>` ioctl
 *
 * @hdl: poपूर्णांकer to &काष्ठा v4l2_ctrl_handler
 * @qc: poपूर्णांकer to &काष्ठा v4l2_queryctrl
 *
 * If hdl == शून्य then they will all वापस -EINVAL.
 */
पूर्णांक v4l2_queryctrl(काष्ठा v4l2_ctrl_handler *hdl, काष्ठा v4l2_queryctrl *qc);

/**
 * v4l2_query_ext_ctrl - Helper function to implement
 *	 :ref:`VIDIOC_QUERY_EXT_CTRL <vidioc_queryctrl>` ioctl
 *
 * @hdl: poपूर्णांकer to &काष्ठा v4l2_ctrl_handler
 * @qc: poपूर्णांकer to &काष्ठा v4l2_query_ext_ctrl
 *
 * If hdl == शून्य then they will all वापस -EINVAL.
 */
पूर्णांक v4l2_query_ext_ctrl(काष्ठा v4l2_ctrl_handler *hdl,
			काष्ठा v4l2_query_ext_ctrl *qc);

/**
 * v4l2_querymenu - Helper function to implement
 *	:ref:`VIDIOC_QUERYMENU <vidioc_queryctrl>` ioctl
 *
 * @hdl: poपूर्णांकer to &काष्ठा v4l2_ctrl_handler
 * @qm: poपूर्णांकer to &काष्ठा v4l2_querymenu
 *
 * If hdl == शून्य then they will all वापस -EINVAL.
 */
पूर्णांक v4l2_querymenu(काष्ठा v4l2_ctrl_handler *hdl, काष्ठा v4l2_querymenu *qm);

/**
 * v4l2_g_ctrl - Helper function to implement
 *	:ref:`VIDIOC_G_CTRL <vidioc_g_ctrl>` ioctl
 *
 * @hdl: poपूर्णांकer to &काष्ठा v4l2_ctrl_handler
 * @ctrl: poपूर्णांकer to &काष्ठा v4l2_control
 *
 * If hdl == शून्य then they will all वापस -EINVAL.
 */
पूर्णांक v4l2_g_ctrl(काष्ठा v4l2_ctrl_handler *hdl, काष्ठा v4l2_control *ctrl);

/**
 * v4l2_s_ctrl - Helper function to implement
 *	:ref:`VIDIOC_S_CTRL <vidioc_g_ctrl>` ioctl
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 * @hdl: poपूर्णांकer to &काष्ठा v4l2_ctrl_handler
 *
 * @ctrl: poपूर्णांकer to &काष्ठा v4l2_control
 *
 * If hdl == शून्य then they will all वापस -EINVAL.
 */
पूर्णांक v4l2_s_ctrl(काष्ठा v4l2_fh *fh, काष्ठा v4l2_ctrl_handler *hdl,
		काष्ठा v4l2_control *ctrl);

/**
 * v4l2_g_ext_ctrls - Helper function to implement
 *	:ref:`VIDIOC_G_EXT_CTRLS <vidioc_g_ext_ctrls>` ioctl
 *
 * @hdl: poपूर्णांकer to &काष्ठा v4l2_ctrl_handler
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 * @mdev: poपूर्णांकer to &काष्ठा media_device
 * @c: poपूर्णांकer to &काष्ठा v4l2_ext_controls
 *
 * If hdl == शून्य then they will all वापस -EINVAL.
 */
पूर्णांक v4l2_g_ext_ctrls(काष्ठा v4l2_ctrl_handler *hdl, काष्ठा video_device *vdev,
		     काष्ठा media_device *mdev, काष्ठा v4l2_ext_controls *c);

/**
 * v4l2_try_ext_ctrls - Helper function to implement
 *	:ref:`VIDIOC_TRY_EXT_CTRLS <vidioc_g_ext_ctrls>` ioctl
 *
 * @hdl: poपूर्णांकer to &काष्ठा v4l2_ctrl_handler
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 * @mdev: poपूर्णांकer to &काष्ठा media_device
 * @c: poपूर्णांकer to &काष्ठा v4l2_ext_controls
 *
 * If hdl == शून्य then they will all वापस -EINVAL.
 */
पूर्णांक v4l2_try_ext_ctrls(काष्ठा v4l2_ctrl_handler *hdl,
		       काष्ठा video_device *vdev,
		       काष्ठा media_device *mdev,
		       काष्ठा v4l2_ext_controls *c);

/**
 * v4l2_s_ext_ctrls - Helper function to implement
 *	:ref:`VIDIOC_S_EXT_CTRLS <vidioc_g_ext_ctrls>` ioctl
 *
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 * @hdl: poपूर्णांकer to &काष्ठा v4l2_ctrl_handler
 * @vdev: poपूर्णांकer to &काष्ठा video_device
 * @mdev: poपूर्णांकer to &काष्ठा media_device
 * @c: poपूर्णांकer to &काष्ठा v4l2_ext_controls
 *
 * If hdl == शून्य then they will all वापस -EINVAL.
 */
पूर्णांक v4l2_s_ext_ctrls(काष्ठा v4l2_fh *fh, काष्ठा v4l2_ctrl_handler *hdl,
		     काष्ठा video_device *vdev,
		     काष्ठा media_device *mdev,
		     काष्ठा v4l2_ext_controls *c);

/**
 * v4l2_ctrl_subdev_subscribe_event - Helper function to implement
 *	as a &काष्ठा v4l2_subdev_core_ops subscribe_event function
 *	that just subscribes control events.
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 * @fh: poपूर्णांकer to &काष्ठा v4l2_fh
 * @sub: poपूर्णांकer to &काष्ठा v4l2_event_subscription
 */
पूर्णांक v4l2_ctrl_subdev_subscribe_event(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_fh *fh,
				     काष्ठा v4l2_event_subscription *sub);

/**
 * v4l2_ctrl_subdev_log_status - Log all controls owned by subdev's control
 *	 handler.
 *
 * @sd: poपूर्णांकer to &काष्ठा v4l2_subdev
 */
पूर्णांक v4l2_ctrl_subdev_log_status(काष्ठा v4l2_subdev *sd);

/**
 * v4l2_ctrl_new_fwnode_properties() - Register controls क्रम the device
 *				       properties
 *
 * @hdl: poपूर्णांकer to &काष्ठा v4l2_ctrl_handler to रेजिस्टर controls on
 * @ctrl_ops: poपूर्णांकer to &काष्ठा v4l2_ctrl_ops to रेजिस्टर controls with
 * @p: poपूर्णांकer to &काष्ठा v4l2_fwnode_device_properties
 *
 * This function रेजिस्टरs controls associated to device properties, using the
 * property values contained in @p parameter, अगर the property has been set to
 * a value.
 *
 * Currently the following v4l2 controls are parsed and रेजिस्टरed:
 * - V4L2_CID_CAMERA_ORIENTATION
 * - V4L2_CID_CAMERA_SENSOR_ROTATION;
 *
 * Controls alपढ़ोy रेजिस्टरed by the caller with the @hdl control handler are
 * not overwritten. Callers should रेजिस्टर the controls they want to handle
 * themselves beक्रमe calling this function.
 *
 * Return: 0 on success, a negative error code on failure.
 */
पूर्णांक v4l2_ctrl_new_fwnode_properties(काष्ठा v4l2_ctrl_handler *hdl,
				    स्थिर काष्ठा v4l2_ctrl_ops *ctrl_ops,
				    स्थिर काष्ठा v4l2_fwnode_device_properties *p);
#पूर्ण_अगर
