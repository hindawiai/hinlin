<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common LiteX header providing
 * helper functions क्रम accessing CSRs.
 *
 * Copyright (C) 2019-2020 Anपंचांगicro <www.anपंचांगicro.com>
 */

#अगर_अघोषित _LINUX_LITEX_H
#घोषणा _LINUX_LITEX_H

#समावेश <linux/पन.स>

/* LiteX SoCs support 8- or 32-bit CSR Bus data width (i.e., subreg. size) */
#अगर defined(CONFIG_LITEX_SUBREG_SIZE) && \
	(CONFIG_LITEX_SUBREG_SIZE == 1 || CONFIG_LITEX_SUBREG_SIZE == 4)
#घोषणा LITEX_SUBREG_SIZE      CONFIG_LITEX_SUBREG_SIZE
#अन्यथा
#त्रुटि LiteX subरेजिस्टर size (LITEX_SUBREG_SIZE) must be 4 or 1!
#पूर्ण_अगर
#घोषणा LITEX_SUBREG_SIZE_BIT	 (LITEX_SUBREG_SIZE * 8)

/* LiteX subरेजिस्टरs of any width are always aligned on a 4-byte boundary */
#घोषणा LITEX_SUBREG_ALIGN	  0x4

अटल अंतरभूत व्योम _ग_लिखो_litex_subरेजिस्टर(u32 val, व्योम __iomem *addr)
अणु
	ग_लिखोl((u32 __क्रमce)cpu_to_le32(val), addr);
पूर्ण

अटल अंतरभूत u32 _पढ़ो_litex_subरेजिस्टर(व्योम __iomem *addr)
अणु
	वापस le32_to_cpu((__le32 __क्रमce)पढ़ोl(addr));
पूर्ण

/*
 * LiteX SoC Generator, depending on the configuration, can split a single
 * logical CSR (Control&Status Register) पूर्णांकo a series of consecutive physical
 * रेजिस्टरs.
 *
 * For example, in the configuration with 8-bit CSR Bus, a 32-bit aligned,
 * 32-bit wide logical CSR will be laid out as four 32-bit physical
 * subरेजिस्टरs, each one containing one byte of meaningful data.
 *
 * For details see: https://github.com/enjoy-digital/litex/wiki/CSR-Bus
 */

/* number of LiteX subरेजिस्टरs needed to store a रेजिस्टर of given reg_size */
#घोषणा _litex_num_subregs(reg_size) \
	(((reg_size) - 1) / LITEX_SUBREG_SIZE + 1)

/*
 * since the number of 4-byte aligned subरेजिस्टरs required to store a single
 * LiteX CSR (MMIO) रेजिस्टर varies with LITEX_SUBREG_SIZE, the offset of the
 * next adjacent LiteX CSR रेजिस्टर w.r.t. the offset of the current one also
 * depends on how many subरेजिस्टरs the latter is spपढ़ो across
 */
#घोषणा _next_reg_off(off, size) \
	((off) + _litex_num_subregs(size) * LITEX_SUBREG_ALIGN)

/*
 * The purpose of `_litex_[set|get]_reg()` is to implement the logic of
 * writing to/पढ़ोing from the LiteX CSR in a single place that can be then
 * reused by all LiteX drivers via the `litex_[ग_लिखो|पढ़ो][8|16|32|64]()`
 * accessors क्रम the appropriate data width.
 * NOTE: direct use of `_litex_[set|get]_reg()` by LiteX drivers is strongly
 * discouraged, as they perक्रमm no error checking on the requested data width!
 */

/**
 * _litex_set_reg() - Writes a value to the LiteX CSR (Control&Status Register)
 * @reg: Address of the CSR
 * @reg_size: The width of the CSR expressed in the number of bytes
 * @val: Value to be written to the CSR
 *
 * This function splits a single (possibly multi-byte) LiteX CSR ग_लिखो पूर्णांकo
 * a series of subरेजिस्टर ग_लिखोs with a proper offset.
 * NOTE: caller is responsible क्रम ensuring (0 < reg_size <= माप(u64)).
 */
अटल अंतरभूत व्योम _litex_set_reg(व्योम __iomem *reg, माप_प्रकार reg_size, u64 val)
अणु
	u8 shअगरt = _litex_num_subregs(reg_size) * LITEX_SUBREG_SIZE_BIT;

	जबतक (shअगरt > 0) अणु
		shअगरt -= LITEX_SUBREG_SIZE_BIT;
		_ग_लिखो_litex_subरेजिस्टर(val >> shअगरt, reg);
		reg += LITEX_SUBREG_ALIGN;
	पूर्ण
पूर्ण

/**
 * _litex_get_reg() - Reads a value of the LiteX CSR (Control&Status Register)
 * @reg: Address of the CSR
 * @reg_size: The width of the CSR expressed in the number of bytes
 *
 * Return: Value पढ़ो from the CSR
 *
 * This function generates a series of subरेजिस्टर पढ़ोs with a proper offset
 * and joins their results पूर्णांकo a single (possibly multi-byte) LiteX CSR value.
 * NOTE: caller is responsible क्रम ensuring (0 < reg_size <= माप(u64)).
 */
अटल अंतरभूत u64 _litex_get_reg(व्योम __iomem *reg, माप_प्रकार reg_size)
अणु
	u64 r;
	u8 i;

	r = _पढ़ो_litex_subरेजिस्टर(reg);
	क्रम (i = 1; i < _litex_num_subregs(reg_size); i++) अणु
		r <<= LITEX_SUBREG_SIZE_BIT;
		reg += LITEX_SUBREG_ALIGN;
		r |= _पढ़ो_litex_subरेजिस्टर(reg);
	पूर्ण
	वापस r;
पूर्ण

अटल अंतरभूत व्योम litex_ग_लिखो8(व्योम __iomem *reg, u8 val)
अणु
	_litex_set_reg(reg, माप(u8), val);
पूर्ण

अटल अंतरभूत व्योम litex_ग_लिखो16(व्योम __iomem *reg, u16 val)
अणु
	_litex_set_reg(reg, माप(u16), val);
पूर्ण

अटल अंतरभूत व्योम litex_ग_लिखो32(व्योम __iomem *reg, u32 val)
अणु
	_litex_set_reg(reg, माप(u32), val);
पूर्ण

अटल अंतरभूत व्योम litex_ग_लिखो64(व्योम __iomem *reg, u64 val)
अणु
	_litex_set_reg(reg, माप(u64), val);
पूर्ण

अटल अंतरभूत u8 litex_पढ़ो8(व्योम __iomem *reg)
अणु
	वापस _litex_get_reg(reg, माप(u8));
पूर्ण

अटल अंतरभूत u16 litex_पढ़ो16(व्योम __iomem *reg)
अणु
	वापस _litex_get_reg(reg, माप(u16));
पूर्ण

अटल अंतरभूत u32 litex_पढ़ो32(व्योम __iomem *reg)
अणु
	वापस _litex_get_reg(reg, माप(u32));
पूर्ण

अटल अंतरभूत u64 litex_पढ़ो64(व्योम __iomem *reg)
अणु
	वापस _litex_get_reg(reg, माप(u64));
पूर्ण

#पूर्ण_अगर /* _LINUX_LITEX_H */
