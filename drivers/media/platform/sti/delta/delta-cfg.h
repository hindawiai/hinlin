<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Author: Hugues Fruchet <hugues.fruchet@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित DELTA_CFG_H
#घोषणा DELTA_CFG_H

#घोषणा DELTA_FW_VERSION "21.1-3"

#घोषणा DELTA_MIN_WIDTH  32
#घोषणा DELTA_MAX_WIDTH  4096
#घोषणा DELTA_MIN_HEIGHT 32
#घोषणा DELTA_MAX_HEIGHT 2400

/* DELTA requires a 32x32 pixels alignment क्रम frames */
#घोषणा DELTA_WIDTH_ALIGNMENT    32
#घोषणा DELTA_HEIGHT_ALIGNMENT   32

#घोषणा DELTA_DEFAULT_WIDTH  DELTA_MIN_WIDTH
#घोषणा DELTA_DEFAULT_HEIGHT DELTA_MIN_HEIGHT
#घोषणा DELTA_DEFAULT_FRAMEFORMAT  V4L2_PIX_FMT_NV12
#घोषणा DELTA_DEFAULT_STREAMFORMAT V4L2_PIX_FMT_MJPEG

#घोषणा DELTA_MAX_RESO (DELTA_MAX_WIDTH * DELTA_MAX_HEIGHT)

/* guard value क्रम number of access units */
#घोषणा DELTA_MAX_AUS 10

/* IP perf dependent, can be tuned */
#घोषणा DELTA_PEAK_FRAME_SMOOTHING 2

/*
 * guard output frame count:
 * - at least 1 frame needed क्रम display
 * - at worst 21
 *   ( max h264 dpb (16) +
 *     decoding peak smoothing (2) +
 *     user display pipeline (3) )
 */
#घोषणा DELTA_MIN_FRAME_USER    1
#घोषणा DELTA_MAX_DPB           16
#घोषणा DELTA_MAX_FRAME_USER    3 /* platक्रमm/use-हाल dependent */
#घोषणा DELTA_MAX_FRAMES (DELTA_MAX_DPB + DELTA_PEAK_FRAME_SMOOTHING +\
			  DELTA_MAX_FRAME_USER)

#अगर DELTA_MAX_FRAMES > VIDEO_MAX_FRAME
#अघोषित DELTA_MAX_FRAMES
#घोषणा DELTA_MAX_FRAMES (VIDEO_MAX_FRAME)
#पूर्ण_अगर

/* extra space to be allocated to store codec specअगरic data per frame */
#घोषणा DELTA_MAX_FRAME_PRIV_SIZE 100

/* PM runसमय स्वतः घातer-off after 5ms of inactivity */
#घोषणा DELTA_HW_AUTOSUSPEND_DELAY_MS 5

#घोषणा DELTA_MAX_DECODERS 10
#अगर_घोषित CONFIG_VIDEO_STI_DELTA_MJPEG
बाह्य स्थिर काष्ठा delta_dec mjpegdec;
#पूर्ण_अगर

#पूर्ण_अगर /* DELTA_CFG_H */
