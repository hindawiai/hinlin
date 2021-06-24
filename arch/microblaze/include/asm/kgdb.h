<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_घोषित __KERNEL__
#अगर_अघोषित __MICROBLAZE_KGDB_H__
#घोषणा __MICROBLAZE_KGDB_H__

#अगर_अघोषित __ASSEMBLY__

#घोषणा CACHE_FLUSH_IS_SAFE	1
#घोषणा BUFMAX			2048

/*
 * 32 32-bit general purpose रेजिस्टरs (r0-r31)
 *  6 32-bit special रेजिस्टरs (pc, msr, ear, esr, fsr, btr)
 * 12 32-bit PVR
 *   7 32-bit MMU Regs (redr, rpid, rzpr, rtlbx, rtlbsx, rtlblo, rtlbhi)
 * ------
 *  57 रेजिस्टरs
 */
#घोषणा NUMREGBYTES	(57 * 4)

#घोषणा BREAK_INSTR_SIZE	4
अटल अंतरभूत व्योम arch_kgdb_अवरोधpoपूर्णांक(व्योम)
अणु
	__यंत्र__ __अस्थिर__("brki r16, 0x18;");
पूर्ण

काष्ठा pt_regs;
यंत्रlinkage व्योम microblaze_kgdb_अवरोध(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __MICROBLAZE_KGDB_H__ */
#पूर्ण_अगर /* __KERNEL__ */
