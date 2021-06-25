<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Management Complex (MC) userspace खुला पूर्णांकerface
 *
 * Copyright 2021 NXP
 *
 */
#अगर_अघोषित _UAPI_FSL_MC_H_
#घोषणा _UAPI_FSL_MC_H_

#समावेश <linux/types.h>

#घोषणा MC_CMD_NUM_OF_PARAMS	7

/**
 * काष्ठा fsl_mc_command - Management Complex (MC) command काष्ठाure
 * @header: MC command header
 * @params: MC command parameters
 *
 * Used by FSL_MC_SEND_MC_COMMAND
 */
काष्ठा fsl_mc_command अणु
	__le64 header;
	__le64 params[MC_CMD_NUM_OF_PARAMS];
पूर्ण;

#घोषणा FSL_MC_SEND_CMD_IOCTL_TYPE	'R'
#घोषणा FSL_MC_SEND_CMD_IOCTL_SEQ	0xE0

#घोषणा FSL_MC_SEND_MC_COMMAND \
	_IOWR(FSL_MC_SEND_CMD_IOCTL_TYPE, FSL_MC_SEND_CMD_IOCTL_SEQ, \
	काष्ठा fsl_mc_command)

#पूर्ण_अगर /* _UAPI_FSL_MC_H_ */
