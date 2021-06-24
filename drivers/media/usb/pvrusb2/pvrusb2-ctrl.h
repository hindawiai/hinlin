<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_CTRL_H
#घोषणा __PVRUSB2_CTRL_H

काष्ठा pvr2_ctrl;

क्रमागत pvr2_ctl_type अणु
	pvr2_ctl_पूर्णांक = 0,
	pvr2_ctl_क्रमागत = 1,
	pvr2_ctl_biपंचांगask = 2,
	pvr2_ctl_bool = 3,
पूर्ण;


/* Set the given control. */
पूर्णांक pvr2_ctrl_set_value(काष्ठा pvr2_ctrl *,पूर्णांक val);

/* Set/clear specअगरic bits of the given control. */
पूर्णांक pvr2_ctrl_set_mask_value(काष्ठा pvr2_ctrl *,पूर्णांक mask,पूर्णांक val);

/* Get the current value of the given control. */
पूर्णांक pvr2_ctrl_get_value(काष्ठा pvr2_ctrl *,पूर्णांक *valptr);

/* Retrieve control's type */
क्रमागत pvr2_ctl_type pvr2_ctrl_get_type(काष्ठा pvr2_ctrl *);

/* Retrieve control's maximum value (पूर्णांक type) */
पूर्णांक pvr2_ctrl_get_max(काष्ठा pvr2_ctrl *);

/* Retrieve control's minimum value (पूर्णांक type) */
पूर्णांक pvr2_ctrl_get_min(काष्ठा pvr2_ctrl *);

/* Retrieve control's शेष value (any type) */
पूर्णांक pvr2_ctrl_get_def(काष्ठा pvr2_ctrl *, पूर्णांक *valptr);

/* Retrieve control's क्रमागतeration count (क्रमागत only) */
पूर्णांक pvr2_ctrl_get_cnt(काष्ठा pvr2_ctrl *);

/* Retrieve control's valid mask bits (bit mask only) */
पूर्णांक pvr2_ctrl_get_mask(काष्ठा pvr2_ctrl *);

/* Retrieve the control's name */
स्थिर अक्षर *pvr2_ctrl_get_name(काष्ठा pvr2_ctrl *);

/* Retrieve the control's desc */
स्थिर अक्षर *pvr2_ctrl_get_desc(काष्ठा pvr2_ctrl *);

/* Retrieve a control क्रमागतeration or bit mask value */
पूर्णांक pvr2_ctrl_get_valname(काष्ठा pvr2_ctrl *,पूर्णांक,अक्षर *,अचिन्हित पूर्णांक,
			  अचिन्हित पूर्णांक *);

/* Return true अगर control is writable */
पूर्णांक pvr2_ctrl_is_writable(काष्ठा pvr2_ctrl *);

/* Return V4L flags value क्रम control (or zero अगर there is no v4l control
   actually under this control) */
अचिन्हित पूर्णांक pvr2_ctrl_get_v4lflags(काष्ठा pvr2_ctrl *);

/* Return V4L ID क्रम this control or zero अगर none */
पूर्णांक pvr2_ctrl_get_v4lid(काष्ठा pvr2_ctrl *);

/* Return true अगर control has custom symbolic representation */
पूर्णांक pvr2_ctrl_has_custom_symbols(काष्ठा pvr2_ctrl *);

/* Convert a given mask/val to a custom symbolic value */
पूर्णांक pvr2_ctrl_custom_value_to_sym(काष्ठा pvr2_ctrl *,
				  पूर्णांक mask,पूर्णांक val,
				  अक्षर *buf,अचिन्हित पूर्णांक maxlen,
				  अचिन्हित पूर्णांक *len);

/* Convert a symbolic value to a mask/value pair */
पूर्णांक pvr2_ctrl_custom_sym_to_value(काष्ठा pvr2_ctrl *,
				  स्थिर अक्षर *buf,अचिन्हित पूर्णांक len,
				  पूर्णांक *maskptr,पूर्णांक *valptr);

/* Convert a given mask/val to a symbolic value */
पूर्णांक pvr2_ctrl_value_to_sym(काष्ठा pvr2_ctrl *,
			   पूर्णांक mask,पूर्णांक val,
			   अक्षर *buf,अचिन्हित पूर्णांक maxlen,
			   अचिन्हित पूर्णांक *len);

/* Convert a symbolic value to a mask/value pair */
पूर्णांक pvr2_ctrl_sym_to_value(काष्ठा pvr2_ctrl *,
			   स्थिर अक्षर *buf,अचिन्हित पूर्णांक len,
			   पूर्णांक *maskptr,पूर्णांक *valptr);

/* Convert a given mask/val to a symbolic value - must alपढ़ोy be
   inside of critical region. */
पूर्णांक pvr2_ctrl_value_to_sym_पूर्णांकernal(काष्ठा pvr2_ctrl *,
			   पूर्णांक mask,पूर्णांक val,
			   अक्षर *buf,अचिन्हित पूर्णांक maxlen,
			   अचिन्हित पूर्णांक *len);

#पूर्ण_अगर /* __PVRUSB2_CTRL_H */
