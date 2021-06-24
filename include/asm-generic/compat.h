<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_GENERIC_COMPAT_H
#घोषणा __ASM_GENERIC_COMPAT_H

/* These types are common across all compat ABIs */
प्रकार u32 compat_माप_प्रकार;
प्रकार s32 compat_sमाप_प्रकार;
प्रकार s32 compat_घड़ी_प्रकार;
प्रकार s32 compat_pid_t;
प्रकार u32 compat_ino_t;
प्रकार s32 compat_off_t;
प्रकार s64 compat_loff_t;
प्रकार s32 compat_daddr_t;
प्रकार s32 compat_समयr_t;
प्रकार s32 compat_key_t;
प्रकार s16 compat_लघु_t;
प्रकार s32 compat_पूर्णांक_t;
प्रकार s32 compat_दीर्घ_t;
प्रकार u16 compat_uलघु_t;
प्रकार u32 compat_uपूर्णांक_t;
प्रकार u32 compat_uदीर्घ_t;
प्रकार u32 compat_uptr_t;
प्रकार u32 compat_aio_context_t;

#अगर_घोषित CONFIG_COMPAT_FOR_U64_ALIGNMENT
प्रकार s64 __attribute__((aligned(4))) compat_s64;
प्रकार u64 __attribute__((aligned(4))) compat_u64;
#अन्यथा
प्रकार s64 compat_s64;
प्रकार u64 compat_u64;
#पूर्ण_अगर

#पूर्ण_अगर
