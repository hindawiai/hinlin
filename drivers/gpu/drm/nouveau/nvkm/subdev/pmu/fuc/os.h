<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_PWR_OS_H__
#घोषणा __NVKM_PWR_OS_H__

/* Process names */
#घोषणा PROC_KERN 0x52544e49
#घोषणा PROC_IDLE 0x454c4449
#घोषणा PROC_HOST 0x54534f48
#घोषणा PROC_MEMX 0x584d454d
#घोषणा PROC_PERF 0x46524550
#घोषणा PROC_I2C_ 0x5f433249
#घोषणा PROC_TEST 0x54534554

/* KERN: message identअगरiers */
#घोषणा KMSG_FIFO   0x00000000
#घोषणा KMSG_ALARM  0x00000001

/* MEMX: message identअगरiers */
#घोषणा MEMX_MSG_INFO 0
#घोषणा MEMX_MSG_EXEC 1

/* MEMX: info types */
#घोषणा MEMX_INFO_DATA  0
#घोषणा MEMX_INFO_TRAIN 1

/* MEMX: script opcode definitions */
#घोषणा MEMX_ENTER  1
#घोषणा MEMX_LEAVE  2
#घोषणा MEMX_WR32   3
#घोषणा MEMX_WAIT   4
#घोषणा MEMX_DELAY  5
#घोषणा MEMX_VBLANK 6
#घोषणा MEMX_TRAIN  7

/* I2C_: message identअगरiers */
#घोषणा I2C__MSG_RD08 0
#घोषणा I2C__MSG_WR08 1

#घोषणा I2C__MSG_DATA0_PORT 24:31
#घोषणा I2C__MSG_DATA0_ADDR 14:23

#घोषणा I2C__MSG_DATA0_RD08_PORT I2C__MSG_DATA0_PORT
#घोषणा I2C__MSG_DATA0_RD08_ADDR I2C__MSG_DATA0_ADDR
#घोषणा I2C__MSG_DATA0_RD08_REG 0:7
#घोषणा I2C__MSG_DATA1_RD08_VAL 0:7

#घोषणा I2C__MSG_DATA0_WR08_PORT I2C__MSG_DATA0_PORT
#घोषणा I2C__MSG_DATA0_WR08_ADDR I2C__MSG_DATA0_ADDR
#घोषणा I2C__MSG_DATA0_WR08_SYNC 8:8
#घोषणा I2C__MSG_DATA0_WR08_REG 0:7
#घोषणा I2C__MSG_DATA1_WR08_VAL 0:7

#पूर्ण_अगर
