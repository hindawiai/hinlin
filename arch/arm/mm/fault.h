<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_ARM_FAULT_H
#घोषणा __ARCH_ARM_FAULT_H

/*
 * Fault status रेजिस्टर encodings.  We steal bit 31 क्रम our own purposes.
 */
#घोषणा FSR_LNX_PF		(1 << 31)
#घोषणा FSR_CM			(1 << 13)
#घोषणा FSR_WRITE		(1 << 11)
#घोषणा FSR_FS4			(1 << 10)
#घोषणा FSR_FS3_0		(15)
#घोषणा FSR_FS5_0		(0x3f)

#अगर_घोषित CONFIG_ARM_LPAE
#घोषणा FSR_FS_AEA		17

अटल अंतरभूत पूर्णांक fsr_fs(अचिन्हित पूर्णांक fsr)
अणु
	वापस fsr & FSR_FS5_0;
पूर्ण
#अन्यथा
#घोषणा FSR_FS_AEA		22

अटल अंतरभूत पूर्णांक fsr_fs(अचिन्हित पूर्णांक fsr)
अणु
	वापस (fsr & FSR_FS3_0) | (fsr & FSR_FS4) >> 6;
पूर्ण
#पूर्ण_अगर

व्योम करो_bad_area(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr, काष्ठा pt_regs *regs);
व्योम early_abt_enable(व्योम);

#पूर्ण_अगर	/* __ARCH_ARM_FAULT_H */
