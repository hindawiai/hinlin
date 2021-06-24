<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/cpu/sh4a/ubc.c
 *
 * On-chip UBC support क्रम SH-4A CPUs.
 *
 * Copyright (C) 2009 - 2010  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>

#घोषणा UBC_CBR(idx)	(0xff200000 + (0x20 * idx))
#घोषणा UBC_CRR(idx)	(0xff200004 + (0x20 * idx))
#घोषणा UBC_CAR(idx)	(0xff200008 + (0x20 * idx))
#घोषणा UBC_CAMR(idx)	(0xff20000c + (0x20 * idx))

#घोषणा UBC_CCMFR	0xff200600
#घोषणा UBC_CBCR	0xff200620

/* CRR */
#घोषणा UBC_CRR_PCB	(1 << 1)
#घोषणा UBC_CRR_BIE	(1 << 0)

/* CBR */
#घोषणा UBC_CBR_CE	(1 << 0)

अटल काष्ठा sh_ubc sh4a_ubc;

अटल व्योम sh4a_ubc_enable(काष्ठा arch_hw_अवरोधpoपूर्णांक *info, पूर्णांक idx)
अणु
	__raw_ग_लिखोl(UBC_CBR_CE | info->len | info->type, UBC_CBR(idx));
	__raw_ग_लिखोl(info->address, UBC_CAR(idx));
पूर्ण

अटल व्योम sh4a_ubc_disable(काष्ठा arch_hw_अवरोधpoपूर्णांक *info, पूर्णांक idx)
अणु
	__raw_ग_लिखोl(0, UBC_CBR(idx));
	__raw_ग_लिखोl(0, UBC_CAR(idx));
पूर्ण

अटल व्योम sh4a_ubc_enable_all(अचिन्हित दीर्घ mask)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sh4a_ubc.num_events; i++)
		अगर (mask & (1 << i))
			__raw_ग_लिखोl(__raw_पढ़ोl(UBC_CBR(i)) | UBC_CBR_CE,
				     UBC_CBR(i));
पूर्ण

अटल व्योम sh4a_ubc_disable_all(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sh4a_ubc.num_events; i++)
		__raw_ग_लिखोl(__raw_पढ़ोl(UBC_CBR(i)) & ~UBC_CBR_CE,
			     UBC_CBR(i));
पूर्ण

अटल अचिन्हित दीर्घ sh4a_ubc_active_mask(व्योम)
अणु
	अचिन्हित दीर्घ active = 0;
	पूर्णांक i;

	क्रम (i = 0; i < sh4a_ubc.num_events; i++)
		अगर (__raw_पढ़ोl(UBC_CBR(i)) & UBC_CBR_CE)
			active |= (1 << i);

	वापस active;
पूर्ण

अटल अचिन्हित दीर्घ sh4a_ubc_triggered_mask(व्योम)
अणु
	वापस __raw_पढ़ोl(UBC_CCMFR);
पूर्ण

अटल व्योम sh4a_ubc_clear_triggered_mask(अचिन्हित दीर्घ mask)
अणु
	__raw_ग_लिखोl(__raw_पढ़ोl(UBC_CCMFR) & ~mask, UBC_CCMFR);
पूर्ण

अटल काष्ठा sh_ubc sh4a_ubc = अणु
	.name			= "SH-4A",
	.num_events		= 2,
	.trap_nr		= 0x1e0,
	.enable			= sh4a_ubc_enable,
	.disable		= sh4a_ubc_disable,
	.enable_all		= sh4a_ubc_enable_all,
	.disable_all		= sh4a_ubc_disable_all,
	.active_mask		= sh4a_ubc_active_mask,
	.triggered_mask		= sh4a_ubc_triggered_mask,
	.clear_triggered_mask	= sh4a_ubc_clear_triggered_mask,
पूर्ण;

अटल पूर्णांक __init sh4a_ubc_init(व्योम)
अणु
	काष्ठा clk *ubc_iclk = clk_get(शून्य, "ubc0");
	पूर्णांक i;

	/*
	 * The UBC MSTP bit is optional, as not all platक्रमms will have
	 * it. Just ignore it अगर we can't find it.
	 */
	अगर (IS_ERR(ubc_iclk))
		ubc_iclk = शून्य;

	clk_enable(ubc_iclk);

	__raw_ग_लिखोl(0, UBC_CBCR);

	क्रम (i = 0; i < sh4a_ubc.num_events; i++) अणु
		__raw_ग_लिखोl(0, UBC_CAMR(i));
		__raw_ग_लिखोl(0, UBC_CBR(i));

		__raw_ग_लिखोl(UBC_CRR_BIE | UBC_CRR_PCB, UBC_CRR(i));

		/* dummy पढ़ो क्रम ग_लिखो posting */
		(व्योम)__raw_पढ़ोl(UBC_CRR(i));
	पूर्ण

	clk_disable(ubc_iclk);

	sh4a_ubc.clk = ubc_iclk;

	वापस रेजिस्टर_sh_ubc(&sh4a_ubc);
पूर्ण
arch_initcall(sh4a_ubc_init);
