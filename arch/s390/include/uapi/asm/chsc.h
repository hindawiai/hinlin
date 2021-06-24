<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * ioctl पूर्णांकerface क्रम /dev/chsc
 *
 * Copyright IBM Corp. 2008, 2012
 * Author(s): Cornelia Huck <cornelia.huck@de.ibm.com>
 */

#अगर_अघोषित _ASM_CHSC_H
#घोषणा _ASM_CHSC_H

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>
#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/schid.h>

#घोषणा CHSC_SIZE 0x1000

काष्ठा chsc_async_header अणु
	__u16 length;
	__u16 code;
	__u32 cmd_dependend;
	__u32 key : 4;
	__u32 : 28;
	काष्ठा subchannel_id sid;
पूर्ण;

काष्ठा chsc_async_area अणु
	काष्ठा chsc_async_header header;
	__u8 data[CHSC_SIZE - माप(काष्ठा chsc_async_header)];
पूर्ण;

काष्ठा chsc_header अणु
	__u16 length;
	__u16 code;
पूर्ण;

काष्ठा chsc_sync_area अणु
	काष्ठा chsc_header header;
	__u8 data[CHSC_SIZE - माप(काष्ठा chsc_header)];
पूर्ण;

काष्ठा chsc_response_काष्ठा अणु
	__u16 length;
	__u16 code;
	__u32 parms;
	__u8 data[CHSC_SIZE - 2 * माप(__u16) - माप(__u32)];
पूर्ण;

काष्ठा chsc_chp_cd अणु
	काष्ठा chp_id chpid;
	पूर्णांक m;
	पूर्णांक fmt;
	काष्ठा chsc_response_काष्ठा cpcb;
पूर्ण;

काष्ठा chsc_cu_cd अणु
	__u16 cun;
	__u8 cssid;
	पूर्णांक m;
	पूर्णांक fmt;
	काष्ठा chsc_response_काष्ठा cucb;
पूर्ण;

काष्ठा chsc_sch_cud अणु
	काष्ठा subchannel_id schid;
	पूर्णांक fmt;
	काष्ठा chsc_response_काष्ठा scub;
पूर्ण;

काष्ठा conf_id अणु
	पूर्णांक m;
	__u8 cssid;
	__u8 ssid;
पूर्ण;

काष्ठा chsc_conf_info अणु
	काष्ठा conf_id id;
	पूर्णांक fmt;
	काष्ठा chsc_response_काष्ठा scid;
पूर्ण;

काष्ठा ccl_parm_chpid अणु
	पूर्णांक m;
	काष्ठा chp_id chp;
पूर्ण;

काष्ठा ccl_parm_cssids अणु
	__u8 f_cssid;
	__u8 l_cssid;
पूर्ण;

काष्ठा chsc_comp_list अणु
	काष्ठा अणु
		क्रमागत अणु
			CCL_CU_ON_CHP = 1,
			CCL_CHP_TYPE_CAP = 2,
			CCL_CSS_IMG = 4,
			CCL_CSS_IMG_CONF_CHAR = 5,
			CCL_IOP_CHP = 6,
		पूर्ण ctype;
		पूर्णांक fmt;
		काष्ठा ccl_parm_chpid chpid;
		काष्ठा ccl_parm_cssids cssids;
	पूर्ण req;
	काष्ठा chsc_response_काष्ठा sccl;
पूर्ण;

काष्ठा chsc_dcal अणु
	काष्ठा अणु
		क्रमागत अणु
			DCAL_CSS_IID_PN = 4,
		पूर्ण atype;
		__u32 list_parm[2];
		पूर्णांक fmt;
	पूर्ण req;
	काष्ठा chsc_response_काष्ठा sdcal;
पूर्ण;

काष्ठा chsc_cpd_info अणु
	काष्ठा chp_id chpid;
	पूर्णांक m;
	पूर्णांक fmt;
	पूर्णांक rfmt;
	पूर्णांक c;
	काष्ठा chsc_response_काष्ठा chpdb;
पूर्ण;

#घोषणा CHSC_IOCTL_MAGIC 'c'

#घोषणा CHSC_START _IOWR(CHSC_IOCTL_MAGIC, 0x81, काष्ठा chsc_async_area)
#घोषणा CHSC_INFO_CHANNEL_PATH _IOWR(CHSC_IOCTL_MAGIC, 0x82, \
				    काष्ठा chsc_chp_cd)
#घोषणा CHSC_INFO_CU _IOWR(CHSC_IOCTL_MAGIC, 0x83, काष्ठा chsc_cu_cd)
#घोषणा CHSC_INFO_SCH_CU _IOWR(CHSC_IOCTL_MAGIC, 0x84, काष्ठा chsc_sch_cud)
#घोषणा CHSC_INFO_CI _IOWR(CHSC_IOCTL_MAGIC, 0x85, काष्ठा chsc_conf_info)
#घोषणा CHSC_INFO_CCL _IOWR(CHSC_IOCTL_MAGIC, 0x86, काष्ठा chsc_comp_list)
#घोषणा CHSC_INFO_CPD _IOWR(CHSC_IOCTL_MAGIC, 0x87, काष्ठा chsc_cpd_info)
#घोषणा CHSC_INFO_DCAL _IOWR(CHSC_IOCTL_MAGIC, 0x88, काष्ठा chsc_dcal)
#घोषणा CHSC_START_SYNC _IOWR(CHSC_IOCTL_MAGIC, 0x89, काष्ठा chsc_sync_area)
#घोषणा CHSC_ON_CLOSE_SET _IOWR(CHSC_IOCTL_MAGIC, 0x8a, काष्ठा chsc_async_area)
#घोषणा CHSC_ON_CLOSE_REMOVE _IO(CHSC_IOCTL_MAGIC, 0x8b)

#पूर्ण_अगर
