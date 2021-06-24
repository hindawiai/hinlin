<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sgiseeq.h: Defines क्रम the Seeq8003 ethernet controller.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 */
#अगर_अघोषित _SGISEEQ_H
#घोषणा _SGISEEQ_H

काष्ठा sgiseeq_wregs अणु
	अस्थिर अचिन्हित पूर्णांक multiहाल_high[2];
	अस्थिर अचिन्हित पूर्णांक frame_gap;
	अस्थिर अचिन्हित पूर्णांक control;
पूर्ण;

काष्ठा sgiseeq_rregs अणु
	अस्थिर अचिन्हित पूर्णांक collision_tx[2];
	अस्थिर अचिन्हित पूर्णांक collision_all[2];
	अस्थिर अचिन्हित पूर्णांक _unused0;
	अस्थिर अचिन्हित पूर्णांक rflags;
पूर्ण;

काष्ठा sgiseeq_regs अणु
	जोड़ अणु
		अस्थिर अचिन्हित पूर्णांक eth_addr[6];
		अस्थिर अचिन्हित पूर्णांक multicast_low[6];
		काष्ठा sgiseeq_wregs wregs;
		काष्ठा sgiseeq_rregs rregs;
	पूर्ण rw;
	अस्थिर अचिन्हित पूर्णांक rstat;
	अस्थिर अचिन्हित पूर्णांक tstat;
पूर्ण;

/* Seeq8003 receive status रेजिस्टर */
#घोषणा SEEQ_RSTAT_OVERF   0x001 /* Overflow */
#घोषणा SEEQ_RSTAT_CERROR  0x002 /* CRC error */
#घोषणा SEEQ_RSTAT_DERROR  0x004 /* Dribble error */
#घोषणा SEEQ_RSTAT_SFRAME  0x008 /* Short frame */
#घोषणा SEEQ_RSTAT_Rखातापूर्ण    0x010 /* Received end of frame */
#घोषणा SEEQ_RSTAT_FIG     0x020 /* Frame is good */
#घोषणा SEEQ_RSTAT_TIMEO   0x040 /* Timeout, or late receive */
#घोषणा SEEQ_RSTAT_WHICH   0x080 /* Which status, 1=old 0=new */
#घोषणा SEEQ_RSTAT_LITTLE  0x100 /* DMA is करोne in little endian क्रमmat */
#घोषणा SEEQ_RSTAT_SDMA    0x200 /* DMA has started */
#घोषणा SEEQ_RSTAT_ADMA    0x400 /* DMA is active */
#घोषणा SEEQ_RSTAT_ROVERF  0x800 /* Receive buffer overflow */

/* Seeq8003 receive command रेजिस्टर */
#घोषणा SEEQ_RCMD_RDISAB   0x000 /* Disable receiver on the Seeq8003 */
#घोषणा SEEQ_RCMD_IOVERF   0x001 /* IRQ on buffer overflows */
#घोषणा SEEQ_RCMD_ICRC     0x002 /* IRQ on CRC errors */
#घोषणा SEEQ_RCMD_IDRIB    0x004 /* IRQ on dribble errors */
#घोषणा SEEQ_RCMD_ISHORT   0x008 /* IRQ on लघु frames */
#घोषणा SEEQ_RCMD_Iखातापूर्ण     0x010 /* IRQ on end of frame */
#घोषणा SEEQ_RCMD_IGOOD    0x020 /* IRQ on good frames */
#घोषणा SEEQ_RCMD_RANY     0x040 /* Receive any frame */
#घोषणा SEEQ_RCMD_RBCAST   0x080 /* Receive broadcasts */
#घोषणा SEEQ_RCMD_RBMCAST  0x0c0 /* Receive broadcasts/multicasts */

