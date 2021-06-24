<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _WCD_CLSH_V2_H_
#घोषणा _WCD_CLSH_V2_H_
#समावेश <sound/soc.h>

क्रमागत wcd_clsh_event अणु
	WCD_CLSH_EVENT_PRE_DAC = 1,
	WCD_CLSH_EVENT_POST_PA,
पूर्ण;

/*
 * Basic states क्रम Class H state machine.
 * represented as a bit mask within a u8 data type
 * bit 0: EAR mode
 * bit 1: HPH Left mode
 * bit 2: HPH Right mode
 * bit 3: Lineout mode
 */
#घोषणा	WCD_CLSH_STATE_IDLE	0
#घोषणा	WCD_CLSH_STATE_EAR	BIT(0)
#घोषणा	WCD_CLSH_STATE_HPHL	BIT(1)
#घोषणा	WCD_CLSH_STATE_HPHR	BIT(2)
#घोषणा	WCD_CLSH_STATE_LO	BIT(3)
#घोषणा WCD_CLSH_STATE_MAX	4
#घोषणा NUM_CLSH_STATES_V2	BIT(WCD_CLSH_STATE_MAX)

क्रमागत wcd_clsh_mode अणु
	CLS_H_NORMAL = 0, /* Class-H Default */
	CLS_H_HIFI, /* Class-H HiFi */
	CLS_H_LP, /* Class-H Low Power */
	CLS_AB, /* Class-AB */
	CLS_H_LOHIFI, /* LoHIFI */
	CLS_NONE, /* None of the above modes */
पूर्ण;

काष्ठा wcd_clsh_ctrl;

बाह्य काष्ठा wcd_clsh_ctrl *wcd_clsh_ctrl_alloc(
				काष्ठा snd_soc_component *comp,
				पूर्णांक version);
बाह्य व्योम wcd_clsh_ctrl_मुक्त(काष्ठा wcd_clsh_ctrl *ctrl);
बाह्य पूर्णांक wcd_clsh_ctrl_get_state(काष्ठा wcd_clsh_ctrl *ctrl);
बाह्य पूर्णांक wcd_clsh_ctrl_set_state(काष्ठा wcd_clsh_ctrl *ctrl,
				   क्रमागत wcd_clsh_event clsh_event,
				   पूर्णांक nstate,
				   क्रमागत wcd_clsh_mode mode);

#पूर्ण_अगर /* _WCD_CLSH_V2_H_ */
