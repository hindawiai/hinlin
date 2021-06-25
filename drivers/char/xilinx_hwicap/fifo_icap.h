<शैली गुरु>
/*****************************************************************************
 *
 *     Author: Xilinx, Inc.
 *
 *     This program is मुक्त software; you can redistribute it and/or modअगरy it
 *     under the terms of the GNU General Public License as published by the
 *     Free Software Foundation; either version 2 of the License, or (at your
 *     option) any later version.
 *
 *     XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
 *     AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
 *     SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
 *     OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
 *     APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
 *     THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
 *     AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
 *     FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
 *     WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
 *     IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
 *     REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
 *     INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *     FOR A PARTICULAR PURPOSE.
 *
 *     (c) Copyright 2007-2008 Xilinx Inc.
 *     All rights reserved.
 *
 *     You should have received a copy of the GNU General Public License aदीर्घ
 *     with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 *     675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *****************************************************************************/

#अगर_अघोषित XILINX_FIFO_ICAP_H_	/* prevent circular inclusions */
#घोषणा XILINX_FIFO_ICAP_H_	/* by using protection macros */

#समावेश <linux/types.h>
#समावेश <linux/cdev.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/पन.स>
#समावेश "xilinx_hwicap.h"

/* Reads पूर्णांकegers from the device पूर्णांकo the storage buffer. */
पूर्णांक fअगरo_icap_get_configuration(
		काष्ठा hwicap_drvdata *drvdata,
		u32 *FrameBuffer,
		u32 NumWords);

/* Writes पूर्णांकegers to the device from the storage buffer. */
पूर्णांक fअगरo_icap_set_configuration(
		काष्ठा hwicap_drvdata *drvdata,
		u32 *FrameBuffer,
		u32 NumWords);

u32 fअगरo_icap_get_status(काष्ठा hwicap_drvdata *drvdata);
व्योम fअगरo_icap_reset(काष्ठा hwicap_drvdata *drvdata);
व्योम fअगरo_icap_flush_fअगरo(काष्ठा hwicap_drvdata *drvdata);

#पूर्ण_अगर
