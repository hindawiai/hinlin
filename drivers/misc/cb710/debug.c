<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cb710/debug.c
 *
 *  Copyright by Michaध Mirosधaw, 2008-2009
 */
#समावेश <linux/cb710.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#घोषणा CB710_REG_COUNT		0x80

अटल स्थिर u16 allow[CB710_REG_COUNT/16] = अणु
	0xFFF0, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFF0, 0xFFFF, 0xFFFF, 0xFFFF,
पूर्ण;
अटल स्थिर अक्षर *स्थिर prefix[ARRAY_SIZE(allow)] = अणु
	"MMC", "MMC", "MMC", "MMC",
	"MS?", "MS?", "SM?", "SM?"
पूर्ण;

अटल अंतरभूत पूर्णांक allow_reg_पढ़ो(अचिन्हित block, अचिन्हित offset, अचिन्हित bits)
अणु
	अचिन्हित mask = (1 << bits/8) - 1;
	offset *= bits/8;
	वापस ((allow[block] >> offset) & mask) == mask;
पूर्ण

#घोषणा CB710_READ_REGS_TEMPLATE(t)					\
अटल व्योम cb710_पढ़ो_regs_##t(व्योम __iomem *iobase,			\
	u##t *reg, अचिन्हित select)					\
अणु									\
	अचिन्हित i, j;							\
									\
	क्रम (i = 0; i < ARRAY_SIZE(allow); ++i, reg += 16/(t/8)) अणु	\
		अगर (!(select & (1 << i)))					\
			जारी;					\
									\
		क्रम (j = 0; j < 0x10/(t/8); ++j) अणु			\
			अगर (!allow_reg_पढ़ो(i, j, t))			\
				जारी;				\
			reg[j] = ioपढ़ो##t(iobase			\
				+ (i << 4) + (j * (t/8)));		\
		पूर्ण							\
	पूर्ण								\
पूर्ण

अटल स्थिर अक्षर cb710_regf_8[] = "%02X";
अटल स्थिर अक्षर cb710_regf_16[] = "%04X";
अटल स्थिर अक्षर cb710_regf_32[] = "%08X";
अटल स्थिर अक्षर cb710_xes[] = "xxxxxxxx";

#घोषणा CB710_DUMP_REGS_TEMPLATE(t)					\
अटल व्योम cb710_dump_regs_##t(काष्ठा device *dev,			\
	स्थिर u##t *reg, अचिन्हित select)				\
अणु									\
	स्थिर अक्षर *स्थिर xp = &cb710_xes[8 - t/4];			\
	स्थिर अक्षर *स्थिर क्रमmat = cb710_regf_##t;			\
									\
	अक्षर msg[100], *p;						\
	अचिन्हित i, j;							\
									\
	क्रम (i = 0; i < ARRAY_SIZE(allow); ++i, reg += 16/(t/8)) अणु	\
		अगर (!(select & (1 << i)))				\
			जारी;					\
		p = msg;						\
		क्रम (j = 0; j < 0x10/(t/8); ++j) अणु			\
			*p++ = ' ';					\
			अगर (j == 8/(t/8))				\
				*p++ = ' ';				\
			अगर (allow_reg_पढ़ो(i, j, t))			\
				p += प्र_लिखो(p, क्रमmat, reg[j]);	\
			अन्यथा						\
				p += प्र_लिखो(p, "%s", xp);		\
		पूर्ण							\
		dev_dbg(dev, "%s 0x%02X %s\n", prefix[i], i << 4, msg);	\
	पूर्ण								\
पूर्ण

#घोषणा CB710_READ_AND_DUMP_REGS_TEMPLATE(t)				\
अटल व्योम cb710_पढ़ो_and_dump_regs_##t(काष्ठा cb710_chip *chip,	\
	अचिन्हित select)						\
अणु									\
	u##t regs[CB710_REG_COUNT/माप(u##t)];			\
									\
	स_रखो(&regs, 0, माप(regs));					\
	cb710_पढ़ो_regs_##t(chip->iobase, regs, select);		\
	cb710_dump_regs_##t(cb710_chip_dev(chip), regs, select);	\
पूर्ण

#घोषणा CB710_REG_ACCESS_TEMPLATES(t)		\
  CB710_READ_REGS_TEMPLATE(t)			\
  CB710_DUMP_REGS_TEMPLATE(t)			\
  CB710_READ_AND_DUMP_REGS_TEMPLATE(t)

CB710_REG_ACCESS_TEMPLATES(8)
CB710_REG_ACCESS_TEMPLATES(16)
CB710_REG_ACCESS_TEMPLATES(32)

व्योम cb710_dump_regs(काष्ठा cb710_chip *chip, अचिन्हित select)
अणु
	अगर (!(select & CB710_DUMP_REGS_MASK))
		select = CB710_DUMP_REGS_ALL;
	अगर (!(select & CB710_DUMP_ACCESS_MASK))
		select |= CB710_DUMP_ACCESS_8;

	अगर (select & CB710_DUMP_ACCESS_32)
		cb710_पढ़ो_and_dump_regs_32(chip, select);
	अगर (select & CB710_DUMP_ACCESS_16)
		cb710_पढ़ो_and_dump_regs_16(chip, select);
	अगर (select & CB710_DUMP_ACCESS_8)
		cb710_पढ़ो_and_dump_regs_8(chip, select);
पूर्ण
EXPORT_SYMBOL_GPL(cb710_dump_regs);

