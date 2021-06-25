<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright (c) 2010-2014 Broadcom. All rights reserved. */

#अगर_अघोषित VCHIQ_CFG_H
#घोषणा VCHIQ_CFG_H

#घोषणा VCHIQ_MAGIC              VCHIQ_MAKE_FOURCC('V', 'C', 'H', 'I')
/* The version of VCHIQ - change with any non-trivial change */
#घोषणा VCHIQ_VERSION            8
/*
 * The minimum compatible version - update to match VCHIQ_VERSION with any
 * incompatible change
 */
#घोषणा VCHIQ_VERSION_MIN        3

/* The version that पूर्णांकroduced the VCHIQ_IOC_LIB_VERSION ioctl */
#घोषणा VCHIQ_VERSION_LIB_VERSION 7

/* The version that पूर्णांकroduced the VCHIQ_IOC_CLOSE_DELIVERED ioctl */
#घोषणा VCHIQ_VERSION_CLOSE_DELIVERED 7

/* The version that made it safe to use SYNCHRONOUS mode */
#घोषणा VCHIQ_VERSION_SYNCHRONOUS_MODE 8

#घोषणा VCHIQ_MAX_STATES         1
#घोषणा VCHIQ_MAX_SERVICES       4096
#घोषणा VCHIQ_MAX_SLOTS          128
#घोषणा VCHIQ_MAX_SLOTS_PER_SIDE 64

#घोषणा VCHIQ_NUM_CURRENT_BULKS        32
#घोषणा VCHIQ_NUM_SERVICE_BULKS        4

#अगर_अघोषित VCHIQ_ENABLE_DEBUG
#घोषणा VCHIQ_ENABLE_DEBUG             1
#पूर्ण_अगर

#अगर_अघोषित VCHIQ_ENABLE_STATS
#घोषणा VCHIQ_ENABLE_STATS             1
#पूर्ण_अगर

#पूर्ण_अगर /* VCHIQ_CFG_H */
