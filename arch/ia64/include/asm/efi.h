<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_EFI_H
#घोषणा _ASM_EFI_H

प्रकार पूर्णांक (*efi_मुक्तmem_callback_t) (u64 start, u64 end, व्योम *arg);

व्योम *efi_get_pal_addr(व्योम);
व्योम efi_map_pal_code(व्योम);
व्योम efi_memmap_walk(efi_मुक्तmem_callback_t, व्योम *);
व्योम efi_memmap_walk_uc(efi_मुक्तmem_callback_t, व्योम *);
व्योम efi_समय_लोofday(काष्ठा बारpec64 *ts);

#पूर्ण_अगर
