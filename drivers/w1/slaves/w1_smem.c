<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	w1_smem.c
 *
 * Copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <यंत्र/types.h>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>

#समावेश <linux/w1.h>

#घोषणा W1_FAMILY_SMEM_01	0x01
#घोषणा W1_FAMILY_SMEM_81	0x81

अटल काष्ठा w1_family w1_smem_family_01 = अणु
	.fid = W1_FAMILY_SMEM_01,
पूर्ण;

अटल काष्ठा w1_family w1_smem_family_81 = अणु
	.fid = W1_FAMILY_SMEM_81,
पूर्ण;

अटल पूर्णांक __init w1_smem_init(व्योम)
अणु
	पूर्णांक err;

	err = w1_रेजिस्टर_family(&w1_smem_family_01);
	अगर (err)
		वापस err;

	err = w1_रेजिस्टर_family(&w1_smem_family_81);
	अगर (err) अणु
		w1_unरेजिस्टर_family(&w1_smem_family_01);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास w1_smem_fini(व्योम)
अणु
	w1_unरेजिस्टर_family(&w1_smem_family_01);
	w1_unरेजिस्टर_family(&w1_smem_family_81);
पूर्ण

module_init(w1_smem_init);
module_निकास(w1_smem_fini);

MODULE_AUTHOR("Evgeniy Polyakov <zbr@ioremap.net>");
MODULE_DESCRIPTION("Driver for 1-wire Dallas network protocol, 64bit memory family.");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_SMEM_01));
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_SMEM_81));
