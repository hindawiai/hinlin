<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_TC_PED_H
#घोषणा __NET_TC_PED_H

#समावेश <net/act_api.h>
#समावेश <linux/tc_act/tc_pedit.h>

काष्ठा tcf_pedit_key_ex अणु
	क्रमागत pedit_header_type htype;
	क्रमागत pedit_cmd cmd;
पूर्ण;

काष्ठा tcf_pedit अणु
	काष्ठा tc_action	common;
	अचिन्हित अक्षर		tcfp_nkeys;
	अचिन्हित अक्षर		tcfp_flags;
	काष्ठा tc_pedit_key	*tcfp_keys;
	काष्ठा tcf_pedit_key_ex	*tcfp_keys_ex;
पूर्ण;

#घोषणा to_pedit(a) ((काष्ठा tcf_pedit *)a)

अटल अंतरभूत bool is_tcf_pedit(स्थिर काष्ठा tc_action *a)
अणु
#अगर_घोषित CONFIG_NET_CLS_ACT
	अगर (a->ops && a->ops->id == TCA_ID_PEDIT)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_pedit_nkeys(स्थिर काष्ठा tc_action *a)
अणु
	वापस to_pedit(a)->tcfp_nkeys;
पूर्ण

अटल अंतरभूत u32 tcf_pedit_htype(स्थिर काष्ठा tc_action *a, पूर्णांक index)
अणु
	अगर (to_pedit(a)->tcfp_keys_ex)
		वापस to_pedit(a)->tcfp_keys_ex[index].htype;

	वापस TCA_PEDIT_KEY_EX_HDR_TYPE_NETWORK;
पूर्ण

अटल अंतरभूत u32 tcf_pedit_cmd(स्थिर काष्ठा tc_action *a, पूर्णांक index)
अणु
	अगर (to_pedit(a)->tcfp_keys_ex)
		वापस to_pedit(a)->tcfp_keys_ex[index].cmd;

	वापस __PEDIT_CMD_MAX;
पूर्ण

अटल अंतरभूत u32 tcf_pedit_mask(स्थिर काष्ठा tc_action *a, पूर्णांक index)
अणु
	वापस to_pedit(a)->tcfp_keys[index].mask;
पूर्ण

अटल अंतरभूत u32 tcf_pedit_val(स्थिर काष्ठा tc_action *a, पूर्णांक index)
अणु
	वापस to_pedit(a)->tcfp_keys[index].val;
पूर्ण

अटल अंतरभूत u32 tcf_pedit_offset(स्थिर काष्ठा tc_action *a, पूर्णांक index)
अणु
	वापस to_pedit(a)->tcfp_keys[index].off;
पूर्ण
#पूर्ण_अगर /* __NET_TC_PED_H */
