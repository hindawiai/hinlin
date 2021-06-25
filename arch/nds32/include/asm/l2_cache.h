<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित L2_CACHE_H
#घोषणा L2_CACHE_H

/* CCTL_CMD_OP */
#घोषणा L2_CA_CONF_OFF		0x0
#घोषणा L2_IF_CONF_OFF		0x4
#घोषणा L2CC_SETUP_OFF		0x8
#घोषणा L2CC_PROT_OFF		0xC
#घोषणा L2CC_CTRL_OFF		0x10
#घोषणा L2_INT_EN_OFF           0x20
#घोषणा L2_STA_OFF              0x24
#घोषणा RDERR_ADDR_OFF		0x28
#घोषणा WRERR_ADDR_OFF		0x2c
#घोषणा EVDPTERR_ADDR_OFF	0x30
#घोषणा IMPL3ERR_ADDR_OFF	0x34
#घोषणा L2_CNT0_CTRL_OFF        0x40
#घोषणा L2_EVNT_CNT0_OFF        0x44
#घोषणा L2_CNT1_CTRL_OFF        0x48
#घोषणा L2_EVNT_CNT1_OFF        0x4c
#घोषणा L2_CCTL_CMD_OFF		0x60
#घोषणा L2_CCTL_STATUS_OFF	0x64
#घोषणा L2_LINE_TAG_OFF		0x68
#घोषणा L2_LINE_DPT_OFF		0x70

#घोषणा CCTL_CMD_L2_IX_INVAL    0x0
#घोषणा CCTL_CMD_L2_PA_INVAL    0x1
#घोषणा CCTL_CMD_L2_IX_WB       0x2
#घोषणा CCTL_CMD_L2_PA_WB       0x3
#घोषणा CCTL_CMD_L2_PA_WBINVAL  0x5
#घोषणा CCTL_CMD_L2_SYNC        0xa

/* CCTL_CMD_TYPE */
#घोषणा CCTL_SINGLE_CMD         0
#घोषणा CCTL_BLOCK_CMD          0x10
#घोषणा CCTL_ALL_CMD		0x10

/******************************************************************************
 * L2_CA_CONF (Cache architecture configuration)
 *****************************************************************************/
#घोषणा L2_CA_CONF_offL2SET		0
#घोषणा L2_CA_CONF_offL2WAY		4
#घोषणा L2_CA_CONF_offL2CLSZ            8
#घोषणा L2_CA_CONF_offL2DW		11
#घोषणा L2_CA_CONF_offL2PT		14
#घोषणा L2_CA_CONF_offL2VER		16

#घोषणा L2_CA_CONF_mskL2SET	(0xFUL << L2_CA_CONF_offL2SET)
#घोषणा L2_CA_CONF_mskL2WAY	(0xFUL << L2_CA_CONF_offL2WAY)
#घोषणा L2_CA_CONF_mskL2CLSZ    (0x7UL << L2_CA_CONF_offL2CLSZ)
#घोषणा L2_CA_CONF_mskL2DW	(0x7UL << L2_CA_CONF_offL2DW)
#घोषणा L2_CA_CONF_mskL2PT	(0x3UL << L2_CA_CONF_offL2PT)
#घोषणा L2_CA_CONF_mskL2VER	(0xFFFFUL << L2_CA_CONF_offL2VER)

/******************************************************************************
 * L2CC_SETUP (L2CC Setup रेजिस्टर)
 *****************************************************************************/
#घोषणा L2CC_SETUP_offPART              0
#घोषणा L2CC_SETUP_mskPART              (0x3UL << L2CC_SETUP_offPART)
#घोषणा L2CC_SETUP_offDDLATC            4
#घोषणा L2CC_SETUP_mskDDLATC            (0x3UL << L2CC_SETUP_offDDLATC)
#घोषणा L2CC_SETUP_offTDLATC            8
#घोषणा L2CC_SETUP_mskTDLATC            (0x3UL << L2CC_SETUP_offTDLATC)

/******************************************************************************
 * L2CC_PROT (L2CC Protect रेजिस्टर)
 *****************************************************************************/
#घोषणा L2CC_PROT_offMRWEN              31
#घोषणा L2CC_PROT_mskMRWEN      (0x1UL << L2CC_PROT_offMRWEN)

/******************************************************************************
 * L2_CCTL_STATUS_Mn (The L2CCTL command working status क्रम Master n)
 *****************************************************************************/
#घोषणा L2CC_CTRL_offEN                 31
#घोषणा L2CC_CTRL_mskEN                 (0x1UL << L2CC_CTRL_offEN)

/******************************************************************************
 * L2_CCTL_STATUS_Mn (The L2CCTL command working status क्रम Master n)
 *****************************************************************************/
#घोषणा L2_CCTL_STATUS_offCMD_COMP      31
#घोषणा L2_CCTL_STATUS_mskCMD_COMP      (0x1 << L2_CCTL_STATUS_offCMD_COMP)

बाह्य व्योम __iomem *atl2c_base;
#समावेश <linux/smp.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/bitfield.h>

#घोषणा L2C_R_REG(offset)               पढ़ोl(atl2c_base + offset)
#घोषणा L2C_W_REG(offset, value)        ग_लिखोl(value, atl2c_base + offset)

#घोषणा L2_CMD_RDY()    \
        करोअणु;पूर्णजबतक((L2C_R_REG(L2_CCTL_STATUS_OFF) & L2_CCTL_STATUS_mskCMD_COMP) == 0)

अटल अंतरभूत अचिन्हित दीर्घ L2_CACHE_SET(व्योम)
अणु
	वापस 64 << ((L2C_R_REG(L2_CA_CONF_OFF) & L2_CA_CONF_mskL2SET) >>
		      L2_CA_CONF_offL2SET);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ L2_CACHE_WAY(व्योम)
अणु
	वापस 1 +
	    ((L2C_R_REG(L2_CA_CONF_OFF) & L2_CA_CONF_mskL2WAY) >>
	     L2_CA_CONF_offL2WAY);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ L2_CACHE_LINE_SIZE(व्योम)
अणु

	वापस 4 << ((L2C_R_REG(L2_CA_CONF_OFF) & L2_CA_CONF_mskL2CLSZ) >>
		     L2_CA_CONF_offL2CLSZ);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ GET_L2CC_CTRL_CPU(अचिन्हित दीर्घ cpu)
अणु
	अगर (cpu == smp_processor_id())
		वापस L2C_R_REG(L2CC_CTRL_OFF);
	वापस L2C_R_REG(L2CC_CTRL_OFF + (cpu << 8));
पूर्ण

अटल अंतरभूत व्योम SET_L2CC_CTRL_CPU(अचिन्हित दीर्घ cpu, अचिन्हित दीर्घ val)
अणु
	अगर (cpu == smp_processor_id())
		L2C_W_REG(L2CC_CTRL_OFF, val);
	अन्यथा
		L2C_W_REG(L2CC_CTRL_OFF + (cpu << 8), val);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ GET_L2CC_STATUS_CPU(अचिन्हित दीर्घ cpu)
अणु
	अगर (cpu == smp_processor_id())
		वापस L2C_R_REG(L2_CCTL_STATUS_OFF);
	वापस L2C_R_REG(L2_CCTL_STATUS_OFF + (cpu << 8));
पूर्ण
#पूर्ण_अगर
