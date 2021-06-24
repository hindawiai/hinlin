<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 *  Copyright (C) 2005 Mike Isely <isely@pobox.com>
 */
#अगर_अघोषित __PVRUSB2_DEBUG_H
#घोषणा __PVRUSB2_DEBUG_H

बाह्य पूर्णांक pvrusb2_debug;

#घोषणा pvr2_trace(msk, fmt, arg...) करो अणुअगर (msk & pvrusb2_debug) pr_info("pvrusb2: " fmt "\n", ##arg); पूर्ण जबतक (0)

/* These are listed in *rough* order of decreasing usefulness and
   increasing noise level. */
#घोषणा PVR2_TRACE_INFO       (1 <<  0) /* Normal messages */
#घोषणा PVR2_TRACE_ERROR_LEGS (1 <<  1) /* error messages */
#घोषणा PVR2_TRACE_TOLERANCE  (1 <<  2) /* track tolerance-affected errors */
#घोषणा PVR2_TRACE_TRAP       (1 <<  3) /* Trap & report app misbehavior */
#घोषणा PVR2_TRACE_STD        (1 <<  4) /* Log video standard stuff */
#घोषणा PVR2_TRACE_INIT       (1 <<  5) /* misc initialization steps */
#घोषणा PVR2_TRACE_START_STOP (1 <<  6) /* Streaming start / stop */
#घोषणा PVR2_TRACE_CTL        (1 <<  7) /* commit of control changes */
#घोषणा PVR2_TRACE_STATE      (1 <<  8) /* Device state changes */
#घोषणा PVR2_TRACE_STBITS     (1 <<  9) /* Inभागidual bit state changes */
#घोषणा PVR2_TRACE_EEPROM     (1 << 10) /* eeprom parsing / report */
#घोषणा PVR2_TRACE_STRUCT     (1 << 11) /* पूर्णांकernal काष्ठा creation */
#घोषणा PVR2_TRACE_OPEN_CLOSE (1 << 12) /* application खोलो / बंद */
#घोषणा PVR2_TRACE_CTXT       (1 << 13) /* Main context tracking */
#घोषणा PVR2_TRACE_SYSFS      (1 << 14) /* Sysfs driven I/O */
#घोषणा PVR2_TRACE_FIRMWARE   (1 << 15) /* firmware upload actions */
#घोषणा PVR2_TRACE_CHIPS      (1 << 16) /* chip broadcast operation */
#घोषणा PVR2_TRACE_I2C        (1 << 17) /* I2C related stuff */
#घोषणा PVR2_TRACE_I2C_CMD    (1 << 18) /* Software commands to I2C modules */
#घोषणा PVR2_TRACE_I2C_CORE   (1 << 19) /* I2C core debugging */
#घोषणा PVR2_TRACE_I2C_TRAF   (1 << 20) /* I2C traffic through the adapter */
#घोषणा PVR2_TRACE_V4LIOCTL   (1 << 21) /* v4l ioctl details */
#घोषणा PVR2_TRACE_ENCODER    (1 << 22) /* mpeg2 encoder operation */
#घोषणा PVR2_TRACE_BUF_POOL   (1 << 23) /* Track buffer pool management */
#घोषणा PVR2_TRACE_BUF_FLOW   (1 << 24) /* Track buffer flow in प्रणाली */
#घोषणा PVR2_TRACE_DATA_FLOW  (1 << 25) /* Track data flow */
#घोषणा PVR2_TRACE_DEBUGIFC   (1 << 26) /* Debug पूर्णांकerface actions */
#घोषणा PVR2_TRACE_GPIO       (1 << 27) /* GPIO state bit changes */
#घोषणा PVR2_TRACE_DVB_FEED   (1 << 28) /* DVB transport feed debug */


#पूर्ण_अगर /* __PVRUSB2_HDW_INTERNAL_H */
