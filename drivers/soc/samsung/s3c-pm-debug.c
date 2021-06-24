<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2013 Samsung Electronics Co., Ltd.
//	Tomasz Figa <t.figa@samsung.com>
// Copyright (C) 2008 Openmoko, Inc.
// Copyright (C) 2004-2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// Samsung common घातer management (suspend to RAM) debug support

#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/mach/map.h>

#समावेश <linux/soc/samsung/s3c-pm.h>

अटल काष्ठा pm_uart_save uart_save;

बाह्य व्योम prपूर्णांकascii(स्थिर अक्षर *);

व्योम s3c_pm_dbg(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची va;
	अक्षर buff[256];

	बहु_शुरू(va, fmt);
	vsnम_लिखो(buff, माप(buff), fmt, va);
	बहु_पूर्ण(va);

	prपूर्णांकascii(buff);
पूर्ण

अटल अंतरभूत व्योम __iomem *s3c_pm_uart_base(व्योम)
अणु
	अचिन्हित दीर्घ paddr;
	अचिन्हित दीर्घ vaddr;

	debug_ll_addr(&paddr, &vaddr);

	वापस (व्योम __iomem *)vaddr;
पूर्ण

व्योम s3c_pm_save_uarts(bool is_s3c2410)
अणु
	व्योम __iomem *regs = s3c_pm_uart_base();
	काष्ठा pm_uart_save *save = &uart_save;

	save->ulcon = __raw_पढ़ोl(regs + S3C2410_ULCON);
	save->ucon = __raw_पढ़ोl(regs + S3C2410_UCON);
	save->ufcon = __raw_पढ़ोl(regs + S3C2410_UFCON);
	save->umcon = __raw_पढ़ोl(regs + S3C2410_UMCON);
	save->ubrभाग = __raw_पढ़ोl(regs + S3C2410_UBRDIV);

	अगर (!is_s3c2410)
		save->uभागslot = __raw_पढ़ोl(regs + S3C2443_DIVSLOT);

	S3C_PMDBG("UART[%p]: ULCON=%04x, UCON=%04x, UFCON=%04x, UBRDIV=%04x\n",
		  regs, save->ulcon, save->ucon, save->ufcon, save->ubrभाग);
पूर्ण

व्योम s3c_pm_restore_uarts(bool is_s3c2410)
अणु
	व्योम __iomem *regs = s3c_pm_uart_base();
	काष्ठा pm_uart_save *save = &uart_save;

	s3c_pm_arch_update_uart(regs, save);

	__raw_ग_लिखोl(save->ulcon, regs + S3C2410_ULCON);
	__raw_ग_लिखोl(save->ucon,  regs + S3C2410_UCON);
	__raw_ग_लिखोl(save->ufcon, regs + S3C2410_UFCON);
	__raw_ग_लिखोl(save->umcon, regs + S3C2410_UMCON);
	__raw_ग_लिखोl(save->ubrभाग, regs + S3C2410_UBRDIV);

	अगर (!is_s3c2410)
		__raw_ग_लिखोl(save->uभागslot, regs + S3C2443_DIVSLOT);
पूर्ण
