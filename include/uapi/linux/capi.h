<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* $Id: capi.h,v 1.4.6.1 2001/09/23 22:25:05 kai Exp $
 * 
 * CAPI 2.0 Interface क्रम Linux
 * 
 * Copyright 1997 by Carsten Paeth (calle@calle.in-berlin.de)
 * 
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#अगर_अघोषित __LINUX_CAPI_H__
#घोषणा __LINUX_CAPI_H__

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>
#अगर_अघोषित __KERNEL__
#समावेश <linux/kernelcapi.h>
#पूर्ण_अगर

/*
 * CAPI_REGISTER
 */

प्रकार काष्ठा capi_रेजिस्टर_params अणु	/* CAPI_REGISTER */
	__u32 level3cnt;	/* No. of simulatneous user data connections */
	__u32 datablkcnt;	/* No. of buffered data messages */
	__u32 datablklen;	/* Size of buffered data messages */
पूर्ण capi_रेजिस्टर_params;

#घोषणा	CAPI_REGISTER	_IOW('C',0x01,काष्ठा capi_रेजिस्टर_params)

/*
 * CAPI_GET_MANUFACTURER
 */

#घोषणा CAPI_MANUFACTURER_LEN		64

#घोषणा	CAPI_GET_MANUFACTURER	_IOWR('C',0x06,पूर्णांक)	/* broken: wanted size 64 (CAPI_MANUFACTURER_LEN) */

/*
 * CAPI_GET_VERSION
 */

प्रकार काष्ठा capi_version अणु
	__u32 majorversion;
	__u32 minorversion;
	__u32 majormanuversion;
	__u32 minormanuversion;
पूर्ण capi_version;

#घोषणा CAPI_GET_VERSION	_IOWR('C',0x07,काष्ठा capi_version)

/*
 * CAPI_GET_SERIAL
 */

#घोषणा CAPI_SERIAL_LEN		8
#घोषणा CAPI_GET_SERIAL		_IOWR('C',0x08,पूर्णांक)	/* broken: wanted size 8 (CAPI_SERIAL_LEN) */

/*
 * CAPI_GET_PROखाता
 */

प्रकार काष्ठा capi_profile अणु
	__u16 ncontroller;	/* number of installed controller */
	__u16 nbchannel;	/* number of B-Channels */
	__u32 goptions;		/* global options */
	__u32 support1;		/* B1 protocols support */
	__u32 support2;		/* B2 protocols support */
	__u32 support3;		/* B3 protocols support */
	__u32 reserved[6];	/* reserved */
	__u32 manu[5];		/* manufacturer specअगरic inक्रमmation */
पूर्ण capi_profile;

#घोषणा CAPI_GET_PROखाता	_IOWR('C',0x09,काष्ठा capi_profile)

प्रकार काष्ठा capi_manufacturer_cmd अणु
	अचिन्हित दीर्घ cmd;
	व्योम __user *data;
पूर्ण capi_manufacturer_cmd;

/*
 * CAPI_MANUFACTURER_CMD
 */

#घोषणा CAPI_MANUFACTURER_CMD	_IOWR('C',0x20, काष्ठा capi_manufacturer_cmd)

/*
 * CAPI_GET_ERRCODE
 * capi errcode is set, * अगर पढ़ो, ग_लिखो, or ioctl वापसs EIO,
 * ioctl वापसs errcode directly, and in arg, अगर != 0
 */

#घोषणा CAPI_GET_ERRCODE	_IOR('C',0x21, __u16)

/*
 * CAPI_INSTALLED
 */
#घोषणा CAPI_INSTALLED		_IOR('C',0x22, __u16)


/*
 * member contr is input क्रम
 * CAPI_GET_MANUFACTURER, CAPI_GET_VERSION, CAPI_GET_SERIAL
 * and CAPI_GET_PROखाता
 */
प्रकार जोड़ capi_ioctl_काष्ठा अणु
	__u32 contr;
	capi_रेजिस्टर_params rparams;
	__u8 manufacturer[CAPI_MANUFACTURER_LEN];
	capi_version version;
	__u8 serial[CAPI_SERIAL_LEN];
	capi_profile profile;
	capi_manufacturer_cmd cmd;
	__u16 errcode;
पूर्ण capi_ioctl_काष्ठा;

/*
 * Middleware extension
 */

#घोषणा CAPIFLAG_HIGHJACKING	0x0001

#घोषणा CAPI_GET_FLAGS		_IOR('C',0x23, अचिन्हित)
#घोषणा CAPI_SET_FLAGS		_IOR('C',0x24, अचिन्हित)
#घोषणा CAPI_CLR_FLAGS		_IOR('C',0x25, अचिन्हित)

#घोषणा CAPI_NCCI_OPENCOUNT	_IOR('C',0x26, अचिन्हित)

#घोषणा CAPI_NCCI_GETUNIT	_IOR('C',0x27, अचिन्हित)

#पूर्ण_अगर				/* __LINUX_CAPI_H__ */
