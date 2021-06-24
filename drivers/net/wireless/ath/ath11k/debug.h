<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ATH11K_DEBUG_H_
#घोषणा _ATH11K_DEBUG_H_

#समावेश "trace.h"
#समावेश "debugfs.h"

क्रमागत ath11k_debug_mask अणु
	ATH11K_DBG_AHB		= 0x00000001,
	ATH11K_DBG_WMI		= 0x00000002,
	ATH11K_DBG_HTC		= 0x00000004,
	ATH11K_DBG_DP_HTT	= 0x00000008,
	ATH11K_DBG_MAC		= 0x00000010,
	ATH11K_DBG_BOOT		= 0x00000020,
	ATH11K_DBG_QMI		= 0x00000040,
	ATH11K_DBG_DATA		= 0x00000080,
	ATH11K_DBG_MGMT		= 0x00000100,
	ATH11K_DBG_REG		= 0x00000200,
	ATH11K_DBG_TESTMODE	= 0x00000400,
	ATH11k_DBG_HAL		= 0x00000800,
	ATH11K_DBG_PCI		= 0x00001000,
	ATH11K_DBG_DP_TX	= 0x00001000,
	ATH11K_DBG_DP_RX	= 0x00002000,
	ATH11K_DBG_ANY		= 0xffffffff,
पूर्ण;

__म_लिखो(2, 3) व्योम ath11k_info(काष्ठा ath11k_base *ab, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) व्योम ath11k_err(काष्ठा ath11k_base *ab, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) व्योम ath11k_warn(काष्ठा ath11k_base *ab, स्थिर अक्षर *fmt, ...);

बाह्य अचिन्हित पूर्णांक ath11k_debug_mask;

#अगर_घोषित CONFIG_ATH11K_DEBUG
__म_लिखो(3, 4) व्योम __ath11k_dbg(काष्ठा ath11k_base *ab,
				 क्रमागत ath11k_debug_mask mask,
				 स्थिर अक्षर *fmt, ...);
व्योम ath11k_dbg_dump(काष्ठा ath11k_base *ab,
		     क्रमागत ath11k_debug_mask mask,
		     स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
		     स्थिर व्योम *buf, माप_प्रकार len);
#अन्यथा /* CONFIG_ATH11K_DEBUG */
अटल अंतरभूत पूर्णांक __ath11k_dbg(काष्ठा ath11k_base *ab,
			       क्रमागत ath11k_debug_mask dbg_mask,
			       स्थिर अक्षर *fmt, ...)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ath11k_dbg_dump(काष्ठा ath11k_base *ab,
				   क्रमागत ath11k_debug_mask mask,
				   स्थिर अक्षर *msg, स्थिर अक्षर *prefix,
				   स्थिर व्योम *buf, माप_प्रकार len)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH11K_DEBUG */

#घोषणा ath11k_dbg(ar, dbg_mask, fmt, ...)			\
करो अणु								\
	अगर (ath11k_debug_mask & dbg_mask)			\
		__ath11k_dbg(ar, dbg_mask, fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#पूर्ण_अगर /* _ATH11K_DEBUG_H_ */
