<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Defines क्रम the SRAM driver
 */
#अगर_अघोषित __SRAM_H
#घोषणा __SRAM_H

काष्ठा sram_partition अणु
	व्योम __iomem *base;

	काष्ठा gen_pool *pool;
	काष्ठा bin_attribute battr;
	काष्ठा mutex lock;
	काष्ठा list_head list;
पूर्ण;

काष्ठा sram_dev अणु
	काष्ठा device *dev;
	व्योम __iomem *virt_base;

	काष्ठा gen_pool *pool;
	काष्ठा clk *clk;

	काष्ठा sram_partition *partition;
	u32 partitions;
पूर्ण;

काष्ठा sram_reserve अणु
	काष्ठा list_head list;
	u32 start;
	u32 size;
	bool export;
	bool pool;
	bool protect_exec;
	स्थिर अक्षर *label;
पूर्ण;

#अगर_घोषित CONFIG_SRAM_EXEC
पूर्णांक sram_check_protect_exec(काष्ठा sram_dev *sram, काष्ठा sram_reserve *block,
			    काष्ठा sram_partition *part);
पूर्णांक sram_add_protect_exec(काष्ठा sram_partition *part);
#अन्यथा
अटल अंतरभूत पूर्णांक sram_check_protect_exec(काष्ठा sram_dev *sram,
					  काष्ठा sram_reserve *block,
					  काष्ठा sram_partition *part)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक sram_add_protect_exec(काष्ठा sram_partition *part)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_SRAM_EXEC */
#पूर्ण_अगर /* __SRAM_H */
