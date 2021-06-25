<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hardware parameter area specअगरic to Sharp SL series devices
 *
 * Copyright (c) 2005 Riअक्षरd Purdie
 *
 * Based on Sharp's 2.4 kernel patches
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/mach/sharpsl_param.h>
#समावेश <यंत्र/memory.h>

/*
 * Certain hardware parameters determined at the समय of device manufacture,
 * typically including LCD parameters are loaded by the bootloader at the
 * address PARAM_BASE. As the kernel will overग_लिखो them, we need to store
 * them early in the boot process, then pass them to the appropriate drivers.
 * Not all devices use all parameters but the क्रमmat is common to all.
 */
#अगर_घोषित CONFIG_ARCH_SA1100
#घोषणा PARAM_BASE	0xe8ffc000
#घोषणा param_start(x)	(व्योम *)(x)
#अन्यथा
#घोषणा PARAM_BASE	0xa0000a00
#घोषणा param_start(x)	__va(x)
#पूर्ण_अगर
#घोषणा MAGIC_CHG(a,b,c,d) ( ( d << 24 ) | ( c << 16 )  | ( b << 8 ) | a )

#घोषणा COMADJ_MAGIC	MAGIC_CHG('C','M','A','D')
#घोषणा UUID_MAGIC	MAGIC_CHG('U','U','I','D')
#घोषणा TOUCH_MAGIC	MAGIC_CHG('T','U','C','H')
#घोषणा AD_MAGIC	MAGIC_CHG('B','V','A','D')
#घोषणा PHAD_MAGIC	MAGIC_CHG('P','H','A','D')

काष्ठा sharpsl_param_info sharpsl_param;
EXPORT_SYMBOL(sharpsl_param);

व्योम sharpsl_save_param(व्योम)
अणु
	स_नकल(&sharpsl_param, param_start(PARAM_BASE), माप(काष्ठा sharpsl_param_info));

	अगर (sharpsl_param.comadj_keyword != COMADJ_MAGIC)
		sharpsl_param.comadj=-1;

	अगर (sharpsl_param.phad_keyword != PHAD_MAGIC)
		sharpsl_param.phadadj=-1;

	अगर (sharpsl_param.uuid_keyword != UUID_MAGIC)
		sharpsl_param.uuid[0]=-1;

	अगर (sharpsl_param.touch_keyword != TOUCH_MAGIC)
		sharpsl_param.touch_xp=-1;

	अगर (sharpsl_param.adadj_keyword != AD_MAGIC)
		sharpsl_param.adadj=-1;
पूर्ण


