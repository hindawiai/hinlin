<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  arch/arm/include/यंत्र/ide.h
 *
 *  Copyright (C) 1994-1996  Linus Torvalds & authors
 */

/*
 *  This file contains the ARM architecture specअगरic IDE code.
 */

#अगर_अघोषित __ASMARM_IDE_H
#घोषणा __ASMARM_IDE_H

#अगर_घोषित __KERNEL__

#घोषणा __ide_mm_insw(port,addr,len)	पढ़ोsw(port,addr,len)
#घोषणा __ide_mm_insl(port,addr,len)	पढ़ोsl(port,addr,len)
#घोषणा __ide_mm_outsw(port,addr,len)	ग_लिखोsw(port,addr,len)
#घोषणा __ide_mm_outsl(port,addr,len)	ग_लिखोsl(port,addr,len)

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASMARM_IDE_H */
