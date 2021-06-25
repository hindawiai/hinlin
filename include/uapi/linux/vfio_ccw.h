<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Interfaces क्रम vfio-ccw
 *
 * Copyright IBM Corp. 2017
 *
 * Author(s): Dong Jia Shi <bjsdjshi@linux.vnet.ibm.com>
 */

#अगर_अघोषित _VFIO_CCW_H_
#घोषणा _VFIO_CCW_H_

#समावेश <linux/types.h>

/* used क्रम START SUBCHANNEL, always present */
काष्ठा ccw_io_region अणु
#घोषणा ORB_AREA_SIZE 12
	__u8	orb_area[ORB_AREA_SIZE];
#घोषणा SCSW_AREA_SIZE 12
	__u8	scsw_area[SCSW_AREA_SIZE];
#घोषणा IRB_AREA_SIZE 96
	__u8	irb_area[IRB_AREA_SIZE];
	__u32	ret_code;
पूर्ण __packed;

/*
 * used क्रम processing commands that trigger asynchronous actions
 * Note: this is controlled by a capability
 */
#घोषणा VFIO_CCW_ASYNC_CMD_HSCH (1 << 0)
#घोषणा VFIO_CCW_ASYNC_CMD_CSCH (1 << 1)
काष्ठा ccw_cmd_region अणु
	__u32 command;
	__u32 ret_code;
पूर्ण __packed;

/*
 * Used क्रम processing commands that पढ़ो the subchannel-inक्रमmation block
 * Reading this region triggers a stsch() to hardware
 * Note: this is controlled by a capability
 */
काष्ठा ccw_schib_region अणु
#घोषणा SCHIB_AREA_SIZE 52
	__u8 schib_area[SCHIB_AREA_SIZE];
पूर्ण __packed;

/*
 * Used क्रम वापसing a Channel Report Word to userspace.
 * Note: this is controlled by a capability
 */
काष्ठा ccw_crw_region अणु
	__u32 crw;
	__u32 pad;
पूर्ण __packed;

#पूर्ण_अगर
