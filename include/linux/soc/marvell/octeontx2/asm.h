<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 * Copyright (C) 2020 Marvell.
 */

#अगर_अघोषित __SOC_OTX2_ASM_H
#घोषणा __SOC_OTX2_ASM_H

#अगर defined(CONFIG_ARM64)
/*
 * otx2_lmt_flush is used क्रम LMT store operation.
 * On octeontx2 platक्रमm CPT inकाष्ठाion enqueue and
 * NIX packet send are only possible via LMTST
 * operations and it uses LDEOR inकाष्ठाion targeting
 * the coprocessor address.
 */
#घोषणा otx2_lmt_flush(ioaddr)                          \
(अणु                                                      \
	u64 result = 0;                                 \
	__यंत्र__ अस्थिर(".cpu  generic+lse\n"          \
			 "ldeor xzr, %x[rf], [%[rs]]"   \
			 : [rf]"=r" (result)            \
			 : [rs]"r" (ioaddr));           \
	(result);                                       \
पूर्ण)
#घोषणा cn10k_lmt_flush(val, addr)			\
(अणु							\
	__यंत्र__ अस्थिर(".cpu  generic+lse\n"		\
			 "steor %x[rf],[%[rs]]"		\
			 : [rf]"+r"(val)		\
			 : [rs]"r"(addr));		\
पूर्ण)
#अन्यथा
#घोषणा otx2_lmt_flush(ioaddr)          (अणु 0; पूर्ण)
#घोषणा cn10k_lmt_flush(val, addr)	(अणु addr = val; पूर्ण)
#पूर्ण_अगर

#पूर्ण_अगर /* __SOC_OTX2_ASM_H */
