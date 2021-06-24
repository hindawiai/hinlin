<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CRASH_H
#घोषणा _ASM_X86_CRASH_H

काष्ठा kimage;

पूर्णांक crash_load_segments(काष्ठा kimage *image);
पूर्णांक crash_setup_memmap_entries(काष्ठा kimage *image,
		काष्ठा boot_params *params);
व्योम crash_smp_send_stop(व्योम);

#अगर_घोषित CONFIG_KEXEC_CORE
व्योम __init crash_reserve_low_1M(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __init crash_reserve_low_1M(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_CRASH_H */
