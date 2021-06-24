<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 Western Digital Corporation or its affiliates.
 * Linker script variables to be set after section resolution, as
 * ld.lld करोes not like variables asचिन्हित beक्रमe SECTIONS is processed.
 * Based on arch/arm64/kernel/image-vars.h
 */
#अगर_अघोषित __RISCV_KERNEL_IMAGE_VARS_H
#घोषणा __RISCV_KERNEL_IMAGE_VARS_H

#अगर_अघोषित LINKER_SCRIPT
#त्रुटि This file should only be included in vmlinux.lds.S
#पूर्ण_अगर

#अगर_घोषित CONFIG_EFI

/*
 * The EFI stub has its own symbol namespace prefixed by __efistub_, to
 * isolate it from the kernel proper. The following symbols are legally
 * accessed by the stub, so provide some aliases to make them accessible.
 * Only include data symbols here, or text symbols of functions that are
 * guaranteed to be safe when executed at another offset than they were
 * linked at. The routines below are all implemented in assembler in a
 * position independent manner
 */
__efistub_स_भेद		= स_भेद;
__efistub_स_प्रथम		= स_प्रथम;
__efistub_स_नकल		= स_नकल;
__efistub_स_हटाओ		= स_हटाओ;
__efistub_स_रखो		= स_रखो;
__efistub_म_माप		= म_माप;
__efistub_strnlen		= strnlen;
__efistub_म_भेद		= म_भेद;
__efistub_म_भेदन		= म_भेदन;
__efistub_म_खोजप		= म_खोजप;

#अगर_घोषित CONFIG_KASAN
__efistub___स_नकल		= स_नकल;
__efistub___स_हटाओ		= स_हटाओ;
__efistub___स_रखो		= स_रखो;
#पूर्ण_अगर

__efistub__start		= _start;
__efistub__start_kernel		= _start_kernel;
__efistub__end			= _end;
__efistub__edata		= _edata;
__efistub_screen_info		= screen_info;

#पूर्ण_अगर

#पूर्ण_अगर /* __RISCV_KERNEL_IMAGE_VARS_H */
