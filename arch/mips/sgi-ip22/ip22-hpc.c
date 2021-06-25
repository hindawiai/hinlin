<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ip22-hpc.c: Routines क्रम generic manipulation of the HPC controllers.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1998 Ralf Baechle
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ioc.h>
#समावेश <यंत्र/sgi/ip22.h>

काष्ठा hpc3_regs *hpc3c0, *hpc3c1;

EXPORT_SYMBOL(hpc3c0);
EXPORT_SYMBOL(hpc3c1);

काष्ठा sgioc_regs *sgioc;

EXPORT_SYMBOL(sgioc);

/* We need software copies of these because they are ग_लिखो only. */
u8 sgi_ioc_reset, sgi_ioc_ग_लिखो;

बाह्य अक्षर *प्रणाली_type;

व्योम __init sgihpc_init(व्योम)
अणु
	/* ioremap can't fail */
	hpc3c0 = (काष्ठा hpc3_regs *)
		 ioremap(HPC3_CHIP0_BASE, माप(काष्ठा hpc3_regs));
	hpc3c1 = (काष्ठा hpc3_regs *)
		 ioremap(HPC3_CHIP1_BASE, माप(काष्ठा hpc3_regs));
	/* IOC lives in PBUS PIO channel 6 */
	sgioc = (काष्ठा sgioc_regs *)hpc3c0->pbus_extregs[6];

	hpc3c0->pbus_piocfg[6][0] |= HPC3_PIOCFG_DS16;
	अगर (ip22_is_fullhouse()) अणु
		/* Full House comes with INT2 which lives in PBUS PIO
		 * channel 4 */
		sgपूर्णांक = (काष्ठा sgपूर्णांक_regs *)hpc3c0->pbus_extregs[4];
		प्रणाली_type = "SGI Indigo2";
	पूर्ण अन्यथा अणु
		/* Guiness comes with INT3 which is part of IOC */
		sgपूर्णांक = &sgioc->पूर्णांक3;
		प्रणाली_type = "SGI Indy";
	पूर्ण

	sgi_ioc_reset = (SGIOC_RESET_PPORT | SGIOC_RESET_KBDMOUSE |
			 SGIOC_RESET_EISA | SGIOC_RESET_ISDN |
			 SGIOC_RESET_LC0OFF);

	sgi_ioc_ग_लिखो = (SGIOC_WRITE_EASEL | SGIOC_WRITE_NTHRESH |
			 SGIOC_WRITE_TPSPEED | SGIOC_WRITE_EPSEL |
			 SGIOC_WRITE_U0AMODE | SGIOC_WRITE_U1AMODE);

	sgioc->reset = sgi_ioc_reset;
	sgioc->ग_लिखो = sgi_ioc_ग_लिखो;
पूर्ण
