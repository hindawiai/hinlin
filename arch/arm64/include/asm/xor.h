<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm64/include/यंत्र/xor.h
 *
 * Authors: Jackie Liu <liuyun01@kylinos.cn>
 * Copyright (C) 2018,Tianjin KYLIN Inक्रमmation Technology Co., Ltd.
 */

#समावेश <linux/hardirq.h>
#समावेश <यंत्र-generic/xor.h>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/neon.h>

#अगर_घोषित CONFIG_KERNEL_MODE_NEON

बाह्य काष्ठा xor_block_ढाँचा स्थिर xor_block_inner_neon;

अटल व्योम
xor_neon_2(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2)
अणु
	kernel_neon_begin();
	xor_block_inner_neon.करो_2(bytes, p1, p2);
	kernel_neon_end();
पूर्ण

अटल व्योम
xor_neon_3(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
		अचिन्हित दीर्घ *p3)
अणु
	kernel_neon_begin();
	xor_block_inner_neon.करो_3(bytes, p1, p2, p3);
	kernel_neon_end();
पूर्ण

अटल व्योम
xor_neon_4(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
		अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4)
अणु
	kernel_neon_begin();
	xor_block_inner_neon.करो_4(bytes, p1, p2, p3, p4);
	kernel_neon_end();
पूर्ण

अटल व्योम
xor_neon_5(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *p1, अचिन्हित दीर्घ *p2,
		अचिन्हित दीर्घ *p3, अचिन्हित दीर्घ *p4, अचिन्हित दीर्घ *p5)
अणु
	kernel_neon_begin();
	xor_block_inner_neon.करो_5(bytes, p1, p2, p3, p4, p5);
	kernel_neon_end();
पूर्ण

अटल काष्ठा xor_block_ढाँचा xor_block_arm64 = अणु
	.name   = "arm64_neon",
	.करो_2   = xor_neon_2,
	.करो_3   = xor_neon_3,
	.करो_4   = xor_neon_4,
	.करो_5	= xor_neon_5
पूर्ण;
#अघोषित XOR_TRY_TEMPLATES
#घोषणा XOR_TRY_TEMPLATES           \
	करो अणु        \
		xor_speed(&xor_block_8regs);    \
		xor_speed(&xor_block_32regs);    \
		अगर (cpu_has_neon()) अणु \
			xor_speed(&xor_block_arm64);\
		पूर्ण \
	पूर्ण जबतक (0)

#पूर्ण_अगर /* ! CONFIG_KERNEL_MODE_NEON */
