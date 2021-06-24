<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * (C) Copyright TOSHIBA CORPORATION 2007
 */
#अगर_अघोषित __TXX9_NDFMC_H
#घोषणा __TXX9_NDFMC_H

#घोषणा NDFMC_PLAT_FLAG_USE_BSPRT	0x01
#घोषणा NDFMC_PLAT_FLAG_NO_RSTR		0x02
#घोषणा NDFMC_PLAT_FLAG_HOLDADD		0x04
#घोषणा NDFMC_PLAT_FLAG_DUMMYWRITE	0x08

काष्ठा txx9ndfmc_platक्रमm_data अणु
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक gbus_घड़ी;
	अचिन्हित पूर्णांक hold;		/* hold समय in nanosecond */
	अचिन्हित पूर्णांक spw;		/* strobe pulse width in nanosecond */
	अचिन्हित पूर्णांक flags;
	अचिन्हित अक्षर ch_mask;		/* available channel biपंचांगask */
	अचिन्हित अक्षर wp_mask;		/* ग_लिखो-protect biपंचांगask */
	अचिन्हित अक्षर wide_mask;	/* 16bit-nand biपंचांगask */
पूर्ण;

व्योम txx9_ndfmc_init(अचिन्हित दीर्घ baseaddr,
		     स्थिर काष्ठा txx9ndfmc_platक्रमm_data *plat_data);

#पूर्ण_अगर /* __TXX9_NDFMC_H */
