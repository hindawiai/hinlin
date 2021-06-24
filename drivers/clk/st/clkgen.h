<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/************************************************************************
File  : Clock H/w specअगरic Inक्रमmation

Author: Pankaj Dev <pankaj.dev@st.com>

Copyright (C) 2014 STMicroelectronics
************************************************************************/

#अगर_अघोषित __CLKGEN_INFO_H
#घोषणा __CLKGEN_INFO_H

बाह्य spinlock_t clkgen_a9_lock;

काष्ठा clkgen_field अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक mask;
	अचिन्हित पूर्णांक shअगरt;
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ clkgen_पढ़ो(व्योम __iomem	*base,
					  काष्ठा clkgen_field *field)
अणु
	वापस (पढ़ोl(base + field->offset) >> field->shअगरt) & field->mask;
पूर्ण


अटल अंतरभूत व्योम clkgen_ग_लिखो(व्योम __iomem *base, काष्ठा clkgen_field *field,
				  अचिन्हित दीर्घ val)
अणु
	ग_लिखोl((पढ़ोl(base + field->offset) &
	       ~(field->mask << field->shअगरt)) | (val << field->shअगरt),
	       base + field->offset);

	वापस;
पूर्ण

#घोषणा CLKGEN_FIELD(_offset, _mask, _shअगरt) अणु		\
				.offset	= _offset,	\
				.mask	= _mask,	\
				.shअगरt	= _shअगरt,	\
				पूर्ण

#घोषणा CLKGEN_READ(pll, field) clkgen_पढ़ो(pll->regs_base, \
		&pll->data->field)

#घोषणा CLKGEN_WRITE(pll, field, val) clkgen_ग_लिखो(pll->regs_base, \
		&pll->data->field, val)

#पूर्ण_अगर /*__CLKGEN_INFO_H*/

