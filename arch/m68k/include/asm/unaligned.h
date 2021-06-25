<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_M68K_UNALIGNED_H
#घोषणा _ASM_M68K_UNALIGNED_H


#अगर_घोषित CONFIG_CPU_HAS_NO_UNALIGNED
#समावेश <linux/unaligned/be_काष्ठा.h>
#समावेश <linux/unaligned/le_byteshअगरt.h>
#समावेश <linux/unaligned/generic.h>

#घोषणा get_unaligned	__get_unaligned_be
#घोषणा put_unaligned	__put_unaligned_be

#अन्यथा
/*
 * The m68k can करो unaligned accesses itself.
 */
#समावेश <linux/unaligned/access_ok.h>
#समावेश <linux/unaligned/generic.h>

#घोषणा get_unaligned	__get_unaligned_be
#घोषणा put_unaligned	__put_unaligned_be

#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_M68K_UNALIGNED_H */
