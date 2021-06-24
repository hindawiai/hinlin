<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * drivers/i2c/busses/i2c-ibm_iic.h
 *
 * Support क्रम the IIC peripheral on IBM PPC 4xx
 *
 * Copyright (c) 2003 Zultys Technologies.
 * Eugene Surovegin <eugene.surovegin@zultys.com> or <ebs@ebshome.net>
 *
 * Based on original work by
 * 	Ian DaSilva  <idasilva@mvista.com>
 *      Armin Kuster <akuster@mvista.com>
 * 	Matt Porter  <mporter@mvista.com>
 *
 *      Copyright 2000-2003 MontaVista Software Inc.
 */
#अगर_अघोषित __I2C_IBM_IIC_H_
#घोषणा __I2C_IBM_IIC_H_

#समावेश <linux/i2c.h>

काष्ठा iic_regs अणु
	u16 mdbuf;
	u16 sbbuf;
	u8 lmadr;
	u8 hmadr;
	u8 cntl;
	u8 mdcntl;
	u8 sts;
	u8 extsts;
	u8 lsadr;
	u8 hsadr;
	u8 clkभाग;
	u8 पूर्णांकmsk;
	u8 xfrcnt;
	u8 xtcntlss;
	u8 directcntl;
पूर्ण;

काष्ठा ibm_iic_निजी अणु
	काष्ठा i2c_adapter adap;
	अस्थिर काष्ठा iic_regs __iomem *vaddr;
	रुको_queue_head_t wq;
	पूर्णांक idx;
	पूर्णांक irq;
	पूर्णांक fast_mode;
	u8  clckभाग;
पूर्ण;

/* IICx_CNTL रेजिस्टर */
#घोषणा CNTL_HMT	0x80
#घोषणा CNTL_AMD	0x40
#घोषणा CNTL_TCT_MASK	0x30
#घोषणा CNTL_TCT_SHIFT	4
#घोषणा CNTL_RPST	0x08
#घोषणा CNTL_CHT	0x04
#घोषणा CNTL_RW		0x02
#घोषणा CNTL_PT		0x01

/* IICx_MDCNTL रेजिस्टर */
#घोषणा MDCNTL_FSDB	0x80
#घोषणा MDCNTL_FMDB	0x40
#घोषणा MDCNTL_EGC	0x20
#घोषणा MDCNTL_FSM	0x10
#घोषणा MDCNTL_ESM	0x08
#घोषणा MDCNTL_EINT	0x04
#घोषणा MDCNTL_EUBS	0x02
#घोषणा MDCNTL_HSCL	0x01

/* IICx_STS रेजिस्टर */
#घोषणा STS_SSS		0x80
#घोषणा STS_SLPR	0x40
#घोषणा STS_MDBS	0x20
#घोषणा STS_MDBF	0x10
#घोषणा STS_SCMP	0x08
#घोषणा STS_ERR		0x04
#घोषणा STS_IRQA	0x02
#घोषणा STS_PT		0x01

/* IICx_EXTSTS रेजिस्टर */
#घोषणा EXTSTS_IRQP	0x80
#घोषणा EXTSTS_BCS_MASK	0x70
#घोषणा   EXTSTS_BCS_FREE  0x40
#घोषणा EXTSTS_IRQD	0x08
#घोषणा EXTSTS_LA	0x04
#घोषणा EXTSTS_ICT	0x02
#घोषणा EXTSTS_XFRA	0x01

/* IICx_INTRMSK रेजिस्टर */
#घोषणा INTRMSK_EIRC	0x80
#घोषणा INTRMSK_EIRS	0x40
#घोषणा INTRMSK_EIWC	0x20
#घोषणा INTRMSK_EIWS	0x10
#घोषणा INTRMSK_EIHE	0x08
#घोषणा INTRMSK_EIIC	0x04
#घोषणा INTRMSK_EITA	0x02
#घोषणा INTRMSK_EIMTC	0x01

/* IICx_XFRCNT रेजिस्टर */
#घोषणा XFRCNT_MTC_MASK	0x07

/* IICx_XTCNTLSS रेजिस्टर */
#घोषणा XTCNTLSS_SRC	0x80
#घोषणा XTCNTLSS_SRS	0x40
#घोषणा XTCNTLSS_SWC	0x20
#घोषणा XTCNTLSS_SWS	0x10
#घोषणा XTCNTLSS_SRST	0x01

/* IICx_सूचीECTCNTL रेजिस्टर */
#घोषणा सूचीCNTL_SDAC	0x08
#घोषणा सूचीCNTL_SCC	0x04
#घोषणा सूचीCNTL_MSDA	0x02
#घोषणा सूचीCNTL_MSC	0x01

/* Check अगर we really control the I2C bus and bus is मुक्त */
#घोषणा सूचीCTNL_FREE(v)	(((v) & 0x0f) == 0x0f)

#पूर्ण_अगर /* __I2C_IBM_IIC_H_ */
