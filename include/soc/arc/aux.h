<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016-2017 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __SOC_ARC_AUX_H__
#घोषणा __SOC_ARC_AUX_H__

#अगर_घोषित CONFIG_ARC

#घोषणा पढ़ो_aux_reg(r)		__builtin_arc_lr(r)

/* gcc builtin sr needs reg param to be दीर्घ immediate */
#घोषणा ग_लिखो_aux_reg(r, v)	__builtin_arc_sr((अचिन्हित पूर्णांक)(v), r)

#अन्यथा	/* !CONFIG_ARC */

अटल अंतरभूत पूर्णांक पढ़ो_aux_reg(u32 r)
अणु
	वापस 0;
पूर्ण

/*
 * function helps elide unused variable warning
 * see: https://lists.infradead.org/pipermail/linux-snps-arc/2016-November/001748.hपंचांगl
 */
अटल अंतरभूत व्योम ग_लिखो_aux_reg(u32 r, u32 v)
अणु
	;
पूर्ण

#पूर्ण_अगर

#घोषणा READ_BCR(reg, पूर्णांकo)				\
अणु							\
	अचिन्हित पूर्णांक पंचांगp;				\
	पंचांगp = पढ़ो_aux_reg(reg);			\
	अगर (माप(पंचांगp) == माप(पूर्णांकo)) अणु		\
		पूर्णांकo = *((typeof(पूर्णांकo) *)&पंचांगp);		\
	पूर्ण अन्यथा अणु					\
		बाह्य व्योम bogus_undefined(व्योम);	\
		bogus_undefined();			\
	पूर्ण						\
पूर्ण

#घोषणा WRITE_AUX(reg, पूर्णांकo)				\
अणु							\
	अचिन्हित पूर्णांक पंचांगp;				\
	अगर (माप(पंचांगp) == माप(पूर्णांकo)) अणु		\
		पंचांगp = (*(अचिन्हित पूर्णांक *)&(पूर्णांकo));	\
		ग_लिखो_aux_reg(reg, पंचांगp);		\
	पूर्ण अन्यथा  अणु					\
		बाह्य व्योम bogus_undefined(व्योम);	\
		bogus_undefined();			\
	पूर्ण						\
पूर्ण


#पूर्ण_अगर
