<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Fault Injection Test harness (FI)
 *  Copyright (C) Intel Crop.
 */

#अगर_अघोषित __PF_H_
#घोषणा __PF_H_

क्रमागत reason_type अणु
	NOT_ME,	/* page fault is not in regions */
	NOTHING,	/* access others poपूर्णांक in regions */
	REG_READ,	/* पढ़ो from addr to reg */
	REG_WRITE,	/* ग_लिखो from reg to addr */
	IMM_WRITE,	/* ग_लिखो from imm to addr */
	OTHERS	/* Other inकाष्ठाions can not पूर्णांकercept */
पूर्ण;

क्रमागत reason_type get_ins_type(अचिन्हित दीर्घ ins_addr);
अचिन्हित पूर्णांक get_ins_mem_width(अचिन्हित दीर्घ ins_addr);
अचिन्हित दीर्घ get_ins_reg_val(अचिन्हित दीर्घ ins_addr, काष्ठा pt_regs *regs);
अचिन्हित दीर्घ get_ins_imm_val(अचिन्हित दीर्घ ins_addr);

#पूर्ण_अगर /* __PF_H_ */
