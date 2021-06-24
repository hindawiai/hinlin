<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RapidIO architecture support
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#अगर_अघोषित ASM_PPC_RIO_H
#घोषणा ASM_PPC_RIO_H

#अगर_घोषित CONFIG_FSL_RIO
बाह्य पूर्णांक fsl_rio_mcheck_exception(काष्ठा pt_regs *);
#अन्यथा
अटल अंतरभूत पूर्णांक fsl_rio_mcheck_exception(काष्ठा pt_regs *regs) अणुवापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर				/* ASM_PPC_RIO_H */
