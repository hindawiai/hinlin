<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * pi1.h: Definitions क्रम SGI PI1 parallel port
 */

#अगर_अघोषित _SGI_PI1_H
#घोषणा _SGI_PI1_H

काष्ठा pi1_regs अणु
	u8 _data[3];
	अस्थिर u8 data;
	u8 _ctrl[3];
	अस्थिर u8 ctrl;
#घोषणा PI1_CTRL_STROBE_N	0x01
#घोषणा PI1_CTRL_AFD_N		0x02
#घोषणा PI1_CTRL_INIT_N		0x04
#घोषणा PI1_CTRL_SLIN_N		0x08
#घोषणा PI1_CTRL_IRQ_ENA	0x10
#घोषणा PI1_CTRL_सूची		0x20
#घोषणा PI1_CTRL_SEL		0x40
	u8 _status[3];
	अस्थिर u8 status;
#घोषणा PI1_STAT_DEVID		0x03	/* bits 0-1 */
#घोषणा PI1_STAT_NOINK		0x04	/* SGI MODE only */
#घोषणा PI1_STAT_ERROR		0x08
#घोषणा PI1_STAT_ONLINE		0x10
#घोषणा PI1_STAT_PE		0x20
#घोषणा PI1_STAT_ACK		0x40
#घोषणा PI1_STAT_BUSY		0x80
	u8 _dmactrl[3];
	अस्थिर u8 dmactrl;
#घोषणा PI1_DMACTRL_FIFO_EMPTY	0x01	/* fअगरo empty R/O */
#घोषणा PI1_DMACTRL_ABORT	0x02	/* reset DMA and पूर्णांकernal fअगरo W/O */
#घोषणा PI1_DMACTRL_STDMODE	0x00	/* bits 2-3 */
#घोषणा PI1_DMACTRL_SGIMODE	0x04	/* bits 2-3 */
#घोषणा PI1_DMACTRL_RICOHMODE	0x08	/* bits 2-3 */
#घोषणा PI1_DMACTRL_HPMODE	0x0c	/* bits 2-3 */
#घोषणा PI1_DMACTRL_BLKMODE	0x10	/* block mode */
#घोषणा PI1_DMACTRL_FIFO_CLEAR	0x20	/* clear fअगरo W/O */
#घोषणा PI1_DMACTRL_READ	0x40	/* पढ़ो */
#घोषणा PI1_DMACTRL_RUN		0x80	/* pedal to the metal */
	u8 _पूर्णांकstat[3];
	अस्थिर u8 पूर्णांकstat;
#घोषणा PI1_INTSTAT_ACK		0x04
#घोषणा PI1_INTSTAT_FEMPTY	0x08
#घोषणा PI1_INTSTAT_NOINK	0x10
#घोषणा PI1_INTSTAT_ONLINE	0x20
#घोषणा PI1_INTSTAT_ERR		0x40
#घोषणा PI1_INTSTAT_PE		0x80
	u8 _पूर्णांकmask[3];
	अस्थिर u8 पूर्णांकmask;		/* enabled low, reset high*/
#घोषणा PI1_INTMASK_ACK		0x04
#घोषणा PI1_INTMASK_FIFO_EMPTY	0x08
#घोषणा PI1_INTMASK_NOINK	0x10
#घोषणा PI1_INTMASK_ONLINE	0x20
#घोषणा PI1_INTMASK_ERR		0x40
#घोषणा PI1_INTMASK_PE		0x80
	u8 _समयr1[3];
	अस्थिर u8 समयr1;
#घोषणा PI1_TIME1		0x27
	u8 _समयr2[3];
	अस्थिर u8 समयr2;
#घोषणा PI1_TIME2		0x13
	u8 _समयr3[3];
	अस्थिर u8 समयr3;
#घोषणा PI1_TIME3		0x10
	u8 _समयr4[3];
	अस्थिर u8 समयr4;
#घोषणा PI1_TIME4		0x00
पूर्ण;

#पूर्ण_अगर
