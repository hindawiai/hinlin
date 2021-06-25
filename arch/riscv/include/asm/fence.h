<शैली गुरु>
#अगर_अघोषित _ASM_RISCV_FENCE_H
#घोषणा _ASM_RISCV_FENCE_H

#अगर_घोषित CONFIG_SMP
#घोषणा RISCV_ACQUIRE_BARRIER		"\tfence r , rw\n"
#घोषणा RISCV_RELEASE_BARRIER		"\tfence rw,  w\n"
#अन्यथा
#घोषणा RISCV_ACQUIRE_BARRIER
#घोषणा RISCV_RELEASE_BARRIER
#पूर्ण_अगर

#पूर्ण_अगर	/* _ASM_RISCV_FENCE_H */
