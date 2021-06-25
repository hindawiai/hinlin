<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_VGTOD_H
#घोषणा _ASM_X86_VGTOD_H

/*
 * This check is required to prevent ARCH=um to include
 * unwanted headers.
 */
#अगर_घोषित CONFIG_GENERIC_GETTIMखातापूर्णDAY
#समावेश <linux/compiler.h>
#समावेश <यंत्र/घड़ीsource.h>
#समावेश <vdso/datapage.h>
#समावेश <vdso/helpers.h>

#समावेश <uapi/linux/समय.स>

#अगर_घोषित BUILD_VDSO32_64
प्रकार u64 gtod_दीर्घ_t;
#अन्यथा
प्रकार अचिन्हित दीर्घ gtod_दीर्घ_t;
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_GENERIC_GETTIMखातापूर्णDAY */

#पूर्ण_अगर /* _ASM_X86_VGTOD_H */