/* Seeq8003 transmit status रेजिस्टर */
#घोषणा SEEQ_TSTAT_UFLOW   0x001 /* Transmit buffer underflow */
#घोषणा SEEQ_TSTAT_CLS     0x002 /* Collision detected */
#घोषणा SEEQ_TSTAT_R16     0x004 /* Did 16 retries to tx a frame */
#घोषणा SEEQ_TSTAT_PTRANS  0x008 /* Packet was transmitted ok */
#घोषणा SEEQ_TSTAT_LCLS    0x010 /* Late collision occurred */
#घोषणा SEEQ_TSTAT_WHICH   0x080 /* Which status, 1=old 0=new */
#घोषणा SEEQ_TSTAT_TLE     0x100 /* DMA is करोne in little endian क्रमmat */
#घोषणा SEEQ_TSTAT_SDMA    0x200 /* DMA has started */
#घोषणा SEEQ_TSTAT_ADMA    0x400 /* DMA is active */

/* Seeq8003 transmit command रेजिस्टर */
#घोषणा SEEQ_TCMD_RB0      0x00 /* Register bank zero w/station addr */
#घोषणा SEEQ_TCMD_IUF      0x01 /* IRQ on tx underflow */
#घोषणा SEEQ_TCMD_IC       0x02 /* IRQ on collisions */
#घोषणा SEEQ_TCMD_I16      0x04 /* IRQ after 16 failed attempts to tx frame */
#घोषणा SEEQ_TCMD_IPT      0x08 /* IRQ when packet successfully transmitted */
#घोषणा SEEQ_TCMD_RB1      0x20 /* Register bank one w/multi-cast low byte */
#घोषणा SEEQ_TCMD_RB2      0x40 /* Register bank two w/multi-cast high byte */

/* Seeq8003 control रेजिस्टर */
#घोषणा SEEQ_CTRL_XCNT     0x01
#घोषणा SEEQ_CTRL_ACCNT    0x02
#घोषणा SEEQ_CTRL_SFLAG    0x04
#घोषणा SEEQ_CTRL_EMULTI   0x08
#घोषणा SEEQ_CTRL_ESHORT   0x10
#घोषणा SEEQ_CTRL_ENCARR   0x20

/* Seeq8003 control रेजिस्टरs on the SGI Hollywood HPC. */
#घोषणा SEEQ_HPIO_P1BITS  0x00000001 /* cycles to stay in P1 phase क्रम PIO */
#घोषणा SEEQ_HPIO_P2BITS  0x00000060 /* cycles to stay in P2 phase क्रम PIO */
#घोषणा SEEQ_HPIO_P3BITS  0x00000100 /* cycles to stay in P3 phase क्रम PIO */
#घोषणा SEEQ_HDMA_D1BITS  0x00000006 /* cycles to stay in D1 phase क्रम DMA */
#घोषणा SEEQ_HDMA_D2BITS  0x00000020 /* cycles to stay in D2 phase क्रम DMA */
#घोषणा SEEQ_HDMA_D3BITS  0x00000000 /* cycles to stay in D3 phase क्रम DMA */
#घोषणा SEEQ_HDMA_TIMEO   0x00030000 /* cycles क्रम DMA समयout */
#घोषणा SEEQ_HCTL_NORM    0x00000000 /* Normal operation mode */
#घोषणा SEEQ_HCTL_RESET   0x00000001 /* Reset Seeq8003 and HPC पूर्णांकerface */
#घोषणा SEEQ_HCTL_IPEND   0x00000002 /* IRQ is pending क्रम the chip */
#घोषणा SEEQ_HCTL_IPG     0x00001000 /* Inter-packet gap */
#घोषणा SEEQ_HCTL_RFIX    0x00002000 /* At rxdc, clear end-of-packet */
#घोषणा SEEQ_HCTL_EFIX    0x00004000 /* fixes पूर्णांकr status bit settings */
#घोषणा SEEQ_HCTL_IFIX    0x00008000 /* enable startup समयouts */

#पूर्ण_अगर /* !(_SGISEEQ_H) */
