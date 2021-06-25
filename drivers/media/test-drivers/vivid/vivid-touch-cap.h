<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * vivid-touch-cap.h - touch support functions.
 */
#अगर_अघोषित _VIVID_TOUCH_CAP_H_
#घोषणा _VIVID_TOUCH_CAP_H_

#घोषणा VIVID_TCH_HEIGHT	12
#घोषणा VIVID_TCH_WIDTH		21
#घोषणा VIVID_MIN_PRESSURE	180
#घोषणा VIVID_PRESSURE_LIMIT	40
#घोषणा TCH_SEQ_COUNT		16
#घोषणा TCH_PATTERN_COUNT	12

क्रमागत vivid_tch_test अणु
	SINGLE_TAP,
	DOUBLE_TAP,
	TRIPLE_TAP,
	MOVE_LEFT_TO_RIGHT,
	ZOOM_IN,
	ZOOM_OUT,
	PALM_PRESS,
	MULTIPLE_PRESS,
	TEST_CASE_MAX
पूर्ण;

बाह्य स्थिर काष्ठा vb2_ops vivid_touch_cap_qops;

पूर्णांक vivid_क्रमागत_fmt_tch(काष्ठा file *file, व्योम  *priv, काष्ठा v4l2_fmtdesc *f);
पूर्णांक vivid_g_fmt_tch(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vivid_g_fmt_tch_mplane(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_क्रमmat *f);
पूर्णांक vivid_क्रमागत_input_tch(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_input *inp);
पूर्णांक vivid_g_input_tch(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i);
पूर्णांक vivid_s_input_tch(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i);
व्योम vivid_fillbuff_tch(काष्ठा vivid_dev *dev, काष्ठा vivid_buffer *buf);
पूर्णांक vivid_set_touch(काष्ठा vivid_dev *dev, अचिन्हित पूर्णांक i);
पूर्णांक vivid_g_parm_tch(काष्ठा file *file, व्योम *priv,
		     काष्ठा v4l2_streamparm *parm);
#पूर्ण_अगर
