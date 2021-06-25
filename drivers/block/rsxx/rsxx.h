<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
* Filename: rsxx.h
*
* Authors: Joshua Morris <josh.h.morris@us.ibm.com>
*	Philip Kelleher <pjk1939@linux.vnet.ibm.com>
*
* (C) Copyright 2013 IBM Corporation
*/

#अगर_अघोषित __RSXX_H__
#घोषणा __RSXX_H__

/*----------------- IOCTL Definitions -------------------*/

#घोषणा RSXX_MAX_DATA 8

काष्ठा rsxx_reg_access अणु
	__u32 addr;
	__u32 cnt;
	__u32 stat;
	__u32 stream;
	__u32 data[RSXX_MAX_DATA];
पूर्ण;

#घोषणा RSXX_MAX_REG_CNT	(RSXX_MAX_DATA * (माप(__u32)))

#घोषणा RSXX_IOC_MAGIC 'r'

#घोषणा RSXX_GETREG _IOWR(RSXX_IOC_MAGIC, 0x20, काष्ठा rsxx_reg_access)
#घोषणा RSXX_SETREG _IOWR(RSXX_IOC_MAGIC, 0x21, काष्ठा rsxx_reg_access)

#पूर्ण_अगर /* __RSXX_H_ */
