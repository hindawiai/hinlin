<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __QCOM_SMEM_STATE__
#घोषणा __QCOM_SMEM_STATE__

#समावेश <linux/err.h>

काष्ठा device_node;
काष्ठा qcom_smem_state;

काष्ठा qcom_smem_state_ops अणु
	पूर्णांक (*update_bits)(व्योम *, u32, u32);
पूर्ण;

#अगर_घोषित CONFIG_QCOM_SMEM_STATE

काष्ठा qcom_smem_state *qcom_smem_state_get(काष्ठा device *dev, स्थिर अक्षर *con_id, अचिन्हित *bit);
व्योम qcom_smem_state_put(काष्ठा qcom_smem_state *);

पूर्णांक qcom_smem_state_update_bits(काष्ठा qcom_smem_state *state, u32 mask, u32 value);

काष्ठा qcom_smem_state *qcom_smem_state_रेजिस्टर(काष्ठा device_node *of_node, स्थिर काष्ठा qcom_smem_state_ops *ops, व्योम *data);
व्योम qcom_smem_state_unरेजिस्टर(काष्ठा qcom_smem_state *state);

#अन्यथा

अटल अंतरभूत काष्ठा qcom_smem_state *qcom_smem_state_get(काष्ठा device *dev,
	स्थिर अक्षर *con_id, अचिन्हित *bit)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत व्योम qcom_smem_state_put(काष्ठा qcom_smem_state *state)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक qcom_smem_state_update_bits(काष्ठा qcom_smem_state *state,
	u32 mask, u32 value)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा qcom_smem_state *qcom_smem_state_रेजिस्टर(काष्ठा device_node *of_node,
	स्थिर काष्ठा qcom_smem_state_ops *ops, व्योम *data)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत व्योम qcom_smem_state_unरेजिस्टर(काष्ठा qcom_smem_state *state)
अणु
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
