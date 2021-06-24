<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: upc.h
 *
 * Purpose: Macros to access device
 *
 * Author: Tevin Chen
 *
 * Date: Mar 17, 1997
 *
 */

#अगर_अघोषित __UPC_H__
#घोषणा __UPC_H__

#समावेश "device.h"

/*---------------------  Export Definitions -------------------------*/

/* For memory mapped IO */

#घोषणा VNSvInPortB(dwIOAddress, pbyData) \
	(*(pbyData) = ioपढ़ो8(dwIOAddress))

#घोषणा VNSvInPortW(dwIOAddress, pwData) \
	(*(pwData) = ioपढ़ो16(dwIOAddress))

#घोषणा VNSvInPortD(dwIOAddress, pdwData) \
	(*(pdwData) = ioपढ़ो32(dwIOAddress))

#घोषणा VNSvOutPortB(dwIOAddress, byData) \
	ioग_लिखो8((u8)(byData), dwIOAddress)

#घोषणा VNSvOutPortW(dwIOAddress, wData) \
	ioग_लिखो16((u16)(wData), dwIOAddress)

#घोषणा VNSvOutPortD(dwIOAddress, dwData) \
	ioग_लिखो32((u32)(dwData), dwIOAddress)

#घोषणा PCAvDelayByIO(uDelayUnit)				\
करो अणु								\
	अचिन्हित अक्षर byData;					\
	अचिन्हित दीर्घ ii;					\
								\
	अगर (uDelayUnit <= 50) अणु					\
		udelay(uDelayUnit);				\
	पूर्ण अन्यथा अणु						\
		क्रम (ii = 0; ii < (uDelayUnit); ii++)		\
			byData = inb(0x61);			\
	पूर्ण							\
पूर्ण जबतक (0)

/*---------------------  Export Classes  ----------------------------*/

/*---------------------  Export Variables  --------------------------*/

/*---------------------  Export Functions  --------------------------*/

#पूर्ण_अगर /* __UPC_H__ */
