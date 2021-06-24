<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Derived from "include/asm-i386/delay.h"
 *    Copyright (C) 1993 Linus Torvalds
 *
 *  Delay routines calling functions in arch/s390/lib/delay.c
 */
 
#अगर_अघोषित _S390_DELAY_H
#घोषणा _S390_DELAY_H

व्योम __ndelay(अचिन्हित दीर्घ nsecs);
व्योम __udelay(अचिन्हित दीर्घ usecs);
व्योम __delay(अचिन्हित दीर्घ loops);

#घोषणा ndelay(n) __ndelay((अचिन्हित दीर्घ)(n))
#घोषणा udelay(n) __udelay((अचिन्हित दीर्घ)(n))
#घोषणा mdelay(n) __udelay((अचिन्हित दीर्घ)(n) * 1000)

#पूर्ण_अगर /* defined(_S390_DELAY_H) */
