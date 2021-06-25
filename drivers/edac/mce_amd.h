<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _EDAC_MCE_AMD_H
#घोषणा _EDAC_MCE_AMD_H

#समावेश <linux/notअगरier.h>

#समावेश <यंत्र/mce.h>

#घोषणा EC(x)				((x) & 0xffff)

#घोषणा LOW_SYNDROME(x)			(((x) >> 15) & 0xff)
#घोषणा HIGH_SYNDROME(x)		(((x) >> 24) & 0xff)

#घोषणा TLB_ERROR(x)			(((x) & 0xFFF0) == 0x0010)
#घोषणा MEM_ERROR(x)			(((x) & 0xFF00) == 0x0100)
#घोषणा BUS_ERROR(x)			(((x) & 0xF800) == 0x0800)
#घोषणा INT_ERROR(x)			(((x) & 0xF4FF) == 0x0400)

#घोषणा TT(x)				(((x) >> 2) & 0x3)
#घोषणा TT_MSG(x)			tt_msgs[TT(x)]
#घोषणा II(x)				(((x) >> 2) & 0x3)
#घोषणा II_MSG(x)			ii_msgs[II(x)]
#घोषणा LL(x)				((x) & 0x3)
#घोषणा LL_MSG(x)			ll_msgs[LL(x)]
#घोषणा TO(x)				(((x) >> 8) & 0x1)
#घोषणा TO_MSG(x)			to_msgs[TO(x)]
#घोषणा PP(x)				(((x) >> 9) & 0x3)
#घोषणा PP_MSG(x)			pp_msgs[PP(x)]
#घोषणा UU(x)				(((x) >> 8) & 0x3)
#घोषणा UU_MSG(x)			uu_msgs[UU(x)]

#घोषणा R4(x)				(((x) >> 4) & 0xf)
#घोषणा R4_MSG(x)			((R4(x) < 9) ?  rrrr_msgs[R4(x)] : "Wrong R4!")

बाह्य स्थिर अक्षर * स्थिर pp_msgs[];

क्रमागत tt_ids अणु
	TT_INSTR = 0,
	TT_DATA,
	TT_GEN,
	TT_RESV,
पूर्ण;

क्रमागत ll_ids अणु
	LL_RESV = 0,
	LL_L1,
	LL_L2,
	LL_LG,
पूर्ण;

क्रमागत ii_ids अणु
	II_MEM = 0,
	II_RESV,
	II_IO,
	II_GEN,
पूर्ण;

क्रमागत rrrr_ids अणु
	R4_GEN	= 0,
	R4_RD,
	R4_WR,
	R4_DRD,
	R4_DWR,
	R4_IRD,
	R4_PREF,
	R4_EVICT,
	R4_SNOOP,
पूर्ण;

/*
 * per-family decoder ops
 */
काष्ठा amd_decoder_ops अणु
	bool (*mc0_mce)(u16, u8);
	bool (*mc1_mce)(u16, u8);
	bool (*mc2_mce)(u16, u8);
पूर्ण;

व्योम amd_रेजिस्टर_ecc_decoder(व्योम (*f)(पूर्णांक, काष्ठा mce *));
व्योम amd_unरेजिस्टर_ecc_decoder(व्योम (*f)(पूर्णांक, काष्ठा mce *));

#पूर्ण_अगर /* _EDAC_MCE_AMD_H */
